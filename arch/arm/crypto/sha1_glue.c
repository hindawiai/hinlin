<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 * Glue code क्रम the SHA1 Secure Hash Algorithm assembler implementation
 *
 * This file is based on sha1_generic.c and sha1_ssse3_glue.c
 *
 * Copyright (c) Alan Smithee.
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) Jean-Francois Dive <jef@linuxbe.org>
 * Copyright (c) Mathias Krause <minipli@googlemail.com>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha1_base.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "sha1.h"

यंत्रlinkage व्योम sha1_block_data_order(u32 *digest,
		स्थिर अचिन्हित अक्षर *data, अचिन्हित पूर्णांक rounds);

पूर्णांक sha1_update_arm(काष्ठा shash_desc *desc, स्थिर u8 *data,
		    अचिन्हित पूर्णांक len)
अणु
	/* make sure casting to sha1_block_fn() is safe */
	BUILD_BUG_ON(दुरत्व(काष्ठा sha1_state, state) != 0);

	वापस sha1_base_करो_update(desc, data, len,
				   (sha1_block_fn *)sha1_block_data_order);
पूर्ण
EXPORT_SYMBOL_GPL(sha1_update_arm);

अटल पूर्णांक sha1_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	sha1_base_करो_finalize(desc, (sha1_block_fn *)sha1_block_data_order);
	वापस sha1_base_finish(desc, out);
पूर्ण

पूर्णांक sha1_finup_arm(काष्ठा shash_desc *desc, स्थिर u8 *data,
		   अचिन्हित पूर्णांक len, u8 *out)
अणु
	sha1_base_करो_update(desc, data, len,
			    (sha1_block_fn *)sha1_block_data_order);
	वापस sha1_final(desc, out);
पूर्ण
EXPORT_SYMBOL_GPL(sha1_finup_arm);

अटल काष्ठा shash_alg alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	sha1_update_arm,
	.final		=	sha1_final,
	.finup		=	sha1_finup_arm,
	.descsize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name	=	"sha1",
		.cra_driver_name=	"sha1-asm",
		.cra_priority	=	150,
		.cra_blocksize	=	SHA1_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;


अटल पूर्णांक __init sha1_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण


अटल व्योम __निकास sha1_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण


module_init(sha1_mod_init);
module_निकास(sha1_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA1 Secure Hash Algorithm (ARM)");
MODULE_ALIAS_CRYPTO("sha1");
MODULE_AUTHOR("David McCullough <ucdevel@gmail.com>");
