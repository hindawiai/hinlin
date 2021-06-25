<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * regmap based generic GPIO driver
 *
 * Copyright 2020 Michael Walle <michael@walle.cc>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/regmap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

काष्ठा gpio_regmap अणु
	काष्ठा device *parent;
	काष्ठा regmap *regmap;
	काष्ठा gpio_chip gpio_chip;

	पूर्णांक reg_stride;
	पूर्णांक ngpio_per_reg;
	अचिन्हित पूर्णांक reg_dat_base;
	अचिन्हित पूर्णांक reg_set_base;
	अचिन्हित पूर्णांक reg_clr_base;
	अचिन्हित पूर्णांक reg_dir_in_base;
	अचिन्हित पूर्णांक reg_dir_out_base;

	पूर्णांक (*reg_mask_xlate)(काष्ठा gpio_regmap *gpio, अचिन्हित पूर्णांक base,
			      अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक *reg,
			      अचिन्हित पूर्णांक *mask);

	व्योम *driver_data;
पूर्ण;

अटल अचिन्हित पूर्णांक gpio_regmap_addr(अचिन्हित पूर्णांक addr)
अणु
	अगर (addr == GPIO_REGMAP_ADDR_ZERO)
		वापस 0;

	वापस addr;
पूर्ण

अटल पूर्णांक gpio_regmap_simple_xlate(काष्ठा gpio_regmap *gpio,
				    अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक offset,
				    अचिन्हित पूर्णांक *reg, अचिन्हित पूर्णांक *mask)
अणु
	अचिन्हित पूर्णांक line = offset % gpio->ngpio_per_reg;
	अचिन्हित पूर्णांक stride = offset / gpio->ngpio_per_reg;

	*reg = base + stride * gpio->reg_stride;
	*mask = BIT(line);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_regmap_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_regmap *gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक base, val, reg, mask;
	पूर्णांक ret;

	/* we might not have an output रेजिस्टर अगर we are input only */
	अगर (gpio->reg_dat_base)
		base = gpio_regmap_addr(gpio->reg_dat_base);
	अन्यथा
		base = gpio_regmap_addr(gpio->reg_set_base);

	ret = gpio->reg_mask_xlate(gpio, base, offset, &reg, &mask);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(gpio->regmap, reg, &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & mask);
पूर्ण

अटल व्योम gpio_regmap_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			    पूर्णांक val)
अणु
	काष्ठा gpio_regmap *gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक base = gpio_regmap_addr(gpio->reg_set_base);
	अचिन्हित पूर्णांक reg, mask;

	gpio->reg_mask_xlate(gpio, base, offset, &reg, &mask);
	अगर (val)
		regmap_update_bits(gpio->regmap, reg, mask, mask);
	अन्यथा
		regmap_update_bits(gpio->regmap, reg, mask, 0);
पूर्ण

अटल व्योम gpio_regmap_set_with_clear(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा gpio_regmap *gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक base, reg, mask;

	अगर (val)
		base = gpio_regmap_addr(gpio->reg_set_base);
	अन्यथा
		base = gpio_regmap_addr(gpio->reg_clr_base);

	gpio->reg_mask_xlate(gpio, base, offset, &reg, &mask);
	regmap_ग_लिखो(gpio->regmap, reg, mask);
पूर्ण

अटल पूर्णांक gpio_regmap_get_direction(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_regmap *gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक base, val, reg, mask;
	पूर्णांक invert, ret;

	अगर (gpio->reg_dir_out_base) अणु
		base = gpio_regmap_addr(gpio->reg_dir_out_base);
		invert = 0;
	पूर्ण अन्यथा अगर (gpio->reg_dir_in_base) अणु
		base = gpio_regmap_addr(gpio->reg_dir_in_base);
		invert = 1;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = gpio->reg_mask_xlate(gpio, base, offset, &reg, &mask);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(gpio->regmap, reg, &val);
	अगर (ret)
		वापस ret;

	अगर (!!(val & mask) ^ invert)
		वापस GPIO_LINE_सूचीECTION_OUT;
	अन्यथा
		वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक gpio_regmap_set_direction(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset, bool output)
अणु
	काष्ठा gpio_regmap *gpio = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक base, val, reg, mask;
	पूर्णांक invert, ret;

	अगर (gpio->reg_dir_out_base) अणु
		base = gpio_regmap_addr(gpio->reg_dir_out_base);
		invert = 0;
	पूर्ण अन्यथा अगर (gpio->reg_dir_in_base) अणु
		base = gpio_regmap_addr(gpio->reg_dir_in_base);
		invert = 1;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = gpio->reg_mask_xlate(gpio, base, offset, &reg, &mask);
	अगर (ret)
		वापस ret;

	अगर (invert)
		val = output ? 0 : mask;
	अन्यथा
		val = output ? mask : 0;

	वापस regmap_update_bits(gpio->regmap, reg, mask, val);
पूर्ण

अटल पूर्णांक gpio_regmap_direction_input(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset)
अणु
	वापस gpio_regmap_set_direction(chip, offset, false);
पूर्ण

अटल पूर्णांक gpio_regmap_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	gpio_regmap_set(chip, offset, value);

	वापस gpio_regmap_set_direction(chip, offset, true);
पूर्ण

व्योम gpio_regmap_set_drvdata(काष्ठा gpio_regmap *gpio, व्योम *data)
अणु
	gpio->driver_data = data;
पूर्ण
EXPORT_SYMBOL_GPL(gpio_regmap_set_drvdata);

व्योम *gpio_regmap_get_drvdata(काष्ठा gpio_regmap *gpio)
अणु
	वापस gpio->driver_data;
पूर्ण
EXPORT_SYMBOL_GPL(gpio_regmap_get_drvdata);

/**
 * gpio_regmap_रेजिस्टर() - Register a generic regmap GPIO controller
 * @config: configuration क्रम gpio_regmap
 *
 * Return: A poपूर्णांकer to the रेजिस्टरed gpio_regmap or ERR_PTR error value.
 */
काष्ठा gpio_regmap *gpio_regmap_रेजिस्टर(स्थिर काष्ठा gpio_regmap_config *config)
अणु
	काष्ठा gpio_regmap *gpio;
	काष्ठा gpio_chip *chip;
	पूर्णांक ret;

	अगर (!config->parent)
		वापस ERR_PTR(-EINVAL);

	अगर (!config->ngpio)
		वापस ERR_PTR(-EINVAL);

	/* we need at least one */
	अगर (!config->reg_dat_base && !config->reg_set_base)
		वापस ERR_PTR(-EINVAL);

	/* अगर we have a direction रेजिस्टर we need both input and output */
	अगर ((config->reg_dir_out_base || config->reg_dir_in_base) &&
	    (!config->reg_dat_base || !config->reg_set_base))
		वापस ERR_PTR(-EINVAL);

	/* we करोn't support having both रेजिस्टरs simultaneously क्रम now */
	अगर (config->reg_dir_out_base && config->reg_dir_in_base)
		वापस ERR_PTR(-EINVAL);

	gpio = kzalloc(माप(*gpio), GFP_KERNEL);
	अगर (!gpio)
		वापस ERR_PTR(-ENOMEM);

	gpio->parent = config->parent;
	gpio->regmap = config->regmap;
	gpio->ngpio_per_reg = config->ngpio_per_reg;
	gpio->reg_stride = config->reg_stride;
	gpio->reg_mask_xlate = config->reg_mask_xlate;
	gpio->reg_dat_base = config->reg_dat_base;
	gpio->reg_set_base = config->reg_set_base;
	gpio->reg_clr_base = config->reg_clr_base;
	gpio->reg_dir_in_base = config->reg_dir_in_base;
	gpio->reg_dir_out_base = config->reg_dir_out_base;

	/* अगर not set, assume there is only one रेजिस्टर */
	अगर (!gpio->ngpio_per_reg)
		gpio->ngpio_per_reg = config->ngpio;

	/* अगर not set, assume they are consecutive */
	अगर (!gpio->reg_stride)
		gpio->reg_stride = 1;

	अगर (!gpio->reg_mask_xlate)
		gpio->reg_mask_xlate = gpio_regmap_simple_xlate;

	chip = &gpio->gpio_chip;
	chip->parent = config->parent;
	chip->base = -1;
	chip->ngpio = config->ngpio;
	chip->names = config->names;
	chip->label = config->label ?: dev_name(config->parent);

#अगर defined(CONFIG_OF_GPIO)
	/* gpiolib will use of_node of the parent अगर chip->of_node is शून्य */
	chip->of_node = to_of_node(config->fwnode);
#पूर्ण_अगर /* CONFIG_OF_GPIO */

	/*
	 * If our regmap is fast_io we should probably set can_sleep to false.
	 * Right now, the regmap करोesn't save this property, nor is there any
	 * access function क्रम it.
	 * The only regmap type which uses fast_io is regmap-mmio. For now,
	 * assume a safe शेष of true here.
	 */
	chip->can_sleep = true;

	chip->get = gpio_regmap_get;
	अगर (gpio->reg_set_base && gpio->reg_clr_base)
		chip->set = gpio_regmap_set_with_clear;
	अन्यथा अगर (gpio->reg_set_base)
		chip->set = gpio_regmap_set;

	अगर (gpio->reg_dir_in_base || gpio->reg_dir_out_base) अणु
		chip->get_direction = gpio_regmap_get_direction;
		chip->direction_input = gpio_regmap_direction_input;
		chip->direction_output = gpio_regmap_direction_output;
	पूर्ण

	ret = gpiochip_add_data(chip, gpio);
	अगर (ret < 0)
		जाओ err_मुक्त_gpio;

	अगर (config->irq_करोमुख्य) अणु
		ret = gpiochip_irqchip_add_करोमुख्य(chip, config->irq_करोमुख्य);
		अगर (ret)
			जाओ err_हटाओ_gpiochip;
	पूर्ण

	वापस gpio;

err_हटाओ_gpiochip:
	gpiochip_हटाओ(chip);
err_मुक्त_gpio:
	kमुक्त(gpio);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(gpio_regmap_रेजिस्टर);

/**
 * gpio_regmap_unरेजिस्टर() - Unरेजिस्टर a generic regmap GPIO controller
 * @gpio: gpio_regmap device to unरेजिस्टर
 */
व्योम gpio_regmap_unरेजिस्टर(काष्ठा gpio_regmap *gpio)
अणु
	gpiochip_हटाओ(&gpio->gpio_chip);
	kमुक्त(gpio);
पूर्ण
EXPORT_SYMBOL_GPL(gpio_regmap_unरेजिस्टर);

अटल व्योम devm_gpio_regmap_unरेजिस्टर(काष्ठा device *dev, व्योम *res)
अणु
	gpio_regmap_unरेजिस्टर(*(काष्ठा gpio_regmap **)res);
पूर्ण

/**
 * devm_gpio_regmap_रेजिस्टर() - resource managed gpio_regmap_रेजिस्टर()
 * @dev: device that is रेजिस्टरing this GPIO device
 * @config: configuration क्रम gpio_regmap
 *
 * Managed gpio_regmap_रेजिस्टर(). For generic regmap GPIO device रेजिस्टरed by
 * this function, gpio_regmap_unरेजिस्टर() is स्वतःmatically called on driver
 * detach. See gpio_regmap_रेजिस्टर() क्रम more inक्रमmation.
 *
 * Return: A poपूर्णांकer to the रेजिस्टरed gpio_regmap or ERR_PTR error value.
 */
काष्ठा gpio_regmap *devm_gpio_regmap_रेजिस्टर(काष्ठा device *dev,
					      स्थिर काष्ठा gpio_regmap_config *config)
अणु
	काष्ठा gpio_regmap **ptr, *gpio;

	ptr = devres_alloc(devm_gpio_regmap_unरेजिस्टर, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	gpio = gpio_regmap_रेजिस्टर(config);
	अगर (!IS_ERR(gpio)) अणु
		*ptr = gpio;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस gpio;
पूर्ण
EXPORT_SYMBOL_GPL(devm_gpio_regmap_रेजिस्टर);

MODULE_AUTHOR("Michael Walle <michael@walle.cc>");
MODULE_DESCRIPTION("GPIO generic regmap driver core");
MODULE_LICENSE("GPL");
