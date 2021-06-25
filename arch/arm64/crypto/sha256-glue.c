<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux/arm64 port of the OpenSSL SHA256 implementation क्रम AArch64
 *
 * Copyright (c) 2016 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/simd.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/simd.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha256_base.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>

MODULE_DESCRIPTION("SHA-224/SHA-256 secure hash for arm64");
MODULE_AUTHOR("Andy Polyakov <appro@openssl.org>");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("sha224");
MODULE_ALIAS_CRYPTO("sha256");

यंत्रlinkage व्योम sha256_block_data_order(u32 *digest, स्थिर व्योम *data,
					अचिन्हित पूर्णांक num_blks);
EXPORT_SYMBOL(sha256_block_data_order);

अटल व्योम __sha256_block_data_order(काष्ठा sha256_state *sst, u8 स्थिर *src,
				      पूर्णांक blocks)
अणु
	sha256_block_data_order(sst->state, src, blocks);
पूर्ण

यंत्रlinkage व्योम sha256_block_neon(u32 *digest, स्थिर व्योम *data,
				  अचिन्हित पूर्णांक num_blks);

अटल व्योम __sha256_block_neon(काष्ठा sha256_state *sst, u8 स्थिर *src,
				पूर्णांक blocks)
अणु
	sha256_block_neon(sst->state, src, blocks);
पूर्ण

अटल पूर्णांक crypto_sha256_arm64_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
				      अचिन्हित पूर्णांक len)
अणु
	वापस sha256_base_करो_update(desc, data, len,
				     __sha256_block_data_order);
पूर्ण

अटल पूर्णांक crypto_sha256_arm64_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
				     अचिन्हित पूर्णांक len, u8 *out)
अणु
	अगर (len)
		sha256_base_करो_update(desc, data, len,
				      __sha256_block_data_order);
	sha256_base_करो_finalize(desc, __sha256_block_data_order);

	वापस sha256_base_finish(desc, out);
पूर्ण

अटल पूर्णांक crypto_sha256_arm64_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस crypto_sha256_arm64_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg algs[] = अणु अणु
	.digestsize		= SHA256_DIGEST_SIZE,
	.init			= sha256_base_init,
	.update			= crypto_sha256_arm64_update,
	.final			= crypto_sha256_arm64_final,
	.finup			= crypto_sha256_arm64_finup,
	.descsize		= माप(काष्ठा sha256_state),
	.base.cra_name		= "sha256",
	.base.cra_driver_name	= "sha256-arm64",
	.base.cra_priority	= 125,
	.base.cra_blocksize	= SHA256_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्ण, अणु
	.digestsize		= SHA224_DIGEST_SIZE,
	.init			= sha224_base_init,
	.update			= crypto_sha256_arm64_update,
	.final			= crypto_sha256_arm64_final,
	.finup			= crypto_sha256_arm64_finup,
	.descsize		= माप(काष्ठा sha256_state),
	.base.cra_name		= "sha224",
	.base.cra_driver_name	= "sha224-arm64",
	.base.cra_priority	= 125,
	.base.cra_blocksize	= SHA224_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्ण पूर्ण;

अटल पूर्णांक sha256_update_neon(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	अगर (!crypto_simd_usable())
		वापस sha256_base_करो_update(desc, data, len,
				__sha256_block_data_order);

	जबतक (len > 0) अणु
		अचिन्हित पूर्णांक chunk = len;

		/*
		 * Don't hog the CPU क्रम the entire समय it takes to process all
		 * input when running on a preemptible kernel, but process the
		 * data block by block instead.
		 */
		अगर (IS_ENABLED(CONFIG_PREEMPTION) &&
		    chunk + sctx->count % SHA256_BLOCK_SIZE > SHA256_BLOCK_SIZE)
			chunk = SHA256_BLOCK_SIZE -
				sctx->count % SHA256_BLOCK_SIZE;

		kernel_neon_begin();
		sha256_base_करो_update(desc, data, chunk, __sha256_block_neon);
		kernel_neon_end();
		data += chunk;
		len -= chunk;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sha256_finup_neon(काष्ठा shash_desc *desc, स्थिर u8 *data,
			     अचिन्हित पूर्णांक len, u8 *out)
अणु
	अगर (!crypto_simd_usable()) अणु
		अगर (len)
			sha256_base_करो_update(desc, data, len,
				__sha256_block_data_order);
		sha256_base_करो_finalize(desc, __sha256_block_data_order);
	पूर्ण अन्यथा अणु
		अगर (len)
			sha256_update_neon(desc, data, len);
		kernel_neon_begin();
		sha256_base_करो_finalize(desc, __sha256_block_neon);
		kernel_neon_end();
	पूर्ण
	वापस sha256_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha256_final_neon(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha256_finup_neon(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg neon_algs[] = अणु अणु
	.digestsize		= SHA256_DIGEST_SIZE,
	.init			= sha256_base_init,
	.update			= sha256_update_neon,
	.final			= sha256_final_neon,
	.finup			= sha256_finup_neon,
	.descsize		= माप(काष्ठा sha256_state),
	.base.cra_name		= "sha256",
	.base.cra_driver_name	= "sha256-arm64-neon",
	.base.cra_priority	= 150,
	.base.cra_blocksize	= SHA256_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्ण, अणु
	.digestsize		= SHA224_DIGEST_SIZE,
	.init			= sha224_base_init,
	.update			= sha256_update_neon,
	.final			= sha256_final_neon,
	.finup			= sha256_finup_neon,
	.descsize		= माप(काष्ठा sha256_state),
	.base.cra_name		= "sha224",
	.base.cra_driver_name	= "sha224-arm64-neon",
	.base.cra_priority	= 150,
	.base.cra_blocksize	= SHA224_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्ण पूर्ण;

अटल पूर्णांक __init sha256_mod_init(व्योम)
अणु
	पूर्णांक ret = crypto_रेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
	अगर (ret)
		वापस ret;

	अगर (cpu_have_named_feature(ASIMD)) अणु
		ret = crypto_रेजिस्टर_shashes(neon_algs, ARRAY_SIZE(neon_algs));
		अगर (ret)
			crypto_unरेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास sha256_mod_fini(व्योम)
अणु
	अगर (cpu_have_named_feature(ASIMD))
		crypto_unरेजिस्टर_shashes(neon_algs, ARRAY_SIZE(neon_algs));
	crypto_unरेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
पूर्ण

module_init(sha256_mod_init);
module_निकास(sha256_mod_fini);
