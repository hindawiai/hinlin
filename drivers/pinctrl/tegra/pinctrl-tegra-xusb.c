<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/pinctrl/pinctrl-tegra-xusb.h>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"

#घोषणा XUSB_PADCTL_ELPG_PROGRAM 0x01c
#घोषणा XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_VCORE_DOWN (1 << 26)
#घोषणा XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN_EARLY (1 << 25)
#घोषणा XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN (1 << 24)

#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL1 0x040
#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL0_LOCKDET (1 << 19)
#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL1_REFCLK_SEL_MASK (0xf << 12)
#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL_RST (1 << 1)

#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL2 0x044
#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL2_REFCLKBUF_EN (1 << 6)
#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL2_TXCLKREF_EN (1 << 5)
#घोषणा XUSB_PADCTL_IOPHY_PLL_P0_CTL2_TXCLKREF_SEL (1 << 4)

#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1 0x138
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_LOCKDET (1 << 27)
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_MODE (1 << 24)
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_PWR_OVRD (1 << 3)
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_RST (1 << 1)
#घोषणा XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_IDDQ (1 << 0)

#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1 0x148
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ_OVRD (1 << 1)
#घोषणा XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ (1 << 0)

काष्ठा tegra_xusb_padctl_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित पूर्णांक num_groups;
पूर्ण;

काष्ठा tegra_xusb_padctl_soc अणु
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक num_pins;

	स्थिर काष्ठा tegra_xusb_padctl_function *functions;
	अचिन्हित पूर्णांक num_functions;

	स्थिर काष्ठा tegra_xusb_padctl_lane *lanes;
	अचिन्हित पूर्णांक num_lanes;
पूर्ण;

काष्ठा tegra_xusb_padctl_lane अणु
	स्थिर अक्षर *name;

	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक iddq;

	स्थिर अचिन्हित पूर्णांक *funcs;
	अचिन्हित पूर्णांक num_funcs;
पूर्ण;

काष्ठा tegra_xusb_padctl अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा mutex lock;
	काष्ठा reset_control *rst;

	स्थिर काष्ठा tegra_xusb_padctl_soc *soc;
	काष्ठा pinctrl_dev *pinctrl;
	काष्ठा pinctrl_desc desc;

	काष्ठा phy_provider *provider;
	काष्ठा phy *phys[2];

	अचिन्हित पूर्णांक enable;
पूर्ण;

अटल अंतरभूत व्योम padctl_ग_लिखोl(काष्ठा tegra_xusb_padctl *padctl, u32 value,
				 अचिन्हित दीर्घ offset)
अणु
	ग_लिखोl(value, padctl->regs + offset);
पूर्ण

अटल अंतरभूत u32 padctl_पढ़ोl(काष्ठा tegra_xusb_padctl *padctl,
			       अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl(padctl->regs + offset);
पूर्ण

अटल पूर्णांक tegra_xusb_padctl_get_groups_count(काष्ठा pinctrl_dev *pinctrl)
अणु
	काष्ठा tegra_xusb_padctl *padctl = pinctrl_dev_get_drvdata(pinctrl);

	वापस padctl->soc->num_pins;
पूर्ण

अटल स्थिर अक्षर *tegra_xusb_padctl_get_group_name(काष्ठा pinctrl_dev *pinctrl,
						    अचिन्हित पूर्णांक group)
अणु
	काष्ठा tegra_xusb_padctl *padctl = pinctrl_dev_get_drvdata(pinctrl);

	वापस padctl->soc->pins[group].name;
पूर्ण

अटल पूर्णांक tegra_xusb_padctl_get_group_pins(काष्ठा pinctrl_dev *pinctrl,
					    अचिन्हित group,
					    स्थिर अचिन्हित **pins,
					    अचिन्हित *num_pins)
अणु
	/*
	 * For the tegra-xusb pad controller groups are synonymous
	 * with lanes/pins and there is always one lane/pin per group.
	 */
	*pins = &pinctrl->desc->pins[group].number;
	*num_pins = 1;

	वापस 0;
पूर्ण

क्रमागत tegra_xusb_padctl_param अणु
	TEGRA_XUSB_PADCTL_IDDQ,
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_padctl_property अणु
	स्थिर अक्षर *name;
	क्रमागत tegra_xusb_padctl_param param;
पूर्ण properties[] = अणु
	अणु "nvidia,iddq", TEGRA_XUSB_PADCTL_IDDQ पूर्ण,
पूर्ण;

#घोषणा TEGRA_XUSB_PADCTL_PACK(param, value) ((param) << 16 | (value))
#घोषणा TEGRA_XUSB_PADCTL_UNPACK_PARAM(config) ((config) >> 16)
#घोषणा TEGRA_XUSB_PADCTL_UNPACK_VALUE(config) ((config) & 0xffff)

अटल पूर्णांक tegra_xusb_padctl_parse_subnode(काष्ठा tegra_xusb_padctl *padctl,
					   काष्ठा device_node *np,
					   काष्ठा pinctrl_map **maps,
					   अचिन्हित पूर्णांक *reserved_maps,
					   अचिन्हित पूर्णांक *num_maps)
अणु
	अचिन्हित पूर्णांक i, reserve = 0, num_configs = 0;
	अचिन्हित दीर्घ config, *configs = शून्य;
	स्थिर अक्षर *function, *group;
	काष्ठा property *prop;
	पूर्णांक err = 0;
	u32 value;

	err = of_property_पढ़ो_string(np, "nvidia,function", &function);
	अगर (err < 0) अणु
		अगर (err != -EINVAL)
			वापस err;

		function = शून्य;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(properties); i++) अणु
		err = of_property_पढ़ो_u32(np, properties[i].name, &value);
		अगर (err < 0) अणु
			अगर (err == -EINVAL)
				जारी;

			जाओ out;
		पूर्ण

		config = TEGRA_XUSB_PADCTL_PACK(properties[i].param, value);

		err = pinctrl_utils_add_config(padctl->pinctrl, &configs,
					       &num_configs, config);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	अगर (function)
		reserve++;

	अगर (num_configs)
		reserve++;

	err = of_property_count_strings(np, "nvidia,lanes");
	अगर (err < 0)
		जाओ out;

	reserve *= err;

	err = pinctrl_utils_reserve_map(padctl->pinctrl, maps, reserved_maps,
					num_maps, reserve);
	अगर (err < 0)
		जाओ out;

	of_property_क्रम_each_string(np, "nvidia,lanes", prop, group) अणु
		अगर (function) अणु
			err = pinctrl_utils_add_map_mux(padctl->pinctrl, maps,
					reserved_maps, num_maps, group,
					function);
			अगर (err < 0)
				जाओ out;
		पूर्ण

		अगर (num_configs) अणु
			err = pinctrl_utils_add_map_configs(padctl->pinctrl,
					maps, reserved_maps, num_maps, group,
					configs, num_configs,
					PIN_MAP_TYPE_CONFIGS_GROUP);
			अगर (err < 0)
				जाओ out;
		पूर्ण
	पूर्ण

	err = 0;

out:
	kमुक्त(configs);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_xusb_padctl_dt_node_to_map(काष्ठा pinctrl_dev *pinctrl,
					    काष्ठा device_node *parent,
					    काष्ठा pinctrl_map **maps,
					    अचिन्हित पूर्णांक *num_maps)
अणु
	काष्ठा tegra_xusb_padctl *padctl = pinctrl_dev_get_drvdata(pinctrl);
	अचिन्हित पूर्णांक reserved_maps = 0;
	काष्ठा device_node *np;
	पूर्णांक err;

	*num_maps = 0;
	*maps = शून्य;

	क्रम_each_child_of_node(parent, np) अणु
		err = tegra_xusb_padctl_parse_subnode(padctl, np, maps,
						      &reserved_maps,
						      num_maps);
		अगर (err < 0) अणु
			of_node_put(np);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops tegra_xusb_padctl_pinctrl_ops = अणु
	.get_groups_count = tegra_xusb_padctl_get_groups_count,
	.get_group_name = tegra_xusb_padctl_get_group_name,
	.get_group_pins = tegra_xusb_padctl_get_group_pins,
	.dt_node_to_map = tegra_xusb_padctl_dt_node_to_map,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक tegra_xusb_padctl_get_functions_count(काष्ठा pinctrl_dev *pinctrl)
अणु
	काष्ठा tegra_xusb_padctl *padctl = pinctrl_dev_get_drvdata(pinctrl);

	वापस padctl->soc->num_functions;
पूर्ण

अटल स्थिर अक्षर *
tegra_xusb_padctl_get_function_name(काष्ठा pinctrl_dev *pinctrl,
				    अचिन्हित पूर्णांक function)
अणु
	काष्ठा tegra_xusb_padctl *padctl = pinctrl_dev_get_drvdata(pinctrl);

	वापस padctl->soc->functions[function].name;
पूर्ण

अटल पूर्णांक tegra_xusb_padctl_get_function_groups(काष्ठा pinctrl_dev *pinctrl,
						 अचिन्हित पूर्णांक function,
						 स्थिर अक्षर * स्थिर **groups,
						 अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा tegra_xusb_padctl *padctl = pinctrl_dev_get_drvdata(pinctrl);

	*num_groups = padctl->soc->functions[function].num_groups;
	*groups = padctl->soc->functions[function].groups;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xusb_padctl_pinmux_set(काष्ठा pinctrl_dev *pinctrl,
					अचिन्हित पूर्णांक function,
					अचिन्हित पूर्णांक group)
अणु
	काष्ठा tegra_xusb_padctl *padctl = pinctrl_dev_get_drvdata(pinctrl);
	स्थिर काष्ठा tegra_xusb_padctl_lane *lane;
	अचिन्हित पूर्णांक i;
	u32 value;

	lane = &padctl->soc->lanes[group];

	क्रम (i = 0; i < lane->num_funcs; i++)
		अगर (lane->funcs[i] == function)
			अवरोध;

	अगर (i >= lane->num_funcs)
		वापस -EINVAL;

	value = padctl_पढ़ोl(padctl, lane->offset);
	value &= ~(lane->mask << lane->shअगरt);
	value |= i << lane->shअगरt;
	padctl_ग_लिखोl(padctl, value, lane->offset);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops tegra_xusb_padctl_pinmux_ops = अणु
	.get_functions_count = tegra_xusb_padctl_get_functions_count,
	.get_function_name = tegra_xusb_padctl_get_function_name,
	.get_function_groups = tegra_xusb_padctl_get_function_groups,
	.set_mux = tegra_xusb_padctl_pinmux_set,
पूर्ण;

अटल पूर्णांक tegra_xusb_padctl_pinconf_group_get(काष्ठा pinctrl_dev *pinctrl,
					       अचिन्हित पूर्णांक group,
					       अचिन्हित दीर्घ *config)
अणु
	काष्ठा tegra_xusb_padctl *padctl = pinctrl_dev_get_drvdata(pinctrl);
	स्थिर काष्ठा tegra_xusb_padctl_lane *lane;
	क्रमागत tegra_xusb_padctl_param param;
	u32 value;

	param = TEGRA_XUSB_PADCTL_UNPACK_PARAM(*config);
	lane = &padctl->soc->lanes[group];

	चयन (param) अणु
	हाल TEGRA_XUSB_PADCTL_IDDQ:
		/* lanes with iddq == 0 करोn't support this parameter */
		अगर (lane->iddq == 0)
			वापस -EINVAL;

		value = padctl_पढ़ोl(padctl, lane->offset);

		अगर (value & BIT(lane->iddq))
			value = 0;
		अन्यथा
			value = 1;

		*config = TEGRA_XUSB_PADCTL_PACK(param, value);
		अवरोध;

	शेष:
		dev_err(padctl->dev, "invalid configuration parameter: %04x\n",
			param);
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xusb_padctl_pinconf_group_set(काष्ठा pinctrl_dev *pinctrl,
					       अचिन्हित पूर्णांक group,
					       अचिन्हित दीर्घ *configs,
					       अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा tegra_xusb_padctl *padctl = pinctrl_dev_get_drvdata(pinctrl);
	स्थिर काष्ठा tegra_xusb_padctl_lane *lane;
	क्रमागत tegra_xusb_padctl_param param;
	अचिन्हित दीर्घ value;
	अचिन्हित पूर्णांक i;
	u32 regval;

	lane = &padctl->soc->lanes[group];

	क्रम (i = 0; i < num_configs; i++) अणु
		param = TEGRA_XUSB_PADCTL_UNPACK_PARAM(configs[i]);
		value = TEGRA_XUSB_PADCTL_UNPACK_VALUE(configs[i]);

		चयन (param) अणु
		हाल TEGRA_XUSB_PADCTL_IDDQ:
			/* lanes with iddq == 0 करोn't support this parameter */
			अगर (lane->iddq == 0)
				वापस -EINVAL;

			regval = padctl_पढ़ोl(padctl, lane->offset);

			अगर (value)
				regval &= ~BIT(lane->iddq);
			अन्यथा
				regval |= BIT(lane->iddq);

			padctl_ग_लिखोl(padctl, regval, lane->offset);
			अवरोध;

		शेष:
			dev_err(padctl->dev,
				"invalid configuration parameter: %04x\n",
				param);
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर अक्षर *strip_prefix(स्थिर अक्षर *s)
अणु
	स्थिर अक्षर *comma = म_अक्षर(s, ',');
	अगर (!comma)
		वापस s;

	वापस comma + 1;
पूर्ण

अटल व्योम
tegra_xusb_padctl_pinconf_group_dbg_show(काष्ठा pinctrl_dev *pinctrl,
					 काष्ठा seq_file *s,
					 अचिन्हित पूर्णांक group)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(properties); i++) अणु
		अचिन्हित दीर्घ config, value;
		पूर्णांक err;

		config = TEGRA_XUSB_PADCTL_PACK(properties[i].param, 0);

		err = tegra_xusb_padctl_pinconf_group_get(pinctrl, group,
							  &config);
		अगर (err < 0)
			जारी;

		value = TEGRA_XUSB_PADCTL_UNPACK_VALUE(config);

		seq_म_लिखो(s, "\n\t%s=%lu\n", strip_prefix(properties[i].name),
			   value);
	पूर्ण
पूर्ण

अटल व्योम
tegra_xusb_padctl_pinconf_config_dbg_show(काष्ठा pinctrl_dev *pinctrl,
					  काष्ठा seq_file *s,
					  अचिन्हित दीर्घ config)
अणु
	क्रमागत tegra_xusb_padctl_param param;
	स्थिर अक्षर *name = "unknown";
	अचिन्हित दीर्घ value;
	अचिन्हित पूर्णांक i;

	param = TEGRA_XUSB_PADCTL_UNPACK_PARAM(config);
	value = TEGRA_XUSB_PADCTL_UNPACK_VALUE(config);

	क्रम (i = 0; i < ARRAY_SIZE(properties); i++) अणु
		अगर (properties[i].param == param) अणु
			name = properties[i].name;
			अवरोध;
		पूर्ण
	पूर्ण

	seq_म_लिखो(s, "%s=%lu", strip_prefix(name), value);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pinconf_ops tegra_xusb_padctl_pinconf_ops = अणु
	.pin_config_group_get = tegra_xusb_padctl_pinconf_group_get,
	.pin_config_group_set = tegra_xusb_padctl_pinconf_group_set,
#अगर_घोषित CONFIG_DEBUG_FS
	.pin_config_group_dbg_show = tegra_xusb_padctl_pinconf_group_dbg_show,
	.pin_config_config_dbg_show = tegra_xusb_padctl_pinconf_config_dbg_show,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक tegra_xusb_padctl_enable(काष्ठा tegra_xusb_padctl *padctl)
अणु
	u32 value;

	mutex_lock(&padctl->lock);

	अगर (padctl->enable++ > 0)
		जाओ out;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN_EARLY;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value &= ~XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_VCORE_DOWN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

out:
	mutex_unlock(&padctl->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xusb_padctl_disable(काष्ठा tegra_xusb_padctl *padctl)
अणु
	u32 value;

	mutex_lock(&padctl->lock);

	अगर (WARN_ON(padctl->enable == 0))
		जाओ out;

	अगर (--padctl->enable > 0)
		जाओ out;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value |= XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_VCORE_DOWN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value |= XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN_EARLY;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

	usleep_range(100, 200);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_ELPG_PROGRAM);
	value |= XUSB_PADCTL_ELPG_PROGRAM_AUX_MUX_LP0_CLAMP_EN;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_ELPG_PROGRAM);

out:
	mutex_unlock(&padctl->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_xusb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_padctl *padctl = phy_get_drvdata(phy);

	वापस tegra_xusb_padctl_enable(padctl);
पूर्ण

अटल पूर्णांक tegra_xusb_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_padctl *padctl = phy_get_drvdata(phy);

	वापस tegra_xusb_padctl_disable(padctl);
पूर्ण

अटल पूर्णांक pcie_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_padctl *padctl = phy_get_drvdata(phy);
	अचिन्हित दीर्घ समयout;
	पूर्णांक err = -ETIMEDOUT;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_P0_CTL1_REFCLK_SEL_MASK;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL2);
	value |= XUSB_PADCTL_IOPHY_PLL_P0_CTL2_REFCLKBUF_EN |
		 XUSB_PADCTL_IOPHY_PLL_P0_CTL2_TXCLKREF_EN |
		 XUSB_PADCTL_IOPHY_PLL_P0_CTL2_TXCLKREF_SEL;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_P0_CTL2);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);
	value |= XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL_RST;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);

	समयout = jअगरfies + msecs_to_jअगरfies(50);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);
		अगर (value & XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL0_LOCKDET) अणु
			err = 0;
			अवरोध;
		पूर्ण

		usleep_range(100, 200);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक pcie_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_padctl *padctl = phy_get_drvdata(phy);
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL_RST;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops pcie_phy_ops = अणु
	.init = tegra_xusb_phy_init,
	.निकास = tegra_xusb_phy_निकास,
	.घातer_on = pcie_phy_घातer_on,
	.घातer_off = pcie_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक sata_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_padctl *padctl = phy_get_drvdata(phy);
	अचिन्हित दीर्घ समयout;
	पूर्णांक err = -ETIMEDOUT;
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ_OVRD;
	value &= ~XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_PWR_OVRD;
	value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_IDDQ;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value |= XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_MODE;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value |= XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_RST;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	समयout = jअगरfies + msecs_to_jअगरfies(50);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
		अगर (value & XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_LOCKDET) अणु
			err = 0;
			अवरोध;
		पूर्ण

		usleep_range(100, 200);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक sata_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा tegra_xusb_padctl *padctl = phy_get_drvdata(phy);
	u32 value;

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_RST;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL1_MODE;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);
	value |= XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_PWR_OVRD;
	value |= XUSB_PADCTL_IOPHY_PLL_S0_CTL1_PLL_IDDQ;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_PLL_S0_CTL1);

	value = padctl_पढ़ोl(padctl, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);
	value |= ~XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ_OVRD;
	value |= ~XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1_IDDQ;
	padctl_ग_लिखोl(padctl, value, XUSB_PADCTL_IOPHY_MISC_PAD_S0_CTL1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops sata_phy_ops = अणु
	.init = tegra_xusb_phy_init,
	.निकास = tegra_xusb_phy_निकास,
	.घातer_on = sata_phy_घातer_on,
	.घातer_off = sata_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *tegra_xusb_padctl_xlate(काष्ठा device *dev,
					   काष्ठा of_phandle_args *args)
अणु
	काष्ठा tegra_xusb_padctl *padctl = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक index = args->args[0];

	अगर (args->args_count <= 0)
		वापस ERR_PTR(-EINVAL);

	अगर (index >= ARRAY_SIZE(padctl->phys))
		वापस ERR_PTR(-EINVAL);

	वापस padctl->phys[index];
पूर्ण

#घोषणा PIN_OTG_0   0
#घोषणा PIN_OTG_1   1
#घोषणा PIN_OTG_2   2
#घोषणा PIN_ULPI_0  3
#घोषणा PIN_HSIC_0  4
#घोषणा PIN_HSIC_1  5
#घोषणा PIN_PCIE_0  6
#घोषणा PIN_PCIE_1  7
#घोषणा PIN_PCIE_2  8
#घोषणा PIN_PCIE_3  9
#घोषणा PIN_PCIE_4 10
#घोषणा PIN_SATA_0 11

अटल स्थिर काष्ठा pinctrl_pin_desc tegra124_pins[] = अणु
	PINCTRL_PIN(PIN_OTG_0,  "otg-0"),
	PINCTRL_PIN(PIN_OTG_1,  "otg-1"),
	PINCTRL_PIN(PIN_OTG_2,  "otg-2"),
	PINCTRL_PIN(PIN_ULPI_0, "ulpi-0"),
	PINCTRL_PIN(PIN_HSIC_0, "hsic-0"),
	PINCTRL_PIN(PIN_HSIC_1, "hsic-1"),
	PINCTRL_PIN(PIN_PCIE_0, "pcie-0"),
	PINCTRL_PIN(PIN_PCIE_1, "pcie-1"),
	PINCTRL_PIN(PIN_PCIE_2, "pcie-2"),
	PINCTRL_PIN(PIN_PCIE_3, "pcie-3"),
	PINCTRL_PIN(PIN_PCIE_4, "pcie-4"),
	PINCTRL_PIN(PIN_SATA_0, "sata-0"),
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_snps_groups[] = अणु
	"otg-0",
	"otg-1",
	"otg-2",
	"ulpi-0",
	"hsic-0",
	"hsic-1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_xusb_groups[] = अणु
	"otg-0",
	"otg-1",
	"otg-2",
	"ulpi-0",
	"hsic-0",
	"hsic-1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_uart_groups[] = अणु
	"otg-0",
	"otg-1",
	"otg-2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_pcie_groups[] = अणु
	"pcie-0",
	"pcie-1",
	"pcie-2",
	"pcie-3",
	"pcie-4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_usb3_groups[] = अणु
	"pcie-0",
	"pcie-1",
	"sata-0",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_sata_groups[] = अणु
	"sata-0",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra124_rsvd_groups[] = अणु
	"otg-0",
	"otg-1",
	"otg-2",
	"pcie-0",
	"pcie-1",
	"pcie-2",
	"pcie-3",
	"pcie-4",
	"sata-0",
पूर्ण;

#घोषणा TEGRA124_FUNCTION(_name)					\
	अणु								\
		.name = #_name,						\
		.num_groups = ARRAY_SIZE(tegra124_##_name##_groups),	\
		.groups = tegra124_##_name##_groups,			\
	पूर्ण

अटल काष्ठा tegra_xusb_padctl_function tegra124_functions[] = अणु
	TEGRA124_FUNCTION(snps),
	TEGRA124_FUNCTION(xusb),
	TEGRA124_FUNCTION(uart),
	TEGRA124_FUNCTION(pcie),
	TEGRA124_FUNCTION(usb3),
	TEGRA124_FUNCTION(sata),
	TEGRA124_FUNCTION(rsvd),
पूर्ण;

क्रमागत tegra124_function अणु
	TEGRA124_FUNC_SNPS,
	TEGRA124_FUNC_XUSB,
	TEGRA124_FUNC_UART,
	TEGRA124_FUNC_PCIE,
	TEGRA124_FUNC_USB3,
	TEGRA124_FUNC_SATA,
	TEGRA124_FUNC_RSVD,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tegra124_otg_functions[] = अणु
	TEGRA124_FUNC_SNPS,
	TEGRA124_FUNC_XUSB,
	TEGRA124_FUNC_UART,
	TEGRA124_FUNC_RSVD,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tegra124_usb_functions[] = अणु
	TEGRA124_FUNC_SNPS,
	TEGRA124_FUNC_XUSB,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tegra124_pci_functions[] = अणु
	TEGRA124_FUNC_PCIE,
	TEGRA124_FUNC_USB3,
	TEGRA124_FUNC_SATA,
	TEGRA124_FUNC_RSVD,
पूर्ण;

#घोषणा TEGRA124_LANE(_name, _offset, _shअगरt, _mask, _iddq, _funcs)	\
	अणु								\
		.name = _name,						\
		.offset = _offset,					\
		.shअगरt = _shअगरt,					\
		.mask = _mask,						\
		.iddq = _iddq,						\
		.num_funcs = ARRAY_SIZE(tegra124_##_funcs##_functions),	\
		.funcs = tegra124_##_funcs##_functions,			\
	पूर्ण

अटल स्थिर काष्ठा tegra_xusb_padctl_lane tegra124_lanes[] = अणु
	TEGRA124_LANE("otg-0",  0x004,  0, 0x3, 0, otg),
	TEGRA124_LANE("otg-1",  0x004,  2, 0x3, 0, otg),
	TEGRA124_LANE("otg-2",  0x004,  4, 0x3, 0, otg),
	TEGRA124_LANE("ulpi-0", 0x004, 12, 0x1, 0, usb),
	TEGRA124_LANE("hsic-0", 0x004, 14, 0x1, 0, usb),
	TEGRA124_LANE("hsic-1", 0x004, 15, 0x1, 0, usb),
	TEGRA124_LANE("pcie-0", 0x134, 16, 0x3, 1, pci),
	TEGRA124_LANE("pcie-1", 0x134, 18, 0x3, 2, pci),
	TEGRA124_LANE("pcie-2", 0x134, 20, 0x3, 3, pci),
	TEGRA124_LANE("pcie-3", 0x134, 22, 0x3, 4, pci),
	TEGRA124_LANE("pcie-4", 0x134, 24, 0x3, 5, pci),
	TEGRA124_LANE("sata-0", 0x134, 26, 0x3, 6, pci),
पूर्ण;

अटल स्थिर काष्ठा tegra_xusb_padctl_soc tegra124_soc = अणु
	.num_pins = ARRAY_SIZE(tegra124_pins),
	.pins = tegra124_pins,
	.num_functions = ARRAY_SIZE(tegra124_functions),
	.functions = tegra124_functions,
	.num_lanes = ARRAY_SIZE(tegra124_lanes),
	.lanes = tegra124_lanes,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_xusb_padctl_of_match[] = अणु
	अणु .compatible = "nvidia,tegra124-xusb-padctl", .data = &tegra124_soc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_xusb_padctl_of_match);

/* predeclare these in order to silence sparse */
पूर्णांक tegra_xusb_padctl_legacy_probe(काष्ठा platक्रमm_device *pdev);
पूर्णांक tegra_xusb_padctl_legacy_हटाओ(काष्ठा platक्रमm_device *pdev);

पूर्णांक tegra_xusb_padctl_legacy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_xusb_padctl *padctl;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा phy *phy;
	पूर्णांक err;

	padctl = devm_kzalloc(&pdev->dev, माप(*padctl), GFP_KERNEL);
	अगर (!padctl)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, padctl);
	mutex_init(&padctl->lock);
	padctl->dev = &pdev->dev;

	/*
	 * Note that we can't replace this by of_device_get_match_data()
	 * because we need the separate matching table क्रम this legacy code on
	 * Tegra124. of_device_get_match_data() would attempt to use the table
	 * from the updated driver and fail.
	 */
	match = of_match_node(tegra_xusb_padctl_of_match, pdev->dev.of_node);
	padctl->soc = match->data;

	padctl->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(padctl->regs))
		वापस PTR_ERR(padctl->regs);

	padctl->rst = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(padctl->rst))
		वापस PTR_ERR(padctl->rst);

	err = reset_control_deनिश्चित(padctl->rst);
	अगर (err < 0)
		वापस err;

	स_रखो(&padctl->desc, 0, माप(padctl->desc));
	padctl->desc.name = dev_name(padctl->dev);
	padctl->desc.pins = tegra124_pins;
	padctl->desc.npins = ARRAY_SIZE(tegra124_pins);
	padctl->desc.pctlops = &tegra_xusb_padctl_pinctrl_ops;
	padctl->desc.pmxops = &tegra_xusb_padctl_pinmux_ops;
	padctl->desc.confops = &tegra_xusb_padctl_pinconf_ops;
	padctl->desc.owner = THIS_MODULE;

	padctl->pinctrl = devm_pinctrl_रेजिस्टर(&pdev->dev, &padctl->desc,
						padctl);
	अगर (IS_ERR(padctl->pinctrl)) अणु
		dev_err(&pdev->dev, "failed to register pincontrol\n");
		err = PTR_ERR(padctl->pinctrl);
		जाओ reset;
	पूर्ण

	phy = devm_phy_create(&pdev->dev, शून्य, &pcie_phy_ops);
	अगर (IS_ERR(phy)) अणु
		err = PTR_ERR(phy);
		जाओ reset;
	पूर्ण

	padctl->phys[TEGRA_XUSB_PADCTL_PCIE] = phy;
	phy_set_drvdata(phy, padctl);

	phy = devm_phy_create(&pdev->dev, शून्य, &sata_phy_ops);
	अगर (IS_ERR(phy)) अणु
		err = PTR_ERR(phy);
		जाओ reset;
	पूर्ण

	padctl->phys[TEGRA_XUSB_PADCTL_SATA] = phy;
	phy_set_drvdata(phy, padctl);

	padctl->provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev,
							 tegra_xusb_padctl_xlate);
	अगर (IS_ERR(padctl->provider)) अणु
		err = PTR_ERR(padctl->provider);
		dev_err(&pdev->dev, "failed to register PHYs: %d\n", err);
		जाओ reset;
	पूर्ण

	वापस 0;

reset:
	reset_control_निश्चित(padctl->rst);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_xusb_padctl_legacy_probe);

पूर्णांक tegra_xusb_padctl_legacy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_xusb_padctl *padctl = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	err = reset_control_निश्चित(padctl->rst);
	अगर (err < 0)
		dev_err(&pdev->dev, "failed to assert reset: %d\n", err);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_xusb_padctl_legacy_हटाओ);
