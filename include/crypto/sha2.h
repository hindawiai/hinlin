<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common values क्रम SHA-2 algorithms
 */

#अगर_अघोषित _CRYPTO_SHA2_H
#घोषणा _CRYPTO_SHA2_H

#समावेश <linux/types.h>

#घोषणा SHA224_DIGEST_SIZE	28
#घोषणा SHA224_BLOCK_SIZE	64

#घोषणा SHA256_DIGEST_SIZE      32
#घोषणा SHA256_BLOCK_SIZE       64

#घोषणा SHA384_DIGEST_SIZE      48
#घोषणा SHA384_BLOCK_SIZE       128

#घोषणा SHA512_DIGEST_SIZE      64
#घोषणा SHA512_BLOCK_SIZE       128

#घोषणा SHA224_H0	0xc1059ed8UL
#घोषणा SHA224_H1	0x367cd507UL
#घोषणा SHA224_H2	0x3070dd17UL
#घोषणा SHA224_H3	0xf70e5939UL
#घोषणा SHA224_H4	0xffc00b31UL
#घोषणा SHA224_H5	0x68581511UL
#घोषणा SHA224_H6	0x64f98fa7UL
#घोषणा SHA224_H7	0xbefa4fa4UL

#घोषणा SHA256_H0	0x6a09e667UL
#घोषणा SHA256_H1	0xbb67ae85UL
#घोषणा SHA256_H2	0x3c6ef372UL
#घोषणा SHA256_H3	0xa54ff53aUL
#घोषणा SHA256_H4	0x510e527fUL
#घोषणा SHA256_H5	0x9b05688cUL
#घोषणा SHA256_H6	0x1f83d9abUL
#घोषणा SHA256_H7	0x5be0cd19UL

#घोषणा SHA384_H0	0xcbbb9d5dc1059ed8ULL
#घोषणा SHA384_H1	0x629a292a367cd507ULL
#घोषणा SHA384_H2	0x9159015a3070dd17ULL
#घोषणा SHA384_H3	0x152fecd8f70e5939ULL
#घोषणा SHA384_H4	0x67332667ffc00b31ULL
#घोषणा SHA384_H5	0x8eb44a8768581511ULL
#घोषणा SHA384_H6	0xdb0c2e0d64f98fa7ULL
#घोषणा SHA384_H7	0x47b5481dbefa4fa4ULL

#घोषणा SHA512_H0	0x6a09e667f3bcc908ULL
#घोषणा SHA512_H1	0xbb67ae8584caa73bULL
#घोषणा SHA512_H2	0x3c6ef372fe94f82bULL
#घोषणा SHA512_H3	0xa54ff53a5f1d36f1ULL
#घोषणा SHA512_H4	0x510e527fade682d1ULL
#घोषणा SHA512_H5	0x9b05688c2b3e6c1fULL
#घोषणा SHA512_H6	0x1f83d9abfb41bd6bULL
#घोषणा SHA512_H7	0x5be0cd19137e2179ULL

बाह्य स्थिर u8 sha224_zero_message_hash[SHA224_DIGEST_SIZE];

बाह्य स्थिर u8 sha256_zero_message_hash[SHA256_DIGEST_SIZE];

बाह्य स्थिर u8 sha384_zero_message_hash[SHA384_DIGEST_SIZE];

बाह्य स्थिर u8 sha512_zero_message_hash[SHA512_DIGEST_SIZE];

काष्ठा sha256_state अणु
	u32 state[SHA256_DIGEST_SIZE / 4];
	u64 count;
	u8 buf[SHA256_BLOCK_SIZE];
पूर्ण;

काष्ठा sha512_state अणु
	u64 state[SHA512_DIGEST_SIZE / 8];
	u64 count[2];
	u8 buf[SHA512_BLOCK_SIZE];
पूर्ण;

काष्ठा shash_desc;

बाह्य पूर्णांक crypto_sha256_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len);

बाह्य पूर्णांक crypto_sha256_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक len, u8 *hash);

बाह्य पूर्णांक crypto_sha512_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len);

बाह्य पूर्णांक crypto_sha512_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			       अचिन्हित पूर्णांक len, u8 *hash);

/*
 * Stand-alone implementation of the SHA256 algorithm. It is deचिन्हित to
 * have as little dependencies as possible so it can be used in the
 * kexec_file purgatory. In other हालs you should generally use the
 * hash APIs from include/crypto/hash.h. Especially when hashing large
 * amounts of data as those APIs may be hw-accelerated.
 *
 * For details see lib/crypto/sha256.c
 */

अटल अंतरभूत व्योम sha256_init(काष्ठा sha256_state *sctx)
अणु
	sctx->state[0] = SHA256_H0;
	sctx->state[1] = SHA256_H1;
	sctx->state[2] = SHA256_H2;
	sctx->state[3] = SHA256_H3;
	sctx->state[4] = SHA256_H4;
	sctx->state[5] = SHA256_H5;
	sctx->state[6] = SHA256_H6;
	sctx->state[7] = SHA256_H7;
	sctx->count = 0;
पूर्ण
व्योम sha256_update(काष्ठा sha256_state *sctx, स्थिर u8 *data, अचिन्हित पूर्णांक len);
व्योम sha256_final(काष्ठा sha256_state *sctx, u8 *out);
व्योम sha256(स्थिर u8 *data, अचिन्हित पूर्णांक len, u8 *out);

अटल अंतरभूत व्योम sha224_init(काष्ठा sha256_state *sctx)
अणु
	sctx->state[0] = SHA224_H0;
	sctx->state[1] = SHA224_H1;
	sctx->state[2] = SHA224_H2;
	sctx->state[3] = SHA224_H3;
	sctx->state[4] = SHA224_H4;
	sctx->state[5] = SHA224_H5;
	sctx->state[6] = SHA224_H6;
	sctx->state[7] = SHA224_H7;
	sctx->count = 0;
पूर्ण
व्योम sha224_update(काष्ठा sha256_state *sctx, स्थिर u8 *data, अचिन्हित पूर्णांक len);
व्योम sha224_final(काष्ठा sha256_state *sctx, u8 *out);

#पूर्ण_अगर /* _CRYPTO_SHA2_H */
