<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ROHM 1780GLI Ambient Light Sensor Driver
 *
 * Copyright (C) 2016 Linaro Ltd.
 * Author: Linus Walleij <linus.walleij@linaro.org>
 * Loosely based on the previous BH1780 ALS misc driver
 * Copyright (C) 2010 Texas Instruments
 * Author: Hemanth V <hemanthv@ti.com>
 */
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/bitops.h>

#घोषणा BH1780_CMD_BIT		BIT(7)
#घोषणा BH1780_REG_CONTROL	0x00
#घोषणा BH1780_REG_PARTID	0x0A
#घोषणा BH1780_REG_MANFID	0x0B
#घोषणा BH1780_REG_DLOW		0x0C
#घोषणा BH1780_REG_DHIGH	0x0D

#घोषणा BH1780_REVMASK		GENMASK(3,0)
#घोषणा BH1780_POWMASK		GENMASK(1,0)
#घोषणा BH1780_POFF		(0x0)
#घोषणा BH1780_PON		(0x3)

/* घातer on settling समय in ms */
#घोषणा BH1780_PON_DELAY	2
/* max समय beक्रमe value available in ms */
#घोषणा BH1780_INTERVAL		250

काष्ठा bh1780_data अणु
	काष्ठा i2c_client *client;
पूर्ण;

अटल पूर्णांक bh1780_ग_लिखो(काष्ठा bh1780_data *bh1780, u8 reg, u8 val)
अणु
	पूर्णांक ret = i2c_smbus_ग_लिखो_byte_data(bh1780->client,
					    BH1780_CMD_BIT | reg,
					    val);
	अगर (ret < 0)
		dev_err(&bh1780->client->dev,
			"i2c_smbus_write_byte_data failed error "
			"%d, register %01x\n",
			ret, reg);
	वापस ret;
पूर्ण

अटल पूर्णांक bh1780_पढ़ो(काष्ठा bh1780_data *bh1780, u8 reg)
अणु
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(bh1780->client,
					   BH1780_CMD_BIT | reg);
	अगर (ret < 0)
		dev_err(&bh1780->client->dev,
			"i2c_smbus_read_byte_data failed error "
			"%d, register %01x\n",
			ret, reg);
	वापस ret;
पूर्ण

अटल पूर्णांक bh1780_पढ़ो_word(काष्ठा bh1780_data *bh1780, u8 reg)
अणु
	पूर्णांक ret = i2c_smbus_पढ़ो_word_data(bh1780->client,
					   BH1780_CMD_BIT | reg);
	अगर (ret < 0)
		dev_err(&bh1780->client->dev,
			"i2c_smbus_read_word_data failed error "
			"%d, register %01x\n",
			ret, reg);
	वापस ret;
पूर्ण

अटल पूर्णांक bh1780_debugfs_reg_access(काष्ठा iio_dev *indio_dev,
			      अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक ग_लिखोval,
			      अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा bh1780_data *bh1780 = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (!पढ़ोval)
		वापस bh1780_ग_लिखो(bh1780, (u8)reg, (u8)ग_लिखोval);

	ret = bh1780_पढ़ो(bh1780, (u8)reg);
	अगर (ret < 0)
		वापस ret;

	*पढ़ोval = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक bh1780_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा bh1780_data *bh1780 = iio_priv(indio_dev);
	पूर्णांक value;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			pm_runसमय_get_sync(&bh1780->client->dev);
			value = bh1780_पढ़ो_word(bh1780, BH1780_REG_DLOW);
			अगर (value < 0)
				वापस value;
			pm_runसमय_mark_last_busy(&bh1780->client->dev);
			pm_runसमय_put_स्वतःsuspend(&bh1780->client->dev);
			*val = value;

			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = BH1780_INTERVAL * 1000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info bh1780_info = अणु
	.पढ़ो_raw = bh1780_पढ़ो_raw,
	.debugfs_reg_access = bh1780_debugfs_reg_access,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec bh1780_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_INT_TIME)
	पूर्ण
पूर्ण;

अटल पूर्णांक bh1780_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा bh1780_data *bh1780;
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा iio_dev *indio_dev;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))
		वापस -EIO;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*bh1780));
	अगर (!indio_dev)
		वापस -ENOMEM;

	bh1780 = iio_priv(indio_dev);
	bh1780->client = client;
	i2c_set_clientdata(client, indio_dev);

	/* Power up the device */
	ret = bh1780_ग_लिखो(bh1780, BH1780_REG_CONTROL, BH1780_PON);
	अगर (ret < 0)
		वापस ret;
	msleep(BH1780_PON_DELAY);
	pm_runसमय_get_noresume(&client->dev);
	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);

	ret = bh1780_पढ़ो(bh1780, BH1780_REG_PARTID);
	अगर (ret < 0)
		जाओ out_disable_pm;
	dev_info(&client->dev,
		 "Ambient Light Sensor, Rev : %lu\n",
		 (ret & BH1780_REVMASK));

	/*
	 * As the device takes 250 ms to even come up with a fresh
	 * measurement after घातer-on, करो not shut it करोwn unnecessarily.
	 * Set स्वतःsuspend to a five seconds.
	 */
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, 5000);
	pm_runसमय_use_स्वतःsuspend(&client->dev);
	pm_runसमय_put(&client->dev);

	indio_dev->info = &bh1780_info;
	indio_dev->name = "bh1780";
	indio_dev->channels = bh1780_channels;
	indio_dev->num_channels = ARRAY_SIZE(bh1780_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ out_disable_pm;
	वापस 0;

out_disable_pm:
	pm_runसमय_put_noidle(&client->dev);
	pm_runसमय_disable(&client->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक bh1780_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा bh1780_data *bh1780 = iio_priv(indio_dev);
	पूर्णांक ret;

	iio_device_unरेजिस्टर(indio_dev);
	pm_runसमय_get_sync(&client->dev);
	pm_runसमय_put_noidle(&client->dev);
	pm_runसमय_disable(&client->dev);
	ret = bh1780_ग_लिखो(bh1780, BH1780_REG_CONTROL, BH1780_POFF);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to power off\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bh1780_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा bh1780_data *bh1780 = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = bh1780_ग_लिखो(bh1780, BH1780_REG_CONTROL, BH1780_POFF);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to runtime suspend\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bh1780_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा bh1780_data *bh1780 = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = bh1780_ग_लिखो(bh1780, BH1780_REG_CONTROL, BH1780_PON);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to runtime resume\n");
		वापस ret;
	पूर्ण

	/* Wait क्रम घातer on, then क्रम a value to be available */
	msleep(BH1780_PON_DELAY + BH1780_INTERVAL);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops bh1780_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(bh1780_runसमय_suspend,
			   bh1780_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id bh1780_id[] = अणु
	अणु "bh1780", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, bh1780_id);

अटल स्थिर काष्ठा of_device_id of_bh1780_match[] = अणु
	अणु .compatible = "rohm,bh1780gli", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_bh1780_match);

अटल काष्ठा i2c_driver bh1780_driver = अणु
	.probe		= bh1780_probe,
	.हटाओ		= bh1780_हटाओ,
	.id_table	= bh1780_id,
	.driver = अणु
		.name = "bh1780",
		.pm = &bh1780_dev_pm_ops,
		.of_match_table = of_bh1780_match,
	पूर्ण,
पूर्ण;

module_i2c_driver(bh1780_driver);

MODULE_DESCRIPTION("ROHM BH1780GLI Ambient Light Sensor Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
