<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ECB: Electronic CodeBook mode
 *
 * Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

अटल पूर्णांक crypto_ecb_crypt(काष्ठा skcipher_request *req,
			    काष्ठा crypto_cipher *cipher,
			    व्योम (*fn)(काष्ठा crypto_tfm *, u8 *, स्थिर u8 *))
अणु
	स्थिर अचिन्हित पूर्णांक bsize = crypto_cipher_blocksize(cipher);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes) != 0) अणु
		स्थिर u8 *src = walk.src.virt.addr;
		u8 *dst = walk.dst.virt.addr;

		करो अणु
			fn(crypto_cipher_tfm(cipher), dst, src);

			src += bsize;
			dst += bsize;
		पूर्ण जबतक ((nbytes -= bsize) >= bsize);

		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक crypto_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_cipher *cipher = skcipher_cipher_simple(tfm);

	वापस crypto_ecb_crypt(req, cipher,
				crypto_cipher_alg(cipher)->cia_encrypt);
पूर्ण

अटल पूर्णांक crypto_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_cipher *cipher = skcipher_cipher_simple(tfm);

	वापस crypto_ecb_crypt(req, cipher,
				crypto_cipher_alg(cipher)->cia_decrypt);
पूर्ण

अटल पूर्णांक crypto_ecb_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा skcipher_instance *inst;
	पूर्णांक err;

	inst = skcipher_alloc_instance_simple(पंचांगpl, tb);
	अगर (IS_ERR(inst))
		वापस PTR_ERR(inst);

	inst->alg.ivsize = 0; /* ECB mode करोesn't take an IV */

	inst->alg.encrypt = crypto_ecb_encrypt;
	inst->alg.decrypt = crypto_ecb_decrypt;

	err = skcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err)
		inst->मुक्त(inst);

	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा crypto_ecb_पंचांगpl = अणु
	.name = "ecb",
	.create = crypto_ecb_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init crypto_ecb_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&crypto_ecb_पंचांगpl);
पूर्ण

अटल व्योम __निकास crypto_ecb_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&crypto_ecb_पंचांगpl);
पूर्ण

subsys_initcall(crypto_ecb_module_init);
module_निकास(crypto_ecb_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ECB block cipher mode of operation");
MODULE_ALIAS_CRYPTO("ecb");
