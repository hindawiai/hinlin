<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MAXIM MAX77620 GPIO driver
 *
 * Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/max77620.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा GPIO_REG_ADDR(offset) (MAX77620_REG_GPIO0 + offset)

काष्ठा max77620_gpio अणु
	काष्ठा gpio_chip	gpio_chip;
	काष्ठा regmap		*rmap;
	काष्ठा device		*dev;
	काष्ठा mutex		buslock; /* irq_bus_lock */
	अचिन्हित पूर्णांक		irq_type[MAX77620_GPIO_NR];
	bool			irq_enabled[MAX77620_GPIO_NR];
पूर्ण;

अटल irqवापस_t max77620_gpio_irqhandler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max77620_gpio *gpio = data;
	अचिन्हित पूर्णांक value, offset;
	अचिन्हित दीर्घ pending;
	पूर्णांक err;

	err = regmap_पढ़ो(gpio->rmap, MAX77620_REG_IRQ_LVL2_GPIO, &value);
	अगर (err < 0) अणु
		dev_err(gpio->dev, "REG_IRQ_LVL2_GPIO read failed: %d\n", err);
		वापस IRQ_NONE;
	पूर्ण

	pending = value;

	क्रम_each_set_bit(offset, &pending, MAX77620_GPIO_NR) अणु
		अचिन्हित पूर्णांक virq;

		virq = irq_find_mapping(gpio->gpio_chip.irq.करोमुख्य, offset);
		handle_nested_irq(virq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम max77620_gpio_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा max77620_gpio *gpio = gpiochip_get_data(chip);

	gpio->irq_enabled[data->hwirq] = false;
पूर्ण

अटल व्योम max77620_gpio_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा max77620_gpio *gpio = gpiochip_get_data(chip);

	gpio->irq_enabled[data->hwirq] = true;
पूर्ण

अटल पूर्णांक max77620_gpio_set_irq_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा max77620_gpio *gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक irq_type;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		irq_type = MAX77620_CNFG_GPIO_INT_RISING;
		अवरोध;

	हाल IRQ_TYPE_EDGE_FALLING:
		irq_type = MAX77620_CNFG_GPIO_INT_FALLING;
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		irq_type = MAX77620_CNFG_GPIO_INT_RISING |
			   MAX77620_CNFG_GPIO_INT_FALLING;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	gpio->irq_type[data->hwirq] = irq_type;

	वापस 0;
पूर्ण

अटल व्योम max77620_gpio_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा max77620_gpio *gpio = gpiochip_get_data(chip);

	mutex_lock(&gpio->buslock);
पूर्ण

अटल व्योम max77620_gpio_bus_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा max77620_gpio *gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक value, offset = data->hwirq;
	पूर्णांक err;

	value = gpio->irq_enabled[offset] ? gpio->irq_type[offset] : 0;

	err = regmap_update_bits(gpio->rmap, GPIO_REG_ADDR(offset),
				 MAX77620_CNFG_GPIO_INT_MASK, value);
	अगर (err < 0)
		dev_err(chip->parent, "failed to update interrupt mask: %d\n",
			err);

	mutex_unlock(&gpio->buslock);
पूर्ण

अटल काष्ठा irq_chip max77620_gpio_irqchip = अणु
	.name		= "max77620-gpio",
	.irq_mask	= max77620_gpio_irq_mask,
	.irq_unmask	= max77620_gpio_irq_unmask,
	.irq_set_type	= max77620_gpio_set_irq_type,
	.irq_bus_lock	= max77620_gpio_bus_lock,
	.irq_bus_sync_unlock = max77620_gpio_bus_sync_unlock,
	.flags		= IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

अटल पूर्णांक max77620_gpio_dir_input(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा max77620_gpio *mgpio = gpiochip_get_data(gc);
	पूर्णांक ret;

	ret = regmap_update_bits(mgpio->rmap, GPIO_REG_ADDR(offset),
				 MAX77620_CNFG_GPIO_सूची_MASK,
				 MAX77620_CNFG_GPIO_सूची_INPUT);
	अगर (ret < 0)
		dev_err(mgpio->dev, "CNFG_GPIOx dir update failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक max77620_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा max77620_gpio *mgpio = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(mgpio->rmap, GPIO_REG_ADDR(offset), &val);
	अगर (ret < 0) अणु
		dev_err(mgpio->dev, "CNFG_GPIOx read failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर  (val & MAX77620_CNFG_GPIO_सूची_MASK)
		वापस !!(val & MAX77620_CNFG_GPIO_INPUT_VAL_MASK);
	अन्यथा
		वापस !!(val & MAX77620_CNFG_GPIO_OUTPUT_VAL_MASK);
पूर्ण

अटल पूर्णांक max77620_gpio_dir_output(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
				    पूर्णांक value)
अणु
	काष्ठा max77620_gpio *mgpio = gpiochip_get_data(gc);
	u8 val;
	पूर्णांक ret;

	val = (value) ? MAX77620_CNFG_GPIO_OUTPUT_VAL_HIGH :
				MAX77620_CNFG_GPIO_OUTPUT_VAL_LOW;

	ret = regmap_update_bits(mgpio->rmap, GPIO_REG_ADDR(offset),
				 MAX77620_CNFG_GPIO_OUTPUT_VAL_MASK, val);
	अगर (ret < 0) अणु
		dev_err(mgpio->dev, "CNFG_GPIOx val update failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(mgpio->rmap, GPIO_REG_ADDR(offset),
				 MAX77620_CNFG_GPIO_सूची_MASK,
				 MAX77620_CNFG_GPIO_सूची_OUTPUT);
	अगर (ret < 0)
		dev_err(mgpio->dev, "CNFG_GPIOx dir update failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक max77620_gpio_set_debounce(काष्ठा max77620_gpio *mgpio,
				      अचिन्हित पूर्णांक offset,
				      अचिन्हित पूर्णांक debounce)
अणु
	u8 val;
	पूर्णांक ret;

	चयन (debounce) अणु
	हाल 0:
		val = MAX77620_CNFG_GPIO_DBNC_None;
		अवरोध;
	हाल 1 ... 8000:
		val = MAX77620_CNFG_GPIO_DBNC_8ms;
		अवरोध;
	हाल 8001 ... 16000:
		val = MAX77620_CNFG_GPIO_DBNC_16ms;
		अवरोध;
	हाल 16001 ... 32000:
		val = MAX77620_CNFG_GPIO_DBNC_32ms;
		अवरोध;
	शेष:
		dev_err(mgpio->dev, "Illegal value %u\n", debounce);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(mgpio->rmap, GPIO_REG_ADDR(offset),
				 MAX77620_CNFG_GPIO_DBNC_MASK, val);
	अगर (ret < 0)
		dev_err(mgpio->dev, "CNFG_GPIOx_DBNC update failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम max77620_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
			      पूर्णांक value)
अणु
	काष्ठा max77620_gpio *mgpio = gpiochip_get_data(gc);
	u8 val;
	पूर्णांक ret;

	val = (value) ? MAX77620_CNFG_GPIO_OUTPUT_VAL_HIGH :
				MAX77620_CNFG_GPIO_OUTPUT_VAL_LOW;

	ret = regmap_update_bits(mgpio->rmap, GPIO_REG_ADDR(offset),
				 MAX77620_CNFG_GPIO_OUTPUT_VAL_MASK, val);
	अगर (ret < 0)
		dev_err(mgpio->dev, "CNFG_GPIO_OUT update failed: %d\n", ret);
पूर्ण

अटल पूर्णांक max77620_gpio_set_config(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
				    अचिन्हित दीर्घ config)
अणु
	काष्ठा max77620_gpio *mgpio = gpiochip_get_data(gc);

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		वापस regmap_update_bits(mgpio->rmap, GPIO_REG_ADDR(offset),
					  MAX77620_CNFG_GPIO_DRV_MASK,
					  MAX77620_CNFG_GPIO_DRV_OPENDRAIN);
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		वापस regmap_update_bits(mgpio->rmap, GPIO_REG_ADDR(offset),
					  MAX77620_CNFG_GPIO_DRV_MASK,
					  MAX77620_CNFG_GPIO_DRV_PUSHPULL);
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		वापस max77620_gpio_set_debounce(mgpio, offset,
			pinconf_to_config_argument(config));
	शेष:
		अवरोध;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक max77620_gpio_irq_init_hw(काष्ठा gpio_chip *gc)
अणु
	काष्ठा max77620_gpio *gpio = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	/*
	 * GPIO पूर्णांकerrupts may be left ON after bootloader, hence let's
	 * pre-initialize hardware to the expected state by disabling all
	 * the पूर्णांकerrupts.
	 */
	क्रम (i = 0; i < MAX77620_GPIO_NR; i++) अणु
		err = regmap_update_bits(gpio->rmap, GPIO_REG_ADDR(i),
					 MAX77620_CNFG_GPIO_INT_MASK, 0);
		अगर (err < 0) अणु
			dev_err(gpio->dev,
				"failed to disable interrupt: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77620_chip *chip =  dev_get_drvdata(pdev->dev.parent);
	काष्ठा max77620_gpio *mgpio;
	काष्ठा gpio_irq_chip *girq;
	अचिन्हित पूर्णांक gpio_irq;
	पूर्णांक ret;

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;

	gpio_irq = ret;

	mgpio = devm_kzalloc(&pdev->dev, माप(*mgpio), GFP_KERNEL);
	अगर (!mgpio)
		वापस -ENOMEM;

	mutex_init(&mgpio->buslock);
	mgpio->rmap = chip->rmap;
	mgpio->dev = &pdev->dev;

	mgpio->gpio_chip.label = pdev->name;
	mgpio->gpio_chip.parent = pdev->dev.parent;
	mgpio->gpio_chip.direction_input = max77620_gpio_dir_input;
	mgpio->gpio_chip.get = max77620_gpio_get;
	mgpio->gpio_chip.direction_output = max77620_gpio_dir_output;
	mgpio->gpio_chip.set = max77620_gpio_set;
	mgpio->gpio_chip.set_config = max77620_gpio_set_config;
	mgpio->gpio_chip.ngpio = MAX77620_GPIO_NR;
	mgpio->gpio_chip.can_sleep = 1;
	mgpio->gpio_chip.base = -1;

	girq = &mgpio->gpio_chip.irq;
	girq->chip = &max77620_gpio_irqchip;
	/* This will let us handle the parent IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->parents = शून्य;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_edge_irq;
	girq->init_hw = max77620_gpio_irq_init_hw;
	girq->thपढ़ोed = true;

	platक्रमm_set_drvdata(pdev, mgpio);

	ret = devm_gpiochip_add_data(&pdev->dev, &mgpio->gpio_chip, mgpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "gpio_init: Failed to add max77620_gpio\n");
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, gpio_irq, शून्य,
					max77620_gpio_irqhandler, IRQF_ONESHOT,
					"max77620-gpio", mgpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to request IRQ: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max77620_gpio_devtype[] = अणु
	अणु .name = "max77620-gpio", पूर्ण,
	अणु .name = "max20024-gpio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max77620_gpio_devtype);

अटल काष्ठा platक्रमm_driver max77620_gpio_driver = अणु
	.driver.name	= "max77620-gpio",
	.probe		= max77620_gpio_probe,
	.id_table	= max77620_gpio_devtype,
पूर्ण;

module_platक्रमm_driver(max77620_gpio_driver);

MODULE_DESCRIPTION("GPIO interface for MAX77620 and MAX20024 PMIC");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_AUTHOR("Chaitanya Bandi <bandik@nvidia.com>");
MODULE_ALIAS("platform:max77620-gpio");
MODULE_LICENSE("GPL v2");
