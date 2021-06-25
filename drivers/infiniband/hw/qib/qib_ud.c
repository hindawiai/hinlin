<शैली गुरु>
/*
 * Copyright (c) 2012 - 2019 Intel Corporation.  All rights reserved.
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

#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_verbs.h>

#समावेश "qib.h"
#समावेश "qib_mad.h"

/**
 * qib_ud_loopback - handle send on loopback QPs
 * @sqp: the sending QP
 * @swqe: the send work request
 *
 * This is called from qib_make_ud_req() to क्रमward a WQE addressed
 * to the same HCA.
 * Note that the receive पूर्णांकerrupt handler may be calling qib_ud_rcv()
 * जबतक this is being called.
 */
अटल व्योम qib_ud_loopback(काष्ठा rvt_qp *sqp, काष्ठा rvt_swqe *swqe)
अणु
	काष्ठा qib_ibport *ibp = to_iport(sqp->ibqp.device, sqp->port_num);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा qib_devdata *dd = ppd->dd;
	काष्ठा rvt_dev_info *rdi = &dd->verbs_dev.rdi;
	काष्ठा rvt_qp *qp;
	काष्ठा rdma_ah_attr *ah_attr;
	अचिन्हित दीर्घ flags;
	काष्ठा rvt_sge_state ssge;
	काष्ठा rvt_sge *sge;
	काष्ठा ib_wc wc;
	u32 length;
	क्रमागत ib_qp_type sqptype, dqptype;

	rcu_पढ़ो_lock();
	qp = rvt_lookup_qpn(rdi, &ibp->rvp, rvt_get_swqe_remote_qpn(swqe));
	अगर (!qp) अणु
		ibp->rvp.n_pkt_drops++;
		जाओ drop;
	पूर्ण

	sqptype = sqp->ibqp.qp_type == IB_QPT_GSI ?
			IB_QPT_UD : sqp->ibqp.qp_type;
	dqptype = qp->ibqp.qp_type == IB_QPT_GSI ?
			IB_QPT_UD : qp->ibqp.qp_type;

	अगर (dqptype != sqptype ||
	    !(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK)) अणु
		ibp->rvp.n_pkt_drops++;
		जाओ drop;
	पूर्ण

	ah_attr = rvt_get_swqe_ah_attr(swqe);
	ppd = ppd_from_ibp(ibp);

	अगर (qp->ibqp.qp_num > 1) अणु
		u16 pkey1;
		u16 pkey2;
		u16 lid;

		pkey1 = qib_get_pkey(ibp, sqp->s_pkey_index);
		pkey2 = qib_get_pkey(ibp, qp->s_pkey_index);
		अगर (unlikely(!qib_pkey_ok(pkey1, pkey2))) अणु
			lid = ppd->lid | (rdma_ah_get_path_bits(ah_attr) &
					  ((1 << ppd->lmc) - 1));
			qib_bad_pkey(ibp, pkey1,
				     rdma_ah_get_sl(ah_attr),
				     sqp->ibqp.qp_num, qp->ibqp.qp_num,
				     cpu_to_be16(lid),
				     cpu_to_be16(rdma_ah_get_dlid(ah_attr)));
			जाओ drop;
		पूर्ण
	पूर्ण

	/*
	 * Check that the qkey matches (except क्रम QP0, see 9.6.1.4.1).
	 * Qkeys with the high order bit set mean use the
	 * qkey from the QP context instead of the WR (see 10.2.5).
	 */
	अगर (qp->ibqp.qp_num) अणु
		u32 qkey;

		qkey = (पूर्णांक)rvt_get_swqe_remote_qkey(swqe) < 0 ?
			sqp->qkey : rvt_get_swqe_remote_qkey(swqe);
		अगर (unlikely(qkey != qp->qkey))
			जाओ drop;
	पूर्ण

	/*
	 * A GRH is expected to precede the data even अगर not
	 * present on the wire.
	 */
	length = swqe->length;
	स_रखो(&wc, 0, माप(wc));
	wc.byte_len = length + माप(काष्ठा ib_grh);

	अगर (swqe->wr.opcode == IB_WR_SEND_WITH_IMM) अणु
		wc.wc_flags = IB_WC_WITH_IMM;
		wc.ex.imm_data = swqe->wr.ex.imm_data;
	पूर्ण

	spin_lock_irqsave(&qp->r_lock, flags);

	/*
	 * Get the next work request entry to find where to put the data.
	 */
	अगर (qp->r_flags & RVT_R_REUSE_SGE)
		qp->r_flags &= ~RVT_R_REUSE_SGE;
	अन्यथा अणु
		पूर्णांक ret;

		ret = rvt_get_rwqe(qp, false);
		अगर (ret < 0) अणु
			rvt_rc_error(qp, IB_WC_LOC_QP_OP_ERR);
			जाओ bail_unlock;
		पूर्ण
		अगर (!ret) अणु
			अगर (qp->ibqp.qp_num == 0)
				ibp->rvp.n_vl15_dropped++;
			जाओ bail_unlock;
		पूर्ण
	पूर्ण
	/* Silently drop packets which are too big. */
	अगर (unlikely(wc.byte_len > qp->r_len)) अणु
		qp->r_flags |= RVT_R_REUSE_SGE;
		ibp->rvp.n_pkt_drops++;
		जाओ bail_unlock;
	पूर्ण

	अगर (rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) अणु
		काष्ठा ib_grh grh;
		स्थिर काष्ठा ib_global_route *grd = rdma_ah_पढ़ो_grh(ah_attr);

		qib_make_grh(ibp, &grh, grd, 0, 0);
		rvt_copy_sge(qp, &qp->r_sge, &grh,
			     माप(grh), true, false);
		wc.wc_flags |= IB_WC_GRH;
	पूर्ण अन्यथा
		rvt_skip_sge(&qp->r_sge, माप(काष्ठा ib_grh), true);
	ssge.sg_list = swqe->sg_list + 1;
	ssge.sge = *swqe->sg_list;
	ssge.num_sge = swqe->wr.num_sge;
	sge = &ssge.sge;
	जबतक (length) अणु
		u32 len = rvt_get_sge_length(sge, length);

		rvt_copy_sge(qp, &qp->r_sge, sge->vaddr, len, true, false);
		sge->vaddr += len;
		sge->length -= len;
		sge->sge_length -= len;
		अगर (sge->sge_length == 0) अणु
			अगर (--ssge.num_sge)
				*sge = *ssge.sg_list++;
		पूर्ण अन्यथा अगर (sge->length == 0 && sge->mr->lkey) अणु
			अगर (++sge->n >= RVT_SEGSZ) अणु
				अगर (++sge->m >= sge->mr->mapsz)
					अवरोध;
				sge->n = 0;
			पूर्ण
			sge->vaddr =
				sge->mr->map[sge->m]->segs[sge->n].vaddr;
			sge->length =
				sge->mr->map[sge->m]->segs[sge->n].length;
		पूर्ण
		length -= len;
	पूर्ण
	rvt_put_ss(&qp->r_sge);
	अगर (!test_and_clear_bit(RVT_R_WRID_VALID, &qp->r_aflags))
		जाओ bail_unlock;
	wc.wr_id = qp->r_wr_id;
	wc.status = IB_WC_SUCCESS;
	wc.opcode = IB_WC_RECV;
	wc.qp = &qp->ibqp;
	wc.src_qp = sqp->ibqp.qp_num;
	wc.pkey_index = qp->ibqp.qp_type == IB_QPT_GSI ?
		rvt_get_swqe_pkey_index(swqe) : 0;
	wc.slid = ppd->lid | (rdma_ah_get_path_bits(ah_attr) &
				((1 << ppd->lmc) - 1));
	wc.sl = rdma_ah_get_sl(ah_attr);
	wc.dlid_path_bits = rdma_ah_get_dlid(ah_attr) & ((1 << ppd->lmc) - 1);
	wc.port_num = qp->port_num;
	/* Signal completion event अगर the solicited bit is set. */
	rvt_recv_cq(qp, &wc, swqe->wr.send_flags & IB_SEND_SOLICITED);
	ibp->rvp.n_loop_pkts++;
bail_unlock:
	spin_unlock_irqrestore(&qp->r_lock, flags);
drop:
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * qib_make_ud_req - स्थिरruct a UD request packet
 * @qp: the QP
 * @flags: flags to modअगरy and pass back to caller
 *
 * Assumes the s_lock is held.
 *
 * Return 1 अगर स्थिरructed; otherwise, वापस 0.
 */
पूर्णांक qib_make_ud_req(काष्ठा rvt_qp *qp, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;
	काष्ठा ib_other_headers *ohdr;
	काष्ठा rdma_ah_attr *ah_attr;
	काष्ठा qib_pportdata *ppd;
	काष्ठा qib_ibport *ibp;
	काष्ठा rvt_swqe *wqe;
	u32 nwords;
	u32 extra_bytes;
	u32 bth0;
	u16 lrh0;
	u16 lid;
	पूर्णांक ret = 0;
	पूर्णांक next_cur;

	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_NEXT_SEND_OK)) अणु
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

	/* see post_one_send() */
	अगर (qp->s_cur == READ_ONCE(qp->s_head))
		जाओ bail;

	wqe = rvt_get_swqe_ptr(qp, qp->s_cur);
	next_cur = qp->s_cur + 1;
	अगर (next_cur >= qp->s_size)
		next_cur = 0;

	/* Conकाष्ठा the header. */
	ibp = to_iport(qp->ibqp.device, qp->port_num);
	ppd = ppd_from_ibp(ibp);
	ah_attr = rvt_get_swqe_ah_attr(wqe);
	अगर (rdma_ah_get_dlid(ah_attr) >= be16_to_cpu(IB_MULTICAST_LID_BASE)) अणु
		अगर (rdma_ah_get_dlid(ah_attr) !=
				be16_to_cpu(IB_LID_PERMISSIVE))
			this_cpu_inc(ibp->pmastats->n_multicast_xmit);
		अन्यथा
			this_cpu_inc(ibp->pmastats->n_unicast_xmit);
	पूर्ण अन्यथा अणु
		this_cpu_inc(ibp->pmastats->n_unicast_xmit);
		lid = rdma_ah_get_dlid(ah_attr) & ~((1 << ppd->lmc) - 1);
		अगर (unlikely(lid == ppd->lid)) अणु
			अचिन्हित दीर्घ tflags = *flags;
			/*
			 * If DMAs are in progress, we can't generate
			 * a completion क्रम the loopback packet since
			 * it would be out of order.
			 * XXX Instead of रुकोing, we could queue a
			 * zero length descriptor so we get a callback.
			 */
			अगर (atomic_पढ़ो(&priv->s_dma_busy)) अणु
				qp->s_flags |= RVT_S_WAIT_DMA;
				जाओ bail;
			पूर्ण
			qp->s_cur = next_cur;
			spin_unlock_irqrestore(&qp->s_lock, tflags);
			qib_ud_loopback(qp, wqe);
			spin_lock_irqsave(&qp->s_lock, tflags);
			*flags = tflags;
			rvt_send_complete(qp, wqe, IB_WC_SUCCESS);
			जाओ करोne;
		पूर्ण
	पूर्ण

	qp->s_cur = next_cur;
	extra_bytes = -wqe->length & 3;
	nwords = (wqe->length + extra_bytes) >> 2;

	/* header size in 32-bit words LRH+BTH+DETH = (8+12+8)/4. */
	qp->s_hdrwords = 7;
	qp->s_cur_size = wqe->length;
	qp->s_cur_sge = &qp->s_sge;
	qp->s_srate = rdma_ah_get_अटल_rate(ah_attr);
	qp->s_wqe = wqe;
	qp->s_sge.sge = wqe->sg_list[0];
	qp->s_sge.sg_list = wqe->sg_list + 1;
	qp->s_sge.num_sge = wqe->wr.num_sge;
	qp->s_sge.total_len = wqe->length;

	अगर (rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) अणु
		/* Header size in 32-bit words. */
		qp->s_hdrwords += qib_make_grh(ibp, &priv->s_hdr->u.l.grh,
					       rdma_ah_पढ़ो_grh(ah_attr),
					       qp->s_hdrwords, nwords);
		lrh0 = QIB_LRH_GRH;
		ohdr = &priv->s_hdr->u.l.oth;
		/*
		 * Don't worry about sending to locally attached multicast
		 * QPs.  It is unspecअगरied by the spec. what happens.
		 */
	पूर्ण अन्यथा अणु
		/* Header size in 32-bit words. */
		lrh0 = QIB_LRH_BTH;
		ohdr = &priv->s_hdr->u.oth;
	पूर्ण
	अगर (wqe->wr.opcode == IB_WR_SEND_WITH_IMM) अणु
		qp->s_hdrwords++;
		ohdr->u.ud.imm_data = wqe->wr.ex.imm_data;
		bth0 = IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE << 24;
	पूर्ण अन्यथा
		bth0 = IB_OPCODE_UD_SEND_ONLY << 24;
	lrh0 |= rdma_ah_get_sl(ah_attr) << 4;
	अगर (qp->ibqp.qp_type == IB_QPT_SMI)
		lrh0 |= 0xF000; /* Set VL (see ch. 13.5.3.1) */
	अन्यथा
		lrh0 |= ibp->sl_to_vl[rdma_ah_get_sl(ah_attr)] << 12;
	priv->s_hdr->lrh[0] = cpu_to_be16(lrh0);
	priv->s_hdr->lrh[1] =
			cpu_to_be16(rdma_ah_get_dlid(ah_attr));  /* DEST LID */
	priv->s_hdr->lrh[2] =
			cpu_to_be16(qp->s_hdrwords + nwords + SIZE_OF_CRC);
	lid = ppd->lid;
	अगर (lid) अणु
		lid |= rdma_ah_get_path_bits(ah_attr) &
			((1 << ppd->lmc) - 1);
		priv->s_hdr->lrh[3] = cpu_to_be16(lid);
	पूर्ण अन्यथा
		priv->s_hdr->lrh[3] = IB_LID_PERMISSIVE;
	अगर (wqe->wr.send_flags & IB_SEND_SOLICITED)
		bth0 |= IB_BTH_SOLICITED;
	bth0 |= extra_bytes << 20;
	bth0 |= qp->ibqp.qp_type == IB_QPT_SMI ? QIB_DEFAULT_P_KEY :
		qib_get_pkey(ibp, qp->ibqp.qp_type == IB_QPT_GSI ?
			     rvt_get_swqe_pkey_index(wqe) : qp->s_pkey_index);
	ohdr->bth[0] = cpu_to_be32(bth0);
	/*
	 * Use the multicast QP अगर the destination LID is a multicast LID.
	 */
	ohdr->bth[1] = rdma_ah_get_dlid(ah_attr) >=
			be16_to_cpu(IB_MULTICAST_LID_BASE) &&
		rdma_ah_get_dlid(ah_attr) != be16_to_cpu(IB_LID_PERMISSIVE) ?
		cpu_to_be32(QIB_MULTICAST_QPN) :
		cpu_to_be32(rvt_get_swqe_remote_qpn(wqe));
	ohdr->bth[2] = cpu_to_be32(wqe->psn & QIB_PSN_MASK);
	/*
	 * Qkeys with the high order bit set mean use the
	 * qkey from the QP context instead of the WR (see 10.2.5).
	 */
	ohdr->u.ud.deth[0] =
		cpu_to_be32((पूर्णांक)rvt_get_swqe_remote_qkey(wqe) < 0 ? qp->qkey :
			    rvt_get_swqe_remote_qkey(wqe));
	ohdr->u.ud.deth[1] = cpu_to_be32(qp->ibqp.qp_num);

करोne:
	वापस 1;
bail:
	qp->s_flags &= ~RVT_S_BUSY;
	वापस ret;
पूर्ण

अटल अचिन्हित qib_lookup_pkey(काष्ठा qib_ibport *ibp, u16 pkey)
अणु
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा qib_devdata *dd = ppd->dd;
	अचिन्हित ctxt = ppd->hw_pidx;
	अचिन्हित i;

	pkey &= 0x7fff;	/* हटाओ limited/full membership bit */

	क्रम (i = 0; i < ARRAY_SIZE(dd->rcd[ctxt]->pkeys); ++i)
		अगर ((dd->rcd[ctxt]->pkeys[i] & 0x7fff) == pkey)
			वापस i;

	/*
	 * Should not get here, this means hardware failed to validate pkeys.
	 * Punt and वापस index 0.
	 */
	वापस 0;
पूर्ण

/**
 * qib_ud_rcv - receive an incoming UD packet
 * @ibp: the port the packet came in on
 * @hdr: the packet header
 * @has_grh: true अगर the packet has a GRH
 * @data: the packet data
 * @tlen: the packet length
 * @qp: the QP the packet came on
 *
 * This is called from qib_qp_rcv() to process an incoming UD packet
 * क्रम the given QP.
 * Called at पूर्णांकerrupt level.
 */
व्योम qib_ud_rcv(काष्ठा qib_ibport *ibp, काष्ठा ib_header *hdr,
		पूर्णांक has_grh, व्योम *data, u32 tlen, काष्ठा rvt_qp *qp)
अणु
	काष्ठा ib_other_headers *ohdr;
	पूर्णांक opcode;
	u32 hdrsize;
	u32 pad;
	काष्ठा ib_wc wc;
	u32 qkey;
	u32 src_qp;
	u16 dlid;

	/* Check क्रम GRH */
	अगर (!has_grh) अणु
		ohdr = &hdr->u.oth;
		hdrsize = 8 + 12 + 8;   /* LRH + BTH + DETH */
	पूर्ण अन्यथा अणु
		ohdr = &hdr->u.l.oth;
		hdrsize = 8 + 40 + 12 + 8; /* LRH + GRH + BTH + DETH */
	पूर्ण
	qkey = be32_to_cpu(ohdr->u.ud.deth[0]);
	src_qp = be32_to_cpu(ohdr->u.ud.deth[1]) & RVT_QPN_MASK;

	/*
	 * Get the number of bytes the message was padded by
	 * and drop incomplete packets.
	 */
	pad = (be32_to_cpu(ohdr->bth[0]) >> 20) & 3;
	अगर (unlikely(tlen < (hdrsize + pad + 4)))
		जाओ drop;

	tlen -= hdrsize + pad + 4;

	/*
	 * Check that the permissive LID is only used on QP0
	 * and the QKEY matches (see 9.6.1.4.1 and 9.6.1.5.1).
	 */
	अगर (qp->ibqp.qp_num) अणु
		अगर (unlikely(hdr->lrh[1] == IB_LID_PERMISSIVE ||
			     hdr->lrh[3] == IB_LID_PERMISSIVE))
			जाओ drop;
		अगर (qp->ibqp.qp_num > 1) अणु
			u16 pkey1, pkey2;

			pkey1 = be32_to_cpu(ohdr->bth[0]);
			pkey2 = qib_get_pkey(ibp, qp->s_pkey_index);
			अगर (unlikely(!qib_pkey_ok(pkey1, pkey2))) अणु
				qib_bad_pkey(ibp,
					     pkey1,
					     (be16_to_cpu(hdr->lrh[0]) >> 4) &
						0xF,
					     src_qp, qp->ibqp.qp_num,
					     hdr->lrh[3], hdr->lrh[1]);
				वापस;
			पूर्ण
		पूर्ण
		अगर (unlikely(qkey != qp->qkey))
			वापस;

		/* Drop invalid MAD packets (see 13.5.3.1). */
		अगर (unlikely(qp->ibqp.qp_num == 1 &&
			     (tlen != 256 ||
			      (be16_to_cpu(hdr->lrh[0]) >> 12) == 15)))
			जाओ drop;
	पूर्ण अन्यथा अणु
		काष्ठा ib_smp *smp;

		/* Drop invalid MAD packets (see 13.5.3.1). */
		अगर (tlen != 256 || (be16_to_cpu(hdr->lrh[0]) >> 12) != 15)
			जाओ drop;
		smp = (काष्ठा ib_smp *) data;
		अगर ((hdr->lrh[1] == IB_LID_PERMISSIVE ||
		     hdr->lrh[3] == IB_LID_PERMISSIVE) &&
		    smp->mgmt_class != IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
			जाओ drop;
	पूर्ण

	/*
	 * The opcode is in the low byte when its in network order
	 * (top byte when in host order).
	 */
	opcode = be32_to_cpu(ohdr->bth[0]) >> 24;
	अगर (qp->ibqp.qp_num > 1 &&
	    opcode == IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE) अणु
		wc.ex.imm_data = ohdr->u.ud.imm_data;
		wc.wc_flags = IB_WC_WITH_IMM;
	पूर्ण अन्यथा अगर (opcode == IB_OPCODE_UD_SEND_ONLY) अणु
		wc.ex.imm_data = 0;
		wc.wc_flags = 0;
	पूर्ण अन्यथा
		जाओ drop;

	/*
	 * A GRH is expected to precede the data even अगर not
	 * present on the wire.
	 */
	wc.byte_len = tlen + माप(काष्ठा ib_grh);

	/*
	 * Get the next work request entry to find where to put the data.
	 */
	अगर (qp->r_flags & RVT_R_REUSE_SGE)
		qp->r_flags &= ~RVT_R_REUSE_SGE;
	अन्यथा अणु
		पूर्णांक ret;

		ret = rvt_get_rwqe(qp, false);
		अगर (ret < 0) अणु
			rvt_rc_error(qp, IB_WC_LOC_QP_OP_ERR);
			वापस;
		पूर्ण
		अगर (!ret) अणु
			अगर (qp->ibqp.qp_num == 0)
				ibp->rvp.n_vl15_dropped++;
			वापस;
		पूर्ण
	पूर्ण
	/* Silently drop packets which are too big. */
	अगर (unlikely(wc.byte_len > qp->r_len)) अणु
		qp->r_flags |= RVT_R_REUSE_SGE;
		जाओ drop;
	पूर्ण
	अगर (has_grh) अणु
		rvt_copy_sge(qp, &qp->r_sge, &hdr->u.l.grh,
			     माप(काष्ठा ib_grh), true, false);
		wc.wc_flags |= IB_WC_GRH;
	पूर्ण अन्यथा
		rvt_skip_sge(&qp->r_sge, माप(काष्ठा ib_grh), true);
	rvt_copy_sge(qp, &qp->r_sge, data, wc.byte_len - माप(काष्ठा ib_grh),
		     true, false);
	rvt_put_ss(&qp->r_sge);
	अगर (!test_and_clear_bit(RVT_R_WRID_VALID, &qp->r_aflags))
		वापस;
	wc.wr_id = qp->r_wr_id;
	wc.status = IB_WC_SUCCESS;
	wc.opcode = IB_WC_RECV;
	wc.venकरोr_err = 0;
	wc.qp = &qp->ibqp;
	wc.src_qp = src_qp;
	wc.pkey_index = qp->ibqp.qp_type == IB_QPT_GSI ?
		qib_lookup_pkey(ibp, be32_to_cpu(ohdr->bth[0])) : 0;
	wc.slid = be16_to_cpu(hdr->lrh[3]);
	wc.sl = (be16_to_cpu(hdr->lrh[0]) >> 4) & 0xF;
	dlid = be16_to_cpu(hdr->lrh[1]);
	/*
	 * Save the LMC lower bits अगर the destination LID is a unicast LID.
	 */
	wc.dlid_path_bits = dlid >= be16_to_cpu(IB_MULTICAST_LID_BASE) ? 0 :
		dlid & ((1 << ppd_from_ibp(ibp)->lmc) - 1);
	wc.port_num = qp->port_num;
	/* Signal completion event अगर the solicited bit is set. */
	rvt_recv_cq(qp, &wc, ib_bth_is_solicited(ohdr));
	वापस;

drop:
	ibp->rvp.n_pkt_drops++;
पूर्ण
