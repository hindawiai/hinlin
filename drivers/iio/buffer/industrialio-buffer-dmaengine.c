<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014-2015 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/buffer_impl.h>
#समावेश <linux/iio/buffer-dma.h>
#समावेश <linux/iio/buffer-dmaengine.h>

/*
 * The IIO DMAengine buffer combines the generic IIO DMA buffer infraकाष्ठाure
 * with the DMAengine framework. The generic IIO DMA buffer infraकाष्ठाure is
 * used to manage the buffer memory and implement the IIO buffer operations
 * जबतक the DMAengine framework is used to perक्रमm the DMA transfers. Combined
 * this results in a device independent fully functional DMA buffer
 * implementation that can be used by device drivers क्रम peripherals which are
 * connected to a DMA controller which has a DMAengine driver implementation.
 */

काष्ठा dmaengine_buffer अणु
	काष्ठा iio_dma_buffer_queue queue;

	काष्ठा dma_chan *chan;
	काष्ठा list_head active;

	माप_प्रकार align;
	माप_प्रकार max_size;
पूर्ण;

अटल काष्ठा dmaengine_buffer *iio_buffer_to_dmaengine_buffer(
		काष्ठा iio_buffer *buffer)
अणु
	वापस container_of(buffer, काष्ठा dmaengine_buffer, queue.buffer);
पूर्ण

अटल व्योम iio_dmaengine_buffer_block_करोne(व्योम *data,
		स्थिर काष्ठा dmaengine_result *result)
अणु
	काष्ठा iio_dma_buffer_block *block = data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&block->queue->list_lock, flags);
	list_del(&block->head);
	spin_unlock_irqrestore(&block->queue->list_lock, flags);
	block->bytes_used -= result->residue;
	iio_dma_buffer_block_करोne(block);
पूर्ण

अटल पूर्णांक iio_dmaengine_buffer_submit_block(काष्ठा iio_dma_buffer_queue *queue,
	काष्ठा iio_dma_buffer_block *block)
अणु
	काष्ठा dmaengine_buffer *dmaengine_buffer =
		iio_buffer_to_dmaengine_buffer(&queue->buffer);
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;

	block->bytes_used = min(block->size, dmaengine_buffer->max_size);
	block->bytes_used = roundकरोwn(block->bytes_used,
			dmaengine_buffer->align);

	desc = dmaengine_prep_slave_single(dmaengine_buffer->chan,
		block->phys_addr, block->bytes_used, DMA_DEV_TO_MEM,
		DMA_PREP_INTERRUPT);
	अगर (!desc)
		वापस -ENOMEM;

	desc->callback_result = iio_dmaengine_buffer_block_करोne;
	desc->callback_param = block;

	cookie = dmaengine_submit(desc);
	अगर (dma_submit_error(cookie))
		वापस dma_submit_error(cookie);

	spin_lock_irq(&dmaengine_buffer->queue.list_lock);
	list_add_tail(&block->head, &dmaengine_buffer->active);
	spin_unlock_irq(&dmaengine_buffer->queue.list_lock);

	dma_async_issue_pending(dmaengine_buffer->chan);

	वापस 0;
पूर्ण

अटल व्योम iio_dmaengine_buffer_पात(काष्ठा iio_dma_buffer_queue *queue)
अणु
	काष्ठा dmaengine_buffer *dmaengine_buffer =
		iio_buffer_to_dmaengine_buffer(&queue->buffer);

	dmaengine_terminate_sync(dmaengine_buffer->chan);
	iio_dma_buffer_block_list_पात(queue, &dmaengine_buffer->active);
पूर्ण

अटल व्योम iio_dmaengine_buffer_release(काष्ठा iio_buffer *buf)
अणु
	काष्ठा dmaengine_buffer *dmaengine_buffer =
		iio_buffer_to_dmaengine_buffer(buf);

	iio_dma_buffer_release(&dmaengine_buffer->queue);
	kमुक्त(dmaengine_buffer);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_access_funcs iio_dmaengine_buffer_ops = अणु
	.पढ़ो = iio_dma_buffer_पढ़ो,
	.set_bytes_per_datum = iio_dma_buffer_set_bytes_per_datum,
	.set_length = iio_dma_buffer_set_length,
	.request_update = iio_dma_buffer_request_update,
	.enable = iio_dma_buffer_enable,
	.disable = iio_dma_buffer_disable,
	.data_available = iio_dma_buffer_data_available,
	.release = iio_dmaengine_buffer_release,

	.modes = INDIO_BUFFER_HARDWARE,
	.flags = INDIO_BUFFER_FLAG_FIXED_WATERMARK,
पूर्ण;

अटल स्थिर काष्ठा iio_dma_buffer_ops iio_dmaengine_शेष_ops = अणु
	.submit = iio_dmaengine_buffer_submit_block,
	.पात = iio_dmaengine_buffer_पात,
पूर्ण;

अटल sमाप_प्रकार iio_dmaengine_buffer_get_length_align(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iio_buffer *buffer = to_iio_dev_attr(attr)->buffer;
	काष्ठा dmaengine_buffer *dmaengine_buffer =
		iio_buffer_to_dmaengine_buffer(buffer);

	वापस प्र_लिखो(buf, "%zu\n", dmaengine_buffer->align);
पूर्ण

अटल IIO_DEVICE_ATTR(length_align_bytes, 0444,
		       iio_dmaengine_buffer_get_length_align, शून्य, 0);

अटल स्थिर काष्ठा attribute *iio_dmaengine_buffer_attrs[] = अणु
	&iio_dev_attr_length_align_bytes.dev_attr.attr,
	शून्य,
पूर्ण;

/**
 * iio_dmaengine_buffer_alloc() - Allocate new buffer which uses DMAengine
 * @dev: Parent device क्रम the buffer
 * @channel: DMA channel name, typically "rx".
 *
 * This allocates a new IIO buffer which पूर्णांकernally uses the DMAengine framework
 * to perक्रमm its transfers. The parent device will be used to request the DMA
 * channel.
 *
 * Once करोne using the buffer iio_dmaengine_buffer_मुक्त() should be used to
 * release it.
 */
अटल काष्ठा iio_buffer *iio_dmaengine_buffer_alloc(काष्ठा device *dev,
	स्थिर अक्षर *channel)
अणु
	काष्ठा dmaengine_buffer *dmaengine_buffer;
	अचिन्हित पूर्णांक width, src_width, dest_width;
	काष्ठा dma_slave_caps caps;
	काष्ठा dma_chan *chan;
	पूर्णांक ret;

	dmaengine_buffer = kzalloc(माप(*dmaengine_buffer), GFP_KERNEL);
	अगर (!dmaengine_buffer)
		वापस ERR_PTR(-ENOMEM);

	chan = dma_request_chan(dev, channel);
	अगर (IS_ERR(chan)) अणु
		ret = PTR_ERR(chan);
		जाओ err_मुक्त;
	पूर्ण

	ret = dma_get_slave_caps(chan, &caps);
	अगर (ret < 0)
		जाओ err_मुक्त;

	/* Needs to be aligned to the maximum of the minimums */
	अगर (caps.src_addr_widths)
		src_width = __ffs(caps.src_addr_widths);
	अन्यथा
		src_width = 1;
	अगर (caps.dst_addr_widths)
		dest_width = __ffs(caps.dst_addr_widths);
	अन्यथा
		dest_width = 1;
	width = max(src_width, dest_width);

	INIT_LIST_HEAD(&dmaengine_buffer->active);
	dmaengine_buffer->chan = chan;
	dmaengine_buffer->align = width;
	dmaengine_buffer->max_size = dma_get_max_seg_size(chan->device->dev);

	iio_dma_buffer_init(&dmaengine_buffer->queue, chan->device->dev,
		&iio_dmaengine_शेष_ops);

	dmaengine_buffer->queue.buffer.attrs = iio_dmaengine_buffer_attrs;
	dmaengine_buffer->queue.buffer.access = &iio_dmaengine_buffer_ops;

	वापस &dmaengine_buffer->queue.buffer;

err_मुक्त:
	kमुक्त(dmaengine_buffer);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * iio_dmaengine_buffer_मुक्त() - Free dmaengine buffer
 * @buffer: Buffer to मुक्त
 *
 * Frees a buffer previously allocated with iio_dmaengine_buffer_alloc().
 */
अटल व्योम iio_dmaengine_buffer_मुक्त(काष्ठा iio_buffer *buffer)
अणु
	काष्ठा dmaengine_buffer *dmaengine_buffer =
		iio_buffer_to_dmaengine_buffer(buffer);

	iio_dma_buffer_निकास(&dmaengine_buffer->queue);
	dma_release_channel(dmaengine_buffer->chan);

	iio_buffer_put(buffer);
पूर्ण

अटल व्योम __devm_iio_dmaengine_buffer_मुक्त(काष्ठा device *dev, व्योम *res)
अणु
	iio_dmaengine_buffer_मुक्त(*(काष्ठा iio_buffer **)res);
पूर्ण

/**
 * devm_iio_dmaengine_buffer_alloc() - Resource-managed iio_dmaengine_buffer_alloc()
 * @dev: Parent device क्रम the buffer
 * @channel: DMA channel name, typically "rx".
 *
 * This allocates a new IIO buffer which पूर्णांकernally uses the DMAengine framework
 * to perक्रमm its transfers. The parent device will be used to request the DMA
 * channel.
 *
 * The buffer will be स्वतःmatically de-allocated once the device माला_लो destroyed.
 */
अटल काष्ठा iio_buffer *devm_iio_dmaengine_buffer_alloc(काष्ठा device *dev,
	स्थिर अक्षर *channel)
अणु
	काष्ठा iio_buffer **bufferp, *buffer;

	bufferp = devres_alloc(__devm_iio_dmaengine_buffer_मुक्त,
			       माप(*bufferp), GFP_KERNEL);
	अगर (!bufferp)
		वापस ERR_PTR(-ENOMEM);

	buffer = iio_dmaengine_buffer_alloc(dev, channel);
	अगर (IS_ERR(buffer)) अणु
		devres_मुक्त(bufferp);
		वापस buffer;
	पूर्ण

	*bufferp = buffer;
	devres_add(dev, bufferp);

	वापस buffer;
पूर्ण

/**
 * devm_iio_dmaengine_buffer_setup() - Setup a DMA buffer क्रम an IIO device
 * @dev: Parent device क्रम the buffer
 * @indio_dev: IIO device to which to attach this buffer.
 * @channel: DMA channel name, typically "rx".
 *
 * This allocates a new IIO buffer with devm_iio_dmaengine_buffer_alloc()
 * and attaches it to an IIO device with iio_device_attach_buffer().
 * It also appends the INDIO_BUFFER_HARDWARE mode to the supported modes of the
 * IIO device.
 */
पूर्णांक devm_iio_dmaengine_buffer_setup(काष्ठा device *dev,
				    काष्ठा iio_dev *indio_dev,
				    स्थिर अक्षर *channel)
अणु
	काष्ठा iio_buffer *buffer;

	buffer = devm_iio_dmaengine_buffer_alloc(indio_dev->dev.parent,
						 channel);
	अगर (IS_ERR(buffer))
		वापस PTR_ERR(buffer);

	indio_dev->modes |= INDIO_BUFFER_HARDWARE;

	वापस iio_device_attach_buffer(indio_dev, buffer);
पूर्ण
EXPORT_SYMBOL_GPL(devm_iio_dmaengine_buffer_setup);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("DMA buffer for the IIO framework");
MODULE_LICENSE("GPL");
