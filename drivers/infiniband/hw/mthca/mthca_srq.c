<शैली गुरु>
/*
 * Copyright (c) 2005 Cisco Systems. All rights reserved.
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

#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>

#समावेश <यंत्र/पन.स>

#समावेश <rdma/uverbs_ioctl.h>

#समावेश "mthca_dev.h"
#समावेश "mthca_cmd.h"
#समावेश "mthca_memfree.h"
#समावेश "mthca_wqe.h"

क्रमागत अणु
	MTHCA_MAX_सूचीECT_SRQ_SIZE = 4 * PAGE_SIZE
पूर्ण;

काष्ठा mthca_tavor_srq_context अणु
	__be64 wqe_base_ds;	/* low 6 bits is descriptor size */
	__be32 state_pd;
	__be32 lkey;
	__be32 uar;
	__be16 limit_watermark;
	__be16 wqe_cnt;
	u32    reserved[2];
पूर्ण;

काष्ठा mthca_arbel_srq_context अणु
	__be32 state_logsize_srqn;
	__be32 lkey;
	__be32 db_index;
	__be32 logstride_usrpage;
	__be64 wqe_base;
	__be32 eq_pd;
	__be16 limit_watermark;
	__be16 wqe_cnt;
	u16    reserved1;
	__be16 wqe_counter;
	u32    reserved2[3];
पूर्ण;

अटल व्योम *get_wqe(काष्ठा mthca_srq *srq, पूर्णांक n)
अणु
	अगर (srq->is_direct)
		वापस srq->queue.direct.buf + (n << srq->wqe_shअगरt);
	अन्यथा
		वापस srq->queue.page_list[(n << srq->wqe_shअगरt) >> PAGE_SHIFT].buf +
			((n << srq->wqe_shअगरt) & (PAGE_SIZE - 1));
पूर्ण

/*
 * Return a poपूर्णांकer to the location within a WQE that we're using as a
 * link when the WQE is in the मुक्त list.  We use the imm field
 * because in the Tavor हाल, posting a WQE may overग_लिखो the next
 * segment of the previous WQE, but a receive WQE will never touch the
 * imm field.  This aव्योमs corrupting our मुक्त list अगर the previous
 * WQE has alपढ़ोy completed and been put on the मुक्त list when we
 * post the next WQE.
 */
अटल अंतरभूत पूर्णांक *wqe_to_link(व्योम *wqe)
अणु
	वापस (पूर्णांक *) (wqe + दुरत्व(काष्ठा mthca_next_seg, imm));
पूर्ण

अटल व्योम mthca_tavor_init_srq_context(काष्ठा mthca_dev *dev,
					 काष्ठा mthca_pd *pd,
					 काष्ठा mthca_srq *srq,
					 काष्ठा mthca_tavor_srq_context *context,
					 काष्ठा ib_udata *udata)
अणु
	काष्ठा mthca_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा mthca_ucontext, ibucontext);

	स_रखो(context, 0, माप *context);

	context->wqe_base_ds = cpu_to_be64(1 << (srq->wqe_shअगरt - 4));
	context->state_pd    = cpu_to_be32(pd->pd_num);
	context->lkey        = cpu_to_be32(srq->mr.ibmr.lkey);

	अगर (udata)
		context->uar = cpu_to_be32(ucontext->uar.index);
	अन्यथा
		context->uar = cpu_to_be32(dev->driver_uar.index);
पूर्ण

अटल व्योम mthca_arbel_init_srq_context(काष्ठा mthca_dev *dev,
					 काष्ठा mthca_pd *pd,
					 काष्ठा mthca_srq *srq,
					 काष्ठा mthca_arbel_srq_context *context,
					 काष्ठा ib_udata *udata)
अणु
	काष्ठा mthca_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा mthca_ucontext, ibucontext);
	पूर्णांक logsize, max;

	स_रखो(context, 0, माप *context);

	/*
	 * Put max in a temporary variable to work around gcc bug
	 * triggered by ilog2() on sparc64.
	 */
	max = srq->max;
	logsize = ilog2(max);
	context->state_logsize_srqn = cpu_to_be32(logsize << 24 | srq->srqn);
	context->lkey = cpu_to_be32(srq->mr.ibmr.lkey);
	context->db_index = cpu_to_be32(srq->db_index);
	context->logstride_usrpage = cpu_to_be32((srq->wqe_shअगरt - 4) << 29);
	अगर (udata)
		context->logstride_usrpage |= cpu_to_be32(ucontext->uar.index);
	अन्यथा
		context->logstride_usrpage |= cpu_to_be32(dev->driver_uar.index);
	context->eq_pd = cpu_to_be32(MTHCA_EQ_ASYNC << 24 | pd->pd_num);
पूर्ण

अटल व्योम mthca_मुक्त_srq_buf(काष्ठा mthca_dev *dev, काष्ठा mthca_srq *srq)
अणु
	mthca_buf_मुक्त(dev, srq->max << srq->wqe_shअगरt, &srq->queue,
		       srq->is_direct, &srq->mr);
	kमुक्त(srq->wrid);
पूर्ण

अटल पूर्णांक mthca_alloc_srq_buf(काष्ठा mthca_dev *dev, काष्ठा mthca_pd *pd,
			       काष्ठा mthca_srq *srq, काष्ठा ib_udata *udata)
अणु
	काष्ठा mthca_data_seg *scatter;
	व्योम *wqe;
	पूर्णांक err;
	पूर्णांक i;

	अगर (udata)
		वापस 0;

	srq->wrid = kदो_स्मृति_array(srq->max, माप(u64), GFP_KERNEL);
	अगर (!srq->wrid)
		वापस -ENOMEM;

	err = mthca_buf_alloc(dev, srq->max << srq->wqe_shअगरt,
			      MTHCA_MAX_सूचीECT_SRQ_SIZE,
			      &srq->queue, &srq->is_direct, pd, 1, &srq->mr);
	अगर (err) अणु
		kमुक्त(srq->wrid);
		वापस err;
	पूर्ण

	/*
	 * Now initialize the SRQ buffer so that all of the WQEs are
	 * linked पूर्णांकo the list of मुक्त WQEs.  In addition, set the
	 * scatter list L_Keys to the sentry value of 0x100.
	 */
	क्रम (i = 0; i < srq->max; ++i) अणु
		काष्ठा mthca_next_seg *next;

		next = wqe = get_wqe(srq, i);

		अगर (i < srq->max - 1) अणु
			*wqe_to_link(wqe) = i + 1;
			next->nda_op = htonl(((i + 1) << srq->wqe_shअगरt) | 1);
		पूर्ण अन्यथा अणु
			*wqe_to_link(wqe) = -1;
			next->nda_op = 0;
		पूर्ण

		क्रम (scatter = wqe + माप (काष्ठा mthca_next_seg);
		     (व्योम *) scatter < wqe + (1 << srq->wqe_shअगरt);
		     ++scatter)
			scatter->lkey = cpu_to_be32(MTHCA_INVAL_LKEY);
	पूर्ण

	srq->last = get_wqe(srq, srq->max - 1);

	वापस 0;
पूर्ण

पूर्णांक mthca_alloc_srq(काष्ठा mthca_dev *dev, काष्ठा mthca_pd *pd,
		    काष्ठा ib_srq_attr *attr, काष्ठा mthca_srq *srq,
		    काष्ठा ib_udata *udata)
अणु
	काष्ठा mthca_mailbox *mailbox;
	पूर्णांक ds;
	पूर्णांक err;

	/* Sanity check SRQ size beक्रमe proceeding */
	अगर (attr->max_wr  > dev->limits.max_srq_wqes ||
	    attr->max_sge > dev->limits.max_srq_sge)
		वापस -EINVAL;

	srq->max      = attr->max_wr;
	srq->max_gs   = attr->max_sge;
	srq->counter  = 0;

	अगर (mthca_is_memमुक्त(dev))
		srq->max = roundup_घात_of_two(srq->max + 1);
	अन्यथा
		srq->max = srq->max + 1;

	ds = max(64UL,
		 roundup_घात_of_two(माप (काष्ठा mthca_next_seg) +
				    srq->max_gs * माप (काष्ठा mthca_data_seg)));

	अगर (!mthca_is_memमुक्त(dev) && (ds > dev->limits.max_desc_sz))
		वापस -EINVAL;

	srq->wqe_shअगरt = ilog2(ds);

	srq->srqn = mthca_alloc(&dev->srq_table.alloc);
	अगर (srq->srqn == -1)
		वापस -ENOMEM;

	अगर (mthca_is_memमुक्त(dev)) अणु
		err = mthca_table_get(dev, dev->srq_table.table, srq->srqn);
		अगर (err)
			जाओ err_out;

		अगर (!udata) अणु
			srq->db_index = mthca_alloc_db(dev, MTHCA_DB_TYPE_SRQ,
						       srq->srqn, &srq->db);
			अगर (srq->db_index < 0) अणु
				err = -ENOMEM;
				जाओ err_out_icm;
			पूर्ण
		पूर्ण
	पूर्ण

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox)) अणु
		err = PTR_ERR(mailbox);
		जाओ err_out_db;
	पूर्ण

	err = mthca_alloc_srq_buf(dev, pd, srq, udata);
	अगर (err)
		जाओ err_out_mailbox;

	spin_lock_init(&srq->lock);
	srq->refcount = 1;
	init_रुकोqueue_head(&srq->रुको);
	mutex_init(&srq->mutex);

	अगर (mthca_is_memमुक्त(dev))
		mthca_arbel_init_srq_context(dev, pd, srq, mailbox->buf, udata);
	अन्यथा
		mthca_tavor_init_srq_context(dev, pd, srq, mailbox->buf, udata);

	err = mthca_SW2HW_SRQ(dev, mailbox, srq->srqn);

	अगर (err) अणु
		mthca_warn(dev, "SW2HW_SRQ failed (%d)\n", err);
		जाओ err_out_मुक्त_buf;
	पूर्ण

	spin_lock_irq(&dev->srq_table.lock);
	अगर (mthca_array_set(&dev->srq_table.srq,
			    srq->srqn & (dev->limits.num_srqs - 1),
			    srq)) अणु
		spin_unlock_irq(&dev->srq_table.lock);
		जाओ err_out_मुक्त_srq;
	पूर्ण
	spin_unlock_irq(&dev->srq_table.lock);

	mthca_मुक्त_mailbox(dev, mailbox);

	srq->first_मुक्त = 0;
	srq->last_मुक्त  = srq->max - 1;

	attr->max_wr    = srq->max - 1;
	attr->max_sge   = srq->max_gs;

	वापस 0;

err_out_मुक्त_srq:
	err = mthca_HW2SW_SRQ(dev, mailbox, srq->srqn);
	अगर (err)
		mthca_warn(dev, "HW2SW_SRQ failed (%d)\n", err);

err_out_मुक्त_buf:
	अगर (!udata)
		mthca_मुक्त_srq_buf(dev, srq);

err_out_mailbox:
	mthca_मुक्त_mailbox(dev, mailbox);

err_out_db:
	अगर (!udata && mthca_is_memमुक्त(dev))
		mthca_मुक्त_db(dev, MTHCA_DB_TYPE_SRQ, srq->db_index);

err_out_icm:
	mthca_table_put(dev, dev->srq_table.table, srq->srqn);

err_out:
	mthca_मुक्त(&dev->srq_table.alloc, srq->srqn);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक get_srq_refcount(काष्ठा mthca_dev *dev, काष्ठा mthca_srq *srq)
अणु
	पूर्णांक c;

	spin_lock_irq(&dev->srq_table.lock);
	c = srq->refcount;
	spin_unlock_irq(&dev->srq_table.lock);

	वापस c;
पूर्ण

व्योम mthca_मुक्त_srq(काष्ठा mthca_dev *dev, काष्ठा mthca_srq *srq)
अणु
	काष्ठा mthca_mailbox *mailbox;
	पूर्णांक err;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox)) अणु
		mthca_warn(dev, "No memory for mailbox to free SRQ.\n");
		वापस;
	पूर्ण

	err = mthca_HW2SW_SRQ(dev, mailbox, srq->srqn);
	अगर (err)
		mthca_warn(dev, "HW2SW_SRQ failed (%d)\n", err);

	spin_lock_irq(&dev->srq_table.lock);
	mthca_array_clear(&dev->srq_table.srq,
			  srq->srqn & (dev->limits.num_srqs - 1));
	--srq->refcount;
	spin_unlock_irq(&dev->srq_table.lock);

	रुको_event(srq->रुको, !get_srq_refcount(dev, srq));

	अगर (!srq->ibsrq.uobject) अणु
		mthca_मुक्त_srq_buf(dev, srq);
		अगर (mthca_is_memमुक्त(dev))
			mthca_मुक्त_db(dev, MTHCA_DB_TYPE_SRQ, srq->db_index);
	पूर्ण

	mthca_table_put(dev, dev->srq_table.table, srq->srqn);
	mthca_मुक्त(&dev->srq_table.alloc, srq->srqn);
	mthca_मुक्त_mailbox(dev, mailbox);
पूर्ण

पूर्णांक mthca_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr,
		     क्रमागत ib_srq_attr_mask attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibsrq->device);
	काष्ठा mthca_srq *srq = to_msrq(ibsrq);
	पूर्णांक ret = 0;

	/* We करोn't support resizing SRQs (yet?) */
	अगर (attr_mask & IB_SRQ_MAX_WR)
		वापस -EINVAL;

	अगर (attr_mask & IB_SRQ_LIMIT) अणु
		u32 max_wr = mthca_is_memमुक्त(dev) ? srq->max - 1 : srq->max;
		अगर (attr->srq_limit > max_wr)
			वापस -EINVAL;

		mutex_lock(&srq->mutex);
		ret = mthca_ARM_SRQ(dev, srq->srqn, attr->srq_limit);
		mutex_unlock(&srq->mutex);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक mthca_query_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *srq_attr)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibsrq->device);
	काष्ठा mthca_srq *srq = to_msrq(ibsrq);
	काष्ठा mthca_mailbox *mailbox;
	काष्ठा mthca_arbel_srq_context *arbel_ctx;
	काष्ठा mthca_tavor_srq_context *tavor_ctx;
	पूर्णांक err;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	err = mthca_QUERY_SRQ(dev, srq->srqn, mailbox);
	अगर (err)
		जाओ out;

	अगर (mthca_is_memमुक्त(dev)) अणु
		arbel_ctx = mailbox->buf;
		srq_attr->srq_limit = be16_to_cpu(arbel_ctx->limit_watermark);
	पूर्ण अन्यथा अणु
		tavor_ctx = mailbox->buf;
		srq_attr->srq_limit = be16_to_cpu(tavor_ctx->limit_watermark);
	पूर्ण

	srq_attr->max_wr  = srq->max - 1;
	srq_attr->max_sge = srq->max_gs;

out:
	mthca_मुक्त_mailbox(dev, mailbox);

	वापस err;
पूर्ण

व्योम mthca_srq_event(काष्ठा mthca_dev *dev, u32 srqn,
		     क्रमागत ib_event_type event_type)
अणु
	काष्ठा mthca_srq *srq;
	काष्ठा ib_event event;

	spin_lock(&dev->srq_table.lock);
	srq = mthca_array_get(&dev->srq_table.srq, srqn & (dev->limits.num_srqs - 1));
	अगर (srq)
		++srq->refcount;
	spin_unlock(&dev->srq_table.lock);

	अगर (!srq) अणु
		mthca_warn(dev, "Async event for bogus SRQ %08x\n", srqn);
		वापस;
	पूर्ण

	अगर (!srq->ibsrq.event_handler)
		जाओ out;

	event.device      = &dev->ib_dev;
	event.event       = event_type;
	event.element.srq = &srq->ibsrq;
	srq->ibsrq.event_handler(&event, srq->ibsrq.srq_context);

out:
	spin_lock(&dev->srq_table.lock);
	अगर (!--srq->refcount)
		wake_up(&srq->रुको);
	spin_unlock(&dev->srq_table.lock);
पूर्ण

/*
 * This function must be called with IRQs disabled.
 */
व्योम mthca_मुक्त_srq_wqe(काष्ठा mthca_srq *srq, u32 wqe_addr)
अणु
	पूर्णांक ind;
	काष्ठा mthca_next_seg *last_मुक्त;

	ind = wqe_addr >> srq->wqe_shअगरt;

	spin_lock(&srq->lock);

	last_मुक्त = get_wqe(srq, srq->last_मुक्त);
	*wqe_to_link(last_मुक्त) = ind;
	last_मुक्त->nda_op = htonl((ind << srq->wqe_shअगरt) | 1);
	*wqe_to_link(get_wqe(srq, ind)) = -1;
	srq->last_मुक्त = ind;

	spin_unlock(&srq->lock);
पूर्ण

पूर्णांक mthca_tavor_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
			      स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibsrq->device);
	काष्ठा mthca_srq *srq = to_msrq(ibsrq);
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक first_ind;
	पूर्णांक ind;
	पूर्णांक next_ind;
	पूर्णांक nreq;
	पूर्णांक i;
	व्योम *wqe;
	व्योम *prev_wqe;

	spin_lock_irqsave(&srq->lock, flags);

	first_ind = srq->first_मुक्त;

	क्रम (nreq = 0; wr; wr = wr->next) अणु
		ind       = srq->first_मुक्त;
		wqe       = get_wqe(srq, ind);
		next_ind  = *wqe_to_link(wqe);

		अगर (unlikely(next_ind < 0)) अणु
			mthca_err(dev, "SRQ %06x full\n", srq->srqn);
			err = -ENOMEM;
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		prev_wqe  = srq->last;
		srq->last = wqe;

		((काष्ठा mthca_next_seg *) wqe)->ee_nds = 0;
		/* flags field will always reमुख्य 0 */

		wqe += माप (काष्ठा mthca_next_seg);

		अगर (unlikely(wr->num_sge > srq->max_gs)) अणु
			err = -EINVAL;
			*bad_wr = wr;
			srq->last = prev_wqe;
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < wr->num_sge; ++i) अणु
			mthca_set_data_seg(wqe, wr->sg_list + i);
			wqe += माप (काष्ठा mthca_data_seg);
		पूर्ण

		अगर (i < srq->max_gs)
			mthca_set_data_seg_inval(wqe);

		((काष्ठा mthca_next_seg *) prev_wqe)->ee_nds =
			cpu_to_be32(MTHCA_NEXT_DBD);

		srq->wrid[ind]  = wr->wr_id;
		srq->first_मुक्त = next_ind;

		++nreq;
		अगर (unlikely(nreq == MTHCA_TAVOR_MAX_WQES_PER_RECV_DB)) अणु
			nreq = 0;

			/*
			 * Make sure that descriptors are written
			 * beक्रमe करोorbell is rung.
			 */
			wmb();

			mthca_ग_लिखो64(first_ind << srq->wqe_shअगरt, srq->srqn << 8,
				      dev->kar + MTHCA_RECEIVE_DOORBELL,
				      MTHCA_GET_DOORBELL_LOCK(&dev->करोorbell_lock));

			first_ind = srq->first_मुक्त;
		पूर्ण
	पूर्ण

	अगर (likely(nreq)) अणु
		/*
		 * Make sure that descriptors are written beक्रमe
		 * करोorbell is rung.
		 */
		wmb();

		mthca_ग_लिखो64(first_ind << srq->wqe_shअगरt, (srq->srqn << 8) | nreq,
			      dev->kar + MTHCA_RECEIVE_DOORBELL,
			      MTHCA_GET_DOORBELL_LOCK(&dev->करोorbell_lock));
	पूर्ण

	spin_unlock_irqrestore(&srq->lock, flags);
	वापस err;
पूर्ण

पूर्णांक mthca_arbel_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
			      स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibsrq->device);
	काष्ठा mthca_srq *srq = to_msrq(ibsrq);
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	पूर्णांक ind;
	पूर्णांक next_ind;
	पूर्णांक nreq;
	पूर्णांक i;
	व्योम *wqe;

	spin_lock_irqsave(&srq->lock, flags);

	क्रम (nreq = 0; wr; ++nreq, wr = wr->next) अणु
		ind       = srq->first_मुक्त;
		wqe       = get_wqe(srq, ind);
		next_ind  = *wqe_to_link(wqe);

		अगर (unlikely(next_ind < 0)) अणु
			mthca_err(dev, "SRQ %06x full\n", srq->srqn);
			err = -ENOMEM;
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		((काष्ठा mthca_next_seg *) wqe)->ee_nds = 0;
		/* flags field will always reमुख्य 0 */

		wqe += माप (काष्ठा mthca_next_seg);

		अगर (unlikely(wr->num_sge > srq->max_gs)) अणु
			err = -EINVAL;
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < wr->num_sge; ++i) अणु
			mthca_set_data_seg(wqe, wr->sg_list + i);
			wqe += माप (काष्ठा mthca_data_seg);
		पूर्ण

		अगर (i < srq->max_gs)
			mthca_set_data_seg_inval(wqe);

		srq->wrid[ind]  = wr->wr_id;
		srq->first_मुक्त = next_ind;
	पूर्ण

	अगर (likely(nreq)) अणु
		srq->counter += nreq;

		/*
		 * Make sure that descriptors are written beक्रमe
		 * we ग_लिखो करोorbell record.
		 */
		wmb();
		*srq->db = cpu_to_be32(srq->counter);
	पूर्ण

	spin_unlock_irqrestore(&srq->lock, flags);
	वापस err;
पूर्ण

पूर्णांक mthca_max_srq_sge(काष्ठा mthca_dev *dev)
अणु
	अगर (mthca_is_memमुक्त(dev))
		वापस dev->limits.max_sg;

	/*
	 * SRQ allocations are based on घातers of 2 क्रम Tavor,
	 * (although they only need to be multiples of 16 bytes).
	 *
	 * Thereक्रमe, we need to base the max number of sg entries on
	 * the largest घातer of 2 descriptor size that is <= to the
	 * actual max WQE descriptor size, rather than वापस the
	 * max_sg value given by the firmware (which is based on WQE
	 * sizes as multiples of 16, not घातers of 2).
	 *
	 * If SRQ implementation is changed क्रम Tavor to be based on
	 * multiples of 16, the calculation below can be deleted and
	 * the FW max_sg value वापसed.
	 */
	वापस min_t(पूर्णांक, dev->limits.max_sg,
		     ((1 << (fls(dev->limits.max_desc_sz) - 1)) -
		      माप (काष्ठा mthca_next_seg)) /
		     माप (काष्ठा mthca_data_seg));
पूर्ण

पूर्णांक mthca_init_srq_table(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक err;

	अगर (!(dev->mthca_flags & MTHCA_FLAG_SRQ))
		वापस 0;

	spin_lock_init(&dev->srq_table.lock);

	err = mthca_alloc_init(&dev->srq_table.alloc,
			       dev->limits.num_srqs,
			       dev->limits.num_srqs - 1,
			       dev->limits.reserved_srqs);
	अगर (err)
		वापस err;

	err = mthca_array_init(&dev->srq_table.srq,
			       dev->limits.num_srqs);
	अगर (err)
		mthca_alloc_cleanup(&dev->srq_table.alloc);

	वापस err;
पूर्ण

व्योम mthca_cleanup_srq_table(काष्ठा mthca_dev *dev)
अणु
	अगर (!(dev->mthca_flags & MTHCA_FLAG_SRQ))
		वापस;

	mthca_array_cleanup(&dev->srq_table.srq, dev->limits.num_srqs);
	mthca_alloc_cleanup(&dev->srq_table.alloc);
पूर्ण
