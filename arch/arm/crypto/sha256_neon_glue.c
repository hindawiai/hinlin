<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue code क्रम the SHA256 Secure Hash Algorithm assembly implementation
 * using NEON inकाष्ठाions.
 *
 * Copyright तऊ 2015 Google Inc.
 *
 * This file is based on sha512_neon_glue.c:
 *   Copyright तऊ 2014 Jussi Kivilinna <jussi.kivilinna@iki.fi>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha256_base.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/neon.h>

#समावेश "sha256_glue.h"

यंत्रlinkage व्योम sha256_block_data_order_neon(u32 *digest, स्थिर व्योम *data,
					     अचिन्हित पूर्णांक num_blks);

अटल पूर्णांक crypto_sha256_neon_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
				     अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable() ||
	    (sctx->count % SHA256_BLOCK_SIZE) + len < SHA256_BLOCK_SIZE)
		वापस crypto_sha256_arm_update(desc, data, len);

	kernel_neon_begin();
	sha256_base_करो_update(desc, data, len,
			(sha256_block_fn *)sha256_block_data_order_neon);
	kernel_neon_end();

	वापस 0;
पूर्ण

अटल पूर्णांक crypto_sha256_neon_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
				    अचिन्हित पूर्णांक len, u8 *out)
अणु
	अगर (!crypto_simd_usable())
		वापस crypto_sha256_arm_finup(desc, data, len, out);

	kernel_neon_begin();
	अगर (len)
		sha256_base_करो_update(desc, data, len,
			(sha256_block_fn *)sha256_block_data_order_neon);
	sha256_base_करो_finalize(desc,
			(sha256_block_fn *)sha256_block_data_order_neon);
	kernel_neon_end();

	वापस sha256_base_finish(desc, out);
पूर्ण

अटल पूर्णांक crypto_sha256_neon_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस crypto_sha256_neon_finup(desc, शून्य, 0, out);
पूर्ण

काष्ठा shash_alg sha256_neon_algs[] = अणु अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	crypto_sha256_neon_update,
	.final		=	crypto_sha256_neon_final,
	.finup		=	crypto_sha256_neon_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha256",
		.cra_driver_name =	"sha256-neon",
		.cra_priority	=	250,
		.cra_blocksize	=	SHA256_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	crypto_sha256_neon_update,
	.final		=	crypto_sha256_neon_final,
	.finup		=	crypto_sha256_neon_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha224",
		.cra_driver_name =	"sha224-neon",
		.cra_priority	=	250,
		.cra_blocksize	=	SHA224_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;
