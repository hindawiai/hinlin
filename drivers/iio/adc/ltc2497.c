<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ltc2497.c - Driver क्रम Analog Devices/Linear Technology LTC2497 ADC
 *
 * Copyright (C) 2017 Analog Devices Inc.
 *
 * Datasheet: http://cds.linear.com/करोcs/en/datasheet/2497fd.pdf
 */

#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>

#समावेश "ltc2497.h"

काष्ठा ltc2497_driverdata अणु
	/* this must be the first member */
	काष्ठा ltc2497core_driverdata common_ddata;
	काष्ठा i2c_client *client;
	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	__be32 buf ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक ltc2497_result_and_measure(काष्ठा ltc2497core_driverdata *ddata,
				      u8 address, पूर्णांक *val)
अणु
	काष्ठा ltc2497_driverdata *st =
		container_of(ddata, काष्ठा ltc2497_driverdata, common_ddata);
	पूर्णांक ret;

	अगर (val) अणु
		ret = i2c_master_recv(st->client, (अक्षर *)&st->buf, 3);
		अगर (ret < 0) अणु
			dev_err(&st->client->dev, "i2c_master_recv failed\n");
			वापस ret;
		पूर्ण

		*val = (be32_to_cpu(st->buf) >> 14) - (1 << 17);
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte(st->client,
				   LTC2497_ENABLE | address);
	अगर (ret)
		dev_err(&st->client->dev, "i2c transfer failed: %pe\n",
			ERR_PTR(ret));
	वापस ret;
पूर्ण

अटल पूर्णांक ltc2497_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ltc2497_driverdata *st;
	काष्ठा device *dev = &client->dev;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_WRITE_BYTE))
		वापस -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	st->client = client;
	st->common_ddata.result_and_measure = ltc2497_result_and_measure;

	वापस ltc2497core_probe(dev, indio_dev);
पूर्ण

अटल पूर्णांक ltc2497_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	ltc2497core_हटाओ(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc2497_id[] = अणु
	अणु "ltc2497", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc2497_id);

अटल स्थिर काष्ठा of_device_id ltc2497_of_match[] = अणु
	अणु .compatible = "lltc,ltc2497", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc2497_of_match);

अटल काष्ठा i2c_driver ltc2497_driver = अणु
	.driver = अणु
		.name = "ltc2497",
		.of_match_table = ltc2497_of_match,
	पूर्ण,
	.probe = ltc2497_probe,
	.हटाओ = ltc2497_हटाओ,
	.id_table = ltc2497_id,
पूर्ण;
module_i2c_driver(ltc2497_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Linear Technology LTC2497 ADC driver");
MODULE_LICENSE("GPL v2");
