<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2017 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/hw-consumer.h>
#समावेश <linux/iio/buffer_impl.h>

/**
 * काष्ठा iio_hw_consumer - IIO hw consumer block
 * @buffers: hardware buffers list head.
 * @channels: IIO provider channels.
 */
काष्ठा iio_hw_consumer अणु
	काष्ठा list_head buffers;
	काष्ठा iio_channel *channels;
पूर्ण;

काष्ठा hw_consumer_buffer अणु
	काष्ठा list_head head;
	काष्ठा iio_dev *indio_dev;
	काष्ठा iio_buffer buffer;
	दीर्घ scan_mask[];
पूर्ण;

अटल काष्ठा hw_consumer_buffer *iio_buffer_to_hw_consumer_buffer(
	काष्ठा iio_buffer *buffer)
अणु
	वापस container_of(buffer, काष्ठा hw_consumer_buffer, buffer);
पूर्ण

अटल व्योम iio_hw_buf_release(काष्ठा iio_buffer *buffer)
अणु
	काष्ठा hw_consumer_buffer *hw_buf =
		iio_buffer_to_hw_consumer_buffer(buffer);
	kमुक्त(hw_buf);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_access_funcs iio_hw_buf_access = अणु
	.release = &iio_hw_buf_release,
	.modes = INDIO_BUFFER_HARDWARE,
पूर्ण;

अटल काष्ठा hw_consumer_buffer *iio_hw_consumer_get_buffer(
	काष्ठा iio_hw_consumer *hwc, काष्ठा iio_dev *indio_dev)
अणु
	माप_प्रकार mask_size = BITS_TO_LONGS(indio_dev->masklength) * माप(दीर्घ);
	काष्ठा hw_consumer_buffer *buf;

	list_क्रम_each_entry(buf, &hwc->buffers, head) अणु
		अगर (buf->indio_dev == indio_dev)
			वापस buf;
	पूर्ण

	buf = kzalloc(माप(*buf) + mask_size, GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	buf->buffer.access = &iio_hw_buf_access;
	buf->indio_dev = indio_dev;
	buf->buffer.scan_mask = buf->scan_mask;

	iio_buffer_init(&buf->buffer);
	list_add_tail(&buf->head, &hwc->buffers);

	वापस buf;
पूर्ण

/**
 * iio_hw_consumer_alloc() - Allocate IIO hardware consumer
 * @dev: Poपूर्णांकer to consumer device.
 *
 * Returns a valid iio_hw_consumer on success or a ERR_PTR() on failure.
 */
काष्ठा iio_hw_consumer *iio_hw_consumer_alloc(काष्ठा device *dev)
अणु
	काष्ठा hw_consumer_buffer *buf;
	काष्ठा iio_hw_consumer *hwc;
	काष्ठा iio_channel *chan;
	पूर्णांक ret;

	hwc = kzalloc(माप(*hwc), GFP_KERNEL);
	अगर (!hwc)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&hwc->buffers);

	hwc->channels = iio_channel_get_all(dev);
	अगर (IS_ERR(hwc->channels)) अणु
		ret = PTR_ERR(hwc->channels);
		जाओ err_मुक्त_hwc;
	पूर्ण

	chan = &hwc->channels[0];
	जबतक (chan->indio_dev) अणु
		buf = iio_hw_consumer_get_buffer(hwc, chan->indio_dev);
		अगर (!buf) अणु
			ret = -ENOMEM;
			जाओ err_put_buffers;
		पूर्ण
		set_bit(chan->channel->scan_index, buf->buffer.scan_mask);
		chan++;
	पूर्ण

	वापस hwc;

err_put_buffers:
	list_क्रम_each_entry(buf, &hwc->buffers, head)
		iio_buffer_put(&buf->buffer);
	iio_channel_release_all(hwc->channels);
err_मुक्त_hwc:
	kमुक्त(hwc);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(iio_hw_consumer_alloc);

/**
 * iio_hw_consumer_मुक्त() - Free IIO hardware consumer
 * @hwc: hw consumer to मुक्त.
 */
व्योम iio_hw_consumer_मुक्त(काष्ठा iio_hw_consumer *hwc)
अणु
	काष्ठा hw_consumer_buffer *buf, *n;

	iio_channel_release_all(hwc->channels);
	list_क्रम_each_entry_safe(buf, n, &hwc->buffers, head)
		iio_buffer_put(&buf->buffer);
	kमुक्त(hwc);
पूर्ण
EXPORT_SYMBOL_GPL(iio_hw_consumer_मुक्त);

अटल व्योम devm_iio_hw_consumer_release(काष्ठा device *dev, व्योम *res)
अणु
	iio_hw_consumer_मुक्त(*(काष्ठा iio_hw_consumer **)res);
पूर्ण

/**
 * devm_iio_hw_consumer_alloc - Resource-managed iio_hw_consumer_alloc()
 * @dev: Poपूर्णांकer to consumer device.
 *
 * Managed iio_hw_consumer_alloc. iio_hw_consumer allocated with this function
 * is स्वतःmatically मुक्तd on driver detach.
 *
 * वापसs poपूर्णांकer to allocated iio_hw_consumer on success, शून्य on failure.
 */
काष्ठा iio_hw_consumer *devm_iio_hw_consumer_alloc(काष्ठा device *dev)
अणु
	काष्ठा iio_hw_consumer **ptr, *iio_hwc;

	ptr = devres_alloc(devm_iio_hw_consumer_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	iio_hwc = iio_hw_consumer_alloc(dev);
	अगर (IS_ERR(iio_hwc)) अणु
		devres_मुक्त(ptr);
	पूर्ण अन्यथा अणु
		*ptr = iio_hwc;
		devres_add(dev, ptr);
	पूर्ण

	वापस iio_hwc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_iio_hw_consumer_alloc);

/**
 * iio_hw_consumer_enable() - Enable IIO hardware consumer
 * @hwc: iio_hw_consumer to enable.
 *
 * Returns 0 on success.
 */
पूर्णांक iio_hw_consumer_enable(काष्ठा iio_hw_consumer *hwc)
अणु
	काष्ठा hw_consumer_buffer *buf;
	पूर्णांक ret;

	list_क्रम_each_entry(buf, &hwc->buffers, head) अणु
		ret = iio_update_buffers(buf->indio_dev, &buf->buffer, शून्य);
		अगर (ret)
			जाओ err_disable_buffers;
	पूर्ण

	वापस 0;

err_disable_buffers:
	list_क्रम_each_entry_जारी_reverse(buf, &hwc->buffers, head)
		iio_update_buffers(buf->indio_dev, शून्य, &buf->buffer);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_hw_consumer_enable);

/**
 * iio_hw_consumer_disable() - Disable IIO hardware consumer
 * @hwc: iio_hw_consumer to disable.
 */
व्योम iio_hw_consumer_disable(काष्ठा iio_hw_consumer *hwc)
अणु
	काष्ठा hw_consumer_buffer *buf;

	list_क्रम_each_entry(buf, &hwc->buffers, head)
		iio_update_buffers(buf->indio_dev, शून्य, &buf->buffer);
पूर्ण
EXPORT_SYMBOL_GPL(iio_hw_consumer_disable);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Hardware consumer buffer the IIO framework");
MODULE_LICENSE("GPL v2");
