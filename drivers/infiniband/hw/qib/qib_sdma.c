<शैली गुरु>
/*
 * Copyright (c) 2012 Intel Corporation. All rights reserved.
 * Copyright (c) 2007 - 2012 QLogic Corporation. All rights reserved.
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
#समावेश <linux/netdevice.h>
#समावेश <linux/moduleparam.h>

#समावेश "qib.h"
#समावेश "qib_common.h"

/* शेष pio off, sdma on */
अटल uलघु sdma_descq_cnt = 256;
module_param_named(sdma_descq_cnt, sdma_descq_cnt, uलघु, S_IRUGO);
MODULE_PARM_DESC(sdma_descq_cnt, "Number of SDMA descq entries");

/*
 * Bits defined in the send DMA descriptor.
 */
#घोषणा SDMA_DESC_LAST          (1ULL << 11)
#घोषणा SDMA_DESC_FIRST         (1ULL << 12)
#घोषणा SDMA_DESC_DMA_HEAD      (1ULL << 13)
#घोषणा SDMA_DESC_USE_LARGE_BUF (1ULL << 14)
#घोषणा SDMA_DESC_INTR          (1ULL << 15)
#घोषणा SDMA_DESC_COUNT_LSB     16
#घोषणा SDMA_DESC_GEN_LSB       30

/* declare all अटलs here rather than keep sorting */
अटल पूर्णांक alloc_sdma(काष्ठा qib_pportdata *);
अटल व्योम sdma_complete(काष्ठा kref *);
अटल व्योम sdma_finalput(काष्ठा qib_sdma_state *);
अटल व्योम sdma_get(काष्ठा qib_sdma_state *);
अटल व्योम sdma_put(काष्ठा qib_sdma_state *);
अटल व्योम sdma_set_state(काष्ठा qib_pportdata *, क्रमागत qib_sdma_states);
अटल व्योम sdma_start_sw_clean_up(काष्ठा qib_pportdata *);
अटल व्योम sdma_sw_clean_up_task(काष्ठा tasklet_काष्ठा *);
अटल व्योम unmap_desc(काष्ठा qib_pportdata *, अचिन्हित);

अटल व्योम sdma_get(काष्ठा qib_sdma_state *ss)
अणु
	kref_get(&ss->kref);
पूर्ण

अटल व्योम sdma_complete(काष्ठा kref *kref)
अणु
	काष्ठा qib_sdma_state *ss =
		container_of(kref, काष्ठा qib_sdma_state, kref);

	complete(&ss->comp);
पूर्ण

अटल व्योम sdma_put(काष्ठा qib_sdma_state *ss)
अणु
	kref_put(&ss->kref, sdma_complete);
पूर्ण

अटल व्योम sdma_finalput(काष्ठा qib_sdma_state *ss)
अणु
	sdma_put(ss);
	रुको_क्रम_completion(&ss->comp);
पूर्ण

/*
 * Complete all the sdma requests on the active list, in the correct
 * order, and with appropriate processing.   Called when cleaning up
 * after sdma shutकरोwn, and when new sdma requests are submitted क्रम
 * a link that is करोwn.   This matches what is करोne क्रम requests
 * that complete normally, it's just the full list.
 *
 * Must be called with sdma_lock held
 */
अटल व्योम clear_sdma_activelist(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_sdma_txreq *txp, *txp_next;

	list_क्रम_each_entry_safe(txp, txp_next, &ppd->sdma_activelist, list) अणु
		list_del_init(&txp->list);
		अगर (txp->flags & QIB_SDMA_TXREQ_F_FREEDESC) अणु
			अचिन्हित idx;

			idx = txp->start_idx;
			जबतक (idx != txp->next_descq_idx) अणु
				unmap_desc(ppd, idx);
				अगर (++idx == ppd->sdma_descq_cnt)
					idx = 0;
			पूर्ण
		पूर्ण
		अगर (txp->callback)
			(*txp->callback)(txp, QIB_SDMA_TXREQ_S_ABORTED);
	पूर्ण
पूर्ण

अटल व्योम sdma_sw_clean_up_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा qib_pportdata *ppd = from_tasklet(ppd, t,
						 sdma_sw_clean_up_task);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ppd->sdma_lock, flags);

	/*
	 * At this poपूर्णांक, the following should always be true:
	 * - We are halted, so no more descriptors are getting retired.
	 * - We are not running, so no one is submitting new work.
	 * - Only we can send the e40_sw_cleaned, so we can't start
	 *   running again until we say so.  So, the active list and
	 *   descq are ours to play with.
	 */

	/* Process all retired requests. */
	qib_sdma_make_progress(ppd);

	clear_sdma_activelist(ppd);

	/*
	 * Resync count of added and हटाओd.  It is VERY important that
	 * sdma_descq_हटाओd NEVER decrement - user_sdma depends on it.
	 */
	ppd->sdma_descq_हटाओd = ppd->sdma_descq_added;

	/*
	 * Reset our notion of head and tail.
	 * Note that the HW रेजिस्टरs will be reset when चयनing states
	 * due to calling __qib_sdma_process_event() below.
	 */
	ppd->sdma_descq_tail = 0;
	ppd->sdma_descq_head = 0;
	ppd->sdma_head_dma[0] = 0;
	ppd->sdma_generation = 0;

	__qib_sdma_process_event(ppd, qib_sdma_event_e40_sw_cleaned);

	spin_unlock_irqrestore(&ppd->sdma_lock, flags);
पूर्ण

/*
 * This is called when changing to state qib_sdma_state_s10_hw_start_up_रुको
 * as a result of send buffer errors or send DMA descriptor errors.
 * We want to disarm the buffers in these हालs.
 */
अटल व्योम sdma_hw_start_up(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_sdma_state *ss = &ppd->sdma_state;
	अचिन्हित bufno;

	क्रम (bufno = ss->first_sendbuf; bufno < ss->last_sendbuf; ++bufno)
		ppd->dd->f_sendctrl(ppd, QIB_SENDCTRL_DISARM_BUF(bufno));

	ppd->dd->f_sdma_hw_start_up(ppd);
पूर्ण

अटल व्योम sdma_sw_tear_करोwn(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_sdma_state *ss = &ppd->sdma_state;

	/* Releasing this reference means the state machine has stopped. */
	sdma_put(ss);
पूर्ण

अटल व्योम sdma_start_sw_clean_up(काष्ठा qib_pportdata *ppd)
अणु
	tasklet_hi_schedule(&ppd->sdma_sw_clean_up_task);
पूर्ण

अटल व्योम sdma_set_state(काष्ठा qib_pportdata *ppd,
	क्रमागत qib_sdma_states next_state)
अणु
	काष्ठा qib_sdma_state *ss = &ppd->sdma_state;
	काष्ठा sdma_set_state_action *action = ss->set_state_action;
	अचिन्हित op = 0;

	/* debugging bookkeeping */
	ss->previous_state = ss->current_state;
	ss->previous_op = ss->current_op;

	ss->current_state = next_state;

	अगर (action[next_state].op_enable)
		op |= QIB_SDMA_SENDCTRL_OP_ENABLE;

	अगर (action[next_state].op_पूर्णांकenable)
		op |= QIB_SDMA_SENDCTRL_OP_INTENABLE;

	अगर (action[next_state].op_halt)
		op |= QIB_SDMA_SENDCTRL_OP_HALT;

	अगर (action[next_state].op_drain)
		op |= QIB_SDMA_SENDCTRL_OP_DRAIN;

	अगर (action[next_state].go_s99_running_tofalse)
		ss->go_s99_running = 0;

	अगर (action[next_state].go_s99_running_totrue)
		ss->go_s99_running = 1;

	ss->current_op = op;

	ppd->dd->f_sdma_sendctrl(ppd, ss->current_op);
पूर्ण

अटल व्योम unmap_desc(काष्ठा qib_pportdata *ppd, अचिन्हित head)
अणु
	__le64 *descqp = &ppd->sdma_descq[head].qw[0];
	u64 desc[2];
	dma_addr_t addr;
	माप_प्रकार len;

	desc[0] = le64_to_cpu(descqp[0]);
	desc[1] = le64_to_cpu(descqp[1]);

	addr = (desc[1] << 32) | (desc[0] >> 32);
	len = (desc[0] >> 14) & (0x7ffULL << 2);
	dma_unmap_single(&ppd->dd->pcidev->dev, addr, len, DMA_TO_DEVICE);
पूर्ण

अटल पूर्णांक alloc_sdma(काष्ठा qib_pportdata *ppd)
अणु
	ppd->sdma_descq_cnt = sdma_descq_cnt;
	अगर (!ppd->sdma_descq_cnt)
		ppd->sdma_descq_cnt = 256;

	/* Allocate memory क्रम SendDMA descriptor FIFO */
	ppd->sdma_descq = dma_alloc_coherent(&ppd->dd->pcidev->dev,
		ppd->sdma_descq_cnt * माप(u64[2]), &ppd->sdma_descq_phys,
		GFP_KERNEL);

	अगर (!ppd->sdma_descq) अणु
		qib_dev_err(ppd->dd,
			"failed to allocate SendDMA descriptor FIFO memory\n");
		जाओ bail;
	पूर्ण

	/* Allocate memory क्रम DMA of head रेजिस्टर to memory */
	ppd->sdma_head_dma = dma_alloc_coherent(&ppd->dd->pcidev->dev,
		PAGE_SIZE, &ppd->sdma_head_phys, GFP_KERNEL);
	अगर (!ppd->sdma_head_dma) अणु
		qib_dev_err(ppd->dd,
			"failed to allocate SendDMA head memory\n");
		जाओ cleanup_descq;
	पूर्ण
	ppd->sdma_head_dma[0] = 0;
	वापस 0;

cleanup_descq:
	dma_मुक्त_coherent(&ppd->dd->pcidev->dev,
		ppd->sdma_descq_cnt * माप(u64[2]), (व्योम *)ppd->sdma_descq,
		ppd->sdma_descq_phys);
	ppd->sdma_descq = शून्य;
	ppd->sdma_descq_phys = 0;
bail:
	ppd->sdma_descq_cnt = 0;
	वापस -ENOMEM;
पूर्ण

अटल व्योम मुक्त_sdma(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;

	अगर (ppd->sdma_head_dma) अणु
		dma_मुक्त_coherent(&dd->pcidev->dev, PAGE_SIZE,
				  (व्योम *)ppd->sdma_head_dma,
				  ppd->sdma_head_phys);
		ppd->sdma_head_dma = शून्य;
		ppd->sdma_head_phys = 0;
	पूर्ण

	अगर (ppd->sdma_descq) अणु
		dma_मुक्त_coherent(&dd->pcidev->dev,
				  ppd->sdma_descq_cnt * माप(u64[2]),
				  ppd->sdma_descq, ppd->sdma_descq_phys);
		ppd->sdma_descq = शून्य;
		ppd->sdma_descq_phys = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम make_sdma_desc(काष्ठा qib_pportdata *ppd,
				  u64 *sdmadesc, u64 addr, u64 dwlen,
				  u64 dwoffset)
अणु

	WARN_ON(addr & 3);
	/* SDmaPhyAddr[47:32] */
	sdmadesc[1] = addr >> 32;
	/* SDmaPhyAddr[31:0] */
	sdmadesc[0] = (addr & 0xfffffffcULL) << 32;
	/* SDmaGeneration[1:0] */
	sdmadesc[0] |= (ppd->sdma_generation & 3ULL) <<
		SDMA_DESC_GEN_LSB;
	/* SDmaDwordCount[10:0] */
	sdmadesc[0] |= (dwlen & 0x7ffULL) << SDMA_DESC_COUNT_LSB;
	/* SDmaBufOffset[12:2] */
	sdmadesc[0] |= dwoffset & 0x7ffULL;
पूर्ण

/* sdma_lock must be held */
पूर्णांक qib_sdma_make_progress(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा list_head *lp = शून्य;
	काष्ठा qib_sdma_txreq *txp = शून्य;
	काष्ठा qib_devdata *dd = ppd->dd;
	पूर्णांक progress = 0;
	u16 hwhead;
	u16 idx = 0;

	hwhead = dd->f_sdma_gethead(ppd);

	/* The reason क्रम some of the complनिकासy of this code is that
	 * not all descriptors have corresponding txps.  So, we have to
	 * be able to skip over descs until we wander पूर्णांकo the range of
	 * the next txp on the list.
	 */

	अगर (!list_empty(&ppd->sdma_activelist)) अणु
		lp = ppd->sdma_activelist.next;
		txp = list_entry(lp, काष्ठा qib_sdma_txreq, list);
		idx = txp->start_idx;
	पूर्ण

	जबतक (ppd->sdma_descq_head != hwhead) अणु
		/* अगर desc is part of this txp, unmap अगर needed */
		अगर (txp && (txp->flags & QIB_SDMA_TXREQ_F_FREEDESC) &&
		    (idx == ppd->sdma_descq_head)) अणु
			unmap_desc(ppd, ppd->sdma_descq_head);
			अगर (++idx == ppd->sdma_descq_cnt)
				idx = 0;
		पूर्ण

		/* increment dequed desc count */
		ppd->sdma_descq_हटाओd++;

		/* advance head, wrap अगर needed */
		अगर (++ppd->sdma_descq_head == ppd->sdma_descq_cnt)
			ppd->sdma_descq_head = 0;

		/* अगर now past this txp's descs, करो the callback */
		अगर (txp && txp->next_descq_idx == ppd->sdma_descq_head) अणु
			/* हटाओ from active list */
			list_del_init(&txp->list);
			अगर (txp->callback)
				(*txp->callback)(txp, QIB_SDMA_TXREQ_S_OK);
			/* see अगर there is another txp */
			अगर (list_empty(&ppd->sdma_activelist))
				txp = शून्य;
			अन्यथा अणु
				lp = ppd->sdma_activelist.next;
				txp = list_entry(lp, काष्ठा qib_sdma_txreq,
					list);
				idx = txp->start_idx;
			पूर्ण
		पूर्ण
		progress = 1;
	पूर्ण
	अगर (progress)
		qib_verbs_sdma_desc_avail(ppd, qib_sdma_descq_मुक्तcnt(ppd));
	वापस progress;
पूर्ण

/*
 * This is called from पूर्णांकerrupt context.
 */
व्योम qib_sdma_पूर्णांकr(काष्ठा qib_pportdata *ppd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ppd->sdma_lock, flags);

	__qib_sdma_पूर्णांकr(ppd);

	spin_unlock_irqrestore(&ppd->sdma_lock, flags);
पूर्ण

व्योम __qib_sdma_पूर्णांकr(काष्ठा qib_pportdata *ppd)
अणु
	अगर (__qib_sdma_running(ppd)) अणु
		qib_sdma_make_progress(ppd);
		अगर (!list_empty(&ppd->sdma_userpending))
			qib_user_sdma_send_desc(ppd, &ppd->sdma_userpending);
	पूर्ण
पूर्ण

पूर्णांक qib_setup_sdma(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	ret = alloc_sdma(ppd);
	अगर (ret)
		जाओ bail;

	/* set consistent sdma state */
	ppd->dd->f_sdma_init_early(ppd);
	spin_lock_irqsave(&ppd->sdma_lock, flags);
	sdma_set_state(ppd, qib_sdma_state_s00_hw_करोwn);
	spin_unlock_irqrestore(&ppd->sdma_lock, flags);

	/* set up reference counting */
	kref_init(&ppd->sdma_state.kref);
	init_completion(&ppd->sdma_state.comp);

	ppd->sdma_generation = 0;
	ppd->sdma_descq_head = 0;
	ppd->sdma_descq_हटाओd = 0;
	ppd->sdma_descq_added = 0;

	ppd->sdma_पूर्णांकrequest = 0;
	INIT_LIST_HEAD(&ppd->sdma_userpending);

	INIT_LIST_HEAD(&ppd->sdma_activelist);

	tasklet_setup(&ppd->sdma_sw_clean_up_task, sdma_sw_clean_up_task);

	ret = dd->f_init_sdma_regs(ppd);
	अगर (ret)
		जाओ bail_alloc;

	qib_sdma_process_event(ppd, qib_sdma_event_e10_go_hw_start);

	वापस 0;

bail_alloc:
	qib_tearकरोwn_sdma(ppd);
bail:
	वापस ret;
पूर्ण

व्योम qib_tearकरोwn_sdma(काष्ठा qib_pportdata *ppd)
अणु
	qib_sdma_process_event(ppd, qib_sdma_event_e00_go_hw_करोwn);

	/*
	 * This रुकोs क्रम the state machine to निकास so it is not
	 * necessary to समाप्त the sdma_sw_clean_up_task to make sure
	 * it is not running.
	 */
	sdma_finalput(&ppd->sdma_state);

	मुक्त_sdma(ppd);
पूर्ण

पूर्णांक qib_sdma_running(काष्ठा qib_pportdata *ppd)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ppd->sdma_lock, flags);
	ret = __qib_sdma_running(ppd);
	spin_unlock_irqrestore(&ppd->sdma_lock, flags);

	वापस ret;
पूर्ण

/*
 * Complete a request when sdma not running; likely only request
 * but to simplअगरy the code, always queue it, then process the full
 * activelist.  We process the entire list to ensure that this particular
 * request करोes get it's callback, but in the correct order.
 * Must be called with sdma_lock held
 */
अटल व्योम complete_sdma_err_req(काष्ठा qib_pportdata *ppd,
				  काष्ठा qib_verbs_txreq *tx)
अणु
	काष्ठा qib_qp_priv *priv = tx->qp->priv;

	atomic_inc(&priv->s_dma_busy);
	/* no sdma descriptors, so no unmap_desc */
	tx->txreq.start_idx = 0;
	tx->txreq.next_descq_idx = 0;
	list_add_tail(&tx->txreq.list, &ppd->sdma_activelist);
	clear_sdma_activelist(ppd);
पूर्ण

/*
 * This function queues one IB packet onto the send DMA queue per call.
 * The caller is responsible क्रम checking:
 * 1) The number of send DMA descriptor entries is less than the size of
 *    the descriptor queue.
 * 2) The IB SGE addresses and lengths are 32-bit aligned
 *    (except possibly the last SGE's length)
 * 3) The SGE addresses are suitable क्रम passing to dma_map_single().
 */
पूर्णांक qib_sdma_verbs_send(काष्ठा qib_pportdata *ppd,
			काष्ठा rvt_sge_state *ss, u32 dwords,
			काष्ठा qib_verbs_txreq *tx)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rvt_sge *sge;
	काष्ठा rvt_qp *qp;
	पूर्णांक ret = 0;
	u16 tail;
	__le64 *descqp;
	u64 sdmadesc[2];
	u32 dwoffset;
	dma_addr_t addr;
	काष्ठा qib_qp_priv *priv;

	spin_lock_irqsave(&ppd->sdma_lock, flags);

retry:
	अगर (unlikely(!__qib_sdma_running(ppd))) अणु
		complete_sdma_err_req(ppd, tx);
		जाओ unlock;
	पूर्ण

	अगर (tx->txreq.sg_count > qib_sdma_descq_मुक्तcnt(ppd)) अणु
		अगर (qib_sdma_make_progress(ppd))
			जाओ retry;
		अगर (ppd->dd->flags & QIB_HAS_SDMA_TIMEOUT)
			ppd->dd->f_sdma_set_desc_cnt(ppd,
					ppd->sdma_descq_cnt / 2);
		जाओ busy;
	पूर्ण

	dwoffset = tx->hdr_dwords;
	make_sdma_desc(ppd, sdmadesc, (u64) tx->txreq.addr, dwoffset, 0);

	sdmadesc[0] |= SDMA_DESC_FIRST;
	अगर (tx->txreq.flags & QIB_SDMA_TXREQ_F_USELARGEBUF)
		sdmadesc[0] |= SDMA_DESC_USE_LARGE_BUF;

	/* ग_लिखो to the descq */
	tail = ppd->sdma_descq_tail;
	descqp = &ppd->sdma_descq[tail].qw[0];
	*descqp++ = cpu_to_le64(sdmadesc[0]);
	*descqp++ = cpu_to_le64(sdmadesc[1]);

	/* increment the tail */
	अगर (++tail == ppd->sdma_descq_cnt) अणु
		tail = 0;
		descqp = &ppd->sdma_descq[0].qw[0];
		++ppd->sdma_generation;
	पूर्ण

	tx->txreq.start_idx = tail;

	sge = &ss->sge;
	जबतक (dwords) अणु
		u32 dw;
		u32 len = rvt_get_sge_length(sge, dwords << 2);

		dw = (len + 3) >> 2;
		addr = dma_map_single(&ppd->dd->pcidev->dev, sge->vaddr,
				      dw << 2, DMA_TO_DEVICE);
		अगर (dma_mapping_error(&ppd->dd->pcidev->dev, addr)) अणु
			ret = -ENOMEM;
			जाओ unmap;
		पूर्ण
		sdmadesc[0] = 0;
		make_sdma_desc(ppd, sdmadesc, (u64) addr, dw, dwoffset);
		/* SDmaUseLargeBuf has to be set in every descriptor */
		अगर (tx->txreq.flags & QIB_SDMA_TXREQ_F_USELARGEBUF)
			sdmadesc[0] |= SDMA_DESC_USE_LARGE_BUF;
		/* ग_लिखो to the descq */
		*descqp++ = cpu_to_le64(sdmadesc[0]);
		*descqp++ = cpu_to_le64(sdmadesc[1]);

		/* increment the tail */
		अगर (++tail == ppd->sdma_descq_cnt) अणु
			tail = 0;
			descqp = &ppd->sdma_descq[0].qw[0];
			++ppd->sdma_generation;
		पूर्ण
		rvt_update_sge(ss, len, false);
		dwoffset += dw;
		dwords -= dw;
	पूर्ण

	अगर (!tail)
		descqp = &ppd->sdma_descq[ppd->sdma_descq_cnt].qw[0];
	descqp -= 2;
	descqp[0] |= cpu_to_le64(SDMA_DESC_LAST);
	अगर (tx->txreq.flags & QIB_SDMA_TXREQ_F_HEADTOHOST)
		descqp[0] |= cpu_to_le64(SDMA_DESC_DMA_HEAD);
	अगर (tx->txreq.flags & QIB_SDMA_TXREQ_F_INTREQ)
		descqp[0] |= cpu_to_le64(SDMA_DESC_INTR);
	priv = tx->qp->priv;
	atomic_inc(&priv->s_dma_busy);
	tx->txreq.next_descq_idx = tail;
	ppd->dd->f_sdma_update_tail(ppd, tail);
	ppd->sdma_descq_added += tx->txreq.sg_count;
	list_add_tail(&tx->txreq.list, &ppd->sdma_activelist);
	जाओ unlock;

unmap:
	क्रम (;;) अणु
		अगर (!tail)
			tail = ppd->sdma_descq_cnt - 1;
		अन्यथा
			tail--;
		अगर (tail == ppd->sdma_descq_tail)
			अवरोध;
		unmap_desc(ppd, tail);
	पूर्ण
	qp = tx->qp;
	priv = qp->priv;
	qib_put_txreq(tx);
	spin_lock(&qp->r_lock);
	spin_lock(&qp->s_lock);
	अगर (qp->ibqp.qp_type == IB_QPT_RC) अणु
		/* XXX what about error sending RDMA पढ़ो responses? */
		अगर (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK)
			rvt_error_qp(qp, IB_WC_GENERAL_ERR);
	पूर्ण अन्यथा अगर (qp->s_wqe)
		rvt_send_complete(qp, qp->s_wqe, IB_WC_GENERAL_ERR);
	spin_unlock(&qp->s_lock);
	spin_unlock(&qp->r_lock);
	/* वापस zero to process the next send work request */
	जाओ unlock;

busy:
	qp = tx->qp;
	priv = qp->priv;
	spin_lock(&qp->s_lock);
	अगर (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) अणु
		काष्ठा qib_ibdev *dev;

		/*
		 * If we couldn't queue the DMA request, save the info
		 * and try again later rather than destroying the
		 * buffer and unकरोing the side effects of the copy.
		 */
		tx->ss = ss;
		tx->dwords = dwords;
		priv->s_tx = tx;
		dev = &ppd->dd->verbs_dev;
		spin_lock(&dev->rdi.pending_lock);
		अगर (list_empty(&priv->ioरुको)) अणु
			काष्ठा qib_ibport *ibp;

			ibp = &ppd->ibport_data;
			ibp->rvp.n_dmaरुको++;
			qp->s_flags |= RVT_S_WAIT_DMA_DESC;
			list_add_tail(&priv->ioरुको, &dev->dmaरुको);
		पूर्ण
		spin_unlock(&dev->rdi.pending_lock);
		qp->s_flags &= ~RVT_S_BUSY;
		spin_unlock(&qp->s_lock);
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		spin_unlock(&qp->s_lock);
		qib_put_txreq(tx);
	पूर्ण
unlock:
	spin_unlock_irqrestore(&ppd->sdma_lock, flags);
	वापस ret;
पूर्ण

/*
 * sdma_lock should be acquired beक्रमe calling this routine
 */
व्योम dump_sdma_state(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_sdma_desc *descq;
	काष्ठा qib_sdma_txreq *txp, *txpnext;
	__le64 *descqp;
	u64 desc[2];
	u64 addr;
	u16 gen, dwlen, dwoffset;
	u16 head, tail, cnt;

	head = ppd->sdma_descq_head;
	tail = ppd->sdma_descq_tail;
	cnt = qib_sdma_descq_मुक्तcnt(ppd);
	descq = ppd->sdma_descq;

	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA ppd->sdma_descq_head: %u\n", head);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA ppd->sdma_descq_tail: %u\n", tail);
	qib_dev_porterr(ppd->dd, ppd->port,
		"SDMA sdma_descq_freecnt: %u\n", cnt);

	/* prपूर्णांक info क्रम each entry in the descriptor queue */
	जबतक (head != tail) अणु
		अक्षर flags[6] = अणु 'x', 'x', 'x', 'x', 'x', 0 पूर्ण;

		descqp = &descq[head].qw[0];
		desc[0] = le64_to_cpu(descqp[0]);
		desc[1] = le64_to_cpu(descqp[1]);
		flags[0] = (desc[0] & 1<<15) ? 'I' : '-';
		flags[1] = (desc[0] & 1<<14) ? 'L' : 'S';
		flags[2] = (desc[0] & 1<<13) ? 'H' : '-';
		flags[3] = (desc[0] & 1<<12) ? 'F' : '-';
		flags[4] = (desc[0] & 1<<11) ? 'L' : '-';
		addr = (desc[1] << 32) | ((desc[0] >> 32) & 0xfffffffcULL);
		gen = (desc[0] >> 30) & 3ULL;
		dwlen = (desc[0] >> 14) & (0x7ffULL << 2);
		dwoffset = (desc[0] & 0x7ffULL) << 2;
		qib_dev_porterr(ppd->dd, ppd->port,
			"SDMA sdmadesc[%u]: flags:%s addr:0x%016llx gen:%u len:%u bytes offset:%u bytes\n",
			 head, flags, addr, gen, dwlen, dwoffset);
		अगर (++head == ppd->sdma_descq_cnt)
			head = 0;
	पूर्ण

	/* prपूर्णांक dma descriptor indices from the TX requests */
	list_क्रम_each_entry_safe(txp, txpnext, &ppd->sdma_activelist,
				 list)
		qib_dev_porterr(ppd->dd, ppd->port,
			"SDMA txp->start_idx: %u txp->next_descq_idx: %u\n",
			txp->start_idx, txp->next_descq_idx);
पूर्ण

व्योम qib_sdma_process_event(काष्ठा qib_pportdata *ppd,
	क्रमागत qib_sdma_events event)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ppd->sdma_lock, flags);

	__qib_sdma_process_event(ppd, event);

	अगर (ppd->sdma_state.current_state == qib_sdma_state_s99_running)
		qib_verbs_sdma_desc_avail(ppd, qib_sdma_descq_मुक्तcnt(ppd));

	spin_unlock_irqrestore(&ppd->sdma_lock, flags);
पूर्ण

व्योम __qib_sdma_process_event(काष्ठा qib_pportdata *ppd,
	क्रमागत qib_sdma_events event)
अणु
	काष्ठा qib_sdma_state *ss = &ppd->sdma_state;

	चयन (ss->current_state) अणु
	हाल qib_sdma_state_s00_hw_करोwn:
		चयन (event) अणु
		हाल qib_sdma_event_e00_go_hw_करोwn:
			अवरोध;
		हाल qib_sdma_event_e30_go_running:
			/*
			 * If करोwn, but running requested (usually result
			 * of link up, then we need to start up.
			 * This can happen when hw करोwn is requested जबतक
			 * bringing the link up with traffic active on
			 * 7220, e.g. */
			ss->go_s99_running = 1;
			fallthrough;	/* and start dma engine */
		हाल qib_sdma_event_e10_go_hw_start:
			/* This reference means the state machine is started */
			sdma_get(&ppd->sdma_state);
			sdma_set_state(ppd,
				       qib_sdma_state_s10_hw_start_up_रुको);
			अवरोध;
		हाल qib_sdma_event_e20_hw_started:
			अवरोध;
		हाल qib_sdma_event_e40_sw_cleaned:
			sdma_sw_tear_करोwn(ppd);
			अवरोध;
		हाल qib_sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल qib_sdma_event_e60_hw_halted:
			अवरोध;
		हाल qib_sdma_event_e70_go_idle:
			अवरोध;
		हाल qib_sdma_event_e7220_err_halted:
			अवरोध;
		हाल qib_sdma_event_e7322_err_halted:
			अवरोध;
		हाल qib_sdma_event_e90_समयr_tick:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल qib_sdma_state_s10_hw_start_up_रुको:
		चयन (event) अणु
		हाल qib_sdma_event_e00_go_hw_करोwn:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_करोwn);
			sdma_sw_tear_करोwn(ppd);
			अवरोध;
		हाल qib_sdma_event_e10_go_hw_start:
			अवरोध;
		हाल qib_sdma_event_e20_hw_started:
			sdma_set_state(ppd, ss->go_s99_running ?
				       qib_sdma_state_s99_running :
				       qib_sdma_state_s20_idle);
			अवरोध;
		हाल qib_sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			अवरोध;
		हाल qib_sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल qib_sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल qib_sdma_event_e60_hw_halted:
			अवरोध;
		हाल qib_sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			अवरोध;
		हाल qib_sdma_event_e7220_err_halted:
			अवरोध;
		हाल qib_sdma_event_e7322_err_halted:
			अवरोध;
		हाल qib_sdma_event_e90_समयr_tick:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल qib_sdma_state_s20_idle:
		चयन (event) अणु
		हाल qib_sdma_event_e00_go_hw_करोwn:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_करोwn);
			sdma_sw_tear_करोwn(ppd);
			अवरोध;
		हाल qib_sdma_event_e10_go_hw_start:
			अवरोध;
		हाल qib_sdma_event_e20_hw_started:
			अवरोध;
		हाल qib_sdma_event_e30_go_running:
			sdma_set_state(ppd, qib_sdma_state_s99_running);
			ss->go_s99_running = 1;
			अवरोध;
		हाल qib_sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल qib_sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल qib_sdma_event_e60_hw_halted:
			अवरोध;
		हाल qib_sdma_event_e70_go_idle:
			अवरोध;
		हाल qib_sdma_event_e7220_err_halted:
			अवरोध;
		हाल qib_sdma_event_e7322_err_halted:
			अवरोध;
		हाल qib_sdma_event_e90_समयr_tick:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल qib_sdma_state_s30_sw_clean_up_रुको:
		चयन (event) अणु
		हाल qib_sdma_event_e00_go_hw_करोwn:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_करोwn);
			अवरोध;
		हाल qib_sdma_event_e10_go_hw_start:
			अवरोध;
		हाल qib_sdma_event_e20_hw_started:
			अवरोध;
		हाल qib_sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			अवरोध;
		हाल qib_sdma_event_e40_sw_cleaned:
			sdma_set_state(ppd,
				       qib_sdma_state_s10_hw_start_up_रुको);
			sdma_hw_start_up(ppd);
			अवरोध;
		हाल qib_sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल qib_sdma_event_e60_hw_halted:
			अवरोध;
		हाल qib_sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			अवरोध;
		हाल qib_sdma_event_e7220_err_halted:
			अवरोध;
		हाल qib_sdma_event_e7322_err_halted:
			अवरोध;
		हाल qib_sdma_event_e90_समयr_tick:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल qib_sdma_state_s40_hw_clean_up_रुको:
		चयन (event) अणु
		हाल qib_sdma_event_e00_go_hw_करोwn:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_करोwn);
			sdma_start_sw_clean_up(ppd);
			अवरोध;
		हाल qib_sdma_event_e10_go_hw_start:
			अवरोध;
		हाल qib_sdma_event_e20_hw_started:
			अवरोध;
		हाल qib_sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			अवरोध;
		हाल qib_sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल qib_sdma_event_e50_hw_cleaned:
			sdma_set_state(ppd,
				       qib_sdma_state_s30_sw_clean_up_रुको);
			sdma_start_sw_clean_up(ppd);
			अवरोध;
		हाल qib_sdma_event_e60_hw_halted:
			अवरोध;
		हाल qib_sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			अवरोध;
		हाल qib_sdma_event_e7220_err_halted:
			अवरोध;
		हाल qib_sdma_event_e7322_err_halted:
			अवरोध;
		हाल qib_sdma_event_e90_समयr_tick:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल qib_sdma_state_s50_hw_halt_रुको:
		चयन (event) अणु
		हाल qib_sdma_event_e00_go_hw_करोwn:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_करोwn);
			sdma_start_sw_clean_up(ppd);
			अवरोध;
		हाल qib_sdma_event_e10_go_hw_start:
			अवरोध;
		हाल qib_sdma_event_e20_hw_started:
			अवरोध;
		हाल qib_sdma_event_e30_go_running:
			ss->go_s99_running = 1;
			अवरोध;
		हाल qib_sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल qib_sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल qib_sdma_event_e60_hw_halted:
			sdma_set_state(ppd,
				       qib_sdma_state_s40_hw_clean_up_रुको);
			ppd->dd->f_sdma_hw_clean_up(ppd);
			अवरोध;
		हाल qib_sdma_event_e70_go_idle:
			ss->go_s99_running = 0;
			अवरोध;
		हाल qib_sdma_event_e7220_err_halted:
			अवरोध;
		हाल qib_sdma_event_e7322_err_halted:
			अवरोध;
		हाल qib_sdma_event_e90_समयr_tick:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल qib_sdma_state_s99_running:
		चयन (event) अणु
		हाल qib_sdma_event_e00_go_hw_करोwn:
			sdma_set_state(ppd, qib_sdma_state_s00_hw_करोwn);
			sdma_start_sw_clean_up(ppd);
			अवरोध;
		हाल qib_sdma_event_e10_go_hw_start:
			अवरोध;
		हाल qib_sdma_event_e20_hw_started:
			अवरोध;
		हाल qib_sdma_event_e30_go_running:
			अवरोध;
		हाल qib_sdma_event_e40_sw_cleaned:
			अवरोध;
		हाल qib_sdma_event_e50_hw_cleaned:
			अवरोध;
		हाल qib_sdma_event_e60_hw_halted:
			sdma_set_state(ppd,
				       qib_sdma_state_s30_sw_clean_up_रुको);
			sdma_start_sw_clean_up(ppd);
			अवरोध;
		हाल qib_sdma_event_e70_go_idle:
			sdma_set_state(ppd, qib_sdma_state_s50_hw_halt_रुको);
			ss->go_s99_running = 0;
			अवरोध;
		हाल qib_sdma_event_e7220_err_halted:
			sdma_set_state(ppd,
				       qib_sdma_state_s30_sw_clean_up_रुको);
			sdma_start_sw_clean_up(ppd);
			अवरोध;
		हाल qib_sdma_event_e7322_err_halted:
			sdma_set_state(ppd, qib_sdma_state_s50_hw_halt_रुको);
			अवरोध;
		हाल qib_sdma_event_e90_समयr_tick:
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	ss->last_event = event;
पूर्ण
