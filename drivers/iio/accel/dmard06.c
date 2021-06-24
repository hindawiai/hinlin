<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO driver क्रम Domपूर्णांकech DMARD06 accelerometer
 *
 * Copyright (C) 2016 Aleksei Mamlin <mamlinav@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>

#घोषणा DMARD06_DRV_NAME		"dmard06"

/* Device data रेजिस्टरs */
#घोषणा DMARD06_CHIP_ID_REG		0x0f
#घोषणा DMARD06_TOUT_REG		0x40
#घोषणा DMARD06_XOUT_REG		0x41
#घोषणा DMARD06_YOUT_REG		0x42
#घोषणा DMARD06_ZOUT_REG		0x43
#घोषणा DMARD06_CTRL1_REG		0x44

/* Device ID value */
#घोषणा DMARD05_CHIP_ID			0x05
#घोषणा DMARD06_CHIP_ID			0x06
#घोषणा DMARD07_CHIP_ID			0x07

/* Device values */
#घोषणा DMARD05_AXIS_SCALE_VAL		15625
#घोषणा DMARD06_AXIS_SCALE_VAL		31250
#घोषणा DMARD06_TEMP_CENTER_VAL		25
#घोषणा DMARD06_SIGN_BIT		7

/* Device घातer modes */
#घोषणा DMARD06_MODE_NORMAL		0x27
#घोषणा DMARD06_MODE_POWERDOWN		0x00

/* Device channels */
#घोषणा DMARD06_ACCEL_CHANNEL(_axis, _reg) अणु			\
	.type = IIO_ACCEL,					\
	.address = _reg,					\
	.channel2 = IIO_MOD_##_axis,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.modअगरied = 1,						\
पूर्ण

#घोषणा DMARD06_TEMP_CHANNEL(_reg) अणु				\
	.type = IIO_TEMP,					\
	.address = _reg,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
			      BIT(IIO_CHAN_INFO_OFFSET),	\
पूर्ण

काष्ठा dmard06_data अणु
	काष्ठा i2c_client *client;
	u8 chip_id;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec dmard06_channels[] = अणु
	DMARD06_ACCEL_CHANNEL(X, DMARD06_XOUT_REG),
	DMARD06_ACCEL_CHANNEL(Y, DMARD06_YOUT_REG),
	DMARD06_ACCEL_CHANNEL(Z, DMARD06_ZOUT_REG),
	DMARD06_TEMP_CHANNEL(DMARD06_TOUT_REG),
पूर्ण;

अटल पूर्णांक dmard06_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा dmard06_data *dmard06 = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = i2c_smbus_पढ़ो_byte_data(dmard06->client,
					       chan->address);
		अगर (ret < 0) अणु
			dev_err(&dmard06->client->dev,
				"Error reading data: %d\n", ret);
			वापस ret;
		पूर्ण

		*val = sign_extend32(ret, DMARD06_SIGN_BIT);

		अगर (dmard06->chip_id == DMARD06_CHIP_ID)
			*val = *val >> 1;

		चयन (chan->type) अणु
		हाल IIO_ACCEL:
			वापस IIO_VAL_INT;
		हाल IIO_TEMP:
			अगर (dmard06->chip_id != DMARD06_CHIP_ID)
				*val = *val / 2;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val = DMARD06_TEMP_CENTER_VAL;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ACCEL:
			*val = 0;
			अगर (dmard06->chip_id == DMARD06_CHIP_ID)
				*val2 = DMARD06_AXIS_SCALE_VAL;
			अन्यथा
				*val2 = DMARD05_AXIS_SCALE_VAL;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info dmard06_info = अणु
	.पढ़ो_raw	= dmard06_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक dmard06_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा dmard06_data *dmard06;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "I2C check functionality failed\n");
		वापस -ENXIO;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*dmard06));
	अगर (!indio_dev) अणु
		dev_err(&client->dev, "Failed to allocate iio device\n");
		वापस -ENOMEM;
	पूर्ण

	dmard06 = iio_priv(indio_dev);
	dmard06->client = client;

	ret = i2c_smbus_पढ़ो_byte_data(dmard06->client, DMARD06_CHIP_ID_REG);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Error reading chip id: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ret != DMARD05_CHIP_ID && ret != DMARD06_CHIP_ID &&
	    ret != DMARD07_CHIP_ID) अणु
		dev_err(&client->dev, "Invalid chip id: %02d\n", ret);
		वापस -ENODEV;
	पूर्ण

	dmard06->chip_id = ret;

	i2c_set_clientdata(client, indio_dev);
	indio_dev->name = DMARD06_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = dmard06_channels;
	indio_dev->num_channels = ARRAY_SIZE(dmard06_channels);
	indio_dev->info = &dmard06_info;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dmard06_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा dmard06_data *dmard06 = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(dmard06->client, DMARD06_CTRL1_REG,
					DMARD06_MODE_POWERDOWN);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक dmard06_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा dmard06_data *dmard06 = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(dmard06->client, DMARD06_CTRL1_REG,
					DMARD06_MODE_NORMAL);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(dmard06_pm_ops, dmard06_suspend, dmard06_resume);
#घोषणा DMARD06_PM_OPS (&dmard06_pm_ops)
#अन्यथा
#घोषणा DMARD06_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id dmard06_id[] = अणु
	अणु "dmard05", 0 पूर्ण,
	अणु "dmard06", 0 पूर्ण,
	अणु "dmard07", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, dmard06_id);

अटल स्थिर काष्ठा of_device_id dmard06_of_match[] = अणु
	अणु .compatible = "domintech,dmard05" पूर्ण,
	अणु .compatible = "domintech,dmard06" पूर्ण,
	अणु .compatible = "domintech,dmard07" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dmard06_of_match);

अटल काष्ठा i2c_driver dmard06_driver = अणु
	.probe = dmard06_probe,
	.id_table = dmard06_id,
	.driver = अणु
		.name = DMARD06_DRV_NAME,
		.of_match_table = dmard06_of_match,
		.pm = DMARD06_PM_OPS,
	पूर्ण,
पूर्ण;
module_i2c_driver(dmard06_driver);

MODULE_AUTHOR("Aleksei Mamlin <mamlinav@gmail.com>");
MODULE_DESCRIPTION("Domintech DMARD06 accelerometer driver");
MODULE_LICENSE("GPL v2");
