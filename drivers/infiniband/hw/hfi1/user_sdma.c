<शैली गुरु>
/*
 * Copyright(c) 2020 - Cornelis Networks, Inc.
 * Copyright(c) 2015 - 2018 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पन.स>
#समावेश <linux/uपन.स>
#समावेश <linux/rbtree.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/माला.स>

#समावेश "hfi.h"
#समावेश "sdma.h"
#समावेश "mmu_rb.h"
#समावेश "user_sdma.h"
#समावेश "verbs.h"  /* क्रम the headers */
#समावेश "common.h" /* क्रम काष्ठा hfi1_tid_info */
#समावेश "trace.h"

अटल uपूर्णांक hfi1_sdma_comp_ring_size = 128;
module_param_named(sdma_comp_size, hfi1_sdma_comp_ring_size, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(sdma_comp_size, "Size of User SDMA completion ring. Default: 128");

अटल अचिन्हित initial_pkt_count = 8;

अटल पूर्णांक user_sdma_send_pkts(काष्ठा user_sdma_request *req, u16 maxpkts);
अटल व्योम user_sdma_txreq_cb(काष्ठा sdma_txreq *txreq, पूर्णांक status);
अटल अंतरभूत व्योम pq_update(काष्ठा hfi1_user_sdma_pkt_q *pq);
अटल व्योम user_sdma_मुक्त_request(काष्ठा user_sdma_request *req, bool unpin);
अटल पूर्णांक pin_vector_pages(काष्ठा user_sdma_request *req,
			    काष्ठा user_sdma_iovec *iovec);
अटल व्योम unpin_vector_pages(काष्ठा mm_काष्ठा *mm, काष्ठा page **pages,
			       अचिन्हित start, अचिन्हित npages);
अटल पूर्णांक check_header_ढाँचा(काष्ठा user_sdma_request *req,
				 काष्ठा hfi1_pkt_header *hdr, u32 lrhlen,
				 u32 datalen);
अटल पूर्णांक set_txreq_header(काष्ठा user_sdma_request *req,
			    काष्ठा user_sdma_txreq *tx, u32 datalen);
अटल पूर्णांक set_txreq_header_ahg(काष्ठा user_sdma_request *req,
				काष्ठा user_sdma_txreq *tx, u32 len);
अटल अंतरभूत व्योम set_comp_state(काष्ठा hfi1_user_sdma_pkt_q *pq,
				  काष्ठा hfi1_user_sdma_comp_q *cq,
				  u16 idx, क्रमागत hfi1_sdma_comp_state state,
				  पूर्णांक ret);
अटल अंतरभूत u32 set_pkt_bth_psn(__be32 bthpsn, u8 expct, u32 frags);
अटल अंतरभूत u32 get_lrh_len(काष्ठा hfi1_pkt_header, u32 len);

अटल पूर्णांक defer_packet_queue(
	काष्ठा sdma_engine *sde,
	काष्ठा ioरुको_work *रुको,
	काष्ठा sdma_txreq *txreq,
	uपूर्णांक seq,
	bool pkts_sent);
अटल व्योम activate_packet_queue(काष्ठा ioरुको *रुको, पूर्णांक reason);
अटल bool sdma_rb_filter(काष्ठा mmu_rb_node *node, अचिन्हित दीर्घ addr,
			   अचिन्हित दीर्घ len);
अटल पूर्णांक sdma_rb_insert(व्योम *arg, काष्ठा mmu_rb_node *mnode);
अटल पूर्णांक sdma_rb_evict(व्योम *arg, काष्ठा mmu_rb_node *mnode,
			 व्योम *arg2, bool *stop);
अटल व्योम sdma_rb_हटाओ(व्योम *arg, काष्ठा mmu_rb_node *mnode);
अटल पूर्णांक sdma_rb_invalidate(व्योम *arg, काष्ठा mmu_rb_node *mnode);

अटल काष्ठा mmu_rb_ops sdma_rb_ops = अणु
	.filter = sdma_rb_filter,
	.insert = sdma_rb_insert,
	.evict = sdma_rb_evict,
	.हटाओ = sdma_rb_हटाओ,
	.invalidate = sdma_rb_invalidate
पूर्ण;

अटल पूर्णांक defer_packet_queue(
	काष्ठा sdma_engine *sde,
	काष्ठा ioरुको_work *रुको,
	काष्ठा sdma_txreq *txreq,
	uपूर्णांक seq,
	bool pkts_sent)
अणु
	काष्ठा hfi1_user_sdma_pkt_q *pq =
		container_of(रुको->iow, काष्ठा hfi1_user_sdma_pkt_q, busy);

	ग_लिखो_seqlock(&sde->रुकोlock);
	trace_hfi1_usdma_defer(pq, sde, &pq->busy);
	अगर (sdma_progress(sde, seq, txreq))
		जाओ eagain;
	/*
	 * We are assuming that अगर the list is enqueued somewhere, it
	 * is to the dmaरुको list since that is the only place where
	 * it is supposed to be enqueued.
	 */
	xchg(&pq->state, SDMA_PKT_Q_DEFERRED);
	अगर (list_empty(&pq->busy.list)) अणु
		pq->busy.lock = &sde->रुकोlock;
		ioरुको_get_priority(&pq->busy);
		ioरुको_queue(pkts_sent, &pq->busy, &sde->dmaरुको);
	पूर्ण
	ग_लिखो_sequnlock(&sde->रुकोlock);
	वापस -EBUSY;
eagain:
	ग_लिखो_sequnlock(&sde->रुकोlock);
	वापस -EAGAIN;
पूर्ण

अटल व्योम activate_packet_queue(काष्ठा ioरुको *रुको, पूर्णांक reason)
अणु
	काष्ठा hfi1_user_sdma_pkt_q *pq =
		container_of(रुको, काष्ठा hfi1_user_sdma_pkt_q, busy);

	trace_hfi1_usdma_activate(pq, रुको, reason);
	xchg(&pq->state, SDMA_PKT_Q_ACTIVE);
	wake_up(&रुको->रुको_dma);
पूर्ण;

पूर्णांक hfi1_user_sdma_alloc_queues(काष्ठा hfi1_ctxtdata *uctxt,
				काष्ठा hfi1_filedata *fd)
अणु
	पूर्णांक ret = -ENOMEM;
	अक्षर buf[64];
	काष्ठा hfi1_devdata *dd;
	काष्ठा hfi1_user_sdma_comp_q *cq;
	काष्ठा hfi1_user_sdma_pkt_q *pq;

	अगर (!uctxt || !fd)
		वापस -EBADF;

	अगर (!hfi1_sdma_comp_ring_size)
		वापस -EINVAL;

	dd = uctxt->dd;

	pq = kzalloc(माप(*pq), GFP_KERNEL);
	अगर (!pq)
		वापस -ENOMEM;
	pq->dd = dd;
	pq->ctxt = uctxt->ctxt;
	pq->subctxt = fd->subctxt;
	pq->n_max_reqs = hfi1_sdma_comp_ring_size;
	atomic_set(&pq->n_reqs, 0);
	init_रुकोqueue_head(&pq->रुको);
	atomic_set(&pq->n_locked, 0);

	ioरुको_init(&pq->busy, 0, शून्य, शून्य, defer_packet_queue,
		    activate_packet_queue, शून्य, शून्य);
	pq->reqidx = 0;

	pq->reqs = kसुस्मृति(hfi1_sdma_comp_ring_size,
			   माप(*pq->reqs),
			   GFP_KERNEL);
	अगर (!pq->reqs)
		जाओ pq_reqs_nomem;

	pq->req_in_use = kसुस्मृति(BITS_TO_LONGS(hfi1_sdma_comp_ring_size),
				 माप(*pq->req_in_use),
				 GFP_KERNEL);
	अगर (!pq->req_in_use)
		जाओ pq_reqs_no_in_use;

	snम_लिखो(buf, 64, "txreq-kmem-cache-%u-%u-%u", dd->unit, uctxt->ctxt,
		 fd->subctxt);
	pq->txreq_cache = kmem_cache_create(buf,
					    माप(काष्ठा user_sdma_txreq),
					    L1_CACHE_BYTES,
					    SLAB_HWCACHE_ALIGN,
					    शून्य);
	अगर (!pq->txreq_cache) अणु
		dd_dev_err(dd, "[%u] Failed to allocate TxReq cache\n",
			   uctxt->ctxt);
		जाओ pq_txreq_nomem;
	पूर्ण

	cq = kzalloc(माप(*cq), GFP_KERNEL);
	अगर (!cq)
		जाओ cq_nomem;

	cq->comps = vदो_स्मृति_user(PAGE_ALIGN(माप(*cq->comps)
				 * hfi1_sdma_comp_ring_size));
	अगर (!cq->comps)
		जाओ cq_comps_nomem;

	cq->nentries = hfi1_sdma_comp_ring_size;

	ret = hfi1_mmu_rb_रेजिस्टर(pq, &sdma_rb_ops, dd->pport->hfi1_wq,
				   &pq->handler);
	अगर (ret) अणु
		dd_dev_err(dd, "Failed to register with MMU %d", ret);
		जाओ pq_mmu_fail;
	पूर्ण

	rcu_assign_poपूर्णांकer(fd->pq, pq);
	fd->cq = cq;

	वापस 0;

pq_mmu_fail:
	vमुक्त(cq->comps);
cq_comps_nomem:
	kमुक्त(cq);
cq_nomem:
	kmem_cache_destroy(pq->txreq_cache);
pq_txreq_nomem:
	kमुक्त(pq->req_in_use);
pq_reqs_no_in_use:
	kमुक्त(pq->reqs);
pq_reqs_nomem:
	kमुक्त(pq);

	वापस ret;
पूर्ण

अटल व्योम flush_pq_ioरुको(काष्ठा hfi1_user_sdma_pkt_q *pq)
अणु
	अचिन्हित दीर्घ flags;
	seqlock_t *lock = pq->busy.lock;

	अगर (!lock)
		वापस;
	ग_लिखो_seqlock_irqsave(lock, flags);
	अगर (!list_empty(&pq->busy.list)) अणु
		list_del_init(&pq->busy.list);
		pq->busy.lock = शून्य;
	पूर्ण
	ग_लिखो_sequnlock_irqrestore(lock, flags);
पूर्ण

पूर्णांक hfi1_user_sdma_मुक्त_queues(काष्ठा hfi1_filedata *fd,
			       काष्ठा hfi1_ctxtdata *uctxt)
अणु
	काष्ठा hfi1_user_sdma_pkt_q *pq;

	trace_hfi1_sdma_user_मुक्त_queues(uctxt->dd, uctxt->ctxt, fd->subctxt);

	spin_lock(&fd->pq_rcu_lock);
	pq = srcu_dereference_check(fd->pq, &fd->pq_srcu,
				    lockdep_is_held(&fd->pq_rcu_lock));
	अगर (pq) अणु
		rcu_assign_poपूर्णांकer(fd->pq, शून्य);
		spin_unlock(&fd->pq_rcu_lock);
		synchronize_srcu(&fd->pq_srcu);
		/* at this poपूर्णांक there can be no more new requests */
		अगर (pq->handler)
			hfi1_mmu_rb_unरेजिस्टर(pq->handler);
		ioरुको_sdma_drain(&pq->busy);
		/* Wait until all requests have been मुक्तd. */
		रुको_event_पूर्णांकerruptible(
			pq->रुको,
			!atomic_पढ़ो(&pq->n_reqs));
		kमुक्त(pq->reqs);
		kमुक्त(pq->req_in_use);
		kmem_cache_destroy(pq->txreq_cache);
		flush_pq_ioरुको(pq);
		kमुक्त(pq);
	पूर्ण अन्यथा अणु
		spin_unlock(&fd->pq_rcu_lock);
	पूर्ण
	अगर (fd->cq) अणु
		vमुक्त(fd->cq->comps);
		kमुक्त(fd->cq);
		fd->cq = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल u8 dlid_to_selector(u16 dlid)
अणु
	अटल u8 mapping[256];
	अटल पूर्णांक initialized;
	अटल u8 next;
	पूर्णांक hash;

	अगर (!initialized) अणु
		स_रखो(mapping, 0xFF, 256);
		initialized = 1;
	पूर्ण

	hash = ((dlid >> 8) ^ dlid) & 0xFF;
	अगर (mapping[hash] == 0xFF) अणु
		mapping[hash] = next;
		next = (next + 1) & 0x7F;
	पूर्ण

	वापस mapping[hash];
पूर्ण

/**
 * hfi1_user_sdma_process_request() - Process and start a user sdma request
 * @fd: valid file descriptor
 * @iovec: array of io vectors to process
 * @dim: overall iovec array size
 * @count: number of io vector array entries processed
 */
पूर्णांक hfi1_user_sdma_process_request(काष्ठा hfi1_filedata *fd,
				   काष्ठा iovec *iovec, अचिन्हित दीर्घ dim,
				   अचिन्हित दीर्घ *count)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	काष्ठा hfi1_user_sdma_pkt_q *pq =
		srcu_dereference(fd->pq, &fd->pq_srcu);
	काष्ठा hfi1_user_sdma_comp_q *cq = fd->cq;
	काष्ठा hfi1_devdata *dd = pq->dd;
	अचिन्हित दीर्घ idx = 0;
	u8 pcount = initial_pkt_count;
	काष्ठा sdma_req_info info;
	काष्ठा user_sdma_request *req;
	u8 opcode, sc, vl;
	u16 pkey;
	u32 slid;
	u16 dlid;
	u32 selector;

	अगर (iovec[idx].iov_len < माप(info) + माप(req->hdr)) अणु
		hfi1_cdbg(
		   SDMA,
		   "[%u:%u:%u] First vector not big enough for header %lu/%lu",
		   dd->unit, uctxt->ctxt, fd->subctxt,
		   iovec[idx].iov_len, माप(info) + माप(req->hdr));
		वापस -EINVAL;
	पूर्ण
	ret = copy_from_user(&info, iovec[idx].iov_base, माप(info));
	अगर (ret) अणु
		hfi1_cdbg(SDMA, "[%u:%u:%u] Failed to copy info QW (%d)",
			  dd->unit, uctxt->ctxt, fd->subctxt, ret);
		वापस -EFAULT;
	पूर्ण

	trace_hfi1_sdma_user_reqinfo(dd, uctxt->ctxt, fd->subctxt,
				     (u16 *)&info);
	अगर (info.comp_idx >= hfi1_sdma_comp_ring_size) अणु
		hfi1_cdbg(SDMA,
			  "[%u:%u:%u:%u] Invalid comp index",
			  dd->unit, uctxt->ctxt, fd->subctxt, info.comp_idx);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Sanity check the header io vector count.  Need at least 1 vector
	 * (header) and cannot be larger than the actual io vector count.
	 */
	अगर (req_iovcnt(info.ctrl) < 1 || req_iovcnt(info.ctrl) > dim) अणु
		hfi1_cdbg(SDMA,
			  "[%u:%u:%u:%u] Invalid iov count %d, dim %ld",
			  dd->unit, uctxt->ctxt, fd->subctxt, info.comp_idx,
			  req_iovcnt(info.ctrl), dim);
		वापस -EINVAL;
	पूर्ण

	अगर (!info.fragsize) अणु
		hfi1_cdbg(SDMA,
			  "[%u:%u:%u:%u] Request does not specify fragsize",
			  dd->unit, uctxt->ctxt, fd->subctxt, info.comp_idx);
		वापस -EINVAL;
	पूर्ण

	/* Try to claim the request. */
	अगर (test_and_set_bit(info.comp_idx, pq->req_in_use)) अणु
		hfi1_cdbg(SDMA, "[%u:%u:%u] Entry %u is in use",
			  dd->unit, uctxt->ctxt, fd->subctxt,
			  info.comp_idx);
		वापस -EBADSLT;
	पूर्ण
	/*
	 * All safety checks have been करोne and this request has been claimed.
	 */
	trace_hfi1_sdma_user_process_request(dd, uctxt->ctxt, fd->subctxt,
					     info.comp_idx);
	req = pq->reqs + info.comp_idx;
	req->data_iovs = req_iovcnt(info.ctrl) - 1; /* subtract header vector */
	req->data_len  = 0;
	req->pq = pq;
	req->cq = cq;
	req->ahg_idx = -1;
	req->iov_idx = 0;
	req->sent = 0;
	req->seqnum = 0;
	req->seqcomp = 0;
	req->seqsubmitted = 0;
	req->tids = शून्य;
	req->has_error = 0;
	INIT_LIST_HEAD(&req->txps);

	स_नकल(&req->info, &info, माप(info));

	/* The request is initialized, count it */
	atomic_inc(&pq->n_reqs);

	अगर (req_opcode(info.ctrl) == EXPECTED) अणु
		/* expected must have a TID info and at least one data vector */
		अगर (req->data_iovs < 2) अणु
			SDMA_DBG(req,
				 "Not enough vectors for expected request");
			ret = -EINVAL;
			जाओ मुक्त_req;
		पूर्ण
		req->data_iovs--;
	पूर्ण

	अगर (!info.npkts || req->data_iovs > MAX_VECTORS_PER_REQ) अणु
		SDMA_DBG(req, "Too many vectors (%u/%u)", req->data_iovs,
			 MAX_VECTORS_PER_REQ);
		ret = -EINVAL;
		जाओ मुक्त_req;
	पूर्ण
	/* Copy the header from the user buffer */
	ret = copy_from_user(&req->hdr, iovec[idx].iov_base + माप(info),
			     माप(req->hdr));
	अगर (ret) अणु
		SDMA_DBG(req, "Failed to copy header template (%d)", ret);
		ret = -EFAULT;
		जाओ मुक्त_req;
	पूर्ण

	/* If Static rate control is not enabled, sanitize the header. */
	अगर (!HFI1_CAP_IS_USET(STATIC_RATE_CTRL))
		req->hdr.pbc[2] = 0;

	/* Validate the opcode. Do not trust packets from user space blindly. */
	opcode = (be32_to_cpu(req->hdr.bth[0]) >> 24) & 0xff;
	अगर ((opcode & USER_OPCODE_CHECK_MASK) !=
	     USER_OPCODE_CHECK_VAL) अणु
		SDMA_DBG(req, "Invalid opcode (%d)", opcode);
		ret = -EINVAL;
		जाओ मुक्त_req;
	पूर्ण
	/*
	 * Validate the vl. Do not trust packets from user space blindly.
	 * VL comes from PBC, SC comes from LRH, and the VL needs to
	 * match the SC look up.
	 */
	vl = (le16_to_cpu(req->hdr.pbc[0]) >> 12) & 0xF;
	sc = (((be16_to_cpu(req->hdr.lrh[0]) >> 12) & 0xF) |
	      (((le16_to_cpu(req->hdr.pbc[1]) >> 14) & 0x1) << 4));
	अगर (vl >= dd->pport->vls_operational ||
	    vl != sc_to_vlt(dd, sc)) अणु
		SDMA_DBG(req, "Invalid SC(%u)/VL(%u)", sc, vl);
		ret = -EINVAL;
		जाओ मुक्त_req;
	पूर्ण

	/* Checking P_KEY क्रम requests from user-space */
	pkey = (u16)be32_to_cpu(req->hdr.bth[0]);
	slid = be16_to_cpu(req->hdr.lrh[3]);
	अगर (egress_pkey_check(dd->pport, slid, pkey, sc, PKEY_CHECK_INVALID)) अणु
		ret = -EINVAL;
		जाओ मुक्त_req;
	पूर्ण

	/*
	 * Also should check the BTH.lnh. If it says the next header is GRH then
	 * the RXE parsing will be off and will land in the middle of the KDETH
	 * or miss it entirely.
	 */
	अगर ((be16_to_cpu(req->hdr.lrh[0]) & 0x3) == HFI1_LRH_GRH) अणु
		SDMA_DBG(req, "User tried to pass in a GRH");
		ret = -EINVAL;
		जाओ मुक्त_req;
	पूर्ण

	req->koffset = le32_to_cpu(req->hdr.kdeth.swdata[6]);
	/*
	 * Calculate the initial TID offset based on the values of
	 * KDETH.OFFSET and KDETH.OM that are passed in.
	 */
	req->tiकरोffset = KDETH_GET(req->hdr.kdeth.ver_tid_offset, OFFSET) *
		(KDETH_GET(req->hdr.kdeth.ver_tid_offset, OM) ?
		 KDETH_OM_LARGE : KDETH_OM_SMALL);
	trace_hfi1_sdma_user_initial_tiकरोffset(dd, uctxt->ctxt, fd->subctxt,
					       info.comp_idx, req->tiकरोffset);
	idx++;

	/* Save all the IO vector काष्ठाures */
	क्रम (i = 0; i < req->data_iovs; i++) अणु
		req->iovs[i].offset = 0;
		INIT_LIST_HEAD(&req->iovs[i].list);
		स_नकल(&req->iovs[i].iov,
		       iovec + idx++,
		       माप(req->iovs[i].iov));
		ret = pin_vector_pages(req, &req->iovs[i]);
		अगर (ret) अणु
			req->data_iovs = i;
			जाओ मुक्त_req;
		पूर्ण
		req->data_len += req->iovs[i].iov.iov_len;
	पूर्ण
	trace_hfi1_sdma_user_data_length(dd, uctxt->ctxt, fd->subctxt,
					 info.comp_idx, req->data_len);
	अगर (pcount > req->info.npkts)
		pcount = req->info.npkts;
	/*
	 * Copy any TID info
	 * User space will provide the TID info only when the
	 * request type is EXPECTED. This is true even अगर there is
	 * only one packet in the request and the header is alपढ़ोy
	 * setup. The reason क्रम the singular TID हाल is that the
	 * driver needs to perक्रमm safety checks.
	 */
	अगर (req_opcode(req->info.ctrl) == EXPECTED) अणु
		u16 ntids = iovec[idx].iov_len / माप(*req->tids);
		u32 *पंचांगp;

		अगर (!ntids || ntids > MAX_TID_PAIR_ENTRIES) अणु
			ret = -EINVAL;
			जाओ मुक्त_req;
		पूर्ण

		/*
		 * We have to copy all of the tids because they may vary
		 * in size and, thereक्रमe, the TID count might not be
		 * equal to the pkt count. However, there is no way to
		 * tell at this poपूर्णांक.
		 */
		पंचांगp = memdup_user(iovec[idx].iov_base,
				  ntids * माप(*req->tids));
		अगर (IS_ERR(पंचांगp)) अणु
			ret = PTR_ERR(पंचांगp);
			SDMA_DBG(req, "Failed to copy %d TIDs (%d)",
				 ntids, ret);
			जाओ मुक्त_req;
		पूर्ण
		req->tids = पंचांगp;
		req->n_tids = ntids;
		req->tididx = 0;
		idx++;
	पूर्ण

	dlid = be16_to_cpu(req->hdr.lrh[1]);
	selector = dlid_to_selector(dlid);
	selector += uctxt->ctxt + fd->subctxt;
	req->sde = sdma_select_user_engine(dd, selector, vl);

	अगर (!req->sde || !sdma_running(req->sde)) अणु
		ret = -ECOMM;
		जाओ मुक्त_req;
	पूर्ण

	/* We करोn't need an AHG entry अगर the request contains only one packet */
	अगर (req->info.npkts > 1 && HFI1_CAP_IS_USET(SDMA_AHG))
		req->ahg_idx = sdma_ahg_alloc(req->sde);

	set_comp_state(pq, cq, info.comp_idx, QUEUED, 0);
	pq->state = SDMA_PKT_Q_ACTIVE;

	/*
	 * This is a somewhat blocking send implementation.
	 * The driver will block the caller until all packets of the
	 * request have been submitted to the SDMA engine. However, it
	 * will not रुको क्रम send completions.
	 */
	जबतक (req->seqsubmitted != req->info.npkts) अणु
		ret = user_sdma_send_pkts(req, pcount);
		अगर (ret < 0) अणु
			पूर्णांक we_ret;

			अगर (ret != -EBUSY)
				जाओ मुक्त_req;
			we_ret = रुको_event_पूर्णांकerruptible_समयout(
				pq->busy.रुको_dma,
				pq->state == SDMA_PKT_Q_ACTIVE,
				msecs_to_jअगरfies(
					SDMA_IOWAIT_TIMEOUT));
			trace_hfi1_usdma_we(pq, we_ret);
			अगर (we_ret <= 0)
				flush_pq_ioरुको(pq);
		पूर्ण
	पूर्ण
	*count += idx;
	वापस 0;
मुक्त_req:
	/*
	 * If the submitted seqsubmitted == npkts, the completion routine
	 * controls the final state.  If sequbmitted < npkts, रुको क्रम any
	 * outstanding packets to finish beक्रमe cleaning up.
	 */
	अगर (req->seqsubmitted < req->info.npkts) अणु
		अगर (req->seqsubmitted)
			रुको_event(pq->busy.रुको_dma,
				   (req->seqcomp == req->seqsubmitted - 1));
		user_sdma_मुक्त_request(req, true);
		pq_update(pq);
		set_comp_state(pq, cq, info.comp_idx, ERROR, ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत u32 compute_data_length(काष्ठा user_sdma_request *req,
				      काष्ठा user_sdma_txreq *tx)
अणु
	/*
	 * Determine the proper size of the packet data.
	 * The size of the data of the first packet is in the header
	 * ढाँचा. However, it includes the header and ICRC, which need
	 * to be subtracted.
	 * The minimum representable packet data length in a header is 4 bytes,
	 * thereक्रमe, when the data length request is less than 4 bytes, there's
	 * only one packet, and the packet data length is equal to that of the
	 * request data length.
	 * The size of the reमुख्यing packets is the minimum of the frag
	 * size (MTU) or reमुख्यing data in the request.
	 */
	u32 len;

	अगर (!req->seqnum) अणु
		अगर (req->data_len < माप(u32))
			len = req->data_len;
		अन्यथा
			len = ((be16_to_cpu(req->hdr.lrh[2]) << 2) -
			       (माप(tx->hdr) - 4));
	पूर्ण अन्यथा अगर (req_opcode(req->info.ctrl) == EXPECTED) अणु
		u32 tidlen = EXP_TID_GET(req->tids[req->tididx], LEN) *
			PAGE_SIZE;
		/*
		 * Get the data length based on the reमुख्यing space in the
		 * TID pair.
		 */
		len = min(tidlen - req->tiकरोffset, (u32)req->info.fragsize);
		/* If we've filled up the TID pair, move to the next one. */
		अगर (unlikely(!len) && ++req->tididx < req->n_tids &&
		    req->tids[req->tididx]) अणु
			tidlen = EXP_TID_GET(req->tids[req->tididx],
					     LEN) * PAGE_SIZE;
			req->tiकरोffset = 0;
			len = min_t(u32, tidlen, req->info.fragsize);
		पूर्ण
		/*
		 * Since the TID pairs map entire pages, make sure that we
		 * are not going to try to send more data that we have
		 * reमुख्यing.
		 */
		len = min(len, req->data_len - req->sent);
	पूर्ण अन्यथा अणु
		len = min(req->data_len - req->sent, (u32)req->info.fragsize);
	पूर्ण
	trace_hfi1_sdma_user_compute_length(req->pq->dd,
					    req->pq->ctxt,
					    req->pq->subctxt,
					    req->info.comp_idx,
					    len);
	वापस len;
पूर्ण

अटल अंतरभूत u32 pad_len(u32 len)
अणु
	अगर (len & (माप(u32) - 1))
		len += माप(u32) - (len & (माप(u32) - 1));
	वापस len;
पूर्ण

अटल अंतरभूत u32 get_lrh_len(काष्ठा hfi1_pkt_header hdr, u32 len)
अणु
	/* (Size of complete header - size of PBC) + 4B ICRC + data length */
	वापस ((माप(hdr) - माप(hdr.pbc)) + 4 + len);
पूर्ण

अटल पूर्णांक user_sdma_txadd_ahg(काष्ठा user_sdma_request *req,
			       काष्ठा user_sdma_txreq *tx,
			       u32 datalen)
अणु
	पूर्णांक ret;
	u16 pbclen = le16_to_cpu(req->hdr.pbc[0]);
	u32 lrhlen = get_lrh_len(req->hdr, pad_len(datalen));
	काष्ठा hfi1_user_sdma_pkt_q *pq = req->pq;

	/*
	 * Copy the request header पूर्णांकo the tx header
	 * because the HW needs a cacheline-aligned
	 * address.
	 * This copy can be optimized out अगर the hdr
	 * member of user_sdma_request were also
	 * cacheline aligned.
	 */
	स_नकल(&tx->hdr, &req->hdr, माप(tx->hdr));
	अगर (PBC2LRH(pbclen) != lrhlen) अणु
		pbclen = (pbclen & 0xf000) | LRH2PBC(lrhlen);
		tx->hdr.pbc[0] = cpu_to_le16(pbclen);
	पूर्ण
	ret = check_header_ढाँचा(req, &tx->hdr, lrhlen, datalen);
	अगर (ret)
		वापस ret;
	ret = sdma_txinit_ahg(&tx->txreq, SDMA_TXREQ_F_AHG_COPY,
			      माप(tx->hdr) + datalen, req->ahg_idx,
			      0, शून्य, 0, user_sdma_txreq_cb);
	अगर (ret)
		वापस ret;
	ret = sdma_txadd_kvaddr(pq->dd, &tx->txreq, &tx->hdr, माप(tx->hdr));
	अगर (ret)
		sdma_txclean(pq->dd, &tx->txreq);
	वापस ret;
पूर्ण

अटल पूर्णांक user_sdma_txadd(काष्ठा user_sdma_request *req,
			   काष्ठा user_sdma_txreq *tx,
			   काष्ठा user_sdma_iovec *iovec, u32 datalen,
			   u32 *queued_ptr, u32 *data_sent_ptr,
			   u64 *iov_offset_ptr)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक pageidx, len;
	अचिन्हित दीर्घ base, offset;
	u64 iov_offset = *iov_offset_ptr;
	u32 queued = *queued_ptr, data_sent = *data_sent_ptr;
	काष्ठा hfi1_user_sdma_pkt_q *pq = req->pq;

	base = (अचिन्हित दीर्घ)iovec->iov.iov_base;
	offset = offset_in_page(base + iovec->offset + iov_offset);
	pageidx = (((iovec->offset + iov_offset + base) - (base & PAGE_MASK)) >>
		   PAGE_SHIFT);
	len = offset + req->info.fragsize > PAGE_SIZE ?
		PAGE_SIZE - offset : req->info.fragsize;
	len = min((datalen - queued), len);
	ret = sdma_txadd_page(pq->dd, &tx->txreq, iovec->pages[pageidx],
			      offset, len);
	अगर (ret) अणु
		SDMA_DBG(req, "SDMA txreq add page failed %d\n", ret);
		वापस ret;
	पूर्ण
	iov_offset += len;
	queued += len;
	data_sent += len;
	अगर (unlikely(queued < datalen && pageidx == iovec->npages &&
		     req->iov_idx < req->data_iovs - 1)) अणु
		iovec->offset += iov_offset;
		iovec = &req->iovs[++req->iov_idx];
		iov_offset = 0;
	पूर्ण

	*queued_ptr = queued;
	*data_sent_ptr = data_sent;
	*iov_offset_ptr = iov_offset;
	वापस ret;
पूर्ण

अटल पूर्णांक user_sdma_send_pkts(काष्ठा user_sdma_request *req, u16 maxpkts)
अणु
	पूर्णांक ret = 0;
	u16 count;
	अचिन्हित npkts = 0;
	काष्ठा user_sdma_txreq *tx = शून्य;
	काष्ठा hfi1_user_sdma_pkt_q *pq = शून्य;
	काष्ठा user_sdma_iovec *iovec = शून्य;

	अगर (!req->pq)
		वापस -EINVAL;

	pq = req->pq;

	/* If tx completion has reported an error, we are करोne. */
	अगर (READ_ONCE(req->has_error))
		वापस -EFAULT;

	/*
	 * Check अगर we might have sent the entire request alपढ़ोy
	 */
	अगर (unlikely(req->seqnum == req->info.npkts)) अणु
		अगर (!list_empty(&req->txps))
			जाओ करोsend;
		वापस ret;
	पूर्ण

	अगर (!maxpkts || maxpkts > req->info.npkts - req->seqnum)
		maxpkts = req->info.npkts - req->seqnum;

	जबतक (npkts < maxpkts) अणु
		u32 datalen = 0, queued = 0, data_sent = 0;
		u64 iov_offset = 0;

		/*
		 * Check whether any of the completions have come back
		 * with errors. If so, we are not going to process any
		 * more packets from this request.
		 */
		अगर (READ_ONCE(req->has_error))
			वापस -EFAULT;

		tx = kmem_cache_alloc(pq->txreq_cache, GFP_KERNEL);
		अगर (!tx)
			वापस -ENOMEM;

		tx->flags = 0;
		tx->req = req;
		INIT_LIST_HEAD(&tx->list);

		/*
		 * For the last packet set the ACK request
		 * and disable header suppression.
		 */
		अगर (req->seqnum == req->info.npkts - 1)
			tx->flags |= (TXREQ_FLAGS_REQ_ACK |
				      TXREQ_FLAGS_REQ_DISABLE_SH);

		/*
		 * Calculate the payload size - this is min of the fragment
		 * (MTU) size or the reमुख्यing bytes in the request but only
		 * अगर we have payload data.
		 */
		अगर (req->data_len) अणु
			iovec = &req->iovs[req->iov_idx];
			अगर (READ_ONCE(iovec->offset) == iovec->iov.iov_len) अणु
				अगर (++req->iov_idx == req->data_iovs) अणु
					ret = -EFAULT;
					जाओ मुक्त_tx;
				पूर्ण
				iovec = &req->iovs[req->iov_idx];
				WARN_ON(iovec->offset);
			पूर्ण

			datalen = compute_data_length(req, tx);

			/*
			 * Disable header suppression क्रम the payload <= 8DWS.
			 * If there is an uncorrectable error in the receive
			 * data FIFO when the received payload size is less than
			 * or equal to 8DWS then the RxDmaDataFअगरoRdUncErr is
			 * not reported.There is set RHF.EccErr अगर the header
			 * is not suppressed.
			 */
			अगर (!datalen) अणु
				SDMA_DBG(req,
					 "Request has data but pkt len is 0");
				ret = -EFAULT;
				जाओ मुक्त_tx;
			पूर्ण अन्यथा अगर (datalen <= 32) अणु
				tx->flags |= TXREQ_FLAGS_REQ_DISABLE_SH;
			पूर्ण
		पूर्ण

		अगर (req->ahg_idx >= 0) अणु
			अगर (!req->seqnum) अणु
				ret = user_sdma_txadd_ahg(req, tx, datalen);
				अगर (ret)
					जाओ मुक्त_tx;
			पूर्ण अन्यथा अणु
				पूर्णांक changes;

				changes = set_txreq_header_ahg(req, tx,
							       datalen);
				अगर (changes < 0) अणु
					ret = changes;
					जाओ मुक्त_tx;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = sdma_txinit(&tx->txreq, 0, माप(req->hdr) +
					  datalen, user_sdma_txreq_cb);
			अगर (ret)
				जाओ मुक्त_tx;
			/*
			 * Modअगरy the header क्रम this packet. This only needs
			 * to be करोne अगर we are not going to use AHG. Otherwise,
			 * the HW will करो it based on the changes we gave it
			 * during sdma_txinit_ahg().
			 */
			ret = set_txreq_header(req, tx, datalen);
			अगर (ret)
				जाओ मुक्त_txreq;
		पूर्ण

		/*
		 * If the request contains any data vectors, add up to
		 * fragsize bytes to the descriptor.
		 */
		जबतक (queued < datalen &&
		       (req->sent + data_sent) < req->data_len) अणु
			ret = user_sdma_txadd(req, tx, iovec, datalen,
					      &queued, &data_sent, &iov_offset);
			अगर (ret)
				जाओ मुक्त_txreq;
		पूर्ण
		/*
		 * The txreq was submitted successfully so we can update
		 * the counters.
		 */
		req->koffset += datalen;
		अगर (req_opcode(req->info.ctrl) == EXPECTED)
			req->tiकरोffset += datalen;
		req->sent += data_sent;
		अगर (req->data_len)
			iovec->offset += iov_offset;
		list_add_tail(&tx->txreq.list, &req->txps);
		/*
		 * It is important to increment this here as it is used to
		 * generate the BTH.PSN and, thereक्रमe, can't be bulk-updated
		 * outside of the loop.
		 */
		tx->seqnum = req->seqnum++;
		npkts++;
	पूर्ण
करोsend:
	ret = sdma_send_txlist(req->sde,
			       ioरुको_get_ib_work(&pq->busy),
			       &req->txps, &count);
	req->seqsubmitted += count;
	अगर (req->seqsubmitted == req->info.npkts) अणु
		/*
		 * The txreq has alपढ़ोy been submitted to the HW queue
		 * so we can मुक्त the AHG entry now. Corruption will not
		 * happen due to the sequential manner in which
		 * descriptors are processed.
		 */
		अगर (req->ahg_idx >= 0)
			sdma_ahg_मुक्त(req->sde, req->ahg_idx);
	पूर्ण
	वापस ret;

मुक्त_txreq:
	sdma_txclean(pq->dd, &tx->txreq);
मुक्त_tx:
	kmem_cache_मुक्त(pq->txreq_cache, tx);
	वापस ret;
पूर्ण

अटल u32 sdma_cache_evict(काष्ठा hfi1_user_sdma_pkt_q *pq, u32 npages)
अणु
	काष्ठा evict_data evict_data;

	evict_data.cleared = 0;
	evict_data.target = npages;
	hfi1_mmu_rb_evict(pq->handler, &evict_data);
	वापस evict_data.cleared;
पूर्ण

अटल पूर्णांक pin_sdma_pages(काष्ठा user_sdma_request *req,
			  काष्ठा user_sdma_iovec *iovec,
			  काष्ठा sdma_mmu_node *node,
			  पूर्णांक npages)
अणु
	पूर्णांक pinned, cleared;
	काष्ठा page **pages;
	काष्ठा hfi1_user_sdma_pkt_q *pq = req->pq;

	pages = kसुस्मृति(npages, माप(*pages), GFP_KERNEL);
	अगर (!pages)
		वापस -ENOMEM;
	स_नकल(pages, node->pages, node->npages * माप(*pages));

	npages -= node->npages;
retry:
	अगर (!hfi1_can_pin_pages(pq->dd, current->mm,
				atomic_पढ़ो(&pq->n_locked), npages)) अणु
		cleared = sdma_cache_evict(pq, npages);
		अगर (cleared >= npages)
			जाओ retry;
	पूर्ण
	pinned = hfi1_acquire_user_pages(current->mm,
					 ((अचिन्हित दीर्घ)iovec->iov.iov_base +
					 (node->npages * PAGE_SIZE)), npages, 0,
					 pages + node->npages);
	अगर (pinned < 0) अणु
		kमुक्त(pages);
		वापस pinned;
	पूर्ण
	अगर (pinned != npages) अणु
		unpin_vector_pages(current->mm, pages, node->npages, pinned);
		वापस -EFAULT;
	पूर्ण
	kमुक्त(node->pages);
	node->rb.len = iovec->iov.iov_len;
	node->pages = pages;
	atomic_add(pinned, &pq->n_locked);
	वापस pinned;
पूर्ण

अटल व्योम unpin_sdma_pages(काष्ठा sdma_mmu_node *node)
अणु
	अगर (node->npages) अणु
		unpin_vector_pages(mm_from_sdma_node(node), node->pages, 0,
				   node->npages);
		atomic_sub(node->npages, &node->pq->n_locked);
	पूर्ण
पूर्ण

अटल पूर्णांक pin_vector_pages(काष्ठा user_sdma_request *req,
			    काष्ठा user_sdma_iovec *iovec)
अणु
	पूर्णांक ret = 0, pinned, npages;
	काष्ठा hfi1_user_sdma_pkt_q *pq = req->pq;
	काष्ठा sdma_mmu_node *node = शून्य;
	काष्ठा mmu_rb_node *rb_node;
	काष्ठा iovec *iov;
	bool extracted;

	extracted =
		hfi1_mmu_rb_हटाओ_unless_exact(pq->handler,
						(अचिन्हित दीर्घ)
						iovec->iov.iov_base,
						iovec->iov.iov_len, &rb_node);
	अगर (rb_node) अणु
		node = container_of(rb_node, काष्ठा sdma_mmu_node, rb);
		अगर (!extracted) अणु
			atomic_inc(&node->refcount);
			iovec->pages = node->pages;
			iovec->npages = node->npages;
			iovec->node = node;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (!node) अणु
		node = kzalloc(माप(*node), GFP_KERNEL);
		अगर (!node)
			वापस -ENOMEM;

		node->rb.addr = (अचिन्हित दीर्घ)iovec->iov.iov_base;
		node->pq = pq;
		atomic_set(&node->refcount, 0);
	पूर्ण

	iov = &iovec->iov;
	npages = num_user_pages((अचिन्हित दीर्घ)iov->iov_base, iov->iov_len);
	अगर (node->npages < npages) अणु
		pinned = pin_sdma_pages(req, iovec, node, npages);
		अगर (pinned < 0) अणु
			ret = pinned;
			जाओ bail;
		पूर्ण
		node->npages += pinned;
		npages = node->npages;
	पूर्ण
	iovec->pages = node->pages;
	iovec->npages = npages;
	iovec->node = node;

	ret = hfi1_mmu_rb_insert(req->pq->handler, &node->rb);
	अगर (ret) अणु
		iovec->node = शून्य;
		जाओ bail;
	पूर्ण
	वापस 0;
bail:
	unpin_sdma_pages(node);
	kमुक्त(node);
	वापस ret;
पूर्ण

अटल व्योम unpin_vector_pages(काष्ठा mm_काष्ठा *mm, काष्ठा page **pages,
			       अचिन्हित start, अचिन्हित npages)
अणु
	hfi1_release_user_pages(mm, pages + start, npages, false);
	kमुक्त(pages);
पूर्ण

अटल पूर्णांक check_header_ढाँचा(काष्ठा user_sdma_request *req,
				 काष्ठा hfi1_pkt_header *hdr, u32 lrhlen,
				 u32 datalen)
अणु
	/*
	 * Perक्रमm safety checks क्रम any type of packet:
	 *    - transfer size is multiple of 64bytes
	 *    - packet length is multiple of 4 bytes
	 *    - packet length is not larger than MTU size
	 *
	 * These checks are only करोne क्रम the first packet of the
	 * transfer since the header is "given" to us by user space.
	 * For the reमुख्यder of the packets we compute the values.
	 */
	अगर (req->info.fragsize % PIO_BLOCK_SIZE || lrhlen & 0x3 ||
	    lrhlen > get_lrh_len(*hdr, req->info.fragsize))
		वापस -EINVAL;

	अगर (req_opcode(req->info.ctrl) == EXPECTED) अणु
		/*
		 * The header is checked only on the first packet. Furthermore,
		 * we ensure that at least one TID entry is copied when the
		 * request is submitted. Thereक्रमe, we करोn't have to verअगरy that
		 * tididx poपूर्णांकs to something sane.
		 */
		u32 tidval = req->tids[req->tididx],
			tidlen = EXP_TID_GET(tidval, LEN) * PAGE_SIZE,
			tididx = EXP_TID_GET(tidval, IDX),
			tidctrl = EXP_TID_GET(tidval, CTRL),
			tiकरोff;
		__le32 kval = hdr->kdeth.ver_tid_offset;

		tiकरोff = KDETH_GET(kval, OFFSET) *
			  (KDETH_GET(req->hdr.kdeth.ver_tid_offset, OM) ?
			   KDETH_OM_LARGE : KDETH_OM_SMALL);
		/*
		 * Expected receive packets have the following
		 * additional checks:
		 *     - offset is not larger than the TID size
		 *     - TIDCtrl values match between header and TID array
		 *     - TID indexes match between header and TID array
		 */
		अगर ((tiकरोff + datalen > tidlen) ||
		    KDETH_GET(kval, TIDCTRL) != tidctrl ||
		    KDETH_GET(kval, TID) != tididx)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Correctly set the BTH.PSN field based on type of
 * transfer - eager packets can just increment the PSN but
 * expected packets encode generation and sequence in the
 * BTH.PSN field so just incrementing will result in errors.
 */
अटल अंतरभूत u32 set_pkt_bth_psn(__be32 bthpsn, u8 expct, u32 frags)
अणु
	u32 val = be32_to_cpu(bthpsn),
		mask = (HFI1_CAP_IS_KSET(EXTENDED_PSN) ? 0x7fffffffull :
			0xffffffull),
		psn = val & mask;
	अगर (expct)
		psn = (psn & ~HFI1_KDETH_BTH_SEQ_MASK) |
			((psn + frags) & HFI1_KDETH_BTH_SEQ_MASK);
	अन्यथा
		psn = psn + frags;
	वापस psn & mask;
पूर्ण

अटल पूर्णांक set_txreq_header(काष्ठा user_sdma_request *req,
			    काष्ठा user_sdma_txreq *tx, u32 datalen)
अणु
	काष्ठा hfi1_user_sdma_pkt_q *pq = req->pq;
	काष्ठा hfi1_pkt_header *hdr = &tx->hdr;
	u8 omfactor; /* KDETH.OM */
	u16 pbclen;
	पूर्णांक ret;
	u32 tidval = 0, lrhlen = get_lrh_len(*hdr, pad_len(datalen));

	/* Copy the header ढाँचा to the request beक्रमe modअगरication */
	स_नकल(hdr, &req->hdr, माप(*hdr));

	/*
	 * Check अगर the PBC and LRH length are mismatched. If so
	 * adjust both in the header.
	 */
	pbclen = le16_to_cpu(hdr->pbc[0]);
	अगर (PBC2LRH(pbclen) != lrhlen) अणु
		pbclen = (pbclen & 0xf000) | LRH2PBC(lrhlen);
		hdr->pbc[0] = cpu_to_le16(pbclen);
		hdr->lrh[2] = cpu_to_be16(lrhlen >> 2);
		/*
		 * Third packet
		 * This is the first packet in the sequence that has
		 * a "static" size that can be used क्रम the rest of
		 * the packets (besides the last one).
		 */
		अगर (unlikely(req->seqnum == 2)) अणु
			/*
			 * From this poपूर्णांक on the lengths in both the
			 * PBC and LRH are the same until the last
			 * packet.
			 * Adjust the ढाँचा so we करोn't have to update
			 * every packet
			 */
			req->hdr.pbc[0] = hdr->pbc[0];
			req->hdr.lrh[2] = hdr->lrh[2];
		पूर्ण
	पूर्ण
	/*
	 * We only have to modअगरy the header अगर this is not the
	 * first packet in the request. Otherwise, we use the
	 * header given to us.
	 */
	अगर (unlikely(!req->seqnum)) अणु
		ret = check_header_ढाँचा(req, hdr, lrhlen, datalen);
		अगर (ret)
			वापस ret;
		जाओ करोne;
	पूर्ण

	hdr->bth[2] = cpu_to_be32(
		set_pkt_bth_psn(hdr->bth[2],
				(req_opcode(req->info.ctrl) == EXPECTED),
				req->seqnum));

	/* Set ACK request on last packet */
	अगर (unlikely(tx->flags & TXREQ_FLAGS_REQ_ACK))
		hdr->bth[2] |= cpu_to_be32(1UL << 31);

	/* Set the new offset */
	hdr->kdeth.swdata[6] = cpu_to_le32(req->koffset);
	/* Expected packets have to fill in the new TID inक्रमmation */
	अगर (req_opcode(req->info.ctrl) == EXPECTED) अणु
		tidval = req->tids[req->tididx];
		/*
		 * If the offset माला_दो us at the end of the current TID,
		 * advance everything.
		 */
		अगर ((req->tiकरोffset) == (EXP_TID_GET(tidval, LEN) *
					 PAGE_SIZE)) अणु
			req->tiकरोffset = 0;
			/*
			 * Since we करोn't copy all the TIDs, all at once,
			 * we have to check again.
			 */
			अगर (++req->tididx > req->n_tids - 1 ||
			    !req->tids[req->tididx]) अणु
				वापस -EINVAL;
			पूर्ण
			tidval = req->tids[req->tididx];
		पूर्ण
		omfactor = EXP_TID_GET(tidval, LEN) * PAGE_SIZE >=
			KDETH_OM_MAX_SIZE ? KDETH_OM_LARGE_SHIFT :
			KDETH_OM_SMALL_SHIFT;
		/* Set KDETH.TIDCtrl based on value क्रम this TID. */
		KDETH_SET(hdr->kdeth.ver_tid_offset, TIDCTRL,
			  EXP_TID_GET(tidval, CTRL));
		/* Set KDETH.TID based on value क्रम this TID */
		KDETH_SET(hdr->kdeth.ver_tid_offset, TID,
			  EXP_TID_GET(tidval, IDX));
		/* Clear KDETH.SH when DISABLE_SH flag is set */
		अगर (unlikely(tx->flags & TXREQ_FLAGS_REQ_DISABLE_SH))
			KDETH_SET(hdr->kdeth.ver_tid_offset, SH, 0);
		/*
		 * Set the KDETH.OFFSET and KDETH.OM based on size of
		 * transfer.
		 */
		trace_hfi1_sdma_user_tid_info(
			pq->dd, pq->ctxt, pq->subctxt, req->info.comp_idx,
			req->tiकरोffset, req->tiकरोffset >> omfactor,
			omfactor != KDETH_OM_SMALL_SHIFT);
		KDETH_SET(hdr->kdeth.ver_tid_offset, OFFSET,
			  req->tiकरोffset >> omfactor);
		KDETH_SET(hdr->kdeth.ver_tid_offset, OM,
			  omfactor != KDETH_OM_SMALL_SHIFT);
	पूर्ण
करोne:
	trace_hfi1_sdma_user_header(pq->dd, pq->ctxt, pq->subctxt,
				    req->info.comp_idx, hdr, tidval);
	वापस sdma_txadd_kvaddr(pq->dd, &tx->txreq, hdr, माप(*hdr));
पूर्ण

अटल पूर्णांक set_txreq_header_ahg(काष्ठा user_sdma_request *req,
				काष्ठा user_sdma_txreq *tx, u32 datalen)
अणु
	u32 ahg[AHG_KDETH_ARRAY_SIZE];
	पूर्णांक idx = 0;
	u8 omfactor; /* KDETH.OM */
	काष्ठा hfi1_user_sdma_pkt_q *pq = req->pq;
	काष्ठा hfi1_pkt_header *hdr = &req->hdr;
	u16 pbclen = le16_to_cpu(hdr->pbc[0]);
	u32 val32, tidval = 0, lrhlen = get_lrh_len(*hdr, pad_len(datalen));
	माप_प्रकार array_size = ARRAY_SIZE(ahg);

	अगर (PBC2LRH(pbclen) != lrhlen) अणु
		/* PBC.PbcLengthDWs */
		idx = ahg_header_set(ahg, idx, array_size, 0, 0, 12,
				     (__क्रमce u16)cpu_to_le16(LRH2PBC(lrhlen)));
		अगर (idx < 0)
			वापस idx;
		/* LRH.PktLen (we need the full 16 bits due to byte swap) */
		idx = ahg_header_set(ahg, idx, array_size, 3, 0, 16,
				     (__क्रमce u16)cpu_to_be16(lrhlen >> 2));
		अगर (idx < 0)
			वापस idx;
	पूर्ण

	/*
	 * Do the common updates
	 */
	/* BTH.PSN and BTH.A */
	val32 = (be32_to_cpu(hdr->bth[2]) + req->seqnum) &
		(HFI1_CAP_IS_KSET(EXTENDED_PSN) ? 0x7fffffff : 0xffffff);
	अगर (unlikely(tx->flags & TXREQ_FLAGS_REQ_ACK))
		val32 |= 1UL << 31;
	idx = ahg_header_set(ahg, idx, array_size, 6, 0, 16,
			     (__क्रमce u16)cpu_to_be16(val32 >> 16));
	अगर (idx < 0)
		वापस idx;
	idx = ahg_header_set(ahg, idx, array_size, 6, 16, 16,
			     (__क्रमce u16)cpu_to_be16(val32 & 0xffff));
	अगर (idx < 0)
		वापस idx;
	/* KDETH.Offset */
	idx = ahg_header_set(ahg, idx, array_size, 15, 0, 16,
			     (__क्रमce u16)cpu_to_le16(req->koffset & 0xffff));
	अगर (idx < 0)
		वापस idx;
	idx = ahg_header_set(ahg, idx, array_size, 15, 16, 16,
			     (__क्रमce u16)cpu_to_le16(req->koffset >> 16));
	अगर (idx < 0)
		वापस idx;
	अगर (req_opcode(req->info.ctrl) == EXPECTED) अणु
		__le16 val;

		tidval = req->tids[req->tididx];

		/*
		 * If the offset माला_दो us at the end of the current TID,
		 * advance everything.
		 */
		अगर ((req->tiकरोffset) == (EXP_TID_GET(tidval, LEN) *
					 PAGE_SIZE)) अणु
			req->tiकरोffset = 0;
			/*
			 * Since we करोn't copy all the TIDs, all at once,
			 * we have to check again.
			 */
			अगर (++req->tididx > req->n_tids - 1 ||
			    !req->tids[req->tididx])
				वापस -EINVAL;
			tidval = req->tids[req->tididx];
		पूर्ण
		omfactor = ((EXP_TID_GET(tidval, LEN) *
				  PAGE_SIZE) >=
				 KDETH_OM_MAX_SIZE) ? KDETH_OM_LARGE_SHIFT :
				 KDETH_OM_SMALL_SHIFT;
		/* KDETH.OM and KDETH.OFFSET (TID) */
		idx = ahg_header_set(
				ahg, idx, array_size, 7, 0, 16,
				((!!(omfactor - KDETH_OM_SMALL_SHIFT)) << 15 |
				((req->tiकरोffset >> omfactor)
				& 0x7fff)));
		अगर (idx < 0)
			वापस idx;
		/* KDETH.TIDCtrl, KDETH.TID, KDETH.Intr, KDETH.SH */
		val = cpu_to_le16(((EXP_TID_GET(tidval, CTRL) & 0x3) << 10) |
				   (EXP_TID_GET(tidval, IDX) & 0x3ff));

		अगर (unlikely(tx->flags & TXREQ_FLAGS_REQ_DISABLE_SH)) अणु
			val |= cpu_to_le16((KDETH_GET(hdr->kdeth.ver_tid_offset,
						      INTR) <<
					    AHG_KDETH_INTR_SHIFT));
		पूर्ण अन्यथा अणु
			val |= KDETH_GET(hdr->kdeth.ver_tid_offset, SH) ?
			       cpu_to_le16(0x1 << AHG_KDETH_SH_SHIFT) :
			       cpu_to_le16((KDETH_GET(hdr->kdeth.ver_tid_offset,
						      INTR) <<
					     AHG_KDETH_INTR_SHIFT));
		पूर्ण

		idx = ahg_header_set(ahg, idx, array_size,
				     7, 16, 14, (__क्रमce u16)val);
		अगर (idx < 0)
			वापस idx;
	पूर्ण

	trace_hfi1_sdma_user_header_ahg(pq->dd, pq->ctxt, pq->subctxt,
					req->info.comp_idx, req->sde->this_idx,
					req->ahg_idx, ahg, idx, tidval);
	sdma_txinit_ahg(&tx->txreq,
			SDMA_TXREQ_F_USE_AHG,
			datalen, req->ahg_idx, idx,
			ahg, माप(req->hdr),
			user_sdma_txreq_cb);

	वापस idx;
पूर्ण

/**
 * user_sdma_txreq_cb() - SDMA tx request completion callback.
 * @txreq: valid sdma tx request
 * @status: success/failure of request
 *
 * Called when the SDMA progress state machine माला_लो notअगरication that
 * the SDMA descriptors क्रम this tx request have been processed by the
 * DMA engine. Called in पूर्णांकerrupt context.
 * Only करो work on completed sequences.
 */
अटल व्योम user_sdma_txreq_cb(काष्ठा sdma_txreq *txreq, पूर्णांक status)
अणु
	काष्ठा user_sdma_txreq *tx =
		container_of(txreq, काष्ठा user_sdma_txreq, txreq);
	काष्ठा user_sdma_request *req;
	काष्ठा hfi1_user_sdma_pkt_q *pq;
	काष्ठा hfi1_user_sdma_comp_q *cq;
	क्रमागत hfi1_sdma_comp_state state = COMPLETE;

	अगर (!tx->req)
		वापस;

	req = tx->req;
	pq = req->pq;
	cq = req->cq;

	अगर (status != SDMA_TXREQ_S_OK) अणु
		SDMA_DBG(req, "SDMA completion with error %d",
			 status);
		WRITE_ONCE(req->has_error, 1);
		state = ERROR;
	पूर्ण

	req->seqcomp = tx->seqnum;
	kmem_cache_मुक्त(pq->txreq_cache, tx);

	/* sequence isn't complete?  We are करोne */
	अगर (req->seqcomp != req->info.npkts - 1)
		वापस;

	user_sdma_मुक्त_request(req, false);
	set_comp_state(pq, cq, req->info.comp_idx, state, status);
	pq_update(pq);
पूर्ण

अटल अंतरभूत व्योम pq_update(काष्ठा hfi1_user_sdma_pkt_q *pq)
अणु
	अगर (atomic_dec_and_test(&pq->n_reqs))
		wake_up(&pq->रुको);
पूर्ण

अटल व्योम user_sdma_मुक्त_request(काष्ठा user_sdma_request *req, bool unpin)
अणु
	पूर्णांक i;

	अगर (!list_empty(&req->txps)) अणु
		काष्ठा sdma_txreq *t, *p;

		list_क्रम_each_entry_safe(t, p, &req->txps, list) अणु
			काष्ठा user_sdma_txreq *tx =
				container_of(t, काष्ठा user_sdma_txreq, txreq);
			list_del_init(&t->list);
			sdma_txclean(req->pq->dd, t);
			kmem_cache_मुक्त(req->pq->txreq_cache, tx);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < req->data_iovs; i++) अणु
		काष्ठा sdma_mmu_node *node = req->iovs[i].node;

		अगर (!node)
			जारी;

		req->iovs[i].node = शून्य;

		अगर (unpin)
			hfi1_mmu_rb_हटाओ(req->pq->handler,
					   &node->rb);
		अन्यथा
			atomic_dec(&node->refcount);
	पूर्ण

	kमुक्त(req->tids);
	clear_bit(req->info.comp_idx, req->pq->req_in_use);
पूर्ण

अटल अंतरभूत व्योम set_comp_state(काष्ठा hfi1_user_sdma_pkt_q *pq,
				  काष्ठा hfi1_user_sdma_comp_q *cq,
				  u16 idx, क्रमागत hfi1_sdma_comp_state state,
				  पूर्णांक ret)
अणु
	अगर (state == ERROR)
		cq->comps[idx].errcode = -ret;
	smp_wmb(); /* make sure errcode is visible first */
	cq->comps[idx].status = state;
	trace_hfi1_sdma_user_completion(pq->dd, pq->ctxt, pq->subctxt,
					idx, state, ret);
पूर्ण

अटल bool sdma_rb_filter(काष्ठा mmu_rb_node *node, अचिन्हित दीर्घ addr,
			   अचिन्हित दीर्घ len)
अणु
	वापस (bool)(node->addr == addr);
पूर्ण

अटल पूर्णांक sdma_rb_insert(व्योम *arg, काष्ठा mmu_rb_node *mnode)
अणु
	काष्ठा sdma_mmu_node *node =
		container_of(mnode, काष्ठा sdma_mmu_node, rb);

	atomic_inc(&node->refcount);
	वापस 0;
पूर्ण

/*
 * Return 1 to हटाओ the node from the rb tree and call the हटाओ op.
 *
 * Called with the rb tree lock held.
 */
अटल पूर्णांक sdma_rb_evict(व्योम *arg, काष्ठा mmu_rb_node *mnode,
			 व्योम *evict_arg, bool *stop)
अणु
	काष्ठा sdma_mmu_node *node =
		container_of(mnode, काष्ठा sdma_mmu_node, rb);
	काष्ठा evict_data *evict_data = evict_arg;

	/* is this node still being used? */
	अगर (atomic_पढ़ो(&node->refcount))
		वापस 0; /* keep this node */

	/* this node will be evicted, add its pages to our count */
	evict_data->cleared += node->npages;

	/* have enough pages been cleared? */
	अगर (evict_data->cleared >= evict_data->target)
		*stop = true;

	वापस 1; /* हटाओ this node */
पूर्ण

अटल व्योम sdma_rb_हटाओ(व्योम *arg, काष्ठा mmu_rb_node *mnode)
अणु
	काष्ठा sdma_mmu_node *node =
		container_of(mnode, काष्ठा sdma_mmu_node, rb);

	unpin_sdma_pages(node);
	kमुक्त(node);
पूर्ण

अटल पूर्णांक sdma_rb_invalidate(व्योम *arg, काष्ठा mmu_rb_node *mnode)
अणु
	काष्ठा sdma_mmu_node *node =
		container_of(mnode, काष्ठा sdma_mmu_node, rb);

	अगर (!atomic_पढ़ो(&node->refcount))
		वापस 1;
	वापस 0;
पूर्ण
