<शैली गुरु>
/*
 * Driver क्रम the ST Microelectronics SPEAr pinmux
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * Inspired from:
 * - U300 Pinctl drivers
 * - Tegra Pinctl drivers
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "pinctrl-spear.h"

#घोषणा DRIVER_NAME "spear-pinmux"

अटल व्योम muxregs_endisable(काष्ठा spear_pmx *pmx,
		काष्ठा spear_muxreg *muxregs, u8 count, bool enable)
अणु
	काष्ठा spear_muxreg *muxreg;
	u32 val, temp, j;

	क्रम (j = 0; j < count; j++) अणु
		muxreg = &muxregs[j];

		val = pmx_पढ़ोl(pmx, muxreg->reg);
		val &= ~muxreg->mask;

		अगर (enable)
			temp = muxreg->val;
		अन्यथा
			temp = ~muxreg->val;

		val |= muxreg->mask & temp;
		pmx_ग_लिखोl(pmx, val, muxreg->reg);
	पूर्ण
पूर्ण

अटल पूर्णांक set_mode(काष्ठा spear_pmx *pmx, पूर्णांक mode)
अणु
	काष्ठा spear_pmx_mode *pmx_mode = शून्य;
	पूर्णांक i;
	u32 val;

	अगर (!pmx->machdata->pmx_modes || !pmx->machdata->npmx_modes)
		वापस -EINVAL;

	क्रम (i = 0; i < pmx->machdata->npmx_modes; i++) अणु
		अगर (pmx->machdata->pmx_modes[i]->mode == (1 << mode)) अणु
			pmx_mode = pmx->machdata->pmx_modes[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!pmx_mode)
		वापस -EINVAL;

	val = pmx_पढ़ोl(pmx, pmx_mode->reg);
	val &= ~pmx_mode->mask;
	val |= pmx_mode->val;
	pmx_ग_लिखोl(pmx, val, pmx_mode->reg);

	pmx->machdata->mode = pmx_mode->mode;
	dev_info(pmx->dev, "Configured Mode: %s with id: %x\n\n",
			pmx_mode->name ? pmx_mode->name : "no_name",
			pmx_mode->reg);

	वापस 0;
पूर्ण

व्योम pmx_init_gpio_pingroup_addr(काष्ठा spear_gpio_pingroup *gpio_pingroup,
				 अचिन्हित count, u16 reg)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < count; i++)
		क्रम (j = 0; j < gpio_pingroup[i].nmuxregs; j++)
			gpio_pingroup[i].muxregs[j].reg = reg;
पूर्ण

व्योम pmx_init_addr(काष्ठा spear_pinctrl_machdata *machdata, u16 reg)
अणु
	काष्ठा spear_pingroup *pgroup;
	काष्ठा spear_modemux *modemux;
	पूर्णांक i, j, group;

	क्रम (group = 0; group < machdata->ngroups; group++) अणु
		pgroup = machdata->groups[group];

		क्रम (i = 0; i < pgroup->nmodemuxs; i++) अणु
			modemux = &pgroup->modemuxs[i];

			क्रम (j = 0; j < modemux->nmuxregs; j++)
				अगर (modemux->muxregs[j].reg == 0xFFFF)
					modemux->muxregs[j].reg = reg;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक spear_pinctrl_get_groups_cnt(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा spear_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->machdata->ngroups;
पूर्ण

अटल स्थिर अक्षर *spear_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित group)
अणु
	काष्ठा spear_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->machdata->groups[group]->name;
पूर्ण

अटल पूर्णांक spear_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित group, स्थिर अचिन्हित **pins, अचिन्हित *num_pins)
अणु
	काष्ठा spear_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	*pins = pmx->machdata->groups[group]->pins;
	*num_pins = pmx->machdata->groups[group]->npins;

	वापस 0;
पूर्ण

अटल व्योम spear_pinctrl_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
		काष्ठा seq_file *s, अचिन्हित offset)
अणु
	seq_म_लिखो(s, " " DRIVER_NAME);
पूर्ण

अटल पूर्णांक spear_pinctrl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
					काष्ठा device_node *np_config,
					काष्ठा pinctrl_map **map,
					अचिन्हित *num_maps)
अणु
	काष्ठा spear_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा device_node *np;
	काष्ठा property *prop;
	स्थिर अक्षर *function, *group;
	पूर्णांक ret, index = 0, count = 0;

	/* calculate number of maps required */
	क्रम_each_child_of_node(np_config, np) अणु
		ret = of_property_पढ़ो_string(np, "st,function", &function);
		अगर (ret < 0) अणु
			of_node_put(np);
			वापस ret;
		पूर्ण

		ret = of_property_count_strings(np, "st,pins");
		अगर (ret < 0) अणु
			of_node_put(np);
			वापस ret;
		पूर्ण

		count += ret;
	पूर्ण

	अगर (!count) अणु
		dev_err(pmx->dev, "No child nodes passed via DT\n");
		वापस -ENODEV;
	पूर्ण

	*map = kसुस्मृति(count, माप(**map), GFP_KERNEL);
	अगर (!*map)
		वापस -ENOMEM;

	क्रम_each_child_of_node(np_config, np) अणु
		of_property_पढ़ो_string(np, "st,function", &function);
		of_property_क्रम_each_string(np, "st,pins", prop, group) अणु
			(*map)[index].type = PIN_MAP_TYPE_MUX_GROUP;
			(*map)[index].data.mux.group = group;
			(*map)[index].data.mux.function = function;
			index++;
		पूर्ण
	पूर्ण

	*num_maps = count;

	वापस 0;
पूर्ण

अटल व्योम spear_pinctrl_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा pinctrl_map *map,
				      अचिन्हित num_maps)
अणु
	kमुक्त(map);
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops spear_pinctrl_ops = अणु
	.get_groups_count = spear_pinctrl_get_groups_cnt,
	.get_group_name = spear_pinctrl_get_group_name,
	.get_group_pins = spear_pinctrl_get_group_pins,
	.pin_dbg_show = spear_pinctrl_pin_dbg_show,
	.dt_node_to_map = spear_pinctrl_dt_node_to_map,
	.dt_मुक्त_map = spear_pinctrl_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक spear_pinctrl_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा spear_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->machdata->nfunctions;
पूर्ण

अटल स्थिर अक्षर *spear_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित function)
अणु
	काष्ठा spear_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->machdata->functions[function]->name;
पूर्ण

अटल पूर्णांक spear_pinctrl_get_func_groups(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित function, स्थिर अक्षर *स्थिर **groups,
		अचिन्हित * स्थिर ngroups)
अणु
	काष्ठा spear_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	*groups = pmx->machdata->functions[function]->groups;
	*ngroups = pmx->machdata->functions[function]->ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक spear_pinctrl_endisable(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित function, अचिन्हित group, bool enable)
अणु
	काष्ठा spear_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा spear_pingroup *pgroup;
	स्थिर काष्ठा spear_modemux *modemux;
	पूर्णांक i;
	bool found = false;

	pgroup = pmx->machdata->groups[group];

	क्रम (i = 0; i < pgroup->nmodemuxs; i++) अणु
		modemux = &pgroup->modemuxs[i];

		/* SoC have any modes */
		अगर (pmx->machdata->modes_supported) अणु
			अगर (!(pmx->machdata->mode & modemux->modes))
				जारी;
		पूर्ण

		found = true;
		muxregs_endisable(pmx, modemux->muxregs, modemux->nmuxregs,
				enable);
	पूर्ण

	अगर (!found) अणु
		dev_err(pmx->dev, "pinmux group: %s not supported\n",
				pgroup->name);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spear_pinctrl_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित function,
		अचिन्हित group)
अणु
	वापस spear_pinctrl_endisable(pctldev, function, group, true);
पूर्ण

/* gpio with pinmux */
अटल काष्ठा spear_gpio_pingroup *get_gpio_pingroup(काष्ठा spear_pmx *pmx,
		अचिन्हित pin)
अणु
	काष्ठा spear_gpio_pingroup *gpio_pingroup;
	पूर्णांक i, j;

	अगर (!pmx->machdata->gpio_pingroups)
		वापस शून्य;

	क्रम (i = 0; i < pmx->machdata->ngpio_pingroups; i++) अणु
		gpio_pingroup = &pmx->machdata->gpio_pingroups[i];

		क्रम (j = 0; j < gpio_pingroup->npins; j++) अणु
			अगर (gpio_pingroup->pins[j] == pin)
				वापस gpio_pingroup;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक gpio_request_endisable(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_gpio_range *range, अचिन्हित offset, bool enable)
अणु
	काष्ठा spear_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा spear_pinctrl_machdata *machdata = pmx->machdata;
	काष्ठा spear_gpio_pingroup *gpio_pingroup;

	/*
	 * Some SoC have configuration options applicable to group of pins,
	 * rather than a single pin.
	 */
	gpio_pingroup = get_gpio_pingroup(pmx, offset);
	अगर (gpio_pingroup)
		muxregs_endisable(pmx, gpio_pingroup->muxregs,
				gpio_pingroup->nmuxregs, enable);

	/*
	 * SoC may need some extra configurations, or configurations क्रम single
	 * pin
	 */
	अगर (machdata->gpio_request_endisable)
		machdata->gpio_request_endisable(pmx, offset, enable);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_gpio_range *range, अचिन्हित offset)
अणु
	वापस gpio_request_endisable(pctldev, range, offset, true);
पूर्ण

अटल व्योम gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_gpio_range *range, अचिन्हित offset)
अणु
	gpio_request_endisable(pctldev, range, offset, false);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops spear_pinmux_ops = अणु
	.get_functions_count = spear_pinctrl_get_funcs_count,
	.get_function_name = spear_pinctrl_get_func_name,
	.get_function_groups = spear_pinctrl_get_func_groups,
	.set_mux = spear_pinctrl_set_mux,
	.gpio_request_enable = gpio_request_enable,
	.gpio_disable_मुक्त = gpio_disable_मुक्त,
पूर्ण;

अटल काष्ठा pinctrl_desc spear_pinctrl_desc = अणु
	.name = DRIVER_NAME,
	.pctlops = &spear_pinctrl_ops,
	.pmxops = &spear_pinmux_ops,
	.owner = THIS_MODULE,
पूर्ण;

पूर्णांक spear_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			काष्ठा spear_pinctrl_machdata *machdata)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा spear_pmx *pmx;

	अगर (!machdata)
		वापस -ENODEV;

	pmx = devm_kzalloc(&pdev->dev, माप(*pmx), GFP_KERNEL);
	अगर (!pmx)
		वापस -ENOMEM;

	pmx->vbase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pmx->vbase))
		वापस PTR_ERR(pmx->vbase);

	pmx->dev = &pdev->dev;
	pmx->machdata = machdata;

	/* configure mode, अगर supported by SoC */
	अगर (machdata->modes_supported) अणु
		पूर्णांक mode = 0;

		अगर (of_property_पढ़ो_u32(np, "st,pinmux-mode", &mode)) अणु
			dev_err(&pdev->dev, "OF: pinmux mode not passed\n");
			वापस -EINVAL;
		पूर्ण

		अगर (set_mode(pmx, mode)) अणु
			dev_err(&pdev->dev, "OF: Couldn't configure mode: %x\n",
					mode);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, pmx);

	spear_pinctrl_desc.pins = machdata->pins;
	spear_pinctrl_desc.npins = machdata->npins;

	pmx->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, &spear_pinctrl_desc, pmx);
	अगर (IS_ERR(pmx->pctl)) अणु
		dev_err(&pdev->dev, "Couldn't register pinctrl driver\n");
		वापस PTR_ERR(pmx->pctl);
	पूर्ण

	वापस 0;
पूर्ण
