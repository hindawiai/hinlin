<शैली गुरु>
/*
 * Copyright (c) 2006, 2007, 2008, 2009, 2010 QLogic Corporation.
 * All rights reserved.
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

#समावेश "qib.h"

/* cut करोwn ridiculously दीर्घ IB macro names */
#घोषणा OP(x) IB_OPCODE_UC_##x

/**
 * qib_make_uc_req - स्थिरruct a request packet (SEND, RDMA ग_लिखो)
 * @qp: a poपूर्णांकer to the QP
 * @flags: unused
 *
 * Assumes the s_lock is held.
 *
 * Return 1 अगर स्थिरructed; otherwise, वापस 0.
 */
पूर्णांक qib_make_uc_req(काष्ठा rvt_qp *qp, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;
	काष्ठा ib_other_headers *ohdr;
	काष्ठा rvt_swqe *wqe;
	u32 hwords;
	u32 bth0;
	u32 len;
	u32 pmtu = qp->pmtu;
	पूर्णांक ret = 0;

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
		rvt_send_complete(qp, wqe, IB_WC_WR_FLUSH_ERR);
		जाओ करोne;
	पूर्ण

	ohdr = &priv->s_hdr->u.oth;
	अगर (rdma_ah_get_ah_flags(&qp->remote_ah_attr) & IB_AH_GRH)
		ohdr = &priv->s_hdr->u.l.oth;

	/* header size in 32-bit words LRH+BTH = (8+12)/4. */
	hwords = 5;
	bth0 = 0;

	/* Get the next send request. */
	wqe = rvt_get_swqe_ptr(qp, qp->s_cur);
	qp->s_wqe = शून्य;
	चयन (qp->s_state) अणु
	शेष:
		अगर (!(ib_rvt_state_ops[qp->state] &
		    RVT_PROCESS_NEXT_SEND_OK))
			जाओ bail;
		/* Check अगर send work queue is empty. */
		अगर (qp->s_cur == READ_ONCE(qp->s_head))
			जाओ bail;
		/*
		 * Start a new request.
		 */
		qp->s_psn = wqe->psn;
		qp->s_sge.sge = wqe->sg_list[0];
		qp->s_sge.sg_list = wqe->sg_list + 1;
		qp->s_sge.num_sge = wqe->wr.num_sge;
		qp->s_sge.total_len = wqe->length;
		len = wqe->length;
		qp->s_len = len;
		चयन (wqe->wr.opcode) अणु
		हाल IB_WR_SEND:
		हाल IB_WR_SEND_WITH_IMM:
			अगर (len > pmtu) अणु
				qp->s_state = OP(SEND_FIRST);
				len = pmtu;
				अवरोध;
			पूर्ण
			अगर (wqe->wr.opcode == IB_WR_SEND)
				qp->s_state = OP(SEND_ONLY);
			अन्यथा अणु
				qp->s_state =
					OP(SEND_ONLY_WITH_IMMEDIATE);
				/* Immediate data comes after the BTH */
				ohdr->u.imm_data = wqe->wr.ex.imm_data;
				hwords += 1;
			पूर्ण
			अगर (wqe->wr.send_flags & IB_SEND_SOLICITED)
				bth0 |= IB_BTH_SOLICITED;
			qp->s_wqe = wqe;
			अगर (++qp->s_cur >= qp->s_size)
				qp->s_cur = 0;
			अवरोध;

		हाल IB_WR_RDMA_WRITE:
		हाल IB_WR_RDMA_WRITE_WITH_IMM:
			ohdr->u.rc.reth.vaddr =
				cpu_to_be64(wqe->rdma_wr.remote_addr);
			ohdr->u.rc.reth.rkey =
				cpu_to_be32(wqe->rdma_wr.rkey);
			ohdr->u.rc.reth.length = cpu_to_be32(len);
			hwords += माप(काष्ठा ib_reth) / 4;
			अगर (len > pmtu) अणु
				qp->s_state = OP(RDMA_WRITE_FIRST);
				len = pmtu;
				अवरोध;
			पूर्ण
			अगर (wqe->wr.opcode == IB_WR_RDMA_WRITE)
				qp->s_state = OP(RDMA_WRITE_ONLY);
			अन्यथा अणु
				qp->s_state =
					OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE);
				/* Immediate data comes after the RETH */
				ohdr->u.rc.imm_data = wqe->wr.ex.imm_data;
				hwords += 1;
				अगर (wqe->wr.send_flags & IB_SEND_SOLICITED)
					bth0 |= IB_BTH_SOLICITED;
			पूर्ण
			qp->s_wqe = wqe;
			अगर (++qp->s_cur >= qp->s_size)
				qp->s_cur = 0;
			अवरोध;

		शेष:
			जाओ bail;
		पूर्ण
		अवरोध;

	हाल OP(SEND_FIRST):
		qp->s_state = OP(SEND_MIDDLE);
		fallthrough;
	हाल OP(SEND_MIDDLE):
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
		qp->s_wqe = wqe;
		अगर (++qp->s_cur >= qp->s_size)
			qp->s_cur = 0;
		अवरोध;

	हाल OP(RDMA_WRITE_FIRST):
		qp->s_state = OP(RDMA_WRITE_MIDDLE);
		fallthrough;
	हाल OP(RDMA_WRITE_MIDDLE):
		len = qp->s_len;
		अगर (len > pmtu) अणु
			len = pmtu;
			अवरोध;
		पूर्ण
		अगर (wqe->wr.opcode == IB_WR_RDMA_WRITE)
			qp->s_state = OP(RDMA_WRITE_LAST);
		अन्यथा अणु
			qp->s_state =
				OP(RDMA_WRITE_LAST_WITH_IMMEDIATE);
			/* Immediate data comes after the BTH */
			ohdr->u.imm_data = wqe->wr.ex.imm_data;
			hwords += 1;
			अगर (wqe->wr.send_flags & IB_SEND_SOLICITED)
				bth0 |= IB_BTH_SOLICITED;
		पूर्ण
		qp->s_wqe = wqe;
		अगर (++qp->s_cur >= qp->s_size)
			qp->s_cur = 0;
		अवरोध;
	पूर्ण
	qp->s_len -= len;
	qp->s_hdrwords = hwords;
	qp->s_cur_sge = &qp->s_sge;
	qp->s_cur_size = len;
	qib_make_ruc_header(qp, ohdr, bth0 | (qp->s_state << 24),
			    qp->s_psn++ & QIB_PSN_MASK);
करोne:
	वापस 1;
bail:
	qp->s_flags &= ~RVT_S_BUSY;
	वापस ret;
पूर्ण

/**
 * qib_uc_rcv - handle an incoming UC packet
 * @ibp: the port the packet came in on
 * @hdr: the header of the packet
 * @has_grh: true अगर the packet has a GRH
 * @data: the packet data
 * @tlen: the length of the packet
 * @qp: the QP क्रम this packet.
 *
 * This is called from qib_qp_rcv() to process an incoming UC packet
 * क्रम the given QP.
 * Called at पूर्णांकerrupt level.
 */
व्योम qib_uc_rcv(काष्ठा qib_ibport *ibp, काष्ठा ib_header *hdr,
		पूर्णांक has_grh, व्योम *data, u32 tlen, काष्ठा rvt_qp *qp)
अणु
	काष्ठा ib_other_headers *ohdr;
	u32 opcode;
	u32 hdrsize;
	u32 psn;
	u32 pad;
	काष्ठा ib_wc wc;
	u32 pmtu = qp->pmtu;
	काष्ठा ib_reth *reth;
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

	/* Compare the PSN verses the expected PSN. */
	अगर (unlikely(qib_cmp24(psn, qp->r_psn) != 0)) अणु
		/*
		 * Handle a sequence error.
		 * Silently drop any current message.
		 */
		qp->r_psn = psn;
inv:
		अगर (qp->r_state == OP(SEND_FIRST) ||
		    qp->r_state == OP(SEND_MIDDLE)) अणु
			set_bit(RVT_R_REWIND_SGE, &qp->r_aflags);
			qp->r_sge.num_sge = 0;
		पूर्ण अन्यथा
			rvt_put_ss(&qp->r_sge);
		qp->r_state = OP(SEND_LAST);
		चयन (opcode) अणु
		हाल OP(SEND_FIRST):
		हाल OP(SEND_ONLY):
		हाल OP(SEND_ONLY_WITH_IMMEDIATE):
			जाओ send_first;

		हाल OP(RDMA_WRITE_FIRST):
		हाल OP(RDMA_WRITE_ONLY):
		हाल OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE):
			जाओ rdma_first;

		शेष:
			जाओ drop;
		पूर्ण
	पूर्ण

	/* Check क्रम opcode sequence errors. */
	चयन (qp->r_state) अणु
	हाल OP(SEND_FIRST):
	हाल OP(SEND_MIDDLE):
		अगर (opcode == OP(SEND_MIDDLE) ||
		    opcode == OP(SEND_LAST) ||
		    opcode == OP(SEND_LAST_WITH_IMMEDIATE))
			अवरोध;
		जाओ inv;

	हाल OP(RDMA_WRITE_FIRST):
	हाल OP(RDMA_WRITE_MIDDLE):
		अगर (opcode == OP(RDMA_WRITE_MIDDLE) ||
		    opcode == OP(RDMA_WRITE_LAST) ||
		    opcode == OP(RDMA_WRITE_LAST_WITH_IMMEDIATE))
			अवरोध;
		जाओ inv;

	शेष:
		अगर (opcode == OP(SEND_FIRST) ||
		    opcode == OP(SEND_ONLY) ||
		    opcode == OP(SEND_ONLY_WITH_IMMEDIATE) ||
		    opcode == OP(RDMA_WRITE_FIRST) ||
		    opcode == OP(RDMA_WRITE_ONLY) ||
		    opcode == OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE))
			अवरोध;
		जाओ inv;
	पूर्ण

	अगर (qp->state == IB_QPS_RTR && !(qp->r_flags & RVT_R_COMM_EST))
		rvt_comm_est(qp);

	/* OK, process the packet. */
	चयन (opcode) अणु
	हाल OP(SEND_FIRST):
	हाल OP(SEND_ONLY):
	हाल OP(SEND_ONLY_WITH_IMMEDIATE):
send_first:
		अगर (test_and_clear_bit(RVT_R_REWIND_SGE, &qp->r_aflags))
			qp->r_sge = qp->s_rdma_पढ़ो_sge;
		अन्यथा अणु
			ret = rvt_get_rwqe(qp, false);
			अगर (ret < 0)
				जाओ op_err;
			अगर (!ret)
				जाओ drop;
			/*
			 * qp->s_rdma_पढ़ो_sge will be the owner
			 * of the mr references.
			 */
			qp->s_rdma_पढ़ो_sge = qp->r_sge;
		पूर्ण
		qp->r_rcv_len = 0;
		अगर (opcode == OP(SEND_ONLY))
			जाओ no_immediate_data;
		अन्यथा अगर (opcode == OP(SEND_ONLY_WITH_IMMEDIATE))
			जाओ send_last_imm;
		fallthrough;
	हाल OP(SEND_MIDDLE):
		/* Check क्रम invalid length PMTU or posted rwqe len. */
		अगर (unlikely(tlen != (hdrsize + pmtu + 4)))
			जाओ शुरुआत;
		qp->r_rcv_len += pmtu;
		अगर (unlikely(qp->r_rcv_len > qp->r_len))
			जाओ शुरुआत;
		rvt_copy_sge(qp, &qp->r_sge, data, pmtu, false, false);
		अवरोध;

	हाल OP(SEND_LAST_WITH_IMMEDIATE):
send_last_imm:
		wc.ex.imm_data = ohdr->u.imm_data;
		hdrsize += 4;
		wc.wc_flags = IB_WC_WITH_IMM;
		जाओ send_last;
	हाल OP(SEND_LAST):
no_immediate_data:
		wc.ex.imm_data = 0;
		wc.wc_flags = 0;
send_last:
		/* Get the number of bytes the message was padded by. */
		pad = (be32_to_cpu(ohdr->bth[0]) >> 20) & 3;
		/* Check क्रम invalid length. */
		/* XXX LAST len should be >= 1 */
		अगर (unlikely(tlen < (hdrsize + pad + 4)))
			जाओ शुरुआत;
		/* Don't count the CRC. */
		tlen -= (hdrsize + pad + 4);
		wc.byte_len = tlen + qp->r_rcv_len;
		अगर (unlikely(wc.byte_len > qp->r_len))
			जाओ शुरुआत;
		wc.opcode = IB_WC_RECV;
		rvt_copy_sge(qp, &qp->r_sge, data, tlen, false, false);
		rvt_put_ss(&qp->s_rdma_पढ़ो_sge);
last_imm:
		wc.wr_id = qp->r_wr_id;
		wc.status = IB_WC_SUCCESS;
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
	हाल OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE): /* consume RWQE */
rdma_first:
		अगर (unlikely(!(qp->qp_access_flags &
			       IB_ACCESS_REMOTE_WRITE))) अणु
			जाओ drop;
		पूर्ण
		reth = &ohdr->u.rc.reth;
		hdrsize += माप(*reth);
		qp->r_len = be32_to_cpu(reth->length);
		qp->r_rcv_len = 0;
		qp->r_sge.sg_list = शून्य;
		अगर (qp->r_len != 0) अणु
			u32 rkey = be32_to_cpu(reth->rkey);
			u64 vaddr = be64_to_cpu(reth->vaddr);
			पूर्णांक ok;

			/* Check rkey */
			ok = rvt_rkey_ok(qp, &qp->r_sge.sge, qp->r_len,
					 vaddr, rkey, IB_ACCESS_REMOTE_WRITE);
			अगर (unlikely(!ok))
				जाओ drop;
			qp->r_sge.num_sge = 1;
		पूर्ण अन्यथा अणु
			qp->r_sge.num_sge = 0;
			qp->r_sge.sge.mr = शून्य;
			qp->r_sge.sge.vaddr = शून्य;
			qp->r_sge.sge.length = 0;
			qp->r_sge.sge.sge_length = 0;
		पूर्ण
		अगर (opcode == OP(RDMA_WRITE_ONLY))
			जाओ rdma_last;
		अन्यथा अगर (opcode == OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE)) अणु
			wc.ex.imm_data = ohdr->u.rc.imm_data;
			जाओ rdma_last_imm;
		पूर्ण
		fallthrough;
	हाल OP(RDMA_WRITE_MIDDLE):
		/* Check क्रम invalid length PMTU or posted rwqe len. */
		अगर (unlikely(tlen != (hdrsize + pmtu + 4)))
			जाओ drop;
		qp->r_rcv_len += pmtu;
		अगर (unlikely(qp->r_rcv_len > qp->r_len))
			जाओ drop;
		rvt_copy_sge(qp, &qp->r_sge, data, pmtu, true, false);
		अवरोध;

	हाल OP(RDMA_WRITE_LAST_WITH_IMMEDIATE):
		wc.ex.imm_data = ohdr->u.imm_data;
rdma_last_imm:
		hdrsize += 4;
		wc.wc_flags = IB_WC_WITH_IMM;

		/* Get the number of bytes the message was padded by. */
		pad = (be32_to_cpu(ohdr->bth[0]) >> 20) & 3;
		/* Check क्रम invalid length. */
		/* XXX LAST len should be >= 1 */
		अगर (unlikely(tlen < (hdrsize + pad + 4)))
			जाओ drop;
		/* Don't count the CRC. */
		tlen -= (hdrsize + pad + 4);
		अगर (unlikely(tlen + qp->r_rcv_len != qp->r_len))
			जाओ drop;
		अगर (test_and_clear_bit(RVT_R_REWIND_SGE, &qp->r_aflags))
			rvt_put_ss(&qp->s_rdma_पढ़ो_sge);
		अन्यथा अणु
			ret = rvt_get_rwqe(qp, true);
			अगर (ret < 0)
				जाओ op_err;
			अगर (!ret)
				जाओ drop;
		पूर्ण
		wc.byte_len = qp->r_len;
		wc.opcode = IB_WC_RECV_RDMA_WITH_IMM;
		rvt_copy_sge(qp, &qp->r_sge, data, tlen, true, false);
		rvt_put_ss(&qp->r_sge);
		जाओ last_imm;

	हाल OP(RDMA_WRITE_LAST):
rdma_last:
		/* Get the number of bytes the message was padded by. */
		pad = (be32_to_cpu(ohdr->bth[0]) >> 20) & 3;
		/* Check क्रम invalid length. */
		/* XXX LAST len should be >= 1 */
		अगर (unlikely(tlen < (hdrsize + pad + 4)))
			जाओ drop;
		/* Don't count the CRC. */
		tlen -= (hdrsize + pad + 4);
		अगर (unlikely(tlen + qp->r_rcv_len != qp->r_len))
			जाओ drop;
		rvt_copy_sge(qp, &qp->r_sge, data, tlen, true, false);
		rvt_put_ss(&qp->r_sge);
		अवरोध;

	शेष:
		/* Drop packet क्रम unknown opcodes. */
		जाओ drop;
	पूर्ण
	qp->r_psn++;
	qp->r_state = opcode;
	वापस;

शुरुआत:
	set_bit(RVT_R_REWIND_SGE, &qp->r_aflags);
	qp->r_sge.num_sge = 0;
drop:
	ibp->rvp.n_pkt_drops++;
	वापस;

op_err:
	rvt_rc_error(qp, IB_WC_LOC_QP_OP_ERR);
	वापस;

पूर्ण
