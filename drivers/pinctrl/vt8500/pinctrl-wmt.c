<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pinctrl driver क्रम the Wondermedia SoC's
 *
 * Copyright (c) 2013 Tony Prisk <linux@prisktech.co.nz>
 */

#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "pinctrl-wmt.h"

अटल अंतरभूत व्योम wmt_setbits(काष्ठा wmt_pinctrl_data *data, u32 reg,
				 u32 mask)
अणु
	u32 val;

	val = पढ़ोl_relaxed(data->base + reg);
	val |= mask;
	ग_लिखोl_relaxed(val, data->base + reg);
पूर्ण

अटल अंतरभूत व्योम wmt_clearbits(काष्ठा wmt_pinctrl_data *data, u32 reg,
				   u32 mask)
अणु
	u32 val;

	val = पढ़ोl_relaxed(data->base + reg);
	val &= ~mask;
	ग_लिखोl_relaxed(val, data->base + reg);
पूर्ण

क्रमागत wmt_func_sel अणु
	WMT_FSEL_GPIO_IN = 0,
	WMT_FSEL_GPIO_OUT = 1,
	WMT_FSEL_ALT = 2,
	WMT_FSEL_COUNT = 3,
पूर्ण;

अटल स्थिर अक्षर * स्थिर wmt_functions[WMT_FSEL_COUNT] = अणु
	[WMT_FSEL_GPIO_IN] = "gpio_in",
	[WMT_FSEL_GPIO_OUT] = "gpio_out",
	[WMT_FSEL_ALT] = "alt",
पूर्ण;

अटल पूर्णांक wmt_pmx_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस WMT_FSEL_COUNT;
पूर्ण

अटल स्थिर अक्षर *wmt_pmx_get_function_name(काष्ठा pinctrl_dev *pctldev,
					     अचिन्हित selector)
अणु
	वापस wmt_functions[selector];
पूर्ण

अटल पूर्णांक wmt_pmx_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित selector,
				       स्थिर अक्षर * स्थिर **groups,
				       अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा wmt_pinctrl_data *data = pinctrl_dev_get_drvdata(pctldev);

	/* every pin करोes every function */
	*groups = data->groups;
	*num_groups = data->ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक wmt_set_pinmux(काष्ठा wmt_pinctrl_data *data, अचिन्हित func,
			  अचिन्हित pin)
अणु
	u32 bank = WMT_BANK_FROM_PIN(pin);
	u32 bit = WMT_BIT_FROM_PIN(pin);
	u32 reg_en = data->banks[bank].reg_en;
	u32 reg_dir = data->banks[bank].reg_dir;

	अगर (reg_dir == NO_REG) अणु
		dev_err(data->dev, "pin:%d no direction register defined\n",
			pin);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If reg_en == NO_REG, we assume it is a dedicated GPIO and cannot be
	 * disabled (as on VT8500) and that no alternate function is available.
	 */
	चयन (func) अणु
	हाल WMT_FSEL_GPIO_IN:
		अगर (reg_en != NO_REG)
			wmt_setbits(data, reg_en, BIT(bit));
		wmt_clearbits(data, reg_dir, BIT(bit));
		अवरोध;
	हाल WMT_FSEL_GPIO_OUT:
		अगर (reg_en != NO_REG)
			wmt_setbits(data, reg_en, BIT(bit));
		wmt_setbits(data, reg_dir, BIT(bit));
		अवरोध;
	हाल WMT_FSEL_ALT:
		अगर (reg_en == NO_REG) अणु
			dev_err(data->dev, "pin:%d no alt function available\n",
				pin);
			वापस -EINVAL;
		पूर्ण
		wmt_clearbits(data, reg_en, BIT(bit));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wmt_pmx_set_mux(काष्ठा pinctrl_dev *pctldev,
			   अचिन्हित func_selector,
			   अचिन्हित group_selector)
अणु
	काष्ठा wmt_pinctrl_data *data = pinctrl_dev_get_drvdata(pctldev);
	u32 pinnum = data->pins[group_selector].number;

	वापस wmt_set_pinmux(data, func_selector, pinnum);
पूर्ण

अटल व्योम wmt_pmx_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा pinctrl_gpio_range *range,
				      अचिन्हित offset)
अणु
	काष्ठा wmt_pinctrl_data *data = pinctrl_dev_get_drvdata(pctldev);

	/* disable by setting GPIO_IN */
	wmt_set_pinmux(data, WMT_FSEL_GPIO_IN, offset);
पूर्ण

अटल पूर्णांक wmt_pmx_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा pinctrl_gpio_range *range,
				      अचिन्हित offset,
				      bool input)
अणु
	काष्ठा wmt_pinctrl_data *data = pinctrl_dev_get_drvdata(pctldev);

	wmt_set_pinmux(data, (input ? WMT_FSEL_GPIO_IN : WMT_FSEL_GPIO_OUT),
		       offset);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops wmt_pinmux_ops = अणु
	.get_functions_count = wmt_pmx_get_functions_count,
	.get_function_name = wmt_pmx_get_function_name,
	.get_function_groups = wmt_pmx_get_function_groups,
	.set_mux = wmt_pmx_set_mux,
	.gpio_disable_मुक्त = wmt_pmx_gpio_disable_मुक्त,
	.gpio_set_direction = wmt_pmx_gpio_set_direction,
पूर्ण;

अटल पूर्णांक wmt_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा wmt_pinctrl_data *data = pinctrl_dev_get_drvdata(pctldev);

	वापस data->ngroups;
पूर्ण

अटल स्थिर अक्षर *wmt_get_group_name(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित selector)
अणु
	काष्ठा wmt_pinctrl_data *data = pinctrl_dev_get_drvdata(pctldev);

	वापस data->groups[selector];
पूर्ण

अटल पूर्णांक wmt_get_group_pins(काष्ठा pinctrl_dev *pctldev,
			      अचिन्हित selector,
			      स्थिर अचिन्हित **pins,
			      अचिन्हित *num_pins)
अणु
	काष्ठा wmt_pinctrl_data *data = pinctrl_dev_get_drvdata(pctldev);

	*pins = &data->pins[selector].number;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक wmt_pctl_find_group_by_pin(काष्ठा wmt_pinctrl_data *data, u32 pin)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < data->npins; i++) अणु
		अगर (data->pins[i].number == pin)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wmt_pctl_dt_node_to_map_func(काष्ठा wmt_pinctrl_data *data,
					काष्ठा device_node *np,
					u32 pin, u32 fnum,
					काष्ठा pinctrl_map **maps)
अणु
	पूर्णांक group;
	काष्ठा pinctrl_map *map = *maps;

	अगर (fnum >= ARRAY_SIZE(wmt_functions)) अणु
		dev_err(data->dev, "invalid wm,function %d\n", fnum);
		वापस -EINVAL;
	पूर्ण

	group = wmt_pctl_find_group_by_pin(data, pin);
	अगर (group < 0) अणु
		dev_err(data->dev, "unable to match pin %d to group\n", pin);
		वापस group;
	पूर्ण

	map->type = PIN_MAP_TYPE_MUX_GROUP;
	map->data.mux.group = data->groups[group];
	map->data.mux.function = wmt_functions[fnum];
	(*maps)++;

	वापस 0;
पूर्ण

अटल पूर्णांक wmt_pctl_dt_node_to_map_pull(काष्ठा wmt_pinctrl_data *data,
					काष्ठा device_node *np,
					u32 pin, u32 pull,
					काष्ठा pinctrl_map **maps)
अणु
	पूर्णांक group;
	अचिन्हित दीर्घ *configs;
	काष्ठा pinctrl_map *map = *maps;

	अगर (pull > 2) अणु
		dev_err(data->dev, "invalid wm,pull %d\n", pull);
		वापस -EINVAL;
	पूर्ण

	group = wmt_pctl_find_group_by_pin(data, pin);
	अगर (group < 0) अणु
		dev_err(data->dev, "unable to match pin %d to group\n", pin);
		वापस group;
	पूर्ण

	configs = kzalloc(माप(*configs), GFP_KERNEL);
	अगर (!configs)
		वापस -ENOMEM;

	चयन (pull) अणु
	हाल 0:
		configs[0] = PIN_CONFIG_BIAS_DISABLE;
		अवरोध;
	हाल 1:
		configs[0] = PIN_CONFIG_BIAS_PULL_DOWN;
		अवरोध;
	हाल 2:
		configs[0] = PIN_CONFIG_BIAS_PULL_UP;
		अवरोध;
	शेष:
		configs[0] = PIN_CONFIG_BIAS_DISABLE;
		dev_err(data->dev, "invalid pull state %d - disabling\n", pull);
	पूर्ण

	map->type = PIN_MAP_TYPE_CONFIGS_PIN;
	map->data.configs.group_or_pin = data->groups[group];
	map->data.configs.configs = configs;
	map->data.configs.num_configs = 1;
	(*maps)++;

	वापस 0;
पूर्ण

अटल व्योम wmt_pctl_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा pinctrl_map *maps,
				 अचिन्हित num_maps)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_maps; i++)
		अगर (maps[i].type == PIN_MAP_TYPE_CONFIGS_PIN)
			kमुक्त(maps[i].data.configs.configs);

	kमुक्त(maps);
पूर्ण

अटल पूर्णांक wmt_pctl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा device_node *np,
				   काष्ठा pinctrl_map **map,
				   अचिन्हित *num_maps)
अणु
	काष्ठा pinctrl_map *maps, *cur_map;
	काष्ठा property *pins, *funcs, *pulls;
	u32 pin, func, pull;
	पूर्णांक num_pins, num_funcs, num_pulls, maps_per_pin;
	पूर्णांक i, err;
	काष्ठा wmt_pinctrl_data *data = pinctrl_dev_get_drvdata(pctldev);

	pins = of_find_property(np, "wm,pins", शून्य);
	अगर (!pins) अणु
		dev_err(data->dev, "missing wmt,pins property\n");
		वापस -EINVAL;
	पूर्ण

	funcs = of_find_property(np, "wm,function", शून्य);
	pulls = of_find_property(np, "wm,pull", शून्य);

	अगर (!funcs && !pulls) अणु
		dev_err(data->dev, "neither wm,function nor wm,pull specified\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * The following lines calculate how many values are defined क्रम each
	 * of the properties.
	 */
	num_pins = pins->length / माप(u32);
	num_funcs = funcs ? (funcs->length / माप(u32)) : 0;
	num_pulls = pulls ? (pulls->length / माप(u32)) : 0;

	अगर (num_funcs > 1 && num_funcs != num_pins) अणु
		dev_err(data->dev, "wm,function must have 1 or %d entries\n",
			num_pins);
		वापस -EINVAL;
	पूर्ण

	अगर (num_pulls > 1 && num_pulls != num_pins) अणु
		dev_err(data->dev, "wm,pull must have 1 or %d entries\n",
			num_pins);
		वापस -EINVAL;
	पूर्ण

	maps_per_pin = 0;
	अगर (num_funcs)
		maps_per_pin++;
	अगर (num_pulls)
		maps_per_pin++;

	cur_map = maps = kसुस्मृति(num_pins * maps_per_pin, माप(*maps),
				 GFP_KERNEL);
	अगर (!maps)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_pins; i++) अणु
		err = of_property_पढ़ो_u32_index(np, "wm,pins", i, &pin);
		अगर (err)
			जाओ fail;

		अगर (pin >= (data->nbanks * 32)) अणु
			dev_err(data->dev, "invalid wm,pins value\n");
			err = -EINVAL;
			जाओ fail;
		पूर्ण

		अगर (num_funcs) अणु
			err = of_property_पढ़ो_u32_index(np, "wm,function",
						(num_funcs > 1 ? i : 0), &func);
			अगर (err)
				जाओ fail;

			err = wmt_pctl_dt_node_to_map_func(data, np, pin, func,
							   &cur_map);
			अगर (err)
				जाओ fail;
		पूर्ण

		अगर (num_pulls) अणु
			err = of_property_पढ़ो_u32_index(np, "wm,pull",
						(num_pulls > 1 ? i : 0), &pull);
			अगर (err)
				जाओ fail;

			err = wmt_pctl_dt_node_to_map_pull(data, np, pin, pull,
							   &cur_map);
			अगर (err)
				जाओ fail;
		पूर्ण
	पूर्ण
	*map = maps;
	*num_maps = num_pins * maps_per_pin;
	वापस 0;

/*
 * The fail path हटाओs any maps that have been allocated. The fail path is
 * only called from code after maps has been kzalloc'd. It is also safe to
 * pass 'num_pins * maps_per_pin' as the map count even though we probably
 * failed beक्रमe all the mappings were पढ़ो as all maps are allocated at once,
 * and configs are only allocated क्रम .type = PIN_MAP_TYPE_CONFIGS_PIN - there
 * is no failpath where a config can be allocated without .type being set.
 */
fail:
	wmt_pctl_dt_मुक्त_map(pctldev, maps, num_pins * maps_per_pin);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops wmt_pctl_ops = अणु
	.get_groups_count = wmt_get_groups_count,
	.get_group_name	= wmt_get_group_name,
	.get_group_pins	= wmt_get_group_pins,
	.dt_node_to_map = wmt_pctl_dt_node_to_map,
	.dt_मुक्त_map = wmt_pctl_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक wmt_pinconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			   अचिन्हित दीर्घ *config)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक wmt_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			   अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा wmt_pinctrl_data *data = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param;
	u32 arg;
	u32 bank = WMT_BANK_FROM_PIN(pin);
	u32 bit = WMT_BIT_FROM_PIN(pin);
	u32 reg_pull_en = data->banks[bank].reg_pull_en;
	u32 reg_pull_cfg = data->banks[bank].reg_pull_cfg;
	पूर्णांक i;

	अगर ((reg_pull_en == NO_REG) || (reg_pull_cfg == NO_REG)) अणु
		dev_err(data->dev, "bias functions not supported on pin %d\n",
			pin);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		अगर ((param == PIN_CONFIG_BIAS_PULL_DOWN) ||
		    (param == PIN_CONFIG_BIAS_PULL_UP)) अणु
			अगर (arg == 0)
				param = PIN_CONFIG_BIAS_DISABLE;
		पूर्ण

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			wmt_clearbits(data, reg_pull_en, BIT(bit));
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			wmt_clearbits(data, reg_pull_cfg, BIT(bit));
			wmt_setbits(data, reg_pull_en, BIT(bit));
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			wmt_setbits(data, reg_pull_cfg, BIT(bit));
			wmt_setbits(data, reg_pull_en, BIT(bit));
			अवरोध;
		शेष:
			dev_err(data->dev, "unknown pinconf param\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops wmt_pinconf_ops = अणु
	.pin_config_get = wmt_pinconf_get,
	.pin_config_set = wmt_pinconf_set,
पूर्ण;

अटल काष्ठा pinctrl_desc wmt_desc = अणु
	.owner = THIS_MODULE,
	.name = "pinctrl-wmt",
	.pctlops = &wmt_pctl_ops,
	.pmxops = &wmt_pinmux_ops,
	.confops = &wmt_pinconf_ops,
पूर्ण;

अटल पूर्णांक wmt_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wmt_pinctrl_data *data = gpiochip_get_data(chip);
	u32 bank = WMT_BANK_FROM_PIN(offset);
	u32 bit = WMT_BIT_FROM_PIN(offset);
	u32 reg_dir = data->banks[bank].reg_dir;
	u32 val;

	val = पढ़ोl_relaxed(data->base + reg_dir);
	अगर (val & BIT(bit))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक wmt_gpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wmt_pinctrl_data *data = gpiochip_get_data(chip);
	u32 bank = WMT_BANK_FROM_PIN(offset);
	u32 bit = WMT_BIT_FROM_PIN(offset);
	u32 reg_data_in = data->banks[bank].reg_data_in;

	अगर (reg_data_in == NO_REG) अणु
		dev_err(data->dev, "no data in register defined\n");
		वापस -EINVAL;
	पूर्ण

	वापस !!(पढ़ोl_relaxed(data->base + reg_data_in) & BIT(bit));
पूर्ण

अटल व्योम wmt_gpio_set_value(काष्ठा gpio_chip *chip, अचिन्हित offset,
			       पूर्णांक val)
अणु
	काष्ठा wmt_pinctrl_data *data = gpiochip_get_data(chip);
	u32 bank = WMT_BANK_FROM_PIN(offset);
	u32 bit = WMT_BIT_FROM_PIN(offset);
	u32 reg_data_out = data->banks[bank].reg_data_out;

	अगर (reg_data_out == NO_REG) अणु
		dev_err(data->dev, "no data out register defined\n");
		वापस;
	पूर्ण

	अगर (val)
		wmt_setbits(data, reg_data_out, BIT(bit));
	अन्यथा
		wmt_clearbits(data, reg_data_out, BIT(bit));
पूर्ण

अटल पूर्णांक wmt_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + offset);
पूर्ण

अटल पूर्णांक wmt_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
				     पूर्णांक value)
अणु
	wmt_gpio_set_value(chip, offset, value);
	वापस pinctrl_gpio_direction_output(chip->base + offset);
पूर्ण

अटल स्थिर काष्ठा gpio_chip wmt_gpio_chip = अणु
	.label = "gpio-wmt",
	.owner = THIS_MODULE,
	.request = gpiochip_generic_request,
	.मुक्त = gpiochip_generic_मुक्त,
	.get_direction = wmt_gpio_get_direction,
	.direction_input = wmt_gpio_direction_input,
	.direction_output = wmt_gpio_direction_output,
	.get = wmt_gpio_get_value,
	.set = wmt_gpio_set_value,
	.can_sleep = false,
पूर्ण;

पूर्णांक wmt_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
		      काष्ठा wmt_pinctrl_data *data)
अणु
	पूर्णांक err;

	data->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->base))
		वापस PTR_ERR(data->base);

	wmt_desc.pins = data->pins;
	wmt_desc.npins = data->npins;

	data->gpio_chip = wmt_gpio_chip;
	data->gpio_chip.parent = &pdev->dev;
	data->gpio_chip.of_node = pdev->dev.of_node;
	data->gpio_chip.ngpio = data->nbanks * 32;

	platक्रमm_set_drvdata(pdev, data);

	data->dev = &pdev->dev;

	data->pctl_dev = devm_pinctrl_रेजिस्टर(&pdev->dev, &wmt_desc, data);
	अगर (IS_ERR(data->pctl_dev)) अणु
		dev_err(&pdev->dev, "Failed to register pinctrl\n");
		वापस PTR_ERR(data->pctl_dev);
	पूर्ण

	err = gpiochip_add_data(&data->gpio_chip, data);
	अगर (err) अणु
		dev_err(&pdev->dev, "could not add GPIO chip\n");
		वापस err;
	पूर्ण

	err = gpiochip_add_pin_range(&data->gpio_chip, dev_name(data->dev),
				     0, 0, data->nbanks * 32);
	अगर (err)
		जाओ fail_range;

	dev_info(&pdev->dev, "Pin controller initialized\n");

	वापस 0;

fail_range:
	gpiochip_हटाओ(&data->gpio_chip);
	वापस err;
पूर्ण
