<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common values क्रम SHA-1 algorithms
 */

#अगर_अघोषित _CRYPTO_SHA1_H
#घोषणा _CRYPTO_SHA1_H

#समावेश <linux/types.h>

#घोषणा SHA1_DIGEST_SIZE        20
#घोषणा SHA1_BLOCK_SIZE         64

#घोषणा SHA1_H0		0x67452301UL
#घोषणा SHA1_H1		0xefcdab89UL
#घोषणा SHA1_H2		0x98badcfeUL
#घोषणा SHA1_H3		0x10325476UL
#घोषणा SHA1_H4		0xc3d2e1f0UL

बाह्य स्थिर u8 sha1_zero_message_hash[SHA1_DIGEST_SIZE];

काष्ठा sha1_state अणु
	u32 state[SHA1_DIGEST_SIZE / 4];
	u64 count;
	u8 buffer[SHA1_BLOCK_SIZE];
पूर्ण;

काष्ठा shash_desc;

बाह्य पूर्णांक crypto_sha1_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len);

बाह्य पूर्णांक crypto_sha1_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			     अचिन्हित पूर्णांक len, u8 *hash);

/*
 * An implementation of SHA-1's compression function.  Don't use in new code!
 * You shouldn't be using SHA-1, and even if you *have* to use SHA-1, this isn't
 * the correct way to hash something with SHA-1 (use crypto_shash instead).
 */
#घोषणा SHA1_DIGEST_WORDS	(SHA1_DIGEST_SIZE / 4)
#घोषणा SHA1_WORKSPACE_WORDS	16
व्योम sha1_init(__u32 *buf);
व्योम sha1_transक्रमm(__u32 *digest, स्थिर अक्षर *data, __u32 *W);

#पूर्ण_अगर /* _CRYPTO_SHA1_H */
