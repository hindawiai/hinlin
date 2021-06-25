<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Marek Vasut <marex@denx.de>
 *
 * Driver क्रम Hope RF HP03 digital temperature and pressure sensor.
 */

#घोषणा pr_fmt(fmt) "hp03: " fmt

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

/*
 * The HP03 sensor occupies two fixed I2C addresses:
 *  0x50 ... पढ़ो-only EEPROM with calibration data
 *  0x77 ... पढ़ो-ग_लिखो ADC क्रम pressure and temperature
 */
#घोषणा HP03_EEPROM_ADDR		0x50
#घोषणा HP03_ADC_ADDR			0x77

#घोषणा HP03_EEPROM_CX_OFFSET		0x10
#घोषणा HP03_EEPROM_AB_OFFSET		0x1e
#घोषणा HP03_EEPROM_CD_OFFSET		0x20

#घोषणा HP03_ADC_WRITE_REG		0xff
#घोषणा HP03_ADC_READ_REG		0xfd
#घोषणा HP03_ADC_READ_PRESSURE		0xf0	/* D1 in datasheet */
#घोषणा HP03_ADC_READ_TEMP		0xe8	/* D2 in datasheet */

काष्ठा hp03_priv अणु
	काष्ठा i2c_client	*client;
	काष्ठा mutex		lock;
	काष्ठा gpio_desc	*xclr_gpio;

	काष्ठा i2c_client	*eeprom_client;
	काष्ठा regmap		*eeprom_regmap;

	s32			pressure;	/* kPa */
	s32			temp;		/* Deg. C */
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec hp03_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
पूर्ण;

अटल bool hp03_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस false;
पूर्ण

अटल bool hp03_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config hp03_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,

	.max_रेजिस्टर	= HP03_EEPROM_CD_OFFSET + 1,
	.cache_type	= REGCACHE_RBTREE,

	.ग_लिखोable_reg	= hp03_is_ग_लिखोable_reg,
	.अस्थिर_reg	= hp03_is_अस्थिर_reg,
पूर्ण;

अटल पूर्णांक hp03_get_temp_pressure(काष्ठा hp03_priv *priv, स्थिर u8 reg)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(priv->client, HP03_ADC_WRITE_REG, reg);
	अगर (ret < 0)
		वापस ret;

	msleep(50);	/* Wait क्रम conversion to finish */

	वापस i2c_smbus_पढ़ो_word_data(priv->client, HP03_ADC_READ_REG);
पूर्ण

अटल पूर्णांक hp03_update_temp_pressure(काष्ठा hp03_priv *priv)
अणु
	काष्ठा device *dev = &priv->client->dev;
	u8 coefs[18];
	u16 cx_val[7];
	पूर्णांक ab_val, d1_val, d2_val, dअगरf_val, dut, off, sens, x;
	पूर्णांक i, ret;

	/* Sample coefficients from EEPROM */
	ret = regmap_bulk_पढ़ो(priv->eeprom_regmap, HP03_EEPROM_CX_OFFSET,
			       coefs, माप(coefs));
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read EEPROM (reg=%02x)\n",
			HP03_EEPROM_CX_OFFSET);
		वापस ret;
	पूर्ण

	/* Sample Temperature and Pressure */
	gpiod_set_value_cansleep(priv->xclr_gpio, 1);

	ret = hp03_get_temp_pressure(priv, HP03_ADC_READ_PRESSURE);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read pressure\n");
		जाओ err_adc;
	पूर्ण
	d1_val = ret;

	ret = hp03_get_temp_pressure(priv, HP03_ADC_READ_TEMP);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read temperature\n");
		जाओ err_adc;
	पूर्ण
	d2_val = ret;

	gpiod_set_value_cansleep(priv->xclr_gpio, 0);

	/* The Cx coefficients and Temp/Pressure values are MSB first. */
	क्रम (i = 0; i < 7; i++)
		cx_val[i] = (coefs[2 * i] << 8) | (coefs[(2 * i) + 1] << 0);
	d1_val = ((d1_val >> 8) & 0xff) | ((d1_val & 0xff) << 8);
	d2_val = ((d2_val >> 8) & 0xff) | ((d2_val & 0xff) << 8);

	/* Coefficient vooकरोo from the HP03 datasheet. */
	अगर (d2_val >= cx_val[4])
		ab_val = coefs[14];	/* A-value */
	अन्यथा
		ab_val = coefs[15];	/* B-value */

	dअगरf_val = d2_val - cx_val[4];
	dut = (ab_val * (dअगरf_val >> 7) * (dअगरf_val >> 7)) >> coefs[16];
	dut = dअगरf_val - dut;

	off = (cx_val[1] + (((cx_val[3] - 1024) * dut) >> 14)) * 4;
	sens = cx_val[0] + ((cx_val[2] * dut) >> 10);
	x = ((sens * (d1_val - 7168)) >> 14) - off;

	priv->pressure = ((x * 100) >> 5) + (cx_val[6] * 10);
	priv->temp = 250 + ((dut * cx_val[5]) >> 16) - (dut >> coefs[17]);

	वापस 0;

err_adc:
	gpiod_set_value_cansleep(priv->xclr_gpio, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक hp03_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			 काष्ठा iio_chan_spec स्थिर *chan,
			 पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा hp03_priv *priv = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	ret = hp03_update_temp_pressure(priv);
	mutex_unlock(&priv->lock);

	अगर (ret)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_PRESSURE:
			*val = priv->pressure;
			वापस IIO_VAL_INT;
		हाल IIO_TEMP:
			*val = priv->temp;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_PRESSURE:
			*val = 0;
			*val2 = 1000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_TEMP:
			*val = 10;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info hp03_info = अणु
	.पढ़ो_raw	= &hp03_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक hp03_probe(काष्ठा i2c_client *client,
		      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा hp03_priv *priv;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*priv));
	अगर (!indio_dev)
		वापस -ENOMEM;

	priv = iio_priv(indio_dev);
	priv->client = client;
	mutex_init(&priv->lock);

	indio_dev->name = id->name;
	indio_dev->channels = hp03_channels;
	indio_dev->num_channels = ARRAY_SIZE(hp03_channels);
	indio_dev->info = &hp03_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	priv->xclr_gpio = devm_gpiod_get_index(dev, "xclr", 0, GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->xclr_gpio)) अणु
		dev_err(dev, "Failed to claim XCLR GPIO\n");
		ret = PTR_ERR(priv->xclr_gpio);
		वापस ret;
	पूर्ण

	/*
	 * Allocate another device क्रम the on-sensor EEPROM,
	 * which has it's dedicated I2C address and contains
	 * the calibration स्थिरants क्रम the sensor.
	 */
	priv->eeprom_client = i2c_new_dummy_device(client->adapter, HP03_EEPROM_ADDR);
	अगर (IS_ERR(priv->eeprom_client)) अणु
		dev_err(dev, "New EEPROM I2C device failed\n");
		वापस PTR_ERR(priv->eeprom_client);
	पूर्ण

	priv->eeprom_regmap = regmap_init_i2c(priv->eeprom_client,
					      &hp03_regmap_config);
	अगर (IS_ERR(priv->eeprom_regmap)) अणु
		dev_err(dev, "Failed to allocate EEPROM regmap\n");
		ret = PTR_ERR(priv->eeprom_regmap);
		जाओ err_cleanup_eeprom_client;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register IIO device\n");
		जाओ err_cleanup_eeprom_regmap;
	पूर्ण

	i2c_set_clientdata(client, indio_dev);

	वापस 0;

err_cleanup_eeprom_regmap:
	regmap_निकास(priv->eeprom_regmap);

err_cleanup_eeprom_client:
	i2c_unरेजिस्टर_device(priv->eeprom_client);
	वापस ret;
पूर्ण

अटल पूर्णांक hp03_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा hp03_priv *priv = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	regmap_निकास(priv->eeprom_regmap);
	i2c_unरेजिस्टर_device(priv->eeprom_client);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id hp03_id[] = अणु
	अणु "hp03", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, hp03_id);

अटल स्थिर काष्ठा of_device_id hp03_of_match[] = अणु
	अणु .compatible = "hoperf,hp03" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hp03_of_match);

अटल काष्ठा i2c_driver hp03_driver = अणु
	.driver = अणु
		.name	= "hp03",
		.of_match_table = hp03_of_match,
	पूर्ण,
	.probe		= hp03_probe,
	.हटाओ		= hp03_हटाओ,
	.id_table	= hp03_id,
पूर्ण;
module_i2c_driver(hp03_driver);

MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_DESCRIPTION("Driver for Hope RF HP03 pressure and temperature sensor");
MODULE_LICENSE("GPL v2");
