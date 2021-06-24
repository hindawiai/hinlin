<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PCBC: Propagating Cipher Block Chaining mode
 *
 * Copyright (C) 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * Derived from cbc.c
 * - Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

अटल पूर्णांक crypto_pcbc_encrypt_segment(काष्ठा skcipher_request *req,
				       काष्ठा skcipher_walk *walk,
				       काष्ठा crypto_cipher *tfm)
अणु
	पूर्णांक bsize = crypto_cipher_blocksize(tfm);
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u8 *src = walk->src.virt.addr;
	u8 *dst = walk->dst.virt.addr;
	u8 * स्थिर iv = walk->iv;

	करो अणु
		crypto_xor(iv, src, bsize);
		crypto_cipher_encrypt_one(tfm, dst, iv);
		crypto_xor_cpy(iv, dst, src, bsize);

		src += bsize;
		dst += bsize;
	पूर्ण जबतक ((nbytes -= bsize) >= bsize);

	वापस nbytes;
पूर्ण

अटल पूर्णांक crypto_pcbc_encrypt_inplace(काष्ठा skcipher_request *req,
				       काष्ठा skcipher_walk *walk,
				       काष्ठा crypto_cipher *tfm)
अणु
	पूर्णांक bsize = crypto_cipher_blocksize(tfm);
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u8 *src = walk->src.virt.addr;
	u8 * स्थिर iv = walk->iv;
	u8 पंचांगpbuf[MAX_CIPHER_BLOCKSIZE];

	करो अणु
		स_नकल(पंचांगpbuf, src, bsize);
		crypto_xor(iv, src, bsize);
		crypto_cipher_encrypt_one(tfm, src, iv);
		crypto_xor_cpy(iv, पंचांगpbuf, src, bsize);

		src += bsize;
	पूर्ण जबतक ((nbytes -= bsize) >= bsize);

	वापस nbytes;
पूर्ण

अटल पूर्णांक crypto_pcbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_cipher *cipher = skcipher_cipher_simple(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes)) अणु
		अगर (walk.src.virt.addr == walk.dst.virt.addr)
			nbytes = crypto_pcbc_encrypt_inplace(req, &walk,
							     cipher);
		अन्यथा
			nbytes = crypto_pcbc_encrypt_segment(req, &walk,
							     cipher);
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक crypto_pcbc_decrypt_segment(काष्ठा skcipher_request *req,
				       काष्ठा skcipher_walk *walk,
				       काष्ठा crypto_cipher *tfm)
अणु
	पूर्णांक bsize = crypto_cipher_blocksize(tfm);
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u8 *src = walk->src.virt.addr;
	u8 *dst = walk->dst.virt.addr;
	u8 * स्थिर iv = walk->iv;

	करो अणु
		crypto_cipher_decrypt_one(tfm, dst, src);
		crypto_xor(dst, iv, bsize);
		crypto_xor_cpy(iv, dst, src, bsize);

		src += bsize;
		dst += bsize;
	पूर्ण जबतक ((nbytes -= bsize) >= bsize);

	वापस nbytes;
पूर्ण

अटल पूर्णांक crypto_pcbc_decrypt_inplace(काष्ठा skcipher_request *req,
				       काष्ठा skcipher_walk *walk,
				       काष्ठा crypto_cipher *tfm)
अणु
	पूर्णांक bsize = crypto_cipher_blocksize(tfm);
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u8 *src = walk->src.virt.addr;
	u8 * स्थिर iv = walk->iv;
	u8 पंचांगpbuf[MAX_CIPHER_BLOCKSIZE] __aligned(__alignof__(u32));

	करो अणु
		स_नकल(पंचांगpbuf, src, bsize);
		crypto_cipher_decrypt_one(tfm, src, src);
		crypto_xor(src, iv, bsize);
		crypto_xor_cpy(iv, src, पंचांगpbuf, bsize);

		src += bsize;
	पूर्ण जबतक ((nbytes -= bsize) >= bsize);

	वापस nbytes;
पूर्ण

अटल पूर्णांक crypto_pcbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा crypto_cipher *cipher = skcipher_cipher_simple(tfm);
	काष्ठा skcipher_walk walk;
	अचिन्हित पूर्णांक nbytes;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक ((nbytes = walk.nbytes)) अणु
		अगर (walk.src.virt.addr == walk.dst.virt.addr)
			nbytes = crypto_pcbc_decrypt_inplace(req, &walk,
							     cipher);
		अन्यथा
			nbytes = crypto_pcbc_decrypt_segment(req, &walk,
							     cipher);
		err = skcipher_walk_करोne(&walk, nbytes);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक crypto_pcbc_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा skcipher_instance *inst;
	पूर्णांक err;

	inst = skcipher_alloc_instance_simple(पंचांगpl, tb);
	अगर (IS_ERR(inst))
		वापस PTR_ERR(inst);

	inst->alg.encrypt = crypto_pcbc_encrypt;
	inst->alg.decrypt = crypto_pcbc_decrypt;

	err = skcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err)
		inst->मुक्त(inst);

	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा crypto_pcbc_पंचांगpl = अणु
	.name = "pcbc",
	.create = crypto_pcbc_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init crypto_pcbc_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&crypto_pcbc_पंचांगpl);
पूर्ण

अटल व्योम __निकास crypto_pcbc_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&crypto_pcbc_पंचांगpl);
पूर्ण

subsys_initcall(crypto_pcbc_module_init);
module_निकास(crypto_pcbc_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PCBC block cipher mode of operation");
MODULE_ALIAS_CRYPTO("pcbc");
MODULE_IMPORT_NS(CRYPTO_INTERNAL);
