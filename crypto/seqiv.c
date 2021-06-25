<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * seqiv: Sequence Number IV Generator
 *
 * This generator generates an IV based on a sequence number by xoring it
 * with a salt.  This algorithm is मुख्यly useful क्रम CTR and similar modes.
 *
 * Copyright (c) 2007 Herbert Xu <herbert@gonकरोr.apana.org.au>
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

अटल व्योम seqiv_aead_encrypt_complete2(काष्ठा aead_request *req, पूर्णांक err)
अणु
	काष्ठा aead_request *subreq = aead_request_ctx(req);
	काष्ठा crypto_aead *geniv;

	अगर (err == -EINPROGRESS)
		वापस;

	अगर (err)
		जाओ out;

	geniv = crypto_aead_reqtfm(req);
	स_नकल(req->iv, subreq->iv, crypto_aead_ivsize(geniv));

out:
	kमुक्त_sensitive(subreq->iv);
पूर्ण

अटल व्योम seqiv_aead_encrypt_complete(काष्ठा crypto_async_request *base,
					पूर्णांक err)
अणु
	काष्ठा aead_request *req = base->data;

	seqiv_aead_encrypt_complete2(req, err);
	aead_request_complete(req, err);
पूर्ण

अटल पूर्णांक seqiv_aead_encrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *geniv = crypto_aead_reqtfm(req);
	काष्ठा aead_geniv_ctx *ctx = crypto_aead_ctx(geniv);
	काष्ठा aead_request *subreq = aead_request_ctx(req);
	crypto_completion_t compl;
	व्योम *data;
	u8 *info;
	अचिन्हित पूर्णांक ivsize = 8;
	पूर्णांक err;

	अगर (req->cryptlen < ivsize)
		वापस -EINVAL;

	aead_request_set_tfm(subreq, ctx->child);

	compl = req->base.complete;
	data = req->base.data;
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

	अगर (unlikely(!IS_ALIGNED((अचिन्हित दीर्घ)info,
				 crypto_aead_alignmask(geniv) + 1))) अणु
		info = kmemdup(req->iv, ivsize, req->base.flags &
			       CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL :
			       GFP_ATOMIC);
		अगर (!info)
			वापस -ENOMEM;

		compl = seqiv_aead_encrypt_complete;
		data = req;
	पूर्ण

	aead_request_set_callback(subreq, req->base.flags, compl, data);
	aead_request_set_crypt(subreq, req->dst, req->dst,
			       req->cryptlen - ivsize, info);
	aead_request_set_ad(subreq, req->assoclen + ivsize);

	crypto_xor(info, ctx->salt, ivsize);
	scatterwalk_map_and_copy(info, req->dst, req->assoclen, ivsize, 1);

	err = crypto_aead_encrypt(subreq);
	अगर (unlikely(info != req->iv))
		seqiv_aead_encrypt_complete2(req, err);
	वापस err;
पूर्ण

अटल पूर्णांक seqiv_aead_decrypt(काष्ठा aead_request *req)
अणु
	काष्ठा crypto_aead *geniv = crypto_aead_reqtfm(req);
	काष्ठा aead_geniv_ctx *ctx = crypto_aead_ctx(geniv);
	काष्ठा aead_request *subreq = aead_request_ctx(req);
	crypto_completion_t compl;
	व्योम *data;
	अचिन्हित पूर्णांक ivsize = 8;

	अगर (req->cryptlen < ivsize + crypto_aead_authsize(geniv))
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

अटल पूर्णांक seqiv_aead_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा aead_instance *inst;
	पूर्णांक err;

	inst = aead_geniv_alloc(पंचांगpl, tb);

	अगर (IS_ERR(inst))
		वापस PTR_ERR(inst);

	err = -EINVAL;
	अगर (inst->alg.ivsize != माप(u64))
		जाओ मुक्त_inst;

	inst->alg.encrypt = seqiv_aead_encrypt;
	inst->alg.decrypt = seqiv_aead_decrypt;

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

अटल काष्ठा crypto_ढाँचा seqiv_पंचांगpl = अणु
	.name = "seqiv",
	.create = seqiv_aead_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init seqiv_module_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_ढाँचा(&seqiv_पंचांगpl);
पूर्ण

अटल व्योम __निकास seqiv_module_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&seqiv_पंचांगpl);
पूर्ण

subsys_initcall(seqiv_module_init);
module_निकास(seqiv_module_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Sequence Number IV Generator");
MODULE_ALIAS_CRYPTO("seqiv");
