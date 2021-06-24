<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Provide TDMA helper functions used by cipher and hash algorithm
 * implementations.
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 * Author: Arnaud Ebalard <arno@natisbad.org>
 *
 * This work is based on an initial version written by
 * Sebastian Andrzej Siewior < sebastian at अवरोधpoपूर्णांक करोt cc >
 */

#समावेश "cesa.h"

bool mv_cesa_req_dma_iter_next_transfer(काष्ठा mv_cesa_dma_iter *iter,
					काष्ठा mv_cesa_sg_dma_iter *sgiter,
					अचिन्हित पूर्णांक len)
अणु
	अगर (!sgiter->sg)
		वापस false;

	sgiter->op_offset += len;
	sgiter->offset += len;
	अगर (sgiter->offset == sg_dma_len(sgiter->sg)) अणु
		अगर (sg_is_last(sgiter->sg))
			वापस false;
		sgiter->offset = 0;
		sgiter->sg = sg_next(sgiter->sg);
	पूर्ण

	अगर (sgiter->op_offset == iter->op_len)
		वापस false;

	वापस true;
पूर्ण

व्योम mv_cesa_dma_step(काष्ठा mv_cesa_req *dreq)
अणु
	काष्ठा mv_cesa_engine *engine = dreq->engine;

	ग_लिखोl_relaxed(0, engine->regs + CESA_SA_CFG);

	mv_cesa_set_पूर्णांक_mask(engine, CESA_SA_INT_ACC0_IDMA_DONE);
	ग_लिखोl_relaxed(CESA_TDMA_DST_BURST_128B | CESA_TDMA_SRC_BURST_128B |
		       CESA_TDMA_NO_BYTE_SWAP | CESA_TDMA_EN,
		       engine->regs + CESA_TDMA_CONTROL);

	ग_लिखोl_relaxed(CESA_SA_CFG_ACT_CH0_IDMA | CESA_SA_CFG_MULTI_PKT |
		       CESA_SA_CFG_CH0_W_IDMA | CESA_SA_CFG_PARA_DIS,
		       engine->regs + CESA_SA_CFG);
	ग_लिखोl_relaxed(dreq->chain.first->cur_dma,
		       engine->regs + CESA_TDMA_NEXT_ADDR);
	WARN_ON(पढ़ोl(engine->regs + CESA_SA_CMD) &
		CESA_SA_CMD_EN_CESA_SA_ACCL0);
	ग_लिखोl(CESA_SA_CMD_EN_CESA_SA_ACCL0, engine->regs + CESA_SA_CMD);
पूर्ण

व्योम mv_cesa_dma_cleanup(काष्ठा mv_cesa_req *dreq)
अणु
	काष्ठा mv_cesa_tdma_desc *tdma;

	क्रम (tdma = dreq->chain.first; tdma;) अणु
		काष्ठा mv_cesa_tdma_desc *old_tdma = tdma;
		u32 type = tdma->flags & CESA_TDMA_TYPE_MSK;

		अगर (type == CESA_TDMA_OP)
			dma_pool_मुक्त(cesa_dev->dma->op_pool, tdma->op,
				      le32_to_cpu(tdma->src));

		tdma = tdma->next;
		dma_pool_मुक्त(cesa_dev->dma->tdma_desc_pool, old_tdma,
			      old_tdma->cur_dma);
	पूर्ण

	dreq->chain.first = शून्य;
	dreq->chain.last = शून्य;
पूर्ण

व्योम mv_cesa_dma_prepare(काष्ठा mv_cesa_req *dreq,
			 काष्ठा mv_cesa_engine *engine)
अणु
	काष्ठा mv_cesa_tdma_desc *tdma;

	क्रम (tdma = dreq->chain.first; tdma; tdma = tdma->next) अणु
		अगर (tdma->flags & CESA_TDMA_DST_IN_SRAM)
			tdma->dst = cpu_to_le32(tdma->dst_dma + engine->sram_dma);

		अगर (tdma->flags & CESA_TDMA_SRC_IN_SRAM)
			tdma->src = cpu_to_le32(tdma->src_dma + engine->sram_dma);

		अगर ((tdma->flags & CESA_TDMA_TYPE_MSK) == CESA_TDMA_OP)
			mv_cesa_adjust_op(engine, tdma->op);
	पूर्ण
पूर्ण

व्योम mv_cesa_tdma_chain(काष्ठा mv_cesa_engine *engine,
			काष्ठा mv_cesa_req *dreq)
अणु
	अगर (engine->chain.first == शून्य && engine->chain.last == शून्य) अणु
		engine->chain.first = dreq->chain.first;
		engine->chain.last  = dreq->chain.last;
	पूर्ण अन्यथा अणु
		काष्ठा mv_cesa_tdma_desc *last;

		last = engine->chain.last;
		last->next = dreq->chain.first;
		engine->chain.last = dreq->chain.last;

		/*
		 * Break the DMA chain अगर the CESA_TDMA_BREAK_CHAIN is set on
		 * the last element of the current chain, or अगर the request
		 * being queued needs the IV regs to be set beक्रमe lauching
		 * the request.
		 */
		अगर (!(last->flags & CESA_TDMA_BREAK_CHAIN) &&
		    !(dreq->chain.first->flags & CESA_TDMA_SET_STATE))
			last->next_dma = cpu_to_le32(dreq->chain.first->cur_dma);
	पूर्ण
पूर्ण

पूर्णांक mv_cesa_tdma_process(काष्ठा mv_cesa_engine *engine, u32 status)
अणु
	काष्ठा crypto_async_request *req = शून्य;
	काष्ठा mv_cesa_tdma_desc *tdma = शून्य, *next = शून्य;
	dma_addr_t tdma_cur;
	पूर्णांक res = 0;

	tdma_cur = पढ़ोl(engine->regs + CESA_TDMA_CUR);

	क्रम (tdma = engine->chain.first; tdma; tdma = next) अणु
		spin_lock_bh(&engine->lock);
		next = tdma->next;
		spin_unlock_bh(&engine->lock);

		अगर (tdma->flags & CESA_TDMA_END_OF_REQ) अणु
			काष्ठा crypto_async_request *backlog = शून्य;
			काष्ठा mv_cesa_ctx *ctx;
			u32 current_status;

			spin_lock_bh(&engine->lock);
			/*
			 * अगर req is शून्य, this means we're processing the
			 * request in engine->req.
			 */
			अगर (!req)
				req = engine->req;
			अन्यथा
				req = mv_cesa_dequeue_req_locked(engine,
								 &backlog);

			/* Re-chaining to the next request */
			engine->chain.first = tdma->next;
			tdma->next = शून्य;

			/* If this is the last request, clear the chain */
			अगर (engine->chain.first == शून्य)
				engine->chain.last  = शून्य;
			spin_unlock_bh(&engine->lock);

			ctx = crypto_tfm_ctx(req->tfm);
			current_status = (tdma->cur_dma == tdma_cur) ?
					  status : CESA_SA_INT_ACC0_IDMA_DONE;
			res = ctx->ops->process(req, current_status);
			ctx->ops->complete(req);

			अगर (res == 0)
				mv_cesa_engine_enqueue_complete_request(engine,
									req);

			अगर (backlog)
				backlog->complete(backlog, -EINPROGRESS);
		पूर्ण

		अगर (res || tdma->cur_dma == tdma_cur)
			अवरोध;
	पूर्ण

	/*
	 * Save the last request in error to engine->req, so that the core
	 * knows which request was faulty
	 */
	अगर (res) अणु
		spin_lock_bh(&engine->lock);
		engine->req = req;
		spin_unlock_bh(&engine->lock);
	पूर्ण

	वापस res;
पूर्ण

अटल काष्ठा mv_cesa_tdma_desc *
mv_cesa_dma_add_desc(काष्ठा mv_cesa_tdma_chain *chain, gfp_t flags)
अणु
	काष्ठा mv_cesa_tdma_desc *new_tdma = शून्य;
	dma_addr_t dma_handle;

	new_tdma = dma_pool_zalloc(cesa_dev->dma->tdma_desc_pool, flags,
				   &dma_handle);
	अगर (!new_tdma)
		वापस ERR_PTR(-ENOMEM);

	new_tdma->cur_dma = dma_handle;
	अगर (chain->last) अणु
		chain->last->next_dma = cpu_to_le32(dma_handle);
		chain->last->next = new_tdma;
	पूर्ण अन्यथा अणु
		chain->first = new_tdma;
	पूर्ण

	chain->last = new_tdma;

	वापस new_tdma;
पूर्ण

पूर्णांक mv_cesa_dma_add_result_op(काष्ठा mv_cesa_tdma_chain *chain, dma_addr_t src,
			  u32 size, u32 flags, gfp_t gfp_flags)
अणु
	काष्ठा mv_cesa_tdma_desc *tdma, *op_desc;

	tdma = mv_cesa_dma_add_desc(chain, gfp_flags);
	अगर (IS_ERR(tdma))
		वापस PTR_ERR(tdma);

	/* We re-use an existing op_desc object to retrieve the context
	 * and result instead of allocating a new one.
	 * There is at least one object of this type in a CESA crypto
	 * req, just pick the first one in the chain.
	 */
	क्रम (op_desc = chain->first; op_desc; op_desc = op_desc->next) अणु
		u32 type = op_desc->flags & CESA_TDMA_TYPE_MSK;

		अगर (type == CESA_TDMA_OP)
			अवरोध;
	पूर्ण

	अगर (!op_desc)
		वापस -EIO;

	tdma->byte_cnt = cpu_to_le32(size | BIT(31));
	tdma->src_dma = src;
	tdma->dst_dma = op_desc->src_dma;
	tdma->op = op_desc->op;

	flags &= (CESA_TDMA_DST_IN_SRAM | CESA_TDMA_SRC_IN_SRAM);
	tdma->flags = flags | CESA_TDMA_RESULT;
	वापस 0;
पूर्ण

काष्ठा mv_cesa_op_ctx *mv_cesa_dma_add_op(काष्ठा mv_cesa_tdma_chain *chain,
					स्थिर काष्ठा mv_cesa_op_ctx *op_templ,
					bool skip_ctx,
					gfp_t flags)
अणु
	काष्ठा mv_cesa_tdma_desc *tdma;
	काष्ठा mv_cesa_op_ctx *op;
	dma_addr_t dma_handle;
	अचिन्हित पूर्णांक size;

	tdma = mv_cesa_dma_add_desc(chain, flags);
	अगर (IS_ERR(tdma))
		वापस ERR_CAST(tdma);

	op = dma_pool_alloc(cesa_dev->dma->op_pool, flags, &dma_handle);
	अगर (!op)
		वापस ERR_PTR(-ENOMEM);

	*op = *op_templ;

	size = skip_ctx ? माप(op->desc) : माप(*op);

	tdma = chain->last;
	tdma->op = op;
	tdma->byte_cnt = cpu_to_le32(size | BIT(31));
	tdma->src = cpu_to_le32(dma_handle);
	tdma->dst_dma = CESA_SA_CFG_SRAM_OFFSET;
	tdma->flags = CESA_TDMA_DST_IN_SRAM | CESA_TDMA_OP;

	वापस op;
पूर्ण

पूर्णांक mv_cesa_dma_add_data_transfer(काष्ठा mv_cesa_tdma_chain *chain,
				  dma_addr_t dst, dma_addr_t src, u32 size,
				  u32 flags, gfp_t gfp_flags)
अणु
	काष्ठा mv_cesa_tdma_desc *tdma;

	tdma = mv_cesa_dma_add_desc(chain, gfp_flags);
	अगर (IS_ERR(tdma))
		वापस PTR_ERR(tdma);

	tdma->byte_cnt = cpu_to_le32(size | BIT(31));
	tdma->src_dma = src;
	tdma->dst_dma = dst;

	flags &= (CESA_TDMA_DST_IN_SRAM | CESA_TDMA_SRC_IN_SRAM);
	tdma->flags = flags | CESA_TDMA_DATA;

	वापस 0;
पूर्ण

पूर्णांक mv_cesa_dma_add_dummy_launch(काष्ठा mv_cesa_tdma_chain *chain, gfp_t flags)
अणु
	काष्ठा mv_cesa_tdma_desc *tdma;

	tdma = mv_cesa_dma_add_desc(chain, flags);
	वापस PTR_ERR_OR_ZERO(tdma);
पूर्ण

पूर्णांक mv_cesa_dma_add_dummy_end(काष्ठा mv_cesa_tdma_chain *chain, gfp_t flags)
अणु
	काष्ठा mv_cesa_tdma_desc *tdma;

	tdma = mv_cesa_dma_add_desc(chain, flags);
	अगर (IS_ERR(tdma))
		वापस PTR_ERR(tdma);

	tdma->byte_cnt = cpu_to_le32(BIT(31));

	वापस 0;
पूर्ण

पूर्णांक mv_cesa_dma_add_op_transfers(काष्ठा mv_cesa_tdma_chain *chain,
				 काष्ठा mv_cesa_dma_iter *dma_iter,
				 काष्ठा mv_cesa_sg_dma_iter *sgiter,
				 gfp_t gfp_flags)
अणु
	u32 flags = sgiter->dir == DMA_TO_DEVICE ?
		    CESA_TDMA_DST_IN_SRAM : CESA_TDMA_SRC_IN_SRAM;
	अचिन्हित पूर्णांक len;

	करो अणु
		dma_addr_t dst, src;
		पूर्णांक ret;

		len = mv_cesa_req_dma_iter_transfer_len(dma_iter, sgiter);
		अगर (sgiter->dir == DMA_TO_DEVICE) अणु
			dst = CESA_SA_DATA_SRAM_OFFSET + sgiter->op_offset;
			src = sg_dma_address(sgiter->sg) + sgiter->offset;
		पूर्ण अन्यथा अणु
			dst = sg_dma_address(sgiter->sg) + sgiter->offset;
			src = CESA_SA_DATA_SRAM_OFFSET + sgiter->op_offset;
		पूर्ण

		ret = mv_cesa_dma_add_data_transfer(chain, dst, src, len,
						    flags, gfp_flags);
		अगर (ret)
			वापस ret;

	पूर्ण जबतक (mv_cesa_req_dma_iter_next_transfer(dma_iter, sgiter, len));

	वापस 0;
पूर्ण

माप_प्रकार mv_cesa_sg_copy(काष्ठा mv_cesa_engine *engine,
		       काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents,
		       अचिन्हित पूर्णांक sram_off, माप_प्रकार buflen, off_t skip,
		       bool to_sram)
अणु
	अचिन्हित पूर्णांक sg_flags = SG_MITER_ATOMIC;
	काष्ठा sg_mapping_iter miter;
	अचिन्हित पूर्णांक offset = 0;

	अगर (to_sram)
		sg_flags |= SG_MITER_FROM_SG;
	अन्यथा
		sg_flags |= SG_MITER_TO_SG;

	sg_miter_start(&miter, sgl, nents, sg_flags);

	अगर (!sg_miter_skip(&miter, skip))
		वापस 0;

	जबतक ((offset < buflen) && sg_miter_next(&miter)) अणु
		अचिन्हित पूर्णांक len;

		len = min(miter.length, buflen - offset);

		अगर (to_sram) अणु
			अगर (engine->pool)
				स_नकल(engine->sram_pool + sram_off + offset,
				       miter.addr, len);
			अन्यथा
				स_नकल_toio(engine->sram + sram_off + offset,
					    miter.addr, len);
		पूर्ण अन्यथा अणु
			अगर (engine->pool)
				स_नकल(miter.addr,
				       engine->sram_pool + sram_off + offset,
				       len);
			अन्यथा
				स_नकल_fromio(miter.addr,
					      engine->sram + sram_off + offset,
					      len);
		पूर्ण

		offset += len;
	पूर्ण

	sg_miter_stop(&miter);

	वापस offset;
पूर्ण
