<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the NVIDIA Tegra pinmux
 *
 * Copyright (c) 2011-2012, NVIDIA CORPORATION.  All rights reserved.
 *
 * Derived from code:
 * Copyright (C) 2010 Google, Inc.
 * Copyright (C) 2010 NVIDIA Corporation
 * Copyright (C) 2009-2011 ST-Ericsson AB
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/slab.h>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"
#समावेश "pinctrl-tegra.h"

अटल अंतरभूत u32 pmx_पढ़ोl(काष्ठा tegra_pmx *pmx, u32 bank, u32 reg)
अणु
	वापस पढ़ोl(pmx->regs[bank] + reg);
पूर्ण

अटल अंतरभूत व्योम pmx_ग_लिखोl(काष्ठा tegra_pmx *pmx, u32 val, u32 bank, u32 reg)
अणु
	ग_लिखोl_relaxed(val, pmx->regs[bank] + reg);
	/* make sure pinmux रेजिस्टर ग_लिखो completed */
	pmx_पढ़ोl(pmx, bank, reg);
पूर्ण

अटल पूर्णांक tegra_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->soc->ngroups;
पूर्ण

अटल स्थिर अक्षर *tegra_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						अचिन्हित group)
अणु
	काष्ठा tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->soc->groups[group].name;
पूर्ण

अटल पूर्णांक tegra_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित group,
					स्थिर अचिन्हित **pins,
					अचिन्हित *num_pins)
अणु
	काष्ठा tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	*pins = pmx->soc->groups[group].pins;
	*num_pins = pmx->soc->groups[group].npins;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम tegra_pinctrl_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
				       काष्ठा seq_file *s,
				       अचिन्हित offset)
अणु
	seq_म_लिखो(s, " %s", dev_name(pctldev->dev));
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा cfg_param अणु
	स्थिर अक्षर *property;
	क्रमागत tegra_pinconf_param param;
पूर्ण cfg_params[] = अणु
	अणु"nvidia,pull",			TEGRA_PINCONF_PARAM_PULLपूर्ण,
	अणु"nvidia,tristate",		TEGRA_PINCONF_PARAM_TRISTATEपूर्ण,
	अणु"nvidia,enable-input",		TEGRA_PINCONF_PARAM_ENABLE_INPUTपूर्ण,
	अणु"nvidia,open-drain",		TEGRA_PINCONF_PARAM_OPEN_DRAINपूर्ण,
	अणु"nvidia,lock",			TEGRA_PINCONF_PARAM_LOCKपूर्ण,
	अणु"nvidia,io-reset",		TEGRA_PINCONF_PARAM_IORESETपूर्ण,
	अणु"nvidia,rcv-sel",		TEGRA_PINCONF_PARAM_RCV_SELपूर्ण,
	अणु"nvidia,io-hv",		TEGRA_PINCONF_PARAM_RCV_SELपूर्ण,
	अणु"nvidia,high-speed-mode",	TEGRA_PINCONF_PARAM_HIGH_SPEED_MODEपूर्ण,
	अणु"nvidia,schmitt",		TEGRA_PINCONF_PARAM_SCHMITTपूर्ण,
	अणु"nvidia,low-power-mode",	TEGRA_PINCONF_PARAM_LOW_POWER_MODEपूर्ण,
	अणु"nvidia,pull-down-strength",	TEGRA_PINCONF_PARAM_DRIVE_DOWN_STRENGTHपूर्ण,
	अणु"nvidia,pull-up-strength",	TEGRA_PINCONF_PARAM_DRIVE_UP_STRENGTHपूर्ण,
	अणु"nvidia,slew-rate-falling",	TEGRA_PINCONF_PARAM_SLEW_RATE_FALLINGपूर्ण,
	अणु"nvidia,slew-rate-rising",	TEGRA_PINCONF_PARAM_SLEW_RATE_RISINGपूर्ण,
	अणु"nvidia,drive-type",		TEGRA_PINCONF_PARAM_DRIVE_TYPEपूर्ण,
पूर्ण;

अटल पूर्णांक tegra_pinctrl_dt_subnode_to_map(काष्ठा pinctrl_dev *pctldev,
					   काष्ठा device_node *np,
					   काष्ठा pinctrl_map **map,
					   अचिन्हित *reserved_maps,
					   अचिन्हित *num_maps)
अणु
	काष्ठा device *dev = pctldev->dev;
	पूर्णांक ret, i;
	स्थिर अक्षर *function;
	u32 val;
	अचिन्हित दीर्घ config;
	अचिन्हित दीर्घ *configs = शून्य;
	अचिन्हित num_configs = 0;
	अचिन्हित reserve;
	काष्ठा property *prop;
	स्थिर अक्षर *group;

	ret = of_property_पढ़ो_string(np, "nvidia,function", &function);
	अगर (ret < 0) अणु
		/* EINVAL=missing, which is fine since it's optional */
		अगर (ret != -EINVAL)
			dev_err(dev,
				"could not parse property nvidia,function\n");
		function = शून्य;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(cfg_params); i++) अणु
		ret = of_property_पढ़ो_u32(np, cfg_params[i].property, &val);
		अगर (!ret) अणु
			config = TEGRA_PINCONF_PACK(cfg_params[i].param, val);
			ret = pinctrl_utils_add_config(pctldev, &configs,
					&num_configs, config);
			अगर (ret < 0)
				जाओ निकास;
		/* EINVAL=missing, which is fine since it's optional */
		पूर्ण अन्यथा अगर (ret != -EINVAL) अणु
			dev_err(dev, "could not parse property %s\n",
				cfg_params[i].property);
		पूर्ण
	पूर्ण

	reserve = 0;
	अगर (function != शून्य)
		reserve++;
	अगर (num_configs)
		reserve++;
	ret = of_property_count_strings(np, "nvidia,pins");
	अगर (ret < 0) अणु
		dev_err(dev, "could not parse property nvidia,pins\n");
		जाओ निकास;
	पूर्ण
	reserve *= ret;

	ret = pinctrl_utils_reserve_map(pctldev, map, reserved_maps,
					num_maps, reserve);
	अगर (ret < 0)
		जाओ निकास;

	of_property_क्रम_each_string(np, "nvidia,pins", prop, group) अणु
		अगर (function) अणु
			ret = pinctrl_utils_add_map_mux(pctldev, map,
					reserved_maps, num_maps, group,
					function);
			अगर (ret < 0)
				जाओ निकास;
		पूर्ण

		अगर (num_configs) अणु
			ret = pinctrl_utils_add_map_configs(pctldev, map,
					reserved_maps, num_maps, group,
					configs, num_configs,
					PIN_MAP_TYPE_CONFIGS_GROUP);
			अगर (ret < 0)
				जाओ निकास;
		पूर्ण
	पूर्ण

	ret = 0;

निकास:
	kमुक्त(configs);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_pinctrl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
					काष्ठा device_node *np_config,
					काष्ठा pinctrl_map **map,
					अचिन्हित *num_maps)
अणु
	अचिन्हित reserved_maps;
	काष्ठा device_node *np;
	पूर्णांक ret;

	reserved_maps = 0;
	*map = शून्य;
	*num_maps = 0;

	क्रम_each_child_of_node(np_config, np) अणु
		ret = tegra_pinctrl_dt_subnode_to_map(pctldev, np, map,
						      &reserved_maps, num_maps);
		अगर (ret < 0) अणु
			pinctrl_utils_मुक्त_map(pctldev, *map,
				*num_maps);
			of_node_put(np);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops tegra_pinctrl_ops = अणु
	.get_groups_count = tegra_pinctrl_get_groups_count,
	.get_group_name = tegra_pinctrl_get_group_name,
	.get_group_pins = tegra_pinctrl_get_group_pins,
#अगर_घोषित CONFIG_DEBUG_FS
	.pin_dbg_show = tegra_pinctrl_pin_dbg_show,
#पूर्ण_अगर
	.dt_node_to_map = tegra_pinctrl_dt_node_to_map,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक tegra_pinctrl_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->soc->nfunctions;
पूर्ण

अटल स्थिर अक्षर *tegra_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
					       अचिन्हित function)
अणु
	काष्ठा tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	वापस pmx->soc->functions[function].name;
पूर्ण

अटल पूर्णांक tegra_pinctrl_get_func_groups(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित function,
					 स्थिर अक्षर * स्थिर **groups,
					 अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);

	*groups = pmx->soc->functions[function].groups;
	*num_groups = pmx->soc->functions[function].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pinctrl_set_mux(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित function,
				 अचिन्हित group)
अणु
	काष्ठा tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा tegra_pingroup *g;
	पूर्णांक i;
	u32 val;

	g = &pmx->soc->groups[group];

	अगर (WARN_ON(g->mux_reg < 0))
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(g->funcs); i++) अणु
		अगर (g->funcs[i] == function)
			अवरोध;
	पूर्ण
	अगर (WARN_ON(i == ARRAY_SIZE(g->funcs)))
		वापस -EINVAL;

	val = pmx_पढ़ोl(pmx, g->mux_bank, g->mux_reg);
	val &= ~(0x3 << g->mux_bit);
	val |= i << g->mux_bit;
	pmx_ग_लिखोl(pmx, val, g->mux_bank, g->mux_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pinctrl_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
					     काष्ठा pinctrl_gpio_range *range,
					     अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा tegra_pingroup *group;
	u32 value;

	अगर (!pmx->soc->sfsel_in_mux)
		वापस 0;

	group = &pmx->soc->groups[offset];

	अगर (group->mux_reg < 0 || group->sfsel_bit < 0)
		वापस -EINVAL;

	value = pmx_पढ़ोl(pmx, group->mux_bank, group->mux_reg);
	value &= ~BIT(group->sfsel_bit);
	pmx_ग_लिखोl(pmx, value, group->mux_bank, group->mux_reg);

	वापस 0;
पूर्ण

अटल व्योम tegra_pinctrl_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctldev,
					    काष्ठा pinctrl_gpio_range *range,
					    अचिन्हित पूर्णांक offset)
अणु
	काष्ठा tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा tegra_pingroup *group;
	u32 value;

	अगर (!pmx->soc->sfsel_in_mux)
		वापस;

	group = &pmx->soc->groups[offset];

	अगर (group->mux_reg < 0 || group->sfsel_bit < 0)
		वापस;

	value = pmx_पढ़ोl(pmx, group->mux_bank, group->mux_reg);
	value |= BIT(group->sfsel_bit);
	pmx_ग_लिखोl(pmx, value, group->mux_bank, group->mux_reg);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops tegra_pinmux_ops = अणु
	.get_functions_count = tegra_pinctrl_get_funcs_count,
	.get_function_name = tegra_pinctrl_get_func_name,
	.get_function_groups = tegra_pinctrl_get_func_groups,
	.set_mux = tegra_pinctrl_set_mux,
	.gpio_request_enable = tegra_pinctrl_gpio_request_enable,
	.gpio_disable_मुक्त = tegra_pinctrl_gpio_disable_मुक्त,
पूर्ण;

अटल पूर्णांक tegra_pinconf_reg(काष्ठा tegra_pmx *pmx,
			     स्थिर काष्ठा tegra_pingroup *g,
			     क्रमागत tegra_pinconf_param param,
			     bool report_err,
			     s8 *bank, s32 *reg, s8 *bit, s8 *width)
अणु
	चयन (param) अणु
	हाल TEGRA_PINCONF_PARAM_PULL:
		*bank = g->pupd_bank;
		*reg = g->pupd_reg;
		*bit = g->pupd_bit;
		*width = 2;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_TRISTATE:
		*bank = g->tri_bank;
		*reg = g->tri_reg;
		*bit = g->tri_bit;
		*width = 1;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_ENABLE_INPUT:
		*bank = g->mux_bank;
		*reg = g->mux_reg;
		*bit = g->einput_bit;
		*width = 1;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_OPEN_DRAIN:
		*bank = g->mux_bank;
		*reg = g->mux_reg;
		*bit = g->odrain_bit;
		*width = 1;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_LOCK:
		*bank = g->mux_bank;
		*reg = g->mux_reg;
		*bit = g->lock_bit;
		*width = 1;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_IORESET:
		*bank = g->mux_bank;
		*reg = g->mux_reg;
		*bit = g->ioreset_bit;
		*width = 1;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_RCV_SEL:
		*bank = g->mux_bank;
		*reg = g->mux_reg;
		*bit = g->rcv_sel_bit;
		*width = 1;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_HIGH_SPEED_MODE:
		अगर (pmx->soc->hsm_in_mux) अणु
			*bank = g->mux_bank;
			*reg = g->mux_reg;
		पूर्ण अन्यथा अणु
			*bank = g->drv_bank;
			*reg = g->drv_reg;
		पूर्ण
		*bit = g->hsm_bit;
		*width = 1;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_SCHMITT:
		अगर (pmx->soc->schmitt_in_mux) अणु
			*bank = g->mux_bank;
			*reg = g->mux_reg;
		पूर्ण अन्यथा अणु
			*bank = g->drv_bank;
			*reg = g->drv_reg;
		पूर्ण
		*bit = g->schmitt_bit;
		*width = 1;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_LOW_POWER_MODE:
		*bank = g->drv_bank;
		*reg = g->drv_reg;
		*bit = g->lpmd_bit;
		*width = 2;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_DRIVE_DOWN_STRENGTH:
		*bank = g->drv_bank;
		*reg = g->drv_reg;
		*bit = g->drvdn_bit;
		*width = g->drvdn_width;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_DRIVE_UP_STRENGTH:
		*bank = g->drv_bank;
		*reg = g->drv_reg;
		*bit = g->drvup_bit;
		*width = g->drvup_width;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_SLEW_RATE_FALLING:
		*bank = g->drv_bank;
		*reg = g->drv_reg;
		*bit = g->slwf_bit;
		*width = g->slwf_width;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_SLEW_RATE_RISING:
		*bank = g->drv_bank;
		*reg = g->drv_reg;
		*bit = g->slwr_bit;
		*width = g->slwr_width;
		अवरोध;
	हाल TEGRA_PINCONF_PARAM_DRIVE_TYPE:
		अगर (pmx->soc->drvtype_in_mux) अणु
			*bank = g->mux_bank;
			*reg = g->mux_reg;
		पूर्ण अन्यथा अणु
			*bank = g->drv_bank;
			*reg = g->drv_reg;
		पूर्ण
		*bit = g->drvtype_bit;
		*width = 2;
		अवरोध;
	शेष:
		dev_err(pmx->dev, "Invalid config param %04x\n", param);
		वापस -ENOTSUPP;
	पूर्ण

	अगर (*reg < 0 || *bit < 0)  अणु
		अगर (report_err) अणु
			स्थिर अक्षर *prop = "unknown";
			पूर्णांक i;

			क्रम (i = 0; i < ARRAY_SIZE(cfg_params); i++) अणु
				अगर (cfg_params[i].param == param) अणु
					prop = cfg_params[i].property;
					अवरोध;
				पूर्ण
			पूर्ण

			dev_err(pmx->dev,
				"Config param %04x (%s) not supported on group %s\n",
				param, prop, g->name);
		पूर्ण
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित pin, अचिन्हित दीर्घ *config)
अणु
	dev_err(pctldev->dev, "pin_config_get op not supported\n");
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक tegra_pinconf_set(काष्ठा pinctrl_dev *pctldev,
			     अचिन्हित pin, अचिन्हित दीर्घ *configs,
			     अचिन्हित num_configs)
अणु
	dev_err(pctldev->dev, "pin_config_set op not supported\n");
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक tegra_pinconf_group_get(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित group, अचिन्हित दीर्घ *config)
अणु
	काष्ठा tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत tegra_pinconf_param param = TEGRA_PINCONF_UNPACK_PARAM(*config);
	u16 arg;
	स्थिर काष्ठा tegra_pingroup *g;
	पूर्णांक ret;
	s8 bank, bit, width;
	s32 reg;
	u32 val, mask;

	g = &pmx->soc->groups[group];

	ret = tegra_pinconf_reg(pmx, g, param, true, &bank, &reg, &bit,
				&width);
	अगर (ret < 0)
		वापस ret;

	val = pmx_पढ़ोl(pmx, bank, reg);
	mask = (1 << width) - 1;
	arg = (val >> bit) & mask;

	*config = TEGRA_PINCONF_PACK(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित group, अचिन्हित दीर्घ *configs,
				   अचिन्हित num_configs)
अणु
	काष्ठा tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत tegra_pinconf_param param;
	u16 arg;
	स्थिर काष्ठा tegra_pingroup *g;
	पूर्णांक ret, i;
	s8 bank, bit, width;
	s32 reg;
	u32 val, mask;

	g = &pmx->soc->groups[group];

	क्रम (i = 0; i < num_configs; i++) अणु
		param = TEGRA_PINCONF_UNPACK_PARAM(configs[i]);
		arg = TEGRA_PINCONF_UNPACK_ARG(configs[i]);

		ret = tegra_pinconf_reg(pmx, g, param, true, &bank, &reg, &bit,
					&width);
		अगर (ret < 0)
			वापस ret;

		val = pmx_पढ़ोl(pmx, bank, reg);

		/* LOCK can't be cleared */
		अगर (param == TEGRA_PINCONF_PARAM_LOCK) अणु
			अगर ((val & BIT(bit)) && !arg) अणु
				dev_err(pctldev->dev, "LOCK bit cannot be cleared\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		/* Special-हाल Boolean values; allow any non-zero as true */
		अगर (width == 1)
			arg = !!arg;

		/* Range-check user-supplied value */
		mask = (1 << width) - 1;
		अगर (arg & ~mask) अणु
			dev_err(pctldev->dev,
				"config %lx: %x too big for %d bit register\n",
				configs[i], arg, width);
			वापस -EINVAL;
		पूर्ण

		/* Update रेजिस्टर */
		val &= ~(mask << bit);
		val |= arg << bit;
		pmx_ग_लिखोl(pmx, val, bank, reg);
	पूर्ण /* क्रम each config */

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम tegra_pinconf_dbg_show(काष्ठा pinctrl_dev *pctldev,
				   काष्ठा seq_file *s, अचिन्हित offset)
अणु
पूर्ण

अटल स्थिर अक्षर *strip_prefix(स्थिर अक्षर *s)
अणु
	स्थिर अक्षर *comma = म_अक्षर(s, ',');
	अगर (!comma)
		वापस s;

	वापस comma + 1;
पूर्ण

अटल व्योम tegra_pinconf_group_dbg_show(काष्ठा pinctrl_dev *pctldev,
					 काष्ठा seq_file *s, अचिन्हित group)
अणु
	काष्ठा tegra_pmx *pmx = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा tegra_pingroup *g;
	पूर्णांक i, ret;
	s8 bank, bit, width;
	s32 reg;
	u32 val;

	g = &pmx->soc->groups[group];

	क्रम (i = 0; i < ARRAY_SIZE(cfg_params); i++) अणु
		ret = tegra_pinconf_reg(pmx, g, cfg_params[i].param, false,
					&bank, &reg, &bit, &width);
		अगर (ret < 0)
			जारी;

		val = pmx_पढ़ोl(pmx, bank, reg);
		val >>= bit;
		val &= (1 << width) - 1;

		seq_म_लिखो(s, "\n\t%s=%u",
			   strip_prefix(cfg_params[i].property), val);
	पूर्ण
पूर्ण

अटल व्योम tegra_pinconf_config_dbg_show(काष्ठा pinctrl_dev *pctldev,
					  काष्ठा seq_file *s,
					  अचिन्हित दीर्घ config)
अणु
	क्रमागत tegra_pinconf_param param = TEGRA_PINCONF_UNPACK_PARAM(config);
	u16 arg = TEGRA_PINCONF_UNPACK_ARG(config);
	स्थिर अक्षर *pname = "unknown";
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cfg_params); i++) अणु
		अगर (cfg_params[i].param == param) अणु
			pname = cfg_params[i].property;
			अवरोध;
		पूर्ण
	पूर्ण

	seq_म_लिखो(s, "%s=%d", strip_prefix(pname), arg);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pinconf_ops tegra_pinconf_ops = अणु
	.pin_config_get = tegra_pinconf_get,
	.pin_config_set = tegra_pinconf_set,
	.pin_config_group_get = tegra_pinconf_group_get,
	.pin_config_group_set = tegra_pinconf_group_set,
#अगर_घोषित CONFIG_DEBUG_FS
	.pin_config_dbg_show = tegra_pinconf_dbg_show,
	.pin_config_group_dbg_show = tegra_pinconf_group_dbg_show,
	.pin_config_config_dbg_show = tegra_pinconf_config_dbg_show,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा pinctrl_gpio_range tegra_pinctrl_gpio_range = अणु
	.name = "Tegra GPIOs",
	.id = 0,
	.base = 0,
पूर्ण;

अटल काष्ठा pinctrl_desc tegra_pinctrl_desc = अणु
	.pctlops = &tegra_pinctrl_ops,
	.pmxops = &tegra_pinmux_ops,
	.confops = &tegra_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल व्योम tegra_pinctrl_clear_parked_bits(काष्ठा tegra_pmx *pmx)
अणु
	पूर्णांक i = 0;
	स्थिर काष्ठा tegra_pingroup *g;
	u32 val;

	क्रम (i = 0; i < pmx->soc->ngroups; ++i) अणु
		g = &pmx->soc->groups[i];
		अगर (g->parked_biपंचांगask > 0) अणु
			अचिन्हित पूर्णांक bank, reg;

			अगर (g->mux_reg != -1) अणु
				bank = g->mux_bank;
				reg = g->mux_reg;
			पूर्ण अन्यथा अणु
				bank = g->drv_bank;
				reg = g->drv_reg;
			पूर्ण

			val = pmx_पढ़ोl(pmx, bank, reg);
			val &= ~g->parked_biपंचांगask;
			pmx_ग_लिखोl(pmx, val, bank, reg);
		पूर्ण
	पूर्ण
पूर्ण

अटल माप_प्रकार tegra_pinctrl_get_bank_size(काष्ठा device *dev,
					  अचिन्हित पूर्णांक bank_id)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, bank_id);

	वापस resource_size(res) / 4;
पूर्ण

अटल पूर्णांक tegra_pinctrl_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_pmx *pmx = dev_get_drvdata(dev);
	u32 *backup_regs = pmx->backup_regs;
	u32 __iomem *regs;
	माप_प्रकार bank_size;
	अचिन्हित पूर्णांक i, k;

	क्रम (i = 0; i < pmx->nbanks; i++) अणु
		bank_size = tegra_pinctrl_get_bank_size(dev, i);
		regs = pmx->regs[i];
		क्रम (k = 0; k < bank_size; k++)
			*backup_regs++ = पढ़ोl_relaxed(regs++);
	पूर्ण

	वापस pinctrl_क्रमce_sleep(pmx->pctl);
पूर्ण

अटल पूर्णांक tegra_pinctrl_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_pmx *pmx = dev_get_drvdata(dev);
	u32 *backup_regs = pmx->backup_regs;
	u32 __iomem *regs;
	माप_प्रकार bank_size;
	अचिन्हित पूर्णांक i, k;

	क्रम (i = 0; i < pmx->nbanks; i++) अणु
		bank_size = tegra_pinctrl_get_bank_size(dev, i);
		regs = pmx->regs[i];
		क्रम (k = 0; k < bank_size; k++)
			ग_लिखोl_relaxed(*backup_regs++, regs++);
	पूर्ण

	/* flush all the prior ग_लिखोs */
	पढ़ोl_relaxed(pmx->regs[0]);
	/* रुको क्रम pinctrl रेजिस्टर पढ़ो to complete */
	rmb();
	वापस 0;
पूर्ण

स्थिर काष्ठा dev_pm_ops tegra_pinctrl_pm = अणु
	.suspend_noirq = &tegra_pinctrl_suspend,
	.resume_noirq = &tegra_pinctrl_resume
पूर्ण;

अटल bool tegra_pinctrl_gpio_node_has_range(काष्ठा tegra_pmx *pmx)
अणु
	काष्ठा device_node *np;
	bool has_prop = false;

	np = of_find_compatible_node(शून्य, शून्य, pmx->soc->gpio_compatible);
	अगर (!np)
		वापस has_prop;

	has_prop = of_find_property(np, "gpio-ranges", शून्य);

	of_node_put(np);

	वापस has_prop;
पूर्ण

पूर्णांक tegra_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			स्थिर काष्ठा tegra_pinctrl_soc_data *soc_data)
अणु
	काष्ठा tegra_pmx *pmx;
	काष्ठा resource *res;
	पूर्णांक i;
	स्थिर अक्षर **group_pins;
	पूर्णांक fn, gn, gfn;
	अचिन्हित दीर्घ backup_regs_size = 0;

	pmx = devm_kzalloc(&pdev->dev, माप(*pmx), GFP_KERNEL);
	अगर (!pmx)
		वापस -ENOMEM;

	pmx->dev = &pdev->dev;
	pmx->soc = soc_data;

	/*
	 * Each mux group will appear in 4 functions' list of groups.
	 * This over-allocates slightly, since not all groups are mux groups.
	 */
	pmx->group_pins = devm_kसुस्मृति(&pdev->dev,
		soc_data->ngroups * 4, माप(*pmx->group_pins),
		GFP_KERNEL);
	अगर (!pmx->group_pins)
		वापस -ENOMEM;

	group_pins = pmx->group_pins;
	क्रम (fn = 0; fn < soc_data->nfunctions; fn++) अणु
		काष्ठा tegra_function *func = &soc_data->functions[fn];

		func->groups = group_pins;

		क्रम (gn = 0; gn < soc_data->ngroups; gn++) अणु
			स्थिर काष्ठा tegra_pingroup *g = &soc_data->groups[gn];

			अगर (g->mux_reg == -1)
				जारी;

			क्रम (gfn = 0; gfn < 4; gfn++)
				अगर (g->funcs[gfn] == fn)
					अवरोध;
			अगर (gfn == 4)
				जारी;

			BUG_ON(group_pins - pmx->group_pins >=
				soc_data->ngroups * 4);
			*group_pins++ = g->name;
			func->ngroups++;
		पूर्ण
	पूर्ण

	tegra_pinctrl_gpio_range.npins = pmx->soc->ngpios;
	tegra_pinctrl_desc.name = dev_name(&pdev->dev);
	tegra_pinctrl_desc.pins = pmx->soc->pins;
	tegra_pinctrl_desc.npins = pmx->soc->npins;

	क्रम (i = 0; ; i++) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		अगर (!res)
			अवरोध;
		backup_regs_size += resource_size(res);
	पूर्ण
	pmx->nbanks = i;

	pmx->regs = devm_kसुस्मृति(&pdev->dev, pmx->nbanks, माप(*pmx->regs),
				 GFP_KERNEL);
	अगर (!pmx->regs)
		वापस -ENOMEM;

	pmx->backup_regs = devm_kzalloc(&pdev->dev, backup_regs_size,
					GFP_KERNEL);
	अगर (!pmx->backup_regs)
		वापस -ENOMEM;

	क्रम (i = 0; i < pmx->nbanks; i++) अणु
		pmx->regs[i] = devm_platक्रमm_ioremap_resource(pdev, i);
		अगर (IS_ERR(pmx->regs[i]))
			वापस PTR_ERR(pmx->regs[i]);
	पूर्ण

	pmx->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, &tegra_pinctrl_desc, pmx);
	अगर (IS_ERR(pmx->pctl)) अणु
		dev_err(&pdev->dev, "Couldn't register pinctrl driver\n");
		वापस PTR_ERR(pmx->pctl);
	पूर्ण

	tegra_pinctrl_clear_parked_bits(pmx);

	अगर (pmx->soc->ngpios > 0 && !tegra_pinctrl_gpio_node_has_range(pmx))
		pinctrl_add_gpio_range(pmx->pctl, &tegra_pinctrl_gpio_range);

	platक्रमm_set_drvdata(pdev, pmx);

	dev_dbg(&pdev->dev, "Probed Tegra pinctrl driver\n");

	वापस 0;
पूर्ण
