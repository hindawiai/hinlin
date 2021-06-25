<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Common library क्रम ADIS16XXX devices
 *
 * Copyright 2012 Analog Devices Inc.
 *   Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/imu/adis.h>

अटल पूर्णांक adis_update_scan_mode_burst(काष्ठा iio_dev *indio_dev,
	स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा adis *adis = iio_device_get_drvdata(indio_dev);
	अचिन्हित पूर्णांक burst_length, burst_max_length;
	u8 *tx;

	burst_length = adis->data->burst_len + adis->burst_extra_len;

	अगर (adis->data->burst_max_len)
		burst_max_length = adis->data->burst_max_len;
	अन्यथा
		burst_max_length = burst_length;

	adis->xfer = kसुस्मृति(2, माप(*adis->xfer), GFP_KERNEL);
	अगर (!adis->xfer)
		वापस -ENOMEM;

	adis->buffer = kzalloc(burst_max_length + माप(u16), GFP_KERNEL);
	अगर (!adis->buffer) अणु
		kमुक्त(adis->xfer);
		adis->xfer = शून्य;
		वापस -ENOMEM;
	पूर्ण

	tx = adis->buffer + burst_max_length;
	tx[0] = ADIS_READ_REG(adis->data->burst_reg_cmd);
	tx[1] = 0;

	adis->xfer[0].tx_buf = tx;
	adis->xfer[0].bits_per_word = 8;
	adis->xfer[0].len = 2;
	adis->xfer[1].rx_buf = adis->buffer;
	adis->xfer[1].bits_per_word = 8;
	adis->xfer[1].len = burst_length;

	spi_message_init(&adis->msg);
	spi_message_add_tail(&adis->xfer[0], &adis->msg);
	spi_message_add_tail(&adis->xfer[1], &adis->msg);

	वापस 0;
पूर्ण

पूर्णांक adis_update_scan_mode(काष्ठा iio_dev *indio_dev,
	स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा adis *adis = iio_device_get_drvdata(indio_dev);
	स्थिर काष्ठा iio_chan_spec *chan;
	अचिन्हित पूर्णांक scan_count;
	अचिन्हित पूर्णांक i, j;
	__be16 *tx, *rx;

	kमुक्त(adis->xfer);
	kमुक्त(adis->buffer);

	अगर (adis->data->burst_len)
		वापस adis_update_scan_mode_burst(indio_dev, scan_mask);

	scan_count = indio_dev->scan_bytes / 2;

	adis->xfer = kसुस्मृति(scan_count + 1, माप(*adis->xfer), GFP_KERNEL);
	अगर (!adis->xfer)
		वापस -ENOMEM;

	adis->buffer = kसुस्मृति(indio_dev->scan_bytes, 2, GFP_KERNEL);
	अगर (!adis->buffer) अणु
		kमुक्त(adis->xfer);
		adis->xfer = शून्य;
		वापस -ENOMEM;
	पूर्ण

	rx = adis->buffer;
	tx = rx + scan_count;

	spi_message_init(&adis->msg);

	क्रम (j = 0; j <= scan_count; j++) अणु
		adis->xfer[j].bits_per_word = 8;
		अगर (j != scan_count)
			adis->xfer[j].cs_change = 1;
		adis->xfer[j].len = 2;
		adis->xfer[j].delay.value = adis->data->पढ़ो_delay;
		adis->xfer[j].delay.unit = SPI_DELAY_UNIT_USECS;
		अगर (j < scan_count)
			adis->xfer[j].tx_buf = &tx[j];
		अगर (j >= 1)
			adis->xfer[j].rx_buf = &rx[j - 1];
		spi_message_add_tail(&adis->xfer[j], &adis->msg);
	पूर्ण

	chan = indio_dev->channels;
	क्रम (i = 0; i < indio_dev->num_channels; i++, chan++) अणु
		अगर (!test_bit(chan->scan_index, scan_mask))
			जारी;
		अगर (chan->scan_type.storagebits == 32)
			*tx++ = cpu_to_be16((chan->address + 2) << 8);
		*tx++ = cpu_to_be16(chan->address << 8);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adis_update_scan_mode);

अटल irqवापस_t adis_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा adis *adis = iio_device_get_drvdata(indio_dev);
	पूर्णांक ret;

	अगर (!adis->buffer)
		वापस -ENOMEM;

	अगर (adis->data->has_paging) अणु
		mutex_lock(&adis->state_lock);
		अगर (adis->current_page != 0) अणु
			adis->tx[0] = ADIS_WRITE_REG(ADIS_REG_PAGE_ID);
			adis->tx[1] = 0;
			spi_ग_लिखो(adis->spi, adis->tx, 2);
		पूर्ण
	पूर्ण

	ret = spi_sync(adis->spi, &adis->msg);
	अगर (ret)
		dev_err(&adis->spi->dev, "Failed to read data: %d", ret);


	अगर (adis->data->has_paging) अणु
		adis->current_page = 0;
		mutex_unlock(&adis->state_lock);
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, adis->buffer,
		pf->बारtamp);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम adis_buffer_cleanup(व्योम *arg)
अणु
	काष्ठा adis *adis = arg;

	kमुक्त(adis->buffer);
	kमुक्त(adis->xfer);
पूर्ण

/**
 * devm_adis_setup_buffer_and_trigger() - Sets up buffer and trigger क्रम
 *					  the managed adis device
 * @adis: The adis device
 * @indio_dev: The IIO device
 * @trigger_handler: Optional trigger handler, may be शून्य.
 *
 * Returns 0 on success, a negative error code otherwise.
 *
 * This function sets up the buffer and trigger क्रम a adis devices.  If
 * 'trigger_handler' is शून्य the शेष trigger handler will be used. The
 * शेष trigger handler will simply पढ़ो the रेजिस्टरs asचिन्हित to the
 * currently active channels.
 */
पूर्णांक
devm_adis_setup_buffer_and_trigger(काष्ठा adis *adis, काष्ठा iio_dev *indio_dev,
				   irq_handler_t trigger_handler)
अणु
	पूर्णांक ret;

	अगर (!trigger_handler)
		trigger_handler = adis_trigger_handler;

	ret = devm_iio_triggered_buffer_setup(&adis->spi->dev, indio_dev,
					      &iio_pollfunc_store_समय,
					      trigger_handler, शून्य);
	अगर (ret)
		वापस ret;

	अगर (adis->spi->irq) अणु
		ret = devm_adis_probe_trigger(adis, indio_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस devm_add_action_or_reset(&adis->spi->dev, adis_buffer_cleanup,
					adis);
पूर्ण
EXPORT_SYMBOL_GPL(devm_adis_setup_buffer_and_trigger);

