<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Verअगरone Int.
 *
 * Author: Nicolas Saenz Julienne <nicolassaenzj@gmail.com>
 *
 * This driver is based on the gpio-tps65912 implementation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/tps65218.h>

काष्ठा tps65218_gpio अणु
	काष्ठा tps65218 *tps65218;
	काष्ठा gpio_chip gpio_chip;
पूर्ण;

अटल पूर्णांक tps65218_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा tps65218_gpio *tps65218_gpio = gpiochip_get_data(gc);
	काष्ठा tps65218 *tps65218 = tps65218_gpio->tps65218;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tps65218->regmap, TPS65218_REG_ENABLE2, &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & (TPS65218_ENABLE2_GPIO1 << offset));
पूर्ण

अटल व्योम tps65218_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित offset,
			      पूर्णांक value)
अणु
	काष्ठा tps65218_gpio *tps65218_gpio = gpiochip_get_data(gc);
	काष्ठा tps65218 *tps65218 = tps65218_gpio->tps65218;

	अगर (value)
		tps65218_set_bits(tps65218, TPS65218_REG_ENABLE2,
				  TPS65218_ENABLE2_GPIO1 << offset,
				  TPS65218_ENABLE2_GPIO1 << offset,
				  TPS65218_PROTECT_L1);
	अन्यथा
		tps65218_clear_bits(tps65218, TPS65218_REG_ENABLE2,
				    TPS65218_ENABLE2_GPIO1 << offset,
				    TPS65218_PROTECT_L1);
पूर्ण

अटल पूर्णांक tps65218_gpio_output(काष्ठा gpio_chip *gc, अचिन्हित offset,
				पूर्णांक value)
अणु
	/* Only drives GPOs */
	tps65218_gpio_set(gc, offset, value);
	वापस 0;
पूर्ण

अटल पूर्णांक tps65218_gpio_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	वापस -EPERM;
पूर्ण

अटल पूर्णांक tps65218_gpio_request(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा tps65218_gpio *tps65218_gpio = gpiochip_get_data(gc);
	काष्ठा tps65218 *tps65218 = tps65218_gpio->tps65218;
	पूर्णांक ret;

	अगर (gpiochip_line_is_खोलो_source(gc, offset)) अणु
		dev_err(gc->parent, "can't work as open source\n");
		वापस -EINVAL;
	पूर्ण

	चयन (offset) अणु
	हाल 0:
		अगर (!gpiochip_line_is_खोलो_drain(gc, offset)) अणु
			dev_err(gc->parent, "GPO1 works only as open drain\n");
			वापस -EINVAL;
		पूर्ण

		/* Disable sequencer क्रम GPO1 */
		ret = tps65218_clear_bits(tps65218, TPS65218_REG_SEQ7,
					  TPS65218_SEQ7_GPO1_SEQ_MASK,
					  TPS65218_PROTECT_L1);
		अगर (ret)
			वापस ret;

		/* Setup GPO1 */
		ret = tps65218_clear_bits(tps65218, TPS65218_REG_CONFIG1,
					  TPS65218_CONFIG1_IO1_SEL,
					  TPS65218_PROTECT_L1);
		अगर (ret)
			वापस ret;

		अवरोध;
	हाल 1:
		/* Setup GPO2 */
		ret = tps65218_clear_bits(tps65218, TPS65218_REG_CONFIG1,
					  TPS65218_CONFIG1_IO1_SEL,
					  TPS65218_PROTECT_L1);
		अगर (ret)
			वापस ret;

		अवरोध;

	हाल 2:
		अगर (!gpiochip_line_is_खोलो_drain(gc, offset)) अणु
			dev_err(gc->parent, "GPO3 works only as open drain\n");
			वापस -EINVAL;
		पूर्ण

		/* Disable sequencer क्रम GPO3 */
		ret = tps65218_clear_bits(tps65218, TPS65218_REG_SEQ7,
					  TPS65218_SEQ7_GPO3_SEQ_MASK,
					  TPS65218_PROTECT_L1);
		अगर (ret)
			वापस ret;

		/* Setup GPO3 */
		ret = tps65218_clear_bits(tps65218, TPS65218_REG_CONFIG2,
					  TPS65218_CONFIG2_DC12_RST,
					  TPS65218_PROTECT_L1);
		अगर (ret)
			वापस ret;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps65218_gpio_set_config(काष्ठा gpio_chip *gc, अचिन्हित offset,
				    अचिन्हित दीर्घ config)
अणु
	काष्ठा tps65218_gpio *tps65218_gpio = gpiochip_get_data(gc);
	काष्ठा tps65218 *tps65218 = tps65218_gpio->tps65218;
	क्रमागत pin_config_param param = pinconf_to_config_param(config);

	चयन (offset) अणु
	हाल 0:
	हाल 2:
		/* GPO1 is hardwired to be खोलो drain */
		अगर (param == PIN_CONFIG_DRIVE_OPEN_DRAIN)
			वापस 0;
		वापस -ENOTSUPP;
	हाल 1:
		/* GPO2 is push-pull by शेष, can be set as खोलो drain. */
		अगर (param == PIN_CONFIG_DRIVE_OPEN_DRAIN)
			वापस tps65218_clear_bits(tps65218,
						   TPS65218_REG_CONFIG1,
						   TPS65218_CONFIG1_GPO2_BUF,
						   TPS65218_PROTECT_L1);
		अगर (param == PIN_CONFIG_DRIVE_PUSH_PULL)
			वापस tps65218_set_bits(tps65218,
						 TPS65218_REG_CONFIG1,
						 TPS65218_CONFIG1_GPO2_BUF,
						 TPS65218_CONFIG1_GPO2_BUF,
						 TPS65218_PROTECT_L1);
		वापस -ENOTSUPP;
	शेष:
		अवरोध;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "gpio-tps65218",
	.owner			= THIS_MODULE,
	.request		= tps65218_gpio_request,
	.direction_output	= tps65218_gpio_output,
	.direction_input	= tps65218_gpio_input,
	.get			= tps65218_gpio_get,
	.set			= tps65218_gpio_set,
	.set_config		= tps65218_gpio_set_config,
	.can_sleep		= true,
	.ngpio			= 3,
	.base			= -1,
पूर्ण;

अटल पूर्णांक tps65218_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65218 *tps65218 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा tps65218_gpio *tps65218_gpio;
	पूर्णांक ret;

	tps65218_gpio = devm_kzalloc(&pdev->dev, माप(*tps65218_gpio),
				     GFP_KERNEL);
	अगर (!tps65218_gpio)
		वापस -ENOMEM;

	tps65218_gpio->tps65218 = tps65218;
	tps65218_gpio->gpio_chip = ढाँचा_chip;
	tps65218_gpio->gpio_chip.parent = &pdev->dev;
#अगर_घोषित CONFIG_OF_GPIO
	tps65218_gpio->gpio_chip.of_node = pdev->dev.of_node;
#पूर्ण_अगर

	ret = devm_gpiochip_add_data(&pdev->dev, &tps65218_gpio->gpio_chip,
				     tps65218_gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, tps65218_gpio);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id tps65218_dt_match[] = अणु
	अणु .compatible = "ti,tps65218-gpio" पूर्ण,
	अणु  पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tps65218_dt_match);

अटल स्थिर काष्ठा platक्रमm_device_id tps65218_gpio_id_table[] = अणु
	अणु "tps65218-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, tps65218_gpio_id_table);

अटल काष्ठा platक्रमm_driver tps65218_gpio_driver = अणु
	.driver = अणु
		.name = "tps65218-gpio",
		.of_match_table = of_match_ptr(tps65218_dt_match)
	पूर्ण,
	.probe = tps65218_gpio_probe,
	.id_table = tps65218_gpio_id_table,
पूर्ण;

module_platक्रमm_driver(tps65218_gpio_driver);

MODULE_AUTHOR("Nicolas Saenz Julienne <nicolassaenzj@gmail.com>");
MODULE_DESCRIPTION("GPO interface for TPS65218 PMICs");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:tps65218-gpio");
