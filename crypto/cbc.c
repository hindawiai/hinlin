<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CBC: Cipher Block Chaining mode
 *
 * Copyright (c) 2006-2016 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/cipher.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>

अटल पूर्णांक crypto_cbc_encrypt_segment(काष्ठा skcipher_walk *walk,
				      काष्ठा crypto_skcipher *skcipher)
अणु
	अचिन्हित पूर्णांक bsize = crypto_skcipher_blocksize(skcipher);
	व्योम (*fn)(काष्ठा crypto_tfm *, u8 *, स्थिर u8 *);
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u8 *src = walk->src.virt.addr;
	u8 *dst = walk->dst.virt.addr;
	काष्ठा crypto_cipher *cipher;
	काष्ठा crypto_tfm *tfm;
	u8 *iv = walk->iv;

	cipher = skcipher_cipher_simple(skcipher);
	tfm = crypto_cipher_tfm(cipher);
	fn = crypto_cipher_alg(cipher)->cia_encrypt;

	करो अणु
		crypto_xor(iv, src, bsize);
		fn(tfm, dst, iv);
		स_नकल(iv, dst, bsize);

		src += bsize;
		dst += bsize;
	पूर्ण जबतक ((nbytes -= bsize) >= bsize);

	वापस nbytes;
पूर्ण

अटल पूर्णांक crypto_cbc_encrypt_inplace(काष्ठा skcipher_walk *walk,
				      काष्ठा crypto_skcipher *skcipher)
अणु
	अचिन्हित पूर्णांक bsize = crypto_skcipher_blocksize(skcipher);
	व्योम (*fn)(काष्ठा crypto_tfm *, u8 *, स्थिर u8 *);
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u8 *src = walk->src.virt.addr;
	काष्ठा crypto_cipher *cipher;
	काष्ठा crypto_tfm *tfm;
	u8 *iv = walk->iv;

	cipher = skcipher_cipher_simple(skcipher);
	tfm = crypto_cipher_tfm(cipher);
	fn = crypto_cipher_alg(cipher)->cia_encrypt;

	करो अणु
		crypto_xor(src, iv, bsize);
		fn(tfm, src, src);
		iv = src;

		src += bsize;
	पूर्ण जबतक ((nbytes -= bsize) >= bsize);

	स_नकल(walk->iv, iv, bsize);

	वापस nbytes;
पूर्ण

अटल पूर्णांक crypto_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक (walk.nbytes) अणु
		अगर (walk.src.virt.addr == walk.dst.virt.addr)
			err = crypto_cbc_encrypt_inplace(&walk, skcipher);
		अन्यथा
			err = crypto_cbc_encrypt_segment(&walk, skcipher);
		err = skcipher_walk_करोne(&walk, err);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक crypto_cbc_decrypt_segment(काष्ठा skcipher_walk *walk,
				      काष्ठा crypto_skcipher *skcipher)
अणु
	अचिन्हित पूर्णांक bsize = crypto_skcipher_blocksize(skcipher);
	व्योम (*fn)(काष्ठा crypto_tfm *, u8 *, स्थिर u8 *);
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u8 *src = walk->src.virt.addr;
	u8 *dst = walk->dst.virt.addr;
	काष्ठा crypto_cipher *cipher;
	काष्ठा crypto_tfm *tfm;
	u8 *iv = walk->iv;

	cipher = skcipher_cipher_simple(skcipher);
	tfm = crypto_cipher_tfm(cipher);
	fn = crypto_cipher_alg(cipher)->cia_decrypt;

	करो अणु
		fn(tfm, dst, src);
		crypto_xor(dst, iv, bsize);
		iv = src;

		src += bsize;
		dst += bsize;
	पूर्ण जबतक ((nbytes -= bsize) >= bsize);

	स_नकल(walk->iv, iv, bsize);

	वापस nbytes;
पूर्ण

अटल पूर्णांक crypto_cbc_decrypt_inplace(काष्ठा skcipher_walk *walk,
				      काष्ठा crypto_skcipher *skcipher)
अणु
	अचिन्हित पूर्णांक bsize = crypto_skcipher_blocksize(skcipher);
	व्योम (*fn)(काष्ठा crypto_tfm *, u8 *, स्थिर u8 *);
	अचिन्हित पूर्णांक nbytes = walk->nbytes;
	u8 *src = walk->src.virt.addr;
	u8 last_iv[MAX_CIPHER_BLOCKSIZE];
	काष्ठा crypto_cipher *cipher;
	काष्ठा crypto_tfm *tfm;

	cipher = skcipher_cipher_simple(skcipher);
	tfm = crypto_cipher_tfm(cipher);
	fn = crypto_cipher_alg(cipher)->cia_decrypt;

	/* Start of the last block. */
	src += nbytes - (nbytes & (bsize - 1)) - bsize;
	स_नकल(last_iv, src, bsize);

	क्रम (;;) अणु
		fn(tfm, src, src);
		अगर ((nbytes -= bsize) < bsize)
			अवरोध;
		crypto_xor(src, src - bsize, bsize);
		src -= bsize;
	पूर्ण

	crypto_xor(src, walk->iv, bsize);
	स_नकल(walk->iv, last_iv, bsize);

	वापस nbytes;
पूर्ण

अटल पूर्णांक crypto_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	काष्ठा skcipher_walk walk;
	पूर्णांक err;

	err = skcipher_walk_virt(&walk, req, false);

	जबतक (walk.nbytes) अणु
		अगर (walk.src.virt.addr == walk.dst.virt.addr)
			err = crypto_cbc_decrypt_inplace(&walk, skcipher);
		अन्यथा
			err = crypto_cbc_decrypt_segment(&walk, skcipher);
		err = skcipher_walk_करोne(&walk, err);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक crypto_cbc_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा skcipher_instance *inst;
	काष्ठा crypto_alg *alg;
	पूर्णांक err;

	inst = skcipher_alloc_instance_simple(पंचांगpl, tb);
	अगर (IS_ERR(inst))
		वापस PTR_ERR(inst);

	alg = skcipher_ialg_simple(inst);

	err = -EINVAL;
	अगर (!is_घातer_of_2(alg->cra_blocksize))
		जाओ out_मुक्त_inst;

	inst->alg.encrypt = crypto_cbc_encrypt;
	inst->alg.decrypt = crypto_cbc_decrypt;

	err = skcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
out_मुक्त_inst:
		inst->मुक्त(inst);
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा crypto_cbc_पंचांगpl = अणु
	.name = "cbc",
	.create = crypto_cbc_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init crypto_cbc_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&crypto_cbc_पंचांगpl);
पूर्ण

अटल व्योम __निकास crypto_cbc_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&crypto_cbc_पंचांगpl);
पूर्ण

subsys_initcall(crypto_cbc_module_init);
module_निकास(crypto_cbc_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CBC block cipher mode of operation");
MODULE_ALIAS_CRYPTO("cbc");
