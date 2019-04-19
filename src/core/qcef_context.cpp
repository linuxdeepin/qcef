/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "core/qcef_context.h"

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QtCore/QThread>

#include "core/qcef_app.h"
#include "core/qcef_cookie_store.h"
#include "core/qcef_x11_util.h"
#include "include/cef_path_util.h"
#include "include/wrapper/cef_helpers.h"

namespace {

QTimer* g_cef_timer = nullptr;

}  // namespace

int QCefInit(int argc, char** argv, const QCefGlobalSettings& settings) {
  SetXErrorHandler();

  int cef_argc = argc;
  char** cef_argv = nullptr;
  // TODO(LiuLang): Free memory block.
  cef_argv = static_cast<char**>(calloc(static_cast<size_t>(cef_argc),
                                        sizeof(argv[0])));
  memcpy(cef_argv, argv, argc * sizeof(argv[0]));

  CefMainArgs main_args(cef_argc, cef_argv);
  CefRefPtr<QCefApp> client_app(new QCefApp());

  // Add flash plugin parameters.
  QCefCommandLineSwitchList arguments(settings.getCommandLineSwitches());
  if (settings.pepperFlash()) {
    arguments.push_back({"ppapi-flash-path",
                         settings.getPepperFlashPath()});
    arguments.push_back({"ppapi-flash-version",
                         settings.getPepperFlashVersion()});
  }

  switch (settings.proxyType()) {
    case QCefGlobalSettings::ProxyType::NoProxy: {
      arguments.push_back({"--no-proxy-server", ""});
      break;
    }
    case QCefGlobalSettings::ProxyType::PacUrl: {
      arguments.push_back({"--proxy-pac-url", settings.proxyInfo()});
      break;
    }
    case QCefGlobalSettings::ProxyType::ProxyServer: {
      arguments.push_back({"--proxy-server", settings.proxyInfo()});
      break;
    }
    case QCefGlobalSettings::ProxyType::AutoDetect: {
      arguments.push_back({"--proxy-auto-detect", ""});
      break;
    }
    default: {
      break;
    }
  }

  client_app->appendCommandLineSwitches(arguments);

  client_app->addCustomSchemes(settings.customSchemes());

  client_app->setCustomSchemeHandler(settings.getCustomSchemeHandler());

  client_app->setSyncMethods(settings.getSyncMethods());

  client_app->setRegisterScripts(settings.getUserScripts());

  QString runtime_override_path;
  const QByteArray kQcefInstallPathEnv = qgetenv("QCEF_INSTALL_PATH");
  if (!kQcefInstallPathEnv.isEmpty()) {
    // If QCEF_INSTALL_PATH environment is set, by pass all other options.
    runtime_override_path = kQcefInstallPathEnv;
  } else {
    // First, check runtime override path.
    runtime_override_path = settings.getOverridePath();
    if (runtime_override_path.isEmpty()) {
      // Then check compile-time override path.
#ifdef QCEF_OVERRIDE_PATH
      runtime_override_path = QCEF_OVERRIDE_PATH;
#endif
    }
  }

  if (!runtime_override_path.isEmpty()) {
    const std::string p = runtime_override_path.toStdString();
    if (!CefOverridePath(PK_DIR_EXE, p)) {
      qCritical() << "Failed to override PK_DIR_EXE" << runtime_override_path;
    }
    if (!CefOverridePath(PK_DIR_MODULE, p)) {
      qCritical() << "Failed to override PK_DIR_MODULE"
                  << runtime_override_path;
    }
  }

  // CEF applications have multiple sub-processes (render, plugin, GPU, etc)
  // that share the same executable. This function checks the command-line and,
  // if this is a sub-process, executes the appropriate logic.
  int exit_code = CefExecuteProcess(main_args, client_app.get(), nullptr);
  if (exit_code >= 0) {
    // The sub-process has completed so return here.
    return exit_code;
  }

  // Merge CEF global settings.
  CefSettings cef_settings;
  cef_settings.background_color = settings.backgroundColor();
  cef_settings.single_process = settings.singleProcess() ? 1 : 0;
  cef_settings.no_sandbox = settings.noSandbox() ? 1 : 0;
  cef_settings.command_line_args_disabled =
      settings.disableCommandLineArgs() ? 1 : 0;
  CefString(&cef_settings.cache_path) = settings.cachePath().toStdString();
  CefString(&cef_settings.user_data_path) =
      settings.userDataPath().toStdString();
  cef_settings.persist_session_cookies =
      settings.persistSessionCookies() ? 1 : 0;
  cef_settings.persist_user_preferences =
      settings.persistUserPreferences() ? 1 : 0;
  CefString(&cef_settings.user_agent) = settings.userAgent().toStdString();
  CefString(&cef_settings.log_file) = settings.logFile().toStdString();
  switch (settings.logSeverity()) {
    case QCefGlobalSettings::LogSeverity::Default: {
      cef_settings.log_severity = LOGSEVERITY_DEFAULT;
      break;
    }
    case QCefGlobalSettings::LogSeverity::Verbose: {
      cef_settings.log_severity = LOGSEVERITY_VERBOSE;
      break;
    }
    case QCefGlobalSettings::LogSeverity::Info: {
      cef_settings.log_severity = LOGSEVERITY_INFO;
      break;
    }
    case QCefGlobalSettings::LogSeverity::Warning: {
      cef_settings.log_severity = LOGSEVERITY_WARNING;
      break;
    }
    case QCefGlobalSettings::LogSeverity::Error: {
      cef_settings.log_severity = LOGSEVERITY_ERROR;
      break;
    }
    case QCefGlobalSettings::LogSeverity::Disable: {
      cef_settings.log_severity = LOGSEVERITY_DISABLE;
      break;
    }
  }
  if (settings.remoteDebug()) {
    cef_settings.remote_debugging_port = settings.remoteDebugPort();
  }
  cef_settings.ignore_certificate_errors =
      settings.ignoresCertificateErrors() ? 1 : 0;
  CefString(&cef_settings.accept_language_list) =
      settings.acceptLanguageList().toStdString();
  CefString(&cef_settings.locale) = settings.locale().toStdString();

  // Integrate CEF message with Qt Message Loop.
  cef_settings.external_message_pump = 0;

  // Initialize CEF for the browser process.
  if (!CefInitialize(main_args, cef_settings, client_app.get(), nullptr)) {
    qCritical() << "CefInitialize() failed!";
    return -2;
  }
  return -1;
}

void QCefBindApp(QCoreApplication* app) {
  CEF_REQUIRE_UI_THREAD();
  QObject::connect(app, &QCoreApplication::aboutToQuit, QCefStopTimer);
  QObject::connect(app, &QCoreApplication::destroyed, CefShutdown);

  Q_ASSERT(g_cef_timer == nullptr);
  g_cef_timer = new QTimer();
  g_cef_timer->setInterval(1);
  QObject::connect(g_cef_timer, &QTimer::timeout, CefDoMessageLoopWork);
  g_cef_timer->start();
}

void QCefStopTimer() {
  QCefFlushCookies();
  QThread::msleep(300);
  if (g_cef_timer != nullptr) {
    g_cef_timer->stop();
    g_cef_timer->deleteLater();
    g_cef_timer = nullptr;
  }
}

void QCefShutdown() {
  CefShutdown();
}
