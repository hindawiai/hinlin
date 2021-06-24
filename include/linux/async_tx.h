<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright तऊ 2006, Intel Corporation.
 */
#अगर_अघोषित _ASYNC_TX_H_
#घोषणा _ASYNC_TX_H_
#समावेश <linux/dmaengine.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>

/* on architectures without dma-mapping capabilities we need to ensure
 * that the asynchronous path compiles away
 */
#अगर_घोषित CONFIG_HAS_DMA
#घोषणा __async_अंतरभूत
#अन्यथा
#घोषणा __async_अंतरभूत __always_अंतरभूत
#पूर्ण_अगर

/**
 * dma_chan_ref - object used to manage dma channels received from the
 *   dmaengine core.
 * @chan - the channel being tracked
 * @node - node क्रम the channel to be placed on async_tx_master_list
 * @rcu - क्रम list_del_rcu
 * @count - number of बार this channel is listed in the pool
 *	(क्रम channels with multiple capabiities)
 */
काष्ठा dma_chan_ref अणु
	काष्ठा dma_chan *chan;
	काष्ठा list_head node;
	काष्ठा rcu_head rcu;
	atomic_t count;
पूर्ण;

/**
 * async_tx_flags - modअगरiers क्रम the async_* calls
 * @ASYNC_TX_XOR_ZERO_DST: this flag must be used क्रम xor operations where the
 * destination address is not a source.  The asynchronous हाल handles this
 * implicitly, the synchronous हाल needs to zero the destination block.
 * @ASYNC_TX_XOR_DROP_DST: this flag must be used अगर the destination address is
 * also one of the source addresses.  In the synchronous हाल the destination
 * address is an implied source, whereas the asynchronous हाल it must be listed
 * as a source.  The destination address must be the first address in the source
 * array.
 * @ASYNC_TX_ACK: immediately ack the descriptor, precludes setting up a
 * dependency chain
 * @ASYNC_TX_FENCE: specअगरy that the next operation in the dependency
 * chain uses this operation's result as an input
 * @ASYNC_TX_PQ_XOR_DST: करो not overग_लिखो the syndrome but XOR it with the
 * input data. Required क्रम rmw हाल.
 */
क्रमागत async_tx_flags अणु
	ASYNC_TX_XOR_ZERO_DST	 = (1 << 0),
	ASYNC_TX_XOR_DROP_DST	 = (1 << 1),
	ASYNC_TX_ACK		 = (1 << 2),
	ASYNC_TX_FENCE		 = (1 << 3),
	ASYNC_TX_PQ_XOR_DST	 = (1 << 4),
पूर्ण;

/**
 * काष्ठा async_submit_ctl - async_tx submission/completion modअगरiers
 * @flags: submission modअगरiers
 * @depend_tx: parent dependency of the current operation being submitted
 * @cb_fn: callback routine to run at operation completion
 * @cb_param: parameter क्रम the callback routine
 * @scribble: caller provided space क्रम dma/page address conversions
 */
काष्ठा async_submit_ctl अणु
	क्रमागत async_tx_flags flags;
	काष्ठा dma_async_tx_descriptor *depend_tx;
	dma_async_tx_callback cb_fn;
	व्योम *cb_param;
	व्योम *scribble;
पूर्ण;

#अगर defined(CONFIG_DMA_ENGINE) && !defined(CONFIG_ASYNC_TX_CHANNEL_SWITCH)
#घोषणा async_tx_issue_pending_all dma_issue_pending_all

/**
 * async_tx_issue_pending - send pending descriptor to the hardware channel
 * @tx: descriptor handle to retrieve hardware context
 *
 * Note: any dependent operations will have alपढ़ोy been issued by
 * async_tx_channel_चयन, or (in the हाल of no channel चयन) will
 * be alपढ़ोy pending on this channel.
 */
अटल अंतरभूत व्योम async_tx_issue_pending(काष्ठा dma_async_tx_descriptor *tx)
अणु
	अगर (likely(tx)) अणु
		काष्ठा dma_chan *chan = tx->chan;
		काष्ठा dma_device *dma = chan->device;

		dma->device_issue_pending(chan);
	पूर्ण
पूर्ण
#अगर_घोषित CONFIG_ARCH_HAS_ASYNC_TX_FIND_CHANNEL
#समावेश <यंत्र/async_tx.h>
#अन्यथा
#घोषणा async_tx_find_channel(dep, type, dst, dst_count, src, src_count, len) \
	 __async_tx_find_channel(dep, type)
काष्ठा dma_chan *
__async_tx_find_channel(काष्ठा async_submit_ctl *submit,
			क्रमागत dma_transaction_type tx_type);
#पूर्ण_अगर /* CONFIG_ARCH_HAS_ASYNC_TX_FIND_CHANNEL */
#अन्यथा
अटल अंतरभूत व्योम async_tx_issue_pending_all(व्योम)
अणु
	करो अणु पूर्ण जबतक (0);
पूर्ण

अटल अंतरभूत व्योम async_tx_issue_pending(काष्ठा dma_async_tx_descriptor *tx)
अणु
	करो अणु पूर्ण जबतक (0);
पूर्ण

अटल अंतरभूत काष्ठा dma_chan *
async_tx_find_channel(काष्ठा async_submit_ctl *submit,
		      क्रमागत dma_transaction_type tx_type, काष्ठा page **dst,
		      पूर्णांक dst_count, काष्ठा page **src, पूर्णांक src_count,
		      माप_प्रकार len)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/**
 * async_tx_sync_epilog - actions to take अगर an operation is run synchronously
 * @cb_fn: function to call when the transaction completes
 * @cb_fn_param: parameter to pass to the callback routine
 */
अटल अंतरभूत व्योम
async_tx_sync_epilog(काष्ठा async_submit_ctl *submit)
अणु
	अगर (submit->cb_fn)
		submit->cb_fn(submit->cb_param);
पूर्ण

प्रकार जोड़ अणु
	अचिन्हित दीर्घ addr;
	काष्ठा page *page;
	dma_addr_t dma;
पूर्ण addr_conv_t;

अटल अंतरभूत व्योम
init_async_submit(काष्ठा async_submit_ctl *args, क्रमागत async_tx_flags flags,
		  काष्ठा dma_async_tx_descriptor *tx,
		  dma_async_tx_callback cb_fn, व्योम *cb_param,
		  addr_conv_t *scribble)
अणु
	args->flags = flags;
	args->depend_tx = tx;
	args->cb_fn = cb_fn;
	args->cb_param = cb_param;
	args->scribble = scribble;
पूर्ण

व्योम async_tx_submit(काष्ठा dma_chan *chan, काष्ठा dma_async_tx_descriptor *tx,
		     काष्ठा async_submit_ctl *submit);

काष्ठा dma_async_tx_descriptor *
async_xor(काष्ठा page *dest, काष्ठा page **src_list, अचिन्हित पूर्णांक offset,
	  पूर्णांक src_cnt, माप_प्रकार len, काष्ठा async_submit_ctl *submit);

काष्ठा dma_async_tx_descriptor *
async_xor_offs(काष्ठा page *dest, अचिन्हित पूर्णांक offset,
		काष्ठा page **src_list, अचिन्हित पूर्णांक *src_offset,
		पूर्णांक src_cnt, माप_प्रकार len, काष्ठा async_submit_ctl *submit);

काष्ठा dma_async_tx_descriptor *
async_xor_val(काष्ठा page *dest, काष्ठा page **src_list, अचिन्हित पूर्णांक offset,
	      पूर्णांक src_cnt, माप_प्रकार len, क्रमागत sum_check_flags *result,
	      काष्ठा async_submit_ctl *submit);

काष्ठा dma_async_tx_descriptor *
async_xor_val_offs(काष्ठा page *dest, अचिन्हित पूर्णांक offset,
		काष्ठा page **src_list, अचिन्हित पूर्णांक *src_offset,
		पूर्णांक src_cnt, माप_प्रकार len, क्रमागत sum_check_flags *result,
		काष्ठा async_submit_ctl *submit);

काष्ठा dma_async_tx_descriptor *
async_स_नकल(काष्ठा page *dest, काष्ठा page *src, अचिन्हित पूर्णांक dest_offset,
	     अचिन्हित पूर्णांक src_offset, माप_प्रकार len,
	     काष्ठा async_submit_ctl *submit);

काष्ठा dma_async_tx_descriptor *async_trigger_callback(काष्ठा async_submit_ctl *submit);

काष्ठा dma_async_tx_descriptor *
async_gen_syndrome(काष्ठा page **blocks, अचिन्हित पूर्णांक *offsets, पूर्णांक src_cnt,
		   माप_प्रकार len, काष्ठा async_submit_ctl *submit);

काष्ठा dma_async_tx_descriptor *
async_syndrome_val(काष्ठा page **blocks, अचिन्हित पूर्णांक *offsets, पूर्णांक src_cnt,
		   माप_प्रकार len, क्रमागत sum_check_flags *pqres, काष्ठा page *spare,
		   अचिन्हित पूर्णांक s_off, काष्ठा async_submit_ctl *submit);

काष्ठा dma_async_tx_descriptor *
async_raid6_2data_recov(पूर्णांक src_num, माप_प्रकार bytes, पूर्णांक faila, पूर्णांक failb,
			काष्ठा page **ptrs, अचिन्हित पूर्णांक *offs,
			काष्ठा async_submit_ctl *submit);

काष्ठा dma_async_tx_descriptor *
async_raid6_datap_recov(पूर्णांक src_num, माप_प्रकार bytes, पूर्णांक faila,
			काष्ठा page **ptrs, अचिन्हित पूर्णांक *offs,
			काष्ठा async_submit_ctl *submit);

व्योम async_tx_quiesce(काष्ठा dma_async_tx_descriptor **tx);
#पूर्ण_अगर /* _ASYNC_TX_H_ */
