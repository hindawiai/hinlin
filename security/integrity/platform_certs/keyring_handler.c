<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/err.h>
#समावेश <linux/efi.h>
#समावेश <linux/slab.h>
#समावेश <keys/asymmetric-type.h>
#समावेश <keys/प्रणाली_keyring.h>
#समावेश "../integrity.h"

अटल efi_guid_t efi_cert_x509_guid __initdata = EFI_CERT_X509_GUID;
अटल efi_guid_t efi_cert_x509_sha256_guid __initdata =
	EFI_CERT_X509_SHA256_GUID;
अटल efi_guid_t efi_cert_sha256_guid __initdata = EFI_CERT_SHA256_GUID;

/*
 * Blacklist a hash.
 */
अटल __init व्योम uefi_blacklist_hash(स्थिर अक्षर *source, स्थिर व्योम *data,
				       माप_प्रकार len, स्थिर अक्षर *type,
				       माप_प्रकार type_len)
अणु
	अक्षर *hash, *p;

	hash = kदो_स्मृति(type_len + len * 2 + 1, GFP_KERNEL);
	अगर (!hash)
		वापस;
	p = स_नकल(hash, type, type_len);
	p += type_len;
	bin2hex(p, data, len);
	p += len * 2;
	*p = 0;

	mark_hash_blacklisted(hash);
	kमुक्त(hash);
पूर्ण

/*
 * Blacklist an X509 TBS hash.
 */
अटल __init व्योम uefi_blacklist_x509_tbs(स्थिर अक्षर *source,
					   स्थिर व्योम *data, माप_प्रकार len)
अणु
	uefi_blacklist_hash(source, data, len, "tbs:", 4);
पूर्ण

/*
 * Blacklist the hash of an executable.
 */
अटल __init व्योम uefi_blacklist_binary(स्थिर अक्षर *source,
					 स्थिर व्योम *data, माप_प्रकार len)
अणु
	uefi_blacklist_hash(source, data, len, "bin:", 4);
पूर्ण

/*
 * Add an X509 cert to the revocation list.
 */
अटल __init व्योम uefi_revocation_list_x509(स्थिर अक्षर *source,
					     स्थिर व्योम *data, माप_प्रकार len)
अणु
	add_key_to_revocation_list(data, len);
पूर्ण

/*
 * Return the appropriate handler क्रम particular signature list types found in
 * the UEFI db and MokListRT tables.
 */
__init efi_element_handler_t get_handler_क्रम_db(स्थिर efi_guid_t *sig_type)
अणु
	अगर (efi_guidcmp(*sig_type, efi_cert_x509_guid) == 0)
		वापस add_to_platक्रमm_keyring;
	वापस 0;
पूर्ण

/*
 * Return the appropriate handler क्रम particular signature list types found in
 * the UEFI dbx and MokListXRT tables.
 */
__init efi_element_handler_t get_handler_क्रम_dbx(स्थिर efi_guid_t *sig_type)
अणु
	अगर (efi_guidcmp(*sig_type, efi_cert_x509_sha256_guid) == 0)
		वापस uefi_blacklist_x509_tbs;
	अगर (efi_guidcmp(*sig_type, efi_cert_sha256_guid) == 0)
		वापस uefi_blacklist_binary;
	अगर (efi_guidcmp(*sig_type, efi_cert_x509_guid) == 0)
		वापस uefi_revocation_list_x509;
	वापस 0;
पूर्ण
