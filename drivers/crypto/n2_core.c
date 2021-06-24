<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* n2_core.c: Niagara2 Stream Processing Unit (SPU) crypto support.
 *
 * Copyright (C) 2010, 2011 David S. Miller <davem@davemloft.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/algapi.h>

#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/mdesc.h>

#समावेश "n2_core.h"

#घोषणा DRV_MODULE_NAME		"n2_crypto"
#घोषणा DRV_MODULE_VERSION	"0.2"
#घोषणा DRV_MODULE_RELDATE	"July 28, 2011"

अटल स्थिर अक्षर version[] =
	DRV_MODULE_NAME ".c:v" DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")\n";

MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_DESCRIPTION("Niagara2 Crypto driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

#घोषणा N2_CRA_PRIORITY		200

अटल DEFINE_MUTEX(spu_lock);

काष्ठा spu_queue अणु
	cpumask_t		sharing;
	अचिन्हित दीर्घ		qhandle;

	spinlock_t		lock;
	u8			q_type;
	व्योम			*q;
	अचिन्हित दीर्घ		head;
	अचिन्हित दीर्घ		tail;
	काष्ठा list_head	jobs;

	अचिन्हित दीर्घ		devino;

	अक्षर			irq_name[32];
	अचिन्हित पूर्णांक		irq;

	काष्ठा list_head	list;
पूर्ण;

काष्ठा spu_qreg अणु
	काष्ठा spu_queue	*queue;
	अचिन्हित दीर्घ		type;
पूर्ण;

अटल काष्ठा spu_queue **cpu_to_cwq;
अटल काष्ठा spu_queue **cpu_to_mau;

अटल अचिन्हित दीर्घ spu_next_offset(काष्ठा spu_queue *q, अचिन्हित दीर्घ off)
अणु
	अगर (q->q_type == HV_NCS_QTYPE_MAU) अणु
		off += MAU_ENTRY_SIZE;
		अगर (off == (MAU_ENTRY_SIZE * MAU_NUM_ENTRIES))
			off = 0;
	पूर्ण अन्यथा अणु
		off += CWQ_ENTRY_SIZE;
		अगर (off == (CWQ_ENTRY_SIZE * CWQ_NUM_ENTRIES))
			off = 0;
	पूर्ण
	वापस off;
पूर्ण

काष्ठा n2_request_common अणु
	काष्ठा list_head	entry;
	अचिन्हित पूर्णांक		offset;
पूर्ण;
#घोषणा OFFSET_NOT_RUNNING	(~(अचिन्हित पूर्णांक)0)

/* An async job request records the final tail value it used in
 * n2_request_common->offset, test to see अगर that offset is in
 * the range old_head, new_head, inclusive.
 */
अटल अंतरभूत bool job_finished(काष्ठा spu_queue *q, अचिन्हित पूर्णांक offset,
				अचिन्हित दीर्घ old_head, अचिन्हित दीर्घ new_head)
अणु
	अगर (old_head <= new_head) अणु
		अगर (offset > old_head && offset <= new_head)
			वापस true;
	पूर्ण अन्यथा अणु
		अगर (offset > old_head || offset <= new_head)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* When the HEAD marker is unequal to the actual HEAD, we get
 * a भव device INO पूर्णांकerrupt.  We should process the
 * completed CWQ entries and adjust the HEAD marker to clear
 * the IRQ.
 */
अटल irqवापस_t cwq_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ off, new_head, hv_ret;
	काष्ठा spu_queue *q = dev_id;

	pr_err("CPU[%d]: Got CWQ interrupt for qhdl[%lx]\n",
	       smp_processor_id(), q->qhandle);

	spin_lock(&q->lock);

	hv_ret = sun4v_ncs_gethead(q->qhandle, &new_head);

	pr_err("CPU[%d]: CWQ gethead[%lx] hv_ret[%lu]\n",
	       smp_processor_id(), new_head, hv_ret);

	क्रम (off = q->head; off != new_head; off = spu_next_offset(q, off)) अणु
		/* XXX ... XXX */
	पूर्ण

	hv_ret = sun4v_ncs_sethead_marker(q->qhandle, new_head);
	अगर (hv_ret == HV_EOK)
		q->head = new_head;

	spin_unlock(&q->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mau_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spu_queue *q = dev_id;
	अचिन्हित दीर्घ head, hv_ret;

	spin_lock(&q->lock);

	pr_err("CPU[%d]: Got MAU interrupt for qhdl[%lx]\n",
	       smp_processor_id(), q->qhandle);

	hv_ret = sun4v_ncs_gethead(q->qhandle, &head);

	pr_err("CPU[%d]: MAU gethead[%lx] hv_ret[%lu]\n",
	       smp_processor_id(), head, hv_ret);

	sun4v_ncs_sethead_marker(q->qhandle, head);

	spin_unlock(&q->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम *spu_queue_next(काष्ठा spu_queue *q, व्योम *cur)
अणु
	वापस q->q + spu_next_offset(q, cur - q->q);
पूर्ण

अटल पूर्णांक spu_queue_num_मुक्त(काष्ठा spu_queue *q)
अणु
	अचिन्हित दीर्घ head = q->head;
	अचिन्हित दीर्घ tail = q->tail;
	अचिन्हित दीर्घ end = (CWQ_ENTRY_SIZE * CWQ_NUM_ENTRIES);
	अचिन्हित दीर्घ dअगरf;

	अगर (head > tail)
		dअगरf = head - tail;
	अन्यथा
		dअगरf = (end - tail) + head;

	वापस (dअगरf / CWQ_ENTRY_SIZE) - 1;
पूर्ण

अटल व्योम *spu_queue_alloc(काष्ठा spu_queue *q, पूर्णांक num_entries)
अणु
	पूर्णांक avail = spu_queue_num_मुक्त(q);

	अगर (avail >= num_entries)
		वापस q->q + q->tail;

	वापस शून्य;
पूर्ण

अटल अचिन्हित दीर्घ spu_queue_submit(काष्ठा spu_queue *q, व्योम *last)
अणु
	अचिन्हित दीर्घ hv_ret, new_tail;

	new_tail = spu_next_offset(q, last - q->q);

	hv_ret = sun4v_ncs_settail(q->qhandle, new_tail);
	अगर (hv_ret == HV_EOK)
		q->tail = new_tail;
	वापस hv_ret;
पूर्ण

अटल u64 control_word_base(अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक hmac_key_len,
			     पूर्णांक enc_type, पूर्णांक auth_type,
			     अचिन्हित पूर्णांक hash_len,
			     bool sfas, bool sob, bool eob, bool encrypt,
			     पूर्णांक opcode)
अणु
	u64 word = (len - 1) & CONTROL_LEN;

	word |= ((u64) opcode << CONTROL_OPCODE_SHIFT);
	word |= ((u64) enc_type << CONTROL_ENC_TYPE_SHIFT);
	word |= ((u64) auth_type << CONTROL_AUTH_TYPE_SHIFT);
	अगर (sfas)
		word |= CONTROL_STORE_FINAL_AUTH_STATE;
	अगर (sob)
		word |= CONTROL_START_OF_BLOCK;
	अगर (eob)
		word |= CONTROL_END_OF_BLOCK;
	अगर (encrypt)
		word |= CONTROL_ENCRYPT;
	अगर (hmac_key_len)
		word |= ((u64) (hmac_key_len - 1)) << CONTROL_HMAC_KEY_LEN_SHIFT;
	अगर (hash_len)
		word |= ((u64) (hash_len - 1)) << CONTROL_HASH_LEN_SHIFT;

	वापस word;
पूर्ण

#अगर 0
अटल अंतरभूत bool n2_should_run_async(काष्ठा spu_queue *qp, पूर्णांक this_len)
अणु
	अगर (this_len >= 64 ||
	    qp->head != qp->tail)
		वापस true;
	वापस false;
पूर्ण
#पूर्ण_अगर

काष्ठा n2_ahash_alg अणु
	काष्ठा list_head	entry;
	स्थिर u8		*hash_zero;
	स्थिर u8		*hash_init;
	u8			hw_op_hashsz;
	u8			digest_size;
	u8			auth_type;
	u8			hmac_type;
	काष्ठा ahash_alg	alg;
पूर्ण;

अटल अंतरभूत काष्ठा n2_ahash_alg *n2_ahash_alg(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_alg *alg = tfm->__crt_alg;
	काष्ठा ahash_alg *ahash_alg;

	ahash_alg = container_of(alg, काष्ठा ahash_alg, halg.base);

	वापस container_of(ahash_alg, काष्ठा n2_ahash_alg, alg);
पूर्ण

काष्ठा n2_hmac_alg अणु
	स्थिर अक्षर		*child_alg;
	काष्ठा n2_ahash_alg	derived;
पूर्ण;

अटल अंतरभूत काष्ठा n2_hmac_alg *n2_hmac_alg(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_alg *alg = tfm->__crt_alg;
	काष्ठा ahash_alg *ahash_alg;

	ahash_alg = container_of(alg, काष्ठा ahash_alg, halg.base);

	वापस container_of(ahash_alg, काष्ठा n2_hmac_alg, derived.alg);
पूर्ण

काष्ठा n2_hash_ctx अणु
	काष्ठा crypto_ahash		*fallback_tfm;
पूर्ण;

#घोषणा N2_HASH_KEY_MAX			32 /* HW limit क्रम all HMAC requests */

काष्ठा n2_hmac_ctx अणु
	काष्ठा n2_hash_ctx		base;

	काष्ठा crypto_shash		*child_shash;

	पूर्णांक				hash_key_len;
	अचिन्हित अक्षर			hash_key[N2_HASH_KEY_MAX];
पूर्ण;

काष्ठा n2_hash_req_ctx अणु
	जोड़ अणु
		काष्ठा md5_state	md5;
		काष्ठा sha1_state	sha1;
		काष्ठा sha256_state	sha256;
	पूर्ण u;

	काष्ठा ahash_request		fallback_req;
पूर्ण;

अटल पूर्णांक n2_hash_async_init(काष्ठा ahash_request *req)
अणु
	काष्ठा n2_hash_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा n2_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
	rctx->fallback_req.base.flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;

	वापस crypto_ahash_init(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक n2_hash_async_update(काष्ठा ahash_request *req)
अणु
	काष्ठा n2_hash_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा n2_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
	rctx->fallback_req.base.flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.nbytes = req->nbytes;
	rctx->fallback_req.src = req->src;

	वापस crypto_ahash_update(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक n2_hash_async_final(काष्ठा ahash_request *req)
अणु
	काष्ठा n2_hash_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा n2_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
	rctx->fallback_req.base.flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.result = req->result;

	वापस crypto_ahash_final(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक n2_hash_async_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा n2_hash_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा n2_hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
	rctx->fallback_req.base.flags = req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;
	rctx->fallback_req.nbytes = req->nbytes;
	rctx->fallback_req.src = req->src;
	rctx->fallback_req.result = req->result;

	वापस crypto_ahash_finup(&rctx->fallback_req);
पूर्ण

अटल पूर्णांक n2_hash_async_noimport(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक n2_hash_async_noexport(काष्ठा ahash_request *req, व्योम *out)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक n2_hash_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	स्थिर अक्षर *fallback_driver_name = crypto_tfm_alg_name(tfm);
	काष्ठा crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	काष्ठा n2_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा crypto_ahash *fallback_tfm;
	पूर्णांक err;

	fallback_tfm = crypto_alloc_ahash(fallback_driver_name, 0,
					  CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(fallback_tfm)) अणु
		pr_warn("Fallback driver '%s' could not be loaded!\n",
			fallback_driver_name);
		err = PTR_ERR(fallback_tfm);
		जाओ out;
	पूर्ण

	crypto_ahash_set_reqsize(ahash, (माप(काष्ठा n2_hash_req_ctx) +
					 crypto_ahash_reqsize(fallback_tfm)));

	ctx->fallback_tfm = fallback_tfm;
	वापस 0;

out:
	वापस err;
पूर्ण

अटल व्योम n2_hash_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	काष्ठा n2_hash_ctx *ctx = crypto_ahash_ctx(ahash);

	crypto_मुक्त_ahash(ctx->fallback_tfm);
पूर्ण

अटल पूर्णांक n2_hmac_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	स्थिर अक्षर *fallback_driver_name = crypto_tfm_alg_name(tfm);
	काष्ठा crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	काष्ठा n2_hmac_ctx *ctx = crypto_ahash_ctx(ahash);
	काष्ठा n2_hmac_alg *n2alg = n2_hmac_alg(tfm);
	काष्ठा crypto_ahash *fallback_tfm;
	काष्ठा crypto_shash *child_shash;
	पूर्णांक err;

	fallback_tfm = crypto_alloc_ahash(fallback_driver_name, 0,
					  CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(fallback_tfm)) अणु
		pr_warn("Fallback driver '%s' could not be loaded!\n",
			fallback_driver_name);
		err = PTR_ERR(fallback_tfm);
		जाओ out;
	पूर्ण

	child_shash = crypto_alloc_shash(n2alg->child_alg, 0, 0);
	अगर (IS_ERR(child_shash)) अणु
		pr_warn("Child shash '%s' could not be loaded!\n",
			n2alg->child_alg);
		err = PTR_ERR(child_shash);
		जाओ out_मुक्त_fallback;
	पूर्ण

	crypto_ahash_set_reqsize(ahash, (माप(काष्ठा n2_hash_req_ctx) +
					 crypto_ahash_reqsize(fallback_tfm)));

	ctx->child_shash = child_shash;
	ctx->base.fallback_tfm = fallback_tfm;
	वापस 0;

out_मुक्त_fallback:
	crypto_मुक्त_ahash(fallback_tfm);

out:
	वापस err;
पूर्ण

अटल व्योम n2_hmac_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा crypto_ahash *ahash = __crypto_ahash_cast(tfm);
	काष्ठा n2_hmac_ctx *ctx = crypto_ahash_ctx(ahash);

	crypto_मुक्त_ahash(ctx->base.fallback_tfm);
	crypto_मुक्त_shash(ctx->child_shash);
पूर्ण

अटल पूर्णांक n2_hmac_async_setkey(काष्ठा crypto_ahash *tfm, स्थिर u8 *key,
				अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा n2_hmac_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा crypto_shash *child_shash = ctx->child_shash;
	काष्ठा crypto_ahash *fallback_tfm;
	पूर्णांक err, bs, ds;

	fallback_tfm = ctx->base.fallback_tfm;
	err = crypto_ahash_setkey(fallback_tfm, key, keylen);
	अगर (err)
		वापस err;

	bs = crypto_shash_blocksize(child_shash);
	ds = crypto_shash_digestsize(child_shash);
	BUG_ON(ds > N2_HASH_KEY_MAX);
	अगर (keylen > bs) अणु
		err = crypto_shash_tfm_digest(child_shash, key, keylen,
					      ctx->hash_key);
		अगर (err)
			वापस err;
		keylen = ds;
	पूर्ण अन्यथा अगर (keylen <= N2_HASH_KEY_MAX)
		स_नकल(ctx->hash_key, key, keylen);

	ctx->hash_key_len = keylen;

	वापस err;
पूर्ण

अटल अचिन्हित दीर्घ रुको_क्रम_tail(काष्ठा spu_queue *qp)
अणु
	अचिन्हित दीर्घ head, hv_ret;

	करो अणु
		hv_ret = sun4v_ncs_gethead(qp->qhandle, &head);
		अगर (hv_ret != HV_EOK) अणु
			pr_err("Hypervisor error on gethead\n");
			अवरोध;
		पूर्ण
		अगर (head == qp->tail) अणु
			qp->head = head;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);
	वापस hv_ret;
पूर्ण

अटल अचिन्हित दीर्घ submit_and_रुको_क्रम_tail(काष्ठा spu_queue *qp,
					      काष्ठा cwq_initial_entry *ent)
अणु
	अचिन्हित दीर्घ hv_ret = spu_queue_submit(qp, ent);

	अगर (hv_ret == HV_EOK)
		hv_ret = रुको_क्रम_tail(qp);

	वापस hv_ret;
पूर्ण

अटल पूर्णांक n2_करो_async_digest(काष्ठा ahash_request *req,
			      अचिन्हित पूर्णांक auth_type, अचिन्हित पूर्णांक digest_size,
			      अचिन्हित पूर्णांक result_size, व्योम *hash_loc,
			      अचिन्हित दीर्घ auth_key, अचिन्हित पूर्णांक auth_key_len)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा cwq_initial_entry *ent;
	काष्ठा crypto_hash_walk walk;
	काष्ठा spu_queue *qp;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -ENODEV;
	पूर्णांक nbytes, cpu;

	/* The total effective length of the operation may not
	 * exceed 2^16.
	 */
	अगर (unlikely(req->nbytes > (1 << 16))) अणु
		काष्ठा n2_hash_req_ctx *rctx = ahash_request_ctx(req);
		काष्ठा n2_hash_ctx *ctx = crypto_ahash_ctx(tfm);

		ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
		rctx->fallback_req.base.flags =
			req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;
		rctx->fallback_req.nbytes = req->nbytes;
		rctx->fallback_req.src = req->src;
		rctx->fallback_req.result = req->result;

		वापस crypto_ahash_digest(&rctx->fallback_req);
	पूर्ण

	nbytes = crypto_hash_walk_first(req, &walk);

	cpu = get_cpu();
	qp = cpu_to_cwq[cpu];
	अगर (!qp)
		जाओ out;

	spin_lock_irqsave(&qp->lock, flags);

	/* XXX can करो better, improve this later by करोing a by-hand scatterlist
	 * XXX walk, etc.
	 */
	ent = qp->q + qp->tail;

	ent->control = control_word_base(nbytes, auth_key_len, 0,
					 auth_type, digest_size,
					 false, true, false, false,
					 OPCODE_INPLACE_BIT |
					 OPCODE_AUTH_MAC);
	ent->src_addr = __pa(walk.data);
	ent->auth_key_addr = auth_key;
	ent->auth_iv_addr = __pa(hash_loc);
	ent->final_auth_state_addr = 0UL;
	ent->enc_key_addr = 0UL;
	ent->enc_iv_addr = 0UL;
	ent->dest_addr = __pa(hash_loc);

	nbytes = crypto_hash_walk_करोne(&walk, 0);
	जबतक (nbytes > 0) अणु
		ent = spu_queue_next(qp, ent);

		ent->control = (nbytes - 1);
		ent->src_addr = __pa(walk.data);
		ent->auth_key_addr = 0UL;
		ent->auth_iv_addr = 0UL;
		ent->final_auth_state_addr = 0UL;
		ent->enc_key_addr = 0UL;
		ent->enc_iv_addr = 0UL;
		ent->dest_addr = 0UL;

		nbytes = crypto_hash_walk_करोne(&walk, 0);
	पूर्ण
	ent->control |= CONTROL_END_OF_BLOCK;

	अगर (submit_and_रुको_क्रम_tail(qp, ent) != HV_EOK)
		err = -EINVAL;
	अन्यथा
		err = 0;

	spin_unlock_irqrestore(&qp->lock, flags);

	अगर (!err)
		स_नकल(req->result, hash_loc, result_size);
out:
	put_cpu();

	वापस err;
पूर्ण

अटल पूर्णांक n2_hash_async_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा n2_ahash_alg *n2alg = n2_ahash_alg(req->base.tfm);
	काष्ठा n2_hash_req_ctx *rctx = ahash_request_ctx(req);
	पूर्णांक ds;

	ds = n2alg->digest_size;
	अगर (unlikely(req->nbytes == 0)) अणु
		स_नकल(req->result, n2alg->hash_zero, ds);
		वापस 0;
	पूर्ण
	स_नकल(&rctx->u, n2alg->hash_init, n2alg->hw_op_hashsz);

	वापस n2_करो_async_digest(req, n2alg->auth_type,
				  n2alg->hw_op_hashsz, ds,
				  &rctx->u, 0UL, 0);
पूर्ण

अटल पूर्णांक n2_hmac_async_digest(काष्ठा ahash_request *req)
अणु
	काष्ठा n2_hmac_alg *n2alg = n2_hmac_alg(req->base.tfm);
	काष्ठा n2_hash_req_ctx *rctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा n2_hmac_ctx *ctx = crypto_ahash_ctx(tfm);
	पूर्णांक ds;

	ds = n2alg->derived.digest_size;
	अगर (unlikely(req->nbytes == 0) ||
	    unlikely(ctx->hash_key_len > N2_HASH_KEY_MAX)) अणु
		काष्ठा n2_hash_req_ctx *rctx = ahash_request_ctx(req);
		काष्ठा n2_hash_ctx *ctx = crypto_ahash_ctx(tfm);

		ahash_request_set_tfm(&rctx->fallback_req, ctx->fallback_tfm);
		rctx->fallback_req.base.flags =
			req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP;
		rctx->fallback_req.nbytes = req->nbytes;
		rctx->fallback_req.src = req->src;
		rctx->fallback_req.result = req->result;

		वापस crypto_ahash_digest(&rctx->fallback_req);
	पूर्ण
	स_नकल(&rctx->u, n2alg->derived.hash_init,
	       n2alg->derived.hw_op_hashsz);

	वापस n2_करो_async_digest(req, n2alg->derived.hmac_type,
				  n2alg->derived.hw_op_hashsz, ds,
				  &rctx->u,
				  __pa(&ctx->hash_key),
				  ctx->hash_key_len);
पूर्ण

काष्ठा n2_skcipher_context अणु
	पूर्णांक			key_len;
	पूर्णांक			enc_type;
	जोड़ अणु
		u8		aes[AES_MAX_KEY_SIZE];
		u8		des[DES_KEY_SIZE];
		u8		des3[3 * DES_KEY_SIZE];
	पूर्ण key;
पूर्ण;

#घोषणा N2_CHUNK_ARR_LEN	16

काष्ठा n2_crypto_chunk अणु
	काष्ठा list_head	entry;
	अचिन्हित दीर्घ		iv_paddr : 44;
	अचिन्हित दीर्घ		arr_len : 20;
	अचिन्हित दीर्घ		dest_paddr;
	अचिन्हित दीर्घ		dest_final;
	काष्ठा अणु
		अचिन्हित दीर्घ	src_paddr : 44;
		अचिन्हित दीर्घ	src_len : 20;
	पूर्ण arr[N2_CHUNK_ARR_LEN];
पूर्ण;

काष्ठा n2_request_context अणु
	काष्ठा skcipher_walk	walk;
	काष्ठा list_head	chunk_list;
	काष्ठा n2_crypto_chunk	chunk;
	u8			temp_iv[16];
पूर्ण;

/* The SPU allows some level of flexibility क्रम partial cipher blocks
 * being specअगरied in a descriptor.
 *
 * It merely requires that every descriptor's length field is at least
 * as large as the cipher block size.  This means that a cipher block
 * can span at most 2 descriptors.  However, this करोes not allow a
 * partial block to span पूर्णांकo the final descriptor as that would
 * violate the rule (since every descriptor's length must be at lest
 * the block size).  So, क्रम example, assuming an 8 byte block size:
 *
 *	0xe --> 0xa --> 0x8
 *
 * is a valid length sequence, whereas:
 *
 *	0xe --> 0xb --> 0x7
 *
 * is not a valid sequence.
 */

काष्ठा n2_skcipher_alg अणु
	काष्ठा list_head	entry;
	u8			enc_type;
	काष्ठा skcipher_alg	skcipher;
पूर्ण;

अटल अंतरभूत काष्ठा n2_skcipher_alg *n2_skcipher_alg(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);

	वापस container_of(alg, काष्ठा n2_skcipher_alg, skcipher);
पूर्ण

काष्ठा n2_skcipher_request_context अणु
	काष्ठा skcipher_walk	walk;
पूर्ण;

अटल पूर्णांक n2_aes_setkey(काष्ठा crypto_skcipher *skcipher, स्थिर u8 *key,
			 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(skcipher);
	काष्ठा n2_skcipher_context *ctx = crypto_tfm_ctx(tfm);
	काष्ठा n2_skcipher_alg *n2alg = n2_skcipher_alg(skcipher);

	ctx->enc_type = (n2alg->enc_type & ENC_TYPE_CHAINING_MASK);

	चयन (keylen) अणु
	हाल AES_KEYSIZE_128:
		ctx->enc_type |= ENC_TYPE_ALG_AES128;
		अवरोध;
	हाल AES_KEYSIZE_192:
		ctx->enc_type |= ENC_TYPE_ALG_AES192;
		अवरोध;
	हाल AES_KEYSIZE_256:
		ctx->enc_type |= ENC_TYPE_ALG_AES256;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ctx->key_len = keylen;
	स_नकल(ctx->key.aes, key, keylen);
	वापस 0;
पूर्ण

अटल पूर्णांक n2_des_setkey(काष्ठा crypto_skcipher *skcipher, स्थिर u8 *key,
			 अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(skcipher);
	काष्ठा n2_skcipher_context *ctx = crypto_tfm_ctx(tfm);
	काष्ठा n2_skcipher_alg *n2alg = n2_skcipher_alg(skcipher);
	पूर्णांक err;

	err = verअगरy_skcipher_des_key(skcipher, key);
	अगर (err)
		वापस err;

	ctx->enc_type = n2alg->enc_type;

	ctx->key_len = keylen;
	स_नकल(ctx->key.des, key, keylen);
	वापस 0;
पूर्ण

अटल पूर्णांक n2_3des_setkey(काष्ठा crypto_skcipher *skcipher, स्थिर u8 *key,
			  अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(skcipher);
	काष्ठा n2_skcipher_context *ctx = crypto_tfm_ctx(tfm);
	काष्ठा n2_skcipher_alg *n2alg = n2_skcipher_alg(skcipher);
	पूर्णांक err;

	err = verअगरy_skcipher_des3_key(skcipher, key);
	अगर (err)
		वापस err;

	ctx->enc_type = n2alg->enc_type;

	ctx->key_len = keylen;
	स_नकल(ctx->key.des3, key, keylen);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक skcipher_descriptor_len(पूर्णांक nbytes, अचिन्हित पूर्णांक block_size)
अणु
	पूर्णांक this_len = nbytes;

	this_len -= (nbytes & (block_size - 1));
	वापस this_len > (1 << 16) ? (1 << 16) : this_len;
पूर्ण

अटल पूर्णांक __n2_crypt_chunk(काष्ठा crypto_skcipher *skcipher,
			    काष्ठा n2_crypto_chunk *cp,
			    काष्ठा spu_queue *qp, bool encrypt)
अणु
	काष्ठा n2_skcipher_context *ctx = crypto_skcipher_ctx(skcipher);
	काष्ठा cwq_initial_entry *ent;
	bool in_place;
	पूर्णांक i;

	ent = spu_queue_alloc(qp, cp->arr_len);
	अगर (!ent) अणु
		pr_info("queue_alloc() of %d fails\n",
			cp->arr_len);
		वापस -EBUSY;
	पूर्ण

	in_place = (cp->dest_paddr == cp->arr[0].src_paddr);

	ent->control = control_word_base(cp->arr[0].src_len,
					 0, ctx->enc_type, 0, 0,
					 false, true, false, encrypt,
					 OPCODE_ENCRYPT |
					 (in_place ? OPCODE_INPLACE_BIT : 0));
	ent->src_addr = cp->arr[0].src_paddr;
	ent->auth_key_addr = 0UL;
	ent->auth_iv_addr = 0UL;
	ent->final_auth_state_addr = 0UL;
	ent->enc_key_addr = __pa(&ctx->key);
	ent->enc_iv_addr = cp->iv_paddr;
	ent->dest_addr = (in_place ? 0UL : cp->dest_paddr);

	क्रम (i = 1; i < cp->arr_len; i++) अणु
		ent = spu_queue_next(qp, ent);

		ent->control = cp->arr[i].src_len - 1;
		ent->src_addr = cp->arr[i].src_paddr;
		ent->auth_key_addr = 0UL;
		ent->auth_iv_addr = 0UL;
		ent->final_auth_state_addr = 0UL;
		ent->enc_key_addr = 0UL;
		ent->enc_iv_addr = 0UL;
		ent->dest_addr = 0UL;
	पूर्ण
	ent->control |= CONTROL_END_OF_BLOCK;

	वापस (spu_queue_submit(qp, ent) != HV_EOK) ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक n2_compute_chunks(काष्ठा skcipher_request *req)
अणु
	काष्ठा n2_request_context *rctx = skcipher_request_ctx(req);
	काष्ठा skcipher_walk *walk = &rctx->walk;
	काष्ठा n2_crypto_chunk *chunk;
	अचिन्हित दीर्घ dest_prev;
	अचिन्हित पूर्णांक tot_len;
	bool prev_in_place;
	पूर्णांक err, nbytes;

	err = skcipher_walk_async(walk, req);
	अगर (err)
		वापस err;

	INIT_LIST_HEAD(&rctx->chunk_list);

	chunk = &rctx->chunk;
	INIT_LIST_HEAD(&chunk->entry);

	chunk->iv_paddr = 0UL;
	chunk->arr_len = 0;
	chunk->dest_paddr = 0UL;

	prev_in_place = false;
	dest_prev = ~0UL;
	tot_len = 0;

	जबतक ((nbytes = walk->nbytes) != 0) अणु
		अचिन्हित दीर्घ dest_paddr, src_paddr;
		bool in_place;
		पूर्णांक this_len;

		src_paddr = (page_to_phys(walk->src.phys.page) +
			     walk->src.phys.offset);
		dest_paddr = (page_to_phys(walk->dst.phys.page) +
			      walk->dst.phys.offset);
		in_place = (src_paddr == dest_paddr);
		this_len = skcipher_descriptor_len(nbytes, walk->blocksize);

		अगर (chunk->arr_len != 0) अणु
			अगर (in_place != prev_in_place ||
			    (!prev_in_place &&
			     dest_paddr != dest_prev) ||
			    chunk->arr_len == N2_CHUNK_ARR_LEN ||
			    tot_len + this_len > (1 << 16)) अणु
				chunk->dest_final = dest_prev;
				list_add_tail(&chunk->entry,
					      &rctx->chunk_list);
				chunk = kzalloc(माप(*chunk), GFP_ATOMIC);
				अगर (!chunk) अणु
					err = -ENOMEM;
					अवरोध;
				पूर्ण
				INIT_LIST_HEAD(&chunk->entry);
			पूर्ण
		पूर्ण
		अगर (chunk->arr_len == 0) अणु
			chunk->dest_paddr = dest_paddr;
			tot_len = 0;
		पूर्ण
		chunk->arr[chunk->arr_len].src_paddr = src_paddr;
		chunk->arr[chunk->arr_len].src_len = this_len;
		chunk->arr_len++;

		dest_prev = dest_paddr + this_len;
		prev_in_place = in_place;
		tot_len += this_len;

		err = skcipher_walk_करोne(walk, nbytes - this_len);
		अगर (err)
			अवरोध;
	पूर्ण
	अगर (!err && chunk->arr_len != 0) अणु
		chunk->dest_final = dest_prev;
		list_add_tail(&chunk->entry, &rctx->chunk_list);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम n2_chunk_complete(काष्ठा skcipher_request *req, व्योम *final_iv)
अणु
	काष्ठा n2_request_context *rctx = skcipher_request_ctx(req);
	काष्ठा n2_crypto_chunk *c, *पंचांगp;

	अगर (final_iv)
		स_नकल(rctx->walk.iv, final_iv, rctx->walk.blocksize);

	list_क्रम_each_entry_safe(c, पंचांगp, &rctx->chunk_list, entry) अणु
		list_del(&c->entry);
		अगर (unlikely(c != &rctx->chunk))
			kमुक्त(c);
	पूर्ण

पूर्ण

अटल पूर्णांक n2_करो_ecb(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा n2_request_context *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	पूर्णांक err = n2_compute_chunks(req);
	काष्ठा n2_crypto_chunk *c, *पंचांगp;
	अचिन्हित दीर्घ flags, hv_ret;
	काष्ठा spu_queue *qp;

	अगर (err)
		वापस err;

	qp = cpu_to_cwq[get_cpu()];
	err = -ENODEV;
	अगर (!qp)
		जाओ out;

	spin_lock_irqsave(&qp->lock, flags);

	list_क्रम_each_entry_safe(c, पंचांगp, &rctx->chunk_list, entry) अणु
		err = __n2_crypt_chunk(tfm, c, qp, encrypt);
		अगर (err)
			अवरोध;
		list_del(&c->entry);
		अगर (unlikely(c != &rctx->chunk))
			kमुक्त(c);
	पूर्ण
	अगर (!err) अणु
		hv_ret = रुको_क्रम_tail(qp);
		अगर (hv_ret != HV_EOK)
			err = -EINVAL;
	पूर्ण

	spin_unlock_irqrestore(&qp->lock, flags);

out:
	put_cpu();

	n2_chunk_complete(req, शून्य);
	वापस err;
पूर्ण

अटल पूर्णांक n2_encrypt_ecb(काष्ठा skcipher_request *req)
अणु
	वापस n2_करो_ecb(req, true);
पूर्ण

अटल पूर्णांक n2_decrypt_ecb(काष्ठा skcipher_request *req)
अणु
	वापस n2_करो_ecb(req, false);
पूर्ण

अटल पूर्णांक n2_करो_chaining(काष्ठा skcipher_request *req, bool encrypt)
अणु
	काष्ठा n2_request_context *rctx = skcipher_request_ctx(req);
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	अचिन्हित दीर्घ flags, hv_ret, iv_paddr;
	पूर्णांक err = n2_compute_chunks(req);
	काष्ठा n2_crypto_chunk *c, *पंचांगp;
	काष्ठा spu_queue *qp;
	व्योम *final_iv_addr;

	final_iv_addr = शून्य;

	अगर (err)
		वापस err;

	qp = cpu_to_cwq[get_cpu()];
	err = -ENODEV;
	अगर (!qp)
		जाओ out;

	spin_lock_irqsave(&qp->lock, flags);

	अगर (encrypt) अणु
		iv_paddr = __pa(rctx->walk.iv);
		list_क्रम_each_entry_safe(c, पंचांगp, &rctx->chunk_list,
					 entry) अणु
			c->iv_paddr = iv_paddr;
			err = __n2_crypt_chunk(tfm, c, qp, true);
			अगर (err)
				अवरोध;
			iv_paddr = c->dest_final - rctx->walk.blocksize;
			list_del(&c->entry);
			अगर (unlikely(c != &rctx->chunk))
				kमुक्त(c);
		पूर्ण
		final_iv_addr = __va(iv_paddr);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_safe_reverse(c, पंचांगp, &rctx->chunk_list,
						 entry) अणु
			अगर (c == &rctx->chunk) अणु
				iv_paddr = __pa(rctx->walk.iv);
			पूर्ण अन्यथा अणु
				iv_paddr = (पंचांगp->arr[पंचांगp->arr_len-1].src_paddr +
					    पंचांगp->arr[पंचांगp->arr_len-1].src_len -
					    rctx->walk.blocksize);
			पूर्ण
			अगर (!final_iv_addr) अणु
				अचिन्हित दीर्घ pa;

				pa = (c->arr[c->arr_len-1].src_paddr +
				      c->arr[c->arr_len-1].src_len -
				      rctx->walk.blocksize);
				final_iv_addr = rctx->temp_iv;
				स_नकल(rctx->temp_iv, __va(pa),
				       rctx->walk.blocksize);
			पूर्ण
			c->iv_paddr = iv_paddr;
			err = __n2_crypt_chunk(tfm, c, qp, false);
			अगर (err)
				अवरोध;
			list_del(&c->entry);
			अगर (unlikely(c != &rctx->chunk))
				kमुक्त(c);
		पूर्ण
	पूर्ण
	अगर (!err) अणु
		hv_ret = रुको_क्रम_tail(qp);
		अगर (hv_ret != HV_EOK)
			err = -EINVAL;
	पूर्ण

	spin_unlock_irqrestore(&qp->lock, flags);

out:
	put_cpu();

	n2_chunk_complete(req, err ? शून्य : final_iv_addr);
	वापस err;
पूर्ण

अटल पूर्णांक n2_encrypt_chaining(काष्ठा skcipher_request *req)
अणु
	वापस n2_करो_chaining(req, true);
पूर्ण

अटल पूर्णांक n2_decrypt_chaining(काष्ठा skcipher_request *req)
अणु
	वापस n2_करो_chaining(req, false);
पूर्ण

काष्ठा n2_skcipher_पंचांगpl अणु
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*drv_name;
	u8			block_size;
	u8			enc_type;
	काष्ठा skcipher_alg	skcipher;
पूर्ण;

अटल स्थिर काष्ठा n2_skcipher_पंचांगpl skcipher_पंचांगpls[] = अणु
	/* DES: ECB CBC and CFB are supported */
	अणु	.name		= "ecb(des)",
		.drv_name	= "ecb-des",
		.block_size	= DES_BLOCK_SIZE,
		.enc_type	= (ENC_TYPE_ALG_DES |
				   ENC_TYPE_CHAINING_ECB),
		.skcipher	= अणु
			.min_keysize	= DES_KEY_SIZE,
			.max_keysize	= DES_KEY_SIZE,
			.setkey		= n2_des_setkey,
			.encrypt	= n2_encrypt_ecb,
			.decrypt	= n2_decrypt_ecb,
		पूर्ण,
	पूर्ण,
	अणु	.name		= "cbc(des)",
		.drv_name	= "cbc-des",
		.block_size	= DES_BLOCK_SIZE,
		.enc_type	= (ENC_TYPE_ALG_DES |
				   ENC_TYPE_CHAINING_CBC),
		.skcipher	= अणु
			.ivsize		= DES_BLOCK_SIZE,
			.min_keysize	= DES_KEY_SIZE,
			.max_keysize	= DES_KEY_SIZE,
			.setkey		= n2_des_setkey,
			.encrypt	= n2_encrypt_chaining,
			.decrypt	= n2_decrypt_chaining,
		पूर्ण,
	पूर्ण,
	अणु	.name		= "cfb(des)",
		.drv_name	= "cfb-des",
		.block_size	= DES_BLOCK_SIZE,
		.enc_type	= (ENC_TYPE_ALG_DES |
				   ENC_TYPE_CHAINING_CFB),
		.skcipher	= अणु
			.min_keysize	= DES_KEY_SIZE,
			.max_keysize	= DES_KEY_SIZE,
			.setkey		= n2_des_setkey,
			.encrypt	= n2_encrypt_chaining,
			.decrypt	= n2_decrypt_chaining,
		पूर्ण,
	पूर्ण,

	/* 3DES: ECB CBC and CFB are supported */
	अणु	.name		= "ecb(des3_ede)",
		.drv_name	= "ecb-3des",
		.block_size	= DES_BLOCK_SIZE,
		.enc_type	= (ENC_TYPE_ALG_3DES |
				   ENC_TYPE_CHAINING_ECB),
		.skcipher	= अणु
			.min_keysize	= 3 * DES_KEY_SIZE,
			.max_keysize	= 3 * DES_KEY_SIZE,
			.setkey		= n2_3des_setkey,
			.encrypt	= n2_encrypt_ecb,
			.decrypt	= n2_decrypt_ecb,
		पूर्ण,
	पूर्ण,
	अणु	.name		= "cbc(des3_ede)",
		.drv_name	= "cbc-3des",
		.block_size	= DES_BLOCK_SIZE,
		.enc_type	= (ENC_TYPE_ALG_3DES |
				   ENC_TYPE_CHAINING_CBC),
		.skcipher	= अणु
			.ivsize		= DES_BLOCK_SIZE,
			.min_keysize	= 3 * DES_KEY_SIZE,
			.max_keysize	= 3 * DES_KEY_SIZE,
			.setkey		= n2_3des_setkey,
			.encrypt	= n2_encrypt_chaining,
			.decrypt	= n2_decrypt_chaining,
		पूर्ण,
	पूर्ण,
	अणु	.name		= "cfb(des3_ede)",
		.drv_name	= "cfb-3des",
		.block_size	= DES_BLOCK_SIZE,
		.enc_type	= (ENC_TYPE_ALG_3DES |
				   ENC_TYPE_CHAINING_CFB),
		.skcipher	= अणु
			.min_keysize	= 3 * DES_KEY_SIZE,
			.max_keysize	= 3 * DES_KEY_SIZE,
			.setkey		= n2_3des_setkey,
			.encrypt	= n2_encrypt_chaining,
			.decrypt	= n2_decrypt_chaining,
		पूर्ण,
	पूर्ण,
	/* AES: ECB CBC and CTR are supported */
	अणु	.name		= "ecb(aes)",
		.drv_name	= "ecb-aes",
		.block_size	= AES_BLOCK_SIZE,
		.enc_type	= (ENC_TYPE_ALG_AES128 |
				   ENC_TYPE_CHAINING_ECB),
		.skcipher	= अणु
			.min_keysize	= AES_MIN_KEY_SIZE,
			.max_keysize	= AES_MAX_KEY_SIZE,
			.setkey		= n2_aes_setkey,
			.encrypt	= n2_encrypt_ecb,
			.decrypt	= n2_decrypt_ecb,
		पूर्ण,
	पूर्ण,
	अणु	.name		= "cbc(aes)",
		.drv_name	= "cbc-aes",
		.block_size	= AES_BLOCK_SIZE,
		.enc_type	= (ENC_TYPE_ALG_AES128 |
				   ENC_TYPE_CHAINING_CBC),
		.skcipher	= अणु
			.ivsize		= AES_BLOCK_SIZE,
			.min_keysize	= AES_MIN_KEY_SIZE,
			.max_keysize	= AES_MAX_KEY_SIZE,
			.setkey		= n2_aes_setkey,
			.encrypt	= n2_encrypt_chaining,
			.decrypt	= n2_decrypt_chaining,
		पूर्ण,
	पूर्ण,
	अणु	.name		= "ctr(aes)",
		.drv_name	= "ctr-aes",
		.block_size	= AES_BLOCK_SIZE,
		.enc_type	= (ENC_TYPE_ALG_AES128 |
				   ENC_TYPE_CHAINING_COUNTER),
		.skcipher	= अणु
			.ivsize		= AES_BLOCK_SIZE,
			.min_keysize	= AES_MIN_KEY_SIZE,
			.max_keysize	= AES_MAX_KEY_SIZE,
			.setkey		= n2_aes_setkey,
			.encrypt	= n2_encrypt_chaining,
			.decrypt	= n2_encrypt_chaining,
		पूर्ण,
	पूर्ण,

पूर्ण;
#घोषणा NUM_CIPHER_TMPLS ARRAY_SIZE(skcipher_पंचांगpls)

अटल LIST_HEAD(skcipher_algs);

काष्ठा n2_hash_पंचांगpl अणु
	स्थिर अक्षर	*name;
	स्थिर u8	*hash_zero;
	स्थिर u8	*hash_init;
	u8		hw_op_hashsz;
	u8		digest_size;
	u8		block_size;
	u8		auth_type;
	u8		hmac_type;
पूर्ण;

अटल स्थिर __le32 n2_md5_init[MD5_HASH_WORDS] = अणु
	cpu_to_le32(MD5_H0),
	cpu_to_le32(MD5_H1),
	cpu_to_le32(MD5_H2),
	cpu_to_le32(MD5_H3),
पूर्ण;
अटल स्थिर u32 n2_sha1_init[SHA1_DIGEST_SIZE / 4] = अणु
	SHA1_H0, SHA1_H1, SHA1_H2, SHA1_H3, SHA1_H4,
पूर्ण;
अटल स्थिर u32 n2_sha256_init[SHA256_DIGEST_SIZE / 4] = अणु
	SHA256_H0, SHA256_H1, SHA256_H2, SHA256_H3,
	SHA256_H4, SHA256_H5, SHA256_H6, SHA256_H7,
पूर्ण;
अटल स्थिर u32 n2_sha224_init[SHA256_DIGEST_SIZE / 4] = अणु
	SHA224_H0, SHA224_H1, SHA224_H2, SHA224_H3,
	SHA224_H4, SHA224_H5, SHA224_H6, SHA224_H7,
पूर्ण;

अटल स्थिर काष्ठा n2_hash_पंचांगpl hash_पंचांगpls[] = अणु
	अणु .name		= "md5",
	  .hash_zero	= md5_zero_message_hash,
	  .hash_init	= (u8 *)n2_md5_init,
	  .auth_type	= AUTH_TYPE_MD5,
	  .hmac_type	= AUTH_TYPE_HMAC_MD5,
	  .hw_op_hashsz	= MD5_DIGEST_SIZE,
	  .digest_size	= MD5_DIGEST_SIZE,
	  .block_size	= MD5_HMAC_BLOCK_SIZE पूर्ण,
	अणु .name		= "sha1",
	  .hash_zero	= sha1_zero_message_hash,
	  .hash_init	= (u8 *)n2_sha1_init,
	  .auth_type	= AUTH_TYPE_SHA1,
	  .hmac_type	= AUTH_TYPE_HMAC_SHA1,
	  .hw_op_hashsz	= SHA1_DIGEST_SIZE,
	  .digest_size	= SHA1_DIGEST_SIZE,
	  .block_size	= SHA1_BLOCK_SIZE पूर्ण,
	अणु .name		= "sha256",
	  .hash_zero	= sha256_zero_message_hash,
	  .hash_init	= (u8 *)n2_sha256_init,
	  .auth_type	= AUTH_TYPE_SHA256,
	  .hmac_type	= AUTH_TYPE_HMAC_SHA256,
	  .hw_op_hashsz	= SHA256_DIGEST_SIZE,
	  .digest_size	= SHA256_DIGEST_SIZE,
	  .block_size	= SHA256_BLOCK_SIZE पूर्ण,
	अणु .name		= "sha224",
	  .hash_zero	= sha224_zero_message_hash,
	  .hash_init	= (u8 *)n2_sha224_init,
	  .auth_type	= AUTH_TYPE_SHA256,
	  .hmac_type	= AUTH_TYPE_RESERVED,
	  .hw_op_hashsz	= SHA256_DIGEST_SIZE,
	  .digest_size	= SHA224_DIGEST_SIZE,
	  .block_size	= SHA224_BLOCK_SIZE पूर्ण,
पूर्ण;
#घोषणा NUM_HASH_TMPLS ARRAY_SIZE(hash_पंचांगpls)

अटल LIST_HEAD(ahash_algs);
अटल LIST_HEAD(hmac_algs);

अटल पूर्णांक algs_रेजिस्टरed;

अटल व्योम __n2_unरेजिस्टर_algs(व्योम)
अणु
	काष्ठा n2_skcipher_alg *skcipher, *skcipher_पंचांगp;
	काष्ठा n2_ahash_alg *alg, *alg_पंचांगp;
	काष्ठा n2_hmac_alg *hmac, *hmac_पंचांगp;

	list_क्रम_each_entry_safe(skcipher, skcipher_पंचांगp, &skcipher_algs, entry) अणु
		crypto_unरेजिस्टर_skcipher(&skcipher->skcipher);
		list_del(&skcipher->entry);
		kमुक्त(skcipher);
	पूर्ण
	list_क्रम_each_entry_safe(hmac, hmac_पंचांगp, &hmac_algs, derived.entry) अणु
		crypto_unरेजिस्टर_ahash(&hmac->derived.alg);
		list_del(&hmac->derived.entry);
		kमुक्त(hmac);
	पूर्ण
	list_क्रम_each_entry_safe(alg, alg_पंचांगp, &ahash_algs, entry) अणु
		crypto_unरेजिस्टर_ahash(&alg->alg);
		list_del(&alg->entry);
		kमुक्त(alg);
	पूर्ण
पूर्ण

अटल पूर्णांक n2_skcipher_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा n2_request_context));
	वापस 0;
पूर्ण

अटल पूर्णांक __n2_रेजिस्टर_one_skcipher(स्थिर काष्ठा n2_skcipher_पंचांगpl *पंचांगpl)
अणु
	काष्ठा n2_skcipher_alg *p = kzalloc(माप(*p), GFP_KERNEL);
	काष्ठा skcipher_alg *alg;
	पूर्णांक err;

	अगर (!p)
		वापस -ENOMEM;

	alg = &p->skcipher;
	*alg = पंचांगpl->skcipher;

	snम_लिखो(alg->base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", पंचांगpl->name);
	snम_लिखो(alg->base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s-n2", पंचांगpl->drv_name);
	alg->base.cra_priority = N2_CRA_PRIORITY;
	alg->base.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC |
			      CRYPTO_ALG_ALLOCATES_MEMORY;
	alg->base.cra_blocksize = पंचांगpl->block_size;
	p->enc_type = पंचांगpl->enc_type;
	alg->base.cra_ctxsize = माप(काष्ठा n2_skcipher_context);
	alg->base.cra_module = THIS_MODULE;
	alg->init = n2_skcipher_init_tfm;

	list_add(&p->entry, &skcipher_algs);
	err = crypto_रेजिस्टर_skcipher(alg);
	अगर (err) अणु
		pr_err("%s alg registration failed\n", alg->base.cra_name);
		list_del(&p->entry);
		kमुक्त(p);
	पूर्ण अन्यथा अणु
		pr_info("%s alg registered\n", alg->base.cra_name);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __n2_रेजिस्टर_one_hmac(काष्ठा n2_ahash_alg *n2ahash)
अणु
	काष्ठा n2_hmac_alg *p = kzalloc(माप(*p), GFP_KERNEL);
	काष्ठा ahash_alg *ahash;
	काष्ठा crypto_alg *base;
	पूर्णांक err;

	अगर (!p)
		वापस -ENOMEM;

	p->child_alg = n2ahash->alg.halg.base.cra_name;
	स_नकल(&p->derived, n2ahash, माप(काष्ठा n2_ahash_alg));
	INIT_LIST_HEAD(&p->derived.entry);

	ahash = &p->derived.alg;
	ahash->digest = n2_hmac_async_digest;
	ahash->setkey = n2_hmac_async_setkey;

	base = &ahash->halg.base;
	snम_लिखो(base->cra_name, CRYPTO_MAX_ALG_NAME, "hmac(%s)", p->child_alg);
	snम_लिखो(base->cra_driver_name, CRYPTO_MAX_ALG_NAME, "hmac-%s-n2", p->child_alg);

	base->cra_ctxsize = माप(काष्ठा n2_hmac_ctx);
	base->cra_init = n2_hmac_cra_init;
	base->cra_निकास = n2_hmac_cra_निकास;

	list_add(&p->derived.entry, &hmac_algs);
	err = crypto_रेजिस्टर_ahash(ahash);
	अगर (err) अणु
		pr_err("%s alg registration failed\n", base->cra_name);
		list_del(&p->derived.entry);
		kमुक्त(p);
	पूर्ण अन्यथा अणु
		pr_info("%s alg registered\n", base->cra_name);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __n2_रेजिस्टर_one_ahash(स्थिर काष्ठा n2_hash_पंचांगpl *पंचांगpl)
अणु
	काष्ठा n2_ahash_alg *p = kzalloc(माप(*p), GFP_KERNEL);
	काष्ठा hash_alg_common *halg;
	काष्ठा crypto_alg *base;
	काष्ठा ahash_alg *ahash;
	पूर्णांक err;

	अगर (!p)
		वापस -ENOMEM;

	p->hash_zero = पंचांगpl->hash_zero;
	p->hash_init = पंचांगpl->hash_init;
	p->auth_type = पंचांगpl->auth_type;
	p->hmac_type = पंचांगpl->hmac_type;
	p->hw_op_hashsz = पंचांगpl->hw_op_hashsz;
	p->digest_size = पंचांगpl->digest_size;

	ahash = &p->alg;
	ahash->init = n2_hash_async_init;
	ahash->update = n2_hash_async_update;
	ahash->final = n2_hash_async_final;
	ahash->finup = n2_hash_async_finup;
	ahash->digest = n2_hash_async_digest;
	ahash->export = n2_hash_async_noexport;
	ahash->import = n2_hash_async_noimport;

	halg = &ahash->halg;
	halg->digestsize = पंचांगpl->digest_size;

	base = &halg->base;
	snम_लिखो(base->cra_name, CRYPTO_MAX_ALG_NAME, "%s", पंचांगpl->name);
	snम_लिखो(base->cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s-n2", पंचांगpl->name);
	base->cra_priority = N2_CRA_PRIORITY;
	base->cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY |
			  CRYPTO_ALG_NEED_FALLBACK;
	base->cra_blocksize = पंचांगpl->block_size;
	base->cra_ctxsize = माप(काष्ठा n2_hash_ctx);
	base->cra_module = THIS_MODULE;
	base->cra_init = n2_hash_cra_init;
	base->cra_निकास = n2_hash_cra_निकास;

	list_add(&p->entry, &ahash_algs);
	err = crypto_रेजिस्टर_ahash(ahash);
	अगर (err) अणु
		pr_err("%s alg registration failed\n", base->cra_name);
		list_del(&p->entry);
		kमुक्त(p);
	पूर्ण अन्यथा अणु
		pr_info("%s alg registered\n", base->cra_name);
	पूर्ण
	अगर (!err && p->hmac_type != AUTH_TYPE_RESERVED)
		err = __n2_रेजिस्टर_one_hmac(p);
	वापस err;
पूर्ण

अटल पूर्णांक n2_रेजिस्टर_algs(व्योम)
अणु
	पूर्णांक i, err = 0;

	mutex_lock(&spu_lock);
	अगर (algs_रेजिस्टरed++)
		जाओ out;

	क्रम (i = 0; i < NUM_HASH_TMPLS; i++) अणु
		err = __n2_रेजिस्टर_one_ahash(&hash_पंचांगpls[i]);
		अगर (err) अणु
			__n2_unरेजिस्टर_algs();
			जाओ out;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < NUM_CIPHER_TMPLS; i++) अणु
		err = __n2_रेजिस्टर_one_skcipher(&skcipher_पंचांगpls[i]);
		अगर (err) अणु
			__n2_unरेजिस्टर_algs();
			जाओ out;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&spu_lock);
	वापस err;
पूर्ण

अटल व्योम n2_unरेजिस्टर_algs(व्योम)
अणु
	mutex_lock(&spu_lock);
	अगर (!--algs_रेजिस्टरed)
		__n2_unरेजिस्टर_algs();
	mutex_unlock(&spu_lock);
पूर्ण

/* To map CWQ queues to पूर्णांकerrupt sources, the hypervisor API provides
 * a devino.  This isn't very useful to us because all of the
 * पूर्णांकerrupts listed in the device_node have been translated to
 * Linux भव IRQ cookie numbers.
 *
 * So we have to back-translate, going through the 'intr' and 'ino'
 * property tables of the n2cp MDESC node, matching it with the OF
 * 'interrupts' property entries, in order to to figure out which
 * devino goes to which alपढ़ोy-translated IRQ.
 */
अटल पूर्णांक find_devino_index(काष्ठा platक्रमm_device *dev, काष्ठा spu_mdesc_info *ip,
			     अचिन्हित दीर्घ dev_ino)
अणु
	स्थिर अचिन्हित पूर्णांक *dev_पूर्णांकrs;
	अचिन्हित पूर्णांक पूर्णांकr;
	पूर्णांक i;

	क्रम (i = 0; i < ip->num_पूर्णांकrs; i++) अणु
		अगर (ip->ino_table[i].ino == dev_ino)
			अवरोध;
	पूर्ण
	अगर (i == ip->num_पूर्णांकrs)
		वापस -ENODEV;

	पूर्णांकr = ip->ino_table[i].पूर्णांकr;

	dev_पूर्णांकrs = of_get_property(dev->dev.of_node, "interrupts", शून्य);
	अगर (!dev_पूर्णांकrs)
		वापस -ENODEV;

	क्रम (i = 0; i < dev->archdata.num_irqs; i++) अणु
		अगर (dev_पूर्णांकrs[i] == पूर्णांकr)
			वापस i;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक spu_map_ino(काष्ठा platक्रमm_device *dev, काष्ठा spu_mdesc_info *ip,
		       स्थिर अक्षर *irq_name, काष्ठा spu_queue *p,
		       irq_handler_t handler)
अणु
	अचिन्हित दीर्घ herr;
	पूर्णांक index;

	herr = sun4v_ncs_qhandle_to_devino(p->qhandle, &p->devino);
	अगर (herr)
		वापस -EINVAL;

	index = find_devino_index(dev, ip, p->devino);
	अगर (index < 0)
		वापस index;

	p->irq = dev->archdata.irqs[index];

	प्र_लिखो(p->irq_name, "%s-%d", irq_name, index);

	वापस request_irq(p->irq, handler, 0, p->irq_name, p);
पूर्ण

अटल काष्ठा kmem_cache *queue_cache[2];

अटल व्योम *new_queue(अचिन्हित दीर्घ q_type)
अणु
	वापस kmem_cache_zalloc(queue_cache[q_type - 1], GFP_KERNEL);
पूर्ण

अटल व्योम मुक्त_queue(व्योम *p, अचिन्हित दीर्घ q_type)
अणु
	kmem_cache_मुक्त(queue_cache[q_type - 1], p);
पूर्ण

अटल पूर्णांक queue_cache_init(व्योम)
अणु
	अगर (!queue_cache[HV_NCS_QTYPE_MAU - 1])
		queue_cache[HV_NCS_QTYPE_MAU - 1] =
			kmem_cache_create("mau_queue",
					  (MAU_NUM_ENTRIES *
					   MAU_ENTRY_SIZE),
					  MAU_ENTRY_SIZE, 0, शून्य);
	अगर (!queue_cache[HV_NCS_QTYPE_MAU - 1])
		वापस -ENOMEM;

	अगर (!queue_cache[HV_NCS_QTYPE_CWQ - 1])
		queue_cache[HV_NCS_QTYPE_CWQ - 1] =
			kmem_cache_create("cwq_queue",
					  (CWQ_NUM_ENTRIES *
					   CWQ_ENTRY_SIZE),
					  CWQ_ENTRY_SIZE, 0, शून्य);
	अगर (!queue_cache[HV_NCS_QTYPE_CWQ - 1]) अणु
		kmem_cache_destroy(queue_cache[HV_NCS_QTYPE_MAU - 1]);
		queue_cache[HV_NCS_QTYPE_MAU - 1] = शून्य;
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम queue_cache_destroy(व्योम)
अणु
	kmem_cache_destroy(queue_cache[HV_NCS_QTYPE_MAU - 1]);
	kmem_cache_destroy(queue_cache[HV_NCS_QTYPE_CWQ - 1]);
	queue_cache[HV_NCS_QTYPE_MAU - 1] = शून्य;
	queue_cache[HV_NCS_QTYPE_CWQ - 1] = शून्य;
पूर्ण

अटल दीर्घ spu_queue_रेजिस्टर_workfn(व्योम *arg)
अणु
	काष्ठा spu_qreg *qr = arg;
	काष्ठा spu_queue *p = qr->queue;
	अचिन्हित दीर्घ q_type = qr->type;
	अचिन्हित दीर्घ hv_ret;

	hv_ret = sun4v_ncs_qconf(q_type, __pa(p->q),
				 CWQ_NUM_ENTRIES, &p->qhandle);
	अगर (!hv_ret)
		sun4v_ncs_sethead_marker(p->qhandle, 0);

	वापस hv_ret ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक spu_queue_रेजिस्टर(काष्ठा spu_queue *p, अचिन्हित दीर्घ q_type)
अणु
	पूर्णांक cpu = cpumask_any_and(&p->sharing, cpu_online_mask);
	काष्ठा spu_qreg qr = अणु .queue = p, .type = q_type पूर्ण;

	वापस work_on_cpu_safe(cpu, spu_queue_रेजिस्टर_workfn, &qr);
पूर्ण

अटल पूर्णांक spu_queue_setup(काष्ठा spu_queue *p)
अणु
	पूर्णांक err;

	p->q = new_queue(p->q_type);
	अगर (!p->q)
		वापस -ENOMEM;

	err = spu_queue_रेजिस्टर(p, p->q_type);
	अगर (err) अणु
		मुक्त_queue(p->q, p->q_type);
		p->q = शून्य;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम spu_queue_destroy(काष्ठा spu_queue *p)
अणु
	अचिन्हित दीर्घ hv_ret;

	अगर (!p->q)
		वापस;

	hv_ret = sun4v_ncs_qconf(p->q_type, p->qhandle, 0, &p->qhandle);

	अगर (!hv_ret)
		मुक्त_queue(p->q, p->q_type);
पूर्ण

अटल व्योम spu_list_destroy(काष्ठा list_head *list)
अणु
	काष्ठा spu_queue *p, *n;

	list_क्रम_each_entry_safe(p, n, list, list) अणु
		पूर्णांक i;

		क्रम (i = 0; i < NR_CPUS; i++) अणु
			अगर (cpu_to_cwq[i] == p)
				cpu_to_cwq[i] = शून्य;
		पूर्ण

		अगर (p->irq) अणु
			मुक्त_irq(p->irq, p);
			p->irq = 0;
		पूर्ण
		spu_queue_destroy(p);
		list_del(&p->list);
		kमुक्त(p);
	पूर्ण
पूर्ण

/* Walk the backward arcs of a CWQ 'exec-unit' node,
 * gathering cpu membership inक्रमmation.
 */
अटल पूर्णांक spu_mdesc_walk_arcs(काष्ठा mdesc_handle *mdesc,
			       काष्ठा platक्रमm_device *dev,
			       u64 node, काष्ठा spu_queue *p,
			       काष्ठा spu_queue **table)
अणु
	u64 arc;

	mdesc_क्रम_each_arc(arc, mdesc, node, MDESC_ARC_TYPE_BACK) अणु
		u64 tgt = mdesc_arc_target(mdesc, arc);
		स्थिर अक्षर *name = mdesc_node_name(mdesc, tgt);
		स्थिर u64 *id;

		अगर (म_भेद(name, "cpu"))
			जारी;
		id = mdesc_get_property(mdesc, tgt, "id", शून्य);
		अगर (table[*id] != शून्य) अणु
			dev_err(&dev->dev, "%pOF: SPU cpu slot already set.\n",
				dev->dev.of_node);
			वापस -EINVAL;
		पूर्ण
		cpumask_set_cpu(*id, &p->sharing);
		table[*id] = p;
	पूर्ण
	वापस 0;
पूर्ण

/* Process an 'exec-unit' MDESC node of type 'cwq'.  */
अटल पूर्णांक handle_exec_unit(काष्ठा spu_mdesc_info *ip, काष्ठा list_head *list,
			    काष्ठा platक्रमm_device *dev, काष्ठा mdesc_handle *mdesc,
			    u64 node, स्थिर अक्षर *iname, अचिन्हित दीर्घ q_type,
			    irq_handler_t handler, काष्ठा spu_queue **table)
अणु
	काष्ठा spu_queue *p;
	पूर्णांक err;

	p = kzalloc(माप(काष्ठा spu_queue), GFP_KERNEL);
	अगर (!p) अणु
		dev_err(&dev->dev, "%pOF: Could not allocate SPU queue.\n",
			dev->dev.of_node);
		वापस -ENOMEM;
	पूर्ण

	cpumask_clear(&p->sharing);
	spin_lock_init(&p->lock);
	p->q_type = q_type;
	INIT_LIST_HEAD(&p->jobs);
	list_add(&p->list, list);

	err = spu_mdesc_walk_arcs(mdesc, dev, node, p, table);
	अगर (err)
		वापस err;

	err = spu_queue_setup(p);
	अगर (err)
		वापस err;

	वापस spu_map_ino(dev, ip, iname, p, handler);
पूर्ण

अटल पूर्णांक spu_mdesc_scan(काष्ठा mdesc_handle *mdesc, काष्ठा platक्रमm_device *dev,
			  काष्ठा spu_mdesc_info *ip, काष्ठा list_head *list,
			  स्थिर अक्षर *exec_name, अचिन्हित दीर्घ q_type,
			  irq_handler_t handler, काष्ठा spu_queue **table)
अणु
	पूर्णांक err = 0;
	u64 node;

	mdesc_क्रम_each_node_by_name(mdesc, node, "exec-unit") अणु
		स्थिर अक्षर *type;

		type = mdesc_get_property(mdesc, node, "type", शून्य);
		अगर (!type || म_भेद(type, exec_name))
			जारी;

		err = handle_exec_unit(ip, list, dev, mdesc, node,
				       exec_name, q_type, handler, table);
		अगर (err) अणु
			spu_list_destroy(list);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक get_irq_props(काष्ठा mdesc_handle *mdesc, u64 node,
			 काष्ठा spu_mdesc_info *ip)
अणु
	स्थिर u64 *ino;
	पूर्णांक ino_len;
	पूर्णांक i;

	ino = mdesc_get_property(mdesc, node, "ino", &ino_len);
	अगर (!ino) अणु
		prपूर्णांकk("NO 'ino'\n");
		वापस -ENODEV;
	पूर्ण

	ip->num_पूर्णांकrs = ino_len / माप(u64);
	ip->ino_table = kzalloc((माप(काष्ठा ino_blob) *
				 ip->num_पूर्णांकrs),
				GFP_KERNEL);
	अगर (!ip->ino_table)
		वापस -ENOMEM;

	क्रम (i = 0; i < ip->num_पूर्णांकrs; i++) अणु
		काष्ठा ino_blob *b = &ip->ino_table[i];
		b->पूर्णांकr = i + 1;
		b->ino = ino[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक grab_mdesc_irq_props(काष्ठा mdesc_handle *mdesc,
				काष्ठा platक्रमm_device *dev,
				काष्ठा spu_mdesc_info *ip,
				स्थिर अक्षर *node_name)
अणु
	स्थिर अचिन्हित पूर्णांक *reg;
	u64 node;

	reg = of_get_property(dev->dev.of_node, "reg", शून्य);
	अगर (!reg)
		वापस -ENODEV;

	mdesc_क्रम_each_node_by_name(mdesc, node, "virtual-device") अणु
		स्थिर अक्षर *name;
		स्थिर u64 *chdl;

		name = mdesc_get_property(mdesc, node, "name", शून्य);
		अगर (!name || म_भेद(name, node_name))
			जारी;
		chdl = mdesc_get_property(mdesc, node, "cfg-handle", शून्य);
		अगर (!chdl || (*chdl != *reg))
			जारी;
		ip->cfg_handle = *chdl;
		वापस get_irq_props(mdesc, node, ip);
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल अचिन्हित दीर्घ n2_spu_hvapi_major;
अटल अचिन्हित दीर्घ n2_spu_hvapi_minor;

अटल पूर्णांक n2_spu_hvapi_रेजिस्टर(व्योम)
अणु
	पूर्णांक err;

	n2_spu_hvapi_major = 2;
	n2_spu_hvapi_minor = 0;

	err = sun4v_hvapi_रेजिस्टर(HV_GRP_NCS,
				   n2_spu_hvapi_major,
				   &n2_spu_hvapi_minor);

	अगर (!err)
		pr_info("Registered NCS HVAPI version %lu.%lu\n",
			n2_spu_hvapi_major,
			n2_spu_hvapi_minor);

	वापस err;
पूर्ण

अटल व्योम n2_spu_hvapi_unरेजिस्टर(व्योम)
अणु
	sun4v_hvapi_unरेजिस्टर(HV_GRP_NCS);
पूर्ण

अटल पूर्णांक global_ref;

अटल पूर्णांक grab_global_resources(व्योम)
अणु
	पूर्णांक err = 0;

	mutex_lock(&spu_lock);

	अगर (global_ref++)
		जाओ out;

	err = n2_spu_hvapi_रेजिस्टर();
	अगर (err)
		जाओ out;

	err = queue_cache_init();
	अगर (err)
		जाओ out_hvapi_release;

	err = -ENOMEM;
	cpu_to_cwq = kसुस्मृति(NR_CPUS, माप(काष्ठा spu_queue *),
			     GFP_KERNEL);
	अगर (!cpu_to_cwq)
		जाओ out_queue_cache_destroy;

	cpu_to_mau = kसुस्मृति(NR_CPUS, माप(काष्ठा spu_queue *),
			     GFP_KERNEL);
	अगर (!cpu_to_mau)
		जाओ out_मुक्त_cwq_table;

	err = 0;

out:
	अगर (err)
		global_ref--;
	mutex_unlock(&spu_lock);
	वापस err;

out_मुक्त_cwq_table:
	kमुक्त(cpu_to_cwq);
	cpu_to_cwq = शून्य;

out_queue_cache_destroy:
	queue_cache_destroy();

out_hvapi_release:
	n2_spu_hvapi_unरेजिस्टर();
	जाओ out;
पूर्ण

अटल व्योम release_global_resources(व्योम)
अणु
	mutex_lock(&spu_lock);
	अगर (!--global_ref) अणु
		kमुक्त(cpu_to_cwq);
		cpu_to_cwq = शून्य;

		kमुक्त(cpu_to_mau);
		cpu_to_mau = शून्य;

		queue_cache_destroy();
		n2_spu_hvapi_unरेजिस्टर();
	पूर्ण
	mutex_unlock(&spu_lock);
पूर्ण

अटल काष्ठा n2_crypto *alloc_n2cp(व्योम)
अणु
	काष्ठा n2_crypto *np = kzalloc(माप(काष्ठा n2_crypto), GFP_KERNEL);

	अगर (np)
		INIT_LIST_HEAD(&np->cwq_list);

	वापस np;
पूर्ण

अटल व्योम मुक्त_n2cp(काष्ठा n2_crypto *np)
अणु
	kमुक्त(np->cwq_info.ino_table);
	np->cwq_info.ino_table = शून्य;

	kमुक्त(np);
पूर्ण

अटल व्योम n2_spu_driver_version(व्योम)
अणु
	अटल पूर्णांक n2_spu_version_prपूर्णांकed;

	अगर (n2_spu_version_prपूर्णांकed++ == 0)
		pr_info("%s", version);
पूर्ण

अटल पूर्णांक n2_crypto_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mdesc_handle *mdesc;
	काष्ठा n2_crypto *np;
	पूर्णांक err;

	n2_spu_driver_version();

	pr_info("Found N2CP at %pOF\n", dev->dev.of_node);

	np = alloc_n2cp();
	अगर (!np) अणु
		dev_err(&dev->dev, "%pOF: Unable to allocate n2cp.\n",
			dev->dev.of_node);
		वापस -ENOMEM;
	पूर्ण

	err = grab_global_resources();
	अगर (err) अणु
		dev_err(&dev->dev, "%pOF: Unable to grab global resources.\n",
			dev->dev.of_node);
		जाओ out_मुक्त_n2cp;
	पूर्ण

	mdesc = mdesc_grab();

	अगर (!mdesc) अणु
		dev_err(&dev->dev, "%pOF: Unable to grab MDESC.\n",
			dev->dev.of_node);
		err = -ENODEV;
		जाओ out_मुक्त_global;
	पूर्ण
	err = grab_mdesc_irq_props(mdesc, dev, &np->cwq_info, "n2cp");
	अगर (err) अणु
		dev_err(&dev->dev, "%pOF: Unable to grab IRQ props.\n",
			dev->dev.of_node);
		mdesc_release(mdesc);
		जाओ out_मुक्त_global;
	पूर्ण

	err = spu_mdesc_scan(mdesc, dev, &np->cwq_info, &np->cwq_list,
			     "cwq", HV_NCS_QTYPE_CWQ, cwq_पूर्णांकr,
			     cpu_to_cwq);
	mdesc_release(mdesc);

	अगर (err) अणु
		dev_err(&dev->dev, "%pOF: CWQ MDESC scan failed.\n",
			dev->dev.of_node);
		जाओ out_मुक्त_global;
	पूर्ण

	err = n2_रेजिस्टर_algs();
	अगर (err) अणु
		dev_err(&dev->dev, "%pOF: Unable to register algorithms.\n",
			dev->dev.of_node);
		जाओ out_मुक्त_spu_list;
	पूर्ण

	dev_set_drvdata(&dev->dev, np);

	वापस 0;

out_मुक्त_spu_list:
	spu_list_destroy(&np->cwq_list);

out_मुक्त_global:
	release_global_resources();

out_मुक्त_n2cp:
	मुक्त_n2cp(np);

	वापस err;
पूर्ण

अटल पूर्णांक n2_crypto_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा n2_crypto *np = dev_get_drvdata(&dev->dev);

	n2_unरेजिस्टर_algs();

	spu_list_destroy(&np->cwq_list);

	release_global_resources();

	मुक्त_n2cp(np);

	वापस 0;
पूर्ण

अटल काष्ठा n2_mau *alloc_ncp(व्योम)
अणु
	काष्ठा n2_mau *mp = kzalloc(माप(काष्ठा n2_mau), GFP_KERNEL);

	अगर (mp)
		INIT_LIST_HEAD(&mp->mau_list);

	वापस mp;
पूर्ण

अटल व्योम मुक्त_ncp(काष्ठा n2_mau *mp)
अणु
	kमुक्त(mp->mau_info.ino_table);
	mp->mau_info.ino_table = शून्य;

	kमुक्त(mp);
पूर्ण

अटल पूर्णांक n2_mau_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mdesc_handle *mdesc;
	काष्ठा n2_mau *mp;
	पूर्णांक err;

	n2_spu_driver_version();

	pr_info("Found NCP at %pOF\n", dev->dev.of_node);

	mp = alloc_ncp();
	अगर (!mp) अणु
		dev_err(&dev->dev, "%pOF: Unable to allocate ncp.\n",
			dev->dev.of_node);
		वापस -ENOMEM;
	पूर्ण

	err = grab_global_resources();
	अगर (err) अणु
		dev_err(&dev->dev, "%pOF: Unable to grab global resources.\n",
			dev->dev.of_node);
		जाओ out_मुक्त_ncp;
	पूर्ण

	mdesc = mdesc_grab();

	अगर (!mdesc) अणु
		dev_err(&dev->dev, "%pOF: Unable to grab MDESC.\n",
			dev->dev.of_node);
		err = -ENODEV;
		जाओ out_मुक्त_global;
	पूर्ण

	err = grab_mdesc_irq_props(mdesc, dev, &mp->mau_info, "ncp");
	अगर (err) अणु
		dev_err(&dev->dev, "%pOF: Unable to grab IRQ props.\n",
			dev->dev.of_node);
		mdesc_release(mdesc);
		जाओ out_मुक्त_global;
	पूर्ण

	err = spu_mdesc_scan(mdesc, dev, &mp->mau_info, &mp->mau_list,
			     "mau", HV_NCS_QTYPE_MAU, mau_पूर्णांकr,
			     cpu_to_mau);
	mdesc_release(mdesc);

	अगर (err) अणु
		dev_err(&dev->dev, "%pOF: MAU MDESC scan failed.\n",
			dev->dev.of_node);
		जाओ out_मुक्त_global;
	पूर्ण

	dev_set_drvdata(&dev->dev, mp);

	वापस 0;

out_मुक्त_global:
	release_global_resources();

out_मुक्त_ncp:
	मुक्त_ncp(mp);

	वापस err;
पूर्ण

अटल पूर्णांक n2_mau_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा n2_mau *mp = dev_get_drvdata(&dev->dev);

	spu_list_destroy(&mp->mau_list);

	release_global_resources();

	मुक्त_ncp(mp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id n2_crypto_match[] = अणु
	अणु
		.name = "n2cp",
		.compatible = "SUNW,n2-cwq",
	पूर्ण,
	अणु
		.name = "n2cp",
		.compatible = "SUNW,vf-cwq",
	पूर्ण,
	अणु
		.name = "n2cp",
		.compatible = "SUNW,kt-cwq",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, n2_crypto_match);

अटल काष्ठा platक्रमm_driver n2_crypto_driver = अणु
	.driver = अणु
		.name		=	"n2cp",
		.of_match_table	=	n2_crypto_match,
	पूर्ण,
	.probe		=	n2_crypto_probe,
	.हटाओ		=	n2_crypto_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा of_device_id n2_mau_match[] = अणु
	अणु
		.name = "ncp",
		.compatible = "SUNW,n2-mau",
	पूर्ण,
	अणु
		.name = "ncp",
		.compatible = "SUNW,vf-mau",
	पूर्ण,
	अणु
		.name = "ncp",
		.compatible = "SUNW,kt-mau",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, n2_mau_match);

अटल काष्ठा platक्रमm_driver n2_mau_driver = अणु
	.driver = अणु
		.name		=	"ncp",
		.of_match_table	=	n2_mau_match,
	पूर्ण,
	.probe		=	n2_mau_probe,
	.हटाओ		=	n2_mau_हटाओ,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&n2_crypto_driver,
	&n2_mau_driver,
पूर्ण;

अटल पूर्णांक __init n2_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण

अटल व्योम __निकास n2_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण

module_init(n2_init);
module_निकास(n2_निकास);
