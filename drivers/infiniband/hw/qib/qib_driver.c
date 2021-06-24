<शैली गुरु>
/*
 * Copyright (c) 2013 Intel Corporation. All rights reserved.
 * Copyright (c) 2006, 2007, 2008, 2009 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
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
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/prefetch.h>

#समावेश "qib.h"

/*
 * The size has to be दीर्घer than this string, so we can append
 * board/chip inक्रमmation to it in the init code.
 */
स्थिर अक्षर ib_qib_version[] = QIB_DRIVER_VERSION "\n";

DEFINE_MUTEX(qib_mutex);	/* general driver use */

अचिन्हित qib_ibmtu;
module_param_named(ibmtu, qib_ibmtu, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ibmtu, "Set max IB MTU (0=2KB, 1=256, 2=512, ... 5=4096");

अचिन्हित qib_compat_ddr_negotiate = 1;
module_param_named(compat_ddr_negotiate, qib_compat_ddr_negotiate, uपूर्णांक,
		   S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(compat_ddr_negotiate,
		 "Attempt pre-IBTA 1.2 DDR speed negotiation");

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Intel <ibsupport@intel.com>");
MODULE_DESCRIPTION("Intel IB driver");

/*
 * QIB_PIO_MAXIBHDR is the max IB header size allowed क्रम in our
 * PIO send buffers.  This is well beyond anything currently
 * defined in the InfiniBand spec.
 */
#घोषणा QIB_PIO_MAXIBHDR 128

/*
 * QIB_MAX_PKT_RCV is the max # अगर packets processed per receive पूर्णांकerrupt.
 */
#घोषणा QIB_MAX_PKT_RECV 64

काष्ठा qlogic_ib_stats qib_stats;

काष्ठा pci_dev *qib_get_pci_dev(काष्ठा rvt_dev_info *rdi)
अणु
	काष्ठा qib_ibdev *ibdev = container_of(rdi, काष्ठा qib_ibdev, rdi);
	काष्ठा qib_devdata *dd = container_of(ibdev,
					      काष्ठा qib_devdata, verbs_dev);
	वापस dd->pcidev;
पूर्ण

/*
 * Return count of units with at least one port ACTIVE.
 */
पूर्णांक qib_count_active_units(व्योम)
अणु
	काष्ठा qib_devdata *dd;
	काष्ठा qib_pportdata *ppd;
	अचिन्हित दीर्घ index, flags;
	पूर्णांक pidx, nunits_active = 0;

	xa_lock_irqsave(&qib_dev_table, flags);
	xa_क्रम_each(&qib_dev_table, index, dd) अणु
		अगर (!(dd->flags & QIB_PRESENT) || !dd->kregbase)
			जारी;
		क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
			ppd = dd->pport + pidx;
			अगर (ppd->lid && (ppd->lflags & (QIBL_LINKINIT |
					 QIBL_LINKARMED | QIBL_LINKACTIVE))) अणु
				nunits_active++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	xa_unlock_irqrestore(&qib_dev_table, flags);
	वापस nunits_active;
पूर्ण

/*
 * Return count of all units, optionally वापस in arguments
 * the number of usable (present) units, and the number of
 * ports that are up.
 */
पूर्णांक qib_count_units(पूर्णांक *npresentp, पूर्णांक *nupp)
अणु
	पूर्णांक nunits = 0, npresent = 0, nup = 0;
	काष्ठा qib_devdata *dd;
	अचिन्हित दीर्घ index, flags;
	पूर्णांक pidx;
	काष्ठा qib_pportdata *ppd;

	xa_lock_irqsave(&qib_dev_table, flags);
	xa_क्रम_each(&qib_dev_table, index, dd) अणु
		nunits++;
		अगर ((dd->flags & QIB_PRESENT) && dd->kregbase)
			npresent++;
		क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
			ppd = dd->pport + pidx;
			अगर (ppd->lid && (ppd->lflags & (QIBL_LINKINIT |
					 QIBL_LINKARMED | QIBL_LINKACTIVE)))
				nup++;
		पूर्ण
	पूर्ण
	xa_unlock_irqrestore(&qib_dev_table, flags);

	अगर (npresentp)
		*npresentp = npresent;
	अगर (nupp)
		*nupp = nup;

	वापस nunits;
पूर्ण

/**
 * qib_रुको_linkstate - रुको क्रम an IB link state change to occur
 * @ppd: the qlogic_ib device
 * @state: the state to रुको क्रम
 * @msecs: the number of milliseconds to रुको
 *
 * रुको up to msecs milliseconds क्रम IB link state change to occur क्रम
 * now, take the easy polling route.  Currently used only by
 * qib_set_linkstate.  Returns 0 अगर state reached, otherwise
 * -ETIMEDOUT state can have multiple states set, क्रम any of several
 * transitions.
 */
पूर्णांक qib_रुको_linkstate(काष्ठा qib_pportdata *ppd, u32 state, पूर्णांक msecs)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ppd->lflags_lock, flags);
	अगर (ppd->state_wanted) अणु
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		ret = -EBUSY;
		जाओ bail;
	पूर्ण
	ppd->state_wanted = state;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	रुको_event_पूर्णांकerruptible_समयout(ppd->state_रुको,
					 (ppd->lflags & state),
					 msecs_to_jअगरfies(msecs));
	spin_lock_irqsave(&ppd->lflags_lock, flags);
	ppd->state_wanted = 0;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);

	अगर (!(ppd->lflags & state))
		ret = -ETIMEDOUT;
	अन्यथा
		ret = 0;
bail:
	वापस ret;
पूर्ण

पूर्णांक qib_set_linkstate(काष्ठा qib_pportdata *ppd, u8 newstate)
अणु
	u32 lstate;
	पूर्णांक ret;
	काष्ठा qib_devdata *dd = ppd->dd;
	अचिन्हित दीर्घ flags;

	चयन (newstate) अणु
	हाल QIB_IB_LINKDOWN_ONLY:
		dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LSTATE,
				 IB_LINKCMD_DOWN | IB_LINKINITCMD_NOP);
		/* करोn't रुको */
		ret = 0;
		जाओ bail;

	हाल QIB_IB_LINKDOWN:
		dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LSTATE,
				 IB_LINKCMD_DOWN | IB_LINKINITCMD_POLL);
		/* करोn't रुको */
		ret = 0;
		जाओ bail;

	हाल QIB_IB_LINKDOWN_SLEEP:
		dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LSTATE,
				 IB_LINKCMD_DOWN | IB_LINKINITCMD_SLEEP);
		/* करोn't रुको */
		ret = 0;
		जाओ bail;

	हाल QIB_IB_LINKDOWN_DISABLE:
		dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LSTATE,
				 IB_LINKCMD_DOWN | IB_LINKINITCMD_DISABLE);
		/* करोn't रुको */
		ret = 0;
		जाओ bail;

	हाल QIB_IB_LINKARM:
		अगर (ppd->lflags & QIBL_LINKARMED) अणु
			ret = 0;
			जाओ bail;
		पूर्ण
		अगर (!(ppd->lflags & (QIBL_LINKINIT | QIBL_LINKACTIVE))) अणु
			ret = -EINVAL;
			जाओ bail;
		पूर्ण
		/*
		 * Since the port can be ACTIVE when we ask क्रम ARMED,
		 * clear QIBL_LINKV so we can रुको क्रम a transition.
		 * If the link isn't ARMED, then something अन्यथा happened
		 * and there is no poपूर्णांक रुकोing क्रम ARMED.
		 */
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags &= ~QIBL_LINKV;
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
		dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LSTATE,
				 IB_LINKCMD_ARMED | IB_LINKINITCMD_NOP);
		lstate = QIBL_LINKV;
		अवरोध;

	हाल QIB_IB_LINKACTIVE:
		अगर (ppd->lflags & QIBL_LINKACTIVE) अणु
			ret = 0;
			जाओ bail;
		पूर्ण
		अगर (!(ppd->lflags & QIBL_LINKARMED)) अणु
			ret = -EINVAL;
			जाओ bail;
		पूर्ण
		dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LSTATE,
				 IB_LINKCMD_ACTIVE | IB_LINKINITCMD_NOP);
		lstate = QIBL_LINKACTIVE;
		अवरोध;

	शेष:
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	ret = qib_रुको_linkstate(ppd, lstate, 10);

bail:
	वापस ret;
पूर्ण

/*
 * Get address of eager buffer from it's index (allocated in chunks, not
 * contiguous).
 */
अटल अंतरभूत व्योम *qib_get_egrbuf(स्थिर काष्ठा qib_ctxtdata *rcd, u32 etail)
अणु
	स्थिर u32 chunk = etail >> rcd->rcvegrbufs_perchunk_shअगरt;
	स्थिर u32 idx =  etail & ((u32)rcd->rcvegrbufs_perchunk - 1);

	वापस rcd->rcvegrbuf[chunk] + (idx << rcd->dd->rcvegrbufsize_shअगरt);
पूर्ण

/*
 * Returns 1 अगर error was a CRC, अन्यथा 0.
 * Needed क्रम some chip's synthesized error counters.
 */
अटल u32 qib_rcv_hdrerr(काष्ठा qib_ctxtdata *rcd, काष्ठा qib_pportdata *ppd,
			  u32 ctxt, u32 eflags, u32 l, u32 etail,
			  __le32 *rhf_addr, काष्ठा qib_message_header *rhdr)
अणु
	u32 ret = 0;

	अगर (eflags & (QLOGIC_IB_RHF_H_ICRCERR | QLOGIC_IB_RHF_H_VCRCERR))
		ret = 1;
	अन्यथा अगर (eflags == QLOGIC_IB_RHF_H_TIDERR) अणु
		/* For TIDERR and RC QPs premptively schedule a NAK */
		काष्ठा ib_header *hdr = (काष्ठा ib_header *)rhdr;
		काष्ठा ib_other_headers *ohdr = शून्य;
		काष्ठा qib_ibport *ibp = &ppd->ibport_data;
		काष्ठा qib_devdata *dd = ppd->dd;
		काष्ठा rvt_dev_info *rdi = &dd->verbs_dev.rdi;
		काष्ठा rvt_qp *qp = शून्य;
		u32 tlen = qib_hdrget_length_in_bytes(rhf_addr);
		u16 lid  = be16_to_cpu(hdr->lrh[1]);
		पूर्णांक lnh = be16_to_cpu(hdr->lrh[0]) & 3;
		u32 qp_num;
		u32 opcode;
		u32 psn;
		पूर्णांक dअगरf;

		/* Sanity check packet */
		अगर (tlen < 24)
			जाओ drop;

		अगर (lid < be16_to_cpu(IB_MULTICAST_LID_BASE)) अणु
			lid &= ~((1 << ppd->lmc) - 1);
			अगर (unlikely(lid != ppd->lid))
				जाओ drop;
		पूर्ण

		/* Check क्रम GRH */
		अगर (lnh == QIB_LRH_BTH)
			ohdr = &hdr->u.oth;
		अन्यथा अगर (lnh == QIB_LRH_GRH) अणु
			u32 vtf;

			ohdr = &hdr->u.l.oth;
			अगर (hdr->u.l.grh.next_hdr != IB_GRH_NEXT_HDR)
				जाओ drop;
			vtf = be32_to_cpu(hdr->u.l.grh.version_tclass_flow);
			अगर ((vtf >> IB_GRH_VERSION_SHIFT) != IB_GRH_VERSION)
				जाओ drop;
		पूर्ण अन्यथा
			जाओ drop;

		/* Get opcode and PSN from packet */
		opcode = be32_to_cpu(ohdr->bth[0]);
		opcode >>= 24;
		psn = be32_to_cpu(ohdr->bth[2]);

		/* Get the destination QP number. */
		qp_num = be32_to_cpu(ohdr->bth[1]) & RVT_QPN_MASK;
		अगर (qp_num != QIB_MULTICAST_QPN) अणु
			पूर्णांक ruc_res;

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
			spin_lock(&qp->r_lock);

			/* Check क्रम valid receive state. */
			अगर (!(ib_rvt_state_ops[qp->state] &
			      RVT_PROCESS_RECV_OK)) अणु
				ibp->rvp.n_pkt_drops++;
				जाओ unlock;
			पूर्ण

			चयन (qp->ibqp.qp_type) अणु
			हाल IB_QPT_RC:
				ruc_res =
					qib_ruc_check_hdr(
						ibp, hdr,
						lnh == QIB_LRH_GRH,
						qp,
						be32_to_cpu(ohdr->bth[0]));
				अगर (ruc_res)
					जाओ unlock;

				/* Only deal with RDMA Writes क्रम now */
				अगर (opcode <
				    IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST) अणु
					dअगरf = qib_cmp24(psn, qp->r_psn);
					अगर (!qp->r_nak_state && dअगरf >= 0) अणु
						ibp->rvp.n_rc_seqnak++;
						qp->r_nak_state =
							IB_NAK_PSN_ERROR;
						/* Use the expected PSN. */
						qp->r_ack_psn = qp->r_psn;
						/*
						 * Wait to send the sequence
						 * NAK until all packets
						 * in the receive queue have
						 * been processed.
						 * Otherwise, we end up
						 * propagating congestion.
						 */
						अगर (list_empty(&qp->rspरुको)) अणु
							qp->r_flags |=
								RVT_R_RSP_NAK;
							rvt_get_qp(qp);
							list_add_tail(
							 &qp->rspरुको,
							 &rcd->qp_रुको_list);
						पूर्ण
					पूर्ण /* Out of sequence NAK */
				पूर्ण /* QP Request NAKs */
				अवरोध;
			हाल IB_QPT_SMI:
			हाल IB_QPT_GSI:
			हाल IB_QPT_UD:
			हाल IB_QPT_UC:
			शेष:
				/* For now करोn't handle any other QP types */
				अवरोध;
			पूर्ण

unlock:
			spin_unlock(&qp->r_lock);
			rcu_पढ़ो_unlock();
		पूर्ण /* Unicast QP */
	पूर्ण /* Valid packet with TIDErr */

drop:
	वापस ret;
पूर्ण

/*
 * qib_kreceive - receive a packet
 * @rcd: the qlogic_ib context
 * @llic: माला_लो count of good packets needed to clear lli,
 *          (used with chips that need need to track crcs क्रम lli)
 *
 * called from पूर्णांकerrupt handler क्रम errors or receive पूर्णांकerrupt
 * Returns number of CRC error packets, needed by some chips क्रम
 * local link पूर्णांकegrity tracking.   crcs are adjusted करोwn by following
 * good packets, अगर any, and count of good packets is also tracked.
 */
u32 qib_kreceive(काष्ठा qib_ctxtdata *rcd, u32 *llic, u32 *npkts)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	काष्ठा qib_pportdata *ppd = rcd->ppd;
	__le32 *rhf_addr;
	व्योम *ebuf;
	स्थिर u32 rsize = dd->rcvhdrentsize;        /* words */
	स्थिर u32 maxcnt = dd->rcvhdrcnt * rsize;   /* words */
	u32 etail = -1, l, hdrqtail;
	काष्ठा qib_message_header *hdr;
	u32 eflags, etype, tlen, i = 0, updegr = 0, crcs = 0;
	पूर्णांक last;
	u64 lval;
	काष्ठा rvt_qp *qp, *nqp;

	l = rcd->head;
	rhf_addr = (__le32 *) rcd->rcvhdrq + l + dd->rhf_offset;
	अगर (dd->flags & QIB_NODMA_RTAIL) अणु
		u32 seq = qib_hdrget_seq(rhf_addr);

		अगर (seq != rcd->seq_cnt)
			जाओ bail;
		hdrqtail = 0;
	पूर्ण अन्यथा अणु
		hdrqtail = qib_get_rcvhdrtail(rcd);
		अगर (l == hdrqtail)
			जाओ bail;
		smp_rmb();  /* prevent speculative पढ़ोs of dma'ed hdrq */
	पूर्ण

	क्रम (last = 0, i = 1; !last; i += !last) अणु
		hdr = dd->f_get_msgheader(dd, rhf_addr);
		eflags = qib_hdrget_err_flags(rhf_addr);
		etype = qib_hdrget_rcv_type(rhf_addr);
		/* total length */
		tlen = qib_hdrget_length_in_bytes(rhf_addr);
		ebuf = शून्य;
		अगर ((dd->flags & QIB_NODMA_RTAIL) ?
		    qib_hdrget_use_egr_buf(rhf_addr) :
		    (etype != RCVHQ_RCV_TYPE_EXPECTED)) अणु
			etail = qib_hdrget_index(rhf_addr);
			updegr = 1;
			अगर (tlen > माप(*hdr) ||
			    etype >= RCVHQ_RCV_TYPE_NON_KD) अणु
				ebuf = qib_get_egrbuf(rcd, etail);
				prefetch_range(ebuf, tlen - माप(*hdr));
			पूर्ण
		पूर्ण
		अगर (!eflags) अणु
			u16 lrh_len = be16_to_cpu(hdr->lrh[2]) << 2;

			अगर (lrh_len != tlen) अणु
				qib_stats.sps_lenerrs++;
				जाओ move_aदीर्घ;
			पूर्ण
		पूर्ण
		अगर (etype == RCVHQ_RCV_TYPE_NON_KD && !eflags &&
		    ebuf == शून्य &&
		    tlen > (dd->rcvhdrentsize - 2 + 1 -
				qib_hdrget_offset(rhf_addr)) << 2) अणु
			जाओ move_aदीर्घ;
		पूर्ण

		/*
		 * Both tiderr and qibhdrerr are set क्रम all plain IB
		 * packets; only qibhdrerr should be set.
		 */
		अगर (unlikely(eflags))
			crcs += qib_rcv_hdrerr(rcd, ppd, rcd->ctxt, eflags, l,
					       etail, rhf_addr, hdr);
		अन्यथा अगर (etype == RCVHQ_RCV_TYPE_NON_KD) अणु
			qib_ib_rcv(rcd, hdr, ebuf, tlen);
			अगर (crcs)
				crcs--;
			अन्यथा अगर (llic && *llic)
				--*llic;
		पूर्ण
move_aदीर्घ:
		l += rsize;
		अगर (l >= maxcnt)
			l = 0;
		अगर (i == QIB_MAX_PKT_RECV)
			last = 1;

		rhf_addr = (__le32 *) rcd->rcvhdrq + l + dd->rhf_offset;
		अगर (dd->flags & QIB_NODMA_RTAIL) अणु
			u32 seq = qib_hdrget_seq(rhf_addr);

			अगर (++rcd->seq_cnt > 13)
				rcd->seq_cnt = 1;
			अगर (seq != rcd->seq_cnt)
				last = 1;
		पूर्ण अन्यथा अगर (l == hdrqtail)
			last = 1;
		/*
		 * Update head regs etc., every 16 packets, अगर not last pkt,
		 * to help prevent rcvhdrq overflows, when many packets
		 * are processed and queue is nearly full.
		 * Don't request an पूर्णांकerrupt क्रम पूर्णांकermediate updates.
		 */
		lval = l;
		अगर (!last && !(i & 0xf)) अणु
			dd->f_update_usrhead(rcd, lval, updegr, etail, i);
			updegr = 0;
		पूर्ण
	पूर्ण

	rcd->head = l;

	/*
	 * Iterate over all QPs रुकोing to respond.
	 * The list won't change since the IRQ is only run on one CPU.
	 */
	list_क्रम_each_entry_safe(qp, nqp, &rcd->qp_रुको_list, rspरुको) अणु
		list_del_init(&qp->rspरुको);
		अगर (qp->r_flags & RVT_R_RSP_NAK) अणु
			qp->r_flags &= ~RVT_R_RSP_NAK;
			qib_send_rc_ack(qp);
		पूर्ण
		अगर (qp->r_flags & RVT_R_RSP_SEND) अणु
			अचिन्हित दीर्घ flags;

			qp->r_flags &= ~RVT_R_RSP_SEND;
			spin_lock_irqsave(&qp->s_lock, flags);
			अगर (ib_rvt_state_ops[qp->state] &
					RVT_PROCESS_OR_FLUSH_SEND)
				qib_schedule_send(qp);
			spin_unlock_irqrestore(&qp->s_lock, flags);
		पूर्ण
		rvt_put_qp(qp);
	पूर्ण

bail:
	/* Report number of packets consumed */
	अगर (npkts)
		*npkts = i;

	/*
	 * Always ग_लिखो head at end, and setup rcv पूर्णांकerrupt, even
	 * अगर no packets were processed.
	 */
	lval = (u64)rcd->head | dd->rhdrhead_पूर्णांकr_off;
	dd->f_update_usrhead(rcd, lval, updegr, etail, i);
	वापस crcs;
पूर्ण

/**
 * qib_set_mtu - set the MTU
 * @ppd: the perport data
 * @arg: the new MTU
 *
 * We can handle "any" incoming size, the issue here is whether we
 * need to restrict our outgoing size.   For now, we करोn't करो any
 * sanity checking on this, and we करोn't deal with what happens to
 * programs that are alपढ़ोy running when the size changes.
 * NOTE: changing the MTU will usually cause the IBC to go back to
 * link INIT state...
 */
पूर्णांक qib_set_mtu(काष्ठा qib_pportdata *ppd, u16 arg)
अणु
	u32 piosize;
	पूर्णांक ret, chk;

	अगर (arg != 256 && arg != 512 && arg != 1024 && arg != 2048 &&
	    arg != 4096) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	chk = ib_mtu_क्रमागत_to_पूर्णांक(qib_ibmtu);
	अगर (chk > 0 && arg > chk) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	piosize = ppd->ibmaxlen;
	ppd->ibmtu = arg;

	अगर (arg >= (piosize - QIB_PIO_MAXIBHDR)) अणु
		/* Only अगर it's not the initial value (or reset to it) */
		अगर (piosize != ppd->init_ibmaxlen) अणु
			अगर (arg > piosize && arg <= ppd->init_ibmaxlen)
				piosize = ppd->init_ibmaxlen - 2 * माप(u32);
			ppd->ibmaxlen = piosize;
		पूर्ण
	पूर्ण अन्यथा अगर ((arg + QIB_PIO_MAXIBHDR) != ppd->ibmaxlen) अणु
		piosize = arg + QIB_PIO_MAXIBHDR - 2 * माप(u32);
		ppd->ibmaxlen = piosize;
	पूर्ण

	ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_MTU, 0);

	ret = 0;

bail:
	वापस ret;
पूर्ण

पूर्णांक qib_set_lid(काष्ठा qib_pportdata *ppd, u32 lid, u8 lmc)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;

	ppd->lid = lid;
	ppd->lmc = lmc;

	dd->f_set_ib_cfg(ppd, QIB_IB_CFG_LIDLMC,
			 lid | (~((1U << lmc) - 1)) << 16);

	qib_devinfo(dd->pcidev, "IB%u:%u got a lid: 0x%x\n",
		    dd->unit, ppd->port, lid);

	वापस 0;
पूर्ण

/*
 * Following deal with the "obviously simple" task of overriding the state
 * of the LEDS, which normally indicate link physical and logical status.
 * The complications arise in dealing with dअगरferent hardware mappings
 * and the board-dependent routine being called from पूर्णांकerrupts.
 * and then there's the requirement to _flash_ them.
 */
#घोषणा LED_OVER_FREQ_SHIFT 8
#घोषणा LED_OVER_FREQ_MASK (0xFF<<LED_OVER_FREQ_SHIFT)
/* Below is "non-zero" to क्रमce override, but both actual LEDs are off */
#घोषणा LED_OVER_BOTH_OFF (8)

अटल व्योम qib_run_led_override(काष्ठा समयr_list *t)
अणु
	काष्ठा qib_pportdata *ppd = from_समयr(ppd, t,
						    led_override_समयr);
	काष्ठा qib_devdata *dd = ppd->dd;
	पूर्णांक समयoff;
	पूर्णांक ph_idx;

	अगर (!(dd->flags & QIB_INITTED))
		वापस;

	ph_idx = ppd->led_override_phase++ & 1;
	ppd->led_override = ppd->led_override_vals[ph_idx];
	समयoff = ppd->led_override_समयoff;

	dd->f_setextled(ppd, 1);
	/*
	 * करोn't re-fire the समयr अगर user asked क्रम it to be off; we let
	 * it fire one more समय after they turn it off to simplअगरy
	 */
	अगर (ppd->led_override_vals[0] || ppd->led_override_vals[1])
		mod_समयr(&ppd->led_override_समयr, jअगरfies + समयoff);
पूर्ण

व्योम qib_set_led_override(काष्ठा qib_pportdata *ppd, अचिन्हित पूर्णांक val)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	पूर्णांक समयoff, freq;

	अगर (!(dd->flags & QIB_INITTED))
		वापस;

	/* First check अगर we are blinking. If not, use 1HZ polling */
	समयoff = HZ;
	freq = (val & LED_OVER_FREQ_MASK) >> LED_OVER_FREQ_SHIFT;

	अगर (freq) अणु
		/* For blink, set each phase from one nybble of val */
		ppd->led_override_vals[0] = val & 0xF;
		ppd->led_override_vals[1] = (val >> 4) & 0xF;
		समयoff = (HZ << 4)/freq;
	पूर्ण अन्यथा अणु
		/* Non-blink set both phases the same. */
		ppd->led_override_vals[0] = val & 0xF;
		ppd->led_override_vals[1] = val & 0xF;
	पूर्ण
	ppd->led_override_समयoff = समयoff;

	/*
	 * If the समयr has not alपढ़ोy been started, करो so. Use a "quick"
	 * समयout so the function will be called soon, to look at our request.
	 */
	अगर (atomic_inc_वापस(&ppd->led_override_समयr_active) == 1) अणु
		/* Need to start समयr */
		समयr_setup(&ppd->led_override_समयr, qib_run_led_override, 0);
		ppd->led_override_समयr.expires = jअगरfies + 1;
		add_समयr(&ppd->led_override_समयr);
	पूर्ण अन्यथा अणु
		अगर (ppd->led_override_vals[0] || ppd->led_override_vals[1])
			mod_समयr(&ppd->led_override_समयr, jअगरfies + 1);
		atomic_dec(&ppd->led_override_समयr_active);
	पूर्ण
पूर्ण

/**
 * qib_reset_device - reset the chip अगर possible
 * @unit: the device to reset
 *
 * Whether or not reset is successful, we attempt to re-initialize the chip
 * (that is, much like a driver unload/reload).  We clear the INITTED flag
 * so that the various entry poपूर्णांकs will fail until we reinitialize.  For
 * now, we only allow this अगर no user contexts are खोलो that use chip resources
 */
पूर्णांक qib_reset_device(पूर्णांक unit)
अणु
	पूर्णांक ret, i;
	काष्ठा qib_devdata *dd = qib_lookup(unit);
	काष्ठा qib_pportdata *ppd;
	अचिन्हित दीर्घ flags;
	पूर्णांक pidx;

	अगर (!dd) अणु
		ret = -ENODEV;
		जाओ bail;
	पूर्ण

	qib_devinfo(dd->pcidev, "Reset on unit %u requested\n", unit);

	अगर (!dd->kregbase || !(dd->flags & QIB_PRESENT)) अणु
		qib_devinfo(dd->pcidev,
			"Invalid unit number %u or not initialized or not present\n",
			unit);
		ret = -ENXIO;
		जाओ bail;
	पूर्ण

	spin_lock_irqsave(&dd->uctxt_lock, flags);
	अगर (dd->rcd)
		क्रम (i = dd->first_user_ctxt; i < dd->cfgctxts; i++) अणु
			अगर (!dd->rcd[i] || !dd->rcd[i]->cnt)
				जारी;
			spin_unlock_irqrestore(&dd->uctxt_lock, flags);
			ret = -EBUSY;
			जाओ bail;
		पूर्ण
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		अगर (atomic_पढ़ो(&ppd->led_override_समयr_active)) अणु
			/* Need to stop LED समयr, _then_ shut off LEDs */
			del_समयr_sync(&ppd->led_override_समयr);
			atomic_set(&ppd->led_override_समयr_active, 0);
		पूर्ण

		/* Shut off LEDs after we are sure समयr is not running */
		ppd->led_override = LED_OVER_BOTH_OFF;
		dd->f_setextled(ppd, 0);
		अगर (dd->flags & QIB_HAS_SEND_DMA)
			qib_tearकरोwn_sdma(ppd);
	पूर्ण

	ret = dd->f_reset(dd);
	अगर (ret == 1)
		ret = qib_init(dd, 1);
	अन्यथा
		ret = -EAGAIN;
	अगर (ret)
		qib_dev_err(dd,
			"Reinitialize unit %u after reset failed with %d\n",
			unit, ret);
	अन्यथा
		qib_devinfo(dd->pcidev,
			"Reinitialized unit %u after resetting\n",
			unit);

bail:
	वापस ret;
पूर्ण
