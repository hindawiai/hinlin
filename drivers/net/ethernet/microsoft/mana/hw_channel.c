<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2021, Microsoft Corporation. */

#समावेश "gdma.h"
#समावेश "hw_channel.h"

अटल पूर्णांक mana_hwc_get_msg_index(काष्ठा hw_channel_context *hwc, u16 *msg_id)
अणु
	काष्ठा gdma_resource *r = &hwc->inflight_msg_res;
	अचिन्हित दीर्घ flags;
	u32 index;

	करोwn(&hwc->sema);

	spin_lock_irqsave(&r->lock, flags);

	index = find_first_zero_bit(hwc->inflight_msg_res.map,
				    hwc->inflight_msg_res.size);

	biपंचांगap_set(hwc->inflight_msg_res.map, index, 1);

	spin_unlock_irqrestore(&r->lock, flags);

	*msg_id = index;

	वापस 0;
पूर्ण

अटल व्योम mana_hwc_put_msg_index(काष्ठा hw_channel_context *hwc, u16 msg_id)
अणु
	काष्ठा gdma_resource *r = &hwc->inflight_msg_res;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&r->lock, flags);
	biपंचांगap_clear(hwc->inflight_msg_res.map, msg_id, 1);
	spin_unlock_irqrestore(&r->lock, flags);

	up(&hwc->sema);
पूर्ण

अटल पूर्णांक mana_hwc_verअगरy_resp_msg(स्थिर काष्ठा hwc_caller_ctx *caller_ctx,
				    स्थिर काष्ठा gdma_resp_hdr *resp_msg,
				    u32 resp_len)
अणु
	अगर (resp_len < माप(*resp_msg))
		वापस -EPROTO;

	अगर (resp_len > caller_ctx->output_buflen)
		वापस -EPROTO;

	वापस 0;
पूर्ण

अटल व्योम mana_hwc_handle_resp(काष्ठा hw_channel_context *hwc, u32 resp_len,
				 स्थिर काष्ठा gdma_resp_hdr *resp_msg)
अणु
	काष्ठा hwc_caller_ctx *ctx;
	पूर्णांक err;

	अगर (!test_bit(resp_msg->response.hwc_msg_id,
		      hwc->inflight_msg_res.map)) अणु
		dev_err(hwc->dev, "hwc_rx: invalid msg_id = %u\n",
			resp_msg->response.hwc_msg_id);
		वापस;
	पूर्ण

	ctx = hwc->caller_ctx + resp_msg->response.hwc_msg_id;
	err = mana_hwc_verअगरy_resp_msg(ctx, resp_msg, resp_len);
	अगर (err)
		जाओ out;

	ctx->status_code = resp_msg->status;

	स_नकल(ctx->output_buf, resp_msg, resp_len);
out:
	ctx->error = err;
	complete(&ctx->comp_event);
पूर्ण

अटल पूर्णांक mana_hwc_post_rx_wqe(स्थिर काष्ठा hwc_wq *hwc_rxq,
				काष्ठा hwc_work_request *req)
अणु
	काष्ठा device *dev = hwc_rxq->hwc->dev;
	काष्ठा gdma_sge *sge;
	पूर्णांक err;

	sge = &req->sge;
	sge->address = (u64)req->buf_sge_addr;
	sge->mem_key = hwc_rxq->msg_buf->gpa_mkey;
	sge->size = req->buf_len;

	स_रखो(&req->wqe_req, 0, माप(काष्ठा gdma_wqe_request));
	req->wqe_req.sgl = sge;
	req->wqe_req.num_sge = 1;
	req->wqe_req.client_data_unit = 0;

	err = mana_gd_post_and_ring(hwc_rxq->gdma_wq, &req->wqe_req, शून्य);
	अगर (err)
		dev_err(dev, "Failed to post WQE on HWC RQ: %d\n", err);
	वापस err;
पूर्ण

अटल व्योम mana_hwc_init_event_handler(व्योम *ctx, काष्ठा gdma_queue *q_self,
					काष्ठा gdma_event *event)
अणु
	काष्ठा hw_channel_context *hwc = ctx;
	काष्ठा gdma_dev *gd = hwc->gdma_dev;
	जोड़ hwc_init_type_data type_data;
	जोड़ hwc_init_eq_id_db eq_db;
	u32 type, val;

	चयन (event->type) अणु
	हाल GDMA_EQE_HWC_INIT_EQ_ID_DB:
		eq_db.as_uपूर्णांक32 = event->details[0];
		hwc->cq->gdma_eq->id = eq_db.eq_id;
		gd->करोorbell = eq_db.करोorbell;
		अवरोध;

	हाल GDMA_EQE_HWC_INIT_DATA:
		type_data.as_uपूर्णांक32 = event->details[0];
		type = type_data.type;
		val = type_data.value;

		चयन (type) अणु
		हाल HWC_INIT_DATA_CQID:
			hwc->cq->gdma_cq->id = val;
			अवरोध;

		हाल HWC_INIT_DATA_RQID:
			hwc->rxq->gdma_wq->id = val;
			अवरोध;

		हाल HWC_INIT_DATA_SQID:
			hwc->txq->gdma_wq->id = val;
			अवरोध;

		हाल HWC_INIT_DATA_QUEUE_DEPTH:
			hwc->hwc_init_q_depth_max = (u16)val;
			अवरोध;

		हाल HWC_INIT_DATA_MAX_REQUEST:
			hwc->hwc_init_max_req_msg_size = val;
			अवरोध;

		हाल HWC_INIT_DATA_MAX_RESPONSE:
			hwc->hwc_init_max_resp_msg_size = val;
			अवरोध;

		हाल HWC_INIT_DATA_MAX_NUM_CQS:
			gd->gdma_context->max_num_cqs = val;
			अवरोध;

		हाल HWC_INIT_DATA_PDID:
			hwc->gdma_dev->pdid = val;
			अवरोध;

		हाल HWC_INIT_DATA_GPA_MKEY:
			hwc->rxq->msg_buf->gpa_mkey = val;
			hwc->txq->msg_buf->gpa_mkey = val;
			अवरोध;
		पूर्ण

		अवरोध;

	हाल GDMA_EQE_HWC_INIT_DONE:
		complete(&hwc->hwc_init_eqe_comp);
		अवरोध;

	शेष:
		/* Ignore unknown events, which should never happen. */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mana_hwc_rx_event_handler(व्योम *ctx, u32 gdma_rxq_id,
				      स्थिर काष्ठा hwc_rx_oob *rx_oob)
अणु
	काष्ठा hw_channel_context *hwc = ctx;
	काष्ठा hwc_wq *hwc_rxq = hwc->rxq;
	काष्ठा hwc_work_request *rx_req;
	काष्ठा gdma_resp_hdr *resp;
	काष्ठा gdma_wqe *dma_oob;
	काष्ठा gdma_queue *rq;
	काष्ठा gdma_sge *sge;
	u64 rq_base_addr;
	u64 rx_req_idx;
	u8 *wqe;

	अगर (WARN_ON_ONCE(hwc_rxq->gdma_wq->id != gdma_rxq_id))
		वापस;

	rq = hwc_rxq->gdma_wq;
	wqe = mana_gd_get_wqe_ptr(rq, rx_oob->wqe_offset / GDMA_WQE_BU_SIZE);
	dma_oob = (काष्ठा gdma_wqe *)wqe;

	sge = (काष्ठा gdma_sge *)(wqe + 8 + dma_oob->अंतरभूत_oob_size_भाग4 * 4);

	/* Select the RX work request क्रम भव address and क्रम reposting. */
	rq_base_addr = hwc_rxq->msg_buf->mem_info.dma_handle;
	rx_req_idx = (sge->address - rq_base_addr) / hwc->max_req_msg_size;

	rx_req = &hwc_rxq->msg_buf->reqs[rx_req_idx];
	resp = (काष्ठा gdma_resp_hdr *)rx_req->buf_va;

	अगर (resp->response.hwc_msg_id >= hwc->num_inflight_msg) अणु
		dev_err(hwc->dev, "HWC RX: wrong msg_id=%u\n",
			resp->response.hwc_msg_id);
		वापस;
	पूर्ण

	mana_hwc_handle_resp(hwc, rx_oob->tx_oob_data_size, resp);

	/* Do no दीर्घer use 'resp', because the buffer is posted to the HW
	 * in the below mana_hwc_post_rx_wqe().
	 */
	resp = शून्य;

	mana_hwc_post_rx_wqe(hwc_rxq, rx_req);
पूर्ण

अटल व्योम mana_hwc_tx_event_handler(व्योम *ctx, u32 gdma_txq_id,
				      स्थिर काष्ठा hwc_rx_oob *rx_oob)
अणु
	काष्ठा hw_channel_context *hwc = ctx;
	काष्ठा hwc_wq *hwc_txq = hwc->txq;

	WARN_ON_ONCE(!hwc_txq || hwc_txq->gdma_wq->id != gdma_txq_id);
पूर्ण

अटल पूर्णांक mana_hwc_create_gdma_wq(काष्ठा hw_channel_context *hwc,
				   क्रमागत gdma_queue_type type, u64 queue_size,
				   काष्ठा gdma_queue **queue)
अणु
	काष्ठा gdma_queue_spec spec = अणुपूर्ण;

	अगर (type != GDMA_SQ && type != GDMA_RQ)
		वापस -EINVAL;

	spec.type = type;
	spec.monitor_avl_buf = false;
	spec.queue_size = queue_size;

	वापस mana_gd_create_hwc_queue(hwc->gdma_dev, &spec, queue);
पूर्ण

अटल पूर्णांक mana_hwc_create_gdma_cq(काष्ठा hw_channel_context *hwc,
				   u64 queue_size,
				   व्योम *ctx, gdma_cq_callback *cb,
				   काष्ठा gdma_queue *parent_eq,
				   काष्ठा gdma_queue **queue)
अणु
	काष्ठा gdma_queue_spec spec = अणुपूर्ण;

	spec.type = GDMA_CQ;
	spec.monitor_avl_buf = false;
	spec.queue_size = queue_size;
	spec.cq.context = ctx;
	spec.cq.callback = cb;
	spec.cq.parent_eq = parent_eq;

	वापस mana_gd_create_hwc_queue(hwc->gdma_dev, &spec, queue);
पूर्ण

अटल पूर्णांक mana_hwc_create_gdma_eq(काष्ठा hw_channel_context *hwc,
				   u64 queue_size,
				   व्योम *ctx, gdma_eq_callback *cb,
				   काष्ठा gdma_queue **queue)
अणु
	काष्ठा gdma_queue_spec spec = अणुपूर्ण;

	spec.type = GDMA_EQ;
	spec.monitor_avl_buf = false;
	spec.queue_size = queue_size;
	spec.eq.context = ctx;
	spec.eq.callback = cb;
	spec.eq.log2_throttle_limit = DEFAULT_LOG2_THROTTLING_FOR_ERROR_EQ;

	वापस mana_gd_create_hwc_queue(hwc->gdma_dev, &spec, queue);
पूर्ण

अटल व्योम mana_hwc_comp_event(व्योम *ctx, काष्ठा gdma_queue *q_self)
अणु
	काष्ठा hwc_rx_oob comp_data = अणुपूर्ण;
	काष्ठा gdma_comp *completions;
	काष्ठा hwc_cq *hwc_cq = ctx;
	पूर्णांक comp_पढ़ो, i;

	WARN_ON_ONCE(hwc_cq->gdma_cq != q_self);

	completions = hwc_cq->comp_buf;
	comp_पढ़ो = mana_gd_poll_cq(q_self, completions, hwc_cq->queue_depth);
	WARN_ON_ONCE(comp_पढ़ो <= 0 || comp_पढ़ो > hwc_cq->queue_depth);

	क्रम (i = 0; i < comp_पढ़ो; ++i) अणु
		comp_data = *(काष्ठा hwc_rx_oob *)completions[i].cqe_data;

		अगर (completions[i].is_sq)
			hwc_cq->tx_event_handler(hwc_cq->tx_event_ctx,
						completions[i].wq_num,
						&comp_data);
		अन्यथा
			hwc_cq->rx_event_handler(hwc_cq->rx_event_ctx,
						completions[i].wq_num,
						&comp_data);
	पूर्ण

	mana_gd_arm_cq(q_self);
पूर्ण

अटल व्योम mana_hwc_destroy_cq(काष्ठा gdma_context *gc, काष्ठा hwc_cq *hwc_cq)
अणु
	अगर (!hwc_cq)
		वापस;

	kमुक्त(hwc_cq->comp_buf);

	अगर (hwc_cq->gdma_cq)
		mana_gd_destroy_queue(gc, hwc_cq->gdma_cq);

	अगर (hwc_cq->gdma_eq)
		mana_gd_destroy_queue(gc, hwc_cq->gdma_eq);

	kमुक्त(hwc_cq);
पूर्ण

अटल पूर्णांक mana_hwc_create_cq(काष्ठा hw_channel_context *hwc, u16 q_depth,
			      gdma_eq_callback *callback, व्योम *ctx,
			      hwc_rx_event_handler_t *rx_ev_hdlr,
			      व्योम *rx_ev_ctx,
			      hwc_tx_event_handler_t *tx_ev_hdlr,
			      व्योम *tx_ev_ctx, काष्ठा hwc_cq **hwc_cq_ptr)
अणु
	काष्ठा gdma_queue *eq, *cq;
	काष्ठा gdma_comp *comp_buf;
	काष्ठा hwc_cq *hwc_cq;
	u32 eq_size, cq_size;
	पूर्णांक err;

	eq_size = roundup_घात_of_two(GDMA_EQE_SIZE * q_depth);
	अगर (eq_size < MINIMUM_SUPPORTED_PAGE_SIZE)
		eq_size = MINIMUM_SUPPORTED_PAGE_SIZE;

	cq_size = roundup_घात_of_two(GDMA_CQE_SIZE * q_depth);
	अगर (cq_size < MINIMUM_SUPPORTED_PAGE_SIZE)
		cq_size = MINIMUM_SUPPORTED_PAGE_SIZE;

	hwc_cq = kzalloc(माप(*hwc_cq), GFP_KERNEL);
	अगर (!hwc_cq)
		वापस -ENOMEM;

	err = mana_hwc_create_gdma_eq(hwc, eq_size, ctx, callback, &eq);
	अगर (err) अणु
		dev_err(hwc->dev, "Failed to create HWC EQ for RQ: %d\n", err);
		जाओ out;
	पूर्ण
	hwc_cq->gdma_eq = eq;

	err = mana_hwc_create_gdma_cq(hwc, cq_size, hwc_cq, mana_hwc_comp_event,
				      eq, &cq);
	अगर (err) अणु
		dev_err(hwc->dev, "Failed to create HWC CQ for RQ: %d\n", err);
		जाओ out;
	पूर्ण
	hwc_cq->gdma_cq = cq;

	comp_buf = kसुस्मृति(q_depth, माप(काष्ठा gdma_comp), GFP_KERNEL);
	अगर (!comp_buf) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	hwc_cq->hwc = hwc;
	hwc_cq->comp_buf = comp_buf;
	hwc_cq->queue_depth = q_depth;
	hwc_cq->rx_event_handler = rx_ev_hdlr;
	hwc_cq->rx_event_ctx = rx_ev_ctx;
	hwc_cq->tx_event_handler = tx_ev_hdlr;
	hwc_cq->tx_event_ctx = tx_ev_ctx;

	*hwc_cq_ptr = hwc_cq;
	वापस 0;
out:
	mana_hwc_destroy_cq(hwc->gdma_dev->gdma_context, hwc_cq);
	वापस err;
पूर्ण

अटल पूर्णांक mana_hwc_alloc_dma_buf(काष्ठा hw_channel_context *hwc, u16 q_depth,
				  u32 max_msg_size,
				  काष्ठा hwc_dma_buf **dma_buf_ptr)
अणु
	काष्ठा gdma_context *gc = hwc->gdma_dev->gdma_context;
	काष्ठा hwc_work_request *hwc_wr;
	काष्ठा hwc_dma_buf *dma_buf;
	काष्ठा gdma_mem_info *gmi;
	व्योम *virt_addr;
	u32 buf_size;
	u8 *base_pa;
	पूर्णांक err;
	u16 i;

	dma_buf = kzalloc(माप(*dma_buf) +
			  q_depth * माप(काष्ठा hwc_work_request),
			  GFP_KERNEL);
	अगर (!dma_buf)
		वापस -ENOMEM;

	dma_buf->num_reqs = q_depth;

	buf_size = PAGE_ALIGN(q_depth * max_msg_size);

	gmi = &dma_buf->mem_info;
	err = mana_gd_alloc_memory(gc, buf_size, gmi);
	अगर (err) अणु
		dev_err(hwc->dev, "Failed to allocate DMA buffer: %d\n", err);
		जाओ out;
	पूर्ण

	virt_addr = dma_buf->mem_info.virt_addr;
	base_pa = (u8 *)dma_buf->mem_info.dma_handle;

	क्रम (i = 0; i < q_depth; i++) अणु
		hwc_wr = &dma_buf->reqs[i];

		hwc_wr->buf_va = virt_addr + i * max_msg_size;
		hwc_wr->buf_sge_addr = base_pa + i * max_msg_size;

		hwc_wr->buf_len = max_msg_size;
	पूर्ण

	*dma_buf_ptr = dma_buf;
	वापस 0;
out:
	kमुक्त(dma_buf);
	वापस err;
पूर्ण

अटल व्योम mana_hwc_dealloc_dma_buf(काष्ठा hw_channel_context *hwc,
				     काष्ठा hwc_dma_buf *dma_buf)
अणु
	अगर (!dma_buf)
		वापस;

	mana_gd_मुक्त_memory(&dma_buf->mem_info);

	kमुक्त(dma_buf);
पूर्ण

अटल व्योम mana_hwc_destroy_wq(काष्ठा hw_channel_context *hwc,
				काष्ठा hwc_wq *hwc_wq)
अणु
	अगर (!hwc_wq)
		वापस;

	mana_hwc_dealloc_dma_buf(hwc, hwc_wq->msg_buf);

	अगर (hwc_wq->gdma_wq)
		mana_gd_destroy_queue(hwc->gdma_dev->gdma_context,
				      hwc_wq->gdma_wq);

	kमुक्त(hwc_wq);
पूर्ण

अटल पूर्णांक mana_hwc_create_wq(काष्ठा hw_channel_context *hwc,
			      क्रमागत gdma_queue_type q_type, u16 q_depth,
			      u32 max_msg_size, काष्ठा hwc_cq *hwc_cq,
			      काष्ठा hwc_wq **hwc_wq_ptr)
अणु
	काष्ठा gdma_queue *queue;
	काष्ठा hwc_wq *hwc_wq;
	u32 queue_size;
	पूर्णांक err;

	WARN_ON(q_type != GDMA_SQ && q_type != GDMA_RQ);

	अगर (q_type == GDMA_RQ)
		queue_size = roundup_घात_of_two(GDMA_MAX_RQE_SIZE * q_depth);
	अन्यथा
		queue_size = roundup_घात_of_two(GDMA_MAX_SQE_SIZE * q_depth);

	अगर (queue_size < MINIMUM_SUPPORTED_PAGE_SIZE)
		queue_size = MINIMUM_SUPPORTED_PAGE_SIZE;

	hwc_wq = kzalloc(माप(*hwc_wq), GFP_KERNEL);
	अगर (!hwc_wq)
		वापस -ENOMEM;

	err = mana_hwc_create_gdma_wq(hwc, q_type, queue_size, &queue);
	अगर (err)
		जाओ out;

	err = mana_hwc_alloc_dma_buf(hwc, q_depth, max_msg_size,
				     &hwc_wq->msg_buf);
	अगर (err)
		जाओ out;

	hwc_wq->hwc = hwc;
	hwc_wq->gdma_wq = queue;
	hwc_wq->queue_depth = q_depth;
	hwc_wq->hwc_cq = hwc_cq;

	*hwc_wq_ptr = hwc_wq;
	वापस 0;
out:
	अगर (err)
		mana_hwc_destroy_wq(hwc, hwc_wq);
	वापस err;
पूर्ण

अटल पूर्णांक mana_hwc_post_tx_wqe(स्थिर काष्ठा hwc_wq *hwc_txq,
				काष्ठा hwc_work_request *req,
				u32 dest_virt_rq_id, u32 dest_virt_rcq_id,
				bool dest_pf)
अणु
	काष्ठा device *dev = hwc_txq->hwc->dev;
	काष्ठा hwc_tx_oob *tx_oob;
	काष्ठा gdma_sge *sge;
	पूर्णांक err;

	अगर (req->msg_size == 0 || req->msg_size > req->buf_len) अणु
		dev_err(dev, "wrong msg_size: %u, buf_len: %u\n",
			req->msg_size, req->buf_len);
		वापस -EINVAL;
	पूर्ण

	tx_oob = &req->tx_oob;

	tx_oob->vrq_id = dest_virt_rq_id;
	tx_oob->dest_vfid = 0;
	tx_oob->vrcq_id = dest_virt_rcq_id;
	tx_oob->vscq_id = hwc_txq->hwc_cq->gdma_cq->id;
	tx_oob->loopback = false;
	tx_oob->lso_override = false;
	tx_oob->dest_pf = dest_pf;
	tx_oob->vsq_id = hwc_txq->gdma_wq->id;

	sge = &req->sge;
	sge->address = (u64)req->buf_sge_addr;
	sge->mem_key = hwc_txq->msg_buf->gpa_mkey;
	sge->size = req->msg_size;

	स_रखो(&req->wqe_req, 0, माप(काष्ठा gdma_wqe_request));
	req->wqe_req.sgl = sge;
	req->wqe_req.num_sge = 1;
	req->wqe_req.अंतरभूत_oob_size = माप(काष्ठा hwc_tx_oob);
	req->wqe_req.अंतरभूत_oob_data = tx_oob;
	req->wqe_req.client_data_unit = 0;

	err = mana_gd_post_and_ring(hwc_txq->gdma_wq, &req->wqe_req, शून्य);
	अगर (err)
		dev_err(dev, "Failed to post WQE on HWC SQ: %d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक mana_hwc_init_inflight_msg(काष्ठा hw_channel_context *hwc,
				      u16 num_msg)
अणु
	पूर्णांक err;

	sema_init(&hwc->sema, num_msg);

	err = mana_gd_alloc_res_map(num_msg, &hwc->inflight_msg_res);
	अगर (err)
		dev_err(hwc->dev, "Failed to init inflight_msg_res: %d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक mana_hwc_test_channel(काष्ठा hw_channel_context *hwc, u16 q_depth,
				 u32 max_req_msg_size, u32 max_resp_msg_size)
अणु
	काष्ठा gdma_context *gc = hwc->gdma_dev->gdma_context;
	काष्ठा hwc_wq *hwc_rxq = hwc->rxq;
	काष्ठा hwc_work_request *req;
	काष्ठा hwc_caller_ctx *ctx;
	पूर्णांक err;
	पूर्णांक i;

	/* Post all WQEs on the RQ */
	क्रम (i = 0; i < q_depth; i++) अणु
		req = &hwc_rxq->msg_buf->reqs[i];
		err = mana_hwc_post_rx_wqe(hwc_rxq, req);
		अगर (err)
			वापस err;
	पूर्ण

	ctx = kzalloc(q_depth * माप(काष्ठा hwc_caller_ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	क्रम (i = 0; i < q_depth; ++i)
		init_completion(&ctx[i].comp_event);

	hwc->caller_ctx = ctx;

	वापस mana_gd_test_eq(gc, hwc->cq->gdma_eq);
पूर्ण

अटल पूर्णांक mana_hwc_establish_channel(काष्ठा gdma_context *gc, u16 *q_depth,
				      u32 *max_req_msg_size,
				      u32 *max_resp_msg_size)
अणु
	काष्ठा hw_channel_context *hwc = gc->hwc.driver_data;
	काष्ठा gdma_queue *rq = hwc->rxq->gdma_wq;
	काष्ठा gdma_queue *sq = hwc->txq->gdma_wq;
	काष्ठा gdma_queue *eq = hwc->cq->gdma_eq;
	काष्ठा gdma_queue *cq = hwc->cq->gdma_cq;
	पूर्णांक err;

	init_completion(&hwc->hwc_init_eqe_comp);

	err = mana_smc_setup_hwc(&gc->shm_channel, false,
				 eq->mem_info.dma_handle,
				 cq->mem_info.dma_handle,
				 rq->mem_info.dma_handle,
				 sq->mem_info.dma_handle,
				 eq->eq.msix_index);
	अगर (err)
		वापस err;

	अगर (!रुको_क्रम_completion_समयout(&hwc->hwc_init_eqe_comp, 60 * HZ))
		वापस -ETIMEDOUT;

	*q_depth = hwc->hwc_init_q_depth_max;
	*max_req_msg_size = hwc->hwc_init_max_req_msg_size;
	*max_resp_msg_size = hwc->hwc_init_max_resp_msg_size;

	अगर (WARN_ON(cq->id >= gc->max_num_cqs))
		वापस -EPROTO;

	gc->cq_table = vzalloc(gc->max_num_cqs * माप(काष्ठा gdma_queue *));
	अगर (!gc->cq_table)
		वापस -ENOMEM;

	gc->cq_table[cq->id] = cq;

	वापस 0;
पूर्ण

अटल पूर्णांक mana_hwc_init_queues(काष्ठा hw_channel_context *hwc, u16 q_depth,
				u32 max_req_msg_size, u32 max_resp_msg_size)
अणु
	काष्ठा hwc_wq *hwc_rxq = शून्य;
	काष्ठा hwc_wq *hwc_txq = शून्य;
	काष्ठा hwc_cq *hwc_cq = शून्य;
	पूर्णांक err;

	err = mana_hwc_init_inflight_msg(hwc, q_depth);
	अगर (err)
		वापस err;

	/* CQ is shared by SQ and RQ, so CQ's queue depth is the sum of SQ
	 * queue depth and RQ queue depth.
	 */
	err = mana_hwc_create_cq(hwc, q_depth * 2,
				 mana_hwc_init_event_handler, hwc,
				 mana_hwc_rx_event_handler, hwc,
				 mana_hwc_tx_event_handler, hwc, &hwc_cq);
	अगर (err) अणु
		dev_err(hwc->dev, "Failed to create HWC CQ: %d\n", err);
		जाओ out;
	पूर्ण
	hwc->cq = hwc_cq;

	err = mana_hwc_create_wq(hwc, GDMA_RQ, q_depth, max_req_msg_size,
				 hwc_cq, &hwc_rxq);
	अगर (err) अणु
		dev_err(hwc->dev, "Failed to create HWC RQ: %d\n", err);
		जाओ out;
	पूर्ण
	hwc->rxq = hwc_rxq;

	err = mana_hwc_create_wq(hwc, GDMA_SQ, q_depth, max_resp_msg_size,
				 hwc_cq, &hwc_txq);
	अगर (err) अणु
		dev_err(hwc->dev, "Failed to create HWC SQ: %d\n", err);
		जाओ out;
	पूर्ण
	hwc->txq = hwc_txq;

	hwc->num_inflight_msg = q_depth;
	hwc->max_req_msg_size = max_req_msg_size;

	वापस 0;
out:
	अगर (hwc_txq)
		mana_hwc_destroy_wq(hwc, hwc_txq);

	अगर (hwc_rxq)
		mana_hwc_destroy_wq(hwc, hwc_rxq);

	अगर (hwc_cq)
		mana_hwc_destroy_cq(hwc->gdma_dev->gdma_context, hwc_cq);

	mana_gd_मुक्त_res_map(&hwc->inflight_msg_res);
	वापस err;
पूर्ण

पूर्णांक mana_hwc_create_channel(काष्ठा gdma_context *gc)
अणु
	u32 max_req_msg_size, max_resp_msg_size;
	काष्ठा gdma_dev *gd = &gc->hwc;
	काष्ठा hw_channel_context *hwc;
	u16 q_depth_max;
	पूर्णांक err;

	hwc = kzalloc(माप(*hwc), GFP_KERNEL);
	अगर (!hwc)
		वापस -ENOMEM;

	gd->gdma_context = gc;
	gd->driver_data = hwc;
	hwc->gdma_dev = gd;
	hwc->dev = gc->dev;

	/* HWC's instance number is always 0. */
	gd->dev_id.as_uपूर्णांक32 = 0;
	gd->dev_id.type = GDMA_DEVICE_HWC;

	gd->pdid = INVALID_PDID;
	gd->करोorbell = INVALID_DOORBELL;

	err = mana_hwc_init_queues(hwc, HW_CHANNEL_VF_BOOTSTRAP_QUEUE_DEPTH,
				   HW_CHANNEL_MAX_REQUEST_SIZE,
				   HW_CHANNEL_MAX_RESPONSE_SIZE);
	अगर (err) अणु
		dev_err(hwc->dev, "Failed to initialize HWC: %d\n", err);
		जाओ out;
	पूर्ण

	err = mana_hwc_establish_channel(gc, &q_depth_max, &max_req_msg_size,
					 &max_resp_msg_size);
	अगर (err) अणु
		dev_err(hwc->dev, "Failed to establish HWC: %d\n", err);
		जाओ out;
	पूर्ण

	err = mana_hwc_test_channel(gc->hwc.driver_data,
				    HW_CHANNEL_VF_BOOTSTRAP_QUEUE_DEPTH,
				    max_req_msg_size, max_resp_msg_size);
	अगर (err) अणु
		dev_err(hwc->dev, "Failed to test HWC: %d\n", err);
		जाओ out;
	पूर्ण

	वापस 0;
out:
	kमुक्त(hwc);
	वापस err;
पूर्ण

व्योम mana_hwc_destroy_channel(काष्ठा gdma_context *gc)
अणु
	काष्ठा hw_channel_context *hwc = gc->hwc.driver_data;
	काष्ठा hwc_caller_ctx *ctx;

	mana_smc_tearकरोwn_hwc(&gc->shm_channel, false);

	ctx = hwc->caller_ctx;
	kमुक्त(ctx);
	hwc->caller_ctx = शून्य;

	mana_hwc_destroy_wq(hwc, hwc->txq);
	hwc->txq = शून्य;

	mana_hwc_destroy_wq(hwc, hwc->rxq);
	hwc->rxq = शून्य;

	mana_hwc_destroy_cq(hwc->gdma_dev->gdma_context, hwc->cq);
	hwc->cq = शून्य;

	mana_gd_मुक्त_res_map(&hwc->inflight_msg_res);

	hwc->num_inflight_msg = 0;

	अगर (hwc->gdma_dev->pdid != INVALID_PDID) अणु
		hwc->gdma_dev->करोorbell = INVALID_DOORBELL;
		hwc->gdma_dev->pdid = INVALID_PDID;
	पूर्ण

	kमुक्त(hwc);
	gc->hwc.driver_data = शून्य;
	gc->hwc.gdma_context = शून्य;
पूर्ण

पूर्णांक mana_hwc_send_request(काष्ठा hw_channel_context *hwc, u32 req_len,
			  स्थिर व्योम *req, u32 resp_len, व्योम *resp)
अणु
	काष्ठा hwc_work_request *tx_wr;
	काष्ठा hwc_wq *txq = hwc->txq;
	काष्ठा gdma_req_hdr *req_msg;
	काष्ठा hwc_caller_ctx *ctx;
	u16 msg_id;
	पूर्णांक err;

	mana_hwc_get_msg_index(hwc, &msg_id);

	tx_wr = &txq->msg_buf->reqs[msg_id];

	अगर (req_len > tx_wr->buf_len) अणु
		dev_err(hwc->dev, "HWC: req msg size: %d > %d\n", req_len,
			tx_wr->buf_len);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	ctx = hwc->caller_ctx + msg_id;
	ctx->output_buf = resp;
	ctx->output_buflen = resp_len;

	req_msg = (काष्ठा gdma_req_hdr *)tx_wr->buf_va;
	अगर (req)
		स_नकल(req_msg, req, req_len);

	req_msg->req.hwc_msg_id = msg_id;

	tx_wr->msg_size = req_len;

	err = mana_hwc_post_tx_wqe(txq, tx_wr, 0, 0, false);
	अगर (err) अणु
		dev_err(hwc->dev, "HWC: Failed to post send WQE: %d\n", err);
		जाओ out;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&ctx->comp_event, 30 * HZ)) अणु
		dev_err(hwc->dev, "HWC: Request timed out!\n");
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	अगर (ctx->error) अणु
		err = ctx->error;
		जाओ out;
	पूर्ण

	अगर (ctx->status_code) अणु
		dev_err(hwc->dev, "HWC: Failed hw_channel req: 0x%x\n",
			ctx->status_code);
		err = -EPROTO;
		जाओ out;
	पूर्ण
out:
	mana_hwc_put_msg_index(hwc, msg_id);
	वापस err;
पूर्ण
