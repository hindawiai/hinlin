<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Crypto API wrapper क्रम the generic SHA256 code from lib/crypto/sha256.c
 *
 * Copyright (c) Jean-Luc Cooke <jlcooke@certainkey.com>
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * SHA224 Support Copyright 2007 Intel Corporation <jonathan.lynch@पूर्णांकel.com>
 */
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/sha256_base.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>

स्थिर u8 sha224_zero_message_hash[SHA224_DIGEST_SIZE] = अणु
	0xd1, 0x4a, 0x02, 0x8c, 0x2a, 0x3a, 0x2b, 0xc9, 0x47,
	0x61, 0x02, 0xbb, 0x28, 0x82, 0x34, 0xc4, 0x15, 0xa2,
	0xb0, 0x1f, 0x82, 0x8e, 0xa6, 0x2a, 0xc5, 0xb3, 0xe4,
	0x2f
पूर्ण;
EXPORT_SYMBOL_GPL(sha224_zero_message_hash);

स्थिर u8 sha256_zero_message_hash[SHA256_DIGEST_SIZE] = अणु
	0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14,
	0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24,
	0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c,
	0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55
पूर्ण;
EXPORT_SYMBOL_GPL(sha256_zero_message_hash);

अटल पूर्णांक crypto_sha256_init(काष्ठा shash_desc *desc)
अणु
	sha256_init(shash_desc_ctx(desc));
	वापस 0;
पूर्ण

अटल पूर्णांक crypto_sha224_init(काष्ठा shash_desc *desc)
अणु
	sha224_init(shash_desc_ctx(desc));
	वापस 0;
पूर्ण

पूर्णांक crypto_sha256_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			  अचिन्हित पूर्णांक len)
अणु
	sha256_update(shash_desc_ctx(desc), data, len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(crypto_sha256_update);

अटल पूर्णांक crypto_sha256_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	अगर (crypto_shash_digestsize(desc->tfm) == SHA224_DIGEST_SIZE)
		sha224_final(shash_desc_ctx(desc), out);
	अन्यथा
		sha256_final(shash_desc_ctx(desc), out);
	वापस 0;
पूर्ण

पूर्णांक crypto_sha256_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len, u8 *hash)
अणु
	sha256_update(shash_desc_ctx(desc), data, len);
	वापस crypto_sha256_final(desc, hash);
पूर्ण
EXPORT_SYMBOL(crypto_sha256_finup);

अटल काष्ठा shash_alg sha256_algs[2] = अणु अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	crypto_sha256_init,
	.update		=	crypto_sha256_update,
	.final		=	crypto_sha256_final,
	.finup		=	crypto_sha256_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha256",
		.cra_driver_name=	"sha256-generic",
		.cra_priority	=	100,
		.cra_blocksize	=	SHA256_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	crypto_sha224_init,
	.update		=	crypto_sha256_update,
	.final		=	crypto_sha256_final,
	.finup		=	crypto_sha256_finup,
	.descsize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha224",
		.cra_driver_name=	"sha224-generic",
		.cra_priority	=	100,
		.cra_blocksize	=	SHA224_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक __init sha256_generic_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shashes(sha256_algs, ARRAY_SIZE(sha256_algs));
पूर्ण

अटल व्योम __निकास sha256_generic_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(sha256_algs, ARRAY_SIZE(sha256_algs));
पूर्ण

subsys_initcall(sha256_generic_mod_init);
module_निकास(sha256_generic_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA-224 and SHA-256 Secure Hash Algorithm");

MODULE_ALIAS_CRYPTO("sha224");
MODULE_ALIAS_CRYPTO("sha224-generic");
MODULE_ALIAS_CRYPTO("sha256");
MODULE_ALIAS_CRYPTO("sha256-generic");
