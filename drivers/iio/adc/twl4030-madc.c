<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * TWL4030 MADC module driver-This driver monitors the real समय
 * conversion of analog संकेतs like battery temperature,
 * battery type, battery level etc.
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * J Keerthy <j-keerthy@ti.com>
 *
 * Based on twl4030-madc.c
 * Copyright (C) 2008 Nokia Corporation
 * Mikko Ylinen <mikko.k.ylinen@nokia.com>
 *
 * Amit Kucheria <amit.kucheria@canonical.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/module.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/mutex.h>
#समावेश <linux/bitops.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/types.h>
#समावेश <linux/gfp.h>
#समावेश <linux/err.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/iio/iपन.स>

#घोषणा TWL4030_MADC_MAX_CHANNELS 16

#घोषणा TWL4030_MADC_CTRL1		0x00
#घोषणा TWL4030_MADC_CTRL2		0x01

#घोषणा TWL4030_MADC_RTSELECT_LSB	0x02
#घोषणा TWL4030_MADC_SW1SELECT_LSB	0x06
#घोषणा TWL4030_MADC_SW2SELECT_LSB	0x0A

#घोषणा TWL4030_MADC_RTAVERAGE_LSB	0x04
#घोषणा TWL4030_MADC_SW1AVERAGE_LSB	0x08
#घोषणा TWL4030_MADC_SW2AVERAGE_LSB	0x0C

#घोषणा TWL4030_MADC_CTRL_SW1		0x12
#घोषणा TWL4030_MADC_CTRL_SW2		0x13

#घोषणा TWL4030_MADC_RTCH0_LSB		0x17
#घोषणा TWL4030_MADC_GPCH0_LSB		0x37

#घोषणा TWL4030_MADC_MADCON	(1 << 0)	/* MADC घातer on */
#घोषणा TWL4030_MADC_BUSY	(1 << 0)	/* MADC busy */
/* MADC conversion completion */
#घोषणा TWL4030_MADC_EOC_SW	(1 << 1)
/* MADC SWx start conversion */
#घोषणा TWL4030_MADC_SW_START	(1 << 5)
#घोषणा TWL4030_MADC_ADCIN0	(1 << 0)
#घोषणा TWL4030_MADC_ADCIN1	(1 << 1)
#घोषणा TWL4030_MADC_ADCIN2	(1 << 2)
#घोषणा TWL4030_MADC_ADCIN3	(1 << 3)
#घोषणा TWL4030_MADC_ADCIN4	(1 << 4)
#घोषणा TWL4030_MADC_ADCIN5	(1 << 5)
#घोषणा TWL4030_MADC_ADCIN6	(1 << 6)
#घोषणा TWL4030_MADC_ADCIN7	(1 << 7)
#घोषणा TWL4030_MADC_ADCIN8	(1 << 8)
#घोषणा TWL4030_MADC_ADCIN9	(1 << 9)
#घोषणा TWL4030_MADC_ADCIN10	(1 << 10)
#घोषणा TWL4030_MADC_ADCIN11	(1 << 11)
#घोषणा TWL4030_MADC_ADCIN12	(1 << 12)
#घोषणा TWL4030_MADC_ADCIN13	(1 << 13)
#घोषणा TWL4030_MADC_ADCIN14	(1 << 14)
#घोषणा TWL4030_MADC_ADCIN15	(1 << 15)

/* Fixed channels */
#घोषणा TWL4030_MADC_BTEMP	TWL4030_MADC_ADCIN1
#घोषणा TWL4030_MADC_VBUS	TWL4030_MADC_ADCIN8
#घोषणा TWL4030_MADC_VBKB	TWL4030_MADC_ADCIN9
#घोषणा TWL4030_MADC_ICHG	TWL4030_MADC_ADCIN10
#घोषणा TWL4030_MADC_VCHG	TWL4030_MADC_ADCIN11
#घोषणा TWL4030_MADC_VBAT	TWL4030_MADC_ADCIN12

/* Step size and prescaler ratio */
#घोषणा TEMP_STEP_SIZE          147
#घोषणा TEMP_PSR_R              100
#घोषणा CURR_STEP_SIZE		147
#घोषणा CURR_PSR_R1		44
#घोषणा CURR_PSR_R2		88

#घोषणा TWL4030_BCI_BCICTL1	0x23
#घोषणा TWL4030_BCI_CGAIN	0x020
#घोषणा TWL4030_BCI_MESBAT	(1 << 1)
#घोषणा TWL4030_BCI_TYPEN	(1 << 4)
#घोषणा TWL4030_BCI_ITHEN	(1 << 3)

#घोषणा REG_BCICTL2             0x024
#घोषणा TWL4030_BCI_ITHSENS	0x007

/* Register and bits क्रम GPBR1 रेजिस्टर */
#घोषणा TWL4030_REG_GPBR1		0x0c
#घोषणा TWL4030_GPBR1_MADC_HFCLK_EN	(1 << 7)

#घोषणा TWL4030_USB_SEL_MADC_MCPC	(1<<3)
#घोषणा TWL4030_USB_CARKIT_ANA_CTRL	0xBB

काष्ठा twl4030_madc_conversion_method अणु
	u8 sel;
	u8 avg;
	u8 rbase;
	u8 ctrl;
पूर्ण;

/**
 * काष्ठा twl4030_madc_request - madc request packet क्रम channel conversion
 * @channels:	16 bit biपंचांगap क्रम inभागidual channels
 * @करो_avg:	sample the input channel क्रम 4 consecutive cycles
 * @method:	RT, SW1, SW2
 * @type:	Polling or पूर्णांकerrupt based method
 * @active:	Flag अगर request is active
 * @result_pending: Flag from irq handler, that result is पढ़ोy
 * @raw:	Return raw value, करो not convert it
 * @rbuf:	Result buffer
 */
काष्ठा twl4030_madc_request अणु
	अचिन्हित दीर्घ channels;
	bool करो_avg;
	u16 method;
	u16 type;
	bool active;
	bool result_pending;
	bool raw;
	पूर्णांक rbuf[TWL4030_MADC_MAX_CHANNELS];
पूर्ण;

क्रमागत conversion_methods अणु
	TWL4030_MADC_RT,
	TWL4030_MADC_SW1,
	TWL4030_MADC_SW2,
	TWL4030_MADC_NUM_METHODS
पूर्ण;

क्रमागत sample_type अणु
	TWL4030_MADC_WAIT,
	TWL4030_MADC_IRQ_ONESHOT,
	TWL4030_MADC_IRQ_REARM
पूर्ण;

/**
 * काष्ठा twl4030_madc_data - a container क्रम madc info
 * @dev:		Poपूर्णांकer to device काष्ठाure क्रम madc
 * @lock:		Mutex protecting this data काष्ठाure
 * @usb3v1:		Poपूर्णांकer to bias regulator क्रम madc
 * @requests:		Array of request काष्ठा corresponding to SW1, SW2 and RT
 * @use_second_irq:	IRQ selection (मुख्य or co-processor)
 * @imr:		Interrupt mask रेजिस्टर of MADC
 * @isr:		Interrupt status रेजिस्टर of MADC
 */
काष्ठा twl4030_madc_data अणु
	काष्ठा device *dev;
	काष्ठा mutex lock;
	काष्ठा regulator *usb3v1;
	काष्ठा twl4030_madc_request requests[TWL4030_MADC_NUM_METHODS];
	bool use_second_irq;
	u8 imr;
	u8 isr;
पूर्ण;

अटल पूर्णांक twl4030_madc_conversion(काष्ठा twl4030_madc_request *req);

अटल पूर्णांक twl4030_madc_पढ़ो(काष्ठा iio_dev *iio_dev,
			     स्थिर काष्ठा iio_chan_spec *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा twl4030_madc_data *madc = iio_priv(iio_dev);
	काष्ठा twl4030_madc_request req;
	पूर्णांक ret;

	req.method = madc->use_second_irq ? TWL4030_MADC_SW2 : TWL4030_MADC_SW1;

	req.channels = BIT(chan->channel);
	req.active = false;
	req.type = TWL4030_MADC_WAIT;
	req.raw = !(mask == IIO_CHAN_INFO_PROCESSED);
	req.करो_avg = (mask == IIO_CHAN_INFO_AVERAGE_RAW);

	ret = twl4030_madc_conversion(&req);
	अगर (ret < 0)
		वापस ret;

	*val = req.rbuf[chan->channel];

	वापस IIO_VAL_INT;
पूर्ण

अटल स्थिर काष्ठा iio_info twl4030_madc_iio_info = अणु
	.पढ़ो_raw = &twl4030_madc_पढ़ो,
पूर्ण;

#घोषणा TWL4030_ADC_CHANNEL(_channel, _type, _name) अणु	\
	.type = _type,					\
	.channel = _channel,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |  \
			      BIT(IIO_CHAN_INFO_AVERAGE_RAW) | \
			      BIT(IIO_CHAN_INFO_PROCESSED), \
	.datasheet_name = _name,			\
	.indexed = 1,					\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec twl4030_madc_iio_channels[] = अणु
	TWL4030_ADC_CHANNEL(0, IIO_VOLTAGE, "ADCIN0"),
	TWL4030_ADC_CHANNEL(1, IIO_TEMP, "ADCIN1"),
	TWL4030_ADC_CHANNEL(2, IIO_VOLTAGE, "ADCIN2"),
	TWL4030_ADC_CHANNEL(3, IIO_VOLTAGE, "ADCIN3"),
	TWL4030_ADC_CHANNEL(4, IIO_VOLTAGE, "ADCIN4"),
	TWL4030_ADC_CHANNEL(5, IIO_VOLTAGE, "ADCIN5"),
	TWL4030_ADC_CHANNEL(6, IIO_VOLTAGE, "ADCIN6"),
	TWL4030_ADC_CHANNEL(7, IIO_VOLTAGE, "ADCIN7"),
	TWL4030_ADC_CHANNEL(8, IIO_VOLTAGE, "ADCIN8"),
	TWL4030_ADC_CHANNEL(9, IIO_VOLTAGE, "ADCIN9"),
	TWL4030_ADC_CHANNEL(10, IIO_CURRENT, "ADCIN10"),
	TWL4030_ADC_CHANNEL(11, IIO_VOLTAGE, "ADCIN11"),
	TWL4030_ADC_CHANNEL(12, IIO_VOLTAGE, "ADCIN12"),
	TWL4030_ADC_CHANNEL(13, IIO_VOLTAGE, "ADCIN13"),
	TWL4030_ADC_CHANNEL(14, IIO_VOLTAGE, "ADCIN14"),
	TWL4030_ADC_CHANNEL(15, IIO_VOLTAGE, "ADCIN15"),
पूर्ण;

अटल काष्ठा twl4030_madc_data *twl4030_madc;

काष्ठा twl4030_prescale_भागider_ratios अणु
	s16 numerator;
	s16 denominator;
पूर्ण;

अटल स्थिर काष्ठा twl4030_prescale_भागider_ratios
twl4030_भागider_ratios[16] = अणु
	अणु1, 1पूर्ण,		/* CHANNEL 0 No Prescaler */
	अणु1, 1पूर्ण,		/* CHANNEL 1 No Prescaler */
	अणु6, 10पूर्ण,	/* CHANNEL 2 */
	अणु6, 10पूर्ण,	/* CHANNEL 3 */
	अणु6, 10पूर्ण,	/* CHANNEL 4 */
	अणु6, 10पूर्ण,	/* CHANNEL 5 */
	अणु6, 10पूर्ण,	/* CHANNEL 6 */
	अणु6, 10पूर्ण,	/* CHANNEL 7 */
	अणु3, 14पूर्ण,	/* CHANNEL 8 */
	अणु1, 3पूर्ण,		/* CHANNEL 9 */
	अणु1, 1पूर्ण,		/* CHANNEL 10 No Prescaler */
	अणु15, 100पूर्ण,	/* CHANNEL 11 */
	अणु1, 4पूर्ण,		/* CHANNEL 12 */
	अणु1, 1पूर्ण,		/* CHANNEL 13 Reserved channels */
	अणु1, 1पूर्ण,		/* CHANNEL 14 Reseved channels */
	अणु5, 11पूर्ण,	/* CHANNEL 15 */
पूर्ण;


/* Conversion table from -3 to 55 degrees Celcius */
अटल पूर्णांक twl4030_therm_tbl[] = अणु
	30800,	29500,	28300,	27100,
	26000,	24900,	23900,	22900,	22000,	21100,	20300,	19400,	18700,
	17900,	17200,	16500,	15900,	15300,	14700,	14100,	13600,	13100,
	12600,	12100,	11600,	11200,	10800,	10400,	10000,	9630,	9280,
	8950,	8620,	8310,	8020,	7730,	7460,	7200,	6950,	6710,
	6470,	6250,	6040,	5830,	5640,	5450,	5260,	5090,	4920,
	4760,	4600,	4450,	4310,	4170,	4040,	3910,	3790,	3670,
	3550
पूर्ण;

/*
 * Structure containing the रेजिस्टरs
 * of dअगरferent conversion methods supported by MADC.
 * Hardware or RT real समय conversion request initiated by बाह्यal host
 * processor क्रम RT Signal conversions.
 * External host processors can also request क्रम non RT conversions
 * SW1 and SW2 software conversions also called asynchronous or GPC request.
 */
अटल
स्थिर काष्ठा twl4030_madc_conversion_method twl4030_conversion_methods[] = अणु
	[TWL4030_MADC_RT] = अणु
			     .sel = TWL4030_MADC_RTSELECT_LSB,
			     .avg = TWL4030_MADC_RTAVERAGE_LSB,
			     .rbase = TWL4030_MADC_RTCH0_LSB,
			     पूर्ण,
	[TWL4030_MADC_SW1] = अणु
			      .sel = TWL4030_MADC_SW1SELECT_LSB,
			      .avg = TWL4030_MADC_SW1AVERAGE_LSB,
			      .rbase = TWL4030_MADC_GPCH0_LSB,
			      .ctrl = TWL4030_MADC_CTRL_SW1,
			      पूर्ण,
	[TWL4030_MADC_SW2] = अणु
			      .sel = TWL4030_MADC_SW2SELECT_LSB,
			      .avg = TWL4030_MADC_SW2AVERAGE_LSB,
			      .rbase = TWL4030_MADC_GPCH0_LSB,
			      .ctrl = TWL4030_MADC_CTRL_SW2,
			      पूर्ण,
पूर्ण;

/**
 * twl4030_madc_channel_raw_पढ़ो() - Function to पढ़ो a particular channel value
 * @madc:	poपूर्णांकer to काष्ठा twl4030_madc_data
 * @reg:	lsb of ADC Channel
 *
 * Return: 0 on success, an error code otherwise.
 */
अटल पूर्णांक twl4030_madc_channel_raw_पढ़ो(काष्ठा twl4030_madc_data *madc, u8 reg)
अणु
	u16 val;
	पूर्णांक ret;
	/*
	 * For each ADC channel, we have MSB and LSB रेजिस्टर pair. MSB address
	 * is always LSB address+1. reg parameter is the address of LSB रेजिस्टर
	 */
	ret = twl_i2c_पढ़ो_u16(TWL4030_MODULE_MADC, &val, reg);
	अगर (ret) अणु
		dev_err(madc->dev, "unable to read register 0x%X\n", reg);
		वापस ret;
	पूर्ण

	वापस (पूर्णांक)(val >> 6);
पूर्ण

/*
 * Return battery temperature in degrees Celsius
 * Or < 0 on failure.
 */
अटल पूर्णांक twl4030battery_temperature(पूर्णांक raw_volt)
अणु
	u8 val;
	पूर्णांक temp, curr, volt, res, ret;

	volt = (raw_volt * TEMP_STEP_SIZE) / TEMP_PSR_R;
	/* Getting and calculating the supply current in micro amperes */
	ret = twl_i2c_पढ़ो_u8(TWL_MODULE_MAIN_CHARGE, &val,
		REG_BCICTL2);
	अगर (ret < 0)
		वापस ret;

	curr = ((val & TWL4030_BCI_ITHSENS) + 1) * 10;
	/* Getting and calculating the thermistor resistance in ohms */
	res = volt * 1000 / curr;
	/* calculating temperature */
	क्रम (temp = 58; temp >= 0; temp--) अणु
		पूर्णांक actual = twl4030_therm_tbl[temp];
		अगर ((actual - res) >= 0)
			अवरोध;
	पूर्ण

	वापस temp + 1;
पूर्ण

अटल पूर्णांक twl4030battery_current(पूर्णांक raw_volt)
अणु
	पूर्णांक ret;
	u8 val;

	ret = twl_i2c_पढ़ो_u8(TWL_MODULE_MAIN_CHARGE, &val,
		TWL4030_BCI_BCICTL1);
	अगर (ret)
		वापस ret;
	अगर (val & TWL4030_BCI_CGAIN) /* slope of 0.44 mV/mA */
		वापस (raw_volt * CURR_STEP_SIZE) / CURR_PSR_R1;
	अन्यथा /* slope of 0.88 mV/mA */
		वापस (raw_volt * CURR_STEP_SIZE) / CURR_PSR_R2;
पूर्ण

/*
 * Function to पढ़ो channel values
 * @madc - poपूर्णांकer to twl4030_madc_data काष्ठा
 * @reg_base - Base address of the first channel
 * @Channels - 16 bit biपंचांगap. If the bit is set, channel's value is पढ़ो
 * @buf - The channel values are stored here. अगर पढ़ो fails error
 * @raw - Return raw values without conversion
 * value is stored
 * Returns the number of successfully पढ़ो channels.
 */
अटल पूर्णांक twl4030_madc_पढ़ो_channels(काष्ठा twl4030_madc_data *madc,
				      u8 reg_base, अचिन्हित
				      दीर्घ channels, पूर्णांक *buf,
				      bool raw)
अणु
	पूर्णांक count = 0;
	पूर्णांक i;
	u8 reg;

	क्रम_each_set_bit(i, &channels, TWL4030_MADC_MAX_CHANNELS) अणु
		reg = reg_base + (2 * i);
		buf[i] = twl4030_madc_channel_raw_पढ़ो(madc, reg);
		अगर (buf[i] < 0) अणु
			dev_err(madc->dev, "Unable to read register 0x%X\n",
				reg);
			वापस buf[i];
		पूर्ण
		अगर (raw) अणु
			count++;
			जारी;
		पूर्ण
		चयन (i) अणु
		हाल 10:
			buf[i] = twl4030battery_current(buf[i]);
			अगर (buf[i] < 0) अणु
				dev_err(madc->dev, "err reading current\n");
				वापस buf[i];
			पूर्ण अन्यथा अणु
				count++;
				buf[i] = buf[i] - 750;
			पूर्ण
			अवरोध;
		हाल 1:
			buf[i] = twl4030battery_temperature(buf[i]);
			अगर (buf[i] < 0) अणु
				dev_err(madc->dev, "err reading temperature\n");
				वापस buf[i];
			पूर्ण अन्यथा अणु
				buf[i] -= 3;
				count++;
			पूर्ण
			अवरोध;
		शेष:
			count++;
			/* Analog Input (V) = conv_result * step_size / R
			 * conv_result = decimal value of 10-bit conversion
			 *		 result
			 * step size = 1.5 / (2 ^ 10 -1)
			 * R = Prescaler ratio क्रम input channels.
			 * Result given in mV hence multiplied by 1000.
			 */
			buf[i] = (buf[i] * 3 * 1000 *
				 twl4030_भागider_ratios[i].denominator)
				/ (2 * 1023 *
				twl4030_भागider_ratios[i].numerator);
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

/*
 * Disables irq.
 * @madc - poपूर्णांकer to twl4030_madc_data काष्ठा
 * @id - irq number to be disabled
 * can take one of TWL4030_MADC_RT, TWL4030_MADC_SW1, TWL4030_MADC_SW2
 * corresponding to RT, SW1, SW2 conversion requests.
 * Returns error अगर i2c पढ़ो/ग_लिखो fails.
 */
अटल पूर्णांक twl4030_madc_disable_irq(काष्ठा twl4030_madc_data *madc, u8 id)
अणु
	u8 val;
	पूर्णांक ret;

	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_MADC, &val, madc->imr);
	अगर (ret) अणु
		dev_err(madc->dev, "unable to read imr register 0x%X\n",
			madc->imr);
		वापस ret;
	पूर्ण
	val |= (1 << id);
	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_MADC, val, madc->imr);
	अगर (ret) अणु
		dev_err(madc->dev,
			"unable to write imr register 0x%X\n", madc->imr);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t twl4030_madc_thपढ़ोed_irq_handler(पूर्णांक irq, व्योम *_madc)
अणु
	काष्ठा twl4030_madc_data *madc = _madc;
	स्थिर काष्ठा twl4030_madc_conversion_method *method;
	u8 isr_val, imr_val;
	पूर्णांक i, ret;
	काष्ठा twl4030_madc_request *r;

	mutex_lock(&madc->lock);
	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_MADC, &isr_val, madc->isr);
	अगर (ret) अणु
		dev_err(madc->dev, "unable to read isr register 0x%X\n",
			madc->isr);
		जाओ err_i2c;
	पूर्ण
	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_MADC, &imr_val, madc->imr);
	अगर (ret) अणु
		dev_err(madc->dev, "unable to read imr register 0x%X\n",
			madc->imr);
		जाओ err_i2c;
	पूर्ण
	isr_val &= ~imr_val;
	क्रम (i = 0; i < TWL4030_MADC_NUM_METHODS; i++) अणु
		अगर (!(isr_val & (1 << i)))
			जारी;
		ret = twl4030_madc_disable_irq(madc, i);
		अगर (ret < 0)
			dev_dbg(madc->dev, "Disable interrupt failed %d\n", i);
		madc->requests[i].result_pending = true;
	पूर्ण
	क्रम (i = 0; i < TWL4030_MADC_NUM_METHODS; i++) अणु
		r = &madc->requests[i];
		/* No pending results क्रम this method, move to next one */
		अगर (!r->result_pending)
			जारी;
		method = &twl4030_conversion_methods[r->method];
		/* Read results */
		twl4030_madc_पढ़ो_channels(madc, method->rbase,
					   r->channels, r->rbuf, r->raw);
		/* Free request */
		r->result_pending = false;
		r->active = false;
	पूर्ण
	mutex_unlock(&madc->lock);

	वापस IRQ_HANDLED;

err_i2c:
	/*
	 * In हाल of error check whichever request is active
	 * and service the same.
	 */
	क्रम (i = 0; i < TWL4030_MADC_NUM_METHODS; i++) अणु
		r = &madc->requests[i];
		अगर (!r->active)
			जारी;
		method = &twl4030_conversion_methods[r->method];
		/* Read results */
		twl4030_madc_पढ़ो_channels(madc, method->rbase,
					   r->channels, r->rbuf, r->raw);
		/* Free request */
		r->result_pending = false;
		r->active = false;
	पूर्ण
	mutex_unlock(&madc->lock);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Function which enables the madc conversion
 * by writing to the control रेजिस्टर.
 * @madc - poपूर्णांकer to twl4030_madc_data काष्ठा
 * @conv_method - can be TWL4030_MADC_RT, TWL4030_MADC_SW2, TWL4030_MADC_SW1
 * corresponding to RT SW1 or SW2 conversion methods.
 * Returns 0 अगर succeeds अन्यथा a negative error value
 */
अटल पूर्णांक twl4030_madc_start_conversion(काष्ठा twl4030_madc_data *madc,
					 पूर्णांक conv_method)
अणु
	स्थिर काष्ठा twl4030_madc_conversion_method *method;
	पूर्णांक ret = 0;

	अगर (conv_method != TWL4030_MADC_SW1 && conv_method != TWL4030_MADC_SW2)
		वापस -ENOTSUPP;

	method = &twl4030_conversion_methods[conv_method];
	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_MADC, TWL4030_MADC_SW_START,
			       method->ctrl);
	अगर (ret) अणु
		dev_err(madc->dev, "unable to write ctrl register 0x%X\n",
			method->ctrl);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function that रुकोs क्रम conversion to be पढ़ोy
 * @madc - poपूर्णांकer to twl4030_madc_data काष्ठा
 * @समयout_ms - समयout value in milliseconds
 * @status_reg - ctrl रेजिस्टर
 * वापसs 0 अगर succeeds अन्यथा a negative error value
 */
अटल पूर्णांक twl4030_madc_रुको_conversion_पढ़ोy(काष्ठा twl4030_madc_data *madc,
					      अचिन्हित पूर्णांक समयout_ms,
					      u8 status_reg)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	समयout = jअगरfies + msecs_to_jअगरfies(समयout_ms);
	करो अणु
		u8 reg;

		ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_MADC, &reg, status_reg);
		अगर (ret) अणु
			dev_err(madc->dev,
				"unable to read status register 0x%X\n",
				status_reg);
			वापस ret;
		पूर्ण
		अगर (!(reg & TWL4030_MADC_BUSY) && (reg & TWL4030_MADC_EOC_SW))
			वापस 0;
		usleep_range(500, 2000);
	पूर्ण जबतक (!समय_after(jअगरfies, समयout));
	dev_err(madc->dev, "conversion timeout!\n");

	वापस -EAGAIN;
पूर्ण

/*
 * An exported function which can be called from other kernel drivers.
 * @req twl4030_madc_request काष्ठाure
 * req->rbuf will be filled with पढ़ो values of channels based on the
 * channel index. If a particular channel पढ़ोing fails there will
 * be a negative error value in the corresponding array element.
 * वापसs 0 अगर succeeds अन्यथा error value
 */
अटल पूर्णांक twl4030_madc_conversion(काष्ठा twl4030_madc_request *req)
अणु
	स्थिर काष्ठा twl4030_madc_conversion_method *method;
	पूर्णांक ret;

	अगर (!req || !twl4030_madc)
		वापस -EINVAL;

	mutex_lock(&twl4030_madc->lock);
	अगर (req->method < TWL4030_MADC_RT || req->method > TWL4030_MADC_SW2) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	/* Do we have a conversion request ongoing */
	अगर (twl4030_madc->requests[req->method].active) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	method = &twl4030_conversion_methods[req->method];
	/* Select channels to be converted */
	ret = twl_i2c_ग_लिखो_u16(TWL4030_MODULE_MADC, req->channels, method->sel);
	अगर (ret) अणु
		dev_err(twl4030_madc->dev,
			"unable to write sel register 0x%X\n", method->sel);
		जाओ out;
	पूर्ण
	/* Select averaging क्रम all channels अगर करो_avg is set */
	अगर (req->करो_avg) अणु
		ret = twl_i2c_ग_लिखो_u16(TWL4030_MODULE_MADC, req->channels,
				       method->avg);
		अगर (ret) अणु
			dev_err(twl4030_madc->dev,
				"unable to write avg register 0x%X\n",
				method->avg);
			जाओ out;
		पूर्ण
	पूर्ण
	/* With RT method we should not be here anymore */
	अगर (req->method == TWL4030_MADC_RT) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = twl4030_madc_start_conversion(twl4030_madc, req->method);
	अगर (ret < 0)
		जाओ out;
	twl4030_madc->requests[req->method].active = true;
	/* Wait until conversion is पढ़ोy (ctrl रेजिस्टर वापसs EOC) */
	ret = twl4030_madc_रुको_conversion_पढ़ोy(twl4030_madc, 5, method->ctrl);
	अगर (ret) अणु
		twl4030_madc->requests[req->method].active = false;
		जाओ out;
	पूर्ण
	ret = twl4030_madc_पढ़ो_channels(twl4030_madc, method->rbase,
					 req->channels, req->rbuf, req->raw);
	twl4030_madc->requests[req->method].active = false;

out:
	mutex_unlock(&twl4030_madc->lock);

	वापस ret;
पूर्ण

/**
 * twl4030_madc_set_current_generator() - setup bias current
 *
 * @madc:	poपूर्णांकer to twl4030_madc_data काष्ठा
 * @chan:	can be one of the two values:
 *		0 - Enables bias current क्रम मुख्य battery type पढ़ोing
 *		1 - Enables bias current क्रम मुख्य battery temperature sensing
 * @on:		enable or disable chan.
 *
 * Function to enable or disable bias current क्रम
 * मुख्य battery type पढ़ोing or temperature sensing
 */
अटल पूर्णांक twl4030_madc_set_current_generator(काष्ठा twl4030_madc_data *madc,
					      पूर्णांक chan, पूर्णांक on)
अणु
	पूर्णांक ret;
	पूर्णांक regmask;
	u8 regval;

	ret = twl_i2c_पढ़ो_u8(TWL_MODULE_MAIN_CHARGE,
			      &regval, TWL4030_BCI_BCICTL1);
	अगर (ret) अणु
		dev_err(madc->dev, "unable to read BCICTL1 reg 0x%X",
			TWL4030_BCI_BCICTL1);
		वापस ret;
	पूर्ण

	regmask = chan ? TWL4030_BCI_ITHEN : TWL4030_BCI_TYPEN;
	अगर (on)
		regval |= regmask;
	अन्यथा
		regval &= ~regmask;

	ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE,
			       regval, TWL4030_BCI_BCICTL1);
	अगर (ret) अणु
		dev_err(madc->dev, "unable to write BCICTL1 reg 0x%X\n",
			TWL4030_BCI_BCICTL1);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function that sets MADC software घातer on bit to enable MADC
 * @madc - poपूर्णांकer to twl4030_madc_data काष्ठा
 * @on - Enable or disable MADC software घातer on bit.
 * वापसs error अगर i2c पढ़ो/ग_लिखो fails अन्यथा 0
 */
अटल पूर्णांक twl4030_madc_set_घातer(काष्ठा twl4030_madc_data *madc, पूर्णांक on)
अणु
	u8 regval;
	पूर्णांक ret;

	ret = twl_i2c_पढ़ो_u8(TWL_MODULE_MAIN_CHARGE,
			      &regval, TWL4030_MADC_CTRL1);
	अगर (ret) अणु
		dev_err(madc->dev, "unable to read madc ctrl1 reg 0x%X\n",
			TWL4030_MADC_CTRL1);
		वापस ret;
	पूर्ण
	अगर (on)
		regval |= TWL4030_MADC_MADCON;
	अन्यथा
		regval &= ~TWL4030_MADC_MADCON;
	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_MADC, regval, TWL4030_MADC_CTRL1);
	अगर (ret) अणु
		dev_err(madc->dev, "unable to write madc ctrl1 reg 0x%X\n",
			TWL4030_MADC_CTRL1);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Initialize MADC and request क्रम thपढ़ोed irq
 */
अटल पूर्णांक twl4030_madc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl4030_madc_data *madc;
	काष्ठा twl4030_madc_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक irq, ret;
	u8 regval;
	काष्ठा iio_dev *iio_dev = शून्य;

	अगर (!pdata && !np) अणु
		dev_err(&pdev->dev, "neither platform data nor Device Tree node available\n");
		वापस -EINVAL;
	पूर्ण

	iio_dev = devm_iio_device_alloc(&pdev->dev, माप(*madc));
	अगर (!iio_dev) अणु
		dev_err(&pdev->dev, "failed allocating iio device\n");
		वापस -ENOMEM;
	पूर्ण

	madc = iio_priv(iio_dev);
	madc->dev = &pdev->dev;

	iio_dev->name = dev_name(&pdev->dev);
	iio_dev->info = &twl4030_madc_iio_info;
	iio_dev->modes = INDIO_सूचीECT_MODE;
	iio_dev->channels = twl4030_madc_iio_channels;
	iio_dev->num_channels = ARRAY_SIZE(twl4030_madc_iio_channels);

	/*
	 * Phoenix provides 2 पूर्णांकerrupt lines. The first one is connected to
	 * the OMAP. The other one can be connected to the other processor such
	 * as modem. Hence two separate ISR and IMR रेजिस्टरs.
	 */
	अगर (pdata)
		madc->use_second_irq = (pdata->irq_line != 1);
	अन्यथा
		madc->use_second_irq = of_property_पढ़ो_bool(np,
				       "ti,system-uses-second-madc-irq");

	madc->imr = madc->use_second_irq ? TWL4030_MADC_IMR2 :
					   TWL4030_MADC_IMR1;
	madc->isr = madc->use_second_irq ? TWL4030_MADC_ISR2 :
					   TWL4030_MADC_ISR1;

	ret = twl4030_madc_set_घातer(madc, 1);
	अगर (ret < 0)
		वापस ret;
	ret = twl4030_madc_set_current_generator(madc, 0, 1);
	अगर (ret < 0)
		जाओ err_current_generator;

	ret = twl_i2c_पढ़ो_u8(TWL_MODULE_MAIN_CHARGE,
			      &regval, TWL4030_BCI_BCICTL1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to read reg BCI CTL1 0x%X\n",
			TWL4030_BCI_BCICTL1);
		जाओ err_i2c;
	पूर्ण
	regval |= TWL4030_BCI_MESBAT;
	ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_MAIN_CHARGE,
			       regval, TWL4030_BCI_BCICTL1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to write reg BCI Ctl1 0x%X\n",
			TWL4030_BCI_BCICTL1);
		जाओ err_i2c;
	पूर्ण

	/* Check that MADC घड़ी is on */
	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_INTBR, &regval, TWL4030_REG_GPBR1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to read reg GPBR1 0x%X\n",
				TWL4030_REG_GPBR1);
		जाओ err_i2c;
	पूर्ण

	/* If MADC clk is not on, turn it on */
	अगर (!(regval & TWL4030_GPBR1_MADC_HFCLK_EN)) अणु
		dev_info(&pdev->dev, "clk disabled, enabling\n");
		regval |= TWL4030_GPBR1_MADC_HFCLK_EN;
		ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, regval,
				       TWL4030_REG_GPBR1);
		अगर (ret) अणु
			dev_err(&pdev->dev, "unable to write reg GPBR1 0x%X\n",
					TWL4030_REG_GPBR1);
			जाओ err_i2c;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, iio_dev);
	mutex_init(&madc->lock);

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
				   twl4030_madc_thपढ़ोed_irq_handler,
				   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				   "twl4030_madc", madc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not request irq\n");
		जाओ err_i2c;
	पूर्ण
	twl4030_madc = madc;

	/* Configure MADC[3:6] */
	ret = twl_i2c_पढ़ो_u8(TWL_MODULE_USB, &regval,
			TWL4030_USB_CARKIT_ANA_CTRL);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to read reg CARKIT_ANA_CTRL  0x%X\n",
				TWL4030_USB_CARKIT_ANA_CTRL);
		जाओ err_i2c;
	पूर्ण
	regval |= TWL4030_USB_SEL_MADC_MCPC;
	ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_USB, regval,
				 TWL4030_USB_CARKIT_ANA_CTRL);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to write reg CARKIT_ANA_CTRL 0x%X\n",
				TWL4030_USB_CARKIT_ANA_CTRL);
		जाओ err_i2c;
	पूर्ण

	/* Enable 3v1 bias regulator क्रम MADC[3:6] */
	madc->usb3v1 = devm_regulator_get(madc->dev, "vusb3v1");
	अगर (IS_ERR(madc->usb3v1)) अणु
		ret = -ENODEV;
		जाओ err_i2c;
	पूर्ण

	ret = regulator_enable(madc->usb3v1);
	अगर (ret) अणु
		dev_err(madc->dev, "could not enable 3v1 bias regulator\n");
		जाओ err_i2c;
	पूर्ण

	ret = iio_device_रेजिस्टर(iio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register iio device\n");
		जाओ err_usb3v1;
	पूर्ण

	वापस 0;

err_usb3v1:
	regulator_disable(madc->usb3v1);
err_i2c:
	twl4030_madc_set_current_generator(madc, 0, 0);
err_current_generator:
	twl4030_madc_set_घातer(madc, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक twl4030_madc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *iio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा twl4030_madc_data *madc = iio_priv(iio_dev);

	iio_device_unरेजिस्टर(iio_dev);

	twl4030_madc_set_current_generator(madc, 0, 0);
	twl4030_madc_set_घातer(madc, 0);

	regulator_disable(madc->usb3v1);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id twl_madc_of_match[] = अणु
	अणु .compatible = "ti,twl4030-madc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, twl_madc_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver twl4030_madc_driver = अणु
	.probe = twl4030_madc_probe,
	.हटाओ = twl4030_madc_हटाओ,
	.driver = अणु
		   .name = "twl4030_madc",
		   .of_match_table = of_match_ptr(twl_madc_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(twl4030_madc_driver);

MODULE_DESCRIPTION("TWL4030 ADC driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("J Keerthy");
MODULE_ALIAS("platform:twl4030_madc");
