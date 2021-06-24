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

#समावेश "hfi.h"
#समावेश "verbs_txreq.h"
#समावेश "qp.h"

/* cut करोwn ridiculously दीर्घ IB macro names */
#घोषणा OP(x) UC_OP(x)

/**
 * hfi1_make_uc_req - स्थिरruct a request packet (SEND, RDMA ग_लिखो)
 * @qp: a poपूर्णांकer to the QP
 * @ps: the current packet state
 *
 * Assume s_lock is held.
 *
 * Return 1 अगर स्थिरructed; otherwise, वापस 0.
 */
पूर्णांक hfi1_make_uc_req(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा ib_other_headers *ohdr;
	काष्ठा rvt_swqe *wqe;
	u32 hwords;
	u32 bth0 = 0;
	u32 len;
	u32 pmtu = qp->pmtu;
	पूर्णांक middle = 0;

	ps->s_txreq = get_txreq(ps->dev, qp);
	अगर (!ps->s_txreq)
		जाओ bail_no_tx;

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
		rvt_send_complete(qp, wqe, IB_WC_WR_FLUSH_ERR);
		जाओ करोne_मुक्त_tx;
	पूर्ण

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

	/* Get the next send request. */
	wqe = rvt_get_swqe_ptr(qp, qp->s_cur);
	qp->s_wqe = शून्य;
	चयन (qp->s_state) अणु
	शेष:
		अगर (!(ib_rvt_state_ops[qp->state] &
		    RVT_PROCESS_NEXT_SEND_OK))
			जाओ bail;
		/* Check अगर send work queue is empty. */
		अगर (qp->s_cur == READ_ONCE(qp->s_head)) अणु
			clear_ahg(qp);
			जाओ bail;
		पूर्ण
		/*
		 * Local operations are processed immediately
		 * after all prior requests have completed.
		 */
		अगर (wqe->wr.opcode == IB_WR_REG_MR ||
		    wqe->wr.opcode == IB_WR_LOCAL_INV) अणु
			पूर्णांक local_ops = 0;
			पूर्णांक err = 0;

			अगर (qp->s_last != qp->s_cur)
				जाओ bail;
			अगर (++qp->s_cur == qp->s_size)
				qp->s_cur = 0;
			अगर (!(wqe->wr.send_flags & RVT_SEND_COMPLETION_ONLY)) अणु
				err = rvt_invalidate_rkey(
					qp, wqe->wr.ex.invalidate_rkey);
				local_ops = 1;
			पूर्ण
			rvt_send_complete(qp, wqe, err ? IB_WC_LOC_PROT_ERR
							: IB_WC_SUCCESS);
			अगर (local_ops)
				atomic_dec(&qp->local_ops_pending);
			जाओ करोne_मुक्त_tx;
		पूर्ण
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
			अगर (wqe->wr.opcode == IB_WR_SEND) अणु
				qp->s_state = OP(SEND_ONLY);
			पूर्ण अन्यथा अणु
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
			अगर (wqe->wr.opcode == IB_WR_RDMA_WRITE) अणु
				qp->s_state = OP(RDMA_WRITE_ONLY);
			पूर्ण अन्यथा अणु
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
			middle = HFI1_CAP_IS_KSET(SDMA_AHG);
			अवरोध;
		पूर्ण
		अगर (wqe->wr.opcode == IB_WR_SEND) अणु
			qp->s_state = OP(SEND_LAST);
		पूर्ण अन्यथा अणु
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
			middle = HFI1_CAP_IS_KSET(SDMA_AHG);
			अवरोध;
		पूर्ण
		अगर (wqe->wr.opcode == IB_WR_RDMA_WRITE) अणु
			qp->s_state = OP(RDMA_WRITE_LAST);
		पूर्ण अन्यथा अणु
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
	ps->s_txreq->hdr_dwords = hwords;
	ps->s_txreq->sde = priv->s_sde;
	ps->s_txreq->ss = &qp->s_sge;
	ps->s_txreq->s_cur_size = len;
	hfi1_make_ruc_header(qp, ohdr, bth0 | (qp->s_state << 24),
			     qp->remote_qpn, mask_psn(qp->s_psn++),
			     middle, ps);
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
	वापस 0;
पूर्ण

/**
 * hfi1_uc_rcv - handle an incoming UC packet
 * @packet: the packet काष्ठाure
 *
 * This is called from qp_rcv() to process an incoming UC packet
 * क्रम the given QP.
 * Called at पूर्णांकerrupt level.
 */
व्योम hfi1_uc_rcv(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ibport *ibp = rcd_to_iport(packet->rcd);
	व्योम *data = packet->payload;
	u32 tlen = packet->tlen;
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा ib_other_headers *ohdr = packet->ohdr;
	u32 opcode = packet->opcode;
	u32 hdrsize = packet->hlen;
	u32 psn;
	u32 pad = packet->pad;
	काष्ठा ib_wc wc;
	u32 pmtu = qp->pmtu;
	काष्ठा ib_reth *reth;
	पूर्णांक ret;
	u8 extra_bytes = pad + packet->extra_byte + (SIZE_OF_CRC << 2);

	अगर (hfi1_ruc_check_hdr(ibp, packet))
		वापस;

	process_ecn(qp, packet);

	psn = ib_bth_get_psn(ohdr);
	/* Compare the PSN verses the expected PSN. */
	अगर (unlikely(cmp_psn(psn, qp->r_psn) != 0)) अणु
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
		पूर्ण अन्यथा अणु
			rvt_put_ss(&qp->r_sge);
		पूर्ण
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
		अगर (test_and_clear_bit(RVT_R_REWIND_SGE, &qp->r_aflags)) अणु
			qp->r_sge = qp->s_rdma_पढ़ो_sge;
		पूर्ण अन्यथा अणु
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
		/*
		 * There will be no padding क्रम 9B packet but 16B packets
		 * will come in with some padding since we always add
		 * CRC and LT bytes which will need to be flit aligned
		 */
		अगर (unlikely(tlen != (hdrsize + pmtu + extra_bytes)))
			जाओ शुरुआत;
		qp->r_rcv_len += pmtu;
		अगर (unlikely(qp->r_rcv_len > qp->r_len))
			जाओ शुरुआत;
		rvt_copy_sge(qp, &qp->r_sge, data, pmtu, false, false);
		अवरोध;

	हाल OP(SEND_LAST_WITH_IMMEDIATE):
send_last_imm:
		wc.ex.imm_data = ohdr->u.imm_data;
		wc.wc_flags = IB_WC_WITH_IMM;
		जाओ send_last;
	हाल OP(SEND_LAST):
no_immediate_data:
		wc.ex.imm_data = 0;
		wc.wc_flags = 0;
send_last:
		/* Check क्रम invalid length. */
		/* LAST len should be >= 1 */
		अगर (unlikely(tlen < (hdrsize + extra_bytes)))
			जाओ शुरुआत;
		/* Don't count the CRC. */
		tlen -= (hdrsize + extra_bytes);
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

	हाल OP(RDMA_WRITE_FIRST):
	हाल OP(RDMA_WRITE_ONLY):
	हाल OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE): /* consume RWQE */
rdma_first:
		अगर (unlikely(!(qp->qp_access_flags &
			       IB_ACCESS_REMOTE_WRITE))) अणु
			जाओ drop;
		पूर्ण
		reth = &ohdr->u.rc.reth;
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
		अगर (opcode == OP(RDMA_WRITE_ONLY)) अणु
			जाओ rdma_last;
		पूर्ण अन्यथा अगर (opcode == OP(RDMA_WRITE_ONLY_WITH_IMMEDIATE)) अणु
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
		wc.wc_flags = IB_WC_WITH_IMM;

		/* Check क्रम invalid length. */
		/* LAST len should be >= 1 */
		अगर (unlikely(tlen < (hdrsize + pad + 4)))
			जाओ drop;
		/* Don't count the CRC. */
		tlen -= (hdrsize + extra_bytes);
		अगर (unlikely(tlen + qp->r_rcv_len != qp->r_len))
			जाओ drop;
		अगर (test_and_clear_bit(RVT_R_REWIND_SGE, &qp->r_aflags)) अणु
			rvt_put_ss(&qp->s_rdma_पढ़ो_sge);
		पूर्ण अन्यथा अणु
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
		/* Check क्रम invalid length. */
		/* LAST len should be >= 1 */
		अगर (unlikely(tlen < (hdrsize + pad + 4)))
			जाओ drop;
		/* Don't count the CRC. */
		tlen -= (hdrsize + extra_bytes);
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
पूर्ण
