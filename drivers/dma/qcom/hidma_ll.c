<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm Technologies HIDMA DMA engine low level code
 *
 * Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/dmaengine.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/atomic.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/bitops.h>

#समावेश "hidma.h"

#घोषणा HIDMA_EVRE_SIZE			16	/* each EVRE is 16 bytes */

#घोषणा HIDMA_TRCA_CTRLSTS_REG			0x000
#घोषणा HIDMA_TRCA_RING_LOW_REG		0x008
#घोषणा HIDMA_TRCA_RING_HIGH_REG		0x00C
#घोषणा HIDMA_TRCA_RING_LEN_REG		0x010
#घोषणा HIDMA_TRCA_DOORBELL_REG		0x400

#घोषणा HIDMA_EVCA_CTRLSTS_REG			0x000
#घोषणा HIDMA_EVCA_INTCTRL_REG			0x004
#घोषणा HIDMA_EVCA_RING_LOW_REG		0x008
#घोषणा HIDMA_EVCA_RING_HIGH_REG		0x00C
#घोषणा HIDMA_EVCA_RING_LEN_REG		0x010
#घोषणा HIDMA_EVCA_WRITE_PTR_REG		0x020
#घोषणा HIDMA_EVCA_DOORBELL_REG		0x400

#घोषणा HIDMA_EVCA_IRQ_STAT_REG		0x100
#घोषणा HIDMA_EVCA_IRQ_CLR_REG			0x108
#घोषणा HIDMA_EVCA_IRQ_EN_REG			0x110

#घोषणा HIDMA_EVRE_CFG_IDX			0

#घोषणा HIDMA_EVRE_ERRINFO_BIT_POS		24
#घोषणा HIDMA_EVRE_CODE_BIT_POS		28

#घोषणा HIDMA_EVRE_ERRINFO_MASK		GENMASK(3, 0)
#घोषणा HIDMA_EVRE_CODE_MASK			GENMASK(3, 0)

#घोषणा HIDMA_CH_CONTROL_MASK			GENMASK(7, 0)
#घोषणा HIDMA_CH_STATE_MASK			GENMASK(7, 0)
#घोषणा HIDMA_CH_STATE_BIT_POS			0x8

#घोषणा HIDMA_IRQ_EV_CH_EOB_IRQ_BIT_POS	0
#घोषणा HIDMA_IRQ_EV_CH_WR_RESP_BIT_POS	1
#घोषणा HIDMA_IRQ_TR_CH_TRE_RD_RSP_ER_BIT_POS	9
#घोषणा HIDMA_IRQ_TR_CH_DATA_RD_ER_BIT_POS	10
#घोषणा HIDMA_IRQ_TR_CH_DATA_WR_ER_BIT_POS	11
#घोषणा HIDMA_IRQ_TR_CH_INVALID_TRE_BIT_POS	14

#घोषणा ENABLE_IRQS (BIT(HIDMA_IRQ_EV_CH_EOB_IRQ_BIT_POS)	| \
		     BIT(HIDMA_IRQ_EV_CH_WR_RESP_BIT_POS)	| \
		     BIT(HIDMA_IRQ_TR_CH_TRE_RD_RSP_ER_BIT_POS)	| \
		     BIT(HIDMA_IRQ_TR_CH_DATA_RD_ER_BIT_POS)	| \
		     BIT(HIDMA_IRQ_TR_CH_DATA_WR_ER_BIT_POS)	| \
		     BIT(HIDMA_IRQ_TR_CH_INVALID_TRE_BIT_POS))

#घोषणा HIDMA_INCREMENT_ITERATOR(iter, size, ring_size)	\
करो अणु								\
	iter += size;						\
	अगर (iter >= ring_size)					\
		iter -= ring_size;				\
पूर्ण जबतक (0)

#घोषणा HIDMA_CH_STATE(val)	\
	((val >> HIDMA_CH_STATE_BIT_POS) & HIDMA_CH_STATE_MASK)

#घोषणा HIDMA_ERR_INT_MASK				\
	(BIT(HIDMA_IRQ_TR_CH_INVALID_TRE_BIT_POS)   |	\
	 BIT(HIDMA_IRQ_TR_CH_TRE_RD_RSP_ER_BIT_POS) |	\
	 BIT(HIDMA_IRQ_EV_CH_WR_RESP_BIT_POS)	    |	\
	 BIT(HIDMA_IRQ_TR_CH_DATA_RD_ER_BIT_POS)    |	\
	 BIT(HIDMA_IRQ_TR_CH_DATA_WR_ER_BIT_POS))

क्रमागत ch_command अणु
	HIDMA_CH_DISABLE = 0,
	HIDMA_CH_ENABLE = 1,
	HIDMA_CH_SUSPEND = 2,
	HIDMA_CH_RESET = 9,
पूर्ण;

क्रमागत ch_state अणु
	HIDMA_CH_DISABLED = 0,
	HIDMA_CH_ENABLED = 1,
	HIDMA_CH_RUNNING = 2,
	HIDMA_CH_SUSPENDED = 3,
	HIDMA_CH_STOPPED = 4,
पूर्ण;

क्रमागत err_code अणु
	HIDMA_EVRE_STATUS_COMPLETE = 1,
	HIDMA_EVRE_STATUS_ERROR = 4,
पूर्ण;

अटल पूर्णांक hidma_is_chan_enabled(पूर्णांक state)
अणु
	चयन (state) अणु
	हाल HIDMA_CH_ENABLED:
	हाल HIDMA_CH_RUNNING:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

व्योम hidma_ll_मुक्त(काष्ठा hidma_lldev *lldev, u32 tre_ch)
अणु
	काष्ठा hidma_tre *tre;

	अगर (tre_ch >= lldev->nr_tres) अणु
		dev_err(lldev->dev, "invalid TRE number in free:%d", tre_ch);
		वापस;
	पूर्ण

	tre = &lldev->trepool[tre_ch];
	अगर (atomic_पढ़ो(&tre->allocated) != true) अणु
		dev_err(lldev->dev, "trying to free an unused TRE:%d", tre_ch);
		वापस;
	पूर्ण

	atomic_set(&tre->allocated, 0);
पूर्ण

पूर्णांक hidma_ll_request(काष्ठा hidma_lldev *lldev, u32 sig, स्थिर अक्षर *dev_name,
		     व्योम (*callback)(व्योम *data), व्योम *data, u32 *tre_ch)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा hidma_tre *tre;
	u32 *tre_local;

	अगर (!tre_ch || !lldev)
		वापस -EINVAL;

	/* need to have at least one empty spot in the queue */
	क्रम (i = 0; i < lldev->nr_tres - 1; i++) अणु
		अगर (atomic_add_unless(&lldev->trepool[i].allocated, 1, 1))
			अवरोध;
	पूर्ण

	अगर (i == (lldev->nr_tres - 1))
		वापस -ENOMEM;

	tre = &lldev->trepool[i];
	tre->dma_sig = sig;
	tre->dev_name = dev_name;
	tre->callback = callback;
	tre->data = data;
	tre->idx = i;
	tre->status = 0;
	tre->queued = 0;
	tre->err_code = 0;
	tre->err_info = 0;
	tre->lldev = lldev;
	tre_local = &tre->tre_local[0];
	tre_local[HIDMA_TRE_CFG_IDX] = (lldev->chidx & 0xFF) << 8;
	tre_local[HIDMA_TRE_CFG_IDX] |= BIT(16);	/* set IEOB */
	*tre_ch = i;
	अगर (callback)
		callback(data);
	वापस 0;
पूर्ण

/*
 * Multiple TREs may be queued and रुकोing in the pending queue.
 */
अटल व्योम hidma_ll_tre_complete(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा hidma_lldev *lldev = from_tasklet(lldev, t, task);
	काष्ठा hidma_tre *tre;

	जबतक (kfअगरo_out(&lldev->hanकरोff_fअगरo, &tre, 1)) अणु
		/* call the user अगर it has been पढ़ो by the hardware */
		अगर (tre->callback)
			tre->callback(tre->data);
	पूर्ण
पूर्ण

अटल पूर्णांक hidma_post_completed(काष्ठा hidma_lldev *lldev, u8 err_info,
				u8 err_code)
अणु
	काष्ठा hidma_tre *tre;
	अचिन्हित दीर्घ flags;
	u32 tre_iterator;

	spin_lock_irqsave(&lldev->lock, flags);

	tre_iterator = lldev->tre_processed_off;
	tre = lldev->pending_tre_list[tre_iterator / HIDMA_TRE_SIZE];
	अगर (!tre) अणु
		spin_unlock_irqrestore(&lldev->lock, flags);
		dev_warn(lldev->dev, "tre_index [%d] and tre out of sync\n",
			 tre_iterator / HIDMA_TRE_SIZE);
		वापस -EINVAL;
	पूर्ण
	lldev->pending_tre_list[tre->tre_index] = शून्य;

	/*
	 * Keep track of pending TREs that SW is expecting to receive
	 * from HW. We got one now. Decrement our counter.
	 */
	अगर (atomic_dec_वापस(&lldev->pending_tre_count) < 0) अणु
		dev_warn(lldev->dev, "tre count mismatch on completion");
		atomic_set(&lldev->pending_tre_count, 0);
	पूर्ण

	HIDMA_INCREMENT_ITERATOR(tre_iterator, HIDMA_TRE_SIZE,
				 lldev->tre_ring_size);
	lldev->tre_processed_off = tre_iterator;
	spin_unlock_irqrestore(&lldev->lock, flags);

	tre->err_info = err_info;
	tre->err_code = err_code;
	tre->queued = 0;

	kfअगरo_put(&lldev->hanकरोff_fअगरo, tre);
	tasklet_schedule(&lldev->task);

	वापस 0;
पूर्ण

/*
 * Called to handle the पूर्णांकerrupt क्रम the channel.
 * Return a positive number अगर TRE or EVRE were consumed on this run.
 * Return a positive number अगर there are pending TREs or EVREs.
 * Return 0 अगर there is nothing to consume or no pending TREs/EVREs found.
 */
अटल पूर्णांक hidma_handle_tre_completion(काष्ठा hidma_lldev *lldev)
अणु
	u32 evre_ring_size = lldev->evre_ring_size;
	u32 err_info, err_code, evre_ग_लिखो_off;
	u32 evre_iterator;
	u32 num_completed = 0;

	evre_ग_लिखो_off = पढ़ोl_relaxed(lldev->evca + HIDMA_EVCA_WRITE_PTR_REG);
	evre_iterator = lldev->evre_processed_off;

	अगर ((evre_ग_लिखो_off > evre_ring_size) ||
	    (evre_ग_लिखो_off % HIDMA_EVRE_SIZE)) अणु
		dev_err(lldev->dev, "HW reports invalid EVRE write offset\n");
		वापस 0;
	पूर्ण

	/*
	 * By the समय control reaches here the number of EVREs and TREs
	 * may not match. Only consume the ones that hardware told us.
	 */
	जबतक ((evre_iterator != evre_ग_लिखो_off)) अणु
		u32 *current_evre = lldev->evre_ring + evre_iterator;
		u32 cfg;

		cfg = current_evre[HIDMA_EVRE_CFG_IDX];
		err_info = cfg >> HIDMA_EVRE_ERRINFO_BIT_POS;
		err_info &= HIDMA_EVRE_ERRINFO_MASK;
		err_code =
		    (cfg >> HIDMA_EVRE_CODE_BIT_POS) & HIDMA_EVRE_CODE_MASK;

		अगर (hidma_post_completed(lldev, err_info, err_code))
			अवरोध;

		HIDMA_INCREMENT_ITERATOR(evre_iterator, HIDMA_EVRE_SIZE,
					 evre_ring_size);

		/*
		 * Read the new event descriptor written by the HW.
		 * As we are processing the delivered events, other events
		 * get queued to the SW क्रम processing.
		 */
		evre_ग_लिखो_off =
		    पढ़ोl_relaxed(lldev->evca + HIDMA_EVCA_WRITE_PTR_REG);
		num_completed++;

		/*
		 * An error पूर्णांकerrupt might have arrived जबतक we are processing
		 * the completed पूर्णांकerrupt.
		 */
		अगर (!hidma_ll_isenabled(lldev))
			अवरोध;
	पूर्ण

	अगर (num_completed) अणु
		u32 evre_पढ़ो_off = (lldev->evre_processed_off +
				     HIDMA_EVRE_SIZE * num_completed);
		evre_पढ़ो_off = evre_पढ़ो_off % evre_ring_size;
		ग_लिखोl(evre_पढ़ो_off, lldev->evca + HIDMA_EVCA_DOORBELL_REG);

		/* record the last processed tre offset */
		lldev->evre_processed_off = evre_पढ़ो_off;
	पूर्ण

	वापस num_completed;
पूर्ण

व्योम hidma_cleanup_pending_tre(काष्ठा hidma_lldev *lldev, u8 err_info,
			       u8 err_code)
अणु
	जबतक (atomic_पढ़ो(&lldev->pending_tre_count)) अणु
		अगर (hidma_post_completed(lldev, err_info, err_code))
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक hidma_ll_reset(काष्ठा hidma_lldev *lldev)
अणु
	u32 val;
	पूर्णांक ret;

	val = पढ़ोl(lldev->trca + HIDMA_TRCA_CTRLSTS_REG);
	val &= ~(HIDMA_CH_CONTROL_MASK << 16);
	val |= HIDMA_CH_RESET << 16;
	ग_लिखोl(val, lldev->trca + HIDMA_TRCA_CTRLSTS_REG);

	/*
	 * Delay 10ms after reset to allow DMA logic to quiesce.
	 * Do a polled पढ़ो up to 1ms and 10ms maximum.
	 */
	ret = पढ़ोl_poll_समयout(lldev->trca + HIDMA_TRCA_CTRLSTS_REG, val,
				 HIDMA_CH_STATE(val) == HIDMA_CH_DISABLED,
				 1000, 10000);
	अगर (ret) अणु
		dev_err(lldev->dev, "transfer channel did not reset\n");
		वापस ret;
	पूर्ण

	val = पढ़ोl(lldev->evca + HIDMA_EVCA_CTRLSTS_REG);
	val &= ~(HIDMA_CH_CONTROL_MASK << 16);
	val |= HIDMA_CH_RESET << 16;
	ग_लिखोl(val, lldev->evca + HIDMA_EVCA_CTRLSTS_REG);

	/*
	 * Delay 10ms after reset to allow DMA logic to quiesce.
	 * Do a polled पढ़ो up to 1ms and 10ms maximum.
	 */
	ret = पढ़ोl_poll_समयout(lldev->evca + HIDMA_EVCA_CTRLSTS_REG, val,
				 HIDMA_CH_STATE(val) == HIDMA_CH_DISABLED,
				 1000, 10000);
	अगर (ret)
		वापस ret;

	lldev->trch_state = HIDMA_CH_DISABLED;
	lldev->evch_state = HIDMA_CH_DISABLED;
	वापस 0;
पूर्ण

/*
 * The पूर्णांकerrupt handler क्रम HIDMA will try to consume as many pending
 * EVRE from the event queue as possible. Each EVRE has an associated
 * TRE that holds the user पूर्णांकerface parameters. EVRE reports the
 * result of the transaction. Hardware guarantees ordering between EVREs
 * and TREs. We use last processed offset to figure out which TRE is
 * associated with which EVRE. If two TREs are consumed by HW, the EVREs
 * are in order in the event ring.
 *
 * This handler will करो a one pass क्रम consuming EVREs. Other EVREs may
 * be delivered जबतक we are working. It will try to consume incoming
 * EVREs one more समय and वापस.
 *
 * For unprocessed EVREs, hardware will trigger another पूर्णांकerrupt until
 * all the पूर्णांकerrupt bits are cleared.
 *
 * Hardware guarantees that by the समय पूर्णांकerrupt is observed, all data
 * transactions in flight are delivered to their respective places and
 * are visible to the CPU.
 *
 * On demand paging क्रम IOMMU is only supported क्रम PCIe via PRI
 * (Page Request Interface) not क्रम HIDMA. All other hardware instances
 * including HIDMA work on pinned DMA addresses.
 *
 * HIDMA is not aware of IOMMU presence since it follows the DMA API. All
 * IOMMU latency will be built पूर्णांकo the data movement समय. By the समय
 * पूर्णांकerrupt happens, IOMMU lookups + data movement has alपढ़ोy taken place.
 *
 * While the first पढ़ो in a typical PCI endpoपूर्णांक ISR flushes all outstanding
 * requests traditionally to the destination, this concept करोes not apply
 * here क्रम this HW.
 */
अटल व्योम hidma_ll_पूर्णांक_handler_पूर्णांकernal(काष्ठा hidma_lldev *lldev, पूर्णांक cause)
अणु
	अचिन्हित दीर्घ irqflags;

	अगर (cause & HIDMA_ERR_INT_MASK) अणु
		dev_err(lldev->dev, "error 0x%x, disabling...\n",
				cause);

		/* Clear out pending पूर्णांकerrupts */
		ग_लिखोl(cause, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);

		/* No further submissions. */
		hidma_ll_disable(lldev);

		/* Driver completes the txn and पूर्णांकimates the client.*/
		hidma_cleanup_pending_tre(lldev, 0xFF,
					  HIDMA_EVRE_STATUS_ERROR);

		वापस;
	पूर्ण

	spin_lock_irqsave(&lldev->lock, irqflags);
	ग_लिखोl_relaxed(cause, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);
	spin_unlock_irqrestore(&lldev->lock, irqflags);

	/*
	 * Fine tuned क्रम this HW...
	 *
	 * This ISR has been deचिन्हित क्रम this particular hardware. Relaxed
	 * पढ़ो and ग_लिखो accessors are used क्रम perक्रमmance reasons due to
	 * पूर्णांकerrupt delivery guarantees. Do not copy this code blindly and
	 * expect that to work.
	 *
	 * Try to consume as many EVREs as possible.
	 */
	hidma_handle_tre_completion(lldev);
पूर्ण

irqवापस_t hidma_ll_पूर्णांकhandler(पूर्णांक chirq, व्योम *arg)
अणु
	काष्ठा hidma_lldev *lldev = arg;
	u32 status;
	u32 enable;
	u32 cause;

	status = पढ़ोl_relaxed(lldev->evca + HIDMA_EVCA_IRQ_STAT_REG);
	enable = पढ़ोl_relaxed(lldev->evca + HIDMA_EVCA_IRQ_EN_REG);
	cause = status & enable;

	जबतक (cause) अणु
		hidma_ll_पूर्णांक_handler_पूर्णांकernal(lldev, cause);

		/*
		 * Another पूर्णांकerrupt might have arrived जबतक we are
		 * processing this one. Read the new cause.
		 */
		status = पढ़ोl_relaxed(lldev->evca + HIDMA_EVCA_IRQ_STAT_REG);
		enable = पढ़ोl_relaxed(lldev->evca + HIDMA_EVCA_IRQ_EN_REG);
		cause = status & enable;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t hidma_ll_पूर्णांकhandler_msi(पूर्णांक chirq, व्योम *arg, पूर्णांक cause)
अणु
	काष्ठा hidma_lldev *lldev = arg;

	hidma_ll_पूर्णांक_handler_पूर्णांकernal(lldev, cause);
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक hidma_ll_enable(काष्ठा hidma_lldev *lldev)
अणु
	u32 val;
	पूर्णांक ret;

	val = पढ़ोl(lldev->evca + HIDMA_EVCA_CTRLSTS_REG);
	val &= ~(HIDMA_CH_CONTROL_MASK << 16);
	val |= HIDMA_CH_ENABLE << 16;
	ग_लिखोl(val, lldev->evca + HIDMA_EVCA_CTRLSTS_REG);

	ret = पढ़ोl_poll_समयout(lldev->evca + HIDMA_EVCA_CTRLSTS_REG, val,
				 hidma_is_chan_enabled(HIDMA_CH_STATE(val)),
				 1000, 10000);
	अगर (ret) अणु
		dev_err(lldev->dev, "event channel did not get enabled\n");
		वापस ret;
	पूर्ण

	val = पढ़ोl(lldev->trca + HIDMA_TRCA_CTRLSTS_REG);
	val &= ~(HIDMA_CH_CONTROL_MASK << 16);
	val |= HIDMA_CH_ENABLE << 16;
	ग_लिखोl(val, lldev->trca + HIDMA_TRCA_CTRLSTS_REG);

	ret = पढ़ोl_poll_समयout(lldev->trca + HIDMA_TRCA_CTRLSTS_REG, val,
				 hidma_is_chan_enabled(HIDMA_CH_STATE(val)),
				 1000, 10000);
	अगर (ret) अणु
		dev_err(lldev->dev, "transfer channel did not get enabled\n");
		वापस ret;
	पूर्ण

	lldev->trch_state = HIDMA_CH_ENABLED;
	lldev->evch_state = HIDMA_CH_ENABLED;

	/* enable irqs */
	ग_लिखोl(ENABLE_IRQS, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);

	वापस 0;
पूर्ण

व्योम hidma_ll_start(काष्ठा hidma_lldev *lldev)
अणु
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&lldev->lock, irqflags);
	ग_लिखोl(lldev->tre_ग_लिखो_offset, lldev->trca + HIDMA_TRCA_DOORBELL_REG);
	spin_unlock_irqrestore(&lldev->lock, irqflags);
पूर्ण

bool hidma_ll_isenabled(काष्ठा hidma_lldev *lldev)
अणु
	u32 val;

	val = पढ़ोl(lldev->trca + HIDMA_TRCA_CTRLSTS_REG);
	lldev->trch_state = HIDMA_CH_STATE(val);
	val = पढ़ोl(lldev->evca + HIDMA_EVCA_CTRLSTS_REG);
	lldev->evch_state = HIDMA_CH_STATE(val);

	/* both channels have to be enabled beक्रमe calling this function */
	अगर (hidma_is_chan_enabled(lldev->trch_state) &&
	    hidma_is_chan_enabled(lldev->evch_state))
		वापस true;

	वापस false;
पूर्ण

व्योम hidma_ll_queue_request(काष्ठा hidma_lldev *lldev, u32 tre_ch)
अणु
	काष्ठा hidma_tre *tre;
	अचिन्हित दीर्घ flags;

	tre = &lldev->trepool[tre_ch];

	/* copy the TRE पूर्णांकo its location in the TRE ring */
	spin_lock_irqsave(&lldev->lock, flags);
	tre->tre_index = lldev->tre_ग_लिखो_offset / HIDMA_TRE_SIZE;
	lldev->pending_tre_list[tre->tre_index] = tre;
	स_नकल(lldev->tre_ring + lldev->tre_ग_लिखो_offset,
			&tre->tre_local[0], HIDMA_TRE_SIZE);
	tre->err_code = 0;
	tre->err_info = 0;
	tre->queued = 1;
	atomic_inc(&lldev->pending_tre_count);
	lldev->tre_ग_लिखो_offset = (lldev->tre_ग_लिखो_offset + HIDMA_TRE_SIZE)
					% lldev->tre_ring_size;
	spin_unlock_irqrestore(&lldev->lock, flags);
पूर्ण

/*
 * Note that even though we stop this channel अगर there is a pending transaction
 * in flight it will complete and follow the callback. This request will
 * prevent further requests to be made.
 */
पूर्णांक hidma_ll_disable(काष्ठा hidma_lldev *lldev)
अणु
	u32 val;
	पूर्णांक ret;

	/* The channel needs to be in working state */
	अगर (!hidma_ll_isenabled(lldev))
		वापस 0;

	val = पढ़ोl(lldev->trca + HIDMA_TRCA_CTRLSTS_REG);
	val &= ~(HIDMA_CH_CONTROL_MASK << 16);
	val |= HIDMA_CH_SUSPEND << 16;
	ग_लिखोl(val, lldev->trca + HIDMA_TRCA_CTRLSTS_REG);

	/*
	 * Start the रुको right after the suspend is confirmed.
	 * Do a polled पढ़ो up to 1ms and 10ms maximum.
	 */
	ret = पढ़ोl_poll_समयout(lldev->trca + HIDMA_TRCA_CTRLSTS_REG, val,
				 HIDMA_CH_STATE(val) == HIDMA_CH_SUSPENDED,
				 1000, 10000);
	अगर (ret)
		वापस ret;

	val = पढ़ोl(lldev->evca + HIDMA_EVCA_CTRLSTS_REG);
	val &= ~(HIDMA_CH_CONTROL_MASK << 16);
	val |= HIDMA_CH_SUSPEND << 16;
	ग_लिखोl(val, lldev->evca + HIDMA_EVCA_CTRLSTS_REG);

	/*
	 * Start the रुको right after the suspend is confirmed
	 * Delay up to 10ms after reset to allow DMA logic to quiesce.
	 */
	ret = पढ़ोl_poll_समयout(lldev->evca + HIDMA_EVCA_CTRLSTS_REG, val,
				 HIDMA_CH_STATE(val) == HIDMA_CH_SUSPENDED,
				 1000, 10000);
	अगर (ret)
		वापस ret;

	lldev->trch_state = HIDMA_CH_SUSPENDED;
	lldev->evch_state = HIDMA_CH_SUSPENDED;

	/* disable पूर्णांकerrupts */
	ग_लिखोl(0, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);
	वापस 0;
पूर्ण

व्योम hidma_ll_set_transfer_params(काष्ठा hidma_lldev *lldev, u32 tre_ch,
				  dma_addr_t src, dma_addr_t dest, u32 len,
				  u32 flags, u32 txntype)
अणु
	काष्ठा hidma_tre *tre;
	u32 *tre_local;

	अगर (tre_ch >= lldev->nr_tres) अणु
		dev_err(lldev->dev, "invalid TRE number in transfer params:%d",
			tre_ch);
		वापस;
	पूर्ण

	tre = &lldev->trepool[tre_ch];
	अगर (atomic_पढ़ो(&tre->allocated) != true) अणु
		dev_err(lldev->dev, "trying to set params on an unused TRE:%d",
			tre_ch);
		वापस;
	पूर्ण

	tre_local = &tre->tre_local[0];
	tre_local[HIDMA_TRE_CFG_IDX] &= ~GENMASK(7, 0);
	tre_local[HIDMA_TRE_CFG_IDX] |= txntype;
	tre_local[HIDMA_TRE_LEN_IDX] = len;
	tre_local[HIDMA_TRE_SRC_LOW_IDX] = lower_32_bits(src);
	tre_local[HIDMA_TRE_SRC_HI_IDX] = upper_32_bits(src);
	tre_local[HIDMA_TRE_DEST_LOW_IDX] = lower_32_bits(dest);
	tre_local[HIDMA_TRE_DEST_HI_IDX] = upper_32_bits(dest);
	tre->पूर्णांक_flags = flags;
पूर्ण

/*
 * Called during initialization and after an error condition
 * to restore hardware state.
 */
पूर्णांक hidma_ll_setup(काष्ठा hidma_lldev *lldev)
अणु
	पूर्णांक rc;
	u64 addr;
	u32 val;
	u32 nr_tres = lldev->nr_tres;

	atomic_set(&lldev->pending_tre_count, 0);
	lldev->tre_processed_off = 0;
	lldev->evre_processed_off = 0;
	lldev->tre_ग_लिखो_offset = 0;

	/* disable पूर्णांकerrupts */
	ग_लिखोl(0, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);

	/* clear all pending पूर्णांकerrupts */
	val = पढ़ोl(lldev->evca + HIDMA_EVCA_IRQ_STAT_REG);
	ग_लिखोl(val, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);

	rc = hidma_ll_reset(lldev);
	अगर (rc)
		वापस rc;

	/*
	 * Clear all pending पूर्णांकerrupts again.
	 * Otherwise, we observe reset complete पूर्णांकerrupts.
	 */
	val = पढ़ोl(lldev->evca + HIDMA_EVCA_IRQ_STAT_REG);
	ग_लिखोl(val, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);

	/* disable पूर्णांकerrupts again after reset */
	ग_लिखोl(0, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);

	addr = lldev->tre_dma;
	ग_लिखोl(lower_32_bits(addr), lldev->trca + HIDMA_TRCA_RING_LOW_REG);
	ग_लिखोl(upper_32_bits(addr), lldev->trca + HIDMA_TRCA_RING_HIGH_REG);
	ग_लिखोl(lldev->tre_ring_size, lldev->trca + HIDMA_TRCA_RING_LEN_REG);

	addr = lldev->evre_dma;
	ग_लिखोl(lower_32_bits(addr), lldev->evca + HIDMA_EVCA_RING_LOW_REG);
	ग_लिखोl(upper_32_bits(addr), lldev->evca + HIDMA_EVCA_RING_HIGH_REG);
	ग_लिखोl(HIDMA_EVRE_SIZE * nr_tres,
			lldev->evca + HIDMA_EVCA_RING_LEN_REG);

	/* configure पूर्णांकerrupts */
	hidma_ll_setup_irq(lldev, lldev->msi_support);

	rc = hidma_ll_enable(lldev);
	अगर (rc)
		वापस rc;

	वापस rc;
पूर्ण

व्योम hidma_ll_setup_irq(काष्ठा hidma_lldev *lldev, bool msi)
अणु
	u32 val;

	lldev->msi_support = msi;

	/* disable पूर्णांकerrupts again after reset */
	ग_लिखोl(0, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);
	ग_लिखोl(0, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);

	/* support IRQ by शेष */
	val = पढ़ोl(lldev->evca + HIDMA_EVCA_INTCTRL_REG);
	val &= ~0xF;
	अगर (!lldev->msi_support)
		val = val | 0x1;
	ग_लिखोl(val, lldev->evca + HIDMA_EVCA_INTCTRL_REG);

	/* clear all pending पूर्णांकerrupts and enable them */
	ग_लिखोl(ENABLE_IRQS, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);
	ग_लिखोl(ENABLE_IRQS, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);
पूर्ण

काष्ठा hidma_lldev *hidma_ll_init(काष्ठा device *dev, u32 nr_tres,
				  व्योम __iomem *trca, व्योम __iomem *evca,
				  u8 chidx)
अणु
	u32 required_bytes;
	काष्ठा hidma_lldev *lldev;
	पूर्णांक rc;
	माप_प्रकार sz;

	अगर (!trca || !evca || !dev || !nr_tres)
		वापस शून्य;

	/* need at least four TREs */
	अगर (nr_tres < 4)
		वापस शून्य;

	/* need an extra space */
	nr_tres += 1;

	lldev = devm_kzalloc(dev, माप(काष्ठा hidma_lldev), GFP_KERNEL);
	अगर (!lldev)
		वापस शून्य;

	lldev->evca = evca;
	lldev->trca = trca;
	lldev->dev = dev;
	sz = माप(काष्ठा hidma_tre);
	lldev->trepool = devm_kसुस्मृति(lldev->dev, nr_tres, sz, GFP_KERNEL);
	अगर (!lldev->trepool)
		वापस शून्य;

	required_bytes = माप(lldev->pending_tre_list[0]);
	lldev->pending_tre_list = devm_kसुस्मृति(dev, nr_tres, required_bytes,
					       GFP_KERNEL);
	अगर (!lldev->pending_tre_list)
		वापस शून्य;

	sz = (HIDMA_TRE_SIZE + 1) * nr_tres;
	lldev->tre_ring = dmam_alloc_coherent(dev, sz, &lldev->tre_dma,
					      GFP_KERNEL);
	अगर (!lldev->tre_ring)
		वापस शून्य;

	lldev->tre_ring_size = HIDMA_TRE_SIZE * nr_tres;
	lldev->nr_tres = nr_tres;

	/* the TRE ring has to be TRE_SIZE aligned */
	अगर (!IS_ALIGNED(lldev->tre_dma, HIDMA_TRE_SIZE)) अणु
		u8 tre_ring_shअगरt;

		tre_ring_shअगरt = lldev->tre_dma % HIDMA_TRE_SIZE;
		tre_ring_shअगरt = HIDMA_TRE_SIZE - tre_ring_shअगरt;
		lldev->tre_dma += tre_ring_shअगरt;
		lldev->tre_ring += tre_ring_shअगरt;
	पूर्ण

	sz = (HIDMA_EVRE_SIZE + 1) * nr_tres;
	lldev->evre_ring = dmam_alloc_coherent(dev, sz, &lldev->evre_dma,
					       GFP_KERNEL);
	अगर (!lldev->evre_ring)
		वापस शून्य;

	lldev->evre_ring_size = HIDMA_EVRE_SIZE * nr_tres;

	/* the EVRE ring has to be EVRE_SIZE aligned */
	अगर (!IS_ALIGNED(lldev->evre_dma, HIDMA_EVRE_SIZE)) अणु
		u8 evre_ring_shअगरt;

		evre_ring_shअगरt = lldev->evre_dma % HIDMA_EVRE_SIZE;
		evre_ring_shअगरt = HIDMA_EVRE_SIZE - evre_ring_shअगरt;
		lldev->evre_dma += evre_ring_shअगरt;
		lldev->evre_ring += evre_ring_shअगरt;
	पूर्ण
	lldev->nr_tres = nr_tres;
	lldev->chidx = chidx;

	sz = nr_tres * माप(काष्ठा hidma_tre *);
	rc = kfअगरo_alloc(&lldev->hanकरोff_fअगरo, sz, GFP_KERNEL);
	अगर (rc)
		वापस शून्य;

	rc = hidma_ll_setup(lldev);
	अगर (rc)
		वापस शून्य;

	spin_lock_init(&lldev->lock);
	tasklet_setup(&lldev->task, hidma_ll_tre_complete);
	lldev->initialized = 1;
	ग_लिखोl(ENABLE_IRQS, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);
	वापस lldev;
पूर्ण

पूर्णांक hidma_ll_uninit(काष्ठा hidma_lldev *lldev)
अणु
	u32 required_bytes;
	पूर्णांक rc = 0;
	u32 val;

	अगर (!lldev)
		वापस -ENODEV;

	अगर (!lldev->initialized)
		वापस 0;

	lldev->initialized = 0;

	required_bytes = माप(काष्ठा hidma_tre) * lldev->nr_tres;
	tasklet_समाप्त(&lldev->task);
	स_रखो(lldev->trepool, 0, required_bytes);
	lldev->trepool = शून्य;
	atomic_set(&lldev->pending_tre_count, 0);
	lldev->tre_ग_लिखो_offset = 0;

	rc = hidma_ll_reset(lldev);

	/*
	 * Clear all pending पूर्णांकerrupts again.
	 * Otherwise, we observe reset complete पूर्णांकerrupts.
	 */
	val = पढ़ोl(lldev->evca + HIDMA_EVCA_IRQ_STAT_REG);
	ग_लिखोl(val, lldev->evca + HIDMA_EVCA_IRQ_CLR_REG);
	ग_लिखोl(0, lldev->evca + HIDMA_EVCA_IRQ_EN_REG);
	वापस rc;
पूर्ण

क्रमागत dma_status hidma_ll_status(काष्ठा hidma_lldev *lldev, u32 tre_ch)
अणु
	क्रमागत dma_status ret = DMA_ERROR;
	काष्ठा hidma_tre *tre;
	अचिन्हित दीर्घ flags;
	u8 err_code;

	spin_lock_irqsave(&lldev->lock, flags);

	tre = &lldev->trepool[tre_ch];
	err_code = tre->err_code;

	अगर (err_code & HIDMA_EVRE_STATUS_COMPLETE)
		ret = DMA_COMPLETE;
	अन्यथा अगर (err_code & HIDMA_EVRE_STATUS_ERROR)
		ret = DMA_ERROR;
	अन्यथा
		ret = DMA_IN_PROGRESS;
	spin_unlock_irqrestore(&lldev->lock, flags);

	वापस ret;
पूर्ण
