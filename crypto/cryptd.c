<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Software async crypto daemon.
 *
 * Copyright (c) 2006 Herbert Xu <herbert@gonकरोr.apana.org.au>
 *
 * Added AEAD support to cryptd.
 *    Authors: Tadeusz Struk (tadeusz.struk@पूर्णांकel.com)
 *             Adrian Hoban <adrian.hoban@पूर्णांकel.com>
 *             Gabriele Paoloni <gabriele.paoloni@पूर्णांकel.com>
 *             Aidan O'Mahony (aidan.o.mahony@पूर्णांकel.com)
 *    Copyright (c) 2010, Intel Corporation.
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/cryptd.h>
#समावेश <linux/refcount.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

अटल अचिन्हित पूर्णांक cryptd_max_cpu_qlen = 1000;
module_param(cryptd_max_cpu_qlen, uपूर्णांक, 0);
MODULE_PARM_DESC(cryptd_max_cpu_qlen, "Set cryptd Max queue depth");

अटल काष्ठा workqueue_काष्ठा *cryptd_wq;

काष्ठा cryptd_cpu_queue अणु
	काष्ठा crypto_queue queue;
	काष्ठा work_काष्ठा work;
पूर्ण;

काष्ठा cryptd_queue अणु
	काष्ठा cryptd_cpu_queue __percpu *cpu_queue;
पूर्ण;

काष्ठा cryptd_instance_ctx अणु
	काष्ठा crypto_spawn spawn;
	काष्ठा cryptd_queue *queue;
पूर्ण;

काष्ठा skcipherd_instance_ctx अणु
	काष्ठा crypto_skcipher_spawn spawn;
	काष्ठा cryptd_queue *queue;
पूर्ण;

काष्ठा hashd_instance_ctx अणु
	काष्ठा crypto_shash_spawn spawn;
	काष्ठा cryptd_queue *queue;
पूर्ण;

काष्ठा aead_instance_ctx अणु
	काष्ठा crypto_aead_spawn aead_spawn;
	काष्ठा cryptd_queue *queue;
पूर्ण;

काष्ठा cryptd_skcipher_ctx अणु
	refcount_t refcnt;
	काष्ठा crypto_sync_skcipher *child;
पूर्ण;

काष्ठा cryptd_skcipher_request_ctx अणु
	crypto_completion_t complete;
पूर्ण;

काष्ठा cryptd_hash_ctx अणु
	refcount_t refcnt;
	काष्ठा crypto_shash *child;
पूर्ण;

काष्ठा cryptd_hash_request_ctx अणु
	crypto_completion_t complete;
	काष्ठा shash_desc desc;
पूर्ण;

काष्ठा cryptd_aead_ctx अणु
	refcount_t refcnt;
	काष्ठा crypto_aead *child;
पूर्ण;

काष्ठा cryptd_aead_request_ctx अणु
	crypto_completion_t complete;
पूर्ण;

अटल व्योम cryptd_queue_worker(काष्ठा work_काष्ठा *work);

अटल पूर्णांक cryptd_init_queue(काष्ठा cryptd_queue *queue,
			     अचिन्हित पूर्णांक max_cpu_qlen)
अणु
	पूर्णांक cpu;
	काष्ठा cryptd_cpu_queue *cpu_queue;

	queue->cpu_queue = alloc_percpu(काष्ठा cryptd_cpu_queue);
	अगर (!queue->cpu_queue)
		वापस -ENOMEM;
	क्रम_each_possible_cpu(cpu) अणु
		cpu_queue = per_cpu_ptr(queue->cpu_queue, cpu);
		crypto_init_queue(&cpu_queue->queue, max_cpu_qlen);
		INIT_WORK(&cpu_queue->work, cryptd_queue_worker);
	पूर्ण
	pr_info("cryptd: max_cpu_qlen set to %d\n", max_cpu_qlen);
	वापस 0;
पूर्ण

अटल व्योम cryptd_fini_queue(काष्ठा cryptd_queue *queue)
अणु
	पूर्णांक cpu;
	काष्ठा cryptd_cpu_queue *cpu_queue;

	क्रम_each_possible_cpu(cpu) अणु
		cpu_queue = per_cpu_ptr(queue->cpu_queue, cpu);
		BUG_ON(cpu_queue->queue.qlen);
	पूर्ण
	मुक्त_percpu(queue->cpu_queue);
पूर्ण

अटल पूर्णांक cryptd_enqueue_request(काष्ठा cryptd_queue *queue,
				  काष्ठा crypto_async_request *request)
अणु
	पूर्णांक cpu, err;
	काष्ठा cryptd_cpu_queue *cpu_queue;
	refcount_t *refcnt;

	cpu = get_cpu();
	cpu_queue = this_cpu_ptr(queue->cpu_queue);
	err = crypto_enqueue_request(&cpu_queue->queue, request);

	refcnt = crypto_tfm_ctx(request->tfm);

	अगर (err == -ENOSPC)
		जाओ out_put_cpu;

	queue_work_on(cpu, cryptd_wq, &cpu_queue->work);

	अगर (!refcount_पढ़ो(refcnt))
		जाओ out_put_cpu;

	refcount_inc(refcnt);

out_put_cpu:
	put_cpu();

	वापस err;
पूर्ण

/* Called in workqueue context, करो one real cryption work (via
 * req->complete) and reschedule itself अगर there are more work to
 * करो. */
अटल व्योम cryptd_queue_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cryptd_cpu_queue *cpu_queue;
	काष्ठा crypto_async_request *req, *backlog;

	cpu_queue = container_of(work, काष्ठा cryptd_cpu_queue, work);
	/*
	 * Only handle one request at a समय to aव्योम hogging crypto workqueue.
	 * preempt_disable/enable is used to prevent being preempted by
	 * cryptd_enqueue_request(). local_bh_disable/enable is used to prevent
	 * cryptd_enqueue_request() being accessed from software पूर्णांकerrupts.
	 */
	local_bh_disable();
	preempt_disable();
	backlog = crypto_get_backlog(&cpu_queue->queue);
	req = crypto_dequeue_request(&cpu_queue->queue);
	preempt_enable();
	local_bh_enable();

	अगर (!req)
		वापस;

	अगर (backlog)
		backlog->complete(backlog, -EINPROGRESS);
	req->complete(req, 0);

	अगर (cpu_queue->queue.qlen)
		queue_work(cryptd_wq, &cpu_queue->work);
पूर्ण

अटल अंतरभूत काष्ठा cryptd_queue *cryptd_get_queue(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_instance *inst = crypto_tfm_alg_instance(tfm);
	काष्ठा cryptd_instance_ctx *ictx = crypto_instance_ctx(inst);
	वापस ictx->queue;
पूर्ण

अटल व्योम cryptd_type_and_mask(काष्ठा crypto_attr_type *algt,
				 u32 *type, u32 *mask)
अणु
	/*
	 * cryptd is allowed to wrap पूर्णांकernal algorithms, but in that हाल the
	 * resulting cryptd instance will be marked as पूर्णांकernal as well.
	 */
	*type = algt->type & CRYPTO_ALG_INTERNAL;
	*mask = algt->mask & CRYPTO_ALG_INTERNAL;

	/* No poपूर्णांक in cryptd wrapping an algorithm that's alपढ़ोy async. */
	*mask |= CRYPTO_ALG_ASYNC;

	*mask |= crypto_algt_inherited_mask(algt);
पूर्ण

अटल पूर्णांक cryptd_init_instance(काष्ठा crypto_instance *inst,
				काष्ठा crypto_alg *alg)
अणु
	अगर (snम_लिखो(inst->alg.cra_driver_name, CRYPTO_MAX_ALG_NAME,
		     "cryptd(%s)",
		     alg->cra_driver_name) >= CRYPTO_MAX_ALG_NAME)
		वापस -ENAMETOOLONG;

	स_नकल(inst->alg.cra_name, alg->cra_name, CRYPTO_MAX_ALG_NAME);

	inst->alg.cra_priority = alg->cra_priority + 50;
	inst->alg.cra_blocksize = alg->cra_blocksize;
	inst->alg.cra_alignmask = alg->cra_alignmask;

	वापस 0;
पूर्ण

अटल पूर्णांक cryptd_skcipher_setkey(काष्ठा crypto_skcipher *parent,
				  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(parent);
	काष्ठा crypto_sync_skcipher *child = ctx->child;

	crypto_sync_skcipher_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_sync_skcipher_set_flags(child,
				       crypto_skcipher_get_flags(parent) &
					 CRYPTO_TFM_REQ_MASK);
	वापस crypto_sync_skcipher_setkey(child, key, keylen);
पूर्ण

अटल व्योम cryptd_skcipher_complete(काष्ठा skcipher_request *req, पूर्णांक err)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा cryptd_skcipher_request_ctx *rctx = skcipher_request_ctx(req);
	पूर्णांक refcnt = refcount_पढ़ो(&ctx->refcnt);

	local_bh_disable();
	rctx->complete(&req->base, err);
	local_bh_enable();

	अगर (err != -EINPROGRESS && refcnt && refcount_dec_and_test(&ctx->refcnt))
		crypto_मुक्त_skcipher(tfm);
पूर्ण

अटल व्योम cryptd_skcipher_encrypt(काष्ठा crypto_async_request *base,
				    पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(base);
	काष्ठा cryptd_skcipher_request_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_sync_skcipher *child = ctx->child;
	SYNC_SKCIPHER_REQUEST_ON_STACK(subreq, child);

	अगर (unlikely(err == -EINPROGRESS))
		जाओ out;

	skcipher_request_set_sync_tfm(subreq, child);
	skcipher_request_set_callback(subreq, CRYPTO_TFM_REQ_MAY_SLEEP,
				      शून्य, शून्य);
	skcipher_request_set_crypt(subreq, req->src, req->dst, req->cryptlen,
				   req->iv);

	err = crypto_skcipher_encrypt(subreq);
	skcipher_request_zero(subreq);

	req->base.complete = rctx->complete;

out:
	cryptd_skcipher_complete(req, err);
पूर्ण

अटल व्योम cryptd_skcipher_decrypt(काष्ठा crypto_async_request *base,
				    पूर्णांक err)
अणु
	काष्ठा skcipher_request *req = skcipher_request_cast(base);
	काष्ठा cryptd_skcipher_request_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_sync_skcipher *child = ctx->child;
	SYNC_SKCIPHER_REQUEST_ON_STACK(subreq, child);

	अगर (unlikely(err == -EINPROGRESS))
		जाओ out;

	skcipher_request_set_sync_tfm(subreq, child);
	skcipher_request_set_callback(subreq, CRYPTO_TFM_REQ_MAY_SLEEP,
				      शून्य, शून्य);
	skcipher_request_set_crypt(subreq, req->src, req->dst, req->cryptlen,
				   req->iv);

	err = crypto_skcipher_decrypt(subreq);
	skcipher_request_zero(subreq);

	req->base.complete = rctx->complete;

out:
	cryptd_skcipher_complete(req, err);
पूर्ण

अटल पूर्णांक cryptd_skcipher_enqueue(काष्ठा skcipher_request *req,
				   crypto_completion_t compl)
अणु
	काष्ठा cryptd_skcipher_request_ctx *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा cryptd_queue *queue;

	queue = cryptd_get_queue(crypto_skcipher_tfm(tfm));
	rctx->complete = req->base.complete;
	req->base.complete = compl;

	वापस cryptd_enqueue_request(queue, &req->base);
पूर्ण

अटल पूर्णांक cryptd_skcipher_encrypt_enqueue(काष्ठा skcipher_request *req)
अणु
	वापस cryptd_skcipher_enqueue(req, cryptd_skcipher_encrypt);
पूर्ण

अटल पूर्णांक cryptd_skcipher_decrypt_enqueue(काष्ठा skcipher_request *req)
अणु
	वापस cryptd_skcipher_enqueue(req, cryptd_skcipher_decrypt);
पूर्ण

अटल पूर्णांक cryptd_skcipher_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_instance *inst = skcipher_alg_instance(tfm);
	काष्ठा skcipherd_instance_ctx *ictx = skcipher_instance_ctx(inst);
	काष्ठा crypto_skcipher_spawn *spawn = &ictx->spawn;
	काष्ठा cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा crypto_skcipher *cipher;

	cipher = crypto_spawn_skcipher(spawn);
	अगर (IS_ERR(cipher))
		वापस PTR_ERR(cipher);

	ctx->child = (काष्ठा crypto_sync_skcipher *)cipher;
	crypto_skcipher_set_reqsize(
		tfm, माप(काष्ठा cryptd_skcipher_request_ctx));
	वापस 0;
पूर्ण

अटल व्योम cryptd_skcipher_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_sync_skcipher(ctx->child);
पूर्ण

अटल व्योम cryptd_skcipher_मुक्त(काष्ठा skcipher_instance *inst)
अणु
	काष्ठा skcipherd_instance_ctx *ctx = skcipher_instance_ctx(inst);

	crypto_drop_skcipher(&ctx->spawn);
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक cryptd_create_skcipher(काष्ठा crypto_ढाँचा *पंचांगpl,
				  काष्ठा rtattr **tb,
				  काष्ठा crypto_attr_type *algt,
				  काष्ठा cryptd_queue *queue)
अणु
	काष्ठा skcipherd_instance_ctx *ctx;
	काष्ठा skcipher_instance *inst;
	काष्ठा skcipher_alg *alg;
	u32 type;
	u32 mask;
	पूर्णांक err;

	cryptd_type_and_mask(algt, &type, &mask);

	inst = kzalloc(माप(*inst) + माप(*ctx), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	ctx = skcipher_instance_ctx(inst);
	ctx->queue = queue;

	err = crypto_grab_skcipher(&ctx->spawn, skcipher_crypto_instance(inst),
				   crypto_attr_alg_name(tb[1]), type, mask);
	अगर (err)
		जाओ err_मुक्त_inst;

	alg = crypto_spawn_skcipher_alg(&ctx->spawn);
	err = cryptd_init_instance(skcipher_crypto_instance(inst), &alg->base);
	अगर (err)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_flags |= CRYPTO_ALG_ASYNC |
		(alg->base.cra_flags & CRYPTO_ALG_INTERNAL);
	inst->alg.ivsize = crypto_skcipher_alg_ivsize(alg);
	inst->alg.chunksize = crypto_skcipher_alg_chunksize(alg);
	inst->alg.min_keysize = crypto_skcipher_alg_min_keysize(alg);
	inst->alg.max_keysize = crypto_skcipher_alg_max_keysize(alg);

	inst->alg.base.cra_ctxsize = माप(काष्ठा cryptd_skcipher_ctx);

	inst->alg.init = cryptd_skcipher_init_tfm;
	inst->alg.निकास = cryptd_skcipher_निकास_tfm;

	inst->alg.setkey = cryptd_skcipher_setkey;
	inst->alg.encrypt = cryptd_skcipher_encrypt_enqueue;
	inst->alg.decrypt = cryptd_skcipher_decrypt_enqueue;

	inst->मुक्त = cryptd_skcipher_मुक्त;

	err = skcipher_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		cryptd_skcipher_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cryptd_hash_init_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_instance *inst = crypto_tfm_alg_instance(tfm);
	काष्ठा hashd_instance_ctx *ictx = crypto_instance_ctx(inst);
	काष्ठा crypto_shash_spawn *spawn = &ictx->spawn;
	काष्ठा cryptd_hash_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा crypto_shash *hash;

	hash = crypto_spawn_shash(spawn);
	अगर (IS_ERR(hash))
		वापस PTR_ERR(hash);

	ctx->child = hash;
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा cryptd_hash_request_ctx) +
				 crypto_shash_descsize(hash));
	वापस 0;
पूर्ण

अटल व्योम cryptd_hash_निकास_tfm(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा cryptd_hash_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_shash(ctx->child);
पूर्ण

अटल पूर्णांक cryptd_hash_setkey(काष्ठा crypto_ahash *parent,
				   स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cryptd_hash_ctx *ctx   = crypto_ahash_ctx(parent);
	काष्ठा crypto_shash *child = ctx->child;

	crypto_shash_clear_flags(child, CRYPTO_TFM_REQ_MASK);
	crypto_shash_set_flags(child, crypto_ahash_get_flags(parent) &
				      CRYPTO_TFM_REQ_MASK);
	वापस crypto_shash_setkey(child, key, keylen);
पूर्ण

अटल पूर्णांक cryptd_hash_enqueue(काष्ठा ahash_request *req,
				crypto_completion_t compl)
अणु
	काष्ठा cryptd_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cryptd_queue *queue =
		cryptd_get_queue(crypto_ahash_tfm(tfm));

	rctx->complete = req->base.complete;
	req->base.complete = compl;

	वापस cryptd_enqueue_request(queue, &req->base);
पूर्ण

अटल व्योम cryptd_hash_complete(काष्ठा ahash_request *req, पूर्णांक err)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cryptd_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा cryptd_hash_request_ctx *rctx = ahash_request_ctx(req);
	पूर्णांक refcnt = refcount_पढ़ो(&ctx->refcnt);

	local_bh_disable();
	rctx->complete(&req->base, err);
	local_bh_enable();

	अगर (err != -EINPROGRESS && refcnt && refcount_dec_and_test(&ctx->refcnt))
		crypto_मुक्त_ahash(tfm);
पूर्ण

अटल व्योम cryptd_hash_init(काष्ठा crypto_async_request *req_async, पूर्णांक err)
अणु
	काष्ठा cryptd_hash_ctx *ctx = crypto_tfm_ctx(req_async->tfm);
	काष्ठा crypto_shash *child = ctx->child;
	काष्ठा ahash_request *req = ahash_request_cast(req_async);
	काष्ठा cryptd_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा shash_desc *desc = &rctx->desc;

	अगर (unlikely(err == -EINPROGRESS))
		जाओ out;

	desc->tfm = child;

	err = crypto_shash_init(desc);

	req->base.complete = rctx->complete;

out:
	cryptd_hash_complete(req, err);
पूर्ण

अटल पूर्णांक cryptd_hash_init_enqueue(काष्ठा ahash_request *req)
अणु
	वापस cryptd_hash_enqueue(req, cryptd_hash_init);
पूर्ण

अटल व्योम cryptd_hash_update(काष्ठा crypto_async_request *req_async, पूर्णांक err)
अणु
	काष्ठा ahash_request *req = ahash_request_cast(req_async);
	काष्ठा cryptd_hash_request_ctx *rctx;

	rctx = ahash_request_ctx(req);

	अगर (unlikely(err == -EINPROGRESS))
		जाओ out;

	err = shash_ahash_update(req, &rctx->desc);

	req->base.complete = rctx->complete;

out:
	cryptd_hash_complete(req, err);
पूर्ण

अटल पूर्णांक cryptd_hash_update_enqueue(काष्ठा ahash_request *req)
अणु
	वापस cryptd_hash_enqueue(req, cryptd_hash_update);
पूर्ण

अटल व्योम cryptd_hash_final(काष्ठा crypto_async_request *req_async, पूर्णांक err)
अणु
	काष्ठा ahash_request *req = ahash_request_cast(req_async);
	काष्ठा cryptd_hash_request_ctx *rctx = ahash_request_ctx(req);

	अगर (unlikely(err == -EINPROGRESS))
		जाओ out;

	err = crypto_shash_final(&rctx->desc, req->result);

	req->base.complete = rctx->complete;

out:
	cryptd_hash_complete(req, err);
पूर्ण

अटल पूर्णांक cryptd_hash_final_enqueue(काष्ठा ahash_request *req)
अणु
	वापस cryptd_hash_enqueue(req, cryptd_hash_final);
पूर्ण

अटल व्योम cryptd_hash_finup(काष्ठा crypto_async_request *req_async, पूर्णांक err)
अणु
	काष्ठा ahash_request *req = ahash_request_cast(req_async);
	काष्ठा cryptd_hash_request_ctx *rctx = ahash_request_ctx(req);

	अगर (unlikely(err == -EINPROGRESS))
		जाओ out;

	err = shash_ahash_finup(req, &rctx->desc);

	req->base.complete = rctx->complete;

out:
	cryptd_hash_complete(req, err);
पूर्ण

अटल पूर्णांक cryptd_hash_finup_enqueue(काष्ठा ahash_request *req)
अणु
	वापस cryptd_hash_enqueue(req, cryptd_hash_finup);
पूर्ण

अटल व्योम cryptd_hash_digest(काष्ठा crypto_async_request *req_async, पूर्णांक err)
अणु
	काष्ठा cryptd_hash_ctx *ctx = crypto_tfm_ctx(req_async->tfm);
	काष्ठा crypto_shash *child = ctx->child;
	काष्ठा ahash_request *req = ahash_request_cast(req_async);
	काष्ठा cryptd_hash_request_ctx *rctx = ahash_request_ctx(req);
	काष्ठा shash_desc *desc = &rctx->desc;

	अगर (unlikely(err == -EINPROGRESS))
		जाओ out;

	desc->tfm = child;

	err = shash_ahash_digest(req, desc);

	req->base.complete = rctx->complete;

out:
	cryptd_hash_complete(req, err);
पूर्ण

अटल पूर्णांक cryptd_hash_digest_enqueue(काष्ठा ahash_request *req)
अणु
	वापस cryptd_hash_enqueue(req, cryptd_hash_digest);
पूर्ण

अटल पूर्णांक cryptd_hash_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा cryptd_hash_request_ctx *rctx = ahash_request_ctx(req);

	वापस crypto_shash_export(&rctx->desc, out);
पूर्ण

अटल पूर्णांक cryptd_hash_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cryptd_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा shash_desc *desc = cryptd_shash_desc(req);

	desc->tfm = ctx->child;

	वापस crypto_shash_import(desc, in);
पूर्ण

अटल व्योम cryptd_hash_मुक्त(काष्ठा ahash_instance *inst)
अणु
	काष्ठा hashd_instance_ctx *ctx = ahash_instance_ctx(inst);

	crypto_drop_shash(&ctx->spawn);
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक cryptd_create_hash(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb,
			      काष्ठा crypto_attr_type *algt,
			      काष्ठा cryptd_queue *queue)
अणु
	काष्ठा hashd_instance_ctx *ctx;
	काष्ठा ahash_instance *inst;
	काष्ठा shash_alg *alg;
	u32 type;
	u32 mask;
	पूर्णांक err;

	cryptd_type_and_mask(algt, &type, &mask);

	inst = kzalloc(माप(*inst) + माप(*ctx), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	ctx = ahash_instance_ctx(inst);
	ctx->queue = queue;

	err = crypto_grab_shash(&ctx->spawn, ahash_crypto_instance(inst),
				crypto_attr_alg_name(tb[1]), type, mask);
	अगर (err)
		जाओ err_मुक्त_inst;
	alg = crypto_spawn_shash_alg(&ctx->spawn);

	err = cryptd_init_instance(ahash_crypto_instance(inst), &alg->base);
	अगर (err)
		जाओ err_मुक्त_inst;

	inst->alg.halg.base.cra_flags |= CRYPTO_ALG_ASYNC |
		(alg->base.cra_flags & (CRYPTO_ALG_INTERNAL|
					CRYPTO_ALG_OPTIONAL_KEY));
	inst->alg.halg.digestsize = alg->digestsize;
	inst->alg.halg.statesize = alg->statesize;
	inst->alg.halg.base.cra_ctxsize = माप(काष्ठा cryptd_hash_ctx);

	inst->alg.halg.base.cra_init = cryptd_hash_init_tfm;
	inst->alg.halg.base.cra_निकास = cryptd_hash_निकास_tfm;

	inst->alg.init   = cryptd_hash_init_enqueue;
	inst->alg.update = cryptd_hash_update_enqueue;
	inst->alg.final  = cryptd_hash_final_enqueue;
	inst->alg.finup  = cryptd_hash_finup_enqueue;
	inst->alg.export = cryptd_hash_export;
	inst->alg.import = cryptd_hash_import;
	अगर (crypto_shash_alg_has_setkey(alg))
		inst->alg.setkey = cryptd_hash_setkey;
	inst->alg.digest = cryptd_hash_digest_enqueue;

	inst->मुक्त = cryptd_hash_मुक्त;

	err = ahash_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		cryptd_hash_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cryptd_aead_setkey(काष्ठा crypto_aead *parent,
			      स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cryptd_aead_ctx *ctx = crypto_aead_ctx(parent);
	काष्ठा crypto_aead *child = ctx->child;

	वापस crypto_aead_setkey(child, key, keylen);
पूर्ण

अटल पूर्णांक cryptd_aead_setauthsize(काष्ठा crypto_aead *parent,
				   अचिन्हित पूर्णांक authsize)
अणु
	काष्ठा cryptd_aead_ctx *ctx = crypto_aead_ctx(parent);
	काष्ठा crypto_aead *child = ctx->child;

	वापस crypto_aead_setauthsize(child, authsize);
पूर्ण

अटल व्योम cryptd_aead_crypt(काष्ठा aead_request *req,
			काष्ठा crypto_aead *child,
			पूर्णांक err,
			पूर्णांक (*crypt)(काष्ठा aead_request *req))
अणु
	काष्ठा cryptd_aead_request_ctx *rctx;
	काष्ठा cryptd_aead_ctx *ctx;
	crypto_completion_t compl;
	काष्ठा crypto_aead *tfm;
	पूर्णांक refcnt;

	rctx = aead_request_ctx(req);
	compl = rctx->complete;

	tfm = crypto_aead_reqtfm(req);

	अगर (unlikely(err == -EINPROGRESS))
		जाओ out;
	aead_request_set_tfm(req, child);
	err = crypt( req );

out:
	ctx = crypto_aead_ctx(tfm);
	refcnt = refcount_पढ़ो(&ctx->refcnt);

	local_bh_disable();
	compl(&req->base, err);
	local_bh_enable();

	अगर (err != -EINPROGRESS && refcnt && refcount_dec_and_test(&ctx->refcnt))
		crypto_मुक्त_aead(tfm);
पूर्ण

अटल व्योम cryptd_aead_encrypt(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा cryptd_aead_ctx *ctx = crypto_tfm_ctx(areq->tfm);
	काष्ठा crypto_aead *child = ctx->child;
	काष्ठा aead_request *req;

	req = container_of(areq, काष्ठा aead_request, base);
	cryptd_aead_crypt(req, child, err, crypto_aead_alg(child)->encrypt);
पूर्ण

अटल व्योम cryptd_aead_decrypt(काष्ठा crypto_async_request *areq, पूर्णांक err)
अणु
	काष्ठा cryptd_aead_ctx *ctx = crypto_tfm_ctx(areq->tfm);
	काष्ठा crypto_aead *child = ctx->child;
	काष्ठा aead_request *req;

	req = container_of(areq, काष्ठा aead_request, base);
	cryptd_aead_crypt(req, child, err, crypto_aead_alg(child)->decrypt);
पूर्ण

अटल पूर्णांक cryptd_aead_enqueue(काष्ठा aead_request *req,
				    crypto_completion_t compl)
अणु
	काष्ठा cryptd_aead_request_ctx *rctx = aead_request_ctx(req);
	काष्ठा crypto_aead *tfm = crypto_aead_reqtfm(req);
	काष्ठा cryptd_queue *queue = cryptd_get_queue(crypto_aead_tfm(tfm));

	rctx->complete = req->base.complete;
	req->base.complete = compl;
	वापस cryptd_enqueue_request(queue, &req->base);
पूर्ण

अटल पूर्णांक cryptd_aead_encrypt_enqueue(काष्ठा aead_request *req)
अणु
	वापस cryptd_aead_enqueue(req, cryptd_aead_encrypt );
पूर्ण

अटल पूर्णांक cryptd_aead_decrypt_enqueue(काष्ठा aead_request *req)
अणु
	वापस cryptd_aead_enqueue(req, cryptd_aead_decrypt );
पूर्ण

अटल पूर्णांक cryptd_aead_init_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_instance *inst = aead_alg_instance(tfm);
	काष्ठा aead_instance_ctx *ictx = aead_instance_ctx(inst);
	काष्ठा crypto_aead_spawn *spawn = &ictx->aead_spawn;
	काष्ठा cryptd_aead_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto_aead *cipher;

	cipher = crypto_spawn_aead(spawn);
	अगर (IS_ERR(cipher))
		वापस PTR_ERR(cipher);

	ctx->child = cipher;
	crypto_aead_set_reqsize(
		tfm, max((अचिन्हित)माप(काष्ठा cryptd_aead_request_ctx),
			 crypto_aead_reqsize(cipher)));
	वापस 0;
पूर्ण

अटल व्योम cryptd_aead_निकास_tfm(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा cryptd_aead_ctx *ctx = crypto_aead_ctx(tfm);
	crypto_मुक्त_aead(ctx->child);
पूर्ण

अटल व्योम cryptd_aead_मुक्त(काष्ठा aead_instance *inst)
अणु
	काष्ठा aead_instance_ctx *ctx = aead_instance_ctx(inst);

	crypto_drop_aead(&ctx->aead_spawn);
	kमुक्त(inst);
पूर्ण

अटल पूर्णांक cryptd_create_aead(काष्ठा crypto_ढाँचा *पंचांगpl,
		              काष्ठा rtattr **tb,
			      काष्ठा crypto_attr_type *algt,
			      काष्ठा cryptd_queue *queue)
अणु
	काष्ठा aead_instance_ctx *ctx;
	काष्ठा aead_instance *inst;
	काष्ठा aead_alg *alg;
	u32 type;
	u32 mask;
	पूर्णांक err;

	cryptd_type_and_mask(algt, &type, &mask);

	inst = kzalloc(माप(*inst) + माप(*ctx), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	ctx = aead_instance_ctx(inst);
	ctx->queue = queue;

	err = crypto_grab_aead(&ctx->aead_spawn, aead_crypto_instance(inst),
			       crypto_attr_alg_name(tb[1]), type, mask);
	अगर (err)
		जाओ err_मुक्त_inst;

	alg = crypto_spawn_aead_alg(&ctx->aead_spawn);
	err = cryptd_init_instance(aead_crypto_instance(inst), &alg->base);
	अगर (err)
		जाओ err_मुक्त_inst;

	inst->alg.base.cra_flags |= CRYPTO_ALG_ASYNC |
		(alg->base.cra_flags & CRYPTO_ALG_INTERNAL);
	inst->alg.base.cra_ctxsize = माप(काष्ठा cryptd_aead_ctx);

	inst->alg.ivsize = crypto_aead_alg_ivsize(alg);
	inst->alg.maxauthsize = crypto_aead_alg_maxauthsize(alg);

	inst->alg.init = cryptd_aead_init_tfm;
	inst->alg.निकास = cryptd_aead_निकास_tfm;
	inst->alg.setkey = cryptd_aead_setkey;
	inst->alg.setauthsize = cryptd_aead_setauthsize;
	inst->alg.encrypt = cryptd_aead_encrypt_enqueue;
	inst->alg.decrypt = cryptd_aead_decrypt_enqueue;

	inst->मुक्त = cryptd_aead_मुक्त;

	err = aead_रेजिस्टर_instance(पंचांगpl, inst);
	अगर (err) अणु
err_मुक्त_inst:
		cryptd_aead_मुक्त(inst);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा cryptd_queue queue;

अटल पूर्णांक cryptd_create(काष्ठा crypto_ढाँचा *पंचांगpl, काष्ठा rtattr **tb)
अणु
	काष्ठा crypto_attr_type *algt;

	algt = crypto_get_attr_type(tb);
	अगर (IS_ERR(algt))
		वापस PTR_ERR(algt);

	चयन (algt->type & algt->mask & CRYPTO_ALG_TYPE_MASK) अणु
	हाल CRYPTO_ALG_TYPE_SKCIPHER:
		वापस cryptd_create_skcipher(पंचांगpl, tb, algt, &queue);
	हाल CRYPTO_ALG_TYPE_HASH:
		वापस cryptd_create_hash(पंचांगpl, tb, algt, &queue);
	हाल CRYPTO_ALG_TYPE_AEAD:
		वापस cryptd_create_aead(पंचांगpl, tb, algt, &queue);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल काष्ठा crypto_ढाँचा cryptd_पंचांगpl = अणु
	.name = "cryptd",
	.create = cryptd_create,
	.module = THIS_MODULE,
पूर्ण;

काष्ठा cryptd_skcipher *cryptd_alloc_skcipher(स्थिर अक्षर *alg_name,
					      u32 type, u32 mask)
अणु
	अक्षर cryptd_alg_name[CRYPTO_MAX_ALG_NAME];
	काष्ठा cryptd_skcipher_ctx *ctx;
	काष्ठा crypto_skcipher *tfm;

	अगर (snम_लिखो(cryptd_alg_name, CRYPTO_MAX_ALG_NAME,
		     "cryptd(%s)", alg_name) >= CRYPTO_MAX_ALG_NAME)
		वापस ERR_PTR(-EINVAL);

	tfm = crypto_alloc_skcipher(cryptd_alg_name, type, mask);
	अगर (IS_ERR(tfm))
		वापस ERR_CAST(tfm);

	अगर (tfm->base.__crt_alg->cra_module != THIS_MODULE) अणु
		crypto_मुक्त_skcipher(tfm);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ctx = crypto_skcipher_ctx(tfm);
	refcount_set(&ctx->refcnt, 1);

	वापस container_of(tfm, काष्ठा cryptd_skcipher, base);
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_alloc_skcipher);

काष्ठा crypto_skcipher *cryptd_skcipher_child(काष्ठा cryptd_skcipher *tfm)
अणु
	काष्ठा cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(&tfm->base);

	वापस &ctx->child->base;
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_skcipher_child);

bool cryptd_skcipher_queued(काष्ठा cryptd_skcipher *tfm)
अणु
	काष्ठा cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(&tfm->base);

	वापस refcount_पढ़ो(&ctx->refcnt) - 1;
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_skcipher_queued);

व्योम cryptd_मुक्त_skcipher(काष्ठा cryptd_skcipher *tfm)
अणु
	काष्ठा cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(&tfm->base);

	अगर (refcount_dec_and_test(&ctx->refcnt))
		crypto_मुक्त_skcipher(&tfm->base);
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_मुक्त_skcipher);

काष्ठा cryptd_ahash *cryptd_alloc_ahash(स्थिर अक्षर *alg_name,
					u32 type, u32 mask)
अणु
	अक्षर cryptd_alg_name[CRYPTO_MAX_ALG_NAME];
	काष्ठा cryptd_hash_ctx *ctx;
	काष्ठा crypto_ahash *tfm;

	अगर (snम_लिखो(cryptd_alg_name, CRYPTO_MAX_ALG_NAME,
		     "cryptd(%s)", alg_name) >= CRYPTO_MAX_ALG_NAME)
		वापस ERR_PTR(-EINVAL);
	tfm = crypto_alloc_ahash(cryptd_alg_name, type, mask);
	अगर (IS_ERR(tfm))
		वापस ERR_CAST(tfm);
	अगर (tfm->base.__crt_alg->cra_module != THIS_MODULE) अणु
		crypto_मुक्त_ahash(tfm);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ctx = crypto_ahash_ctx(tfm);
	refcount_set(&ctx->refcnt, 1);

	वापस __cryptd_ahash_cast(tfm);
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_alloc_ahash);

काष्ठा crypto_shash *cryptd_ahash_child(काष्ठा cryptd_ahash *tfm)
अणु
	काष्ठा cryptd_hash_ctx *ctx = crypto_ahash_ctx(&tfm->base);

	वापस ctx->child;
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_ahash_child);

काष्ठा shash_desc *cryptd_shash_desc(काष्ठा ahash_request *req)
अणु
	काष्ठा cryptd_hash_request_ctx *rctx = ahash_request_ctx(req);
	वापस &rctx->desc;
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_shash_desc);

bool cryptd_ahash_queued(काष्ठा cryptd_ahash *tfm)
अणु
	काष्ठा cryptd_hash_ctx *ctx = crypto_ahash_ctx(&tfm->base);

	वापस refcount_पढ़ो(&ctx->refcnt) - 1;
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_ahash_queued);

व्योम cryptd_मुक्त_ahash(काष्ठा cryptd_ahash *tfm)
अणु
	काष्ठा cryptd_hash_ctx *ctx = crypto_ahash_ctx(&tfm->base);

	अगर (refcount_dec_and_test(&ctx->refcnt))
		crypto_मुक्त_ahash(&tfm->base);
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_मुक्त_ahash);

काष्ठा cryptd_aead *cryptd_alloc_aead(स्थिर अक्षर *alg_name,
						  u32 type, u32 mask)
अणु
	अक्षर cryptd_alg_name[CRYPTO_MAX_ALG_NAME];
	काष्ठा cryptd_aead_ctx *ctx;
	काष्ठा crypto_aead *tfm;

	अगर (snम_लिखो(cryptd_alg_name, CRYPTO_MAX_ALG_NAME,
		     "cryptd(%s)", alg_name) >= CRYPTO_MAX_ALG_NAME)
		वापस ERR_PTR(-EINVAL);
	tfm = crypto_alloc_aead(cryptd_alg_name, type, mask);
	अगर (IS_ERR(tfm))
		वापस ERR_CAST(tfm);
	अगर (tfm->base.__crt_alg->cra_module != THIS_MODULE) अणु
		crypto_मुक्त_aead(tfm);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ctx = crypto_aead_ctx(tfm);
	refcount_set(&ctx->refcnt, 1);

	वापस __cryptd_aead_cast(tfm);
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_alloc_aead);

काष्ठा crypto_aead *cryptd_aead_child(काष्ठा cryptd_aead *tfm)
अणु
	काष्ठा cryptd_aead_ctx *ctx;
	ctx = crypto_aead_ctx(&tfm->base);
	वापस ctx->child;
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_aead_child);

bool cryptd_aead_queued(काष्ठा cryptd_aead *tfm)
अणु
	काष्ठा cryptd_aead_ctx *ctx = crypto_aead_ctx(&tfm->base);

	वापस refcount_पढ़ो(&ctx->refcnt) - 1;
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_aead_queued);

व्योम cryptd_मुक्त_aead(काष्ठा cryptd_aead *tfm)
अणु
	काष्ठा cryptd_aead_ctx *ctx = crypto_aead_ctx(&tfm->base);

	अगर (refcount_dec_and_test(&ctx->refcnt))
		crypto_मुक्त_aead(&tfm->base);
पूर्ण
EXPORT_SYMBOL_GPL(cryptd_मुक्त_aead);

अटल पूर्णांक __init cryptd_init(व्योम)
अणु
	पूर्णांक err;

	cryptd_wq = alloc_workqueue("cryptd", WQ_MEM_RECLAIM | WQ_CPU_INTENSIVE,
				    1);
	अगर (!cryptd_wq)
		वापस -ENOMEM;

	err = cryptd_init_queue(&queue, cryptd_max_cpu_qlen);
	अगर (err)
		जाओ err_destroy_wq;

	err = crypto_रेजिस्टर_ढाँचा(&cryptd_पंचांगpl);
	अगर (err)
		जाओ err_fini_queue;

	वापस 0;

err_fini_queue:
	cryptd_fini_queue(&queue);
err_destroy_wq:
	destroy_workqueue(cryptd_wq);
	वापस err;
पूर्ण

अटल व्योम __निकास cryptd_निकास(व्योम)
अणु
	destroy_workqueue(cryptd_wq);
	cryptd_fini_queue(&queue);
	crypto_unरेजिस्टर_ढाँचा(&cryptd_पंचांगpl);
पूर्ण

subsys_initcall(cryptd_init);
module_निकास(cryptd_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Software async crypto daemon");
MODULE_ALIAS_CRYPTO("cryptd");
