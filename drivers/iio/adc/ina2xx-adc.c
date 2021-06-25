<शैली गुरु>
/*
 * INA2XX Current and Power Monitors
 *
 * Copyright 2015 Baylibre SAS.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Based on linux/drivers/iio/adc/ad7291.c
 * Copyright 2010-2011 Analog Devices Inc.
 *
 * Based on linux/drivers/hwmon/ina2xx.c
 * Copyright 2012 Lothar Felten <l-felten@ti.com>
 *
 * Licensed under the GPL-2 or later.
 *
 * IIO driver क्रम INA219-220-226-230-231
 *
 * Configurable 7-bit I2C slave address from 0x40 to 0x4F
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/util_macros.h>

#समावेश <linux/platक्रमm_data/ina2xx.h>

/* INA2XX रेजिस्टरs definition */
#घोषणा INA2XX_CONFIG                   0x00
#घोषणा INA2XX_SHUNT_VOLTAGE            0x01	/* पढ़ोonly */
#घोषणा INA2XX_BUS_VOLTAGE              0x02	/* पढ़ोonly */
#घोषणा INA2XX_POWER                    0x03	/* पढ़ोonly */
#घोषणा INA2XX_CURRENT                  0x04	/* पढ़ोonly */
#घोषणा INA2XX_CALIBRATION              0x05

#घोषणा INA226_MASK_ENABLE		0x06
#घोषणा INA226_CVRF			BIT(3)

#घोषणा INA2XX_MAX_REGISTERS            8

/* settings - depend on use हाल */
#घोषणा INA219_CONFIG_DEFAULT           0x399F	/* PGA=1/8, BRNG=32V */
#घोषणा INA219_DEFAULT_IT		532
#घोषणा INA219_DEFAULT_BRNG             1   /* 32V */
#घोषणा INA219_DEFAULT_PGA              125 /* 1000/8 */
#घोषणा INA226_CONFIG_DEFAULT           0x4327
#घोषणा INA226_DEFAULT_AVG              4
#घोषणा INA226_DEFAULT_IT		1110

#घोषणा INA2XX_RSHUNT_DEFAULT           10000

/*
 * bit masks क्रम पढ़ोing the settings in the configuration रेजिस्टर
 * FIXME: use regmap_fields.
 */
#घोषणा INA2XX_MODE_MASK	GENMASK(3, 0)

/* Gain क्रम VShunt: 1/8 (शेष), 1/4, 1/2, 1 */
#घोषणा INA219_PGA_MASK		GENMASK(12, 11)
#घोषणा INA219_SHIFT_PGA(val)	((val) << 11)

/* VBus range: 32V (शेष), 16V */
#घोषणा INA219_BRNG_MASK	BIT(13)
#घोषणा INA219_SHIFT_BRNG(val)	((val) << 13)

/* Averaging क्रम VBus/VShunt/Power */
#घोषणा INA226_AVG_MASK		GENMASK(11, 9)
#घोषणा INA226_SHIFT_AVG(val)	((val) << 9)

/* Integration समय क्रम VBus */
#घोषणा INA219_ITB_MASK		GENMASK(10, 7)
#घोषणा INA219_SHIFT_ITB(val)	((val) << 7)
#घोषणा INA226_ITB_MASK		GENMASK(8, 6)
#घोषणा INA226_SHIFT_ITB(val)	((val) << 6)

/* Integration समय क्रम VShunt */
#घोषणा INA219_ITS_MASK		GENMASK(6, 3)
#घोषणा INA219_SHIFT_ITS(val)	((val) << 3)
#घोषणा INA226_ITS_MASK		GENMASK(5, 3)
#घोषणा INA226_SHIFT_ITS(val)	((val) << 3)

/* INA219 Bus voltage रेजिस्टर, low bits are flags */
#घोषणा INA219_OVF		BIT(0)
#घोषणा INA219_CNVR		BIT(1)
#घोषणा INA219_BUS_VOLTAGE_SHIFT	3

/* Cosmetic macro giving the sampling period क्रम a full P=UxI cycle */
#घोषणा SAMPLING_PERIOD(c)	((c->पूर्णांक_समय_vbus + c->पूर्णांक_समय_vshunt) \
				 * c->avg)

अटल bool ina2xx_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg == INA2XX_CONFIG) || (reg > INA2XX_CURRENT);
पूर्ण

अटल bool ina2xx_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg != INA2XX_CONFIG);
पूर्ण

अटल अंतरभूत bool is_चिन्हित_reg(अचिन्हित पूर्णांक reg)
अणु
	वापस (reg == INA2XX_SHUNT_VOLTAGE) || (reg == INA2XX_CURRENT);
पूर्ण

अटल स्थिर काष्ठा regmap_config ina2xx_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = INA2XX_MAX_REGISTERS,
	.ग_लिखोable_reg = ina2xx_is_ग_लिखोable_reg,
	.अस्थिर_reg = ina2xx_is_अस्थिर_reg,
पूर्ण;

क्रमागत ina2xx_ids अणु ina219, ina226 पूर्ण;

काष्ठा ina2xx_config अणु
	u16 config_शेष;
	पूर्णांक calibration_value;
	पूर्णांक shunt_voltage_lsb;	/* nV */
	पूर्णांक bus_voltage_shअगरt;	/* position of lsb */
	पूर्णांक bus_voltage_lsb;	/* uV */
	/* fixed relation between current and घातer lsb, uW/uA */
	पूर्णांक घातer_lsb_factor;
	क्रमागत ina2xx_ids chip_id;
पूर्ण;

काष्ठा ina2xx_chip_info अणु
	काष्ठा regmap *regmap;
	काष्ठा task_काष्ठा *task;
	स्थिर काष्ठा ina2xx_config *config;
	काष्ठा mutex state_lock;
	अचिन्हित पूर्णांक shunt_resistor_uohm;
	पूर्णांक avg;
	पूर्णांक पूर्णांक_समय_vbus; /* Bus voltage पूर्णांकegration समय uS */
	पूर्णांक पूर्णांक_समय_vshunt; /* Shunt voltage पूर्णांकegration समय uS */
	पूर्णांक range_vbus; /* Bus voltage maximum in V */
	पूर्णांक pga_gain_vshunt; /* Shunt voltage PGA gain */
	bool allow_async_पढ़ोout;
	/* data buffer needs space क्रम channel data and बारtamp */
	काष्ठा अणु
		u16 chan[4];
		u64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

अटल स्थिर काष्ठा ina2xx_config ina2xx_config[] = अणु
	[ina219] = अणु
		.config_शेष = INA219_CONFIG_DEFAULT,
		.calibration_value = 4096,
		.shunt_voltage_lsb = 10000,
		.bus_voltage_shअगरt = INA219_BUS_VOLTAGE_SHIFT,
		.bus_voltage_lsb = 4000,
		.घातer_lsb_factor = 20,
		.chip_id = ina219,
	पूर्ण,
	[ina226] = अणु
		.config_शेष = INA226_CONFIG_DEFAULT,
		.calibration_value = 2048,
		.shunt_voltage_lsb = 2500,
		.bus_voltage_shअगरt = 0,
		.bus_voltage_lsb = 1250,
		.घातer_lsb_factor = 25,
		.chip_id = ina226,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ina2xx_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा ina2xx_chip_info *chip = iio_priv(indio_dev);
	अचिन्हित पूर्णांक regval;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = regmap_पढ़ो(chip->regmap, chan->address, &regval);
		अगर (ret)
			वापस ret;

		अगर (is_चिन्हित_reg(chan->address))
			*val = (s16) regval;
		अन्यथा
			*val  = regval;

		अगर (chan->address == INA2XX_BUS_VOLTAGE)
			*val >>= chip->config->bus_voltage_shअगरt;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		*val = chip->avg;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		अगर (chan->address == INA2XX_SHUNT_VOLTAGE)
			*val2 = chip->पूर्णांक_समय_vshunt;
		अन्यथा
			*val2 = chip->पूर्णांक_समय_vbus;

		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		/*
		 * Sample freq is पढ़ो only, it is a consequence of
		 * 1/AVG*(CT_bus+CT_shunt).
		 */
		*val = DIV_ROUND_CLOSEST(1000000, SAMPLING_PERIOD(chip));

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->address) अणु
		हाल INA2XX_SHUNT_VOLTAGE:
			/* processed (mV) = raw * lsb(nV) / 1000000 */
			*val = chip->config->shunt_voltage_lsb;
			*val2 = 1000000;
			वापस IIO_VAL_FRACTIONAL;

		हाल INA2XX_BUS_VOLTAGE:
			/* processed (mV) = raw * lsb (uV) / 1000 */
			*val = chip->config->bus_voltage_lsb;
			*val2 = 1000;
			वापस IIO_VAL_FRACTIONAL;

		हाल INA2XX_CURRENT:
			/*
			 * processed (mA) = raw * current_lsb (mA)
			 * current_lsb (mA) = shunt_voltage_lsb (nV) /
			 *                    shunt_resistor (uOhm)
			 */
			*val = chip->config->shunt_voltage_lsb;
			*val2 = chip->shunt_resistor_uohm;
			वापस IIO_VAL_FRACTIONAL;

		हाल INA2XX_POWER:
			/*
			 * processed (mW) = raw * घातer_lsb (mW)
			 * घातer_lsb (mW) = घातer_lsb_factor (mW/mA) *
			 *                  current_lsb (mA)
			 */
			*val = chip->config->घातer_lsb_factor *
			       chip->config->shunt_voltage_lsb;
			*val2 = chip->shunt_resistor_uohm;
			वापस IIO_VAL_FRACTIONAL;
		पूर्ण
		वापस -EINVAL;

	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		चयन (chan->address) अणु
		हाल INA2XX_SHUNT_VOLTAGE:
			*val = chip->pga_gain_vshunt;
			*val2 = 1000;
			वापस IIO_VAL_FRACTIONAL;

		हाल INA2XX_BUS_VOLTAGE:
			*val = chip->range_vbus == 32 ? 1 : 2;
			वापस IIO_VAL_INT;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * Available averaging rates क्रम ina226. The indices correspond with
 * the bit values expected by the chip (according to the ina226 datasheet,
 * table 3 AVG bit settings, found at
 * https://www.ti.com/lit/ds/symlink/ina226.pdf.
 */
अटल स्थिर पूर्णांक ina226_avg_tab[] = अणु 1, 4, 16, 64, 128, 256, 512, 1024 पूर्ण;

अटल पूर्णांक ina226_set_average(काष्ठा ina2xx_chip_info *chip, अचिन्हित पूर्णांक val,
			      अचिन्हित पूर्णांक *config)
अणु
	पूर्णांक bits;

	अगर (val > 1024 || val < 1)
		वापस -EINVAL;

	bits = find_बंदst(val, ina226_avg_tab,
			    ARRAY_SIZE(ina226_avg_tab));

	chip->avg = ina226_avg_tab[bits];

	*config &= ~INA226_AVG_MASK;
	*config |= INA226_SHIFT_AVG(bits) & INA226_AVG_MASK;

	वापस 0;
पूर्ण

/* Conversion बार in uS */
अटल स्थिर पूर्णांक ina226_conv_समय_प्रकारab[] = अणु 140, 204, 332, 588, 1100,
					    2116, 4156, 8244 पूर्ण;

अटल पूर्णांक ina226_set_पूर्णांक_समय_vbus(काष्ठा ina2xx_chip_info *chip,
				    अचिन्हित पूर्णांक val_us, अचिन्हित पूर्णांक *config)
अणु
	पूर्णांक bits;

	अगर (val_us > 8244 || val_us < 140)
		वापस -EINVAL;

	bits = find_बंदst(val_us, ina226_conv_समय_प्रकारab,
			    ARRAY_SIZE(ina226_conv_समय_प्रकारab));

	chip->पूर्णांक_समय_vbus = ina226_conv_समय_प्रकारab[bits];

	*config &= ~INA226_ITB_MASK;
	*config |= INA226_SHIFT_ITB(bits) & INA226_ITB_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक ina226_set_पूर्णांक_समय_vshunt(काष्ठा ina2xx_chip_info *chip,
				      अचिन्हित पूर्णांक val_us, अचिन्हित पूर्णांक *config)
अणु
	पूर्णांक bits;

	अगर (val_us > 8244 || val_us < 140)
		वापस -EINVAL;

	bits = find_बंदst(val_us, ina226_conv_समय_प्रकारab,
			    ARRAY_SIZE(ina226_conv_समय_प्रकारab));

	chip->पूर्णांक_समय_vshunt = ina226_conv_समय_प्रकारab[bits];

	*config &= ~INA226_ITS_MASK;
	*config |= INA226_SHIFT_ITS(bits) & INA226_ITS_MASK;

	वापस 0;
पूर्ण

/* Conversion बार in uS. */
अटल स्थिर पूर्णांक ina219_conv_समय_प्रकारab_subsample[] = अणु 84, 148, 276, 532 पूर्ण;
अटल स्थिर पूर्णांक ina219_conv_समय_प्रकारab_average[] = अणु 532, 1060, 2130, 4260,
						    8510, 17020, 34050, 68100पूर्ण;

अटल पूर्णांक ina219_lookup_पूर्णांक_समय(अचिन्हित पूर्णांक *val_us, पूर्णांक *bits)
अणु
	अगर (*val_us > 68100 || *val_us < 84)
		वापस -EINVAL;

	अगर (*val_us <= 532) अणु
		*bits = find_बंदst(*val_us, ina219_conv_समय_प्रकारab_subsample,
				    ARRAY_SIZE(ina219_conv_समय_प्रकारab_subsample));
		*val_us = ina219_conv_समय_प्रकारab_subsample[*bits];
	पूर्ण अन्यथा अणु
		*bits = find_बंदst(*val_us, ina219_conv_समय_प्रकारab_average,
				    ARRAY_SIZE(ina219_conv_समय_प्रकारab_average));
		*val_us = ina219_conv_समय_प्रकारab_average[*bits];
		*bits |= 0x8;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ina219_set_पूर्णांक_समय_vbus(काष्ठा ina2xx_chip_info *chip,
				    अचिन्हित पूर्णांक val_us, अचिन्हित पूर्णांक *config)
अणु
	पूर्णांक bits, ret;
	अचिन्हित पूर्णांक val_us_best = val_us;

	ret = ina219_lookup_पूर्णांक_समय(&val_us_best, &bits);
	अगर (ret)
		वापस ret;

	chip->पूर्णांक_समय_vbus = val_us_best;

	*config &= ~INA219_ITB_MASK;
	*config |= INA219_SHIFT_ITB(bits) & INA219_ITB_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक ina219_set_पूर्णांक_समय_vshunt(काष्ठा ina2xx_chip_info *chip,
				      अचिन्हित पूर्णांक val_us, अचिन्हित पूर्णांक *config)
अणु
	पूर्णांक bits, ret;
	अचिन्हित पूर्णांक val_us_best = val_us;

	ret = ina219_lookup_पूर्णांक_समय(&val_us_best, &bits);
	अगर (ret)
		वापस ret;

	chip->पूर्णांक_समय_vshunt = val_us_best;

	*config &= ~INA219_ITS_MASK;
	*config |= INA219_SHIFT_ITS(bits) & INA219_ITS_MASK;

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक ina219_vbus_range_tab[] = अणु 1, 2 पूर्ण;
अटल पूर्णांक ina219_set_vbus_range_denom(काष्ठा ina2xx_chip_info *chip,
				       अचिन्हित पूर्णांक range,
				       अचिन्हित पूर्णांक *config)
अणु
	अगर (range == 1)
		chip->range_vbus = 32;
	अन्यथा अगर (range == 2)
		chip->range_vbus = 16;
	अन्यथा
		वापस -EINVAL;

	*config &= ~INA219_BRNG_MASK;
	*config |= INA219_SHIFT_BRNG(range == 1 ? 1 : 0) & INA219_BRNG_MASK;

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक ina219_vshunt_gain_tab[] = अणु 125, 250, 500, 1000 पूर्ण;
अटल स्थिर पूर्णांक ina219_vshunt_gain_frac[] = अणु
	125, 1000, 250, 1000, 500, 1000, 1000, 1000 पूर्ण;

अटल पूर्णांक ina219_set_vshunt_pga_gain(काष्ठा ina2xx_chip_info *chip,
				      अचिन्हित पूर्णांक gain,
				      अचिन्हित पूर्णांक *config)
अणु
	पूर्णांक bits;

	अगर (gain < 125 || gain > 1000)
		वापस -EINVAL;

	bits = find_बंदst(gain, ina219_vshunt_gain_tab,
			    ARRAY_SIZE(ina219_vshunt_gain_tab));

	chip->pga_gain_vshunt = ina219_vshunt_gain_tab[bits];
	bits = 3 - bits;

	*config &= ~INA219_PGA_MASK;
	*config |= INA219_SHIFT_PGA(bits) & INA219_PGA_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक ina2xx_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			     दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		चयन (chan->address) अणु
		हाल INA2XX_SHUNT_VOLTAGE:
			*type = IIO_VAL_FRACTIONAL;
			*length = माप(ina219_vshunt_gain_frac) / माप(पूर्णांक);
			*vals = ina219_vshunt_gain_frac;
			वापस IIO_AVAIL_LIST;

		हाल INA2XX_BUS_VOLTAGE:
			*type = IIO_VAL_INT;
			*length = माप(ina219_vbus_range_tab) / माप(पूर्णांक);
			*vals = ina219_vbus_range_tab;
			वापस IIO_AVAIL_LIST;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ina2xx_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ina2xx_chip_info *chip = iio_priv(indio_dev);
	अचिन्हित पूर्णांक config, पंचांगp;
	पूर्णांक ret;

	अगर (iio_buffer_enabled(indio_dev))
		वापस -EBUSY;

	mutex_lock(&chip->state_lock);

	ret = regmap_पढ़ो(chip->regmap, INA2XX_CONFIG, &config);
	अगर (ret)
		जाओ err;

	पंचांगp = config;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		ret = ina226_set_average(chip, val, &पंचांगp);
		अवरोध;

	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (chip->config->chip_id == ina226) अणु
			अगर (chan->address == INA2XX_SHUNT_VOLTAGE)
				ret = ina226_set_पूर्णांक_समय_vshunt(chip, val2,
								 &पंचांगp);
			अन्यथा
				ret = ina226_set_पूर्णांक_समय_vbus(chip, val2,
							       &पंचांगp);
		पूर्ण अन्यथा अणु
			अगर (chan->address == INA2XX_SHUNT_VOLTAGE)
				ret = ina219_set_पूर्णांक_समय_vshunt(chip, val2,
								 &पंचांगp);
			अन्यथा
				ret = ina219_set_पूर्णांक_समय_vbus(chip, val2,
							       &पंचांगp);
		पूर्ण
		अवरोध;

	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		अगर (chan->address == INA2XX_SHUNT_VOLTAGE)
			ret = ina219_set_vshunt_pga_gain(chip, val * 1000 +
							 val2 / 1000, &पंचांगp);
		अन्यथा
			ret = ina219_set_vbus_range_denom(chip, val, &पंचांगp);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (!ret && (पंचांगp != config))
		ret = regmap_ग_लिखो(chip->regmap, INA2XX_CONFIG, पंचांगp);
err:
	mutex_unlock(&chip->state_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ina2xx_allow_async_पढ़ोout_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा ina2xx_chip_info *chip = iio_priv(dev_to_iio_dev(dev));

	वापस प्र_लिखो(buf, "%d\n", chip->allow_async_पढ़ोout);
पूर्ण

अटल sमाप_प्रकार ina2xx_allow_async_पढ़ोout_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ina2xx_chip_info *chip = iio_priv(dev_to_iio_dev(dev));
	bool val;
	पूर्णांक ret;

	ret = strtobool((स्थिर अक्षर *) buf, &val);
	अगर (ret)
		वापस ret;

	chip->allow_async_पढ़ोout = val;

	वापस len;
पूर्ण

/*
 * Calibration रेजिस्टर is set to the best value, which eliminates
 * truncation errors on calculating current रेजिस्टर in hardware.
 * According to datasheet (INA 226: eq. 3, INA219: eq. 4) the best values
 * are 2048 क्रम ina226 and 4096 क्रम ina219. They are hardcoded as
 * calibration_value.
 */
अटल पूर्णांक ina2xx_set_calibration(काष्ठा ina2xx_chip_info *chip)
अणु
	वापस regmap_ग_लिखो(chip->regmap, INA2XX_CALIBRATION,
			    chip->config->calibration_value);
पूर्ण

अटल पूर्णांक set_shunt_resistor(काष्ठा ina2xx_chip_info *chip, अचिन्हित पूर्णांक val)
अणु
	अगर (val == 0 || val > पूर्णांक_उच्च)
		वापस -EINVAL;

	chip->shunt_resistor_uohm = val;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ina2xx_shunt_resistor_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा ina2xx_chip_info *chip = iio_priv(dev_to_iio_dev(dev));
	पूर्णांक vals[2] = अणु chip->shunt_resistor_uohm, 1000000 पूर्ण;

	वापस iio_क्रमmat_value(buf, IIO_VAL_FRACTIONAL, 1, vals);
पूर्ण

अटल sमाप_प्रकार ina2xx_shunt_resistor_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ina2xx_chip_info *chip = iio_priv(dev_to_iio_dev(dev));
	पूर्णांक val, val_fract, ret;

	ret = iio_str_to_fixpoपूर्णांक(buf, 100000, &val, &val_fract);
	अगर (ret)
		वापस ret;

	ret = set_shunt_resistor(chip, val * 1000000 + val_fract);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

#घोषणा INA219_CHAN(_type, _index, _address) अणु \
	.type = (_type), \
	.address = (_address), \
	.indexed = 1, \
	.channel = (_index), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			      BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_dir = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.scan_index = (_index), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 16, \
		.storagebits = 16, \
		.endianness = IIO_CPU, \
	पूर्ण \
पूर्ण

#घोषणा INA226_CHAN(_type, _index, _address) अणु \
	.type = (_type), \
	.address = (_address), \
	.indexed = 1, \
	.channel = (_index), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			      BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_dir = BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
				   BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO), \
	.scan_index = (_index), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 16, \
		.storagebits = 16, \
		.endianness = IIO_CPU, \
	पूर्ण \
पूर्ण

/*
 * Sampling Freq is a consequence of the पूर्णांकegration बार of
 * the Voltage channels.
 */
#घोषणा INA219_CHAN_VOLTAGE(_index, _address, _shअगरt) अणु \
	.type = IIO_VOLTAGE, \
	.address = (_address), \
	.indexed = 1, \
	.channel = (_index), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			      BIT(IIO_CHAN_INFO_SCALE) | \
			      BIT(IIO_CHAN_INFO_INT_TIME) | \
			      BIT(IIO_CHAN_INFO_HARDWAREGAIN), \
	.info_mask_separate_available = \
			      BIT(IIO_CHAN_INFO_HARDWAREGAIN), \
	.info_mask_shared_by_dir = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.scan_index = (_index), \
	.scan_type = अणु \
		.sign = 'u', \
		.shअगरt = _shअगरt, \
		.realbits = 16 - _shअगरt, \
		.storagebits = 16, \
		.endianness = IIO_LE, \
	पूर्ण \
पूर्ण

#घोषणा INA226_CHAN_VOLTAGE(_index, _address) अणु \
	.type = IIO_VOLTAGE, \
	.address = (_address), \
	.indexed = 1, \
	.channel = (_index), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			      BIT(IIO_CHAN_INFO_SCALE) | \
			      BIT(IIO_CHAN_INFO_INT_TIME), \
	.info_mask_shared_by_dir = BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
				   BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO), \
	.scan_index = (_index), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 16, \
		.storagebits = 16, \
		.endianness = IIO_LE, \
	पूर्ण \
पूर्ण


अटल स्थिर काष्ठा iio_chan_spec ina226_channels[] = अणु
	INA226_CHAN_VOLTAGE(0, INA2XX_SHUNT_VOLTAGE),
	INA226_CHAN_VOLTAGE(1, INA2XX_BUS_VOLTAGE),
	INA226_CHAN(IIO_POWER, 2, INA2XX_POWER),
	INA226_CHAN(IIO_CURRENT, 3, INA2XX_CURRENT),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ina219_channels[] = अणु
	INA219_CHAN_VOLTAGE(0, INA2XX_SHUNT_VOLTAGE, 0),
	INA219_CHAN_VOLTAGE(1, INA2XX_BUS_VOLTAGE, INA219_BUS_VOLTAGE_SHIFT),
	INA219_CHAN(IIO_POWER, 2, INA2XX_POWER),
	INA219_CHAN(IIO_CURRENT, 3, INA2XX_CURRENT),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल पूर्णांक ina2xx_conversion_पढ़ोy(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ina2xx_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक alert;

	/*
	 * Because the समयr thपढ़ो and the chip conversion घड़ी
	 * are asynchronous, the period dअगरference will eventually
	 * result in पढ़ोing V[k-1] again, or skip V[k] at समय Tk.
	 * In order to resync the समयr with the conversion process
	 * we check the ConVersionReadyFlag.
	 * On hardware that supports using the ALERT pin to toggle a
	 * GPIO a triggered buffer could be used instead.
	 * For now, we करो an extra पढ़ो of the MASK_ENABLE रेजिस्टर (INA226)
	 * resp. the BUS_VOLTAGE रेजिस्टर (INA219).
	 */
	अगर (chip->config->chip_id == ina226) अणु
		ret = regmap_पढ़ो(chip->regmap,
				  INA226_MASK_ENABLE, &alert);
		alert &= INA226_CVRF;
	पूर्ण अन्यथा अणु
		ret = regmap_पढ़ो(chip->regmap,
				  INA2XX_BUS_VOLTAGE, &alert);
		alert &= INA219_CNVR;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	वापस !!alert;
पूर्ण

अटल पूर्णांक ina2xx_work_buffer(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ina2xx_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक bit, ret, i = 0;
	s64 समय;

	समय = iio_get_समय_ns(indio_dev);

	/*
	 * Single रेजिस्टर पढ़ोs: bulk_पढ़ो will not work with ina226/219
	 * as there is no स्वतः-increment of the रेजिस्टर poपूर्णांकer.
	 */
	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		अचिन्हित पूर्णांक val;

		ret = regmap_पढ़ो(chip->regmap,
				  INA2XX_SHUNT_VOLTAGE + bit, &val);
		अगर (ret < 0)
			वापस ret;

		chip->scan.chan[i++] = val;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, &chip->scan, समय);

	वापस 0;
पूर्ण;

अटल पूर्णांक ina2xx_capture_thपढ़ो(व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा ina2xx_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक sampling_us = SAMPLING_PERIOD(chip);
	पूर्णांक ret;
	काष्ठा बारpec64 next, now, delta;
	s64 delay_us;

	/*
	 * Poll a bit faster than the chip पूर्णांकernal Fs, in हाल
	 * we wish to sync with the conversion पढ़ोy flag.
	 */
	अगर (!chip->allow_async_पढ़ोout)
		sampling_us -= 200;

	kसमय_get_ts64(&next);

	करो अणु
		जबतक (!chip->allow_async_पढ़ोout) अणु
			ret = ina2xx_conversion_पढ़ोy(indio_dev);
			अगर (ret < 0)
				वापस ret;

			/*
			 * If the conversion was not yet finished,
			 * reset the reference बारtamp.
			 */
			अगर (ret == 0)
				kसमय_get_ts64(&next);
			अन्यथा
				अवरोध;
		पूर्ण

		ret = ina2xx_work_buffer(indio_dev);
		अगर (ret < 0)
			वापस ret;

		kसमय_get_ts64(&now);

		/*
		 * Advance the बारtamp क्रम the next poll by one sampling
		 * पूर्णांकerval, and sleep क्रम the reमुख्यder (next - now)
		 * In हाल "next" has alपढ़ोy passed, the पूर्णांकerval is added
		 * multiple बार, i.e. samples are dropped.
		 */
		करो अणु
			बारpec64_add_ns(&next, 1000 * sampling_us);
			delta = बारpec64_sub(next, now);
			delay_us = भाग_s64(बारpec64_to_ns(&delta), 1000);
		पूर्ण जबतक (delay_us <= 0);

		usleep_range(delay_us, (delay_us * 3) >> 1);

	पूर्ण जबतक (!kthपढ़ो_should_stop());

	वापस 0;
पूर्ण

अटल पूर्णांक ina2xx_buffer_enable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ina2xx_chip_info *chip = iio_priv(indio_dev);
	अचिन्हित पूर्णांक sampling_us = SAMPLING_PERIOD(chip);
	काष्ठा task_काष्ठा *task;

	dev_dbg(&indio_dev->dev, "Enabling buffer w/ scan_mask %02x, freq = %d, avg =%u\n",
		(अचिन्हित पूर्णांक)(*indio_dev->active_scan_mask),
		1000000 / sampling_us, chip->avg);

	dev_dbg(&indio_dev->dev, "Expected work period: %u us\n", sampling_us);
	dev_dbg(&indio_dev->dev, "Async readout mode: %d\n",
		chip->allow_async_पढ़ोout);

	task = kthपढ़ो_create(ina2xx_capture_thपढ़ो, (व्योम *)indio_dev,
			      "%s:%d-%uus", indio_dev->name, indio_dev->id,
			      sampling_us);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);

	get_task_काष्ठा(task);
	wake_up_process(task);
	chip->task = task;

	वापस 0;
पूर्ण

अटल पूर्णांक ina2xx_buffer_disable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ina2xx_chip_info *chip = iio_priv(indio_dev);

	अगर (chip->task) अणु
		kthपढ़ो_stop(chip->task);
		put_task_काष्ठा(chip->task);
		chip->task = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops ina2xx_setup_ops = अणु
	.postenable = &ina2xx_buffer_enable,
	.predisable = &ina2xx_buffer_disable,
पूर्ण;

अटल पूर्णांक ina2xx_debug_reg(काष्ठा iio_dev *indio_dev,
			    अचिन्हित reg, अचिन्हित ग_लिखोval, अचिन्हित *पढ़ोval)
अणु
	काष्ठा ina2xx_chip_info *chip = iio_priv(indio_dev);

	अगर (!पढ़ोval)
		वापस regmap_ग_लिखो(chip->regmap, reg, ग_लिखोval);

	वापस regmap_पढ़ो(chip->regmap, reg, पढ़ोval);
पूर्ण

/* Possible पूर्णांकegration बार क्रम vshunt and vbus */
अटल IIO_CONST_ATTR_NAMED(ina219_पूर्णांकegration_समय_available,
			    पूर्णांकegration_समय_available,
			    "0.000084 0.000148 0.000276 0.000532 0.001060 0.002130 0.004260 0.008510 0.017020 0.034050 0.068100");

अटल IIO_CONST_ATTR_NAMED(ina226_पूर्णांकegration_समय_available,
			    पूर्णांकegration_समय_available,
			    "0.000140 0.000204 0.000332 0.000588 0.001100 0.002116 0.004156 0.008244");

अटल IIO_DEVICE_ATTR(in_allow_async_पढ़ोout, S_IRUGO | S_IWUSR,
		       ina2xx_allow_async_पढ़ोout_show,
		       ina2xx_allow_async_पढ़ोout_store, 0);

अटल IIO_DEVICE_ATTR(in_shunt_resistor, S_IRUGO | S_IWUSR,
		       ina2xx_shunt_resistor_show,
		       ina2xx_shunt_resistor_store, 0);

अटल काष्ठा attribute *ina219_attributes[] = अणु
	&iio_dev_attr_in_allow_async_पढ़ोout.dev_attr.attr,
	&iio_स्थिर_attr_ina219_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_dev_attr_in_shunt_resistor.dev_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *ina226_attributes[] = अणु
	&iio_dev_attr_in_allow_async_पढ़ोout.dev_attr.attr,
	&iio_स्थिर_attr_ina226_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_dev_attr_in_shunt_resistor.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ina219_attribute_group = अणु
	.attrs = ina219_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ina226_attribute_group = अणु
	.attrs = ina226_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info ina219_info = अणु
	.attrs = &ina219_attribute_group,
	.पढ़ो_raw = ina2xx_पढ़ो_raw,
	.पढ़ो_avail = ina2xx_पढ़ो_avail,
	.ग_लिखो_raw = ina2xx_ग_लिखो_raw,
	.debugfs_reg_access = ina2xx_debug_reg,
पूर्ण;

अटल स्थिर काष्ठा iio_info ina226_info = अणु
	.attrs = &ina226_attribute_group,
	.पढ़ो_raw = ina2xx_पढ़ो_raw,
	.ग_लिखो_raw = ina2xx_ग_लिखो_raw,
	.debugfs_reg_access = ina2xx_debug_reg,
पूर्ण;

/* Initialize the configuration and calibration रेजिस्टरs. */
अटल पूर्णांक ina2xx_init(काष्ठा ina2xx_chip_info *chip, अचिन्हित पूर्णांक config)
अणु
	पूर्णांक ret = regmap_ग_लिखो(chip->regmap, INA2XX_CONFIG, config);
	अगर (ret)
		वापस ret;

	वापस ina2xx_set_calibration(chip);
पूर्ण

अटल पूर्णांक ina2xx_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ina2xx_chip_info *chip;
	काष्ठा iio_dev *indio_dev;
	अचिन्हित पूर्णांक val;
	क्रमागत ina2xx_ids type;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*chip));
	अगर (!indio_dev)
		वापस -ENOMEM;

	chip = iio_priv(indio_dev);

	/* This is only used क्रम device removal purposes. */
	i2c_set_clientdata(client, indio_dev);

	chip->regmap = devm_regmap_init_i2c(client, &ina2xx_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		dev_err(&client->dev, "failed to allocate register map\n");
		वापस PTR_ERR(chip->regmap);
	पूर्ण

	अगर (client->dev.of_node)
		type = (क्रमागत ina2xx_ids)of_device_get_match_data(&client->dev);
	अन्यथा
		type = id->driver_data;
	chip->config = &ina2xx_config[type];

	mutex_init(&chip->state_lock);

	अगर (of_property_पढ़ो_u32(client->dev.of_node,
				 "shunt-resistor", &val) < 0) अणु
		काष्ठा ina2xx_platक्रमm_data *pdata =
		    dev_get_platdata(&client->dev);

		अगर (pdata)
			val = pdata->shunt_uohms;
		अन्यथा
			val = INA2XX_RSHUNT_DEFAULT;
	पूर्ण

	ret = set_shunt_resistor(chip, val);
	अगर (ret)
		वापस ret;

	/* Patch the current config रेजिस्टर with शेष. */
	val = chip->config->config_शेष;

	अगर (id->driver_data == ina226) अणु
		ina226_set_average(chip, INA226_DEFAULT_AVG, &val);
		ina226_set_पूर्णांक_समय_vbus(chip, INA226_DEFAULT_IT, &val);
		ina226_set_पूर्णांक_समय_vshunt(chip, INA226_DEFAULT_IT, &val);
	पूर्ण अन्यथा अणु
		chip->avg = 1;
		ina219_set_पूर्णांक_समय_vbus(chip, INA219_DEFAULT_IT, &val);
		ina219_set_पूर्णांक_समय_vshunt(chip, INA219_DEFAULT_IT, &val);
		ina219_set_vbus_range_denom(chip, INA219_DEFAULT_BRNG, &val);
		ina219_set_vshunt_pga_gain(chip, INA219_DEFAULT_PGA, &val);
	पूर्ण

	ret = ina2xx_init(chip, val);
	अगर (ret) अणु
		dev_err(&client->dev, "error configuring the device\n");
		वापस ret;
	पूर्ण

	indio_dev->modes = INDIO_सूचीECT_MODE;
	अगर (id->driver_data == ina226) अणु
		indio_dev->channels = ina226_channels;
		indio_dev->num_channels = ARRAY_SIZE(ina226_channels);
		indio_dev->info = &ina226_info;
	पूर्ण अन्यथा अणु
		indio_dev->channels = ina219_channels;
		indio_dev->num_channels = ARRAY_SIZE(ina219_channels);
		indio_dev->info = &ina219_info;
	पूर्ण
	indio_dev->name = id->name;

	ret = devm_iio_kfअगरo_buffer_setup(&client->dev, indio_dev,
					  INDIO_BUFFER_SOFTWARE,
					  &ina2xx_setup_ops);
	अगर (ret)
		वापस ret;

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक ina2xx_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ina2xx_chip_info *chip = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	/* Powerकरोwn */
	वापस regmap_update_bits(chip->regmap, INA2XX_CONFIG,
				  INA2XX_MODE_MASK, 0);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ina2xx_id[] = अणु
	अणु"ina219", ina219पूर्ण,
	अणु"ina220", ina219पूर्ण,
	अणु"ina226", ina226पूर्ण,
	अणु"ina230", ina226पूर्ण,
	अणु"ina231", ina226पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ina2xx_id);

अटल स्थिर काष्ठा of_device_id ina2xx_of_match[] = अणु
	अणु
		.compatible = "ti,ina219",
		.data = (व्योम *)ina219
	पूर्ण,
	अणु
		.compatible = "ti,ina220",
		.data = (व्योम *)ina219
	पूर्ण,
	अणु
		.compatible = "ti,ina226",
		.data = (व्योम *)ina226
	पूर्ण,
	अणु
		.compatible = "ti,ina230",
		.data = (व्योम *)ina226
	पूर्ण,
	अणु
		.compatible = "ti,ina231",
		.data = (व्योम *)ina226
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ina2xx_of_match);

अटल काष्ठा i2c_driver ina2xx_driver = अणु
	.driver = अणु
		   .name = KBUILD_MODNAME,
		   .of_match_table = ina2xx_of_match,
	पूर्ण,
	.probe = ina2xx_probe,
	.हटाओ = ina2xx_हटाओ,
	.id_table = ina2xx_id,
पूर्ण;
module_i2c_driver(ina2xx_driver);

MODULE_AUTHOR("Marc Titinger <marc.titinger@baylibre.com>");
MODULE_DESCRIPTION("Texas Instruments INA2XX ADC driver");
MODULE_LICENSE("GPL v2");
