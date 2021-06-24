<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rfd77402.c - Support क्रम RF Digital RFD77402 Time-of-Flight (distance) sensor
 *
 * Copyright 2017 Peter Meerwald-Stadler <pmeerw@pmeerw.net>
 *
 * 7-bit I2C slave address 0x4c
 *
 * TODO: पूर्णांकerrupt
 * https://media.digikey.com/pdf/Data%20Sheets/RF%20Digital%20PDFs/RFD77402.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>

#समावेश <linux/iio/iपन.स>

#घोषणा RFD77402_DRV_NAME "rfd77402"

#घोषणा RFD77402_ICSR		0x00 /* Interrupt Control Status Register */
#घोषणा RFD77402_ICSR_INT_MODE	BIT(2)
#घोषणा RFD77402_ICSR_INT_POL	BIT(3)
#घोषणा RFD77402_ICSR_RESULT	BIT(4)
#घोषणा RFD77402_ICSR_M2H_MSG	BIT(5)
#घोषणा RFD77402_ICSR_H2M_MSG	BIT(6)
#घोषणा RFD77402_ICSR_RESET	BIT(7)

#घोषणा RFD77402_CMD_R		0x04
#घोषणा RFD77402_CMD_SINGLE	0x01
#घोषणा RFD77402_CMD_STANDBY	0x10
#घोषणा RFD77402_CMD_MCPU_OFF	0x11
#घोषणा RFD77402_CMD_MCPU_ON	0x12
#घोषणा RFD77402_CMD_RESET	BIT(6)
#घोषणा RFD77402_CMD_VALID	BIT(7)

#घोषणा RFD77402_STATUS_R	0x06
#घोषणा RFD77402_STATUS_PM_MASK	GENMASK(4, 0)
#घोषणा RFD77402_STATUS_STANDBY	0x00
#घोषणा RFD77402_STATUS_MCPU_OFF	0x10
#घोषणा RFD77402_STATUS_MCPU_ON	0x18

#घोषणा RFD77402_RESULT_R	0x08
#घोषणा RFD77402_RESULT_DIST_MASK	GENMASK(12, 2)
#घोषणा RFD77402_RESULT_ERR_MASK	GENMASK(14, 13)
#घोषणा RFD77402_RESULT_VALID	BIT(15)

#घोषणा RFD77402_PMU_CFG	0x14
#घोषणा RFD77402_PMU_MCPU_INIT	BIT(9)

#घोषणा RFD77402_I2C_INIT_CFG	0x1c
#घोषणा RFD77402_I2C_ADDR_INCR	BIT(0)
#घोषणा RFD77402_I2C_DATA_INCR	BIT(2)
#घोषणा RFD77402_I2C_HOST_DEBUG	BIT(5)
#घोषणा RFD77402_I2C_MCPU_DEBUG	BIT(6)

#घोषणा RFD77402_CMD_CFGR_A	0x0c
#घोषणा RFD77402_CMD_CFGR_B	0x0e
#घोषणा RFD77402_HFCFG_0	0x20
#घोषणा RFD77402_HFCFG_1	0x22
#घोषणा RFD77402_HFCFG_2	0x24
#घोषणा RFD77402_HFCFG_3	0x26

#घोषणा RFD77402_MOD_CHIP_ID	0x28

/* magic configuration values from datasheet */
अटल स्थिर काष्ठा अणु
	u8 reg;
	u16 val;
पूर्ण rf77402_tof_config[] = अणु
	अणुRFD77402_CMD_CFGR_A,	0xe100पूर्ण,
	अणुRFD77402_CMD_CFGR_B,	0x10ffपूर्ण,
	अणुRFD77402_HFCFG_0,	0x07d0पूर्ण,
	अणुRFD77402_HFCFG_1,	0x5008पूर्ण,
	अणुRFD77402_HFCFG_2,	0xa041पूर्ण,
	अणुRFD77402_HFCFG_3,	0x45d4पूर्ण,
पूर्ण;

काष्ठा rfd77402_data अणु
	काष्ठा i2c_client *client;
	/* Serialize पढ़ोs from the sensor */
	काष्ठा mutex lock;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec rfd77402_channels[] = अणु
	अणु
		.type = IIO_DISTANCE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
पूर्ण;

अटल पूर्णांक rfd77402_set_state(काष्ठा rfd77402_data *data, u8 state, u16 check)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, RFD77402_CMD_R,
					state | RFD77402_CMD_VALID);
	अगर (ret < 0)
		वापस ret;

	usleep_range(10000, 20000);

	ret = i2c_smbus_पढ़ो_word_data(data->client, RFD77402_STATUS_R);
	अगर (ret < 0)
		वापस ret;
	अगर ((ret & RFD77402_STATUS_PM_MASK) != check)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक rfd77402_measure(काष्ठा rfd77402_data *data)
अणु
	पूर्णांक ret;
	पूर्णांक tries = 10;

	ret = rfd77402_set_state(data, RFD77402_CMD_MCPU_ON,
				 RFD77402_STATUS_MCPU_ON);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, RFD77402_CMD_R,
					RFD77402_CMD_SINGLE |
					RFD77402_CMD_VALID);
	अगर (ret < 0)
		जाओ err;

	जबतक (tries-- > 0) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client, RFD77402_ICSR);
		अगर (ret < 0)
			जाओ err;
		अगर (ret & RFD77402_ICSR_RESULT)
			अवरोध;
		msleep(20);
	पूर्ण

	अगर (tries < 0) अणु
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	ret = i2c_smbus_पढ़ो_word_data(data->client, RFD77402_RESULT_R);
	अगर (ret < 0)
		जाओ err;

	अगर ((ret & RFD77402_RESULT_ERR_MASK) ||
	    !(ret & RFD77402_RESULT_VALID)) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण

	वापस (ret & RFD77402_RESULT_DIST_MASK) >> 2;

err:
	rfd77402_set_state(data, RFD77402_CMD_MCPU_OFF,
			   RFD77402_STATUS_MCPU_OFF);
	वापस ret;
पूर्ण

अटल पूर्णांक rfd77402_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा rfd77402_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&data->lock);
		ret = rfd77402_measure(data);
		mutex_unlock(&data->lock);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/* 1 LSB is 1 mm */
		*val = 0;
		*val2 = 1000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info rfd77402_info = अणु
	.पढ़ो_raw = rfd77402_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक rfd77402_init(काष्ठा rfd77402_data *data)
अणु
	पूर्णांक ret, i;

	ret = rfd77402_set_state(data, RFD77402_CMD_STANDBY,
				 RFD77402_STATUS_STANDBY);
	अगर (ret < 0)
		वापस ret;

	/* configure INT pad as push-pull, active low */
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, RFD77402_ICSR,
					RFD77402_ICSR_INT_MODE);
	अगर (ret < 0)
		वापस ret;

	/* I2C configuration */
	ret = i2c_smbus_ग_लिखो_word_data(data->client, RFD77402_I2C_INIT_CFG,
					RFD77402_I2C_ADDR_INCR |
					RFD77402_I2C_DATA_INCR |
					RFD77402_I2C_HOST_DEBUG	|
					RFD77402_I2C_MCPU_DEBUG);
	अगर (ret < 0)
		वापस ret;

	/* set initialization */
	ret = i2c_smbus_ग_लिखो_word_data(data->client, RFD77402_PMU_CFG, 0x0500);
	अगर (ret < 0)
		वापस ret;

	ret = rfd77402_set_state(data, RFD77402_CMD_MCPU_OFF,
				 RFD77402_STATUS_MCPU_OFF);
	अगर (ret < 0)
		वापस ret;

	/* set initialization */
	ret = i2c_smbus_ग_लिखो_word_data(data->client, RFD77402_PMU_CFG, 0x0600);
	अगर (ret < 0)
		वापस ret;

	ret = rfd77402_set_state(data, RFD77402_CMD_MCPU_ON,
				 RFD77402_STATUS_MCPU_ON);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(rf77402_tof_config); i++) अणु
		ret = i2c_smbus_ग_लिखो_word_data(data->client,
						rf77402_tof_config[i].reg,
						rf77402_tof_config[i].val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = rfd77402_set_state(data, RFD77402_CMD_STANDBY,
				 RFD77402_STATUS_STANDBY);

	वापस ret;
पूर्ण

अटल पूर्णांक rfd77402_घातerकरोwn(काष्ठा rfd77402_data *data)
अणु
	वापस rfd77402_set_state(data, RFD77402_CMD_STANDBY,
				  RFD77402_STATUS_STANDBY);
पूर्ण

अटल पूर्णांक rfd77402_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rfd77402_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_word_data(client, RFD77402_MOD_CHIP_ID);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != 0xad01 && ret != 0xad02) /* known chip ids */
		वापस -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	indio_dev->info = &rfd77402_info;
	indio_dev->channels = rfd77402_channels;
	indio_dev->num_channels = ARRAY_SIZE(rfd77402_channels);
	indio_dev->name = RFD77402_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = rfd77402_init(data);
	अगर (ret < 0)
		वापस ret;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err_घातerकरोwn;

	वापस 0;

err_घातerकरोwn:
	rfd77402_घातerकरोwn(data);
	वापस ret;
पूर्ण

अटल पूर्णांक rfd77402_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);
	rfd77402_घातerकरोwn(iio_priv(indio_dev));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rfd77402_suspend(काष्ठा device *dev)
अणु
	काष्ठा rfd77402_data *data = iio_priv(i2c_get_clientdata(
				     to_i2c_client(dev)));

	वापस rfd77402_घातerकरोwn(data);
पूर्ण

अटल पूर्णांक rfd77402_resume(काष्ठा device *dev)
अणु
	काष्ठा rfd77402_data *data = iio_priv(i2c_get_clientdata(
				     to_i2c_client(dev)));

	वापस rfd77402_init(data);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(rfd77402_pm_ops, rfd77402_suspend, rfd77402_resume);

अटल स्थिर काष्ठा i2c_device_id rfd77402_id[] = अणु
	अणु "rfd77402", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rfd77402_id);

अटल काष्ठा i2c_driver rfd77402_driver = अणु
	.driver = अणु
		.name   = RFD77402_DRV_NAME,
		.pm     = &rfd77402_pm_ops,
	पूर्ण,
	.probe  = rfd77402_probe,
	.हटाओ = rfd77402_हटाओ,
	.id_table = rfd77402_id,
पूर्ण;

module_i2c_driver(rfd77402_driver);

MODULE_AUTHOR("Peter Meerwald-Stadler <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("RFD77402 Time-of-Flight sensor driver");
MODULE_LICENSE("GPL");
