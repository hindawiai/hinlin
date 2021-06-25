<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश <linux/skbuff.h>

#समावेश "rxe.h"
#समावेश "rxe_loc.h"
#समावेश "rxe_queue.h"

क्रमागत resp_states अणु
	RESPST_NONE,
	RESPST_GET_REQ,
	RESPST_CHK_PSN,
	RESPST_CHK_OP_SEQ,
	RESPST_CHK_OP_VALID,
	RESPST_CHK_RESOURCE,
	RESPST_CHK_LENGTH,
	RESPST_CHK_RKEY,
	RESPST_EXECUTE,
	RESPST_READ_REPLY,
	RESPST_COMPLETE,
	RESPST_ACKNOWLEDGE,
	RESPST_CLEANUP,
	RESPST_DUPLICATE_REQUEST,
	RESPST_ERR_MALFORMED_WQE,
	RESPST_ERR_UNSUPPORTED_OPCODE,
	RESPST_ERR_MISALIGNED_ATOMIC,
	RESPST_ERR_PSN_OUT_OF_SEQ,
	RESPST_ERR_MISSING_OPCODE_FIRST,
	RESPST_ERR_MISSING_OPCODE_LAST_C,
	RESPST_ERR_MISSING_OPCODE_LAST_D1E,
	RESPST_ERR_TOO_MANY_RDMA_ATM_REQ,
	RESPST_ERR_RNR,
	RESPST_ERR_RKEY_VIOLATION,
	RESPST_ERR_LENGTH,
	RESPST_ERR_CQ_OVERFLOW,
	RESPST_ERROR,
	RESPST_RESET,
	RESPST_DONE,
	RESPST_EXIT,
पूर्ण;

अटल अक्षर *resp_state_name[] = अणु
	[RESPST_NONE]				= "NONE",
	[RESPST_GET_REQ]			= "GET_REQ",
	[RESPST_CHK_PSN]			= "CHK_PSN",
	[RESPST_CHK_OP_SEQ]			= "CHK_OP_SEQ",
	[RESPST_CHK_OP_VALID]			= "CHK_OP_VALID",
	[RESPST_CHK_RESOURCE]			= "CHK_RESOURCE",
	[RESPST_CHK_LENGTH]			= "CHK_LENGTH",
	[RESPST_CHK_RKEY]			= "CHK_RKEY",
	[RESPST_EXECUTE]			= "EXECUTE",
	[RESPST_READ_REPLY]			= "READ_REPLY",
	[RESPST_COMPLETE]			= "COMPLETE",
	[RESPST_ACKNOWLEDGE]			= "ACKNOWLEDGE",
	[RESPST_CLEANUP]			= "CLEANUP",
	[RESPST_DUPLICATE_REQUEST]		= "DUPLICATE_REQUEST",
	[RESPST_ERR_MALFORMED_WQE]		= "ERR_MALFORMED_WQE",
	[RESPST_ERR_UNSUPPORTED_OPCODE]		= "ERR_UNSUPPORTED_OPCODE",
	[RESPST_ERR_MISALIGNED_ATOMIC]		= "ERR_MISALIGNED_ATOMIC",
	[RESPST_ERR_PSN_OUT_OF_SEQ]		= "ERR_PSN_OUT_OF_SEQ",
	[RESPST_ERR_MISSING_OPCODE_FIRST]	= "ERR_MISSING_OPCODE_FIRST",
	[RESPST_ERR_MISSING_OPCODE_LAST_C]	= "ERR_MISSING_OPCODE_LAST_C",
	[RESPST_ERR_MISSING_OPCODE_LAST_D1E]	= "ERR_MISSING_OPCODE_LAST_D1E",
	[RESPST_ERR_TOO_MANY_RDMA_ATM_REQ]	= "ERR_TOO_MANY_RDMA_ATM_REQ",
	[RESPST_ERR_RNR]			= "ERR_RNR",
	[RESPST_ERR_RKEY_VIOLATION]		= "ERR_RKEY_VIOLATION",
	[RESPST_ERR_LENGTH]			= "ERR_LENGTH",
	[RESPST_ERR_CQ_OVERFLOW]		= "ERR_CQ_OVERFLOW",
	[RESPST_ERROR]				= "ERROR",
	[RESPST_RESET]				= "RESET",
	[RESPST_DONE]				= "DONE",
	[RESPST_EXIT]				= "EXIT",
पूर्ण;

/* rxe_recv calls here to add a request packet to the input queue */
व्योम rxe_resp_queue_pkt(काष्ठा rxe_qp *qp, काष्ठा sk_buff *skb)
अणु
	पूर्णांक must_sched;
	काष्ठा rxe_pkt_info *pkt = SKB_TO_PKT(skb);

	skb_queue_tail(&qp->req_pkts, skb);

	must_sched = (pkt->opcode == IB_OPCODE_RC_RDMA_READ_REQUEST) ||
			(skb_queue_len(&qp->req_pkts) > 1);

	rxe_run_task(&qp->resp.task, must_sched);
पूर्ण

अटल अंतरभूत क्रमागत resp_states get_req(काष्ठा rxe_qp *qp,
				       काष्ठा rxe_pkt_info **pkt_p)
अणु
	काष्ठा sk_buff *skb;

	अगर (qp->resp.state == QP_STATE_ERROR) अणु
		जबतक ((skb = skb_dequeue(&qp->req_pkts))) अणु
			rxe_drop_ref(qp);
			kमुक्त_skb(skb);
			ib_device_put(qp->ibqp.device);
		पूर्ण

		/* go drain recv wr queue */
		वापस RESPST_CHK_RESOURCE;
	पूर्ण

	skb = skb_peek(&qp->req_pkts);
	अगर (!skb)
		वापस RESPST_EXIT;

	*pkt_p = SKB_TO_PKT(skb);

	वापस (qp->resp.res) ? RESPST_READ_REPLY : RESPST_CHK_PSN;
पूर्ण

अटल क्रमागत resp_states check_psn(काष्ठा rxe_qp *qp,
				  काष्ठा rxe_pkt_info *pkt)
अणु
	पूर्णांक dअगरf = psn_compare(pkt->psn, qp->resp.psn);
	काष्ठा rxe_dev *rxe = to_rdev(qp->ibqp.device);

	चयन (qp_type(qp)) अणु
	हाल IB_QPT_RC:
		अगर (dअगरf > 0) अणु
			अगर (qp->resp.sent_psn_nak)
				वापस RESPST_CLEANUP;

			qp->resp.sent_psn_nak = 1;
			rxe_counter_inc(rxe, RXE_CNT_OUT_OF_SEQ_REQ);
			वापस RESPST_ERR_PSN_OUT_OF_SEQ;

		पूर्ण अन्यथा अगर (dअगरf < 0) अणु
			rxe_counter_inc(rxe, RXE_CNT_DUP_REQ);
			वापस RESPST_DUPLICATE_REQUEST;
		पूर्ण

		अगर (qp->resp.sent_psn_nak)
			qp->resp.sent_psn_nak = 0;

		अवरोध;

	हाल IB_QPT_UC:
		अगर (qp->resp.drop_msg || dअगरf != 0) अणु
			अगर (pkt->mask & RXE_START_MASK) अणु
				qp->resp.drop_msg = 0;
				वापस RESPST_CHK_OP_SEQ;
			पूर्ण

			qp->resp.drop_msg = 1;
			वापस RESPST_CLEANUP;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस RESPST_CHK_OP_SEQ;
पूर्ण

अटल क्रमागत resp_states check_op_seq(काष्ठा rxe_qp *qp,
				     काष्ठा rxe_pkt_info *pkt)
अणु
	चयन (qp_type(qp)) अणु
	हाल IB_QPT_RC:
		चयन (qp->resp.opcode) अणु
		हाल IB_OPCODE_RC_SEND_FIRST:
		हाल IB_OPCODE_RC_SEND_MIDDLE:
			चयन (pkt->opcode) अणु
			हाल IB_OPCODE_RC_SEND_MIDDLE:
			हाल IB_OPCODE_RC_SEND_LAST:
			हाल IB_OPCODE_RC_SEND_LAST_WITH_IMMEDIATE:
			हाल IB_OPCODE_RC_SEND_LAST_WITH_INVALIDATE:
				वापस RESPST_CHK_OP_VALID;
			शेष:
				वापस RESPST_ERR_MISSING_OPCODE_LAST_C;
			पूर्ण

		हाल IB_OPCODE_RC_RDMA_WRITE_FIRST:
		हाल IB_OPCODE_RC_RDMA_WRITE_MIDDLE:
			चयन (pkt->opcode) अणु
			हाल IB_OPCODE_RC_RDMA_WRITE_MIDDLE:
			हाल IB_OPCODE_RC_RDMA_WRITE_LAST:
			हाल IB_OPCODE_RC_RDMA_WRITE_LAST_WITH_IMMEDIATE:
				वापस RESPST_CHK_OP_VALID;
			शेष:
				वापस RESPST_ERR_MISSING_OPCODE_LAST_C;
			पूर्ण

		शेष:
			चयन (pkt->opcode) अणु
			हाल IB_OPCODE_RC_SEND_MIDDLE:
			हाल IB_OPCODE_RC_SEND_LAST:
			हाल IB_OPCODE_RC_SEND_LAST_WITH_IMMEDIATE:
			हाल IB_OPCODE_RC_SEND_LAST_WITH_INVALIDATE:
			हाल IB_OPCODE_RC_RDMA_WRITE_MIDDLE:
			हाल IB_OPCODE_RC_RDMA_WRITE_LAST:
			हाल IB_OPCODE_RC_RDMA_WRITE_LAST_WITH_IMMEDIATE:
				वापस RESPST_ERR_MISSING_OPCODE_FIRST;
			शेष:
				वापस RESPST_CHK_OP_VALID;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल IB_QPT_UC:
		चयन (qp->resp.opcode) अणु
		हाल IB_OPCODE_UC_SEND_FIRST:
		हाल IB_OPCODE_UC_SEND_MIDDLE:
			चयन (pkt->opcode) अणु
			हाल IB_OPCODE_UC_SEND_MIDDLE:
			हाल IB_OPCODE_UC_SEND_LAST:
			हाल IB_OPCODE_UC_SEND_LAST_WITH_IMMEDIATE:
				वापस RESPST_CHK_OP_VALID;
			शेष:
				वापस RESPST_ERR_MISSING_OPCODE_LAST_D1E;
			पूर्ण

		हाल IB_OPCODE_UC_RDMA_WRITE_FIRST:
		हाल IB_OPCODE_UC_RDMA_WRITE_MIDDLE:
			चयन (pkt->opcode) अणु
			हाल IB_OPCODE_UC_RDMA_WRITE_MIDDLE:
			हाल IB_OPCODE_UC_RDMA_WRITE_LAST:
			हाल IB_OPCODE_UC_RDMA_WRITE_LAST_WITH_IMMEDIATE:
				वापस RESPST_CHK_OP_VALID;
			शेष:
				वापस RESPST_ERR_MISSING_OPCODE_LAST_D1E;
			पूर्ण

		शेष:
			चयन (pkt->opcode) अणु
			हाल IB_OPCODE_UC_SEND_MIDDLE:
			हाल IB_OPCODE_UC_SEND_LAST:
			हाल IB_OPCODE_UC_SEND_LAST_WITH_IMMEDIATE:
			हाल IB_OPCODE_UC_RDMA_WRITE_MIDDLE:
			हाल IB_OPCODE_UC_RDMA_WRITE_LAST:
			हाल IB_OPCODE_UC_RDMA_WRITE_LAST_WITH_IMMEDIATE:
				qp->resp.drop_msg = 1;
				वापस RESPST_CLEANUP;
			शेष:
				वापस RESPST_CHK_OP_VALID;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		वापस RESPST_CHK_OP_VALID;
	पूर्ण
पूर्ण

अटल क्रमागत resp_states check_op_valid(काष्ठा rxe_qp *qp,
				       काष्ठा rxe_pkt_info *pkt)
अणु
	चयन (qp_type(qp)) अणु
	हाल IB_QPT_RC:
		अगर (((pkt->mask & RXE_READ_MASK) &&
		     !(qp->attr.qp_access_flags & IB_ACCESS_REMOTE_READ)) ||
		    ((pkt->mask & RXE_WRITE_MASK) &&
		     !(qp->attr.qp_access_flags & IB_ACCESS_REMOTE_WRITE)) ||
		    ((pkt->mask & RXE_ATOMIC_MASK) &&
		     !(qp->attr.qp_access_flags & IB_ACCESS_REMOTE_ATOMIC))) अणु
			वापस RESPST_ERR_UNSUPPORTED_OPCODE;
		पूर्ण

		अवरोध;

	हाल IB_QPT_UC:
		अगर ((pkt->mask & RXE_WRITE_MASK) &&
		    !(qp->attr.qp_access_flags & IB_ACCESS_REMOTE_WRITE)) अणु
			qp->resp.drop_msg = 1;
			वापस RESPST_CLEANUP;
		पूर्ण

		अवरोध;

	हाल IB_QPT_UD:
	हाल IB_QPT_SMI:
	हाल IB_QPT_GSI:
		अवरोध;

	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस RESPST_CHK_RESOURCE;
पूर्ण

अटल क्रमागत resp_states get_srq_wqe(काष्ठा rxe_qp *qp)
अणु
	काष्ठा rxe_srq *srq = qp->srq;
	काष्ठा rxe_queue *q = srq->rq.queue;
	काष्ठा rxe_recv_wqe *wqe;
	काष्ठा ib_event ev;

	अगर (srq->error)
		वापस RESPST_ERR_RNR;

	spin_lock_bh(&srq->rq.consumer_lock);

	wqe = queue_head(q);
	अगर (!wqe) अणु
		spin_unlock_bh(&srq->rq.consumer_lock);
		वापस RESPST_ERR_RNR;
	पूर्ण

	/* note kernel and user space recv wqes have same size */
	स_नकल(&qp->resp.srq_wqe, wqe, माप(qp->resp.srq_wqe));

	qp->resp.wqe = &qp->resp.srq_wqe.wqe;
	advance_consumer(q);

	अगर (srq->limit && srq->ibsrq.event_handler &&
	    (queue_count(q) < srq->limit)) अणु
		srq->limit = 0;
		जाओ event;
	पूर्ण

	spin_unlock_bh(&srq->rq.consumer_lock);
	वापस RESPST_CHK_LENGTH;

event:
	spin_unlock_bh(&srq->rq.consumer_lock);
	ev.device = qp->ibqp.device;
	ev.element.srq = qp->ibqp.srq;
	ev.event = IB_EVENT_SRQ_LIMIT_REACHED;
	srq->ibsrq.event_handler(&ev, srq->ibsrq.srq_context);
	वापस RESPST_CHK_LENGTH;
पूर्ण

अटल क्रमागत resp_states check_resource(काष्ठा rxe_qp *qp,
				       काष्ठा rxe_pkt_info *pkt)
अणु
	काष्ठा rxe_srq *srq = qp->srq;

	अगर (qp->resp.state == QP_STATE_ERROR) अणु
		अगर (qp->resp.wqe) अणु
			qp->resp.status = IB_WC_WR_FLUSH_ERR;
			वापस RESPST_COMPLETE;
		पूर्ण अन्यथा अगर (!srq) अणु
			qp->resp.wqe = queue_head(qp->rq.queue);
			अगर (qp->resp.wqe) अणु
				qp->resp.status = IB_WC_WR_FLUSH_ERR;
				वापस RESPST_COMPLETE;
			पूर्ण अन्यथा अणु
				वापस RESPST_EXIT;
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस RESPST_EXIT;
		पूर्ण
	पूर्ण

	अगर (pkt->mask & RXE_READ_OR_ATOMIC) अणु
		/* it is the requesters job to not send
		 * too many पढ़ो/atomic ops, we just
		 * recycle the responder resource queue
		 */
		अगर (likely(qp->attr.max_dest_rd_atomic > 0))
			वापस RESPST_CHK_LENGTH;
		अन्यथा
			वापस RESPST_ERR_TOO_MANY_RDMA_ATM_REQ;
	पूर्ण

	अगर (pkt->mask & RXE_RWR_MASK) अणु
		अगर (srq)
			वापस get_srq_wqe(qp);

		qp->resp.wqe = queue_head(qp->rq.queue);
		वापस (qp->resp.wqe) ? RESPST_CHK_LENGTH : RESPST_ERR_RNR;
	पूर्ण

	वापस RESPST_CHK_LENGTH;
पूर्ण

अटल क्रमागत resp_states check_length(काष्ठा rxe_qp *qp,
				     काष्ठा rxe_pkt_info *pkt)
अणु
	चयन (qp_type(qp)) अणु
	हाल IB_QPT_RC:
		वापस RESPST_CHK_RKEY;

	हाल IB_QPT_UC:
		वापस RESPST_CHK_RKEY;

	शेष:
		वापस RESPST_CHK_RKEY;
	पूर्ण
पूर्ण

अटल क्रमागत resp_states check_rkey(काष्ठा rxe_qp *qp,
				   काष्ठा rxe_pkt_info *pkt)
अणु
	काष्ठा rxe_mr *mr = शून्य;
	u64 va;
	u32 rkey;
	u32 resid;
	u32 pktlen;
	पूर्णांक mtu = qp->mtu;
	क्रमागत resp_states state;
	पूर्णांक access;

	अगर (pkt->mask & (RXE_READ_MASK | RXE_WRITE_MASK)) अणु
		अगर (pkt->mask & RXE_RETH_MASK) अणु
			qp->resp.va = reth_va(pkt);
			qp->resp.rkey = reth_rkey(pkt);
			qp->resp.resid = reth_len(pkt);
			qp->resp.length = reth_len(pkt);
		पूर्ण
		access = (pkt->mask & RXE_READ_MASK) ? IB_ACCESS_REMOTE_READ
						     : IB_ACCESS_REMOTE_WRITE;
	पूर्ण अन्यथा अगर (pkt->mask & RXE_ATOMIC_MASK) अणु
		qp->resp.va = aपंचांगeth_va(pkt);
		qp->resp.rkey = aपंचांगeth_rkey(pkt);
		qp->resp.resid = माप(u64);
		access = IB_ACCESS_REMOTE_ATOMIC;
	पूर्ण अन्यथा अणु
		वापस RESPST_EXECUTE;
	पूर्ण

	/* A zero-byte op is not required to set an addr or rkey. */
	अगर ((pkt->mask & (RXE_READ_MASK | RXE_WRITE_OR_SEND)) &&
	    (pkt->mask & RXE_RETH_MASK) &&
	    reth_len(pkt) == 0) अणु
		वापस RESPST_EXECUTE;
	पूर्ण

	va	= qp->resp.va;
	rkey	= qp->resp.rkey;
	resid	= qp->resp.resid;
	pktlen	= payload_size(pkt);

	mr = lookup_mr(qp->pd, access, rkey, lookup_remote);
	अगर (!mr) अणु
		state = RESPST_ERR_RKEY_VIOLATION;
		जाओ err;
	पूर्ण

	अगर (unlikely(mr->state == RXE_MR_STATE_FREE)) अणु
		state = RESPST_ERR_RKEY_VIOLATION;
		जाओ err;
	पूर्ण

	अगर (mr_check_range(mr, va, resid)) अणु
		state = RESPST_ERR_RKEY_VIOLATION;
		जाओ err;
	पूर्ण

	अगर (pkt->mask & RXE_WRITE_MASK)	 अणु
		अगर (resid > mtu) अणु
			अगर (pktlen != mtu || bth_pad(pkt)) अणु
				state = RESPST_ERR_LENGTH;
				जाओ err;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (pktlen != resid) अणु
				state = RESPST_ERR_LENGTH;
				जाओ err;
			पूर्ण
			अगर ((bth_pad(pkt) != (0x3 & (-resid)))) अणु
				/* This हाल may not be exactly that
				 * but nothing अन्यथा fits.
				 */
				state = RESPST_ERR_LENGTH;
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	WARN_ON_ONCE(qp->resp.mr);

	qp->resp.mr = mr;
	वापस RESPST_EXECUTE;

err:
	अगर (mr)
		rxe_drop_ref(mr);
	वापस state;
पूर्ण

अटल क्रमागत resp_states send_data_in(काष्ठा rxe_qp *qp, व्योम *data_addr,
				     पूर्णांक data_len)
अणु
	पूर्णांक err;

	err = copy_data(qp->pd, IB_ACCESS_LOCAL_WRITE, &qp->resp.wqe->dma,
			data_addr, data_len, to_mr_obj, शून्य);
	अगर (unlikely(err))
		वापस (err == -ENOSPC) ? RESPST_ERR_LENGTH
					: RESPST_ERR_MALFORMED_WQE;

	वापस RESPST_NONE;
पूर्ण

अटल क्रमागत resp_states ग_लिखो_data_in(काष्ठा rxe_qp *qp,
				      काष्ठा rxe_pkt_info *pkt)
अणु
	क्रमागत resp_states rc = RESPST_NONE;
	पूर्णांक	err;
	पूर्णांक data_len = payload_size(pkt);

	err = rxe_mr_copy(qp->resp.mr, qp->resp.va, payload_addr(pkt), data_len,
			  to_mr_obj, शून्य);
	अगर (err) अणु
		rc = RESPST_ERR_RKEY_VIOLATION;
		जाओ out;
	पूर्ण

	qp->resp.va += data_len;
	qp->resp.resid -= data_len;

out:
	वापस rc;
पूर्ण

/* Guarantee atomicity of atomic operations at the machine level. */
अटल DEFINE_SPINLOCK(atomic_ops_lock);

अटल क्रमागत resp_states process_atomic(काष्ठा rxe_qp *qp,
				       काष्ठा rxe_pkt_info *pkt)
अणु
	u64 iova = aपंचांगeth_va(pkt);
	u64 *vaddr;
	क्रमागत resp_states ret;
	काष्ठा rxe_mr *mr = qp->resp.mr;

	अगर (mr->state != RXE_MR_STATE_VALID) अणु
		ret = RESPST_ERR_RKEY_VIOLATION;
		जाओ out;
	पूर्ण

	vaddr = iova_to_vaddr(mr, iova, माप(u64));

	/* check vaddr is 8 bytes aligned. */
	अगर (!vaddr || (uपूर्णांकptr_t)vaddr & 7) अणु
		ret = RESPST_ERR_MISALIGNED_ATOMIC;
		जाओ out;
	पूर्ण

	spin_lock_bh(&atomic_ops_lock);

	qp->resp.atomic_orig = *vaddr;

	अगर (pkt->opcode == IB_OPCODE_RC_COMPARE_SWAP ||
	    pkt->opcode == IB_OPCODE_RD_COMPARE_SWAP) अणु
		अगर (*vaddr == aपंचांगeth_comp(pkt))
			*vaddr = aपंचांगeth_swap_add(pkt);
	पूर्ण अन्यथा अणु
		*vaddr += aपंचांगeth_swap_add(pkt);
	पूर्ण

	spin_unlock_bh(&atomic_ops_lock);

	ret = RESPST_NONE;
out:
	वापस ret;
पूर्ण

अटल काष्ठा sk_buff *prepare_ack_packet(काष्ठा rxe_qp *qp,
					  काष्ठा rxe_pkt_info *pkt,
					  काष्ठा rxe_pkt_info *ack,
					  पूर्णांक opcode,
					  पूर्णांक payload,
					  u32 psn,
					  u8 syndrome,
					  u32 *crcp)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(qp->ibqp.device);
	काष्ठा sk_buff *skb;
	u32 crc = 0;
	u32 *p;
	पूर्णांक paylen;
	पूर्णांक pad;
	पूर्णांक err;

	/*
	 * allocate packet
	 */
	pad = (-payload) & 0x3;
	paylen = rxe_opcode[opcode].length + payload + pad + RXE_ICRC_SIZE;

	skb = rxe_init_packet(rxe, &qp->pri_av, paylen, ack);
	अगर (!skb)
		वापस शून्य;

	ack->qp = qp;
	ack->opcode = opcode;
	ack->mask = rxe_opcode[opcode].mask;
	ack->paylen = paylen;

	/* fill in bth using the request packet headers */
	स_नकल(ack->hdr, pkt->hdr, RXE_BTH_BYTES);

	bth_set_opcode(ack, opcode);
	bth_set_qpn(ack, qp->attr.dest_qp_num);
	bth_set_pad(ack, pad);
	bth_set_se(ack, 0);
	bth_set_psn(ack, psn);
	bth_set_ack(ack, 0);
	ack->psn = psn;

	अगर (ack->mask & RXE_AETH_MASK) अणु
		aeth_set_syn(ack, syndrome);
		aeth_set_msn(ack, qp->resp.msn);
	पूर्ण

	अगर (ack->mask & RXE_ATMACK_MASK)
		aपंचांगack_set_orig(ack, qp->resp.atomic_orig);

	err = rxe_prepare(ack, skb, &crc);
	अगर (err) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	अगर (crcp) अणु
		/* CRC computation will be जारीd by the caller */
		*crcp = crc;
	पूर्ण अन्यथा अणु
		p = payload_addr(ack) + payload + bth_pad(ack);
		*p = ~crc;
	पूर्ण

	वापस skb;
पूर्ण

/* RDMA पढ़ो response. If res is not शून्य, then we have a current RDMA request
 * being processed or replayed.
 */
अटल क्रमागत resp_states पढ़ो_reply(काष्ठा rxe_qp *qp,
				   काष्ठा rxe_pkt_info *req_pkt)
अणु
	काष्ठा rxe_pkt_info ack_pkt;
	काष्ठा sk_buff *skb;
	पूर्णांक mtu = qp->mtu;
	क्रमागत resp_states state;
	पूर्णांक payload;
	पूर्णांक opcode;
	पूर्णांक err;
	काष्ठा resp_res *res = qp->resp.res;
	u32 icrc;
	u32 *p;

	अगर (!res) अणु
		/* This is the first समय we process that request. Get a
		 * resource
		 */
		res = &qp->resp.resources[qp->resp.res_head];

		मुक्त_rd_atomic_resource(qp, res);
		rxe_advance_resp_resource(qp);

		res->type		= RXE_READ_MASK;
		res->replay		= 0;

		res->पढ़ो.va		= qp->resp.va;
		res->पढ़ो.va_org	= qp->resp.va;

		res->first_psn		= req_pkt->psn;

		अगर (reth_len(req_pkt)) अणु
			res->last_psn	= (req_pkt->psn +
					   (reth_len(req_pkt) + mtu - 1) /
					   mtu - 1) & BTH_PSN_MASK;
		पूर्ण अन्यथा अणु
			res->last_psn	= res->first_psn;
		पूर्ण
		res->cur_psn		= req_pkt->psn;

		res->पढ़ो.resid		= qp->resp.resid;
		res->पढ़ो.length	= qp->resp.resid;
		res->पढ़ो.rkey		= qp->resp.rkey;

		/* note res inherits the reference to mr from qp */
		res->पढ़ो.mr		= qp->resp.mr;
		qp->resp.mr		= शून्य;

		qp->resp.res		= res;
		res->state		= rdaपंचांग_res_state_new;
	पूर्ण

	अगर (res->state == rdaपंचांग_res_state_new) अणु
		अगर (res->पढ़ो.resid <= mtu)
			opcode = IB_OPCODE_RC_RDMA_READ_RESPONSE_ONLY;
		अन्यथा
			opcode = IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST;
	पूर्ण अन्यथा अणु
		अगर (res->पढ़ो.resid > mtu)
			opcode = IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE;
		अन्यथा
			opcode = IB_OPCODE_RC_RDMA_READ_RESPONSE_LAST;
	पूर्ण

	res->state = rdaपंचांग_res_state_next;

	payload = min_t(पूर्णांक, res->पढ़ो.resid, mtu);

	skb = prepare_ack_packet(qp, req_pkt, &ack_pkt, opcode, payload,
				 res->cur_psn, AETH_ACK_UNLIMITED, &icrc);
	अगर (!skb)
		वापस RESPST_ERR_RNR;

	err = rxe_mr_copy(res->पढ़ो.mr, res->पढ़ो.va, payload_addr(&ack_pkt),
			  payload, from_mr_obj, &icrc);
	अगर (err)
		pr_err("Failed copying memory\n");

	अगर (bth_pad(&ack_pkt)) अणु
		काष्ठा rxe_dev *rxe = to_rdev(qp->ibqp.device);
		u8 *pad = payload_addr(&ack_pkt) + payload;

		स_रखो(pad, 0, bth_pad(&ack_pkt));
		icrc = rxe_crc32(rxe, icrc, pad, bth_pad(&ack_pkt));
	पूर्ण
	p = payload_addr(&ack_pkt) + payload + bth_pad(&ack_pkt);
	*p = ~icrc;

	err = rxe_xmit_packet(qp, &ack_pkt, skb);
	अगर (err) अणु
		pr_err("Failed sending RDMA reply.\n");
		वापस RESPST_ERR_RNR;
	पूर्ण

	res->पढ़ो.va += payload;
	res->पढ़ो.resid -= payload;
	res->cur_psn = (res->cur_psn + 1) & BTH_PSN_MASK;

	अगर (res->पढ़ो.resid > 0) अणु
		state = RESPST_DONE;
	पूर्ण अन्यथा अणु
		qp->resp.res = शून्य;
		अगर (!res->replay)
			qp->resp.opcode = -1;
		अगर (psn_compare(res->cur_psn, qp->resp.psn) >= 0)
			qp->resp.psn = res->cur_psn;
		state = RESPST_CLEANUP;
	पूर्ण

	वापस state;
पूर्ण

अटल व्योम build_rdma_network_hdr(जोड़ rdma_network_hdr *hdr,
				   काष्ठा rxe_pkt_info *pkt)
अणु
	काष्ठा sk_buff *skb = PKT_TO_SKB(pkt);

	स_रखो(hdr, 0, माप(*hdr));
	अगर (skb->protocol == htons(ETH_P_IP))
		स_नकल(&hdr->roce4grh, ip_hdr(skb), माप(hdr->roce4grh));
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		स_नकल(&hdr->ibgrh, ipv6_hdr(skb), माप(hdr->ibgrh));
पूर्ण

/* Executes a new request. A retried request never reach that function (send
 * and ग_लिखोs are discarded, and पढ़ोs and atomics are retried अन्यथाwhere.
 */
अटल क्रमागत resp_states execute(काष्ठा rxe_qp *qp, काष्ठा rxe_pkt_info *pkt)
अणु
	क्रमागत resp_states err;

	अगर (pkt->mask & RXE_SEND_MASK) अणु
		अगर (qp_type(qp) == IB_QPT_UD ||
		    qp_type(qp) == IB_QPT_SMI ||
		    qp_type(qp) == IB_QPT_GSI) अणु
			जोड़ rdma_network_hdr hdr;

			build_rdma_network_hdr(&hdr, pkt);

			err = send_data_in(qp, &hdr, माप(hdr));
			अगर (err)
				वापस err;
		पूर्ण
		err = send_data_in(qp, payload_addr(pkt), payload_size(pkt));
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (pkt->mask & RXE_WRITE_MASK) अणु
		err = ग_लिखो_data_in(qp, pkt);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (pkt->mask & RXE_READ_MASK) अणु
		/* For RDMA Read we can increment the msn now. See C9-148. */
		qp->resp.msn++;
		वापस RESPST_READ_REPLY;
	पूर्ण अन्यथा अगर (pkt->mask & RXE_ATOMIC_MASK) अणु
		err = process_atomic(qp, pkt);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		/* Unreachable */
		WARN_ON_ONCE(1);
	पूर्ण

	/* next expected psn, पढ़ो handles this separately */
	qp->resp.psn = (pkt->psn + 1) & BTH_PSN_MASK;
	qp->resp.ack_psn = qp->resp.psn;

	qp->resp.opcode = pkt->opcode;
	qp->resp.status = IB_WC_SUCCESS;

	अगर (pkt->mask & RXE_COMP_MASK) अणु
		/* We successfully processed this new request. */
		qp->resp.msn++;
		वापस RESPST_COMPLETE;
	पूर्ण अन्यथा अगर (qp_type(qp) == IB_QPT_RC)
		वापस RESPST_ACKNOWLEDGE;
	अन्यथा
		वापस RESPST_CLEANUP;
पूर्ण

अटल क्रमागत resp_states करो_complete(काष्ठा rxe_qp *qp,
				    काष्ठा rxe_pkt_info *pkt)
अणु
	काष्ठा rxe_cqe cqe;
	काष्ठा ib_wc *wc = &cqe.ibwc;
	काष्ठा ib_uverbs_wc *uwc = &cqe.uibwc;
	काष्ठा rxe_recv_wqe *wqe = qp->resp.wqe;
	काष्ठा rxe_dev *rxe = to_rdev(qp->ibqp.device);

	अगर (!wqe)
		जाओ finish;

	स_रखो(&cqe, 0, माप(cqe));

	अगर (qp->rcq->is_user) अणु
		uwc->status             = qp->resp.status;
		uwc->qp_num             = qp->ibqp.qp_num;
		uwc->wr_id              = wqe->wr_id;
	पूर्ण अन्यथा अणु
		wc->status              = qp->resp.status;
		wc->qp                  = &qp->ibqp;
		wc->wr_id               = wqe->wr_id;
	पूर्ण

	अगर (wc->status == IB_WC_SUCCESS) अणु
		rxe_counter_inc(rxe, RXE_CNT_RDMA_RECV);
		wc->opcode = (pkt->mask & RXE_IMMDT_MASK &&
				pkt->mask & RXE_WRITE_MASK) ?
					IB_WC_RECV_RDMA_WITH_IMM : IB_WC_RECV;
		wc->venकरोr_err = 0;
		wc->byte_len = (pkt->mask & RXE_IMMDT_MASK &&
				pkt->mask & RXE_WRITE_MASK) ?
					qp->resp.length : wqe->dma.length - wqe->dma.resid;

		/* fields after byte_len are dअगरferent between kernel and user
		 * space
		 */
		अगर (qp->rcq->is_user) अणु
			uwc->wc_flags = IB_WC_GRH;

			अगर (pkt->mask & RXE_IMMDT_MASK) अणु
				uwc->wc_flags |= IB_WC_WITH_IMM;
				uwc->ex.imm_data = immdt_imm(pkt);
			पूर्ण

			अगर (pkt->mask & RXE_IETH_MASK) अणु
				uwc->wc_flags |= IB_WC_WITH_INVALIDATE;
				uwc->ex.invalidate_rkey = ieth_rkey(pkt);
			पूर्ण

			uwc->qp_num		= qp->ibqp.qp_num;

			अगर (pkt->mask & RXE_DETH_MASK)
				uwc->src_qp = deth_sqp(pkt);

			uwc->port_num		= qp->attr.port_num;
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *skb = PKT_TO_SKB(pkt);

			wc->wc_flags = IB_WC_GRH | IB_WC_WITH_NETWORK_HDR_TYPE;
			अगर (skb->protocol == htons(ETH_P_IP))
				wc->network_hdr_type = RDMA_NETWORK_IPV4;
			अन्यथा
				wc->network_hdr_type = RDMA_NETWORK_IPV6;

			अगर (is_vlan_dev(skb->dev)) अणु
				wc->wc_flags |= IB_WC_WITH_VLAN;
				wc->vlan_id = vlan_dev_vlan_id(skb->dev);
			पूर्ण

			अगर (pkt->mask & RXE_IMMDT_MASK) अणु
				wc->wc_flags |= IB_WC_WITH_IMM;
				wc->ex.imm_data = immdt_imm(pkt);
			पूर्ण

			अगर (pkt->mask & RXE_IETH_MASK) अणु
				काष्ठा rxe_mr *rmr;

				wc->wc_flags |= IB_WC_WITH_INVALIDATE;
				wc->ex.invalidate_rkey = ieth_rkey(pkt);

				rmr = rxe_pool_get_index(&rxe->mr_pool,
							 wc->ex.invalidate_rkey >> 8);
				अगर (unlikely(!rmr)) अणु
					pr_err("Bad rkey %#x invalidation\n",
					       wc->ex.invalidate_rkey);
					वापस RESPST_ERROR;
				पूर्ण
				rmr->state = RXE_MR_STATE_FREE;
				rxe_drop_ref(rmr);
			पूर्ण

			wc->qp			= &qp->ibqp;

			अगर (pkt->mask & RXE_DETH_MASK)
				wc->src_qp = deth_sqp(pkt);

			wc->port_num		= qp->attr.port_num;
		पूर्ण
	पूर्ण

	/* have copy क्रम srq and reference क्रम !srq */
	अगर (!qp->srq)
		advance_consumer(qp->rq.queue);

	qp->resp.wqe = शून्य;

	अगर (rxe_cq_post(qp->rcq, &cqe, pkt ? bth_se(pkt) : 1))
		वापस RESPST_ERR_CQ_OVERFLOW;

finish:
	अगर (unlikely(qp->resp.state == QP_STATE_ERROR))
		वापस RESPST_CHK_RESOURCE;
	अगर (unlikely(!pkt))
		वापस RESPST_DONE;
	अगर (qp_type(qp) == IB_QPT_RC)
		वापस RESPST_ACKNOWLEDGE;
	अन्यथा
		वापस RESPST_CLEANUP;
पूर्ण

अटल पूर्णांक send_ack(काष्ठा rxe_qp *qp, काष्ठा rxe_pkt_info *pkt,
		    u8 syndrome, u32 psn)
अणु
	पूर्णांक err = 0;
	काष्ठा rxe_pkt_info ack_pkt;
	काष्ठा sk_buff *skb;

	skb = prepare_ack_packet(qp, pkt, &ack_pkt, IB_OPCODE_RC_ACKNOWLEDGE,
				 0, psn, syndrome, शून्य);
	अगर (!skb) अणु
		err = -ENOMEM;
		जाओ err1;
	पूर्ण

	err = rxe_xmit_packet(qp, &ack_pkt, skb);
	अगर (err)
		pr_err_ratelimited("Failed sending ack\n");

err1:
	वापस err;
पूर्ण

अटल पूर्णांक send_atomic_ack(काष्ठा rxe_qp *qp, काष्ठा rxe_pkt_info *pkt,
			   u8 syndrome)
अणु
	पूर्णांक rc = 0;
	काष्ठा rxe_pkt_info ack_pkt;
	काष्ठा sk_buff *skb;
	काष्ठा resp_res *res;

	skb = prepare_ack_packet(qp, pkt, &ack_pkt,
				 IB_OPCODE_RC_ATOMIC_ACKNOWLEDGE, 0, pkt->psn,
				 syndrome, शून्य);
	अगर (!skb) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	rxe_add_ref(qp);

	res = &qp->resp.resources[qp->resp.res_head];
	मुक्त_rd_atomic_resource(qp, res);
	rxe_advance_resp_resource(qp);

	स_नकल(SKB_TO_PKT(skb), &ack_pkt, माप(ack_pkt));
	स_रखो((अचिन्हित अक्षर *)SKB_TO_PKT(skb) + माप(ack_pkt), 0,
	       माप(skb->cb) - माप(ack_pkt));

	skb_get(skb);
	res->type = RXE_ATOMIC_MASK;
	res->atomic.skb = skb;
	res->first_psn = ack_pkt.psn;
	res->last_psn  = ack_pkt.psn;
	res->cur_psn   = ack_pkt.psn;

	rc = rxe_xmit_packet(qp, &ack_pkt, skb);
	अगर (rc) अणु
		pr_err_ratelimited("Failed sending ack\n");
		rxe_drop_ref(qp);
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल क्रमागत resp_states acknowledge(काष्ठा rxe_qp *qp,
				    काष्ठा rxe_pkt_info *pkt)
अणु
	अगर (qp_type(qp) != IB_QPT_RC)
		वापस RESPST_CLEANUP;

	अगर (qp->resp.aeth_syndrome != AETH_ACK_UNLIMITED)
		send_ack(qp, pkt, qp->resp.aeth_syndrome, pkt->psn);
	अन्यथा अगर (pkt->mask & RXE_ATOMIC_MASK)
		send_atomic_ack(qp, pkt, AETH_ACK_UNLIMITED);
	अन्यथा अगर (bth_ack(pkt))
		send_ack(qp, pkt, AETH_ACK_UNLIMITED, pkt->psn);

	वापस RESPST_CLEANUP;
पूर्ण

अटल क्रमागत resp_states cleanup(काष्ठा rxe_qp *qp,
				काष्ठा rxe_pkt_info *pkt)
अणु
	काष्ठा sk_buff *skb;

	अगर (pkt) अणु
		skb = skb_dequeue(&qp->req_pkts);
		rxe_drop_ref(qp);
		kमुक्त_skb(skb);
		ib_device_put(qp->ibqp.device);
	पूर्ण

	अगर (qp->resp.mr) अणु
		rxe_drop_ref(qp->resp.mr);
		qp->resp.mr = शून्य;
	पूर्ण

	वापस RESPST_DONE;
पूर्ण

अटल काष्ठा resp_res *find_resource(काष्ठा rxe_qp *qp, u32 psn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < qp->attr.max_dest_rd_atomic; i++) अणु
		काष्ठा resp_res *res = &qp->resp.resources[i];

		अगर (res->type == 0)
			जारी;

		अगर (psn_compare(psn, res->first_psn) >= 0 &&
		    psn_compare(psn, res->last_psn) <= 0) अणु
			वापस res;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत resp_states duplicate_request(काष्ठा rxe_qp *qp,
					  काष्ठा rxe_pkt_info *pkt)
अणु
	क्रमागत resp_states rc;
	u32 prev_psn = (qp->resp.ack_psn - 1) & BTH_PSN_MASK;

	अगर (pkt->mask & RXE_SEND_MASK ||
	    pkt->mask & RXE_WRITE_MASK) अणु
		/* SEND. Ack again and cleanup. C9-105. */
		send_ack(qp, pkt, AETH_ACK_UNLIMITED, prev_psn);
		वापस RESPST_CLEANUP;
	पूर्ण अन्यथा अगर (pkt->mask & RXE_READ_MASK) अणु
		काष्ठा resp_res *res;

		res = find_resource(qp, pkt->psn);
		अगर (!res) अणु
			/* Resource not found. Class D error.  Drop the
			 * request.
			 */
			rc = RESPST_CLEANUP;
			जाओ out;
		पूर्ण अन्यथा अणु
			/* Ensure this new request is the same as the previous
			 * one or a subset of it.
			 */
			u64 iova = reth_va(pkt);
			u32 resid = reth_len(pkt);

			अगर (iova < res->पढ़ो.va_org ||
			    resid > res->पढ़ो.length ||
			    (iova + resid) > (res->पढ़ो.va_org +
					      res->पढ़ो.length)) अणु
				rc = RESPST_CLEANUP;
				जाओ out;
			पूर्ण

			अगर (reth_rkey(pkt) != res->पढ़ो.rkey) अणु
				rc = RESPST_CLEANUP;
				जाओ out;
			पूर्ण

			res->cur_psn = pkt->psn;
			res->state = (pkt->psn == res->first_psn) ?
					rdaपंचांग_res_state_new :
					rdaपंचांग_res_state_replay;
			res->replay = 1;

			/* Reset the resource, except length. */
			res->पढ़ो.va_org = iova;
			res->पढ़ो.va = iova;
			res->पढ़ो.resid = resid;

			/* Replay the RDMA पढ़ो reply. */
			qp->resp.res = res;
			rc = RESPST_READ_REPLY;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा resp_res *res;

		/* Find the operation in our list of responder resources. */
		res = find_resource(qp, pkt->psn);
		अगर (res) अणु
			skb_get(res->atomic.skb);
			/* Resend the result. */
			rc = rxe_xmit_packet(qp, pkt, res->atomic.skb);
			अगर (rc) अणु
				pr_err("Failed resending result. This flow is not handled - skb ignored\n");
				rc = RESPST_CLEANUP;
				जाओ out;
			पूर्ण
		पूर्ण

		/* Resource not found. Class D error. Drop the request. */
		rc = RESPST_CLEANUP;
		जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

/* Process a class A or C. Both are treated the same in this implementation. */
अटल व्योम करो_class_ac_error(काष्ठा rxe_qp *qp, u8 syndrome,
			      क्रमागत ib_wc_status status)
अणु
	qp->resp.aeth_syndrome	= syndrome;
	qp->resp.status		= status;

	/* indicate that we should go through the ERROR state */
	qp->resp.जाओ_error	= 1;
पूर्ण

अटल क्रमागत resp_states करो_class_d1e_error(काष्ठा rxe_qp *qp)
अणु
	/* UC */
	अगर (qp->srq) अणु
		/* Class E */
		qp->resp.drop_msg = 1;
		अगर (qp->resp.wqe) अणु
			qp->resp.status = IB_WC_REM_INV_REQ_ERR;
			वापस RESPST_COMPLETE;
		पूर्ण अन्यथा अणु
			वापस RESPST_CLEANUP;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Class D1. This packet may be the start of a
		 * new message and could be valid. The previous
		 * message is invalid and ignored. reset the
		 * recv wr to its original state
		 */
		अगर (qp->resp.wqe) अणु
			qp->resp.wqe->dma.resid = qp->resp.wqe->dma.length;
			qp->resp.wqe->dma.cur_sge = 0;
			qp->resp.wqe->dma.sge_offset = 0;
			qp->resp.opcode = -1;
		पूर्ण

		अगर (qp->resp.mr) अणु
			rxe_drop_ref(qp->resp.mr);
			qp->resp.mr = शून्य;
		पूर्ण

		वापस RESPST_CLEANUP;
	पूर्ण
पूर्ण

अटल व्योम rxe_drain_req_pkts(काष्ठा rxe_qp *qp, bool notअगरy)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&qp->req_pkts))) अणु
		rxe_drop_ref(qp);
		kमुक्त_skb(skb);
		ib_device_put(qp->ibqp.device);
	पूर्ण

	अगर (notअगरy)
		वापस;

	जबतक (!qp->srq && qp->rq.queue && queue_head(qp->rq.queue))
		advance_consumer(qp->rq.queue);
पूर्ण

पूर्णांक rxe_responder(व्योम *arg)
अणु
	काष्ठा rxe_qp *qp = (काष्ठा rxe_qp *)arg;
	काष्ठा rxe_dev *rxe = to_rdev(qp->ibqp.device);
	क्रमागत resp_states state;
	काष्ठा rxe_pkt_info *pkt = शून्य;
	पूर्णांक ret = 0;

	rxe_add_ref(qp);

	qp->resp.aeth_syndrome = AETH_ACK_UNLIMITED;

	अगर (!qp->valid) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	चयन (qp->resp.state) अणु
	हाल QP_STATE_RESET:
		state = RESPST_RESET;
		अवरोध;

	शेष:
		state = RESPST_GET_REQ;
		अवरोध;
	पूर्ण

	जबतक (1) अणु
		pr_debug("qp#%d state = %s\n", qp_num(qp),
			 resp_state_name[state]);
		चयन (state) अणु
		हाल RESPST_GET_REQ:
			state = get_req(qp, &pkt);
			अवरोध;
		हाल RESPST_CHK_PSN:
			state = check_psn(qp, pkt);
			अवरोध;
		हाल RESPST_CHK_OP_SEQ:
			state = check_op_seq(qp, pkt);
			अवरोध;
		हाल RESPST_CHK_OP_VALID:
			state = check_op_valid(qp, pkt);
			अवरोध;
		हाल RESPST_CHK_RESOURCE:
			state = check_resource(qp, pkt);
			अवरोध;
		हाल RESPST_CHK_LENGTH:
			state = check_length(qp, pkt);
			अवरोध;
		हाल RESPST_CHK_RKEY:
			state = check_rkey(qp, pkt);
			अवरोध;
		हाल RESPST_EXECUTE:
			state = execute(qp, pkt);
			अवरोध;
		हाल RESPST_COMPLETE:
			state = करो_complete(qp, pkt);
			अवरोध;
		हाल RESPST_READ_REPLY:
			state = पढ़ो_reply(qp, pkt);
			अवरोध;
		हाल RESPST_ACKNOWLEDGE:
			state = acknowledge(qp, pkt);
			अवरोध;
		हाल RESPST_CLEANUP:
			state = cleanup(qp, pkt);
			अवरोध;
		हाल RESPST_DUPLICATE_REQUEST:
			state = duplicate_request(qp, pkt);
			अवरोध;
		हाल RESPST_ERR_PSN_OUT_OF_SEQ:
			/* RC only - Class B. Drop packet. */
			send_ack(qp, pkt, AETH_NAK_PSN_SEQ_ERROR, qp->resp.psn);
			state = RESPST_CLEANUP;
			अवरोध;

		हाल RESPST_ERR_TOO_MANY_RDMA_ATM_REQ:
		हाल RESPST_ERR_MISSING_OPCODE_FIRST:
		हाल RESPST_ERR_MISSING_OPCODE_LAST_C:
		हाल RESPST_ERR_UNSUPPORTED_OPCODE:
		हाल RESPST_ERR_MISALIGNED_ATOMIC:
			/* RC Only - Class C. */
			करो_class_ac_error(qp, AETH_NAK_INVALID_REQ,
					  IB_WC_REM_INV_REQ_ERR);
			state = RESPST_COMPLETE;
			अवरोध;

		हाल RESPST_ERR_MISSING_OPCODE_LAST_D1E:
			state = करो_class_d1e_error(qp);
			अवरोध;
		हाल RESPST_ERR_RNR:
			अगर (qp_type(qp) == IB_QPT_RC) अणु
				rxe_counter_inc(rxe, RXE_CNT_SND_RNR);
				/* RC - class B */
				send_ack(qp, pkt, AETH_RNR_NAK |
					 (~AETH_TYPE_MASK &
					 qp->attr.min_rnr_समयr),
					 pkt->psn);
			पूर्ण अन्यथा अणु
				/* UD/UC - class D */
				qp->resp.drop_msg = 1;
			पूर्ण
			state = RESPST_CLEANUP;
			अवरोध;

		हाल RESPST_ERR_RKEY_VIOLATION:
			अगर (qp_type(qp) == IB_QPT_RC) अणु
				/* Class C */
				करो_class_ac_error(qp, AETH_NAK_REM_ACC_ERR,
						  IB_WC_REM_ACCESS_ERR);
				state = RESPST_COMPLETE;
			पूर्ण अन्यथा अणु
				qp->resp.drop_msg = 1;
				अगर (qp->srq) अणु
					/* UC/SRQ Class D */
					qp->resp.status = IB_WC_REM_ACCESS_ERR;
					state = RESPST_COMPLETE;
				पूर्ण अन्यथा अणु
					/* UC/non-SRQ Class E. */
					state = RESPST_CLEANUP;
				पूर्ण
			पूर्ण
			अवरोध;

		हाल RESPST_ERR_LENGTH:
			अगर (qp_type(qp) == IB_QPT_RC) अणु
				/* Class C */
				करो_class_ac_error(qp, AETH_NAK_INVALID_REQ,
						  IB_WC_REM_INV_REQ_ERR);
				state = RESPST_COMPLETE;
			पूर्ण अन्यथा अगर (qp->srq) अणु
				/* UC/UD - class E */
				qp->resp.status = IB_WC_REM_INV_REQ_ERR;
				state = RESPST_COMPLETE;
			पूर्ण अन्यथा अणु
				/* UC/UD - class D */
				qp->resp.drop_msg = 1;
				state = RESPST_CLEANUP;
			पूर्ण
			अवरोध;

		हाल RESPST_ERR_MALFORMED_WQE:
			/* All, Class A. */
			करो_class_ac_error(qp, AETH_NAK_REM_OP_ERR,
					  IB_WC_LOC_QP_OP_ERR);
			state = RESPST_COMPLETE;
			अवरोध;

		हाल RESPST_ERR_CQ_OVERFLOW:
			/* All - Class G */
			state = RESPST_ERROR;
			अवरोध;

		हाल RESPST_DONE:
			अगर (qp->resp.जाओ_error) अणु
				state = RESPST_ERROR;
				अवरोध;
			पूर्ण

			जाओ करोne;

		हाल RESPST_EXIT:
			अगर (qp->resp.जाओ_error) अणु
				state = RESPST_ERROR;
				अवरोध;
			पूर्ण

			जाओ निकास;

		हाल RESPST_RESET:
			rxe_drain_req_pkts(qp, false);
			qp->resp.wqe = शून्य;
			जाओ निकास;

		हाल RESPST_ERROR:
			qp->resp.जाओ_error = 0;
			pr_warn("qp#%d moved to error state\n", qp_num(qp));
			rxe_qp_error(qp);
			जाओ निकास;

		शेष:
			WARN_ON_ONCE(1);
		पूर्ण
	पूर्ण

निकास:
	ret = -EAGAIN;
करोne:
	rxe_drop_ref(qp);
	वापस ret;
पूर्ण
