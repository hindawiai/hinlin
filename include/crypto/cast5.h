<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CRYPTO_CAST5_H
#घोषणा _CRYPTO_CAST5_H

#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/cast_common.h>

#घोषणा CAST5_BLOCK_SIZE 8
#घोषणा CAST5_MIN_KEY_SIZE 5
#घोषणा CAST5_MAX_KEY_SIZE 16

काष्ठा cast5_ctx अणु
	u32 Km[16];
	u8 Kr[16];
	पूर्णांक rr;	/* rr ? rounds = 12 : rounds = 16; (rfc 2144) */
पूर्ण;

पूर्णांक cast5_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *key, अचिन्हित पूर्णांक keylen);

व्योम __cast5_encrypt(काष्ठा cast5_ctx *ctx, u8 *dst, स्थिर u8 *src);
व्योम __cast5_decrypt(काष्ठा cast5_ctx *ctx, u8 *dst, स्थिर u8 *src);

#पूर्ण_अगर
