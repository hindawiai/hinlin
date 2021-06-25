<शैली गुरु>
/*
 * Copyright (c) 2016 Oracle.  All rights reserved.
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

#समावेश "ib_mr.h"

अटल अंतरभूत व्योम
rds_transition_frwr_state(काष्ठा rds_ib_mr *ibmr,
			  क्रमागत rds_ib_fr_state old_state,
			  क्रमागत rds_ib_fr_state new_state)
अणु
	अगर (cmpxchg(&ibmr->u.frmr.fr_state,
		    old_state, new_state) == old_state &&
	    old_state == FRMR_IS_INUSE) अणु
		/* enक्रमce order of ibmr->u.frmr.fr_state update
		 * beक्रमe decrementing i_fastreg_inuse_count
		 */
		smp_mb__beक्रमe_atomic();
		atomic_dec(&ibmr->ic->i_fastreg_inuse_count);
		अगर (रुकोqueue_active(&rds_ib_ring_empty_रुको))
			wake_up(&rds_ib_ring_empty_रुको);
	पूर्ण
पूर्ण

अटल काष्ठा rds_ib_mr *rds_ib_alloc_frmr(काष्ठा rds_ib_device *rds_ibdev,
					   पूर्णांक npages)
अणु
	काष्ठा rds_ib_mr_pool *pool;
	काष्ठा rds_ib_mr *ibmr = शून्य;
	काष्ठा rds_ib_frmr *frmr;
	पूर्णांक err = 0;

	अगर (npages <= RDS_MR_8K_MSG_SIZE)
		pool = rds_ibdev->mr_8k_pool;
	अन्यथा
		pool = rds_ibdev->mr_1m_pool;

	ibmr = rds_ib_try_reuse_ibmr(pool);
	अगर (ibmr)
		वापस ibmr;

	ibmr = kzalloc_node(माप(*ibmr), GFP_KERNEL,
			    rdsibdev_to_node(rds_ibdev));
	अगर (!ibmr) अणु
		err = -ENOMEM;
		जाओ out_no_cigar;
	पूर्ण

	frmr = &ibmr->u.frmr;
	frmr->mr = ib_alloc_mr(rds_ibdev->pd, IB_MR_TYPE_MEM_REG,
			 pool->max_pages);
	अगर (IS_ERR(frmr->mr)) अणु
		pr_warn("RDS/IB: %s failed to allocate MR", __func__);
		err = PTR_ERR(frmr->mr);
		जाओ out_no_cigar;
	पूर्ण

	ibmr->pool = pool;
	अगर (pool->pool_type == RDS_IB_MR_8K_POOL)
		rds_ib_stats_inc(s_ib_rdma_mr_8k_alloc);
	अन्यथा
		rds_ib_stats_inc(s_ib_rdma_mr_1m_alloc);

	अगर (atomic_पढ़ो(&pool->item_count) > pool->max_items_soft)
		pool->max_items_soft = pool->max_items;

	frmr->fr_state = FRMR_IS_FREE;
	init_रुकोqueue_head(&frmr->fr_inv_करोne);
	init_रुकोqueue_head(&frmr->fr_reg_करोne);
	वापस ibmr;

out_no_cigar:
	kमुक्त(ibmr);
	atomic_dec(&pool->item_count);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम rds_ib_मुक्त_frmr(काष्ठा rds_ib_mr *ibmr, bool drop)
अणु
	काष्ठा rds_ib_mr_pool *pool = ibmr->pool;

	अगर (drop)
		llist_add(&ibmr->llnode, &pool->drop_list);
	अन्यथा
		llist_add(&ibmr->llnode, &pool->मुक्त_list);
	atomic_add(ibmr->sg_len, &pool->मुक्त_pinned);
	atomic_inc(&pool->dirty_count);

	/* If we've pinned too many pages, request a flush */
	अगर (atomic_पढ़ो(&pool->मुक्त_pinned) >= pool->max_मुक्त_pinned ||
	    atomic_पढ़ो(&pool->dirty_count) >= pool->max_items / 5)
		queue_delayed_work(rds_ib_mr_wq, &pool->flush_worker, 10);
पूर्ण

अटल पूर्णांक rds_ib_post_reg_frmr(काष्ठा rds_ib_mr *ibmr)
अणु
	काष्ठा rds_ib_frmr *frmr = &ibmr->u.frmr;
	काष्ठा ib_reg_wr reg_wr;
	पूर्णांक ret, off = 0;

	जबतक (atomic_dec_वापस(&ibmr->ic->i_fastreg_wrs) <= 0) अणु
		atomic_inc(&ibmr->ic->i_fastreg_wrs);
		cpu_relax();
	पूर्ण

	ret = ib_map_mr_sg_zbva(frmr->mr, ibmr->sg, ibmr->sg_len,
				&off, PAGE_SIZE);
	अगर (unlikely(ret != ibmr->sg_len))
		वापस ret < 0 ? ret : -EINVAL;

	अगर (cmpxchg(&frmr->fr_state,
		    FRMR_IS_FREE, FRMR_IS_INUSE) != FRMR_IS_FREE)
		वापस -EBUSY;

	atomic_inc(&ibmr->ic->i_fastreg_inuse_count);

	/* Perक्रमm a WR क्रम the fast_reg_mr. Each inभागidual page
	 * in the sg list is added to the fast reg page list and placed
	 * inside the fast_reg_mr WR.  The key used is a rolling 8bit
	 * counter, which should guarantee uniqueness.
	 */
	ib_update_fast_reg_key(frmr->mr, ibmr->remap_count++);
	frmr->fr_reg = true;

	स_रखो(&reg_wr, 0, माप(reg_wr));
	reg_wr.wr.wr_id = (अचिन्हित दीर्घ)(व्योम *)ibmr;
	reg_wr.wr.opcode = IB_WR_REG_MR;
	reg_wr.wr.num_sge = 0;
	reg_wr.mr = frmr->mr;
	reg_wr.key = frmr->mr->rkey;
	reg_wr.access = IB_ACCESS_LOCAL_WRITE |
			IB_ACCESS_REMOTE_READ |
			IB_ACCESS_REMOTE_WRITE;
	reg_wr.wr.send_flags = IB_SEND_SIGNALED;

	ret = ib_post_send(ibmr->ic->i_cm_id->qp, &reg_wr.wr, शून्य);
	अगर (unlikely(ret)) अणु
		/* Failure here can be because of -ENOMEM as well */
		rds_transition_frwr_state(ibmr, FRMR_IS_INUSE, FRMR_IS_STALE);

		atomic_inc(&ibmr->ic->i_fastreg_wrs);
		अगर (prपूर्णांकk_ratelimit())
			pr_warn("RDS/IB: %s returned error(%d)\n",
				__func__, ret);
		जाओ out;
	पूर्ण

	/* Wait क्रम the registration to complete in order to prevent an invalid
	 * access error resulting from a race between the memory region alपढ़ोy
	 * being accessed जबतक registration is still pending.
	 */
	रुको_event(frmr->fr_reg_करोne, !frmr->fr_reg);

out:

	वापस ret;
पूर्ण

अटल पूर्णांक rds_ib_map_frmr(काष्ठा rds_ib_device *rds_ibdev,
			   काष्ठा rds_ib_mr_pool *pool,
			   काष्ठा rds_ib_mr *ibmr,
			   काष्ठा scatterlist *sg, अचिन्हित पूर्णांक sg_len)
अणु
	काष्ठा ib_device *dev = rds_ibdev->dev;
	काष्ठा rds_ib_frmr *frmr = &ibmr->u.frmr;
	पूर्णांक i;
	u32 len;
	पूर्णांक ret = 0;

	/* We want to tearकरोwn old ibmr values here and fill it up with
	 * new sg values
	 */
	rds_ib_tearकरोwn_mr(ibmr);

	ibmr->sg = sg;
	ibmr->sg_len = sg_len;
	ibmr->sg_dma_len = 0;
	frmr->sg_byte_len = 0;
	WARN_ON(ibmr->sg_dma_len);
	ibmr->sg_dma_len = ib_dma_map_sg(dev, ibmr->sg, ibmr->sg_len,
					 DMA_BIसूचीECTIONAL);
	अगर (unlikely(!ibmr->sg_dma_len)) अणु
		pr_warn("RDS/IB: %s failed!\n", __func__);
		वापस -EBUSY;
	पूर्ण

	frmr->sg_byte_len = 0;
	frmr->dma_npages = 0;
	len = 0;

	ret = -EINVAL;
	क्रम (i = 0; i < ibmr->sg_dma_len; ++i) अणु
		अचिन्हित पूर्णांक dma_len = sg_dma_len(&ibmr->sg[i]);
		u64 dma_addr = sg_dma_address(&ibmr->sg[i]);

		frmr->sg_byte_len += dma_len;
		अगर (dma_addr & ~PAGE_MASK) अणु
			अगर (i > 0)
				जाओ out_unmap;
			अन्यथा
				++frmr->dma_npages;
		पूर्ण

		अगर ((dma_addr + dma_len) & ~PAGE_MASK) अणु
			अगर (i < ibmr->sg_dma_len - 1)
				जाओ out_unmap;
			अन्यथा
				++frmr->dma_npages;
		पूर्ण

		len += dma_len;
	पूर्ण
	frmr->dma_npages += len >> PAGE_SHIFT;

	अगर (frmr->dma_npages > ibmr->pool->max_pages) अणु
		ret = -EMSGSIZE;
		जाओ out_unmap;
	पूर्ण

	ret = rds_ib_post_reg_frmr(ibmr);
	अगर (ret)
		जाओ out_unmap;

	अगर (ibmr->pool->pool_type == RDS_IB_MR_8K_POOL)
		rds_ib_stats_inc(s_ib_rdma_mr_8k_used);
	अन्यथा
		rds_ib_stats_inc(s_ib_rdma_mr_1m_used);

	वापस ret;

out_unmap:
	ib_dma_unmap_sg(rds_ibdev->dev, ibmr->sg, ibmr->sg_len,
			DMA_BIसूचीECTIONAL);
	ibmr->sg_dma_len = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक rds_ib_post_inv(काष्ठा rds_ib_mr *ibmr)
अणु
	काष्ठा ib_send_wr *s_wr;
	काष्ठा rds_ib_frmr *frmr = &ibmr->u.frmr;
	काष्ठा rdma_cm_id *i_cm_id = ibmr->ic->i_cm_id;
	पूर्णांक ret = -EINVAL;

	अगर (!i_cm_id || !i_cm_id->qp || !frmr->mr)
		जाओ out;

	अगर (frmr->fr_state != FRMR_IS_INUSE)
		जाओ out;

	जबतक (atomic_dec_वापस(&ibmr->ic->i_fastreg_wrs) <= 0) अणु
		atomic_inc(&ibmr->ic->i_fastreg_wrs);
		cpu_relax();
	पूर्ण

	frmr->fr_inv = true;
	s_wr = &frmr->fr_wr;

	स_रखो(s_wr, 0, माप(*s_wr));
	s_wr->wr_id = (अचिन्हित दीर्घ)(व्योम *)ibmr;
	s_wr->opcode = IB_WR_LOCAL_INV;
	s_wr->ex.invalidate_rkey = frmr->mr->rkey;
	s_wr->send_flags = IB_SEND_SIGNALED;

	ret = ib_post_send(i_cm_id->qp, s_wr, शून्य);
	अगर (unlikely(ret)) अणु
		rds_transition_frwr_state(ibmr, FRMR_IS_INUSE, FRMR_IS_STALE);
		frmr->fr_inv = false;
		/* enक्रमce order of frmr->fr_inv update
		 * beक्रमe incrementing i_fastreg_wrs
		 */
		smp_mb__beक्रमe_atomic();
		atomic_inc(&ibmr->ic->i_fastreg_wrs);
		pr_err("RDS/IB: %s returned error(%d)\n", __func__, ret);
		जाओ out;
	पूर्ण

	/* Wait क्रम the FRMR_IS_FREE (or FRMR_IS_STALE) transition in order to
	 * 1) aव्योम a silly bouncing between "clean_list" and "drop_list"
	 *    triggered by function "rds_ib_reg_frmr" as it is releases frmr
	 *    regions whose state is not "FRMR_IS_FREE" right away.
	 * 2) prevents an invalid access error in a race
	 *    from a pending "IB_WR_LOCAL_INV" operation
	 *    with a tearकरोwn ("dma_unmap_sg", "put_page")
	 *    and de-registration ("ib_dereg_mr") of the corresponding
	 *    memory region.
	 */
	रुको_event(frmr->fr_inv_करोne, frmr->fr_state != FRMR_IS_INUSE);

out:
	वापस ret;
पूर्ण

व्योम rds_ib_mr_cqe_handler(काष्ठा rds_ib_connection *ic, काष्ठा ib_wc *wc)
अणु
	काष्ठा rds_ib_mr *ibmr = (व्योम *)(अचिन्हित दीर्घ)wc->wr_id;
	काष्ठा rds_ib_frmr *frmr = &ibmr->u.frmr;

	अगर (wc->status != IB_WC_SUCCESS) अणु
		rds_transition_frwr_state(ibmr, FRMR_IS_INUSE, FRMR_IS_STALE);
		अगर (rds_conn_up(ic->conn))
			rds_ib_conn_error(ic->conn,
					  "frmr completion <%pI4,%pI4> status %u(%s), vendor_err 0x%x, disconnecting and reconnecting\n",
					  &ic->conn->c_laddr,
					  &ic->conn->c_faddr,
					  wc->status,
					  ib_wc_status_msg(wc->status),
					  wc->venकरोr_err);
	पूर्ण

	अगर (frmr->fr_inv) अणु
		rds_transition_frwr_state(ibmr, FRMR_IS_INUSE, FRMR_IS_FREE);
		frmr->fr_inv = false;
		wake_up(&frmr->fr_inv_करोne);
	पूर्ण

	अगर (frmr->fr_reg) अणु
		frmr->fr_reg = false;
		wake_up(&frmr->fr_reg_करोne);
	पूर्ण

	/* enक्रमce order of frmr->अणुfr_reg,fr_invपूर्ण update
	 * beक्रमe incrementing i_fastreg_wrs
	 */
	smp_mb__beक्रमe_atomic();
	atomic_inc(&ic->i_fastreg_wrs);
पूर्ण

व्योम rds_ib_unreg_frmr(काष्ठा list_head *list, अचिन्हित पूर्णांक *nमुक्तd,
		       अचिन्हित दीर्घ *unpinned, अचिन्हित पूर्णांक goal)
अणु
	काष्ठा rds_ib_mr *ibmr, *next;
	काष्ठा rds_ib_frmr *frmr;
	पूर्णांक ret = 0, ret2;
	अचिन्हित पूर्णांक मुक्तd = *nमुक्तd;

	/* String all ib_mr's onto one list and hand them to ib_unmap_fmr */
	list_क्रम_each_entry(ibmr, list, unmap_list) अणु
		अगर (ibmr->sg_dma_len) अणु
			ret2 = rds_ib_post_inv(ibmr);
			अगर (ret2 && !ret)
				ret = ret2;
		पूर्ण
	पूर्ण

	अगर (ret)
		pr_warn("RDS/IB: %s failed (err=%d)\n", __func__, ret);

	/* Now we can destroy the DMA mapping and unpin any pages */
	list_क्रम_each_entry_safe(ibmr, next, list, unmap_list) अणु
		*unpinned += ibmr->sg_len;
		frmr = &ibmr->u.frmr;
		__rds_ib_tearकरोwn_mr(ibmr);
		अगर (मुक्तd < goal || frmr->fr_state == FRMR_IS_STALE) अणु
			/* Don't de-allocate अगर the MR is not मुक्त yet */
			अगर (frmr->fr_state == FRMR_IS_INUSE)
				जारी;

			अगर (ibmr->pool->pool_type == RDS_IB_MR_8K_POOL)
				rds_ib_stats_inc(s_ib_rdma_mr_8k_मुक्त);
			अन्यथा
				rds_ib_stats_inc(s_ib_rdma_mr_1m_मुक्त);
			list_del(&ibmr->unmap_list);
			अगर (frmr->mr)
				ib_dereg_mr(frmr->mr);
			kमुक्त(ibmr);
			मुक्तd++;
		पूर्ण
	पूर्ण
	*nमुक्तd = मुक्तd;
पूर्ण

काष्ठा rds_ib_mr *rds_ib_reg_frmr(काष्ठा rds_ib_device *rds_ibdev,
				  काष्ठा rds_ib_connection *ic,
				  काष्ठा scatterlist *sg,
				  अचिन्हित दीर्घ nents, u32 *key)
अणु
	काष्ठा rds_ib_mr *ibmr = शून्य;
	काष्ठा rds_ib_frmr *frmr;
	पूर्णांक ret;

	अगर (!ic) अणु
		/* TODO: Add FRWR support क्रम RDS_GET_MR using proxy qp*/
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	करो अणु
		अगर (ibmr)
			rds_ib_मुक्त_frmr(ibmr, true);
		ibmr = rds_ib_alloc_frmr(rds_ibdev, nents);
		अगर (IS_ERR(ibmr))
			वापस ibmr;
		frmr = &ibmr->u.frmr;
	पूर्ण जबतक (frmr->fr_state != FRMR_IS_FREE);

	ibmr->ic = ic;
	ibmr->device = rds_ibdev;
	ret = rds_ib_map_frmr(rds_ibdev, ibmr->pool, ibmr, sg, nents);
	अगर (ret == 0) अणु
		*key = frmr->mr->rkey;
	पूर्ण अन्यथा अणु
		rds_ib_मुक्त_frmr(ibmr, false);
		ibmr = ERR_PTR(ret);
	पूर्ण

	वापस ibmr;
पूर्ण

व्योम rds_ib_मुक्त_frmr_list(काष्ठा rds_ib_mr *ibmr)
अणु
	काष्ठा rds_ib_mr_pool *pool = ibmr->pool;
	काष्ठा rds_ib_frmr *frmr = &ibmr->u.frmr;

	अगर (frmr->fr_state == FRMR_IS_STALE)
		llist_add(&ibmr->llnode, &pool->drop_list);
	अन्यथा
		llist_add(&ibmr->llnode, &pool->मुक्त_list);
पूर्ण
