<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/iio/light/tsl2563.c
 *
 * Copyright (C) 2008 Nokia Corporation
 *
 * Written by Timo O. Karjalainen <timo.o.karjalainen@nokia.com>
 * Contact: Amit Kucheria <amit.kucheria@verdurent.com>
 *
 * Converted to IIO driver
 * Amit Kucheria <amit.kucheria@verdurent.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/sched.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/platक्रमm_data/tsl2563.h>

/* Use this many bits क्रम fraction part. */
#घोषणा ADC_FRAC_BITS		14

/* Given number of 1/10000's in ADC_FRAC_BITS precision. */
#घोषणा FRAC10K(f)		(((f) * (1L << (ADC_FRAC_BITS))) / (10000))

/* Bits used क्रम fraction in calibration coefficients.*/
#घोषणा CALIB_FRAC_BITS		10
/* 0.5 in CALIB_FRAC_BITS precision */
#घोषणा CALIB_FRAC_HALF		(1 << (CALIB_FRAC_BITS - 1))
/* Make a fraction from a number n that was multiplied with b. */
#घोषणा CALIB_FRAC(n, b)	(((n) << CALIB_FRAC_BITS) / (b))
/* Decimal 10^(digits in sysfs presentation) */
#घोषणा CALIB_BASE_SYSFS	1000

#घोषणा TSL2563_CMD		0x80
#घोषणा TSL2563_CLEARINT	0x40

#घोषणा TSL2563_REG_CTRL	0x00
#घोषणा TSL2563_REG_TIMING	0x01
#घोषणा TSL2563_REG_LOWLOW	0x02 /* data0 low threshold, 2 bytes */
#घोषणा TSL2563_REG_LOWHIGH	0x03
#घोषणा TSL2563_REG_HIGHLOW	0x04 /* data0 high threshold, 2 bytes */
#घोषणा TSL2563_REG_HIGHHIGH	0x05
#घोषणा TSL2563_REG_INT		0x06
#घोषणा TSL2563_REG_ID		0x0a
#घोषणा TSL2563_REG_DATA0LOW	0x0c /* broadband sensor value, 2 bytes */
#घोषणा TSL2563_REG_DATA0HIGH	0x0d
#घोषणा TSL2563_REG_DATA1LOW	0x0e /* infrared sensor value, 2 bytes */
#घोषणा TSL2563_REG_DATA1HIGH	0x0f

#घोषणा TSL2563_CMD_POWER_ON	0x03
#घोषणा TSL2563_CMD_POWER_OFF	0x00
#घोषणा TSL2563_CTRL_POWER_MASK	0x03

#घोषणा TSL2563_TIMING_13MS	0x00
#घोषणा TSL2563_TIMING_100MS	0x01
#घोषणा TSL2563_TIMING_400MS	0x02
#घोषणा TSL2563_TIMING_MASK	0x03
#घोषणा TSL2563_TIMING_GAIN16	0x10
#घोषणा TSL2563_TIMING_GAIN1	0x00

#घोषणा TSL2563_INT_DISABLED	0x00
#घोषणा TSL2563_INT_LEVEL	0x10
#घोषणा TSL2563_INT_PERSIST(n)	((n) & 0x0F)

काष्ठा tsl2563_gainlevel_coeff अणु
	u8 gaपूर्णांकime;
	u16 min;
	u16 max;
पूर्ण;

अटल स्थिर काष्ठा tsl2563_gainlevel_coeff tsl2563_gainlevel_table[] = अणु
	अणु
		.gaपूर्णांकime	= TSL2563_TIMING_400MS | TSL2563_TIMING_GAIN16,
		.min		= 0,
		.max		= 65534,
	पूर्ण, अणु
		.gaपूर्णांकime	= TSL2563_TIMING_400MS | TSL2563_TIMING_GAIN1,
		.min		= 2048,
		.max		= 65534,
	पूर्ण, अणु
		.gaपूर्णांकime	= TSL2563_TIMING_100MS | TSL2563_TIMING_GAIN1,
		.min		= 4095,
		.max		= 37177,
	पूर्ण, अणु
		.gaपूर्णांकime	= TSL2563_TIMING_13MS | TSL2563_TIMING_GAIN1,
		.min		= 3000,
		.max		= 65535,
	पूर्ण,
पूर्ण;

काष्ठा tsl2563_chip अणु
	काष्ठा mutex		lock;
	काष्ठा i2c_client	*client;
	काष्ठा delayed_work	घातeroff_work;

	/* Remember state क्रम suspend and resume functions */
	bool suspended;

	काष्ठा tsl2563_gainlevel_coeff स्थिर *gainlevel;

	u16			low_thres;
	u16			high_thres;
	u8			पूर्णांकr;
	bool			पूर्णांक_enabled;

	/* Calibration coefficients */
	u32			calib0;
	u32			calib1;
	पूर्णांक			cover_comp_gain;

	/* Cache current values, to be वापसed जबतक suspended */
	u32			data0;
	u32			data1;
पूर्ण;

अटल पूर्णांक tsl2563_set_घातer(काष्ठा tsl2563_chip *chip, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = chip->client;
	u8 cmd;

	cmd = on ? TSL2563_CMD_POWER_ON : TSL2563_CMD_POWER_OFF;
	वापस i2c_smbus_ग_लिखो_byte_data(client,
					 TSL2563_CMD | TSL2563_REG_CTRL, cmd);
पूर्ण

/*
 * Return value is 0 क्रम off, 1 क्रम on, or a negative error
 * code अगर पढ़ोing failed.
 */
अटल पूर्णांक tsl2563_get_घातer(काष्ठा tsl2563_chip *chip)
अणु
	काष्ठा i2c_client *client = chip->client;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, TSL2563_CMD | TSL2563_REG_CTRL);
	अगर (ret < 0)
		वापस ret;

	वापस (ret & TSL2563_CTRL_POWER_MASK) == TSL2563_CMD_POWER_ON;
पूर्ण

अटल पूर्णांक tsl2563_configure(काष्ठा tsl2563_chip *chip)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
			TSL2563_CMD | TSL2563_REG_TIMING,
			chip->gainlevel->gaपूर्णांकime);
	अगर (ret)
		जाओ error_ret;
	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
			TSL2563_CMD | TSL2563_REG_HIGHLOW,
			chip->high_thres & 0xFF);
	अगर (ret)
		जाओ error_ret;
	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
			TSL2563_CMD | TSL2563_REG_HIGHHIGH,
			(chip->high_thres >> 8) & 0xFF);
	अगर (ret)
		जाओ error_ret;
	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
			TSL2563_CMD | TSL2563_REG_LOWLOW,
			chip->low_thres & 0xFF);
	अगर (ret)
		जाओ error_ret;
	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
			TSL2563_CMD | TSL2563_REG_LOWHIGH,
			(chip->low_thres >> 8) & 0xFF);
/*
 * Interrupt रेजिस्टर is स्वतःmatically written anyway अगर it is relevant
 * so is not here.
 */
error_ret:
	वापस ret;
पूर्ण

अटल व्योम tsl2563_घातeroff_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tsl2563_chip *chip =
		container_of(work, काष्ठा tsl2563_chip, घातeroff_work.work);
	tsl2563_set_घातer(chip, 0);
पूर्ण

अटल पूर्णांक tsl2563_detect(काष्ठा tsl2563_chip *chip)
अणु
	पूर्णांक ret;

	ret = tsl2563_set_घातer(chip, 1);
	अगर (ret)
		वापस ret;

	ret = tsl2563_get_घातer(chip);
	अगर (ret < 0)
		वापस ret;

	वापस ret ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक tsl2563_पढ़ो_id(काष्ठा tsl2563_chip *chip, u8 *id)
अणु
	काष्ठा i2c_client *client = chip->client;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, TSL2563_CMD | TSL2563_REG_ID);
	अगर (ret < 0)
		वापस ret;

	*id = ret;

	वापस 0;
पूर्ण

/*
 * "Normalized" ADC value is one obtained with 400ms of पूर्णांकegration समय and
 * 16x gain. This function वापसs the number of bits of shअगरt needed to
 * convert between normalized values and HW values obtained using given
 * timing and gain settings.
 */
अटल पूर्णांक tsl2563_adc_shअगरtbits(u8 timing)
अणु
	पूर्णांक shअगरt = 0;

	चयन (timing & TSL2563_TIMING_MASK) अणु
	हाल TSL2563_TIMING_13MS:
		shअगरt += 5;
		अवरोध;
	हाल TSL2563_TIMING_100MS:
		shअगरt += 2;
		अवरोध;
	हाल TSL2563_TIMING_400MS:
		/* no-op */
		अवरोध;
	पूर्ण

	अगर (!(timing & TSL2563_TIMING_GAIN16))
		shअगरt += 4;

	वापस shअगरt;
पूर्ण

/* Convert a HW ADC value to normalized scale. */
अटल u32 tsl2563_normalize_adc(u16 adc, u8 timing)
अणु
	वापस adc << tsl2563_adc_shअगरtbits(timing);
पूर्ण

अटल व्योम tsl2563_रुको_adc(काष्ठा tsl2563_chip *chip)
अणु
	अचिन्हित पूर्णांक delay;

	चयन (chip->gainlevel->gaपूर्णांकime & TSL2563_TIMING_MASK) अणु
	हाल TSL2563_TIMING_13MS:
		delay = 14;
		अवरोध;
	हाल TSL2563_TIMING_100MS:
		delay = 101;
		अवरोध;
	शेष:
		delay = 402;
	पूर्ण
	/*
	 * TODO: Make sure that we रुको at least required delay but why we
	 * have to extend it one tick more?
	 */
	schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(delay) + 2);
पूर्ण

अटल पूर्णांक tsl2563_adjust_gainlevel(काष्ठा tsl2563_chip *chip, u16 adc)
अणु
	काष्ठा i2c_client *client = chip->client;

	अगर (adc > chip->gainlevel->max || adc < chip->gainlevel->min) अणु

		(adc > chip->gainlevel->max) ?
			chip->gainlevel++ : chip->gainlevel--;

		i2c_smbus_ग_लिखो_byte_data(client,
					  TSL2563_CMD | TSL2563_REG_TIMING,
					  chip->gainlevel->gaपूर्णांकime);

		tsl2563_रुको_adc(chip);
		tsl2563_रुको_adc(chip);

		वापस 1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक tsl2563_get_adc(काष्ठा tsl2563_chip *chip)
अणु
	काष्ठा i2c_client *client = chip->client;
	u16 adc0, adc1;
	पूर्णांक retry = 1;
	पूर्णांक ret = 0;

	अगर (chip->suspended)
		जाओ out;

	अगर (!chip->पूर्णांक_enabled) अणु
		cancel_delayed_work(&chip->घातeroff_work);

		अगर (!tsl2563_get_घातer(chip)) अणु
			ret = tsl2563_set_घातer(chip, 1);
			अगर (ret)
				जाओ out;
			ret = tsl2563_configure(chip);
			अगर (ret)
				जाओ out;
			tsl2563_रुको_adc(chip);
		पूर्ण
	पूर्ण

	जबतक (retry) अणु
		ret = i2c_smbus_पढ़ो_word_data(client,
				TSL2563_CMD | TSL2563_REG_DATA0LOW);
		अगर (ret < 0)
			जाओ out;
		adc0 = ret;

		ret = i2c_smbus_पढ़ो_word_data(client,
				TSL2563_CMD | TSL2563_REG_DATA1LOW);
		अगर (ret < 0)
			जाओ out;
		adc1 = ret;

		retry = tsl2563_adjust_gainlevel(chip, adc0);
	पूर्ण

	chip->data0 = tsl2563_normalize_adc(adc0, chip->gainlevel->gaपूर्णांकime);
	chip->data1 = tsl2563_normalize_adc(adc1, chip->gainlevel->gaपूर्णांकime);

	अगर (!chip->पूर्णांक_enabled)
		schedule_delayed_work(&chip->घातeroff_work, 5 * HZ);

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक tsl2563_calib_to_sysfs(u32 calib)
अणु
	वापस (पूर्णांक) (((calib * CALIB_BASE_SYSFS) +
		       CALIB_FRAC_HALF) >> CALIB_FRAC_BITS);
पूर्ण

अटल अंतरभूत u32 tsl2563_calib_from_sysfs(पूर्णांक value)
अणु
	वापस (((u32) value) << CALIB_FRAC_BITS) / CALIB_BASE_SYSFS;
पूर्ण

/*
 * Conversions between lux and ADC values.
 *
 * The basic क्रमmula is lux = c0 * adc0 - c1 * adc1, where c0 and c1 are
 * appropriate स्थिरants. Dअगरferent स्थिरants are needed क्रम dअगरferent
 * kinds of light, determined by the ratio adc1/adc0 (basically the ratio
 * of the पूर्णांकensities in infrared and visible wavelengths). lux_table below
 * lists the upper threshold of the adc1/adc0 ratio and the corresponding
 * स्थिरants.
 */

काष्ठा tsl2563_lux_coeff अणु
	अचिन्हित दीर्घ ch_ratio;
	अचिन्हित दीर्घ ch0_coeff;
	अचिन्हित दीर्घ ch1_coeff;
पूर्ण;

अटल स्थिर काष्ठा tsl2563_lux_coeff lux_table[] = अणु
	अणु
		.ch_ratio	= FRAC10K(1300),
		.ch0_coeff	= FRAC10K(315),
		.ch1_coeff	= FRAC10K(262),
	पूर्ण, अणु
		.ch_ratio	= FRAC10K(2600),
		.ch0_coeff	= FRAC10K(337),
		.ch1_coeff	= FRAC10K(430),
	पूर्ण, अणु
		.ch_ratio	= FRAC10K(3900),
		.ch0_coeff	= FRAC10K(363),
		.ch1_coeff	= FRAC10K(529),
	पूर्ण, अणु
		.ch_ratio	= FRAC10K(5200),
		.ch0_coeff	= FRAC10K(392),
		.ch1_coeff	= FRAC10K(605),
	पूर्ण, अणु
		.ch_ratio	= FRAC10K(6500),
		.ch0_coeff	= FRAC10K(229),
		.ch1_coeff	= FRAC10K(291),
	पूर्ण, अणु
		.ch_ratio	= FRAC10K(8000),
		.ch0_coeff	= FRAC10K(157),
		.ch1_coeff	= FRAC10K(180),
	पूर्ण, अणु
		.ch_ratio	= FRAC10K(13000),
		.ch0_coeff	= FRAC10K(34),
		.ch1_coeff	= FRAC10K(26),
	पूर्ण, अणु
		.ch_ratio	= अच_दीर्घ_उच्च,
		.ch0_coeff	= 0,
		.ch1_coeff	= 0,
	पूर्ण,
पूर्ण;

/* Convert normalized, scaled ADC values to lux. */
अटल अचिन्हित पूर्णांक tsl2563_adc_to_lux(u32 adc0, u32 adc1)
अणु
	स्थिर काष्ठा tsl2563_lux_coeff *lp = lux_table;
	अचिन्हित दीर्घ ratio, lux, ch0 = adc0, ch1 = adc1;

	ratio = ch0 ? ((ch1 << ADC_FRAC_BITS) / ch0) : अच_दीर्घ_उच्च;

	जबतक (lp->ch_ratio < ratio)
		lp++;

	lux = ch0 * lp->ch0_coeff - ch1 * lp->ch1_coeff;

	वापस (अचिन्हित पूर्णांक) (lux >> ADC_FRAC_BITS);
पूर्ण

/* Apply calibration coefficient to ADC count. */
अटल u32 tsl2563_calib_adc(u32 adc, u32 calib)
अणु
	अचिन्हित दीर्घ scaled = adc;

	scaled *= calib;
	scaled >>= CALIB_FRAC_BITS;

	वापस (u32) scaled;
पूर्ण

अटल पूर्णांक tsl2563_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा tsl2563_chip *chip = iio_priv(indio_dev);

	अगर (mask != IIO_CHAN_INFO_CALIBSCALE)
		वापस -EINVAL;
	अगर (chan->channel2 == IIO_MOD_LIGHT_BOTH)
		chip->calib0 = tsl2563_calib_from_sysfs(val);
	अन्यथा अगर (chan->channel2 == IIO_MOD_LIGHT_IR)
		chip->calib1 = tsl2563_calib_from_sysfs(val);
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक tsl2563_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val,
			    पूर्णांक *val2,
			    दीर्घ mask)
अणु
	पूर्णांक ret = -EINVAL;
	u32 calib0, calib1;
	काष्ठा tsl2563_chip *chip = iio_priv(indio_dev);

	mutex_lock(&chip->lock);
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = tsl2563_get_adc(chip);
			अगर (ret)
				जाओ error_ret;
			calib0 = tsl2563_calib_adc(chip->data0, chip->calib0) *
				chip->cover_comp_gain;
			calib1 = tsl2563_calib_adc(chip->data1, chip->calib1) *
				chip->cover_comp_gain;
			*val = tsl2563_adc_to_lux(calib0, calib1);
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_INTENSITY:
			ret = tsl2563_get_adc(chip);
			अगर (ret)
				जाओ error_ret;
			अगर (chan->channel2 == IIO_MOD_LIGHT_BOTH)
				*val = chip->data0;
			अन्यथा
				*val = chip->data1;
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (chan->channel2 == IIO_MOD_LIGHT_BOTH)
			*val = tsl2563_calib_to_sysfs(chip->calib0);
		अन्यथा
			*val = tsl2563_calib_to_sysfs(chip->calib1);
		ret = IIO_VAL_INT;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ error_ret;
	पूर्ण

error_ret:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_event_spec tsl2563_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
				BIT(IIO_EV_INFO_ENABLE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
				BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec tsl2563_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.indexed = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.channel = 0,
	पूर्ण, अणु
		.type = IIO_INTENSITY,
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_BOTH,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_CALIBSCALE),
		.event_spec = tsl2563_events,
		.num_event_specs = ARRAY_SIZE(tsl2563_events),
	पूर्ण, अणु
		.type = IIO_INTENSITY,
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_IR,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_CALIBSCALE),
	पूर्ण
पूर्ण;

अटल पूर्णांक tsl2563_पढ़ो_thresh(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक *val,
	पूर्णांक *val2)
अणु
	काष्ठा tsl2563_chip *chip = iio_priv(indio_dev);

	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		*val = chip->high_thres;
		अवरोध;
	हाल IIO_EV_सूची_FALLING:
		*val = chip->low_thres;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक tsl2563_ग_लिखो_thresh(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक val,
	पूर्णांक val2)
अणु
	काष्ठा tsl2563_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;
	u8 address;

	अगर (dir == IIO_EV_सूची_RISING)
		address = TSL2563_REG_HIGHLOW;
	अन्यथा
		address = TSL2563_REG_LOWLOW;
	mutex_lock(&chip->lock);
	ret = i2c_smbus_ग_लिखो_byte_data(chip->client, TSL2563_CMD | address,
					val & 0xFF);
	अगर (ret)
		जाओ error_ret;
	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
					TSL2563_CMD | (address + 1),
					(val >> 8) & 0xFF);
	अगर (dir == IIO_EV_सूची_RISING)
		chip->high_thres = val;
	अन्यथा
		chip->low_thres = val;

error_ret:
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल irqवापस_t tsl2563_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *dev_info = निजी;
	काष्ठा tsl2563_chip *chip = iio_priv(dev_info);

	iio_push_event(dev_info,
		       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY,
					    0,
					    IIO_EV_TYPE_THRESH,
					    IIO_EV_सूची_EITHER),
		       iio_get_समय_ns(dev_info));

	/* clear the पूर्णांकerrupt and push the event */
	i2c_smbus_ग_लिखो_byte(chip->client, TSL2563_CMD | TSL2563_CLEARINT);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tsl2563_ग_लिखो_पूर्णांकerrupt_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा tsl2563_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	mutex_lock(&chip->lock);
	अगर (state && !(chip->पूर्णांकr & 0x30)) अणु
		chip->पूर्णांकr &= ~0x30;
		chip->पूर्णांकr |= 0x10;
		/* ensure the chip is actually on */
		cancel_delayed_work(&chip->घातeroff_work);
		अगर (!tsl2563_get_घातer(chip)) अणु
			ret = tsl2563_set_घातer(chip, 1);
			अगर (ret)
				जाओ out;
			ret = tsl2563_configure(chip);
			अगर (ret)
				जाओ out;
		पूर्ण
		ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
						TSL2563_CMD | TSL2563_REG_INT,
						chip->पूर्णांकr);
		chip->पूर्णांक_enabled = true;
	पूर्ण

	अगर (!state && (chip->पूर्णांकr & 0x30)) अणु
		chip->पूर्णांकr &= ~0x30;
		ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
						TSL2563_CMD | TSL2563_REG_INT,
						chip->पूर्णांकr);
		chip->पूर्णांक_enabled = false;
		/* now the पूर्णांकerrupt is not enabled, we can go to sleep */
		schedule_delayed_work(&chip->घातeroff_work, 5 * HZ);
	पूर्ण
out:
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2563_पढ़ो_पूर्णांकerrupt_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir)
अणु
	काष्ठा tsl2563_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	ret = i2c_smbus_पढ़ो_byte_data(chip->client,
				       TSL2563_CMD | TSL2563_REG_INT);
	mutex_unlock(&chip->lock);
	अगर (ret < 0)
		वापस ret;

	वापस !!(ret & 0x30);
पूर्ण

अटल स्थिर काष्ठा iio_info tsl2563_info_no_irq = अणु
	.पढ़ो_raw = &tsl2563_पढ़ो_raw,
	.ग_लिखो_raw = &tsl2563_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_info tsl2563_info = अणु
	.पढ़ो_raw = &tsl2563_पढ़ो_raw,
	.ग_लिखो_raw = &tsl2563_ग_लिखो_raw,
	.पढ़ो_event_value = &tsl2563_पढ़ो_thresh,
	.ग_लिखो_event_value = &tsl2563_ग_लिखो_thresh,
	.पढ़ो_event_config = &tsl2563_पढ़ो_पूर्णांकerrupt_config,
	.ग_लिखो_event_config = &tsl2563_ग_लिखो_पूर्णांकerrupt_config,
पूर्ण;

अटल पूर्णांक tsl2563_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *device_id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा tsl2563_chip *chip;
	काष्ठा tsl2563_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	पूर्णांक err = 0;
	u8 id = 0;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*chip));
	अगर (!indio_dev)
		वापस -ENOMEM;

	chip = iio_priv(indio_dev);

	i2c_set_clientdata(client, indio_dev);
	chip->client = client;

	err = tsl2563_detect(chip);
	अगर (err) अणु
		dev_err(&client->dev, "detect error %d\n", -err);
		वापस err;
	पूर्ण

	err = tsl2563_पढ़ो_id(chip, &id);
	अगर (err) अणु
		dev_err(&client->dev, "read id error %d\n", -err);
		वापस err;
	पूर्ण

	mutex_init(&chip->lock);

	/* Default values used until userspace says otherwise */
	chip->low_thres = 0x0;
	chip->high_thres = 0xffff;
	chip->gainlevel = tsl2563_gainlevel_table;
	chip->पूर्णांकr = TSL2563_INT_PERSIST(4);
	chip->calib0 = tsl2563_calib_from_sysfs(CALIB_BASE_SYSFS);
	chip->calib1 = tsl2563_calib_from_sysfs(CALIB_BASE_SYSFS);

	अगर (pdata) अणु
		chip->cover_comp_gain = pdata->cover_comp_gain;
	पूर्ण अन्यथा अणु
		err = device_property_पढ़ो_u32(&client->dev, "amstaos,cover-comp-gain",
					       &chip->cover_comp_gain);
		अगर (err)
			chip->cover_comp_gain = 1;
	पूर्ण

	dev_info(&client->dev, "model %d, rev. %d\n", id >> 4, id & 0x0f);
	indio_dev->name = client->name;
	indio_dev->channels = tsl2563_channels;
	indio_dev->num_channels = ARRAY_SIZE(tsl2563_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	अगर (client->irq)
		indio_dev->info = &tsl2563_info;
	अन्यथा
		indio_dev->info = &tsl2563_info_no_irq;

	अगर (client->irq) अणु
		err = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					   शून्य,
					   &tsl2563_event_handler,
					   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					   "tsl2563_event",
					   indio_dev);
		अगर (err) अणु
			dev_err(&client->dev, "irq request error %d\n", -err);
			वापस err;
		पूर्ण
	पूर्ण

	err = tsl2563_configure(chip);
	अगर (err) अणु
		dev_err(&client->dev, "configure error %d\n", -err);
		वापस err;
	पूर्ण

	INIT_DELAYED_WORK(&chip->घातeroff_work, tsl2563_घातeroff_work);

	/* The पूर्णांकerrupt cannot yet be enabled so this is fine without lock */
	schedule_delayed_work(&chip->घातeroff_work, 5 * HZ);

	err = iio_device_रेजिस्टर(indio_dev);
	अगर (err) अणु
		dev_err(&client->dev, "iio registration error %d\n", -err);
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	cancel_delayed_work_sync(&chip->घातeroff_work);
	वापस err;
पूर्ण

अटल पूर्णांक tsl2563_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा tsl2563_chip *chip = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	अगर (!chip->पूर्णांक_enabled)
		cancel_delayed_work(&chip->घातeroff_work);
	/* Ensure that पूर्णांकerrupts are disabled - then flush any bottom halves */
	chip->पूर्णांकr &= ~0x30;
	i2c_smbus_ग_लिखो_byte_data(chip->client, TSL2563_CMD | TSL2563_REG_INT,
				  chip->पूर्णांकr);
	flush_scheduled_work();
	tsl2563_set_घातer(chip, 0);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tsl2563_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा tsl2563_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&chip->lock);

	ret = tsl2563_set_घातer(chip, 0);
	अगर (ret)
		जाओ out;

	chip->suspended = true;

out:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक tsl2563_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा tsl2563_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&chip->lock);

	ret = tsl2563_set_घातer(chip, 1);
	अगर (ret)
		जाओ out;

	ret = tsl2563_configure(chip);
	अगर (ret)
		जाओ out;

	chip->suspended = false;

out:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tsl2563_pm_ops, tsl2563_suspend, tsl2563_resume);
#घोषणा TSL2563_PM_OPS (&tsl2563_pm_ops)
#अन्यथा
#घोषणा TSL2563_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id tsl2563_id[] = अणु
	अणु "tsl2560", 0 पूर्ण,
	अणु "tsl2561", 1 पूर्ण,
	अणु "tsl2562", 2 पूर्ण,
	अणु "tsl2563", 3 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tsl2563_id);

अटल स्थिर काष्ठा of_device_id tsl2563_of_match[] = अणु
	अणु .compatible = "amstaos,tsl2560" पूर्ण,
	अणु .compatible = "amstaos,tsl2561" पूर्ण,
	अणु .compatible = "amstaos,tsl2562" पूर्ण,
	अणु .compatible = "amstaos,tsl2563" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tsl2563_of_match);

अटल काष्ठा i2c_driver tsl2563_i2c_driver = अणु
	.driver = अणु
		.name	 = "tsl2563",
		.of_match_table = tsl2563_of_match,
		.pm	= TSL2563_PM_OPS,
	पूर्ण,
	.probe		= tsl2563_probe,
	.हटाओ		= tsl2563_हटाओ,
	.id_table	= tsl2563_id,
पूर्ण;
module_i2c_driver(tsl2563_i2c_driver);

MODULE_AUTHOR("Nokia Corporation");
MODULE_DESCRIPTION("tsl2563 light sensor driver");
MODULE_LICENSE("GPL");
