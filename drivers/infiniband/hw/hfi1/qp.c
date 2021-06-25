<शैली गुरु>
/*
 * Copyright(c) 2015 - 2020 Intel Corporation.
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

#समावेश <linux/err.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/hash.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <rdma/rdma_vt.h>
#समावेश <rdma/rdmavt_qp.h>
#समावेश <rdma/ib_verbs.h>

#समावेश "hfi.h"
#समावेश "qp.h"
#समावेश "trace.h"
#समावेश "verbs_txreq.h"

अचिन्हित पूर्णांक hfi1_qp_table_size = 256;
module_param_named(qp_table_size, hfi1_qp_table_size, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(qp_table_size, "QP table size");

अटल व्योम flush_tx_list(काष्ठा rvt_qp *qp);
अटल पूर्णांक ioरुको_sleep(
	काष्ठा sdma_engine *sde,
	काष्ठा ioरुको_work *रुको,
	काष्ठा sdma_txreq *stx,
	अचिन्हित पूर्णांक seq,
	bool pkts_sent);
अटल व्योम ioरुको_wakeup(काष्ठा ioरुको *रुको, पूर्णांक reason);
अटल व्योम ioरुको_sdma_drained(काष्ठा ioरुको *रुको);
अटल व्योम qp_pio_drain(काष्ठा rvt_qp *qp);

स्थिर काष्ठा rvt_operation_params hfi1_post_parms[RVT_OPERATION_MAX] = अणु
[IB_WR_RDMA_WRITE] = अणु
	.length = माप(काष्ठा ib_rdma_wr),
	.qpt_support = BIT(IB_QPT_UC) | BIT(IB_QPT_RC),
पूर्ण,

[IB_WR_RDMA_READ] = अणु
	.length = माप(काष्ठा ib_rdma_wr),
	.qpt_support = BIT(IB_QPT_RC),
	.flags = RVT_OPERATION_ATOMIC,
पूर्ण,

[IB_WR_ATOMIC_CMP_AND_SWP] = अणु
	.length = माप(काष्ठा ib_atomic_wr),
	.qpt_support = BIT(IB_QPT_RC),
	.flags = RVT_OPERATION_ATOMIC | RVT_OPERATION_ATOMIC_SGE,
पूर्ण,

[IB_WR_ATOMIC_FETCH_AND_ADD] = अणु
	.length = माप(काष्ठा ib_atomic_wr),
	.qpt_support = BIT(IB_QPT_RC),
	.flags = RVT_OPERATION_ATOMIC | RVT_OPERATION_ATOMIC_SGE,
पूर्ण,

[IB_WR_RDMA_WRITE_WITH_IMM] = अणु
	.length = माप(काष्ठा ib_rdma_wr),
	.qpt_support = BIT(IB_QPT_UC) | BIT(IB_QPT_RC),
पूर्ण,

[IB_WR_SEND] = अणु
	.length = माप(काष्ठा ib_send_wr),
	.qpt_support = BIT(IB_QPT_UD) | BIT(IB_QPT_SMI) | BIT(IB_QPT_GSI) |
		       BIT(IB_QPT_UC) | BIT(IB_QPT_RC),
पूर्ण,

[IB_WR_SEND_WITH_IMM] = अणु
	.length = माप(काष्ठा ib_send_wr),
	.qpt_support = BIT(IB_QPT_UD) | BIT(IB_QPT_SMI) | BIT(IB_QPT_GSI) |
		       BIT(IB_QPT_UC) | BIT(IB_QPT_RC),
पूर्ण,

[IB_WR_REG_MR] = अणु
	.length = माप(काष्ठा ib_reg_wr),
	.qpt_support = BIT(IB_QPT_UC) | BIT(IB_QPT_RC),
	.flags = RVT_OPERATION_LOCAL,
पूर्ण,

[IB_WR_LOCAL_INV] = अणु
	.length = माप(काष्ठा ib_send_wr),
	.qpt_support = BIT(IB_QPT_UC) | BIT(IB_QPT_RC),
	.flags = RVT_OPERATION_LOCAL,
पूर्ण,

[IB_WR_SEND_WITH_INV] = अणु
	.length = माप(काष्ठा ib_send_wr),
	.qpt_support = BIT(IB_QPT_RC),
पूर्ण,

[IB_WR_OPFN] = अणु
	.length = माप(काष्ठा ib_atomic_wr),
	.qpt_support = BIT(IB_QPT_RC),
	.flags = RVT_OPERATION_USE_RESERVE,
पूर्ण,

[IB_WR_TID_RDMA_WRITE] = अणु
	.length = माप(काष्ठा ib_rdma_wr),
	.qpt_support = BIT(IB_QPT_RC),
	.flags = RVT_OPERATION_IGN_RNR_CNT,
पूर्ण,

पूर्ण;

अटल व्योम flush_list_head(काष्ठा list_head *l)
अणु
	जबतक (!list_empty(l)) अणु
		काष्ठा sdma_txreq *tx;

		tx = list_first_entry(
			l,
			काष्ठा sdma_txreq,
			list);
		list_del_init(&tx->list);
		hfi1_put_txreq(
			container_of(tx, काष्ठा verbs_txreq, txreq));
	पूर्ण
पूर्ण

अटल व्योम flush_tx_list(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	flush_list_head(&ioरुको_get_ib_work(&priv->s_ioरुको)->tx_head);
	flush_list_head(&ioरुको_get_tid_work(&priv->s_ioरुको)->tx_head);
पूर्ण

अटल व्योम flush_ioरुको(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	अचिन्हित दीर्घ flags;
	seqlock_t *lock = priv->s_ioरुको.lock;

	अगर (!lock)
		वापस;
	ग_लिखो_seqlock_irqsave(lock, flags);
	अगर (!list_empty(&priv->s_ioरुको.list)) अणु
		list_del_init(&priv->s_ioरुको.list);
		priv->s_ioरुको.lock = शून्य;
		rvt_put_qp(qp);
	पूर्ण
	ग_लिखो_sequnlock_irqrestore(lock, flags);
पूर्ण

/*
 * This function is what we would push to the core layer अगर we wanted to be a
 * "first class citizen".  Instead we hide this here and rely on Verbs ULPs
 * to blindly pass the MTU क्रमागत value from the PathRecord to us.
 */
अटल अंतरभूत पूर्णांक verbs_mtu_क्रमागत_to_पूर्णांक(काष्ठा ib_device *dev, क्रमागत ib_mtu mtu)
अणु
	/* Constraining 10KB packets to 8KB packets */
	अगर (mtu == (क्रमागत ib_mtu)OPA_MTU_10240)
		mtu = (क्रमागत ib_mtu)OPA_MTU_8192;
	वापस opa_mtu_क्रमागत_to_पूर्णांक((क्रमागत opa_mtu)mtu);
पूर्ण

पूर्णांक hfi1_check_modअगरy_qp(काष्ठा rvt_qp *qp, काष्ठा ib_qp_attr *attr,
			 पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_qp *ibqp = &qp->ibqp;
	काष्ठा hfi1_ibdev *dev = to_idev(ibqp->device);
	काष्ठा hfi1_devdata *dd = dd_from_dev(dev);
	u8 sc;

	अगर (attr_mask & IB_QP_AV) अणु
		sc = ah_to_sc(ibqp->device, &attr->ah_attr);
		अगर (sc == 0xf)
			वापस -EINVAL;

		अगर (!qp_to_sdma_engine(qp, sc) &&
		    dd->flags & HFI1_HAS_SEND_DMA)
			वापस -EINVAL;

		अगर (!qp_to_send_context(qp, sc))
			वापस -EINVAL;
	पूर्ण

	अगर (attr_mask & IB_QP_ALT_PATH) अणु
		sc = ah_to_sc(ibqp->device, &attr->alt_ah_attr);
		अगर (sc == 0xf)
			वापस -EINVAL;

		अगर (!qp_to_sdma_engine(qp, sc) &&
		    dd->flags & HFI1_HAS_SEND_DMA)
			वापस -EINVAL;

		अगर (!qp_to_send_context(qp, sc))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * qp_set_16b - Set the hdr_type based on whether the slid or the
 * dlid in the connection is extended. Only applicable क्रम RC and UC
 * QPs. UD QPs determine this on the fly from the ah in the wqe
 */
अटल अंतरभूत व्योम qp_set_16b(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_ibport *ibp;
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	/* Update ah_attr to account क्रम extended LIDs */
	hfi1_update_ah_attr(qp->ibqp.device, &qp->remote_ah_attr);

	/* Create 32 bit LIDs */
	hfi1_make_opa_lid(&qp->remote_ah_attr);

	अगर (!(rdma_ah_get_ah_flags(&qp->remote_ah_attr) & IB_AH_GRH))
		वापस;

	ibp = to_iport(qp->ibqp.device, qp->port_num);
	ppd = ppd_from_ibp(ibp);
	priv->hdr_type = hfi1_get_hdr_type(ppd->lid, &qp->remote_ah_attr);
पूर्ण

व्योम hfi1_modअगरy_qp(काष्ठा rvt_qp *qp, काष्ठा ib_qp_attr *attr,
		    पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_qp *ibqp = &qp->ibqp;
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	अगर (attr_mask & IB_QP_AV) अणु
		priv->s_sc = ah_to_sc(ibqp->device, &qp->remote_ah_attr);
		priv->s_sde = qp_to_sdma_engine(qp, priv->s_sc);
		priv->s_sendcontext = qp_to_send_context(qp, priv->s_sc);
		qp_set_16b(qp);
	पूर्ण

	अगर (attr_mask & IB_QP_PATH_MIG_STATE &&
	    attr->path_mig_state == IB_MIG_MIGRATED &&
	    qp->s_mig_state == IB_MIG_ARMED) अणु
		qp->s_flags |= HFI1_S_AHG_CLEAR;
		priv->s_sc = ah_to_sc(ibqp->device, &qp->remote_ah_attr);
		priv->s_sde = qp_to_sdma_engine(qp, priv->s_sc);
		priv->s_sendcontext = qp_to_send_context(qp, priv->s_sc);
		qp_set_16b(qp);
	पूर्ण

	opfn_qp_init(qp, attr, attr_mask);
पूर्ण

/**
 * hfi1_setup_wqe - set up the wqe
 * @qp: The qp
 * @wqe: The built wqe
 * @call_send: Determine अगर the send should be posted or scheduled.
 *
 * Perक्रमm setup of the wqe.  This is called
 * prior to inserting the wqe पूर्णांकo the ring but after
 * the wqe has been setup by RDMAVT. This function
 * allows the driver the opportunity to perक्रमm
 * validation and additional setup of the wqe.
 *
 * Returns 0 on success, -EINVAL on failure
 *
 */
पूर्णांक hfi1_setup_wqe(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe, bool *call_send)
अणु
	काष्ठा hfi1_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा rvt_ah *ah;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_devdata *dd;

	चयन (qp->ibqp.qp_type) अणु
	हाल IB_QPT_RC:
		hfi1_setup_tid_rdma_wqe(qp, wqe);
		fallthrough;
	हाल IB_QPT_UC:
		अगर (wqe->length > 0x80000000U)
			वापस -EINVAL;
		अगर (wqe->length > qp->pmtu)
			*call_send = false;
		अवरोध;
	हाल IB_QPT_SMI:
		/*
		 * SM packets should exclusively use VL15 and their SL is
		 * ignored (IBTA v1.3, Section 3.5.8.2). Thereक्रमe, when ah
		 * is created, SL is 0 in most हालs and as a result some
		 * fields (vl and pmtu) in ah may not be set correctly,
		 * depending on the SL2SC and SC2VL tables at the समय.
		 */
		ppd = ppd_from_ibp(ibp);
		dd = dd_from_ppd(ppd);
		अगर (wqe->length > dd->vld[15].mtu)
			वापस -EINVAL;
		अवरोध;
	हाल IB_QPT_GSI:
	हाल IB_QPT_UD:
		ah = rvt_get_swqe_ah(wqe);
		अगर (wqe->length > (1 << ah->log_pmtu))
			वापस -EINVAL;
		अगर (ibp->sl_to_sc[rdma_ah_get_sl(&ah->attr)] == 0xf)
			वापस -EINVAL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * System latency between send and schedule is large enough that
	 * क्रमcing call_send to true क्रम piothreshold packets is necessary.
	 */
	अगर (wqe->length <= piothreshold)
		*call_send = true;
	वापस 0;
पूर्ण

/**
 * _hfi1_schedule_send - schedule progress
 * @qp: the QP
 *
 * This schedules qp progress w/o regard to the s_flags.
 *
 * It is only used in the post send, which करोesn't hold
 * the s_lock.
 */
bool _hfi1_schedule_send(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा hfi1_ibport *ibp =
		to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा hfi1_devdata *dd = ppd->dd;

	अगर (dd->flags & HFI1_SHUTDOWN)
		वापस true;

	वापस ioरुको_schedule(&priv->s_ioरुको, ppd->hfi1_wq,
			       priv->s_sde ?
			       priv->s_sde->cpu :
			       cpumask_first(cpumask_of_node(dd->node)));
पूर्ण

अटल व्योम qp_pio_drain(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	अगर (!priv->s_sendcontext)
		वापस;
	जबतक (ioरुको_pio_pending(&priv->s_ioरुको)) अणु
		ग_लिखो_seqlock_irq(&priv->s_sendcontext->रुकोlock);
		hfi1_sc_wantpiobuf_पूर्णांकr(priv->s_sendcontext, 1);
		ग_लिखो_sequnlock_irq(&priv->s_sendcontext->रुकोlock);
		ioरुको_pio_drain(&priv->s_ioरुको);
		ग_लिखो_seqlock_irq(&priv->s_sendcontext->रुकोlock);
		hfi1_sc_wantpiobuf_पूर्णांकr(priv->s_sendcontext, 0);
		ग_लिखो_sequnlock_irq(&priv->s_sendcontext->रुकोlock);
	पूर्ण
पूर्ण

/**
 * hfi1_schedule_send - schedule progress
 * @qp: the QP
 *
 * This schedules qp progress and caller should hold
 * the s_lock.
 * @वापस true अगर the first leg is scheduled;
 * false अगर the first leg is not scheduled.
 */
bool hfi1_schedule_send(काष्ठा rvt_qp *qp)
अणु
	lockdep_निश्चित_held(&qp->s_lock);
	अगर (hfi1_send_ok(qp)) अणु
		_hfi1_schedule_send(qp);
		वापस true;
	पूर्ण
	अगर (qp->s_flags & HFI1_S_ANY_WAIT_IO)
		ioरुको_set_flag(&((काष्ठा hfi1_qp_priv *)qp->priv)->s_ioरुको,
				IOWAIT_PENDING_IB);
	वापस false;
पूर्ण

अटल व्योम hfi1_qp_schedule(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	bool ret;

	अगर (ioरुको_flag_set(&priv->s_ioरुको, IOWAIT_PENDING_IB)) अणु
		ret = hfi1_schedule_send(qp);
		अगर (ret)
			ioरुको_clear_flag(&priv->s_ioरुको, IOWAIT_PENDING_IB);
	पूर्ण
	अगर (ioरुको_flag_set(&priv->s_ioरुको, IOWAIT_PENDING_TID)) अणु
		ret = hfi1_schedule_tid_send(qp);
		अगर (ret)
			ioरुको_clear_flag(&priv->s_ioरुको, IOWAIT_PENDING_TID);
	पूर्ण
पूर्ण

व्योम hfi1_qp_wakeup(काष्ठा rvt_qp *qp, u32 flag)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->s_lock, flags);
	अगर (qp->s_flags & flag) अणु
		qp->s_flags &= ~flag;
		trace_hfi1_qpwakeup(qp, flag);
		hfi1_qp_schedule(qp);
	पूर्ण
	spin_unlock_irqrestore(&qp->s_lock, flags);
	/* Notअगरy hfi1_destroy_qp() अगर it is रुकोing. */
	rvt_put_qp(qp);
पूर्ण

व्योम hfi1_qp_unbusy(काष्ठा rvt_qp *qp, काष्ठा ioरुको_work *रुको)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	अगर (ioरुको_set_work_flag(रुको) == IOWAIT_IB_SE) अणु
		qp->s_flags &= ~RVT_S_BUSY;
		/*
		 * If we are sending a first-leg packet from the second leg,
		 * we need to clear the busy flag from priv->s_flags to
		 * aव्योम a race condition when the qp wakes up beक्रमe
		 * the call to hfi1_verbs_send() वापसs to the second
		 * leg. In that हाल, the second leg will terminate without
		 * being re-scheduled, resulting in failure to send TID RDMA
		 * WRITE DATA and TID RDMA ACK packets.
		 */
		अगर (priv->s_flags & HFI1_S_TID_BUSY_SET) अणु
			priv->s_flags &= ~(HFI1_S_TID_BUSY_SET |
					   RVT_S_BUSY);
			ioरुको_set_flag(&priv->s_ioरुको, IOWAIT_PENDING_TID);
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->s_flags &= ~RVT_S_BUSY;
	पूर्ण
पूर्ण

अटल पूर्णांक ioरुको_sleep(
	काष्ठा sdma_engine *sde,
	काष्ठा ioरुको_work *रुको,
	काष्ठा sdma_txreq *stx,
	uपूर्णांक seq,
	bool pkts_sent)
अणु
	काष्ठा verbs_txreq *tx = container_of(stx, काष्ठा verbs_txreq, txreq);
	काष्ठा rvt_qp *qp;
	काष्ठा hfi1_qp_priv *priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	qp = tx->qp;
	priv = qp->priv;

	spin_lock_irqsave(&qp->s_lock, flags);
	अगर (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) अणु
		/*
		 * If we couldn't queue the DMA request, save the info
		 * and try again later rather than destroying the
		 * buffer and unकरोing the side effects of the copy.
		 */
		/* Make a common routine? */
		list_add_tail(&stx->list, &रुको->tx_head);
		ग_लिखो_seqlock(&sde->रुकोlock);
		अगर (sdma_progress(sde, seq, stx))
			जाओ eagain;
		अगर (list_empty(&priv->s_ioरुको.list)) अणु
			काष्ठा hfi1_ibport *ibp =
				to_iport(qp->ibqp.device, qp->port_num);

			ibp->rvp.n_dmaरुको++;
			qp->s_flags |= RVT_S_WAIT_DMA_DESC;
			ioरुको_get_priority(&priv->s_ioरुको);
			ioरुको_queue(pkts_sent, &priv->s_ioरुको,
				     &sde->dmaरुको);
			priv->s_ioरुको.lock = &sde->रुकोlock;
			trace_hfi1_qpsleep(qp, RVT_S_WAIT_DMA_DESC);
			rvt_get_qp(qp);
		पूर्ण
		ग_लिखो_sequnlock(&sde->रुकोlock);
		hfi1_qp_unbusy(qp, रुको);
		spin_unlock_irqrestore(&qp->s_lock, flags);
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&qp->s_lock, flags);
		hfi1_put_txreq(tx);
	पूर्ण
	वापस ret;
eagain:
	ग_लिखो_sequnlock(&sde->रुकोlock);
	spin_unlock_irqrestore(&qp->s_lock, flags);
	list_del_init(&stx->list);
	वापस -EAGAIN;
पूर्ण

अटल व्योम ioरुको_wakeup(काष्ठा ioरुको *रुको, पूर्णांक reason)
अणु
	काष्ठा rvt_qp *qp = ioरुको_to_qp(रुको);

	WARN_ON(reason != SDMA_AVAIL_REASON);
	hfi1_qp_wakeup(qp, RVT_S_WAIT_DMA_DESC);
पूर्ण

अटल व्योम ioरुको_sdma_drained(काष्ठा ioरुको *रुको)
अणु
	काष्ठा rvt_qp *qp = ioरुको_to_qp(रुको);
	अचिन्हित दीर्घ flags;

	/*
	 * This happens when the send engine notes
	 * a QP in the error state and cannot
	 * करो the flush work until that QP's
	 * sdma work has finished.
	 */
	spin_lock_irqsave(&qp->s_lock, flags);
	अगर (qp->s_flags & RVT_S_WAIT_DMA) अणु
		qp->s_flags &= ~RVT_S_WAIT_DMA;
		hfi1_schedule_send(qp);
	पूर्ण
	spin_unlock_irqrestore(&qp->s_lock, flags);
पूर्ण

अटल व्योम hfi1_init_priority(काष्ठा ioरुको *w)
अणु
	काष्ठा rvt_qp *qp = ioरुको_to_qp(w);
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	अगर (qp->s_flags & RVT_S_ACK_PENDING)
		w->priority++;
	अगर (priv->s_flags & RVT_S_ACK_PENDING)
		w->priority++;
पूर्ण

/**
 * qp_to_sdma_engine - map a qp to a send engine
 * @qp: the QP
 * @sc5: the 5 bit sc
 *
 * Return:
 * A send engine क्रम the qp or शून्य क्रम SMI type qp.
 */
काष्ठा sdma_engine *qp_to_sdma_engine(काष्ठा rvt_qp *qp, u8 sc5)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(qp->ibqp.device);
	काष्ठा sdma_engine *sde;

	अगर (!(dd->flags & HFI1_HAS_SEND_DMA))
		वापस शून्य;
	चयन (qp->ibqp.qp_type) अणु
	हाल IB_QPT_SMI:
		वापस शून्य;
	शेष:
		अवरोध;
	पूर्ण
	sde = sdma_select_engine_sc(dd, qp->ibqp.qp_num >> dd->qos_shअगरt, sc5);
	वापस sde;
पूर्ण

/**
 * qp_to_send_context - map a qp to a send context
 * @qp: the QP
 * @sc5: the 5 bit sc
 *
 * Return:
 * A send context क्रम the qp
 */
काष्ठा send_context *qp_to_send_context(काष्ठा rvt_qp *qp, u8 sc5)
अणु
	काष्ठा hfi1_devdata *dd = dd_from_ibdev(qp->ibqp.device);

	चयन (qp->ibqp.qp_type) अणु
	हाल IB_QPT_SMI:
		/* SMA packets to VL15 */
		वापस dd->vld[15].sc;
	शेष:
		अवरोध;
	पूर्ण

	वापस pio_select_send_context_sc(dd, qp->ibqp.qp_num >> dd->qos_shअगरt,
					  sc5);
पूर्ण

अटल स्थिर अक्षर * स्थिर qp_type_str[] = अणु
	"SMI", "GSI", "RC", "UC", "UD",
पूर्ण;

अटल पूर्णांक qp_idle(काष्ठा rvt_qp *qp)
अणु
	वापस
		qp->s_last == qp->s_acked &&
		qp->s_acked == qp->s_cur &&
		qp->s_cur == qp->s_tail &&
		qp->s_tail == qp->s_head;
पूर्ण

/**
 * qp_iter_prपूर्णांक - prपूर्णांक the qp inक्रमmation to seq_file
 * @s: the seq_file to emit the qp inक्रमmation on
 * @iter: the iterator क्रम the qp hash list
 */
व्योम qp_iter_prपूर्णांक(काष्ठा seq_file *s, काष्ठा rvt_qp_iter *iter)
अणु
	काष्ठा rvt_swqe *wqe;
	काष्ठा rvt_qp *qp = iter->qp;
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा sdma_engine *sde;
	काष्ठा send_context *send_context;
	काष्ठा rvt_ack_entry *e = शून्य;
	काष्ठा rvt_srq *srq = qp->ibqp.srq ?
		ibsrq_to_rvtsrq(qp->ibqp.srq) : शून्य;

	sde = qp_to_sdma_engine(qp, priv->s_sc);
	wqe = rvt_get_swqe_ptr(qp, qp->s_last);
	send_context = qp_to_send_context(qp, priv->s_sc);
	अगर (qp->s_ack_queue)
		e = &qp->s_ack_queue[qp->s_tail_ack_queue];
	seq_म_लिखो(s,
		   "N %d %s QP %x R %u %s %u %u f=%x %u %u %u %u %u %u SPSN %x %x %x %x %x RPSN %x S(%u %u %u %u %u %u %u) R(%u %u %u) RQP %x LID %x SL %u MTU %u %u %u %u %u SDE %p,%u SC %p,%u SCQ %u %u PID %d OS %x %x E %x %x %x RNR %d %s %d\n",
		   iter->n,
		   qp_idle(qp) ? "I" : "B",
		   qp->ibqp.qp_num,
		   atomic_पढ़ो(&qp->refcount),
		   qp_type_str[qp->ibqp.qp_type],
		   qp->state,
		   wqe ? wqe->wr.opcode : 0,
		   qp->s_flags,
		   ioरुको_sdma_pending(&priv->s_ioरुको),
		   ioरुको_pio_pending(&priv->s_ioरुको),
		   !list_empty(&priv->s_ioरुको.list),
		   qp->समयout,
		   wqe ? wqe->ssn : 0,
		   qp->s_lsn,
		   qp->s_last_psn,
		   qp->s_psn, qp->s_next_psn,
		   qp->s_sending_psn, qp->s_sending_hpsn,
		   qp->r_psn,
		   qp->s_last, qp->s_acked, qp->s_cur,
		   qp->s_tail, qp->s_head, qp->s_size,
		   qp->s_avail,
		   /* ack_queue ring poपूर्णांकers, size */
		   qp->s_tail_ack_queue, qp->r_head_ack_queue,
		   rvt_max_atomic(&to_idev(qp->ibqp.device)->rdi),
		   /* remote QP info  */
		   qp->remote_qpn,
		   rdma_ah_get_dlid(&qp->remote_ah_attr),
		   rdma_ah_get_sl(&qp->remote_ah_attr),
		   qp->pmtu,
		   qp->s_retry,
		   qp->s_retry_cnt,
		   qp->s_rnr_retry_cnt,
		   qp->s_rnr_retry,
		   sde,
		   sde ? sde->this_idx : 0,
		   send_context,
		   send_context ? send_context->sw_index : 0,
		   ib_cq_head(qp->ibqp.send_cq),
		   ib_cq_tail(qp->ibqp.send_cq),
		   qp->pid,
		   qp->s_state,
		   qp->s_ack_state,
		   /* ack queue inक्रमmation */
		   e ? e->opcode : 0,
		   e ? e->psn : 0,
		   e ? e->lpsn : 0,
		   qp->r_min_rnr_समयr,
		   srq ? "SRQ" : "RQ",
		   srq ? srq->rq.size : qp->r_rq.size
		);
पूर्ण

व्योम *qp_priv_alloc(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv;

	priv = kzalloc_node(माप(*priv), GFP_KERNEL, rdi->dparms.node);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);

	priv->owner = qp;

	priv->s_ahg = kzalloc_node(माप(*priv->s_ahg), GFP_KERNEL,
				   rdi->dparms.node);
	अगर (!priv->s_ahg) अणु
		kमुक्त(priv);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	ioरुको_init(
		&priv->s_ioरुको,
		1,
		_hfi1_करो_send,
		_hfi1_करो_tid_send,
		ioरुको_sleep,
		ioरुको_wakeup,
		ioरुको_sdma_drained,
		hfi1_init_priority);
	/* Init to a value to start the running average correctly */
	priv->s_running_pkt_size = piothreshold / 2;
	वापस priv;
पूर्ण

व्योम qp_priv_मुक्त(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	hfi1_qp_priv_tid_मुक्त(rdi, qp);
	kमुक्त(priv->s_ahg);
	kमुक्त(priv);
पूर्ण

अचिन्हित मुक्त_all_qps(काष्ठा rvt_dev_info *rdi)
अणु
	काष्ठा hfi1_ibdev *verbs_dev = container_of(rdi,
						    काष्ठा hfi1_ibdev,
						    rdi);
	काष्ठा hfi1_devdata *dd = container_of(verbs_dev,
					       काष्ठा hfi1_devdata,
					       verbs_dev);
	पूर्णांक n;
	अचिन्हित qp_inuse = 0;

	क्रम (n = 0; n < dd->num_pports; n++) अणु
		काष्ठा hfi1_ibport *ibp = &dd->pport[n].ibport_data;

		rcu_पढ़ो_lock();
		अगर (rcu_dereference(ibp->rvp.qp[0]))
			qp_inuse++;
		अगर (rcu_dereference(ibp->rvp.qp[1]))
			qp_inuse++;
		rcu_पढ़ो_unlock();
	पूर्ण

	वापस qp_inuse;
पूर्ण

व्योम flush_qp_रुकोers(काष्ठा rvt_qp *qp)
अणु
	lockdep_निश्चित_held(&qp->s_lock);
	flush_ioरुको(qp);
	hfi1_tid_rdma_flush_रुको(qp);
पूर्ण

व्योम stop_send_queue(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	ioरुको_cancel_work(&priv->s_ioरुको);
	अगर (cancel_work_sync(&priv->tid_rdma.trigger_work))
		rvt_put_qp(qp);
पूर्ण

व्योम quiesce_qp(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	hfi1_del_tid_reap_समयr(qp);
	hfi1_del_tid_retry_समयr(qp);
	ioरुको_sdma_drain(&priv->s_ioरुको);
	qp_pio_drain(qp);
	flush_tx_list(qp);
पूर्ण

व्योम notअगरy_qp_reset(काष्ठा rvt_qp *qp)
अणु
	hfi1_qp_kern_exp_rcv_clear_all(qp);
	qp->r_adefered = 0;
	clear_ahg(qp);

	/* Clear any OPFN state */
	अगर (qp->ibqp.qp_type == IB_QPT_RC)
		opfn_conn_error(qp);
पूर्ण

/*
 * Switch to alternate path.
 * The QP s_lock should be held and पूर्णांकerrupts disabled.
 */
व्योम hfi1_migrate_qp(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा ib_event ev;

	qp->s_mig_state = IB_MIG_MIGRATED;
	qp->remote_ah_attr = qp->alt_ah_attr;
	qp->port_num = rdma_ah_get_port_num(&qp->alt_ah_attr);
	qp->s_pkey_index = qp->s_alt_pkey_index;
	qp->s_flags |= HFI1_S_AHG_CLEAR;
	priv->s_sc = ah_to_sc(qp->ibqp.device, &qp->remote_ah_attr);
	priv->s_sde = qp_to_sdma_engine(qp, priv->s_sc);
	qp_set_16b(qp);

	ev.device = qp->ibqp.device;
	ev.element.qp = &qp->ibqp;
	ev.event = IB_EVENT_PATH_MIG;
	qp->ibqp.event_handler(&ev, qp->ibqp.qp_context);
पूर्ण

पूर्णांक mtu_to_path_mtu(u32 mtu)
अणु
	वापस mtu_to_क्रमागत(mtu, OPA_MTU_8192);
पूर्ण

u32 mtu_from_qp(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp, u32 pmtu)
अणु
	u32 mtu;
	काष्ठा hfi1_ibdev *verbs_dev = container_of(rdi,
						    काष्ठा hfi1_ibdev,
						    rdi);
	काष्ठा hfi1_devdata *dd = container_of(verbs_dev,
					       काष्ठा hfi1_devdata,
					       verbs_dev);
	काष्ठा hfi1_ibport *ibp;
	u8 sc, vl;

	ibp = &dd->pport[qp->port_num - 1].ibport_data;
	sc = ibp->sl_to_sc[rdma_ah_get_sl(&qp->remote_ah_attr)];
	vl = sc_to_vlt(dd, sc);

	mtu = verbs_mtu_क्रमागत_to_पूर्णांक(qp->ibqp.device, pmtu);
	अगर (vl < PER_VL_SEND_CONTEXTS)
		mtu = min_t(u32, mtu, dd->vld[vl].mtu);
	वापस mtu;
पूर्ण

पूर्णांक get_pmtu_from_attr(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
		       काष्ठा ib_qp_attr *attr)
अणु
	पूर्णांक mtu, pidx = qp->port_num - 1;
	काष्ठा hfi1_ibdev *verbs_dev = container_of(rdi,
						    काष्ठा hfi1_ibdev,
						    rdi);
	काष्ठा hfi1_devdata *dd = container_of(verbs_dev,
					       काष्ठा hfi1_devdata,
					       verbs_dev);
	mtu = verbs_mtu_क्रमागत_to_पूर्णांक(qp->ibqp.device, attr->path_mtu);
	अगर (mtu == -1)
		वापस -1; /* values less than 0 are error */

	अगर (mtu > dd->pport[pidx].ibmtu)
		वापस mtu_to_क्रमागत(dd->pport[pidx].ibmtu, IB_MTU_2048);
	अन्यथा
		वापस attr->path_mtu;
पूर्ण

व्योम notअगरy_error_qp(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	seqlock_t *lock = priv->s_ioरुको.lock;

	अगर (lock) अणु
		ग_लिखो_seqlock(lock);
		अगर (!list_empty(&priv->s_ioरुको.list) &&
		    !(qp->s_flags & RVT_S_BUSY) &&
		    !(priv->s_flags & RVT_S_BUSY)) अणु
			qp->s_flags &= ~HFI1_S_ANY_WAIT_IO;
			ioरुको_clear_flag(&priv->s_ioरुको, IOWAIT_PENDING_IB);
			ioरुको_clear_flag(&priv->s_ioरुको, IOWAIT_PENDING_TID);
			list_del_init(&priv->s_ioरुको.list);
			priv->s_ioरुको.lock = शून्य;
			rvt_put_qp(qp);
		पूर्ण
		ग_लिखो_sequnlock(lock);
	पूर्ण

	अगर (!(qp->s_flags & RVT_S_BUSY) && !(priv->s_flags & RVT_S_BUSY)) अणु
		qp->s_hdrwords = 0;
		अगर (qp->s_rdma_mr) अणु
			rvt_put_mr(qp->s_rdma_mr);
			qp->s_rdma_mr = शून्य;
		पूर्ण
		flush_tx_list(qp);
	पूर्ण
पूर्ण

/**
 * hfi1_qp_iter_cb - callback क्रम iterator
 * @qp: the qp
 * @v: the sl in low bits of v
 *
 * This is called from the iterator callback to work
 * on an inभागidual qp.
 */
अटल व्योम hfi1_qp_iter_cb(काष्ठा rvt_qp *qp, u64 v)
अणु
	पूर्णांक lastwqe;
	काष्ठा ib_event ev;
	काष्ठा hfi1_ibport *ibp =
		to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	u8 sl = (u8)v;

	अगर (qp->port_num != ppd->port ||
	    (qp->ibqp.qp_type != IB_QPT_UC &&
	     qp->ibqp.qp_type != IB_QPT_RC) ||
	    rdma_ah_get_sl(&qp->remote_ah_attr) != sl ||
	    !(ib_rvt_state_ops[qp->state] & RVT_POST_SEND_OK))
		वापस;

	spin_lock_irq(&qp->r_lock);
	spin_lock(&qp->s_hlock);
	spin_lock(&qp->s_lock);
	lastwqe = rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);
	spin_unlock(&qp->s_lock);
	spin_unlock(&qp->s_hlock);
	spin_unlock_irq(&qp->r_lock);
	अगर (lastwqe) अणु
		ev.device = qp->ibqp.device;
		ev.element.qp = &qp->ibqp;
		ev.event = IB_EVENT_QP_LAST_WQE_REACHED;
		qp->ibqp.event_handler(&ev, qp->ibqp.qp_context);
	पूर्ण
पूर्ण

/**
 * hfi1_error_port_qps - put a port's RC/UC qps पूर्णांकo error state
 * @ibp: the ibport.
 * @sl: the service level.
 *
 * This function places all RC/UC qps with a given service level पूर्णांकo error
 * state. It is generally called to क्रमce upper lay apps to abanकरोn stale qps
 * after an sl->sc mapping change.
 */
व्योम hfi1_error_port_qps(काष्ठा hfi1_ibport *ibp, u8 sl)
अणु
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा hfi1_ibdev *dev = &ppd->dd->verbs_dev;

	rvt_qp_iter(&dev->rdi, sl, hfi1_qp_iter_cb);
पूर्ण
