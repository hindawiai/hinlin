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

#समावेश <linux/spinlock.h>

#समावेश "hfi.h"
#समावेश "mad.h"
#समावेश "qp.h"
#समावेश "verbs_txreq.h"
#समावेश "trace.h"

अटल पूर्णांक gid_ok(जोड़ ib_gid *gid, __be64 gid_prefix, __be64 id)
अणु
	वापस (gid->global.पूर्णांकerface_id == id &&
		(gid->global.subnet_prefix == gid_prefix ||
		 gid->global.subnet_prefix == IB_DEFAULT_GID_PREFIX));
पूर्ण

/*
 *
 * This should be called with the QP r_lock held.
 *
 * The s_lock will be acquired around the hfi1_migrate_qp() call.
 */
पूर्णांक hfi1_ruc_check_hdr(काष्ठा hfi1_ibport *ibp, काष्ठा hfi1_packet *packet)
अणु
	__be64 guid;
	अचिन्हित दीर्घ flags;
	काष्ठा rvt_qp *qp = packet->qp;
	u8 sc5 = ibp->sl_to_sc[rdma_ah_get_sl(&qp->remote_ah_attr)];
	u32 dlid = packet->dlid;
	u32 slid = packet->slid;
	u32 sl = packet->sl;
	bool migrated = packet->migrated;
	u16 pkey = packet->pkey;

	अगर (qp->s_mig_state == IB_MIG_ARMED && migrated) अणु
		अगर (!packet->grh) अणु
			अगर ((rdma_ah_get_ah_flags(&qp->alt_ah_attr) &
			     IB_AH_GRH) &&
			    (packet->etype != RHF_RCV_TYPE_BYPASS))
				वापस 1;
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा ib_global_route *grh;

			अगर (!(rdma_ah_get_ah_flags(&qp->alt_ah_attr) &
			      IB_AH_GRH))
				वापस 1;
			grh = rdma_ah_पढ़ो_grh(&qp->alt_ah_attr);
			guid = get_sguid(ibp, grh->sgid_index);
			अगर (!gid_ok(&packet->grh->dgid, ibp->rvp.gid_prefix,
				    guid))
				वापस 1;
			अगर (!gid_ok(
				&packet->grh->sgid,
				grh->dgid.global.subnet_prefix,
				grh->dgid.global.पूर्णांकerface_id))
				वापस 1;
		पूर्ण
		अगर (unlikely(rcv_pkey_check(ppd_from_ibp(ibp), pkey,
					    sc5, slid))) अणु
			hfi1_bad_pkey(ibp, pkey, sl, 0, qp->ibqp.qp_num,
				      slid, dlid);
			वापस 1;
		पूर्ण
		/* Validate the SLID. See Ch. 9.6.1.5 and 17.2.8 */
		अगर (slid != rdma_ah_get_dlid(&qp->alt_ah_attr) ||
		    ppd_from_ibp(ibp)->port !=
			rdma_ah_get_port_num(&qp->alt_ah_attr))
			वापस 1;
		spin_lock_irqsave(&qp->s_lock, flags);
		hfi1_migrate_qp(qp);
		spin_unlock_irqrestore(&qp->s_lock, flags);
	पूर्ण अन्यथा अणु
		अगर (!packet->grh) अणु
			अगर ((rdma_ah_get_ah_flags(&qp->remote_ah_attr) &
			     IB_AH_GRH) &&
			    (packet->etype != RHF_RCV_TYPE_BYPASS))
				वापस 1;
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा ib_global_route *grh;

			अगर (!(rdma_ah_get_ah_flags(&qp->remote_ah_attr) &
						   IB_AH_GRH))
				वापस 1;
			grh = rdma_ah_पढ़ो_grh(&qp->remote_ah_attr);
			guid = get_sguid(ibp, grh->sgid_index);
			अगर (!gid_ok(&packet->grh->dgid, ibp->rvp.gid_prefix,
				    guid))
				वापस 1;
			अगर (!gid_ok(
			     &packet->grh->sgid,
			     grh->dgid.global.subnet_prefix,
			     grh->dgid.global.पूर्णांकerface_id))
				वापस 1;
		पूर्ण
		अगर (unlikely(rcv_pkey_check(ppd_from_ibp(ibp), pkey,
					    sc5, slid))) अणु
			hfi1_bad_pkey(ibp, pkey, sl, 0, qp->ibqp.qp_num,
				      slid, dlid);
			वापस 1;
		पूर्ण
		/* Validate the SLID. See Ch. 9.6.1.5 */
		अगर ((slid != rdma_ah_get_dlid(&qp->remote_ah_attr)) ||
		    ppd_from_ibp(ibp)->port != qp->port_num)
			वापस 1;
		अगर (qp->s_mig_state == IB_MIG_REARM && !migrated)
			qp->s_mig_state = IB_MIG_ARMED;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hfi1_make_grh - स्थिरruct a GRH header
 * @ibp: a poपूर्णांकer to the IB port
 * @hdr: a poपूर्णांकer to the GRH header being स्थिरructed
 * @grh: the global route address to send to
 * @hwords: size of header after grh being sent in dwords
 * @nwords: the number of 32 bit words of data being sent
 *
 * Return the size of the header in 32 bit words.
 */
u32 hfi1_make_grh(काष्ठा hfi1_ibport *ibp, काष्ठा ib_grh *hdr,
		  स्थिर काष्ठा ib_global_route *grh, u32 hwords, u32 nwords)
अणु
	hdr->version_tclass_flow =
		cpu_to_be32((IB_GRH_VERSION << IB_GRH_VERSION_SHIFT) |
			    (grh->traffic_class << IB_GRH_TCLASS_SHIFT) |
			    (grh->flow_label << IB_GRH_FLOW_SHIFT));
	hdr->paylen = cpu_to_be16((hwords + nwords) << 2);
	/* next_hdr is defined by C8-7 in ch. 8.4.1 */
	hdr->next_hdr = IB_GRH_NEXT_HDR;
	hdr->hop_limit = grh->hop_limit;
	/* The SGID is 32-bit aligned. */
	hdr->sgid.global.subnet_prefix = ibp->rvp.gid_prefix;
	hdr->sgid.global.पूर्णांकerface_id =
		grh->sgid_index < HFI1_GUIDS_PER_PORT ?
		get_sguid(ibp, grh->sgid_index) :
		get_sguid(ibp, HFI1_PORT_GUID_INDEX);
	hdr->dgid = grh->dgid;

	/* GRH header size in 32-bit words. */
	वापस माप(काष्ठा ib_grh) / माप(u32);
पूर्ण

#घोषणा BTH2_OFFSET (दुरत्व(काष्ठा hfi1_sdma_header, \
			      hdr.ibh.u.oth.bth[2]) / 4)

/**
 * build_ahg - create ahg in s_ahg
 * @qp: a poपूर्णांकer to QP
 * @npsn: the next PSN क्रम the request/response
 *
 * This routine handles the AHG by allocating an ahg entry and causing the
 * copy of the first middle.
 *
 * Subsequent middles use the copied entry, editing the
 * PSN with 1 or 2 edits.
 */
अटल अंतरभूत व्योम build_ahg(काष्ठा rvt_qp *qp, u32 npsn)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	अगर (unlikely(qp->s_flags & HFI1_S_AHG_CLEAR))
		clear_ahg(qp);
	अगर (!(qp->s_flags & HFI1_S_AHG_VALID)) अणु
		/* first middle that needs copy  */
		अगर (qp->s_ahgidx < 0)
			qp->s_ahgidx = sdma_ahg_alloc(priv->s_sde);
		अगर (qp->s_ahgidx >= 0) अणु
			qp->s_ahgpsn = npsn;
			priv->s_ahg->tx_flags |= SDMA_TXREQ_F_AHG_COPY;
			/* save to protect a change in another thपढ़ो */
			priv->s_ahg->ahgidx = qp->s_ahgidx;
			qp->s_flags |= HFI1_S_AHG_VALID;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* subsequent middle after valid */
		अगर (qp->s_ahgidx >= 0) अणु
			priv->s_ahg->tx_flags |= SDMA_TXREQ_F_USE_AHG;
			priv->s_ahg->ahgidx = qp->s_ahgidx;
			priv->s_ahg->ahgcount++;
			priv->s_ahg->ahgdesc[0] =
				sdma_build_ahg_descriptor(
					(__क्रमce u16)cpu_to_be16((u16)npsn),
					BTH2_OFFSET,
					16,
					16);
			अगर ((npsn & 0xffff0000) !=
					(qp->s_ahgpsn & 0xffff0000)) अणु
				priv->s_ahg->ahgcount++;
				priv->s_ahg->ahgdesc[1] =
					sdma_build_ahg_descriptor(
						(__क्रमce u16)cpu_to_be16(
							(u16)(npsn >> 16)),
						BTH2_OFFSET,
						0,
						16);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम hfi1_make_ruc_bth(काष्ठा rvt_qp *qp,
				     काष्ठा ib_other_headers *ohdr,
				     u32 bth0, u32 bth1, u32 bth2)
अणु
	ohdr->bth[0] = cpu_to_be32(bth0);
	ohdr->bth[1] = cpu_to_be32(bth1);
	ohdr->bth[2] = cpu_to_be32(bth2);
पूर्ण

/**
 * hfi1_make_ruc_header_16B - build a 16B header
 * @qp: the queue pair
 * @ohdr: a poपूर्णांकer to the destination header memory
 * @bth0: bth0 passed in from the RC/UC builder
 * @bth1: bth1 passed in from the RC/UC builder
 * @bth2: bth2 passed in from the RC/UC builder
 * @middle: non zero implies indicates ahg "could" be used
 * @ps: the current packet state
 *
 * This routine may disarm ahg under these situations:
 * - packet needs a GRH
 * - BECN needed
 * - migration state not IB_MIG_MIGRATED
 */
अटल अंतरभूत व्योम hfi1_make_ruc_header_16B(काष्ठा rvt_qp *qp,
					    काष्ठा ib_other_headers *ohdr,
					    u32 bth0, u32 bth1, u32 bth2,
					    पूर्णांक middle,
					    काष्ठा hfi1_pkt_state *ps)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा hfi1_ibport *ibp = ps->ibp;
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u32 slid;
	u16 pkey = hfi1_get_pkey(ibp, qp->s_pkey_index);
	u8 l4 = OPA_16B_L4_IB_LOCAL;
	u8 extra_bytes = hfi1_get_16b_padding(
				(ps->s_txreq->hdr_dwords << 2),
				ps->s_txreq->s_cur_size);
	u32 nwords = SIZE_OF_CRC + ((ps->s_txreq->s_cur_size +
				 extra_bytes + SIZE_OF_LT) >> 2);
	bool becn = false;

	अगर (unlikely(rdma_ah_get_ah_flags(&qp->remote_ah_attr) & IB_AH_GRH) &&
	    hfi1_check_mcast(rdma_ah_get_dlid(&qp->remote_ah_attr))) अणु
		काष्ठा ib_grh *grh;
		काष्ठा ib_global_route *grd =
			rdma_ah_retrieve_grh(&qp->remote_ah_attr);
		/*
		 * Ensure OPA GIDs are transक्रमmed to IB gids
		 * beक्रमe creating the GRH.
		 */
		अगर (grd->sgid_index == OPA_GID_INDEX)
			grd->sgid_index = 0;
		grh = &ps->s_txreq->phdr.hdr.opah.u.l.grh;
		l4 = OPA_16B_L4_IB_GLOBAL;
		ps->s_txreq->hdr_dwords +=
			hfi1_make_grh(ibp, grh, grd,
				      ps->s_txreq->hdr_dwords - LRH_16B_DWORDS,
				      nwords);
		middle = 0;
	पूर्ण

	अगर (qp->s_mig_state == IB_MIG_MIGRATED)
		bth1 |= OPA_BTH_MIG_REQ;
	अन्यथा
		middle = 0;

	अगर (qp->s_flags & RVT_S_ECN) अणु
		qp->s_flags &= ~RVT_S_ECN;
		/* we recently received a FECN, so वापस a BECN */
		becn = true;
		middle = 0;
	पूर्ण
	अगर (middle)
		build_ahg(qp, bth2);
	अन्यथा
		qp->s_flags &= ~HFI1_S_AHG_VALID;

	bth0 |= pkey;
	bth0 |= extra_bytes << 20;
	hfi1_make_ruc_bth(qp, ohdr, bth0, bth1, bth2);

	अगर (!ppd->lid)
		slid = be32_to_cpu(OPA_LID_PERMISSIVE);
	अन्यथा
		slid = ppd->lid |
			(rdma_ah_get_path_bits(&qp->remote_ah_attr) &
			((1 << ppd->lmc) - 1));

	hfi1_make_16b_hdr(&ps->s_txreq->phdr.hdr.opah,
			  slid,
			  opa_get_lid(rdma_ah_get_dlid(&qp->remote_ah_attr),
				      16B),
			  (ps->s_txreq->hdr_dwords + nwords) >> 1,
			  pkey, becn, 0, l4, priv->s_sc);
पूर्ण

/**
 * hfi1_make_ruc_header_9B - build a 9B header
 * @qp: the queue pair
 * @ohdr: a poपूर्णांकer to the destination header memory
 * @bth0: bth0 passed in from the RC/UC builder
 * @bth1: bth1 passed in from the RC/UC builder
 * @bth2: bth2 passed in from the RC/UC builder
 * @middle: non zero implies indicates ahg "could" be used
 * @ps: the current packet state
 *
 * This routine may disarm ahg under these situations:
 * - packet needs a GRH
 * - BECN needed
 * - migration state not IB_MIG_MIGRATED
 */
अटल अंतरभूत व्योम hfi1_make_ruc_header_9B(काष्ठा rvt_qp *qp,
					   काष्ठा ib_other_headers *ohdr,
					   u32 bth0, u32 bth1, u32 bth2,
					   पूर्णांक middle,
					   काष्ठा hfi1_pkt_state *ps)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा hfi1_ibport *ibp = ps->ibp;
	u16 pkey = hfi1_get_pkey(ibp, qp->s_pkey_index);
	u16 lrh0 = HFI1_LRH_BTH;
	u8 extra_bytes = -ps->s_txreq->s_cur_size & 3;
	u32 nwords = SIZE_OF_CRC + ((ps->s_txreq->s_cur_size +
					 extra_bytes) >> 2);

	अगर (unlikely(rdma_ah_get_ah_flags(&qp->remote_ah_attr) & IB_AH_GRH)) अणु
		काष्ठा ib_grh *grh = &ps->s_txreq->phdr.hdr.ibh.u.l.grh;

		lrh0 = HFI1_LRH_GRH;
		ps->s_txreq->hdr_dwords +=
			hfi1_make_grh(ibp, grh,
				      rdma_ah_पढ़ो_grh(&qp->remote_ah_attr),
				      ps->s_txreq->hdr_dwords - LRH_9B_DWORDS,
				      nwords);
		middle = 0;
	पूर्ण
	lrh0 |= (priv->s_sc & 0xf) << 12 |
		(rdma_ah_get_sl(&qp->remote_ah_attr) & 0xf) << 4;

	अगर (qp->s_mig_state == IB_MIG_MIGRATED)
		bth0 |= IB_BTH_MIG_REQ;
	अन्यथा
		middle = 0;

	अगर (qp->s_flags & RVT_S_ECN) अणु
		qp->s_flags &= ~RVT_S_ECN;
		/* we recently received a FECN, so वापस a BECN */
		bth1 |= (IB_BECN_MASK << IB_BECN_SHIFT);
		middle = 0;
	पूर्ण
	अगर (middle)
		build_ahg(qp, bth2);
	अन्यथा
		qp->s_flags &= ~HFI1_S_AHG_VALID;

	bth0 |= pkey;
	bth0 |= extra_bytes << 20;
	hfi1_make_ruc_bth(qp, ohdr, bth0, bth1, bth2);
	hfi1_make_ib_hdr(&ps->s_txreq->phdr.hdr.ibh,
			 lrh0,
			 ps->s_txreq->hdr_dwords + nwords,
			 opa_get_lid(rdma_ah_get_dlid(&qp->remote_ah_attr), 9B),
			 ppd_from_ibp(ibp)->lid |
				rdma_ah_get_path_bits(&qp->remote_ah_attr));
पूर्ण

प्रकार व्योम (*hfi1_make_ruc_hdr)(काष्ठा rvt_qp *qp,
				  काष्ठा ib_other_headers *ohdr,
				  u32 bth0, u32 bth1, u32 bth2, पूर्णांक middle,
				  काष्ठा hfi1_pkt_state *ps);

/* We support only two types - 9B and 16B क्रम now */
अटल स्थिर hfi1_make_ruc_hdr hfi1_ruc_header_tbl[2] = अणु
	[HFI1_PKT_TYPE_9B] = &hfi1_make_ruc_header_9B,
	[HFI1_PKT_TYPE_16B] = &hfi1_make_ruc_header_16B
पूर्ण;

व्योम hfi1_make_ruc_header(काष्ठा rvt_qp *qp, काष्ठा ib_other_headers *ohdr,
			  u32 bth0, u32 bth1, u32 bth2, पूर्णांक middle,
			  काष्ठा hfi1_pkt_state *ps)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	/*
	 * reset s_ahg/AHG fields
	 *
	 * This insures that the ahgentry/ahgcount
	 * are at a non-AHG शेष to protect
	 * build_verbs_tx_desc() from using
	 * an include ahgidx.
	 *
	 * build_ahg() will modअगरy as appropriate
	 * to use the AHG feature.
	 */
	priv->s_ahg->tx_flags = 0;
	priv->s_ahg->ahgcount = 0;
	priv->s_ahg->ahgidx = 0;

	/* Make the appropriate header */
	hfi1_ruc_header_tbl[priv->hdr_type](qp, ohdr, bth0, bth1, bth2, middle,
					    ps);
पूर्ण

/* when sending, क्रमce a reschedule every one of these periods */
#घोषणा SEND_RESCHED_TIMEOUT (5 * HZ)  /* 5s in jअगरfies */

/**
 * hfi1_schedule_send_yield - test क्रम a yield required क्रम QP
 * send engine
 * @qp: a poपूर्णांकer to QP
 * @ps: a poपूर्णांकer to a काष्ठाure with commonly lookup values क्रम
 *      the the send engine progress
 * @tid: true अगर it is the tid leg
 *
 * This routine checks अगर the समय slice क्रम the QP has expired
 * क्रम RC QPs, अगर so an additional work entry is queued. At this
 * poपूर्णांक, other QPs have an opportunity to be scheduled. It
 * वापसs true अगर a yield is required, otherwise, false
 * is वापसed.
 */
bool hfi1_schedule_send_yield(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps,
			      bool tid)
अणु
	ps->pkts_sent = true;

	अगर (unlikely(समय_after(jअगरfies, ps->समयout))) अणु
		अगर (!ps->in_thपढ़ो ||
		    workqueue_congested(ps->cpu, ps->ppd->hfi1_wq)) अणु
			spin_lock_irqsave(&qp->s_lock, ps->flags);
			अगर (!tid) अणु
				qp->s_flags &= ~RVT_S_BUSY;
				hfi1_schedule_send(qp);
			पूर्ण अन्यथा अणु
				काष्ठा hfi1_qp_priv *priv = qp->priv;

				अगर (priv->s_flags &
				    HFI1_S_TID_BUSY_SET) अणु
					qp->s_flags &= ~RVT_S_BUSY;
					priv->s_flags &=
						~(HFI1_S_TID_BUSY_SET |
						  RVT_S_BUSY);
				पूर्ण अन्यथा अणु
					priv->s_flags &= ~RVT_S_BUSY;
				पूर्ण
				hfi1_schedule_tid_send(qp);
			पूर्ण

			spin_unlock_irqrestore(&qp->s_lock, ps->flags);
			this_cpu_inc(*ps->ppd->dd->send_schedule);
			trace_hfi1_rc_expired_समय_slice(qp, true);
			वापस true;
		पूर्ण

		cond_resched();
		this_cpu_inc(*ps->ppd->dd->send_schedule);
		ps->समयout = jअगरfies + ps->समयout_पूर्णांक;
	पूर्ण

	trace_hfi1_rc_expired_समय_slice(qp, false);
	वापस false;
पूर्ण

व्योम hfi1_करो_send_from_rvt(काष्ठा rvt_qp *qp)
अणु
	hfi1_करो_send(qp, false);
पूर्ण

व्योम _hfi1_करो_send(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ioरुको_work *w = container_of(work, काष्ठा ioरुको_work, iowork);
	काष्ठा rvt_qp *qp = ioरुको_to_qp(w->iow);

	hfi1_करो_send(qp, true);
पूर्ण

/**
 * hfi1_करो_send - perक्रमm a send on a QP
 * @qp: a poपूर्णांकer to the QP
 * @in_thपढ़ो: true अगर in a workqueue thपढ़ो
 *
 * Process entries in the send work queue until credit or queue is
 * exhausted.  Only allow one CPU to send a packet per QP.
 * Otherwise, two thपढ़ोs could send packets out of order.
 */
व्योम hfi1_करो_send(काष्ठा rvt_qp *qp, bool in_thपढ़ो)
अणु
	काष्ठा hfi1_pkt_state ps;
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	पूर्णांक (*make_req)(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps);

	ps.dev = to_idev(qp->ibqp.device);
	ps.ibp = to_iport(qp->ibqp.device, qp->port_num);
	ps.ppd = ppd_from_ibp(ps.ibp);
	ps.in_thपढ़ो = in_thपढ़ो;
	ps.रुको = ioरुको_get_ib_work(&priv->s_ioरुको);

	trace_hfi1_rc_करो_send(qp, in_thपढ़ो);

	चयन (qp->ibqp.qp_type) अणु
	हाल IB_QPT_RC:
		अगर (!loopback && ((rdma_ah_get_dlid(&qp->remote_ah_attr) &
				   ~((1 << ps.ppd->lmc) - 1)) ==
				  ps.ppd->lid)) अणु
			rvt_ruc_loopback(qp);
			वापस;
		पूर्ण
		make_req = hfi1_make_rc_req;
		ps.समयout_पूर्णांक = qp->समयout_jअगरfies;
		अवरोध;
	हाल IB_QPT_UC:
		अगर (!loopback && ((rdma_ah_get_dlid(&qp->remote_ah_attr) &
				   ~((1 << ps.ppd->lmc) - 1)) ==
				  ps.ppd->lid)) अणु
			rvt_ruc_loopback(qp);
			वापस;
		पूर्ण
		make_req = hfi1_make_uc_req;
		ps.समयout_पूर्णांक = SEND_RESCHED_TIMEOUT;
		अवरोध;
	शेष:
		make_req = hfi1_make_ud_req;
		ps.समयout_पूर्णांक = SEND_RESCHED_TIMEOUT;
	पूर्ण

	spin_lock_irqsave(&qp->s_lock, ps.flags);

	/* Return अगर we are alपढ़ोy busy processing a work request. */
	अगर (!hfi1_send_ok(qp)) अणु
		अगर (qp->s_flags & HFI1_S_ANY_WAIT_IO)
			ioरुको_set_flag(&priv->s_ioरुको, IOWAIT_PENDING_IB);
		spin_unlock_irqrestore(&qp->s_lock, ps.flags);
		वापस;
	पूर्ण

	qp->s_flags |= RVT_S_BUSY;

	ps.समयout_पूर्णांक = ps.समयout_पूर्णांक / 8;
	ps.समयout = jअगरfies + ps.समयout_पूर्णांक;
	ps.cpu = priv->s_sde ? priv->s_sde->cpu :
			cpumask_first(cpumask_of_node(ps.ppd->dd->node));
	ps.pkts_sent = false;

	/* insure a pre-built packet is handled  */
	ps.s_txreq = get_रुकोing_verbs_txreq(ps.रुको);
	करो अणु
		/* Check क्रम a स्थिरructed packet to be sent. */
		अगर (ps.s_txreq) अणु
			अगर (priv->s_flags & HFI1_S_TID_BUSY_SET)
				qp->s_flags |= RVT_S_BUSY;
			spin_unlock_irqrestore(&qp->s_lock, ps.flags);
			/*
			 * If the packet cannot be sent now, वापस and
			 * the send engine will be woken up later.
			 */
			अगर (hfi1_verbs_send(qp, &ps))
				वापस;

			/* allow other tasks to run */
			अगर (hfi1_schedule_send_yield(qp, &ps, false))
				वापस;

			spin_lock_irqsave(&qp->s_lock, ps.flags);
		पूर्ण
	पूर्ण जबतक (make_req(qp, &ps));
	ioरुको_starve_clear(ps.pkts_sent, &priv->s_ioरुको);
	spin_unlock_irqrestore(&qp->s_lock, ps.flags);
पूर्ण
