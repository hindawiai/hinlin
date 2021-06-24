<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Arun R Murthy <arun.murthy@stericsson.com>
 * Author: Daniel Willerud <daniel.willerud@stericsson.com>
 * Author: Johan Palsson <johan.palsson@stericsson.com>
 * Author: M'boumba Cedric Madianga
 * Author: Linus Walleij <linus.walleij@linaro.org>
 *
 * AB8500 General Purpose ADC driver. The AB8500 uses reference voltages:
 * VinVADC, and VADC relative to GND to करो its job. It monitors मुख्य and backup
 * battery voltages, AC (मुख्यs) voltage, USB cable voltage, as well as voltages
 * representing the temperature of the chip die and battery, accessory
 * detection by resistance measurements using relative voltages and GSM burst
 * inक्रमmation.
 *
 * Some of the voltages are measured on बाह्यal pins on the IC, such as
 * battery temperature or "ADC aux" 1 and 2. Other voltages are पूर्णांकernal rails
 * from other parts of the ASIC such as मुख्य अक्षरger voltage, मुख्य and battery
 * backup voltage or USB VBUS voltage. For this reason drivers क्रम other
 * parts of the प्रणाली are required to obtain handles to the ADC to करो work
 * क्रम them and the IIO driver provides arbitration among these consumers.
 */
#समावेश <linux/init.h>
#समावेश <linux/bits.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/completion.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>

/* GPADC रेजिस्टर offsets and bit definitions */

#घोषणा AB8500_GPADC_CTRL1_REG		0x00
/* GPADC control रेजिस्टर 1 bits */
#घोषणा AB8500_GPADC_CTRL1_DISABLE		0x00
#घोषणा AB8500_GPADC_CTRL1_ENABLE		BIT(0)
#घोषणा AB8500_GPADC_CTRL1_TRIG_ENA		BIT(1)
#घोषणा AB8500_GPADC_CTRL1_START_SW_CONV	BIT(2)
#घोषणा AB8500_GPADC_CTRL1_BTEMP_PULL_UP	BIT(3)
/* 0 = use rising edge, 1 = use falling edge */
#घोषणा AB8500_GPADC_CTRL1_TRIG_EDGE		BIT(4)
/* 0 = use VTVOUT, 1 = use VRTC as pull-up supply क्रम battery temp NTC */
#घोषणा AB8500_GPADC_CTRL1_PUPSUPSEL		BIT(5)
#घोषणा AB8500_GPADC_CTRL1_BUF_ENA		BIT(6)
#घोषणा AB8500_GPADC_CTRL1_ICHAR_ENA		BIT(7)

#घोषणा AB8500_GPADC_CTRL2_REG		0x01
#घोषणा AB8500_GPADC_CTRL3_REG		0x02
/*
 * GPADC control रेजिस्टर 2 and 3 bits
 * the bit layout is the same क्रम SW and HW conversion set-up
 */
#घोषणा AB8500_GPADC_CTRL2_AVG_1		0x00
#घोषणा AB8500_GPADC_CTRL2_AVG_4		BIT(5)
#घोषणा AB8500_GPADC_CTRL2_AVG_8		BIT(6)
#घोषणा AB8500_GPADC_CTRL2_AVG_16		(BIT(5) | BIT(6))

क्रमागत ab8500_gpadc_channel अणु
	AB8500_GPADC_CHAN_UNUSED = 0x00,
	AB8500_GPADC_CHAN_BAT_CTRL = 0x01,
	AB8500_GPADC_CHAN_BAT_TEMP = 0x02,
	/* This is not used on AB8505 */
	AB8500_GPADC_CHAN_MAIN_CHARGER = 0x03,
	AB8500_GPADC_CHAN_ACC_DET_1 = 0x04,
	AB8500_GPADC_CHAN_ACC_DET_2 = 0x05,
	AB8500_GPADC_CHAN_ADC_AUX_1 = 0x06,
	AB8500_GPADC_CHAN_ADC_AUX_2 = 0x07,
	AB8500_GPADC_CHAN_VBAT_A = 0x08,
	AB8500_GPADC_CHAN_VBUS = 0x09,
	AB8500_GPADC_CHAN_MAIN_CHARGER_CURRENT = 0x0a,
	AB8500_GPADC_CHAN_USB_CHARGER_CURRENT = 0x0b,
	AB8500_GPADC_CHAN_BACKUP_BAT = 0x0c,
	/* Only on AB8505 */
	AB8505_GPADC_CHAN_DIE_TEMP = 0x0d,
	AB8500_GPADC_CHAN_ID = 0x0e,
	AB8500_GPADC_CHAN_INTERNAL_TEST_1 = 0x0f,
	AB8500_GPADC_CHAN_INTERNAL_TEST_2 = 0x10,
	AB8500_GPADC_CHAN_INTERNAL_TEST_3 = 0x11,
	/* FIXME: Applicable to all ASIC variants? */
	AB8500_GPADC_CHAN_XTAL_TEMP = 0x12,
	AB8500_GPADC_CHAN_VBAT_TRUE_MEAS = 0x13,
	/* FIXME: Doesn't seem to work with pure AB8500 */
	AB8500_GPADC_CHAN_BAT_CTRL_AND_IBAT = 0x1c,
	AB8500_GPADC_CHAN_VBAT_MEAS_AND_IBAT = 0x1d,
	AB8500_GPADC_CHAN_VBAT_TRUE_MEAS_AND_IBAT = 0x1e,
	AB8500_GPADC_CHAN_BAT_TEMP_AND_IBAT = 0x1f,
	/*
	 * Virtual channel used only क्रम ibat conversion to ampere.
	 * Battery current conversion (ibat) cannot be requested as a
	 * single conversion but it is always requested in combination
	 * with other input requests.
	 */
	AB8500_GPADC_CHAN_IBAT_VIRTUAL = 0xFF,
पूर्ण;

#घोषणा AB8500_GPADC_AUTO_TIMER_REG	0x03

#घोषणा AB8500_GPADC_STAT_REG		0x04
#घोषणा AB8500_GPADC_STAT_BUSY		BIT(0)

#घोषणा AB8500_GPADC_MANDATAL_REG	0x05
#घोषणा AB8500_GPADC_MANDATAH_REG	0x06
#घोषणा AB8500_GPADC_AUTODATAL_REG	0x07
#घोषणा AB8500_GPADC_AUTODATAH_REG	0x08
#घोषणा AB8500_GPADC_MUX_CTRL_REG	0x09
#घोषणा AB8540_GPADC_MANDATA2L_REG	0x09
#घोषणा AB8540_GPADC_MANDATA2H_REG	0x0A
#घोषणा AB8540_GPADC_APEAAX_REG		0x10
#घोषणा AB8540_GPADC_APEAAT_REG		0x11
#घोषणा AB8540_GPADC_APEAAM_REG		0x12
#घोषणा AB8540_GPADC_APEAAH_REG		0x13
#घोषणा AB8540_GPADC_APEAAL_REG		0x14

/*
 * OTP रेजिस्टर offsets
 * Bank : 0x15
 */
#घोषणा AB8500_GPADC_CAL_1	0x0F
#घोषणा AB8500_GPADC_CAL_2	0x10
#घोषणा AB8500_GPADC_CAL_3	0x11
#घोषणा AB8500_GPADC_CAL_4	0x12
#घोषणा AB8500_GPADC_CAL_5	0x13
#घोषणा AB8500_GPADC_CAL_6	0x14
#घोषणा AB8500_GPADC_CAL_7	0x15
/* New calibration क्रम 8540 */
#घोषणा AB8540_GPADC_OTP4_REG_7	0x38
#घोषणा AB8540_GPADC_OTP4_REG_6	0x39
#घोषणा AB8540_GPADC_OTP4_REG_5	0x3A

#घोषणा AB8540_GPADC_DIS_ZERO	0x00
#घोषणा AB8540_GPADC_EN_VBIAS_XTAL_TEMP	0x02

/* GPADC स्थिरants from AB8500 spec, UM0836 */
#घोषणा AB8500_ADC_RESOLUTION		1024
#घोषणा AB8500_ADC_CH_BTEMP_MIN		0
#घोषणा AB8500_ADC_CH_BTEMP_MAX		1350
#घोषणा AB8500_ADC_CH_DIETEMP_MIN	0
#घोषणा AB8500_ADC_CH_DIETEMP_MAX	1350
#घोषणा AB8500_ADC_CH_CHG_V_MIN		0
#घोषणा AB8500_ADC_CH_CHG_V_MAX		20030
#घोषणा AB8500_ADC_CH_ACCDET2_MIN	0
#घोषणा AB8500_ADC_CH_ACCDET2_MAX	2500
#घोषणा AB8500_ADC_CH_VBAT_MIN		2300
#घोषणा AB8500_ADC_CH_VBAT_MAX		4800
#घोषणा AB8500_ADC_CH_CHG_I_MIN		0
#घोषणा AB8500_ADC_CH_CHG_I_MAX		1500
#घोषणा AB8500_ADC_CH_BKBAT_MIN		0
#घोषणा AB8500_ADC_CH_BKBAT_MAX		3200

/* GPADC स्थिरants from AB8540 spec */
#घोषणा AB8500_ADC_CH_IBAT_MIN		(-6000) /* mA range measured by ADC क्रम ibat */
#घोषणा AB8500_ADC_CH_IBAT_MAX		6000
#घोषणा AB8500_ADC_CH_IBAT_MIN_V	(-60)	/* mV range measured by ADC क्रम ibat */
#घोषणा AB8500_ADC_CH_IBAT_MAX_V	60
#घोषणा AB8500_GPADC_IBAT_VDROP_L	(-56)  /* mV */
#घोषणा AB8500_GPADC_IBAT_VDROP_H	56

/* This is used to not lose precision when भागiding to get gain and offset */
#घोषणा AB8500_GPADC_CALIB_SCALE	1000
/*
 * Number of bits shअगरt used to not lose precision
 * when भागiding to get ibat gain.
 */
#घोषणा AB8500_GPADC_CALIB_SHIFT_IBAT	20

/* Time in ms beक्रमe disabling regulator */
#घोषणा AB8500_GPADC_AUTOSUSPEND_DELAY	1

#घोषणा AB8500_GPADC_CONVERSION_TIME	500 /* ms */

क्रमागत ab8500_cal_channels अणु
	AB8500_CAL_VMAIN = 0,
	AB8500_CAL_BTEMP,
	AB8500_CAL_VBAT,
	AB8500_CAL_IBAT,
	AB8500_CAL_NR,
पूर्ण;

/**
 * काष्ठा ab8500_adc_cal_data - Table क्रम storing gain and offset क्रम the
 * calibrated ADC channels
 * @gain: Gain of the ADC channel
 * @offset: Offset of the ADC channel
 * @otp_calib_hi: Calibration from OTP
 * @otp_calib_lo: Calibration from OTP
 */
काष्ठा ab8500_adc_cal_data अणु
	s64 gain;
	s64 offset;
	u16 otp_calib_hi;
	u16 otp_calib_lo;
पूर्ण;

/**
 * काष्ठा ab8500_gpadc_chan_info - per-channel GPADC info
 * @name: name of the channel
 * @id: the पूर्णांकernal AB8500 ID number क्रम the channel
 * @hardware_control: indicate that we want to use hardware ADC control
 * on this channel, the शेष is software ADC control. Hardware control
 * is normally only used to test the battery voltage during GSM bursts
 * and needs a hardware trigger on the GPADCTrig pin of the ASIC.
 * @falling_edge: indicate that we want to trigger on falling edge
 * rather than rising edge, rising edge is the शेष
 * @avg_sample: how many samples to average: must be 1, 4, 8 or 16.
 * @trig_समयr: how दीर्घ to रुको क्रम the trigger, in 32kHz periods:
 * 0 .. 255 periods
 */
काष्ठा ab8500_gpadc_chan_info अणु
	स्थिर अक्षर *name;
	u8 id;
	bool hardware_control;
	bool falling_edge;
	u8 avg_sample;
	u8 trig_समयr;
पूर्ण;

/**
 * काष्ठा ab8500_gpadc - AB8500 GPADC device inक्रमmation
 * @dev: poपूर्णांकer to the containing device
 * @ab8500: poपूर्णांकer to the parent AB8500 device
 * @chans: पूर्णांकernal per-channel inक्रमmation container
 * @nchans: number of channels
 * @complete: poपूर्णांकer to the completion that indicates
 * the completion of an gpadc conversion cycle
 * @vddadc: poपूर्णांकer to the regulator supplying VDDADC
 * @irq_sw: पूर्णांकerrupt number that is used by gpadc क्रम software ADC conversion
 * @irq_hw: पूर्णांकerrupt number that is used by gpadc क्रम hardware ADC conversion
 * @cal_data: array of ADC calibration data काष्ठाs
 */
काष्ठा ab8500_gpadc अणु
	काष्ठा device *dev;
	काष्ठा ab8500 *ab8500;
	काष्ठा ab8500_gpadc_chan_info *chans;
	अचिन्हित पूर्णांक nchans;
	काष्ठा completion complete;
	काष्ठा regulator *vddadc;
	पूर्णांक irq_sw;
	पूर्णांक irq_hw;
	काष्ठा ab8500_adc_cal_data cal_data[AB8500_CAL_NR];
पूर्ण;

अटल काष्ठा ab8500_gpadc_chan_info *
ab8500_gpadc_get_channel(काष्ठा ab8500_gpadc *gpadc, u8 chan)
अणु
	काष्ठा ab8500_gpadc_chan_info *ch;
	पूर्णांक i;

	क्रम (i = 0; i < gpadc->nchans; i++) अणु
		ch = &gpadc->chans[i];
		अगर (ch->id == chan)
			अवरोध;
	पूर्ण
	अगर (i == gpadc->nchans)
		वापस शून्य;

	वापस ch;
पूर्ण

/**
 * ab8500_gpadc_ad_to_voltage() - Convert a raw ADC value to a voltage
 * @gpadc: GPADC instance
 * @ch: the sampled channel this raw value is coming from
 * @ad_value: the raw value
 */
अटल पूर्णांक ab8500_gpadc_ad_to_voltage(काष्ठा ab8500_gpadc *gpadc,
				      क्रमागत ab8500_gpadc_channel ch,
				      पूर्णांक ad_value)
अणु
	पूर्णांक res;

	चयन (ch) अणु
	हाल AB8500_GPADC_CHAN_MAIN_CHARGER:
		/* No calibration data available: just पूर्णांकerpolate */
		अगर (!gpadc->cal_data[AB8500_CAL_VMAIN].gain) अणु
			res = AB8500_ADC_CH_CHG_V_MIN + (AB8500_ADC_CH_CHG_V_MAX -
				AB8500_ADC_CH_CHG_V_MIN) * ad_value /
				AB8500_ADC_RESOLUTION;
			अवरोध;
		पूर्ण
		/* Here we can use calibration */
		res = (पूर्णांक) (ad_value * gpadc->cal_data[AB8500_CAL_VMAIN].gain +
			gpadc->cal_data[AB8500_CAL_VMAIN].offset) / AB8500_GPADC_CALIB_SCALE;
		अवरोध;

	हाल AB8500_GPADC_CHAN_BAT_CTRL:
	हाल AB8500_GPADC_CHAN_BAT_TEMP:
	हाल AB8500_GPADC_CHAN_ACC_DET_1:
	हाल AB8500_GPADC_CHAN_ADC_AUX_1:
	हाल AB8500_GPADC_CHAN_ADC_AUX_2:
	हाल AB8500_GPADC_CHAN_XTAL_TEMP:
		/* No calibration data available: just पूर्णांकerpolate */
		अगर (!gpadc->cal_data[AB8500_CAL_BTEMP].gain) अणु
			res = AB8500_ADC_CH_BTEMP_MIN + (AB8500_ADC_CH_BTEMP_MAX -
				AB8500_ADC_CH_BTEMP_MIN) * ad_value /
				AB8500_ADC_RESOLUTION;
			अवरोध;
		पूर्ण
		/* Here we can use calibration */
		res = (पूर्णांक) (ad_value * gpadc->cal_data[AB8500_CAL_BTEMP].gain +
			gpadc->cal_data[AB8500_CAL_BTEMP].offset) / AB8500_GPADC_CALIB_SCALE;
		अवरोध;

	हाल AB8500_GPADC_CHAN_VBAT_A:
	हाल AB8500_GPADC_CHAN_VBAT_TRUE_MEAS:
		/* No calibration data available: just पूर्णांकerpolate */
		अगर (!gpadc->cal_data[AB8500_CAL_VBAT].gain) अणु
			res = AB8500_ADC_CH_VBAT_MIN + (AB8500_ADC_CH_VBAT_MAX -
				AB8500_ADC_CH_VBAT_MIN) * ad_value /
				AB8500_ADC_RESOLUTION;
			अवरोध;
		पूर्ण
		/* Here we can use calibration */
		res = (पूर्णांक) (ad_value * gpadc->cal_data[AB8500_CAL_VBAT].gain +
			gpadc->cal_data[AB8500_CAL_VBAT].offset) / AB8500_GPADC_CALIB_SCALE;
		अवरोध;

	हाल AB8505_GPADC_CHAN_DIE_TEMP:
		res = AB8500_ADC_CH_DIETEMP_MIN +
			(AB8500_ADC_CH_DIETEMP_MAX - AB8500_ADC_CH_DIETEMP_MIN) * ad_value /
			AB8500_ADC_RESOLUTION;
		अवरोध;

	हाल AB8500_GPADC_CHAN_ACC_DET_2:
		res = AB8500_ADC_CH_ACCDET2_MIN +
			(AB8500_ADC_CH_ACCDET2_MAX - AB8500_ADC_CH_ACCDET2_MIN) * ad_value /
			AB8500_ADC_RESOLUTION;
		अवरोध;

	हाल AB8500_GPADC_CHAN_VBUS:
		res = AB8500_ADC_CH_CHG_V_MIN +
			(AB8500_ADC_CH_CHG_V_MAX - AB8500_ADC_CH_CHG_V_MIN) * ad_value /
			AB8500_ADC_RESOLUTION;
		अवरोध;

	हाल AB8500_GPADC_CHAN_MAIN_CHARGER_CURRENT:
	हाल AB8500_GPADC_CHAN_USB_CHARGER_CURRENT:
		res = AB8500_ADC_CH_CHG_I_MIN +
			(AB8500_ADC_CH_CHG_I_MAX - AB8500_ADC_CH_CHG_I_MIN) * ad_value /
			AB8500_ADC_RESOLUTION;
		अवरोध;

	हाल AB8500_GPADC_CHAN_BACKUP_BAT:
		res = AB8500_ADC_CH_BKBAT_MIN +
			(AB8500_ADC_CH_BKBAT_MAX - AB8500_ADC_CH_BKBAT_MIN) * ad_value /
			AB8500_ADC_RESOLUTION;
		अवरोध;

	हाल AB8500_GPADC_CHAN_IBAT_VIRTUAL:
		/* No calibration data available: just पूर्णांकerpolate */
		अगर (!gpadc->cal_data[AB8500_CAL_IBAT].gain) अणु
			res = AB8500_ADC_CH_IBAT_MIN + (AB8500_ADC_CH_IBAT_MAX -
				AB8500_ADC_CH_IBAT_MIN) * ad_value /
				AB8500_ADC_RESOLUTION;
			अवरोध;
		पूर्ण
		/* Here we can use calibration */
		res = (पूर्णांक) (ad_value * gpadc->cal_data[AB8500_CAL_IBAT].gain +
				gpadc->cal_data[AB8500_CAL_IBAT].offset)
				>> AB8500_GPADC_CALIB_SHIFT_IBAT;
		अवरोध;

	शेष:
		dev_err(gpadc->dev,
			"unknown channel ID: %d, not possible to convert\n",
			ch);
		res = -EINVAL;
		अवरोध;

	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक ab8500_gpadc_पढ़ो(काष्ठा ab8500_gpadc *gpadc,
			     स्थिर काष्ठा ab8500_gpadc_chan_info *ch,
			     पूर्णांक *ibat)
अणु
	पूर्णांक ret;
	पूर्णांक looplimit = 0;
	अचिन्हित दीर्घ completion_समयout;
	u8 val;
	u8 low_data, high_data, low_data2, high_data2;
	u8 ctrl1;
	u8 ctrl23;
	अचिन्हित पूर्णांक delay_min = 0;
	अचिन्हित पूर्णांक delay_max = 0;
	u8 data_low_addr, data_high_addr;

	अगर (!gpadc)
		वापस -ENODEV;

	/* check अगर conversion is supported */
	अगर ((gpadc->irq_sw <= 0) && !ch->hardware_control)
		वापस -ENOTSUPP;
	अगर ((gpadc->irq_hw <= 0) && ch->hardware_control)
		वापस -ENOTSUPP;

	/* Enable vddadc by grabbing PM runसमय */
	pm_runसमय_get_sync(gpadc->dev);

	/* Check अगर ADC is not busy, lock and proceed */
	करो अणु
		ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(gpadc->dev,
			AB8500_GPADC, AB8500_GPADC_STAT_REG, &val);
		अगर (ret < 0)
			जाओ out;
		अगर (!(val & AB8500_GPADC_STAT_BUSY))
			अवरोध;
		msleep(20);
	पूर्ण जबतक (++looplimit < 10);
	अगर (looplimit >= 10 && (val & AB8500_GPADC_STAT_BUSY)) अणु
		dev_err(gpadc->dev, "gpadc_conversion: GPADC busy");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Enable GPADC */
	ctrl1 = AB8500_GPADC_CTRL1_ENABLE;

	/* Select the channel source and set average samples */
	चयन (ch->avg_sample) अणु
	हाल 1:
		ctrl23 = ch->id | AB8500_GPADC_CTRL2_AVG_1;
		अवरोध;
	हाल 4:
		ctrl23 = ch->id | AB8500_GPADC_CTRL2_AVG_4;
		अवरोध;
	हाल 8:
		ctrl23 = ch->id | AB8500_GPADC_CTRL2_AVG_8;
		अवरोध;
	शेष:
		ctrl23 = ch->id | AB8500_GPADC_CTRL2_AVG_16;
		अवरोध;
	पूर्ण

	अगर (ch->hardware_control) अणु
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(gpadc->dev,
				AB8500_GPADC, AB8500_GPADC_CTRL3_REG, ctrl23);
		ctrl1 |= AB8500_GPADC_CTRL1_TRIG_ENA;
		अगर (ch->falling_edge)
			ctrl1 |= AB8500_GPADC_CTRL1_TRIG_EDGE;
	पूर्ण अन्यथा अणु
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(gpadc->dev,
				AB8500_GPADC, AB8500_GPADC_CTRL2_REG, ctrl23);
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(gpadc->dev,
			"gpadc_conversion: set avg samples failed\n");
		जाओ out;
	पूर्ण

	/*
	 * Enable ADC, buffering, select rising edge and enable ADC path
	 * अक्षरging current sense अगर it needed, ABB 3.0 needs some special
	 * treaपंचांगent too.
	 */
	चयन (ch->id) अणु
	हाल AB8500_GPADC_CHAN_MAIN_CHARGER_CURRENT:
	हाल AB8500_GPADC_CHAN_USB_CHARGER_CURRENT:
		ctrl1 |= AB8500_GPADC_CTRL1_BUF_ENA |
			AB8500_GPADC_CTRL1_ICHAR_ENA;
		अवरोध;
	हाल AB8500_GPADC_CHAN_BAT_TEMP:
		अगर (!is_ab8500_2p0_or_earlier(gpadc->ab8500)) अणु
			ctrl1 |= AB8500_GPADC_CTRL1_BUF_ENA |
				AB8500_GPADC_CTRL1_BTEMP_PULL_UP;
			/*
			 * Delay might be needed क्रम ABB8500 cut 3.0, अगर not,
			 * हटाओ when hardware will be available
			 */
			delay_min = 1000; /* Delay in micro seconds */
			delay_max = 10000; /* large range optimises sleepmode */
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		ctrl1 |= AB8500_GPADC_CTRL1_BUF_ENA;
		अवरोध;
	पूर्ण

	/* Write configuration to control रेजिस्टर 1 */
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(gpadc->dev,
		AB8500_GPADC, AB8500_GPADC_CTRL1_REG, ctrl1);
	अगर (ret < 0) अणु
		dev_err(gpadc->dev,
			"gpadc_conversion: set Control register failed\n");
		जाओ out;
	पूर्ण

	अगर (delay_min != 0)
		usleep_range(delay_min, delay_max);

	अगर (ch->hardware_control) अणु
		/* Set trigger delay समयr */
		ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(gpadc->dev,
			AB8500_GPADC, AB8500_GPADC_AUTO_TIMER_REG,
			ch->trig_समयr);
		अगर (ret < 0) अणु
			dev_err(gpadc->dev,
				"gpadc_conversion: trig timer failed\n");
			जाओ out;
		पूर्ण
		completion_समयout = 2 * HZ;
		data_low_addr = AB8500_GPADC_AUTODATAL_REG;
		data_high_addr = AB8500_GPADC_AUTODATAH_REG;
	पूर्ण अन्यथा अणु
		/* Start SW conversion */
		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(gpadc->dev,
			AB8500_GPADC, AB8500_GPADC_CTRL1_REG,
			AB8500_GPADC_CTRL1_START_SW_CONV,
			AB8500_GPADC_CTRL1_START_SW_CONV);
		अगर (ret < 0) अणु
			dev_err(gpadc->dev,
				"gpadc_conversion: start s/w conv failed\n");
			जाओ out;
		पूर्ण
		completion_समयout = msecs_to_jअगरfies(AB8500_GPADC_CONVERSION_TIME);
		data_low_addr = AB8500_GPADC_MANDATAL_REG;
		data_high_addr = AB8500_GPADC_MANDATAH_REG;
	पूर्ण

	/* Wait क्रम completion of conversion */
	अगर (!रुको_क्रम_completion_समयout(&gpadc->complete,
			completion_समयout)) अणु
		dev_err(gpadc->dev,
			"timeout didn't receive GPADC conv interrupt\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Read the converted RAW data */
	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(gpadc->dev,
			AB8500_GPADC, data_low_addr, &low_data);
	अगर (ret < 0) अणु
		dev_err(gpadc->dev,
			"gpadc_conversion: read low data failed\n");
		जाओ out;
	पूर्ण

	ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(gpadc->dev,
		AB8500_GPADC, data_high_addr, &high_data);
	अगर (ret < 0) अणु
		dev_err(gpadc->dev,
			"gpadc_conversion: read high data failed\n");
		जाओ out;
	पूर्ण

	/* Check अगर द्विगुन conversion is required */
	अगर ((ch->id == AB8500_GPADC_CHAN_BAT_CTRL_AND_IBAT) ||
	    (ch->id == AB8500_GPADC_CHAN_VBAT_MEAS_AND_IBAT) ||
	    (ch->id == AB8500_GPADC_CHAN_VBAT_TRUE_MEAS_AND_IBAT) ||
	    (ch->id == AB8500_GPADC_CHAN_BAT_TEMP_AND_IBAT)) अणु

		अगर (ch->hardware_control) अणु
			/* not supported */
			ret = -ENOTSUPP;
			dev_err(gpadc->dev,
				"gpadc_conversion: only SW double conversion supported\n");
			जाओ out;
		पूर्ण अन्यथा अणु
			/* Read the converted RAW data 2 */
			ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(gpadc->dev,
				AB8500_GPADC, AB8540_GPADC_MANDATA2L_REG,
				&low_data2);
			अगर (ret < 0) अणु
				dev_err(gpadc->dev,
					"gpadc_conversion: read sw low data 2 failed\n");
				जाओ out;
			पूर्ण

			ret = abx500_get_रेजिस्टर_पूर्णांकerruptible(gpadc->dev,
				AB8500_GPADC, AB8540_GPADC_MANDATA2H_REG,
				&high_data2);
			अगर (ret < 0) अणु
				dev_err(gpadc->dev,
					"gpadc_conversion: read sw high data 2 failed\n");
				जाओ out;
			पूर्ण
			अगर (ibat != शून्य) अणु
				*ibat = (high_data2 << 8) | low_data2;
			पूर्ण अन्यथा अणु
				dev_warn(gpadc->dev,
					"gpadc_conversion: ibat not stored\n");
			पूर्ण

		पूर्ण
	पूर्ण

	/* Disable GPADC */
	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(gpadc->dev, AB8500_GPADC,
		AB8500_GPADC_CTRL1_REG, AB8500_GPADC_CTRL1_DISABLE);
	अगर (ret < 0) अणु
		dev_err(gpadc->dev, "gpadc_conversion: disable gpadc failed\n");
		जाओ out;
	पूर्ण

	/* This eventually drops the regulator */
	pm_runसमय_mark_last_busy(gpadc->dev);
	pm_runसमय_put_स्वतःsuspend(gpadc->dev);

	वापस (high_data << 8) | low_data;

out:
	/*
	 * It has shown to be needed to turn off the GPADC अगर an error occurs,
	 * otherwise we might have problem when रुकोing क्रम the busy bit in the
	 * GPADC status रेजिस्टर to go low. In V1.1 there रुको_क्रम_completion
	 * seems to समयout when रुकोing क्रम an पूर्णांकerrupt.. Not seen in V2.0
	 */
	(व्योम) abx500_set_रेजिस्टर_पूर्णांकerruptible(gpadc->dev, AB8500_GPADC,
		AB8500_GPADC_CTRL1_REG, AB8500_GPADC_CTRL1_DISABLE);
	pm_runसमय_put(gpadc->dev);
	dev_err(gpadc->dev,
		"gpadc_conversion: Failed to AD convert channel %d\n", ch->id);

	वापस ret;
पूर्ण

/**
 * ab8500_bm_gpadcconvend_handler() - isr क्रम gpadc conversion completion
 * @irq: irq number
 * @data: poपूर्णांकer to the data passed during request irq
 *
 * This is a पूर्णांकerrupt service routine क्रम gpadc conversion completion.
 * Notअगरies the gpadc completion is completed and the converted raw value
 * can be पढ़ो from the रेजिस्टरs.
 * Returns IRQ status(IRQ_HANDLED)
 */
अटल irqवापस_t ab8500_bm_gpadcconvend_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ab8500_gpadc *gpadc = data;

	complete(&gpadc->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक otp_cal_regs[] = अणु
	AB8500_GPADC_CAL_1,
	AB8500_GPADC_CAL_2,
	AB8500_GPADC_CAL_3,
	AB8500_GPADC_CAL_4,
	AB8500_GPADC_CAL_5,
	AB8500_GPADC_CAL_6,
	AB8500_GPADC_CAL_7,
पूर्ण;

अटल पूर्णांक otp4_cal_regs[] = अणु
	AB8540_GPADC_OTP4_REG_7,
	AB8540_GPADC_OTP4_REG_6,
	AB8540_GPADC_OTP4_REG_5,
पूर्ण;

अटल व्योम ab8500_gpadc_पढ़ो_calibration_data(काष्ठा ab8500_gpadc *gpadc)
अणु
	पूर्णांक i;
	पूर्णांक ret[ARRAY_SIZE(otp_cal_regs)];
	u8 gpadc_cal[ARRAY_SIZE(otp_cal_regs)];
	पूर्णांक ret_otp4[ARRAY_SIZE(otp4_cal_regs)];
	u8 gpadc_otp4[ARRAY_SIZE(otp4_cal_regs)];
	पूर्णांक vमुख्य_high, vमुख्य_low;
	पूर्णांक btemp_high, btemp_low;
	पूर्णांक vbat_high, vbat_low;
	पूर्णांक ibat_high, ibat_low;
	s64 V_gain, V_offset, V2A_gain, V2A_offset;

	/* First we पढ़ो all OTP रेजिस्टरs and store the error code */
	क्रम (i = 0; i < ARRAY_SIZE(otp_cal_regs); i++) अणु
		ret[i] = abx500_get_रेजिस्टर_पूर्णांकerruptible(gpadc->dev,
			AB8500_OTP_EMUL, otp_cal_regs[i],  &gpadc_cal[i]);
		अगर (ret[i] < 0) अणु
			/* Continue anyway: maybe the other रेजिस्टरs are OK */
			dev_err(gpadc->dev, "%s: read otp reg 0x%02x failed\n",
				__func__, otp_cal_regs[i]);
		पूर्ण अन्यथा अणु
			/* Put this in the entropy pool as device-unique */
			add_device_अक्रमomness(&ret[i], माप(ret[i]));
		पूर्ण
	पूर्ण

	/*
	 * The ADC calibration data is stored in OTP रेजिस्टरs.
	 * The layout of the calibration data is outlined below and a more
	 * detailed description can be found in UM0836
	 *
	 * vm_h/l = vमुख्य_high/low
	 * bt_h/l = btemp_high/low
	 * vb_h/l = vbat_high/low
	 *
	 * Data bits 8500/9540:
	 * | 7	   | 6	   | 5	   | 4	   | 3	   | 2	   | 1	   | 0
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * |						   | vm_h9 | vm_h8
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * |		   | vm_h7 | vm_h6 | vm_h5 | vm_h4 | vm_h3 | vm_h2
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vm_h1 | vm_h0 | vm_l4 | vm_l3 | vm_l2 | vm_l1 | vm_l0 | bt_h9
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | bt_h8 | bt_h7 | bt_h6 | bt_h5 | bt_h4 | bt_h3 | bt_h2 | bt_h1
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | bt_h0 | bt_l4 | bt_l3 | bt_l2 | bt_l1 | bt_l0 | vb_h9 | vb_h8
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vb_h7 | vb_h6 | vb_h5 | vb_h4 | vb_h3 | vb_h2 | vb_h1 | vb_h0
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vb_l5 | vb_l4 | vb_l3 | vb_l2 | vb_l1 | vb_l0 |
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 *
	 * Data bits 8540:
	 * OTP2
	 * | 7	   | 6	   | 5	   | 4	   | 3	   | 2	   | 1	   | 0
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * |
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vm_h9 | vm_h8 | vm_h7 | vm_h6 | vm_h5 | vm_h4 | vm_h3 | vm_h2
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vm_h1 | vm_h0 | vm_l4 | vm_l3 | vm_l2 | vm_l1 | vm_l0 | bt_h9
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | bt_h8 | bt_h7 | bt_h6 | bt_h5 | bt_h4 | bt_h3 | bt_h2 | bt_h1
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | bt_h0 | bt_l4 | bt_l3 | bt_l2 | bt_l1 | bt_l0 | vb_h9 | vb_h8
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vb_h7 | vb_h6 | vb_h5 | vb_h4 | vb_h3 | vb_h2 | vb_h1 | vb_h0
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | vb_l5 | vb_l4 | vb_l3 | vb_l2 | vb_l1 | vb_l0 |
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 *
	 * Data bits 8540:
	 * OTP4
	 * | 7	   | 6	   | 5	   | 4	   | 3	   | 2	   | 1	   | 0
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * |					   | ib_h9 | ib_h8 | ib_h7
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | ib_h6 | ib_h5 | ib_h4 | ib_h3 | ib_h2 | ib_h1 | ib_h0 | ib_l5
	 * |.......|.......|.......|.......|.......|.......|.......|.......
	 * | ib_l4 | ib_l3 | ib_l2 | ib_l1 | ib_l0 |
	 *
	 *
	 * Ideal output ADC codes corresponding to injected input voltages
	 * during manufacturing is:
	 *
	 * vमुख्य_high: Vin = 19500mV / ADC ideal code = 997
	 * vमुख्य_low:  Vin = 315mV   / ADC ideal code = 16
	 * btemp_high: Vin = 1300mV  / ADC ideal code = 985
	 * btemp_low:  Vin = 21mV    / ADC ideal code = 16
	 * vbat_high:  Vin = 4700mV  / ADC ideal code = 982
	 * vbat_low:   Vin = 2380mV  / ADC ideal code = 33
	 */

	अगर (is_ab8540(gpadc->ab8500)) अणु
		/* Calculate gain and offset क्रम VMAIN अगर all पढ़ोs succeeded*/
		अगर (!(ret[1] < 0 || ret[2] < 0)) अणु
			vमुख्य_high = (((gpadc_cal[1] & 0xFF) << 2) |
				((gpadc_cal[2] & 0xC0) >> 6));
			vमुख्य_low = ((gpadc_cal[2] & 0x3E) >> 1);

			gpadc->cal_data[AB8500_CAL_VMAIN].otp_calib_hi =
				(u16)vमुख्य_high;
			gpadc->cal_data[AB8500_CAL_VMAIN].otp_calib_lo =
				(u16)vमुख्य_low;

			gpadc->cal_data[AB8500_CAL_VMAIN].gain = AB8500_GPADC_CALIB_SCALE *
				(19500 - 315) / (vमुख्य_high - vमुख्य_low);
			gpadc->cal_data[AB8500_CAL_VMAIN].offset = AB8500_GPADC_CALIB_SCALE *
				19500 - (AB8500_GPADC_CALIB_SCALE * (19500 - 315) /
				(vमुख्य_high - vमुख्य_low)) * vमुख्य_high;
		पूर्ण अन्यथा अणु
			gpadc->cal_data[AB8500_CAL_VMAIN].gain = 0;
		पूर्ण

		/* Read IBAT calibration Data */
		क्रम (i = 0; i < ARRAY_SIZE(otp4_cal_regs); i++) अणु
			ret_otp4[i] = abx500_get_रेजिस्टर_पूर्णांकerruptible(
					gpadc->dev, AB8500_OTP_EMUL,
					otp4_cal_regs[i],  &gpadc_otp4[i]);
			अगर (ret_otp4[i] < 0)
				dev_err(gpadc->dev,
					"%s: read otp4 reg 0x%02x failed\n",
					__func__, otp4_cal_regs[i]);
		पूर्ण

		/* Calculate gain and offset क्रम IBAT अगर all पढ़ोs succeeded */
		अगर (!(ret_otp4[0] < 0 || ret_otp4[1] < 0 || ret_otp4[2] < 0)) अणु
			ibat_high = (((gpadc_otp4[0] & 0x07) << 7) |
				((gpadc_otp4[1] & 0xFE) >> 1));
			ibat_low = (((gpadc_otp4[1] & 0x01) << 5) |
				((gpadc_otp4[2] & 0xF8) >> 3));

			gpadc->cal_data[AB8500_CAL_IBAT].otp_calib_hi =
				(u16)ibat_high;
			gpadc->cal_data[AB8500_CAL_IBAT].otp_calib_lo =
				(u16)ibat_low;

			V_gain = ((AB8500_GPADC_IBAT_VDROP_H - AB8500_GPADC_IBAT_VDROP_L)
				<< AB8500_GPADC_CALIB_SHIFT_IBAT) / (ibat_high - ibat_low);

			V_offset = (AB8500_GPADC_IBAT_VDROP_H << AB8500_GPADC_CALIB_SHIFT_IBAT) -
				(((AB8500_GPADC_IBAT_VDROP_H - AB8500_GPADC_IBAT_VDROP_L) <<
				AB8500_GPADC_CALIB_SHIFT_IBAT) / (ibat_high - ibat_low))
				* ibat_high;
			/*
			 * Result obtained is in mV (at a scale factor),
			 * we need to calculate gain and offset to get mA
			 */
			V2A_gain = (AB8500_ADC_CH_IBAT_MAX - AB8500_ADC_CH_IBAT_MIN)/
				(AB8500_ADC_CH_IBAT_MAX_V - AB8500_ADC_CH_IBAT_MIN_V);
			V2A_offset = ((AB8500_ADC_CH_IBAT_MAX_V * AB8500_ADC_CH_IBAT_MIN -
				AB8500_ADC_CH_IBAT_MAX * AB8500_ADC_CH_IBAT_MIN_V)
				<< AB8500_GPADC_CALIB_SHIFT_IBAT)
				/ (AB8500_ADC_CH_IBAT_MAX_V - AB8500_ADC_CH_IBAT_MIN_V);

			gpadc->cal_data[AB8500_CAL_IBAT].gain =
				V_gain * V2A_gain;
			gpadc->cal_data[AB8500_CAL_IBAT].offset =
				V_offset * V2A_gain + V2A_offset;
		पूर्ण अन्यथा अणु
			gpadc->cal_data[AB8500_CAL_IBAT].gain = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Calculate gain and offset क्रम VMAIN अगर all पढ़ोs succeeded */
		अगर (!(ret[0] < 0 || ret[1] < 0 || ret[2] < 0)) अणु
			vमुख्य_high = (((gpadc_cal[0] & 0x03) << 8) |
				((gpadc_cal[1] & 0x3F) << 2) |
				((gpadc_cal[2] & 0xC0) >> 6));
			vमुख्य_low = ((gpadc_cal[2] & 0x3E) >> 1);

			gpadc->cal_data[AB8500_CAL_VMAIN].otp_calib_hi =
				(u16)vमुख्य_high;
			gpadc->cal_data[AB8500_CAL_VMAIN].otp_calib_lo =
				(u16)vमुख्य_low;

			gpadc->cal_data[AB8500_CAL_VMAIN].gain = AB8500_GPADC_CALIB_SCALE *
				(19500 - 315) / (vमुख्य_high - vमुख्य_low);

			gpadc->cal_data[AB8500_CAL_VMAIN].offset = AB8500_GPADC_CALIB_SCALE *
				19500 - (AB8500_GPADC_CALIB_SCALE * (19500 - 315) /
				(vमुख्य_high - vमुख्य_low)) * vमुख्य_high;
		पूर्ण अन्यथा अणु
			gpadc->cal_data[AB8500_CAL_VMAIN].gain = 0;
		पूर्ण
	पूर्ण

	/* Calculate gain and offset क्रम BTEMP अगर all पढ़ोs succeeded */
	अगर (!(ret[2] < 0 || ret[3] < 0 || ret[4] < 0)) अणु
		btemp_high = (((gpadc_cal[2] & 0x01) << 9) |
			(gpadc_cal[3] << 1) | ((gpadc_cal[4] & 0x80) >> 7));
		btemp_low = ((gpadc_cal[4] & 0x7C) >> 2);

		gpadc->cal_data[AB8500_CAL_BTEMP].otp_calib_hi = (u16)btemp_high;
		gpadc->cal_data[AB8500_CAL_BTEMP].otp_calib_lo = (u16)btemp_low;

		gpadc->cal_data[AB8500_CAL_BTEMP].gain =
			AB8500_GPADC_CALIB_SCALE * (1300 - 21) / (btemp_high - btemp_low);
		gpadc->cal_data[AB8500_CAL_BTEMP].offset = AB8500_GPADC_CALIB_SCALE * 1300 -
			(AB8500_GPADC_CALIB_SCALE * (1300 - 21) / (btemp_high - btemp_low))
			* btemp_high;
	पूर्ण अन्यथा अणु
		gpadc->cal_data[AB8500_CAL_BTEMP].gain = 0;
	पूर्ण

	/* Calculate gain and offset क्रम VBAT अगर all पढ़ोs succeeded */
	अगर (!(ret[4] < 0 || ret[5] < 0 || ret[6] < 0)) अणु
		vbat_high = (((gpadc_cal[4] & 0x03) << 8) | gpadc_cal[5]);
		vbat_low = ((gpadc_cal[6] & 0xFC) >> 2);

		gpadc->cal_data[AB8500_CAL_VBAT].otp_calib_hi = (u16)vbat_high;
		gpadc->cal_data[AB8500_CAL_VBAT].otp_calib_lo = (u16)vbat_low;

		gpadc->cal_data[AB8500_CAL_VBAT].gain = AB8500_GPADC_CALIB_SCALE *
			(4700 - 2380) /	(vbat_high - vbat_low);
		gpadc->cal_data[AB8500_CAL_VBAT].offset = AB8500_GPADC_CALIB_SCALE * 4700 -
			(AB8500_GPADC_CALIB_SCALE * (4700 - 2380) /
			(vbat_high - vbat_low)) * vbat_high;
	पूर्ण अन्यथा अणु
		gpadc->cal_data[AB8500_CAL_VBAT].gain = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ab8500_gpadc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ab8500_gpadc *gpadc = iio_priv(indio_dev);
	स्थिर काष्ठा ab8500_gpadc_chan_info *ch;
	पूर्णांक raw_val;
	पूर्णांक processed;

	ch = ab8500_gpadc_get_channel(gpadc, chan->address);
	अगर (!ch) अणु
		dev_err(gpadc->dev, "no such channel %lu\n",
			chan->address);
		वापस -EINVAL;
	पूर्ण

	raw_val = ab8500_gpadc_पढ़ो(gpadc, ch, शून्य);
	अगर (raw_val < 0)
		वापस raw_val;

	अगर (mask == IIO_CHAN_INFO_RAW) अणु
		*val = raw_val;
		वापस IIO_VAL_INT;
	पूर्ण

	अगर (mask == IIO_CHAN_INFO_PROCESSED) अणु
		processed = ab8500_gpadc_ad_to_voltage(gpadc, ch->id, raw_val);
		अगर (processed < 0)
			वापस processed;

		/* Return millivolt or milliamps or millicentigrades */
		*val = processed;
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ab8500_gpadc_of_xlate(काष्ठा iio_dev *indio_dev,
				 स्थिर काष्ठा of_phandle_args *iiospec)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < indio_dev->num_channels; i++)
		अगर (indio_dev->channels[i].channel == iiospec->args[0])
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ab8500_gpadc_info = अणु
	.of_xlate = ab8500_gpadc_of_xlate,
	.पढ़ो_raw = ab8500_gpadc_पढ़ो_raw,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ab8500_gpadc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा ab8500_gpadc *gpadc = iio_priv(indio_dev);

	regulator_disable(gpadc->vddadc);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_gpadc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा ab8500_gpadc *gpadc = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_enable(gpadc->vddadc);
	अगर (ret)
		dev_err(dev, "Failed to enable vddadc: %d\n", ret);

	वापस ret;
पूर्ण
#पूर्ण_अगर

/**
 * ab8500_gpadc_parse_channel() - process devicetree channel configuration
 * @dev: poपूर्णांकer to containing device
 * @np: device tree node क्रम the channel to configure
 * @ch: channel info to fill in
 * @iio_chan: IIO channel specअगरication to fill in
 *
 * The devicetree will set up the channel क्रम use with the specअगरic device,
 * and define usage क्रम things like AUX GPADC inमाला_दो more precisely.
 */
अटल पूर्णांक ab8500_gpadc_parse_channel(काष्ठा device *dev,
				      काष्ठा device_node *np,
				      काष्ठा ab8500_gpadc_chan_info *ch,
				      काष्ठा iio_chan_spec *iio_chan)
अणु
	स्थिर अक्षर *name = np->name;
	u32 chan;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "reg", &chan);
	अगर (ret) अणु
		dev_err(dev, "invalid channel number %s\n", name);
		वापस ret;
	पूर्ण
	अगर (chan > AB8500_GPADC_CHAN_BAT_TEMP_AND_IBAT) अणु
		dev_err(dev, "%s channel number out of range %d\n", name, chan);
		वापस -EINVAL;
	पूर्ण

	iio_chan->channel = chan;
	iio_chan->datasheet_name = name;
	iio_chan->indexed = 1;
	iio_chan->address = chan;
	iio_chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_PROCESSED);
	/* Most are voltages (also temperatures), some are currents */
	अगर ((chan == AB8500_GPADC_CHAN_MAIN_CHARGER_CURRENT) ||
	    (chan == AB8500_GPADC_CHAN_USB_CHARGER_CURRENT))
		iio_chan->type = IIO_CURRENT;
	अन्यथा
		iio_chan->type = IIO_VOLTAGE;

	ch->id = chan;

	/* Sensible शेषs */
	ch->avg_sample = 16;
	ch->hardware_control = false;
	ch->falling_edge = false;
	ch->trig_समयr = 0;

	वापस 0;
पूर्ण

/**
 * ab8500_gpadc_parse_channels() - Parse the GPADC channels from DT
 * @gpadc: the GPADC to configure the channels क्रम
 * @np: device tree node containing the channel configurations
 * @chans: the IIO channels we parsed
 * @nchans: the number of IIO channels we parsed
 */
अटल पूर्णांक ab8500_gpadc_parse_channels(काष्ठा ab8500_gpadc *gpadc,
				       काष्ठा device_node *np,
				       काष्ठा iio_chan_spec **chans_parsed,
				       अचिन्हित पूर्णांक *nchans_parsed)
अणु
	काष्ठा device_node *child;
	काष्ठा ab8500_gpadc_chan_info *ch;
	काष्ठा iio_chan_spec *iio_chans;
	अचिन्हित पूर्णांक nchans;
	पूर्णांक i;

	nchans = of_get_available_child_count(np);
	अगर (!nchans) अणु
		dev_err(gpadc->dev, "no channel children\n");
		वापस -ENODEV;
	पूर्ण
	dev_info(gpadc->dev, "found %d ADC channels\n", nchans);

	iio_chans = devm_kसुस्मृति(gpadc->dev, nchans,
				 माप(*iio_chans), GFP_KERNEL);
	अगर (!iio_chans)
		वापस -ENOMEM;

	gpadc->chans = devm_kसुस्मृति(gpadc->dev, nchans,
				    माप(*gpadc->chans), GFP_KERNEL);
	अगर (!gpadc->chans)
		वापस -ENOMEM;

	i = 0;
	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा iio_chan_spec *iio_chan;
		पूर्णांक ret;

		ch = &gpadc->chans[i];
		iio_chan = &iio_chans[i];

		ret = ab8500_gpadc_parse_channel(gpadc->dev, child, ch,
						 iio_chan);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
		i++;
	पूर्ण
	gpadc->nchans = nchans;
	*chans_parsed = iio_chans;
	*nchans_parsed = nchans;

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_gpadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ab8500_gpadc *gpadc;
	काष्ठा iio_dev *indio_dev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा iio_chan_spec *iio_chans;
	अचिन्हित पूर्णांक n_iio_chans;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*gpadc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, indio_dev);
	gpadc = iio_priv(indio_dev);

	gpadc->dev = dev;
	gpadc->ab8500 = dev_get_drvdata(dev->parent);

	ret = ab8500_gpadc_parse_channels(gpadc, np, &iio_chans, &n_iio_chans);
	अगर (ret)
		वापस ret;

	gpadc->irq_sw = platक्रमm_get_irq_byname(pdev, "SW_CONV_END");
	अगर (gpadc->irq_sw < 0) अणु
		dev_err(dev, "failed to get platform sw_conv_end irq\n");
		वापस gpadc->irq_sw;
	पूर्ण

	अगर (is_ab8500(gpadc->ab8500)) अणु
		gpadc->irq_hw = platक्रमm_get_irq_byname(pdev, "HW_CONV_END");
		अगर (gpadc->irq_hw < 0) अणु
			dev_err(dev, "failed to get platform hw_conv_end irq\n");
			वापस gpadc->irq_hw;
		पूर्ण
	पूर्ण अन्यथा अणु
		gpadc->irq_hw = 0;
	पूर्ण

	/* Initialize completion used to notअगरy completion of conversion */
	init_completion(&gpadc->complete);

	/* Request पूर्णांकerrupts */
	ret = devm_request_thपढ़ोed_irq(dev, gpadc->irq_sw, शून्य,
		ab8500_bm_gpadcconvend_handler,	IRQF_NO_SUSPEND | IRQF_ONESHOT,
		"ab8500-gpadc-sw", gpadc);
	अगर (ret < 0) अणु
		dev_err(dev,
			"failed to request sw conversion irq %d\n",
			gpadc->irq_sw);
		वापस ret;
	पूर्ण

	अगर (gpadc->irq_hw) अणु
		ret = devm_request_thपढ़ोed_irq(dev, gpadc->irq_hw, शून्य,
			ab8500_bm_gpadcconvend_handler,	IRQF_NO_SUSPEND | IRQF_ONESHOT,
			"ab8500-gpadc-hw", gpadc);
		अगर (ret < 0) अणु
			dev_err(dev,
				"Failed to request hw conversion irq: %d\n",
				gpadc->irq_hw);
			वापस ret;
		पूर्ण
	पूर्ण

	/* The VTVout LDO used to घातer the AB8500 GPADC */
	gpadc->vddadc = devm_regulator_get(dev, "vddadc");
	अगर (IS_ERR(gpadc->vddadc)) अणु
		ret = PTR_ERR(gpadc->vddadc);
		dev_err(dev, "failed to get vddadc\n");
		वापस ret;
	पूर्ण

	ret = regulator_enable(gpadc->vddadc);
	अगर (ret) अणु
		dev_err(dev, "failed to enable vddadc: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Enable runसमय PM */
	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, AB8500_GPADC_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(dev);

	ab8500_gpadc_पढ़ो_calibration_data(gpadc);

	pm_runसमय_put(dev);

	indio_dev->name = "ab8500-gpadc";
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &ab8500_gpadc_info;
	indio_dev->channels = iio_chans;
	indio_dev->num_channels = n_iio_chans;

	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret)
		जाओ out_dis_pm;

	वापस 0;

out_dis_pm:
	pm_runसमय_get_sync(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
	regulator_disable(gpadc->vddadc);

	वापस ret;
पूर्ण

अटल पूर्णांक ab8500_gpadc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा ab8500_gpadc *gpadc = iio_priv(indio_dev);

	pm_runसमय_get_sync(gpadc->dev);
	pm_runसमय_put_noidle(gpadc->dev);
	pm_runसमय_disable(gpadc->dev);
	regulator_disable(gpadc->vddadc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ab8500_gpadc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(ab8500_gpadc_runसमय_suspend,
			   ab8500_gpadc_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver ab8500_gpadc_driver = अणु
	.probe = ab8500_gpadc_probe,
	.हटाओ = ab8500_gpadc_हटाओ,
	.driver = अणु
		.name = "ab8500-gpadc",
		.pm = &ab8500_gpadc_pm_ops,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(ab8500_gpadc_driver);
