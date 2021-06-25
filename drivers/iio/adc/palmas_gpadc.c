<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * palmas-adc.c -- TI PALMAS GPADC.
 *
 * Copyright (c) 2013, NVIDIA Corporation. All rights reserved.
 *
 * Author: Pradeep Goudagunta <pgoudagunta@nvidia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm.h>
#समावेश <linux/mfd/palmas.h>
#समावेश <linux/completion.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/machine.h>
#समावेश <linux/iio/driver.h>

#घोषणा MOD_NAME "palmas-gpadc"
#घोषणा PALMAS_ADC_CONVERSION_TIMEOUT	(msecs_to_jअगरfies(5000))
#घोषणा PALMAS_TO_BE_CALCULATED 0
#घोषणा PALMAS_GPADC_TRIMINVALID	-1

काष्ठा palmas_gpadc_info अणु
/* calibration codes and regs */
	पूर्णांक x1;	/* lower ideal code */
	पूर्णांक x2;	/* higher ideal code */
	पूर्णांक v1;	/* expected lower volt पढ़ोing */
	पूर्णांक v2;	/* expected higher volt पढ़ोing */
	u8 trim1_reg;	/* रेजिस्टर number क्रम lower trim */
	u8 trim2_reg;	/* रेजिस्टर number क्रम upper trim */
	पूर्णांक gain;	/* calculated from above (after पढ़ोing trim regs) */
	पूर्णांक offset;	/* calculated from above (after पढ़ोing trim regs) */
	पूर्णांक gain_error;	/* calculated from above (after पढ़ोing trim regs) */
	bool is_uncalibrated;	/* अगर channel has calibration data */
पूर्ण;

#घोषणा PALMAS_ADC_INFO(_chan, _x1, _x2, _v1, _v2, _t1, _t2, _is_uncalibrated) \
	[PALMAS_ADC_CH_##_chan] = अणु \
		.x1 = _x1, \
		.x2 = _x2, \
		.v1 = _v1, \
		.v2 = _v2, \
		.gain = PALMAS_TO_BE_CALCULATED, \
		.offset = PALMAS_TO_BE_CALCULATED, \
		.gain_error = PALMAS_TO_BE_CALCULATED, \
		.trim1_reg = PALMAS_GPADC_TRIM##_t1, \
		.trim2_reg = PALMAS_GPADC_TRIM##_t2,  \
		.is_uncalibrated = _is_uncalibrated \
	पूर्ण

अटल काष्ठा palmas_gpadc_info palmas_gpadc_info[] = अणु
	PALMAS_ADC_INFO(IN0, 2064, 3112, 630, 950, 1, 2, false),
	PALMAS_ADC_INFO(IN1, 2064, 3112, 630, 950, 1, 2, false),
	PALMAS_ADC_INFO(IN2, 2064, 3112, 1260, 1900, 3, 4, false),
	PALMAS_ADC_INFO(IN3, 2064, 3112, 630, 950, 1, 2, false),
	PALMAS_ADC_INFO(IN4, 2064, 3112, 630, 950, 1, 2, false),
	PALMAS_ADC_INFO(IN5, 2064, 3112, 630, 950, 1, 2, false),
	PALMAS_ADC_INFO(IN6, 2064, 3112, 2520, 3800, 5, 6, false),
	PALMAS_ADC_INFO(IN7, 2064, 3112, 2520, 3800, 7, 8, false),
	PALMAS_ADC_INFO(IN8, 2064, 3112, 3150, 4750, 9, 10, false),
	PALMAS_ADC_INFO(IN9, 2064, 3112, 5670, 8550, 11, 12, false),
	PALMAS_ADC_INFO(IN10, 2064, 3112, 3465, 5225, 13, 14, false),
	PALMAS_ADC_INFO(IN11, 0, 0, 0, 0, INVALID, INVALID, true),
	PALMAS_ADC_INFO(IN12, 0, 0, 0, 0, INVALID, INVALID, true),
	PALMAS_ADC_INFO(IN13, 0, 0, 0, 0, INVALID, INVALID, true),
	PALMAS_ADC_INFO(IN14, 2064, 3112, 3645, 5225, 15, 16, false),
	PALMAS_ADC_INFO(IN15, 0, 0, 0, 0, INVALID, INVALID, true),
पूर्ण;

/*
 * काष्ठा palmas_gpadc - the palmas_gpadc काष्ठाure
 * @ch0_current:	channel 0 current source setting
 *			0: 0 uA
 *			1: 5 uA
 *			2: 15 uA
 *			3: 20 uA
 * @ch3_current:	channel 0 current source setting
 *			0: 0 uA
 *			1: 10 uA
 *			2: 400 uA
 *			3: 800 uA
 * @extended_delay:	enable the gpadc extended delay mode
 * @स्वतः_conversion_period:	define the स्वतः_conversion_period
 * @lock:	Lock to protect the device state during a potential concurrent
 *		पढ़ो access from userspace. Reading a raw value requires a sequence
 *		of रेजिस्टर ग_लिखोs, then a रुको क्रम a completion callback,
 *		and finally a रेजिस्टर पढ़ो, during which userspace could issue
 *		another पढ़ो request. This lock protects a पढ़ो access from
 *		ocurring beक्रमe another one has finished.
 *
 * This is the palmas_gpadc काष्ठाure to store run-समय inक्रमmation
 * and poपूर्णांकers क्रम this driver instance.
 */
काष्ठा palmas_gpadc अणु
	काष्ठा device			*dev;
	काष्ठा palmas			*palmas;
	u8				ch0_current;
	u8				ch3_current;
	bool				extended_delay;
	पूर्णांक				irq;
	पूर्णांक				irq_स्वतः_0;
	पूर्णांक				irq_स्वतः_1;
	काष्ठा palmas_gpadc_info	*adc_info;
	काष्ठा completion		conv_completion;
	काष्ठा palmas_adc_wakeup_property wakeup1_data;
	काष्ठा palmas_adc_wakeup_property wakeup2_data;
	bool				wakeup1_enable;
	bool				wakeup2_enable;
	पूर्णांक				स्वतः_conversion_period;
	काष्ठा mutex			lock;
पूर्ण;

/*
 * GPADC lock issue in AUTO mode.
 * Impact: In AUTO mode, GPADC conversion can be locked after disabling AUTO
 *	   mode feature.
 * Details:
 *	When the AUTO mode is the only conversion mode enabled, अगर the AUTO
 *	mode feature is disabled with bit GPADC_AUTO_CTRL.  AUTO_CONV1_EN = 0
 *	or bit GPADC_AUTO_CTRL.  AUTO_CONV0_EN = 0 during a conversion, the
 *	conversion mechanism can be seen as locked meaning that all following
 *	conversion will give 0 as a result.  Bit GPADC_STATUS.GPADC_AVAILABLE
 *	will stay at 0 meaning that GPADC is busy.  An RT conversion can unlock
 *	the GPADC.
 *
 * Workaround(s):
 *	To aव्योम the lock mechanism, the workaround to follow beक्रमe any stop
 *	conversion request is:
 *	Force the GPADC state machine to be ON by using the GPADC_CTRL1.
 *		GPADC_FORCE bit = 1
 *	Shutकरोwn the GPADC AUTO conversion using
 *		GPADC_AUTO_CTRL.SHUTDOWN_CONV[01] = 0.
 *	After 100us, क्रमce the GPADC state machine to be OFF by using the
 *		GPADC_CTRL1.  GPADC_FORCE bit = 0
 */

अटल पूर्णांक palmas_disable_स्वतः_conversion(काष्ठा palmas_gpadc *adc)
अणु
	पूर्णांक ret;

	ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
			PALMAS_GPADC_CTRL1,
			PALMAS_GPADC_CTRL1_GPADC_FORCE,
			PALMAS_GPADC_CTRL1_GPADC_FORCE);
	अगर (ret < 0) अणु
		dev_err(adc->dev, "GPADC_CTRL1 update failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
			PALMAS_GPADC_AUTO_CTRL,
			PALMAS_GPADC_AUTO_CTRL_SHUTDOWN_CONV1 |
			PALMAS_GPADC_AUTO_CTRL_SHUTDOWN_CONV0,
			0);
	अगर (ret < 0) अणु
		dev_err(adc->dev, "AUTO_CTRL update failed: %d\n", ret);
		वापस ret;
	पूर्ण

	udelay(100);

	ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
			PALMAS_GPADC_CTRL1,
			PALMAS_GPADC_CTRL1_GPADC_FORCE, 0);
	अगर (ret < 0)
		dev_err(adc->dev, "GPADC_CTRL1 update failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल irqवापस_t palmas_gpadc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा palmas_gpadc *adc = data;

	complete(&adc->conv_completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t palmas_gpadc_irq_स्वतः(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा palmas_gpadc *adc = data;

	dev_dbg(adc->dev, "Threshold interrupt %d occurs\n", irq);
	palmas_disable_स्वतः_conversion(adc);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक palmas_gpadc_start_mask_पूर्णांकerrupt(काष्ठा palmas_gpadc *adc,
						bool mask)
अणु
	पूर्णांक ret;

	अगर (!mask)
		ret = palmas_update_bits(adc->palmas, PALMAS_INTERRUPT_BASE,
					PALMAS_INT3_MASK,
					PALMAS_INT3_MASK_GPADC_EOC_SW, 0);
	अन्यथा
		ret = palmas_update_bits(adc->palmas, PALMAS_INTERRUPT_BASE,
					PALMAS_INT3_MASK,
					PALMAS_INT3_MASK_GPADC_EOC_SW,
					PALMAS_INT3_MASK_GPADC_EOC_SW);
	अगर (ret < 0)
		dev_err(adc->dev, "GPADC INT MASK update failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक palmas_gpadc_enable(काष्ठा palmas_gpadc *adc, पूर्णांक adc_chan,
			       पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक mask, val;
	पूर्णांक ret;

	अगर (enable) अणु
		val = (adc->extended_delay
			<< PALMAS_GPADC_RT_CTRL_EXTEND_DELAY_SHIFT);
		ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
					PALMAS_GPADC_RT_CTRL,
					PALMAS_GPADC_RT_CTRL_EXTEND_DELAY, val);
		अगर (ret < 0) अणु
			dev_err(adc->dev, "RT_CTRL update failed: %d\n", ret);
			वापस ret;
		पूर्ण

		mask = (PALMAS_GPADC_CTRL1_CURRENT_SRC_CH0_MASK |
			PALMAS_GPADC_CTRL1_CURRENT_SRC_CH3_MASK |
			PALMAS_GPADC_CTRL1_GPADC_FORCE);
		val = (adc->ch0_current
			<< PALMAS_GPADC_CTRL1_CURRENT_SRC_CH0_SHIFT);
		val |= (adc->ch3_current
			<< PALMAS_GPADC_CTRL1_CURRENT_SRC_CH3_SHIFT);
		val |= PALMAS_GPADC_CTRL1_GPADC_FORCE;
		ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_CTRL1, mask, val);
		अगर (ret < 0) अणु
			dev_err(adc->dev,
				"Failed to update current setting: %d\n", ret);
			वापस ret;
		पूर्ण

		mask = (PALMAS_GPADC_SW_SELECT_SW_CONV0_SEL_MASK |
			PALMAS_GPADC_SW_SELECT_SW_CONV_EN);
		val = (adc_chan | PALMAS_GPADC_SW_SELECT_SW_CONV_EN);
		ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_SW_SELECT, mask, val);
		अगर (ret < 0) अणु
			dev_err(adc->dev, "SW_SELECT update failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = palmas_ग_लिखो(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_SW_SELECT, 0);
		अगर (ret < 0)
			dev_err(adc->dev, "SW_SELECT write failed: %d\n", ret);

		ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_CTRL1,
				PALMAS_GPADC_CTRL1_GPADC_FORCE, 0);
		अगर (ret < 0) अणु
			dev_err(adc->dev, "CTRL1 update failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक palmas_gpadc_पढ़ो_prepare(काष्ठा palmas_gpadc *adc, पूर्णांक adc_chan)
अणु
	पूर्णांक ret;

	ret = palmas_gpadc_enable(adc, adc_chan, true);
	अगर (ret < 0)
		वापस ret;

	वापस palmas_gpadc_start_mask_पूर्णांकerrupt(adc, 0);
पूर्ण

अटल व्योम palmas_gpadc_पढ़ो_करोne(काष्ठा palmas_gpadc *adc, पूर्णांक adc_chan)
अणु
	palmas_gpadc_start_mask_पूर्णांकerrupt(adc, 1);
	palmas_gpadc_enable(adc, adc_chan, false);
पूर्ण

अटल पूर्णांक palmas_gpadc_calibrate(काष्ठा palmas_gpadc *adc, पूर्णांक adc_chan)
अणु
	पूर्णांक k;
	पूर्णांक d1;
	पूर्णांक d2;
	पूर्णांक ret;
	पूर्णांक gain;
	पूर्णांक x1 =  adc->adc_info[adc_chan].x1;
	पूर्णांक x2 =  adc->adc_info[adc_chan].x2;
	पूर्णांक v1 = adc->adc_info[adc_chan].v1;
	पूर्णांक v2 = adc->adc_info[adc_chan].v2;

	ret = palmas_पढ़ो(adc->palmas, PALMAS_TRIM_GPADC_BASE,
				adc->adc_info[adc_chan].trim1_reg, &d1);
	अगर (ret < 0) अणु
		dev_err(adc->dev, "TRIM read failed: %d\n", ret);
		जाओ scrub;
	पूर्ण

	ret = palmas_पढ़ो(adc->palmas, PALMAS_TRIM_GPADC_BASE,
				adc->adc_info[adc_chan].trim2_reg, &d2);
	अगर (ret < 0) अणु
		dev_err(adc->dev, "TRIM read failed: %d\n", ret);
		जाओ scrub;
	पूर्ण

	/* gain error calculation */
	k = (1000 + (1000 * (d2 - d1)) / (x2 - x1));

	/* gain calculation */
	gain = ((v2 - v1) * 1000) / (x2 - x1);

	adc->adc_info[adc_chan].gain_error = k;
	adc->adc_info[adc_chan].gain = gain;
	/* offset Calculation */
	adc->adc_info[adc_chan].offset = (d1 * 1000) - ((k - 1000) * x1);

scrub:
	वापस ret;
पूर्ण

अटल पूर्णांक palmas_gpadc_start_conversion(काष्ठा palmas_gpadc *adc, पूर्णांक adc_chan)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	init_completion(&adc->conv_completion);
	ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_SW_SELECT,
				PALMAS_GPADC_SW_SELECT_SW_START_CONV0,
				PALMAS_GPADC_SW_SELECT_SW_START_CONV0);
	अगर (ret < 0) अणु
		dev_err(adc->dev, "SELECT_SW_START write failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&adc->conv_completion,
				PALMAS_ADC_CONVERSION_TIMEOUT);
	अगर (ret == 0) अणु
		dev_err(adc->dev, "conversion not completed\n");
		वापस -ETIMEDOUT;
	पूर्ण

	ret = palmas_bulk_पढ़ो(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_SW_CONV0_LSB, &val, 2);
	अगर (ret < 0) अणु
		dev_err(adc->dev, "SW_CONV0_LSB read failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = val & 0xFFF;

	वापस ret;
पूर्ण

अटल पूर्णांक palmas_gpadc_get_calibrated_code(काष्ठा palmas_gpadc *adc,
						पूर्णांक adc_chan, पूर्णांक val)
अणु
	अगर (!adc->adc_info[adc_chan].is_uncalibrated)
		val  = (val*1000 - adc->adc_info[adc_chan].offset) /
					adc->adc_info[adc_chan].gain_error;

	अगर (val < 0) अणु
		dev_err(adc->dev, "Mismatch with calibration\n");
		वापस 0;
	पूर्ण

	val = (val * adc->adc_info[adc_chan].gain) / 1000;

	वापस val;
पूर्ण

अटल पूर्णांक palmas_gpadc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा  palmas_gpadc *adc = iio_priv(indio_dev);
	पूर्णांक adc_chan = chan->channel;
	पूर्णांक ret = 0;

	अगर (adc_chan > PALMAS_ADC_CH_MAX)
		वापस -EINVAL;

	mutex_lock(&adc->lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED:
		ret = palmas_gpadc_पढ़ो_prepare(adc, adc_chan);
		अगर (ret < 0)
			जाओ out;

		ret = palmas_gpadc_start_conversion(adc, adc_chan);
		अगर (ret < 0) अणु
			dev_err(adc->dev,
			"ADC start conversion failed\n");
			जाओ out;
		पूर्ण

		अगर (mask == IIO_CHAN_INFO_PROCESSED)
			ret = palmas_gpadc_get_calibrated_code(
							adc, adc_chan, ret);

		*val = ret;

		ret = IIO_VAL_INT;
		जाओ out;
	पूर्ण

	mutex_unlock(&adc->lock);
	वापस ret;

out:
	palmas_gpadc_पढ़ो_करोne(adc, adc_chan);
	mutex_unlock(&adc->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info palmas_gpadc_iio_info = अणु
	.पढ़ो_raw = palmas_gpadc_पढ़ो_raw,
पूर्ण;

#घोषणा PALMAS_ADC_CHAN_IIO(chan, _type, chan_info)	\
अणु							\
	.datasheet_name = PALMAS_DATASHEET_NAME(chan),	\
	.type = _type,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	\
			BIT(chan_info),			\
	.indexed = 1,					\
	.channel = PALMAS_ADC_CH_##chan,		\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec palmas_gpadc_iio_channel[] = अणु
	PALMAS_ADC_CHAN_IIO(IN0, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	PALMAS_ADC_CHAN_IIO(IN1, IIO_TEMP, IIO_CHAN_INFO_RAW),
	PALMAS_ADC_CHAN_IIO(IN2, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	PALMAS_ADC_CHAN_IIO(IN3, IIO_TEMP, IIO_CHAN_INFO_RAW),
	PALMAS_ADC_CHAN_IIO(IN4, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	PALMAS_ADC_CHAN_IIO(IN5, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	PALMAS_ADC_CHAN_IIO(IN6, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	PALMAS_ADC_CHAN_IIO(IN7, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	PALMAS_ADC_CHAN_IIO(IN8, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	PALMAS_ADC_CHAN_IIO(IN9, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	PALMAS_ADC_CHAN_IIO(IN10, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	PALMAS_ADC_CHAN_IIO(IN11, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	PALMAS_ADC_CHAN_IIO(IN12, IIO_TEMP, IIO_CHAN_INFO_RAW),
	PALMAS_ADC_CHAN_IIO(IN13, IIO_TEMP, IIO_CHAN_INFO_RAW),
	PALMAS_ADC_CHAN_IIO(IN14, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
	PALMAS_ADC_CHAN_IIO(IN15, IIO_VOLTAGE, IIO_CHAN_INFO_PROCESSED),
पूर्ण;

अटल पूर्णांक palmas_gpadc_get_adc_dt_data(काष्ठा platक्रमm_device *pdev,
	काष्ठा palmas_gpadc_platक्रमm_data **gpadc_pdata)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा palmas_gpadc_platक्रमm_data *gp_data;
	पूर्णांक ret;
	u32 pval;

	gp_data = devm_kzalloc(&pdev->dev, माप(*gp_data), GFP_KERNEL);
	अगर (!gp_data)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32(np, "ti,channel0-current-microamp", &pval);
	अगर (!ret)
		gp_data->ch0_current = pval;

	ret = of_property_पढ़ो_u32(np, "ti,channel3-current-microamp", &pval);
	अगर (!ret)
		gp_data->ch3_current = pval;

	gp_data->extended_delay = of_property_पढ़ो_bool(np,
					"ti,enable-extended-delay");

	*gpadc_pdata = gp_data;

	वापस 0;
पूर्ण

अटल पूर्णांक palmas_gpadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा palmas_gpadc *adc;
	काष्ठा palmas_platक्रमm_data *pdata;
	काष्ठा palmas_gpadc_platक्रमm_data *gpadc_pdata = शून्य;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret, i;

	pdata = dev_get_platdata(pdev->dev.parent);

	अगर (pdata && pdata->gpadc_pdata)
		gpadc_pdata = pdata->gpadc_pdata;

	अगर (!gpadc_pdata && pdev->dev.of_node) अणु
		ret = palmas_gpadc_get_adc_dt_data(pdev, &gpadc_pdata);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	अगर (!gpadc_pdata)
		वापस -EINVAL;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*adc));
	अगर (!indio_dev) अणु
		dev_err(&pdev->dev, "iio_device_alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	adc = iio_priv(indio_dev);
	adc->dev = &pdev->dev;
	adc->palmas = dev_get_drvdata(pdev->dev.parent);
	adc->adc_info = palmas_gpadc_info;

	mutex_init(&adc->lock);

	init_completion(&adc->conv_completion);
	platक्रमm_set_drvdata(pdev, indio_dev);

	adc->स्वतः_conversion_period = gpadc_pdata->स्वतः_conversion_period_ms;
	adc->irq = palmas_irq_get_virq(adc->palmas, PALMAS_GPADC_EOC_SW_IRQ);
	अगर (adc->irq < 0) अणु
		dev_err(adc->dev,
			"get virq failed: %d\n", adc->irq);
		ret = adc->irq;
		जाओ out;
	पूर्ण
	ret = request_thपढ़ोed_irq(adc->irq, शून्य,
		palmas_gpadc_irq,
		IRQF_ONESHOT, dev_name(adc->dev),
		adc);
	अगर (ret < 0) अणु
		dev_err(adc->dev,
			"request irq %d failed: %d\n", adc->irq, ret);
		जाओ out;
	पूर्ण

	अगर (gpadc_pdata->adc_wakeup1_data) अणु
		स_नकल(&adc->wakeup1_data, gpadc_pdata->adc_wakeup1_data,
			माप(adc->wakeup1_data));
		adc->wakeup1_enable = true;
		adc->irq_स्वतः_0 =  platक्रमm_get_irq(pdev, 1);
		ret = request_thपढ़ोed_irq(adc->irq_स्वतः_0, शून्य,
				palmas_gpadc_irq_स्वतः,
				IRQF_ONESHOT,
				"palmas-adc-auto-0", adc);
		अगर (ret < 0) अणु
			dev_err(adc->dev, "request auto0 irq %d failed: %d\n",
				adc->irq_स्वतः_0, ret);
			जाओ out_irq_मुक्त;
		पूर्ण
	पूर्ण

	अगर (gpadc_pdata->adc_wakeup2_data) अणु
		स_नकल(&adc->wakeup2_data, gpadc_pdata->adc_wakeup2_data,
				माप(adc->wakeup2_data));
		adc->wakeup2_enable = true;
		adc->irq_स्वतः_1 =  platक्रमm_get_irq(pdev, 2);
		ret = request_thपढ़ोed_irq(adc->irq_स्वतः_1, शून्य,
				palmas_gpadc_irq_स्वतः,
				IRQF_ONESHOT,
				"palmas-adc-auto-1", adc);
		अगर (ret < 0) अणु
			dev_err(adc->dev, "request auto1 irq %d failed: %d\n",
				adc->irq_स्वतः_1, ret);
			जाओ out_irq_स्वतः0_मुक्त;
		पूर्ण
	पूर्ण

	/* set the current source 0 (value 0/5/15/20 uA => 0..3) */
	अगर (gpadc_pdata->ch0_current <= 1)
		adc->ch0_current = PALMAS_ADC_CH0_CURRENT_SRC_0;
	अन्यथा अगर (gpadc_pdata->ch0_current <= 5)
		adc->ch0_current = PALMAS_ADC_CH0_CURRENT_SRC_5;
	अन्यथा अगर (gpadc_pdata->ch0_current <= 15)
		adc->ch0_current = PALMAS_ADC_CH0_CURRENT_SRC_15;
	अन्यथा
		adc->ch0_current = PALMAS_ADC_CH0_CURRENT_SRC_20;

	/* set the current source 3 (value 0/10/400/800 uA => 0..3) */
	अगर (gpadc_pdata->ch3_current <= 1)
		adc->ch3_current = PALMAS_ADC_CH3_CURRENT_SRC_0;
	अन्यथा अगर (gpadc_pdata->ch3_current <= 10)
		adc->ch3_current = PALMAS_ADC_CH3_CURRENT_SRC_10;
	अन्यथा अगर (gpadc_pdata->ch3_current <= 400)
		adc->ch3_current = PALMAS_ADC_CH3_CURRENT_SRC_400;
	अन्यथा
		adc->ch3_current = PALMAS_ADC_CH3_CURRENT_SRC_800;

	adc->extended_delay = gpadc_pdata->extended_delay;

	indio_dev->name = MOD_NAME;
	indio_dev->info = &palmas_gpadc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = palmas_gpadc_iio_channel;
	indio_dev->num_channels = ARRAY_SIZE(palmas_gpadc_iio_channel);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(adc->dev, "iio_device_register() failed: %d\n", ret);
		जाओ out_irq_स्वतः1_मुक्त;
	पूर्ण

	device_set_wakeup_capable(&pdev->dev, 1);
	क्रम (i = 0; i < PALMAS_ADC_CH_MAX; i++) अणु
		अगर (!(adc->adc_info[i].is_uncalibrated))
			palmas_gpadc_calibrate(adc, i);
	पूर्ण

	अगर (adc->wakeup1_enable || adc->wakeup2_enable)
		device_wakeup_enable(&pdev->dev);

	वापस 0;

out_irq_स्वतः1_मुक्त:
	अगर (gpadc_pdata->adc_wakeup2_data)
		मुक्त_irq(adc->irq_स्वतः_1, adc);
out_irq_स्वतः0_मुक्त:
	अगर (gpadc_pdata->adc_wakeup1_data)
		मुक्त_irq(adc->irq_स्वतः_0, adc);
out_irq_मुक्त:
	मुक्त_irq(adc->irq, adc);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक palmas_gpadc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(&pdev->dev);
	काष्ठा palmas_gpadc *adc = iio_priv(indio_dev);

	अगर (adc->wakeup1_enable || adc->wakeup2_enable)
		device_wakeup_disable(&pdev->dev);
	iio_device_unरेजिस्टर(indio_dev);
	मुक्त_irq(adc->irq, adc);
	अगर (adc->wakeup1_enable)
		मुक्त_irq(adc->irq_स्वतः_0, adc);
	अगर (adc->wakeup2_enable)
		मुक्त_irq(adc->irq_स्वतः_1, adc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक palmas_adc_wakeup_configure(काष्ठा palmas_gpadc *adc)
अणु
	पूर्णांक adc_period, conv;
	पूर्णांक i;
	पूर्णांक ch0 = 0, ch1 = 0;
	पूर्णांक thres;
	पूर्णांक ret;

	adc_period = adc->स्वतः_conversion_period;
	क्रम (i = 0; i < 16; ++i) अणु
		अगर (((1000 * (1 << i)) / 32) < adc_period)
			जारी;
	पूर्ण
	अगर (i > 0)
		i--;
	adc_period = i;
	ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
			PALMAS_GPADC_AUTO_CTRL,
			PALMAS_GPADC_AUTO_CTRL_COUNTER_CONV_MASK,
			adc_period);
	अगर (ret < 0) अणु
		dev_err(adc->dev, "AUTO_CTRL write failed: %d\n", ret);
		वापस ret;
	पूर्ण

	conv = 0;
	अगर (adc->wakeup1_enable) अणु
		पूर्णांक polarity;

		ch0 = adc->wakeup1_data.adc_channel_number;
		conv |= PALMAS_GPADC_AUTO_CTRL_AUTO_CONV0_EN;
		अगर (adc->wakeup1_data.adc_high_threshold > 0) अणु
			thres = adc->wakeup1_data.adc_high_threshold;
			polarity = 0;
		पूर्ण अन्यथा अणु
			thres = adc->wakeup1_data.adc_low_threshold;
			polarity = PALMAS_GPADC_THRES_CONV0_MSB_THRES_CONV0_POL;
		पूर्ण

		ret = palmas_ग_लिखो(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_THRES_CONV0_LSB, thres & 0xFF);
		अगर (ret < 0) अणु
			dev_err(adc->dev,
				"THRES_CONV0_LSB write failed: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = palmas_ग_लिखो(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_THRES_CONV0_MSB,
				((thres >> 8) & 0xF) | polarity);
		अगर (ret < 0) अणु
			dev_err(adc->dev,
				"THRES_CONV0_MSB write failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (adc->wakeup2_enable) अणु
		पूर्णांक polarity;

		ch1 = adc->wakeup2_data.adc_channel_number;
		conv |= PALMAS_GPADC_AUTO_CTRL_AUTO_CONV1_EN;
		अगर (adc->wakeup2_data.adc_high_threshold > 0) अणु
			thres = adc->wakeup2_data.adc_high_threshold;
			polarity = 0;
		पूर्ण अन्यथा अणु
			thres = adc->wakeup2_data.adc_low_threshold;
			polarity = PALMAS_GPADC_THRES_CONV1_MSB_THRES_CONV1_POL;
		पूर्ण

		ret = palmas_ग_लिखो(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_THRES_CONV1_LSB, thres & 0xFF);
		अगर (ret < 0) अणु
			dev_err(adc->dev,
				"THRES_CONV1_LSB write failed: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = palmas_ग_लिखो(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_THRES_CONV1_MSB,
				((thres >> 8) & 0xF) | polarity);
		अगर (ret < 0) अणु
			dev_err(adc->dev,
				"THRES_CONV1_MSB write failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = palmas_ग_लिखो(adc->palmas, PALMAS_GPADC_BASE,
			PALMAS_GPADC_AUTO_SELECT, (ch1 << 4) | ch0);
	अगर (ret < 0) अणु
		dev_err(adc->dev, "AUTO_SELECT write failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
			PALMAS_GPADC_AUTO_CTRL,
			PALMAS_GPADC_AUTO_CTRL_AUTO_CONV1_EN |
			PALMAS_GPADC_AUTO_CTRL_AUTO_CONV0_EN, conv);
	अगर (ret < 0)
		dev_err(adc->dev, "AUTO_CTRL write failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक palmas_adc_wakeup_reset(काष्ठा palmas_gpadc *adc)
अणु
	पूर्णांक ret;

	ret = palmas_ग_लिखो(adc->palmas, PALMAS_GPADC_BASE,
			PALMAS_GPADC_AUTO_SELECT, 0);
	अगर (ret < 0) अणु
		dev_err(adc->dev, "AUTO_SELECT write failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = palmas_disable_स्वतः_conversion(adc);
	अगर (ret < 0)
		dev_err(adc->dev, "Disable auto conversion failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक palmas_gpadc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा palmas_gpadc *adc = iio_priv(indio_dev);
	पूर्णांक wakeup = adc->wakeup1_enable || adc->wakeup2_enable;
	पूर्णांक ret;

	अगर (!device_may_wakeup(dev) || !wakeup)
		वापस 0;

	ret = palmas_adc_wakeup_configure(adc);
	अगर (ret < 0)
		वापस ret;

	अगर (adc->wakeup1_enable)
		enable_irq_wake(adc->irq_स्वतः_0);

	अगर (adc->wakeup2_enable)
		enable_irq_wake(adc->irq_स्वतः_1);

	वापस 0;
पूर्ण

अटल पूर्णांक palmas_gpadc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा palmas_gpadc *adc = iio_priv(indio_dev);
	पूर्णांक wakeup = adc->wakeup1_enable || adc->wakeup2_enable;
	पूर्णांक ret;

	अगर (!device_may_wakeup(dev) || !wakeup)
		वापस 0;

	ret = palmas_adc_wakeup_reset(adc);
	अगर (ret < 0)
		वापस ret;

	अगर (adc->wakeup1_enable)
		disable_irq_wake(adc->irq_स्वतः_0);

	अगर (adc->wakeup2_enable)
		disable_irq_wake(adc->irq_स्वतः_1);

	वापस 0;
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops palmas_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(palmas_gpadc_suspend,
				palmas_gpadc_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_palmas_gpadc_match_tbl[] = अणु
	अणु .compatible = "ti,palmas-gpadc", पूर्ण,
	अणु /* end */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_palmas_gpadc_match_tbl);

अटल काष्ठा platक्रमm_driver palmas_gpadc_driver = अणु
	.probe = palmas_gpadc_probe,
	.हटाओ = palmas_gpadc_हटाओ,
	.driver = अणु
		.name = MOD_NAME,
		.pm = &palmas_pm_ops,
		.of_match_table = of_palmas_gpadc_match_tbl,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(palmas_gpadc_driver);

MODULE_DESCRIPTION("palmas GPADC driver");
MODULE_AUTHOR("Pradeep Goudagunta<pgoudagunta@nvidia.com>");
MODULE_ALIAS("platform:palmas-gpadc");
MODULE_LICENSE("GPL v2");
