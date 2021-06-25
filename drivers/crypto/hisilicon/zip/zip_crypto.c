<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 HiSilicon Limited. */
#समावेश <crypto/पूर्णांकernal/acompress.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश "zip.h"

/* hisi_zip_sqe dw3 */
#घोषणा HZIP_BD_STATUS_M			GENMASK(7, 0)
/* hisi_zip_sqe dw7 */
#घोषणा HZIP_IN_SGE_DATA_OFFSET_M		GENMASK(23, 0)
#घोषणा HZIP_SQE_TYPE_M				GENMASK(31, 28)
/* hisi_zip_sqe dw8 */
#घोषणा HZIP_OUT_SGE_DATA_OFFSET_M		GENMASK(23, 0)
/* hisi_zip_sqe dw9 */
#घोषणा HZIP_REQ_TYPE_M				GENMASK(7, 0)
#घोषणा HZIP_ALG_TYPE_ZLIB			0x02
#घोषणा HZIP_ALG_TYPE_GZIP			0x03
#घोषणा HZIP_BUF_TYPE_M				GENMASK(11, 8)
#घोषणा HZIP_PBUFFER				0x0
#घोषणा HZIP_SGL				0x1

#घोषणा HZIP_ZLIB_HEAD_SIZE			2
#घोषणा HZIP_GZIP_HEAD_SIZE			10

#घोषणा GZIP_HEAD_FHCRC_BIT			BIT(1)
#घोषणा GZIP_HEAD_FEXTRA_BIT			BIT(2)
#घोषणा GZIP_HEAD_FNAME_BIT			BIT(3)
#घोषणा GZIP_HEAD_FCOMMENT_BIT			BIT(4)

#घोषणा GZIP_HEAD_FLG_SHIFT			3
#घोषणा GZIP_HEAD_FEXTRA_SHIFT			10
#घोषणा GZIP_HEAD_FEXTRA_XLEN			2UL
#घोषणा GZIP_HEAD_FHCRC_SIZE			2

#घोषणा HZIP_GZIP_HEAD_BUF			256
#घोषणा HZIP_ALG_PRIORITY			300
#घोषणा HZIP_SGL_SGE_NR				10

अटल स्थिर u8 zlib_head[HZIP_ZLIB_HEAD_SIZE] = अणु0x78, 0x9cपूर्ण;
अटल स्थिर u8 gzip_head[HZIP_GZIP_HEAD_SIZE] = अणु
	0x1f, 0x8b, 0x08, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x03
पूर्ण;

क्रमागत hisi_zip_alg_type अणु
	HZIP_ALG_TYPE_COMP = 0,
	HZIP_ALG_TYPE_DECOMP = 1,
पूर्ण;

क्रमागत अणु
	HZIP_QPC_COMP,
	HZIP_QPC_DECOMP,
	HZIP_CTX_Q_NUM
पूर्ण;

#घोषणा COMP_NAME_TO_TYPE(alg_name)					\
	(!म_भेद((alg_name), "zlib-deflate") ? HZIP_ALG_TYPE_ZLIB :	\
	 !म_भेद((alg_name), "gzip") ? HZIP_ALG_TYPE_GZIP : 0)		\

#घोषणा TO_HEAD_SIZE(req_type)						\
	(((req_type) == HZIP_ALG_TYPE_ZLIB) ? माप(zlib_head) :	\
	 ((req_type) == HZIP_ALG_TYPE_GZIP) ? माप(gzip_head) : 0)	\

#घोषणा TO_HEAD(req_type)						\
	(((req_type) == HZIP_ALG_TYPE_ZLIB) ? zlib_head :		\
	 ((req_type) == HZIP_ALG_TYPE_GZIP) ? gzip_head : शून्य)		\

काष्ठा hisi_zip_req अणु
	काष्ठा acomp_req *req;
	u32 sskip;
	u32 dskip;
	काष्ठा hisi_acc_hw_sgl *hw_src;
	काष्ठा hisi_acc_hw_sgl *hw_dst;
	dma_addr_t dma_src;
	dma_addr_t dma_dst;
	u16 req_id;
पूर्ण;

काष्ठा hisi_zip_req_q अणु
	काष्ठा hisi_zip_req *q;
	अचिन्हित दीर्घ *req_biपंचांगap;
	rwlock_t req_lock;
	u16 size;
पूर्ण;

काष्ठा hisi_zip_qp_ctx अणु
	काष्ठा hisi_qp *qp;
	काष्ठा hisi_zip_req_q req_q;
	काष्ठा hisi_acc_sgl_pool *sgl_pool;
	काष्ठा hisi_zip *zip_dev;
	काष्ठा hisi_zip_ctx *ctx;
पूर्ण;

काष्ठा hisi_zip_sqe_ops अणु
	u8 sqe_type;
	व्योम (*fill_addr)(काष्ठा hisi_zip_sqe *sqe, काष्ठा hisi_zip_req *req);
	व्योम (*fill_buf_size)(काष्ठा hisi_zip_sqe *sqe, काष्ठा hisi_zip_req *req);
	व्योम (*fill_buf_type)(काष्ठा hisi_zip_sqe *sqe, u8 buf_type);
	व्योम (*fill_req_type)(काष्ठा hisi_zip_sqe *sqe, u8 req_type);
	व्योम (*fill_tag)(काष्ठा hisi_zip_sqe *sqe, काष्ठा hisi_zip_req *req);
	व्योम (*fill_sqe_type)(काष्ठा hisi_zip_sqe *sqe, u8 sqe_type);
	u32 (*get_tag)(काष्ठा hisi_zip_sqe *sqe);
	u32 (*get_status)(काष्ठा hisi_zip_sqe *sqe);
	u32 (*get_dstlen)(काष्ठा hisi_zip_sqe *sqe);
पूर्ण;

काष्ठा hisi_zip_ctx अणु
	काष्ठा hisi_zip_qp_ctx qp_ctx[HZIP_CTX_Q_NUM];
	स्थिर काष्ठा hisi_zip_sqe_ops *ops;
पूर्ण;

अटल पूर्णांक sgl_sge_nr_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;
	u16 n;

	अगर (!val)
		वापस -EINVAL;

	ret = kstrtou16(val, 10, &n);
	अगर (ret || n == 0 || n > HISI_ACC_SGL_SGE_NR_MAX)
		वापस -EINVAL;

	वापस param_set_पूर्णांक(val, kp);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops sgl_sge_nr_ops = अणु
	.set = sgl_sge_nr_set,
	.get = param_get_पूर्णांक,
पूर्ण;

अटल u16 sgl_sge_nr = HZIP_SGL_SGE_NR;
module_param_cb(sgl_sge_nr, &sgl_sge_nr_ops, &sgl_sge_nr, 0444);
MODULE_PARM_DESC(sgl_sge_nr, "Number of sge in sgl(1-255)");

अटल u16 get_extra_field_size(स्थिर u8 *start)
अणु
	वापस *((u16 *)start) + GZIP_HEAD_FEXTRA_XLEN;
पूर्ण

अटल u32 get_name_field_size(स्थिर u8 *start)
अणु
	वापस म_माप(start) + 1;
पूर्ण

अटल u32 get_comment_field_size(स्थिर u8 *start)
अणु
	वापस म_माप(start) + 1;
पूर्ण

अटल u32 __get_gzip_head_size(स्थिर u8 *src)
अणु
	u8 head_flg = *(src + GZIP_HEAD_FLG_SHIFT);
	u32 size = GZIP_HEAD_FEXTRA_SHIFT;

	अगर (head_flg & GZIP_HEAD_FEXTRA_BIT)
		size += get_extra_field_size(src + size);
	अगर (head_flg & GZIP_HEAD_FNAME_BIT)
		size += get_name_field_size(src + size);
	अगर (head_flg & GZIP_HEAD_FCOMMENT_BIT)
		size += get_comment_field_size(src + size);
	अगर (head_flg & GZIP_HEAD_FHCRC_BIT)
		size += GZIP_HEAD_FHCRC_SIZE;

	वापस size;
पूर्ण

अटल माप_प्रकार __maybe_unused get_gzip_head_size(काष्ठा scatterlist *sgl)
अणु
	अक्षर buf[HZIP_GZIP_HEAD_BUF];

	sg_copy_to_buffer(sgl, sg_nents(sgl), buf, माप(buf));

	वापस __get_gzip_head_size(buf);
पूर्ण

अटल पूर्णांक add_comp_head(काष्ठा scatterlist *dst, u8 req_type)
अणु
	पूर्णांक head_size = TO_HEAD_SIZE(req_type);
	स्थिर u8 *head = TO_HEAD(req_type);
	पूर्णांक ret;

	ret = sg_copy_from_buffer(dst, sg_nents(dst), head, head_size);
	अगर (ret != head_size) अणु
		pr_err("the head size of buffer is wrong (%d)!\n", ret);
		वापस -ENOMEM;
	पूर्ण

	वापस head_size;
पूर्ण

अटल पूर्णांक get_comp_head_size(काष्ठा acomp_req *acomp_req, u8 req_type)
अणु
	अगर (!acomp_req->src || !acomp_req->slen)
		वापस -EINVAL;

	अगर (req_type == HZIP_ALG_TYPE_GZIP &&
	    acomp_req->slen < GZIP_HEAD_FEXTRA_SHIFT)
		वापस -EINVAL;

	चयन (req_type) अणु
	हाल HZIP_ALG_TYPE_ZLIB:
		वापस TO_HEAD_SIZE(HZIP_ALG_TYPE_ZLIB);
	हाल HZIP_ALG_TYPE_GZIP:
		वापस TO_HEAD_SIZE(HZIP_ALG_TYPE_GZIP);
	शेष:
		pr_err("request type does not support!\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा hisi_zip_req *hisi_zip_create_req(काष्ठा acomp_req *req,
						काष्ठा hisi_zip_qp_ctx *qp_ctx,
						माप_प्रकार head_size, bool is_comp)
अणु
	काष्ठा hisi_zip_req_q *req_q = &qp_ctx->req_q;
	काष्ठा hisi_zip_req *q = req_q->q;
	काष्ठा hisi_zip_req *req_cache;
	पूर्णांक req_id;

	ग_लिखो_lock(&req_q->req_lock);

	req_id = find_first_zero_bit(req_q->req_biपंचांगap, req_q->size);
	अगर (req_id >= req_q->size) अणु
		ग_लिखो_unlock(&req_q->req_lock);
		dev_dbg(&qp_ctx->qp->qm->pdev->dev, "req cache is full!\n");
		वापस ERR_PTR(-EAGAIN);
	पूर्ण
	set_bit(req_id, req_q->req_biपंचांगap);

	req_cache = q + req_id;
	req_cache->req_id = req_id;
	req_cache->req = req;

	अगर (is_comp) अणु
		req_cache->sskip = 0;
		req_cache->dskip = head_size;
	पूर्ण अन्यथा अणु
		req_cache->sskip = head_size;
		req_cache->dskip = 0;
	पूर्ण

	ग_लिखो_unlock(&req_q->req_lock);

	वापस req_cache;
पूर्ण

अटल व्योम hisi_zip_हटाओ_req(काष्ठा hisi_zip_qp_ctx *qp_ctx,
				काष्ठा hisi_zip_req *req)
अणु
	काष्ठा hisi_zip_req_q *req_q = &qp_ctx->req_q;

	ग_लिखो_lock(&req_q->req_lock);
	clear_bit(req->req_id, req_q->req_biपंचांगap);
	स_रखो(req, 0, माप(काष्ठा hisi_zip_req));
	ग_लिखो_unlock(&req_q->req_lock);
पूर्ण

अटल व्योम hisi_zip_fill_addr(काष्ठा hisi_zip_sqe *sqe, काष्ठा hisi_zip_req *req)
अणु
	sqe->source_addr_l = lower_32_bits(req->dma_src);
	sqe->source_addr_h = upper_32_bits(req->dma_src);
	sqe->dest_addr_l = lower_32_bits(req->dma_dst);
	sqe->dest_addr_h = upper_32_bits(req->dma_dst);
पूर्ण

अटल व्योम hisi_zip_fill_buf_size(काष्ठा hisi_zip_sqe *sqe, काष्ठा hisi_zip_req *req)
अणु
	काष्ठा acomp_req *a_req = req->req;

	sqe->input_data_length = a_req->slen - req->sskip;
	sqe->dest_avail_out = a_req->dlen - req->dskip;
	sqe->dw7 = FIELD_PREP(HZIP_IN_SGE_DATA_OFFSET_M, req->sskip);
	sqe->dw8 = FIELD_PREP(HZIP_OUT_SGE_DATA_OFFSET_M, req->dskip);
पूर्ण

अटल व्योम hisi_zip_fill_buf_type(काष्ठा hisi_zip_sqe *sqe, u8 buf_type)
अणु
	u32 val;

	val = sqe->dw9 & ~HZIP_BUF_TYPE_M;
	val |= FIELD_PREP(HZIP_BUF_TYPE_M, buf_type);
	sqe->dw9 = val;
पूर्ण

अटल व्योम hisi_zip_fill_req_type(काष्ठा hisi_zip_sqe *sqe, u8 req_type)
अणु
	u32 val;

	val = sqe->dw9 & ~HZIP_REQ_TYPE_M;
	val |= FIELD_PREP(HZIP_REQ_TYPE_M, req_type);
	sqe->dw9 = val;
पूर्ण

अटल व्योम hisi_zip_fill_tag_v1(काष्ठा hisi_zip_sqe *sqe, काष्ठा hisi_zip_req *req)
अणु
	sqe->dw13 = req->req_id;
पूर्ण

अटल व्योम hisi_zip_fill_tag_v2(काष्ठा hisi_zip_sqe *sqe, काष्ठा hisi_zip_req *req)
अणु
	sqe->dw26 = req->req_id;
पूर्ण

अटल व्योम hisi_zip_fill_sqe_type(काष्ठा hisi_zip_sqe *sqe, u8 sqe_type)
अणु
	u32 val;

	val = sqe->dw7 & ~HZIP_SQE_TYPE_M;
	val |= FIELD_PREP(HZIP_SQE_TYPE_M, sqe_type);
	sqe->dw7 = val;
पूर्ण

अटल व्योम hisi_zip_fill_sqe(काष्ठा hisi_zip_ctx *ctx, काष्ठा hisi_zip_sqe *sqe,
			      u8 req_type, काष्ठा hisi_zip_req *req)
अणु
	स्थिर काष्ठा hisi_zip_sqe_ops *ops = ctx->ops;

	स_रखो(sqe, 0, माप(काष्ठा hisi_zip_sqe));

	ops->fill_addr(sqe, req);
	ops->fill_buf_size(sqe, req);
	ops->fill_buf_type(sqe, HZIP_SGL);
	ops->fill_req_type(sqe, req_type);
	ops->fill_tag(sqe, req);
	ops->fill_sqe_type(sqe, ops->sqe_type);
पूर्ण

अटल पूर्णांक hisi_zip_करो_work(काष्ठा hisi_zip_req *req,
			    काष्ठा hisi_zip_qp_ctx *qp_ctx)
अणु
	काष्ठा hisi_acc_sgl_pool *pool = qp_ctx->sgl_pool;
	काष्ठा hisi_zip_dfx *dfx = &qp_ctx->zip_dev->dfx;
	काष्ठा acomp_req *a_req = req->req;
	काष्ठा hisi_qp *qp = qp_ctx->qp;
	काष्ठा device *dev = &qp->qm->pdev->dev;
	काष्ठा hisi_zip_sqe zip_sqe;
	पूर्णांक ret;

	अगर (!a_req->src || !a_req->slen || !a_req->dst || !a_req->dlen)
		वापस -EINVAL;

	req->hw_src = hisi_acc_sg_buf_map_to_hw_sgl(dev, a_req->src, pool,
						    req->req_id << 1, &req->dma_src);
	अगर (IS_ERR(req->hw_src)) अणु
		dev_err(dev, "failed to map the src buffer to hw sgl (%ld)!\n",
			PTR_ERR(req->hw_src));
		वापस PTR_ERR(req->hw_src);
	पूर्ण

	req->hw_dst = hisi_acc_sg_buf_map_to_hw_sgl(dev, a_req->dst, pool,
						    (req->req_id << 1) + 1,
						    &req->dma_dst);
	अगर (IS_ERR(req->hw_dst)) अणु
		ret = PTR_ERR(req->hw_dst);
		dev_err(dev, "failed to map the dst buffer to hw slg (%d)!\n",
			ret);
		जाओ err_unmap_input;
	पूर्ण

	hisi_zip_fill_sqe(qp_ctx->ctx, &zip_sqe, qp->req_type, req);

	/* send command to start a task */
	atomic64_inc(&dfx->send_cnt);
	ret = hisi_qp_send(qp, &zip_sqe);
	अगर (ret < 0) अणु
		atomic64_inc(&dfx->send_busy_cnt);
		ret = -EAGAIN;
		dev_dbg_ratelimited(dev, "failed to send request!\n");
		जाओ err_unmap_output;
	पूर्ण

	वापस -EINPROGRESS;

err_unmap_output:
	hisi_acc_sg_buf_unmap(dev, a_req->dst, req->hw_dst);
err_unmap_input:
	hisi_acc_sg_buf_unmap(dev, a_req->src, req->hw_src);
	वापस ret;
पूर्ण

अटल u32 hisi_zip_get_tag_v1(काष्ठा hisi_zip_sqe *sqe)
अणु
	वापस sqe->dw13;
पूर्ण

अटल u32 hisi_zip_get_tag_v2(काष्ठा hisi_zip_sqe *sqe)
अणु
	वापस sqe->dw26;
पूर्ण

अटल u32 hisi_zip_get_status(काष्ठा hisi_zip_sqe *sqe)
अणु
	वापस sqe->dw3 & HZIP_BD_STATUS_M;
पूर्ण

अटल u32 hisi_zip_get_dstlen(काष्ठा hisi_zip_sqe *sqe)
अणु
	वापस sqe->produced;
पूर्ण

अटल व्योम hisi_zip_acomp_cb(काष्ठा hisi_qp *qp, व्योम *data)
अणु
	काष्ठा hisi_zip_qp_ctx *qp_ctx = qp->qp_ctx;
	स्थिर काष्ठा hisi_zip_sqe_ops *ops = qp_ctx->ctx->ops;
	काष्ठा hisi_zip_dfx *dfx = &qp_ctx->zip_dev->dfx;
	काष्ठा hisi_zip_req_q *req_q = &qp_ctx->req_q;
	काष्ठा device *dev = &qp->qm->pdev->dev;
	काष्ठा hisi_zip_sqe *sqe = data;
	u32 tag = ops->get_tag(sqe);
	काष्ठा hisi_zip_req *req = req_q->q + tag;
	काष्ठा acomp_req *acomp_req = req->req;
	u32 status, dlen, head_size;
	पूर्णांक err = 0;

	atomic64_inc(&dfx->recv_cnt);
	status = ops->get_status(sqe);
	अगर (status != 0 && status != HZIP_NC_ERR) अणु
		dev_err(dev, "%scompress fail in qp%u: %u, output: %u\n",
			(qp->alg_type == 0) ? "" : "de", qp->qp_id, status,
			sqe->produced);
		atomic64_inc(&dfx->err_bd_cnt);
		err = -EIO;
	पूर्ण

	dlen = ops->get_dstlen(sqe);

	hisi_acc_sg_buf_unmap(dev, acomp_req->src, req->hw_src);
	hisi_acc_sg_buf_unmap(dev, acomp_req->dst, req->hw_dst);

	head_size = (qp->alg_type == 0) ? TO_HEAD_SIZE(qp->req_type) : 0;
	acomp_req->dlen = dlen + head_size;

	अगर (acomp_req->base.complete)
		acomp_request_complete(acomp_req, err);

	hisi_zip_हटाओ_req(qp_ctx, req);
पूर्ण

अटल पूर्णांक hisi_zip_acompress(काष्ठा acomp_req *acomp_req)
अणु
	काष्ठा hisi_zip_ctx *ctx = crypto_tfm_ctx(acomp_req->base.tfm);
	काष्ठा hisi_zip_qp_ctx *qp_ctx = &ctx->qp_ctx[HZIP_QPC_COMP];
	काष्ठा device *dev = &qp_ctx->qp->qm->pdev->dev;
	काष्ठा hisi_zip_req *req;
	पूर्णांक head_size;
	पूर्णांक ret;

	/* let's output compression head now */
	head_size = add_comp_head(acomp_req->dst, qp_ctx->qp->req_type);
	अगर (head_size < 0) अणु
		dev_err_ratelimited(dev, "failed to add comp head (%d)!\n",
				    head_size);
		वापस head_size;
	पूर्ण

	req = hisi_zip_create_req(acomp_req, qp_ctx, head_size, true);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	ret = hisi_zip_करो_work(req, qp_ctx);
	अगर (ret != -EINPROGRESS) अणु
		dev_info_ratelimited(dev, "failed to do compress (%d)!\n", ret);
		hisi_zip_हटाओ_req(qp_ctx, req);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hisi_zip_adecompress(काष्ठा acomp_req *acomp_req)
अणु
	काष्ठा hisi_zip_ctx *ctx = crypto_tfm_ctx(acomp_req->base.tfm);
	काष्ठा hisi_zip_qp_ctx *qp_ctx = &ctx->qp_ctx[HZIP_QPC_DECOMP];
	काष्ठा device *dev = &qp_ctx->qp->qm->pdev->dev;
	काष्ठा hisi_zip_req *req;
	पूर्णांक head_size, ret;

	head_size = get_comp_head_size(acomp_req, qp_ctx->qp->req_type);
	अगर (head_size < 0) अणु
		dev_err_ratelimited(dev, "failed to get comp head size (%d)!\n",
				    head_size);
		वापस head_size;
	पूर्ण

	req = hisi_zip_create_req(acomp_req, qp_ctx, head_size, false);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	ret = hisi_zip_करो_work(req, qp_ctx);
	अगर (ret != -EINPROGRESS) अणु
		dev_info_ratelimited(dev, "failed to do decompress (%d)!\n",
				     ret);
		hisi_zip_हटाओ_req(qp_ctx, req);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hisi_zip_start_qp(काष्ठा hisi_qp *qp, काष्ठा hisi_zip_qp_ctx *ctx,
			     पूर्णांक alg_type, पूर्णांक req_type)
अणु
	काष्ठा device *dev = &qp->qm->pdev->dev;
	पूर्णांक ret;

	qp->req_type = req_type;
	qp->alg_type = alg_type;
	qp->qp_ctx = ctx;

	ret = hisi_qm_start_qp(qp, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to start qp (%d)!\n", ret);
		वापस ret;
	पूर्ण

	ctx->qp = qp;

	वापस 0;
पूर्ण

अटल व्योम hisi_zip_release_qp(काष्ठा hisi_zip_qp_ctx *ctx)
अणु
	hisi_qm_stop_qp(ctx->qp);
	hisi_qm_release_qp(ctx->qp);
पूर्ण

अटल स्थिर काष्ठा hisi_zip_sqe_ops hisi_zip_ops_v1 = अणु
	.sqe_type		= 0,
	.fill_addr		= hisi_zip_fill_addr,
	.fill_buf_size		= hisi_zip_fill_buf_size,
	.fill_buf_type		= hisi_zip_fill_buf_type,
	.fill_req_type		= hisi_zip_fill_req_type,
	.fill_tag		= hisi_zip_fill_tag_v1,
	.fill_sqe_type		= hisi_zip_fill_sqe_type,
	.get_tag		= hisi_zip_get_tag_v1,
	.get_status		= hisi_zip_get_status,
	.get_dstlen		= hisi_zip_get_dstlen,
पूर्ण;

अटल स्थिर काष्ठा hisi_zip_sqe_ops hisi_zip_ops_v2 = अणु
	.sqe_type		= 0x3,
	.fill_addr		= hisi_zip_fill_addr,
	.fill_buf_size		= hisi_zip_fill_buf_size,
	.fill_buf_type		= hisi_zip_fill_buf_type,
	.fill_req_type		= hisi_zip_fill_req_type,
	.fill_tag		= hisi_zip_fill_tag_v2,
	.fill_sqe_type		= hisi_zip_fill_sqe_type,
	.get_tag		= hisi_zip_get_tag_v2,
	.get_status		= hisi_zip_get_status,
	.get_dstlen		= hisi_zip_get_dstlen,
पूर्ण;

अटल पूर्णांक hisi_zip_ctx_init(काष्ठा hisi_zip_ctx *hisi_zip_ctx, u8 req_type, पूर्णांक node)
अणु
	काष्ठा hisi_qp *qps[HZIP_CTX_Q_NUM] = अणु शून्य पूर्ण;
	काष्ठा hisi_zip_qp_ctx *qp_ctx;
	काष्ठा hisi_zip *hisi_zip;
	पूर्णांक ret, i, j;

	ret = zip_create_qps(qps, HZIP_CTX_Q_NUM, node);
	अगर (ret) अणु
		pr_err("failed to create zip qps (%d)!\n", ret);
		वापस -ENODEV;
	पूर्ण

	hisi_zip = container_of(qps[0]->qm, काष्ठा hisi_zip, qm);

	क्रम (i = 0; i < HZIP_CTX_Q_NUM; i++) अणु
		/* alg_type = 0 क्रम compress, 1 क्रम decompress in hw sqe */
		qp_ctx = &hisi_zip_ctx->qp_ctx[i];
		qp_ctx->ctx = hisi_zip_ctx;
		ret = hisi_zip_start_qp(qps[i], qp_ctx, i, req_type);
		अगर (ret) अणु
			क्रम (j = i - 1; j >= 0; j--)
				hisi_qm_stop_qp(hisi_zip_ctx->qp_ctx[j].qp);

			hisi_qm_मुक्त_qps(qps, HZIP_CTX_Q_NUM);
			वापस ret;
		पूर्ण

		qp_ctx->zip_dev = hisi_zip;
	पूर्ण

	अगर (hisi_zip->qm.ver < QM_HW_V3)
		hisi_zip_ctx->ops = &hisi_zip_ops_v1;
	अन्यथा
		hisi_zip_ctx->ops = &hisi_zip_ops_v2;

	वापस 0;
पूर्ण

अटल व्योम hisi_zip_ctx_निकास(काष्ठा hisi_zip_ctx *hisi_zip_ctx)
अणु
	पूर्णांक i;

	क्रम (i = 1; i >= 0; i--)
		hisi_zip_release_qp(&hisi_zip_ctx->qp_ctx[i]);
पूर्ण

अटल पूर्णांक hisi_zip_create_req_q(काष्ठा hisi_zip_ctx *ctx)
अणु
	काष्ठा hisi_zip_req_q *req_q;
	पूर्णांक i, ret;

	क्रम (i = 0; i < HZIP_CTX_Q_NUM; i++) अणु
		req_q = &ctx->qp_ctx[i].req_q;
		req_q->size = QM_Q_DEPTH;

		req_q->req_biपंचांगap = kसुस्मृति(BITS_TO_LONGS(req_q->size),
					    माप(दीर्घ), GFP_KERNEL);
		अगर (!req_q->req_biपंचांगap) अणु
			ret = -ENOMEM;
			अगर (i == 0)
				वापस ret;

			जाओ err_मुक्त_loop0;
		पूर्ण
		rwlock_init(&req_q->req_lock);

		req_q->q = kसुस्मृति(req_q->size, माप(काष्ठा hisi_zip_req),
				   GFP_KERNEL);
		अगर (!req_q->q) अणु
			ret = -ENOMEM;
			अगर (i == 0)
				जाओ err_मुक्त_biपंचांगap;
			अन्यथा
				जाओ err_मुक्त_loop1;
		पूर्ण
	पूर्ण

	वापस 0;

err_मुक्त_loop1:
	kमुक्त(ctx->qp_ctx[HZIP_QPC_DECOMP].req_q.req_biपंचांगap);
err_मुक्त_loop0:
	kमुक्त(ctx->qp_ctx[HZIP_QPC_COMP].req_q.q);
err_मुक्त_biपंचांगap:
	kमुक्त(ctx->qp_ctx[HZIP_QPC_COMP].req_q.req_biपंचांगap);
	वापस ret;
पूर्ण

अटल व्योम hisi_zip_release_req_q(काष्ठा hisi_zip_ctx *ctx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HZIP_CTX_Q_NUM; i++) अणु
		kमुक्त(ctx->qp_ctx[i].req_q.q);
		kमुक्त(ctx->qp_ctx[i].req_q.req_biपंचांगap);
	पूर्ण
पूर्ण

अटल पूर्णांक hisi_zip_create_sgl_pool(काष्ठा hisi_zip_ctx *ctx)
अणु
	काष्ठा hisi_zip_qp_ctx *पंचांगp;
	काष्ठा device *dev;
	पूर्णांक i;

	क्रम (i = 0; i < HZIP_CTX_Q_NUM; i++) अणु
		पंचांगp = &ctx->qp_ctx[i];
		dev = &पंचांगp->qp->qm->pdev->dev;
		पंचांगp->sgl_pool = hisi_acc_create_sgl_pool(dev, QM_Q_DEPTH << 1,
							 sgl_sge_nr);
		अगर (IS_ERR(पंचांगp->sgl_pool)) अणु
			अगर (i == 1)
				जाओ err_मुक्त_sgl_pool0;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;

err_मुक्त_sgl_pool0:
	hisi_acc_मुक्त_sgl_pool(&ctx->qp_ctx[HZIP_QPC_COMP].qp->qm->pdev->dev,
			       ctx->qp_ctx[HZIP_QPC_COMP].sgl_pool);
	वापस -ENOMEM;
पूर्ण

अटल व्योम hisi_zip_release_sgl_pool(काष्ठा hisi_zip_ctx *ctx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HZIP_CTX_Q_NUM; i++)
		hisi_acc_मुक्त_sgl_pool(&ctx->qp_ctx[i].qp->qm->pdev->dev,
				       ctx->qp_ctx[i].sgl_pool);
पूर्ण

अटल व्योम hisi_zip_set_acomp_cb(काष्ठा hisi_zip_ctx *ctx,
				  व्योम (*fn)(काष्ठा hisi_qp *, व्योम *))
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HZIP_CTX_Q_NUM; i++)
		ctx->qp_ctx[i].qp->req_cb = fn;
पूर्ण

अटल पूर्णांक hisi_zip_acomp_init(काष्ठा crypto_acomp *tfm)
अणु
	स्थिर अक्षर *alg_name = crypto_tfm_alg_name(&tfm->base);
	काष्ठा hisi_zip_ctx *ctx = crypto_tfm_ctx(&tfm->base);
	काष्ठा device *dev;
	पूर्णांक ret;

	ret = hisi_zip_ctx_init(ctx, COMP_NAME_TO_TYPE(alg_name), tfm->base.node);
	अगर (ret) अणु
		pr_err("failed to init ctx (%d)!\n", ret);
		वापस ret;
	पूर्ण

	dev = &ctx->qp_ctx[0].qp->qm->pdev->dev;

	ret = hisi_zip_create_req_q(ctx);
	अगर (ret) अणु
		dev_err(dev, "failed to create request queue (%d)!\n", ret);
		जाओ err_ctx_निकास;
	पूर्ण

	ret = hisi_zip_create_sgl_pool(ctx);
	अगर (ret) अणु
		dev_err(dev, "failed to create sgl pool (%d)!\n", ret);
		जाओ err_release_req_q;
	पूर्ण

	hisi_zip_set_acomp_cb(ctx, hisi_zip_acomp_cb);

	वापस 0;

err_release_req_q:
	hisi_zip_release_req_q(ctx);
err_ctx_निकास:
	hisi_zip_ctx_निकास(ctx);
	वापस ret;
पूर्ण

अटल व्योम hisi_zip_acomp_निकास(काष्ठा crypto_acomp *tfm)
अणु
	काष्ठा hisi_zip_ctx *ctx = crypto_tfm_ctx(&tfm->base);

	hisi_zip_set_acomp_cb(ctx, शून्य);
	hisi_zip_release_sgl_pool(ctx);
	hisi_zip_release_req_q(ctx);
	hisi_zip_ctx_निकास(ctx);
पूर्ण

अटल काष्ठा acomp_alg hisi_zip_acomp_zlib = अणु
	.init			= hisi_zip_acomp_init,
	.निकास			= hisi_zip_acomp_निकास,
	.compress		= hisi_zip_acompress,
	.decompress		= hisi_zip_adecompress,
	.base			= अणु
		.cra_name		= "zlib-deflate",
		.cra_driver_name	= "hisi-zlib-acomp",
		.cra_module		= THIS_MODULE,
		.cra_priority           = HZIP_ALG_PRIORITY,
		.cra_ctxsize		= माप(काष्ठा hisi_zip_ctx),
	पूर्ण
पूर्ण;

अटल काष्ठा acomp_alg hisi_zip_acomp_gzip = अणु
	.init			= hisi_zip_acomp_init,
	.निकास			= hisi_zip_acomp_निकास,
	.compress		= hisi_zip_acompress,
	.decompress		= hisi_zip_adecompress,
	.base			= अणु
		.cra_name		= "gzip",
		.cra_driver_name	= "hisi-gzip-acomp",
		.cra_module		= THIS_MODULE,
		.cra_priority           = HZIP_ALG_PRIORITY,
		.cra_ctxsize		= माप(काष्ठा hisi_zip_ctx),
	पूर्ण
पूर्ण;

पूर्णांक hisi_zip_रेजिस्टर_to_crypto(काष्ठा hisi_qm *qm)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_acomp(&hisi_zip_acomp_zlib);
	अगर (ret) अणु
		pr_err("failed to register to zlib (%d)!\n", ret);
		वापस ret;
	पूर्ण

	ret = crypto_रेजिस्टर_acomp(&hisi_zip_acomp_gzip);
	अगर (ret) अणु
		pr_err("failed to register to gzip (%d)!\n", ret);
		crypto_unरेजिस्टर_acomp(&hisi_zip_acomp_zlib);
	पूर्ण

	वापस ret;
पूर्ण

व्योम hisi_zip_unरेजिस्टर_from_crypto(काष्ठा hisi_qm *qm)
अणु
	crypto_unरेजिस्टर_acomp(&hisi_zip_acomp_gzip);
	crypto_unरेजिस्टर_acomp(&hisi_zip_acomp_zlib);
पूर्ण
