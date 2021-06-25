<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * The contents of this file are निजी to DMA engine drivers, and is not
 * part of the API to be used by DMA engine users.
 */
#अगर_अघोषित DMAENGINE_H
#घोषणा DMAENGINE_H

#समावेश <linux/bug.h>
#समावेश <linux/dmaengine.h>

/**
 * dma_cookie_init - initialize the cookies क्रम a DMA channel
 * @chan: dma channel to initialize
 */
अटल अंतरभूत व्योम dma_cookie_init(काष्ठा dma_chan *chan)
अणु
	chan->cookie = DMA_MIN_COOKIE;
	chan->completed_cookie = DMA_MIN_COOKIE;
पूर्ण

/**
 * dma_cookie_assign - assign a DMA engine cookie to the descriptor
 * @tx: descriptor needing cookie
 *
 * Assign a unique non-zero per-channel cookie to the descriptor.
 * Note: caller is expected to hold a lock to prevent concurrency.
 */
अटल अंतरभूत dma_cookie_t dma_cookie_assign(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा dma_chan *chan = tx->chan;
	dma_cookie_t cookie;

	cookie = chan->cookie + 1;
	अगर (cookie < DMA_MIN_COOKIE)
		cookie = DMA_MIN_COOKIE;
	tx->cookie = chan->cookie = cookie;

	वापस cookie;
पूर्ण

/**
 * dma_cookie_complete - complete a descriptor
 * @tx: descriptor to complete
 *
 * Mark this descriptor complete by updating the channels completed
 * cookie marker.  Zero the descriptors cookie to prevent accidental
 * repeated completions.
 *
 * Note: caller is expected to hold a lock to prevent concurrency.
 */
अटल अंतरभूत व्योम dma_cookie_complete(काष्ठा dma_async_tx_descriptor *tx)
अणु
	BUG_ON(tx->cookie < DMA_MIN_COOKIE);
	tx->chan->completed_cookie = tx->cookie;
	tx->cookie = 0;
पूर्ण

/**
 * dma_cookie_status - report cookie status
 * @chan: dma channel
 * @cookie: cookie we are पूर्णांकerested in
 * @state: dma_tx_state काष्ठाure to वापस last/used cookies
 *
 * Report the status of the cookie, filling in the state काष्ठाure अगर
 * non-शून्य.  No locking is required.
 */
अटल अंतरभूत क्रमागत dma_status dma_cookie_status(काष्ठा dma_chan *chan,
	dma_cookie_t cookie, काष्ठा dma_tx_state *state)
अणु
	dma_cookie_t used, complete;

	used = chan->cookie;
	complete = chan->completed_cookie;
	barrier();
	अगर (state) अणु
		state->last = complete;
		state->used = used;
		state->residue = 0;
		state->in_flight_bytes = 0;
	पूर्ण
	वापस dma_async_is_complete(cookie, complete, used);
पूर्ण

अटल अंतरभूत व्योम dma_set_residue(काष्ठा dma_tx_state *state, u32 residue)
अणु
	अगर (state)
		state->residue = residue;
पूर्ण

अटल अंतरभूत व्योम dma_set_in_flight_bytes(काष्ठा dma_tx_state *state,
					   u32 in_flight_bytes)
अणु
	अगर (state)
		state->in_flight_bytes = in_flight_bytes;
पूर्ण

काष्ठा dmaengine_desc_callback अणु
	dma_async_tx_callback callback;
	dma_async_tx_callback_result callback_result;
	व्योम *callback_param;
पूर्ण;

/**
 * dmaengine_desc_get_callback - get the passed in callback function
 * @tx: tx descriptor
 * @cb: temp काष्ठा to hold the callback info
 *
 * Fill the passed in cb काष्ठा with what's available in the passed in
 * tx descriptor काष्ठा
 * No locking is required.
 */
अटल अंतरभूत व्योम
dmaengine_desc_get_callback(काष्ठा dma_async_tx_descriptor *tx,
			    काष्ठा dmaengine_desc_callback *cb)
अणु
	cb->callback = tx->callback;
	cb->callback_result = tx->callback_result;
	cb->callback_param = tx->callback_param;
पूर्ण

/**
 * dmaengine_desc_callback_invoke - call the callback function in cb काष्ठा
 * @cb: temp काष्ठा that is holding the callback info
 * @result: transaction result
 *
 * Call the callback function provided in the cb काष्ठा with the parameter
 * in the cb काष्ठा.
 * Locking is dependent on the driver.
 */
अटल अंतरभूत व्योम
dmaengine_desc_callback_invoke(काष्ठा dmaengine_desc_callback *cb,
			       स्थिर काष्ठा dmaengine_result *result)
अणु
	काष्ठा dmaengine_result dummy_result = अणु
		.result = DMA_TRANS_NOERROR,
		.residue = 0
	पूर्ण;

	अगर (cb->callback_result) अणु
		अगर (!result)
			result = &dummy_result;
		cb->callback_result(cb->callback_param, result);
	पूर्ण अन्यथा अगर (cb->callback) अणु
		cb->callback(cb->callback_param);
	पूर्ण
पूर्ण

/**
 * dmaengine_desc_get_callback_invoke - get the callback in tx descriptor and
 * 					then immediately call the callback.
 * @tx: dma async tx descriptor
 * @result: transaction result
 *
 * Call dmaengine_desc_get_callback() and dmaengine_desc_callback_invoke()
 * in a single function since no work is necessary in between क्रम the driver.
 * Locking is dependent on the driver.
 */
अटल अंतरभूत व्योम
dmaengine_desc_get_callback_invoke(काष्ठा dma_async_tx_descriptor *tx,
				   स्थिर काष्ठा dmaengine_result *result)
अणु
	काष्ठा dmaengine_desc_callback cb;

	dmaengine_desc_get_callback(tx, &cb);
	dmaengine_desc_callback_invoke(&cb, result);
पूर्ण

/**
 * dmaengine_desc_callback_valid - verअगरy the callback is valid in cb
 * @cb: callback info काष्ठा
 *
 * Return a bool that verअगरies whether callback in cb is valid or not.
 * No locking is required.
 */
अटल अंतरभूत bool
dmaengine_desc_callback_valid(काष्ठा dmaengine_desc_callback *cb)
अणु
	वापस (cb->callback) ? true : false;
पूर्ण

काष्ठा dma_chan *dma_get_slave_channel(काष्ठा dma_chan *chan);
काष्ठा dma_chan *dma_get_any_slave_channel(काष्ठा dma_device *device);

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>

अटल अंतरभूत काष्ठा dentry *
dmaengine_get_debugfs_root(काष्ठा dma_device *dma_dev) अणु
	वापस dma_dev->dbg_dev_root;
पूर्ण
#अन्यथा
काष्ठा dentry;
अटल अंतरभूत काष्ठा dentry *
dmaengine_get_debugfs_root(काष्ठा dma_device *dma_dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

#पूर्ण_अगर
