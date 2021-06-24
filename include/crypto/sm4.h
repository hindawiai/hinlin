<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * Common values क्रम the SM4 algorithm
 * Copyright (C) 2018 ARM Limited or its affiliates.
 */

#अगर_अघोषित _CRYPTO_SM4_H
#घोषणा _CRYPTO_SM4_H

#समावेश <linux/types.h>
#समावेश <linux/crypto.h>

#घोषणा SM4_KEY_SIZE	16
#घोषणा SM4_BLOCK_SIZE	16
#घोषणा SM4_RKEY_WORDS	32

काष्ठा crypto_sm4_ctx अणु
	u32 rkey_enc[SM4_RKEY_WORDS];
	u32 rkey_dec[SM4_RKEY_WORDS];
पूर्ण;

पूर्णांक crypto_sm4_set_key(काष्ठा crypto_tfm *tfm, स्थिर u8 *in_key,
		       अचिन्हित पूर्णांक key_len);
पूर्णांक crypto_sm4_expand_key(काष्ठा crypto_sm4_ctx *ctx, स्थिर u8 *in_key,
			  अचिन्हित पूर्णांक key_len);

व्योम crypto_sm4_encrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in);
व्योम crypto_sm4_decrypt(काष्ठा crypto_tfm *tfm, u8 *out, स्थिर u8 *in);

#पूर्ण_अगर
