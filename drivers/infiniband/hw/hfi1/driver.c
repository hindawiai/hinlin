<शैली गुरु>
/*
 * Copyright(c) 2015-2020 Intel Corporation.
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
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/prefetch.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <linux/etherdevice.h>

#समावेश "hfi.h"
#समावेश "trace.h"
#समावेश "qp.h"
#समावेश "sdma.h"
#समावेश "debugfs.h"
#समावेश "vnic.h"
#समावेश "fault.h"

#समावेश "ipoib.h"
#समावेश "netdev.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) DRIVER_NAME ": " fmt

/*
 * The size has to be दीर्घer than this string, so we can append
 * board/chip inक्रमmation to it in the initialization code.
 */
स्थिर अक्षर ib_hfi1_version[] = HFI1_DRIVER_VERSION "\n";

DEFINE_MUTEX(hfi1_mutex);	/* general driver use */

अचिन्हित पूर्णांक hfi1_max_mtu = HFI1_DEFAULT_MAX_MTU;
module_param_named(max_mtu, hfi1_max_mtu, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_mtu, "Set max MTU bytes, default is " __stringअगरy(
		 HFI1_DEFAULT_MAX_MTU));

अचिन्हित पूर्णांक hfi1_cu = 1;
module_param_named(cu, hfi1_cu, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(cu, "Credit return units");

अचिन्हित दीर्घ hfi1_cap_mask = HFI1_CAP_MASK_DEFAULT;
अटल पूर्णांक hfi1_caps_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल पूर्णांक hfi1_caps_get(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
अटल स्थिर काष्ठा kernel_param_ops cap_ops = अणु
	.set = hfi1_caps_set,
	.get = hfi1_caps_get
पूर्ण;
module_param_cb(cap_mask, &cap_ops, &hfi1_cap_mask, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(cap_mask, "Bit mask of enabled/disabled HW features");

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Intel Omni-Path Architecture driver");

/*
 * MAX_PKT_RCV is the max # अगर packets processed per receive पूर्णांकerrupt.
 */
#घोषणा MAX_PKT_RECV 64
/*
 * MAX_PKT_THREAD_RCV is the max # of packets processed beक्रमe
 * the qp_रुको_list queue is flushed.
 */
#घोषणा MAX_PKT_RECV_THREAD (MAX_PKT_RECV * 4)
#घोषणा EGR_HEAD_UPDATE_THRESHOLD 16

काष्ठा hfi1_ib_stats hfi1_stats;

अटल पूर्णांक hfi1_caps_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ *cap_mask_ptr = (अचिन्हित दीर्घ *)kp->arg,
		cap_mask = *cap_mask_ptr, value, dअगरf,
		ग_लिखो_mask = ((HFI1_CAP_WRITABLE_MASK << HFI1_CAP_USER_SHIFT) |
			      HFI1_CAP_WRITABLE_MASK);

	ret = kम_से_अदीर्घ(val, 0, &value);
	अगर (ret) अणु
		pr_warn("Invalid module parameter value for 'cap_mask'\n");
		जाओ करोne;
	पूर्ण
	/* Get the changed bits (except the locked bit) */
	dअगरf = value ^ (cap_mask & ~HFI1_CAP_LOCKED_SMASK);

	/* Remove any bits that are not allowed to change after driver load */
	अगर (HFI1_CAP_LOCKED() && (dअगरf & ~ग_लिखो_mask)) अणु
		pr_warn("Ignoring non-writable capability bits %#lx\n",
			dअगरf & ~ग_लिखो_mask);
		dअगरf &= ग_लिखो_mask;
	पूर्ण

	/* Mask off any reserved bits */
	dअगरf &= ~HFI1_CAP_RESERVED_MASK;
	/* Clear any previously set and changing bits */
	cap_mask &= ~dअगरf;
	/* Update the bits with the new capability */
	cap_mask |= (value & dअगरf);
	/* Check क्रम any kernel/user restrictions */
	dअगरf = (cap_mask & (HFI1_CAP_MUST_HAVE_KERN << HFI1_CAP_USER_SHIFT)) ^
		((cap_mask & HFI1_CAP_MUST_HAVE_KERN) << HFI1_CAP_USER_SHIFT);
	cap_mask &= ~dअगरf;
	/* Set the biपंचांगask to the final set */
	*cap_mask_ptr = cap_mask;
करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक hfi1_caps_get(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	अचिन्हित दीर्घ cap_mask = *(अचिन्हित दीर्घ *)kp->arg;

	cap_mask &= ~HFI1_CAP_LOCKED_SMASK;
	cap_mask |= ((cap_mask & HFI1_CAP_K2U) << HFI1_CAP_USER_SHIFT);

	वापस scnम_लिखो(buffer, PAGE_SIZE, "0x%lx", cap_mask);
पूर्ण

काष्ठा pci_dev *get_pci_dev(काष्ठा rvt_dev_info *rdi)
अणु
	काष्ठा hfi1_ibdev *ibdev = container_of(rdi, काष्ठा hfi1_ibdev, rdi);
	काष्ठा hfi1_devdata *dd = container_of(ibdev,
					       काष्ठा hfi1_devdata, verbs_dev);
	वापस dd->pcidev;
पूर्ण

/*
 * Return count of units with at least one port ACTIVE.
 */
पूर्णांक hfi1_count_active_units(व्योम)
अणु
	काष्ठा hfi1_devdata *dd;
	काष्ठा hfi1_pportdata *ppd;
	अचिन्हित दीर्घ index, flags;
	पूर्णांक pidx, nunits_active = 0;

	xa_lock_irqsave(&hfi1_dev_table, flags);
	xa_क्रम_each(&hfi1_dev_table, index, dd) अणु
		अगर (!(dd->flags & HFI1_PRESENT) || !dd->kregbase1)
			जारी;
		क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
			ppd = dd->pport + pidx;
			अगर (ppd->lid && ppd->linkup) अणु
				nunits_active++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	xa_unlock_irqrestore(&hfi1_dev_table, flags);
	वापस nunits_active;
पूर्ण

/*
 * Get address of eager buffer from it's index (allocated in chunks, not
 * contiguous).
 */
अटल अंतरभूत व्योम *get_egrbuf(स्थिर काष्ठा hfi1_ctxtdata *rcd, u64 rhf,
			       u8 *update)
अणु
	u32 idx = rhf_egr_index(rhf), offset = rhf_egr_buf_offset(rhf);

	*update |= !(idx & (rcd->egrbufs.threshold - 1)) && !offset;
	वापस (व्योम *)(((u64)(rcd->egrbufs.rcvtids[idx].addr)) +
			(offset * RCV_BUF_BLOCK_SIZE));
पूर्ण

अटल अंतरभूत व्योम *hfi1_get_header(काष्ठा hfi1_ctxtdata *rcd,
				    __le32 *rhf_addr)
अणु
	u32 offset = rhf_hdrq_offset(rhf_to_cpu(rhf_addr));

	वापस (व्योम *)(rhf_addr - rcd->rhf_offset + offset);
पूर्ण

अटल अंतरभूत काष्ठा ib_header *hfi1_get_msgheader(काष्ठा hfi1_ctxtdata *rcd,
						   __le32 *rhf_addr)
अणु
	वापस (काष्ठा ib_header *)hfi1_get_header(rcd, rhf_addr);
पूर्ण

अटल अंतरभूत काष्ठा hfi1_16b_header
		*hfi1_get_16B_header(काष्ठा hfi1_ctxtdata *rcd,
				     __le32 *rhf_addr)
अणु
	वापस (काष्ठा hfi1_16b_header *)hfi1_get_header(rcd, rhf_addr);
पूर्ण

/*
 * Validate and encode the a given RcvArray Buffer size.
 * The function will check whether the given size falls within
 * allowed size ranges क्रम the respective type and, optionally,
 * वापस the proper encoding.
 */
पूर्णांक hfi1_rcvbuf_validate(u32 size, u8 type, u16 *encoded)
अणु
	अगर (unlikely(!PAGE_ALIGNED(size)))
		वापस 0;
	अगर (unlikely(size < MIN_EAGER_BUFFER))
		वापस 0;
	अगर (size >
	    (type == PT_EAGER ? MAX_EAGER_BUFFER : MAX_EXPECTED_BUFFER))
		वापस 0;
	अगर (encoded)
		*encoded = ilog2(size / PAGE_SIZE) + 1;
	वापस 1;
पूर्ण

अटल व्योम rcv_hdrerr(काष्ठा hfi1_ctxtdata *rcd, काष्ठा hfi1_pportdata *ppd,
		       काष्ठा hfi1_packet *packet)
अणु
	काष्ठा ib_header *rhdr = packet->hdr;
	u32 rte = rhf_rcv_type_err(packet->rhf);
	u32 mlid_base;
	काष्ठा hfi1_ibport *ibp = rcd_to_iport(rcd);
	काष्ठा hfi1_devdata *dd = ppd->dd;
	काष्ठा hfi1_ibdev *verbs_dev = &dd->verbs_dev;
	काष्ठा rvt_dev_info *rdi = &verbs_dev->rdi;

	अगर ((packet->rhf & RHF_DC_ERR) &&
	    hfi1_dbg_fault_suppress_err(verbs_dev))
		वापस;

	अगर (packet->rhf & RHF_ICRC_ERR)
		वापस;

	अगर (packet->etype == RHF_RCV_TYPE_BYPASS) अणु
		जाओ drop;
	पूर्ण अन्यथा अणु
		u8 lnh = ib_get_lnh(rhdr);

		mlid_base = be16_to_cpu(IB_MULTICAST_LID_BASE);
		अगर (lnh == HFI1_LRH_BTH) अणु
			packet->ohdr = &rhdr->u.oth;
		पूर्ण अन्यथा अगर (lnh == HFI1_LRH_GRH) अणु
			packet->ohdr = &rhdr->u.l.oth;
			packet->grh = &rhdr->u.l.grh;
		पूर्ण अन्यथा अणु
			जाओ drop;
		पूर्ण
	पूर्ण

	अगर (packet->rhf & RHF_TID_ERR) अणु
		/* For TIDERR and RC QPs preemptively schedule a NAK */
		u32 tlen = rhf_pkt_len(packet->rhf); /* in bytes */
		u32 dlid = ib_get_dlid(rhdr);
		u32 qp_num;

		/* Sanity check packet */
		अगर (tlen < 24)
			जाओ drop;

		/* Check क्रम GRH */
		अगर (packet->grh) अणु
			u32 vtf;
			काष्ठा ib_grh *grh = packet->grh;

			अगर (grh->next_hdr != IB_GRH_NEXT_HDR)
				जाओ drop;
			vtf = be32_to_cpu(grh->version_tclass_flow);
			अगर ((vtf >> IB_GRH_VERSION_SHIFT) != IB_GRH_VERSION)
				जाओ drop;
		पूर्ण

		/* Get the destination QP number. */
		qp_num = ib_bth_get_qpn(packet->ohdr);
		अगर (dlid < mlid_base) अणु
			काष्ठा rvt_qp *qp;
			अचिन्हित दीर्घ flags;

			rcu_पढ़ो_lock();
			qp = rvt_lookup_qpn(rdi, &ibp->rvp, qp_num);
			अगर (!qp) अणु
				rcu_पढ़ो_unlock();
				जाओ drop;
			पूर्ण

			/*
			 * Handle only RC QPs - क्रम other QP types drop error
			 * packet.
			 */
			spin_lock_irqsave(&qp->r_lock, flags);

			/* Check क्रम valid receive state. */
			अगर (!(ib_rvt_state_ops[qp->state] &
			      RVT_PROCESS_RECV_OK)) अणु
				ibp->rvp.n_pkt_drops++;
			पूर्ण

			चयन (qp->ibqp.qp_type) अणु
			हाल IB_QPT_RC:
				hfi1_rc_hdrerr(rcd, packet, qp);
				अवरोध;
			शेष:
				/* For now करोn't handle any other QP types */
				अवरोध;
			पूर्ण

			spin_unlock_irqrestore(&qp->r_lock, flags);
			rcu_पढ़ो_unlock();
		पूर्ण /* Unicast QP */
	पूर्ण /* Valid packet with TIDErr */

	/* handle "RcvTypeErr" flags */
	चयन (rte) अणु
	हाल RHF_RTE_ERROR_OP_CODE_ERR:
	अणु
		व्योम *ebuf = शून्य;
		u8 opcode;

		अगर (rhf_use_egr_bfr(packet->rhf))
			ebuf = packet->ebuf;

		अगर (!ebuf)
			जाओ drop; /* this should never happen */

		opcode = ib_bth_get_opcode(packet->ohdr);
		अगर (opcode == IB_OPCODE_CNP) अणु
			/*
			 * Only in pre-B0 h/w is the CNP_OPCODE handled
			 * via this code path.
			 */
			काष्ठा rvt_qp *qp = शून्य;
			u32 lqpn, rqpn;
			u16 rlid;
			u8 svc_type, sl, sc5;

			sc5 = hfi1_9B_get_sc5(rhdr, packet->rhf);
			sl = ibp->sc_to_sl[sc5];

			lqpn = ib_bth_get_qpn(packet->ohdr);
			rcu_पढ़ो_lock();
			qp = rvt_lookup_qpn(rdi, &ibp->rvp, lqpn);
			अगर (!qp) अणु
				rcu_पढ़ो_unlock();
				जाओ drop;
			पूर्ण

			चयन (qp->ibqp.qp_type) अणु
			हाल IB_QPT_UD:
				rlid = 0;
				rqpn = 0;
				svc_type = IB_CC_SVCTYPE_UD;
				अवरोध;
			हाल IB_QPT_UC:
				rlid = ib_get_slid(rhdr);
				rqpn = qp->remote_qpn;
				svc_type = IB_CC_SVCTYPE_UC;
				अवरोध;
			शेष:
				rcu_पढ़ो_unlock();
				जाओ drop;
			पूर्ण

			process_becn(ppd, sl, rlid, lqpn, rqpn, svc_type);
			rcu_पढ़ो_unlock();
		पूर्ण

		packet->rhf &= ~RHF_RCV_TYPE_ERR_SMASK;
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

drop:
	वापस;
पूर्ण

अटल अंतरभूत व्योम init_packet(काष्ठा hfi1_ctxtdata *rcd,
			       काष्ठा hfi1_packet *packet)
अणु
	packet->rsize = get_hdrqentsize(rcd); /* words */
	packet->maxcnt = get_hdrq_cnt(rcd) * packet->rsize; /* words */
	packet->rcd = rcd;
	packet->updegr = 0;
	packet->etail = -1;
	packet->rhf_addr = get_rhf_addr(rcd);
	packet->rhf = rhf_to_cpu(packet->rhf_addr);
	packet->rhqoff = hfi1_rcd_head(rcd);
	packet->numpkt = 0;
पूर्ण

/* We support only two types - 9B and 16B क्रम now */
अटल स्थिर hfi1_handle_cnp hfi1_handle_cnp_tbl[2] = अणु
	[HFI1_PKT_TYPE_9B] = &वापस_cnp,
	[HFI1_PKT_TYPE_16B] = &वापस_cnp_16B
पूर्ण;

/**
 * hfi1_process_ecn_slowpath - Process FECN or BECN bits
 * @qp: The packet's destination QP
 * @pkt: The packet itself.
 * @prescan: Is the caller the RXQ prescan
 *
 * Process the packet's FECN or BECN bits. By now, the packet
 * has alपढ़ोy been evaluated whether processing of those bit should
 * be करोne.
 * The signअगरicance of the @prescan argument is that अगर the caller
 * is the RXQ prescan, a CNP will be send out instead of रुकोing क्रम the
 * normal packet processing to send an ACK with BECN set (or a CNP).
 */
bool hfi1_process_ecn_slowpath(काष्ठा rvt_qp *qp, काष्ठा hfi1_packet *pkt,
			       bool prescan)
अणु
	काष्ठा hfi1_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा ib_other_headers *ohdr = pkt->ohdr;
	काष्ठा ib_grh *grh = pkt->grh;
	u32 rqpn = 0;
	u16 pkey;
	u32 rlid, slid, dlid = 0;
	u8 hdr_type, sc, svc_type, opcode;
	bool is_mcast = false, ignore_fecn = false, करो_cnp = false,
		fecn, becn;

	/* can be called from prescan */
	अगर (pkt->etype == RHF_RCV_TYPE_BYPASS) अणु
		pkey = hfi1_16B_get_pkey(pkt->hdr);
		sc = hfi1_16B_get_sc(pkt->hdr);
		dlid = hfi1_16B_get_dlid(pkt->hdr);
		slid = hfi1_16B_get_slid(pkt->hdr);
		is_mcast = hfi1_is_16B_mcast(dlid);
		opcode = ib_bth_get_opcode(ohdr);
		hdr_type = HFI1_PKT_TYPE_16B;
		fecn = hfi1_16B_get_fecn(pkt->hdr);
		becn = hfi1_16B_get_becn(pkt->hdr);
	पूर्ण अन्यथा अणु
		pkey = ib_bth_get_pkey(ohdr);
		sc = hfi1_9B_get_sc5(pkt->hdr, pkt->rhf);
		dlid = qp->ibqp.qp_type != IB_QPT_UD ? ib_get_dlid(pkt->hdr) :
			ppd->lid;
		slid = ib_get_slid(pkt->hdr);
		is_mcast = (dlid > be16_to_cpu(IB_MULTICAST_LID_BASE)) &&
			   (dlid != be16_to_cpu(IB_LID_PERMISSIVE));
		opcode = ib_bth_get_opcode(ohdr);
		hdr_type = HFI1_PKT_TYPE_9B;
		fecn = ib_bth_get_fecn(ohdr);
		becn = ib_bth_get_becn(ohdr);
	पूर्ण

	चयन (qp->ibqp.qp_type) अणु
	हाल IB_QPT_UD:
		rlid = slid;
		rqpn = ib_get_sqpn(pkt->ohdr);
		svc_type = IB_CC_SVCTYPE_UD;
		अवरोध;
	हाल IB_QPT_SMI:
	हाल IB_QPT_GSI:
		rlid = slid;
		rqpn = ib_get_sqpn(pkt->ohdr);
		svc_type = IB_CC_SVCTYPE_UD;
		अवरोध;
	हाल IB_QPT_UC:
		rlid = rdma_ah_get_dlid(&qp->remote_ah_attr);
		rqpn = qp->remote_qpn;
		svc_type = IB_CC_SVCTYPE_UC;
		अवरोध;
	हाल IB_QPT_RC:
		rlid = rdma_ah_get_dlid(&qp->remote_ah_attr);
		rqpn = qp->remote_qpn;
		svc_type = IB_CC_SVCTYPE_RC;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	ignore_fecn = is_mcast || (opcode == IB_OPCODE_CNP) ||
		(opcode == IB_OPCODE_RC_ACKNOWLEDGE);
	/*
	 * ACKNOWLEDGE packets करो not get a CNP but this will be
	 * guarded by ignore_fecn above.
	 */
	करो_cnp = prescan ||
		(opcode >= IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST &&
		 opcode <= IB_OPCODE_RC_ATOMIC_ACKNOWLEDGE) ||
		opcode == TID_OP(READ_RESP) ||
		opcode == TID_OP(ACK);

	/* Call appropriate CNP handler */
	अगर (!ignore_fecn && करो_cnp && fecn)
		hfi1_handle_cnp_tbl[hdr_type](ibp, qp, rqpn, pkey,
					      dlid, rlid, sc, grh);

	अगर (becn) अणु
		u32 lqpn = be32_to_cpu(ohdr->bth[1]) & RVT_QPN_MASK;
		u8 sl = ibp->sc_to_sl[sc];

		process_becn(ppd, sl, rlid, lqpn, rqpn, svc_type);
	पूर्ण
	वापस !ignore_fecn && fecn;
पूर्ण

काष्ठा ps_mdata अणु
	काष्ठा hfi1_ctxtdata *rcd;
	u32 rsize;
	u32 maxcnt;
	u32 ps_head;
	u32 ps_tail;
	u32 ps_seq;
पूर्ण;

अटल अंतरभूत व्योम init_ps_mdata(काष्ठा ps_mdata *mdata,
				 काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;

	mdata->rcd = rcd;
	mdata->rsize = packet->rsize;
	mdata->maxcnt = packet->maxcnt;
	mdata->ps_head = packet->rhqoff;

	अगर (get_dma_rtail_setting(rcd)) अणु
		mdata->ps_tail = get_rcvhdrtail(rcd);
		अगर (rcd->ctxt == HFI1_CTRL_CTXT)
			mdata->ps_seq = hfi1_seq_cnt(rcd);
		अन्यथा
			mdata->ps_seq = 0; /* not used with DMA_RTAIL */
	पूर्ण अन्यथा अणु
		mdata->ps_tail = 0; /* used only with DMA_RTAIL*/
		mdata->ps_seq = hfi1_seq_cnt(rcd);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक ps_करोne(काष्ठा ps_mdata *mdata, u64 rhf,
			  काष्ठा hfi1_ctxtdata *rcd)
अणु
	अगर (get_dma_rtail_setting(rcd))
		वापस mdata->ps_head == mdata->ps_tail;
	वापस mdata->ps_seq != rhf_rcv_seq(rhf);
पूर्ण

अटल अंतरभूत पूर्णांक ps_skip(काष्ठा ps_mdata *mdata, u64 rhf,
			  काष्ठा hfi1_ctxtdata *rcd)
अणु
	/*
	 * Control context can potentially receive an invalid rhf.
	 * Drop such packets.
	 */
	अगर ((rcd->ctxt == HFI1_CTRL_CTXT) && (mdata->ps_head != mdata->ps_tail))
		वापस mdata->ps_seq != rhf_rcv_seq(rhf);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम update_ps_mdata(काष्ठा ps_mdata *mdata,
				   काष्ठा hfi1_ctxtdata *rcd)
अणु
	mdata->ps_head += mdata->rsize;
	अगर (mdata->ps_head >= mdata->maxcnt)
		mdata->ps_head = 0;

	/* Control context must करो seq counting */
	अगर (!get_dma_rtail_setting(rcd) ||
	    rcd->ctxt == HFI1_CTRL_CTXT)
		mdata->ps_seq = hfi1_seq_incr_wrap(mdata->ps_seq);
पूर्ण

/*
 * prescan_rxq - search through the receive queue looking क्रम packets
 * containing Excplicit Congestion Notअगरications (FECNs, or BECNs).
 * When an ECN is found, process the Congestion Notअगरication, and toggle
 * it off.
 * This is declared as a macro to allow quick checking of the port to aव्योम
 * the overhead of a function call अगर not enabled.
 */
#घोषणा prescan_rxq(rcd, packet) \
	करो अणु \
		अगर (rcd->ppd->cc_prescan) \
			__prescan_rxq(packet); \
	पूर्ण जबतक (0)
अटल व्योम __prescan_rxq(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	काष्ठा ps_mdata mdata;

	init_ps_mdata(&mdata, packet);

	जबतक (1) अणु
		काष्ठा hfi1_ibport *ibp = rcd_to_iport(rcd);
		__le32 *rhf_addr = (__le32 *)rcd->rcvhdrq + mdata.ps_head +
					 packet->rcd->rhf_offset;
		काष्ठा rvt_qp *qp;
		काष्ठा ib_header *hdr;
		काष्ठा rvt_dev_info *rdi = &rcd->dd->verbs_dev.rdi;
		u64 rhf = rhf_to_cpu(rhf_addr);
		u32 etype = rhf_rcv_type(rhf), qpn, bth1;
		u8 lnh;

		अगर (ps_करोne(&mdata, rhf, rcd))
			अवरोध;

		अगर (ps_skip(&mdata, rhf, rcd))
			जाओ next;

		अगर (etype != RHF_RCV_TYPE_IB)
			जाओ next;

		packet->hdr = hfi1_get_msgheader(packet->rcd, rhf_addr);
		hdr = packet->hdr;
		lnh = ib_get_lnh(hdr);

		अगर (lnh == HFI1_LRH_BTH) अणु
			packet->ohdr = &hdr->u.oth;
			packet->grh = शून्य;
		पूर्ण अन्यथा अगर (lnh == HFI1_LRH_GRH) अणु
			packet->ohdr = &hdr->u.l.oth;
			packet->grh = &hdr->u.l.grh;
		पूर्ण अन्यथा अणु
			जाओ next; /* just in हाल */
		पूर्ण

		अगर (!hfi1_may_ecn(packet))
			जाओ next;

		bth1 = be32_to_cpu(packet->ohdr->bth[1]);
		qpn = bth1 & RVT_QPN_MASK;
		rcu_पढ़ो_lock();
		qp = rvt_lookup_qpn(rdi, &ibp->rvp, qpn);

		अगर (!qp) अणु
			rcu_पढ़ो_unlock();
			जाओ next;
		पूर्ण

		hfi1_process_ecn_slowpath(qp, packet, true);
		rcu_पढ़ो_unlock();

		/* turn off BECN, FECN */
		bth1 &= ~(IB_FECN_SMASK | IB_BECN_SMASK);
		packet->ohdr->bth[1] = cpu_to_be32(bth1);
next:
		update_ps_mdata(&mdata, rcd);
	पूर्ण
पूर्ण

अटल व्योम process_rcv_qp_work(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा rvt_qp *qp, *nqp;
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;

	/*
	 * Iterate over all QPs रुकोing to respond.
	 * The list won't change since the IRQ is only run on one CPU.
	 */
	list_क्रम_each_entry_safe(qp, nqp, &rcd->qp_रुको_list, rspरुको) अणु
		list_del_init(&qp->rspरुको);
		अगर (qp->r_flags & RVT_R_RSP_NAK) अणु
			qp->r_flags &= ~RVT_R_RSP_NAK;
			packet->qp = qp;
			hfi1_send_rc_ack(packet, 0);
		पूर्ण
		अगर (qp->r_flags & RVT_R_RSP_SEND) अणु
			अचिन्हित दीर्घ flags;

			qp->r_flags &= ~RVT_R_RSP_SEND;
			spin_lock_irqsave(&qp->s_lock, flags);
			अगर (ib_rvt_state_ops[qp->state] &
					RVT_PROCESS_OR_FLUSH_SEND)
				hfi1_schedule_send(qp);
			spin_unlock_irqrestore(&qp->s_lock, flags);
		पूर्ण
		rvt_put_qp(qp);
	पूर्ण
पूर्ण

अटल noअंतरभूत पूर्णांक max_packet_exceeded(काष्ठा hfi1_packet *packet, पूर्णांक thपढ़ो)
अणु
	अगर (thपढ़ो) अणु
		अगर ((packet->numpkt & (MAX_PKT_RECV_THREAD - 1)) == 0)
			/* allow defered processing */
			process_rcv_qp_work(packet);
		cond_resched();
		वापस RCV_PKT_OK;
	पूर्ण अन्यथा अणु
		this_cpu_inc(*packet->rcd->dd->rcv_limit);
		वापस RCV_PKT_LIMIT;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक check_max_packet(काष्ठा hfi1_packet *packet, पूर्णांक thपढ़ो)
अणु
	पूर्णांक ret = RCV_PKT_OK;

	अगर (unlikely((packet->numpkt & (MAX_PKT_RECV - 1)) == 0))
		ret = max_packet_exceeded(packet, thपढ़ो);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक skip_rcv_packet(काष्ठा hfi1_packet *packet, पूर्णांक thपढ़ो)
अणु
	पूर्णांक ret;

	packet->rcd->dd->ctx0_seq_drop++;
	/* Set up क्रम the next packet */
	packet->rhqoff += packet->rsize;
	अगर (packet->rhqoff >= packet->maxcnt)
		packet->rhqoff = 0;

	packet->numpkt++;
	ret = check_max_packet(packet, thपढ़ो);

	packet->rhf_addr = (__le32 *)packet->rcd->rcvhdrq + packet->rhqoff +
				     packet->rcd->rhf_offset;
	packet->rhf = rhf_to_cpu(packet->rhf_addr);

	वापस ret;
पूर्ण

अटल व्योम process_rcv_packet_napi(काष्ठा hfi1_packet *packet)
अणु
	packet->etype = rhf_rcv_type(packet->rhf);

	/* total length */
	packet->tlen = rhf_pkt_len(packet->rhf); /* in bytes */
	/* retrieve eager buffer details */
	packet->etail = rhf_egr_index(packet->rhf);
	packet->ebuf = get_egrbuf(packet->rcd, packet->rhf,
				  &packet->updegr);
	/*
	 * Prefetch the contents of the eager buffer.  It is
	 * OK to send a negative length to prefetch_range().
	 * The +2 is the size of the RHF.
	 */
	prefetch_range(packet->ebuf,
		       packet->tlen - ((packet->rcd->rcvhdrqentsize -
				       (rhf_hdrq_offset(packet->rhf)
					+ 2)) * 4));

	packet->rcd->rhf_rcv_function_map[packet->etype](packet);
	packet->numpkt++;

	/* Set up क्रम the next packet */
	packet->rhqoff += packet->rsize;
	अगर (packet->rhqoff >= packet->maxcnt)
		packet->rhqoff = 0;

	packet->rhf_addr = (__le32 *)packet->rcd->rcvhdrq + packet->rhqoff +
				      packet->rcd->rhf_offset;
	packet->rhf = rhf_to_cpu(packet->rhf_addr);
पूर्ण

अटल अंतरभूत पूर्णांक process_rcv_packet(काष्ठा hfi1_packet *packet, पूर्णांक thपढ़ो)
अणु
	पूर्णांक ret;

	packet->etype = rhf_rcv_type(packet->rhf);

	/* total length */
	packet->tlen = rhf_pkt_len(packet->rhf); /* in bytes */
	/* retrieve eager buffer details */
	packet->ebuf = शून्य;
	अगर (rhf_use_egr_bfr(packet->rhf)) अणु
		packet->etail = rhf_egr_index(packet->rhf);
		packet->ebuf = get_egrbuf(packet->rcd, packet->rhf,
				 &packet->updegr);
		/*
		 * Prefetch the contents of the eager buffer.  It is
		 * OK to send a negative length to prefetch_range().
		 * The +2 is the size of the RHF.
		 */
		prefetch_range(packet->ebuf,
			       packet->tlen - ((get_hdrqentsize(packet->rcd) -
					       (rhf_hdrq_offset(packet->rhf)
						+ 2)) * 4));
	पूर्ण

	/*
	 * Call a type specअगरic handler क्रम the packet. We
	 * should be able to trust that etype won't be beyond
	 * the range of valid indexes. If so something is really
	 * wrong and we can probably just let things come
	 * crashing करोwn. There is no need to eat another
	 * comparison in this perक्रमmance critical code.
	 */
	packet->rcd->rhf_rcv_function_map[packet->etype](packet);
	packet->numpkt++;

	/* Set up क्रम the next packet */
	packet->rhqoff += packet->rsize;
	अगर (packet->rhqoff >= packet->maxcnt)
		packet->rhqoff = 0;

	ret = check_max_packet(packet, thपढ़ो);

	packet->rhf_addr = (__le32 *)packet->rcd->rcvhdrq + packet->rhqoff +
				      packet->rcd->rhf_offset;
	packet->rhf = rhf_to_cpu(packet->rhf_addr);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम process_rcv_update(पूर्णांक last, काष्ठा hfi1_packet *packet)
अणु
	/*
	 * Update head regs etc., every 16 packets, अगर not last pkt,
	 * to help prevent rcvhdrq overflows, when many packets
	 * are processed and queue is nearly full.
	 * Don't request an पूर्णांकerrupt क्रम पूर्णांकermediate updates.
	 */
	अगर (!last && !(packet->numpkt & 0xf)) अणु
		update_usrhead(packet->rcd, packet->rhqoff, packet->updegr,
			       packet->etail, 0, 0);
		packet->updegr = 0;
	पूर्ण
	packet->grh = शून्य;
पूर्ण

अटल अंतरभूत व्योम finish_packet(काष्ठा hfi1_packet *packet)
अणु
	/*
	 * Nothing we need to मुक्त क्रम the packet.
	 *
	 * The only thing we need to करो is a final update and call क्रम an
	 * पूर्णांकerrupt
	 */
	update_usrhead(packet->rcd, hfi1_rcd_head(packet->rcd), packet->updegr,
		       packet->etail, rcv_पूर्णांकr_dynamic, packet->numpkt);
पूर्ण

/*
 * handle_receive_पूर्णांकerrupt_napi_fp - receive a packet
 * @rcd: the context
 * @budget: polling budget
 *
 * Called from पूर्णांकerrupt handler क्रम receive पूर्णांकerrupt.
 * This is the fast path पूर्णांकerrupt handler
 * when executing napi soft irq environment.
 */
पूर्णांक handle_receive_पूर्णांकerrupt_napi_fp(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक budget)
अणु
	काष्ठा hfi1_packet packet;

	init_packet(rcd, &packet);
	अगर (last_rcv_seq(rcd, rhf_rcv_seq(packet.rhf)))
		जाओ bail;

	जबतक (packet.numpkt < budget) अणु
		process_rcv_packet_napi(&packet);
		अगर (hfi1_seq_incr(rcd, rhf_rcv_seq(packet.rhf)))
			अवरोध;

		process_rcv_update(0, &packet);
	पूर्ण
	hfi1_set_rcd_head(rcd, packet.rhqoff);
bail:
	finish_packet(&packet);
	वापस packet.numpkt;
पूर्ण

/*
 * Handle receive पूर्णांकerrupts when using the no dma rtail option.
 */
पूर्णांक handle_receive_पूर्णांकerrupt_nodma_rtail(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक thपढ़ो)
अणु
	पूर्णांक last = RCV_PKT_OK;
	काष्ठा hfi1_packet packet;

	init_packet(rcd, &packet);
	अगर (last_rcv_seq(rcd, rhf_rcv_seq(packet.rhf))) अणु
		last = RCV_PKT_DONE;
		जाओ bail;
	पूर्ण

	prescan_rxq(rcd, &packet);

	जबतक (last == RCV_PKT_OK) अणु
		last = process_rcv_packet(&packet, thपढ़ो);
		अगर (hfi1_seq_incr(rcd, rhf_rcv_seq(packet.rhf)))
			last = RCV_PKT_DONE;
		process_rcv_update(last, &packet);
	पूर्ण
	process_rcv_qp_work(&packet);
	hfi1_set_rcd_head(rcd, packet.rhqoff);
bail:
	finish_packet(&packet);
	वापस last;
पूर्ण

पूर्णांक handle_receive_पूर्णांकerrupt_dma_rtail(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक thपढ़ो)
अणु
	u32 hdrqtail;
	पूर्णांक last = RCV_PKT_OK;
	काष्ठा hfi1_packet packet;

	init_packet(rcd, &packet);
	hdrqtail = get_rcvhdrtail(rcd);
	अगर (packet.rhqoff == hdrqtail) अणु
		last = RCV_PKT_DONE;
		जाओ bail;
	पूर्ण
	smp_rmb();  /* prevent speculative पढ़ोs of dma'ed hdrq */

	prescan_rxq(rcd, &packet);

	जबतक (last == RCV_PKT_OK) अणु
		last = process_rcv_packet(&packet, thपढ़ो);
		अगर (packet.rhqoff == hdrqtail)
			last = RCV_PKT_DONE;
		process_rcv_update(last, &packet);
	पूर्ण
	process_rcv_qp_work(&packet);
	hfi1_set_rcd_head(rcd, packet.rhqoff);
bail:
	finish_packet(&packet);
	वापस last;
पूर्ण

अटल व्योम set_all_fastpath(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *rcd)
अणु
	u16 i;

	/*
	 * For dynamically allocated kernel contexts (like vnic) चयन
	 * पूर्णांकerrupt handler only क्रम that context. Otherwise, चयन
	 * पूर्णांकerrupt handler क्रम all अटलally allocated kernel contexts.
	 */
	अगर (rcd->ctxt >= dd->first_dyn_alloc_ctxt && !rcd->is_vnic) अणु
		hfi1_rcd_get(rcd);
		hfi1_set_fast(rcd);
		hfi1_rcd_put(rcd);
		वापस;
	पूर्ण

	क्रम (i = HFI1_CTRL_CTXT + 1; i < dd->num_rcv_contexts; i++) अणु
		rcd = hfi1_rcd_get_by_index(dd, i);
		अगर (rcd && (i < dd->first_dyn_alloc_ctxt || rcd->is_vnic))
			hfi1_set_fast(rcd);
		hfi1_rcd_put(rcd);
	पूर्ण
पूर्ण

व्योम set_all_slowpath(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_ctxtdata *rcd;
	u16 i;

	/* HFI1_CTRL_CTXT must always use the slow path पूर्णांकerrupt handler */
	क्रम (i = HFI1_CTRL_CTXT + 1; i < dd->num_rcv_contexts; i++) अणु
		rcd = hfi1_rcd_get_by_index(dd, i);
		अगर (!rcd)
			जारी;
		अगर (i < dd->first_dyn_alloc_ctxt || rcd->is_vnic)
			rcd->करो_पूर्णांकerrupt = rcd->slow_handler;

		hfi1_rcd_put(rcd);
	पूर्ण
पूर्ण

अटल bool __set_armed_to_active(काष्ठा hfi1_packet *packet)
अणु
	u8 etype = rhf_rcv_type(packet->rhf);
	u8 sc = SC15_PACKET;

	अगर (etype == RHF_RCV_TYPE_IB) अणु
		काष्ठा ib_header *hdr = hfi1_get_msgheader(packet->rcd,
							   packet->rhf_addr);
		sc = hfi1_9B_get_sc5(hdr, packet->rhf);
	पूर्ण अन्यथा अगर (etype == RHF_RCV_TYPE_BYPASS) अणु
		काष्ठा hfi1_16b_header *hdr = hfi1_get_16B_header(
						packet->rcd,
						packet->rhf_addr);
		sc = hfi1_16B_get_sc(hdr);
	पूर्ण
	अगर (sc != SC15_PACKET) अणु
		पूर्णांक hwstate = driver_lstate(packet->rcd->ppd);
		काष्ठा work_काष्ठा *lsaw =
				&packet->rcd->ppd->linkstate_active_work;

		अगर (hwstate != IB_PORT_ACTIVE) अणु
			dd_dev_info(packet->rcd->dd,
				    "Unexpected link state %s\n",
				    opa_lstate_name(hwstate));
			वापस false;
		पूर्ण

		queue_work(packet->rcd->ppd->link_wq, lsaw);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * set_armed_to_active  - the fast path क्रम armed to active
 * @packet: the packet काष्ठाure
 *
 * Return true अगर packet processing needs to bail.
 */
अटल bool set_armed_to_active(काष्ठा hfi1_packet *packet)
अणु
	अगर (likely(packet->rcd->ppd->host_link_state != HLS_UP_ARMED))
		वापस false;
	वापस __set_armed_to_active(packet);
पूर्ण

/*
 * handle_receive_पूर्णांकerrupt - receive a packet
 * @rcd: the context
 *
 * Called from पूर्णांकerrupt handler क्रम errors or receive पूर्णांकerrupt.
 * This is the slow path पूर्णांकerrupt handler.
 */
पूर्णांक handle_receive_पूर्णांकerrupt(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक thपढ़ो)
अणु
	काष्ठा hfi1_devdata *dd = rcd->dd;
	u32 hdrqtail;
	पूर्णांक needset, last = RCV_PKT_OK;
	काष्ठा hfi1_packet packet;
	पूर्णांक skip_pkt = 0;

	/* Control context will always use the slow path पूर्णांकerrupt handler */
	needset = (rcd->ctxt == HFI1_CTRL_CTXT) ? 0 : 1;

	init_packet(rcd, &packet);

	अगर (!get_dma_rtail_setting(rcd)) अणु
		अगर (last_rcv_seq(rcd, rhf_rcv_seq(packet.rhf))) अणु
			last = RCV_PKT_DONE;
			जाओ bail;
		पूर्ण
		hdrqtail = 0;
	पूर्ण अन्यथा अणु
		hdrqtail = get_rcvhdrtail(rcd);
		अगर (packet.rhqoff == hdrqtail) अणु
			last = RCV_PKT_DONE;
			जाओ bail;
		पूर्ण
		smp_rmb();  /* prevent speculative पढ़ोs of dma'ed hdrq */

		/*
		 * Control context can potentially receive an invalid
		 * rhf. Drop such packets.
		 */
		अगर (rcd->ctxt == HFI1_CTRL_CTXT)
			अगर (last_rcv_seq(rcd, rhf_rcv_seq(packet.rhf)))
				skip_pkt = 1;
	पूर्ण

	prescan_rxq(rcd, &packet);

	जबतक (last == RCV_PKT_OK) अणु
		अगर (hfi1_need_drop(dd)) अणु
			/* On to the next packet */
			packet.rhqoff += packet.rsize;
			packet.rhf_addr = (__le32 *)rcd->rcvhdrq +
					  packet.rhqoff +
					  rcd->rhf_offset;
			packet.rhf = rhf_to_cpu(packet.rhf_addr);

		पूर्ण अन्यथा अगर (skip_pkt) अणु
			last = skip_rcv_packet(&packet, thपढ़ो);
			skip_pkt = 0;
		पूर्ण अन्यथा अणु
			अगर (set_armed_to_active(&packet))
				जाओ bail;
			last = process_rcv_packet(&packet, thपढ़ो);
		पूर्ण

		अगर (!get_dma_rtail_setting(rcd)) अणु
			अगर (hfi1_seq_incr(rcd, rhf_rcv_seq(packet.rhf)))
				last = RCV_PKT_DONE;
		पूर्ण अन्यथा अणु
			अगर (packet.rhqoff == hdrqtail)
				last = RCV_PKT_DONE;
			/*
			 * Control context can potentially receive an invalid
			 * rhf. Drop such packets.
			 */
			अगर (rcd->ctxt == HFI1_CTRL_CTXT) अणु
				bool lseq;

				lseq = hfi1_seq_incr(rcd,
						     rhf_rcv_seq(packet.rhf));
				अगर (!last && lseq)
					skip_pkt = 1;
			पूर्ण
		पूर्ण

		अगर (needset) अणु
			needset = false;
			set_all_fastpath(dd, rcd);
		पूर्ण
		process_rcv_update(last, &packet);
	पूर्ण

	process_rcv_qp_work(&packet);
	hfi1_set_rcd_head(rcd, packet.rhqoff);

bail:
	/*
	 * Always ग_लिखो head at end, and setup rcv पूर्णांकerrupt, even
	 * अगर no packets were processed.
	 */
	finish_packet(&packet);
	वापस last;
पूर्ण

/*
 * handle_receive_पूर्णांकerrupt_napi_sp - receive a packet
 * @rcd: the context
 * @budget: polling budget
 *
 * Called from पूर्णांकerrupt handler क्रम errors or receive पूर्णांकerrupt.
 * This is the slow path पूर्णांकerrupt handler
 * when executing napi soft irq environment.
 */
पूर्णांक handle_receive_पूर्णांकerrupt_napi_sp(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक budget)
अणु
	काष्ठा hfi1_devdata *dd = rcd->dd;
	पूर्णांक last = RCV_PKT_OK;
	bool needset = true;
	काष्ठा hfi1_packet packet;

	init_packet(rcd, &packet);
	अगर (last_rcv_seq(rcd, rhf_rcv_seq(packet.rhf)))
		जाओ bail;

	जबतक (last != RCV_PKT_DONE && packet.numpkt < budget) अणु
		अगर (hfi1_need_drop(dd)) अणु
			/* On to the next packet */
			packet.rhqoff += packet.rsize;
			packet.rhf_addr = (__le32 *)rcd->rcvhdrq +
					  packet.rhqoff +
					  rcd->rhf_offset;
			packet.rhf = rhf_to_cpu(packet.rhf_addr);

		पूर्ण अन्यथा अणु
			अगर (set_armed_to_active(&packet))
				जाओ bail;
			process_rcv_packet_napi(&packet);
		पूर्ण

		अगर (hfi1_seq_incr(rcd, rhf_rcv_seq(packet.rhf)))
			last = RCV_PKT_DONE;

		अगर (needset) अणु
			needset = false;
			set_all_fastpath(dd, rcd);
		पूर्ण

		process_rcv_update(last, &packet);
	पूर्ण

	hfi1_set_rcd_head(rcd, packet.rhqoff);

bail:
	/*
	 * Always ग_लिखो head at end, and setup rcv पूर्णांकerrupt, even
	 * अगर no packets were processed.
	 */
	finish_packet(&packet);
	वापस packet.numpkt;
पूर्ण

/*
 * We may discover in the पूर्णांकerrupt that the hardware link state has
 * changed from ARMED to ACTIVE (due to the arrival of a non-SC15 packet),
 * and we need to update the driver's notion of the link state.  We cannot
 * run set_link_state from पूर्णांकerrupt context, so we queue this function on
 * a workqueue.
 *
 * We delay the regular पूर्णांकerrupt processing until after the state changes
 * so that the link will be in the correct state by the समय any application
 * we wake up attempts to send a reply to any message it received.
 * (Subsequent receive पूर्णांकerrupts may possibly क्रमce the wakeup beक्रमe we
 * update the link state.)
 *
 * The rcd is मुक्तd in hfi1_मुक्त_ctxtdata after hfi1_postinit_cleanup invokes
 * dd->f_cleanup(dd) to disable the पूर्णांकerrupt handler and flush workqueues,
 * so we're safe from use-after-मुक्त of the rcd.
 */
व्योम receive_पूर्णांकerrupt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hfi1_pportdata *ppd = container_of(work, काष्ठा hfi1_pportdata,
						  linkstate_active_work);
	काष्ठा hfi1_devdata *dd = ppd->dd;
	काष्ठा hfi1_ctxtdata *rcd;
	u16 i;

	/* Received non-SC15 packet implies neighbor_normal */
	ppd->neighbor_normal = 1;
	set_link_state(ppd, HLS_UP_ACTIVE);

	/*
	 * Interrupt all अटलally allocated kernel contexts that could
	 * have had an पूर्णांकerrupt during स्वतः activation.
	 */
	क्रम (i = HFI1_CTRL_CTXT; i < dd->first_dyn_alloc_ctxt; i++) अणु
		rcd = hfi1_rcd_get_by_index(dd, i);
		अगर (rcd)
			क्रमce_recv_पूर्णांकr(rcd);
		hfi1_rcd_put(rcd);
	पूर्ण
पूर्ण

/*
 * Convert a given MTU size to the on-wire MAD packet क्रमागतeration.
 * Return -1 अगर the size is invalid.
 */
पूर्णांक mtu_to_क्रमागत(u32 mtu, पूर्णांक शेष_अगर_bad)
अणु
	चयन (mtu) अणु
	हाल     0: वापस OPA_MTU_0;
	हाल   256: वापस OPA_MTU_256;
	हाल   512: वापस OPA_MTU_512;
	हाल  1024: वापस OPA_MTU_1024;
	हाल  2048: वापस OPA_MTU_2048;
	हाल  4096: वापस OPA_MTU_4096;
	हाल  8192: वापस OPA_MTU_8192;
	हाल 10240: वापस OPA_MTU_10240;
	पूर्ण
	वापस शेष_अगर_bad;
पूर्ण

u16 क्रमागत_to_mtu(पूर्णांक mtu)
अणु
	चयन (mtu) अणु
	हाल OPA_MTU_0:     वापस 0;
	हाल OPA_MTU_256:   वापस 256;
	हाल OPA_MTU_512:   वापस 512;
	हाल OPA_MTU_1024:  वापस 1024;
	हाल OPA_MTU_2048:  वापस 2048;
	हाल OPA_MTU_4096:  वापस 4096;
	हाल OPA_MTU_8192:  वापस 8192;
	हाल OPA_MTU_10240: वापस 10240;
	शेष: वापस 0xffff;
	पूर्ण
पूर्ण

/*
 * set_mtu - set the MTU
 * @ppd: the per port data
 *
 * We can handle "any" incoming size, the issue here is whether we
 * need to restrict our outgoing size.  We करो not deal with what happens
 * to programs that are alपढ़ोy running when the size changes.
 */
पूर्णांक set_mtu(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	पूर्णांक i, drain, ret = 0, is_up = 0;

	ppd->ibmtu = 0;
	क्रम (i = 0; i < ppd->vls_supported; i++)
		अगर (ppd->ibmtu < dd->vld[i].mtu)
			ppd->ibmtu = dd->vld[i].mtu;
	ppd->ibmaxlen = ppd->ibmtu + lrh_max_header_bytes(ppd->dd);

	mutex_lock(&ppd->hls_lock);
	अगर (ppd->host_link_state == HLS_UP_INIT ||
	    ppd->host_link_state == HLS_UP_ARMED ||
	    ppd->host_link_state == HLS_UP_ACTIVE)
		is_up = 1;

	drain = !is_ax(dd) && is_up;

	अगर (drain)
		/*
		 * MTU is specअगरied per-VL. To ensure that no packet माला_लो
		 * stuck (due, e.g., to the MTU क्रम the packet's VL being
		 * reduced), empty the per-VL FIFOs beक्रमe adjusting MTU.
		 */
		ret = stop_drain_data_vls(dd);

	अगर (ret) अणु
		dd_dev_err(dd, "%s: cannot stop/drain VLs - refusing to change per-VL MTUs\n",
			   __func__);
		जाओ err;
	पूर्ण

	hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_MTU, 0);

	अगर (drain)
		खोलो_fill_data_vls(dd); /* reखोलो all VLs */

err:
	mutex_unlock(&ppd->hls_lock);

	वापस ret;
पूर्ण

पूर्णांक hfi1_set_lid(काष्ठा hfi1_pportdata *ppd, u32 lid, u8 lmc)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;

	ppd->lid = lid;
	ppd->lmc = lmc;
	hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_LIDLMC, 0);

	dd_dev_info(dd, "port %u: got a lid: 0x%x\n", ppd->port, lid);

	वापस 0;
पूर्ण

व्योम shutकरोwn_led_override(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;

	/*
	 * This pairs with the memory barrier in hfi1_start_led_override to
	 * ensure that we पढ़ो the correct state of LED beaconing represented
	 * by led_override_समयr_active
	 */
	smp_rmb();
	अगर (atomic_पढ़ो(&ppd->led_override_समयr_active)) अणु
		del_समयr_sync(&ppd->led_override_समयr);
		atomic_set(&ppd->led_override_समयr_active, 0);
		/* Ensure the atomic_set is visible to all CPUs */
		smp_wmb();
	पूर्ण

	/* Hand control of the LED to the DC क्रम normal operation */
	ग_लिखो_csr(dd, DCC_CFG_LED_CNTRL, 0);
पूर्ण

अटल व्योम run_led_override(काष्ठा समयr_list *t)
अणु
	काष्ठा hfi1_pportdata *ppd = from_समयr(ppd, t, led_override_समयr);
	काष्ठा hfi1_devdata *dd = ppd->dd;
	अचिन्हित दीर्घ समयout;
	पूर्णांक phase_idx;

	अगर (!(dd->flags & HFI1_INITTED))
		वापस;

	phase_idx = ppd->led_override_phase & 1;

	setextled(dd, phase_idx);

	समयout = ppd->led_override_vals[phase_idx];

	/* Set up क्रम next phase */
	ppd->led_override_phase = !ppd->led_override_phase;

	mod_समयr(&ppd->led_override_समयr, jअगरfies + समयout);
पूर्ण

/*
 * To have the LED blink in a particular pattern, provide समयon and समयoff
 * in milliseconds.
 * To turn off custom blinking and वापस to normal operation, use
 * shutकरोwn_led_override()
 */
व्योम hfi1_start_led_override(काष्ठा hfi1_pportdata *ppd, अचिन्हित पूर्णांक समयon,
			     अचिन्हित पूर्णांक समयoff)
अणु
	अगर (!(ppd->dd->flags & HFI1_INITTED))
		वापस;

	/* Convert to jअगरfies क्रम direct use in समयr */
	ppd->led_override_vals[0] = msecs_to_jअगरfies(समयoff);
	ppd->led_override_vals[1] = msecs_to_jअगरfies(समयon);

	/* Arbitrarily start from LED on phase */
	ppd->led_override_phase = 1;

	/*
	 * If the समयr has not alपढ़ोy been started, करो so. Use a "quick"
	 * समयout so the handler will be called soon to look at our request.
	 */
	अगर (!समयr_pending(&ppd->led_override_समयr)) अणु
		समयr_setup(&ppd->led_override_समयr, run_led_override, 0);
		ppd->led_override_समयr.expires = jअगरfies + 1;
		add_समयr(&ppd->led_override_समयr);
		atomic_set(&ppd->led_override_समयr_active, 1);
		/* Ensure the atomic_set is visible to all CPUs */
		smp_wmb();
	पूर्ण
पूर्ण

/**
 * hfi1_reset_device - reset the chip अगर possible
 * @unit: the device to reset
 *
 * Whether or not reset is successful, we attempt to re-initialize the chip
 * (that is, much like a driver unload/reload).  We clear the INITTED flag
 * so that the various entry poपूर्णांकs will fail until we reinitialize.  For
 * now, we only allow this अगर no user contexts are खोलो that use chip resources
 */
पूर्णांक hfi1_reset_device(पूर्णांक unit)
अणु
	पूर्णांक ret;
	काष्ठा hfi1_devdata *dd = hfi1_lookup(unit);
	काष्ठा hfi1_pportdata *ppd;
	पूर्णांक pidx;

	अगर (!dd) अणु
		ret = -ENODEV;
		जाओ bail;
	पूर्ण

	dd_dev_info(dd, "Reset on unit %u requested\n", unit);

	अगर (!dd->kregbase1 || !(dd->flags & HFI1_PRESENT)) अणु
		dd_dev_info(dd,
			    "Invalid unit number %u or not initialized or not present\n",
			    unit);
		ret = -ENXIO;
		जाओ bail;
	पूर्ण

	/* If there are any user/vnic contexts, we cannot reset */
	mutex_lock(&hfi1_mutex);
	अगर (dd->rcd)
		अगर (hfi1_stats.sps_ctxts) अणु
			mutex_unlock(&hfi1_mutex);
			ret = -EBUSY;
			जाओ bail;
		पूर्ण
	mutex_unlock(&hfi1_mutex);

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;

		shutकरोwn_led_override(ppd);
	पूर्ण
	अगर (dd->flags & HFI1_HAS_SEND_DMA)
		sdma_निकास(dd);

	hfi1_reset_cpu_counters(dd);

	ret = hfi1_init(dd, 1);

	अगर (ret)
		dd_dev_err(dd,
			   "Reinitialize unit %u after reset failed with %d\n",
			   unit, ret);
	अन्यथा
		dd_dev_info(dd, "Reinitialized unit %u after resetting\n",
			    unit);

bail:
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम hfi1_setup_ib_header(काष्ठा hfi1_packet *packet)
अणु
	packet->hdr = (काष्ठा hfi1_ib_message_header *)
			hfi1_get_msgheader(packet->rcd,
					   packet->rhf_addr);
	packet->hlen = (u8 *)packet->rhf_addr - (u8 *)packet->hdr;
पूर्ण

अटल पूर्णांक hfi1_bypass_ingress_pkt_check(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_pportdata *ppd = packet->rcd->ppd;

	/* slid and dlid cannot be 0 */
	अगर ((!packet->slid) || (!packet->dlid))
		वापस -EINVAL;

	/* Compare port lid with incoming packet dlid */
	अगर ((!(hfi1_is_16B_mcast(packet->dlid))) &&
	    (packet->dlid !=
		opa_get_lid(be32_to_cpu(OPA_LID_PERMISSIVE), 16B))) अणु
		अगर ((packet->dlid & ~((1 << ppd->lmc) - 1)) != ppd->lid)
			वापस -EINVAL;
	पूर्ण

	/* No multicast packets with SC15 */
	अगर ((hfi1_is_16B_mcast(packet->dlid)) && (packet->sc == 0xF))
		वापस -EINVAL;

	/* Packets with permissive DLID always on SC15 */
	अगर ((packet->dlid == opa_get_lid(be32_to_cpu(OPA_LID_PERMISSIVE),
					 16B)) &&
	    (packet->sc != 0xF))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक hfi1_setup_9B_packet(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ibport *ibp = rcd_to_iport(packet->rcd);
	काष्ठा ib_header *hdr;
	u8 lnh;

	hfi1_setup_ib_header(packet);
	hdr = packet->hdr;

	lnh = ib_get_lnh(hdr);
	अगर (lnh == HFI1_LRH_BTH) अणु
		packet->ohdr = &hdr->u.oth;
		packet->grh = शून्य;
	पूर्ण अन्यथा अगर (lnh == HFI1_LRH_GRH) अणु
		u32 vtf;

		packet->ohdr = &hdr->u.l.oth;
		packet->grh = &hdr->u.l.grh;
		अगर (packet->grh->next_hdr != IB_GRH_NEXT_HDR)
			जाओ drop;
		vtf = be32_to_cpu(packet->grh->version_tclass_flow);
		अगर ((vtf >> IB_GRH_VERSION_SHIFT) != IB_GRH_VERSION)
			जाओ drop;
	पूर्ण अन्यथा अणु
		जाओ drop;
	पूर्ण

	/* Query commonly used fields from packet header */
	packet->payload = packet->ebuf;
	packet->opcode = ib_bth_get_opcode(packet->ohdr);
	packet->slid = ib_get_slid(hdr);
	packet->dlid = ib_get_dlid(hdr);
	अगर (unlikely((packet->dlid >= be16_to_cpu(IB_MULTICAST_LID_BASE)) &&
		     (packet->dlid != be16_to_cpu(IB_LID_PERMISSIVE))))
		packet->dlid += opa_get_mcast_base(OPA_MCAST_NR) -
				be16_to_cpu(IB_MULTICAST_LID_BASE);
	packet->sl = ib_get_sl(hdr);
	packet->sc = hfi1_9B_get_sc5(hdr, packet->rhf);
	packet->pad = ib_bth_get_pad(packet->ohdr);
	packet->extra_byte = 0;
	packet->pkey = ib_bth_get_pkey(packet->ohdr);
	packet->migrated = ib_bth_is_migration(packet->ohdr);

	वापस 0;
drop:
	ibp->rvp.n_pkt_drops++;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hfi1_setup_bypass_packet(काष्ठा hfi1_packet *packet)
अणु
	/*
	 * Bypass packets have a dअगरferent header/payload split
	 * compared to an IB packet.
	 * Current split is set such that 16 bytes of the actual
	 * header is in the header buffer and the remining is in
	 * the eager buffer. We chose 16 since hfi1 driver only
	 * supports 16B bypass packets and we will be able to
	 * receive the entire LRH with such a split.
	 */

	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	काष्ठा hfi1_pportdata *ppd = rcd->ppd;
	काष्ठा hfi1_ibport *ibp = &ppd->ibport_data;
	u8 l4;

	packet->hdr = (काष्ठा hfi1_16b_header *)
			hfi1_get_16B_header(packet->rcd,
					    packet->rhf_addr);
	l4 = hfi1_16B_get_l4(packet->hdr);
	अगर (l4 == OPA_16B_L4_IB_LOCAL) अणु
		packet->ohdr = packet->ebuf;
		packet->grh = शून्य;
		packet->opcode = ib_bth_get_opcode(packet->ohdr);
		packet->pad = hfi1_16B_bth_get_pad(packet->ohdr);
		/* hdr_len_by_opcode alपढ़ोy has an IB LRH factored in */
		packet->hlen = hdr_len_by_opcode[packet->opcode] +
			(LRH_16B_BYTES - LRH_9B_BYTES);
		packet->migrated = opa_bth_is_migration(packet->ohdr);
	पूर्ण अन्यथा अगर (l4 == OPA_16B_L4_IB_GLOBAL) अणु
		u32 vtf;
		u8 grh_len = माप(काष्ठा ib_grh);

		packet->ohdr = packet->ebuf + grh_len;
		packet->grh = packet->ebuf;
		packet->opcode = ib_bth_get_opcode(packet->ohdr);
		packet->pad = hfi1_16B_bth_get_pad(packet->ohdr);
		/* hdr_len_by_opcode alपढ़ोy has an IB LRH factored in */
		packet->hlen = hdr_len_by_opcode[packet->opcode] +
			(LRH_16B_BYTES - LRH_9B_BYTES) + grh_len;
		packet->migrated = opa_bth_is_migration(packet->ohdr);

		अगर (packet->grh->next_hdr != IB_GRH_NEXT_HDR)
			जाओ drop;
		vtf = be32_to_cpu(packet->grh->version_tclass_flow);
		अगर ((vtf >> IB_GRH_VERSION_SHIFT) != IB_GRH_VERSION)
			जाओ drop;
	पूर्ण अन्यथा अगर (l4 == OPA_16B_L4_FM) अणु
		packet->mgmt = packet->ebuf;
		packet->ohdr = शून्य;
		packet->grh = शून्य;
		packet->opcode = IB_OPCODE_UD_SEND_ONLY;
		packet->pad = OPA_16B_L4_FM_PAD;
		packet->hlen = OPA_16B_L4_FM_HLEN;
		packet->migrated = false;
	पूर्ण अन्यथा अणु
		जाओ drop;
	पूर्ण

	/* Query commonly used fields from packet header */
	packet->payload = packet->ebuf + packet->hlen - LRH_16B_BYTES;
	packet->slid = hfi1_16B_get_slid(packet->hdr);
	packet->dlid = hfi1_16B_get_dlid(packet->hdr);
	अगर (unlikely(hfi1_is_16B_mcast(packet->dlid)))
		packet->dlid += opa_get_mcast_base(OPA_MCAST_NR) -
				opa_get_lid(opa_get_mcast_base(OPA_MCAST_NR),
					    16B);
	packet->sc = hfi1_16B_get_sc(packet->hdr);
	packet->sl = ibp->sc_to_sl[packet->sc];
	packet->extra_byte = SIZE_OF_LT;
	packet->pkey = hfi1_16B_get_pkey(packet->hdr);

	अगर (hfi1_bypass_ingress_pkt_check(packet))
		जाओ drop;

	वापस 0;
drop:
	hfi1_cdbg(PKT, "%s: packet dropped\n", __func__);
	ibp->rvp.n_pkt_drops++;
	वापस -EINVAL;
पूर्ण

अटल व्योम show_eflags_errs(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	u32 rte = rhf_rcv_type_err(packet->rhf);

	dd_dev_err(rcd->dd,
		   "receive context %d: rhf 0x%016llx, errs [ %s%s%s%s%s%s%s] rte 0x%x\n",
		   rcd->ctxt, packet->rhf,
		   packet->rhf & RHF_K_HDR_LEN_ERR ? "k_hdr_len " : "",
		   packet->rhf & RHF_DC_UNC_ERR ? "dc_unc " : "",
		   packet->rhf & RHF_DC_ERR ? "dc " : "",
		   packet->rhf & RHF_TID_ERR ? "tid " : "",
		   packet->rhf & RHF_LEN_ERR ? "len " : "",
		   packet->rhf & RHF_ECC_ERR ? "ecc " : "",
		   packet->rhf & RHF_ICRC_ERR ? "icrc " : "",
		   rte);
पूर्ण

व्योम handle_eflags(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;

	rcv_hdrerr(rcd, rcd->ppd, packet);
	अगर (rhf_err_flags(packet->rhf))
		show_eflags_errs(packet);
पूर्ण

अटल व्योम hfi1_ipoib_ib_rcv(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ibport *ibp;
	काष्ठा net_device *netdev;
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	काष्ठा napi_काष्ठा *napi = rcd->napi;
	काष्ठा sk_buff *skb;
	काष्ठा hfi1_netdev_rxq *rxq = container_of(napi,
			काष्ठा hfi1_netdev_rxq, napi);
	u32 extra_bytes;
	u32 tlen, qpnum;
	bool करो_work, करो_cnp;

	trace_hfi1_rcvhdr(packet);

	hfi1_setup_ib_header(packet);

	packet->ohdr = &((काष्ठा ib_header *)packet->hdr)->u.oth;
	packet->grh = शून्य;

	अगर (unlikely(rhf_err_flags(packet->rhf))) अणु
		handle_eflags(packet);
		वापस;
	पूर्ण

	qpnum = ib_bth_get_qpn(packet->ohdr);
	netdev = hfi1_netdev_get_data(rcd->dd, qpnum);
	अगर (!netdev)
		जाओ drop_no_nd;

	trace_input_ibhdr(rcd->dd, packet, !!(rhf_dc_info(packet->rhf)));
	trace_ctxt_rsm_hist(rcd->ctxt);

	/* handle congestion notअगरications */
	करो_work = hfi1_may_ecn(packet);
	अगर (unlikely(करो_work)) अणु
		करो_cnp = (packet->opcode != IB_OPCODE_CNP);
		(व्योम)hfi1_process_ecn_slowpath(hfi1_ipoib_priv(netdev)->qp,
						 packet, करो_cnp);
	पूर्ण

	/*
	 * We have split poपूर्णांक after last byte of DETH
	 * lets strip padding and CRC and ICRC.
	 * tlen is whole packet len so we need to
	 * subtract header size as well.
	 */
	tlen = packet->tlen;
	extra_bytes = ib_bth_get_pad(packet->ohdr) + (SIZE_OF_CRC << 2) +
			packet->hlen;
	अगर (unlikely(tlen < extra_bytes))
		जाओ drop;

	tlen -= extra_bytes;

	skb = hfi1_ipoib_prepare_skb(rxq, tlen, packet->ebuf);
	अगर (unlikely(!skb))
		जाओ drop;

	dev_sw_netstats_rx_add(netdev, skb->len);

	skb->dev = netdev;
	skb->pkt_type = PACKET_HOST;
	netअगर_receive_skb(skb);

	वापस;

drop:
	++netdev->stats.rx_dropped;
drop_no_nd:
	ibp = rcd_to_iport(packet->rcd);
	++ibp->rvp.n_pkt_drops;
पूर्ण

/*
 * The following functions are called by the पूर्णांकerrupt handler. They are type
 * specअगरic handlers क्रम each packet type.
 */
अटल व्योम process_receive_ib(काष्ठा hfi1_packet *packet)
अणु
	अगर (hfi1_setup_9B_packet(packet))
		वापस;

	अगर (unlikely(hfi1_dbg_should_fault_rx(packet)))
		वापस;

	trace_hfi1_rcvhdr(packet);

	अगर (unlikely(rhf_err_flags(packet->rhf))) अणु
		handle_eflags(packet);
		वापस;
	पूर्ण

	hfi1_ib_rcv(packet);
पूर्ण

अटल व्योम process_receive_bypass(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_devdata *dd = packet->rcd->dd;

	अगर (hfi1_setup_bypass_packet(packet))
		वापस;

	trace_hfi1_rcvhdr(packet);

	अगर (unlikely(rhf_err_flags(packet->rhf))) अणु
		handle_eflags(packet);
		वापस;
	पूर्ण

	अगर (hfi1_16B_get_l2(packet->hdr) == 0x2) अणु
		hfi1_16B_rcv(packet);
	पूर्ण अन्यथा अणु
		dd_dev_err(dd,
			   "Bypass packets other than 16B are not supported in normal operation. Dropping\n");
		incr_cntr64(&dd->sw_rcv_bypass_packet_errors);
		अगर (!(dd->err_info_rcvport.status_and_code &
		      OPA_EI_STATUS_SMASK)) अणु
			u64 *flits = packet->ebuf;

			अगर (flits && !(packet->rhf & RHF_LEN_ERR)) अणु
				dd->err_info_rcvport.packet_flit1 = flits[0];
				dd->err_info_rcvport.packet_flit2 =
					packet->tlen > माप(flits[0]) ?
					flits[1] : 0;
			पूर्ण
			dd->err_info_rcvport.status_and_code |=
				(OPA_EI_STATUS_SMASK | BAD_L2_ERR);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम process_receive_error(काष्ठा hfi1_packet *packet)
अणु
	/* KHdrHCRCErr -- KDETH packet with a bad HCRC */
	अगर (unlikely(
		 hfi1_dbg_fault_suppress_err(&packet->rcd->dd->verbs_dev) &&
		 (rhf_rcv_type_err(packet->rhf) == RHF_RCV_TYPE_ERROR ||
		  packet->rhf & RHF_DC_ERR)))
		वापस;

	hfi1_setup_ib_header(packet);
	handle_eflags(packet);

	अगर (unlikely(rhf_err_flags(packet->rhf)))
		dd_dev_err(packet->rcd->dd,
			   "Unhandled error packet received. Dropping.\n");
पूर्ण

अटल व्योम kdeth_process_expected(काष्ठा hfi1_packet *packet)
अणु
	hfi1_setup_9B_packet(packet);
	अगर (unlikely(hfi1_dbg_should_fault_rx(packet)))
		वापस;

	अगर (unlikely(rhf_err_flags(packet->rhf))) अणु
		काष्ठा hfi1_ctxtdata *rcd = packet->rcd;

		अगर (hfi1_handle_kdeth_eflags(rcd, rcd->ppd, packet))
			वापस;
	पूर्ण

	hfi1_kdeth_expected_rcv(packet);
पूर्ण

अटल व्योम kdeth_process_eager(काष्ठा hfi1_packet *packet)
अणु
	hfi1_setup_9B_packet(packet);
	अगर (unlikely(hfi1_dbg_should_fault_rx(packet)))
		वापस;

	trace_hfi1_rcvhdr(packet);
	अगर (unlikely(rhf_err_flags(packet->rhf))) अणु
		काष्ठा hfi1_ctxtdata *rcd = packet->rcd;

		show_eflags_errs(packet);
		अगर (hfi1_handle_kdeth_eflags(rcd, rcd->ppd, packet))
			वापस;
	पूर्ण

	hfi1_kdeth_eager_rcv(packet);
पूर्ण

अटल व्योम process_receive_invalid(काष्ठा hfi1_packet *packet)
अणु
	dd_dev_err(packet->rcd->dd, "Invalid packet type %d. Dropping\n",
		   rhf_rcv_type(packet->rhf));
पूर्ण

#घोषणा HFI1_RCVHDR_DUMP_MAX	5

व्योम seqfile_dump_rcd(काष्ठा seq_file *s, काष्ठा hfi1_ctxtdata *rcd)
अणु
	काष्ठा hfi1_packet packet;
	काष्ठा ps_mdata mdata;
	पूर्णांक i;

	seq_म_लिखो(s, "Rcd %u: RcvHdr cnt %u entsize %u %s ctrl 0x%08llx status 0x%08llx, head %llu tail %llu  sw head %u\n",
		   rcd->ctxt, get_hdrq_cnt(rcd), get_hdrqentsize(rcd),
		   get_dma_rtail_setting(rcd) ?
		   "dma_rtail" : "nodma_rtail",
		   पढ़ो_kctxt_csr(rcd->dd, rcd->ctxt, RCV_CTXT_CTRL),
		   पढ़ो_kctxt_csr(rcd->dd, rcd->ctxt, RCV_CTXT_STATUS),
		   पढ़ो_uctxt_csr(rcd->dd, rcd->ctxt, RCV_HDR_HEAD) &
		   RCV_HDR_HEAD_HEAD_MASK,
		   पढ़ो_uctxt_csr(rcd->dd, rcd->ctxt, RCV_HDR_TAIL),
		   rcd->head);

	init_packet(rcd, &packet);
	init_ps_mdata(&mdata, &packet);

	क्रम (i = 0; i < HFI1_RCVHDR_DUMP_MAX; i++) अणु
		__le32 *rhf_addr = (__le32 *)rcd->rcvhdrq + mdata.ps_head +
					 rcd->rhf_offset;
		काष्ठा ib_header *hdr;
		u64 rhf = rhf_to_cpu(rhf_addr);
		u32 etype = rhf_rcv_type(rhf), qpn;
		u8 opcode;
		u32 psn;
		u8 lnh;

		अगर (ps_करोne(&mdata, rhf, rcd))
			अवरोध;

		अगर (ps_skip(&mdata, rhf, rcd))
			जाओ next;

		अगर (etype > RHF_RCV_TYPE_IB)
			जाओ next;

		packet.hdr = hfi1_get_msgheader(rcd, rhf_addr);
		hdr = packet.hdr;

		lnh = be16_to_cpu(hdr->lrh[0]) & 3;

		अगर (lnh == HFI1_LRH_BTH)
			packet.ohdr = &hdr->u.oth;
		अन्यथा अगर (lnh == HFI1_LRH_GRH)
			packet.ohdr = &hdr->u.l.oth;
		अन्यथा
			जाओ next; /* just in हाल */

		opcode = (be32_to_cpu(packet.ohdr->bth[0]) >> 24);
		qpn = be32_to_cpu(packet.ohdr->bth[1]) & RVT_QPN_MASK;
		psn = mask_psn(be32_to_cpu(packet.ohdr->bth[2]));

		seq_म_लिखो(s, "\tEnt %u: opcode 0x%x, qpn 0x%x, psn 0x%x\n",
			   mdata.ps_head, opcode, qpn, psn);
next:
		update_ps_mdata(&mdata, rcd);
	पूर्ण
पूर्ण

स्थिर rhf_rcv_function_ptr normal_rhf_rcv_functions[] = अणु
	[RHF_RCV_TYPE_EXPECTED] = kdeth_process_expected,
	[RHF_RCV_TYPE_EAGER] = kdeth_process_eager,
	[RHF_RCV_TYPE_IB] = process_receive_ib,
	[RHF_RCV_TYPE_ERROR] = process_receive_error,
	[RHF_RCV_TYPE_BYPASS] = process_receive_bypass,
	[RHF_RCV_TYPE_INVALID5] = process_receive_invalid,
	[RHF_RCV_TYPE_INVALID6] = process_receive_invalid,
	[RHF_RCV_TYPE_INVALID7] = process_receive_invalid,
पूर्ण;

स्थिर rhf_rcv_function_ptr netdev_rhf_rcv_functions[] = अणु
	[RHF_RCV_TYPE_EXPECTED] = process_receive_invalid,
	[RHF_RCV_TYPE_EAGER] = process_receive_invalid,
	[RHF_RCV_TYPE_IB] = hfi1_ipoib_ib_rcv,
	[RHF_RCV_TYPE_ERROR] = process_receive_error,
	[RHF_RCV_TYPE_BYPASS] = hfi1_vnic_bypass_rcv,
	[RHF_RCV_TYPE_INVALID5] = process_receive_invalid,
	[RHF_RCV_TYPE_INVALID6] = process_receive_invalid,
	[RHF_RCV_TYPE_INVALID7] = process_receive_invalid,
पूर्ण;
