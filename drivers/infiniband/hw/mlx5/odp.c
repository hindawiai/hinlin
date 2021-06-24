<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_umem_odp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-resv.h>

#समावेश "mlx5_ib.h"
#समावेश "cmd.h"
#समावेश "qp.h"

#समावेश <linux/mlx5/eq.h>

/* Contains the details of a pagefault. */
काष्ठा mlx5_pagefault अणु
	u32			bytes_committed;
	u32			token;
	u8			event_subtype;
	u8			type;
	जोड़ अणु
		/* Initiator or send message responder pagefault details. */
		काष्ठा अणु
			/* Received packet size, only valid क्रम responders. */
			u32	packet_size;
			/*
			 * Number of resource holding WQE, depends on type.
			 */
			u32	wq_num;
			/*
			 * WQE index. Refers to either the send queue or
			 * receive queue, according to event_subtype.
			 */
			u16	wqe_index;
		पूर्ण wqe;
		/* RDMA responder pagefault details */
		काष्ठा अणु
			u32	r_key;
			/*
			 * Received packet size, minimal size page fault
			 * resolution required क्रम क्रमward progress.
			 */
			u32	packet_size;
			u32	rdma_op_len;
			u64	rdma_va;
		पूर्ण rdma;
	पूर्ण;

	काष्ठा mlx5_ib_pf_eq	*eq;
	काष्ठा work_काष्ठा	work;
पूर्ण;

#घोषणा MAX_PREFETCH_LEN (4*1024*1024U)

/* Timeout in ms to रुको क्रम an active mmu notअगरier to complete when handling
 * a pagefault. */
#घोषणा MMU_NOTIFIER_TIMEOUT 1000

#घोषणा MLX5_IMR_MTT_BITS (30 - PAGE_SHIFT)
#घोषणा MLX5_IMR_MTT_SHIFT (MLX5_IMR_MTT_BITS + PAGE_SHIFT)
#घोषणा MLX5_IMR_MTT_ENTRIES BIT_ULL(MLX5_IMR_MTT_BITS)
#घोषणा MLX5_IMR_MTT_SIZE BIT_ULL(MLX5_IMR_MTT_SHIFT)
#घोषणा MLX5_IMR_MTT_MASK (~(MLX5_IMR_MTT_SIZE - 1))

#घोषणा MLX5_KSM_PAGE_SHIFT MLX5_IMR_MTT_SHIFT

अटल u64 mlx5_imr_ksm_entries;

अटल व्योम populate_klm(काष्ठा mlx5_klm *pklm, माप_प्रकार idx, माप_प्रकार nentries,
			काष्ठा mlx5_ib_mr *imr, पूर्णांक flags)
अणु
	काष्ठा mlx5_klm *end = pklm + nentries;

	अगर (flags & MLX5_IB_UPD_XLT_ZAP) अणु
		क्रम (; pklm != end; pklm++, idx++) अणु
			pklm->bcount = cpu_to_be32(MLX5_IMR_MTT_SIZE);
			pklm->key = cpu_to_be32(mr_to_mdev(imr)->null_mkey);
			pklm->va = 0;
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * The locking here is pretty subtle. Ideally the implicit_children
	 * xarray would be रक्षित by the umem_mutex, however that is not
	 * possible. Instead this uses a weaker update-then-lock pattern:
	 *
	 *    xa_store()
	 *    mutex_lock(umem_mutex)
	 *     mlx5_ib_update_xlt()
	 *    mutex_unlock(umem_mutex)
	 *    destroy lkey
	 *
	 * ie any change the xarray must be followed by the locked update_xlt
	 * beक्रमe destroying.
	 *
	 * The umem_mutex provides the acquire/release semantic needed to make
	 * the xa_store() visible to a racing thपढ़ो.
	 */
	lockdep_निश्चित_held(&to_ib_umem_odp(imr->umem)->umem_mutex);

	क्रम (; pklm != end; pklm++, idx++) अणु
		काष्ठा mlx5_ib_mr *mtt = xa_load(&imr->implicit_children, idx);

		pklm->bcount = cpu_to_be32(MLX5_IMR_MTT_SIZE);
		अगर (mtt) अणु
			pklm->key = cpu_to_be32(mtt->ibmr.lkey);
			pklm->va = cpu_to_be64(idx * MLX5_IMR_MTT_SIZE);
		पूर्ण अन्यथा अणु
			pklm->key = cpu_to_be32(mr_to_mdev(imr)->null_mkey);
			pklm->va = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल u64 umem_dma_to_mtt(dma_addr_t umem_dma)
अणु
	u64 mtt_entry = umem_dma & ODP_DMA_ADDR_MASK;

	अगर (umem_dma & ODP_READ_ALLOWED_BIT)
		mtt_entry |= MLX5_IB_MTT_READ;
	अगर (umem_dma & ODP_WRITE_ALLOWED_BIT)
		mtt_entry |= MLX5_IB_MTT_WRITE;

	वापस mtt_entry;
पूर्ण

अटल व्योम populate_mtt(__be64 *pas, माप_प्रकार idx, माप_प्रकार nentries,
			 काष्ठा mlx5_ib_mr *mr, पूर्णांक flags)
अणु
	काष्ठा ib_umem_odp *odp = to_ib_umem_odp(mr->umem);
	dma_addr_t pa;
	माप_प्रकार i;

	अगर (flags & MLX5_IB_UPD_XLT_ZAP)
		वापस;

	क्रम (i = 0; i < nentries; i++) अणु
		pa = odp->dma_list[idx + i];
		pas[i] = cpu_to_be64(umem_dma_to_mtt(pa));
	पूर्ण
पूर्ण

व्योम mlx5_odp_populate_xlt(व्योम *xlt, माप_प्रकार idx, माप_प्रकार nentries,
			   काष्ठा mlx5_ib_mr *mr, पूर्णांक flags)
अणु
	अगर (flags & MLX5_IB_UPD_XLT_INसूचीECT) अणु
		populate_klm(xlt, idx, nentries, mr, flags);
	पूर्ण अन्यथा अणु
		populate_mtt(xlt, idx, nentries, mr, flags);
	पूर्ण
पूर्ण

/*
 * This must be called after the mr has been हटाओd from implicit_children.
 * NOTE: The MR करोes not necessarily have to be
 * empty here, parallel page faults could have raced with the मुक्त process and
 * added pages to it.
 */
अटल व्योम मुक्त_implicit_child_mr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_ib_mr *mr =
		container_of(work, काष्ठा mlx5_ib_mr, odp_destroy.work);
	काष्ठा mlx5_ib_mr *imr = mr->parent;
	काष्ठा ib_umem_odp *odp_imr = to_ib_umem_odp(imr->umem);
	काष्ठा ib_umem_odp *odp = to_ib_umem_odp(mr->umem);

	mlx5r_deref_रुको_odp_mkey(&mr->mmkey);

	mutex_lock(&odp_imr->umem_mutex);
	mlx5_ib_update_xlt(mr->parent, ib_umem_start(odp) >> MLX5_IMR_MTT_SHIFT,
			   1, 0,
			   MLX5_IB_UPD_XLT_INसूचीECT | MLX5_IB_UPD_XLT_ATOMIC);
	mutex_unlock(&odp_imr->umem_mutex);
	mlx5_ib_dereg_mr(&mr->ibmr, शून्य);

	mlx5r_deref_odp_mkey(&imr->mmkey);
पूर्ण

अटल व्योम destroy_unused_implicit_child_mr(काष्ठा mlx5_ib_mr *mr)
अणु
	काष्ठा ib_umem_odp *odp = to_ib_umem_odp(mr->umem);
	अचिन्हित दीर्घ idx = ib_umem_start(odp) >> MLX5_IMR_MTT_SHIFT;
	काष्ठा mlx5_ib_mr *imr = mr->parent;

	अगर (!refcount_inc_not_zero(&imr->mmkey.usecount))
		वापस;

	xa_erase(&imr->implicit_children, idx);

	/* Freeing a MR is a sleeping operation, so bounce to a work queue */
	INIT_WORK(&mr->odp_destroy.work, मुक्त_implicit_child_mr_work);
	queue_work(प्रणाली_unbound_wq, &mr->odp_destroy.work);
पूर्ण

अटल bool mlx5_ib_invalidate_range(काष्ठा mmu_पूर्णांकerval_notअगरier *mni,
				     स्थिर काष्ठा mmu_notअगरier_range *range,
				     अचिन्हित दीर्घ cur_seq)
अणु
	काष्ठा ib_umem_odp *umem_odp =
		container_of(mni, काष्ठा ib_umem_odp, notअगरier);
	काष्ठा mlx5_ib_mr *mr;
	स्थिर u64 umr_block_mask = (MLX5_UMR_MTT_ALIGNMENT /
				    माप(काष्ठा mlx5_mtt)) - 1;
	u64 idx = 0, blk_start_idx = 0;
	u64 invalidations = 0;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	पूर्णांक in_block = 0;
	u64 addr;

	अगर (!mmu_notअगरier_range_blockable(range))
		वापस false;

	mutex_lock(&umem_odp->umem_mutex);
	mmu_पूर्णांकerval_set_seq(mni, cur_seq);
	/*
	 * If npages is zero then umem_odp->निजी may not be setup yet. This
	 * करोes not complete until after the first page is mapped क्रम DMA.
	 */
	अगर (!umem_odp->npages)
		जाओ out;
	mr = umem_odp->निजी;

	start = max_t(u64, ib_umem_start(umem_odp), range->start);
	end = min_t(u64, ib_umem_end(umem_odp), range->end);

	/*
	 * Iteration one - zap the HW's MTTs. The notअगरiers_count ensures that
	 * जबतक we are करोing the invalidation, no page fault will attempt to
	 * overग_लिखो the same MTTs.  Concurent invalidations might race us,
	 * but they will ग_लिखो 0s as well, so no dअगरference in the end result.
	 */
	क्रम (addr = start; addr < end; addr += BIT(umem_odp->page_shअगरt)) अणु
		idx = (addr - ib_umem_start(umem_odp)) >> umem_odp->page_shअगरt;
		/*
		 * Strive to ग_लिखो the MTTs in chunks, but aव्योम overwriting
		 * non-existing MTTs. The huristic here can be improved to
		 * estimate the cost of another UMR vs. the cost of bigger
		 * UMR.
		 */
		अगर (umem_odp->dma_list[idx] &
		    (ODP_READ_ALLOWED_BIT | ODP_WRITE_ALLOWED_BIT)) अणु
			अगर (!in_block) अणु
				blk_start_idx = idx;
				in_block = 1;
			पूर्ण

			/* Count page invalidations */
			invalidations += idx - blk_start_idx + 1;
		पूर्ण अन्यथा अणु
			u64 umr_offset = idx & umr_block_mask;

			अगर (in_block && umr_offset == 0) अणु
				mlx5_ib_update_xlt(mr, blk_start_idx,
						   idx - blk_start_idx, 0,
						   MLX5_IB_UPD_XLT_ZAP |
						   MLX5_IB_UPD_XLT_ATOMIC);
				in_block = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (in_block)
		mlx5_ib_update_xlt(mr, blk_start_idx,
				   idx - blk_start_idx + 1, 0,
				   MLX5_IB_UPD_XLT_ZAP |
				   MLX5_IB_UPD_XLT_ATOMIC);

	mlx5_update_odp_stats(mr, invalidations, invalidations);

	/*
	 * We are now sure that the device will not access the
	 * memory. We can safely unmap it, and mark it as dirty अगर
	 * needed.
	 */

	ib_umem_odp_unmap_dma_pages(umem_odp, start, end);

	अगर (unlikely(!umem_odp->npages && mr->parent))
		destroy_unused_implicit_child_mr(mr);
out:
	mutex_unlock(&umem_odp->umem_mutex);
	वापस true;
पूर्ण

स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops mlx5_mn_ops = अणु
	.invalidate = mlx5_ib_invalidate_range,
पूर्ण;

अटल व्योम पूर्णांकernal_fill_odp_caps(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा ib_odp_caps *caps = &dev->odp_caps;

	स_रखो(caps, 0, माप(*caps));

	अगर (!MLX5_CAP_GEN(dev->mdev, pg) ||
	    !mlx5_ib_can_load_pas_with_umr(dev, 0))
		वापस;

	caps->general_caps = IB_ODP_SUPPORT;

	अगर (MLX5_CAP_GEN(dev->mdev, umr_extended_translation_offset))
		dev->odp_max_size = U64_MAX;
	अन्यथा
		dev->odp_max_size = BIT_ULL(MLX5_MAX_UMR_SHIFT + PAGE_SHIFT);

	अगर (MLX5_CAP_ODP(dev->mdev, ud_odp_caps.send))
		caps->per_transport_caps.ud_odp_caps |= IB_ODP_SUPPORT_SEND;

	अगर (MLX5_CAP_ODP(dev->mdev, ud_odp_caps.srq_receive))
		caps->per_transport_caps.ud_odp_caps |= IB_ODP_SUPPORT_SRQ_RECV;

	अगर (MLX5_CAP_ODP(dev->mdev, rc_odp_caps.send))
		caps->per_transport_caps.rc_odp_caps |= IB_ODP_SUPPORT_SEND;

	अगर (MLX5_CAP_ODP(dev->mdev, rc_odp_caps.receive))
		caps->per_transport_caps.rc_odp_caps |= IB_ODP_SUPPORT_RECV;

	अगर (MLX5_CAP_ODP(dev->mdev, rc_odp_caps.ग_लिखो))
		caps->per_transport_caps.rc_odp_caps |= IB_ODP_SUPPORT_WRITE;

	अगर (MLX5_CAP_ODP(dev->mdev, rc_odp_caps.पढ़ो))
		caps->per_transport_caps.rc_odp_caps |= IB_ODP_SUPPORT_READ;

	अगर (MLX5_CAP_ODP(dev->mdev, rc_odp_caps.atomic))
		caps->per_transport_caps.rc_odp_caps |= IB_ODP_SUPPORT_ATOMIC;

	अगर (MLX5_CAP_ODP(dev->mdev, rc_odp_caps.srq_receive))
		caps->per_transport_caps.rc_odp_caps |= IB_ODP_SUPPORT_SRQ_RECV;

	अगर (MLX5_CAP_ODP(dev->mdev, xrc_odp_caps.send))
		caps->per_transport_caps.xrc_odp_caps |= IB_ODP_SUPPORT_SEND;

	अगर (MLX5_CAP_ODP(dev->mdev, xrc_odp_caps.receive))
		caps->per_transport_caps.xrc_odp_caps |= IB_ODP_SUPPORT_RECV;

	अगर (MLX5_CAP_ODP(dev->mdev, xrc_odp_caps.ग_लिखो))
		caps->per_transport_caps.xrc_odp_caps |= IB_ODP_SUPPORT_WRITE;

	अगर (MLX5_CAP_ODP(dev->mdev, xrc_odp_caps.पढ़ो))
		caps->per_transport_caps.xrc_odp_caps |= IB_ODP_SUPPORT_READ;

	अगर (MLX5_CAP_ODP(dev->mdev, xrc_odp_caps.atomic))
		caps->per_transport_caps.xrc_odp_caps |= IB_ODP_SUPPORT_ATOMIC;

	अगर (MLX5_CAP_ODP(dev->mdev, xrc_odp_caps.srq_receive))
		caps->per_transport_caps.xrc_odp_caps |= IB_ODP_SUPPORT_SRQ_RECV;

	अगर (MLX5_CAP_GEN(dev->mdev, fixed_buffer_size) &&
	    MLX5_CAP_GEN(dev->mdev, null_mkey) &&
	    MLX5_CAP_GEN(dev->mdev, umr_extended_translation_offset) &&
	    !MLX5_CAP_GEN(dev->mdev, umr_indirect_mkey_disabled))
		caps->general_caps |= IB_ODP_SUPPORT_IMPLICIT;
पूर्ण

अटल व्योम mlx5_ib_page_fault_resume(काष्ठा mlx5_ib_dev *dev,
				      काष्ठा mlx5_pagefault *pfault,
				      पूर्णांक error)
अणु
	पूर्णांक wq_num = pfault->event_subtype == MLX5_PFAULT_SUBTYPE_WQE ?
		     pfault->wqe.wq_num : pfault->token;
	u32 in[MLX5_ST_SZ_DW(page_fault_resume_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(page_fault_resume_in, in, opcode, MLX5_CMD_OP_PAGE_FAULT_RESUME);
	MLX5_SET(page_fault_resume_in, in, page_fault_type, pfault->type);
	MLX5_SET(page_fault_resume_in, in, token, pfault->token);
	MLX5_SET(page_fault_resume_in, in, wq_number, wq_num);
	MLX5_SET(page_fault_resume_in, in, error, !!error);

	err = mlx5_cmd_exec_in(dev->mdev, page_fault_resume, in);
	अगर (err)
		mlx5_ib_err(dev, "Failed to resolve the page fault on WQ 0x%x err %d\n",
			    wq_num, err);
पूर्ण

अटल काष्ठा mlx5_ib_mr *implicit_get_child_mr(काष्ठा mlx5_ib_mr *imr,
						अचिन्हित दीर्घ idx)
अणु
	काष्ठा ib_umem_odp *odp;
	काष्ठा mlx5_ib_mr *mr;
	काष्ठा mlx5_ib_mr *ret;
	पूर्णांक err;

	odp = ib_umem_odp_alloc_child(to_ib_umem_odp(imr->umem),
				      idx * MLX5_IMR_MTT_SIZE,
				      MLX5_IMR_MTT_SIZE, &mlx5_mn_ops);
	अगर (IS_ERR(odp))
		वापस ERR_CAST(odp);

	ret = mr = mlx5_mr_cache_alloc(
		mr_to_mdev(imr), MLX5_IMR_MTT_CACHE_ENTRY, imr->access_flags);
	अगर (IS_ERR(mr)) अणु
		ib_umem_odp_release(odp);
		वापस mr;
	पूर्ण

	mr->ibmr.pd = imr->ibmr.pd;
	mr->ibmr.device = &mr_to_mdev(imr)->ib_dev;
	mr->umem = &odp->umem;
	mr->ibmr.lkey = mr->mmkey.key;
	mr->ibmr.rkey = mr->mmkey.key;
	mr->mmkey.iova = idx * MLX5_IMR_MTT_SIZE;
	mr->parent = imr;
	odp->निजी = mr;

	/*
	 * First refcount is owned by the xarray and second refconut
	 * is वापसed to the caller.
	 */
	refcount_set(&mr->mmkey.usecount, 2);

	err = mlx5_ib_update_xlt(mr, 0,
				 MLX5_IMR_MTT_ENTRIES,
				 PAGE_SHIFT,
				 MLX5_IB_UPD_XLT_ZAP |
				 MLX5_IB_UPD_XLT_ENABLE);
	अगर (err) अणु
		ret = ERR_PTR(err);
		जाओ out_mr;
	पूर्ण

	xa_lock(&imr->implicit_children);
	ret = __xa_cmpxchg(&imr->implicit_children, idx, शून्य, mr,
			   GFP_KERNEL);
	अगर (unlikely(ret)) अणु
		अगर (xa_is_err(ret)) अणु
			ret = ERR_PTR(xa_err(ret));
			जाओ out_lock;
		पूर्ण
		/*
		 * Another thपढ़ो beat us to creating the child mr, use
		 * theirs.
		 */
		refcount_inc(&ret->mmkey.usecount);
		जाओ out_lock;
	पूर्ण
	xa_unlock(&imr->implicit_children);

	mlx5_ib_dbg(mr_to_mdev(imr), "key %x mr %p\n", mr->mmkey.key, mr);
	वापस mr;

out_lock:
	xa_unlock(&imr->implicit_children);
out_mr:
	mlx5_ib_dereg_mr(&mr->ibmr, शून्य);
	वापस ret;
पूर्ण

काष्ठा mlx5_ib_mr *mlx5_ib_alloc_implicit_mr(काष्ठा mlx5_ib_pd *pd,
					     काष्ठा ib_udata *udata,
					     पूर्णांक access_flags)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->ibpd.device);
	काष्ठा ib_umem_odp *umem_odp;
	काष्ठा mlx5_ib_mr *imr;
	पूर्णांक err;

	अगर (!mlx5_ib_can_load_pas_with_umr(dev,
					   MLX5_IMR_MTT_ENTRIES * PAGE_SIZE))
		वापस ERR_PTR(-EOPNOTSUPP);

	umem_odp = ib_umem_odp_alloc_implicit(&dev->ib_dev, access_flags);
	अगर (IS_ERR(umem_odp))
		वापस ERR_CAST(umem_odp);

	imr = mlx5_mr_cache_alloc(dev, MLX5_IMR_KSM_CACHE_ENTRY, access_flags);
	अगर (IS_ERR(imr)) अणु
		ib_umem_odp_release(umem_odp);
		वापस imr;
	पूर्ण

	imr->ibmr.pd = &pd->ibpd;
	imr->mmkey.iova = 0;
	imr->umem = &umem_odp->umem;
	imr->ibmr.lkey = imr->mmkey.key;
	imr->ibmr.rkey = imr->mmkey.key;
	imr->ibmr.device = &dev->ib_dev;
	imr->umem = &umem_odp->umem;
	imr->is_odp_implicit = true;
	xa_init(&imr->implicit_children);

	err = mlx5_ib_update_xlt(imr, 0,
				 mlx5_imr_ksm_entries,
				 MLX5_KSM_PAGE_SHIFT,
				 MLX5_IB_UPD_XLT_INसूचीECT |
				 MLX5_IB_UPD_XLT_ZAP |
				 MLX5_IB_UPD_XLT_ENABLE);
	अगर (err)
		जाओ out_mr;

	err = mlx5r_store_odp_mkey(dev, &imr->mmkey);
	अगर (err)
		जाओ out_mr;

	mlx5_ib_dbg(dev, "key %x mr %p\n", imr->mmkey.key, imr);
	वापस imr;
out_mr:
	mlx5_ib_err(dev, "Failed to register MKEY %d\n", err);
	mlx5_ib_dereg_mr(&imr->ibmr, शून्य);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlx5_ib_मुक्त_odp_mr(काष्ठा mlx5_ib_mr *mr)
अणु
	काष्ठा mlx5_ib_mr *mtt;
	अचिन्हित दीर्घ idx;

	/*
	 * If this is an implicit MR it is alपढ़ोy invalidated so we can just
	 * delete the children mkeys.
	 */
	xa_क्रम_each(&mr->implicit_children, idx, mtt) अणु
		xa_erase(&mr->implicit_children, idx);
		mlx5_ib_dereg_mr(&mtt->ibmr, शून्य);
	पूर्ण
पूर्ण

#घोषणा MLX5_PF_FLAGS_DOWNGRADE BIT(1)
#घोषणा MLX5_PF_FLAGS_SNAPSHOT BIT(2)
#घोषणा MLX5_PF_FLAGS_ENABLE BIT(3)
अटल पूर्णांक pagefault_real_mr(काष्ठा mlx5_ib_mr *mr, काष्ठा ib_umem_odp *odp,
			     u64 user_va, माप_प्रकार bcnt, u32 *bytes_mapped,
			     u32 flags)
अणु
	पूर्णांक page_shअगरt, ret, np;
	bool करोwngrade = flags & MLX5_PF_FLAGS_DOWNGRADE;
	u64 access_mask;
	u64 start_idx;
	bool fault = !(flags & MLX5_PF_FLAGS_SNAPSHOT);
	u32 xlt_flags = MLX5_IB_UPD_XLT_ATOMIC;

	अगर (flags & MLX5_PF_FLAGS_ENABLE)
		xlt_flags |= MLX5_IB_UPD_XLT_ENABLE;

	page_shअगरt = odp->page_shअगरt;
	start_idx = (user_va - ib_umem_start(odp)) >> page_shअगरt;
	access_mask = ODP_READ_ALLOWED_BIT;

	अगर (odp->umem.writable && !करोwngrade)
		access_mask |= ODP_WRITE_ALLOWED_BIT;

	np = ib_umem_odp_map_dma_and_lock(odp, user_va, bcnt, access_mask, fault);
	अगर (np < 0)
		वापस np;

	/*
	 * No need to check whether the MTTs really beदीर्घ to this MR, since
	 * ib_umem_odp_map_dma_and_lock alपढ़ोy checks this.
	 */
	ret = mlx5_ib_update_xlt(mr, start_idx, np, page_shअगरt, xlt_flags);
	mutex_unlock(&odp->umem_mutex);

	अगर (ret < 0) अणु
		अगर (ret != -EAGAIN)
			mlx5_ib_err(mr_to_mdev(mr),
				    "Failed to update mkey page tables\n");
		जाओ out;
	पूर्ण

	अगर (bytes_mapped) अणु
		u32 new_mappings = (np << page_shअगरt) -
			(user_va - round_करोwn(user_va, 1 << page_shअगरt));

		*bytes_mapped += min_t(u32, new_mappings, bcnt);
	पूर्ण

	वापस np << (page_shअगरt - PAGE_SHIFT);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक pagefault_implicit_mr(काष्ठा mlx5_ib_mr *imr,
				 काष्ठा ib_umem_odp *odp_imr, u64 user_va,
				 माप_प्रकार bcnt, u32 *bytes_mapped, u32 flags)
अणु
	अचिन्हित दीर्घ end_idx = (user_va + bcnt - 1) >> MLX5_IMR_MTT_SHIFT;
	अचिन्हित दीर्घ upd_start_idx = end_idx + 1;
	अचिन्हित दीर्घ upd_len = 0;
	अचिन्हित दीर्घ npages = 0;
	पूर्णांक err;
	पूर्णांक ret;

	अगर (unlikely(user_va >= mlx5_imr_ksm_entries * MLX5_IMR_MTT_SIZE ||
		     mlx5_imr_ksm_entries * MLX5_IMR_MTT_SIZE - user_va < bcnt))
		वापस -EFAULT;

	/* Fault each child mr that पूर्णांकersects with our पूर्णांकerval. */
	जबतक (bcnt) अणु
		अचिन्हित दीर्घ idx = user_va >> MLX5_IMR_MTT_SHIFT;
		काष्ठा ib_umem_odp *umem_odp;
		काष्ठा mlx5_ib_mr *mtt;
		u64 len;

		xa_lock(&imr->implicit_children);
		mtt = xa_load(&imr->implicit_children, idx);
		अगर (unlikely(!mtt)) अणु
			xa_unlock(&imr->implicit_children);
			mtt = implicit_get_child_mr(imr, idx);
			अगर (IS_ERR(mtt)) अणु
				ret = PTR_ERR(mtt);
				जाओ out;
			पूर्ण
			upd_start_idx = min(upd_start_idx, idx);
			upd_len = idx - upd_start_idx + 1;
		पूर्ण अन्यथा अणु
			refcount_inc(&mtt->mmkey.usecount);
			xa_unlock(&imr->implicit_children);
		पूर्ण

		umem_odp = to_ib_umem_odp(mtt->umem);
		len = min_t(u64, user_va + bcnt, ib_umem_end(umem_odp)) -
		      user_va;

		ret = pagefault_real_mr(mtt, umem_odp, user_va, len,
					bytes_mapped, flags);

		mlx5r_deref_odp_mkey(&mtt->mmkey);

		अगर (ret < 0)
			जाओ out;
		user_va += len;
		bcnt -= len;
		npages += ret;
	पूर्ण

	ret = npages;

	/*
	 * Any समय the implicit_children are changed we must perक्रमm an
	 * update of the xlt beक्रमe निकासing to ensure the HW and the
	 * implicit_children reमुख्यs synchronized.
	 */
out:
	अगर (likely(!upd_len))
		वापस ret;

	/*
	 * Notice this is not strictly ordered right, the KSM is updated after
	 * the implicit_children is updated, so a parallel page fault could
	 * see a MR that is not yet visible in the KSM.  This is similar to a
	 * parallel page fault seeing a MR that is being concurrently हटाओd
	 * from the KSM. Both of these improbable situations are resolved
	 * safely by resuming the HW and then taking another page fault. The
	 * next pagefault handler will see the new inक्रमmation.
	 */
	mutex_lock(&odp_imr->umem_mutex);
	err = mlx5_ib_update_xlt(imr, upd_start_idx, upd_len, 0,
				 MLX5_IB_UPD_XLT_INसूचीECT |
					 MLX5_IB_UPD_XLT_ATOMIC);
	mutex_unlock(&odp_imr->umem_mutex);
	अगर (err) अणु
		mlx5_ib_err(mr_to_mdev(imr), "Failed to update PAS\n");
		वापस err;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक pagefault_dmabuf_mr(काष्ठा mlx5_ib_mr *mr, माप_प्रकार bcnt,
			       u32 *bytes_mapped, u32 flags)
अणु
	काष्ठा ib_umem_dmabuf *umem_dmabuf = to_ib_umem_dmabuf(mr->umem);
	u32 xlt_flags = 0;
	पूर्णांक err;
	अचिन्हित पूर्णांक page_size;

	अगर (flags & MLX5_PF_FLAGS_ENABLE)
		xlt_flags |= MLX5_IB_UPD_XLT_ENABLE;

	dma_resv_lock(umem_dmabuf->attach->dmabuf->resv, शून्य);
	err = ib_umem_dmabuf_map_pages(umem_dmabuf);
	अगर (err) अणु
		dma_resv_unlock(umem_dmabuf->attach->dmabuf->resv);
		वापस err;
	पूर्ण

	page_size = mlx5_umem_find_best_pgsz(&umem_dmabuf->umem, mkc,
					     log_page_size, 0,
					     umem_dmabuf->umem.iova);
	अगर (unlikely(page_size < PAGE_SIZE)) अणु
		ib_umem_dmabuf_unmap_pages(umem_dmabuf);
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		err = mlx5_ib_update_mr_pas(mr, xlt_flags);
	पूर्ण
	dma_resv_unlock(umem_dmabuf->attach->dmabuf->resv);

	अगर (err)
		वापस err;

	अगर (bytes_mapped)
		*bytes_mapped += bcnt;

	वापस ib_umem_num_pages(mr->umem);
पूर्ण

/*
 * Returns:
 *  -EFAULT: The io_virt->bcnt is not within the MR, it covers pages that are
 *           not accessible, or the MR is no दीर्घer valid.
 *  -EAGAIN/-ENOMEM: The operation should be retried
 *
 *  -EINVAL/others: General पूर्णांकernal malfunction
 *  >0: Number of pages mapped
 */
अटल पूर्णांक pagefault_mr(काष्ठा mlx5_ib_mr *mr, u64 io_virt, माप_प्रकार bcnt,
			u32 *bytes_mapped, u32 flags)
अणु
	काष्ठा ib_umem_odp *odp = to_ib_umem_odp(mr->umem);

	अगर (unlikely(io_virt < mr->mmkey.iova))
		वापस -EFAULT;

	अगर (mr->umem->is_dmabuf)
		वापस pagefault_dmabuf_mr(mr, bcnt, bytes_mapped, flags);

	अगर (!odp->is_implicit_odp) अणु
		u64 user_va;

		अगर (check_add_overflow(io_virt - mr->mmkey.iova,
				       (u64)odp->umem.address, &user_va))
			वापस -EFAULT;
		अगर (unlikely(user_va >= ib_umem_end(odp) ||
			     ib_umem_end(odp) - user_va < bcnt))
			वापस -EFAULT;
		वापस pagefault_real_mr(mr, odp, user_va, bcnt, bytes_mapped,
					 flags);
	पूर्ण
	वापस pagefault_implicit_mr(mr, odp, io_virt, bcnt, bytes_mapped,
				     flags);
पूर्ण

पूर्णांक mlx5_ib_init_odp_mr(काष्ठा mlx5_ib_mr *mr)
अणु
	पूर्णांक ret;

	ret = pagefault_real_mr(mr, to_ib_umem_odp(mr->umem), mr->umem->address,
				mr->umem->length, शून्य,
				MLX5_PF_FLAGS_SNAPSHOT | MLX5_PF_FLAGS_ENABLE);
	वापस ret >= 0 ? 0 : ret;
पूर्ण

पूर्णांक mlx5_ib_init_dmabuf_mr(काष्ठा mlx5_ib_mr *mr)
अणु
	पूर्णांक ret;

	ret = pagefault_dmabuf_mr(mr, mr->umem->length, शून्य,
				  MLX5_PF_FLAGS_ENABLE);

	वापस ret >= 0 ? 0 : ret;
पूर्ण

काष्ठा pf_frame अणु
	काष्ठा pf_frame *next;
	u32 key;
	u64 io_virt;
	माप_प्रकार bcnt;
	पूर्णांक depth;
पूर्ण;

अटल bool mkey_is_eq(काष्ठा mlx5_core_mkey *mmkey, u32 key)
अणु
	अगर (!mmkey)
		वापस false;
	अगर (mmkey->type == MLX5_MKEY_MW)
		वापस mlx5_base_mkey(mmkey->key) == mlx5_base_mkey(key);
	वापस mmkey->key == key;
पूर्ण

अटल पूर्णांक get_indirect_num_descs(काष्ठा mlx5_core_mkey *mmkey)
अणु
	काष्ठा mlx5_ib_mw *mw;
	काष्ठा mlx5_ib_devx_mr *devx_mr;

	अगर (mmkey->type == MLX5_MKEY_MW) अणु
		mw = container_of(mmkey, काष्ठा mlx5_ib_mw, mmkey);
		वापस mw->ndescs;
	पूर्ण

	devx_mr = container_of(mmkey, काष्ठा mlx5_ib_devx_mr,
			       mmkey);
	वापस devx_mr->ndescs;
पूर्ण

/*
 * Handle a single data segment in a page-fault WQE or RDMA region.
 *
 * Returns number of OS pages retrieved on success. The caller may जारी to
 * the next data segment.
 * Can वापस the following error codes:
 * -EAGAIN to designate a temporary error. The caller will पात handling the
 *  page fault and resolve it.
 * -EFAULT when there's an error mapping the requested pages. The caller will
 *  पात the page fault handling.
 */
अटल पूर्णांक pagefault_single_data_segment(काष्ठा mlx5_ib_dev *dev,
					 काष्ठा ib_pd *pd, u32 key,
					 u64 io_virt, माप_प्रकार bcnt,
					 u32 *bytes_committed,
					 u32 *bytes_mapped)
अणु
	पूर्णांक npages = 0, ret, i, outlen, cur_outlen = 0, depth = 0;
	काष्ठा pf_frame *head = शून्य, *frame;
	काष्ठा mlx5_core_mkey *mmkey;
	काष्ठा mlx5_ib_mr *mr;
	काष्ठा mlx5_klm *pklm;
	u32 *out = शून्य;
	माप_प्रकार offset;
	पूर्णांक ndescs;

	io_virt += *bytes_committed;
	bcnt -= *bytes_committed;

next_mr:
	xa_lock(&dev->odp_mkeys);
	mmkey = xa_load(&dev->odp_mkeys, mlx5_base_mkey(key));
	अगर (!mmkey) अणु
		xa_unlock(&dev->odp_mkeys);
		mlx5_ib_dbg(
			dev,
			"skipping non ODP MR (lkey=0x%06x) in page fault handler.\n",
			key);
		अगर (bytes_mapped)
			*bytes_mapped += bcnt;
		/*
		 * The user could specअगरy a SGL with multiple lkeys and only
		 * some of them are ODP. Treat the non-ODP ones as fully
		 * faulted.
		 */
		ret = 0;
		जाओ end;
	पूर्ण
	refcount_inc(&mmkey->usecount);
	xa_unlock(&dev->odp_mkeys);

	अगर (!mkey_is_eq(mmkey, key)) अणु
		mlx5_ib_dbg(dev, "failed to find mkey %x\n", key);
		ret = -EFAULT;
		जाओ end;
	पूर्ण

	चयन (mmkey->type) अणु
	हाल MLX5_MKEY_MR:
		mr = container_of(mmkey, काष्ठा mlx5_ib_mr, mmkey);

		ret = pagefault_mr(mr, io_virt, bcnt, bytes_mapped, 0);
		अगर (ret < 0)
			जाओ end;

		mlx5_update_odp_stats(mr, faults, ret);

		npages += ret;
		ret = 0;
		अवरोध;

	हाल MLX5_MKEY_MW:
	हाल MLX5_MKEY_INसूचीECT_DEVX:
		ndescs = get_indirect_num_descs(mmkey);

		अगर (depth >= MLX5_CAP_GEN(dev->mdev, max_indirection)) अणु
			mlx5_ib_dbg(dev, "indirection level exceeded\n");
			ret = -EFAULT;
			जाओ end;
		पूर्ण

		outlen = MLX5_ST_SZ_BYTES(query_mkey_out) +
			माप(*pklm) * (ndescs - 2);

		अगर (outlen > cur_outlen) अणु
			kमुक्त(out);
			out = kzalloc(outlen, GFP_KERNEL);
			अगर (!out) अणु
				ret = -ENOMEM;
				जाओ end;
			पूर्ण
			cur_outlen = outlen;
		पूर्ण

		pklm = (काष्ठा mlx5_klm *)MLX5_ADDR_OF(query_mkey_out, out,
						       bsf0_klm0_pas_mtt0_1);

		ret = mlx5_core_query_mkey(dev->mdev, mmkey, out, outlen);
		अगर (ret)
			जाओ end;

		offset = io_virt - MLX5_GET64(query_mkey_out, out,
					      memory_key_mkey_entry.start_addr);

		क्रम (i = 0; bcnt && i < ndescs; i++, pklm++) अणु
			अगर (offset >= be32_to_cpu(pklm->bcount)) अणु
				offset -= be32_to_cpu(pklm->bcount);
				जारी;
			पूर्ण

			frame = kzalloc(माप(*frame), GFP_KERNEL);
			अगर (!frame) अणु
				ret = -ENOMEM;
				जाओ end;
			पूर्ण

			frame->key = be32_to_cpu(pklm->key);
			frame->io_virt = be64_to_cpu(pklm->va) + offset;
			frame->bcnt = min_t(माप_प्रकार, bcnt,
					    be32_to_cpu(pklm->bcount) - offset);
			frame->depth = depth + 1;
			frame->next = head;
			head = frame;

			bcnt -= frame->bcnt;
			offset = 0;
		पूर्ण
		अवरोध;

	शेष:
		mlx5_ib_dbg(dev, "wrong mkey type %d\n", mmkey->type);
		ret = -EFAULT;
		जाओ end;
	पूर्ण

	अगर (head) अणु
		frame = head;
		head = frame->next;

		key = frame->key;
		io_virt = frame->io_virt;
		bcnt = frame->bcnt;
		depth = frame->depth;
		kमुक्त(frame);

		mlx5r_deref_odp_mkey(mmkey);
		जाओ next_mr;
	पूर्ण

end:
	अगर (mmkey)
		mlx5r_deref_odp_mkey(mmkey);
	जबतक (head) अणु
		frame = head;
		head = frame->next;
		kमुक्त(frame);
	पूर्ण
	kमुक्त(out);

	*bytes_committed = 0;
	वापस ret ? ret : npages;
पूर्ण

/*
 * Parse a series of data segments क्रम page fault handling.
 *
 * @dev:  Poपूर्णांकer to mlx5 IB device
 * @pfault: contains page fault inक्रमmation.
 * @wqe: poपूर्णांकs at the first data segment in the WQE.
 * @wqe_end: poपूर्णांकs after the end of the WQE.
 * @bytes_mapped: receives the number of bytes that the function was able to
 *                map. This allows the caller to decide पूर्णांकelligently whether
 *                enough memory was mapped to resolve the page fault
 *                successfully (e.g. enough क्रम the next MTU, or the entire
 *                WQE).
 * @total_wqe_bytes: receives the total data size of this WQE in bytes (minus
 *                   the committed bytes).
 * @receive_queue: receive WQE end of sg list
 *
 * Returns the number of pages loaded अगर positive, zero क्रम an empty WQE, or a
 * negative error code.
 */
अटल पूर्णांक pagefault_data_segments(काष्ठा mlx5_ib_dev *dev,
				   काष्ठा mlx5_pagefault *pfault,
				   व्योम *wqe,
				   व्योम *wqe_end, u32 *bytes_mapped,
				   u32 *total_wqe_bytes, bool receive_queue)
अणु
	पूर्णांक ret = 0, npages = 0;
	u64 io_virt;
	u32 key;
	u32 byte_count;
	माप_प्रकार bcnt;
	पूर्णांक अंतरभूत_segment;

	अगर (bytes_mapped)
		*bytes_mapped = 0;
	अगर (total_wqe_bytes)
		*total_wqe_bytes = 0;

	जबतक (wqe < wqe_end) अणु
		काष्ठा mlx5_wqe_data_seg *dseg = wqe;

		io_virt = be64_to_cpu(dseg->addr);
		key = be32_to_cpu(dseg->lkey);
		byte_count = be32_to_cpu(dseg->byte_count);
		अंतरभूत_segment = !!(byte_count &  MLX5_INLINE_SEG);
		bcnt	       = byte_count & ~MLX5_INLINE_SEG;

		अगर (अंतरभूत_segment) अणु
			bcnt = bcnt & MLX5_WQE_INLINE_SEG_BYTE_COUNT_MASK;
			wqe += ALIGN(माप(काष्ठा mlx5_wqe_अंतरभूत_seg) + bcnt,
				     16);
		पूर्ण अन्यथा अणु
			wqe += माप(*dseg);
		पूर्ण

		/* receive WQE end of sg list. */
		अगर (receive_queue && bcnt == 0 && key == MLX5_INVALID_LKEY &&
		    io_virt == 0)
			अवरोध;

		अगर (!अंतरभूत_segment && total_wqe_bytes) अणु
			*total_wqe_bytes += bcnt - min_t(माप_प्रकार, bcnt,
					pfault->bytes_committed);
		पूर्ण

		/* A zero length data segment designates a length of 2GB. */
		अगर (bcnt == 0)
			bcnt = 1U << 31;

		अगर (अंतरभूत_segment || bcnt <= pfault->bytes_committed) अणु
			pfault->bytes_committed -=
				min_t(माप_प्रकार, bcnt,
				      pfault->bytes_committed);
			जारी;
		पूर्ण

		ret = pagefault_single_data_segment(dev, शून्य, key,
						    io_virt, bcnt,
						    &pfault->bytes_committed,
						    bytes_mapped);
		अगर (ret < 0)
			अवरोध;
		npages += ret;
	पूर्ण

	वापस ret < 0 ? ret : npages;
पूर्ण

/*
 * Parse initiator WQE. Advances the wqe poपूर्णांकer to poपूर्णांक at the
 * scatter-gather list, and set wqe_end to the end of the WQE.
 */
अटल पूर्णांक mlx5_ib_mr_initiator_pfault_handler(
	काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_pagefault *pfault,
	काष्ठा mlx5_ib_qp *qp, व्योम **wqe, व्योम **wqe_end, पूर्णांक wqe_length)
अणु
	काष्ठा mlx5_wqe_ctrl_seg *ctrl = *wqe;
	u16 wqe_index = pfault->wqe.wqe_index;
	काष्ठा mlx5_base_av *av;
	अचिन्हित ds, opcode;
	u32 qpn = qp->trans_qp.base.mqp.qpn;

	ds = be32_to_cpu(ctrl->qpn_ds) & MLX5_WQE_CTRL_DS_MASK;
	अगर (ds * MLX5_WQE_DS_UNITS > wqe_length) अणु
		mlx5_ib_err(dev, "Unable to read the complete WQE. ds = 0x%x, ret = 0x%x\n",
			    ds, wqe_length);
		वापस -EFAULT;
	पूर्ण

	अगर (ds == 0) अणु
		mlx5_ib_err(dev, "Got WQE with zero DS. wqe_index=%x, qpn=%x\n",
			    wqe_index, qpn);
		वापस -EFAULT;
	पूर्ण

	*wqe_end = *wqe + ds * MLX5_WQE_DS_UNITS;
	*wqe += माप(*ctrl);

	opcode = be32_to_cpu(ctrl->opmod_idx_opcode) &
		 MLX5_WQE_CTRL_OPCODE_MASK;

	अगर (qp->ibqp.qp_type == IB_QPT_XRC_INI)
		*wqe += माप(काष्ठा mlx5_wqe_xrc_seg);

	अगर (qp->type == IB_QPT_UD || qp->type == MLX5_IB_QPT_DCI) अणु
		av = *wqe;
		अगर (av->dqp_dct & cpu_to_be32(MLX5_EXTENDED_UD_AV))
			*wqe += माप(काष्ठा mlx5_av);
		अन्यथा
			*wqe += माप(काष्ठा mlx5_base_av);
	पूर्ण

	चयन (opcode) अणु
	हाल MLX5_OPCODE_RDMA_WRITE:
	हाल MLX5_OPCODE_RDMA_WRITE_IMM:
	हाल MLX5_OPCODE_RDMA_READ:
		*wqe += माप(काष्ठा mlx5_wqe_raddr_seg);
		अवरोध;
	हाल MLX5_OPCODE_ATOMIC_CS:
	हाल MLX5_OPCODE_ATOMIC_FA:
		*wqe += माप(काष्ठा mlx5_wqe_raddr_seg);
		*wqe += माप(काष्ठा mlx5_wqe_atomic_seg);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Parse responder WQE and set wqe_end to the end of the WQE.
 */
अटल पूर्णांक mlx5_ib_mr_responder_pfault_handler_srq(काष्ठा mlx5_ib_dev *dev,
						   काष्ठा mlx5_ib_srq *srq,
						   व्योम **wqe, व्योम **wqe_end,
						   पूर्णांक wqe_length)
अणु
	पूर्णांक wqe_size = 1 << srq->msrq.wqe_shअगरt;

	अगर (wqe_size > wqe_length) अणु
		mlx5_ib_err(dev, "Couldn't read all of the receive WQE's content\n");
		वापस -EFAULT;
	पूर्ण

	*wqe_end = *wqe + wqe_size;
	*wqe += माप(काष्ठा mlx5_wqe_srq_next_seg);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ib_mr_responder_pfault_handler_rq(काष्ठा mlx5_ib_dev *dev,
						  काष्ठा mlx5_ib_qp *qp,
						  व्योम *wqe, व्योम **wqe_end,
						  पूर्णांक wqe_length)
अणु
	काष्ठा mlx5_ib_wq *wq = &qp->rq;
	पूर्णांक wqe_size = 1 << wq->wqe_shअगरt;

	अगर (qp->flags_en & MLX5_QP_FLAG_SIGNATURE) अणु
		mlx5_ib_err(dev, "ODP fault with WQE signatures is not supported\n");
		वापस -EFAULT;
	पूर्ण

	अगर (wqe_size > wqe_length) अणु
		mlx5_ib_err(dev, "Couldn't read all of the receive WQE's content\n");
		वापस -EFAULT;
	पूर्ण

	*wqe_end = wqe + wqe_size;

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा mlx5_core_rsc_common *odp_get_rsc(काष्ठा mlx5_ib_dev *dev,
						       u32 wq_num, पूर्णांक pf_type)
अणु
	काष्ठा mlx5_core_rsc_common *common = शून्य;
	काष्ठा mlx5_core_srq *srq;

	चयन (pf_type) अणु
	हाल MLX5_WQE_PF_TYPE_RMP:
		srq = mlx5_cmd_get_srq(dev, wq_num);
		अगर (srq)
			common = &srq->common;
		अवरोध;
	हाल MLX5_WQE_PF_TYPE_REQ_SEND_OR_WRITE:
	हाल MLX5_WQE_PF_TYPE_RESP:
	हाल MLX5_WQE_PF_TYPE_REQ_READ_OR_ATOMIC:
		common = mlx5_core_res_hold(dev, wq_num, MLX5_RES_QP);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस common;
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_qp *res_to_qp(काष्ठा mlx5_core_rsc_common *res)
अणु
	काष्ठा mlx5_core_qp *mqp = (काष्ठा mlx5_core_qp *)res;

	वापस to_mibqp(mqp);
पूर्ण

अटल अंतरभूत काष्ठा mlx5_ib_srq *res_to_srq(काष्ठा mlx5_core_rsc_common *res)
अणु
	काष्ठा mlx5_core_srq *msrq =
		container_of(res, काष्ठा mlx5_core_srq, common);

	वापस to_mibsrq(msrq);
पूर्ण

अटल व्योम mlx5_ib_mr_wqe_pfault_handler(काष्ठा mlx5_ib_dev *dev,
					  काष्ठा mlx5_pagefault *pfault)
अणु
	bool sq = pfault->type & MLX5_PFAULT_REQUESTOR;
	u16 wqe_index = pfault->wqe.wqe_index;
	व्योम *wqe, *wqe_start = शून्य, *wqe_end = शून्य;
	u32 bytes_mapped, total_wqe_bytes;
	काष्ठा mlx5_core_rsc_common *res;
	पूर्णांक resume_with_error = 1;
	काष्ठा mlx5_ib_qp *qp;
	माप_प्रकार bytes_copied;
	पूर्णांक ret = 0;

	res = odp_get_rsc(dev, pfault->wqe.wq_num, pfault->type);
	अगर (!res) अणु
		mlx5_ib_dbg(dev, "wqe page fault for missing resource %d\n", pfault->wqe.wq_num);
		वापस;
	पूर्ण

	अगर (res->res != MLX5_RES_QP && res->res != MLX5_RES_SRQ &&
	    res->res != MLX5_RES_XSRQ) अणु
		mlx5_ib_err(dev, "wqe page fault for unsupported type %d\n",
			    pfault->type);
		जाओ resolve_page_fault;
	पूर्ण

	wqe_start = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!wqe_start) अणु
		mlx5_ib_err(dev, "Error allocating memory for IO page fault handling.\n");
		जाओ resolve_page_fault;
	पूर्ण

	wqe = wqe_start;
	qp = (res->res == MLX5_RES_QP) ? res_to_qp(res) : शून्य;
	अगर (qp && sq) अणु
		ret = mlx5_ib_पढ़ो_wqe_sq(qp, wqe_index, wqe, PAGE_SIZE,
					  &bytes_copied);
		अगर (ret)
			जाओ पढ़ो_user;
		ret = mlx5_ib_mr_initiator_pfault_handler(
			dev, pfault, qp, &wqe, &wqe_end, bytes_copied);
	पूर्ण अन्यथा अगर (qp && !sq) अणु
		ret = mlx5_ib_पढ़ो_wqe_rq(qp, wqe_index, wqe, PAGE_SIZE,
					  &bytes_copied);
		अगर (ret)
			जाओ पढ़ो_user;
		ret = mlx5_ib_mr_responder_pfault_handler_rq(
			dev, qp, wqe, &wqe_end, bytes_copied);
	पूर्ण अन्यथा अगर (!qp) अणु
		काष्ठा mlx5_ib_srq *srq = res_to_srq(res);

		ret = mlx5_ib_पढ़ो_wqe_srq(srq, wqe_index, wqe, PAGE_SIZE,
					   &bytes_copied);
		अगर (ret)
			जाओ पढ़ो_user;
		ret = mlx5_ib_mr_responder_pfault_handler_srq(
			dev, srq, &wqe, &wqe_end, bytes_copied);
	पूर्ण

	अगर (ret < 0 || wqe >= wqe_end)
		जाओ resolve_page_fault;

	ret = pagefault_data_segments(dev, pfault, wqe, wqe_end, &bytes_mapped,
				      &total_wqe_bytes, !sq);
	अगर (ret == -EAGAIN)
		जाओ out;

	अगर (ret < 0 || total_wqe_bytes > bytes_mapped)
		जाओ resolve_page_fault;

out:
	ret = 0;
	resume_with_error = 0;

पढ़ो_user:
	अगर (ret)
		mlx5_ib_err(
			dev,
			"Failed reading a WQE following page fault, error %d, wqe_index %x, qpn %x\n",
			ret, wqe_index, pfault->token);

resolve_page_fault:
	mlx5_ib_page_fault_resume(dev, pfault, resume_with_error);
	mlx5_ib_dbg(dev, "PAGE FAULT completed. QP 0x%x resume_with_error=%d, type: 0x%x\n",
		    pfault->wqe.wq_num, resume_with_error,
		    pfault->type);
	mlx5_core_res_put(res);
	मुक्त_page((अचिन्हित दीर्घ)wqe_start);
पूर्ण

अटल पूर्णांक pages_in_range(u64 address, u32 length)
अणु
	वापस (ALIGN(address + length, PAGE_SIZE) -
		(address & PAGE_MASK)) >> PAGE_SHIFT;
पूर्ण

अटल व्योम mlx5_ib_mr_rdma_pfault_handler(काष्ठा mlx5_ib_dev *dev,
					   काष्ठा mlx5_pagefault *pfault)
अणु
	u64 address;
	u32 length;
	u32 prefetch_len = pfault->bytes_committed;
	पूर्णांक prefetch_activated = 0;
	u32 rkey = pfault->rdma.r_key;
	पूर्णांक ret;

	/* The RDMA responder handler handles the page fault in two parts.
	 * First it brings the necessary pages क्रम the current packet
	 * (and uses the pfault context), and then (after resuming the QP)
	 * prefetches more pages. The second operation cannot use the pfault
	 * context and thereक्रमe uses the dummy_pfault context allocated on
	 * the stack */
	pfault->rdma.rdma_va += pfault->bytes_committed;
	pfault->rdma.rdma_op_len -= min(pfault->bytes_committed,
					 pfault->rdma.rdma_op_len);
	pfault->bytes_committed = 0;

	address = pfault->rdma.rdma_va;
	length  = pfault->rdma.rdma_op_len;

	/* For some operations, the hardware cannot tell the exact message
	 * length, and in those हालs it reports zero. Use prefetch
	 * logic. */
	अगर (length == 0) अणु
		prefetch_activated = 1;
		length = pfault->rdma.packet_size;
		prefetch_len = min(MAX_PREFETCH_LEN, prefetch_len);
	पूर्ण

	ret = pagefault_single_data_segment(dev, शून्य, rkey, address, length,
					    &pfault->bytes_committed, शून्य);
	अगर (ret == -EAGAIN) अणु
		/* We're racing with an invalidation, don't prefetch */
		prefetch_activated = 0;
	पूर्ण अन्यथा अगर (ret < 0 || pages_in_range(address, length) > ret) अणु
		mlx5_ib_page_fault_resume(dev, pfault, 1);
		अगर (ret != -ENOENT)
			mlx5_ib_dbg(dev, "PAGE FAULT error %d. QP 0x%x, type: 0x%x\n",
				    ret, pfault->token, pfault->type);
		वापस;
	पूर्ण

	mlx5_ib_page_fault_resume(dev, pfault, 0);
	mlx5_ib_dbg(dev, "PAGE FAULT completed. QP 0x%x, type: 0x%x, prefetch_activated: %d\n",
		    pfault->token, pfault->type,
		    prefetch_activated);

	/* At this poपूर्णांक, there might be a new pagefault alपढ़ोy arriving in
	 * the eq, चयन to the dummy pagefault क्रम the rest of the
	 * processing. We're still OK with the objects being alive as the
	 * work-queue is being fenced. */

	अगर (prefetch_activated) अणु
		u32 bytes_committed = 0;

		ret = pagefault_single_data_segment(dev, शून्य, rkey, address,
						    prefetch_len,
						    &bytes_committed, शून्य);
		अगर (ret < 0 && ret != -EAGAIN) अणु
			mlx5_ib_dbg(dev, "Prefetch failed. ret: %d, QP 0x%x, address: 0x%.16llx, length = 0x%.16x\n",
				    ret, pfault->token, address, prefetch_len);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mlx5_ib_pfault(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_pagefault *pfault)
अणु
	u8 event_subtype = pfault->event_subtype;

	चयन (event_subtype) अणु
	हाल MLX5_PFAULT_SUBTYPE_WQE:
		mlx5_ib_mr_wqe_pfault_handler(dev, pfault);
		अवरोध;
	हाल MLX5_PFAULT_SUBTYPE_RDMA:
		mlx5_ib_mr_rdma_pfault_handler(dev, pfault);
		अवरोध;
	शेष:
		mlx5_ib_err(dev, "Invalid page fault event subtype: 0x%x\n",
			    event_subtype);
		mlx5_ib_page_fault_resume(dev, pfault, 1);
	पूर्ण
पूर्ण

अटल व्योम mlx5_ib_eqe_pf_action(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_pagefault *pfault = container_of(work,
						     काष्ठा mlx5_pagefault,
						     work);
	काष्ठा mlx5_ib_pf_eq *eq = pfault->eq;

	mlx5_ib_pfault(eq->dev, pfault);
	mempool_मुक्त(pfault, eq->pool);
पूर्ण

अटल व्योम mlx5_ib_eq_pf_process(काष्ठा mlx5_ib_pf_eq *eq)
अणु
	काष्ठा mlx5_eqe_page_fault *pf_eqe;
	काष्ठा mlx5_pagefault *pfault;
	काष्ठा mlx5_eqe *eqe;
	पूर्णांक cc = 0;

	जबतक ((eqe = mlx5_eq_get_eqe(eq->core, cc))) अणु
		pfault = mempool_alloc(eq->pool, GFP_ATOMIC);
		अगर (!pfault) अणु
			schedule_work(&eq->work);
			अवरोध;
		पूर्ण

		pf_eqe = &eqe->data.page_fault;
		pfault->event_subtype = eqe->sub_type;
		pfault->bytes_committed = be32_to_cpu(pf_eqe->bytes_committed);

		mlx5_ib_dbg(eq->dev,
			    "PAGE_FAULT: subtype: 0x%02x, bytes_committed: 0x%06x\n",
			    eqe->sub_type, pfault->bytes_committed);

		चयन (eqe->sub_type) अणु
		हाल MLX5_PFAULT_SUBTYPE_RDMA:
			/* RDMA based event */
			pfault->type =
				be32_to_cpu(pf_eqe->rdma.pftype_token) >> 24;
			pfault->token =
				be32_to_cpu(pf_eqe->rdma.pftype_token) &
				MLX5_24BIT_MASK;
			pfault->rdma.r_key =
				be32_to_cpu(pf_eqe->rdma.r_key);
			pfault->rdma.packet_size =
				be16_to_cpu(pf_eqe->rdma.packet_length);
			pfault->rdma.rdma_op_len =
				be32_to_cpu(pf_eqe->rdma.rdma_op_len);
			pfault->rdma.rdma_va =
				be64_to_cpu(pf_eqe->rdma.rdma_va);
			mlx5_ib_dbg(eq->dev,
				    "PAGE_FAULT: type:0x%x, token: 0x%06x, r_key: 0x%08x\n",
				    pfault->type, pfault->token,
				    pfault->rdma.r_key);
			mlx5_ib_dbg(eq->dev,
				    "PAGE_FAULT: rdma_op_len: 0x%08x, rdma_va: 0x%016llx\n",
				    pfault->rdma.rdma_op_len,
				    pfault->rdma.rdma_va);
			अवरोध;

		हाल MLX5_PFAULT_SUBTYPE_WQE:
			/* WQE based event */
			pfault->type =
				(be32_to_cpu(pf_eqe->wqe.pftype_wq) >> 24) & 0x7;
			pfault->token =
				be32_to_cpu(pf_eqe->wqe.token);
			pfault->wqe.wq_num =
				be32_to_cpu(pf_eqe->wqe.pftype_wq) &
				MLX5_24BIT_MASK;
			pfault->wqe.wqe_index =
				be16_to_cpu(pf_eqe->wqe.wqe_index);
			pfault->wqe.packet_size =
				be16_to_cpu(pf_eqe->wqe.packet_length);
			mlx5_ib_dbg(eq->dev,
				    "PAGE_FAULT: type:0x%x, token: 0x%06x, wq_num: 0x%06x, wqe_index: 0x%04x\n",
				    pfault->type, pfault->token,
				    pfault->wqe.wq_num,
				    pfault->wqe.wqe_index);
			अवरोध;

		शेष:
			mlx5_ib_warn(eq->dev,
				     "Unsupported page fault event sub-type: 0x%02hhx\n",
				     eqe->sub_type);
			/* Unsupported page faults should still be
			 * resolved by the page fault handler
			 */
		पूर्ण

		pfault->eq = eq;
		INIT_WORK(&pfault->work, mlx5_ib_eqe_pf_action);
		queue_work(eq->wq, &pfault->work);

		cc = mlx5_eq_update_cc(eq->core, ++cc);
	पूर्ण

	mlx5_eq_update_ci(eq->core, cc, 1);
पूर्ण

अटल पूर्णांक mlx5_ib_eq_pf_पूर्णांक(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ type,
			     व्योम *data)
अणु
	काष्ठा mlx5_ib_pf_eq *eq =
		container_of(nb, काष्ठा mlx5_ib_pf_eq, irq_nb);
	अचिन्हित दीर्घ flags;

	अगर (spin_trylock_irqsave(&eq->lock, flags)) अणु
		mlx5_ib_eq_pf_process(eq);
		spin_unlock_irqrestore(&eq->lock, flags);
	पूर्ण अन्यथा अणु
		schedule_work(&eq->work);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* mempool_refill() was proposed but unक्रमtunately wasn't accepted
 * http://lkml.iu.edu/hypermail/linux/kernel/1512.1/05073.hपंचांगl
 * Cheap workaround.
 */
अटल व्योम mempool_refill(mempool_t *pool)
अणु
	जबतक (pool->curr_nr < pool->min_nr)
		mempool_मुक्त(mempool_alloc(pool, GFP_KERNEL), pool);
पूर्ण

अटल व्योम mlx5_ib_eq_pf_action(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_ib_pf_eq *eq =
		container_of(work, काष्ठा mlx5_ib_pf_eq, work);

	mempool_refill(eq->pool);

	spin_lock_irq(&eq->lock);
	mlx5_ib_eq_pf_process(eq);
	spin_unlock_irq(&eq->lock);
पूर्ण

क्रमागत अणु
	MLX5_IB_NUM_PF_EQE	= 0x1000,
	MLX5_IB_NUM_PF_DRAIN	= 64,
पूर्ण;

पूर्णांक mlx5r_odp_create_eq(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_pf_eq *eq)
अणु
	काष्ठा mlx5_eq_param param = अणुपूर्ण;
	पूर्णांक err = 0;

	mutex_lock(&dev->odp_eq_mutex);
	अगर (eq->core)
		जाओ unlock;
	INIT_WORK(&eq->work, mlx5_ib_eq_pf_action);
	spin_lock_init(&eq->lock);
	eq->dev = dev;

	eq->pool = mempool_create_kदो_स्मृति_pool(MLX5_IB_NUM_PF_DRAIN,
					       माप(काष्ठा mlx5_pagefault));
	अगर (!eq->pool) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	eq->wq = alloc_workqueue("mlx5_ib_page_fault",
				 WQ_HIGHPRI | WQ_UNBOUND | WQ_MEM_RECLAIM,
				 MLX5_NUM_CMD_EQE);
	अगर (!eq->wq) अणु
		err = -ENOMEM;
		जाओ err_mempool;
	पूर्ण

	eq->irq_nb.notअगरier_call = mlx5_ib_eq_pf_पूर्णांक;
	param = (काष्ठा mlx5_eq_param)अणु
		.irq_index = 0,
		.nent = MLX5_IB_NUM_PF_EQE,
	पूर्ण;
	param.mask[0] = 1ull << MLX5_EVENT_TYPE_PAGE_FAULT;
	eq->core = mlx5_eq_create_generic(dev->mdev, &param);
	अगर (IS_ERR(eq->core)) अणु
		err = PTR_ERR(eq->core);
		जाओ err_wq;
	पूर्ण
	err = mlx5_eq_enable(dev->mdev, eq->core, &eq->irq_nb);
	अगर (err) अणु
		mlx5_ib_err(dev, "failed to enable odp EQ %d\n", err);
		जाओ err_eq;
	पूर्ण

	mutex_unlock(&dev->odp_eq_mutex);
	वापस 0;
err_eq:
	mlx5_eq_destroy_generic(dev->mdev, eq->core);
err_wq:
	eq->core = शून्य;
	destroy_workqueue(eq->wq);
err_mempool:
	mempool_destroy(eq->pool);
unlock:
	mutex_unlock(&dev->odp_eq_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक
mlx5_ib_odp_destroy_eq(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_pf_eq *eq)
अणु
	पूर्णांक err;

	अगर (!eq->core)
		वापस 0;
	mlx5_eq_disable(dev->mdev, eq->core, &eq->irq_nb);
	err = mlx5_eq_destroy_generic(dev->mdev, eq->core);
	cancel_work_sync(&eq->work);
	destroy_workqueue(eq->wq);
	mempool_destroy(eq->pool);

	वापस err;
पूर्ण

व्योम mlx5_odp_init_mr_cache_entry(काष्ठा mlx5_cache_ent *ent)
अणु
	अगर (!(ent->dev->odp_caps.general_caps & IB_ODP_SUPPORT_IMPLICIT))
		वापस;

	चयन (ent->order - 2) अणु
	हाल MLX5_IMR_MTT_CACHE_ENTRY:
		ent->page = PAGE_SHIFT;
		ent->xlt = MLX5_IMR_MTT_ENTRIES *
			   माप(काष्ठा mlx5_mtt) /
			   MLX5_IB_UMR_OCTOWORD;
		ent->access_mode = MLX5_MKC_ACCESS_MODE_MTT;
		ent->limit = 0;
		अवरोध;

	हाल MLX5_IMR_KSM_CACHE_ENTRY:
		ent->page = MLX5_KSM_PAGE_SHIFT;
		ent->xlt = mlx5_imr_ksm_entries *
			   माप(काष्ठा mlx5_klm) /
			   MLX5_IB_UMR_OCTOWORD;
		ent->access_mode = MLX5_MKC_ACCESS_MODE_KSM;
		ent->limit = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ib_device_ops mlx5_ib_dev_odp_ops = अणु
	.advise_mr = mlx5_ib_advise_mr,
पूर्ण;

पूर्णांक mlx5_ib_odp_init_one(काष्ठा mlx5_ib_dev *dev)
अणु
	पूर्णांक ret = 0;

	पूर्णांकernal_fill_odp_caps(dev);

	अगर (!(dev->odp_caps.general_caps & IB_ODP_SUPPORT))
		वापस ret;

	ib_set_device_ops(&dev->ib_dev, &mlx5_ib_dev_odp_ops);

	अगर (dev->odp_caps.general_caps & IB_ODP_SUPPORT_IMPLICIT) अणु
		ret = mlx5_cmd_null_mkey(dev->mdev, &dev->null_mkey);
		अगर (ret) अणु
			mlx5_ib_err(dev, "Error getting null_mkey %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_init(&dev->odp_eq_mutex);
	वापस ret;
पूर्ण

व्योम mlx5_ib_odp_cleanup_one(काष्ठा mlx5_ib_dev *dev)
अणु
	अगर (!(dev->odp_caps.general_caps & IB_ODP_SUPPORT))
		वापस;

	mlx5_ib_odp_destroy_eq(dev, &dev->odp_pf_eq);
पूर्ण

पूर्णांक mlx5_ib_odp_init(व्योम)
अणु
	mlx5_imr_ksm_entries = BIT_ULL(get_order(TASK_SIZE) -
				       MLX5_IMR_MTT_BITS);

	वापस 0;
पूर्ण

काष्ठा prefetch_mr_work अणु
	काष्ठा work_काष्ठा work;
	u32 pf_flags;
	u32 num_sge;
	काष्ठा अणु
		u64 io_virt;
		काष्ठा mlx5_ib_mr *mr;
		माप_प्रकार length;
	पूर्ण frags[];
पूर्ण;

अटल व्योम destroy_prefetch_work(काष्ठा prefetch_mr_work *work)
अणु
	u32 i;

	क्रम (i = 0; i < work->num_sge; ++i)
		mlx5r_deref_odp_mkey(&work->frags[i].mr->mmkey);

	kvमुक्त(work);
पूर्ण

अटल काष्ठा mlx5_ib_mr *
get_prefetchable_mr(काष्ठा ib_pd *pd, क्रमागत ib_uverbs_advise_mr_advice advice,
		    u32 lkey)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(pd->device);
	काष्ठा mlx5_core_mkey *mmkey;
	काष्ठा mlx5_ib_mr *mr = शून्य;

	xa_lock(&dev->odp_mkeys);
	mmkey = xa_load(&dev->odp_mkeys, mlx5_base_mkey(lkey));
	अगर (!mmkey || mmkey->key != lkey || mmkey->type != MLX5_MKEY_MR)
		जाओ end;

	mr = container_of(mmkey, काष्ठा mlx5_ib_mr, mmkey);

	अगर (mr->ibmr.pd != pd) अणु
		mr = शून्य;
		जाओ end;
	पूर्ण

	/* prefetch with ग_लिखो-access must be supported by the MR */
	अगर (advice == IB_UVERBS_ADVISE_MR_ADVICE_PREFETCH_WRITE &&
	    !mr->umem->writable) अणु
		mr = शून्य;
		जाओ end;
	पूर्ण

	refcount_inc(&mmkey->usecount);
end:
	xa_unlock(&dev->odp_mkeys);
	वापस mr;
पूर्ण

अटल व्योम mlx5_ib_prefetch_mr_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा prefetch_mr_work *work =
		container_of(w, काष्ठा prefetch_mr_work, work);
	u32 bytes_mapped = 0;
	पूर्णांक ret;
	u32 i;

	/* We rely on IB/core that work is executed अगर we have num_sge != 0 only. */
	WARN_ON(!work->num_sge);
	क्रम (i = 0; i < work->num_sge; ++i) अणु
		ret = pagefault_mr(work->frags[i].mr, work->frags[i].io_virt,
				   work->frags[i].length, &bytes_mapped,
				   work->pf_flags);
		अगर (ret <= 0)
			जारी;
		mlx5_update_odp_stats(work->frags[i].mr, prefetch, ret);
	पूर्ण

	destroy_prefetch_work(work);
पूर्ण

अटल bool init_prefetch_work(काष्ठा ib_pd *pd,
			       क्रमागत ib_uverbs_advise_mr_advice advice,
			       u32 pf_flags, काष्ठा prefetch_mr_work *work,
			       काष्ठा ib_sge *sg_list, u32 num_sge)
अणु
	u32 i;

	INIT_WORK(&work->work, mlx5_ib_prefetch_mr_work);
	work->pf_flags = pf_flags;

	क्रम (i = 0; i < num_sge; ++i) अणु
		work->frags[i].io_virt = sg_list[i].addr;
		work->frags[i].length = sg_list[i].length;
		work->frags[i].mr =
			get_prefetchable_mr(pd, advice, sg_list[i].lkey);
		अगर (!work->frags[i].mr) अणु
			work->num_sge = i;
			वापस false;
		पूर्ण
	पूर्ण
	work->num_sge = num_sge;
	वापस true;
पूर्ण

अटल पूर्णांक mlx5_ib_prefetch_sg_list(काष्ठा ib_pd *pd,
				    क्रमागत ib_uverbs_advise_mr_advice advice,
				    u32 pf_flags, काष्ठा ib_sge *sg_list,
				    u32 num_sge)
अणु
	u32 bytes_mapped = 0;
	पूर्णांक ret = 0;
	u32 i;

	क्रम (i = 0; i < num_sge; ++i) अणु
		काष्ठा mlx5_ib_mr *mr;

		mr = get_prefetchable_mr(pd, advice, sg_list[i].lkey);
		अगर (!mr)
			वापस -ENOENT;
		ret = pagefault_mr(mr, sg_list[i].addr, sg_list[i].length,
				   &bytes_mapped, pf_flags);
		अगर (ret < 0) अणु
			mlx5r_deref_odp_mkey(&mr->mmkey);
			वापस ret;
		पूर्ण
		mlx5_update_odp_stats(mr, prefetch, ret);
		mlx5r_deref_odp_mkey(&mr->mmkey);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx5_ib_advise_mr_prefetch(काष्ठा ib_pd *pd,
			       क्रमागत ib_uverbs_advise_mr_advice advice,
			       u32 flags, काष्ठा ib_sge *sg_list, u32 num_sge)
अणु
	u32 pf_flags = 0;
	काष्ठा prefetch_mr_work *work;

	अगर (advice == IB_UVERBS_ADVISE_MR_ADVICE_PREFETCH)
		pf_flags |= MLX5_PF_FLAGS_DOWNGRADE;

	अगर (advice == IB_UVERBS_ADVISE_MR_ADVICE_PREFETCH_NO_FAULT)
		pf_flags |= MLX5_PF_FLAGS_SNAPSHOT;

	अगर (flags & IB_UVERBS_ADVISE_MR_FLAG_FLUSH)
		वापस mlx5_ib_prefetch_sg_list(pd, advice, pf_flags, sg_list,
						num_sge);

	work = kvzalloc(काष्ठा_size(work, frags, num_sge), GFP_KERNEL);
	अगर (!work)
		वापस -ENOMEM;

	अगर (!init_prefetch_work(pd, advice, pf_flags, work, sg_list, num_sge)) अणु
		destroy_prefetch_work(work);
		वापस -EINVAL;
	पूर्ण
	queue_work(प्रणाली_unbound_wq, &work->work);
	वापस 0;
पूर्ण
