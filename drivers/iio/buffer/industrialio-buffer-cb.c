<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* The industrial I/O callback buffer
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer_impl.h>
#समावेश <linux/iio/consumer.h>

काष्ठा iio_cb_buffer अणु
	काष्ठा iio_buffer buffer;
	पूर्णांक (*cb)(स्थिर व्योम *data, व्योम *निजी);
	व्योम *निजी;
	काष्ठा iio_channel *channels;
	काष्ठा iio_dev *indio_dev;
पूर्ण;

अटल काष्ठा iio_cb_buffer *buffer_to_cb_buffer(काष्ठा iio_buffer *buffer)
अणु
	वापस container_of(buffer, काष्ठा iio_cb_buffer, buffer);
पूर्ण

अटल पूर्णांक iio_buffer_cb_store_to(काष्ठा iio_buffer *buffer, स्थिर व्योम *data)
अणु
	काष्ठा iio_cb_buffer *cb_buff = buffer_to_cb_buffer(buffer);
	वापस cb_buff->cb(data, cb_buff->निजी);
पूर्ण

अटल व्योम iio_buffer_cb_release(काष्ठा iio_buffer *buffer)
अणु
	काष्ठा iio_cb_buffer *cb_buff = buffer_to_cb_buffer(buffer);

	biपंचांगap_मुक्त(cb_buff->buffer.scan_mask);
	kमुक्त(cb_buff);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_access_funcs iio_cb_access = अणु
	.store_to = &iio_buffer_cb_store_to,
	.release = &iio_buffer_cb_release,

	.modes = INDIO_BUFFER_SOFTWARE | INDIO_BUFFER_TRIGGERED,
पूर्ण;

काष्ठा iio_cb_buffer *iio_channel_get_all_cb(काष्ठा device *dev,
					     पूर्णांक (*cb)(स्थिर व्योम *data,
						       व्योम *निजी),
					     व्योम *निजी)
अणु
	पूर्णांक ret;
	काष्ठा iio_cb_buffer *cb_buff;
	काष्ठा iio_channel *chan;

	अगर (!cb) अणु
		dev_err(dev, "Invalid arguments: A callback must be provided!\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	cb_buff = kzalloc(माप(*cb_buff), GFP_KERNEL);
	अगर (cb_buff == शून्य)
		वापस ERR_PTR(-ENOMEM);

	iio_buffer_init(&cb_buff->buffer);

	cb_buff->निजी = निजी;
	cb_buff->cb = cb;
	cb_buff->buffer.access = &iio_cb_access;
	INIT_LIST_HEAD(&cb_buff->buffer.demux_list);

	cb_buff->channels = iio_channel_get_all(dev);
	अगर (IS_ERR(cb_buff->channels)) अणु
		ret = PTR_ERR(cb_buff->channels);
		जाओ error_मुक्त_cb_buff;
	पूर्ण

	cb_buff->indio_dev = cb_buff->channels[0].indio_dev;
	cb_buff->buffer.scan_mask = biपंचांगap_zalloc(cb_buff->indio_dev->masklength,
						  GFP_KERNEL);
	अगर (cb_buff->buffer.scan_mask == शून्य) अणु
		ret = -ENOMEM;
		जाओ error_release_channels;
	पूर्ण
	chan = &cb_buff->channels[0];
	जबतक (chan->indio_dev) अणु
		अगर (chan->indio_dev != cb_buff->indio_dev) अणु
			ret = -EINVAL;
			जाओ error_मुक्त_scan_mask;
		पूर्ण
		set_bit(chan->channel->scan_index,
			cb_buff->buffer.scan_mask);
		chan++;
	पूर्ण

	वापस cb_buff;

error_मुक्त_scan_mask:
	biपंचांगap_मुक्त(cb_buff->buffer.scan_mask);
error_release_channels:
	iio_channel_release_all(cb_buff->channels);
error_मुक्त_cb_buff:
	kमुक्त(cb_buff);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(iio_channel_get_all_cb);

पूर्णांक iio_channel_cb_set_buffer_watermark(काष्ठा iio_cb_buffer *cb_buff,
					माप_प्रकार watermark)
अणु
	अगर (!watermark)
		वापस -EINVAL;
	cb_buff->buffer.watermark = watermark;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iio_channel_cb_set_buffer_watermark);

पूर्णांक iio_channel_start_all_cb(काष्ठा iio_cb_buffer *cb_buff)
अणु
	वापस iio_update_buffers(cb_buff->indio_dev, &cb_buff->buffer,
				  शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(iio_channel_start_all_cb);

व्योम iio_channel_stop_all_cb(काष्ठा iio_cb_buffer *cb_buff)
अणु
	iio_update_buffers(cb_buff->indio_dev, शून्य, &cb_buff->buffer);
पूर्ण
EXPORT_SYMBOL_GPL(iio_channel_stop_all_cb);

व्योम iio_channel_release_all_cb(काष्ठा iio_cb_buffer *cb_buff)
अणु
	iio_channel_release_all(cb_buff->channels);
	iio_buffer_put(&cb_buff->buffer);
पूर्ण
EXPORT_SYMBOL_GPL(iio_channel_release_all_cb);

काष्ठा iio_channel
*iio_channel_cb_get_channels(स्थिर काष्ठा iio_cb_buffer *cb_buffer)
अणु
	वापस cb_buffer->channels;
पूर्ण
EXPORT_SYMBOL_GPL(iio_channel_cb_get_channels);

काष्ठा iio_dev
*iio_channel_cb_get_iio_dev(स्थिर काष्ठा iio_cb_buffer *cb_buffer)
अणु
	वापस cb_buffer->indio_dev;
पूर्ण
EXPORT_SYMBOL_GPL(iio_channel_cb_get_iio_dev);

MODULE_AUTHOR("Jonathan Cameron <jic23@kernel.org>");
MODULE_DESCRIPTION("Industrial I/O callback buffer");
MODULE_LICENSE("GPL");
