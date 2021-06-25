<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO driver क्रम the MiraMEMS DA311 3-axis accelerometer
 *
 * Copyright (c) 2016 Hans de Goede <hdegoede@redhat.com>
 * Copyright (c) 2011-2013 MiraMEMS Sensing Technology Co., Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/byteorder/generic.h>

#घोषणा DA311_CHIP_ID			0x13

/*
 * Note रेजिस्टर addressed go from 0 - 0x3f and then wrap.
 * For some reason there are 2 banks with 0 - 0x3f addresses,
 * rather then a single 0-0x7f bank.
 */

/* Bank 0 regs */
#घोषणा DA311_REG_BANK			0x0000
#घोषणा DA311_REG_LDO_REG		0x0006
#घोषणा DA311_REG_CHIP_ID		0x000f
#घोषणा DA311_REG_TEMP_CFG_REG		0x001f
#घोषणा DA311_REG_CTRL_REG1		0x0020
#घोषणा DA311_REG_CTRL_REG3		0x0022
#घोषणा DA311_REG_CTRL_REG4		0x0023
#घोषणा DA311_REG_CTRL_REG5		0x0024
#घोषणा DA311_REG_CTRL_REG6		0x0025
#घोषणा DA311_REG_STATUS_REG		0x0027
#घोषणा DA311_REG_OUT_X_L		0x0028
#घोषणा DA311_REG_OUT_X_H		0x0029
#घोषणा DA311_REG_OUT_Y_L		0x002a
#घोषणा DA311_REG_OUT_Y_H		0x002b
#घोषणा DA311_REG_OUT_Z_L		0x002c
#घोषणा DA311_REG_OUT_Z_H		0x002d
#घोषणा DA311_REG_INT1_CFG		0x0030
#घोषणा DA311_REG_INT1_SRC		0x0031
#घोषणा DA311_REG_INT1_THS		0x0032
#घोषणा DA311_REG_INT1_DURATION		0x0033
#घोषणा DA311_REG_INT2_CFG		0x0034
#घोषणा DA311_REG_INT2_SRC		0x0035
#घोषणा DA311_REG_INT2_THS		0x0036
#घोषणा DA311_REG_INT2_DURATION		0x0037
#घोषणा DA311_REG_CLICK_CFG		0x0038
#घोषणा DA311_REG_CLICK_SRC		0x0039
#घोषणा DA311_REG_CLICK_THS		0x003a
#घोषणा DA311_REG_TIME_LIMIT		0x003b
#घोषणा DA311_REG_TIME_LATENCY		0x003c
#घोषणा DA311_REG_TIME_WINDOW		0x003d

/* Bank 1 regs */
#घोषणा DA311_REG_SOFT_RESET		0x0105
#घोषणा DA311_REG_OTP_XOFF_L		0x0110
#घोषणा DA311_REG_OTP_XOFF_H		0x0111
#घोषणा DA311_REG_OTP_YOFF_L		0x0112
#घोषणा DA311_REG_OTP_YOFF_H		0x0113
#घोषणा DA311_REG_OTP_ZOFF_L		0x0114
#घोषणा DA311_REG_OTP_ZOFF_H		0x0115
#घोषणा DA311_REG_OTP_XSO		0x0116
#घोषणा DA311_REG_OTP_YSO		0x0117
#घोषणा DA311_REG_OTP_ZSO		0x0118
#घोषणा DA311_REG_OTP_TRIM_OSC		0x011b
#घोषणा DA311_REG_LPF_ABSOLUTE		0x011c
#घोषणा DA311_REG_TEMP_OFF1		0x0127
#घोषणा DA311_REG_TEMP_OFF2		0x0128
#घोषणा DA311_REG_TEMP_OFF3		0x0129
#घोषणा DA311_REG_OTP_TRIM_THERM_H	0x011a

/*
 * a value of + or -1024 corresponds to + or - 1G
 * scale = 9.81 / 1024 = 0.009580078
 */

अटल स्थिर पूर्णांक da311_nscale = 9580078;

#घोषणा DA311_CHANNEL(reg, axis) अणु	\
	.type = IIO_ACCEL,	\
	.address = reg,	\
	.modअगरied = 1,	\
	.channel2 = IIO_MOD_##axis,	\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec da311_channels[] = अणु
	/* | 0x80 comes from the android driver */
	DA311_CHANNEL(DA311_REG_OUT_X_L | 0x80, X),
	DA311_CHANNEL(DA311_REG_OUT_Y_L | 0x80, Y),
	DA311_CHANNEL(DA311_REG_OUT_Z_L | 0x80, Z),
पूर्ण;

काष्ठा da311_data अणु
	काष्ठा i2c_client *client;
पूर्ण;

अटल पूर्णांक da311_रेजिस्टर_mask_ग_लिखो(काष्ठा i2c_client *client, u16 addr,
				     u8 mask, u8 data)
अणु
	पूर्णांक ret;
	u8 पंचांगp_data = 0;

	अगर (addr & 0xff00) अणु
		/* Select bank 1 */
		ret = i2c_smbus_ग_लिखो_byte_data(client, DA311_REG_BANK, 0x01);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (mask != 0xff) अणु
		ret = i2c_smbus_पढ़ो_byte_data(client, addr);
		अगर (ret < 0)
			वापस ret;
		पंचांगp_data = ret;
	पूर्ण

	पंचांगp_data &= ~mask;
	पंचांगp_data |= data & mask;
	ret = i2c_smbus_ग_लिखो_byte_data(client, addr & 0xff, पंचांगp_data);
	अगर (ret < 0)
		वापस ret;

	अगर (addr & 0xff00) अणु
		/* Back to bank 0 */
		ret = i2c_smbus_ग_लिखो_byte_data(client, DA311_REG_BANK, 0x00);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Init sequence taken from the android driver */
अटल पूर्णांक da311_reset(काष्ठा i2c_client *client)
अणु
	अटल स्थिर काष्ठा अणु
		u16 addr;
		u8 mask;
		u8 data;
	पूर्ण init_data[] = अणु
		अणु DA311_REG_TEMP_CFG_REG,       0xff,   0x08 पूर्ण,
		अणु DA311_REG_CTRL_REG5,          0xff,   0x80 पूर्ण,
		अणु DA311_REG_CTRL_REG4,          0x30,   0x00 पूर्ण,
		अणु DA311_REG_CTRL_REG1,          0xff,   0x6f पूर्ण,
		अणु DA311_REG_TEMP_CFG_REG,       0xff,   0x88 पूर्ण,
		अणु DA311_REG_LDO_REG,            0xff,   0x02 पूर्ण,
		अणु DA311_REG_OTP_TRIM_OSC,       0xff,   0x27 पूर्ण,
		अणु DA311_REG_LPF_ABSOLUTE,       0xff,   0x30 पूर्ण,
		अणु DA311_REG_TEMP_OFF1,          0xff,   0x3f पूर्ण,
		अणु DA311_REG_TEMP_OFF2,          0xff,   0xff पूर्ण,
		अणु DA311_REG_TEMP_OFF3,          0xff,   0x0f पूर्ण,
	पूर्ण;
	पूर्णांक i, ret;

	/* Reset */
	ret = da311_रेजिस्टर_mask_ग_लिखो(client, DA311_REG_SOFT_RESET,
					0xff, 0xaa);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(init_data); i++) अणु
		ret = da311_रेजिस्टर_mask_ग_लिखो(client,
						init_data[i].addr,
						init_data[i].mask,
						init_data[i].data);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da311_enable(काष्ठा i2c_client *client, bool enable)
अणु
	u8 data = enable ? 0x00 : 0x20;

	वापस da311_रेजिस्टर_mask_ग_लिखो(client, DA311_REG_TEMP_CFG_REG,
					 0x20, data);
पूर्ण

अटल पूर्णांक da311_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा da311_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = i2c_smbus_पढ़ो_word_data(data->client, chan->address);
		अगर (ret < 0)
			वापस ret;
		/*
		 * Values are 12 bits, stored as 16 bits with the 4
		 * least signअगरicant bits always 0.
		 */
		*val = (लघु)ret >> 4;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = da311_nscale;
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info da311_info = अणु
	.पढ़ो_raw	= da311_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक da311_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा da311_data *data;

	ret = i2c_smbus_पढ़ो_byte_data(client, DA311_REG_CHIP_ID);
	अगर (ret != DA311_CHIP_ID)
		वापस (ret < 0) ? ret : -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	i2c_set_clientdata(client, indio_dev);

	indio_dev->info = &da311_info;
	indio_dev->name = "da311";
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = da311_channels;
	indio_dev->num_channels = ARRAY_SIZE(da311_channels);

	ret = da311_reset(client);
	अगर (ret < 0)
		वापस ret;

	ret = da311_enable(client, true);
	अगर (ret < 0)
		वापस ret;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "device_register failed\n");
		da311_enable(client, false);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da311_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);

	वापस da311_enable(client, false);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक da311_suspend(काष्ठा device *dev)
अणु
	वापस da311_enable(to_i2c_client(dev), false);
पूर्ण

अटल पूर्णांक da311_resume(काष्ठा device *dev)
अणु
	वापस da311_enable(to_i2c_client(dev), true);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(da311_pm_ops, da311_suspend, da311_resume);

अटल स्थिर काष्ठा i2c_device_id da311_i2c_id[] = अणु
	अणु"da311", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da311_i2c_id);

अटल काष्ठा i2c_driver da311_driver = अणु
	.driver = अणु
		.name = "da311",
		.pm = &da311_pm_ops,
	पूर्ण,
	.probe		= da311_probe,
	.हटाओ		= da311_हटाओ,
	.id_table	= da311_i2c_id,
पूर्ण;

module_i2c_driver(da311_driver);

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("MiraMEMS DA311 3-Axis Accelerometer driver");
MODULE_LICENSE("GPL v2");
