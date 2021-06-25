<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 IBM Corp.
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश "../core.h"
#समावेश "pinctrl-aspeed.h"

पूर्णांक aspeed_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा aspeed_pinctrl_data *pdata = pinctrl_dev_get_drvdata(pctldev);

	वापस pdata->pinmux.ngroups;
पूर्ण

स्थिर अक्षर *aspeed_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक group)
अणु
	काष्ठा aspeed_pinctrl_data *pdata = pinctrl_dev_get_drvdata(pctldev);

	वापस pdata->pinmux.groups[group].name;
पूर्ण

पूर्णांक aspeed_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक group, स्थिर अचिन्हित पूर्णांक **pins,
				  अचिन्हित पूर्णांक *npins)
अणु
	काष्ठा aspeed_pinctrl_data *pdata = pinctrl_dev_get_drvdata(pctldev);

	*pins = &pdata->pinmux.groups[group].pins[0];
	*npins = pdata->pinmux.groups[group].npins;

	वापस 0;
पूर्ण

व्योम aspeed_pinctrl_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा seq_file *s, अचिन्हित पूर्णांक offset)
अणु
	seq_म_लिखो(s, " %s", dev_name(pctldev->dev));
पूर्ण

पूर्णांक aspeed_pinmux_get_fn_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा aspeed_pinctrl_data *pdata = pinctrl_dev_get_drvdata(pctldev);

	वापस pdata->pinmux.nfunctions;
पूर्ण

स्थिर अक्षर *aspeed_pinmux_get_fn_name(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित पूर्णांक function)
अणु
	काष्ठा aspeed_pinctrl_data *pdata = pinctrl_dev_get_drvdata(pctldev);

	वापस pdata->pinmux.functions[function].name;
पूर्ण

पूर्णांक aspeed_pinmux_get_fn_groups(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक function,
				स्थिर अक्षर * स्थिर **groups,
				अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	काष्ठा aspeed_pinctrl_data *pdata = pinctrl_dev_get_drvdata(pctldev);

	*groups = pdata->pinmux.functions[function].groups;
	*num_groups = pdata->pinmux.functions[function].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_sig_expr_enable(काष्ठा aspeed_pinmux_data *ctx,
				  स्थिर काष्ठा aspeed_sig_expr *expr)
अणु
	पूर्णांक ret;

	pr_debug("Enabling signal %s for %s\n", expr->संकेत,
		 expr->function);

	ret = aspeed_sig_expr_eval(ctx, expr, true);
	अगर (ret < 0)
		वापस ret;

	अगर (!ret)
		वापस aspeed_sig_expr_set(ctx, expr, true);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_sig_expr_disable(काष्ठा aspeed_pinmux_data *ctx,
				   स्थिर काष्ठा aspeed_sig_expr *expr)
अणु
	पूर्णांक ret;

	pr_debug("Disabling signal %s for %s\n", expr->संकेत,
		 expr->function);

	ret = aspeed_sig_expr_eval(ctx, expr, true);
	अगर (ret < 0)
		वापस ret;

	अगर (ret)
		वापस aspeed_sig_expr_set(ctx, expr, false);

	वापस 0;
पूर्ण

/**
 * aspeed_disable_sig() - Disable a संकेत on a pin by disabling all provided
 * संकेत expressions.
 *
 * @ctx: The pinmux context
 * @exprs: The list of संकेत expressions (from a priority level on a pin)
 *
 * Return: 0 अगर all expressions are disabled, otherwise a negative error code
 */
अटल पूर्णांक aspeed_disable_sig(काष्ठा aspeed_pinmux_data *ctx,
			      स्थिर काष्ठा aspeed_sig_expr **exprs)
अणु
	पूर्णांक ret = 0;

	अगर (!exprs)
		वापस true;

	जबतक (*exprs && !ret) अणु
		ret = aspeed_sig_expr_disable(ctx, *exprs);
		exprs++;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * Search क्रम the संकेत expression needed to enable the pin's संकेत क्रम the
 * requested function.
 *
 * @exprs: List of संकेत expressions (haystack)
 * @name: The name of the requested function (needle)
 *
 * Return: A poपूर्णांकer to the संकेत expression whose function tag matches the
 * provided name, otherwise शून्य.
 *
 */
अटल स्थिर काष्ठा aspeed_sig_expr *aspeed_find_expr_by_name(
		स्थिर काष्ठा aspeed_sig_expr **exprs, स्थिर अक्षर *name)
अणु
	जबतक (*exprs) अणु
		अगर (म_भेद((*exprs)->function, name) == 0)
			वापस *exprs;
		exprs++;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अक्षर *get_defined_attribute(स्थिर काष्ठा aspeed_pin_desc *pdesc,
				   स्थिर अक्षर *(*get)(
					   स्थिर काष्ठा aspeed_sig_expr *))
अणु
	अक्षर *found = शून्य;
	माप_प्रकार len = 0;
	स्थिर काष्ठा aspeed_sig_expr ***prios, **funcs, *expr;

	prios = pdesc->prios;

	जबतक ((funcs = *prios)) अणु
		जबतक ((expr = *funcs)) अणु
			स्थिर अक्षर *str = get(expr);
			माप_प्रकार delta = म_माप(str) + 2;
			अक्षर *expanded;

			expanded = kपुनः_स्मृति(found, len + delta + 1, GFP_KERNEL);
			अगर (!expanded) अणु
				kमुक्त(found);
				वापस expanded;
			पूर्ण

			found = expanded;
			found[len] = '\0';
			len += delta;

			म_जोड़ो(found, str);
			म_जोड़ो(found, ", ");

			funcs++;
		पूर्ण
		prios++;
	पूर्ण

	अगर (len < 2) अणु
		kमुक्त(found);
		वापस शून्य;
	पूर्ण

	found[len - 2] = '\0';

	वापस found;
पूर्ण

अटल स्थिर अक्षर *aspeed_sig_expr_function(स्थिर काष्ठा aspeed_sig_expr *expr)
अणु
	वापस expr->function;
पूर्ण

अटल अक्षर *get_defined_functions(स्थिर काष्ठा aspeed_pin_desc *pdesc)
अणु
	वापस get_defined_attribute(pdesc, aspeed_sig_expr_function);
पूर्ण

अटल स्थिर अक्षर *aspeed_sig_expr_संकेत(स्थिर काष्ठा aspeed_sig_expr *expr)
अणु
	वापस expr->संकेत;
पूर्ण

अटल अक्षर *get_defined_संकेतs(स्थिर काष्ठा aspeed_pin_desc *pdesc)
अणु
	वापस get_defined_attribute(pdesc, aspeed_sig_expr_संकेत);
पूर्ण

पूर्णांक aspeed_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक function,
			  अचिन्हित पूर्णांक group)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा aspeed_pinctrl_data *pdata = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा aspeed_pin_group *pgroup = &pdata->pinmux.groups[group];
	स्थिर काष्ठा aspeed_pin_function *pfunc =
		&pdata->pinmux.functions[function];

	क्रम (i = 0; i < pgroup->npins; i++) अणु
		पूर्णांक pin = pgroup->pins[i];
		स्थिर काष्ठा aspeed_pin_desc *pdesc = pdata->pins[pin].drv_data;
		स्थिर काष्ठा aspeed_sig_expr *expr = शून्य;
		स्थिर काष्ठा aspeed_sig_expr **funcs;
		स्थिर काष्ठा aspeed_sig_expr ***prios;

		pr_debug("Muxing pin %s for %s\n", pdesc->name, pfunc->name);

		अगर (!pdesc)
			वापस -EINVAL;

		prios = pdesc->prios;

		अगर (!prios)
			जारी;

		/* Disable functions at a higher priority than that requested */
		जबतक ((funcs = *prios)) अणु
			expr = aspeed_find_expr_by_name(funcs, pfunc->name);

			अगर (expr)
				अवरोध;

			ret = aspeed_disable_sig(&pdata->pinmux, funcs);
			अगर (ret)
				वापस ret;

			prios++;
		पूर्ण

		अगर (!expr) अणु
			अक्षर *functions = get_defined_functions(pdesc);
			अक्षर *संकेतs = get_defined_संकेतs(pdesc);

			pr_warn("No function %s found on pin %s (%d). Found signal(s) %s for function(s) %s\n",
				pfunc->name, pdesc->name, pin, संकेतs,
				functions);
			kमुक्त(संकेतs);
			kमुक्त(functions);

			वापस -ENXIO;
		पूर्ण

		ret = aspeed_sig_expr_enable(&pdata->pinmux, expr);
		अगर (ret)
			वापस ret;

		pr_debug("Muxed pin %s as %s for %s\n", pdesc->name, expr->संकेत,
			 expr->function);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool aspeed_expr_is_gpio(स्थिर काष्ठा aspeed_sig_expr *expr)
अणु
	/*
	 * We need to dअगरferentiate between GPIO and non-GPIO संकेतs to
	 * implement the gpio_request_enable() पूर्णांकerface. For better or worse
	 * the ASPEED pinctrl driver uses the expression names to determine
	 * whether an expression will mux a pin क्रम GPIO.
	 *
	 * Generally we have the following - A GPIO such as B1 has:
	 *
	 *    - expr->संकेत set to "GPIOB1"
	 *    - expr->function set to "GPIOB1"
	 *
	 * Using this fact we can determine whether the provided expression is
	 * a GPIO expression by testing the संकेत name क्रम the string prefix
	 * "GPIO".
	 *
	 * However, some GPIOs are input-only, and the ASPEED datasheets name
	 * them dअगरferently. An input-only GPIO such as T0 has:
	 *
	 *    - expr->संकेत set to "GPIT0"
	 *    - expr->function set to "GPIT0"
	 *
	 * It's tempting to generalise the prefix test from "GPIO" to "GPI" to
	 * account क्रम both GPIOs and GPIs, but in करोing so we run aground on
	 * another feature:
	 *
	 * Some pins in the ASPEED BMC SoCs have a "pass-through" GPIO
	 * function where the input state of one pin is replicated as the
	 * output state of another (as अगर they were लघुed together - a mux
	 * configuration that is typically enabled by hardware strapping).
	 * This feature allows the BMC to pass e.g. घातer button state through
	 * to the host जबतक the BMC is yet to boot, but take control of the
	 * button state once the BMC has booted by muxing each pin as a
	 * separate, pin-specअगरic GPIO.
	 *
	 * Conceptually this pass-through mode is a क्रमm of GPIO and is named
	 * as such in the datasheets, e.g. "GPID0". This naming similarity
	 * trips us up with the simple GPI-prefixed-संकेत-name scheme
	 * discussed above, as the pass-through configuration is not what we
	 * want when muxing a pin as GPIO क्रम the GPIO subप्रणाली.
	 *
	 * On e.g. the AST2400, a pass-through function "GPID0" is grouped on
	 * balls A18 and D16, where we have:
	 *
	 *    For ball A18:
	 *    - expr->संकेत set to "GPID0IN"
	 *    - expr->function set to "GPID0"
	 *
	 *    For ball D16:
	 *    - expr->संकेत set to "GPID0OUT"
	 *    - expr->function set to "GPID0"
	 *
	 * By contrast, the pin-specअगरic GPIO expressions क्रम the same pins are
	 * as follows:
	 *
	 *    For ball A18:
	 *    - expr->संकेत looks like "GPIOD0"
	 *    - expr->function looks like "GPIOD0"
	 *
	 *    For ball D16:
	 *    - expr->संकेत looks like "GPIOD1"
	 *    - expr->function looks like "GPIOD1"
	 *
	 * Testing both the संकेत _and_ function names gives us the means
	 * dअगरferentiate the pass-through GPIO pinmux configuration from the
	 * pin-specअगरic configuration that the GPIO subप्रणाली is after: An
	 * expression is a pin-specअगरic (non-pass-through) GPIO configuration
	 * अगर the संकेत prefix is "GPI" and the संकेत name matches the
	 * function name.
	 */
	वापस !म_भेदन(expr->संकेत, "GPI", 3) &&
			!म_भेद(expr->संकेत, expr->function);
पूर्ण

अटल bool aspeed_gpio_in_exprs(स्थिर काष्ठा aspeed_sig_expr **exprs)
अणु
	अगर (!exprs)
		वापस false;

	जबतक (*exprs) अणु
		अगर (aspeed_expr_is_gpio(*exprs))
			वापस true;
		exprs++;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक aspeed_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
			       काष्ठा pinctrl_gpio_range *range,
			       अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;
	काष्ठा aspeed_pinctrl_data *pdata = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा aspeed_pin_desc *pdesc = pdata->pins[offset].drv_data;
	स्थिर काष्ठा aspeed_sig_expr ***prios, **funcs, *expr;

	अगर (!pdesc)
		वापस -EINVAL;

	prios = pdesc->prios;

	अगर (!prios)
		वापस -ENXIO;

	pr_debug("Muxing pin %s for GPIO\n", pdesc->name);

	/* Disable any functions of higher priority than GPIO */
	जबतक ((funcs = *prios)) अणु
		अगर (aspeed_gpio_in_exprs(funcs))
			अवरोध;

		ret = aspeed_disable_sig(&pdata->pinmux, funcs);
		अगर (ret)
			वापस ret;

		prios++;
	पूर्ण

	अगर (!funcs) अणु
		अक्षर *संकेतs = get_defined_संकेतs(pdesc);

		pr_warn("No GPIO signal type found on pin %s (%d). Found: %s\n",
			pdesc->name, offset, संकेतs);
		kमुक्त(संकेतs);

		वापस -ENXIO;
	पूर्ण

	expr = *funcs;

	/*
	 * Disabling all higher-priority expressions is enough to enable the
	 * lowest-priority संकेत type. As such it has no associated
	 * expression.
	 */
	अगर (!expr) अणु
		pr_debug("Muxed pin %s as GPIO\n", pdesc->name);
		वापस 0;
	पूर्ण

	/*
	 * If GPIO is not the lowest priority संकेत type, assume there is only
	 * one expression defined to enable the GPIO function
	 */
	ret = aspeed_sig_expr_enable(&pdata->pinmux, expr);
	अगर (ret)
		वापस ret;

	pr_debug("Muxed pin %s as %s\n", pdesc->name, expr->संकेत);

	वापस 0;
पूर्ण

पूर्णांक aspeed_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			 काष्ठा pinctrl_desc *pdesc,
			 काष्ठा aspeed_pinctrl_data *pdata)
अणु
	काष्ठा device *parent;
	काष्ठा pinctrl_dev *pctl;

	parent = pdev->dev.parent;
	अगर (!parent) अणु
		dev_err(&pdev->dev, "No parent for syscon pincontroller\n");
		वापस -ENODEV;
	पूर्ण

	pdata->scu = syscon_node_to_regmap(parent->of_node);
	अगर (IS_ERR(pdata->scu)) अणु
		dev_err(&pdev->dev, "No regmap for syscon pincontroller parent\n");
		वापस PTR_ERR(pdata->scu);
	पूर्ण

	pdata->pinmux.maps[ASPEED_IP_SCU] = pdata->scu;

	pctl = pinctrl_रेजिस्टर(pdesc, &pdev->dev, pdata);

	अगर (IS_ERR(pctl)) अणु
		dev_err(&pdev->dev, "Failed to register pinctrl\n");
		वापस PTR_ERR(pctl);
	पूर्ण

	platक्रमm_set_drvdata(pdev, pdata);

	वापस 0;
पूर्ण

अटल अंतरभूत bool pin_in_config_range(अचिन्हित पूर्णांक offset,
		स्थिर काष्ठा aspeed_pin_config *config)
अणु
	वापस offset >= config->pins[0] && offset <= config->pins[1];
पूर्ण

अटल अंतरभूत स्थिर काष्ठा aspeed_pin_config *find_pinconf_config(
		स्थिर काष्ठा aspeed_pinctrl_data *pdata,
		अचिन्हित पूर्णांक offset,
		क्रमागत pin_config_param param)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->nconfigs; i++) अणु
		अगर (param == pdata->configs[i].param &&
				pin_in_config_range(offset, &pdata->configs[i]))
			वापस &pdata->configs[i];
	पूर्ण

	वापस शून्य;
पूर्ण

क्रमागत aspeed_pin_config_map_type अणु MAP_TYPE_ARG, MAP_TYPE_VAL पूर्ण;

अटल स्थिर काष्ठा aspeed_pin_config_map *find_pinconf_map(
		स्थिर काष्ठा aspeed_pinctrl_data *pdata,
		क्रमागत pin_config_param param,
		क्रमागत aspeed_pin_config_map_type type,
		s64 value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pdata->nconfmaps; i++) अणु
		स्थिर काष्ठा aspeed_pin_config_map *elem;
		bool match;

		elem = &pdata->confmaps[i];

		चयन (type) अणु
		हाल MAP_TYPE_ARG:
			match = (elem->arg == -1 || elem->arg == value);
			अवरोध;
		हाल MAP_TYPE_VAL:
			match = (elem->val == value);
			अवरोध;
		पूर्ण

		अगर (param == elem->param && match)
			वापस elem;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक aspeed_pin_config_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक offset,
		अचिन्हित दीर्घ *config)
अणु
	स्थिर क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	स्थिर काष्ठा aspeed_pin_config_map *pmap;
	स्थिर काष्ठा aspeed_pinctrl_data *pdata;
	स्थिर काष्ठा aspeed_pin_config *pconf;
	अचिन्हित पूर्णांक val;
	पूर्णांक rc = 0;
	u32 arg;

	pdata = pinctrl_dev_get_drvdata(pctldev);
	pconf = find_pinconf_config(pdata, offset, param);
	अगर (!pconf)
		वापस -ENOTSUPP;

	rc = regmap_पढ़ो(pdata->scu, pconf->reg, &val);
	अगर (rc < 0)
		वापस rc;

	pmap = find_pinconf_map(pdata, param, MAP_TYPE_VAL,
			(val & pconf->mask) >> __ffs(pconf->mask));

	अगर (!pmap)
		वापस -EINVAL;

	अगर (param == PIN_CONFIG_DRIVE_STRENGTH)
		arg = (u32) pmap->arg;
	अन्यथा अगर (param == PIN_CONFIG_BIAS_PULL_DOWN)
		arg = !!pmap->arg;
	अन्यथा
		arg = 1;

	अगर (!arg)
		वापस -EINVAL;

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

पूर्णांक aspeed_pin_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक offset,
		अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	स्थिर काष्ठा aspeed_pinctrl_data *pdata;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = 0;

	pdata = pinctrl_dev_get_drvdata(pctldev);

	क्रम (i = 0; i < num_configs; i++) अणु
		स्थिर काष्ठा aspeed_pin_config_map *pmap;
		स्थिर काष्ठा aspeed_pin_config *pconf;
		क्रमागत pin_config_param param;
		अचिन्हित पूर्णांक val;
		u32 arg;

		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		pconf = find_pinconf_config(pdata, offset, param);
		अगर (!pconf)
			वापस -ENOTSUPP;

		pmap = find_pinconf_map(pdata, param, MAP_TYPE_ARG, arg);

		अगर (WARN_ON(!pmap))
			वापस -EINVAL;

		val = pmap->val << __ffs(pconf->mask);

		rc = regmap_update_bits(pdata->scu, pconf->reg,
					pconf->mask, val);

		अगर (rc < 0)
			वापस rc;

		pr_debug("%s: Set SCU%02X[0x%08X]=0x%X for param %d(=%d) on pin %d\n",
				__func__, pconf->reg, pconf->mask,
				val, param, arg, offset);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक aspeed_pin_config_group_get(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक selector,
		अचिन्हित दीर्घ *config)
अणु
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक npins;
	पूर्णांक rc;

	rc = aspeed_pinctrl_get_group_pins(pctldev, selector, &pins, &npins);
	अगर (rc < 0)
		वापस rc;

	अगर (!npins)
		वापस -ENODEV;

	rc = aspeed_pin_config_get(pctldev, pins[0], config);

	वापस rc;
पूर्ण

पूर्णांक aspeed_pin_config_group_set(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित पूर्णांक selector,
		अचिन्हित दीर्घ *configs,
		अचिन्हित पूर्णांक num_configs)
अणु
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक npins;
	पूर्णांक rc;
	पूर्णांक i;

	pr_debug("%s: Fetching pins for group selector %d\n",
			__func__, selector);
	rc = aspeed_pinctrl_get_group_pins(pctldev, selector, &pins, &npins);
	अगर (rc < 0)
		वापस rc;

	क्रम (i = 0; i < npins; i++) अणु
		rc = aspeed_pin_config_set(pctldev, pins[i], configs,
				num_configs);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण
