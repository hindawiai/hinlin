<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 HGST, a Western Digital Company.
 */
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci-p2pdma.h>
#समावेश <rdma/mr_pool.h>
#समावेश <rdma/rw.h>

क्रमागत अणु
	RDMA_RW_SINGLE_WR,
	RDMA_RW_MULTI_WR,
	RDMA_RW_MR,
	RDMA_RW_SIG_MR,
पूर्ण;

अटल bool rdma_rw_क्रमce_mr;
module_param_named(क्रमce_mr, rdma_rw_क्रमce_mr, bool, 0);
MODULE_PARM_DESC(क्रमce_mr, "Force usage of MRs for RDMA READ/WRITE operations");

/*
 * Report whether memory registration should be used. Memory registration must
 * be used क्रम iWarp devices because of iWARP-specअगरic limitations. Memory
 * registration is also enabled अगर रेजिस्टरing memory might yield better
 * perक्रमmance than using multiple SGE entries, see rdma_rw_io_needs_mr()
 */
अटल अंतरभूत bool rdma_rw_can_use_mr(काष्ठा ib_device *dev, u32 port_num)
अणु
	अगर (rdma_protocol_iwarp(dev, port_num))
		वापस true;
	अगर (dev->attrs.max_sgl_rd)
		वापस true;
	अगर (unlikely(rdma_rw_क्रमce_mr))
		वापस true;
	वापस false;
पूर्ण

/*
 * Check अगर the device will use memory registration क्रम this RW operation.
 * For RDMA READs we must use MRs on iWarp and can optionally use them as an
 * optimization otherwise.  Additionally we have a debug option to क्रमce usage
 * of MRs to help testing this code path.
 */
अटल अंतरभूत bool rdma_rw_io_needs_mr(काष्ठा ib_device *dev, u32 port_num,
		क्रमागत dma_data_direction dir, पूर्णांक dma_nents)
अणु
	अगर (dir == DMA_FROM_DEVICE) अणु
		अगर (rdma_protocol_iwarp(dev, port_num))
			वापस true;
		अगर (dev->attrs.max_sgl_rd && dma_nents > dev->attrs.max_sgl_rd)
			वापस true;
	पूर्ण
	अगर (unlikely(rdma_rw_क्रमce_mr))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत u32 rdma_rw_fr_page_list_len(काष्ठा ib_device *dev,
					   bool pi_support)
अणु
	u32 max_pages;

	अगर (pi_support)
		max_pages = dev->attrs.max_pi_fast_reg_page_list_len;
	अन्यथा
		max_pages = dev->attrs.max_fast_reg_page_list_len;

	/* arbitrary limit to aव्योम allocating gigantic resources */
	वापस min_t(u32, max_pages, 256);
पूर्ण

अटल अंतरभूत पूर्णांक rdma_rw_inv_key(काष्ठा rdma_rw_reg_ctx *reg)
अणु
	पूर्णांक count = 0;

	अगर (reg->mr->need_inval) अणु
		reg->inv_wr.opcode = IB_WR_LOCAL_INV;
		reg->inv_wr.ex.invalidate_rkey = reg->mr->lkey;
		reg->inv_wr.next = &reg->reg_wr.wr;
		count++;
	पूर्ण अन्यथा अणु
		reg->inv_wr.next = शून्य;
	पूर्ण

	वापस count;
पूर्ण

/* Caller must have zero-initialized *reg. */
अटल पूर्णांक rdma_rw_init_one_mr(काष्ठा ib_qp *qp, u32 port_num,
		काष्ठा rdma_rw_reg_ctx *reg, काष्ठा scatterlist *sg,
		u32 sg_cnt, u32 offset)
अणु
	u32 pages_per_mr = rdma_rw_fr_page_list_len(qp->pd->device,
						    qp->पूर्णांकegrity_en);
	u32 nents = min(sg_cnt, pages_per_mr);
	पूर्णांक count = 0, ret;

	reg->mr = ib_mr_pool_get(qp, &qp->rdma_mrs);
	अगर (!reg->mr)
		वापस -EAGAIN;

	count += rdma_rw_inv_key(reg);

	ret = ib_map_mr_sg(reg->mr, sg, nents, &offset, PAGE_SIZE);
	अगर (ret < 0 || ret < nents) अणु
		ib_mr_pool_put(qp, &qp->rdma_mrs, reg->mr);
		वापस -EINVAL;
	पूर्ण

	reg->reg_wr.wr.opcode = IB_WR_REG_MR;
	reg->reg_wr.mr = reg->mr;
	reg->reg_wr.access = IB_ACCESS_LOCAL_WRITE;
	अगर (rdma_protocol_iwarp(qp->device, port_num))
		reg->reg_wr.access |= IB_ACCESS_REMOTE_WRITE;
	count++;

	reg->sge.addr = reg->mr->iova;
	reg->sge.length = reg->mr->length;
	वापस count;
पूर्ण

अटल पूर्णांक rdma_rw_init_mr_wrs(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp,
		u32 port_num, काष्ठा scatterlist *sg, u32 sg_cnt, u32 offset,
		u64 remote_addr, u32 rkey, क्रमागत dma_data_direction dir)
अणु
	काष्ठा rdma_rw_reg_ctx *prev = शून्य;
	u32 pages_per_mr = rdma_rw_fr_page_list_len(qp->pd->device,
						    qp->पूर्णांकegrity_en);
	पूर्णांक i, j, ret = 0, count = 0;

	ctx->nr_ops = DIV_ROUND_UP(sg_cnt, pages_per_mr);
	ctx->reg = kसुस्मृति(ctx->nr_ops, माप(*ctx->reg), GFP_KERNEL);
	अगर (!ctx->reg) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < ctx->nr_ops; i++) अणु
		काष्ठा rdma_rw_reg_ctx *reg = &ctx->reg[i];
		u32 nents = min(sg_cnt, pages_per_mr);

		ret = rdma_rw_init_one_mr(qp, port_num, reg, sg, sg_cnt,
				offset);
		अगर (ret < 0)
			जाओ out_मुक्त;
		count += ret;

		अगर (prev) अणु
			अगर (reg->mr->need_inval)
				prev->wr.wr.next = &reg->inv_wr;
			अन्यथा
				prev->wr.wr.next = &reg->reg_wr.wr;
		पूर्ण

		reg->reg_wr.wr.next = &reg->wr.wr;

		reg->wr.wr.sg_list = &reg->sge;
		reg->wr.wr.num_sge = 1;
		reg->wr.remote_addr = remote_addr;
		reg->wr.rkey = rkey;
		अगर (dir == DMA_TO_DEVICE) अणु
			reg->wr.wr.opcode = IB_WR_RDMA_WRITE;
		पूर्ण अन्यथा अगर (!rdma_cap_पढ़ो_inv(qp->device, port_num)) अणु
			reg->wr.wr.opcode = IB_WR_RDMA_READ;
		पूर्ण अन्यथा अणु
			reg->wr.wr.opcode = IB_WR_RDMA_READ_WITH_INV;
			reg->wr.wr.ex.invalidate_rkey = reg->mr->lkey;
		पूर्ण
		count++;

		remote_addr += reg->sge.length;
		sg_cnt -= nents;
		क्रम (j = 0; j < nents; j++)
			sg = sg_next(sg);
		prev = reg;
		offset = 0;
	पूर्ण

	अगर (prev)
		prev->wr.wr.next = शून्य;

	ctx->type = RDMA_RW_MR;
	वापस count;

out_मुक्त:
	जबतक (--i >= 0)
		ib_mr_pool_put(qp, &qp->rdma_mrs, ctx->reg[i].mr);
	kमुक्त(ctx->reg);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक rdma_rw_init_map_wrs(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp,
		काष्ठा scatterlist *sg, u32 sg_cnt, u32 offset,
		u64 remote_addr, u32 rkey, क्रमागत dma_data_direction dir)
अणु
	u32 max_sge = dir == DMA_TO_DEVICE ? qp->max_ग_लिखो_sge :
		      qp->max_पढ़ो_sge;
	काष्ठा ib_sge *sge;
	u32 total_len = 0, i, j;

	ctx->nr_ops = DIV_ROUND_UP(sg_cnt, max_sge);

	ctx->map.sges = sge = kसुस्मृति(sg_cnt, माप(*sge), GFP_KERNEL);
	अगर (!ctx->map.sges)
		जाओ out;

	ctx->map.wrs = kसुस्मृति(ctx->nr_ops, माप(*ctx->map.wrs), GFP_KERNEL);
	अगर (!ctx->map.wrs)
		जाओ out_मुक्त_sges;

	क्रम (i = 0; i < ctx->nr_ops; i++) अणु
		काष्ठा ib_rdma_wr *rdma_wr = &ctx->map.wrs[i];
		u32 nr_sge = min(sg_cnt, max_sge);

		अगर (dir == DMA_TO_DEVICE)
			rdma_wr->wr.opcode = IB_WR_RDMA_WRITE;
		अन्यथा
			rdma_wr->wr.opcode = IB_WR_RDMA_READ;
		rdma_wr->remote_addr = remote_addr + total_len;
		rdma_wr->rkey = rkey;
		rdma_wr->wr.num_sge = nr_sge;
		rdma_wr->wr.sg_list = sge;

		क्रम (j = 0; j < nr_sge; j++, sg = sg_next(sg)) अणु
			sge->addr = sg_dma_address(sg) + offset;
			sge->length = sg_dma_len(sg) - offset;
			sge->lkey = qp->pd->local_dma_lkey;

			total_len += sge->length;
			sge++;
			sg_cnt--;
			offset = 0;
		पूर्ण

		rdma_wr->wr.next = i + 1 < ctx->nr_ops ?
			&ctx->map.wrs[i + 1].wr : शून्य;
	पूर्ण

	ctx->type = RDMA_RW_MULTI_WR;
	वापस ctx->nr_ops;

out_मुक्त_sges:
	kमुक्त(ctx->map.sges);
out:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक rdma_rw_init_single_wr(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp,
		काष्ठा scatterlist *sg, u32 offset, u64 remote_addr, u32 rkey,
		क्रमागत dma_data_direction dir)
अणु
	काष्ठा ib_rdma_wr *rdma_wr = &ctx->single.wr;

	ctx->nr_ops = 1;

	ctx->single.sge.lkey = qp->pd->local_dma_lkey;
	ctx->single.sge.addr = sg_dma_address(sg) + offset;
	ctx->single.sge.length = sg_dma_len(sg) - offset;

	स_रखो(rdma_wr, 0, माप(*rdma_wr));
	अगर (dir == DMA_TO_DEVICE)
		rdma_wr->wr.opcode = IB_WR_RDMA_WRITE;
	अन्यथा
		rdma_wr->wr.opcode = IB_WR_RDMA_READ;
	rdma_wr->wr.sg_list = &ctx->single.sge;
	rdma_wr->wr.num_sge = 1;
	rdma_wr->remote_addr = remote_addr;
	rdma_wr->rkey = rkey;

	ctx->type = RDMA_RW_SINGLE_WR;
	वापस 1;
पूर्ण

अटल व्योम rdma_rw_unmap_sg(काष्ठा ib_device *dev, काष्ठा scatterlist *sg,
			     u32 sg_cnt, क्रमागत dma_data_direction dir)
अणु
	अगर (is_pci_p2pdma_page(sg_page(sg)))
		pci_p2pdma_unmap_sg(dev->dma_device, sg, sg_cnt, dir);
	अन्यथा
		ib_dma_unmap_sg(dev, sg, sg_cnt, dir);
पूर्ण

अटल पूर्णांक rdma_rw_map_sg(काष्ठा ib_device *dev, काष्ठा scatterlist *sg,
			  u32 sg_cnt, क्रमागत dma_data_direction dir)
अणु
	अगर (is_pci_p2pdma_page(sg_page(sg))) अणु
		अगर (WARN_ON_ONCE(ib_uses_virt_dma(dev)))
			वापस 0;
		वापस pci_p2pdma_map_sg(dev->dma_device, sg, sg_cnt, dir);
	पूर्ण
	वापस ib_dma_map_sg(dev, sg, sg_cnt, dir);
पूर्ण

/**
 * rdma_rw_ctx_init - initialize a RDMA READ/WRITE context
 * @ctx:	context to initialize
 * @qp:		queue pair to operate on
 * @port_num:	port num to which the connection is bound
 * @sg:		scatterlist to READ/WRITE from/to
 * @sg_cnt:	number of entries in @sg
 * @sg_offset:	current byte offset पूर्णांकo @sg
 * @remote_addr:remote address to पढ़ो/ग_लिखो (relative to @rkey)
 * @rkey:	remote key to operate on
 * @dir:	%DMA_TO_DEVICE क्रम RDMA WRITE, %DMA_FROM_DEVICE क्रम RDMA READ
 *
 * Returns the number of WQEs that will be needed on the workqueue अगर
 * successful, or a negative error code.
 */
पूर्णांक rdma_rw_ctx_init(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp, u32 port_num,
		काष्ठा scatterlist *sg, u32 sg_cnt, u32 sg_offset,
		u64 remote_addr, u32 rkey, क्रमागत dma_data_direction dir)
अणु
	काष्ठा ib_device *dev = qp->pd->device;
	पूर्णांक ret;

	ret = rdma_rw_map_sg(dev, sg, sg_cnt, dir);
	अगर (!ret)
		वापस -ENOMEM;
	sg_cnt = ret;

	/*
	 * Skip to the S/G entry that sg_offset falls पूर्णांकo:
	 */
	क्रम (;;) अणु
		u32 len = sg_dma_len(sg);

		अगर (sg_offset < len)
			अवरोध;

		sg = sg_next(sg);
		sg_offset -= len;
		sg_cnt--;
	पूर्ण

	ret = -EIO;
	अगर (WARN_ON_ONCE(sg_cnt == 0))
		जाओ out_unmap_sg;

	अगर (rdma_rw_io_needs_mr(qp->device, port_num, dir, sg_cnt)) अणु
		ret = rdma_rw_init_mr_wrs(ctx, qp, port_num, sg, sg_cnt,
				sg_offset, remote_addr, rkey, dir);
	पूर्ण अन्यथा अगर (sg_cnt > 1) अणु
		ret = rdma_rw_init_map_wrs(ctx, qp, sg, sg_cnt, sg_offset,
				remote_addr, rkey, dir);
	पूर्ण अन्यथा अणु
		ret = rdma_rw_init_single_wr(ctx, qp, sg, sg_offset,
				remote_addr, rkey, dir);
	पूर्ण

	अगर (ret < 0)
		जाओ out_unmap_sg;
	वापस ret;

out_unmap_sg:
	rdma_rw_unmap_sg(dev, sg, sg_cnt, dir);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_rw_ctx_init);

/**
 * rdma_rw_ctx_signature_init - initialize a RW context with signature offload
 * @ctx:	context to initialize
 * @qp:		queue pair to operate on
 * @port_num:	port num to which the connection is bound
 * @sg:		scatterlist to READ/WRITE from/to
 * @sg_cnt:	number of entries in @sg
 * @prot_sg:	scatterlist to READ/WRITE protection inक्रमmation from/to
 * @prot_sg_cnt: number of entries in @prot_sg
 * @sig_attrs:	signature offloading algorithms
 * @remote_addr:remote address to पढ़ो/ग_लिखो (relative to @rkey)
 * @rkey:	remote key to operate on
 * @dir:	%DMA_TO_DEVICE क्रम RDMA WRITE, %DMA_FROM_DEVICE क्रम RDMA READ
 *
 * Returns the number of WQEs that will be needed on the workqueue अगर
 * successful, or a negative error code.
 */
पूर्णांक rdma_rw_ctx_signature_init(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp,
		u32 port_num, काष्ठा scatterlist *sg, u32 sg_cnt,
		काष्ठा scatterlist *prot_sg, u32 prot_sg_cnt,
		काष्ठा ib_sig_attrs *sig_attrs,
		u64 remote_addr, u32 rkey, क्रमागत dma_data_direction dir)
अणु
	काष्ठा ib_device *dev = qp->pd->device;
	u32 pages_per_mr = rdma_rw_fr_page_list_len(qp->pd->device,
						    qp->पूर्णांकegrity_en);
	काष्ठा ib_rdma_wr *rdma_wr;
	पूर्णांक count = 0, ret;

	अगर (sg_cnt > pages_per_mr || prot_sg_cnt > pages_per_mr) अणु
		pr_err("SG count too large: sg_cnt=%d, prot_sg_cnt=%d, pages_per_mr=%d\n",
		       sg_cnt, prot_sg_cnt, pages_per_mr);
		वापस -EINVAL;
	पूर्ण

	ret = rdma_rw_map_sg(dev, sg, sg_cnt, dir);
	अगर (!ret)
		वापस -ENOMEM;
	sg_cnt = ret;

	अगर (prot_sg_cnt) अणु
		ret = rdma_rw_map_sg(dev, prot_sg, prot_sg_cnt, dir);
		अगर (!ret) अणु
			ret = -ENOMEM;
			जाओ out_unmap_sg;
		पूर्ण
		prot_sg_cnt = ret;
	पूर्ण

	ctx->type = RDMA_RW_SIG_MR;
	ctx->nr_ops = 1;
	ctx->reg = kzalloc(माप(*ctx->reg), GFP_KERNEL);
	अगर (!ctx->reg) अणु
		ret = -ENOMEM;
		जाओ out_unmap_prot_sg;
	पूर्ण

	ctx->reg->mr = ib_mr_pool_get(qp, &qp->sig_mrs);
	अगर (!ctx->reg->mr) अणु
		ret = -EAGAIN;
		जाओ out_मुक्त_ctx;
	पूर्ण

	count += rdma_rw_inv_key(ctx->reg);

	स_नकल(ctx->reg->mr->sig_attrs, sig_attrs, माप(काष्ठा ib_sig_attrs));

	ret = ib_map_mr_sg_pi(ctx->reg->mr, sg, sg_cnt, शून्य, prot_sg,
			      prot_sg_cnt, शून्य, SZ_4K);
	अगर (unlikely(ret)) अणु
		pr_err("failed to map PI sg (%d)\n", sg_cnt + prot_sg_cnt);
		जाओ out_destroy_sig_mr;
	पूर्ण

	ctx->reg->reg_wr.wr.opcode = IB_WR_REG_MR_INTEGRITY;
	ctx->reg->reg_wr.wr.wr_cqe = शून्य;
	ctx->reg->reg_wr.wr.num_sge = 0;
	ctx->reg->reg_wr.wr.send_flags = 0;
	ctx->reg->reg_wr.access = IB_ACCESS_LOCAL_WRITE;
	अगर (rdma_protocol_iwarp(qp->device, port_num))
		ctx->reg->reg_wr.access |= IB_ACCESS_REMOTE_WRITE;
	ctx->reg->reg_wr.mr = ctx->reg->mr;
	ctx->reg->reg_wr.key = ctx->reg->mr->lkey;
	count++;

	ctx->reg->sge.addr = ctx->reg->mr->iova;
	ctx->reg->sge.length = ctx->reg->mr->length;
	अगर (sig_attrs->wire.sig_type == IB_SIG_TYPE_NONE)
		ctx->reg->sge.length -= ctx->reg->mr->sig_attrs->meta_length;

	rdma_wr = &ctx->reg->wr;
	rdma_wr->wr.sg_list = &ctx->reg->sge;
	rdma_wr->wr.num_sge = 1;
	rdma_wr->remote_addr = remote_addr;
	rdma_wr->rkey = rkey;
	अगर (dir == DMA_TO_DEVICE)
		rdma_wr->wr.opcode = IB_WR_RDMA_WRITE;
	अन्यथा
		rdma_wr->wr.opcode = IB_WR_RDMA_READ;
	ctx->reg->reg_wr.wr.next = &rdma_wr->wr;
	count++;

	वापस count;

out_destroy_sig_mr:
	ib_mr_pool_put(qp, &qp->sig_mrs, ctx->reg->mr);
out_मुक्त_ctx:
	kमुक्त(ctx->reg);
out_unmap_prot_sg:
	अगर (prot_sg_cnt)
		rdma_rw_unmap_sg(dev, prot_sg, prot_sg_cnt, dir);
out_unmap_sg:
	rdma_rw_unmap_sg(dev, sg, sg_cnt, dir);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rdma_rw_ctx_signature_init);

/*
 * Now that we are going to post the WRs we can update the lkey and need_inval
 * state on the MRs.  If we were करोing this at init समय, we would get द्विगुन
 * or missing invalidations अगर a context was initialized but not actually
 * posted.
 */
अटल व्योम rdma_rw_update_lkey(काष्ठा rdma_rw_reg_ctx *reg, bool need_inval)
अणु
	reg->mr->need_inval = need_inval;
	ib_update_fast_reg_key(reg->mr, ib_inc_rkey(reg->mr->lkey));
	reg->reg_wr.key = reg->mr->lkey;
	reg->sge.lkey = reg->mr->lkey;
पूर्ण

/**
 * rdma_rw_ctx_wrs - वापस chain of WRs क्रम a RDMA READ or WRITE operation
 * @ctx:	context to operate on
 * @qp:		queue pair to operate on
 * @port_num:	port num to which the connection is bound
 * @cqe:	completion queue entry क्रम the last WR
 * @chain_wr:	WR to append to the posted chain
 *
 * Return the WR chain क्रम the set of RDMA READ/WRITE operations described by
 * @ctx, as well as any memory registration operations needed.  If @chain_wr
 * is non-शून्य the WR it poपूर्णांकs to will be appended to the chain of WRs posted.
 * If @chain_wr is not set @cqe must be set so that the caller माला_लो a
 * completion notअगरication.
 */
काष्ठा ib_send_wr *rdma_rw_ctx_wrs(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp,
		u32 port_num, काष्ठा ib_cqe *cqe, काष्ठा ib_send_wr *chain_wr)
अणु
	काष्ठा ib_send_wr *first_wr, *last_wr;
	पूर्णांक i;

	चयन (ctx->type) अणु
	हाल RDMA_RW_SIG_MR:
	हाल RDMA_RW_MR:
		क्रम (i = 0; i < ctx->nr_ops; i++) अणु
			rdma_rw_update_lkey(&ctx->reg[i],
				ctx->reg[i].wr.wr.opcode !=
					IB_WR_RDMA_READ_WITH_INV);
		पूर्ण

		अगर (ctx->reg[0].inv_wr.next)
			first_wr = &ctx->reg[0].inv_wr;
		अन्यथा
			first_wr = &ctx->reg[0].reg_wr.wr;
		last_wr = &ctx->reg[ctx->nr_ops - 1].wr.wr;
		अवरोध;
	हाल RDMA_RW_MULTI_WR:
		first_wr = &ctx->map.wrs[0].wr;
		last_wr = &ctx->map.wrs[ctx->nr_ops - 1].wr;
		अवरोध;
	हाल RDMA_RW_SINGLE_WR:
		first_wr = &ctx->single.wr.wr;
		last_wr = &ctx->single.wr.wr;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (chain_wr) अणु
		last_wr->next = chain_wr;
	पूर्ण अन्यथा अणु
		last_wr->wr_cqe = cqe;
		last_wr->send_flags |= IB_SEND_SIGNALED;
	पूर्ण

	वापस first_wr;
पूर्ण
EXPORT_SYMBOL(rdma_rw_ctx_wrs);

/**
 * rdma_rw_ctx_post - post a RDMA READ or RDMA WRITE operation
 * @ctx:	context to operate on
 * @qp:		queue pair to operate on
 * @port_num:	port num to which the connection is bound
 * @cqe:	completion queue entry क्रम the last WR
 * @chain_wr:	WR to append to the posted chain
 *
 * Post the set of RDMA READ/WRITE operations described by @ctx, as well as
 * any memory registration operations needed.  If @chain_wr is non-शून्य the
 * WR it poपूर्णांकs to will be appended to the chain of WRs posted.  If @chain_wr
 * is not set @cqe must be set so that the caller माला_लो a completion
 * notअगरication.
 */
पूर्णांक rdma_rw_ctx_post(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp, u32 port_num,
		काष्ठा ib_cqe *cqe, काष्ठा ib_send_wr *chain_wr)
अणु
	काष्ठा ib_send_wr *first_wr;

	first_wr = rdma_rw_ctx_wrs(ctx, qp, port_num, cqe, chain_wr);
	वापस ib_post_send(qp, first_wr, शून्य);
पूर्ण
EXPORT_SYMBOL(rdma_rw_ctx_post);

/**
 * rdma_rw_ctx_destroy - release all resources allocated by rdma_rw_ctx_init
 * @ctx:	context to release
 * @qp:		queue pair to operate on
 * @port_num:	port num to which the connection is bound
 * @sg:		scatterlist that was used क्रम the READ/WRITE
 * @sg_cnt:	number of entries in @sg
 * @dir:	%DMA_TO_DEVICE क्रम RDMA WRITE, %DMA_FROM_DEVICE क्रम RDMA READ
 */
व्योम rdma_rw_ctx_destroy(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp,
			 u32 port_num, काष्ठा scatterlist *sg, u32 sg_cnt,
			 क्रमागत dma_data_direction dir)
अणु
	पूर्णांक i;

	चयन (ctx->type) अणु
	हाल RDMA_RW_MR:
		क्रम (i = 0; i < ctx->nr_ops; i++)
			ib_mr_pool_put(qp, &qp->rdma_mrs, ctx->reg[i].mr);
		kमुक्त(ctx->reg);
		अवरोध;
	हाल RDMA_RW_MULTI_WR:
		kमुक्त(ctx->map.wrs);
		kमुक्त(ctx->map.sges);
		अवरोध;
	हाल RDMA_RW_SINGLE_WR:
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	rdma_rw_unmap_sg(qp->pd->device, sg, sg_cnt, dir);
पूर्ण
EXPORT_SYMBOL(rdma_rw_ctx_destroy);

/**
 * rdma_rw_ctx_destroy_signature - release all resources allocated by
 *	rdma_rw_ctx_signature_init
 * @ctx:	context to release
 * @qp:		queue pair to operate on
 * @port_num:	port num to which the connection is bound
 * @sg:		scatterlist that was used क्रम the READ/WRITE
 * @sg_cnt:	number of entries in @sg
 * @prot_sg:	scatterlist that was used क्रम the READ/WRITE of the PI
 * @prot_sg_cnt: number of entries in @prot_sg
 * @dir:	%DMA_TO_DEVICE क्रम RDMA WRITE, %DMA_FROM_DEVICE क्रम RDMA READ
 */
व्योम rdma_rw_ctx_destroy_signature(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp,
		u32 port_num, काष्ठा scatterlist *sg, u32 sg_cnt,
		काष्ठा scatterlist *prot_sg, u32 prot_sg_cnt,
		क्रमागत dma_data_direction dir)
अणु
	अगर (WARN_ON_ONCE(ctx->type != RDMA_RW_SIG_MR))
		वापस;

	ib_mr_pool_put(qp, &qp->sig_mrs, ctx->reg->mr);
	kमुक्त(ctx->reg);

	अगर (prot_sg_cnt)
		rdma_rw_unmap_sg(qp->pd->device, prot_sg, prot_sg_cnt, dir);
	rdma_rw_unmap_sg(qp->pd->device, sg, sg_cnt, dir);
पूर्ण
EXPORT_SYMBOL(rdma_rw_ctx_destroy_signature);

/**
 * rdma_rw_mr_factor - वापस number of MRs required क्रम a payload
 * @device:	device handling the connection
 * @port_num:	port num to which the connection is bound
 * @maxpages:	maximum payload pages per rdma_rw_ctx
 *
 * Returns the number of MRs the device requires to move @maxpayload
 * bytes. The वापसed value is used during transport creation to
 * compute max_rdma_ctxts and the size of the transport's Send and
 * Send Completion Queues.
 */
अचिन्हित पूर्णांक rdma_rw_mr_factor(काष्ठा ib_device *device, u32 port_num,
			       अचिन्हित पूर्णांक maxpages)
अणु
	अचिन्हित पूर्णांक mr_pages;

	अगर (rdma_rw_can_use_mr(device, port_num))
		mr_pages = rdma_rw_fr_page_list_len(device, false);
	अन्यथा
		mr_pages = device->attrs.max_sge_rd;
	वापस DIV_ROUND_UP(maxpages, mr_pages);
पूर्ण
EXPORT_SYMBOL(rdma_rw_mr_factor);

व्योम rdma_rw_init_qp(काष्ठा ib_device *dev, काष्ठा ib_qp_init_attr *attr)
अणु
	u32 factor;

	WARN_ON_ONCE(attr->port_num == 0);

	/*
	 * Each context needs at least one RDMA READ or WRITE WR.
	 *
	 * For some hardware we might need more, eventually we should ask the
	 * HCA driver क्रम a multiplier here.
	 */
	factor = 1;

	/*
	 * If the devices needs MRs to perक्रमm RDMA READ or WRITE operations,
	 * we'll need two additional MRs क्रम the registrations and the
	 * invalidation.
	 */
	अगर (attr->create_flags & IB_QP_CREATE_INTEGRITY_EN ||
	    rdma_rw_can_use_mr(dev, attr->port_num))
		factor += 2;	/* inv + reg */

	attr->cap.max_send_wr += factor * attr->cap.max_rdma_ctxs;

	/*
	 * But maybe we were just too high in the sky and the device करोesn't
	 * even support all we need, and we'll have to live with what we get..
	 */
	attr->cap.max_send_wr =
		min_t(u32, attr->cap.max_send_wr, dev->attrs.max_qp_wr);
पूर्ण

पूर्णांक rdma_rw_init_mrs(काष्ठा ib_qp *qp, काष्ठा ib_qp_init_attr *attr)
अणु
	काष्ठा ib_device *dev = qp->pd->device;
	u32 nr_mrs = 0, nr_sig_mrs = 0, max_num_sg = 0;
	पूर्णांक ret = 0;

	अगर (attr->create_flags & IB_QP_CREATE_INTEGRITY_EN) अणु
		nr_sig_mrs = attr->cap.max_rdma_ctxs;
		nr_mrs = attr->cap.max_rdma_ctxs;
		max_num_sg = rdma_rw_fr_page_list_len(dev, true);
	पूर्ण अन्यथा अगर (rdma_rw_can_use_mr(dev, attr->port_num)) अणु
		nr_mrs = attr->cap.max_rdma_ctxs;
		max_num_sg = rdma_rw_fr_page_list_len(dev, false);
	पूर्ण

	अगर (nr_mrs) अणु
		ret = ib_mr_pool_init(qp, &qp->rdma_mrs, nr_mrs,
				IB_MR_TYPE_MEM_REG,
				max_num_sg, 0);
		अगर (ret) अणु
			pr_err("%s: failed to allocated %d MRs\n",
				__func__, nr_mrs);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (nr_sig_mrs) अणु
		ret = ib_mr_pool_init(qp, &qp->sig_mrs, nr_sig_mrs,
				IB_MR_TYPE_INTEGRITY, max_num_sg, max_num_sg);
		अगर (ret) अणु
			pr_err("%s: failed to allocated %d SIG MRs\n",
				__func__, nr_sig_mrs);
			जाओ out_मुक्त_rdma_mrs;
		पूर्ण
	पूर्ण

	वापस 0;

out_मुक्त_rdma_mrs:
	ib_mr_pool_destroy(qp, &qp->rdma_mrs);
	वापस ret;
पूर्ण

व्योम rdma_rw_cleanup_mrs(काष्ठा ib_qp *qp)
अणु
	ib_mr_pool_destroy(qp, &qp->sig_mrs);
	ib_mr_pool_destroy(qp, &qp->rdma_mrs);
पूर्ण
