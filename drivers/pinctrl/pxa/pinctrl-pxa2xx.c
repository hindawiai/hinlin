<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell PXA2xx family pin control
 *
 * Copyright (C) 2015 Robert Jarzmik
 */

#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/module.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "../pinctrl-utils.h"
#समावेश "pinctrl-pxa2xx.h"

अटल पूर्णांक pxa2xx_pctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा pxa_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->ngroups;
पूर्ण

अटल स्थिर अक्षर *pxa2xx_pctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					       अचिन्हित tgroup)
अणु
	काष्ठा pxa_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pxa_pinctrl_group *group = pctl->groups + tgroup;

	वापस group->name;
पूर्ण

अटल पूर्णांक pxa2xx_pctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित tgroup,
				       स्थिर अचिन्हित **pins,
				       अचिन्हित *num_pins)
अणु
	काष्ठा pxa_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pxa_pinctrl_group *group = pctl->groups + tgroup;

	*pins = (अचिन्हित *)&group->pin;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops pxa2xx_pctl_ops = अणु
#अगर_घोषित CONFIG_OF
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
#पूर्ण_अगर
	.get_groups_count	= pxa2xx_pctrl_get_groups_count,
	.get_group_name		= pxa2xx_pctrl_get_group_name,
	.get_group_pins		= pxa2xx_pctrl_get_group_pins,
पूर्ण;

अटल काष्ठा pxa_desc_function *
pxa_desc_by_func_group(काष्ठा pxa_pinctrl *pctl, स्थिर अक्षर *pin_name,
		       स्थिर अक्षर *func_name)
अणु
	पूर्णांक i;
	काष्ठा pxa_desc_function *df;

	क्रम (i = 0; i < pctl->npins; i++) अणु
		स्थिर काष्ठा pxa_desc_pin *pin = pctl->ppins + i;

		अगर (!म_भेद(pin->pin.name, pin_name))
			क्रम (df = pin->functions; df->name; df++)
				अगर (!म_भेद(df->name, func_name))
					वापस df;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक pxa2xx_pmx_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
					 काष्ठा pinctrl_gpio_range *range,
					 अचिन्हित pin,
					 bool input)
अणु
	काष्ठा pxa_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t val;
	व्योम __iomem *gpdr;

	gpdr = pctl->base_gpdr[pin / 32];
	dev_dbg(pctl->dev, "set_direction(pin=%d): dir=%d\n",
		pin, !input);

	spin_lock_irqsave(&pctl->lock, flags);

	val = पढ़ोl_relaxed(gpdr);
	val = (val & ~BIT(pin % 32)) | (input ? 0 : BIT(pin % 32));
	ग_लिखोl_relaxed(val, gpdr);

	spin_unlock_irqrestore(&pctl->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *pxa2xx_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित function)
अणु
	काष्ठा pxa_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pxa_pinctrl_function *pf = pctl->functions + function;

	वापस pf->name;
पूर्ण

अटल पूर्णांक pxa2xx_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा pxa_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->nfuncs;
पूर्ण

अटल पूर्णांक pxa2xx_pmx_get_func_groups(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित function,
				      स्थिर अक्षर * स्थिर **groups,
				      अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा pxa_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pxa_pinctrl_function *pf = pctl->functions + function;

	*groups = pf->groups;
	*num_groups = pf->ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_pmx_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित function,
			      अचिन्हित tgroup)
अणु
	काष्ठा pxa_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pxa_pinctrl_group *group = pctl->groups + tgroup;
	काष्ठा pxa_desc_function *df;
	पूर्णांक pin, shअगरt;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *gafr, *gpdr;
	u32 val;


	df = pxa_desc_by_func_group(pctl, group->name,
				    (pctl->functions + function)->name);
	अगर (!df)
		वापस -EINVAL;

	pin = group->pin;
	gafr = pctl->base_gafr[pin / 16];
	gpdr = pctl->base_gpdr[pin / 32];
	shअगरt = (pin % 16) << 1;
	dev_dbg(pctl->dev, "set_mux(pin=%d): af=%d dir=%d\n",
		pin, df->muxval >> 1, df->muxval & 0x1);

	spin_lock_irqsave(&pctl->lock, flags);

	val = पढ़ोl_relaxed(gafr);
	val = (val & ~(0x3 << shअगरt)) | ((df->muxval >> 1) << shअगरt);
	ग_लिखोl_relaxed(val, gafr);

	val = पढ़ोl_relaxed(gpdr);
	val = (val & ~BIT(pin % 32)) | ((df->muxval & 1) ? BIT(pin % 32) : 0);
	ग_लिखोl_relaxed(val, gpdr);

	spin_unlock_irqrestore(&pctl->lock, flags);

	वापस 0;
पूर्ण
अटल स्थिर काष्ठा pinmux_ops pxa2xx_pinmux_ops = अणु
	.get_functions_count = pxa2xx_get_functions_count,
	.get_function_name = pxa2xx_pmx_get_func_name,
	.get_function_groups = pxa2xx_pmx_get_func_groups,
	.set_mux = pxa2xx_pmx_set_mux,
	.gpio_set_direction = pxa2xx_pmx_gpio_set_direction,
पूर्ण;

अटल पूर्णांक pxa2xx_pconf_group_get(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित group,
				  अचिन्हित दीर्घ *config)
अणु
	काष्ठा pxa_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pxa_pinctrl_group *g = pctl->groups + group;
	अचिन्हित दीर्घ flags;
	अचिन्हित pin = g->pin;
	व्योम __iomem *pgsr = pctl->base_pgsr[pin / 32];
	u32 val;

	spin_lock_irqsave(&pctl->lock, flags);
	val = पढ़ोl_relaxed(pgsr) & BIT(pin % 32);
	*config = val ? PIN_CONFIG_MODE_LOW_POWER : 0;
	spin_unlock_irqrestore(&pctl->lock, flags);

	dev_dbg(pctl->dev, "get sleep gpio state(pin=%d) %d\n",
		pin, !!val);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_pconf_group_set(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित group,
				  अचिन्हित दीर्घ *configs,
				  अचिन्हित num_configs)
अणु
	काष्ठा pxa_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pxa_pinctrl_group *g = pctl->groups + group;
	अचिन्हित दीर्घ flags;
	अचिन्हित pin = g->pin;
	व्योम __iomem *pgsr = pctl->base_pgsr[pin / 32];
	पूर्णांक i, is_set = 0;
	u32 val;

	क्रम (i = 0; i < num_configs; i++) अणु
		चयन (pinconf_to_config_param(configs[i])) अणु
		हाल PIN_CONFIG_MODE_LOW_POWER:
			is_set = pinconf_to_config_argument(configs[i]);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dev_dbg(pctl->dev, "set sleep gpio state(pin=%d) %d\n",
		pin, is_set);

	spin_lock_irqsave(&pctl->lock, flags);
	val = पढ़ोl_relaxed(pgsr);
	val = (val & ~BIT(pin % 32)) | (is_set ? BIT(pin % 32) : 0);
	ग_लिखोl_relaxed(val, pgsr);
	spin_unlock_irqrestore(&pctl->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops pxa2xx_pconf_ops = अणु
	.pin_config_group_get	= pxa2xx_pconf_group_get,
	.pin_config_group_set	= pxa2xx_pconf_group_set,
	.is_generic		= true,
पूर्ण;

अटल काष्ठा pinctrl_desc pxa2xx_pinctrl_desc = अणु
	.confops	= &pxa2xx_pconf_ops,
	.pctlops	= &pxa2xx_pctl_ops,
	.pmxops		= &pxa2xx_pinmux_ops,
पूर्ण;

अटल स्थिर काष्ठा pxa_pinctrl_function *
pxa2xx_find_function(काष्ठा pxa_pinctrl *pctl, स्थिर अक्षर *fname,
		     स्थिर काष्ठा pxa_pinctrl_function *functions)
अणु
	स्थिर काष्ठा pxa_pinctrl_function *func;

	क्रम (func = functions; func->name; func++)
		अगर (!म_भेद(fname, func->name))
			वापस func;

	वापस शून्य;
पूर्ण

अटल पूर्णांक pxa2xx_build_functions(काष्ठा pxa_pinctrl *pctl)
अणु
	पूर्णांक i;
	काष्ठा pxa_pinctrl_function *functions;
	काष्ठा pxa_desc_function *df;

	/*
	 * Each pin can have at most 6 alternate functions, and 2 gpio functions
	 * which are common to each pin. As there are more than 2 pins without
	 * alternate function, 6 * npins is an असलolute high limit of the number
	 * of functions.
	 */
	functions = devm_kसुस्मृति(pctl->dev, pctl->npins * 6,
				 माप(*functions), GFP_KERNEL);
	अगर (!functions)
		वापस -ENOMEM;

	क्रम (i = 0; i < pctl->npins; i++)
		क्रम (df = pctl->ppins[i].functions; df->name; df++)
			अगर (!pxa2xx_find_function(pctl, df->name, functions))
				(functions + pctl->nfuncs++)->name = df->name;
	pctl->functions = devm_kmemdup(pctl->dev, functions,
				       pctl->nfuncs * माप(*functions),
				       GFP_KERNEL);
	अगर (!pctl->functions)
		वापस -ENOMEM;

	devm_kमुक्त(pctl->dev, functions);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_build_groups(काष्ठा pxa_pinctrl *pctl)
अणु
	पूर्णांक i, j, ngroups;
	काष्ठा pxa_pinctrl_function *func;
	काष्ठा pxa_desc_function *df;
	अक्षर **gपंचांगp;

	gपंचांगp = devm_kदो_स्मृति_array(pctl->dev, pctl->npins, माप(*gपंचांगp),
				  GFP_KERNEL);
	अगर (!gपंचांगp)
		वापस -ENOMEM;

	क्रम (i = 0; i < pctl->nfuncs; i++) अणु
		ngroups = 0;
		क्रम (j = 0; j < pctl->npins; j++)
			क्रम (df = pctl->ppins[j].functions; df->name;
			     df++)
				अगर (!म_भेद(pctl->functions[i].name,
					    df->name))
					gपंचांगp[ngroups++] = (अक्षर *)
						pctl->ppins[j].pin.name;
		func = pctl->functions + i;
		func->ngroups = ngroups;
		func->groups =
			devm_kदो_स्मृति_array(pctl->dev, ngroups,
					   माप(अक्षर *), GFP_KERNEL);
		अगर (!func->groups)
			वापस -ENOMEM;

		स_नकल(func->groups, gपंचांगp, ngroups * माप(*gपंचांगp));
	पूर्ण

	devm_kमुक्त(pctl->dev, gपंचांगp);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_build_state(काष्ठा pxa_pinctrl *pctl,
			      स्थिर काष्ठा pxa_desc_pin *ppins, पूर्णांक npins)
अणु
	काष्ठा pxa_pinctrl_group *group;
	काष्ठा pinctrl_pin_desc *pins;
	पूर्णांक ret, i;

	pctl->npins = npins;
	pctl->ppins = ppins;
	pctl->ngroups = npins;

	pctl->desc.npins = npins;
	pins = devm_kसुस्मृति(pctl->dev, npins, माप(*pins), GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	pctl->desc.pins = pins;
	क्रम (i = 0; i < npins; i++)
		pins[i] = ppins[i].pin;

	pctl->groups = devm_kदो_स्मृति_array(pctl->dev, pctl->ngroups,
					  माप(*pctl->groups), GFP_KERNEL);
	अगर (!pctl->groups)
		वापस -ENOMEM;

	क्रम (i = 0; i < npins; i++) अणु
		group = pctl->groups + i;
		group->name = ppins[i].pin.name;
		group->pin = ppins[i].pin.number;
	पूर्ण

	ret = pxa2xx_build_functions(pctl);
	अगर (ret)
		वापस ret;

	ret = pxa2xx_build_groups(pctl);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक pxa2xx_pinctrl_init(काष्ठा platक्रमm_device *pdev,
			स्थिर काष्ठा pxa_desc_pin *ppins, पूर्णांक npins,
			व्योम __iomem *base_gafr[], व्योम __iomem *base_gpdr[],
			व्योम __iomem *base_pgsr[])
अणु
	काष्ठा pxa_pinctrl *pctl;
	पूर्णांक ret, i, maxpin = 0;

	क्रम (i = 0; i < npins; i++)
		maxpin = max_t(पूर्णांक, ppins[i].pin.number, maxpin);

	pctl = devm_kzalloc(&pdev->dev, माप(*pctl), GFP_KERNEL);
	अगर (!pctl)
		वापस -ENOMEM;
	pctl->base_gafr = devm_kसुस्मृति(&pdev->dev, roundup(maxpin, 16),
				       माप(*pctl->base_gafr), GFP_KERNEL);
	pctl->base_gpdr = devm_kसुस्मृति(&pdev->dev, roundup(maxpin, 32),
				       माप(*pctl->base_gpdr), GFP_KERNEL);
	pctl->base_pgsr = devm_kसुस्मृति(&pdev->dev, roundup(maxpin, 32),
				       माप(*pctl->base_pgsr), GFP_KERNEL);
	अगर (!pctl->base_gafr || !pctl->base_gpdr || !pctl->base_pgsr)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pctl);
	spin_lock_init(&pctl->lock);

	pctl->dev = &pdev->dev;
	pctl->desc = pxa2xx_pinctrl_desc;
	pctl->desc.name = dev_name(&pdev->dev);
	pctl->desc.owner = THIS_MODULE;

	क्रम (i = 0; i < roundup(maxpin, 16); i += 16)
		pctl->base_gafr[i / 16] = base_gafr[i / 16];
	क्रम (i = 0; i < roundup(maxpin, 32); i += 32) अणु
		pctl->base_gpdr[i / 32] = base_gpdr[i / 32];
		pctl->base_pgsr[i / 32] = base_pgsr[i / 32];
	पूर्ण

	ret = pxa2xx_build_state(pctl, ppins, npins);
	अगर (ret)
		वापस ret;

	pctl->pctl_dev = devm_pinctrl_रेजिस्टर(&pdev->dev, &pctl->desc, pctl);
	अगर (IS_ERR(pctl->pctl_dev)) अणु
		dev_err(&pdev->dev, "couldn't register pinctrl driver\n");
		वापस PTR_ERR(pctl->pctl_dev);
	पूर्ण

	dev_info(&pdev->dev, "initialized pxa2xx pinctrl driver\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pxa2xx_pinctrl_init);

MODULE_AUTHOR("Robert Jarzmik <robert.jarzmik@free.fr>");
MODULE_DESCRIPTION("Marvell PXA2xx pinctrl driver");
MODULE_LICENSE("GPL v2");
