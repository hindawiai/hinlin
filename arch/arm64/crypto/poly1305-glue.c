<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OpenSSL/Cryptogams accelerated Poly1305 transक्रमm क्रम arm64
 *
 * Copyright (C) 2019 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/poly1305.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/cpufeature.h>
#समावेश <linux/crypto.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/module.h>

यंत्रlinkage व्योम poly1305_init_arm64(व्योम *state, स्थिर u8 *key);
यंत्रlinkage व्योम poly1305_blocks(व्योम *state, स्थिर u8 *src, u32 len, u32 hibit);
यंत्रlinkage व्योम poly1305_blocks_neon(व्योम *state, स्थिर u8 *src, u32 len, u32 hibit);
यंत्रlinkage व्योम poly1305_emit(व्योम *state, u8 *digest, स्थिर u32 *nonce);

अटल __ro_after_init DEFINE_STATIC_KEY_FALSE(have_neon);

व्योम poly1305_init_arch(काष्ठा poly1305_desc_ctx *dctx, स्थिर u8 key[POLY1305_KEY_SIZE])
अणु
	poly1305_init_arm64(&dctx->h, key);
	dctx->s[0] = get_unaligned_le32(key + 16);
	dctx->s[1] = get_unaligned_le32(key + 20);
	dctx->s[2] = get_unaligned_le32(key + 24);
	dctx->s[3] = get_unaligned_le32(key + 28);
	dctx->buflen = 0;
पूर्ण
EXPORT_SYMBOL(poly1305_init_arch);

अटल पूर्णांक neon_poly1305_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा poly1305_desc_ctx *dctx = shash_desc_ctx(desc);

	dctx->buflen = 0;
	dctx->rset = 0;
	dctx->sset = false;

	वापस 0;
पूर्ण

अटल व्योम neon_poly1305_blocks(काष्ठा poly1305_desc_ctx *dctx, स्थिर u8 *src,
				 u32 len, u32 hibit, bool करो_neon)
अणु
	अगर (unlikely(!dctx->sset)) अणु
		अगर (!dctx->rset) अणु
			poly1305_init_arch(dctx, src);
			src += POLY1305_BLOCK_SIZE;
			len -= POLY1305_BLOCK_SIZE;
			dctx->rset = 1;
		पूर्ण
		अगर (len >= POLY1305_BLOCK_SIZE) अणु
			dctx->s[0] = get_unaligned_le32(src +  0);
			dctx->s[1] = get_unaligned_le32(src +  4);
			dctx->s[2] = get_unaligned_le32(src +  8);
			dctx->s[3] = get_unaligned_le32(src + 12);
			src += POLY1305_BLOCK_SIZE;
			len -= POLY1305_BLOCK_SIZE;
			dctx->sset = true;
		पूर्ण
		अगर (len < POLY1305_BLOCK_SIZE)
			वापस;
	पूर्ण

	len &= ~(POLY1305_BLOCK_SIZE - 1);

	अगर (अटल_branch_likely(&have_neon) && likely(करो_neon))
		poly1305_blocks_neon(&dctx->h, src, len, hibit);
	अन्यथा
		poly1305_blocks(&dctx->h, src, len, hibit);
पूर्ण

अटल व्योम neon_poly1305_करो_update(काष्ठा poly1305_desc_ctx *dctx,
				    स्थिर u8 *src, u32 len, bool करो_neon)
अणु
	अगर (unlikely(dctx->buflen)) अणु
		u32 bytes = min(len, POLY1305_BLOCK_SIZE - dctx->buflen);

		स_नकल(dctx->buf + dctx->buflen, src, bytes);
		src += bytes;
		len -= bytes;
		dctx->buflen += bytes;

		अगर (dctx->buflen == POLY1305_BLOCK_SIZE) अणु
			neon_poly1305_blocks(dctx, dctx->buf,
					     POLY1305_BLOCK_SIZE, 1, false);
			dctx->buflen = 0;
		पूर्ण
	पूर्ण

	अगर (likely(len >= POLY1305_BLOCK_SIZE)) अणु
		neon_poly1305_blocks(dctx, src, len, 1, करो_neon);
		src += round_करोwn(len, POLY1305_BLOCK_SIZE);
		len %= POLY1305_BLOCK_SIZE;
	पूर्ण

	अगर (unlikely(len)) अणु
		dctx->buflen = len;
		स_नकल(dctx->buf, src, len);
	पूर्ण
पूर्ण

अटल पूर्णांक neon_poly1305_update(काष्ठा shash_desc *desc,
				स्थिर u8 *src, अचिन्हित पूर्णांक srclen)
अणु
	bool करो_neon = crypto_simd_usable() && srclen > 128;
	काष्ठा poly1305_desc_ctx *dctx = shash_desc_ctx(desc);

	अगर (अटल_branch_likely(&have_neon) && करो_neon)
		kernel_neon_begin();
	neon_poly1305_करो_update(dctx, src, srclen, करो_neon);
	अगर (अटल_branch_likely(&have_neon) && करो_neon)
		kernel_neon_end();
	वापस 0;
पूर्ण

व्योम poly1305_update_arch(काष्ठा poly1305_desc_ctx *dctx, स्थिर u8 *src,
			  अचिन्हित पूर्णांक nbytes)
अणु
	अगर (unlikely(dctx->buflen)) अणु
		u32 bytes = min(nbytes, POLY1305_BLOCK_SIZE - dctx->buflen);

		स_नकल(dctx->buf + dctx->buflen, src, bytes);
		src += bytes;
		nbytes -= bytes;
		dctx->buflen += bytes;

		अगर (dctx->buflen == POLY1305_BLOCK_SIZE) अणु
			poly1305_blocks(&dctx->h, dctx->buf, POLY1305_BLOCK_SIZE, 1);
			dctx->buflen = 0;
		पूर्ण
	पूर्ण

	अगर (likely(nbytes >= POLY1305_BLOCK_SIZE)) अणु
		अचिन्हित पूर्णांक len = round_करोwn(nbytes, POLY1305_BLOCK_SIZE);

		अगर (अटल_branch_likely(&have_neon) && crypto_simd_usable()) अणु
			करो अणु
				अचिन्हित पूर्णांक toकरो = min_t(अचिन्हित पूर्णांक, len, SZ_4K);

				kernel_neon_begin();
				poly1305_blocks_neon(&dctx->h, src, toकरो, 1);
				kernel_neon_end();

				len -= toकरो;
				src += toकरो;
			पूर्ण जबतक (len);
		पूर्ण अन्यथा अणु
			poly1305_blocks(&dctx->h, src, len, 1);
			src += len;
		पूर्ण
		nbytes %= POLY1305_BLOCK_SIZE;
	पूर्ण

	अगर (unlikely(nbytes)) अणु
		dctx->buflen = nbytes;
		स_नकल(dctx->buf, src, nbytes);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(poly1305_update_arch);

व्योम poly1305_final_arch(काष्ठा poly1305_desc_ctx *dctx, u8 *dst)
अणु
	अगर (unlikely(dctx->buflen)) अणु
		dctx->buf[dctx->buflen++] = 1;
		स_रखो(dctx->buf + dctx->buflen, 0,
		       POLY1305_BLOCK_SIZE - dctx->buflen);
		poly1305_blocks(&dctx->h, dctx->buf, POLY1305_BLOCK_SIZE, 0);
	पूर्ण

	poly1305_emit(&dctx->h, dst, dctx->s);
	memzero_explicit(dctx, माप(*dctx));
पूर्ण
EXPORT_SYMBOL(poly1305_final_arch);

अटल पूर्णांक neon_poly1305_final(काष्ठा shash_desc *desc, u8 *dst)
अणु
	काष्ठा poly1305_desc_ctx *dctx = shash_desc_ctx(desc);

	अगर (unlikely(!dctx->sset))
		वापस -ENOKEY;

	poly1305_final_arch(dctx, dst);
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg neon_poly1305_alg = अणु
	.init			= neon_poly1305_init,
	.update			= neon_poly1305_update,
	.final			= neon_poly1305_final,
	.digestsize		= POLY1305_DIGEST_SIZE,
	.descsize		= माप(काष्ठा poly1305_desc_ctx),

	.base.cra_name		= "poly1305",
	.base.cra_driver_name	= "poly1305-neon",
	.base.cra_priority	= 200,
	.base.cra_blocksize	= POLY1305_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init neon_poly1305_mod_init(व्योम)
अणु
	अगर (!cpu_have_named_feature(ASIMD))
		वापस 0;

	अटल_branch_enable(&have_neon);

	वापस IS_REACHABLE(CONFIG_CRYPTO_HASH) ?
		crypto_रेजिस्टर_shash(&neon_poly1305_alg) : 0;
पूर्ण

अटल व्योम __निकास neon_poly1305_mod_निकास(व्योम)
अणु
	अगर (IS_REACHABLE(CONFIG_CRYPTO_HASH) && cpu_have_named_feature(ASIMD))
		crypto_unरेजिस्टर_shash(&neon_poly1305_alg);
पूर्ण

module_init(neon_poly1305_mod_init);
module_निकास(neon_poly1305_mod_निकास);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("poly1305");
MODULE_ALIAS_CRYPTO("poly1305-neon");
