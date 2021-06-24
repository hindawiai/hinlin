<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of the ROHM BH1770GLC / OSRAM SFH7770 sensor driver.
 * Chip is combined proximity and ambient light sensor.
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Samu Onkalo <samu.p.onkalo@nokia.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_data/bh1770glc.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>

#घोषणा BH1770_ALS_CONTROL	0x80 /* ALS operation mode control */
#घोषणा BH1770_PS_CONTROL	0x81 /* PS operation mode control */
#घोषणा BH1770_I_LED		0x82 /* active LED and LED1, LED2 current */
#घोषणा BH1770_I_LED3		0x83 /* LED3 current setting */
#घोषणा BH1770_ALS_PS_MEAS	0x84 /* Forced mode trigger */
#घोषणा BH1770_PS_MEAS_RATE	0x85 /* PS meas. rate at stand alone mode */
#घोषणा BH1770_ALS_MEAS_RATE	0x86 /* ALS meas. rate at stand alone mode */
#घोषणा BH1770_PART_ID		0x8a /* Part number and revision ID */
#घोषणा BH1770_MANUFACT_ID	0x8b /* Manufacturerer ID */
#घोषणा BH1770_ALS_DATA_0	0x8c /* ALS DATA low byte */
#घोषणा BH1770_ALS_DATA_1	0x8d /* ALS DATA high byte */
#घोषणा BH1770_ALS_PS_STATUS	0x8e /* Measurement data and पूर्णांक status */
#घोषणा BH1770_PS_DATA_LED1	0x8f /* PS data from LED1 */
#घोषणा BH1770_PS_DATA_LED2	0x90 /* PS data from LED2 */
#घोषणा BH1770_PS_DATA_LED3	0x91 /* PS data from LED3 */
#घोषणा BH1770_INTERRUPT	0x92 /* Interrupt setting */
#घोषणा BH1770_PS_TH_LED1	0x93 /* PS पूर्णांकerrupt threshold क्रम LED1 */
#घोषणा BH1770_PS_TH_LED2	0x94 /* PS पूर्णांकerrupt threshold क्रम LED2 */
#घोषणा BH1770_PS_TH_LED3	0x95 /* PS पूर्णांकerrupt threshold क्रम LED3 */
#घोषणा BH1770_ALS_TH_UP_0	0x96 /* ALS upper threshold low byte */
#घोषणा BH1770_ALS_TH_UP_1	0x97 /* ALS upper threshold high byte */
#घोषणा BH1770_ALS_TH_LOW_0	0x98 /* ALS lower threshold low byte */
#घोषणा BH1770_ALS_TH_LOW_1	0x99 /* ALS lower threshold high byte */

/* MANUFACT_ID */
#घोषणा BH1770_MANUFACT_ROHM	0x01
#घोषणा BH1770_MANUFACT_OSRAM	0x03

/* PART_ID */
#घोषणा BH1770_PART		0x90
#घोषणा BH1770_PART_MASK	0xf0
#घोषणा BH1770_REV_MASK		0x0f
#घोषणा BH1770_REV_SHIFT	0
#घोषणा BH1770_REV_0		0x00
#घोषणा BH1770_REV_1		0x01

/* Operating modes क्रम both */
#घोषणा BH1770_STANDBY		0x00
#घोषणा BH1770_FORCED		0x02
#घोषणा BH1770_STANDALONE	0x03
#घोषणा BH1770_SWRESET		(0x01 << 2)

#घोषणा BH1770_PS_TRIG_MEAS	(1 << 0)
#घोषणा BH1770_ALS_TRIG_MEAS	(1 << 1)

/* Interrupt control */
#घोषणा BH1770_INT_OUTPUT_MODE	(1 << 3) /* 0 = latched */
#घोषणा BH1770_INT_POLARITY	(1 << 2) /* 1 = active high */
#घोषणा BH1770_INT_ALS_ENA	(1 << 1)
#घोषणा BH1770_INT_PS_ENA	(1 << 0)

/* Interrupt status */
#घोषणा BH1770_INT_LED1_DATA	(1 << 0)
#घोषणा BH1770_INT_LED1_INT	(1 << 1)
#घोषणा BH1770_INT_LED2_DATA	(1 << 2)
#घोषणा BH1770_INT_LED2_INT	(1 << 3)
#घोषणा BH1770_INT_LED3_DATA	(1 << 4)
#घोषणा BH1770_INT_LED3_INT	(1 << 5)
#घोषणा BH1770_INT_LEDS_INT	((1 << 1) | (1 << 3) | (1 << 5))
#घोषणा BH1770_INT_ALS_DATA	(1 << 6)
#घोषणा BH1770_INT_ALS_INT	(1 << 7)

/* Led channels */
#घोषणा BH1770_LED1		0x00

#घोषणा BH1770_DISABLE		0
#घोषणा BH1770_ENABLE		1
#घोषणा BH1770_PROX_CHANNELS	1

#घोषणा BH1770_LUX_DEFAULT_RATE	1 /* Index to lux rate table */
#घोषणा BH1770_PROX_DEFAULT_RATE 1 /* Direct HW value =~ 50Hz */
#घोषणा BH1770_PROX_DEF_RATE_THRESH 6 /* Direct HW value =~ 5 Hz */
#घोषणा BH1770_STARTUP_DELAY	50
#घोषणा BH1770_RESET_TIME	10
#घोषणा BH1770_TIMEOUT		2100 /* Timeout in 2.1 seconds */

#घोषणा BH1770_LUX_RANGE	65535
#घोषणा BH1770_PROX_RANGE	255
#घोषणा BH1770_COEF_SCALER	1024
#घोषणा BH1770_CALIB_SCALER	8192
#घोषणा BH1770_LUX_NEUTRAL_CALIB_VALUE (1 * BH1770_CALIB_SCALER)
#घोषणा BH1770_LUX_DEF_THRES	1000
#घोषणा BH1770_PROX_DEF_THRES	70
#घोषणा BH1770_PROX_DEF_ABS_THRES   100
#घोषणा BH1770_DEFAULT_PERSISTENCE  10
#घोषणा BH1770_PROX_MAX_PERSISTENCE 50
#घोषणा BH1770_LUX_GA_SCALE	16384
#घोषणा BH1770_LUX_CF_SCALE	2048 /* CF ChipFactor */
#घोषणा BH1770_NEUTRAL_CF	BH1770_LUX_CF_SCALE
#घोषणा BH1770_LUX_CORR_SCALE	4096

#घोषणा PROX_ABOVE_THRESHOLD	1
#घोषणा PROX_BELOW_THRESHOLD	0

#घोषणा PROX_IGNORE_LUX_LIMIT	500

काष्ठा bh1770_chip अणु
	काष्ठा bh1770_platक्रमm_data	*pdata;
	अक्षर				chipname[10];
	u8				revision;
	काष्ठा i2c_client		*client;
	काष्ठा regulator_bulk_data	regs[2];
	काष्ठा mutex			mutex; /* aव्योम parallel access */
	रुको_queue_head_t		रुको;

	bool			पूर्णांक_mode_prox;
	bool			पूर्णांक_mode_lux;
	काष्ठा delayed_work	prox_work;
	u32	lux_cf; /* Chip specअगरic factor */
	u32	lux_ga;
	u32	lux_calib;
	पूर्णांक	lux_rate_index;
	u32	lux_corr;
	u16	lux_data_raw;
	u16	lux_threshold_hi;
	u16	lux_threshold_lo;
	u16	lux_thres_hi_onchip;
	u16	lux_thres_lo_onchip;
	bool	lux_रुको_result;

	पूर्णांक	prox_enable_count;
	u16	prox_coef;
	u16	prox_स्थिर;
	पूर्णांक	prox_rate;
	पूर्णांक	prox_rate_threshold;
	u8	prox_persistence;
	u8	prox_persistence_counter;
	u8	prox_data;
	u8	prox_threshold;
	u8	prox_threshold_hw;
	bool	prox_क्रमce_update;
	u8	prox_असल_thres;
	u8	prox_led;
पूर्ण;

अटल स्थिर अक्षर reg_vcc[] = "Vcc";
अटल स्थिर अक्षर reg_vleds[] = "Vleds";

/*
 * Supported stand alone rates in ms from chip data sheet
 * अणु10, 20, 30, 40, 70, 100, 200, 500, 1000, 2000पूर्ण;
 */
अटल स्थिर s16 prox_rates_hz[] = अणु100, 50, 33, 25, 14, 10, 5, 2पूर्ण;
अटल स्थिर s16 prox_rates_ms[] = अणु10, 20, 30, 40, 70, 100, 200, 500पूर्ण;

/*
 * Supported stand alone rates in ms from chip data sheet
 * अणु100, 200, 500, 1000, 2000पूर्ण;
 */
अटल स्थिर s16 lux_rates_hz[] = अणु10, 5, 2, 1, 0पूर्ण;

/*
 * पूर्णांकerrupt control functions are called जबतक keeping chip->mutex
 * excluding module probe / हटाओ
 */
अटल अंतरभूत पूर्णांक bh1770_lux_पूर्णांकerrupt_control(काष्ठा bh1770_chip *chip,
					पूर्णांक lux)
अणु
	chip->पूर्णांक_mode_lux = lux;
	/* Set पूर्णांकerrupt modes, पूर्णांकerrupt active low, latched */
	वापस i2c_smbus_ग_लिखो_byte_data(chip->client,
					BH1770_INTERRUPT,
					(lux << 1) | chip->पूर्णांक_mode_prox);
पूर्ण

अटल अंतरभूत पूर्णांक bh1770_prox_पूर्णांकerrupt_control(काष्ठा bh1770_chip *chip,
					पूर्णांक ps)
अणु
	chip->पूर्णांक_mode_prox = ps;
	वापस i2c_smbus_ग_लिखो_byte_data(chip->client,
					BH1770_INTERRUPT,
					(chip->पूर्णांक_mode_lux << 1) | (ps << 0));
पूर्ण

/* chip->mutex is always kept here */
अटल पूर्णांक bh1770_lux_rate(काष्ठा bh1770_chip *chip, पूर्णांक rate_index)
अणु
	/* sysfs may call this when the chip is घातered off */
	अगर (pm_runसमय_suspended(&chip->client->dev))
		वापस 0;

	/* Proper proximity response needs fastest lux rate (100ms) */
	अगर (chip->prox_enable_count)
		rate_index = 0;

	वापस i2c_smbus_ग_लिखो_byte_data(chip->client,
					BH1770_ALS_MEAS_RATE,
					rate_index);
पूर्ण

अटल पूर्णांक bh1770_prox_rate(काष्ठा bh1770_chip *chip, पूर्णांक mode)
अणु
	पूर्णांक rate;

	rate = (mode == PROX_ABOVE_THRESHOLD) ?
		chip->prox_rate_threshold : chip->prox_rate;

	वापस i2c_smbus_ग_लिखो_byte_data(chip->client,
					BH1770_PS_MEAS_RATE,
					rate);
पूर्ण

/* InfraredLED is controlled by the chip during proximity scanning */
अटल अंतरभूत पूर्णांक bh1770_led_cfg(काष्ठा bh1770_chip *chip)
अणु
	/* LED cfg, current क्रम leds 1 and 2 */
	वापस i2c_smbus_ग_लिखो_byte_data(chip->client,
					BH1770_I_LED,
					(BH1770_LED1 << 6) |
					(BH1770_LED_5mA << 3) |
					chip->prox_led);
पूर्ण

/*
 * Following two functions converts raw ps values from HW to normalized
 * values. Purpose is to compensate dअगरferences between dअगरferent sensor
 * versions and variants so that result means about the same between
 * versions.
 */
अटल अंतरभूत u8 bh1770_psraw_to_adjusted(काष्ठा bh1770_chip *chip, u8 psraw)
अणु
	u16 adjusted;
	adjusted = (u16)(((u32)(psraw + chip->prox_स्थिर) * chip->prox_coef) /
		BH1770_COEF_SCALER);
	अगर (adjusted > BH1770_PROX_RANGE)
		adjusted = BH1770_PROX_RANGE;
	वापस adjusted;
पूर्ण

अटल अंतरभूत u8 bh1770_psadjusted_to_raw(काष्ठा bh1770_chip *chip, u8 ps)
अणु
	u16 raw;

	raw = (((u32)ps * BH1770_COEF_SCALER) / chip->prox_coef);
	अगर (raw > chip->prox_स्थिर)
		raw = raw - chip->prox_स्थिर;
	अन्यथा
		raw = 0;
	वापस raw;
पूर्ण

/*
 * Following two functions converts raw lux values from HW to normalized
 * values. Purpose is to compensate dअगरferences between dअगरferent sensor
 * versions and variants so that result means about the same between
 * versions. Chip->mutex is kept when this is called.
 */
अटल पूर्णांक bh1770_prox_set_threshold(काष्ठा bh1770_chip *chip)
अणु
	u8 पंचांगp = 0;

	/* sysfs may call this when the chip is घातered off */
	अगर (pm_runसमय_suspended(&chip->client->dev))
		वापस 0;

	पंचांगp = bh1770_psadjusted_to_raw(chip, chip->prox_threshold);
	chip->prox_threshold_hw = पंचांगp;

	वापस	i2c_smbus_ग_लिखो_byte_data(chip->client, BH1770_PS_TH_LED1,
					पंचांगp);
पूर्ण

अटल अंतरभूत u16 bh1770_lux_raw_to_adjusted(काष्ठा bh1770_chip *chip, u16 raw)
अणु
	u32 lux;
	lux = ((u32)raw * chip->lux_corr) / BH1770_LUX_CORR_SCALE;
	वापस min(lux, (u32)BH1770_LUX_RANGE);
पूर्ण

अटल अंतरभूत u16 bh1770_lux_adjusted_to_raw(काष्ठा bh1770_chip *chip,
					u16 adjusted)
अणु
	वापस (u32)adjusted * BH1770_LUX_CORR_SCALE / chip->lux_corr;
पूर्ण

/* chip->mutex is kept when this is called */
अटल पूर्णांक bh1770_lux_update_thresholds(काष्ठा bh1770_chip *chip,
					u16 threshold_hi, u16 threshold_lo)
अणु
	u8 data[4];
	पूर्णांक ret;

	/* sysfs may call this when the chip is घातered off */
	अगर (pm_runसमय_suspended(&chip->client->dev))
		वापस 0;

	/*
	 * Compensate threshold values with the correction factors अगर not
	 * set to minimum or maximum.
	 * Min & max values disables पूर्णांकerrupts.
	 */
	अगर (threshold_hi != BH1770_LUX_RANGE && threshold_hi != 0)
		threshold_hi = bh1770_lux_adjusted_to_raw(chip, threshold_hi);

	अगर (threshold_lo != BH1770_LUX_RANGE && threshold_lo != 0)
		threshold_lo = bh1770_lux_adjusted_to_raw(chip, threshold_lo);

	अगर (chip->lux_thres_hi_onchip == threshold_hi &&
	    chip->lux_thres_lo_onchip == threshold_lo)
		वापस 0;

	chip->lux_thres_hi_onchip = threshold_hi;
	chip->lux_thres_lo_onchip = threshold_lo;

	data[0] = threshold_hi;
	data[1] = threshold_hi >> 8;
	data[2] = threshold_lo;
	data[3] = threshold_lo >> 8;

	ret = i2c_smbus_ग_लिखो_i2c_block_data(chip->client,
					BH1770_ALS_TH_UP_0,
					ARRAY_SIZE(data),
					data);
	वापस ret;
पूर्ण

अटल पूर्णांक bh1770_lux_get_result(काष्ठा bh1770_chip *chip)
अणु
	u16 data;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(chip->client, BH1770_ALS_DATA_0);
	अगर (ret < 0)
		वापस ret;

	data = ret & 0xff;
	ret = i2c_smbus_पढ़ो_byte_data(chip->client, BH1770_ALS_DATA_1);
	अगर (ret < 0)
		वापस ret;

	chip->lux_data_raw = data | ((ret & 0xff) << 8);

	वापस 0;
पूर्ण

/* Calculate correction value which contains chip and device specअगरic parts */
अटल u32 bh1770_get_corr_value(काष्ठा bh1770_chip *chip)
अणु
	u32 पंचांगp;
	/* Impact of glass attenuation correction */
	पंचांगp = (BH1770_LUX_CORR_SCALE * chip->lux_ga) / BH1770_LUX_GA_SCALE;
	/* Impact of chip factor correction */
	पंचांगp = (पंचांगp * chip->lux_cf) / BH1770_LUX_CF_SCALE;
	/* Impact of Device specअगरic calibration correction */
	पंचांगp = (पंचांगp * chip->lux_calib) / BH1770_CALIB_SCALER;
	वापस पंचांगp;
पूर्ण

अटल पूर्णांक bh1770_lux_पढ़ो_result(काष्ठा bh1770_chip *chip)
अणु
	bh1770_lux_get_result(chip);
	वापस bh1770_lux_raw_to_adjusted(chip, chip->lux_data_raw);
पूर्ण

/*
 * Chip on / off functions are called जबतक keeping mutex except probe
 * or हटाओ phase
 */
अटल पूर्णांक bh1770_chip_on(काष्ठा bh1770_chip *chip)
अणु
	पूर्णांक ret = regulator_bulk_enable(ARRAY_SIZE(chip->regs),
					chip->regs);
	अगर (ret < 0)
		वापस ret;

	usleep_range(BH1770_STARTUP_DELAY, BH1770_STARTUP_DELAY * 2);

	/* Reset the chip */
	i2c_smbus_ग_लिखो_byte_data(chip->client, BH1770_ALS_CONTROL,
				BH1770_SWRESET);
	usleep_range(BH1770_RESET_TIME, BH1770_RESET_TIME * 2);

	/*
	 * ALS is started always since proximity needs als results
	 * क्रम realibility estimation.
	 * Let's assume dark until the first ALS measurement is पढ़ोy.
	 */
	chip->lux_data_raw = 0;
	chip->prox_data = 0;
	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
					BH1770_ALS_CONTROL, BH1770_STANDALONE);

	/* Assume reset शेषs */
	chip->lux_thres_hi_onchip = BH1770_LUX_RANGE;
	chip->lux_thres_lo_onchip = 0;

	वापस ret;
पूर्ण

अटल व्योम bh1770_chip_off(काष्ठा bh1770_chip *chip)
अणु
	i2c_smbus_ग_लिखो_byte_data(chip->client,
					BH1770_INTERRUPT, BH1770_DISABLE);
	i2c_smbus_ग_लिखो_byte_data(chip->client,
				BH1770_ALS_CONTROL, BH1770_STANDBY);
	i2c_smbus_ग_लिखो_byte_data(chip->client,
				BH1770_PS_CONTROL, BH1770_STANDBY);
	regulator_bulk_disable(ARRAY_SIZE(chip->regs), chip->regs);
पूर्ण

/* chip->mutex is kept when this is called */
अटल पूर्णांक bh1770_prox_mode_control(काष्ठा bh1770_chip *chip)
अणु
	अगर (chip->prox_enable_count) अणु
		chip->prox_क्रमce_update = true; /* Force immediate update */

		bh1770_lux_rate(chip, chip->lux_rate_index);
		bh1770_prox_set_threshold(chip);
		bh1770_led_cfg(chip);
		bh1770_prox_rate(chip, PROX_BELOW_THRESHOLD);
		bh1770_prox_पूर्णांकerrupt_control(chip, BH1770_ENABLE);
		i2c_smbus_ग_लिखो_byte_data(chip->client,
					BH1770_PS_CONTROL, BH1770_STANDALONE);
	पूर्ण अन्यथा अणु
		chip->prox_data = 0;
		bh1770_lux_rate(chip, chip->lux_rate_index);
		bh1770_prox_पूर्णांकerrupt_control(chip, BH1770_DISABLE);
		i2c_smbus_ग_लिखो_byte_data(chip->client,
					BH1770_PS_CONTROL, BH1770_STANDBY);
	पूर्ण
	वापस 0;
पूर्ण

/* chip->mutex is kept when this is called */
अटल पूर्णांक bh1770_prox_पढ़ो_result(काष्ठा bh1770_chip *chip)
अणु
	पूर्णांक ret;
	bool above;
	u8 mode;

	ret = i2c_smbus_पढ़ो_byte_data(chip->client, BH1770_PS_DATA_LED1);
	अगर (ret < 0)
		जाओ out;

	अगर (ret > chip->prox_threshold_hw)
		above = true;
	अन्यथा
		above = false;

	/*
	 * when ALS levels goes above limit, proximity result may be
	 * false proximity. Thus ignore the result. With real proximity
	 * there is a shaकरोw causing low als levels.
	 */
	अगर (chip->lux_data_raw > PROX_IGNORE_LUX_LIMIT)
		ret = 0;

	chip->prox_data = bh1770_psraw_to_adjusted(chip, ret);

	/* Strong proximity level or क्रमce mode requires immediate response */
	अगर (chip->prox_data >= chip->prox_असल_thres ||
	    chip->prox_क्रमce_update)
		chip->prox_persistence_counter = chip->prox_persistence;

	chip->prox_क्रमce_update = false;

	/* Persistence filttering to reduce false proximity events */
	अगर (likely(above)) अणु
		अगर (chip->prox_persistence_counter < chip->prox_persistence) अणु
			chip->prox_persistence_counter++;
			ret = -ENODATA;
		पूर्ण अन्यथा अणु
			mode = PROX_ABOVE_THRESHOLD;
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		chip->prox_persistence_counter = 0;
		mode = PROX_BELOW_THRESHOLD;
		chip->prox_data = 0;
		ret = 0;
	पूर्ण

	/* Set proximity detection rate based on above or below value */
	अगर (ret == 0) अणु
		bh1770_prox_rate(chip, mode);
		sysfs_notअगरy(&chip->client->dev.kobj, शून्य, "prox0_raw");
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक bh1770_detect(काष्ठा bh1770_chip *chip)
अणु
	काष्ठा i2c_client *client = chip->client;
	s32 ret;
	u8 manu, part;

	ret = i2c_smbus_पढ़ो_byte_data(client, BH1770_MANUFACT_ID);
	अगर (ret < 0)
		जाओ error;
	manu = (u8)ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, BH1770_PART_ID);
	अगर (ret < 0)
		जाओ error;
	part = (u8)ret;

	chip->revision = (part & BH1770_REV_MASK) >> BH1770_REV_SHIFT;
	chip->prox_coef = BH1770_COEF_SCALER;
	chip->prox_स्थिर = 0;
	chip->lux_cf = BH1770_NEUTRAL_CF;

	अगर ((manu == BH1770_MANUFACT_ROHM) &&
	    ((part & BH1770_PART_MASK) == BH1770_PART)) अणु
		snम_लिखो(chip->chipname, माप(chip->chipname), "BH1770GLC");
		वापस 0;
	पूर्ण

	अगर ((manu == BH1770_MANUFACT_OSRAM) &&
	    ((part & BH1770_PART_MASK) == BH1770_PART)) अणु
		snम_लिखो(chip->chipname, माप(chip->chipname), "SFH7770");
		/* Values selected by comparing dअगरferent versions */
		chip->prox_coef = 819; /* 0.8 * BH1770_COEF_SCALER */
		chip->prox_स्थिर = 40;
		वापस 0;
	पूर्ण

	ret = -ENODEV;
error:
	dev_dbg(&client->dev, "BH1770 or SFH7770 not found\n");

	वापस ret;
पूर्ण

/*
 * This work is re-scheduled at every proximity पूर्णांकerrupt.
 * If this work is running, it means that there hasn't been any
 * proximity पूर्णांकerrupt in समय. Situation is handled as no-proximity.
 * It would be nice to have low-threshold पूर्णांकerrupt or पूर्णांकerrupt
 * when measurement and hi-threshold are both 0. But neither of those exists.
 * This is a workaroud क्रम missing HW feature.
 */

अटल व्योम bh1770_prox_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bh1770_chip *chip =
		container_of(work, काष्ठा bh1770_chip, prox_work.work);

	mutex_lock(&chip->mutex);
	bh1770_prox_पढ़ो_result(chip);
	mutex_unlock(&chip->mutex);
पूर्ण

/* This is thपढ़ोed irq handler */
अटल irqवापस_t bh1770_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bh1770_chip *chip = data;
	पूर्णांक status;
	पूर्णांक rate = 0;

	mutex_lock(&chip->mutex);
	status = i2c_smbus_पढ़ो_byte_data(chip->client, BH1770_ALS_PS_STATUS);

	/* Acknowledge पूर्णांकerrupt by पढ़ोing this रेजिस्टर */
	i2c_smbus_पढ़ो_byte_data(chip->client, BH1770_INTERRUPT);

	/*
	 * Check अगर there is fresh data available क्रम als.
	 * If this is the very first data, update thresholds after that.
	 */
	अगर (status & BH1770_INT_ALS_DATA) अणु
		bh1770_lux_get_result(chip);
		अगर (unlikely(chip->lux_रुको_result)) अणु
			chip->lux_रुको_result = false;
			wake_up(&chip->रुको);
			bh1770_lux_update_thresholds(chip,
						chip->lux_threshold_hi,
						chip->lux_threshold_lo);
		पूर्ण
	पूर्ण

	/* Disable पूर्णांकerrupt logic to guarantee acknowledgement */
	i2c_smbus_ग_लिखो_byte_data(chip->client, BH1770_INTERRUPT,
				  (0 << 1) | (0 << 0));

	अगर ((status & BH1770_INT_ALS_INT))
		sysfs_notअगरy(&chip->client->dev.kobj, शून्य, "lux0_input");

	अगर (chip->पूर्णांक_mode_prox && (status & BH1770_INT_LEDS_INT)) अणु
		rate = prox_rates_ms[chip->prox_rate_threshold];
		bh1770_prox_पढ़ो_result(chip);
	पूर्ण

	/* Re-enable पूर्णांकerrupt logic */
	i2c_smbus_ग_लिखो_byte_data(chip->client, BH1770_INTERRUPT,
				  (chip->पूर्णांक_mode_lux << 1) |
				  (chip->पूर्णांक_mode_prox << 0));
	mutex_unlock(&chip->mutex);

	/*
	 * Can't cancel work जबतक keeping mutex since the work uses the
	 * same mutex.
	 */
	अगर (rate) अणु
		/*
		 * Simulate missing no-proximity पूर्णांकerrupt 50ms after the
		 * next expected पूर्णांकerrupt समय.
		 */
		cancel_delayed_work_sync(&chip->prox_work);
		schedule_delayed_work(&chip->prox_work,
				msecs_to_jअगरfies(rate + 50));
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार bh1770_घातer_state_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	mutex_lock(&chip->mutex);
	अगर (value) अणु
		pm_runसमय_get_sync(dev);

		ret = bh1770_lux_rate(chip, chip->lux_rate_index);
		अगर (ret < 0) अणु
			pm_runसमय_put(dev);
			जाओ leave;
		पूर्ण

		ret = bh1770_lux_पूर्णांकerrupt_control(chip, BH1770_ENABLE);
		अगर (ret < 0) अणु
			pm_runसमय_put(dev);
			जाओ leave;
		पूर्ण

		/* This causes पूर्णांकerrupt after the next measurement cycle */
		bh1770_lux_update_thresholds(chip, BH1770_LUX_DEF_THRES,
					BH1770_LUX_DEF_THRES);
		/* Inक्रमm that we are रुकोing क्रम a result from ALS */
		chip->lux_रुको_result = true;
		bh1770_prox_mode_control(chip);
	पूर्ण अन्यथा अगर (!pm_runसमय_suspended(dev)) अणु
		pm_runसमय_put(dev);
	पूर्ण
	ret = count;
leave:
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार bh1770_घातer_state_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", !pm_runसमय_suspended(dev));
पूर्ण

अटल sमाप_प्रकार bh1770_lux_result_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	sमाप_प्रकार ret;
	दीर्घ समयout;

	अगर (pm_runसमय_suspended(dev))
		वापस -EIO; /* Chip is not enabled at all */

	समयout = रुको_event_पूर्णांकerruptible_समयout(chip->रुको,
					!chip->lux_रुको_result,
					msecs_to_jअगरfies(BH1770_TIMEOUT));
	अगर (!समयout)
		वापस -EIO;

	mutex_lock(&chip->mutex);
	ret = प्र_लिखो(buf, "%d\n", bh1770_lux_पढ़ो_result(chip));
	mutex_unlock(&chip->mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार bh1770_lux_range_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", BH1770_LUX_RANGE);
पूर्ण

अटल sमाप_प्रकार bh1770_prox_enable_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	mutex_lock(&chip->mutex);
	/* Assume no proximity. Sensor will tell real state soon */
	अगर (!chip->prox_enable_count)
		chip->prox_data = 0;

	अगर (value)
		chip->prox_enable_count++;
	अन्यथा अगर (chip->prox_enable_count > 0)
		chip->prox_enable_count--;
	अन्यथा
		जाओ leave;

	/* Run control only when chip is घातered on */
	अगर (!pm_runसमय_suspended(dev))
		bh1770_prox_mode_control(chip);
leave:
	mutex_unlock(&chip->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार bh1770_prox_enable_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	sमाप_प्रकार len;

	mutex_lock(&chip->mutex);
	len = प्र_लिखो(buf, "%d\n", chip->prox_enable_count);
	mutex_unlock(&chip->mutex);
	वापस len;
पूर्ण

अटल sमाप_प्रकार bh1770_prox_result_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	sमाप_प्रकार ret;

	mutex_lock(&chip->mutex);
	अगर (chip->prox_enable_count && !pm_runसमय_suspended(dev))
		ret = प्र_लिखो(buf, "%d\n", chip->prox_data);
	अन्यथा
		ret = -EIO;
	mutex_unlock(&chip->mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार bh1770_prox_range_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", BH1770_PROX_RANGE);
पूर्ण

अटल sमाप_प्रकार bh1770_get_prox_rate_avail(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i;
	पूर्णांक pos = 0;
	क्रम (i = 0; i < ARRAY_SIZE(prox_rates_hz); i++)
		pos += प्र_लिखो(buf + pos, "%d ", prox_rates_hz[i]);
	प्र_लिखो(buf + pos - 1, "\n");
	वापस pos;
पूर्ण

अटल sमाप_प्रकार bh1770_get_prox_rate_above(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", prox_rates_hz[chip->prox_rate_threshold]);
पूर्ण

अटल sमाप_प्रकार bh1770_get_prox_rate_below(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", prox_rates_hz[chip->prox_rate]);
पूर्ण

अटल पूर्णांक bh1770_prox_rate_validate(पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(prox_rates_hz) - 1; i++)
		अगर (rate >= prox_rates_hz[i])
			अवरोध;
	वापस i;
पूर्ण

अटल sमाप_प्रकार bh1770_set_prox_rate_above(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	mutex_lock(&chip->mutex);
	chip->prox_rate_threshold = bh1770_prox_rate_validate(value);
	mutex_unlock(&chip->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार bh1770_set_prox_rate_below(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	mutex_lock(&chip->mutex);
	chip->prox_rate = bh1770_prox_rate_validate(value);
	mutex_unlock(&chip->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार bh1770_get_prox_thres(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", chip->prox_threshold);
पूर्ण

अटल sमाप_प्रकार bh1770_set_prox_thres(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	अगर (value > BH1770_PROX_RANGE)
		वापस -EINVAL;

	mutex_lock(&chip->mutex);
	chip->prox_threshold = value;
	ret = bh1770_prox_set_threshold(chip);
	mutex_unlock(&chip->mutex);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

अटल sमाप_प्रकार bh1770_prox_persistence_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", chip->prox_persistence);
पूर्ण

अटल sमाप_प्रकार bh1770_prox_persistence_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा bh1770_chip *chip = dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	अगर (value > BH1770_PROX_MAX_PERSISTENCE)
		वापस -EINVAL;

	chip->prox_persistence = value;

	वापस len;
पूर्ण

अटल sमाप_प्रकार bh1770_prox_असल_thres_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%u\n", chip->prox_असल_thres);
पूर्ण

अटल sमाप_प्रकार bh1770_prox_असल_thres_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा bh1770_chip *chip = dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	अगर (value > BH1770_PROX_RANGE)
		वापस -EINVAL;

	chip->prox_असल_thres = value;

	वापस len;
पूर्ण

अटल sमाप_प्रकार bh1770_chip_id_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%s rev %d\n", chip->chipname, chip->revision);
पूर्ण

अटल sमाप_प्रकार bh1770_lux_calib_शेष_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", BH1770_CALIB_SCALER);
पूर्ण

अटल sमाप_प्रकार bh1770_lux_calib_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip = dev_get_drvdata(dev);
	sमाप_प्रकार len;

	mutex_lock(&chip->mutex);
	len = प्र_लिखो(buf, "%u\n", chip->lux_calib);
	mutex_unlock(&chip->mutex);
	वापस len;
पूर्ण

अटल sमाप_प्रकार bh1770_lux_calib_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा bh1770_chip *chip = dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	u32 old_calib;
	u32 new_corr;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		वापस ret;

	mutex_lock(&chip->mutex);
	old_calib = chip->lux_calib;
	chip->lux_calib = value;
	new_corr = bh1770_get_corr_value(chip);
	अगर (new_corr == 0) अणु
		chip->lux_calib = old_calib;
		mutex_unlock(&chip->mutex);
		वापस -EINVAL;
	पूर्ण
	chip->lux_corr = new_corr;
	/* Refresh thresholds on HW after changing correction value */
	bh1770_lux_update_thresholds(chip, chip->lux_threshold_hi,
				chip->lux_threshold_lo);

	mutex_unlock(&chip->mutex);

	वापस len;
पूर्ण

अटल sमाप_प्रकार bh1770_get_lux_rate_avail(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i;
	पूर्णांक pos = 0;
	क्रम (i = 0; i < ARRAY_SIZE(lux_rates_hz); i++)
		pos += प्र_लिखो(buf + pos, "%d ", lux_rates_hz[i]);
	प्र_लिखो(buf + pos - 1, "\n");
	वापस pos;
पूर्ण

अटल sमाप_प्रकार bh1770_get_lux_rate(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", lux_rates_hz[chip->lux_rate_index]);
पूर्ण

अटल sमाप_प्रकार bh1770_set_lux_rate(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	अचिन्हित दीर्घ rate_hz;
	पूर्णांक ret, i;

	ret = kम_से_अदीर्घ(buf, 0, &rate_hz);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(lux_rates_hz) - 1; i++)
		अगर (rate_hz >= lux_rates_hz[i])
			अवरोध;

	mutex_lock(&chip->mutex);
	chip->lux_rate_index = i;
	ret = bh1770_lux_rate(chip, i);
	mutex_unlock(&chip->mutex);

	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार bh1770_get_lux_thresh_above(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", chip->lux_threshold_hi);
पूर्ण

अटल sमाप_प्रकार bh1770_get_lux_thresh_below(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", chip->lux_threshold_lo);
पूर्ण

अटल sमाप_प्रकार bh1770_set_lux_thresh(काष्ठा bh1770_chip *chip, u16 *target,
				स्थिर अक्षर *buf)
अणु
	अचिन्हित दीर्घ thresh;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &thresh);
	अगर (ret)
		वापस ret;

	अगर (thresh > BH1770_LUX_RANGE)
		वापस -EINVAL;

	mutex_lock(&chip->mutex);
	*target = thresh;
	/*
	 * Don't update values in HW अगर we are still रुकोing क्रम
	 * first पूर्णांकerrupt to come after device handle खोलो call.
	 */
	अगर (!chip->lux_रुको_result)
		ret = bh1770_lux_update_thresholds(chip,
						chip->lux_threshold_hi,
						chip->lux_threshold_lo);
	mutex_unlock(&chip->mutex);
	वापस ret;

पूर्ण

अटल sमाप_प्रकार bh1770_set_lux_thresh_above(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	पूर्णांक ret = bh1770_set_lux_thresh(chip, &chip->lux_threshold_hi, buf);
	अगर (ret < 0)
		वापस ret;
	वापस len;
पूर्ण

अटल sमाप_प्रकार bh1770_set_lux_thresh_below(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा bh1770_chip *chip =  dev_get_drvdata(dev);
	पूर्णांक ret = bh1770_set_lux_thresh(chip, &chip->lux_threshold_lo, buf);
	अगर (ret < 0)
		वापस ret;
	वापस len;
पूर्ण

अटल DEVICE_ATTR(prox0_raw_en, S_IRUGO | S_IWUSR, bh1770_prox_enable_show,
						bh1770_prox_enable_store);
अटल DEVICE_ATTR(prox0_thresh_above1_value, S_IRUGO | S_IWUSR,
						bh1770_prox_असल_thres_show,
						bh1770_prox_असल_thres_store);
अटल DEVICE_ATTR(prox0_thresh_above0_value, S_IRUGO | S_IWUSR,
						bh1770_get_prox_thres,
						bh1770_set_prox_thres);
अटल DEVICE_ATTR(prox0_raw, S_IRUGO, bh1770_prox_result_show, शून्य);
अटल DEVICE_ATTR(prox0_sensor_range, S_IRUGO, bh1770_prox_range_show, शून्य);
अटल DEVICE_ATTR(prox0_thresh_above_count, S_IRUGO | S_IWUSR,
						bh1770_prox_persistence_show,
						bh1770_prox_persistence_store);
अटल DEVICE_ATTR(prox0_rate_above, S_IRUGO | S_IWUSR,
						bh1770_get_prox_rate_above,
						bh1770_set_prox_rate_above);
अटल DEVICE_ATTR(prox0_rate_below, S_IRUGO | S_IWUSR,
						bh1770_get_prox_rate_below,
						bh1770_set_prox_rate_below);
अटल DEVICE_ATTR(prox0_rate_avail, S_IRUGO, bh1770_get_prox_rate_avail, शून्य);

अटल DEVICE_ATTR(lux0_calibscale, S_IRUGO | S_IWUSR, bh1770_lux_calib_show,
						bh1770_lux_calib_store);
अटल DEVICE_ATTR(lux0_calibscale_शेष, S_IRUGO,
						bh1770_lux_calib_शेष_show,
						शून्य);
अटल DEVICE_ATTR(lux0_input, S_IRUGO, bh1770_lux_result_show, शून्य);
अटल DEVICE_ATTR(lux0_sensor_range, S_IRUGO, bh1770_lux_range_show, शून्य);
अटल DEVICE_ATTR(lux0_rate, S_IRUGO | S_IWUSR, bh1770_get_lux_rate,
						bh1770_set_lux_rate);
अटल DEVICE_ATTR(lux0_rate_avail, S_IRUGO, bh1770_get_lux_rate_avail, शून्य);
अटल DEVICE_ATTR(lux0_thresh_above_value, S_IRUGO | S_IWUSR,
						bh1770_get_lux_thresh_above,
						bh1770_set_lux_thresh_above);
अटल DEVICE_ATTR(lux0_thresh_below_value, S_IRUGO | S_IWUSR,
						bh1770_get_lux_thresh_below,
						bh1770_set_lux_thresh_below);
अटल DEVICE_ATTR(chip_id, S_IRUGO, bh1770_chip_id_show, शून्य);
अटल DEVICE_ATTR(घातer_state, S_IRUGO | S_IWUSR, bh1770_घातer_state_show,
						 bh1770_घातer_state_store);


अटल काष्ठा attribute *sysfs_attrs[] = अणु
	&dev_attr_lux0_calibscale.attr,
	&dev_attr_lux0_calibscale_शेष.attr,
	&dev_attr_lux0_input.attr,
	&dev_attr_lux0_sensor_range.attr,
	&dev_attr_lux0_rate.attr,
	&dev_attr_lux0_rate_avail.attr,
	&dev_attr_lux0_thresh_above_value.attr,
	&dev_attr_lux0_thresh_below_value.attr,
	&dev_attr_prox0_raw.attr,
	&dev_attr_prox0_sensor_range.attr,
	&dev_attr_prox0_raw_en.attr,
	&dev_attr_prox0_thresh_above_count.attr,
	&dev_attr_prox0_rate_above.attr,
	&dev_attr_prox0_rate_below.attr,
	&dev_attr_prox0_rate_avail.attr,
	&dev_attr_prox0_thresh_above0_value.attr,
	&dev_attr_prox0_thresh_above1_value.attr,
	&dev_attr_chip_id.attr,
	&dev_attr_घातer_state.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group bh1770_attribute_group = अणु
	.attrs = sysfs_attrs
पूर्ण;

अटल पूर्णांक bh1770_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा bh1770_chip *chip;
	पूर्णांक err;

	chip = devm_kzalloc(&client->dev, माप *chip, GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	i2c_set_clientdata(client, chip);
	chip->client  = client;

	mutex_init(&chip->mutex);
	init_रुकोqueue_head(&chip->रुको);
	INIT_DELAYED_WORK(&chip->prox_work, bh1770_prox_work);

	अगर (client->dev.platक्रमm_data == शून्य) अणु
		dev_err(&client->dev, "platform data is mandatory\n");
		वापस -EINVAL;
	पूर्ण

	chip->pdata		= client->dev.platक्रमm_data;
	chip->lux_calib		= BH1770_LUX_NEUTRAL_CALIB_VALUE;
	chip->lux_rate_index	= BH1770_LUX_DEFAULT_RATE;
	chip->lux_threshold_lo	= BH1770_LUX_DEF_THRES;
	chip->lux_threshold_hi	= BH1770_LUX_DEF_THRES;

	अगर (chip->pdata->glass_attenuation == 0)
		chip->lux_ga = BH1770_NEUTRAL_GA;
	अन्यथा
		chip->lux_ga = chip->pdata->glass_attenuation;

	chip->prox_threshold	= BH1770_PROX_DEF_THRES;
	chip->prox_led		= chip->pdata->led_def_curr;
	chip->prox_असल_thres	= BH1770_PROX_DEF_ABS_THRES;
	chip->prox_persistence	= BH1770_DEFAULT_PERSISTENCE;
	chip->prox_rate_threshold = BH1770_PROX_DEF_RATE_THRESH;
	chip->prox_rate		= BH1770_PROX_DEFAULT_RATE;
	chip->prox_data		= 0;

	chip->regs[0].supply = reg_vcc;
	chip->regs[1].supply = reg_vleds;

	err = devm_regulator_bulk_get(&client->dev,
				      ARRAY_SIZE(chip->regs), chip->regs);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Cannot get regulators\n");
		वापस err;
	पूर्ण

	err = regulator_bulk_enable(ARRAY_SIZE(chip->regs),
				chip->regs);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Cannot enable regulators\n");
		वापस err;
	पूर्ण

	usleep_range(BH1770_STARTUP_DELAY, BH1770_STARTUP_DELAY * 2);
	err = bh1770_detect(chip);
	अगर (err < 0)
		जाओ fail0;

	/* Start chip */
	bh1770_chip_on(chip);
	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);

	chip->lux_corr = bh1770_get_corr_value(chip);
	अगर (chip->lux_corr == 0) अणु
		dev_err(&client->dev, "Improper correction values\n");
		err = -EINVAL;
		जाओ fail0;
	पूर्ण

	अगर (chip->pdata->setup_resources) अणु
		err = chip->pdata->setup_resources();
		अगर (err) अणु
			err = -EINVAL;
			जाओ fail0;
		पूर्ण
	पूर्ण

	err = sysfs_create_group(&chip->client->dev.kobj,
				&bh1770_attribute_group);
	अगर (err < 0) अणु
		dev_err(&chip->client->dev, "Sysfs registration failed\n");
		जाओ fail1;
	पूर्ण

	/*
	 * Chip needs level triggered पूर्णांकerrupt to work. However,
	 * level triggering करोesn't work always correctly with घातer
	 * management. Select both
	 */
	err = request_thपढ़ोed_irq(client->irq, शून्य,
				bh1770_irq,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT |
				IRQF_TRIGGER_LOW,
				"bh1770", chip);
	अगर (err) अणु
		dev_err(&client->dev, "could not get IRQ %d\n",
			client->irq);
		जाओ fail2;
	पूर्ण
	regulator_bulk_disable(ARRAY_SIZE(chip->regs), chip->regs);
	वापस err;
fail2:
	sysfs_हटाओ_group(&chip->client->dev.kobj,
			&bh1770_attribute_group);
fail1:
	अगर (chip->pdata->release_resources)
		chip->pdata->release_resources();
fail0:
	regulator_bulk_disable(ARRAY_SIZE(chip->regs), chip->regs);
	वापस err;
पूर्ण

अटल पूर्णांक bh1770_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा bh1770_chip *chip = i2c_get_clientdata(client);

	मुक्त_irq(client->irq, chip);

	sysfs_हटाओ_group(&chip->client->dev.kobj,
			&bh1770_attribute_group);

	अगर (chip->pdata->release_resources)
		chip->pdata->release_resources();

	cancel_delayed_work_sync(&chip->prox_work);

	अगर (!pm_runसमय_suspended(&client->dev))
		bh1770_chip_off(chip);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bh1770_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bh1770_chip *chip = i2c_get_clientdata(client);

	bh1770_chip_off(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक bh1770_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bh1770_chip *chip = i2c_get_clientdata(client);
	पूर्णांक ret = 0;

	bh1770_chip_on(chip);

	अगर (!pm_runसमय_suspended(dev)) अणु
		/*
		 * If we were enabled at suspend समय, it is expected
		 * everything works nice and smoothly
		 */
		ret = bh1770_lux_rate(chip, chip->lux_rate_index);
		ret |= bh1770_lux_पूर्णांकerrupt_control(chip, BH1770_ENABLE);

		/* This causes पूर्णांकerrupt after the next measurement cycle */
		bh1770_lux_update_thresholds(chip, BH1770_LUX_DEF_THRES,
					BH1770_LUX_DEF_THRES);
		/* Inक्रमm that we are रुकोing क्रम a result from ALS */
		chip->lux_रुको_result = true;
		bh1770_prox_mode_control(chip);
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bh1770_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bh1770_chip *chip = i2c_get_clientdata(client);

	bh1770_chip_off(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक bh1770_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bh1770_chip *chip = i2c_get_clientdata(client);

	bh1770_chip_on(chip);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id bh1770_id[] = अणु
	अणु"bh1770glc", 0 पूर्ण,
	अणु"sfh7770", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, bh1770_id);

अटल स्थिर काष्ठा dev_pm_ops bh1770_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(bh1770_suspend, bh1770_resume)
	SET_RUNTIME_PM_OPS(bh1770_runसमय_suspend, bh1770_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver bh1770_driver = अणु
	.driver	 = अणु
		.name	= "bh1770glc",
		.pm	= &bh1770_pm_ops,
	पूर्ण,
	.probe	  = bh1770_probe,
	.हटाओ	  = bh1770_हटाओ,
	.id_table = bh1770_id,
पूर्ण;

module_i2c_driver(bh1770_driver);

MODULE_DESCRIPTION("BH1770GLC / SFH7770 combined ALS and proximity sensor");
MODULE_AUTHOR("Samu Onkalo, Nokia Corporation");
MODULE_LICENSE("GPL v2");
