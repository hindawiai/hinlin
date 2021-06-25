<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/* Copyright (c) 2008-2019, IBM Corporation */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/net.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/llist.h>
#समावेश <यंत्र/barrier.h>
#समावेश <net/tcp.h>

#समावेश "siw.h"
#समावेश "siw_verbs.h"
#समावेश "siw_mem.h"

अटल अक्षर siw_qp_state_to_string[SIW_QP_STATE_COUNT][माप "TERMINATE"] = अणु
	[SIW_QP_STATE_IDLE] = "IDLE",
	[SIW_QP_STATE_RTR] = "RTR",
	[SIW_QP_STATE_RTS] = "RTS",
	[SIW_QP_STATE_CLOSING] = "CLOSING",
	[SIW_QP_STATE_TERMINATE] = "TERMINATE",
	[SIW_QP_STATE_ERROR] = "ERROR"
पूर्ण;

/*
 * iWARP (RDMAP, DDP and MPA) parameters as well as Softiwarp settings on a
 * per-RDMAP message basis. Please keep order of initializer. All MPA len
 * is initialized to minimum packet size.
 */
काष्ठा iwarp_msg_info iwarp_pktinfo[RDMAP_TERMINATE + 1] = अणु
	अणु /* RDMAP_RDMA_WRITE */
	  .hdr_len = माप(काष्ठा iwarp_rdma_ग_लिखो),
	  .ctrl.mpa_len = htons(माप(काष्ठा iwarp_rdma_ग_लिखो) - 2),
	  .ctrl.ddp_rdmap_ctrl = DDP_FLAG_TAGGED | DDP_FLAG_LAST |
				 cpu_to_be16(DDP_VERSION << 8) |
				 cpu_to_be16(RDMAP_VERSION << 6) |
				 cpu_to_be16(RDMAP_RDMA_WRITE),
	  .rx_data = siw_proc_ग_लिखो पूर्ण,
	अणु /* RDMAP_RDMA_READ_REQ */
	  .hdr_len = माप(काष्ठा iwarp_rdma_rreq),
	  .ctrl.mpa_len = htons(माप(काष्ठा iwarp_rdma_rreq) - 2),
	  .ctrl.ddp_rdmap_ctrl = DDP_FLAG_LAST | cpu_to_be16(DDP_VERSION << 8) |
				 cpu_to_be16(RDMAP_VERSION << 6) |
				 cpu_to_be16(RDMAP_RDMA_READ_REQ),
	  .rx_data = siw_proc_rreq पूर्ण,
	अणु /* RDMAP_RDMA_READ_RESP */
	  .hdr_len = माप(काष्ठा iwarp_rdma_rresp),
	  .ctrl.mpa_len = htons(माप(काष्ठा iwarp_rdma_rresp) - 2),
	  .ctrl.ddp_rdmap_ctrl = DDP_FLAG_TAGGED | DDP_FLAG_LAST |
				 cpu_to_be16(DDP_VERSION << 8) |
				 cpu_to_be16(RDMAP_VERSION << 6) |
				 cpu_to_be16(RDMAP_RDMA_READ_RESP),
	  .rx_data = siw_proc_rresp पूर्ण,
	अणु /* RDMAP_SEND */
	  .hdr_len = माप(काष्ठा iwarp_send),
	  .ctrl.mpa_len = htons(माप(काष्ठा iwarp_send) - 2),
	  .ctrl.ddp_rdmap_ctrl = DDP_FLAG_LAST | cpu_to_be16(DDP_VERSION << 8) |
				 cpu_to_be16(RDMAP_VERSION << 6) |
				 cpu_to_be16(RDMAP_SEND),
	  .rx_data = siw_proc_send पूर्ण,
	अणु /* RDMAP_SEND_INVAL */
	  .hdr_len = माप(काष्ठा iwarp_send_inv),
	  .ctrl.mpa_len = htons(माप(काष्ठा iwarp_send_inv) - 2),
	  .ctrl.ddp_rdmap_ctrl = DDP_FLAG_LAST | cpu_to_be16(DDP_VERSION << 8) |
				 cpu_to_be16(RDMAP_VERSION << 6) |
				 cpu_to_be16(RDMAP_SEND_INVAL),
	  .rx_data = siw_proc_send पूर्ण,
	अणु /* RDMAP_SEND_SE */
	  .hdr_len = माप(काष्ठा iwarp_send),
	  .ctrl.mpa_len = htons(माप(काष्ठा iwarp_send) - 2),
	  .ctrl.ddp_rdmap_ctrl = DDP_FLAG_LAST | cpu_to_be16(DDP_VERSION << 8) |
				 cpu_to_be16(RDMAP_VERSION << 6) |
				 cpu_to_be16(RDMAP_SEND_SE),
	  .rx_data = siw_proc_send पूर्ण,
	अणु /* RDMAP_SEND_SE_INVAL */
	  .hdr_len = माप(काष्ठा iwarp_send_inv),
	  .ctrl.mpa_len = htons(माप(काष्ठा iwarp_send_inv) - 2),
	  .ctrl.ddp_rdmap_ctrl = DDP_FLAG_LAST | cpu_to_be16(DDP_VERSION << 8) |
				 cpu_to_be16(RDMAP_VERSION << 6) |
				 cpu_to_be16(RDMAP_SEND_SE_INVAL),
	  .rx_data = siw_proc_send पूर्ण,
	अणु /* RDMAP_TERMINATE */
	  .hdr_len = माप(काष्ठा iwarp_terminate),
	  .ctrl.mpa_len = htons(माप(काष्ठा iwarp_terminate) - 2),
	  .ctrl.ddp_rdmap_ctrl = DDP_FLAG_LAST | cpu_to_be16(DDP_VERSION << 8) |
				 cpu_to_be16(RDMAP_VERSION << 6) |
				 cpu_to_be16(RDMAP_TERMINATE),
	  .rx_data = siw_proc_terminate पूर्ण
पूर्ण;

व्योम siw_qp_llp_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा siw_qp *qp;

	पढ़ो_lock(&sk->sk_callback_lock);

	अगर (unlikely(!sk->sk_user_data || !sk_to_qp(sk)))
		जाओ करोne;

	qp = sk_to_qp(sk);

	अगर (likely(!qp->rx_stream.rx_suspend &&
		   करोwn_पढ़ो_trylock(&qp->state_lock))) अणु
		पढ़ो_descriptor_t rd_desc = अणु .arg.data = qp, .count = 1 पूर्ण;

		अगर (likely(qp->attrs.state == SIW_QP_STATE_RTS))
			/*
			 * Implements data receive operation during
			 * socket callback. TCP gracefully catches
			 * the हाल where there is nothing to receive
			 * (not calling siw_tcp_rx_data() then).
			 */
			tcp_पढ़ो_sock(sk, &rd_desc, siw_tcp_rx_data);

		up_पढ़ो(&qp->state_lock);
	पूर्ण अन्यथा अणु
		siw_dbg_qp(qp, "unable to process RX, suspend: %d\n",
			   qp->rx_stream.rx_suspend);
	पूर्ण
करोne:
	पढ़ो_unlock(&sk->sk_callback_lock);
पूर्ण

व्योम siw_qp_llp_बंद(काष्ठा siw_qp *qp)
अणु
	siw_dbg_qp(qp, "enter llp close, state = %s\n",
		   siw_qp_state_to_string[qp->attrs.state]);

	करोwn_ग_लिखो(&qp->state_lock);

	qp->rx_stream.rx_suspend = 1;
	qp->tx_ctx.tx_suspend = 1;
	qp->attrs.sk = शून्य;

	चयन (qp->attrs.state) अणु
	हाल SIW_QP_STATE_RTS:
	हाल SIW_QP_STATE_RTR:
	हाल SIW_QP_STATE_IDLE:
	हाल SIW_QP_STATE_TERMINATE:
		qp->attrs.state = SIW_QP_STATE_ERROR;
		अवरोध;
	/*
	 * SIW_QP_STATE_CLOSING:
	 *
	 * This is a क्रमced बंद. shall the QP be moved to
	 * ERROR or IDLE ?
	 */
	हाल SIW_QP_STATE_CLOSING:
		अगर (tx_wqe(qp)->wr_status == SIW_WR_IDLE)
			qp->attrs.state = SIW_QP_STATE_ERROR;
		अन्यथा
			qp->attrs.state = SIW_QP_STATE_IDLE;
		अवरोध;

	शेष:
		siw_dbg_qp(qp, "llp close: no state transition needed: %s\n",
			   siw_qp_state_to_string[qp->attrs.state]);
		अवरोध;
	पूर्ण
	siw_sq_flush(qp);
	siw_rq_flush(qp);

	/*
	 * Dereference closing CEP
	 */
	अगर (qp->cep) अणु
		siw_cep_put(qp->cep);
		qp->cep = शून्य;
	पूर्ण

	up_ग_लिखो(&qp->state_lock);

	siw_dbg_qp(qp, "llp close exit: state %s\n",
		   siw_qp_state_to_string[qp->attrs.state]);
पूर्ण

/*
 * socket callback routine inक्रमming about newly available send space.
 * Function schedules SQ work क्रम processing SQ items.
 */
व्योम siw_qp_llp_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा siw_cep *cep;

	पढ़ो_lock(&sk->sk_callback_lock);

	cep  = sk_to_cep(sk);
	अगर (cep) अणु
		cep->sk_ग_लिखो_space(sk);

		अगर (!test_bit(SOCK_NOSPACE, &sk->sk_socket->flags))
			(व्योम)siw_sq_start(cep->qp);
	पूर्ण

	पढ़ो_unlock(&sk->sk_callback_lock);
पूर्ण

अटल पूर्णांक siw_qp_पढ़ोq_init(काष्ठा siw_qp *qp, पूर्णांक irq_size, पूर्णांक orq_size)
अणु
	अगर (irq_size) अणु
		irq_size = roundup_घात_of_two(irq_size);
		qp->irq = vzalloc(irq_size * माप(काष्ठा siw_sqe));
		अगर (!qp->irq) अणु
			qp->attrs.irq_size = 0;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	अगर (orq_size) अणु
		orq_size = roundup_घात_of_two(orq_size);
		qp->orq = vzalloc(orq_size * माप(काष्ठा siw_sqe));
		अगर (!qp->orq) अणु
			qp->attrs.orq_size = 0;
			qp->attrs.irq_size = 0;
			vमुक्त(qp->irq);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	qp->attrs.irq_size = irq_size;
	qp->attrs.orq_size = orq_size;
	siw_dbg_qp(qp, "ORD %d, IRD %d\n", orq_size, irq_size);
	वापस 0;
पूर्ण

अटल पूर्णांक siw_qp_enable_crc(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_rx_stream *c_rx = &qp->rx_stream;
	काष्ठा siw_iwarp_tx *c_tx = &qp->tx_ctx;
	पूर्णांक size;

	अगर (siw_crypto_shash == शून्य)
		वापस -ENOENT;

	size = crypto_shash_descsize(siw_crypto_shash) +
		माप(काष्ठा shash_desc);

	c_tx->mpa_crc_hd = kzalloc(size, GFP_KERNEL);
	c_rx->mpa_crc_hd = kzalloc(size, GFP_KERNEL);
	अगर (!c_tx->mpa_crc_hd || !c_rx->mpa_crc_hd) अणु
		kमुक्त(c_tx->mpa_crc_hd);
		kमुक्त(c_rx->mpa_crc_hd);
		c_tx->mpa_crc_hd = शून्य;
		c_rx->mpa_crc_hd = शून्य;
		वापस -ENOMEM;
	पूर्ण
	c_tx->mpa_crc_hd->tfm = siw_crypto_shash;
	c_rx->mpa_crc_hd->tfm = siw_crypto_shash;

	वापस 0;
पूर्ण

/*
 * Send a non संकेतled READ or WRITE to peer side as negotiated
 * with MPAv2 P2P setup protocol. The work request is only created
 * as a current active WR and करोes not consume Send Queue space.
 *
 * Caller must hold QP state lock.
 */
पूर्णांक siw_qp_mpa_rts(काष्ठा siw_qp *qp, क्रमागत mpa_v2_ctrl ctrl)
अणु
	काष्ठा siw_wqe *wqe = tx_wqe(qp);
	अचिन्हित दीर्घ flags;
	पूर्णांक rv = 0;

	spin_lock_irqsave(&qp->sq_lock, flags);

	अगर (unlikely(wqe->wr_status != SIW_WR_IDLE)) अणु
		spin_unlock_irqrestore(&qp->sq_lock, flags);
		वापस -EIO;
	पूर्ण
	स_रखो(wqe->mem, 0, माप(*wqe->mem) * SIW_MAX_SGE);

	wqe->wr_status = SIW_WR_QUEUED;
	wqe->sqe.flags = 0;
	wqe->sqe.num_sge = 1;
	wqe->sqe.sge[0].length = 0;
	wqe->sqe.sge[0].laddr = 0;
	wqe->sqe.sge[0].lkey = 0;
	/*
	 * While it must not be checked क्रम inbound zero length
	 * READ/WRITE, some HW may treat STag 0 special.
	 */
	wqe->sqe.rkey = 1;
	wqe->sqe.raddr = 0;
	wqe->processed = 0;

	अगर (ctrl & MPA_V2_RDMA_WRITE_RTR)
		wqe->sqe.opcode = SIW_OP_WRITE;
	अन्यथा अगर (ctrl & MPA_V2_RDMA_READ_RTR) अणु
		काष्ठा siw_sqe *rreq = शून्य;

		wqe->sqe.opcode = SIW_OP_READ;

		spin_lock(&qp->orq_lock);

		अगर (qp->attrs.orq_size)
			rreq = orq_get_मुक्त(qp);
		अगर (rreq) अणु
			siw_पढ़ो_to_orq(rreq, &wqe->sqe);
			qp->orq_put++;
		पूर्ण अन्यथा
			rv = -EIO;

		spin_unlock(&qp->orq_lock);
	पूर्ण अन्यथा
		rv = -EINVAL;

	अगर (rv)
		wqe->wr_status = SIW_WR_IDLE;

	spin_unlock_irqrestore(&qp->sq_lock, flags);

	अगर (!rv)
		rv = siw_sq_start(qp);

	वापस rv;
पूर्ण

/*
 * Map memory access error to DDP tagged error
 */
क्रमागत ddp_ecode siw_tagged_error(क्रमागत siw_access_state state)
अणु
	चयन (state) अणु
	हाल E_STAG_INVALID:
		वापस DDP_ECODE_T_INVALID_STAG;
	हाल E_BASE_BOUNDS:
		वापस DDP_ECODE_T_BASE_BOUNDS;
	हाल E_PD_MISMATCH:
		वापस DDP_ECODE_T_STAG_NOT_ASSOC;
	हाल E_ACCESS_PERM:
		/*
		 * RFC 5041 (DDP) lacks an ecode क्रम insufficient access
		 * permissions. 'Invalid STag' seem to be the बंदst
		 * match though.
		 */
		वापस DDP_ECODE_T_INVALID_STAG;
	शेष:
		WARN_ON(1);
		वापस DDP_ECODE_T_INVALID_STAG;
	पूर्ण
पूर्ण

/*
 * Map memory access error to RDMAP protection error
 */
क्रमागत rdmap_ecode siw_rdmap_error(क्रमागत siw_access_state state)
अणु
	चयन (state) अणु
	हाल E_STAG_INVALID:
		वापस RDMAP_ECODE_INVALID_STAG;
	हाल E_BASE_BOUNDS:
		वापस RDMAP_ECODE_BASE_BOUNDS;
	हाल E_PD_MISMATCH:
		वापस RDMAP_ECODE_STAG_NOT_ASSOC;
	हाल E_ACCESS_PERM:
		वापस RDMAP_ECODE_ACCESS_RIGHTS;
	शेष:
		वापस RDMAP_ECODE_UNSPECIFIED;
	पूर्ण
पूर्ण

व्योम siw_init_terminate(काष्ठा siw_qp *qp, क्रमागत term_elayer layer, u8 etype,
			u8 ecode, पूर्णांक in_tx)
अणु
	अगर (!qp->term_info.valid) अणु
		स_रखो(&qp->term_info, 0, माप(qp->term_info));
		qp->term_info.layer = layer;
		qp->term_info.etype = etype;
		qp->term_info.ecode = ecode;
		qp->term_info.in_tx = in_tx;
		qp->term_info.valid = 1;
	पूर्ण
	siw_dbg_qp(qp, "init TERM: layer %d, type %d, code %d, in tx %s\n",
		   layer, etype, ecode, in_tx ? "yes" : "no");
पूर्ण

/*
 * Send a TERMINATE message, as defined in RFC's 5040/5041/5044/6581.
 * Sending TERMINATE messages is best efक्रमt - such messages
 * can only be send अगर the QP is still connected and it करोes
 * not have another outbound message in-progress, i.e. the
 * TERMINATE message must not पूर्णांकerfer with an incomplete current
 * transmit operation.
 */
व्योम siw_send_terminate(काष्ठा siw_qp *qp)
अणु
	काष्ठा kvec iov[3];
	काष्ठा msghdr msg = अणु .msg_flags = MSG_DONTWAIT | MSG_EOR पूर्ण;
	काष्ठा iwarp_terminate *term = शून्य;
	जोड़ iwarp_hdr *err_hdr = शून्य;
	काष्ठा socket *s = qp->attrs.sk;
	काष्ठा siw_rx_stream *srx = &qp->rx_stream;
	जोड़ iwarp_hdr *rx_hdr = &srx->hdr;
	u32 crc = 0;
	पूर्णांक num_frags, len_terminate, rv;

	अगर (!qp->term_info.valid)
		वापस;

	qp->term_info.valid = 0;

	अगर (tx_wqe(qp)->wr_status == SIW_WR_INPROGRESS) अणु
		siw_dbg_qp(qp, "cannot send TERMINATE: op %d in progress\n",
			   tx_type(tx_wqe(qp)));
		वापस;
	पूर्ण
	अगर (!s && qp->cep)
		/* QP not yet in RTS. Take socket from connection end poपूर्णांक */
		s = qp->cep->sock;

	अगर (!s) अणु
		siw_dbg_qp(qp, "cannot send TERMINATE: not connected\n");
		वापस;
	पूर्ण

	term = kzalloc(माप(*term), GFP_KERNEL);
	अगर (!term)
		वापस;

	term->ddp_qn = cpu_to_be32(RDMAP_UNTAGGED_QN_TERMINATE);
	term->ddp_mo = 0;
	term->ddp_msn = cpu_to_be32(1);

	iov[0].iov_base = term;
	iov[0].iov_len = माप(*term);

	अगर ((qp->term_info.layer == TERM_ERROR_LAYER_DDP) ||
	    ((qp->term_info.layer == TERM_ERROR_LAYER_RDMAP) &&
	     (qp->term_info.etype != RDMAP_ETYPE_CATASTROPHIC))) अणु
		err_hdr = kzalloc(माप(*err_hdr), GFP_KERNEL);
		अगर (!err_hdr) अणु
			kमुक्त(term);
			वापस;
		पूर्ण
	पूर्ण
	स_नकल(&term->ctrl, &iwarp_pktinfo[RDMAP_TERMINATE].ctrl,
	       माप(काष्ठा iwarp_ctrl));

	__rdmap_term_set_layer(term, qp->term_info.layer);
	__rdmap_term_set_etype(term, qp->term_info.etype);
	__rdmap_term_set_ecode(term, qp->term_info.ecode);

	चयन (qp->term_info.layer) अणु
	हाल TERM_ERROR_LAYER_RDMAP:
		अगर (qp->term_info.etype == RDMAP_ETYPE_CATASTROPHIC)
			/* No additional DDP/RDMAP header to be included */
			अवरोध;

		अगर (qp->term_info.etype == RDMAP_ETYPE_REMOTE_PROTECTION) अणु
			/*
			 * Complete RDMAP frame will get attached, and
			 * DDP segment length is valid
			 */
			term->flag_m = 1;
			term->flag_d = 1;
			term->flag_r = 1;

			अगर (qp->term_info.in_tx) अणु
				काष्ठा iwarp_rdma_rreq *rreq;
				काष्ठा siw_wqe *wqe = tx_wqe(qp);

				/* Inbound RREQ error, detected during
				 * RRESP creation. Take state from
				 * current TX work queue element to
				 * reस्थिरruct peers RREQ.
				 */
				rreq = (काष्ठा iwarp_rdma_rreq *)err_hdr;

				स_नकल(&rreq->ctrl,
				       &iwarp_pktinfo[RDMAP_RDMA_READ_REQ].ctrl,
				       माप(काष्ठा iwarp_ctrl));

				rreq->rsvd = 0;
				rreq->ddp_qn =
					htonl(RDMAP_UNTAGGED_QN_RDMA_READ);

				/* Provide RREQ's MSN as kept aside */
				rreq->ddp_msn = htonl(wqe->sqe.sge[0].length);

				rreq->ddp_mo = htonl(wqe->processed);
				rreq->sink_stag = htonl(wqe->sqe.rkey);
				rreq->sink_to = cpu_to_be64(wqe->sqe.raddr);
				rreq->पढ़ो_size = htonl(wqe->sqe.sge[0].length);
				rreq->source_stag = htonl(wqe->sqe.sge[0].lkey);
				rreq->source_to =
					cpu_to_be64(wqe->sqe.sge[0].laddr);

				iov[1].iov_base = rreq;
				iov[1].iov_len = माप(*rreq);

				rx_hdr = (जोड़ iwarp_hdr *)rreq;
			पूर्ण अन्यथा अणु
				/* Take RDMAP/DDP inक्रमmation from
				 * current (failed) inbound frame.
				 */
				iov[1].iov_base = rx_hdr;

				अगर (__rdmap_get_opcode(&rx_hdr->ctrl) ==
				    RDMAP_RDMA_READ_REQ)
					iov[1].iov_len =
						माप(काष्ठा iwarp_rdma_rreq);
				अन्यथा /* SEND type */
					iov[1].iov_len =
						माप(काष्ठा iwarp_send);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Do not report DDP hdr inक्रमmation अगर packet
			 * layout is unknown
			 */
			अगर ((qp->term_info.ecode == RDMAP_ECODE_VERSION) ||
			    (qp->term_info.ecode == RDMAP_ECODE_OPCODE))
				अवरोध;

			iov[1].iov_base = rx_hdr;

			/* Only DDP frame will get attached */
			अगर (rx_hdr->ctrl.ddp_rdmap_ctrl & DDP_FLAG_TAGGED)
				iov[1].iov_len =
					माप(काष्ठा iwarp_rdma_ग_लिखो);
			अन्यथा
				iov[1].iov_len = माप(काष्ठा iwarp_send);

			term->flag_m = 1;
			term->flag_d = 1;
		पूर्ण
		term->ctrl.mpa_len = cpu_to_be16(iov[1].iov_len);
		अवरोध;

	हाल TERM_ERROR_LAYER_DDP:
		/* Report error encountered जबतक DDP processing.
		 * This can only happen as a result of inbound
		 * DDP processing
		 */

		/* Do not report DDP hdr inक्रमmation अगर packet
		 * layout is unknown
		 */
		अगर (((qp->term_info.etype == DDP_ETYPE_TAGGED_BUF) &&
		     (qp->term_info.ecode == DDP_ECODE_T_VERSION)) ||
		    ((qp->term_info.etype == DDP_ETYPE_UNTAGGED_BUF) &&
		     (qp->term_info.ecode == DDP_ECODE_UT_VERSION)))
			अवरोध;

		iov[1].iov_base = rx_hdr;

		अगर (rx_hdr->ctrl.ddp_rdmap_ctrl & DDP_FLAG_TAGGED)
			iov[1].iov_len = माप(काष्ठा iwarp_ctrl_tagged);
		अन्यथा
			iov[1].iov_len = माप(काष्ठा iwarp_ctrl_untagged);

		term->flag_m = 1;
		term->flag_d = 1;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	अगर (term->flag_m || term->flag_d || term->flag_r) अणु
		iov[2].iov_base = &crc;
		iov[2].iov_len = माप(crc);
		len_terminate = माप(*term) + iov[1].iov_len + MPA_CRC_SIZE;
		num_frags = 3;
	पूर्ण अन्यथा अणु
		iov[1].iov_base = &crc;
		iov[1].iov_len = माप(crc);
		len_terminate = माप(*term) + MPA_CRC_SIZE;
		num_frags = 2;
	पूर्ण

	/* Adjust DDP Segment Length parameter, अगर valid */
	अगर (term->flag_m) अणु
		u32 real_ddp_len = be16_to_cpu(rx_hdr->ctrl.mpa_len);
		क्रमागत rdma_opcode op = __rdmap_get_opcode(&rx_hdr->ctrl);

		real_ddp_len -= iwarp_pktinfo[op].hdr_len - MPA_HDR_SIZE;
		rx_hdr->ctrl.mpa_len = cpu_to_be16(real_ddp_len);
	पूर्ण

	term->ctrl.mpa_len =
		cpu_to_be16(len_terminate - (MPA_HDR_SIZE + MPA_CRC_SIZE));
	अगर (qp->tx_ctx.mpa_crc_hd) अणु
		crypto_shash_init(qp->tx_ctx.mpa_crc_hd);
		अगर (crypto_shash_update(qp->tx_ctx.mpa_crc_hd,
					(u8 *)iov[0].iov_base,
					iov[0].iov_len))
			जाओ out;

		अगर (num_frags == 3) अणु
			अगर (crypto_shash_update(qp->tx_ctx.mpa_crc_hd,
						(u8 *)iov[1].iov_base,
						iov[1].iov_len))
				जाओ out;
		पूर्ण
		crypto_shash_final(qp->tx_ctx.mpa_crc_hd, (u8 *)&crc);
	पूर्ण

	rv = kernel_sendmsg(s, &msg, iov, num_frags, len_terminate);
	siw_dbg_qp(qp, "sent TERM: %s, layer %d, type %d, code %d (%d bytes)\n",
		   rv == len_terminate ? "success" : "failure",
		   __rdmap_term_layer(term), __rdmap_term_etype(term),
		   __rdmap_term_ecode(term), rv);
out:
	kमुक्त(term);
	kमुक्त(err_hdr);
पूर्ण

/*
 * Handle all attrs other than state
 */
अटल व्योम siw_qp_modअगरy_nonstate(काष्ठा siw_qp *qp,
				   काष्ठा siw_qp_attrs *attrs,
				   क्रमागत siw_qp_attr_mask mask)
अणु
	अगर (mask & SIW_QP_ATTR_ACCESS_FLAGS) अणु
		अगर (attrs->flags & SIW_RDMA_BIND_ENABLED)
			qp->attrs.flags |= SIW_RDMA_BIND_ENABLED;
		अन्यथा
			qp->attrs.flags &= ~SIW_RDMA_BIND_ENABLED;

		अगर (attrs->flags & SIW_RDMA_WRITE_ENABLED)
			qp->attrs.flags |= SIW_RDMA_WRITE_ENABLED;
		अन्यथा
			qp->attrs.flags &= ~SIW_RDMA_WRITE_ENABLED;

		अगर (attrs->flags & SIW_RDMA_READ_ENABLED)
			qp->attrs.flags |= SIW_RDMA_READ_ENABLED;
		अन्यथा
			qp->attrs.flags &= ~SIW_RDMA_READ_ENABLED;
	पूर्ण
पूर्ण

अटल पूर्णांक siw_qp_nextstate_from_idle(काष्ठा siw_qp *qp,
				      काष्ठा siw_qp_attrs *attrs,
				      क्रमागत siw_qp_attr_mask mask)
अणु
	पूर्णांक rv = 0;

	चयन (attrs->state) अणु
	हाल SIW_QP_STATE_RTS:
		अगर (attrs->flags & SIW_MPA_CRC) अणु
			rv = siw_qp_enable_crc(qp);
			अगर (rv)
				अवरोध;
		पूर्ण
		अगर (!(mask & SIW_QP_ATTR_LLP_HANDLE)) अणु
			siw_dbg_qp(qp, "no socket\n");
			rv = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (!(mask & SIW_QP_ATTR_MPA)) अणु
			siw_dbg_qp(qp, "no MPA\n");
			rv = -EINVAL;
			अवरोध;
		पूर्ण
		/*
		 * Initialize iWARP TX state
		 */
		qp->tx_ctx.ddp_msn[RDMAP_UNTAGGED_QN_SEND] = 0;
		qp->tx_ctx.ddp_msn[RDMAP_UNTAGGED_QN_RDMA_READ] = 0;
		qp->tx_ctx.ddp_msn[RDMAP_UNTAGGED_QN_TERMINATE] = 0;

		/*
		 * Initialize iWARP RX state
		 */
		qp->rx_stream.ddp_msn[RDMAP_UNTAGGED_QN_SEND] = 1;
		qp->rx_stream.ddp_msn[RDMAP_UNTAGGED_QN_RDMA_READ] = 1;
		qp->rx_stream.ddp_msn[RDMAP_UNTAGGED_QN_TERMINATE] = 1;

		/*
		 * init IRD मुक्त queue, caller has alपढ़ोy checked
		 * limits.
		 */
		rv = siw_qp_पढ़ोq_init(qp, attrs->irq_size,
				       attrs->orq_size);
		अगर (rv)
			अवरोध;

		qp->attrs.sk = attrs->sk;
		qp->attrs.state = SIW_QP_STATE_RTS;

		siw_dbg_qp(qp, "enter RTS: crc=%s, ord=%u, ird=%u\n",
			   attrs->flags & SIW_MPA_CRC ? "y" : "n",
			   qp->attrs.orq_size, qp->attrs.irq_size);
		अवरोध;

	हाल SIW_QP_STATE_ERROR:
		siw_rq_flush(qp);
		qp->attrs.state = SIW_QP_STATE_ERROR;
		अगर (qp->cep) अणु
			siw_cep_put(qp->cep);
			qp->cep = शून्य;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस rv;
पूर्ण

अटल पूर्णांक siw_qp_nextstate_from_rts(काष्ठा siw_qp *qp,
				     काष्ठा siw_qp_attrs *attrs)
अणु
	पूर्णांक drop_conn = 0;

	चयन (attrs->state) अणु
	हाल SIW_QP_STATE_CLOSING:
		/*
		 * Verbs: move to IDLE अगर SQ and ORQ are empty.
		 * Move to ERROR otherwise. But first of all we must
		 * बंद the connection. So we keep CLOSING or ERROR
		 * as a transient state, schedule connection drop work
		 * and रुको क्रम the socket state change upcall to
		 * come back बंदd.
		 */
		अगर (tx_wqe(qp)->wr_status == SIW_WR_IDLE) अणु
			qp->attrs.state = SIW_QP_STATE_CLOSING;
		पूर्ण अन्यथा अणु
			qp->attrs.state = SIW_QP_STATE_ERROR;
			siw_sq_flush(qp);
		पूर्ण
		siw_rq_flush(qp);

		drop_conn = 1;
		अवरोध;

	हाल SIW_QP_STATE_TERMINATE:
		qp->attrs.state = SIW_QP_STATE_TERMINATE;

		siw_init_terminate(qp, TERM_ERROR_LAYER_RDMAP,
				   RDMAP_ETYPE_CATASTROPHIC,
				   RDMAP_ECODE_UNSPECIFIED, 1);
		drop_conn = 1;
		अवरोध;

	हाल SIW_QP_STATE_ERROR:
		/*
		 * This is an emergency बंद.
		 *
		 * Any in progress transmit operation will get
		 * cancelled.
		 * This will likely result in a protocol failure,
		 * अगर a TX operation is in transit. The caller
		 * could unconditional रुको to give the current
		 * operation a chance to complete.
		 * Esp., how to handle the non-empty IRQ हाल?
		 * The peer was asking क्रम data transfer at a valid
		 * poपूर्णांक in समय.
		 */
		siw_sq_flush(qp);
		siw_rq_flush(qp);
		qp->attrs.state = SIW_QP_STATE_ERROR;
		drop_conn = 1;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस drop_conn;
पूर्ण

अटल व्योम siw_qp_nextstate_from_term(काष्ठा siw_qp *qp,
				       काष्ठा siw_qp_attrs *attrs)
अणु
	चयन (attrs->state) अणु
	हाल SIW_QP_STATE_ERROR:
		siw_rq_flush(qp);
		qp->attrs.state = SIW_QP_STATE_ERROR;

		अगर (tx_wqe(qp)->wr_status != SIW_WR_IDLE)
			siw_sq_flush(qp);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक siw_qp_nextstate_from_बंद(काष्ठा siw_qp *qp,
				       काष्ठा siw_qp_attrs *attrs)
अणु
	पूर्णांक rv = 0;

	चयन (attrs->state) अणु
	हाल SIW_QP_STATE_IDLE:
		WARN_ON(tx_wqe(qp)->wr_status != SIW_WR_IDLE);
		qp->attrs.state = SIW_QP_STATE_IDLE;
		अवरोध;

	हाल SIW_QP_STATE_CLOSING:
		/*
		 * The LLP may alपढ़ोy moved the QP to closing
		 * due to graceful peer बंद init
		 */
		अवरोध;

	हाल SIW_QP_STATE_ERROR:
		/*
		 * QP was moved to CLOSING by LLP event
		 * not yet seen by user.
		 */
		qp->attrs.state = SIW_QP_STATE_ERROR;

		अगर (tx_wqe(qp)->wr_status != SIW_WR_IDLE)
			siw_sq_flush(qp);

		siw_rq_flush(qp);
		अवरोध;

	शेष:
		siw_dbg_qp(qp, "state transition undefined: %s => %s\n",
			   siw_qp_state_to_string[qp->attrs.state],
			   siw_qp_state_to_string[attrs->state]);

		rv = -ECONNABORTED;
	पूर्ण
	वापस rv;
पूर्ण

/*
 * Caller must hold qp->state_lock
 */
पूर्णांक siw_qp_modअगरy(काष्ठा siw_qp *qp, काष्ठा siw_qp_attrs *attrs,
		  क्रमागत siw_qp_attr_mask mask)
अणु
	पूर्णांक drop_conn = 0, rv = 0;

	अगर (!mask)
		वापस 0;

	siw_dbg_qp(qp, "state: %s => %s\n",
		   siw_qp_state_to_string[qp->attrs.state],
		   siw_qp_state_to_string[attrs->state]);

	अगर (mask != SIW_QP_ATTR_STATE)
		siw_qp_modअगरy_nonstate(qp, attrs, mask);

	अगर (!(mask & SIW_QP_ATTR_STATE))
		वापस 0;

	चयन (qp->attrs.state) अणु
	हाल SIW_QP_STATE_IDLE:
	हाल SIW_QP_STATE_RTR:
		rv = siw_qp_nextstate_from_idle(qp, attrs, mask);
		अवरोध;

	हाल SIW_QP_STATE_RTS:
		drop_conn = siw_qp_nextstate_from_rts(qp, attrs);
		अवरोध;

	हाल SIW_QP_STATE_TERMINATE:
		siw_qp_nextstate_from_term(qp, attrs);
		अवरोध;

	हाल SIW_QP_STATE_CLOSING:
		siw_qp_nextstate_from_बंद(qp, attrs);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (drop_conn)
		siw_qp_cm_drop(qp, 0);

	वापस rv;
पूर्ण

व्योम siw_पढ़ो_to_orq(काष्ठा siw_sqe *rreq, काष्ठा siw_sqe *sqe)
अणु
	rreq->id = sqe->id;
	rreq->opcode = sqe->opcode;
	rreq->sge[0].laddr = sqe->sge[0].laddr;
	rreq->sge[0].length = sqe->sge[0].length;
	rreq->sge[0].lkey = sqe->sge[0].lkey;
	rreq->sge[1].lkey = sqe->sge[1].lkey;
	rreq->flags = sqe->flags | SIW_WQE_VALID;
	rreq->num_sge = 1;
पूर्ण

अटल पूर्णांक siw_activate_tx_from_sq(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_sqe *sqe;
	काष्ठा siw_wqe *wqe = tx_wqe(qp);
	पूर्णांक rv = 1;

	sqe = sq_get_next(qp);
	अगर (!sqe)
		वापस 0;

	स_रखो(wqe->mem, 0, माप(*wqe->mem) * SIW_MAX_SGE);
	wqe->wr_status = SIW_WR_QUEUED;

	/* First copy SQE to kernel निजी memory */
	स_नकल(&wqe->sqe, sqe, माप(*sqe));

	अगर (wqe->sqe.opcode >= SIW_NUM_OPCODES) अणु
		rv = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (wqe->sqe.flags & SIW_WQE_INLINE) अणु
		अगर (wqe->sqe.opcode != SIW_OP_SEND &&
		    wqe->sqe.opcode != SIW_OP_WRITE) अणु
			rv = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (wqe->sqe.sge[0].length > SIW_MAX_INLINE) अणु
			rv = -EINVAL;
			जाओ out;
		पूर्ण
		wqe->sqe.sge[0].laddr = (uपूर्णांकptr_t)&wqe->sqe.sge[1];
		wqe->sqe.sge[0].lkey = 0;
		wqe->sqe.num_sge = 1;
	पूर्ण
	अगर (wqe->sqe.flags & SIW_WQE_READ_FENCE) अणु
		/* A READ cannot be fenced */
		अगर (unlikely(wqe->sqe.opcode == SIW_OP_READ ||
			     wqe->sqe.opcode ==
				     SIW_OP_READ_LOCAL_INV)) अणु
			siw_dbg_qp(qp, "cannot fence read\n");
			rv = -EINVAL;
			जाओ out;
		पूर्ण
		spin_lock(&qp->orq_lock);

		अगर (qp->attrs.orq_size && !siw_orq_empty(qp)) अणु
			qp->tx_ctx.orq_fence = 1;
			rv = 0;
		पूर्ण
		spin_unlock(&qp->orq_lock);

	पूर्ण अन्यथा अगर (wqe->sqe.opcode == SIW_OP_READ ||
		   wqe->sqe.opcode == SIW_OP_READ_LOCAL_INV) अणु
		काष्ठा siw_sqe *rreq;

		अगर (unlikely(!qp->attrs.orq_size)) अणु
			/* We negotiated not to send READ req's */
			rv = -EINVAL;
			जाओ out;
		पूर्ण
		wqe->sqe.num_sge = 1;

		spin_lock(&qp->orq_lock);

		rreq = orq_get_मुक्त(qp);
		अगर (rreq) अणु
			/*
			 * Make an immediate copy in ORQ to be पढ़ोy
			 * to process loopback READ reply
			 */
			siw_पढ़ो_to_orq(rreq, &wqe->sqe);
			qp->orq_put++;
		पूर्ण अन्यथा अणु
			qp->tx_ctx.orq_fence = 1;
			rv = 0;
		पूर्ण
		spin_unlock(&qp->orq_lock);
	पूर्ण

	/* Clear SQE, can be re-used by application */
	smp_store_mb(sqe->flags, 0);
	qp->sq_get++;
out:
	अगर (unlikely(rv < 0)) अणु
		siw_dbg_qp(qp, "error %d\n", rv);
		wqe->wr_status = SIW_WR_IDLE;
	पूर्ण
	वापस rv;
पूर्ण

/*
 * Must be called with SQ locked.
 * To aव्योम complete SQ starvation by स्थिरant inbound READ requests,
 * the active IRQ will not be served after qp->irq_burst, अगर the
 * SQ has pending work.
 */
पूर्णांक siw_activate_tx(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_sqe *irqe;
	काष्ठा siw_wqe *wqe = tx_wqe(qp);

	अगर (!qp->attrs.irq_size)
		वापस siw_activate_tx_from_sq(qp);

	irqe = &qp->irq[qp->irq_get % qp->attrs.irq_size];

	अगर (!(irqe->flags & SIW_WQE_VALID))
		वापस siw_activate_tx_from_sq(qp);

	/*
	 * Aव्योम local WQE processing starvation in हाल
	 * of स्थिरant inbound READ request stream
	 */
	अगर (sq_get_next(qp) && ++qp->irq_burst >= SIW_IRQ_MAXBURST_SQ_ACTIVE) अणु
		qp->irq_burst = 0;
		वापस siw_activate_tx_from_sq(qp);
	पूर्ण
	स_रखो(wqe->mem, 0, माप(*wqe->mem) * SIW_MAX_SGE);
	wqe->wr_status = SIW_WR_QUEUED;

	/* start READ RESPONSE */
	wqe->sqe.opcode = SIW_OP_READ_RESPONSE;
	wqe->sqe.flags = 0;
	अगर (irqe->num_sge) अणु
		wqe->sqe.num_sge = 1;
		wqe->sqe.sge[0].length = irqe->sge[0].length;
		wqe->sqe.sge[0].laddr = irqe->sge[0].laddr;
		wqe->sqe.sge[0].lkey = irqe->sge[0].lkey;
	पूर्ण अन्यथा अणु
		wqe->sqe.num_sge = 0;
	पूर्ण

	/* Retain original RREQ's message sequence number क्रम
	 * potential error reporting हालs.
	 */
	wqe->sqe.sge[1].length = irqe->sge[1].length;

	wqe->sqe.rkey = irqe->rkey;
	wqe->sqe.raddr = irqe->raddr;

	wqe->processed = 0;
	qp->irq_get++;

	/* mark current IRQ entry मुक्त */
	smp_store_mb(irqe->flags, 0);

	वापस 1;
पूर्ण

/*
 * Check अगर current CQ state qualअगरies क्रम calling CQ completion
 * handler. Must be called with CQ lock held.
 */
अटल bool siw_cq_notअगरy_now(काष्ठा siw_cq *cq, u32 flags)
अणु
	u32 cq_notअगरy;

	अगर (!cq->base_cq.comp_handler)
		वापस false;

	/* Read application shared notअगरication state */
	cq_notअगरy = READ_ONCE(cq->notअगरy->flags);

	अगर ((cq_notअगरy & SIW_NOTIFY_NEXT_COMPLETION) ||
	    ((cq_notअगरy & SIW_NOTIFY_SOLICITED) &&
	     (flags & SIW_WQE_SOLICITED))) अणु
		/*
		 * CQ notअगरication is one-shot: Since the
		 * current CQE causes user notअगरication,
		 * the CQ माला_लो dis-aremd and must be re-aremd
		 * by the user क्रम a new notअगरication.
		 */
		WRITE_ONCE(cq->notअगरy->flags, SIW_NOTIFY_NOT);

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक siw_sqe_complete(काष्ठा siw_qp *qp, काष्ठा siw_sqe *sqe, u32 bytes,
		     क्रमागत siw_wc_status status)
अणु
	काष्ठा siw_cq *cq = qp->scq;
	पूर्णांक rv = 0;

	अगर (cq) अणु
		u32 sqe_flags = sqe->flags;
		काष्ठा siw_cqe *cqe;
		u32 idx;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&cq->lock, flags);

		idx = cq->cq_put % cq->num_cqe;
		cqe = &cq->queue[idx];

		अगर (!READ_ONCE(cqe->flags)) अणु
			bool notअगरy;

			cqe->id = sqe->id;
			cqe->opcode = sqe->opcode;
			cqe->status = status;
			cqe->imm_data = 0;
			cqe->bytes = bytes;

			अगर (rdma_is_kernel_res(&cq->base_cq.res))
				cqe->base_qp = &qp->base_qp;
			अन्यथा
				cqe->qp_id = qp_id(qp);

			/* mark CQE valid क्रम application */
			WRITE_ONCE(cqe->flags, SIW_WQE_VALID);
			/* recycle SQE */
			smp_store_mb(sqe->flags, 0);

			cq->cq_put++;
			notअगरy = siw_cq_notअगरy_now(cq, sqe_flags);

			spin_unlock_irqrestore(&cq->lock, flags);

			अगर (notअगरy) अणु
				siw_dbg_cq(cq, "Call completion handler\n");
				cq->base_cq.comp_handler(&cq->base_cq,
						cq->base_cq.cq_context);
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&cq->lock, flags);
			rv = -ENOMEM;
			siw_cq_event(cq, IB_EVENT_CQ_ERR);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* recycle SQE */
		smp_store_mb(sqe->flags, 0);
	पूर्ण
	वापस rv;
पूर्ण

पूर्णांक siw_rqe_complete(काष्ठा siw_qp *qp, काष्ठा siw_rqe *rqe, u32 bytes,
		     u32 inval_stag, क्रमागत siw_wc_status status)
अणु
	काष्ठा siw_cq *cq = qp->rcq;
	पूर्णांक rv = 0;

	अगर (cq) अणु
		काष्ठा siw_cqe *cqe;
		u32 idx;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&cq->lock, flags);

		idx = cq->cq_put % cq->num_cqe;
		cqe = &cq->queue[idx];

		अगर (!READ_ONCE(cqe->flags)) अणु
			bool notअगरy;
			u8 cqe_flags = SIW_WQE_VALID;

			cqe->id = rqe->id;
			cqe->opcode = SIW_OP_RECEIVE;
			cqe->status = status;
			cqe->imm_data = 0;
			cqe->bytes = bytes;

			अगर (rdma_is_kernel_res(&cq->base_cq.res)) अणु
				cqe->base_qp = &qp->base_qp;
				अगर (inval_stag) अणु
					cqe_flags |= SIW_WQE_REM_INVAL;
					cqe->inval_stag = inval_stag;
				पूर्ण
			पूर्ण अन्यथा अणु
				cqe->qp_id = qp_id(qp);
			पूर्ण
			/* mark CQE valid क्रम application */
			WRITE_ONCE(cqe->flags, cqe_flags);
			/* recycle RQE */
			smp_store_mb(rqe->flags, 0);

			cq->cq_put++;
			notअगरy = siw_cq_notअगरy_now(cq, SIW_WQE_SIGNALLED);

			spin_unlock_irqrestore(&cq->lock, flags);

			अगर (notअगरy) अणु
				siw_dbg_cq(cq, "Call completion handler\n");
				cq->base_cq.comp_handler(&cq->base_cq,
						cq->base_cq.cq_context);
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&cq->lock, flags);
			rv = -ENOMEM;
			siw_cq_event(cq, IB_EVENT_CQ_ERR);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* recycle RQE */
		smp_store_mb(rqe->flags, 0);
	पूर्ण
	वापस rv;
पूर्ण

/*
 * siw_sq_flush()
 *
 * Flush SQ and ORRQ entries to CQ.
 *
 * Must be called with QP state ग_लिखो lock held.
 * Thereक्रमe, SQ and ORQ lock must not be taken.
 */
व्योम siw_sq_flush(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_sqe *sqe;
	काष्ठा siw_wqe *wqe = tx_wqe(qp);
	पूर्णांक async_event = 0;

	/*
	 * Start with completing any work currently on the ORQ
	 */
	जबतक (qp->attrs.orq_size) अणु
		sqe = &qp->orq[qp->orq_get % qp->attrs.orq_size];
		अगर (!READ_ONCE(sqe->flags))
			अवरोध;

		अगर (siw_sqe_complete(qp, sqe, 0, SIW_WC_WR_FLUSH_ERR) != 0)
			अवरोध;

		WRITE_ONCE(sqe->flags, 0);
		qp->orq_get++;
	पूर्ण
	/*
	 * Flush an in-progress WQE अगर present
	 */
	अगर (wqe->wr_status != SIW_WR_IDLE) अणु
		siw_dbg_qp(qp, "flush current SQE, type %d, status %d\n",
			   tx_type(wqe), wqe->wr_status);

		siw_wqe_put_mem(wqe, tx_type(wqe));

		अगर (tx_type(wqe) != SIW_OP_READ_RESPONSE &&
		    ((tx_type(wqe) != SIW_OP_READ &&
		      tx_type(wqe) != SIW_OP_READ_LOCAL_INV) ||
		     wqe->wr_status == SIW_WR_QUEUED))
			/*
			 * An in-progress Read Request is alपढ़ोy in
			 * the ORQ
			 */
			siw_sqe_complete(qp, &wqe->sqe, wqe->bytes,
					 SIW_WC_WR_FLUSH_ERR);

		wqe->wr_status = SIW_WR_IDLE;
	पूर्ण
	/*
	 * Flush the Send Queue
	 */
	जबतक (qp->attrs.sq_size) अणु
		sqe = &qp->sendq[qp->sq_get % qp->attrs.sq_size];
		अगर (!READ_ONCE(sqe->flags))
			अवरोध;

		async_event = 1;
		अगर (siw_sqe_complete(qp, sqe, 0, SIW_WC_WR_FLUSH_ERR) != 0)
			/*
			 * Shall IB_EVENT_SQ_DRAINED be supressed अगर work
			 * completion fails?
			 */
			अवरोध;

		WRITE_ONCE(sqe->flags, 0);
		qp->sq_get++;
	पूर्ण
	अगर (async_event)
		siw_qp_event(qp, IB_EVENT_SQ_DRAINED);
पूर्ण

/*
 * siw_rq_flush()
 *
 * Flush recv queue entries to CQ. Also
 * takes care of pending active tagged and untagged
 * inbound transfers, which have target memory
 * referenced.
 *
 * Must be called with QP state ग_लिखो lock held.
 * Thereक्रमe, RQ lock must not be taken.
 */
व्योम siw_rq_flush(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_wqe *wqe = &qp->rx_untagged.wqe_active;

	/*
	 * Flush an in-progress untagged operation अगर present
	 */
	अगर (wqe->wr_status != SIW_WR_IDLE) अणु
		siw_dbg_qp(qp, "flush current rqe, type %d, status %d\n",
			   rx_type(wqe), wqe->wr_status);

		siw_wqe_put_mem(wqe, rx_type(wqe));

		अगर (rx_type(wqe) == SIW_OP_RECEIVE) अणु
			siw_rqe_complete(qp, &wqe->rqe, wqe->bytes,
					 0, SIW_WC_WR_FLUSH_ERR);
		पूर्ण अन्यथा अगर (rx_type(wqe) != SIW_OP_READ &&
			   rx_type(wqe) != SIW_OP_READ_RESPONSE &&
			   rx_type(wqe) != SIW_OP_WRITE) अणु
			siw_sqe_complete(qp, &wqe->sqe, 0, SIW_WC_WR_FLUSH_ERR);
		पूर्ण
		wqe->wr_status = SIW_WR_IDLE;
	पूर्ण
	wqe = &qp->rx_tagged.wqe_active;

	अगर (wqe->wr_status != SIW_WR_IDLE) अणु
		siw_wqe_put_mem(wqe, rx_type(wqe));
		wqe->wr_status = SIW_WR_IDLE;
	पूर्ण
	/*
	 * Flush the Receive Queue
	 */
	जबतक (qp->attrs.rq_size) अणु
		काष्ठा siw_rqe *rqe =
			&qp->recvq[qp->rq_get % qp->attrs.rq_size];

		अगर (!READ_ONCE(rqe->flags))
			अवरोध;

		अगर (siw_rqe_complete(qp, rqe, 0, 0, SIW_WC_WR_FLUSH_ERR) != 0)
			अवरोध;

		WRITE_ONCE(rqe->flags, 0);
		qp->rq_get++;
	पूर्ण
पूर्ण

पूर्णांक siw_qp_add(काष्ठा siw_device *sdev, काष्ठा siw_qp *qp)
अणु
	पूर्णांक rv = xa_alloc(&sdev->qp_xa, &qp->base_qp.qp_num, qp, xa_limit_32b,
			  GFP_KERNEL);

	अगर (!rv) अणु
		kref_init(&qp->ref);
		qp->sdev = sdev;
		siw_dbg_qp(qp, "new QP\n");
	पूर्ण
	वापस rv;
पूर्ण

व्योम siw_मुक्त_qp(काष्ठा kref *ref)
अणु
	काष्ठा siw_qp *found, *qp = container_of(ref, काष्ठा siw_qp, ref);
	काष्ठा siw_device *sdev = qp->sdev;
	अचिन्हित दीर्घ flags;

	अगर (qp->cep)
		siw_cep_put(qp->cep);

	found = xa_erase(&sdev->qp_xa, qp_id(qp));
	WARN_ON(found != qp);
	spin_lock_irqsave(&sdev->lock, flags);
	list_del(&qp->devq);
	spin_unlock_irqrestore(&sdev->lock, flags);

	vमुक्त(qp->sendq);
	vमुक्त(qp->recvq);
	vमुक्त(qp->irq);
	vमुक्त(qp->orq);

	siw_put_tx_cpu(qp->tx_cpu);

	atomic_dec(&sdev->num_qp);
	siw_dbg_qp(qp, "free QP\n");
	kमुक्त_rcu(qp, rcu);
पूर्ण
