<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ADE7854/58/68/78 Polyphase Multअगरunction Energy Metering IC Driver (I2C Bus)
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश "ade7854.h"

अटल पूर्णांक ade7854_i2c_ग_लिखो_reg(काष्ठा device *dev,
				 u16 reg_address,
				 u32 val,
				 पूर्णांक bits)
अणु
	पूर्णांक ret;
	पूर्णांक count;
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);

	mutex_lock(&st->buf_lock);
	st->tx[0] = (reg_address >> 8) & 0xFF;
	st->tx[1] = reg_address & 0xFF;

	चयन (bits) अणु
	हाल 8:
		st->tx[2] = val & 0xFF;
		count = 3;
		अवरोध;
	हाल 16:
		st->tx[2] = (val >> 8) & 0xFF;
		st->tx[3] = val & 0xFF;
		count = 4;
		अवरोध;
	हाल 24:
		st->tx[2] = (val >> 16) & 0xFF;
		st->tx[3] = (val >> 8) & 0xFF;
		st->tx[4] = val & 0xFF;
		count = 5;
		अवरोध;
	हाल 32:
		st->tx[2] = (val >> 24) & 0xFF;
		st->tx[3] = (val >> 16) & 0xFF;
		st->tx[4] = (val >> 8) & 0xFF;
		st->tx[5] = val & 0xFF;
		count = 6;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	ret = i2c_master_send(st->i2c, st->tx, count);

unlock:
	mutex_unlock(&st->buf_lock);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक ade7854_i2c_पढ़ो_reg(काष्ठा device *dev,
				u16 reg_address,
				u32 *val,
				पूर्णांक bits)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->buf_lock);
	st->tx[0] = (reg_address >> 8) & 0xFF;
	st->tx[1] = reg_address & 0xFF;

	ret = i2c_master_send(st->i2c, st->tx, 2);
	अगर (ret < 0)
		जाओ unlock;

	ret = i2c_master_recv(st->i2c, st->rx, bits);
	अगर (ret < 0)
		जाओ unlock;

	चयन (bits) अणु
	हाल 8:
		*val = st->rx[0];
		अवरोध;
	हाल 16:
		*val = (st->rx[0] << 8) | st->rx[1];
		अवरोध;
	हाल 24:
		*val = (st->rx[0] << 16) | (st->rx[1] << 8) | st->rx[2];
		अवरोध;
	हाल 32:
		*val = (st->rx[0] << 24) | (st->rx[1] << 16) |
			(st->rx[2] << 8) | st->rx[3];
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

unlock:
	mutex_unlock(&st->buf_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ade7854_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ade7854_state *st;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;
	st = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	st->पढ़ो_reg = ade7854_i2c_पढ़ो_reg;
	st->ग_लिखो_reg = ade7854_i2c_ग_लिखो_reg;
	st->i2c = client;
	st->irq = client->irq;

	वापस ade7854_probe(indio_dev, &client->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ade7854_id[] = अणु
	अणु "ade7854", 0 पूर्ण,
	अणु "ade7858", 0 पूर्ण,
	अणु "ade7868", 0 पूर्ण,
	अणु "ade7878", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ade7854_id);

अटल काष्ठा i2c_driver ade7854_i2c_driver = अणु
	.driver = अणु
		.name = "ade7854",
	पूर्ण,
	.probe    = ade7854_i2c_probe,
	.id_table = ade7854_id,
पूर्ण;
module_i2c_driver(ade7854_i2c_driver);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ADE7854/58/68/78 Polyphase Multifunction Energy Metering IC I2C Driver");
MODULE_LICENSE("GPL v2");
