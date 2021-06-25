<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, 2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/iio/adc/qcom-vadc-common.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/iio/qcom,spmi-vadc.h>

#घोषणा ADC5_USR_REVISION1			0x0
#घोषणा ADC5_USR_STATUS1			0x8
#घोषणा ADC5_USR_STATUS1_CONV_FAULT		BIT(7)
#घोषणा ADC5_USR_STATUS1_REQ_STS		BIT(1)
#घोषणा ADC5_USR_STATUS1_EOC			BIT(0)
#घोषणा ADC5_USR_STATUS1_REQ_STS_EOC_MASK	0x3

#घोषणा ADC5_USR_STATUS2			0x9
#घोषणा ADC5_USR_STATUS2_CONV_SEQ_MASK		0x70
#घोषणा ADC5_USR_STATUS2_CONV_SEQ_MASK_SHIFT	0x5

#घोषणा ADC5_USR_IBAT_MEAS			0xf
#घोषणा ADC5_USR_IBAT_MEAS_SUPPORTED		BIT(0)

#घोषणा ADC5_USR_DIG_PARAM			0x42
#घोषणा ADC5_USR_DIG_PARAM_CAL_VAL		BIT(6)
#घोषणा ADC5_USR_DIG_PARAM_CAL_VAL_SHIFT	6
#घोषणा ADC5_USR_DIG_PARAM_CAL_SEL		0x30
#घोषणा ADC5_USR_DIG_PARAM_CAL_SEL_SHIFT	4
#घोषणा ADC5_USR_DIG_PARAM_DEC_RATIO_SEL	0xc
#घोषणा ADC5_USR_DIG_PARAM_DEC_RATIO_SEL_SHIFT	2

#घोषणा ADC5_USR_FAST_AVG_CTL			0x43
#घोषणा ADC5_USR_FAST_AVG_CTL_EN		BIT(7)
#घोषणा ADC5_USR_FAST_AVG_CTL_SAMPLES_MASK	0x7

#घोषणा ADC5_USR_CH_SEL_CTL			0x44

#घोषणा ADC5_USR_DELAY_CTL			0x45
#घोषणा ADC5_USR_HW_SETTLE_DELAY_MASK		0xf

#घोषणा ADC5_USR_EN_CTL1			0x46
#घोषणा ADC5_USR_EN_CTL1_ADC_EN			BIT(7)

#घोषणा ADC5_USR_CONV_REQ			0x47
#घोषणा ADC5_USR_CONV_REQ_REQ			BIT(7)

#घोषणा ADC5_USR_DATA0				0x50

#घोषणा ADC5_USR_DATA1				0x51

#घोषणा ADC5_USR_IBAT_DATA0			0x52

#घोषणा ADC5_USR_IBAT_DATA1			0x53

#घोषणा ADC_CHANNEL_OFFSET			0x8
#घोषणा ADC_CHANNEL_MASK			GENMASK(7, 0)

/*
 * Conversion समय varies based on the decimation, घड़ी rate, fast average
 * samples and measurements queued across dअगरferent VADC peripherals.
 * Set the समयout to a max of 100ms.
 */
#घोषणा ADC5_CONV_TIME_MIN_US			263
#घोषणा ADC5_CONV_TIME_MAX_US			264
#घोषणा ADC5_CONV_TIME_RETRY			400
#घोषणा ADC5_CONV_TIMEOUT			msecs_to_jअगरfies(100)

/* Digital version >= 5.3 supports hw_settle_2 */
#घोषणा ADC5_HW_SETTLE_DIFF_MINOR		3
#घोषणा ADC5_HW_SETTLE_DIFF_MAJOR		5

/* For PMIC7 */
#घोषणा ADC_APP_SID				0x40
#घोषणा ADC_APP_SID_MASK			GENMASK(3, 0)
#घोषणा ADC7_CONV_TIMEOUT			msecs_to_jअगरfies(10)

क्रमागत adc5_cal_method अणु
	ADC5_NO_CAL = 0,
	ADC5_RATIOMETRIC_CAL,
	ADC5_ABSOLUTE_CAL
पूर्ण;

क्रमागत adc5_cal_val अणु
	ADC5_TIMER_CAL = 0,
	ADC5_NEW_CAL
पूर्ण;

/**
 * काष्ठा adc5_channel_prop - ADC channel property.
 * @channel: channel number, refer to the channel list.
 * @cal_method: calibration method.
 * @cal_val: calibration value
 * @decimation: sampling rate supported क्रम the channel.
 * @sid: slave id of PMIC owning the channel, क्रम PMIC7.
 * @prescale: channel scaling perक्रमmed on the input संकेत.
 * @hw_settle_समय: the समय between AMUX being configured and the
 *	start of conversion.
 * @avg_samples: ability to provide single result from the ADC
 *	that is an average of multiple measurements.
 * @scale_fn_type: Represents the scaling function to convert voltage
 *	physical units desired by the client क्रम the channel.
 * @datasheet_name: Channel name used in device tree.
 */
काष्ठा adc5_channel_prop अणु
	अचिन्हित पूर्णांक		channel;
	क्रमागत adc5_cal_method	cal_method;
	क्रमागत adc5_cal_val	cal_val;
	अचिन्हित पूर्णांक		decimation;
	अचिन्हित पूर्णांक		sid;
	अचिन्हित पूर्णांक		prescale;
	अचिन्हित पूर्णांक		hw_settle_समय;
	अचिन्हित पूर्णांक		avg_samples;
	क्रमागत vadc_scale_fn_type	scale_fn_type;
	स्थिर अक्षर		*datasheet_name;
पूर्ण;

/**
 * काष्ठा adc5_chip - ADC निजी काष्ठाure.
 * @regmap: SPMI ADC5 peripheral रेजिस्टर map field.
 * @dev: SPMI ADC5 device.
 * @base: base address क्रम the ADC peripheral.
 * @nchannels: number of ADC channels.
 * @chan_props: array of ADC channel properties.
 * @iio_chans: array of IIO channels specअगरication.
 * @poll_eoc: use polling instead of पूर्णांकerrupt.
 * @complete: ADC result notअगरication after पूर्णांकerrupt is received.
 * @lock: ADC lock क्रम access to the peripheral.
 * @data: software configuration data.
 */
काष्ठा adc5_chip अणु
	काष्ठा regmap		*regmap;
	काष्ठा device		*dev;
	u16			base;
	अचिन्हित पूर्णांक		nchannels;
	काष्ठा adc5_channel_prop	*chan_props;
	काष्ठा iio_chan_spec	*iio_chans;
	bool			poll_eoc;
	काष्ठा completion	complete;
	काष्ठा mutex		lock;
	स्थिर काष्ठा adc5_data	*data;
पूर्ण;

अटल पूर्णांक adc5_पढ़ो(काष्ठा adc5_chip *adc, u16 offset, u8 *data, पूर्णांक len)
अणु
	वापस regmap_bulk_पढ़ो(adc->regmap, adc->base + offset, data, len);
पूर्ण

अटल पूर्णांक adc5_ग_लिखो(काष्ठा adc5_chip *adc, u16 offset, u8 *data, पूर्णांक len)
अणु
	वापस regmap_bulk_ग_लिखो(adc->regmap, adc->base + offset, data, len);
पूर्ण

अटल पूर्णांक adc5_masked_ग_लिखो(काष्ठा adc5_chip *adc, u16 offset, u8 mask, u8 val)
अणु
	वापस regmap_update_bits(adc->regmap, adc->base + offset, mask, val);
पूर्ण

अटल पूर्णांक adc5_पढ़ो_voltage_data(काष्ठा adc5_chip *adc, u16 *data)
अणु
	पूर्णांक ret;
	u8 rslt_lsb, rslt_msb;

	ret = adc5_पढ़ो(adc, ADC5_USR_DATA0, &rslt_lsb, माप(rslt_lsb));
	अगर (ret)
		वापस ret;

	ret = adc5_पढ़ो(adc, ADC5_USR_DATA1, &rslt_msb, माप(rslt_lsb));
	अगर (ret)
		वापस ret;

	*data = (rslt_msb << 8) | rslt_lsb;

	अगर (*data == ADC5_USR_DATA_CHECK) अणु
		dev_err(adc->dev, "Invalid data:0x%x\n", *data);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(adc->dev, "voltage raw code:0x%x\n", *data);

	वापस 0;
पूर्ण

अटल पूर्णांक adc5_poll_रुको_eoc(काष्ठा adc5_chip *adc)
अणु
	अचिन्हित पूर्णांक count, retry = ADC5_CONV_TIME_RETRY;
	u8 status1;
	पूर्णांक ret;

	क्रम (count = 0; count < retry; count++) अणु
		ret = adc5_पढ़ो(adc, ADC5_USR_STATUS1, &status1,
							माप(status1));
		अगर (ret)
			वापस ret;

		status1 &= ADC5_USR_STATUS1_REQ_STS_EOC_MASK;
		अगर (status1 == ADC5_USR_STATUS1_EOC)
			वापस 0;

		usleep_range(ADC5_CONV_TIME_MIN_US, ADC5_CONV_TIME_MAX_US);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम adc5_update_dig_param(काष्ठा adc5_chip *adc,
			काष्ठा adc5_channel_prop *prop, u8 *data)
अणु
	/* Update calibration value */
	*data &= ~ADC5_USR_DIG_PARAM_CAL_VAL;
	*data |= (prop->cal_val << ADC5_USR_DIG_PARAM_CAL_VAL_SHIFT);

	/* Update calibration select */
	*data &= ~ADC5_USR_DIG_PARAM_CAL_SEL;
	*data |= (prop->cal_method << ADC5_USR_DIG_PARAM_CAL_SEL_SHIFT);

	/* Update decimation ratio select */
	*data &= ~ADC5_USR_DIG_PARAM_DEC_RATIO_SEL;
	*data |= (prop->decimation << ADC5_USR_DIG_PARAM_DEC_RATIO_SEL_SHIFT);
पूर्ण

अटल पूर्णांक adc5_configure(काष्ठा adc5_chip *adc,
			काष्ठा adc5_channel_prop *prop)
अणु
	पूर्णांक ret;
	u8 buf[6];

	/* Read रेजिस्टरs 0x42 through 0x46 */
	ret = adc5_पढ़ो(adc, ADC5_USR_DIG_PARAM, buf, माप(buf));
	अगर (ret)
		वापस ret;

	/* Digital param selection */
	adc5_update_dig_param(adc, prop, &buf[0]);

	/* Update fast average sample value */
	buf[1] &= (u8) ~ADC5_USR_FAST_AVG_CTL_SAMPLES_MASK;
	buf[1] |= prop->avg_samples;

	/* Select ADC channel */
	buf[2] = prop->channel;

	/* Select HW settle delay क्रम channel */
	buf[3] &= (u8) ~ADC5_USR_HW_SETTLE_DELAY_MASK;
	buf[3] |= prop->hw_settle_समय;

	/* Select ADC enable */
	buf[4] |= ADC5_USR_EN_CTL1_ADC_EN;

	/* Select CONV request */
	buf[5] |= ADC5_USR_CONV_REQ_REQ;

	अगर (!adc->poll_eoc)
		reinit_completion(&adc->complete);

	वापस adc5_ग_लिखो(adc, ADC5_USR_DIG_PARAM, buf, माप(buf));
पूर्ण

अटल पूर्णांक adc7_configure(काष्ठा adc5_chip *adc,
			काष्ठा adc5_channel_prop *prop)
अणु
	पूर्णांक ret;
	u8 conv_req = 0, buf[4];

	ret = adc5_masked_ग_लिखो(adc, ADC_APP_SID, ADC_APP_SID_MASK, prop->sid);
	अगर (ret)
		वापस ret;

	ret = adc5_पढ़ो(adc, ADC5_USR_DIG_PARAM, buf, माप(buf));
	अगर (ret)
		वापस ret;

	/* Digital param selection */
	adc5_update_dig_param(adc, prop, &buf[0]);

	/* Update fast average sample value */
	buf[1] &= ~ADC5_USR_FAST_AVG_CTL_SAMPLES_MASK;
	buf[1] |= prop->avg_samples;

	/* Select ADC channel */
	buf[2] = prop->channel;

	/* Select HW settle delay क्रम channel */
	buf[3] &= ~ADC5_USR_HW_SETTLE_DELAY_MASK;
	buf[3] |= prop->hw_settle_समय;

	/* Select CONV request */
	conv_req = ADC5_USR_CONV_REQ_REQ;

	अगर (!adc->poll_eoc)
		reinit_completion(&adc->complete);

	ret = adc5_ग_लिखो(adc, ADC5_USR_DIG_PARAM, buf, माप(buf));
	अगर (ret)
		वापस ret;

	वापस adc5_ग_लिखो(adc, ADC5_USR_CONV_REQ, &conv_req, 1);
पूर्ण

अटल पूर्णांक adc5_करो_conversion(काष्ठा adc5_chip *adc,
			काष्ठा adc5_channel_prop *prop,
			काष्ठा iio_chan_spec स्थिर *chan,
			u16 *data_volt, u16 *data_cur)
अणु
	पूर्णांक ret;

	mutex_lock(&adc->lock);

	ret = adc5_configure(adc, prop);
	अगर (ret) अणु
		dev_err(adc->dev, "ADC configure failed with %d\n", ret);
		जाओ unlock;
	पूर्ण

	अगर (adc->poll_eoc) अणु
		ret = adc5_poll_रुको_eoc(adc);
		अगर (ret) अणु
			dev_err(adc->dev, "EOC bit not set\n");
			जाओ unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = रुको_क्रम_completion_समयout(&adc->complete,
							ADC5_CONV_TIMEOUT);
		अगर (!ret) अणु
			dev_dbg(adc->dev, "Did not get completion timeout.\n");
			ret = adc5_poll_रुको_eoc(adc);
			अगर (ret) अणु
				dev_err(adc->dev, "EOC bit not set\n");
				जाओ unlock;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = adc5_पढ़ो_voltage_data(adc, data_volt);
unlock:
	mutex_unlock(&adc->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक adc7_करो_conversion(काष्ठा adc5_chip *adc,
			काष्ठा adc5_channel_prop *prop,
			काष्ठा iio_chan_spec स्थिर *chan,
			u16 *data_volt, u16 *data_cur)
अणु
	पूर्णांक ret;
	u8 status;

	mutex_lock(&adc->lock);

	ret = adc7_configure(adc, prop);
	अगर (ret) अणु
		dev_err(adc->dev, "ADC configure failed with %d\n", ret);
		जाओ unlock;
	पूर्ण

	/* No support क्रम polling mode at present */
	रुको_क्रम_completion_समयout(&adc->complete, ADC7_CONV_TIMEOUT);

	ret = adc5_पढ़ो(adc, ADC5_USR_STATUS1, &status, 1);
	अगर (ret)
		जाओ unlock;

	अगर (status & ADC5_USR_STATUS1_CONV_FAULT) अणु
		dev_err(adc->dev, "Unexpected conversion fault\n");
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	ret = adc5_पढ़ो_voltage_data(adc, data_volt);

unlock:
	mutex_unlock(&adc->lock);

	वापस ret;
पूर्ण

प्रकार पूर्णांक (*adc_करो_conversion)(काष्ठा adc5_chip *adc,
			काष्ठा adc5_channel_prop *prop,
			काष्ठा iio_chan_spec स्थिर *chan,
			u16 *data_volt, u16 *data_cur);

अटल irqवापस_t adc5_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा adc5_chip *adc = dev_id;

	complete(&adc->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adc5_of_xlate(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा of_phandle_args *iiospec)
अणु
	काष्ठा adc5_chip *adc = iio_priv(indio_dev);
	पूर्णांक i;

	क्रम (i = 0; i < adc->nchannels; i++)
		अगर (adc->chan_props[i].channel == iiospec->args[0])
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adc7_of_xlate(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा of_phandle_args *iiospec)
अणु
	काष्ठा adc5_chip *adc = iio_priv(indio_dev);
	पूर्णांक i, v_channel;

	क्रम (i = 0; i < adc->nchannels; i++) अणु
		v_channel = (adc->chan_props[i].sid << ADC_CHANNEL_OFFSET) |
			adc->chan_props[i].channel;
		अगर (v_channel == iiospec->args[0])
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adc_पढ़ो_raw_common(काष्ठा iio_dev *indio_dev,
			 काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2,
			 दीर्घ mask, adc_करो_conversion करो_conv)
अणु
	काष्ठा adc5_chip *adc = iio_priv(indio_dev);
	काष्ठा adc5_channel_prop *prop;
	u16 adc_code_volt, adc_code_cur;
	पूर्णांक ret;

	prop = &adc->chan_props[chan->address];

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		ret = करो_conv(adc, prop, chan,
					&adc_code_volt, &adc_code_cur);
		अगर (ret)
			वापस ret;

		ret = qcom_adc5_hw_scale(prop->scale_fn_type,
			prop->prescale,
			adc->data,
			adc_code_volt, val);
		अगर (ret)
			वापस ret;

		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक adc5_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			 काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2,
			 दीर्घ mask)
अणु
	वापस adc_पढ़ो_raw_common(indio_dev, chan, val, val2,
				mask, adc5_करो_conversion);
पूर्ण

अटल पूर्णांक adc7_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			 काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2,
			 दीर्घ mask)
अणु
	वापस adc_पढ़ो_raw_common(indio_dev, chan, val, val2,
				mask, adc7_करो_conversion);
पूर्ण

अटल स्थिर काष्ठा iio_info adc5_info = अणु
	.पढ़ो_raw = adc5_पढ़ो_raw,
	.of_xlate = adc5_of_xlate,
पूर्ण;

अटल स्थिर काष्ठा iio_info adc7_info = अणु
	.पढ़ो_raw = adc7_पढ़ो_raw,
	.of_xlate = adc7_of_xlate,
पूर्ण;

काष्ठा adc5_channels अणु
	स्थिर अक्षर *datasheet_name;
	अचिन्हित पूर्णांक prescale_index;
	क्रमागत iio_chan_type type;
	दीर्घ info_mask;
	क्रमागत vadc_scale_fn_type scale_fn_type;
पूर्ण;

/* In these definitions, _pre refers to an index पूर्णांकo adc5_prescale_ratios. */
#घोषणा ADC5_CHAN(_dname, _type, _mask, _pre, _scale)			\
	अणु								\
		.datasheet_name = _dname,				\
		.prescale_index = _pre,					\
		.type = _type,						\
		.info_mask = _mask,					\
		.scale_fn_type = _scale,				\
	पूर्ण,								\

#घोषणा ADC5_CHAN_TEMP(_dname, _pre, _scale)				\
	ADC5_CHAN(_dname, IIO_TEMP,					\
		BIT(IIO_CHAN_INFO_PROCESSED),				\
		_pre, _scale)						\

#घोषणा ADC5_CHAN_VOLT(_dname, _pre, _scale)				\
	ADC5_CHAN(_dname, IIO_VOLTAGE,					\
		  BIT(IIO_CHAN_INFO_PROCESSED),				\
		  _pre, _scale)						\

अटल स्थिर काष्ठा adc5_channels adc5_chans_pmic[ADC5_MAX_CHANNEL] = अणु
	[ADC5_REF_GND]		= ADC5_CHAN_VOLT("ref_gnd", 0,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_1P25VREF]		= ADC5_CHAN_VOLT("vref_1p25", 0,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_VPH_PWR]		= ADC5_CHAN_VOLT("vph_pwr", 1,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_VBAT_SNS]		= ADC5_CHAN_VOLT("vbat_sns", 1,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_DIE_TEMP]		= ADC5_CHAN_TEMP("die_temp", 0,
					SCALE_HW_CALIB_PMIC_THERM)
	[ADC5_USB_IN_I]		= ADC5_CHAN_VOLT("usb_in_i_uv", 0,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_USB_IN_V_16]	= ADC5_CHAN_VOLT("usb_in_v_div_16", 8,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_CHG_TEMP]		= ADC5_CHAN_TEMP("chg_temp", 0,
					SCALE_HW_CALIB_PM5_CHG_TEMP)
	/* Charger prescales SBUx and MID_CHG to fit within 1.8V upper unit */
	[ADC5_SBUx]		= ADC5_CHAN_VOLT("chg_sbux", 1,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_MID_CHG_DIV6]	= ADC5_CHAN_VOLT("chg_mid_chg", 3,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_XO_THERM_100K_PU]	= ADC5_CHAN_TEMP("xo_therm", 0,
					SCALE_HW_CALIB_XOTHERM)
	[ADC5_AMUX_THM1_100K_PU] = ADC5_CHAN_TEMP("amux_thm1_100k_pu", 0,
					SCALE_HW_CALIB_THERM_100K_PULLUP)
	[ADC5_AMUX_THM2_100K_PU] = ADC5_CHAN_TEMP("amux_thm2_100k_pu", 0,
					SCALE_HW_CALIB_THERM_100K_PULLUP)
	[ADC5_AMUX_THM3_100K_PU] = ADC5_CHAN_TEMP("amux_thm3_100k_pu", 0,
					SCALE_HW_CALIB_THERM_100K_PULLUP)
	[ADC5_AMUX_THM2]	= ADC5_CHAN_TEMP("amux_thm2", 0,
					SCALE_HW_CALIB_PM5_SMB_TEMP)
पूर्ण;

अटल स्थिर काष्ठा adc5_channels adc7_chans_pmic[ADC5_MAX_CHANNEL] = अणु
	[ADC7_REF_GND]		= ADC5_CHAN_VOLT("ref_gnd", 0,
					SCALE_HW_CALIB_DEFAULT)
	[ADC7_1P25VREF]		= ADC5_CHAN_VOLT("vref_1p25", 0,
					SCALE_HW_CALIB_DEFAULT)
	[ADC7_VPH_PWR]		= ADC5_CHAN_VOLT("vph_pwr", 1,
					SCALE_HW_CALIB_DEFAULT)
	[ADC7_VBAT_SNS]		= ADC5_CHAN_VOLT("vbat_sns", 3,
					SCALE_HW_CALIB_DEFAULT)
	[ADC7_DIE_TEMP]		= ADC5_CHAN_TEMP("die_temp", 0,
					SCALE_HW_CALIB_PMIC_THERM_PM7)
	[ADC7_AMUX_THM1_100K_PU] = ADC5_CHAN_TEMP("amux_thm1_pu2", 0,
					SCALE_HW_CALIB_THERM_100K_PU_PM7)
	[ADC7_AMUX_THM2_100K_PU] = ADC5_CHAN_TEMP("amux_thm2_pu2", 0,
					SCALE_HW_CALIB_THERM_100K_PU_PM7)
	[ADC7_AMUX_THM3_100K_PU] = ADC5_CHAN_TEMP("amux_thm3_pu2", 0,
					SCALE_HW_CALIB_THERM_100K_PU_PM7)
	[ADC7_AMUX_THM4_100K_PU] = ADC5_CHAN_TEMP("amux_thm4_pu2", 0,
					SCALE_HW_CALIB_THERM_100K_PU_PM7)
	[ADC7_AMUX_THM5_100K_PU] = ADC5_CHAN_TEMP("amux_thm5_pu2", 0,
					SCALE_HW_CALIB_THERM_100K_PU_PM7)
	[ADC7_AMUX_THM6_100K_PU] = ADC5_CHAN_TEMP("amux_thm6_pu2", 0,
					SCALE_HW_CALIB_THERM_100K_PU_PM7)
	[ADC7_GPIO1_100K_PU]	= ADC5_CHAN_TEMP("gpio1_pu2", 0,
					SCALE_HW_CALIB_THERM_100K_PU_PM7)
	[ADC7_GPIO2_100K_PU]	= ADC5_CHAN_TEMP("gpio2_pu2", 0,
					SCALE_HW_CALIB_THERM_100K_PU_PM7)
	[ADC7_GPIO3_100K_PU]	= ADC5_CHAN_TEMP("gpio3_pu2", 0,
					SCALE_HW_CALIB_THERM_100K_PU_PM7)
	[ADC7_GPIO4_100K_PU]	= ADC5_CHAN_TEMP("gpio4_pu2", 0,
					SCALE_HW_CALIB_THERM_100K_PU_PM7)
पूर्ण;

अटल स्थिर काष्ठा adc5_channels adc5_chans_rev2[ADC5_MAX_CHANNEL] = अणु
	[ADC5_REF_GND]		= ADC5_CHAN_VOLT("ref_gnd", 0,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_1P25VREF]		= ADC5_CHAN_VOLT("vref_1p25", 0,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_VPH_PWR]		= ADC5_CHAN_VOLT("vph_pwr", 1,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_VBAT_SNS]		= ADC5_CHAN_VOLT("vbat_sns", 1,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_VCOIN]		= ADC5_CHAN_VOLT("vcoin", 1,
					SCALE_HW_CALIB_DEFAULT)
	[ADC5_DIE_TEMP]		= ADC5_CHAN_TEMP("die_temp", 0,
					SCALE_HW_CALIB_PMIC_THERM)
	[ADC5_AMUX_THM1_100K_PU] = ADC5_CHAN_TEMP("amux_thm1_100k_pu", 0,
					SCALE_HW_CALIB_THERM_100K_PULLUP)
	[ADC5_AMUX_THM2_100K_PU] = ADC5_CHAN_TEMP("amux_thm2_100k_pu", 0,
					SCALE_HW_CALIB_THERM_100K_PULLUP)
	[ADC5_AMUX_THM3_100K_PU] = ADC5_CHAN_TEMP("amux_thm3_100k_pu", 0,
					SCALE_HW_CALIB_THERM_100K_PULLUP)
	[ADC5_AMUX_THM4_100K_PU] = ADC5_CHAN_TEMP("amux_thm4_100k_pu", 0,
					SCALE_HW_CALIB_THERM_100K_PULLUP)
	[ADC5_AMUX_THM5_100K_PU] = ADC5_CHAN_TEMP("amux_thm5_100k_pu", 0,
					SCALE_HW_CALIB_THERM_100K_PULLUP)
	[ADC5_XO_THERM_100K_PU]	= ADC5_CHAN_TEMP("xo_therm_100k_pu", 0,
					SCALE_HW_CALIB_THERM_100K_PULLUP)
पूर्ण;

अटल पूर्णांक adc5_get_dt_channel_data(काष्ठा adc5_chip *adc,
				    काष्ठा adc5_channel_prop *prop,
				    काष्ठा device_node *node,
				    स्थिर काष्ठा adc5_data *data)
अणु
	स्थिर अक्षर *name = node->name, *channel_name;
	u32 chan, value, varr[2];
	u32 sid = 0;
	पूर्णांक ret;
	काष्ठा device *dev = adc->dev;

	ret = of_property_पढ़ो_u32(node, "reg", &chan);
	अगर (ret) अणु
		dev_err(dev, "invalid channel number %s\n", name);
		वापस ret;
	पूर्ण

	/* Value पढ़ो from "reg" is भव channel number */

	/* भव channel number = sid << 8 | channel number */

	अगर (adc->data->info == &adc7_info) अणु
		sid = chan >> ADC_CHANNEL_OFFSET;
		chan = chan & ADC_CHANNEL_MASK;
	पूर्ण

	अगर (chan > ADC5_PARALLEL_ISENSE_VBAT_IDATA ||
	    !data->adc_chans[chan].datasheet_name) अणु
		dev_err(dev, "%s invalid channel number %d\n", name, chan);
		वापस -EINVAL;
	पूर्ण

	/* the channel has DT description */
	prop->channel = chan;
	prop->sid = sid;

	channel_name = of_get_property(node,
				"label", शून्य) ? : node->name;
	अगर (!channel_name) अणु
		dev_err(dev, "Invalid channel name\n");
		वापस -EINVAL;
	पूर्ण
	prop->datasheet_name = channel_name;

	ret = of_property_पढ़ो_u32(node, "qcom,decimation", &value);
	अगर (!ret) अणु
		ret = qcom_adc5_decimation_from_dt(value, data->decimation);
		अगर (ret < 0) अणु
			dev_err(dev, "%02x invalid decimation %d\n",
				chan, value);
			वापस ret;
		पूर्ण
		prop->decimation = ret;
	पूर्ण अन्यथा अणु
		prop->decimation = ADC5_DECIMATION_DEFAULT;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(node, "qcom,pre-scaling", varr, 2);
	अगर (!ret) अणु
		ret = qcom_adc5_prescaling_from_dt(varr[0], varr[1]);
		अगर (ret < 0) अणु
			dev_err(dev, "%02x invalid pre-scaling <%d %d>\n",
				chan, varr[0], varr[1]);
			वापस ret;
		पूर्ण
		prop->prescale = ret;
	पूर्ण अन्यथा अणु
		prop->prescale =
			adc->data->adc_chans[prop->channel].prescale_index;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "qcom,hw-settle-time", &value);
	अगर (!ret) अणु
		u8 dig_version[2];

		ret = adc5_पढ़ो(adc, ADC5_USR_REVISION1, dig_version,
							माप(dig_version));
		अगर (ret) अणु
			dev_err(dev, "Invalid dig version read %d\n", ret);
			वापस ret;
		पूर्ण

		dev_dbg(dev, "dig_ver:minor:%d, major:%d\n", dig_version[0],
						dig_version[1]);
		/* Digital controller >= 5.3 have hw_settle_2 option */
		अगर ((dig_version[0] >= ADC5_HW_SETTLE_DIFF_MINOR &&
			dig_version[1] >= ADC5_HW_SETTLE_DIFF_MAJOR) ||
			adc->data->info == &adc7_info)
			ret = qcom_adc5_hw_settle_समय_from_dt(value, data->hw_settle_2);
		अन्यथा
			ret = qcom_adc5_hw_settle_समय_from_dt(value, data->hw_settle_1);

		अगर (ret < 0) अणु
			dev_err(dev, "%02x invalid hw-settle-time %d us\n",
				chan, value);
			वापस ret;
		पूर्ण
		prop->hw_settle_समय = ret;
	पूर्ण अन्यथा अणु
		prop->hw_settle_समय = VADC_DEF_HW_SETTLE_TIME;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "qcom,avg-samples", &value);
	अगर (!ret) अणु
		ret = qcom_adc5_avg_samples_from_dt(value);
		अगर (ret < 0) अणु
			dev_err(dev, "%02x invalid avg-samples %d\n",
				chan, value);
			वापस ret;
		पूर्ण
		prop->avg_samples = ret;
	पूर्ण अन्यथा अणु
		prop->avg_samples = VADC_DEF_AVG_SAMPLES;
	पूर्ण

	अगर (of_property_पढ़ो_bool(node, "qcom,ratiometric"))
		prop->cal_method = ADC5_RATIOMETRIC_CAL;
	अन्यथा
		prop->cal_method = ADC5_ABSOLUTE_CAL;

	/*
	 * Default to using समयr calibration. Using a fresh calibration value
	 * क्रम every conversion will increase the overall समय क्रम a request.
	 */
	prop->cal_val = ADC5_TIMER_CAL;

	dev_dbg(dev, "%02x name %s\n", chan, name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा adc5_data adc5_data_pmic = अणु
	.full_scale_code_volt = 0x70e4,
	.full_scale_code_cur = 0x2710,
	.adc_chans = adc5_chans_pmic,
	.info = &adc5_info,
	.decimation = (अचिन्हित पूर्णांक [ADC5_DECIMATION_SAMPLES_MAX])
				अणु250, 420, 840पूर्ण,
	.hw_settle_1 = (अचिन्हित पूर्णांक [VADC_HW_SETTLE_SAMPLES_MAX])
				अणु15, 100, 200, 300, 400, 500, 600, 700,
				800, 900, 1, 2, 4, 6, 8, 10पूर्ण,
	.hw_settle_2 = (अचिन्हित पूर्णांक [VADC_HW_SETTLE_SAMPLES_MAX])
				अणु15, 100, 200, 300, 400, 500, 600, 700,
				1, 2, 4, 8, 16, 32, 64, 128पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा adc5_data adc7_data_pmic = अणु
	.full_scale_code_volt = 0x70e4,
	.adc_chans = adc7_chans_pmic,
	.info = &adc7_info,
	.decimation = (अचिन्हित पूर्णांक [ADC5_DECIMATION_SAMPLES_MAX])
				अणु85, 340, 1360पूर्ण,
	.hw_settle_2 = (अचिन्हित पूर्णांक [VADC_HW_SETTLE_SAMPLES_MAX])
				अणु15, 100, 200, 300, 400, 500, 600, 700,
				1000, 2000, 4000, 8000, 16000, 32000,
				64000, 128000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा adc5_data adc5_data_pmic_rev2 = अणु
	.full_scale_code_volt = 0x4000,
	.full_scale_code_cur = 0x1800,
	.adc_chans = adc5_chans_rev2,
	.info = &adc5_info,
	.decimation = (अचिन्हित पूर्णांक [ADC5_DECIMATION_SAMPLES_MAX])
				अणु256, 512, 1024पूर्ण,
	.hw_settle_1 = (अचिन्हित पूर्णांक [VADC_HW_SETTLE_SAMPLES_MAX])
				अणु0, 100, 200, 300, 400, 500, 600, 700,
				800, 900, 1, 2, 4, 6, 8, 10पूर्ण,
	.hw_settle_2 = (अचिन्हित पूर्णांक [VADC_HW_SETTLE_SAMPLES_MAX])
				अणु15, 100, 200, 300, 400, 500, 600, 700,
				1, 2, 4, 8, 16, 32, 64, 128पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id adc5_match_table[] = अणु
	अणु
		.compatible = "qcom,spmi-adc5",
		.data = &adc5_data_pmic,
	पूर्ण,
	अणु
		.compatible = "qcom,spmi-adc7",
		.data = &adc7_data_pmic,
	पूर्ण,
	अणु
		.compatible = "qcom,spmi-adc-rev2",
		.data = &adc5_data_pmic_rev2,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adc5_match_table);

अटल पूर्णांक adc5_get_dt_data(काष्ठा adc5_chip *adc, काष्ठा device_node *node)
अणु
	स्थिर काष्ठा adc5_channels *adc_chan;
	काष्ठा iio_chan_spec *iio_chan;
	काष्ठा adc5_channel_prop prop, *chan_props;
	काष्ठा device_node *child;
	अचिन्हित पूर्णांक index = 0;
	पूर्णांक ret;

	adc->nchannels = of_get_available_child_count(node);
	अगर (!adc->nchannels)
		वापस -EINVAL;

	adc->iio_chans = devm_kसुस्मृति(adc->dev, adc->nchannels,
				       माप(*adc->iio_chans), GFP_KERNEL);
	अगर (!adc->iio_chans)
		वापस -ENOMEM;

	adc->chan_props = devm_kसुस्मृति(adc->dev, adc->nchannels,
					माप(*adc->chan_props), GFP_KERNEL);
	अगर (!adc->chan_props)
		वापस -ENOMEM;

	chan_props = adc->chan_props;
	iio_chan = adc->iio_chans;
	adc->data = of_device_get_match_data(adc->dev);
	अगर (!adc->data)
		adc->data = &adc5_data_pmic;

	क्रम_each_available_child_of_node(node, child) अणु
		ret = adc5_get_dt_channel_data(adc, &prop, child, adc->data);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण

		prop.scale_fn_type =
			adc->data->adc_chans[prop.channel].scale_fn_type;
		*chan_props = prop;
		adc_chan = &adc->data->adc_chans[prop.channel];

		iio_chan->channel = prop.channel;
		iio_chan->datasheet_name = prop.datasheet_name;
		iio_chan->extend_name = prop.datasheet_name;
		iio_chan->info_mask_separate = adc_chan->info_mask;
		iio_chan->type = adc_chan->type;
		iio_chan->address = index;
		iio_chan++;
		chan_props++;
		index++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adc5_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा adc5_chip *adc;
	काष्ठा regmap *regmap;
	पूर्णांक ret, irq_eoc;
	u32 reg;

	regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!regmap)
		वापस -ENODEV;

	ret = of_property_पढ़ो_u32(node, "reg", &reg);
	अगर (ret < 0)
		वापस ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->regmap = regmap;
	adc->dev = dev;
	adc->base = reg;

	init_completion(&adc->complete);
	mutex_init(&adc->lock);

	ret = adc5_get_dt_data(adc, node);
	अगर (ret) अणु
		dev_err(dev, "adc get dt data failed\n");
		वापस ret;
	पूर्ण

	irq_eoc = platक्रमm_get_irq(pdev, 0);
	अगर (irq_eoc < 0) अणु
		अगर (irq_eoc == -EPROBE_DEFER || irq_eoc == -EINVAL)
			वापस irq_eoc;
		adc->poll_eoc = true;
	पूर्ण अन्यथा अणु
		ret = devm_request_irq(dev, irq_eoc, adc5_isr, 0,
				       "pm-adc5", adc);
		अगर (ret)
			वापस ret;
	पूर्ण

	indio_dev->name = pdev->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = adc->data->info;
	indio_dev->channels = adc->iio_chans;
	indio_dev->num_channels = adc->nchannels;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver adc5_driver = अणु
	.driver = अणु
		.name = "qcom-spmi-adc5",
		.of_match_table = adc5_match_table,
	पूर्ण,
	.probe = adc5_probe,
पूर्ण;
module_platक्रमm_driver(adc5_driver);

MODULE_ALIAS("platform:qcom-spmi-adc5");
MODULE_DESCRIPTION("Qualcomm Technologies Inc. PMIC5 ADC driver");
MODULE_LICENSE("GPL v2");
