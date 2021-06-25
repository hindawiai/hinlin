<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common values क्रम blowfish algorithms
 */

#अगर_अघोषित _CRYPTO_BLOWFISH_H
#घोषणा _CRYPTO_BLOWFISH_H

#समावेश <linux/types.h>
#समावेश <linux/crypto.h>

#घोषणा BF_BLOCK_SIZE 8
#घोषणा BF_MIN_KEY_SIZE 4
#घोषणा BF_MAX_KEY_SIZE 56

काष्ठा bf_ctx अणु
	u32 p[18];
	u32 s[1024];
पूर्ण;

पूर्णांक blowfish_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *key,
		    अचिन्हित पूर्णांक key_len);

#पूर्ण_अगर
