<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 * Work Requests exploiting Infiniband API
 *
 * Work requests (WR) of type ib_post_send or ib_post_recv respectively
 * are submitted to either RC SQ or RC RQ respectively
 * (reliably connected send/receive queue)
 * and become work queue entries (WQEs).
 * While an SQ WR/WQE is pending, we track it until transmission completion.
 * Through a send or receive completion queue (CQ) respectively,
 * we get completion queue entries (CQEs) [aka work completions (WCs)].
 * Since the CQ callback is called from IRQ context, we split work by using
 * bottom halves implemented by tasklets.
 *
 * SMC uses this to exchange LLC (link layer control)
 * and CDC (connection data control) messages.
 *
 * Copyright IBM Corp. 2016
 *
 * Author(s):  Steffen Maier <maier@linux.vnet.ibm.com>
 */

#समावेश <linux/atomic.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/रुको.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "smc.h"
#समावेश "smc_wr.h"

#घोषणा SMC_WR_MAX_POLL_CQE 10	/* max. # of compl. queue elements in 1 poll */

#घोषणा SMC_WR_RX_HASH_BITS 4
अटल DEFINE_HASHTABLE(smc_wr_rx_hash, SMC_WR_RX_HASH_BITS);
अटल DEFINE_SPINLOCK(smc_wr_rx_hash_lock);

काष्ठा smc_wr_tx_pend अणु	/* control data क्रम a pending send request */
	u64			wr_id;		/* work request id sent */
	smc_wr_tx_handler	handler;
	क्रमागत ib_wc_status	wc_status;	/* CQE status */
	काष्ठा smc_link		*link;
	u32			idx;
	काष्ठा smc_wr_tx_pend_priv priv;
	u8			compl_requested;
पूर्ण;

/******************************** send queue *********************************/

/*------------------------------- completion --------------------------------*/

/* वापसs true अगर at least one tx work request is pending on the given link */
अटल अंतरभूत bool smc_wr_is_tx_pend(काष्ठा smc_link *link)
अणु
	अगर (find_first_bit(link->wr_tx_mask, link->wr_tx_cnt) !=
							link->wr_tx_cnt) अणु
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* रुको till all pending tx work requests on the given link are completed */
पूर्णांक smc_wr_tx_रुको_no_pending_sends(काष्ठा smc_link *link)
अणु
	अगर (रुको_event_समयout(link->wr_tx_रुको, !smc_wr_is_tx_pend(link),
			       SMC_WR_TX_WAIT_PENDING_TIME))
		वापस 0;
	अन्यथा /* समयout */
		वापस -EPIPE;
पूर्ण

अटल अंतरभूत पूर्णांक smc_wr_tx_find_pending_index(काष्ठा smc_link *link, u64 wr_id)
अणु
	u32 i;

	क्रम (i = 0; i < link->wr_tx_cnt; i++) अणु
		अगर (link->wr_tx_pends[i].wr_id == wr_id)
			वापस i;
	पूर्ण
	वापस link->wr_tx_cnt;
पूर्ण

अटल अंतरभूत व्योम smc_wr_tx_process_cqe(काष्ठा ib_wc *wc)
अणु
	काष्ठा smc_wr_tx_pend pnd_snd;
	काष्ठा smc_link *link;
	u32 pnd_snd_idx;
	पूर्णांक i;

	link = wc->qp->qp_context;

	अगर (wc->opcode == IB_WC_REG_MR) अणु
		अगर (wc->status)
			link->wr_reg_state = FAILED;
		अन्यथा
			link->wr_reg_state = CONFIRMED;
		smc_wr_wakeup_reg_रुको(link);
		वापस;
	पूर्ण

	pnd_snd_idx = smc_wr_tx_find_pending_index(link, wc->wr_id);
	अगर (pnd_snd_idx == link->wr_tx_cnt)
		वापस;
	link->wr_tx_pends[pnd_snd_idx].wc_status = wc->status;
	अगर (link->wr_tx_pends[pnd_snd_idx].compl_requested)
		complete(&link->wr_tx_compl[pnd_snd_idx]);
	स_नकल(&pnd_snd, &link->wr_tx_pends[pnd_snd_idx], माप(pnd_snd));
	/* clear the full काष्ठा smc_wr_tx_pend including .priv */
	स_रखो(&link->wr_tx_pends[pnd_snd_idx], 0,
	       माप(link->wr_tx_pends[pnd_snd_idx]));
	स_रखो(&link->wr_tx_bufs[pnd_snd_idx], 0,
	       माप(link->wr_tx_bufs[pnd_snd_idx]));
	अगर (!test_and_clear_bit(pnd_snd_idx, link->wr_tx_mask))
		वापस;
	अगर (wc->status) अणु
		क्रम_each_set_bit(i, link->wr_tx_mask, link->wr_tx_cnt) अणु
			/* clear full काष्ठा smc_wr_tx_pend including .priv */
			स_रखो(&link->wr_tx_pends[i], 0,
			       माप(link->wr_tx_pends[i]));
			स_रखो(&link->wr_tx_bufs[i], 0,
			       माप(link->wr_tx_bufs[i]));
			clear_bit(i, link->wr_tx_mask);
		पूर्ण
		/* terminate link */
		smcr_link_करोwn_cond_sched(link);
	पूर्ण
	अगर (pnd_snd.handler)
		pnd_snd.handler(&pnd_snd.priv, link, wc->status);
	wake_up(&link->wr_tx_रुको);
पूर्ण

अटल व्योम smc_wr_tx_tasklet_fn(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा smc_ib_device *dev = from_tasklet(dev, t, send_tasklet);
	काष्ठा ib_wc wc[SMC_WR_MAX_POLL_CQE];
	पूर्णांक i = 0, rc;
	पूर्णांक polled = 0;

again:
	polled++;
	करो अणु
		स_रखो(&wc, 0, माप(wc));
		rc = ib_poll_cq(dev->roce_cq_send, SMC_WR_MAX_POLL_CQE, wc);
		अगर (polled == 1) अणु
			ib_req_notअगरy_cq(dev->roce_cq_send,
					 IB_CQ_NEXT_COMP |
					 IB_CQ_REPORT_MISSED_EVENTS);
		पूर्ण
		अगर (!rc)
			अवरोध;
		क्रम (i = 0; i < rc; i++)
			smc_wr_tx_process_cqe(&wc[i]);
	पूर्ण जबतक (rc > 0);
	अगर (polled == 1)
		जाओ again;
पूर्ण

व्योम smc_wr_tx_cq_handler(काष्ठा ib_cq *ib_cq, व्योम *cq_context)
अणु
	काष्ठा smc_ib_device *dev = (काष्ठा smc_ib_device *)cq_context;

	tasklet_schedule(&dev->send_tasklet);
पूर्ण

/*---------------------------- request submission ---------------------------*/

अटल अंतरभूत पूर्णांक smc_wr_tx_get_मुक्त_slot_index(काष्ठा smc_link *link, u32 *idx)
अणु
	*idx = link->wr_tx_cnt;
	अगर (!smc_link_usable(link))
		वापस -ENOLINK;
	क्रम_each_clear_bit(*idx, link->wr_tx_mask, link->wr_tx_cnt) अणु
		अगर (!test_and_set_bit(*idx, link->wr_tx_mask))
			वापस 0;
	पूर्ण
	*idx = link->wr_tx_cnt;
	वापस -EBUSY;
पूर्ण

/**
 * smc_wr_tx_get_मुक्त_slot() - वापसs buffer क्रम message assembly,
 *			and sets info क्रम pending transmit tracking
 * @link:		Poपूर्णांकer to smc_link used to later send the message.
 * @handler:		Send completion handler function poपूर्णांकer.
 * @wr_buf:		Out value वापसs poपूर्णांकer to message buffer.
 * @wr_rdma_buf:	Out value वापसs poपूर्णांकer to rdma work request.
 * @wr_pend_priv:	Out value वापसs poपूर्णांकer serving as handler context.
 *
 * Return: 0 on success, or -त्रुटि_सं on error.
 */
पूर्णांक smc_wr_tx_get_मुक्त_slot(काष्ठा smc_link *link,
			    smc_wr_tx_handler handler,
			    काष्ठा smc_wr_buf **wr_buf,
			    काष्ठा smc_rdma_wr **wr_rdma_buf,
			    काष्ठा smc_wr_tx_pend_priv **wr_pend_priv)
अणु
	काष्ठा smc_link_group *lgr = smc_get_lgr(link);
	काष्ठा smc_wr_tx_pend *wr_pend;
	u32 idx = link->wr_tx_cnt;
	काष्ठा ib_send_wr *wr_ib;
	u64 wr_id;
	पूर्णांक rc;

	*wr_buf = शून्य;
	*wr_pend_priv = शून्य;
	अगर (in_softirq() || lgr->terminating) अणु
		rc = smc_wr_tx_get_मुक्त_slot_index(link, &idx);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		rc = रुको_event_पूर्णांकerruptible_समयout(
			link->wr_tx_रुको,
			!smc_link_usable(link) ||
			lgr->terminating ||
			(smc_wr_tx_get_मुक्त_slot_index(link, &idx) != -EBUSY),
			SMC_WR_TX_WAIT_FREE_SLOT_TIME);
		अगर (!rc) अणु
			/* समयout - terminate link */
			smcr_link_करोwn_cond_sched(link);
			वापस -EPIPE;
		पूर्ण
		अगर (idx == link->wr_tx_cnt)
			वापस -EPIPE;
	पूर्ण
	wr_id = smc_wr_tx_get_next_wr_id(link);
	wr_pend = &link->wr_tx_pends[idx];
	wr_pend->wr_id = wr_id;
	wr_pend->handler = handler;
	wr_pend->link = link;
	wr_pend->idx = idx;
	wr_ib = &link->wr_tx_ibs[idx];
	wr_ib->wr_id = wr_id;
	*wr_buf = &link->wr_tx_bufs[idx];
	अगर (wr_rdma_buf)
		*wr_rdma_buf = &link->wr_tx_rdmas[idx];
	*wr_pend_priv = &wr_pend->priv;
	वापस 0;
पूर्ण

पूर्णांक smc_wr_tx_put_slot(काष्ठा smc_link *link,
		       काष्ठा smc_wr_tx_pend_priv *wr_pend_priv)
अणु
	काष्ठा smc_wr_tx_pend *pend;

	pend = container_of(wr_pend_priv, काष्ठा smc_wr_tx_pend, priv);
	अगर (pend->idx < link->wr_tx_cnt) अणु
		u32 idx = pend->idx;

		/* clear the full काष्ठा smc_wr_tx_pend including .priv */
		स_रखो(&link->wr_tx_pends[idx], 0,
		       माप(link->wr_tx_pends[idx]));
		स_रखो(&link->wr_tx_bufs[idx], 0,
		       माप(link->wr_tx_bufs[idx]));
		test_and_clear_bit(idx, link->wr_tx_mask);
		wake_up(&link->wr_tx_रुको);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* Send prepared WR slot via ib_post_send.
 * @priv: poपूर्णांकer to smc_wr_tx_pend_priv identअगरying prepared message buffer
 */
पूर्णांक smc_wr_tx_send(काष्ठा smc_link *link, काष्ठा smc_wr_tx_pend_priv *priv)
अणु
	काष्ठा smc_wr_tx_pend *pend;
	पूर्णांक rc;

	ib_req_notअगरy_cq(link->smcibdev->roce_cq_send,
			 IB_CQ_NEXT_COMP | IB_CQ_REPORT_MISSED_EVENTS);
	pend = container_of(priv, काष्ठा smc_wr_tx_pend, priv);
	rc = ib_post_send(link->roce_qp, &link->wr_tx_ibs[pend->idx], शून्य);
	अगर (rc) अणु
		smc_wr_tx_put_slot(link, priv);
		smcr_link_करोwn_cond_sched(link);
	पूर्ण
	वापस rc;
पूर्ण

/* Send prepared WR slot via ib_post_send and रुको क्रम send completion
 * notअगरication.
 * @priv: poपूर्णांकer to smc_wr_tx_pend_priv identअगरying prepared message buffer
 */
पूर्णांक smc_wr_tx_send_रुको(काष्ठा smc_link *link, काष्ठा smc_wr_tx_pend_priv *priv,
			अचिन्हित दीर्घ समयout)
अणु
	काष्ठा smc_wr_tx_pend *pend;
	पूर्णांक rc;

	pend = container_of(priv, काष्ठा smc_wr_tx_pend, priv);
	pend->compl_requested = 1;
	init_completion(&link->wr_tx_compl[pend->idx]);

	rc = smc_wr_tx_send(link, priv);
	अगर (rc)
		वापस rc;
	/* रुको क्रम completion by smc_wr_tx_process_cqe() */
	rc = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
					&link->wr_tx_compl[pend->idx], समयout);
	अगर (rc <= 0)
		rc = -ENODATA;
	अगर (rc > 0)
		rc = 0;
	वापस rc;
पूर्ण

/* Register a memory region and रुको क्रम result. */
पूर्णांक smc_wr_reg_send(काष्ठा smc_link *link, काष्ठा ib_mr *mr)
अणु
	पूर्णांक rc;

	ib_req_notअगरy_cq(link->smcibdev->roce_cq_send,
			 IB_CQ_NEXT_COMP | IB_CQ_REPORT_MISSED_EVENTS);
	link->wr_reg_state = POSTED;
	link->wr_reg.wr.wr_id = (u64)(uपूर्णांकptr_t)mr;
	link->wr_reg.mr = mr;
	link->wr_reg.key = mr->rkey;
	rc = ib_post_send(link->roce_qp, &link->wr_reg.wr, शून्य);
	अगर (rc)
		वापस rc;

	rc = रुको_event_पूर्णांकerruptible_समयout(link->wr_reg_रुको,
					      (link->wr_reg_state != POSTED),
					      SMC_WR_REG_MR_WAIT_TIME);
	अगर (!rc) अणु
		/* समयout - terminate link */
		smcr_link_करोwn_cond_sched(link);
		वापस -EPIPE;
	पूर्ण
	अगर (rc == -ERESTARTSYS)
		वापस -EINTR;
	चयन (link->wr_reg_state) अणु
	हाल CONFIRMED:
		rc = 0;
		अवरोध;
	हाल FAILED:
		rc = -EIO;
		अवरोध;
	हाल POSTED:
		rc = -EPIPE;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

व्योम smc_wr_tx_dismiss_slots(काष्ठा smc_link *link, u8 wr_tx_hdr_type,
			     smc_wr_tx_filter filter,
			     smc_wr_tx_dismisser dismisser,
			     अचिन्हित दीर्घ data)
अणु
	काष्ठा smc_wr_tx_pend_priv *tx_pend;
	काष्ठा smc_wr_rx_hdr *wr_tx;
	पूर्णांक i;

	क्रम_each_set_bit(i, link->wr_tx_mask, link->wr_tx_cnt) अणु
		wr_tx = (काष्ठा smc_wr_rx_hdr *)&link->wr_tx_bufs[i];
		अगर (wr_tx->type != wr_tx_hdr_type)
			जारी;
		tx_pend = &link->wr_tx_pends[i].priv;
		अगर (filter(tx_pend, data))
			dismisser(tx_pend);
	पूर्ण
पूर्ण

/****************************** receive queue ********************************/

पूर्णांक smc_wr_rx_रेजिस्टर_handler(काष्ठा smc_wr_rx_handler *handler)
अणु
	काष्ठा smc_wr_rx_handler *h_iter;
	पूर्णांक rc = 0;

	spin_lock(&smc_wr_rx_hash_lock);
	hash_क्रम_each_possible(smc_wr_rx_hash, h_iter, list, handler->type) अणु
		अगर (h_iter->type == handler->type) अणु
			rc = -EEXIST;
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	hash_add(smc_wr_rx_hash, &handler->list, handler->type);
out_unlock:
	spin_unlock(&smc_wr_rx_hash_lock);
	वापस rc;
पूर्ण

/* Demultiplex a received work request based on the message type to its handler.
 * Relies on smc_wr_rx_hash having been completely filled beक्रमe any IB WRs,
 * and not being modअगरied any more afterwards so we करोn't need to lock it.
 */
अटल अंतरभूत व्योम smc_wr_rx_demultiplex(काष्ठा ib_wc *wc)
अणु
	काष्ठा smc_link *link = (काष्ठा smc_link *)wc->qp->qp_context;
	काष्ठा smc_wr_rx_handler *handler;
	काष्ठा smc_wr_rx_hdr *wr_rx;
	u64 temp_wr_id;
	u32 index;

	अगर (wc->byte_len < माप(*wr_rx))
		वापस; /* लघु message */
	temp_wr_id = wc->wr_id;
	index = करो_भाग(temp_wr_id, link->wr_rx_cnt);
	wr_rx = (काष्ठा smc_wr_rx_hdr *)&link->wr_rx_bufs[index];
	hash_क्रम_each_possible(smc_wr_rx_hash, handler, list, wr_rx->type) अणु
		अगर (handler->type == wr_rx->type)
			handler->handler(wc, wr_rx);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम smc_wr_rx_process_cqes(काष्ठा ib_wc wc[], पूर्णांक num)
अणु
	काष्ठा smc_link *link;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		link = wc[i].qp->qp_context;
		अगर (wc[i].status == IB_WC_SUCCESS) अणु
			link->wr_rx_tstamp = jअगरfies;
			smc_wr_rx_demultiplex(&wc[i]);
			smc_wr_rx_post(link); /* refill WR RX */
		पूर्ण अन्यथा अणु
			/* handle status errors */
			चयन (wc[i].status) अणु
			हाल IB_WC_RETRY_EXC_ERR:
			हाल IB_WC_RNR_RETRY_EXC_ERR:
			हाल IB_WC_WR_FLUSH_ERR:
				smcr_link_करोwn_cond_sched(link);
				अवरोध;
			शेष:
				smc_wr_rx_post(link); /* refill WR RX */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम smc_wr_rx_tasklet_fn(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा smc_ib_device *dev = from_tasklet(dev, t, recv_tasklet);
	काष्ठा ib_wc wc[SMC_WR_MAX_POLL_CQE];
	पूर्णांक polled = 0;
	पूर्णांक rc;

again:
	polled++;
	करो अणु
		स_रखो(&wc, 0, माप(wc));
		rc = ib_poll_cq(dev->roce_cq_recv, SMC_WR_MAX_POLL_CQE, wc);
		अगर (polled == 1) अणु
			ib_req_notअगरy_cq(dev->roce_cq_recv,
					 IB_CQ_SOLICITED_MASK
					 | IB_CQ_REPORT_MISSED_EVENTS);
		पूर्ण
		अगर (!rc)
			अवरोध;
		smc_wr_rx_process_cqes(&wc[0], rc);
	पूर्ण जबतक (rc > 0);
	अगर (polled == 1)
		जाओ again;
पूर्ण

व्योम smc_wr_rx_cq_handler(काष्ठा ib_cq *ib_cq, व्योम *cq_context)
अणु
	काष्ठा smc_ib_device *dev = (काष्ठा smc_ib_device *)cq_context;

	tasklet_schedule(&dev->recv_tasklet);
पूर्ण

पूर्णांक smc_wr_rx_post_init(काष्ठा smc_link *link)
अणु
	u32 i;
	पूर्णांक rc = 0;

	क्रम (i = 0; i < link->wr_rx_cnt; i++)
		rc = smc_wr_rx_post(link);
	वापस rc;
पूर्ण

/***************************** init, निकास, misc ******************************/

व्योम smc_wr_remember_qp_attr(काष्ठा smc_link *lnk)
अणु
	काष्ठा ib_qp_attr *attr = &lnk->qp_attr;
	काष्ठा ib_qp_init_attr init_attr;

	स_रखो(attr, 0, माप(*attr));
	स_रखो(&init_attr, 0, माप(init_attr));
	ib_query_qp(lnk->roce_qp, attr,
		    IB_QP_STATE |
		    IB_QP_CUR_STATE |
		    IB_QP_PKEY_INDEX |
		    IB_QP_PORT |
		    IB_QP_QKEY |
		    IB_QP_AV |
		    IB_QP_PATH_MTU |
		    IB_QP_TIMEOUT |
		    IB_QP_RETRY_CNT |
		    IB_QP_RNR_RETRY |
		    IB_QP_RQ_PSN |
		    IB_QP_ALT_PATH |
		    IB_QP_MIN_RNR_TIMER |
		    IB_QP_SQ_PSN |
		    IB_QP_PATH_MIG_STATE |
		    IB_QP_CAP |
		    IB_QP_DEST_QPN,
		    &init_attr);

	lnk->wr_tx_cnt = min_t(माप_प्रकार, SMC_WR_BUF_CNT,
			       lnk->qp_attr.cap.max_send_wr);
	lnk->wr_rx_cnt = min_t(माप_प्रकार, SMC_WR_BUF_CNT * 3,
			       lnk->qp_attr.cap.max_recv_wr);
पूर्ण

अटल व्योम smc_wr_init_sge(काष्ठा smc_link *lnk)
अणु
	u32 i;

	क्रम (i = 0; i < lnk->wr_tx_cnt; i++) अणु
		lnk->wr_tx_sges[i].addr =
			lnk->wr_tx_dma_addr + i * SMC_WR_BUF_SIZE;
		lnk->wr_tx_sges[i].length = SMC_WR_TX_SIZE;
		lnk->wr_tx_sges[i].lkey = lnk->roce_pd->local_dma_lkey;
		lnk->wr_tx_rdma_sges[i].tx_rdma_sge[0].wr_tx_rdma_sge[0].lkey =
			lnk->roce_pd->local_dma_lkey;
		lnk->wr_tx_rdma_sges[i].tx_rdma_sge[0].wr_tx_rdma_sge[1].lkey =
			lnk->roce_pd->local_dma_lkey;
		lnk->wr_tx_rdma_sges[i].tx_rdma_sge[1].wr_tx_rdma_sge[0].lkey =
			lnk->roce_pd->local_dma_lkey;
		lnk->wr_tx_rdma_sges[i].tx_rdma_sge[1].wr_tx_rdma_sge[1].lkey =
			lnk->roce_pd->local_dma_lkey;
		lnk->wr_tx_ibs[i].next = शून्य;
		lnk->wr_tx_ibs[i].sg_list = &lnk->wr_tx_sges[i];
		lnk->wr_tx_ibs[i].num_sge = 1;
		lnk->wr_tx_ibs[i].opcode = IB_WR_SEND;
		lnk->wr_tx_ibs[i].send_flags =
			IB_SEND_SIGNALED | IB_SEND_SOLICITED;
		lnk->wr_tx_rdmas[i].wr_tx_rdma[0].wr.opcode = IB_WR_RDMA_WRITE;
		lnk->wr_tx_rdmas[i].wr_tx_rdma[1].wr.opcode = IB_WR_RDMA_WRITE;
		lnk->wr_tx_rdmas[i].wr_tx_rdma[0].wr.sg_list =
			lnk->wr_tx_rdma_sges[i].tx_rdma_sge[0].wr_tx_rdma_sge;
		lnk->wr_tx_rdmas[i].wr_tx_rdma[1].wr.sg_list =
			lnk->wr_tx_rdma_sges[i].tx_rdma_sge[1].wr_tx_rdma_sge;
	पूर्ण
	क्रम (i = 0; i < lnk->wr_rx_cnt; i++) अणु
		lnk->wr_rx_sges[i].addr =
			lnk->wr_rx_dma_addr + i * SMC_WR_BUF_SIZE;
		lnk->wr_rx_sges[i].length = SMC_WR_BUF_SIZE;
		lnk->wr_rx_sges[i].lkey = lnk->roce_pd->local_dma_lkey;
		lnk->wr_rx_ibs[i].next = शून्य;
		lnk->wr_rx_ibs[i].sg_list = &lnk->wr_rx_sges[i];
		lnk->wr_rx_ibs[i].num_sge = 1;
	पूर्ण
	lnk->wr_reg.wr.next = शून्य;
	lnk->wr_reg.wr.num_sge = 0;
	lnk->wr_reg.wr.send_flags = IB_SEND_SIGNALED;
	lnk->wr_reg.wr.opcode = IB_WR_REG_MR;
	lnk->wr_reg.access = IB_ACCESS_LOCAL_WRITE | IB_ACCESS_REMOTE_WRITE;
पूर्ण

व्योम smc_wr_मुक्त_link(काष्ठा smc_link *lnk)
अणु
	काष्ठा ib_device *ibdev;

	अगर (!lnk->smcibdev)
		वापस;
	ibdev = lnk->smcibdev->ibdev;

	अगर (smc_wr_tx_रुको_no_pending_sends(lnk))
		स_रखो(lnk->wr_tx_mask, 0,
		       BITS_TO_LONGS(SMC_WR_BUF_CNT) *
						माप(*lnk->wr_tx_mask));

	अगर (lnk->wr_rx_dma_addr) अणु
		ib_dma_unmap_single(ibdev, lnk->wr_rx_dma_addr,
				    SMC_WR_BUF_SIZE * lnk->wr_rx_cnt,
				    DMA_FROM_DEVICE);
		lnk->wr_rx_dma_addr = 0;
	पूर्ण
	अगर (lnk->wr_tx_dma_addr) अणु
		ib_dma_unmap_single(ibdev, lnk->wr_tx_dma_addr,
				    SMC_WR_BUF_SIZE * lnk->wr_tx_cnt,
				    DMA_TO_DEVICE);
		lnk->wr_tx_dma_addr = 0;
	पूर्ण
पूर्ण

व्योम smc_wr_मुक्त_link_mem(काष्ठा smc_link *lnk)
अणु
	kमुक्त(lnk->wr_tx_compl);
	lnk->wr_tx_compl = शून्य;
	kमुक्त(lnk->wr_tx_pends);
	lnk->wr_tx_pends = शून्य;
	kमुक्त(lnk->wr_tx_mask);
	lnk->wr_tx_mask = शून्य;
	kमुक्त(lnk->wr_tx_sges);
	lnk->wr_tx_sges = शून्य;
	kमुक्त(lnk->wr_tx_rdma_sges);
	lnk->wr_tx_rdma_sges = शून्य;
	kमुक्त(lnk->wr_rx_sges);
	lnk->wr_rx_sges = शून्य;
	kमुक्त(lnk->wr_tx_rdmas);
	lnk->wr_tx_rdmas = शून्य;
	kमुक्त(lnk->wr_rx_ibs);
	lnk->wr_rx_ibs = शून्य;
	kमुक्त(lnk->wr_tx_ibs);
	lnk->wr_tx_ibs = शून्य;
	kमुक्त(lnk->wr_tx_bufs);
	lnk->wr_tx_bufs = शून्य;
	kमुक्त(lnk->wr_rx_bufs);
	lnk->wr_rx_bufs = शून्य;
पूर्ण

पूर्णांक smc_wr_alloc_link_mem(काष्ठा smc_link *link)
अणु
	/* allocate link related memory */
	link->wr_tx_bufs = kसुस्मृति(SMC_WR_BUF_CNT, SMC_WR_BUF_SIZE, GFP_KERNEL);
	अगर (!link->wr_tx_bufs)
		जाओ no_mem;
	link->wr_rx_bufs = kसुस्मृति(SMC_WR_BUF_CNT * 3, SMC_WR_BUF_SIZE,
				   GFP_KERNEL);
	अगर (!link->wr_rx_bufs)
		जाओ no_mem_wr_tx_bufs;
	link->wr_tx_ibs = kसुस्मृति(SMC_WR_BUF_CNT, माप(link->wr_tx_ibs[0]),
				  GFP_KERNEL);
	अगर (!link->wr_tx_ibs)
		जाओ no_mem_wr_rx_bufs;
	link->wr_rx_ibs = kसुस्मृति(SMC_WR_BUF_CNT * 3,
				  माप(link->wr_rx_ibs[0]),
				  GFP_KERNEL);
	अगर (!link->wr_rx_ibs)
		जाओ no_mem_wr_tx_ibs;
	link->wr_tx_rdmas = kसुस्मृति(SMC_WR_BUF_CNT,
				    माप(link->wr_tx_rdmas[0]),
				    GFP_KERNEL);
	अगर (!link->wr_tx_rdmas)
		जाओ no_mem_wr_rx_ibs;
	link->wr_tx_rdma_sges = kसुस्मृति(SMC_WR_BUF_CNT,
					माप(link->wr_tx_rdma_sges[0]),
					GFP_KERNEL);
	अगर (!link->wr_tx_rdma_sges)
		जाओ no_mem_wr_tx_rdmas;
	link->wr_tx_sges = kसुस्मृति(SMC_WR_BUF_CNT, माप(link->wr_tx_sges[0]),
				   GFP_KERNEL);
	अगर (!link->wr_tx_sges)
		जाओ no_mem_wr_tx_rdma_sges;
	link->wr_rx_sges = kसुस्मृति(SMC_WR_BUF_CNT * 3,
				   माप(link->wr_rx_sges[0]),
				   GFP_KERNEL);
	अगर (!link->wr_rx_sges)
		जाओ no_mem_wr_tx_sges;
	link->wr_tx_mask = kसुस्मृति(BITS_TO_LONGS(SMC_WR_BUF_CNT),
				   माप(*link->wr_tx_mask),
				   GFP_KERNEL);
	अगर (!link->wr_tx_mask)
		जाओ no_mem_wr_rx_sges;
	link->wr_tx_pends = kसुस्मृति(SMC_WR_BUF_CNT,
				    माप(link->wr_tx_pends[0]),
				    GFP_KERNEL);
	अगर (!link->wr_tx_pends)
		जाओ no_mem_wr_tx_mask;
	link->wr_tx_compl = kसुस्मृति(SMC_WR_BUF_CNT,
				    माप(link->wr_tx_compl[0]),
				    GFP_KERNEL);
	अगर (!link->wr_tx_compl)
		जाओ no_mem_wr_tx_pends;
	वापस 0;

no_mem_wr_tx_pends:
	kमुक्त(link->wr_tx_pends);
no_mem_wr_tx_mask:
	kमुक्त(link->wr_tx_mask);
no_mem_wr_rx_sges:
	kमुक्त(link->wr_rx_sges);
no_mem_wr_tx_sges:
	kमुक्त(link->wr_tx_sges);
no_mem_wr_tx_rdma_sges:
	kमुक्त(link->wr_tx_rdma_sges);
no_mem_wr_tx_rdmas:
	kमुक्त(link->wr_tx_rdmas);
no_mem_wr_rx_ibs:
	kमुक्त(link->wr_rx_ibs);
no_mem_wr_tx_ibs:
	kमुक्त(link->wr_tx_ibs);
no_mem_wr_rx_bufs:
	kमुक्त(link->wr_rx_bufs);
no_mem_wr_tx_bufs:
	kमुक्त(link->wr_tx_bufs);
no_mem:
	वापस -ENOMEM;
पूर्ण

व्योम smc_wr_हटाओ_dev(काष्ठा smc_ib_device *smcibdev)
अणु
	tasklet_समाप्त(&smcibdev->recv_tasklet);
	tasklet_समाप्त(&smcibdev->send_tasklet);
पूर्ण

व्योम smc_wr_add_dev(काष्ठा smc_ib_device *smcibdev)
अणु
	tasklet_setup(&smcibdev->recv_tasklet, smc_wr_rx_tasklet_fn);
	tasklet_setup(&smcibdev->send_tasklet, smc_wr_tx_tasklet_fn);
पूर्ण

पूर्णांक smc_wr_create_link(काष्ठा smc_link *lnk)
अणु
	काष्ठा ib_device *ibdev = lnk->smcibdev->ibdev;
	पूर्णांक rc = 0;

	smc_wr_tx_set_wr_id(&lnk->wr_tx_id, 0);
	lnk->wr_rx_id = 0;
	lnk->wr_rx_dma_addr = ib_dma_map_single(
		ibdev, lnk->wr_rx_bufs,	SMC_WR_BUF_SIZE * lnk->wr_rx_cnt,
		DMA_FROM_DEVICE);
	अगर (ib_dma_mapping_error(ibdev, lnk->wr_rx_dma_addr)) अणु
		lnk->wr_rx_dma_addr = 0;
		rc = -EIO;
		जाओ out;
	पूर्ण
	lnk->wr_tx_dma_addr = ib_dma_map_single(
		ibdev, lnk->wr_tx_bufs,	SMC_WR_BUF_SIZE * lnk->wr_tx_cnt,
		DMA_TO_DEVICE);
	अगर (ib_dma_mapping_error(ibdev, lnk->wr_tx_dma_addr)) अणु
		rc = -EIO;
		जाओ dma_unmap;
	पूर्ण
	smc_wr_init_sge(lnk);
	स_रखो(lnk->wr_tx_mask, 0,
	       BITS_TO_LONGS(SMC_WR_BUF_CNT) * माप(*lnk->wr_tx_mask));
	init_रुकोqueue_head(&lnk->wr_tx_रुको);
	init_रुकोqueue_head(&lnk->wr_reg_रुको);
	वापस rc;

dma_unmap:
	ib_dma_unmap_single(ibdev, lnk->wr_rx_dma_addr,
			    SMC_WR_BUF_SIZE * lnk->wr_rx_cnt,
			    DMA_FROM_DEVICE);
	lnk->wr_rx_dma_addr = 0;
out:
	वापस rc;
पूर्ण
