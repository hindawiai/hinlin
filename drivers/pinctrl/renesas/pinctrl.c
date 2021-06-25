<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH Pin Function Controller pinmux support.
 *
 * Copyright (C) 2012  Paul Mundt
 */

#घोषणा DRV_NAME "sh-pfc"

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "core.h"
#समावेश "../core.h"
#समावेश "../pinconf.h"

काष्ठा sh_pfc_pin_config अणु
	u16 gpio_enabled:1;
	u16 mux_mark:15;
पूर्ण;

काष्ठा sh_pfc_pinctrl अणु
	काष्ठा pinctrl_dev *pctl;
	काष्ठा pinctrl_desc pctl_desc;

	काष्ठा sh_pfc *pfc;

	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा sh_pfc_pin_config *configs;

	स्थिर अक्षर *func_prop_name;
	स्थिर अक्षर *groups_prop_name;
	स्थिर अक्षर *pins_prop_name;
पूर्ण;

अटल पूर्णांक sh_pfc_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->pfc->info->nr_groups;
पूर्ण

अटल स्थिर अक्षर *sh_pfc_get_group_name(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित selector)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->pfc->info->groups[selector].name;
पूर्ण

अटल पूर्णांक sh_pfc_get_group_pins(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
				 स्थिर अचिन्हित **pins, अचिन्हित *num_pins)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);

	*pins = pmx->pfc->info->groups[selector].pins;
	*num_pins = pmx->pfc->info->groups[selector].nr_pins;

	वापस 0;
पूर्ण

अटल व्योम sh_pfc_pin_dbg_show(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
				अचिन्हित offset)
अणु
	seq_माला_दो(s, DRV_NAME);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक sh_pfc_map_add_config(काष्ठा pinctrl_map *map,
				 स्थिर अक्षर *group_or_pin,
				 क्रमागत pinctrl_map_type type,
				 अचिन्हित दीर्घ *configs,
				 अचिन्हित पूर्णांक num_configs)
अणु
	अचिन्हित दीर्घ *cfgs;

	cfgs = kmemdup(configs, num_configs * माप(*cfgs),
		       GFP_KERNEL);
	अगर (cfgs == शून्य)
		वापस -ENOMEM;

	map->type = type;
	map->data.configs.group_or_pin = group_or_pin;
	map->data.configs.configs = cfgs;
	map->data.configs.num_configs = num_configs;

	वापस 0;
पूर्ण

अटल पूर्णांक sh_pfc_dt_subnode_to_map(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा device_node *np,
				    काष्ठा pinctrl_map **map,
				    अचिन्हित पूर्णांक *num_maps, अचिन्हित पूर्णांक *index)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा device *dev = pmx->pfc->dev;
	काष्ठा pinctrl_map *maps = *map;
	अचिन्हित पूर्णांक nmaps = *num_maps;
	अचिन्हित पूर्णांक idx = *index;
	अचिन्हित पूर्णांक num_configs;
	स्थिर अक्षर *function = शून्य;
	अचिन्हित दीर्घ *configs;
	काष्ठा property *prop;
	अचिन्हित पूर्णांक num_groups;
	अचिन्हित पूर्णांक num_pins;
	स्थिर अक्षर *group;
	स्थिर अक्षर *pin;
	पूर्णांक ret;

	/* Support both the old Renesas-specअगरic properties and the new standard
	 * properties. Mixing old and new properties isn't allowed, neither
	 * inside a subnode nor across subnodes.
	 */
	अगर (!pmx->func_prop_name) अणु
		अगर (of_find_property(np, "groups", शून्य) ||
		    of_find_property(np, "pins", शून्य)) अणु
			pmx->func_prop_name = "function";
			pmx->groups_prop_name = "groups";
			pmx->pins_prop_name = "pins";
		पूर्ण अन्यथा अणु
			pmx->func_prop_name = "renesas,function";
			pmx->groups_prop_name = "renesas,groups";
			pmx->pins_prop_name = "renesas,pins";
		पूर्ण
	पूर्ण

	/* Parse the function and configuration properties. At least a function
	 * or one configuration must be specअगरied.
	 */
	ret = of_property_पढ़ो_string(np, pmx->func_prop_name, &function);
	अगर (ret < 0 && ret != -EINVAL) अणु
		dev_err(dev, "Invalid function in DT\n");
		वापस ret;
	पूर्ण

	ret = pinconf_generic_parse_dt_config(np, शून्य, &configs, &num_configs);
	अगर (ret < 0)
		वापस ret;

	अगर (!function && num_configs == 0) अणु
		dev_err(dev,
			"DT node must contain at least a function or config\n");
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	/* Count the number of pins and groups and पुनः_स्मृतिate mappings. */
	ret = of_property_count_strings(np, pmx->pins_prop_name);
	अगर (ret == -EINVAL) अणु
		num_pins = 0;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		dev_err(dev, "Invalid pins list in DT\n");
		जाओ करोne;
	पूर्ण अन्यथा अणु
		num_pins = ret;
	पूर्ण

	ret = of_property_count_strings(np, pmx->groups_prop_name);
	अगर (ret == -EINVAL) अणु
		num_groups = 0;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		dev_err(dev, "Invalid pin groups list in DT\n");
		जाओ करोne;
	पूर्ण अन्यथा अणु
		num_groups = ret;
	पूर्ण

	अगर (!num_pins && !num_groups) अणु
		dev_err(dev, "No pin or group provided in DT node\n");
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	अगर (function)
		nmaps += num_groups;
	अगर (configs)
		nmaps += num_pins + num_groups;

	maps = kपुनः_स्मृति(maps, माप(*maps) * nmaps, GFP_KERNEL);
	अगर (maps == शून्य) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	*map = maps;
	*num_maps = nmaps;

	/* Iterate over pins and groups and create the mappings. */
	of_property_क्रम_each_string(np, pmx->groups_prop_name, prop, group) अणु
		अगर (function) अणु
			maps[idx].type = PIN_MAP_TYPE_MUX_GROUP;
			maps[idx].data.mux.group = group;
			maps[idx].data.mux.function = function;
			idx++;
		पूर्ण

		अगर (configs) अणु
			ret = sh_pfc_map_add_config(&maps[idx], group,
						    PIN_MAP_TYPE_CONFIGS_GROUP,
						    configs, num_configs);
			अगर (ret < 0)
				जाओ करोne;

			idx++;
		पूर्ण
	पूर्ण

	अगर (!configs) अणु
		ret = 0;
		जाओ करोne;
	पूर्ण

	of_property_क्रम_each_string(np, pmx->pins_prop_name, prop, pin) अणु
		ret = sh_pfc_map_add_config(&maps[idx], pin,
					    PIN_MAP_TYPE_CONFIGS_PIN,
					    configs, num_configs);
		अगर (ret < 0)
			जाओ करोne;

		idx++;
	पूर्ण

करोne:
	*index = idx;
	kमुक्त(configs);
	वापस ret;
पूर्ण

अटल व्योम sh_pfc_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
			       काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
	अचिन्हित पूर्णांक i;

	अगर (map == शून्य)
		वापस;

	क्रम (i = 0; i < num_maps; ++i) अणु
		अगर (map[i].type == PIN_MAP_TYPE_CONFIGS_GROUP ||
		    map[i].type == PIN_MAP_TYPE_CONFIGS_PIN)
			kमुक्त(map[i].data.configs.configs);
	पूर्ण

	kमुक्त(map);
पूर्ण

अटल पूर्णांक sh_pfc_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा device_node *np,
				 काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा device *dev = pmx->pfc->dev;
	काष्ठा device_node *child;
	अचिन्हित पूर्णांक index;
	पूर्णांक ret;

	*map = शून्य;
	*num_maps = 0;
	index = 0;

	क्रम_each_child_of_node(np, child) अणु
		ret = sh_pfc_dt_subnode_to_map(pctldev, child, map, num_maps,
					       &index);
		अगर (ret < 0) अणु
			of_node_put(child);
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* If no mapping has been found in child nodes try the config node. */
	अगर (*num_maps == 0) अणु
		ret = sh_pfc_dt_subnode_to_map(pctldev, np, map, num_maps,
					       &index);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	अगर (*num_maps)
		वापस 0;

	dev_err(dev, "no mapping found in node %pOF\n", np);
	ret = -EINVAL;

करोne:
	अगर (ret < 0)
		sh_pfc_dt_मुक्त_map(pctldev, *map, *num_maps);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल स्थिर काष्ठा pinctrl_ops sh_pfc_pinctrl_ops = अणु
	.get_groups_count	= sh_pfc_get_groups_count,
	.get_group_name		= sh_pfc_get_group_name,
	.get_group_pins		= sh_pfc_get_group_pins,
	.pin_dbg_show		= sh_pfc_pin_dbg_show,
#अगर_घोषित CONFIG_OF
	.dt_node_to_map		= sh_pfc_dt_node_to_map,
	.dt_मुक्त_map		= sh_pfc_dt_मुक्त_map,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक sh_pfc_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->pfc->info->nr_functions;
पूर्ण

अटल स्थिर अक्षर *sh_pfc_get_function_name(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित selector)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->pfc->info->functions[selector].name;
पूर्ण

अटल पूर्णांक sh_pfc_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित selector,
				      स्थिर अक्षर * स्थिर **groups,
				      अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);

	*groups = pmx->pfc->info->functions[selector].groups;
	*num_groups = pmx->pfc->info->functions[selector].nr_groups;

	वापस 0;
पूर्ण

अटल पूर्णांक sh_pfc_func_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
			       अचिन्हित group)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sh_pfc *pfc = pmx->pfc;
	स्थिर काष्ठा sh_pfc_pin_group *grp = &pfc->info->groups[group];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	dev_dbg(pctldev->dev, "Configuring pin group %s\n", grp->name);

	spin_lock_irqsave(&pfc->lock, flags);

	क्रम (i = 0; i < grp->nr_pins; ++i) अणु
		पूर्णांक idx = sh_pfc_get_pin_index(pfc, grp->pins[i]);
		काष्ठा sh_pfc_pin_config *cfg = &pmx->configs[idx];

		/*
		 * This driver cannot manage both gpio and mux when the gpio
		 * pin is alपढ़ोy enabled. So, this function fails.
		 */
		अगर (cfg->gpio_enabled) अणु
			ret = -EBUSY;
			जाओ करोne;
		पूर्ण

		ret = sh_pfc_config_mux(pfc, grp->mux[i], PINMUX_TYPE_FUNCTION);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	/* All group pins are configured, mark the pins as muxed */
	क्रम (i = 0; i < grp->nr_pins; ++i) अणु
		पूर्णांक idx = sh_pfc_get_pin_index(pfc, grp->pins[i]);
		काष्ठा sh_pfc_pin_config *cfg = &pmx->configs[idx];

		cfg->mux_mark = grp->mux[i];
	पूर्ण

करोne:
	spin_unlock_irqrestore(&pfc->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक sh_pfc_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा pinctrl_gpio_range *range,
				      अचिन्हित offset)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sh_pfc *pfc = pmx->pfc;
	पूर्णांक idx = sh_pfc_get_pin_index(pfc, offset);
	काष्ठा sh_pfc_pin_config *cfg = &pmx->configs[idx];
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&pfc->lock, flags);

	अगर (!pfc->gpio) अणु
		/* If GPIOs are handled बाह्यally the pin mux type needs to be
		 * set to GPIO here.
		 */
		स्थिर काष्ठा sh_pfc_pin *pin = &pfc->info->pins[idx];

		ret = sh_pfc_config_mux(pfc, pin->क्रमागत_id, PINMUX_TYPE_GPIO);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	cfg->gpio_enabled = true;

	ret = 0;

करोne:
	spin_unlock_irqrestore(&pfc->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम sh_pfc_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा pinctrl_gpio_range *range,
				     अचिन्हित offset)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sh_pfc *pfc = pmx->pfc;
	पूर्णांक idx = sh_pfc_get_pin_index(pfc, offset);
	काष्ठा sh_pfc_pin_config *cfg = &pmx->configs[idx];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pfc->lock, flags);
	cfg->gpio_enabled = false;
	/* If mux is alपढ़ोy set, this configures it here */
	अगर (cfg->mux_mark)
		sh_pfc_config_mux(pfc, cfg->mux_mark, PINMUX_TYPE_FUNCTION);
	spin_unlock_irqrestore(&pfc->lock, flags);
पूर्ण

#अगर_घोषित CONFIG_PINCTRL_SH_PFC_GPIO
अटल पूर्णांक sh_pfc_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा pinctrl_gpio_range *range,
				     अचिन्हित offset, bool input)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sh_pfc *pfc = pmx->pfc;
	पूर्णांक new_type = input ? PINMUX_TYPE_INPUT : PINMUX_TYPE_OUTPUT;
	पूर्णांक idx = sh_pfc_get_pin_index(pfc, offset);
	स्थिर काष्ठा sh_pfc_pin *pin = &pfc->info->pins[idx];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक dir;
	पूर्णांक ret;

	/* Check अगर the requested direction is supported by the pin. Not all
	 * SoCs provide pin config data, so perक्रमm the check conditionally.
	 */
	अगर (pin->configs) अणु
		dir = input ? SH_PFC_PIN_CFG_INPUT : SH_PFC_PIN_CFG_OUTPUT;
		अगर (!(pin->configs & dir))
			वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&pfc->lock, flags);
	ret = sh_pfc_config_mux(pfc, pin->क्रमागत_id, new_type);
	spin_unlock_irqrestore(&pfc->lock, flags);
	वापस ret;
पूर्ण
#अन्यथा
#घोषणा sh_pfc_gpio_set_direction	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा pinmux_ops sh_pfc_pinmux_ops = अणु
	.get_functions_count	= sh_pfc_get_functions_count,
	.get_function_name	= sh_pfc_get_function_name,
	.get_function_groups	= sh_pfc_get_function_groups,
	.set_mux		= sh_pfc_func_set_mux,
	.gpio_request_enable	= sh_pfc_gpio_request_enable,
	.gpio_disable_मुक्त	= sh_pfc_gpio_disable_मुक्त,
	.gpio_set_direction	= sh_pfc_gpio_set_direction,
पूर्ण;

अटल u32 sh_pfc_pinconf_find_drive_strength_reg(काष्ठा sh_pfc *pfc,
		अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक *offset, अचिन्हित पूर्णांक *size)
अणु
	स्थिर काष्ठा pinmux_drive_reg_field *field;
	स्थिर काष्ठा pinmux_drive_reg *reg;
	अचिन्हित पूर्णांक i;

	क्रम (reg = pfc->info->drive_regs; reg->reg; ++reg) अणु
		क्रम (i = 0; i < ARRAY_SIZE(reg->fields); ++i) अणु
			field = &reg->fields[i];

			अगर (field->size && field->pin == pin) अणु
				*offset = field->offset;
				*size = field->size;

				वापस reg->reg;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sh_pfc_pinconf_get_drive_strength(काष्ठा sh_pfc *pfc,
					     अचिन्हित पूर्णांक pin)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक size;
	u32 reg;
	u32 val;

	reg = sh_pfc_pinconf_find_drive_strength_reg(pfc, pin, &offset, &size);
	अगर (!reg)
		वापस -EINVAL;

	spin_lock_irqsave(&pfc->lock, flags);
	val = sh_pfc_पढ़ो(pfc, reg);
	spin_unlock_irqrestore(&pfc->lock, flags);

	val = (val >> offset) & GENMASK(size - 1, 0);

	/* Convert the value to mA based on a full drive strength value of 24mA.
	 * We can make the full value configurable later अगर needed.
	 */
	वापस (val + 1) * (size == 2 ? 6 : 3);
पूर्ण

अटल पूर्णांक sh_pfc_pinconf_set_drive_strength(काष्ठा sh_pfc *pfc,
					     अचिन्हित पूर्णांक pin, u16 strength)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक step;
	u32 reg;
	u32 val;

	reg = sh_pfc_pinconf_find_drive_strength_reg(pfc, pin, &offset, &size);
	अगर (!reg)
		वापस -EINVAL;

	step = size == 2 ? 6 : 3;

	अगर (strength < step || strength > 24)
		वापस -EINVAL;

	/* Convert the value from mA based on a full drive strength value of
	 * 24mA. We can make the full value configurable later अगर needed.
	 */
	strength = strength / step - 1;

	spin_lock_irqsave(&pfc->lock, flags);

	val = sh_pfc_पढ़ो(pfc, reg);
	val &= ~GENMASK(offset + size - 1, offset);
	val |= strength << offset;

	sh_pfc_ग_लिखो(pfc, reg, val);

	spin_unlock_irqrestore(&pfc->lock, flags);

	वापस 0;
पूर्ण

/* Check whether the requested parameter is supported क्रम a pin. */
अटल bool sh_pfc_pinconf_validate(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक _pin,
				    क्रमागत pin_config_param param)
अणु
	पूर्णांक idx = sh_pfc_get_pin_index(pfc, _pin);
	स्थिर काष्ठा sh_pfc_pin *pin = &pfc->info->pins[idx];

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		वापस pin->configs & SH_PFC_PIN_CFG_PULL_UP_DOWN;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		वापस pin->configs & SH_PFC_PIN_CFG_PULL_UP;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		वापस pin->configs & SH_PFC_PIN_CFG_PULL_DOWN;

	हाल PIN_CONFIG_DRIVE_STRENGTH:
		वापस pin->configs & SH_PFC_PIN_CFG_DRIVE_STRENGTH;

	हाल PIN_CONFIG_POWER_SOURCE:
		वापस pin->configs & SH_PFC_PIN_CFG_IO_VOLTAGE;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक sh_pfc_pinconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित _pin,
			      अचिन्हित दीर्घ *config)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sh_pfc *pfc = pmx->pfc;
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक arg;

	अगर (!sh_pfc_pinconf_validate(pfc, _pin, param))
		वापस -ENOTSUPP;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN: अणु
		अचिन्हित पूर्णांक bias;

		अगर (!pfc->info->ops || !pfc->info->ops->get_bias)
			वापस -ENOTSUPP;

		spin_lock_irqsave(&pfc->lock, flags);
		bias = pfc->info->ops->get_bias(pfc, _pin);
		spin_unlock_irqrestore(&pfc->lock, flags);

		अगर (bias != param)
			वापस -EINVAL;

		arg = 0;
		अवरोध;
	पूर्ण

	हाल PIN_CONFIG_DRIVE_STRENGTH: अणु
		पूर्णांक ret;

		ret = sh_pfc_pinconf_get_drive_strength(pfc, _pin);
		अगर (ret < 0)
			वापस ret;

		arg = ret;
		अवरोध;
	पूर्ण

	हाल PIN_CONFIG_POWER_SOURCE: अणु
		पूर्णांक idx = sh_pfc_get_pin_index(pfc, _pin);
		स्थिर काष्ठा sh_pfc_pin *pin = &pfc->info->pins[idx];
		अचिन्हित पूर्णांक lower_voltage;
		u32 pocctrl, val;
		पूर्णांक bit;

		अगर (!pfc->info->ops || !pfc->info->ops->pin_to_pocctrl)
			वापस -ENOTSUPP;

		bit = pfc->info->ops->pin_to_pocctrl(pfc, _pin, &pocctrl);
		अगर (WARN(bit < 0, "invalid pin %#x", _pin))
			वापस bit;

		spin_lock_irqsave(&pfc->lock, flags);
		val = sh_pfc_पढ़ो(pfc, pocctrl);
		spin_unlock_irqrestore(&pfc->lock, flags);

		lower_voltage = (pin->configs & SH_PFC_PIN_VOLTAGE_25_33) ?
			2500 : 1800;

		arg = (val & BIT(bit)) ? 3300 : lower_voltage;
		अवरोध;
	पूर्ण

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_pfc_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित _pin,
			      अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sh_pfc *pfc = pmx->pfc;
	क्रमागत pin_config_param param;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);

		अगर (!sh_pfc_pinconf_validate(pfc, _pin, param))
			वापस -ENOTSUPP;

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_UP:
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
		हाल PIN_CONFIG_BIAS_DISABLE:
			अगर (!pfc->info->ops || !pfc->info->ops->set_bias)
				वापस -ENOTSUPP;

			spin_lock_irqsave(&pfc->lock, flags);
			pfc->info->ops->set_bias(pfc, _pin, param);
			spin_unlock_irqrestore(&pfc->lock, flags);

			अवरोध;

		हाल PIN_CONFIG_DRIVE_STRENGTH: अणु
			अचिन्हित पूर्णांक arg =
				pinconf_to_config_argument(configs[i]);
			पूर्णांक ret;

			ret = sh_pfc_pinconf_set_drive_strength(pfc, _pin, arg);
			अगर (ret < 0)
				वापस ret;

			अवरोध;
		पूर्ण

		हाल PIN_CONFIG_POWER_SOURCE: अणु
			अचिन्हित पूर्णांक mV = pinconf_to_config_argument(configs[i]);
			पूर्णांक idx = sh_pfc_get_pin_index(pfc, _pin);
			स्थिर काष्ठा sh_pfc_pin *pin = &pfc->info->pins[idx];
			अचिन्हित पूर्णांक lower_voltage;
			u32 pocctrl, val;
			पूर्णांक bit;

			अगर (!pfc->info->ops || !pfc->info->ops->pin_to_pocctrl)
				वापस -ENOTSUPP;

			bit = pfc->info->ops->pin_to_pocctrl(pfc, _pin, &pocctrl);
			अगर (WARN(bit < 0, "invalid pin %#x", _pin))
				वापस bit;

			lower_voltage = (pin->configs & SH_PFC_PIN_VOLTAGE_25_33) ?
				2500 : 1800;

			अगर (mV != lower_voltage && mV != 3300)
				वापस -EINVAL;

			spin_lock_irqsave(&pfc->lock, flags);
			val = sh_pfc_पढ़ो(pfc, pocctrl);
			अगर (mV == 3300)
				val |= BIT(bit);
			अन्यथा
				val &= ~BIT(bit);
			sh_pfc_ग_लिखो(pfc, pocctrl, val);
			spin_unlock_irqrestore(&pfc->lock, flags);

			अवरोध;
		पूर्ण

		शेष:
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल पूर्णांक sh_pfc_pinconf_group_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित group,
				    अचिन्हित दीर्घ *configs,
				    अचिन्हित num_configs)
अणु
	काष्ठा sh_pfc_pinctrl *pmx = pinctrl_dev_get_drvdata(pctldev);
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक num_pins;
	अचिन्हित पूर्णांक i, ret;

	pins = pmx->pfc->info->groups[group].pins;
	num_pins = pmx->pfc->info->groups[group].nr_pins;

	क्रम (i = 0; i < num_pins; ++i) अणु
		ret = sh_pfc_pinconf_set(pctldev, pins[i], configs, num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops sh_pfc_pinconf_ops = अणु
	.is_generic			= true,
	.pin_config_get			= sh_pfc_pinconf_get,
	.pin_config_set			= sh_pfc_pinconf_set,
	.pin_config_group_set		= sh_pfc_pinconf_group_set,
	.pin_config_config_dbg_show	= pinconf_generic_dump_config,
पूर्ण;

/* PFC ranges -> pinctrl pin descs */
अटल पूर्णांक sh_pfc_map_pins(काष्ठा sh_pfc *pfc, काष्ठा sh_pfc_pinctrl *pmx)
अणु
	अचिन्हित पूर्णांक i;

	/* Allocate and initialize the pins and configs arrays. */
	pmx->pins = devm_kसुस्मृति(pfc->dev,
				 pfc->info->nr_pins, माप(*pmx->pins),
				 GFP_KERNEL);
	अगर (unlikely(!pmx->pins))
		वापस -ENOMEM;

	pmx->configs = devm_kसुस्मृति(pfc->dev,
				    pfc->info->nr_pins, माप(*pmx->configs),
				    GFP_KERNEL);
	अगर (unlikely(!pmx->configs))
		वापस -ENOMEM;

	क्रम (i = 0; i < pfc->info->nr_pins; ++i) अणु
		स्थिर काष्ठा sh_pfc_pin *info = &pfc->info->pins[i];
		काष्ठा pinctrl_pin_desc *pin = &pmx->pins[i];

		/* If the pin number is equal to -1 all pins are considered */
		pin->number = info->pin != (u16)-1 ? info->pin : i;
		pin->name = info->name;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sh_pfc_रेजिस्टर_pinctrl(काष्ठा sh_pfc *pfc)
अणु
	काष्ठा sh_pfc_pinctrl *pmx;
	पूर्णांक ret;

	pmx = devm_kzalloc(pfc->dev, माप(*pmx), GFP_KERNEL);
	अगर (unlikely(!pmx))
		वापस -ENOMEM;

	pmx->pfc = pfc;

	ret = sh_pfc_map_pins(pfc, pmx);
	अगर (ret < 0)
		वापस ret;

	pmx->pctl_desc.name = DRV_NAME;
	pmx->pctl_desc.owner = THIS_MODULE;
	pmx->pctl_desc.pctlops = &sh_pfc_pinctrl_ops;
	pmx->pctl_desc.pmxops = &sh_pfc_pinmux_ops;
	pmx->pctl_desc.confops = &sh_pfc_pinconf_ops;
	pmx->pctl_desc.pins = pmx->pins;
	pmx->pctl_desc.npins = pfc->info->nr_pins;

	ret = devm_pinctrl_रेजिस्टर_and_init(pfc->dev, &pmx->pctl_desc, pmx,
					     &pmx->pctl);
	अगर (ret) अणु
		dev_err(pfc->dev, "could not register: %i\n", ret);

		वापस ret;
	पूर्ण

	वापस pinctrl_enable(pmx->pctl);
पूर्ण

अटल स्थिर काष्ठा pinmux_bias_reg *
rcar_pin_to_bias_reg(स्थिर काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin,
		     अचिन्हित पूर्णांक *bit)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; pfc->info->bias_regs[i].puen || pfc->info->bias_regs[i].pud; i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(pfc->info->bias_regs[i].pins); j++) अणु
			अगर (pfc->info->bias_regs[i].pins[j] == pin) अणु
				*bit = j;
				वापस &pfc->info->bias_regs[i];
			पूर्ण
		पूर्ण
	पूर्ण

	WARN_ONCE(1, "Pin %u is not in bias info list\n", pin);

	वापस शून्य;
पूर्ण

अचिन्हित पूर्णांक rcar_pinmux_get_bias(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin)
अणु
	स्थिर काष्ठा pinmux_bias_reg *reg;
	अचिन्हित पूर्णांक bit;

	reg = rcar_pin_to_bias_reg(pfc, pin, &bit);
	अगर (!reg)
		वापस PIN_CONFIG_BIAS_DISABLE;

	अगर (reg->puen) अणु
		अगर (!(sh_pfc_पढ़ो(pfc, reg->puen) & BIT(bit)))
			वापस PIN_CONFIG_BIAS_DISABLE;
		अन्यथा अगर (!reg->pud || (sh_pfc_पढ़ो(pfc, reg->pud) & BIT(bit)))
			वापस PIN_CONFIG_BIAS_PULL_UP;
		अन्यथा
			वापस PIN_CONFIG_BIAS_PULL_DOWN;
	पूर्ण अन्यथा अणु
		अगर (sh_pfc_पढ़ो(pfc, reg->pud) & BIT(bit))
			वापस PIN_CONFIG_BIAS_PULL_DOWN;
		अन्यथा
			वापस PIN_CONFIG_BIAS_DISABLE;
	पूर्ण
पूर्ण

व्योम rcar_pinmux_set_bias(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin,
			  अचिन्हित पूर्णांक bias)
अणु
	स्थिर काष्ठा pinmux_bias_reg *reg;
	u32 enable, upकरोwn;
	अचिन्हित पूर्णांक bit;

	reg = rcar_pin_to_bias_reg(pfc, pin, &bit);
	अगर (!reg)
		वापस;

	अगर (reg->puen) अणु
		enable = sh_pfc_पढ़ो(pfc, reg->puen) & ~BIT(bit);
		अगर (bias != PIN_CONFIG_BIAS_DISABLE)
			enable |= BIT(bit);

		अगर (reg->pud) अणु
			upकरोwn = sh_pfc_पढ़ो(pfc, reg->pud) & ~BIT(bit);
			अगर (bias == PIN_CONFIG_BIAS_PULL_UP)
				upकरोwn |= BIT(bit);

			sh_pfc_ग_लिखो(pfc, reg->pud, upकरोwn);
		पूर्ण

		sh_pfc_ग_लिखो(pfc, reg->puen, enable);
	पूर्ण अन्यथा अणु
		enable = sh_pfc_पढ़ो(pfc, reg->pud) & ~BIT(bit);
		अगर (bias == PIN_CONFIG_BIAS_PULL_DOWN)
			enable |= BIT(bit);

		sh_pfc_ग_लिखो(pfc, reg->pud, enable);
	पूर्ण
पूर्ण

#घोषणा PORTnCR_PULMD_OFF	(0 << 6)
#घोषणा PORTnCR_PULMD_DOWN	(2 << 6)
#घोषणा PORTnCR_PULMD_UP	(3 << 6)
#घोषणा PORTnCR_PULMD_MASK	(3 << 6)

अचिन्हित पूर्णांक rmobile_pinmux_get_bias(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin)
अणु
	व्योम __iomem *reg = pfc->info->ops->pin_to_portcr(pfc, pin);
	u32 value = ioपढ़ो8(reg) & PORTnCR_PULMD_MASK;

	चयन (value) अणु
	हाल PORTnCR_PULMD_UP:
		वापस PIN_CONFIG_BIAS_PULL_UP;
	हाल PORTnCR_PULMD_DOWN:
		वापस PIN_CONFIG_BIAS_PULL_DOWN;
	हाल PORTnCR_PULMD_OFF:
	शेष:
		वापस PIN_CONFIG_BIAS_DISABLE;
	पूर्ण
पूर्ण

व्योम rmobile_pinmux_set_bias(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin,
			     अचिन्हित पूर्णांक bias)
अणु
	व्योम __iomem *reg = pfc->info->ops->pin_to_portcr(pfc, pin);
	u32 value = ioपढ़ो8(reg) & ~PORTnCR_PULMD_MASK;

	चयन (bias) अणु
	हाल PIN_CONFIG_BIAS_PULL_UP:
		value |= PORTnCR_PULMD_UP;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		value |= PORTnCR_PULMD_DOWN;
		अवरोध;
	पूर्ण

	ioग_लिखो8(value, reg);
पूर्ण
