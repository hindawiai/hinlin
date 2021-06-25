<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support code क्रम Analog Devices Sigma-Delta ADCs
 *
 * Copyright 2012 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/adc/ad_sigma_delta.h>

#समावेश <यंत्र/unaligned.h>


#घोषणा AD_SD_COMM_CHAN_MASK	0x3

#घोषणा AD_SD_REG_COMM		0x00
#घोषणा AD_SD_REG_DATA		0x03

/**
 * ad_sd_set_comm() - Set communications रेजिस्टर
 *
 * @sigma_delta: The sigma delta device
 * @comm: New value क्रम the communications रेजिस्टर
 */
व्योम ad_sd_set_comm(काष्ठा ad_sigma_delta *sigma_delta, uपूर्णांक8_t comm)
अणु
	/* Some variants use the lower two bits of the communications रेजिस्टर
	 * to select the channel */
	sigma_delta->comm = comm & AD_SD_COMM_CHAN_MASK;
पूर्ण
EXPORT_SYMBOL_GPL(ad_sd_set_comm);

/**
 * ad_sd_ग_लिखो_reg() - Write a रेजिस्टर
 *
 * @sigma_delta: The sigma delta device
 * @reg: Address of the रेजिस्टर
 * @size: Size of the रेजिस्टर (0-3)
 * @val: Value to ग_लिखो to the रेजिस्टर
 *
 * Returns 0 on success, an error code otherwise.
 **/
पूर्णांक ad_sd_ग_लिखो_reg(काष्ठा ad_sigma_delta *sigma_delta, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक val)
अणु
	uपूर्णांक8_t *data = sigma_delta->tx_buf;
	काष्ठा spi_transfer t = अणु
		.tx_buf		= data,
		.len		= size + 1,
		.cs_change	= sigma_delta->keep_cs_निश्चितed,
	पूर्ण;
	काष्ठा spi_message m;
	पूर्णांक ret;

	data[0] = (reg << sigma_delta->info->addr_shअगरt) | sigma_delta->comm;

	चयन (size) अणु
	हाल 3:
		put_unaligned_be24(val, &data[1]);
		अवरोध;
	हाल 2:
		put_unaligned_be16(val, &data[1]);
		अवरोध;
	हाल 1:
		data[1] = val;
		अवरोध;
	हाल 0:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);

	अगर (sigma_delta->bus_locked)
		ret = spi_sync_locked(sigma_delta->spi, &m);
	अन्यथा
		ret = spi_sync(sigma_delta->spi, &m);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ad_sd_ग_लिखो_reg);

अटल पूर्णांक ad_sd_पढ़ो_reg_raw(काष्ठा ad_sigma_delta *sigma_delta,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक size, uपूर्णांक8_t *val)
अणु
	uपूर्णांक8_t *data = sigma_delta->tx_buf;
	पूर्णांक ret;
	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = data,
			.len = 1,
		पूर्ण, अणु
			.rx_buf = val,
			.len = size,
			.cs_change = sigma_delta->bus_locked,
		पूर्ण,
	पूर्ण;
	काष्ठा spi_message m;

	spi_message_init(&m);

	अगर (sigma_delta->info->has_रेजिस्टरs) अणु
		data[0] = reg << sigma_delta->info->addr_shअगरt;
		data[0] |= sigma_delta->info->पढ़ो_mask;
		data[0] |= sigma_delta->comm;
		spi_message_add_tail(&t[0], &m);
	पूर्ण
	spi_message_add_tail(&t[1], &m);

	अगर (sigma_delta->bus_locked)
		ret = spi_sync_locked(sigma_delta->spi, &m);
	अन्यथा
		ret = spi_sync(sigma_delta->spi, &m);

	वापस ret;
पूर्ण

/**
 * ad_sd_पढ़ो_reg() - Read a रेजिस्टर
 *
 * @sigma_delta: The sigma delta device
 * @reg: Address of the रेजिस्टर
 * @size: Size of the रेजिस्टर (1-4)
 * @val: Read value
 *
 * Returns 0 on success, an error code otherwise.
 **/
पूर्णांक ad_sd_पढ़ो_reg(काष्ठा ad_sigma_delta *sigma_delta,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;

	ret = ad_sd_पढ़ो_reg_raw(sigma_delta, reg, size, sigma_delta->rx_buf);
	अगर (ret < 0)
		जाओ out;

	चयन (size) अणु
	हाल 4:
		*val = get_unaligned_be32(sigma_delta->rx_buf);
		अवरोध;
	हाल 3:
		*val = get_unaligned_be24(sigma_delta->rx_buf);
		अवरोध;
	हाल 2:
		*val = get_unaligned_be16(sigma_delta->rx_buf);
		अवरोध;
	हाल 1:
		*val = sigma_delta->rx_buf[0];
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ad_sd_पढ़ो_reg);

/**
 * ad_sd_reset() - Reset the serial पूर्णांकerface
 *
 * @sigma_delta: The sigma delta device
 * @reset_length: Number of SCLKs with DIN = 1
 *
 * Returns 0 on success, an error code otherwise.
 **/
पूर्णांक ad_sd_reset(काष्ठा ad_sigma_delta *sigma_delta,
	अचिन्हित पूर्णांक reset_length)
अणु
	uपूर्णांक8_t *buf;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret;

	size = DIV_ROUND_UP(reset_length, 8);
	buf = kसुस्मृति(size, माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	स_रखो(buf, 0xff, size);
	ret = spi_ग_लिखो(sigma_delta->spi, buf, size);
	kमुक्त(buf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ad_sd_reset);

पूर्णांक ad_sd_calibrate(काष्ठा ad_sigma_delta *sigma_delta,
	अचिन्हित पूर्णांक mode, अचिन्हित पूर्णांक channel)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;

	ret = ad_sigma_delta_set_channel(sigma_delta, channel);
	अगर (ret)
		वापस ret;

	spi_bus_lock(sigma_delta->spi->master);
	sigma_delta->bus_locked = true;
	sigma_delta->keep_cs_निश्चितed = true;
	reinit_completion(&sigma_delta->completion);

	ret = ad_sigma_delta_set_mode(sigma_delta, mode);
	अगर (ret < 0)
		जाओ out;

	sigma_delta->irq_dis = false;
	enable_irq(sigma_delta->spi->irq);
	समयout = रुको_क्रम_completion_समयout(&sigma_delta->completion, 2 * HZ);
	अगर (समयout == 0) अणु
		sigma_delta->irq_dis = true;
		disable_irq_nosync(sigma_delta->spi->irq);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण
out:
	sigma_delta->keep_cs_निश्चितed = false;
	ad_sigma_delta_set_mode(sigma_delta, AD_SD_MODE_IDLE);
	sigma_delta->bus_locked = false;
	spi_bus_unlock(sigma_delta->spi->master);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ad_sd_calibrate);

/**
 * ad_sd_calibrate_all() - Perक्रमms channel calibration
 * @sigma_delta: The sigma delta device
 * @cb: Array of channels and calibration type to perक्रमm
 * @n: Number of items in cb
 *
 * Returns 0 on success, an error code otherwise.
 **/
पूर्णांक ad_sd_calibrate_all(काष्ठा ad_sigma_delta *sigma_delta,
	स्थिर काष्ठा ad_sd_calib_data *cb, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < n; i++) अणु
		ret = ad_sd_calibrate(sigma_delta, cb[i].mode, cb[i].channel);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ad_sd_calibrate_all);

/**
 * ad_sigma_delta_single_conversion() - Perक्रमms a single data conversion
 * @indio_dev: The IIO device
 * @chan: The conversion is करोne क्रम this channel
 * @val: Poपूर्णांकer to the location where to store the पढ़ो value
 *
 * Returns: 0 on success, an error value otherwise.
 */
पूर्णांक ad_sigma_delta_single_conversion(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val)
अणु
	काष्ठा ad_sigma_delta *sigma_delta = iio_device_get_drvdata(indio_dev);
	अचिन्हित पूर्णांक sample, raw_sample;
	अचिन्हित पूर्णांक data_reg;
	पूर्णांक ret = 0;

	अगर (iio_buffer_enabled(indio_dev))
		वापस -EBUSY;

	mutex_lock(&indio_dev->mlock);
	ad_sigma_delta_set_channel(sigma_delta, chan->address);

	spi_bus_lock(sigma_delta->spi->master);
	sigma_delta->bus_locked = true;
	sigma_delta->keep_cs_निश्चितed = true;
	reinit_completion(&sigma_delta->completion);

	ad_sigma_delta_set_mode(sigma_delta, AD_SD_MODE_SINGLE);

	sigma_delta->irq_dis = false;
	enable_irq(sigma_delta->spi->irq);
	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&sigma_delta->completion, HZ);

	अगर (ret == 0)
		ret = -EIO;
	अगर (ret < 0)
		जाओ out;

	अगर (sigma_delta->info->data_reg != 0)
		data_reg = sigma_delta->info->data_reg;
	अन्यथा
		data_reg = AD_SD_REG_DATA;

	ret = ad_sd_पढ़ो_reg(sigma_delta, data_reg,
		DIV_ROUND_UP(chan->scan_type.realbits + chan->scan_type.shअगरt, 8),
		&raw_sample);

out:
	अगर (!sigma_delta->irq_dis) अणु
		disable_irq_nosync(sigma_delta->spi->irq);
		sigma_delta->irq_dis = true;
	पूर्ण

	sigma_delta->keep_cs_निश्चितed = false;
	ad_sigma_delta_set_mode(sigma_delta, AD_SD_MODE_IDLE);
	sigma_delta->bus_locked = false;
	spi_bus_unlock(sigma_delta->spi->master);
	mutex_unlock(&indio_dev->mlock);

	अगर (ret)
		वापस ret;

	sample = raw_sample >> chan->scan_type.shअगरt;
	sample &= (1 << chan->scan_type.realbits) - 1;
	*val = sample;

	ret = ad_sigma_delta_postprocess_sample(sigma_delta, raw_sample);
	अगर (ret)
		वापस ret;

	वापस IIO_VAL_INT;
पूर्ण
EXPORT_SYMBOL_GPL(ad_sigma_delta_single_conversion);

अटल पूर्णांक ad_sd_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad_sigma_delta *sigma_delta = iio_device_get_drvdata(indio_dev);
	अचिन्हित पूर्णांक channel;
	पूर्णांक ret;

	channel = find_first_bit(indio_dev->active_scan_mask,
				 indio_dev->masklength);
	ret = ad_sigma_delta_set_channel(sigma_delta,
		indio_dev->channels[channel].address);
	अगर (ret)
		वापस ret;

	spi_bus_lock(sigma_delta->spi->master);
	sigma_delta->bus_locked = true;
	sigma_delta->keep_cs_निश्चितed = true;

	ret = ad_sigma_delta_set_mode(sigma_delta, AD_SD_MODE_CONTINUOUS);
	अगर (ret)
		जाओ err_unlock;

	sigma_delta->irq_dis = false;
	enable_irq(sigma_delta->spi->irq);

	वापस 0;

err_unlock:
	spi_bus_unlock(sigma_delta->spi->master);

	वापस ret;
पूर्ण

अटल पूर्णांक ad_sd_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad_sigma_delta *sigma_delta = iio_device_get_drvdata(indio_dev);

	reinit_completion(&sigma_delta->completion);
	रुको_क्रम_completion_समयout(&sigma_delta->completion, HZ);

	अगर (!sigma_delta->irq_dis) अणु
		disable_irq_nosync(sigma_delta->spi->irq);
		sigma_delta->irq_dis = true;
	पूर्ण

	sigma_delta->keep_cs_निश्चितed = false;
	ad_sigma_delta_set_mode(sigma_delta, AD_SD_MODE_IDLE);

	sigma_delta->bus_locked = false;
	वापस spi_bus_unlock(sigma_delta->spi->master);
पूर्ण

अटल irqवापस_t ad_sd_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ad_sigma_delta *sigma_delta = iio_device_get_drvdata(indio_dev);
	uपूर्णांक8_t *data = sigma_delta->rx_buf;
	अचिन्हित पूर्णांक reg_size;
	अचिन्हित पूर्णांक data_reg;

	reg_size = indio_dev->channels[0].scan_type.realbits +
			indio_dev->channels[0].scan_type.shअगरt;
	reg_size = DIV_ROUND_UP(reg_size, 8);

	अगर (sigma_delta->info->data_reg != 0)
		data_reg = sigma_delta->info->data_reg;
	अन्यथा
		data_reg = AD_SD_REG_DATA;

	चयन (reg_size) अणु
	हाल 4:
	हाल 2:
	हाल 1:
		ad_sd_पढ़ो_reg_raw(sigma_delta, data_reg, reg_size, &data[0]);
		अवरोध;
	हाल 3:
		/* We store 24 bit samples in a 32 bit word. Keep the upper
		 * byte set to zero. */
		ad_sd_पढ़ो_reg_raw(sigma_delta, data_reg, reg_size, &data[1]);
		अवरोध;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, data, pf->बारtamp);

	iio_trigger_notअगरy_करोne(indio_dev->trig);
	sigma_delta->irq_dis = false;
	enable_irq(sigma_delta->spi->irq);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops ad_sd_buffer_setup_ops = अणु
	.postenable = &ad_sd_buffer_postenable,
	.postdisable = &ad_sd_buffer_postdisable,
	.validate_scan_mask = &iio_validate_scan_mask_onehot,
पूर्ण;

अटल irqवापस_t ad_sd_data_rdy_trig_poll(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा ad_sigma_delta *sigma_delta = निजी;

	complete(&sigma_delta->completion);
	disable_irq_nosync(irq);
	sigma_delta->irq_dis = true;
	iio_trigger_poll(sigma_delta->trig);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ad_sd_validate_trigger() - validate_trigger callback क्रम ad_sigma_delta devices
 * @indio_dev: The IIO device
 * @trig: The new trigger
 *
 * Returns: 0 अगर the 'trig' matches the trigger रेजिस्टरed by the ad_sigma_delta
 * device, -EINVAL otherwise.
 */
पूर्णांक ad_sd_validate_trigger(काष्ठा iio_dev *indio_dev, काष्ठा iio_trigger *trig)
अणु
	काष्ठा ad_sigma_delta *sigma_delta = iio_device_get_drvdata(indio_dev);

	अगर (sigma_delta->trig != trig)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ad_sd_validate_trigger);

अटल स्थिर काष्ठा iio_trigger_ops ad_sd_trigger_ops = अणु
पूर्ण;

अटल पूर्णांक ad_sd_probe_trigger(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad_sigma_delta *sigma_delta = iio_device_get_drvdata(indio_dev);
	पूर्णांक ret;

	sigma_delta->trig = iio_trigger_alloc(&sigma_delta->spi->dev,
					      "%s-dev%d", indio_dev->name,
					      indio_dev->id);
	अगर (sigma_delta->trig == शून्य) अणु
		ret = -ENOMEM;
		जाओ error_ret;
	पूर्ण
	sigma_delta->trig->ops = &ad_sd_trigger_ops;
	init_completion(&sigma_delta->completion);

	sigma_delta->irq_dis = true;
	ret = request_irq(sigma_delta->spi->irq,
			  ad_sd_data_rdy_trig_poll,
			  sigma_delta->info->irq_flags | IRQF_NO_AUTOEN,
			  indio_dev->name,
			  sigma_delta);
	अगर (ret)
		जाओ error_मुक्त_trig;

	iio_trigger_set_drvdata(sigma_delta->trig, sigma_delta);

	ret = iio_trigger_रेजिस्टर(sigma_delta->trig);
	अगर (ret)
		जाओ error_मुक्त_irq;

	/* select शेष trigger */
	indio_dev->trig = iio_trigger_get(sigma_delta->trig);

	वापस 0;

error_मुक्त_irq:
	मुक्त_irq(sigma_delta->spi->irq, sigma_delta);
error_मुक्त_trig:
	iio_trigger_मुक्त(sigma_delta->trig);
error_ret:
	वापस ret;
पूर्ण

अटल व्योम ad_sd_हटाओ_trigger(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad_sigma_delta *sigma_delta = iio_device_get_drvdata(indio_dev);

	iio_trigger_unरेजिस्टर(sigma_delta->trig);
	मुक्त_irq(sigma_delta->spi->irq, sigma_delta);
	iio_trigger_मुक्त(sigma_delta->trig);
पूर्ण

/**
 * ad_sd_setup_buffer_and_trigger() -
 * @indio_dev: The IIO device
 */
पूर्णांक ad_sd_setup_buffer_and_trigger(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_समय,
			&ad_sd_trigger_handler, &ad_sd_buffer_setup_ops);
	अगर (ret)
		वापस ret;

	ret = ad_sd_probe_trigger(indio_dev);
	अगर (ret) अणु
		iio_triggered_buffer_cleanup(indio_dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ad_sd_setup_buffer_and_trigger);

/**
 * ad_sd_cleanup_buffer_and_trigger() -
 * @indio_dev: The IIO device
 */
व्योम ad_sd_cleanup_buffer_and_trigger(काष्ठा iio_dev *indio_dev)
अणु
	ad_sd_हटाओ_trigger(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
पूर्ण
EXPORT_SYMBOL_GPL(ad_sd_cleanup_buffer_and_trigger);

/**
 * ad_sd_init() - Initializes a ad_sigma_delta काष्ठा
 * @sigma_delta: The ad_sigma_delta device
 * @indio_dev: The IIO device which the Sigma Delta device is used क्रम
 * @spi: The SPI device क्रम the ad_sigma_delta device
 * @info: Device specअगरic callbacks and options
 *
 * This function needs to be called beक्रमe any other operations are perक्रमmed on
 * the ad_sigma_delta काष्ठा.
 */
पूर्णांक ad_sd_init(काष्ठा ad_sigma_delta *sigma_delta, काष्ठा iio_dev *indio_dev,
	काष्ठा spi_device *spi, स्थिर काष्ठा ad_sigma_delta_info *info)
अणु
	sigma_delta->spi = spi;
	sigma_delta->info = info;
	iio_device_set_drvdata(indio_dev, sigma_delta);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ad_sd_init);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices Sigma-Delta ADCs");
MODULE_LICENSE("GPL v2");
