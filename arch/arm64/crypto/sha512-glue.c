<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux/arm64 port of the OpenSSL SHA512 implementation क्रम AArch64
 *
 * Copyright (c) 2016 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha512_base.h>
#समावेश <यंत्र/neon.h>

MODULE_DESCRIPTION("SHA-384/SHA-512 secure hash for arm64");
MODULE_AUTHOR("Andy Polyakov <appro@openssl.org>");
MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_CRYPTO("sha384");
MODULE_ALIAS_CRYPTO("sha512");

यंत्रlinkage व्योम sha512_block_data_order(u64 *digest, स्थिर व्योम *data,
					अचिन्हित पूर्णांक num_blks);
EXPORT_SYMBOL(sha512_block_data_order);

अटल व्योम __sha512_block_data_order(काष्ठा sha512_state *sst, u8 स्थिर *src,
				      पूर्णांक blocks)
अणु
	sha512_block_data_order(sst->state, src, blocks);
पूर्ण

अटल पूर्णांक sha512_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			 अचिन्हित पूर्णांक len)
अणु
	वापस sha512_base_करो_update(desc, data, len,
				     __sha512_block_data_order);
पूर्ण

अटल पूर्णांक sha512_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len, u8 *out)
अणु
	अगर (len)
		sha512_base_करो_update(desc, data, len,
				      __sha512_block_data_order);
	sha512_base_करो_finalize(desc, __sha512_block_data_order);

	वापस sha512_base_finish(desc, out);
पूर्ण

अटल पूर्णांक sha512_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस sha512_finup(desc, शून्य, 0, out);
पूर्ण

अटल काष्ठा shash_alg algs[] = अणु अणु
	.digestsize		= SHA512_DIGEST_SIZE,
	.init			= sha512_base_init,
	.update			= sha512_update,
	.final			= sha512_final,
	.finup			= sha512_finup,
	.descsize		= माप(काष्ठा sha512_state),
	.base.cra_name		= "sha512",
	.base.cra_driver_name	= "sha512-arm64",
	.base.cra_priority	= 150,
	.base.cra_blocksize	= SHA512_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्ण, अणु
	.digestsize		= SHA384_DIGEST_SIZE,
	.init			= sha384_base_init,
	.update			= sha512_update,
	.final			= sha512_final,
	.finup			= sha512_finup,
	.descsize		= माप(काष्ठा sha512_state),
	.base.cra_name		= "sha384",
	.base.cra_driver_name	= "sha384-arm64",
	.base.cra_priority	= 150,
	.base.cra_blocksize	= SHA384_BLOCK_SIZE,
	.base.cra_module	= THIS_MODULE,
पूर्ण पूर्ण;

अटल पूर्णांक __init sha512_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
पूर्ण

अटल व्योम __निकास sha512_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
पूर्ण

module_init(sha512_mod_init);
module_निकास(sha512_mod_fini);
