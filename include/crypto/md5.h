<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CRYPTO_MD5_H
#घोषणा _CRYPTO_MD5_H

#समावेश <linux/types.h>

#घोषणा MD5_DIGEST_SIZE		16
#घोषणा MD5_HMAC_BLOCK_SIZE	64
#घोषणा MD5_BLOCK_WORDS		16
#घोषणा MD5_HASH_WORDS		4

#घोषणा MD5_H0	0x67452301UL
#घोषणा MD5_H1	0xefcdab89UL
#घोषणा MD5_H2	0x98badcfeUL
#घोषणा MD5_H3	0x10325476UL

बाह्य स्थिर u8 md5_zero_message_hash[MD5_DIGEST_SIZE];

काष्ठा md5_state अणु
	u32 hash[MD5_HASH_WORDS];
	u32 block[MD5_BLOCK_WORDS];
	u64 byte_count;
पूर्ण;

#पूर्ण_अगर
