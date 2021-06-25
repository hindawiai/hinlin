<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics sensors buffer library driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/common/st_sensors.h>


अटल पूर्णांक st_sensors_get_buffer_element(काष्ठा iio_dev *indio_dev, u8 *buf)
अणु
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);
	अचिन्हित पूर्णांक num_data_channels = sdata->num_data_channels;
	पूर्णांक i;

	क्रम_each_set_bit(i, indio_dev->active_scan_mask, num_data_channels) अणु
		स्थिर काष्ठा iio_chan_spec *channel = &indio_dev->channels[i];
		अचिन्हित पूर्णांक bytes_to_पढ़ो =
			DIV_ROUND_UP(channel->scan_type.realbits +
				     channel->scan_type.shअगरt, 8);
		अचिन्हित पूर्णांक storage_bytes =
			channel->scan_type.storagebits >> 3;

		buf = PTR_ALIGN(buf, storage_bytes);
		अगर (regmap_bulk_पढ़ो(sdata->regmap, channel->address,
				     buf, bytes_to_पढ़ो) < 0)
			वापस -EIO;

		/* Advance the buffer poपूर्णांकer */
		buf += storage_bytes;
	पूर्ण

	वापस 0;
पूर्ण

irqवापस_t st_sensors_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	पूर्णांक len;
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);
	s64 बारtamp;

	/*
	 * If we करो बारtamping here, करो it beक्रमe पढ़ोing the values, because
	 * once we've पढ़ो the values, new पूर्णांकerrupts can occur (when using
	 * the hardware trigger) and the hw_बारtamp may get updated.
	 * By storing it in a local variable first, we are safe.
	 */
	अगर (iio_trigger_using_own(indio_dev))
		बारtamp = sdata->hw_बारtamp;
	अन्यथा
		बारtamp = iio_get_समय_ns(indio_dev);

	len = st_sensors_get_buffer_element(indio_dev, sdata->buffer_data);
	अगर (len < 0)
		जाओ st_sensors_get_buffer_element_error;

	iio_push_to_buffers_with_बारtamp(indio_dev, sdata->buffer_data,
					   बारtamp);

st_sensors_get_buffer_element_error:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL(st_sensors_trigger_handler);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics ST-sensors buffer");
MODULE_LICENSE("GPL v2");
