<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2012 Freescale Semiconductor, Inc.

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश "../core.h"
#समावेश "pinctrl-mxs.h"

#घोषणा SUFFIX_LEN	4

काष्ठा mxs_pinctrl_data अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
	व्योम __iomem *base;
	काष्ठा mxs_pinctrl_soc_data *soc;
पूर्ण;

अटल पूर्णांक mxs_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा mxs_pinctrl_data *d = pinctrl_dev_get_drvdata(pctldev);

	वापस d->soc->ngroups;
पूर्ण

अटल स्थिर अक्षर *mxs_get_group_name(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित group)
अणु
	काष्ठा mxs_pinctrl_data *d = pinctrl_dev_get_drvdata(pctldev);

	वापस d->soc->groups[group].name;
पूर्ण

अटल पूर्णांक mxs_get_group_pins(काष्ठा pinctrl_dev *pctldev, अचिन्हित group,
			      स्थिर अचिन्हित **pins, अचिन्हित *num_pins)
अणु
	काष्ठा mxs_pinctrl_data *d = pinctrl_dev_get_drvdata(pctldev);

	*pins = d->soc->groups[group].pins;
	*num_pins = d->soc->groups[group].npins;

	वापस 0;
पूर्ण

अटल व्योम mxs_pin_dbg_show(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
			     अचिन्हित offset)
अणु
	seq_म_लिखो(s, " %s", dev_name(pctldev->dev));
पूर्ण

अटल पूर्णांक mxs_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
			      काष्ठा device_node *np,
			      काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	काष्ठा pinctrl_map *new_map;
	अक्षर *group = शून्य;
	अचिन्हित new_num = 1;
	अचिन्हित दीर्घ config = 0;
	अचिन्हित दीर्घ *pconfig;
	पूर्णांक length = म_माप(np->name) + SUFFIX_LEN;
	bool purecfg = false;
	u32 val, reg;
	पूर्णांक ret, i = 0;

	/* Check क्रम pin config node which has no 'reg' property */
	अगर (of_property_पढ़ो_u32(np, "reg", &reg))
		purecfg = true;

	ret = of_property_पढ़ो_u32(np, "fsl,drive-strength", &val);
	अगर (!ret)
		config = val | MA_PRESENT;
	ret = of_property_पढ़ो_u32(np, "fsl,voltage", &val);
	अगर (!ret)
		config |= val << VOL_SHIFT | VOL_PRESENT;
	ret = of_property_पढ़ो_u32(np, "fsl,pull-up", &val);
	अगर (!ret)
		config |= val << PULL_SHIFT | PULL_PRESENT;

	/* Check क्रम group node which has both mux and config settings */
	अगर (!purecfg && config)
		new_num = 2;

	new_map = kसुस्मृति(new_num, माप(*new_map), GFP_KERNEL);
	अगर (!new_map)
		वापस -ENOMEM;

	अगर (!purecfg) अणु
		new_map[i].type = PIN_MAP_TYPE_MUX_GROUP;
		new_map[i].data.mux.function = np->name;

		/* Compose group name */
		group = kzalloc(length, GFP_KERNEL);
		अगर (!group) अणु
			ret = -ENOMEM;
			जाओ मुक्त;
		पूर्ण
		snम_लिखो(group, length, "%s.%d", np->name, reg);
		new_map[i].data.mux.group = group;
		i++;
	पूर्ण

	अगर (config) अणु
		pconfig = kmemdup(&config, माप(config), GFP_KERNEL);
		अगर (!pconfig) अणु
			ret = -ENOMEM;
			जाओ मुक्त_group;
		पूर्ण

		new_map[i].type = PIN_MAP_TYPE_CONFIGS_GROUP;
		new_map[i].data.configs.group_or_pin = purecfg ? np->name :
								 group;
		new_map[i].data.configs.configs = pconfig;
		new_map[i].data.configs.num_configs = 1;
	पूर्ण

	*map = new_map;
	*num_maps = new_num;

	वापस 0;

मुक्त_group:
	अगर (!purecfg)
		kमुक्त(group);
मुक्त:
	kमुक्त(new_map);
	वापस ret;
पूर्ण

अटल व्योम mxs_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
			    काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
	u32 i;

	क्रम (i = 0; i < num_maps; i++) अणु
		अगर (map[i].type == PIN_MAP_TYPE_MUX_GROUP)
			kमुक्त(map[i].data.mux.group);
		अगर (map[i].type == PIN_MAP_TYPE_CONFIGS_GROUP)
			kमुक्त(map[i].data.configs.configs);
	पूर्ण

	kमुक्त(map);
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops mxs_pinctrl_ops = अणु
	.get_groups_count = mxs_get_groups_count,
	.get_group_name = mxs_get_group_name,
	.get_group_pins = mxs_get_group_pins,
	.pin_dbg_show = mxs_pin_dbg_show,
	.dt_node_to_map = mxs_dt_node_to_map,
	.dt_मुक्त_map = mxs_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक mxs_pinctrl_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा mxs_pinctrl_data *d = pinctrl_dev_get_drvdata(pctldev);

	वापस d->soc->nfunctions;
पूर्ण

अटल स्थिर अक्षर *mxs_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
					     अचिन्हित function)
अणु
	काष्ठा mxs_pinctrl_data *d = pinctrl_dev_get_drvdata(pctldev);

	वापस d->soc->functions[function].name;
पूर्ण

अटल पूर्णांक mxs_pinctrl_get_func_groups(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित group,
				       स्थिर अक्षर * स्थिर **groups,
				       अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा mxs_pinctrl_data *d = pinctrl_dev_get_drvdata(pctldev);

	*groups = d->soc->functions[group].groups;
	*num_groups = d->soc->functions[group].ngroups;

	वापस 0;
पूर्ण

अटल व्योम mxs_pinctrl_rmwl(u32 value, u32 mask, u8 shअगरt, व्योम __iomem *reg)
अणु
	u32 पंचांगp;

	पंचांगp = पढ़ोl(reg);
	पंचांगp &= ~(mask << shअगरt);
	पंचांगp |= value << shअगरt;
	ग_लिखोl(पंचांगp, reg);
पूर्ण

अटल पूर्णांक mxs_pinctrl_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित selector,
			       अचिन्हित group)
अणु
	काष्ठा mxs_pinctrl_data *d = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा mxs_group *g = &d->soc->groups[group];
	व्योम __iomem *reg;
	u8 bank, shअगरt;
	u16 pin;
	u32 i;

	क्रम (i = 0; i < g->npins; i++) अणु
		bank = PINID_TO_BANK(g->pins[i]);
		pin = PINID_TO_PIN(g->pins[i]);
		reg = d->base + d->soc->regs->muxsel;
		reg += bank * 0x20 + pin / 16 * 0x10;
		shअगरt = pin % 16 * 2;

		mxs_pinctrl_rmwl(g->muxsel[i], 0x3, shअगरt, reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops mxs_pinmux_ops = अणु
	.get_functions_count = mxs_pinctrl_get_funcs_count,
	.get_function_name = mxs_pinctrl_get_func_name,
	.get_function_groups = mxs_pinctrl_get_func_groups,
	.set_mux = mxs_pinctrl_set_mux,
पूर्ण;

अटल पूर्णांक mxs_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			   अचिन्हित pin, अचिन्हित दीर्घ *config)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक mxs_pinconf_set(काष्ठा pinctrl_dev *pctldev,
			   अचिन्हित pin, अचिन्हित दीर्घ *configs,
			   अचिन्हित num_configs)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक mxs_pinconf_group_get(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित group, अचिन्हित दीर्घ *config)
अणु
	काष्ठा mxs_pinctrl_data *d = pinctrl_dev_get_drvdata(pctldev);

	*config = d->soc->groups[group].config;

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित group, अचिन्हित दीर्घ *configs,
				 अचिन्हित num_configs)
अणु
	काष्ठा mxs_pinctrl_data *d = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा mxs_group *g = &d->soc->groups[group];
	व्योम __iomem *reg;
	u8 ma, vol, pull, bank, shअगरt;
	u16 pin;
	u32 i;
	पूर्णांक n;
	अचिन्हित दीर्घ config;

	क्रम (n = 0; n < num_configs; n++) अणु
		config = configs[n];

		ma = CONFIG_TO_MA(config);
		vol = CONFIG_TO_VOL(config);
		pull = CONFIG_TO_PULL(config);

		क्रम (i = 0; i < g->npins; i++) अणु
			bank = PINID_TO_BANK(g->pins[i]);
			pin = PINID_TO_PIN(g->pins[i]);

			/* drive */
			reg = d->base + d->soc->regs->drive;
			reg += bank * 0x40 + pin / 8 * 0x10;

			/* mA */
			अगर (config & MA_PRESENT) अणु
				shअगरt = pin % 8 * 4;
				mxs_pinctrl_rmwl(ma, 0x3, shअगरt, reg);
			पूर्ण

			/* vol */
			अगर (config & VOL_PRESENT) अणु
				shअगरt = pin % 8 * 4 + 2;
				अगर (vol)
					ग_लिखोl(1 << shअगरt, reg + SET);
				अन्यथा
					ग_लिखोl(1 << shअगरt, reg + CLR);
			पूर्ण

			/* pull */
			अगर (config & PULL_PRESENT) अणु
				reg = d->base + d->soc->regs->pull;
				reg += bank * 0x10;
				shअगरt = pin;
				अगर (pull)
					ग_लिखोl(1 << shअगरt, reg + SET);
				अन्यथा
					ग_लिखोl(1 << shअगरt, reg + CLR);
			पूर्ण
		पूर्ण

		/* cache the config value क्रम mxs_pinconf_group_get() */
		g->config = config;

	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

अटल व्योम mxs_pinconf_dbg_show(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा seq_file *s, अचिन्हित pin)
अणु
	/* Not support */
पूर्ण

अटल व्योम mxs_pinconf_group_dbg_show(काष्ठा pinctrl_dev *pctldev,
				       काष्ठा seq_file *s, अचिन्हित group)
अणु
	अचिन्हित दीर्घ config;

	अगर (!mxs_pinconf_group_get(pctldev, group, &config))
		seq_म_लिखो(s, "0x%lx", config);
पूर्ण

अटल स्थिर काष्ठा pinconf_ops mxs_pinconf_ops = अणु
	.pin_config_get = mxs_pinconf_get,
	.pin_config_set = mxs_pinconf_set,
	.pin_config_group_get = mxs_pinconf_group_get,
	.pin_config_group_set = mxs_pinconf_group_set,
	.pin_config_dbg_show = mxs_pinconf_dbg_show,
	.pin_config_group_dbg_show = mxs_pinconf_group_dbg_show,
पूर्ण;

अटल काष्ठा pinctrl_desc mxs_pinctrl_desc = अणु
	.pctlops = &mxs_pinctrl_ops,
	.pmxops = &mxs_pinmux_ops,
	.confops = &mxs_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक mxs_pinctrl_parse_group(काष्ठा platक्रमm_device *pdev,
				   काष्ठा device_node *np, पूर्णांक idx,
				   स्थिर अक्षर **out_name)
अणु
	काष्ठा mxs_pinctrl_data *d = platक्रमm_get_drvdata(pdev);
	काष्ठा mxs_group *g = &d->soc->groups[idx];
	काष्ठा property *prop;
	स्थिर अक्षर *propname = "fsl,pinmux-ids";
	अक्षर *group;
	पूर्णांक length = म_माप(np->name) + SUFFIX_LEN;
	u32 val, i;

	group = devm_kzalloc(&pdev->dev, length, GFP_KERNEL);
	अगर (!group)
		वापस -ENOMEM;
	अगर (of_property_पढ़ो_u32(np, "reg", &val))
		snम_लिखो(group, length, "%s", np->name);
	अन्यथा
		snम_लिखो(group, length, "%s.%d", np->name, val);
	g->name = group;

	prop = of_find_property(np, propname, &length);
	अगर (!prop)
		वापस -EINVAL;
	g->npins = length / माप(u32);

	g->pins = devm_kसुस्मृति(&pdev->dev, g->npins, माप(*g->pins),
			       GFP_KERNEL);
	अगर (!g->pins)
		वापस -ENOMEM;

	g->muxsel = devm_kसुस्मृति(&pdev->dev, g->npins, माप(*g->muxsel),
				 GFP_KERNEL);
	अगर (!g->muxsel)
		वापस -ENOMEM;

	of_property_पढ़ो_u32_array(np, propname, g->pins, g->npins);
	क्रम (i = 0; i < g->npins; i++) अणु
		g->muxsel[i] = MUXID_TO_MUXSEL(g->pins[i]);
		g->pins[i] = MUXID_TO_PINID(g->pins[i]);
	पूर्ण

	अगर (out_name)
		*out_name = g->name;

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_pinctrl_probe_dt(काष्ठा platक्रमm_device *pdev,
				काष्ठा mxs_pinctrl_data *d)
अणु
	काष्ठा mxs_pinctrl_soc_data *soc = d->soc;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *child;
	काष्ठा mxs_function *f;
	स्थिर अक्षर *gpio_compat = "fsl,mxs-gpio";
	स्थिर अक्षर *fn, *fnull = "";
	पूर्णांक i = 0, idxf = 0, idxg = 0;
	पूर्णांक ret;
	u32 val;

	child = of_get_next_child(np, शून्य);
	अगर (!child) अणु
		dev_err(&pdev->dev, "no group is defined\n");
		वापस -ENOENT;
	पूर्ण

	/* Count total functions and groups */
	fn = fnull;
	क्रम_each_child_of_node(np, child) अणु
		अगर (of_device_is_compatible(child, gpio_compat))
			जारी;
		soc->ngroups++;
		/* Skip pure pinconf node */
		अगर (of_property_पढ़ो_u32(child, "reg", &val))
			जारी;
		अगर (म_भेद(fn, child->name)) अणु
			fn = child->name;
			soc->nfunctions++;
		पूर्ण
	पूर्ण

	soc->functions = devm_kसुस्मृति(&pdev->dev,
				      soc->nfunctions,
				      माप(*soc->functions),
				      GFP_KERNEL);
	अगर (!soc->functions)
		वापस -ENOMEM;

	soc->groups = devm_kसुस्मृति(&pdev->dev,
				   soc->ngroups, माप(*soc->groups),
				   GFP_KERNEL);
	अगर (!soc->groups)
		वापस -ENOMEM;

	/* Count groups क्रम each function */
	fn = fnull;
	f = &soc->functions[idxf];
	क्रम_each_child_of_node(np, child) अणु
		अगर (of_device_is_compatible(child, gpio_compat))
			जारी;
		अगर (of_property_पढ़ो_u32(child, "reg", &val))
			जारी;
		अगर (म_भेद(fn, child->name)) अणु
			काष्ठा device_node *child2;

			/*
			 * This reference is dropped by
			 * of_get_next_child(np, * child)
			 */
			of_node_get(child);

			/*
			 * The logic parsing the functions from dt currently
			 * करोesn't handle अगर functions with the same name are
			 * not grouped together. Only the first contiguous
			 * cluster is usable क्रम each function name. This is a
			 * bug that is not trivial to fix, but at least warn
			 * about it.
			 */
			क्रम (child2 = of_get_next_child(np, child);
			     child2 != शून्य;
			     child2 = of_get_next_child(np, child2)) अणु
				अगर (!म_भेद(child2->name, fn))
					dev_warn(&pdev->dev,
						 "function nodes must be grouped by name (failed for: %s)",
						 fn);
			पूर्ण

			f = &soc->functions[idxf++];
			f->name = fn = child->name;
		पूर्ण
		f->ngroups++;
	पूर्ण

	/* Get groups क्रम each function */
	idxf = 0;
	fn = fnull;
	क्रम_each_child_of_node(np, child) अणु
		अगर (of_device_is_compatible(child, gpio_compat))
			जारी;
		अगर (of_property_पढ़ो_u32(child, "reg", &val)) अणु
			ret = mxs_pinctrl_parse_group(pdev, child,
						      idxg++, शून्य);
			अगर (ret) अणु
				of_node_put(child);
				वापस ret;
			पूर्ण
			जारी;
		पूर्ण

		अगर (म_भेद(fn, child->name)) अणु
			f = &soc->functions[idxf++];
			f->groups = devm_kसुस्मृति(&pdev->dev,
						 f->ngroups,
						 माप(*f->groups),
						 GFP_KERNEL);
			अगर (!f->groups) अणु
				of_node_put(child);
				वापस -ENOMEM;
			पूर्ण
			fn = child->name;
			i = 0;
		पूर्ण
		ret = mxs_pinctrl_parse_group(pdev, child, idxg++,
					      &f->groups[i++]);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mxs_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
		      काष्ठा mxs_pinctrl_soc_data *soc)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mxs_pinctrl_data *d;
	पूर्णांक ret;

	d = devm_kzalloc(&pdev->dev, माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	d->dev = &pdev->dev;
	d->soc = soc;

	d->base = of_iomap(np, 0);
	अगर (!d->base)
		वापस -EADDRNOTAVAIL;

	mxs_pinctrl_desc.pins = d->soc->pins;
	mxs_pinctrl_desc.npins = d->soc->npins;
	mxs_pinctrl_desc.name = dev_name(&pdev->dev);

	platक्रमm_set_drvdata(pdev, d);

	ret = mxs_pinctrl_probe_dt(pdev, d);
	अगर (ret) अणु
		dev_err(&pdev->dev, "dt probe failed: %d\n", ret);
		जाओ err;
	पूर्ण

	d->pctl = pinctrl_रेजिस्टर(&mxs_pinctrl_desc, &pdev->dev, d);
	अगर (IS_ERR(d->pctl)) अणु
		dev_err(&pdev->dev, "Couldn't register MXS pinctrl driver\n");
		ret = PTR_ERR(d->pctl);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	iounmap(d->base);
	वापस ret;
पूर्ण
