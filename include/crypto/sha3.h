<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common values क्रम SHA-3 algorithms
 */
#अगर_अघोषित __CRYPTO_SHA3_H__
#घोषणा __CRYPTO_SHA3_H__

#घोषणा SHA3_224_DIGEST_SIZE	(224 / 8)
#घोषणा SHA3_224_BLOCK_SIZE	(200 - 2 * SHA3_224_DIGEST_SIZE)

#घोषणा SHA3_256_DIGEST_SIZE	(256 / 8)
#घोषणा SHA3_256_BLOCK_SIZE	(200 - 2 * SHA3_256_DIGEST_SIZE)

#घोषणा SHA3_384_DIGEST_SIZE	(384 / 8)
#घोषणा SHA3_384_BLOCK_SIZE	(200 - 2 * SHA3_384_DIGEST_SIZE)

#घोषणा SHA3_512_DIGEST_SIZE	(512 / 8)
#घोषणा SHA3_512_BLOCK_SIZE	(200 - 2 * SHA3_512_DIGEST_SIZE)

काष्ठा sha3_state अणु
	u64		st[25];
	अचिन्हित पूर्णांक	rsiz;
	अचिन्हित पूर्णांक	rsizw;

	अचिन्हित पूर्णांक	partial;
	u8		buf[SHA3_224_BLOCK_SIZE];
पूर्ण;

पूर्णांक crypto_sha3_init(काष्ठा shash_desc *desc);
पूर्णांक crypto_sha3_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
		       अचिन्हित पूर्णांक len);
पूर्णांक crypto_sha3_final(काष्ठा shash_desc *desc, u8 *out);

#पूर्ण_अगर
