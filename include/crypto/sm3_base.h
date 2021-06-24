<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * sm3_base.h - core logic क्रम SM3 implementations
 *
 * Copyright (C) 2017 ARM Limited or its affiliates.
 * Written by Gilad Ben-Yossef <gilad@benyossef.com>
 */

#अगर_अघोषित _CRYPTO_SM3_BASE_H
#घोषणा _CRYPTO_SM3_BASE_H

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/sm3.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/unaligned.h>

प्रकार व्योम (sm3_block_fn)(काष्ठा sm3_state *sst, u8 स्थिर *src, पूर्णांक blocks);

अटल अंतरभूत पूर्णांक sm3_base_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sm3_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SM3_IVA;
	sctx->state[1] = SM3_IVB;
	sctx->state[2] = SM3_IVC;
	sctx->state[3] = SM3_IVD;
	sctx->state[4] = SM3_IVE;
	sctx->state[5] = SM3_IVF;
	sctx->state[6] = SM3_IVG;
	sctx->state[7] = SM3_IVH;
	sctx->count = 0;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sm3_base_करो_update(काष्ठा shash_desc *desc,
				      स्थिर u8 *data,
				      अचिन्हित पूर्णांक len,
				      sm3_block_fn *block_fn)
अणु
	काष्ठा sm3_state *sctx = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक partial = sctx->count % SM3_BLOCK_SIZE;

	sctx->count += len;

	अगर (unlikely((partial + len) >= SM3_BLOCK_SIZE)) अणु
		पूर्णांक blocks;

		अगर (partial) अणु
			पूर्णांक p = SM3_BLOCK_SIZE - partial;

			स_नकल(sctx->buffer + partial, data, p);
			data += p;
			len -= p;

			block_fn(sctx, sctx->buffer, 1);
		पूर्ण

		blocks = len / SM3_BLOCK_SIZE;
		len %= SM3_BLOCK_SIZE;

		अगर (blocks) अणु
			block_fn(sctx, data, blocks);
			data += blocks * SM3_BLOCK_SIZE;
		पूर्ण
		partial = 0;
	पूर्ण
	अगर (len)
		स_नकल(sctx->buffer + partial, data, len);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sm3_base_करो_finalize(काष्ठा shash_desc *desc,
					sm3_block_fn *block_fn)
अणु
	स्थिर पूर्णांक bit_offset = SM3_BLOCK_SIZE - माप(__be64);
	काष्ठा sm3_state *sctx = shash_desc_ctx(desc);
	__be64 *bits = (__be64 *)(sctx->buffer + bit_offset);
	अचिन्हित पूर्णांक partial = sctx->count % SM3_BLOCK_SIZE;

	sctx->buffer[partial++] = 0x80;
	अगर (partial > bit_offset) अणु
		स_रखो(sctx->buffer + partial, 0x0, SM3_BLOCK_SIZE - partial);
		partial = 0;

		block_fn(sctx, sctx->buffer, 1);
	पूर्ण

	स_रखो(sctx->buffer + partial, 0x0, bit_offset - partial);
	*bits = cpu_to_be64(sctx->count << 3);
	block_fn(sctx, sctx->buffer, 1);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sm3_base_finish(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sm3_state *sctx = shash_desc_ctx(desc);
	__be32 *digest = (__be32 *)out;
	पूर्णांक i;

	क्रम (i = 0; i < SM3_DIGEST_SIZE / माप(__be32); i++)
		put_unaligned_be32(sctx->state[i], digest++);

	memzero_explicit(sctx, माप(*sctx));
	वापस 0;
पूर्ण

#पूर्ण_अगर /* _CRYPTO_SM3_BASE_H */
