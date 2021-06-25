<शैली गुरु>
/*
 * Copyright (c) 2006, 2007, 2008, 2009 QLogic Corporation. All rights reserved.
 * Copyright (c) 2005, 2006 PathScale, Inc. All rights reserved.
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

#समावेश <linux/पन.स>

#समावेश "qib.h"

/* cut करोwn ridiculously दीर्घ IB macro names */
#घोषणा OP(x) IB_OPCODE_RC_##x


अटल u32 restart_sge(काष्ठा rvt_sge_state *ss, काष्ठा rvt_swqe *wqe,
		       u32 psn, u32 pmtu)
अणु
	u32 len;

	len = ((psn - wqe->psn) & QIB_PSN_MASK) * pmtu;
	वापस rvt_restart_sge(ss, wqe, len);
पूर्ण

/**
 * qib_make_rc_ack - स्थिरruct a response packet (ACK, NAK, or RDMA पढ़ो)
 * @dev: the device क्रम this QP
 * @qp: a poपूर्णांकer to the QP
 * @ohdr: a poपूर्णांकer to the IB header being स्थिरructed
 * @pmtu: the path MTU
 *
 * Return 1 अगर स्थिरructed; otherwise, वापस 0.
 * Note that we are in the responder's side of the QP context.
 * Note the QP s_lock must be held.
 */
अटल पूर्णांक qib_make_rc_ack(काष्ठा qib_ibdev *dev, काष्ठा rvt_qp *qp,
			   काष्ठा ib_other_headers *ohdr, u32 pmtu)
अणु
	काष्ठा rvt_ack_entry *e;
	u32 hwords;
	u32 len;
	u32 bth0;
	u32 bth2;

	/* Don't send an ACK if we aren't supposed to. */
	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK))
		जाओ bail;

	/* header size in 32-bit words LRH+BTH = (8+12)/4. */
	hwords = 5;

	चयन (qp->s_ack_state) अणु
	हाल OP(RDMA_READ_RESPONSE_LAST):
	हाल OP(RDMA_READ_RESPONSE_ONLY):
		e = &qp->s_ack_queue[qp->s_tail_ack_queue];
		अगर (e->rdma_sge.mr) अणु
			rvt_put_mr(e->rdma_sge.mr);
			e->rdma_sge.mr = शून्य;
		पूर्ण
		fallthrough;
	हाल OP(ATOMIC_ACKNOWLEDGE):
		/*
		 * We can increment the tail poपूर्णांकer now that the last
		 * response has been sent instead of only being
		 * स्थिरructed.
		 */
		अगर (++qp->s_tail_ack_queue > QIB_MAX_RDMA_ATOMIC)
			qp->s_tail_ack_queue = 0;
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
		अगर (e->opcode == OP(RDMA_READ_REQUEST)) अणु
			/*
			 * If a RDMA पढ़ो response is being resent and
			 * we haven't seen the duplicate request yet,
			 * then stop sending the reमुख्यing responses the
			 * responder has seen until the requester resends it.
			 */
			len = e->rdma_sge.sge_length;
			अगर (len && !e->rdma_sge.mr) अणु
				qp->s_tail_ack_queue = qp->r_head_ack_queue;
				जाओ bail;
			पूर्ण
			/* Copy SGE state in हाल we need to resend */
			qp->s_rdma_mr = e->rdma_sge.mr;
			अगर (qp->s_rdma_mr)
				rvt_get_mr(qp->s_rdma_mr);
			qp->s_ack_rdma_sge.sge = e->rdma_sge;
			qp->s_ack_rdma_sge.num_sge = 1;
			qp->s_cur_sge = &qp->s_ack_rdma_sge;
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
			bth2 = qp->s_ack_rdma_psn++ & QIB_PSN_MASK;
		पूर्ण अन्यथा अणु
			/* COMPARE_SWAP or FETCH_ADD */
			qp->s_cur_sge = शून्य;
			len = 0;
			qp->s_ack_state = OP(ATOMIC_ACKNOWLEDGE);
			ohdr->u.at.aeth = rvt_compute_aeth(qp);
			ib_u64_put(e->atomic_data, &ohdr->u.at.atomic_ack_eth);
			hwords += माप(ohdr->u.at) / माप(u32);
			bth2 = e->psn & QIB_PSN_MASK;
			e->sent = 1;
		पूर्ण
		bth0 = qp->s_ack_state << 24;
		अवरोध;

	हाल OP(RDMA_READ_RESPONSE_FIRST):
		qp->s_ack_state = OP(RDMA_READ_RESPONSE_MIDDLE);
		fallthrough;
	हाल OP(RDMA_READ_RESPONSE_MIDDLE):
		qp->s_cur_sge = &qp->s_ack_rdma_sge;
		qp->s_rdma_mr = qp->s_ack_rdma_sge.sge.mr;
		अगर (qp->s_rdma_mr)
			rvt_get_mr(qp->s_rdma_mr);
		len = qp->s_ack_rdma_sge.sge.sge_length;
		अगर (len > pmtu)
			len = pmtu;
		अन्यथा अणु
			ohdr->u.aeth = rvt_compute_aeth(qp);
			hwords++;
			qp->s_ack_state = OP(RDMA_READ_RESPONSE_LAST);
			e = &qp->s_ack_queue[qp->s_tail_ack_queue];
			e->sent = 1;
		पूर्ण
		bth0 = qp->s_ack_state << 24;
		bth2 = qp->s_ack_rdma_psn++ & QIB_PSN_MASK;
		अवरोध;

	शेष:
normal:
		/*
		 * Send a regular ACK.
		 * Set the s_ack_state so we रुको until after sending
		 * the ACK beक्रमe setting s_ack_state to ACKNOWLEDGE
		 * (see above).
		 */
		qp->s_ack_state = OP(SEND_ONLY);
		qp->s_flags &= ~RVT_S_ACK_PENDING;
		qp->s_cur_sge = शून्य;
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
		bth2 = qp->s_ack_psn & QIB_PSN_MASK;
	पूर्ण
	qp->s_rdma_ack_cnt++;
	qp->s_hdrwords = hwords;
	qp->s_cur_size = len;
	qib_make_ruc_header(qp, ohdr, bth0, bth2);
	वापस 1;

bail:
	qp->s_ack_state = OP(ACKNOWLEDGE);
	qp->s_flags &= ~(RVT_S_RESP_PENDING | RVT_S_ACK_PENDING);
	वापस 0;
पूर्ण

/**
 * qib_make_rc_req - स्थिरruct a request packet (SEND, RDMA r/w, ATOMIC)
 * @qp: a poपूर्णांकer to the QP
 * @flags: unused
 *
 * Assumes the s_lock is held.
 *
 * Return 1 अगर स्थिरructed; otherwise, वापस 0.
 */
पूर्णांक qib_make_rc_req(काष्ठा rvt_qp *qp, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;
	काष्ठा qib_ibdev *dev = to_idev(qp->ibqp.device);
	काष्ठा ib_other_headers *ohdr;
	काष्ठा rvt_sge_state *ss;
	काष्ठा rvt_swqe *wqe;
	u32 hwords;
	u32 len;
	u32 bth0;
	u32 bth2;
	u32 pmtu = qp->pmtu;
	अक्षर newreq;
	पूर्णांक ret = 0;
	पूर्णांक delta;

	ohdr = &priv->s_hdr->u.oth;
	अगर (rdma_ah_get_ah_flags(&qp->remote_ah_attr) & IB_AH_GRH)
		ohdr = &priv->s_hdr->u.l.oth;

	/* Sending responses has higher priority over sending requests. */
	अगर ((qp->s_flags & RVT_S_RESP_PENDING) &&
	    qib_make_rc_ack(dev, qp, ohdr, pmtu))
		जाओ करोne;

	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_SEND_OK)) अणु
		अगर (!(ib_rvt_state_ops[qp->state] & RVT_FLUSH_SEND))
			जाओ bail;
		/* We are in the error state, flush the work request. */
		अगर (qp->s_last == READ_ONCE(qp->s_head))
			जाओ bail;
		/* If DMAs are in progress, we can't flush immediately. */
		अगर (atomic_पढ़ो(&priv->s_dma_busy)) अणु
			qp->s_flags |= RVT_S_WAIT_DMA;
			जाओ bail;
		पूर्ण
		wqe = rvt_get_swqe_ptr(qp, qp->s_last);
		rvt_send_complete(qp, wqe, qp->s_last != qp->s_acked ?
			IB_WC_SUCCESS : IB_WC_WR_FLUSH_ERR);
		/* will get called again */
		जाओ करोne;
	पूर्ण

	अगर (qp->s_flags & (RVT_S_WAIT_RNR | RVT_S_WAIT_ACK))
		जाओ bail;

	अगर (qib_cmp24(qp->s_psn, qp->s_sending_hpsn) <= 0) अणु
		अगर (qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) <= 0) अणु
			qp->s_flags |= RVT_S_WAIT_PSN;
			जाओ bail;
		पूर्ण
		qp->s_sending_psn = qp->s_psn;
		qp->s_sending_hpsn = qp->s_psn - 1;
	पूर्ण

	/* header size in 32-bit words LRH+BTH = (8+12)/4. */
	hwords = 5;
	bth0 = 0;

	/* Send a request. */
	wqe = rvt_get_swqe_ptr(qp, qp->s_cur);
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
			अगर (qp->s_tail == READ_ONCE(qp->s_head))
				जाओ bail;
			/*
			 * If a fence is requested, रुको क्रम previous
			 * RDMA पढ़ो and atomic operations to finish.
			 */
			अगर ((wqe->wr.send_flags & IB_SEND_FENCE) &&
			    qp->s_num_rd_atomic) अणु
				qp->s_flags |= RVT_S_WAIT_FENCE;
				जाओ bail;
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
		bth2 = qp->s_psn & QIB_PSN_MASK;
		चयन (wqe->wr.opcode) अणु
		हाल IB_WR_SEND:
		हाल IB_WR_SEND_WITH_IMM:
			/* If no credit, वापस. */
			अगर (!rvt_rc_credit_avail(qp, wqe))
				जाओ bail;
			अगर (len > pmtu) अणु
				qp->s_state = OP(SEND_FIRST);
				len = pmtu;
				अवरोध;
			पूर्ण
			अगर (wqe->wr.opcode == IB_WR_SEND)
				qp->s_state = OP(SEND_ONLY);
			अन्यथा अणु
				qp->s_state = OP(SEND_ONLY_WITH_IMMEDIATE);
				/* Immediate data comes after the BTH */
				ohdr->u.imm_data = wqe->wr.ex.imm_data;
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
			ohdr->u.rc.reth.vaddr =
				cpu_to_be64(wqe->rdma_wr.remote_addr);
			ohdr->u.rc.reth.rkey =
				cpu_to_be32(wqe->rdma_wr.rkey);
			ohdr->u.rc.reth.length = cpu_to_be32(len);
			hwords += माप(काष्ठा ib_reth) / माप(u32);
			अगर (len > pmtu) अणु
				qp->s_state = OP(RDMA_WRITE_FIRST);
				len = pmtu;
				अवरोध;
			पूर्ण
			अगर (wqe->rdma_wr.wr.opcode == IB_WR_RDMA_WRITE)
				qp->s_state = OP(RDMA_WRITE_ONLY);
			अन्यथा अणु
				qp->s_state = OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE);
				/* Immediate data comes after RETH */
				ohdr->u.rc.imm_data =
					wqe->rdma_wr.wr.ex.imm_data;
				hwords += 1;
				अगर (wqe->rdma_wr.wr.send_flags & IB_SEND_SOLICITED)
					bth0 |= IB_BTH_SOLICITED;
			पूर्ण
			bth2 |= IB_BTH_REQ_ACK;
			अगर (++qp->s_cur == qp->s_size)
				qp->s_cur = 0;
			अवरोध;

		हाल IB_WR_RDMA_READ:
			/*
			 * Don't allow more operations to be started
			 * than the QP limits allow.
			 */
			अगर (newreq) अणु
				अगर (qp->s_num_rd_atomic >=
				    qp->s_max_rd_atomic) अणु
					qp->s_flags |= RVT_S_WAIT_RDMAR;
					जाओ bail;
				पूर्ण
				qp->s_num_rd_atomic++;
				अगर (!(qp->s_flags & RVT_S_UNLIMITED_CREDIT))
					qp->s_lsn++;
			पूर्ण

			ohdr->u.rc.reth.vaddr =
				cpu_to_be64(wqe->rdma_wr.remote_addr);
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

		हाल IB_WR_ATOMIC_CMP_AND_SWP:
		हाल IB_WR_ATOMIC_FETCH_AND_ADD:
			/*
			 * Don't allow more operations to be started
			 * than the QP limits allow.
			 */
			अगर (newreq) अणु
				अगर (qp->s_num_rd_atomic >=
				    qp->s_max_rd_atomic) अणु
					qp->s_flags |= RVT_S_WAIT_RDMAR;
					जाओ bail;
				पूर्ण
				qp->s_num_rd_atomic++;
				अगर (!(qp->s_flags & RVT_S_UNLIMITED_CREDIT))
					qp->s_lsn++;
			पूर्ण
			अगर (wqe->atomic_wr.wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP) अणु
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
		qp->s_sge.sge = wqe->sg_list[0];
		qp->s_sge.sg_list = wqe->sg_list + 1;
		qp->s_sge.num_sge = wqe->wr.num_sge;
		qp->s_sge.total_len = wqe->length;
		qp->s_len = wqe->length;
		अगर (newreq) अणु
			qp->s_tail++;
			अगर (qp->s_tail >= qp->s_size)
				qp->s_tail = 0;
		पूर्ण
		अगर (wqe->wr.opcode == IB_WR_RDMA_READ)
			qp->s_psn = wqe->lpsn + 1;
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
		 * earlier PSN without पूर्णांकerferring with the sending thपढ़ो.
		 * See qib_restart_rc().
		 */
		qp->s_len = restart_sge(&qp->s_sge, wqe, qp->s_psn, pmtu);
		fallthrough;
	हाल OP(SEND_FIRST):
		qp->s_state = OP(SEND_MIDDLE);
		fallthrough;
	हाल OP(SEND_MIDDLE):
		bth2 = qp->s_psn++ & QIB_PSN_MASK;
		ss = &qp->s_sge;
		len = qp->s_len;
		अगर (len > pmtu) अणु
			len = pmtu;
			अवरोध;
		पूर्ण
		अगर (wqe->wr.opcode == IB_WR_SEND)
			qp->s_state = OP(SEND_LAST);
		अन्यथा अणु
			qp->s_state = OP(SEND_LAST_WITH_IMMEDIATE);
			/* Immediate data comes after the BTH */
			ohdr->u.imm_data = wqe->wr.ex.imm_data;
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
		 * an earlier PSN without पूर्णांकerferring with the sending thपढ़ो.
		 * See qib_restart_rc().
		 */
		qp->s_len = restart_sge(&qp->s_sge, wqe, qp->s_psn, pmtu);
		fallthrough;
	हाल OP(RDMA_WRITE_FIRST):
		qp->s_state = OP(RDMA_WRITE_MIDDLE);
		fallthrough;
	हाल OP(RDMA_WRITE_MIDDLE):
		bth2 = qp->s_psn++ & QIB_PSN_MASK;
		ss = &qp->s_sge;
		len = qp->s_len;
		अगर (len > pmtu) अणु
			len = pmtu;
			अवरोध;
		पूर्ण
		अगर (wqe->wr.opcode == IB_WR_RDMA_WRITE)
			qp->s_state = OP(RDMA_WRITE_LAST);
		अन्यथा अणु
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
		 * an earlier PSN without पूर्णांकerferring with the sending thपढ़ो.
		 * See qib_restart_rc().
		 */
		len = ((qp->s_psn - wqe->psn) & QIB_PSN_MASK) * pmtu;
		ohdr->u.rc.reth.vaddr =
			cpu_to_be64(wqe->rdma_wr.remote_addr + len);
		ohdr->u.rc.reth.rkey =
			cpu_to_be32(wqe->rdma_wr.rkey);
		ohdr->u.rc.reth.length = cpu_to_be32(wqe->length - len);
		qp->s_state = OP(RDMA_READ_REQUEST);
		hwords += माप(ohdr->u.rc.reth) / माप(u32);
		bth2 = (qp->s_psn & QIB_PSN_MASK) | IB_BTH_REQ_ACK;
		qp->s_psn = wqe->lpsn + 1;
		ss = शून्य;
		len = 0;
		qp->s_cur++;
		अगर (qp->s_cur == qp->s_size)
			qp->s_cur = 0;
		अवरोध;
	पूर्ण
	qp->s_sending_hpsn = bth2;
	delta = (((पूर्णांक) bth2 - (पूर्णांक) wqe->psn) << 8) >> 8;
	अगर (delta && delta % QIB_PSN_CREDIT == 0)
		bth2 |= IB_BTH_REQ_ACK;
	अगर (qp->s_flags & RVT_S_SEND_ONE) अणु
		qp->s_flags &= ~RVT_S_SEND_ONE;
		qp->s_flags |= RVT_S_WAIT_ACK;
		bth2 |= IB_BTH_REQ_ACK;
	पूर्ण
	qp->s_len -= len;
	qp->s_hdrwords = hwords;
	qp->s_cur_sge = ss;
	qp->s_cur_size = len;
	qib_make_ruc_header(qp, ohdr, bth0 | (qp->s_state << 24), bth2);
करोne:
	वापस 1;
bail:
	qp->s_flags &= ~RVT_S_BUSY;
	वापस ret;
पूर्ण

/**
 * qib_send_rc_ack - Conकाष्ठा an ACK packet and send it
 * @qp: a poपूर्णांकer to the QP
 *
 * This is called from qib_rc_rcv() and qib_kreceive().
 * Note that RDMA पढ़ोs and atomics are handled in the
 * send side QP state and tasklet.
 */
व्योम qib_send_rc_ack(काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_devdata *dd = dd_from_ibdev(qp->ibqp.device);
	काष्ठा qib_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	u64 pbc;
	u16 lrh0;
	u32 bth0;
	u32 hwords;
	u32 pbufn;
	u32 __iomem *piobuf;
	काष्ठा ib_header hdr;
	काष्ठा ib_other_headers *ohdr;
	u32 control;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->s_lock, flags);

	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK))
		जाओ unlock;

	/* Don't send ACK or NAK अगर a RDMA पढ़ो or atomic is pending. */
	अगर ((qp->s_flags & RVT_S_RESP_PENDING) || qp->s_rdma_ack_cnt)
		जाओ queue_ack;

	/* Conकाष्ठा the header with s_lock held so APM करोesn't change it. */
	ohdr = &hdr.u.oth;
	lrh0 = QIB_LRH_BTH;
	/* header size in 32-bit words LRH+BTH+AETH = (8+12+4)/4. */
	hwords = 6;
	अगर (unlikely(rdma_ah_get_ah_flags(&qp->remote_ah_attr) &
		     IB_AH_GRH)) अणु
		hwords += qib_make_grh(ibp, &hdr.u.l.grh,
				       rdma_ah_पढ़ो_grh(&qp->remote_ah_attr),
				       hwords, 0);
		ohdr = &hdr.u.l.oth;
		lrh0 = QIB_LRH_GRH;
	पूर्ण
	/* पढ़ो pkey_index w/o lock (its atomic) */
	bth0 = qib_get_pkey(ibp, qp->s_pkey_index) | (OP(ACKNOWLEDGE) << 24);
	अगर (qp->s_mig_state == IB_MIG_MIGRATED)
		bth0 |= IB_BTH_MIG_REQ;
	अगर (qp->r_nak_state)
		ohdr->u.aeth = cpu_to_be32((qp->r_msn & IB_MSN_MASK) |
					    (qp->r_nak_state <<
					     IB_AETH_CREDIT_SHIFT));
	अन्यथा
		ohdr->u.aeth = rvt_compute_aeth(qp);
	lrh0 |= ibp->sl_to_vl[rdma_ah_get_sl(&qp->remote_ah_attr)] << 12 |
		rdma_ah_get_sl(&qp->remote_ah_attr) << 4;
	hdr.lrh[0] = cpu_to_be16(lrh0);
	hdr.lrh[1] = cpu_to_be16(rdma_ah_get_dlid(&qp->remote_ah_attr));
	hdr.lrh[2] = cpu_to_be16(hwords + SIZE_OF_CRC);
	hdr.lrh[3] = cpu_to_be16(ppd->lid |
				 rdma_ah_get_path_bits(&qp->remote_ah_attr));
	ohdr->bth[0] = cpu_to_be32(bth0);
	ohdr->bth[1] = cpu_to_be32(qp->remote_qpn);
	ohdr->bth[2] = cpu_to_be32(qp->r_ack_psn & QIB_PSN_MASK);

	spin_unlock_irqrestore(&qp->s_lock, flags);

	/* Don't try to send ACKs if the link isn't ACTIVE */
	अगर (!(ppd->lflags & QIBL_LINKACTIVE))
		जाओ करोne;

	control = dd->f_setpbc_control(ppd, hwords + SIZE_OF_CRC,
				       qp->s_srate, lrh0 >> 12);
	/* length is + 1 क्रम the control dword */
	pbc = ((u64) control << 32) | (hwords + 1);

	piobuf = dd->f_माला_लोendbuf(ppd, pbc, &pbufn);
	अगर (!piobuf) अणु
		/*
		 * We are out of PIO buffers at the moment.
		 * Pass responsibility क्रम sending the ACK to the
		 * send tasklet so that when a PIO buffer becomes
		 * available, the ACK is sent ahead of other outgoing
		 * packets.
		 */
		spin_lock_irqsave(&qp->s_lock, flags);
		जाओ queue_ack;
	पूर्ण

	/*
	 * Write the pbc.
	 * We have to flush after the PBC क्रम correctness
	 * on some cpus or WC buffer can be written out of order.
	 */
	ग_लिखोq(pbc, piobuf);

	अगर (dd->flags & QIB_PIO_FLUSH_WC) अणु
		u32 *hdrp = (u32 *) &hdr;

		qib_flush_wc();
		qib_pio_copy(piobuf + 2, hdrp, hwords - 1);
		qib_flush_wc();
		__raw_ग_लिखोl(hdrp[hwords - 1], piobuf + hwords + 1);
	पूर्ण अन्यथा
		qib_pio_copy(piobuf + 2, (u32 *) &hdr, hwords);

	अगर (dd->flags & QIB_USE_SPCL_TRIG) अणु
		u32 spcl_off = (pbufn >= dd->piobcnt2k) ? 2047 : 1023;

		qib_flush_wc();
		__raw_ग_लिखोl(0xaebecede, piobuf + spcl_off);
	पूर्ण

	qib_flush_wc();
	qib_sendbuf_करोne(dd, pbufn);

	this_cpu_inc(ibp->pmastats->n_unicast_xmit);
	जाओ करोne;

queue_ack:
	अगर (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) अणु
		this_cpu_inc(*ibp->rvp.rc_qacks);
		qp->s_flags |= RVT_S_ACK_PENDING | RVT_S_RESP_PENDING;
		qp->s_nak_state = qp->r_nak_state;
		qp->s_ack_psn = qp->r_ack_psn;

		/* Schedule the send tasklet. */
		qib_schedule_send(qp);
	पूर्ण
unlock:
	spin_unlock_irqrestore(&qp->s_lock, flags);
करोne:
	वापस;
पूर्ण

/**
 * reset_psn - reset the QP state to send starting from PSN
 * @qp: the QP
 * @psn: the packet sequence number to restart at
 *
 * This is called from qib_rc_rcv() to process an incoming RC ACK
 * क्रम the given QP.
 * Called at पूर्णांकerrupt level with the QP s_lock held.
 */
अटल व्योम reset_psn(काष्ठा rvt_qp *qp, u32 psn)
अणु
	u32 n = qp->s_acked;
	काष्ठा rvt_swqe *wqe = rvt_get_swqe_ptr(qp, n);
	u32 opcode;

	qp->s_cur = n;

	/*
	 * If we are starting the request from the beginning,
	 * let the normal send code handle initialization.
	 */
	अगर (qib_cmp24(psn, wqe->psn) <= 0) अणु
		qp->s_state = OP(SEND_LAST);
		जाओ करोne;
	पूर्ण

	/* Find the work request opcode corresponding to the given PSN. */
	opcode = wqe->wr.opcode;
	क्रम (;;) अणु
		पूर्णांक dअगरf;

		अगर (++n == qp->s_size)
			n = 0;
		अगर (n == qp->s_tail)
			अवरोध;
		wqe = rvt_get_swqe_ptr(qp, n);
		dअगरf = qib_cmp24(psn, wqe->psn);
		अगर (dअगरf < 0)
			अवरोध;
		qp->s_cur = n;
		/*
		 * If we are starting the request from the beginning,
		 * let the normal send code handle initialization.
		 */
		अगर (dअगरf == 0) अणु
			qp->s_state = OP(SEND_LAST);
			जाओ करोne;
		पूर्ण
		opcode = wqe->wr.opcode;
	पूर्ण

	/*
	 * Set the state to restart in the middle of a request.
	 * Don't change the s_sge, s_cur_sge, or s_cur_size.
	 * See qib_make_rc_req().
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

	हाल IB_WR_RDMA_READ:
		qp->s_state = OP(RDMA_READ_RESPONSE_MIDDLE);
		अवरोध;

	शेष:
		/*
		 * This हाल shouldn't happen since its only
		 * one PSN per req.
		 */
		qp->s_state = OP(SEND_LAST);
	पूर्ण
करोne:
	qp->s_psn = psn;
	/*
	 * Set RVT_S_WAIT_PSN as qib_rc_complete() may start the समयr
	 * asynchronously beक्रमe the send tasklet can get scheduled.
	 * Doing it in qib_make_rc_req() is too late.
	 */
	अगर ((qib_cmp24(qp->s_psn, qp->s_sending_hpsn) <= 0) &&
	    (qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) <= 0))
		qp->s_flags |= RVT_S_WAIT_PSN;
पूर्ण

/*
 * Back up requester to resend the last un-ACKed request.
 * The QP r_lock and s_lock should be held and पूर्णांकerrupts disabled.
 */
व्योम qib_restart_rc(काष्ठा rvt_qp *qp, u32 psn, पूर्णांक रुको)
अणु
	काष्ठा rvt_swqe *wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
	काष्ठा qib_ibport *ibp;

	अगर (qp->s_retry == 0) अणु
		अगर (qp->s_mig_state == IB_MIG_ARMED) अणु
			qib_migrate_qp(qp);
			qp->s_retry = qp->s_retry_cnt;
		पूर्ण अन्यथा अगर (qp->s_last == qp->s_acked) अणु
			rvt_send_complete(qp, wqe, IB_WC_RETRY_EXC_ERR);
			rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);
			वापस;
		पूर्ण अन्यथा /* XXX need to handle delayed completion */
			वापस;
	पूर्ण अन्यथा
		qp->s_retry--;

	ibp = to_iport(qp->ibqp.device, qp->port_num);
	अगर (wqe->wr.opcode == IB_WR_RDMA_READ)
		ibp->rvp.n_rc_resends++;
	अन्यथा
		ibp->rvp.n_rc_resends += (qp->s_psn - psn) & QIB_PSN_MASK;

	qp->s_flags &= ~(RVT_S_WAIT_FENCE | RVT_S_WAIT_RDMAR |
			 RVT_S_WAIT_SSN_CREDIT | RVT_S_WAIT_PSN |
			 RVT_S_WAIT_ACK);
	अगर (रुको)
		qp->s_flags |= RVT_S_SEND_ONE;
	reset_psn(qp, psn);
पूर्ण

/*
 * Set qp->s_sending_psn to the next PSN after the given one.
 * This would be psn+1 except when RDMA पढ़ोs are present.
 */
अटल व्योम reset_sending_psn(काष्ठा rvt_qp *qp, u32 psn)
अणु
	काष्ठा rvt_swqe *wqe;
	u32 n = qp->s_last;

	/* Find the work request corresponding to the given PSN. */
	क्रम (;;) अणु
		wqe = rvt_get_swqe_ptr(qp, n);
		अगर (qib_cmp24(psn, wqe->lpsn) <= 0) अणु
			अगर (wqe->wr.opcode == IB_WR_RDMA_READ)
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

/*
 * This should be called with the QP s_lock held and पूर्णांकerrupts disabled.
 */
व्योम qib_rc_send_complete(काष्ठा rvt_qp *qp, काष्ठा ib_header *hdr)
अणु
	काष्ठा ib_other_headers *ohdr;
	काष्ठा rvt_swqe *wqe;
	u32 opcode;
	u32 psn;

	अगर (!(ib_rvt_state_ops[qp->state] & RVT_SEND_OR_FLUSH_OR_RECV_OK))
		वापस;

	/* Find out where the BTH is */
	अगर ((be16_to_cpu(hdr->lrh[0]) & 3) == QIB_LRH_BTH)
		ohdr = &hdr->u.oth;
	अन्यथा
		ohdr = &hdr->u.l.oth;

	opcode = be32_to_cpu(ohdr->bth[0]) >> 24;
	अगर (opcode >= OP(RDMA_READ_RESPONSE_FIRST) &&
	    opcode <= OP(ATOMIC_ACKNOWLEDGE)) अणु
		WARN_ON(!qp->s_rdma_ack_cnt);
		qp->s_rdma_ack_cnt--;
		वापस;
	पूर्ण

	psn = be32_to_cpu(ohdr->bth[2]);
	reset_sending_psn(qp, psn);

	/*
	 * Start समयr after a packet requesting an ACK has been sent and
	 * there are still requests that haven't been acked.
	 */
	अगर ((psn & IB_BTH_REQ_ACK) && qp->s_acked != qp->s_tail &&
	    !(qp->s_flags & (RVT_S_TIMER | RVT_S_WAIT_RNR | RVT_S_WAIT_PSN)) &&
	    (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK))
		rvt_add_retry_समयr(qp);

	जबतक (qp->s_last != qp->s_acked) अणु
		wqe = rvt_get_swqe_ptr(qp, qp->s_last);
		अगर (qib_cmp24(wqe->lpsn, qp->s_sending_psn) >= 0 &&
		    qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) <= 0)
			अवरोध;
		rvt_qp_complete_swqe(qp,
				     wqe,
				     ib_qib_wc_opcode[wqe->wr.opcode],
				     IB_WC_SUCCESS);
	पूर्ण
	/*
	 * If we were रुकोing क्रम sends to complete beक्रमe resending,
	 * and they are now complete, restart sending.
	 */
	अगर (qp->s_flags & RVT_S_WAIT_PSN &&
	    qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) > 0) अणु
		qp->s_flags &= ~RVT_S_WAIT_PSN;
		qp->s_sending_psn = qp->s_psn;
		qp->s_sending_hpsn = qp->s_psn - 1;
		qib_schedule_send(qp);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम update_last_psn(काष्ठा rvt_qp *qp, u32 psn)
अणु
	qp->s_last_psn = psn;
पूर्ण

/*
 * Generate a SWQE completion.
 * This is similar to qib_send_complete but has to check to be sure
 * that the SGEs are not being referenced अगर the SWQE is being resent.
 */
अटल काष्ठा rvt_swqe *करो_rc_completion(काष्ठा rvt_qp *qp,
					 काष्ठा rvt_swqe *wqe,
					 काष्ठा qib_ibport *ibp)
अणु
	/*
	 * Don't decrement refcount and don't generate a
	 * completion अगर the SWQE is being resent until the send
	 * is finished.
	 */
	अगर (qib_cmp24(wqe->lpsn, qp->s_sending_psn) < 0 ||
	    qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) > 0)
		rvt_qp_complete_swqe(qp,
				     wqe,
				     ib_qib_wc_opcode[wqe->wr.opcode],
				     IB_WC_SUCCESS);
	अन्यथा
		this_cpu_inc(*ibp->rvp.rc_delayed_comp);

	qp->s_retry = qp->s_retry_cnt;
	update_last_psn(qp, wqe->lpsn);

	/*
	 * If we are completing a request which is in the process of
	 * being resent, we can stop resending it since we know the
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
	वापस wqe;
पूर्ण

/*
 * करो_rc_ack - process an incoming RC ACK
 * @qp: the QP the ACK came in on
 * @psn: the packet sequence number of the ACK
 * @opcode: the opcode of the request that resulted in the ACK
 *
 * This is called from qib_rc_rcv_resp() to process an incoming RC ACK
 * क्रम the given QP.
 * Called at पूर्णांकerrupt level with the QP s_lock held.
 * Returns 1 अगर OK, 0 अगर current operation should be पातed (NAK).
 */
अटल पूर्णांक करो_rc_ack(काष्ठा rvt_qp *qp, u32 aeth, u32 psn, पूर्णांक opcode,
		     u64 val, काष्ठा qib_ctxtdata *rcd)
अणु
	काष्ठा qib_ibport *ibp;
	क्रमागत ib_wc_status status;
	काष्ठा rvt_swqe *wqe;
	पूर्णांक ret = 0;
	u32 ack_psn;
	पूर्णांक dअगरf;

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
	ibp = to_iport(qp->ibqp.device, qp->port_num);

	/*
	 * The MSN might be क्रम a later WQE than the PSN indicates so
	 * only complete WQEs that the PSN finishes.
	 */
	जबतक ((dअगरf = qib_cmp24(ack_psn, wqe->lpsn)) >= 0) अणु
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
			जाओ bail;
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
		    ((wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		      wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) &&
		     (opcode != OP(ATOMIC_ACKNOWLEDGE) || dअगरf != 0))) अणु
			/* Retry this request. */
			अगर (!(qp->r_flags & RVT_R_RDMAR_SEQ)) अणु
				qp->r_flags |= RVT_R_RDMAR_SEQ;
				qib_restart_rc(qp, qp->s_last_psn + 1, 0);
				अगर (list_empty(&qp->rspरुको)) अणु
					qp->r_flags |= RVT_R_RSP_SEND;
					rvt_get_qp(qp);
					list_add_tail(&qp->rspरुको,
						      &rcd->qp_रुको_list);
				पूर्ण
			पूर्ण
			/*
			 * No need to process the ACK/NAK since we are
			 * restarting an earlier request.
			 */
			जाओ bail;
		पूर्ण
		अगर (wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		    wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) अणु
			u64 *vaddr = wqe->sg_list[0].vaddr;
			*vaddr = val;
		पूर्ण
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
				qib_schedule_send(qp);
			पूर्ण अन्यथा अगर (qp->s_flags & RVT_S_WAIT_RDMAR) अणु
				qp->s_flags &= ~(RVT_S_WAIT_RDMAR |
						 RVT_S_WAIT_ACK);
				qib_schedule_send(qp);
			पूर्ण
		पूर्ण
		wqe = करो_rc_completion(qp, wqe, ibp);
		अगर (qp->s_acked == qp->s_tail)
			अवरोध;
	पूर्ण

	चयन (aeth >> IB_AETH_NAK_SHIFT) अणु
	हाल 0:         /* ACK */
		this_cpu_inc(*ibp->rvp.rc_acks);
		अगर (qp->s_acked != qp->s_tail) अणु
			/*
			 * We are expecting more ACKs so
			 * reset the retransmit समयr.
			 */
			rvt_mod_retry_समयr(qp);
			/*
			 * We can stop resending the earlier packets and
			 * जारी with the next packet the receiver wants.
			 */
			अगर (qib_cmp24(qp->s_psn, psn) <= 0)
				reset_psn(qp, psn + 1);
		पूर्ण अन्यथा अणु
			/* No more acks - समाप्त all समयrs */
			rvt_stop_rc_समयrs(qp);
			अगर (qib_cmp24(qp->s_psn, psn) <= 0) अणु
				qp->s_state = OP(SEND_LAST);
				qp->s_psn = psn + 1;
			पूर्ण
		पूर्ण
		अगर (qp->s_flags & RVT_S_WAIT_ACK) अणु
			qp->s_flags &= ~RVT_S_WAIT_ACK;
			qib_schedule_send(qp);
		पूर्ण
		rvt_get_credit(qp, aeth);
		qp->s_rnr_retry = qp->s_rnr_retry_cnt;
		qp->s_retry = qp->s_retry_cnt;
		update_last_psn(qp, psn);
		वापस 1;

	हाल 1:         /* RNR NAK */
		ibp->rvp.n_rnr_naks++;
		अगर (qp->s_acked == qp->s_tail)
			जाओ bail;
		अगर (qp->s_flags & RVT_S_WAIT_RNR)
			जाओ bail;
		अगर (qp->s_rnr_retry == 0) अणु
			status = IB_WC_RNR_RETRY_EXC_ERR;
			जाओ class_b;
		पूर्ण
		अगर (qp->s_rnr_retry_cnt < 7)
			qp->s_rnr_retry--;

		/* The last valid PSN is the previous PSN. */
		update_last_psn(qp, psn - 1);

		ibp->rvp.n_rc_resends += (qp->s_psn - psn) & QIB_PSN_MASK;

		reset_psn(qp, psn);

		qp->s_flags &= ~(RVT_S_WAIT_SSN_CREDIT | RVT_S_WAIT_ACK);
		rvt_stop_rc_समयrs(qp);
		rvt_add_rnr_समयr(qp, aeth);
		वापस 0;

	हाल 3:         /* NAK */
		अगर (qp->s_acked == qp->s_tail)
			जाओ bail;
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
			qib_restart_rc(qp, psn, 0);
			qib_schedule_send(qp);
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
				rvt_send_complete(qp, wqe, status);
				rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);
			पूर्ण
			अवरोध;

		शेष:
			/* Ignore other reserved NAK error codes */
			जाओ reserved;
		पूर्ण
		qp->s_retry = qp->s_retry_cnt;
		qp->s_rnr_retry = qp->s_rnr_retry_cnt;
		जाओ bail;

	शेष:                /* 2: reserved */
reserved:
		/* Ignore reserved NAK codes. */
		जाओ bail;
	पूर्ण

bail:
	rvt_stop_rc_समयrs(qp);
	वापस ret;
पूर्ण

/*
 * We have seen an out of sequence RDMA पढ़ो middle or last packet.
 * This ACKs SENDs and RDMA ग_लिखोs up to the first RDMA पढ़ो or atomic SWQE.
 */
अटल व्योम rdma_seq_err(काष्ठा rvt_qp *qp, काष्ठा qib_ibport *ibp, u32 psn,
			 काष्ठा qib_ctxtdata *rcd)
अणु
	काष्ठा rvt_swqe *wqe;

	/* Remove QP from retry समयr */
	rvt_stop_rc_समयrs(qp);

	wqe = rvt_get_swqe_ptr(qp, qp->s_acked);

	जबतक (qib_cmp24(psn, wqe->lpsn) > 0) अणु
		अगर (wqe->wr.opcode == IB_WR_RDMA_READ ||
		    wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		    wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD)
			अवरोध;
		wqe = करो_rc_completion(qp, wqe, ibp);
	पूर्ण

	ibp->rvp.n_rdma_seq++;
	qp->r_flags |= RVT_R_RDMAR_SEQ;
	qib_restart_rc(qp, qp->s_last_psn + 1, 0);
	अगर (list_empty(&qp->rspरुको)) अणु
		qp->r_flags |= RVT_R_RSP_SEND;
		rvt_get_qp(qp);
		list_add_tail(&qp->rspरुको, &rcd->qp_रुको_list);
	पूर्ण
पूर्ण

/**
 * qib_rc_rcv_resp - process an incoming RC response packet
 * @ibp: the port this packet came in on
 * @ohdr: the other headers क्रम this packet
 * @data: the packet data
 * @tlen: the packet length
 * @qp: the QP क्रम this packet
 * @opcode: the opcode क्रम this packet
 * @psn: the packet sequence number क्रम this packet
 * @hdrsize: the header length
 * @pmtu: the path MTU
 * @rcd: the context poपूर्णांकer
 *
 * This is called from qib_rc_rcv() to process an incoming RC response
 * packet क्रम the given QP.
 * Called at पूर्णांकerrupt level.
 */
अटल व्योम qib_rc_rcv_resp(काष्ठा qib_ibport *ibp,
			    काष्ठा ib_other_headers *ohdr,
			    व्योम *data, u32 tlen,
			    काष्ठा rvt_qp *qp,
			    u32 opcode,
			    u32 psn, u32 hdrsize, u32 pmtu,
			    काष्ठा qib_ctxtdata *rcd)
अणु
	काष्ठा rvt_swqe *wqe;
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	क्रमागत ib_wc_status status;
	अचिन्हित दीर्घ flags;
	पूर्णांक dअगरf;
	u32 pad;
	u32 aeth;
	u64 val;

	अगर (opcode != OP(RDMA_READ_RESPONSE_MIDDLE)) अणु
		/*
		 * If ACK'd PSN on SDMA busy list try to make progress to
		 * reclaim SDMA credits.
		 */
		अगर ((qib_cmp24(psn, qp->s_sending_psn) >= 0) &&
		    (qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) <= 0)) अणु

			/*
			 * If send tasklet not running attempt to progress
			 * SDMA queue.
			 */
			अगर (!(qp->s_flags & RVT_S_BUSY)) अणु
				/* Acquire SDMA Lock */
				spin_lock_irqsave(&ppd->sdma_lock, flags);
				/* Invoke sdma make progress */
				qib_sdma_make_progress(ppd);
				/* Release SDMA Lock */
				spin_unlock_irqrestore(&ppd->sdma_lock, flags);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&qp->s_lock, flags);
	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK))
		जाओ ack_करोne;

	/* Ignore invalid responses. */
	अगर (qib_cmp24(psn, READ_ONCE(qp->s_next_psn)) >= 0)
		जाओ ack_करोne;

	/* Ignore duplicate responses. */
	dअगरf = qib_cmp24(psn, qp->s_last_psn);
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
		अगर (qib_cmp24(psn, qp->s_last_psn + 1) != 0)
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
		hdrsize += 4;
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
		अगर (unlikely(qib_cmp24(psn, qp->s_last_psn + 1)))
			जाओ ack_seq_err;
		अगर (unlikely(wqe->wr.opcode != IB_WR_RDMA_READ))
			जाओ ack_op_err;
पढ़ो_middle:
		अगर (unlikely(tlen != (hdrsize + pmtu + 4)))
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
			qib_schedule_send(qp);
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
		/* Get the number of bytes the message was padded by. */
		pad = (be32_to_cpu(ohdr->bth[0]) >> 20) & 3;
		/*
		 * Check that the data size is >= 0 && <= pmtu.
		 * Remember to account क्रम the AETH header (4) and
		 * ICRC (4).
		 */
		अगर (unlikely(tlen < (hdrsize + pad + 8)))
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
		अगर (unlikely(qib_cmp24(psn, qp->s_last_psn + 1)))
			जाओ ack_seq_err;
		अगर (unlikely(wqe->wr.opcode != IB_WR_RDMA_READ))
			जाओ ack_op_err;
		/* Get the number of bytes the message was padded by. */
		pad = (be32_to_cpu(ohdr->bth[0]) >> 20) & 3;
		/*
		 * Check that the data size is >= 1 && <= pmtu.
		 * Remember to account क्रम the AETH header (4) and
		 * ICRC (4).
		 */
		अगर (unlikely(tlen <= (hdrsize + pad + 8)))
			जाओ ack_len_err;
पढ़ो_last:
		tlen -= hdrsize + pad + 8;
		अगर (unlikely(tlen != qp->s_rdma_पढ़ो_len))
			जाओ ack_len_err;
		aeth = be32_to_cpu(ohdr->u.aeth);
		rvt_copy_sge(qp, &qp->s_rdma_पढ़ो_sge,
			     data, tlen, false, false);
		WARN_ON(qp->s_rdma_पढ़ो_sge.num_sge);
		(व्योम) करो_rc_ack(qp, aeth, psn,
				 OP(RDMA_READ_RESPONSE_LAST), 0, rcd);
		जाओ ack_करोne;
	पूर्ण

ack_op_err:
	status = IB_WC_LOC_QP_OP_ERR;
	जाओ ack_err;

ack_seq_err:
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

/**
 * qib_rc_rcv_error - process an incoming duplicate or error RC packet
 * @ohdr: the other headers क्रम this packet
 * @data: the packet data
 * @qp: the QP क्रम this packet
 * @opcode: the opcode क्रम this packet
 * @psn: the packet sequence number क्रम this packet
 * @dअगरf: the dअगरference between the PSN and the expected PSN
 * @rcd: the context poपूर्णांकer
 *
 * This is called from qib_rc_rcv() to process an unexpected
 * incoming RC packet क्रम the given QP.
 * Called at पूर्णांकerrupt level.
 * Return 1 अगर no more processing is needed; otherwise वापस 0 to
 * schedule a response to be sent.
 */
अटल पूर्णांक qib_rc_rcv_error(काष्ठा ib_other_headers *ohdr,
			    व्योम *data,
			    काष्ठा rvt_qp *qp,
			    u32 opcode,
			    u32 psn,
			    पूर्णांक dअगरf,
			    काष्ठा qib_ctxtdata *rcd)
अणु
	काष्ठा qib_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा rvt_ack_entry *e;
	अचिन्हित दीर्घ flags;
	u8 i, prev;
	पूर्णांक old_req;

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
			अगर (list_empty(&qp->rspरुको)) अणु
				qp->r_flags |= RVT_R_RSP_NAK;
				rvt_get_qp(qp);
				list_add_tail(&qp->rspरुको, &rcd->qp_रुको_list);
			पूर्ण
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
	old_req = 1;
	ibp->rvp.n_rc_dupreq++;

	spin_lock_irqsave(&qp->s_lock, flags);

	क्रम (i = qp->r_head_ack_queue; ; i = prev) अणु
		अगर (i == qp->s_tail_ack_queue)
			old_req = 0;
		अगर (i)
			prev = i - 1;
		अन्यथा
			prev = QIB_MAX_RDMA_ATOMIC;
		अगर (prev == qp->r_head_ack_queue) अणु
			e = शून्य;
			अवरोध;
		पूर्ण
		e = &qp->s_ack_queue[prev];
		अगर (!e->opcode) अणु
			e = शून्य;
			अवरोध;
		पूर्ण
		अगर (qib_cmp24(psn, e->psn) >= 0) अणु
			अगर (prev == qp->s_tail_ack_queue &&
			    qib_cmp24(psn, e->lpsn) <= 0)
				old_req = 0;
			अवरोध;
		पूर्ण
	पूर्ण
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
		offset = ((psn - e->psn) & QIB_PSN_MASK) *
			qp->pmtu;
		len = be32_to_cpu(reth->length);
		अगर (unlikely(offset + len != e->rdma_sge.sge_length))
			जाओ unlock_करोne;
		अगर (e->rdma_sge.mr) अणु
			rvt_put_mr(e->rdma_sge.mr);
			e->rdma_sge.mr = शून्य;
		पूर्ण
		अगर (len != 0) अणु
			u32 rkey = be32_to_cpu(reth->rkey);
			u64 vaddr = be64_to_cpu(reth->vaddr);
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
		qp->s_tail_ack_queue = prev;
		अवरोध;
	पूर्ण

	हाल OP(COMPARE_SWAP):
	हाल OP(FETCH_ADD): अणु
		/*
		 * If we didn't find the atomic request in the ack queue
		 * or the send tasklet is alपढ़ोy backed up to send an
		 * earlier entry, we can ignore this request.
		 */
		अगर (!e || e->opcode != (u8) opcode || old_req)
			जाओ unlock_करोne;
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
		अगर (i == qp->r_head_ack_queue) अणु
			spin_unlock_irqrestore(&qp->s_lock, flags);
			qp->r_nak_state = 0;
			qp->r_ack_psn = qp->r_psn - 1;
			जाओ send_ack;
		पूर्ण
		/*
		 * Try to send a simple ACK to work around a Mellanox bug
		 * which करोesn't accept a RDMA पढ़ो response or atomic
		 * response as an ACK क्रम earlier SENDs or RDMA ग_लिखोs.
		 */
		अगर (!(qp->s_flags & RVT_S_RESP_PENDING)) अणु
			spin_unlock_irqrestore(&qp->s_lock, flags);
			qp->r_nak_state = 0;
			qp->r_ack_psn = qp->s_ack_queue[i].psn - 1;
			जाओ send_ack;
		पूर्ण
		/*
		 * Resend the RDMA पढ़ो or atomic op which
		 * ACKs this duplicate request.
		 */
		qp->s_tail_ack_queue = i;
		अवरोध;
	पूर्ण
	qp->s_ack_state = OP(ACKNOWLEDGE);
	qp->s_flags |= RVT_S_RESP_PENDING;
	qp->r_nak_state = 0;
	qib_schedule_send(qp);

unlock_करोne:
	spin_unlock_irqrestore(&qp->s_lock, flags);
करोne:
	वापस 1;

send_ack:
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qib_update_ack_queue(काष्ठा rvt_qp *qp, अचिन्हित n)
अणु
	अचिन्हित next;

	next = n + 1;
	अगर (next > QIB_MAX_RDMA_ATOMIC)
		next = 0;
	qp->s_tail_ack_queue = next;
	qp->s_ack_state = OP(ACKNOWLEDGE);
पूर्ण

/**
 * qib_rc_rcv - process an incoming RC packet
 * @rcd: the context poपूर्णांकer
 * @hdr: the header of this packet
 * @has_grh: true अगर the header has a GRH
 * @data: the packet data
 * @tlen: the packet length
 * @qp: the QP क्रम this packet
 *
 * This is called from qib_qp_rcv() to process an incoming RC packet
 * क्रम the given QP.
 * Called at पूर्णांकerrupt level.
 */
व्योम qib_rc_rcv(काष्ठा qib_ctxtdata *rcd, काष्ठा ib_header *hdr,
		पूर्णांक has_grh, व्योम *data, u32 tlen, काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_ibport *ibp = &rcd->ppd->ibport_data;
	काष्ठा ib_other_headers *ohdr;
	u32 opcode;
	u32 hdrsize;
	u32 psn;
	u32 pad;
	काष्ठा ib_wc wc;
	u32 pmtu = qp->pmtu;
	पूर्णांक dअगरf;
	काष्ठा ib_reth *reth;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Check क्रम GRH */
	अगर (!has_grh) अणु
		ohdr = &hdr->u.oth;
		hdrsize = 8 + 12;       /* LRH + BTH */
	पूर्ण अन्यथा अणु
		ohdr = &hdr->u.l.oth;
		hdrsize = 8 + 40 + 12;  /* LRH + GRH + BTH */
	पूर्ण

	opcode = be32_to_cpu(ohdr->bth[0]);
	अगर (qib_ruc_check_hdr(ibp, hdr, has_grh, qp, opcode))
		वापस;

	psn = be32_to_cpu(ohdr->bth[2]);
	opcode >>= 24;

	/*
	 * Process responses (ACKs) beक्रमe anything अन्यथा.  Note that the
	 * packet sequence number will be क्रम something in the send work
	 * queue rather than the expected receive packet sequence number.
	 * In other words, this QP is the requester.
	 */
	अगर (opcode >= OP(RDMA_READ_RESPONSE_FIRST) &&
	    opcode <= OP(ATOMIC_ACKNOWLEDGE)) अणु
		qib_rc_rcv_resp(ibp, ohdr, data, tlen, qp, opcode, psn,
				hdrsize, pmtu, rcd);
		वापस;
	पूर्ण

	/* Compute 24 bits worth of dअगरference. */
	dअगरf = qib_cmp24(psn, qp->r_psn);
	अगर (unlikely(dअगरf)) अणु
		अगर (qib_rc_rcv_error(ohdr, data, qp, opcode, psn, dअगरf, rcd))
			वापस;
		जाओ send_ack;
	पूर्ण

	/* Check क्रम opcode sequence errors. */
	चयन (qp->r_state) अणु
	हाल OP(SEND_FIRST):
	हाल OP(SEND_MIDDLE):
		अगर (opcode == OP(SEND_MIDDLE) ||
		    opcode == OP(SEND_LAST) ||
		    opcode == OP(SEND_LAST_WITH_IMMEDIATE))
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
		अगर (unlikely(tlen != (hdrsize + pmtu + 4)))
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
		ret = rvt_get_rwqe(qp, false);
		अगर (ret < 0)
			जाओ nack_op_err;
		अगर (!ret)
			जाओ rnr_nak;
		qp->r_rcv_len = 0;
		अगर (opcode == OP(SEND_ONLY))
			जाओ no_immediate_data;
		fallthrough;	/* क्रम SEND_ONLY_WITH_IMMEDIATE */
	हाल OP(SEND_LAST_WITH_IMMEDIATE):
send_last_imm:
		wc.ex.imm_data = ohdr->u.imm_data;
		hdrsize += 4;
		wc.wc_flags = IB_WC_WITH_IMM;
		जाओ send_last;
	हाल OP(SEND_LAST):
	हाल OP(RDMA_WRITE_LAST):
no_immediate_data:
		wc.wc_flags = 0;
		wc.ex.imm_data = 0;
send_last:
		/* Get the number of bytes the message was padded by. */
		pad = (be32_to_cpu(ohdr->bth[0]) >> 20) & 3;
		/* Check क्रम invalid length. */
		/* XXX LAST len should be >= 1 */
		अगर (unlikely(tlen < (hdrsize + pad + 4)))
			जाओ nack_inv;
		/* Don't count the CRC. */
		tlen -= (hdrsize + pad + 4);
		wc.byte_len = tlen + qp->r_rcv_len;
		अगर (unlikely(wc.byte_len > qp->r_len))
			जाओ nack_inv;
		rvt_copy_sge(qp, &qp->r_sge, data, tlen, true, false);
		rvt_put_ss(&qp->r_sge);
		qp->r_msn++;
		अगर (!test_and_clear_bit(RVT_R_WRID_VALID, &qp->r_aflags))
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
		wc.slid = rdma_ah_get_dlid(&qp->remote_ah_attr);
		wc.sl = rdma_ah_get_sl(&qp->remote_ah_attr);
		/* zero fields that are N/A */
		wc.venकरोr_err = 0;
		wc.pkey_index = 0;
		wc.dlid_path_bits = 0;
		wc.port_num = 0;
		/* Signal completion event अगर the solicited bit is set. */
		rvt_recv_cq(qp, &wc, ib_bth_is_solicited(ohdr));
		अवरोध;

	हाल OP(RDMA_WRITE_FIRST):
	हाल OP(RDMA_WRITE_ONLY):
	हाल OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE):
		अगर (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_WRITE)))
			जाओ nack_inv;
		/* consume RWQE */
		reth = &ohdr->u.rc.reth;
		hdrsize += माप(*reth);
		qp->r_len = be32_to_cpu(reth->length);
		qp->r_rcv_len = 0;
		qp->r_sge.sg_list = शून्य;
		अगर (qp->r_len != 0) अणु
			u32 rkey = be32_to_cpu(reth->rkey);
			u64 vaddr = be64_to_cpu(reth->vaddr);
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
			rvt_put_ss(&qp->r_sge);
			जाओ rnr_nak;
		पूर्ण
		wc.ex.imm_data = ohdr->u.rc.imm_data;
		hdrsize += 4;
		wc.wc_flags = IB_WC_WITH_IMM;
		जाओ send_last;

	हाल OP(RDMA_READ_REQUEST): अणु
		काष्ठा rvt_ack_entry *e;
		u32 len;
		u8 next;

		अगर (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_READ)))
			जाओ nack_inv;
		next = qp->r_head_ack_queue + 1;
		/* s_ack_queue is size QIB_MAX_RDMA_ATOMIC+1 so use > not >= */
		अगर (next > QIB_MAX_RDMA_ATOMIC)
			next = 0;
		spin_lock_irqsave(&qp->s_lock, flags);
		अगर (unlikely(next == qp->s_tail_ack_queue)) अणु
			अगर (!qp->s_ack_queue[next].sent)
				जाओ nack_inv_unlck;
			qib_update_ack_queue(qp, next);
		पूर्ण
		e = &qp->s_ack_queue[qp->r_head_ack_queue];
		अगर (e->opcode == OP(RDMA_READ_REQUEST) && e->rdma_sge.mr) अणु
			rvt_put_mr(e->rdma_sge.mr);
			e->rdma_sge.mr = शून्य;
		पूर्ण
		reth = &ohdr->u.rc.reth;
		len = be32_to_cpu(reth->length);
		अगर (len) अणु
			u32 rkey = be32_to_cpu(reth->rkey);
			u64 vaddr = be64_to_cpu(reth->vaddr);
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

		/* Schedule the send tasklet. */
		qp->s_flags |= RVT_S_RESP_PENDING;
		qib_schedule_send(qp);

		जाओ sunlock;
	पूर्ण

	हाल OP(COMPARE_SWAP):
	हाल OP(FETCH_ADD): अणु
		काष्ठा ib_atomic_eth *ateth;
		काष्ठा rvt_ack_entry *e;
		u64 vaddr;
		atomic64_t *maddr;
		u64 sdata;
		u32 rkey;
		u8 next;

		अगर (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_ATOMIC)))
			जाओ nack_inv;
		next = qp->r_head_ack_queue + 1;
		अगर (next > QIB_MAX_RDMA_ATOMIC)
			next = 0;
		spin_lock_irqsave(&qp->s_lock, flags);
		अगर (unlikely(next == qp->s_tail_ack_queue)) अणु
			अगर (!qp->s_ack_queue[next].sent)
				जाओ nack_inv_unlck;
			qib_update_ack_queue(qp, next);
		पूर्ण
		e = &qp->s_ack_queue[qp->r_head_ack_queue];
		अगर (e->opcode == OP(RDMA_READ_REQUEST) && e->rdma_sge.mr) अणु
			rvt_put_mr(e->rdma_sge.mr);
			e->rdma_sge.mr = शून्य;
		पूर्ण
		ateth = &ohdr->u.atomic_eth;
		vaddr = get_ib_ateth_vaddr(ateth);
		अगर (unlikely(vaddr & (माप(u64) - 1)))
			जाओ nack_inv_unlck;
		rkey = be32_to_cpu(ateth->rkey);
		/* Check rkey & NAK */
		अगर (unlikely(!rvt_rkey_ok(qp, &qp->r_sge.sge, माप(u64),
					  vaddr, rkey,
					  IB_ACCESS_REMOTE_ATOMIC)))
			जाओ nack_acc_unlck;
		/* Perक्रमm atomic OP and save result. */
		maddr = (atomic64_t *) qp->r_sge.sge.vaddr;
		sdata = get_ib_ateth_swap(ateth);
		e->atomic_data = (opcode == OP(FETCH_ADD)) ?
			(u64) atomic64_add_वापस(sdata, maddr) - sdata :
			(u64) cmpxchg((u64 *) qp->r_sge.sge.vaddr,
				      get_ib_ateth_compare(ateth),
				      sdata);
		rvt_put_mr(qp->r_sge.sge.mr);
		qp->r_sge.num_sge = 0;
		e->opcode = opcode;
		e->sent = 0;
		e->psn = psn;
		e->lpsn = psn;
		qp->r_msn++;
		qp->r_psn++;
		qp->r_state = opcode;
		qp->r_nak_state = 0;
		qp->r_head_ack_queue = next;

		/* Schedule the send tasklet. */
		qp->s_flags |= RVT_S_RESP_PENDING;
		qib_schedule_send(qp);

		जाओ sunlock;
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
	अगर (psn & (1 << 31))
		जाओ send_ack;
	वापस;

rnr_nak:
	qp->r_nak_state = IB_RNR_NAK | qp->r_min_rnr_समयr;
	qp->r_ack_psn = qp->r_psn;
	/* Queue RNR NAK क्रम later */
	अगर (list_empty(&qp->rspरुको)) अणु
		qp->r_flags |= RVT_R_RSP_NAK;
		rvt_get_qp(qp);
		list_add_tail(&qp->rspरुको, &rcd->qp_रुको_list);
	पूर्ण
	वापस;

nack_op_err:
	rvt_rc_error(qp, IB_WC_LOC_QP_OP_ERR);
	qp->r_nak_state = IB_NAK_REMOTE_OPERATIONAL_ERROR;
	qp->r_ack_psn = qp->r_psn;
	/* Queue NAK क्रम later */
	अगर (list_empty(&qp->rspरुको)) अणु
		qp->r_flags |= RVT_R_RSP_NAK;
		rvt_get_qp(qp);
		list_add_tail(&qp->rspरुको, &rcd->qp_रुको_list);
	पूर्ण
	वापस;

nack_inv_unlck:
	spin_unlock_irqrestore(&qp->s_lock, flags);
nack_inv:
	rvt_rc_error(qp, IB_WC_LOC_QP_OP_ERR);
	qp->r_nak_state = IB_NAK_INVALID_REQUEST;
	qp->r_ack_psn = qp->r_psn;
	/* Queue NAK क्रम later */
	अगर (list_empty(&qp->rspरुको)) अणु
		qp->r_flags |= RVT_R_RSP_NAK;
		rvt_get_qp(qp);
		list_add_tail(&qp->rspरुको, &rcd->qp_रुको_list);
	पूर्ण
	वापस;

nack_acc_unlck:
	spin_unlock_irqrestore(&qp->s_lock, flags);
nack_acc:
	rvt_rc_error(qp, IB_WC_LOC_PROT_ERR);
	qp->r_nak_state = IB_NAK_REMOTE_ACCESS_ERROR;
	qp->r_ack_psn = qp->r_psn;
send_ack:
	qib_send_rc_ack(qp);
	वापस;

sunlock:
	spin_unlock_irqrestore(&qp->s_lock, flags);
पूर्ण
