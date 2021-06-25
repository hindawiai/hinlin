<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010 Christoph Mair <christoph.mair@gmail.com>
 * Copyright (c) 2012 Bosch Sensortec GmbH
 * Copyright (c) 2012 Unixphere AB
 * Copyright (c) 2014 Intel Corporation
 * Copyright (c) 2016 Linus Walleij <linus.walleij@linaro.org>
 *
 * Driver क्रम Bosch Sensortec BMP180 and BMP280 digital pressure sensor.
 *
 * Datasheet:
 * https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMP180-DS000-121.pdf
 * https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMP280-DS001-12.pdf
 * https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280_DS001-11.pdf
 */

#घोषणा pr_fmt(fmt) "bmp280: " fmt

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h> /* For irq_get_irq_data() */
#समावेश <linux/completion.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/अक्रमom.h>

#समावेश "bmp280.h"

/*
 * These क्रमागतs are used क्रम indexing पूर्णांकo the array of calibration
 * coefficients क्रम BMP180.
 */
क्रमागत अणु AC1, AC2, AC3, AC4, AC5, AC6, B1, B2, MB, MC, MD पूर्ण;

काष्ठा bmp180_calib अणु
	s16 AC1;
	s16 AC2;
	s16 AC3;
	u16 AC4;
	u16 AC5;
	u16 AC6;
	s16 B1;
	s16 B2;
	s16 MB;
	s16 MC;
	s16 MD;
पूर्ण;

/* See datasheet Section 4.2.2. */
काष्ठा bmp280_calib अणु
	u16 T1;
	s16 T2;
	s16 T3;
	u16 P1;
	s16 P2;
	s16 P3;
	s16 P4;
	s16 P5;
	s16 P6;
	s16 P7;
	s16 P8;
	s16 P9;
	u8  H1;
	s16 H2;
	u8  H3;
	s16 H4;
	s16 H5;
	s8  H6;
पूर्ण;

अटल स्थिर अक्षर *स्थिर bmp280_supply_names[] = अणु
	"vddd", "vdda"
पूर्ण;

#घोषणा BMP280_NUM_SUPPLIES ARRAY_SIZE(bmp280_supply_names)

काष्ठा bmp280_data अणु
	काष्ठा device *dev;
	काष्ठा mutex lock;
	काष्ठा regmap *regmap;
	काष्ठा completion करोne;
	bool use_eoc;
	स्थिर काष्ठा bmp280_chip_info *chip_info;
	जोड़ अणु
		काष्ठा bmp180_calib bmp180;
		काष्ठा bmp280_calib bmp280;
	पूर्ण calib;
	काष्ठा regulator_bulk_data supplies[BMP280_NUM_SUPPLIES];
	अचिन्हित पूर्णांक start_up_समय; /* in microseconds */

	/* log of base 2 of oversampling rate */
	u8 oversampling_press;
	u8 oversampling_temp;
	u8 oversampling_humid;

	/*
	 * Carryover value from temperature conversion, used in pressure
	 * calculation.
	 */
	s32 t_fine;
पूर्ण;

काष्ठा bmp280_chip_info अणु
	स्थिर पूर्णांक *oversampling_temp_avail;
	पूर्णांक num_oversampling_temp_avail;

	स्थिर पूर्णांक *oversampling_press_avail;
	पूर्णांक num_oversampling_press_avail;

	स्थिर पूर्णांक *oversampling_humid_avail;
	पूर्णांक num_oversampling_humid_avail;

	पूर्णांक (*chip_config)(काष्ठा bmp280_data *);
	पूर्णांक (*पढ़ो_temp)(काष्ठा bmp280_data *, पूर्णांक *);
	पूर्णांक (*पढ़ो_press)(काष्ठा bmp280_data *, पूर्णांक *, पूर्णांक *);
	पूर्णांक (*पढ़ो_humid)(काष्ठा bmp280_data *, पूर्णांक *, पूर्णांक *);
पूर्ण;

/*
 * These क्रमागतs are used क्रम indexing पूर्णांकo the array of compensation
 * parameters क्रम BMP280.
 */
क्रमागत अणु T1, T2, T3 पूर्ण;
क्रमागत अणु P1, P2, P3, P4, P5, P6, P7, P8, P9 पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec bmp280_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				      BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				      BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
	पूर्ण,
	अणु
		.type = IIO_HUMIDITYRELATIVE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				      BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
	पूर्ण,
पूर्ण;

अटल पूर्णांक bmp280_पढ़ो_calib(काष्ठा bmp280_data *data,
			     काष्ठा bmp280_calib *calib,
			     अचिन्हित पूर्णांक chip)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक पंचांगp;
	__le16 l16;
	__be16 b16;
	काष्ठा device *dev = data->dev;
	__le16 t_buf[BMP280_COMP_TEMP_REG_COUNT / 2];
	__le16 p_buf[BMP280_COMP_PRESS_REG_COUNT / 2];

	/* Read temperature calibration values. */
	ret = regmap_bulk_पढ़ो(data->regmap, BMP280_REG_COMP_TEMP_START,
			       t_buf, BMP280_COMP_TEMP_REG_COUNT);
	अगर (ret < 0) अणु
		dev_err(data->dev,
			"failed to read temperature calibration parameters\n");
		वापस ret;
	पूर्ण

	/* Toss the temperature calibration data पूर्णांकo the entropy pool */
	add_device_अक्रमomness(t_buf, माप(t_buf));

	calib->T1 = le16_to_cpu(t_buf[T1]);
	calib->T2 = le16_to_cpu(t_buf[T2]);
	calib->T3 = le16_to_cpu(t_buf[T3]);

	/* Read pressure calibration values. */
	ret = regmap_bulk_पढ़ो(data->regmap, BMP280_REG_COMP_PRESS_START,
			       p_buf, BMP280_COMP_PRESS_REG_COUNT);
	अगर (ret < 0) अणु
		dev_err(data->dev,
			"failed to read pressure calibration parameters\n");
		वापस ret;
	पूर्ण

	/* Toss the pressure calibration data पूर्णांकo the entropy pool */
	add_device_अक्रमomness(p_buf, माप(p_buf));

	calib->P1 = le16_to_cpu(p_buf[P1]);
	calib->P2 = le16_to_cpu(p_buf[P2]);
	calib->P3 = le16_to_cpu(p_buf[P3]);
	calib->P4 = le16_to_cpu(p_buf[P4]);
	calib->P5 = le16_to_cpu(p_buf[P5]);
	calib->P6 = le16_to_cpu(p_buf[P6]);
	calib->P7 = le16_to_cpu(p_buf[P7]);
	calib->P8 = le16_to_cpu(p_buf[P8]);
	calib->P9 = le16_to_cpu(p_buf[P9]);

	/*
	 * Read humidity calibration values.
	 * Due to some odd रेजिस्टर addressing we cannot just
	 * करो a big bulk पढ़ो. Instead, we have to पढ़ो each Hx
	 * value separately and someबार करो some bit shअगरting...
	 * Humidity data is only available on BME280.
	 */
	अगर (chip != BME280_CHIP_ID)
		वापस 0;

	ret = regmap_पढ़ो(data->regmap, BMP280_REG_COMP_H1, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read H1 comp value\n");
		वापस ret;
	पूर्ण
	calib->H1 = पंचांगp;

	ret = regmap_bulk_पढ़ो(data->regmap, BMP280_REG_COMP_H2, &l16, 2);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read H2 comp value\n");
		वापस ret;
	पूर्ण
	calib->H2 = sign_extend32(le16_to_cpu(l16), 15);

	ret = regmap_पढ़ो(data->regmap, BMP280_REG_COMP_H3, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read H3 comp value\n");
		वापस ret;
	पूर्ण
	calib->H3 = पंचांगp;

	ret = regmap_bulk_पढ़ो(data->regmap, BMP280_REG_COMP_H4, &b16, 2);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read H4 comp value\n");
		वापस ret;
	पूर्ण
	calib->H4 = sign_extend32(((be16_to_cpu(b16) >> 4) & 0xff0) |
				  (be16_to_cpu(b16) & 0xf), 11);

	ret = regmap_bulk_पढ़ो(data->regmap, BMP280_REG_COMP_H5, &l16, 2);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read H5 comp value\n");
		वापस ret;
	पूर्ण
	calib->H5 = sign_extend32(((le16_to_cpu(l16) >> 4) & 0xfff), 11);

	ret = regmap_पढ़ो(data->regmap, BMP280_REG_COMP_H6, &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read H6 comp value\n");
		वापस ret;
	पूर्ण
	calib->H6 = sign_extend32(पंचांगp, 7);

	वापस 0;
पूर्ण
/*
 * Returns humidity in percent, resolution is 0.01 percent. Output value of
 * "47445" represents 47445/1024 = 46.333 %RH.
 *
 * Taken from BME280 datasheet, Section 4.2.3, "Compensation formula".
 */
अटल u32 bmp280_compensate_humidity(काष्ठा bmp280_data *data,
				      s32 adc_humidity)
अणु
	s32 var;
	काष्ठा bmp280_calib *calib = &data->calib.bmp280;

	var = ((s32)data->t_fine) - (s32)76800;
	var = ((((adc_humidity << 14) - (calib->H4 << 20) - (calib->H5 * var))
		+ (s32)16384) >> 15) * (((((((var * calib->H6) >> 10)
		* (((var * (s32)calib->H3) >> 11) + (s32)32768)) >> 10)
		+ (s32)2097152) * calib->H2 + 8192) >> 14);
	var -= ((((var >> 15) * (var >> 15)) >> 7) * (s32)calib->H1) >> 4;

	var = clamp_val(var, 0, 419430400);

	वापस var >> 12;
पूर्ण;

/*
 * Returns temperature in DegC, resolution is 0.01 DegC.  Output value of
 * "5123" equals 51.23 DegC.  t_fine carries fine temperature as global
 * value.
 *
 * Taken from datasheet, Section 3.11.3, "Compensation formula".
 */
अटल s32 bmp280_compensate_temp(काष्ठा bmp280_data *data,
				  s32 adc_temp)
अणु
	s32 var1, var2;
	काष्ठा bmp280_calib *calib = &data->calib.bmp280;

	var1 = (((adc_temp >> 3) - ((s32)calib->T1 << 1)) *
		((s32)calib->T2)) >> 11;
	var2 = (((((adc_temp >> 4) - ((s32)calib->T1)) *
		  ((adc_temp >> 4) - ((s32)calib->T1))) >> 12) *
		((s32)calib->T3)) >> 14;
	data->t_fine = var1 + var2;

	वापस (data->t_fine * 5 + 128) >> 8;
पूर्ण

/*
 * Returns pressure in Pa as अचिन्हित 32 bit पूर्णांकeger in Q24.8 क्रमmat (24
 * पूर्णांकeger bits and 8 fractional bits).  Output value of "24674867"
 * represents 24674867/256 = 96386.2 Pa = 963.862 hPa
 *
 * Taken from datasheet, Section 3.11.3, "Compensation formula".
 */
अटल u32 bmp280_compensate_press(काष्ठा bmp280_data *data,
				   s32 adc_press)
अणु
	s64 var1, var2, p;
	काष्ठा bmp280_calib *calib = &data->calib.bmp280;

	var1 = ((s64)data->t_fine) - 128000;
	var2 = var1 * var1 * (s64)calib->P6;
	var2 += (var1 * (s64)calib->P5) << 17;
	var2 += ((s64)calib->P4) << 35;
	var1 = ((var1 * var1 * (s64)calib->P3) >> 8) +
		((var1 * (s64)calib->P2) << 12);
	var1 = ((((s64)1) << 47) + var1) * ((s64)calib->P1) >> 33;

	अगर (var1 == 0)
		वापस 0;

	p = ((((s64)1048576 - adc_press) << 31) - var2) * 3125;
	p = भाग64_s64(p, var1);
	var1 = (((s64)calib->P9) * (p >> 13) * (p >> 13)) >> 25;
	var2 = ((s64)(calib->P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((s64)calib->P7) << 4);

	वापस (u32)p;
पूर्ण

अटल पूर्णांक bmp280_पढ़ो_temp(काष्ठा bmp280_data *data,
			    पूर्णांक *val)
अणु
	पूर्णांक ret;
	__be32 पंचांगp = 0;
	s32 adc_temp, comp_temp;

	ret = regmap_bulk_पढ़ो(data->regmap, BMP280_REG_TEMP_MSB, &पंचांगp, 3);
	अगर (ret < 0) अणु
		dev_err(data->dev, "failed to read temperature\n");
		वापस ret;
	पूर्ण

	adc_temp = be32_to_cpu(पंचांगp) >> 12;
	अगर (adc_temp == BMP280_TEMP_SKIPPED) अणु
		/* पढ़ोing was skipped */
		dev_err(data->dev, "reading temperature skipped\n");
		वापस -EIO;
	पूर्ण
	comp_temp = bmp280_compensate_temp(data, adc_temp);

	/*
	 * val might be शून्य अगर we're called by the पढ़ो_press routine,
	 * who only cares about the carry over t_fine value.
	 */
	अगर (val) अणु
		*val = comp_temp * 10;
		वापस IIO_VAL_INT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmp280_पढ़ो_press(काष्ठा bmp280_data *data,
			     पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;
	__be32 पंचांगp = 0;
	s32 adc_press;
	u32 comp_press;

	/* Read and compensate temperature so we get a पढ़ोing of t_fine. */
	ret = bmp280_पढ़ो_temp(data, शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_bulk_पढ़ो(data->regmap, BMP280_REG_PRESS_MSB, &पंचांगp, 3);
	अगर (ret < 0) अणु
		dev_err(data->dev, "failed to read pressure\n");
		वापस ret;
	पूर्ण

	adc_press = be32_to_cpu(पंचांगp) >> 12;
	अगर (adc_press == BMP280_PRESS_SKIPPED) अणु
		/* पढ़ोing was skipped */
		dev_err(data->dev, "reading pressure skipped\n");
		वापस -EIO;
	पूर्ण
	comp_press = bmp280_compensate_press(data, adc_press);

	*val = comp_press;
	*val2 = 256000;

	वापस IIO_VAL_FRACTIONAL;
पूर्ण

अटल पूर्णांक bmp280_पढ़ो_humid(काष्ठा bmp280_data *data, पूर्णांक *val, पूर्णांक *val2)
अणु
	__be16 पंचांगp;
	पूर्णांक ret;
	s32 adc_humidity;
	u32 comp_humidity;

	/* Read and compensate temperature so we get a पढ़ोing of t_fine. */
	ret = bmp280_पढ़ो_temp(data, शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_bulk_पढ़ो(data->regmap, BMP280_REG_HUMIDITY_MSB, &पंचांगp, 2);
	अगर (ret < 0) अणु
		dev_err(data->dev, "failed to read humidity\n");
		वापस ret;
	पूर्ण

	adc_humidity = be16_to_cpu(पंचांगp);
	अगर (adc_humidity == BMP280_HUMIDITY_SKIPPED) अणु
		/* पढ़ोing was skipped */
		dev_err(data->dev, "reading humidity skipped\n");
		वापस -EIO;
	पूर्ण
	comp_humidity = bmp280_compensate_humidity(data, adc_humidity);

	*val = comp_humidity * 1000 / 1024;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक bmp280_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा bmp280_data *data = iio_priv(indio_dev);

	pm_runसमय_get_sync(data->dev);
	mutex_lock(&data->lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_HUMIDITYRELATIVE:
			ret = data->chip_info->पढ़ो_humid(data, val, val2);
			अवरोध;
		हाल IIO_PRESSURE:
			ret = data->chip_info->पढ़ो_press(data, val, val2);
			अवरोध;
		हाल IIO_TEMP:
			ret = data->chip_info->पढ़ो_temp(data, val);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		चयन (chan->type) अणु
		हाल IIO_HUMIDITYRELATIVE:
			*val = 1 << data->oversampling_humid;
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_PRESSURE:
			*val = 1 << data->oversampling_press;
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_TEMP:
			*val = 1 << data->oversampling_temp;
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&data->lock);
	pm_runसमय_mark_last_busy(data->dev);
	pm_runसमय_put_स्वतःsuspend(data->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक bmp280_ग_लिखो_oversampling_ratio_humid(काष्ठा bmp280_data *data,
					       पूर्णांक val)
अणु
	पूर्णांक i;
	स्थिर पूर्णांक *avail = data->chip_info->oversampling_humid_avail;
	स्थिर पूर्णांक n = data->chip_info->num_oversampling_humid_avail;

	क्रम (i = 0; i < n; i++) अणु
		अगर (avail[i] == val) अणु
			data->oversampling_humid = ilog2(val);

			वापस data->chip_info->chip_config(data);
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmp280_ग_लिखो_oversampling_ratio_temp(काष्ठा bmp280_data *data,
					       पूर्णांक val)
अणु
	पूर्णांक i;
	स्थिर पूर्णांक *avail = data->chip_info->oversampling_temp_avail;
	स्थिर पूर्णांक n = data->chip_info->num_oversampling_temp_avail;

	क्रम (i = 0; i < n; i++) अणु
		अगर (avail[i] == val) अणु
			data->oversampling_temp = ilog2(val);

			वापस data->chip_info->chip_config(data);
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmp280_ग_लिखो_oversampling_ratio_press(काष्ठा bmp280_data *data,
					       पूर्णांक val)
अणु
	पूर्णांक i;
	स्थिर पूर्णांक *avail = data->chip_info->oversampling_press_avail;
	स्थिर पूर्णांक n = data->chip_info->num_oversampling_press_avail;

	क्रम (i = 0; i < n; i++) अणु
		अगर (avail[i] == val) अणु
			data->oversampling_press = ilog2(val);

			वापस data->chip_info->chip_config(data);
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmp280_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक ret = 0;
	काष्ठा bmp280_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		pm_runसमय_get_sync(data->dev);
		mutex_lock(&data->lock);
		चयन (chan->type) अणु
		हाल IIO_HUMIDITYRELATIVE:
			ret = bmp280_ग_लिखो_oversampling_ratio_humid(data, val);
			अवरोध;
		हाल IIO_PRESSURE:
			ret = bmp280_ग_लिखो_oversampling_ratio_press(data, val);
			अवरोध;
		हाल IIO_TEMP:
			ret = bmp280_ग_लिखो_oversampling_ratio_temp(data, val);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		mutex_unlock(&data->lock);
		pm_runसमय_mark_last_busy(data->dev);
		pm_runसमय_put_स्वतःsuspend(data->dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bmp280_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			     दीर्घ mask)
अणु
	काष्ठा bmp280_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		चयन (chan->type) अणु
		हाल IIO_PRESSURE:
			*vals = data->chip_info->oversampling_press_avail;
			*length = data->chip_info->num_oversampling_press_avail;
			अवरोध;
		हाल IIO_TEMP:
			*vals = data->chip_info->oversampling_temp_avail;
			*length = data->chip_info->num_oversampling_temp_avail;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		*type = IIO_VAL_INT;
		वापस IIO_AVAIL_LIST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info bmp280_info = अणु
	.पढ़ो_raw = &bmp280_पढ़ो_raw,
	.पढ़ो_avail = &bmp280_पढ़ो_avail,
	.ग_लिखो_raw = &bmp280_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक bmp280_chip_config(काष्ठा bmp280_data *data)
अणु
	पूर्णांक ret;
	u8 osrs = BMP280_OSRS_TEMP_X(data->oversampling_temp + 1) |
		  BMP280_OSRS_PRESS_X(data->oversampling_press + 1);

	ret = regmap_ग_लिखो_bits(data->regmap, BMP280_REG_CTRL_MEAS,
				 BMP280_OSRS_TEMP_MASK |
				 BMP280_OSRS_PRESS_MASK |
				 BMP280_MODE_MASK,
				 osrs | BMP280_MODE_NORMAL);
	अगर (ret < 0) अणु
		dev_err(data->dev,
			"failed to write ctrl_meas register\n");
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(data->regmap, BMP280_REG_CONFIG,
				 BMP280_FILTER_MASK,
				 BMP280_FILTER_4X);
	अगर (ret < 0) अणु
		dev_err(data->dev,
			"failed to write config register\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर पूर्णांक bmp280_oversampling_avail[] = अणु 1, 2, 4, 8, 16 पूर्ण;

अटल स्थिर काष्ठा bmp280_chip_info bmp280_chip_info = अणु
	.oversampling_temp_avail = bmp280_oversampling_avail,
	.num_oversampling_temp_avail = ARRAY_SIZE(bmp280_oversampling_avail),

	.oversampling_press_avail = bmp280_oversampling_avail,
	.num_oversampling_press_avail = ARRAY_SIZE(bmp280_oversampling_avail),

	.chip_config = bmp280_chip_config,
	.पढ़ो_temp = bmp280_पढ़ो_temp,
	.पढ़ो_press = bmp280_पढ़ो_press,
पूर्ण;

अटल पूर्णांक bme280_chip_config(काष्ठा bmp280_data *data)
अणु
	पूर्णांक ret;
	u8 osrs = BMP280_OSRS_HUMIDITIY_X(data->oversampling_humid + 1);

	/*
	 * Oversampling of humidity must be set beक्रमe oversampling of
	 * temperature/pressure is set to become effective.
	 */
	ret = regmap_update_bits(data->regmap, BMP280_REG_CTRL_HUMIDITY,
				  BMP280_OSRS_HUMIDITY_MASK, osrs);

	अगर (ret < 0)
		वापस ret;

	वापस bmp280_chip_config(data);
पूर्ण

अटल स्थिर काष्ठा bmp280_chip_info bme280_chip_info = अणु
	.oversampling_temp_avail = bmp280_oversampling_avail,
	.num_oversampling_temp_avail = ARRAY_SIZE(bmp280_oversampling_avail),

	.oversampling_press_avail = bmp280_oversampling_avail,
	.num_oversampling_press_avail = ARRAY_SIZE(bmp280_oversampling_avail),

	.oversampling_humid_avail = bmp280_oversampling_avail,
	.num_oversampling_humid_avail = ARRAY_SIZE(bmp280_oversampling_avail),

	.chip_config = bme280_chip_config,
	.पढ़ो_temp = bmp280_पढ़ो_temp,
	.पढ़ो_press = bmp280_पढ़ो_press,
	.पढ़ो_humid = bmp280_पढ़ो_humid,
पूर्ण;

अटल पूर्णांक bmp180_measure(काष्ठा bmp280_data *data, u8 ctrl_meas)
अणु
	पूर्णांक ret;
	स्थिर पूर्णांक conversion_समय_max[] = अणु 4500, 7500, 13500, 25500 पूर्ण;
	अचिन्हित पूर्णांक delay_us;
	अचिन्हित पूर्णांक ctrl;

	अगर (data->use_eoc)
		reinit_completion(&data->करोne);

	ret = regmap_ग_लिखो(data->regmap, BMP280_REG_CTRL_MEAS, ctrl_meas);
	अगर (ret)
		वापस ret;

	अगर (data->use_eoc) अणु
		/*
		 * If we have a completion पूर्णांकerrupt, use it, रुको up to
		 * 100ms. The दीर्घest conversion समय listed is 76.5 ms क्रम
		 * advanced resolution mode.
		 */
		ret = रुको_क्रम_completion_समयout(&data->करोne,
						  1 + msecs_to_jअगरfies(100));
		अगर (!ret)
			dev_err(data->dev, "timeout waiting for completion\n");
	पूर्ण अन्यथा अणु
		अगर (ctrl_meas == BMP180_MEAS_TEMP)
			delay_us = 4500;
		अन्यथा
			delay_us =
				conversion_समय_max[data->oversampling_press];

		usleep_range(delay_us, delay_us + 1000);
	पूर्ण

	ret = regmap_पढ़ो(data->regmap, BMP280_REG_CTRL_MEAS, &ctrl);
	अगर (ret)
		वापस ret;

	/* The value of this bit reset to "0" after conversion is complete */
	अगर (ctrl & BMP180_MEAS_SCO)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक bmp180_पढ़ो_adc_temp(काष्ठा bmp280_data *data, पूर्णांक *val)
अणु
	__be16 पंचांगp;
	पूर्णांक ret;

	ret = bmp180_measure(data, BMP180_MEAS_TEMP);
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_पढ़ो(data->regmap, BMP180_REG_OUT_MSB, &पंचांगp, 2);
	अगर (ret)
		वापस ret;

	*val = be16_to_cpu(पंचांगp);

	वापस 0;
पूर्ण

अटल पूर्णांक bmp180_पढ़ो_calib(काष्ठा bmp280_data *data,
			     काष्ठा bmp180_calib *calib)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	__be16 buf[BMP180_REG_CALIB_COUNT / 2];

	ret = regmap_bulk_पढ़ो(data->regmap, BMP180_REG_CALIB_START, buf,
			       माप(buf));

	अगर (ret < 0)
		वापस ret;

	/* None of the words has the value 0 or 0xFFFF */
	क्रम (i = 0; i < ARRAY_SIZE(buf); i++) अणु
		अगर (buf[i] == cpu_to_be16(0) || buf[i] == cpu_to_be16(0xffff))
			वापस -EIO;
	पूर्ण

	/* Toss the calibration data पूर्णांकo the entropy pool */
	add_device_अक्रमomness(buf, माप(buf));

	calib->AC1 = be16_to_cpu(buf[AC1]);
	calib->AC2 = be16_to_cpu(buf[AC2]);
	calib->AC3 = be16_to_cpu(buf[AC3]);
	calib->AC4 = be16_to_cpu(buf[AC4]);
	calib->AC5 = be16_to_cpu(buf[AC5]);
	calib->AC6 = be16_to_cpu(buf[AC6]);
	calib->B1 = be16_to_cpu(buf[B1]);
	calib->B2 = be16_to_cpu(buf[B2]);
	calib->MB = be16_to_cpu(buf[MB]);
	calib->MC = be16_to_cpu(buf[MC]);
	calib->MD = be16_to_cpu(buf[MD]);

	वापस 0;
पूर्ण

/*
 * Returns temperature in DegC, resolution is 0.1 DegC.
 * t_fine carries fine temperature as global value.
 *
 * Taken from datasheet, Section 3.5, "Calculating pressure and temperature".
 */
अटल s32 bmp180_compensate_temp(काष्ठा bmp280_data *data, s32 adc_temp)
अणु
	s32 x1, x2;
	काष्ठा bmp180_calib *calib = &data->calib.bmp180;

	x1 = ((adc_temp - calib->AC6) * calib->AC5) >> 15;
	x2 = (calib->MC << 11) / (x1 + calib->MD);
	data->t_fine = x1 + x2;

	वापस (data->t_fine + 8) >> 4;
पूर्ण

अटल पूर्णांक bmp180_पढ़ो_temp(काष्ठा bmp280_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret;
	s32 adc_temp, comp_temp;

	ret = bmp180_पढ़ो_adc_temp(data, &adc_temp);
	अगर (ret)
		वापस ret;

	comp_temp = bmp180_compensate_temp(data, adc_temp);

	/*
	 * val might be शून्य अगर we're called by the पढ़ो_press routine,
	 * who only cares about the carry over t_fine value.
	 */
	अगर (val) अणु
		*val = comp_temp * 100;
		वापस IIO_VAL_INT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmp180_पढ़ो_adc_press(काष्ठा bmp280_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret;
	__be32 पंचांगp = 0;
	u8 oss = data->oversampling_press;

	ret = bmp180_measure(data, BMP180_MEAS_PRESS_X(oss));
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_पढ़ो(data->regmap, BMP180_REG_OUT_MSB, &पंचांगp, 3);
	अगर (ret)
		वापस ret;

	*val = (be32_to_cpu(पंचांगp) >> 8) >> (8 - oss);

	वापस 0;
पूर्ण

/*
 * Returns pressure in Pa, resolution is 1 Pa.
 *
 * Taken from datasheet, Section 3.5, "Calculating pressure and temperature".
 */
अटल u32 bmp180_compensate_press(काष्ठा bmp280_data *data, s32 adc_press)
अणु
	s32 x1, x2, x3, p;
	s32 b3, b6;
	u32 b4, b7;
	s32 oss = data->oversampling_press;
	काष्ठा bmp180_calib *calib = &data->calib.bmp180;

	b6 = data->t_fine - 4000;
	x1 = (calib->B2 * (b6 * b6 >> 12)) >> 11;
	x2 = calib->AC2 * b6 >> 11;
	x3 = x1 + x2;
	b3 = ((((s32)calib->AC1 * 4 + x3) << oss) + 2) / 4;
	x1 = calib->AC3 * b6 >> 13;
	x2 = (calib->B1 * ((b6 * b6) >> 12)) >> 16;
	x3 = (x1 + x2 + 2) >> 2;
	b4 = calib->AC4 * (u32)(x3 + 32768) >> 15;
	b7 = ((u32)adc_press - b3) * (50000 >> oss);
	अगर (b7 < 0x80000000)
		p = (b7 * 2) / b4;
	अन्यथा
		p = (b7 / b4) * 2;

	x1 = (p >> 8) * (p >> 8);
	x1 = (x1 * 3038) >> 16;
	x2 = (-7357 * p) >> 16;

	वापस p + ((x1 + x2 + 3791) >> 4);
पूर्ण

अटल पूर्णांक bmp180_पढ़ो_press(काष्ठा bmp280_data *data,
			     पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;
	s32 adc_press;
	u32 comp_press;

	/* Read and compensate temperature so we get a पढ़ोing of t_fine. */
	ret = bmp180_पढ़ो_temp(data, शून्य);
	अगर (ret)
		वापस ret;

	ret = bmp180_पढ़ो_adc_press(data, &adc_press);
	अगर (ret)
		वापस ret;

	comp_press = bmp180_compensate_press(data, adc_press);

	*val = comp_press;
	*val2 = 1000;

	वापस IIO_VAL_FRACTIONAL;
पूर्ण

अटल पूर्णांक bmp180_chip_config(काष्ठा bmp280_data *data)
अणु
	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक bmp180_oversampling_temp_avail[] = अणु 1 पूर्ण;
अटल स्थिर पूर्णांक bmp180_oversampling_press_avail[] = अणु 1, 2, 4, 8 पूर्ण;

अटल स्थिर काष्ठा bmp280_chip_info bmp180_chip_info = अणु
	.oversampling_temp_avail = bmp180_oversampling_temp_avail,
	.num_oversampling_temp_avail =
		ARRAY_SIZE(bmp180_oversampling_temp_avail),

	.oversampling_press_avail = bmp180_oversampling_press_avail,
	.num_oversampling_press_avail =
		ARRAY_SIZE(bmp180_oversampling_press_avail),

	.chip_config = bmp180_chip_config,
	.पढ़ो_temp = bmp180_पढ़ो_temp,
	.पढ़ो_press = bmp180_पढ़ो_press,
पूर्ण;

अटल irqवापस_t bmp085_eoc_irq(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा bmp280_data *data = d;

	complete(&data->करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bmp085_fetch_eoc_irq(काष्ठा device *dev,
				स्थिर अक्षर *name,
				पूर्णांक irq,
				काष्ठा bmp280_data *data)
अणु
	अचिन्हित दीर्घ irq_trig;
	पूर्णांक ret;

	irq_trig = irqd_get_trigger_type(irq_get_irq_data(irq));
	अगर (irq_trig != IRQF_TRIGGER_RISING) अणु
		dev_err(dev, "non-rising trigger given for EOC interrupt, trying to enforce it\n");
		irq_trig = IRQF_TRIGGER_RISING;
	पूर्ण

	init_completion(&data->करोne);

	ret = devm_request_thपढ़ोed_irq(dev,
			irq,
			bmp085_eoc_irq,
			शून्य,
			irq_trig,
			name,
			data);
	अगर (ret) अणु
		/* Bail out without IRQ but keep the driver in place */
		dev_err(dev, "unable to request DRDY IRQ\n");
		वापस 0;
	पूर्ण

	data->use_eoc = true;
	वापस 0;
पूर्ण

अटल व्योम bmp280_pm_disable(व्योम *data)
अणु
	काष्ठा device *dev = data;

	pm_runसमय_get_sync(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
पूर्ण

अटल व्योम bmp280_regulators_disable(व्योम *data)
अणु
	काष्ठा regulator_bulk_data *supplies = data;

	regulator_bulk_disable(BMP280_NUM_SUPPLIES, supplies);
पूर्ण

पूर्णांक bmp280_common_probe(काष्ठा device *dev,
			काष्ठा regmap *regmap,
			अचिन्हित पूर्णांक chip,
			स्थिर अक्षर *name,
			पूर्णांक irq)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा bmp280_data *data;
	अचिन्हित पूर्णांक chip_id;
	काष्ठा gpio_desc *gpiod;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	mutex_init(&data->lock);
	data->dev = dev;

	indio_dev->name = name;
	indio_dev->channels = bmp280_channels;
	indio_dev->info = &bmp280_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	चयन (chip) अणु
	हाल BMP180_CHIP_ID:
		indio_dev->num_channels = 2;
		data->chip_info = &bmp180_chip_info;
		data->oversampling_press = ilog2(8);
		data->oversampling_temp = ilog2(1);
		data->start_up_समय = 10000;
		अवरोध;
	हाल BMP280_CHIP_ID:
		indio_dev->num_channels = 2;
		data->chip_info = &bmp280_chip_info;
		data->oversampling_press = ilog2(16);
		data->oversampling_temp = ilog2(2);
		data->start_up_समय = 2000;
		अवरोध;
	हाल BME280_CHIP_ID:
		indio_dev->num_channels = 3;
		data->chip_info = &bme280_chip_info;
		data->oversampling_press = ilog2(16);
		data->oversampling_humid = ilog2(16);
		data->oversampling_temp = ilog2(2);
		data->start_up_समय = 2000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Bring up regulators */
	regulator_bulk_set_supply_names(data->supplies,
					bmp280_supply_names,
					BMP280_NUM_SUPPLIES);

	ret = devm_regulator_bulk_get(dev,
				      BMP280_NUM_SUPPLIES, data->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed to get regulators\n");
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(BMP280_NUM_SUPPLIES, data->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed to enable regulators\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, bmp280_regulators_disable,
				       data->supplies);
	अगर (ret)
		वापस ret;

	/* Wait to make sure we started up properly */
	usleep_range(data->start_up_समय, data->start_up_समय + 100);

	/* Bring chip out of reset अगर there is an asचिन्हित GPIO line */
	gpiod = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	/* Deनिश्चित the संकेत */
	अगर (gpiod) अणु
		dev_info(dev, "release reset\n");
		gpiod_set_value(gpiod, 0);
	पूर्ण

	data->regmap = regmap;
	ret = regmap_पढ़ो(regmap, BMP280_REG_ID, &chip_id);
	अगर (ret < 0)
		वापस ret;
	अगर (chip_id != chip) अणु
		dev_err(dev, "bad chip id: expected %x got %x\n",
			chip, chip_id);
		वापस -EINVAL;
	पूर्ण

	ret = data->chip_info->chip_config(data);
	अगर (ret < 0)
		वापस ret;

	dev_set_drvdata(dev, indio_dev);

	/*
	 * Some chips have calibration parameters "programmed पूर्णांकo the devices'
	 * non-अस्थिर memory during production". Let's पढ़ो them out at probe
	 * समय once. They will not change.
	 */
	अगर (chip_id  == BMP180_CHIP_ID) अणु
		ret = bmp180_पढ़ो_calib(data, &data->calib.bmp180);
		अगर (ret < 0) अणु
			dev_err(data->dev,
				"failed to read calibration coefficients\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (chip_id == BMP280_CHIP_ID || chip_id == BME280_CHIP_ID) अणु
		ret = bmp280_पढ़ो_calib(data, &data->calib.bmp280, chip_id);
		अगर (ret < 0) अणु
			dev_err(data->dev,
				"failed to read calibration coefficients\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Attempt to grab an optional EOC IRQ - only the BMP085 has this
	 * however as it happens, the BMP085 shares the chip ID of BMP180
	 * so we look क्रम an IRQ अगर we have that.
	 */
	अगर (irq > 0 || (chip_id  == BMP180_CHIP_ID)) अणु
		ret = bmp085_fetch_eoc_irq(dev, name, irq, data);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Enable runसमय PM */
	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	/*
	 * Set स्वतःsuspend to two orders of magnitude larger than the
	 * start-up समय.
	 */
	pm_runसमय_set_स्वतःsuspend_delay(dev, data->start_up_समय / 10);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_put(dev);

	ret = devm_add_action_or_reset(dev, bmp280_pm_disable, dev);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण
EXPORT_SYMBOL(bmp280_common_probe);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bmp280_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmp280_data *data = iio_priv(indio_dev);

	वापस regulator_bulk_disable(BMP280_NUM_SUPPLIES, data->supplies);
पूर्ण

अटल पूर्णांक bmp280_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmp280_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(BMP280_NUM_SUPPLIES, data->supplies);
	अगर (ret)
		वापस ret;
	usleep_range(data->start_up_समय, data->start_up_समय + 100);
	वापस data->chip_info->chip_config(data);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

स्थिर काष्ठा dev_pm_ops bmp280_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(bmp280_runसमय_suspend,
			   bmp280_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL(bmp280_dev_pm_ops);

MODULE_AUTHOR("Vlad Dogaru <vlad.dogaru@intel.com>");
MODULE_DESCRIPTION("Driver for Bosch Sensortec BMP180/BMP280 pressure and temperature sensor");
MODULE_LICENSE("GPL v2");
