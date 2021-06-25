<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * core routines क्रम the asynchronous memory transfer/transक्रमm api
 *
 * Copyright तऊ 2006, Intel Corporation.
 *
 *	Dan Williams <dan.j.williams@पूर्णांकel.com>
 *
 *	with architecture considerations by:
 *	Neil Brown <neilb@suse.de>
 *	Jeff Garzik <jeff@garzik.org>
 */
#समावेश <linux/rculist.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/async_tx.h>

#अगर_घोषित CONFIG_DMA_ENGINE
अटल पूर्णांक __init async_tx_init(व्योम)
अणु
	async_dmaengine_get();

	prपूर्णांकk(KERN_INFO "async_tx: api initialized (async)\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास async_tx_निकास(व्योम)
अणु
	async_dmaengine_put();
पूर्ण

module_init(async_tx_init);
module_निकास(async_tx_निकास);

/**
 * __async_tx_find_channel - find a channel to carry out the operation or let
 *	the transaction execute synchronously
 * @submit: transaction dependency and submission modअगरiers
 * @tx_type: transaction type
 */
काष्ठा dma_chan *
__async_tx_find_channel(काष्ठा async_submit_ctl *submit,
			क्रमागत dma_transaction_type tx_type)
अणु
	काष्ठा dma_async_tx_descriptor *depend_tx = submit->depend_tx;

	/* see अगर we can keep the chain on one channel */
	अगर (depend_tx &&
	    dma_has_cap(tx_type, depend_tx->chan->device->cap_mask))
		वापस depend_tx->chan;
	वापस async_dma_find_channel(tx_type);
पूर्ण
EXPORT_SYMBOL_GPL(__async_tx_find_channel);
#पूर्ण_अगर


/**
 * async_tx_channel_चयन - queue an पूर्णांकerrupt descriptor with a dependency
 * 	pre-attached.
 * @depend_tx: the operation that must finish beक्रमe the new operation runs
 * @tx: the new operation
 */
अटल व्योम
async_tx_channel_चयन(काष्ठा dma_async_tx_descriptor *depend_tx,
			काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा dma_chan *chan = depend_tx->chan;
	काष्ठा dma_device *device = chan->device;
	काष्ठा dma_async_tx_descriptor *पूर्णांकr_tx = (व्योम *) ~0;

	/* first check to see अगर we can still append to depend_tx */
	txd_lock(depend_tx);
	अगर (txd_parent(depend_tx) && depend_tx->chan == tx->chan) अणु
		txd_chain(depend_tx, tx);
		पूर्णांकr_tx = शून्य;
	पूर्ण
	txd_unlock(depend_tx);

	/* attached dependency, flush the parent channel */
	अगर (!पूर्णांकr_tx) अणु
		device->device_issue_pending(chan);
		वापस;
	पूर्ण

	/* see अगर we can schedule an पूर्णांकerrupt
	 * otherwise poll क्रम completion
	 */
	अगर (dma_has_cap(DMA_INTERRUPT, device->cap_mask))
		पूर्णांकr_tx = device->device_prep_dma_पूर्णांकerrupt(chan, 0);
	अन्यथा
		पूर्णांकr_tx = शून्य;

	अगर (पूर्णांकr_tx) अणु
		पूर्णांकr_tx->callback = शून्य;
		पूर्णांकr_tx->callback_param = शून्य;
		/* safe to chain outside the lock since we know we are
		 * not submitted yet
		 */
		txd_chain(पूर्णांकr_tx, tx);

		/* check अगर we need to append */
		txd_lock(depend_tx);
		अगर (txd_parent(depend_tx)) अणु
			txd_chain(depend_tx, पूर्णांकr_tx);
			async_tx_ack(पूर्णांकr_tx);
			पूर्णांकr_tx = शून्य;
		पूर्ण
		txd_unlock(depend_tx);

		अगर (पूर्णांकr_tx) अणु
			txd_clear_parent(पूर्णांकr_tx);
			पूर्णांकr_tx->tx_submit(पूर्णांकr_tx);
			async_tx_ack(पूर्णांकr_tx);
		पूर्ण
		device->device_issue_pending(chan);
	पूर्ण अन्यथा अणु
		अगर (dma_रुको_क्रम_async_tx(depend_tx) != DMA_COMPLETE)
			panic("%s: DMA error waiting for depend_tx\n",
			      __func__);
		tx->tx_submit(tx);
	पूर्ण
पूर्ण


/**
 * submit_disposition - flags क्रम routing an incoming operation
 * @ASYNC_TX_SUBMITTED: we were able to append the new operation under the lock
 * @ASYNC_TX_CHANNEL_SWITCH: when the lock is dropped schedule a channel चयन
 * @ASYNC_TX_सूचीECT_SUBMIT: when the lock is dropped submit directly
 *
 * जबतक holding depend_tx->lock we must aव्योम submitting new operations
 * to prevent a circular locking dependency with drivers that alपढ़ोy
 * hold a channel lock when calling async_tx_run_dependencies.
 */
क्रमागत submit_disposition अणु
	ASYNC_TX_SUBMITTED,
	ASYNC_TX_CHANNEL_SWITCH,
	ASYNC_TX_सूचीECT_SUBMIT,
पूर्ण;

व्योम
async_tx_submit(काष्ठा dma_chan *chan, काष्ठा dma_async_tx_descriptor *tx,
		काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_async_tx_descriptor *depend_tx = submit->depend_tx;

	tx->callback = submit->cb_fn;
	tx->callback_param = submit->cb_param;

	अगर (depend_tx) अणु
		क्रमागत submit_disposition s;

		/* sanity check the dependency chain:
		 * 1/ अगर ack is alपढ़ोy set then we cannot be sure
		 * we are referring to the correct operation
		 * 2/ dependencies are 1:1 i.e. two transactions can
		 * not depend on the same parent
		 */
		BUG_ON(async_tx_test_ack(depend_tx) || txd_next(depend_tx) ||
		       txd_parent(tx));

		/* the lock prevents async_tx_run_dependencies from missing
		 * the setting of ->next when ->parent != शून्य
		 */
		txd_lock(depend_tx);
		अगर (txd_parent(depend_tx)) अणु
			/* we have a parent so we can not submit directly
			 * अगर we are staying on the same channel: append
			 * अन्यथा: channel चयन
			 */
			अगर (depend_tx->chan == chan) अणु
				txd_chain(depend_tx, tx);
				s = ASYNC_TX_SUBMITTED;
			पूर्ण अन्यथा
				s = ASYNC_TX_CHANNEL_SWITCH;
		पूर्ण अन्यथा अणु
			/* we करो not have a parent so we may be able to submit
			 * directly अगर we are staying on the same channel
			 */
			अगर (depend_tx->chan == chan)
				s = ASYNC_TX_सूचीECT_SUBMIT;
			अन्यथा
				s = ASYNC_TX_CHANNEL_SWITCH;
		पूर्ण
		txd_unlock(depend_tx);

		चयन (s) अणु
		हाल ASYNC_TX_SUBMITTED:
			अवरोध;
		हाल ASYNC_TX_CHANNEL_SWITCH:
			async_tx_channel_चयन(depend_tx, tx);
			अवरोध;
		हाल ASYNC_TX_सूचीECT_SUBMIT:
			txd_clear_parent(tx);
			tx->tx_submit(tx);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		txd_clear_parent(tx);
		tx->tx_submit(tx);
	पूर्ण

	अगर (submit->flags & ASYNC_TX_ACK)
		async_tx_ack(tx);

	अगर (depend_tx)
		async_tx_ack(depend_tx);
पूर्ण
EXPORT_SYMBOL_GPL(async_tx_submit);

/**
 * async_trigger_callback - schedules the callback function to be run
 * @submit: submission and completion parameters
 *
 * honored flags: ASYNC_TX_ACK
 *
 * The callback is run after any dependent operations have completed.
 */
काष्ठा dma_async_tx_descriptor *
async_trigger_callback(काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_device *device;
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा dma_async_tx_descriptor *depend_tx = submit->depend_tx;

	अगर (depend_tx) अणु
		chan = depend_tx->chan;
		device = chan->device;

		/* see अगर we can schedule an पूर्णांकerrupt
		 * otherwise poll क्रम completion
		 */
		अगर (device && !dma_has_cap(DMA_INTERRUPT, device->cap_mask))
			device = शून्य;

		tx = device ? device->device_prep_dma_पूर्णांकerrupt(chan, 0) : शून्य;
	पूर्ण अन्यथा
		tx = शून्य;

	अगर (tx) अणु
		pr_debug("%s: (async)\n", __func__);

		async_tx_submit(chan, tx, submit);
	पूर्ण अन्यथा अणु
		pr_debug("%s: (sync)\n", __func__);

		/* रुको क्रम any prerequisite operations */
		async_tx_quiesce(&submit->depend_tx);

		async_tx_sync_epilog(submit);
	पूर्ण

	वापस tx;
पूर्ण
EXPORT_SYMBOL_GPL(async_trigger_callback);

/**
 * async_tx_quiesce - ensure tx is complete and मुक्तable upon वापस
 * @tx - transaction to quiesce
 */
व्योम async_tx_quiesce(काष्ठा dma_async_tx_descriptor **tx)
अणु
	अगर (*tx) अणु
		/* अगर ack is alपढ़ोy set then we cannot be sure
		 * we are referring to the correct operation
		 */
		BUG_ON(async_tx_test_ack(*tx));
		अगर (dma_रुको_क्रम_async_tx(*tx) != DMA_COMPLETE)
			panic("%s: DMA error waiting for transaction\n",
			      __func__);
		async_tx_ack(*tx);
		*tx = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(async_tx_quiesce);

MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("Asynchronous Bulk Memory Transactions API");
MODULE_LICENSE("GPL");
