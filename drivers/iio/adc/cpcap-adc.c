<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Tony Lindgren <tony@atomide.com>
 *
 * Rewritten क्रम Linux IIO framework with some code based on
 * earlier driver found in the Motorola Linux kernel:
 *
 * Copyright (C) 2009-2010 Motorola, Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/driver.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/mfd/motorola-cpcap.h>

/* Register CPCAP_REG_ADCC1 bits */
#घोषणा CPCAP_BIT_ADEN_AUTO_CLR		BIT(15)	/* Currently unused */
#घोषणा CPCAP_BIT_CAL_MODE		BIT(14) /* Set with BIT_RAND0 */
#घोषणा CPCAP_BIT_ADC_CLK_SEL1		BIT(13)	/* Currently unused */
#घोषणा CPCAP_BIT_ADC_CLK_SEL0		BIT(12)	/* Currently unused */
#घोषणा CPCAP_BIT_ATOX			BIT(11)
#घोषणा CPCAP_BIT_ATO3			BIT(10)
#घोषणा CPCAP_BIT_ATO2			BIT(9)
#घोषणा CPCAP_BIT_ATO1			BIT(8)
#घोषणा CPCAP_BIT_ATO0			BIT(7)
#घोषणा CPCAP_BIT_ADA2			BIT(6)
#घोषणा CPCAP_BIT_ADA1			BIT(5)
#घोषणा CPCAP_BIT_ADA0			BIT(4)
#घोषणा CPCAP_BIT_AD_SEL1		BIT(3)	/* Set क्रम bank1 */
#घोषणा CPCAP_BIT_RAND1			BIT(2)	/* Set क्रम channel 16 & 17 */
#घोषणा CPCAP_BIT_RAND0			BIT(1)	/* Set with CAL_MODE */
#घोषणा CPCAP_BIT_ADEN			BIT(0)	/* Currently unused */

#घोषणा CPCAP_REG_ADCC1_DEFAULTS	(CPCAP_BIT_ADEN_AUTO_CLR | \
					 CPCAP_BIT_ADC_CLK_SEL0 |  \
					 CPCAP_BIT_RAND1)

/* Register CPCAP_REG_ADCC2 bits */
#घोषणा CPCAP_BIT_CAL_FACTOR_ENABLE	BIT(15)	/* Currently unused */
#घोषणा CPCAP_BIT_BATDETB_EN		BIT(14)	/* Currently unused */
#घोषणा CPCAP_BIT_ADTRIG_ONESHOT	BIT(13)	/* Set क्रम !TIMING_IMM */
#घोषणा CPCAP_BIT_ASC			BIT(12)	/* Set क्रम TIMING_IMM */
#घोषणा CPCAP_BIT_ATOX_PS_FACTOR	BIT(11)
#घोषणा CPCAP_BIT_ADC_PS_FACTOR1	BIT(10)
#घोषणा CPCAP_BIT_ADC_PS_FACTOR0	BIT(9)
#घोषणा CPCAP_BIT_AD4_SELECT		BIT(8)	/* Currently unused */
#घोषणा CPCAP_BIT_ADC_BUSY		BIT(7)	/* Currently unused */
#घोषणा CPCAP_BIT_THERMBIAS_EN		BIT(6)	/* Bias क्रम AD0_BATTDETB */
#घोषणा CPCAP_BIT_ADTRIG_DIS		BIT(5)	/* Disable पूर्णांकerrupt */
#घोषणा CPCAP_BIT_LIADC			BIT(4)	/* Currently unused */
#घोषणा CPCAP_BIT_TS_REFEN		BIT(3)	/* Currently unused */
#घोषणा CPCAP_BIT_TS_M2			BIT(2)	/* Currently unused */
#घोषणा CPCAP_BIT_TS_M1			BIT(1)	/* Currently unused */
#घोषणा CPCAP_BIT_TS_M0			BIT(0)	/* Currently unused */

#घोषणा CPCAP_REG_ADCC2_DEFAULTS	(CPCAP_BIT_AD4_SELECT | \
					 CPCAP_BIT_ADTRIG_DIS | \
					 CPCAP_BIT_LIADC | \
					 CPCAP_BIT_TS_M2 | \
					 CPCAP_BIT_TS_M1)

#घोषणा CPCAP_MAX_TEMP_LVL		27
#घोषणा CPCAP_FOUR_POINT_TWO_ADC	801
#घोषणा ST_ADC_CAL_CHRGI_HIGH_THRESHOLD	530
#घोषणा ST_ADC_CAL_CHRGI_LOW_THRESHOLD	494
#घोषणा ST_ADC_CAL_BATTI_HIGH_THRESHOLD	530
#घोषणा ST_ADC_CAL_BATTI_LOW_THRESHOLD	494
#घोषणा ST_ADC_CALIBRATE_DIFF_THRESHOLD	3

#घोषणा CPCAP_ADC_MAX_RETRIES		5	/* Calibration */

/*
 * काष्ठा cpcap_adc_ato - timing settings क्रम cpcap adc
 *
 * Unक्रमtunately no cpcap करोcumentation available, please करोcument when
 * using these.
 */
काष्ठा cpcap_adc_ato अणु
	अचिन्हित लघु ato_in;
	अचिन्हित लघु atox_in;
	अचिन्हित लघु adc_ps_factor_in;
	अचिन्हित लघु atox_ps_factor_in;
	अचिन्हित लघु ato_out;
	अचिन्हित लघु atox_out;
	अचिन्हित लघु adc_ps_factor_out;
	अचिन्हित लघु atox_ps_factor_out;
पूर्ण;

/**
 * काष्ठा cpcap_adc - cpcap adc device driver data
 * @reg: cpcap regmap
 * @dev: काष्ठा device
 * @venकरोr: cpcap venकरोr
 * @irq: पूर्णांकerrupt
 * @lock: mutex
 * @ato: request timings
 * @wq_data_avail: work queue
 * @करोne: work करोne
 */
काष्ठा cpcap_adc अणु
	काष्ठा regmap *reg;
	काष्ठा device *dev;
	u16 venकरोr;
	पूर्णांक irq;
	काष्ठा mutex lock;	/* ADC रेजिस्टर access lock */
	स्थिर काष्ठा cpcap_adc_ato *ato;
	रुको_queue_head_t wq_data_avail;
	bool करोne;
पूर्ण;

/*
 * क्रमागत cpcap_adc_channel - cpcap adc channels
 */
क्रमागत cpcap_adc_channel अणु
	/* Bank0 channels */
	CPCAP_ADC_AD0,		/* Battery temperature */
	CPCAP_ADC_BATTP,	/* Battery voltage */
	CPCAP_ADC_VBUS,		/* USB VBUS voltage */
	CPCAP_ADC_AD3,		/* Die temperature when अक्षरging */
	CPCAP_ADC_BPLUS_AD4,	/* Another battery or प्रणाली voltage */
	CPCAP_ADC_CHG_ISENSE,	/* Calibrated अक्षरge current */
	CPCAP_ADC_BATTI,	/* Calibrated प्रणाली current */
	CPCAP_ADC_USB_ID,	/* USB OTG ID, unused on droid 4? */

	/* Bank1 channels */
	CPCAP_ADC_AD8,		/* Seems unused */
	CPCAP_ADC_AD9,		/* Seems unused */
	CPCAP_ADC_LICELL,	/* Maybe प्रणाली voltage? Always 3V */
	CPCAP_ADC_HV_BATTP,	/* Another battery detection? */
	CPCAP_ADC_TSX1_AD12,	/* Seems unused, क्रम touchscreen? */
	CPCAP_ADC_TSX2_AD13,	/* Seems unused, क्रम touchscreen? */
	CPCAP_ADC_TSY1_AD14,	/* Seems unused, क्रम touchscreen? */
	CPCAP_ADC_TSY2_AD15,	/* Seems unused, क्रम touchscreen? */

	/* Remuxed channels using bank0 entries */
	CPCAP_ADC_BATTP_PI16,	/* Alternative mux mode क्रम BATTP */
	CPCAP_ADC_BATTI_PI17,	/* Alternative mux mode क्रम BATTI */

	CPCAP_ADC_CHANNEL_NUM,
पूर्ण;

/*
 * क्रमागत cpcap_adc_timing - cpcap adc timing options
 *
 * CPCAP_ADC_TIMING_IMM seems to be immediate with no timings.
 * Please करोcument when using.
 */
क्रमागत cpcap_adc_timing अणु
	CPCAP_ADC_TIMING_IMM,
	CPCAP_ADC_TIMING_IN,
	CPCAP_ADC_TIMING_OUT,
पूर्ण;

/**
 * काष्ठा cpcap_adc_phasing_tbl - cpcap phasing table
 * @offset: offset in the phasing table
 * @multiplier: multiplier in the phasing table
 * @भागider: भागider in the phasing table
 * @min: minimum value
 * @max: maximum value
 */
काष्ठा cpcap_adc_phasing_tbl अणु
	लघु offset;
	अचिन्हित लघु multiplier;
	अचिन्हित लघु भागider;
	लघु min;
	लघु max;
पूर्ण;

/**
 * काष्ठा cpcap_adc_conversion_tbl - cpcap conversion table
 * @conv_type: conversion type
 * @align_offset: align offset
 * @conv_offset: conversion offset
 * @cal_offset: calibration offset
 * @multiplier: conversion multiplier
 * @भागider: conversion भागider
 */
काष्ठा cpcap_adc_conversion_tbl अणु
	क्रमागत iio_chan_info_क्रमागत conv_type;
	पूर्णांक align_offset;
	पूर्णांक conv_offset;
	पूर्णांक cal_offset;
	पूर्णांक multiplier;
	पूर्णांक भागider;
पूर्ण;

/**
 * काष्ठा cpcap_adc_request - cpcap adc request
 * @channel: request channel
 * @phase_tbl: channel phasing table
 * @conv_tbl: channel conversion table
 * @bank_index: channel index within the bank
 * @timing: timing settings
 * @result: result
 */
काष्ठा cpcap_adc_request अणु
	पूर्णांक channel;
	स्थिर काष्ठा cpcap_adc_phasing_tbl *phase_tbl;
	स्थिर काष्ठा cpcap_adc_conversion_tbl *conv_tbl;
	पूर्णांक bank_index;
	क्रमागत cpcap_adc_timing timing;
	पूर्णांक result;
पूर्ण;

/* Phasing table क्रम channels. Note that channels 16 & 17 use BATTP and BATTI */
अटल स्थिर काष्ठा cpcap_adc_phasing_tbl bank_phasing[] = अणु
	/* Bank0 */
	[CPCAP_ADC_AD0] =          अणु0, 0x80, 0x80,    0, 1023पूर्ण,
	[CPCAP_ADC_BATTP] =        अणु0, 0x80, 0x80,    0, 1023पूर्ण,
	[CPCAP_ADC_VBUS] =         अणु0, 0x80, 0x80,    0, 1023पूर्ण,
	[CPCAP_ADC_AD3] =          अणु0, 0x80, 0x80,    0, 1023पूर्ण,
	[CPCAP_ADC_BPLUS_AD4] =    अणु0, 0x80, 0x80,    0, 1023पूर्ण,
	[CPCAP_ADC_CHG_ISENSE] =   अणु0, 0x80, 0x80, -512,  511पूर्ण,
	[CPCAP_ADC_BATTI] =        अणु0, 0x80, 0x80, -512,  511पूर्ण,
	[CPCAP_ADC_USB_ID] =       अणु0, 0x80, 0x80,    0, 1023पूर्ण,

	/* Bank1 */
	[CPCAP_ADC_AD8] =          अणु0, 0x80, 0x80,    0, 1023पूर्ण,
	[CPCAP_ADC_AD9] =          अणु0, 0x80, 0x80,    0, 1023पूर्ण,
	[CPCAP_ADC_LICELL] =       अणु0, 0x80, 0x80,    0, 1023पूर्ण,
	[CPCAP_ADC_HV_BATTP] =     अणु0, 0x80, 0x80,    0, 1023पूर्ण,
	[CPCAP_ADC_TSX1_AD12] =    अणु0, 0x80, 0x80,    0, 1023पूर्ण,
	[CPCAP_ADC_TSX2_AD13] =    अणु0, 0x80, 0x80,    0, 1023पूर्ण,
	[CPCAP_ADC_TSY1_AD14] =    अणु0, 0x80, 0x80,    0, 1023पूर्ण,
	[CPCAP_ADC_TSY2_AD15] =    अणु0, 0x80, 0x80,    0, 1023पूर्ण,
पूर्ण;

/*
 * Conversion table क्रम channels. Updated during init based on calibration.
 * Here too channels 16 & 17 use BATTP and BATTI.
 */
अटल काष्ठा cpcap_adc_conversion_tbl bank_conversion[] = अणु
	/* Bank0 */
	[CPCAP_ADC_AD0] = अणु
		IIO_CHAN_INFO_PROCESSED,    0,    0, 0,     1,    1,
	पूर्ण,
	[CPCAP_ADC_BATTP] = अणु
		IIO_CHAN_INFO_PROCESSED,    0, 2400, 0,  2300, 1023,
	पूर्ण,
	[CPCAP_ADC_VBUS] = अणु
		IIO_CHAN_INFO_PROCESSED,    0,    0, 0, 10000, 1023,
	पूर्ण,
	[CPCAP_ADC_AD3] = अणु
		IIO_CHAN_INFO_PROCESSED,    0,    0, 0,     1,    1,
		पूर्ण,
	[CPCAP_ADC_BPLUS_AD4] = अणु
		IIO_CHAN_INFO_PROCESSED,    0, 2400, 0,  2300, 1023,
	पूर्ण,
	[CPCAP_ADC_CHG_ISENSE] = अणु
		IIO_CHAN_INFO_PROCESSED, -512,    2, 0,  5000, 1023,
	पूर्ण,
	[CPCAP_ADC_BATTI] = अणु
		IIO_CHAN_INFO_PROCESSED, -512,    2, 0,  5000, 1023,
	पूर्ण,
	[CPCAP_ADC_USB_ID] = अणु
		IIO_CHAN_INFO_RAW,          0,    0, 0,     1,    1,
	पूर्ण,

	/* Bank1 */
	[CPCAP_ADC_AD8] = अणु
		IIO_CHAN_INFO_RAW,          0,    0, 0,     1,    1,
	पूर्ण,
	[CPCAP_ADC_AD9] = अणु
		IIO_CHAN_INFO_RAW,          0,    0, 0,     1,    1,
	पूर्ण,
	[CPCAP_ADC_LICELL] = अणु
		IIO_CHAN_INFO_PROCESSED,    0,    0, 0,  3400, 1023,
	पूर्ण,
	[CPCAP_ADC_HV_BATTP] = अणु
		IIO_CHAN_INFO_RAW,          0,    0, 0,     1,    1,
	पूर्ण,
	[CPCAP_ADC_TSX1_AD12] = अणु
		IIO_CHAN_INFO_RAW,          0,    0, 0,     1,    1,
	पूर्ण,
	[CPCAP_ADC_TSX2_AD13] = अणु
		IIO_CHAN_INFO_RAW,          0,    0, 0,     1,    1,
	पूर्ण,
	[CPCAP_ADC_TSY1_AD14] = अणु
		IIO_CHAN_INFO_RAW,          0,    0, 0,     1,    1,
	पूर्ण,
	[CPCAP_ADC_TSY2_AD15] = अणु
		IIO_CHAN_INFO_RAW,          0,    0, 0,     1,    1,
	पूर्ण,
पूर्ण;

/*
 * Temperature lookup table of रेजिस्टर values to milliCelcius.
 * REVISIT: Check the duplicate 0x3ff entry in a मुक्तzer
 */
अटल स्थिर पूर्णांक temp_map[CPCAP_MAX_TEMP_LVL][2] = अणु
	अणु 0x03ff, -40000 पूर्ण,
	अणु 0x03ff, -35000 पूर्ण,
	अणु 0x03ef, -30000 पूर्ण,
	अणु 0x03b2, -25000 पूर्ण,
	अणु 0x036c, -20000 पूर्ण,
	अणु 0x0320, -15000 पूर्ण,
	अणु 0x02d0, -10000 पूर्ण,
	अणु 0x027f, -5000 पूर्ण,
	अणु 0x022f, 0 पूर्ण,
	अणु 0x01e4, 5000 पूर्ण,
	अणु 0x019f, 10000 पूर्ण,
	अणु 0x0161, 15000 पूर्ण,
	अणु 0x012b, 20000 पूर्ण,
	अणु 0x00fc, 25000 पूर्ण,
	अणु 0x00d4, 30000 पूर्ण,
	अणु 0x00b2, 35000 पूर्ण,
	अणु 0x0095, 40000 पूर्ण,
	अणु 0x007d, 45000 पूर्ण,
	अणु 0x0069, 50000 पूर्ण,
	अणु 0x0059, 55000 पूर्ण,
	अणु 0x004b, 60000 पूर्ण,
	अणु 0x003f, 65000 पूर्ण,
	अणु 0x0036, 70000 पूर्ण,
	अणु 0x002e, 75000 पूर्ण,
	अणु 0x0027, 80000 पूर्ण,
	अणु 0x0022, 85000 पूर्ण,
	अणु 0x001d, 90000 पूर्ण,
पूर्ण;

#घोषणा CPCAP_CHAN(_type, _index, _address, _datasheet_name) अणु	\
	.type = (_type), \
	.address = (_address), \
	.indexed = 1, \
	.channel = (_index), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			      BIT(IIO_CHAN_INFO_PROCESSED), \
	.scan_index = (_index), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 10, \
		.storagebits = 16, \
		.endianness = IIO_CPU, \
	पूर्ण, \
	.datasheet_name = (_datasheet_name), \
पूर्ण

/*
 * The datasheet names are from Motorola mapphone Linux kernel except
 * क्रम the last two which might be uncalibrated अक्षरge voltage and
 * current.
 */
अटल स्थिर काष्ठा iio_chan_spec cpcap_adc_channels[] = अणु
	/* Bank0 */
	CPCAP_CHAN(IIO_TEMP,    0, CPCAP_REG_ADCD0,  "battdetb"),
	CPCAP_CHAN(IIO_VOLTAGE, 1, CPCAP_REG_ADCD1,  "battp"),
	CPCAP_CHAN(IIO_VOLTAGE, 2, CPCAP_REG_ADCD2,  "vbus"),
	CPCAP_CHAN(IIO_TEMP,    3, CPCAP_REG_ADCD3,  "ad3"),
	CPCAP_CHAN(IIO_VOLTAGE, 4, CPCAP_REG_ADCD4,  "ad4"),
	CPCAP_CHAN(IIO_CURRENT, 5, CPCAP_REG_ADCD5,  "chg_isense"),
	CPCAP_CHAN(IIO_CURRENT, 6, CPCAP_REG_ADCD6,  "batti"),
	CPCAP_CHAN(IIO_VOLTAGE, 7, CPCAP_REG_ADCD7,  "usb_id"),

	/* Bank1 */
	CPCAP_CHAN(IIO_CURRENT, 8, CPCAP_REG_ADCD0,  "ad8"),
	CPCAP_CHAN(IIO_VOLTAGE, 9, CPCAP_REG_ADCD1,  "ad9"),
	CPCAP_CHAN(IIO_VOLTAGE, 10, CPCAP_REG_ADCD2, "licell"),
	CPCAP_CHAN(IIO_VOLTAGE, 11, CPCAP_REG_ADCD3, "hv_battp"),
	CPCAP_CHAN(IIO_VOLTAGE, 12, CPCAP_REG_ADCD4, "tsx1_ad12"),
	CPCAP_CHAN(IIO_VOLTAGE, 13, CPCAP_REG_ADCD5, "tsx2_ad13"),
	CPCAP_CHAN(IIO_VOLTAGE, 14, CPCAP_REG_ADCD6, "tsy1_ad14"),
	CPCAP_CHAN(IIO_VOLTAGE, 15, CPCAP_REG_ADCD7, "tsy2_ad15"),

	/* There are two रेजिस्टरs with multiplexed functionality */
	CPCAP_CHAN(IIO_VOLTAGE, 16, CPCAP_REG_ADCD0, "chg_vsense"),
	CPCAP_CHAN(IIO_CURRENT, 17, CPCAP_REG_ADCD1, "batti2"),
पूर्ण;

अटल irqवापस_t cpcap_adc_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा cpcap_adc *ddata = iio_priv(indio_dev);
	पूर्णांक error;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
				   CPCAP_BIT_ADTRIG_DIS,
				   CPCAP_BIT_ADTRIG_DIS);
	अगर (error)
		वापस IRQ_NONE;

	ddata->करोne = true;
	wake_up_पूर्णांकerruptible(&ddata->wq_data_avail);

	वापस IRQ_HANDLED;
पूर्ण

/* ADC calibration functions */
अटल व्योम cpcap_adc_setup_calibrate(काष्ठा cpcap_adc *ddata,
				      क्रमागत cpcap_adc_channel chan)
अणु
	अचिन्हित पूर्णांक value = 0;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(3000);
	पूर्णांक error;

	अगर ((chan != CPCAP_ADC_CHG_ISENSE) &&
	    (chan != CPCAP_ADC_BATTI))
		वापस;

	value |= CPCAP_BIT_CAL_MODE | CPCAP_BIT_RAND0;
	value |= ((chan << 4) &
		  (CPCAP_BIT_ADA2 | CPCAP_BIT_ADA1 | CPCAP_BIT_ADA0));

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC1,
				   CPCAP_BIT_CAL_MODE | CPCAP_BIT_ATOX |
				   CPCAP_BIT_ATO3 | CPCAP_BIT_ATO2 |
				   CPCAP_BIT_ATO1 | CPCAP_BIT_ATO0 |
				   CPCAP_BIT_ADA2 | CPCAP_BIT_ADA1 |
				   CPCAP_BIT_ADA0 | CPCAP_BIT_AD_SEL1 |
				   CPCAP_BIT_RAND1 | CPCAP_BIT_RAND0,
				   value);
	अगर (error)
		वापस;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
				   CPCAP_BIT_ATOX_PS_FACTOR |
				   CPCAP_BIT_ADC_PS_FACTOR1 |
				   CPCAP_BIT_ADC_PS_FACTOR0,
				   0);
	अगर (error)
		वापस;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
				   CPCAP_BIT_ADTRIG_DIS,
				   CPCAP_BIT_ADTRIG_DIS);
	अगर (error)
		वापस;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
				   CPCAP_BIT_ASC,
				   CPCAP_BIT_ASC);
	अगर (error)
		वापस;

	करो अणु
		schedule_समयout_unपूर्णांकerruptible(1);
		error = regmap_पढ़ो(ddata->reg, CPCAP_REG_ADCC2, &value);
		अगर (error)
			वापस;
	पूर्ण जबतक ((value & CPCAP_BIT_ASC) && समय_beक्रमe(jअगरfies, समयout));

	अगर (value & CPCAP_BIT_ASC)
		dev_err(ddata->dev,
			"Timeout waiting for calibration to complete\n");

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC1,
				   CPCAP_BIT_CAL_MODE, 0);
	अगर (error)
		वापस;
पूर्ण

अटल पूर्णांक cpcap_adc_calibrate_one(काष्ठा cpcap_adc *ddata,
				   पूर्णांक channel,
				   u16 calibration_रेजिस्टर,
				   पूर्णांक lower_threshold,
				   पूर्णांक upper_threshold)
अणु
	अचिन्हित पूर्णांक calibration_data[2];
	अचिन्हित लघु cal_data_dअगरf;
	पूर्णांक i, error;

	क्रम (i = 0; i < CPCAP_ADC_MAX_RETRIES; i++) अणु
		calibration_data[0]  = 0;
		calibration_data[1]  = 0;
		cal_data_dअगरf = 0;
		cpcap_adc_setup_calibrate(ddata, channel);
		error = regmap_पढ़ो(ddata->reg, calibration_रेजिस्टर,
				    &calibration_data[0]);
		अगर (error)
			वापस error;
		cpcap_adc_setup_calibrate(ddata, channel);
		error = regmap_पढ़ो(ddata->reg, calibration_रेजिस्टर,
				    &calibration_data[1]);
		अगर (error)
			वापस error;

		अगर (calibration_data[0] > calibration_data[1])
			cal_data_dअगरf =
				calibration_data[0] - calibration_data[1];
		अन्यथा
			cal_data_dअगरf =
				calibration_data[1] - calibration_data[0];

		अगर (((calibration_data[1] >= lower_threshold) &&
		     (calibration_data[1] <= upper_threshold) &&
		     (cal_data_dअगरf <= ST_ADC_CALIBRATE_DIFF_THRESHOLD)) ||
		    (ddata->venकरोr == CPCAP_VENDOR_TI)) अणु
			bank_conversion[channel].cal_offset =
				((लघु)calibration_data[1] * -1) + 512;
			dev_dbg(ddata->dev, "ch%i calibration complete: %i\n",
				channel, bank_conversion[channel].cal_offset);
			अवरोध;
		पूर्ण
		usleep_range(5000, 10000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_adc_calibrate(काष्ठा cpcap_adc *ddata)
अणु
	पूर्णांक error;

	error = cpcap_adc_calibrate_one(ddata, CPCAP_ADC_CHG_ISENSE,
					CPCAP_REG_ADCAL1,
					ST_ADC_CAL_CHRGI_LOW_THRESHOLD,
					ST_ADC_CAL_CHRGI_HIGH_THRESHOLD);
	अगर (error)
		वापस error;

	error = cpcap_adc_calibrate_one(ddata, CPCAP_ADC_BATTI,
					CPCAP_REG_ADCAL2,
					ST_ADC_CAL_BATTI_LOW_THRESHOLD,
					ST_ADC_CAL_BATTI_HIGH_THRESHOLD);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

/* ADC setup, पढ़ो and scale functions */
अटल व्योम cpcap_adc_setup_bank(काष्ठा cpcap_adc *ddata,
				 काष्ठा cpcap_adc_request *req)
अणु
	स्थिर काष्ठा cpcap_adc_ato *ato = ddata->ato;
	अचिन्हित लघु value1 = 0;
	अचिन्हित लघु value2 = 0;
	पूर्णांक error;

	अगर (!ato)
		वापस;

	चयन (req->channel) अणु
	हाल CPCAP_ADC_AD0:
		value2 |= CPCAP_BIT_THERMBIAS_EN;
		error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
					   CPCAP_BIT_THERMBIAS_EN,
					   value2);
		अगर (error)
			वापस;
		usleep_range(800, 1000);
		अवरोध;
	हाल CPCAP_ADC_AD8 ... CPCAP_ADC_TSY2_AD15:
		value1 |= CPCAP_BIT_AD_SEL1;
		अवरोध;
	हाल CPCAP_ADC_BATTP_PI16 ... CPCAP_ADC_BATTI_PI17:
		value1 |= CPCAP_BIT_RAND1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (req->timing) अणु
	हाल CPCAP_ADC_TIMING_IN:
		value1 |= ato->ato_in;
		value1 |= ato->atox_in;
		value2 |= ato->adc_ps_factor_in;
		value2 |= ato->atox_ps_factor_in;
		अवरोध;
	हाल CPCAP_ADC_TIMING_OUT:
		value1 |= ato->ato_out;
		value1 |= ato->atox_out;
		value2 |= ato->adc_ps_factor_out;
		value2 |= ato->atox_ps_factor_out;
		अवरोध;

	हाल CPCAP_ADC_TIMING_IMM:
	शेष:
		अवरोध;
	पूर्ण

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC1,
				   CPCAP_BIT_CAL_MODE | CPCAP_BIT_ATOX |
				   CPCAP_BIT_ATO3 | CPCAP_BIT_ATO2 |
				   CPCAP_BIT_ATO1 | CPCAP_BIT_ATO0 |
				   CPCAP_BIT_ADA2 | CPCAP_BIT_ADA1 |
				   CPCAP_BIT_ADA0 | CPCAP_BIT_AD_SEL1 |
				   CPCAP_BIT_RAND1 | CPCAP_BIT_RAND0,
				   value1);
	अगर (error)
		वापस;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
				   CPCAP_BIT_ATOX_PS_FACTOR |
				   CPCAP_BIT_ADC_PS_FACTOR1 |
				   CPCAP_BIT_ADC_PS_FACTOR0 |
				   CPCAP_BIT_THERMBIAS_EN,
				   value2);
	अगर (error)
		वापस;

	अगर (req->timing == CPCAP_ADC_TIMING_IMM) अणु
		error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
					   CPCAP_BIT_ADTRIG_DIS,
					   CPCAP_BIT_ADTRIG_DIS);
		अगर (error)
			वापस;

		error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
					   CPCAP_BIT_ASC,
					   CPCAP_BIT_ASC);
		अगर (error)
			वापस;
	पूर्ण अन्यथा अणु
		error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
					   CPCAP_BIT_ADTRIG_ONESHOT,
					   CPCAP_BIT_ADTRIG_ONESHOT);
		अगर (error)
			वापस;

		error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
					   CPCAP_BIT_ADTRIG_DIS, 0);
		अगर (error)
			वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक cpcap_adc_start_bank(काष्ठा cpcap_adc *ddata,
				काष्ठा cpcap_adc_request *req)
अणु
	पूर्णांक i, error;

	req->timing = CPCAP_ADC_TIMING_IMM;
	ddata->करोne = false;

	क्रम (i = 0; i < CPCAP_ADC_MAX_RETRIES; i++) अणु
		cpcap_adc_setup_bank(ddata, req);
		error = रुको_event_पूर्णांकerruptible_समयout(ddata->wq_data_avail,
							 ddata->करोne,
							 msecs_to_jअगरfies(50));
		अगर (error > 0)
			वापस 0;

		अगर (error == 0) अणु
			error = -ETIMEDOUT;
			जारी;
		पूर्ण

		अगर (error < 0)
			वापस error;
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक cpcap_adc_stop_bank(काष्ठा cpcap_adc *ddata)
अणु
	पूर्णांक error;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC1,
				   0xffff,
				   CPCAP_REG_ADCC1_DEFAULTS);
	अगर (error)
		वापस error;

	वापस regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
				  0xffff,
				  CPCAP_REG_ADCC2_DEFAULTS);
पूर्ण

अटल व्योम cpcap_adc_phase(काष्ठा cpcap_adc_request *req)
अणु
	स्थिर काष्ठा cpcap_adc_conversion_tbl *conv_tbl = req->conv_tbl;
	स्थिर काष्ठा cpcap_adc_phasing_tbl *phase_tbl = req->phase_tbl;
	पूर्णांक index = req->channel;

	/* Remuxed channels 16 and 17 use BATTP and BATTI entries */
	चयन (req->channel) अणु
	हाल CPCAP_ADC_BATTP:
	हाल CPCAP_ADC_BATTP_PI16:
		index = req->bank_index;
		req->result -= phase_tbl[index].offset;
		req->result -= CPCAP_FOUR_POINT_TWO_ADC;
		req->result *= phase_tbl[index].multiplier;
		अगर (phase_tbl[index].भागider == 0)
			वापस;
		req->result /= phase_tbl[index].भागider;
		req->result += CPCAP_FOUR_POINT_TWO_ADC;
		अवरोध;
	हाल CPCAP_ADC_BATTI_PI17:
		index = req->bank_index;
		fallthrough;
	शेष:
		req->result += conv_tbl[index].cal_offset;
		req->result += conv_tbl[index].align_offset;
		req->result *= phase_tbl[index].multiplier;
		अगर (phase_tbl[index].भागider == 0)
			वापस;
		req->result /= phase_tbl[index].भागider;
		req->result += phase_tbl[index].offset;
		अवरोध;
	पूर्ण

	अगर (req->result < phase_tbl[index].min)
		req->result = phase_tbl[index].min;
	अन्यथा अगर (req->result > phase_tbl[index].max)
		req->result = phase_tbl[index].max;
पूर्ण

/* Looks up temperatures in a table and calculates averages अगर needed */
अटल पूर्णांक cpcap_adc_table_to_millicelcius(अचिन्हित लघु value)
अणु
	पूर्णांक i, result = 0, alpha;

	अगर (value <= temp_map[CPCAP_MAX_TEMP_LVL - 1][0])
		वापस temp_map[CPCAP_MAX_TEMP_LVL - 1][1];

	अगर (value >= temp_map[0][0])
		वापस temp_map[0][1];

	क्रम (i = 0; i < CPCAP_MAX_TEMP_LVL - 1; i++) अणु
		अगर ((value <= temp_map[i][0]) &&
		    (value >= temp_map[i + 1][0])) अणु
			अगर (value == temp_map[i][0]) अणु
				result = temp_map[i][1];
			पूर्ण अन्यथा अगर (value == temp_map[i + 1][0]) अणु
				result = temp_map[i + 1][1];
			पूर्ण अन्यथा अणु
				alpha = ((value - temp_map[i][0]) * 1000) /
					(temp_map[i + 1][0] - temp_map[i][0]);

				result = temp_map[i][1] +
					((alpha * (temp_map[i + 1][1] -
						 temp_map[i][1])) / 1000);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम cpcap_adc_convert(काष्ठा cpcap_adc_request *req)
अणु
	स्थिर काष्ठा cpcap_adc_conversion_tbl *conv_tbl = req->conv_tbl;
	पूर्णांक index = req->channel;

	/* Remuxed channels 16 and 17 use BATTP and BATTI entries */
	चयन (req->channel) अणु
	हाल CPCAP_ADC_BATTP_PI16:
		index = CPCAP_ADC_BATTP;
		अवरोध;
	हाल CPCAP_ADC_BATTI_PI17:
		index = CPCAP_ADC_BATTI;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* No conversion क्रम raw channels */
	अगर (conv_tbl[index].conv_type == IIO_CHAN_INFO_RAW)
		वापस;

	/* Temperatures use a lookup table instead of conversion table */
	अगर ((req->channel == CPCAP_ADC_AD0) ||
	    (req->channel == CPCAP_ADC_AD3)) अणु
		req->result =
			cpcap_adc_table_to_millicelcius(req->result);

		वापस;
	पूर्ण

	/* All processed channels use a conversion table */
	req->result *= conv_tbl[index].multiplier;
	अगर (conv_tbl[index].भागider == 0)
		वापस;
	req->result /= conv_tbl[index].भागider;
	req->result += conv_tbl[index].conv_offset;
पूर्ण

/*
 * REVISIT: Check अगर समयd sampling can use multiple channels at the
 * same समय. If not, replace channel_mask with just channel.
 */
अटल पूर्णांक cpcap_adc_पढ़ो_bank_scaled(काष्ठा cpcap_adc *ddata,
				      काष्ठा cpcap_adc_request *req)
अणु
	पूर्णांक calibration_data, error, addr;

	अगर (ddata->venकरोr == CPCAP_VENDOR_TI) अणु
		error = regmap_पढ़ो(ddata->reg, CPCAP_REG_ADCAL1,
				    &calibration_data);
		अगर (error)
			वापस error;
		bank_conversion[CPCAP_ADC_CHG_ISENSE].cal_offset =
			((लघु)calibration_data * -1) + 512;

		error = regmap_पढ़ो(ddata->reg, CPCAP_REG_ADCAL2,
				    &calibration_data);
		अगर (error)
			वापस error;
		bank_conversion[CPCAP_ADC_BATTI].cal_offset =
			((लघु)calibration_data * -1) + 512;
	पूर्ण

	addr = CPCAP_REG_ADCD0 + req->bank_index * 4;

	error = regmap_पढ़ो(ddata->reg, addr, &req->result);
	अगर (error)
		वापस error;

	req->result &= 0x3ff;
	cpcap_adc_phase(req);
	cpcap_adc_convert(req);

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_adc_init_request(काष्ठा cpcap_adc_request *req,
				  पूर्णांक channel)
अणु
	req->channel = channel;
	req->phase_tbl = bank_phasing;
	req->conv_tbl = bank_conversion;

	चयन (channel) अणु
	हाल CPCAP_ADC_AD0 ... CPCAP_ADC_USB_ID:
		req->bank_index = channel;
		अवरोध;
	हाल CPCAP_ADC_AD8 ... CPCAP_ADC_TSY2_AD15:
		req->bank_index = channel - 8;
		अवरोध;
	हाल CPCAP_ADC_BATTP_PI16:
		req->bank_index = CPCAP_ADC_BATTP;
		अवरोध;
	हाल CPCAP_ADC_BATTI_PI17:
		req->bank_index = CPCAP_ADC_BATTI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_adc_पढ़ो_st_die_temp(काष्ठा cpcap_adc *ddata,
				      पूर्णांक addr, पूर्णांक *val)
अणु
	पूर्णांक error;

	error = regmap_पढ़ो(ddata->reg, addr, val);
	अगर (error)
		वापस error;

	*val -= 282;
	*val *= 114;
	*val += 25000;

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_adc_पढ़ो(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा cpcap_adc *ddata = iio_priv(indio_dev);
	काष्ठा cpcap_adc_request req;
	पूर्णांक error;

	error = cpcap_adc_init_request(&req, chan->channel);
	अगर (error)
		वापस error;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&ddata->lock);
		error = cpcap_adc_start_bank(ddata, &req);
		अगर (error)
			जाओ err_unlock;
		error = regmap_पढ़ो(ddata->reg, chan->address, val);
		अगर (error)
			जाओ err_unlock;
		error = cpcap_adc_stop_bank(ddata);
		अगर (error)
			जाओ err_unlock;
		mutex_unlock(&ddata->lock);
		अवरोध;
	हाल IIO_CHAN_INFO_PROCESSED:
		mutex_lock(&ddata->lock);
		error = cpcap_adc_start_bank(ddata, &req);
		अगर (error)
			जाओ err_unlock;
		अगर ((ddata->venकरोr == CPCAP_VENDOR_ST) &&
		    (chan->channel == CPCAP_ADC_AD3)) अणु
			error = cpcap_adc_पढ़ो_st_die_temp(ddata,
							   chan->address,
							   &req.result);
			अगर (error)
				जाओ err_unlock;
		पूर्ण अन्यथा अणु
			error = cpcap_adc_पढ़ो_bank_scaled(ddata, &req);
			अगर (error)
				जाओ err_unlock;
		पूर्ण
		error = cpcap_adc_stop_bank(ddata);
		अगर (error)
			जाओ err_unlock;
		mutex_unlock(&ddata->lock);
		*val = req.result;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_INT;

err_unlock:
	mutex_unlock(&ddata->lock);
	dev_err(ddata->dev, "error reading ADC: %i\n", error);

	वापस error;
पूर्ण

अटल स्थिर काष्ठा iio_info cpcap_adc_info = अणु
	.पढ़ो_raw = &cpcap_adc_पढ़ो,
पूर्ण;

/*
 * Configuration क्रम Motorola mapphone series such as droid 4.
 * Copied from the Motorola mapphone kernel tree.
 */
अटल स्थिर काष्ठा cpcap_adc_ato mapphone_adc = अणु
	.ato_in = 0x0480,
	.atox_in = 0,
	.adc_ps_factor_in = 0x0200,
	.atox_ps_factor_in = 0,
	.ato_out = 0,
	.atox_out = 0,
	.adc_ps_factor_out = 0,
	.atox_ps_factor_out = 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cpcap_adc_id_table[] = अणु
	अणु
		.compatible = "motorola,cpcap-adc",
	पूर्ण,
	अणु
		.compatible = "motorola,mapphone-cpcap-adc",
		.data = &mapphone_adc,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpcap_adc_id_table);

अटल पूर्णांक cpcap_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpcap_adc *ddata;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक error;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*ddata));
	अगर (!indio_dev) अणु
		dev_err(&pdev->dev, "failed to allocate iio device\n");

		वापस -ENOMEM;
	पूर्ण
	ddata = iio_priv(indio_dev);
	ddata->ato = device_get_match_data(&pdev->dev);
	अगर (!ddata->ato)
		वापस -ENODEV;
	ddata->dev = &pdev->dev;

	mutex_init(&ddata->lock);
	init_रुकोqueue_head(&ddata->wq_data_avail);

	indio_dev->modes = INDIO_सूचीECT_MODE | INDIO_BUFFER_SOFTWARE;
	indio_dev->channels = cpcap_adc_channels;
	indio_dev->num_channels = ARRAY_SIZE(cpcap_adc_channels);
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &cpcap_adc_info;

	ddata->reg = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!ddata->reg)
		वापस -ENODEV;

	error = cpcap_get_venकरोr(ddata->dev, ddata->reg, &ddata->venकरोr);
	अगर (error)
		वापस error;

	platक्रमm_set_drvdata(pdev, indio_dev);

	ddata->irq = platक्रमm_get_irq_byname(pdev, "adcdone");
	अगर (ddata->irq < 0)
		वापस -ENODEV;

	error = devm_request_thपढ़ोed_irq(&pdev->dev, ddata->irq, शून्य,
					  cpcap_adc_irq_thपढ़ो,
					  IRQF_TRIGGER_NONE | IRQF_ONESHOT,
					  "cpcap-adc", indio_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "could not get irq: %i\n",
			error);

		वापस error;
	पूर्ण

	error = cpcap_adc_calibrate(ddata);
	अगर (error)
		वापस error;

	dev_info(&pdev->dev, "CPCAP ADC device probed\n");

	वापस devm_iio_device_रेजिस्टर(&pdev->dev, indio_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver cpcap_adc_driver = अणु
	.driver = अणु
		.name = "cpcap_adc",
		.of_match_table = cpcap_adc_id_table,
	पूर्ण,
	.probe = cpcap_adc_probe,
पूर्ण;

module_platक्रमm_driver(cpcap_adc_driver);

MODULE_ALIAS("platform:cpcap_adc");
MODULE_DESCRIPTION("CPCAP ADC driver");
MODULE_AUTHOR("Tony Lindgren <tony@atomide.com");
MODULE_LICENSE("GPL v2");
