<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO driver क्रम the MiraMEMS DA280 3-axis accelerometer and
 * IIO driver क्रम the MiraMEMS DA226 2-axis accelerometer
 *
 * Copyright (c) 2016 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/byteorder/generic.h>

#घोषणा DA280_REG_CHIP_ID		0x01
#घोषणा DA280_REG_ACC_X_LSB		0x02
#घोषणा DA280_REG_ACC_Y_LSB		0x04
#घोषणा DA280_REG_ACC_Z_LSB		0x06
#घोषणा DA280_REG_MODE_BW		0x11

#घोषणा DA280_CHIP_ID			0x13
#घोषणा DA280_MODE_ENABLE		0x1e
#घोषणा DA280_MODE_DISABLE		0x9e

क्रमागत da280_chipset अणु da226, da280 पूर्ण;

/*
 * a value of + or -4096 corresponds to + or - 1G
 * scale = 9.81 / 4096 = 0.002395019
 */

अटल स्थिर पूर्णांक da280_nscale = 2395019;

#घोषणा DA280_CHANNEL(reg, axis) अणु	\
	.type = IIO_ACCEL,	\
	.address = reg,	\
	.modअगरied = 1,	\
	.channel2 = IIO_MOD_##axis,	\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec da280_channels[] = अणु
	DA280_CHANNEL(DA280_REG_ACC_X_LSB, X),
	DA280_CHANNEL(DA280_REG_ACC_Y_LSB, Y),
	DA280_CHANNEL(DA280_REG_ACC_Z_LSB, Z),
पूर्ण;

काष्ठा da280_data अणु
	काष्ठा i2c_client *client;
पूर्ण;

अटल पूर्णांक da280_enable(काष्ठा i2c_client *client, bool enable)
अणु
	u8 data = enable ? DA280_MODE_ENABLE : DA280_MODE_DISABLE;

	वापस i2c_smbus_ग_लिखो_byte_data(client, DA280_REG_MODE_BW, data);
पूर्ण

अटल पूर्णांक da280_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा da280_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = i2c_smbus_पढ़ो_word_data(data->client, chan->address);
		अगर (ret < 0)
			वापस ret;
		/*
		 * Values are 14 bits, stored as 16 bits with the 2
		 * least signअगरicant bits always 0.
		 */
		*val = (लघु)ret >> 2;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = da280_nscale;
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info da280_info = अणु
	.पढ़ो_raw	= da280_पढ़ो_raw,
पूर्ण;

अटल क्रमागत da280_chipset da280_match_acpi_device(काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस -EINVAL;

	वापस (क्रमागत da280_chipset) id->driver_data;
पूर्ण

अटल पूर्णांक da280_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा da280_data *data;
	क्रमागत da280_chipset chip;

	ret = i2c_smbus_पढ़ो_byte_data(client, DA280_REG_CHIP_ID);
	अगर (ret != DA280_CHIP_ID)
		वापस (ret < 0) ? ret : -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	i2c_set_clientdata(client, indio_dev);

	indio_dev->info = &da280_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = da280_channels;

	अगर (ACPI_HANDLE(&client->dev)) अणु
		chip = da280_match_acpi_device(&client->dev);
	पूर्ण अन्यथा अणु
		chip = id->driver_data;
	पूर्ण

	अगर (chip == da226) अणु
		indio_dev->name = "da226";
		indio_dev->num_channels = 2;
	पूर्ण अन्यथा अणु
		indio_dev->name = "da280";
		indio_dev->num_channels = 3;
	पूर्ण

	ret = da280_enable(client, true);
	अगर (ret < 0)
		वापस ret;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "device_register failed\n");
		da280_enable(client, false);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da280_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);

	वापस da280_enable(client, false);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक da280_suspend(काष्ठा device *dev)
अणु
	वापस da280_enable(to_i2c_client(dev), false);
पूर्ण

अटल पूर्णांक da280_resume(काष्ठा device *dev)
अणु
	वापस da280_enable(to_i2c_client(dev), true);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(da280_pm_ops, da280_suspend, da280_resume);

अटल स्थिर काष्ठा acpi_device_id da280_acpi_match[] = अणु
	अणु"MIRAACC", da280पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, da280_acpi_match);

अटल स्थिर काष्ठा i2c_device_id da280_i2c_id[] = अणु
	अणु "da226", da226 पूर्ण,
	अणु "da280", da280 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da280_i2c_id);

अटल काष्ठा i2c_driver da280_driver = अणु
	.driver = अणु
		.name = "da280",
		.acpi_match_table = ACPI_PTR(da280_acpi_match),
		.pm = &da280_pm_ops,
	पूर्ण,
	.probe		= da280_probe,
	.हटाओ		= da280_हटाओ,
	.id_table	= da280_i2c_id,
पूर्ण;

module_i2c_driver(da280_driver);

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("MiraMEMS DA280 3-Axis Accelerometer driver");
MODULE_LICENSE("GPL v2");
