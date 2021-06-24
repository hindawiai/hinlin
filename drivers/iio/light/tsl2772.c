<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Device driver क्रम monitoring ambient light पूर्णांकensity in (lux) and proximity
 * detection (prox) within the TAOS TSL2571, TSL2671, TMD2671, TSL2771, TMD2771,
 * TSL2572, TSL2672, TMD2672, TSL2772, and TMD2772 devices.
 *
 * Copyright (c) 2012, TAOS Corporation.
 * Copyright (c) 2017-2018 Brian Masney <masneyb@onstation.org>
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/platक्रमm_data/tsl2772.h>
#समावेश <linux/regulator/consumer.h>

/* Cal defs */
#घोषणा PROX_STAT_CAL			0
#घोषणा PROX_STAT_SAMP			1
#घोषणा MAX_SAMPLES_CAL			200

/* TSL2772 Device ID */
#घोषणा TRITON_ID			0x00
#घोषणा SWORDFISH_ID			0x30
#घोषणा HALIBUT_ID			0x20

/* Lux calculation स्थिरants */
#घोषणा TSL2772_LUX_CALC_OVER_FLOW	65535

/*
 * TAOS Register definitions - Note: depending on device, some of these रेजिस्टर
 * are not used and the रेजिस्टर address is benign.
 */

/* Register offsets */
#घोषणा TSL2772_MAX_CONFIG_REG		16

/* Device Registers and Masks */
#घोषणा TSL2772_CNTRL			0x00
#घोषणा TSL2772_ALS_TIME		0X01
#घोषणा TSL2772_PRX_TIME		0x02
#घोषणा TSL2772_WAIT_TIME		0x03
#घोषणा TSL2772_ALS_MINTHRESHLO		0X04
#घोषणा TSL2772_ALS_MINTHRESHHI		0X05
#घोषणा TSL2772_ALS_MAXTHRESHLO		0X06
#घोषणा TSL2772_ALS_MAXTHRESHHI		0X07
#घोषणा TSL2772_PRX_MINTHRESHLO		0X08
#घोषणा TSL2772_PRX_MINTHRESHHI		0X09
#घोषणा TSL2772_PRX_MAXTHRESHLO		0X0A
#घोषणा TSL2772_PRX_MAXTHRESHHI		0X0B
#घोषणा TSL2772_PERSISTENCE		0x0C
#घोषणा TSL2772_ALS_PRX_CONFIG		0x0D
#घोषणा TSL2772_PRX_COUNT		0x0E
#घोषणा TSL2772_GAIN			0x0F
#घोषणा TSL2772_NOTUSED			0x10
#घोषणा TSL2772_REVID			0x11
#घोषणा TSL2772_CHIPID			0x12
#घोषणा TSL2772_STATUS			0x13
#घोषणा TSL2772_ALS_CHAN0LO		0x14
#घोषणा TSL2772_ALS_CHAN0HI		0x15
#घोषणा TSL2772_ALS_CHAN1LO		0x16
#घोषणा TSL2772_ALS_CHAN1HI		0x17
#घोषणा TSL2772_PRX_LO			0x18
#घोषणा TSL2772_PRX_HI			0x19

/* tsl2772 cmd reg masks */
#घोषणा TSL2772_CMD_REG			0x80
#घोषणा TSL2772_CMD_SPL_FN		0x60
#घोषणा TSL2772_CMD_REPEAT_PROTO	0x00
#घोषणा TSL2772_CMD_AUTOINC_PROTO	0x20

#घोषणा TSL2772_CMD_PROX_INT_CLR	0X05
#घोषणा TSL2772_CMD_ALS_INT_CLR		0x06
#घोषणा TSL2772_CMD_PROXALS_INT_CLR	0X07

/* tsl2772 cntrl reg masks */
#घोषणा TSL2772_CNTL_ADC_ENBL		0x02
#घोषणा TSL2772_CNTL_PWR_ON		0x01

/* tsl2772 status reg masks */
#घोषणा TSL2772_STA_ADC_VALID		0x01
#घोषणा TSL2772_STA_PRX_VALID		0x02
#घोषणा TSL2772_STA_ADC_PRX_VALID	(TSL2772_STA_ADC_VALID | \
					 TSL2772_STA_PRX_VALID)
#घोषणा TSL2772_STA_ALS_INTR		0x10
#घोषणा TSL2772_STA_PRX_INTR		0x20

/* tsl2772 cntrl reg masks */
#घोषणा TSL2772_CNTL_REG_CLEAR		0x00
#घोषणा TSL2772_CNTL_PROX_INT_ENBL	0X20
#घोषणा TSL2772_CNTL_ALS_INT_ENBL	0X10
#घोषणा TSL2772_CNTL_WAIT_TMR_ENBL	0X08
#घोषणा TSL2772_CNTL_PROX_DET_ENBL	0X04
#घोषणा TSL2772_CNTL_PWRON		0x01
#घोषणा TSL2772_CNTL_ALSPON_ENBL	0x03
#घोषणा TSL2772_CNTL_INTALSPON_ENBL	0x13
#घोषणा TSL2772_CNTL_PROXPON_ENBL	0x0F
#घोषणा TSL2772_CNTL_INTPROXPON_ENBL	0x2F

#घोषणा TSL2772_ALS_GAIN_TRIM_MIN	250
#घोषणा TSL2772_ALS_GAIN_TRIM_MAX	4000

#घोषणा TSL2772_MAX_PROX_LEDS		2

#घोषणा TSL2772_BOOT_MIN_SLEEP_TIME	10000
#घोषणा TSL2772_BOOT_MAX_SLEEP_TIME	28000

/* Device family members */
क्रमागत अणु
	tsl2571,
	tsl2671,
	पंचांगd2671,
	tsl2771,
	पंचांगd2771,
	tsl2572,
	tsl2672,
	पंचांगd2672,
	tsl2772,
	पंचांगd2772,
	apds9930,
पूर्ण;

क्रमागत अणु
	TSL2772_CHIP_UNKNOWN = 0,
	TSL2772_CHIP_WORKING = 1,
	TSL2772_CHIP_SUSPENDED = 2
पूर्ण;

क्रमागत अणु
	TSL2772_SUPPLY_VDD = 0,
	TSL2772_SUPPLY_VDDIO = 1,
	TSL2772_NUM_SUPPLIES = 2
पूर्ण;

/* Per-device data */
काष्ठा tsl2772_als_info अणु
	u16 als_ch0;
	u16 als_ch1;
	u16 lux;
पूर्ण;

काष्ठा tsl2772_chip_info अणु
	पूर्णांक chan_table_elements;
	काष्ठा iio_chan_spec channel_with_events[4];
	काष्ठा iio_chan_spec channel_without_events[4];
	स्थिर काष्ठा iio_info *info;
पूर्ण;

अटल स्थिर पूर्णांक tsl2772_led_currents[][2] = अणु
	अणु 100000, TSL2772_100_mA पूर्ण,
	अणु  50000, TSL2772_50_mA पूर्ण,
	अणु  25000, TSL2772_25_mA पूर्ण,
	अणु  13000, TSL2772_13_mA पूर्ण,
	अणु      0, 0 पूर्ण
पूर्ण;

काष्ठा tsl2772_chip अणु
	kernel_uदीर्घ_t id;
	काष्ठा mutex prox_mutex;
	काष्ठा mutex als_mutex;
	काष्ठा i2c_client *client;
	काष्ठा regulator_bulk_data supplies[TSL2772_NUM_SUPPLIES];
	u16 prox_data;
	काष्ठा tsl2772_als_info als_cur_info;
	काष्ठा tsl2772_settings settings;
	काष्ठा tsl2772_platक्रमm_data *pdata;
	पूर्णांक als_gain_समय_scale;
	पूर्णांक als_saturation;
	पूर्णांक tsl2772_chip_status;
	u8 tsl2772_config[TSL2772_MAX_CONFIG_REG];
	स्थिर काष्ठा tsl2772_chip_info	*chip_info;
	स्थिर काष्ठा iio_info *info;
	s64 event_बारtamp;
	/*
	 * This काष्ठाure is पूर्णांकentionally large to accommodate
	 * updates via sysfs.
	 * Sized to 9 = max 8 segments + 1 termination segment
	 */
	काष्ठा tsl2772_lux tsl2772_device_lux[TSL2772_MAX_LUX_TABLE_SIZE];
पूर्ण;

/*
 * Dअगरferent devices require dअगरferent coefficents, and these numbers were
 * derived from the 'Lux Equation' section of the various device datasheets.
 * All of these coefficients assume a Glass Attenuation (GA) factor of 1.
 * The coefficients are multiplied by 1000 to aव्योम भग्नing poपूर्णांक operations.
 * The two rows in each table correspond to the Lux1 and Lux2 equations from
 * the datasheets.
 */
अटल स्थिर काष्ठा tsl2772_lux tsl2x71_lux_table[TSL2772_DEF_LUX_TABLE_SZ] = अणु
	अणु 53000, 106000 पूर्ण,
	अणु 31800,  53000 पूर्ण,
	अणु 0,          0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tsl2772_lux पंचांगd2x71_lux_table[TSL2772_DEF_LUX_TABLE_SZ] = अणु
	अणु 24000,  48000 पूर्ण,
	अणु 14400,  24000 पूर्ण,
	अणु 0,          0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tsl2772_lux tsl2x72_lux_table[TSL2772_DEF_LUX_TABLE_SZ] = अणु
	अणु 60000, 112200 पूर्ण,
	अणु 37800,  60000 पूर्ण,
	अणु     0,      0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tsl2772_lux पंचांगd2x72_lux_table[TSL2772_DEF_LUX_TABLE_SZ] = अणु
	अणु 20000,  35000 पूर्ण,
	अणु 12600,  20000 पूर्ण,
	अणु     0,      0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tsl2772_lux apds9930_lux_table[TSL2772_DEF_LUX_TABLE_SZ] = अणु
	अणु 52000,  96824 पूर्ण,
	अणु 38792,  67132 पूर्ण,
	अणु     0,      0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tsl2772_lux *tsl2772_शेष_lux_table_group[] = अणु
	[tsl2571] = tsl2x71_lux_table,
	[tsl2671] = tsl2x71_lux_table,
	[पंचांगd2671] = पंचांगd2x71_lux_table,
	[tsl2771] = tsl2x71_lux_table,
	[पंचांगd2771] = पंचांगd2x71_lux_table,
	[tsl2572] = tsl2x72_lux_table,
	[tsl2672] = tsl2x72_lux_table,
	[पंचांगd2672] = पंचांगd2x72_lux_table,
	[tsl2772] = tsl2x72_lux_table,
	[पंचांगd2772] = पंचांगd2x72_lux_table,
	[apds9930] = apds9930_lux_table,
पूर्ण;

अटल स्थिर काष्ठा tsl2772_settings tsl2772_शेष_settings = अणु
	.als_समय = 255, /* 2.72 / 2.73 ms */
	.als_gain = 0,
	.prox_समय = 255, /* 2.72 / 2.73 ms */
	.prox_gain = 0,
	.रुको_समय = 255,
	.als_prox_config = 0,
	.als_gain_trim = 1000,
	.als_cal_target = 150,
	.als_persistence = 1,
	.als_पूर्णांकerrupt_en = false,
	.als_thresh_low = 200,
	.als_thresh_high = 256,
	.prox_persistence = 1,
	.prox_पूर्णांकerrupt_en = false,
	.prox_thres_low  = 0,
	.prox_thres_high = 512,
	.prox_max_samples_cal = 30,
	.prox_pulse_count = 8,
	.prox_diode = TSL2772_DIODE1,
	.prox_घातer = TSL2772_100_mA
पूर्ण;

अटल स्थिर s16 tsl2772_als_gain[] = अणु
	1,
	8,
	16,
	120
पूर्ण;

अटल स्थिर s16 tsl2772_prox_gain[] = अणु
	1,
	2,
	4,
	8
पूर्ण;

अटल स्थिर पूर्णांक tsl2772_पूर्णांक_समय_avail[][6] = अणु
	[tsl2571] = अणु 0, 2720, 0, 2720, 0, 696000 पूर्ण,
	[tsl2671] = अणु 0, 2720, 0, 2720, 0, 696000 पूर्ण,
	[पंचांगd2671] = अणु 0, 2720, 0, 2720, 0, 696000 पूर्ण,
	[tsl2771] = अणु 0, 2720, 0, 2720, 0, 696000 पूर्ण,
	[पंचांगd2771] = अणु 0, 2720, 0, 2720, 0, 696000 पूर्ण,
	[tsl2572] = अणु 0, 2730, 0, 2730, 0, 699000 पूर्ण,
	[tsl2672] = अणु 0, 2730, 0, 2730, 0, 699000 पूर्ण,
	[पंचांगd2672] = अणु 0, 2730, 0, 2730, 0, 699000 पूर्ण,
	[tsl2772] = अणु 0, 2730, 0, 2730, 0, 699000 पूर्ण,
	[पंचांगd2772] = अणु 0, 2730, 0, 2730, 0, 699000 पूर्ण,
	[apds9930] = अणु 0, 2730, 0, 2730, 0, 699000 पूर्ण,
पूर्ण;

अटल पूर्णांक tsl2772_पूर्णांक_calibscale_avail[] = अणु 1, 8, 16, 120 पूर्ण;

अटल पूर्णांक tsl2772_prox_calibscale_avail[] = अणु 1, 2, 4, 8 पूर्ण;

/* Channel variations */
क्रमागत अणु
	ALS,
	PRX,
	ALSPRX,
	PRX2,
	ALSPRX2,
पूर्ण;

अटल स्थिर u8 device_channel_config[] = अणु
	[tsl2571] = ALS,
	[tsl2671] = PRX,
	[पंचांगd2671] = PRX,
	[tsl2771] = ALSPRX,
	[पंचांगd2771] = ALSPRX,
	[tsl2572] = ALS,
	[tsl2672] = PRX2,
	[पंचांगd2672] = PRX2,
	[tsl2772] = ALSPRX2,
	[पंचांगd2772] = ALSPRX2,
	[apds9930] = ALSPRX2,
पूर्ण;

अटल पूर्णांक tsl2772_पढ़ो_status(काष्ठा tsl2772_chip *chip)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(chip->client,
				       TSL2772_CMD_REG | TSL2772_STATUS);
	अगर (ret < 0)
		dev_err(&chip->client->dev,
			"%s: failed to read STATUS register: %d\n", __func__,
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2772_ग_लिखो_control_reg(काष्ठा tsl2772_chip *chip, u8 data)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
					TSL2772_CMD_REG | TSL2772_CNTRL, data);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev,
			"%s: failed to write to control register %x: %d\n",
			__func__, data, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2772_पढ़ो_स्वतःinc_regs(काष्ठा tsl2772_chip *chip, पूर्णांक lower_reg,
				     पूर्णांक upper_reg)
अणु
	u8 buf[2];
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte(chip->client,
				   TSL2772_CMD_REG | TSL2772_CMD_AUTOINC_PROTO |
				   lower_reg);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev,
			"%s: failed to enable auto increment protocol: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(chip->client,
				       TSL2772_CMD_REG | lower_reg);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev,
			"%s: failed to read from register %x: %d\n", __func__,
			lower_reg, ret);
		वापस ret;
	पूर्ण
	buf[0] = ret;

	ret = i2c_smbus_पढ़ो_byte_data(chip->client,
				       TSL2772_CMD_REG | upper_reg);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev,
			"%s: failed to read from register %x: %d\n", __func__,
			upper_reg, ret);
		वापस ret;
	पूर्ण
	buf[1] = ret;

	ret = i2c_smbus_ग_लिखो_byte(chip->client,
				   TSL2772_CMD_REG | TSL2772_CMD_REPEAT_PROTO |
				   lower_reg);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev,
			"%s: failed to enable repeated byte protocol: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	वापस le16_to_cpup((स्थिर __le16 *)&buf[0]);
पूर्ण

/**
 * tsl2772_get_lux() - Reads and calculates current lux value.
 * @indio_dev:	poपूर्णांकer to IIO device
 *
 * The raw ch0 and ch1 values of the ambient light sensed in the last
 * पूर्णांकegration cycle are पढ़ो from the device. The raw values are multiplied
 * by a device-specअगरic scale factor, and भागided by the पूर्णांकegration समय and
 * device gain. The code supports multiple lux equations through the lux table
 * coefficients. A lux gain trim is applied to each lux equation, and then the
 * maximum lux within the पूर्णांकerval 0..65535 is selected.
 */
अटल पूर्णांक tsl2772_get_lux(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	काष्ठा tsl2772_lux *p;
	पूर्णांक max_lux, ret;
	bool overflow;

	mutex_lock(&chip->als_mutex);

	अगर (chip->tsl2772_chip_status != TSL2772_CHIP_WORKING) अणु
		dev_err(&chip->client->dev, "%s: device is not enabled\n",
			__func__);
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	ret = tsl2772_पढ़ो_status(chip);
	अगर (ret < 0)
		जाओ out_unlock;

	अगर (!(ret & TSL2772_STA_ADC_VALID)) अणु
		dev_err(&chip->client->dev,
			"%s: data not valid yet\n", __func__);
		ret = chip->als_cur_info.lux; /* वापस LAST VALUE */
		जाओ out_unlock;
	पूर्ण

	ret = tsl2772_पढ़ो_स्वतःinc_regs(chip, TSL2772_ALS_CHAN0LO,
					TSL2772_ALS_CHAN0HI);
	अगर (ret < 0)
		जाओ out_unlock;
	chip->als_cur_info.als_ch0 = ret;

	ret = tsl2772_पढ़ो_स्वतःinc_regs(chip, TSL2772_ALS_CHAN1LO,
					TSL2772_ALS_CHAN1HI);
	अगर (ret < 0)
		जाओ out_unlock;
	chip->als_cur_info.als_ch1 = ret;

	अगर (chip->als_cur_info.als_ch0 >= chip->als_saturation) अणु
		max_lux = TSL2772_LUX_CALC_OVER_FLOW;
		जाओ update_काष्ठा_with_max_lux;
	पूर्ण

	अगर (!chip->als_cur_info.als_ch0) अणु
		/* have no data, so वापस LAST VALUE */
		ret = chip->als_cur_info.lux;
		जाओ out_unlock;
	पूर्ण

	max_lux = 0;
	overflow = false;
	क्रम (p = (काष्ठा tsl2772_lux *)chip->tsl2772_device_lux; p->ch0 != 0;
	     p++) अणु
		पूर्णांक lux;

		lux = ((chip->als_cur_info.als_ch0 * p->ch0) -
		       (chip->als_cur_info.als_ch1 * p->ch1)) /
			chip->als_gain_समय_scale;

		/*
		 * The als_gain_trim can have a value within the range 250..4000
		 * and is a multiplier क्रम the lux. A trim of 1000 makes no
		 * changes to the lux, less than 1000 scales it करोwn, and
		 * greater than 1000 scales it up.
		 */
		lux = (lux * chip->settings.als_gain_trim) / 1000;

		अगर (lux > TSL2772_LUX_CALC_OVER_FLOW) अणु
			overflow = true;
			जारी;
		पूर्ण

		max_lux = max(max_lux, lux);
	पूर्ण

	अगर (overflow && max_lux == 0)
		max_lux = TSL2772_LUX_CALC_OVER_FLOW;

update_काष्ठा_with_max_lux:
	chip->als_cur_info.lux = max_lux;
	ret = max_lux;

out_unlock:
	mutex_unlock(&chip->als_mutex);

	वापस ret;
पूर्ण

/**
 * tsl2772_get_prox() - Reads proximity data रेजिस्टरs and updates
 *                      chip->prox_data.
 *
 * @indio_dev:	poपूर्णांकer to IIO device
 */
अटल पूर्णांक tsl2772_get_prox(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&chip->prox_mutex);

	ret = tsl2772_पढ़ो_status(chip);
	अगर (ret < 0)
		जाओ prox_poll_err;

	चयन (chip->id) अणु
	हाल tsl2571:
	हाल tsl2671:
	हाल पंचांगd2671:
	हाल tsl2771:
	हाल पंचांगd2771:
		अगर (!(ret & TSL2772_STA_ADC_VALID)) अणु
			ret = -EINVAL;
			जाओ prox_poll_err;
		पूर्ण
		अवरोध;
	हाल tsl2572:
	हाल tsl2672:
	हाल पंचांगd2672:
	हाल tsl2772:
	हाल पंचांगd2772:
	हाल apds9930:
		अगर (!(ret & TSL2772_STA_PRX_VALID)) अणु
			ret = -EINVAL;
			जाओ prox_poll_err;
		पूर्ण
		अवरोध;
	पूर्ण

	ret = tsl2772_पढ़ो_स्वतःinc_regs(chip, TSL2772_PRX_LO, TSL2772_PRX_HI);
	अगर (ret < 0)
		जाओ prox_poll_err;
	chip->prox_data = ret;

prox_poll_err:
	mutex_unlock(&chip->prox_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2772_पढ़ो_prox_led_current(काष्ठा tsl2772_chip *chip)
अणु
	काष्ठा device_node *of_node = chip->client->dev.of_node;
	पूर्णांक ret, पंचांगp, i;

	ret = of_property_पढ़ो_u32(of_node, "led-max-microamp", &पंचांगp);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; tsl2772_led_currents[i][0] != 0; i++) अणु
		अगर (पंचांगp == tsl2772_led_currents[i][0]) अणु
			chip->settings.prox_घातer = tsl2772_led_currents[i][1];
			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(&chip->client->dev, "Invalid value %d for led-max-microamp\n",
		पंचांगp);

	वापस -EINVAL;

पूर्ण

अटल पूर्णांक tsl2772_पढ़ो_prox_diodes(काष्ठा tsl2772_chip *chip)
अणु
	काष्ठा device_node *of_node = chip->client->dev.of_node;
	पूर्णांक i, ret, num_leds, prox_diode_mask;
	u32 leds[TSL2772_MAX_PROX_LEDS];

	ret = of_property_count_u32_elems(of_node, "amstaos,proximity-diodes");
	अगर (ret < 0)
		वापस ret;

	num_leds = ret;
	अगर (num_leds > TSL2772_MAX_PROX_LEDS)
		num_leds = TSL2772_MAX_PROX_LEDS;

	ret = of_property_पढ़ो_u32_array(of_node, "amstaos,proximity-diodes",
					 leds, num_leds);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev,
			"Invalid value for amstaos,proximity-diodes: %d.\n",
			ret);
		वापस ret;
	पूर्ण

	prox_diode_mask = 0;
	क्रम (i = 0; i < num_leds; i++) अणु
		अगर (leds[i] == 0)
			prox_diode_mask |= TSL2772_DIODE0;
		अन्यथा अगर (leds[i] == 1)
			prox_diode_mask |= TSL2772_DIODE1;
		अन्यथा अणु
			dev_err(&chip->client->dev,
				"Invalid value %d in amstaos,proximity-diodes.\n",
				leds[i]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tsl2772_parse_dt(काष्ठा tsl2772_chip *chip)
अणु
	tsl2772_पढ़ो_prox_led_current(chip);
	tsl2772_पढ़ो_prox_diodes(chip);
पूर्ण

/**
 * tsl2772_शेषs() - Populates the device nominal operating parameters
 *                      with those provided by a 'platform' data काष्ठा or
 *                      with prefined शेषs.
 *
 * @chip:               poपूर्णांकer to device काष्ठाure.
 */
अटल व्योम tsl2772_शेषs(काष्ठा tsl2772_chip *chip)
अणु
	/* If Operational settings defined अन्यथाwhere.. */
	अगर (chip->pdata && chip->pdata->platक्रमm_शेष_settings)
		स_नकल(&chip->settings, chip->pdata->platक्रमm_शेष_settings,
		       माप(tsl2772_शेष_settings));
	अन्यथा
		स_नकल(&chip->settings, &tsl2772_शेष_settings,
		       माप(tsl2772_शेष_settings));

	/* Load up the proper lux table. */
	अगर (chip->pdata && chip->pdata->platक्रमm_lux_table[0].ch0 != 0)
		स_नकल(chip->tsl2772_device_lux,
		       chip->pdata->platक्रमm_lux_table,
		       माप(chip->pdata->platक्रमm_lux_table));
	अन्यथा
		स_नकल(chip->tsl2772_device_lux,
		       tsl2772_शेष_lux_table_group[chip->id],
		       TSL2772_DEFAULT_TABLE_BYTES);

	tsl2772_parse_dt(chip);
पूर्ण

/**
 * tsl2772_als_calibrate() -	Obtain single पढ़ोing and calculate
 *                              the als_gain_trim.
 *
 * @indio_dev:	poपूर्णांकer to IIO device
 */
अटल पूर्णांक tsl2772_als_calibrate(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret, lux_val;

	ret = i2c_smbus_पढ़ो_byte_data(chip->client,
				       TSL2772_CMD_REG | TSL2772_CNTRL);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev,
			"%s: failed to read from the CNTRL register\n",
			__func__);
		वापस ret;
	पूर्ण

	अगर ((ret & (TSL2772_CNTL_ADC_ENBL | TSL2772_CNTL_PWR_ON))
			!= (TSL2772_CNTL_ADC_ENBL | TSL2772_CNTL_PWR_ON)) अणु
		dev_err(&chip->client->dev,
			"%s: Device is not powered on and/or ADC is not enabled\n",
			__func__);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर ((ret & TSL2772_STA_ADC_VALID) != TSL2772_STA_ADC_VALID) अणु
		dev_err(&chip->client->dev,
			"%s: The two ADC channels have not completed an integration cycle\n",
			__func__);
		वापस -ENODATA;
	पूर्ण

	lux_val = tsl2772_get_lux(indio_dev);
	अगर (lux_val < 0) अणु
		dev_err(&chip->client->dev,
			"%s: failed to get lux\n", __func__);
		वापस lux_val;
	पूर्ण
	अगर (lux_val == 0)
		वापस -दुस्फल;

	ret = (chip->settings.als_cal_target * chip->settings.als_gain_trim) /
			lux_val;
	अगर (ret < TSL2772_ALS_GAIN_TRIM_MIN || ret > TSL2772_ALS_GAIN_TRIM_MAX)
		वापस -दुस्फल;

	chip->settings.als_gain_trim = ret;

	वापस ret;
पूर्ण

अटल व्योम tsl2772_disable_regulators_action(व्योम *_data)
अणु
	काष्ठा tsl2772_chip *chip = _data;

	regulator_bulk_disable(ARRAY_SIZE(chip->supplies), chip->supplies);
पूर्ण

अटल पूर्णांक tsl2772_chip_on(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret, i, als_count, als_समय_us;
	u8 *dev_reg, reg_val;

	/* Non calculated parameters */
	chip->tsl2772_config[TSL2772_ALS_TIME] = chip->settings.als_समय;
	chip->tsl2772_config[TSL2772_PRX_TIME] = chip->settings.prox_समय;
	chip->tsl2772_config[TSL2772_WAIT_TIME] = chip->settings.रुको_समय;
	chip->tsl2772_config[TSL2772_ALS_PRX_CONFIG] =
		chip->settings.als_prox_config;

	chip->tsl2772_config[TSL2772_ALS_MINTHRESHLO] =
		(chip->settings.als_thresh_low) & 0xFF;
	chip->tsl2772_config[TSL2772_ALS_MINTHRESHHI] =
		(chip->settings.als_thresh_low >> 8) & 0xFF;
	chip->tsl2772_config[TSL2772_ALS_MAXTHRESHLO] =
		(chip->settings.als_thresh_high) & 0xFF;
	chip->tsl2772_config[TSL2772_ALS_MAXTHRESHHI] =
		(chip->settings.als_thresh_high >> 8) & 0xFF;
	chip->tsl2772_config[TSL2772_PERSISTENCE] =
		(chip->settings.prox_persistence & 0xFF) << 4 |
		(chip->settings.als_persistence & 0xFF);

	chip->tsl2772_config[TSL2772_PRX_COUNT] =
			chip->settings.prox_pulse_count;
	chip->tsl2772_config[TSL2772_PRX_MINTHRESHLO] =
			(chip->settings.prox_thres_low) & 0xFF;
	chip->tsl2772_config[TSL2772_PRX_MINTHRESHHI] =
			(chip->settings.prox_thres_low >> 8) & 0xFF;
	chip->tsl2772_config[TSL2772_PRX_MAXTHRESHLO] =
			(chip->settings.prox_thres_high) & 0xFF;
	chip->tsl2772_config[TSL2772_PRX_MAXTHRESHHI] =
			(chip->settings.prox_thres_high >> 8) & 0xFF;

	/* and make sure we're not alपढ़ोy on */
	अगर (chip->tsl2772_chip_status == TSL2772_CHIP_WORKING) अणु
		/* अगर क्रमcing a रेजिस्टर update - turn off, then on */
		dev_info(&chip->client->dev, "device is already enabled\n");
		वापस -EINVAL;
	पूर्ण

	/* Set the gain based on tsl2772_settings काष्ठा */
	chip->tsl2772_config[TSL2772_GAIN] =
		(chip->settings.als_gain & 0xFF) |
		((chip->settings.prox_gain & 0xFF) << 2) |
		(chip->settings.prox_diode << 4) |
		(chip->settings.prox_घातer << 6);

	/* set chip समय scaling and saturation */
	als_count = 256 - chip->settings.als_समय;
	als_समय_us = als_count * tsl2772_पूर्णांक_समय_avail[chip->id][3];
	chip->als_saturation = als_count * 768; /* 75% of full scale */
	chip->als_gain_समय_scale = als_समय_us *
		tsl2772_als_gain[chip->settings.als_gain];

	/*
	 * TSL2772 Specअगरic घातer-on / adc enable sequence
	 * Power on the device 1st.
	 */
	ret = tsl2772_ग_लिखो_control_reg(chip, TSL2772_CNTL_PWR_ON);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Use the following shaकरोw copy क्रम our delay beक्रमe enabling ADC.
	 * Write all the रेजिस्टरs.
	 */
	क्रम (i = 0, dev_reg = chip->tsl2772_config;
			i < TSL2772_MAX_CONFIG_REG; i++) अणु
		पूर्णांक reg = TSL2772_CMD_REG + i;

		ret = i2c_smbus_ग_लिखो_byte_data(chip->client, reg,
						*dev_reg++);
		अगर (ret < 0) अणु
			dev_err(&chip->client->dev,
				"%s: failed to write to register %x: %d\n",
				__func__, reg, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Power-on settling समय */
	usleep_range(3000, 3500);

	reg_val = TSL2772_CNTL_PWR_ON | TSL2772_CNTL_ADC_ENBL |
		  TSL2772_CNTL_PROX_DET_ENBL;
	अगर (chip->settings.als_पूर्णांकerrupt_en)
		reg_val |= TSL2772_CNTL_ALS_INT_ENBL;
	अगर (chip->settings.prox_पूर्णांकerrupt_en)
		reg_val |= TSL2772_CNTL_PROX_INT_ENBL;

	ret = tsl2772_ग_लिखो_control_reg(chip, reg_val);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte(chip->client,
				   TSL2772_CMD_REG | TSL2772_CMD_SPL_FN |
				   TSL2772_CMD_PROXALS_INT_CLR);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev,
			"%s: failed to clear interrupt status: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	chip->tsl2772_chip_status = TSL2772_CHIP_WORKING;

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2772_chip_off(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);

	/* turn device off */
	chip->tsl2772_chip_status = TSL2772_CHIP_SUSPENDED;
	वापस tsl2772_ग_लिखो_control_reg(chip, 0x00);
पूर्ण

अटल व्योम tsl2772_chip_off_action(व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;

	tsl2772_chip_off(indio_dev);
पूर्ण

/**
 * tsl2772_invoke_change - घातer cycle the device to implement the user
 *                         parameters
 * @indio_dev:	poपूर्णांकer to IIO device
 *
 * Obtain and lock both ALS and PROX resources, determine and save device state
 * (On/Off), cycle device to implement updated parameter, put device back पूर्णांकo
 * proper state, and unlock resource.
 */
अटल पूर्णांक tsl2772_invoke_change(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	पूर्णांक device_status = chip->tsl2772_chip_status;
	पूर्णांक ret;

	mutex_lock(&chip->als_mutex);
	mutex_lock(&chip->prox_mutex);

	अगर (device_status == TSL2772_CHIP_WORKING) अणु
		ret = tsl2772_chip_off(indio_dev);
		अगर (ret < 0)
			जाओ unlock;
	पूर्ण

	ret = tsl2772_chip_on(indio_dev);

unlock:
	mutex_unlock(&chip->prox_mutex);
	mutex_unlock(&chip->als_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2772_prox_cal(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	पूर्णांक prox_history[MAX_SAMPLES_CAL + 1];
	पूर्णांक i, ret, mean, max, sample_sum;

	अगर (chip->settings.prox_max_samples_cal < 1 ||
	    chip->settings.prox_max_samples_cal > MAX_SAMPLES_CAL)
		वापस -EINVAL;

	क्रम (i = 0; i < chip->settings.prox_max_samples_cal; i++) अणु
		usleep_range(15000, 17500);
		ret = tsl2772_get_prox(indio_dev);
		अगर (ret < 0)
			वापस ret;

		prox_history[i] = chip->prox_data;
	पूर्ण

	sample_sum = 0;
	max = पूर्णांक_न्यून;
	क्रम (i = 0; i < chip->settings.prox_max_samples_cal; i++) अणु
		sample_sum += prox_history[i];
		max = max(max, prox_history[i]);
	पूर्ण
	mean = sample_sum / chip->settings.prox_max_samples_cal;

	chip->settings.prox_thres_high = (max << 1) - mean;

	वापस tsl2772_invoke_change(indio_dev);
पूर्ण

अटल पूर्णांक tsl2772_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			      दीर्घ mask)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (chan->type == IIO_INTENSITY) अणु
			*length = ARRAY_SIZE(tsl2772_पूर्णांक_calibscale_avail);
			*vals = tsl2772_पूर्णांक_calibscale_avail;
		पूर्ण अन्यथा अणु
			*length = ARRAY_SIZE(tsl2772_prox_calibscale_avail);
			*vals = tsl2772_prox_calibscale_avail;
		पूर्ण
		*type = IIO_VAL_INT;
		वापस IIO_AVAIL_LIST;
	हाल IIO_CHAN_INFO_INT_TIME:
		*length = ARRAY_SIZE(tsl2772_पूर्णांक_समय_avail[chip->id]);
		*vals = tsl2772_पूर्णांक_समय_avail[chip->id];
		*type = IIO_VAL_INT_PLUS_MICRO;
		वापस IIO_AVAIL_RANGE;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार in_illuminance0_target_input_show(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(dev_to_iio_dev(dev));

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", chip->settings.als_cal_target);
पूर्ण

अटल sमाप_प्रकार in_illuminance0_target_input_store(काष्ठा device *dev,
						  काष्ठा device_attribute *attr,
						  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	u16 value;
	पूर्णांक ret;

	अगर (kstrtou16(buf, 0, &value))
		वापस -EINVAL;

	chip->settings.als_cal_target = value;
	ret = tsl2772_invoke_change(indio_dev);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार in_illuminance0_calibrate_store(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	bool value;
	पूर्णांक ret;

	अगर (kstrtobool(buf, &value) || !value)
		वापस -EINVAL;

	ret = tsl2772_als_calibrate(indio_dev);
	अगर (ret < 0)
		वापस ret;

	ret = tsl2772_invoke_change(indio_dev);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार in_illuminance0_lux_table_show(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(dev_to_iio_dev(dev));
	पूर्णांक i = 0;
	पूर्णांक offset = 0;

	जबतक (i < TSL2772_MAX_LUX_TABLE_SIZE) अणु
		offset += scnम_लिखो(buf + offset, PAGE_SIZE - offset, "%u,%u,",
			chip->tsl2772_device_lux[i].ch0,
			chip->tsl2772_device_lux[i].ch1);
		अगर (chip->tsl2772_device_lux[i].ch0 == 0) अणु
			/*
			 * We just prपूर्णांकed the first "0" entry.
			 * Now get rid of the extra "," and अवरोध.
			 */
			offset--;
			अवरोध;
		पूर्ण
		i++;
	पूर्ण

	offset += scnम_लिखो(buf + offset, PAGE_SIZE - offset, "\n");
	वापस offset;
पूर्ण

अटल sमाप_प्रकार in_illuminance0_lux_table_store(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	पूर्णांक value[ARRAY_SIZE(chip->tsl2772_device_lux) * 2 + 1];
	पूर्णांक n, ret;

	get_options(buf, ARRAY_SIZE(value), value);

	/*
	 * We now have an array of पूर्णांकs starting at value[1], and
	 * क्रमागतerated by value[0].
	 * We expect each group of two पूर्णांकs to be one table entry,
	 * and the last table entry is all 0.
	 */
	n = value[0];
	अगर ((n % 2) || n < 4 ||
	    n > ((ARRAY_SIZE(chip->tsl2772_device_lux) - 1) * 2))
		वापस -EINVAL;

	अगर ((value[(n - 1)] | value[n]) != 0)
		वापस -EINVAL;

	अगर (chip->tsl2772_chip_status == TSL2772_CHIP_WORKING) अणु
		ret = tsl2772_chip_off(indio_dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Zero out the table */
	स_रखो(chip->tsl2772_device_lux, 0, माप(chip->tsl2772_device_lux));
	स_नकल(chip->tsl2772_device_lux, &value[1], (value[0] * 4));

	ret = tsl2772_invoke_change(indio_dev);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार in_proximity0_calibrate_store(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	bool value;
	पूर्णांक ret;

	अगर (kstrtobool(buf, &value) || !value)
		वापस -EINVAL;

	ret = tsl2772_prox_cal(indio_dev);
	अगर (ret < 0)
		वापस ret;

	ret = tsl2772_invoke_change(indio_dev);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण

अटल पूर्णांक tsl2772_पढ़ो_पूर्णांकerrupt_config(काष्ठा iio_dev *indio_dev,
					 स्थिर काष्ठा iio_chan_spec *chan,
					 क्रमागत iio_event_type type,
					 क्रमागत iio_event_direction dir)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);

	अगर (chan->type == IIO_INTENSITY)
		वापस chip->settings.als_पूर्णांकerrupt_en;
	अन्यथा
		वापस chip->settings.prox_पूर्णांकerrupt_en;
पूर्ण

अटल पूर्णांक tsl2772_ग_लिखो_पूर्णांकerrupt_config(काष्ठा iio_dev *indio_dev,
					  स्थिर काष्ठा iio_chan_spec *chan,
					  क्रमागत iio_event_type type,
					  क्रमागत iio_event_direction dir,
					  पूर्णांक val)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);

	अगर (chan->type == IIO_INTENSITY)
		chip->settings.als_पूर्णांकerrupt_en = val ? true : false;
	अन्यथा
		chip->settings.prox_पूर्णांकerrupt_en = val ? true : false;

	वापस tsl2772_invoke_change(indio_dev);
पूर्ण

अटल पूर्णांक tsl2772_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir,
				     क्रमागत iio_event_info info,
				     पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL, count, persistence;
	u8 समय;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		अगर (chan->type == IIO_INTENSITY) अणु
			चयन (dir) अणु
			हाल IIO_EV_सूची_RISING:
				chip->settings.als_thresh_high = val;
				ret = 0;
				अवरोध;
			हाल IIO_EV_सूची_FALLING:
				chip->settings.als_thresh_low = val;
				ret = 0;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (dir) अणु
			हाल IIO_EV_सूची_RISING:
				chip->settings.prox_thres_high = val;
				ret = 0;
				अवरोध;
			हाल IIO_EV_सूची_FALLING:
				chip->settings.prox_thres_low = val;
				ret = 0;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IIO_EV_INFO_PERIOD:
		अगर (chan->type == IIO_INTENSITY)
			समय = chip->settings.als_समय;
		अन्यथा
			समय = chip->settings.prox_समय;

		count = 256 - समय;
		persistence = ((val * 1000000) + val2) /
			(count * tsl2772_पूर्णांक_समय_avail[chip->id][3]);

		अगर (chan->type == IIO_INTENSITY) अणु
			/* ALS filter values are 1, 2, 3, 5, 10, 15, ..., 60 */
			अगर (persistence > 3)
				persistence = (persistence / 5) + 3;

			chip->settings.als_persistence = persistence;
		पूर्ण अन्यथा अणु
			chip->settings.prox_persistence = persistence;
		पूर्ण

		ret = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	वापस tsl2772_invoke_change(indio_dev);
पूर्ण

अटल पूर्णांक tsl2772_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir,
				    क्रमागत iio_event_info info,
				    पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	पूर्णांक filter_delay, persistence;
	u8 समय;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		अगर (chan->type == IIO_INTENSITY) अणु
			चयन (dir) अणु
			हाल IIO_EV_सूची_RISING:
				*val = chip->settings.als_thresh_high;
				वापस IIO_VAL_INT;
			हाल IIO_EV_सूची_FALLING:
				*val = chip->settings.als_thresh_low;
				वापस IIO_VAL_INT;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (dir) अणु
			हाल IIO_EV_सूची_RISING:
				*val = chip->settings.prox_thres_high;
				वापस IIO_VAL_INT;
			हाल IIO_EV_सूची_FALLING:
				*val = chip->settings.prox_thres_low;
				वापस IIO_VAL_INT;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IIO_EV_INFO_PERIOD:
		अगर (chan->type == IIO_INTENSITY) अणु
			समय = chip->settings.als_समय;
			persistence = chip->settings.als_persistence;

			/* ALS filter values are 1, 2, 3, 5, 10, 15, ..., 60 */
			अगर (persistence > 3)
				persistence = (persistence - 3) * 5;
		पूर्ण अन्यथा अणु
			समय = chip->settings.prox_समय;
			persistence = chip->settings.prox_persistence;
		पूर्ण

		filter_delay = persistence * (256 - समय) *
			tsl2772_पूर्णांक_समय_avail[chip->id][3];

		*val = filter_delay / 1000000;
		*val2 = filter_delay % 1000000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tsl2772_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val,
			    पूर्णांक *val2,
			    दीर्घ mask)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			tsl2772_get_lux(indio_dev);
			*val = chip->als_cur_info.lux;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
			tsl2772_get_lux(indio_dev);
			अगर (chan->channel == 0)
				*val = chip->als_cur_info.als_ch0;
			अन्यथा
				*val = chip->als_cur_info.als_ch1;
			वापस IIO_VAL_INT;
		हाल IIO_PROXIMITY:
			tsl2772_get_prox(indio_dev);
			*val = chip->prox_data;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (chan->type == IIO_LIGHT)
			*val = tsl2772_als_gain[chip->settings.als_gain];
		अन्यथा
			*val = tsl2772_prox_gain[chip->settings.prox_gain];
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		*val = chip->settings.als_gain_trim;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = (256 - chip->settings.als_समय) *
			tsl2772_पूर्णांक_समय_avail[chip->id][3];
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tsl2772_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val,
			     पूर्णांक val2,
			     दीर्घ mask)
अणु
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (chan->type == IIO_INTENSITY) अणु
			चयन (val) अणु
			हाल 1:
				chip->settings.als_gain = 0;
				अवरोध;
			हाल 8:
				chip->settings.als_gain = 1;
				अवरोध;
			हाल 16:
				chip->settings.als_gain = 2;
				अवरोध;
			हाल 120:
				chip->settings.als_gain = 3;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (val) अणु
			हाल 1:
				chip->settings.prox_gain = 0;
				अवरोध;
			हाल 2:
				chip->settings.prox_gain = 1;
				अवरोध;
			हाल 4:
				chip->settings.prox_gain = 2;
				अवरोध;
			हाल 8:
				chip->settings.prox_gain = 3;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (val < TSL2772_ALS_GAIN_TRIM_MIN ||
		    val > TSL2772_ALS_GAIN_TRIM_MAX)
			वापस -EINVAL;

		chip->settings.als_gain_trim = val;
		अवरोध;
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (val != 0 || val2 < tsl2772_पूर्णांक_समय_avail[chip->id][1] ||
		    val2 > tsl2772_पूर्णांक_समय_avail[chip->id][5])
			वापस -EINVAL;

		chip->settings.als_समय = 256 -
			(val2 / tsl2772_पूर्णांक_समय_avail[chip->id][3]);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस tsl2772_invoke_change(indio_dev);
पूर्ण

अटल DEVICE_ATTR_RW(in_illuminance0_target_input);

अटल DEVICE_ATTR_WO(in_illuminance0_calibrate);

अटल DEVICE_ATTR_WO(in_proximity0_calibrate);

अटल DEVICE_ATTR_RW(in_illuminance0_lux_table);

/* Use the शेष रेजिस्टर values to identअगरy the Taos device */
अटल पूर्णांक tsl2772_device_id_verअगर(पूर्णांक id, पूर्णांक target)
अणु
	चयन (target) अणु
	हाल tsl2571:
	हाल tsl2671:
	हाल tsl2771:
		वापस (id & 0xf0) == TRITON_ID;
	हाल पंचांगd2671:
	हाल पंचांगd2771:
		वापस (id & 0xf0) == HALIBUT_ID;
	हाल tsl2572:
	हाल tsl2672:
	हाल पंचांगd2672:
	हाल tsl2772:
	हाल पंचांगd2772:
	हाल apds9930:
		वापस (id & 0xf0) == SWORDFISH_ID;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल irqवापस_t tsl2772_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	s64 बारtamp = iio_get_समय_ns(indio_dev);
	पूर्णांक ret;

	ret = tsl2772_पढ़ो_status(chip);
	अगर (ret < 0)
		वापस IRQ_HANDLED;

	/* What type of पूर्णांकerrupt करो we need to process */
	अगर (ret & TSL2772_STA_PRX_INTR) अणु
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY,
						    0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_EITHER),
			       बारtamp);
	पूर्ण

	अगर (ret & TSL2772_STA_ALS_INTR) अणु
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_LIGHT,
						    0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_EITHER),
			       बारtamp);
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte(chip->client,
				   TSL2772_CMD_REG | TSL2772_CMD_SPL_FN |
				   TSL2772_CMD_PROXALS_INT_CLR);
	अगर (ret < 0)
		dev_err(&chip->client->dev,
			"%s: failed to clear interrupt status: %d\n",
			__func__, ret);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा attribute *tsl2772_ALS_device_attrs[] = अणु
	&dev_attr_in_illuminance0_target_input.attr,
	&dev_attr_in_illuminance0_calibrate.attr,
	&dev_attr_in_illuminance0_lux_table.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *tsl2772_PRX_device_attrs[] = अणु
	&dev_attr_in_proximity0_calibrate.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *tsl2772_ALSPRX_device_attrs[] = अणु
	&dev_attr_in_illuminance0_target_input.attr,
	&dev_attr_in_illuminance0_calibrate.attr,
	&dev_attr_in_illuminance0_lux_table.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *tsl2772_PRX2_device_attrs[] = अणु
	&dev_attr_in_proximity0_calibrate.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *tsl2772_ALSPRX2_device_attrs[] = अणु
	&dev_attr_in_illuminance0_target_input.attr,
	&dev_attr_in_illuminance0_calibrate.attr,
	&dev_attr_in_illuminance0_lux_table.attr,
	&dev_attr_in_proximity0_calibrate.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tsl2772_device_attr_group_tbl[] = अणु
	[ALS] = अणु
		.attrs = tsl2772_ALS_device_attrs,
	पूर्ण,
	[PRX] = अणु
		.attrs = tsl2772_PRX_device_attrs,
	पूर्ण,
	[ALSPRX] = अणु
		.attrs = tsl2772_ALSPRX_device_attrs,
	पूर्ण,
	[PRX2] = अणु
		.attrs = tsl2772_PRX2_device_attrs,
	पूर्ण,
	[ALSPRX2] = अणु
		.attrs = tsl2772_ALSPRX2_device_attrs,
	पूर्ण,
पूर्ण;

#घोषणा TSL2772_DEVICE_INFO(type)[type] = \
	अणु \
		.attrs = &tsl2772_device_attr_group_tbl[type], \
		.पढ़ो_raw = &tsl2772_पढ़ो_raw, \
		.पढ़ो_avail = &tsl2772_पढ़ो_avail, \
		.ग_लिखो_raw = &tsl2772_ग_लिखो_raw, \
		.पढ़ो_event_value = &tsl2772_पढ़ो_event_value, \
		.ग_लिखो_event_value = &tsl2772_ग_लिखो_event_value, \
		.पढ़ो_event_config = &tsl2772_पढ़ो_पूर्णांकerrupt_config, \
		.ग_लिखो_event_config = &tsl2772_ग_लिखो_पूर्णांकerrupt_config, \
	पूर्ण

अटल स्थिर काष्ठा iio_info tsl2772_device_info[] = अणु
	TSL2772_DEVICE_INFO(ALS),
	TSL2772_DEVICE_INFO(PRX),
	TSL2772_DEVICE_INFO(ALSPRX),
	TSL2772_DEVICE_INFO(PRX2),
	TSL2772_DEVICE_INFO(ALSPRX2),
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec tsl2772_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_PERIOD) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tsl2772_chip_info tsl2772_chip_info_tbl[] = अणु
	[ALS] = अणु
		.channel_with_events = अणु
			अणु
			.type = IIO_LIGHT,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
			पूर्ण, अणु
			.type = IIO_INTENSITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_CALIBSCALE) |
				BIT(IIO_CHAN_INFO_CALIBBIAS),
			.info_mask_separate_available =
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			.event_spec = tsl2772_events,
			.num_event_specs = ARRAY_SIZE(tsl2772_events),
			पूर्ण, अणु
			.type = IIO_INTENSITY,
			.indexed = 1,
			.channel = 1,
			पूर्ण,
		पूर्ण,
		.channel_without_events = अणु
			अणु
			.type = IIO_LIGHT,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
			पूर्ण, अणु
			.type = IIO_INTENSITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_CALIBSCALE) |
				BIT(IIO_CHAN_INFO_CALIBBIAS),
			.info_mask_separate_available =
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			पूर्ण, अणु
			.type = IIO_INTENSITY,
			.indexed = 1,
			.channel = 1,
			पूर्ण,
		पूर्ण,
		.chan_table_elements = 3,
		.info = &tsl2772_device_info[ALS],
	पूर्ण,
	[PRX] = अणु
		.channel_with_events = अणु
			अणु
			.type = IIO_PROXIMITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
			.event_spec = tsl2772_events,
			.num_event_specs = ARRAY_SIZE(tsl2772_events),
			पूर्ण,
		पूर्ण,
		.channel_without_events = अणु
			अणु
			.type = IIO_PROXIMITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
			पूर्ण,
		पूर्ण,
		.chan_table_elements = 1,
		.info = &tsl2772_device_info[PRX],
	पूर्ण,
	[ALSPRX] = अणु
		.channel_with_events = अणु
			अणु
			.type = IIO_LIGHT,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
			पूर्ण, अणु
			.type = IIO_INTENSITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_CALIBSCALE) |
				BIT(IIO_CHAN_INFO_CALIBBIAS),
			.info_mask_separate_available =
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			.event_spec = tsl2772_events,
			.num_event_specs = ARRAY_SIZE(tsl2772_events),
			पूर्ण, अणु
			.type = IIO_INTENSITY,
			.indexed = 1,
			.channel = 1,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
			पूर्ण, अणु
			.type = IIO_PROXIMITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
			.event_spec = tsl2772_events,
			.num_event_specs = ARRAY_SIZE(tsl2772_events),
			पूर्ण,
		पूर्ण,
		.channel_without_events = अणु
			अणु
			.type = IIO_LIGHT,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
			पूर्ण, अणु
			.type = IIO_INTENSITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_CALIBSCALE) |
				BIT(IIO_CHAN_INFO_CALIBBIAS),
			.info_mask_separate_available =
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			पूर्ण, अणु
			.type = IIO_INTENSITY,
			.indexed = 1,
			.channel = 1,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
			पूर्ण, अणु
			.type = IIO_PROXIMITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
			पूर्ण,
		पूर्ण,
		.chan_table_elements = 4,
		.info = &tsl2772_device_info[ALSPRX],
	पूर्ण,
	[PRX2] = अणु
		.channel_with_events = अणु
			अणु
			.type = IIO_PROXIMITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			.info_mask_separate_available =
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			.event_spec = tsl2772_events,
			.num_event_specs = ARRAY_SIZE(tsl2772_events),
			पूर्ण,
		पूर्ण,
		.channel_without_events = अणु
			अणु
			.type = IIO_PROXIMITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			.info_mask_separate_available =
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			पूर्ण,
		पूर्ण,
		.chan_table_elements = 1,
		.info = &tsl2772_device_info[PRX2],
	पूर्ण,
	[ALSPRX2] = अणु
		.channel_with_events = अणु
			अणु
			.type = IIO_LIGHT,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
			पूर्ण, अणु
			.type = IIO_INTENSITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_CALIBSCALE) |
				BIT(IIO_CHAN_INFO_CALIBBIAS),
			.info_mask_separate_available =
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			.event_spec = tsl2772_events,
			.num_event_specs = ARRAY_SIZE(tsl2772_events),
			पूर्ण, अणु
			.type = IIO_INTENSITY,
			.indexed = 1,
			.channel = 1,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
			पूर्ण, अणु
			.type = IIO_PROXIMITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			.info_mask_separate_available =
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			.event_spec = tsl2772_events,
			.num_event_specs = ARRAY_SIZE(tsl2772_events),
			पूर्ण,
		पूर्ण,
		.channel_without_events = अणु
			अणु
			.type = IIO_LIGHT,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
			पूर्ण, अणु
			.type = IIO_INTENSITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_CALIBSCALE) |
				BIT(IIO_CHAN_INFO_CALIBBIAS),
			.info_mask_separate_available =
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			पूर्ण, अणु
			.type = IIO_INTENSITY,
			.indexed = 1,
			.channel = 1,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
			पूर्ण, अणु
			.type = IIO_PROXIMITY,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			.info_mask_separate_available =
				BIT(IIO_CHAN_INFO_CALIBSCALE),
			पूर्ण,
		पूर्ण,
		.chan_table_elements = 4,
		.info = &tsl2772_device_info[ALSPRX2],
	पूर्ण,
पूर्ण;

अटल पूर्णांक tsl2772_probe(काष्ठा i2c_client *clientp,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा tsl2772_chip *chip;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&clientp->dev, माप(*chip));
	अगर (!indio_dev)
		वापस -ENOMEM;

	chip = iio_priv(indio_dev);
	chip->client = clientp;
	i2c_set_clientdata(clientp, indio_dev);

	chip->supplies[TSL2772_SUPPLY_VDD].supply = "vdd";
	chip->supplies[TSL2772_SUPPLY_VDDIO].supply = "vddio";

	ret = devm_regulator_bulk_get(&clientp->dev,
				      ARRAY_SIZE(chip->supplies),
				      chip->supplies);
	अगर (ret < 0)
		वापस dev_err_probe(&clientp->dev, ret, "Failed to get regulators\n");

	ret = regulator_bulk_enable(ARRAY_SIZE(chip->supplies), chip->supplies);
	अगर (ret < 0) अणु
		dev_err(&clientp->dev, "Failed to enable regulators: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&clientp->dev,
					tsl2772_disable_regulators_action,
					chip);
	अगर (ret < 0) अणु
		dev_err(&clientp->dev, "Failed to setup regulator cleanup action %d\n",
			ret);
		वापस ret;
	पूर्ण

	usleep_range(TSL2772_BOOT_MIN_SLEEP_TIME, TSL2772_BOOT_MAX_SLEEP_TIME);

	ret = i2c_smbus_पढ़ो_byte_data(chip->client,
				       TSL2772_CMD_REG | TSL2772_CHIPID);
	अगर (ret < 0)
		वापस ret;

	अगर (tsl2772_device_id_verअगर(ret, id->driver_data) <= 0) अणु
		dev_info(&chip->client->dev,
			 "%s: i2c device found does not match expected id\n",
				__func__);
		वापस -EINVAL;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte(clientp, TSL2772_CMD_REG | TSL2772_CNTRL);
	अगर (ret < 0) अणु
		dev_err(&clientp->dev,
			"%s: Failed to write to CMD register: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	mutex_init(&chip->als_mutex);
	mutex_init(&chip->prox_mutex);

	chip->tsl2772_chip_status = TSL2772_CHIP_UNKNOWN;
	chip->pdata = dev_get_platdata(&clientp->dev);
	chip->id = id->driver_data;
	chip->chip_info =
		&tsl2772_chip_info_tbl[device_channel_config[id->driver_data]];

	indio_dev->info = chip->chip_info->info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->name = chip->client->name;
	indio_dev->num_channels = chip->chip_info->chan_table_elements;

	अगर (clientp->irq) अणु
		indio_dev->channels = chip->chip_info->channel_with_events;

		ret = devm_request_thपढ़ोed_irq(&clientp->dev, clientp->irq,
						शून्य,
						&tsl2772_event_handler,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						"TSL2772_event",
						indio_dev);
		अगर (ret) अणु
			dev_err(&clientp->dev,
				"%s: irq request failed\n", __func__);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		indio_dev->channels = chip->chip_info->channel_without_events;
	पूर्ण

	tsl2772_शेषs(chip);
	ret = tsl2772_chip_on(indio_dev);
	अगर (ret < 0)
		वापस ret;

	ret = devm_add_action_or_reset(&clientp->dev,
					tsl2772_chip_off_action,
					indio_dev);
	अगर (ret < 0)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&clientp->dev, indio_dev);
पूर्ण

अटल पूर्णांक tsl2772_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = tsl2772_chip_off(indio_dev);
	regulator_bulk_disable(ARRAY_SIZE(chip->supplies), chip->supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2772_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा tsl2772_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(chip->supplies), chip->supplies);
	अगर (ret < 0)
		वापस ret;

	usleep_range(TSL2772_BOOT_MIN_SLEEP_TIME, TSL2772_BOOT_MAX_SLEEP_TIME);

	वापस tsl2772_chip_on(indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tsl2772_idtable[] = अणु
	अणु "tsl2571", tsl2571 पूर्ण,
	अणु "tsl2671", tsl2671 पूर्ण,
	अणु "tmd2671", पंचांगd2671 पूर्ण,
	अणु "tsl2771", tsl2771 पूर्ण,
	अणु "tmd2771", पंचांगd2771 पूर्ण,
	अणु "tsl2572", tsl2572 पूर्ण,
	अणु "tsl2672", tsl2672 पूर्ण,
	अणु "tmd2672", पंचांगd2672 पूर्ण,
	अणु "tsl2772", tsl2772 पूर्ण,
	अणु "tmd2772", पंचांगd2772 पूर्ण,
	अणु "apds9930", apds9930पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, tsl2772_idtable);

अटल स्थिर काष्ठा of_device_id tsl2772_of_match[] = अणु
	अणु .compatible = "amstaos,tsl2571" पूर्ण,
	अणु .compatible = "amstaos,tsl2671" पूर्ण,
	अणु .compatible = "amstaos,tmd2671" पूर्ण,
	अणु .compatible = "amstaos,tsl2771" पूर्ण,
	अणु .compatible = "amstaos,tmd2771" पूर्ण,
	अणु .compatible = "amstaos,tsl2572" पूर्ण,
	अणु .compatible = "amstaos,tsl2672" पूर्ण,
	अणु .compatible = "amstaos,tmd2672" पूर्ण,
	अणु .compatible = "amstaos,tsl2772" पूर्ण,
	अणु .compatible = "amstaos,tmd2772" पूर्ण,
	अणु .compatible = "avago,apds9930" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tsl2772_of_match);

अटल स्थिर काष्ठा dev_pm_ops tsl2772_pm_ops = अणु
	.suspend = tsl2772_suspend,
	.resume  = tsl2772_resume,
पूर्ण;

अटल काष्ठा i2c_driver tsl2772_driver = अणु
	.driver = अणु
		.name = "tsl2772",
		.of_match_table = tsl2772_of_match,
		.pm = &tsl2772_pm_ops,
	पूर्ण,
	.id_table = tsl2772_idtable,
	.probe = tsl2772_probe,
पूर्ण;

module_i2c_driver(tsl2772_driver);

MODULE_AUTHOR("J. August Brenner <Jon.Brenner@ams.com>");
MODULE_AUTHOR("Brian Masney <masneyb@onstation.org>");
MODULE_DESCRIPTION("TAOS tsl2772 ambient and proximity light sensor driver");
MODULE_LICENSE("GPL");
