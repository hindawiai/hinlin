<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/poly1305.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/crypto.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/simd.h>

यंत्रlinkage व्योम poly1305_init_x86_64(व्योम *ctx,
				     स्थिर u8 key[POLY1305_BLOCK_SIZE]);
यंत्रlinkage व्योम poly1305_blocks_x86_64(व्योम *ctx, स्थिर u8 *inp,
				       स्थिर माप_प्रकार len, स्थिर u32 padbit);
यंत्रlinkage व्योम poly1305_emit_x86_64(व्योम *ctx, u8 mac[POLY1305_DIGEST_SIZE],
				     स्थिर u32 nonce[4]);
यंत्रlinkage व्योम poly1305_emit_avx(व्योम *ctx, u8 mac[POLY1305_DIGEST_SIZE],
				  स्थिर u32 nonce[4]);
यंत्रlinkage व्योम poly1305_blocks_avx(व्योम *ctx, स्थिर u8 *inp, स्थिर माप_प्रकार len,
				    स्थिर u32 padbit);
यंत्रlinkage व्योम poly1305_blocks_avx2(व्योम *ctx, स्थिर u8 *inp, स्थिर माप_प्रकार len,
				     स्थिर u32 padbit);
यंत्रlinkage व्योम poly1305_blocks_avx512(व्योम *ctx, स्थिर u8 *inp,
				       स्थिर माप_प्रकार len, स्थिर u32 padbit);

अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(poly1305_use_avx);
अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(poly1305_use_avx2);
अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(poly1305_use_avx512);

काष्ठा poly1305_arch_पूर्णांकernal अणु
	जोड़ अणु
		काष्ठा अणु
			u32 h[5];
			u32 is_base2_26;
		पूर्ण;
		u64 hs[3];
	पूर्ण;
	u64 r[2];
	u64 pad;
	काष्ठा अणु u32 r2, r1, r4, r3; पूर्ण rn[9];
पूर्ण;

/* The AVX code uses base 2^26, जबतक the scalar code uses base 2^64. If we hit
 * the unक्रमtunate situation of using AVX and then having to go back to scalar
 * -- because the user is silly and has called the update function from two
 * separate contexts -- then we need to convert back to the original base beक्रमe
 * proceeding. It is possible to reason that the initial reduction below is
 * sufficient given the implementation invariants. However, क्रम an aव्योमance of
 * करोubt and because this is not perक्रमmance critical, we करो the full reduction
 * anyway. Z3 proof of below function: https://xn--4db.cc/ltPtHCKN/py
 */
अटल व्योम convert_to_base2_64(व्योम *ctx)
अणु
	काष्ठा poly1305_arch_पूर्णांकernal *state = ctx;
	u32 cy;

	अगर (!state->is_base2_26)
		वापस;

	cy = state->h[0] >> 26; state->h[0] &= 0x3ffffff; state->h[1] += cy;
	cy = state->h[1] >> 26; state->h[1] &= 0x3ffffff; state->h[2] += cy;
	cy = state->h[2] >> 26; state->h[2] &= 0x3ffffff; state->h[3] += cy;
	cy = state->h[3] >> 26; state->h[3] &= 0x3ffffff; state->h[4] += cy;
	state->hs[0] = ((u64)state->h[2] << 52) | ((u64)state->h[1] << 26) | state->h[0];
	state->hs[1] = ((u64)state->h[4] << 40) | ((u64)state->h[3] << 14) | (state->h[2] >> 12);
	state->hs[2] = state->h[4] >> 24;
#घोषणा ULT(a, b) ((a ^ ((a ^ b) | ((a - b) ^ b))) >> (माप(a) * 8 - 1))
	cy = (state->hs[2] >> 2) + (state->hs[2] & ~3ULL);
	state->hs[2] &= 3;
	state->hs[0] += cy;
	state->hs[1] += (cy = ULT(state->hs[0], cy));
	state->hs[2] += ULT(state->hs[1], cy);
#अघोषित ULT
	state->is_base2_26 = 0;
पूर्ण

अटल व्योम poly1305_simd_init(व्योम *ctx, स्थिर u8 key[POLY1305_BLOCK_SIZE])
अणु
	poly1305_init_x86_64(ctx, key);
पूर्ण

अटल व्योम poly1305_simd_blocks(व्योम *ctx, स्थिर u8 *inp, माप_प्रकार len,
				 स्थिर u32 padbit)
अणु
	काष्ठा poly1305_arch_पूर्णांकernal *state = ctx;

	/* SIMD disables preemption, so relax after processing each page. */
	BUILD_BUG_ON(SZ_4K < POLY1305_BLOCK_SIZE ||
		     SZ_4K % POLY1305_BLOCK_SIZE);

	अगर (!अटल_branch_likely(&poly1305_use_avx) ||
	    (len < (POLY1305_BLOCK_SIZE * 18) && !state->is_base2_26) ||
	    !crypto_simd_usable()) अणु
		convert_to_base2_64(ctx);
		poly1305_blocks_x86_64(ctx, inp, len, padbit);
		वापस;
	पूर्ण

	करो अणु
		स्थिर माप_प्रकार bytes = min_t(माप_प्रकार, len, SZ_4K);

		kernel_fpu_begin();
		अगर (IS_ENABLED(CONFIG_AS_AVX512) && अटल_branch_likely(&poly1305_use_avx512))
			poly1305_blocks_avx512(ctx, inp, bytes, padbit);
		अन्यथा अगर (अटल_branch_likely(&poly1305_use_avx2))
			poly1305_blocks_avx2(ctx, inp, bytes, padbit);
		अन्यथा
			poly1305_blocks_avx(ctx, inp, bytes, padbit);
		kernel_fpu_end();

		len -= bytes;
		inp += bytes;
	पूर्ण जबतक (len);
पूर्ण

अटल व्योम poly1305_simd_emit(व्योम *ctx, u8 mac[POLY1305_DIGEST_SIZE],
			       स्थिर u32 nonce[4])
अणु
	अगर (!अटल_branch_likely(&poly1305_use_avx))
		poly1305_emit_x86_64(ctx, mac, nonce);
	अन्यथा
		poly1305_emit_avx(ctx, mac, nonce);
पूर्ण

व्योम poly1305_init_arch(काष्ठा poly1305_desc_ctx *dctx, स्थिर u8 key[POLY1305_KEY_SIZE])
अणु
	poly1305_simd_init(&dctx->h, key);
	dctx->s[0] = get_unaligned_le32(&key[16]);
	dctx->s[1] = get_unaligned_le32(&key[20]);
	dctx->s[2] = get_unaligned_le32(&key[24]);
	dctx->s[3] = get_unaligned_le32(&key[28]);
	dctx->buflen = 0;
	dctx->sset = true;
पूर्ण
EXPORT_SYMBOL(poly1305_init_arch);

अटल अचिन्हित पूर्णांक crypto_poly1305_setdctxkey(काष्ठा poly1305_desc_ctx *dctx,
					       स्थिर u8 *inp, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक acc = 0;
	अगर (unlikely(!dctx->sset)) अणु
		अगर (!dctx->rset && len >= POLY1305_BLOCK_SIZE) अणु
			poly1305_simd_init(&dctx->h, inp);
			inp += POLY1305_BLOCK_SIZE;
			len -= POLY1305_BLOCK_SIZE;
			acc += POLY1305_BLOCK_SIZE;
			dctx->rset = 1;
		पूर्ण
		अगर (len >= POLY1305_BLOCK_SIZE) अणु
			dctx->s[0] = get_unaligned_le32(&inp[0]);
			dctx->s[1] = get_unaligned_le32(&inp[4]);
			dctx->s[2] = get_unaligned_le32(&inp[8]);
			dctx->s[3] = get_unaligned_le32(&inp[12]);
			acc += POLY1305_BLOCK_SIZE;
			dctx->sset = true;
		पूर्ण
	पूर्ण
	वापस acc;
पूर्ण

व्योम poly1305_update_arch(काष्ठा poly1305_desc_ctx *dctx, स्थिर u8 *src,
			  अचिन्हित पूर्णांक srclen)
अणु
	अचिन्हित पूर्णांक bytes, used;

	अगर (unlikely(dctx->buflen)) अणु
		bytes = min(srclen, POLY1305_BLOCK_SIZE - dctx->buflen);
		स_नकल(dctx->buf + dctx->buflen, src, bytes);
		src += bytes;
		srclen -= bytes;
		dctx->buflen += bytes;

		अगर (dctx->buflen == POLY1305_BLOCK_SIZE) अणु
			अगर (likely(!crypto_poly1305_setdctxkey(dctx, dctx->buf, POLY1305_BLOCK_SIZE)))
				poly1305_simd_blocks(&dctx->h, dctx->buf, POLY1305_BLOCK_SIZE, 1);
			dctx->buflen = 0;
		पूर्ण
	पूर्ण

	अगर (likely(srclen >= POLY1305_BLOCK_SIZE)) अणु
		bytes = round_करोwn(srclen, POLY1305_BLOCK_SIZE);
		srclen -= bytes;
		used = crypto_poly1305_setdctxkey(dctx, src, bytes);
		अगर (likely(bytes - used))
			poly1305_simd_blocks(&dctx->h, src + used, bytes - used, 1);
		src += bytes;
	पूर्ण

	अगर (unlikely(srclen)) अणु
		dctx->buflen = srclen;
		स_नकल(dctx->buf, src, srclen);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(poly1305_update_arch);

व्योम poly1305_final_arch(काष्ठा poly1305_desc_ctx *dctx, u8 *dst)
अणु
	अगर (unlikely(dctx->buflen)) अणु
		dctx->buf[dctx->buflen++] = 1;
		स_रखो(dctx->buf + dctx->buflen, 0,
		       POLY1305_BLOCK_SIZE - dctx->buflen);
		poly1305_simd_blocks(&dctx->h, dctx->buf, POLY1305_BLOCK_SIZE, 0);
	पूर्ण

	poly1305_simd_emit(&dctx->h, dst, dctx->s);
	memzero_explicit(dctx, माप(*dctx));
पूर्ण
EXPORT_SYMBOL(poly1305_final_arch);

अटल पूर्णांक crypto_poly1305_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा poly1305_desc_ctx *dctx = shash_desc_ctx(desc);

	*dctx = (काष्ठा poly1305_desc_ctx)अणुपूर्ण;
	वापस 0;
पूर्ण

अटल पूर्णांक crypto_poly1305_update(काष्ठा shash_desc *desc,
				  स्थिर u8 *src, अचिन्हित पूर्णांक srclen)
अणु
	काष्ठा poly1305_desc_ctx *dctx = shash_desc_ctx(desc);

	poly1305_update_arch(dctx, src, srclen);
	वापस 0;
पूर्ण

अटल पूर्णांक crypto_poly1305_final(काष्ठा shash_desc *desc, u8 *dst)
अणु
	काष्ठा poly1305_desc_ctx *dctx = shash_desc_ctx(desc);

	अगर (unlikely(!dctx->sset))
		वापस -ENOKEY;

	poly1305_final_arch(dctx, dst);
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize	= POLY1305_DIGEST_SIZE,
	.init		= crypto_poly1305_init,
	.update		= crypto_poly1305_update,
	.final		= crypto_poly1305_final,
	.descsize	= माप(काष्ठा poly1305_desc_ctx),
	.base		= अणु
		.cra_name		= "poly1305",
		.cra_driver_name	= "poly1305-simd",
		.cra_priority		= 300,
		.cra_blocksize		= POLY1305_BLOCK_SIZE,
		.cra_module		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init poly1305_simd_mod_init(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_AVX) &&
	    cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM, शून्य))
		अटल_branch_enable(&poly1305_use_avx);
	अगर (boot_cpu_has(X86_FEATURE_AVX) && boot_cpu_has(X86_FEATURE_AVX2) &&
	    cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM, शून्य))
		अटल_branch_enable(&poly1305_use_avx2);
	अगर (IS_ENABLED(CONFIG_AS_AVX512) && boot_cpu_has(X86_FEATURE_AVX) &&
	    boot_cpu_has(X86_FEATURE_AVX2) && boot_cpu_has(X86_FEATURE_AVX512F) &&
	    cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM | XFEATURE_MASK_AVX512, शून्य) &&
	    /* Skylake करोwnघड़ीs unacceptably much when using zmm, but later generations are fast. */
	    boot_cpu_data.x86_model != INTEL_FAM6_SKYLAKE_X)
		अटल_branch_enable(&poly1305_use_avx512);
	वापस IS_REACHABLE(CONFIG_CRYPTO_HASH) ? crypto_रेजिस्टर_shash(&alg) : 0;
पूर्ण

अटल व्योम __निकास poly1305_simd_mod_निकास(व्योम)
अणु
	अगर (IS_REACHABLE(CONFIG_CRYPTO_HASH))
		crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_init(poly1305_simd_mod_init);
module_निकास(poly1305_simd_mod_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jason A. Donenfeld <Jason@zx2c4.com>");
MODULE_DESCRIPTION("Poly1305 authenticator");
MODULE_ALIAS_CRYPTO("poly1305");
MODULE_ALIAS_CRYPTO("poly1305-simd");
