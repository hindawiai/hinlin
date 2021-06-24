<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  74Hx164 - Generic serial-in/parallel-out 8-bits shअगरt रेजिस्टर GPIO driver
 *
 *  Copyright (C) 2010 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2010 Miguel Gaio <miguel.gaio@efixo.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>

#घोषणा GEN_74X164_NUMBER_GPIOS	8

काष्ठा gen_74x164_chip अणु
	काष्ठा gpio_chip	gpio_chip;
	काष्ठा mutex		lock;
	काष्ठा gpio_desc	*gpiod_oe;
	u32			रेजिस्टरs;
	/*
	 * Since the रेजिस्टरs are chained, every byte sent will make
	 * the previous byte shअगरt to the next रेजिस्टर in the
	 * chain. Thus, the first byte sent will end up in the last
	 * रेजिस्टर at the end of the transfer. So, to have a logical
	 * numbering, store the bytes in reverse order.
	 */
	u8			buffer[];
पूर्ण;

अटल पूर्णांक __gen_74x164_ग_लिखो_config(काष्ठा gen_74x164_chip *chip)
अणु
	वापस spi_ग_लिखो(to_spi_device(chip->gpio_chip.parent), chip->buffer,
			 chip->रेजिस्टरs);
पूर्ण

अटल पूर्णांक gen_74x164_get_value(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा gen_74x164_chip *chip = gpiochip_get_data(gc);
	u8 bank = chip->रेजिस्टरs - 1 - offset / 8;
	u8 pin = offset % 8;
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	ret = (chip->buffer[bank] >> pin) & 0x1;
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल व्योम gen_74x164_set_value(काष्ठा gpio_chip *gc,
		अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा gen_74x164_chip *chip = gpiochip_get_data(gc);
	u8 bank = chip->रेजिस्टरs - 1 - offset / 8;
	u8 pin = offset % 8;

	mutex_lock(&chip->lock);
	अगर (val)
		chip->buffer[bank] |= (1 << pin);
	अन्यथा
		chip->buffer[bank] &= ~(1 << pin);

	__gen_74x164_ग_लिखो_config(chip);
	mutex_unlock(&chip->lock);
पूर्ण

अटल व्योम gen_74x164_set_multiple(काष्ठा gpio_chip *gc, अचिन्हित दीर्घ *mask,
				    अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gen_74x164_chip *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ bankmask;
	माप_प्रकार bank;
	अचिन्हित दीर्घ biपंचांगask;

	mutex_lock(&chip->lock);
	क्रम_each_set_clump8(offset, bankmask, mask, chip->रेजिस्टरs * 8) अणु
		bank = chip->रेजिस्टरs - 1 - offset / 8;
		biपंचांगask = biपंचांगap_get_value8(bits, offset) & bankmask;

		chip->buffer[bank] &= ~bankmask;
		chip->buffer[bank] |= biपंचांगask;
	पूर्ण
	__gen_74x164_ग_लिखो_config(chip);
	mutex_unlock(&chip->lock);
पूर्ण

अटल पूर्णांक gen_74x164_direction_output(काष्ठा gpio_chip *gc,
		अचिन्हित offset, पूर्णांक val)
अणु
	gen_74x164_set_value(gc, offset, val);
	वापस 0;
पूर्ण

अटल पूर्णांक gen_74x164_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा gen_74x164_chip *chip;
	u32 nregs;
	पूर्णांक ret;

	/*
	 * bits_per_word cannot be configured in platक्रमm data
	 */
	spi->bits_per_word = 8;

	ret = spi_setup(spi);
	अगर (ret < 0)
		वापस ret;

	ret = device_property_पढ़ो_u32(&spi->dev, "registers-number", &nregs);
	अगर (ret) अणु
		dev_err(&spi->dev, "Missing 'registers-number' property.\n");
		वापस -EINVAL;
	पूर्ण

	chip = devm_kzalloc(&spi->dev, माप(*chip) + nregs, GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->gpiod_oe = devm_gpiod_get_optional(&spi->dev, "enable",
						 GPIOD_OUT_LOW);
	अगर (IS_ERR(chip->gpiod_oe))
		वापस PTR_ERR(chip->gpiod_oe);

	gpiod_set_value_cansleep(chip->gpiod_oe, 1);

	spi_set_drvdata(spi, chip);

	chip->gpio_chip.label = spi->modalias;
	chip->gpio_chip.direction_output = gen_74x164_direction_output;
	chip->gpio_chip.get = gen_74x164_get_value;
	chip->gpio_chip.set = gen_74x164_set_value;
	chip->gpio_chip.set_multiple = gen_74x164_set_multiple;
	chip->gpio_chip.base = -1;

	chip->रेजिस्टरs = nregs;
	chip->gpio_chip.ngpio = GEN_74X164_NUMBER_GPIOS * chip->रेजिस्टरs;

	chip->gpio_chip.can_sleep = true;
	chip->gpio_chip.parent = &spi->dev;
	chip->gpio_chip.owner = THIS_MODULE;

	mutex_init(&chip->lock);

	ret = __gen_74x164_ग_लिखो_config(chip);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed writing: %d\n", ret);
		जाओ निकास_destroy;
	पूर्ण

	ret = gpiochip_add_data(&chip->gpio_chip, chip);
	अगर (!ret)
		वापस 0;

निकास_destroy:
	mutex_destroy(&chip->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक gen_74x164_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा gen_74x164_chip *chip = spi_get_drvdata(spi);

	gpiod_set_value_cansleep(chip->gpiod_oe, 0);
	gpiochip_हटाओ(&chip->gpio_chip);
	mutex_destroy(&chip->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gen_74x164_dt_ids[] = अणु
	अणु .compatible = "fairchild,74hc595" पूर्ण,
	अणु .compatible = "nxp,74lvc594" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gen_74x164_dt_ids);

अटल काष्ठा spi_driver gen_74x164_driver = अणु
	.driver = अणु
		.name		= "74x164",
		.of_match_table	= gen_74x164_dt_ids,
	पूर्ण,
	.probe		= gen_74x164_probe,
	.हटाओ		= gen_74x164_हटाओ,
पूर्ण;
module_spi_driver(gen_74x164_driver);

MODULE_AUTHOR("Gabor Juhos <juhosg@openwrt.org>");
MODULE_AUTHOR("Miguel Gaio <miguel.gaio@efixo.com>");
MODULE_DESCRIPTION("GPIO expander driver for 74X164 8-bits shift register");
MODULE_LICENSE("GPL v2");
