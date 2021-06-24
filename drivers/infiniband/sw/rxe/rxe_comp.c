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
#समावेश "rxe_task.h"

क्रमागत comp_state अणु
	COMPST_GET_ACK,
	COMPST_GET_WQE,
	COMPST_COMP_WQE,
	COMPST_COMP_ACK,
	COMPST_CHECK_PSN,
	COMPST_CHECK_ACK,
	COMPST_READ,
	COMPST_ATOMIC,
	COMPST_WRITE_SEND,
	COMPST_UPDATE_COMP,
	COMPST_ERROR_RETRY,
	COMPST_RNR_RETRY,
	COMPST_ERROR,
	COMPST_EXIT, /* We have an issue, and we want to rerun the completer */
	COMPST_DONE, /* The completer finished successflly */
पूर्ण;

अटल अक्षर *comp_state_name[] =  अणु
	[COMPST_GET_ACK]		= "GET ACK",
	[COMPST_GET_WQE]		= "GET WQE",
	[COMPST_COMP_WQE]		= "COMP WQE",
	[COMPST_COMP_ACK]		= "COMP ACK",
	[COMPST_CHECK_PSN]		= "CHECK PSN",
	[COMPST_CHECK_ACK]		= "CHECK ACK",
	[COMPST_READ]			= "READ",
	[COMPST_ATOMIC]			= "ATOMIC",
	[COMPST_WRITE_SEND]		= "WRITE/SEND",
	[COMPST_UPDATE_COMP]		= "UPDATE COMP",
	[COMPST_ERROR_RETRY]		= "ERROR RETRY",
	[COMPST_RNR_RETRY]		= "RNR RETRY",
	[COMPST_ERROR]			= "ERROR",
	[COMPST_EXIT]			= "EXIT",
	[COMPST_DONE]			= "DONE",
पूर्ण;

अटल अचिन्हित दीर्घ rnrnak_usec[32] = अणु
	[IB_RNR_TIMER_655_36] = 655360,
	[IB_RNR_TIMER_000_01] = 10,
	[IB_RNR_TIMER_000_02] = 20,
	[IB_RNR_TIMER_000_03] = 30,
	[IB_RNR_TIMER_000_04] = 40,
	[IB_RNR_TIMER_000_06] = 60,
	[IB_RNR_TIMER_000_08] = 80,
	[IB_RNR_TIMER_000_12] = 120,
	[IB_RNR_TIMER_000_16] = 160,
	[IB_RNR_TIMER_000_24] = 240,
	[IB_RNR_TIMER_000_32] = 320,
	[IB_RNR_TIMER_000_48] = 480,
	[IB_RNR_TIMER_000_64] = 640,
	[IB_RNR_TIMER_000_96] = 960,
	[IB_RNR_TIMER_001_28] = 1280,
	[IB_RNR_TIMER_001_92] = 1920,
	[IB_RNR_TIMER_002_56] = 2560,
	[IB_RNR_TIMER_003_84] = 3840,
	[IB_RNR_TIMER_005_12] = 5120,
	[IB_RNR_TIMER_007_68] = 7680,
	[IB_RNR_TIMER_010_24] = 10240,
	[IB_RNR_TIMER_015_36] = 15360,
	[IB_RNR_TIMER_020_48] = 20480,
	[IB_RNR_TIMER_030_72] = 30720,
	[IB_RNR_TIMER_040_96] = 40960,
	[IB_RNR_TIMER_061_44] = 61410,
	[IB_RNR_TIMER_081_92] = 81920,
	[IB_RNR_TIMER_122_88] = 122880,
	[IB_RNR_TIMER_163_84] = 163840,
	[IB_RNR_TIMER_245_76] = 245760,
	[IB_RNR_TIMER_327_68] = 327680,
	[IB_RNR_TIMER_491_52] = 491520,
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ rnrnak_jअगरfies(u8 समयout)
अणु
	वापस max_t(अचिन्हित दीर्घ,
		usecs_to_jअगरfies(rnrnak_usec[समयout]), 1);
पूर्ण

अटल क्रमागत ib_wc_opcode wr_to_wc_opcode(क्रमागत ib_wr_opcode opcode)
अणु
	चयन (opcode) अणु
	हाल IB_WR_RDMA_WRITE:			वापस IB_WC_RDMA_WRITE;
	हाल IB_WR_RDMA_WRITE_WITH_IMM:		वापस IB_WC_RDMA_WRITE;
	हाल IB_WR_SEND:			वापस IB_WC_SEND;
	हाल IB_WR_SEND_WITH_IMM:		वापस IB_WC_SEND;
	हाल IB_WR_RDMA_READ:			वापस IB_WC_RDMA_READ;
	हाल IB_WR_ATOMIC_CMP_AND_SWP:		वापस IB_WC_COMP_SWAP;
	हाल IB_WR_ATOMIC_FETCH_AND_ADD:	वापस IB_WC_FETCH_ADD;
	हाल IB_WR_LSO:				वापस IB_WC_LSO;
	हाल IB_WR_SEND_WITH_INV:		वापस IB_WC_SEND;
	हाल IB_WR_RDMA_READ_WITH_INV:		वापस IB_WC_RDMA_READ;
	हाल IB_WR_LOCAL_INV:			वापस IB_WC_LOCAL_INV;
	हाल IB_WR_REG_MR:			वापस IB_WC_REG_MR;

	शेष:
		वापस 0xff;
	पूर्ण
पूर्ण

व्योम retransmit_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा rxe_qp *qp = from_समयr(qp, t, retrans_समयr);

	अगर (qp->valid) अणु
		qp->comp.समयout = 1;
		rxe_run_task(&qp->comp.task, 1);
	पूर्ण
पूर्ण

व्योम rxe_comp_queue_pkt(काष्ठा rxe_qp *qp, काष्ठा sk_buff *skb)
अणु
	पूर्णांक must_sched;

	skb_queue_tail(&qp->resp_pkts, skb);

	must_sched = skb_queue_len(&qp->resp_pkts) > 1;
	अगर (must_sched != 0)
		rxe_counter_inc(SKB_TO_PKT(skb)->rxe, RXE_CNT_COMPLETER_SCHED);

	rxe_run_task(&qp->comp.task, must_sched);
पूर्ण

अटल अंतरभूत क्रमागत comp_state get_wqe(काष्ठा rxe_qp *qp,
				      काष्ठा rxe_pkt_info *pkt,
				      काष्ठा rxe_send_wqe **wqe_p)
अणु
	काष्ठा rxe_send_wqe *wqe;

	/* we come here whether or not we found a response packet to see अगर
	 * there are any posted WQEs
	 */
	wqe = queue_head(qp->sq.queue);
	*wqe_p = wqe;

	/* no WQE or requester has not started it yet */
	अगर (!wqe || wqe->state == wqe_state_posted)
		वापस pkt ? COMPST_DONE : COMPST_EXIT;

	/* WQE करोes not require an ack */
	अगर (wqe->state == wqe_state_करोne)
		वापस COMPST_COMP_WQE;

	/* WQE caused an error */
	अगर (wqe->state == wqe_state_error)
		वापस COMPST_ERROR;

	/* we have a WQE, अगर we also have an ack check its PSN */
	वापस pkt ? COMPST_CHECK_PSN : COMPST_EXIT;
पूर्ण

अटल अंतरभूत व्योम reset_retry_counters(काष्ठा rxe_qp *qp)
अणु
	qp->comp.retry_cnt = qp->attr.retry_cnt;
	qp->comp.rnr_retry = qp->attr.rnr_retry;
	qp->comp.started_retry = 0;
पूर्ण

अटल अंतरभूत क्रमागत comp_state check_psn(काष्ठा rxe_qp *qp,
					काष्ठा rxe_pkt_info *pkt,
					काष्ठा rxe_send_wqe *wqe)
अणु
	s32 dअगरf;

	/* check to see अगर response is past the oldest WQE. अगर it is, complete
	 * send/ग_लिखो or error पढ़ो/atomic
	 */
	dअगरf = psn_compare(pkt->psn, wqe->last_psn);
	अगर (dअगरf > 0) अणु
		अगर (wqe->state == wqe_state_pending) अणु
			अगर (wqe->mask & WR_ATOMIC_OR_READ_MASK)
				वापस COMPST_ERROR_RETRY;

			reset_retry_counters(qp);
			वापस COMPST_COMP_WQE;
		पूर्ण अन्यथा अणु
			वापस COMPST_DONE;
		पूर्ण
	पूर्ण

	/* compare response packet to expected response */
	dअगरf = psn_compare(pkt->psn, qp->comp.psn);
	अगर (dअगरf < 0) अणु
		/* response is most likely a retried packet अगर it matches an
		 * uncompleted WQE go complete it अन्यथा ignore it
		 */
		अगर (pkt->psn == wqe->last_psn)
			वापस COMPST_COMP_ACK;
		अन्यथा
			वापस COMPST_DONE;
	पूर्ण अन्यथा अगर ((dअगरf > 0) && (wqe->mask & WR_ATOMIC_OR_READ_MASK)) अणु
		वापस COMPST_DONE;
	पूर्ण अन्यथा अणु
		वापस COMPST_CHECK_ACK;
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत comp_state check_ack(काष्ठा rxe_qp *qp,
					काष्ठा rxe_pkt_info *pkt,
					काष्ठा rxe_send_wqe *wqe)
अणु
	अचिन्हित पूर्णांक mask = pkt->mask;
	u8 syn;
	काष्ठा rxe_dev *rxe = to_rdev(qp->ibqp.device);

	/* Check the sequence only */
	चयन (qp->comp.opcode) अणु
	हाल -1:
		/* Will catch all *_ONLY हालs. */
		अगर (!(mask & RXE_START_MASK))
			वापस COMPST_ERROR;

		अवरोध;

	हाल IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST:
	हाल IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE:
		अगर (pkt->opcode != IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE &&
		    pkt->opcode != IB_OPCODE_RC_RDMA_READ_RESPONSE_LAST) अणु
			/* पढ़ो retries of partial data may restart from
			 * पढ़ो response first or response only.
			 */
			अगर ((pkt->psn == wqe->first_psn &&
			     pkt->opcode ==
			     IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST) ||
			    (wqe->first_psn == wqe->last_psn &&
			     pkt->opcode ==
			     IB_OPCODE_RC_RDMA_READ_RESPONSE_ONLY))
				अवरोध;

			वापस COMPST_ERROR;
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण

	/* Check operation validity. */
	चयन (pkt->opcode) अणु
	हाल IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST:
	हाल IB_OPCODE_RC_RDMA_READ_RESPONSE_LAST:
	हाल IB_OPCODE_RC_RDMA_READ_RESPONSE_ONLY:
		syn = aeth_syn(pkt);

		अगर ((syn & AETH_TYPE_MASK) != AETH_ACK)
			वापस COMPST_ERROR;

		fallthrough;
		/* (IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE करोesn't have an AETH)
		 */
	हाल IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE:
		अगर (wqe->wr.opcode != IB_WR_RDMA_READ &&
		    wqe->wr.opcode != IB_WR_RDMA_READ_WITH_INV) अणु
			wqe->status = IB_WC_FATAL_ERR;
			वापस COMPST_ERROR;
		पूर्ण
		reset_retry_counters(qp);
		वापस COMPST_READ;

	हाल IB_OPCODE_RC_ATOMIC_ACKNOWLEDGE:
		syn = aeth_syn(pkt);

		अगर ((syn & AETH_TYPE_MASK) != AETH_ACK)
			वापस COMPST_ERROR;

		अगर (wqe->wr.opcode != IB_WR_ATOMIC_CMP_AND_SWP &&
		    wqe->wr.opcode != IB_WR_ATOMIC_FETCH_AND_ADD)
			वापस COMPST_ERROR;
		reset_retry_counters(qp);
		वापस COMPST_ATOMIC;

	हाल IB_OPCODE_RC_ACKNOWLEDGE:
		syn = aeth_syn(pkt);
		चयन (syn & AETH_TYPE_MASK) अणु
		हाल AETH_ACK:
			reset_retry_counters(qp);
			वापस COMPST_WRITE_SEND;

		हाल AETH_RNR_NAK:
			rxe_counter_inc(rxe, RXE_CNT_RCV_RNR);
			वापस COMPST_RNR_RETRY;

		हाल AETH_NAK:
			चयन (syn) अणु
			हाल AETH_NAK_PSN_SEQ_ERROR:
				/* a nak implicitly acks all packets with psns
				 * beक्रमe
				 */
				अगर (psn_compare(pkt->psn, qp->comp.psn) > 0) अणु
					rxe_counter_inc(rxe,
							RXE_CNT_RCV_SEQ_ERR);
					qp->comp.psn = pkt->psn;
					अगर (qp->req.रुको_psn) अणु
						qp->req.रुको_psn = 0;
						rxe_run_task(&qp->req.task, 0);
					पूर्ण
				पूर्ण
				वापस COMPST_ERROR_RETRY;

			हाल AETH_NAK_INVALID_REQ:
				wqe->status = IB_WC_REM_INV_REQ_ERR;
				वापस COMPST_ERROR;

			हाल AETH_NAK_REM_ACC_ERR:
				wqe->status = IB_WC_REM_ACCESS_ERR;
				वापस COMPST_ERROR;

			हाल AETH_NAK_REM_OP_ERR:
				wqe->status = IB_WC_REM_OP_ERR;
				वापस COMPST_ERROR;

			शेष:
				pr_warn("unexpected nak %x\n", syn);
				wqe->status = IB_WC_REM_OP_ERR;
				वापस COMPST_ERROR;
			पूर्ण

		शेष:
			वापस COMPST_ERROR;
		पूर्ण
		अवरोध;

	शेष:
		pr_warn("unexpected opcode\n");
	पूर्ण

	वापस COMPST_ERROR;
पूर्ण

अटल अंतरभूत क्रमागत comp_state करो_पढ़ो(काष्ठा rxe_qp *qp,
				      काष्ठा rxe_pkt_info *pkt,
				      काष्ठा rxe_send_wqe *wqe)
अणु
	पूर्णांक ret;

	ret = copy_data(qp->pd, IB_ACCESS_LOCAL_WRITE,
			&wqe->dma, payload_addr(pkt),
			payload_size(pkt), to_mr_obj, शून्य);
	अगर (ret) अणु
		wqe->status = IB_WC_LOC_PROT_ERR;
		वापस COMPST_ERROR;
	पूर्ण

	अगर (wqe->dma.resid == 0 && (pkt->mask & RXE_END_MASK))
		वापस COMPST_COMP_ACK;

	वापस COMPST_UPDATE_COMP;
पूर्ण

अटल अंतरभूत क्रमागत comp_state करो_atomic(काष्ठा rxe_qp *qp,
					काष्ठा rxe_pkt_info *pkt,
					काष्ठा rxe_send_wqe *wqe)
अणु
	पूर्णांक ret;

	u64 atomic_orig = aपंचांगack_orig(pkt);

	ret = copy_data(qp->pd, IB_ACCESS_LOCAL_WRITE,
			&wqe->dma, &atomic_orig,
			माप(u64), to_mr_obj, शून्य);
	अगर (ret) अणु
		wqe->status = IB_WC_LOC_PROT_ERR;
		वापस COMPST_ERROR;
	पूर्ण

	वापस COMPST_COMP_ACK;
पूर्ण

अटल व्योम make_send_cqe(काष्ठा rxe_qp *qp, काष्ठा rxe_send_wqe *wqe,
			  काष्ठा rxe_cqe *cqe)
अणु
	स_रखो(cqe, 0, माप(*cqe));

	अगर (!qp->is_user) अणु
		काष्ठा ib_wc		*wc	= &cqe->ibwc;

		wc->wr_id		= wqe->wr.wr_id;
		wc->status		= wqe->status;
		wc->opcode		= wr_to_wc_opcode(wqe->wr.opcode);
		अगर (wqe->wr.opcode == IB_WR_RDMA_WRITE_WITH_IMM ||
		    wqe->wr.opcode == IB_WR_SEND_WITH_IMM)
			wc->wc_flags = IB_WC_WITH_IMM;
		wc->byte_len		= wqe->dma.length;
		wc->qp			= &qp->ibqp;
	पूर्ण अन्यथा अणु
		काष्ठा ib_uverbs_wc	*uwc	= &cqe->uibwc;

		uwc->wr_id		= wqe->wr.wr_id;
		uwc->status		= wqe->status;
		uwc->opcode		= wr_to_wc_opcode(wqe->wr.opcode);
		अगर (wqe->wr.opcode == IB_WR_RDMA_WRITE_WITH_IMM ||
		    wqe->wr.opcode == IB_WR_SEND_WITH_IMM)
			uwc->wc_flags = IB_WC_WITH_IMM;
		uwc->byte_len		= wqe->dma.length;
		uwc->qp_num		= qp->ibqp.qp_num;
	पूर्ण
पूर्ण

/*
 * IBA Spec. Section 10.7.3.1 SIGNALED COMPLETIONS
 * ---------8<---------8<-------------
 * ...Note that अगर a completion error occurs, a Work Completion
 * will always be generated, even अगर the संकेतing
 * indicator requests an Unसंकेतed Completion.
 * ---------8<---------8<-------------
 */
अटल व्योम करो_complete(काष्ठा rxe_qp *qp, काष्ठा rxe_send_wqe *wqe)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(qp->ibqp.device);
	काष्ठा rxe_cqe cqe;

	अगर ((qp->sq_sig_type == IB_SIGNAL_ALL_WR) ||
	    (wqe->wr.send_flags & IB_SEND_SIGNALED) ||
	    wqe->status != IB_WC_SUCCESS) अणु
		make_send_cqe(qp, wqe, &cqe);
		advance_consumer(qp->sq.queue);
		rxe_cq_post(qp->scq, &cqe, 0);
	पूर्ण अन्यथा अणु
		advance_consumer(qp->sq.queue);
	पूर्ण

	अगर (wqe->wr.opcode == IB_WR_SEND ||
	    wqe->wr.opcode == IB_WR_SEND_WITH_IMM ||
	    wqe->wr.opcode == IB_WR_SEND_WITH_INV)
		rxe_counter_inc(rxe, RXE_CNT_RDMA_SEND);

	/*
	 * we completed something so let req run again
	 * अगर it is trying to fence
	 */
	अगर (qp->req.रुको_fence) अणु
		qp->req.रुको_fence = 0;
		rxe_run_task(&qp->req.task, 0);
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत comp_state complete_ack(काष्ठा rxe_qp *qp,
					   काष्ठा rxe_pkt_info *pkt,
					   काष्ठा rxe_send_wqe *wqe)
अणु
	अचिन्हित दीर्घ flags;

	अगर (wqe->has_rd_atomic) अणु
		wqe->has_rd_atomic = 0;
		atomic_inc(&qp->req.rd_atomic);
		अगर (qp->req.need_rd_atomic) अणु
			qp->comp.समयout_retry = 0;
			qp->req.need_rd_atomic = 0;
			rxe_run_task(&qp->req.task, 0);
		पूर्ण
	पूर्ण

	अगर (unlikely(qp->req.state == QP_STATE_DRAIN)) अणु
		/* state_lock used by requester & completer */
		spin_lock_irqsave(&qp->state_lock, flags);
		अगर ((qp->req.state == QP_STATE_DRAIN) &&
		    (qp->comp.psn == qp->req.psn)) अणु
			qp->req.state = QP_STATE_DRAINED;
			spin_unlock_irqrestore(&qp->state_lock, flags);

			अगर (qp->ibqp.event_handler) अणु
				काष्ठा ib_event ev;

				ev.device = qp->ibqp.device;
				ev.element.qp = &qp->ibqp;
				ev.event = IB_EVENT_SQ_DRAINED;
				qp->ibqp.event_handler(&ev,
					qp->ibqp.qp_context);
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&qp->state_lock, flags);
		पूर्ण
	पूर्ण

	करो_complete(qp, wqe);

	अगर (psn_compare(pkt->psn, qp->comp.psn) >= 0)
		वापस COMPST_UPDATE_COMP;
	अन्यथा
		वापस COMPST_DONE;
पूर्ण

अटल अंतरभूत क्रमागत comp_state complete_wqe(काष्ठा rxe_qp *qp,
					   काष्ठा rxe_pkt_info *pkt,
					   काष्ठा rxe_send_wqe *wqe)
अणु
	अगर (pkt && wqe->state == wqe_state_pending) अणु
		अगर (psn_compare(wqe->last_psn, qp->comp.psn) >= 0) अणु
			qp->comp.psn = (wqe->last_psn + 1) & BTH_PSN_MASK;
			qp->comp.opcode = -1;
		पूर्ण

		अगर (qp->req.रुको_psn) अणु
			qp->req.रुको_psn = 0;
			rxe_run_task(&qp->req.task, 1);
		पूर्ण
	पूर्ण

	करो_complete(qp, wqe);

	वापस COMPST_GET_WQE;
पूर्ण

अटल व्योम rxe_drain_resp_pkts(काष्ठा rxe_qp *qp, bool notअगरy)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rxe_send_wqe *wqe;

	जबतक ((skb = skb_dequeue(&qp->resp_pkts))) अणु
		rxe_drop_ref(qp);
		kमुक्त_skb(skb);
		ib_device_put(qp->ibqp.device);
	पूर्ण

	जबतक ((wqe = queue_head(qp->sq.queue))) अणु
		अगर (notअगरy) अणु
			wqe->status = IB_WC_WR_FLUSH_ERR;
			करो_complete(qp, wqe);
		पूर्ण अन्यथा अणु
			advance_consumer(qp->sq.queue);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम मुक्त_pkt(काष्ठा rxe_pkt_info *pkt)
अणु
	काष्ठा sk_buff *skb = PKT_TO_SKB(pkt);
	काष्ठा rxe_qp *qp = pkt->qp;
	काष्ठा ib_device *dev = qp->ibqp.device;

	kमुक्त_skb(skb);
	rxe_drop_ref(qp);
	ib_device_put(dev);
पूर्ण

पूर्णांक rxe_completer(व्योम *arg)
अणु
	काष्ठा rxe_qp *qp = (काष्ठा rxe_qp *)arg;
	काष्ठा rxe_dev *rxe = to_rdev(qp->ibqp.device);
	काष्ठा rxe_send_wqe *wqe = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rxe_pkt_info *pkt = शून्य;
	क्रमागत comp_state state;
	पूर्णांक ret = 0;

	rxe_add_ref(qp);

	अगर (!qp->valid || qp->req.state == QP_STATE_ERROR ||
	    qp->req.state == QP_STATE_RESET) अणु
		rxe_drain_resp_pkts(qp, qp->valid &&
				    qp->req.state == QP_STATE_ERROR);
		ret = -EAGAIN;
		जाओ करोne;
	पूर्ण

	अगर (qp->comp.समयout) अणु
		qp->comp.समयout_retry = 1;
		qp->comp.समयout = 0;
	पूर्ण अन्यथा अणु
		qp->comp.समयout_retry = 0;
	पूर्ण

	अगर (qp->req.need_retry) अणु
		ret = -EAGAIN;
		जाओ करोne;
	पूर्ण

	state = COMPST_GET_ACK;

	जबतक (1) अणु
		pr_debug("qp#%d state = %s\n", qp_num(qp),
			 comp_state_name[state]);
		चयन (state) अणु
		हाल COMPST_GET_ACK:
			skb = skb_dequeue(&qp->resp_pkts);
			अगर (skb) अणु
				pkt = SKB_TO_PKT(skb);
				qp->comp.समयout_retry = 0;
			पूर्ण
			state = COMPST_GET_WQE;
			अवरोध;

		हाल COMPST_GET_WQE:
			state = get_wqe(qp, pkt, &wqe);
			अवरोध;

		हाल COMPST_CHECK_PSN:
			state = check_psn(qp, pkt, wqe);
			अवरोध;

		हाल COMPST_CHECK_ACK:
			state = check_ack(qp, pkt, wqe);
			अवरोध;

		हाल COMPST_READ:
			state = करो_पढ़ो(qp, pkt, wqe);
			अवरोध;

		हाल COMPST_ATOMIC:
			state = करो_atomic(qp, pkt, wqe);
			अवरोध;

		हाल COMPST_WRITE_SEND:
			अगर (wqe->state == wqe_state_pending &&
			    wqe->last_psn == pkt->psn)
				state = COMPST_COMP_ACK;
			अन्यथा
				state = COMPST_UPDATE_COMP;
			अवरोध;

		हाल COMPST_COMP_ACK:
			state = complete_ack(qp, pkt, wqe);
			अवरोध;

		हाल COMPST_COMP_WQE:
			state = complete_wqe(qp, pkt, wqe);
			अवरोध;

		हाल COMPST_UPDATE_COMP:
			अगर (pkt->mask & RXE_END_MASK)
				qp->comp.opcode = -1;
			अन्यथा
				qp->comp.opcode = pkt->opcode;

			अगर (psn_compare(pkt->psn, qp->comp.psn) >= 0)
				qp->comp.psn = (pkt->psn + 1) & BTH_PSN_MASK;

			अगर (qp->req.रुको_psn) अणु
				qp->req.रुको_psn = 0;
				rxe_run_task(&qp->req.task, 1);
			पूर्ण

			state = COMPST_DONE;
			अवरोध;

		हाल COMPST_DONE:
			जाओ करोne;

		हाल COMPST_EXIT:
			अगर (qp->comp.समयout_retry && wqe) अणु
				state = COMPST_ERROR_RETRY;
				अवरोध;
			पूर्ण

			/* re reset the समयout counter अगर
			 * (1) QP is type RC
			 * (2) the QP is alive
			 * (3) there is a packet sent by the requester that
			 *     might be acked (we still might get spurious
			 *     समयouts but try to keep them as few as possible)
			 * (4) the समयout parameter is set
			 */
			अगर ((qp_type(qp) == IB_QPT_RC) &&
			    (qp->req.state == QP_STATE_READY) &&
			    (psn_compare(qp->req.psn, qp->comp.psn) > 0) &&
			    qp->qp_समयout_jअगरfies)
				mod_समयr(&qp->retrans_समयr,
					  jअगरfies + qp->qp_समयout_jअगरfies);
			ret = -EAGAIN;
			जाओ करोne;

		हाल COMPST_ERROR_RETRY:
			/* we come here अगर the retry समयr fired and we did
			 * not receive a response packet. try to retry the send
			 * queue अगर that makes sense and the limits have not
			 * been exceeded. remember that some समयouts are
			 * spurious since we करो not reset the समयr but kick
			 * it करोwn the road or let it expire
			 */

			/* there is nothing to retry in this हाल */
			अगर (!wqe || (wqe->state == wqe_state_posted)) अणु
				ret = -EAGAIN;
				जाओ करोne;
			पूर्ण

			/* अगर we've started a retry, don't start another
			 * retry sequence, unless this is a समयout.
			 */
			अगर (qp->comp.started_retry &&
			    !qp->comp.समयout_retry)
				जाओ करोne;

			अगर (qp->comp.retry_cnt > 0) अणु
				अगर (qp->comp.retry_cnt != 7)
					qp->comp.retry_cnt--;

				/* no poपूर्णांक in retrying अगर we have alपढ़ोy
				 * seen the last ack that the requester could
				 * have caused
				 */
				अगर (psn_compare(qp->req.psn,
						qp->comp.psn) > 0) अणु
					/* tell the requester to retry the
					 * send queue next समय around
					 */
					rxe_counter_inc(rxe,
							RXE_CNT_COMP_RETRY);
					qp->req.need_retry = 1;
					qp->comp.started_retry = 1;
					rxe_run_task(&qp->req.task, 0);
				पूर्ण
				जाओ करोne;

			पूर्ण अन्यथा अणु
				rxe_counter_inc(rxe, RXE_CNT_RETRY_EXCEEDED);
				wqe->status = IB_WC_RETRY_EXC_ERR;
				state = COMPST_ERROR;
			पूर्ण
			अवरोध;

		हाल COMPST_RNR_RETRY:
			अगर (qp->comp.rnr_retry > 0) अणु
				अगर (qp->comp.rnr_retry != 7)
					qp->comp.rnr_retry--;

				qp->req.need_retry = 1;
				pr_debug("qp#%d set rnr nak timer\n",
					 qp_num(qp));
				mod_समयr(&qp->rnr_nak_समयr,
					  jअगरfies + rnrnak_jअगरfies(aeth_syn(pkt)
						& ~AETH_TYPE_MASK));
				ret = -EAGAIN;
				जाओ करोne;
			पूर्ण अन्यथा अणु
				rxe_counter_inc(rxe,
						RXE_CNT_RNR_RETRY_EXCEEDED);
				wqe->status = IB_WC_RNR_RETRY_EXC_ERR;
				state = COMPST_ERROR;
			पूर्ण
			अवरोध;

		हाल COMPST_ERROR:
			WARN_ON_ONCE(wqe->status == IB_WC_SUCCESS);
			करो_complete(qp, wqe);
			rxe_qp_error(qp);
			ret = -EAGAIN;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	अगर (pkt)
		मुक्त_pkt(pkt);
	rxe_drop_ref(qp);

	वापस ret;
पूर्ण
