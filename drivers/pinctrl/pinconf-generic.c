<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver क्रम the generic pin config portions of the pin control subप्रणाली
 *
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#घोषणा pr_fmt(fmt) "generic pinconfig core: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/of.h>
#समावेश "core.h"
#समावेश "pinconf.h"
#समावेश "pinctrl-utils.h"

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर काष्ठा pin_config_item conf_items[] = अणु
	PCONFDUMP(PIN_CONFIG_BIAS_BUS_HOLD, "input bias bus hold", शून्य, false),
	PCONFDUMP(PIN_CONFIG_BIAS_DISABLE, "input bias disabled", शून्य, false),
	PCONFDUMP(PIN_CONFIG_BIAS_HIGH_IMPEDANCE, "input bias high impedance", शून्य, false),
	PCONFDUMP(PIN_CONFIG_BIAS_PULL_DOWN, "input bias pull down", शून्य, false),
	PCONFDUMP(PIN_CONFIG_BIAS_PULL_PIN_DEFAULT,
				"input bias pull to pin specific state", शून्य, false),
	PCONFDUMP(PIN_CONFIG_BIAS_PULL_UP, "input bias pull up", शून्य, false),
	PCONFDUMP(PIN_CONFIG_DRIVE_OPEN_DRAIN, "output drive open drain", शून्य, false),
	PCONFDUMP(PIN_CONFIG_DRIVE_OPEN_SOURCE, "output drive open source", शून्य, false),
	PCONFDUMP(PIN_CONFIG_DRIVE_PUSH_PULL, "output drive push pull", शून्य, false),
	PCONFDUMP(PIN_CONFIG_DRIVE_STRENGTH, "output drive strength", "mA", true),
	PCONFDUMP(PIN_CONFIG_DRIVE_STRENGTH_UA, "output drive strength", "uA", true),
	PCONFDUMP(PIN_CONFIG_INPUT_DEBOUNCE, "input debounce", "usec", true),
	PCONFDUMP(PIN_CONFIG_INPUT_ENABLE, "input enabled", शून्य, false),
	PCONFDUMP(PIN_CONFIG_INPUT_SCHMITT, "input schmitt trigger", शून्य, false),
	PCONFDUMP(PIN_CONFIG_INPUT_SCHMITT_ENABLE, "input schmitt enabled", शून्य, false),
	PCONFDUMP(PIN_CONFIG_MODE_LOW_POWER, "pin low power", "mode", true),
	PCONFDUMP(PIN_CONFIG_OUTPUT_ENABLE, "output enabled", शून्य, false),
	PCONFDUMP(PIN_CONFIG_OUTPUT, "pin output", "level", true),
	PCONFDUMP(PIN_CONFIG_POWER_SOURCE, "pin power source", "selector", true),
	PCONFDUMP(PIN_CONFIG_SLEEP_HARDWARE_STATE, "sleep hardware state", शून्य, false),
	PCONFDUMP(PIN_CONFIG_SLEW_RATE, "slew rate", शून्य, true),
	PCONFDUMP(PIN_CONFIG_SKEW_DELAY, "skew delay", शून्य, true),
पूर्ण;

अटल व्योम pinconf_generic_dump_one(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा seq_file *s, स्थिर अक्षर *gname,
				     अचिन्हित pin,
				     स्थिर काष्ठा pin_config_item *items,
				     पूर्णांक nitems, पूर्णांक *prपूर्णांक_sep)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nitems; i++) अणु
		अचिन्हित दीर्घ config;
		पूर्णांक ret;

		/* We want to check out this parameter */
		config = pinconf_to_config_packed(items[i].param, 0);
		अगर (gname)
			ret = pin_config_group_get(dev_name(pctldev->dev),
						   gname, &config);
		अन्यथा
			ret = pin_config_get_क्रम_pin(pctldev, pin, &config);
		/* These are legal errors */
		अगर (ret == -EINVAL || ret == -ENOTSUPP)
			जारी;
		अगर (ret) अणु
			seq_म_लिखो(s, "ERROR READING CONFIG SETTING %d ", i);
			जारी;
		पूर्ण
		/* comma between multiple configs */
		अगर (*prपूर्णांक_sep)
			seq_माला_दो(s, ", ");
		*prपूर्णांक_sep = 1;
		seq_माला_दो(s, items[i].display);
		/* Prपूर्णांक unit अगर available */
		अगर (items[i].has_arg) अणु
			seq_म_लिखो(s, " (%u",
				   pinconf_to_config_argument(config));
			अगर (items[i].क्रमmat)
				seq_म_लिखो(s, " %s)", items[i].क्रमmat);
			अन्यथा
				seq_माला_दो(s, ")");
		पूर्ण
	पूर्ण
पूर्ण

/**
 * pinconf_generic_dump_pins - Prपूर्णांक inक्रमmation about pin or group of pins
 * @pctldev:	Pincontrol device
 * @s:		File to prपूर्णांक to
 * @gname:	Group name specअगरying pins
 * @pin:	Pin number specyfying pin
 *
 * Prपूर्णांक the pinconf configuration क्रम the requested pin(s) to @s. Pins can be
 * specअगरied either by pin using @pin or by group using @gname. Only one needs
 * to be specअगरied the other can be शून्य/0.
 */
व्योम pinconf_generic_dump_pins(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
			       स्थिर अक्षर *gname, अचिन्हित pin)
अणु
	स्थिर काष्ठा pinconf_ops *ops = pctldev->desc->confops;
	पूर्णांक prपूर्णांक_sep = 0;

	अगर (!ops->is_generic)
		वापस;

	/* generic parameters */
	pinconf_generic_dump_one(pctldev, s, gname, pin, conf_items,
				 ARRAY_SIZE(conf_items), &prपूर्णांक_sep);
	/* driver-specअगरic parameters */
	अगर (pctldev->desc->num_custom_params &&
	    pctldev->desc->custom_conf_items)
		pinconf_generic_dump_one(pctldev, s, gname, pin,
					 pctldev->desc->custom_conf_items,
					 pctldev->desc->num_custom_params,
					 &prपूर्णांक_sep);
पूर्ण

व्योम pinconf_generic_dump_config(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा seq_file *s, अचिन्हित दीर्घ config)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(conf_items); i++) अणु
		अगर (pinconf_to_config_param(config) != conf_items[i].param)
			जारी;
		seq_म_लिखो(s, "%s: 0x%x", conf_items[i].display,
			   pinconf_to_config_argument(config));
	पूर्ण

	अगर (!pctldev->desc->num_custom_params ||
	    !pctldev->desc->custom_conf_items)
		वापस;

	क्रम (i = 0; i < pctldev->desc->num_custom_params; i++) अणु
		अगर (pinconf_to_config_param(config) !=
		    pctldev->desc->custom_conf_items[i].param)
			जारी;
		seq_म_लिखो(s, "%s: 0x%x",
				pctldev->desc->custom_conf_items[i].display,
				pinconf_to_config_argument(config));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(pinconf_generic_dump_config);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा pinconf_generic_params dt_params[] = अणु
	अणु "bias-bus-hold", PIN_CONFIG_BIAS_BUS_HOLD, 0 पूर्ण,
	अणु "bias-disable", PIN_CONFIG_BIAS_DISABLE, 0 पूर्ण,
	अणु "bias-high-impedance", PIN_CONFIG_BIAS_HIGH_IMPEDANCE, 0 पूर्ण,
	अणु "bias-pull-up", PIN_CONFIG_BIAS_PULL_UP, 1 पूर्ण,
	अणु "bias-pull-pin-default", PIN_CONFIG_BIAS_PULL_PIN_DEFAULT, 1 पूर्ण,
	अणु "bias-pull-down", PIN_CONFIG_BIAS_PULL_DOWN, 1 पूर्ण,
	अणु "drive-open-drain", PIN_CONFIG_DRIVE_OPEN_DRAIN, 0 पूर्ण,
	अणु "drive-open-source", PIN_CONFIG_DRIVE_OPEN_SOURCE, 0 पूर्ण,
	अणु "drive-push-pull", PIN_CONFIG_DRIVE_PUSH_PULL, 0 पूर्ण,
	अणु "drive-strength", PIN_CONFIG_DRIVE_STRENGTH, 0 पूर्ण,
	अणु "drive-strength-microamp", PIN_CONFIG_DRIVE_STRENGTH_UA, 0 पूर्ण,
	अणु "input-debounce", PIN_CONFIG_INPUT_DEBOUNCE, 0 पूर्ण,
	अणु "input-disable", PIN_CONFIG_INPUT_ENABLE, 0 पूर्ण,
	अणु "input-enable", PIN_CONFIG_INPUT_ENABLE, 1 पूर्ण,
	अणु "input-schmitt", PIN_CONFIG_INPUT_SCHMITT, 0 पूर्ण,
	अणु "input-schmitt-disable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 0 पूर्ण,
	अणु "input-schmitt-enable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 1 पूर्ण,
	अणु "low-power-disable", PIN_CONFIG_MODE_LOW_POWER, 0 पूर्ण,
	अणु "low-power-enable", PIN_CONFIG_MODE_LOW_POWER, 1 पूर्ण,
	अणु "output-disable", PIN_CONFIG_OUTPUT_ENABLE, 0 पूर्ण,
	अणु "output-enable", PIN_CONFIG_OUTPUT_ENABLE, 1 पूर्ण,
	अणु "output-high", PIN_CONFIG_OUTPUT, 1, पूर्ण,
	अणु "output-low", PIN_CONFIG_OUTPUT, 0, पूर्ण,
	अणु "power-source", PIN_CONFIG_POWER_SOURCE, 0 पूर्ण,
	अणु "sleep-hardware-state", PIN_CONFIG_SLEEP_HARDWARE_STATE, 0 पूर्ण,
	अणु "slew-rate", PIN_CONFIG_SLEW_RATE, 0 पूर्ण,
	अणु "skew-delay", PIN_CONFIG_SKEW_DELAY, 0 पूर्ण,
पूर्ण;

/**
 * parse_dt_cfg() - Parse DT pinconf parameters
 * @np:	DT node
 * @params:	Array of describing generic parameters
 * @count:	Number of entries in @params
 * @cfg:	Array of parsed config options
 * @ncfg:	Number of entries in @cfg
 *
 * Parse the config options described in @params from @np and माला_दो the result
 * in @cfg. @cfg करोes not need to be empty, entries are added beginning at
 * @ncfg. @ncfg is updated to reflect the number of entries after parsing. @cfg
 * needs to have enough memory allocated to hold all possible entries.
 */
अटल व्योम parse_dt_cfg(काष्ठा device_node *np,
			 स्थिर काष्ठा pinconf_generic_params *params,
			 अचिन्हित पूर्णांक count, अचिन्हित दीर्घ *cfg,
			 अचिन्हित पूर्णांक *ncfg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		u32 val;
		पूर्णांक ret;
		स्थिर काष्ठा pinconf_generic_params *par = &params[i];

		ret = of_property_पढ़ो_u32(np, par->property, &val);

		/* property not found */
		अगर (ret == -EINVAL)
			जारी;

		/* use शेष value, when no value is specअगरied */
		अगर (ret)
			val = par->शेष_value;

		pr_debug("found %s with value %u\n", par->property, val);
		cfg[*ncfg] = pinconf_to_config_packed(par->param, val);
		(*ncfg)++;
	पूर्ण
पूर्ण

/**
 * pinconf_generic_parse_dt_config()
 * parse the config properties पूर्णांकo generic pinconfig values.
 * @np: node containing the pinconfig properties
 * @pctldev: pincontrol device
 * @configs: array with nconfigs entries containing the generic pinconf values
 *           must be मुक्तd when no दीर्घer necessary.
 * @nconfigs: number of configurations
 */
पूर्णांक pinconf_generic_parse_dt_config(काष्ठा device_node *np,
				    काष्ठा pinctrl_dev *pctldev,
				    अचिन्हित दीर्घ **configs,
				    अचिन्हित पूर्णांक *nconfigs)
अणु
	अचिन्हित दीर्घ *cfg;
	अचिन्हित पूर्णांक max_cfg, ncfg = 0;
	पूर्णांक ret;

	अगर (!np)
		वापस -EINVAL;

	/* allocate a temporary array big enough to hold one of each option */
	max_cfg = ARRAY_SIZE(dt_params);
	अगर (pctldev)
		max_cfg += pctldev->desc->num_custom_params;
	cfg = kसुस्मृति(max_cfg, माप(*cfg), GFP_KERNEL);
	अगर (!cfg)
		वापस -ENOMEM;

	parse_dt_cfg(np, dt_params, ARRAY_SIZE(dt_params), cfg, &ncfg);
	अगर (pctldev && pctldev->desc->num_custom_params &&
		pctldev->desc->custom_params)
		parse_dt_cfg(np, pctldev->desc->custom_params,
			     pctldev->desc->num_custom_params, cfg, &ncfg);

	ret = 0;

	/* no configs found at all */
	अगर (ncfg == 0) अणु
		*configs = शून्य;
		*nconfigs = 0;
		जाओ out;
	पूर्ण

	/*
	 * Now limit the number of configs to the real number of
	 * found properties.
	 */
	*configs = kmemdup(cfg, ncfg * माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!*configs) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	*nconfigs = ncfg;

out:
	kमुक्त(cfg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pinconf_generic_parse_dt_config);

पूर्णांक pinconf_generic_dt_subnode_to_map(काष्ठा pinctrl_dev *pctldev,
		काष्ठा device_node *np, काष्ठा pinctrl_map **map,
		अचिन्हित *reserved_maps, अचिन्हित *num_maps,
		क्रमागत pinctrl_map_type type)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *function;
	काष्ठा device *dev = pctldev->dev;
	अचिन्हित दीर्घ *configs = शून्य;
	अचिन्हित num_configs = 0;
	अचिन्हित reserve, strings_count;
	काष्ठा property *prop;
	स्थिर अक्षर *group;
	स्थिर अक्षर *subnode_target_type = "pins";

	ret = of_property_count_strings(np, "pins");
	अगर (ret < 0) अणु
		ret = of_property_count_strings(np, "groups");
		अगर (ret < 0)
			/* skip this node; may contain config child nodes */
			वापस 0;
		अगर (type == PIN_MAP_TYPE_INVALID)
			type = PIN_MAP_TYPE_CONFIGS_GROUP;
		subnode_target_type = "groups";
	पूर्ण अन्यथा अणु
		अगर (type == PIN_MAP_TYPE_INVALID)
			type = PIN_MAP_TYPE_CONFIGS_PIN;
	पूर्ण
	strings_count = ret;

	ret = of_property_पढ़ो_string(np, "function", &function);
	अगर (ret < 0) अणु
		/* EINVAL=missing, which is fine since it's optional */
		अगर (ret != -EINVAL)
			dev_err(dev, "%pOF: could not parse property function\n",
				np);
		function = शून्य;
	पूर्ण

	ret = pinconf_generic_parse_dt_config(np, pctldev, &configs,
					      &num_configs);
	अगर (ret < 0) अणु
		dev_err(dev, "%pOF: could not parse node property\n", np);
		वापस ret;
	पूर्ण

	reserve = 0;
	अगर (function != शून्य)
		reserve++;
	अगर (num_configs)
		reserve++;

	reserve *= strings_count;

	ret = pinctrl_utils_reserve_map(pctldev, map, reserved_maps,
			num_maps, reserve);
	अगर (ret < 0)
		जाओ निकास;

	of_property_क्रम_each_string(np, subnode_target_type, prop, group) अणु
		अगर (function) अणु
			ret = pinctrl_utils_add_map_mux(pctldev, map,
					reserved_maps, num_maps, group,
					function);
			अगर (ret < 0)
				जाओ निकास;
		पूर्ण

		अगर (num_configs) अणु
			ret = pinctrl_utils_add_map_configs(pctldev, map,
					reserved_maps, num_maps, group, configs,
					num_configs, type);
			अगर (ret < 0)
				जाओ निकास;
		पूर्ण
	पूर्ण
	ret = 0;

निकास:
	kमुक्त(configs);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pinconf_generic_dt_subnode_to_map);

पूर्णांक pinconf_generic_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
		काष्ठा device_node *np_config, काष्ठा pinctrl_map **map,
		अचिन्हित *num_maps, क्रमागत pinctrl_map_type type)
अणु
	अचिन्हित reserved_maps;
	काष्ठा device_node *np;
	पूर्णांक ret;

	reserved_maps = 0;
	*map = शून्य;
	*num_maps = 0;

	ret = pinconf_generic_dt_subnode_to_map(pctldev, np_config, map,
						&reserved_maps, num_maps, type);
	अगर (ret < 0)
		जाओ निकास;

	क्रम_each_available_child_of_node(np_config, np) अणु
		ret = pinconf_generic_dt_subnode_to_map(pctldev, np, map,
					&reserved_maps, num_maps, type);
		अगर (ret < 0)
			जाओ निकास;
	पूर्ण
	वापस 0;

निकास:
	pinctrl_utils_मुक्त_map(pctldev, *map, *num_maps);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pinconf_generic_dt_node_to_map);

व्योम pinconf_generic_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा pinctrl_map *map,
				 अचिन्हित num_maps)
अणु
	pinctrl_utils_मुक्त_map(pctldev, map, num_maps);
पूर्ण
EXPORT_SYMBOL_GPL(pinconf_generic_dt_मुक्त_map);

#पूर्ण_अगर
