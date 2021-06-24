<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common values क्रम the GHASH hash function
 */

#अगर_अघोषित __CRYPTO_GHASH_H__
#घोषणा __CRYPTO_GHASH_H__

#समावेश <linux/types.h>
#समावेश <crypto/gf128mul.h>

#घोषणा GHASH_BLOCK_SIZE	16
#घोषणा GHASH_DIGEST_SIZE	16

काष्ठा ghash_ctx अणु
	काष्ठा gf128mul_4k *gf128;
पूर्ण;

काष्ठा ghash_desc_ctx अणु
	u8 buffer[GHASH_BLOCK_SIZE];
	u32 bytes;
पूर्ण;

#पूर्ण_अगर
