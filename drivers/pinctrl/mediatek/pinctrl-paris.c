<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MediaTek Pinctrl Paris Driver, which implement the venकरोr per-pin
 * bindings क्रम MediaTek SoC.
 *
 * Copyright (C) 2018 MediaTek Inc.
 * Author: Sean Wang <sean.wang@mediatek.com>
 *	   Zhiyong Tao <zhiyong.tao@mediatek.com>
 *	   Hongzhou.Yang <hongzhou.yang@mediatek.com>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <dt-bindings/pinctrl/mt65xx.h>
#समावेश "pinctrl-paris.h"

#घोषणा PINCTRL_PINCTRL_DEV	KBUILD_MODNAME

/* Custom pinconf parameters */
#घोषणा MTK_PIN_CONFIG_TDSEL	(PIN_CONFIG_END + 1)
#घोषणा MTK_PIN_CONFIG_RDSEL	(PIN_CONFIG_END + 2)
#घोषणा MTK_PIN_CONFIG_PU_ADV	(PIN_CONFIG_END + 3)
#घोषणा MTK_PIN_CONFIG_PD_ADV	(PIN_CONFIG_END + 4)
#घोषणा MTK_PIN_CONFIG_DRV_ADV	(PIN_CONFIG_END + 5)

अटल स्थिर काष्ठा pinconf_generic_params mtk_custom_bindings[] = अणु
	अणु"mediatek,tdsel",	MTK_PIN_CONFIG_TDSEL,		0पूर्ण,
	अणु"mediatek,rdsel",	MTK_PIN_CONFIG_RDSEL,		0पूर्ण,
	अणु"mediatek,pull-up-adv", MTK_PIN_CONFIG_PU_ADV,		1पूर्ण,
	अणु"mediatek,pull-down-adv", MTK_PIN_CONFIG_PD_ADV,	1पूर्ण,
	अणु"mediatek,drive-strength-adv", MTK_PIN_CONFIG_DRV_ADV,	2पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर काष्ठा pin_config_item mtk_conf_items[] = अणु
	PCONFDUMP(MTK_PIN_CONFIG_TDSEL, "tdsel", शून्य, true),
	PCONFDUMP(MTK_PIN_CONFIG_RDSEL, "rdsel", शून्य, true),
	PCONFDUMP(MTK_PIN_CONFIG_PU_ADV, "pu-adv", शून्य, true),
	PCONFDUMP(MTK_PIN_CONFIG_PD_ADV, "pd-adv", शून्य, true),
	PCONFDUMP(MTK_PIN_CONFIG_DRV_ADV, "drive-strength-adv", शून्य, true),
पूर्ण;
#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर mtk_gpio_functions[] = अणु
	"func0", "func1", "func2", "func3",
	"func4", "func5", "func6", "func7",
	"func8", "func9", "func10", "func11",
	"func12", "func13", "func14", "func15",
पूर्ण;

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
	पूर्णांक pullup, err, reg, ret = 1;
	स्थिर काष्ठा mtk_pin_desc *desc;

	अगर (pin >= hw->soc->npins) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण
	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[pin];

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (hw->soc->bias_get_combo) अणु
			err = hw->soc->bias_get_combo(hw, desc, &pullup, &ret);
			अगर (err)
				जाओ out;
			अगर (param == PIN_CONFIG_BIAS_DISABLE) अणु
				अगर (ret == MTK_PUPD_SET_R1R0_00)
					ret = MTK_DISABLE;
			पूर्ण अन्यथा अगर (param == PIN_CONFIG_BIAS_PULL_UP) अणु
				/* When desire to get pull-up value, वापस
				 *  error अगर current setting is pull-करोwn
				 */
				अगर (!pullup)
					err = -EINVAL;
			पूर्ण अन्यथा अगर (param == PIN_CONFIG_BIAS_PULL_DOWN) अणु
				/* When desire to get pull-करोwn value, वापस
				 *  error अगर current setting is pull-up
				 */
				अगर (pullup)
					err = -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			err = -ENOTSUPP;
		पूर्ण
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_SR, &ret);
		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
	हाल PIN_CONFIG_OUTPUT_ENABLE:
		err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_सूची, &ret);
		अगर (err)
			जाओ out;
		/*     CONFIG     Current direction वापस value
		 * -------------  ----------------- ----------------------
		 * OUTPUT_ENABLE       output       1 (= HW value)
		 *                     input        0 (= HW value)
		 * INPUT_ENABLE        output       0 (= reverse HW value)
		 *                     input        1 (= reverse HW value)
		 */
		अगर (param == PIN_CONFIG_INPUT_ENABLE)
			ret = !ret;

		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_सूची, &ret);
		अगर (err)
			जाओ out;
		/* वापस error when in output mode
		 * because schmitt trigger only work in input mode
		 */
		अगर (ret) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_SMT, &ret);

		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		अगर (hw->soc->drive_get)
			err = hw->soc->drive_get(hw, desc, &ret);
		अन्यथा
			err = -ENOTSUPP;
		अवरोध;
	हाल MTK_PIN_CONFIG_TDSEL:
	हाल MTK_PIN_CONFIG_RDSEL:
		reg = (param == MTK_PIN_CONFIG_TDSEL) ?
		       PINCTRL_PIN_REG_TDSEL : PINCTRL_PIN_REG_RDSEL;
		err = mtk_hw_get_value(hw, desc, reg, &ret);
		अवरोध;
	हाल MTK_PIN_CONFIG_PU_ADV:
	हाल MTK_PIN_CONFIG_PD_ADV:
		अगर (hw->soc->adv_pull_get) अणु
			pullup = param == MTK_PIN_CONFIG_PU_ADV;
			err = hw->soc->adv_pull_get(hw, desc, pullup, &ret);
		पूर्ण अन्यथा
			err = -ENOTSUPP;
		अवरोध;
	हाल MTK_PIN_CONFIG_DRV_ADV:
		अगर (hw->soc->adv_drive_get)
			err = hw->soc->adv_drive_get(hw, desc, &ret);
		अन्यथा
			err = -ENOTSUPP;
		अवरोध;
	शेष:
		err = -ENOTSUPP;
	पूर्ण

out:
	अगर (!err)
		*config = pinconf_to_config_packed(param, ret);

	वापस err;
पूर्ण

अटल पूर्णांक mtk_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			   क्रमागत pin_config_param param,
			   क्रमागत pin_config_param arg)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा mtk_pin_desc *desc;
	पूर्णांक err = 0;
	u32 reg;

	अगर (pin >= hw->soc->npins) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण
	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[pin];

	चयन ((u32)param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (hw->soc->bias_set_combo)
			err = hw->soc->bias_set_combo(hw, desc, 0, MTK_DISABLE);
		अन्यथा
			err = -ENOTSUPP;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (hw->soc->bias_set_combo)
			err = hw->soc->bias_set_combo(hw, desc, 1, arg);
		अन्यथा
			err = -ENOTSUPP;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (hw->soc->bias_set_combo)
			err = hw->soc->bias_set_combo(hw, desc, 0, arg);
		अन्यथा
			err = -ENOTSUPP;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT_ENABLE:
		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_SMT,
				       MTK_DISABLE);
		/* Keep set direction to consider the हाल that a GPIO pin
		 *  करोes not have SMT control
		 */
		अगर (err != -ENOTSUPP)
			जाओ err;

		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_सूची,
				       MTK_OUTPUT);
		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
		/* regard all non-zero value as enable */
		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_IES, !!arg);
		अगर (err)
			जाओ err;

		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_सूची,
				       MTK_INPUT);
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		/* regard all non-zero value as enable */
		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_SR, !!arg);
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DO,
				       arg);
		अगर (err)
			जाओ err;

		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_सूची,
				       MTK_OUTPUT);
		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT:
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		/* arg = 1: Input mode & SMT enable ;
		 * arg = 0: Output mode & SMT disable
		 */
		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_सूची, !arg);
		अगर (err)
			जाओ err;

		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_SMT, !!arg);
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		अगर (hw->soc->drive_set)
			err = hw->soc->drive_set(hw, desc, arg);
		अन्यथा
			err = -ENOTSUPP;
		अवरोध;
	हाल MTK_PIN_CONFIG_TDSEL:
	हाल MTK_PIN_CONFIG_RDSEL:
		reg = (param == MTK_PIN_CONFIG_TDSEL) ?
		       PINCTRL_PIN_REG_TDSEL : PINCTRL_PIN_REG_RDSEL;
		err = mtk_hw_set_value(hw, desc, reg, arg);
		अवरोध;
	हाल MTK_PIN_CONFIG_PU_ADV:
	हाल MTK_PIN_CONFIG_PD_ADV:
		अगर (hw->soc->adv_pull_set) अणु
			bool pullup;

			pullup = param == MTK_PIN_CONFIG_PU_ADV;
			err = hw->soc->adv_pull_set(hw, desc, pullup,
						    arg);
		पूर्ण अन्यथा
			err = -ENOTSUPP;
		अवरोध;
	हाल MTK_PIN_CONFIG_DRV_ADV:
		अगर (hw->soc->adv_drive_set)
			err = hw->soc->adv_drive_set(hw, desc, arg);
		अन्यथा
			err = -ENOTSUPP;
		अवरोध;
	शेष:
		err = -ENOTSUPP;
	पूर्ण

err:
	वापस err;
पूर्ण

अटल काष्ठा mtk_pinctrl_group *
mtk_pctrl_find_group_by_pin(काष्ठा mtk_pinctrl *hw, u32 pin)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hw->soc->ngrps; i++) अणु
		काष्ठा mtk_pinctrl_group *grp = hw->groups + i;

		अगर (grp->pin == pin)
			वापस grp;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा mtk_func_desc *
mtk_pctrl_find_function_by_pin(काष्ठा mtk_pinctrl *hw, u32 pin_num, u32 fnum)
अणु
	स्थिर काष्ठा mtk_pin_desc *pin = hw->soc->pins + pin_num;
	स्थिर काष्ठा mtk_func_desc *func = pin->funcs;

	जबतक (func && func->name) अणु
		अगर (func->muxval == fnum)
			वापस func;
		func++;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool mtk_pctrl_is_function_valid(काष्ठा mtk_pinctrl *hw, u32 pin_num,
					u32 fnum)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hw->soc->npins; i++) अणु
		स्थिर काष्ठा mtk_pin_desc *pin = hw->soc->pins + i;

		अगर (pin->number == pin_num) अणु
			स्थिर काष्ठा mtk_func_desc *func = pin->funcs;

			जबतक (func && func->name) अणु
				अगर (func->muxval == fnum)
					वापस true;
				func++;
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक mtk_pctrl_dt_node_to_map_func(काष्ठा mtk_pinctrl *pctl,
					 u32 pin, u32 fnum,
					 काष्ठा mtk_pinctrl_group *grp,
					 काष्ठा pinctrl_map **map,
					 अचिन्हित *reserved_maps,
					 अचिन्हित *num_maps)
अणु
	bool ret;

	अगर (*num_maps == *reserved_maps)
		वापस -ENOSPC;

	(*map)[*num_maps].type = PIN_MAP_TYPE_MUX_GROUP;
	(*map)[*num_maps].data.mux.group = grp->name;

	ret = mtk_pctrl_is_function_valid(pctl, pin, fnum);
	अगर (!ret) अणु
		dev_err(pctl->dev, "invalid function %d on pin %d .\n",
			fnum, pin);
		वापस -EINVAL;
	पूर्ण

	(*map)[*num_maps].data.mux.function = mtk_gpio_functions[fnum];
	(*num_maps)++;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pctrl_dt_subnode_to_map(काष्ठा pinctrl_dev *pctldev,
				       काष्ठा device_node *node,
				       काष्ठा pinctrl_map **map,
				       अचिन्हित *reserved_maps,
				       अचिन्हित *num_maps)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक num_pins, num_funcs, maps_per_pin, i, err;
	काष्ठा mtk_pinctrl_group *grp;
	अचिन्हित पूर्णांक num_configs;
	bool has_config = false;
	अचिन्हित दीर्घ *configs;
	u32 pinfunc, pin, func;
	काष्ठा property *pins;
	अचिन्हित reserve = 0;

	pins = of_find_property(node, "pinmux", शून्य);
	अगर (!pins) अणु
		dev_err(hw->dev, "missing pins property in node %pOFn .\n",
			node);
		वापस -EINVAL;
	पूर्ण

	err = pinconf_generic_parse_dt_config(node, pctldev, &configs,
					      &num_configs);
	अगर (err)
		वापस err;

	अगर (num_configs)
		has_config = true;

	num_pins = pins->length / माप(u32);
	num_funcs = num_pins;
	maps_per_pin = 0;
	अगर (num_funcs)
		maps_per_pin++;
	अगर (has_config && num_pins >= 1)
		maps_per_pin++;

	अगर (!num_pins || !maps_per_pin) अणु
		err = -EINVAL;
		जाओ निकास;
	पूर्ण

	reserve = num_pins * maps_per_pin;

	err = pinctrl_utils_reserve_map(pctldev, map, reserved_maps, num_maps,
					reserve);
	अगर (err < 0)
		जाओ निकास;

	क्रम (i = 0; i < num_pins; i++) अणु
		err = of_property_पढ़ो_u32_index(node, "pinmux", i, &pinfunc);
		अगर (err)
			जाओ निकास;

		pin = MTK_GET_PIN_NO(pinfunc);
		func = MTK_GET_PIN_FUNC(pinfunc);

		अगर (pin >= hw->soc->npins ||
		    func >= ARRAY_SIZE(mtk_gpio_functions)) अणु
			dev_err(hw->dev, "invalid pins value.\n");
			err = -EINVAL;
			जाओ निकास;
		पूर्ण

		grp = mtk_pctrl_find_group_by_pin(hw, pin);
		अगर (!grp) अणु
			dev_err(hw->dev, "unable to match pin %d to group\n",
				pin);
			err = -EINVAL;
			जाओ निकास;
		पूर्ण

		err = mtk_pctrl_dt_node_to_map_func(hw, pin, func, grp, map,
						    reserved_maps, num_maps);
		अगर (err < 0)
			जाओ निकास;

		अगर (has_config) अणु
			err = pinctrl_utils_add_map_configs(pctldev, map,
							    reserved_maps,
							    num_maps,
							    grp->name,
							    configs,
							    num_configs,
							    PIN_MAP_TYPE_CONFIGS_GROUP);
			अगर (err < 0)
				जाओ निकास;
		पूर्ण
	पूर्ण

	err = 0;

निकास:
	kमुक्त(configs);
	वापस err;
पूर्ण

अटल पूर्णांक mtk_pctrl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा device_node *np_config,
				    काष्ठा pinctrl_map **map,
				    अचिन्हित *num_maps)
अणु
	काष्ठा device_node *np;
	अचिन्हित reserved_maps;
	पूर्णांक ret;

	*map = शून्य;
	*num_maps = 0;
	reserved_maps = 0;

	क्रम_each_child_of_node(np_config, np) अणु
		ret = mtk_pctrl_dt_subnode_to_map(pctldev, np, map,
						  &reserved_maps,
						  num_maps);
		अगर (ret < 0) अणु
			pinctrl_utils_मुक्त_map(pctldev, *map, *num_maps);
			of_node_put(np);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);

	वापस hw->soc->ngrps;
पूर्ण

अटल स्थिर अक्षर *mtk_pctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित group)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);

	वापस hw->groups[group].name;
पूर्ण

अटल पूर्णांक mtk_pctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				    अचिन्हित group, स्थिर अचिन्हित **pins,
				    अचिन्हित *num_pins)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);

	*pins = (अचिन्हित *)&hw->groups[group].pin;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hw_get_value_wrap(काष्ठा mtk_pinctrl *hw, अचिन्हित पूर्णांक gpio, पूर्णांक field)
अणु
	स्थिर काष्ठा mtk_pin_desc *desc;
	पूर्णांक value, err;

	अगर (gpio >= hw->soc->npins)
		वापस -EINVAL;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[gpio];

	err = mtk_hw_get_value(hw, desc, field, &value);
	अगर (err)
		वापस err;

	वापस value;
पूर्ण

#घोषणा mtk_pctrl_get_pinmux(hw, gpio)			\
	mtk_hw_get_value_wrap(hw, gpio, PINCTRL_PIN_REG_MODE)

#घोषणा mtk_pctrl_get_direction(hw, gpio)		\
	mtk_hw_get_value_wrap(hw, gpio, PINCTRL_PIN_REG_सूची)

#घोषणा mtk_pctrl_get_out(hw, gpio)			\
	mtk_hw_get_value_wrap(hw, gpio, PINCTRL_PIN_REG_DO)

#घोषणा mtk_pctrl_get_in(hw, gpio)			\
	mtk_hw_get_value_wrap(hw, gpio, PINCTRL_PIN_REG_DI)

#घोषणा mtk_pctrl_get_smt(hw, gpio)			\
	mtk_hw_get_value_wrap(hw, gpio, PINCTRL_PIN_REG_SMT)

#घोषणा mtk_pctrl_get_ies(hw, gpio)			\
	mtk_hw_get_value_wrap(hw, gpio, PINCTRL_PIN_REG_IES)

#घोषणा mtk_pctrl_get_driving(hw, gpio)			\
	mtk_hw_get_value_wrap(hw, gpio, PINCTRL_PIN_REG_DRV)

sमाप_प्रकार mtk_pctrl_show_one_pin(काष्ठा mtk_pinctrl *hw,
	अचिन्हित पूर्णांक gpio, अक्षर *buf, अचिन्हित पूर्णांक bufLen)
अणु
	पूर्णांक pinmux, pullup, pullen, len = 0, r1 = -1, r0 = -1;
	स्थिर काष्ठा mtk_pin_desc *desc;

	अगर (gpio >= hw->soc->npins)
		वापस -EINVAL;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[gpio];
	pinmux = mtk_pctrl_get_pinmux(hw, gpio);
	अगर (pinmux >= hw->soc->nfuncs)
		pinmux -= hw->soc->nfuncs;

	mtk_pinconf_bias_get_combo(hw, desc, &pullup, &pullen);
	अगर (pullen == MTK_PUPD_SET_R1R0_00) अणु
		pullen = 0;
		r1 = 0;
		r0 = 0;
	पूर्ण अन्यथा अगर (pullen == MTK_PUPD_SET_R1R0_01) अणु
		pullen = 1;
		r1 = 0;
		r0 = 1;
	पूर्ण अन्यथा अगर (pullen == MTK_PUPD_SET_R1R0_10) अणु
		pullen = 1;
		r1 = 1;
		r0 = 0;
	पूर्ण अन्यथा अगर (pullen == MTK_PUPD_SET_R1R0_11) अणु
		pullen = 1;
		r1 = 1;
		r0 = 1;
	पूर्ण अन्यथा अगर (pullen != MTK_DISABLE && pullen != MTK_ENABLE) अणु
		pullen = 0;
	पूर्ण
	len += scnम_लिखो(buf + len, bufLen - len,
			"%03d: %1d%1d%1d%1d%02d%1d%1d%1d%1d",
			gpio,
			pinmux,
			mtk_pctrl_get_direction(hw, gpio),
			mtk_pctrl_get_out(hw, gpio),
			mtk_pctrl_get_in(hw, gpio),
			mtk_pctrl_get_driving(hw, gpio),
			mtk_pctrl_get_smt(hw, gpio),
			mtk_pctrl_get_ies(hw, gpio),
			pullen,
			pullup);

	अगर (r1 != -1) अणु
		len += scnम_लिखो(buf + len, bufLen - len, " (%1d %1d)\n",
			r1, r0);
	पूर्ण अन्यथा अणु
		len += scnम_लिखो(buf + len, bufLen - len, "\n");
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pctrl_show_one_pin);

#घोषणा PIN_DBG_BUF_SZ 96
अटल व्योम mtk_pctrl_dbg_show(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
			  अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	अक्षर buf[PIN_DBG_BUF_SZ];

	(व्योम)mtk_pctrl_show_one_pin(hw, gpio, buf, PIN_DBG_BUF_SZ);

	seq_म_लिखो(s, "%s", buf);
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops mtk_pctlops = अणु
	.dt_node_to_map		= mtk_pctrl_dt_node_to_map,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
	.get_groups_count	= mtk_pctrl_get_groups_count,
	.get_group_name		= mtk_pctrl_get_group_name,
	.get_group_pins		= mtk_pctrl_get_group_pins,
	.pin_dbg_show           = mtk_pctrl_dbg_show,
पूर्ण;

अटल पूर्णांक mtk_pmx_get_funcs_cnt(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(mtk_gpio_functions);
पूर्ण

अटल स्थिर अक्षर *mtk_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित selector)
अणु
	वापस mtk_gpio_functions[selector];
पूर्ण

अटल पूर्णांक mtk_pmx_get_func_groups(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित function,
				   स्थिर अक्षर * स्थिर **groups,
				   अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);

	*groups = hw->grp_names;
	*num_groups = hw->soc->ngrps;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pmx_set_mux(काष्ठा pinctrl_dev *pctldev,
			   अचिन्हित function,
			   अचिन्हित group)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा mtk_pinctrl_group *grp = hw->groups + group;
	स्थिर काष्ठा mtk_func_desc *desc_func;
	स्थिर काष्ठा mtk_pin_desc *desc;
	bool ret;

	ret = mtk_pctrl_is_function_valid(hw, grp->pin, function);
	अगर (!ret) अणु
		dev_err(hw->dev, "invalid function %d on group %d .\n",
			function, group);
		वापस -EINVAL;
	पूर्ण

	desc_func = mtk_pctrl_find_function_by_pin(hw, grp->pin, function);
	अगर (!desc_func)
		वापस -EINVAL;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[grp->pin];
	mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_MODE, desc_func->muxval);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops mtk_pmxops = अणु
	.get_functions_count	= mtk_pmx_get_funcs_cnt,
	.get_function_name	= mtk_pmx_get_func_name,
	.get_function_groups	= mtk_pmx_get_func_groups,
	.set_mux		= mtk_pmx_set_mux,
	.gpio_set_direction	= mtk_pinmux_gpio_set_direction,
	.gpio_request_enable	= mtk_pinmux_gpio_request_enable,
पूर्ण;

अटल पूर्णांक mtk_pconf_group_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित group,
			       अचिन्हित दीर्घ *config)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);

	*config = hw->groups[group].config;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pconf_group_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित group,
			       अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा mtk_pinctrl *hw = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा mtk_pinctrl_group *grp = &hw->groups[group];
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_configs; i++) अणु
		ret = mtk_pinconf_set(pctldev, grp->pin,
				      pinconf_to_config_param(configs[i]),
				      pinconf_to_config_argument(configs[i]));
		अगर (ret < 0)
			वापस ret;

		grp->config = configs[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops mtk_confops = अणु
	.pin_config_get = mtk_pinconf_get,
	.pin_config_group_get	= mtk_pconf_group_get,
	.pin_config_group_set	= mtk_pconf_group_set,
	.is_generic = true,
पूर्ण;

अटल काष्ठा pinctrl_desc mtk_desc = अणु
	.name = PINCTRL_PINCTRL_DEV,
	.pctlops = &mtk_pctlops,
	.pmxops = &mtk_pmxops,
	.confops = &mtk_confops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक mtk_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा mtk_pinctrl *hw = gpiochip_get_data(chip);
	स्थिर काष्ठा mtk_pin_desc *desc;
	पूर्णांक value, err;

	अगर (gpio >= hw->soc->npins)
		वापस -EINVAL;

	/*
	 * "Virtual" GPIOs are always and only used क्रम पूर्णांकerrupts
	 * Since they are only used क्रम पूर्णांकerrupts, they are always inमाला_दो
	 */
	अगर (mtk_is_virt_gpio(hw, gpio))
		वापस 1;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[gpio];

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_सूची, &value);
	अगर (err)
		वापस err;

	अगर (value)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक mtk_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा mtk_pinctrl *hw = gpiochip_get_data(chip);
	स्थिर काष्ठा mtk_pin_desc *desc;
	पूर्णांक value, err;

	अगर (gpio >= hw->soc->npins)
		वापस -EINVAL;

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

	अगर (gpio >= hw->soc->npins)
		वापस;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[gpio];

	mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DO, !!value);
पूर्ण

अटल पूर्णांक mtk_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा mtk_pinctrl *hw = gpiochip_get_data(chip);

	अगर (gpio >= hw->soc->npins)
		वापस -EINVAL;

	वापस pinctrl_gpio_direction_input(chip->base + gpio);
पूर्ण

अटल पूर्णांक mtk_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक gpio,
				     पूर्णांक value)
अणु
	काष्ठा mtk_pinctrl *hw = gpiochip_get_data(chip);

	अगर (gpio >= hw->soc->npins)
		वापस -EINVAL;

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

	अगर (desc->eपूर्णांक.eपूर्णांक_n == EINT_NA)
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
	    desc->eपूर्णांक.eपूर्णांक_n == EINT_NA)
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
	chip->get_direction	= mtk_gpio_get_direction;
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

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pctrl_build_state(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_pinctrl *hw = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	/* Allocate groups */
	hw->groups = devm_kदो_स्मृति_array(&pdev->dev, hw->soc->ngrps,
					माप(*hw->groups), GFP_KERNEL);
	अगर (!hw->groups)
		वापस -ENOMEM;

	/* We assume that one pin is one group, use pin name as group name. */
	hw->grp_names = devm_kदो_स्मृति_array(&pdev->dev, hw->soc->ngrps,
					   माप(*hw->grp_names), GFP_KERNEL);
	अगर (!hw->grp_names)
		वापस -ENOMEM;

	क्रम (i = 0; i < hw->soc->npins; i++) अणु
		स्थिर काष्ठा mtk_pin_desc *pin = hw->soc->pins + i;
		काष्ठा mtk_pinctrl_group *group = hw->groups + i;

		group->name = pin->name;
		group->pin = pin->number;

		hw->grp_names[i] = pin->name;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mtk_paris_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			    स्थिर काष्ठा mtk_pin_soc *soc)
अणु
	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा mtk_pinctrl *hw;
	पूर्णांक err, i;

	hw = devm_kzalloc(&pdev->dev, माप(*hw), GFP_KERNEL);
	अगर (!hw)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, hw);
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

	err = mtk_pctrl_build_state(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "build state failed: %d\n", err);
		वापस -EINVAL;
	पूर्ण

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
EXPORT_SYMBOL_GPL(mtk_paris_pinctrl_probe);

अटल पूर्णांक mtk_paris_pinctrl_suspend(काष्ठा device *device)
अणु
	काष्ठा mtk_pinctrl *pctl = dev_get_drvdata(device);

	वापस mtk_eपूर्णांक_करो_suspend(pctl->eपूर्णांक);
पूर्ण

अटल पूर्णांक mtk_paris_pinctrl_resume(काष्ठा device *device)
अणु
	काष्ठा mtk_pinctrl *pctl = dev_get_drvdata(device);

	वापस mtk_eपूर्णांक_करो_resume(pctl->eपूर्णांक);
पूर्ण

स्थिर काष्ठा dev_pm_ops mtk_paris_pinctrl_pm_ops = अणु
	.suspend_noirq = mtk_paris_pinctrl_suspend,
	.resume_noirq = mtk_paris_pinctrl_resume,
पूर्ण;

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MediaTek Pinctrl Common Driver V2 Paris");
