<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Spपढ़ोtrum pin controller driver
 * Copyright (C) 2017 Spपढ़ोtrum  - http://www.spपढ़ोtrum.com
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/slab.h>

#समावेश "../core.h"
#समावेश "../pinmux.h"
#समावेश "../pinconf.h"
#समावेश "../pinctrl-utils.h"
#समावेश "pinctrl-sprd.h"

#घोषणा PINCTRL_BIT_MASK(width)		(~(~0UL << (width)))
#घोषणा PINCTRL_REG_OFFSET		0x20
#घोषणा PINCTRL_REG_MISC_OFFSET		0x4020
#घोषणा PINCTRL_REG_LEN			0x4

#घोषणा PIN_FUNC_MASK			(BIT(4) | BIT(5))
#घोषणा PIN_FUNC_SEL_1			~PIN_FUNC_MASK
#घोषणा PIN_FUNC_SEL_2			BIT(4)
#घोषणा PIN_FUNC_SEL_3			BIT(5)
#घोषणा PIN_FUNC_SEL_4			PIN_FUNC_MASK

#घोषणा AP_SLEEP_MODE			BIT(13)
#घोषणा PUBCP_SLEEP_MODE		BIT(14)
#घोषणा TGLDSP_SLEEP_MODE		BIT(15)
#घोषणा AGDSP_SLEEP_MODE		BIT(16)
#घोषणा CM4_SLEEP_MODE			BIT(17)
#घोषणा SLEEP_MODE_MASK			GENMASK(5, 0)
#घोषणा SLEEP_MODE_SHIFT		13

#घोषणा SLEEP_INPUT			BIT(1)
#घोषणा SLEEP_INPUT_MASK		0x1
#घोषणा SLEEP_INPUT_SHIFT		1

#घोषणा SLEEP_OUTPUT			BIT(0)
#घोषणा SLEEP_OUTPUT_MASK		0x1
#घोषणा SLEEP_OUTPUT_SHIFT		0

#घोषणा DRIVE_STRENGTH_MASK		GENMASK(3, 0)
#घोषणा DRIVE_STRENGTH_SHIFT		19

#घोषणा SLEEP_PULL_DOWN			BIT(2)
#घोषणा SLEEP_PULL_DOWN_MASK		0x1
#घोषणा SLEEP_PULL_DOWN_SHIFT		2

#घोषणा PULL_DOWN			BIT(6)
#घोषणा PULL_DOWN_MASK			0x1
#घोषणा PULL_DOWN_SHIFT			6

#घोषणा SLEEP_PULL_UP			BIT(3)
#घोषणा SLEEP_PULL_UP_MASK		0x1
#घोषणा SLEEP_PULL_UP_SHIFT		3

#घोषणा PULL_UP_4_7K			(BIT(12) | BIT(7))
#घोषणा PULL_UP_20K			BIT(7)
#घोषणा PULL_UP_MASK			0x21
#घोषणा PULL_UP_SHIFT			7

#घोषणा INPUT_SCHMITT			BIT(11)
#घोषणा INPUT_SCHMITT_MASK		0x1
#घोषणा INPUT_SCHMITT_SHIFT		11

क्रमागत pin_sleep_mode अणु
	AP_SLEEP = BIT(0),
	PUBCP_SLEEP = BIT(1),
	TGLDSP_SLEEP = BIT(2),
	AGDSP_SLEEP = BIT(3),
	CM4_SLEEP = BIT(4),
पूर्ण;

क्रमागत pin_func_sel अणु
	PIN_FUNC_1,
	PIN_FUNC_2,
	PIN_FUNC_3,
	PIN_FUNC_4,
	PIN_FUNC_MAX,
पूर्ण;

/**
 * काष्ठा sprd_pin: represent one pin's description
 * @name: pin name
 * @number: pin number
 * @type: pin type, can be GLOBAL_CTRL_PIN/COMMON_PIN/MISC_PIN
 * @reg: pin रेजिस्टर address
 * @bit_offset: bit offset in pin रेजिस्टर
 * @bit_width: bit width in pin रेजिस्टर
 */
काष्ठा sprd_pin अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक number;
	क्रमागत pin_type type;
	अचिन्हित दीर्घ reg;
	अचिन्हित दीर्घ bit_offset;
	अचिन्हित दीर्घ bit_width;
पूर्ण;

/**
 * काष्ठा sprd_pin_group: represent one group's description
 * @name: group name
 * @npins: pin numbers of this group
 * @pins: poपूर्णांकer to pins array
 */
काष्ठा sprd_pin_group अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक npins;
	अचिन्हित पूर्णांक *pins;
पूर्ण;

/**
 * काष्ठा sprd_pinctrl_soc_info: represent the SoC's pins description
 * @groups: poपूर्णांकer to groups of pins
 * @ngroups: group numbers of the whole SoC
 * @pins: poपूर्णांकer to pins description
 * @npins: pin numbers of the whole SoC
 * @grp_names: poपूर्णांकer to group names array
 */
काष्ठा sprd_pinctrl_soc_info अणु
	काष्ठा sprd_pin_group *groups;
	अचिन्हित पूर्णांक ngroups;
	काष्ठा sprd_pin *pins;
	अचिन्हित पूर्णांक npins;
	स्थिर अक्षर **grp_names;
पूर्ण;

/**
 * काष्ठा sprd_pinctrl: represent the pin controller device
 * @dev: poपूर्णांकer to the device काष्ठाure
 * @pctl: poपूर्णांकer to the pinctrl handle
 * @base: base address of the controller
 * @info: poपूर्णांकer to SoC's pins description inक्रमmation
 */
काष्ठा sprd_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
	व्योम __iomem *base;
	काष्ठा sprd_pinctrl_soc_info *info;
पूर्ण;

#घोषणा SPRD_PIN_CONFIG_CONTROL		(PIN_CONFIG_END + 1)
#घोषणा SPRD_PIN_CONFIG_SLEEP_MODE	(PIN_CONFIG_END + 2)

अटल पूर्णांक sprd_pinctrl_get_id_by_name(काष्ठा sprd_pinctrl *sprd_pctl,
				       स्थिर अक्षर *name)
अणु
	काष्ठा sprd_pinctrl_soc_info *info = sprd_pctl->info;
	पूर्णांक i;

	क्रम (i = 0; i < info->npins; i++) अणु
		अगर (!म_भेद(info->pins[i].name, name))
			वापस info->pins[i].number;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल काष्ठा sprd_pin *
sprd_pinctrl_get_pin_by_id(काष्ठा sprd_pinctrl *sprd_pctl, अचिन्हित पूर्णांक id)
अणु
	काष्ठा sprd_pinctrl_soc_info *info = sprd_pctl->info;
	काष्ठा sprd_pin *pin = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < info->npins; i++) अणु
		अगर (info->pins[i].number == id) अणु
			pin = &info->pins[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस pin;
पूर्ण

अटल स्थिर काष्ठा sprd_pin_group *
sprd_pinctrl_find_group_by_name(काष्ठा sprd_pinctrl *sprd_pctl,
				स्थिर अक्षर *name)
अणु
	काष्ठा sprd_pinctrl_soc_info *info = sprd_pctl->info;
	स्थिर काष्ठा sprd_pin_group *grp = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < info->ngroups; i++) अणु
		अगर (!म_भेद(info->groups[i].name, name)) अणु
			grp = &info->groups[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस grp;
पूर्ण

अटल पूर्णांक sprd_pctrl_group_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sprd_pinctrl_soc_info *info = pctl->info;

	वापस info->ngroups;
पूर्ण

अटल स्थिर अक्षर *sprd_pctrl_group_name(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित पूर्णांक selector)
अणु
	काष्ठा sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sprd_pinctrl_soc_info *info = pctl->info;

	वापस info->groups[selector].name;
पूर्ण

अटल पूर्णांक sprd_pctrl_group_pins(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक selector,
				 स्थिर अचिन्हित पूर्णांक **pins,
				 अचिन्हित पूर्णांक *npins)
अणु
	काष्ठा sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sprd_pinctrl_soc_info *info = pctl->info;

	अगर (selector >= info->ngroups)
		वापस -EINVAL;

	*pins = info->groups[selector].pins;
	*npins = info->groups[selector].npins;

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
			       काष्ठा device_node *np,
			       काष्ठा pinctrl_map **map,
			       अचिन्हित पूर्णांक *num_maps)
अणु
	काष्ठा sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा sprd_pin_group *grp;
	अचिन्हित दीर्घ *configs = शून्य;
	अचिन्हित पूर्णांक num_configs = 0;
	अचिन्हित पूर्णांक reserved_maps = 0;
	अचिन्हित पूर्णांक reserve = 0;
	स्थिर अक्षर *function;
	क्रमागत pinctrl_map_type type;
	पूर्णांक ret;

	grp = sprd_pinctrl_find_group_by_name(pctl, np->name);
	अगर (!grp) अणु
		dev_err(pctl->dev, "unable to find group for node %s\n",
			of_node_full_name(np));
		वापस -EINVAL;
	पूर्ण

	ret = of_property_count_strings(np, "pins");
	अगर (ret < 0)
		वापस ret;

	अगर (ret == 1)
		type = PIN_MAP_TYPE_CONFIGS_PIN;
	अन्यथा
		type = PIN_MAP_TYPE_CONFIGS_GROUP;

	ret = of_property_पढ़ो_string(np, "function", &function);
	अगर (ret < 0) अणु
		अगर (ret != -EINVAL)
			dev_err(pctl->dev,
				"%s: could not parse property function\n",
				of_node_full_name(np));
		function = शून्य;
	पूर्ण

	ret = pinconf_generic_parse_dt_config(np, pctldev, &configs,
					      &num_configs);
	अगर (ret < 0) अणु
		dev_err(pctl->dev, "%s: could not parse node property\n",
			of_node_full_name(np));
		वापस ret;
	पूर्ण

	*map = शून्य;
	*num_maps = 0;

	अगर (function != शून्य)
		reserve++;
	अगर (num_configs)
		reserve++;

	ret = pinctrl_utils_reserve_map(pctldev, map, &reserved_maps,
					num_maps, reserve);
	अगर (ret < 0)
		जाओ out;

	अगर (function) अणु
		ret = pinctrl_utils_add_map_mux(pctldev, map,
						&reserved_maps, num_maps,
						grp->name, function);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (num_configs) अणु
		स्थिर अक्षर *group_or_pin;
		अचिन्हित पूर्णांक pin_id;

		अगर (type == PIN_MAP_TYPE_CONFIGS_PIN) अणु
			pin_id = grp->pins[0];
			group_or_pin = pin_get_name(pctldev, pin_id);
		पूर्ण अन्यथा अणु
			group_or_pin = grp->name;
		पूर्ण

		ret = pinctrl_utils_add_map_configs(pctldev, map,
						    &reserved_maps, num_maps,
						    group_or_pin, configs,
						    num_configs, type);
	पूर्ण

out:
	kमुक्त(configs);
	वापस ret;
पूर्ण

अटल व्योम sprd_pctrl_dbg_show(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
				अचिन्हित पूर्णांक offset)
अणु
	seq_म_लिखो(s, "%s", dev_name(pctldev->dev));
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops sprd_pctrl_ops = अणु
	.get_groups_count = sprd_pctrl_group_count,
	.get_group_name = sprd_pctrl_group_name,
	.get_group_pins = sprd_pctrl_group_pins,
	.pin_dbg_show = sprd_pctrl_dbg_show,
	.dt_node_to_map = sprd_dt_node_to_map,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक sprd_pmx_get_function_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस PIN_FUNC_MAX;
पूर्ण

अटल स्थिर अक्षर *sprd_pmx_get_function_name(काष्ठा pinctrl_dev *pctldev,
					      अचिन्हित पूर्णांक selector)
अणु
	चयन (selector) अणु
	हाल PIN_FUNC_1:
		वापस "func1";
	हाल PIN_FUNC_2:
		वापस "func2";
	हाल PIN_FUNC_3:
		वापस "func3";
	हाल PIN_FUNC_4:
		वापस "func4";
	शेष:
		वापस "null";
	पूर्ण
पूर्ण

अटल पूर्णांक sprd_pmx_get_function_groups(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक selector,
					स्थिर अक्षर * स्थिर **groups,
					अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	काष्ठा sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sprd_pinctrl_soc_info *info = pctl->info;

	*groups = info->grp_names;
	*num_groups = info->ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_pmx_set_mux(काष्ठा pinctrl_dev *pctldev,
			    अचिन्हित पूर्णांक func_selector,
			    अचिन्हित पूर्णांक group_selector)
अणु
	काष्ठा sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sprd_pinctrl_soc_info *info = pctl->info;
	काष्ठा sprd_pin_group *grp = &info->groups[group_selector];
	अचिन्हित पूर्णांक i, grp_pins = grp->npins;
	अचिन्हित दीर्घ reg;
	अचिन्हित पूर्णांक val = 0;

	अगर (group_selector >= info->ngroups)
		वापस -EINVAL;

	चयन (func_selector) अणु
	हाल PIN_FUNC_1:
		val &= PIN_FUNC_SEL_1;
		अवरोध;
	हाल PIN_FUNC_2:
		val |= PIN_FUNC_SEL_2;
		अवरोध;
	हाल PIN_FUNC_3:
		val |= PIN_FUNC_SEL_3;
		अवरोध;
	हाल PIN_FUNC_4:
		val |= PIN_FUNC_SEL_4;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < grp_pins; i++) अणु
		अचिन्हित पूर्णांक pin_id = grp->pins[i];
		काष्ठा sprd_pin *pin = sprd_pinctrl_get_pin_by_id(pctl, pin_id);

		अगर (!pin || pin->type != COMMON_PIN)
			जारी;

		reg = पढ़ोl((व्योम __iomem *)pin->reg);
		reg &= ~PIN_FUNC_MASK;
		reg |= val;
		ग_लिखोl(reg, (व्योम __iomem *)pin->reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops sprd_pmx_ops = अणु
	.get_functions_count = sprd_pmx_get_function_count,
	.get_function_name = sprd_pmx_get_function_name,
	.get_function_groups = sprd_pmx_get_function_groups,
	.set_mux = sprd_pmx_set_mux,
पूर्ण;

अटल पूर्णांक sprd_pinconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin_id,
			    अचिन्हित दीर्घ *config)
अणु
	काष्ठा sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sprd_pin *pin = sprd_pinctrl_get_pin_by_id(pctl, pin_id);
	अचिन्हित पूर्णांक param = pinconf_to_config_param(*config);
	अचिन्हित पूर्णांक reg, arg;

	अगर (!pin)
		वापस -EINVAL;

	अगर (pin->type == GLOBAL_CTRL_PIN) अणु
		reg = (पढ़ोl((व्योम __iomem *)pin->reg) >>
			   pin->bit_offset) & PINCTRL_BIT_MASK(pin->bit_width);
	पूर्ण अन्यथा अणु
		reg = पढ़ोl((व्योम __iomem *)pin->reg);
	पूर्ण

	अगर (pin->type == GLOBAL_CTRL_PIN &&
	    param == SPRD_PIN_CONFIG_CONTROL) अणु
		arg = reg;
	पूर्ण अन्यथा अगर (pin->type == COMMON_PIN || pin->type == MISC_PIN) अणु
		चयन (param) अणु
		हाल SPRD_PIN_CONFIG_SLEEP_MODE:
			arg = (reg >> SLEEP_MODE_SHIFT) & SLEEP_MODE_MASK;
			अवरोध;
		हाल PIN_CONFIG_INPUT_ENABLE:
			arg = (reg >> SLEEP_INPUT_SHIFT) & SLEEP_INPUT_MASK;
			अवरोध;
		हाल PIN_CONFIG_OUTPUT_ENABLE:
			arg = reg & SLEEP_OUTPUT_MASK;
			अवरोध;
		हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			अगर ((reg & SLEEP_OUTPUT) || (reg & SLEEP_INPUT))
				वापस -EINVAL;

			arg = 1;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			arg = (reg >> DRIVE_STRENGTH_SHIFT) &
				DRIVE_STRENGTH_MASK;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			/* combine sleep pull करोwn and pull करोwn config */
			arg = ((reg >> SLEEP_PULL_DOWN_SHIFT) &
			       SLEEP_PULL_DOWN_MASK) << 16;
			arg |= (reg >> PULL_DOWN_SHIFT) & PULL_DOWN_MASK;
			अवरोध;
		हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			arg = (reg >> INPUT_SCHMITT_SHIFT) & INPUT_SCHMITT_MASK;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			/* combine sleep pull up and pull up config */
			arg = ((reg >> SLEEP_PULL_UP_SHIFT) &
			       SLEEP_PULL_UP_MASK) << 16;
			arg |= (reg >> PULL_UP_SHIFT) & PULL_UP_MASK;
			अवरोध;
		हाल PIN_CONFIG_BIAS_DISABLE:
			अगर ((reg & (SLEEP_PULL_DOWN | SLEEP_PULL_UP)) ||
			    (reg & (PULL_DOWN | PULL_UP_4_7K | PULL_UP_20K)))
				वापस -EINVAL;

			arg = 1;
			अवरोध;
		हाल PIN_CONFIG_SLEEP_HARDWARE_STATE:
			arg = 0;
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक sprd_pinconf_drive(अचिन्हित पूर्णांक mA)
अणु
	अचिन्हित पूर्णांक val = 0;

	चयन (mA) अणु
	हाल 2:
		अवरोध;
	हाल 4:
		val |= BIT(19);
		अवरोध;
	हाल 6:
		val |= BIT(20);
		अवरोध;
	हाल 8:
		val |= BIT(19) | BIT(20);
		अवरोध;
	हाल 10:
		val |= BIT(21);
		अवरोध;
	हाल 12:
		val |= BIT(21) | BIT(19);
		अवरोध;
	हाल 14:
		val |= BIT(21) | BIT(20);
		अवरोध;
	हाल 16:
		val |= BIT(19) | BIT(20) | BIT(21);
		अवरोध;
	हाल 20:
		val |= BIT(22);
		अवरोध;
	हाल 21:
		val |= BIT(22) | BIT(19);
		अवरोध;
	हाल 24:
		val |= BIT(22) | BIT(20);
		अवरोध;
	हाल 25:
		val |= BIT(22) | BIT(20) | BIT(19);
		अवरोध;
	हाल 27:
		val |= BIT(22) | BIT(21);
		अवरोध;
	हाल 29:
		val |= BIT(22) | BIT(21) | BIT(19);
		अवरोध;
	हाल 31:
		val |= BIT(22) | BIT(21) | BIT(20);
		अवरोध;
	हाल 33:
		val |= BIT(22) | BIT(21) | BIT(20) | BIT(19);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

अटल bool sprd_pinctrl_check_sleep_config(अचिन्हित दीर्घ *configs,
					    अचिन्हित पूर्णांक num_configs)
अणु
	अचिन्हित पूर्णांक param;
	पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		अगर (param == PIN_CONFIG_SLEEP_HARDWARE_STATE)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक sprd_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin_id,
			    अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sprd_pin *pin = sprd_pinctrl_get_pin_by_id(pctl, pin_id);
	bool is_sleep_config;
	अचिन्हित दीर्घ reg;
	पूर्णांक i;

	अगर (!pin)
		वापस -EINVAL;

	is_sleep_config = sprd_pinctrl_check_sleep_config(configs, num_configs);

	क्रम (i = 0; i < num_configs; i++) अणु
		अचिन्हित पूर्णांक param, arg, shअगरt, mask, val;

		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		val = 0;
		shअगरt = 0;
		mask = 0;
		अगर (pin->type == GLOBAL_CTRL_PIN &&
		    param == SPRD_PIN_CONFIG_CONTROL) अणु
			val = arg;
		पूर्ण अन्यथा अगर (pin->type == COMMON_PIN || pin->type == MISC_PIN) अणु
			चयन (param) अणु
			हाल SPRD_PIN_CONFIG_SLEEP_MODE:
				अगर (arg & AP_SLEEP)
					val |= AP_SLEEP_MODE;
				अगर (arg & PUBCP_SLEEP)
					val |= PUBCP_SLEEP_MODE;
				अगर (arg & TGLDSP_SLEEP)
					val |= TGLDSP_SLEEP_MODE;
				अगर (arg & AGDSP_SLEEP)
					val |= AGDSP_SLEEP_MODE;
				अगर (arg & CM4_SLEEP)
					val |= CM4_SLEEP_MODE;

				mask = SLEEP_MODE_MASK;
				shअगरt = SLEEP_MODE_SHIFT;
				अवरोध;
			हाल PIN_CONFIG_INPUT_ENABLE:
				अगर (is_sleep_config == true) अणु
					अगर (arg > 0)
						val |= SLEEP_INPUT;
					अन्यथा
						val &= ~SLEEP_INPUT;

					mask = SLEEP_INPUT_MASK;
					shअगरt = SLEEP_INPUT_SHIFT;
				पूर्ण
				अवरोध;
			हाल PIN_CONFIG_OUTPUT_ENABLE:
				अगर (is_sleep_config == true) अणु
					अगर (arg > 0)
						val |= SLEEP_OUTPUT;
					अन्यथा
						val &= ~SLEEP_OUTPUT;

					mask = SLEEP_OUTPUT_MASK;
					shअगरt = SLEEP_OUTPUT_SHIFT;
				पूर्ण
				अवरोध;
			हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
				अगर (is_sleep_config == true) अणु
					val = shअगरt = 0;
					mask = SLEEP_OUTPUT | SLEEP_INPUT;
				पूर्ण
				अवरोध;
			हाल PIN_CONFIG_DRIVE_STRENGTH:
				अगर (arg < 2 || arg > 60)
					वापस -EINVAL;

				val = sprd_pinconf_drive(arg);
				mask = DRIVE_STRENGTH_MASK;
				shअगरt = DRIVE_STRENGTH_SHIFT;
				अवरोध;
			हाल PIN_CONFIG_BIAS_PULL_DOWN:
				अगर (is_sleep_config == true) अणु
					val |= SLEEP_PULL_DOWN;
					mask = SLEEP_PULL_DOWN_MASK;
					shअगरt = SLEEP_PULL_DOWN_SHIFT;
				पूर्ण अन्यथा अणु
					val |= PULL_DOWN;
					mask = PULL_DOWN_MASK;
					shअगरt = PULL_DOWN_SHIFT;
				पूर्ण
				अवरोध;
			हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
				अगर (arg > 0)
					val |= INPUT_SCHMITT;
				अन्यथा
					val &= ~INPUT_SCHMITT;

				mask = INPUT_SCHMITT_MASK;
				shअगरt = INPUT_SCHMITT_SHIFT;
				अवरोध;
			हाल PIN_CONFIG_BIAS_PULL_UP:
				अगर (is_sleep_config) अणु
					val |= SLEEP_PULL_UP;
					mask = SLEEP_PULL_UP_MASK;
					shअगरt = SLEEP_PULL_UP_SHIFT;
				पूर्ण अन्यथा अणु
					अगर (arg == 20000)
						val |= PULL_UP_20K;
					अन्यथा अगर (arg == 4700)
						val |= PULL_UP_4_7K;

					mask = PULL_UP_MASK;
					shअगरt = PULL_UP_SHIFT;
				पूर्ण
				अवरोध;
			हाल PIN_CONFIG_BIAS_DISABLE:
				अगर (is_sleep_config == true) अणु
					val = shअगरt = 0;
					mask = SLEEP_PULL_DOWN | SLEEP_PULL_UP;
				पूर्ण अन्यथा अणु
					val = shअगरt = 0;
					mask = PULL_DOWN | PULL_UP_20K |
						PULL_UP_4_7K;
				पूर्ण
				अवरोध;
			हाल PIN_CONFIG_SLEEP_HARDWARE_STATE:
				जारी;
			शेष:
				वापस -ENOTSUPP;
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस -ENOTSUPP;
		पूर्ण

		अगर (pin->type == GLOBAL_CTRL_PIN) अणु
			reg = पढ़ोl((व्योम __iomem *)pin->reg);
			reg &= ~(PINCTRL_BIT_MASK(pin->bit_width)
				<< pin->bit_offset);
			reg |= (val & PINCTRL_BIT_MASK(pin->bit_width))
				<< pin->bit_offset;
			ग_लिखोl(reg, (व्योम __iomem *)pin->reg);
		पूर्ण अन्यथा अणु
			reg = पढ़ोl((व्योम __iomem *)pin->reg);
			reg &= ~(mask << shअगरt);
			reg |= val;
			ग_लिखोl(reg, (व्योम __iomem *)pin->reg);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_pinconf_group_get(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक selector, अचिन्हित दीर्घ *config)
अणु
	काष्ठा sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sprd_pinctrl_soc_info *info = pctl->info;
	काष्ठा sprd_pin_group *grp;
	अचिन्हित पूर्णांक pin_id;

	अगर (selector >= info->ngroups)
		वापस -EINVAL;

	grp = &info->groups[selector];
	pin_id = grp->pins[0];

	वापस sprd_pinconf_get(pctldev, pin_id, config);
पूर्ण

अटल पूर्णांक sprd_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक selector,
				  अचिन्हित दीर्घ *configs,
				  अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sprd_pinctrl_soc_info *info = pctl->info;
	काष्ठा sprd_pin_group *grp;
	पूर्णांक ret, i;

	अगर (selector >= info->ngroups)
		वापस -EINVAL;

	grp = &info->groups[selector];

	क्रम (i = 0; i < grp->npins; i++) अणु
		अचिन्हित पूर्णांक pin_id = grp->pins[i];

		ret = sprd_pinconf_set(pctldev, pin_id, configs, num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_pinconf_get_config(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक pin_id,
				   अचिन्हित दीर्घ *config)
अणु
	काष्ठा sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sprd_pin *pin = sprd_pinctrl_get_pin_by_id(pctl, pin_id);

	अगर (!pin)
		वापस -EINVAL;

	अगर (pin->type == GLOBAL_CTRL_PIN) अणु
		*config = (पढ़ोl((व्योम __iomem *)pin->reg) >>
			   pin->bit_offset) & PINCTRL_BIT_MASK(pin->bit_width);
	पूर्ण अन्यथा अणु
		*config = पढ़ोl((व्योम __iomem *)pin->reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sprd_pinconf_dbg_show(काष्ठा pinctrl_dev *pctldev,
				  काष्ठा seq_file *s, अचिन्हित पूर्णांक pin_id)
अणु
	अचिन्हित दीर्घ config;
	पूर्णांक ret;

	ret = sprd_pinconf_get_config(pctldev, pin_id, &config);
	अगर (ret)
		वापस;

	seq_म_लिखो(s, "0x%lx", config);
पूर्ण

अटल व्योम sprd_pinconf_group_dbg_show(काष्ठा pinctrl_dev *pctldev,
					काष्ठा seq_file *s,
					अचिन्हित पूर्णांक selector)
अणु
	काष्ठा sprd_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sprd_pinctrl_soc_info *info = pctl->info;
	काष्ठा sprd_pin_group *grp;
	अचिन्हित दीर्घ config;
	स्थिर अक्षर *name;
	पूर्णांक i, ret;

	अगर (selector >= info->ngroups)
		वापस;

	grp = &info->groups[selector];

	seq_अ_दो(s, '\n');
	क्रम (i = 0; i < grp->npins; i++, config++) अणु
		अचिन्हित पूर्णांक pin_id = grp->pins[i];

		name = pin_get_name(pctldev, pin_id);
		ret = sprd_pinconf_get_config(pctldev, pin_id, &config);
		अगर (ret)
			वापस;

		seq_म_लिखो(s, "%s: 0x%lx ", name, config);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pinconf_ops sprd_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = sprd_pinconf_get,
	.pin_config_set = sprd_pinconf_set,
	.pin_config_group_get = sprd_pinconf_group_get,
	.pin_config_group_set = sprd_pinconf_group_set,
	.pin_config_dbg_show = sprd_pinconf_dbg_show,
	.pin_config_group_dbg_show = sprd_pinconf_group_dbg_show,
पूर्ण;

अटल स्थिर काष्ठा pinconf_generic_params sprd_dt_params[] = अणु
	अणु"sprd,control", SPRD_PIN_CONFIG_CONTROL, 0पूर्ण,
	अणु"sprd,sleep-mode", SPRD_PIN_CONFIG_SLEEP_MODE, 0पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर काष्ठा pin_config_item sprd_conf_items[] = अणु
	PCONFDUMP(SPRD_PIN_CONFIG_CONTROL, "global control", शून्य, true),
	PCONFDUMP(SPRD_PIN_CONFIG_SLEEP_MODE, "sleep mode", शून्य, true),
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा pinctrl_desc sprd_pinctrl_desc = अणु
	.pctlops = &sprd_pctrl_ops,
	.pmxops = &sprd_pmx_ops,
	.confops = &sprd_pinconf_ops,
	.num_custom_params = ARRAY_SIZE(sprd_dt_params),
	.custom_params = sprd_dt_params,
#अगर_घोषित CONFIG_DEBUG_FS
	.custom_conf_items = sprd_conf_items,
#पूर्ण_अगर
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक sprd_pinctrl_parse_groups(काष्ठा device_node *np,
				     काष्ठा sprd_pinctrl *sprd_pctl,
				     काष्ठा sprd_pin_group *grp)
अणु
	काष्ठा property *prop;
	स्थिर अक्षर *pin_name;
	पूर्णांक ret, i = 0;

	ret = of_property_count_strings(np, "pins");
	अगर (ret < 0)
		वापस ret;

	grp->name = np->name;
	grp->npins = ret;
	grp->pins = devm_kसुस्मृति(sprd_pctl->dev,
				 grp->npins, माप(अचिन्हित पूर्णांक),
				 GFP_KERNEL);
	अगर (!grp->pins)
		वापस -ENOMEM;

	of_property_क्रम_each_string(np, "pins", prop, pin_name) अणु
		ret = sprd_pinctrl_get_id_by_name(sprd_pctl, pin_name);
		अगर (ret >= 0)
			grp->pins[i++] = ret;
	पूर्ण

	क्रम (i = 0; i < grp->npins; i++) अणु
		dev_dbg(sprd_pctl->dev,
			"Group[%s] contains [%d] pins: id = %d\n",
			grp->name, grp->npins, grp->pins[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक sprd_pinctrl_get_groups(काष्ठा device_node *np)
अणु
	काष्ठा device_node *child;
	अचिन्हित पूर्णांक group_cnt, cnt;

	group_cnt = of_get_child_count(np);

	क्रम_each_child_of_node(np, child) अणु
		cnt = of_get_child_count(child);
		अगर (cnt > 0)
			group_cnt += cnt;
	पूर्ण

	वापस group_cnt;
पूर्ण

अटल पूर्णांक sprd_pinctrl_parse_dt(काष्ठा sprd_pinctrl *sprd_pctl)
अणु
	काष्ठा sprd_pinctrl_soc_info *info = sprd_pctl->info;
	काष्ठा device_node *np = sprd_pctl->dev->of_node;
	काष्ठा device_node *child, *sub_child;
	काष्ठा sprd_pin_group *grp;
	स्थिर अक्षर **temp;
	पूर्णांक ret;

	अगर (!np)
		वापस -ENODEV;

	info->ngroups = sprd_pinctrl_get_groups(np);
	अगर (!info->ngroups)
		वापस 0;

	info->groups = devm_kसुस्मृति(sprd_pctl->dev,
				    info->ngroups,
				    माप(काष्ठा sprd_pin_group),
				    GFP_KERNEL);
	अगर (!info->groups)
		वापस -ENOMEM;

	info->grp_names = devm_kसुस्मृति(sprd_pctl->dev,
				       info->ngroups, माप(अक्षर *),
				       GFP_KERNEL);
	अगर (!info->grp_names)
		वापस -ENOMEM;

	temp = info->grp_names;
	grp = info->groups;

	क्रम_each_child_of_node(np, child) अणु
		ret = sprd_pinctrl_parse_groups(child, sprd_pctl, grp);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण

		*temp++ = grp->name;
		grp++;

		अगर (of_get_child_count(child) > 0) अणु
			क्रम_each_child_of_node(child, sub_child) अणु
				ret = sprd_pinctrl_parse_groups(sub_child,
								sprd_pctl, grp);
				अगर (ret) अणु
					of_node_put(sub_child);
					of_node_put(child);
					वापस ret;
				पूर्ण

				*temp++ = grp->name;
				grp++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_pinctrl_add_pins(काष्ठा sprd_pinctrl *sprd_pctl,
				 काष्ठा sprd_pins_info *sprd_soc_pin_info,
				 पूर्णांक pins_cnt)
अणु
	काष्ठा sprd_pinctrl_soc_info *info = sprd_pctl->info;
	अचिन्हित पूर्णांक ctrl_pin = 0, com_pin = 0;
	काष्ठा sprd_pin *pin;
	पूर्णांक i;

	info->npins = pins_cnt;
	info->pins = devm_kसुस्मृति(sprd_pctl->dev,
				  info->npins, माप(काष्ठा sprd_pin),
				  GFP_KERNEL);
	अगर (!info->pins)
		वापस -ENOMEM;

	क्रम (i = 0, pin = info->pins; i < info->npins; i++, pin++) अणु
		अचिन्हित पूर्णांक reg;

		pin->name = sprd_soc_pin_info[i].name;
		pin->type = sprd_soc_pin_info[i].type;
		pin->number = sprd_soc_pin_info[i].num;
		reg = sprd_soc_pin_info[i].reg;
		अगर (pin->type == GLOBAL_CTRL_PIN) अणु
			pin->reg = (अचिन्हित दीर्घ)sprd_pctl->base +
				PINCTRL_REG_LEN * reg;
			pin->bit_offset = sprd_soc_pin_info[i].bit_offset;
			pin->bit_width = sprd_soc_pin_info[i].bit_width;
			ctrl_pin++;
		पूर्ण अन्यथा अगर (pin->type == COMMON_PIN) अणु
			pin->reg = (अचिन्हित दीर्घ)sprd_pctl->base +
				PINCTRL_REG_OFFSET + PINCTRL_REG_LEN *
				(i - ctrl_pin);
			com_pin++;
		पूर्ण अन्यथा अगर (pin->type == MISC_PIN) अणु
			pin->reg = (अचिन्हित दीर्घ)sprd_pctl->base +
				PINCTRL_REG_MISC_OFFSET + PINCTRL_REG_LEN *
				(i - ctrl_pin - com_pin);
		पूर्ण
	पूर्ण

	क्रम (i = 0, pin = info->pins; i < info->npins; pin++, i++) अणु
		dev_dbg(sprd_pctl->dev, "pin name[%s-%d], type = %d, "
			"bit offset = %ld, bit width = %ld, reg = 0x%lx\n",
			pin->name, pin->number, pin->type,
			pin->bit_offset, pin->bit_width, pin->reg);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sprd_pinctrl_core_probe(काष्ठा platक्रमm_device *pdev,
			    काष्ठा sprd_pins_info *sprd_soc_pin_info,
			    पूर्णांक pins_cnt)
अणु
	काष्ठा sprd_pinctrl *sprd_pctl;
	काष्ठा sprd_pinctrl_soc_info *pinctrl_info;
	काष्ठा pinctrl_pin_desc *pin_desc;
	पूर्णांक ret, i;

	sprd_pctl = devm_kzalloc(&pdev->dev, माप(काष्ठा sprd_pinctrl),
				 GFP_KERNEL);
	अगर (!sprd_pctl)
		वापस -ENOMEM;

	sprd_pctl->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sprd_pctl->base))
		वापस PTR_ERR(sprd_pctl->base);

	pinctrl_info = devm_kzalloc(&pdev->dev,
				    माप(काष्ठा sprd_pinctrl_soc_info),
				    GFP_KERNEL);
	अगर (!pinctrl_info)
		वापस -ENOMEM;

	sprd_pctl->info = pinctrl_info;
	sprd_pctl->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, sprd_pctl);

	ret = sprd_pinctrl_add_pins(sprd_pctl, sprd_soc_pin_info, pins_cnt);
	अगर (ret) अणु
		dev_err(&pdev->dev, "fail to add pins information\n");
		वापस ret;
	पूर्ण

	ret = sprd_pinctrl_parse_dt(sprd_pctl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "fail to parse dt properties\n");
		वापस ret;
	पूर्ण

	pin_desc = devm_kसुस्मृति(&pdev->dev,
				pinctrl_info->npins,
				माप(काष्ठा pinctrl_pin_desc),
				GFP_KERNEL);
	अगर (!pin_desc)
		वापस -ENOMEM;

	क्रम (i = 0; i < pinctrl_info->npins; i++) अणु
		pin_desc[i].number = pinctrl_info->pins[i].number;
		pin_desc[i].name = pinctrl_info->pins[i].name;
		pin_desc[i].drv_data = pinctrl_info;
	पूर्ण

	sprd_pinctrl_desc.pins = pin_desc;
	sprd_pinctrl_desc.name = dev_name(&pdev->dev);
	sprd_pinctrl_desc.npins = pinctrl_info->npins;

	sprd_pctl->pctl = pinctrl_रेजिस्टर(&sprd_pinctrl_desc,
					   &pdev->dev, (व्योम *)sprd_pctl);
	अगर (IS_ERR(sprd_pctl->pctl)) अणु
		dev_err(&pdev->dev, "could not register pinctrl driver\n");
		वापस PTR_ERR(sprd_pctl->pctl);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sprd_pinctrl_core_probe);

पूर्णांक sprd_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sprd_pinctrl *sprd_pctl = platक्रमm_get_drvdata(pdev);

	pinctrl_unरेजिस्टर(sprd_pctl->pctl);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sprd_pinctrl_हटाओ);

व्योम sprd_pinctrl_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pinctrl *pinctl;
	काष्ठा pinctrl_state *state;

	pinctl = devm_pinctrl_get(&pdev->dev);
	अगर (IS_ERR(pinctl))
		वापस;
	state = pinctrl_lookup_state(pinctl, "shutdown");
	अगर (IS_ERR(state))
		वापस;
	pinctrl_select_state(pinctl, state);
पूर्ण
EXPORT_SYMBOL_GPL(sprd_pinctrl_shutकरोwn);

MODULE_DESCRIPTION("SPREADTRUM Pin Controller Driver");
MODULE_AUTHOR("Baolin Wang <baolin.wang@spreadtrum.com>");
MODULE_LICENSE("GPL v2");
