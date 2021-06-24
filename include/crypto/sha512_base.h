<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * sha512_base.h - core logic क्रम SHA-512 implementations
 *
 * Copyright (C) 2015 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#अगर_अघोषित _CRYPTO_SHA512_BASE_H
#घोषणा _CRYPTO_SHA512_BASE_H

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/sha2.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/unaligned.h>

प्रकार व्योम (sha512_block_fn)(काष्ठा sha512_state *sst, u8 स्थिर *src,
			       पूर्णांक blocks);

अटल अंतरभूत पूर्णांक sha384_base_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA384_H0;
	sctx->state[1] = SHA384_H1;
	sctx->state[2] = SHA384_H2;
	sctx->state[3] = SHA384_H3;
	sctx->state[4] = SHA384_H4;
	sctx->state[5] = SHA384_H5;
	sctx->state[6] = SHA384_H6;
	sctx->state[7] = SHA384_H7;
	sctx->count[0] = sctx->count[1] = 0;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sha512_base_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA512_H0;
	sctx->state[1] = SHA512_H1;
	sctx->state[2] = SHA512_H2;
	sctx->state[3] = SHA512_H3;
	sctx->state[4] = SHA512_H4;
	sctx->state[5] = SHA512_H5;
	sctx->state[6] = SHA512_H6;
	sctx->state[7] = SHA512_H7;
	sctx->count[0] = sctx->count[1] = 0;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sha512_base_करो_update(काष्ठा shash_desc *desc,
					स्थिर u8 *data,
					अचिन्हित पूर्णांक len,
					sha512_block_fn *block_fn)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial = sctx->count[0] % SHA512_BLOCK_SIZE;

	sctx->count[0] += len;
	अगर (sctx->count[0] < len)
		sctx->count[1]++;

	अगर (unlikely((partial + len) >= SHA512_BLOCK_SIZE)) अणु
		पूर्णांक blocks;

		अगर (partial) अणु
			पूर्णांक p = SHA512_BLOCK_SIZE - partial;

			स_नकल(sctx->buf + partial, data, p);
			data += p;
			len -= p;

			block_fn(sctx, sctx->buf, 1);
		पूर्ण

		blocks = len / SHA512_BLOCK_SIZE;
		len %= SHA512_BLOCK_SIZE;

		अगर (blocks) अणु
			block_fn(sctx, data, blocks);
			data += blocks * SHA512_BLOCK_SIZE;
		पूर्ण
		partial = 0;
	पूर्ण
	अगर (len)
		स_नकल(sctx->buf + partial, data, len);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sha512_base_करो_finalize(काष्ठा shash_desc *desc,
					  sha512_block_fn *block_fn)
अणु
	स्थिर पूर्णांक bit_offset = SHA512_BLOCK_SIZE - माप(__be64[2]);
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);
	__be64 *bits = (__be64 *)(sctx->buf + bit_offset);
	अचिन्हित पूर्णांक partial = sctx->count[0] % SHA512_BLOCK_SIZE;

	sctx->buf[partial++] = 0x80;
	अगर (partial > bit_offset) अणु
		स_रखो(sctx->buf + partial, 0x0, SHA512_BLOCK_SIZE - partial);
		partial = 0;

		block_fn(sctx, sctx->buf, 1);
	पूर्ण

	स_रखो(sctx->buf + partial, 0x0, bit_offset - partial);
	bits[0] = cpu_to_be64(sctx->count[1] << 3 | sctx->count[0] >> 61);
	bits[1] = cpu_to_be64(sctx->count[0] << 3);
	block_fn(sctx, sctx->buf, 1);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sha512_base_finish(काष्ठा shash_desc *desc, u8 *out)
अणु
	अचिन्हित पूर्णांक digest_size = crypto_shash_digestsize(desc->tfm);
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);
	__be64 *digest = (__be64 *)out;
	पूर्णांक i;

	क्रम (i = 0; digest_size > 0; i++, digest_size -= माप(__be64))
		put_unaligned_be64(sctx->state[i], digest++);

	memzero_explicit(sctx, माप(*sctx));
	वापस 0;
पूर्ण

#पूर्ण_अगर /* _CRYPTO_SHA512_BASE_H */
