<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Analog Devices AD7768-1 SPI ADC driver
 *
 * Copyright 2017 Analog Devices Inc.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

/* AD7768 रेजिस्टरs definition */
#घोषणा AD7768_REG_CHIP_TYPE		0x3
#घोषणा AD7768_REG_PROD_ID_L		0x4
#घोषणा AD7768_REG_PROD_ID_H		0x5
#घोषणा AD7768_REG_CHIP_GRADE		0x6
#घोषणा AD7768_REG_SCRATCH_PAD		0x0A
#घोषणा AD7768_REG_VENDOR_L		0x0C
#घोषणा AD7768_REG_VENDOR_H		0x0D
#घोषणा AD7768_REG_INTERFACE_FORMAT	0x14
#घोषणा AD7768_REG_POWER_CLOCK		0x15
#घोषणा AD7768_REG_ANALOG		0x16
#घोषणा AD7768_REG_ANALOG2		0x17
#घोषणा AD7768_REG_CONVERSION		0x18
#घोषणा AD7768_REG_DIGITAL_FILTER	0x19
#घोषणा AD7768_REG_SINC3_DEC_RATE_MSB	0x1A
#घोषणा AD7768_REG_SINC3_DEC_RATE_LSB	0x1B
#घोषणा AD7768_REG_DUTY_CYCLE_RATIO	0x1C
#घोषणा AD7768_REG_SYNC_RESET		0x1D
#घोषणा AD7768_REG_GPIO_CONTROL		0x1E
#घोषणा AD7768_REG_GPIO_WRITE		0x1F
#घोषणा AD7768_REG_GPIO_READ		0x20
#घोषणा AD7768_REG_OFFSET_HI		0x21
#घोषणा AD7768_REG_OFFSET_MID		0x22
#घोषणा AD7768_REG_OFFSET_LO		0x23
#घोषणा AD7768_REG_GAIN_HI		0x24
#घोषणा AD7768_REG_GAIN_MID		0x25
#घोषणा AD7768_REG_GAIN_LO		0x26
#घोषणा AD7768_REG_SPI_DIAG_ENABLE	0x28
#घोषणा AD7768_REG_ADC_DIAG_ENABLE	0x29
#घोषणा AD7768_REG_DIG_DIAG_ENABLE	0x2A
#घोषणा AD7768_REG_ADC_DATA		0x2C
#घोषणा AD7768_REG_MASTER_STATUS	0x2D
#घोषणा AD7768_REG_SPI_DIAG_STATUS	0x2E
#घोषणा AD7768_REG_ADC_DIAG_STATUS	0x2F
#घोषणा AD7768_REG_DIG_DIAG_STATUS	0x30
#घोषणा AD7768_REG_MCLK_COUNTER		0x31

/* AD7768_REG_POWER_CLOCK */
#घोषणा AD7768_PWR_MCLK_DIV_MSK		GENMASK(5, 4)
#घोषणा AD7768_PWR_MCLK_DIV(x)		FIELD_PREP(AD7768_PWR_MCLK_DIV_MSK, x)
#घोषणा AD7768_PWR_PWRMODE_MSK		GENMASK(1, 0)
#घोषणा AD7768_PWR_PWRMODE(x)		FIELD_PREP(AD7768_PWR_PWRMODE_MSK, x)

/* AD7768_REG_DIGITAL_FILTER */
#घोषणा AD7768_DIG_FIL_FIL_MSK		GENMASK(6, 4)
#घोषणा AD7768_DIG_FIL_FIL(x)		FIELD_PREP(AD7768_DIG_FIL_FIL_MSK, x)
#घोषणा AD7768_DIG_FIL_DEC_MSK		GENMASK(2, 0)
#घोषणा AD7768_DIG_FIL_DEC_RATE(x)	FIELD_PREP(AD7768_DIG_FIL_DEC_MSK, x)

/* AD7768_REG_CONVERSION */
#घोषणा AD7768_CONV_MODE_MSK		GENMASK(2, 0)
#घोषणा AD7768_CONV_MODE(x)		FIELD_PREP(AD7768_CONV_MODE_MSK, x)

#घोषणा AD7768_RD_FLAG_MSK(x)		(BIT(6) | ((x) & 0x3F))
#घोषणा AD7768_WR_FLAG_MSK(x)		((x) & 0x3F)

क्रमागत ad7768_conv_mode अणु
	AD7768_CONTINUOUS,
	AD7768_ONE_SHOT,
	AD7768_SINGLE,
	AD7768_PERIODIC,
	AD7768_STANDBY
पूर्ण;

क्रमागत ad7768_pwrmode अणु
	AD7768_ECO_MODE = 0,
	AD7768_MED_MODE = 2,
	AD7768_FAST_MODE = 3
पूर्ण;

क्रमागत ad7768_mclk_भाग अणु
	AD7768_MCLK_DIV_16,
	AD7768_MCLK_DIV_8,
	AD7768_MCLK_DIV_4,
	AD7768_MCLK_DIV_2
पूर्ण;

क्रमागत ad7768_dec_rate अणु
	AD7768_DEC_RATE_32 = 0,
	AD7768_DEC_RATE_64 = 1,
	AD7768_DEC_RATE_128 = 2,
	AD7768_DEC_RATE_256 = 3,
	AD7768_DEC_RATE_512 = 4,
	AD7768_DEC_RATE_1024 = 5,
	AD7768_DEC_RATE_8 = 9,
	AD7768_DEC_RATE_16 = 10
पूर्ण;

काष्ठा ad7768_clk_configuration अणु
	क्रमागत ad7768_mclk_भाग mclk_भाग;
	क्रमागत ad7768_dec_rate dec_rate;
	अचिन्हित पूर्णांक clk_भाग;
	क्रमागत ad7768_pwrmode pwrmode;
पूर्ण;

अटल स्थिर काष्ठा ad7768_clk_configuration ad7768_clk_config[] = अणु
	अणु AD7768_MCLK_DIV_2, AD7768_DEC_RATE_8, 16,  AD7768_FAST_MODE पूर्ण,
	अणु AD7768_MCLK_DIV_2, AD7768_DEC_RATE_16, 32,  AD7768_FAST_MODE पूर्ण,
	अणु AD7768_MCLK_DIV_2, AD7768_DEC_RATE_32, 64, AD7768_FAST_MODE पूर्ण,
	अणु AD7768_MCLK_DIV_2, AD7768_DEC_RATE_64, 128, AD7768_FAST_MODE पूर्ण,
	अणु AD7768_MCLK_DIV_2, AD7768_DEC_RATE_128, 256, AD7768_FAST_MODE पूर्ण,
	अणु AD7768_MCLK_DIV_4, AD7768_DEC_RATE_128, 512, AD7768_MED_MODE पूर्ण,
	अणु AD7768_MCLK_DIV_4, AD7768_DEC_RATE_256, 1024, AD7768_MED_MODE पूर्ण,
	अणु AD7768_MCLK_DIV_4, AD7768_DEC_RATE_512, 2048, AD7768_MED_MODE पूर्ण,
	अणु AD7768_MCLK_DIV_4, AD7768_DEC_RATE_1024, 4096, AD7768_MED_MODE पूर्ण,
	अणु AD7768_MCLK_DIV_8, AD7768_DEC_RATE_1024, 8192, AD7768_MED_MODE पूर्ण,
	अणु AD7768_MCLK_DIV_16, AD7768_DEC_RATE_1024, 16384, AD7768_ECO_MODE पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7768_channels[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.indexed = 1,
		.channel = 0,
		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 24,
			.storagebits = 32,
			.shअगरt = 8,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा ad7768_state अणु
	काष्ठा spi_device *spi;
	काष्ठा regulator *vref;
	काष्ठा mutex lock;
	काष्ठा clk *mclk;
	अचिन्हित पूर्णांक mclk_freq;
	अचिन्हित पूर्णांक samp_freq;
	काष्ठा completion completion;
	काष्ठा iio_trigger *trig;
	काष्ठा gpio_desc *gpio_sync_in;
	स्थिर अक्षर *labels[ARRAY_SIZE(ad7768_channels)];
	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	जोड़ अणु
		काष्ठा अणु
			__be32 chan;
			s64 बारtamp;
		पूर्ण scan;
		__be32 d32;
		u8 d8[2];
	पूर्ण data ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक ad7768_spi_reg_पढ़ो(काष्ठा ad7768_state *st, अचिन्हित पूर्णांक addr,
			       अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक shअगरt;
	पूर्णांक ret;

	shअगरt = 32 - (8 * len);
	st->data.d8[0] = AD7768_RD_FLAG_MSK(addr);

	ret = spi_ग_लिखो_then_पढ़ो(st->spi, st->data.d8, 1,
				  &st->data.d32, len);
	अगर (ret < 0)
		वापस ret;

	वापस (be32_to_cpu(st->data.d32) >> shअगरt);
पूर्ण

अटल पूर्णांक ad7768_spi_reg_ग_लिखो(काष्ठा ad7768_state *st,
				अचिन्हित पूर्णांक addr,
				अचिन्हित पूर्णांक val)
अणु
	st->data.d8[0] = AD7768_WR_FLAG_MSK(addr);
	st->data.d8[1] = val & 0xFF;

	वापस spi_ग_लिखो(st->spi, st->data.d8, 2);
पूर्ण

अटल पूर्णांक ad7768_set_mode(काष्ठा ad7768_state *st,
			   क्रमागत ad7768_conv_mode mode)
अणु
	पूर्णांक regval;

	regval = ad7768_spi_reg_पढ़ो(st, AD7768_REG_CONVERSION, 1);
	अगर (regval < 0)
		वापस regval;

	regval &= ~AD7768_CONV_MODE_MSK;
	regval |= AD7768_CONV_MODE(mode);

	वापस ad7768_spi_reg_ग_लिखो(st, AD7768_REG_CONVERSION, regval);
पूर्ण

अटल पूर्णांक ad7768_scan_direct(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7768_state *st = iio_priv(indio_dev);
	पूर्णांक पढ़ोval, ret;

	reinit_completion(&st->completion);

	ret = ad7768_set_mode(st, AD7768_ONE_SHOT);
	अगर (ret < 0)
		वापस ret;

	ret = रुको_क्रम_completion_समयout(&st->completion,
					  msecs_to_jअगरfies(1000));
	अगर (!ret)
		वापस -ETIMEDOUT;

	पढ़ोval = ad7768_spi_reg_पढ़ो(st, AD7768_REG_ADC_DATA, 3);
	अगर (पढ़ोval < 0)
		वापस पढ़ोval;
	/*
	 * Any SPI configuration of the AD7768-1 can only be
	 * perक्रमmed in continuous conversion mode.
	 */
	ret = ad7768_set_mode(st, AD7768_CONTINUOUS);
	अगर (ret < 0)
		वापस ret;

	वापस पढ़ोval;
पूर्ण

अटल पूर्णांक ad7768_reg_access(काष्ठा iio_dev *indio_dev,
			     अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक ग_लिखोval,
			     अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा ad7768_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	अगर (पढ़ोval) अणु
		ret = ad7768_spi_reg_पढ़ो(st, reg, 1);
		अगर (ret < 0)
			जाओ err_unlock;
		*पढ़ोval = ret;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = ad7768_spi_reg_ग_लिखो(st, reg, ग_लिखोval);
	पूर्ण
err_unlock:
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7768_set_dig_fil(काष्ठा ad7768_state *st,
			      क्रमागत ad7768_dec_rate dec_rate)
अणु
	अचिन्हित पूर्णांक mode;
	पूर्णांक ret;

	अगर (dec_rate == AD7768_DEC_RATE_8 || dec_rate == AD7768_DEC_RATE_16)
		mode = AD7768_DIG_FIL_FIL(dec_rate);
	अन्यथा
		mode = AD7768_DIG_FIL_DEC_RATE(dec_rate);

	ret = ad7768_spi_reg_ग_लिखो(st, AD7768_REG_DIGITAL_FILTER, mode);
	अगर (ret < 0)
		वापस ret;

	/* A sync-in pulse is required every समय the filter dec rate changes */
	gpiod_set_value(st->gpio_sync_in, 1);
	gpiod_set_value(st->gpio_sync_in, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7768_set_freq(काष्ठा ad7768_state *st,
			   अचिन्हित पूर्णांक freq)
अणु
	अचिन्हित पूर्णांक dअगरf_new, dअगरf_old, pwr_mode, i, idx;
	पूर्णांक res, ret;

	dअगरf_old = U32_MAX;
	idx = 0;

	res = DIV_ROUND_CLOSEST(st->mclk_freq, freq);

	/* Find the बंदst match क्रम the desired sampling frequency */
	क्रम (i = 0; i < ARRAY_SIZE(ad7768_clk_config); i++) अणु
		dअगरf_new = असल(res - ad7768_clk_config[i].clk_भाग);
		अगर (dअगरf_new < dअगरf_old) अणु
			dअगरf_old = dअगरf_new;
			idx = i;
		पूर्ण
	पूर्ण

	/*
	 * Set both the mclk_भाग and pwrmode with a single ग_लिखो to the
	 * POWER_CLOCK रेजिस्टर
	 */
	pwr_mode = AD7768_PWR_MCLK_DIV(ad7768_clk_config[idx].mclk_भाग) |
		   AD7768_PWR_PWRMODE(ad7768_clk_config[idx].pwrmode);
	ret = ad7768_spi_reg_ग_लिखो(st, AD7768_REG_POWER_CLOCK, pwr_mode);
	अगर (ret < 0)
		वापस ret;

	ret =  ad7768_set_dig_fil(st, ad7768_clk_config[idx].dec_rate);
	अगर (ret < 0)
		वापस ret;

	st->samp_freq = DIV_ROUND_CLOSEST(st->mclk_freq,
					  ad7768_clk_config[idx].clk_भाग);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ad7768_sampling_freq_avail(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7768_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक freq;
	पूर्णांक i, len = 0;

	क्रम (i = 0; i < ARRAY_SIZE(ad7768_clk_config); i++) अणु
		freq = DIV_ROUND_CLOSEST(st->mclk_freq,
					 ad7768_clk_config[i].clk_भाग);
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d ", freq);
	पूर्ण

	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEV_ATTR_SAMP_FREQ_AVAIL(ad7768_sampling_freq_avail);

अटल पूर्णांक ad7768_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad7768_state *st = iio_priv(indio_dev);
	पूर्णांक scale_uv, ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = ad7768_scan_direct(indio_dev);
		अगर (ret >= 0)
			*val = ret;

		iio_device_release_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		scale_uv = regulator_get_voltage(st->vref);
		अगर (scale_uv < 0)
			वापस scale_uv;

		*val = (scale_uv * 2) / 1000;
		*val2 = chan->scan_type.realbits;

		वापस IIO_VAL_FRACTIONAL_LOG2;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = st->samp_freq;

		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad7768_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	काष्ठा ad7768_state *st = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस ad7768_set_freq(st, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad7768_पढ़ो_label(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, अक्षर *label)
अणु
	काष्ठा ad7768_state *st = iio_priv(indio_dev);

	वापस प्र_लिखो(label, "%s\n", st->labels[chan->channel]);
पूर्ण

अटल काष्ठा attribute *ad7768_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7768_group = अणु
	.attrs = ad7768_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7768_info = अणु
	.attrs = &ad7768_group,
	.पढ़ो_raw = &ad7768_पढ़ो_raw,
	.ग_लिखो_raw = &ad7768_ग_लिखो_raw,
	.पढ़ो_label = ad7768_पढ़ो_label,
	.debugfs_reg_access = &ad7768_reg_access,
पूर्ण;

अटल पूर्णांक ad7768_setup(काष्ठा ad7768_state *st)
अणु
	पूर्णांक ret;

	/*
	 * Two ग_लिखोs to the SPI_RESET[1:0] bits are required to initiate
	 * a software reset. The bits must first be set to 11, and then
	 * to 10. When the sequence is detected, the reset occurs.
	 * See the datasheet, page 70.
	 */
	ret = ad7768_spi_reg_ग_लिखो(st, AD7768_REG_SYNC_RESET, 0x3);
	अगर (ret)
		वापस ret;

	ret = ad7768_spi_reg_ग_लिखो(st, AD7768_REG_SYNC_RESET, 0x2);
	अगर (ret)
		वापस ret;

	st->gpio_sync_in = devm_gpiod_get(&st->spi->dev, "adi,sync-in",
					  GPIOD_OUT_LOW);
	अगर (IS_ERR(st->gpio_sync_in))
		वापस PTR_ERR(st->gpio_sync_in);

	/* Set the शेष sampling frequency to 32000 kSPS */
	वापस ad7768_set_freq(st, 32000);
पूर्ण

अटल irqवापस_t ad7768_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ad7768_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);

	ret = spi_पढ़ो(st->spi, &st->data.scan.chan, 3);
	अगर (ret < 0)
		जाओ err_unlock;

	iio_push_to_buffers_with_बारtamp(indio_dev, &st->data.scan,
					   iio_get_समय_ns(indio_dev));

	iio_trigger_notअगरy_करोne(indio_dev->trig);
err_unlock:
	mutex_unlock(&st->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ad7768_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा iio_dev *indio_dev = dev_id;
	काष्ठा ad7768_state *st = iio_priv(indio_dev);

	अगर (iio_buffer_enabled(indio_dev))
		iio_trigger_poll(st->trig);
	अन्यथा
		complete(&st->completion);

	वापस IRQ_HANDLED;
पूर्ण;

अटल पूर्णांक ad7768_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7768_state *st = iio_priv(indio_dev);

	/*
	 * Write a 1 to the LSB of the INTERFACE_FORMAT रेजिस्टर to enter
	 * continuous पढ़ो mode. Subsequent data पढ़ोs करो not require an
	 * initial 8-bit ग_लिखो to query the ADC_DATA रेजिस्टर.
	 */
	वापस ad7768_spi_reg_ग_लिखो(st, AD7768_REG_INTERFACE_FORMAT, 0x01);
पूर्ण

अटल पूर्णांक ad7768_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7768_state *st = iio_priv(indio_dev);

	/*
	 * To निकास continuous पढ़ो mode, perक्रमm a single पढ़ो of the ADC_DATA
	 * reg (0x2C), which allows further configuration of the device.
	 */
	वापस ad7768_spi_reg_पढ़ो(st, AD7768_REG_ADC_DATA, 3);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops ad7768_buffer_ops = अणु
	.postenable = &ad7768_buffer_postenable,
	.predisable = &ad7768_buffer_predisable,
पूर्ण;

अटल स्थिर काष्ठा iio_trigger_ops ad7768_trigger_ops = अणु
	.validate_device = iio_trigger_validate_own_device,
पूर्ण;

अटल व्योम ad7768_regulator_disable(व्योम *data)
अणु
	काष्ठा ad7768_state *st = data;

	regulator_disable(st->vref);
पूर्ण

अटल व्योम ad7768_clk_disable(व्योम *data)
अणु
	काष्ठा ad7768_state *st = data;

	clk_disable_unprepare(st->mclk);
पूर्ण

अटल पूर्णांक ad7768_set_channel_label(काष्ठा iio_dev *indio_dev,
						पूर्णांक num_channels)
अणु
	काष्ठा ad7768_state *st = iio_priv(indio_dev);
	काष्ठा device *device = indio_dev->dev.parent;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा fwnode_handle *child;
	स्थिर अक्षर *label;
	पूर्णांक crt_ch = 0;

	fwnode = dev_fwnode(device);
	fwnode_क्रम_each_child_node(fwnode, child) अणु
		अगर (fwnode_property_पढ़ो_u32(child, "reg", &crt_ch))
			जारी;

		अगर (crt_ch >= num_channels)
			जारी;

		अगर (fwnode_property_पढ़ो_string(child, "label", &label))
			जारी;

		st->labels[crt_ch] = label;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad7768_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad7768_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	st->spi = spi;

	st->vref = devm_regulator_get(&spi->dev, "vref");
	अगर (IS_ERR(st->vref))
		वापस PTR_ERR(st->vref);

	ret = regulator_enable(st->vref);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to enable specified vref supply\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&spi->dev, ad7768_regulator_disable, st);
	अगर (ret)
		वापस ret;

	st->mclk = devm_clk_get(&spi->dev, "mclk");
	अगर (IS_ERR(st->mclk))
		वापस PTR_ERR(st->mclk);

	ret = clk_prepare_enable(st->mclk);
	अगर (ret < 0)
		वापस ret;

	ret = devm_add_action_or_reset(&spi->dev, ad7768_clk_disable, st);
	अगर (ret)
		वापस ret;

	st->mclk_freq = clk_get_rate(st->mclk);

	spi_set_drvdata(spi, indio_dev);
	mutex_init(&st->lock);

	indio_dev->channels = ad7768_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad7768_channels);
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad7768_info;
	indio_dev->modes = INDIO_सूचीECT_MODE | INDIO_BUFFER_TRIGGERED;

	ret = ad7768_setup(st);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "AD7768 setup failed\n");
		वापस ret;
	पूर्ण

	st->trig = devm_iio_trigger_alloc(&spi->dev, "%s-dev%d",
					  indio_dev->name, indio_dev->id);
	अगर (!st->trig)
		वापस -ENOMEM;

	st->trig->ops = &ad7768_trigger_ops;
	iio_trigger_set_drvdata(st->trig, indio_dev);
	ret = devm_iio_trigger_रेजिस्टर(&spi->dev, st->trig);
	अगर (ret)
		वापस ret;

	indio_dev->trig = iio_trigger_get(st->trig);

	init_completion(&st->completion);

	ret = ad7768_set_channel_label(indio_dev, ARRAY_SIZE(ad7768_channels));
	अगर (ret)
		वापस ret;

	ret = devm_request_irq(&spi->dev, spi->irq,
			       &ad7768_पूर्णांकerrupt,
			       IRQF_TRIGGER_RISING | IRQF_ONESHOT,
			       indio_dev->name, indio_dev);
	अगर (ret)
		वापस ret;

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev,
					      &iio_pollfunc_store_समय,
					      &ad7768_trigger_handler,
					      &ad7768_buffer_ops);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7768_id_table[] = अणु
	अणु "ad7768-1", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7768_id_table);

अटल स्थिर काष्ठा of_device_id ad7768_of_match[] = अणु
	अणु .compatible = "adi,ad7768-1" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7768_of_match);

अटल काष्ठा spi_driver ad7768_driver = अणु
	.driver = अणु
		.name = "ad7768-1",
		.of_match_table = ad7768_of_match,
	पूर्ण,
	.probe = ad7768_probe,
	.id_table = ad7768_id_table,
पूर्ण;
module_spi_driver(ad7768_driver);

MODULE_AUTHOR("Stefan Popa <stefan.popa@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7768-1 ADC driver");
MODULE_LICENSE("GPL v2");
