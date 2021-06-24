<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * GPIO driver क्रम TPS68470 PMIC
 *
 * Copyright (C) 2017 Intel Corporation
 *
 * Authors:
 *	Antti Laakso <antti.laakso@पूर्णांकel.com>
 *	Tianshu Qiu <tian.shu.qiu@पूर्णांकel.com>
 *	Jian Xu Zheng <jian.xu.zheng@पूर्णांकel.com>
 *	Yuning Pu <yuning.pu@पूर्णांकel.com>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/mfd/tps68470.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा TPS68470_N_LOGIC_OUTPUT	3
#घोषणा TPS68470_N_REGULAR_GPIO	7
#घोषणा TPS68470_N_GPIO	(TPS68470_N_LOGIC_OUTPUT + TPS68470_N_REGULAR_GPIO)

काष्ठा tps68470_gpio_data अणु
	काष्ठा regmap *tps68470_regmap;
	काष्ठा gpio_chip gc;
पूर्ण;

अटल पूर्णांक tps68470_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tps68470_gpio_data *tps68470_gpio = gpiochip_get_data(gc);
	काष्ठा regmap *regmap = tps68470_gpio->tps68470_regmap;
	अचिन्हित पूर्णांक reg = TPS68470_REG_GPDO;
	पूर्णांक val, ret;

	अगर (offset >= TPS68470_N_REGULAR_GPIO) अणु
		offset -= TPS68470_N_REGULAR_GPIO;
		reg = TPS68470_REG_SGPO;
	पूर्ण

	ret = regmap_पढ़ो(regmap, reg, &val);
	अगर (ret) अणु
		dev_err(tps68470_gpio->gc.parent, "reg 0x%x read failed\n",
			TPS68470_REG_SGPO);
		वापस ret;
	पूर्ण
	वापस !!(val & BIT(offset));
पूर्ण

अटल पूर्णांक tps68470_gpio_get_direction(काष्ठा gpio_chip *gc,
				       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tps68470_gpio_data *tps68470_gpio = gpiochip_get_data(gc);
	काष्ठा regmap *regmap = tps68470_gpio->tps68470_regmap;
	पूर्णांक val, ret;

	/* rest are always outमाला_दो */
	अगर (offset >= TPS68470_N_REGULAR_GPIO)
		वापस GPIO_LINE_सूचीECTION_OUT;

	ret = regmap_पढ़ो(regmap, TPS68470_GPIO_CTL_REG_A(offset), &val);
	अगर (ret) अणु
		dev_err(tps68470_gpio->gc.parent, "reg 0x%x read failed\n",
			TPS68470_GPIO_CTL_REG_A(offset));
		वापस ret;
	पूर्ण

	val &= TPS68470_GPIO_MODE_MASK;
	वापस val >= TPS68470_GPIO_MODE_OUT_CMOS ? GPIO_LINE_सूचीECTION_OUT :
						    GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल व्योम tps68470_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
				पूर्णांक value)
अणु
	काष्ठा tps68470_gpio_data *tps68470_gpio = gpiochip_get_data(gc);
	काष्ठा regmap *regmap = tps68470_gpio->tps68470_regmap;
	अचिन्हित पूर्णांक reg = TPS68470_REG_GPDO;

	अगर (offset >= TPS68470_N_REGULAR_GPIO) अणु
		reg = TPS68470_REG_SGPO;
		offset -= TPS68470_N_REGULAR_GPIO;
	पूर्ण

	regmap_update_bits(regmap, reg, BIT(offset), value ? BIT(offset) : 0);
पूर्ण

अटल पूर्णांक tps68470_gpio_output(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
				पूर्णांक value)
अणु
	काष्ठा tps68470_gpio_data *tps68470_gpio = gpiochip_get_data(gc);
	काष्ठा regmap *regmap = tps68470_gpio->tps68470_regmap;

	/* rest are always outमाला_दो */
	अगर (offset >= TPS68470_N_REGULAR_GPIO)
		वापस 0;

	/* Set the initial value */
	tps68470_gpio_set(gc, offset, value);

	वापस regmap_update_bits(regmap, TPS68470_GPIO_CTL_REG_A(offset),
				 TPS68470_GPIO_MODE_MASK,
				 TPS68470_GPIO_MODE_OUT_CMOS);
पूर्ण

अटल पूर्णांक tps68470_gpio_input(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tps68470_gpio_data *tps68470_gpio = gpiochip_get_data(gc);
	काष्ठा regmap *regmap = tps68470_gpio->tps68470_regmap;

	/* rest are always outमाला_दो */
	अगर (offset >= TPS68470_N_REGULAR_GPIO)
		वापस -EINVAL;

	वापस regmap_update_bits(regmap, TPS68470_GPIO_CTL_REG_A(offset),
				   TPS68470_GPIO_MODE_MASK, 0x00);
पूर्ण

अटल स्थिर अक्षर *tps68470_names[TPS68470_N_GPIO] = अणु
	"gpio.0", "gpio.1", "gpio.2", "gpio.3",
	"gpio.4", "gpio.5", "gpio.6",
	"s_enable", "s_idle", "s_resetn",
पूर्ण;

अटल पूर्णांक tps68470_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps68470_gpio_data *tps68470_gpio;
	पूर्णांक ret;

	tps68470_gpio = devm_kzalloc(&pdev->dev, माप(*tps68470_gpio),
				     GFP_KERNEL);
	अगर (!tps68470_gpio)
		वापस -ENOMEM;

	tps68470_gpio->tps68470_regmap = dev_get_drvdata(pdev->dev.parent);
	tps68470_gpio->gc.label = "tps68470-gpio";
	tps68470_gpio->gc.owner = THIS_MODULE;
	tps68470_gpio->gc.direction_input = tps68470_gpio_input;
	tps68470_gpio->gc.direction_output = tps68470_gpio_output;
	tps68470_gpio->gc.get = tps68470_gpio_get;
	tps68470_gpio->gc.get_direction = tps68470_gpio_get_direction;
	tps68470_gpio->gc.set = tps68470_gpio_set;
	tps68470_gpio->gc.can_sleep = true;
	tps68470_gpio->gc.names = tps68470_names;
	tps68470_gpio->gc.ngpio = TPS68470_N_GPIO;
	tps68470_gpio->gc.base = -1;
	tps68470_gpio->gc.parent = &pdev->dev;

	ret = devm_gpiochip_add_data(&pdev->dev, &tps68470_gpio->gc,
				     tps68470_gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register gpio_chip: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, tps68470_gpio);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver tps68470_gpio_driver = अणु
	.driver = अणु
		   .name = "tps68470-gpio",
	पूर्ण,
	.probe = tps68470_gpio_probe,
पूर्ण;

builtin_platक्रमm_driver(tps68470_gpio_driver)
