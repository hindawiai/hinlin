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

#समावेश <linux/spinlock.h>
#समावेश <rdma/ib_smi.h>

#समावेश "qib.h"
#समावेश "qib_mad.h"

/*
 * Switch to alternate path.
 * The QP s_lock should be held and पूर्णांकerrupts disabled.
 */
व्योम qib_migrate_qp(काष्ठा rvt_qp *qp)
अणु
	काष्ठा ib_event ev;

	qp->s_mig_state = IB_MIG_MIGRATED;
	qp->remote_ah_attr = qp->alt_ah_attr;
	qp->port_num = rdma_ah_get_port_num(&qp->alt_ah_attr);
	qp->s_pkey_index = qp->s_alt_pkey_index;

	ev.device = qp->ibqp.device;
	ev.element.qp = &qp->ibqp;
	ev.event = IB_EVENT_PATH_MIG;
	qp->ibqp.event_handler(&ev, qp->ibqp.qp_context);
पूर्ण

अटल __be64 get_sguid(काष्ठा qib_ibport *ibp, अचिन्हित index)
अणु
	अगर (!index) अणु
		काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);

		वापस ppd->guid;
	पूर्ण
	वापस ibp->guids[index - 1];
पूर्ण

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
 * The s_lock will be acquired around the qib_migrate_qp() call.
 */
पूर्णांक qib_ruc_check_hdr(काष्ठा qib_ibport *ibp, काष्ठा ib_header *hdr,
		      पूर्णांक has_grh, काष्ठा rvt_qp *qp, u32 bth0)
अणु
	__be64 guid;
	अचिन्हित दीर्घ flags;

	अगर (qp->s_mig_state == IB_MIG_ARMED && (bth0 & IB_BTH_MIG_REQ)) अणु
		अगर (!has_grh) अणु
			अगर (rdma_ah_get_ah_flags(&qp->alt_ah_attr) &
			    IB_AH_GRH)
				जाओ err;
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा ib_global_route *grh;

			अगर (!(rdma_ah_get_ah_flags(&qp->alt_ah_attr) &
			      IB_AH_GRH))
				जाओ err;
			grh = rdma_ah_पढ़ो_grh(&qp->alt_ah_attr);
			guid = get_sguid(ibp, grh->sgid_index);
			अगर (!gid_ok(&hdr->u.l.grh.dgid,
				    ibp->rvp.gid_prefix, guid))
				जाओ err;
			अगर (!gid_ok(&hdr->u.l.grh.sgid,
			    grh->dgid.global.subnet_prefix,
			    grh->dgid.global.पूर्णांकerface_id))
				जाओ err;
		पूर्ण
		अगर (!qib_pkey_ok((u16)bth0,
				 qib_get_pkey(ibp, qp->s_alt_pkey_index))) अणु
			qib_bad_pkey(ibp,
				     (u16)bth0,
				     (be16_to_cpu(hdr->lrh[0]) >> 4) & 0xF,
				     0, qp->ibqp.qp_num,
				     hdr->lrh[3], hdr->lrh[1]);
			जाओ err;
		पूर्ण
		/* Validate the SLID. See Ch. 9.6.1.5 and 17.2.8 */
		अगर ((be16_to_cpu(hdr->lrh[3]) !=
		     rdma_ah_get_dlid(&qp->alt_ah_attr)) ||
		    ppd_from_ibp(ibp)->port !=
			    rdma_ah_get_port_num(&qp->alt_ah_attr))
			जाओ err;
		spin_lock_irqsave(&qp->s_lock, flags);
		qib_migrate_qp(qp);
		spin_unlock_irqrestore(&qp->s_lock, flags);
	पूर्ण अन्यथा अणु
		अगर (!has_grh) अणु
			अगर (rdma_ah_get_ah_flags(&qp->remote_ah_attr) &
			    IB_AH_GRH)
				जाओ err;
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा ib_global_route *grh;

			अगर (!(rdma_ah_get_ah_flags(&qp->remote_ah_attr) &
			      IB_AH_GRH))
				जाओ err;
			grh = rdma_ah_पढ़ो_grh(&qp->remote_ah_attr);
			guid = get_sguid(ibp, grh->sgid_index);
			अगर (!gid_ok(&hdr->u.l.grh.dgid,
				    ibp->rvp.gid_prefix, guid))
				जाओ err;
			अगर (!gid_ok(&hdr->u.l.grh.sgid,
			    grh->dgid.global.subnet_prefix,
			    grh->dgid.global.पूर्णांकerface_id))
				जाओ err;
		पूर्ण
		अगर (!qib_pkey_ok((u16)bth0,
				 qib_get_pkey(ibp, qp->s_pkey_index))) अणु
			qib_bad_pkey(ibp,
				     (u16)bth0,
				     (be16_to_cpu(hdr->lrh[0]) >> 4) & 0xF,
				     0, qp->ibqp.qp_num,
				     hdr->lrh[3], hdr->lrh[1]);
			जाओ err;
		पूर्ण
		/* Validate the SLID. See Ch. 9.6.1.5 */
		अगर (be16_to_cpu(hdr->lrh[3]) !=
		    rdma_ah_get_dlid(&qp->remote_ah_attr) ||
		    ppd_from_ibp(ibp)->port != qp->port_num)
			जाओ err;
		अगर (qp->s_mig_state == IB_MIG_REARM &&
		    !(bth0 & IB_BTH_MIG_REQ))
			qp->s_mig_state = IB_MIG_ARMED;
	पूर्ण

	वापस 0;

err:
	वापस 1;
पूर्ण

/**
 * qib_make_grh - स्थिरruct a GRH header
 * @ibp: a poपूर्णांकer to the IB port
 * @hdr: a poपूर्णांकer to the GRH header being स्थिरructed
 * @grh: the global route address to send to
 * @hwords: the number of 32 bit words of header being sent
 * @nwords: the number of 32 bit words of data being sent
 *
 * Return the size of the header in 32 bit words.
 */
u32 qib_make_grh(काष्ठा qib_ibport *ibp, काष्ठा ib_grh *hdr,
		 स्थिर काष्ठा ib_global_route *grh, u32 hwords, u32 nwords)
अणु
	hdr->version_tclass_flow =
		cpu_to_be32((IB_GRH_VERSION << IB_GRH_VERSION_SHIFT) |
			    (grh->traffic_class << IB_GRH_TCLASS_SHIFT) |
			    (grh->flow_label << IB_GRH_FLOW_SHIFT));
	hdr->paylen = cpu_to_be16((hwords - 2 + nwords + SIZE_OF_CRC) << 2);
	/* next_hdr is defined by C8-7 in ch. 8.4.1 */
	hdr->next_hdr = IB_GRH_NEXT_HDR;
	hdr->hop_limit = grh->hop_limit;
	/* The SGID is 32-bit aligned. */
	hdr->sgid.global.subnet_prefix = ibp->rvp.gid_prefix;
	अगर (!grh->sgid_index)
		hdr->sgid.global.पूर्णांकerface_id = ppd_from_ibp(ibp)->guid;
	अन्यथा अगर (grh->sgid_index < QIB_GUIDS_PER_PORT)
		hdr->sgid.global.पूर्णांकerface_id = ibp->guids[grh->sgid_index - 1];
	hdr->dgid = grh->dgid;

	/* GRH header size in 32-bit words. */
	वापस माप(काष्ठा ib_grh) / माप(u32);
पूर्ण

व्योम qib_make_ruc_header(काष्ठा rvt_qp *qp, काष्ठा ib_other_headers *ohdr,
			 u32 bth0, u32 bth2)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;
	काष्ठा qib_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	u16 lrh0;
	u32 nwords;
	u32 extra_bytes;

	/* Conकाष्ठा the header. */
	extra_bytes = -qp->s_cur_size & 3;
	nwords = (qp->s_cur_size + extra_bytes) >> 2;
	lrh0 = QIB_LRH_BTH;
	अगर (unlikely(rdma_ah_get_ah_flags(&qp->remote_ah_attr) & IB_AH_GRH)) अणु
		qp->s_hdrwords +=
			qib_make_grh(ibp, &priv->s_hdr->u.l.grh,
				     rdma_ah_पढ़ो_grh(&qp->remote_ah_attr),
				     qp->s_hdrwords, nwords);
		lrh0 = QIB_LRH_GRH;
	पूर्ण
	lrh0 |= ibp->sl_to_vl[rdma_ah_get_sl(&qp->remote_ah_attr)] << 12 |
		rdma_ah_get_sl(&qp->remote_ah_attr) << 4;
	priv->s_hdr->lrh[0] = cpu_to_be16(lrh0);
	priv->s_hdr->lrh[1] =
			cpu_to_be16(rdma_ah_get_dlid(&qp->remote_ah_attr));
	priv->s_hdr->lrh[2] =
			cpu_to_be16(qp->s_hdrwords + nwords + SIZE_OF_CRC);
	priv->s_hdr->lrh[3] =
		cpu_to_be16(ppd_from_ibp(ibp)->lid |
			    rdma_ah_get_path_bits(&qp->remote_ah_attr));
	bth0 |= qib_get_pkey(ibp, qp->s_pkey_index);
	bth0 |= extra_bytes << 20;
	अगर (qp->s_mig_state == IB_MIG_MIGRATED)
		bth0 |= IB_BTH_MIG_REQ;
	ohdr->bth[0] = cpu_to_be32(bth0);
	ohdr->bth[1] = cpu_to_be32(qp->remote_qpn);
	ohdr->bth[2] = cpu_to_be32(bth2);
	this_cpu_inc(ibp->pmastats->n_unicast_xmit);
पूर्ण

व्योम _qib_करो_send(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qib_qp_priv *priv = container_of(work, काष्ठा qib_qp_priv,
						s_work);
	काष्ठा rvt_qp *qp = priv->owner;

	qib_करो_send(qp);
पूर्ण

/**
 * qib_करो_send - perक्रमm a send on a QP
 * @qp: poपूर्णांकer to the QP
 *
 * Process entries in the send work queue until credit or queue is
 * exhausted.  Only allow one CPU to send a packet per QP (tasklet).
 * Otherwise, two thपढ़ोs could send packets out of order.
 */
व्योम qib_करो_send(काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;
	काष्ठा qib_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	पूर्णांक (*make_req)(काष्ठा rvt_qp *qp, अचिन्हित दीर्घ *flags);
	अचिन्हित दीर्घ flags;

	अगर ((qp->ibqp.qp_type == IB_QPT_RC ||
	     qp->ibqp.qp_type == IB_QPT_UC) &&
	    (rdma_ah_get_dlid(&qp->remote_ah_attr) &
	     ~((1 << ppd->lmc) - 1)) == ppd->lid) अणु
		rvt_ruc_loopback(qp);
		वापस;
	पूर्ण

	अगर (qp->ibqp.qp_type == IB_QPT_RC)
		make_req = qib_make_rc_req;
	अन्यथा अगर (qp->ibqp.qp_type == IB_QPT_UC)
		make_req = qib_make_uc_req;
	अन्यथा
		make_req = qib_make_ud_req;

	spin_lock_irqsave(&qp->s_lock, flags);

	/* Return अगर we are alपढ़ोy busy processing a work request. */
	अगर (!qib_send_ok(qp)) अणु
		spin_unlock_irqrestore(&qp->s_lock, flags);
		वापस;
	पूर्ण

	qp->s_flags |= RVT_S_BUSY;

	करो अणु
		/* Check क्रम a स्थिरructed packet to be sent. */
		अगर (qp->s_hdrwords != 0) अणु
			spin_unlock_irqrestore(&qp->s_lock, flags);
			/*
			 * If the packet cannot be sent now, वापस and
			 * the send tasklet will be woken up later.
			 */
			अगर (qib_verbs_send(qp, priv->s_hdr, qp->s_hdrwords,
					   qp->s_cur_sge, qp->s_cur_size))
				वापस;
			/* Record that s_hdr is empty. */
			qp->s_hdrwords = 0;
			spin_lock_irqsave(&qp->s_lock, flags);
		पूर्ण
	पूर्ण जबतक (make_req(qp, &flags));

	spin_unlock_irqrestore(&qp->s_lock, flags);
पूर्ण
