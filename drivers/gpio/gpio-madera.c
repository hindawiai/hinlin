<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO support क्रम Cirrus Logic Madera codecs
 *
 * Copyright (C) 2015-2018 Cirrus Logic
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/madera/core.h>
#समावेश <linux/mfd/madera/pdata.h>
#समावेश <linux/mfd/madera/रेजिस्टरs.h>

काष्ठा madera_gpio अणु
	काष्ठा madera *madera;
	/* storage space क्रम the gpio_chip we're using */
	काष्ठा gpio_chip gpio_chip;
पूर्ण;

अटल पूर्णांक madera_gpio_get_direction(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset)
अणु
	काष्ठा madera_gpio *madera_gpio = gpiochip_get_data(chip);
	काष्ठा madera *madera = madera_gpio->madera;
	अचिन्हित पूर्णांक reg_offset = 2 * offset;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(madera->regmap, MADERA_GPIO1_CTRL_2 + reg_offset,
			  &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val & MADERA_GP1_सूची_MASK)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक madera_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा madera_gpio *madera_gpio = gpiochip_get_data(chip);
	काष्ठा madera *madera = madera_gpio->madera;
	अचिन्हित पूर्णांक reg_offset = 2 * offset;

	वापस regmap_update_bits(madera->regmap,
				  MADERA_GPIO1_CTRL_2 + reg_offset,
				  MADERA_GP1_सूची_MASK, MADERA_GP1_सूची);
पूर्ण

अटल पूर्णांक madera_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा madera_gpio *madera_gpio = gpiochip_get_data(chip);
	काष्ठा madera *madera = madera_gpio->madera;
	अचिन्हित पूर्णांक reg_offset = 2 * offset;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(madera->regmap, MADERA_GPIO1_CTRL_1 + reg_offset,
			  &val);
	अगर (ret < 0)
		वापस ret;

	वापस !!(val & MADERA_GP1_LVL_MASK);
पूर्ण

अटल पूर्णांक madera_gpio_direction_out(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा madera_gpio *madera_gpio = gpiochip_get_data(chip);
	काष्ठा madera *madera = madera_gpio->madera;
	अचिन्हित पूर्णांक reg_offset = 2 * offset;
	अचिन्हित पूर्णांक reg_val = value ? MADERA_GP1_LVL : 0;
	पूर्णांक ret;

	ret = regmap_update_bits(madera->regmap,
				 MADERA_GPIO1_CTRL_2 + reg_offset,
				 MADERA_GP1_सूची_MASK, 0);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_update_bits(madera->regmap,
				  MADERA_GPIO1_CTRL_1 + reg_offset,
				  MADERA_GP1_LVL_MASK, reg_val);
पूर्ण

अटल व्योम madera_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			    पूर्णांक value)
अणु
	काष्ठा madera_gpio *madera_gpio = gpiochip_get_data(chip);
	काष्ठा madera *madera = madera_gpio->madera;
	अचिन्हित पूर्णांक reg_offset = 2 * offset;
	अचिन्हित पूर्णांक reg_val = value ? MADERA_GP1_LVL : 0;
	पूर्णांक ret;

	ret = regmap_update_bits(madera->regmap,
				 MADERA_GPIO1_CTRL_1 + reg_offset,
				 MADERA_GP1_LVL_MASK, reg_val);

	/* set() करोesn't वापस an error so log a warning */
	अगर (ret)
		dev_warn(madera->dev, "Failed to write to 0x%x (%d)\n",
			 MADERA_GPIO1_CTRL_1 + reg_offset, ret);
पूर्ण

अटल स्थिर काष्ठा gpio_chip madera_gpio_chip = अणु
	.label			= "madera",
	.owner			= THIS_MODULE,
	.request		= gpiochip_generic_request,
	.मुक्त			= gpiochip_generic_मुक्त,
	.get_direction		= madera_gpio_get_direction,
	.direction_input	= madera_gpio_direction_in,
	.get			= madera_gpio_get,
	.direction_output	= madera_gpio_direction_out,
	.set			= madera_gpio_set,
	.set_config		= gpiochip_generic_config,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक madera_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(pdev->dev.parent);
	काष्ठा madera_pdata *pdata = &madera->pdata;
	काष्ठा madera_gpio *madera_gpio;
	पूर्णांक ret;

	madera_gpio = devm_kzalloc(&pdev->dev, माप(*madera_gpio),
				   GFP_KERNEL);
	अगर (!madera_gpio)
		वापस -ENOMEM;

	madera_gpio->madera = madera;

	/* Conकाष्ठा suitable gpio_chip from the ढाँचा in madera_gpio_chip */
	madera_gpio->gpio_chip = madera_gpio_chip;
	madera_gpio->gpio_chip.parent = pdev->dev.parent;

	चयन (madera->type) अणु
	हाल CS47L15:
		madera_gpio->gpio_chip.ngpio = CS47L15_NUM_GPIOS;
		अवरोध;
	हाल CS47L35:
		madera_gpio->gpio_chip.ngpio = CS47L35_NUM_GPIOS;
		अवरोध;
	हाल CS47L85:
	हाल WM1840:
		madera_gpio->gpio_chip.ngpio = CS47L85_NUM_GPIOS;
		अवरोध;
	हाल CS47L90:
	हाल CS47L91:
		madera_gpio->gpio_chip.ngpio = CS47L90_NUM_GPIOS;
		अवरोध;
	हाल CS42L92:
	हाल CS47L92:
	हाल CS47L93:
		madera_gpio->gpio_chip.ngpio = CS47L92_NUM_GPIOS;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unknown chip variant %d\n", madera->type);
		वापस -EINVAL;
	पूर्ण

	/* We want to be usable on प्रणालीs that करोn't use devicetree or acpi */
	अगर (pdata->gpio_base)
		madera_gpio->gpio_chip.base = pdata->gpio_base;
	अन्यथा
		madera_gpio->gpio_chip.base = -1;

	ret = devm_gpiochip_add_data(&pdev->dev,
				     &madera_gpio->gpio_chip,
				     madera_gpio);
	अगर (ret < 0) अणु
		dev_dbg(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * This is part of a composite MFD device which can only be used with
	 * the corresponding pinctrl driver. On all supported silicon the GPIO
	 * to pinctrl mapping is fixed in the silicon, so we रेजिस्टर it
	 * explicitly instead of requiring a redundant gpio-ranges in the
	 * devicetree.
	 * In any हाल we also want to work on प्रणालीs that करोn't use devicetree
	 * or acpi.
	 */
	ret = gpiochip_add_pin_range(&madera_gpio->gpio_chip, "madera-pinctrl",
				     0, 0, madera_gpio->gpio_chip.ngpio);
	अगर (ret) अणु
		dev_dbg(&pdev->dev, "Failed to add pin range (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver madera_gpio_driver = अणु
	.driver = अणु
		.name	= "madera-gpio",
	पूर्ण,
	.probe		= madera_gpio_probe,
पूर्ण;

module_platक्रमm_driver(madera_gpio_driver);

MODULE_SOFTDEP("pre: pinctrl-madera");
MODULE_DESCRIPTION("GPIO interface for Madera codecs");
MODULE_AUTHOR("Nariman Poushin <nariman@opensource.cirrus.com>");
MODULE_AUTHOR("Richard Fitzgerald <rf@opensource.cirrus.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:madera-gpio");
