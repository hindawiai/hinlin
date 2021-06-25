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

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spi/spi.h>

#घोषणा DEFAULT_NGPIO 8

/**
 * काष्ठा pisosr_gpio - GPIO driver data
 * @chip: GPIO controller chip
 * @spi: SPI device poपूर्णांकer
 * @buffer: Buffer क्रम device पढ़ोs
 * @buffer_size: Size of buffer
 * @load_gpio: GPIO pin used to load input पूर्णांकo device
 * @lock: Protects पढ़ो sequences
 */
काष्ठा pisosr_gpio अणु
	काष्ठा gpio_chip chip;
	काष्ठा spi_device *spi;
	u8 *buffer;
	माप_प्रकार buffer_size;
	काष्ठा gpio_desc *load_gpio;
	काष्ठा mutex lock;
पूर्ण;

अटल पूर्णांक pisosr_gpio_refresh(काष्ठा pisosr_gpio *gpio)
अणु
	पूर्णांक ret;

	mutex_lock(&gpio->lock);

	अगर (gpio->load_gpio) अणु
		gpiod_set_value_cansleep(gpio->load_gpio, 1);
		udelay(1); /* रेजिस्टरs load समय (~10ns) */
		gpiod_set_value_cansleep(gpio->load_gpio, 0);
		udelay(1); /* रेजिस्टरs recovery समय (~5ns) */
	पूर्ण

	ret = spi_पढ़ो(gpio->spi, gpio->buffer, gpio->buffer_size);

	mutex_unlock(&gpio->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pisosr_gpio_get_direction(काष्ठा gpio_chip *chip,
				     अचिन्हित offset)
अणु
	/* This device always input */
	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक pisosr_gpio_direction_input(काष्ठा gpio_chip *chip,
				       अचिन्हित offset)
अणु
	/* This device always input */
	वापस 0;
पूर्ण

अटल पूर्णांक pisosr_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset, पूर्णांक value)
अणु
	/* This device is input only */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pisosr_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा pisosr_gpio *gpio = gpiochip_get_data(chip);

	/* Refresh may not always be needed */
	pisosr_gpio_refresh(gpio);

	वापस (gpio->buffer[offset / 8] >> (offset % 8)) & 0x1;
पूर्ण

अटल पूर्णांक pisosr_gpio_get_multiple(काष्ठा gpio_chip *chip,
				    अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा pisosr_gpio *gpio = gpiochip_get_data(chip);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ gpio_mask;
	अचिन्हित दीर्घ buffer_state;

	pisosr_gpio_refresh(gpio);

	biपंचांगap_zero(bits, chip->ngpio);
	क्रम_each_set_clump8(offset, gpio_mask, mask, chip->ngpio) अणु
		buffer_state = gpio->buffer[offset / 8] & gpio_mask;
		biपंचांगap_set_value8(bits, buffer_state, offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "pisosr-gpio",
	.owner			= THIS_MODULE,
	.get_direction		= pisosr_gpio_get_direction,
	.direction_input	= pisosr_gpio_direction_input,
	.direction_output	= pisosr_gpio_direction_output,
	.get			= pisosr_gpio_get,
	.get_multiple		= pisosr_gpio_get_multiple,
	.base			= -1,
	.ngpio			= DEFAULT_NGPIO,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक pisosr_gpio_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा pisosr_gpio *gpio;
	पूर्णांक ret;

	gpio = devm_kzalloc(dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	spi_set_drvdata(spi, gpio);

	gpio->chip = ढाँचा_chip;
	gpio->chip.parent = dev;
	of_property_पढ़ो_u16(dev->of_node, "ngpios", &gpio->chip.ngpio);

	gpio->spi = spi;

	gpio->buffer_size = DIV_ROUND_UP(gpio->chip.ngpio, 8);
	gpio->buffer = devm_kzalloc(dev, gpio->buffer_size, GFP_KERNEL);
	अगर (!gpio->buffer)
		वापस -ENOMEM;

	gpio->load_gpio = devm_gpiod_get_optional(dev, "load", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio->load_gpio))
		वापस dev_err_probe(dev, PTR_ERR(gpio->load_gpio),
				     "Unable to allocate load GPIO\n");

	mutex_init(&gpio->lock);

	ret = gpiochip_add_data(&gpio->chip, gpio);
	अगर (ret < 0) अणु
		dev_err(dev, "Unable to register gpiochip\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pisosr_gpio_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा pisosr_gpio *gpio = spi_get_drvdata(spi);

	gpiochip_हटाओ(&gpio->chip);

	mutex_destroy(&gpio->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id pisosr_gpio_id_table[] = अणु
	अणु "pisosr-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, pisosr_gpio_id_table);

अटल स्थिर काष्ठा of_device_id pisosr_gpio_of_match_table[] = अणु
	अणु .compatible = "pisosr-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pisosr_gpio_of_match_table);

अटल काष्ठा spi_driver pisosr_gpio_driver = अणु
	.driver = अणु
		.name = "pisosr-gpio",
		.of_match_table = pisosr_gpio_of_match_table,
	पूर्ण,
	.probe = pisosr_gpio_probe,
	.हटाओ = pisosr_gpio_हटाओ,
	.id_table = pisosr_gpio_id_table,
पूर्ण;
module_spi_driver(pisosr_gpio_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("SPI Compatible PISO Shift Register GPIO Driver");
MODULE_LICENSE("GPL v2");
