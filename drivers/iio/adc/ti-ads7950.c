<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments ADS7950 SPI ADC driver
 *
 * Copyright 2016 David Lechner <david@lechnology.com>
 *
 * Based on iio/ad7923.c:
 * Copyright 2011 Analog Devices Inc
 * Copyright 2012 CS Systemes d'Inक्रमmation
 *
 * And also on hwmon/ads79xx.c
 * Copyright (C) 2013 Texas Instruments Incorporated - https://www.ti.com/
 *	Nishanth Menon
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

/*
 * In हाल of ACPI, we use the 5000 mV as शेष क्रम the reference pin.
 * Device tree users encode that via the vref-supply regulator.
 */
#घोषणा TI_ADS7950_VA_MV_ACPI_DEFAULT	5000

#घोषणा TI_ADS7950_CR_GPIO	BIT(14)
#घोषणा TI_ADS7950_CR_MANUAL	BIT(12)
#घोषणा TI_ADS7950_CR_WRITE	BIT(11)
#घोषणा TI_ADS7950_CR_CHAN(ch)	((ch) << 7)
#घोषणा TI_ADS7950_CR_RANGE_5V	BIT(6)
#घोषणा TI_ADS7950_CR_GPIO_DATA	BIT(4)

#घोषणा TI_ADS7950_MAX_CHAN	16
#घोषणा TI_ADS7950_NUM_GPIOS	4

#घोषणा TI_ADS7950_TIMESTAMP_SIZE (माप(पूर्णांक64_t) / माप(__be16))

/* val = value, dec = left shअगरt, bits = number of bits of the mask */
#घोषणा TI_ADS7950_EXTRACT(val, dec, bits) \
	(((val) >> (dec)) & ((1 << (bits)) - 1))

#घोषणा TI_ADS7950_MAN_CMD(cmd)         (TI_ADS7950_CR_MANUAL | (cmd))
#घोषणा TI_ADS7950_GPIO_CMD(cmd)        (TI_ADS7950_CR_GPIO | (cmd))

/* Manual mode configuration */
#घोषणा TI_ADS7950_MAN_CMD_SETTINGS(st) \
	(TI_ADS7950_MAN_CMD(TI_ADS7950_CR_WRITE | st->cmd_settings_biपंचांगask))
/* GPIO mode configuration */
#घोषणा TI_ADS7950_GPIO_CMD_SETTINGS(st) \
	(TI_ADS7950_GPIO_CMD(st->gpio_cmd_settings_biपंचांगask))

काष्ठा ti_ads7950_state अणु
	काष्ठा spi_device	*spi;
	काष्ठा spi_transfer	ring_xfer;
	काष्ठा spi_transfer	scan_single_xfer[3];
	काष्ठा spi_message	ring_msg;
	काष्ठा spi_message	scan_single_msg;

	/* Lock to protect the spi xfer buffers */
	काष्ठा mutex		slock;
	काष्ठा gpio_chip	chip;

	काष्ठा regulator	*reg;
	अचिन्हित पूर्णांक		vref_mv;

	/*
	 * Biपंचांगask of lower 7 bits used क्रम configuration
	 * These bits only can be written when TI_ADS7950_CR_WRITE
	 * is set, otherwise it retains its original state.
	 * [0-3] GPIO संकेत
	 * [4]   Set following frame to वापस GPIO संकेत values
	 * [5]   Powers करोwn device
	 * [6]   Sets Vref range1(2.5v) or range2(5v)
	 *
	 * Bits present on Manual/Auto1/Auto2 commands
	 */
	अचिन्हित पूर्णांक		cmd_settings_biपंचांगask;

	/*
	 * Biपंचांगask of GPIO command
	 * [0-3] GPIO direction
	 * [4-6] Dअगरferent GPIO alarm mode configurations
	 * [7]   GPIO 2 as device range input
	 * [8]   GPIO 3 as device घातer करोwn input
	 * [9]   Reset all रेजिस्टरs
	 * [10-11] N/A
	 */
	अचिन्हित पूर्णांक		gpio_cmd_settings_biपंचांगask;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	u16 rx_buf[TI_ADS7950_MAX_CHAN + 2 + TI_ADS7950_TIMESTAMP_SIZE]
							____cacheline_aligned;
	u16 tx_buf[TI_ADS7950_MAX_CHAN + 2];
	u16 single_tx;
	u16 single_rx;

पूर्ण;

काष्ठा ti_ads7950_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
पूर्ण;

क्रमागत ti_ads7950_id अणु
	TI_ADS7950,
	TI_ADS7951,
	TI_ADS7952,
	TI_ADS7953,
	TI_ADS7954,
	TI_ADS7955,
	TI_ADS7956,
	TI_ADS7957,
	TI_ADS7958,
	TI_ADS7959,
	TI_ADS7960,
	TI_ADS7961,
पूर्ण;

#घोषणा TI_ADS7950_V_CHAN(index, bits)				\
अणु								\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = index,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.address = index,					\
	.datasheet_name = "CH##index",				\
	.scan_index = index,					\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = bits,				\
		.storagebits = 16,				\
		.shअगरt = 12 - (bits),				\
		.endianness = IIO_CPU,				\
	पूर्ण,							\
पूर्ण

#घोषणा DECLARE_TI_ADS7950_4_CHANNELS(name, bits) \
स्थिर काष्ठा iio_chan_spec name ## _channels[] = अणु \
	TI_ADS7950_V_CHAN(0, bits), \
	TI_ADS7950_V_CHAN(1, bits), \
	TI_ADS7950_V_CHAN(2, bits), \
	TI_ADS7950_V_CHAN(3, bits), \
	IIO_CHAN_SOFT_TIMESTAMP(4), \
पूर्ण

#घोषणा DECLARE_TI_ADS7950_8_CHANNELS(name, bits) \
स्थिर काष्ठा iio_chan_spec name ## _channels[] = अणु \
	TI_ADS7950_V_CHAN(0, bits), \
	TI_ADS7950_V_CHAN(1, bits), \
	TI_ADS7950_V_CHAN(2, bits), \
	TI_ADS7950_V_CHAN(3, bits), \
	TI_ADS7950_V_CHAN(4, bits), \
	TI_ADS7950_V_CHAN(5, bits), \
	TI_ADS7950_V_CHAN(6, bits), \
	TI_ADS7950_V_CHAN(7, bits), \
	IIO_CHAN_SOFT_TIMESTAMP(8), \
पूर्ण

#घोषणा DECLARE_TI_ADS7950_12_CHANNELS(name, bits) \
स्थिर काष्ठा iio_chan_spec name ## _channels[] = अणु \
	TI_ADS7950_V_CHAN(0, bits), \
	TI_ADS7950_V_CHAN(1, bits), \
	TI_ADS7950_V_CHAN(2, bits), \
	TI_ADS7950_V_CHAN(3, bits), \
	TI_ADS7950_V_CHAN(4, bits), \
	TI_ADS7950_V_CHAN(5, bits), \
	TI_ADS7950_V_CHAN(6, bits), \
	TI_ADS7950_V_CHAN(7, bits), \
	TI_ADS7950_V_CHAN(8, bits), \
	TI_ADS7950_V_CHAN(9, bits), \
	TI_ADS7950_V_CHAN(10, bits), \
	TI_ADS7950_V_CHAN(11, bits), \
	IIO_CHAN_SOFT_TIMESTAMP(12), \
पूर्ण

#घोषणा DECLARE_TI_ADS7950_16_CHANNELS(name, bits) \
स्थिर काष्ठा iio_chan_spec name ## _channels[] = अणु \
	TI_ADS7950_V_CHAN(0, bits), \
	TI_ADS7950_V_CHAN(1, bits), \
	TI_ADS7950_V_CHAN(2, bits), \
	TI_ADS7950_V_CHAN(3, bits), \
	TI_ADS7950_V_CHAN(4, bits), \
	TI_ADS7950_V_CHAN(5, bits), \
	TI_ADS7950_V_CHAN(6, bits), \
	TI_ADS7950_V_CHAN(7, bits), \
	TI_ADS7950_V_CHAN(8, bits), \
	TI_ADS7950_V_CHAN(9, bits), \
	TI_ADS7950_V_CHAN(10, bits), \
	TI_ADS7950_V_CHAN(11, bits), \
	TI_ADS7950_V_CHAN(12, bits), \
	TI_ADS7950_V_CHAN(13, bits), \
	TI_ADS7950_V_CHAN(14, bits), \
	TI_ADS7950_V_CHAN(15, bits), \
	IIO_CHAN_SOFT_TIMESTAMP(16), \
पूर्ण

अटल DECLARE_TI_ADS7950_4_CHANNELS(ti_ads7950, 12);
अटल DECLARE_TI_ADS7950_8_CHANNELS(ti_ads7951, 12);
अटल DECLARE_TI_ADS7950_12_CHANNELS(ti_ads7952, 12);
अटल DECLARE_TI_ADS7950_16_CHANNELS(ti_ads7953, 12);
अटल DECLARE_TI_ADS7950_4_CHANNELS(ti_ads7954, 10);
अटल DECLARE_TI_ADS7950_8_CHANNELS(ti_ads7955, 10);
अटल DECLARE_TI_ADS7950_12_CHANNELS(ti_ads7956, 10);
अटल DECLARE_TI_ADS7950_16_CHANNELS(ti_ads7957, 10);
अटल DECLARE_TI_ADS7950_4_CHANNELS(ti_ads7958, 8);
अटल DECLARE_TI_ADS7950_8_CHANNELS(ti_ads7959, 8);
अटल DECLARE_TI_ADS7950_12_CHANNELS(ti_ads7960, 8);
अटल DECLARE_TI_ADS7950_16_CHANNELS(ti_ads7961, 8);

अटल स्थिर काष्ठा ti_ads7950_chip_info ti_ads7950_chip_info[] = अणु
	[TI_ADS7950] = अणु
		.channels	= ti_ads7950_channels,
		.num_channels	= ARRAY_SIZE(ti_ads7950_channels),
	पूर्ण,
	[TI_ADS7951] = अणु
		.channels	= ti_ads7951_channels,
		.num_channels	= ARRAY_SIZE(ti_ads7951_channels),
	पूर्ण,
	[TI_ADS7952] = अणु
		.channels	= ti_ads7952_channels,
		.num_channels	= ARRAY_SIZE(ti_ads7952_channels),
	पूर्ण,
	[TI_ADS7953] = अणु
		.channels	= ti_ads7953_channels,
		.num_channels	= ARRAY_SIZE(ti_ads7953_channels),
	पूर्ण,
	[TI_ADS7954] = अणु
		.channels	= ti_ads7954_channels,
		.num_channels	= ARRAY_SIZE(ti_ads7954_channels),
	पूर्ण,
	[TI_ADS7955] = अणु
		.channels	= ti_ads7955_channels,
		.num_channels	= ARRAY_SIZE(ti_ads7955_channels),
	पूर्ण,
	[TI_ADS7956] = अणु
		.channels	= ti_ads7956_channels,
		.num_channels	= ARRAY_SIZE(ti_ads7956_channels),
	पूर्ण,
	[TI_ADS7957] = अणु
		.channels	= ti_ads7957_channels,
		.num_channels	= ARRAY_SIZE(ti_ads7957_channels),
	पूर्ण,
	[TI_ADS7958] = अणु
		.channels	= ti_ads7958_channels,
		.num_channels	= ARRAY_SIZE(ti_ads7958_channels),
	पूर्ण,
	[TI_ADS7959] = अणु
		.channels	= ti_ads7959_channels,
		.num_channels	= ARRAY_SIZE(ti_ads7959_channels),
	पूर्ण,
	[TI_ADS7960] = अणु
		.channels	= ti_ads7960_channels,
		.num_channels	= ARRAY_SIZE(ti_ads7960_channels),
	पूर्ण,
	[TI_ADS7961] = अणु
		.channels	= ti_ads7961_channels,
		.num_channels	= ARRAY_SIZE(ti_ads7961_channels),
	पूर्ण,
पूर्ण;

/*
 * ti_ads7950_update_scan_mode() setup the spi transfer buffer क्रम the new
 * scan mask
 */
अटल पूर्णांक ti_ads7950_update_scan_mode(काष्ठा iio_dev *indio_dev,
				       स्थिर अचिन्हित दीर्घ *active_scan_mask)
अणु
	काष्ठा ti_ads7950_state *st = iio_priv(indio_dev);
	पूर्णांक i, cmd, len;

	len = 0;
	क्रम_each_set_bit(i, active_scan_mask, indio_dev->num_channels) अणु
		cmd = TI_ADS7950_MAN_CMD(TI_ADS7950_CR_CHAN(i));
		st->tx_buf[len++] = cmd;
	पूर्ण

	/* Data क्रम the 1st channel is not वापसed until the 3rd transfer */
	st->tx_buf[len++] = 0;
	st->tx_buf[len++] = 0;

	st->ring_xfer.len = len * 2;

	वापस 0;
पूर्ण

अटल irqवापस_t ti_ads7950_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ti_ads7950_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->slock);
	ret = spi_sync(st->spi, &st->ring_msg);
	अगर (ret < 0)
		जाओ out;

	iio_push_to_buffers_with_बारtamp(indio_dev, &st->rx_buf[2],
					   iio_get_समय_ns(indio_dev));

out:
	mutex_unlock(&st->slock);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ti_ads7950_scan_direct(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक ch)
अणु
	काष्ठा ti_ads7950_state *st = iio_priv(indio_dev);
	पूर्णांक ret, cmd;

	mutex_lock(&st->slock);
	cmd = TI_ADS7950_MAN_CMD(TI_ADS7950_CR_CHAN(ch));
	st->single_tx = cmd;

	ret = spi_sync(st->spi, &st->scan_single_msg);
	अगर (ret)
		जाओ out;

	ret = st->single_rx;

out:
	mutex_unlock(&st->slock);

	वापस ret;
पूर्ण

अटल पूर्णांक ti_ads7950_get_range(काष्ठा ti_ads7950_state *st)
अणु
	पूर्णांक vref;

	अगर (st->vref_mv) अणु
		vref = st->vref_mv;
	पूर्ण अन्यथा अणु
		vref = regulator_get_voltage(st->reg);
		अगर (vref < 0)
			वापस vref;

		vref /= 1000;
	पूर्ण

	अगर (st->cmd_settings_biपंचांगask & TI_ADS7950_CR_RANGE_5V)
		vref *= 2;

	वापस vref;
पूर्ण

अटल पूर्णांक ti_ads7950_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक *val, पूर्णांक *val2, दीर्घ m)
अणु
	काष्ठा ti_ads7950_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ti_ads7950_scan_direct(indio_dev, chan->address);
		अगर (ret < 0)
			वापस ret;

		अगर (chan->address != TI_ADS7950_EXTRACT(ret, 12, 4))
			वापस -EIO;

		*val = TI_ADS7950_EXTRACT(ret, chan->scan_type.shअगरt,
					  chan->scan_type.realbits);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = ti_ads7950_get_range(st);
		अगर (ret < 0)
			वापस ret;

		*val = ret;
		*val2 = (1 << chan->scan_type.realbits) - 1;

		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ti_ads7950_info = अणु
	.पढ़ो_raw		= &ti_ads7950_पढ़ो_raw,
	.update_scan_mode	= ti_ads7950_update_scan_mode,
पूर्ण;

अटल व्योम ti_ads7950_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			   पूर्णांक value)
अणु
	काष्ठा ti_ads7950_state *st = gpiochip_get_data(chip);

	mutex_lock(&st->slock);

	अगर (value)
		st->cmd_settings_biपंचांगask |= BIT(offset);
	अन्यथा
		st->cmd_settings_biपंचांगask &= ~BIT(offset);

	st->single_tx = TI_ADS7950_MAN_CMD_SETTINGS(st);
	spi_sync(st->spi, &st->scan_single_msg);

	mutex_unlock(&st->slock);
पूर्ण

अटल पूर्णांक ti_ads7950_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ti_ads7950_state *st = gpiochip_get_data(chip);
	पूर्णांक ret;

	mutex_lock(&st->slock);

	/* If set as output, वापस the output */
	अगर (st->gpio_cmd_settings_biपंचांगask & BIT(offset)) अणु
		ret = st->cmd_settings_biपंचांगask & BIT(offset);
		जाओ out;
	पूर्ण

	/* GPIO data bit sets SDO bits 12-15 to GPIO input */
	st->cmd_settings_biपंचांगask |= TI_ADS7950_CR_GPIO_DATA;
	st->single_tx = TI_ADS7950_MAN_CMD_SETTINGS(st);
	ret = spi_sync(st->spi, &st->scan_single_msg);
	अगर (ret)
		जाओ out;

	ret = ((st->single_rx >> 12) & BIT(offset)) ? 1 : 0;

	/* Revert back to original settings */
	st->cmd_settings_biपंचांगask &= ~TI_ADS7950_CR_GPIO_DATA;
	st->single_tx = TI_ADS7950_MAN_CMD_SETTINGS(st);
	ret = spi_sync(st->spi, &st->scan_single_msg);
	अगर (ret)
		जाओ out;

out:
	mutex_unlock(&st->slock);

	वापस ret;
पूर्ण

अटल पूर्णांक ti_ads7950_get_direction(काष्ठा gpio_chip *chip,
				    अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ti_ads7950_state *st = gpiochip_get_data(chip);

	/* Biपंचांगask is inverted from GPIO framework 0=input/1=output */
	वापस !(st->gpio_cmd_settings_biपंचांगask & BIT(offset));
पूर्ण

अटल पूर्णांक _ti_ads7950_set_direction(काष्ठा gpio_chip *chip, पूर्णांक offset,
				     पूर्णांक input)
अणु
	काष्ठा ti_ads7950_state *st = gpiochip_get_data(chip);
	पूर्णांक ret = 0;

	mutex_lock(&st->slock);

	/* Only change direction अगर needed */
	अगर (input && (st->gpio_cmd_settings_biपंचांगask & BIT(offset)))
		st->gpio_cmd_settings_biपंचांगask &= ~BIT(offset);
	अन्यथा अगर (!input && !(st->gpio_cmd_settings_biपंचांगask & BIT(offset)))
		st->gpio_cmd_settings_biपंचांगask |= BIT(offset);
	अन्यथा
		जाओ out;

	st->single_tx = TI_ADS7950_GPIO_CMD_SETTINGS(st);
	ret = spi_sync(st->spi, &st->scan_single_msg);

out:
	mutex_unlock(&st->slock);

	वापस ret;
पूर्ण

अटल पूर्णांक ti_ads7950_direction_input(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	वापस _ti_ads7950_set_direction(chip, offset, 1);
पूर्ण

अटल पूर्णांक ti_ads7950_direction_output(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	ti_ads7950_set(chip, offset, value);

	वापस _ti_ads7950_set_direction(chip, offset, 0);
पूर्ण

अटल पूर्णांक ti_ads7950_init_hw(काष्ठा ti_ads7950_state *st)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&st->slock);

	/* Settings क्रम Manual/Auto1/Auto2 commands */
	/* Default to 5v ref */
	st->cmd_settings_biपंचांगask = TI_ADS7950_CR_RANGE_5V;
	st->single_tx = TI_ADS7950_MAN_CMD_SETTINGS(st);
	ret = spi_sync(st->spi, &st->scan_single_msg);
	अगर (ret)
		जाओ out;

	/* Settings क्रम GPIO command */
	st->gpio_cmd_settings_biपंचांगask = 0x0;
	st->single_tx = TI_ADS7950_GPIO_CMD_SETTINGS(st);
	ret = spi_sync(st->spi, &st->scan_single_msg);

out:
	mutex_unlock(&st->slock);

	वापस ret;
पूर्ण

अटल पूर्णांक ti_ads7950_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ti_ads7950_state *st;
	काष्ठा iio_dev *indio_dev;
	स्थिर काष्ठा ti_ads7950_chip_info *info;
	पूर्णांक ret;

	spi->bits_per_word = 16;
	spi->mode |= SPI_CS_WORD;
	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "Error in spi setup\n");
		वापस ret;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;

	info = &ti_ads7950_chip_info[spi_get_device_id(spi)->driver_data];

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = info->channels;
	indio_dev->num_channels = info->num_channels;
	indio_dev->info = &ti_ads7950_info;

	/* build spi ring message */
	spi_message_init(&st->ring_msg);

	st->ring_xfer.tx_buf = &st->tx_buf[0];
	st->ring_xfer.rx_buf = &st->rx_buf[0];
	/* len will be set later */
	st->ring_xfer.cs_change = true;

	spi_message_add_tail(&st->ring_xfer, &st->ring_msg);

	/*
	 * Setup शेष message. The sample is पढ़ो at the end of the first
	 * transfer, then it takes one full cycle to convert the sample and one
	 * more cycle to send the value. The conversion process is driven by
	 * the SPI घड़ी, which is why we have 3 transfers. The middle one is
	 * just dummy data sent जबतक the chip is converting the sample that
	 * was पढ़ो at the end of the first transfer.
	 */

	st->scan_single_xfer[0].tx_buf = &st->single_tx;
	st->scan_single_xfer[0].len = 2;
	st->scan_single_xfer[0].cs_change = 1;
	st->scan_single_xfer[1].tx_buf = &st->single_tx;
	st->scan_single_xfer[1].len = 2;
	st->scan_single_xfer[1].cs_change = 1;
	st->scan_single_xfer[2].rx_buf = &st->single_rx;
	st->scan_single_xfer[2].len = 2;

	spi_message_init_with_transfers(&st->scan_single_msg,
					st->scan_single_xfer, 3);

	/* Use hard coded value क्रम reference voltage in ACPI हाल */
	अगर (ACPI_COMPANION(&spi->dev))
		st->vref_mv = TI_ADS7950_VA_MV_ACPI_DEFAULT;

	mutex_init(&st->slock);

	st->reg = devm_regulator_get(&spi->dev, "vref");
	अगर (IS_ERR(st->reg)) अणु
		dev_err(&spi->dev, "Failed to get regulator \"vref\"\n");
		ret = PTR_ERR(st->reg);
		जाओ error_destroy_mutex;
	पूर्ण

	ret = regulator_enable(st->reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to enable regulator \"vref\"\n");
		जाओ error_destroy_mutex;
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 &ti_ads7950_trigger_handler, शून्य);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to setup triggered buffer\n");
		जाओ error_disable_reg;
	पूर्ण

	ret = ti_ads7950_init_hw(st);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to init adc chip\n");
		जाओ error_cleanup_ring;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to register iio device\n");
		जाओ error_cleanup_ring;
	पूर्ण

	/* Add GPIO chip */
	st->chip.label = dev_name(&st->spi->dev);
	st->chip.parent = &st->spi->dev;
	st->chip.owner = THIS_MODULE;
	st->chip.base = -1;
	st->chip.ngpio = TI_ADS7950_NUM_GPIOS;
	st->chip.get_direction = ti_ads7950_get_direction;
	st->chip.direction_input = ti_ads7950_direction_input;
	st->chip.direction_output = ti_ads7950_direction_output;
	st->chip.get = ti_ads7950_get;
	st->chip.set = ti_ads7950_set;

	ret = gpiochip_add_data(&st->chip, st);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to init GPIOs\n");
		जाओ error_iio_device;
	पूर्ण

	वापस 0;

error_iio_device:
	iio_device_unरेजिस्टर(indio_dev);
error_cleanup_ring:
	iio_triggered_buffer_cleanup(indio_dev);
error_disable_reg:
	regulator_disable(st->reg);
error_destroy_mutex:
	mutex_destroy(&st->slock);

	वापस ret;
पूर्ण

अटल पूर्णांक ti_ads7950_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ti_ads7950_state *st = iio_priv(indio_dev);

	gpiochip_हटाओ(&st->chip);
	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	regulator_disable(st->reg);
	mutex_destroy(&st->slock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ti_ads7950_id[] = अणु
	अणु "ads7950", TI_ADS7950 पूर्ण,
	अणु "ads7951", TI_ADS7951 पूर्ण,
	अणु "ads7952", TI_ADS7952 पूर्ण,
	अणु "ads7953", TI_ADS7953 पूर्ण,
	अणु "ads7954", TI_ADS7954 पूर्ण,
	अणु "ads7955", TI_ADS7955 पूर्ण,
	अणु "ads7956", TI_ADS7956 पूर्ण,
	अणु "ads7957", TI_ADS7957 पूर्ण,
	अणु "ads7958", TI_ADS7958 पूर्ण,
	अणु "ads7959", TI_ADS7959 पूर्ण,
	अणु "ads7960", TI_ADS7960 पूर्ण,
	अणु "ads7961", TI_ADS7961 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ti_ads7950_id);

अटल स्थिर काष्ठा of_device_id ads7950_of_table[] = अणु
	अणु .compatible = "ti,ads7950", .data = &ti_ads7950_chip_info[TI_ADS7950] पूर्ण,
	अणु .compatible = "ti,ads7951", .data = &ti_ads7950_chip_info[TI_ADS7951] पूर्ण,
	अणु .compatible = "ti,ads7952", .data = &ti_ads7950_chip_info[TI_ADS7952] पूर्ण,
	अणु .compatible = "ti,ads7953", .data = &ti_ads7950_chip_info[TI_ADS7953] पूर्ण,
	अणु .compatible = "ti,ads7954", .data = &ti_ads7950_chip_info[TI_ADS7954] पूर्ण,
	अणु .compatible = "ti,ads7955", .data = &ti_ads7950_chip_info[TI_ADS7955] पूर्ण,
	अणु .compatible = "ti,ads7956", .data = &ti_ads7950_chip_info[TI_ADS7956] पूर्ण,
	अणु .compatible = "ti,ads7957", .data = &ti_ads7950_chip_info[TI_ADS7957] पूर्ण,
	अणु .compatible = "ti,ads7958", .data = &ti_ads7950_chip_info[TI_ADS7958] पूर्ण,
	अणु .compatible = "ti,ads7959", .data = &ti_ads7950_chip_info[TI_ADS7959] पूर्ण,
	अणु .compatible = "ti,ads7960", .data = &ti_ads7950_chip_info[TI_ADS7960] पूर्ण,
	अणु .compatible = "ti,ads7961", .data = &ti_ads7950_chip_info[TI_ADS7961] पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ads7950_of_table);

अटल काष्ठा spi_driver ti_ads7950_driver = अणु
	.driver = अणु
		.name	= "ads7950",
		.of_match_table = ads7950_of_table,
	पूर्ण,
	.probe		= ti_ads7950_probe,
	.हटाओ		= ti_ads7950_हटाओ,
	.id_table	= ti_ads7950_id,
पूर्ण;
module_spi_driver(ti_ads7950_driver);

MODULE_AUTHOR("David Lechner <david@lechnology.com>");
MODULE_DESCRIPTION("TI TI_ADS7950 ADC");
MODULE_LICENSE("GPL v2");
