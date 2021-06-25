<शैली गुरु>
/*
 * Copyright (c) 2012-2016 VMware, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of EITHER the GNU General Public License
 * version 2 as published by the Free Software Foundation or the BSD
 * 2-Clause License. This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License version 2 क्रम more details at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.hपंचांगl.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program available in the file COPYING in the मुख्य
 * directory of this source tree.
 *
 * The BSD 2-Clause License
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <यंत्र/page.h>
#समावेश <linux/पन.स>
#समावेश <linux/रुको.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "pvrdma.h"

/**
 * pvrdma_req_notअगरy_cq - request notअगरication क्रम a completion queue
 * @ibcq: the completion queue
 * @notअगरy_flags: notअगरication flags
 *
 * @वापस: 0 क्रम success.
 */
पूर्णांक pvrdma_req_notअगरy_cq(काष्ठा ib_cq *ibcq,
			 क्रमागत ib_cq_notअगरy_flags notअगरy_flags)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(ibcq->device);
	काष्ठा pvrdma_cq *cq = to_vcq(ibcq);
	u32 val = cq->cq_handle;
	अचिन्हित दीर्घ flags;
	पूर्णांक has_data = 0;

	val |= (notअगरy_flags & IB_CQ_SOLICITED_MASK) == IB_CQ_SOLICITED ?
		PVRDMA_UAR_CQ_ARM_SOL : PVRDMA_UAR_CQ_ARM;

	spin_lock_irqsave(&cq->cq_lock, flags);

	pvrdma_ग_लिखो_uar_cq(dev, val);

	अगर (notअगरy_flags & IB_CQ_REPORT_MISSED_EVENTS) अणु
		अचिन्हित पूर्णांक head;

		has_data = pvrdma_idx_ring_has_data(&cq->ring_state->rx,
						    cq->ibcq.cqe, &head);
		अगर (unlikely(has_data == PVRDMA_INVALID_IDX))
			dev_err(&dev->pdev->dev, "CQ ring state invalid\n");
	पूर्ण

	spin_unlock_irqrestore(&cq->cq_lock, flags);

	वापस has_data;
पूर्ण

/**
 * pvrdma_create_cq - create completion queue
 * @ibcq: Allocated CQ
 * @attr: completion queue attributes
 * @udata: user data
 *
 * @वापस: 0 on success
 */
पूर्णांक pvrdma_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		     काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibcq->device;
	पूर्णांक entries = attr->cqe;
	काष्ठा pvrdma_dev *dev = to_vdev(ibdev);
	काष्ठा pvrdma_cq *cq = to_vcq(ibcq);
	पूर्णांक ret;
	पूर्णांक npages;
	अचिन्हित दीर्घ flags;
	जोड़ pvrdma_cmd_req req;
	जोड़ pvrdma_cmd_resp rsp;
	काष्ठा pvrdma_cmd_create_cq *cmd = &req.create_cq;
	काष्ठा pvrdma_cmd_create_cq_resp *resp = &rsp.create_cq_resp;
	काष्ठा pvrdma_create_cq_resp cq_resp = अणुपूर्ण;
	काष्ठा pvrdma_create_cq ucmd;
	काष्ठा pvrdma_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा pvrdma_ucontext, ibucontext);

	BUILD_BUG_ON(माप(काष्ठा pvrdma_cqe) != 64);

	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	entries = roundup_घात_of_two(entries);
	अगर (entries < 1 || entries > dev->dsr->caps.max_cqe)
		वापस -EINVAL;

	अगर (!atomic_add_unless(&dev->num_cqs, 1, dev->dsr->caps.max_cq))
		वापस -ENOMEM;

	cq->ibcq.cqe = entries;
	cq->is_kernel = !udata;

	अगर (!cq->is_kernel) अणु
		अगर (ib_copy_from_udata(&ucmd, udata, माप(ucmd))) अणु
			ret = -EFAULT;
			जाओ err_cq;
		पूर्ण

		cq->umem = ib_umem_get(ibdev, ucmd.buf_addr, ucmd.buf_size,
				       IB_ACCESS_LOCAL_WRITE);
		अगर (IS_ERR(cq->umem)) अणु
			ret = PTR_ERR(cq->umem);
			जाओ err_cq;
		पूर्ण

		npages = ib_umem_num_dma_blocks(cq->umem, PAGE_SIZE);
	पूर्ण अन्यथा अणु
		/* One extra page क्रम shared ring state */
		npages = 1 + (entries * माप(काष्ठा pvrdma_cqe) +
			      PAGE_SIZE - 1) / PAGE_SIZE;

		/* Skip header page. */
		cq->offset = PAGE_SIZE;
	पूर्ण

	अगर (npages < 0 || npages > PVRDMA_PAGE_सूची_MAX_PAGES) अणु
		dev_warn(&dev->pdev->dev,
			 "overflow pages in completion queue\n");
		ret = -EINVAL;
		जाओ err_umem;
	पूर्ण

	ret = pvrdma_page_dir_init(dev, &cq->pdir, npages, cq->is_kernel);
	अगर (ret) अणु
		dev_warn(&dev->pdev->dev,
			 "could not allocate page directory\n");
		जाओ err_umem;
	पूर्ण

	/* Ring state is always the first page. Set in library क्रम user cq. */
	अगर (cq->is_kernel)
		cq->ring_state = cq->pdir.pages[0];
	अन्यथा
		pvrdma_page_dir_insert_umem(&cq->pdir, cq->umem, 0);

	refcount_set(&cq->refcnt, 1);
	init_completion(&cq->मुक्त);
	spin_lock_init(&cq->cq_lock);

	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_CREATE_CQ;
	cmd->nchunks = npages;
	cmd->ctx_handle = context ? context->ctx_handle : 0;
	cmd->cqe = entries;
	cmd->pdir_dma = cq->pdir.dir_dma;
	ret = pvrdma_cmd_post(dev, &req, &rsp, PVRDMA_CMD_CREATE_CQ_RESP);
	अगर (ret < 0) अणु
		dev_warn(&dev->pdev->dev,
			 "could not create completion queue, error: %d\n", ret);
		जाओ err_page_dir;
	पूर्ण

	cq->ibcq.cqe = resp->cqe;
	cq->cq_handle = resp->cq_handle;
	cq_resp.cqn = resp->cq_handle;
	spin_lock_irqsave(&dev->cq_tbl_lock, flags);
	dev->cq_tbl[cq->cq_handle % dev->dsr->caps.max_cq] = cq;
	spin_unlock_irqrestore(&dev->cq_tbl_lock, flags);

	अगर (!cq->is_kernel) अणु
		cq->uar = &context->uar;

		/* Copy udata back. */
		अगर (ib_copy_to_udata(udata, &cq_resp, माप(cq_resp))) अणु
			dev_warn(&dev->pdev->dev,
				 "failed to copy back udata\n");
			pvrdma_destroy_cq(&cq->ibcq, udata);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;

err_page_dir:
	pvrdma_page_dir_cleanup(dev, &cq->pdir);
err_umem:
	ib_umem_release(cq->umem);
err_cq:
	atomic_dec(&dev->num_cqs);
	वापस ret;
पूर्ण

अटल व्योम pvrdma_मुक्त_cq(काष्ठा pvrdma_dev *dev, काष्ठा pvrdma_cq *cq)
अणु
	अगर (refcount_dec_and_test(&cq->refcnt))
		complete(&cq->मुक्त);
	रुको_क्रम_completion(&cq->मुक्त);

	ib_umem_release(cq->umem);

	pvrdma_page_dir_cleanup(dev, &cq->pdir);
पूर्ण

/**
 * pvrdma_destroy_cq - destroy completion queue
 * @cq: the completion queue to destroy.
 * @udata: user data or null क्रम kernel object
 */
पूर्णांक pvrdma_destroy_cq(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata)
अणु
	काष्ठा pvrdma_cq *vcq = to_vcq(cq);
	जोड़ pvrdma_cmd_req req;
	काष्ठा pvrdma_cmd_destroy_cq *cmd = &req.destroy_cq;
	काष्ठा pvrdma_dev *dev = to_vdev(cq->device);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->hdr.cmd = PVRDMA_CMD_DESTROY_CQ;
	cmd->cq_handle = vcq->cq_handle;

	ret = pvrdma_cmd_post(dev, &req, शून्य, 0);
	अगर (ret < 0)
		dev_warn(&dev->pdev->dev,
			 "could not destroy completion queue, error: %d\n",
			 ret);

	/* मुक्त cq's resources */
	spin_lock_irqsave(&dev->cq_tbl_lock, flags);
	dev->cq_tbl[vcq->cq_handle] = शून्य;
	spin_unlock_irqrestore(&dev->cq_tbl_lock, flags);

	pvrdma_मुक्त_cq(dev, vcq);
	atomic_dec(&dev->num_cqs);
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा pvrdma_cqe *get_cqe(काष्ठा pvrdma_cq *cq, पूर्णांक i)
अणु
	वापस (काष्ठा pvrdma_cqe *)pvrdma_page_dir_get_ptr(
					&cq->pdir,
					cq->offset +
					माप(काष्ठा pvrdma_cqe) * i);
पूर्ण

व्योम _pvrdma_flush_cqe(काष्ठा pvrdma_qp *qp, काष्ठा pvrdma_cq *cq)
अणु
	अचिन्हित पूर्णांक head;
	पूर्णांक has_data;

	अगर (!cq->is_kernel)
		वापस;

	/* Lock held */
	has_data = pvrdma_idx_ring_has_data(&cq->ring_state->rx,
					    cq->ibcq.cqe, &head);
	अगर (unlikely(has_data > 0)) अणु
		पूर्णांक items;
		पूर्णांक curr;
		पूर्णांक tail = pvrdma_idx(&cq->ring_state->rx.prod_tail,
				      cq->ibcq.cqe);
		काष्ठा pvrdma_cqe *cqe;
		काष्ठा pvrdma_cqe *curr_cqe;

		items = (tail > head) ? (tail - head) :
			(cq->ibcq.cqe - head + tail);
		curr = --tail;
		जबतक (items-- > 0) अणु
			अगर (curr < 0)
				curr = cq->ibcq.cqe - 1;
			अगर (tail < 0)
				tail = cq->ibcq.cqe - 1;
			curr_cqe = get_cqe(cq, curr);
			अगर ((curr_cqe->qp & 0xFFFF) != qp->qp_handle) अणु
				अगर (curr != tail) अणु
					cqe = get_cqe(cq, tail);
					*cqe = *curr_cqe;
				पूर्ण
				tail--;
			पूर्ण अन्यथा अणु
				pvrdma_idx_ring_inc(
					&cq->ring_state->rx.cons_head,
					cq->ibcq.cqe);
			पूर्ण
			curr--;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pvrdma_poll_one(काष्ठा pvrdma_cq *cq, काष्ठा pvrdma_qp **cur_qp,
			   काष्ठा ib_wc *wc)
अणु
	काष्ठा pvrdma_dev *dev = to_vdev(cq->ibcq.device);
	पूर्णांक has_data;
	अचिन्हित पूर्णांक head;
	bool tried = false;
	काष्ठा pvrdma_cqe *cqe;

retry:
	has_data = pvrdma_idx_ring_has_data(&cq->ring_state->rx,
					    cq->ibcq.cqe, &head);
	अगर (has_data == 0) अणु
		अगर (tried)
			वापस -EAGAIN;

		pvrdma_ग_लिखो_uar_cq(dev, cq->cq_handle | PVRDMA_UAR_CQ_POLL);

		tried = true;
		जाओ retry;
	पूर्ण अन्यथा अगर (has_data == PVRDMA_INVALID_IDX) अणु
		dev_err(&dev->pdev->dev, "CQ ring state invalid\n");
		वापस -EAGAIN;
	पूर्ण

	cqe = get_cqe(cq, head);

	/* Ensure cqe is valid. */
	rmb();
	अगर (dev->qp_tbl[cqe->qp & 0xffff])
		*cur_qp = (काष्ठा pvrdma_qp *)dev->qp_tbl[cqe->qp & 0xffff];
	अन्यथा
		वापस -EAGAIN;

	wc->opcode = pvrdma_wc_opcode_to_ib(cqe->opcode);
	wc->status = pvrdma_wc_status_to_ib(cqe->status);
	wc->wr_id = cqe->wr_id;
	wc->qp = &(*cur_qp)->ibqp;
	wc->byte_len = cqe->byte_len;
	wc->ex.imm_data = cqe->imm_data;
	wc->src_qp = cqe->src_qp;
	wc->wc_flags = pvrdma_wc_flags_to_ib(cqe->wc_flags);
	wc->pkey_index = cqe->pkey_index;
	wc->slid = cqe->slid;
	wc->sl = cqe->sl;
	wc->dlid_path_bits = cqe->dlid_path_bits;
	wc->port_num = cqe->port_num;
	wc->venकरोr_err = cqe->venकरोr_err;
	wc->network_hdr_type = pvrdma_network_type_to_ib(cqe->network_hdr_type);

	/* Update shared ring state */
	pvrdma_idx_ring_inc(&cq->ring_state->rx.cons_head, cq->ibcq.cqe);

	वापस 0;
पूर्ण

/**
 * pvrdma_poll_cq - poll क्रम work completion queue entries
 * @ibcq: completion queue
 * @num_entries: the maximum number of entries
 * @wc: poपूर्णांकer to work completion array
 *
 * @वापस: number of polled completion entries
 */
पूर्णांक pvrdma_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc)
अणु
	काष्ठा pvrdma_cq *cq = to_vcq(ibcq);
	काष्ठा pvrdma_qp *cur_qp = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक npolled;

	अगर (num_entries < 1 || wc == शून्य)
		वापस 0;

	spin_lock_irqsave(&cq->cq_lock, flags);
	क्रम (npolled = 0; npolled < num_entries; ++npolled) अणु
		अगर (pvrdma_poll_one(cq, &cur_qp, wc + npolled))
			अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&cq->cq_lock, flags);

	/* Ensure we करो not वापस errors from poll_cq */
	वापस npolled;
पूर्ण
