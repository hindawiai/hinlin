<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम PCA9570 I2C GPO expander
 *
 * Copyright (C) 2020 Sungbo Eo <mans0n@gorani.run>
 *
 * Based on gpio-tpic2810.c
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/property.h>

/**
 * काष्ठा pca9570 - GPIO driver data
 * @chip: GPIO controller chip
 * @lock: Protects ग_लिखो sequences
 * @out: Buffer क्रम device रेजिस्टर
 */
काष्ठा pca9570 अणु
	काष्ठा gpio_chip chip;
	काष्ठा mutex lock;
	u8 out;
पूर्ण;

अटल पूर्णांक pca9570_पढ़ो(काष्ठा pca9570 *gpio, u8 *value)
अणु
	काष्ठा i2c_client *client = to_i2c_client(gpio->chip.parent);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte(client);
	अगर (ret < 0)
		वापस ret;

	*value = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक pca9570_ग_लिखो(काष्ठा pca9570 *gpio, u8 value)
अणु
	काष्ठा i2c_client *client = to_i2c_client(gpio->chip.parent);

	वापस i2c_smbus_ग_लिखो_byte(client, value);
पूर्ण

अटल पूर्णांक pca9570_get_direction(काष्ठा gpio_chip *chip,
				 अचिन्हित offset)
अणु
	/* This device always output */
	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक pca9570_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा pca9570 *gpio = gpiochip_get_data(chip);
	u8 buffer;
	पूर्णांक ret;

	ret = pca9570_पढ़ो(gpio, &buffer);
	अगर (ret)
		वापस ret;

	वापस !!(buffer & BIT(offset));
पूर्ण

अटल व्योम pca9570_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा pca9570 *gpio = gpiochip_get_data(chip);
	u8 buffer;
	पूर्णांक ret;

	mutex_lock(&gpio->lock);

	buffer = gpio->out;
	अगर (value)
		buffer |= BIT(offset);
	अन्यथा
		buffer &= ~BIT(offset);

	ret = pca9570_ग_लिखो(gpio, buffer);
	अगर (ret)
		जाओ out;

	gpio->out = buffer;

out:
	mutex_unlock(&gpio->lock);
पूर्ण

अटल पूर्णांक pca9570_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा pca9570 *gpio;

	gpio = devm_kzalloc(&client->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	gpio->chip.label = client->name;
	gpio->chip.parent = &client->dev;
	gpio->chip.owner = THIS_MODULE;
	gpio->chip.get_direction = pca9570_get_direction;
	gpio->chip.get = pca9570_get;
	gpio->chip.set = pca9570_set;
	gpio->chip.base = -1;
	gpio->chip.ngpio = (uपूर्णांकptr_t)device_get_match_data(&client->dev);
	gpio->chip.can_sleep = true;

	mutex_init(&gpio->lock);

	/* Read the current output level */
	pca9570_पढ़ो(gpio, &gpio->out);

	i2c_set_clientdata(client, gpio);

	वापस devm_gpiochip_add_data(&client->dev, &gpio->chip, gpio);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pca9570_id_table[] = अणु
	अणु "pca9570", 4 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pca9570_id_table);

अटल स्थिर काष्ठा of_device_id pca9570_of_match_table[] = अणु
	अणु .compatible = "nxp,pca9570", .data = (व्योम *)4 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pca9570_of_match_table);

अटल काष्ठा i2c_driver pca9570_driver = अणु
	.driver = अणु
		.name = "pca9570",
		.of_match_table = pca9570_of_match_table,
	पूर्ण,
	.probe_new = pca9570_probe,
	.id_table = pca9570_id_table,
पूर्ण;
module_i2c_driver(pca9570_driver);

MODULE_AUTHOR("Sungbo Eo <mans0n@gorani.run>");
MODULE_DESCRIPTION("GPIO expander driver for PCA9570");
MODULE_LICENSE("GPL v2");
