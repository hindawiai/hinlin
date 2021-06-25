<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kontron PLD GPIO driver
 *
 * Copyright (c) 2010-2013 Kontron Europe GmbH
 * Author: Michael Brunner <michael.brunner@kontron.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/mfd/kempld.h>

#घोषणा KEMPLD_GPIO_MAX_NUM		16
#घोषणा KEMPLD_GPIO_MASK(x)		(BIT((x) % 8))
#घोषणा KEMPLD_GPIO_सूची_NUM(x)		(0x40 + (x) / 8)
#घोषणा KEMPLD_GPIO_LVL_NUM(x)		(0x42 + (x) / 8)
#घोषणा KEMPLD_GPIO_EVT_LVL_EDGE	0x46
#घोषणा KEMPLD_GPIO_IEN			0x4A

काष्ठा kempld_gpio_data अणु
	काष्ठा gpio_chip		chip;
	काष्ठा kempld_device_data	*pld;
पूर्ण;

/*
 * Set or clear GPIO bit
 * kempld_get_mutex must be called prior to calling this function.
 */
अटल व्योम kempld_gpio_bitop(काष्ठा kempld_device_data *pld,
			      u8 reg, u8 bit, u8 val)
अणु
	u8 status;

	status = kempld_पढ़ो8(pld, reg);
	अगर (val)
		status |= KEMPLD_GPIO_MASK(bit);
	अन्यथा
		status &= ~KEMPLD_GPIO_MASK(bit);
	kempld_ग_लिखो8(pld, reg, status);
पूर्ण

अटल पूर्णांक kempld_gpio_get_bit(काष्ठा kempld_device_data *pld, u8 reg, u8 bit)
अणु
	u8 status;

	kempld_get_mutex(pld);
	status = kempld_पढ़ो8(pld, reg);
	kempld_release_mutex(pld);

	वापस !!(status & KEMPLD_GPIO_MASK(bit));
पूर्ण

अटल पूर्णांक kempld_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा kempld_gpio_data *gpio = gpiochip_get_data(chip);
	काष्ठा kempld_device_data *pld = gpio->pld;

	वापस !!kempld_gpio_get_bit(pld, KEMPLD_GPIO_LVL_NUM(offset), offset);
पूर्ण

अटल व्योम kempld_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा kempld_gpio_data *gpio = gpiochip_get_data(chip);
	काष्ठा kempld_device_data *pld = gpio->pld;

	kempld_get_mutex(pld);
	kempld_gpio_bitop(pld, KEMPLD_GPIO_LVL_NUM(offset), offset, value);
	kempld_release_mutex(pld);
पूर्ण

अटल पूर्णांक kempld_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा kempld_gpio_data *gpio = gpiochip_get_data(chip);
	काष्ठा kempld_device_data *pld = gpio->pld;

	kempld_get_mutex(pld);
	kempld_gpio_bitop(pld, KEMPLD_GPIO_सूची_NUM(offset), offset, 0);
	kempld_release_mutex(pld);

	वापस 0;
पूर्ण

अटल पूर्णांक kempld_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
					पूर्णांक value)
अणु
	काष्ठा kempld_gpio_data *gpio = gpiochip_get_data(chip);
	काष्ठा kempld_device_data *pld = gpio->pld;

	kempld_get_mutex(pld);
	kempld_gpio_bitop(pld, KEMPLD_GPIO_LVL_NUM(offset), offset, value);
	kempld_gpio_bitop(pld, KEMPLD_GPIO_सूची_NUM(offset), offset, 1);
	kempld_release_mutex(pld);

	वापस 0;
पूर्ण

अटल पूर्णांक kempld_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा kempld_gpio_data *gpio = gpiochip_get_data(chip);
	काष्ठा kempld_device_data *pld = gpio->pld;

	अगर (kempld_gpio_get_bit(pld, KEMPLD_GPIO_सूची_NUM(offset), offset))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक kempld_gpio_pincount(काष्ठा kempld_device_data *pld)
अणु
	u16 evt, evt_back;

	kempld_get_mutex(pld);

	/* Backup event रेजिस्टर as it might be alपढ़ोy initialized */
	evt_back = kempld_पढ़ो16(pld, KEMPLD_GPIO_EVT_LVL_EDGE);
	/* Clear event रेजिस्टर */
	kempld_ग_लिखो16(pld, KEMPLD_GPIO_EVT_LVL_EDGE, 0x0000);
	/* Read back event रेजिस्टर */
	evt = kempld_पढ़ो16(pld, KEMPLD_GPIO_EVT_LVL_EDGE);
	/* Restore event रेजिस्टर */
	kempld_ग_लिखो16(pld, KEMPLD_GPIO_EVT_LVL_EDGE, evt_back);

	kempld_release_mutex(pld);

	वापस evt ? __ffs(evt) : 16;
पूर्ण

अटल पूर्णांक kempld_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा kempld_device_data *pld = dev_get_drvdata(dev->parent);
	काष्ठा kempld_platक्रमm_data *pdata = dev_get_platdata(pld->dev);
	काष्ठा kempld_gpio_data *gpio;
	काष्ठा gpio_chip *chip;
	पूर्णांक ret;

	अगर (pld->info.spec_major < 2) अणु
		dev_err(dev,
			"Driver only supports GPIO devices compatible to PLD spec. rev. 2.0 or higher\n");
		वापस -ENODEV;
	पूर्ण

	gpio = devm_kzalloc(dev, माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस -ENOMEM;

	gpio->pld = pld;

	platक्रमm_set_drvdata(pdev, gpio);

	chip = &gpio->chip;
	chip->label = "gpio-kempld";
	chip->owner = THIS_MODULE;
	chip->parent = dev;
	chip->can_sleep = true;
	अगर (pdata && pdata->gpio_base)
		chip->base = pdata->gpio_base;
	अन्यथा
		chip->base = -1;
	chip->direction_input = kempld_gpio_direction_input;
	chip->direction_output = kempld_gpio_direction_output;
	chip->get_direction = kempld_gpio_get_direction;
	chip->get = kempld_gpio_get;
	chip->set = kempld_gpio_set;
	chip->ngpio = kempld_gpio_pincount(pld);
	अगर (chip->ngpio == 0) अणु
		dev_err(dev, "No GPIO pins detected\n");
		वापस -ENODEV;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, chip, gpio);
	अगर (ret) अणु
		dev_err(dev, "Could not register GPIO chip\n");
		वापस ret;
	पूर्ण

	dev_info(dev, "GPIO functionality initialized with %d pins\n",
		 chip->ngpio);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver kempld_gpio_driver = अणु
	.driver = अणु
		.name = "kempld-gpio",
	पूर्ण,
	.probe		= kempld_gpio_probe,
पूर्ण;

module_platक्रमm_driver(kempld_gpio_driver);

MODULE_DESCRIPTION("KEM PLD GPIO Driver");
MODULE_AUTHOR("Michael Brunner <michael.brunner@kontron.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:kempld-gpio");
