<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AD714X CapTouch Programmable Controller driver (I2C bus)
 *
 * Copyright 2009-2011 Analog Devices Inc.
 */

#समावेश <linux/input.h>	/* BUS_I2C */
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pm.h>
#समावेश "ad714x.h"

अटल पूर्णांक __maybe_unused ad714x_i2c_suspend(काष्ठा device *dev)
अणु
	वापस ad714x_disable(i2c_get_clientdata(to_i2c_client(dev)));
पूर्ण

अटल पूर्णांक __maybe_unused ad714x_i2c_resume(काष्ठा device *dev)
अणु
	वापस ad714x_enable(i2c_get_clientdata(to_i2c_client(dev)));
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ad714x_i2c_pm, ad714x_i2c_suspend, ad714x_i2c_resume);

अटल पूर्णांक ad714x_i2c_ग_लिखो(काष्ठा ad714x_chip *chip,
			    अचिन्हित लघु reg, अचिन्हित लघु data)
अणु
	काष्ठा i2c_client *client = to_i2c_client(chip->dev);
	पूर्णांक error;

	chip->xfer_buf[0] = cpu_to_be16(reg);
	chip->xfer_buf[1] = cpu_to_be16(data);

	error = i2c_master_send(client, (u8 *)chip->xfer_buf,
				2 * माप(*chip->xfer_buf));
	अगर (unlikely(error < 0)) अणु
		dev_err(&client->dev, "I2C write error: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad714x_i2c_पढ़ो(काष्ठा ad714x_chip *chip,
			   अचिन्हित लघु reg, अचिन्हित लघु *data, माप_प्रकार len)
अणु
	काष्ठा i2c_client *client = to_i2c_client(chip->dev);
	पूर्णांक i;
	पूर्णांक error;

	chip->xfer_buf[0] = cpu_to_be16(reg);

	error = i2c_master_send(client, (u8 *)chip->xfer_buf,
				माप(*chip->xfer_buf));
	अगर (error >= 0)
		error = i2c_master_recv(client, (u8 *)chip->xfer_buf,
					len * माप(*chip->xfer_buf));

	अगर (unlikely(error < 0)) अणु
		dev_err(&client->dev, "I2C read error: %d\n", error);
		वापस error;
	पूर्ण

	क्रम (i = 0; i < len; i++)
		data[i] = be16_to_cpu(chip->xfer_buf[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक ad714x_i2c_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ad714x_chip *chip;

	chip = ad714x_probe(&client->dev, BUS_I2C, client->irq,
			    ad714x_i2c_पढ़ो, ad714x_i2c_ग_लिखो);
	अगर (IS_ERR(chip))
		वापस PTR_ERR(chip);

	i2c_set_clientdata(client, chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad714x_id[] = अणु
	अणु "ad7142_captouch", 0 पूर्ण,
	अणु "ad7143_captouch", 0 पूर्ण,
	अणु "ad7147_captouch", 0 पूर्ण,
	अणु "ad7147a_captouch", 0 पूर्ण,
	अणु "ad7148_captouch", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad714x_id);

अटल काष्ठा i2c_driver ad714x_i2c_driver = अणु
	.driver = अणु
		.name = "ad714x_captouch",
		.pm   = &ad714x_i2c_pm,
	पूर्ण,
	.probe    = ad714x_i2c_probe,
	.id_table = ad714x_id,
पूर्ण;

module_i2c_driver(ad714x_i2c_driver);

MODULE_DESCRIPTION("Analog Devices AD714X Capacitance Touch Sensor I2C Bus Driver");
MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_LICENSE("GPL");
