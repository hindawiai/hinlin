<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित PLATFORM_CERTS_INTERNAL_H
#घोषणा PLATFORM_CERTS_INTERNAL_H

#समावेश <linux/efi.h>

व्योम blacklist_hash(स्थिर अक्षर *source, स्थिर व्योम *data,
		    माप_प्रकार len, स्थिर अक्षर *type,
		    माप_प्रकार type_len);

/*
 * Blacklist an X509 TBS hash.
 */
व्योम blacklist_x509_tbs(स्थिर अक्षर *source, स्थिर व्योम *data, माप_प्रकार len);

/*
 * Blacklist the hash of an executable.
 */
व्योम blacklist_binary(स्थिर अक्षर *source, स्थिर व्योम *data, माप_प्रकार len);

/*
 * Return the handler क्रम particular signature list types found in the db.
 */
efi_element_handler_t get_handler_क्रम_db(स्थिर efi_guid_t *sig_type);

/*
 * Return the handler क्रम particular signature list types found in the dbx.
 */
efi_element_handler_t get_handler_क्रम_dbx(स्थिर efi_guid_t *sig_type);

#पूर्ण_अगर
