<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013-2015 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/poll.h>
#समावेश <linux/iio/buffer_impl.h>
#समावेश <linux/iio/buffer-dma.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sizes.h>

/*
 * For DMA buffers the storage is sub-भागided पूर्णांकo so called blocks. Each block
 * has its own memory buffer. The size of the block is the granularity at which
 * memory is exchanged between the hardware and the application. Increasing the
 * basic unit of data exchange from one sample to one block decreases the
 * management overhead that is associated with each sample. E.g. अगर we say the
 * management overhead क्रम one exchange is x and the unit of exchange is one
 * sample the overhead will be x क्रम each sample. Whereas when using a block
 * which contains n samples the overhead per sample is reduced to x/n. This
 * allows to achieve much higher samplerates than what can be sustained with
 * the one sample approach.
 *
 * Blocks are exchanged between the DMA controller and the application via the
 * means of two queues. The incoming queue and the outgoing queue. Blocks on the
 * incoming queue are रुकोing क्रम the DMA controller to pick them up and fill
 * them with data. Block on the outgoing queue have been filled with data and
 * are रुकोing क्रम the application to dequeue them and पढ़ो the data.
 *
 * A block can be in one of the following states:
 *  * Owned by the application. In this state the application can पढ़ो data from
 *    the block.
 *  * On the incoming list: Blocks on the incoming list are queued up to be
 *    processed by the DMA controller.
 *  * Owned by the DMA controller: The DMA controller is processing the block
 *    and filling it with data.
 *  * On the outgoing list: Blocks on the outgoing list have been successfully
 *    processed by the DMA controller and contain data. They can be dequeued by
 *    the application.
 *  * Dead: A block that is dead has been marked as to be मुक्तd. It might still
 *    be owned by either the application or the DMA controller at the moment.
 *    But once they are करोne processing it instead of going to either the
 *    incoming or outgoing queue the block will be मुक्तd.
 *
 * In addition to this blocks are reference counted and the memory associated
 * with both the block काष्ठाure as well as the storage memory क्रम the block
 * will be मुक्तd when the last reference to the block is dropped. This means a
 * block must not be accessed without holding a reference.
 *
 * The iio_dma_buffer implementation provides a generic infraकाष्ठाure क्रम
 * managing the blocks.
 *
 * A driver क्रम a specअगरic piece of hardware that has DMA capabilities need to
 * implement the submit() callback from the iio_dma_buffer_ops काष्ठाure. This
 * callback is supposed to initiate the DMA transfer copying data from the
 * converter to the memory region of the block. Once the DMA transfer has been
 * completed the driver must call iio_dma_buffer_block_करोne() क्रम the completed
 * block.
 *
 * Prior to this it must set the bytes_used field of the block contains
 * the actual number of bytes in the buffer. Typically this will be equal to the
 * size of the block, but अगर the DMA hardware has certain alignment requirements
 * क्रम the transfer length it might choose to use less than the full size. In
 * either हाल it is expected that bytes_used is a multiple of the bytes per
 * datum, i.e. the block must not contain partial samples.
 *
 * The driver must call iio_dma_buffer_block_करोne() क्रम each block it has
 * received through its submit_block() callback, even अगर it करोes not actually
 * perक्रमm a DMA transfer क्रम the block, e.g. because the buffer was disabled
 * beक्रमe the block transfer was started. In this हाल it should set bytes_used
 * to 0.
 *
 * In addition it is recommended that a driver implements the पात() callback.
 * It will be called when the buffer is disabled and can be used to cancel
 * pending and stop active transfers.
 *
 * The specअगरic driver implementation should use the शेष callback
 * implementations provided by this module क्रम the iio_buffer_access_funcs
 * काष्ठा. It may overload some callbacks with custom variants अगर the hardware
 * has special requirements that are not handled by the generic functions. If a
 * driver chooses to overload a callback it has to ensure that the generic
 * callback is called from within the custom callback.
 */

अटल व्योम iio_buffer_block_release(काष्ठा kref *kref)
अणु
	काष्ठा iio_dma_buffer_block *block = container_of(kref,
		काष्ठा iio_dma_buffer_block, kref);

	WARN_ON(block->state != IIO_BLOCK_STATE_DEAD);

	dma_मुक्त_coherent(block->queue->dev, PAGE_ALIGN(block->size),
					block->vaddr, block->phys_addr);

	iio_buffer_put(&block->queue->buffer);
	kमुक्त(block);
पूर्ण

अटल व्योम iio_buffer_block_get(काष्ठा iio_dma_buffer_block *block)
अणु
	kref_get(&block->kref);
पूर्ण

अटल व्योम iio_buffer_block_put(काष्ठा iio_dma_buffer_block *block)
अणु
	kref_put(&block->kref, iio_buffer_block_release);
पूर्ण

/*
 * dma_मुक्त_coherent can sleep, hence we need to take some special care to be
 * able to drop a reference from an atomic context.
 */
अटल LIST_HEAD(iio_dma_buffer_dead_blocks);
अटल DEFINE_SPINLOCK(iio_dma_buffer_dead_blocks_lock);

अटल व्योम iio_dma_buffer_cleanup_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iio_dma_buffer_block *block, *_block;
	LIST_HEAD(block_list);

	spin_lock_irq(&iio_dma_buffer_dead_blocks_lock);
	list_splice_tail_init(&iio_dma_buffer_dead_blocks, &block_list);
	spin_unlock_irq(&iio_dma_buffer_dead_blocks_lock);

	list_क्रम_each_entry_safe(block, _block, &block_list, head)
		iio_buffer_block_release(&block->kref);
पूर्ण
अटल DECLARE_WORK(iio_dma_buffer_cleanup_work, iio_dma_buffer_cleanup_worker);

अटल व्योम iio_buffer_block_release_atomic(काष्ठा kref *kref)
अणु
	काष्ठा iio_dma_buffer_block *block;
	अचिन्हित दीर्घ flags;

	block = container_of(kref, काष्ठा iio_dma_buffer_block, kref);

	spin_lock_irqsave(&iio_dma_buffer_dead_blocks_lock, flags);
	list_add_tail(&block->head, &iio_dma_buffer_dead_blocks);
	spin_unlock_irqrestore(&iio_dma_buffer_dead_blocks_lock, flags);

	schedule_work(&iio_dma_buffer_cleanup_work);
पूर्ण

/*
 * Version of iio_buffer_block_put() that can be called from atomic context
 */
अटल व्योम iio_buffer_block_put_atomic(काष्ठा iio_dma_buffer_block *block)
अणु
	kref_put(&block->kref, iio_buffer_block_release_atomic);
पूर्ण

अटल काष्ठा iio_dma_buffer_queue *iio_buffer_to_queue(काष्ठा iio_buffer *buf)
अणु
	वापस container_of(buf, काष्ठा iio_dma_buffer_queue, buffer);
पूर्ण

अटल काष्ठा iio_dma_buffer_block *iio_dma_buffer_alloc_block(
	काष्ठा iio_dma_buffer_queue *queue, माप_प्रकार size)
अणु
	काष्ठा iio_dma_buffer_block *block;

	block = kzalloc(माप(*block), GFP_KERNEL);
	अगर (!block)
		वापस शून्य;

	block->vaddr = dma_alloc_coherent(queue->dev, PAGE_ALIGN(size),
		&block->phys_addr, GFP_KERNEL);
	अगर (!block->vaddr) अणु
		kमुक्त(block);
		वापस शून्य;
	पूर्ण

	block->size = size;
	block->state = IIO_BLOCK_STATE_DEQUEUED;
	block->queue = queue;
	INIT_LIST_HEAD(&block->head);
	kref_init(&block->kref);

	iio_buffer_get(&queue->buffer);

	वापस block;
पूर्ण

अटल व्योम _iio_dma_buffer_block_करोne(काष्ठा iio_dma_buffer_block *block)
अणु
	काष्ठा iio_dma_buffer_queue *queue = block->queue;

	/*
	 * The buffer has alपढ़ोy been मुक्तd by the application, just drop the
	 * reference.
	 */
	अगर (block->state != IIO_BLOCK_STATE_DEAD) अणु
		block->state = IIO_BLOCK_STATE_DONE;
		list_add_tail(&block->head, &queue->outgoing);
	पूर्ण
पूर्ण

/**
 * iio_dma_buffer_block_करोne() - Indicate that a block has been completed
 * @block: The completed block
 *
 * Should be called when the DMA controller has finished handling the block to
 * pass back ownership of the block to the queue.
 */
व्योम iio_dma_buffer_block_करोne(काष्ठा iio_dma_buffer_block *block)
अणु
	काष्ठा iio_dma_buffer_queue *queue = block->queue;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->list_lock, flags);
	_iio_dma_buffer_block_करोne(block);
	spin_unlock_irqrestore(&queue->list_lock, flags);

	iio_buffer_block_put_atomic(block);
	wake_up_पूर्णांकerruptible_poll(&queue->buffer.pollq, EPOLLIN | EPOLLRDNORM);
पूर्ण
EXPORT_SYMBOL_GPL(iio_dma_buffer_block_करोne);

/**
 * iio_dma_buffer_block_list_पात() - Indicate that a list block has been
 *   पातed
 * @queue: Queue क्रम which to complete blocks.
 * @list: List of पातed blocks. All blocks in this list must be from @queue.
 *
 * Typically called from the पात() callback after the DMA controller has been
 * stopped. This will set bytes_used to 0 क्रम each block in the list and then
 * hand the blocks back to the queue.
 */
व्योम iio_dma_buffer_block_list_पात(काष्ठा iio_dma_buffer_queue *queue,
	काष्ठा list_head *list)
अणु
	काष्ठा iio_dma_buffer_block *block, *_block;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->list_lock, flags);
	list_क्रम_each_entry_safe(block, _block, list, head) अणु
		list_del(&block->head);
		block->bytes_used = 0;
		_iio_dma_buffer_block_करोne(block);
		iio_buffer_block_put_atomic(block);
	पूर्ण
	spin_unlock_irqrestore(&queue->list_lock, flags);

	wake_up_पूर्णांकerruptible_poll(&queue->buffer.pollq, EPOLLIN | EPOLLRDNORM);
पूर्ण
EXPORT_SYMBOL_GPL(iio_dma_buffer_block_list_पात);

अटल bool iio_dma_block_reusable(काष्ठा iio_dma_buffer_block *block)
अणु
	/*
	 * If the core owns the block it can be re-used. This should be the
	 * शेष हाल when enabling the buffer, unless the DMA controller करोes
	 * not support पात and has not given back the block yet.
	 */
	चयन (block->state) अणु
	हाल IIO_BLOCK_STATE_DEQUEUED:
	हाल IIO_BLOCK_STATE_QUEUED:
	हाल IIO_BLOCK_STATE_DONE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * iio_dma_buffer_request_update() - DMA buffer request_update callback
 * @buffer: The buffer which to request an update
 *
 * Should be used as the iio_dma_buffer_request_update() callback क्रम
 * iio_buffer_access_ops काष्ठा क्रम DMA buffers.
 */
पूर्णांक iio_dma_buffer_request_update(काष्ठा iio_buffer *buffer)
अणु
	काष्ठा iio_dma_buffer_queue *queue = iio_buffer_to_queue(buffer);
	काष्ठा iio_dma_buffer_block *block;
	bool try_reuse = false;
	माप_प्रकार size;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/*
	 * Split the buffer पूर्णांकo two even parts. This is used as a द्विगुन
	 * buffering scheme with usually one block at a समय being used by the
	 * DMA and the other one by the application.
	 */
	size = DIV_ROUND_UP(queue->buffer.bytes_per_datum *
		queue->buffer.length, 2);

	mutex_lock(&queue->lock);

	/* Allocations are page aligned */
	अगर (PAGE_ALIGN(queue->fileio.block_size) == PAGE_ALIGN(size))
		try_reuse = true;

	queue->fileio.block_size = size;
	queue->fileio.active_block = शून्य;

	spin_lock_irq(&queue->list_lock);
	क्रम (i = 0; i < ARRAY_SIZE(queue->fileio.blocks); i++) अणु
		block = queue->fileio.blocks[i];

		/* If we can't re-use it मुक्त it */
		अगर (block && (!iio_dma_block_reusable(block) || !try_reuse))
			block->state = IIO_BLOCK_STATE_DEAD;
	पूर्ण

	/*
	 * At this poपूर्णांक all blocks are either owned by the core or marked as
	 * dead. This means we can reset the lists without having to fear
	 * corrution.
	 */
	INIT_LIST_HEAD(&queue->outgoing);
	spin_unlock_irq(&queue->list_lock);

	INIT_LIST_HEAD(&queue->incoming);

	क्रम (i = 0; i < ARRAY_SIZE(queue->fileio.blocks); i++) अणु
		अगर (queue->fileio.blocks[i]) अणु
			block = queue->fileio.blocks[i];
			अगर (block->state == IIO_BLOCK_STATE_DEAD) अणु
				/* Could not reuse it */
				iio_buffer_block_put(block);
				block = शून्य;
			पूर्ण अन्यथा अणु
				block->size = size;
			पूर्ण
		पूर्ण अन्यथा अणु
			block = शून्य;
		पूर्ण

		अगर (!block) अणु
			block = iio_dma_buffer_alloc_block(queue, size);
			अगर (!block) अणु
				ret = -ENOMEM;
				जाओ out_unlock;
			पूर्ण
			queue->fileio.blocks[i] = block;
		पूर्ण

		block->state = IIO_BLOCK_STATE_QUEUED;
		list_add_tail(&block->head, &queue->incoming);
	पूर्ण

out_unlock:
	mutex_unlock(&queue->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_dma_buffer_request_update);

अटल व्योम iio_dma_buffer_submit_block(काष्ठा iio_dma_buffer_queue *queue,
	काष्ठा iio_dma_buffer_block *block)
अणु
	पूर्णांक ret;

	/*
	 * If the hardware has alपढ़ोy been हटाओd we put the block पूर्णांकo
	 * limbo. It will neither be on the incoming nor outgoing list, nor will
	 * it ever complete. It will just रुको to be मुक्तd eventually.
	 */
	अगर (!queue->ops)
		वापस;

	block->state = IIO_BLOCK_STATE_ACTIVE;
	iio_buffer_block_get(block);
	ret = queue->ops->submit(queue, block);
	अगर (ret) अणु
		/*
		 * This is a bit of a problem and there is not much we can करो
		 * other then रुको क्रम the buffer to be disabled and re-enabled
		 * and try again. But it should not really happen unless we run
		 * out of memory or something similar.
		 *
		 * TODO: Implement support in the IIO core to allow buffers to
		 * notअगरy consumers that something went wrong and the buffer
		 * should be disabled.
		 */
		iio_buffer_block_put(block);
	पूर्ण
पूर्ण

/**
 * iio_dma_buffer_enable() - Enable DMA buffer
 * @buffer: IIO buffer to enable
 * @indio_dev: IIO device the buffer is attached to
 *
 * Needs to be called when the device that the buffer is attached to starts
 * sampling. Typically should be the iio_buffer_access_ops enable callback.
 *
 * This will allocate the DMA buffers and start the DMA transfers.
 */
पूर्णांक iio_dma_buffer_enable(काष्ठा iio_buffer *buffer,
	काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dma_buffer_queue *queue = iio_buffer_to_queue(buffer);
	काष्ठा iio_dma_buffer_block *block, *_block;

	mutex_lock(&queue->lock);
	queue->active = true;
	list_क्रम_each_entry_safe(block, _block, &queue->incoming, head) अणु
		list_del(&block->head);
		iio_dma_buffer_submit_block(queue, block);
	पूर्ण
	mutex_unlock(&queue->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iio_dma_buffer_enable);

/**
 * iio_dma_buffer_disable() - Disable DMA buffer
 * @buffer: IIO DMA buffer to disable
 * @indio_dev: IIO device the buffer is attached to
 *
 * Needs to be called when the device that the buffer is attached to stops
 * sampling. Typically should be the iio_buffer_access_ops disable callback.
 */
पूर्णांक iio_dma_buffer_disable(काष्ठा iio_buffer *buffer,
	काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dma_buffer_queue *queue = iio_buffer_to_queue(buffer);

	mutex_lock(&queue->lock);
	queue->active = false;

	अगर (queue->ops && queue->ops->पात)
		queue->ops->पात(queue);
	mutex_unlock(&queue->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iio_dma_buffer_disable);

अटल व्योम iio_dma_buffer_enqueue(काष्ठा iio_dma_buffer_queue *queue,
	काष्ठा iio_dma_buffer_block *block)
अणु
	अगर (block->state == IIO_BLOCK_STATE_DEAD) अणु
		iio_buffer_block_put(block);
	पूर्ण अन्यथा अगर (queue->active) अणु
		iio_dma_buffer_submit_block(queue, block);
	पूर्ण अन्यथा अणु
		block->state = IIO_BLOCK_STATE_QUEUED;
		list_add_tail(&block->head, &queue->incoming);
	पूर्ण
पूर्ण

अटल काष्ठा iio_dma_buffer_block *iio_dma_buffer_dequeue(
	काष्ठा iio_dma_buffer_queue *queue)
अणु
	काष्ठा iio_dma_buffer_block *block;

	spin_lock_irq(&queue->list_lock);
	block = list_first_entry_or_null(&queue->outgoing, काष्ठा
		iio_dma_buffer_block, head);
	अगर (block != शून्य) अणु
		list_del(&block->head);
		block->state = IIO_BLOCK_STATE_DEQUEUED;
	पूर्ण
	spin_unlock_irq(&queue->list_lock);

	वापस block;
पूर्ण

/**
 * iio_dma_buffer_पढ़ो() - DMA buffer पढ़ो callback
 * @buffer: Buffer to पढ़ो क्रमm
 * @n: Number of bytes to पढ़ो
 * @user_buffer: Userspace buffer to copy the data to
 *
 * Should be used as the पढ़ो callback क्रम iio_buffer_access_ops
 * काष्ठा क्रम DMA buffers.
 */
पूर्णांक iio_dma_buffer_पढ़ो(काष्ठा iio_buffer *buffer, माप_प्रकार n,
	अक्षर __user *user_buffer)
अणु
	काष्ठा iio_dma_buffer_queue *queue = iio_buffer_to_queue(buffer);
	काष्ठा iio_dma_buffer_block *block;
	पूर्णांक ret;

	अगर (n < buffer->bytes_per_datum)
		वापस -EINVAL;

	mutex_lock(&queue->lock);

	अगर (!queue->fileio.active_block) अणु
		block = iio_dma_buffer_dequeue(queue);
		अगर (block == शून्य) अणु
			ret = 0;
			जाओ out_unlock;
		पूर्ण
		queue->fileio.pos = 0;
		queue->fileio.active_block = block;
	पूर्ण अन्यथा अणु
		block = queue->fileio.active_block;
	पूर्ण

	n = roundकरोwn(n, buffer->bytes_per_datum);
	अगर (n > block->bytes_used - queue->fileio.pos)
		n = block->bytes_used - queue->fileio.pos;

	अगर (copy_to_user(user_buffer, block->vaddr + queue->fileio.pos, n)) अणु
		ret = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	queue->fileio.pos += n;

	अगर (queue->fileio.pos == block->bytes_used) अणु
		queue->fileio.active_block = शून्य;
		iio_dma_buffer_enqueue(queue, block);
	पूर्ण

	ret = n;

out_unlock:
	mutex_unlock(&queue->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_dma_buffer_पढ़ो);

/**
 * iio_dma_buffer_data_available() - DMA buffer data_available callback
 * @buf: Buffer to check क्रम data availability
 *
 * Should be used as the data_available callback क्रम iio_buffer_access_ops
 * काष्ठा क्रम DMA buffers.
 */
माप_प्रकार iio_dma_buffer_data_available(काष्ठा iio_buffer *buf)
अणु
	काष्ठा iio_dma_buffer_queue *queue = iio_buffer_to_queue(buf);
	काष्ठा iio_dma_buffer_block *block;
	माप_प्रकार data_available = 0;

	/*
	 * For counting the available bytes we'll use the size of the block not
	 * the number of actual bytes available in the block. Otherwise it is
	 * possible that we end up with a value that is lower than the watermark
	 * but won't increase since all blocks are in use.
	 */

	mutex_lock(&queue->lock);
	अगर (queue->fileio.active_block)
		data_available += queue->fileio.active_block->size;

	spin_lock_irq(&queue->list_lock);
	list_क्रम_each_entry(block, &queue->outgoing, head)
		data_available += block->size;
	spin_unlock_irq(&queue->list_lock);
	mutex_unlock(&queue->lock);

	वापस data_available;
पूर्ण
EXPORT_SYMBOL_GPL(iio_dma_buffer_data_available);

/**
 * iio_dma_buffer_set_bytes_per_datum() - DMA buffer set_bytes_per_datum callback
 * @buffer: Buffer to set the bytes-per-datum क्रम
 * @bpd: The new bytes-per-datum value
 *
 * Should be used as the set_bytes_per_datum callback क्रम iio_buffer_access_ops
 * काष्ठा क्रम DMA buffers.
 */
पूर्णांक iio_dma_buffer_set_bytes_per_datum(काष्ठा iio_buffer *buffer, माप_प्रकार bpd)
अणु
	buffer->bytes_per_datum = bpd;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iio_dma_buffer_set_bytes_per_datum);

/**
 * iio_dma_buffer_set_length - DMA buffer set_length callback
 * @buffer: Buffer to set the length क्रम
 * @length: The new buffer length
 *
 * Should be used as the set_length callback क्रम iio_buffer_access_ops
 * काष्ठा क्रम DMA buffers.
 */
पूर्णांक iio_dma_buffer_set_length(काष्ठा iio_buffer *buffer, अचिन्हित पूर्णांक length)
अणु
	/* Aव्योम an invalid state */
	अगर (length < 2)
		length = 2;
	buffer->length = length;
	buffer->watermark = length / 2;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iio_dma_buffer_set_length);

/**
 * iio_dma_buffer_init() - Initialize DMA buffer queue
 * @queue: Buffer to initialize
 * @dev: DMA device
 * @ops: DMA buffer queue callback operations
 *
 * The DMA device will be used by the queue to करो DMA memory allocations. So it
 * should refer to the device that will perक्रमm the DMA to ensure that
 * allocations are करोne from a memory region that can be accessed by the device.
 */
पूर्णांक iio_dma_buffer_init(काष्ठा iio_dma_buffer_queue *queue,
	काष्ठा device *dev, स्थिर काष्ठा iio_dma_buffer_ops *ops)
अणु
	iio_buffer_init(&queue->buffer);
	queue->buffer.length = PAGE_SIZE;
	queue->buffer.watermark = queue->buffer.length / 2;
	queue->dev = dev;
	queue->ops = ops;

	INIT_LIST_HEAD(&queue->incoming);
	INIT_LIST_HEAD(&queue->outgoing);

	mutex_init(&queue->lock);
	spin_lock_init(&queue->list_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iio_dma_buffer_init);

/**
 * iio_dma_buffer_निकास() - Cleanup DMA buffer queue
 * @queue: Buffer to cleanup
 *
 * After this function has completed it is safe to मुक्त any resources that are
 * associated with the buffer and are accessed inside the callback operations.
 */
व्योम iio_dma_buffer_निकास(काष्ठा iio_dma_buffer_queue *queue)
अणु
	अचिन्हित पूर्णांक i;

	mutex_lock(&queue->lock);

	spin_lock_irq(&queue->list_lock);
	क्रम (i = 0; i < ARRAY_SIZE(queue->fileio.blocks); i++) अणु
		अगर (!queue->fileio.blocks[i])
			जारी;
		queue->fileio.blocks[i]->state = IIO_BLOCK_STATE_DEAD;
	पूर्ण
	INIT_LIST_HEAD(&queue->outgoing);
	spin_unlock_irq(&queue->list_lock);

	INIT_LIST_HEAD(&queue->incoming);

	क्रम (i = 0; i < ARRAY_SIZE(queue->fileio.blocks); i++) अणु
		अगर (!queue->fileio.blocks[i])
			जारी;
		iio_buffer_block_put(queue->fileio.blocks[i]);
		queue->fileio.blocks[i] = शून्य;
	पूर्ण
	queue->fileio.active_block = शून्य;
	queue->ops = शून्य;

	mutex_unlock(&queue->lock);
पूर्ण
EXPORT_SYMBOL_GPL(iio_dma_buffer_निकास);

/**
 * iio_dma_buffer_release() - Release final buffer resources
 * @queue: Buffer to release
 *
 * Frees resources that can't yet be मुक्तd in iio_dma_buffer_निकास(). Should be
 * called in the buffers release callback implementation right beक्रमe मुक्तing
 * the memory associated with the buffer.
 */
व्योम iio_dma_buffer_release(काष्ठा iio_dma_buffer_queue *queue)
अणु
	mutex_destroy(&queue->lock);
पूर्ण
EXPORT_SYMBOL_GPL(iio_dma_buffer_release);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("DMA buffer for the IIO framework");
MODULE_LICENSE("GPL v2");
