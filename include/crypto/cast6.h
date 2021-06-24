<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CRYPTO_CAST6_H
#घोषणा _CRYPTO_CAST6_H

#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/cast_common.h>

#घोषणा CAST6_BLOCK_SIZE 16
#घोषणा CAST6_MIN_KEY_SIZE 16
#घोषणा CAST6_MAX_KEY_SIZE 32

काष्ठा cast6_ctx अणु
	u32 Km[12][4];
	u8 Kr[12][4];
पूर्ण;

पूर्णांक __cast6_setkey(काष्ठा cast6_ctx *ctx, स्थिर u8 *key, अचिन्हित पूर्णांक keylen);
पूर्णांक cast6_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *key, अचिन्हित पूर्णांक keylen);

व्योम __cast6_encrypt(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);
व्योम __cast6_decrypt(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);

#पूर्ण_अगर
