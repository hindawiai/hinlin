<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * OFB: Output FeedBack mode
 *
 * Copyright (C) 2018 ARM Limited or its affiliates.
 * All rights reserved.
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

अटल पूर्णांक crypto_ofb_crypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_cipher *cipher = skcipher_cipher_simple(tfm);
	स्थिर अचिन्हित पूर्णांक bsize = crypto_cipher_blocksize(cipher);
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक (walk.nbytes >= bsize) अणु
		स्थिर u8 *src = walk.src.virt.addr;
		u8 *dst = walk.dst.virt.addr;
		u8 * स्थिर iv = walk.iv;
		अचिन्हित पूर्णांक nbytes = walk.nbytes;

		करो अणु
			crypto_cipher_encrypt_one(cipher, iv, iv);
			crypto_xor_cpy(dst, src, iv, bsize);
			dst += bsize;
			src += bsize;
		पूर्ण जबतक ((nbytes -= bsize) >= bsize);

		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	अगर (walk.nbytes) अणु
		crypto_cipher_encrypt_one(cipher, walk.iv, walk.iv);
		crypto_xor_cpy(walk.dst.virt.addr, walk.src.virt.addr, walk.iv,
			       walk.nbytes);
		err = skcipher_walk_करोne(&walk, 0);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक crypto_ofb_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा skcipher_instance *inst;
	काष्ठा crypto_alg *alg;
	पूर्णांक err;

	inst = skcipher_alloc_instance_simple(पंचांगpl, tb);
	अगर (IS_ERR(inst))
		वापस PTR_ERR(inst);

	alg = skcipher_ialg_simple(inst);

	/* OFB mode is a stream cipher. */
	inst->alg.base.cra_blocksize = 1;

	/*
	 * To simplअगरy the implementation, configure the skcipher walk to only
	 * give a partial block at the very end, never earlier.
	 */
	inst->alg.chunksize = alg->cra_blocksize;

	inst->alg.encrypt = crypto_ofb_crypt;
	inst->alg.decrypt = crypto_ofb_crypt;

	err = skcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err)
		inst->मुक्त(inst);

	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा crypto_ofb_पंचांगpl = अणु
	.name = "ofb",
	.create = crypto_ofb_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init crypto_ofb_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&crypto_ofb_पंचांगpl);
पूर्ण

अटल व्योम __निकास crypto_ofb_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&crypto_ofb_पंचांगpl);
पूर्ण

subsys_initcall(crypto_ofb_module_init);
module_निकास(crypto_ofb_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("OFB block cipher mode of operation");
MODULE_ALIAS_CRYPTO("ofb");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
