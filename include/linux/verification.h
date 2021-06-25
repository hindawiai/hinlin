<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Signature verअगरication
 *
 * Copyright (C) 2014 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _LINUX_VERIFICATION_H
#घोषणा _LINUX_VERIFICATION_H

#समावेश <linux/types.h>

/*
 * Indicate that both builtin trusted keys and secondary trusted keys
 * should be used.
 */
#घोषणा VERIFY_USE_SECONDARY_KEYRING ((काष्ठा key *)1UL)
#घोषणा VERIFY_USE_PLATFORM_KEYRING  ((काष्ठा key *)2UL)

/*
 * The use to which an asymmetric key is being put.
 */
क्रमागत key_being_used_क्रम अणु
	VERIFYING_MODULE_SIGNATURE,
	VERIFYING_FIRMWARE_SIGNATURE,
	VERIFYING_KEXEC_PE_SIGNATURE,
	VERIFYING_KEY_SIGNATURE,
	VERIFYING_KEY_SELF_SIGNATURE,
	VERIFYING_UNSPECIFIED_SIGNATURE,
	NR__KEY_BEING_USED_FOR
पूर्ण;
बाह्य स्थिर अक्षर *स्थिर key_being_used_क्रम[NR__KEY_BEING_USED_FOR];

#अगर_घोषित CONFIG_SYSTEM_DATA_VERIFICATION

काष्ठा key;
काष्ठा pkcs7_message;

बाह्य पूर्णांक verअगरy_pkcs7_signature(स्थिर व्योम *data, माप_प्रकार len,
				  स्थिर व्योम *raw_pkcs7, माप_प्रकार pkcs7_len,
				  काष्ठा key *trusted_keys,
				  क्रमागत key_being_used_क्रम usage,
				  पूर्णांक (*view_content)(व्योम *ctx,
						      स्थिर व्योम *data, माप_प्रकार len,
						      माप_प्रकार asn1hdrlen),
				  व्योम *ctx);
बाह्य पूर्णांक verअगरy_pkcs7_message_sig(स्थिर व्योम *data, माप_प्रकार len,
				    काष्ठा pkcs7_message *pkcs7,
				    काष्ठा key *trusted_keys,
				    क्रमागत key_being_used_क्रम usage,
				    पूर्णांक (*view_content)(व्योम *ctx,
							स्थिर व्योम *data,
							माप_प्रकार len,
							माप_प्रकार asn1hdrlen),
				    व्योम *ctx);

#अगर_घोषित CONFIG_SIGNED_PE_खाता_VERIFICATION
बाह्य पूर्णांक verअगरy_pefile_signature(स्थिर व्योम *pebuf, अचिन्हित pelen,
				   काष्ठा key *trusted_keys,
				   क्रमागत key_being_used_क्रम usage);
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_SYSTEM_DATA_VERIFICATION */
#पूर्ण_अगर /* _LINUX_VERIFY_PEखाता_H */
