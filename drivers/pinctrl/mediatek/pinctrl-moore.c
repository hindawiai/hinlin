<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MediaTek Pinctrl Moore Driver, which implement the generic dt-binding
 * pinctrl-bindings.txt क्रम MediaTek SoC.
 *
 * Copyright (C) 2017-2018 MediaTek Inc.
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */

#समावेश <linux/gpio/driver.h>
#समावेश "pinctrl-moore.h"

#घोषणा PINCTRL_PINCTRL_DEV		KBUILD_MODNAME

/* Custom pinconf parameters */
#घोषणा MTK_PIN_CONFIG_TDSEL	(PIN_CONFIG_END + 1)
#घोषणा MTK_PIN_CONFIG_RDSEL	(PIN_CONFIG_END + 2)
#घोषणा MTK_PIN_CONFIG_PU_ADV	(PIN_CONFIG_END + 3)
#घोषणा MTK_PIN_CONFIG_PD_ADV	(PIN_CONFIG_END + 4)

अटल स्थिर काष्ठा pinconf_generic_params mtk_custom_bindings[] = अणु
	अणु"mediatek,tdsel",	MTK_PIN_CONFIG_TDSEL,		0पूर्ण,
	अणु"mediatek,rdsel",	MTK_PIN_CONFIG_RDSEL,		0पूर्ण,
	अणु"mediatek,pull-up-adv", MTK_PIN_CONFIG_PU_ADV,		1पूर्ण,
	अणु"mediatek,pull-down-adv", MTK_PIN_CONFIG_PD_ADV,	1पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर काष्ठा pin_config_item mtk_conf_items[] = अणु
	PCONFDUMP(MTK_PIN_CONFIG_TDSEL, "tdsel", शून्य, true),
	PCONFDUMP(MTK_PIN_CONFIG_RDSEL, "rdsel", शून्य, true),
	PCONFDUMP(MTK_PIN_CONFIG_PU_ADV, "pu-adv", शून्य, true),
	PCONFDUMP(MTK_PIN_CONFIG_PD_ADV, "pd-adv", शून्य, true),
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक mtk_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
			      अचिन्हित पूर्णांक selector, अचिन्हित पूर्णांक group)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा function_desc *func;
	काष्ठा group_desc *grp;
	पूर्णांक i;

	func = pinmux_generic_get_function(pctldev, selector);
	अगर (!func)
		वापस -EINVAL;

	grp = pinctrl_generic_get_group(pctldev, group);
	अगर (!grp)
		वापस -EINVAL;

	dev_dbg(pctldev->dev, "enable function %s group %s\n",
		func->name, grp->name);

	क्रम (i = 0; i < grp->num_pins; i++) अणु
		स्थिर काष्ठा mtk_pin_desc *desc;
		पूर्णांक *pin_modes = grp->data;
		पूर्णांक pin = grp->pins[i];

		desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[pin];

		mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_MODE,
				 pin_modes[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pinmux_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
					  काष्ठा pinctrl_gpio_range *range,
					  अचिन्हित पूर्णांक pin)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा mtk_pin_desc *desc;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[pin];

	वापस mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_MODE,
				hw->soc->gpio_m);
पूर्ण

अटल पूर्णांक mtk_pinmux_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
					 काष्ठा pinctrl_gpio_range *range,
					 अचिन्हित पूर्णांक pin, bool input)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा mtk_pin_desc *desc;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[pin];

	/* hardware would take 0 as input direction */
	वापस mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_सूची, !input);
पूर्ण

अटल पूर्णांक mtk_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			   अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	u32 param = pinconf_to_config_param(*config);
	पूर्णांक val, val2, err, reg, ret = 1;
	स्थिर काष्ठा mtk_pin_desc *desc;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[pin];

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (hw->soc->bias_disable_get) अणु
			err = hw->soc->bias_disable_get(hw, desc, &ret);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			वापस -ENOTSUPP;
		पूर्ण
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (hw->soc->bias_get) अणु
			err = hw->soc->bias_get(hw, desc, 1, &ret);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			वापस -ENOTSUPP;
		पूर्ण
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (hw->soc->bias_get) अणु
			err = hw->soc->bias_get(hw, desc, 0, &ret);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			वापस -ENOTSUPP;
		पूर्ण
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_SR, &val);
		अगर (err)
			वापस err;

		अगर (!val)
			वापस -EINVAL;

		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
	हाल PIN_CONFIG_OUTPUT_ENABLE:
		err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_सूची, &val);
		अगर (err)
			वापस err;

		/* HW takes input mode as zero; output mode as non-zero */
		अगर ((val && param == PIN_CONFIG_INPUT_ENABLE) ||
		    (!val && param == PIN_CONFIG_OUTPUT_ENABLE))
			वापस -EINVAL;

		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_सूची, &val);
		अगर (err)
			वापस err;

		err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_SMT, &val2);
		अगर (err)
			वापस err;

		अगर (val || !val2)
			वापस -EINVAL;

		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		अगर (hw->soc->drive_get) अणु
			err = hw->soc->drive_get(hw, desc, &ret);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			err = -ENOTSUPP;
		पूर्ण
		अवरोध;
	हाल MTK_PIN_CONFIG_TDSEL:
	हाल MTK_PIN_CONFIG_RDSEL:
		reg = (param == MTK_PIN_CONFIG_TDSEL) ?
		       PINCTRL_PIN_REG_TDSEL : PINCTRL_PIN_REG_RDSEL;

		err = mtk_hw_get_value(hw, desc, reg, &val);
		अगर (err)
			वापस err;

		ret = val;

		अवरोध;
	हाल MTK_PIN_CONFIG_PU_ADV:
	हाल MTK_PIN_CONFIG_PD_ADV:
		अगर (hw->soc->adv_pull_get) अणु
			bool pullup;

			pullup = param == MTK_PIN_CONFIG_PU_ADV;
			err = hw->soc->adv_pull_get(hw, desc, pullup, &ret);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			वापस -ENOTSUPP;
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, ret);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			   अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा mtk_pin_desc *desc;
	u32 reg, param, arg;
	पूर्णांक cfg, err = 0;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[pin];

	क्रम (cfg = 0; cfg < num_configs; cfg++) अणु
		param = pinconf_to_config_param(configs[cfg]);
		arg = pinconf_to_config_argument(configs[cfg]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			अगर (hw->soc->bias_disable_set) अणु
				err = hw->soc->bias_disable_set(hw, desc);
				अगर (err)
					वापस err;
			पूर्ण अन्यथा अणु
				वापस -ENOTSUPP;
			पूर्ण
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			अगर (hw->soc->bias_set) अणु
				err = hw->soc->bias_set(hw, desc, 1);
				अगर (err)
					वापस err;
			पूर्ण अन्यथा अणु
				वापस -ENOTSUPP;
			पूर्ण
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			अगर (hw->soc->bias_set) अणु
				err = hw->soc->bias_set(hw, desc, 0);
				अगर (err)
					वापस err;
			पूर्ण अन्यथा अणु
				वापस -ENOTSUPP;
			पूर्ण
			अवरोध;
		हाल PIN_CONFIG_OUTPUT_ENABLE:
			err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_SMT,
					       MTK_DISABLE);
			अगर (err)
				जाओ err;

			err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_सूची,
					       MTK_OUTPUT);
			अगर (err)
				जाओ err;
			अवरोध;
		हाल PIN_CONFIG_INPUT_ENABLE:

			अगर (hw->soc->ies_present) अणु
				mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_IES,
						 MTK_ENABLE);
			पूर्ण

			err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_सूची,
					       MTK_INPUT);
			अगर (err)
				जाओ err;
			अवरोध;
		हाल PIN_CONFIG_SLEW_RATE:
			err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_SR,
					       arg);
			अगर (err)
				जाओ err;

			अवरोध;
		हाल PIN_CONFIG_OUTPUT:
			err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_सूची,
					       MTK_OUTPUT);
			अगर (err)
				जाओ err;

			err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DO,
					       arg);
			अगर (err)
				जाओ err;
			अवरोध;
		हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			/* arg = 1: Input mode & SMT enable ;
			 * arg = 0: Output mode & SMT disable
			 */
			arg = arg ? 2 : 1;
			err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_सूची,
					       arg & 1);
			अगर (err)
				जाओ err;

			err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_SMT,
					       !!(arg & 2));
			अगर (err)
				जाओ err;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			अगर (hw->soc->drive_set) अणु
				err = hw->soc->drive_set(hw, desc, arg);
				अगर (err)
					वापस err;
			पूर्ण अन्यथा अणु
				err = -ENOTSUPP;
			पूर्ण
			अवरोध;
		हाल MTK_PIN_CONFIG_TDSEL:
		हाल MTK_PIN_CONFIG_RDSEL:
			reg = (param == MTK_PIN_CONFIG_TDSEL) ?
			       PINCTRL_PIN_REG_TDSEL : PINCTRL_PIN_REG_RDSEL;

			err = mtk_hw_set_value(hw, desc, reg, arg);
			अगर (err)
				जाओ err;
			अवरोध;
		हाल MTK_PIN_CONFIG_PU_ADV:
		हाल MTK_PIN_CONFIG_PD_ADV:
			अगर (hw->soc->adv_pull_set) अणु
				bool pullup;

				pullup = param == MTK_PIN_CONFIG_PU_ADV;
				err = hw->soc->adv_pull_set(hw, desc, pullup,
							    arg);
				अगर (err)
					वापस err;
			पूर्ण अन्यथा अणु
				वापस -ENOTSUPP;
			पूर्ण
			अवरोध;
		शेष:
			err = -ENOTSUPP;
		पूर्ण
	पूर्ण
err:
	वापस err;
पूर्ण

अटल पूर्णांक mtk_pinconf_group_get(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक group, अचिन्हित दीर्घ *config)
अणु
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक i, npins, old = 0;
	पूर्णांक ret;

	ret = pinctrl_generic_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < npins; i++) अणु
		अगर (mtk_pinconf_get(pctldev, pins[i], config))
			वापस -ENOTSUPP;

		/* configs करो not match between two pins */
		अगर (i && old != *config)
			वापस -ENOTSUPP;

		old = *config;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक group, अचिन्हित दीर्घ *configs,
				 अचिन्हित पूर्णांक num_configs)
अणु
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक i, npins;
	पूर्णांक ret;

	ret = pinctrl_generic_get_group_pins(pctldev, group, &pins, &npins);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < npins; i++) अणु
		ret = mtk_pinconf_set(pctldev, pins[i], configs, num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops mtk_pctlops = अणु
	.get_groups_count = pinctrl_generic_get_group_count,
	.get_group_name = pinctrl_generic_get_group_name,
	.get_group_pins = pinctrl_generic_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map = pinconf_generic_dt_मुक्त_map,
पूर्ण;

अटल स्थिर काष्ठा pinmux_ops mtk_pmxops = अणु
	.get_functions_count = pinmux_generic_get_function_count,
	.get_function_name = pinmux_generic_get_function_name,
	.get_function_groups = pinmux_generic_get_function_groups,
	.set_mux = mtk_pinmux_set_mux,
	.gpio_request_enable = mtk_pinmux_gpio_request_enable,
	.gpio_set_direction = mtk_pinmux_gpio_set_direction,
	.strict = true,
पूर्ण;

अटल स्थिर काष्ठा pinconf_ops mtk_confops = अणु
	.is_generic = true,
	.pin_config_get = mtk_pinconf_get,
	.pin_config_set = mtk_pinconf_set,
	.pin_config_group_get = mtk_pinconf_group_get,
	.pin_config_group_set = mtk_pinconf_group_set,
	.pin_config_config_dbg_show = pinconf_generic_dump_config,
पूर्ण;

अटल काष्ठा pinctrl_desc mtk_desc = अणु
	.name = PINCTRL_PINCTRL_DEV,
	.pctlops = &mtk_pctlops,
	.pmxops = &mtk_pmxops,
	.confops = &mtk_confops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक mtk_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा mtk_pinctrl *hw = gpiochip_get_data(chip);
	स्थिर काष्ठा mtk_pin_desc *desc;
	पूर्णांक value, err;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[gpio];

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DI, &value);
	अगर (err)
		वापस err;

	वापस !!value;
पूर्ण

अटल व्योम mtk_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	काष्ठा mtk_pinctrl *hw = gpiochip_get_data(chip);
	स्थिर काष्ठा mtk_pin_desc *desc;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[gpio];

	mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DO, !!value);
पूर्ण

अटल पूर्णांक mtk_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + gpio);
पूर्ण

अटल पूर्णांक mtk_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio,
				     पूर्णांक value)
अणु
	mtk_gpio_set(chip, gpio, value);

	वापस pinctrl_gpio_direction_output(chip->base + gpio);
पूर्ण

अटल पूर्णांक mtk_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा mtk_pinctrl *hw = gpiochip_get_data(chip);
	स्थिर काष्ठा mtk_pin_desc *desc;

	अगर (!hw->eपूर्णांक)
		वापस -ENOTSUPP;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[offset];

	अगर (desc->eपूर्णांक.eपूर्णांक_n == (u16)EINT_NA)
		वापस -ENOTSUPP;

	वापस mtk_eपूर्णांक_find_irq(hw->eपूर्णांक, desc->eपूर्णांक.eपूर्णांक_n);
पूर्ण

अटल पूर्णांक mtk_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			       अचिन्हित दीर्घ config)
अणु
	काष्ठा mtk_pinctrl *hw = gpiochip_get_data(chip);
	स्थिर काष्ठा mtk_pin_desc *desc;
	u32 debounce;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[offset];

	अगर (!hw->eपूर्णांक ||
	    pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE ||
	    desc->eपूर्णांक.eपूर्णांक_n == (u16)EINT_NA)
		वापस -ENOTSUPP;

	debounce = pinconf_to_config_argument(config);

	वापस mtk_eपूर्णांक_set_debounce(hw->eपूर्णांक, desc->eपूर्णांक.eपूर्णांक_n, debounce);
पूर्ण

अटल पूर्णांक mtk_build_gpiochip(काष्ठा mtk_pinctrl *hw, काष्ठा device_node *np)
अणु
	काष्ठा gpio_chip *chip = &hw->chip;
	पूर्णांक ret;

	chip->label		= PINCTRL_PINCTRL_DEV;
	chip->parent		= hw->dev;
	chip->request		= gpiochip_generic_request;
	chip->मुक्त		= gpiochip_generic_मुक्त;
	chip->direction_input	= mtk_gpio_direction_input;
	chip->direction_output	= mtk_gpio_direction_output;
	chip->get		= mtk_gpio_get;
	chip->set		= mtk_gpio_set;
	chip->to_irq		= mtk_gpio_to_irq;
	chip->set_config	= mtk_gpio_set_config;
	chip->base		= -1;
	chip->ngpio		= hw->soc->npins;
	chip->of_node		= np;
	chip->of_gpio_n_cells	= 2;

	ret = gpiochip_add_data(chip, hw);
	अगर (ret < 0)
		वापस ret;

	/* Just क्रम backward compatible क्रम these old pinctrl nodes without
	 * "gpio-ranges" property. Otherwise, called directly from a
	 * DeviceTree-supported pinctrl driver is DEPRECATED.
	 * Please see Section 2.1 of
	 * Documentation/devicetree/bindings/gpio/gpio.txt on how to
	 * bind pinctrl and gpio drivers via the "gpio-ranges" property.
	 */
	अगर (!of_find_property(np, "gpio-ranges", शून्य)) अणु
		ret = gpiochip_add_pin_range(chip, dev_name(hw->dev), 0, 0,
					     chip->ngpio);
		अगर (ret < 0) अणु
			gpiochip_हटाओ(chip);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_build_groups(काष्ठा mtk_pinctrl *hw)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < hw->soc->ngrps; i++) अणु
		स्थिर काष्ठा group_desc *group = hw->soc->grps + i;

		err = pinctrl_generic_add_group(hw->pctrl, group->name,
						group->pins, group->num_pins,
						group->data);
		अगर (err < 0) अणु
			dev_err(hw->dev, "Failed to register group %s\n",
				group->name);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_build_functions(काष्ठा mtk_pinctrl *hw)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < hw->soc->nfuncs ; i++) अणु
		स्थिर काष्ठा function_desc *func = hw->soc->funcs + i;

		err = pinmux_generic_add_function(hw->pctrl, func->name,
						  func->group_names,
						  func->num_group_names,
						  func->data);
		अगर (err < 0) अणु
			dev_err(hw->dev, "Failed to register function %s\n",
				func->name);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mtk_moore_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			    स्थिर काष्ठा mtk_pin_soc *soc)
अणु
	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा mtk_pinctrl *hw;
	पूर्णांक err, i;

	hw = devm_kzalloc(&pdev->dev, माप(*hw), GFP_KERNEL);
	अगर (!hw)
		वापस -ENOMEM;

	hw->soc = soc;
	hw->dev = &pdev->dev;

	अगर (!hw->soc->nbase_names) अणु
		dev_err(&pdev->dev,
			"SoC should be assigned at least one register base\n");
		वापस -EINVAL;
	पूर्ण

	hw->base = devm_kदो_स्मृति_array(&pdev->dev, hw->soc->nbase_names,
				      माप(*hw->base), GFP_KERNEL);
	अगर (!hw->base)
		वापस -ENOMEM;

	क्रम (i = 0; i < hw->soc->nbase_names; i++) अणु
		hw->base[i] = devm_platक्रमm_ioremap_resource_byname(pdev,
						hw->soc->base_names[i]);
		अगर (IS_ERR(hw->base[i]))
			वापस PTR_ERR(hw->base[i]);
	पूर्ण

	hw->nbase = hw->soc->nbase_names;

	spin_lock_init(&hw->lock);

	/* Copy from पूर्णांकernal काष्ठा mtk_pin_desc to रेजिस्टर to the core */
	pins = devm_kदो_स्मृति_array(&pdev->dev, hw->soc->npins, माप(*pins),
				  GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	क्रम (i = 0; i < hw->soc->npins; i++) अणु
		pins[i].number = hw->soc->pins[i].number;
		pins[i].name = hw->soc->pins[i].name;
	पूर्ण

	/* Setup pins descriptions per SoC types */
	mtk_desc.pins = (स्थिर काष्ठा pinctrl_pin_desc *)pins;
	mtk_desc.npins = hw->soc->npins;
	mtk_desc.num_custom_params = ARRAY_SIZE(mtk_custom_bindings);
	mtk_desc.custom_params = mtk_custom_bindings;
#अगर_घोषित CONFIG_DEBUG_FS
	mtk_desc.custom_conf_items = mtk_conf_items;
#पूर्ण_अगर

	err = devm_pinctrl_रेजिस्टर_and_init(&pdev->dev, &mtk_desc, hw,
					     &hw->pctrl);
	अगर (err)
		वापस err;

	/* Setup groups descriptions per SoC types */
	err = mtk_build_groups(hw);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to build groups\n");
		वापस err;
	पूर्ण

	/* Setup functions descriptions per SoC types */
	err = mtk_build_functions(hw);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to build functions\n");
		वापस err;
	पूर्ण

	/* For able to make pinctrl_claim_hogs, we must not enable pinctrl
	 * until all groups and functions are being added one.
	 */
	err = pinctrl_enable(hw->pctrl);
	अगर (err)
		वापस err;

	err = mtk_build_eपूर्णांक(hw, pdev);
	अगर (err)
		dev_warn(&pdev->dev,
			 "Failed to add EINT, but pinctrl still can work\n");

	/* Build gpiochip should be after pinctrl_enable is करोne */
	err = mtk_build_gpiochip(hw, pdev->dev.of_node);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to add gpio_chip\n");
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, hw);

	वापस 0;
पूर्ण
