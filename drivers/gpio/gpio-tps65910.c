<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TI TPS6591x GPIO driver
 *
 * Copyright 2010 Texas Instruments Inc.
 *
 * Author: Graeme Gregory <gg@slimlogic.co.uk>
 * Author: Jorge Eduarकरो Candelaria <jedu@slimlogic.co.uk>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/tps65910.h>
#समावेश <linux/of_device.h>

काष्ठा tps65910_gpio अणु
	काष्ठा gpio_chip gpio_chip;
	काष्ठा tps65910 *tps65910;
पूर्ण;

अटल पूर्णांक tps65910_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा tps65910_gpio *tps65910_gpio = gpiochip_get_data(gc);
	काष्ठा tps65910 *tps65910 = tps65910_gpio->tps65910;
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(tps65910->regmap, TPS65910_GPIO0 + offset, &val);

	अगर (val & GPIO_STS_MASK)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम tps65910_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित offset,
			      पूर्णांक value)
अणु
	काष्ठा tps65910_gpio *tps65910_gpio = gpiochip_get_data(gc);
	काष्ठा tps65910 *tps65910 = tps65910_gpio->tps65910;

	अगर (value)
		regmap_set_bits(tps65910->regmap, TPS65910_GPIO0 + offset,
						GPIO_SET_MASK);
	अन्यथा
		regmap_clear_bits(tps65910->regmap, TPS65910_GPIO0 + offset,
						GPIO_SET_MASK);
पूर्ण

अटल पूर्णांक tps65910_gpio_output(काष्ठा gpio_chip *gc, अचिन्हित offset,
				पूर्णांक value)
अणु
	काष्ठा tps65910_gpio *tps65910_gpio = gpiochip_get_data(gc);
	काष्ठा tps65910 *tps65910 = tps65910_gpio->tps65910;

	/* Set the initial value */
	tps65910_gpio_set(gc, offset, value);

	वापस regmap_set_bits(tps65910->regmap, TPS65910_GPIO0 + offset,
						GPIO_CFG_MASK);
पूर्ण

अटल पूर्णांक tps65910_gpio_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा tps65910_gpio *tps65910_gpio = gpiochip_get_data(gc);
	काष्ठा tps65910 *tps65910 = tps65910_gpio->tps65910;

	वापस regmap_clear_bits(tps65910->regmap, TPS65910_GPIO0 + offset,
						GPIO_CFG_MASK);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा tps65910_board *tps65910_parse_dt_क्रम_gpio(काष्ठा device *dev,
		काष्ठा tps65910 *tps65910, पूर्णांक chip_ngpio)
अणु
	काष्ठा tps65910_board *tps65910_board = tps65910->of_plat_data;
	अचिन्हित पूर्णांक prop_array[TPS6591X_MAX_NUM_GPIO];
	पूर्णांक ngpio = min(chip_ngpio, TPS6591X_MAX_NUM_GPIO);
	पूर्णांक ret;
	पूर्णांक idx;

	tps65910_board->gpio_base = -1;
	ret = of_property_पढ़ो_u32_array(tps65910->dev->of_node,
			"ti,en-gpio-sleep", prop_array, ngpio);
	अगर (ret < 0) अणु
		dev_dbg(dev, "ti,en-gpio-sleep not specified\n");
		वापस tps65910_board;
	पूर्ण

	क्रम (idx = 0; idx < ngpio; idx++)
		tps65910_board->en_gpio_sleep[idx] = (prop_array[idx] != 0);

	वापस tps65910_board;
पूर्ण
#अन्यथा
अटल काष्ठा tps65910_board *tps65910_parse_dt_क्रम_gpio(काष्ठा device *dev,
		काष्ठा tps65910 *tps65910, पूर्णांक chip_ngpio)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tps65910_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65910 *tps65910 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा tps65910_board *pdata = dev_get_platdata(tps65910->dev);
	काष्ठा tps65910_gpio *tps65910_gpio;
	पूर्णांक ret;
	पूर्णांक i;

	tps65910_gpio = devm_kzalloc(&pdev->dev,
				माप(*tps65910_gpio), GFP_KERNEL);
	अगर (!tps65910_gpio)
		वापस -ENOMEM;

	tps65910_gpio->tps65910 = tps65910;

	tps65910_gpio->gpio_chip.owner = THIS_MODULE;
	tps65910_gpio->gpio_chip.label = tps65910->i2c_client->name;

	चयन (tps65910_chip_id(tps65910)) अणु
	हाल TPS65910:
		tps65910_gpio->gpio_chip.ngpio = TPS65910_NUM_GPIO;
		अवरोध;
	हाल TPS65911:
		tps65910_gpio->gpio_chip.ngpio = TPS65911_NUM_GPIO;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	tps65910_gpio->gpio_chip.can_sleep = true;
	tps65910_gpio->gpio_chip.direction_input = tps65910_gpio_input;
	tps65910_gpio->gpio_chip.direction_output = tps65910_gpio_output;
	tps65910_gpio->gpio_chip.set	= tps65910_gpio_set;
	tps65910_gpio->gpio_chip.get	= tps65910_gpio_get;
	tps65910_gpio->gpio_chip.parent = &pdev->dev;
#अगर_घोषित CONFIG_OF_GPIO
	tps65910_gpio->gpio_chip.of_node = tps65910->dev->of_node;
#पूर्ण_अगर
	अगर (pdata && pdata->gpio_base)
		tps65910_gpio->gpio_chip.base = pdata->gpio_base;
	अन्यथा
		tps65910_gpio->gpio_chip.base = -1;

	अगर (!pdata && tps65910->dev->of_node)
		pdata = tps65910_parse_dt_क्रम_gpio(&pdev->dev, tps65910,
			tps65910_gpio->gpio_chip.ngpio);

	अगर (!pdata)
		जाओ skip_init;

	/* Configure sleep control क्रम gpios अगर provided */
	क्रम (i = 0; i < tps65910_gpio->gpio_chip.ngpio; ++i) अणु
		अगर (!pdata->en_gpio_sleep[i])
			जारी;

		ret = regmap_set_bits(tps65910->regmap,
			TPS65910_GPIO0 + i, GPIO_SLEEP_MASK);
		अगर (ret < 0)
			dev_warn(tps65910->dev,
				"GPIO Sleep setting failed with err %d\n", ret);
	पूर्ण

skip_init:
	ret = devm_gpiochip_add_data(&pdev->dev, &tps65910_gpio->gpio_chip,
				     tps65910_gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, tps65910_gpio);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver tps65910_gpio_driver = अणु
	.driver.name    = "tps65910-gpio",
	.probe		= tps65910_gpio_probe,
पूर्ण;

अटल पूर्णांक __init tps65910_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tps65910_gpio_driver);
पूर्ण
subsys_initcall(tps65910_gpio_init);
