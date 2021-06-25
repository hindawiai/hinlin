<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2015-2017 Socionext Inc.
//   Author: Masahiro Yamada <yamada.masahiro@socionext.com>

#समावेश <linux/list.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"
#समावेश "pinctrl-uniphier.h"

#घोषणा UNIPHIER_PINCTRL_PINMUX_BASE	0x1000
#घोषणा UNIPHIER_PINCTRL_LOAD_PINMUX	0x1700
#घोषणा UNIPHIER_PINCTRL_DRVCTRL_BASE	0x1800
#घोषणा UNIPHIER_PINCTRL_DRV2CTRL_BASE	0x1900
#घोषणा UNIPHIER_PINCTRL_DRV3CTRL_BASE	0x1980
#घोषणा UNIPHIER_PINCTRL_PUPDCTRL_BASE	0x1a00
#घोषणा UNIPHIER_PINCTRL_IECTRL_BASE	0x1d00

काष्ठा uniphier_pinctrl_reg_region अणु
	काष्ठा list_head node;
	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक nregs;
	u32 vals[];
पूर्ण;

काष्ठा uniphier_pinctrl_priv अणु
	काष्ठा pinctrl_desc pctldesc;
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा uniphier_pinctrl_socdata *socdata;
	काष्ठा list_head reg_regions;
पूर्ण;

अटल पूर्णांक uniphier_pctl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	वापस priv->socdata->groups_count;
पूर्ण

अटल स्थिर अक्षर *uniphier_pctl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						अचिन्हित selector)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	वापस priv->socdata->groups[selector].name;
पूर्ण

अटल पूर्णांक uniphier_pctl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित selector,
					स्थिर अचिन्हित **pins,
					अचिन्हित *num_pins)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	*pins = priv->socdata->groups[selector].pins;
	*num_pins = priv->socdata->groups[selector].num_pins;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम uniphier_pctl_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
				       काष्ठा seq_file *s, अचिन्हित offset)
अणु
	स्थिर काष्ठा pin_desc *desc = pin_desc_get(pctldev, offset);
	स्थिर अक्षर *pull_dir, *drv_type;

	चयन (uniphier_pin_get_pull_dir(desc->drv_data)) अणु
	हाल UNIPHIER_PIN_PULL_UP:
		pull_dir = "UP";
		अवरोध;
	हाल UNIPHIER_PIN_PULL_DOWN:
		pull_dir = "DOWN";
		अवरोध;
	हाल UNIPHIER_PIN_PULL_UP_FIXED:
		pull_dir = "UP(FIXED)";
		अवरोध;
	हाल UNIPHIER_PIN_PULL_DOWN_FIXED:
		pull_dir = "DOWN(FIXED)";
		अवरोध;
	हाल UNIPHIER_PIN_PULL_NONE:
		pull_dir = "NONE";
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	चयन (uniphier_pin_get_drv_type(desc->drv_data)) अणु
	हाल UNIPHIER_PIN_DRV_1BIT:
		drv_type = "4/8(mA)";
		अवरोध;
	हाल UNIPHIER_PIN_DRV_2BIT:
		drv_type = "8/12/16/20(mA)";
		अवरोध;
	हाल UNIPHIER_PIN_DRV_3BIT:
		drv_type = "4/5/7/9/11/12/14/16(mA)";
		अवरोध;
	हाल UNIPHIER_PIN_DRV_FIXED4:
		drv_type = "4(mA)";
		अवरोध;
	हाल UNIPHIER_PIN_DRV_FIXED5:
		drv_type = "5(mA)";
		अवरोध;
	हाल UNIPHIER_PIN_DRV_FIXED8:
		drv_type = "8(mA)";
		अवरोध;
	हाल UNIPHIER_PIN_DRV_NONE:
		drv_type = "NONE";
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	seq_म_लिखो(s, " PULL_DIR=%s  DRV_TYPE=%s", pull_dir, drv_type);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pinctrl_ops uniphier_pctlops = अणु
	.get_groups_count = uniphier_pctl_get_groups_count,
	.get_group_name = uniphier_pctl_get_group_name,
	.get_group_pins = uniphier_pctl_get_group_pins,
#अगर_घोषित CONFIG_DEBUG_FS
	.pin_dbg_show = uniphier_pctl_pin_dbg_show,
#पूर्ण_अगर
	.dt_node_to_map = pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक uniphier_conf_drv_strengths_1bit[] = अणु4, 8पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uniphier_conf_drv_strengths_2bit[] = अणु8, 12, 16, 20पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uniphier_conf_drv_strengths_3bit[] = अणु4, 5, 7, 9, 11,
								12, 14, 16पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uniphier_conf_drv_strengths_fixed4[] = अणु4पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uniphier_conf_drv_strengths_fixed5[] = अणु5पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uniphier_conf_drv_strengths_fixed8[] = अणु8पूर्ण;

अटल पूर्णांक uniphier_conf_get_drvctrl_data(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक *reg,
					  अचिन्हित पूर्णांक *shअगरt,
					  अचिन्हित पूर्णांक *mask,
					  स्थिर अचिन्हित पूर्णांक **strengths)
अणु
	स्थिर काष्ठा pin_desc *desc = pin_desc_get(pctldev, pin);
	क्रमागत uniphier_pin_drv_type type =
				uniphier_pin_get_drv_type(desc->drv_data);
	अचिन्हित पूर्णांक base = 0;
	अचिन्हित पूर्णांक stride = 0;
	अचिन्हित पूर्णांक width = 0;
	अचिन्हित पूर्णांक drvctrl;

	चयन (type) अणु
	हाल UNIPHIER_PIN_DRV_1BIT:
		*strengths = uniphier_conf_drv_strengths_1bit;
		base = UNIPHIER_PINCTRL_DRVCTRL_BASE;
		stride = 1;
		width = 1;
		अवरोध;
	हाल UNIPHIER_PIN_DRV_2BIT:
		*strengths = uniphier_conf_drv_strengths_2bit;
		base = UNIPHIER_PINCTRL_DRV2CTRL_BASE;
		stride = 2;
		width = 2;
		अवरोध;
	हाल UNIPHIER_PIN_DRV_3BIT:
		*strengths = uniphier_conf_drv_strengths_3bit;
		base = UNIPHIER_PINCTRL_DRV3CTRL_BASE;
		stride = 4;
		width = 3;
		अवरोध;
	हाल UNIPHIER_PIN_DRV_FIXED4:
		*strengths = uniphier_conf_drv_strengths_fixed4;
		अवरोध;
	हाल UNIPHIER_PIN_DRV_FIXED5:
		*strengths = uniphier_conf_drv_strengths_fixed5;
		अवरोध;
	हाल UNIPHIER_PIN_DRV_FIXED8:
		*strengths = uniphier_conf_drv_strengths_fixed8;
		अवरोध;
	शेष:
		/* drive strength control is not supported क्रम this pin */
		वापस -EINVAL;
	पूर्ण

	drvctrl = uniphier_pin_get_drvctrl(desc->drv_data);
	drvctrl *= stride;

	*reg = base + drvctrl / 32 * 4;
	*shअगरt = drvctrl % 32;
	*mask = (1U << width) - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_conf_pin_bias_get(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित पूर्णांक pin,
				      क्रमागत pin_config_param param)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा pin_desc *desc = pin_desc_get(pctldev, pin);
	क्रमागत uniphier_pin_pull_dir pull_dir =
				uniphier_pin_get_pull_dir(desc->drv_data);
	अचिन्हित पूर्णांक pupdctrl, reg, shअगरt, val;
	अचिन्हित पूर्णांक expected = 1;
	पूर्णांक ret;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (pull_dir == UNIPHIER_PIN_PULL_NONE)
			वापस 0;
		अगर (pull_dir == UNIPHIER_PIN_PULL_UP_FIXED ||
		    pull_dir == UNIPHIER_PIN_PULL_DOWN_FIXED)
			वापस -EINVAL;
		expected = 0;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (pull_dir == UNIPHIER_PIN_PULL_UP_FIXED)
			वापस 0;
		अगर (pull_dir != UNIPHIER_PIN_PULL_UP)
			वापस -EINVAL;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (pull_dir == UNIPHIER_PIN_PULL_DOWN_FIXED)
			वापस 0;
		अगर (pull_dir != UNIPHIER_PIN_PULL_DOWN)
			वापस -EINVAL;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	pupdctrl = uniphier_pin_get_pupdctrl(desc->drv_data);

	reg = UNIPHIER_PINCTRL_PUPDCTRL_BASE + pupdctrl / 32 * 4;
	shअगरt = pupdctrl % 32;

	ret = regmap_पढ़ो(priv->regmap, reg, &val);
	अगर (ret)
		वापस ret;

	val = (val >> shअगरt) & 1;

	वापस (val == expected) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक uniphier_conf_pin_drive_get(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित पूर्णांक pin, u32 *strength)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक reg, shअगरt, mask, val;
	स्थिर अचिन्हित पूर्णांक *strengths;
	पूर्णांक ret;

	ret = uniphier_conf_get_drvctrl_data(pctldev, pin, &reg, &shअगरt,
					     &mask, &strengths);
	अगर (ret)
		वापस ret;

	अगर (mask) अणु
		ret = regmap_पढ़ो(priv->regmap, reg, &val);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		val = 0;
	पूर्ण

	*strength = strengths[(val >> shअगरt) & mask];

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_conf_pin_input_enable_get(काष्ठा pinctrl_dev *pctldev,
					      अचिन्हित पूर्णांक pin)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा pin_desc *desc = pin_desc_get(pctldev, pin);
	अचिन्हित पूर्णांक iectrl = uniphier_pin_get_iectrl(desc->drv_data);
	अचिन्हित पूर्णांक reg, mask, val;
	पूर्णांक ret;

	अगर (iectrl == UNIPHIER_PIN_IECTRL_NONE)
		/* This pin is always input-enabled. */
		वापस 0;

	अगर (priv->socdata->caps & UNIPHIER_PINCTRL_CAPS_PERPIN_IECTRL)
		iectrl = pin;

	reg = UNIPHIER_PINCTRL_IECTRL_BASE + iectrl / 32 * 4;
	mask = BIT(iectrl % 32);

	ret = regmap_पढ़ो(priv->regmap, reg, &val);
	अगर (ret)
		वापस ret;

	वापस val & mask ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक uniphier_conf_pin_config_get(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित pin,
					अचिन्हित दीर्घ *configs)
अणु
	क्रमागत pin_config_param param = pinconf_to_config_param(*configs);
	bool has_arg = false;
	u32 arg;
	पूर्णांक ret;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		ret = uniphier_conf_pin_bias_get(pctldev, pin, param);
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		ret = uniphier_conf_pin_drive_get(pctldev, pin, &arg);
		has_arg = true;
		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
		ret = uniphier_conf_pin_input_enable_get(pctldev, pin);
		अवरोध;
	शेष:
		/* unsupported parameter */
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret == 0 && has_arg)
		*configs = pinconf_to_config_packed(param, arg);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_conf_pin_bias_set(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित पूर्णांक pin,
				      क्रमागत pin_config_param param, u32 arg)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा pin_desc *desc = pin_desc_get(pctldev, pin);
	क्रमागत uniphier_pin_pull_dir pull_dir =
				uniphier_pin_get_pull_dir(desc->drv_data);
	अचिन्हित पूर्णांक pupdctrl, reg, shअगरt;
	अचिन्हित पूर्णांक val = 1;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (pull_dir == UNIPHIER_PIN_PULL_NONE)
			वापस 0;
		अगर (pull_dir == UNIPHIER_PIN_PULL_UP_FIXED ||
		    pull_dir == UNIPHIER_PIN_PULL_DOWN_FIXED) अणु
			dev_err(pctldev->dev,
				"can not disable pull register for pin %s\n",
				desc->name);
			वापस -EINVAL;
		पूर्ण
		val = 0;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (pull_dir == UNIPHIER_PIN_PULL_UP_FIXED && arg != 0)
			वापस 0;
		अगर (pull_dir != UNIPHIER_PIN_PULL_UP) अणु
			dev_err(pctldev->dev,
				"pull-up is unsupported for pin %s\n",
				desc->name);
			वापस -EINVAL;
		पूर्ण
		अगर (arg == 0) अणु
			dev_err(pctldev->dev, "pull-up can not be total\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (pull_dir == UNIPHIER_PIN_PULL_DOWN_FIXED && arg != 0)
			वापस 0;
		अगर (pull_dir != UNIPHIER_PIN_PULL_DOWN) अणु
			dev_err(pctldev->dev,
				"pull-down is unsupported for pin %s\n",
				desc->name);
			वापस -EINVAL;
		पूर्ण
		अगर (arg == 0) अणु
			dev_err(pctldev->dev, "pull-down can not be total\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
		अगर (pull_dir == UNIPHIER_PIN_PULL_NONE) अणु
			dev_err(pctldev->dev,
				"pull-up/down is unsupported for pin %s\n",
				desc->name);
			वापस -EINVAL;
		पूर्ण

		अगर (arg == 0)
			वापस 0; /* configuration ingored */
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	pupdctrl = uniphier_pin_get_pupdctrl(desc->drv_data);

	reg = UNIPHIER_PINCTRL_PUPDCTRL_BASE + pupdctrl / 32 * 4;
	shअगरt = pupdctrl % 32;

	वापस regmap_update_bits(priv->regmap, reg, 1 << shअगरt, val << shअगरt);
पूर्ण

अटल पूर्णांक uniphier_conf_pin_drive_set(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित पूर्णांक pin, u32 strength)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा pin_desc *desc = pin_desc_get(pctldev, pin);
	अचिन्हित पूर्णांक reg, shअगरt, mask, val;
	स्थिर अचिन्हित पूर्णांक *strengths;
	पूर्णांक ret;

	ret = uniphier_conf_get_drvctrl_data(pctldev, pin, &reg, &shअगरt,
					     &mask, &strengths);
	अगर (ret) अणु
		dev_err(pctldev->dev, "cannot set drive strength for pin %s\n",
			desc->name);
		वापस ret;
	पूर्ण

	क्रम (val = 0; val <= mask; val++) अणु
		अगर (strengths[val] > strength)
			अवरोध;
	पूर्ण

	अगर (val == 0) अणु
		dev_err(pctldev->dev,
			"unsupported drive strength %u mA for pin %s\n",
			strength, desc->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!mask)
		वापस 0;

	val--;

	वापस regmap_update_bits(priv->regmap, reg,
				  mask << shअगरt, val << shअगरt);
पूर्ण

अटल पूर्णांक uniphier_conf_pin_input_enable(काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित पूर्णांक pin, u32 enable)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा pin_desc *desc = pin_desc_get(pctldev, pin);
	अचिन्हित पूर्णांक iectrl = uniphier_pin_get_iectrl(desc->drv_data);
	अचिन्हित पूर्णांक reg, mask;

	/*
	 * Multiple pins share one input enable, per-pin disabling is
	 * impossible.
	 */
	अगर (!(priv->socdata->caps & UNIPHIER_PINCTRL_CAPS_PERPIN_IECTRL) &&
	    !enable)
		वापस -EINVAL;

	/* UNIPHIER_PIN_IECTRL_NONE means the pin is always input-enabled */
	अगर (iectrl == UNIPHIER_PIN_IECTRL_NONE)
		वापस enable ? 0 : -EINVAL;

	अगर (priv->socdata->caps & UNIPHIER_PINCTRL_CAPS_PERPIN_IECTRL)
		iectrl = pin;

	reg = UNIPHIER_PINCTRL_IECTRL_BASE + iectrl / 32 * 4;
	mask = BIT(iectrl % 32);

	वापस regmap_update_bits(priv->regmap, reg, mask, enable ? mask : 0);
पूर्ण

अटल पूर्णांक uniphier_conf_pin_config_set(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित pin,
					अचिन्हित दीर्घ *configs,
					अचिन्हित num_configs)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_configs; i++) अणु
		क्रमागत pin_config_param param =
					pinconf_to_config_param(configs[i]);
		u32 arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
		हाल PIN_CONFIG_BIAS_PULL_UP:
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
		हाल PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
			ret = uniphier_conf_pin_bias_set(pctldev, pin,
							 param, arg);
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			ret = uniphier_conf_pin_drive_set(pctldev, pin, arg);
			अवरोध;
		हाल PIN_CONFIG_INPUT_ENABLE:
			ret = uniphier_conf_pin_input_enable(pctldev, pin, arg);
			अवरोध;
		शेष:
			dev_err(pctldev->dev,
				"unsupported configuration parameter %u\n",
				param);
			वापस -EINVAL;
		पूर्ण

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_conf_pin_config_group_set(काष्ठा pinctrl_dev *pctldev,
					      अचिन्हित selector,
					      अचिन्हित दीर्घ *configs,
					      अचिन्हित num_configs)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर अचिन्हित *pins = priv->socdata->groups[selector].pins;
	अचिन्हित num_pins = priv->socdata->groups[selector].num_pins;
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_pins; i++) अणु
		ret = uniphier_conf_pin_config_set(pctldev, pins[i],
						   configs, num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops uniphier_confops = अणु
	.is_generic = true,
	.pin_config_get = uniphier_conf_pin_config_get,
	.pin_config_set = uniphier_conf_pin_config_set,
	.pin_config_group_set = uniphier_conf_pin_config_group_set,
पूर्ण;

अटल पूर्णांक uniphier_pmx_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	वापस priv->socdata->functions_count;
पूर्ण

अटल स्थिर अक्षर *uniphier_pmx_get_function_name(काष्ठा pinctrl_dev *pctldev,
						  अचिन्हित selector)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	वापस priv->socdata->functions[selector].name;
पूर्ण

अटल पूर्णांक uniphier_pmx_get_function_groups(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित selector,
					    स्थिर अक्षर * स्थिर **groups,
					    अचिन्हित *num_groups)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	*groups = priv->socdata->functions[selector].groups;
	*num_groups = priv->socdata->functions[selector].num_groups;

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_pmx_set_one_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
				    पूर्णांक muxval)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक mux_bits, reg_stride, reg, reg_end, shअगरt, mask;
	bool load_pinctrl;
	पूर्णांक ret;

	/* some pins need input-enabling */
	ret = uniphier_conf_pin_input_enable(pctldev, pin, 1);
	अगर (ret)
		वापस ret;

	अगर (muxval < 0)
		वापस 0;	/* dedicated pin; nothing to करो क्रम pin-mux */

	अगर (priv->socdata->caps & UNIPHIER_PINCTRL_CAPS_DBGMUX_SEPARATE) अणु
		/*
		 *  Mode     reg_offset     bit_position
		 *  Normal    4 * n        shअगरt+3:shअगरt
		 *  Debug     4 * n        shअगरt+7:shअगरt+4
		 */
		mux_bits = 4;
		reg_stride = 8;
		load_pinctrl = true;
	पूर्ण अन्यथा अणु
		/*
		 *  Mode     reg_offset     bit_position
		 *  Normal    8 * n        shअगरt+3:shअगरt
		 *  Debug     8 * n + 4    shअगरt+3:shअगरt
		 */
		mux_bits = 8;
		reg_stride = 4;
		load_pinctrl = false;
	पूर्ण

	reg = UNIPHIER_PINCTRL_PINMUX_BASE + pin * mux_bits / 32 * reg_stride;
	reg_end = reg + reg_stride;
	shअगरt = pin * mux_bits % 32;
	mask = (1U << mux_bits) - 1;

	/*
	 * If reg_stride is greater than 4, the MSB of each pinsel shall be
	 * stored in the offset+4.
	 */
	क्रम (; reg < reg_end; reg += 4) अणु
		ret = regmap_update_bits(priv->regmap, reg,
					 mask << shअगरt, muxval << shअगरt);
		अगर (ret)
			वापस ret;
		muxval >>= mux_bits;
	पूर्ण

	अगर (load_pinctrl) अणु
		ret = regmap_ग_लिखो(priv->regmap,
				   UNIPHIER_PINCTRL_LOAD_PINMUX, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_pmx_set_mux(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित func_selector,
				अचिन्हित group_selector)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा uniphier_pinctrl_group *grp =
					&priv->socdata->groups[group_selector];
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < grp->num_pins; i++) अणु
		ret = uniphier_pmx_set_one_mux(pctldev, grp->pins[i],
					       grp->muxvals[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_pmx_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
					    काष्ठा pinctrl_gpio_range *range,
					    अचिन्हित offset)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक gpio_offset;
	पूर्णांक muxval, i;

	अगर (range->pins) अणु
		क्रम (i = 0; i < range->npins; i++)
			अगर (range->pins[i] == offset)
				अवरोध;

		अगर (WARN_ON(i == range->npins))
			वापस -EINVAL;

		gpio_offset = i;
	पूर्ण अन्यथा अणु
		gpio_offset = offset - range->pin_base;
	पूर्ण

	gpio_offset += range->id;

	muxval = priv->socdata->get_gpio_muxval(offset, gpio_offset);

	वापस uniphier_pmx_set_one_mux(pctldev, offset, muxval);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops uniphier_pmxops = अणु
	.get_functions_count = uniphier_pmx_get_functions_count,
	.get_function_name = uniphier_pmx_get_function_name,
	.get_function_groups = uniphier_pmx_get_function_groups,
	.set_mux = uniphier_pmx_set_mux,
	.gpio_request_enable = uniphier_pmx_gpio_request_enable,
	.strict = true,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक uniphier_pinctrl_suspend(काष्ठा device *dev)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = dev_get_drvdata(dev);
	काष्ठा uniphier_pinctrl_reg_region *r;
	पूर्णांक ret;

	list_क्रम_each_entry(r, &priv->reg_regions, node) अणु
		ret = regmap_bulk_पढ़ो(priv->regmap, r->base, r->vals,
				       r->nregs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_pinctrl_resume(काष्ठा device *dev)
अणु
	काष्ठा uniphier_pinctrl_priv *priv = dev_get_drvdata(dev);
	काष्ठा uniphier_pinctrl_reg_region *r;
	पूर्णांक ret;

	list_क्रम_each_entry(r, &priv->reg_regions, node) अणु
		ret = regmap_bulk_ग_लिखो(priv->regmap, r->base, r->vals,
					r->nregs);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (priv->socdata->caps & UNIPHIER_PINCTRL_CAPS_DBGMUX_SEPARATE) अणु
		ret = regmap_ग_लिखो(priv->regmap,
				   UNIPHIER_PINCTRL_LOAD_PINMUX, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_pinctrl_add_reg_region(काष्ठा device *dev,
					   काष्ठा uniphier_pinctrl_priv *priv,
					   अचिन्हित पूर्णांक base,
					   अचिन्हित पूर्णांक count,
					   अचिन्हित पूर्णांक width)
अणु
	काष्ठा uniphier_pinctrl_reg_region *region;
	अचिन्हित पूर्णांक nregs;

	अगर (!count)
		वापस 0;

	nregs = DIV_ROUND_UP(count * width, 32);

	region = devm_kzalloc(dev, काष्ठा_size(region, vals, nregs),
			      GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;

	region->base = base;
	region->nregs = nregs;

	list_add_tail(&region->node, &priv->reg_regions);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक uniphier_pinctrl_pm_init(काष्ठा device *dev,
				    काष्ठा uniphier_pinctrl_priv *priv)
अणु
#अगर_घोषित CONFIG_PM_SLEEP
	स्थिर काष्ठा uniphier_pinctrl_socdata *socdata = priv->socdata;
	अचिन्हित पूर्णांक num_drvctrl = 0;
	अचिन्हित पूर्णांक num_drv2ctrl = 0;
	अचिन्हित पूर्णांक num_drv3ctrl = 0;
	अचिन्हित पूर्णांक num_pupdctrl = 0;
	अचिन्हित पूर्णांक num_iectrl = 0;
	अचिन्हित पूर्णांक iectrl, drvctrl, pupdctrl;
	क्रमागत uniphier_pin_drv_type drv_type;
	क्रमागत uniphier_pin_pull_dir pull_dir;
	पूर्णांक i, ret;

	क्रम (i = 0; i < socdata->npins; i++) अणु
		व्योम *drv_data = socdata->pins[i].drv_data;

		drvctrl = uniphier_pin_get_drvctrl(drv_data);
		drv_type = uniphier_pin_get_drv_type(drv_data);
		pupdctrl = uniphier_pin_get_pupdctrl(drv_data);
		pull_dir = uniphier_pin_get_pull_dir(drv_data);
		iectrl = uniphier_pin_get_iectrl(drv_data);

		चयन (drv_type) अणु
		हाल UNIPHIER_PIN_DRV_1BIT:
			num_drvctrl = max(num_drvctrl, drvctrl + 1);
			अवरोध;
		हाल UNIPHIER_PIN_DRV_2BIT:
			num_drv2ctrl = max(num_drv2ctrl, drvctrl + 1);
			अवरोध;
		हाल UNIPHIER_PIN_DRV_3BIT:
			num_drv3ctrl = max(num_drv3ctrl, drvctrl + 1);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (pull_dir == UNIPHIER_PIN_PULL_UP ||
		    pull_dir == UNIPHIER_PIN_PULL_DOWN)
			num_pupdctrl = max(num_pupdctrl, pupdctrl + 1);

		अगर (iectrl != UNIPHIER_PIN_IECTRL_NONE) अणु
			अगर (socdata->caps & UNIPHIER_PINCTRL_CAPS_PERPIN_IECTRL)
				iectrl = i;
			num_iectrl = max(num_iectrl, iectrl + 1);
		पूर्ण
	पूर्ण

	INIT_LIST_HEAD(&priv->reg_regions);

	ret = uniphier_pinctrl_add_reg_region(dev, priv,
					      UNIPHIER_PINCTRL_PINMUX_BASE,
					      socdata->npins, 8);
	अगर (ret)
		वापस ret;

	ret = uniphier_pinctrl_add_reg_region(dev, priv,
					      UNIPHIER_PINCTRL_DRVCTRL_BASE,
					      num_drvctrl, 1);
	अगर (ret)
		वापस ret;

	ret = uniphier_pinctrl_add_reg_region(dev, priv,
					      UNIPHIER_PINCTRL_DRV2CTRL_BASE,
					      num_drv2ctrl, 2);
	अगर (ret)
		वापस ret;

	ret = uniphier_pinctrl_add_reg_region(dev, priv,
					      UNIPHIER_PINCTRL_DRV3CTRL_BASE,
					      num_drv3ctrl, 3);
	अगर (ret)
		वापस ret;

	ret = uniphier_pinctrl_add_reg_region(dev, priv,
					      UNIPHIER_PINCTRL_PUPDCTRL_BASE,
					      num_pupdctrl, 1);
	अगर (ret)
		वापस ret;

	ret = uniphier_pinctrl_add_reg_region(dev, priv,
					      UNIPHIER_PINCTRL_IECTRL_BASE,
					      num_iectrl, 1);
	अगर (ret)
		वापस ret;
#पूर्ण_अगर
	वापस 0;
पूर्ण

स्थिर काष्ठा dev_pm_ops uniphier_pinctrl_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(uniphier_pinctrl_suspend,
				     uniphier_pinctrl_resume)
पूर्ण;

पूर्णांक uniphier_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			   स्थिर काष्ठा uniphier_pinctrl_socdata *socdata)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_pinctrl_priv *priv;
	काष्ठा device_node *parent;
	पूर्णांक ret;

	अगर (!socdata ||
	    !socdata->pins || !socdata->npins ||
	    !socdata->groups || !socdata->groups_count ||
	    !socdata->functions || !socdata->functions_count) अणु
		dev_err(dev, "pinctrl socdata lacks necessary members\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	parent = of_get_parent(dev->of_node);
	priv->regmap = syscon_node_to_regmap(parent);
	of_node_put(parent);

	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(dev, "failed to get regmap\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	priv->socdata = socdata;
	priv->pctldesc.name = dev->driver->name;
	priv->pctldesc.pins = socdata->pins;
	priv->pctldesc.npins = socdata->npins;
	priv->pctldesc.pctlops = &uniphier_pctlops;
	priv->pctldesc.pmxops = &uniphier_pmxops;
	priv->pctldesc.confops = &uniphier_confops;
	priv->pctldesc.owner = dev->driver->owner;

	ret = uniphier_pinctrl_pm_init(dev, priv);
	अगर (ret)
		वापस ret;

	priv->pctldev = devm_pinctrl_रेजिस्टर(dev, &priv->pctldesc, priv);
	अगर (IS_ERR(priv->pctldev)) अणु
		dev_err(dev, "failed to register UniPhier pinctrl driver\n");
		वापस PTR_ERR(priv->pctldev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;
पूर्ण
