<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2018 BayLibre SAS
// Author: Bartosz Golaszewski <bgolaszewski@baylibre.com>
//
// GPIO driver क्रम MAXIM 77650/77651 अक्षरger/घातer-supply.

#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/max77650.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा MAX77650_GPIO_सूची_MASK		BIT(0)
#घोषणा MAX77650_GPIO_INVAL_MASK	BIT(1)
#घोषणा MAX77650_GPIO_DRV_MASK		BIT(2)
#घोषणा MAX77650_GPIO_OUTVAL_MASK	BIT(3)
#घोषणा MAX77650_GPIO_DEBOUNCE_MASK	BIT(4)

#घोषणा MAX77650_GPIO_सूची_OUT		0x00
#घोषणा MAX77650_GPIO_सूची_IN		BIT(0)
#घोषणा MAX77650_GPIO_OUT_LOW		0x00
#घोषणा MAX77650_GPIO_OUT_HIGH		BIT(3)
#घोषणा MAX77650_GPIO_DRV_OPEN_DRAIN	0x00
#घोषणा MAX77650_GPIO_DRV_PUSH_PULL	BIT(2)
#घोषणा MAX77650_GPIO_DEBOUNCE		BIT(4)

#घोषणा MAX77650_GPIO_सूची_BITS(_reg) \
		((_reg) & MAX77650_GPIO_सूची_MASK)
#घोषणा MAX77650_GPIO_INVAL_BITS(_reg) \
		(((_reg) & MAX77650_GPIO_INVAL_MASK) >> 1)

काष्ठा max77650_gpio_chip अणु
	काष्ठा regmap *map;
	काष्ठा gpio_chip gc;
	पूर्णांक irq;
पूर्ण;

अटल पूर्णांक max77650_gpio_direction_input(काष्ठा gpio_chip *gc,
					 अचिन्हित पूर्णांक offset)
अणु
	काष्ठा max77650_gpio_chip *chip = gpiochip_get_data(gc);

	वापस regmap_update_bits(chip->map,
				  MAX77650_REG_CNFG_GPIO,
				  MAX77650_GPIO_सूची_MASK,
				  MAX77650_GPIO_सूची_IN);
पूर्ण

अटल पूर्णांक max77650_gpio_direction_output(काष्ठा gpio_chip *gc,
					  अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा max77650_gpio_chip *chip = gpiochip_get_data(gc);
	पूर्णांक mask, regval;

	mask = MAX77650_GPIO_सूची_MASK | MAX77650_GPIO_OUTVAL_MASK;
	regval = value ? MAX77650_GPIO_OUT_HIGH : MAX77650_GPIO_OUT_LOW;
	regval |= MAX77650_GPIO_सूची_OUT;

	वापस regmap_update_bits(chip->map,
				  MAX77650_REG_CNFG_GPIO, mask, regval);
पूर्ण

अटल व्योम max77650_gpio_set_value(काष्ठा gpio_chip *gc,
				    अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा max77650_gpio_chip *chip = gpiochip_get_data(gc);
	पूर्णांक rv, regval;

	regval = value ? MAX77650_GPIO_OUT_HIGH : MAX77650_GPIO_OUT_LOW;

	rv = regmap_update_bits(chip->map, MAX77650_REG_CNFG_GPIO,
				MAX77650_GPIO_OUTVAL_MASK, regval);
	अगर (rv)
		dev_err(gc->parent, "cannot set GPIO value: %d\n", rv);
पूर्ण

अटल पूर्णांक max77650_gpio_get_value(काष्ठा gpio_chip *gc,
				   अचिन्हित पूर्णांक offset)
अणु
	काष्ठा max77650_gpio_chip *chip = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक val;
	पूर्णांक rv;

	rv = regmap_पढ़ो(chip->map, MAX77650_REG_CNFG_GPIO, &val);
	अगर (rv)
		वापस rv;

	वापस MAX77650_GPIO_INVAL_BITS(val);
पूर्ण

अटल पूर्णांक max77650_gpio_get_direction(काष्ठा gpio_chip *gc,
				       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा max77650_gpio_chip *chip = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक val;
	पूर्णांक rv;

	rv = regmap_पढ़ो(chip->map, MAX77650_REG_CNFG_GPIO, &val);
	अगर (rv)
		वापस rv;

	वापस MAX77650_GPIO_सूची_BITS(val);
पूर्ण

अटल पूर्णांक max77650_gpio_set_config(काष्ठा gpio_chip *gc,
				    अचिन्हित पूर्णांक offset, अचिन्हित दीर्घ cfg)
अणु
	काष्ठा max77650_gpio_chip *chip = gpiochip_get_data(gc);

	चयन (pinconf_to_config_param(cfg)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		वापस regmap_update_bits(chip->map,
					  MAX77650_REG_CNFG_GPIO,
					  MAX77650_GPIO_DRV_MASK,
					  MAX77650_GPIO_DRV_OPEN_DRAIN);
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		वापस regmap_update_bits(chip->map,
					  MAX77650_REG_CNFG_GPIO,
					  MAX77650_GPIO_DRV_MASK,
					  MAX77650_GPIO_DRV_PUSH_PULL);
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		वापस regmap_update_bits(chip->map,
					  MAX77650_REG_CNFG_GPIO,
					  MAX77650_GPIO_DEBOUNCE_MASK,
					  MAX77650_GPIO_DEBOUNCE);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक max77650_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा max77650_gpio_chip *chip = gpiochip_get_data(gc);

	वापस chip->irq;
पूर्ण

अटल पूर्णांक max77650_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77650_gpio_chip *chip;
	काष्ठा device *dev, *parent;
	काष्ठा i2c_client *i2c;

	dev = &pdev->dev;
	parent = dev->parent;
	i2c = to_i2c_client(parent);

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->map = dev_get_regmap(parent, शून्य);
	अगर (!chip->map)
		वापस -ENODEV;

	chip->irq = platक्रमm_get_irq_byname(pdev, "GPI");
	अगर (chip->irq < 0)
		वापस chip->irq;

	chip->gc.base = -1;
	chip->gc.ngpio = 1;
	chip->gc.label = i2c->name;
	chip->gc.parent = dev;
	chip->gc.owner = THIS_MODULE;
	chip->gc.can_sleep = true;

	chip->gc.direction_input = max77650_gpio_direction_input;
	chip->gc.direction_output = max77650_gpio_direction_output;
	chip->gc.set = max77650_gpio_set_value;
	chip->gc.get = max77650_gpio_get_value;
	chip->gc.get_direction = max77650_gpio_get_direction;
	chip->gc.set_config = max77650_gpio_set_config;
	chip->gc.to_irq = max77650_gpio_to_irq;

	वापस devm_gpiochip_add_data(dev, &chip->gc, chip);
पूर्ण

अटल काष्ठा platक्रमm_driver max77650_gpio_driver = अणु
	.driver = अणु
		.name = "max77650-gpio",
	पूर्ण,
	.probe = max77650_gpio_probe,
पूर्ण;
module_platक्रमm_driver(max77650_gpio_driver);

MODULE_DESCRIPTION("MAXIM 77650/77651 GPIO driver");
MODULE_AUTHOR("Bartosz Golaszewski <bgolaszewski@baylibre.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:max77650-gpio");
