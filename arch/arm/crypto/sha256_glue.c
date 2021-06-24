<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue code क्रम the SHA256 Secure Hash Algorithm assembly implementation
 * using optimized ARM assembler and NEON inकाष्ठाions.
 *
 * Copyright तऊ 2015 Google Inc.
 *
 * This file is based on sha256_ssse3_glue.c:
 *   Copyright (C) 2013 Intel Corporation
 *   Author: Tim Chen <tim.c.chen@linux.पूर्णांकel.com>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/crypto.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha256_base.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/neon.h>

#समावेश "sha256_glue.h"

यंत्रlinkage व्योम sha256_block_data_order(u32 *digest, स्थिर व्योम *data,
					अचिन्हित पूर्णांक num_blks);

पूर्णांक crypto_sha256_arm_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			     अचिन्हित पूर्णांक len)
अणु
	/* make sure casting to sha256_block_fn() is safe */
	BUILD_BUG_ON(दुरत्व(काष्ठा sha256_state, state) != 0);

	वापस sha256_base_करो_update(desc, data, len,
				(sha256_block_fn *)sha256_block_data_order);
पूर्ण
EXPORT_SYMBOL(crypto_sha256_arm_update);

अटल पूर्णांक crypto_sha256_arm_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	sha256_base_करो_finalize(desc,
				(sha256_block_fn *)sha256_block_data_order);
	वापस sha256_base_finish(desc, out);
पूर्ण

पूर्णांक crypto_sha256_arm_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			    अचिन्हित पूर्णांक len, u8 *out)
अणु
	sha256_base_करो_update(desc, data, len,
			      (sha256_block_fn *)sha256_block_data_order);
	वापस crypto_sha256_arm_final(desc, out);
पूर्ण
EXPORT_SYMBOL(crypto_sha256_arm_finup);

अटल काष्ठा shash_alg algs[] = अणु अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	crypto_sha256_arm_update,
	.final		=	crypto_sha256_arm_final,
	.finup		=	crypto_sha256_arm_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha256",
		.cra_driver_name =	"sha256-asm",
		.cra_priority	=	150,
		.cra_blocksize	=	SHA256_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	crypto_sha256_arm_update,
	.final		=	crypto_sha256_arm_final,
	.finup		=	crypto_sha256_arm_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha224",
		.cra_driver_name =	"sha224-asm",
		.cra_priority	=	150,
		.cra_blocksize	=	SHA224_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक __init sha256_mod_init(व्योम)
अणु
	पूर्णांक res = crypto_रेजिस्टर_shashes(algs, ARRAY_SIZE(algs));

	अगर (res < 0)
		वापस res;

	अगर (IS_ENABLED(CONFIG_KERNEL_MODE_NEON) && cpu_has_neon()) अणु
		res = crypto_रेजिस्टर_shashes(sha256_neon_algs,
					      ARRAY_SIZE(sha256_neon_algs));

		अगर (res < 0)
			crypto_unरेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
	पूर्ण

	वापस res;
पूर्ण

अटल व्योम __निकास sha256_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(algs, ARRAY_SIZE(algs));

	अगर (IS_ENABLED(CONFIG_KERNEL_MODE_NEON) && cpu_has_neon())
		crypto_unरेजिस्टर_shashes(sha256_neon_algs,
					  ARRAY_SIZE(sha256_neon_algs));
पूर्ण

module_init(sha256_mod_init);
module_निकास(sha256_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA256 Secure Hash Algorithm (ARM), including NEON");

MODULE_ALIAS_CRYPTO("sha256");
