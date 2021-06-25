<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sha512-neon-glue.c - accelerated SHA-384/512 क्रम ARM NEON
 *
 * Copyright (C) 2015 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha512_base.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/neon.h>

#समावेश "sha512.h"

MODULE_ALIAS_CRYPTO("sha384-neon");
MODULE_ALIAS_CRYPTO("sha512-neon");

यंत्रlinkage व्योम sha512_block_data_order_neon(u64 *state, u8 स्थिर *src,
					     पूर्णांक blocks);

अटल पूर्णांक sha512_neon_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha512_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable() ||
	    (sctx->count[0] % SHA512_BLOCK_SIZE) + len < SHA512_BLOCK_SIZE)
		वापस sha512_arm_update(desc, data, len);

	kernel_neon_begin();
	sha512_base_करो_update(desc, data, len,
		(sha512_block_fn *)sha512_block_data_order_neon);
	kernel_neon_end();

	वापस 0;
पूर्ण

अटल पूर्णांक sha512_neon_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			     अचिन्हित पूर्णांक len, u8 *out)
अणु
	अगर (!crypto_simd_usable())
		वापस sha512_arm_finup(desc, data, len, out);

	kernel_neon_begin();
	अगर (len)
		sha512_base_करो_update(desc, data, len,
			(sha512_block_fn *)sha512_block_data_order_neon);
	sha512_base_करो_finalize(desc,
		(sha512_block_fn *)sha512_block_data_order_neon);
	kernel_neon_end();

	वापस sha512_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha512_neon_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha512_neon_finup(desc, शून्य, 0, out);
पूर्ण

काष्ठा shash_alg sha512_neon_algs[] = अणु अणु
	.init			= sha384_base_init,
	.update			= sha512_neon_update,
	.final			= sha512_neon_final,
	.finup			= sha512_neon_finup,
	.descsize		= माप(काष्ठा sha512_state),
	.digestsize		= SHA384_DIGEST_SIZE,
	.base			= अणु
		.cra_name		= "sha384",
		.cra_driver_name	= "sha384-neon",
		.cra_priority		= 300,
		.cra_blocksize		= SHA384_BLOCK_SIZE,
		.cra_module		= THIS_MODULE,

	पूर्ण
पूर्ण,  अणु
	.init			= sha512_base_init,
	.update			= sha512_neon_update,
	.final			= sha512_neon_final,
	.finup			= sha512_neon_finup,
	.descsize		= माप(काष्ठा sha512_state),
	.digestsize		= SHA512_DIGEST_SIZE,
	.base			= अणु
		.cra_name		= "sha512",
		.cra_driver_name	= "sha512-neon",
		.cra_priority		= 300,
		.cra_blocksize		= SHA512_BLOCK_SIZE,
		.cra_module		= THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;
