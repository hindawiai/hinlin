<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/module.h>
#समावेश <crypto/पूर्णांकernal/rsa.h>
#समावेश <crypto/पूर्णांकernal/akcipher.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/kpp.h>
#समावेश <crypto/पूर्णांकernal/kpp.h>
#समावेश <crypto/dh.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fips.h>
#समावेश <crypto/scatterwalk.h>
#समावेश "icp_qat_fw_pke.h"
#समावेश "adf_accel_devices.h"
#समावेश "adf_transport.h"
#समावेश "adf_common_drv.h"
#समावेश "qat_crypto.h"

अटल DEFINE_MUTEX(algs_lock);
अटल अचिन्हित पूर्णांक active_devs;

काष्ठा qat_rsa_input_params अणु
	जोड़ अणु
		काष्ठा अणु
			dma_addr_t m;
			dma_addr_t e;
			dma_addr_t n;
		पूर्ण enc;
		काष्ठा अणु
			dma_addr_t c;
			dma_addr_t d;
			dma_addr_t n;
		पूर्ण dec;
		काष्ठा अणु
			dma_addr_t c;
			dma_addr_t p;
			dma_addr_t q;
			dma_addr_t dp;
			dma_addr_t dq;
			dma_addr_t qinv;
		पूर्ण dec_crt;
		u64 in_tab[8];
	पूर्ण;
पूर्ण __packed __aligned(64);

काष्ठा qat_rsa_output_params अणु
	जोड़ अणु
		काष्ठा अणु
			dma_addr_t c;
		पूर्ण enc;
		काष्ठा अणु
			dma_addr_t m;
		पूर्ण dec;
		u64 out_tab[8];
	पूर्ण;
पूर्ण __packed __aligned(64);

काष्ठा qat_rsa_ctx अणु
	अक्षर *n;
	अक्षर *e;
	अक्षर *d;
	अक्षर *p;
	अक्षर *q;
	अक्षर *dp;
	अक्षर *dq;
	अक्षर *qinv;
	dma_addr_t dma_n;
	dma_addr_t dma_e;
	dma_addr_t dma_d;
	dma_addr_t dma_p;
	dma_addr_t dma_q;
	dma_addr_t dma_dp;
	dma_addr_t dma_dq;
	dma_addr_t dma_qinv;
	अचिन्हित पूर्णांक key_sz;
	bool crt_mode;
	काष्ठा qat_crypto_instance *inst;
पूर्ण __packed __aligned(64);

काष्ठा qat_dh_input_params अणु
	जोड़ अणु
		काष्ठा अणु
			dma_addr_t b;
			dma_addr_t xa;
			dma_addr_t p;
		पूर्ण in;
		काष्ठा अणु
			dma_addr_t xa;
			dma_addr_t p;
		पूर्ण in_g2;
		u64 in_tab[8];
	पूर्ण;
पूर्ण __packed __aligned(64);

काष्ठा qat_dh_output_params अणु
	जोड़ अणु
		dma_addr_t r;
		u64 out_tab[8];
	पूर्ण;
पूर्ण __packed __aligned(64);

काष्ठा qat_dh_ctx अणु
	अक्षर *g;
	अक्षर *xa;
	अक्षर *p;
	dma_addr_t dma_g;
	dma_addr_t dma_xa;
	dma_addr_t dma_p;
	अचिन्हित पूर्णांक p_size;
	bool g2;
	काष्ठा qat_crypto_instance *inst;
पूर्ण __packed __aligned(64);

काष्ठा qat_asym_request अणु
	जोड़ अणु
		काष्ठा qat_rsa_input_params rsa;
		काष्ठा qat_dh_input_params dh;
	पूर्ण in;
	जोड़ अणु
		काष्ठा qat_rsa_output_params rsa;
		काष्ठा qat_dh_output_params dh;
	पूर्ण out;
	dma_addr_t phy_in;
	dma_addr_t phy_out;
	अक्षर *src_align;
	अक्षर *dst_align;
	काष्ठा icp_qat_fw_pke_request req;
	जोड़ अणु
		काष्ठा qat_rsa_ctx *rsa;
		काष्ठा qat_dh_ctx *dh;
	पूर्ण ctx;
	जोड़ अणु
		काष्ठा akcipher_request *rsa;
		काष्ठा kpp_request *dh;
	पूर्ण areq;
	पूर्णांक err;
	व्योम (*cb)(काष्ठा icp_qat_fw_pke_resp *resp);
पूर्ण __aligned(64);

अटल व्योम qat_dh_cb(काष्ठा icp_qat_fw_pke_resp *resp)
अणु
	काष्ठा qat_asym_request *req = (व्योम *)(__क्रमce दीर्घ)resp->opaque;
	काष्ठा kpp_request *areq = req->areq.dh;
	काष्ठा device *dev = &GET_DEV(req->ctx.dh->inst->accel_dev);
	पूर्णांक err = ICP_QAT_FW_PKE_RESP_PKE_STAT_GET(
				resp->pke_resp_hdr.comn_resp_flags);

	err = (err == ICP_QAT_FW_COMN_STATUS_FLAG_OK) ? 0 : -EINVAL;

	अगर (areq->src) अणु
		अगर (req->src_align)
			dma_मुक्त_coherent(dev, req->ctx.dh->p_size,
					  req->src_align, req->in.dh.in.b);
		अन्यथा
			dma_unmap_single(dev, req->in.dh.in.b,
					 req->ctx.dh->p_size, DMA_TO_DEVICE);
	पूर्ण

	areq->dst_len = req->ctx.dh->p_size;
	अगर (req->dst_align) अणु
		scatterwalk_map_and_copy(req->dst_align, areq->dst, 0,
					 areq->dst_len, 1);

		dma_मुक्त_coherent(dev, req->ctx.dh->p_size, req->dst_align,
				  req->out.dh.r);
	पूर्ण अन्यथा अणु
		dma_unmap_single(dev, req->out.dh.r, req->ctx.dh->p_size,
				 DMA_FROM_DEVICE);
	पूर्ण

	dma_unmap_single(dev, req->phy_in, माप(काष्ठा qat_dh_input_params),
			 DMA_TO_DEVICE);
	dma_unmap_single(dev, req->phy_out,
			 माप(काष्ठा qat_dh_output_params),
			 DMA_TO_DEVICE);

	kpp_request_complete(areq, err);
पूर्ण

#घोषणा PKE_DH_1536 0x390c1a49
#घोषणा PKE_DH_G2_1536 0x2e0b1a3e
#घोषणा PKE_DH_2048 0x4d0c1a60
#घोषणा PKE_DH_G2_2048 0x3e0b1a55
#घोषणा PKE_DH_3072 0x510c1a77
#घोषणा PKE_DH_G2_3072 0x3a0b1a6c
#घोषणा PKE_DH_4096 0x690c1a8e
#घोषणा PKE_DH_G2_4096 0x4a0b1a83

अटल अचिन्हित दीर्घ qat_dh_fn_id(अचिन्हित पूर्णांक len, bool g2)
अणु
	अचिन्हित पूर्णांक bitslen = len << 3;

	चयन (bitslen) अणु
	हाल 1536:
		वापस g2 ? PKE_DH_G2_1536 : PKE_DH_1536;
	हाल 2048:
		वापस g2 ? PKE_DH_G2_2048 : PKE_DH_2048;
	हाल 3072:
		वापस g2 ? PKE_DH_G2_3072 : PKE_DH_3072;
	हाल 4096:
		वापस g2 ? PKE_DH_G2_4096 : PKE_DH_4096;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक qat_dh_compute_value(काष्ठा kpp_request *req)
अणु
	काष्ठा crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	काष्ठा qat_dh_ctx *ctx = kpp_tfm_ctx(tfm);
	काष्ठा qat_crypto_instance *inst = ctx->inst;
	काष्ठा device *dev = &GET_DEV(inst->accel_dev);
	काष्ठा qat_asym_request *qat_req =
			PTR_ALIGN(kpp_request_ctx(req), 64);
	काष्ठा icp_qat_fw_pke_request *msg = &qat_req->req;
	पूर्णांक ret, ctr = 0;
	पूर्णांक n_input_params = 0;

	अगर (unlikely(!ctx->xa))
		वापस -EINVAL;

	अगर (req->dst_len < ctx->p_size) अणु
		req->dst_len = ctx->p_size;
		वापस -EOVERFLOW;
	पूर्ण
	स_रखो(msg, '\0', माप(*msg));
	ICP_QAT_FW_PKE_HDR_VALID_FLAG_SET(msg->pke_hdr,
					  ICP_QAT_FW_COMN_REQ_FLAG_SET);

	msg->pke_hdr.cd_pars.func_id = qat_dh_fn_id(ctx->p_size,
						    !req->src && ctx->g2);
	अगर (unlikely(!msg->pke_hdr.cd_pars.func_id))
		वापस -EINVAL;

	qat_req->cb = qat_dh_cb;
	qat_req->ctx.dh = ctx;
	qat_req->areq.dh = req;
	msg->pke_hdr.service_type = ICP_QAT_FW_COMN_REQ_CPM_FW_PKE;
	msg->pke_hdr.comn_req_flags =
		ICP_QAT_FW_COMN_FLAGS_BUILD(QAT_COMN_PTR_TYPE_FLAT,
					    QAT_COMN_CD_FLD_TYPE_64BIT_ADR);

	/*
	 * If no source is provided use g as base
	 */
	अगर (req->src) अणु
		qat_req->in.dh.in.xa = ctx->dma_xa;
		qat_req->in.dh.in.p = ctx->dma_p;
		n_input_params = 3;
	पूर्ण अन्यथा अणु
		अगर (ctx->g2) अणु
			qat_req->in.dh.in_g2.xa = ctx->dma_xa;
			qat_req->in.dh.in_g2.p = ctx->dma_p;
			n_input_params = 2;
		पूर्ण अन्यथा अणु
			qat_req->in.dh.in.b = ctx->dma_g;
			qat_req->in.dh.in.xa = ctx->dma_xa;
			qat_req->in.dh.in.p = ctx->dma_p;
			n_input_params = 3;
		पूर्ण
	पूर्ण

	ret = -ENOMEM;
	अगर (req->src) अणु
		/*
		 * src can be of any size in valid range, but HW expects it to
		 * be the same as modulo p so in हाल it is dअगरferent we need
		 * to allocate a new buf and copy src data.
		 * In other हाल we just need to map the user provided buffer.
		 * Also need to make sure that it is in contiguous buffer.
		 */
		अगर (sg_is_last(req->src) && req->src_len == ctx->p_size) अणु
			qat_req->src_align = शून्य;
			qat_req->in.dh.in.b = dma_map_single(dev,
							     sg_virt(req->src),
							     req->src_len,
							     DMA_TO_DEVICE);
			अगर (unlikely(dma_mapping_error(dev,
						       qat_req->in.dh.in.b)))
				वापस ret;

		पूर्ण अन्यथा अणु
			पूर्णांक shअगरt = ctx->p_size - req->src_len;

			qat_req->src_align = dma_alloc_coherent(dev,
								ctx->p_size,
								&qat_req->in.dh.in.b,
								GFP_KERNEL);
			अगर (unlikely(!qat_req->src_align))
				वापस ret;

			scatterwalk_map_and_copy(qat_req->src_align + shअगरt,
						 req->src, 0, req->src_len, 0);
		पूर्ण
	पूर्ण
	/*
	 * dst can be of any size in valid range, but HW expects it to be the
	 * same as modulo m so in हाल it is dअगरferent we need to allocate a
	 * new buf and copy src data.
	 * In other हाल we just need to map the user provided buffer.
	 * Also need to make sure that it is in contiguous buffer.
	 */
	अगर (sg_is_last(req->dst) && req->dst_len == ctx->p_size) अणु
		qat_req->dst_align = शून्य;
		qat_req->out.dh.r = dma_map_single(dev, sg_virt(req->dst),
						   req->dst_len,
						   DMA_FROM_DEVICE);

		अगर (unlikely(dma_mapping_error(dev, qat_req->out.dh.r)))
			जाओ unmap_src;

	पूर्ण अन्यथा अणु
		qat_req->dst_align = dma_alloc_coherent(dev, ctx->p_size,
							&qat_req->out.dh.r,
							GFP_KERNEL);
		अगर (unlikely(!qat_req->dst_align))
			जाओ unmap_src;
	पूर्ण

	qat_req->in.dh.in_tab[n_input_params] = 0;
	qat_req->out.dh.out_tab[1] = 0;
	/* Mapping in.in.b or in.in_g2.xa is the same */
	qat_req->phy_in = dma_map_single(dev, &qat_req->in.dh.in.b,
					 माप(qat_req->in.dh.in.b),
					 DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, qat_req->phy_in)))
		जाओ unmap_dst;

	qat_req->phy_out = dma_map_single(dev, &qat_req->out.dh.r,
					  माप(qat_req->out.dh.r),
					  DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, qat_req->phy_out)))
		जाओ unmap_in_params;

	msg->pke_mid.src_data_addr = qat_req->phy_in;
	msg->pke_mid.dest_data_addr = qat_req->phy_out;
	msg->pke_mid.opaque = (u64)(__क्रमce दीर्घ)qat_req;
	msg->input_param_count = n_input_params;
	msg->output_param_count = 1;

	करो अणु
		ret = adf_send_message(ctx->inst->pke_tx, (u32 *)msg);
	पूर्ण जबतक (ret == -EBUSY && ctr++ < 100);

	अगर (!ret)
		वापस -EINPROGRESS;

	अगर (!dma_mapping_error(dev, qat_req->phy_out))
		dma_unmap_single(dev, qat_req->phy_out,
				 माप(काष्ठा qat_dh_output_params),
				 DMA_TO_DEVICE);
unmap_in_params:
	अगर (!dma_mapping_error(dev, qat_req->phy_in))
		dma_unmap_single(dev, qat_req->phy_in,
				 माप(काष्ठा qat_dh_input_params),
				 DMA_TO_DEVICE);
unmap_dst:
	अगर (qat_req->dst_align)
		dma_मुक्त_coherent(dev, ctx->p_size, qat_req->dst_align,
				  qat_req->out.dh.r);
	अन्यथा
		अगर (!dma_mapping_error(dev, qat_req->out.dh.r))
			dma_unmap_single(dev, qat_req->out.dh.r, ctx->p_size,
					 DMA_FROM_DEVICE);
unmap_src:
	अगर (req->src) अणु
		अगर (qat_req->src_align)
			dma_मुक्त_coherent(dev, ctx->p_size, qat_req->src_align,
					  qat_req->in.dh.in.b);
		अन्यथा
			अगर (!dma_mapping_error(dev, qat_req->in.dh.in.b))
				dma_unmap_single(dev, qat_req->in.dh.in.b,
						 ctx->p_size,
						 DMA_TO_DEVICE);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक qat_dh_check_params_length(अचिन्हित पूर्णांक p_len)
अणु
	चयन (p_len) अणु
	हाल 1536:
	हाल 2048:
	हाल 3072:
	हाल 4096:
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qat_dh_set_params(काष्ठा qat_dh_ctx *ctx, काष्ठा dh *params)
अणु
	काष्ठा qat_crypto_instance *inst = ctx->inst;
	काष्ठा device *dev = &GET_DEV(inst->accel_dev);

	अगर (qat_dh_check_params_length(params->p_size << 3))
		वापस -EINVAL;

	ctx->p_size = params->p_size;
	ctx->p = dma_alloc_coherent(dev, ctx->p_size, &ctx->dma_p, GFP_KERNEL);
	अगर (!ctx->p)
		वापस -ENOMEM;
	स_नकल(ctx->p, params->p, ctx->p_size);

	/* If g equals 2 करोn't copy it */
	अगर (params->g_size == 1 && *(अक्षर *)params->g == 0x02) अणु
		ctx->g2 = true;
		वापस 0;
	पूर्ण

	ctx->g = dma_alloc_coherent(dev, ctx->p_size, &ctx->dma_g, GFP_KERNEL);
	अगर (!ctx->g)
		वापस -ENOMEM;
	स_नकल(ctx->g + (ctx->p_size - params->g_size), params->g,
	       params->g_size);

	वापस 0;
पूर्ण

अटल व्योम qat_dh_clear_ctx(काष्ठा device *dev, काष्ठा qat_dh_ctx *ctx)
अणु
	अगर (ctx->g) अणु
		dma_मुक्त_coherent(dev, ctx->p_size, ctx->g, ctx->dma_g);
		ctx->g = शून्य;
	पूर्ण
	अगर (ctx->xa) अणु
		dma_मुक्त_coherent(dev, ctx->p_size, ctx->xa, ctx->dma_xa);
		ctx->xa = शून्य;
	पूर्ण
	अगर (ctx->p) अणु
		dma_मुक्त_coherent(dev, ctx->p_size, ctx->p, ctx->dma_p);
		ctx->p = शून्य;
	पूर्ण
	ctx->p_size = 0;
	ctx->g2 = false;
पूर्ण

अटल पूर्णांक qat_dh_set_secret(काष्ठा crypto_kpp *tfm, स्थिर व्योम *buf,
			     अचिन्हित पूर्णांक len)
अणु
	काष्ठा qat_dh_ctx *ctx = kpp_tfm_ctx(tfm);
	काष्ठा device *dev = &GET_DEV(ctx->inst->accel_dev);
	काष्ठा dh params;
	पूर्णांक ret;

	अगर (crypto_dh_decode_key(buf, len, &params) < 0)
		वापस -EINVAL;

	/* Free old secret अगर any */
	qat_dh_clear_ctx(dev, ctx);

	ret = qat_dh_set_params(ctx, &params);
	अगर (ret < 0)
		जाओ err_clear_ctx;

	ctx->xa = dma_alloc_coherent(dev, ctx->p_size, &ctx->dma_xa,
				     GFP_KERNEL);
	अगर (!ctx->xa) अणु
		ret = -ENOMEM;
		जाओ err_clear_ctx;
	पूर्ण
	स_नकल(ctx->xa + (ctx->p_size - params.key_size), params.key,
	       params.key_size);

	वापस 0;

err_clear_ctx:
	qat_dh_clear_ctx(dev, ctx);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक qat_dh_max_size(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा qat_dh_ctx *ctx = kpp_tfm_ctx(tfm);

	वापस ctx->p_size;
पूर्ण

अटल पूर्णांक qat_dh_init_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा qat_dh_ctx *ctx = kpp_tfm_ctx(tfm);
	काष्ठा qat_crypto_instance *inst =
			qat_crypto_get_instance_node(get_current_node());

	अगर (!inst)
		वापस -EINVAL;

	ctx->p_size = 0;
	ctx->g2 = false;
	ctx->inst = inst;
	वापस 0;
पूर्ण

अटल व्योम qat_dh_निकास_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा qat_dh_ctx *ctx = kpp_tfm_ctx(tfm);
	काष्ठा device *dev = &GET_DEV(ctx->inst->accel_dev);

	qat_dh_clear_ctx(dev, ctx);
	qat_crypto_put_instance(ctx->inst);
पूर्ण

अटल व्योम qat_rsa_cb(काष्ठा icp_qat_fw_pke_resp *resp)
अणु
	काष्ठा qat_asym_request *req = (व्योम *)(__क्रमce दीर्घ)resp->opaque;
	काष्ठा akcipher_request *areq = req->areq.rsa;
	काष्ठा device *dev = &GET_DEV(req->ctx.rsa->inst->accel_dev);
	पूर्णांक err = ICP_QAT_FW_PKE_RESP_PKE_STAT_GET(
				resp->pke_resp_hdr.comn_resp_flags);

	err = (err == ICP_QAT_FW_COMN_STATUS_FLAG_OK) ? 0 : -EINVAL;

	अगर (req->src_align)
		dma_मुक्त_coherent(dev, req->ctx.rsa->key_sz, req->src_align,
				  req->in.rsa.enc.m);
	अन्यथा
		dma_unmap_single(dev, req->in.rsa.enc.m, req->ctx.rsa->key_sz,
				 DMA_TO_DEVICE);

	areq->dst_len = req->ctx.rsa->key_sz;
	अगर (req->dst_align) अणु
		scatterwalk_map_and_copy(req->dst_align, areq->dst, 0,
					 areq->dst_len, 1);

		dma_मुक्त_coherent(dev, req->ctx.rsa->key_sz, req->dst_align,
				  req->out.rsa.enc.c);
	पूर्ण अन्यथा अणु
		dma_unmap_single(dev, req->out.rsa.enc.c, req->ctx.rsa->key_sz,
				 DMA_FROM_DEVICE);
	पूर्ण

	dma_unmap_single(dev, req->phy_in, माप(काष्ठा qat_rsa_input_params),
			 DMA_TO_DEVICE);
	dma_unmap_single(dev, req->phy_out,
			 माप(काष्ठा qat_rsa_output_params),
			 DMA_TO_DEVICE);

	akcipher_request_complete(areq, err);
पूर्ण

व्योम qat_alg_asym_callback(व्योम *_resp)
अणु
	काष्ठा icp_qat_fw_pke_resp *resp = _resp;
	काष्ठा qat_asym_request *areq = (व्योम *)(__क्रमce दीर्घ)resp->opaque;

	areq->cb(resp);
पूर्ण

#घोषणा PKE_RSA_EP_512 0x1c161b21
#घोषणा PKE_RSA_EP_1024 0x35111bf7
#घोषणा PKE_RSA_EP_1536 0x4d111cdc
#घोषणा PKE_RSA_EP_2048 0x6e111dba
#घोषणा PKE_RSA_EP_3072 0x7d111ea3
#घोषणा PKE_RSA_EP_4096 0xa5101f7e

अटल अचिन्हित दीर्घ qat_rsa_enc_fn_id(अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक bitslen = len << 3;

	चयन (bitslen) अणु
	हाल 512:
		वापस PKE_RSA_EP_512;
	हाल 1024:
		वापस PKE_RSA_EP_1024;
	हाल 1536:
		वापस PKE_RSA_EP_1536;
	हाल 2048:
		वापस PKE_RSA_EP_2048;
	हाल 3072:
		वापस PKE_RSA_EP_3072;
	हाल 4096:
		वापस PKE_RSA_EP_4096;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

#घोषणा PKE_RSA_DP1_512 0x1c161b3c
#घोषणा PKE_RSA_DP1_1024 0x35111c12
#घोषणा PKE_RSA_DP1_1536 0x4d111cf7
#घोषणा PKE_RSA_DP1_2048 0x6e111dda
#घोषणा PKE_RSA_DP1_3072 0x7d111ebe
#घोषणा PKE_RSA_DP1_4096 0xa5101f98

अटल अचिन्हित दीर्घ qat_rsa_dec_fn_id(अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक bitslen = len << 3;

	चयन (bitslen) अणु
	हाल 512:
		वापस PKE_RSA_DP1_512;
	हाल 1024:
		वापस PKE_RSA_DP1_1024;
	हाल 1536:
		वापस PKE_RSA_DP1_1536;
	हाल 2048:
		वापस PKE_RSA_DP1_2048;
	हाल 3072:
		वापस PKE_RSA_DP1_3072;
	हाल 4096:
		वापस PKE_RSA_DP1_4096;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

#घोषणा PKE_RSA_DP2_512 0x1c131b57
#घोषणा PKE_RSA_DP2_1024 0x26131c2d
#घोषणा PKE_RSA_DP2_1536 0x45111d12
#घोषणा PKE_RSA_DP2_2048 0x59121dfa
#घोषणा PKE_RSA_DP2_3072 0x81121ed9
#घोषणा PKE_RSA_DP2_4096 0xb1111fb2

अटल अचिन्हित दीर्घ qat_rsa_dec_fn_id_crt(अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक bitslen = len << 3;

	चयन (bitslen) अणु
	हाल 512:
		वापस PKE_RSA_DP2_512;
	हाल 1024:
		वापस PKE_RSA_DP2_1024;
	हाल 1536:
		वापस PKE_RSA_DP2_1536;
	हाल 2048:
		वापस PKE_RSA_DP2_2048;
	हाल 3072:
		वापस PKE_RSA_DP2_3072;
	हाल 4096:
		वापस PKE_RSA_DP2_4096;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक qat_rsa_enc(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा qat_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा qat_crypto_instance *inst = ctx->inst;
	काष्ठा device *dev = &GET_DEV(inst->accel_dev);
	काष्ठा qat_asym_request *qat_req =
			PTR_ALIGN(akcipher_request_ctx(req), 64);
	काष्ठा icp_qat_fw_pke_request *msg = &qat_req->req;
	पूर्णांक ret, ctr = 0;

	अगर (unlikely(!ctx->n || !ctx->e))
		वापस -EINVAL;

	अगर (req->dst_len < ctx->key_sz) अणु
		req->dst_len = ctx->key_sz;
		वापस -EOVERFLOW;
	पूर्ण
	स_रखो(msg, '\0', माप(*msg));
	ICP_QAT_FW_PKE_HDR_VALID_FLAG_SET(msg->pke_hdr,
					  ICP_QAT_FW_COMN_REQ_FLAG_SET);
	msg->pke_hdr.cd_pars.func_id = qat_rsa_enc_fn_id(ctx->key_sz);
	अगर (unlikely(!msg->pke_hdr.cd_pars.func_id))
		वापस -EINVAL;

	qat_req->cb = qat_rsa_cb;
	qat_req->ctx.rsa = ctx;
	qat_req->areq.rsa = req;
	msg->pke_hdr.service_type = ICP_QAT_FW_COMN_REQ_CPM_FW_PKE;
	msg->pke_hdr.comn_req_flags =
		ICP_QAT_FW_COMN_FLAGS_BUILD(QAT_COMN_PTR_TYPE_FLAT,
					    QAT_COMN_CD_FLD_TYPE_64BIT_ADR);

	qat_req->in.rsa.enc.e = ctx->dma_e;
	qat_req->in.rsa.enc.n = ctx->dma_n;
	ret = -ENOMEM;

	/*
	 * src can be of any size in valid range, but HW expects it to be the
	 * same as modulo n so in हाल it is dअगरferent we need to allocate a
	 * new buf and copy src data.
	 * In other हाल we just need to map the user provided buffer.
	 * Also need to make sure that it is in contiguous buffer.
	 */
	अगर (sg_is_last(req->src) && req->src_len == ctx->key_sz) अणु
		qat_req->src_align = शून्य;
		qat_req->in.rsa.enc.m = dma_map_single(dev, sg_virt(req->src),
						   req->src_len, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(dev, qat_req->in.rsa.enc.m)))
			वापस ret;

	पूर्ण अन्यथा अणु
		पूर्णांक shअगरt = ctx->key_sz - req->src_len;

		qat_req->src_align = dma_alloc_coherent(dev, ctx->key_sz,
							&qat_req->in.rsa.enc.m,
							GFP_KERNEL);
		अगर (unlikely(!qat_req->src_align))
			वापस ret;

		scatterwalk_map_and_copy(qat_req->src_align + shअगरt, req->src,
					 0, req->src_len, 0);
	पूर्ण
	अगर (sg_is_last(req->dst) && req->dst_len == ctx->key_sz) अणु
		qat_req->dst_align = शून्य;
		qat_req->out.rsa.enc.c = dma_map_single(dev, sg_virt(req->dst),
							req->dst_len,
							DMA_FROM_DEVICE);

		अगर (unlikely(dma_mapping_error(dev, qat_req->out.rsa.enc.c)))
			जाओ unmap_src;

	पूर्ण अन्यथा अणु
		qat_req->dst_align = dma_alloc_coherent(dev, ctx->key_sz,
							&qat_req->out.rsa.enc.c,
							GFP_KERNEL);
		अगर (unlikely(!qat_req->dst_align))
			जाओ unmap_src;

	पूर्ण
	qat_req->in.rsa.in_tab[3] = 0;
	qat_req->out.rsa.out_tab[1] = 0;
	qat_req->phy_in = dma_map_single(dev, &qat_req->in.rsa.enc.m,
					 माप(qat_req->in.rsa.enc.m),
					 DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, qat_req->phy_in)))
		जाओ unmap_dst;

	qat_req->phy_out = dma_map_single(dev, &qat_req->out.rsa.enc.c,
					  माप(qat_req->out.rsa.enc.c),
					  DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, qat_req->phy_out)))
		जाओ unmap_in_params;

	msg->pke_mid.src_data_addr = qat_req->phy_in;
	msg->pke_mid.dest_data_addr = qat_req->phy_out;
	msg->pke_mid.opaque = (u64)(__क्रमce दीर्घ)qat_req;
	msg->input_param_count = 3;
	msg->output_param_count = 1;
	करो अणु
		ret = adf_send_message(ctx->inst->pke_tx, (u32 *)msg);
	पूर्ण जबतक (ret == -EBUSY && ctr++ < 100);

	अगर (!ret)
		वापस -EINPROGRESS;

	अगर (!dma_mapping_error(dev, qat_req->phy_out))
		dma_unmap_single(dev, qat_req->phy_out,
				 माप(काष्ठा qat_rsa_output_params),
				 DMA_TO_DEVICE);
unmap_in_params:
	अगर (!dma_mapping_error(dev, qat_req->phy_in))
		dma_unmap_single(dev, qat_req->phy_in,
				 माप(काष्ठा qat_rsa_input_params),
				 DMA_TO_DEVICE);
unmap_dst:
	अगर (qat_req->dst_align)
		dma_मुक्त_coherent(dev, ctx->key_sz, qat_req->dst_align,
				  qat_req->out.rsa.enc.c);
	अन्यथा
		अगर (!dma_mapping_error(dev, qat_req->out.rsa.enc.c))
			dma_unmap_single(dev, qat_req->out.rsa.enc.c,
					 ctx->key_sz, DMA_FROM_DEVICE);
unmap_src:
	अगर (qat_req->src_align)
		dma_मुक्त_coherent(dev, ctx->key_sz, qat_req->src_align,
				  qat_req->in.rsa.enc.m);
	अन्यथा
		अगर (!dma_mapping_error(dev, qat_req->in.rsa.enc.m))
			dma_unmap_single(dev, qat_req->in.rsa.enc.m,
					 ctx->key_sz, DMA_TO_DEVICE);
	वापस ret;
पूर्ण

अटल पूर्णांक qat_rsa_dec(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा qat_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा qat_crypto_instance *inst = ctx->inst;
	काष्ठा device *dev = &GET_DEV(inst->accel_dev);
	काष्ठा qat_asym_request *qat_req =
			PTR_ALIGN(akcipher_request_ctx(req), 64);
	काष्ठा icp_qat_fw_pke_request *msg = &qat_req->req;
	पूर्णांक ret, ctr = 0;

	अगर (unlikely(!ctx->n || !ctx->d))
		वापस -EINVAL;

	अगर (req->dst_len < ctx->key_sz) अणु
		req->dst_len = ctx->key_sz;
		वापस -EOVERFLOW;
	पूर्ण
	स_रखो(msg, '\0', माप(*msg));
	ICP_QAT_FW_PKE_HDR_VALID_FLAG_SET(msg->pke_hdr,
					  ICP_QAT_FW_COMN_REQ_FLAG_SET);
	msg->pke_hdr.cd_pars.func_id = ctx->crt_mode ?
		qat_rsa_dec_fn_id_crt(ctx->key_sz) :
		qat_rsa_dec_fn_id(ctx->key_sz);
	अगर (unlikely(!msg->pke_hdr.cd_pars.func_id))
		वापस -EINVAL;

	qat_req->cb = qat_rsa_cb;
	qat_req->ctx.rsa = ctx;
	qat_req->areq.rsa = req;
	msg->pke_hdr.service_type = ICP_QAT_FW_COMN_REQ_CPM_FW_PKE;
	msg->pke_hdr.comn_req_flags =
		ICP_QAT_FW_COMN_FLAGS_BUILD(QAT_COMN_PTR_TYPE_FLAT,
					    QAT_COMN_CD_FLD_TYPE_64BIT_ADR);

	अगर (ctx->crt_mode) अणु
		qat_req->in.rsa.dec_crt.p = ctx->dma_p;
		qat_req->in.rsa.dec_crt.q = ctx->dma_q;
		qat_req->in.rsa.dec_crt.dp = ctx->dma_dp;
		qat_req->in.rsa.dec_crt.dq = ctx->dma_dq;
		qat_req->in.rsa.dec_crt.qinv = ctx->dma_qinv;
	पूर्ण अन्यथा अणु
		qat_req->in.rsa.dec.d = ctx->dma_d;
		qat_req->in.rsa.dec.n = ctx->dma_n;
	पूर्ण
	ret = -ENOMEM;

	/*
	 * src can be of any size in valid range, but HW expects it to be the
	 * same as modulo n so in हाल it is dअगरferent we need to allocate a
	 * new buf and copy src data.
	 * In other हाल we just need to map the user provided buffer.
	 * Also need to make sure that it is in contiguous buffer.
	 */
	अगर (sg_is_last(req->src) && req->src_len == ctx->key_sz) अणु
		qat_req->src_align = शून्य;
		qat_req->in.rsa.dec.c = dma_map_single(dev, sg_virt(req->src),
						   req->dst_len, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(dev, qat_req->in.rsa.dec.c)))
			वापस ret;

	पूर्ण अन्यथा अणु
		पूर्णांक shअगरt = ctx->key_sz - req->src_len;

		qat_req->src_align = dma_alloc_coherent(dev, ctx->key_sz,
							&qat_req->in.rsa.dec.c,
							GFP_KERNEL);
		अगर (unlikely(!qat_req->src_align))
			वापस ret;

		scatterwalk_map_and_copy(qat_req->src_align + shअगरt, req->src,
					 0, req->src_len, 0);
	पूर्ण
	अगर (sg_is_last(req->dst) && req->dst_len == ctx->key_sz) अणु
		qat_req->dst_align = शून्य;
		qat_req->out.rsa.dec.m = dma_map_single(dev, sg_virt(req->dst),
						    req->dst_len,
						    DMA_FROM_DEVICE);

		अगर (unlikely(dma_mapping_error(dev, qat_req->out.rsa.dec.m)))
			जाओ unmap_src;

	पूर्ण अन्यथा अणु
		qat_req->dst_align = dma_alloc_coherent(dev, ctx->key_sz,
							&qat_req->out.rsa.dec.m,
							GFP_KERNEL);
		अगर (unlikely(!qat_req->dst_align))
			जाओ unmap_src;

	पूर्ण

	अगर (ctx->crt_mode)
		qat_req->in.rsa.in_tab[6] = 0;
	अन्यथा
		qat_req->in.rsa.in_tab[3] = 0;
	qat_req->out.rsa.out_tab[1] = 0;
	qat_req->phy_in = dma_map_single(dev, &qat_req->in.rsa.dec.c,
					 माप(qat_req->in.rsa.dec.c),
					 DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, qat_req->phy_in)))
		जाओ unmap_dst;

	qat_req->phy_out = dma_map_single(dev, &qat_req->out.rsa.dec.m,
					  माप(qat_req->out.rsa.dec.m),
					  DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, qat_req->phy_out)))
		जाओ unmap_in_params;

	msg->pke_mid.src_data_addr = qat_req->phy_in;
	msg->pke_mid.dest_data_addr = qat_req->phy_out;
	msg->pke_mid.opaque = (u64)(__क्रमce दीर्घ)qat_req;
	अगर (ctx->crt_mode)
		msg->input_param_count = 6;
	अन्यथा
		msg->input_param_count = 3;

	msg->output_param_count = 1;
	करो अणु
		ret = adf_send_message(ctx->inst->pke_tx, (u32 *)msg);
	पूर्ण जबतक (ret == -EBUSY && ctr++ < 100);

	अगर (!ret)
		वापस -EINPROGRESS;

	अगर (!dma_mapping_error(dev, qat_req->phy_out))
		dma_unmap_single(dev, qat_req->phy_out,
				 माप(काष्ठा qat_rsa_output_params),
				 DMA_TO_DEVICE);
unmap_in_params:
	अगर (!dma_mapping_error(dev, qat_req->phy_in))
		dma_unmap_single(dev, qat_req->phy_in,
				 माप(काष्ठा qat_rsa_input_params),
				 DMA_TO_DEVICE);
unmap_dst:
	अगर (qat_req->dst_align)
		dma_मुक्त_coherent(dev, ctx->key_sz, qat_req->dst_align,
				  qat_req->out.rsa.dec.m);
	अन्यथा
		अगर (!dma_mapping_error(dev, qat_req->out.rsa.dec.m))
			dma_unmap_single(dev, qat_req->out.rsa.dec.m,
					 ctx->key_sz, DMA_FROM_DEVICE);
unmap_src:
	अगर (qat_req->src_align)
		dma_मुक्त_coherent(dev, ctx->key_sz, qat_req->src_align,
				  qat_req->in.rsa.dec.c);
	अन्यथा
		अगर (!dma_mapping_error(dev, qat_req->in.rsa.dec.c))
			dma_unmap_single(dev, qat_req->in.rsa.dec.c,
					 ctx->key_sz, DMA_TO_DEVICE);
	वापस ret;
पूर्ण

अटल पूर्णांक qat_rsa_set_n(काष्ठा qat_rsa_ctx *ctx, स्थिर अक्षर *value,
			 माप_प्रकार vlen)
अणु
	काष्ठा qat_crypto_instance *inst = ctx->inst;
	काष्ठा device *dev = &GET_DEV(inst->accel_dev);
	स्थिर अक्षर *ptr = value;
	पूर्णांक ret;

	जबतक (!*ptr && vlen) अणु
		ptr++;
		vlen--;
	पूर्ण

	ctx->key_sz = vlen;
	ret = -EINVAL;
	/* invalid key size provided */
	अगर (!qat_rsa_enc_fn_id(ctx->key_sz))
		जाओ err;

	ret = -ENOMEM;
	ctx->n = dma_alloc_coherent(dev, ctx->key_sz, &ctx->dma_n, GFP_KERNEL);
	अगर (!ctx->n)
		जाओ err;

	स_नकल(ctx->n, ptr, ctx->key_sz);
	वापस 0;
err:
	ctx->key_sz = 0;
	ctx->n = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक qat_rsa_set_e(काष्ठा qat_rsa_ctx *ctx, स्थिर अक्षर *value,
			 माप_प्रकार vlen)
अणु
	काष्ठा qat_crypto_instance *inst = ctx->inst;
	काष्ठा device *dev = &GET_DEV(inst->accel_dev);
	स्थिर अक्षर *ptr = value;

	जबतक (!*ptr && vlen) अणु
		ptr++;
		vlen--;
	पूर्ण

	अगर (!ctx->key_sz || !vlen || vlen > ctx->key_sz) अणु
		ctx->e = शून्य;
		वापस -EINVAL;
	पूर्ण

	ctx->e = dma_alloc_coherent(dev, ctx->key_sz, &ctx->dma_e, GFP_KERNEL);
	अगर (!ctx->e)
		वापस -ENOMEM;

	स_नकल(ctx->e + (ctx->key_sz - vlen), ptr, vlen);
	वापस 0;
पूर्ण

अटल पूर्णांक qat_rsa_set_d(काष्ठा qat_rsa_ctx *ctx, स्थिर अक्षर *value,
			 माप_प्रकार vlen)
अणु
	काष्ठा qat_crypto_instance *inst = ctx->inst;
	काष्ठा device *dev = &GET_DEV(inst->accel_dev);
	स्थिर अक्षर *ptr = value;
	पूर्णांक ret;

	जबतक (!*ptr && vlen) अणु
		ptr++;
		vlen--;
	पूर्ण

	ret = -EINVAL;
	अगर (!ctx->key_sz || !vlen || vlen > ctx->key_sz)
		जाओ err;

	ret = -ENOMEM;
	ctx->d = dma_alloc_coherent(dev, ctx->key_sz, &ctx->dma_d, GFP_KERNEL);
	अगर (!ctx->d)
		जाओ err;

	स_नकल(ctx->d + (ctx->key_sz - vlen), ptr, vlen);
	वापस 0;
err:
	ctx->d = शून्य;
	वापस ret;
पूर्ण

अटल व्योम qat_rsa_drop_leading_zeros(स्थिर अक्षर **ptr, अचिन्हित पूर्णांक *len)
अणु
	जबतक (!**ptr && *len) अणु
		(*ptr)++;
		(*len)--;
	पूर्ण
पूर्ण

अटल व्योम qat_rsa_setkey_crt(काष्ठा qat_rsa_ctx *ctx, काष्ठा rsa_key *rsa_key)
अणु
	काष्ठा qat_crypto_instance *inst = ctx->inst;
	काष्ठा device *dev = &GET_DEV(inst->accel_dev);
	स्थिर अक्षर *ptr;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक half_key_sz = ctx->key_sz / 2;

	/* p */
	ptr = rsa_key->p;
	len = rsa_key->p_sz;
	qat_rsa_drop_leading_zeros(&ptr, &len);
	अगर (!len)
		जाओ err;
	ctx->p = dma_alloc_coherent(dev, half_key_sz, &ctx->dma_p, GFP_KERNEL);
	अगर (!ctx->p)
		जाओ err;
	स_नकल(ctx->p + (half_key_sz - len), ptr, len);

	/* q */
	ptr = rsa_key->q;
	len = rsa_key->q_sz;
	qat_rsa_drop_leading_zeros(&ptr, &len);
	अगर (!len)
		जाओ मुक्त_p;
	ctx->q = dma_alloc_coherent(dev, half_key_sz, &ctx->dma_q, GFP_KERNEL);
	अगर (!ctx->q)
		जाओ मुक्त_p;
	स_नकल(ctx->q + (half_key_sz - len), ptr, len);

	/* dp */
	ptr = rsa_key->dp;
	len = rsa_key->dp_sz;
	qat_rsa_drop_leading_zeros(&ptr, &len);
	अगर (!len)
		जाओ मुक्त_q;
	ctx->dp = dma_alloc_coherent(dev, half_key_sz, &ctx->dma_dp,
				     GFP_KERNEL);
	अगर (!ctx->dp)
		जाओ मुक्त_q;
	स_नकल(ctx->dp + (half_key_sz - len), ptr, len);

	/* dq */
	ptr = rsa_key->dq;
	len = rsa_key->dq_sz;
	qat_rsa_drop_leading_zeros(&ptr, &len);
	अगर (!len)
		जाओ मुक्त_dp;
	ctx->dq = dma_alloc_coherent(dev, half_key_sz, &ctx->dma_dq,
				     GFP_KERNEL);
	अगर (!ctx->dq)
		जाओ मुक्त_dp;
	स_नकल(ctx->dq + (half_key_sz - len), ptr, len);

	/* qinv */
	ptr = rsa_key->qinv;
	len = rsa_key->qinv_sz;
	qat_rsa_drop_leading_zeros(&ptr, &len);
	अगर (!len)
		जाओ मुक्त_dq;
	ctx->qinv = dma_alloc_coherent(dev, half_key_sz, &ctx->dma_qinv,
				       GFP_KERNEL);
	अगर (!ctx->qinv)
		जाओ मुक्त_dq;
	स_नकल(ctx->qinv + (half_key_sz - len), ptr, len);

	ctx->crt_mode = true;
	वापस;

मुक्त_dq:
	स_रखो(ctx->dq, '\0', half_key_sz);
	dma_मुक्त_coherent(dev, half_key_sz, ctx->dq, ctx->dma_dq);
	ctx->dq = शून्य;
मुक्त_dp:
	स_रखो(ctx->dp, '\0', half_key_sz);
	dma_मुक्त_coherent(dev, half_key_sz, ctx->dp, ctx->dma_dp);
	ctx->dp = शून्य;
मुक्त_q:
	स_रखो(ctx->q, '\0', half_key_sz);
	dma_मुक्त_coherent(dev, half_key_sz, ctx->q, ctx->dma_q);
	ctx->q = शून्य;
मुक्त_p:
	स_रखो(ctx->p, '\0', half_key_sz);
	dma_मुक्त_coherent(dev, half_key_sz, ctx->p, ctx->dma_p);
	ctx->p = शून्य;
err:
	ctx->crt_mode = false;
पूर्ण

अटल व्योम qat_rsa_clear_ctx(काष्ठा device *dev, काष्ठा qat_rsa_ctx *ctx)
अणु
	अचिन्हित पूर्णांक half_key_sz = ctx->key_sz / 2;

	/* Free the old key अगर any */
	अगर (ctx->n)
		dma_मुक्त_coherent(dev, ctx->key_sz, ctx->n, ctx->dma_n);
	अगर (ctx->e)
		dma_मुक्त_coherent(dev, ctx->key_sz, ctx->e, ctx->dma_e);
	अगर (ctx->d) अणु
		स_रखो(ctx->d, '\0', ctx->key_sz);
		dma_मुक्त_coherent(dev, ctx->key_sz, ctx->d, ctx->dma_d);
	पूर्ण
	अगर (ctx->p) अणु
		स_रखो(ctx->p, '\0', half_key_sz);
		dma_मुक्त_coherent(dev, half_key_sz, ctx->p, ctx->dma_p);
	पूर्ण
	अगर (ctx->q) अणु
		स_रखो(ctx->q, '\0', half_key_sz);
		dma_मुक्त_coherent(dev, half_key_sz, ctx->q, ctx->dma_q);
	पूर्ण
	अगर (ctx->dp) अणु
		स_रखो(ctx->dp, '\0', half_key_sz);
		dma_मुक्त_coherent(dev, half_key_sz, ctx->dp, ctx->dma_dp);
	पूर्ण
	अगर (ctx->dq) अणु
		स_रखो(ctx->dq, '\0', half_key_sz);
		dma_मुक्त_coherent(dev, half_key_sz, ctx->dq, ctx->dma_dq);
	पूर्ण
	अगर (ctx->qinv) अणु
		स_रखो(ctx->qinv, '\0', half_key_sz);
		dma_मुक्त_coherent(dev, half_key_sz, ctx->qinv, ctx->dma_qinv);
	पूर्ण

	ctx->n = शून्य;
	ctx->e = शून्य;
	ctx->d = शून्य;
	ctx->p = शून्य;
	ctx->q = शून्य;
	ctx->dp = शून्य;
	ctx->dq = शून्य;
	ctx->qinv = शून्य;
	ctx->crt_mode = false;
	ctx->key_sz = 0;
पूर्ण

अटल पूर्णांक qat_rsa_setkey(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			  अचिन्हित पूर्णांक keylen, bool निजी)
अणु
	काष्ठा qat_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा device *dev = &GET_DEV(ctx->inst->accel_dev);
	काष्ठा rsa_key rsa_key;
	पूर्णांक ret;

	qat_rsa_clear_ctx(dev, ctx);

	अगर (निजी)
		ret = rsa_parse_priv_key(&rsa_key, key, keylen);
	अन्यथा
		ret = rsa_parse_pub_key(&rsa_key, key, keylen);
	अगर (ret < 0)
		जाओ मुक्त;

	ret = qat_rsa_set_n(ctx, rsa_key.n, rsa_key.n_sz);
	अगर (ret < 0)
		जाओ मुक्त;
	ret = qat_rsa_set_e(ctx, rsa_key.e, rsa_key.e_sz);
	अगर (ret < 0)
		जाओ मुक्त;
	अगर (निजी) अणु
		ret = qat_rsa_set_d(ctx, rsa_key.d, rsa_key.d_sz);
		अगर (ret < 0)
			जाओ मुक्त;
		qat_rsa_setkey_crt(ctx, &rsa_key);
	पूर्ण

	अगर (!ctx->n || !ctx->e) अणु
		/* invalid key provided */
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण
	अगर (निजी && !ctx->d) अणु
		/* invalid निजी key provided */
		ret = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	वापस 0;
मुक्त:
	qat_rsa_clear_ctx(dev, ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक qat_rsa_setpubkey(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	वापस qat_rsa_setkey(tfm, key, keylen, false);
पूर्ण

अटल पूर्णांक qat_rsa_setprivkey(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			      अचिन्हित पूर्णांक keylen)
अणु
	वापस qat_rsa_setkey(tfm, key, keylen, true);
पूर्ण

अटल अचिन्हित पूर्णांक qat_rsa_max_size(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा qat_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);

	वापस ctx->key_sz;
पूर्ण

अटल पूर्णांक qat_rsa_init_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा qat_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा qat_crypto_instance *inst =
			qat_crypto_get_instance_node(get_current_node());

	अगर (!inst)
		वापस -EINVAL;

	ctx->key_sz = 0;
	ctx->inst = inst;
	वापस 0;
पूर्ण

अटल व्योम qat_rsa_निकास_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा qat_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	काष्ठा device *dev = &GET_DEV(ctx->inst->accel_dev);

	अगर (ctx->n)
		dma_मुक्त_coherent(dev, ctx->key_sz, ctx->n, ctx->dma_n);
	अगर (ctx->e)
		dma_मुक्त_coherent(dev, ctx->key_sz, ctx->e, ctx->dma_e);
	अगर (ctx->d) अणु
		स_रखो(ctx->d, '\0', ctx->key_sz);
		dma_मुक्त_coherent(dev, ctx->key_sz, ctx->d, ctx->dma_d);
	पूर्ण
	qat_crypto_put_instance(ctx->inst);
	ctx->n = शून्य;
	ctx->e = शून्य;
	ctx->d = शून्य;
पूर्ण

अटल काष्ठा akcipher_alg rsa = अणु
	.encrypt = qat_rsa_enc,
	.decrypt = qat_rsa_dec,
	.set_pub_key = qat_rsa_setpubkey,
	.set_priv_key = qat_rsa_setprivkey,
	.max_size = qat_rsa_max_size,
	.init = qat_rsa_init_tfm,
	.निकास = qat_rsa_निकास_tfm,
	.reqsize = माप(काष्ठा qat_asym_request) + 64,
	.base = अणु
		.cra_name = "rsa",
		.cra_driver_name = "qat-rsa",
		.cra_priority = 1000,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = माप(काष्ठा qat_rsa_ctx),
	पूर्ण,
पूर्ण;

अटल काष्ठा kpp_alg dh = अणु
	.set_secret = qat_dh_set_secret,
	.generate_खुला_key = qat_dh_compute_value,
	.compute_shared_secret = qat_dh_compute_value,
	.max_size = qat_dh_max_size,
	.init = qat_dh_init_tfm,
	.निकास = qat_dh_निकास_tfm,
	.reqsize = माप(काष्ठा qat_asym_request) + 64,
	.base = अणु
		.cra_name = "dh",
		.cra_driver_name = "qat-dh",
		.cra_priority = 1000,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = माप(काष्ठा qat_dh_ctx),
	पूर्ण,
पूर्ण;

पूर्णांक qat_asym_algs_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&algs_lock);
	अगर (++active_devs == 1) अणु
		rsa.base.cra_flags = 0;
		ret = crypto_रेजिस्टर_akcipher(&rsa);
		अगर (ret)
			जाओ unlock;
		ret = crypto_रेजिस्टर_kpp(&dh);
	पूर्ण
unlock:
	mutex_unlock(&algs_lock);
	वापस ret;
पूर्ण

व्योम qat_asym_algs_unरेजिस्टर(व्योम)
अणु
	mutex_lock(&algs_lock);
	अगर (--active_devs == 0) अणु
		crypto_unरेजिस्टर_akcipher(&rsa);
		crypto_unरेजिस्टर_kpp(&dh);
	पूर्ण
	mutex_unlock(&algs_lock);
पूर्ण
