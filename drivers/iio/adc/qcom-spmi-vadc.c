<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/iio/adc/qcom-vadc-common.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/log2.h>

#समावेश <dt-bindings/iio/qcom,spmi-vadc.h>

/* VADC रेजिस्टर and bit definitions */
#घोषणा VADC_REVISION2				0x1
#घोषणा VADC_REVISION2_SUPPORTED_VADC		1

#घोषणा VADC_PERPH_TYPE				0x4
#घोषणा VADC_PERPH_TYPE_ADC			8

#घोषणा VADC_PERPH_SUBTYPE			0x5
#घोषणा VADC_PERPH_SUBTYPE_VADC			1

#घोषणा VADC_STATUS1				0x8
#घोषणा VADC_STATUS1_OP_MODE			4
#घोषणा VADC_STATUS1_REQ_STS			BIT(1)
#घोषणा VADC_STATUS1_EOC			BIT(0)
#घोषणा VADC_STATUS1_REQ_STS_EOC_MASK		0x3

#घोषणा VADC_MODE_CTL				0x40
#घोषणा VADC_OP_MODE_SHIFT			3
#घोषणा VADC_OP_MODE_NORMAL			0
#घोषणा VADC_AMUX_TRIM_EN			BIT(1)
#घोषणा VADC_ADC_TRIM_EN			BIT(0)

#घोषणा VADC_EN_CTL1				0x46
#घोषणा VADC_EN_CTL1_SET			BIT(7)

#घोषणा VADC_ADC_CH_SEL_CTL			0x48

#घोषणा VADC_ADC_DIG_PARAM			0x50
#घोषणा VADC_ADC_DIG_DEC_RATIO_SEL_SHIFT	2

#घोषणा VADC_HW_SETTLE_DELAY			0x51

#घोषणा VADC_CONV_REQ				0x52
#घोषणा VADC_CONV_REQ_SET			BIT(7)

#घोषणा VADC_FAST_AVG_CTL			0x5a
#घोषणा VADC_FAST_AVG_EN			0x5b
#घोषणा VADC_FAST_AVG_EN_SET			BIT(7)

#घोषणा VADC_ACCESS				0xd0
#घोषणा VADC_ACCESS_DATA			0xa5

#घोषणा VADC_PERH_RESET_CTL3			0xda
#घोषणा VADC_FOLLOW_WARM_RB			BIT(2)

#घोषणा VADC_DATA				0x60	/* 16 bits */

#घोषणा VADC_CHAN_MIN			VADC_USBIN
#घोषणा VADC_CHAN_MAX			VADC_LR_MUX3_BUF_PU1_PU2_XO_THERM

/**
 * काष्ठा vadc_channel_prop - VADC channel property.
 * @channel: channel number, refer to the channel list.
 * @calibration: calibration type.
 * @decimation: sampling rate supported क्रम the channel.
 * @prescale: channel scaling perक्रमmed on the input संकेत.
 * @hw_settle_समय: the समय between AMUX being configured and the
 *	start of conversion.
 * @avg_samples: ability to provide single result from the ADC
 *	that is an average of multiple measurements.
 * @scale_fn_type: Represents the scaling function to convert voltage
 *	physical units desired by the client क्रम the channel.
 */
काष्ठा vadc_channel_prop अणु
	अचिन्हित पूर्णांक channel;
	क्रमागत vadc_calibration calibration;
	अचिन्हित पूर्णांक decimation;
	अचिन्हित पूर्णांक prescale;
	अचिन्हित पूर्णांक hw_settle_समय;
	अचिन्हित पूर्णांक avg_samples;
	क्रमागत vadc_scale_fn_type scale_fn_type;
पूर्ण;

/**
 * काष्ठा vadc_priv - VADC निजी काष्ठाure.
 * @regmap: poपूर्णांकer to काष्ठा regmap.
 * @dev: poपूर्णांकer to काष्ठा device.
 * @base: base address क्रम the ADC peripheral.
 * @nchannels: number of VADC channels.
 * @chan_props: array of VADC channel properties.
 * @iio_chans: array of IIO channels specअगरication.
 * @are_ref_measured: are reference poपूर्णांकs measured.
 * @poll_eoc: use polling instead of पूर्णांकerrupt.
 * @complete: VADC result notअगरication after पूर्णांकerrupt is received.
 * @graph: store parameters क्रम calibration.
 * @lock: ADC lock क्रम access to the peripheral.
 */
काष्ठा vadc_priv अणु
	काष्ठा regmap		 *regmap;
	काष्ठा device		 *dev;
	u16			 base;
	अचिन्हित पूर्णांक		 nchannels;
	काष्ठा vadc_channel_prop *chan_props;
	काष्ठा iio_chan_spec	 *iio_chans;
	bool			 are_ref_measured;
	bool			 poll_eoc;
	काष्ठा completion	 complete;
	काष्ठा vadc_linear_graph graph[2];
	काष्ठा mutex		 lock;
पूर्ण;

अटल स्थिर काष्ठा vadc_prescale_ratio vadc_prescale_ratios[] = अणु
	अणु.num =  1, .den =  1पूर्ण,
	अणु.num =  1, .den =  3पूर्ण,
	अणु.num =  1, .den =  4पूर्ण,
	अणु.num =  1, .den =  6पूर्ण,
	अणु.num =  1, .den = 20पूर्ण,
	अणु.num =  1, .den =  8पूर्ण,
	अणु.num = 10, .den = 81पूर्ण,
	अणु.num =  1, .den = 10पूर्ण
पूर्ण;

अटल पूर्णांक vadc_पढ़ो(काष्ठा vadc_priv *vadc, u16 offset, u8 *data)
अणु
	वापस regmap_bulk_पढ़ो(vadc->regmap, vadc->base + offset, data, 1);
पूर्ण

अटल पूर्णांक vadc_ग_लिखो(काष्ठा vadc_priv *vadc, u16 offset, u8 data)
अणु
	वापस regmap_ग_लिखो(vadc->regmap, vadc->base + offset, data);
पूर्ण

अटल पूर्णांक vadc_reset(काष्ठा vadc_priv *vadc)
अणु
	u8 data;
	पूर्णांक ret;

	ret = vadc_ग_लिखो(vadc, VADC_ACCESS, VADC_ACCESS_DATA);
	अगर (ret)
		वापस ret;

	ret = vadc_पढ़ो(vadc, VADC_PERH_RESET_CTL3, &data);
	अगर (ret)
		वापस ret;

	ret = vadc_ग_लिखो(vadc, VADC_ACCESS, VADC_ACCESS_DATA);
	अगर (ret)
		वापस ret;

	data |= VADC_FOLLOW_WARM_RB;

	वापस vadc_ग_लिखो(vadc, VADC_PERH_RESET_CTL3, data);
पूर्ण

अटल पूर्णांक vadc_set_state(काष्ठा vadc_priv *vadc, bool state)
अणु
	वापस vadc_ग_लिखो(vadc, VADC_EN_CTL1, state ? VADC_EN_CTL1_SET : 0);
पूर्ण

अटल व्योम vadc_show_status(काष्ठा vadc_priv *vadc)
अणु
	u8 mode, sta1, chan, dig, en, req;
	पूर्णांक ret;

	ret = vadc_पढ़ो(vadc, VADC_MODE_CTL, &mode);
	अगर (ret)
		वापस;

	ret = vadc_पढ़ो(vadc, VADC_ADC_DIG_PARAM, &dig);
	अगर (ret)
		वापस;

	ret = vadc_पढ़ो(vadc, VADC_ADC_CH_SEL_CTL, &chan);
	अगर (ret)
		वापस;

	ret = vadc_पढ़ो(vadc, VADC_CONV_REQ, &req);
	अगर (ret)
		वापस;

	ret = vadc_पढ़ो(vadc, VADC_STATUS1, &sta1);
	अगर (ret)
		वापस;

	ret = vadc_पढ़ो(vadc, VADC_EN_CTL1, &en);
	अगर (ret)
		वापस;

	dev_err(vadc->dev,
		"mode:%02x en:%02x chan:%02x dig:%02x req:%02x sta1:%02x\n",
		mode, en, chan, dig, req, sta1);
पूर्ण

अटल पूर्णांक vadc_configure(काष्ठा vadc_priv *vadc,
			  काष्ठा vadc_channel_prop *prop)
अणु
	u8 decimation, mode_ctrl;
	पूर्णांक ret;

	/* Mode selection */
	mode_ctrl = (VADC_OP_MODE_NORMAL << VADC_OP_MODE_SHIFT) |
		     VADC_ADC_TRIM_EN | VADC_AMUX_TRIM_EN;
	ret = vadc_ग_लिखो(vadc, VADC_MODE_CTL, mode_ctrl);
	अगर (ret)
		वापस ret;

	/* Channel selection */
	ret = vadc_ग_लिखो(vadc, VADC_ADC_CH_SEL_CTL, prop->channel);
	अगर (ret)
		वापस ret;

	/* Digital parameter setup */
	decimation = prop->decimation << VADC_ADC_DIG_DEC_RATIO_SEL_SHIFT;
	ret = vadc_ग_लिखो(vadc, VADC_ADC_DIG_PARAM, decimation);
	अगर (ret)
		वापस ret;

	/* HW settle समय delay */
	ret = vadc_ग_लिखो(vadc, VADC_HW_SETTLE_DELAY, prop->hw_settle_समय);
	अगर (ret)
		वापस ret;

	ret = vadc_ग_लिखो(vadc, VADC_FAST_AVG_CTL, prop->avg_samples);
	अगर (ret)
		वापस ret;

	अगर (prop->avg_samples)
		ret = vadc_ग_लिखो(vadc, VADC_FAST_AVG_EN, VADC_FAST_AVG_EN_SET);
	अन्यथा
		ret = vadc_ग_लिखो(vadc, VADC_FAST_AVG_EN, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक vadc_poll_रुको_eoc(काष्ठा vadc_priv *vadc, अचिन्हित पूर्णांक पूर्णांकerval_us)
अणु
	अचिन्हित पूर्णांक count, retry;
	u8 sta1;
	पूर्णांक ret;

	retry = पूर्णांकerval_us / VADC_CONV_TIME_MIN_US;

	क्रम (count = 0; count < retry; count++) अणु
		ret = vadc_पढ़ो(vadc, VADC_STATUS1, &sta1);
		अगर (ret)
			वापस ret;

		sta1 &= VADC_STATUS1_REQ_STS_EOC_MASK;
		अगर (sta1 == VADC_STATUS1_EOC)
			वापस 0;

		usleep_range(VADC_CONV_TIME_MIN_US, VADC_CONV_TIME_MAX_US);
	पूर्ण

	vadc_show_status(vadc);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक vadc_पढ़ो_result(काष्ठा vadc_priv *vadc, u16 *data)
अणु
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(vadc->regmap, vadc->base + VADC_DATA, data, 2);
	अगर (ret)
		वापस ret;

	*data = clamp_t(u16, *data, VADC_MIN_ADC_CODE, VADC_MAX_ADC_CODE);

	वापस 0;
पूर्ण

अटल काष्ठा vadc_channel_prop *vadc_get_channel(काष्ठा vadc_priv *vadc,
						  अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < vadc->nchannels; i++)
		अगर (vadc->chan_props[i].channel == num)
			वापस &vadc->chan_props[i];

	dev_dbg(vadc->dev, "no such channel %02x\n", num);

	वापस शून्य;
पूर्ण

अटल पूर्णांक vadc_करो_conversion(काष्ठा vadc_priv *vadc,
			      काष्ठा vadc_channel_prop *prop, u16 *data)
अणु
	अचिन्हित पूर्णांक समयout;
	पूर्णांक ret;

	mutex_lock(&vadc->lock);

	ret = vadc_configure(vadc, prop);
	अगर (ret)
		जाओ unlock;

	अगर (!vadc->poll_eoc)
		reinit_completion(&vadc->complete);

	ret = vadc_set_state(vadc, true);
	अगर (ret)
		जाओ unlock;

	ret = vadc_ग_लिखो(vadc, VADC_CONV_REQ, VADC_CONV_REQ_SET);
	अगर (ret)
		जाओ err_disable;

	समयout = BIT(prop->avg_samples) * VADC_CONV_TIME_MIN_US * 2;

	अगर (vadc->poll_eoc) अणु
		ret = vadc_poll_रुको_eoc(vadc, समयout);
	पूर्ण अन्यथा अणु
		ret = रुको_क्रम_completion_समयout(&vadc->complete, समयout);
		अगर (!ret) अणु
			ret = -ETIMEDOUT;
			जाओ err_disable;
		पूर्ण

		/* Double check conversion status */
		ret = vadc_poll_रुको_eoc(vadc, VADC_CONV_TIME_MIN_US);
		अगर (ret)
			जाओ err_disable;
	पूर्ण

	ret = vadc_पढ़ो_result(vadc, data);

err_disable:
	vadc_set_state(vadc, false);
	अगर (ret)
		dev_err(vadc->dev, "conversion failed\n");
unlock:
	mutex_unlock(&vadc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vadc_measure_ref_poपूर्णांकs(काष्ठा vadc_priv *vadc)
अणु
	काष्ठा vadc_channel_prop *prop;
	u16 पढ़ो_1, पढ़ो_2;
	पूर्णांक ret;

	vadc->graph[VADC_CALIB_RATIOMETRIC].dx = VADC_RATIOMETRIC_RANGE;
	vadc->graph[VADC_CALIB_ABSOLUTE].dx = VADC_ABSOLUTE_RANGE_UV;

	prop = vadc_get_channel(vadc, VADC_REF_1250MV);
	ret = vadc_करो_conversion(vadc, prop, &पढ़ो_1);
	अगर (ret)
		जाओ err;

	/* Try with buffered 625mV channel first */
	prop = vadc_get_channel(vadc, VADC_SPARE1);
	अगर (!prop)
		prop = vadc_get_channel(vadc, VADC_REF_625MV);

	ret = vadc_करो_conversion(vadc, prop, &पढ़ो_2);
	अगर (ret)
		जाओ err;

	अगर (पढ़ो_1 == पढ़ो_2) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	vadc->graph[VADC_CALIB_ABSOLUTE].dy = पढ़ो_1 - पढ़ो_2;
	vadc->graph[VADC_CALIB_ABSOLUTE].gnd = पढ़ो_2;

	/* Ratiometric calibration */
	prop = vadc_get_channel(vadc, VADC_VDD_VADC);
	ret = vadc_करो_conversion(vadc, prop, &पढ़ो_1);
	अगर (ret)
		जाओ err;

	prop = vadc_get_channel(vadc, VADC_GND_REF);
	ret = vadc_करो_conversion(vadc, prop, &पढ़ो_2);
	अगर (ret)
		जाओ err;

	अगर (पढ़ो_1 == पढ़ो_2) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	vadc->graph[VADC_CALIB_RATIOMETRIC].dy = पढ़ो_1 - पढ़ो_2;
	vadc->graph[VADC_CALIB_RATIOMETRIC].gnd = पढ़ो_2;
err:
	अगर (ret)
		dev_err(vadc->dev, "measure reference points failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक vadc_prescaling_from_dt(u32 num, u32 den)
अणु
	अचिन्हित पूर्णांक pre;

	क्रम (pre = 0; pre < ARRAY_SIZE(vadc_prescale_ratios); pre++)
		अगर (vadc_prescale_ratios[pre].num == num &&
		    vadc_prescale_ratios[pre].den == den)
			अवरोध;

	अगर (pre == ARRAY_SIZE(vadc_prescale_ratios))
		वापस -EINVAL;

	वापस pre;
पूर्ण

अटल पूर्णांक vadc_hw_settle_समय_from_dt(u32 value)
अणु
	अगर ((value <= 1000 && value % 100) || (value > 1000 && value % 2000))
		वापस -EINVAL;

	अगर (value <= 1000)
		value /= 100;
	अन्यथा
		value = value / 2000 + 10;

	वापस value;
पूर्ण

अटल पूर्णांक vadc_avg_samples_from_dt(u32 value)
अणु
	अगर (!is_घातer_of_2(value) || value > VADC_AVG_SAMPLES_MAX)
		वापस -EINVAL;

	वापस __ffs64(value);
पूर्ण

अटल पूर्णांक vadc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			 काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2,
			 दीर्घ mask)
अणु
	काष्ठा vadc_priv *vadc = iio_priv(indio_dev);
	काष्ठा vadc_channel_prop *prop;
	u16 adc_code;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		prop = &vadc->chan_props[chan->address];
		ret = vadc_करो_conversion(vadc, prop, &adc_code);
		अगर (ret)
			अवरोध;

		ret = qcom_vadc_scale(prop->scale_fn_type,
				&vadc->graph[prop->calibration],
				&vadc_prescale_ratios[prop->prescale],
				(prop->calibration == VADC_CALIB_ABSOLUTE),
				adc_code, val);
		अगर (ret)
			अवरोध;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_RAW:
		prop = &vadc->chan_props[chan->address];
		ret = vadc_करो_conversion(vadc, prop, &adc_code);
		अगर (ret)
			अवरोध;

		*val = (पूर्णांक)adc_code;
		वापस IIO_VAL_INT;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vadc_of_xlate(काष्ठा iio_dev *indio_dev,
			 स्थिर काष्ठा of_phandle_args *iiospec)
अणु
	काष्ठा vadc_priv *vadc = iio_priv(indio_dev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < vadc->nchannels; i++)
		अगर (vadc->iio_chans[i].channel == iiospec->args[0])
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info vadc_info = अणु
	.पढ़ो_raw = vadc_पढ़ो_raw,
	.of_xlate = vadc_of_xlate,
पूर्ण;

काष्ठा vadc_channels अणु
	स्थिर अक्षर *datasheet_name;
	अचिन्हित पूर्णांक prescale_index;
	क्रमागत iio_chan_type type;
	दीर्घ info_mask;
	क्रमागत vadc_scale_fn_type scale_fn_type;
पूर्ण;

#घोषणा VADC_CHAN(_dname, _type, _mask, _pre, _scale)			\
	[VADC_##_dname] = अणु						\
		.datasheet_name = __stringअगरy(_dname),			\
		.prescale_index = _pre,					\
		.type = _type,						\
		.info_mask = _mask,					\
		.scale_fn_type = _scale					\
	पूर्ण,								\

#घोषणा VADC_NO_CHAN(_dname, _type, _mask, _pre)			\
	[VADC_##_dname] = अणु						\
		.datasheet_name = __stringअगरy(_dname),			\
		.prescale_index = _pre,					\
		.type = _type,						\
		.info_mask = _mask					\
	पूर्ण,

#घोषणा VADC_CHAN_TEMP(_dname, _pre, _scale)				\
	VADC_CHAN(_dname, IIO_TEMP,					\
		BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_PROCESSED),	\
		_pre, _scale)						\

#घोषणा VADC_CHAN_VOLT(_dname, _pre, _scale)				\
	VADC_CHAN(_dname, IIO_VOLTAGE,					\
		  BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_PROCESSED),\
		  _pre, _scale)						\

#घोषणा VADC_CHAN_NO_SCALE(_dname, _pre)				\
	VADC_NO_CHAN(_dname, IIO_VOLTAGE,				\
		  BIT(IIO_CHAN_INFO_RAW),				\
		  _pre)							\

/*
 * The array represents all possible ADC channels found in the supported PMICs.
 * Every index in the array is equal to the channel number per datasheet. The
 * gaps in the array should be treated as reserved channels.
 */
अटल स्थिर काष्ठा vadc_channels vadc_chans[] = अणु
	VADC_CHAN_VOLT(USBIN, 4, SCALE_DEFAULT)
	VADC_CHAN_VOLT(DCIN, 4, SCALE_DEFAULT)
	VADC_CHAN_NO_SCALE(VCHG_SNS, 3)
	VADC_CHAN_NO_SCALE(SPARE1_03, 1)
	VADC_CHAN_NO_SCALE(USB_ID_MV, 1)
	VADC_CHAN_VOLT(VCOIN, 1, SCALE_DEFAULT)
	VADC_CHAN_NO_SCALE(VBAT_SNS, 1)
	VADC_CHAN_VOLT(VSYS, 1, SCALE_DEFAULT)
	VADC_CHAN_TEMP(DIE_TEMP, 0, SCALE_PMIC_THERM)
	VADC_CHAN_VOLT(REF_625MV, 0, SCALE_DEFAULT)
	VADC_CHAN_VOLT(REF_1250MV, 0, SCALE_DEFAULT)
	VADC_CHAN_NO_SCALE(CHG_TEMP, 0)
	VADC_CHAN_NO_SCALE(SPARE1, 0)
	VADC_CHAN_TEMP(SPARE2, 0, SCALE_PMI_CHG_TEMP)
	VADC_CHAN_VOLT(GND_REF, 0, SCALE_DEFAULT)
	VADC_CHAN_VOLT(VDD_VADC, 0, SCALE_DEFAULT)

	VADC_CHAN_NO_SCALE(P_MUX1_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX2_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX3_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX4_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX5_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX6_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX7_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX8_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX9_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX10_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX11_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX12_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX13_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX14_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX15_1_1, 0)
	VADC_CHAN_NO_SCALE(P_MUX16_1_1, 0)

	VADC_CHAN_NO_SCALE(P_MUX1_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX2_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX3_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX4_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX5_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX6_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX7_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX8_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX9_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX10_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX11_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX12_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX13_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX14_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX15_1_3, 1)
	VADC_CHAN_NO_SCALE(P_MUX16_1_3, 1)

	VADC_CHAN_NO_SCALE(LR_MUX1_BAT_THERM, 0)
	VADC_CHAN_VOLT(LR_MUX2_BAT_ID, 0, SCALE_DEFAULT)
	VADC_CHAN_NO_SCALE(LR_MUX3_XO_THERM, 0)
	VADC_CHAN_NO_SCALE(LR_MUX4_AMUX_THM1, 0)
	VADC_CHAN_NO_SCALE(LR_MUX5_AMUX_THM2, 0)
	VADC_CHAN_NO_SCALE(LR_MUX6_AMUX_THM3, 0)
	VADC_CHAN_NO_SCALE(LR_MUX7_HW_ID, 0)
	VADC_CHAN_NO_SCALE(LR_MUX8_AMUX_THM4, 0)
	VADC_CHAN_NO_SCALE(LR_MUX9_AMUX_THM5, 0)
	VADC_CHAN_NO_SCALE(LR_MUX10_USB_ID, 0)
	VADC_CHAN_NO_SCALE(AMUX_PU1, 0)
	VADC_CHAN_NO_SCALE(AMUX_PU2, 0)
	VADC_CHAN_NO_SCALE(LR_MUX3_BUF_XO_THERM, 0)

	VADC_CHAN_NO_SCALE(LR_MUX1_PU1_BAT_THERM, 0)
	VADC_CHAN_NO_SCALE(LR_MUX2_PU1_BAT_ID, 0)
	VADC_CHAN_NO_SCALE(LR_MUX3_PU1_XO_THERM, 0)
	VADC_CHAN_TEMP(LR_MUX4_PU1_AMUX_THM1, 0, SCALE_THERM_100K_PULLUP)
	VADC_CHAN_TEMP(LR_MUX5_PU1_AMUX_THM2, 0, SCALE_THERM_100K_PULLUP)
	VADC_CHAN_TEMP(LR_MUX6_PU1_AMUX_THM3, 0, SCALE_THERM_100K_PULLUP)
	VADC_CHAN_NO_SCALE(LR_MUX7_PU1_AMUX_HW_ID, 0)
	VADC_CHAN_TEMP(LR_MUX8_PU1_AMUX_THM4, 0, SCALE_THERM_100K_PULLUP)
	VADC_CHAN_TEMP(LR_MUX9_PU1_AMUX_THM5, 0, SCALE_THERM_100K_PULLUP)
	VADC_CHAN_NO_SCALE(LR_MUX10_PU1_AMUX_USB_ID, 0)
	VADC_CHAN_TEMP(LR_MUX3_BUF_PU1_XO_THERM, 0, SCALE_XOTHERM)

	VADC_CHAN_NO_SCALE(LR_MUX1_PU2_BAT_THERM, 0)
	VADC_CHAN_NO_SCALE(LR_MUX2_PU2_BAT_ID, 0)
	VADC_CHAN_NO_SCALE(LR_MUX3_PU2_XO_THERM, 0)
	VADC_CHAN_NO_SCALE(LR_MUX4_PU2_AMUX_THM1, 0)
	VADC_CHAN_NO_SCALE(LR_MUX5_PU2_AMUX_THM2, 0)
	VADC_CHAN_NO_SCALE(LR_MUX6_PU2_AMUX_THM3, 0)
	VADC_CHAN_NO_SCALE(LR_MUX7_PU2_AMUX_HW_ID, 0)
	VADC_CHAN_NO_SCALE(LR_MUX8_PU2_AMUX_THM4, 0)
	VADC_CHAN_NO_SCALE(LR_MUX9_PU2_AMUX_THM5, 0)
	VADC_CHAN_NO_SCALE(LR_MUX10_PU2_AMUX_USB_ID, 0)
	VADC_CHAN_NO_SCALE(LR_MUX3_BUF_PU2_XO_THERM, 0)

	VADC_CHAN_NO_SCALE(LR_MUX1_PU1_PU2_BAT_THERM, 0)
	VADC_CHAN_NO_SCALE(LR_MUX2_PU1_PU2_BAT_ID, 0)
	VADC_CHAN_NO_SCALE(LR_MUX3_PU1_PU2_XO_THERM, 0)
	VADC_CHAN_NO_SCALE(LR_MUX4_PU1_PU2_AMUX_THM1, 0)
	VADC_CHAN_NO_SCALE(LR_MUX5_PU1_PU2_AMUX_THM2, 0)
	VADC_CHAN_NO_SCALE(LR_MUX6_PU1_PU2_AMUX_THM3, 0)
	VADC_CHAN_NO_SCALE(LR_MUX7_PU1_PU2_AMUX_HW_ID, 0)
	VADC_CHAN_NO_SCALE(LR_MUX8_PU1_PU2_AMUX_THM4, 0)
	VADC_CHAN_NO_SCALE(LR_MUX9_PU1_PU2_AMUX_THM5, 0)
	VADC_CHAN_NO_SCALE(LR_MUX10_PU1_PU2_AMUX_USB_ID, 0)
	VADC_CHAN_NO_SCALE(LR_MUX3_BUF_PU1_PU2_XO_THERM, 0)
पूर्ण;

अटल पूर्णांक vadc_get_dt_channel_data(काष्ठा device *dev,
				    काष्ठा vadc_channel_prop *prop,
				    काष्ठा device_node *node)
अणु
	स्थिर अक्षर *name = node->name;
	u32 chan, value, varr[2];
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(node, "reg", &chan);
	अगर (ret) अणु
		dev_err(dev, "invalid channel number %s\n", name);
		वापस ret;
	पूर्ण

	अगर (chan > VADC_CHAN_MAX || chan < VADC_CHAN_MIN) अणु
		dev_err(dev, "%s invalid channel number %d\n", name, chan);
		वापस -EINVAL;
	पूर्ण

	/* the channel has DT description */
	prop->channel = chan;

	ret = of_property_पढ़ो_u32(node, "qcom,decimation", &value);
	अगर (!ret) अणु
		ret = qcom_vadc_decimation_from_dt(value);
		अगर (ret < 0) अणु
			dev_err(dev, "%02x invalid decimation %d\n",
				chan, value);
			वापस ret;
		पूर्ण
		prop->decimation = ret;
	पूर्ण अन्यथा अणु
		prop->decimation = VADC_DEF_DECIMATION;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(node, "qcom,pre-scaling", varr, 2);
	अगर (!ret) अणु
		ret = vadc_prescaling_from_dt(varr[0], varr[1]);
		अगर (ret < 0) अणु
			dev_err(dev, "%02x invalid pre-scaling <%d %d>\n",
				chan, varr[0], varr[1]);
			वापस ret;
		पूर्ण
		prop->prescale = ret;
	पूर्ण अन्यथा अणु
		prop->prescale = vadc_chans[prop->channel].prescale_index;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "qcom,hw-settle-time", &value);
	अगर (!ret) अणु
		ret = vadc_hw_settle_समय_from_dt(value);
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
		ret = vadc_avg_samples_from_dt(value);
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
		prop->calibration = VADC_CALIB_RATIOMETRIC;
	अन्यथा
		prop->calibration = VADC_CALIB_ABSOLUTE;

	dev_dbg(dev, "%02x name %s\n", chan, name);

	वापस 0;
पूर्ण

अटल पूर्णांक vadc_get_dt_data(काष्ठा vadc_priv *vadc, काष्ठा device_node *node)
अणु
	स्थिर काष्ठा vadc_channels *vadc_chan;
	काष्ठा iio_chan_spec *iio_chan;
	काष्ठा vadc_channel_prop prop;
	काष्ठा device_node *child;
	अचिन्हित पूर्णांक index = 0;
	पूर्णांक ret;

	vadc->nchannels = of_get_available_child_count(node);
	अगर (!vadc->nchannels)
		वापस -EINVAL;

	vadc->iio_chans = devm_kसुस्मृति(vadc->dev, vadc->nchannels,
				       माप(*vadc->iio_chans), GFP_KERNEL);
	अगर (!vadc->iio_chans)
		वापस -ENOMEM;

	vadc->chan_props = devm_kसुस्मृति(vadc->dev, vadc->nchannels,
					माप(*vadc->chan_props), GFP_KERNEL);
	अगर (!vadc->chan_props)
		वापस -ENOMEM;

	iio_chan = vadc->iio_chans;

	क्रम_each_available_child_of_node(node, child) अणु
		ret = vadc_get_dt_channel_data(vadc->dev, &prop, child);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण

		prop.scale_fn_type = vadc_chans[prop.channel].scale_fn_type;
		vadc->chan_props[index] = prop;

		vadc_chan = &vadc_chans[prop.channel];

		iio_chan->channel = prop.channel;
		iio_chan->datasheet_name = vadc_chan->datasheet_name;
		iio_chan->info_mask_separate = vadc_chan->info_mask;
		iio_chan->type = vadc_chan->type;
		iio_chan->indexed = 1;
		iio_chan->address = index++;

		iio_chan++;
	पूर्ण

	/* These channels are mandatory, they are used as reference poपूर्णांकs */
	अगर (!vadc_get_channel(vadc, VADC_REF_1250MV)) अणु
		dev_err(vadc->dev, "Please define 1.25V channel\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!vadc_get_channel(vadc, VADC_REF_625MV)) अणु
		dev_err(vadc->dev, "Please define 0.625V channel\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!vadc_get_channel(vadc, VADC_VDD_VADC)) अणु
		dev_err(vadc->dev, "Please define VDD channel\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!vadc_get_channel(vadc, VADC_GND_REF)) अणु
		dev_err(vadc->dev, "Please define GND channel\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t vadc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vadc_priv *vadc = dev_id;

	complete(&vadc->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vadc_check_revision(काष्ठा vadc_priv *vadc)
अणु
	u8 val;
	पूर्णांक ret;

	ret = vadc_पढ़ो(vadc, VADC_PERPH_TYPE, &val);
	अगर (ret)
		वापस ret;

	अगर (val < VADC_PERPH_TYPE_ADC) अणु
		dev_err(vadc->dev, "%d is not ADC\n", val);
		वापस -ENODEV;
	पूर्ण

	ret = vadc_पढ़ो(vadc, VADC_PERPH_SUBTYPE, &val);
	अगर (ret)
		वापस ret;

	अगर (val < VADC_PERPH_SUBTYPE_VADC) अणु
		dev_err(vadc->dev, "%d is not VADC\n", val);
		वापस -ENODEV;
	पूर्ण

	ret = vadc_पढ़ो(vadc, VADC_REVISION2, &val);
	अगर (ret)
		वापस ret;

	अगर (val < VADC_REVISION2_SUPPORTED_VADC) अणु
		dev_err(vadc->dev, "revision %d not supported\n", val);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा vadc_priv *vadc;
	काष्ठा regmap *regmap;
	पूर्णांक ret, irq_eoc;
	u32 reg;

	regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!regmap)
		वापस -ENODEV;

	ret = of_property_पढ़ो_u32(node, "reg", &reg);
	अगर (ret < 0)
		वापस ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*vadc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	vadc = iio_priv(indio_dev);
	vadc->regmap = regmap;
	vadc->dev = dev;
	vadc->base = reg;
	vadc->are_ref_measured = false;
	init_completion(&vadc->complete);
	mutex_init(&vadc->lock);

	ret = vadc_check_revision(vadc);
	अगर (ret)
		वापस ret;

	ret = vadc_get_dt_data(vadc, node);
	अगर (ret)
		वापस ret;

	irq_eoc = platक्रमm_get_irq(pdev, 0);
	अगर (irq_eoc < 0) अणु
		अगर (irq_eoc == -EPROBE_DEFER || irq_eoc == -EINVAL)
			वापस irq_eoc;
		vadc->poll_eoc = true;
	पूर्ण अन्यथा अणु
		ret = devm_request_irq(dev, irq_eoc, vadc_isr, 0,
				       "spmi-vadc", vadc);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = vadc_reset(vadc);
	अगर (ret) अणु
		dev_err(dev, "reset failed\n");
		वापस ret;
	पूर्ण

	ret = vadc_measure_ref_poपूर्णांकs(vadc);
	अगर (ret)
		वापस ret;

	indio_dev->name = pdev->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &vadc_info;
	indio_dev->channels = vadc->iio_chans;
	indio_dev->num_channels = vadc->nchannels;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id vadc_match_table[] = अणु
	अणु .compatible = "qcom,spmi-vadc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vadc_match_table);

अटल काष्ठा platक्रमm_driver vadc_driver = अणु
	.driver = अणु
		   .name = "qcom-spmi-vadc",
		   .of_match_table = vadc_match_table,
	पूर्ण,
	.probe = vadc_probe,
पूर्ण;
module_platक्रमm_driver(vadc_driver);

MODULE_ALIAS("platform:qcom-spmi-vadc");
MODULE_DESCRIPTION("Qualcomm SPMI PMIC voltage ADC driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Stanimir Varbanov <svarbanov@mm-sol.com>");
MODULE_AUTHOR("Ivan T. Ivanov <iivanov@mm-sol.com>");
