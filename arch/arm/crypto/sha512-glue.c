<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sha512-glue.c - accelerated SHA-384/512 क्रम ARM
 *
 * Copyright (C) 2015 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha512_base.h>
#समावेश <linux/crypto.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/neon.h>

#समावेश "sha512.h"

MODULE_DESCRIPTION("Accelerated SHA-384/SHA-512 secure hash for ARM");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");

MODULE_ALIAS_CRYPTO("sha384");
MODULE_ALIAS_CRYPTO("sha512");
MODULE_ALIAS_CRYPTO("sha384-arm");
MODULE_ALIAS_CRYPTO("sha512-arm");

यंत्रlinkage व्योम sha512_block_data_order(u64 *state, u8 स्थिर *src, पूर्णांक blocks);

पूर्णांक sha512_arm_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
		      अचिन्हित पूर्णांक len)
अणु
	वापस sha512_base_करो_update(desc, data, len,
		(sha512_block_fn *)sha512_block_data_order);
पूर्ण

अटल पूर्णांक sha512_arm_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	sha512_base_करो_finalize(desc,
		(sha512_block_fn *)sha512_block_data_order);
	वापस sha512_base_finish(desc, out);
पूर्ण

पूर्णांक sha512_arm_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
		     अचिन्हित पूर्णांक len, u8 *out)
अणु
	sha512_base_करो_update(desc, data, len,
		(sha512_block_fn *)sha512_block_data_order);
	वापस sha512_arm_final(desc, out);
पूर्ण

अटल काष्ठा shash_alg sha512_arm_algs[] = अणु अणु
	.init			= sha384_base_init,
	.update			= sha512_arm_update,
	.final			= sha512_arm_final,
	.finup			= sha512_arm_finup,
	.descsize		= माप(काष्ठा sha512_state),
	.digestsize		= SHA384_DIGEST_SIZE,
	.base			= अणु
		.cra_name		= "sha384",
		.cra_driver_name	= "sha384-arm",
		.cra_priority		= 250,
		.cra_blocksize		= SHA512_BLOCK_SIZE,
		.cra_module		= THIS_MODULE,
	पूर्ण
पूर्ण,  अणु
	.init			= sha512_base_init,
	.update			= sha512_arm_update,
	.final			= sha512_arm_final,
	.finup			= sha512_arm_finup,
	.descsize		= माप(काष्ठा sha512_state),
	.digestsize		= SHA512_DIGEST_SIZE,
	.base			= अणु
		.cra_name		= "sha512",
		.cra_driver_name	= "sha512-arm",
		.cra_priority		= 250,
		.cra_blocksize		= SHA512_BLOCK_SIZE,
		.cra_module		= THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक __init sha512_arm_mod_init(व्योम)
अणु
	पूर्णांक err;

	err = crypto_रेजिस्टर_shashes(sha512_arm_algs,
				      ARRAY_SIZE(sha512_arm_algs));
	अगर (err)
		वापस err;

	अगर (IS_ENABLED(CONFIG_KERNEL_MODE_NEON) && cpu_has_neon()) अणु
		err = crypto_रेजिस्टर_shashes(sha512_neon_algs,
					      ARRAY_SIZE(sha512_neon_algs));
		अगर (err)
			जाओ err_unरेजिस्टर;
	पूर्ण
	वापस 0;

err_unरेजिस्टर:
	crypto_unरेजिस्टर_shashes(sha512_arm_algs,
				  ARRAY_SIZE(sha512_arm_algs));

	वापस err;
पूर्ण

अटल व्योम __निकास sha512_arm_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(sha512_arm_algs,
				  ARRAY_SIZE(sha512_arm_algs));
	अगर (IS_ENABLED(CONFIG_KERNEL_MODE_NEON) && cpu_has_neon())
		crypto_unरेजिस्टर_shashes(sha512_neon_algs,
					  ARRAY_SIZE(sha512_neon_algs));
पूर्ण

module_init(sha512_arm_mod_init);
module_निकास(sha512_arm_mod_fini);
