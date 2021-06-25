<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010-2013 Bluecherry, LLC <https://www.bluecherrydvr.com>
 *
 * Original author:
 * Ben Collins <bcollins@ubuntu.com>
 *
 * Additional work by:
 * John Brooks <john.brooks@bluecherry.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>

#समावेश "solo6x10.h"

अटल व्योम solo_gpio_mode(काष्ठा solo_dev *solo_dev,
			   अचिन्हित पूर्णांक port_mask, अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक port;
	अचिन्हित पूर्णांक ret;

	ret = solo_reg_पढ़ो(solo_dev, SOLO_GPIO_CONFIG_0);

	/* To set gpio */
	क्रम (port = 0; port < 16; port++) अणु
		अगर (!((1 << port) & port_mask))
			जारी;

		ret &= (~(3 << (port << 1)));
		ret |= ((mode & 3) << (port << 1));
	पूर्ण

	solo_reg_ग_लिखो(solo_dev, SOLO_GPIO_CONFIG_0, ret);

	/* To set extended gpio - sensor */
	ret = solo_reg_पढ़ो(solo_dev, SOLO_GPIO_CONFIG_1);

	क्रम (port = 0; port < 16; port++) अणु
		अगर (!((1UL << (port + 16)) & port_mask))
			जारी;

		अगर (!mode)
			ret &= ~(1UL << port);
		अन्यथा
			ret |= 1UL << port;
	पूर्ण

	/* Enable GPIO[31:16] */
	ret |= 0xffff0000;

	solo_reg_ग_लिखो(solo_dev, SOLO_GPIO_CONFIG_1, ret);
पूर्ण

अटल व्योम solo_gpio_set(काष्ठा solo_dev *solo_dev, अचिन्हित पूर्णांक value)
अणु
	solo_reg_ग_लिखो(solo_dev, SOLO_GPIO_DATA_OUT,
		       solo_reg_पढ़ो(solo_dev, SOLO_GPIO_DATA_OUT) | value);
पूर्ण

अटल व्योम solo_gpio_clear(काष्ठा solo_dev *solo_dev, अचिन्हित पूर्णांक value)
अणु
	solo_reg_ग_लिखो(solo_dev, SOLO_GPIO_DATA_OUT,
		       solo_reg_पढ़ो(solo_dev, SOLO_GPIO_DATA_OUT) & ~value);
पूर्ण

अटल व्योम solo_gpio_config(काष्ठा solo_dev *solo_dev)
अणु
	/* Video reset */
	solo_gpio_mode(solo_dev, 0x30, 1);
	solo_gpio_clear(solo_dev, 0x30);
	udelay(100);
	solo_gpio_set(solo_dev, 0x30);
	udelay(100);

	/* Warning: Don't touch the next line unless you're sure of what
	 * you're करोing: first four gpio [0-3] are used क्रम video. */
	solo_gpio_mode(solo_dev, 0x0f, 2);

	/* We use bit 8-15 of SOLO_GPIO_CONFIG_0 क्रम relay purposes */
	solo_gpio_mode(solo_dev, 0xff00, 1);

	/* Initially set relay status to 0 */
	solo_gpio_clear(solo_dev, 0xff00);

	/* Set input pins direction */
	solo_gpio_mode(solo_dev, 0xffff0000, 0);
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
/* Pins 0-7 are not exported, because it seems from code above they are
 * used क्रम पूर्णांकernal purposes. So offset 0 corresponds to pin 8, thereक्रमe
 * offsets 0-7 are relay GPIOs, 8-23 - input GPIOs.
 */
अटल पूर्णांक solo_gpiochip_get_direction(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret, mode;
	काष्ठा solo_dev *solo_dev = gpiochip_get_data(chip);

	अगर (offset < 8) अणु
		ret = solo_reg_पढ़ो(solo_dev, SOLO_GPIO_CONFIG_0);
		mode = 3 & (ret >> ((offset + 8) * 2));
	पूर्ण अन्यथा अणु
		ret = solo_reg_पढ़ो(solo_dev, SOLO_GPIO_CONFIG_1);
		mode =  1 & (ret >> (offset - 8));
	पूर्ण

	अगर (!mode)
		वापस 1;
	अन्यथा अगर (mode == 1)
		वापस 0;

	वापस -1;
पूर्ण

अटल पूर्णांक solo_gpiochip_direction_input(काष्ठा gpio_chip *chip,
					 अचिन्हित पूर्णांक offset)
अणु
	वापस -1;
पूर्ण

अटल पूर्णांक solo_gpiochip_direction_output(काष्ठा gpio_chip *chip,
					  अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	वापस -1;
पूर्ण

अटल पूर्णांक solo_gpiochip_get(काष्ठा gpio_chip *chip,
						अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	काष्ठा solo_dev *solo_dev = gpiochip_get_data(chip);

	ret = solo_reg_पढ़ो(solo_dev, SOLO_GPIO_DATA_IN);

	वापस 1 & (ret >> (offset + 8));
पूर्ण

अटल व्योम solo_gpiochip_set(काष्ठा gpio_chip *chip,
						अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा solo_dev *solo_dev = gpiochip_get_data(chip);

	अगर (value)
		solo_gpio_set(solo_dev, 1 << (offset + 8));
	अन्यथा
		solo_gpio_clear(solo_dev, 1 << (offset + 8));
पूर्ण
#पूर्ण_अगर

पूर्णांक solo_gpio_init(काष्ठा solo_dev *solo_dev)
अणु
#अगर_घोषित CONFIG_GPIOLIB
	पूर्णांक ret;
#पूर्ण_अगर

	solo_gpio_config(solo_dev);
#अगर_घोषित CONFIG_GPIOLIB
	solo_dev->gpio_dev.label = SOLO6X10_NAME"_gpio";
	solo_dev->gpio_dev.parent = &solo_dev->pdev->dev;
	solo_dev->gpio_dev.owner = THIS_MODULE;
	solo_dev->gpio_dev.base = -1;
	solo_dev->gpio_dev.ngpio = 24;
	solo_dev->gpio_dev.can_sleep = 0;

	solo_dev->gpio_dev.get_direction = solo_gpiochip_get_direction;
	solo_dev->gpio_dev.direction_input = solo_gpiochip_direction_input;
	solo_dev->gpio_dev.direction_output = solo_gpiochip_direction_output;
	solo_dev->gpio_dev.get = solo_gpiochip_get;
	solo_dev->gpio_dev.set = solo_gpiochip_set;

	ret = gpiochip_add_data(&solo_dev->gpio_dev, solo_dev);

	अगर (ret) अणु
		solo_dev->gpio_dev.label = शून्य;
		वापस -1;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम solo_gpio_निकास(काष्ठा solo_dev *solo_dev)
अणु
#अगर_घोषित CONFIG_GPIOLIB
	अगर (solo_dev->gpio_dev.label) अणु
		gpiochip_हटाओ(&solo_dev->gpio_dev);
		solo_dev->gpio_dev.label = शून्य;
	पूर्ण
#पूर्ण_अगर
	solo_gpio_clear(solo_dev, 0x30);
	solo_gpio_config(solo_dev);
पूर्ण
