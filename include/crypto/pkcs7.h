<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* PKCS#7 crypto data parser
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _CRYPTO_PKCS7_H
#घोषणा _CRYPTO_PKCS7_H

#समावेश <linux/verअगरication.h>
#समावेश <linux/hash_info.h>
#समावेश <crypto/खुला_key.h>

काष्ठा key;
काष्ठा pkcs7_message;

/*
 * pkcs7_parser.c
 */
बाह्य काष्ठा pkcs7_message *pkcs7_parse_message(स्थिर व्योम *data,
						 माप_प्रकार datalen);
बाह्य व्योम pkcs7_मुक्त_message(काष्ठा pkcs7_message *pkcs7);

बाह्य पूर्णांक pkcs7_get_content_data(स्थिर काष्ठा pkcs7_message *pkcs7,
				  स्थिर व्योम **_data, माप_प्रकार *_datalen,
				  माप_प्रकार *_headerlen);

/*
 * pkcs7_trust.c
 */
बाह्य पूर्णांक pkcs7_validate_trust(काष्ठा pkcs7_message *pkcs7,
				काष्ठा key *trust_keyring);

/*
 * pkcs7_verअगरy.c
 */
बाह्य पूर्णांक pkcs7_verअगरy(काष्ठा pkcs7_message *pkcs7,
			क्रमागत key_being_used_क्रम usage);

बाह्य पूर्णांक pkcs7_supply_detached_data(काष्ठा pkcs7_message *pkcs7,
				      स्थिर व्योम *data, माप_प्रकार datalen);

बाह्य पूर्णांक pkcs7_get_digest(काष्ठा pkcs7_message *pkcs7, स्थिर u8 **buf,
			    u32 *len, क्रमागत hash_algo *hash_algo);

#पूर्ण_अगर /* _CRYPTO_PKCS7_H */
