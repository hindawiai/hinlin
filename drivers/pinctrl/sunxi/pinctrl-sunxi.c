<शैली गुरु>
/*
 * Allwinner A1X SoCs pinctrl driver.
 *
 * Copyright (C) 2012 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/export.h>
#समावेश <linux/of.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/pinctrl/sun4i-a10.h>

#समावेश "../core.h"
#समावेश "pinctrl-sunxi.h"

अटल काष्ठा irq_chip sunxi_pinctrl_edge_irq_chip;
अटल काष्ठा irq_chip sunxi_pinctrl_level_irq_chip;

अटल काष्ठा sunxi_pinctrl_group *
sunxi_pinctrl_find_group_by_name(काष्ठा sunxi_pinctrl *pctl, स्थिर अक्षर *group)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pctl->ngroups; i++) अणु
		काष्ठा sunxi_pinctrl_group *grp = pctl->groups + i;

		अगर (!म_भेद(grp->name, group))
			वापस grp;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा sunxi_pinctrl_function *
sunxi_pinctrl_find_function_by_name(काष्ठा sunxi_pinctrl *pctl,
				    स्थिर अक्षर *name)
अणु
	काष्ठा sunxi_pinctrl_function *func = pctl->functions;
	पूर्णांक i;

	क्रम (i = 0; i < pctl->nfunctions; i++) अणु
		अगर (!func[i].name)
			अवरोध;

		अगर (!म_भेद(func[i].name, name))
			वापस func + i;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा sunxi_desc_function *
sunxi_pinctrl_desc_find_function_by_name(काष्ठा sunxi_pinctrl *pctl,
					 स्थिर अक्षर *pin_name,
					 स्थिर अक्षर *func_name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pctl->desc->npins; i++) अणु
		स्थिर काष्ठा sunxi_desc_pin *pin = pctl->desc->pins + i;

		अगर (!म_भेद(pin->pin.name, pin_name)) अणु
			काष्ठा sunxi_desc_function *func = pin->functions;

			जबतक (func->name) अणु
				अगर (!म_भेद(func->name, func_name) &&
					(!func->variant ||
					func->variant & pctl->variant))
					वापस func;

				func++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा sunxi_desc_function *
sunxi_pinctrl_desc_find_function_by_pin(काष्ठा sunxi_pinctrl *pctl,
					स्थिर u16 pin_num,
					स्थिर अक्षर *func_name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pctl->desc->npins; i++) अणु
		स्थिर काष्ठा sunxi_desc_pin *pin = pctl->desc->pins + i;

		अगर (pin->pin.number == pin_num) अणु
			काष्ठा sunxi_desc_function *func = pin->functions;

			जबतक (func->name) अणु
				अगर (!म_भेद(func->name, func_name))
					वापस func;

				func++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक sunxi_pctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->ngroups;
पूर्ण

अटल स्थिर अक्षर *sunxi_pctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					      अचिन्हित group)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->groups[group].name;
पूर्ण

अटल पूर्णांक sunxi_pctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित group,
				      स्थिर अचिन्हित **pins,
				      अचिन्हित *num_pins)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*pins = (अचिन्हित *)&pctl->groups[group].pin;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल bool sunxi_pctrl_has_bias_prop(काष्ठा device_node *node)
अणु
	वापस of_find_property(node, "bias-pull-up", शून्य) ||
		of_find_property(node, "bias-pull-down", शून्य) ||
		of_find_property(node, "bias-disable", शून्य) ||
		of_find_property(node, "allwinner,pull", शून्य);
पूर्ण

अटल bool sunxi_pctrl_has_drive_prop(काष्ठा device_node *node)
अणु
	वापस of_find_property(node, "drive-strength", शून्य) ||
		of_find_property(node, "allwinner,drive", शून्य);
पूर्ण

अटल पूर्णांक sunxi_pctrl_parse_bias_prop(काष्ठा device_node *node)
अणु
	u32 val;

	/* Try the new style binding */
	अगर (of_find_property(node, "bias-pull-up", शून्य))
		वापस PIN_CONFIG_BIAS_PULL_UP;

	अगर (of_find_property(node, "bias-pull-down", शून्य))
		वापस PIN_CONFIG_BIAS_PULL_DOWN;

	अगर (of_find_property(node, "bias-disable", शून्य))
		वापस PIN_CONFIG_BIAS_DISABLE;

	/* And fall back to the old binding */
	अगर (of_property_पढ़ो_u32(node, "allwinner,pull", &val))
		वापस -EINVAL;

	चयन (val) अणु
	हाल SUN4I_PINCTRL_NO_PULL:
		वापस PIN_CONFIG_BIAS_DISABLE;
	हाल SUN4I_PINCTRL_PULL_UP:
		वापस PIN_CONFIG_BIAS_PULL_UP;
	हाल SUN4I_PINCTRL_PULL_DOWN:
		वापस PIN_CONFIG_BIAS_PULL_DOWN;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sunxi_pctrl_parse_drive_prop(काष्ठा device_node *node)
अणु
	u32 val;

	/* Try the new style binding */
	अगर (!of_property_पढ़ो_u32(node, "drive-strength", &val)) अणु
		/* We can't go below 10mA ... */
		अगर (val < 10)
			वापस -EINVAL;

		/* ... and only up to 40 mA ... */
		अगर (val > 40)
			val = 40;

		/* by steps of 10 mA */
		वापस roundकरोwn(val, 10);
	पूर्ण

	/* And then fall back to the old binding */
	अगर (of_property_पढ़ो_u32(node, "allwinner,drive", &val))
		वापस -EINVAL;

	वापस (val + 1) * 10;
पूर्ण

अटल स्थिर अक्षर *sunxi_pctrl_parse_function_prop(काष्ठा device_node *node)
अणु
	स्थिर अक्षर *function;
	पूर्णांक ret;

	/* Try the generic binding */
	ret = of_property_पढ़ो_string(node, "function", &function);
	अगर (!ret)
		वापस function;

	/* And fall back to our legacy one */
	ret = of_property_पढ़ो_string(node, "allwinner,function", &function);
	अगर (!ret)
		वापस function;

	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *sunxi_pctrl_find_pins_prop(काष्ठा device_node *node,
					      पूर्णांक *npins)
अणु
	पूर्णांक count;

	/* Try the generic binding */
	count = of_property_count_strings(node, "pins");
	अगर (count > 0) अणु
		*npins = count;
		वापस "pins";
	पूर्ण

	/* And fall back to our legacy one */
	count = of_property_count_strings(node, "allwinner,pins");
	अगर (count > 0) अणु
		*npins = count;
		वापस "allwinner,pins";
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अचिन्हित दीर्घ *sunxi_pctrl_build_pin_config(काष्ठा device_node *node,
						   अचिन्हित पूर्णांक *len)
अणु
	अचिन्हित दीर्घ *pinconfig;
	अचिन्हित पूर्णांक configlen = 0, idx = 0;
	पूर्णांक ret;

	अगर (sunxi_pctrl_has_drive_prop(node))
		configlen++;
	अगर (sunxi_pctrl_has_bias_prop(node))
		configlen++;

	/*
	 * If we करोn't have any configuration, bail out
	 */
	अगर (!configlen)
		वापस शून्य;

	pinconfig = kसुस्मृति(configlen, माप(*pinconfig), GFP_KERNEL);
	अगर (!pinconfig)
		वापस ERR_PTR(-ENOMEM);

	अगर (sunxi_pctrl_has_drive_prop(node)) अणु
		पूर्णांक drive = sunxi_pctrl_parse_drive_prop(node);
		अगर (drive < 0) अणु
			ret = drive;
			जाओ err_मुक्त;
		पूर्ण

		pinconfig[idx++] = pinconf_to_config_packed(PIN_CONFIG_DRIVE_STRENGTH,
							  drive);
	पूर्ण

	अगर (sunxi_pctrl_has_bias_prop(node)) अणु
		पूर्णांक pull = sunxi_pctrl_parse_bias_prop(node);
		पूर्णांक arg = 0;
		अगर (pull < 0) अणु
			ret = pull;
			जाओ err_मुक्त;
		पूर्ण

		अगर (pull != PIN_CONFIG_BIAS_DISABLE)
			arg = 1; /* hardware uses weak pull resistors */

		pinconfig[idx++] = pinconf_to_config_packed(pull, arg);
	पूर्ण


	*len = configlen;
	वापस pinconfig;

err_मुक्त:
	kमुक्त(pinconfig);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक sunxi_pctrl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा device_node *node,
				      काष्ठा pinctrl_map **map,
				      अचिन्हित *num_maps)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित दीर्घ *pinconfig;
	काष्ठा property *prop;
	स्थिर अक्षर *function, *pin_prop;
	स्थिर अक्षर *group;
	पूर्णांक ret, npins, nmaps, configlen = 0, i = 0;

	*map = शून्य;
	*num_maps = 0;

	function = sunxi_pctrl_parse_function_prop(node);
	अगर (!function) अणु
		dev_err(pctl->dev, "missing function property in node %pOFn\n",
			node);
		वापस -EINVAL;
	पूर्ण

	pin_prop = sunxi_pctrl_find_pins_prop(node, &npins);
	अगर (!pin_prop) अणु
		dev_err(pctl->dev, "missing pins property in node %pOFn\n",
			node);
		वापस -EINVAL;
	पूर्ण

	/*
	 * We have two maps क्रम each pin: one क्रम the function, one
	 * क्रम the configuration (bias, strength, etc).
	 *
	 * We might be slightly overshooting, since we might not have
	 * any configuration.
	 */
	nmaps = npins * 2;
	*map = kदो_स्मृति_array(nmaps, माप(काष्ठा pinctrl_map), GFP_KERNEL);
	अगर (!*map)
		वापस -ENOMEM;

	pinconfig = sunxi_pctrl_build_pin_config(node, &configlen);
	अगर (IS_ERR(pinconfig)) अणु
		ret = PTR_ERR(pinconfig);
		जाओ err_मुक्त_map;
	पूर्ण

	of_property_क्रम_each_string(node, pin_prop, prop, group) अणु
		काष्ठा sunxi_pinctrl_group *grp =
			sunxi_pinctrl_find_group_by_name(pctl, group);

		अगर (!grp) अणु
			dev_err(pctl->dev, "unknown pin %s", group);
			जारी;
		पूर्ण

		अगर (!sunxi_pinctrl_desc_find_function_by_name(pctl,
							      grp->name,
							      function)) अणु
			dev_err(pctl->dev, "unsupported function %s on pin %s",
				function, group);
			जारी;
		पूर्ण

		(*map)[i].type = PIN_MAP_TYPE_MUX_GROUP;
		(*map)[i].data.mux.group = group;
		(*map)[i].data.mux.function = function;

		i++;

		अगर (pinconfig) अणु
			(*map)[i].type = PIN_MAP_TYPE_CONFIGS_GROUP;
			(*map)[i].data.configs.group_or_pin = group;
			(*map)[i].data.configs.configs = pinconfig;
			(*map)[i].data.configs.num_configs = configlen;
			i++;
		पूर्ण
	पूर्ण

	*num_maps = i;

	/*
	 * We know have the number of maps we need, we can resize our
	 * map array
	 */
	*map = kपुनः_स्मृति(*map, i * माप(काष्ठा pinctrl_map), GFP_KERNEL);
	अगर (!*map)
		वापस -ENOMEM;

	वापस 0;

err_मुक्त_map:
	kमुक्त(*map);
	*map = शून्य;
	वापस ret;
पूर्ण

अटल व्योम sunxi_pctrl_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा pinctrl_map *map,
				    अचिन्हित num_maps)
अणु
	पूर्णांक i;

	/* pin config is never in the first map */
	क्रम (i = 1; i < num_maps; i++) अणु
		अगर (map[i].type != PIN_MAP_TYPE_CONFIGS_GROUP)
			जारी;

		/*
		 * All the maps share the same pin config,
		 * मुक्त only the first one we find.
		 */
		kमुक्त(map[i].data.configs.configs);
		अवरोध;
	पूर्ण

	kमुक्त(map);
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops sunxi_pctrl_ops = अणु
	.dt_node_to_map		= sunxi_pctrl_dt_node_to_map,
	.dt_मुक्त_map		= sunxi_pctrl_dt_मुक्त_map,
	.get_groups_count	= sunxi_pctrl_get_groups_count,
	.get_group_name		= sunxi_pctrl_get_group_name,
	.get_group_pins		= sunxi_pctrl_get_group_pins,
पूर्ण;

अटल पूर्णांक sunxi_pconf_reg(अचिन्हित pin, क्रमागत pin_config_param param,
			   u32 *offset, u32 *shअगरt, u32 *mask)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		*offset = sunxi_dlevel_reg(pin);
		*shअगरt = sunxi_dlevel_offset(pin);
		*mask = DLEVEL_PINS_MASK;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
	हाल PIN_CONFIG_BIAS_DISABLE:
		*offset = sunxi_pull_reg(pin);
		*shअगरt = sunxi_pull_offset(pin);
		*mask = PULL_PINS_MASK;
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_pconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			   अचिन्हित दीर्घ *config)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	u32 offset, shअगरt, mask, val;
	u16 arg;
	पूर्णांक ret;

	pin -= pctl->desc->pin_base;

	ret = sunxi_pconf_reg(pin, param, &offset, &shअगरt, &mask);
	अगर (ret < 0)
		वापस ret;

	val = (पढ़ोl(pctl->membase + offset) >> shअगरt) & mask;

	चयन (pinconf_to_config_param(*config)) अणु
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		arg = (val + 1) * 10;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (val != SUN4I_PINCTRL_PULL_UP)
			वापस -EINVAL;
		arg = 1; /* hardware is weak pull-up */
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (val != SUN4I_PINCTRL_PULL_DOWN)
			वापस -EINVAL;
		arg = 1; /* hardware is weak pull-करोwn */
		अवरोध;

	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (val != SUN4I_PINCTRL_NO_PULL)
			वापस -EINVAL;
		arg = 0;
		अवरोध;

	शेष:
		/* sunxi_pconf_reg should catch anything unsupported */
		WARN_ON(1);
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_pconf_group_get(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित group,
				 अचिन्हित दीर्घ *config)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sunxi_pinctrl_group *g = &pctl->groups[group];

	/* We only support 1 pin per group. Chain it to the pin callback */
	वापस sunxi_pconf_get(pctldev, g->pin, config);
पूर्ण

अटल पूर्णांक sunxi_pconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			   अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		क्रमागत pin_config_param param;
		अचिन्हित दीर्घ flags;
		u32 offset, shअगरt, mask, reg;
		u32 arg, val;
		पूर्णांक ret;

		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		ret = sunxi_pconf_reg(pin, param, &offset, &shअगरt, &mask);
		अगर (ret < 0)
			वापस ret;

		चयन (param) अणु
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			अगर (arg < 10 || arg > 40)
				वापस -EINVAL;
			/*
			 * We convert from mA to what the रेजिस्टर expects:
			 *   0: 10mA
			 *   1: 20mA
			 *   2: 30mA
			 *   3: 40mA
			 */
			val = arg / 10 - 1;
			अवरोध;
		हाल PIN_CONFIG_BIAS_DISABLE:
			val = 0;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			अगर (arg == 0)
				वापस -EINVAL;
			val = 1;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			अगर (arg == 0)
				वापस -EINVAL;
			val = 2;
			अवरोध;
		शेष:
			/* sunxi_pconf_reg should catch anything unsupported */
			WARN_ON(1);
			वापस -ENOTSUPP;
		पूर्ण

		raw_spin_lock_irqsave(&pctl->lock, flags);
		reg = पढ़ोl(pctl->membase + offset);
		reg &= ~(mask << shअगरt);
		ग_लिखोl(reg | val << shअगरt, pctl->membase + offset);
		raw_spin_unlock_irqrestore(&pctl->lock, flags);
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_pconf_group_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित group,
				 अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sunxi_pinctrl_group *g = &pctl->groups[group];

	/* We only support 1 pin per group. Chain it to the pin callback */
	वापस sunxi_pconf_set(pctldev, g->pin, configs, num_configs);
पूर्ण

अटल स्थिर काष्ठा pinconf_ops sunxi_pconf_ops = अणु
	.is_generic		= true,
	.pin_config_get		= sunxi_pconf_get,
	.pin_config_set		= sunxi_pconf_set,
	.pin_config_group_get	= sunxi_pconf_group_get,
	.pin_config_group_set	= sunxi_pconf_group_set,
पूर्ण;

अटल पूर्णांक sunxi_pinctrl_set_io_bias_cfg(काष्ठा sunxi_pinctrl *pctl,
					 अचिन्हित pin,
					 काष्ठा regulator *supply)
अणु
	अचिन्हित लघु bank = pin / PINS_PER_BANK;
	अचिन्हित दीर्घ flags;
	u32 val, reg;
	पूर्णांक uV;

	अगर (!pctl->desc->io_bias_cfg_variant)
		वापस 0;

	uV = regulator_get_voltage(supply);
	अगर (uV < 0)
		वापस uV;

	/* Might be dummy regulator with no voltage set */
	अगर (uV == 0)
		वापस 0;

	चयन (pctl->desc->io_bias_cfg_variant) अणु
	हाल BIAS_VOLTAGE_GRP_CONFIG:
		/*
		 * Configured value must be equal or greater to actual
		 * voltage.
		 */
		अगर (uV <= 1800000)
			val = 0x0; /* 1.8V */
		अन्यथा अगर (uV <= 2500000)
			val = 0x6; /* 2.5V */
		अन्यथा अगर (uV <= 2800000)
			val = 0x9; /* 2.8V */
		अन्यथा अगर (uV <= 3000000)
			val = 0xA; /* 3.0V */
		अन्यथा
			val = 0xD; /* 3.3V */

		pin -= pctl->desc->pin_base;

		reg = पढ़ोl(pctl->membase + sunxi_grp_config_reg(pin));
		reg &= ~IO_BIAS_MASK;
		ग_लिखोl(reg | val, pctl->membase + sunxi_grp_config_reg(pin));
		वापस 0;
	हाल BIAS_VOLTAGE_PIO_POW_MODE_SEL:
		val = uV <= 1800000 ? 1 : 0;

		raw_spin_lock_irqsave(&pctl->lock, flags);
		reg = पढ़ोl(pctl->membase + PIO_POW_MOD_SEL_REG);
		reg &= ~(1 << bank);
		ग_लिखोl(reg | val << bank, pctl->membase + PIO_POW_MOD_SEL_REG);
		raw_spin_unlock_irqrestore(&pctl->lock, flags);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sunxi_pmx_get_funcs_cnt(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->nfunctions;
पूर्ण

अटल स्थिर अक्षर *sunxi_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित function)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->functions[function].name;
पूर्ण

अटल पूर्णांक sunxi_pmx_get_func_groups(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित function,
				     स्थिर अक्षर * स्थिर **groups,
				     अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctl->functions[function].groups;
	*num_groups = pctl->functions[function].ngroups;

	वापस 0;
पूर्ण

अटल व्योम sunxi_pmx_set(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित pin,
				 u8 config)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित दीर्घ flags;
	u32 val, mask;

	raw_spin_lock_irqsave(&pctl->lock, flags);

	pin -= pctl->desc->pin_base;
	val = पढ़ोl(pctl->membase + sunxi_mux_reg(pin));
	mask = MUX_PINS_MASK << sunxi_mux_offset(pin);
	ग_लिखोl((val & ~mask) | config << sunxi_mux_offset(pin),
		pctl->membase + sunxi_mux_reg(pin));

	raw_spin_unlock_irqrestore(&pctl->lock, flags);
पूर्ण

अटल पूर्णांक sunxi_pmx_set_mux(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित function,
			     अचिन्हित group)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sunxi_pinctrl_group *g = pctl->groups + group;
	काष्ठा sunxi_pinctrl_function *func = pctl->functions + function;
	काष्ठा sunxi_desc_function *desc =
		sunxi_pinctrl_desc_find_function_by_name(pctl,
							 g->name,
							 func->name);

	अगर (!desc)
		वापस -EINVAL;

	sunxi_pmx_set(pctldev, g->pin, desc->muxval);

	वापस 0;
पूर्ण

अटल पूर्णांक
sunxi_pmx_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
			काष्ठा pinctrl_gpio_range *range,
			अचिन्हित offset,
			bool input)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा sunxi_desc_function *desc;
	स्थिर अक्षर *func;

	अगर (input)
		func = "gpio_in";
	अन्यथा
		func = "gpio_out";

	desc = sunxi_pinctrl_desc_find_function_by_pin(pctl, offset, func);
	अगर (!desc)
		वापस -EINVAL;

	sunxi_pmx_set(pctldev, offset, desc->muxval);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_pmx_request(काष्ठा pinctrl_dev *pctldev, अचिन्हित offset)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित लघु bank = offset / PINS_PER_BANK;
	अचिन्हित लघु bank_offset = bank - pctl->desc->pin_base /
					    PINS_PER_BANK;
	काष्ठा sunxi_pinctrl_regulator *s_reg = &pctl->regulators[bank_offset];
	काष्ठा regulator *reg = s_reg->regulator;
	अक्षर supply[16];
	पूर्णांक ret;

	अगर (reg) अणु
		refcount_inc(&s_reg->refcount);
		वापस 0;
	पूर्ण

	snम_लिखो(supply, माप(supply), "vcc-p%c", 'a' + bank);
	reg = regulator_get(pctl->dev, supply);
	अगर (IS_ERR(reg)) अणु
		dev_err(pctl->dev, "Couldn't get bank P%c regulator\n",
			'A' + bank);
		वापस PTR_ERR(reg);
	पूर्ण

	ret = regulator_enable(reg);
	अगर (ret) अणु
		dev_err(pctl->dev,
			"Couldn't enable bank P%c regulator\n", 'A' + bank);
		जाओ out;
	पूर्ण

	sunxi_pinctrl_set_io_bias_cfg(pctl, offset, reg);

	s_reg->regulator = reg;
	refcount_set(&s_reg->refcount, 1);

	वापस 0;

out:
	regulator_put(s_reg->regulator);

	वापस ret;
पूर्ण

अटल पूर्णांक sunxi_pmx_मुक्त(काष्ठा pinctrl_dev *pctldev, अचिन्हित offset)
अणु
	काष्ठा sunxi_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित लघु bank = offset / PINS_PER_BANK;
	अचिन्हित लघु bank_offset = bank - pctl->desc->pin_base /
					    PINS_PER_BANK;
	काष्ठा sunxi_pinctrl_regulator *s_reg = &pctl->regulators[bank_offset];

	अगर (!refcount_dec_and_test(&s_reg->refcount))
		वापस 0;

	regulator_disable(s_reg->regulator);
	regulator_put(s_reg->regulator);
	s_reg->regulator = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops sunxi_pmx_ops = अणु
	.get_functions_count	= sunxi_pmx_get_funcs_cnt,
	.get_function_name	= sunxi_pmx_get_func_name,
	.get_function_groups	= sunxi_pmx_get_func_groups,
	.set_mux		= sunxi_pmx_set_mux,
	.gpio_set_direction	= sunxi_pmx_gpio_set_direction,
	.request		= sunxi_pmx_request,
	.मुक्त			= sunxi_pmx_मुक्त,
	.strict			= true,
पूर्ण;

अटल पूर्णांक sunxi_pinctrl_gpio_direction_input(काष्ठा gpio_chip *chip,
					अचिन्हित offset)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + offset);
पूर्ण

अटल पूर्णांक sunxi_pinctrl_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा sunxi_pinctrl *pctl = gpiochip_get_data(chip);
	u32 reg = sunxi_data_reg(offset);
	u8 index = sunxi_data_offset(offset);
	bool set_mux = pctl->desc->irq_पढ़ो_needs_mux &&
		gpiochip_line_is_irq(chip, offset);
	u32 pin = offset + chip->base;
	u32 val;

	अगर (set_mux)
		sunxi_pmx_set(pctl->pctl_dev, pin, SUN4I_FUNC_INPUT);

	val = (पढ़ोl(pctl->membase + reg) >> index) & DATA_PINS_MASK;

	अगर (set_mux)
		sunxi_pmx_set(pctl->pctl_dev, pin, SUN4I_FUNC_IRQ);

	वापस !!val;
पूर्ण

अटल व्योम sunxi_pinctrl_gpio_set(काष्ठा gpio_chip *chip,
				अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा sunxi_pinctrl *pctl = gpiochip_get_data(chip);
	u32 reg = sunxi_data_reg(offset);
	u8 index = sunxi_data_offset(offset);
	अचिन्हित दीर्घ flags;
	u32 regval;

	raw_spin_lock_irqsave(&pctl->lock, flags);

	regval = पढ़ोl(pctl->membase + reg);

	अगर (value)
		regval |= BIT(index);
	अन्यथा
		regval &= ~(BIT(index));

	ग_लिखोl(regval, pctl->membase + reg);

	raw_spin_unlock_irqrestore(&pctl->lock, flags);
पूर्ण

अटल पूर्णांक sunxi_pinctrl_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset, पूर्णांक value)
अणु
	sunxi_pinctrl_gpio_set(chip, offset, value);
	वापस pinctrl_gpio_direction_output(chip->base + offset);
पूर्ण

अटल पूर्णांक sunxi_pinctrl_gpio_of_xlate(काष्ठा gpio_chip *gc,
				स्थिर काष्ठा of_phandle_args *gpiospec,
				u32 *flags)
अणु
	पूर्णांक pin, base;

	base = PINS_PER_BANK * gpiospec->args[0];
	pin = base + gpiospec->args[1];

	अगर (pin > gc->ngpio)
		वापस -EINVAL;

	अगर (flags)
		*flags = gpiospec->args[2];

	वापस pin;
पूर्ण

अटल पूर्णांक sunxi_pinctrl_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा sunxi_pinctrl *pctl = gpiochip_get_data(chip);
	काष्ठा sunxi_desc_function *desc;
	अचिन्हित pinnum = pctl->desc->pin_base + offset;
	अचिन्हित irqnum;

	अगर (offset >= chip->ngpio)
		वापस -ENXIO;

	desc = sunxi_pinctrl_desc_find_function_by_pin(pctl, pinnum, "irq");
	अगर (!desc)
		वापस -EINVAL;

	irqnum = desc->irqbank * IRQ_PER_BANK + desc->irqnum;

	dev_dbg(chip->parent, "%s: request IRQ for GPIO %d, return %d\n",
		chip->label, offset + chip->base, irqnum);

	वापस irq_find_mapping(pctl->करोमुख्य, irqnum);
पूर्ण

अटल पूर्णांक sunxi_pinctrl_irq_request_resources(काष्ठा irq_data *d)
अणु
	काष्ठा sunxi_pinctrl *pctl = irq_data_get_irq_chip_data(d);
	काष्ठा sunxi_desc_function *func;
	पूर्णांक ret;

	func = sunxi_pinctrl_desc_find_function_by_pin(pctl,
					pctl->irq_array[d->hwirq], "irq");
	अगर (!func)
		वापस -EINVAL;

	ret = gpiochip_lock_as_irq(pctl->chip,
			pctl->irq_array[d->hwirq] - pctl->desc->pin_base);
	अगर (ret) अणु
		dev_err(pctl->dev, "unable to lock HW IRQ %lu for IRQ\n",
			irqd_to_hwirq(d));
		वापस ret;
	पूर्ण

	/* Change muxing to INT mode */
	sunxi_pmx_set(pctl->pctl_dev, pctl->irq_array[d->hwirq], func->muxval);

	वापस 0;
पूर्ण

अटल व्योम sunxi_pinctrl_irq_release_resources(काष्ठा irq_data *d)
अणु
	काष्ठा sunxi_pinctrl *pctl = irq_data_get_irq_chip_data(d);

	gpiochip_unlock_as_irq(pctl->chip,
			      pctl->irq_array[d->hwirq] - pctl->desc->pin_base);
पूर्ण

अटल पूर्णांक sunxi_pinctrl_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा sunxi_pinctrl *pctl = irq_data_get_irq_chip_data(d);
	u32 reg = sunxi_irq_cfg_reg(pctl->desc, d->hwirq);
	u8 index = sunxi_irq_cfg_offset(d->hwirq);
	अचिन्हित दीर्घ flags;
	u32 regval;
	u8 mode;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		mode = IRQ_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		mode = IRQ_EDGE_FALLING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		mode = IRQ_EDGE_BOTH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		mode = IRQ_LEVEL_HIGH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		mode = IRQ_LEVEL_LOW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	raw_spin_lock_irqsave(&pctl->lock, flags);

	अगर (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_chip_handler_name_locked(d, &sunxi_pinctrl_level_irq_chip,
						 handle_fasteoi_irq, शून्य);
	अन्यथा
		irq_set_chip_handler_name_locked(d, &sunxi_pinctrl_edge_irq_chip,
						 handle_edge_irq, शून्य);

	regval = पढ़ोl(pctl->membase + reg);
	regval &= ~(IRQ_CFG_IRQ_MASK << index);
	ग_लिखोl(regval | (mode << index), pctl->membase + reg);

	raw_spin_unlock_irqrestore(&pctl->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम sunxi_pinctrl_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा sunxi_pinctrl *pctl = irq_data_get_irq_chip_data(d);
	u32 status_reg = sunxi_irq_status_reg(pctl->desc, d->hwirq);
	u8 status_idx = sunxi_irq_status_offset(d->hwirq);

	/* Clear the IRQ */
	ग_लिखोl(1 << status_idx, pctl->membase + status_reg);
पूर्ण

अटल व्योम sunxi_pinctrl_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा sunxi_pinctrl *pctl = irq_data_get_irq_chip_data(d);
	u32 reg = sunxi_irq_ctrl_reg(pctl->desc, d->hwirq);
	u8 idx = sunxi_irq_ctrl_offset(d->hwirq);
	अचिन्हित दीर्घ flags;
	u32 val;

	raw_spin_lock_irqsave(&pctl->lock, flags);

	/* Mask the IRQ */
	val = पढ़ोl(pctl->membase + reg);
	ग_लिखोl(val & ~(1 << idx), pctl->membase + reg);

	raw_spin_unlock_irqrestore(&pctl->lock, flags);
पूर्ण

अटल व्योम sunxi_pinctrl_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा sunxi_pinctrl *pctl = irq_data_get_irq_chip_data(d);
	u32 reg = sunxi_irq_ctrl_reg(pctl->desc, d->hwirq);
	u8 idx = sunxi_irq_ctrl_offset(d->hwirq);
	अचिन्हित दीर्घ flags;
	u32 val;

	raw_spin_lock_irqsave(&pctl->lock, flags);

	/* Unmask the IRQ */
	val = पढ़ोl(pctl->membase + reg);
	ग_लिखोl(val | (1 << idx), pctl->membase + reg);

	raw_spin_unlock_irqrestore(&pctl->lock, flags);
पूर्ण

अटल व्योम sunxi_pinctrl_irq_ack_unmask(काष्ठा irq_data *d)
अणु
	sunxi_pinctrl_irq_ack(d);
	sunxi_pinctrl_irq_unmask(d);
पूर्ण

अटल पूर्णांक sunxi_pinctrl_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा sunxi_pinctrl *pctl = irq_data_get_irq_chip_data(d);
	u8 bank = d->hwirq / IRQ_PER_BANK;

	वापस irq_set_irq_wake(pctl->irq[bank], on);
पूर्ण

अटल काष्ठा irq_chip sunxi_pinctrl_edge_irq_chip = अणु
	.name		= "sunxi_pio_edge",
	.irq_ack	= sunxi_pinctrl_irq_ack,
	.irq_mask	= sunxi_pinctrl_irq_mask,
	.irq_unmask	= sunxi_pinctrl_irq_unmask,
	.irq_request_resources = sunxi_pinctrl_irq_request_resources,
	.irq_release_resources = sunxi_pinctrl_irq_release_resources,
	.irq_set_type	= sunxi_pinctrl_irq_set_type,
	.irq_set_wake	= sunxi_pinctrl_irq_set_wake,
	.flags		= IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

अटल काष्ठा irq_chip sunxi_pinctrl_level_irq_chip = अणु
	.name		= "sunxi_pio_level",
	.irq_eoi	= sunxi_pinctrl_irq_ack,
	.irq_mask	= sunxi_pinctrl_irq_mask,
	.irq_unmask	= sunxi_pinctrl_irq_unmask,
	/* Define irq_enable / disable to aव्योम spurious irqs क्रम drivers
	 * using these to suppress irqs जबतक they clear the irq source */
	.irq_enable	= sunxi_pinctrl_irq_ack_unmask,
	.irq_disable	= sunxi_pinctrl_irq_mask,
	.irq_request_resources = sunxi_pinctrl_irq_request_resources,
	.irq_release_resources = sunxi_pinctrl_irq_release_resources,
	.irq_set_type	= sunxi_pinctrl_irq_set_type,
	.irq_set_wake	= sunxi_pinctrl_irq_set_wake,
	.flags		= IRQCHIP_EOI_THREADED |
			  IRQCHIP_MASK_ON_SUSPEND |
			  IRQCHIP_EOI_IF_HANDLED,
पूर्ण;

अटल पूर्णांक sunxi_pinctrl_irq_of_xlate(काष्ठा irq_करोमुख्य *d,
				      काष्ठा device_node *node,
				      स्थिर u32 *पूर्णांकspec,
				      अचिन्हित पूर्णांक पूर्णांकsize,
				      अचिन्हित दीर्घ *out_hwirq,
				      अचिन्हित पूर्णांक *out_type)
अणु
	काष्ठा sunxi_pinctrl *pctl = d->host_data;
	काष्ठा sunxi_desc_function *desc;
	पूर्णांक pin, base;

	अगर (पूर्णांकsize < 3)
		वापस -EINVAL;

	base = PINS_PER_BANK * पूर्णांकspec[0];
	pin = pctl->desc->pin_base + base + पूर्णांकspec[1];

	desc = sunxi_pinctrl_desc_find_function_by_pin(pctl, pin, "irq");
	अगर (!desc)
		वापस -EINVAL;

	*out_hwirq = desc->irqbank * PINS_PER_BANK + desc->irqnum;
	*out_type = पूर्णांकspec[2];

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops sunxi_pinctrl_irq_करोमुख्य_ops = अणु
	.xlate		= sunxi_pinctrl_irq_of_xlate,
पूर्ण;

अटल व्योम sunxi_pinctrl_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा sunxi_pinctrl *pctl = irq_desc_get_handler_data(desc);
	अचिन्हित दीर्घ bank, reg, val;

	क्रम (bank = 0; bank < pctl->desc->irq_banks; bank++)
		अगर (irq == pctl->irq[bank])
			अवरोध;

	WARN_ON(bank == pctl->desc->irq_banks);

	chained_irq_enter(chip, desc);

	reg = sunxi_irq_status_reg_from_bank(pctl->desc, bank);
	val = पढ़ोl(pctl->membase + reg);

	अगर (val) अणु
		पूर्णांक irqoffset;

		क्रम_each_set_bit(irqoffset, &val, IRQ_PER_BANK) अणु
			पूर्णांक pin_irq = irq_find_mapping(pctl->करोमुख्य,
						       bank * IRQ_PER_BANK + irqoffset);
			generic_handle_irq(pin_irq);
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक sunxi_pinctrl_add_function(काष्ठा sunxi_pinctrl *pctl,
					स्थिर अक्षर *name)
अणु
	काष्ठा sunxi_pinctrl_function *func = pctl->functions;

	जबतक (func->name) अणु
		/* function alपढ़ोy there */
		अगर (म_भेद(func->name, name) == 0) अणु
			func->ngroups++;
			वापस -EEXIST;
		पूर्ण
		func++;
	पूर्ण

	func->name = name;
	func->ngroups = 1;

	pctl->nfunctions++;

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_pinctrl_build_state(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sunxi_pinctrl *pctl = platक्रमm_get_drvdata(pdev);
	व्योम *ptr;
	पूर्णांक i;

	/*
	 * Allocate groups
	 *
	 * We assume that the number of groups is the number of pins
	 * given in the data array.

	 * This will not always be true, since some pins might not be
	 * available in the current variant, but क्रमtunately क्रम us,
	 * this means that the number of pins is the maximum group
	 * number we will ever see.
	 */
	pctl->groups = devm_kसुस्मृति(&pdev->dev,
				    pctl->desc->npins, माप(*pctl->groups),
				    GFP_KERNEL);
	अगर (!pctl->groups)
		वापस -ENOMEM;

	क्रम (i = 0; i < pctl->desc->npins; i++) अणु
		स्थिर काष्ठा sunxi_desc_pin *pin = pctl->desc->pins + i;
		काष्ठा sunxi_pinctrl_group *group = pctl->groups + pctl->ngroups;

		अगर (pin->variant && !(pctl->variant & pin->variant))
			जारी;

		group->name = pin->pin.name;
		group->pin = pin->pin.number;

		/* And now we count the actual number of pins / groups */
		pctl->ngroups++;
	पूर्ण

	/*
	 * We suppose that we won't have any more functions than pins,
	 * we'll पुनः_स्मृतिate that later anyway
	 */
	pctl->functions = kसुस्मृति(pctl->ngroups,
				  माप(*pctl->functions),
				  GFP_KERNEL);
	अगर (!pctl->functions)
		वापस -ENOMEM;

	/* Count functions and their associated groups */
	क्रम (i = 0; i < pctl->desc->npins; i++) अणु
		स्थिर काष्ठा sunxi_desc_pin *pin = pctl->desc->pins + i;
		काष्ठा sunxi_desc_function *func;

		अगर (pin->variant && !(pctl->variant & pin->variant))
			जारी;

		क्रम (func = pin->functions; func->name; func++) अणु
			अगर (func->variant && !(pctl->variant & func->variant))
				जारी;

			/* Create पूर्णांकerrupt mapping जबतक we're at it */
			अगर (!म_भेद(func->name, "irq")) अणु
				पूर्णांक irqnum = func->irqnum + func->irqbank * IRQ_PER_BANK;
				pctl->irq_array[irqnum] = pin->pin.number;
			पूर्ण

			sunxi_pinctrl_add_function(pctl, func->name);
		पूर्ण
	पूर्ण

	/* And now allocated and fill the array क्रम real */
	ptr = kपुनः_स्मृति(pctl->functions,
		       pctl->nfunctions * माप(*pctl->functions),
		       GFP_KERNEL);
	अगर (!ptr) अणु
		kमुक्त(pctl->functions);
		pctl->functions = शून्य;
		वापस -ENOMEM;
	पूर्ण
	pctl->functions = ptr;

	क्रम (i = 0; i < pctl->desc->npins; i++) अणु
		स्थिर काष्ठा sunxi_desc_pin *pin = pctl->desc->pins + i;
		काष्ठा sunxi_desc_function *func;

		अगर (pin->variant && !(pctl->variant & pin->variant))
			जारी;

		क्रम (func = pin->functions; func->name; func++) अणु
			काष्ठा sunxi_pinctrl_function *func_item;
			स्थिर अक्षर **func_grp;

			अगर (func->variant && !(pctl->variant & func->variant))
				जारी;

			func_item = sunxi_pinctrl_find_function_by_name(pctl,
									func->name);
			अगर (!func_item) अणु
				kमुक्त(pctl->functions);
				वापस -EINVAL;
			पूर्ण

			अगर (!func_item->groups) अणु
				func_item->groups =
					devm_kसुस्मृति(&pdev->dev,
						     func_item->ngroups,
						     माप(*func_item->groups),
						     GFP_KERNEL);
				अगर (!func_item->groups) अणु
					kमुक्त(pctl->functions);
					वापस -ENOMEM;
				पूर्ण
			पूर्ण

			func_grp = func_item->groups;
			जबतक (*func_grp)
				func_grp++;

			*func_grp = pin->pin.name;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_pinctrl_get_debounce_भाग(काष्ठा clk *clk, पूर्णांक freq, पूर्णांक *dअगरf)
अणु
	अचिन्हित दीर्घ घड़ी = clk_get_rate(clk);
	अचिन्हित पूर्णांक best_dअगरf, best_भाग;
	पूर्णांक i;

	best_dअगरf = असल(freq - घड़ी);
	best_भाग = 0;

	क्रम (i = 1; i < 8; i++) अणु
		पूर्णांक cur_dअगरf = असल(freq - (घड़ी >> i));

		अगर (cur_dअगरf < best_dअगरf) अणु
			best_dअगरf = cur_dअगरf;
			best_भाग = i;
		पूर्ण
	पूर्ण

	*dअगरf = best_dअगरf;
	वापस best_भाग;
पूर्ण

अटल पूर्णांक sunxi_pinctrl_setup_debounce(काष्ठा sunxi_pinctrl *pctl,
					काष्ठा device_node *node)
अणु
	अचिन्हित पूर्णांक hosc_dअगरf, losc_dअगरf;
	अचिन्हित पूर्णांक hosc_भाग, losc_भाग;
	काष्ठा clk *hosc, *losc;
	u8 भाग, src;
	पूर्णांक i, ret;

	/* Deal with old DTs that didn't have the oscillators */
	अगर (of_clk_get_parent_count(node) != 3)
		वापस 0;

	/* If we करोn't have any setup, bail out */
	अगर (!of_find_property(node, "input-debounce", शून्य))
		वापस 0;

	losc = devm_clk_get(pctl->dev, "losc");
	अगर (IS_ERR(losc))
		वापस PTR_ERR(losc);

	hosc = devm_clk_get(pctl->dev, "hosc");
	अगर (IS_ERR(hosc))
		वापस PTR_ERR(hosc);

	क्रम (i = 0; i < pctl->desc->irq_banks; i++) अणु
		अचिन्हित दीर्घ debounce_freq;
		u32 debounce;

		ret = of_property_पढ़ो_u32_index(node, "input-debounce",
						 i, &debounce);
		अगर (ret)
			वापस ret;

		अगर (!debounce)
			जारी;

		debounce_freq = DIV_ROUND_CLOSEST(USEC_PER_SEC, debounce);
		losc_भाग = sunxi_pinctrl_get_debounce_भाग(losc,
							  debounce_freq,
							  &losc_dअगरf);

		hosc_भाग = sunxi_pinctrl_get_debounce_भाग(hosc,
							  debounce_freq,
							  &hosc_dअगरf);

		अगर (hosc_dअगरf < losc_dअगरf) अणु
			भाग = hosc_भाग;
			src = 1;
		पूर्ण अन्यथा अणु
			भाग = losc_भाग;
			src = 0;
		पूर्ण

		ग_लिखोl(src | भाग << 4,
		       pctl->membase +
		       sunxi_irq_debounce_reg_from_bank(pctl->desc, i));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sunxi_pinctrl_init_with_variant(काष्ठा platक्रमm_device *pdev,
				    स्थिर काष्ठा sunxi_pinctrl_desc *desc,
				    अचिन्हित दीर्घ variant)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा pinctrl_desc *pctrl_desc;
	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा sunxi_pinctrl *pctl;
	काष्ठा pinmux_ops *pmxops;
	पूर्णांक i, ret, last_pin, pin_idx;
	काष्ठा clk *clk;

	pctl = devm_kzalloc(&pdev->dev, माप(*pctl), GFP_KERNEL);
	अगर (!pctl)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, pctl);

	raw_spin_lock_init(&pctl->lock);

	pctl->membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pctl->membase))
		वापस PTR_ERR(pctl->membase);

	pctl->dev = &pdev->dev;
	pctl->desc = desc;
	pctl->variant = variant;

	pctl->irq_array = devm_kसुस्मृति(&pdev->dev,
				       IRQ_PER_BANK * pctl->desc->irq_banks,
				       माप(*pctl->irq_array),
				       GFP_KERNEL);
	अगर (!pctl->irq_array)
		वापस -ENOMEM;

	ret = sunxi_pinctrl_build_state(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "dt probe failed: %d\n", ret);
		वापस ret;
	पूर्ण

	pins = devm_kसुस्मृति(&pdev->dev,
			    pctl->desc->npins, माप(*pins),
			    GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	क्रम (i = 0, pin_idx = 0; i < pctl->desc->npins; i++) अणु
		स्थिर काष्ठा sunxi_desc_pin *pin = pctl->desc->pins + i;

		अगर (pin->variant && !(pctl->variant & pin->variant))
			जारी;

		pins[pin_idx++] = pin->pin;
	पूर्ण

	pctrl_desc = devm_kzalloc(&pdev->dev,
				  माप(*pctrl_desc),
				  GFP_KERNEL);
	अगर (!pctrl_desc)
		वापस -ENOMEM;

	pctrl_desc->name = dev_name(&pdev->dev);
	pctrl_desc->owner = THIS_MODULE;
	pctrl_desc->pins = pins;
	pctrl_desc->npins = pctl->ngroups;
	pctrl_desc->confops = &sunxi_pconf_ops;
	pctrl_desc->pctlops = &sunxi_pctrl_ops;

	pmxops = devm_kmemdup(&pdev->dev, &sunxi_pmx_ops, माप(sunxi_pmx_ops),
			      GFP_KERNEL);
	अगर (!pmxops)
		वापस -ENOMEM;

	अगर (desc->disable_strict_mode)
		pmxops->strict = false;

	pctrl_desc->pmxops = pmxops;

	pctl->pctl_dev = devm_pinctrl_रेजिस्टर(&pdev->dev, pctrl_desc, pctl);
	अगर (IS_ERR(pctl->pctl_dev)) अणु
		dev_err(&pdev->dev, "couldn't register pinctrl driver\n");
		वापस PTR_ERR(pctl->pctl_dev);
	पूर्ण

	pctl->chip = devm_kzalloc(&pdev->dev, माप(*pctl->chip), GFP_KERNEL);
	अगर (!pctl->chip)
		वापस -ENOMEM;

	last_pin = pctl->desc->pins[pctl->desc->npins - 1].pin.number;
	pctl->chip->owner = THIS_MODULE;
	pctl->chip->request = gpiochip_generic_request;
	pctl->chip->मुक्त = gpiochip_generic_मुक्त;
	pctl->chip->set_config = gpiochip_generic_config;
	pctl->chip->direction_input = sunxi_pinctrl_gpio_direction_input;
	pctl->chip->direction_output = sunxi_pinctrl_gpio_direction_output;
	pctl->chip->get = sunxi_pinctrl_gpio_get;
	pctl->chip->set = sunxi_pinctrl_gpio_set;
	pctl->chip->of_xlate = sunxi_pinctrl_gpio_of_xlate;
	pctl->chip->to_irq = sunxi_pinctrl_gpio_to_irq;
	pctl->chip->of_gpio_n_cells = 3;
	pctl->chip->can_sleep = false;
	pctl->chip->ngpio = round_up(last_pin, PINS_PER_BANK) -
			    pctl->desc->pin_base;
	pctl->chip->label = dev_name(&pdev->dev);
	pctl->chip->parent = &pdev->dev;
	pctl->chip->base = pctl->desc->pin_base;

	ret = gpiochip_add_data(pctl->chip, pctl);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < pctl->desc->npins; i++) अणु
		स्थिर काष्ठा sunxi_desc_pin *pin = pctl->desc->pins + i;

		ret = gpiochip_add_pin_range(pctl->chip, dev_name(&pdev->dev),
					     pin->pin.number - pctl->desc->pin_base,
					     pin->pin.number, 1);
		अगर (ret)
			जाओ gpiochip_error;
	पूर्ण

	ret = of_clk_get_parent_count(node);
	clk = devm_clk_get(&pdev->dev, ret == 1 ? शून्य : "apb");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ gpiochip_error;
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret)
		जाओ gpiochip_error;

	pctl->irq = devm_kसुस्मृति(&pdev->dev,
				 pctl->desc->irq_banks,
				 माप(*pctl->irq),
				 GFP_KERNEL);
	अगर (!pctl->irq) अणु
		ret = -ENOMEM;
		जाओ clk_error;
	पूर्ण

	क्रम (i = 0; i < pctl->desc->irq_banks; i++) अणु
		pctl->irq[i] = platक्रमm_get_irq(pdev, i);
		अगर (pctl->irq[i] < 0) अणु
			ret = pctl->irq[i];
			जाओ clk_error;
		पूर्ण
	पूर्ण

	pctl->करोमुख्य = irq_करोमुख्य_add_linear(node,
					     pctl->desc->irq_banks * IRQ_PER_BANK,
					     &sunxi_pinctrl_irq_करोमुख्य_ops,
					     pctl);
	अगर (!pctl->करोमुख्य) अणु
		dev_err(&pdev->dev, "Couldn't register IRQ domain\n");
		ret = -ENOMEM;
		जाओ clk_error;
	पूर्ण

	क्रम (i = 0; i < (pctl->desc->irq_banks * IRQ_PER_BANK); i++) अणु
		पूर्णांक irqno = irq_create_mapping(pctl->करोमुख्य, i);

		irq_set_chip_and_handler(irqno, &sunxi_pinctrl_edge_irq_chip,
					 handle_edge_irq);
		irq_set_chip_data(irqno, pctl);
	पूर्ण

	क्रम (i = 0; i < pctl->desc->irq_banks; i++) अणु
		/* Mask and clear all IRQs beक्रमe रेजिस्टरing a handler */
		ग_लिखोl(0, pctl->membase +
			  sunxi_irq_ctrl_reg_from_bank(pctl->desc, i));
		ग_लिखोl(0xffffffff,
		       pctl->membase +
		       sunxi_irq_status_reg_from_bank(pctl->desc, i));

		irq_set_chained_handler_and_data(pctl->irq[i],
						 sunxi_pinctrl_irq_handler,
						 pctl);
	पूर्ण

	sunxi_pinctrl_setup_debounce(pctl, node);

	dev_info(&pdev->dev, "initialized sunXi PIO driver\n");

	वापस 0;

clk_error:
	clk_disable_unprepare(clk);
gpiochip_error:
	gpiochip_हटाओ(pctl->chip);
	वापस ret;
पूर्ण
