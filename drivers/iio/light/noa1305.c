<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Support क्रम ON Semiconductor NOA1305 ambient light sensor
 *
 * Copyright (C) 2016 Emcraft Systems
 * Copyright (C) 2019 Collabora Ltd.
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा NOA1305_REG_POWER_CONTROL	0x0
#घोषणा   NOA1305_POWER_CONTROL_DOWN	0x00
#घोषणा   NOA1305_POWER_CONTROL_ON	0x08
#घोषणा NOA1305_REG_RESET		0x1
#घोषणा   NOA1305_RESET_RESET		0x10
#घोषणा NOA1305_REG_INTEGRATION_TIME	0x2
#घोषणा   NOA1305_INTEGR_TIME_800MS	0x00
#घोषणा   NOA1305_INTEGR_TIME_400MS	0x01
#घोषणा   NOA1305_INTEGR_TIME_200MS	0x02
#घोषणा   NOA1305_INTEGR_TIME_100MS	0x03
#घोषणा   NOA1305_INTEGR_TIME_50MS	0x04
#घोषणा   NOA1305_INTEGR_TIME_25MS	0x05
#घोषणा   NOA1305_INTEGR_TIME_12_5MS	0x06
#घोषणा   NOA1305_INTEGR_TIME_6_25MS	0x07
#घोषणा NOA1305_REG_INT_SELECT		0x3
#घोषणा   NOA1305_INT_SEL_ACTIVE_HIGH	0x01
#घोषणा   NOA1305_INT_SEL_ACTIVE_LOW	0x02
#घोषणा   NOA1305_INT_SEL_INACTIVE	0x03
#घोषणा NOA1305_REG_INT_THRESH_LSB	0x4
#घोषणा NOA1305_REG_INT_THRESH_MSB	0x5
#घोषणा NOA1305_REG_ALS_DATA_LSB	0x6
#घोषणा NOA1305_REG_ALS_DATA_MSB	0x7
#घोषणा NOA1305_REG_DEVICE_ID_LSB	0x8
#घोषणा NOA1305_REG_DEVICE_ID_MSB	0x9

#घोषणा NOA1305_DEVICE_ID	0x0519
#घोषणा NOA1305_DRIVER_NAME	"noa1305"

काष्ठा noa1305_priv अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा regulator *vin_reg;
पूर्ण;

अटल पूर्णांक noa1305_measure(काष्ठा noa1305_priv *priv)
अणु
	__le16 data;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(priv->regmap, NOA1305_REG_ALS_DATA_LSB, &data,
			       2);
	अगर (ret < 0)
		वापस ret;

	वापस le16_to_cpu(data);
पूर्ण

अटल पूर्णांक noa1305_scale(काष्ठा noa1305_priv *priv, पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक data;
	पूर्णांक ret;

	ret = regmap_पढ़ो(priv->regmap, NOA1305_REG_INTEGRATION_TIME, &data);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Lux = count / (<Integration Constant> * <Integration Time>)
	 *
	 * Integration Constant = 7.7
	 * Integration Time in Seconds
	 */
	चयन (data) अणु
	हाल NOA1305_INTEGR_TIME_800MS:
		*val = 100;
		*val2 = 77 * 8;
		अवरोध;
	हाल NOA1305_INTEGR_TIME_400MS:
		*val = 100;
		*val2 = 77 * 4;
		अवरोध;
	हाल NOA1305_INTEGR_TIME_200MS:
		*val = 100;
		*val2 = 77 * 2;
		अवरोध;
	हाल NOA1305_INTEGR_TIME_100MS:
		*val = 100;
		*val2 = 77;
		अवरोध;
	हाल NOA1305_INTEGR_TIME_50MS:
		*val = 1000;
		*val2 = 77 * 5;
		अवरोध;
	हाल NOA1305_INTEGR_TIME_25MS:
		*val = 10000;
		*val2 = 77 * 25;
		अवरोध;
	हाल NOA1305_INTEGR_TIME_12_5MS:
		*val = 100000;
		*val2 = 77 * 125;
		अवरोध;
	हाल NOA1305_INTEGR_TIME_6_25MS:
		*val = 1000000;
		*val2 = 77 * 625;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_FRACTIONAL;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec noa1305_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण
पूर्ण;

अटल पूर्णांक noa1305_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा noa1305_priv *priv = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = noa1305_measure(priv);
			अगर (ret < 0)
				वापस ret;
			*val = ret;
			वापस IIO_VAL_INT;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			वापस noa1305_scale(priv, val, val2);
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info noa1305_info = अणु
	.पढ़ो_raw = noa1305_पढ़ो_raw,
पूर्ण;

अटल bool noa1305_writable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल NOA1305_REG_POWER_CONTROL:
	हाल NOA1305_REG_RESET:
	हाल NOA1305_REG_INTEGRATION_TIME:
	हाल NOA1305_REG_INT_SELECT:
	हाल NOA1305_REG_INT_THRESH_LSB:
	हाल NOA1305_REG_INT_THRESH_MSB:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config noa1305_regmap_config = अणु
	.name = NOA1305_DRIVER_NAME,
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = NOA1305_REG_DEVICE_ID_MSB,
	.ग_लिखोable_reg = noa1305_writable_reg,
पूर्ण;

अटल व्योम noa1305_reg_हटाओ(व्योम *data)
अणु
	काष्ठा noa1305_priv *priv = data;

	regulator_disable(priv->vin_reg);
पूर्ण

अटल पूर्णांक noa1305_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा noa1305_priv *priv;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap *regmap;
	__le16 data;
	अचिन्हित पूर्णांक dev_id;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*priv));
	अगर (!indio_dev)
		वापस -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &noa1305_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Regmap initialization failed.\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	priv = iio_priv(indio_dev);

	priv->vin_reg = devm_regulator_get(&client->dev, "vin");
	अगर (IS_ERR(priv->vin_reg)) अणु
		dev_err(&client->dev, "get regulator vin failed\n");
		वापस PTR_ERR(priv->vin_reg);
	पूर्ण

	ret = regulator_enable(priv->vin_reg);
	अगर (ret) अणु
		dev_err(&client->dev, "enable regulator vin failed\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&client->dev, noa1305_reg_हटाओ, priv);
	अगर (ret) अणु
		dev_err(&client->dev, "addition of devm action failed\n");
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, indio_dev);
	priv->client = client;
	priv->regmap = regmap;

	ret = regmap_bulk_पढ़ो(regmap, NOA1305_REG_DEVICE_ID_LSB, &data, 2);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "ID reading failed: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_id = le16_to_cpu(data);
	अगर (dev_id != NOA1305_DEVICE_ID) अणु
		dev_err(&client->dev, "Unknown device ID: 0x%x\n", dev_id);
		वापस -ENODEV;
	पूर्ण

	ret = regmap_ग_लिखो(regmap, NOA1305_REG_POWER_CONTROL,
			   NOA1305_POWER_CONTROL_ON);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Enabling power control failed\n");
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(regmap, NOA1305_REG_RESET, NOA1305_RESET_RESET);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Device reset failed\n");
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(regmap, NOA1305_REG_INTEGRATION_TIME,
			   NOA1305_INTEGR_TIME_800MS);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Setting integration time failed\n");
		वापस ret;
	पूर्ण

	indio_dev->info = &noa1305_info;
	indio_dev->channels = noa1305_channels;
	indio_dev->num_channels = ARRAY_SIZE(noa1305_channels);
	indio_dev->name = NOA1305_DRIVER_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
	अगर (ret)
		dev_err(&client->dev, "registering device failed\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id noa1305_of_match[] = अणु
	अणु .compatible = "onnn,noa1305" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, noa1305_of_match);

अटल स्थिर काष्ठा i2c_device_id noa1305_ids[] = अणु
	अणु "noa1305", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, noa1305_ids);

अटल काष्ठा i2c_driver noa1305_driver = अणु
	.driver = अणु
		.name		= NOA1305_DRIVER_NAME,
		.of_match_table	= noa1305_of_match,
	पूर्ण,
	.probe		= noa1305_probe,
	.id_table	= noa1305_ids,
पूर्ण;

module_i2c_driver(noa1305_driver);

MODULE_AUTHOR("Sergei Miroshnichenko <sergeimir@emcraft.com>");
MODULE_AUTHOR("Martyn Welch <martyn.welch@collabora.com");
MODULE_DESCRIPTION("ON Semiconductor NOA1305 ambient light sensor");
MODULE_LICENSE("GPL");
