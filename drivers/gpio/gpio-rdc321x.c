<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RDC321x GPIO driver
 *
 * Copyright (C) 2008, Volker Weiss <dev@tपूर्णांकuc.de>
 * Copyright (C) 2007-2010 Florian Fainelli <florian@खोलोwrt.org>
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/mfd/rdc321x.h>
#समावेश <linux/slab.h>

काष्ठा rdc321x_gpio अणु
	spinlock_t		lock;
	काष्ठा pci_dev		*sb_pdev;
	u32			data_reg[2];
	पूर्णांक			reg1_ctrl_base;
	पूर्णांक			reg1_data_base;
	पूर्णांक			reg2_ctrl_base;
	पूर्णांक			reg2_data_base;
	काष्ठा gpio_chip	chip;
पूर्ण;

/* पढ़ो GPIO pin */
अटल पूर्णांक rdc_gpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	काष्ठा rdc321x_gpio *gpch;
	u32 value = 0;
	पूर्णांक reg;

	gpch = gpiochip_get_data(chip);
	reg = gpio < 32 ? gpch->reg1_data_base : gpch->reg2_data_base;

	spin_lock(&gpch->lock);
	pci_ग_लिखो_config_dword(gpch->sb_pdev, reg,
					gpch->data_reg[gpio < 32 ? 0 : 1]);
	pci_पढ़ो_config_dword(gpch->sb_pdev, reg, &value);
	spin_unlock(&gpch->lock);

	वापस (1 << (gpio & 0x1f)) & value ? 1 : 0;
पूर्ण

अटल व्योम rdc_gpio_set_value_impl(काष्ठा gpio_chip *chip,
				अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा rdc321x_gpio *gpch;
	पूर्णांक reg = (gpio < 32) ? 0 : 1;

	gpch = gpiochip_get_data(chip);

	अगर (value)
		gpch->data_reg[reg] |= 1 << (gpio & 0x1f);
	अन्यथा
		gpch->data_reg[reg] &= ~(1 << (gpio & 0x1f));

	pci_ग_लिखो_config_dword(gpch->sb_pdev,
			reg ? gpch->reg2_data_base : gpch->reg1_data_base,
			gpch->data_reg[reg]);
पूर्ण

/* set GPIO pin to value */
अटल व्योम rdc_gpio_set_value(काष्ठा gpio_chip *chip,
				अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा rdc321x_gpio *gpch;

	gpch = gpiochip_get_data(chip);
	spin_lock(&gpch->lock);
	rdc_gpio_set_value_impl(chip, gpio, value);
	spin_unlock(&gpch->lock);
पूर्ण

अटल पूर्णांक rdc_gpio_config(काष्ठा gpio_chip *chip,
				अचिन्हित gpio, पूर्णांक value)
अणु
	काष्ठा rdc321x_gpio *gpch;
	पूर्णांक err;
	u32 reg;

	gpch = gpiochip_get_data(chip);

	spin_lock(&gpch->lock);
	err = pci_पढ़ो_config_dword(gpch->sb_pdev, gpio < 32 ?
			gpch->reg1_ctrl_base : gpch->reg2_ctrl_base, &reg);
	अगर (err)
		जाओ unlock;

	reg |= 1 << (gpio & 0x1f);

	err = pci_ग_लिखो_config_dword(gpch->sb_pdev, gpio < 32 ?
			gpch->reg1_ctrl_base : gpch->reg2_ctrl_base, reg);
	अगर (err)
		जाओ unlock;

	rdc_gpio_set_value_impl(chip, gpio, value);

unlock:
	spin_unlock(&gpch->lock);

	वापस err;
पूर्ण

/* configure GPIO pin as input */
अटल पूर्णांक rdc_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	वापस rdc_gpio_config(chip, gpio, 1);
पूर्ण

/*
 * Cache the initial value of both GPIO data रेजिस्टरs
 */
अटल पूर्णांक rdc321x_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	काष्ठा resource *r;
	काष्ठा rdc321x_gpio *rdc321x_gpio_dev;
	काष्ठा rdc321x_gpio_pdata *pdata;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform data supplied\n");
		वापस -ENODEV;
	पूर्ण

	rdc321x_gpio_dev = devm_kzalloc(&pdev->dev, माप(काष्ठा rdc321x_gpio),
					GFP_KERNEL);
	अगर (!rdc321x_gpio_dev)
		वापस -ENOMEM;

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IO, "gpio-reg1");
	अगर (!r) अणु
		dev_err(&pdev->dev, "failed to get gpio-reg1 resource\n");
		वापस -ENODEV;
	पूर्ण

	spin_lock_init(&rdc321x_gpio_dev->lock);
	rdc321x_gpio_dev->sb_pdev = pdata->sb_pdev;
	rdc321x_gpio_dev->reg1_ctrl_base = r->start;
	rdc321x_gpio_dev->reg1_data_base = r->start + 0x4;

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_IO, "gpio-reg2");
	अगर (!r) अणु
		dev_err(&pdev->dev, "failed to get gpio-reg2 resource\n");
		वापस -ENODEV;
	पूर्ण

	rdc321x_gpio_dev->reg2_ctrl_base = r->start;
	rdc321x_gpio_dev->reg2_data_base = r->start + 0x4;

	rdc321x_gpio_dev->chip.label = "rdc321x-gpio";
	rdc321x_gpio_dev->chip.owner = THIS_MODULE;
	rdc321x_gpio_dev->chip.direction_input = rdc_gpio_direction_input;
	rdc321x_gpio_dev->chip.direction_output = rdc_gpio_config;
	rdc321x_gpio_dev->chip.get = rdc_gpio_get_value;
	rdc321x_gpio_dev->chip.set = rdc_gpio_set_value;
	rdc321x_gpio_dev->chip.base = 0;
	rdc321x_gpio_dev->chip.ngpio = pdata->max_gpios;

	platक्रमm_set_drvdata(pdev, rdc321x_gpio_dev);

	/* This might not be, what others (BIOS, bootloader, etc.)
	   wrote to these रेजिस्टरs beक्रमe, but it's a good guess. Still
	   better than just using 0xffffffff. */
	err = pci_पढ़ो_config_dword(rdc321x_gpio_dev->sb_pdev,
					rdc321x_gpio_dev->reg1_data_base,
					&rdc321x_gpio_dev->data_reg[0]);
	अगर (err)
		वापस err;

	err = pci_पढ़ो_config_dword(rdc321x_gpio_dev->sb_pdev,
					rdc321x_gpio_dev->reg2_data_base,
					&rdc321x_gpio_dev->data_reg[1]);
	अगर (err)
		वापस err;

	dev_info(&pdev->dev, "registering %d GPIOs\n",
					rdc321x_gpio_dev->chip.ngpio);
	वापस devm_gpiochip_add_data(&pdev->dev, &rdc321x_gpio_dev->chip,
				      rdc321x_gpio_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver rdc321x_gpio_driver = अणु
	.driver.name	= "rdc321x-gpio",
	.probe		= rdc321x_gpio_probe,
पूर्ण;

module_platक्रमm_driver(rdc321x_gpio_driver);

MODULE_AUTHOR("Florian Fainelli <florian@openwrt.org>");
MODULE_DESCRIPTION("RDC321x GPIO driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rdc321x-gpio");
