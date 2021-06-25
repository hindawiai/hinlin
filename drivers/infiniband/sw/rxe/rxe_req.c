<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश <linux/skbuff.h>
#समावेश <crypto/hash.h>

#समावेश "rxe.h"
#समावेश "rxe_loc.h"
#समावेश "rxe_queue.h"

अटल पूर्णांक next_opcode(काष्ठा rxe_qp *qp, काष्ठा rxe_send_wqe *wqe,
		       u32 opcode);

अटल अंतरभूत व्योम retry_first_ग_लिखो_send(काष्ठा rxe_qp *qp,
					  काष्ठा rxe_send_wqe *wqe,
					  अचिन्हित पूर्णांक mask, पूर्णांक npsn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < npsn; i++) अणु
		पूर्णांक to_send = (wqe->dma.resid > qp->mtu) ?
				qp->mtu : wqe->dma.resid;

		qp->req.opcode = next_opcode(qp, wqe,
					     wqe->wr.opcode);

		अगर (wqe->wr.send_flags & IB_SEND_INLINE) अणु
			wqe->dma.resid -= to_send;
			wqe->dma.sge_offset += to_send;
		पूर्ण अन्यथा अणु
			advance_dma_data(&wqe->dma, to_send);
		पूर्ण
		अगर (mask & WR_WRITE_MASK)
			wqe->iova += qp->mtu;
	पूर्ण
पूर्ण

अटल व्योम req_retry(काष्ठा rxe_qp *qp)
अणु
	काष्ठा rxe_send_wqe *wqe;
	अचिन्हित पूर्णांक wqe_index;
	अचिन्हित पूर्णांक mask;
	पूर्णांक npsn;
	पूर्णांक first = 1;

	qp->req.wqe_index	= consumer_index(qp->sq.queue);
	qp->req.psn		= qp->comp.psn;
	qp->req.opcode		= -1;

	क्रम (wqe_index = consumer_index(qp->sq.queue);
		wqe_index != producer_index(qp->sq.queue);
		wqe_index = next_index(qp->sq.queue, wqe_index)) अणु
		wqe = addr_from_index(qp->sq.queue, wqe_index);
		mask = wr_opcode_mask(wqe->wr.opcode, qp);

		अगर (wqe->state == wqe_state_posted)
			अवरोध;

		अगर (wqe->state == wqe_state_करोne)
			जारी;

		wqe->iova = (mask & WR_ATOMIC_MASK) ?
			     wqe->wr.wr.atomic.remote_addr :
			     (mask & WR_READ_OR_WRITE_MASK) ?
			     wqe->wr.wr.rdma.remote_addr :
			     0;

		अगर (!first || (mask & WR_READ_MASK) == 0) अणु
			wqe->dma.resid = wqe->dma.length;
			wqe->dma.cur_sge = 0;
			wqe->dma.sge_offset = 0;
		पूर्ण

		अगर (first) अणु
			first = 0;

			अगर (mask & WR_WRITE_OR_SEND_MASK) अणु
				npsn = (qp->comp.psn - wqe->first_psn) &
					BTH_PSN_MASK;
				retry_first_ग_लिखो_send(qp, wqe, mask, npsn);
			पूर्ण

			अगर (mask & WR_READ_MASK) अणु
				npsn = (wqe->dma.length - wqe->dma.resid) /
					qp->mtu;
				wqe->iova += npsn * qp->mtu;
			पूर्ण
		पूर्ण

		wqe->state = wqe_state_posted;
	पूर्ण
पूर्ण

व्योम rnr_nak_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा rxe_qp *qp = from_समयr(qp, t, rnr_nak_समयr);

	pr_debug("qp#%d rnr nak timer fired\n", qp_num(qp));
	rxe_run_task(&qp->req.task, 1);
पूर्ण

अटल काष्ठा rxe_send_wqe *req_next_wqe(काष्ठा rxe_qp *qp)
अणु
	काष्ठा rxe_send_wqe *wqe = queue_head(qp->sq.queue);
	अचिन्हित दीर्घ flags;

	अगर (unlikely(qp->req.state == QP_STATE_DRAIN)) अणु
		/* check to see अगर we are drained;
		 * state_lock used by requester and completer
		 */
		spin_lock_irqsave(&qp->state_lock, flags);
		करो अणु
			अगर (qp->req.state != QP_STATE_DRAIN) अणु
				/* comp just finished */
				spin_unlock_irqrestore(&qp->state_lock,
						       flags);
				अवरोध;
			पूर्ण

			अगर (wqe && ((qp->req.wqe_index !=
				consumer_index(qp->sq.queue)) ||
				(wqe->state != wqe_state_posted))) अणु
				/* comp not करोne yet */
				spin_unlock_irqrestore(&qp->state_lock,
						       flags);
				अवरोध;
			पूर्ण

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
		पूर्ण जबतक (0);
	पूर्ण

	अगर (qp->req.wqe_index == producer_index(qp->sq.queue))
		वापस शून्य;

	wqe = addr_from_index(qp->sq.queue, qp->req.wqe_index);

	अगर (unlikely((qp->req.state == QP_STATE_DRAIN ||
		      qp->req.state == QP_STATE_DRAINED) &&
		     (wqe->state != wqe_state_processing)))
		वापस शून्य;

	अगर (unlikely((wqe->wr.send_flags & IB_SEND_FENCE) &&
		     (qp->req.wqe_index != consumer_index(qp->sq.queue)))) अणु
		qp->req.रुको_fence = 1;
		वापस शून्य;
	पूर्ण

	wqe->mask = wr_opcode_mask(wqe->wr.opcode, qp);
	वापस wqe;
पूर्ण

अटल पूर्णांक next_opcode_rc(काष्ठा rxe_qp *qp, u32 opcode, पूर्णांक fits)
अणु
	चयन (opcode) अणु
	हाल IB_WR_RDMA_WRITE:
		अगर (qp->req.opcode == IB_OPCODE_RC_RDMA_WRITE_FIRST ||
		    qp->req.opcode == IB_OPCODE_RC_RDMA_WRITE_MIDDLE)
			वापस fits ?
				IB_OPCODE_RC_RDMA_WRITE_LAST :
				IB_OPCODE_RC_RDMA_WRITE_MIDDLE;
		अन्यथा
			वापस fits ?
				IB_OPCODE_RC_RDMA_WRITE_ONLY :
				IB_OPCODE_RC_RDMA_WRITE_FIRST;

	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		अगर (qp->req.opcode == IB_OPCODE_RC_RDMA_WRITE_FIRST ||
		    qp->req.opcode == IB_OPCODE_RC_RDMA_WRITE_MIDDLE)
			वापस fits ?
				IB_OPCODE_RC_RDMA_WRITE_LAST_WITH_IMMEDIATE :
				IB_OPCODE_RC_RDMA_WRITE_MIDDLE;
		अन्यथा
			वापस fits ?
				IB_OPCODE_RC_RDMA_WRITE_ONLY_WITH_IMMEDIATE :
				IB_OPCODE_RC_RDMA_WRITE_FIRST;

	हाल IB_WR_SEND:
		अगर (qp->req.opcode == IB_OPCODE_RC_SEND_FIRST ||
		    qp->req.opcode == IB_OPCODE_RC_SEND_MIDDLE)
			वापस fits ?
				IB_OPCODE_RC_SEND_LAST :
				IB_OPCODE_RC_SEND_MIDDLE;
		अन्यथा
			वापस fits ?
				IB_OPCODE_RC_SEND_ONLY :
				IB_OPCODE_RC_SEND_FIRST;

	हाल IB_WR_SEND_WITH_IMM:
		अगर (qp->req.opcode == IB_OPCODE_RC_SEND_FIRST ||
		    qp->req.opcode == IB_OPCODE_RC_SEND_MIDDLE)
			वापस fits ?
				IB_OPCODE_RC_SEND_LAST_WITH_IMMEDIATE :
				IB_OPCODE_RC_SEND_MIDDLE;
		अन्यथा
			वापस fits ?
				IB_OPCODE_RC_SEND_ONLY_WITH_IMMEDIATE :
				IB_OPCODE_RC_SEND_FIRST;

	हाल IB_WR_RDMA_READ:
		वापस IB_OPCODE_RC_RDMA_READ_REQUEST;

	हाल IB_WR_ATOMIC_CMP_AND_SWP:
		वापस IB_OPCODE_RC_COMPARE_SWAP;

	हाल IB_WR_ATOMIC_FETCH_AND_ADD:
		वापस IB_OPCODE_RC_FETCH_ADD;

	हाल IB_WR_SEND_WITH_INV:
		अगर (qp->req.opcode == IB_OPCODE_RC_SEND_FIRST ||
		    qp->req.opcode == IB_OPCODE_RC_SEND_MIDDLE)
			वापस fits ? IB_OPCODE_RC_SEND_LAST_WITH_INVALIDATE :
				IB_OPCODE_RC_SEND_MIDDLE;
		अन्यथा
			वापस fits ? IB_OPCODE_RC_SEND_ONLY_WITH_INVALIDATE :
				IB_OPCODE_RC_SEND_FIRST;
	हाल IB_WR_REG_MR:
	हाल IB_WR_LOCAL_INV:
		वापस opcode;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक next_opcode_uc(काष्ठा rxe_qp *qp, u32 opcode, पूर्णांक fits)
अणु
	चयन (opcode) अणु
	हाल IB_WR_RDMA_WRITE:
		अगर (qp->req.opcode == IB_OPCODE_UC_RDMA_WRITE_FIRST ||
		    qp->req.opcode == IB_OPCODE_UC_RDMA_WRITE_MIDDLE)
			वापस fits ?
				IB_OPCODE_UC_RDMA_WRITE_LAST :
				IB_OPCODE_UC_RDMA_WRITE_MIDDLE;
		अन्यथा
			वापस fits ?
				IB_OPCODE_UC_RDMA_WRITE_ONLY :
				IB_OPCODE_UC_RDMA_WRITE_FIRST;

	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		अगर (qp->req.opcode == IB_OPCODE_UC_RDMA_WRITE_FIRST ||
		    qp->req.opcode == IB_OPCODE_UC_RDMA_WRITE_MIDDLE)
			वापस fits ?
				IB_OPCODE_UC_RDMA_WRITE_LAST_WITH_IMMEDIATE :
				IB_OPCODE_UC_RDMA_WRITE_MIDDLE;
		अन्यथा
			वापस fits ?
				IB_OPCODE_UC_RDMA_WRITE_ONLY_WITH_IMMEDIATE :
				IB_OPCODE_UC_RDMA_WRITE_FIRST;

	हाल IB_WR_SEND:
		अगर (qp->req.opcode == IB_OPCODE_UC_SEND_FIRST ||
		    qp->req.opcode == IB_OPCODE_UC_SEND_MIDDLE)
			वापस fits ?
				IB_OPCODE_UC_SEND_LAST :
				IB_OPCODE_UC_SEND_MIDDLE;
		अन्यथा
			वापस fits ?
				IB_OPCODE_UC_SEND_ONLY :
				IB_OPCODE_UC_SEND_FIRST;

	हाल IB_WR_SEND_WITH_IMM:
		अगर (qp->req.opcode == IB_OPCODE_UC_SEND_FIRST ||
		    qp->req.opcode == IB_OPCODE_UC_SEND_MIDDLE)
			वापस fits ?
				IB_OPCODE_UC_SEND_LAST_WITH_IMMEDIATE :
				IB_OPCODE_UC_SEND_MIDDLE;
		अन्यथा
			वापस fits ?
				IB_OPCODE_UC_SEND_ONLY_WITH_IMMEDIATE :
				IB_OPCODE_UC_SEND_FIRST;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक next_opcode(काष्ठा rxe_qp *qp, काष्ठा rxe_send_wqe *wqe,
		       u32 opcode)
अणु
	पूर्णांक fits = (wqe->dma.resid <= qp->mtu);

	चयन (qp_type(qp)) अणु
	हाल IB_QPT_RC:
		वापस next_opcode_rc(qp, opcode, fits);

	हाल IB_QPT_UC:
		वापस next_opcode_uc(qp, opcode, fits);

	हाल IB_QPT_SMI:
	हाल IB_QPT_UD:
	हाल IB_QPT_GSI:
		चयन (opcode) अणु
		हाल IB_WR_SEND:
			वापस IB_OPCODE_UD_SEND_ONLY;

		हाल IB_WR_SEND_WITH_IMM:
			वापस IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक check_init_depth(काष्ठा rxe_qp *qp, काष्ठा rxe_send_wqe *wqe)
अणु
	पूर्णांक depth;

	अगर (wqe->has_rd_atomic)
		वापस 0;

	qp->req.need_rd_atomic = 1;
	depth = atomic_dec_वापस(&qp->req.rd_atomic);

	अगर (depth >= 0) अणु
		qp->req.need_rd_atomic = 0;
		wqe->has_rd_atomic = 1;
		वापस 0;
	पूर्ण

	atomic_inc(&qp->req.rd_atomic);
	वापस -EAGAIN;
पूर्ण

अटल अंतरभूत पूर्णांक get_mtu(काष्ठा rxe_qp *qp)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(qp->ibqp.device);

	अगर ((qp_type(qp) == IB_QPT_RC) || (qp_type(qp) == IB_QPT_UC))
		वापस qp->mtu;

	वापस rxe->port.mtu_cap;
पूर्ण

अटल काष्ठा sk_buff *init_req_packet(काष्ठा rxe_qp *qp,
				       काष्ठा rxe_send_wqe *wqe,
				       पूर्णांक opcode, पूर्णांक payload,
				       काष्ठा rxe_pkt_info *pkt)
अणु
	काष्ठा rxe_dev		*rxe = to_rdev(qp->ibqp.device);
	काष्ठा sk_buff		*skb;
	काष्ठा rxe_send_wr	*ibwr = &wqe->wr;
	काष्ठा rxe_av		*av;
	पूर्णांक			pad = (-payload) & 0x3;
	पूर्णांक			paylen;
	पूर्णांक			solicited;
	u16			pkey;
	u32			qp_num;
	पूर्णांक			ack_req;

	/* length from start of bth to end of icrc */
	paylen = rxe_opcode[opcode].length + payload + pad + RXE_ICRC_SIZE;

	/* pkt->hdr, rxe, port_num and mask are initialized in अगरc
	 * layer
	 */
	pkt->opcode	= opcode;
	pkt->qp		= qp;
	pkt->psn	= qp->req.psn;
	pkt->mask	= rxe_opcode[opcode].mask;
	pkt->paylen	= paylen;
	pkt->wqe	= wqe;

	/* init skb */
	av = rxe_get_av(pkt);
	skb = rxe_init_packet(rxe, av, paylen, pkt);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* init bth */
	solicited = (ibwr->send_flags & IB_SEND_SOLICITED) &&
			(pkt->mask & RXE_END_MASK) &&
			((pkt->mask & (RXE_SEND_MASK)) ||
			(pkt->mask & (RXE_WRITE_MASK | RXE_IMMDT_MASK)) ==
			(RXE_WRITE_MASK | RXE_IMMDT_MASK));

	pkey = IB_DEFAULT_PKEY_FULL;

	qp_num = (pkt->mask & RXE_DETH_MASK) ? ibwr->wr.ud.remote_qpn :
					 qp->attr.dest_qp_num;

	ack_req = ((pkt->mask & RXE_END_MASK) ||
		(qp->req.noack_pkts++ > RXE_MAX_PKT_PER_ACK));
	अगर (ack_req)
		qp->req.noack_pkts = 0;

	bth_init(pkt, pkt->opcode, solicited, 0, pad, pkey, qp_num,
		 ack_req, pkt->psn);

	/* init optional headers */
	अगर (pkt->mask & RXE_RETH_MASK) अणु
		reth_set_rkey(pkt, ibwr->wr.rdma.rkey);
		reth_set_va(pkt, wqe->iova);
		reth_set_len(pkt, wqe->dma.resid);
	पूर्ण

	अगर (pkt->mask & RXE_IMMDT_MASK)
		immdt_set_imm(pkt, ibwr->ex.imm_data);

	अगर (pkt->mask & RXE_IETH_MASK)
		ieth_set_rkey(pkt, ibwr->ex.invalidate_rkey);

	अगर (pkt->mask & RXE_ATMETH_MASK) अणु
		aपंचांगeth_set_va(pkt, wqe->iova);
		अगर (opcode == IB_OPCODE_RC_COMPARE_SWAP ||
		    opcode == IB_OPCODE_RD_COMPARE_SWAP) अणु
			aपंचांगeth_set_swap_add(pkt, ibwr->wr.atomic.swap);
			aपंचांगeth_set_comp(pkt, ibwr->wr.atomic.compare_add);
		पूर्ण अन्यथा अणु
			aपंचांगeth_set_swap_add(pkt, ibwr->wr.atomic.compare_add);
		पूर्ण
		aपंचांगeth_set_rkey(pkt, ibwr->wr.atomic.rkey);
	पूर्ण

	अगर (pkt->mask & RXE_DETH_MASK) अणु
		अगर (qp->ibqp.qp_num == 1)
			deth_set_qkey(pkt, GSI_QKEY);
		अन्यथा
			deth_set_qkey(pkt, ibwr->wr.ud.remote_qkey);
		deth_set_sqp(pkt, qp->ibqp.qp_num);
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक fill_packet(काष्ठा rxe_qp *qp, काष्ठा rxe_send_wqe *wqe,
		       काष्ठा rxe_pkt_info *pkt, काष्ठा sk_buff *skb,
		       पूर्णांक paylen)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(qp->ibqp.device);
	u32 crc = 0;
	u32 *p;
	पूर्णांक err;

	err = rxe_prepare(pkt, skb, &crc);
	अगर (err)
		वापस err;

	अगर (pkt->mask & RXE_WRITE_OR_SEND) अणु
		अगर (wqe->wr.send_flags & IB_SEND_INLINE) अणु
			u8 *पंचांगp = &wqe->dma.अंतरभूत_data[wqe->dma.sge_offset];

			crc = rxe_crc32(rxe, crc, पंचांगp, paylen);
			स_नकल(payload_addr(pkt), पंचांगp, paylen);

			wqe->dma.resid -= paylen;
			wqe->dma.sge_offset += paylen;
		पूर्ण अन्यथा अणु
			err = copy_data(qp->pd, 0, &wqe->dma,
					payload_addr(pkt), paylen,
					from_mr_obj,
					&crc);
			अगर (err)
				वापस err;
		पूर्ण
		अगर (bth_pad(pkt)) अणु
			u8 *pad = payload_addr(pkt) + paylen;

			स_रखो(pad, 0, bth_pad(pkt));
			crc = rxe_crc32(rxe, crc, pad, bth_pad(pkt));
		पूर्ण
	पूर्ण
	p = payload_addr(pkt) + paylen + bth_pad(pkt);

	*p = ~crc;

	वापस 0;
पूर्ण

अटल व्योम update_wqe_state(काष्ठा rxe_qp *qp,
		काष्ठा rxe_send_wqe *wqe,
		काष्ठा rxe_pkt_info *pkt)
अणु
	अगर (pkt->mask & RXE_END_MASK) अणु
		अगर (qp_type(qp) == IB_QPT_RC)
			wqe->state = wqe_state_pending;
	पूर्ण अन्यथा अणु
		wqe->state = wqe_state_processing;
	पूर्ण
पूर्ण

अटल व्योम update_wqe_psn(काष्ठा rxe_qp *qp,
			   काष्ठा rxe_send_wqe *wqe,
			   काष्ठा rxe_pkt_info *pkt,
			   पूर्णांक payload)
अणु
	/* number of packets left to send including current one */
	पूर्णांक num_pkt = (wqe->dma.resid + payload + qp->mtu - 1) / qp->mtu;

	/* handle zero length packet हाल */
	अगर (num_pkt == 0)
		num_pkt = 1;

	अगर (pkt->mask & RXE_START_MASK) अणु
		wqe->first_psn = qp->req.psn;
		wqe->last_psn = (qp->req.psn + num_pkt - 1) & BTH_PSN_MASK;
	पूर्ण

	अगर (pkt->mask & RXE_READ_MASK)
		qp->req.psn = (wqe->first_psn + num_pkt) & BTH_PSN_MASK;
	अन्यथा
		qp->req.psn = (qp->req.psn + 1) & BTH_PSN_MASK;
पूर्ण

अटल व्योम save_state(काष्ठा rxe_send_wqe *wqe,
		       काष्ठा rxe_qp *qp,
		       काष्ठा rxe_send_wqe *rollback_wqe,
		       u32 *rollback_psn)
अणु
	rollback_wqe->state     = wqe->state;
	rollback_wqe->first_psn = wqe->first_psn;
	rollback_wqe->last_psn  = wqe->last_psn;
	*rollback_psn		= qp->req.psn;
पूर्ण

अटल व्योम rollback_state(काष्ठा rxe_send_wqe *wqe,
			   काष्ठा rxe_qp *qp,
			   काष्ठा rxe_send_wqe *rollback_wqe,
			   u32 rollback_psn)
अणु
	wqe->state     = rollback_wqe->state;
	wqe->first_psn = rollback_wqe->first_psn;
	wqe->last_psn  = rollback_wqe->last_psn;
	qp->req.psn    = rollback_psn;
पूर्ण

अटल व्योम update_state(काष्ठा rxe_qp *qp, काष्ठा rxe_send_wqe *wqe,
			 काष्ठा rxe_pkt_info *pkt, पूर्णांक payload)
अणु
	qp->req.opcode = pkt->opcode;

	अगर (pkt->mask & RXE_END_MASK)
		qp->req.wqe_index = next_index(qp->sq.queue, qp->req.wqe_index);

	qp->need_req_skb = 0;

	अगर (qp->qp_समयout_jअगरfies && !समयr_pending(&qp->retrans_समयr))
		mod_समयr(&qp->retrans_समयr,
			  jअगरfies + qp->qp_समयout_jअगरfies);
पूर्ण

पूर्णांक rxe_requester(व्योम *arg)
अणु
	काष्ठा rxe_qp *qp = (काष्ठा rxe_qp *)arg;
	काष्ठा rxe_pkt_info pkt;
	काष्ठा sk_buff *skb;
	काष्ठा rxe_send_wqe *wqe;
	क्रमागत rxe_hdr_mask mask;
	पूर्णांक payload;
	पूर्णांक mtu;
	पूर्णांक opcode;
	पूर्णांक ret;
	काष्ठा rxe_send_wqe rollback_wqe;
	u32 rollback_psn;

	rxe_add_ref(qp);

next_wqe:
	अगर (unlikely(!qp->valid || qp->req.state == QP_STATE_ERROR))
		जाओ निकास;

	अगर (unlikely(qp->req.state == QP_STATE_RESET)) अणु
		qp->req.wqe_index = consumer_index(qp->sq.queue);
		qp->req.opcode = -1;
		qp->req.need_rd_atomic = 0;
		qp->req.रुको_psn = 0;
		qp->req.need_retry = 0;
		जाओ निकास;
	पूर्ण

	अगर (unlikely(qp->req.need_retry)) अणु
		req_retry(qp);
		qp->req.need_retry = 0;
	पूर्ण

	wqe = req_next_wqe(qp);
	अगर (unlikely(!wqe))
		जाओ निकास;

	अगर (wqe->mask & WR_REG_MASK) अणु
		अगर (wqe->wr.opcode == IB_WR_LOCAL_INV) अणु
			काष्ठा rxe_dev *rxe = to_rdev(qp->ibqp.device);
			काष्ठा rxe_mr *rmr;

			rmr = rxe_pool_get_index(&rxe->mr_pool,
						 wqe->wr.ex.invalidate_rkey >> 8);
			अगर (!rmr) अणु
				pr_err("No mr for key %#x\n",
				       wqe->wr.ex.invalidate_rkey);
				wqe->state = wqe_state_error;
				wqe->status = IB_WC_MW_BIND_ERR;
				जाओ निकास;
			पूर्ण
			rmr->state = RXE_MR_STATE_FREE;
			rxe_drop_ref(rmr);
			wqe->state = wqe_state_करोne;
			wqe->status = IB_WC_SUCCESS;
		पूर्ण अन्यथा अगर (wqe->wr.opcode == IB_WR_REG_MR) अणु
			काष्ठा rxe_mr *rmr = to_rmr(wqe->wr.wr.reg.mr);

			rmr->state = RXE_MR_STATE_VALID;
			rmr->access = wqe->wr.wr.reg.access;
			rmr->ibmr.lkey = wqe->wr.wr.reg.key;
			rmr->ibmr.rkey = wqe->wr.wr.reg.key;
			rmr->iova = wqe->wr.wr.reg.mr->iova;
			wqe->state = wqe_state_करोne;
			wqe->status = IB_WC_SUCCESS;
		पूर्ण अन्यथा अणु
			जाओ निकास;
		पूर्ण
		अगर ((wqe->wr.send_flags & IB_SEND_SIGNALED) ||
		    qp->sq_sig_type == IB_SIGNAL_ALL_WR)
			rxe_run_task(&qp->comp.task, 1);
		qp->req.wqe_index = next_index(qp->sq.queue,
						qp->req.wqe_index);
		जाओ next_wqe;
	पूर्ण

	अगर (unlikely(qp_type(qp) == IB_QPT_RC &&
		psn_compare(qp->req.psn, (qp->comp.psn +
				RXE_MAX_UNACKED_PSNS)) > 0)) अणु
		qp->req.रुको_psn = 1;
		जाओ निकास;
	पूर्ण

	/* Limit the number of inflight SKBs per QP */
	अगर (unlikely(atomic_पढ़ो(&qp->skb_out) >
		     RXE_INFLIGHT_SKBS_PER_QP_HIGH)) अणु
		qp->need_req_skb = 1;
		जाओ निकास;
	पूर्ण

	opcode = next_opcode(qp, wqe, wqe->wr.opcode);
	अगर (unlikely(opcode < 0)) अणु
		wqe->status = IB_WC_LOC_QP_OP_ERR;
		जाओ निकास;
	पूर्ण

	mask = rxe_opcode[opcode].mask;
	अगर (unlikely(mask & RXE_READ_OR_ATOMIC)) अणु
		अगर (check_init_depth(qp, wqe))
			जाओ निकास;
	पूर्ण

	mtu = get_mtu(qp);
	payload = (mask & RXE_WRITE_OR_SEND) ? wqe->dma.resid : 0;
	अगर (payload > mtu) अणु
		अगर (qp_type(qp) == IB_QPT_UD) अणु
			/* C10-93.1.1: If the total sum of all the buffer lengths specअगरied क्रम a
			 * UD message exceeds the MTU of the port as वापसed by QueryHCA, the CI
			 * shall not emit any packets क्रम this message. Further, the CI shall not
			 * generate an error due to this condition.
			 */

			/* fake a successful UD send */
			wqe->first_psn = qp->req.psn;
			wqe->last_psn = qp->req.psn;
			qp->req.psn = (qp->req.psn + 1) & BTH_PSN_MASK;
			qp->req.opcode = IB_OPCODE_UD_SEND_ONLY;
			qp->req.wqe_index = next_index(qp->sq.queue,
						       qp->req.wqe_index);
			wqe->state = wqe_state_करोne;
			wqe->status = IB_WC_SUCCESS;
			__rxe_करो_task(&qp->comp.task);
			rxe_drop_ref(qp);
			वापस 0;
		पूर्ण
		payload = mtu;
	पूर्ण

	skb = init_req_packet(qp, wqe, opcode, payload, &pkt);
	अगर (unlikely(!skb)) अणु
		pr_err("qp#%d Failed allocating skb\n", qp_num(qp));
		जाओ err;
	पूर्ण

	अगर (fill_packet(qp, wqe, &pkt, skb, payload)) अणु
		pr_debug("qp#%d Error during fill packet\n", qp_num(qp));
		kमुक्त_skb(skb);
		जाओ err;
	पूर्ण

	/*
	 * To prevent a race on wqe access between requester and completer,
	 * wqe members state and psn need to be set beक्रमe calling
	 * rxe_xmit_packet().
	 * Otherwise, completer might initiate an unjustअगरied retry flow.
	 */
	save_state(wqe, qp, &rollback_wqe, &rollback_psn);
	update_wqe_state(qp, wqe, &pkt);
	update_wqe_psn(qp, wqe, &pkt, payload);
	ret = rxe_xmit_packet(qp, &pkt, skb);
	अगर (ret) अणु
		qp->need_req_skb = 1;

		rollback_state(wqe, qp, &rollback_wqe, rollback_psn);

		अगर (ret == -EAGAIN) अणु
			rxe_run_task(&qp->req.task, 1);
			जाओ निकास;
		पूर्ण

		जाओ err;
	पूर्ण

	update_state(qp, wqe, &pkt, payload);

	जाओ next_wqe;

err:
	wqe->status = IB_WC_LOC_PROT_ERR;
	wqe->state = wqe_state_error;
	__rxe_करो_task(&qp->comp.task);

निकास:
	rxe_drop_ref(qp);
	वापस -EAGAIN;
पूर्ण
