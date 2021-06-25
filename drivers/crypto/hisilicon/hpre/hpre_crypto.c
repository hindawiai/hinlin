<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 HiSilicon Limited. */
#समावेश <crypto/akcipher.h>
#समावेश <crypto/curve25519.h>
#समावेश <crypto/dh.h>
#समावेश <crypto/ecc_curve.h>
#समावेश <crypto/ecdh.h>
#समावेश <crypto/पूर्णांकernal/akcipher.h>
#समावेश <crypto/पूर्णांकernal/kpp.h>
#समावेश <crypto/पूर्णांकernal/rsa.h>
#समावेश <crypto/kpp.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fips.h>
#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश "hpre.h"

काष्ठा hpre_ctx;

#घोषणा HPRE_CRYPTO_ALG_PRI	1000
#घोषणा HPRE_ALIGN_SZ		64
#घोषणा HPRE_BITS_2_BYTES_SHIFT	3
#घोषणा HPRE_RSA_512BITS_KSZ	64
#घोषणा HPRE_RSA_1536BITS_KSZ	192
#घोषणा HPRE_CRT_PRMS		5
#घोषणा HPRE_CRT_Q		2
#घोषणा HPRE_CRT_P		3
#घोषणा HPRE_CRT_INV		4
#घोषणा HPRE_DH_G_FLAG		0x02
#घोषणा HPRE_TRY_SEND_TIMES	100
#घोषणा HPRE_INVLD_REQ_ID		(-1)
#घोषणा HPRE_DEV(ctx)		(&((ctx)->qp->qm->pdev->dev))

#घोषणा HPRE_SQE_ALG_BITS	5
#घोषणा HPRE_SQE_DONE_SHIFT	30
#घोषणा HPRE_DH_MAX_P_SZ	512

#घोषणा HPRE_DFX_SEC_TO_US	1000000
#घोषणा HPRE_DFX_US_TO_NS	1000

/* size in bytes of the n prime */
#घोषणा HPRE_ECC_NIST_P192_N_SIZE	24
#घोषणा HPRE_ECC_NIST_P256_N_SIZE	32

/* size in bytes */
#घोषणा HPRE_ECC_HW256_KSZ_B	32

प्रकार व्योम (*hpre_cb)(काष्ठा hpre_ctx *ctx, व्योम *sqe);

काष्ठा hpre_rsa_ctx अणु
	/* low address: e--->n */
	अक्षर *pubkey;
	dma_addr_t dma_pubkey;

	/* low address: d--->n */
	अक्षर *prikey;
	dma_addr_t dma_prikey;

	/* low address: dq->dp->q->p->qinv */
	अक्षर *crt_prikey;
	dma_addr_t dma_crt_prikey;

	काष्ठा crypto_akcipher *soft_tfm;
पूर्ण;

काष्ठा hpre_dh_ctx अणु
	/*
	 * If base is g we compute the खुला key
	 *	ya = g^xa mod p; [RFC2631 sec 2.1.1]
	 * अन्यथा अगर base अगर the counterpart खुला key we
	 * compute the shared secret
	 *	ZZ = yb^xa mod p; [RFC2631 sec 2.1.1]
	 * low address: d--->n, please refer to Hisilicon HPRE UM
	 */
	अक्षर *xa_p;
	dma_addr_t dma_xa_p;

	अक्षर *g; /* m */
	dma_addr_t dma_g;
पूर्ण;

काष्ठा hpre_ecdh_ctx अणु
	/* low address: p->a->k->b */
	अचिन्हित अक्षर *p;
	dma_addr_t dma_p;

	/* low address: x->y */
	अचिन्हित अक्षर *g;
	dma_addr_t dma_g;
पूर्ण;

काष्ठा hpre_curve25519_ctx अणु
	/* low address: p->a->k */
	अचिन्हित अक्षर *p;
	dma_addr_t dma_p;

	/* gx coordinate */
	अचिन्हित अक्षर *g;
	dma_addr_t dma_g;
पूर्ण;

काष्ठा hpre_ctx अणु
	काष्ठा hisi_qp *qp;
	काष्ठा hpre_asym_request **req_list;
	काष्ठा hpre *hpre;
	spinlock_t req_lock;
	अचिन्हित पूर्णांक key_sz;
	bool crt_g2_mode;
	काष्ठा idr req_idr;
	जोड़ अणु
		काष्ठा hpre_rsa_ctx rsa;
		काष्ठा hpre_dh_ctx dh;
		काष्ठा hpre_ecdh_ctx ecdh;
		काष्ठा hpre_curve25519_ctx curve25519;
	पूर्ण;
	/* क्रम ecc algorithms */
	अचिन्हित पूर्णांक curve_id;
पूर्ण;

काष्ठा hpre_asym_request अणु
	अक्षर *src;
	अक्षर *dst;
	काष्ठा hpre_sqe req;
	काष्ठा hpre_ctx *ctx;
	जोड़ अणु
		काष्ठा akcipher_request *rsa;
		काष्ठा kpp_request *dh;
		काष्ठा kpp_request *ecdh;
		काष्ठा kpp_request *curve25519;
	पूर्ण areq;
	पूर्णांक err;
	पूर्णांक req_id;
	hpre_cb cb;
	काष्ठा बारpec64 req_समय;
पूर्ण;

अटल पूर्णांक hpre_alloc_req_id(काष्ठा hpre_ctx *ctx)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक id;

	spin_lock_irqsave(&ctx->req_lock, flags);
	id = idr_alloc(&ctx->req_idr, शून्य, 0, QM_Q_DEPTH, GFP_ATOMIC);
	spin_unlock_irqrestore(&ctx->req_lock, flags);

	वापस id;
पूर्ण

अटल व्योम hpre_मुक्त_req_id(काष्ठा hpre_ctx *ctx, पूर्णांक req_id)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->req_lock, flags);
	idr_हटाओ(&ctx->req_idr, req_id);
	spin_unlock_irqrestore(&ctx->req_lock, flags);
पूर्ण

अटल पूर्णांक hpre_add_req_to_ctx(काष्ठा hpre_asym_request *hpre_req)
अणु
	काष्ठा hpre_ctx *ctx;
	काष्ठा hpre_dfx *dfx;
	पूर्णांक id;

	ctx = hpre_req->ctx;
	id = hpre_alloc_req_id(ctx);
	अगर (unlikely(id < 0))
		वापस -EINVAL;

	ctx->req_list[id] = hpre_req;
	hpre_req->req_id = id;

	dfx = ctx->hpre->debug.dfx;
	अगर (atomic64_पढ़ो(&dfx[HPRE_OVERTIME_THRHLD].value))
		kसमय_get_ts64(&hpre_req->req_समय);

	वापस id;
पूर्ण

अटल व्योम hpre_rm_req_from_ctx(काष्ठा hpre_asym_request *hpre_req)
अणु
	काष्ठा hpre_ctx *ctx = hpre_req->ctx;
	पूर्णांक id = hpre_req->req_id;

	अगर (hpre_req->req_id >= 0) अणु
		hpre_req->req_id = HPRE_INVLD_REQ_ID;
		ctx->req_list[id] = शून्य;
		hpre_मुक्त_req_id(ctx, id);
	पूर्ण
पूर्ण

अटल काष्ठा hisi_qp *hpre_get_qp_and_start(u8 type)
अणु
	काष्ठा hisi_qp *qp;
	पूर्णांक ret;

	qp = hpre_create_qp(type);
	अगर (!qp) अणु
		pr_err("Can not create hpre qp!\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	ret = hisi_qm_start_qp(qp, 0);
	अगर (ret < 0) अणु
		hisi_qm_मुक्त_qps(&qp, 1);
		pci_err(qp->qm->pdev, "Can not start qp!\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस qp;
पूर्ण

अटल पूर्णांक hpre_get_data_dma_addr(काष्ठा hpre_asym_request *hpre_req,
				  काष्ठा scatterlist *data, अचिन्हित पूर्णांक len,
				  पूर्णांक is_src, dma_addr_t *पंचांगp)
अणु
	काष्ठा hpre_ctx *ctx = hpre_req->ctx;
	काष्ठा device *dev = HPRE_DEV(ctx);
	क्रमागत dma_data_direction dma_dir;

	अगर (is_src) अणु
		hpre_req->src = शून्य;
		dma_dir = DMA_TO_DEVICE;
	पूर्ण अन्यथा अणु
		hpre_req->dst = शून्य;
		dma_dir = DMA_FROM_DEVICE;
	पूर्ण
	*पंचांगp = dma_map_single(dev, sg_virt(data), len, dma_dir);
	अगर (unlikely(dma_mapping_error(dev, *पंचांगp))) अणु
		dev_err(dev, "dma map data err!\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_prepare_dma_buf(काष्ठा hpre_asym_request *hpre_req,
				काष्ठा scatterlist *data, अचिन्हित पूर्णांक len,
				पूर्णांक is_src, dma_addr_t *पंचांगp)
अणु
	काष्ठा hpre_ctx *ctx = hpre_req->ctx;
	काष्ठा device *dev = HPRE_DEV(ctx);
	व्योम *ptr;
	पूर्णांक shअगरt;

	shअगरt = ctx->key_sz - len;
	अगर (unlikely(shअगरt < 0))
		वापस -EINVAL;

	ptr = dma_alloc_coherent(dev, ctx->key_sz, पंचांगp, GFP_KERNEL);
	अगर (unlikely(!ptr))
		वापस -ENOMEM;

	अगर (is_src) अणु
		scatterwalk_map_and_copy(ptr + shअगरt, data, 0, len, 0);
		hpre_req->src = ptr;
	पूर्ण अन्यथा अणु
		hpre_req->dst = ptr;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_hw_data_init(काष्ठा hpre_asym_request *hpre_req,
			     काष्ठा scatterlist *data, अचिन्हित पूर्णांक len,
			     पूर्णांक is_src, पूर्णांक is_dh)
अणु
	काष्ठा hpre_sqe *msg = &hpre_req->req;
	काष्ठा hpre_ctx *ctx = hpre_req->ctx;
	dma_addr_t पंचांगp = 0;
	पूर्णांक ret;

	/* when the data is dh's source, we should क्रमmat it */
	अगर ((sg_is_last(data) && len == ctx->key_sz) &&
	    ((is_dh && !is_src) || !is_dh))
		ret = hpre_get_data_dma_addr(hpre_req, data, len, is_src, &पंचांगp);
	अन्यथा
		ret = hpre_prepare_dma_buf(hpre_req, data, len, is_src, &पंचांगp);

	अगर (unlikely(ret))
		वापस ret;

	अगर (is_src)
		msg->in = cpu_to_le64(पंचांगp);
	अन्यथा
		msg->out = cpu_to_le64(पंचांगp);

	वापस 0;
पूर्ण

अटल व्योम hpre_hw_data_clr_all(काष्ठा hpre_ctx *ctx,
				 काष्ठा hpre_asym_request *req,
				 काष्ठा scatterlist *dst,
				 काष्ठा scatterlist *src)
अणु
	काष्ठा device *dev = HPRE_DEV(ctx);
	काष्ठा hpre_sqe *sqe = &req->req;
	dma_addr_t पंचांगp;

	पंचांगp = le64_to_cpu(sqe->in);

	अगर (src) अणु
		अगर (req->src)
			dma_मुक्त_coherent(dev, ctx->key_sz, req->src, पंचांगp);
		अन्यथा
			dma_unmap_single(dev, पंचांगp, ctx->key_sz, DMA_TO_DEVICE);
	पूर्ण

	पंचांगp = le64_to_cpu(sqe->out);

	अगर (req->dst) अणु
		अगर (dst)
			scatterwalk_map_and_copy(req->dst, dst, 0,
						 ctx->key_sz, 1);
		dma_मुक्त_coherent(dev, ctx->key_sz, req->dst, पंचांगp);
	पूर्ण अन्यथा अणु
		dma_unmap_single(dev, पंचांगp, ctx->key_sz, DMA_FROM_DEVICE);
	पूर्ण
पूर्ण

अटल पूर्णांक hpre_alg_res_post_hf(काष्ठा hpre_ctx *ctx, काष्ठा hpre_sqe *sqe,
				व्योम **kreq)
अणु
	काष्ठा device *dev = HPRE_DEV(ctx);
	काष्ठा hpre_asym_request *req;
	अचिन्हित पूर्णांक err, करोne, alg;
	पूर्णांक id;

#घोषणा HPRE_NO_HW_ERR		0
#घोषणा HPRE_HW_TASK_DONE	3
#घोषणा HREE_HW_ERR_MASK	0x7ff
#घोषणा HREE_SQE_DONE_MASK	0x3
#घोषणा HREE_ALG_TYPE_MASK	0x1f
	id = (पूर्णांक)le16_to_cpu(sqe->tag);
	req = ctx->req_list[id];
	hpre_rm_req_from_ctx(req);
	*kreq = req;

	err = (le32_to_cpu(sqe->dw0) >> HPRE_SQE_ALG_BITS) &
		HREE_HW_ERR_MASK;

	करोne = (le32_to_cpu(sqe->dw0) >> HPRE_SQE_DONE_SHIFT) &
		HREE_SQE_DONE_MASK;

	अगर (likely(err == HPRE_NO_HW_ERR && करोne == HPRE_HW_TASK_DONE))
		वापस 0;

	alg = le32_to_cpu(sqe->dw0) & HREE_ALG_TYPE_MASK;
	dev_err_ratelimited(dev, "alg[0x%x] error: done[0x%x], etype[0x%x]\n",
		alg, करोne, err);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hpre_ctx_set(काष्ठा hpre_ctx *ctx, काष्ठा hisi_qp *qp, पूर्णांक qlen)
अणु
	काष्ठा hpre *hpre;

	अगर (!ctx || !qp || qlen < 0)
		वापस -EINVAL;

	spin_lock_init(&ctx->req_lock);
	ctx->qp = qp;

	hpre = container_of(ctx->qp->qm, काष्ठा hpre, qm);
	ctx->hpre = hpre;
	ctx->req_list = kसुस्मृति(qlen, माप(व्योम *), GFP_KERNEL);
	अगर (!ctx->req_list)
		वापस -ENOMEM;
	ctx->key_sz = 0;
	ctx->crt_g2_mode = false;
	idr_init(&ctx->req_idr);

	वापस 0;
पूर्ण

अटल व्योम hpre_ctx_clear(काष्ठा hpre_ctx *ctx, bool is_clear_all)
अणु
	अगर (is_clear_all) अणु
		idr_destroy(&ctx->req_idr);
		kमुक्त(ctx->req_list);
		hisi_qm_मुक्त_qps(&ctx->qp, 1);
	पूर्ण

	ctx->crt_g2_mode = false;
	ctx->key_sz = 0;
पूर्ण

अटल bool hpre_is_bd_समयout(काष्ठा hpre_asym_request *req,
			       u64 overसमय_प्रकारhrhld)
अणु
	काष्ठा बारpec64 reply_समय;
	u64 समय_use_us;

	kसमय_get_ts64(&reply_समय);
	समय_use_us = (reply_समय.tv_sec - req->req_समय.tv_sec) *
		HPRE_DFX_SEC_TO_US +
		(reply_समय.tv_nsec - req->req_समय.tv_nsec) /
		HPRE_DFX_US_TO_NS;

	अगर (समय_use_us <= overसमय_प्रकारhrhld)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम hpre_dh_cb(काष्ठा hpre_ctx *ctx, व्योम *resp)
अणु
	काष्ठा hpre_dfx *dfx = ctx->hpre->debug.dfx;
	काष्ठा hpre_asym_request *req;
	काष्ठा kpp_request *areq;
	u64 overसमय_प्रकारhrhld;
	पूर्णांक ret;

	ret = hpre_alg_res_post_hf(ctx, resp, (व्योम **)&req);
	areq = req->areq.dh;
	areq->dst_len = ctx->key_sz;

	overसमय_प्रकारhrhld = atomic64_पढ़ो(&dfx[HPRE_OVERTIME_THRHLD].value);
	अगर (overसमय_प्रकारhrhld && hpre_is_bd_समयout(req, overसमय_प्रकारhrhld))
		atomic64_inc(&dfx[HPRE_OVER_THRHLD_CNT].value);

	hpre_hw_data_clr_all(ctx, req, areq->dst, areq->src);
	kpp_request_complete(areq, ret);
	atomic64_inc(&dfx[HPRE_RECV_CNT].value);
पूर्ण

अटल व्योम hpre_rsa_cb(काष्ठा hpre_ctx *ctx, व्योम *resp)
अणु
	काष्ठा hpre_dfx *dfx = ctx->hpre->debug.dfx;
	काष्ठा hpre_asym_request *req;
	काष्ठा akcipher_request *areq;
	u64 overसमय_प्रकारhrhld;
	पूर्णांक ret;

	ret = hpre_alg_res_post_hf(ctx, resp, (व्योम **)&req);

	overसमय_प्रकारhrhld = atomic64_पढ़ो(&dfx[HPRE_OVERTIME_THRHLD].value);
	अगर (overसमय_प्रकारhrhld && hpre_is_bd_समयout(req, overसमय_प्रकारhrhld))
		atomic64_inc(&dfx[HPRE_OVER_THRHLD_CNT].value);

	areq = req->areq.rsa;
	areq->dst_len = ctx->key_sz;
	hpre_hw_data_clr_all(ctx, req, areq->dst, areq->src);
	akcipher_request_complete(areq, ret);
	atomic64_inc(&dfx[HPRE_RECV_CNT].value);
पूर्ण

अटल व्योम hpre_alg_cb(काष्ठा hisi_qp *qp, व्योम *resp)
अणु
	काष्ठा hpre_ctx *ctx = qp->qp_ctx;
	काष्ठा hpre_dfx *dfx = ctx->hpre->debug.dfx;
	काष्ठा hpre_sqe *sqe = resp;
	काष्ठा hpre_asym_request *req = ctx->req_list[le16_to_cpu(sqe->tag)];

	अगर (unlikely(!req)) अणु
		atomic64_inc(&dfx[HPRE_INVALID_REQ_CNT].value);
		वापस;
	पूर्ण

	req->cb(ctx, resp);
पूर्ण

अटल व्योम hpre_stop_qp_and_put(काष्ठा hisi_qp *qp)
अणु
	hisi_qm_stop_qp(qp);
	hisi_qm_मुक्त_qps(&qp, 1);
पूर्ण

अटल पूर्णांक hpre_ctx_init(काष्ठा hpre_ctx *ctx, u8 type)
अणु
	काष्ठा hisi_qp *qp;
	पूर्णांक ret;

	qp = hpre_get_qp_and_start(type);
	अगर (IS_ERR(qp))
		वापस PTR_ERR(qp);

	qp->qp_ctx = ctx;
	qp->req_cb = hpre_alg_cb;

	ret = hpre_ctx_set(ctx, qp, QM_Q_DEPTH);
	अगर (ret)
		hpre_stop_qp_and_put(qp);

	वापस ret;
पूर्ण

अटल पूर्णांक hpre_msg_request_set(काष्ठा hpre_ctx *ctx, व्योम *req, bool is_rsa)
अणु
	काष्ठा hpre_asym_request *h_req;
	काष्ठा hpre_sqe *msg;
	पूर्णांक req_id;
	व्योम *पंचांगp;

	अगर (is_rsa) अणु
		काष्ठा akcipher_request *akreq = req;

		अगर (akreq->dst_len < ctx->key_sz) अणु
			akreq->dst_len = ctx->key_sz;
			वापस -EOVERFLOW;
		पूर्ण

		पंचांगp = akcipher_request_ctx(akreq);
		h_req = PTR_ALIGN(पंचांगp, HPRE_ALIGN_SZ);
		h_req->cb = hpre_rsa_cb;
		h_req->areq.rsa = akreq;
		msg = &h_req->req;
		स_रखो(msg, 0, माप(*msg));
	पूर्ण अन्यथा अणु
		काष्ठा kpp_request *kreq = req;

		अगर (kreq->dst_len < ctx->key_sz) अणु
			kreq->dst_len = ctx->key_sz;
			वापस -EOVERFLOW;
		पूर्ण

		पंचांगp = kpp_request_ctx(kreq);
		h_req = PTR_ALIGN(पंचांगp, HPRE_ALIGN_SZ);
		h_req->cb = hpre_dh_cb;
		h_req->areq.dh = kreq;
		msg = &h_req->req;
		स_रखो(msg, 0, माप(*msg));
		msg->key = cpu_to_le64(ctx->dh.dma_xa_p);
	पूर्ण

	msg->dw0 |= cpu_to_le32(0x1 << HPRE_SQE_DONE_SHIFT);
	msg->task_len1 = (ctx->key_sz >> HPRE_BITS_2_BYTES_SHIFT) - 1;
	h_req->ctx = ctx;

	req_id = hpre_add_req_to_ctx(h_req);
	अगर (req_id < 0)
		वापस -EBUSY;

	msg->tag = cpu_to_le16((u16)req_id);

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_send(काष्ठा hpre_ctx *ctx, काष्ठा hpre_sqe *msg)
अणु
	काष्ठा hpre_dfx *dfx = ctx->hpre->debug.dfx;
	पूर्णांक ctr = 0;
	पूर्णांक ret;

	करो अणु
		atomic64_inc(&dfx[HPRE_SEND_CNT].value);
		ret = hisi_qp_send(ctx->qp, msg);
		अगर (ret != -EBUSY)
			अवरोध;
		atomic64_inc(&dfx[HPRE_SEND_BUSY_CNT].value);
	पूर्ण जबतक (ctr++ < HPRE_TRY_SEND_TIMES);

	अगर (likely(!ret))
		वापस ret;

	अगर (ret != -EBUSY)
		atomic64_inc(&dfx[HPRE_SEND_FAIL_CNT].value);

	वापस ret;
पूर्ण

अटल पूर्णांक hpre_dh_compute_value(काष्ठा kpp_request *req)
अणु
	काष्ठा crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);
	व्योम *पंचांगp = kpp_request_ctx(req);
	काष्ठा hpre_asym_request *hpre_req = PTR_ALIGN(पंचांगp, HPRE_ALIGN_SZ);
	काष्ठा hpre_sqe *msg = &hpre_req->req;
	पूर्णांक ret;

	ret = hpre_msg_request_set(ctx, req, false);
	अगर (unlikely(ret))
		वापस ret;

	अगर (req->src) अणु
		ret = hpre_hw_data_init(hpre_req, req->src, req->src_len, 1, 1);
		अगर (unlikely(ret))
			जाओ clear_all;
	पूर्ण अन्यथा अणु
		msg->in = cpu_to_le64(ctx->dh.dma_g);
	पूर्ण

	ret = hpre_hw_data_init(hpre_req, req->dst, req->dst_len, 0, 1);
	अगर (unlikely(ret))
		जाओ clear_all;

	अगर (ctx->crt_g2_mode && !req->src)
		msg->dw0 = cpu_to_le32(le32_to_cpu(msg->dw0) | HPRE_ALG_DH_G2);
	अन्यथा
		msg->dw0 = cpu_to_le32(le32_to_cpu(msg->dw0) | HPRE_ALG_DH);

	/* success */
	ret = hpre_send(ctx, msg);
	अगर (likely(!ret))
		वापस -EINPROGRESS;

clear_all:
	hpre_rm_req_from_ctx(hpre_req);
	hpre_hw_data_clr_all(ctx, hpre_req, req->dst, req->src);

	वापस ret;
पूर्ण

अटल पूर्णांक hpre_is_dh_params_length_valid(अचिन्हित पूर्णांक key_sz)
अणु
#घोषणा _HPRE_DH_GRP1		768
#घोषणा _HPRE_DH_GRP2		1024
#घोषणा _HPRE_DH_GRP5		1536
#घोषणा _HPRE_DH_GRP14		2048
#घोषणा _HPRE_DH_GRP15		3072
#घोषणा _HPRE_DH_GRP16		4096
	चयन (key_sz) अणु
	हाल _HPRE_DH_GRP1:
	हाल _HPRE_DH_GRP2:
	हाल _HPRE_DH_GRP5:
	हाल _HPRE_DH_GRP14:
	हाल _HPRE_DH_GRP15:
	हाल _HPRE_DH_GRP16:
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hpre_dh_set_params(काष्ठा hpre_ctx *ctx, काष्ठा dh *params)
अणु
	काष्ठा device *dev = HPRE_DEV(ctx);
	अचिन्हित पूर्णांक sz;

	अगर (params->p_size > HPRE_DH_MAX_P_SZ)
		वापस -EINVAL;

	अगर (hpre_is_dh_params_length_valid(params->p_size <<
					   HPRE_BITS_2_BYTES_SHIFT))
		वापस -EINVAL;

	sz = ctx->key_sz = params->p_size;
	ctx->dh.xa_p = dma_alloc_coherent(dev, sz << 1,
					  &ctx->dh.dma_xa_p, GFP_KERNEL);
	अगर (!ctx->dh.xa_p)
		वापस -ENOMEM;

	स_नकल(ctx->dh.xa_p + sz, params->p, sz);

	/* If g equals 2 करोn't copy it */
	अगर (params->g_size == 1 && *(अक्षर *)params->g == HPRE_DH_G_FLAG) अणु
		ctx->crt_g2_mode = true;
		वापस 0;
	पूर्ण

	ctx->dh.g = dma_alloc_coherent(dev, sz, &ctx->dh.dma_g, GFP_KERNEL);
	अगर (!ctx->dh.g) अणु
		dma_मुक्त_coherent(dev, sz << 1, ctx->dh.xa_p,
				  ctx->dh.dma_xa_p);
		ctx->dh.xa_p = शून्य;
		वापस -ENOMEM;
	पूर्ण

	स_नकल(ctx->dh.g + (sz - params->g_size), params->g, params->g_size);

	वापस 0;
पूर्ण

अटल व्योम hpre_dh_clear_ctx(काष्ठा hpre_ctx *ctx, bool is_clear_all)
अणु
	काष्ठा device *dev = HPRE_DEV(ctx);
	अचिन्हित पूर्णांक sz = ctx->key_sz;

	अगर (is_clear_all)
		hisi_qm_stop_qp(ctx->qp);

	अगर (ctx->dh.g) अणु
		dma_मुक्त_coherent(dev, sz, ctx->dh.g, ctx->dh.dma_g);
		ctx->dh.g = शून्य;
	पूर्ण

	अगर (ctx->dh.xa_p) अणु
		memzero_explicit(ctx->dh.xa_p, sz);
		dma_मुक्त_coherent(dev, sz << 1, ctx->dh.xa_p,
				  ctx->dh.dma_xa_p);
		ctx->dh.xa_p = शून्य;
	पूर्ण

	hpre_ctx_clear(ctx, is_clear_all);
पूर्ण

अटल पूर्णांक hpre_dh_set_secret(काष्ठा crypto_kpp *tfm, स्थिर व्योम *buf,
			      अचिन्हित पूर्णांक len)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);
	काष्ठा dh params;
	पूर्णांक ret;

	अगर (crypto_dh_decode_key(buf, len, &params) < 0)
		वापस -EINVAL;

	/* Free old secret अगर any */
	hpre_dh_clear_ctx(ctx, false);

	ret = hpre_dh_set_params(ctx, &params);
	अगर (ret < 0)
		जाओ err_clear_ctx;

	स_नकल(ctx->dh.xa_p + (ctx->key_sz - params.key_size), params.key,
	       params.key_size);

	वापस 0;

err_clear_ctx:
	hpre_dh_clear_ctx(ctx, false);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक hpre_dh_max_size(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);

	वापस ctx->key_sz;
पूर्ण

अटल पूर्णांक hpre_dh_init_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);

	वापस hpre_ctx_init(ctx, HPRE_V2_ALG_TYPE);
पूर्ण

अटल व्योम hpre_dh_निकास_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);

	hpre_dh_clear_ctx(ctx, true);
पूर्ण

अटल व्योम hpre_rsa_drop_leading_zeros(स्थिर अक्षर **ptr, माप_प्रकार *len)
अणु
	जबतक (!**ptr && *len) अणु
		(*ptr)++;
		(*len)--;
	पूर्ण
पूर्ण

अटल bool hpre_rsa_key_size_is_support(अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक bits = len << HPRE_BITS_2_BYTES_SHIFT;

#घोषणा _RSA_1024BITS_KEY_WDTH		1024
#घोषणा _RSA_2048BITS_KEY_WDTH		2048
#घोषणा _RSA_3072BITS_KEY_WDTH		3072
#घोषणा _RSA_4096BITS_KEY_WDTH		4096

	चयन (bits) अणु
	हाल _RSA_1024BITS_KEY_WDTH:
	हाल _RSA_2048BITS_KEY_WDTH:
	हाल _RSA_3072BITS_KEY_WDTH:
	हाल _RSA_4096BITS_KEY_WDTH:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक hpre_rsa_enc(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा hpre_ctx *ctx = akcipher_tfm_ctx(tfm);
	व्योम *पंचांगp = akcipher_request_ctx(req);
	काष्ठा hpre_asym_request *hpre_req = PTR_ALIGN(पंचांगp, HPRE_ALIGN_SZ);
	काष्ठा hpre_sqe *msg = &hpre_req->req;
	पूर्णांक ret;

	/* For 512 and 1536 bits key size, use soft tfm instead */
	अगर (ctx->key_sz == HPRE_RSA_512BITS_KSZ ||
	    ctx->key_sz == HPRE_RSA_1536BITS_KSZ) अणु
		akcipher_request_set_tfm(req, ctx->rsa.soft_tfm);
		ret = crypto_akcipher_encrypt(req);
		akcipher_request_set_tfm(req, tfm);
		वापस ret;
	पूर्ण

	अगर (unlikely(!ctx->rsa.pubkey))
		वापस -EINVAL;

	ret = hpre_msg_request_set(ctx, req, true);
	अगर (unlikely(ret))
		वापस ret;

	msg->dw0 |= cpu_to_le32(HPRE_ALG_NC_NCRT);
	msg->key = cpu_to_le64(ctx->rsa.dma_pubkey);

	ret = hpre_hw_data_init(hpre_req, req->src, req->src_len, 1, 0);
	अगर (unlikely(ret))
		जाओ clear_all;

	ret = hpre_hw_data_init(hpre_req, req->dst, req->dst_len, 0, 0);
	अगर (unlikely(ret))
		जाओ clear_all;

	/* success */
	ret = hpre_send(ctx, msg);
	अगर (likely(!ret))
		वापस -EINPROGRESS;

clear_all:
	hpre_rm_req_from_ctx(hpre_req);
	hpre_hw_data_clr_all(ctx, hpre_req, req->dst, req->src);

	वापस ret;
पूर्ण

अटल पूर्णांक hpre_rsa_dec(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा hpre_ctx *ctx = akcipher_tfm_ctx(tfm);
	व्योम *पंचांगp = akcipher_request_ctx(req);
	काष्ठा hpre_asym_request *hpre_req = PTR_ALIGN(पंचांगp, HPRE_ALIGN_SZ);
	काष्ठा hpre_sqe *msg = &hpre_req->req;
	पूर्णांक ret;

	/* For 512 and 1536 bits key size, use soft tfm instead */
	अगर (ctx->key_sz == HPRE_RSA_512BITS_KSZ ||
	    ctx->key_sz == HPRE_RSA_1536BITS_KSZ) अणु
		akcipher_request_set_tfm(req, ctx->rsa.soft_tfm);
		ret = crypto_akcipher_decrypt(req);
		akcipher_request_set_tfm(req, tfm);
		वापस ret;
	पूर्ण

	अगर (unlikely(!ctx->rsa.prikey))
		वापस -EINVAL;

	ret = hpre_msg_request_set(ctx, req, true);
	अगर (unlikely(ret))
		वापस ret;

	अगर (ctx->crt_g2_mode) अणु
		msg->key = cpu_to_le64(ctx->rsa.dma_crt_prikey);
		msg->dw0 = cpu_to_le32(le32_to_cpu(msg->dw0) |
				       HPRE_ALG_NC_CRT);
	पूर्ण अन्यथा अणु
		msg->key = cpu_to_le64(ctx->rsa.dma_prikey);
		msg->dw0 = cpu_to_le32(le32_to_cpu(msg->dw0) |
				       HPRE_ALG_NC_NCRT);
	पूर्ण

	ret = hpre_hw_data_init(hpre_req, req->src, req->src_len, 1, 0);
	अगर (unlikely(ret))
		जाओ clear_all;

	ret = hpre_hw_data_init(hpre_req, req->dst, req->dst_len, 0, 0);
	अगर (unlikely(ret))
		जाओ clear_all;

	/* success */
	ret = hpre_send(ctx, msg);
	अगर (likely(!ret))
		वापस -EINPROGRESS;

clear_all:
	hpre_rm_req_from_ctx(hpre_req);
	hpre_hw_data_clr_all(ctx, hpre_req, req->dst, req->src);

	वापस ret;
पूर्ण

अटल पूर्णांक hpre_rsa_set_n(काष्ठा hpre_ctx *ctx, स्थिर अक्षर *value,
			  माप_प्रकार vlen, bool निजी)
अणु
	स्थिर अक्षर *ptr = value;

	hpre_rsa_drop_leading_zeros(&ptr, &vlen);

	ctx->key_sz = vlen;

	/* अगर invalid key size provided, we use software tfm */
	अगर (!hpre_rsa_key_size_is_support(ctx->key_sz))
		वापस 0;

	ctx->rsa.pubkey = dma_alloc_coherent(HPRE_DEV(ctx), vlen << 1,
					     &ctx->rsa.dma_pubkey,
					     GFP_KERNEL);
	अगर (!ctx->rsa.pubkey)
		वापस -ENOMEM;

	अगर (निजी) अणु
		ctx->rsa.prikey = dma_alloc_coherent(HPRE_DEV(ctx), vlen << 1,
						     &ctx->rsa.dma_prikey,
						     GFP_KERNEL);
		अगर (!ctx->rsa.prikey) अणु
			dma_मुक्त_coherent(HPRE_DEV(ctx), vlen << 1,
					  ctx->rsa.pubkey,
					  ctx->rsa.dma_pubkey);
			ctx->rsa.pubkey = शून्य;
			वापस -ENOMEM;
		पूर्ण
		स_नकल(ctx->rsa.prikey + vlen, ptr, vlen);
	पूर्ण
	स_नकल(ctx->rsa.pubkey + vlen, ptr, vlen);

	/* Using hardware HPRE to करो RSA */
	वापस 1;
पूर्ण

अटल पूर्णांक hpre_rsa_set_e(काष्ठा hpre_ctx *ctx, स्थिर अक्षर *value,
			  माप_प्रकार vlen)
अणु
	स्थिर अक्षर *ptr = value;

	hpre_rsa_drop_leading_zeros(&ptr, &vlen);

	अगर (!ctx->key_sz || !vlen || vlen > ctx->key_sz)
		वापस -EINVAL;

	स_नकल(ctx->rsa.pubkey + ctx->key_sz - vlen, ptr, vlen);

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_rsa_set_d(काष्ठा hpre_ctx *ctx, स्थिर अक्षर *value,
			  माप_प्रकार vlen)
अणु
	स्थिर अक्षर *ptr = value;

	hpre_rsa_drop_leading_zeros(&ptr, &vlen);

	अगर (!ctx->key_sz || !vlen || vlen > ctx->key_sz)
		वापस -EINVAL;

	स_नकल(ctx->rsa.prikey + ctx->key_sz - vlen, ptr, vlen);

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_crt_para_get(अक्षर *para, माप_प्रकार para_sz,
			     स्थिर अक्षर *raw, माप_प्रकार raw_sz)
अणु
	स्थिर अक्षर *ptr = raw;
	माप_प्रकार len = raw_sz;

	hpre_rsa_drop_leading_zeros(&ptr, &len);
	अगर (!len || len > para_sz)
		वापस -EINVAL;

	स_नकल(para + para_sz - len, ptr, len);

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_rsa_setkey_crt(काष्ठा hpre_ctx *ctx, काष्ठा rsa_key *rsa_key)
अणु
	अचिन्हित पूर्णांक hlf_ksz = ctx->key_sz >> 1;
	काष्ठा device *dev = HPRE_DEV(ctx);
	u64 offset;
	पूर्णांक ret;

	ctx->rsa.crt_prikey = dma_alloc_coherent(dev, hlf_ksz * HPRE_CRT_PRMS,
					&ctx->rsa.dma_crt_prikey,
					GFP_KERNEL);
	अगर (!ctx->rsa.crt_prikey)
		वापस -ENOMEM;

	ret = hpre_crt_para_get(ctx->rsa.crt_prikey, hlf_ksz,
				rsa_key->dq, rsa_key->dq_sz);
	अगर (ret)
		जाओ मुक्त_key;

	offset = hlf_ksz;
	ret = hpre_crt_para_get(ctx->rsa.crt_prikey + offset, hlf_ksz,
				rsa_key->dp, rsa_key->dp_sz);
	अगर (ret)
		जाओ मुक्त_key;

	offset = hlf_ksz * HPRE_CRT_Q;
	ret = hpre_crt_para_get(ctx->rsa.crt_prikey + offset, hlf_ksz,
				rsa_key->q, rsa_key->q_sz);
	अगर (ret)
		जाओ मुक्त_key;

	offset = hlf_ksz * HPRE_CRT_P;
	ret = hpre_crt_para_get(ctx->rsa.crt_prikey + offset, hlf_ksz,
				rsa_key->p, rsa_key->p_sz);
	अगर (ret)
		जाओ मुक्त_key;

	offset = hlf_ksz * HPRE_CRT_INV;
	ret = hpre_crt_para_get(ctx->rsa.crt_prikey + offset, hlf_ksz,
				rsa_key->qinv, rsa_key->qinv_sz);
	अगर (ret)
		जाओ मुक्त_key;

	ctx->crt_g2_mode = true;

	वापस 0;

मुक्त_key:
	offset = hlf_ksz * HPRE_CRT_PRMS;
	memzero_explicit(ctx->rsa.crt_prikey, offset);
	dma_मुक्त_coherent(dev, hlf_ksz * HPRE_CRT_PRMS, ctx->rsa.crt_prikey,
			  ctx->rsa.dma_crt_prikey);
	ctx->rsa.crt_prikey = शून्य;
	ctx->crt_g2_mode = false;

	वापस ret;
पूर्ण

/* If it is clear all, all the resources of the QP will be cleaned. */
अटल व्योम hpre_rsa_clear_ctx(काष्ठा hpre_ctx *ctx, bool is_clear_all)
अणु
	अचिन्हित पूर्णांक half_key_sz = ctx->key_sz >> 1;
	काष्ठा device *dev = HPRE_DEV(ctx);

	अगर (is_clear_all)
		hisi_qm_stop_qp(ctx->qp);

	अगर (ctx->rsa.pubkey) अणु
		dma_मुक्त_coherent(dev, ctx->key_sz << 1,
				  ctx->rsa.pubkey, ctx->rsa.dma_pubkey);
		ctx->rsa.pubkey = शून्य;
	पूर्ण

	अगर (ctx->rsa.crt_prikey) अणु
		memzero_explicit(ctx->rsa.crt_prikey,
				 half_key_sz * HPRE_CRT_PRMS);
		dma_मुक्त_coherent(dev, half_key_sz * HPRE_CRT_PRMS,
				  ctx->rsa.crt_prikey, ctx->rsa.dma_crt_prikey);
		ctx->rsa.crt_prikey = शून्य;
	पूर्ण

	अगर (ctx->rsa.prikey) अणु
		memzero_explicit(ctx->rsa.prikey, ctx->key_sz);
		dma_मुक्त_coherent(dev, ctx->key_sz << 1, ctx->rsa.prikey,
				  ctx->rsa.dma_prikey);
		ctx->rsa.prikey = शून्य;
	पूर्ण

	hpre_ctx_clear(ctx, is_clear_all);
पूर्ण

/*
 * we should judge अगर it is CRT or not,
 * CRT: वापस true,  N-CRT: वापस false .
 */
अटल bool hpre_is_crt_key(काष्ठा rsa_key *key)
अणु
	u16 len = key->p_sz + key->q_sz + key->dp_sz + key->dq_sz +
		  key->qinv_sz;

#घोषणा LEN_OF_NCRT_PARA	5

	/* N-CRT less than 5 parameters */
	वापस len > LEN_OF_NCRT_PARA;
पूर्ण

अटल पूर्णांक hpre_rsa_setkey(काष्ठा hpre_ctx *ctx, स्थिर व्योम *key,
			   अचिन्हित पूर्णांक keylen, bool निजी)
अणु
	काष्ठा rsa_key rsa_key;
	पूर्णांक ret;

	hpre_rsa_clear_ctx(ctx, false);

	अगर (निजी)
		ret = rsa_parse_priv_key(&rsa_key, key, keylen);
	अन्यथा
		ret = rsa_parse_pub_key(&rsa_key, key, keylen);
	अगर (ret < 0)
		वापस ret;

	ret = hpre_rsa_set_n(ctx, rsa_key.n, rsa_key.n_sz, निजी);
	अगर (ret <= 0)
		वापस ret;

	अगर (निजी) अणु
		ret = hpre_rsa_set_d(ctx, rsa_key.d, rsa_key.d_sz);
		अगर (ret < 0)
			जाओ मुक्त;

		अगर (hpre_is_crt_key(&rsa_key)) अणु
			ret = hpre_rsa_setkey_crt(ctx, &rsa_key);
			अगर (ret < 0)
				जाओ मुक्त;
		पूर्ण
	पूर्ण

	ret = hpre_rsa_set_e(ctx, rsa_key.e, rsa_key.e_sz);
	अगर (ret < 0)
		जाओ मुक्त;

	अगर ((निजी && !ctx->rsa.prikey) || !ctx->rsa.pubkey) अणु
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	वापस 0;

मुक्त:
	hpre_rsa_clear_ctx(ctx, false);
	वापस ret;
पूर्ण

अटल पूर्णांक hpre_rsa_setpubkey(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा hpre_ctx *ctx = akcipher_tfm_ctx(tfm);
	पूर्णांक ret;

	ret = crypto_akcipher_set_pub_key(ctx->rsa.soft_tfm, key, keylen);
	अगर (ret)
		वापस ret;

	वापस hpre_rsa_setkey(ctx, key, keylen, false);
पूर्ण

अटल पूर्णांक hpre_rsa_setprivkey(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			       अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा hpre_ctx *ctx = akcipher_tfm_ctx(tfm);
	पूर्णांक ret;

	ret = crypto_akcipher_set_priv_key(ctx->rsa.soft_tfm, key, keylen);
	अगर (ret)
		वापस ret;

	वापस hpre_rsa_setkey(ctx, key, keylen, true);
पूर्ण

अटल अचिन्हित पूर्णांक hpre_rsa_max_size(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा hpre_ctx *ctx = akcipher_tfm_ctx(tfm);

	/* For 512 and 1536 bits key size, use soft tfm instead */
	अगर (ctx->key_sz == HPRE_RSA_512BITS_KSZ ||
	    ctx->key_sz == HPRE_RSA_1536BITS_KSZ)
		वापस crypto_akcipher_maxsize(ctx->rsa.soft_tfm);

	वापस ctx->key_sz;
पूर्ण

अटल पूर्णांक hpre_rsa_init_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा hpre_ctx *ctx = akcipher_tfm_ctx(tfm);
	पूर्णांक ret;

	ctx->rsa.soft_tfm = crypto_alloc_akcipher("rsa-generic", 0, 0);
	अगर (IS_ERR(ctx->rsa.soft_tfm)) अणु
		pr_err("Can not alloc_akcipher!\n");
		वापस PTR_ERR(ctx->rsa.soft_tfm);
	पूर्ण

	ret = hpre_ctx_init(ctx, HPRE_V2_ALG_TYPE);
	अगर (ret)
		crypto_मुक्त_akcipher(ctx->rsa.soft_tfm);

	वापस ret;
पूर्ण

अटल व्योम hpre_rsa_निकास_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा hpre_ctx *ctx = akcipher_tfm_ctx(tfm);

	hpre_rsa_clear_ctx(ctx, true);
	crypto_मुक्त_akcipher(ctx->rsa.soft_tfm);
पूर्ण

अटल व्योम hpre_key_to_big_end(u8 *data, पूर्णांक len)
अणु
	पूर्णांक i, j;
	u8 पंचांगp;

	क्रम (i = 0; i < len / 2; i++) अणु
		j = len - i - 1;
		पंचांगp = data[j];
		data[j] = data[i];
		data[i] = पंचांगp;
	पूर्ण
पूर्ण

अटल व्योम hpre_ecc_clear_ctx(काष्ठा hpre_ctx *ctx, bool is_clear_all,
			       bool is_ecdh)
अणु
	काष्ठा device *dev = HPRE_DEV(ctx);
	अचिन्हित पूर्णांक sz = ctx->key_sz;
	अचिन्हित पूर्णांक shअगरt = sz << 1;

	अगर (is_clear_all)
		hisi_qm_stop_qp(ctx->qp);

	अगर (is_ecdh && ctx->ecdh.p) अणु
		/* ecdh: p->a->k->b */
		memzero_explicit(ctx->ecdh.p + shअगरt, sz);
		dma_मुक्त_coherent(dev, sz << 3, ctx->ecdh.p, ctx->ecdh.dma_p);
		ctx->ecdh.p = शून्य;
	पूर्ण अन्यथा अगर (!is_ecdh && ctx->curve25519.p) अणु
		/* curve25519: p->a->k */
		memzero_explicit(ctx->curve25519.p + shअगरt, sz);
		dma_मुक्त_coherent(dev, sz << 2, ctx->curve25519.p,
				  ctx->curve25519.dma_p);
		ctx->curve25519.p = शून्य;
	पूर्ण

	hpre_ctx_clear(ctx, is_clear_all);
पूर्ण

अटल अचिन्हित पूर्णांक hpre_ecdh_supported_curve(अचिन्हित लघु id)
अणु
	चयन (id) अणु
	हाल ECC_CURVE_NIST_P192:
	हाल ECC_CURVE_NIST_P256:
		वापस HPRE_ECC_HW256_KSZ_B;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fill_curve_param(व्योम *addr, u64 *param, अचिन्हित पूर्णांक cur_sz, u8 ndigits)
अणु
	अचिन्हित पूर्णांक sz = cur_sz - (ndigits - 1) * माप(u64);
	u8 i = 0;

	जबतक (i < ndigits - 1) अणु
		स_नकल(addr + माप(u64) * i, &param[i], माप(u64));
		i++;
	पूर्ण

	स_नकल(addr + माप(u64) * i, &param[ndigits - 1], sz);
	hpre_key_to_big_end((u8 *)addr, cur_sz);
पूर्ण

अटल पूर्णांक hpre_ecdh_fill_curve(काष्ठा hpre_ctx *ctx, काष्ठा ecdh *params,
				अचिन्हित पूर्णांक cur_sz)
अणु
	अचिन्हित पूर्णांक shअगरta = ctx->key_sz << 1;
	अचिन्हित पूर्णांक shअगरtb = ctx->key_sz << 2;
	व्योम *p = ctx->ecdh.p + ctx->key_sz - cur_sz;
	व्योम *a = ctx->ecdh.p + shअगरta - cur_sz;
	व्योम *b = ctx->ecdh.p + shअगरtb - cur_sz;
	व्योम *x = ctx->ecdh.g + ctx->key_sz - cur_sz;
	व्योम *y = ctx->ecdh.g + shअगरta - cur_sz;
	स्थिर काष्ठा ecc_curve *curve = ecc_get_curve(ctx->curve_id);
	अक्षर *n;

	अगर (unlikely(!curve))
		वापस -EINVAL;

	n = kzalloc(ctx->key_sz, GFP_KERNEL);
	अगर (!n)
		वापस -ENOMEM;

	fill_curve_param(p, curve->p, cur_sz, curve->g.ndigits);
	fill_curve_param(a, curve->a, cur_sz, curve->g.ndigits);
	fill_curve_param(b, curve->b, cur_sz, curve->g.ndigits);
	fill_curve_param(x, curve->g.x, cur_sz, curve->g.ndigits);
	fill_curve_param(y, curve->g.y, cur_sz, curve->g.ndigits);
	fill_curve_param(n, curve->n, cur_sz, curve->g.ndigits);

	अगर (params->key_size == cur_sz && स_भेद(params->key, n, cur_sz) >= 0) अणु
		kमुक्त(n);
		वापस -EINVAL;
	पूर्ण

	kमुक्त(n);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक hpre_ecdh_get_curvesz(अचिन्हित लघु id)
अणु
	चयन (id) अणु
	हाल ECC_CURVE_NIST_P192:
		वापस HPRE_ECC_NIST_P192_N_SIZE;
	हाल ECC_CURVE_NIST_P256:
		वापस HPRE_ECC_NIST_P256_N_SIZE;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_ecdh_set_param(काष्ठा hpre_ctx *ctx, काष्ठा ecdh *params)
अणु
	काष्ठा device *dev = HPRE_DEV(ctx);
	अचिन्हित पूर्णांक sz, shअगरt, curve_sz;
	पूर्णांक ret;

	ctx->key_sz = hpre_ecdh_supported_curve(ctx->curve_id);
	अगर (!ctx->key_sz)
		वापस -EINVAL;

	curve_sz = hpre_ecdh_get_curvesz(ctx->curve_id);
	अगर (!curve_sz || params->key_size > curve_sz)
		वापस -EINVAL;

	sz = ctx->key_sz;

	अगर (!ctx->ecdh.p) अणु
		ctx->ecdh.p = dma_alloc_coherent(dev, sz << 3, &ctx->ecdh.dma_p,
						 GFP_KERNEL);
		अगर (!ctx->ecdh.p)
			वापस -ENOMEM;
	पूर्ण

	shअगरt = sz << 2;
	ctx->ecdh.g = ctx->ecdh.p + shअगरt;
	ctx->ecdh.dma_g = ctx->ecdh.dma_p + shअगरt;

	ret = hpre_ecdh_fill_curve(ctx, params, curve_sz);
	अगर (ret) अणु
		dev_err(dev, "failed to fill curve_param, ret = %d!\n", ret);
		dma_मुक्त_coherent(dev, sz << 3, ctx->ecdh.p, ctx->ecdh.dma_p);
		ctx->ecdh.p = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool hpre_key_is_zero(अक्षर *key, अचिन्हित लघु key_sz)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < key_sz; i++)
		अगर (key[i])
			वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक hpre_ecdh_set_secret(काष्ठा crypto_kpp *tfm, स्थिर व्योम *buf,
				अचिन्हित पूर्णांक len)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);
	काष्ठा device *dev = HPRE_DEV(ctx);
	अचिन्हित पूर्णांक sz, sz_shअगरt;
	काष्ठा ecdh params;
	पूर्णांक ret;

	अगर (crypto_ecdh_decode_key(buf, len, &params) < 0) अणु
		dev_err(dev, "failed to decode ecdh key!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (hpre_key_is_zero(params.key, params.key_size)) अणु
		dev_err(dev, "Invalid hpre key!\n");
		वापस -EINVAL;
	पूर्ण

	hpre_ecc_clear_ctx(ctx, false, true);

	ret = hpre_ecdh_set_param(ctx, &params);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to set hpre param, ret = %d!\n", ret);
		वापस ret;
	पूर्ण

	sz = ctx->key_sz;
	sz_shअगरt = (sz << 1) + sz - params.key_size;
	स_नकल(ctx->ecdh.p + sz_shअगरt, params.key, params.key_size);

	वापस 0;
पूर्ण

अटल व्योम hpre_ecdh_hw_data_clr_all(काष्ठा hpre_ctx *ctx,
				      काष्ठा hpre_asym_request *req,
				      काष्ठा scatterlist *dst,
				      काष्ठा scatterlist *src)
अणु
	काष्ठा device *dev = HPRE_DEV(ctx);
	काष्ठा hpre_sqe *sqe = &req->req;
	dma_addr_t dma;

	dma = le64_to_cpu(sqe->in);

	अगर (src && req->src)
		dma_मुक्त_coherent(dev, ctx->key_sz << 2, req->src, dma);

	dma = le64_to_cpu(sqe->out);

	अगर (req->dst)
		dma_मुक्त_coherent(dev, ctx->key_sz << 1, req->dst, dma);
	अगर (dst)
		dma_unmap_single(dev, dma, ctx->key_sz << 1, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम hpre_ecdh_cb(काष्ठा hpre_ctx *ctx, व्योम *resp)
अणु
	अचिन्हित पूर्णांक curve_sz = hpre_ecdh_get_curvesz(ctx->curve_id);
	काष्ठा hpre_dfx *dfx = ctx->hpre->debug.dfx;
	काष्ठा hpre_asym_request *req = शून्य;
	काष्ठा kpp_request *areq;
	u64 overसमय_प्रकारhrhld;
	अक्षर *p;
	पूर्णांक ret;

	ret = hpre_alg_res_post_hf(ctx, resp, (व्योम **)&req);
	areq = req->areq.ecdh;
	areq->dst_len = ctx->key_sz << 1;

	overसमय_प्रकारhrhld = atomic64_पढ़ो(&dfx[HPRE_OVERTIME_THRHLD].value);
	अगर (overसमय_प्रकारhrhld && hpre_is_bd_समयout(req, overसमय_प्रकारhrhld))
		atomic64_inc(&dfx[HPRE_OVER_THRHLD_CNT].value);

	p = sg_virt(areq->dst);
	स_हटाओ(p, p + ctx->key_sz - curve_sz, curve_sz);
	स_हटाओ(p + curve_sz, p + areq->dst_len - curve_sz, curve_sz);

	hpre_ecdh_hw_data_clr_all(ctx, req, areq->dst, areq->src);
	kpp_request_complete(areq, ret);

	atomic64_inc(&dfx[HPRE_RECV_CNT].value);
पूर्ण

अटल पूर्णांक hpre_ecdh_msg_request_set(काष्ठा hpre_ctx *ctx,
				     काष्ठा kpp_request *req)
अणु
	काष्ठा hpre_asym_request *h_req;
	काष्ठा hpre_sqe *msg;
	पूर्णांक req_id;
	व्योम *पंचांगp;

	अगर (req->dst_len < ctx->key_sz << 1) अणु
		req->dst_len = ctx->key_sz << 1;
		वापस -EINVAL;
	पूर्ण

	पंचांगp = kpp_request_ctx(req);
	h_req = PTR_ALIGN(पंचांगp, HPRE_ALIGN_SZ);
	h_req->cb = hpre_ecdh_cb;
	h_req->areq.ecdh = req;
	msg = &h_req->req;
	स_रखो(msg, 0, माप(*msg));
	msg->key = cpu_to_le64(ctx->ecdh.dma_p);

	msg->dw0 |= cpu_to_le32(0x1U << HPRE_SQE_DONE_SHIFT);
	msg->task_len1 = (ctx->key_sz >> HPRE_BITS_2_BYTES_SHIFT) - 1;
	h_req->ctx = ctx;

	req_id = hpre_add_req_to_ctx(h_req);
	अगर (req_id < 0)
		वापस -EBUSY;

	msg->tag = cpu_to_le16((u16)req_id);
	वापस 0;
पूर्ण

अटल पूर्णांक hpre_ecdh_src_data_init(काष्ठा hpre_asym_request *hpre_req,
				   काष्ठा scatterlist *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा hpre_sqe *msg = &hpre_req->req;
	काष्ठा hpre_ctx *ctx = hpre_req->ctx;
	काष्ठा device *dev = HPRE_DEV(ctx);
	अचिन्हित पूर्णांक पंचांगpshअगरt;
	dma_addr_t dma = 0;
	व्योम *ptr;
	पूर्णांक shअगरt;

	/* Src_data include gx and gy. */
	shअगरt = ctx->key_sz - (len >> 1);
	अगर (unlikely(shअगरt < 0))
		वापस -EINVAL;

	ptr = dma_alloc_coherent(dev, ctx->key_sz << 2, &dma, GFP_KERNEL);
	अगर (unlikely(!ptr))
		वापस -ENOMEM;

	पंचांगpshअगरt = ctx->key_sz << 1;
	scatterwalk_map_and_copy(ptr + पंचांगpshअगरt, data, 0, len, 0);
	स_नकल(ptr + shअगरt, ptr + पंचांगpshअगरt, len >> 1);
	स_नकल(ptr + ctx->key_sz + shअगरt, ptr + पंचांगpshअगरt + (len >> 1), len >> 1);

	hpre_req->src = ptr;
	msg->in = cpu_to_le64(dma);
	वापस 0;
पूर्ण

अटल पूर्णांक hpre_ecdh_dst_data_init(काष्ठा hpre_asym_request *hpre_req,
				   काष्ठा scatterlist *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा hpre_sqe *msg = &hpre_req->req;
	काष्ठा hpre_ctx *ctx = hpre_req->ctx;
	काष्ठा device *dev = HPRE_DEV(ctx);
	dma_addr_t dma = 0;

	अगर (unlikely(!data || !sg_is_last(data) || len != ctx->key_sz << 1)) अणु
		dev_err(dev, "data or data length is illegal!\n");
		वापस -EINVAL;
	पूर्ण

	hpre_req->dst = शून्य;
	dma = dma_map_single(dev, sg_virt(data), len, DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, dma))) अणु
		dev_err(dev, "dma map data err!\n");
		वापस -ENOMEM;
	पूर्ण

	msg->out = cpu_to_le64(dma);
	वापस 0;
पूर्ण

अटल पूर्णांक hpre_ecdh_compute_value(काष्ठा kpp_request *req)
अणु
	काष्ठा crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);
	काष्ठा device *dev = HPRE_DEV(ctx);
	व्योम *पंचांगp = kpp_request_ctx(req);
	काष्ठा hpre_asym_request *hpre_req = PTR_ALIGN(पंचांगp, HPRE_ALIGN_SZ);
	काष्ठा hpre_sqe *msg = &hpre_req->req;
	पूर्णांक ret;

	ret = hpre_ecdh_msg_request_set(ctx, req);
	अगर (unlikely(ret)) अणु
		dev_err(dev, "failed to set ecdh request, ret = %d!\n", ret);
		वापस ret;
	पूर्ण

	अगर (req->src) अणु
		ret = hpre_ecdh_src_data_init(hpre_req, req->src, req->src_len);
		अगर (unlikely(ret)) अणु
			dev_err(dev, "failed to init src data, ret = %d!\n", ret);
			जाओ clear_all;
		पूर्ण
	पूर्ण अन्यथा अणु
		msg->in = cpu_to_le64(ctx->ecdh.dma_g);
	पूर्ण

	ret = hpre_ecdh_dst_data_init(hpre_req, req->dst, req->dst_len);
	अगर (unlikely(ret)) अणु
		dev_err(dev, "failed to init dst data, ret = %d!\n", ret);
		जाओ clear_all;
	पूर्ण

	msg->dw0 = cpu_to_le32(le32_to_cpu(msg->dw0) | HPRE_ALG_ECC_MUL);
	ret = hpre_send(ctx, msg);
	अगर (likely(!ret))
		वापस -EINPROGRESS;

clear_all:
	hpre_rm_req_from_ctx(hpre_req);
	hpre_ecdh_hw_data_clr_all(ctx, hpre_req, req->dst, req->src);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक hpre_ecdh_max_size(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);

	/* max size is the pub_key_size, include x and y */
	वापस ctx->key_sz << 1;
पूर्ण

अटल पूर्णांक hpre_ecdh_nist_p192_init_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);

	ctx->curve_id = ECC_CURVE_NIST_P192;

	वापस hpre_ctx_init(ctx, HPRE_V3_ECC_ALG_TYPE);
पूर्ण

अटल पूर्णांक hpre_ecdh_nist_p256_init_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);

	ctx->curve_id = ECC_CURVE_NIST_P256;

	वापस hpre_ctx_init(ctx, HPRE_V3_ECC_ALG_TYPE);
पूर्ण

अटल व्योम hpre_ecdh_निकास_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);

	hpre_ecc_clear_ctx(ctx, true, true);
पूर्ण

अटल व्योम hpre_curve25519_fill_curve(काष्ठा hpre_ctx *ctx, स्थिर व्योम *buf,
				       अचिन्हित पूर्णांक len)
अणु
	u8 secret[CURVE25519_KEY_SIZE] = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक sz = ctx->key_sz;
	स्थिर काष्ठा ecc_curve *curve;
	अचिन्हित पूर्णांक shअगरt = sz << 1;
	व्योम *p;

	/*
	 * The key from 'buf' is in little-endian, we should preprocess it as
	 * the description in rfc7748: "k[0] &= 248, k[31] &= 127, k[31] |= 64",
	 * then convert it to big endian. Only in this way, the result can be
	 * the same as the software curve-25519 that exists in crypto.
	 */
	स_नकल(secret, buf, len);
	curve25519_clamp_secret(secret);
	hpre_key_to_big_end(secret, CURVE25519_KEY_SIZE);

	p = ctx->curve25519.p + sz - len;

	curve = ecc_get_curve25519();

	/* fill curve parameters */
	fill_curve_param(p, curve->p, len, curve->g.ndigits);
	fill_curve_param(p + sz, curve->a, len, curve->g.ndigits);
	स_नकल(p + shअगरt, secret, len);
	fill_curve_param(p + shअगरt + sz, curve->g.x, len, curve->g.ndigits);
	memzero_explicit(secret, CURVE25519_KEY_SIZE);
पूर्ण

अटल पूर्णांक hpre_curve25519_set_param(काष्ठा hpre_ctx *ctx, स्थिर व्योम *buf,
				     अचिन्हित पूर्णांक len)
अणु
	काष्ठा device *dev = HPRE_DEV(ctx);
	अचिन्हित पूर्णांक sz = ctx->key_sz;
	अचिन्हित पूर्णांक shअगरt = sz << 1;

	/* p->a->k->gx */
	अगर (!ctx->curve25519.p) अणु
		ctx->curve25519.p = dma_alloc_coherent(dev, sz << 2,
						       &ctx->curve25519.dma_p,
						       GFP_KERNEL);
		अगर (!ctx->curve25519.p)
			वापस -ENOMEM;
	पूर्ण

	ctx->curve25519.g = ctx->curve25519.p + shअगरt + sz;
	ctx->curve25519.dma_g = ctx->curve25519.dma_p + shअगरt + sz;

	hpre_curve25519_fill_curve(ctx, buf, len);

	वापस 0;
पूर्ण

अटल पूर्णांक hpre_curve25519_set_secret(काष्ठा crypto_kpp *tfm, स्थिर व्योम *buf,
				      अचिन्हित पूर्णांक len)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);
	काष्ठा device *dev = HPRE_DEV(ctx);
	पूर्णांक ret = -EINVAL;

	अगर (len != CURVE25519_KEY_SIZE ||
	    !crypto_memneq(buf, curve25519_null_poपूर्णांक, CURVE25519_KEY_SIZE)) अणु
		dev_err(dev, "key is null or key len is not 32bytes!\n");
		वापस ret;
	पूर्ण

	/* Free old secret अगर any */
	hpre_ecc_clear_ctx(ctx, false, false);

	ctx->key_sz = CURVE25519_KEY_SIZE;
	ret = hpre_curve25519_set_param(ctx, buf, CURVE25519_KEY_SIZE);
	अगर (ret) अणु
		dev_err(dev, "failed to set curve25519 param, ret = %d!\n", ret);
		hpre_ecc_clear_ctx(ctx, false, false);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hpre_curve25519_hw_data_clr_all(काष्ठा hpre_ctx *ctx,
					    काष्ठा hpre_asym_request *req,
					    काष्ठा scatterlist *dst,
					    काष्ठा scatterlist *src)
अणु
	काष्ठा device *dev = HPRE_DEV(ctx);
	काष्ठा hpre_sqe *sqe = &req->req;
	dma_addr_t dma;

	dma = le64_to_cpu(sqe->in);

	अगर (src && req->src)
		dma_मुक्त_coherent(dev, ctx->key_sz, req->src, dma);

	dma = le64_to_cpu(sqe->out);

	अगर (req->dst)
		dma_मुक्त_coherent(dev, ctx->key_sz, req->dst, dma);
	अगर (dst)
		dma_unmap_single(dev, dma, ctx->key_sz, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम hpre_curve25519_cb(काष्ठा hpre_ctx *ctx, व्योम *resp)
अणु
	काष्ठा hpre_dfx *dfx = ctx->hpre->debug.dfx;
	काष्ठा hpre_asym_request *req = शून्य;
	काष्ठा kpp_request *areq;
	u64 overसमय_प्रकारhrhld;
	पूर्णांक ret;

	ret = hpre_alg_res_post_hf(ctx, resp, (व्योम **)&req);
	areq = req->areq.curve25519;
	areq->dst_len = ctx->key_sz;

	overसमय_प्रकारhrhld = atomic64_पढ़ो(&dfx[HPRE_OVERTIME_THRHLD].value);
	अगर (overसमय_प्रकारhrhld && hpre_is_bd_समयout(req, overसमय_प्रकारhrhld))
		atomic64_inc(&dfx[HPRE_OVER_THRHLD_CNT].value);

	hpre_key_to_big_end(sg_virt(areq->dst), CURVE25519_KEY_SIZE);

	hpre_curve25519_hw_data_clr_all(ctx, req, areq->dst, areq->src);
	kpp_request_complete(areq, ret);

	atomic64_inc(&dfx[HPRE_RECV_CNT].value);
पूर्ण

अटल पूर्णांक hpre_curve25519_msg_request_set(काष्ठा hpre_ctx *ctx,
					   काष्ठा kpp_request *req)
अणु
	काष्ठा hpre_asym_request *h_req;
	काष्ठा hpre_sqe *msg;
	पूर्णांक req_id;
	व्योम *पंचांगp;

	अगर (unlikely(req->dst_len < ctx->key_sz)) अणु
		req->dst_len = ctx->key_sz;
		वापस -EINVAL;
	पूर्ण

	पंचांगp = kpp_request_ctx(req);
	h_req = PTR_ALIGN(पंचांगp, HPRE_ALIGN_SZ);
	h_req->cb = hpre_curve25519_cb;
	h_req->areq.curve25519 = req;
	msg = &h_req->req;
	स_रखो(msg, 0, माप(*msg));
	msg->key = cpu_to_le64(ctx->curve25519.dma_p);

	msg->dw0 |= cpu_to_le32(0x1U << HPRE_SQE_DONE_SHIFT);
	msg->task_len1 = (ctx->key_sz >> HPRE_BITS_2_BYTES_SHIFT) - 1;
	h_req->ctx = ctx;

	req_id = hpre_add_req_to_ctx(h_req);
	अगर (req_id < 0)
		वापस -EBUSY;

	msg->tag = cpu_to_le16((u16)req_id);
	वापस 0;
पूर्ण

अटल व्योम hpre_curve25519_src_modulo_p(u8 *ptr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CURVE25519_KEY_SIZE - 1; i++)
		ptr[i] = 0;

	/* The modulus is ptr's last byte minus '0xed'(last byte of p) */
	ptr[i] -= 0xed;
पूर्ण

अटल पूर्णांक hpre_curve25519_src_init(काष्ठा hpre_asym_request *hpre_req,
				    काष्ठा scatterlist *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा hpre_sqe *msg = &hpre_req->req;
	काष्ठा hpre_ctx *ctx = hpre_req->ctx;
	काष्ठा device *dev = HPRE_DEV(ctx);
	u8 p[CURVE25519_KEY_SIZE] = अणु 0 पूर्ण;
	स्थिर काष्ठा ecc_curve *curve;
	dma_addr_t dma = 0;
	u8 *ptr;

	अगर (len != CURVE25519_KEY_SIZE) अणु
		dev_err(dev, "sourc_data len is not 32bytes, len = %u!\n", len);
		वापस -EINVAL;
	पूर्ण

	ptr = dma_alloc_coherent(dev, ctx->key_sz, &dma, GFP_KERNEL);
	अगर (unlikely(!ptr))
		वापस -ENOMEM;

	scatterwalk_map_and_copy(ptr, data, 0, len, 0);

	अगर (!crypto_memneq(ptr, curve25519_null_poपूर्णांक, CURVE25519_KEY_SIZE)) अणु
		dev_err(dev, "gx is null!\n");
		जाओ err;
	पूर्ण

	/*
	 * Src_data(gx) is in little-endian order, MSB in the final byte should
	 * be masked as described in RFC7748, then transक्रमm it to big-endian
	 * क्रमm, then hisi_hpre can use the data.
	 */
	ptr[31] &= 0x7f;
	hpre_key_to_big_end(ptr, CURVE25519_KEY_SIZE);

	curve = ecc_get_curve25519();

	fill_curve_param(p, curve->p, CURVE25519_KEY_SIZE, curve->g.ndigits);

	/*
	 * When src_data equals (2^255 - 19) ~  (2^255 - 1), it is out of p,
	 * we get its modulus to p, and then use it.
	 */
	अगर (स_भेद(ptr, p, ctx->key_sz) >= 0)
		hpre_curve25519_src_modulo_p(ptr);

	hpre_req->src = ptr;
	msg->in = cpu_to_le64(dma);
	वापस 0;

err:
	dma_मुक्त_coherent(dev, ctx->key_sz, ptr, dma);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hpre_curve25519_dst_init(काष्ठा hpre_asym_request *hpre_req,
				    काष्ठा scatterlist *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा hpre_sqe *msg = &hpre_req->req;
	काष्ठा hpre_ctx *ctx = hpre_req->ctx;
	काष्ठा device *dev = HPRE_DEV(ctx);
	dma_addr_t dma = 0;

	अगर (!data || !sg_is_last(data) || len != ctx->key_sz) अणु
		dev_err(dev, "data or data length is illegal!\n");
		वापस -EINVAL;
	पूर्ण

	hpre_req->dst = शून्य;
	dma = dma_map_single(dev, sg_virt(data), len, DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, dma))) अणु
		dev_err(dev, "dma map data err!\n");
		वापस -ENOMEM;
	पूर्ण

	msg->out = cpu_to_le64(dma);
	वापस 0;
पूर्ण

अटल पूर्णांक hpre_curve25519_compute_value(काष्ठा kpp_request *req)
अणु
	काष्ठा crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);
	काष्ठा device *dev = HPRE_DEV(ctx);
	व्योम *पंचांगp = kpp_request_ctx(req);
	काष्ठा hpre_asym_request *hpre_req = PTR_ALIGN(पंचांगp, HPRE_ALIGN_SZ);
	काष्ठा hpre_sqe *msg = &hpre_req->req;
	पूर्णांक ret;

	ret = hpre_curve25519_msg_request_set(ctx, req);
	अगर (unlikely(ret)) अणु
		dev_err(dev, "failed to set curve25519 request, ret = %d!\n", ret);
		वापस ret;
	पूर्ण

	अगर (req->src) अणु
		ret = hpre_curve25519_src_init(hpre_req, req->src, req->src_len);
		अगर (unlikely(ret)) अणु
			dev_err(dev, "failed to init src data, ret = %d!\n",
				ret);
			जाओ clear_all;
		पूर्ण
	पूर्ण अन्यथा अणु
		msg->in = cpu_to_le64(ctx->curve25519.dma_g);
	पूर्ण

	ret = hpre_curve25519_dst_init(hpre_req, req->dst, req->dst_len);
	अगर (unlikely(ret)) अणु
		dev_err(dev, "failed to init dst data, ret = %d!\n", ret);
		जाओ clear_all;
	पूर्ण

	msg->dw0 = cpu_to_le32(le32_to_cpu(msg->dw0) | HPRE_ALG_CURVE25519_MUL);
	ret = hpre_send(ctx, msg);
	अगर (likely(!ret))
		वापस -EINPROGRESS;

clear_all:
	hpre_rm_req_from_ctx(hpre_req);
	hpre_curve25519_hw_data_clr_all(ctx, hpre_req, req->dst, req->src);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक hpre_curve25519_max_size(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);

	वापस ctx->key_sz;
पूर्ण

अटल पूर्णांक hpre_curve25519_init_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);

	वापस hpre_ctx_init(ctx, HPRE_V3_ECC_ALG_TYPE);
पूर्ण

अटल व्योम hpre_curve25519_निकास_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा hpre_ctx *ctx = kpp_tfm_ctx(tfm);

	hpre_ecc_clear_ctx(ctx, true, false);
पूर्ण

अटल काष्ठा akcipher_alg rsa = अणु
	.sign = hpre_rsa_dec,
	.verअगरy = hpre_rsa_enc,
	.encrypt = hpre_rsa_enc,
	.decrypt = hpre_rsa_dec,
	.set_pub_key = hpre_rsa_setpubkey,
	.set_priv_key = hpre_rsa_setprivkey,
	.max_size = hpre_rsa_max_size,
	.init = hpre_rsa_init_tfm,
	.निकास = hpre_rsa_निकास_tfm,
	.reqsize = माप(काष्ठा hpre_asym_request) + HPRE_ALIGN_SZ,
	.base = अणु
		.cra_ctxsize = माप(काष्ठा hpre_ctx),
		.cra_priority = HPRE_CRYPTO_ALG_PRI,
		.cra_name = "rsa",
		.cra_driver_name = "hpre-rsa",
		.cra_module = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल काष्ठा kpp_alg dh = अणु
	.set_secret = hpre_dh_set_secret,
	.generate_खुला_key = hpre_dh_compute_value,
	.compute_shared_secret = hpre_dh_compute_value,
	.max_size = hpre_dh_max_size,
	.init = hpre_dh_init_tfm,
	.निकास = hpre_dh_निकास_tfm,
	.reqsize = माप(काष्ठा hpre_asym_request) + HPRE_ALIGN_SZ,
	.base = अणु
		.cra_ctxsize = माप(काष्ठा hpre_ctx),
		.cra_priority = HPRE_CRYPTO_ALG_PRI,
		.cra_name = "dh",
		.cra_driver_name = "hpre-dh",
		.cra_module = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल काष्ठा kpp_alg ecdh_nist_p192 = अणु
	.set_secret = hpre_ecdh_set_secret,
	.generate_खुला_key = hpre_ecdh_compute_value,
	.compute_shared_secret = hpre_ecdh_compute_value,
	.max_size = hpre_ecdh_max_size,
	.init = hpre_ecdh_nist_p192_init_tfm,
	.निकास = hpre_ecdh_निकास_tfm,
	.reqsize = माप(काष्ठा hpre_asym_request) + HPRE_ALIGN_SZ,
	.base = अणु
		.cra_ctxsize = माप(काष्ठा hpre_ctx),
		.cra_priority = HPRE_CRYPTO_ALG_PRI,
		.cra_name = "ecdh-nist-p192",
		.cra_driver_name = "hpre-ecdh",
		.cra_module = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल काष्ठा kpp_alg ecdh_nist_p256 = अणु
	.set_secret = hpre_ecdh_set_secret,
	.generate_खुला_key = hpre_ecdh_compute_value,
	.compute_shared_secret = hpre_ecdh_compute_value,
	.max_size = hpre_ecdh_max_size,
	.init = hpre_ecdh_nist_p256_init_tfm,
	.निकास = hpre_ecdh_निकास_tfm,
	.reqsize = माप(काष्ठा hpre_asym_request) + HPRE_ALIGN_SZ,
	.base = अणु
		.cra_ctxsize = माप(काष्ठा hpre_ctx),
		.cra_priority = HPRE_CRYPTO_ALG_PRI,
		.cra_name = "ecdh-nist-p256",
		.cra_driver_name = "hpre-ecdh",
		.cra_module = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल काष्ठा kpp_alg curve25519_alg = अणु
	.set_secret = hpre_curve25519_set_secret,
	.generate_खुला_key = hpre_curve25519_compute_value,
	.compute_shared_secret = hpre_curve25519_compute_value,
	.max_size = hpre_curve25519_max_size,
	.init = hpre_curve25519_init_tfm,
	.निकास = hpre_curve25519_निकास_tfm,
	.reqsize = माप(काष्ठा hpre_asym_request) + HPRE_ALIGN_SZ,
	.base = अणु
		.cra_ctxsize = माप(काष्ठा hpre_ctx),
		.cra_priority = HPRE_CRYPTO_ALG_PRI,
		.cra_name = "curve25519",
		.cra_driver_name = "hpre-curve25519",
		.cra_module = THIS_MODULE,
	पूर्ण,
पूर्ण;


अटल पूर्णांक hpre_रेजिस्टर_ecdh(व्योम)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_kpp(&ecdh_nist_p192);
	अगर (ret)
		वापस ret;

	ret = crypto_रेजिस्टर_kpp(&ecdh_nist_p256);
	अगर (ret) अणु
		crypto_unरेजिस्टर_kpp(&ecdh_nist_p192);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hpre_unरेजिस्टर_ecdh(व्योम)
अणु
	crypto_unरेजिस्टर_kpp(&ecdh_nist_p256);
	crypto_unरेजिस्टर_kpp(&ecdh_nist_p192);
पूर्ण

पूर्णांक hpre_algs_रेजिस्टर(काष्ठा hisi_qm *qm)
अणु
	पूर्णांक ret;

	rsa.base.cra_flags = 0;
	ret = crypto_रेजिस्टर_akcipher(&rsa);
	अगर (ret)
		वापस ret;

	ret = crypto_रेजिस्टर_kpp(&dh);
	अगर (ret)
		जाओ unreg_rsa;

	अगर (qm->ver >= QM_HW_V3) अणु
		ret = hpre_रेजिस्टर_ecdh();
		अगर (ret)
			जाओ unreg_dh;
		ret = crypto_रेजिस्टर_kpp(&curve25519_alg);
		अगर (ret)
			जाओ unreg_ecdh;
	पूर्ण
	वापस 0;

unreg_ecdh:
	hpre_unरेजिस्टर_ecdh();
unreg_dh:
	crypto_unरेजिस्टर_kpp(&dh);
unreg_rsa:
	crypto_unरेजिस्टर_akcipher(&rsa);
	वापस ret;
पूर्ण

व्योम hpre_algs_unरेजिस्टर(काष्ठा hisi_qm *qm)
अणु
	अगर (qm->ver >= QM_HW_V3) अणु
		crypto_unरेजिस्टर_kpp(&curve25519_alg);
		hpre_unरेजिस्टर_ecdh();
	पूर्ण

	crypto_unरेजिस्टर_kpp(&dh);
	crypto_unरेजिस्टर_akcipher(&rsa);
पूर्ण
