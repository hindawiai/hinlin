<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Asymmetric खुला-key algorithm definitions
 *
 * See Documentation/crypto/asymmetric-keys.rst
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _LINUX_PUBLIC_KEY_H
#घोषणा _LINUX_PUBLIC_KEY_H

#समावेश <linux/keyctl.h>
#समावेश <linux/oid_registry.h>

/*
 * Cryptographic data क्रम the खुला-key subtype of the asymmetric key type.
 *
 * Note that this may include निजी part of the key as well as the खुला
 * part.
 */
काष्ठा खुला_key अणु
	व्योम *key;
	u32 keylen;
	क्रमागत OID algo;
	व्योम *params;
	u32 paramlen;
	bool key_is_निजी;
	स्थिर अक्षर *id_type;
	स्थिर अक्षर *pkey_algo;
पूर्ण;

बाह्य व्योम खुला_key_मुक्त(काष्ठा खुला_key *key);

/*
 * Public key cryptography signature data
 */
काष्ठा खुला_key_signature अणु
	काष्ठा asymmetric_key_id *auth_ids[2];
	u8 *s;			/* Signature */
	u32 s_size;		/* Number of bytes in signature */
	u8 *digest;
	u8 digest_size;		/* Number of bytes in digest */
	स्थिर अक्षर *pkey_algo;
	स्थिर अक्षर *hash_algo;
	स्थिर अक्षर *encoding;
	स्थिर व्योम *data;
	अचिन्हित पूर्णांक data_size;
पूर्ण;

बाह्य व्योम खुला_key_signature_मुक्त(काष्ठा खुला_key_signature *sig);

बाह्य काष्ठा asymmetric_key_subtype खुला_key_subtype;

काष्ठा key;
काष्ठा key_type;
जोड़ key_payload;

बाह्य पूर्णांक restrict_link_by_signature(काष्ठा key *dest_keyring,
				      स्थिर काष्ठा key_type *type,
				      स्थिर जोड़ key_payload *payload,
				      काष्ठा key *trust_keyring);

बाह्य पूर्णांक restrict_link_by_key_or_keyring(काष्ठा key *dest_keyring,
					   स्थिर काष्ठा key_type *type,
					   स्थिर जोड़ key_payload *payload,
					   काष्ठा key *trusted);

बाह्य पूर्णांक restrict_link_by_key_or_keyring_chain(काष्ठा key *trust_keyring,
						 स्थिर काष्ठा key_type *type,
						 स्थिर जोड़ key_payload *payload,
						 काष्ठा key *trusted);

बाह्य पूर्णांक query_asymmetric_key(स्थिर काष्ठा kernel_pkey_params *,
				काष्ठा kernel_pkey_query *);

बाह्य पूर्णांक encrypt_blob(काष्ठा kernel_pkey_params *, स्थिर व्योम *, व्योम *);
बाह्य पूर्णांक decrypt_blob(काष्ठा kernel_pkey_params *, स्थिर व्योम *, व्योम *);
बाह्य पूर्णांक create_signature(काष्ठा kernel_pkey_params *, स्थिर व्योम *, व्योम *);
बाह्य पूर्णांक verअगरy_signature(स्थिर काष्ठा key *,
			    स्थिर काष्ठा खुला_key_signature *);

पूर्णांक खुला_key_verअगरy_signature(स्थिर काष्ठा खुला_key *pkey,
				स्थिर काष्ठा खुला_key_signature *sig);

#पूर्ण_अगर /* _LINUX_PUBLIC_KEY_H */
