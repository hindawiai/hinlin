<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * GHASH routines supporting VMX inकाष्ठाions on the Power 8
 *
 * Copyright (C) 2015, 2019 International Business Machines Inc.
 *
 * Author: Marcelo Henrique Cerri <mhcerri@br.ibm.com>
 *
 * Extended by Daniel Axtens <dja@axtens.net> to replace the fallback
 * mechanism. The new approach is based on arm64 code, which is:
 *   Copyright (C) 2014 - 2018 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/crypto.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/ghash.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/b128ops.h>

व्योम gcm_init_p8(u128 htable[16], स्थिर u64 Xi[2]);
व्योम gcm_gmult_p8(u64 Xi[2], स्थिर u128 htable[16]);
व्योम gcm_ghash_p8(u64 Xi[2], स्थिर u128 htable[16],
		  स्थिर u8 *in, माप_प्रकार len);

काष्ठा p8_ghash_ctx अणु
	/* key used by vector यंत्र */
	u128 htable[16];
	/* key used by software fallback */
	be128 key;
पूर्ण;

काष्ठा p8_ghash_desc_ctx अणु
	u64 shash[2];
	u8 buffer[GHASH_DIGEST_SIZE];
	पूर्णांक bytes;
पूर्ण;

अटल पूर्णांक p8_ghash_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा p8_ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	dctx->bytes = 0;
	स_रखो(dctx->shash, 0, GHASH_DIGEST_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक p8_ghash_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *key,
			   अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा p8_ghash_ctx *ctx = crypto_tfm_ctx(crypto_shash_tfm(tfm));

	अगर (keylen != GHASH_BLOCK_SIZE)
		वापस -EINVAL;

	preempt_disable();
	pagefault_disable();
	enable_kernel_vsx();
	gcm_init_p8(ctx->htable, (स्थिर u64 *) key);
	disable_kernel_vsx();
	pagefault_enable();
	preempt_enable();

	स_नकल(&ctx->key, key, GHASH_BLOCK_SIZE);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __ghash_block(काष्ठा p8_ghash_ctx *ctx,
				 काष्ठा p8_ghash_desc_ctx *dctx)
अणु
	अगर (crypto_simd_usable()) अणु
		preempt_disable();
		pagefault_disable();
		enable_kernel_vsx();
		gcm_ghash_p8(dctx->shash, ctx->htable,
				dctx->buffer, GHASH_DIGEST_SIZE);
		disable_kernel_vsx();
		pagefault_enable();
		preempt_enable();
	पूर्ण अन्यथा अणु
		crypto_xor((u8 *)dctx->shash, dctx->buffer, GHASH_BLOCK_SIZE);
		gf128mul_lle((be128 *)dctx->shash, &ctx->key);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __ghash_blocks(काष्ठा p8_ghash_ctx *ctx,
				  काष्ठा p8_ghash_desc_ctx *dctx,
				  स्थिर u8 *src, अचिन्हित पूर्णांक srclen)
अणु
	अगर (crypto_simd_usable()) अणु
		preempt_disable();
		pagefault_disable();
		enable_kernel_vsx();
		gcm_ghash_p8(dctx->shash, ctx->htable,
				src, srclen);
		disable_kernel_vsx();
		pagefault_enable();
		preempt_enable();
	पूर्ण अन्यथा अणु
		जबतक (srclen >= GHASH_BLOCK_SIZE) अणु
			crypto_xor((u8 *)dctx->shash, src, GHASH_BLOCK_SIZE);
			gf128mul_lle((be128 *)dctx->shash, &ctx->key);
			srclen -= GHASH_BLOCK_SIZE;
			src += GHASH_BLOCK_SIZE;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक p8_ghash_update(काष्ठा shash_desc *desc,
			   स्थिर u8 *src, अचिन्हित पूर्णांक srclen)
अणु
	अचिन्हित पूर्णांक len;
	काष्ठा p8_ghash_ctx *ctx = crypto_tfm_ctx(crypto_shash_tfm(desc->tfm));
	काष्ठा p8_ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	अगर (dctx->bytes) अणु
		अगर (dctx->bytes + srclen < GHASH_DIGEST_SIZE) अणु
			स_नकल(dctx->buffer + dctx->bytes, src,
				srclen);
			dctx->bytes += srclen;
			वापस 0;
		पूर्ण
		स_नकल(dctx->buffer + dctx->bytes, src,
			GHASH_DIGEST_SIZE - dctx->bytes);

		__ghash_block(ctx, dctx);

		src += GHASH_DIGEST_SIZE - dctx->bytes;
		srclen -= GHASH_DIGEST_SIZE - dctx->bytes;
		dctx->bytes = 0;
	पूर्ण
	len = srclen & ~(GHASH_DIGEST_SIZE - 1);
	अगर (len) अणु
		__ghash_blocks(ctx, dctx, src, len);
		src += len;
		srclen -= len;
	पूर्ण
	अगर (srclen) अणु
		स_नकल(dctx->buffer, src, srclen);
		dctx->bytes = srclen;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक p8_ghash_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	पूर्णांक i;
	काष्ठा p8_ghash_ctx *ctx = crypto_tfm_ctx(crypto_shash_tfm(desc->tfm));
	काष्ठा p8_ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	अगर (dctx->bytes) अणु
		क्रम (i = dctx->bytes; i < GHASH_DIGEST_SIZE; i++)
			dctx->buffer[i] = 0;
		__ghash_block(ctx, dctx);
		dctx->bytes = 0;
	पूर्ण
	स_नकल(out, dctx->shash, GHASH_DIGEST_SIZE);
	वापस 0;
पूर्ण

काष्ठा shash_alg p8_ghash_alg = अणु
	.digestsize = GHASH_DIGEST_SIZE,
	.init = p8_ghash_init,
	.update = p8_ghash_update,
	.final = p8_ghash_final,
	.setkey = p8_ghash_setkey,
	.descsize = माप(काष्ठा p8_ghash_desc_ctx)
		+ माप(काष्ठा ghash_desc_ctx),
	.base = अणु
		 .cra_name = "ghash",
		 .cra_driver_name = "p8_ghash",
		 .cra_priority = 1000,
		 .cra_blocksize = GHASH_BLOCK_SIZE,
		 .cra_ctxsize = माप(काष्ठा p8_ghash_ctx),
		 .cra_module = THIS_MODULE,
	पूर्ण,
पूर्ण;
