<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO driver क्रम the 3-axis accelerometer Domपूर्णांकech ARD10.
 *
 * Copyright (c) 2016 Hans de Goede <hdegoede@redhat.com>
 * Copyright (c) 2012 Domपूर्णांकech Technology Co., Ltd
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/byteorder/generic.h>

#घोषणा DMARD10_REG_ACTR			0x00
#घोषणा DMARD10_REG_AFEM			0x0c
#घोषणा DMARD10_REG_STADR			0x12
#घोषणा DMARD10_REG_STAINT			0x1c
#घोषणा DMARD10_REG_MISC2			0x1f
#घोषणा DMARD10_REG_PD				0x21

#घोषणा DMARD10_MODE_OFF			0x00
#घोषणा DMARD10_MODE_STANDBY			0x02
#घोषणा DMARD10_MODE_ACTIVE			0x06
#घोषणा DMARD10_MODE_READ_OTP			0x12
#घोषणा DMARD10_MODE_RESET_DATA_PATH		0x82

/* AFEN set 1, ATM[2:0]=b'000 (normal), EN_Z/Y/X/T=1 */
#घोषणा DMARD10_VALUE_AFEM_AFEN_NORMAL		0x8f
/* ODR[3:0]=b'0111 (100Hz), CCK[3:0]=b'0100 (204.8kHZ) */
#घोषणा DMARD10_VALUE_CKSEL_ODR_100_204		0x74
/* INTC[6:5]=b'00 */
#घोषणा DMARD10_VALUE_INTC			0x00
/* TAP1/TAP2 Average 2 */
#घोषणा DMARD10_VALUE_TAPNS_AVE_2		0x11

#घोषणा DMARD10_VALUE_STADR			0x55
#घोषणा DMARD10_VALUE_STAINT			0xaa
#घोषणा DMARD10_VALUE_MISC2_OSCA_EN		0x08
#घोषणा DMARD10_VALUE_PD_RST			0x52

/* Offsets पूर्णांकo the buffer पढ़ो in dmard10_पढ़ो_raw() */
#घोषणा DMARD10_X_OFFSET			1
#घोषणा DMARD10_Y_OFFSET			2
#घोषणा DMARD10_Z_OFFSET			3

/*
 * a value of + or -128 corresponds to + or - 1G
 * scale = 9.81 / 128 = 0.076640625
 */

अटल स्थिर पूर्णांक dmard10_nscale = 76640625;

#घोषणा DMARD10_CHANNEL(reg, axis) अणु	\
	.type = IIO_ACCEL,	\
	.address = reg,	\
	.modअगरied = 1,	\
	.channel2 = IIO_MOD_##axis,	\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec dmard10_channels[] = अणु
	DMARD10_CHANNEL(DMARD10_X_OFFSET, X),
	DMARD10_CHANNEL(DMARD10_Y_OFFSET, Y),
	DMARD10_CHANNEL(DMARD10_Z_OFFSET, Z),
पूर्ण;

काष्ठा dmard10_data अणु
	काष्ठा i2c_client *client;
पूर्ण;

/* Init sequence taken from the android driver */
अटल पूर्णांक dmard10_reset(काष्ठा i2c_client *client)
अणु
	अचिन्हित अक्षर buffer[7];
	पूर्णांक ret;

	/* 1. Powerकरोwn reset */
	ret = i2c_smbus_ग_लिखो_byte_data(client, DMARD10_REG_PD,
						DMARD10_VALUE_PD_RST);
	अगर (ret < 0)
		वापस ret;

	/*
	 * 2. ACTR => Standby mode => Download OTP to parameter reg =>
	 *    Standby mode => Reset data path => Standby mode
	 */
	buffer[0] = DMARD10_REG_ACTR;
	buffer[1] = DMARD10_MODE_STANDBY;
	buffer[2] = DMARD10_MODE_READ_OTP;
	buffer[3] = DMARD10_MODE_STANDBY;
	buffer[4] = DMARD10_MODE_RESET_DATA_PATH;
	buffer[5] = DMARD10_MODE_STANDBY;
	ret = i2c_master_send(client, buffer, 6);
	अगर (ret < 0)
		वापस ret;

	/* 3. OSCA_EN = 1, TSTO = b'000 (INT1 = normal, TEST0 = normal) */
	ret = i2c_smbus_ग_लिखो_byte_data(client, DMARD10_REG_MISC2,
						DMARD10_VALUE_MISC2_OSCA_EN);
	अगर (ret < 0)
		वापस ret;

	/* 4. AFEN = 1 (AFE will घातerकरोwn after ADC) */
	buffer[0] = DMARD10_REG_AFEM;
	buffer[1] = DMARD10_VALUE_AFEM_AFEN_NORMAL;
	buffer[2] = DMARD10_VALUE_CKSEL_ODR_100_204;
	buffer[3] = DMARD10_VALUE_INTC;
	buffer[4] = DMARD10_VALUE_TAPNS_AVE_2;
	buffer[5] = 0x00; /* DLYC, no delay timing */
	buffer[6] = 0x07; /* INTD=1 push-pull, INTA=1 active high, AUTOT=1 */
	ret = i2c_master_send(client, buffer, 7);
	अगर (ret < 0)
		वापस ret;

	/* 5. Activation mode */
	ret = i2c_smbus_ग_लिखो_byte_data(client, DMARD10_REG_ACTR,
						DMARD10_MODE_ACTIVE);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* Shutकरोwn sequence taken from the android driver */
अटल पूर्णांक dmard10_shutकरोwn(काष्ठा i2c_client *client)
अणु
	अचिन्हित अक्षर buffer[3];

	buffer[0] = DMARD10_REG_ACTR;
	buffer[1] = DMARD10_MODE_STANDBY;
	buffer[2] = DMARD10_MODE_OFF;

	वापस i2c_master_send(client, buffer, 3);
पूर्ण

अटल पूर्णांक dmard10_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा dmard10_data *data = iio_priv(indio_dev);
	__le16 buf[4];
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		/*
		 * Read 8 bytes starting at the REG_STADR रेजिस्टर, trying to
		 * पढ़ो the inभागidual X, Y, Z रेजिस्टरs will always पढ़ो 0.
		 */
		ret = i2c_smbus_पढ़ो_i2c_block_data(data->client,
						    DMARD10_REG_STADR,
						    माप(buf), (u8 *)buf);
		अगर (ret < 0)
			वापस ret;
		ret = le16_to_cpu(buf[chan->address]);
		*val = sign_extend32(ret, 12);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = dmard10_nscale;
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info dmard10_info = अणु
	.पढ़ो_raw	= dmard10_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक dmard10_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा dmard10_data *data;

	/* These 2 रेजिस्टरs have special POR reset values used क्रम id */
	ret = i2c_smbus_पढ़ो_byte_data(client, DMARD10_REG_STADR);
	अगर (ret != DMARD10_VALUE_STADR)
		वापस (ret < 0) ? ret : -ENODEV;

	ret = i2c_smbus_पढ़ो_byte_data(client, DMARD10_REG_STAINT);
	अगर (ret != DMARD10_VALUE_STAINT)
		वापस (ret < 0) ? ret : -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev) अणु
		dev_err(&client->dev, "iio allocation failed!\n");
		वापस -ENOMEM;
	पूर्ण

	data = iio_priv(indio_dev);
	data->client = client;
	i2c_set_clientdata(client, indio_dev);

	indio_dev->info = &dmard10_info;
	indio_dev->name = "dmard10";
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = dmard10_channels;
	indio_dev->num_channels = ARRAY_SIZE(dmard10_channels);

	ret = dmard10_reset(client);
	अगर (ret < 0)
		वापस ret;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "device_register failed\n");
		dmard10_shutकरोwn(client);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dmard10_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);

	वापस dmard10_shutकरोwn(client);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dmard10_suspend(काष्ठा device *dev)
अणु
	वापस dmard10_shutकरोwn(to_i2c_client(dev));
पूर्ण

अटल पूर्णांक dmard10_resume(काष्ठा device *dev)
अणु
	वापस dmard10_reset(to_i2c_client(dev));
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(dmard10_pm_ops, dmard10_suspend, dmard10_resume);

अटल स्थिर काष्ठा i2c_device_id dmard10_i2c_id[] = अणु
	अणु"dmard10", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, dmard10_i2c_id);

अटल काष्ठा i2c_driver dmard10_driver = अणु
	.driver = अणु
		.name = "dmard10",
		.pm = &dmard10_pm_ops,
	पूर्ण,
	.probe		= dmard10_probe,
	.हटाओ		= dmard10_हटाओ,
	.id_table	= dmard10_i2c_id,
पूर्ण;

module_i2c_driver(dmard10_driver);

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Domintech ARD10 3-Axis Accelerometer driver");
MODULE_LICENSE("GPL v2");
