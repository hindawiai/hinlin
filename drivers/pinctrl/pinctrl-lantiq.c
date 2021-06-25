<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/pinctrl/pinctrl-lantiq.c
 *  based on linux/drivers/pinctrl/pinctrl-pxa3xx.c
 *
 *  Copyright (C) 2012 John Crispin <john@phrozen.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश "pinctrl-lantiq.h"

अटल पूर्णांक ltq_get_group_count(काष्ठा pinctrl_dev *pctrldev)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	वापस info->num_grps;
पूर्ण

अटल स्थिर अक्षर *ltq_get_group_name(काष्ठा pinctrl_dev *pctrldev,
					 अचिन्हित selector)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	अगर (selector >= info->num_grps)
		वापस शून्य;
	वापस info->grps[selector].name;
पूर्ण

अटल पूर्णांक ltq_get_group_pins(काष्ठा pinctrl_dev *pctrldev,
				 अचिन्हित selector,
				 स्थिर अचिन्हित **pins,
				 अचिन्हित *num_pins)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	अगर (selector >= info->num_grps)
		वापस -EINVAL;
	*pins = info->grps[selector].pins;
	*num_pins = info->grps[selector].npins;
	वापस 0;
पूर्ण

अटल व्योम ltq_pinctrl_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा pinctrl_map *map, अचिन्हित num_maps)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_maps; i++)
		अगर (map[i].type == PIN_MAP_TYPE_CONFIGS_PIN ||
		    map[i].type == PIN_MAP_TYPE_CONFIGS_GROUP)
			kमुक्त(map[i].data.configs.configs);
	kमुक्त(map);
पूर्ण

अटल व्योम ltq_pinctrl_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
					काष्ठा seq_file *s,
					अचिन्हित offset)
अणु
	seq_म_लिखो(s, " %s", dev_name(pctldev->dev));
पूर्ण

अटल व्योम ltq_pinctrl_dt_subnode_to_map(काष्ठा pinctrl_dev *pctldev,
				काष्ठा device_node *np,
				काष्ठा pinctrl_map **map)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा property *pins = of_find_property(np, "lantiq,pins", शून्य);
	काष्ठा property *groups = of_find_property(np, "lantiq,groups", शून्य);
	अचिन्हित दीर्घ configs[3];
	अचिन्हित num_configs = 0;
	काष्ठा property *prop;
	स्थिर अक्षर *group, *pin;
	स्थिर अक्षर *function;
	पूर्णांक ret, i;

	अगर (!pins && !groups) अणु
		dev_err(pctldev->dev, "%pOFn defines neither pins nor groups\n",
			np);
		वापस;
	पूर्ण

	अगर (pins && groups) अणु
		dev_err(pctldev->dev, "%pOFn defines both pins and groups\n",
			np);
		वापस;
	पूर्ण

	ret = of_property_पढ़ो_string(np, "lantiq,function", &function);
	अगर (groups && !ret) अणु
		of_property_क्रम_each_string(np, "lantiq,groups", prop, group) अणु
			(*map)->type = PIN_MAP_TYPE_MUX_GROUP;
			(*map)->name = function;
			(*map)->data.mux.group = group;
			(*map)->data.mux.function = function;
			(*map)++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < info->num_params; i++) अणु
		u32 val;
		पूर्णांक ret = of_property_पढ़ो_u32(np,
				info->params[i].property, &val);
		अगर (!ret)
			configs[num_configs++] =
				LTQ_PINCONF_PACK(info->params[i].param,
				val);
	पूर्ण

	अगर (!num_configs)
		वापस;

	of_property_क्रम_each_string(np, "lantiq,pins", prop, pin) अणु
		(*map)->data.configs.configs = kmemdup(configs,
					num_configs * माप(अचिन्हित दीर्घ),
					GFP_KERNEL);
		(*map)->type = PIN_MAP_TYPE_CONFIGS_PIN;
		(*map)->name = pin;
		(*map)->data.configs.group_or_pin = pin;
		(*map)->data.configs.num_configs = num_configs;
		(*map)++;
	पूर्ण
	of_property_क्रम_each_string(np, "lantiq,groups", prop, group) अणु
		(*map)->data.configs.configs = kmemdup(configs,
					num_configs * माप(अचिन्हित दीर्घ),
					GFP_KERNEL);
		(*map)->type = PIN_MAP_TYPE_CONFIGS_GROUP;
		(*map)->name = group;
		(*map)->data.configs.group_or_pin = group;
		(*map)->data.configs.num_configs = num_configs;
		(*map)++;
	पूर्ण
पूर्ण

अटल पूर्णांक ltq_pinctrl_dt_subnode_size(काष्ठा device_node *np)
अणु
	पूर्णांक ret;

	ret = of_property_count_strings(np, "lantiq,groups");
	अगर (ret < 0)
		ret = of_property_count_strings(np, "lantiq,pins");
	वापस ret;
पूर्ण

अटल पूर्णांक ltq_pinctrl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा device_node *np_config,
				      काष्ठा pinctrl_map **map,
				      अचिन्हित *num_maps)
अणु
	काष्ठा pinctrl_map *पंचांगp;
	काष्ठा device_node *np;
	पूर्णांक max_maps = 0;

	क्रम_each_child_of_node(np_config, np)
		max_maps += ltq_pinctrl_dt_subnode_size(np);
	*map = kzalloc(array3_size(max_maps, माप(काष्ठा pinctrl_map), 2),
		       GFP_KERNEL);
	अगर (!*map)
		वापस -ENOMEM;
	पंचांगp = *map;

	क्रम_each_child_of_node(np_config, np)
		ltq_pinctrl_dt_subnode_to_map(pctldev, np, &पंचांगp);
	*num_maps = ((पूर्णांक)(पंचांगp - *map));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops ltq_pctrl_ops = अणु
	.get_groups_count	= ltq_get_group_count,
	.get_group_name		= ltq_get_group_name,
	.get_group_pins		= ltq_get_group_pins,
	.pin_dbg_show		= ltq_pinctrl_pin_dbg_show,
	.dt_node_to_map		= ltq_pinctrl_dt_node_to_map,
	.dt_मुक्त_map		= ltq_pinctrl_dt_मुक्त_map,
पूर्ण;

अटल पूर्णांक ltq_pmx_func_count(काष्ठा pinctrl_dev *pctrldev)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);

	वापस info->num_funcs;
पूर्ण

अटल स्थिर अक्षर *ltq_pmx_func_name(काष्ठा pinctrl_dev *pctrldev,
					 अचिन्हित selector)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);

	अगर (selector >= info->num_funcs)
		वापस शून्य;

	वापस info->funcs[selector].name;
पूर्ण

अटल पूर्णांक ltq_pmx_get_groups(काष्ठा pinctrl_dev *pctrldev,
				अचिन्हित func,
				स्थिर अक्षर * स्थिर **groups,
				अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);

	*groups = info->funcs[func].groups;
	*num_groups = info->funcs[func].num_groups;

	वापस 0;
पूर्ण

/* Return function number. If failure, वापस negative value. */
अटल पूर्णांक match_mux(स्थिर काष्ठा ltq_mfp_pin *mfp, अचिन्हित mux)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < LTQ_MAX_MUX; i++) अणु
		अगर (mfp->func[i] == mux)
			अवरोध;
	पूर्ण
	अगर (i >= LTQ_MAX_MUX)
		वापस -EINVAL;
	वापस i;
पूर्ण

/* करोn't assume .mfp is linearly mapped. find the mfp with the correct .pin */
अटल पूर्णांक match_mfp(स्थिर काष्ठा ltq_pinmux_info *info, पूर्णांक pin)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < info->num_mfp; i++) अणु
		अगर (info->mfp[i].pin == pin)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

/* check whether current pin configuration is valid. Negative क्रम failure */
अटल पूर्णांक match_group_mux(स्थिर काष्ठा ltq_pin_group *grp,
			   स्थिर काष्ठा ltq_pinmux_info *info,
			   अचिन्हित mux)
अणु
	पूर्णांक i, pin, ret = 0;
	क्रम (i = 0; i < grp->npins; i++) अणु
		pin = match_mfp(info, grp->pins[i]);
		अगर (pin < 0) अणु
			dev_err(info->dev, "could not find mfp for pin %d\n",
				grp->pins[i]);
			वापस -EINVAL;
		पूर्ण
		ret = match_mux(&info->mfp[pin], mux);
		अगर (ret < 0) अणु
			dev_err(info->dev, "Can't find mux %d on pin%d\n",
				mux, pin);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ltq_pmx_set(काष्ठा pinctrl_dev *pctrldev,
		       अचिन्हित func,
		       अचिन्हित group)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	स्थिर काष्ठा ltq_pin_group *pin_grp = &info->grps[group];
	पूर्णांक i, pin, pin_func, ret;

	अगर (!pin_grp->npins ||
		(match_group_mux(pin_grp, info, pin_grp->mux) < 0)) अणु
		dev_err(info->dev, "Failed to set the pin group: %s\n",
			info->grps[group].name);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < pin_grp->npins; i++) अणु
		pin = match_mfp(info, pin_grp->pins[i]);
		अगर (pin < 0) अणु
			dev_err(info->dev, "could not find mfp for pin %d\n",
				pin_grp->pins[i]);
			वापस -EINVAL;
		पूर्ण
		pin_func = match_mux(&info->mfp[pin], pin_grp->mux);
		ret = info->apply_mux(pctrldev, pin, pin_func);
		अगर (ret) अणु
			dev_err(info->dev,
				"failed to apply mux %d for pin %d\n",
				pin_func, pin);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ltq_pmx_gpio_request_enable(काष्ठा pinctrl_dev *pctrldev,
				काष्ठा pinctrl_gpio_range *range,
				अचिन्हित pin)
अणु
	काष्ठा ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	पूर्णांक mfp = match_mfp(info, pin);
	पूर्णांक pin_func;

	अगर (mfp < 0) अणु
		dev_err(info->dev, "could not find mfp for pin %d\n", pin);
		वापस -EINVAL;
	पूर्ण

	pin_func = match_mux(&info->mfp[mfp], 0);
	अगर (pin_func < 0) अणु
		dev_err(info->dev, "No GPIO function on pin%d\n", mfp);
		वापस -EINVAL;
	पूर्ण

	वापस info->apply_mux(pctrldev, mfp, pin_func);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops ltq_pmx_ops = अणु
	.get_functions_count	= ltq_pmx_func_count,
	.get_function_name	= ltq_pmx_func_name,
	.get_function_groups	= ltq_pmx_get_groups,
	.set_mux		= ltq_pmx_set,
	.gpio_request_enable	= ltq_pmx_gpio_request_enable,
पूर्ण;

/*
 * allow dअगरferent socs to रेजिस्टर with the generic part of the lanti
 * pinctrl code
 */
पूर्णांक ltq_pinctrl_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
				काष्ठा ltq_pinmux_info *info)
अणु
	काष्ठा pinctrl_desc *desc;

	अगर (!info)
		वापस -EINVAL;
	desc = info->desc;
	desc->pctlops = &ltq_pctrl_ops;
	desc->pmxops = &ltq_pmx_ops;
	info->dev = &pdev->dev;

	info->pctrl = devm_pinctrl_रेजिस्टर(&pdev->dev, desc, info);
	अगर (IS_ERR(info->pctrl)) अणु
		dev_err(&pdev->dev, "failed to register LTQ pinmux driver\n");
		वापस PTR_ERR(info->pctrl);
	पूर्ण
	platक्रमm_set_drvdata(pdev, info);
	वापस 0;
पूर्ण
