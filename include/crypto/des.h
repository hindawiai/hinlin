<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * DES & Triple DES EDE Cipher Algorithms.
 */

#अगर_अघोषित __CRYPTO_DES_H
#घोषणा __CRYPTO_DES_H

#समावेश <linux/types.h>

#घोषणा DES_KEY_SIZE		8
#घोषणा DES_EXPKEY_WORDS	32
#घोषणा DES_BLOCK_SIZE		8

#घोषणा DES3_EDE_KEY_SIZE	(3 * DES_KEY_SIZE)
#घोषणा DES3_EDE_EXPKEY_WORDS	(3 * DES_EXPKEY_WORDS)
#घोषणा DES3_EDE_BLOCK_SIZE	DES_BLOCK_SIZE

काष्ठा des_ctx अणु
	u32 expkey[DES_EXPKEY_WORDS];
पूर्ण;

काष्ठा des3_ede_ctx अणु
	u32 expkey[DES3_EDE_EXPKEY_WORDS];
पूर्ण;

व्योम des_encrypt(स्थिर काष्ठा des_ctx *ctx, u8 *dst, स्थिर u8 *src);
व्योम des_decrypt(स्थिर काष्ठा des_ctx *ctx, u8 *dst, स्थिर u8 *src);

व्योम des3_ede_encrypt(स्थिर काष्ठा des3_ede_ctx *dctx, u8 *dst, स्थिर u8 *src);
व्योम des3_ede_decrypt(स्थिर काष्ठा des3_ede_ctx *dctx, u8 *dst, स्थिर u8 *src);

/**
 * des_expand_key - Expand a DES input key पूर्णांकo a key schedule
 * @ctx: the key schedule
 * @key: buffer containing the input key
 * @len: size of the buffer contents
 *
 * Returns 0 on success, -EINVAL अगर the input key is rejected and -ENOKEY अगर
 * the key is accepted but has been found to be weak.
 */
पूर्णांक des_expand_key(काष्ठा des_ctx *ctx, स्थिर u8 *key, अचिन्हित पूर्णांक keylen);

/**
 * des3_ede_expand_key - Expand a triple DES input key पूर्णांकo a key schedule
 * @ctx: the key schedule
 * @key: buffer containing the input key
 * @len: size of the buffer contents
 *
 * Returns 0 on success, -EINVAL अगर the input key is rejected and -ENOKEY अगर
 * the key is accepted but has been found to be weak. Note that weak keys will
 * be rejected (and -EINVAL will be वापसed) when running in FIPS mode.
 */
पूर्णांक des3_ede_expand_key(काष्ठा des3_ede_ctx *ctx, स्थिर u8 *key,
			अचिन्हित पूर्णांक keylen);

#पूर्ण_अगर /* __CRYPTO_DES_H */
