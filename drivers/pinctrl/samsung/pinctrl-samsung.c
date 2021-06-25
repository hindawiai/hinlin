<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// pin-controller/pin-mux/pin-config/gpio-driver क्रम Samsung's SoC's.
//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
// Copyright (c) 2012 Linaro Ltd
//		http://www.linaro.org
//
// Author: Thomas Abraham <thomas.ab@samsung.com>
//
// This driver implements the Samsung pinctrl driver. It supports setting up of
// pinmux and pinconf configurations. The gpiolib पूर्णांकerface is also included.
// External पूर्णांकerrupt (gpio and wakeup) support are not included in this driver
// but provides extensions to which platक्रमm specअगरic implementation of the gpio
// and wakeup पूर्णांकerrupts can be hooked to.

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spinlock.h>

#समावेश <dt-bindings/pinctrl/samsung.h>

#समावेश "../core.h"
#समावेश "pinctrl-samsung.h"

/* maximum number of the memory resources */
#घोषणा	SAMSUNG_PINCTRL_NUM_RESOURCES	2

/* list of all possible config options supported */
अटल काष्ठा pin_config अणु
	स्थिर अक्षर *property;
	क्रमागत pincfg_type param;
पूर्ण cfg_params[] = अणु
	अणु "samsung,pin-pud", PINCFG_TYPE_PUD पूर्ण,
	अणु "samsung,pin-drv", PINCFG_TYPE_DRV पूर्ण,
	अणु "samsung,pin-con-pdn", PINCFG_TYPE_CON_PDN पूर्ण,
	अणु "samsung,pin-pud-pdn", PINCFG_TYPE_PUD_PDN पूर्ण,
	अणु "samsung,pin-val", PINCFG_TYPE_DAT पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक pin_base;

अटल पूर्णांक samsung_get_group_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा samsung_pinctrl_drv_data *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->nr_groups;
पूर्ण

अटल स्थिर अक्षर *samsung_get_group_name(काष्ठा pinctrl_dev *pctldev,
						अचिन्हित group)
अणु
	काष्ठा samsung_pinctrl_drv_data *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->pin_groups[group].name;
पूर्ण

अटल पूर्णांक samsung_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित group,
					स्थिर अचिन्हित **pins,
					अचिन्हित *num_pins)
अणु
	काष्ठा samsung_pinctrl_drv_data *pmx = pinctrl_dev_get_drvdata(pctldev);

	*pins = pmx->pin_groups[group].pins;
	*num_pins = pmx->pin_groups[group].num_pins;

	वापस 0;
पूर्ण

अटल पूर्णांक reserve_map(काष्ठा device *dev, काष्ठा pinctrl_map **map,
		       अचिन्हित *reserved_maps, अचिन्हित *num_maps,
		       अचिन्हित reserve)
अणु
	अचिन्हित old_num = *reserved_maps;
	अचिन्हित new_num = *num_maps + reserve;
	काष्ठा pinctrl_map *new_map;

	अगर (old_num >= new_num)
		वापस 0;

	new_map = kपुनः_स्मृति(*map, माप(*new_map) * new_num, GFP_KERNEL);
	अगर (!new_map)
		वापस -ENOMEM;

	स_रखो(new_map + old_num, 0, (new_num - old_num) * माप(*new_map));

	*map = new_map;
	*reserved_maps = new_num;

	वापस 0;
पूर्ण

अटल पूर्णांक add_map_mux(काष्ठा pinctrl_map **map, अचिन्हित *reserved_maps,
		       अचिन्हित *num_maps, स्थिर अक्षर *group,
		       स्थिर अक्षर *function)
अणु
	अगर (WARN_ON(*num_maps == *reserved_maps))
		वापस -ENOSPC;

	(*map)[*num_maps].type = PIN_MAP_TYPE_MUX_GROUP;
	(*map)[*num_maps].data.mux.group = group;
	(*map)[*num_maps].data.mux.function = function;
	(*num_maps)++;

	वापस 0;
पूर्ण

अटल पूर्णांक add_map_configs(काष्ठा device *dev, काष्ठा pinctrl_map **map,
			   अचिन्हित *reserved_maps, अचिन्हित *num_maps,
			   स्थिर अक्षर *group, अचिन्हित दीर्घ *configs,
			   अचिन्हित num_configs)
अणु
	अचिन्हित दीर्घ *dup_configs;

	अगर (WARN_ON(*num_maps == *reserved_maps))
		वापस -ENOSPC;

	dup_configs = kmemdup(configs, num_configs * माप(*dup_configs),
			      GFP_KERNEL);
	अगर (!dup_configs)
		वापस -ENOMEM;

	(*map)[*num_maps].type = PIN_MAP_TYPE_CONFIGS_GROUP;
	(*map)[*num_maps].data.configs.group_or_pin = group;
	(*map)[*num_maps].data.configs.configs = dup_configs;
	(*map)[*num_maps].data.configs.num_configs = num_configs;
	(*num_maps)++;

	वापस 0;
पूर्ण

अटल पूर्णांक add_config(काष्ठा device *dev, अचिन्हित दीर्घ **configs,
		      अचिन्हित *num_configs, अचिन्हित दीर्घ config)
अणु
	अचिन्हित old_num = *num_configs;
	अचिन्हित new_num = old_num + 1;
	अचिन्हित दीर्घ *new_configs;

	new_configs = kपुनः_स्मृति(*configs, माप(*new_configs) * new_num,
			       GFP_KERNEL);
	अगर (!new_configs)
		वापस -ENOMEM;

	new_configs[old_num] = config;

	*configs = new_configs;
	*num_configs = new_num;

	वापस 0;
पूर्ण

अटल व्योम samsung_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा pinctrl_map *map,
				      अचिन्हित num_maps)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_maps; i++)
		अगर (map[i].type == PIN_MAP_TYPE_CONFIGS_GROUP)
			kमुक्त(map[i].data.configs.configs);

	kमुक्त(map);
पूर्ण

अटल पूर्णांक samsung_dt_subnode_to_map(काष्ठा samsung_pinctrl_drv_data *drvdata,
				     काष्ठा device *dev,
				     काष्ठा device_node *np,
				     काष्ठा pinctrl_map **map,
				     अचिन्हित *reserved_maps,
				     अचिन्हित *num_maps)
अणु
	पूर्णांक ret, i;
	u32 val;
	अचिन्हित दीर्घ config;
	अचिन्हित दीर्घ *configs = शून्य;
	अचिन्हित num_configs = 0;
	अचिन्हित reserve;
	काष्ठा property *prop;
	स्थिर अक्षर *group;
	bool has_func = false;

	ret = of_property_पढ़ो_u32(np, "samsung,pin-function", &val);
	अगर (!ret)
		has_func = true;

	क्रम (i = 0; i < ARRAY_SIZE(cfg_params); i++) अणु
		ret = of_property_पढ़ो_u32(np, cfg_params[i].property, &val);
		अगर (!ret) अणु
			config = PINCFG_PACK(cfg_params[i].param, val);
			ret = add_config(dev, &configs, &num_configs, config);
			अगर (ret < 0)
				जाओ निकास;
		/* EINVAL=missing, which is fine since it's optional */
		पूर्ण अन्यथा अगर (ret != -EINVAL) अणु
			dev_err(dev, "could not parse property %s\n",
				cfg_params[i].property);
		पूर्ण
	पूर्ण

	reserve = 0;
	अगर (has_func)
		reserve++;
	अगर (num_configs)
		reserve++;
	ret = of_property_count_strings(np, "samsung,pins");
	अगर (ret < 0) अणु
		dev_err(dev, "could not parse property samsung,pins\n");
		जाओ निकास;
	पूर्ण
	reserve *= ret;

	ret = reserve_map(dev, map, reserved_maps, num_maps, reserve);
	अगर (ret < 0)
		जाओ निकास;

	of_property_क्रम_each_string(np, "samsung,pins", prop, group) अणु
		अगर (has_func) अणु
			ret = add_map_mux(map, reserved_maps,
						num_maps, group, np->full_name);
			अगर (ret < 0)
				जाओ निकास;
		पूर्ण

		अगर (num_configs) अणु
			ret = add_map_configs(dev, map, reserved_maps,
					      num_maps, group, configs,
					      num_configs);
			अगर (ret < 0)
				जाओ निकास;
		पूर्ण
	पूर्ण

	ret = 0;

निकास:
	kमुक्त(configs);
	वापस ret;
पूर्ण

अटल पूर्णांक samsung_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
					काष्ठा device_node *np_config,
					काष्ठा pinctrl_map **map,
					अचिन्हित *num_maps)
अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata;
	अचिन्हित reserved_maps;
	काष्ठा device_node *np;
	पूर्णांक ret;

	drvdata = pinctrl_dev_get_drvdata(pctldev);

	reserved_maps = 0;
	*map = शून्य;
	*num_maps = 0;

	अगर (!of_get_child_count(np_config))
		वापस samsung_dt_subnode_to_map(drvdata, pctldev->dev,
							np_config, map,
							&reserved_maps,
							num_maps);

	क्रम_each_child_of_node(np_config, np) अणु
		ret = samsung_dt_subnode_to_map(drvdata, pctldev->dev, np, map,
						&reserved_maps, num_maps);
		अगर (ret < 0) अणु
			samsung_dt_मुक्त_map(pctldev, *map, *num_maps);
			of_node_put(np);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
/* Forward declaration which can be used by samsung_pin_dbg_show */
अटल पूर्णांक samsung_pinconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
					अचिन्हित दीर्घ *config);
अटल स्थिर अक्षर * स्थिर reg_names[] = अणु"CON", "DAT", "PUD", "DRV", "CON_PDN",
					 "PUD_PDN"पूर्ण;

अटल व्योम samsung_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
				काष्ठा seq_file *s, अचिन्हित पूर्णांक pin)
अणु
	क्रमागत pincfg_type cfg_type;
	अचिन्हित दीर्घ config;
	पूर्णांक ret;

	क्रम (cfg_type = 0; cfg_type < PINCFG_TYPE_NUM; cfg_type++) अणु
		config = PINCFG_PACK(cfg_type, 0);
		ret = samsung_pinconf_get(pctldev, pin, &config);
		अगर (ret < 0)
			जारी;

		seq_म_लिखो(s, " %s(0x%lx)", reg_names[cfg_type],
			   PINCFG_UNPACK_VALUE(config));
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* list of pinctrl callbacks क्रम the pinctrl core */
अटल स्थिर काष्ठा pinctrl_ops samsung_pctrl_ops = अणु
	.get_groups_count	= samsung_get_group_count,
	.get_group_name		= samsung_get_group_name,
	.get_group_pins		= samsung_get_group_pins,
	.dt_node_to_map		= samsung_dt_node_to_map,
	.dt_मुक्त_map		= samsung_dt_मुक्त_map,
#अगर_घोषित CONFIG_DEBUG_FS
	.pin_dbg_show		= samsung_pin_dbg_show,
#पूर्ण_अगर
पूर्ण;

/* check अगर the selector is a valid pin function selector */
अटल पूर्णांक samsung_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata;

	drvdata = pinctrl_dev_get_drvdata(pctldev);
	वापस drvdata->nr_functions;
पूर्ण

/* वापस the name of the pin function specअगरied */
अटल स्थिर अक्षर *samsung_pinmux_get_fname(काष्ठा pinctrl_dev *pctldev,
						अचिन्हित selector)
अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata;

	drvdata = pinctrl_dev_get_drvdata(pctldev);
	वापस drvdata->pmx_functions[selector].name;
पूर्ण

/* वापस the groups associated क्रम the specअगरied function selector */
अटल पूर्णांक samsung_pinmux_get_groups(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित selector, स्थिर अक्षर * स्थिर **groups,
		अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata;

	drvdata = pinctrl_dev_get_drvdata(pctldev);
	*groups = drvdata->pmx_functions[selector].groups;
	*num_groups = drvdata->pmx_functions[selector].num_groups;
	वापस 0;
पूर्ण

/*
 * given a pin number that is local to a pin controller, find out the pin bank
 * and the रेजिस्टर base of the pin bank.
 */
अटल व्योम pin_to_reg_bank(काष्ठा samsung_pinctrl_drv_data *drvdata,
			अचिन्हित pin, व्योम __iomem **reg, u32 *offset,
			काष्ठा samsung_pin_bank **bank)
अणु
	काष्ठा samsung_pin_bank *b;

	b = drvdata->pin_banks;

	जबतक ((pin >= b->pin_base) &&
			((b->pin_base + b->nr_pins - 1) < pin))
		b++;

	*reg = b->pctl_base + b->pctl_offset;
	*offset = pin - b->pin_base;
	अगर (bank)
		*bank = b;
पूर्ण

/* enable or disable a pinmux function */
अटल व्योम samsung_pinmux_setup(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
					अचिन्हित group)
अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata;
	स्थिर काष्ठा samsung_pin_bank_type *type;
	काष्ठा samsung_pin_bank *bank;
	व्योम __iomem *reg;
	u32 mask, shअगरt, data, pin_offset;
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा samsung_pmx_func *func;
	स्थिर काष्ठा samsung_pin_group *grp;

	drvdata = pinctrl_dev_get_drvdata(pctldev);
	func = &drvdata->pmx_functions[selector];
	grp = &drvdata->pin_groups[group];

	pin_to_reg_bank(drvdata, grp->pins[0] - drvdata->pin_base,
			&reg, &pin_offset, &bank);
	type = bank->type;
	mask = (1 << type->fld_width[PINCFG_TYPE_FUNC]) - 1;
	shअगरt = pin_offset * type->fld_width[PINCFG_TYPE_FUNC];
	अगर (shअगरt >= 32) अणु
		/* Some banks have two config रेजिस्टरs */
		shअगरt -= 32;
		reg += 4;
	पूर्ण

	raw_spin_lock_irqsave(&bank->slock, flags);

	data = पढ़ोl(reg + type->reg_offset[PINCFG_TYPE_FUNC]);
	data &= ~(mask << shअगरt);
	data |= func->val << shअगरt;
	ग_लिखोl(data, reg + type->reg_offset[PINCFG_TYPE_FUNC]);

	raw_spin_unlock_irqrestore(&bank->slock, flags);
पूर्ण

/* enable a specअगरied pinmux by writing to रेजिस्टरs */
अटल पूर्णांक samsung_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित selector,
				  अचिन्हित group)
अणु
	samsung_pinmux_setup(pctldev, selector, group);
	वापस 0;
पूर्ण

/* list of pinmux callbacks क्रम the pinmux vertical in pinctrl core */
अटल स्थिर काष्ठा pinmux_ops samsung_pinmux_ops = अणु
	.get_functions_count	= samsung_get_functions_count,
	.get_function_name	= samsung_pinmux_get_fname,
	.get_function_groups	= samsung_pinmux_get_groups,
	.set_mux		= samsung_pinmux_set_mux,
पूर्ण;

/* set or get the pin config settings क्रम a specअगरied pin */
अटल पूर्णांक samsung_pinconf_rw(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
				अचिन्हित दीर्घ *config, bool set)
अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata;
	स्थिर काष्ठा samsung_pin_bank_type *type;
	काष्ठा samsung_pin_bank *bank;
	व्योम __iomem *reg_base;
	क्रमागत pincfg_type cfg_type = PINCFG_UNPACK_TYPE(*config);
	u32 data, width, pin_offset, mask, shअगरt;
	u32 cfg_value, cfg_reg;
	अचिन्हित दीर्घ flags;

	drvdata = pinctrl_dev_get_drvdata(pctldev);
	pin_to_reg_bank(drvdata, pin - drvdata->pin_base, &reg_base,
					&pin_offset, &bank);
	type = bank->type;

	अगर (cfg_type >= PINCFG_TYPE_NUM || !type->fld_width[cfg_type])
		वापस -EINVAL;

	width = type->fld_width[cfg_type];
	cfg_reg = type->reg_offset[cfg_type];

	raw_spin_lock_irqsave(&bank->slock, flags);

	mask = (1 << width) - 1;
	shअगरt = pin_offset * width;
	data = पढ़ोl(reg_base + cfg_reg);

	अगर (set) अणु
		cfg_value = PINCFG_UNPACK_VALUE(*config);
		data &= ~(mask << shअगरt);
		data |= (cfg_value << shअगरt);
		ग_लिखोl(data, reg_base + cfg_reg);
	पूर्ण अन्यथा अणु
		data >>= shअगरt;
		data &= mask;
		*config = PINCFG_PACK(cfg_type, data);
	पूर्ण

	raw_spin_unlock_irqrestore(&bank->slock, flags);

	वापस 0;
पूर्ण

/* set the pin config settings क्रम a specअगरied pin */
अटल पूर्णांक samsung_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
				अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_configs; i++) अणु
		ret = samsung_pinconf_rw(pctldev, pin, &configs[i], true);
		अगर (ret < 0)
			वापस ret;
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

/* get the pin config settings क्रम a specअगरied pin */
अटल पूर्णांक samsung_pinconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
					अचिन्हित दीर्घ *config)
अणु
	वापस samsung_pinconf_rw(pctldev, pin, config, false);
पूर्ण

/* set the pin config settings क्रम a specअगरied pin group */
अटल पूर्णांक samsung_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
			अचिन्हित group, अचिन्हित दीर्घ *configs,
			अचिन्हित num_configs)
अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata;
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक cnt;

	drvdata = pinctrl_dev_get_drvdata(pctldev);
	pins = drvdata->pin_groups[group].pins;

	क्रम (cnt = 0; cnt < drvdata->pin_groups[group].num_pins; cnt++)
		samsung_pinconf_set(pctldev, pins[cnt], configs, num_configs);

	वापस 0;
पूर्ण

/* get the pin config settings क्रम a specअगरied pin group */
अटल पूर्णांक samsung_pinconf_group_get(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक group, अचिन्हित दीर्घ *config)
अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata;
	स्थिर अचिन्हित पूर्णांक *pins;

	drvdata = pinctrl_dev_get_drvdata(pctldev);
	pins = drvdata->pin_groups[group].pins;
	samsung_pinconf_get(pctldev, pins[0], config);
	वापस 0;
पूर्ण

/* list of pinconfig callbacks क्रम pinconfig vertical in the pinctrl code */
अटल स्थिर काष्ठा pinconf_ops samsung_pinconf_ops = अणु
	.pin_config_get		= samsung_pinconf_get,
	.pin_config_set		= samsung_pinconf_set,
	.pin_config_group_get	= samsung_pinconf_group_get,
	.pin_config_group_set	= samsung_pinconf_group_set,
पूर्ण;

/*
 * The samsung_gpio_set_vlaue() should be called with "bank->slock" held
 * to aव्योम race condition.
 */
अटल व्योम samsung_gpio_set_value(काष्ठा gpio_chip *gc,
					  अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा samsung_pin_bank *bank = gpiochip_get_data(gc);
	स्थिर काष्ठा samsung_pin_bank_type *type = bank->type;
	व्योम __iomem *reg;
	u32 data;

	reg = bank->pctl_base + bank->pctl_offset;

	data = पढ़ोl(reg + type->reg_offset[PINCFG_TYPE_DAT]);
	data &= ~(1 << offset);
	अगर (value)
		data |= 1 << offset;
	ग_लिखोl(data, reg + type->reg_offset[PINCFG_TYPE_DAT]);
पूर्ण

/* gpiolib gpio_set callback function */
अटल व्योम samsung_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा samsung_pin_bank *bank = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&bank->slock, flags);
	samsung_gpio_set_value(gc, offset, value);
	raw_spin_unlock_irqrestore(&bank->slock, flags);
पूर्ण

/* gpiolib gpio_get callback function */
अटल पूर्णांक samsung_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	व्योम __iomem *reg;
	u32 data;
	काष्ठा samsung_pin_bank *bank = gpiochip_get_data(gc);
	स्थिर काष्ठा samsung_pin_bank_type *type = bank->type;

	reg = bank->pctl_base + bank->pctl_offset;

	data = पढ़ोl(reg + type->reg_offset[PINCFG_TYPE_DAT]);
	data >>= offset;
	data &= 1;
	वापस data;
पूर्ण

/*
 * The samsung_gpio_set_direction() should be called with "bank->slock" held
 * to aव्योम race condition.
 * The calls to gpio_direction_output() and gpio_direction_input()
 * leads to this function call.
 */
अटल पूर्णांक samsung_gpio_set_direction(काष्ठा gpio_chip *gc,
					     अचिन्हित offset, bool input)
अणु
	स्थिर काष्ठा samsung_pin_bank_type *type;
	काष्ठा samsung_pin_bank *bank;
	व्योम __iomem *reg;
	u32 data, mask, shअगरt;

	bank = gpiochip_get_data(gc);
	type = bank->type;

	reg = bank->pctl_base + bank->pctl_offset
			+ type->reg_offset[PINCFG_TYPE_FUNC];

	mask = (1 << type->fld_width[PINCFG_TYPE_FUNC]) - 1;
	shअगरt = offset * type->fld_width[PINCFG_TYPE_FUNC];
	अगर (shअगरt >= 32) अणु
		/* Some banks have two config रेजिस्टरs */
		shअगरt -= 32;
		reg += 4;
	पूर्ण

	data = पढ़ोl(reg);
	data &= ~(mask << shअगरt);
	अगर (!input)
		data |= EXYNOS_PIN_FUNC_OUTPUT << shअगरt;
	ग_लिखोl(data, reg);

	वापस 0;
पूर्ण

/* gpiolib gpio_direction_input callback function. */
अटल पूर्णांक samsung_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा samsung_pin_bank *bank = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	raw_spin_lock_irqsave(&bank->slock, flags);
	ret = samsung_gpio_set_direction(gc, offset, true);
	raw_spin_unlock_irqrestore(&bank->slock, flags);
	वापस ret;
पूर्ण

/* gpiolib gpio_direction_output callback function. */
अटल पूर्णांक samsung_gpio_direction_output(काष्ठा gpio_chip *gc, अचिन्हित offset,
							पूर्णांक value)
अणु
	काष्ठा samsung_pin_bank *bank = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	raw_spin_lock_irqsave(&bank->slock, flags);
	samsung_gpio_set_value(gc, offset, value);
	ret = samsung_gpio_set_direction(gc, offset, false);
	raw_spin_unlock_irqrestore(&bank->slock, flags);

	वापस ret;
पूर्ण

/*
 * gpiolib gpio_to_irq callback function. Creates a mapping between a GPIO pin
 * and a भव IRQ, अगर not alपढ़ोy present.
 */
अटल पूर्णांक samsung_gpio_to_irq(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा samsung_pin_bank *bank = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक virq;

	अगर (!bank->irq_करोमुख्य)
		वापस -ENXIO;

	virq = irq_create_mapping(bank->irq_करोमुख्य, offset);

	वापस (virq) ? : -ENXIO;
पूर्ण

अटल काष्ठा samsung_pin_group *samsung_pinctrl_create_groups(
				काष्ठा device *dev,
				काष्ठा samsung_pinctrl_drv_data *drvdata,
				अचिन्हित पूर्णांक *cnt)
अणु
	काष्ठा pinctrl_desc *ctrldesc = &drvdata->pctl;
	काष्ठा samsung_pin_group *groups, *grp;
	स्थिर काष्ठा pinctrl_pin_desc *pdesc;
	पूर्णांक i;

	groups = devm_kसुस्मृति(dev, ctrldesc->npins, माप(*groups),
				GFP_KERNEL);
	अगर (!groups)
		वापस ERR_PTR(-EINVAL);
	grp = groups;

	pdesc = ctrldesc->pins;
	क्रम (i = 0; i < ctrldesc->npins; ++i, ++pdesc, ++grp) अणु
		grp->name = pdesc->name;
		grp->pins = &pdesc->number;
		grp->num_pins = 1;
	पूर्ण

	*cnt = ctrldesc->npins;
	वापस groups;
पूर्ण

अटल पूर्णांक samsung_pinctrl_create_function(काष्ठा device *dev,
				काष्ठा samsung_pinctrl_drv_data *drvdata,
				काष्ठा device_node *func_np,
				काष्ठा samsung_pmx_func *func)
अणु
	पूर्णांक npins;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (of_property_पढ़ो_u32(func_np, "samsung,pin-function", &func->val))
		वापस 0;

	npins = of_property_count_strings(func_np, "samsung,pins");
	अगर (npins < 1) अणु
		dev_err(dev, "invalid pin list in %pOFn node", func_np);
		वापस -EINVAL;
	पूर्ण

	func->name = func_np->full_name;

	func->groups = devm_kसुस्मृति(dev, npins, माप(अक्षर *), GFP_KERNEL);
	अगर (!func->groups)
		वापस -ENOMEM;

	क्रम (i = 0; i < npins; ++i) अणु
		स्थिर अक्षर *gname;

		ret = of_property_पढ़ो_string_index(func_np, "samsung,pins",
							i, &gname);
		अगर (ret) अणु
			dev_err(dev,
				"failed to read pin name %d from %pOFn node\n",
				i, func_np);
			वापस ret;
		पूर्ण

		func->groups[i] = gname;
	पूर्ण

	func->num_groups = npins;
	वापस 1;
पूर्ण

अटल काष्ठा samsung_pmx_func *samsung_pinctrl_create_functions(
				काष्ठा device *dev,
				काष्ठा samsung_pinctrl_drv_data *drvdata,
				अचिन्हित पूर्णांक *cnt)
अणु
	काष्ठा samsung_pmx_func *functions, *func;
	काष्ठा device_node *dev_np = dev->of_node;
	काष्ठा device_node *cfg_np;
	अचिन्हित पूर्णांक func_cnt = 0;
	पूर्णांक ret;

	/*
	 * Iterate over all the child nodes of the pin controller node
	 * and create pin groups and pin function lists.
	 */
	क्रम_each_child_of_node(dev_np, cfg_np) अणु
		काष्ठा device_node *func_np;

		अगर (!of_get_child_count(cfg_np)) अणु
			अगर (!of_find_property(cfg_np,
			    "samsung,pin-function", शून्य))
				जारी;
			++func_cnt;
			जारी;
		पूर्ण

		क्रम_each_child_of_node(cfg_np, func_np) अणु
			अगर (!of_find_property(func_np,
			    "samsung,pin-function", शून्य))
				जारी;
			++func_cnt;
		पूर्ण
	पूर्ण

	functions = devm_kसुस्मृति(dev, func_cnt, माप(*functions),
					GFP_KERNEL);
	अगर (!functions)
		वापस ERR_PTR(-ENOMEM);
	func = functions;

	/*
	 * Iterate over all the child nodes of the pin controller node
	 * and create pin groups and pin function lists.
	 */
	func_cnt = 0;
	क्रम_each_child_of_node(dev_np, cfg_np) अणु
		काष्ठा device_node *func_np;

		अगर (!of_get_child_count(cfg_np)) अणु
			ret = samsung_pinctrl_create_function(dev, drvdata,
							cfg_np, func);
			अगर (ret < 0) अणु
				of_node_put(cfg_np);
				वापस ERR_PTR(ret);
			पूर्ण
			अगर (ret > 0) अणु
				++func;
				++func_cnt;
			पूर्ण
			जारी;
		पूर्ण

		क्रम_each_child_of_node(cfg_np, func_np) अणु
			ret = samsung_pinctrl_create_function(dev, drvdata,
						func_np, func);
			अगर (ret < 0) अणु
				of_node_put(func_np);
				of_node_put(cfg_np);
				वापस ERR_PTR(ret);
			पूर्ण
			अगर (ret > 0) अणु
				++func;
				++func_cnt;
			पूर्ण
		पूर्ण
	पूर्ण

	*cnt = func_cnt;
	वापस functions;
पूर्ण

/*
 * Parse the inक्रमmation about all the available pin groups and pin functions
 * from device node of the pin-controller. A pin group is क्रमmed with all
 * the pins listed in the "samsung,pins" property.
 */

अटल पूर्णांक samsung_pinctrl_parse_dt(काष्ठा platक्रमm_device *pdev,
				    काष्ठा samsung_pinctrl_drv_data *drvdata)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा samsung_pin_group *groups;
	काष्ठा samsung_pmx_func *functions;
	अचिन्हित पूर्णांक grp_cnt = 0, func_cnt = 0;

	groups = samsung_pinctrl_create_groups(dev, drvdata, &grp_cnt);
	अगर (IS_ERR(groups)) अणु
		dev_err(dev, "failed to parse pin groups\n");
		वापस PTR_ERR(groups);
	पूर्ण

	functions = samsung_pinctrl_create_functions(dev, drvdata, &func_cnt);
	अगर (IS_ERR(functions)) अणु
		dev_err(dev, "failed to parse pin functions\n");
		वापस PTR_ERR(functions);
	पूर्ण

	drvdata->pin_groups = groups;
	drvdata->nr_groups = grp_cnt;
	drvdata->pmx_functions = functions;
	drvdata->nr_functions = func_cnt;

	वापस 0;
पूर्ण

/* रेजिस्टर the pinctrl पूर्णांकerface with the pinctrl subप्रणाली */
अटल पूर्णांक samsung_pinctrl_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
				    काष्ठा samsung_pinctrl_drv_data *drvdata)
अणु
	काष्ठा pinctrl_desc *ctrldesc = &drvdata->pctl;
	काष्ठा pinctrl_pin_desc *pindesc, *pdesc;
	काष्ठा samsung_pin_bank *pin_bank;
	अक्षर *pin_names;
	पूर्णांक pin, bank, ret;

	ctrldesc->name = "samsung-pinctrl";
	ctrldesc->owner = THIS_MODULE;
	ctrldesc->pctlops = &samsung_pctrl_ops;
	ctrldesc->pmxops = &samsung_pinmux_ops;
	ctrldesc->confops = &samsung_pinconf_ops;

	pindesc = devm_kसुस्मृति(&pdev->dev,
			       drvdata->nr_pins, माप(*pindesc),
			       GFP_KERNEL);
	अगर (!pindesc)
		वापस -ENOMEM;
	ctrldesc->pins = pindesc;
	ctrldesc->npins = drvdata->nr_pins;

	/* dynamically populate the pin number and pin name क्रम pindesc */
	क्रम (pin = 0, pdesc = pindesc; pin < ctrldesc->npins; pin++, pdesc++)
		pdesc->number = pin + drvdata->pin_base;

	/*
	 * allocate space क्रम storing the dynamically generated names क्रम all
	 * the pins which beदीर्घ to this pin-controller.
	 */
	pin_names = devm_kzalloc(&pdev->dev,
				 array3_size(माप(अक्षर), PIN_NAME_LENGTH,
					     drvdata->nr_pins),
				 GFP_KERNEL);
	अगर (!pin_names)
		वापस -ENOMEM;

	/* क्रम each pin, the name of the pin is pin-bank name + pin number */
	क्रम (bank = 0; bank < drvdata->nr_banks; bank++) अणु
		pin_bank = &drvdata->pin_banks[bank];
		क्रम (pin = 0; pin < pin_bank->nr_pins; pin++) अणु
			प्र_लिखो(pin_names, "%s-%d", pin_bank->name, pin);
			pdesc = pindesc + pin_bank->pin_base + pin;
			pdesc->name = pin_names;
			pin_names += PIN_NAME_LENGTH;
		पूर्ण
	पूर्ण

	ret = samsung_pinctrl_parse_dt(pdev, drvdata);
	अगर (ret)
		वापस ret;

	drvdata->pctl_dev = devm_pinctrl_रेजिस्टर(&pdev->dev, ctrldesc,
						  drvdata);
	अगर (IS_ERR(drvdata->pctl_dev)) अणु
		dev_err(&pdev->dev, "could not register pinctrl driver\n");
		वापस PTR_ERR(drvdata->pctl_dev);
	पूर्ण

	क्रम (bank = 0; bank < drvdata->nr_banks; ++bank) अणु
		pin_bank = &drvdata->pin_banks[bank];
		pin_bank->grange.name = pin_bank->name;
		pin_bank->grange.id = bank;
		pin_bank->grange.pin_base = drvdata->pin_base
						+ pin_bank->pin_base;
		pin_bank->grange.base = pin_bank->grange.pin_base;
		pin_bank->grange.npins = pin_bank->gpio_chip.ngpio;
		pin_bank->grange.gc = &pin_bank->gpio_chip;
		pinctrl_add_gpio_range(drvdata->pctl_dev, &pin_bank->grange);
	पूर्ण

	वापस 0;
पूर्ण

/* unरेजिस्टर the pinctrl पूर्णांकerface with the pinctrl subप्रणाली */
अटल पूर्णांक samsung_pinctrl_unरेजिस्टर(काष्ठा platक्रमm_device *pdev,
				      काष्ठा samsung_pinctrl_drv_data *drvdata)
अणु
	काष्ठा samsung_pin_bank *bank = drvdata->pin_banks;
	पूर्णांक i;

	क्रम (i = 0; i < drvdata->nr_banks; ++i, ++bank)
		pinctrl_हटाओ_gpio_range(drvdata->pctl_dev, &bank->grange);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gpio_chip samsung_gpiolib_chip = अणु
	.request = gpiochip_generic_request,
	.मुक्त = gpiochip_generic_मुक्त,
	.set = samsung_gpio_set,
	.get = samsung_gpio_get,
	.direction_input = samsung_gpio_direction_input,
	.direction_output = samsung_gpio_direction_output,
	.to_irq = samsung_gpio_to_irq,
	.owner = THIS_MODULE,
पूर्ण;

/* रेजिस्टर the gpiolib पूर्णांकerface with the gpiolib subप्रणाली */
अटल पूर्णांक samsung_gpiolib_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
				    काष्ठा samsung_pinctrl_drv_data *drvdata)
अणु
	काष्ठा samsung_pin_bank *bank = drvdata->pin_banks;
	काष्ठा gpio_chip *gc;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < drvdata->nr_banks; ++i, ++bank) अणु
		bank->gpio_chip = samsung_gpiolib_chip;

		gc = &bank->gpio_chip;
		gc->base = bank->grange.base;
		gc->ngpio = bank->nr_pins;
		gc->parent = &pdev->dev;
		gc->of_node = bank->of_node;
		gc->label = bank->name;

		ret = devm_gpiochip_add_data(&pdev->dev, gc, bank);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to register gpio_chip %s, error code: %d\n",
							gc->label, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा samsung_pin_ctrl *
samsung_pinctrl_get_soc_data_क्रम_of_alias(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर काष्ठा samsung_pinctrl_of_match_data *of_data;
	पूर्णांक id;

	id = of_alias_get_id(node, "pinctrl");
	अगर (id < 0) अणु
		dev_err(&pdev->dev, "failed to get alias id\n");
		वापस शून्य;
	पूर्ण

	of_data = of_device_get_match_data(&pdev->dev);
	अगर (id >= of_data->num_ctrl) अणु
		dev_err(&pdev->dev, "invalid alias id %d\n", id);
		वापस शून्य;
	पूर्ण

	वापस &(of_data->ctrl[id]);
पूर्ण

/* retrieve the soc specअगरic data */
अटल स्थिर काष्ठा samsung_pin_ctrl *
samsung_pinctrl_get_soc_data(काष्ठा samsung_pinctrl_drv_data *d,
			     काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *np;
	स्थिर काष्ठा samsung_pin_bank_data *bdata;
	स्थिर काष्ठा samsung_pin_ctrl *ctrl;
	काष्ठा samsung_pin_bank *bank;
	काष्ठा resource *res;
	व्योम __iomem *virt_base[SAMSUNG_PINCTRL_NUM_RESOURCES];
	अचिन्हित पूर्णांक i;

	ctrl = samsung_pinctrl_get_soc_data_क्रम_of_alias(pdev);
	अगर (!ctrl)
		वापस ERR_PTR(-ENOENT);

	d->suspend = ctrl->suspend;
	d->resume = ctrl->resume;
	d->nr_banks = ctrl->nr_banks;
	d->pin_banks = devm_kसुस्मृति(&pdev->dev, d->nr_banks,
					माप(*d->pin_banks), GFP_KERNEL);
	अगर (!d->pin_banks)
		वापस ERR_PTR(-ENOMEM);

	अगर (ctrl->nr_ext_resources + 1 > SAMSUNG_PINCTRL_NUM_RESOURCES)
		वापस ERR_PTR(-EINVAL);

	क्रम (i = 0; i < ctrl->nr_ext_resources + 1; i++) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		अगर (!res) अणु
			dev_err(&pdev->dev, "failed to get mem%d resource\n", i);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		virt_base[i] = devm_ioremap(&pdev->dev, res->start,
						resource_size(res));
		अगर (!virt_base[i]) अणु
			dev_err(&pdev->dev, "failed to ioremap %pR\n", res);
			वापस ERR_PTR(-EIO);
		पूर्ण
	पूर्ण

	bank = d->pin_banks;
	bdata = ctrl->pin_banks;
	क्रम (i = 0; i < ctrl->nr_banks; ++i, ++bdata, ++bank) अणु
		bank->type = bdata->type;
		bank->pctl_offset = bdata->pctl_offset;
		bank->nr_pins = bdata->nr_pins;
		bank->eपूर्णांक_func = bdata->eपूर्णांक_func;
		bank->eपूर्णांक_type = bdata->eपूर्णांक_type;
		bank->eपूर्णांक_mask = bdata->eपूर्णांक_mask;
		bank->eपूर्णांक_offset = bdata->eपूर्णांक_offset;
		bank->name = bdata->name;

		raw_spin_lock_init(&bank->slock);
		bank->drvdata = d;
		bank->pin_base = d->nr_pins;
		d->nr_pins += bank->nr_pins;

		bank->eपूर्णांक_base = virt_base[0];
		bank->pctl_base = virt_base[bdata->pctl_res_idx];
	पूर्ण
	/*
	 * Legacy platक्रमms should provide only one resource with IO memory.
	 * Store it as virt_base because legacy driver needs to access it
	 * through samsung_pinctrl_drv_data.
	 */
	d->virt_base = virt_base[0];

	क्रम_each_child_of_node(node, np) अणु
		अगर (!of_find_property(np, "gpio-controller", शून्य))
			जारी;
		bank = d->pin_banks;
		क्रम (i = 0; i < d->nr_banks; ++i, ++bank) अणु
			अगर (of_node_name_eq(np, bank->name)) अणु
				bank->of_node = np;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	d->pin_base = pin_base;
	pin_base += d->nr_pins;

	वापस ctrl;
पूर्ण

अटल पूर्णांक samsung_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata;
	स्थिर काष्ठा samsung_pin_ctrl *ctrl;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक ret;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	ctrl = samsung_pinctrl_get_soc_data(drvdata, pdev);
	अगर (IS_ERR(ctrl)) अणु
		dev_err(&pdev->dev, "driver data not available\n");
		वापस PTR_ERR(ctrl);
	पूर्ण
	drvdata->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res)
		drvdata->irq = res->start;

	अगर (ctrl->retention_data) अणु
		drvdata->retention_ctrl = ctrl->retention_data->init(drvdata,
							  ctrl->retention_data);
		अगर (IS_ERR(drvdata->retention_ctrl))
			वापस PTR_ERR(drvdata->retention_ctrl);
	पूर्ण

	ret = samsung_pinctrl_रेजिस्टर(pdev, drvdata);
	अगर (ret)
		वापस ret;

	ret = samsung_gpiolib_रेजिस्टर(pdev, drvdata);
	अगर (ret) अणु
		samsung_pinctrl_unरेजिस्टर(pdev, drvdata);
		वापस ret;
	पूर्ण

	अगर (ctrl->eपूर्णांक_gpio_init)
		ctrl->eपूर्णांक_gpio_init(drvdata);
	अगर (ctrl->eपूर्णांक_wkup_init)
		ctrl->eपूर्णांक_wkup_init(drvdata);

	platक्रमm_set_drvdata(pdev, drvdata);

	वापस 0;
पूर्ण

/*
 * samsung_pinctrl_suspend - save pinctrl state क्रम suspend
 *
 * Save data क्रम all banks handled by this device.
 */
अटल पूर्णांक __maybe_unused samsung_pinctrl_suspend(काष्ठा device *dev)
अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < drvdata->nr_banks; i++) अणु
		काष्ठा samsung_pin_bank *bank = &drvdata->pin_banks[i];
		व्योम __iomem *reg = bank->pctl_base + bank->pctl_offset;
		स्थिर u8 *offs = bank->type->reg_offset;
		स्थिर u8 *widths = bank->type->fld_width;
		क्रमागत pincfg_type type;

		/* Registers without a घातerकरोwn config aren't lost */
		अगर (!widths[PINCFG_TYPE_CON_PDN])
			जारी;

		क्रम (type = 0; type < PINCFG_TYPE_NUM; type++)
			अगर (widths[type])
				bank->pm_save[type] = पढ़ोl(reg + offs[type]);

		अगर (widths[PINCFG_TYPE_FUNC] * bank->nr_pins > 32) अणु
			/* Some banks have two config रेजिस्टरs */
			bank->pm_save[PINCFG_TYPE_NUM] =
				पढ़ोl(reg + offs[PINCFG_TYPE_FUNC] + 4);
			pr_debug("Save %s @ %p (con %#010x %08x)\n",
				 bank->name, reg,
				 bank->pm_save[PINCFG_TYPE_FUNC],
				 bank->pm_save[PINCFG_TYPE_NUM]);
		पूर्ण अन्यथा अणु
			pr_debug("Save %s @ %p (con %#010x)\n", bank->name,
				 reg, bank->pm_save[PINCFG_TYPE_FUNC]);
		पूर्ण
	पूर्ण

	अगर (drvdata->suspend)
		drvdata->suspend(drvdata);
	अगर (drvdata->retention_ctrl && drvdata->retention_ctrl->enable)
		drvdata->retention_ctrl->enable(drvdata);

	वापस 0;
पूर्ण

/*
 * samsung_pinctrl_resume - restore pinctrl state from suspend
 *
 * Restore one of the banks that was saved during suspend.
 *
 * We करोn't bother करोing anything complicated to aव्योम glitching lines since
 * we're called beक्रमe pad retention is turned off.
 */
अटल पूर्णांक __maybe_unused samsung_pinctrl_resume(काष्ठा device *dev)
अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata = dev_get_drvdata(dev);
	पूर्णांक i;

	अगर (drvdata->resume)
		drvdata->resume(drvdata);

	क्रम (i = 0; i < drvdata->nr_banks; i++) अणु
		काष्ठा samsung_pin_bank *bank = &drvdata->pin_banks[i];
		व्योम __iomem *reg = bank->pctl_base + bank->pctl_offset;
		स्थिर u8 *offs = bank->type->reg_offset;
		स्थिर u8 *widths = bank->type->fld_width;
		क्रमागत pincfg_type type;

		/* Registers without a घातerकरोwn config aren't lost */
		अगर (!widths[PINCFG_TYPE_CON_PDN])
			जारी;

		अगर (widths[PINCFG_TYPE_FUNC] * bank->nr_pins > 32) अणु
			/* Some banks have two config रेजिस्टरs */
			pr_debug("%s @ %p (con %#010x %08x => %#010x %08x)\n",
				 bank->name, reg,
				 पढ़ोl(reg + offs[PINCFG_TYPE_FUNC]),
				 पढ़ोl(reg + offs[PINCFG_TYPE_FUNC] + 4),
				 bank->pm_save[PINCFG_TYPE_FUNC],
				 bank->pm_save[PINCFG_TYPE_NUM]);
			ग_लिखोl(bank->pm_save[PINCFG_TYPE_NUM],
			       reg + offs[PINCFG_TYPE_FUNC] + 4);
		पूर्ण अन्यथा अणु
			pr_debug("%s @ %p (con %#010x => %#010x)\n", bank->name,
				 reg, पढ़ोl(reg + offs[PINCFG_TYPE_FUNC]),
				 bank->pm_save[PINCFG_TYPE_FUNC]);
		पूर्ण
		क्रम (type = 0; type < PINCFG_TYPE_NUM; type++)
			अगर (widths[type])
				ग_लिखोl(bank->pm_save[type], reg + offs[type]);
	पूर्ण

	अगर (drvdata->retention_ctrl && drvdata->retention_ctrl->disable)
		drvdata->retention_ctrl->disable(drvdata);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id samsung_pinctrl_dt_match[] = अणु
#अगर_घोषित CONFIG_PINCTRL_EXYNOS_ARM
	अणु .compatible = "samsung,exynos3250-pinctrl",
		.data = &exynos3250_of_data पूर्ण,
	अणु .compatible = "samsung,exynos4210-pinctrl",
		.data = &exynos4210_of_data पूर्ण,
	अणु .compatible = "samsung,exynos4x12-pinctrl",
		.data = &exynos4x12_of_data पूर्ण,
	अणु .compatible = "samsung,exynos5250-pinctrl",
		.data = &exynos5250_of_data पूर्ण,
	अणु .compatible = "samsung,exynos5260-pinctrl",
		.data = &exynos5260_of_data पूर्ण,
	अणु .compatible = "samsung,exynos5410-pinctrl",
		.data = &exynos5410_of_data पूर्ण,
	अणु .compatible = "samsung,exynos5420-pinctrl",
		.data = &exynos5420_of_data पूर्ण,
	अणु .compatible = "samsung,s5pv210-pinctrl",
		.data = &s5pv210_of_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_EXYNOS_ARM64
	अणु .compatible = "samsung,exynos5433-pinctrl",
		.data = &exynos5433_of_data पूर्ण,
	अणु .compatible = "samsung,exynos7-pinctrl",
		.data = &exynos7_of_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_S3C64XX
	अणु .compatible = "samsung,s3c64xx-pinctrl",
		.data = &s3c64xx_of_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_S3C24XX
	अणु .compatible = "samsung,s3c2412-pinctrl",
		.data = &s3c2412_of_data पूर्ण,
	अणु .compatible = "samsung,s3c2416-pinctrl",
		.data = &s3c2416_of_data पूर्ण,
	अणु .compatible = "samsung,s3c2440-pinctrl",
		.data = &s3c2440_of_data पूर्ण,
	अणु .compatible = "samsung,s3c2450-pinctrl",
		.data = &s3c2450_of_data पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops samsung_pinctrl_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(samsung_pinctrl_suspend,
				     samsung_pinctrl_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver samsung_pinctrl_driver = अणु
	.probe		= samsung_pinctrl_probe,
	.driver = अणु
		.name	= "samsung-pinctrl",
		.of_match_table = samsung_pinctrl_dt_match,
		.suppress_bind_attrs = true,
		.pm = &samsung_pinctrl_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init samsung_pinctrl_drv_रेजिस्टर(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&samsung_pinctrl_driver);
पूर्ण
postcore_initcall(samsung_pinctrl_drv_रेजिस्टर);
