<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _CRYPTO_INTERNAL_CHACHA_H
#घोषणा _CRYPTO_INTERNAL_CHACHA_H

#समावेश <crypto/chacha.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/crypto.h>

काष्ठा chacha_ctx अणु
	u32 key[8];
	पूर्णांक nrounds;
पूर्ण;

अटल अंतरभूत पूर्णांक chacha_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				अचिन्हित पूर्णांक keysize, पूर्णांक nrounds)
अणु
	काष्ठा chacha_ctx *ctx = crypto_skcipher_ctx(tfm);
	पूर्णांक i;

	अगर (keysize != CHACHA_KEY_SIZE)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(ctx->key); i++)
		ctx->key[i] = get_unaligned_le32(key + i * माप(u32));

	ctx->nrounds = nrounds;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक chacha20_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				  अचिन्हित पूर्णांक keysize)
अणु
	वापस chacha_setkey(tfm, key, keysize, 20);
पूर्ण

अटल अंतरभूत पूर्णांक chacha12_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				  अचिन्हित पूर्णांक keysize)
अणु
	वापस chacha_setkey(tfm, key, keysize, 12);
पूर्ण

#पूर्ण_अगर /* _CRYPTO_CHACHA_H */
