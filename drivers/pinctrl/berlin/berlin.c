<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Berlin SoC pinctrl core driver
 *
 * Copyright (C) 2014 Marvell Technology Group Ltd.
 *
 * Antoine Tथऊnart <antoine.tenart@मुक्त-electrons.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"
#समावेश "berlin.h"

काष्ठा berlin_pinctrl अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	स्थिर काष्ठा berlin_pinctrl_desc *desc;
	काष्ठा berlin_pinctrl_function *functions;
	अचिन्हित nfunctions;
	काष्ठा pinctrl_dev *pctrl_dev;
पूर्ण;

अटल पूर्णांक berlin_pinctrl_get_group_count(काष्ठा pinctrl_dev *pctrl_dev)
अणु
	काष्ठा berlin_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pctrl->desc->ngroups;
पूर्ण

अटल स्थिर अक्षर *berlin_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctrl_dev,
						 अचिन्हित group)
अणु
	काष्ठा berlin_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pctrl->desc->groups[group].name;
पूर्ण

अटल पूर्णांक berlin_pinctrl_dt_node_to_map(काष्ठा pinctrl_dev *pctrl_dev,
					 काष्ठा device_node *node,
					 काष्ठा pinctrl_map **map,
					 अचिन्हित *num_maps)
अणु
	काष्ठा berlin_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	काष्ठा property *prop;
	स्थिर अक्षर *function_name, *group_name;
	अचिन्हित reserved_maps = 0;
	पूर्णांक ret, ngroups;

	*map = शून्य;
	*num_maps = 0;

	ret = of_property_पढ़ो_string(node, "function", &function_name);
	अगर (ret) अणु
		dev_err(pctrl->dev,
			"missing function property in node %pOFn\n", node);
		वापस -EINVAL;
	पूर्ण

	ngroups = of_property_count_strings(node, "groups");
	अगर (ngroups < 0) अणु
		dev_err(pctrl->dev,
			"missing groups property in node %pOFn\n", node);
		वापस -EINVAL;
	पूर्ण

	ret = pinctrl_utils_reserve_map(pctrl_dev, map, &reserved_maps,
					num_maps, ngroups);
	अगर (ret) अणु
		dev_err(pctrl->dev, "can't reserve map: %d\n", ret);
		वापस ret;
	पूर्ण

	of_property_क्रम_each_string(node, "groups", prop, group_name) अणु
		ret = pinctrl_utils_add_map_mux(pctrl_dev, map, &reserved_maps,
						num_maps, group_name,
						function_name);
		अगर (ret) अणु
			dev_err(pctrl->dev, "can't add map: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops berlin_pinctrl_ops = अणु
	.get_groups_count	= &berlin_pinctrl_get_group_count,
	.get_group_name		= &berlin_pinctrl_get_group_name,
	.dt_node_to_map		= &berlin_pinctrl_dt_node_to_map,
	.dt_मुक्त_map		= &pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक berlin_pinmux_get_functions_count(काष्ठा pinctrl_dev *pctrl_dev)
अणु
	काष्ठा berlin_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pctrl->nfunctions;
पूर्ण

अटल स्थिर अक्षर *berlin_pinmux_get_function_name(काष्ठा pinctrl_dev *pctrl_dev,
						   अचिन्हित function)
अणु
	काष्ठा berlin_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	वापस pctrl->functions[function].name;
पूर्ण

अटल पूर्णांक berlin_pinmux_get_function_groups(काष्ठा pinctrl_dev *pctrl_dev,
					     अचिन्हित function,
					     स्थिर अक्षर * स्थिर **groups,
					     अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा berlin_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	*groups = pctrl->functions[function].groups;
	*num_groups = pctrl->functions[function].ngroups;

	वापस 0;
पूर्ण

अटल काष्ठा berlin_desc_function *
berlin_pinctrl_find_function_by_name(काष्ठा berlin_pinctrl *pctrl,
				     स्थिर काष्ठा berlin_desc_group *group,
				     स्थिर अक्षर *fname)
अणु
	काष्ठा berlin_desc_function *function = group->functions;

	जबतक (function->name) अणु
		अगर (!म_भेद(function->name, fname))
			वापस function;

		function++;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक berlin_pinmux_set(काष्ठा pinctrl_dev *pctrl_dev,
			     अचिन्हित function,
			     अचिन्हित group)
अणु
	काष्ठा berlin_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrl_dev);
	स्थिर काष्ठा berlin_desc_group *group_desc = pctrl->desc->groups + group;
	काष्ठा berlin_pinctrl_function *func = pctrl->functions + function;
	काष्ठा berlin_desc_function *function_desc =
		berlin_pinctrl_find_function_by_name(pctrl, group_desc,
						     func->name);
	u32 mask, val;

	अगर (!function_desc)
		वापस -EINVAL;

	mask = GENMASK(group_desc->lsb + group_desc->bit_width - 1,
		       group_desc->lsb);
	val = function_desc->muxval << group_desc->lsb;
	regmap_update_bits(pctrl->regmap, group_desc->offset, mask, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops berlin_pinmux_ops = अणु
	.get_functions_count	= &berlin_pinmux_get_functions_count,
	.get_function_name	= &berlin_pinmux_get_function_name,
	.get_function_groups	= &berlin_pinmux_get_function_groups,
	.set_mux		= &berlin_pinmux_set,
पूर्ण;

अटल पूर्णांक berlin_pinctrl_add_function(काष्ठा berlin_pinctrl *pctrl,
				       स्थिर अक्षर *name)
अणु
	काष्ठा berlin_pinctrl_function *function = pctrl->functions;

	जबतक (function->name) अणु
		अगर (!म_भेद(function->name, name)) अणु
			function->ngroups++;
			वापस -EEXIST;
		पूर्ण
		function++;
	पूर्ण

	function->name = name;
	function->ngroups = 1;

	pctrl->nfunctions++;

	वापस 0;
पूर्ण

अटल पूर्णांक berlin_pinctrl_build_state(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा berlin_pinctrl *pctrl = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा berlin_desc_group *desc_group;
	स्थिर काष्ठा berlin_desc_function *desc_function;
	पूर्णांक i, max_functions = 0;

	pctrl->nfunctions = 0;

	क्रम (i = 0; i < pctrl->desc->ngroups; i++) अणु
		desc_group = pctrl->desc->groups + i;
		/* compute the maxiumum number of functions a group can have */
		max_functions += 1 << (desc_group->bit_width + 1);
	पूर्ण

	/* we will पुनः_स्मृतिate later */
	pctrl->functions = kसुस्मृति(max_functions,
				   माप(*pctrl->functions), GFP_KERNEL);
	अगर (!pctrl->functions)
		वापस -ENOMEM;

	/* रेजिस्टर all functions */
	क्रम (i = 0; i < pctrl->desc->ngroups; i++) अणु
		desc_group = pctrl->desc->groups + i;
		desc_function = desc_group->functions;

		जबतक (desc_function->name) अणु
			berlin_pinctrl_add_function(pctrl, desc_function->name);
			desc_function++;
		पूर्ण
	पूर्ण

	pctrl->functions = kपुनः_स्मृति(pctrl->functions,
				    pctrl->nfunctions * माप(*pctrl->functions),
				    GFP_KERNEL);

	/* map functions to theirs groups */
	क्रम (i = 0; i < pctrl->desc->ngroups; i++) अणु
		desc_group = pctrl->desc->groups + i;
		desc_function = desc_group->functions;

		जबतक (desc_function->name) अणु
			काष्ठा berlin_pinctrl_function
				*function = pctrl->functions;
			स्थिर अक्षर **groups;
			bool found = false;

			जबतक (function->name) अणु
				अगर (!म_भेद(desc_function->name, function->name)) अणु
					found = true;
					अवरोध;
				पूर्ण
				function++;
			पूर्ण

			अगर (!found) अणु
				kमुक्त(pctrl->functions);
				वापस -EINVAL;
			पूर्ण

			अगर (!function->groups) अणु
				function->groups =
					devm_kसुस्मृति(&pdev->dev,
						     function->ngroups,
						     माप(अक्षर *),
						     GFP_KERNEL);

				अगर (!function->groups) अणु
					kमुक्त(pctrl->functions);
					वापस -ENOMEM;
				पूर्ण
			पूर्ण

			groups = function->groups;
			जबतक (*groups)
				groups++;

			*groups = desc_group->name;

			desc_function++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pinctrl_desc berlin_pctrl_desc = अणु
	.name		= "berlin-pinctrl",
	.pctlops	= &berlin_pinctrl_ops,
	.pmxops		= &berlin_pinmux_ops,
	.owner		= THIS_MODULE,
पूर्ण;

पूर्णांक berlin_pinctrl_probe_regmap(काष्ठा platक्रमm_device *pdev,
				स्थिर काष्ठा berlin_pinctrl_desc *desc,
				काष्ठा regmap *regmap)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा berlin_pinctrl *pctrl;
	पूर्णांक ret;

	pctrl = devm_kzalloc(dev, माप(*pctrl), GFP_KERNEL);
	अगर (!pctrl)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pctrl);

	pctrl->regmap = regmap;
	pctrl->dev = &pdev->dev;
	pctrl->desc = desc;

	ret = berlin_pinctrl_build_state(pdev);
	अगर (ret) अणु
		dev_err(dev, "cannot build driver state: %d\n", ret);
		वापस ret;
	पूर्ण

	pctrl->pctrl_dev = devm_pinctrl_रेजिस्टर(dev, &berlin_pctrl_desc,
						 pctrl);
	अगर (IS_ERR(pctrl->pctrl_dev)) अणु
		dev_err(dev, "failed to register pinctrl driver\n");
		वापस PTR_ERR(pctrl->pctrl_dev);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक berlin_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			 स्थिर काष्ठा berlin_pinctrl_desc *desc)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *parent_np = of_get_parent(dev->of_node);
	काष्ठा regmap *regmap = syscon_node_to_regmap(parent_np);

	of_node_put(parent_np);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस berlin_pinctrl_probe_regmap(pdev, desc, regmap);
पूर्ण
