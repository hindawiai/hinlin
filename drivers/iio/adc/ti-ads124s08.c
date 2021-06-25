<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* TI ADS124S0X chip family driver
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 */

#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/sysfs.h>

#समावेश <यंत्र/unaligned.h>

/* Commands */
#घोषणा ADS124S08_CMD_NOP	0x00
#घोषणा ADS124S08_CMD_WAKEUP	0x02
#घोषणा ADS124S08_CMD_PWRDWN	0x04
#घोषणा ADS124S08_CMD_RESET	0x06
#घोषणा ADS124S08_CMD_START	0x08
#घोषणा ADS124S08_CMD_STOP	0x0a
#घोषणा ADS124S08_CMD_SYOCAL	0x16
#घोषणा ADS124S08_CMD_SYGCAL	0x17
#घोषणा ADS124S08_CMD_SFOCAL	0x19
#घोषणा ADS124S08_CMD_RDATA	0x12
#घोषणा ADS124S08_CMD_RREG	0x20
#घोषणा ADS124S08_CMD_WREG	0x40

/* Registers */
#घोषणा ADS124S08_ID_REG	0x00
#घोषणा ADS124S08_STATUS	0x01
#घोषणा ADS124S08_INPUT_MUX	0x02
#घोषणा ADS124S08_PGA		0x03
#घोषणा ADS124S08_DATA_RATE	0x04
#घोषणा ADS124S08_REF		0x05
#घोषणा ADS124S08_IDACMAG	0x06
#घोषणा ADS124S08_IDACMUX	0x07
#घोषणा ADS124S08_VBIAS		0x08
#घोषणा ADS124S08_SYS		0x09
#घोषणा ADS124S08_OFCAL0	0x0a
#घोषणा ADS124S08_OFCAL1	0x0b
#घोषणा ADS124S08_OFCAL2	0x0c
#घोषणा ADS124S08_FSCAL0	0x0d
#घोषणा ADS124S08_FSCAL1	0x0e
#घोषणा ADS124S08_FSCAL2	0x0f
#घोषणा ADS124S08_GPIODAT	0x10
#घोषणा ADS124S08_GPIOCON	0x11

/* ADS124S0x common channels */
#घोषणा ADS124S08_AIN0		0x00
#घोषणा ADS124S08_AIN1		0x01
#घोषणा ADS124S08_AIN2		0x02
#घोषणा ADS124S08_AIN3		0x03
#घोषणा ADS124S08_AIN4		0x04
#घोषणा ADS124S08_AIN5		0x05
#घोषणा ADS124S08_AINCOM	0x0c
/* ADS124S08 only channels */
#घोषणा ADS124S08_AIN6		0x06
#घोषणा ADS124S08_AIN7		0x07
#घोषणा ADS124S08_AIN8		0x08
#घोषणा ADS124S08_AIN9		0x09
#घोषणा ADS124S08_AIN10		0x0a
#घोषणा ADS124S08_AIN11		0x0b
#घोषणा ADS124S08_MAX_CHANNELS	12

#घोषणा ADS124S08_POS_MUX_SHIFT	0x04
#घोषणा ADS124S08_INT_REF		0x09

#घोषणा ADS124S08_START_REG_MASK	0x1f
#घोषणा ADS124S08_NUM_BYTES_MASK	0x1f

#घोषणा ADS124S08_START_CONV	0x01
#घोषणा ADS124S08_STOP_CONV	0x00

क्रमागत ads124s_id अणु
	ADS124S08_ID,
	ADS124S06_ID,
पूर्ण;

काष्ठा ads124s_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
पूर्ण;

काष्ठा ads124s_निजी अणु
	स्थिर काष्ठा ads124s_chip_info	*chip_info;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा spi_device *spi;
	काष्ठा mutex lock;
	/*
	 * Used to correctly align data.
	 * Ensure बारtamp is naturally aligned.
	 * Note that the full buffer length may not be needed अगर not
	 * all channels are enabled, as दीर्घ as the alignment of the
	 * बारtamp is मुख्यtained.
	 */
	u32 buffer[ADS124S08_MAX_CHANNELS + माप(s64)/माप(u32)] __aligned(8);
	u8 data[5] ____cacheline_aligned;
पूर्ण;

#घोषणा ADS124S08_CHAN(index)					\
अणु								\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = index,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.scan_index = index,					\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = 32,					\
		.storagebits = 32,				\
	पूर्ण,							\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ads124s06_channels[] = अणु
	ADS124S08_CHAN(0),
	ADS124S08_CHAN(1),
	ADS124S08_CHAN(2),
	ADS124S08_CHAN(3),
	ADS124S08_CHAN(4),
	ADS124S08_CHAN(5),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ads124s08_channels[] = अणु
	ADS124S08_CHAN(0),
	ADS124S08_CHAN(1),
	ADS124S08_CHAN(2),
	ADS124S08_CHAN(3),
	ADS124S08_CHAN(4),
	ADS124S08_CHAN(5),
	ADS124S08_CHAN(6),
	ADS124S08_CHAN(7),
	ADS124S08_CHAN(8),
	ADS124S08_CHAN(9),
	ADS124S08_CHAN(10),
	ADS124S08_CHAN(11),
पूर्ण;

अटल स्थिर काष्ठा ads124s_chip_info ads124s_chip_info_tbl[] = अणु
	[ADS124S08_ID] = अणु
		.channels = ads124s08_channels,
		.num_channels = ARRAY_SIZE(ads124s08_channels),
	पूर्ण,
	[ADS124S06_ID] = अणु
		.channels = ads124s06_channels,
		.num_channels = ARRAY_SIZE(ads124s06_channels),
	पूर्ण,
पूर्ण;

अटल पूर्णांक ads124s_ग_लिखो_cmd(काष्ठा iio_dev *indio_dev, u8 command)
अणु
	काष्ठा ads124s_निजी *priv = iio_priv(indio_dev);

	priv->data[0] = command;

	वापस spi_ग_लिखो(priv->spi, &priv->data[0], 1);
पूर्ण

अटल पूर्णांक ads124s_ग_लिखो_reg(काष्ठा iio_dev *indio_dev, u8 reg, u8 data)
अणु
	काष्ठा ads124s_निजी *priv = iio_priv(indio_dev);

	priv->data[0] = ADS124S08_CMD_WREG | reg;
	priv->data[1] = 0x0;
	priv->data[2] = data;

	वापस spi_ग_लिखो(priv->spi, &priv->data[0], 3);
पूर्ण

अटल पूर्णांक ads124s_reset(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ads124s_निजी *priv = iio_priv(indio_dev);

	अगर (priv->reset_gpio) अणु
		gpiod_set_value(priv->reset_gpio, 0);
		udelay(200);
		gpiod_set_value(priv->reset_gpio, 1);
	पूर्ण अन्यथा अणु
		वापस ads124s_ग_लिखो_cmd(indio_dev, ADS124S08_CMD_RESET);
	पूर्ण

	वापस 0;
पूर्ण;

अटल पूर्णांक ads124s_पढ़ो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा ads124s_निजी *priv = iio_priv(indio_dev);
	पूर्णांक ret;
	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = &priv->data[0],
			.len = 4,
			.cs_change = 1,
		पूर्ण, अणु
			.tx_buf = &priv->data[1],
			.rx_buf = &priv->data[1],
			.len = 4,
		पूर्ण,
	पूर्ण;

	priv->data[0] = ADS124S08_CMD_RDATA;
	स_रखो(&priv->data[1], ADS124S08_CMD_NOP, माप(priv->data) - 1);

	ret = spi_sync_transfer(priv->spi, t, ARRAY_SIZE(t));
	अगर (ret < 0)
		वापस ret;

	वापस get_unaligned_be24(&priv->data[2]);
पूर्ण

अटल पूर्णांक ads124s_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ m)
अणु
	काष्ठा ads124s_निजी *priv = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ads124s_ग_लिखो_reg(indio_dev, ADS124S08_INPUT_MUX,
					chan->channel);
		अगर (ret) अणु
			dev_err(&priv->spi->dev, "Set ADC CH failed\n");
			जाओ out;
		पूर्ण

		ret = ads124s_ग_लिखो_cmd(indio_dev, ADS124S08_START_CONV);
		अगर (ret) अणु
			dev_err(&priv->spi->dev, "Start conversions failed\n");
			जाओ out;
		पूर्ण

		ret = ads124s_पढ़ो(indio_dev, chan->channel);
		अगर (ret < 0) अणु
			dev_err(&priv->spi->dev, "Read ADC failed\n");
			जाओ out;
		पूर्ण

		*val = ret;

		ret = ads124s_ग_लिखो_cmd(indio_dev, ADS124S08_STOP_CONV);
		अगर (ret) अणु
			dev_err(&priv->spi->dev, "Stop conversions failed\n");
			जाओ out;
		पूर्ण

		ret = IIO_VAL_INT;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
out:
	mutex_unlock(&priv->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ads124s_info = अणु
	.पढ़ो_raw = &ads124s_पढ़ो_raw,
पूर्ण;

अटल irqवापस_t ads124s_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ads124s_निजी *priv = iio_priv(indio_dev);
	पूर्णांक scan_index, j = 0;
	पूर्णांक ret;

	क्रम_each_set_bit(scan_index, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		ret = ads124s_ग_लिखो_reg(indio_dev, ADS124S08_INPUT_MUX,
					scan_index);
		अगर (ret)
			dev_err(&priv->spi->dev, "Set ADC CH failed\n");

		ret = ads124s_ग_लिखो_cmd(indio_dev, ADS124S08_START_CONV);
		अगर (ret)
			dev_err(&priv->spi->dev, "Start ADC conversions failed\n");

		priv->buffer[j] = ads124s_पढ़ो(indio_dev, scan_index);
		ret = ads124s_ग_लिखो_cmd(indio_dev, ADS124S08_STOP_CONV);
		अगर (ret)
			dev_err(&priv->spi->dev, "Stop ADC conversions failed\n");

		j++;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, priv->buffer,
			pf->बारtamp);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ads124s_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ads124s_निजी *ads124s_priv;
	काष्ठा iio_dev *indio_dev;
	स्थिर काष्ठा spi_device_id *spi_id = spi_get_device_id(spi);
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*ads124s_priv));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	ads124s_priv = iio_priv(indio_dev);

	ads124s_priv->reset_gpio = devm_gpiod_get_optional(&spi->dev,
						   "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ads124s_priv->reset_gpio))
		dev_info(&spi->dev, "Reset GPIO not defined\n");

	ads124s_priv->chip_info = &ads124s_chip_info_tbl[spi_id->driver_data];

	spi_set_drvdata(spi, indio_dev);

	ads124s_priv->spi = spi;

	indio_dev->name = spi_id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ads124s_priv->chip_info->channels;
	indio_dev->num_channels = ads124s_priv->chip_info->num_channels;
	indio_dev->info = &ads124s_info;

	mutex_init(&ads124s_priv->lock);

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev, शून्य,
					      ads124s_trigger_handler, शून्य);
	अगर (ret) अणु
		dev_err(&spi->dev, "iio triggered buffer setup failed\n");
		वापस ret;
	पूर्ण

	ads124s_reset(indio_dev);

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ads124s_id[] = अणु
	अणु "ads124s06", ADS124S06_ID पूर्ण,
	अणु "ads124s08", ADS124S08_ID पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ads124s_id);

अटल स्थिर काष्ठा of_device_id ads124s_of_table[] = अणु
	अणु .compatible = "ti,ads124s06" पूर्ण,
	अणु .compatible = "ti,ads124s08" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ads124s_of_table);

अटल काष्ठा spi_driver ads124s_driver = अणु
	.driver = अणु
		.name	= "ads124s08",
		.of_match_table = ads124s_of_table,
	पूर्ण,
	.probe		= ads124s_probe,
	.id_table	= ads124s_id,
पूर्ण;
module_spi_driver(ads124s_driver);

MODULE_AUTHOR("Dan Murphy <dmuprhy@ti.com>");
MODULE_DESCRIPTION("TI TI_ADS12S0X ADC");
MODULE_LICENSE("GPL v2");
