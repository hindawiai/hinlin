<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Freescale MMA7660FC 3-Axis Accelerometer
 *
 * Copyright (c) 2016, Intel Corporation.
 *
 * IIO driver क्रम Freescale MMA7660FC; 7-bit I2C address: 0x4c.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा MMA7660_DRIVER_NAME	"mma7660"

#घोषणा MMA7660_REG_XOUT	0x00
#घोषणा MMA7660_REG_YOUT	0x01
#घोषणा MMA7660_REG_ZOUT	0x02
#घोषणा MMA7660_REG_OUT_BIT_ALERT	BIT(6)

#घोषणा MMA7660_REG_MODE	0x07
#घोषणा MMA7660_REG_MODE_BIT_MODE	BIT(0)
#घोषणा MMA7660_REG_MODE_BIT_TON	BIT(2)

#घोषणा MMA7660_I2C_READ_RETRIES	5

/*
 * The accelerometer has one measurement range:
 *
 * -1.5g - +1.5g (6-bit, चिन्हित)
 *
 * scale = (1.5 + 1.5) * 9.81 / (2^6 - 1)	= 0.467142857
 */

#घोषणा MMA7660_SCALE_AVAIL	"0.467142857"

अटल स्थिर पूर्णांक mma7660_nscale = 467142857;

#घोषणा MMA7660_CHANNEL(reg, axis) अणु	\
	.type = IIO_ACCEL,	\
	.address = reg,	\
	.modअगरied = 1,	\
	.channel2 = IIO_MOD_##axis,	\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mma7660_channels[] = अणु
	MMA7660_CHANNEL(MMA7660_REG_XOUT, X),
	MMA7660_CHANNEL(MMA7660_REG_YOUT, Y),
	MMA7660_CHANNEL(MMA7660_REG_ZOUT, Z),
पूर्ण;

क्रमागत mma7660_mode अणु
	MMA7660_MODE_STANDBY,
	MMA7660_MODE_ACTIVE
पूर्ण;

काष्ठा mma7660_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	क्रमागत mma7660_mode mode;
पूर्ण;

अटल IIO_CONST_ATTR(in_accel_scale_available, MMA7660_SCALE_AVAIL);

अटल काष्ठा attribute *mma7660_attributes[] = अणु
	&iio_स्थिर_attr_in_accel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mma7660_attribute_group = अणु
	.attrs = mma7660_attributes
पूर्ण;

अटल पूर्णांक mma7660_set_mode(काष्ठा mma7660_data *data,
				क्रमागत mma7660_mode mode)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = data->client;

	अगर (mode == data->mode)
		वापस 0;

	ret = i2c_smbus_पढ़ो_byte_data(client, MMA7660_REG_MODE);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to read sensor mode\n");
		वापस ret;
	पूर्ण

	अगर (mode == MMA7660_MODE_ACTIVE) अणु
		ret &= ~MMA7660_REG_MODE_BIT_TON;
		ret |= MMA7660_REG_MODE_BIT_MODE;
	पूर्ण अन्यथा अणु
		ret &= ~MMA7660_REG_MODE_BIT_TON;
		ret &= ~MMA7660_REG_MODE_BIT_MODE;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(client, MMA7660_REG_MODE, ret);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to change sensor mode\n");
		वापस ret;
	पूर्ण

	data->mode = mode;

	वापस ret;
पूर्ण

अटल पूर्णांक mma7660_पढ़ो_accel(काष्ठा mma7660_data *data, u8 address)
अणु
	पूर्णांक ret, retries = MMA7660_I2C_READ_RETRIES;
	काष्ठा i2c_client *client = data->client;

	/*
	 * Read data. If the Alert bit is set, the रेजिस्टर was पढ़ो at
	 * the same समय as the device was attempting to update the content.
	 * The solution is to पढ़ो the रेजिस्टर again. Do this only
	 * MMA7660_I2C_READ_RETRIES बार to aव्योम spending too much समय
	 * in the kernel.
	 */
	करो अणु
		ret = i2c_smbus_पढ़ो_byte_data(client, address);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "register read failed\n");
			वापस ret;
		पूर्ण
	पूर्ण जबतक (retries-- > 0 && ret & MMA7660_REG_OUT_BIT_ALERT);

	अगर (ret & MMA7660_REG_OUT_BIT_ALERT) अणु
		dev_err(&client->dev, "all register read retries failed\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mma7660_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mma7660_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&data->lock);
		ret = mma7660_पढ़ो_accel(data, chan->address);
		mutex_unlock(&data->lock);
		अगर (ret < 0)
			वापस ret;
		*val = sign_extend32(ret, 5);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = mma7660_nscale;
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info mma7660_info = अणु
	.पढ़ो_raw		= mma7660_पढ़ो_raw,
	.attrs			= &mma7660_attribute_group,
पूर्ण;

अटल पूर्णांक mma7660_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा mma7660_data *data;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev) अणु
		dev_err(&client->dev, "iio allocation failed!\n");
		वापस -ENOMEM;
	पूर्ण

	data = iio_priv(indio_dev);
	data->client = client;
	i2c_set_clientdata(client, indio_dev);
	mutex_init(&data->lock);
	data->mode = MMA7660_MODE_STANDBY;

	indio_dev->info = &mma7660_info;
	indio_dev->name = MMA7660_DRIVER_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = mma7660_channels;
	indio_dev->num_channels = ARRAY_SIZE(mma7660_channels);

	ret = mma7660_set_mode(data, MMA7660_MODE_ACTIVE);
	अगर (ret < 0)
		वापस ret;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "device_register failed\n");
		mma7660_set_mode(data, MMA7660_MODE_STANDBY);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mma7660_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);

	वापस mma7660_set_mode(iio_priv(indio_dev), MMA7660_MODE_STANDBY);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mma7660_suspend(काष्ठा device *dev)
अणु
	काष्ठा mma7660_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस mma7660_set_mode(data, MMA7660_MODE_STANDBY);
पूर्ण

अटल पूर्णांक mma7660_resume(काष्ठा device *dev)
अणु
	काष्ठा mma7660_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस mma7660_set_mode(data, MMA7660_MODE_ACTIVE);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mma7660_pm_ops, mma7660_suspend, mma7660_resume);

#घोषणा MMA7660_PM_OPS (&mma7660_pm_ops)
#अन्यथा
#घोषणा MMA7660_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id mma7660_i2c_id[] = अणु
	अणु"mma7660", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mma7660_i2c_id);

अटल स्थिर काष्ठा of_device_id mma7660_of_match[] = अणु
	अणु .compatible = "fsl,mma7660" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mma7660_of_match);

अटल स्थिर काष्ठा acpi_device_id mma7660_acpi_id[] = अणु
	अणु"MMA7660", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, mma7660_acpi_id);

अटल काष्ठा i2c_driver mma7660_driver = अणु
	.driver = अणु
		.name = "mma7660",
		.pm = MMA7660_PM_OPS,
		.of_match_table = mma7660_of_match,
		.acpi_match_table = ACPI_PTR(mma7660_acpi_id),
	पूर्ण,
	.probe		= mma7660_probe,
	.हटाओ		= mma7660_हटाओ,
	.id_table	= mma7660_i2c_id,
पूर्ण;

module_i2c_driver(mma7660_driver);

MODULE_AUTHOR("Constantin Musca <constantin.musca@intel.com>");
MODULE_DESCRIPTION("Freescale MMA7660FC 3-Axis Accelerometer driver");
MODULE_LICENSE("GPL v2");
