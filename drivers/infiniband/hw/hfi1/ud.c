<शैली गुरु>
/*
 * Copyright(c) 2015 - 2019 Intel Corporation.
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

#समावेश <linux/net.h>
#समावेश <rdma/ib_smi.h>

#समावेश "hfi.h"
#समावेश "mad.h"
#समावेश "verbs_txreq.h"
#समावेश "trace_ibhdrs.h"
#समावेश "qp.h"

/* We support only two types - 9B and 16B क्रम now */
अटल स्थिर hfi1_make_req hfi1_make_ud_req_tbl[2] = अणु
	[HFI1_PKT_TYPE_9B] = &hfi1_make_ud_req_9B,
	[HFI1_PKT_TYPE_16B] = &hfi1_make_ud_req_16B
पूर्ण;

/**
 * ud_loopback - handle send on loopback QPs
 * @sqp: the sending QP
 * @swqe: the send work request
 *
 * This is called from hfi1_make_ud_req() to क्रमward a WQE addressed
 * to the same HFI.
 * Note that the receive पूर्णांकerrupt handler may be calling hfi1_ud_rcv()
 * जबतक this is being called.
 */
अटल व्योम ud_loopback(काष्ठा rvt_qp *sqp, काष्ठा rvt_swqe *swqe)
अणु
	काष्ठा hfi1_ibport *ibp = to_iport(sqp->ibqp.device, sqp->port_num);
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_qp_priv *priv = sqp->priv;
	काष्ठा rvt_qp *qp;
	काष्ठा rdma_ah_attr *ah_attr;
	अचिन्हित दीर्घ flags;
	काष्ठा rvt_sge_state ssge;
	काष्ठा rvt_sge *sge;
	काष्ठा ib_wc wc;
	u32 length;
	क्रमागत ib_qp_type sqptype, dqptype;

	rcu_पढ़ो_lock();

	qp = rvt_lookup_qpn(ib_to_rvt(sqp->ibqp.device), &ibp->rvp,
			    rvt_get_swqe_remote_qpn(swqe));
	अगर (!qp) अणु
		ibp->rvp.n_pkt_drops++;
		rcu_पढ़ो_unlock();
		वापस;
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
		u16 pkey;
		u32 slid;
		u8 sc5 = ibp->sl_to_sc[rdma_ah_get_sl(ah_attr)];

		pkey = hfi1_get_pkey(ibp, sqp->s_pkey_index);
		slid = ppd->lid | (rdma_ah_get_path_bits(ah_attr) &
				   ((1 << ppd->lmc) - 1));
		अगर (unlikely(ingress_pkey_check(ppd, pkey, sc5,
						qp->s_pkey_index,
						slid, false))) अणु
			hfi1_bad_pkey(ibp, pkey,
				      rdma_ah_get_sl(ah_attr),
				      sqp->ibqp.qp_num, qp->ibqp.qp_num,
				      slid, rdma_ah_get_dlid(ah_attr));
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
			जाओ drop; /* silently drop per IBTA spec */
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
	अगर (qp->r_flags & RVT_R_REUSE_SGE) अणु
		qp->r_flags &= ~RVT_R_REUSE_SGE;
	पूर्ण अन्यथा अणु
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
		काष्ठा ib_global_route grd = *(rdma_ah_पढ़ो_grh(ah_attr));

		/*
		 * For loopback packets with extended LIDs, the
		 * sgid_index in the GRH is 0 and the dgid is
		 * OPA GID of the sender. While creating a response
		 * to the loopback packet, IB core creates the new
		 * sgid_index from the DGID and that will be the
		 * OPA_GID_INDEX. The new dgid is from the sgid
		 * index and that will be in the IB GID क्रमmat.
		 *
		 * We now have a हाल where the sent packet had a
		 * dअगरferent sgid_index and dgid compared to the
		 * one that was received in response.
		 *
		 * Fix this inconsistency.
		 */
		अगर (priv->hdr_type == HFI1_PKT_TYPE_16B) अणु
			अगर (grd.sgid_index == 0)
				grd.sgid_index = OPA_GID_INDEX;

			अगर (ib_is_opa_gid(&grd.dgid))
				grd.dgid.global.पूर्णांकerface_id =
				cpu_to_be64(ppd->guids[HFI1_PORT_GUID_INDEX]);
		पूर्ण

		hfi1_make_grh(ibp, &grh, &grd, 0, 0);
		rvt_copy_sge(qp, &qp->r_sge, &grh,
			     माप(grh), true, false);
		wc.wc_flags |= IB_WC_GRH;
	पूर्ण अन्यथा अणु
		rvt_skip_sge(&qp->r_sge, माप(काष्ठा ib_grh), true);
	पूर्ण
	ssge.sg_list = swqe->sg_list + 1;
	ssge.sge = *swqe->sg_list;
	ssge.num_sge = swqe->wr.num_sge;
	sge = &ssge.sge;
	जबतक (length) अणु
		u32 len = rvt_get_sge_length(sge, length);

		WARN_ON_ONCE(len == 0);
		rvt_copy_sge(qp, &qp->r_sge, sge->vaddr, len, true, false);
		rvt_update_sge(&ssge, len, false);
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
	अगर (qp->ibqp.qp_type == IB_QPT_GSI || qp->ibqp.qp_type == IB_QPT_SMI) अणु
		अगर (sqp->ibqp.qp_type == IB_QPT_GSI ||
		    sqp->ibqp.qp_type == IB_QPT_SMI)
			wc.pkey_index = rvt_get_swqe_pkey_index(swqe);
		अन्यथा
			wc.pkey_index = sqp->s_pkey_index;
	पूर्ण अन्यथा अणु
		wc.pkey_index = 0;
	पूर्ण
	wc.slid = (ppd->lid | (rdma_ah_get_path_bits(ah_attr) &
				   ((1 << ppd->lmc) - 1))) & U16_MAX;
	/* Check क्रम loopback when the port lid is not set */
	अगर (wc.slid == 0 && sqp->ibqp.qp_type == IB_QPT_GSI)
		wc.slid = be16_to_cpu(IB_LID_PERMISSIVE);
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

अटल व्योम hfi1_make_bth_deth(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
			       काष्ठा ib_other_headers *ohdr,
			       u16 *pkey, u32 extra_bytes, bool bypass)
अणु
	u32 bth0;
	काष्ठा hfi1_ibport *ibp;

	ibp = to_iport(qp->ibqp.device, qp->port_num);
	अगर (wqe->wr.opcode == IB_WR_SEND_WITH_IMM) अणु
		ohdr->u.ud.imm_data = wqe->wr.ex.imm_data;
		bth0 = IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE << 24;
	पूर्ण अन्यथा अणु
		bth0 = IB_OPCODE_UD_SEND_ONLY << 24;
	पूर्ण

	अगर (wqe->wr.send_flags & IB_SEND_SOLICITED)
		bth0 |= IB_BTH_SOLICITED;
	bth0 |= extra_bytes << 20;
	अगर (qp->ibqp.qp_type == IB_QPT_GSI || qp->ibqp.qp_type == IB_QPT_SMI)
		*pkey = hfi1_get_pkey(ibp, rvt_get_swqe_pkey_index(wqe));
	अन्यथा
		*pkey = hfi1_get_pkey(ibp, qp->s_pkey_index);
	अगर (!bypass)
		bth0 |= *pkey;
	ohdr->bth[0] = cpu_to_be32(bth0);
	ohdr->bth[1] = cpu_to_be32(rvt_get_swqe_remote_qpn(wqe));
	ohdr->bth[2] = cpu_to_be32(mask_psn(wqe->psn));
	/*
	 * Qkeys with the high order bit set mean use the
	 * qkey from the QP context instead of the WR (see 10.2.5).
	 */
	ohdr->u.ud.deth[0] =
		cpu_to_be32((पूर्णांक)rvt_get_swqe_remote_qkey(wqe) < 0 ? qp->qkey :
			    rvt_get_swqe_remote_qkey(wqe));
	ohdr->u.ud.deth[1] = cpu_to_be32(qp->ibqp.qp_num);
पूर्ण

व्योम hfi1_make_ud_req_9B(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps,
			 काष्ठा rvt_swqe *wqe)
अणु
	u32 nwords, extra_bytes;
	u16 len, slid, dlid, pkey;
	u16 lrh0 = 0;
	u8 sc5;
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा ib_other_headers *ohdr;
	काष्ठा rdma_ah_attr *ah_attr;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_ibport *ibp;
	काष्ठा ib_grh *grh;

	ibp = to_iport(qp->ibqp.device, qp->port_num);
	ppd = ppd_from_ibp(ibp);
	ah_attr = rvt_get_swqe_ah_attr(wqe);

	extra_bytes = -wqe->length & 3;
	nwords = ((wqe->length + extra_bytes) >> 2) + SIZE_OF_CRC;
	/* header size in dwords LRH+BTH+DETH = (8+12+8)/4. */
	ps->s_txreq->hdr_dwords = 7;
	अगर (wqe->wr.opcode == IB_WR_SEND_WITH_IMM)
		ps->s_txreq->hdr_dwords++;

	अगर (rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) अणु
		grh = &ps->s_txreq->phdr.hdr.ibh.u.l.grh;
		ps->s_txreq->hdr_dwords +=
			hfi1_make_grh(ibp, grh, rdma_ah_पढ़ो_grh(ah_attr),
				      ps->s_txreq->hdr_dwords - LRH_9B_DWORDS,
				      nwords);
		lrh0 = HFI1_LRH_GRH;
		ohdr = &ps->s_txreq->phdr.hdr.ibh.u.l.oth;
	पूर्ण अन्यथा अणु
		lrh0 = HFI1_LRH_BTH;
		ohdr = &ps->s_txreq->phdr.hdr.ibh.u.oth;
	पूर्ण

	sc5 = ibp->sl_to_sc[rdma_ah_get_sl(ah_attr)];
	lrh0 |= (rdma_ah_get_sl(ah_attr) & 0xf) << 4;
	अगर (qp->ibqp.qp_type == IB_QPT_SMI) अणु
		lrh0 |= 0xF000; /* Set VL (see ch. 13.5.3.1) */
		priv->s_sc = 0xf;
	पूर्ण अन्यथा अणु
		lrh0 |= (sc5 & 0xf) << 12;
		priv->s_sc = sc5;
	पूर्ण

	dlid = opa_get_lid(rdma_ah_get_dlid(ah_attr), 9B);
	अगर (dlid == be16_to_cpu(IB_LID_PERMISSIVE)) अणु
		slid = be16_to_cpu(IB_LID_PERMISSIVE);
	पूर्ण अन्यथा अणु
		u16 lid = (u16)ppd->lid;

		अगर (lid) अणु
			lid |= rdma_ah_get_path_bits(ah_attr) &
				((1 << ppd->lmc) - 1);
			slid = lid;
		पूर्ण अन्यथा अणु
			slid = be16_to_cpu(IB_LID_PERMISSIVE);
		पूर्ण
	पूर्ण
	hfi1_make_bth_deth(qp, wqe, ohdr, &pkey, extra_bytes, false);
	len = ps->s_txreq->hdr_dwords + nwords;

	/* Setup the packet */
	ps->s_txreq->phdr.hdr.hdr_type = HFI1_PKT_TYPE_9B;
	hfi1_make_ib_hdr(&ps->s_txreq->phdr.hdr.ibh,
			 lrh0, len, dlid, slid);
पूर्ण

व्योम hfi1_make_ud_req_16B(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps,
			  काष्ठा rvt_swqe *wqe)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा ib_other_headers *ohdr;
	काष्ठा rdma_ah_attr *ah_attr;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_ibport *ibp;
	u32 dlid, slid, nwords, extra_bytes;
	u32 dest_qp = rvt_get_swqe_remote_qpn(wqe);
	u32 src_qp = qp->ibqp.qp_num;
	u16 len, pkey;
	u8 l4, sc5;
	bool is_mgmt = false;

	ibp = to_iport(qp->ibqp.device, qp->port_num);
	ppd = ppd_from_ibp(ibp);
	ah_attr = rvt_get_swqe_ah_attr(wqe);

	/*
	 * Build 16B Management Packet अगर either the destination
	 * or source queue pair number is 0 or 1.
	 */
	अगर (dest_qp == 0 || src_qp == 0 || dest_qp == 1 || src_qp == 1) अणु
		/* header size in dwords 16B LRH+L4_FM = (16+8)/4. */
		ps->s_txreq->hdr_dwords = 6;
		is_mgmt = true;
	पूर्ण अन्यथा अणु
		/* header size in dwords 16B LRH+BTH+DETH = (16+12+8)/4. */
		ps->s_txreq->hdr_dwords = 9;
		अगर (wqe->wr.opcode == IB_WR_SEND_WITH_IMM)
			ps->s_txreq->hdr_dwords++;
	पूर्ण

	/* SW provides space क्रम CRC and LT क्रम bypass packets. */
	extra_bytes = hfi1_get_16b_padding((ps->s_txreq->hdr_dwords << 2),
					   wqe->length);
	nwords = ((wqe->length + extra_bytes + SIZE_OF_LT) >> 2) + SIZE_OF_CRC;

	अगर ((rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) &&
	    hfi1_check_mcast(rdma_ah_get_dlid(ah_attr))) अणु
		काष्ठा ib_grh *grh;
		काष्ठा ib_global_route *grd = rdma_ah_retrieve_grh(ah_attr);
		/*
		 * Ensure OPA GIDs are transक्रमmed to IB gids
		 * beक्रमe creating the GRH.
		 */
		अगर (grd->sgid_index == OPA_GID_INDEX) अणु
			dd_dev_warn(ppd->dd, "Bad sgid_index. sgid_index: %d\n",
				    grd->sgid_index);
			grd->sgid_index = 0;
		पूर्ण
		grh = &ps->s_txreq->phdr.hdr.opah.u.l.grh;
		ps->s_txreq->hdr_dwords += hfi1_make_grh(
			ibp, grh, grd,
			ps->s_txreq->hdr_dwords - LRH_16B_DWORDS,
			nwords);
		ohdr = &ps->s_txreq->phdr.hdr.opah.u.l.oth;
		l4 = OPA_16B_L4_IB_GLOBAL;
	पूर्ण अन्यथा अणु
		ohdr = &ps->s_txreq->phdr.hdr.opah.u.oth;
		l4 = OPA_16B_L4_IB_LOCAL;
	पूर्ण

	sc5 = ibp->sl_to_sc[rdma_ah_get_sl(ah_attr)];
	अगर (qp->ibqp.qp_type == IB_QPT_SMI)
		priv->s_sc = 0xf;
	अन्यथा
		priv->s_sc = sc5;

	dlid = opa_get_lid(rdma_ah_get_dlid(ah_attr), 16B);
	अगर (!ppd->lid)
		slid = be32_to_cpu(OPA_LID_PERMISSIVE);
	अन्यथा
		slid = ppd->lid | (rdma_ah_get_path_bits(ah_attr) &
			   ((1 << ppd->lmc) - 1));

	अगर (is_mgmt) अणु
		l4 = OPA_16B_L4_FM;
		pkey = hfi1_get_pkey(ibp, rvt_get_swqe_pkey_index(wqe));
		hfi1_16B_set_qpn(&ps->s_txreq->phdr.hdr.opah.u.mgmt,
				 dest_qp, src_qp);
	पूर्ण अन्यथा अणु
		hfi1_make_bth_deth(qp, wqe, ohdr, &pkey, extra_bytes, true);
	पूर्ण
	/* Convert dwords to flits */
	len = (ps->s_txreq->hdr_dwords + nwords) >> 1;

	/* Setup the packet */
	ps->s_txreq->phdr.hdr.hdr_type = HFI1_PKT_TYPE_16B;
	hfi1_make_16b_hdr(&ps->s_txreq->phdr.hdr.opah,
			  slid, dlid, len, pkey, 0, 0, l4, priv->s_sc);
पूर्ण

/**
 * hfi1_make_ud_req - स्थिरruct a UD request packet
 * @qp: the QP
 * @ps: the current packet state
 *
 * Assume s_lock is held.
 *
 * Return 1 अगर स्थिरructed; otherwise, वापस 0.
 */
पूर्णांक hfi1_make_ud_req(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा rdma_ah_attr *ah_attr;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_ibport *ibp;
	काष्ठा rvt_swqe *wqe;
	पूर्णांक next_cur;
	u32 lid;

	ps->s_txreq = get_txreq(ps->dev, qp);
	अगर (!ps->s_txreq)
		जाओ bail_no_tx;

	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_NEXT_SEND_OK)) अणु
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
		wqe = rvt_get_swqe_ptr(qp, qp->s_last);
		rvt_send_complete(qp, wqe, IB_WC_WR_FLUSH_ERR);
		जाओ करोne_मुक्त_tx;
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
	priv->hdr_type = hfi1_get_hdr_type(ppd->lid, ah_attr);
	अगर ((!hfi1_check_mcast(rdma_ah_get_dlid(ah_attr))) ||
	    (rdma_ah_get_dlid(ah_attr) == be32_to_cpu(OPA_LID_PERMISSIVE))) अणु
		lid = rdma_ah_get_dlid(ah_attr) & ~((1 << ppd->lmc) - 1);
		अगर (unlikely(!loopback &&
			     ((lid == ppd->lid) ||
			      ((lid == be32_to_cpu(OPA_LID_PERMISSIVE)) &&
			       (qp->ibqp.qp_type == IB_QPT_GSI))))) अणु
			अचिन्हित दीर्घ tflags = ps->flags;
			/*
			 * If DMAs are in progress, we can't generate
			 * a completion क्रम the loopback packet since
			 * it would be out of order.
			 * Instead of रुकोing, we could queue a
			 * zero length descriptor so we get a callback.
			 */
			अगर (ioरुको_sdma_pending(&priv->s_ioरुको)) अणु
				qp->s_flags |= RVT_S_WAIT_DMA;
				जाओ bail;
			पूर्ण
			qp->s_cur = next_cur;
			spin_unlock_irqrestore(&qp->s_lock, tflags);
			ud_loopback(qp, wqe);
			spin_lock_irqsave(&qp->s_lock, tflags);
			ps->flags = tflags;
			rvt_send_complete(qp, wqe, IB_WC_SUCCESS);
			जाओ करोne_मुक्त_tx;
		पूर्ण
	पूर्ण

	qp->s_cur = next_cur;
	ps->s_txreq->s_cur_size = wqe->length;
	ps->s_txreq->ss = &qp->s_sge;
	qp->s_srate = rdma_ah_get_अटल_rate(ah_attr);
	qp->srate_mbps = ib_rate_to_mbps(qp->s_srate);
	qp->s_wqe = wqe;
	qp->s_sge.sge = wqe->sg_list[0];
	qp->s_sge.sg_list = wqe->sg_list + 1;
	qp->s_sge.num_sge = wqe->wr.num_sge;
	qp->s_sge.total_len = wqe->length;

	/* Make the appropriate header */
	hfi1_make_ud_req_tbl[priv->hdr_type](qp, ps, qp->s_wqe);
	priv->s_sde = qp_to_sdma_engine(qp, priv->s_sc);
	ps->s_txreq->sde = priv->s_sde;
	priv->s_sendcontext = qp_to_send_context(qp, priv->s_sc);
	ps->s_txreq->psc = priv->s_sendcontext;
	/* disarm any ahg */
	priv->s_ahg->ahgcount = 0;
	priv->s_ahg->ahgidx = 0;
	priv->s_ahg->tx_flags = 0;

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

/*
 * Hardware can't check this so we करो it here.
 *
 * This is a slightly dअगरferent algorithm than the standard pkey check.  It
 * special हालs the management keys and allows क्रम 0x7fff and 0xffff to be in
 * the table at the same समय.
 *
 * @वापसs the index found or -1 अगर not found
 */
पूर्णांक hfi1_lookup_pkey_idx(काष्ठा hfi1_ibport *ibp, u16 pkey)
अणु
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	अचिन्हित i;

	अगर (pkey == FULL_MGMT_P_KEY || pkey == LIM_MGMT_P_KEY) अणु
		अचिन्हित lim_idx = -1;

		क्रम (i = 0; i < ARRAY_SIZE(ppd->pkeys); ++i) अणु
			/* here we look क्रम an exact match */
			अगर (ppd->pkeys[i] == pkey)
				वापस i;
			अगर (ppd->pkeys[i] == LIM_MGMT_P_KEY)
				lim_idx = i;
		पूर्ण

		/* did not find 0xffff वापस 0x7fff idx अगर found */
		अगर (pkey == FULL_MGMT_P_KEY)
			वापस lim_idx;

		/* no match...  */
		वापस -1;
	पूर्ण

	pkey &= 0x7fff; /* हटाओ limited/full membership bit */

	क्रम (i = 0; i < ARRAY_SIZE(ppd->pkeys); ++i)
		अगर ((ppd->pkeys[i] & 0x7fff) == pkey)
			वापस i;

	/*
	 * Should not get here, this means hardware failed to validate pkeys.
	 */
	वापस -1;
पूर्ण

व्योम वापस_cnp_16B(काष्ठा hfi1_ibport *ibp, काष्ठा rvt_qp *qp,
		    u32 remote_qpn, u16 pkey, u32 slid, u32 dlid,
		    u8 sc5, स्थिर काष्ठा ib_grh *old_grh)
अणु
	u64 pbc, pbc_flags = 0;
	u32 bth0, plen, vl, hwords = 7;
	u16 len;
	u8 l4;
	काष्ठा hfi1_opa_header hdr;
	काष्ठा ib_other_headers *ohdr;
	काष्ठा pio_buf *pbuf;
	काष्ठा send_context *ctxt = qp_to_send_context(qp, sc5);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u32 nwords;

	hdr.hdr_type = HFI1_PKT_TYPE_16B;
	/* Populate length */
	nwords = ((hfi1_get_16b_padding(hwords << 2, 0) +
		   SIZE_OF_LT) >> 2) + SIZE_OF_CRC;
	अगर (old_grh) अणु
		काष्ठा ib_grh *grh = &hdr.opah.u.l.grh;

		grh->version_tclass_flow = old_grh->version_tclass_flow;
		grh->paylen = cpu_to_be16(
			(hwords - LRH_16B_DWORDS + nwords) << 2);
		grh->hop_limit = 0xff;
		grh->sgid = old_grh->dgid;
		grh->dgid = old_grh->sgid;
		ohdr = &hdr.opah.u.l.oth;
		l4 = OPA_16B_L4_IB_GLOBAL;
		hwords += माप(काष्ठा ib_grh) / माप(u32);
	पूर्ण अन्यथा अणु
		ohdr = &hdr.opah.u.oth;
		l4 = OPA_16B_L4_IB_LOCAL;
	पूर्ण

	/* BIT 16 to 19 is TVER. Bit 20 to 22 is pad cnt */
	bth0 = (IB_OPCODE_CNP << 24) | (1 << 16) |
	       (hfi1_get_16b_padding(hwords << 2, 0) << 20);
	ohdr->bth[0] = cpu_to_be32(bth0);

	ohdr->bth[1] = cpu_to_be32(remote_qpn);
	ohdr->bth[2] = 0; /* PSN 0 */

	/* Convert dwords to flits */
	len = (hwords + nwords) >> 1;
	hfi1_make_16b_hdr(&hdr.opah, slid, dlid, len, pkey, 1, 0, l4, sc5);

	plen = 2 /* PBC */ + hwords + nwords;
	pbc_flags |= PBC_PACKET_BYPASS | PBC_INSERT_BYPASS_ICRC;
	vl = sc_to_vlt(ppd->dd, sc5);
	pbc = create_pbc(ppd, pbc_flags, qp->srate_mbps, vl, plen);
	अगर (ctxt) अणु
		pbuf = sc_buffer_alloc(ctxt, plen, शून्य, शून्य);
		अगर (!IS_ERR_OR_शून्य(pbuf)) अणु
			trace_pio_output_ibhdr(ppd->dd, &hdr, sc5);
			ppd->dd->pio_अंतरभूत_send(ppd->dd, pbuf, pbc,
						 &hdr, hwords);
		पूर्ण
	पूर्ण
पूर्ण

व्योम वापस_cnp(काष्ठा hfi1_ibport *ibp, काष्ठा rvt_qp *qp, u32 remote_qpn,
		u16 pkey, u32 slid, u32 dlid, u8 sc5,
		स्थिर काष्ठा ib_grh *old_grh)
अणु
	u64 pbc, pbc_flags = 0;
	u32 bth0, plen, vl, hwords = 5;
	u16 lrh0;
	u8 sl = ibp->sc_to_sl[sc5];
	काष्ठा hfi1_opa_header hdr;
	काष्ठा ib_other_headers *ohdr;
	काष्ठा pio_buf *pbuf;
	काष्ठा send_context *ctxt = qp_to_send_context(qp, sc5);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	hdr.hdr_type = HFI1_PKT_TYPE_9B;
	अगर (old_grh) अणु
		काष्ठा ib_grh *grh = &hdr.ibh.u.l.grh;

		grh->version_tclass_flow = old_grh->version_tclass_flow;
		grh->paylen = cpu_to_be16(
			(hwords - LRH_9B_DWORDS + SIZE_OF_CRC) << 2);
		grh->hop_limit = 0xff;
		grh->sgid = old_grh->dgid;
		grh->dgid = old_grh->sgid;
		ohdr = &hdr.ibh.u.l.oth;
		lrh0 = HFI1_LRH_GRH;
		hwords += माप(काष्ठा ib_grh) / माप(u32);
	पूर्ण अन्यथा अणु
		ohdr = &hdr.ibh.u.oth;
		lrh0 = HFI1_LRH_BTH;
	पूर्ण

	lrh0 |= (sc5 & 0xf) << 12 | sl << 4;

	bth0 = pkey | (IB_OPCODE_CNP << 24);
	ohdr->bth[0] = cpu_to_be32(bth0);

	ohdr->bth[1] = cpu_to_be32(remote_qpn | (1 << IB_BECN_SHIFT));
	ohdr->bth[2] = 0; /* PSN 0 */

	hfi1_make_ib_hdr(&hdr.ibh, lrh0, hwords + SIZE_OF_CRC, dlid, slid);
	plen = 2 /* PBC */ + hwords;
	pbc_flags |= (ib_is_sc5(sc5) << PBC_DC_INFO_SHIFT);
	vl = sc_to_vlt(ppd->dd, sc5);
	pbc = create_pbc(ppd, pbc_flags, qp->srate_mbps, vl, plen);
	अगर (ctxt) अणु
		pbuf = sc_buffer_alloc(ctxt, plen, शून्य, शून्य);
		अगर (!IS_ERR_OR_शून्य(pbuf)) अणु
			trace_pio_output_ibhdr(ppd->dd, &hdr, sc5);
			ppd->dd->pio_अंतरभूत_send(ppd->dd, pbuf, pbc,
						 &hdr, hwords);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * opa_smp_check() - Do the regular pkey checking, and the additional
 * checks क्रम SMPs specअगरied in OPAv1 rev 1.0, 9/19/2016 update, section
 * 9.10.25 ("SMA Packet Checks").
 *
 * Note that:
 *   - Checks are करोne using the pkey directly from the packet's BTH,
 *     and specअगरically _not_ the pkey that we attach to the completion,
 *     which may be dअगरferent.
 *   - These checks are specअगरically क्रम "non-local" SMPs (i.e., SMPs
 *     which originated on another node). SMPs which are sent from, and
 *     destined to this node are checked in opa_local_smp_check().
 *
 * At the poपूर्णांक where opa_smp_check() is called, we know:
 *   - destination QP is QP0
 *
 * opa_smp_check() वापसs 0 अगर all checks succeed, 1 otherwise.
 */
अटल पूर्णांक opa_smp_check(काष्ठा hfi1_ibport *ibp, u16 pkey, u8 sc5,
			 काष्ठा rvt_qp *qp, u16 slid, काष्ठा opa_smp *smp)
अणु
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	/*
	 * I करोn't think it's possible क्रम us to get here with sc != 0xf,
	 * but check it to be certain.
	 */
	अगर (sc5 != 0xf)
		वापस 1;

	अगर (rcv_pkey_check(ppd, pkey, sc5, slid))
		वापस 1;

	/*
	 * At this poपूर्णांक we know (and so करोn't need to check again) that
	 * the pkey is either LIM_MGMT_P_KEY, or FULL_MGMT_P_KEY
	 * (see ingress_pkey_check).
	 */
	अगर (smp->mgmt_class != IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE &&
	    smp->mgmt_class != IB_MGMT_CLASS_SUBN_LID_ROUTED) अणु
		ingress_pkey_table_fail(ppd, pkey, slid);
		वापस 1;
	पूर्ण

	/*
	 * SMPs fall पूर्णांकo one of four (disjoपूर्णांक) categories:
	 * SMA request, SMA response, SMA trap, or SMA trap repress.
	 * Our response depends, in part, on which type of SMP we're
	 * processing.
	 *
	 * If this is an SMA response, skip the check here.
	 *
	 * If this is an SMA request or SMA trap repress:
	 *   - pkey != FULL_MGMT_P_KEY =>
	 *       increment port recv स्थिरraपूर्णांक errors, drop MAD
	 *
	 * Otherwise:
	 *    - accept अगर the port is running an SM
	 *    - drop MAD अगर it's an SMA trap
	 *    - pkey == FULL_MGMT_P_KEY =>
	 *        reply with unsupported method
	 *    - pkey != FULL_MGMT_P_KEY =>
	 *	  increment port recv स्थिरraपूर्णांक errors, drop MAD
	 */
	चयन (smp->method) अणु
	हाल IB_MGMT_METHOD_GET_RESP:
	हाल IB_MGMT_METHOD_REPORT_RESP:
		अवरोध;
	हाल IB_MGMT_METHOD_GET:
	हाल IB_MGMT_METHOD_SET:
	हाल IB_MGMT_METHOD_REPORT:
	हाल IB_MGMT_METHOD_TRAP_REPRESS:
		अगर (pkey != FULL_MGMT_P_KEY) अणु
			ingress_pkey_table_fail(ppd, pkey, slid);
			वापस 1;
		पूर्ण
		अवरोध;
	शेष:
		अगर (ibp->rvp.port_cap_flags & IB_PORT_SM)
			वापस 0;
		अगर (smp->method == IB_MGMT_METHOD_TRAP)
			वापस 1;
		अगर (pkey == FULL_MGMT_P_KEY) अणु
			smp->status |= IB_SMP_UNSUP_METHOD;
			वापस 0;
		पूर्ण
		ingress_pkey_table_fail(ppd, pkey, slid);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * hfi1_ud_rcv - receive an incoming UD packet
 * @packet: the packet काष्ठाure
 *
 * This is called from qp_rcv() to process an incoming UD packet
 * क्रम the given QP.
 * Called at पूर्णांकerrupt level.
 */
व्योम hfi1_ud_rcv(काष्ठा hfi1_packet *packet)
अणु
	u32 hdrsize = packet->hlen;
	काष्ठा ib_wc wc;
	u32 src_qp;
	u16 pkey;
	पूर्णांक mgmt_pkey_idx = -1;
	काष्ठा hfi1_ibport *ibp = rcd_to_iport(packet->rcd);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	व्योम *data = packet->payload;
	u32 tlen = packet->tlen;
	काष्ठा rvt_qp *qp = packet->qp;
	u8 sc5 = packet->sc;
	u8 sl_from_sc;
	u8 opcode = packet->opcode;
	u8 sl = packet->sl;
	u32 dlid = packet->dlid;
	u32 slid = packet->slid;
	u8 extra_bytes;
	u8 l4 = 0;
	bool dlid_is_permissive;
	bool slid_is_permissive;
	bool solicited = false;

	extra_bytes = packet->pad + packet->extra_byte + (SIZE_OF_CRC << 2);

	अगर (packet->etype == RHF_RCV_TYPE_BYPASS) अणु
		u32 permissive_lid =
			opa_get_lid(be32_to_cpu(OPA_LID_PERMISSIVE), 16B);

		l4 = hfi1_16B_get_l4(packet->hdr);
		pkey = hfi1_16B_get_pkey(packet->hdr);
		dlid_is_permissive = (dlid == permissive_lid);
		slid_is_permissive = (slid == permissive_lid);
	पूर्ण अन्यथा अणु
		pkey = ib_bth_get_pkey(packet->ohdr);
		dlid_is_permissive = (dlid == be16_to_cpu(IB_LID_PERMISSIVE));
		slid_is_permissive = (slid == be16_to_cpu(IB_LID_PERMISSIVE));
	पूर्ण
	sl_from_sc = ibp->sc_to_sl[sc5];

	अगर (likely(l4 != OPA_16B_L4_FM)) अणु
		src_qp = ib_get_sqpn(packet->ohdr);
		solicited = ib_bth_is_solicited(packet->ohdr);
	पूर्ण अन्यथा अणु
		src_qp = hfi1_16B_get_src_qpn(packet->mgmt);
	पूर्ण

	process_ecn(qp, packet);
	/*
	 * Get the number of bytes the message was padded by
	 * and drop incomplete packets.
	 */
	अगर (unlikely(tlen < (hdrsize + extra_bytes)))
		जाओ drop;

	tlen -= hdrsize + extra_bytes;

	/*
	 * Check that the permissive LID is only used on QP0
	 * and the QKEY matches (see 9.6.1.4.1 and 9.6.1.5.1).
	 */
	अगर (qp->ibqp.qp_num) अणु
		अगर (unlikely(dlid_is_permissive || slid_is_permissive))
			जाओ drop;
		अगर (qp->ibqp.qp_num > 1) अणु
			अगर (unlikely(rcv_pkey_check(ppd, pkey, sc5, slid))) अणु
				/*
				 * Traps will not be sent क्रम packets dropped
				 * by the HW. This is fine, as sending trap
				 * क्रम invalid pkeys is optional according to
				 * IB spec (release 1.3, section 10.9.4)
				 */
				hfi1_bad_pkey(ibp,
					      pkey, sl,
					      src_qp, qp->ibqp.qp_num,
					      slid, dlid);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* GSI packet */
			mgmt_pkey_idx = hfi1_lookup_pkey_idx(ibp, pkey);
			अगर (mgmt_pkey_idx < 0)
				जाओ drop;
		पूर्ण
		अगर (unlikely(l4 != OPA_16B_L4_FM &&
			     ib_get_qkey(packet->ohdr) != qp->qkey))
			वापस; /* Silent drop */

		/* Drop invalid MAD packets (see 13.5.3.1). */
		अगर (unlikely(qp->ibqp.qp_num == 1 &&
			     (tlen > 2048 || (sc5 == 0xF))))
			जाओ drop;
	पूर्ण अन्यथा अणु
		/* Received on QP0, and so by definition, this is an SMP */
		काष्ठा opa_smp *smp = (काष्ठा opa_smp *)data;

		अगर (opa_smp_check(ibp, pkey, sc5, qp, slid, smp))
			जाओ drop;

		अगर (tlen > 2048)
			जाओ drop;
		अगर ((dlid_is_permissive || slid_is_permissive) &&
		    smp->mgmt_class != IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
			जाओ drop;

		/* look up SMI pkey */
		mgmt_pkey_idx = hfi1_lookup_pkey_idx(ibp, pkey);
		अगर (mgmt_pkey_idx < 0)
			जाओ drop;
	पूर्ण

	अगर (qp->ibqp.qp_num > 1 &&
	    opcode == IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE) अणु
		wc.ex.imm_data = packet->ohdr->u.ud.imm_data;
		wc.wc_flags = IB_WC_WITH_IMM;
	पूर्ण अन्यथा अगर (opcode == IB_OPCODE_UD_SEND_ONLY) अणु
		wc.ex.imm_data = 0;
		wc.wc_flags = 0;
	पूर्ण अन्यथा अणु
		जाओ drop;
	पूर्ण

	/*
	 * A GRH is expected to precede the data even अगर not
	 * present on the wire.
	 */
	wc.byte_len = tlen + माप(काष्ठा ib_grh);

	/*
	 * Get the next work request entry to find where to put the data.
	 */
	अगर (qp->r_flags & RVT_R_REUSE_SGE) अणु
		qp->r_flags &= ~RVT_R_REUSE_SGE;
	पूर्ण अन्यथा अणु
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
	अगर (packet->grh) अणु
		rvt_copy_sge(qp, &qp->r_sge, packet->grh,
			     माप(काष्ठा ib_grh), true, false);
		wc.wc_flags |= IB_WC_GRH;
	पूर्ण अन्यथा अगर (packet->etype == RHF_RCV_TYPE_BYPASS) अणु
		काष्ठा ib_grh grh;
		/*
		 * Assuming we only created 16B on the send side
		 * अगर we want to use large LIDs, since GRH was stripped
		 * out when creating 16B, add back the GRH here.
		 */
		hfi1_make_ext_grh(packet, &grh, slid, dlid);
		rvt_copy_sge(qp, &qp->r_sge, &grh,
			     माप(काष्ठा ib_grh), true, false);
		wc.wc_flags |= IB_WC_GRH;
	पूर्ण अन्यथा अणु
		rvt_skip_sge(&qp->r_sge, माप(काष्ठा ib_grh), true);
	पूर्ण
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

	अगर (qp->ibqp.qp_type == IB_QPT_GSI ||
	    qp->ibqp.qp_type == IB_QPT_SMI) अणु
		अगर (mgmt_pkey_idx < 0) अणु
			अगर (net_ratelimit()) अणु
				काष्ठा hfi1_devdata *dd = ppd->dd;

				dd_dev_err(dd, "QP type %d mgmt_pkey_idx < 0 and packet not dropped???\n",
					   qp->ibqp.qp_type);
				mgmt_pkey_idx = 0;
			पूर्ण
		पूर्ण
		wc.pkey_index = (अचिन्हित)mgmt_pkey_idx;
	पूर्ण अन्यथा अणु
		wc.pkey_index = 0;
	पूर्ण
	अगर (slid_is_permissive)
		slid = be32_to_cpu(OPA_LID_PERMISSIVE);
	wc.slid = slid & U16_MAX;
	wc.sl = sl_from_sc;

	/*
	 * Save the LMC lower bits अगर the destination LID is a unicast LID.
	 */
	wc.dlid_path_bits = hfi1_check_mcast(dlid) ? 0 :
		dlid & ((1 << ppd_from_ibp(ibp)->lmc) - 1);
	wc.port_num = qp->port_num;
	/* Signal completion event अगर the solicited bit is set. */
	rvt_recv_cq(qp, &wc, solicited);
	वापस;

drop:
	ibp->rvp.n_pkt_drops++;
पूर्ण
