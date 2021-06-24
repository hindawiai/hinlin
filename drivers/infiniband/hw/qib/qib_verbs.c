<शैली गुरु>
/*
 * Copyright (c) 2012 - 2018 Intel Corporation.  All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
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

#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/utsname.h>
#समावेश <linux/rculist.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <rdma/rdma_vt.h>

#समावेश "qib.h"
#समावेश "qib_common.h"

अटल अचिन्हित पूर्णांक ib_qib_qp_table_size = 256;
module_param_named(qp_table_size, ib_qib_qp_table_size, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(qp_table_size, "QP table size");

अटल अचिन्हित पूर्णांक qib_lkey_table_size = 16;
module_param_named(lkey_table_size, qib_lkey_table_size, uपूर्णांक,
		   S_IRUGO);
MODULE_PARM_DESC(lkey_table_size,
		 "LKEY table size in bits (2^n, 1 <= n <= 23)");

अटल अचिन्हित पूर्णांक ib_qib_max_pds = 0xFFFF;
module_param_named(max_pds, ib_qib_max_pds, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_pds,
		 "Maximum number of protection domains to support");

अटल अचिन्हित पूर्णांक ib_qib_max_ahs = 0xFFFF;
module_param_named(max_ahs, ib_qib_max_ahs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_ahs, "Maximum number of address handles to support");

अचिन्हित पूर्णांक ib_qib_max_cqes = 0x2FFFF;
module_param_named(max_cqes, ib_qib_max_cqes, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_cqes,
		 "Maximum number of completion queue entries to support");

अचिन्हित पूर्णांक ib_qib_max_cqs = 0x1FFFF;
module_param_named(max_cqs, ib_qib_max_cqs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_cqs, "Maximum number of completion queues to support");

अचिन्हित पूर्णांक ib_qib_max_qp_wrs = 0x3FFF;
module_param_named(max_qp_wrs, ib_qib_max_qp_wrs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_qp_wrs, "Maximum number of QP WRs to support");

अचिन्हित पूर्णांक ib_qib_max_qps = 16384;
module_param_named(max_qps, ib_qib_max_qps, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_qps, "Maximum number of QPs to support");

अचिन्हित पूर्णांक ib_qib_max_sges = 0x60;
module_param_named(max_sges, ib_qib_max_sges, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_sges, "Maximum number of SGEs to support");

अचिन्हित पूर्णांक ib_qib_max_mcast_grps = 16384;
module_param_named(max_mcast_grps, ib_qib_max_mcast_grps, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_mcast_grps,
		 "Maximum number of multicast groups to support");

अचिन्हित पूर्णांक ib_qib_max_mcast_qp_attached = 16;
module_param_named(max_mcast_qp_attached, ib_qib_max_mcast_qp_attached,
		   uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_mcast_qp_attached,
		 "Maximum number of attached QPs to support");

अचिन्हित पूर्णांक ib_qib_max_srqs = 1024;
module_param_named(max_srqs, ib_qib_max_srqs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_srqs, "Maximum number of SRQs to support");

अचिन्हित पूर्णांक ib_qib_max_srq_sges = 128;
module_param_named(max_srq_sges, ib_qib_max_srq_sges, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_srq_sges, "Maximum number of SRQ SGEs to support");

अचिन्हित पूर्णांक ib_qib_max_srq_wrs = 0x1FFFF;
module_param_named(max_srq_wrs, ib_qib_max_srq_wrs, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_srq_wrs, "Maximum number of SRQ WRs support");

अटल अचिन्हित पूर्णांक ib_qib_disable_sma;
module_param_named(disable_sma, ib_qib_disable_sma, uपूर्णांक, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(disable_sma, "Disable the SMA");

/*
 * Translate ib_wr_opcode पूर्णांकo ib_wc_opcode.
 */
स्थिर क्रमागत ib_wc_opcode ib_qib_wc_opcode[] = अणु
	[IB_WR_RDMA_WRITE] = IB_WC_RDMA_WRITE,
	[IB_WR_RDMA_WRITE_WITH_IMM] = IB_WC_RDMA_WRITE,
	[IB_WR_SEND] = IB_WC_SEND,
	[IB_WR_SEND_WITH_IMM] = IB_WC_SEND,
	[IB_WR_RDMA_READ] = IB_WC_RDMA_READ,
	[IB_WR_ATOMIC_CMP_AND_SWP] = IB_WC_COMP_SWAP,
	[IB_WR_ATOMIC_FETCH_AND_ADD] = IB_WC_FETCH_ADD
पूर्ण;

/*
 * System image GUID.
 */
__be64 ib_qib_sys_image_guid;

/*
 * Count the number of DMA descriptors needed to send length bytes of data.
 * Don't modअगरy the qib_sge_state to get the count.
 * Return zero अगर any of the segments is not aligned.
 */
अटल u32 qib_count_sge(काष्ठा rvt_sge_state *ss, u32 length)
अणु
	काष्ठा rvt_sge *sg_list = ss->sg_list;
	काष्ठा rvt_sge sge = ss->sge;
	u8 num_sge = ss->num_sge;
	u32 ndesc = 1;  /* count the header */

	जबतक (length) अणु
		u32 len = rvt_get_sge_length(&sge, length);

		अगर (((दीर्घ) sge.vaddr & (माप(u32) - 1)) ||
		    (len != length && (len & (माप(u32) - 1)))) अणु
			ndesc = 0;
			अवरोध;
		पूर्ण
		ndesc++;
		sge.vaddr += len;
		sge.length -= len;
		sge.sge_length -= len;
		अगर (sge.sge_length == 0) अणु
			अगर (--num_sge)
				sge = *sg_list++;
		पूर्ण अन्यथा अगर (sge.length == 0 && sge.mr->lkey) अणु
			अगर (++sge.n >= RVT_SEGSZ) अणु
				अगर (++sge.m >= sge.mr->mapsz)
					अवरोध;
				sge.n = 0;
			पूर्ण
			sge.vaddr =
				sge.mr->map[sge.m]->segs[sge.n].vaddr;
			sge.length =
				sge.mr->map[sge.m]->segs[sge.n].length;
		पूर्ण
		length -= len;
	पूर्ण
	वापस ndesc;
पूर्ण

/*
 * Copy from the SGEs to the data buffer.
 */
अटल व्योम qib_copy_from_sge(व्योम *data, काष्ठा rvt_sge_state *ss, u32 length)
अणु
	काष्ठा rvt_sge *sge = &ss->sge;

	जबतक (length) अणु
		u32 len = rvt_get_sge_length(sge, length);

		स_नकल(data, sge->vaddr, len);
		sge->vaddr += len;
		sge->length -= len;
		sge->sge_length -= len;
		अगर (sge->sge_length == 0) अणु
			अगर (--ss->num_sge)
				*sge = *ss->sg_list++;
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
		data += len;
		length -= len;
	पूर्ण
पूर्ण

/**
 * qib_qp_rcv - processing an incoming packet on a QP
 * @rcd: the context poपूर्णांकer
 * @hdr: the packet header
 * @has_grh: true अगर the packet has a GRH
 * @data: the packet data
 * @tlen: the packet length
 * @qp: the QP the packet came on
 *
 * This is called from qib_ib_rcv() to process an incoming packet
 * क्रम the given QP.
 * Called at पूर्णांकerrupt level.
 */
अटल व्योम qib_qp_rcv(काष्ठा qib_ctxtdata *rcd, काष्ठा ib_header *hdr,
		       पूर्णांक has_grh, व्योम *data, u32 tlen, काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_ibport *ibp = &rcd->ppd->ibport_data;

	spin_lock(&qp->r_lock);

	/* Check क्रम valid receive state. */
	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK)) अणु
		ibp->rvp.n_pkt_drops++;
		जाओ unlock;
	पूर्ण

	चयन (qp->ibqp.qp_type) अणु
	हाल IB_QPT_SMI:
	हाल IB_QPT_GSI:
		अगर (ib_qib_disable_sma)
			अवरोध;
		fallthrough;
	हाल IB_QPT_UD:
		qib_ud_rcv(ibp, hdr, has_grh, data, tlen, qp);
		अवरोध;

	हाल IB_QPT_RC:
		qib_rc_rcv(rcd, hdr, has_grh, data, tlen, qp);
		अवरोध;

	हाल IB_QPT_UC:
		qib_uc_rcv(ibp, hdr, has_grh, data, tlen, qp);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

unlock:
	spin_unlock(&qp->r_lock);
पूर्ण

/**
 * qib_ib_rcv - process an incoming packet
 * @rcd: the context poपूर्णांकer
 * @rhdr: the header of the packet
 * @data: the packet payload
 * @tlen: the packet length
 *
 * This is called from qib_kreceive() to process an incoming packet at
 * पूर्णांकerrupt level. Tlen is the length of the header + data + CRC in bytes.
 */
व्योम qib_ib_rcv(काष्ठा qib_ctxtdata *rcd, व्योम *rhdr, व्योम *data, u32 tlen)
अणु
	काष्ठा qib_pportdata *ppd = rcd->ppd;
	काष्ठा qib_ibport *ibp = &ppd->ibport_data;
	काष्ठा ib_header *hdr = rhdr;
	काष्ठा qib_devdata *dd = ppd->dd;
	काष्ठा rvt_dev_info *rdi = &dd->verbs_dev.rdi;
	काष्ठा ib_other_headers *ohdr;
	काष्ठा rvt_qp *qp;
	u32 qp_num;
	पूर्णांक lnh;
	u8 opcode;
	u16 lid;

	/* 24 == LRH+BTH+CRC */
	अगर (unlikely(tlen < 24))
		जाओ drop;

	/* Check क्रम a valid destination LID (see ch. 7.11.1). */
	lid = be16_to_cpu(hdr->lrh[1]);
	अगर (lid < be16_to_cpu(IB_MULTICAST_LID_BASE)) अणु
		lid &= ~((1 << ppd->lmc) - 1);
		अगर (unlikely(lid != ppd->lid))
			जाओ drop;
	पूर्ण

	/* Check क्रम GRH */
	lnh = be16_to_cpu(hdr->lrh[0]) & 3;
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

	opcode = (be32_to_cpu(ohdr->bth[0]) >> 24) & 0x7f;
#अगर_घोषित CONFIG_DEBUG_FS
	rcd->opstats->stats[opcode].n_bytes += tlen;
	rcd->opstats->stats[opcode].n_packets++;
#पूर्ण_अगर

	/* Get the destination QP number. */
	qp_num = be32_to_cpu(ohdr->bth[1]) & RVT_QPN_MASK;
	अगर (qp_num == QIB_MULTICAST_QPN) अणु
		काष्ठा rvt_mcast *mcast;
		काष्ठा rvt_mcast_qp *p;

		अगर (lnh != QIB_LRH_GRH)
			जाओ drop;
		mcast = rvt_mcast_find(&ibp->rvp, &hdr->u.l.grh.dgid, lid);
		अगर (mcast == शून्य)
			जाओ drop;
		this_cpu_inc(ibp->pmastats->n_multicast_rcv);
		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(p, &mcast->qp_list, list)
			qib_qp_rcv(rcd, hdr, 1, data, tlen, p->qp);
		rcu_पढ़ो_unlock();
		/*
		 * Notअगरy rvt_multicast_detach() अगर it is रुकोing क्रम us
		 * to finish.
		 */
		अगर (atomic_dec_वापस(&mcast->refcount) <= 1)
			wake_up(&mcast->रुको);
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_lock();
		qp = rvt_lookup_qpn(rdi, &ibp->rvp, qp_num);
		अगर (!qp) अणु
			rcu_पढ़ो_unlock();
			जाओ drop;
		पूर्ण
		this_cpu_inc(ibp->pmastats->n_unicast_rcv);
		qib_qp_rcv(rcd, hdr, lnh == QIB_LRH_GRH, data, tlen, qp);
		rcu_पढ़ो_unlock();
	पूर्ण
	वापस;

drop:
	ibp->rvp.n_pkt_drops++;
पूर्ण

/*
 * This is called from a समयr to check क्रम QPs
 * which need kernel memory in order to send a packet.
 */
अटल व्योम mem_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा qib_ibdev *dev = from_समयr(dev, t, mem_समयr);
	काष्ठा list_head *list = &dev->memरुको;
	काष्ठा rvt_qp *qp = शून्य;
	काष्ठा qib_qp_priv *priv = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->rdi.pending_lock, flags);
	अगर (!list_empty(list)) अणु
		priv = list_entry(list->next, काष्ठा qib_qp_priv, ioरुको);
		qp = priv->owner;
		list_del_init(&priv->ioरुको);
		rvt_get_qp(qp);
		अगर (!list_empty(list))
			mod_समयr(&dev->mem_समयr, jअगरfies + 1);
	पूर्ण
	spin_unlock_irqrestore(&dev->rdi.pending_lock, flags);

	अगर (qp) अणु
		spin_lock_irqsave(&qp->s_lock, flags);
		अगर (qp->s_flags & RVT_S_WAIT_KMEM) अणु
			qp->s_flags &= ~RVT_S_WAIT_KMEM;
			qib_schedule_send(qp);
		पूर्ण
		spin_unlock_irqrestore(&qp->s_lock, flags);
		rvt_put_qp(qp);
	पूर्ण
पूर्ण

#अगर_घोषित __LITTLE_ENDIAN
अटल अंतरभूत u32 get_upper_bits(u32 data, u32 shअगरt)
अणु
	वापस data >> shअगरt;
पूर्ण

अटल अंतरभूत u32 set_upper_bits(u32 data, u32 shअगरt)
अणु
	वापस data << shअगरt;
पूर्ण

अटल अंतरभूत u32 clear_upper_bytes(u32 data, u32 n, u32 off)
अणु
	data <<= ((माप(u32) - n) * BITS_PER_BYTE);
	data >>= ((माप(u32) - n - off) * BITS_PER_BYTE);
	वापस data;
पूर्ण
#अन्यथा
अटल अंतरभूत u32 get_upper_bits(u32 data, u32 shअगरt)
अणु
	वापस data << shअगरt;
पूर्ण

अटल अंतरभूत u32 set_upper_bits(u32 data, u32 shअगरt)
अणु
	वापस data >> shअगरt;
पूर्ण

अटल अंतरभूत u32 clear_upper_bytes(u32 data, u32 n, u32 off)
अणु
	data >>= ((माप(u32) - n) * BITS_PER_BYTE);
	data <<= ((माप(u32) - n - off) * BITS_PER_BYTE);
	वापस data;
पूर्ण
#पूर्ण_अगर

अटल व्योम copy_io(u32 __iomem *piobuf, काष्ठा rvt_sge_state *ss,
		    u32 length, अचिन्हित flush_wc)
अणु
	u32 extra = 0;
	u32 data = 0;
	u32 last;

	जबतक (1) अणु
		u32 len = rvt_get_sge_length(&ss->sge, length);
		u32 off;

		/* If the source address is not aligned, try to align it. */
		off = (अचिन्हित दीर्घ)ss->sge.vaddr & (माप(u32) - 1);
		अगर (off) अणु
			u32 *addr = (u32 *)((अचिन्हित दीर्घ)ss->sge.vaddr &
					    ~(माप(u32) - 1));
			u32 v = get_upper_bits(*addr, off * BITS_PER_BYTE);
			u32 y;

			y = माप(u32) - off;
			अगर (len > y)
				len = y;
			अगर (len + extra >= माप(u32)) अणु
				data |= set_upper_bits(v, extra *
						       BITS_PER_BYTE);
				len = माप(u32) - extra;
				अगर (len == length) अणु
					last = data;
					अवरोध;
				पूर्ण
				__raw_ग_लिखोl(data, piobuf);
				piobuf++;
				extra = 0;
				data = 0;
			पूर्ण अन्यथा अणु
				/* Clear unused upper bytes */
				data |= clear_upper_bytes(v, len, extra);
				अगर (len == length) अणु
					last = data;
					अवरोध;
				पूर्ण
				extra += len;
			पूर्ण
		पूर्ण अन्यथा अगर (extra) अणु
			/* Source address is aligned. */
			u32 *addr = (u32 *) ss->sge.vaddr;
			पूर्णांक shअगरt = extra * BITS_PER_BYTE;
			पूर्णांक ushअगरt = 32 - shअगरt;
			u32 l = len;

			जबतक (l >= माप(u32)) अणु
				u32 v = *addr;

				data |= set_upper_bits(v, shअगरt);
				__raw_ग_लिखोl(data, piobuf);
				data = get_upper_bits(v, ushअगरt);
				piobuf++;
				addr++;
				l -= माप(u32);
			पूर्ण
			/*
			 * We still have 'extra' number of bytes leftover.
			 */
			अगर (l) अणु
				u32 v = *addr;

				अगर (l + extra >= माप(u32)) अणु
					data |= set_upper_bits(v, shअगरt);
					len -= l + extra - माप(u32);
					अगर (len == length) अणु
						last = data;
						अवरोध;
					पूर्ण
					__raw_ग_लिखोl(data, piobuf);
					piobuf++;
					extra = 0;
					data = 0;
				पूर्ण अन्यथा अणु
					/* Clear unused upper bytes */
					data |= clear_upper_bytes(v, l, extra);
					अगर (len == length) अणु
						last = data;
						अवरोध;
					पूर्ण
					extra += l;
				पूर्ण
			पूर्ण अन्यथा अगर (len == length) अणु
				last = data;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (len == length) अणु
			u32 w;

			/*
			 * Need to round up क्रम the last dword in the
			 * packet.
			 */
			w = (len + 3) >> 2;
			qib_pio_copy(piobuf, ss->sge.vaddr, w - 1);
			piobuf += w - 1;
			last = ((u32 *) ss->sge.vaddr)[w - 1];
			अवरोध;
		पूर्ण अन्यथा अणु
			u32 w = len >> 2;

			qib_pio_copy(piobuf, ss->sge.vaddr, w);
			piobuf += w;

			extra = len & (माप(u32) - 1);
			अगर (extra) अणु
				u32 v = ((u32 *) ss->sge.vaddr)[w];

				/* Clear unused upper bytes */
				data = clear_upper_bytes(v, extra, 0);
			पूर्ण
		पूर्ण
		rvt_update_sge(ss, len, false);
		length -= len;
	पूर्ण
	/* Update address beक्रमe sending packet. */
	rvt_update_sge(ss, length, false);
	अगर (flush_wc) अणु
		/* must flush early everything beक्रमe trigger word */
		qib_flush_wc();
		__raw_ग_लिखोl(last, piobuf);
		/* be sure trigger word is written */
		qib_flush_wc();
	पूर्ण अन्यथा
		__raw_ग_लिखोl(last, piobuf);
पूर्ण

अटल noअंतरभूत काष्ठा qib_verbs_txreq *__get_txreq(काष्ठा qib_ibdev *dev,
					   काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;
	काष्ठा qib_verbs_txreq *tx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->s_lock, flags);
	spin_lock(&dev->rdi.pending_lock);

	अगर (!list_empty(&dev->txreq_मुक्त)) अणु
		काष्ठा list_head *l = dev->txreq_मुक्त.next;

		list_del(l);
		spin_unlock(&dev->rdi.pending_lock);
		spin_unlock_irqrestore(&qp->s_lock, flags);
		tx = list_entry(l, काष्ठा qib_verbs_txreq, txreq.list);
	पूर्ण अन्यथा अणु
		अगर (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK &&
		    list_empty(&priv->ioरुको)) अणु
			dev->n_txरुको++;
			qp->s_flags |= RVT_S_WAIT_TX;
			list_add_tail(&priv->ioरुको, &dev->txरुको);
		पूर्ण
		qp->s_flags &= ~RVT_S_BUSY;
		spin_unlock(&dev->rdi.pending_lock);
		spin_unlock_irqrestore(&qp->s_lock, flags);
		tx = ERR_PTR(-EBUSY);
	पूर्ण
	वापस tx;
पूर्ण

अटल अंतरभूत काष्ठा qib_verbs_txreq *get_txreq(काष्ठा qib_ibdev *dev,
					 काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_verbs_txreq *tx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->rdi.pending_lock, flags);
	/* assume the list non empty */
	अगर (likely(!list_empty(&dev->txreq_मुक्त))) अणु
		काष्ठा list_head *l = dev->txreq_मुक्त.next;

		list_del(l);
		spin_unlock_irqrestore(&dev->rdi.pending_lock, flags);
		tx = list_entry(l, काष्ठा qib_verbs_txreq, txreq.list);
	पूर्ण अन्यथा अणु
		/* call slow path to get the extra lock */
		spin_unlock_irqrestore(&dev->rdi.pending_lock, flags);
		tx =  __get_txreq(dev, qp);
	पूर्ण
	वापस tx;
पूर्ण

व्योम qib_put_txreq(काष्ठा qib_verbs_txreq *tx)
अणु
	काष्ठा qib_ibdev *dev;
	काष्ठा rvt_qp *qp;
	काष्ठा qib_qp_priv *priv;
	अचिन्हित दीर्घ flags;

	qp = tx->qp;
	dev = to_idev(qp->ibqp.device);

	अगर (tx->mr) अणु
		rvt_put_mr(tx->mr);
		tx->mr = शून्य;
	पूर्ण
	अगर (tx->txreq.flags & QIB_SDMA_TXREQ_F_FREEBUF) अणु
		tx->txreq.flags &= ~QIB_SDMA_TXREQ_F_FREEBUF;
		dma_unmap_single(&dd_from_dev(dev)->pcidev->dev,
				 tx->txreq.addr, tx->hdr_dwords << 2,
				 DMA_TO_DEVICE);
		kमुक्त(tx->align_buf);
	पूर्ण

	spin_lock_irqsave(&dev->rdi.pending_lock, flags);

	/* Put काष्ठा back on मुक्त list */
	list_add(&tx->txreq.list, &dev->txreq_मुक्त);

	अगर (!list_empty(&dev->txरुको)) अणु
		/* Wake up first QP wanting a मुक्त काष्ठा */
		priv = list_entry(dev->txरुको.next, काष्ठा qib_qp_priv,
				  ioरुको);
		qp = priv->owner;
		list_del_init(&priv->ioरुको);
		rvt_get_qp(qp);
		spin_unlock_irqrestore(&dev->rdi.pending_lock, flags);

		spin_lock_irqsave(&qp->s_lock, flags);
		अगर (qp->s_flags & RVT_S_WAIT_TX) अणु
			qp->s_flags &= ~RVT_S_WAIT_TX;
			qib_schedule_send(qp);
		पूर्ण
		spin_unlock_irqrestore(&qp->s_lock, flags);

		rvt_put_qp(qp);
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&dev->rdi.pending_lock, flags);
पूर्ण

/*
 * This is called when there are send DMA descriptors that might be
 * available.
 *
 * This is called with ppd->sdma_lock held.
 */
व्योम qib_verbs_sdma_desc_avail(काष्ठा qib_pportdata *ppd, अचिन्हित avail)
अणु
	काष्ठा rvt_qp *qp;
	काष्ठा qib_qp_priv *qpp, *nqpp;
	काष्ठा rvt_qp *qps[20];
	काष्ठा qib_ibdev *dev;
	अचिन्हित i, n;

	n = 0;
	dev = &ppd->dd->verbs_dev;
	spin_lock(&dev->rdi.pending_lock);

	/* Search रुको list क्रम first QP wanting DMA descriptors. */
	list_क्रम_each_entry_safe(qpp, nqpp, &dev->dmaरुको, ioरुको) अणु
		qp = qpp->owner;
		अगर (qp->port_num != ppd->port)
			जारी;
		अगर (n == ARRAY_SIZE(qps))
			अवरोध;
		अगर (qpp->s_tx->txreq.sg_count > avail)
			अवरोध;
		avail -= qpp->s_tx->txreq.sg_count;
		list_del_init(&qpp->ioरुको);
		rvt_get_qp(qp);
		qps[n++] = qp;
	पूर्ण

	spin_unlock(&dev->rdi.pending_lock);

	क्रम (i = 0; i < n; i++) अणु
		qp = qps[i];
		spin_lock(&qp->s_lock);
		अगर (qp->s_flags & RVT_S_WAIT_DMA_DESC) अणु
			qp->s_flags &= ~RVT_S_WAIT_DMA_DESC;
			qib_schedule_send(qp);
		पूर्ण
		spin_unlock(&qp->s_lock);
		rvt_put_qp(qp);
	पूर्ण
पूर्ण

/*
 * This is called with ppd->sdma_lock held.
 */
अटल व्योम sdma_complete(काष्ठा qib_sdma_txreq *cookie, पूर्णांक status)
अणु
	काष्ठा qib_verbs_txreq *tx =
		container_of(cookie, काष्ठा qib_verbs_txreq, txreq);
	काष्ठा rvt_qp *qp = tx->qp;
	काष्ठा qib_qp_priv *priv = qp->priv;

	spin_lock(&qp->s_lock);
	अगर (tx->wqe)
		rvt_send_complete(qp, tx->wqe, IB_WC_SUCCESS);
	अन्यथा अगर (qp->ibqp.qp_type == IB_QPT_RC) अणु
		काष्ठा ib_header *hdr;

		अगर (tx->txreq.flags & QIB_SDMA_TXREQ_F_FREEBUF)
			hdr = &tx->align_buf->hdr;
		अन्यथा अणु
			काष्ठा qib_ibdev *dev = to_idev(qp->ibqp.device);

			hdr = &dev->pio_hdrs[tx->hdr_inx].hdr;
		पूर्ण
		qib_rc_send_complete(qp, hdr);
	पूर्ण
	अगर (atomic_dec_and_test(&priv->s_dma_busy)) अणु
		अगर (qp->state == IB_QPS_RESET)
			wake_up(&priv->रुको_dma);
		अन्यथा अगर (qp->s_flags & RVT_S_WAIT_DMA) अणु
			qp->s_flags &= ~RVT_S_WAIT_DMA;
			qib_schedule_send(qp);
		पूर्ण
	पूर्ण
	spin_unlock(&qp->s_lock);

	qib_put_txreq(tx);
पूर्ण

अटल पूर्णांक रुको_kmem(काष्ठा qib_ibdev *dev, काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&qp->s_lock, flags);
	अगर (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) अणु
		spin_lock(&dev->rdi.pending_lock);
		अगर (list_empty(&priv->ioरुको)) अणु
			अगर (list_empty(&dev->memरुको))
				mod_समयr(&dev->mem_समयr, jअगरfies + 1);
			qp->s_flags |= RVT_S_WAIT_KMEM;
			list_add_tail(&priv->ioरुको, &dev->memरुको);
		पूर्ण
		spin_unlock(&dev->rdi.pending_lock);
		qp->s_flags &= ~RVT_S_BUSY;
		ret = -EBUSY;
	पूर्ण
	spin_unlock_irqrestore(&qp->s_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक qib_verbs_send_dma(काष्ठा rvt_qp *qp, काष्ठा ib_header *hdr,
			      u32 hdrwords, काष्ठा rvt_sge_state *ss, u32 len,
			      u32 plen, u32 dwords)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;
	काष्ठा qib_ibdev *dev = to_idev(qp->ibqp.device);
	काष्ठा qib_devdata *dd = dd_from_dev(dev);
	काष्ठा qib_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा qib_verbs_txreq *tx;
	काष्ठा qib_pio_header *phdr;
	u32 control;
	u32 ndesc;
	पूर्णांक ret;

	tx = priv->s_tx;
	अगर (tx) अणु
		priv->s_tx = शून्य;
		/* resend previously स्थिरructed packet */
		ret = qib_sdma_verbs_send(ppd, tx->ss, tx->dwords, tx);
		जाओ bail;
	पूर्ण

	tx = get_txreq(dev, qp);
	अगर (IS_ERR(tx))
		जाओ bail_tx;

	control = dd->f_setpbc_control(ppd, plen, qp->s_srate,
				       be16_to_cpu(hdr->lrh[0]) >> 12);
	tx->qp = qp;
	tx->wqe = qp->s_wqe;
	tx->mr = qp->s_rdma_mr;
	अगर (qp->s_rdma_mr)
		qp->s_rdma_mr = शून्य;
	tx->txreq.callback = sdma_complete;
	अगर (dd->flags & QIB_HAS_SDMA_TIMEOUT)
		tx->txreq.flags = QIB_SDMA_TXREQ_F_HEADTOHOST;
	अन्यथा
		tx->txreq.flags = QIB_SDMA_TXREQ_F_INTREQ;
	अगर (plen + 1 > dd->piosize2kmax_dwords)
		tx->txreq.flags |= QIB_SDMA_TXREQ_F_USELARGEBUF;

	अगर (len) अणु
		/*
		 * Don't try to DMA अगर it takes more descriptors than
		 * the queue holds.
		 */
		ndesc = qib_count_sge(ss, len);
		अगर (ndesc >= ppd->sdma_descq_cnt)
			ndesc = 0;
	पूर्ण अन्यथा
		ndesc = 1;
	अगर (ndesc) अणु
		phdr = &dev->pio_hdrs[tx->hdr_inx];
		phdr->pbc[0] = cpu_to_le32(plen);
		phdr->pbc[1] = cpu_to_le32(control);
		स_नकल(&phdr->hdr, hdr, hdrwords << 2);
		tx->txreq.flags |= QIB_SDMA_TXREQ_F_FREEDESC;
		tx->txreq.sg_count = ndesc;
		tx->txreq.addr = dev->pio_hdrs_phys +
			tx->hdr_inx * माप(काष्ठा qib_pio_header);
		tx->hdr_dwords = hdrwords + 2; /* add PBC length */
		ret = qib_sdma_verbs_send(ppd, ss, dwords, tx);
		जाओ bail;
	पूर्ण

	/* Allocate a buffer and copy the header and payload to it. */
	tx->hdr_dwords = plen + 1;
	phdr = kदो_स्मृति(tx->hdr_dwords << 2, GFP_ATOMIC);
	अगर (!phdr)
		जाओ err_tx;
	phdr->pbc[0] = cpu_to_le32(plen);
	phdr->pbc[1] = cpu_to_le32(control);
	स_नकल(&phdr->hdr, hdr, hdrwords << 2);
	qib_copy_from_sge((u32 *) &phdr->hdr + hdrwords, ss, len);

	tx->txreq.addr = dma_map_single(&dd->pcidev->dev, phdr,
					tx->hdr_dwords << 2, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&dd->pcidev->dev, tx->txreq.addr))
		जाओ map_err;
	tx->align_buf = phdr;
	tx->txreq.flags |= QIB_SDMA_TXREQ_F_FREEBUF;
	tx->txreq.sg_count = 1;
	ret = qib_sdma_verbs_send(ppd, शून्य, 0, tx);
	जाओ unaligned;

map_err:
	kमुक्त(phdr);
err_tx:
	qib_put_txreq(tx);
	ret = रुको_kmem(dev, qp);
unaligned:
	ibp->rvp.n_unaligned++;
bail:
	वापस ret;
bail_tx:
	ret = PTR_ERR(tx);
	जाओ bail;
पूर्ण

/*
 * If we are now in the error state, वापस zero to flush the
 * send work request.
 */
अटल पूर्णांक no_bufs_available(काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_qp_priv *priv = qp->priv;
	काष्ठा qib_ibdev *dev = to_idev(qp->ibqp.device);
	काष्ठा qib_devdata *dd;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/*
	 * Note that as soon as want_buffer() is called and
	 * possibly beक्रमe it वापसs, qib_ib_piobufavail()
	 * could be called. Thereक्रमe, put QP on the I/O रुको list beक्रमe
	 * enabling the PIO avail पूर्णांकerrupt.
	 */
	spin_lock_irqsave(&qp->s_lock, flags);
	अगर (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) अणु
		spin_lock(&dev->rdi.pending_lock);
		अगर (list_empty(&priv->ioरुको)) अणु
			dev->n_pioरुको++;
			qp->s_flags |= RVT_S_WAIT_PIO;
			list_add_tail(&priv->ioरुको, &dev->pioरुको);
			dd = dd_from_dev(dev);
			dd->f_wantpiobuf_पूर्णांकr(dd, 1);
		पूर्ण
		spin_unlock(&dev->rdi.pending_lock);
		qp->s_flags &= ~RVT_S_BUSY;
		ret = -EBUSY;
	पूर्ण
	spin_unlock_irqrestore(&qp->s_lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक qib_verbs_send_pio(काष्ठा rvt_qp *qp, काष्ठा ib_header *ibhdr,
			      u32 hdrwords, काष्ठा rvt_sge_state *ss, u32 len,
			      u32 plen, u32 dwords)
अणु
	काष्ठा qib_devdata *dd = dd_from_ibdev(qp->ibqp.device);
	काष्ठा qib_pportdata *ppd = dd->pport + qp->port_num - 1;
	u32 *hdr = (u32 *) ibhdr;
	u32 __iomem *piobuf_orig;
	u32 __iomem *piobuf;
	u64 pbc;
	अचिन्हित दीर्घ flags;
	अचिन्हित flush_wc;
	u32 control;
	u32 pbufn;

	control = dd->f_setpbc_control(ppd, plen, qp->s_srate,
		be16_to_cpu(ibhdr->lrh[0]) >> 12);
	pbc = ((u64) control << 32) | plen;
	piobuf = dd->f_माला_लोendbuf(ppd, pbc, &pbufn);
	अगर (unlikely(piobuf == शून्य))
		वापस no_bufs_available(qp);

	/*
	 * Write the pbc.
	 * We have to flush after the PBC क्रम correctness on some cpus
	 * or WC buffer can be written out of order.
	 */
	ग_लिखोq(pbc, piobuf);
	piobuf_orig = piobuf;
	piobuf += 2;

	flush_wc = dd->flags & QIB_PIO_FLUSH_WC;
	अगर (len == 0) अणु
		/*
		 * If there is just the header portion, must flush beक्रमe
		 * writing last word of header क्रम correctness, and after
		 * the last header word (trigger word).
		 */
		अगर (flush_wc) अणु
			qib_flush_wc();
			qib_pio_copy(piobuf, hdr, hdrwords - 1);
			qib_flush_wc();
			__raw_ग_लिखोl(hdr[hdrwords - 1], piobuf + hdrwords - 1);
			qib_flush_wc();
		पूर्ण अन्यथा
			qib_pio_copy(piobuf, hdr, hdrwords);
		जाओ करोne;
	पूर्ण

	अगर (flush_wc)
		qib_flush_wc();
	qib_pio_copy(piobuf, hdr, hdrwords);
	piobuf += hdrwords;

	/* The common हाल is aligned and contained in one segment. */
	अगर (likely(ss->num_sge == 1 && len <= ss->sge.length &&
		   !((अचिन्हित दीर्घ)ss->sge.vaddr & (माप(u32) - 1)))) अणु
		u32 *addr = (u32 *) ss->sge.vaddr;

		/* Update address beक्रमe sending packet. */
		rvt_update_sge(ss, len, false);
		अगर (flush_wc) अणु
			qib_pio_copy(piobuf, addr, dwords - 1);
			/* must flush early everything beक्रमe trigger word */
			qib_flush_wc();
			__raw_ग_लिखोl(addr[dwords - 1], piobuf + dwords - 1);
			/* be sure trigger word is written */
			qib_flush_wc();
		पूर्ण अन्यथा
			qib_pio_copy(piobuf, addr, dwords);
		जाओ करोne;
	पूर्ण
	copy_io(piobuf, ss, len, flush_wc);
करोne:
	अगर (dd->flags & QIB_USE_SPCL_TRIG) अणु
		u32 spcl_off = (pbufn >= dd->piobcnt2k) ? 2047 : 1023;

		qib_flush_wc();
		__raw_ग_लिखोl(0xaebecede, piobuf_orig + spcl_off);
	पूर्ण
	qib_sendbuf_करोne(dd, pbufn);
	अगर (qp->s_rdma_mr) अणु
		rvt_put_mr(qp->s_rdma_mr);
		qp->s_rdma_mr = शून्य;
	पूर्ण
	अगर (qp->s_wqe) अणु
		spin_lock_irqsave(&qp->s_lock, flags);
		rvt_send_complete(qp, qp->s_wqe, IB_WC_SUCCESS);
		spin_unlock_irqrestore(&qp->s_lock, flags);
	पूर्ण अन्यथा अगर (qp->ibqp.qp_type == IB_QPT_RC) अणु
		spin_lock_irqsave(&qp->s_lock, flags);
		qib_rc_send_complete(qp, ibhdr);
		spin_unlock_irqrestore(&qp->s_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * qib_verbs_send - send a packet
 * @qp: the QP to send on
 * @hdr: the packet header
 * @hdrwords: the number of 32-bit words in the header
 * @ss: the SGE to send
 * @len: the length of the packet in bytes
 *
 * Return zero अगर packet is sent or queued OK.
 * Return non-zero and clear qp->s_flags RVT_S_BUSY otherwise.
 */
पूर्णांक qib_verbs_send(काष्ठा rvt_qp *qp, काष्ठा ib_header *hdr,
		   u32 hdrwords, काष्ठा rvt_sge_state *ss, u32 len)
अणु
	काष्ठा qib_devdata *dd = dd_from_ibdev(qp->ibqp.device);
	u32 plen;
	पूर्णांक ret;
	u32 dwords = (len + 3) >> 2;

	/*
	 * Calculate the send buffer trigger address.
	 * The +1 counts क्रम the pbc control dword following the pbc length.
	 */
	plen = hdrwords + dwords + 1;

	/*
	 * VL15 packets (IB_QPT_SMI) will always use PIO, so we
	 * can defer SDMA restart until link goes ACTIVE without
	 * worrying about just how we got there.
	 */
	अगर (qp->ibqp.qp_type == IB_QPT_SMI ||
	    !(dd->flags & QIB_HAS_SEND_DMA))
		ret = qib_verbs_send_pio(qp, hdr, hdrwords, ss, len,
					 plen, dwords);
	अन्यथा
		ret = qib_verbs_send_dma(qp, hdr, hdrwords, ss, len,
					 plen, dwords);

	वापस ret;
पूर्ण

पूर्णांक qib_snapshot_counters(काष्ठा qib_pportdata *ppd, u64 *swords,
			  u64 *rwords, u64 *spkts, u64 *rpkts,
			  u64 *xmit_रुको)
अणु
	पूर्णांक ret;
	काष्ठा qib_devdata *dd = ppd->dd;

	अगर (!(dd->flags & QIB_PRESENT)) अणु
		/* no hardware, मुक्तze, etc. */
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	*swords = dd->f_portcntr(ppd, QIBPORTCNTR_WORDSEND);
	*rwords = dd->f_portcntr(ppd, QIBPORTCNTR_WORDRCV);
	*spkts = dd->f_portcntr(ppd, QIBPORTCNTR_PKTSEND);
	*rpkts = dd->f_portcntr(ppd, QIBPORTCNTR_PKTRCV);
	*xmit_रुको = dd->f_portcntr(ppd, QIBPORTCNTR_SENDSTALL);

	ret = 0;

bail:
	वापस ret;
पूर्ण

/**
 * qib_get_counters - get various chip counters
 * @ppd: the qlogic_ib device
 * @cntrs: counters are placed here
 *
 * Return the counters needed by recv_pma_get_portcounters().
 */
पूर्णांक qib_get_counters(काष्ठा qib_pportdata *ppd,
		     काष्ठा qib_verbs_counters *cntrs)
अणु
	पूर्णांक ret;

	अगर (!(ppd->dd->flags & QIB_PRESENT)) अणु
		/* no hardware, मुक्तze, etc. */
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	cntrs->symbol_error_counter =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_IBSYMBOLERR);
	cntrs->link_error_recovery_counter =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_IBLINKERRRECOV);
	/*
	 * The link करोwned counter counts when the other side करोwns the
	 * connection.  We add in the number of बार we करोwned the link
	 * due to local link पूर्णांकegrity errors to compensate.
	 */
	cntrs->link_करोwned_counter =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_IBLINKDOWN);
	cntrs->port_rcv_errors =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_RXDROPPKT) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_RCVOVFL) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_ERR_RLEN) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_INVALIDRLEN) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_ERRLINK) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_ERRICRC) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_ERRVCRC) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_ERRLPCRC) +
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_BADFORMAT);
	cntrs->port_rcv_errors +=
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_RXLOCALPHYERR);
	cntrs->port_rcv_errors +=
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_RXVLERR);
	cntrs->port_rcv_remphys_errors =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_RCVEBP);
	cntrs->port_xmit_discards =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_UNSUPVL);
	cntrs->port_xmit_data = ppd->dd->f_portcntr(ppd,
			QIBPORTCNTR_WORDSEND);
	cntrs->port_rcv_data = ppd->dd->f_portcntr(ppd,
			QIBPORTCNTR_WORDRCV);
	cntrs->port_xmit_packets = ppd->dd->f_portcntr(ppd,
			QIBPORTCNTR_PKTSEND);
	cntrs->port_rcv_packets = ppd->dd->f_portcntr(ppd,
			QIBPORTCNTR_PKTRCV);
	cntrs->local_link_पूर्णांकegrity_errors =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_LLI);
	cntrs->excessive_buffer_overrun_errors =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_EXCESSBUFOVFL);
	cntrs->vl15_dropped =
		ppd->dd->f_portcntr(ppd, QIBPORTCNTR_VL15PKTDROP);

	ret = 0;

bail:
	वापस ret;
पूर्ण

/**
 * qib_ib_piobufavail - callback when a PIO buffer is available
 * @dd: the device poपूर्णांकer
 *
 * This is called from qib_पूर्णांकr() at पूर्णांकerrupt level when a PIO buffer is
 * available after qib_verbs_send() वापसed an error that no buffers were
 * available. Disable the पूर्णांकerrupt अगर there are no more QPs रुकोing.
 */
व्योम qib_ib_piobufavail(काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_ibdev *dev = &dd->verbs_dev;
	काष्ठा list_head *list;
	काष्ठा rvt_qp *qps[5];
	काष्ठा rvt_qp *qp;
	अचिन्हित दीर्घ flags;
	अचिन्हित i, n;
	काष्ठा qib_qp_priv *priv;

	list = &dev->pioरुको;
	n = 0;

	/*
	 * Note: checking that the pioरुको list is empty and clearing
	 * the buffer available पूर्णांकerrupt needs to be atomic or we
	 * could end up with QPs on the रुको list with the पूर्णांकerrupt
	 * disabled.
	 */
	spin_lock_irqsave(&dev->rdi.pending_lock, flags);
	जबतक (!list_empty(list)) अणु
		अगर (n == ARRAY_SIZE(qps))
			जाओ full;
		priv = list_entry(list->next, काष्ठा qib_qp_priv, ioरुको);
		qp = priv->owner;
		list_del_init(&priv->ioरुको);
		rvt_get_qp(qp);
		qps[n++] = qp;
	पूर्ण
	dd->f_wantpiobuf_पूर्णांकr(dd, 0);
full:
	spin_unlock_irqrestore(&dev->rdi.pending_lock, flags);

	क्रम (i = 0; i < n; i++) अणु
		qp = qps[i];

		spin_lock_irqsave(&qp->s_lock, flags);
		अगर (qp->s_flags & RVT_S_WAIT_PIO) अणु
			qp->s_flags &= ~RVT_S_WAIT_PIO;
			qib_schedule_send(qp);
		पूर्ण
		spin_unlock_irqrestore(&qp->s_lock, flags);

		/* Notअगरy qib_destroy_qp() अगर it is रुकोing. */
		rvt_put_qp(qp);
	पूर्ण
पूर्ण

अटल पूर्णांक qib_query_port(काष्ठा rvt_dev_info *rdi, u32 port_num,
			  काष्ठा ib_port_attr *props)
अणु
	काष्ठा qib_ibdev *ibdev = container_of(rdi, काष्ठा qib_ibdev, rdi);
	काष्ठा qib_devdata *dd = dd_from_dev(ibdev);
	काष्ठा qib_pportdata *ppd = &dd->pport[port_num - 1];
	क्रमागत ib_mtu mtu;
	u16 lid = ppd->lid;

	/* props being zeroed by the caller, aव्योम zeroing it here */
	props->lid = lid ? lid : be16_to_cpu(IB_LID_PERMISSIVE);
	props->lmc = ppd->lmc;
	props->state = dd->f_iblink_state(ppd->lastibcstat);
	props->phys_state = dd->f_ibphys_portstate(ppd->lastibcstat);
	props->gid_tbl_len = QIB_GUIDS_PER_PORT;
	props->active_width = ppd->link_width_active;
	/* See rate_show() */
	props->active_speed = ppd->link_speed_active;
	props->max_vl_num = qib_num_vls(ppd->vls_supported);

	props->max_mtu = qib_ibmtu ? qib_ibmtu : IB_MTU_4096;
	चयन (ppd->ibmtu) अणु
	हाल 4096:
		mtu = IB_MTU_4096;
		अवरोध;
	हाल 2048:
		mtu = IB_MTU_2048;
		अवरोध;
	हाल 1024:
		mtu = IB_MTU_1024;
		अवरोध;
	हाल 512:
		mtu = IB_MTU_512;
		अवरोध;
	हाल 256:
		mtu = IB_MTU_256;
		अवरोध;
	शेष:
		mtu = IB_MTU_2048;
	पूर्ण
	props->active_mtu = mtu;

	वापस 0;
पूर्ण

अटल पूर्णांक qib_modअगरy_device(काष्ठा ib_device *device,
			     पूर्णांक device_modअगरy_mask,
			     काष्ठा ib_device_modअगरy *device_modअगरy)
अणु
	काष्ठा qib_devdata *dd = dd_from_ibdev(device);
	अचिन्हित i;
	पूर्णांक ret;

	अगर (device_modअगरy_mask & ~(IB_DEVICE_MODIFY_SYS_IMAGE_GUID |
				   IB_DEVICE_MODIFY_NODE_DESC)) अणु
		ret = -EOPNOTSUPP;
		जाओ bail;
	पूर्ण

	अगर (device_modअगरy_mask & IB_DEVICE_MODIFY_NODE_DESC) अणु
		स_नकल(device->node_desc, device_modअगरy->node_desc,
		       IB_DEVICE_NODE_DESC_MAX);
		क्रम (i = 0; i < dd->num_pports; i++) अणु
			काष्ठा qib_ibport *ibp = &dd->pport[i].ibport_data;

			qib_node_desc_chg(ibp);
		पूर्ण
	पूर्ण

	अगर (device_modअगरy_mask & IB_DEVICE_MODIFY_SYS_IMAGE_GUID) अणु
		ib_qib_sys_image_guid =
			cpu_to_be64(device_modअगरy->sys_image_guid);
		क्रम (i = 0; i < dd->num_pports; i++) अणु
			काष्ठा qib_ibport *ibp = &dd->pport[i].ibport_data;

			qib_sys_guid_chg(ibp);
		पूर्ण
	पूर्ण

	ret = 0;

bail:
	वापस ret;
पूर्ण

अटल पूर्णांक qib_shut_करोwn_port(काष्ठा rvt_dev_info *rdi, u32 port_num)
अणु
	काष्ठा qib_ibdev *ibdev = container_of(rdi, काष्ठा qib_ibdev, rdi);
	काष्ठा qib_devdata *dd = dd_from_dev(ibdev);
	काष्ठा qib_pportdata *ppd = &dd->pport[port_num - 1];

	qib_set_linkstate(ppd, QIB_IB_LINKDOWN);

	वापस 0;
पूर्ण

अटल पूर्णांक qib_get_guid_be(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_ibport *rvp,
			   पूर्णांक guid_index, __be64 *guid)
अणु
	काष्ठा qib_ibport *ibp = container_of(rvp, काष्ठा qib_ibport, rvp);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);

	अगर (guid_index == 0)
		*guid = ppd->guid;
	अन्यथा अगर (guid_index < QIB_GUIDS_PER_PORT)
		*guid = ibp->guids[guid_index - 1];
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक qib_check_ah(काष्ठा ib_device *ibdev, काष्ठा rdma_ah_attr *ah_attr)
अणु
	अगर (rdma_ah_get_sl(ah_attr) > 15)
		वापस -EINVAL;

	अगर (rdma_ah_get_dlid(ah_attr) == 0)
		वापस -EINVAL;
	अगर (rdma_ah_get_dlid(ah_attr) >=
		be16_to_cpu(IB_MULTICAST_LID_BASE) &&
	    rdma_ah_get_dlid(ah_attr) !=
		be16_to_cpu(IB_LID_PERMISSIVE) &&
	    !(rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम qib_notअगरy_new_ah(काष्ठा ib_device *ibdev,
			      काष्ठा rdma_ah_attr *ah_attr,
			      काष्ठा rvt_ah *ah)
अणु
	काष्ठा qib_ibport *ibp;
	काष्ठा qib_pportdata *ppd;

	/*
	 * Do not trust पढ़ोing anything from rvt_ah at this poपूर्णांक as it is not
	 * करोne being setup. We can however modअगरy things which we need to set.
	 */

	ibp = to_iport(ibdev, rdma_ah_get_port_num(ah_attr));
	ppd = ppd_from_ibp(ibp);
	ah->vl = ibp->sl_to_vl[rdma_ah_get_sl(&ah->attr)];
	ah->log_pmtu = ilog2(ppd->ibmtu);
पूर्ण

काष्ठा ib_ah *qib_create_qp0_ah(काष्ठा qib_ibport *ibp, u16 dlid)
अणु
	काष्ठा rdma_ah_attr attr;
	काष्ठा ib_ah *ah = ERR_PTR(-EINVAL);
	काष्ठा rvt_qp *qp0;
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा qib_devdata *dd = dd_from_ppd(ppd);
	u32 port_num = ppd->port;

	स_रखो(&attr, 0, माप(attr));
	attr.type = rdma_ah_find_type(&dd->verbs_dev.rdi.ibdev, port_num);
	rdma_ah_set_dlid(&attr, dlid);
	rdma_ah_set_port_num(&attr, port_num);
	rcu_पढ़ो_lock();
	qp0 = rcu_dereference(ibp->rvp.qp[0]);
	अगर (qp0)
		ah = rdma_create_ah(qp0->ibqp.pd, &attr, 0);
	rcu_पढ़ो_unlock();
	वापस ah;
पूर्ण

/**
 * qib_get_npkeys - वापस the size of the PKEY table क्रम context 0
 * @dd: the qlogic_ib device
 */
अचिन्हित qib_get_npkeys(काष्ठा qib_devdata *dd)
अणु
	वापस ARRAY_SIZE(dd->rcd[0]->pkeys);
पूर्ण

/*
 * Return the indexed PKEY from the port PKEY table.
 * No need to validate rcd[ctxt]; the port is setup अगर we are here.
 */
अचिन्हित qib_get_pkey(काष्ठा qib_ibport *ibp, अचिन्हित index)
अणु
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा qib_devdata *dd = ppd->dd;
	अचिन्हित ctxt = ppd->hw_pidx;
	अचिन्हित ret;

	/* dd->rcd null अगर mini_init or some init failures */
	अगर (!dd->rcd || index >= ARRAY_SIZE(dd->rcd[ctxt]->pkeys))
		ret = 0;
	अन्यथा
		ret = dd->rcd[ctxt]->pkeys[index];

	वापस ret;
पूर्ण

अटल व्योम init_ibport(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_verbs_counters cntrs;
	काष्ठा qib_ibport *ibp = &ppd->ibport_data;

	spin_lock_init(&ibp->rvp.lock);
	/* Set the prefix to the शेष value (see ch. 4.1.1) */
	ibp->rvp.gid_prefix = IB_DEFAULT_GID_PREFIX;
	ibp->rvp.sm_lid = be16_to_cpu(IB_LID_PERMISSIVE);
	ibp->rvp.port_cap_flags = IB_PORT_SYS_IMAGE_GUID_SUP |
		IB_PORT_CLIENT_REG_SUP | IB_PORT_SL_MAP_SUP |
		IB_PORT_TRAP_SUP | IB_PORT_AUTO_MIGR_SUP |
		IB_PORT_DR_NOTICE_SUP | IB_PORT_CAP_MASK_NOTICE_SUP |
		IB_PORT_OTHER_LOCAL_CHANGES_SUP;
	अगर (ppd->dd->flags & QIB_HAS_LINK_LATENCY)
		ibp->rvp.port_cap_flags |= IB_PORT_LINK_LATENCY_SUP;
	ibp->rvp.pma_counter_select[0] = IB_PMA_PORT_XMIT_DATA;
	ibp->rvp.pma_counter_select[1] = IB_PMA_PORT_RCV_DATA;
	ibp->rvp.pma_counter_select[2] = IB_PMA_PORT_XMIT_PKTS;
	ibp->rvp.pma_counter_select[3] = IB_PMA_PORT_RCV_PKTS;
	ibp->rvp.pma_counter_select[4] = IB_PMA_PORT_XMIT_WAIT;

	/* Snapshot current HW counters to "clear" them. */
	qib_get_counters(ppd, &cntrs);
	ibp->z_symbol_error_counter = cntrs.symbol_error_counter;
	ibp->z_link_error_recovery_counter =
		cntrs.link_error_recovery_counter;
	ibp->z_link_करोwned_counter = cntrs.link_करोwned_counter;
	ibp->z_port_rcv_errors = cntrs.port_rcv_errors;
	ibp->z_port_rcv_remphys_errors = cntrs.port_rcv_remphys_errors;
	ibp->z_port_xmit_discards = cntrs.port_xmit_discards;
	ibp->z_port_xmit_data = cntrs.port_xmit_data;
	ibp->z_port_rcv_data = cntrs.port_rcv_data;
	ibp->z_port_xmit_packets = cntrs.port_xmit_packets;
	ibp->z_port_rcv_packets = cntrs.port_rcv_packets;
	ibp->z_local_link_पूर्णांकegrity_errors =
		cntrs.local_link_पूर्णांकegrity_errors;
	ibp->z_excessive_buffer_overrun_errors =
		cntrs.excessive_buffer_overrun_errors;
	ibp->z_vl15_dropped = cntrs.vl15_dropped;
	RCU_INIT_POINTER(ibp->rvp.qp[0], शून्य);
	RCU_INIT_POINTER(ibp->rvp.qp[1], शून्य);
पूर्ण

/**
 * qib_fill_device_attr - Fill in rvt dev info device attributes.
 * @dd: the device data काष्ठाure
 */
अटल व्योम qib_fill_device_attr(काष्ठा qib_devdata *dd)
अणु
	काष्ठा rvt_dev_info *rdi = &dd->verbs_dev.rdi;

	स_रखो(&rdi->dparms.props, 0, माप(rdi->dparms.props));

	rdi->dparms.props.max_pd = ib_qib_max_pds;
	rdi->dparms.props.max_ah = ib_qib_max_ahs;
	rdi->dparms.props.device_cap_flags = IB_DEVICE_BAD_PKEY_CNTR |
		IB_DEVICE_BAD_QKEY_CNTR | IB_DEVICE_SHUTDOWN_PORT |
		IB_DEVICE_SYS_IMAGE_GUID | IB_DEVICE_RC_RNR_NAK_GEN |
		IB_DEVICE_PORT_ACTIVE_EVENT | IB_DEVICE_SRQ_RESIZE;
	rdi->dparms.props.page_size_cap = PAGE_SIZE;
	rdi->dparms.props.venकरोr_id =
		QIB_SRC_OUI_1 << 16 | QIB_SRC_OUI_2 << 8 | QIB_SRC_OUI_3;
	rdi->dparms.props.venकरोr_part_id = dd->deviceid;
	rdi->dparms.props.hw_ver = dd->minrev;
	rdi->dparms.props.sys_image_guid = ib_qib_sys_image_guid;
	rdi->dparms.props.max_mr_size = ~0ULL;
	rdi->dparms.props.max_qp = ib_qib_max_qps;
	rdi->dparms.props.max_qp_wr = ib_qib_max_qp_wrs;
	rdi->dparms.props.max_send_sge = ib_qib_max_sges;
	rdi->dparms.props.max_recv_sge = ib_qib_max_sges;
	rdi->dparms.props.max_sge_rd = ib_qib_max_sges;
	rdi->dparms.props.max_cq = ib_qib_max_cqs;
	rdi->dparms.props.max_cqe = ib_qib_max_cqes;
	rdi->dparms.props.max_ah = ib_qib_max_ahs;
	rdi->dparms.props.max_qp_rd_atom = QIB_MAX_RDMA_ATOMIC;
	rdi->dparms.props.max_qp_init_rd_atom = 255;
	rdi->dparms.props.max_srq = ib_qib_max_srqs;
	rdi->dparms.props.max_srq_wr = ib_qib_max_srq_wrs;
	rdi->dparms.props.max_srq_sge = ib_qib_max_srq_sges;
	rdi->dparms.props.atomic_cap = IB_ATOMIC_GLOB;
	rdi->dparms.props.max_pkeys = qib_get_npkeys(dd);
	rdi->dparms.props.max_mcast_grp = ib_qib_max_mcast_grps;
	rdi->dparms.props.max_mcast_qp_attach = ib_qib_max_mcast_qp_attached;
	rdi->dparms.props.max_total_mcast_qp_attach =
					rdi->dparms.props.max_mcast_qp_attach *
					rdi->dparms.props.max_mcast_grp;
	/* post send table */
	dd->verbs_dev.rdi.post_parms = qib_post_parms;

	/* opcode translation table */
	dd->verbs_dev.rdi.wc_opcode = ib_qib_wc_opcode;
पूर्ण

अटल स्थिर काष्ठा ib_device_ops qib_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_QIB,

	.init_port = qib_create_port_files,
	.modअगरy_device = qib_modअगरy_device,
	.process_mad = qib_process_mad,
पूर्ण;

/**
 * qib_रेजिस्टर_ib_device - रेजिस्टर our device with the infiniband core
 * @dd: the device data काष्ठाure
 * Return the allocated qib_ibdev poपूर्णांकer or शून्य on error.
 */
पूर्णांक qib_रेजिस्टर_ib_device(काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_ibdev *dev = &dd->verbs_dev;
	काष्ठा ib_device *ibdev = &dev->rdi.ibdev;
	काष्ठा qib_pportdata *ppd = dd->pport;
	अचिन्हित i, ctxt;
	पूर्णांक ret;

	क्रम (i = 0; i < dd->num_pports; i++)
		init_ibport(ppd + i);

	/* Only need to initialize non-zero fields. */
	समयr_setup(&dev->mem_समयr, mem_समयr, 0);

	INIT_LIST_HEAD(&dev->pioरुको);
	INIT_LIST_HEAD(&dev->dmaरुको);
	INIT_LIST_HEAD(&dev->txरुको);
	INIT_LIST_HEAD(&dev->memरुको);
	INIT_LIST_HEAD(&dev->txreq_मुक्त);

	अगर (ppd->sdma_descq_cnt) अणु
		dev->pio_hdrs = dma_alloc_coherent(&dd->pcidev->dev,
						ppd->sdma_descq_cnt *
						माप(काष्ठा qib_pio_header),
						&dev->pio_hdrs_phys,
						GFP_KERNEL);
		अगर (!dev->pio_hdrs) अणु
			ret = -ENOMEM;
			जाओ err_hdrs;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ppd->sdma_descq_cnt; i++) अणु
		काष्ठा qib_verbs_txreq *tx;

		tx = kzalloc(माप(*tx), GFP_KERNEL);
		अगर (!tx) अणु
			ret = -ENOMEM;
			जाओ err_tx;
		पूर्ण
		tx->hdr_inx = i;
		list_add(&tx->txreq.list, &dev->txreq_मुक्त);
	पूर्ण

	/*
	 * The प्रणाली image GUID is supposed to be the same क्रम all
	 * IB HCAs in a single प्रणाली but since there can be other
	 * device types in the प्रणाली, we can't be sure this is unique.
	 */
	अगर (!ib_qib_sys_image_guid)
		ib_qib_sys_image_guid = ppd->guid;

	ibdev->node_guid = ppd->guid;
	ibdev->phys_port_cnt = dd->num_pports;
	ibdev->dev.parent = &dd->pcidev->dev;

	snम_लिखो(ibdev->node_desc, माप(ibdev->node_desc),
		 "Intel Infiniband HCA %s", init_utsname()->nodename);

	/*
	 * Fill in rvt info object.
	 */
	dd->verbs_dev.rdi.driver_f.get_pci_dev = qib_get_pci_dev;
	dd->verbs_dev.rdi.driver_f.check_ah = qib_check_ah;
	dd->verbs_dev.rdi.driver_f.setup_wqe = qib_check_send_wqe;
	dd->verbs_dev.rdi.driver_f.notअगरy_new_ah = qib_notअगरy_new_ah;
	dd->verbs_dev.rdi.driver_f.alloc_qpn = qib_alloc_qpn;
	dd->verbs_dev.rdi.driver_f.qp_priv_alloc = qib_qp_priv_alloc;
	dd->verbs_dev.rdi.driver_f.qp_priv_मुक्त = qib_qp_priv_मुक्त;
	dd->verbs_dev.rdi.driver_f.मुक्त_all_qps = qib_मुक्त_all_qps;
	dd->verbs_dev.rdi.driver_f.notअगरy_qp_reset = qib_notअगरy_qp_reset;
	dd->verbs_dev.rdi.driver_f.करो_send = qib_करो_send;
	dd->verbs_dev.rdi.driver_f.schedule_send = qib_schedule_send;
	dd->verbs_dev.rdi.driver_f.quiesce_qp = qib_quiesce_qp;
	dd->verbs_dev.rdi.driver_f.stop_send_queue = qib_stop_send_queue;
	dd->verbs_dev.rdi.driver_f.flush_qp_रुकोers = qib_flush_qp_रुकोers;
	dd->verbs_dev.rdi.driver_f.notअगरy_error_qp = qib_notअगरy_error_qp;
	dd->verbs_dev.rdi.driver_f.notअगरy_restart_rc = qib_restart_rc;
	dd->verbs_dev.rdi.driver_f.mtu_to_path_mtu = qib_mtu_to_path_mtu;
	dd->verbs_dev.rdi.driver_f.mtu_from_qp = qib_mtu_from_qp;
	dd->verbs_dev.rdi.driver_f.get_pmtu_from_attr = qib_get_pmtu_from_attr;
	dd->verbs_dev.rdi.driver_f.schedule_send_no_lock = _qib_schedule_send;
	dd->verbs_dev.rdi.driver_f.query_port_state = qib_query_port;
	dd->verbs_dev.rdi.driver_f.shut_करोwn_port = qib_shut_करोwn_port;
	dd->verbs_dev.rdi.driver_f.cap_mask_chg = qib_cap_mask_chg;
	dd->verbs_dev.rdi.driver_f.notअगरy_create_mad_agent =
						qib_notअगरy_create_mad_agent;
	dd->verbs_dev.rdi.driver_f.notअगरy_मुक्त_mad_agent =
						qib_notअगरy_मुक्त_mad_agent;

	dd->verbs_dev.rdi.dparms.max_rdma_atomic = QIB_MAX_RDMA_ATOMIC;
	dd->verbs_dev.rdi.driver_f.get_guid_be = qib_get_guid_be;
	dd->verbs_dev.rdi.dparms.lkey_table_size = qib_lkey_table_size;
	dd->verbs_dev.rdi.dparms.qp_table_size = ib_qib_qp_table_size;
	dd->verbs_dev.rdi.dparms.qpn_start = 1;
	dd->verbs_dev.rdi.dparms.qpn_res_start = QIB_KD_QP;
	dd->verbs_dev.rdi.dparms.qpn_res_end = QIB_KD_QP; /* Reserve one QP */
	dd->verbs_dev.rdi.dparms.qpn_inc = 1;
	dd->verbs_dev.rdi.dparms.qos_shअगरt = 1;
	dd->verbs_dev.rdi.dparms.psn_mask = QIB_PSN_MASK;
	dd->verbs_dev.rdi.dparms.psn_shअगरt = QIB_PSN_SHIFT;
	dd->verbs_dev.rdi.dparms.psn_modअगरy_mask = QIB_PSN_MASK;
	dd->verbs_dev.rdi.dparms.nports = dd->num_pports;
	dd->verbs_dev.rdi.dparms.npkeys = qib_get_npkeys(dd);
	dd->verbs_dev.rdi.dparms.node = dd->asचिन्हित_node_id;
	dd->verbs_dev.rdi.dparms.core_cap_flags = RDMA_CORE_PORT_IBA_IB;
	dd->verbs_dev.rdi.dparms.max_mad_size = IB_MGMT_MAD_SIZE;
	dd->verbs_dev.rdi.dparms.sge_copy_mode = RVT_SGE_COPY_MEMCPY;

	qib_fill_device_attr(dd);

	ppd = dd->pport;
	क्रम (i = 0; i < dd->num_pports; i++, ppd++) अणु
		ctxt = ppd->hw_pidx;
		rvt_init_port(&dd->verbs_dev.rdi,
			      &ppd->ibport_data.rvp,
			      i,
			      dd->rcd[ctxt]->pkeys);
	पूर्ण
	rdma_set_device_sysfs_group(&dd->verbs_dev.rdi.ibdev, &qib_attr_group);

	ib_set_device_ops(ibdev, &qib_dev_ops);
	ret = rvt_रेजिस्टर_device(&dd->verbs_dev.rdi);
	अगर (ret)
		जाओ err_tx;

	वापस ret;

err_tx:
	जबतक (!list_empty(&dev->txreq_मुक्त)) अणु
		काष्ठा list_head *l = dev->txreq_मुक्त.next;
		काष्ठा qib_verbs_txreq *tx;

		list_del(l);
		tx = list_entry(l, काष्ठा qib_verbs_txreq, txreq.list);
		kमुक्त(tx);
	पूर्ण
	अगर (ppd->sdma_descq_cnt)
		dma_मुक्त_coherent(&dd->pcidev->dev,
				  ppd->sdma_descq_cnt *
					माप(काष्ठा qib_pio_header),
				  dev->pio_hdrs, dev->pio_hdrs_phys);
err_hdrs:
	qib_dev_err(dd, "cannot register verbs: %d!\n", -ret);
	वापस ret;
पूर्ण

व्योम qib_unरेजिस्टर_ib_device(काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_ibdev *dev = &dd->verbs_dev;

	qib_verbs_unरेजिस्टर_sysfs(dd);

	rvt_unरेजिस्टर_device(&dd->verbs_dev.rdi);

	अगर (!list_empty(&dev->pioरुको))
		qib_dev_err(dd, "piowait list not empty!\n");
	अगर (!list_empty(&dev->dmaरुको))
		qib_dev_err(dd, "dmawait list not empty!\n");
	अगर (!list_empty(&dev->txरुको))
		qib_dev_err(dd, "txwait list not empty!\n");
	अगर (!list_empty(&dev->memरुको))
		qib_dev_err(dd, "memwait list not empty!\n");

	del_समयr_sync(&dev->mem_समयr);
	जबतक (!list_empty(&dev->txreq_मुक्त)) अणु
		काष्ठा list_head *l = dev->txreq_मुक्त.next;
		काष्ठा qib_verbs_txreq *tx;

		list_del(l);
		tx = list_entry(l, काष्ठा qib_verbs_txreq, txreq.list);
		kमुक्त(tx);
	पूर्ण
	अगर (dd->pport->sdma_descq_cnt)
		dma_मुक्त_coherent(&dd->pcidev->dev,
				  dd->pport->sdma_descq_cnt *
					माप(काष्ठा qib_pio_header),
				  dev->pio_hdrs, dev->pio_hdrs_phys);
पूर्ण

/**
 * _qib_schedule_send - schedule progress
 * @qp: the qp
 *
 * This schedules progress w/o regard to the s_flags.
 *
 * It is only used in post send, which करोesn't hold
 * the s_lock.
 */
bool _qib_schedule_send(काष्ठा rvt_qp *qp)
अणु
	काष्ठा qib_ibport *ibp =
		to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा qib_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा qib_qp_priv *priv = qp->priv;

	वापस queue_work(ppd->qib_wq, &priv->s_work);
पूर्ण

/**
 * qib_schedule_send - schedule progress
 * @qp: the qp
 *
 * This schedules qp progress.  The s_lock
 * should be held.
 */
bool qib_schedule_send(काष्ठा rvt_qp *qp)
अणु
	अगर (qib_send_ok(qp))
		वापस _qib_schedule_send(qp);
	वापस false;
पूर्ण
