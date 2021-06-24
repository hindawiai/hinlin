<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Dmaengine driver base library क्रम DMA controllers, found on SH-based SoCs
 *
 * extracted from shdma.c
 *
 * Copyright (C) 2011-2012 Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 * Copyright (C) 2009 Nobuhiro Iwamatsu <iwamatsu.nobuhiro@renesas.com>
 * Copyright (C) 2009 Renesas Solutions, Inc. All rights reserved.
 * Copyright (C) 2007 Freescale Semiconductor, Inc. All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/shdma-base.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "../dmaengine.h"

/* DMA descriptor control */
क्रमागत shdma_desc_status अणु
	DESC_IDLE,
	DESC_PREPARED,
	DESC_SUBMITTED,
	DESC_COMPLETED,	/* completed, have to call callback */
	DESC_WAITING,	/* callback called, रुकोing क्रम ack / re-submit */
पूर्ण;

#घोषणा NR_DESCS_PER_CHANNEL 32

#घोषणा to_shdma_chan(c) container_of(c, काष्ठा shdma_chan, dma_chan)
#घोषणा to_shdma_dev(d) container_of(d, काष्ठा shdma_dev, dma_dev)

/*
 * For slave DMA we assume, that there is a finite number of DMA slaves in the
 * प्रणाली, and that each such slave can only use a finite number of channels.
 * We use slave channel IDs to make sure, that no such slave channel ID is
 * allocated more than once.
 */
अटल अचिन्हित पूर्णांक slave_num = 256;
module_param(slave_num, uपूर्णांक, 0444);

/* A biपंचांगask with slave_num bits */
अटल अचिन्हित दीर्घ *shdma_slave_used;

/* Called under spin_lock_irq(&schan->chan_lock") */
अटल व्योम shdma_chan_xfer_ld_queue(काष्ठा shdma_chan *schan)
अणु
	काष्ठा shdma_dev *sdev = to_shdma_dev(schan->dma_chan.device);
	स्थिर काष्ठा shdma_ops *ops = sdev->ops;
	काष्ठा shdma_desc *sdesc;

	/* DMA work check */
	अगर (ops->channel_busy(schan))
		वापस;

	/* Find the first not transferred descriptor */
	list_क्रम_each_entry(sdesc, &schan->ld_queue, node)
		अगर (sdesc->mark == DESC_SUBMITTED) अणु
			ops->start_xfer(schan, sdesc);
			अवरोध;
		पूर्ण
पूर्ण

अटल dma_cookie_t shdma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा shdma_desc *chunk, *c, *desc =
		container_of(tx, काष्ठा shdma_desc, async_tx);
	काष्ठा shdma_chan *schan = to_shdma_chan(tx->chan);
	dma_async_tx_callback callback = tx->callback;
	dma_cookie_t cookie;
	bool घातer_up;

	spin_lock_irq(&schan->chan_lock);

	घातer_up = list_empty(&schan->ld_queue);

	cookie = dma_cookie_assign(tx);

	/* Mark all chunks of this descriptor as submitted, move to the queue */
	list_क्रम_each_entry_safe(chunk, c, desc->node.prev, node) अणु
		/*
		 * All chunks are on the global ld_मुक्त, so, we have to find
		 * the end of the chain ourselves
		 */
		अगर (chunk != desc && (chunk->mark == DESC_IDLE ||
				      chunk->async_tx.cookie > 0 ||
				      chunk->async_tx.cookie == -EBUSY ||
				      &chunk->node == &schan->ld_मुक्त))
			अवरोध;
		chunk->mark = DESC_SUBMITTED;
		अगर (chunk->chunks == 1) अणु
			chunk->async_tx.callback = callback;
			chunk->async_tx.callback_param = tx->callback_param;
		पूर्ण अन्यथा अणु
			/* Callback goes to the last chunk */
			chunk->async_tx.callback = शून्य;
		पूर्ण
		chunk->cookie = cookie;
		list_move_tail(&chunk->node, &schan->ld_queue);

		dev_dbg(schan->dev, "submit #%d@%p on %d\n",
			tx->cookie, &chunk->async_tx, schan->id);
	पूर्ण

	अगर (घातer_up) अणु
		पूर्णांक ret;
		schan->pm_state = SHDMA_PM_BUSY;

		ret = pm_runसमय_get(schan->dev);

		spin_unlock_irq(&schan->chan_lock);
		अगर (ret < 0)
			dev_err(schan->dev, "%s(): GET = %d\n", __func__, ret);

		pm_runसमय_barrier(schan->dev);

		spin_lock_irq(&schan->chan_lock);

		/* Have we been reset, जबतक रुकोing? */
		अगर (schan->pm_state != SHDMA_PM_ESTABLISHED) अणु
			काष्ठा shdma_dev *sdev =
				to_shdma_dev(schan->dma_chan.device);
			स्थिर काष्ठा shdma_ops *ops = sdev->ops;
			dev_dbg(schan->dev, "Bring up channel %d\n",
				schan->id);
			/*
			 * TODO: .xfer_setup() might fail on some platक्रमms.
			 * Make it पूर्णांक then, on error हटाओ chunks from the
			 * queue again
			 */
			ops->setup_xfer(schan, schan->slave_id);

			अगर (schan->pm_state == SHDMA_PM_PENDING)
				shdma_chan_xfer_ld_queue(schan);
			schan->pm_state = SHDMA_PM_ESTABLISHED;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Tell .device_issue_pending() not to run the queue, पूर्णांकerrupts
		 * will करो it anyway
		 */
		schan->pm_state = SHDMA_PM_PENDING;
	पूर्ण

	spin_unlock_irq(&schan->chan_lock);

	वापस cookie;
पूर्ण

/* Called with desc_lock held */
अटल काष्ठा shdma_desc *shdma_get_desc(काष्ठा shdma_chan *schan)
अणु
	काष्ठा shdma_desc *sdesc;

	list_क्रम_each_entry(sdesc, &schan->ld_मुक्त, node)
		अगर (sdesc->mark != DESC_PREPARED) अणु
			BUG_ON(sdesc->mark != DESC_IDLE);
			list_del(&sdesc->node);
			वापस sdesc;
		पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक shdma_setup_slave(काष्ठा shdma_chan *schan, dma_addr_t slave_addr)
अणु
	काष्ठा shdma_dev *sdev = to_shdma_dev(schan->dma_chan.device);
	स्थिर काष्ठा shdma_ops *ops = sdev->ops;
	पूर्णांक ret, match;

	अगर (schan->dev->of_node) अणु
		match = schan->hw_req;
		ret = ops->set_slave(schan, match, slave_addr, true);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		match = schan->real_slave_id;
	पूर्ण

	अगर (schan->real_slave_id < 0 || schan->real_slave_id >= slave_num)
		वापस -EINVAL;

	अगर (test_and_set_bit(schan->real_slave_id, shdma_slave_used))
		वापस -EBUSY;

	ret = ops->set_slave(schan, match, slave_addr, false);
	अगर (ret < 0) अणु
		clear_bit(schan->real_slave_id, shdma_slave_used);
		वापस ret;
	पूर्ण

	schan->slave_id = schan->real_slave_id;

	वापस 0;
पूर्ण

अटल पूर्णांक shdma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा shdma_chan *schan = to_shdma_chan(chan);
	काष्ठा shdma_dev *sdev = to_shdma_dev(schan->dma_chan.device);
	स्थिर काष्ठा shdma_ops *ops = sdev->ops;
	काष्ठा shdma_desc *desc;
	काष्ठा shdma_slave *slave = chan->निजी;
	पूर्णांक ret, i;

	/*
	 * This relies on the guarantee from dmaengine that alloc_chan_resources
	 * never runs concurrently with itself or मुक्त_chan_resources.
	 */
	अगर (slave) अणु
		/* Legacy mode: .निजी is set in filter */
		schan->real_slave_id = slave->slave_id;
		ret = shdma_setup_slave(schan, 0);
		अगर (ret < 0)
			जाओ esetslave;
	पूर्ण अन्यथा अणु
		/* Normal mode: real_slave_id was set by filter */
		schan->slave_id = -EINVAL;
	पूर्ण

	schan->desc = kसुस्मृति(NR_DESCS_PER_CHANNEL,
			      sdev->desc_size, GFP_KERNEL);
	अगर (!schan->desc) अणु
		ret = -ENOMEM;
		जाओ edesसुस्मृति;
	पूर्ण
	schan->desc_num = NR_DESCS_PER_CHANNEL;

	क्रम (i = 0; i < NR_DESCS_PER_CHANNEL; i++) अणु
		desc = ops->embedded_desc(schan->desc, i);
		dma_async_tx_descriptor_init(&desc->async_tx,
					     &schan->dma_chan);
		desc->async_tx.tx_submit = shdma_tx_submit;
		desc->mark = DESC_IDLE;

		list_add(&desc->node, &schan->ld_मुक्त);
	पूर्ण

	वापस NR_DESCS_PER_CHANNEL;

edesसुस्मृति:
	अगर (slave)
esetslave:
		clear_bit(slave->slave_id, shdma_slave_used);
	chan->निजी = शून्य;
	वापस ret;
पूर्ण

/*
 * This is the standard shdma filter function to be used as a replacement to the
 * "old" method, using the .निजी poपूर्णांकer.
 * You always have to pass a valid slave id as the argument, old drivers that
 * pass ERR_PTR(-EINVAL) as a filter parameter and set it up in dma_slave_config
 * need to be updated so we can हटाओ the slave_id field from dma_slave_config.
 * parameter. If this filter is used, the slave driver, after calling
 * dma_request_channel(), will also have to call dmaengine_slave_config() with
 * .direction, and either .src_addr or .dst_addr set.
 *
 * NOTE: this filter करोesn't support multiple DMAC drivers with the DMA_SLAVE
 * capability! If this becomes a requirement, hardware glue drivers, using this
 * services would have to provide their own filters, which first would check
 * the device driver, similar to how other DMAC drivers, e.g., sa11x0-dma.c, करो
 * this, and only then, in हाल of a match, call this common filter.
 * NOTE 2: This filter function is also used in the DT हाल by shdma_of_xlate().
 * In that हाल the MID-RID value is used क्रम slave channel filtering and is
 * passed to this function in the "arg" parameter.
 */
bool shdma_chan_filter(काष्ठा dma_chan *chan, व्योम *arg)
अणु
	काष्ठा shdma_chan *schan;
	काष्ठा shdma_dev *sdev;
	पूर्णांक slave_id = (दीर्घ)arg;
	पूर्णांक ret;

	/* Only support channels handled by this driver. */
	अगर (chan->device->device_alloc_chan_resources !=
	    shdma_alloc_chan_resources)
		वापस false;

	schan = to_shdma_chan(chan);
	sdev = to_shdma_dev(chan->device);

	/*
	 * For DT, the schan->slave_id field is generated by the
	 * set_slave function from the slave ID that is passed in
	 * from xlate. For the non-DT हाल, the slave ID is
	 * directly passed पूर्णांकo the filter function by the driver
	 */
	अगर (schan->dev->of_node) अणु
		ret = sdev->ops->set_slave(schan, slave_id, 0, true);
		अगर (ret < 0)
			वापस false;

		schan->real_slave_id = schan->slave_id;
		वापस true;
	पूर्ण

	अगर (slave_id < 0) अणु
		/* No slave requested - arbitrary channel */
		dev_warn(sdev->dma_dev.dev, "invalid slave ID passed to dma_request_slave\n");
		वापस true;
	पूर्ण

	अगर (slave_id >= slave_num)
		वापस false;

	ret = sdev->ops->set_slave(schan, slave_id, 0, true);
	अगर (ret < 0)
		वापस false;

	schan->real_slave_id = slave_id;

	वापस true;
पूर्ण
EXPORT_SYMBOL(shdma_chan_filter);

अटल dma_async_tx_callback __ld_cleanup(काष्ठा shdma_chan *schan, bool all)
अणु
	काष्ठा shdma_desc *desc, *_desc;
	/* Is the "exposed" head of a chain acked? */
	bool head_acked = false;
	dma_cookie_t cookie = 0;
	dma_async_tx_callback callback = शून्य;
	काष्ठा dmaengine_desc_callback cb;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(cyclic_list);

	स_रखो(&cb, 0, माप(cb));
	spin_lock_irqsave(&schan->chan_lock, flags);
	list_क्रम_each_entry_safe(desc, _desc, &schan->ld_queue, node) अणु
		काष्ठा dma_async_tx_descriptor *tx = &desc->async_tx;

		BUG_ON(tx->cookie > 0 && tx->cookie != desc->cookie);
		BUG_ON(desc->mark != DESC_SUBMITTED &&
		       desc->mark != DESC_COMPLETED &&
		       desc->mark != DESC_WAITING);

		/*
		 * queue is ordered, and we use this loop to (1) clean up all
		 * completed descriptors, and to (2) update descriptor flags of
		 * any chunks in a (partially) completed chain
		 */
		अगर (!all && desc->mark == DESC_SUBMITTED &&
		    desc->cookie != cookie)
			अवरोध;

		अगर (tx->cookie > 0)
			cookie = tx->cookie;

		अगर (desc->mark == DESC_COMPLETED && desc->chunks == 1) अणु
			अगर (schan->dma_chan.completed_cookie != desc->cookie - 1)
				dev_dbg(schan->dev,
					"Completing cookie %d, expected %d\n",
					desc->cookie,
					schan->dma_chan.completed_cookie + 1);
			schan->dma_chan.completed_cookie = desc->cookie;
		पूर्ण

		/* Call callback on the last chunk */
		अगर (desc->mark == DESC_COMPLETED && tx->callback) अणु
			desc->mark = DESC_WAITING;
			dmaengine_desc_get_callback(tx, &cb);
			callback = tx->callback;
			dev_dbg(schan->dev, "descriptor #%d@%p on %d callback\n",
				tx->cookie, tx, schan->id);
			BUG_ON(desc->chunks != 1);
			अवरोध;
		पूर्ण

		अगर (tx->cookie > 0 || tx->cookie == -EBUSY) अणु
			अगर (desc->mark == DESC_COMPLETED) अणु
				BUG_ON(tx->cookie < 0);
				desc->mark = DESC_WAITING;
			पूर्ण
			head_acked = async_tx_test_ack(tx);
		पूर्ण अन्यथा अणु
			चयन (desc->mark) अणु
			हाल DESC_COMPLETED:
				desc->mark = DESC_WAITING;
				fallthrough;
			हाल DESC_WAITING:
				अगर (head_acked)
					async_tx_ack(&desc->async_tx);
			पूर्ण
		पूर्ण

		dev_dbg(schan->dev, "descriptor %p #%d completed.\n",
			tx, tx->cookie);

		अगर (((desc->mark == DESC_COMPLETED ||
		      desc->mark == DESC_WAITING) &&
		     async_tx_test_ack(&desc->async_tx)) || all) अणु

			अगर (all || !desc->cyclic) अणु
				/* Remove from ld_queue list */
				desc->mark = DESC_IDLE;
				list_move(&desc->node, &schan->ld_मुक्त);
			पूर्ण अन्यथा अणु
				/* reuse as cyclic */
				desc->mark = DESC_SUBMITTED;
				list_move_tail(&desc->node, &cyclic_list);
			पूर्ण

			अगर (list_empty(&schan->ld_queue)) अणु
				dev_dbg(schan->dev, "Bring down channel %d\n", schan->id);
				pm_runसमय_put(schan->dev);
				schan->pm_state = SHDMA_PM_ESTABLISHED;
			पूर्ण अन्यथा अगर (schan->pm_state == SHDMA_PM_PENDING) अणु
				shdma_chan_xfer_ld_queue(schan);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (all && !callback)
		/*
		 * Terminating and the loop completed normally: क्रमgive
		 * uncompleted cookies
		 */
		schan->dma_chan.completed_cookie = schan->dma_chan.cookie;

	list_splice_tail(&cyclic_list, &schan->ld_queue);

	spin_unlock_irqrestore(&schan->chan_lock, flags);

	dmaengine_desc_callback_invoke(&cb, शून्य);

	वापस callback;
पूर्ण

/*
 * shdma_chan_ld_cleanup - Clean up link descriptors
 *
 * Clean up the ld_queue of DMA channel.
 */
अटल व्योम shdma_chan_ld_cleanup(काष्ठा shdma_chan *schan, bool all)
अणु
	जबतक (__ld_cleanup(schan, all))
		;
पूर्ण

/*
 * shdma_मुक्त_chan_resources - Free all resources of the channel.
 */
अटल व्योम shdma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा shdma_chan *schan = to_shdma_chan(chan);
	काष्ठा shdma_dev *sdev = to_shdma_dev(chan->device);
	स्थिर काष्ठा shdma_ops *ops = sdev->ops;
	LIST_HEAD(list);

	/* Protect against ISR */
	spin_lock_irq(&schan->chan_lock);
	ops->halt_channel(schan);
	spin_unlock_irq(&schan->chan_lock);

	/* Now no new पूर्णांकerrupts will occur */

	/* Prepared and not submitted descriptors can still be on the queue */
	अगर (!list_empty(&schan->ld_queue))
		shdma_chan_ld_cleanup(schan, true);

	अगर (schan->slave_id >= 0) अणु
		/* The caller is holding dma_list_mutex */
		clear_bit(schan->slave_id, shdma_slave_used);
		chan->निजी = शून्य;
	पूर्ण

	schan->real_slave_id = 0;

	spin_lock_irq(&schan->chan_lock);

	list_splice_init(&schan->ld_मुक्त, &list);
	schan->desc_num = 0;

	spin_unlock_irq(&schan->chan_lock);

	kमुक्त(schan->desc);
पूर्ण

/**
 * shdma_add_desc - get, set up and वापस one transfer descriptor
 * @schan:	DMA channel
 * @flags:	DMA transfer flags
 * @dst:	destination DMA address, incremented when direction equals
 *		DMA_DEV_TO_MEM or DMA_MEM_TO_MEM
 * @src:	source DMA address, incremented when direction equals
 *		DMA_MEM_TO_DEV or DMA_MEM_TO_MEM
 * @len:	DMA transfer length
 * @first:	अगर शून्य, set to the current descriptor and cookie set to -EBUSY
 * @direction:	needed क्रम slave DMA to decide which address to keep स्थिरant,
 *		equals DMA_MEM_TO_MEM क्रम MEMCPY
 * Returns 0 or an error
 * Locks: called with desc_lock held
 */
अटल काष्ठा shdma_desc *shdma_add_desc(काष्ठा shdma_chan *schan,
	अचिन्हित दीर्घ flags, dma_addr_t *dst, dma_addr_t *src, माप_प्रकार *len,
	काष्ठा shdma_desc **first, क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा shdma_dev *sdev = to_shdma_dev(schan->dma_chan.device);
	स्थिर काष्ठा shdma_ops *ops = sdev->ops;
	काष्ठा shdma_desc *new;
	माप_प्रकार copy_size = *len;

	अगर (!copy_size)
		वापस शून्य;

	/* Allocate the link descriptor from the मुक्त list */
	new = shdma_get_desc(schan);
	अगर (!new) अणु
		dev_err(schan->dev, "No free link descriptor available\n");
		वापस शून्य;
	पूर्ण

	ops->desc_setup(schan, new, *src, *dst, &copy_size);

	अगर (!*first) अणु
		/* First desc */
		new->async_tx.cookie = -EBUSY;
		*first = new;
	पूर्ण अन्यथा अणु
		/* Other desc - invisible to the user */
		new->async_tx.cookie = -EINVAL;
	पूर्ण

	dev_dbg(schan->dev,
		"chaining (%zu/%zu)@%pad -> %pad with %p, cookie %d\n",
		copy_size, *len, src, dst, &new->async_tx,
		new->async_tx.cookie);

	new->mark = DESC_PREPARED;
	new->async_tx.flags = flags;
	new->direction = direction;
	new->partial = 0;

	*len -= copy_size;
	अगर (direction == DMA_MEM_TO_MEM || direction == DMA_MEM_TO_DEV)
		*src += copy_size;
	अगर (direction == DMA_MEM_TO_MEM || direction == DMA_DEV_TO_MEM)
		*dst += copy_size;

	वापस new;
पूर्ण

/*
 * shdma_prep_sg - prepare transfer descriptors from an SG list
 *
 * Common routine क्रम खुला (MEMCPY) and slave DMA. The MEMCPY हाल is also
 * converted to scatter-gather to guarantee consistent locking and a correct
 * list manipulation. For slave DMA direction carries the usual meaning, and,
 * logically, the SG list is RAM and the addr variable contains slave address,
 * e.g., the FIFO I/O रेजिस्टर. For MEMCPY direction equals DMA_MEM_TO_MEM
 * and the SG list contains only one element and poपूर्णांकs at the source buffer.
 */
अटल काष्ठा dma_async_tx_descriptor *shdma_prep_sg(काष्ठा shdma_chan *schan,
	काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sg_len, dma_addr_t *addr,
	क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags, bool cyclic)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा shdma_desc *first = शून्य, *new = शून्य /* compiler... */;
	LIST_HEAD(tx_list);
	पूर्णांक chunks = 0;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, sg_len, i)
		chunks += DIV_ROUND_UP(sg_dma_len(sg), schan->max_xfer_len);

	/* Have to lock the whole loop to protect against concurrent release */
	spin_lock_irqsave(&schan->chan_lock, irq_flags);

	/*
	 * Chaining:
	 * first descriptor is what user is dealing with in all API calls, its
	 *	cookie is at first set to -EBUSY, at tx-submit to a positive
	 *	number
	 * अगर more than one chunk is needed further chunks have cookie = -EINVAL
	 * the last chunk, अगर not equal to the first, has cookie = -ENOSPC
	 * all chunks are linked onto the tx_list head with their .node heads
	 *	only during this function, then they are immediately spliced
	 *	back onto the मुक्त list in क्रमm of a chain
	 */
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		dma_addr_t sg_addr = sg_dma_address(sg);
		माप_प्रकार len = sg_dma_len(sg);

		अगर (!len)
			जाओ err_get_desc;

		करो अणु
			dev_dbg(schan->dev, "Add SG #%d@%p[%zu], dma %pad\n",
				i, sg, len, &sg_addr);

			अगर (direction == DMA_DEV_TO_MEM)
				new = shdma_add_desc(schan, flags,
						&sg_addr, addr, &len, &first,
						direction);
			अन्यथा
				new = shdma_add_desc(schan, flags,
						addr, &sg_addr, &len, &first,
						direction);
			अगर (!new)
				जाओ err_get_desc;

			new->cyclic = cyclic;
			अगर (cyclic)
				new->chunks = 1;
			अन्यथा
				new->chunks = chunks--;
			list_add_tail(&new->node, &tx_list);
		पूर्ण जबतक (len);
	पूर्ण

	अगर (new != first)
		new->async_tx.cookie = -ENOSPC;

	/* Put them back on the मुक्त list, so, they करोn't get lost */
	list_splice_tail(&tx_list, &schan->ld_मुक्त);

	spin_unlock_irqrestore(&schan->chan_lock, irq_flags);

	वापस &first->async_tx;

err_get_desc:
	list_क्रम_each_entry(new, &tx_list, node)
		new->mark = DESC_IDLE;
	list_splice(&tx_list, &schan->ld_मुक्त);

	spin_unlock_irqrestore(&schan->chan_lock, irq_flags);

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *shdma_prep_स_नकल(
	काष्ठा dma_chan *chan, dma_addr_t dma_dest, dma_addr_t dma_src,
	माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा shdma_chan *schan = to_shdma_chan(chan);
	काष्ठा scatterlist sg;

	अगर (!chan || !len)
		वापस शून्य;

	BUG_ON(!schan->desc_num);

	sg_init_table(&sg, 1);
	sg_set_page(&sg, pfn_to_page(PFN_DOWN(dma_src)), len,
		    offset_in_page(dma_src));
	sg_dma_address(&sg) = dma_src;
	sg_dma_len(&sg) = len;

	वापस shdma_prep_sg(schan, &sg, 1, &dma_dest, DMA_MEM_TO_MEM,
			     flags, false);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *shdma_prep_slave_sg(
	काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sg_len,
	क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा shdma_chan *schan = to_shdma_chan(chan);
	काष्ठा shdma_dev *sdev = to_shdma_dev(schan->dma_chan.device);
	स्थिर काष्ठा shdma_ops *ops = sdev->ops;
	पूर्णांक slave_id = schan->slave_id;
	dma_addr_t slave_addr;

	अगर (!chan)
		वापस शून्य;

	BUG_ON(!schan->desc_num);

	/* Someone calling slave DMA on a generic channel? */
	अगर (slave_id < 0 || !sg_len) अणु
		dev_warn(schan->dev, "%s: bad parameter: len=%d, id=%d\n",
			 __func__, sg_len, slave_id);
		वापस शून्य;
	पूर्ण

	slave_addr = ops->slave_addr(schan);

	वापस shdma_prep_sg(schan, sgl, sg_len, &slave_addr,
			     direction, flags, false);
पूर्ण

#घोषणा SHDMA_MAX_SG_LEN 32

अटल काष्ठा dma_async_tx_descriptor *shdma_prep_dma_cyclic(
	काष्ठा dma_chan *chan, dma_addr_t buf_addr, माप_प्रकार buf_len,
	माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा shdma_chan *schan = to_shdma_chan(chan);
	काष्ठा shdma_dev *sdev = to_shdma_dev(schan->dma_chan.device);
	काष्ठा dma_async_tx_descriptor *desc;
	स्थिर काष्ठा shdma_ops *ops = sdev->ops;
	अचिन्हित पूर्णांक sg_len = buf_len / period_len;
	पूर्णांक slave_id = schan->slave_id;
	dma_addr_t slave_addr;
	काष्ठा scatterlist *sgl;
	पूर्णांक i;

	अगर (!chan)
		वापस शून्य;

	BUG_ON(!schan->desc_num);

	अगर (sg_len > SHDMA_MAX_SG_LEN) अणु
		dev_err(schan->dev, "sg length %d exceeds limit %d",
				sg_len, SHDMA_MAX_SG_LEN);
		वापस शून्य;
	पूर्ण

	/* Someone calling slave DMA on a generic channel? */
	अगर (slave_id < 0 || (buf_len < period_len)) अणु
		dev_warn(schan->dev,
			"%s: bad parameter: buf_len=%zu, period_len=%zu, id=%d\n",
			__func__, buf_len, period_len, slave_id);
		वापस शून्य;
	पूर्ण

	slave_addr = ops->slave_addr(schan);

	/*
	 * Allocate the sg list dynamically as it would consumer too much stack
	 * space.
	 */
	sgl = kदो_स्मृति_array(sg_len, माप(*sgl), GFP_KERNEL);
	अगर (!sgl)
		वापस शून्य;

	sg_init_table(sgl, sg_len);

	क्रम (i = 0; i < sg_len; i++) अणु
		dma_addr_t src = buf_addr + (period_len * i);

		sg_set_page(&sgl[i], pfn_to_page(PFN_DOWN(src)), period_len,
			    offset_in_page(src));
		sg_dma_address(&sgl[i]) = src;
		sg_dma_len(&sgl[i]) = period_len;
	पूर्ण

	desc = shdma_prep_sg(schan, sgl, sg_len, &slave_addr,
			     direction, flags, true);

	kमुक्त(sgl);
	वापस desc;
पूर्ण

अटल पूर्णांक shdma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा shdma_chan *schan = to_shdma_chan(chan);
	काष्ठा shdma_dev *sdev = to_shdma_dev(chan->device);
	स्थिर काष्ठा shdma_ops *ops = sdev->ops;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&schan->chan_lock, flags);
	ops->halt_channel(schan);

	अगर (ops->get_partial && !list_empty(&schan->ld_queue)) अणु
		/* Record partial transfer */
		काष्ठा shdma_desc *desc = list_first_entry(&schan->ld_queue,
							   काष्ठा shdma_desc, node);
		desc->partial = ops->get_partial(schan, desc);
	पूर्ण

	spin_unlock_irqrestore(&schan->chan_lock, flags);

	shdma_chan_ld_cleanup(schan, true);

	वापस 0;
पूर्ण

अटल पूर्णांक shdma_config(काष्ठा dma_chan *chan,
			काष्ठा dma_slave_config *config)
अणु
	काष्ठा shdma_chan *schan = to_shdma_chan(chan);

	/*
	 * So far only .slave_id is used, but the slave drivers are
	 * encouraged to also set a transfer direction and an address.
	 */
	अगर (!config)
		वापस -EINVAL;

	/*
	 * overriding the slave_id through dma_slave_config is deprecated,
	 * but possibly some out-of-tree drivers still करो it.
	 */
	अगर (WARN_ON_ONCE(config->slave_id &&
			 config->slave_id != schan->real_slave_id))
		schan->real_slave_id = config->slave_id;

	/*
	 * We could lock this, but you shouldn't be configuring the
	 * channel, जबतक using it...
	 */
	वापस shdma_setup_slave(schan,
				 config->direction == DMA_DEV_TO_MEM ?
				 config->src_addr : config->dst_addr);
पूर्ण

अटल व्योम shdma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा shdma_chan *schan = to_shdma_chan(chan);

	spin_lock_irq(&schan->chan_lock);
	अगर (schan->pm_state == SHDMA_PM_ESTABLISHED)
		shdma_chan_xfer_ld_queue(schan);
	अन्यथा
		schan->pm_state = SHDMA_PM_PENDING;
	spin_unlock_irq(&schan->chan_lock);
पूर्ण

अटल क्रमागत dma_status shdma_tx_status(काष्ठा dma_chan *chan,
					dma_cookie_t cookie,
					काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा shdma_chan *schan = to_shdma_chan(chan);
	क्रमागत dma_status status;
	अचिन्हित दीर्घ flags;

	shdma_chan_ld_cleanup(schan, false);

	spin_lock_irqsave(&schan->chan_lock, flags);

	status = dma_cookie_status(chan, cookie, txstate);

	/*
	 * If we करोn't find cookie on the queue, it has been पातed and we have
	 * to report error
	 */
	अगर (status != DMA_COMPLETE) अणु
		काष्ठा shdma_desc *sdesc;
		status = DMA_ERROR;
		list_क्रम_each_entry(sdesc, &schan->ld_queue, node)
			अगर (sdesc->cookie == cookie) अणु
				status = DMA_IN_PROGRESS;
				अवरोध;
			पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&schan->chan_lock, flags);

	वापस status;
पूर्ण

/* Called from error IRQ or NMI */
bool shdma_reset(काष्ठा shdma_dev *sdev)
अणु
	स्थिर काष्ठा shdma_ops *ops = sdev->ops;
	काष्ठा shdma_chan *schan;
	अचिन्हित पूर्णांक handled = 0;
	पूर्णांक i;

	/* Reset all channels */
	shdma_क्रम_each_chan(schan, sdev, i) अणु
		काष्ठा shdma_desc *sdesc;
		LIST_HEAD(dl);

		अगर (!schan)
			जारी;

		spin_lock(&schan->chan_lock);

		/* Stop the channel */
		ops->halt_channel(schan);

		list_splice_init(&schan->ld_queue, &dl);

		अगर (!list_empty(&dl)) अणु
			dev_dbg(schan->dev, "Bring down channel %d\n", schan->id);
			pm_runसमय_put(schan->dev);
		पूर्ण
		schan->pm_state = SHDMA_PM_ESTABLISHED;

		spin_unlock(&schan->chan_lock);

		/* Complete all  */
		list_क्रम_each_entry(sdesc, &dl, node) अणु
			काष्ठा dma_async_tx_descriptor *tx = &sdesc->async_tx;

			sdesc->mark = DESC_IDLE;
			dmaengine_desc_get_callback_invoke(tx, शून्य);
		पूर्ण

		spin_lock(&schan->chan_lock);
		list_splice(&dl, &schan->ld_मुक्त);
		spin_unlock(&schan->chan_lock);

		handled++;
	पूर्ण

	वापस !!handled;
पूर्ण
EXPORT_SYMBOL(shdma_reset);

अटल irqवापस_t chan_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा shdma_chan *schan = dev;
	स्थिर काष्ठा shdma_ops *ops =
		to_shdma_dev(schan->dma_chan.device)->ops;
	irqवापस_t ret;

	spin_lock(&schan->chan_lock);

	ret = ops->chan_irq(schan, irq) ? IRQ_WAKE_THREAD : IRQ_NONE;

	spin_unlock(&schan->chan_lock);

	वापस ret;
पूर्ण

अटल irqवापस_t chan_irqt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा shdma_chan *schan = dev;
	स्थिर काष्ठा shdma_ops *ops =
		to_shdma_dev(schan->dma_chan.device)->ops;
	काष्ठा shdma_desc *sdesc;

	spin_lock_irq(&schan->chan_lock);
	list_क्रम_each_entry(sdesc, &schan->ld_queue, node) अणु
		अगर (sdesc->mark == DESC_SUBMITTED &&
		    ops->desc_completed(schan, sdesc)) अणु
			dev_dbg(schan->dev, "done #%d@%p\n",
				sdesc->async_tx.cookie, &sdesc->async_tx);
			sdesc->mark = DESC_COMPLETED;
			अवरोध;
		पूर्ण
	पूर्ण
	/* Next desc */
	shdma_chan_xfer_ld_queue(schan);
	spin_unlock_irq(&schan->chan_lock);

	shdma_chan_ld_cleanup(schan, false);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक shdma_request_irq(काष्ठा shdma_chan *schan, पूर्णांक irq,
			   अचिन्हित दीर्घ flags, स्थिर अक्षर *name)
अणु
	पूर्णांक ret = devm_request_thपढ़ोed_irq(schan->dev, irq, chan_irq,
					    chan_irqt, flags, name, schan);

	schan->irq = ret < 0 ? ret : irq;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(shdma_request_irq);

व्योम shdma_chan_probe(काष्ठा shdma_dev *sdev,
			   काष्ठा shdma_chan *schan, पूर्णांक id)
अणु
	schan->pm_state = SHDMA_PM_ESTABLISHED;

	/* reference काष्ठा dma_device */
	schan->dma_chan.device = &sdev->dma_dev;
	dma_cookie_init(&schan->dma_chan);

	schan->dev = sdev->dma_dev.dev;
	schan->id = id;

	अगर (!schan->max_xfer_len)
		schan->max_xfer_len = PAGE_SIZE;

	spin_lock_init(&schan->chan_lock);

	/* Init descripter manage list */
	INIT_LIST_HEAD(&schan->ld_queue);
	INIT_LIST_HEAD(&schan->ld_मुक्त);

	/* Add the channel to DMA device channel list */
	list_add_tail(&schan->dma_chan.device_node,
			&sdev->dma_dev.channels);
	sdev->schan[id] = schan;
पूर्ण
EXPORT_SYMBOL(shdma_chan_probe);

व्योम shdma_chan_हटाओ(काष्ठा shdma_chan *schan)
अणु
	list_del(&schan->dma_chan.device_node);
पूर्ण
EXPORT_SYMBOL(shdma_chan_हटाओ);

पूर्णांक shdma_init(काष्ठा device *dev, काष्ठा shdma_dev *sdev,
		    पूर्णांक chan_num)
अणु
	काष्ठा dma_device *dma_dev = &sdev->dma_dev;

	/*
	 * Require all call-backs क्रम now, they can trivially be made optional
	 * later as required
	 */
	अगर (!sdev->ops ||
	    !sdev->desc_size ||
	    !sdev->ops->embedded_desc ||
	    !sdev->ops->start_xfer ||
	    !sdev->ops->setup_xfer ||
	    !sdev->ops->set_slave ||
	    !sdev->ops->desc_setup ||
	    !sdev->ops->slave_addr ||
	    !sdev->ops->channel_busy ||
	    !sdev->ops->halt_channel ||
	    !sdev->ops->desc_completed)
		वापस -EINVAL;

	sdev->schan = kसुस्मृति(chan_num, माप(*sdev->schan), GFP_KERNEL);
	अगर (!sdev->schan)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&dma_dev->channels);

	/* Common and MEMCPY operations */
	dma_dev->device_alloc_chan_resources
		= shdma_alloc_chan_resources;
	dma_dev->device_मुक्त_chan_resources = shdma_मुक्त_chan_resources;
	dma_dev->device_prep_dma_स_नकल = shdma_prep_स_नकल;
	dma_dev->device_tx_status = shdma_tx_status;
	dma_dev->device_issue_pending = shdma_issue_pending;

	/* Compulsory क्रम DMA_SLAVE fields */
	dma_dev->device_prep_slave_sg = shdma_prep_slave_sg;
	dma_dev->device_prep_dma_cyclic = shdma_prep_dma_cyclic;
	dma_dev->device_config = shdma_config;
	dma_dev->device_terminate_all = shdma_terminate_all;

	dma_dev->dev = dev;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(shdma_init);

व्योम shdma_cleanup(काष्ठा shdma_dev *sdev)
अणु
	kमुक्त(sdev->schan);
पूर्ण
EXPORT_SYMBOL(shdma_cleanup);

अटल पूर्णांक __init shdma_enter(व्योम)
अणु
	shdma_slave_used = kसुस्मृति(DIV_ROUND_UP(slave_num, BITS_PER_LONG),
				   माप(दीर्घ),
				   GFP_KERNEL);
	अगर (!shdma_slave_used)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
module_init(shdma_enter);

अटल व्योम __निकास shdma_निकास(व्योम)
अणु
	kमुक्त(shdma_slave_used);
पूर्ण
module_निकास(shdma_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SH-DMA driver base library");
MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de>");
