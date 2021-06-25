<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mCube MC3230 3-Axis Accelerometer
 *
 * Copyright (c) 2016 Hans de Goede <hdegoede@redhat.com>
 *
 * IIO driver क्रम mCube MC3230; 7-bit I2C address: 0x4c.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा MC3230_REG_XOUT			0x00
#घोषणा MC3230_REG_YOUT			0x01
#घोषणा MC3230_REG_ZOUT			0x02

#घोषणा MC3230_REG_MODE			0x07
#घोषणा MC3230_MODE_OPCON_MASK		0x03
#घोषणा MC3230_MODE_OPCON_WAKE		0x01
#घोषणा MC3230_MODE_OPCON_STANDBY	0x03

#घोषणा MC3230_REG_CHIP_ID		0x18
#घोषणा MC3230_CHIP_ID			0x01

#घोषणा MC3230_REG_PRODUCT_CODE		0x3b
#घोषणा MC3230_PRODUCT_CODE		0x19

/*
 * The accelerometer has one measurement range:
 *
 * -1.5g - +1.5g (8-bit, चिन्हित)
 *
 * scale = (1.5 + 1.5) * 9.81 / (2^8 - 1)	= 0.115411765
 */

अटल स्थिर पूर्णांक mc3230_nscale = 115411765;

#घोषणा MC3230_CHANNEL(reg, axis) अणु	\
	.type = IIO_ACCEL,	\
	.address = reg,	\
	.modअगरied = 1,	\
	.channel2 = IIO_MOD_##axis,	\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mc3230_channels[] = अणु
	MC3230_CHANNEL(MC3230_REG_XOUT, X),
	MC3230_CHANNEL(MC3230_REG_YOUT, Y),
	MC3230_CHANNEL(MC3230_REG_ZOUT, Z),
पूर्ण;

काष्ठा mc3230_data अणु
	काष्ठा i2c_client *client;
पूर्ण;

अटल पूर्णांक mc3230_set_opcon(काष्ठा mc3230_data *data, पूर्णांक opcon)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = data->client;

	ret = i2c_smbus_पढ़ो_byte_data(client, MC3230_REG_MODE);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to read mode reg: %d\n", ret);
		वापस ret;
	पूर्ण

	ret &= ~MC3230_MODE_OPCON_MASK;
	ret |= opcon;

	ret = i2c_smbus_ग_लिखो_byte_data(client, MC3230_REG_MODE, ret);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to write mode reg: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mc3230_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mc3230_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = i2c_smbus_पढ़ो_byte_data(data->client, chan->address);
		अगर (ret < 0)
			वापस ret;
		*val = sign_extend32(ret, 7);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = mc3230_nscale;
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info mc3230_info = अणु
	.पढ़ो_raw	= mc3230_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक mc3230_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा mc3230_data *data;

	/* First check chip-id and product-id */
	ret = i2c_smbus_पढ़ो_byte_data(client, MC3230_REG_CHIP_ID);
	अगर (ret != MC3230_CHIP_ID)
		वापस (ret < 0) ? ret : -ENODEV;

	ret = i2c_smbus_पढ़ो_byte_data(client, MC3230_REG_PRODUCT_CODE);
	अगर (ret != MC3230_PRODUCT_CODE)
		वापस (ret < 0) ? ret : -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev) अणु
		dev_err(&client->dev, "iio allocation failed!\n");
		वापस -ENOMEM;
	पूर्ण

	data = iio_priv(indio_dev);
	data->client = client;
	i2c_set_clientdata(client, indio_dev);

	indio_dev->info = &mc3230_info;
	indio_dev->name = "mc3230";
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = mc3230_channels;
	indio_dev->num_channels = ARRAY_SIZE(mc3230_channels);

	ret = mc3230_set_opcon(data, MC3230_MODE_OPCON_WAKE);
	अगर (ret < 0)
		वापस ret;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "device_register failed\n");
		mc3230_set_opcon(data, MC3230_MODE_OPCON_STANDBY);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mc3230_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);

	वापस mc3230_set_opcon(iio_priv(indio_dev), MC3230_MODE_OPCON_STANDBY);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mc3230_suspend(काष्ठा device *dev)
अणु
	काष्ठा mc3230_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस mc3230_set_opcon(data, MC3230_MODE_OPCON_STANDBY);
पूर्ण

अटल पूर्णांक mc3230_resume(काष्ठा device *dev)
अणु
	काष्ठा mc3230_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस mc3230_set_opcon(data, MC3230_MODE_OPCON_WAKE);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(mc3230_pm_ops, mc3230_suspend, mc3230_resume);

अटल स्थिर काष्ठा i2c_device_id mc3230_i2c_id[] = अणु
	अणु"mc3230", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mc3230_i2c_id);

अटल काष्ठा i2c_driver mc3230_driver = अणु
	.driver = अणु
		.name = "mc3230",
		.pm = &mc3230_pm_ops,
	पूर्ण,
	.probe		= mc3230_probe,
	.हटाओ		= mc3230_हटाओ,
	.id_table	= mc3230_i2c_id,
पूर्ण;

module_i2c_driver(mc3230_driver);

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("mCube MC3230 3-Axis Accelerometer driver");
MODULE_LICENSE("GPL v2");
