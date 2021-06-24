<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NHPoly1305 - Nग-almost-ै-universal hash function क्रम Adiantum
 *
 * Copyright 2018 Google LLC
 */

/*
 * "NHPoly1305" is the मुख्य component of Adiantum hashing.
 * Specअगरically, it is the calculation
 *
 *	H_L ै Poly1305_अणुK_Lपूर्ण(NH_अणुK_Nपूर्ण(pad_अणु128पूर्ण(L)))
 *
 * from the procedure in section 6.4 of the Adiantum paper [1].  It is an
 * Nग-almost-ै-universal (Nग-ैU) hash function क्रम equal-length inमाला_दो over
 * Z/(2^अणु128पूर्णZ), where the "ै" operation is addition.  It hashes 1024-byte
 * chunks of the input with the NH hash function [2], reducing the input length
 * by 32x.  The resulting NH digests are evaluated as a polynomial in
 * GF(2^अणु130पूर्ण-5), like in the Poly1305 MAC [3].  Note that the polynomial
 * evaluation by itself would suffice to achieve the Nग-ैU property; NH is used
 * क्रम perक्रमmance since it's over twice as fast as Poly1305.
 *
 * This is *not* a cryptographic hash function; करो not use it as such!
 *
 * [1] Adiantum: length-preserving encryption क्रम entry-level processors
 *     (https://eprपूर्णांक.iacr.org/2018/720.pdf)
 * [2] UMAC: Fast and Secure Message Authentication
 *     (https://fastcrypto.org/umac/umac_proc.pdf)
 * [3] The Poly1305-AES message-authentication code
 *     (https://cr.yp.to/mac/poly1305-20050329.pdf)
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/poly1305.h>
#समावेश <crypto/nhpoly1305.h>
#समावेश <linux/crypto.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

अटल व्योम nh_generic(स्थिर u32 *key, स्थिर u8 *message, माप_प्रकार message_len,
		       __le64 hash[NH_NUM_PASSES])
अणु
	u64 sums[4] = अणु 0, 0, 0, 0 पूर्ण;

	BUILD_BUG_ON(NH_PAIR_STRIDE != 2);
	BUILD_BUG_ON(NH_NUM_PASSES != 4);

	जबतक (message_len) अणु
		u32 m0 = get_unaligned_le32(message + 0);
		u32 m1 = get_unaligned_le32(message + 4);
		u32 m2 = get_unaligned_le32(message + 8);
		u32 m3 = get_unaligned_le32(message + 12);

		sums[0] += (u64)(u32)(m0 + key[ 0]) * (u32)(m2 + key[ 2]);
		sums[1] += (u64)(u32)(m0 + key[ 4]) * (u32)(m2 + key[ 6]);
		sums[2] += (u64)(u32)(m0 + key[ 8]) * (u32)(m2 + key[10]);
		sums[3] += (u64)(u32)(m0 + key[12]) * (u32)(m2 + key[14]);
		sums[0] += (u64)(u32)(m1 + key[ 1]) * (u32)(m3 + key[ 3]);
		sums[1] += (u64)(u32)(m1 + key[ 5]) * (u32)(m3 + key[ 7]);
		sums[2] += (u64)(u32)(m1 + key[ 9]) * (u32)(m3 + key[11]);
		sums[3] += (u64)(u32)(m1 + key[13]) * (u32)(m3 + key[15]);
		key += NH_MESSAGE_UNIT / माप(key[0]);
		message += NH_MESSAGE_UNIT;
		message_len -= NH_MESSAGE_UNIT;
	पूर्ण

	hash[0] = cpu_to_le64(sums[0]);
	hash[1] = cpu_to_le64(sums[1]);
	hash[2] = cpu_to_le64(sums[2]);
	hash[3] = cpu_to_le64(sums[3]);
पूर्ण

/* Pass the next NH hash value through Poly1305 */
अटल व्योम process_nh_hash_value(काष्ठा nhpoly1305_state *state,
				  स्थिर काष्ठा nhpoly1305_key *key)
अणु
	BUILD_BUG_ON(NH_HASH_BYTES % POLY1305_BLOCK_SIZE != 0);

	poly1305_core_blocks(&state->poly_state, &key->poly_key, state->nh_hash,
			     NH_HASH_BYTES / POLY1305_BLOCK_SIZE, 1);
पूर्ण

/*
 * Feed the next portion of the source data, as a whole number of 16-byte
 * "NH message units", through NH and Poly1305.  Each NH hash is taken over
 * 1024 bytes, except possibly the final one which is taken over a multiple of
 * 16 bytes up to 1024.  Also, in the हाल where data is passed in misaligned
 * chunks, we combine partial hashes; the end result is the same either way.
 */
अटल व्योम nhpoly1305_units(काष्ठा nhpoly1305_state *state,
			     स्थिर काष्ठा nhpoly1305_key *key,
			     स्थिर u8 *src, अचिन्हित पूर्णांक srclen, nh_t nh_fn)
अणु
	करो अणु
		अचिन्हित पूर्णांक bytes;

		अगर (state->nh_reमुख्यing == 0) अणु
			/* Starting a new NH message */
			bytes = min_t(अचिन्हित पूर्णांक, srclen, NH_MESSAGE_BYTES);
			nh_fn(key->nh_key, src, bytes, state->nh_hash);
			state->nh_reमुख्यing = NH_MESSAGE_BYTES - bytes;
		पूर्ण अन्यथा अणु
			/* Continuing a previous NH message */
			__le64 पंचांगp_hash[NH_NUM_PASSES];
			अचिन्हित पूर्णांक pos;
			पूर्णांक i;

			pos = NH_MESSAGE_BYTES - state->nh_reमुख्यing;
			bytes = min(srclen, state->nh_reमुख्यing);
			nh_fn(&key->nh_key[pos / 4], src, bytes, पंचांगp_hash);
			क्रम (i = 0; i < NH_NUM_PASSES; i++)
				le64_add_cpu(&state->nh_hash[i],
					     le64_to_cpu(पंचांगp_hash[i]));
			state->nh_reमुख्यing -= bytes;
		पूर्ण
		अगर (state->nh_reमुख्यing == 0)
			process_nh_hash_value(state, key);
		src += bytes;
		srclen -= bytes;
	पूर्ण जबतक (srclen);
पूर्ण

पूर्णांक crypto_nhpoly1305_setkey(काष्ठा crypto_shash *tfm,
			     स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा nhpoly1305_key *ctx = crypto_shash_ctx(tfm);
	पूर्णांक i;

	अगर (keylen != NHPOLY1305_KEY_SIZE)
		वापस -EINVAL;

	poly1305_core_setkey(&ctx->poly_key, key);
	key += POLY1305_BLOCK_SIZE;

	क्रम (i = 0; i < NH_KEY_WORDS; i++)
		ctx->nh_key[i] = get_unaligned_le32(key + i * माप(u32));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(crypto_nhpoly1305_setkey);

पूर्णांक crypto_nhpoly1305_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा nhpoly1305_state *state = shash_desc_ctx(desc);

	poly1305_core_init(&state->poly_state);
	state->buflen = 0;
	state->nh_reमुख्यing = 0;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(crypto_nhpoly1305_init);

पूर्णांक crypto_nhpoly1305_update_helper(काष्ठा shash_desc *desc,
				    स्थिर u8 *src, अचिन्हित पूर्णांक srclen,
				    nh_t nh_fn)
अणु
	काष्ठा nhpoly1305_state *state = shash_desc_ctx(desc);
	स्थिर काष्ठा nhpoly1305_key *key = crypto_shash_ctx(desc->tfm);
	अचिन्हित पूर्णांक bytes;

	अगर (state->buflen) अणु
		bytes = min(srclen, (पूर्णांक)NH_MESSAGE_UNIT - state->buflen);
		स_नकल(&state->buffer[state->buflen], src, bytes);
		state->buflen += bytes;
		अगर (state->buflen < NH_MESSAGE_UNIT)
			वापस 0;
		nhpoly1305_units(state, key, state->buffer, NH_MESSAGE_UNIT,
				 nh_fn);
		state->buflen = 0;
		src += bytes;
		srclen -= bytes;
	पूर्ण

	अगर (srclen >= NH_MESSAGE_UNIT) अणु
		bytes = round_करोwn(srclen, NH_MESSAGE_UNIT);
		nhpoly1305_units(state, key, src, bytes, nh_fn);
		src += bytes;
		srclen -= bytes;
	पूर्ण

	अगर (srclen) अणु
		स_नकल(state->buffer, src, srclen);
		state->buflen = srclen;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(crypto_nhpoly1305_update_helper);

पूर्णांक crypto_nhpoly1305_update(काष्ठा shash_desc *desc,
			     स्थिर u8 *src, अचिन्हित पूर्णांक srclen)
अणु
	वापस crypto_nhpoly1305_update_helper(desc, src, srclen, nh_generic);
पूर्ण
EXPORT_SYMBOL(crypto_nhpoly1305_update);

पूर्णांक crypto_nhpoly1305_final_helper(काष्ठा shash_desc *desc, u8 *dst, nh_t nh_fn)
अणु
	काष्ठा nhpoly1305_state *state = shash_desc_ctx(desc);
	स्थिर काष्ठा nhpoly1305_key *key = crypto_shash_ctx(desc->tfm);

	अगर (state->buflen) अणु
		स_रखो(&state->buffer[state->buflen], 0,
		       NH_MESSAGE_UNIT - state->buflen);
		nhpoly1305_units(state, key, state->buffer, NH_MESSAGE_UNIT,
				 nh_fn);
	पूर्ण

	अगर (state->nh_reमुख्यing)
		process_nh_hash_value(state, key);

	poly1305_core_emit(&state->poly_state, शून्य, dst);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(crypto_nhpoly1305_final_helper);

पूर्णांक crypto_nhpoly1305_final(काष्ठा shash_desc *desc, u8 *dst)
अणु
	वापस crypto_nhpoly1305_final_helper(desc, dst, nh_generic);
पूर्ण
EXPORT_SYMBOL(crypto_nhpoly1305_final);

अटल काष्ठा shash_alg nhpoly1305_alg = अणु
	.base.cra_name		= "nhpoly1305",
	.base.cra_driver_name	= "nhpoly1305-generic",
	.base.cra_priority	= 100,
	.base.cra_ctxsize	= माप(काष्ठा nhpoly1305_key),
	.base.cra_module	= THIS_MODULE,
	.digestsize		= POLY1305_DIGEST_SIZE,
	.init			= crypto_nhpoly1305_init,
	.update			= crypto_nhpoly1305_update,
	.final			= crypto_nhpoly1305_final,
	.setkey			= crypto_nhpoly1305_setkey,
	.descsize		= माप(काष्ठा nhpoly1305_state),
पूर्ण;

अटल पूर्णांक __init nhpoly1305_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&nhpoly1305_alg);
पूर्ण

अटल व्योम __निकास nhpoly1305_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&nhpoly1305_alg);
पूर्ण

subsys_initcall(nhpoly1305_mod_init);
module_निकास(nhpoly1305_mod_निकास);

MODULE_DESCRIPTION("NHPoly1305 Nग-almost-ै-universal hash function");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Eric Biggers <ebiggers@google.com>");
MODULE_ALIAS_CRYPTO("nhpoly1305");
MODULE_ALIAS_CRYPTO("nhpoly1305-generic");
