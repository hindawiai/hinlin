<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AXP20x pinctrl and GPIO driver
 *
 * Copyright (C) 2016 Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 * Copyright (C) 2017 Quentin Schulz <quentin.schulz@मुक्त-electrons.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/axp20x.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा AXP20X_GPIO_FUNCTIONS		0x7
#घोषणा AXP20X_GPIO_FUNCTION_OUT_LOW	0
#घोषणा AXP20X_GPIO_FUNCTION_OUT_HIGH	1
#घोषणा AXP20X_GPIO_FUNCTION_INPUT	2

#घोषणा AXP20X_FUNC_GPIO_OUT		0
#घोषणा AXP20X_FUNC_GPIO_IN		1
#घोषणा AXP20X_FUNC_LDO			2
#घोषणा AXP20X_FUNC_ADC			3
#घोषणा AXP20X_FUNCS_NB			4

#घोषणा AXP20X_MUX_GPIO_OUT		0
#घोषणा AXP20X_MUX_GPIO_IN		BIT(1)
#घोषणा AXP20X_MUX_ADC			BIT(2)

#घोषणा AXP813_MUX_ADC			(BIT(2) | BIT(0))

काष्ठा axp20x_pctrl_desc अणु
	स्थिर काष्ठा pinctrl_pin_desc	*pins;
	अचिन्हित पूर्णांक			npins;
	/* Stores the pins supporting LDO function. Bit offset is pin number. */
	u8				lकरो_mask;
	/* Stores the pins supporting ADC function. Bit offset is pin number. */
	u8				adc_mask;
	u8				gpio_status_offset;
	u8				adc_mux;
पूर्ण;

काष्ठा axp20x_pinctrl_function अणु
	स्थिर अक्षर	*name;
	अचिन्हित पूर्णांक	muxval;
	स्थिर अक्षर	**groups;
	अचिन्हित पूर्णांक	ngroups;
पूर्ण;

काष्ठा axp20x_pctl अणु
	काष्ठा gpio_chip	chip;
	काष्ठा regmap		*regmap;
	काष्ठा pinctrl_dev			*pctl_dev;
	काष्ठा device				*dev;
	स्थिर काष्ठा axp20x_pctrl_desc		*desc;
	काष्ठा axp20x_pinctrl_function		funcs[AXP20X_FUNCS_NB];
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc axp209_pins[] = अणु
	PINCTRL_PIN(0, "GPIO0"),
	PINCTRL_PIN(1, "GPIO1"),
	PINCTRL_PIN(2, "GPIO2"),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc axp813_pins[] = अणु
	PINCTRL_PIN(0, "GPIO0"),
	PINCTRL_PIN(1, "GPIO1"),
पूर्ण;

अटल स्थिर काष्ठा axp20x_pctrl_desc axp20x_data = अणु
	.pins	= axp209_pins,
	.npins	= ARRAY_SIZE(axp209_pins),
	.lकरो_mask = BIT(0) | BIT(1),
	.adc_mask = BIT(0) | BIT(1),
	.gpio_status_offset = 4,
	.adc_mux = AXP20X_MUX_ADC,
पूर्ण;

अटल स्थिर काष्ठा axp20x_pctrl_desc axp813_data = अणु
	.pins	= axp813_pins,
	.npins	= ARRAY_SIZE(axp813_pins),
	.lकरो_mask = BIT(0) | BIT(1),
	.adc_mask = BIT(0),
	.gpio_status_offset = 0,
	.adc_mux = AXP813_MUX_ADC,
पूर्ण;

अटल पूर्णांक axp20x_gpio_get_reg(अचिन्हित पूर्णांक offset)
अणु
	चयन (offset) अणु
	हाल 0:
		वापस AXP20X_GPIO0_CTRL;
	हाल 1:
		वापस AXP20X_GPIO1_CTRL;
	हाल 2:
		वापस AXP20X_GPIO2_CTRL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक axp20x_gpio_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + offset);
पूर्ण

अटल पूर्णांक axp20x_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा axp20x_pctl *pctl = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pctl->regmap, AXP20X_GPIO20_SS, &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & BIT(offset + pctl->desc->gpio_status_offset));
पूर्ण

अटल पूर्णांक axp20x_gpio_get_direction(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset)
अणु
	काष्ठा axp20x_pctl *pctl = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val;
	पूर्णांक reg, ret;

	reg = axp20x_gpio_get_reg(offset);
	अगर (reg < 0)
		वापस reg;

	ret = regmap_पढ़ो(pctl->regmap, reg, &val);
	अगर (ret)
		वापस ret;

	/*
	 * This shouldn't really happen अगर the pin is in use alपढ़ोy,
	 * or अगर it's not in use yet, it doesn't matter since we're
	 * going to change the value soon anyway. Default to output.
	 */
	अगर ((val & AXP20X_GPIO_FUNCTIONS) > 2)
		वापस GPIO_LINE_सूचीECTION_OUT;

	/*
	 * The GPIO directions are the three lowest values.
	 * 2 is input, 0 and 1 are output
	 */
	अगर (val & 2)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक axp20x_gpio_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			      पूर्णांक value)
अणु
	chip->set(chip, offset, value);

	वापस 0;
पूर्ण

अटल व्योम axp20x_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			    पूर्णांक value)
अणु
	काष्ठा axp20x_pctl *pctl = gpiochip_get_data(chip);
	पूर्णांक reg;

	reg = axp20x_gpio_get_reg(offset);
	अगर (reg < 0)
		वापस;

	regmap_update_bits(pctl->regmap, reg,
			   AXP20X_GPIO_FUNCTIONS,
			   value ? AXP20X_GPIO_FUNCTION_OUT_HIGH :
			   AXP20X_GPIO_FUNCTION_OUT_LOW);
पूर्ण

अटल पूर्णांक axp20x_pmx_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक offset,
			  u8 config)
अणु
	काष्ठा axp20x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक reg;

	reg = axp20x_gpio_get_reg(offset);
	अगर (reg < 0)
		वापस reg;

	वापस regmap_update_bits(pctl->regmap, reg, AXP20X_GPIO_FUNCTIONS,
				  config);
पूर्ण

अटल पूर्णांक axp20x_pmx_func_cnt(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा axp20x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस ARRAY_SIZE(pctl->funcs);
पूर्ण

अटल स्थिर अक्षर *axp20x_pmx_func_name(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक selector)
अणु
	काष्ठा axp20x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->funcs[selector].name;
पूर्ण

अटल पूर्णांक axp20x_pmx_func_groups(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक selector,
				  स्थिर अक्षर * स्थिर **groups,
				  अचिन्हित पूर्णांक *num_groups)
अणु
	काष्ठा axp20x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctl->funcs[selector].groups;
	*num_groups = pctl->funcs[selector].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक axp20x_pmx_set_mux(काष्ठा pinctrl_dev *pctldev,
			      अचिन्हित पूर्णांक function, अचिन्हित पूर्णांक group)
अणु
	काष्ठा axp20x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक mask;

	/* Every pin supports GPIO_OUT and GPIO_IN functions */
	अगर (function <= AXP20X_FUNC_GPIO_IN)
		वापस axp20x_pmx_set(pctldev, group,
				      pctl->funcs[function].muxval);

	अगर (function == AXP20X_FUNC_LDO)
		mask = pctl->desc->lकरो_mask;
	अन्यथा
		mask = pctl->desc->adc_mask;

	अगर (!(BIT(group) & mask))
		वापस -EINVAL;

	/*
	 * We let the regulator framework handle the LDO muxing as muxing bits
	 * are basically also regulators on/off bits. It's better not to enक्रमce
	 * any state of the regulator when selecting LDO mux so that we करोn't
	 * पूर्णांकerfere with the regulator driver.
	 */
	अगर (function == AXP20X_FUNC_LDO)
		वापस 0;

	वापस axp20x_pmx_set(pctldev, group, pctl->funcs[function].muxval);
पूर्ण

अटल पूर्णांक axp20x_pmx_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
					 काष्ठा pinctrl_gpio_range *range,
					 अचिन्हित पूर्णांक offset, bool input)
अणु
	काष्ठा axp20x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	अगर (input)
		वापस axp20x_pmx_set(pctldev, offset,
				      pctl->funcs[AXP20X_FUNC_GPIO_IN].muxval);

	वापस axp20x_pmx_set(pctldev, offset,
			      pctl->funcs[AXP20X_FUNC_GPIO_OUT].muxval);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops axp20x_pmx_ops = अणु
	.get_functions_count	= axp20x_pmx_func_cnt,
	.get_function_name	= axp20x_pmx_func_name,
	.get_function_groups	= axp20x_pmx_func_groups,
	.set_mux		= axp20x_pmx_set_mux,
	.gpio_set_direction	= axp20x_pmx_gpio_set_direction,
	.strict			= true,
पूर्ण;

अटल पूर्णांक axp20x_groups_cnt(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा axp20x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->desc->npins;
पूर्ण

अटल पूर्णांक axp20x_group_pins(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक selector,
			     स्थिर अचिन्हित पूर्णांक **pins, अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा axp20x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*pins = (अचिन्हित पूर्णांक *)&pctl->desc->pins[selector];
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *axp20x_group_name(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक selector)
अणु
	काष्ठा axp20x_pctl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->desc->pins[selector].name;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops axp20x_pctrl_ops = अणु
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map		= pinconf_generic_dt_मुक्त_map,
	.get_groups_count	= axp20x_groups_cnt,
	.get_group_name		= axp20x_group_name,
	.get_group_pins		= axp20x_group_pins,
पूर्ण;

अटल पूर्णांक axp20x_funcs_groups_from_mask(काष्ठा device *dev, अचिन्हित पूर्णांक mask,
					  अचिन्हित पूर्णांक mask_len,
					  काष्ठा axp20x_pinctrl_function *func,
					  स्थिर काष्ठा pinctrl_pin_desc *pins)
अणु
	अचिन्हित दीर्घ पूर्णांक mask_cpy = mask;
	स्थिर अक्षर **group;
	अचिन्हित पूर्णांक ngroups = hweight8(mask);
	पूर्णांक bit;

	func->ngroups = ngroups;
	अगर (func->ngroups > 0) अणु
		func->groups = devm_kसुस्मृति(dev,
					    ngroups, माप(स्थिर अक्षर *),
					    GFP_KERNEL);
		अगर (!func->groups)
			वापस -ENOMEM;
		group = func->groups;
		क्रम_each_set_bit(bit, &mask_cpy, mask_len) अणु
			*group = pins[bit].name;
			group++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axp20x_build_funcs_groups(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axp20x_pctl *pctl = platक्रमm_get_drvdata(pdev);
	पूर्णांक i, ret, pin, npins = pctl->desc->npins;

	pctl->funcs[AXP20X_FUNC_GPIO_OUT].name = "gpio_out";
	pctl->funcs[AXP20X_FUNC_GPIO_OUT].muxval = AXP20X_MUX_GPIO_OUT;
	pctl->funcs[AXP20X_FUNC_GPIO_IN].name = "gpio_in";
	pctl->funcs[AXP20X_FUNC_GPIO_IN].muxval = AXP20X_MUX_GPIO_IN;
	pctl->funcs[AXP20X_FUNC_LDO].name = "ldo";
	/*
	 * Muxval क्रम LDO is useless as we won't use it.
	 * See comment in axp20x_pmx_set_mux.
	 */
	pctl->funcs[AXP20X_FUNC_ADC].name = "adc";
	pctl->funcs[AXP20X_FUNC_ADC].muxval = pctl->desc->adc_mux;

	/* Every pin supports GPIO_OUT and GPIO_IN functions */
	क्रम (i = 0; i <= AXP20X_FUNC_GPIO_IN; i++) अणु
		pctl->funcs[i].ngroups = npins;
		pctl->funcs[i].groups = devm_kसुस्मृति(&pdev->dev,
						     npins, माप(अक्षर *),
						     GFP_KERNEL);
		अगर (!pctl->funcs[i].groups)
			वापस -ENOMEM;
		क्रम (pin = 0; pin < npins; pin++)
			pctl->funcs[i].groups[pin] = pctl->desc->pins[pin].name;
	पूर्ण

	ret = axp20x_funcs_groups_from_mask(&pdev->dev, pctl->desc->lकरो_mask,
				      npins, &pctl->funcs[AXP20X_FUNC_LDO],
				      pctl->desc->pins);
	अगर (ret)
		वापस ret;

	ret = axp20x_funcs_groups_from_mask(&pdev->dev, pctl->desc->adc_mask,
				      npins, &pctl->funcs[AXP20X_FUNC_ADC],
				      pctl->desc->pins);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id axp20x_pctl_match[] = अणु
	अणु .compatible = "x-powers,axp209-gpio", .data = &axp20x_data, पूर्ण,
	अणु .compatible = "x-powers,axp813-gpio", .data = &axp813_data, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axp20x_pctl_match);

अटल पूर्णांक axp20x_pctl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा axp20x_pctl *pctl;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pinctrl_desc *pctrl_desc;
	पूर्णांक ret;

	अगर (!of_device_is_available(pdev->dev.of_node))
		वापस -ENODEV;

	अगर (!axp20x) अणु
		dev_err(&pdev->dev, "Parent drvdata not set\n");
		वापस -EINVAL;
	पूर्ण

	pctl = devm_kzalloc(&pdev->dev, माप(*pctl), GFP_KERNEL);
	अगर (!pctl)
		वापस -ENOMEM;

	pctl->chip.base			= -1;
	pctl->chip.can_sleep		= true;
	pctl->chip.request		= gpiochip_generic_request;
	pctl->chip.मुक्त			= gpiochip_generic_मुक्त;
	pctl->chip.parent		= &pdev->dev;
	pctl->chip.label		= dev_name(&pdev->dev);
	pctl->chip.owner		= THIS_MODULE;
	pctl->chip.get			= axp20x_gpio_get;
	pctl->chip.get_direction	= axp20x_gpio_get_direction;
	pctl->chip.set			= axp20x_gpio_set;
	pctl->chip.direction_input	= axp20x_gpio_input;
	pctl->chip.direction_output	= axp20x_gpio_output;

	pctl->desc = of_device_get_match_data(dev);

	pctl->chip.ngpio		= pctl->desc->npins;

	pctl->regmap = axp20x->regmap;
	pctl->dev = &pdev->dev;

	platक्रमm_set_drvdata(pdev, pctl);

	ret = axp20x_build_funcs_groups(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to build groups\n");
		वापस ret;
	पूर्ण

	pctrl_desc = devm_kzalloc(&pdev->dev, माप(*pctrl_desc), GFP_KERNEL);
	अगर (!pctrl_desc)
		वापस -ENOMEM;

	pctrl_desc->name = dev_name(&pdev->dev);
	pctrl_desc->owner = THIS_MODULE;
	pctrl_desc->pins = pctl->desc->pins;
	pctrl_desc->npins = pctl->desc->npins;
	pctrl_desc->pctlops = &axp20x_pctrl_ops;
	pctrl_desc->pmxops = &axp20x_pmx_ops;

	pctl->pctl_dev = devm_pinctrl_रेजिस्टर(&pdev->dev, pctrl_desc, pctl);
	अगर (IS_ERR(pctl->pctl_dev)) अणु
		dev_err(&pdev->dev, "couldn't register pinctrl driver\n");
		वापस PTR_ERR(pctl->pctl_dev);
	पूर्ण

	ret = devm_gpiochip_add_data(&pdev->dev, &pctl->chip, pctl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register GPIO chip\n");
		वापस ret;
	पूर्ण

	ret = gpiochip_add_pin_range(&pctl->chip, dev_name(&pdev->dev),
				     pctl->desc->pins->number,
				     pctl->desc->pins->number,
				     pctl->desc->npins);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add pin range\n");
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "AXP209 pinctrl and GPIO driver loaded\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver axp20x_pctl_driver = अणु
	.probe		= axp20x_pctl_probe,
	.driver = अणु
		.name		= "axp20x-gpio",
		.of_match_table	= axp20x_pctl_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(axp20x_pctl_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_AUTHOR("Quentin Schulz <quentin.schulz@free-electrons.com>");
MODULE_DESCRIPTION("AXP20x PMIC pinctrl and GPIO driver");
MODULE_LICENSE("GPL");
