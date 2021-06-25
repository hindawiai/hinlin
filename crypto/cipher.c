<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * Single-block cipher operations.
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2005 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <linux/kernel.h>
#समावेश <linux/crypto.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश "internal.h"

अटल पूर्णांक setkey_unaligned(काष्ठा crypto_cipher *tfm, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cipher_alg *cia = crypto_cipher_alg(tfm);
	अचिन्हित दीर्घ alignmask = crypto_cipher_alignmask(tfm);
	पूर्णांक ret;
	u8 *buffer, *alignbuffer;
	अचिन्हित दीर्घ असलize;

	असलize = keylen + alignmask;
	buffer = kदो_स्मृति(असलize, GFP_ATOMIC);
	अगर (!buffer)
		वापस -ENOMEM;

	alignbuffer = (u8 *)ALIGN((अचिन्हित दीर्घ)buffer, alignmask + 1);
	स_नकल(alignbuffer, key, keylen);
	ret = cia->cia_setkey(crypto_cipher_tfm(tfm), alignbuffer, keylen);
	स_रखो(alignbuffer, 0, keylen);
	kमुक्त(buffer);
	वापस ret;

पूर्ण

पूर्णांक crypto_cipher_setkey(काष्ठा crypto_cipher *tfm,
			 स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cipher_alg *cia = crypto_cipher_alg(tfm);
	अचिन्हित दीर्घ alignmask = crypto_cipher_alignmask(tfm);

	अगर (keylen < cia->cia_min_keysize || keylen > cia->cia_max_keysize)
		वापस -EINVAL;

	अगर ((अचिन्हित दीर्घ)key & alignmask)
		वापस setkey_unaligned(tfm, key, keylen);

	वापस cia->cia_setkey(crypto_cipher_tfm(tfm), key, keylen);
पूर्ण
EXPORT_SYMBOL_NS_GPL(crypto_cipher_setkey, CRYPTO_INTERNAL);

अटल अंतरभूत व्योम cipher_crypt_one(काष्ठा crypto_cipher *tfm,
				    u8 *dst, स्थिर u8 *src, bool enc)
अणु
	अचिन्हित दीर्घ alignmask = crypto_cipher_alignmask(tfm);
	काष्ठा cipher_alg *cia = crypto_cipher_alg(tfm);
	व्योम (*fn)(काष्ठा crypto_tfm *, u8 *, स्थिर u8 *) =
		enc ? cia->cia_encrypt : cia->cia_decrypt;

	अगर (unlikely(((अचिन्हित दीर्घ)dst | (अचिन्हित दीर्घ)src) & alignmask)) अणु
		अचिन्हित पूर्णांक bs = crypto_cipher_blocksize(tfm);
		u8 buffer[MAX_CIPHER_BLOCKSIZE + MAX_CIPHER_ALIGNMASK];
		u8 *पंचांगp = (u8 *)ALIGN((अचिन्हित दीर्घ)buffer, alignmask + 1);

		स_नकल(पंचांगp, src, bs);
		fn(crypto_cipher_tfm(tfm), पंचांगp, पंचांगp);
		स_नकल(dst, पंचांगp, bs);
	पूर्ण अन्यथा अणु
		fn(crypto_cipher_tfm(tfm), dst, src);
	पूर्ण
पूर्ण

व्योम crypto_cipher_encrypt_one(काष्ठा crypto_cipher *tfm,
			       u8 *dst, स्थिर u8 *src)
अणु
	cipher_crypt_one(tfm, dst, src, true);
पूर्ण
EXPORT_SYMBOL_NS_GPL(crypto_cipher_encrypt_one, CRYPTO_INTERNAL);

व्योम crypto_cipher_decrypt_one(काष्ठा crypto_cipher *tfm,
			       u8 *dst, स्थिर u8 *src)
अणु
	cipher_crypt_one(tfm, dst, src, false);
पूर्ण
EXPORT_SYMBOL_NS_GPL(crypto_cipher_decrypt_one, CRYPTO_INTERNAL);
