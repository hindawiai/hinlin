<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device driver क्रम monitoring ambient light पूर्णांकensity (lux)
 * within the TAOS tsl258x family of devices (tsl2580, tsl2581, tsl2583).
 *
 * Copyright (c) 2011, TAOS Corporation.
 * Copyright (c) 2016-2017 Brian Masney <masneyb@onstation.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/mutex.h>
#समावेश <linux/unistd.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/pm_runसमय.स>

/* Device Registers and Masks */
#घोषणा TSL2583_CNTRL			0x00
#घोषणा TSL2583_ALS_TIME		0X01
#घोषणा TSL2583_INTERRUPT		0x02
#घोषणा TSL2583_GAIN			0x07
#घोषणा TSL2583_REVID			0x11
#घोषणा TSL2583_CHIPID			0x12
#घोषणा TSL2583_ALS_CHAN0LO		0x14
#घोषणा TSL2583_ALS_CHAN0HI		0x15
#घोषणा TSL2583_ALS_CHAN1LO		0x16
#घोषणा TSL2583_ALS_CHAN1HI		0x17
#घोषणा TSL2583_TMR_LO			0x18
#घोषणा TSL2583_TMR_HI			0x19

/* tsl2583 cmd reg masks */
#घोषणा TSL2583_CMD_REG			0x80
#घोषणा TSL2583_CMD_SPL_FN		0x60
#घोषणा TSL2583_CMD_ALS_INT_CLR		0x01

/* tsl2583 cntrl reg masks */
#घोषणा TSL2583_CNTL_ADC_ENBL		0x02
#घोषणा TSL2583_CNTL_PWR_OFF		0x00
#घोषणा TSL2583_CNTL_PWR_ON		0x01

/* tsl2583 status reg masks */
#घोषणा TSL2583_STA_ADC_VALID		0x01
#घोषणा TSL2583_STA_ADC_INTR		0x10

/* Lux calculation स्थिरants */
#घोषणा TSL2583_LUX_CALC_OVER_FLOW	65535

#घोषणा TSL2583_INTERRUPT_DISABLED	0x00

#घोषणा TSL2583_CHIP_ID			0x90
#घोषणा TSL2583_CHIP_ID_MASK		0xf0

#घोषणा TSL2583_POWER_OFF_DELAY_MS	2000

/* Per-device data */
काष्ठा tsl2583_als_info अणु
	u16 als_ch0;
	u16 als_ch1;
	u16 lux;
पूर्ण;

काष्ठा tsl2583_lux अणु
	अचिन्हित पूर्णांक ratio;
	अचिन्हित पूर्णांक ch0;
	अचिन्हित पूर्णांक ch1;
पूर्ण;

अटल स्थिर काष्ठा tsl2583_lux tsl2583_शेष_lux[] = अणु
	अणु  9830,  8520, 15729 पूर्ण,
	अणु 12452, 10807, 23344 पूर्ण,
	अणु 14746,  6383, 11705 पूर्ण,
	अणु 17695,  4063,  6554 पूर्ण,
	अणु     0,     0,     0 पूर्ण  /* Termination segment */
पूर्ण;

#घोषणा TSL2583_MAX_LUX_TABLE_ENTRIES 11

काष्ठा tsl2583_settings अणु
	पूर्णांक als_समय;
	पूर्णांक als_gain;
	पूर्णांक als_gain_trim;
	पूर्णांक als_cal_target;

	/*
	 * This काष्ठाure is पूर्णांकentionally large to accommodate updates via
	 * sysfs. Sized to 11 = max 10 segments + 1 termination segment.
	 * Assumption is that one and only one type of glass used.
	 */
	काष्ठा tsl2583_lux als_device_lux[TSL2583_MAX_LUX_TABLE_ENTRIES];
पूर्ण;

काष्ठा tsl2583_chip अणु
	काष्ठा mutex als_mutex;
	काष्ठा i2c_client *client;
	काष्ठा tsl2583_als_info als_cur_info;
	काष्ठा tsl2583_settings als_settings;
	पूर्णांक als_समय_scale;
	पूर्णांक als_saturation;
पूर्ण;

काष्ठा gainadj अणु
	s16 ch0;
	s16 ch1;
	s16 mean;
पूर्ण;

/* Index = (0 - 3) Used to validate the gain selection index */
अटल स्थिर काष्ठा gainadj gainadj[] = अणु
	अणु 1, 1, 1 पूर्ण,
	अणु 8, 8, 8 पूर्ण,
	अणु 16, 16, 16 पूर्ण,
	अणु 107, 115, 111 पूर्ण
पूर्ण;

/*
 * Provides initial operational parameter शेषs.
 * These शेषs may be changed through the device's sysfs files.
 */
अटल व्योम tsl2583_शेषs(काष्ठा tsl2583_chip *chip)
अणु
	/*
	 * The पूर्णांकegration समय must be a multiple of 50ms and within the
	 * range [50, 600] ms.
	 */
	chip->als_settings.als_समय = 100;

	/*
	 * This is an index पूर्णांकo the gainadj table. Assume clear glass as the
	 * शेष.
	 */
	chip->als_settings.als_gain = 0;

	/* Default gain trim to account क्रम aperture effects */
	chip->als_settings.als_gain_trim = 1000;

	/* Known बाह्यal ALS पढ़ोing used क्रम calibration */
	chip->als_settings.als_cal_target = 130;

	/* Default lux table. */
	स_नकल(chip->als_settings.als_device_lux, tsl2583_शेष_lux,
	       माप(tsl2583_शेष_lux));
पूर्ण

/*
 * Reads and calculates current lux value.
 * The raw ch0 and ch1 values of the ambient light sensed in the last
 * पूर्णांकegration cycle are पढ़ो from the device.
 * Time scale factor array values are adjusted based on the पूर्णांकegration समय.
 * The raw values are multiplied by a scale factor, and device gain is obtained
 * using gain index. Limit checks are करोne next, then the ratio of a multiple
 * of ch1 value, to the ch0 value, is calculated. The array als_device_lux[]
 * declared above is then scanned to find the first ratio value that is just
 * above the ratio we just calculated. The ch0 and ch1 multiplier स्थिरants in
 * the array are then used aदीर्घ with the समय scale factor array values, to
 * calculate the lux.
 */
अटल पूर्णांक tsl2583_get_lux(काष्ठा iio_dev *indio_dev)
अणु
	u16 ch0, ch1; /* separated ch0/ch1 data from device */
	u32 lux; /* raw lux calculated from device data */
	u64 lux64;
	u32 ratio;
	u8 buf[5];
	काष्ठा tsl2583_lux *p;
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);
	पूर्णांक i, ret;

	ret = i2c_smbus_पढ़ो_byte_data(chip->client, TSL2583_CMD_REG);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev, "%s: failed to read CMD_REG register\n",
			__func__);
		जाओ करोne;
	पूर्ण

	/* is data new & valid */
	अगर (!(ret & TSL2583_STA_ADC_INTR)) अणु
		dev_err(&chip->client->dev, "%s: data not valid; returning last value\n",
			__func__);
		ret = chip->als_cur_info.lux; /* वापस LAST VALUE */
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांक reg = TSL2583_CMD_REG | (TSL2583_ALS_CHAN0LO + i);

		ret = i2c_smbus_पढ़ो_byte_data(chip->client, reg);
		अगर (ret < 0) अणु
			dev_err(&chip->client->dev, "%s: failed to read register %x\n",
				__func__, reg);
			जाओ करोne;
		पूर्ण
		buf[i] = ret;
	पूर्ण

	/*
	 * Clear the pending पूर्णांकerrupt status bit on the chip to allow the next
	 * पूर्णांकegration cycle to start. This has to be करोne even though this
	 * driver currently करोes not support पूर्णांकerrupts.
	 */
	ret = i2c_smbus_ग_लिखो_byte(chip->client,
				   (TSL2583_CMD_REG | TSL2583_CMD_SPL_FN |
				    TSL2583_CMD_ALS_INT_CLR));
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev, "%s: failed to clear the interrupt bit\n",
			__func__);
		जाओ करोne; /* have no data, so वापस failure */
	पूर्ण

	/* extract ALS/lux data */
	ch0 = le16_to_cpup((स्थिर __le16 *)&buf[0]);
	ch1 = le16_to_cpup((स्थिर __le16 *)&buf[2]);

	chip->als_cur_info.als_ch0 = ch0;
	chip->als_cur_info.als_ch1 = ch1;

	अगर ((ch0 >= chip->als_saturation) || (ch1 >= chip->als_saturation))
		जाओ वापस_max;

	अगर (!ch0) अणु
		/*
		 * The sensor appears to be in total darkness so set the
		 * calculated lux to 0 and वापस early to aव्योम a भागision by
		 * zero below when calculating the ratio.
		 */
		ret = 0;
		chip->als_cur_info.lux = 0;
		जाओ करोne;
	पूर्ण

	/* calculate ratio */
	ratio = (ch1 << 15) / ch0;

	/* convert to unscaled lux using the poपूर्णांकer to the table */
	क्रम (p = (काष्ठा tsl2583_lux *)chip->als_settings.als_device_lux;
	     p->ratio != 0 && p->ratio < ratio; p++)
		;

	अगर (p->ratio == 0) अणु
		lux = 0;
	पूर्ण अन्यथा अणु
		u32 ch0lux, ch1lux;

		ch0lux = ((ch0 * p->ch0) +
			  (gainadj[chip->als_settings.als_gain].ch0 >> 1))
			 / gainadj[chip->als_settings.als_gain].ch0;
		ch1lux = ((ch1 * p->ch1) +
			  (gainadj[chip->als_settings.als_gain].ch1 >> 1))
			 / gainadj[chip->als_settings.als_gain].ch1;

		/* note: lux is 31 bit max at this poपूर्णांक */
		अगर (ch1lux > ch0lux) अणु
			dev_dbg(&chip->client->dev, "%s: No Data - Returning 0\n",
				__func__);
			ret = 0;
			chip->als_cur_info.lux = 0;
			जाओ करोne;
		पूर्ण

		lux = ch0lux - ch1lux;
	पूर्ण

	/* adjust क्रम active समय scale */
	अगर (chip->als_समय_scale == 0)
		lux = 0;
	अन्यथा
		lux = (lux + (chip->als_समय_scale >> 1)) /
			chip->als_समय_scale;

	/*
	 * Adjust क्रम active gain scale.
	 * The tsl2583_शेष_lux tables above have a factor of 8192 built in,
	 * so we need to shअगरt right.
	 * User-specअगरied gain provides a multiplier.
	 * Apply user-specअगरied gain beक्रमe shअगरting right to retain precision.
	 * Use 64 bits to aव्योम overflow on multiplication.
	 * Then go back to 32 bits beक्रमe भागision to aव्योम using भाग_u64().
	 */
	lux64 = lux;
	lux64 = lux64 * chip->als_settings.als_gain_trim;
	lux64 >>= 13;
	lux = lux64;
	lux = DIV_ROUND_CLOSEST(lux, 1000);

	अगर (lux > TSL2583_LUX_CALC_OVER_FLOW) अणु /* check क्रम overflow */
वापस_max:
		lux = TSL2583_LUX_CALC_OVER_FLOW;
	पूर्ण

	/* Update the काष्ठाure with the latest VALID lux. */
	chip->als_cur_info.lux = lux;
	ret = lux;

करोne:
	वापस ret;
पूर्ण

/*
 * Obtain single पढ़ोing and calculate the als_gain_trim (later used
 * to derive actual lux).
 * Return updated gain_trim value.
 */
अटल पूर्णांक tsl2583_als_calibrate(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);
	अचिन्हित पूर्णांक gain_trim_val;
	पूर्णांक ret;
	पूर्णांक lux_val;

	ret = i2c_smbus_पढ़ो_byte_data(chip->client,
				       TSL2583_CMD_REG | TSL2583_CNTRL);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev,
			"%s: failed to read from the CNTRL register\n",
			__func__);
		वापस ret;
	पूर्ण

	अगर ((ret & (TSL2583_CNTL_ADC_ENBL | TSL2583_CNTL_PWR_ON))
			!= (TSL2583_CNTL_ADC_ENBL | TSL2583_CNTL_PWR_ON)) अणु
		dev_err(&chip->client->dev,
			"%s: Device is not powered on and/or ADC is not enabled\n",
			__func__);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर ((ret & TSL2583_STA_ADC_VALID) != TSL2583_STA_ADC_VALID) अणु
		dev_err(&chip->client->dev,
			"%s: The two ADC channels have not completed an integration cycle\n",
			__func__);
		वापस -ENODATA;
	पूर्ण

	lux_val = tsl2583_get_lux(indio_dev);
	अगर (lux_val < 0) अणु
		dev_err(&chip->client->dev, "%s: failed to get lux\n",
			__func__);
		वापस lux_val;
	पूर्ण

	/* Aव्योम भागision by zero of lux_value later on */
	अगर (lux_val == 0) अणु
		dev_err(&chip->client->dev,
			"%s: lux_val of 0 will produce out of range trim_value\n",
			__func__);
		वापस -ENODATA;
	पूर्ण

	gain_trim_val = (अचिन्हित पूर्णांक)(((chip->als_settings.als_cal_target)
			* chip->als_settings.als_gain_trim) / lux_val);
	अगर ((gain_trim_val < 250) || (gain_trim_val > 4000)) अणु
		dev_err(&chip->client->dev,
			"%s: trim_val of %d is not within the range [250, 4000]\n",
			__func__, gain_trim_val);
		वापस -ENODATA;
	पूर्ण

	chip->als_settings.als_gain_trim = (पूर्णांक)gain_trim_val;

	वापस 0;
पूर्ण

अटल पूर्णांक tsl2583_set_als_समय(काष्ठा tsl2583_chip *chip)
अणु
	पूर्णांक als_count, als_समय, ret;
	u8 val;

	/* determine als पूर्णांकegration रेजिस्टर */
	als_count = DIV_ROUND_CLOSEST(chip->als_settings.als_समय * 100, 270);
	अगर (!als_count)
		als_count = 1; /* ensure at least one cycle */

	/* convert back to समय (encompasses overrides) */
	als_समय = DIV_ROUND_CLOSEST(als_count * 27, 10);

	val = 256 - als_count;
	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
					TSL2583_CMD_REG | TSL2583_ALS_TIME,
					val);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev, "%s: failed to set the als time to %d\n",
			__func__, val);
		वापस ret;
	पूर्ण

	/* set chip काष्ठा re scaling and saturation */
	chip->als_saturation = als_count * 922; /* 90% of full scale */
	chip->als_समय_scale = DIV_ROUND_CLOSEST(als_समय, 50);

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2583_set_als_gain(काष्ठा tsl2583_chip *chip)
अणु
	पूर्णांक ret;

	/* Set the gain based on als_settings काष्ठा */
	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
					TSL2583_CMD_REG | TSL2583_GAIN,
					chip->als_settings.als_gain);
	अगर (ret < 0)
		dev_err(&chip->client->dev,
			"%s: failed to set the gain to %d\n", __func__,
			chip->als_settings.als_gain);

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2583_set_घातer_state(काष्ठा tsl2583_chip *chip, u8 state)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
					TSL2583_CMD_REG | TSL2583_CNTRL, state);
	अगर (ret < 0)
		dev_err(&chip->client->dev,
			"%s: failed to set the power state to %d\n", __func__,
			state);

	वापस ret;
पूर्ण

/*
 * Turn the device on.
 * Configuration must be set beक्रमe calling this function.
 */
अटल पूर्णांक tsl2583_chip_init_and_घातer_on(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;

	/* Power on the device; ADC off. */
	ret = tsl2583_set_घातer_state(chip, TSL2583_CNTL_PWR_ON);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
					TSL2583_CMD_REG | TSL2583_INTERRUPT,
					TSL2583_INTERRUPT_DISABLED);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev,
			"%s: failed to disable interrupts\n", __func__);
		वापस ret;
	पूर्ण

	ret = tsl2583_set_als_समय(chip);
	अगर (ret < 0)
		वापस ret;

	ret = tsl2583_set_als_gain(chip);
	अगर (ret < 0)
		वापस ret;

	usleep_range(3000, 3500);

	ret = tsl2583_set_घातer_state(chip, TSL2583_CNTL_PWR_ON |
					    TSL2583_CNTL_ADC_ENBL);
	अगर (ret < 0)
		वापस ret;

	वापस ret;
पूर्ण

/* Sysfs Interface Functions */

अटल sमाप_प्रकार in_illuminance_input_target_show(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&chip->als_mutex);
	ret = प्र_लिखो(buf, "%d\n", chip->als_settings.als_cal_target);
	mutex_unlock(&chip->als_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार in_illuminance_input_target_store(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);
	पूर्णांक value;

	अगर (kstrtoपूर्णांक(buf, 0, &value) || !value)
		वापस -EINVAL;

	mutex_lock(&chip->als_mutex);
	chip->als_settings.als_cal_target = value;
	mutex_unlock(&chip->als_mutex);

	वापस len;
पूर्ण

अटल sमाप_प्रकार in_illuminance_calibrate_store(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);
	पूर्णांक value, ret;

	अगर (kstrtoपूर्णांक(buf, 0, &value) || value != 1)
		वापस -EINVAL;

	mutex_lock(&chip->als_mutex);

	ret = tsl2583_als_calibrate(indio_dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = len;
करोne:
	mutex_unlock(&chip->als_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार in_illuminance_lux_table_show(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);
	अचिन्हित पूर्णांक i;
	पूर्णांक offset = 0;

	क्रम (i = 0; i < ARRAY_SIZE(chip->als_settings.als_device_lux); i++) अणु
		offset += प्र_लिखो(buf + offset, "%u,%u,%u,",
				  chip->als_settings.als_device_lux[i].ratio,
				  chip->als_settings.als_device_lux[i].ch0,
				  chip->als_settings.als_device_lux[i].ch1);
		अगर (chip->als_settings.als_device_lux[i].ratio == 0) अणु
			/*
			 * We just prपूर्णांकed the first "0" entry.
			 * Now get rid of the extra "," and अवरोध.
			 */
			offset--;
			अवरोध;
		पूर्ण
	पूर्ण

	offset += प्र_लिखो(buf + offset, "\n");

	वापस offset;
पूर्ण

अटल sमाप_प्रकार in_illuminance_lux_table_store(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);
	स्थिर अचिन्हित पूर्णांक max_पूर्णांकs = TSL2583_MAX_LUX_TABLE_ENTRIES * 3;
	पूर्णांक value[TSL2583_MAX_LUX_TABLE_ENTRIES * 3 + 1];
	पूर्णांक ret = -EINVAL;
	अचिन्हित पूर्णांक n;

	mutex_lock(&chip->als_mutex);

	get_options(buf, ARRAY_SIZE(value), value);

	/*
	 * We now have an array of पूर्णांकs starting at value[1], and
	 * क्रमागतerated by value[0].
	 * We expect each group of three पूर्णांकs is one table entry,
	 * and the last table entry is all 0.
	 */
	n = value[0];
	अगर ((n % 3) || n < 6 || n > max_पूर्णांकs) अणु
		dev_err(dev,
			"%s: The number of entries in the lux table must be a multiple of 3 and within the range [6, %d]\n",
			__func__, max_पूर्णांकs);
		जाओ करोne;
	पूर्ण
	अगर ((value[n - 2] | value[n - 1] | value[n]) != 0) अणु
		dev_err(dev, "%s: The last 3 entries in the lux table must be zeros.\n",
			__func__);
		जाओ करोne;
	पूर्ण

	स_नकल(chip->als_settings.als_device_lux, &value[1],
	       value[0] * माप(value[1]));

	ret = len;

करोne:
	mutex_unlock(&chip->als_mutex);

	वापस ret;
पूर्ण

अटल IIO_CONST_ATTR(in_illuminance_calibscale_available, "1 8 16 111");
अटल IIO_CONST_ATTR(in_illuminance_पूर्णांकegration_समय_available,
		      "0.050 0.100 0.150 0.200 0.250 0.300 0.350 0.400 0.450 0.500 0.550 0.600 0.650");
अटल IIO_DEVICE_ATTR_RW(in_illuminance_input_target, 0);
अटल IIO_DEVICE_ATTR_WO(in_illuminance_calibrate, 0);
अटल IIO_DEVICE_ATTR_RW(in_illuminance_lux_table, 0);

अटल काष्ठा attribute *sysfs_attrs_ctrl[] = अणु
	&iio_स्थिर_attr_in_illuminance_calibscale_available.dev_attr.attr,
	&iio_स्थिर_attr_in_illuminance_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_dev_attr_in_illuminance_input_target.dev_attr.attr,
	&iio_dev_attr_in_illuminance_calibrate.dev_attr.attr,
	&iio_dev_attr_in_illuminance_lux_table.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tsl2583_attribute_group = अणु
	.attrs = sysfs_attrs_ctrl,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec tsl2583_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_IR,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण,
	अणु
		.type = IIO_LIGHT,
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_BOTH,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण,
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				      BIT(IIO_CHAN_INFO_CALIBBIAS) |
				      BIT(IIO_CHAN_INFO_CALIBSCALE) |
				      BIT(IIO_CHAN_INFO_INT_TIME),
	पूर्ण,
पूर्ण;

अटल पूर्णांक tsl2583_set_pm_runसमय_busy(काष्ठा tsl2583_chip *chip, bool on)
अणु
	पूर्णांक ret;

	अगर (on) अणु
		ret = pm_runसमय_get_sync(&chip->client->dev);
		अगर (ret < 0)
			pm_runसमय_put_noidle(&chip->client->dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(&chip->client->dev);
		ret = pm_runसमय_put_स्वतःsuspend(&chip->client->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2583_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret, pm_ret;

	ret = tsl2583_set_pm_runसमय_busy(chip, true);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&chip->als_mutex);

	ret = -EINVAL;
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->type == IIO_LIGHT) अणु
			ret = tsl2583_get_lux(indio_dev);
			अगर (ret < 0)
				जाओ पढ़ो_करोne;

			/*
			 * From page 20 of the TSL2581, TSL2583 data
			 * sheet (TAOS134 ै MARCH 2011):
			 *
			 * One of the photodiodes (channel 0) is
			 * sensitive to both visible and infrared light,
			 * जबतक the second photodiode (channel 1) is
			 * sensitive primarily to infrared light.
			 */
			अगर (chan->channel2 == IIO_MOD_LIGHT_BOTH)
				*val = chip->als_cur_info.als_ch0;
			अन्यथा
				*val = chip->als_cur_info.als_ch1;

			ret = IIO_VAL_INT;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_PROCESSED:
		अगर (chan->type == IIO_LIGHT) अणु
			ret = tsl2583_get_lux(indio_dev);
			अगर (ret < 0)
				जाओ पढ़ो_करोne;

			*val = ret;
			ret = IIO_VAL_INT;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (chan->type == IIO_LIGHT) अणु
			*val = chip->als_settings.als_gain_trim;
			ret = IIO_VAL_INT;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (chan->type == IIO_LIGHT) अणु
			*val = gainadj[chip->als_settings.als_gain].mean;
			ret = IIO_VAL_INT;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (chan->type == IIO_LIGHT) अणु
			*val = 0;
			*val2 = chip->als_settings.als_समय;
			ret = IIO_VAL_INT_PLUS_MICRO;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

पढ़ो_करोne:
	mutex_unlock(&chip->als_mutex);

	अगर (ret < 0)
		वापस ret;

	/*
	 * Preserve the ret variable अगर the call to
	 * tsl2583_set_pm_runसमय_busy() is successful so the पढ़ोing
	 * (अगर applicable) is वापसed to user space.
	 */
	pm_ret = tsl2583_set_pm_runसमय_busy(chip, false);
	अगर (pm_ret < 0)
		वापस pm_ret;

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2583_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = tsl2583_set_pm_runसमय_busy(chip, true);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&chip->als_mutex);

	ret = -EINVAL;
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (chan->type == IIO_LIGHT) अणु
			chip->als_settings.als_gain_trim = val;
			ret = 0;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (chan->type == IIO_LIGHT) अणु
			अचिन्हित पूर्णांक i;

			क्रम (i = 0; i < ARRAY_SIZE(gainadj); i++) अणु
				अगर (gainadj[i].mean == val) अणु
					chip->als_settings.als_gain = i;
					ret = tsl2583_set_als_gain(chip);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (chan->type == IIO_LIGHT && !val && val2 >= 50 &&
		    val2 <= 650 && !(val2 % 50)) अणु
			chip->als_settings.als_समय = val2;
			ret = tsl2583_set_als_समय(chip);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&chip->als_mutex);

	अगर (ret < 0)
		वापस ret;

	ret = tsl2583_set_pm_runसमय_busy(chip, false);
	अगर (ret < 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info tsl2583_info = अणु
	.attrs = &tsl2583_attribute_group,
	.पढ़ो_raw = tsl2583_पढ़ो_raw,
	.ग_लिखो_raw = tsl2583_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक tsl2583_probe(काष्ठा i2c_client *clientp,
			 स्थिर काष्ठा i2c_device_id *idp)
अणु
	पूर्णांक ret;
	काष्ठा tsl2583_chip *chip;
	काष्ठा iio_dev *indio_dev;

	अगर (!i2c_check_functionality(clientp->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&clientp->dev, "%s: i2c smbus byte data functionality is unsupported\n",
			__func__);
		वापस -EOPNOTSUPP;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&clientp->dev, माप(*chip));
	अगर (!indio_dev)
		वापस -ENOMEM;

	chip = iio_priv(indio_dev);
	chip->client = clientp;
	i2c_set_clientdata(clientp, indio_dev);

	mutex_init(&chip->als_mutex);

	ret = i2c_smbus_पढ़ो_byte_data(clientp,
				       TSL2583_CMD_REG | TSL2583_CHIPID);
	अगर (ret < 0) अणु
		dev_err(&clientp->dev,
			"%s: failed to read the chip ID register\n", __func__);
		वापस ret;
	पूर्ण

	अगर ((ret & TSL2583_CHIP_ID_MASK) != TSL2583_CHIP_ID) अणु
		dev_err(&clientp->dev, "%s: received an unknown chip ID %x\n",
			__func__, ret);
		वापस -EINVAL;
	पूर्ण

	indio_dev->info = &tsl2583_info;
	indio_dev->channels = tsl2583_channels;
	indio_dev->num_channels = ARRAY_SIZE(tsl2583_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->name = chip->client->name;

	pm_runसमय_enable(&clientp->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&clientp->dev,
					 TSL2583_POWER_OFF_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&clientp->dev);

	ret = devm_iio_device_रेजिस्टर(indio_dev->dev.parent, indio_dev);
	अगर (ret) अणु
		dev_err(&clientp->dev, "%s: iio registration failed\n",
			__func__);
		वापस ret;
	पूर्ण

	/* Load up the V2 शेषs (these are hard coded शेषs क्रम now) */
	tsl2583_शेषs(chip);

	dev_info(&clientp->dev, "Light sensor found.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tsl2583_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	वापस tsl2583_set_घातer_state(chip, TSL2583_CNTL_PWR_OFF);
पूर्ण

अटल पूर्णांक __maybe_unused tsl2583_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&chip->als_mutex);

	ret = tsl2583_set_घातer_state(chip, TSL2583_CNTL_PWR_OFF);

	mutex_unlock(&chip->als_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused tsl2583_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा tsl2583_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&chip->als_mutex);

	ret = tsl2583_chip_init_and_घातer_on(indio_dev);

	mutex_unlock(&chip->als_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tsl2583_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(tsl2583_suspend, tsl2583_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id tsl2583_idtable[] = अणु
	अणु "tsl2580", 0 पूर्ण,
	अणु "tsl2581", 1 पूर्ण,
	अणु "tsl2583", 2 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tsl2583_idtable);

अटल स्थिर काष्ठा of_device_id tsl2583_of_match[] = अणु
	अणु .compatible = "amstaos,tsl2580", पूर्ण,
	अणु .compatible = "amstaos,tsl2581", पूर्ण,
	अणु .compatible = "amstaos,tsl2583", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tsl2583_of_match);

/* Driver definition */
अटल काष्ठा i2c_driver tsl2583_driver = अणु
	.driver = अणु
		.name = "tsl2583",
		.pm = &tsl2583_pm_ops,
		.of_match_table = tsl2583_of_match,
	पूर्ण,
	.id_table = tsl2583_idtable,
	.probe = tsl2583_probe,
	.हटाओ = tsl2583_हटाओ,
पूर्ण;
module_i2c_driver(tsl2583_driver);

MODULE_AUTHOR("J. August Brenner <jbrenner@taosinc.com>");
MODULE_AUTHOR("Brian Masney <masneyb@onstation.org>");
MODULE_DESCRIPTION("TAOS tsl2583 ambient light sensor driver");
MODULE_LICENSE("GPL");
