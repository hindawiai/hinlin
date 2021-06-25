<शैली गुरु>
/*
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether expressed or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 क्रम more details.
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#घोषणा TPIC2810_WS_COMMAND 0x44

/**
 * काष्ठा tpic2810 - GPIO driver data
 * @chip: GPIO controller chip
 * @client: I2C device poपूर्णांकer
 * @buffer: Buffer क्रम device रेजिस्टर
 * @lock: Protects ग_लिखो sequences
 */
काष्ठा tpic2810 अणु
	काष्ठा gpio_chip chip;
	काष्ठा i2c_client *client;
	u8 buffer;
	काष्ठा mutex lock;
पूर्ण;

अटल व्योम tpic2810_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value);

अटल पूर्णांक tpic2810_get_direction(काष्ठा gpio_chip *chip,
				  अचिन्हित offset)
अणु
	/* This device always output */
	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक tpic2810_direction_input(काष्ठा gpio_chip *chip,
				    अचिन्हित offset)
अणु
	/* This device is output only */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tpic2810_direction_output(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value)
अणु
	/* This device always output */
	tpic2810_set(chip, offset, value);
	वापस 0;
पूर्ण

अटल व्योम tpic2810_set_mask_bits(काष्ठा gpio_chip *chip, u8 mask, u8 bits)
अणु
	काष्ठा tpic2810 *gpio = gpiochip_get_data(chip);
	u8 buffer;
	पूर्णांक err;

	mutex_lock(&gpio->lock);

	buffer = gpio->buffer & ~mask;
	buffer |= (mask & bits);

	err = i2c_smbus_ग_लिखो_byte_data(gpio->client, TPIC2810_WS_COMMAND,
					buffer);
	अगर (!err)
		gpio->buffer = buffer;

	mutex_unlock(&gpio->lock);
पूर्ण

अटल व्योम tpic2810_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	tpic2810_set_mask_bits(chip, BIT(offset), value ? BIT(offset) : 0);
पूर्ण

अटल व्योम tpic2810_set_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
				  अचिन्हित दीर्घ *bits)
अणु
	tpic2810_set_mask_bits(chip, *mask, *bits);
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "tpic2810",
	.owner			= THIS_MODULE,
	.get_direction		= tpic2810_get_direction,
	.direction_input	= tpic2810_direction_input,
	.direction_output	= tpic2810_direction_output,
	.set			= tpic2810_set,
	.set_multiple		= tpic2810_set_multiple,
	.base			= -1,
	.ngpio			= 8,
	.can_sleep		= true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tpic2810_of_match_table[] = अणु
	अणु .compatible = "ti,tpic2810" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tpic2810_of_match_table);

अटल पूर्णांक tpic2810_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tpic2810 *gpio;
	पूर्णांक ret;

	gpio = devm_kzalloc(&client->dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	i2c_set_clientdata(client, gpio);

	gpio->chip = ढाँचा_chip;
	gpio->chip.parent = &client->dev;

	gpio->client = client;

	mutex_init(&gpio->lock);

	ret = gpiochip_add_data(&gpio->chip, gpio);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Unable to register gpiochip\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tpic2810_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tpic2810 *gpio = i2c_get_clientdata(client);

	gpiochip_हटाओ(&gpio->chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tpic2810_id_table[] = अणु
	अणु "tpic2810", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tpic2810_id_table);

अटल काष्ठा i2c_driver tpic2810_driver = अणु
	.driver = अणु
		.name = "tpic2810",
		.of_match_table = tpic2810_of_match_table,
	पूर्ण,
	.probe = tpic2810_probe,
	.हटाओ = tpic2810_हटाओ,
	.id_table = tpic2810_id_table,
पूर्ण;
module_i2c_driver(tpic2810_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("TPIC2810 8-Bit LED Driver GPIO Driver");
MODULE_LICENSE("GPL v2");
