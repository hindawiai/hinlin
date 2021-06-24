<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Analog Devices AD9467 SPI ADC driver
 *
 * Copyright 2012-2020 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_device.h>


#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश <linux/clk.h>

#समावेश <linux/iio/adc/adi-axi-adc.h>

/*
 * ADI High-Speed ADC common spi पूर्णांकerface रेजिस्टरs
 * See Application-Note AN-877:
 *   https://www.analog.com/media/en/technical-करोcumentation/application-notes/AN-877.pdf
 */

#घोषणा AN877_ADC_REG_CHIP_PORT_CONF		0x00
#घोषणा AN877_ADC_REG_CHIP_ID			0x01
#घोषणा AN877_ADC_REG_CHIP_GRADE		0x02
#घोषणा AN877_ADC_REG_CHAN_INDEX		0x05
#घोषणा AN877_ADC_REG_TRANSFER			0xFF
#घोषणा AN877_ADC_REG_MODES			0x08
#घोषणा AN877_ADC_REG_TEST_IO			0x0D
#घोषणा AN877_ADC_REG_ADC_INPUT			0x0F
#घोषणा AN877_ADC_REG_OFFSET			0x10
#घोषणा AN877_ADC_REG_OUTPUT_MODE		0x14
#घोषणा AN877_ADC_REG_OUTPUT_ADJUST		0x15
#घोषणा AN877_ADC_REG_OUTPUT_PHASE		0x16
#घोषणा AN877_ADC_REG_OUTPUT_DELAY		0x17
#घोषणा AN877_ADC_REG_VREF			0x18
#घोषणा AN877_ADC_REG_ANALOG_INPUT		0x2C

/* AN877_ADC_REG_TEST_IO */
#घोषणा AN877_ADC_TESTMODE_OFF			0x0
#घोषणा AN877_ADC_TESTMODE_MIDSCALE_SHORT	0x1
#घोषणा AN877_ADC_TESTMODE_POS_FULLSCALE	0x2
#घोषणा AN877_ADC_TESTMODE_NEG_FULLSCALE	0x3
#घोषणा AN877_ADC_TESTMODE_ALT_CHECKERBOARD	0x4
#घोषणा AN877_ADC_TESTMODE_PN23_SEQ		0x5
#घोषणा AN877_ADC_TESTMODE_PN9_SEQ		0x6
#घोषणा AN877_ADC_TESTMODE_ONE_ZERO_TOGGLE	0x7
#घोषणा AN877_ADC_TESTMODE_USER			0x8
#घोषणा AN877_ADC_TESTMODE_BIT_TOGGLE		0x9
#घोषणा AN877_ADC_TESTMODE_SYNC			0xA
#घोषणा AN877_ADC_TESTMODE_ONE_BIT_HIGH		0xB
#घोषणा AN877_ADC_TESTMODE_MIXED_BIT_FREQUENCY	0xC
#घोषणा AN877_ADC_TESTMODE_RAMP			0xF

/* AN877_ADC_REG_TRANSFER */
#घोषणा AN877_ADC_TRANSFER_SYNC			0x1

/* AN877_ADC_REG_OUTPUT_MODE */
#घोषणा AN877_ADC_OUTPUT_MODE_OFFSET_BINARY	0x0
#घोषणा AN877_ADC_OUTPUT_MODE_TWOS_COMPLEMENT	0x1
#घोषणा AN877_ADC_OUTPUT_MODE_GRAY_CODE		0x2

/* AN877_ADC_REG_OUTPUT_PHASE */
#घोषणा AN877_ADC_OUTPUT_EVEN_ODD_MODE_EN	0x20
#घोषणा AN877_ADC_INVERT_DCO_CLK		0x80

/* AN877_ADC_REG_OUTPUT_DELAY */
#घोषणा AN877_ADC_DCO_DELAY_ENABLE		0x80

/*
 * Analog Devices AD9265 16-Bit, 125/105/80 MSPS ADC
 */

#घोषणा CHIPID_AD9265			0x64
#घोषणा AD9265_DEF_OUTPUT_MODE		0x40
#घोषणा AD9265_REG_VREF_MASK		0xC0

/*
 * Analog Devices AD9434 12-Bit, 370/500 MSPS ADC
 */

#घोषणा CHIPID_AD9434			0x6A
#घोषणा AD9434_DEF_OUTPUT_MODE		0x00
#घोषणा AD9434_REG_VREF_MASK		0xC0

/*
 * Analog Devices AD9467 16-Bit, 200/250 MSPS ADC
 */

#घोषणा CHIPID_AD9467			0x50
#घोषणा AD9467_DEF_OUTPUT_MODE		0x08
#घोषणा AD9467_REG_VREF_MASK		0x0F

क्रमागत अणु
	ID_AD9265,
	ID_AD9434,
	ID_AD9467,
पूर्ण;

काष्ठा ad9467_chip_info अणु
	काष्ठा adi_axi_adc_chip_info	axi_adc_info;
	अचिन्हित पूर्णांक			शेष_output_mode;
	अचिन्हित पूर्णांक			vref_mask;
पूर्ण;

#घोषणा to_ad9467_chip_info(_info)	\
	container_of(_info, काष्ठा ad9467_chip_info, axi_adc_info)

काष्ठा ad9467_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा clk			*clk;
	अचिन्हित पूर्णांक			output_mode;

	काष्ठा gpio_desc		*pwrकरोwn_gpio;
	काष्ठा gpio_desc		*reset_gpio;
पूर्ण;

अटल पूर्णांक ad9467_spi_पढ़ो(काष्ठा spi_device *spi, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित अक्षर tbuf[2], rbuf[1];
	पूर्णांक ret;

	tbuf[0] = 0x80 | (reg >> 8);
	tbuf[1] = reg & 0xFF;

	ret = spi_ग_लिखो_then_पढ़ो(spi,
				  tbuf, ARRAY_SIZE(tbuf),
				  rbuf, ARRAY_SIZE(rbuf));

	अगर (ret < 0)
		वापस ret;

	वापस rbuf[0];
पूर्ण

अटल पूर्णांक ad9467_spi_ग_लिखो(काष्ठा spi_device *spi, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक val)
अणु
	अचिन्हित अक्षर buf[3];

	buf[0] = reg >> 8;
	buf[1] = reg & 0xFF;
	buf[2] = val;

	वापस spi_ग_लिखो(spi, buf, ARRAY_SIZE(buf));
पूर्ण

अटल पूर्णांक ad9467_reg_access(काष्ठा adi_axi_adc_conv *conv, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक ग_लिखोval, अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा ad9467_state *st = adi_axi_adc_conv_priv(conv);
	काष्ठा spi_device *spi = st->spi;
	पूर्णांक ret;

	अगर (पढ़ोval == शून्य) अणु
		ret = ad9467_spi_ग_लिखो(spi, reg, ग_लिखोval);
		ad9467_spi_ग_लिखो(spi, AN877_ADC_REG_TRANSFER,
				 AN877_ADC_TRANSFER_SYNC);
		वापस ret;
	पूर्ण

	ret = ad9467_spi_पढ़ो(spi, reg);
	अगर (ret < 0)
		वापस ret;
	*पढ़ोval = ret;

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक ad9265_scale_table[][2] = अणु
	अणु1250, 0x00पूर्ण, अणु1500, 0x40पूर्ण, अणु1750, 0x80पूर्ण, अणु2000, 0xC0पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ad9434_scale_table[][2] = अणु
	अणु1600, 0x1Cपूर्ण, अणु1580, 0x1Dपूर्ण, अणु1550, 0x1Eपूर्ण, अणु1520, 0x1Fपूर्ण, अणु1500, 0x00पूर्ण,
	अणु1470, 0x01पूर्ण, अणु1440, 0x02पूर्ण, अणु1420, 0x03पूर्ण, अणु1390, 0x04पूर्ण, अणु1360, 0x05पूर्ण,
	अणु1340, 0x06पूर्ण, अणु1310, 0x07पूर्ण, अणु1280, 0x08पूर्ण, अणु1260, 0x09पूर्ण, अणु1230, 0x0Aपूर्ण,
	अणु1200, 0x0Bपूर्ण, अणु1180, 0x0Cपूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ad9467_scale_table[][2] = अणु
	अणु2000, 0पूर्ण, अणु2100, 6पूर्ण, अणु2200, 7पूर्ण,
	अणु2300, 8पूर्ण, अणु2400, 9पूर्ण, अणु2500, 10पूर्ण,
पूर्ण;

अटल व्योम __ad9467_get_scale(काष्ठा adi_axi_adc_conv *conv, पूर्णांक index,
			       अचिन्हित पूर्णांक *val, अचिन्हित पूर्णांक *val2)
अणु
	स्थिर काष्ठा adi_axi_adc_chip_info *info = conv->chip_info;
	स्थिर काष्ठा iio_chan_spec *chan = &info->channels[0];
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = (info->scale_table[index][0] * 1000000ULL) >>
			chan->scan_type.realbits;
	*val = पंचांगp / 1000000;
	*val2 = पंचांगp % 1000000;
पूर्ण

#घोषणा AD9467_CHAN(_chan, _si, _bits, _sign)				\
अणु									\
	.type = IIO_VOLTAGE,						\
	.indexed = 1,							\
	.channel = _chan,						\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |		\
		BIT(IIO_CHAN_INFO_SAMP_FREQ),				\
	.scan_index = _si,						\
	.scan_type = अणु							\
		.sign = _sign,						\
		.realbits = _bits,					\
		.storagebits = 16,					\
	पूर्ण,								\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad9434_channels[] = अणु
	AD9467_CHAN(0, 0, 12, 'S'),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad9467_channels[] = अणु
	AD9467_CHAN(0, 0, 16, 'S'),
पूर्ण;

अटल स्थिर काष्ठा ad9467_chip_info ad9467_chip_tbl[] = अणु
	[ID_AD9265] = अणु
		.axi_adc_info = अणु
			.id = CHIPID_AD9265,
			.max_rate = 125000000UL,
			.scale_table = ad9265_scale_table,
			.num_scales = ARRAY_SIZE(ad9265_scale_table),
			.channels = ad9467_channels,
			.num_channels = ARRAY_SIZE(ad9467_channels),
		पूर्ण,
		.शेष_output_mode = AD9265_DEF_OUTPUT_MODE,
		.vref_mask = AD9265_REG_VREF_MASK,
	पूर्ण,
	[ID_AD9434] = अणु
		.axi_adc_info = अणु
			.id = CHIPID_AD9434,
			.max_rate = 500000000UL,
			.scale_table = ad9434_scale_table,
			.num_scales = ARRAY_SIZE(ad9434_scale_table),
			.channels = ad9434_channels,
			.num_channels = ARRAY_SIZE(ad9434_channels),
		पूर्ण,
		.शेष_output_mode = AD9434_DEF_OUTPUT_MODE,
		.vref_mask = AD9434_REG_VREF_MASK,
	पूर्ण,
	[ID_AD9467] = अणु
		.axi_adc_info = अणु
			.id = CHIPID_AD9467,
			.max_rate = 250000000UL,
			.scale_table = ad9467_scale_table,
			.num_scales = ARRAY_SIZE(ad9467_scale_table),
			.channels = ad9467_channels,
			.num_channels = ARRAY_SIZE(ad9467_channels),
		पूर्ण,
		.शेष_output_mode = AD9467_DEF_OUTPUT_MODE,
		.vref_mask = AD9467_REG_VREF_MASK,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad9467_get_scale(काष्ठा adi_axi_adc_conv *conv, पूर्णांक *val, पूर्णांक *val2)
अणु
	स्थिर काष्ठा adi_axi_adc_chip_info *info = conv->chip_info;
	स्थिर काष्ठा ad9467_chip_info *info1 = to_ad9467_chip_info(info);
	काष्ठा ad9467_state *st = adi_axi_adc_conv_priv(conv);
	अचिन्हित पूर्णांक i, vref_val;

	vref_val = ad9467_spi_पढ़ो(st->spi, AN877_ADC_REG_VREF);

	vref_val &= info1->vref_mask;

	क्रम (i = 0; i < info->num_scales; i++) अणु
		अगर (vref_val == info->scale_table[i][1])
			अवरोध;
	पूर्ण

	अगर (i == info->num_scales)
		वापस -दुस्फल;

	__ad9467_get_scale(conv, i, val, val2);

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक ad9467_set_scale(काष्ठा adi_axi_adc_conv *conv, पूर्णांक val, पूर्णांक val2)
अणु
	स्थिर काष्ठा adi_axi_adc_chip_info *info = conv->chip_info;
	काष्ठा ad9467_state *st = adi_axi_adc_conv_priv(conv);
	अचिन्हित पूर्णांक scale_val[2];
	अचिन्हित पूर्णांक i;

	अगर (val != 0)
		वापस -EINVAL;

	क्रम (i = 0; i < info->num_scales; i++) अणु
		__ad9467_get_scale(conv, i, &scale_val[0], &scale_val[1]);
		अगर (scale_val[0] != val || scale_val[1] != val2)
			जारी;

		ad9467_spi_ग_लिखो(st->spi, AN877_ADC_REG_VREF,
				 info->scale_table[i][1]);
		ad9467_spi_ग_लिखो(st->spi, AN877_ADC_REG_TRANSFER,
				 AN877_ADC_TRANSFER_SYNC);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad9467_पढ़ो_raw(काष्ठा adi_axi_adc_conv *conv,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ m)
अणु
	काष्ठा ad9467_state *st = adi_axi_adc_conv_priv(conv);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_SCALE:
		वापस ad9467_get_scale(conv, val, val2);
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = clk_get_rate(st->clk);

		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad9467_ग_लिखो_raw(काष्ठा adi_axi_adc_conv *conv,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	स्थिर काष्ठा adi_axi_adc_chip_info *info = conv->chip_info;
	काष्ठा ad9467_state *st = adi_axi_adc_conv_priv(conv);
	दीर्घ r_clk;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		वापस ad9467_set_scale(conv, val, val2);
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		r_clk = clk_round_rate(st->clk, val);
		अगर (r_clk < 0 || r_clk > info->max_rate) अणु
			dev_warn(&st->spi->dev,
				 "Error setting ADC sample rate %ld", r_clk);
			वापस -EINVAL;
		पूर्ण

		वापस clk_set_rate(st->clk, r_clk);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad9467_outpuपंचांगode_set(काष्ठा spi_device *spi, अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक ret;

	ret = ad9467_spi_ग_लिखो(spi, AN877_ADC_REG_OUTPUT_MODE, mode);
	अगर (ret < 0)
		वापस ret;

	वापस ad9467_spi_ग_लिखो(spi, AN877_ADC_REG_TRANSFER,
				AN877_ADC_TRANSFER_SYNC);
पूर्ण

अटल पूर्णांक ad9467_preenable_setup(काष्ठा adi_axi_adc_conv *conv)
अणु
	काष्ठा ad9467_state *st = adi_axi_adc_conv_priv(conv);

	वापस ad9467_outpuपंचांगode_set(st->spi, st->output_mode);
पूर्ण

अटल व्योम ad9467_clk_disable(व्योम *data)
अणु
	काष्ठा ad9467_state *st = data;

	clk_disable_unprepare(st->clk);
पूर्ण

अटल पूर्णांक ad9467_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा ad9467_chip_info *info;
	काष्ठा adi_axi_adc_conv *conv;
	काष्ठा ad9467_state *st;
	अचिन्हित पूर्णांक id;
	पूर्णांक ret;

	info = of_device_get_match_data(&spi->dev);
	अगर (!info)
		वापस -ENODEV;

	conv = devm_adi_axi_adc_conv_रेजिस्टर(&spi->dev, माप(*st));
	अगर (IS_ERR(conv))
		वापस PTR_ERR(conv);

	st = adi_axi_adc_conv_priv(conv);
	st->spi = spi;

	st->clk = devm_clk_get(&spi->dev, "adc-clk");
	अगर (IS_ERR(st->clk))
		वापस PTR_ERR(st->clk);

	ret = clk_prepare_enable(st->clk);
	अगर (ret < 0)
		वापस ret;

	ret = devm_add_action_or_reset(&spi->dev, ad9467_clk_disable, st);
	अगर (ret)
		वापस ret;

	st->pwrकरोwn_gpio = devm_gpiod_get_optional(&spi->dev, "powerdown",
						   GPIOD_OUT_LOW);
	अगर (IS_ERR(st->pwrकरोwn_gpio))
		वापस PTR_ERR(st->pwrकरोwn_gpio);

	st->reset_gpio = devm_gpiod_get_optional(&spi->dev, "reset",
						 GPIOD_OUT_LOW);
	अगर (IS_ERR(st->reset_gpio))
		वापस PTR_ERR(st->reset_gpio);

	अगर (st->reset_gpio) अणु
		udelay(1);
		ret = gpiod_direction_output(st->reset_gpio, 1);
		अगर (ret)
			वापस ret;
		mdelay(10);
	पूर्ण

	spi_set_drvdata(spi, st);

	conv->chip_info = &info->axi_adc_info;

	id = ad9467_spi_पढ़ो(spi, AN877_ADC_REG_CHIP_ID);
	अगर (id != conv->chip_info->id) अणु
		dev_err(&spi->dev, "Mismatch CHIP_ID, got 0x%X, expected 0x%X\n",
			id, conv->chip_info->id);
		वापस -ENODEV;
	पूर्ण

	conv->reg_access = ad9467_reg_access;
	conv->ग_लिखो_raw = ad9467_ग_लिखो_raw;
	conv->पढ़ो_raw = ad9467_पढ़ो_raw;
	conv->preenable_setup = ad9467_preenable_setup;

	st->output_mode = info->शेष_output_mode |
			  AN877_ADC_OUTPUT_MODE_TWOS_COMPLEMENT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ad9467_of_match[] = अणु
	अणु .compatible = "adi,ad9265", .data = &ad9467_chip_tbl[ID_AD9265], पूर्ण,
	अणु .compatible = "adi,ad9434", .data = &ad9467_chip_tbl[ID_AD9434], पूर्ण,
	अणु .compatible = "adi,ad9467", .data = &ad9467_chip_tbl[ID_AD9467], पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad9467_of_match);

अटल काष्ठा spi_driver ad9467_driver = अणु
	.driver = अणु
		.name = "ad9467",
		.of_match_table = ad9467_of_match,
	पूर्ण,
	.probe = ad9467_probe,
पूर्ण;
module_spi_driver(ad9467_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD9467 ADC driver");
MODULE_LICENSE("GPL v2");
