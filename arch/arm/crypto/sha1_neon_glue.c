<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue code क्रम the SHA1 Secure Hash Algorithm assembler implementation using
 * ARM NEON inकाष्ठाions.
 *
 * Copyright तऊ 2014 Jussi Kivilinna <jussi.kivilinna@iki.fi>
 *
 * This file is based on sha1_generic.c and sha1_ssse3_glue.c:
 *  Copyright (c) Alan Smithee.
 *  Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 *  Copyright (c) Jean-Francois Dive <jef@linuxbe.org>
 *  Copyright (c) Mathias Krause <minipli@googlemail.com>
 *  Copyright (c) Chandramouli Narayanan <mouli@linux.पूर्णांकel.com>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha1_base.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>

#समावेश "sha1.h"

यंत्रlinkage व्योम sha1_transक्रमm_neon(व्योम *state_h, स्थिर अक्षर *data,
				    अचिन्हित पूर्णांक rounds);

अटल पूर्णांक sha1_neon_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			  अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable() ||
	    (sctx->count % SHA1_BLOCK_SIZE) + len < SHA1_BLOCK_SIZE)
		वापस sha1_update_arm(desc, data, len);

	kernel_neon_begin();
	sha1_base_करो_update(desc, data, len,
			    (sha1_block_fn *)sha1_transक्रमm_neon);
	kernel_neon_end();

	वापस 0;
पूर्ण

अटल पूर्णांक sha1_neon_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			   अचिन्हित पूर्णांक len, u8 *out)
अणु
	अगर (!crypto_simd_usable())
		वापस sha1_finup_arm(desc, data, len, out);

	kernel_neon_begin();
	अगर (len)
		sha1_base_करो_update(desc, data, len,
				    (sha1_block_fn *)sha1_transक्रमm_neon);
	sha1_base_करो_finalize(desc, (sha1_block_fn *)sha1_transक्रमm_neon);
	kernel_neon_end();

	वापस sha1_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha1_neon_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha1_neon_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	sha1_neon_update,
	.final		=	sha1_neon_final,
	.finup		=	sha1_neon_finup,
	.descsize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name		= "sha1",
		.cra_driver_name	= "sha1-neon",
		.cra_priority		= 250,
		.cra_blocksize		= SHA1_BLOCK_SIZE,
		.cra_module		= THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init sha1_neon_mod_init(व्योम)
अणु
	अगर (!cpu_has_neon())
		वापस -ENODEV;

	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास sha1_neon_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_init(sha1_neon_mod_init);
module_निकास(sha1_neon_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA1 Secure Hash Algorithm, NEON accelerated");
MODULE_ALIAS_CRYPTO("sha1");
