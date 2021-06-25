<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TWL6030 GPADC module driver
 *
 * Copyright (C) 2009-2013 Texas Instruments Inc.
 * Nishant Kamat <nskamat@ti.com>
 * Balaji T K <balajitk@ti.com>
 * Graeme Gregory <gg@slimlogic.co.uk>
 * Girish S Ghongdemath <girishsg@ti.com>
 * Ambresh K <ambresh@ti.com>
 * Oleksandr Kozaruk <oleksandr.kozaruk@ti.com
 *
 * Based on twl4030-madc.c
 * Copyright (C) 2008 Nokia Corporation
 * Mikko Ylinen <mikko.k.ylinen@nokia.com>
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा DRIVER_NAME		"twl6030_gpadc"

/*
 * twl6030 per TRM has 17 channels, and twl6032 has 19 channels
 * 2 test network channels are not used,
 * 2 die temperature channels are not used either, as it is not
 * defined how to convert ADC value to temperature
 */
#घोषणा TWL6030_GPADC_USED_CHANNELS		13
#घोषणा TWL6030_GPADC_MAX_CHANNELS		15
#घोषणा TWL6032_GPADC_USED_CHANNELS		15
#घोषणा TWL6032_GPADC_MAX_CHANNELS		19
#घोषणा TWL6030_GPADC_NUM_TRIM_REGS		16

#घोषणा TWL6030_GPADC_CTRL_P1			0x05

#घोषणा TWL6032_GPADC_GPSELECT_ISB		0x07
#घोषणा TWL6032_GPADC_CTRL_P1			0x08

#घोषणा TWL6032_GPADC_GPCH0_LSB			0x0d
#घोषणा TWL6032_GPADC_GPCH0_MSB			0x0e

#घोषणा TWL6030_GPADC_CTRL_P1_SP1		BIT(3)

#घोषणा TWL6030_GPADC_GPCH0_LSB			(0x29)

#घोषणा TWL6030_GPADC_RT_SW1_EOC_MASK		BIT(5)

#घोषणा TWL6030_GPADC_TRIM1			0xCD

#घोषणा TWL6030_REG_TOGGLE1			0x90
#घोषणा TWL6030_GPADCS				BIT(1)
#घोषणा TWL6030_GPADCR				BIT(0)

/**
 * काष्ठा twl6030_chnl_calib - channel calibration
 * @gain:		slope coefficient क्रम ideal curve
 * @gain_error:		gain error
 * @offset_error:	offset of the real curve
 */
काष्ठा twl6030_chnl_calib अणु
	s32 gain;
	s32 gain_error;
	s32 offset_error;
पूर्ण;

/**
 * काष्ठा twl6030_ideal_code - GPADC calibration parameters
 * GPADC is calibrated in two poपूर्णांकs: बंद to the beginning and
 * to the and of the measurable input range
 *
 * @channel:	channel number
 * @code1:	ideal code क्रम the input at the beginning
 * @code2:	ideal code क्रम at the end of the range
 * @volt1:	voltage input at the beginning(low voltage)
 * @volt2:	voltage input at the end(high voltage)
 */
काष्ठा twl6030_ideal_code अणु
	पूर्णांक channel;
	u16 code1;
	u16 code2;
	u16 volt1;
	u16 volt2;
पूर्ण;

काष्ठा twl6030_gpadc_data;

/**
 * काष्ठा twl6030_gpadc_platक्रमm_data - platक्रमm specअगरic data
 * @nchannels:		number of GPADC channels
 * @iio_channels:	iio channels
 * @ideal:		poपूर्णांकer to calibration parameters
 * @start_conversion:	poपूर्णांकer to ADC start conversion function
 * @channel_to_reg:	poपूर्णांकer to ADC function to convert channel to
 *			रेजिस्टर address क्रम पढ़ोing conversion result
 * @calibrate:		poपूर्णांकer to calibration function
 */
काष्ठा twl6030_gpadc_platक्रमm_data अणु
	स्थिर पूर्णांक nchannels;
	स्थिर काष्ठा iio_chan_spec *iio_channels;
	स्थिर काष्ठा twl6030_ideal_code *ideal;
	पूर्णांक (*start_conversion)(पूर्णांक channel);
	u8 (*channel_to_reg)(पूर्णांक channel);
	पूर्णांक (*calibrate)(काष्ठा twl6030_gpadc_data *gpadc);
पूर्ण;

/**
 * काष्ठा twl6030_gpadc_data - GPADC data
 * @dev:		device poपूर्णांकer
 * @lock:		mutual exclusion lock क्रम the काष्ठाure
 * @irq_complete:	completion to संकेत end of conversion
 * @twl6030_cal_tbl:	poपूर्णांकer to calibration data क्रम each
 *			channel with gain error and offset
 * @pdata:		poपूर्णांकer to device specअगरic data
 */
काष्ठा twl6030_gpadc_data अणु
	काष्ठा device	*dev;
	काष्ठा mutex	lock;
	काष्ठा completion	irq_complete;
	काष्ठा twl6030_chnl_calib	*twl6030_cal_tbl;
	स्थिर काष्ठा twl6030_gpadc_platक्रमm_data *pdata;
पूर्ण;

/*
 * channels 11, 12, 13, 15 and 16 have no calibration data
 * calibration offset is same क्रम channels 1, 3, 4, 5
 *
 * The data is taken from GPADC_TRIM रेजिस्टरs description.
 * GPADC_TRIM रेजिस्टरs keep dअगरference between the code measured
 * at volt1 and volt2 input voltages and corresponding code1 and code2
 */
अटल स्थिर काष्ठा twl6030_ideal_code
	twl6030_ideal[TWL6030_GPADC_USED_CHANNELS] = अणु
	[0] = अणु /* ch 0, बाह्यal, battery type, resistor value */
		.channel = 0,
		.code1 = 116,
		.code2 = 745,
		.volt1 = 141,
		.volt2 = 910,
	पूर्ण,
	[1] = अणु /* ch 1, बाह्यal, battery temperature, NTC resistor value */
		.channel = 1,
		.code1 = 82,
		.code2 = 900,
		.volt1 = 100,
		.volt2 = 1100,
	पूर्ण,
	[2] = अणु /* ch 2, बाह्यal, audio accessory/general purpose */
		.channel = 2,
		.code1 = 55,
		.code2 = 818,
		.volt1 = 101,
		.volt2 = 1499,
	पूर्ण,
	[3] = अणु /* ch 3, बाह्यal, general purpose */
		.channel = 3,
		.code1 = 82,
		.code2 = 900,
		.volt1 = 100,
		.volt2 = 1100,
	पूर्ण,
	[4] = अणु /* ch 4, बाह्यal, temperature measurement/general purpose */
		.channel = 4,
		.code1 = 82,
		.code2 = 900,
		.volt1 = 100,
		.volt2 = 1100,
	पूर्ण,
	[5] = अणु /* ch 5, बाह्यal, general purpose */
		.channel = 5,
		.code1 = 82,
		.code2 = 900,
		.volt1 = 100,
		.volt2 = 1100,
	पूर्ण,
	[6] = अणु /* ch 6, बाह्यal, general purpose */
		.channel = 6,
		.code1 = 82,
		.code2 = 900,
		.volt1 = 100,
		.volt2 = 1100,
	पूर्ण,
	[7] = अणु /* ch 7, पूर्णांकernal, मुख्य battery */
		.channel = 7,
		.code1 = 614,
		.code2 = 941,
		.volt1 = 3001,
		.volt2 = 4599,
	पूर्ण,
	[8] = अणु /* ch 8, पूर्णांकernal, backup battery */
		.channel = 8,
		.code1 = 82,
		.code2 = 688,
		.volt1 = 501,
		.volt2 = 4203,
	पूर्ण,
	[9] = अणु /* ch 9, पूर्णांकernal, बाह्यal अक्षरger input */
		.channel = 9,
		.code1 = 182,
		.code2 = 818,
		.volt1 = 2001,
		.volt2 = 8996,
	पूर्ण,
	[10] = अणु /* ch 10, पूर्णांकernal, VBUS */
		.channel = 10,
		.code1 = 149,
		.code2 = 818,
		.volt1 = 1001,
		.volt2 = 5497,
	पूर्ण,
	[11] = अणु /* ch 11, पूर्णांकernal, VBUS अक्षरging current */
		.channel = 11,
	पूर्ण,
		/* ch 12, पूर्णांकernal, Die temperature */
		/* ch 13, पूर्णांकernal, Die temperature */
	[12] = अणु /* ch 14, पूर्णांकernal, USB ID line */
		.channel = 14,
		.code1 = 48,
		.code2 = 714,
		.volt1 = 323,
		.volt2 = 4800,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा twl6030_ideal_code
			twl6032_ideal[TWL6032_GPADC_USED_CHANNELS] = अणु
	[0] = अणु /* ch 0, बाह्यal, battery type, resistor value */
		.channel = 0,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 440,
		.volt2 = 1000,
	पूर्ण,
	[1] = अणु /* ch 1, बाह्यal, battery temperature, NTC resistor value */
		.channel = 1,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 440,
		.volt2 = 1000,
	पूर्ण,
	[2] = अणु /* ch 2, बाह्यal, audio accessory/general purpose */
		.channel = 2,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 660,
		.volt2 = 1500,
	पूर्ण,
	[3] = अणु /* ch 3, बाह्यal, temperature with बाह्यal diode/general
								purpose */
		.channel = 3,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 440,
		.volt2 = 1000,
	पूर्ण,
	[4] = अणु /* ch 4, बाह्यal, temperature measurement/general purpose */
		.channel = 4,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 440,
		.volt2 = 1000,
	पूर्ण,
	[5] = अणु /* ch 5, बाह्यal, general purpose */
		.channel = 5,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 440,
		.volt2 = 1000,
	पूर्ण,
	[6] = अणु /* ch 6, बाह्यal, general purpose */
		.channel = 6,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 440,
		.volt2 = 1000,
	पूर्ण,
	[7] = अणु /* ch7, पूर्णांकernal, प्रणाली supply */
		.channel = 7,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 2200,
		.volt2 = 5000,
	पूर्ण,
	[8] = अणु /* ch8, पूर्णांकernal, backup battery */
		.channel = 8,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 2200,
		.volt2 = 5000,
	पूर्ण,
	[9] = अणु /* ch 9, पूर्णांकernal, बाह्यal अक्षरger input */
		.channel = 9,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 3960,
		.volt2 = 9000,
	पूर्ण,
	[10] = अणु /* ch10, पूर्णांकernal, VBUS */
		.channel = 10,
		.code1 = 150,
		.code2 = 751,
		.volt1 = 1000,
		.volt2 = 5000,
	पूर्ण,
	[11] = अणु /* ch 11, पूर्णांकernal, VBUS DC-DC output current */
		.channel = 11,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 660,
		.volt2 = 1500,
	पूर्ण,
		/* ch 12, पूर्णांकernal, Die temperature */
		/* ch 13, पूर्णांकernal, Die temperature */
	[12] = अणु /* ch 14, पूर्णांकernal, USB ID line */
		.channel = 14,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 2420,
		.volt2 = 5500,
	पूर्ण,
		/* ch 15, पूर्णांकernal, test network */
		/* ch 16, पूर्णांकernal, test network */
	[13] = अणु /* ch 17, पूर्णांकernal, battery अक्षरging current */
		.channel = 17,
	पूर्ण,
	[14] = अणु /* ch 18, पूर्णांकernal, battery voltage */
		.channel = 18,
		.code1 = 1441,
		.code2 = 3276,
		.volt1 = 2200,
		.volt2 = 5000,
	पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक twl6030_gpadc_ग_लिखो(u8 reg, u8 val)
अणु
	वापस twl_i2c_ग_लिखो_u8(TWL6030_MODULE_GPADC, val, reg);
पूर्ण

अटल अंतरभूत पूर्णांक twl6030_gpadc_पढ़ो(u8 reg, u8 *val)
अणु

	वापस twl_i2c_पढ़ो(TWL6030_MODULE_GPADC, val, reg, 2);
पूर्ण

अटल पूर्णांक twl6030_gpadc_enable_irq(u8 mask)
अणु
	पूर्णांक ret;

	ret = twl6030_पूर्णांकerrupt_unmask(mask, REG_INT_MSK_LINE_B);
	अगर (ret < 0)
		वापस ret;

	ret = twl6030_पूर्णांकerrupt_unmask(mask, REG_INT_MSK_STS_B);

	वापस ret;
पूर्ण

अटल व्योम twl6030_gpadc_disable_irq(u8 mask)
अणु
	twl6030_पूर्णांकerrupt_mask(mask, REG_INT_MSK_LINE_B);
	twl6030_पूर्णांकerrupt_mask(mask, REG_INT_MSK_STS_B);
पूर्ण

अटल irqवापस_t twl6030_gpadc_irq_handler(पूर्णांक irq, व्योम *indio_dev)
अणु
	काष्ठा twl6030_gpadc_data *gpadc = iio_priv(indio_dev);

	complete(&gpadc->irq_complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक twl6030_start_conversion(पूर्णांक channel)
अणु
	वापस twl6030_gpadc_ग_लिखो(TWL6030_GPADC_CTRL_P1,
					TWL6030_GPADC_CTRL_P1_SP1);
पूर्ण

अटल पूर्णांक twl6032_start_conversion(पूर्णांक channel)
अणु
	पूर्णांक ret;

	ret = twl6030_gpadc_ग_लिखो(TWL6032_GPADC_GPSELECT_ISB, channel);
	अगर (ret)
		वापस ret;

	वापस twl6030_gpadc_ग_लिखो(TWL6032_GPADC_CTRL_P1,
						TWL6030_GPADC_CTRL_P1_SP1);
पूर्ण

अटल u8 twl6030_channel_to_reg(पूर्णांक channel)
अणु
	वापस TWL6030_GPADC_GPCH0_LSB + 2 * channel;
पूर्ण

अटल u8 twl6032_channel_to_reg(पूर्णांक channel)
अणु
	/*
	 * क्रम any prior chosen channel, when the conversion is पढ़ोy
	 * the result is avalable in GPCH0_LSB, GPCH0_MSB.
	 */

	वापस TWL6032_GPADC_GPCH0_LSB;
पूर्ण

अटल पूर्णांक twl6030_gpadc_lookup(स्थिर काष्ठा twl6030_ideal_code *ideal,
		पूर्णांक channel, पूर्णांक size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		अगर (ideal[i].channel == channel)
			अवरोध;

	वापस i;
पूर्ण

अटल पूर्णांक twl6030_channel_calibrated(स्थिर काष्ठा twl6030_gpadc_platक्रमm_data
		*pdata, पूर्णांक channel)
अणु
	स्थिर काष्ठा twl6030_ideal_code *ideal = pdata->ideal;
	पूर्णांक i;

	i = twl6030_gpadc_lookup(ideal, channel, pdata->nchannels);
	/* not calibrated channels have 0 in all काष्ठाure members */
	वापस pdata->ideal[i].code2;
पूर्ण

अटल पूर्णांक twl6030_gpadc_make_correction(काष्ठा twl6030_gpadc_data *gpadc,
		पूर्णांक channel, पूर्णांक raw_code)
अणु
	स्थिर काष्ठा twl6030_ideal_code *ideal = gpadc->pdata->ideal;
	पूर्णांक corrected_code;
	पूर्णांक i;

	i = twl6030_gpadc_lookup(ideal, channel, gpadc->pdata->nchannels);
	corrected_code = ((raw_code * 1000) -
		gpadc->twl6030_cal_tbl[i].offset_error) /
		gpadc->twl6030_cal_tbl[i].gain_error;

	वापस corrected_code;
पूर्ण

अटल पूर्णांक twl6030_gpadc_get_raw(काष्ठा twl6030_gpadc_data *gpadc,
		पूर्णांक channel, पूर्णांक *res)
अणु
	u8 reg = gpadc->pdata->channel_to_reg(channel);
	__le16 val;
	पूर्णांक raw_code;
	पूर्णांक ret;

	ret = twl6030_gpadc_पढ़ो(reg, (u8 *)&val);
	अगर (ret) अणु
		dev_dbg(gpadc->dev, "unable to read register 0x%X\n", reg);
		वापस ret;
	पूर्ण

	raw_code = le16_to_cpu(val);
	dev_dbg(gpadc->dev, "GPADC raw code: %d", raw_code);

	अगर (twl6030_channel_calibrated(gpadc->pdata, channel))
		*res = twl6030_gpadc_make_correction(gpadc, channel, raw_code);
	अन्यथा
		*res = raw_code;

	वापस ret;
पूर्ण

अटल पूर्णांक twl6030_gpadc_get_processed(काष्ठा twl6030_gpadc_data *gpadc,
		पूर्णांक channel, पूर्णांक *val)
अणु
	स्थिर काष्ठा twl6030_ideal_code *ideal = gpadc->pdata->ideal;
	पूर्णांक corrected_code;
	पूर्णांक channel_value;
	पूर्णांक i;
	पूर्णांक ret;

	ret = twl6030_gpadc_get_raw(gpadc, channel, &corrected_code);
	अगर (ret)
		वापस ret;

	i = twl6030_gpadc_lookup(ideal, channel, gpadc->pdata->nchannels);
	channel_value = corrected_code *
			gpadc->twl6030_cal_tbl[i].gain;

	/* Shअगरt back पूर्णांकo mV range */
	channel_value /= 1000;

	dev_dbg(gpadc->dev, "GPADC corrected code: %d", corrected_code);
	dev_dbg(gpadc->dev, "GPADC value: %d", channel_value);

	*val = channel_value;

	वापस ret;
पूर्ण

अटल पूर्णांक twl6030_gpadc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     स्थिर काष्ठा iio_chan_spec *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा twl6030_gpadc_data *gpadc = iio_priv(indio_dev);
	पूर्णांक ret;
	दीर्घ समयout;

	mutex_lock(&gpadc->lock);

	ret = gpadc->pdata->start_conversion(chan->channel);
	अगर (ret) अणु
		dev_err(gpadc->dev, "failed to start conversion\n");
		जाओ err;
	पूर्ण
	/* रुको क्रम conversion to complete */
	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
				&gpadc->irq_complete, msecs_to_jअगरfies(5000));
	अगर (समयout == 0) अणु
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण अन्यथा अगर (समयout < 0) अणु
		ret = -EINTR;
		जाओ err;
	पूर्ण

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = twl6030_gpadc_get_raw(gpadc, chan->channel, val);
		ret = ret ? -EIO : IIO_VAL_INT;
		अवरोध;

	हाल IIO_CHAN_INFO_PROCESSED:
		ret = twl6030_gpadc_get_processed(gpadc, chan->channel, val);
		ret = ret ? -EIO : IIO_VAL_INT;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
err:
	mutex_unlock(&gpadc->lock);

	वापस ret;
पूर्ण

/*
 * The GPADC channels are calibrated using a two poपूर्णांक calibration method.
 * The channels measured with two known values: volt1 and volt2, and
 * ideal corresponding output codes are known: code1, code2.
 * The dअगरference(d1, d2) between ideal and measured codes stored in trim
 * रेजिस्टरs.
 * The goal is to find offset and gain of the real curve क्रम each calibrated
 * channel.
 * gain: k = 1 + ((d2 - d1) / (x2 - x1))
 * offset: b = d1 + (k - 1) * x1
 */
अटल व्योम twl6030_calibrate_channel(काष्ठा twl6030_gpadc_data *gpadc,
		पूर्णांक channel, पूर्णांक d1, पूर्णांक d2)
अणु
	पूर्णांक b, k, gain, x1, x2, i;
	स्थिर काष्ठा twl6030_ideal_code *ideal = gpadc->pdata->ideal;

	i = twl6030_gpadc_lookup(ideal, channel, gpadc->pdata->nchannels);

	/* Gain */
	gain = ((ideal[i].volt2 - ideal[i].volt1) * 1000) /
		(ideal[i].code2 - ideal[i].code1);

	x1 = ideal[i].code1;
	x2 = ideal[i].code2;

	/* k - real curve gain */
	k = 1000 + (((d2 - d1) * 1000) / (x2 - x1));

	/* b - offset of the real curve gain */
	b = (d1 * 1000) - (k - 1000) * x1;

	gpadc->twl6030_cal_tbl[i].gain = gain;
	gpadc->twl6030_cal_tbl[i].gain_error = k;
	gpadc->twl6030_cal_tbl[i].offset_error = b;

	dev_dbg(gpadc->dev, "GPADC d1   for Chn: %d = %d\n", channel, d1);
	dev_dbg(gpadc->dev, "GPADC d2   for Chn: %d = %d\n", channel, d2);
	dev_dbg(gpadc->dev, "GPADC x1   for Chn: %d = %d\n", channel, x1);
	dev_dbg(gpadc->dev, "GPADC x2   for Chn: %d = %d\n", channel, x2);
	dev_dbg(gpadc->dev, "GPADC Gain for Chn: %d = %d\n", channel, gain);
	dev_dbg(gpadc->dev, "GPADC k    for Chn: %d = %d\n", channel, k);
	dev_dbg(gpadc->dev, "GPADC b    for Chn: %d = %d\n", channel, b);
पूर्ण

अटल अंतरभूत पूर्णांक twl6030_gpadc_get_trim_offset(s8 d)
अणु
	/*
	 * XXX NOTE!
	 * bit 0 - sign, bit 7 - reserved, 6..1 - trim value
	 * though, the करोcumentation states that trim value
	 * is असलolute value, the correct conversion results are
	 * obtained अगर the value is पूर्णांकerpreted as 2's complement.
	 */
	__u32 temp = ((d & 0x7f) >> 1) | ((d & 1) << 6);

	वापस sign_extend32(temp, 6);
पूर्ण

अटल पूर्णांक twl6030_calibration(काष्ठा twl6030_gpadc_data *gpadc)
अणु
	पूर्णांक ret;
	पूर्णांक chn;
	u8 trim_regs[TWL6030_GPADC_NUM_TRIM_REGS];
	s8 d1, d2;

	/*
	 * क्रम calibration two measurements have been perक्रमmed at
	 * factory, क्रम some channels, during the production test and
	 * have been stored in रेजिस्टरs. This two stored values are
	 * used to correct the measurements. The values represent
	 * offsets क्रम the given input from the output on ideal curve.
	 */
	ret = twl_i2c_पढ़ो(TWL6030_MODULE_ID2, trim_regs,
			TWL6030_GPADC_TRIM1, TWL6030_GPADC_NUM_TRIM_REGS);
	अगर (ret < 0) अणु
		dev_err(gpadc->dev, "calibration failed\n");
		वापस ret;
	पूर्ण

	क्रम (chn = 0; chn < TWL6030_GPADC_MAX_CHANNELS; chn++) अणु

		चयन (chn) अणु
		हाल 0:
			d1 = trim_regs[0];
			d2 = trim_regs[1];
			अवरोध;
		हाल 1:
		हाल 3:
		हाल 4:
		हाल 5:
		हाल 6:
			d1 = trim_regs[4];
			d2 = trim_regs[5];
			अवरोध;
		हाल 2:
			d1 = trim_regs[12];
			d2 = trim_regs[13];
			अवरोध;
		हाल 7:
			d1 = trim_regs[6];
			d2 = trim_regs[7];
			अवरोध;
		हाल 8:
			d1 = trim_regs[2];
			d2 = trim_regs[3];
			अवरोध;
		हाल 9:
			d1 = trim_regs[8];
			d2 = trim_regs[9];
			अवरोध;
		हाल 10:
			d1 = trim_regs[10];
			d2 = trim_regs[11];
			अवरोध;
		हाल 14:
			d1 = trim_regs[14];
			d2 = trim_regs[15];
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		d1 = twl6030_gpadc_get_trim_offset(d1);
		d2 = twl6030_gpadc_get_trim_offset(d2);

		twl6030_calibrate_channel(gpadc, chn, d1, d2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक twl6032_get_trim_value(u8 *trim_regs, अचिन्हित पूर्णांक reg0,
		अचिन्हित पूर्णांक reg1, अचिन्हित पूर्णांक mask0, अचिन्हित पूर्णांक mask1,
		अचिन्हित पूर्णांक shअगरt0)
अणु
	पूर्णांक val;

	val = (trim_regs[reg0] & mask0) << shअगरt0;
	val |= (trim_regs[reg1] & mask1) >> 1;
	अगर (trim_regs[reg1] & 0x01)
		val = -val;

	वापस val;
पूर्ण

अटल पूर्णांक twl6032_calibration(काष्ठा twl6030_gpadc_data *gpadc)
अणु
	पूर्णांक chn, d1 = 0, d2 = 0, temp;
	u8 trim_regs[TWL6030_GPADC_NUM_TRIM_REGS];
	पूर्णांक ret;

	ret = twl_i2c_पढ़ो(TWL6030_MODULE_ID2, trim_regs,
			TWL6030_GPADC_TRIM1, TWL6030_GPADC_NUM_TRIM_REGS);
	अगर (ret < 0) अणु
		dev_err(gpadc->dev, "calibration failed\n");
		वापस ret;
	पूर्ण

	/*
	 * Loop to calculate the value needed क्रम वापसing voltages from
	 * GPADC not values.
	 *
	 * gain is calculated to 3 decimal places fixed poपूर्णांक.
	 */
	क्रम (chn = 0; chn < TWL6032_GPADC_MAX_CHANNELS; chn++) अणु

		चयन (chn) अणु
		हाल 0:
		हाल 1:
		हाल 2:
		हाल 3:
		हाल 4:
		हाल 5:
		हाल 6:
		हाल 11:
		हाल 14:
			d1 = twl6032_get_trim_value(trim_regs, 2, 0, 0x1f,
								0x06, 2);
			d2 = twl6032_get_trim_value(trim_regs, 3, 1, 0x3f,
								0x06, 2);
			अवरोध;
		हाल 8:
			temp = twl6032_get_trim_value(trim_regs, 2, 0, 0x1f,
								0x06, 2);
			d1 = temp + twl6032_get_trim_value(trim_regs, 7, 6,
								0x18, 0x1E, 1);

			temp = twl6032_get_trim_value(trim_regs, 3, 1, 0x3F,
								0x06, 2);
			d2 = temp + twl6032_get_trim_value(trim_regs, 9, 7,
								0x1F, 0x06, 2);
			अवरोध;
		हाल 9:
			temp = twl6032_get_trim_value(trim_regs, 2, 0, 0x1f,
								0x06, 2);
			d1 = temp + twl6032_get_trim_value(trim_regs, 13, 11,
								0x18, 0x1E, 1);

			temp = twl6032_get_trim_value(trim_regs, 3, 1, 0x3f,
								0x06, 2);
			d2 = temp + twl6032_get_trim_value(trim_regs, 15, 13,
								0x1F, 0x06, 1);
			अवरोध;
		हाल 10:
			d1 = twl6032_get_trim_value(trim_regs, 10, 8, 0x0f,
								0x0E, 3);
			d2 = twl6032_get_trim_value(trim_regs, 14, 12, 0x0f,
								0x0E, 3);
			अवरोध;
		हाल 7:
		हाल 18:
			temp = twl6032_get_trim_value(trim_regs, 2, 0, 0x1f,
								0x06, 2);

			d1 = (trim_regs[4] & 0x7E) >> 1;
			अगर (trim_regs[4] & 0x01)
				d1 = -d1;
			d1 += temp;

			temp = twl6032_get_trim_value(trim_regs, 3, 1, 0x3f,
								0x06, 2);

			d2 = (trim_regs[5] & 0xFE) >> 1;
			अगर (trim_regs[5] & 0x01)
				d2 = -d2;

			d2 += temp;
			अवरोध;
		शेष:
			/* No data क्रम other channels */
			जारी;
		पूर्ण

		twl6030_calibrate_channel(gpadc, chn, d1, d2);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा TWL6030_GPADC_CHAN(chn, _type, chan_info) अणु	\
	.type = _type,					\
	.channel = chn,					\
	.info_mask_separate = BIT(chan_info),		\
	.indexed = 1,					\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec twl6030_gpadc_iio_channels[] = अणु
	TWL6030_GPADC_CHAN(0, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(1, IIO_TEMP, IIO_CHAN_INFO_RAW),
	TWL6030_GPADC_CHAN(2, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(3, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(4, IIO_TEMP, IIO_CHAN_INFO_RAW),
	TWL6030_GPADC_CHAN(5, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(6, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(7, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(8, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(9, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(10, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(11, IIO_VOLTAGE, IIO_CHAN_INFO_RAW),
	TWL6030_GPADC_CHAN(14, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec twl6032_gpadc_iio_channels[] = अणु
	TWL6030_GPADC_CHAN(0, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(1, IIO_TEMP, IIO_CHAN_INFO_RAW),
	TWL6030_GPADC_CHAN(2, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(3, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(4, IIO_TEMP, IIO_CHAN_INFO_RAW),
	TWL6030_GPADC_CHAN(5, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(6, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(7, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(8, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(9, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(10, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(11, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(14, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	TWL6030_GPADC_CHAN(17, IIO_VOLTAGE, IIO_CHAN_INFO_RAW),
	TWL6030_GPADC_CHAN(18, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
पूर्ण;

अटल स्थिर काष्ठा iio_info twl6030_gpadc_iio_info = अणु
	.पढ़ो_raw = &twl6030_gpadc_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा twl6030_gpadc_platक्रमm_data twl6030_pdata = अणु
	.iio_channels = twl6030_gpadc_iio_channels,
	.nchannels = TWL6030_GPADC_USED_CHANNELS,
	.ideal = twl6030_ideal,
	.start_conversion = twl6030_start_conversion,
	.channel_to_reg = twl6030_channel_to_reg,
	.calibrate = twl6030_calibration,
पूर्ण;

अटल स्थिर काष्ठा twl6030_gpadc_platक्रमm_data twl6032_pdata = अणु
	.iio_channels = twl6032_gpadc_iio_channels,
	.nchannels = TWL6032_GPADC_USED_CHANNELS,
	.ideal = twl6032_ideal,
	.start_conversion = twl6032_start_conversion,
	.channel_to_reg = twl6032_channel_to_reg,
	.calibrate = twl6032_calibration,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_twl6030_match_tbl[] = अणु
	अणु
		.compatible = "ti,twl6030-gpadc",
		.data = &twl6030_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,twl6032-gpadc",
		.data = &twl6032_pdata,
	पूर्ण,
	अणु /* end */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_twl6030_match_tbl);

अटल पूर्णांक twl6030_gpadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा twl6030_gpadc_data *gpadc;
	स्थिर काष्ठा twl6030_gpadc_platक्रमm_data *pdata;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक irq;
	पूर्णांक ret;

	match = of_match_device(of_twl6030_match_tbl, dev);
	अगर (!match)
		वापस -EINVAL;

	pdata = match->data;

	indio_dev = devm_iio_device_alloc(dev, माप(*gpadc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	gpadc = iio_priv(indio_dev);

	gpadc->twl6030_cal_tbl = devm_kसुस्मृति(dev,
					pdata->nchannels,
					माप(*gpadc->twl6030_cal_tbl),
					GFP_KERNEL);
	अगर (!gpadc->twl6030_cal_tbl)
		वापस -ENOMEM;

	gpadc->dev = dev;
	gpadc->pdata = pdata;

	platक्रमm_set_drvdata(pdev, indio_dev);
	mutex_init(&gpadc->lock);
	init_completion(&gpadc->irq_complete);

	ret = pdata->calibrate(gpadc);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to read calibration registers\n");
		वापस ret;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
				twl6030_gpadc_irq_handler,
				IRQF_ONESHOT, "twl6030_gpadc", indio_dev);

	ret = twl6030_gpadc_enable_irq(TWL6030_GPADC_RT_SW1_EOC_MASK);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to enable GPADC interrupt\n");
		वापस ret;
	पूर्ण

	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID1, TWL6030_GPADCS,
					TWL6030_REG_TOGGLE1);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to enable GPADC module\n");
		वापस ret;
	पूर्ण

	indio_dev->name = DRIVER_NAME;
	indio_dev->info = &twl6030_gpadc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = pdata->iio_channels;
	indio_dev->num_channels = pdata->nchannels;

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक twl6030_gpadc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);

	twl6030_gpadc_disable_irq(TWL6030_GPADC_RT_SW1_EOC_MASK);
	iio_device_unरेजिस्टर(indio_dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक twl6030_gpadc_suspend(काष्ठा device *pdev)
अणु
	पूर्णांक ret;

	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID1, TWL6030_GPADCR,
				TWL6030_REG_TOGGLE1);
	अगर (ret)
		dev_err(pdev, "error resetting GPADC (%d)!\n", ret);

	वापस 0;
पूर्ण;

अटल पूर्णांक twl6030_gpadc_resume(काष्ठा device *pdev)
अणु
	पूर्णांक ret;

	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID1, TWL6030_GPADCS,
				TWL6030_REG_TOGGLE1);
	अगर (ret)
		dev_err(pdev, "error setting GPADC (%d)!\n", ret);

	वापस 0;
पूर्ण;
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(twl6030_gpadc_pm_ops, twl6030_gpadc_suspend,
					twl6030_gpadc_resume);

अटल काष्ठा platक्रमm_driver twl6030_gpadc_driver = अणु
	.probe		= twl6030_gpadc_probe,
	.हटाओ		= twl6030_gpadc_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.pm	= &twl6030_gpadc_pm_ops,
		.of_match_table = of_twl6030_match_tbl,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(twl6030_gpadc_driver);

MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_AUTHOR("Balaji T K <balajitk@ti.com>");
MODULE_AUTHOR("Graeme Gregory <gg@slimlogic.co.uk>");
MODULE_AUTHOR("Oleksandr Kozaruk <oleksandr.kozaruk@ti.com");
MODULE_DESCRIPTION("twl6030 ADC driver");
MODULE_LICENSE("GPL");
