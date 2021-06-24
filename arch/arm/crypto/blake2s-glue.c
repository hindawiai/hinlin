<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * BLAKE2s digest algorithm, ARM scalar implementation
 *
 * Copyright 2020 Google LLC
 */

#समावेश <crypto/पूर्णांकernal/blake2s.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

#समावेश <linux/module.h>

/* defined in blake2s-core.S */
EXPORT_SYMBOL(blake2s_compress_arch);

अटल पूर्णांक crypto_blake2s_update_arm(काष्ठा shash_desc *desc,
				     स्थिर u8 *in, अचिन्हित पूर्णांक inlen)
अणु
	वापस crypto_blake2s_update(desc, in, inlen, blake2s_compress_arch);
पूर्ण

अटल पूर्णांक crypto_blake2s_final_arm(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस crypto_blake2s_final(desc, out, blake2s_compress_arch);
पूर्ण

#घोषणा BLAKE2S_ALG(name, driver_name, digest_size)			\
	अणु								\
		.base.cra_name		= name,				\
		.base.cra_driver_name	= driver_name,			\
		.base.cra_priority	= 200,				\
		.base.cra_flags		= CRYPTO_ALG_OPTIONAL_KEY,	\
		.base.cra_blocksize	= BLAKE2S_BLOCK_SIZE,		\
		.base.cra_ctxsize	= माप(काष्ठा blake2s_tfm_ctx), \
		.base.cra_module	= THIS_MODULE,			\
		.digestsize		= digest_size,			\
		.setkey			= crypto_blake2s_setkey,	\
		.init			= crypto_blake2s_init,		\
		.update			= crypto_blake2s_update_arm,	\
		.final			= crypto_blake2s_final_arm,	\
		.descsize		= माप(काष्ठा blake2s_state),	\
	पूर्ण

अटल काष्ठा shash_alg blake2s_arm_algs[] = अणु
	BLAKE2S_ALG("blake2s-128", "blake2s-128-arm", BLAKE2S_128_HASH_SIZE),
	BLAKE2S_ALG("blake2s-160", "blake2s-160-arm", BLAKE2S_160_HASH_SIZE),
	BLAKE2S_ALG("blake2s-224", "blake2s-224-arm", BLAKE2S_224_HASH_SIZE),
	BLAKE2S_ALG("blake2s-256", "blake2s-256-arm", BLAKE2S_256_HASH_SIZE),
पूर्ण;

अटल पूर्णांक __init blake2s_arm_mod_init(व्योम)
अणु
	वापस IS_REACHABLE(CONFIG_CRYPTO_HASH) ?
		crypto_रेजिस्टर_shashes(blake2s_arm_algs,
					ARRAY_SIZE(blake2s_arm_algs)) : 0;
पूर्ण

अटल व्योम __निकास blake2s_arm_mod_निकास(व्योम)
अणु
	अगर (IS_REACHABLE(CONFIG_CRYPTO_HASH))
		crypto_unरेजिस्टर_shashes(blake2s_arm_algs,
					  ARRAY_SIZE(blake2s_arm_algs));
पूर्ण

module_init(blake2s_arm_mod_init);
module_निकास(blake2s_arm_mod_निकास);

MODULE_DESCRIPTION("BLAKE2s digest algorithm, ARM scalar implementation");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eric Biggers <ebiggers@google.com>");
MODULE_ALIAS_CRYPTO("blake2s-128");
MODULE_ALIAS_CRYPTO("blake2s-128-arm");
MODULE_ALIAS_CRYPTO("blake2s-160");
MODULE_ALIAS_CRYPTO("blake2s-160-arm");
MODULE_ALIAS_CRYPTO("blake2s-224");
MODULE_ALIAS_CRYPTO("blake2s-224-arm");
MODULE_ALIAS_CRYPTO("blake2s-256");
MODULE_ALIAS_CRYPTO("blake2s-256-arm");
