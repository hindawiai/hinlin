<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO driver क्रम the light sensor ISL29028.
 * ISL29028 is Concurrent Ambient Light and Proximity Sensor
 *
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 * Copyright (c) 2016-2017 Brian Masney <masneyb@onstation.org>
 *
 * Datasheets:
 *  - http://www.पूर्णांकersil.com/content/dam/Intersil/करोcuments/isl2/isl29028.pdf
 *  - http://www.पूर्णांकersil.com/content/dam/Intersil/करोcuments/isl2/isl29030.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा ISL29028_CONV_TIME_MS			100

#घोषणा ISL29028_REG_CONFIGURE			0x01

#घोषणा ISL29028_CONF_ALS_IR_MODE_ALS		0
#घोषणा ISL29028_CONF_ALS_IR_MODE_IR		BIT(0)
#घोषणा ISL29028_CONF_ALS_IR_MODE_MASK		BIT(0)

#घोषणा ISL29028_CONF_ALS_RANGE_LOW_LUX		0
#घोषणा ISL29028_CONF_ALS_RANGE_HIGH_LUX	BIT(1)
#घोषणा ISL29028_CONF_ALS_RANGE_MASK		BIT(1)

#घोषणा ISL29028_CONF_ALS_DIS			0
#घोषणा ISL29028_CONF_ALS_EN			BIT(2)
#घोषणा ISL29028_CONF_ALS_EN_MASK		BIT(2)

#घोषणा ISL29028_CONF_PROX_SLP_SH		4
#घोषणा ISL29028_CONF_PROX_SLP_MASK		(7 << ISL29028_CONF_PROX_SLP_SH)

#घोषणा ISL29028_CONF_PROX_EN			BIT(7)
#घोषणा ISL29028_CONF_PROX_EN_MASK		BIT(7)

#घोषणा ISL29028_REG_INTERRUPT			0x02

#घोषणा ISL29028_REG_PROX_DATA			0x08
#घोषणा ISL29028_REG_ALSIR_L			0x09
#घोषणा ISL29028_REG_ALSIR_U			0x0A

#घोषणा ISL29028_REG_TEST1_MODE			0x0E
#घोषणा ISL29028_REG_TEST2_MODE			0x0F

#घोषणा ISL29028_NUM_REGS			(ISL29028_REG_TEST2_MODE + 1)

#घोषणा ISL29028_POWER_OFF_DELAY_MS		2000

काष्ठा isl29028_prox_data अणु
	पूर्णांक sampling_पूर्णांक;
	पूर्णांक sampling_fract;
	पूर्णांक sleep_समय;
पूर्ण;

अटल स्थिर काष्ठा isl29028_prox_data isl29028_prox_data[] = अणु
	अणु   1, 250000, 800 पूर्ण,
	अणु   2, 500000, 400 पूर्ण,
	अणु   5,      0, 200 पूर्ण,
	अणु  10,      0, 100 पूर्ण,
	अणु  13, 300000,  75 पूर्ण,
	अणु  20,      0,  50 पूर्ण,
	अणु  80,      0,  13 पूर्ण, /*
			       * Note: Data sheet lists 12.5 ms sleep समय.
			       * Round up a half millisecond क्रम msleep().
			       */
	अणु 100,  0,   0 पूर्ण
पूर्ण;

क्रमागत isl29028_als_ir_mode अणु
	ISL29028_MODE_NONE = 0,
	ISL29028_MODE_ALS,
	ISL29028_MODE_IR,
पूर्ण;

काष्ठा isl29028_chip अणु
	काष्ठा mutex			lock;
	काष्ठा regmap			*regmap;
	पूर्णांक				prox_sampling_पूर्णांक;
	पूर्णांक				prox_sampling_frac;
	bool				enable_prox;
	पूर्णांक				lux_scale;
	क्रमागत isl29028_als_ir_mode	als_ir_mode;
पूर्ण;

अटल पूर्णांक isl29028_find_prox_sleep_index(पूर्णांक sampling_पूर्णांक, पूर्णांक sampling_fract)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(isl29028_prox_data); ++i) अणु
		अगर (isl29028_prox_data[i].sampling_पूर्णांक == sampling_पूर्णांक &&
		    isl29028_prox_data[i].sampling_fract == sampling_fract)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक isl29028_set_proxim_sampling(काष्ठा isl29028_chip *chip,
					पूर्णांक sampling_पूर्णांक, पूर्णांक sampling_fract)
अणु
	काष्ठा device *dev = regmap_get_device(chip->regmap);
	पूर्णांक sleep_index, ret;

	sleep_index = isl29028_find_prox_sleep_index(sampling_पूर्णांक,
						     sampling_fract);
	अगर (sleep_index < 0)
		वापस sleep_index;

	ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
				 ISL29028_CONF_PROX_SLP_MASK,
				 sleep_index << ISL29028_CONF_PROX_SLP_SH);

	अगर (ret < 0) अणु
		dev_err(dev, "%s(): Error %d setting the proximity sampling\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	chip->prox_sampling_पूर्णांक = sampling_पूर्णांक;
	chip->prox_sampling_frac = sampling_fract;

	वापस ret;
पूर्ण

अटल पूर्णांक isl29028_enable_proximity(काष्ठा isl29028_chip *chip)
अणु
	पूर्णांक prox_index, ret;

	ret = isl29028_set_proxim_sampling(chip, chip->prox_sampling_पूर्णांक,
					   chip->prox_sampling_frac);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
				 ISL29028_CONF_PROX_EN_MASK,
				 ISL29028_CONF_PROX_EN);
	अगर (ret < 0)
		वापस ret;

	/* Wait क्रम conversion to be complete क्रम first sample */
	prox_index = isl29028_find_prox_sleep_index(chip->prox_sampling_पूर्णांक,
						    chip->prox_sampling_frac);
	अगर (prox_index < 0)
		वापस prox_index;

	msleep(isl29028_prox_data[prox_index].sleep_समय);

	वापस 0;
पूर्ण

अटल पूर्णांक isl29028_set_als_scale(काष्ठा isl29028_chip *chip, पूर्णांक lux_scale)
अणु
	काष्ठा device *dev = regmap_get_device(chip->regmap);
	पूर्णांक val = (lux_scale == 2000) ? ISL29028_CONF_ALS_RANGE_HIGH_LUX :
					ISL29028_CONF_ALS_RANGE_LOW_LUX;
	पूर्णांक ret;

	ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
				 ISL29028_CONF_ALS_RANGE_MASK, val);
	अगर (ret < 0) अणु
		dev_err(dev, "%s(): Error %d setting the ALS scale\n", __func__,
			ret);
		वापस ret;
	पूर्ण

	chip->lux_scale = lux_scale;

	वापस ret;
पूर्ण

अटल पूर्णांक isl29028_set_als_ir_mode(काष्ठा isl29028_chip *chip,
				    क्रमागत isl29028_als_ir_mode mode)
अणु
	पूर्णांक ret;

	अगर (chip->als_ir_mode == mode)
		वापस 0;

	ret = isl29028_set_als_scale(chip, chip->lux_scale);
	अगर (ret < 0)
		वापस ret;

	चयन (mode) अणु
	हाल ISL29028_MODE_ALS:
		ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
					 ISL29028_CONF_ALS_IR_MODE_MASK,
					 ISL29028_CONF_ALS_IR_MODE_ALS);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
					 ISL29028_CONF_ALS_RANGE_MASK,
					 ISL29028_CONF_ALS_RANGE_HIGH_LUX);
		अवरोध;
	हाल ISL29028_MODE_IR:
		ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
					 ISL29028_CONF_ALS_IR_MODE_MASK,
					 ISL29028_CONF_ALS_IR_MODE_IR);
		अवरोध;
	हाल ISL29028_MODE_NONE:
		वापस regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
					  ISL29028_CONF_ALS_EN_MASK,
					  ISL29028_CONF_ALS_DIS);
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	/* Enable the ALS/IR */
	ret = regmap_update_bits(chip->regmap, ISL29028_REG_CONFIGURE,
				 ISL29028_CONF_ALS_EN_MASK,
				 ISL29028_CONF_ALS_EN);
	अगर (ret < 0)
		वापस ret;

	/* Need to रुको क्रम conversion समय अगर ALS/IR mode enabled */
	msleep(ISL29028_CONV_TIME_MS);

	chip->als_ir_mode = mode;

	वापस 0;
पूर्ण

अटल पूर्णांक isl29028_पढ़ो_als_ir(काष्ठा isl29028_chip *chip, पूर्णांक *als_ir)
अणु
	काष्ठा device *dev = regmap_get_device(chip->regmap);
	अचिन्हित पूर्णांक lsb;
	अचिन्हित पूर्णांक msb;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chip->regmap, ISL29028_REG_ALSIR_L, &lsb);
	अगर (ret < 0) अणु
		dev_err(dev,
			"%s(): Error %d reading register ALSIR_L\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(chip->regmap, ISL29028_REG_ALSIR_U, &msb);
	अगर (ret < 0) अणु
		dev_err(dev,
			"%s(): Error %d reading register ALSIR_U\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	*als_ir = ((msb & 0xF) << 8) | (lsb & 0xFF);

	वापस 0;
पूर्ण

अटल पूर्णांक isl29028_पढ़ो_proxim(काष्ठा isl29028_chip *chip, पूर्णांक *prox)
अणु
	काष्ठा device *dev = regmap_get_device(chip->regmap);
	अचिन्हित पूर्णांक data;
	पूर्णांक ret;

	अगर (!chip->enable_prox) अणु
		ret = isl29028_enable_proximity(chip);
		अगर (ret < 0)
			वापस ret;

		chip->enable_prox = true;
	पूर्ण

	ret = regmap_पढ़ो(chip->regmap, ISL29028_REG_PROX_DATA, &data);
	अगर (ret < 0) अणु
		dev_err(dev, "%s(): Error %d reading register PROX_DATA\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	*prox = data;

	वापस 0;
पूर्ण

अटल पूर्णांक isl29028_als_get(काष्ठा isl29028_chip *chip, पूर्णांक *als_data)
अणु
	काष्ठा device *dev = regmap_get_device(chip->regmap);
	पूर्णांक ret;
	पूर्णांक als_ir_data;

	ret = isl29028_set_als_ir_mode(chip, ISL29028_MODE_ALS);
	अगर (ret < 0) अणु
		dev_err(dev, "%s(): Error %d enabling ALS mode\n", __func__,
			ret);
		वापस ret;
	पूर्ण

	ret = isl29028_पढ़ो_als_ir(chip, &als_ir_data);
	अगर (ret < 0)
		वापस ret;

	/*
	 * convert als data count to lux.
	 * अगर lux_scale = 125,  lux = count * 0.031
	 * अगर lux_scale = 2000, lux = count * 0.49
	 */
	अगर (chip->lux_scale == 125)
		als_ir_data = (als_ir_data * 31) / 1000;
	अन्यथा
		als_ir_data = (als_ir_data * 49) / 100;

	*als_data = als_ir_data;

	वापस 0;
पूर्ण

अटल पूर्णांक isl29028_ir_get(काष्ठा isl29028_chip *chip, पूर्णांक *ir_data)
अणु
	काष्ठा device *dev = regmap_get_device(chip->regmap);
	पूर्णांक ret;

	ret = isl29028_set_als_ir_mode(chip, ISL29028_MODE_IR);
	अगर (ret < 0) अणु
		dev_err(dev, "%s(): Error %d enabling IR mode\n", __func__,
			ret);
		वापस ret;
	पूर्ण

	वापस isl29028_पढ़ो_als_ir(chip, ir_data);
पूर्ण

अटल पूर्णांक isl29028_set_pm_runसमय_busy(काष्ठा isl29028_chip *chip, bool on)
अणु
	काष्ठा device *dev = regmap_get_device(chip->regmap);
	पूर्णांक ret;

	अगर (on) अणु
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0)
			pm_runसमय_put_noidle(dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(dev);
		ret = pm_runसमय_put_स्वतःsuspend(dev);
	पूर्ण

	वापस ret;
पूर्ण

/* Channel IO */
अटल पूर्णांक isl29028_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा isl29028_chip *chip = iio_priv(indio_dev);
	काष्ठा device *dev = regmap_get_device(chip->regmap);
	पूर्णांक ret;

	ret = isl29028_set_pm_runसमय_busy(chip, true);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&chip->lock);

	ret = -EINVAL;
	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		अगर (mask != IIO_CHAN_INFO_SAMP_FREQ) अणु
			dev_err(dev,
				"%s(): proximity: Mask value 0x%08lx is not supported\n",
				__func__, mask);
			अवरोध;
		पूर्ण

		अगर (val < 1 || val > 100) अणु
			dev_err(dev,
				"%s(): proximity: Sampling frequency %d is not in the range [1:100]\n",
				__func__, val);
			अवरोध;
		पूर्ण

		ret = isl29028_set_proxim_sampling(chip, val, val2);
		अवरोध;
	हाल IIO_LIGHT:
		अगर (mask != IIO_CHAN_INFO_SCALE) अणु
			dev_err(dev,
				"%s(): light: Mask value 0x%08lx is not supported\n",
				__func__, mask);
			अवरोध;
		पूर्ण

		अगर (val != 125 && val != 2000) अणु
			dev_err(dev,
				"%s(): light: Lux scale %d is not in the set {125, 2000}\n",
				__func__, val);
			अवरोध;
		पूर्ण

		ret = isl29028_set_als_scale(chip, val);
		अवरोध;
	शेष:
		dev_err(dev, "%s(): Unsupported channel type %x\n",
			__func__, chan->type);
		अवरोध;
	पूर्ण

	mutex_unlock(&chip->lock);

	अगर (ret < 0)
		वापस ret;

	ret = isl29028_set_pm_runसमय_busy(chip, false);
	अगर (ret < 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक isl29028_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा isl29028_chip *chip = iio_priv(indio_dev);
	काष्ठा device *dev = regmap_get_device(chip->regmap);
	पूर्णांक ret, pm_ret;

	ret = isl29028_set_pm_runसमय_busy(chip, true);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&chip->lock);

	ret = -EINVAL;
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = isl29028_als_get(chip, val);
			अवरोध;
		हाल IIO_INTENSITY:
			ret = isl29028_ir_get(chip, val);
			अवरोध;
		हाल IIO_PROXIMITY:
			ret = isl29028_पढ़ो_proxim(chip, val);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (ret < 0)
			अवरोध;

		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (chan->type != IIO_PROXIMITY)
			अवरोध;

		*val = chip->prox_sampling_पूर्णांक;
		*val2 = chip->prox_sampling_frac;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type != IIO_LIGHT)
			अवरोध;
		*val = chip->lux_scale;
		ret = IIO_VAL_INT;
		अवरोध;
	शेष:
		dev_err(dev, "%s(): mask value 0x%08lx is not supported\n",
			__func__, mask);
		अवरोध;
	पूर्ण

	mutex_unlock(&chip->lock);

	अगर (ret < 0)
		वापस ret;

	/**
	 * Preserve the ret variable अगर the call to
	 * isl29028_set_pm_runसमय_busy() is successful so the पढ़ोing
	 * (अगर applicable) is वापसed to user space.
	 */
	pm_ret = isl29028_set_pm_runसमय_busy(chip, false);
	अगर (pm_ret < 0)
		वापस pm_ret;

	वापस ret;
पूर्ण

अटल IIO_CONST_ATTR(in_proximity_sampling_frequency_available,
				"1.25 2.5 5 10 13.3 20 80 100");
अटल IIO_CONST_ATTR(in_illuminance_scale_available, "125 2000");

#घोषणा ISL29028_CONST_ATTR(name) (&iio_स्थिर_attr_##name.dev_attr.attr)
अटल काष्ठा attribute *isl29028_attributes[] = अणु
	ISL29028_CONST_ATTR(in_proximity_sampling_frequency_available),
	ISL29028_CONST_ATTR(in_illuminance_scale_available),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group isl29108_group = अणु
	.attrs = isl29028_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec isl29028_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
		BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण, अणु
		.type = IIO_INTENSITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण, अणु
		.type = IIO_PROXIMITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_info isl29028_info = अणु
	.attrs = &isl29108_group,
	.पढ़ो_raw = isl29028_पढ़ो_raw,
	.ग_लिखो_raw = isl29028_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक isl29028_clear_configure_reg(काष्ठा isl29028_chip *chip)
अणु
	काष्ठा device *dev = regmap_get_device(chip->regmap);
	पूर्णांक ret;

	ret = regmap_ग_लिखो(chip->regmap, ISL29028_REG_CONFIGURE, 0x0);
	अगर (ret < 0)
		dev_err(dev, "%s(): Error %d clearing the CONFIGURE register\n",
			__func__, ret);

	chip->als_ir_mode = ISL29028_MODE_NONE;
	chip->enable_prox = false;

	वापस ret;
पूर्ण

अटल bool isl29028_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ISL29028_REG_INTERRUPT:
	हाल ISL29028_REG_PROX_DATA:
	हाल ISL29028_REG_ALSIR_L:
	हाल ISL29028_REG_ALSIR_U:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config isl29028_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_reg = isl29028_is_अस्थिर_reg,
	.max_रेजिस्टर = ISL29028_NUM_REGS - 1,
	.num_reg_शेषs_raw = ISL29028_NUM_REGS,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक isl29028_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा isl29028_chip *chip;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*chip));
	अगर (!indio_dev)
		वापस -ENOMEM;

	chip = iio_priv(indio_dev);

	i2c_set_clientdata(client, indio_dev);
	mutex_init(&chip->lock);

	chip->regmap = devm_regmap_init_i2c(client, &isl29028_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		ret = PTR_ERR(chip->regmap);
		dev_err(&client->dev, "%s: Error %d initializing regmap\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	chip->enable_prox  = false;
	chip->prox_sampling_पूर्णांक = 20;
	chip->prox_sampling_frac = 0;
	chip->lux_scale = 2000;

	ret = regmap_ग_लिखो(chip->regmap, ISL29028_REG_TEST1_MODE, 0x0);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"%s(): Error %d writing to TEST1_MODE register\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(chip->regmap, ISL29028_REG_TEST2_MODE, 0x0);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"%s(): Error %d writing to TEST2_MODE register\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ret = isl29028_clear_configure_reg(chip);
	अगर (ret < 0)
		वापस ret;

	indio_dev->info = &isl29028_info;
	indio_dev->channels = isl29028_channels;
	indio_dev->num_channels = ARRAY_SIZE(isl29028_channels);
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev,
					 ISL29028_POWER_OFF_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	ret = devm_iio_device_रेजिस्टर(indio_dev->dev.parent, indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"%s(): iio registration failed with error %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक isl29028_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा isl29028_chip *chip = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	वापस isl29028_clear_configure_reg(chip);
पूर्ण

अटल पूर्णांक __maybe_unused isl29028_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा isl29028_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&chip->lock);

	ret = isl29028_clear_configure_reg(chip);

	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused isl29028_resume(काष्ठा device *dev)
अणु
	/**
	 * The specअगरic component (ALS/IR or proximity) will enable itself as
	 * needed the next समय that the user requests a पढ़ोing. This is करोne
	 * above in isl29028_set_als_ir_mode() and isl29028_enable_proximity().
	 */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops isl29028_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(isl29028_suspend, isl29028_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id isl29028_id[] = अणु
	अणु"isl29028", 0पूर्ण,
	अणु"isl29030", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, isl29028_id);

अटल स्थिर काष्ठा of_device_id isl29028_of_match[] = अणु
	अणु .compatible = "isl,isl29028", पूर्ण, /* क्रम backward compat., करोn't use */
	अणु .compatible = "isil,isl29028", पूर्ण,
	अणु .compatible = "isil,isl29030", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, isl29028_of_match);

अटल काष्ठा i2c_driver isl29028_driver = अणु
	.driver  = अणु
		.name = "isl29028",
		.pm = &isl29028_pm_ops,
		.of_match_table = isl29028_of_match,
	पूर्ण,
	.probe	 = isl29028_probe,
	.हटाओ  = isl29028_हटाओ,
	.id_table = isl29028_id,
पूर्ण;

module_i2c_driver(isl29028_driver);

MODULE_DESCRIPTION("ISL29028 Ambient Light and Proximity Sensor driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
