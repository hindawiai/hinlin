<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Authenc: Simple AEAD wrapper क्रम IPsec
 *
 * Copyright (c) 2007 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */
#अगर_अघोषित _CRYPTO_AUTHENC_H
#घोषणा _CRYPTO_AUTHENC_H

#समावेश <linux/types.h>

क्रमागत अणु
	CRYPTO_AUTHENC_KEYA_UNSPEC,
	CRYPTO_AUTHENC_KEYA_PARAM,
पूर्ण;

काष्ठा crypto_authenc_key_param अणु
	__be32 enckeylen;
पूर्ण;

काष्ठा crypto_authenc_keys अणु
	स्थिर u8 *authkey;
	स्थिर u8 *enckey;

	अचिन्हित पूर्णांक authkeylen;
	अचिन्हित पूर्णांक enckeylen;
पूर्ण;

पूर्णांक crypto_authenc_extractkeys(काष्ठा crypto_authenc_keys *keys, स्थिर u8 *key,
			       अचिन्हित पूर्णांक keylen);

#पूर्ण_अगर	/* _CRYPTO_AUTHENC_H */
