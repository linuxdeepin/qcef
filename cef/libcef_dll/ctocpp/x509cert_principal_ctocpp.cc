// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=6f1cfb4286ceb605bfc6ba718d0ef1b3620bb9de$
//

#include "libcef_dll/ctocpp/x509cert_principal_ctocpp.h"
#include "libcef_dll/transfer_util.h"

// VIRTUAL METHODS - Body may be edited by hand.

CefString CefX509CertPrincipalCToCpp::GetDisplayName() {
  cef_x509cert_principal_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_display_name))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = _struct->get_display_name(_struct);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

CefString CefX509CertPrincipalCToCpp::GetCommonName() {
  cef_x509cert_principal_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_common_name))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = _struct->get_common_name(_struct);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

CefString CefX509CertPrincipalCToCpp::GetLocalityName() {
  cef_x509cert_principal_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_locality_name))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = _struct->get_locality_name(_struct);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

CefString CefX509CertPrincipalCToCpp::GetStateOrProvinceName() {
  cef_x509cert_principal_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_state_or_province_name))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = _struct->get_state_or_province_name(_struct);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

CefString CefX509CertPrincipalCToCpp::GetCountryName() {
  cef_x509cert_principal_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_country_name))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = _struct->get_country_name(_struct);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

void CefX509CertPrincipalCToCpp::GetStreetAddresses(
    std::vector<CefString>& addresses) {
  cef_x509cert_principal_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_street_addresses))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Translate param: addresses; type: string_vec_byref
  cef_string_list_t addressesList = cef_string_list_alloc();
  DCHECK(addressesList);
  if (addressesList)
    transfer_string_list_contents(addresses, addressesList);

  // Execute
  _struct->get_street_addresses(_struct, addressesList);

  // Restore param:addresses; type: string_vec_byref
  if (addressesList) {
    addresses.clear();
    transfer_string_list_contents(addressesList, addresses);
    cef_string_list_free(addressesList);
  }
}

void CefX509CertPrincipalCToCpp::GetOrganizationNames(
    std::vector<CefString>& names) {
  cef_x509cert_principal_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_organization_names))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Translate param: names; type: string_vec_byref
  cef_string_list_t namesList = cef_string_list_alloc();
  DCHECK(namesList);
  if (namesList)
    transfer_string_list_contents(names, namesList);

  // Execute
  _struct->get_organization_names(_struct, namesList);

  // Restore param:names; type: string_vec_byref
  if (namesList) {
    names.clear();
    transfer_string_list_contents(namesList, names);
    cef_string_list_free(namesList);
  }
}

void CefX509CertPrincipalCToCpp::GetOrganizationUnitNames(
    std::vector<CefString>& names) {
  cef_x509cert_principal_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_organization_unit_names))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Translate param: names; type: string_vec_byref
  cef_string_list_t namesList = cef_string_list_alloc();
  DCHECK(namesList);
  if (namesList)
    transfer_string_list_contents(names, namesList);

  // Execute
  _struct->get_organization_unit_names(_struct, namesList);

  // Restore param:names; type: string_vec_byref
  if (namesList) {
    names.clear();
    transfer_string_list_contents(namesList, names);
    cef_string_list_free(namesList);
  }
}

void CefX509CertPrincipalCToCpp::GetDomainComponents(
    std::vector<CefString>& components) {
  cef_x509cert_principal_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_domain_components))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Translate param: components; type: string_vec_byref
  cef_string_list_t componentsList = cef_string_list_alloc();
  DCHECK(componentsList);
  if (componentsList)
    transfer_string_list_contents(components, componentsList);

  // Execute
  _struct->get_domain_components(_struct, componentsList);

  // Restore param:components; type: string_vec_byref
  if (componentsList) {
    components.clear();
    transfer_string_list_contents(componentsList, components);
    cef_string_list_free(componentsList);
  }
}

// CONSTRUCTOR - Do not edit by hand.

CefX509CertPrincipalCToCpp::CefX509CertPrincipalCToCpp() {}

template <>
cef_x509cert_principal_t* CefCToCppRefCounted<
    CefX509CertPrincipalCToCpp,
    CefX509CertPrincipal,
    cef_x509cert_principal_t>::UnwrapDerived(CefWrapperType type,
                                             CefX509CertPrincipal* c) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#if DCHECK_IS_ON()
template <>
base::AtomicRefCount CefCToCppRefCounted<CefX509CertPrincipalCToCpp,
                                         CefX509CertPrincipal,
                                         cef_x509cert_principal_t>::DebugObjCt =
    0;
#endif

template <>
CefWrapperType CefCToCppRefCounted<CefX509CertPrincipalCToCpp,
                                   CefX509CertPrincipal,
                                   cef_x509cert_principal_t>::kWrapperType =
    WT_X509CERT_PRINCIPAL;