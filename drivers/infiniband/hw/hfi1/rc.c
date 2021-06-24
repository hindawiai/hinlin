<शैली गुरु>
/*
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

#समावेश <linux/पन.स>
#समावेश <rdma/rdma_vt.h>
#समावेश <rdma/rdmavt_qp.h>

#समावेश "hfi.h"
#समावेश "qp.h"
#समावेश "rc.h"
#समावेश "verbs_txreq.h"
#समावेश "trace.h"

काष्ठा rvt_ack_entry *find_prev_entry(काष्ठा rvt_qp *qp, u32 psn, u8 *prev,
				      u8 *prev_ack, bool *scheduled)
	__must_hold(&qp->s_lock)
अणु
	काष्ठा rvt_ack_entry *e = शून्य;
	u8 i, p;
	bool s = true;

	क्रम (i = qp->r_head_ack_queue; ; i = p) अणु
		अगर (i == qp->s_tail_ack_queue)
			s = false;
		अगर (i)
			p = i - 1;
		अन्यथा
			p = rvt_size_atomic(ib_to_rvt(qp->ibqp.device));
		अगर (p == qp->r_head_ack_queue) अणु
			e = शून्य;
			अवरोध;
		पूर्ण
		e = &qp->s_ack_queue[p];
		अगर (!e->opcode) अणु
			e = शून्य;
			अवरोध;
		पूर्ण
		अगर (cmp_psn(psn, e->psn) >= 0) अणु
			अगर (p == qp->s_tail_ack_queue &&
			    cmp_psn(psn, e->lpsn) <= 0)
				s = false;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (prev)
		*prev = p;
	अगर (prev_ack)
		*prev_ack = i;
	अगर (scheduled)
		*scheduled = s;
	वापस e;
पूर्ण

/**
 * make_rc_ack - स्थिरruct a response packet (ACK, NAK, or RDMA पढ़ो)
 * @dev: the device क्रम this QP
 * @qp: a poपूर्णांकer to the QP
 * @ohdr: a poपूर्णांकer to the IB header being स्थिरructed
 * @ps: the xmit packet state
 *
 * Return 1 अगर स्थिरructed; otherwise, वापस 0.
 * Note that we are in the responder's side of the QP context.
 * Note the QP s_lock must be held.
 */
अटल पूर्णांक make_rc_ack(काष्ठा hfi1_ibdev *dev, काष्ठा rvt_qp *qp,
		       काष्ठा ib_other_headers *ohdr,
		       काष्ठा hfi1_pkt_state *ps)
अणु
	काष्ठा rvt_ack_entry *e;
	u32 hwords, hdrlen;
	u32 len = 0;
	u32 bth0 = 0, bth2 = 0;
	u32 bth1 = qp->remote_qpn | (HFI1_CAP_IS_KSET(OPFN) << IB_BTHE_E_SHIFT);
	पूर्णांक middle = 0;
	u32 pmtu = qp->pmtu;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	bool last_pkt;
	u32 delta;
	u8 next = qp->s_tail_ack_queue;
	काष्ठा tid_rdma_request *req;

	trace_hfi1_rsp_make_rc_ack(qp, 0);
	lockdep_निश्चित_held(&qp->s_lock);
	/* Don't send an ACK if we aren't supposed to. */
	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK))
		जाओ bail;

	अगर (qpriv->hdr_type == HFI1_PKT_TYPE_9B)
		/* header size in 32-bit words LRH+BTH = (8+12)/4. */
		hwords = 5;
	अन्यथा
		/* header size in 32-bit words 16B LRH+BTH = (16+12)/4. */
		hwords = 7;

	चयन (qp->s_ack_state) अणु
	हाल OP(RDMA_READ_RESPONSE_LAST):
	हाल OP(RDMA_READ_RESPONSE_ONLY):
		e = &qp->s_ack_queue[qp->s_tail_ack_queue];
		release_rdma_sge_mr(e);
		fallthrough;
	हाल OP(ATOMIC_ACKNOWLEDGE):
		/*
		 * We can increment the tail poपूर्णांकer now that the last
		 * response has been sent instead of only being
		 * स्थिरructed.
		 */
		अगर (++next > rvt_size_atomic(&dev->rdi))
			next = 0;
		/*
		 * Only advance the s_acked_ack_queue poपूर्णांकer अगर there
		 * have been no TID RDMA requests.
		 */
		e = &qp->s_ack_queue[qp->s_tail_ack_queue];
		अगर (e->opcode != TID_OP(WRITE_REQ) &&
		    qp->s_acked_ack_queue == qp->s_tail_ack_queue)
			qp->s_acked_ack_queue = next;
		qp->s_tail_ack_queue = next;
		trace_hfi1_rsp_make_rc_ack(qp, e->psn);
		fallthrough;
	हाल OP(SEND_ONLY):
	हाल OP(ACKNOWLEDGE):
		/* Check क्रम no next entry in the queue. */
		अगर (qp->r_head_ack_queue == qp->s_tail_ack_queue) अणु
			अगर (qp->s_flags & RVT_S_ACK_PENDING)
				जाओ normal;
			जाओ bail;
		पूर्ण

		e = &qp->s_ack_queue[qp->s_tail_ack_queue];
		/* Check क्रम tid ग_लिखो fence */
		अगर ((qpriv->s_flags & HFI1_R_TID_WAIT_INTERLCK) ||
		    hfi1_tid_rdma_ack_पूर्णांकerlock(qp, e)) अणु
			ioरुको_set_flag(&qpriv->s_ioरुको, IOWAIT_PENDING_IB);
			जाओ bail;
		पूर्ण
		अगर (e->opcode == OP(RDMA_READ_REQUEST)) अणु
			/*
			 * If a RDMA पढ़ो response is being resent and
			 * we haven't seen the duplicate request yet,
			 * then stop sending the reमुख्यing responses the
			 * responder has seen until the requester re-sends it.
			 */
			len = e->rdma_sge.sge_length;
			अगर (len && !e->rdma_sge.mr) अणु
				अगर (qp->s_acked_ack_queue ==
				    qp->s_tail_ack_queue)
					qp->s_acked_ack_queue =
						qp->r_head_ack_queue;
				qp->s_tail_ack_queue = qp->r_head_ack_queue;
				जाओ bail;
			पूर्ण
			/* Copy SGE state in हाल we need to resend */
			ps->s_txreq->mr = e->rdma_sge.mr;
			अगर (ps->s_txreq->mr)
				rvt_get_mr(ps->s_txreq->mr);
			qp->s_ack_rdma_sge.sge = e->rdma_sge;
			qp->s_ack_rdma_sge.num_sge = 1;
			ps->s_txreq->ss = &qp->s_ack_rdma_sge;
			अगर (len > pmtu) अणु
				len = pmtu;
				qp->s_ack_state = OP(RDMA_READ_RESPONSE_FIRST);
			पूर्ण अन्यथा अणु
				qp->s_ack_state = OP(RDMA_READ_RESPONSE_ONLY);
				e->sent = 1;
			पूर्ण
			ohdr->u.aeth = rvt_compute_aeth(qp);
			hwords++;
			qp->s_ack_rdma_psn = e->psn;
			bth2 = mask_psn(qp->s_ack_rdma_psn++);
		पूर्ण अन्यथा अगर (e->opcode == TID_OP(WRITE_REQ)) अणु
			/*
			 * If a TID RDMA WRITE RESP is being resent, we have to
			 * रुको क्रम the actual request. All requests that are to
			 * be resent will have their state set to
			 * TID_REQUEST_RESEND. When the new request arrives, the
			 * state will be changed to TID_REQUEST_RESEND_ACTIVE.
			 */
			req = ack_to_tid_req(e);
			अगर (req->state == TID_REQUEST_RESEND ||
			    req->state == TID_REQUEST_INIT_RESEND)
				जाओ bail;
			qp->s_ack_state = TID_OP(WRITE_RESP);
			qp->s_ack_rdma_psn = mask_psn(e->psn + req->cur_seg);
			जाओ ग_लिखो_resp;
		पूर्ण अन्यथा अगर (e->opcode == TID_OP(READ_REQ)) अणु
			/*
			 * If a TID RDMA पढ़ो response is being resent and
			 * we haven't seen the duplicate request yet,
			 * then stop sending the reमुख्यing responses the
			 * responder has seen until the requester re-sends it.
			 */
			len = e->rdma_sge.sge_length;
			अगर (len && !e->rdma_sge.mr) अणु
				अगर (qp->s_acked_ack_queue ==
				    qp->s_tail_ack_queue)
					qp->s_acked_ack_queue =
						qp->r_head_ack_queue;
				qp->s_tail_ack_queue = qp->r_head_ack_queue;
				जाओ bail;
			पूर्ण
			/* Copy SGE state in हाल we need to resend */
			ps->s_txreq->mr = e->rdma_sge.mr;
			अगर (ps->s_txreq->mr)
				rvt_get_mr(ps->s_txreq->mr);
			qp->s_ack_rdma_sge.sge = e->rdma_sge;
			qp->s_ack_rdma_sge.num_sge = 1;
			qp->s_ack_state = TID_OP(READ_RESP);
			जाओ पढ़ो_resp;
		पूर्ण अन्यथा अणु
			/* COMPARE_SWAP or FETCH_ADD */
			ps->s_txreq->ss = शून्य;
			len = 0;
			qp->s_ack_state = OP(ATOMIC_ACKNOWLEDGE);
			ohdr->u.at.aeth = rvt_compute_aeth(qp);
			ib_u64_put(e->atomic_data, &ohdr->u.at.atomic_ack_eth);
			hwords += माप(ohdr->u.at) / माप(u32);
			bth2 = mask_psn(e->psn);
			e->sent = 1;
		पूर्ण
		trace_hfi1_tid_ग_लिखो_rsp_make_rc_ack(qp);
		bth0 = qp->s_ack_state << 24;
		अवरोध;

	हाल OP(RDMA_READ_RESPONSE_FIRST):
		qp->s_ack_state = OP(RDMA_READ_RESPONSE_MIDDLE);
		fallthrough;
	हाल OP(RDMA_READ_RESPONSE_MIDDLE):
		ps->s_txreq->ss = &qp->s_ack_rdma_sge;
		ps->s_txreq->mr = qp->s_ack_rdma_sge.sge.mr;
		अगर (ps->s_txreq->mr)
			rvt_get_mr(ps->s_txreq->mr);
		len = qp->s_ack_rdma_sge.sge.sge_length;
		अगर (len > pmtu) अणु
			len = pmtu;
			middle = HFI1_CAP_IS_KSET(SDMA_AHG);
		पूर्ण अन्यथा अणु
			ohdr->u.aeth = rvt_compute_aeth(qp);
			hwords++;
			qp->s_ack_state = OP(RDMA_READ_RESPONSE_LAST);
			e = &qp->s_ack_queue[qp->s_tail_ack_queue];
			e->sent = 1;
		पूर्ण
		bth0 = qp->s_ack_state << 24;
		bth2 = mask_psn(qp->s_ack_rdma_psn++);
		अवरोध;

	हाल TID_OP(WRITE_RESP):
ग_लिखो_resp:
		/*
		 * 1. Check अगर RVT_S_ACK_PENDING is set. If yes,
		 *    जाओ normal.
		 * 2. Attempt to allocate TID resources.
		 * 3. Remove RVT_S_RESP_PENDING flags from s_flags
		 * 4. If resources not available:
		 *    4.1 Set RVT_S_WAIT_TID_SPACE
		 *    4.2 Queue QP on RCD TID queue
		 *    4.3 Put QP on ioरुको list.
		 *    4.4 Build IB RNR NAK with appropriate समयout value
		 *    4.5 Return indication progress made.
		 * 5. If resources are available:
		 *    5.1 Program HW flow CSRs
		 *    5.2 Build TID RDMA WRITE RESP packet
		 *    5.3 If more resources needed, करो 2.1 - 2.3.
		 *    5.4 Wake up next QP on RCD TID queue.
		 *    5.5 Return indication progress made.
		 */

		e = &qp->s_ack_queue[qp->s_tail_ack_queue];
		req = ack_to_tid_req(e);

		/*
		 * Send scheduled RNR NAK's. RNR NAK's need to be sent at
		 * segment boundaries, not at request boundaries. Don't change
		 * s_ack_state because we are still in the middle of a request
		 */
		अगर (qpriv->rnr_nak_state == TID_RNR_NAK_SEND &&
		    qp->s_tail_ack_queue == qpriv->r_tid_alloc &&
		    req->cur_seg == req->alloc_seg) अणु
			qpriv->rnr_nak_state = TID_RNR_NAK_SENT;
			जाओ normal_no_state;
		पूर्ण

		bth2 = mask_psn(qp->s_ack_rdma_psn);
		hdrlen = hfi1_build_tid_rdma_ग_लिखो_resp(qp, e, ohdr, &bth1,
							bth2, &len,
							&ps->s_txreq->ss);
		अगर (!hdrlen)
			वापस 0;

		hwords += hdrlen;
		bth0 = qp->s_ack_state << 24;
		qp->s_ack_rdma_psn++;
		trace_hfi1_tid_req_make_rc_ack_ग_लिखो(qp, 0, e->opcode, e->psn,
						     e->lpsn, req);
		अगर (req->cur_seg != req->total_segs)
			अवरोध;

		e->sent = 1;
		/* Do not मुक्त e->rdma_sge until all data are received */
		qp->s_ack_state = OP(ATOMIC_ACKNOWLEDGE);
		अवरोध;

	हाल TID_OP(READ_RESP):
पढ़ो_resp:
		e = &qp->s_ack_queue[qp->s_tail_ack_queue];
		ps->s_txreq->ss = &qp->s_ack_rdma_sge;
		delta = hfi1_build_tid_rdma_पढ़ो_resp(qp, e, ohdr, &bth0,
						      &bth1, &bth2, &len,
						      &last_pkt);
		अगर (delta == 0)
			जाओ error_qp;
		hwords += delta;
		अगर (last_pkt) अणु
			e->sent = 1;
			/*
			 * Increment qp->s_tail_ack_queue through s_ack_state
			 * transition.
			 */
			qp->s_ack_state = OP(RDMA_READ_RESPONSE_LAST);
		पूर्ण
		अवरोध;
	हाल TID_OP(READ_REQ):
		जाओ bail;

	शेष:
normal:
		/*
		 * Send a regular ACK.
		 * Set the s_ack_state so we रुको until after sending
		 * the ACK beक्रमe setting s_ack_state to ACKNOWLEDGE
		 * (see above).
		 */
		qp->s_ack_state = OP(SEND_ONLY);
normal_no_state:
		अगर (qp->s_nak_state)
			ohdr->u.aeth =
				cpu_to_be32((qp->r_msn & IB_MSN_MASK) |
					    (qp->s_nak_state <<
					     IB_AETH_CREDIT_SHIFT));
		अन्यथा
			ohdr->u.aeth = rvt_compute_aeth(qp);
		hwords++;
		len = 0;
		bth0 = OP(ACKNOWLEDGE) << 24;
		bth2 = mask_psn(qp->s_ack_psn);
		qp->s_flags &= ~RVT_S_ACK_PENDING;
		ps->s_txreq->txreq.flags |= SDMA_TXREQ_F_VIP;
		ps->s_txreq->ss = शून्य;
	पूर्ण
	qp->s_rdma_ack_cnt++;
	ps->s_txreq->sde = qpriv->s_sde;
	ps->s_txreq->s_cur_size = len;
	ps->s_txreq->hdr_dwords = hwords;
	hfi1_make_ruc_header(qp, ohdr, bth0, bth1, bth2, middle, ps);
	वापस 1;
error_qp:
	spin_unlock_irqrestore(&qp->s_lock, ps->flags);
	spin_lock_irqsave(&qp->r_lock, ps->flags);
	spin_lock(&qp->s_lock);
	rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);
	spin_unlock(&qp->s_lock);
	spin_unlock_irqrestore(&qp->r_lock, ps->flags);
	spin_lock_irqsave(&qp->s_lock, ps->flags);
bail:
	qp->s_ack_state = OP(ACKNOWLEDGE);
	/*
	 * Ensure s_rdma_ack_cnt changes are committed prior to resetting
	 * RVT_S_RESP_PENDING
	 */
	smp_wmb();
	qp->s_flags &= ~(RVT_S_RESP_PENDING
				| RVT_S_ACK_PENDING
				| HFI1_S_AHG_VALID);
	वापस 0;
पूर्ण

/**
 * hfi1_make_rc_req - स्थिरruct a request packet (SEND, RDMA r/w, ATOMIC)
 * @qp: a poपूर्णांकer to the QP
 * @ps: the current packet state
 *
 * Assumes s_lock is held.
 *
 * Return 1 अगर स्थिरructed; otherwise, वापस 0.
 */
पूर्णांक hfi1_make_rc_req(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा hfi1_ibdev *dev = to_idev(qp->ibqp.device);
	काष्ठा ib_other_headers *ohdr;
	काष्ठा rvt_sge_state *ss = शून्य;
	काष्ठा rvt_swqe *wqe;
	काष्ठा hfi1_swqe_priv *wpriv;
	काष्ठा tid_rdma_request *req = शून्य;
	/* header size in 32-bit words LRH+BTH = (8+12)/4. */
	u32 hwords = 5;
	u32 len = 0;
	u32 bth0 = 0, bth2 = 0;
	u32 bth1 = qp->remote_qpn | (HFI1_CAP_IS_KSET(OPFN) << IB_BTHE_E_SHIFT);
	u32 pmtu = qp->pmtu;
	अक्षर newreq;
	पूर्णांक middle = 0;
	पूर्णांक delta;
	काष्ठा tid_rdma_flow *flow = शून्य;
	काष्ठा tid_rdma_params *remote;

	trace_hfi1_sender_make_rc_req(qp);
	lockdep_निश्चित_held(&qp->s_lock);
	ps->s_txreq = get_txreq(ps->dev, qp);
	अगर (!ps->s_txreq)
		जाओ bail_no_tx;

	अगर (priv->hdr_type == HFI1_PKT_TYPE_9B) अणु
		/* header size in 32-bit words LRH+BTH = (8+12)/4. */
		hwords = 5;
		अगर (rdma_ah_get_ah_flags(&qp->remote_ah_attr) & IB_AH_GRH)
			ohdr = &ps->s_txreq->phdr.hdr.ibh.u.l.oth;
		अन्यथा
			ohdr = &ps->s_txreq->phdr.hdr.ibh.u.oth;
	पूर्ण अन्यथा अणु
		/* header size in 32-bit words 16B LRH+BTH = (16+12)/4. */
		hwords = 7;
		अगर ((rdma_ah_get_ah_flags(&qp->remote_ah_attr) & IB_AH_GRH) &&
		    (hfi1_check_mcast(rdma_ah_get_dlid(&qp->remote_ah_attr))))
			ohdr = &ps->s_txreq->phdr.hdr.opah.u.l.oth;
		अन्यथा
			ohdr = &ps->s_txreq->phdr.hdr.opah.u.oth;
	पूर्ण

	/* Sending responses has higher priority over sending requests. */
	अगर ((qp->s_flags & RVT_S_RESP_PENDING) &&
	    make_rc_ack(dev, qp, ohdr, ps))
		वापस 1;

	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_SEND_OK)) अणु
		अगर (!(ib_rvt_state_ops[qp->state] & RVT_FLUSH_SEND))
			जाओ bail;
		/* We are in the error state, flush the work request. */
		अगर (qp->s_last == READ_ONCE(qp->s_head))
			जाओ bail;
		/* If DMAs are in progress, we can't flush immediately. */
		अगर (ioरुको_sdma_pending(&priv->s_ioरुको)) अणु
			qp->s_flags |= RVT_S_WAIT_DMA;
			जाओ bail;
		पूर्ण
		clear_ahg(qp);
		wqe = rvt_get_swqe_ptr(qp, qp->s_last);
		hfi1_trdma_send_complete(qp, wqe, qp->s_last != qp->s_acked ?
					 IB_WC_SUCCESS : IB_WC_WR_FLUSH_ERR);
		/* will get called again */
		जाओ करोne_मुक्त_tx;
	पूर्ण

	अगर (qp->s_flags & (RVT_S_WAIT_RNR | RVT_S_WAIT_ACK | HFI1_S_WAIT_HALT))
		जाओ bail;

	अगर (cmp_psn(qp->s_psn, qp->s_sending_hpsn) <= 0) अणु
		अगर (cmp_psn(qp->s_sending_psn, qp->s_sending_hpsn) <= 0) अणु
			qp->s_flags |= RVT_S_WAIT_PSN;
			जाओ bail;
		पूर्ण
		qp->s_sending_psn = qp->s_psn;
		qp->s_sending_hpsn = qp->s_psn - 1;
	पूर्ण

	/* Send a request. */
	wqe = rvt_get_swqe_ptr(qp, qp->s_cur);
check_s_state:
	चयन (qp->s_state) अणु
	शेष:
		अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_NEXT_SEND_OK))
			जाओ bail;
		/*
		 * Resend an old request or start a new one.
		 *
		 * We keep track of the current SWQE so that
		 * we करोn't reset the "furthest progress" state
		 * अगर we need to back up.
		 */
		newreq = 0;
		अगर (qp->s_cur == qp->s_tail) अणु
			/* Check अगर send work queue is empty. */
			अगर (qp->s_tail == READ_ONCE(qp->s_head)) अणु
				clear_ahg(qp);
				जाओ bail;
			पूर्ण
			/*
			 * If a fence is requested, रुको क्रम previous
			 * RDMA पढ़ो and atomic operations to finish.
			 * However, there is no need to guard against
			 * TID RDMA READ after TID RDMA READ.
			 */
			अगर ((wqe->wr.send_flags & IB_SEND_FENCE) &&
			    qp->s_num_rd_atomic &&
			    (wqe->wr.opcode != IB_WR_TID_RDMA_READ ||
			     priv->pending_tid_r_segs < qp->s_num_rd_atomic)) अणु
				qp->s_flags |= RVT_S_WAIT_FENCE;
				जाओ bail;
			पूर्ण
			/*
			 * Local operations are processed immediately
			 * after all prior requests have completed
			 */
			अगर (wqe->wr.opcode == IB_WR_REG_MR ||
			    wqe->wr.opcode == IB_WR_LOCAL_INV) अणु
				पूर्णांक local_ops = 0;
				पूर्णांक err = 0;

				अगर (qp->s_last != qp->s_cur)
					जाओ bail;
				अगर (++qp->s_cur == qp->s_size)
					qp->s_cur = 0;
				अगर (++qp->s_tail == qp->s_size)
					qp->s_tail = 0;
				अगर (!(wqe->wr.send_flags &
				      RVT_SEND_COMPLETION_ONLY)) अणु
					err = rvt_invalidate_rkey(
						qp,
						wqe->wr.ex.invalidate_rkey);
					local_ops = 1;
				पूर्ण
				rvt_send_complete(qp, wqe,
						  err ? IB_WC_LOC_PROT_ERR
						      : IB_WC_SUCCESS);
				अगर (local_ops)
					atomic_dec(&qp->local_ops_pending);
				जाओ करोne_मुक्त_tx;
			पूर्ण

			newreq = 1;
			qp->s_psn = wqe->psn;
		पूर्ण
		/*
		 * Note that we have to be careful not to modअगरy the
		 * original work request since we may need to resend
		 * it.
		 */
		len = wqe->length;
		ss = &qp->s_sge;
		bth2 = mask_psn(qp->s_psn);

		/*
		 * Interlock between various IB requests and TID RDMA
		 * अगर necessary.
		 */
		अगर ((priv->s_flags & HFI1_S_TID_WAIT_INTERLCK) ||
		    hfi1_tid_rdma_wqe_पूर्णांकerlock(qp, wqe))
			जाओ bail;

		चयन (wqe->wr.opcode) अणु
		हाल IB_WR_SEND:
		हाल IB_WR_SEND_WITH_IMM:
		हाल IB_WR_SEND_WITH_INV:
			/* If no credit, वापस. */
			अगर (!rvt_rc_credit_avail(qp, wqe))
				जाओ bail;
			अगर (len > pmtu) अणु
				qp->s_state = OP(SEND_FIRST);
				len = pmtu;
				अवरोध;
			पूर्ण
			अगर (wqe->wr.opcode == IB_WR_SEND) अणु
				qp->s_state = OP(SEND_ONLY);
			पूर्ण अन्यथा अगर (wqe->wr.opcode == IB_WR_SEND_WITH_IMM) अणु
				qp->s_state = OP(SEND_ONLY_WITH_IMMEDIATE);
				/* Immediate data comes after the BTH */
				ohdr->u.imm_data = wqe->wr.ex.imm_data;
				hwords += 1;
			पूर्ण अन्यथा अणु
				qp->s_state = OP(SEND_ONLY_WITH_INVALIDATE);
				/* Invalidate rkey comes after the BTH */
				ohdr->u.ieth = cpu_to_be32(
						wqe->wr.ex.invalidate_rkey);
				hwords += 1;
			पूर्ण
			अगर (wqe->wr.send_flags & IB_SEND_SOLICITED)
				bth0 |= IB_BTH_SOLICITED;
			bth2 |= IB_BTH_REQ_ACK;
			अगर (++qp->s_cur == qp->s_size)
				qp->s_cur = 0;
			अवरोध;

		हाल IB_WR_RDMA_WRITE:
			अगर (newreq && !(qp->s_flags & RVT_S_UNLIMITED_CREDIT))
				qp->s_lsn++;
			जाओ no_flow_control;
		हाल IB_WR_RDMA_WRITE_WITH_IMM:
			/* If no credit, वापस. */
			अगर (!rvt_rc_credit_avail(qp, wqe))
				जाओ bail;
no_flow_control:
			put_ib_reth_vaddr(
				wqe->rdma_wr.remote_addr,
				&ohdr->u.rc.reth);
			ohdr->u.rc.reth.rkey =
				cpu_to_be32(wqe->rdma_wr.rkey);
			ohdr->u.rc.reth.length = cpu_to_be32(len);
			hwords += माप(काष्ठा ib_reth) / माप(u32);
			अगर (len > pmtu) अणु
				qp->s_state = OP(RDMA_WRITE_FIRST);
				len = pmtu;
				अवरोध;
			पूर्ण
			अगर (wqe->wr.opcode == IB_WR_RDMA_WRITE) अणु
				qp->s_state = OP(RDMA_WRITE_ONLY);
			पूर्ण अन्यथा अणु
				qp->s_state =
					OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE);
				/* Immediate data comes after RETH */
				ohdr->u.rc.imm_data = wqe->wr.ex.imm_data;
				hwords += 1;
				अगर (wqe->wr.send_flags & IB_SEND_SOLICITED)
					bth0 |= IB_BTH_SOLICITED;
			पूर्ण
			bth2 |= IB_BTH_REQ_ACK;
			अगर (++qp->s_cur == qp->s_size)
				qp->s_cur = 0;
			अवरोध;

		हाल IB_WR_TID_RDMA_WRITE:
			अगर (newreq) अणु
				/*
				 * Limit the number of TID RDMA WRITE requests.
				 */
				अगर (atomic_पढ़ो(&priv->n_tid_requests) >=
				    HFI1_TID_RDMA_WRITE_CNT)
					जाओ bail;

				अगर (!(qp->s_flags & RVT_S_UNLIMITED_CREDIT))
					qp->s_lsn++;
			पूर्ण

			hwords += hfi1_build_tid_rdma_ग_लिखो_req(qp, wqe, ohdr,
								&bth1, &bth2,
								&len);
			ss = शून्य;
			अगर (priv->s_tid_cur == HFI1_QP_WQE_INVALID) अणु
				priv->s_tid_cur = qp->s_cur;
				अगर (priv->s_tid_tail == HFI1_QP_WQE_INVALID) अणु
					priv->s_tid_tail = qp->s_cur;
					priv->s_state = TID_OP(WRITE_RESP);
				पूर्ण
			पूर्ण अन्यथा अगर (priv->s_tid_cur == priv->s_tid_head) अणु
				काष्ठा rvt_swqe *__w;
				काष्ठा tid_rdma_request *__r;

				__w = rvt_get_swqe_ptr(qp, priv->s_tid_cur);
				__r = wqe_to_tid_req(__w);

				/*
				 * The s_tid_cur poपूर्णांकer is advanced to s_cur अगर
				 * any of the following conditions about the WQE
				 * to which s_ti_cur currently poपूर्णांकs to are
				 * satisfied:
				 *   1. The request is not a TID RDMA WRITE
				 *      request,
				 *   2. The request is in the INACTIVE or
				 *      COMPLETE states (TID RDMA READ requests
				 *      stay at INACTIVE and TID RDMA WRITE
				 *      transition to COMPLETE when करोne),
				 *   3. The request is in the ACTIVE or SYNC
				 *      state and the number of completed
				 *      segments is equal to the total segment
				 *      count.
				 *      (If ACTIVE, the request is रुकोing क्रम
				 *       ACKs. If SYNC, the request has not
				 *       received any responses because it's
				 *       रुकोing on a sync poपूर्णांक.)
				 */
				अगर (__w->wr.opcode != IB_WR_TID_RDMA_WRITE ||
				    __r->state == TID_REQUEST_INACTIVE ||
				    __r->state == TID_REQUEST_COMPLETE ||
				    ((__r->state == TID_REQUEST_ACTIVE ||
				      __r->state == TID_REQUEST_SYNC) &&
				     __r->comp_seg == __r->total_segs)) अणु
					अगर (priv->s_tid_tail ==
					    priv->s_tid_cur &&
					    priv->s_state ==
					    TID_OP(WRITE_DATA_LAST)) अणु
						priv->s_tid_tail = qp->s_cur;
						priv->s_state =
							TID_OP(WRITE_RESP);
					पूर्ण
					priv->s_tid_cur = qp->s_cur;
				पूर्ण
				/*
				 * A corner हाल: when the last TID RDMA WRITE
				 * request was completed, s_tid_head,
				 * s_tid_cur, and s_tid_tail all poपूर्णांक to the
				 * same location. Other requests are posted and
				 * s_cur wraps around to the same location,
				 * where a new TID RDMA WRITE is posted. In
				 * this हाल, none of the indices need to be
				 * updated. However, the priv->s_state should.
				 */
				अगर (priv->s_tid_tail == qp->s_cur &&
				    priv->s_state == TID_OP(WRITE_DATA_LAST))
					priv->s_state = TID_OP(WRITE_RESP);
			पूर्ण
			req = wqe_to_tid_req(wqe);
			अगर (newreq) अणु
				priv->s_tid_head = qp->s_cur;
				priv->pending_tid_w_resp += req->total_segs;
				atomic_inc(&priv->n_tid_requests);
				atomic_dec(&priv->n_requests);
			पूर्ण अन्यथा अणु
				req->state = TID_REQUEST_RESEND;
				req->comp_seg = delta_psn(bth2, wqe->psn);
				/*
				 * Pull back any segments since we are going
				 * to re-receive them.
				 */
				req->setup_head = req->clear_tail;
				priv->pending_tid_w_resp +=
					delta_psn(wqe->lpsn, bth2) + 1;
			पूर्ण

			trace_hfi1_tid_ग_लिखो_sender_make_req(qp, newreq);
			trace_hfi1_tid_req_make_req_ग_लिखो(qp, newreq,
							  wqe->wr.opcode,
							  wqe->psn, wqe->lpsn,
							  req);
			अगर (++qp->s_cur == qp->s_size)
				qp->s_cur = 0;
			अवरोध;

		हाल IB_WR_RDMA_READ:
			/*
			 * Don't allow more operations to be started
			 * than the QP limits allow.
			 */
			अगर (qp->s_num_rd_atomic >=
			    qp->s_max_rd_atomic) अणु
				qp->s_flags |= RVT_S_WAIT_RDMAR;
				जाओ bail;
			पूर्ण
			qp->s_num_rd_atomic++;
			अगर (newreq && !(qp->s_flags & RVT_S_UNLIMITED_CREDIT))
				qp->s_lsn++;
			put_ib_reth_vaddr(
				wqe->rdma_wr.remote_addr,
				&ohdr->u.rc.reth);
			ohdr->u.rc.reth.rkey =
				cpu_to_be32(wqe->rdma_wr.rkey);
			ohdr->u.rc.reth.length = cpu_to_be32(len);
			qp->s_state = OP(RDMA_READ_REQUEST);
			hwords += माप(ohdr->u.rc.reth) / माप(u32);
			ss = शून्य;
			len = 0;
			bth2 |= IB_BTH_REQ_ACK;
			अगर (++qp->s_cur == qp->s_size)
				qp->s_cur = 0;
			अवरोध;

		हाल IB_WR_TID_RDMA_READ:
			trace_hfi1_tid_पढ़ो_sender_make_req(qp, newreq);
			wpriv = wqe->priv;
			req = wqe_to_tid_req(wqe);
			trace_hfi1_tid_req_make_req_पढ़ो(qp, newreq,
							 wqe->wr.opcode,
							 wqe->psn, wqe->lpsn,
							 req);
			delta = cmp_psn(qp->s_psn, wqe->psn);

			/*
			 * Don't allow more operations to be started
			 * than the QP limits allow. We could get here under
			 * three conditions; (1) It's a new request; (2) We are
			 * sending the second or later segment of a request,
			 * but the qp->s_state is set to OP(RDMA_READ_REQUEST)
			 * when the last segment of a previous request is
			 * received just beक्रमe this; (3) We are re-sending a
			 * request.
			 */
			अगर (qp->s_num_rd_atomic >= qp->s_max_rd_atomic) अणु
				qp->s_flags |= RVT_S_WAIT_RDMAR;
				जाओ bail;
			पूर्ण
			अगर (newreq) अणु
				काष्ठा tid_rdma_flow *flow =
					&req->flows[req->setup_head];

				/*
				 * Set up s_sge as it is needed क्रम TID
				 * allocation. However, अगर the pages have been
				 * walked and mapped, skip it. An earlier try
				 * has failed to allocate the TID entries.
				 */
				अगर (!flow->npagesets) अणु
					qp->s_sge.sge = wqe->sg_list[0];
					qp->s_sge.sg_list = wqe->sg_list + 1;
					qp->s_sge.num_sge = wqe->wr.num_sge;
					qp->s_sge.total_len = wqe->length;
					qp->s_len = wqe->length;
					req->isge = 0;
					req->clear_tail = req->setup_head;
					req->flow_idx = req->setup_head;
					req->state = TID_REQUEST_ACTIVE;
				पूर्ण
			पूर्ण अन्यथा अगर (delta == 0) अणु
				/* Re-send a request */
				req->cur_seg = 0;
				req->comp_seg = 0;
				req->ack_pending = 0;
				req->flow_idx = req->clear_tail;
				req->state = TID_REQUEST_RESEND;
			पूर्ण
			req->s_next_psn = qp->s_psn;
			/* Read one segment at a समय */
			len = min_t(u32, req->seg_len,
				    wqe->length - req->seg_len * req->cur_seg);
			delta = hfi1_build_tid_rdma_पढ़ो_req(qp, wqe, ohdr,
							     &bth1, &bth2,
							     &len);
			अगर (delta <= 0) अणु
				/* Wait क्रम TID space */
				जाओ bail;
			पूर्ण
			अगर (newreq && !(qp->s_flags & RVT_S_UNLIMITED_CREDIT))
				qp->s_lsn++;
			hwords += delta;
			ss = &wpriv->ss;
			/* Check अगर this is the last segment */
			अगर (req->cur_seg >= req->total_segs &&
			    ++qp->s_cur == qp->s_size)
				qp->s_cur = 0;
			अवरोध;

		हाल IB_WR_ATOMIC_CMP_AND_SWP:
		हाल IB_WR_ATOMIC_FETCH_AND_ADD:
			/*
			 * Don't allow more operations to be started
			 * than the QP limits allow.
			 */
			अगर (qp->s_num_rd_atomic >=
			    qp->s_max_rd_atomic) अणु
				qp->s_flags |= RVT_S_WAIT_RDMAR;
				जाओ bail;
			पूर्ण
			qp->s_num_rd_atomic++;
			fallthrough;
		हाल IB_WR_OPFN:
			अगर (newreq && !(qp->s_flags & RVT_S_UNLIMITED_CREDIT))
				qp->s_lsn++;
			अगर (wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
			    wqe->wr.opcode == IB_WR_OPFN) अणु
				qp->s_state = OP(COMPARE_SWAP);
				put_ib_ateth_swap(wqe->atomic_wr.swap,
						  &ohdr->u.atomic_eth);
				put_ib_ateth_compare(wqe->atomic_wr.compare_add,
						     &ohdr->u.atomic_eth);
			पूर्ण अन्यथा अणु
				qp->s_state = OP(FETCH_ADD);
				put_ib_ateth_swap(wqe->atomic_wr.compare_add,
						  &ohdr->u.atomic_eth);
				put_ib_ateth_compare(0, &ohdr->u.atomic_eth);
			पूर्ण
			put_ib_ateth_vaddr(wqe->atomic_wr.remote_addr,
					   &ohdr->u.atomic_eth);
			ohdr->u.atomic_eth.rkey = cpu_to_be32(
				wqe->atomic_wr.rkey);
			hwords += माप(काष्ठा ib_atomic_eth) / माप(u32);
			ss = शून्य;
			len = 0;
			bth2 |= IB_BTH_REQ_ACK;
			अगर (++qp->s_cur == qp->s_size)
				qp->s_cur = 0;
			अवरोध;

		शेष:
			जाओ bail;
		पूर्ण
		अगर (wqe->wr.opcode != IB_WR_TID_RDMA_READ) अणु
			qp->s_sge.sge = wqe->sg_list[0];
			qp->s_sge.sg_list = wqe->sg_list + 1;
			qp->s_sge.num_sge = wqe->wr.num_sge;
			qp->s_sge.total_len = wqe->length;
			qp->s_len = wqe->length;
		पूर्ण
		अगर (newreq) अणु
			qp->s_tail++;
			अगर (qp->s_tail >= qp->s_size)
				qp->s_tail = 0;
		पूर्ण
		अगर (wqe->wr.opcode == IB_WR_RDMA_READ ||
		    wqe->wr.opcode == IB_WR_TID_RDMA_WRITE)
			qp->s_psn = wqe->lpsn + 1;
		अन्यथा अगर (wqe->wr.opcode == IB_WR_TID_RDMA_READ)
			qp->s_psn = req->s_next_psn;
		अन्यथा
			qp->s_psn++;
		अवरोध;

	हाल OP(RDMA_READ_RESPONSE_FIRST):
		/*
		 * qp->s_state is normally set to the opcode of the
		 * last packet स्थिरructed क्रम new requests and thereक्रमe
		 * is never set to RDMA पढ़ो response.
		 * RDMA_READ_RESPONSE_FIRST is used by the ACK processing
		 * thपढ़ो to indicate a SEND needs to be restarted from an
		 * earlier PSN without पूर्णांकerfering with the sending thपढ़ो.
		 * See restart_rc().
		 */
		qp->s_len = restart_sge(&qp->s_sge, wqe, qp->s_psn, pmtu);
		fallthrough;
	हाल OP(SEND_FIRST):
		qp->s_state = OP(SEND_MIDDLE);
		fallthrough;
	हाल OP(SEND_MIDDLE):
		bth2 = mask_psn(qp->s_psn++);
		ss = &qp->s_sge;
		len = qp->s_len;
		अगर (len > pmtu) अणु
			len = pmtu;
			middle = HFI1_CAP_IS_KSET(SDMA_AHG);
			अवरोध;
		पूर्ण
		अगर (wqe->wr.opcode == IB_WR_SEND) अणु
			qp->s_state = OP(SEND_LAST);
		पूर्ण अन्यथा अगर (wqe->wr.opcode == IB_WR_SEND_WITH_IMM) अणु
			qp->s_state = OP(SEND_LAST_WITH_IMMEDIATE);
			/* Immediate data comes after the BTH */
			ohdr->u.imm_data = wqe->wr.ex.imm_data;
			hwords += 1;
		पूर्ण अन्यथा अणु
			qp->s_state = OP(SEND_LAST_WITH_INVALIDATE);
			/* invalidate data comes after the BTH */
			ohdr->u.ieth = cpu_to_be32(wqe->wr.ex.invalidate_rkey);
			hwords += 1;
		पूर्ण
		अगर (wqe->wr.send_flags & IB_SEND_SOLICITED)
			bth0 |= IB_BTH_SOLICITED;
		bth2 |= IB_BTH_REQ_ACK;
		qp->s_cur++;
		अगर (qp->s_cur >= qp->s_size)
			qp->s_cur = 0;
		अवरोध;

	हाल OP(RDMA_READ_RESPONSE_LAST):
		/*
		 * qp->s_state is normally set to the opcode of the
		 * last packet स्थिरructed क्रम new requests and thereक्रमe
		 * is never set to RDMA पढ़ो response.
		 * RDMA_READ_RESPONSE_LAST is used by the ACK processing
		 * thपढ़ो to indicate a RDMA ग_लिखो needs to be restarted from
		 * an earlier PSN without पूर्णांकerfering with the sending thपढ़ो.
		 * See restart_rc().
		 */
		qp->s_len = restart_sge(&qp->s_sge, wqe, qp->s_psn, pmtu);
		fallthrough;
	हाल OP(RDMA_WRITE_FIRST):
		qp->s_state = OP(RDMA_WRITE_MIDDLE);
		fallthrough;
	हाल OP(RDMA_WRITE_MIDDLE):
		bth2 = mask_psn(qp->s_psn++);
		ss = &qp->s_sge;
		len = qp->s_len;
		अगर (len > pmtu) अणु
			len = pmtu;
			middle = HFI1_CAP_IS_KSET(SDMA_AHG);
			अवरोध;
		पूर्ण
		अगर (wqe->wr.opcode == IB_WR_RDMA_WRITE) अणु
			qp->s_state = OP(RDMA_WRITE_LAST);
		पूर्ण अन्यथा अणु
			qp->s_state = OP(RDMA_WRITE_LAST_WITH_IMMEDIATE);
			/* Immediate data comes after the BTH */
			ohdr->u.imm_data = wqe->wr.ex.imm_data;
			hwords += 1;
			अगर (wqe->wr.send_flags & IB_SEND_SOLICITED)
				bth0 |= IB_BTH_SOLICITED;
		पूर्ण
		bth2 |= IB_BTH_REQ_ACK;
		qp->s_cur++;
		अगर (qp->s_cur >= qp->s_size)
			qp->s_cur = 0;
		अवरोध;

	हाल OP(RDMA_READ_RESPONSE_MIDDLE):
		/*
		 * qp->s_state is normally set to the opcode of the
		 * last packet स्थिरructed क्रम new requests and thereक्रमe
		 * is never set to RDMA पढ़ो response.
		 * RDMA_READ_RESPONSE_MIDDLE is used by the ACK processing
		 * thपढ़ो to indicate a RDMA पढ़ो needs to be restarted from
		 * an earlier PSN without पूर्णांकerfering with the sending thपढ़ो.
		 * See restart_rc().
		 */
		len = (delta_psn(qp->s_psn, wqe->psn)) * pmtu;
		put_ib_reth_vaddr(
			wqe->rdma_wr.remote_addr + len,
			&ohdr->u.rc.reth);
		ohdr->u.rc.reth.rkey =
			cpu_to_be32(wqe->rdma_wr.rkey);
		ohdr->u.rc.reth.length = cpu_to_be32(wqe->length - len);
		qp->s_state = OP(RDMA_READ_REQUEST);
		hwords += माप(ohdr->u.rc.reth) / माप(u32);
		bth2 = mask_psn(qp->s_psn) | IB_BTH_REQ_ACK;
		qp->s_psn = wqe->lpsn + 1;
		ss = शून्य;
		len = 0;
		qp->s_cur++;
		अगर (qp->s_cur == qp->s_size)
			qp->s_cur = 0;
		अवरोध;

	हाल TID_OP(WRITE_RESP):
		/*
		 * This value क्रम s_state is used क्रम restarting a TID RDMA
		 * WRITE request. See comment in OP(RDMA_READ_RESPONSE_MIDDLE
		 * क्रम more).
		 */
		req = wqe_to_tid_req(wqe);
		req->state = TID_REQUEST_RESEND;
		rcu_पढ़ो_lock();
		remote = rcu_dereference(priv->tid_rdma.remote);
		req->comp_seg = delta_psn(qp->s_psn, wqe->psn);
		len = wqe->length - (req->comp_seg * remote->max_len);
		rcu_पढ़ो_unlock();

		bth2 = mask_psn(qp->s_psn);
		hwords += hfi1_build_tid_rdma_ग_लिखो_req(qp, wqe, ohdr, &bth1,
							&bth2, &len);
		qp->s_psn = wqe->lpsn + 1;
		ss = शून्य;
		qp->s_state = TID_OP(WRITE_REQ);
		priv->pending_tid_w_resp += delta_psn(wqe->lpsn, bth2) + 1;
		priv->s_tid_cur = qp->s_cur;
		अगर (++qp->s_cur == qp->s_size)
			qp->s_cur = 0;
		trace_hfi1_tid_req_make_req_ग_लिखो(qp, 0, wqe->wr.opcode,
						  wqe->psn, wqe->lpsn, req);
		अवरोध;

	हाल TID_OP(READ_RESP):
		अगर (wqe->wr.opcode != IB_WR_TID_RDMA_READ)
			जाओ bail;
		/* This is used to restart a TID पढ़ो request */
		req = wqe_to_tid_req(wqe);
		wpriv = wqe->priv;
		/*
		 * Back करोwn. The field qp->s_psn has been set to the psn with
		 * which the request should be restart. It's OK to use भागision
		 * as this is on the retry path.
		 */
		req->cur_seg = delta_psn(qp->s_psn, wqe->psn) / priv->pkts_ps;

		/*
		 * The following function need to be redefined to वापस the
		 * status to make sure that we find the flow. At the same
		 * समय, we can use the req->state change to check अगर the
		 * call succeeds or not.
		 */
		req->state = TID_REQUEST_RESEND;
		hfi1_tid_rdma_restart_req(qp, wqe, &bth2);
		अगर (req->state != TID_REQUEST_ACTIVE) अणु
			/*
			 * Failed to find the flow. Release all allocated tid
			 * resources.
			 */
			hfi1_kern_exp_rcv_clear_all(req);
			hfi1_kern_clear_hw_flow(priv->rcd, qp);

			hfi1_trdma_send_complete(qp, wqe, IB_WC_LOC_QP_OP_ERR);
			जाओ bail;
		पूर्ण
		req->state = TID_REQUEST_RESEND;
		len = min_t(u32, req->seg_len,
			    wqe->length - req->seg_len * req->cur_seg);
		flow = &req->flows[req->flow_idx];
		len -= flow->sent;
		req->s_next_psn = flow->flow_state.ib_lpsn + 1;
		delta = hfi1_build_tid_rdma_पढ़ो_packet(wqe, ohdr, &bth1,
							&bth2, &len);
		अगर (delta <= 0) अणु
			/* Wait क्रम TID space */
			जाओ bail;
		पूर्ण
		hwords += delta;
		ss = &wpriv->ss;
		/* Check अगर this is the last segment */
		अगर (req->cur_seg >= req->total_segs &&
		    ++qp->s_cur == qp->s_size)
			qp->s_cur = 0;
		qp->s_psn = req->s_next_psn;
		trace_hfi1_tid_req_make_req_पढ़ो(qp, 0, wqe->wr.opcode,
						 wqe->psn, wqe->lpsn, req);
		अवरोध;
	हाल TID_OP(READ_REQ):
		req = wqe_to_tid_req(wqe);
		delta = cmp_psn(qp->s_psn, wqe->psn);
		/*
		 * If the current WR is not TID RDMA READ, or this is the start
		 * of a new request, we need to change the qp->s_state so that
		 * the request can be set up properly.
		 */
		अगर (wqe->wr.opcode != IB_WR_TID_RDMA_READ || delta == 0 ||
		    qp->s_cur == qp->s_tail) अणु
			qp->s_state = OP(RDMA_READ_REQUEST);
			अगर (delta == 0 || qp->s_cur == qp->s_tail)
				जाओ check_s_state;
			अन्यथा
				जाओ bail;
		पूर्ण

		/* Rate limiting */
		अगर (qp->s_num_rd_atomic >= qp->s_max_rd_atomic) अणु
			qp->s_flags |= RVT_S_WAIT_RDMAR;
			जाओ bail;
		पूर्ण

		wpriv = wqe->priv;
		/* Read one segment at a समय */
		len = min_t(u32, req->seg_len,
			    wqe->length - req->seg_len * req->cur_seg);
		delta = hfi1_build_tid_rdma_पढ़ो_req(qp, wqe, ohdr, &bth1,
						     &bth2, &len);
		अगर (delta <= 0) अणु
			/* Wait क्रम TID space */
			जाओ bail;
		पूर्ण
		hwords += delta;
		ss = &wpriv->ss;
		/* Check अगर this is the last segment */
		अगर (req->cur_seg >= req->total_segs &&
		    ++qp->s_cur == qp->s_size)
			qp->s_cur = 0;
		qp->s_psn = req->s_next_psn;
		trace_hfi1_tid_req_make_req_पढ़ो(qp, 0, wqe->wr.opcode,
						 wqe->psn, wqe->lpsn, req);
		अवरोध;
	पूर्ण
	qp->s_sending_hpsn = bth2;
	delta = delta_psn(bth2, wqe->psn);
	अगर (delta && delta % HFI1_PSN_CREDIT == 0 &&
	    wqe->wr.opcode != IB_WR_TID_RDMA_WRITE)
		bth2 |= IB_BTH_REQ_ACK;
	अगर (qp->s_flags & RVT_S_SEND_ONE) अणु
		qp->s_flags &= ~RVT_S_SEND_ONE;
		qp->s_flags |= RVT_S_WAIT_ACK;
		bth2 |= IB_BTH_REQ_ACK;
	पूर्ण
	qp->s_len -= len;
	ps->s_txreq->hdr_dwords = hwords;
	ps->s_txreq->sde = priv->s_sde;
	ps->s_txreq->ss = ss;
	ps->s_txreq->s_cur_size = len;
	hfi1_make_ruc_header(
		qp,
		ohdr,
		bth0 | (qp->s_state << 24),
		bth1,
		bth2,
		middle,
		ps);
	वापस 1;

करोne_मुक्त_tx:
	hfi1_put_txreq(ps->s_txreq);
	ps->s_txreq = शून्य;
	वापस 1;

bail:
	hfi1_put_txreq(ps->s_txreq);

bail_no_tx:
	ps->s_txreq = शून्य;
	qp->s_flags &= ~RVT_S_BUSY;
	/*
	 * If we didn't get a txreq, the QP will be woken up later to try
	 * again. Set the flags to indicate which work item to wake
	 * up.
	 */
	ioरुको_set_flag(&priv->s_ioरुको, IOWAIT_PENDING_IB);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम hfi1_make_bth_aeth(काष्ठा rvt_qp *qp,
				      काष्ठा ib_other_headers *ohdr,
				      u32 bth0, u32 bth1)
अणु
	अगर (qp->r_nak_state)
		ohdr->u.aeth = cpu_to_be32((qp->r_msn & IB_MSN_MASK) |
					    (qp->r_nak_state <<
					     IB_AETH_CREDIT_SHIFT));
	अन्यथा
		ohdr->u.aeth = rvt_compute_aeth(qp);

	ohdr->bth[0] = cpu_to_be32(bth0);
	ohdr->bth[1] = cpu_to_be32(bth1 | qp->remote_qpn);
	ohdr->bth[2] = cpu_to_be32(mask_psn(qp->r_ack_psn));
पूर्ण

अटल अंतरभूत व्योम hfi1_queue_rc_ack(काष्ठा hfi1_packet *packet, bool is_fecn)
अणु
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_ibport *ibp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->s_lock, flags);
	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK))
		जाओ unlock;
	ibp = rcd_to_iport(packet->rcd);
	this_cpu_inc(*ibp->rvp.rc_qacks);
	qp->s_flags |= RVT_S_ACK_PENDING | RVT_S_RESP_PENDING;
	qp->s_nak_state = qp->r_nak_state;
	qp->s_ack_psn = qp->r_ack_psn;
	अगर (is_fecn)
		qp->s_flags |= RVT_S_ECN;

	/* Schedule the send tasklet. */
	hfi1_schedule_send(qp);
unlock:
	spin_unlock_irqrestore(&qp->s_lock, flags);
पूर्ण

अटल अंतरभूत व्योम hfi1_make_rc_ack_9B(काष्ठा hfi1_packet *packet,
				       काष्ठा hfi1_opa_header *opa_hdr,
				       u8 sc5, bool is_fecn,
				       u64 *pbc_flags, u32 *hwords,
				       u32 *nwords)
अणु
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_ibport *ibp = rcd_to_iport(packet->rcd);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा ib_header *hdr = &opa_hdr->ibh;
	काष्ठा ib_other_headers *ohdr;
	u16 lrh0 = HFI1_LRH_BTH;
	u16 pkey;
	u32 bth0, bth1;

	opa_hdr->hdr_type = HFI1_PKT_TYPE_9B;
	ohdr = &hdr->u.oth;
	/* header size in 32-bit words LRH+BTH+AETH = (8+12+4)/4 */
	*hwords = 6;

	अगर (unlikely(rdma_ah_get_ah_flags(&qp->remote_ah_attr) & IB_AH_GRH)) अणु
		*hwords += hfi1_make_grh(ibp, &hdr->u.l.grh,
					 rdma_ah_पढ़ो_grh(&qp->remote_ah_attr),
					 *hwords - 2, SIZE_OF_CRC);
		ohdr = &hdr->u.l.oth;
		lrh0 = HFI1_LRH_GRH;
	पूर्ण
	/* set PBC_DC_INFO bit (aka SC[4]) in pbc_flags */
	*pbc_flags |= ((!!(sc5 & 0x10)) << PBC_DC_INFO_SHIFT);

	/* पढ़ो pkey_index w/o lock (its atomic) */
	pkey = hfi1_get_pkey(ibp, qp->s_pkey_index);

	lrh0 |= (sc5 & IB_SC_MASK) << IB_SC_SHIFT |
		(rdma_ah_get_sl(&qp->remote_ah_attr) & IB_SL_MASK) <<
			IB_SL_SHIFT;

	hfi1_make_ib_hdr(hdr, lrh0, *hwords + SIZE_OF_CRC,
			 opa_get_lid(rdma_ah_get_dlid(&qp->remote_ah_attr), 9B),
			 ppd->lid | rdma_ah_get_path_bits(&qp->remote_ah_attr));

	bth0 = pkey | (OP(ACKNOWLEDGE) << 24);
	अगर (qp->s_mig_state == IB_MIG_MIGRATED)
		bth0 |= IB_BTH_MIG_REQ;
	bth1 = (!!is_fecn) << IB_BECN_SHIFT;
	/*
	 * Inline ACKs go out without the use of the Verbs send engine, so
	 * we need to set the STL Verbs Extended bit here
	 */
	bth1 |= HFI1_CAP_IS_KSET(OPFN) << IB_BTHE_E_SHIFT;
	hfi1_make_bth_aeth(qp, ohdr, bth0, bth1);
पूर्ण

अटल अंतरभूत व्योम hfi1_make_rc_ack_16B(काष्ठा hfi1_packet *packet,
					काष्ठा hfi1_opa_header *opa_hdr,
					u8 sc5, bool is_fecn,
					u64 *pbc_flags, u32 *hwords,
					u32 *nwords)
अणु
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_ibport *ibp = rcd_to_iport(packet->rcd);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा hfi1_16b_header *hdr = &opa_hdr->opah;
	काष्ठा ib_other_headers *ohdr;
	u32 bth0, bth1 = 0;
	u16 len, pkey;
	bool becn = is_fecn;
	u8 l4 = OPA_16B_L4_IB_LOCAL;
	u8 extra_bytes;

	opa_hdr->hdr_type = HFI1_PKT_TYPE_16B;
	ohdr = &hdr->u.oth;
	/* header size in 32-bit words 16B LRH+BTH+AETH = (16+12+4)/4 */
	*hwords = 8;
	extra_bytes = hfi1_get_16b_padding(*hwords << 2, 0);
	*nwords = SIZE_OF_CRC + ((extra_bytes + SIZE_OF_LT) >> 2);

	अगर (unlikely(rdma_ah_get_ah_flags(&qp->remote_ah_attr) & IB_AH_GRH) &&
	    hfi1_check_mcast(rdma_ah_get_dlid(&qp->remote_ah_attr))) अणु
		*hwords += hfi1_make_grh(ibp, &hdr->u.l.grh,
					 rdma_ah_पढ़ो_grh(&qp->remote_ah_attr),
					 *hwords - 4, *nwords);
		ohdr = &hdr->u.l.oth;
		l4 = OPA_16B_L4_IB_GLOBAL;
	पूर्ण
	*pbc_flags |= PBC_PACKET_BYPASS | PBC_INSERT_BYPASS_ICRC;

	/* पढ़ो pkey_index w/o lock (its atomic) */
	pkey = hfi1_get_pkey(ibp, qp->s_pkey_index);

	/* Convert dwords to flits */
	len = (*hwords + *nwords) >> 1;

	hfi1_make_16b_hdr(hdr, ppd->lid |
			  (rdma_ah_get_path_bits(&qp->remote_ah_attr) &
			  ((1 << ppd->lmc) - 1)),
			  opa_get_lid(rdma_ah_get_dlid(&qp->remote_ah_attr),
				      16B), len, pkey, becn, 0, l4, sc5);

	bth0 = pkey | (OP(ACKNOWLEDGE) << 24);
	bth0 |= extra_bytes << 20;
	अगर (qp->s_mig_state == IB_MIG_MIGRATED)
		bth1 = OPA_BTH_MIG_REQ;
	hfi1_make_bth_aeth(qp, ohdr, bth0, bth1);
पूर्ण

प्रकार व्योम (*hfi1_make_rc_ack)(काष्ठा hfi1_packet *packet,
				 काष्ठा hfi1_opa_header *opa_hdr,
				 u8 sc5, bool is_fecn,
				 u64 *pbc_flags, u32 *hwords,
				 u32 *nwords);

/* We support only two types - 9B and 16B क्रम now */
अटल स्थिर hfi1_make_rc_ack hfi1_make_rc_ack_tbl[2] = अणु
	[HFI1_PKT_TYPE_9B] = &hfi1_make_rc_ack_9B,
	[HFI1_PKT_TYPE_16B] = &hfi1_make_rc_ack_16B
पूर्ण;

/*
 * hfi1_send_rc_ack - Conकाष्ठा an ACK packet and send it
 *
 * This is called from hfi1_rc_rcv() and handle_receive_पूर्णांकerrupt().
 * Note that RDMA पढ़ोs and atomics are handled in the
 * send side QP state and send engine.
 */
व्योम hfi1_send_rc_ack(काष्ठा hfi1_packet *packet, bool is_fecn)
अणु
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_ibport *ibp = rcd_to_iport(rcd);
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u8 sc5 = ibp->sl_to_sc[rdma_ah_get_sl(&qp->remote_ah_attr)];
	u64 pbc, pbc_flags = 0;
	u32 hwords = 0;
	u32 nwords = 0;
	u32 plen;
	काष्ठा pio_buf *pbuf;
	काष्ठा hfi1_opa_header opa_hdr;

	/* clear the defer count */
	qp->r_adefered = 0;

	/* Don't send ACK or NAK अगर a RDMA पढ़ो or atomic is pending. */
	अगर (qp->s_flags & RVT_S_RESP_PENDING) अणु
		hfi1_queue_rc_ack(packet, is_fecn);
		वापस;
	पूर्ण

	/* Ensure s_rdma_ack_cnt changes are committed */
	अगर (qp->s_rdma_ack_cnt) अणु
		hfi1_queue_rc_ack(packet, is_fecn);
		वापस;
	पूर्ण

	/* Don't try to send ACKs if the link isn't ACTIVE */
	अगर (driver_lstate(ppd) != IB_PORT_ACTIVE)
		वापस;

	/* Make the appropriate header */
	hfi1_make_rc_ack_tbl[priv->hdr_type](packet, &opa_hdr, sc5, is_fecn,
					     &pbc_flags, &hwords, &nwords);

	plen = 2 /* PBC */ + hwords + nwords;
	pbc = create_pbc(ppd, pbc_flags, qp->srate_mbps,
			 sc_to_vlt(ppd->dd, sc5), plen);
	pbuf = sc_buffer_alloc(rcd->sc, plen, शून्य, शून्य);
	अगर (IS_ERR_OR_शून्य(pbuf)) अणु
		/*
		 * We have no room to send at the moment.  Pass
		 * responsibility क्रम sending the ACK to the send engine
		 * so that when enough buffer space becomes available,
		 * the ACK is sent ahead of other outgoing packets.
		 */
		hfi1_queue_rc_ack(packet, is_fecn);
		वापस;
	पूर्ण
	trace_ack_output_ibhdr(dd_from_ibdev(qp->ibqp.device),
			       &opa_hdr, ib_is_sc5(sc5));

	/* ग_लिखो the pbc and data */
	ppd->dd->pio_अंतरभूत_send(ppd->dd, pbuf, pbc,
				 (priv->hdr_type == HFI1_PKT_TYPE_9B ?
				 (व्योम *)&opa_hdr.ibh :
				 (व्योम *)&opa_hdr.opah), hwords);
	वापस;
पूर्ण

/**
 * update_num_rd_atomic - update the qp->s_num_rd_atomic
 * @qp: the QP
 * @psn: the packet sequence number to restart at
 * @wqe: the wqe
 *
 * This is called from reset_psn() to update qp->s_num_rd_atomic
 * क्रम the current wqe.
 * Called at पूर्णांकerrupt level with the QP s_lock held.
 */
अटल व्योम update_num_rd_atomic(काष्ठा rvt_qp *qp, u32 psn,
				 काष्ठा rvt_swqe *wqe)
अणु
	u32 opcode = wqe->wr.opcode;

	अगर (opcode == IB_WR_RDMA_READ ||
	    opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
	    opcode == IB_WR_ATOMIC_FETCH_AND_ADD) अणु
		qp->s_num_rd_atomic++;
	पूर्ण अन्यथा अगर (opcode == IB_WR_TID_RDMA_READ) अणु
		काष्ठा tid_rdma_request *req = wqe_to_tid_req(wqe);
		काष्ठा hfi1_qp_priv *priv = qp->priv;

		अगर (cmp_psn(psn, wqe->lpsn) <= 0) अणु
			u32 cur_seg;

			cur_seg = (psn - wqe->psn) / priv->pkts_ps;
			req->ack_pending = cur_seg - req->comp_seg;
			priv->pending_tid_r_segs += req->ack_pending;
			qp->s_num_rd_atomic += req->ack_pending;
			trace_hfi1_tid_req_update_num_rd_atomic(qp, 0,
								wqe->wr.opcode,
								wqe->psn,
								wqe->lpsn,
								req);
		पूर्ण अन्यथा अणु
			priv->pending_tid_r_segs += req->total_segs;
			qp->s_num_rd_atomic += req->total_segs;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * reset_psn - reset the QP state to send starting from PSN
 * @qp: the QP
 * @psn: the packet sequence number to restart at
 *
 * This is called from hfi1_rc_rcv() to process an incoming RC ACK
 * क्रम the given QP.
 * Called at पूर्णांकerrupt level with the QP s_lock held.
 */
अटल व्योम reset_psn(काष्ठा rvt_qp *qp, u32 psn)
अणु
	u32 n = qp->s_acked;
	काष्ठा rvt_swqe *wqe = rvt_get_swqe_ptr(qp, n);
	u32 opcode;
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	lockdep_निश्चित_held(&qp->s_lock);
	qp->s_cur = n;
	priv->pending_tid_r_segs = 0;
	priv->pending_tid_w_resp = 0;
	qp->s_num_rd_atomic = 0;

	/*
	 * If we are starting the request from the beginning,
	 * let the normal send code handle initialization.
	 */
	अगर (cmp_psn(psn, wqe->psn) <= 0) अणु
		qp->s_state = OP(SEND_LAST);
		जाओ करोne;
	पूर्ण
	update_num_rd_atomic(qp, psn, wqe);

	/* Find the work request opcode corresponding to the given PSN. */
	क्रम (;;) अणु
		पूर्णांक dअगरf;

		अगर (++n == qp->s_size)
			n = 0;
		अगर (n == qp->s_tail)
			अवरोध;
		wqe = rvt_get_swqe_ptr(qp, n);
		dअगरf = cmp_psn(psn, wqe->psn);
		अगर (dअगरf < 0) अणु
			/* Poपूर्णांक wqe back to the previous one*/
			wqe = rvt_get_swqe_ptr(qp, qp->s_cur);
			अवरोध;
		पूर्ण
		qp->s_cur = n;
		/*
		 * If we are starting the request from the beginning,
		 * let the normal send code handle initialization.
		 */
		अगर (dअगरf == 0) अणु
			qp->s_state = OP(SEND_LAST);
			जाओ करोne;
		पूर्ण

		update_num_rd_atomic(qp, psn, wqe);
	पूर्ण
	opcode = wqe->wr.opcode;

	/*
	 * Set the state to restart in the middle of a request.
	 * Don't change the s_sge, s_cur_sge, or s_cur_size.
	 * See hfi1_make_rc_req().
	 */
	चयन (opcode) अणु
	हाल IB_WR_SEND:
	हाल IB_WR_SEND_WITH_IMM:
		qp->s_state = OP(RDMA_READ_RESPONSE_FIRST);
		अवरोध;

	हाल IB_WR_RDMA_WRITE:
	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		qp->s_state = OP(RDMA_READ_RESPONSE_LAST);
		अवरोध;

	हाल IB_WR_TID_RDMA_WRITE:
		qp->s_state = TID_OP(WRITE_RESP);
		अवरोध;

	हाल IB_WR_RDMA_READ:
		qp->s_state = OP(RDMA_READ_RESPONSE_MIDDLE);
		अवरोध;

	हाल IB_WR_TID_RDMA_READ:
		qp->s_state = TID_OP(READ_RESP);
		अवरोध;

	शेष:
		/*
		 * This हाल shouldn't happen since its only
		 * one PSN per req.
		 */
		qp->s_state = OP(SEND_LAST);
	पूर्ण
करोne:
	priv->s_flags &= ~HFI1_S_TID_WAIT_INTERLCK;
	qp->s_psn = psn;
	/*
	 * Set RVT_S_WAIT_PSN as rc_complete() may start the समयr
	 * asynchronously beक्रमe the send engine can get scheduled.
	 * Doing it in hfi1_make_rc_req() is too late.
	 */
	अगर ((cmp_psn(qp->s_psn, qp->s_sending_hpsn) <= 0) &&
	    (cmp_psn(qp->s_sending_psn, qp->s_sending_hpsn) <= 0))
		qp->s_flags |= RVT_S_WAIT_PSN;
	qp->s_flags &= ~HFI1_S_AHG_VALID;
	trace_hfi1_sender_reset_psn(qp);
पूर्ण

/*
 * Back up requester to resend the last un-ACKed request.
 * The QP r_lock and s_lock should be held and पूर्णांकerrupts disabled.
 */
व्योम hfi1_restart_rc(काष्ठा rvt_qp *qp, u32 psn, पूर्णांक रुको)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा rvt_swqe *wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
	काष्ठा hfi1_ibport *ibp;

	lockdep_निश्चित_held(&qp->r_lock);
	lockdep_निश्चित_held(&qp->s_lock);
	trace_hfi1_sender_restart_rc(qp);
	अगर (qp->s_retry == 0) अणु
		अगर (qp->s_mig_state == IB_MIG_ARMED) अणु
			hfi1_migrate_qp(qp);
			qp->s_retry = qp->s_retry_cnt;
		पूर्ण अन्यथा अगर (qp->s_last == qp->s_acked) अणु
			/*
			 * We need special handling क्रम the OPFN request WQEs as
			 * they are not allowed to generate real user errors
			 */
			अगर (wqe->wr.opcode == IB_WR_OPFN) अणु
				काष्ठा hfi1_ibport *ibp =
					to_iport(qp->ibqp.device, qp->port_num);
				/*
				 * Call opfn_conn_reply() with capcode and
				 * reमुख्यing data as 0 to बंद out the
				 * current request
				 */
				opfn_conn_reply(qp, priv->opfn.curr);
				wqe = करो_rc_completion(qp, wqe, ibp);
				qp->s_flags &= ~RVT_S_WAIT_ACK;
			पूर्ण अन्यथा अणु
				trace_hfi1_tid_ग_लिखो_sender_restart_rc(qp, 0);
				अगर (wqe->wr.opcode == IB_WR_TID_RDMA_READ) अणु
					काष्ठा tid_rdma_request *req;

					req = wqe_to_tid_req(wqe);
					hfi1_kern_exp_rcv_clear_all(req);
					hfi1_kern_clear_hw_flow(priv->rcd, qp);
				पूर्ण

				hfi1_trdma_send_complete(qp, wqe,
							 IB_WC_RETRY_EXC_ERR);
				rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);
			पूर्ण
			वापस;
		पूर्ण अन्यथा अणु /* need to handle delayed completion */
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		qp->s_retry--;
	पूर्ण

	ibp = to_iport(qp->ibqp.device, qp->port_num);
	अगर (wqe->wr.opcode == IB_WR_RDMA_READ ||
	    wqe->wr.opcode == IB_WR_TID_RDMA_READ)
		ibp->rvp.n_rc_resends++;
	अन्यथा
		ibp->rvp.n_rc_resends += delta_psn(qp->s_psn, psn);

	qp->s_flags &= ~(RVT_S_WAIT_FENCE | RVT_S_WAIT_RDMAR |
			 RVT_S_WAIT_SSN_CREDIT | RVT_S_WAIT_PSN |
			 RVT_S_WAIT_ACK | HFI1_S_WAIT_TID_RESP);
	अगर (रुको)
		qp->s_flags |= RVT_S_SEND_ONE;
	reset_psn(qp, psn);
पूर्ण

/*
 * Set qp->s_sending_psn to the next PSN after the given one.
 * This would be psn+1 except when RDMA पढ़ोs or TID RDMA ops
 * are present.
 */
अटल व्योम reset_sending_psn(काष्ठा rvt_qp *qp, u32 psn)
अणु
	काष्ठा rvt_swqe *wqe;
	u32 n = qp->s_last;

	lockdep_निश्चित_held(&qp->s_lock);
	/* Find the work request corresponding to the given PSN. */
	क्रम (;;) अणु
		wqe = rvt_get_swqe_ptr(qp, n);
		अगर (cmp_psn(psn, wqe->lpsn) <= 0) अणु
			अगर (wqe->wr.opcode == IB_WR_RDMA_READ ||
			    wqe->wr.opcode == IB_WR_TID_RDMA_READ ||
			    wqe->wr.opcode == IB_WR_TID_RDMA_WRITE)
				qp->s_sending_psn = wqe->lpsn + 1;
			अन्यथा
				qp->s_sending_psn = psn + 1;
			अवरोध;
		पूर्ण
		अगर (++n == qp->s_size)
			n = 0;
		अगर (n == qp->s_tail)
			अवरोध;
	पूर्ण
पूर्ण

/**
 * hfi1_rc_verbs_पातed - handle पात status
 * @qp: the QP
 * @opah: the opa header
 *
 * This code modअगरies both ACK bit in BTH[2]
 * and the s_flags to go पूर्णांकo send one mode.
 *
 * This serves to throttle the send engine to only
 * send a single packet in the likely हाल the
 * a link has gone करोwn.
 */
व्योम hfi1_rc_verbs_पातed(काष्ठा rvt_qp *qp, काष्ठा hfi1_opa_header *opah)
अणु
	काष्ठा ib_other_headers *ohdr = hfi1_get_rc_ohdr(opah);
	u8 opcode = ib_bth_get_opcode(ohdr);
	u32 psn;

	/* ignore responses */
	अगर ((opcode >= OP(RDMA_READ_RESPONSE_FIRST) &&
	     opcode <= OP(ATOMIC_ACKNOWLEDGE)) ||
	    opcode == TID_OP(READ_RESP) ||
	    opcode == TID_OP(WRITE_RESP))
		वापस;

	psn = ib_bth_get_psn(ohdr) | IB_BTH_REQ_ACK;
	ohdr->bth[2] = cpu_to_be32(psn);
	qp->s_flags |= RVT_S_SEND_ONE;
पूर्ण

/*
 * This should be called with the QP s_lock held and पूर्णांकerrupts disabled.
 */
व्योम hfi1_rc_send_complete(काष्ठा rvt_qp *qp, काष्ठा hfi1_opa_header *opah)
अणु
	काष्ठा ib_other_headers *ohdr;
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा rvt_swqe *wqe;
	u32 opcode, head, tail;
	u32 psn;
	काष्ठा tid_rdma_request *req;

	lockdep_निश्चित_held(&qp->s_lock);
	अगर (!(ib_rvt_state_ops[qp->state] & RVT_SEND_OR_FLUSH_OR_RECV_OK))
		वापस;

	ohdr = hfi1_get_rc_ohdr(opah);
	opcode = ib_bth_get_opcode(ohdr);
	अगर ((opcode >= OP(RDMA_READ_RESPONSE_FIRST) &&
	     opcode <= OP(ATOMIC_ACKNOWLEDGE)) ||
	    opcode == TID_OP(READ_RESP) ||
	    opcode == TID_OP(WRITE_RESP)) अणु
		WARN_ON(!qp->s_rdma_ack_cnt);
		qp->s_rdma_ack_cnt--;
		वापस;
	पूर्ण

	psn = ib_bth_get_psn(ohdr);
	/*
	 * Don't attempt to reset the sending PSN क्रम packets in the
	 * KDETH PSN space since the PSN करोes not match anything.
	 */
	अगर (opcode != TID_OP(WRITE_DATA) &&
	    opcode != TID_OP(WRITE_DATA_LAST) &&
	    opcode != TID_OP(ACK) && opcode != TID_OP(RESYNC))
		reset_sending_psn(qp, psn);

	/* Handle TID RDMA WRITE packets dअगरferently */
	अगर (opcode >= TID_OP(WRITE_REQ) &&
	    opcode <= TID_OP(WRITE_DATA_LAST)) अणु
		head = priv->s_tid_head;
		tail = priv->s_tid_cur;
		/*
		 * s_tid_cur is set to s_tid_head in the हाल, where
		 * a new TID RDMA request is being started and all
		 * previous ones have been completed.
		 * Thereक्रमe, we need to करो a secondary check in order
		 * to properly determine whether we should start the
		 * RC समयr.
		 */
		wqe = rvt_get_swqe_ptr(qp, tail);
		req = wqe_to_tid_req(wqe);
		अगर (head == tail && req->comp_seg < req->total_segs) अणु
			अगर (tail == 0)
				tail = qp->s_size - 1;
			अन्यथा
				tail -= 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		head = qp->s_tail;
		tail = qp->s_acked;
	पूर्ण

	/*
	 * Start समयr after a packet requesting an ACK has been sent and
	 * there are still requests that haven't been acked.
	 */
	अगर ((psn & IB_BTH_REQ_ACK) && tail != head &&
	    opcode != TID_OP(WRITE_DATA) && opcode != TID_OP(WRITE_DATA_LAST) &&
	    opcode != TID_OP(RESYNC) &&
	    !(qp->s_flags &
	      (RVT_S_TIMER | RVT_S_WAIT_RNR | RVT_S_WAIT_PSN)) &&
	    (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK)) अणु
		अगर (opcode == TID_OP(READ_REQ))
			rvt_add_retry_समयr_ext(qp, priv->समयout_shअगरt);
		अन्यथा
			rvt_add_retry_समयr(qp);
	पूर्ण

	/* Start TID RDMA ACK समयr */
	अगर ((opcode == TID_OP(WRITE_DATA) ||
	     opcode == TID_OP(WRITE_DATA_LAST) ||
	     opcode == TID_OP(RESYNC)) &&
	    (psn & IB_BTH_REQ_ACK) &&
	    !(priv->s_flags & HFI1_S_TID_RETRY_TIMER) &&
	    (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK)) अणु
		/*
		 * The TID RDMA ACK packet could be received beक्रमe this
		 * function is called. Thereक्रमe, add the समयr only अगर TID
		 * RDMA ACK packets are actually pending.
		 */
		wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
		req = wqe_to_tid_req(wqe);
		अगर (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE &&
		    req->ack_seg < req->cur_seg)
			hfi1_add_tid_retry_समयr(qp);
	पूर्ण

	जबतक (qp->s_last != qp->s_acked) अणु
		wqe = rvt_get_swqe_ptr(qp, qp->s_last);
		अगर (cmp_psn(wqe->lpsn, qp->s_sending_psn) >= 0 &&
		    cmp_psn(qp->s_sending_psn, qp->s_sending_hpsn) <= 0)
			अवरोध;
		trdma_clean_swqe(qp, wqe);
		trace_hfi1_qp_send_completion(qp, wqe, qp->s_last);
		rvt_qp_complete_swqe(qp,
				     wqe,
				     ib_hfi1_wc_opcode[wqe->wr.opcode],
				     IB_WC_SUCCESS);
	पूर्ण
	/*
	 * If we were रुकोing क्रम sends to complete beक्रमe re-sending,
	 * and they are now complete, restart sending.
	 */
	trace_hfi1_sendcomplete(qp, psn);
	अगर (qp->s_flags & RVT_S_WAIT_PSN &&
	    cmp_psn(qp->s_sending_psn, qp->s_sending_hpsn) > 0) अणु
		qp->s_flags &= ~RVT_S_WAIT_PSN;
		qp->s_sending_psn = qp->s_psn;
		qp->s_sending_hpsn = qp->s_psn - 1;
		hfi1_schedule_send(qp);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम update_last_psn(काष्ठा rvt_qp *qp, u32 psn)
अणु
	qp->s_last_psn = psn;
पूर्ण

/*
 * Generate a SWQE completion.
 * This is similar to hfi1_send_complete but has to check to be sure
 * that the SGEs are not being referenced अगर the SWQE is being resent.
 */
काष्ठा rvt_swqe *करो_rc_completion(काष्ठा rvt_qp *qp,
				  काष्ठा rvt_swqe *wqe,
				  काष्ठा hfi1_ibport *ibp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	lockdep_निश्चित_held(&qp->s_lock);
	/*
	 * Don't decrement refcount and don't generate a
	 * completion अगर the SWQE is being resent until the send
	 * is finished.
	 */
	trace_hfi1_rc_completion(qp, wqe->lpsn);
	अगर (cmp_psn(wqe->lpsn, qp->s_sending_psn) < 0 ||
	    cmp_psn(qp->s_sending_psn, qp->s_sending_hpsn) > 0) अणु
		trdma_clean_swqe(qp, wqe);
		trace_hfi1_qp_send_completion(qp, wqe, qp->s_last);
		rvt_qp_complete_swqe(qp,
				     wqe,
				     ib_hfi1_wc_opcode[wqe->wr.opcode],
				     IB_WC_SUCCESS);
	पूर्ण अन्यथा अणु
		काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);

		this_cpu_inc(*ibp->rvp.rc_delayed_comp);
		/*
		 * If send progress not running attempt to progress
		 * SDMA queue.
		 */
		अगर (ppd->dd->flags & HFI1_HAS_SEND_DMA) अणु
			काष्ठा sdma_engine *engine;
			u8 sl = rdma_ah_get_sl(&qp->remote_ah_attr);
			u8 sc5;

			/* For now use sc to find engine */
			sc5 = ibp->sl_to_sc[sl];
			engine = qp_to_sdma_engine(qp, sc5);
			sdma_engine_progress_schedule(engine);
		पूर्ण
	पूर्ण

	qp->s_retry = qp->s_retry_cnt;
	/*
	 * Don't update the last PSN अगर the request being completed is
	 * a TID RDMA WRITE request.
	 * Completion of the TID RDMA WRITE requests are करोne by the
	 * TID RDMA ACKs and as such could be क्रम a request that has
	 * alपढ़ोy been ACKed as far as the IB state machine is
	 * concerned.
	 */
	अगर (wqe->wr.opcode != IB_WR_TID_RDMA_WRITE)
		update_last_psn(qp, wqe->lpsn);

	/*
	 * If we are completing a request which is in the process of
	 * being resent, we can stop re-sending it since we know the
	 * responder has alपढ़ोy seen it.
	 */
	अगर (qp->s_acked == qp->s_cur) अणु
		अगर (++qp->s_cur >= qp->s_size)
			qp->s_cur = 0;
		qp->s_acked = qp->s_cur;
		wqe = rvt_get_swqe_ptr(qp, qp->s_cur);
		अगर (qp->s_acked != qp->s_tail) अणु
			qp->s_state = OP(SEND_LAST);
			qp->s_psn = wqe->psn;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (++qp->s_acked >= qp->s_size)
			qp->s_acked = 0;
		अगर (qp->state == IB_QPS_SQD && qp->s_acked == qp->s_cur)
			qp->s_draining = 0;
		wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
	पूर्ण
	अगर (priv->s_flags & HFI1_S_TID_WAIT_INTERLCK) अणु
		priv->s_flags &= ~HFI1_S_TID_WAIT_INTERLCK;
		hfi1_schedule_send(qp);
	पूर्ण
	वापस wqe;
पूर्ण

अटल व्योम set_restart_qp(काष्ठा rvt_qp *qp, काष्ठा hfi1_ctxtdata *rcd)
अणु
	/* Retry this request. */
	अगर (!(qp->r_flags & RVT_R_RDMAR_SEQ)) अणु
		qp->r_flags |= RVT_R_RDMAR_SEQ;
		hfi1_restart_rc(qp, qp->s_last_psn + 1, 0);
		अगर (list_empty(&qp->rspरुको)) अणु
			qp->r_flags |= RVT_R_RSP_SEND;
			rvt_get_qp(qp);
			list_add_tail(&qp->rspरुको, &rcd->qp_रुको_list);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * update_qp_retry_state - Update qp retry state.
 * @qp: the QP
 * @psn: the packet sequence number of the TID RDMA WRITE RESP.
 * @spsn:  The start psn क्रम the given TID RDMA WRITE swqe.
 * @lpsn:  The last psn क्रम the given TID RDMA WRITE swqe.
 *
 * This function is called to update the qp retry state upon
 * receiving a TID WRITE RESP after the qp is scheduled to retry
 * a request.
 */
अटल व्योम update_qp_retry_state(काष्ठा rvt_qp *qp, u32 psn, u32 spsn,
				  u32 lpsn)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;

	qp->s_psn = psn + 1;
	/*
	 * If this is the first TID RDMA WRITE RESP packet क्रम the current
	 * request, change the s_state so that the retry will be processed
	 * correctly. Similarly, अगर this is the last TID RDMA WRITE RESP
	 * packet, change the s_state and advance the s_cur.
	 */
	अगर (cmp_psn(psn, lpsn) >= 0) अणु
		qp->s_cur = qpriv->s_tid_cur + 1;
		अगर (qp->s_cur >= qp->s_size)
			qp->s_cur = 0;
		qp->s_state = TID_OP(WRITE_REQ);
	पूर्ण अन्यथा  अगर (!cmp_psn(psn, spsn)) अणु
		qp->s_cur = qpriv->s_tid_cur;
		qp->s_state = TID_OP(WRITE_RESP);
	पूर्ण
पूर्ण

/*
 * करो_rc_ack - process an incoming RC ACK
 * @qp: the QP the ACK came in on
 * @psn: the packet sequence number of the ACK
 * @opcode: the opcode of the request that resulted in the ACK
 *
 * This is called from rc_rcv_resp() to process an incoming RC ACK
 * क्रम the given QP.
 * May be called at पूर्णांकerrupt level, with the QP s_lock held.
 * Returns 1 अगर OK, 0 अगर current operation should be पातed (NAK).
 */
पूर्णांक करो_rc_ack(काष्ठा rvt_qp *qp, u32 aeth, u32 psn, पूर्णांक opcode,
	      u64 val, काष्ठा hfi1_ctxtdata *rcd)
अणु
	काष्ठा hfi1_ibport *ibp;
	क्रमागत ib_wc_status status;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा rvt_swqe *wqe;
	पूर्णांक ret = 0;
	u32 ack_psn;
	पूर्णांक dअगरf;
	काष्ठा rvt_dev_info *rdi;

	lockdep_निश्चित_held(&qp->s_lock);
	/*
	 * Note that NAKs implicitly ACK outstanding SEND and RDMA ग_लिखो
	 * requests and implicitly NAK RDMA पढ़ो and atomic requests issued
	 * beक्रमe the NAK'ed request.  The MSN won't include the NAK'ed
	 * request but will include an ACK'ed request(s).
	 */
	ack_psn = psn;
	अगर (aeth >> IB_AETH_NAK_SHIFT)
		ack_psn--;
	wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
	ibp = rcd_to_iport(rcd);

	/*
	 * The MSN might be क्रम a later WQE than the PSN indicates so
	 * only complete WQEs that the PSN finishes.
	 */
	जबतक ((dअगरf = delta_psn(ack_psn, wqe->lpsn)) >= 0) अणु
		/*
		 * RDMA_READ_RESPONSE_ONLY is a special हाल since
		 * we want to generate completion events क्रम everything
		 * beक्रमe the RDMA पढ़ो, copy the data, then generate
		 * the completion क्रम the पढ़ो.
		 */
		अगर (wqe->wr.opcode == IB_WR_RDMA_READ &&
		    opcode == OP(RDMA_READ_RESPONSE_ONLY) &&
		    dअगरf == 0) अणु
			ret = 1;
			जाओ bail_stop;
		पूर्ण
		/*
		 * If this request is a RDMA पढ़ो or atomic, and the ACK is
		 * क्रम a later operation, this ACK NAKs the RDMA पढ़ो or
		 * atomic.  In other words, only a RDMA_READ_LAST or ONLY
		 * can ACK a RDMA पढ़ो and likewise क्रम atomic ops.  Note
		 * that the NAK हाल can only happen अगर relaxed ordering is
		 * used and requests are sent after an RDMA पढ़ो or atomic
		 * is sent but beक्रमe the response is received.
		 */
		अगर ((wqe->wr.opcode == IB_WR_RDMA_READ &&
		     (opcode != OP(RDMA_READ_RESPONSE_LAST) || dअगरf != 0)) ||
		    (wqe->wr.opcode == IB_WR_TID_RDMA_READ &&
		     (opcode != TID_OP(READ_RESP) || dअगरf != 0)) ||
		    ((wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		      wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) &&
		     (opcode != OP(ATOMIC_ACKNOWLEDGE) || dअगरf != 0)) ||
		    (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE &&
		     (delta_psn(psn, qp->s_last_psn) != 1))) अणु
			set_restart_qp(qp, rcd);
			/*
			 * No need to process the ACK/NAK since we are
			 * restarting an earlier request.
			 */
			जाओ bail_stop;
		पूर्ण
		अगर (wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		    wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) अणु
			u64 *vaddr = wqe->sg_list[0].vaddr;
			*vaddr = val;
		पूर्ण
		अगर (wqe->wr.opcode == IB_WR_OPFN)
			opfn_conn_reply(qp, val);

		अगर (qp->s_num_rd_atomic &&
		    (wqe->wr.opcode == IB_WR_RDMA_READ ||
		     wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		     wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD)) अणु
			qp->s_num_rd_atomic--;
			/* Restart sending task अगर fence is complete */
			अगर ((qp->s_flags & RVT_S_WAIT_FENCE) &&
			    !qp->s_num_rd_atomic) अणु
				qp->s_flags &= ~(RVT_S_WAIT_FENCE |
						 RVT_S_WAIT_ACK);
				hfi1_schedule_send(qp);
			पूर्ण अन्यथा अगर (qp->s_flags & RVT_S_WAIT_RDMAR) अणु
				qp->s_flags &= ~(RVT_S_WAIT_RDMAR |
						 RVT_S_WAIT_ACK);
				hfi1_schedule_send(qp);
			पूर्ण
		पूर्ण

		/*
		 * TID RDMA WRITE requests will be completed by the TID RDMA
		 * ACK packet handler (see tid_rdma.c).
		 */
		अगर (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE)
			अवरोध;

		wqe = करो_rc_completion(qp, wqe, ibp);
		अगर (qp->s_acked == qp->s_tail)
			अवरोध;
	पूर्ण

	trace_hfi1_rc_ack_करो(qp, aeth, psn, wqe);
	trace_hfi1_sender_करो_rc_ack(qp);
	चयन (aeth >> IB_AETH_NAK_SHIFT) अणु
	हाल 0:         /* ACK */
		this_cpu_inc(*ibp->rvp.rc_acks);
		अगर (wqe->wr.opcode == IB_WR_TID_RDMA_READ) अणु
			अगर (wqe_to_tid_req(wqe)->ack_pending)
				rvt_mod_retry_समयr_ext(qp,
							qpriv->समयout_shअगरt);
			अन्यथा
				rvt_stop_rc_समयrs(qp);
		पूर्ण अन्यथा अगर (qp->s_acked != qp->s_tail) अणु
			काष्ठा rvt_swqe *__w = शून्य;

			अगर (qpriv->s_tid_cur != HFI1_QP_WQE_INVALID)
				__w = rvt_get_swqe_ptr(qp, qpriv->s_tid_cur);

			/*
			 * Stop समयrs अगर we've received all of the TID RDMA
			 * WRITE * responses.
			 */
			अगर (__w && __w->wr.opcode == IB_WR_TID_RDMA_WRITE &&
			    opcode == TID_OP(WRITE_RESP)) अणु
				/*
				 * Normally, the loop above would correctly
				 * process all WQEs from s_acked onward and
				 * either complete them or check क्रम correct
				 * PSN sequencing.
				 * However, क्रम TID RDMA, due to pipelining,
				 * the response may not be क्रम the request at
				 * s_acked so the above look would just be
				 * skipped. This करोes not allow क्रम checking
				 * the PSN sequencing. It has to be करोne
				 * separately.
				 */
				अगर (cmp_psn(psn, qp->s_last_psn + 1)) अणु
					set_restart_qp(qp, rcd);
					जाओ bail_stop;
				पूर्ण
				/*
				 * If the psn is being resent, stop the
				 * resending.
				 */
				अगर (qp->s_cur != qp->s_tail &&
				    cmp_psn(qp->s_psn, psn) <= 0)
					update_qp_retry_state(qp, psn,
							      __w->psn,
							      __w->lpsn);
				अन्यथा अगर (--qpriv->pending_tid_w_resp)
					rvt_mod_retry_समयr(qp);
				अन्यथा
					rvt_stop_rc_समयrs(qp);
			पूर्ण अन्यथा अणु
				/*
				 * We are expecting more ACKs so
				 * mod the retry समयr.
				 */
				rvt_mod_retry_समयr(qp);
				/*
				 * We can stop re-sending the earlier packets
				 * and जारी with the next packet the
				 * receiver wants.
				 */
				अगर (cmp_psn(qp->s_psn, psn) <= 0)
					reset_psn(qp, psn + 1);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* No more acks - समाप्त all समयrs */
			rvt_stop_rc_समयrs(qp);
			अगर (cmp_psn(qp->s_psn, psn) <= 0) अणु
				qp->s_state = OP(SEND_LAST);
				qp->s_psn = psn + 1;
			पूर्ण
		पूर्ण
		अगर (qp->s_flags & RVT_S_WAIT_ACK) अणु
			qp->s_flags &= ~RVT_S_WAIT_ACK;
			hfi1_schedule_send(qp);
		पूर्ण
		rvt_get_credit(qp, aeth);
		qp->s_rnr_retry = qp->s_rnr_retry_cnt;
		qp->s_retry = qp->s_retry_cnt;
		/*
		 * If the current request is a TID RDMA WRITE request and the
		 * response is not a TID RDMA WRITE RESP packet, s_last_psn
		 * can't be advanced.
		 */
		अगर (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE &&
		    opcode != TID_OP(WRITE_RESP) &&
		    cmp_psn(psn, wqe->psn) >= 0)
			वापस 1;
		update_last_psn(qp, psn);
		वापस 1;

	हाल 1:         /* RNR NAK */
		ibp->rvp.n_rnr_naks++;
		अगर (qp->s_acked == qp->s_tail)
			जाओ bail_stop;
		अगर (qp->s_flags & RVT_S_WAIT_RNR)
			जाओ bail_stop;
		rdi = ib_to_rvt(qp->ibqp.device);
		अगर (!(rdi->post_parms[wqe->wr.opcode].flags &
		       RVT_OPERATION_IGN_RNR_CNT)) अणु
			अगर (qp->s_rnr_retry == 0) अणु
				status = IB_WC_RNR_RETRY_EXC_ERR;
				जाओ class_b;
			पूर्ण
			अगर (qp->s_rnr_retry_cnt < 7 && qp->s_rnr_retry_cnt > 0)
				qp->s_rnr_retry--;
		पूर्ण

		/*
		 * The last valid PSN is the previous PSN. For TID RDMA WRITE
		 * request, s_last_psn should be incremented only when a TID
		 * RDMA WRITE RESP is received to aव्योम skipping lost TID RDMA
		 * WRITE RESP packets.
		 */
		अगर (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE) अणु
			reset_psn(qp, qp->s_last_psn + 1);
		पूर्ण अन्यथा अणु
			update_last_psn(qp, psn - 1);
			reset_psn(qp, psn);
		पूर्ण

		ibp->rvp.n_rc_resends += delta_psn(qp->s_psn, psn);
		qp->s_flags &= ~(RVT_S_WAIT_SSN_CREDIT | RVT_S_WAIT_ACK);
		rvt_stop_rc_समयrs(qp);
		rvt_add_rnr_समयr(qp, aeth);
		वापस 0;

	हाल 3:         /* NAK */
		अगर (qp->s_acked == qp->s_tail)
			जाओ bail_stop;
		/* The last valid PSN is the previous PSN. */
		update_last_psn(qp, psn - 1);
		चयन ((aeth >> IB_AETH_CREDIT_SHIFT) &
			IB_AETH_CREDIT_MASK) अणु
		हाल 0: /* PSN sequence error */
			ibp->rvp.n_seq_naks++;
			/*
			 * Back up to the responder's expected PSN.
			 * Note that we might get a NAK in the middle of an
			 * RDMA READ response which terminates the RDMA
			 * READ.
			 */
			hfi1_restart_rc(qp, psn, 0);
			hfi1_schedule_send(qp);
			अवरोध;

		हाल 1: /* Invalid Request */
			status = IB_WC_REM_INV_REQ_ERR;
			ibp->rvp.n_other_naks++;
			जाओ class_b;

		हाल 2: /* Remote Access Error */
			status = IB_WC_REM_ACCESS_ERR;
			ibp->rvp.n_other_naks++;
			जाओ class_b;

		हाल 3: /* Remote Operation Error */
			status = IB_WC_REM_OP_ERR;
			ibp->rvp.n_other_naks++;
class_b:
			अगर (qp->s_last == qp->s_acked) अणु
				अगर (wqe->wr.opcode == IB_WR_TID_RDMA_READ)
					hfi1_kern_पढ़ो_tid_flow_मुक्त(qp);

				hfi1_trdma_send_complete(qp, wqe, status);
				rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);
			पूर्ण
			अवरोध;

		शेष:
			/* Ignore other reserved NAK error codes */
			जाओ reserved;
		पूर्ण
		qp->s_retry = qp->s_retry_cnt;
		qp->s_rnr_retry = qp->s_rnr_retry_cnt;
		जाओ bail_stop;

	शेष:                /* 2: reserved */
reserved:
		/* Ignore reserved NAK codes. */
		जाओ bail_stop;
	पूर्ण
	/* cannot be reached  */
bail_stop:
	rvt_stop_rc_समयrs(qp);
	वापस ret;
पूर्ण

/*
 * We have seen an out of sequence RDMA पढ़ो middle or last packet.
 * This ACKs SENDs and RDMA ग_लिखोs up to the first RDMA पढ़ो or atomic SWQE.
 */
अटल व्योम rdma_seq_err(काष्ठा rvt_qp *qp, काष्ठा hfi1_ibport *ibp, u32 psn,
			 काष्ठा hfi1_ctxtdata *rcd)
अणु
	काष्ठा rvt_swqe *wqe;

	lockdep_निश्चित_held(&qp->s_lock);
	/* Remove QP from retry समयr */
	rvt_stop_rc_समयrs(qp);

	wqe = rvt_get_swqe_ptr(qp, qp->s_acked);

	जबतक (cmp_psn(psn, wqe->lpsn) > 0) अणु
		अगर (wqe->wr.opcode == IB_WR_RDMA_READ ||
		    wqe->wr.opcode == IB_WR_TID_RDMA_READ ||
		    wqe->wr.opcode == IB_WR_TID_RDMA_WRITE ||
		    wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		    wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD)
			अवरोध;
		wqe = करो_rc_completion(qp, wqe, ibp);
	पूर्ण

	ibp->rvp.n_rdma_seq++;
	qp->r_flags |= RVT_R_RDMAR_SEQ;
	hfi1_restart_rc(qp, qp->s_last_psn + 1, 0);
	अगर (list_empty(&qp->rspरुको)) अणु
		qp->r_flags |= RVT_R_RSP_SEND;
		rvt_get_qp(qp);
		list_add_tail(&qp->rspरुको, &rcd->qp_रुको_list);
	पूर्ण
पूर्ण

/**
 * rc_rcv_resp - process an incoming RC response packet
 * @packet: data packet inक्रमmation
 *
 * This is called from hfi1_rc_rcv() to process an incoming RC response
 * packet क्रम the given QP.
 * Called at पूर्णांकerrupt level.
 */
अटल व्योम rc_rcv_resp(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	व्योम *data = packet->payload;
	u32 tlen = packet->tlen;
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_ibport *ibp;
	काष्ठा ib_other_headers *ohdr = packet->ohdr;
	काष्ठा rvt_swqe *wqe;
	क्रमागत ib_wc_status status;
	अचिन्हित दीर्घ flags;
	पूर्णांक dअगरf;
	u64 val;
	u32 aeth;
	u32 psn = ib_bth_get_psn(packet->ohdr);
	u32 pmtu = qp->pmtu;
	u16 hdrsize = packet->hlen;
	u8 opcode = packet->opcode;
	u8 pad = packet->pad;
	u8 extra_bytes = pad + packet->extra_byte + (SIZE_OF_CRC << 2);

	spin_lock_irqsave(&qp->s_lock, flags);
	trace_hfi1_ack(qp, psn);

	/* Ignore invalid responses. */
	अगर (cmp_psn(psn, READ_ONCE(qp->s_next_psn)) >= 0)
		जाओ ack_करोne;

	/* Ignore duplicate responses. */
	dअगरf = cmp_psn(psn, qp->s_last_psn);
	अगर (unlikely(dअगरf <= 0)) अणु
		/* Update credits क्रम "ghost" ACKs */
		अगर (dअगरf == 0 && opcode == OP(ACKNOWLEDGE)) अणु
			aeth = be32_to_cpu(ohdr->u.aeth);
			अगर ((aeth >> IB_AETH_NAK_SHIFT) == 0)
				rvt_get_credit(qp, aeth);
		पूर्ण
		जाओ ack_करोne;
	पूर्ण

	/*
	 * Skip everything other than the PSN we expect, अगर we are रुकोing
	 * क्रम a reply to a restarted RDMA पढ़ो or atomic op.
	 */
	अगर (qp->r_flags & RVT_R_RDMAR_SEQ) अणु
		अगर (cmp_psn(psn, qp->s_last_psn + 1) != 0)
			जाओ ack_करोne;
		qp->r_flags &= ~RVT_R_RDMAR_SEQ;
	पूर्ण

	अगर (unlikely(qp->s_acked == qp->s_tail))
		जाओ ack_करोne;
	wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
	status = IB_WC_SUCCESS;

	चयन (opcode) अणु
	हाल OP(ACKNOWLEDGE):
	हाल OP(ATOMIC_ACKNOWLEDGE):
	हाल OP(RDMA_READ_RESPONSE_FIRST):
		aeth = be32_to_cpu(ohdr->u.aeth);
		अगर (opcode == OP(ATOMIC_ACKNOWLEDGE))
			val = ib_u64_get(&ohdr->u.at.atomic_ack_eth);
		अन्यथा
			val = 0;
		अगर (!करो_rc_ack(qp, aeth, psn, opcode, val, rcd) ||
		    opcode != OP(RDMA_READ_RESPONSE_FIRST))
			जाओ ack_करोne;
		wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
		अगर (unlikely(wqe->wr.opcode != IB_WR_RDMA_READ))
			जाओ ack_op_err;
		/*
		 * If this is a response to a resent RDMA पढ़ो, we
		 * have to be careful to copy the data to the right
		 * location.
		 */
		qp->s_rdma_पढ़ो_len = restart_sge(&qp->s_rdma_पढ़ो_sge,
						  wqe, psn, pmtu);
		जाओ पढ़ो_middle;

	हाल OP(RDMA_READ_RESPONSE_MIDDLE):
		/* no AETH, no ACK */
		अगर (unlikely(cmp_psn(psn, qp->s_last_psn + 1)))
			जाओ ack_seq_err;
		अगर (unlikely(wqe->wr.opcode != IB_WR_RDMA_READ))
			जाओ ack_op_err;
पढ़ो_middle:
		अगर (unlikely(tlen != (hdrsize + pmtu + extra_bytes)))
			जाओ ack_len_err;
		अगर (unlikely(pmtu >= qp->s_rdma_पढ़ो_len))
			जाओ ack_len_err;

		/*
		 * We got a response so update the समयout.
		 * 4.096 usec. * (1 << qp->समयout)
		 */
		rvt_mod_retry_समयr(qp);
		अगर (qp->s_flags & RVT_S_WAIT_ACK) अणु
			qp->s_flags &= ~RVT_S_WAIT_ACK;
			hfi1_schedule_send(qp);
		पूर्ण

		अगर (opcode == OP(RDMA_READ_RESPONSE_MIDDLE))
			qp->s_retry = qp->s_retry_cnt;

		/*
		 * Update the RDMA receive state but करो the copy w/o
		 * holding the locks and blocking पूर्णांकerrupts.
		 */
		qp->s_rdma_पढ़ो_len -= pmtu;
		update_last_psn(qp, psn);
		spin_unlock_irqrestore(&qp->s_lock, flags);
		rvt_copy_sge(qp, &qp->s_rdma_पढ़ो_sge,
			     data, pmtu, false, false);
		जाओ bail;

	हाल OP(RDMA_READ_RESPONSE_ONLY):
		aeth = be32_to_cpu(ohdr->u.aeth);
		अगर (!करो_rc_ack(qp, aeth, psn, opcode, 0, rcd))
			जाओ ack_करोne;
		/*
		 * Check that the data size is >= 0 && <= pmtu.
		 * Remember to account क्रम ICRC (4).
		 */
		अगर (unlikely(tlen < (hdrsize + extra_bytes)))
			जाओ ack_len_err;
		/*
		 * If this is a response to a resent RDMA पढ़ो, we
		 * have to be careful to copy the data to the right
		 * location.
		 */
		wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
		qp->s_rdma_पढ़ो_len = restart_sge(&qp->s_rdma_पढ़ो_sge,
						  wqe, psn, pmtu);
		जाओ पढ़ो_last;

	हाल OP(RDMA_READ_RESPONSE_LAST):
		/* ACKs READ req. */
		अगर (unlikely(cmp_psn(psn, qp->s_last_psn + 1)))
			जाओ ack_seq_err;
		अगर (unlikely(wqe->wr.opcode != IB_WR_RDMA_READ))
			जाओ ack_op_err;
		/*
		 * Check that the data size is >= 1 && <= pmtu.
		 * Remember to account क्रम ICRC (4).
		 */
		अगर (unlikely(tlen <= (hdrsize + extra_bytes)))
			जाओ ack_len_err;
पढ़ो_last:
		tlen -= hdrsize + extra_bytes;
		अगर (unlikely(tlen != qp->s_rdma_पढ़ो_len))
			जाओ ack_len_err;
		aeth = be32_to_cpu(ohdr->u.aeth);
		rvt_copy_sge(qp, &qp->s_rdma_पढ़ो_sge,
			     data, tlen, false, false);
		WARN_ON(qp->s_rdma_पढ़ो_sge.num_sge);
		(व्योम)करो_rc_ack(qp, aeth, psn,
				 OP(RDMA_READ_RESPONSE_LAST), 0, rcd);
		जाओ ack_करोne;
	पूर्ण

ack_op_err:
	status = IB_WC_LOC_QP_OP_ERR;
	जाओ ack_err;

ack_seq_err:
	ibp = rcd_to_iport(rcd);
	rdma_seq_err(qp, ibp, psn, rcd);
	जाओ ack_करोne;

ack_len_err:
	status = IB_WC_LOC_LEN_ERR;
ack_err:
	अगर (qp->s_last == qp->s_acked) अणु
		rvt_send_complete(qp, wqe, status);
		rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);
	पूर्ण
ack_करोne:
	spin_unlock_irqrestore(&qp->s_lock, flags);
bail:
	वापस;
पूर्ण

अटल अंतरभूत व्योम rc_cancel_ack(काष्ठा rvt_qp *qp)
अणु
	qp->r_adefered = 0;
	अगर (list_empty(&qp->rspरुको))
		वापस;
	list_del_init(&qp->rspरुको);
	qp->r_flags &= ~RVT_R_RSP_NAK;
	rvt_put_qp(qp);
पूर्ण

/**
 * rc_rcv_error - process an incoming duplicate or error RC packet
 * @ohdr: the other headers क्रम this packet
 * @data: the packet data
 * @qp: the QP क्रम this packet
 * @opcode: the opcode क्रम this packet
 * @psn: the packet sequence number क्रम this packet
 * @dअगरf: the dअगरference between the PSN and the expected PSN
 * @rcd: the receive context
 *
 * This is called from hfi1_rc_rcv() to process an unexpected
 * incoming RC packet क्रम the given QP.
 * Called at पूर्णांकerrupt level.
 * Return 1 अगर no more processing is needed; otherwise वापस 0 to
 * schedule a response to be sent.
 */
अटल noअंतरभूत पूर्णांक rc_rcv_error(काष्ठा ib_other_headers *ohdr, व्योम *data,
				 काष्ठा rvt_qp *qp, u32 opcode, u32 psn,
				 पूर्णांक dअगरf, काष्ठा hfi1_ctxtdata *rcd)
अणु
	काष्ठा hfi1_ibport *ibp = rcd_to_iport(rcd);
	काष्ठा rvt_ack_entry *e;
	अचिन्हित दीर्घ flags;
	u8 prev;
	u8 mra; /* most recent ACK */
	bool old_req;

	trace_hfi1_rcv_error(qp, psn);
	अगर (dअगरf > 0) अणु
		/*
		 * Packet sequence error.
		 * A NAK will ACK earlier sends and RDMA ग_लिखोs.
		 * Don't queue the NAK अगर we alपढ़ोy sent one.
		 */
		अगर (!qp->r_nak_state) अणु
			ibp->rvp.n_rc_seqnak++;
			qp->r_nak_state = IB_NAK_PSN_ERROR;
			/* Use the expected PSN. */
			qp->r_ack_psn = qp->r_psn;
			/*
			 * Wait to send the sequence NAK until all packets
			 * in the receive queue have been processed.
			 * Otherwise, we end up propagating congestion.
			 */
			rc_defered_ack(rcd, qp);
		पूर्ण
		जाओ करोne;
	पूर्ण

	/*
	 * Handle a duplicate request.  Don't re-execute SEND, RDMA
	 * ग_लिखो or atomic op.  Don't NAK errors, just silently drop
	 * the duplicate request.  Note that r_sge, r_len, and
	 * r_rcv_len may be in use so करोn't modअगरy them.
	 *
	 * We are supposed to ACK the earliest duplicate PSN but we
	 * can coalesce an outstanding duplicate ACK.  We have to
	 * send the earliest so that RDMA पढ़ोs can be restarted at
	 * the requester's expected PSN.
	 *
	 * First, find where this duplicate PSN falls within the
	 * ACKs previously sent.
	 * old_req is true अगर there is an older response that is scheduled
	 * to be sent beक्रमe sending this one.
	 */
	e = शून्य;
	old_req = true;
	ibp->rvp.n_rc_dupreq++;

	spin_lock_irqsave(&qp->s_lock, flags);

	e = find_prev_entry(qp, psn, &prev, &mra, &old_req);

	चयन (opcode) अणु
	हाल OP(RDMA_READ_REQUEST): अणु
		काष्ठा ib_reth *reth;
		u32 offset;
		u32 len;

		/*
		 * If we didn't find the RDMA पढ़ो request in the ack queue,
		 * we can ignore this request.
		 */
		अगर (!e || e->opcode != OP(RDMA_READ_REQUEST))
			जाओ unlock_करोne;
		/* RETH comes after BTH */
		reth = &ohdr->u.rc.reth;
		/*
		 * Address range must be a subset of the original
		 * request and start on pmtu boundaries.
		 * We reuse the old ack_queue slot since the requester
		 * should not back up and request an earlier PSN क्रम the
		 * same request.
		 */
		offset = delta_psn(psn, e->psn) * qp->pmtu;
		len = be32_to_cpu(reth->length);
		अगर (unlikely(offset + len != e->rdma_sge.sge_length))
			जाओ unlock_करोne;
		release_rdma_sge_mr(e);
		अगर (len != 0) अणु
			u32 rkey = be32_to_cpu(reth->rkey);
			u64 vaddr = get_ib_reth_vaddr(reth);
			पूर्णांक ok;

			ok = rvt_rkey_ok(qp, &e->rdma_sge, len, vaddr, rkey,
					 IB_ACCESS_REMOTE_READ);
			अगर (unlikely(!ok))
				जाओ unlock_करोne;
		पूर्ण अन्यथा अणु
			e->rdma_sge.vaddr = शून्य;
			e->rdma_sge.length = 0;
			e->rdma_sge.sge_length = 0;
		पूर्ण
		e->psn = psn;
		अगर (old_req)
			जाओ unlock_करोne;
		अगर (qp->s_acked_ack_queue == qp->s_tail_ack_queue)
			qp->s_acked_ack_queue = prev;
		qp->s_tail_ack_queue = prev;
		अवरोध;
	पूर्ण

	हाल OP(COMPARE_SWAP):
	हाल OP(FETCH_ADD): अणु
		/*
		 * If we didn't find the atomic request in the ack queue
		 * or the send engine is alपढ़ोy backed up to send an
		 * earlier entry, we can ignore this request.
		 */
		अगर (!e || e->opcode != (u8)opcode || old_req)
			जाओ unlock_करोne;
		अगर (qp->s_tail_ack_queue == qp->s_acked_ack_queue)
			qp->s_acked_ack_queue = prev;
		qp->s_tail_ack_queue = prev;
		अवरोध;
	पूर्ण

	शेष:
		/*
		 * Ignore this operation अगर it करोesn't request an ACK
		 * or an earlier RDMA पढ़ो or atomic is going to be resent.
		 */
		अगर (!(psn & IB_BTH_REQ_ACK) || old_req)
			जाओ unlock_करोne;
		/*
		 * Resend the most recent ACK अगर this request is
		 * after all the previous RDMA पढ़ोs and atomics.
		 */
		अगर (mra == qp->r_head_ack_queue) अणु
			spin_unlock_irqrestore(&qp->s_lock, flags);
			qp->r_nak_state = 0;
			qp->r_ack_psn = qp->r_psn - 1;
			जाओ send_ack;
		पूर्ण

		/*
		 * Resend the RDMA पढ़ो or atomic op which
		 * ACKs this duplicate request.
		 */
		अगर (qp->s_tail_ack_queue == qp->s_acked_ack_queue)
			qp->s_acked_ack_queue = mra;
		qp->s_tail_ack_queue = mra;
		अवरोध;
	पूर्ण
	qp->s_ack_state = OP(ACKNOWLEDGE);
	qp->s_flags |= RVT_S_RESP_PENDING;
	qp->r_nak_state = 0;
	hfi1_schedule_send(qp);

unlock_करोne:
	spin_unlock_irqrestore(&qp->s_lock, flags);
करोne:
	वापस 1;

send_ack:
	वापस 0;
पूर्ण

अटल व्योम log_cca_event(काष्ठा hfi1_pportdata *ppd, u8 sl, u32 rlid,
			  u32 lqpn, u32 rqpn, u8 svc_type)
अणु
	काष्ठा opa_hfi1_cong_log_event_पूर्णांकernal *cc_event;
	अचिन्हित दीर्घ flags;

	अगर (sl >= OPA_MAX_SLS)
		वापस;

	spin_lock_irqsave(&ppd->cc_log_lock, flags);

	ppd->threshold_cong_event_map[sl / 8] |= 1 << (sl % 8);
	ppd->threshold_event_counter++;

	cc_event = &ppd->cc_events[ppd->cc_log_idx++];
	अगर (ppd->cc_log_idx == OPA_CONG_LOG_ELEMS)
		ppd->cc_log_idx = 0;
	cc_event->lqpn = lqpn & RVT_QPN_MASK;
	cc_event->rqpn = rqpn & RVT_QPN_MASK;
	cc_event->sl = sl;
	cc_event->svc_type = svc_type;
	cc_event->rlid = rlid;
	/* keep बारtamp in units of 1.024 usec */
	cc_event->बारtamp = kसमय_get_ns() / 1024;

	spin_unlock_irqrestore(&ppd->cc_log_lock, flags);
पूर्ण

व्योम process_becn(काष्ठा hfi1_pportdata *ppd, u8 sl, u32 rlid, u32 lqpn,
		  u32 rqpn, u8 svc_type)
अणु
	काष्ठा cca_समयr *cca_समयr;
	u16 ccti, ccti_incr, ccti_समयr, ccti_limit;
	u8 trigger_threshold;
	काष्ठा cc_state *cc_state;
	अचिन्हित दीर्घ flags;

	अगर (sl >= OPA_MAX_SLS)
		वापस;

	cc_state = get_cc_state(ppd);

	अगर (!cc_state)
		वापस;

	/*
	 * 1) increase CCTI (क्रम this SL)
	 * 2) select IPG (i.e., call set_link_ipg())
	 * 3) start समयr
	 */
	ccti_limit = cc_state->cct.ccti_limit;
	ccti_incr = cc_state->cong_setting.entries[sl].ccti_increase;
	ccti_समयr = cc_state->cong_setting.entries[sl].ccti_समयr;
	trigger_threshold =
		cc_state->cong_setting.entries[sl].trigger_threshold;

	spin_lock_irqsave(&ppd->cca_समयr_lock, flags);

	cca_समयr = &ppd->cca_समयr[sl];
	अगर (cca_समयr->ccti < ccti_limit) अणु
		अगर (cca_समयr->ccti + ccti_incr <= ccti_limit)
			cca_समयr->ccti += ccti_incr;
		अन्यथा
			cca_समयr->ccti = ccti_limit;
		set_link_ipg(ppd);
	पूर्ण

	ccti = cca_समयr->ccti;

	अगर (!hrसमयr_active(&cca_समयr->hrसमयr)) अणु
		/* ccti_समयr is in units of 1.024 usec */
		अचिन्हित दीर्घ nsec = 1024 * ccti_समयr;

		hrसमयr_start(&cca_समयr->hrसमयr, ns_to_kसमय(nsec),
			      HRTIMER_MODE_REL_PINNED);
	पूर्ण

	spin_unlock_irqrestore(&ppd->cca_समयr_lock, flags);

	अगर ((trigger_threshold != 0) && (ccti >= trigger_threshold))
		log_cca_event(ppd, sl, rlid, lqpn, rqpn, svc_type);
पूर्ण

/**
 * hfi1_rc_rcv - process an incoming RC packet
 * @packet: data packet inक्रमmation
 *
 * This is called from qp_rcv() to process an incoming RC packet
 * क्रम the given QP.
 * May be called at पूर्णांकerrupt level.
 */
व्योम hfi1_rc_rcv(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	व्योम *data = packet->payload;
	u32 tlen = packet->tlen;
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा hfi1_ibport *ibp = rcd_to_iport(rcd);
	काष्ठा ib_other_headers *ohdr = packet->ohdr;
	u32 opcode = packet->opcode;
	u32 hdrsize = packet->hlen;
	u32 psn = ib_bth_get_psn(packet->ohdr);
	u32 pad = packet->pad;
	काष्ठा ib_wc wc;
	u32 pmtu = qp->pmtu;
	पूर्णांक dअगरf;
	काष्ठा ib_reth *reth;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	bool copy_last = false, fecn;
	u32 rkey;
	u8 extra_bytes = pad + packet->extra_byte + (SIZE_OF_CRC << 2);

	lockdep_निश्चित_held(&qp->r_lock);

	अगर (hfi1_ruc_check_hdr(ibp, packet))
		वापस;

	fecn = process_ecn(qp, packet);
	opfn_trigger_conn_request(qp, be32_to_cpu(ohdr->bth[1]));

	/*
	 * Process responses (ACKs) beक्रमe anything अन्यथा.  Note that the
	 * packet sequence number will be क्रम something in the send work
	 * queue rather than the expected receive packet sequence number.
	 * In other words, this QP is the requester.
	 */
	अगर (opcode >= OP(RDMA_READ_RESPONSE_FIRST) &&
	    opcode <= OP(ATOMIC_ACKNOWLEDGE)) अणु
		rc_rcv_resp(packet);
		वापस;
	पूर्ण

	/* Compute 24 bits worth of dअगरference. */
	dअगरf = delta_psn(psn, qp->r_psn);
	अगर (unlikely(dअगरf)) अणु
		अगर (rc_rcv_error(ohdr, data, qp, opcode, psn, dअगरf, rcd))
			वापस;
		जाओ send_ack;
	पूर्ण

	/* Check क्रम opcode sequence errors. */
	चयन (qp->r_state) अणु
	हाल OP(SEND_FIRST):
	हाल OP(SEND_MIDDLE):
		अगर (opcode == OP(SEND_MIDDLE) ||
		    opcode == OP(SEND_LAST) ||
		    opcode == OP(SEND_LAST_WITH_IMMEDIATE) ||
		    opcode == OP(SEND_LAST_WITH_INVALIDATE))
			अवरोध;
		जाओ nack_inv;

	हाल OP(RDMA_WRITE_FIRST):
	हाल OP(RDMA_WRITE_MIDDLE):
		अगर (opcode == OP(RDMA_WRITE_MIDDLE) ||
		    opcode == OP(RDMA_WRITE_LAST) ||
		    opcode == OP(RDMA_WRITE_LAST_WITH_IMMEDIATE))
			अवरोध;
		जाओ nack_inv;

	शेष:
		अगर (opcode == OP(SEND_MIDDLE) ||
		    opcode == OP(SEND_LAST) ||
		    opcode == OP(SEND_LAST_WITH_IMMEDIATE) ||
		    opcode == OP(SEND_LAST_WITH_INVALIDATE) ||
		    opcode == OP(RDMA_WRITE_MIDDLE) ||
		    opcode == OP(RDMA_WRITE_LAST) ||
		    opcode == OP(RDMA_WRITE_LAST_WITH_IMMEDIATE))
			जाओ nack_inv;
		/*
		 * Note that it is up to the requester to not send a new
		 * RDMA पढ़ो or atomic operation beक्रमe receiving an ACK
		 * क्रम the previous operation.
		 */
		अवरोध;
	पूर्ण

	अगर (qp->state == IB_QPS_RTR && !(qp->r_flags & RVT_R_COMM_EST))
		rvt_comm_est(qp);

	/* OK, process the packet. */
	चयन (opcode) अणु
	हाल OP(SEND_FIRST):
		ret = rvt_get_rwqe(qp, false);
		अगर (ret < 0)
			जाओ nack_op_err;
		अगर (!ret)
			जाओ rnr_nak;
		qp->r_rcv_len = 0;
		fallthrough;
	हाल OP(SEND_MIDDLE):
	हाल OP(RDMA_WRITE_MIDDLE):
send_middle:
		/* Check क्रम invalid length PMTU or posted rwqe len. */
		/*
		 * There will be no padding क्रम 9B packet but 16B packets
		 * will come in with some padding since we always add
		 * CRC and LT bytes which will need to be flit aligned
		 */
		अगर (unlikely(tlen != (hdrsize + pmtu + extra_bytes)))
			जाओ nack_inv;
		qp->r_rcv_len += pmtu;
		अगर (unlikely(qp->r_rcv_len > qp->r_len))
			जाओ nack_inv;
		rvt_copy_sge(qp, &qp->r_sge, data, pmtu, true, false);
		अवरोध;

	हाल OP(RDMA_WRITE_LAST_WITH_IMMEDIATE):
		/* consume RWQE */
		ret = rvt_get_rwqe(qp, true);
		अगर (ret < 0)
			जाओ nack_op_err;
		अगर (!ret)
			जाओ rnr_nak;
		जाओ send_last_imm;

	हाल OP(SEND_ONLY):
	हाल OP(SEND_ONLY_WITH_IMMEDIATE):
	हाल OP(SEND_ONLY_WITH_INVALIDATE):
		ret = rvt_get_rwqe(qp, false);
		अगर (ret < 0)
			जाओ nack_op_err;
		अगर (!ret)
			जाओ rnr_nak;
		qp->r_rcv_len = 0;
		अगर (opcode == OP(SEND_ONLY))
			जाओ no_immediate_data;
		अगर (opcode == OP(SEND_ONLY_WITH_INVALIDATE))
			जाओ send_last_inv;
		fallthrough;	/* क्रम SEND_ONLY_WITH_IMMEDIATE */
	हाल OP(SEND_LAST_WITH_IMMEDIATE):
send_last_imm:
		wc.ex.imm_data = ohdr->u.imm_data;
		wc.wc_flags = IB_WC_WITH_IMM;
		जाओ send_last;
	हाल OP(SEND_LAST_WITH_INVALIDATE):
send_last_inv:
		rkey = be32_to_cpu(ohdr->u.ieth);
		अगर (rvt_invalidate_rkey(qp, rkey))
			जाओ no_immediate_data;
		wc.ex.invalidate_rkey = rkey;
		wc.wc_flags = IB_WC_WITH_INVALIDATE;
		जाओ send_last;
	हाल OP(RDMA_WRITE_LAST):
		copy_last = rvt_is_user_qp(qp);
		fallthrough;
	हाल OP(SEND_LAST):
no_immediate_data:
		wc.wc_flags = 0;
		wc.ex.imm_data = 0;
send_last:
		/* Check क्रम invalid length. */
		/* LAST len should be >= 1 */
		अगर (unlikely(tlen < (hdrsize + extra_bytes)))
			जाओ nack_inv;
		/* Don't count the CRC(and padding and LT byte क्रम 16B). */
		tlen -= (hdrsize + extra_bytes);
		wc.byte_len = tlen + qp->r_rcv_len;
		अगर (unlikely(wc.byte_len > qp->r_len))
			जाओ nack_inv;
		rvt_copy_sge(qp, &qp->r_sge, data, tlen, true, copy_last);
		rvt_put_ss(&qp->r_sge);
		qp->r_msn++;
		अगर (!__test_and_clear_bit(RVT_R_WRID_VALID, &qp->r_aflags))
			अवरोध;
		wc.wr_id = qp->r_wr_id;
		wc.status = IB_WC_SUCCESS;
		अगर (opcode == OP(RDMA_WRITE_LAST_WITH_IMMEDIATE) ||
		    opcode == OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE))
			wc.opcode = IB_WC_RECV_RDMA_WITH_IMM;
		अन्यथा
			wc.opcode = IB_WC_RECV;
		wc.qp = &qp->ibqp;
		wc.src_qp = qp->remote_qpn;
		wc.slid = rdma_ah_get_dlid(&qp->remote_ah_attr) & U16_MAX;
		/*
		 * It seems that IB mandates the presence of an SL in a
		 * work completion only क्रम the UD transport (see section
		 * 11.4.2 of IBTA Vol. 1).
		 *
		 * However, the way the SL is chosen below is consistent
		 * with the way that IB/qib works and is trying aव्योम
		 * पूर्णांकroducing incompatibilities.
		 *
		 * See also OPA Vol. 1, section 9.7.6, and table 9-17.
		 */
		wc.sl = rdma_ah_get_sl(&qp->remote_ah_attr);
		/* zero fields that are N/A */
		wc.venकरोr_err = 0;
		wc.pkey_index = 0;
		wc.dlid_path_bits = 0;
		wc.port_num = 0;
		/* Signal completion event अगर the solicited bit is set. */
		rvt_recv_cq(qp, &wc, ib_bth_is_solicited(ohdr));
		अवरोध;

	हाल OP(RDMA_WRITE_ONLY):
		copy_last = rvt_is_user_qp(qp);
		fallthrough;
	हाल OP(RDMA_WRITE_FIRST):
	हाल OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE):
		अगर (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_WRITE)))
			जाओ nack_inv;
		/* consume RWQE */
		reth = &ohdr->u.rc.reth;
		qp->r_len = be32_to_cpu(reth->length);
		qp->r_rcv_len = 0;
		qp->r_sge.sg_list = शून्य;
		अगर (qp->r_len != 0) अणु
			u32 rkey = be32_to_cpu(reth->rkey);
			u64 vaddr = get_ib_reth_vaddr(reth);
			पूर्णांक ok;

			/* Check rkey & NAK */
			ok = rvt_rkey_ok(qp, &qp->r_sge.sge, qp->r_len, vaddr,
					 rkey, IB_ACCESS_REMOTE_WRITE);
			अगर (unlikely(!ok))
				जाओ nack_acc;
			qp->r_sge.num_sge = 1;
		पूर्ण अन्यथा अणु
			qp->r_sge.num_sge = 0;
			qp->r_sge.sge.mr = शून्य;
			qp->r_sge.sge.vaddr = शून्य;
			qp->r_sge.sge.length = 0;
			qp->r_sge.sge.sge_length = 0;
		पूर्ण
		अगर (opcode == OP(RDMA_WRITE_FIRST))
			जाओ send_middle;
		अन्यथा अगर (opcode == OP(RDMA_WRITE_ONLY))
			जाओ no_immediate_data;
		ret = rvt_get_rwqe(qp, true);
		अगर (ret < 0)
			जाओ nack_op_err;
		अगर (!ret) अणु
			/* peer will send again */
			rvt_put_ss(&qp->r_sge);
			जाओ rnr_nak;
		पूर्ण
		wc.ex.imm_data = ohdr->u.rc.imm_data;
		wc.wc_flags = IB_WC_WITH_IMM;
		जाओ send_last;

	हाल OP(RDMA_READ_REQUEST): अणु
		काष्ठा rvt_ack_entry *e;
		u32 len;
		u8 next;

		अगर (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_READ)))
			जाओ nack_inv;
		next = qp->r_head_ack_queue + 1;
		/* s_ack_queue is size rvt_size_atomic()+1 so use > not >= */
		अगर (next > rvt_size_atomic(ib_to_rvt(qp->ibqp.device)))
			next = 0;
		spin_lock_irqsave(&qp->s_lock, flags);
		अगर (unlikely(next == qp->s_acked_ack_queue)) अणु
			अगर (!qp->s_ack_queue[next].sent)
				जाओ nack_inv_unlck;
			update_ack_queue(qp, next);
		पूर्ण
		e = &qp->s_ack_queue[qp->r_head_ack_queue];
		release_rdma_sge_mr(e);
		reth = &ohdr->u.rc.reth;
		len = be32_to_cpu(reth->length);
		अगर (len) अणु
			u32 rkey = be32_to_cpu(reth->rkey);
			u64 vaddr = get_ib_reth_vaddr(reth);
			पूर्णांक ok;

			/* Check rkey & NAK */
			ok = rvt_rkey_ok(qp, &e->rdma_sge, len, vaddr,
					 rkey, IB_ACCESS_REMOTE_READ);
			अगर (unlikely(!ok))
				जाओ nack_acc_unlck;
			/*
			 * Update the next expected PSN.  We add 1 later
			 * below, so only add the reमुख्यder here.
			 */
			qp->r_psn += rvt_भाग_mtu(qp, len - 1);
		पूर्ण अन्यथा अणु
			e->rdma_sge.mr = शून्य;
			e->rdma_sge.vaddr = शून्य;
			e->rdma_sge.length = 0;
			e->rdma_sge.sge_length = 0;
		पूर्ण
		e->opcode = opcode;
		e->sent = 0;
		e->psn = psn;
		e->lpsn = qp->r_psn;
		/*
		 * We need to increment the MSN here instead of when we
		 * finish sending the result since a duplicate request would
		 * increment it more than once.
		 */
		qp->r_msn++;
		qp->r_psn++;
		qp->r_state = opcode;
		qp->r_nak_state = 0;
		qp->r_head_ack_queue = next;
		qpriv->r_tid_alloc = qp->r_head_ack_queue;

		/* Schedule the send engine. */
		qp->s_flags |= RVT_S_RESP_PENDING;
		अगर (fecn)
			qp->s_flags |= RVT_S_ECN;
		hfi1_schedule_send(qp);

		spin_unlock_irqrestore(&qp->s_lock, flags);
		वापस;
	पूर्ण

	हाल OP(COMPARE_SWAP):
	हाल OP(FETCH_ADD): अणु
		काष्ठा ib_atomic_eth *ateth = &ohdr->u.atomic_eth;
		u64 vaddr = get_ib_ateth_vaddr(ateth);
		bool opfn = opcode == OP(COMPARE_SWAP) &&
			vaddr == HFI1_VERBS_E_ATOMIC_VADDR;
		काष्ठा rvt_ack_entry *e;
		atomic64_t *maddr;
		u64 sdata;
		u32 rkey;
		u8 next;

		अगर (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_ATOMIC) &&
			     !opfn))
			जाओ nack_inv;
		next = qp->r_head_ack_queue + 1;
		अगर (next > rvt_size_atomic(ib_to_rvt(qp->ibqp.device)))
			next = 0;
		spin_lock_irqsave(&qp->s_lock, flags);
		अगर (unlikely(next == qp->s_acked_ack_queue)) अणु
			अगर (!qp->s_ack_queue[next].sent)
				जाओ nack_inv_unlck;
			update_ack_queue(qp, next);
		पूर्ण
		e = &qp->s_ack_queue[qp->r_head_ack_queue];
		release_rdma_sge_mr(e);
		/* Process OPFN special भव address */
		अगर (opfn) अणु
			opfn_conn_response(qp, e, ateth);
			जाओ ack;
		पूर्ण
		अगर (unlikely(vaddr & (माप(u64) - 1)))
			जाओ nack_inv_unlck;
		rkey = be32_to_cpu(ateth->rkey);
		/* Check rkey & NAK */
		अगर (unlikely(!rvt_rkey_ok(qp, &qp->r_sge.sge, माप(u64),
					  vaddr, rkey,
					  IB_ACCESS_REMOTE_ATOMIC)))
			जाओ nack_acc_unlck;
		/* Perक्रमm atomic OP and save result. */
		maddr = (atomic64_t *)qp->r_sge.sge.vaddr;
		sdata = get_ib_ateth_swap(ateth);
		e->atomic_data = (opcode == OP(FETCH_ADD)) ?
			(u64)atomic64_add_वापस(sdata, maddr) - sdata :
			(u64)cmpxchg((u64 *)qp->r_sge.sge.vaddr,
				      get_ib_ateth_compare(ateth),
				      sdata);
		rvt_put_mr(qp->r_sge.sge.mr);
		qp->r_sge.num_sge = 0;
ack:
		e->opcode = opcode;
		e->sent = 0;
		e->psn = psn;
		e->lpsn = psn;
		qp->r_msn++;
		qp->r_psn++;
		qp->r_state = opcode;
		qp->r_nak_state = 0;
		qp->r_head_ack_queue = next;
		qpriv->r_tid_alloc = qp->r_head_ack_queue;

		/* Schedule the send engine. */
		qp->s_flags |= RVT_S_RESP_PENDING;
		अगर (fecn)
			qp->s_flags |= RVT_S_ECN;
		hfi1_schedule_send(qp);

		spin_unlock_irqrestore(&qp->s_lock, flags);
		वापस;
	पूर्ण

	शेष:
		/* NAK unknown opcodes. */
		जाओ nack_inv;
	पूर्ण
	qp->r_psn++;
	qp->r_state = opcode;
	qp->r_ack_psn = psn;
	qp->r_nak_state = 0;
	/* Send an ACK अगर requested or required. */
	अगर (psn & IB_BTH_REQ_ACK || fecn) अणु
		अगर (packet->numpkt == 0 || fecn ||
		    qp->r_adefered >= HFI1_PSN_CREDIT) अणु
			rc_cancel_ack(qp);
			जाओ send_ack;
		पूर्ण
		qp->r_adefered++;
		rc_defered_ack(rcd, qp);
	पूर्ण
	वापस;

rnr_nak:
	qp->r_nak_state = qp->r_min_rnr_समयr | IB_RNR_NAK;
	qp->r_ack_psn = qp->r_psn;
	/* Queue RNR NAK क्रम later */
	rc_defered_ack(rcd, qp);
	वापस;

nack_op_err:
	rvt_rc_error(qp, IB_WC_LOC_QP_OP_ERR);
	qp->r_nak_state = IB_NAK_REMOTE_OPERATIONAL_ERROR;
	qp->r_ack_psn = qp->r_psn;
	/* Queue NAK क्रम later */
	rc_defered_ack(rcd, qp);
	वापस;

nack_inv_unlck:
	spin_unlock_irqrestore(&qp->s_lock, flags);
nack_inv:
	rvt_rc_error(qp, IB_WC_LOC_QP_OP_ERR);
	qp->r_nak_state = IB_NAK_INVALID_REQUEST;
	qp->r_ack_psn = qp->r_psn;
	/* Queue NAK क्रम later */
	rc_defered_ack(rcd, qp);
	वापस;

nack_acc_unlck:
	spin_unlock_irqrestore(&qp->s_lock, flags);
nack_acc:
	rvt_rc_error(qp, IB_WC_LOC_PROT_ERR);
	qp->r_nak_state = IB_NAK_REMOTE_ACCESS_ERROR;
	qp->r_ack_psn = qp->r_psn;
send_ack:
	hfi1_send_rc_ack(packet, fecn);
पूर्ण

व्योम hfi1_rc_hdrerr(
	काष्ठा hfi1_ctxtdata *rcd,
	काष्ठा hfi1_packet *packet,
	काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_ibport *ibp = rcd_to_iport(rcd);
	पूर्णांक dअगरf;
	u32 opcode;
	u32 psn;

	अगर (hfi1_ruc_check_hdr(ibp, packet))
		वापस;

	psn = ib_bth_get_psn(packet->ohdr);
	opcode = ib_bth_get_opcode(packet->ohdr);

	/* Only deal with RDMA Writes क्रम now */
	अगर (opcode < IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST) अणु
		dअगरf = delta_psn(psn, qp->r_psn);
		अगर (!qp->r_nak_state && dअगरf >= 0) अणु
			ibp->rvp.n_rc_seqnak++;
			qp->r_nak_state = IB_NAK_PSN_ERROR;
			/* Use the expected PSN. */
			qp->r_ack_psn = qp->r_psn;
			/*
			 * Wait to send the sequence
			 * NAK until all packets
			 * in the receive queue have
			 * been processed.
			 * Otherwise, we end up
			 * propagating congestion.
			 */
			rc_defered_ack(rcd, qp);
		पूर्ण /* Out of sequence NAK */
	पूर्ण /* QP Request NAKs */
पूर्ण
