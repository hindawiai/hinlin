<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * SHA1 Secure Hash Algorithm.
 *
 * Derived from cryptoapi implementation, adapted क्रम in-place
 * scatterlist पूर्णांकerface.
 *
 * Copyright (c) Alan Smithee.
 * Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 * Copyright (c) Jean-Francois Dive <jef@linuxbe.org>
 */
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha1_base.h>
#समावेश <यंत्र/byteorder.h>

स्थिर u8 sha1_zero_message_hash[SHA1_DIGEST_SIZE] = अणु
	0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b, 0x0d,
	0x32, 0x55, 0xbf, 0xef, 0x95, 0x60, 0x18, 0x90,
	0xaf, 0xd8, 0x07, 0x09
पूर्ण;
EXPORT_SYMBOL_GPL(sha1_zero_message_hash);

अटल व्योम sha1_generic_block_fn(काष्ठा sha1_state *sst, u8 स्थिर *src,
				  पूर्णांक blocks)
अणु
	u32 temp[SHA1_WORKSPACE_WORDS];

	जबतक (blocks--) अणु
		sha1_transक्रमm(sst->state, src, temp);
		src += SHA1_BLOCK_SIZE;
	पूर्ण
	memzero_explicit(temp, माप(temp));
पूर्ण

पूर्णांक crypto_sha1_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
		       अचिन्हित पूर्णांक len)
अणु
	वापस sha1_base_करो_update(desc, data, len, sha1_generic_block_fn);
पूर्ण
EXPORT_SYMBOL(crypto_sha1_update);

अटल पूर्णांक sha1_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	sha1_base_करो_finalize(desc, sha1_generic_block_fn);
	वापस sha1_base_finish(desc, out);
पूर्ण

पूर्णांक crypto_sha1_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
		      अचिन्हित पूर्णांक len, u8 *out)
अणु
	sha1_base_करो_update(desc, data, len, sha1_generic_block_fn);
	वापस sha1_final(desc, out);
पूर्ण
EXPORT_SYMBOL(crypto_sha1_finup);

अटल काष्ठा shash_alg alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	crypto_sha1_update,
	.final		=	sha1_final,
	.finup		=	crypto_sha1_finup,
	.descsize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name	=	"sha1",
		.cra_driver_name=	"sha1-generic",
		.cra_priority	=	100,
		.cra_blocksize	=	SHA1_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init sha1_generic_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास sha1_generic_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

subsys_initcall(sha1_generic_mod_init);
module_निकास(sha1_generic_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA1 Secure Hash Algorithm");

MODULE_ALIAS_CRYPTO("sha1");
MODULE_ALIAS_CRYPTO("sha1-generic");
