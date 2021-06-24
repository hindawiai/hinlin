<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/*
 * Helper functions क्रम BLAKE2b implementations.
 * Keep this in sync with the corresponding BLAKE2s header.
 */

#अगर_अघोषित _CRYPTO_INTERNAL_BLAKE2B_H
#घोषणा _CRYPTO_INTERNAL_BLAKE2B_H

#समावेश <crypto/blake2b.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/माला.स>

व्योम blake2b_compress_generic(काष्ठा blake2b_state *state,
			      स्थिर u8 *block, माप_प्रकार nblocks, u32 inc);

अटल अंतरभूत व्योम blake2b_set_lastblock(काष्ठा blake2b_state *state)
अणु
	state->f[0] = -1;
पूर्ण

प्रकार व्योम (*blake2b_compress_t)(काष्ठा blake2b_state *state,
				   स्थिर u8 *block, माप_प्रकार nblocks, u32 inc);

अटल अंतरभूत व्योम __blake2b_update(काष्ठा blake2b_state *state,
				    स्थिर u8 *in, माप_प्रकार inlen,
				    blake2b_compress_t compress)
अणु
	स्थिर माप_प्रकार fill = BLAKE2B_BLOCK_SIZE - state->buflen;

	अगर (unlikely(!inlen))
		वापस;
	अगर (inlen > fill) अणु
		स_नकल(state->buf + state->buflen, in, fill);
		(*compress)(state, state->buf, 1, BLAKE2B_BLOCK_SIZE);
		state->buflen = 0;
		in += fill;
		inlen -= fill;
	पूर्ण
	अगर (inlen > BLAKE2B_BLOCK_SIZE) अणु
		स्थिर माप_प्रकार nblocks = DIV_ROUND_UP(inlen, BLAKE2B_BLOCK_SIZE);
		/* Hash one less (full) block than strictly possible */
		(*compress)(state, in, nblocks - 1, BLAKE2B_BLOCK_SIZE);
		in += BLAKE2B_BLOCK_SIZE * (nblocks - 1);
		inlen -= BLAKE2B_BLOCK_SIZE * (nblocks - 1);
	पूर्ण
	स_नकल(state->buf + state->buflen, in, inlen);
	state->buflen += inlen;
पूर्ण

अटल अंतरभूत व्योम __blake2b_final(काष्ठा blake2b_state *state, u8 *out,
				   blake2b_compress_t compress)
अणु
	पूर्णांक i;

	blake2b_set_lastblock(state);
	स_रखो(state->buf + state->buflen, 0,
	       BLAKE2B_BLOCK_SIZE - state->buflen); /* Padding */
	(*compress)(state, state->buf, 1, state->buflen);
	क्रम (i = 0; i < ARRAY_SIZE(state->h); i++)
		__cpu_to_le64s(&state->h[i]);
	स_नकल(out, state->h, state->outlen);
पूर्ण

/* Helper functions क्रम shash implementations of BLAKE2b */

काष्ठा blake2b_tfm_ctx अणु
	u8 key[BLAKE2B_KEY_SIZE];
	अचिन्हित पूर्णांक keylen;
पूर्ण;

अटल अंतरभूत पूर्णांक crypto_blake2b_setkey(काष्ठा crypto_shash *tfm,
					स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा blake2b_tfm_ctx *tctx = crypto_shash_ctx(tfm);

	अगर (keylen == 0 || keylen > BLAKE2B_KEY_SIZE)
		वापस -EINVAL;

	स_नकल(tctx->key, key, keylen);
	tctx->keylen = keylen;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक crypto_blake2b_init(काष्ठा shash_desc *desc)
अणु
	स्थिर काष्ठा blake2b_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	काष्ठा blake2b_state *state = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक outlen = crypto_shash_digestsize(desc->tfm);

	__blake2b_init(state, outlen, tctx->key, tctx->keylen);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक crypto_blake2b_update(काष्ठा shash_desc *desc,
					स्थिर u8 *in, अचिन्हित पूर्णांक inlen,
					blake2b_compress_t compress)
अणु
	काष्ठा blake2b_state *state = shash_desc_ctx(desc);

	__blake2b_update(state, in, inlen, compress);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक crypto_blake2b_final(काष्ठा shash_desc *desc, u8 *out,
				       blake2b_compress_t compress)
अणु
	काष्ठा blake2b_state *state = shash_desc_ctx(desc);

	__blake2b_final(state, out, compress);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* _CRYPTO_INTERNAL_BLAKE2B_H */
