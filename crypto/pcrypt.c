<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pcrypt - Parallel crypto wrapper.
 *
 * Copyright (C) 2009 secunet Security Networks AG
 * Copyright (C) 2009 Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 */

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <linux/atomic.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/kobject.h>
#समावेश <linux/cpu.h>
#समावेश <crypto/pcrypt.h>

अटल काष्ठा padata_instance *pencrypt;
अटल काष्ठा padata_instance *pdecrypt;
अटल काष्ठा kset           *pcrypt_kset;

काष्ठा pcrypt_instance_ctx अणु
	काष्ठा crypto_aead_spawn spawn;
	काष्ठा padata_shell *psenc;
	काष्ठा padata_shell *psdec;
	atomic_t tfm_count;
पूर्ण;

काष्ठा pcrypt_aead_ctx अणु
	काष्ठा crypto_aead *child;
	अचिन्हित पूर्णांक cb_cpu;
पूर्ण;

अटल अंतरभूत काष्ठा pcrypt_instance_ctx *pcrypt_tfm_ictx(
	काष्ठा crypto_aead *tfm)
अणु
	वापस aead_instance_ctx(aead_alg_instance(tfm));
पूर्ण

अटल पूर्णांक pcrypt_aead_setkey(काष्ठा crypto_aead *parent,
			      स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा pcrypt_aead_ctx *ctx = crypto_aead_ctx(parent);

	वापस crypto_aead_setkey(ctx->child, key, keylen);
पूर्ण

अटल पूर्णांक pcrypt_aead_setauthsize(काष्ठा crypto_aead *parent,
				   अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा pcrypt_aead_ctx *ctx = crypto_aead_ctx(parent);

	वापस crypto_aead_setauthsize(ctx->child, authsize);
पूर्ण

अटल व्योम pcrypt_aead_serial(काष्ठा padata_priv *padata)
अणु
	काष्ठा pcrypt_request *preq = pcrypt_padata_request(padata);
	काष्ठा aead_request *req = pcrypt_request_ctx(preq);

	aead_request_complete(req->base.data, padata->info);
पूर्ण

अटल व्योम pcrypt_aead_करोne(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा aead_request *req = areq->data;
	काष्ठा pcrypt_request *preq = aead_request_ctx(req);
	काष्ठा padata_priv *padata = pcrypt_request_padata(preq);

	padata->info = err;

	padata_करो_serial(padata);
पूर्ण

अटल व्योम pcrypt_aead_enc(काष्ठा padata_priv *padata)
अणु
	काष्ठा pcrypt_request *preq = pcrypt_padata_request(padata);
	काष्ठा aead_request *req = pcrypt_request_ctx(preq);

	padata->info = crypto_aead_encrypt(req);

	अगर (padata->info == -EINPROGRESS)
		वापस;

	padata_करो_serial(padata);
पूर्ण

अटल पूर्णांक pcrypt_aead_encrypt(काष्ठा aead_request *req)
अणु
	पूर्णांक err;
	काष्ठा pcrypt_request *preq = aead_request_ctx(req);
	काष्ठा aead_request *creq = pcrypt_request_ctx(preq);
	काष्ठा padata_priv *padata = pcrypt_request_padata(preq);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा pcrypt_aead_ctx *ctx = crypto_aead_ctx(aead);
	u32 flags = aead_request_flags(req);
	काष्ठा pcrypt_instance_ctx *ictx;

	ictx = pcrypt_tfm_ictx(aead);

	स_रखो(padata, 0, माप(काष्ठा padata_priv));

	padata->parallel = pcrypt_aead_enc;
	padata->serial = pcrypt_aead_serial;

	aead_request_set_tfm(creq, ctx->child);
	aead_request_set_callback(creq, flags & ~CRYPTO_TFM_REQ_MAY_SLEEP,
				  pcrypt_aead_करोne, req);
	aead_request_set_crypt(creq, req->src, req->dst,
			       req->cryptlen, req->iv);
	aead_request_set_ad(creq, req->assoclen);

	err = padata_करो_parallel(ictx->psenc, padata, &ctx->cb_cpu);
	अगर (!err)
		वापस -EINPROGRESS;

	वापस err;
पूर्ण

अटल व्योम pcrypt_aead_dec(काष्ठा padata_priv *padata)
अणु
	काष्ठा pcrypt_request *preq = pcrypt_padata_request(padata);
	काष्ठा aead_request *req = pcrypt_request_ctx(preq);

	padata->info = crypto_aead_decrypt(req);

	अगर (padata->info == -EINPROGRESS)
		वापस;

	padata_करो_serial(padata);
पूर्ण

अटल पूर्णांक pcrypt_aead_decrypt(काष्ठा aead_request *req)
अणु
	पूर्णांक err;
	काष्ठा pcrypt_request *preq = aead_request_ctx(req);
	काष्ठा aead_request *creq = pcrypt_request_ctx(preq);
	काष्ठा padata_priv *padata = pcrypt_request_padata(preq);
	काष्ठा crypto_aead *aead = crypto_aead_reqtfm(req);
	काष्ठा pcrypt_aead_ctx *ctx = crypto_aead_ctx(aead);
	u32 flags = aead_request_flags(req);
	काष्ठा pcrypt_instance_ctx *ictx;

	ictx = pcrypt_tfm_ictx(aead);

	स_रखो(padata, 0, माप(काष्ठा padata_priv));

	padata->parallel = pcrypt_aead_dec;
	padata->serial = pcrypt_aead_serial;

	aead_request_set_tfm(creq, ctx->child);
	aead_request_set_callback(creq, flags & ~CRYPTO_TFM_REQ_MAY_SLEEP,
				  pcrypt_aead_करोne, req);
	aead_request_set_crypt(creq, req->src, req->dst,
			       req->cryptlen, req->iv);
	aead_request_set_ad(creq, req->assoclen);

	err = padata_करो_parallel(ictx->psdec, padata, &ctx->cb_cpu);
	अगर (!err)
		वापस -EINPROGRESS;

	वापस err;
पूर्ण

अटल पूर्णांक pcrypt_aead_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	पूर्णांक cpu, cpu_index;
	काष्ठा aead_instance *inst = aead_alg_instance(tfm);
	काष्ठा pcrypt_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा pcrypt_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_aead *cipher;

	cpu_index = (अचिन्हित पूर्णांक)atomic_inc_वापस(&ictx->tfm_count) %
		    cpumask_weight(cpu_online_mask);

	ctx->cb_cpu = cpumask_first(cpu_online_mask);
	क्रम (cpu = 0; cpu < cpu_index; cpu++)
		ctx->cb_cpu = cpumask_next(ctx->cb_cpu, cpu_online_mask);

	cipher = crypto_spawn_aead(&ictx->spawn);

	अगर (IS_ERR(cipher))
		वापस PTR_ERR(cipher);

	ctx->child = cipher;
	crypto_aead_set_reqsize(tfm, माप(काष्ठा pcrypt_request) +
				     माप(काष्ठा aead_request) +
				     crypto_aead_reqsize(cipher));

	वापस 0;
पूर्ण

अटल व्योम pcrypt_aead_निकास_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा pcrypt_aead_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_मुक्त_aead(ctx->child);
पूर्ण

अटल व्योम pcrypt_मुक्त(काष्ठा aead_instance *inst)
अणु
	काष्ठा pcrypt_instance_ctx *ctx = aead_instance_ctx(inst);

	crypto_drop_aead(&ctx->spawn);
	padata_मुक्त_shell(ctx->psdec);
	padata_मुक्त_shell(ctx->psenc);
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक pcrypt_init_instance(काष्ठा crypto_instance *inst,
				काष्ठा crypto_alg *alg)
अणु
	अगर (snम_लिखो(inst->alg.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "pcrypt(%s)", alg->cra_driver_name) >= CRYPTO_MAX_ALG_NAME)
		वापस -ENAMETOOLONG;

	स_नकल(inst->alg.cra_name, alg->cra_name, CRYPTO_MAX_ALG_NAME);

	inst->alg.cra_priority = alg->cra_priority + 100;
	inst->alg.cra_blocksize = alg->cra_blocksize;
	inst->alg.cra_alignmask = alg->cra_alignmask;

	वापस 0;
पूर्ण

अटल पूर्णांक pcrypt_create_aead(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb,
			      काष्ठा crypto_attr_type *algt)
अणु
	काष्ठा pcrypt_instance_ctx *ctx;
	काष्ठा aead_instance *inst;
	काष्ठा aead_alg *alg;
	u32 mask = crypto_algt_inherited_mask(algt);
	पूर्णांक err;

	inst = kzalloc(माप(*inst) + माप(*ctx), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	err = -ENOMEM;

	ctx = aead_instance_ctx(inst);
	ctx->psenc = padata_alloc_shell(pencrypt);
	अगर (!ctx->psenc)
		जाओ err_मुक्त_inst;

	ctx->psdec = padata_alloc_shell(pdecrypt);
	अगर (!ctx->psdec)
		जाओ err_मुक्त_inst;

	err = crypto_grab_aead(&ctx->spawn, aead_crypto_instance(inst),
			       crypto_attr_alg_name(tb[1]), 0, mask);
	अगर (err)
		जाओ err_मुक्त_inst;

	alg = crypto_spawn_aead_alg(&ctx->spawn);
	err = pcrypt_init_instance(aead_crypto_instance(inst), &alg->base);
	अगर (err)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_flags |= CRYPTO_ALG_ASYNC;

	inst->alg.ivsize = crypto_aead_alg_ivsize(alg);
	inst->alg.maxauthsize = crypto_aead_alg_maxauthsize(alg);

	inst->alg.base.cra_ctxsize = माप(काष्ठा pcrypt_aead_ctx);

	inst->alg.init = pcrypt_aead_init_tfm;
	inst->alg.निकास = pcrypt_aead_निकास_tfm;

	inst->alg.setkey = pcrypt_aead_setkey;
	inst->alg.setauthsize = pcrypt_aead_setauthsize;
	inst->alg.encrypt = pcrypt_aead_encrypt;
	inst->alg.decrypt = pcrypt_aead_decrypt;

	inst->मुक्त = pcrypt_मुक्त;

	err = aead_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		pcrypt_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक pcrypt_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा crypto_attr_type *algt;

	algt = crypto_get_attr_type(tb);
	अगर (IS_ERR(algt))
		वापस PTR_ERR(algt);

	चयन (algt->type & algt->mask & CRYPTO_ALG_TYPE_MASK) अणु
	हाल CRYPTO_ALG_TYPE_AEAD:
		वापस pcrypt_create_aead(पंचांगpl, tb, algt);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pcrypt_sysfs_add(काष्ठा padata_instance *pinst, स्थिर अक्षर *name)
अणु
	पूर्णांक ret;

	pinst->kobj.kset = pcrypt_kset;
	ret = kobject_add(&pinst->kobj, शून्य, "%s", name);
	अगर (!ret)
		kobject_uevent(&pinst->kobj, KOBJ_ADD);

	वापस ret;
पूर्ण

अटल पूर्णांक pcrypt_init_padata(काष्ठा padata_instance **pinst, स्थिर अक्षर *name)
अणु
	पूर्णांक ret = -ENOMEM;

	*pinst = padata_alloc(name);
	अगर (!*pinst)
		वापस ret;

	ret = pcrypt_sysfs_add(*pinst, name);
	अगर (ret)
		padata_मुक्त(*pinst);

	वापस ret;
पूर्ण

अटल काष्ठा crypto_ढाँचा pcrypt_पंचांगpl = अणु
	.name = "pcrypt",
	.create = pcrypt_create,
	.module = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init pcrypt_init(व्योम)
अणु
	पूर्णांक err = -ENOMEM;

	pcrypt_kset = kset_create_and_add("pcrypt", शून्य, kernel_kobj);
	अगर (!pcrypt_kset)
		जाओ err;

	err = pcrypt_init_padata(&pencrypt, "pencrypt");
	अगर (err)
		जाओ err_unreg_kset;

	err = pcrypt_init_padata(&pdecrypt, "pdecrypt");
	अगर (err)
		जाओ err_deinit_pencrypt;

	वापस crypto_रेजिस्टर_ढाँचा(&pcrypt_पंचांगpl);

err_deinit_pencrypt:
	padata_मुक्त(pencrypt);
err_unreg_kset:
	kset_unरेजिस्टर(pcrypt_kset);
err:
	वापस err;
पूर्ण

अटल व्योम __निकास pcrypt_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_ढाँचा(&pcrypt_पंचांगpl);

	padata_मुक्त(pencrypt);
	padata_मुक्त(pdecrypt);

	kset_unरेजिस्टर(pcrypt_kset);
पूर्ण

subsys_initcall(pcrypt_init);
module_निकास(pcrypt_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Steffen Klassert <steffen.klassert@secunet.com>");
MODULE_DESCRIPTION("Parallel crypto wrapper");
MODULE_ALIAS_CRYPTO("pcrypt");
