<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Pinctrl driver क्रम Rockchip RK805 PMIC
 *
 * Copyright (c) 2017, Fuzhou Rockchip Electronics Co., Ltd
 *
 * Author: Joseph Chen <chenjh@rock-chips.com>
 *
 * Based on the pinctrl-as3722 driver
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/rk808.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>

#समावेश "core.h"
#समावेश "pinconf.h"
#समावेश "pinctrl-utils.h"

काष्ठा rk805_pin_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *स्थिर *groups;
	अचिन्हित पूर्णांक ngroups;
	पूर्णांक mux_option;
पूर्ण;

काष्ठा rk805_pin_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक pins[1];
	अचिन्हित पूर्णांक npins;
पूर्ण;

/*
 * @reg: gpio setting रेजिस्टर;
 * @fun_mask: functions select mask value, when set is gpio;
 * @dir_mask: input or output mask value, when set is output, otherwise input;
 * @val_mask: gpio set value, when set is level high, otherwise low;
 *
 * Dअगरferent PMIC has dअगरferent pin features, belowing 3 mask members are not
 * all necessary क्रम every PMIC. For example, RK805 has 2 pins that can be used
 * as output only GPIOs, so func_mask and dir_mask are not needed. RK816 has 1
 * pin that can be used as TS/GPIO, so fun_mask, dir_mask and val_mask are all
 * necessary.
 */
काष्ठा rk805_pin_config अणु
	u8 reg;
	u8 fun_msk;
	u8 dir_msk;
	u8 val_msk;
पूर्ण;

काष्ठा rk805_pctrl_info अणु
	काष्ठा rk808 *rk808;
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
	काष्ठा gpio_chip gpio_chip;
	काष्ठा pinctrl_desc pinctrl_desc;
	स्थिर काष्ठा rk805_pin_function *functions;
	अचिन्हित पूर्णांक num_functions;
	स्थिर काष्ठा rk805_pin_group *groups;
	पूर्णांक num_pin_groups;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक num_pins;
	स्थिर काष्ठा rk805_pin_config *pin_cfg;
पूर्ण;

क्रमागत rk805_pinmux_option अणु
	RK805_PINMUX_GPIO,
पूर्ण;

क्रमागत अणु
	RK805_GPIO0,
	RK805_GPIO1,
पूर्ण;

अटल स्थिर अक्षर *स्थिर rk805_gpio_groups[] = अणु
	"gpio0",
	"gpio1",
पूर्ण;

/* RK805: 2 output only GPIOs */
अटल स्थिर काष्ठा pinctrl_pin_desc rk805_pins_desc[] = अणु
	PINCTRL_PIN(RK805_GPIO0, "gpio0"),
	PINCTRL_PIN(RK805_GPIO1, "gpio1"),
पूर्ण;

अटल स्थिर काष्ठा rk805_pin_function rk805_pin_functions[] = अणु
	अणु
		.name = "gpio",
		.groups = rk805_gpio_groups,
		.ngroups = ARRAY_SIZE(rk805_gpio_groups),
		.mux_option = RK805_PINMUX_GPIO,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rk805_pin_group rk805_pin_groups[] = अणु
	अणु
		.name = "gpio0",
		.pins = अणु RK805_GPIO0 पूर्ण,
		.npins = 1,
	पूर्ण,
	अणु
		.name = "gpio1",
		.pins = अणु RK805_GPIO1 पूर्ण,
		.npins = 1,
	पूर्ण,
पूर्ण;

#घोषणा RK805_GPIO0_VAL_MSK	BIT(0)
#घोषणा RK805_GPIO1_VAL_MSK	BIT(1)

अटल स्थिर काष्ठा rk805_pin_config rk805_gpio_cfgs[] = अणु
	अणु
		.reg = RK805_OUT_REG,
		.val_msk = RK805_GPIO0_VAL_MSK,
	पूर्ण,
	अणु
		.reg = RK805_OUT_REG,
		.val_msk = RK805_GPIO1_VAL_MSK,
	पूर्ण,
पूर्ण;

/* generic gpio chip */
अटल पूर्णांक rk805_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा rk805_pctrl_info *pci = gpiochip_get_data(chip);
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(pci->rk808->regmap, pci->pin_cfg[offset].reg, &val);
	अगर (ret) अणु
		dev_err(pci->dev, "get gpio%d value failed\n", offset);
		वापस ret;
	पूर्ण

	वापस !!(val & pci->pin_cfg[offset].val_msk);
पूर्ण

अटल व्योम rk805_gpio_set(काष्ठा gpio_chip *chip,
			   अचिन्हित पूर्णांक offset,
			   पूर्णांक value)
अणु
	काष्ठा rk805_pctrl_info *pci = gpiochip_get_data(chip);
	पूर्णांक ret;

	ret = regmap_update_bits(pci->rk808->regmap,
				 pci->pin_cfg[offset].reg,
				 pci->pin_cfg[offset].val_msk,
				 value ? pci->pin_cfg[offset].val_msk : 0);
	अगर (ret)
		dev_err(pci->dev, "set gpio%d value %d failed\n",
			offset, value);
पूर्ण

अटल पूर्णांक rk805_gpio_direction_input(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + offset);
पूर्ण

अटल पूर्णांक rk805_gpio_direction_output(काष्ठा gpio_chip *chip,
				       अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	rk805_gpio_set(chip, offset, value);
	वापस pinctrl_gpio_direction_output(chip->base + offset);
पूर्ण

अटल पूर्णांक rk805_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा rk805_pctrl_info *pci = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* शेष output*/
	अगर (!pci->pin_cfg[offset].dir_msk)
		वापस GPIO_LINE_सूचीECTION_OUT;

	ret = regmap_पढ़ो(pci->rk808->regmap,
			  pci->pin_cfg[offset].reg,
			  &val);
	अगर (ret) अणु
		dev_err(pci->dev, "get gpio%d direction failed\n", offset);
		वापस ret;
	पूर्ण

	अगर (val & pci->pin_cfg[offset].dir_msk)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल स्थिर काष्ठा gpio_chip rk805_gpio_chip = अणु
	.label			= "rk805-gpio",
	.request		= gpiochip_generic_request,
	.मुक्त			= gpiochip_generic_मुक्त,
	.get_direction		= rk805_gpio_get_direction,
	.get			= rk805_gpio_get,
	.set			= rk805_gpio_set,
	.direction_input	= rk805_gpio_direction_input,
	.direction_output	= rk805_gpio_direction_output,
	.can_sleep		= true,
	.base			= -1,
	.owner			= THIS_MODULE,
पूर्ण;

/* generic pinctrl */
अटल पूर्णांक rk805_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);

	वापस pci->num_pin_groups;
पूर्ण

अटल स्थिर अक्षर *rk805_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						अचिन्हित पूर्णांक group)
अणु
	काष्ठा rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);

	वापस pci->groups[group].name;
पूर्ण

अटल पूर्णांक rk805_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक group,
					स्थिर अचिन्हित पूर्णांक **pins,
					अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);

	*pins = pci->groups[group].pins;
	*num_pins = pci->groups[group].npins;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops rk805_pinctrl_ops = अणु
	.get_groups_count = rk805_pinctrl_get_groups_count,
	.get_group_name = rk805_pinctrl_get_group_name,
	.get_group_pins = rk805_pinctrl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक rk805_pinctrl_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);

	वापस pci->num_functions;
पूर्ण

अटल स्थिर अक्षर *rk805_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
					       अचिन्हित पूर्णांक function)
अणु
	काष्ठा rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);

	वापस pci->functions[function].name;
पूर्ण

अटल पूर्णांक rk805_pinctrl_get_func_groups(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित पूर्णांक function,
					 स्थिर अक्षर *स्थिर **groups,
					 अचिन्हित पूर्णांक *स्थिर num_groups)
अणु
	काष्ठा rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);

	*groups = pci->functions[function].groups;
	*num_groups = pci->functions[function].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक _rk805_pinctrl_set_mux(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक offset,
				  पूर्णांक mux)
अणु
	काष्ठा rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक ret;

	अगर (!pci->pin_cfg[offset].fun_msk)
		वापस 0;

	अगर (mux == RK805_PINMUX_GPIO) अणु
		ret = regmap_update_bits(pci->rk808->regmap,
					 pci->pin_cfg[offset].reg,
					 pci->pin_cfg[offset].fun_msk,
					 pci->pin_cfg[offset].fun_msk);
		अगर (ret) अणु
			dev_err(pci->dev, "set gpio%d GPIO failed\n", offset);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(pci->dev, "Couldn't find function mux %d\n", mux);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rk805_pinctrl_set_mux(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक function,
				 अचिन्हित पूर्णांक group)
अणु
	काष्ठा rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक mux = pci->functions[function].mux_option;
	पूर्णांक offset = group;

	वापस _rk805_pinctrl_set_mux(pctldev, offset, mux);
पूर्ण

अटल पूर्णांक rk805_pmx_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
					काष्ठा pinctrl_gpio_range *range,
					अचिन्हित पूर्णांक offset, bool input)
अणु
	काष्ठा rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक ret;

	/* चयन to gpio function */
	ret = _rk805_pinctrl_set_mux(pctldev, offset, RK805_PINMUX_GPIO);
	अगर (ret) अणु
		dev_err(pci->dev, "set gpio%d mux failed\n", offset);
		वापस ret;
	पूर्ण

	/* set direction */
	अगर (!pci->pin_cfg[offset].dir_msk)
		वापस 0;

	ret = regmap_update_bits(pci->rk808->regmap,
				 pci->pin_cfg[offset].reg,
				 pci->pin_cfg[offset].dir_msk,
				 input ? 0 : pci->pin_cfg[offset].dir_msk);
	अगर (ret) अणु
		dev_err(pci->dev, "set gpio%d direction failed\n", offset);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops rk805_pinmux_ops = अणु
	.get_functions_count	= rk805_pinctrl_get_funcs_count,
	.get_function_name	= rk805_pinctrl_get_func_name,
	.get_function_groups	= rk805_pinctrl_get_func_groups,
	.set_mux		= rk805_pinctrl_set_mux,
	.gpio_set_direction	= rk805_pmx_gpio_set_direction,
पूर्ण;

अटल पूर्णांक rk805_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	u32 arg = 0;

	चयन (param) अणु
	हाल PIN_CONFIG_OUTPUT:
		arg = rk805_gpio_get(&pci->gpio_chip, pin);
		अवरोध;
	शेष:
		dev_err(pci->dev, "Properties not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, (u16)arg);

	वापस 0;
पूर्ण

अटल पूर्णांक rk805_pinconf_set(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *configs,
			     अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा rk805_pctrl_info *pci = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param;
	u32 i, arg = 0;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_OUTPUT:
			rk805_gpio_set(&pci->gpio_chip, pin, arg);
			rk805_pmx_gpio_set_direction(pctldev, शून्य, pin, false);
			अवरोध;
		शेष:
			dev_err(pci->dev, "Properties not supported\n");
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops rk805_pinconf_ops = अणु
	.pin_config_get = rk805_pinconf_get,
	.pin_config_set = rk805_pinconf_set,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_desc rk805_pinctrl_desc = अणु
	.name = "rk805-pinctrl",
	.pctlops = &rk805_pinctrl_ops,
	.pmxops = &rk805_pinmux_ops,
	.confops = &rk805_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक rk805_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk805_pctrl_info *pci;
	पूर्णांक ret;

	pci = devm_kzalloc(&pdev->dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	pci->dev = &pdev->dev;
	pci->dev->of_node = pdev->dev.parent->of_node;
	pci->rk808 = dev_get_drvdata(pdev->dev.parent);

	pci->pinctrl_desc = rk805_pinctrl_desc;
	pci->gpio_chip = rk805_gpio_chip;
	pci->gpio_chip.parent = &pdev->dev;
	pci->gpio_chip.of_node = pdev->dev.parent->of_node;

	platक्रमm_set_drvdata(pdev, pci);

	चयन (pci->rk808->variant) अणु
	हाल RK805_ID:
		pci->pins = rk805_pins_desc;
		pci->num_pins = ARRAY_SIZE(rk805_pins_desc);
		pci->functions = rk805_pin_functions;
		pci->num_functions = ARRAY_SIZE(rk805_pin_functions);
		pci->groups = rk805_pin_groups;
		pci->num_pin_groups = ARRAY_SIZE(rk805_pin_groups);
		pci->pinctrl_desc.pins = rk805_pins_desc;
		pci->pinctrl_desc.npins = ARRAY_SIZE(rk805_pins_desc);
		pci->pin_cfg = rk805_gpio_cfgs;
		pci->gpio_chip.ngpio = ARRAY_SIZE(rk805_gpio_cfgs);
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "unsupported RK805 ID %lu\n",
			pci->rk808->variant);
		वापस -EINVAL;
	पूर्ण

	/* Add gpio chip */
	ret = devm_gpiochip_add_data(&pdev->dev, &pci->gpio_chip, pci);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Couldn't add gpiochip\n");
		वापस ret;
	पूर्ण

	/* Add pinctrl */
	pci->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, &pci->pinctrl_desc, pci);
	अगर (IS_ERR(pci->pctl)) अणु
		dev_err(&pdev->dev, "Couldn't add pinctrl\n");
		वापस PTR_ERR(pci->pctl);
	पूर्ण

	/* Add pin range */
	ret = gpiochip_add_pin_range(&pci->gpio_chip, dev_name(&pdev->dev),
				     0, 0, pci->gpio_chip.ngpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Couldn't add gpiochip pin range\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rk805_pinctrl_driver = अणु
	.probe = rk805_pinctrl_probe,
	.driver = अणु
		.name = "rk805-pinctrl",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rk805_pinctrl_driver);

MODULE_DESCRIPTION("RK805 pin control and GPIO driver");
MODULE_AUTHOR("Joseph Chen <chenjh@rock-chips.com>");
MODULE_LICENSE("GPL v2");
