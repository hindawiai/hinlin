<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * echainiv: Encrypted Chain IV Generator
 *
 * This generator generates an IV based on a sequence number by multiplying
 * it with a salt and then encrypting it with the same key as used to encrypt
 * the plain text.  This algorithm requires that the block size be equal
 * to the IV size.  It is मुख्यly useful क्रम CBC.
 *
 * This generator can only be used by algorithms where authentication
 * is perक्रमmed after encryption (i.e., authenc).
 *
 * Copyright (c) 2015 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <crypto/पूर्णांकernal/geniv.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

अटल पूर्णांक echainiv_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *geniv = crypto_aead_reqtfm(req);
	काष्ठा aead_geniv_ctx *ctx = crypto_aead_ctx(geniv);
	काष्ठा aead_request *subreq = aead_request_ctx(req);
	__be64 nseqno;
	u64 seqno;
	u8 *info;
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(geniv);
	पूर्णांक err;

	अगर (req->cryptlen < ivsize)
		वापस -EINVAL;

	aead_request_set_tfm(subreq, ctx->child);

	info = req->iv;

	अगर (req->src != req->dst) अणु
		SYNC_SKCIPHER_REQUEST_ON_STACK(nreq, ctx->sknull);

		skcipher_request_set_sync_tfm(nreq, ctx->sknull);
		skcipher_request_set_callback(nreq, req->base.flags,
					      शून्य, शून्य);
		skcipher_request_set_crypt(nreq, req->src, req->dst,
					   req->assoclen + req->cryptlen,
					   शून्य);

		err = crypto_skcipher_encrypt(nreq);
		अगर (err)
			वापस err;
	पूर्ण

	aead_request_set_callback(subreq, req->base.flags,
				  req->base.complete, req->base.data);
	aead_request_set_crypt(subreq, req->dst, req->dst,
			       req->cryptlen, info);
	aead_request_set_ad(subreq, req->assoclen);

	स_नकल(&nseqno, info + ivsize - 8, 8);
	seqno = be64_to_cpu(nseqno);
	स_रखो(info, 0, ivsize);

	scatterwalk_map_and_copy(info, req->dst, req->assoclen, ivsize, 1);

	करो अणु
		u64 a;

		स_नकल(&a, ctx->salt + ivsize - 8, 8);

		a |= 1;
		a *= seqno;

		स_नकल(info + ivsize - 8, &a, 8);
	पूर्ण जबतक ((ivsize -= 8));

	वापस crypto_aead_encrypt(subreq);
पूर्ण

अटल पूर्णांक echainiv_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *geniv = crypto_aead_reqtfm(req);
	काष्ठा aead_geniv_ctx *ctx = crypto_aead_ctx(geniv);
	काष्ठा aead_request *subreq = aead_request_ctx(req);
	crypto_completion_t compl;
	व्योम *data;
	अचिन्हित पूर्णांक ivsize = crypto_aead_ivsize(geniv);

	अगर (req->cryptlen < ivsize)
		वापस -EINVAL;

	aead_request_set_tfm(subreq, ctx->child);

	compl = req->base.complete;
	data = req->base.data;

	aead_request_set_callback(subreq, req->base.flags, compl, data);
	aead_request_set_crypt(subreq, req->src, req->dst,
			       req->cryptlen - ivsize, req->iv);
	aead_request_set_ad(subreq, req->assoclen + ivsize);

	scatterwalk_map_and_copy(req->iv, req->src, req->assoclen, ivsize, 0);

	वापस crypto_aead_decrypt(subreq);
पूर्ण

अटल पूर्णांक echainiv_aead_create(काष्ठा crypto_ढाँचा *पंचांगpl,
				काष्ठा rtattr **tb)
अणु
	काष्ठा aead_instance *inst;
	पूर्णांक err;

	inst = aead_geniv_alloc(पंचांगpl, tb);

	अगर (IS_ERR(inst))
		वापस PTR_ERR(inst);

	err = -EINVAL;
	अगर (inst->alg.ivsize & (माप(u64) - 1) || !inst->alg.ivsize)
		जाओ मुक्त_inst;

	inst->alg.encrypt = echainiv_encrypt;
	inst->alg.decrypt = echainiv_decrypt;

	inst->alg.init = aead_init_geniv;
	inst->alg.निकास = aead_निकास_geniv;

	inst->alg.base.cra_ctxsize = माप(काष्ठा aead_geniv_ctx);
	inst->alg.base.cra_ctxsize += inst->alg.ivsize;

	err = aead_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
मुक्त_inst:
		inst->मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा crypto_ढाँचा echainiv_पंचांगpl = अणु
	.name = "echainiv",
	.create = echainiv_aead_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init echainiv_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&echainiv_पंचांगpl);
पूर्ण

अटल व्योम __निकास echainiv_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&echainiv_पंचांगpl);
पूर्ण

subsys_initcall(echainiv_module_init);
module_निकास(echainiv_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Encrypted Chain IV Generator");
MODULE_ALIAS_CRYPTO("echainiv");
