<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * BLAKE2b digest algorithm, NEON accelerated
 *
 * Copyright 2020 Google LLC
 */

#समावेश <crypto/पूर्णांकernal/blake2b.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>

#समावेश <linux/module.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>

यंत्रlinkage व्योम blake2b_compress_neon(काष्ठा blake2b_state *state,
				      स्थिर u8 *block, माप_प्रकार nblocks, u32 inc);

अटल व्योम blake2b_compress_arch(काष्ठा blake2b_state *state,
				  स्थिर u8 *block, माप_प्रकार nblocks, u32 inc)
अणु
	अगर (!crypto_simd_usable()) अणु
		blake2b_compress_generic(state, block, nblocks, inc);
		वापस;
	पूर्ण

	करो अणु
		स्थिर माप_प्रकार blocks = min_t(माप_प्रकार, nblocks,
					    SZ_4K / BLAKE2B_BLOCK_SIZE);

		kernel_neon_begin();
		blake2b_compress_neon(state, block, blocks, inc);
		kernel_neon_end();

		nblocks -= blocks;
		block += blocks * BLAKE2B_BLOCK_SIZE;
	पूर्ण जबतक (nblocks);
पूर्ण

अटल पूर्णांक crypto_blake2b_update_neon(काष्ठा shash_desc *desc,
				      स्थिर u8 *in, अचिन्हित पूर्णांक inlen)
अणु
	वापस crypto_blake2b_update(desc, in, inlen, blake2b_compress_arch);
पूर्ण

अटल पूर्णांक crypto_blake2b_final_neon(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस crypto_blake2b_final(desc, out, blake2b_compress_arch);
पूर्ण

#घोषणा BLAKE2B_ALG(name, driver_name, digest_size)			\
	अणु								\
		.base.cra_name		= name,				\
		.base.cra_driver_name	= driver_name,			\
		.base.cra_priority	= 200,				\
		.base.cra_flags		= CRYPTO_ALG_OPTIONAL_KEY,	\
		.base.cra_blocksize	= BLAKE2B_BLOCK_SIZE,		\
		.base.cra_ctxsize	= माप(काष्ठा blake2b_tfm_ctx), \
		.base.cra_module	= THIS_MODULE,			\
		.digestsize		= digest_size,			\
		.setkey			= crypto_blake2b_setkey,	\
		.init			= crypto_blake2b_init,		\
		.update			= crypto_blake2b_update_neon,	\
		.final			= crypto_blake2b_final_neon,	\
		.descsize		= माप(काष्ठा blake2b_state),	\
	पूर्ण

अटल काष्ठा shash_alg blake2b_neon_algs[] = अणु
	BLAKE2B_ALG("blake2b-160", "blake2b-160-neon", BLAKE2B_160_HASH_SIZE),
	BLAKE2B_ALG("blake2b-256", "blake2b-256-neon", BLAKE2B_256_HASH_SIZE),
	BLAKE2B_ALG("blake2b-384", "blake2b-384-neon", BLAKE2B_384_HASH_SIZE),
	BLAKE2B_ALG("blake2b-512", "blake2b-512-neon", BLAKE2B_512_HASH_SIZE),
पूर्ण;

अटल पूर्णांक __init blake2b_neon_mod_init(व्योम)
अणु
	अगर (!(elf_hwcap & HWCAP_NEON))
		वापस -ENODEV;

	वापस crypto_रेजिस्टर_shashes(blake2b_neon_algs,
				       ARRAY_SIZE(blake2b_neon_algs));
पूर्ण

अटल व्योम __निकास blake2b_neon_mod_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(blake2b_neon_algs,
				  ARRAY_SIZE(blake2b_neon_algs));
पूर्ण

module_init(blake2b_neon_mod_init);
module_निकास(blake2b_neon_mod_निकास);

MODULE_DESCRIPTION("BLAKE2b digest algorithm, NEON accelerated");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eric Biggers <ebiggers@google.com>");
MODULE_ALIAS_CRYPTO("blake2b-160");
MODULE_ALIAS_CRYPTO("blake2b-160-neon");
MODULE_ALIAS_CRYPTO("blake2b-256");
MODULE_ALIAS_CRYPTO("blake2b-256-neon");
MODULE_ALIAS_CRYPTO("blake2b-384");
MODULE_ALIAS_CRYPTO("blake2b-384-neon");
MODULE_ALIAS_CRYPTO("blake2b-512");
MODULE_ALIAS_CRYPTO("blake2b-512-neon");
