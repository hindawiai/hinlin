<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * sha1_base.h - core logic क्रम SHA-1 implementations
 *
 * Copyright (C) 2015 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#अगर_अघोषित _CRYPTO_SHA1_BASE_H
#घोषणा _CRYPTO_SHA1_BASE_H

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/sha1.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/unaligned.h>

प्रकार व्योम (sha1_block_fn)(काष्ठा sha1_state *sst, u8 स्थिर *src, पूर्णांक blocks);

अटल अंतरभूत पूर्णांक sha1_base_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA1_H0;
	sctx->state[1] = SHA1_H1;
	sctx->state[2] = SHA1_H2;
	sctx->state[3] = SHA1_H3;
	sctx->state[4] = SHA1_H4;
	sctx->count = 0;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sha1_base_करो_update(काष्ठा shash_desc *desc,
				      स्थिर u8 *data,
				      अचिन्हित पूर्णांक len,
				      sha1_block_fn *block_fn)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial = sctx->count % SHA1_BLOCK_SIZE;

	sctx->count += len;

	अगर (unlikely((partial + len) >= SHA1_BLOCK_SIZE)) अणु
		पूर्णांक blocks;

		अगर (partial) अणु
			पूर्णांक p = SHA1_BLOCK_SIZE - partial;

			स_नकल(sctx->buffer + partial, data, p);
			data += p;
			len -= p;

			block_fn(sctx, sctx->buffer, 1);
		पूर्ण

		blocks = len / SHA1_BLOCK_SIZE;
		len %= SHA1_BLOCK_SIZE;

		अगर (blocks) अणु
			block_fn(sctx, data, blocks);
			data += blocks * SHA1_BLOCK_SIZE;
		पूर्ण
		partial = 0;
	पूर्ण
	अगर (len)
		स_नकल(sctx->buffer + partial, data, len);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sha1_base_करो_finalize(काष्ठा shash_desc *desc,
					sha1_block_fn *block_fn)
अणु
	स्थिर पूर्णांक bit_offset = SHA1_BLOCK_SIZE - माप(__be64);
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);
	__be64 *bits = (__be64 *)(sctx->buffer + bit_offset);
	अचिन्हित पूर्णांक partial = sctx->count % SHA1_BLOCK_SIZE;

	sctx->buffer[partial++] = 0x80;
	अगर (partial > bit_offset) अणु
		स_रखो(sctx->buffer + partial, 0x0, SHA1_BLOCK_SIZE - partial);
		partial = 0;

		block_fn(sctx, sctx->buffer, 1);
	पूर्ण

	स_रखो(sctx->buffer + partial, 0x0, bit_offset - partial);
	*bits = cpu_to_be64(sctx->count << 3);
	block_fn(sctx, sctx->buffer, 1);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sha1_base_finish(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);
	__be32 *digest = (__be32 *)out;
	पूर्णांक i;

	क्रम (i = 0; i < SHA1_DIGEST_SIZE / माप(__be32); i++)
		put_unaligned_be32(sctx->state[i], digest++);

	memzero_explicit(sctx, माप(*sctx));
	वापस 0;
पूर्ण

#पूर्ण_अगर /* _CRYPTO_SHA1_BASE_H */
