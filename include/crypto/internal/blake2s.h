<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/*
 * Helper functions क्रम BLAKE2s implementations.
 * Keep this in sync with the corresponding BLAKE2b header.
 */

#अगर_अघोषित _CRYPTO_INTERNAL_BLAKE2S_H
#घोषणा _CRYPTO_INTERNAL_BLAKE2S_H

#समावेश <crypto/blake2s.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/माला.स>

व्योम blake2s_compress_generic(काष्ठा blake2s_state *state,स्थिर u8 *block,
			      माप_प्रकार nblocks, स्थिर u32 inc);

व्योम blake2s_compress_arch(काष्ठा blake2s_state *state,स्थिर u8 *block,
			   माप_प्रकार nblocks, स्थिर u32 inc);

bool blake2s_selftest(व्योम);

अटल अंतरभूत व्योम blake2s_set_lastblock(काष्ठा blake2s_state *state)
अणु
	state->f[0] = -1;
पूर्ण

प्रकार व्योम (*blake2s_compress_t)(काष्ठा blake2s_state *state,
				   स्थिर u8 *block, माप_प्रकार nblocks, u32 inc);

/* Helper functions क्रम BLAKE2s shared by the library and shash APIs */

अटल अंतरभूत व्योम __blake2s_update(काष्ठा blake2s_state *state,
				    स्थिर u8 *in, माप_प्रकार inlen,
				    blake2s_compress_t compress)
अणु
	स्थिर माप_प्रकार fill = BLAKE2S_BLOCK_SIZE - state->buflen;

	अगर (unlikely(!inlen))
		वापस;
	अगर (inlen > fill) अणु
		स_नकल(state->buf + state->buflen, in, fill);
		(*compress)(state, state->buf, 1, BLAKE2S_BLOCK_SIZE);
		state->buflen = 0;
		in += fill;
		inlen -= fill;
	पूर्ण
	अगर (inlen > BLAKE2S_BLOCK_SIZE) अणु
		स्थिर माप_प्रकार nblocks = DIV_ROUND_UP(inlen, BLAKE2S_BLOCK_SIZE);
		/* Hash one less (full) block than strictly possible */
		(*compress)(state, in, nblocks - 1, BLAKE2S_BLOCK_SIZE);
		in += BLAKE2S_BLOCK_SIZE * (nblocks - 1);
		inlen -= BLAKE2S_BLOCK_SIZE * (nblocks - 1);
	पूर्ण
	स_नकल(state->buf + state->buflen, in, inlen);
	state->buflen += inlen;
पूर्ण

अटल अंतरभूत व्योम __blake2s_final(काष्ठा blake2s_state *state, u8 *out,
				   blake2s_compress_t compress)
अणु
	blake2s_set_lastblock(state);
	स_रखो(state->buf + state->buflen, 0,
	       BLAKE2S_BLOCK_SIZE - state->buflen); /* Padding */
	(*compress)(state, state->buf, 1, state->buflen);
	cpu_to_le32_array(state->h, ARRAY_SIZE(state->h));
	स_नकल(out, state->h, state->outlen);
पूर्ण

/* Helper functions क्रम shash implementations of BLAKE2s */

काष्ठा blake2s_tfm_ctx अणु
	u8 key[BLAKE2S_KEY_SIZE];
	अचिन्हित पूर्णांक keylen;
पूर्ण;

अटल अंतरभूत पूर्णांक crypto_blake2s_setkey(काष्ठा crypto_shash *tfm,
					स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा blake2s_tfm_ctx *tctx = crypto_shash_ctx(tfm);

	अगर (keylen == 0 || keylen > BLAKE2S_KEY_SIZE)
		वापस -EINVAL;

	स_नकल(tctx->key, key, keylen);
	tctx->keylen = keylen;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक crypto_blake2s_init(काष्ठा shash_desc *desc)
अणु
	स्थिर काष्ठा blake2s_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	काष्ठा blake2s_state *state = shash_desc_ctx(desc);
	अचिन्हित पूर्णांक outlen = crypto_shash_digestsize(desc->tfm);

	__blake2s_init(state, outlen, tctx->key, tctx->keylen);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक crypto_blake2s_update(काष्ठा shash_desc *desc,
					स्थिर u8 *in, अचिन्हित पूर्णांक inlen,
					blake2s_compress_t compress)
अणु
	काष्ठा blake2s_state *state = shash_desc_ctx(desc);

	__blake2s_update(state, in, inlen, compress);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक crypto_blake2s_final(काष्ठा shash_desc *desc, u8 *out,
				       blake2s_compress_t compress)
अणु
	काष्ठा blake2s_state *state = shash_desc_ctx(desc);

	__blake2s_final(state, out, compress);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* _CRYPTO_INTERNAL_BLAKE2S_H */
