<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Dialog DA9062 pinctrl and GPIO driver.
 * Based on DA9055 GPIO driver.
 *
 * TODO:
 *   - add pinmux and pinctrl support (gpio alternate mode)
 *
 * Documents:
 * [1] https://www.dialog-semiconductor.com/sites/शेष/files/da9062_datasheet_3v6.pdf
 *
 * Copyright (C) 2019 Pengutronix, Marco Felsch <kernel@pengutronix.de>
 */
#समावेश <linux/bits.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/gpio/driver.h>

#समावेश <linux/mfd/da9062/core.h>
#समावेश <linux/mfd/da9062/रेजिस्टरs.h>

/*
 * We need this get the gpio_desc from a <gpio_chip,offset> tuple to decide अगर
 * the gpio is active low without a venकरोr specअगरic dt-binding.
 */
#समावेश "../gpio/gpiolib.h"

#घोषणा DA9062_TYPE(offset)		(4 * (offset % 2))
#घोषणा DA9062_PIN_SHIFT(offset)	(4 * (offset % 2))
#घोषणा DA9062_PIN_ALTERNATE		0x00 /* gpio alternate mode */
#घोषणा DA9062_PIN_GPI			0x01 /* gpio in */
#घोषणा DA9062_PIN_GPO_OD		0x02 /* gpio out खोलो-drain */
#घोषणा DA9062_PIN_GPO_PP		0x03 /* gpio out push-pull */
#घोषणा DA9062_GPIO_NUM			5

काष्ठा da9062_pctl अणु
	काष्ठा da9062 *da9062;
	काष्ठा gpio_chip gc;
	अचिन्हित पूर्णांक pin_config[DA9062_GPIO_NUM];
पूर्ण;

अटल पूर्णांक da9062_pctl_get_pin_mode(काष्ठा da9062_pctl *pctl,
				    अचिन्हित पूर्णांक offset)
अणु
	काष्ठा regmap *regmap = pctl->da9062->regmap;
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(regmap, DA9062AA_GPIO_0_1 + (offset >> 1), &val);
	अगर (ret < 0)
		वापस ret;

	val >>= DA9062_PIN_SHIFT(offset);
	val &= DA9062AA_GPIO0_PIN_MASK;

	वापस val;
पूर्ण

अटल पूर्णांक da9062_pctl_set_pin_mode(काष्ठा da9062_pctl *pctl,
				    अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक mode_req)
अणु
	काष्ठा regmap *regmap = pctl->da9062->regmap;
	अचिन्हित पूर्णांक mode = mode_req;
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	mode &= DA9062AA_GPIO0_PIN_MASK;
	mode <<= DA9062_PIN_SHIFT(offset);
	mask = DA9062AA_GPIO0_PIN_MASK << DA9062_PIN_SHIFT(offset);

	ret = regmap_update_bits(regmap, DA9062AA_GPIO_0_1 + (offset >> 1),
				 mask, mode);
	अगर (!ret)
		pctl->pin_config[offset] = mode_req;

	वापस ret;
पूर्ण

अटल पूर्णांक da9062_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा da9062_pctl *pctl = gpiochip_get_data(gc);
	काष्ठा regmap *regmap = pctl->da9062->regmap;
	पूर्णांक gpio_mode, val;
	पूर्णांक ret;

	gpio_mode = da9062_pctl_get_pin_mode(pctl, offset);
	अगर (gpio_mode < 0)
		वापस gpio_mode;

	चयन (gpio_mode) अणु
	हाल DA9062_PIN_ALTERNATE:
		वापस -ENOTSUPP;
	हाल DA9062_PIN_GPI:
		ret = regmap_पढ़ो(regmap, DA9062AA_STATUS_B, &val);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल DA9062_PIN_GPO_OD:
	हाल DA9062_PIN_GPO_PP:
		ret = regmap_पढ़ो(regmap, DA9062AA_GPIO_MODE0_4, &val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस !!(val & BIT(offset));
पूर्ण

अटल व्योम da9062_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
			    पूर्णांक value)
अणु
	काष्ठा da9062_pctl *pctl = gpiochip_get_data(gc);
	काष्ठा regmap *regmap = pctl->da9062->regmap;

	regmap_update_bits(regmap, DA9062AA_GPIO_MODE0_4, BIT(offset),
			   value << offset);
पूर्ण

अटल पूर्णांक da9062_gpio_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा da9062_pctl *pctl = gpiochip_get_data(gc);
	पूर्णांक gpio_mode;

	gpio_mode = da9062_pctl_get_pin_mode(pctl, offset);
	अगर (gpio_mode < 0)
		वापस gpio_mode;

	चयन (gpio_mode) अणु
	हाल DA9062_PIN_ALTERNATE:
		वापस -ENOTSUPP;
	हाल DA9062_PIN_GPI:
		वापस GPIO_LINE_सूचीECTION_IN;
	हाल DA9062_PIN_GPO_OD:
	हाल DA9062_PIN_GPO_PP:
		वापस GPIO_LINE_सूचीECTION_OUT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक da9062_gpio_direction_input(काष्ठा gpio_chip *gc,
				       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा da9062_pctl *pctl = gpiochip_get_data(gc);
	काष्ठा regmap *regmap = pctl->da9062->regmap;
	काष्ठा gpio_desc *desc = gpiochip_get_desc(gc, offset);
	अचिन्हित पूर्णांक gpi_type;
	पूर्णांक ret;

	ret = da9062_pctl_set_pin_mode(pctl, offset, DA9062_PIN_GPI);
	अगर (ret)
		वापस ret;

	/*
	 * If the gpio is active low we should set it in hw too. No worries
	 * about gpio_get() because we पढ़ो and वापस the gpio-level. So the
	 * gpiolib active_low handling is still correct.
	 *
	 * 0 - active low, 1 - active high
	 */
	gpi_type = !gpiod_is_active_low(desc);

	वापस regmap_update_bits(regmap, DA9062AA_GPIO_0_1 + (offset >> 1),
				DA9062AA_GPIO0_TYPE_MASK << DA9062_TYPE(offset),
				gpi_type << DA9062_TYPE(offset));
पूर्ण

अटल पूर्णांक da9062_gpio_direction_output(काष्ठा gpio_chip *gc,
					अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा da9062_pctl *pctl = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक pin_config = pctl->pin_config[offset];
	पूर्णांक ret;

	ret = da9062_pctl_set_pin_mode(pctl, offset, pin_config);
	अगर (ret)
		वापस ret;

	da9062_gpio_set(gc, offset, value);

	वापस 0;
पूर्ण

अटल पूर्णांक da9062_gpio_set_config(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
				  अचिन्हित दीर्घ config)
अणु
	काष्ठा da9062_pctl *pctl = gpiochip_get_data(gc);
	काष्ठा regmap *regmap = pctl->da9062->regmap;
	पूर्णांक gpio_mode;

	/*
	 * We need to meet the following restrictions [1, Figure 18]:
	 * - PIN_CONFIG_BIAS_PULL_DOWN -> only allowed अगर the pin is used as
	 *				  gpio input
	 * - PIN_CONFIG_BIAS_PULL_UP   -> only allowed अगर the pin is used as
	 *				  gpio output खोलो-drain.
	 */

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		वापस regmap_update_bits(regmap, DA9062AA_CONFIG_K,
					  BIT(offset), 0);
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		gpio_mode = da9062_pctl_get_pin_mode(pctl, offset);
		अगर (gpio_mode < 0)
			वापस -EINVAL;
		अन्यथा अगर (gpio_mode != DA9062_PIN_GPI)
			वापस -ENOTSUPP;
		वापस regmap_update_bits(regmap, DA9062AA_CONFIG_K,
					  BIT(offset), BIT(offset));
	हाल PIN_CONFIG_BIAS_PULL_UP:
		gpio_mode = da9062_pctl_get_pin_mode(pctl, offset);
		अगर (gpio_mode < 0)
			वापस -EINVAL;
		अन्यथा अगर (gpio_mode != DA9062_PIN_GPO_OD)
			वापस -ENOTSUPP;
		वापस regmap_update_bits(regmap, DA9062AA_CONFIG_K,
					  BIT(offset), BIT(offset));
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		वापस da9062_pctl_set_pin_mode(pctl, offset,
						DA9062_PIN_GPO_OD);
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		वापस da9062_pctl_set_pin_mode(pctl, offset,
						DA9062_PIN_GPO_PP);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक da9062_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा da9062_pctl *pctl = gpiochip_get_data(gc);
	काष्ठा da9062 *da9062 = pctl->da9062;

	वापस regmap_irq_get_virq(da9062->regmap_irq,
				   DA9062_IRQ_GPI0 + offset);
पूर्ण

अटल स्थिर काष्ठा gpio_chip reference_gc = अणु
	.owner = THIS_MODULE,
	.get = da9062_gpio_get,
	.set = da9062_gpio_set,
	.get_direction = da9062_gpio_get_direction,
	.direction_input = da9062_gpio_direction_input,
	.direction_output = da9062_gpio_direction_output,
	.set_config = da9062_gpio_set_config,
	.to_irq = da9062_gpio_to_irq,
	.can_sleep = true,
	.ngpio = DA9062_GPIO_NUM,
	.base = -1,
पूर्ण;

अटल पूर्णांक da9062_pctl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *parent = pdev->dev.parent;
	काष्ठा da9062_pctl *pctl;
	पूर्णांक i;

	pctl = devm_kzalloc(&pdev->dev, माप(*pctl), GFP_KERNEL);
	अगर (!pctl)
		वापस -ENOMEM;

	pctl->da9062 = dev_get_drvdata(parent);
	अगर (!pctl->da9062)
		वापस -EINVAL;

	अगर (!device_property_present(parent, "gpio-controller"))
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(pctl->pin_config); i++)
		pctl->pin_config[i] = DA9062_PIN_GPO_PP;

	/*
	 * Currently the driver handles only the GPIO support. The
	 * pinctrl/pinmux support can be added later अगर needed.
	 */
	pctl->gc = reference_gc;
	pctl->gc.label = dev_name(&pdev->dev);
	pctl->gc.parent = &pdev->dev;
#अगर_घोषित CONFIG_OF_GPIO
	pctl->gc.of_node = parent->of_node;
#पूर्ण_अगर

	platक्रमm_set_drvdata(pdev, pctl);

	वापस devm_gpiochip_add_data(&pdev->dev, &pctl->gc, pctl);
पूर्ण

अटल काष्ठा platक्रमm_driver da9062_pctl_driver = अणु
	.probe = da9062_pctl_probe,
	.driver = अणु
		.name	= "da9062-gpio",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(da9062_pctl_driver);

MODULE_AUTHOR("Marco Felsch <kernel@pengutronix.de>");
MODULE_DESCRIPTION("DA9062 PMIC pinctrl and GPIO Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:da9062-gpio");
