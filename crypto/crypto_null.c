<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * Null algorithms, aka Much Aकरो About Nothing.
 *
 * These are needed क्रम IPsec, and may be useful in general क्रम
 * testing & debugging.
 *
 * The null cipher is compliant with RFC2410.
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 */

#समावेश <crypto/null.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>

अटल DEFINE_MUTEX(crypto_शेष_null_skcipher_lock);
अटल काष्ठा crypto_sync_skcipher *crypto_शेष_null_skcipher;
अटल पूर्णांक crypto_शेष_null_skcipher_refcnt;

अटल पूर्णांक null_compress(काष्ठा crypto_tfm *tfm, स्थिर u8 *src,
			 अचिन्हित पूर्णांक slen, u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	अगर (slen > *dlen)
		वापस -EINVAL;
	स_नकल(dst, src, slen);
	*dlen = slen;
	वापस 0;
पूर्ण

अटल पूर्णांक null_init(काष्ठा shash_desc *desc)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक null_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
		       अचिन्हित पूर्णांक len)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक null_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक null_digest(काष्ठा shash_desc *desc, स्थिर u8 *data,
		       अचिन्हित पूर्णांक len, u8 *out)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक null_hash_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *key,
			    अचिन्हित पूर्णांक keylen)
अणु वापस 0; पूर्ण

अटल पूर्णांक null_skcipher_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				अचिन्हित पूर्णांक keylen)
अणु वापस 0; पूर्ण

अटल पूर्णांक null_setkey(काष्ठा crypto_tfm *tfm, स्थिर u8 *key,
		       अचिन्हित पूर्णांक keylen)
अणु वापस 0; पूर्ण

अटल व्योम null_crypt(काष्ठा crypto_tfm *tfm, u8 *dst, स्थिर u8 *src)
अणु
	स_नकल(dst, src, शून्य_BLOCK_SIZE);
पूर्ण

अटल पूर्णांक null_skcipher_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक (walk.nbytes) अणु
		अगर (walk.src.virt.addr != walk.dst.virt.addr)
			स_नकल(walk.dst.virt.addr, walk.src.virt.addr,
			       walk.nbytes);
		err = skcipher_walk_करोne(&walk, 0);
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा shash_alg digest_null = अणु
	.digestsize		=	शून्य_DIGEST_SIZE,
	.setkey   		=	null_hash_setkey,
	.init   		=	null_init,
	.update 		=	null_update,
	.finup 			=	null_digest,
	.digest 		=	null_digest,
	.final  		=	null_final,
	.base			=	अणु
		.cra_name		=	"digest_null",
		.cra_driver_name	=	"digest_null-generic",
		.cra_blocksize		=	शून्य_BLOCK_SIZE,
		.cra_module		=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल काष्ठा skcipher_alg skcipher_null = अणु
	.base.cra_name		=	"ecb(cipher_null)",
	.base.cra_driver_name	=	"ecb-cipher_null",
	.base.cra_priority	=	100,
	.base.cra_blocksize	=	शून्य_BLOCK_SIZE,
	.base.cra_ctxsize	=	0,
	.base.cra_module	=	THIS_MODULE,
	.min_keysize		=	शून्य_KEY_SIZE,
	.max_keysize		=	शून्य_KEY_SIZE,
	.ivsize			=	शून्य_IV_SIZE,
	.setkey			=	null_skcipher_setkey,
	.encrypt		=	null_skcipher_crypt,
	.decrypt		=	null_skcipher_crypt,
पूर्ण;

अटल काष्ठा crypto_alg null_algs[] = अणु अणु
	.cra_name		=	"cipher_null",
	.cra_driver_name	=	"cipher_null-generic",
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	शून्य_BLOCK_SIZE,
	.cra_ctxsize		=	0,
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु .cipher = अणु
	.cia_min_keysize	=	शून्य_KEY_SIZE,
	.cia_max_keysize	=	शून्य_KEY_SIZE,
	.cia_setkey		= 	null_setkey,
	.cia_encrypt		=	null_crypt,
	.cia_decrypt		=	null_crypt पूर्ण पूर्ण
पूर्ण, अणु
	.cra_name		=	"compress_null",
	.cra_driver_name	=	"compress_null-generic",
	.cra_flags		=	CRYPTO_ALG_TYPE_COMPRESS,
	.cra_blocksize		=	शून्य_BLOCK_SIZE,
	.cra_ctxsize		=	0,
	.cra_module		=	THIS_MODULE,
	.cra_u			=	अणु .compress = अणु
	.coa_compress		=	null_compress,
	.coa_decompress		=	null_compress पूर्ण पूर्ण
पूर्ण पूर्ण;

MODULE_ALIAS_CRYPTO("compress_null");
MODULE_ALIAS_CRYPTO("digest_null");
MODULE_ALIAS_CRYPTO("cipher_null");

काष्ठा crypto_sync_skcipher *crypto_get_शेष_null_skcipher(व्योम)
अणु
	काष्ठा crypto_sync_skcipher *tfm;

	mutex_lock(&crypto_शेष_null_skcipher_lock);
	tfm = crypto_शेष_null_skcipher;

	अगर (!tfm) अणु
		tfm = crypto_alloc_sync_skcipher("ecb(cipher_null)", 0, 0);
		अगर (IS_ERR(tfm))
			जाओ unlock;

		crypto_शेष_null_skcipher = tfm;
	पूर्ण

	crypto_शेष_null_skcipher_refcnt++;

unlock:
	mutex_unlock(&crypto_शेष_null_skcipher_lock);

	वापस tfm;
पूर्ण
EXPORT_SYMBOL_GPL(crypto_get_शेष_null_skcipher);

व्योम crypto_put_शेष_null_skcipher(व्योम)
अणु
	mutex_lock(&crypto_शेष_null_skcipher_lock);
	अगर (!--crypto_शेष_null_skcipher_refcnt) अणु
		crypto_मुक्त_sync_skcipher(crypto_शेष_null_skcipher);
		crypto_शेष_null_skcipher = शून्य;
	पूर्ण
	mutex_unlock(&crypto_शेष_null_skcipher_lock);
पूर्ण
EXPORT_SYMBOL_GPL(crypto_put_शेष_null_skcipher);

अटल पूर्णांक __init crypto_null_mod_init(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = crypto_रेजिस्टर_algs(null_algs, ARRAY_SIZE(null_algs));
	अगर (ret < 0)
		जाओ out;

	ret = crypto_रेजिस्टर_shash(&digest_null);
	अगर (ret < 0)
		जाओ out_unरेजिस्टर_algs;

	ret = crypto_रेजिस्टर_skcipher(&skcipher_null);
	अगर (ret < 0)
		जाओ out_unरेजिस्टर_shash;

	वापस 0;

out_unरेजिस्टर_shash:
	crypto_unरेजिस्टर_shash(&digest_null);
out_unरेजिस्टर_algs:
	crypto_unरेजिस्टर_algs(null_algs, ARRAY_SIZE(null_algs));
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास crypto_null_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_algs(null_algs, ARRAY_SIZE(null_algs));
	crypto_unरेजिस्टर_shash(&digest_null);
	crypto_unरेजिस्टर_skcipher(&skcipher_null);
पूर्ण

subsys_initcall(crypto_null_mod_init);
module_निकास(crypto_null_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Null Cryptographic Algorithms");
