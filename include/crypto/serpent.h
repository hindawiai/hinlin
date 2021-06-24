<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common values क्रम serpent algorithms
 */

#अगर_अघोषित _CRYPTO_SERPENT_H
#घोषणा _CRYPTO_SERPENT_H

#समावेश <linux/types.h>
#समावेश <linux/crypto.h>

#घोषणा SERPENT_MIN_KEY_SIZE		  0
#घोषणा SERPENT_MAX_KEY_SIZE		 32
#घोषणा SERPENT_EXPKEY_WORDS		132
#घोषणा SERPENT_BLOCK_SIZE		 16

काष्ठा serpent_ctx अणु
	u32 expkey[SERPENT_EXPKEY_WORDS];
पूर्ण;

पूर्णांक __serpent_setkey(काष्ठा serpent_ctx *ctx, स्थिर u8 *key,
		     अचिन्हित पूर्णांक keylen);
पूर्णांक serpent_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *key, अचिन्हित पूर्णांक keylen);

व्योम __serpent_encrypt(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);
व्योम __serpent_decrypt(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);

#पूर्ण_अगर
