<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Common values क्रम ARC4 Cipher Algorithm
 */

#अगर_अघोषित _CRYPTO_ARC4_H
#घोषणा _CRYPTO_ARC4_H

#समावेश <linux/types.h>

#घोषणा ARC4_MIN_KEY_SIZE	1
#घोषणा ARC4_MAX_KEY_SIZE	256
#घोषणा ARC4_BLOCK_SIZE		1

काष्ठा arc4_ctx अणु
	u32 S[256];
	u32 x, y;
पूर्ण;

पूर्णांक arc4_setkey(काष्ठा arc4_ctx *ctx, स्थिर u8 *in_key, अचिन्हित पूर्णांक key_len);
व्योम arc4_crypt(काष्ठा arc4_ctx *ctx, u8 *out, स्थिर u8 *in, अचिन्हित पूर्णांक len);

#पूर्ण_अगर /* _CRYPTO_ARC4_H */
