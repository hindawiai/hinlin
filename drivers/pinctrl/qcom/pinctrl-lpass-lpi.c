<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016-2019, The Linux Foundation. All rights reserved.
 * Copyright (c) 2020 Linaro Ltd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"

#घोषणा LPI_SLEW_RATE_CTL_REG		0xa000
#घोषणा LPI_TLMM_REG_OFFSET		0x1000
#घोषणा LPI_SLEW_RATE_MAX		0x03
#घोषणा LPI_SLEW_BITS_SIZE		0x02
#घोषणा LPI_SLEW_RATE_MASK		GENMASK(1, 0)
#घोषणा LPI_GPIO_CFG_REG		0x00
#घोषणा LPI_GPIO_PULL_MASK		GENMASK(1, 0)
#घोषणा LPI_GPIO_FUNCTION_MASK		GENMASK(5, 2)
#घोषणा LPI_GPIO_OUT_STRENGTH_MASK	GENMASK(8, 6)
#घोषणा LPI_GPIO_OE_MASK		BIT(9)
#घोषणा LPI_GPIO_VALUE_REG		0x04
#घोषणा LPI_GPIO_VALUE_IN_MASK		BIT(0)
#घोषणा LPI_GPIO_VALUE_OUT_MASK		BIT(1)

#घोषणा LPI_GPIO_BIAS_DISABLE		0x0
#घोषणा LPI_GPIO_PULL_DOWN		0x1
#घोषणा LPI_GPIO_KEEPER			0x2
#घोषणा LPI_GPIO_PULL_UP		0x3
#घोषणा LPI_GPIO_DS_TO_VAL(v)		(v / 2 - 1)
#घोषणा NO_SLEW				-1

#घोषणा LPI_FUNCTION(fname)			                \
	[LPI_MUX_##fname] = अणु		                \
		.name = #fname,				\
		.groups = fname##_groups,               \
		.ngroups = ARRAY_SIZE(fname##_groups),	\
	पूर्ण

#घोषणा LPI_PINGROUP(id, soff, f1, f2, f3, f4)		\
	अणु						\
		.name = "gpio" #id,			\
		.pins = gpio##id##_pins,		\
		.pin = id,				\
		.slew_offset = soff,			\
		.npins = ARRAY_SIZE(gpio##id##_pins),	\
		.funcs = (पूर्णांक[])अणु			\
			LPI_MUX_gpio,			\
			LPI_MUX_##f1,			\
			LPI_MUX_##f2,			\
			LPI_MUX_##f3,			\
			LPI_MUX_##f4,			\
		पूर्ण,					\
		.nfuncs = 5,				\
	पूर्ण

काष्ठा lpi_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक npins;
	अचिन्हित पूर्णांक pin;
	/* Bit offset in slew रेजिस्टर क्रम SoundWire pins only */
	पूर्णांक slew_offset;
	अचिन्हित पूर्णांक *funcs;
	अचिन्हित पूर्णांक nfuncs;
पूर्ण;

काष्ठा lpi_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित पूर्णांक ngroups;
पूर्ण;

काष्ठा lpi_pinctrl_variant_data अणु
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	पूर्णांक npins;
	स्थिर काष्ठा lpi_pingroup *groups;
	पूर्णांक ngroups;
	स्थिर काष्ठा lpi_function *functions;
	पूर्णांक nfunctions;
पूर्ण;

#घोषणा MAX_LPI_NUM_CLKS	2

काष्ठा lpi_pinctrl अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *ctrl;
	काष्ठा gpio_chip chip;
	काष्ठा pinctrl_desc desc;
	अक्षर __iomem *tlmm_base;
	अक्षर __iomem *slew_base;
	काष्ठा clk_bulk_data clks[MAX_LPI_NUM_CLKS];
	काष्ठा mutex slew_access_lock;
	स्थिर काष्ठा lpi_pinctrl_variant_data *data;
पूर्ण;

/* sm8250 variant specअगरic data */
अटल स्थिर काष्ठा pinctrl_pin_desc sm8250_lpi_pins[] = अणु
	PINCTRL_PIN(0, "gpio0"),
	PINCTRL_PIN(1, "gpio1"),
	PINCTRL_PIN(2, "gpio2"),
	PINCTRL_PIN(3, "gpio3"),
	PINCTRL_PIN(4, "gpio4"),
	PINCTRL_PIN(5, "gpio5"),
	PINCTRL_PIN(6, "gpio6"),
	PINCTRL_PIN(7, "gpio7"),
	PINCTRL_PIN(8, "gpio8"),
	PINCTRL_PIN(9, "gpio9"),
	PINCTRL_PIN(10, "gpio10"),
	PINCTRL_PIN(11, "gpio11"),
	PINCTRL_PIN(12, "gpio12"),
	PINCTRL_PIN(13, "gpio13"),
पूर्ण;

क्रमागत sm8250_lpi_functions अणु
	LPI_MUX_dmic1_clk,
	LPI_MUX_dmic1_data,
	LPI_MUX_dmic2_clk,
	LPI_MUX_dmic2_data,
	LPI_MUX_dmic3_clk,
	LPI_MUX_dmic3_data,
	LPI_MUX_i2s1_clk,
	LPI_MUX_i2s1_data,
	LPI_MUX_i2s1_ws,
	LPI_MUX_i2s2_clk,
	LPI_MUX_i2s2_data,
	LPI_MUX_i2s2_ws,
	LPI_MUX_qua_mi2s_data,
	LPI_MUX_qua_mi2s_sclk,
	LPI_MUX_qua_mi2s_ws,
	LPI_MUX_swr_rx_clk,
	LPI_MUX_swr_rx_data,
	LPI_MUX_swr_tx_clk,
	LPI_MUX_swr_tx_data,
	LPI_MUX_wsa_swr_clk,
	LPI_MUX_wsa_swr_data,
	LPI_MUX_gpio,
	LPI_MUX__,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक gpio0_pins[] = अणु 0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio1_pins[] = अणु 1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio2_pins[] = अणु 2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio3_pins[] = अणु 3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio4_pins[] = अणु 4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio5_pins[] = अणु 5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio6_pins[] = अणु 6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio7_pins[] = अणु 7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio8_pins[] = अणु 8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio9_pins[] = अणु 9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio10_pins[] = अणु 10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio11_pins[] = अणु 11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio12_pins[] = अणु 12 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gpio13_pins[] = अणु 13 पूर्ण;
अटल स्थिर अक्षर * स्थिर swr_tx_clk_groups[] = अणु "gpio0" पूर्ण;
अटल स्थिर अक्षर * स्थिर swr_tx_data_groups[] = अणु "gpio1", "gpio2", "gpio5" पूर्ण;
अटल स्थिर अक्षर * स्थिर swr_rx_clk_groups[] = अणु "gpio3" पूर्ण;
अटल स्थिर अक्षर * स्थिर swr_rx_data_groups[] = अणु "gpio4", "gpio5" पूर्ण;
अटल स्थिर अक्षर * स्थिर dmic1_clk_groups[] = अणु "gpio6" पूर्ण;
अटल स्थिर अक्षर * स्थिर dmic1_data_groups[] = अणु "gpio7" पूर्ण;
अटल स्थिर अक्षर * स्थिर dmic2_clk_groups[] = अणु "gpio8" पूर्ण;
अटल स्थिर अक्षर * स्थिर dmic2_data_groups[] = अणु "gpio9" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s2_clk_groups[] = अणु "gpio10" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s2_ws_groups[] = अणु "gpio11" पूर्ण;
अटल स्थिर अक्षर * स्थिर dmic3_clk_groups[] = अणु "gpio12" पूर्ण;
अटल स्थिर अक्षर * स्थिर dmic3_data_groups[] = अणु "gpio13" पूर्ण;
अटल स्थिर अक्षर * स्थिर qua_mi2s_sclk_groups[] = अणु "gpio0" पूर्ण;
अटल स्थिर अक्षर * स्थिर qua_mi2s_ws_groups[] = अणु "gpio1" पूर्ण;
अटल स्थिर अक्षर * स्थिर qua_mi2s_data_groups[] = अणु "gpio2", "gpio3", "gpio4" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s1_clk_groups[] = अणु "gpio6" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s1_ws_groups[] = अणु "gpio7" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s1_data_groups[] = अणु "gpio8", "gpio9" पूर्ण;
अटल स्थिर अक्षर * स्थिर wsa_swr_clk_groups[] = अणु "gpio10" पूर्ण;
अटल स्थिर अक्षर * स्थिर wsa_swr_data_groups[] = अणु "gpio11" पूर्ण;
अटल स्थिर अक्षर * स्थिर i2s2_data_groups[] = अणु "gpio12", "gpio12" पूर्ण;

अटल स्थिर काष्ठा lpi_pingroup sm8250_groups[] = अणु
	LPI_PINGROUP(0, 0, swr_tx_clk, qua_mi2s_sclk, _, _),
	LPI_PINGROUP(1, 2, swr_tx_data, qua_mi2s_ws, _, _),
	LPI_PINGROUP(2, 4, swr_tx_data, qua_mi2s_data, _, _),
	LPI_PINGROUP(3, 8, swr_rx_clk, qua_mi2s_data, _, _),
	LPI_PINGROUP(4, 10, swr_rx_data, qua_mi2s_data, _, _),
	LPI_PINGROUP(5, 12, swr_tx_data, swr_rx_data, _, _),
	LPI_PINGROUP(6, NO_SLEW, dmic1_clk, i2s1_clk, _,  _),
	LPI_PINGROUP(7, NO_SLEW, dmic1_data, i2s1_ws, _, _),
	LPI_PINGROUP(8, NO_SLEW, dmic2_clk, i2s1_data, _, _),
	LPI_PINGROUP(9, NO_SLEW, dmic2_data, i2s1_data, _, _),
	LPI_PINGROUP(10, 16, i2s2_clk, wsa_swr_clk, _, _),
	LPI_PINGROUP(11, 18, i2s2_ws, wsa_swr_data, _, _),
	LPI_PINGROUP(12, NO_SLEW, dmic3_clk, i2s2_data, _, _),
	LPI_PINGROUP(13, NO_SLEW, dmic3_data, i2s2_data, _, _),
पूर्ण;

अटल स्थिर काष्ठा lpi_function sm8250_functions[] = अणु
	LPI_FUNCTION(dmic1_clk),
	LPI_FUNCTION(dmic1_data),
	LPI_FUNCTION(dmic2_clk),
	LPI_FUNCTION(dmic2_data),
	LPI_FUNCTION(dmic3_clk),
	LPI_FUNCTION(dmic3_data),
	LPI_FUNCTION(i2s1_clk),
	LPI_FUNCTION(i2s1_data),
	LPI_FUNCTION(i2s1_ws),
	LPI_FUNCTION(i2s2_clk),
	LPI_FUNCTION(i2s2_data),
	LPI_FUNCTION(i2s2_ws),
	LPI_FUNCTION(qua_mi2s_data),
	LPI_FUNCTION(qua_mi2s_sclk),
	LPI_FUNCTION(qua_mi2s_ws),
	LPI_FUNCTION(swr_rx_clk),
	LPI_FUNCTION(swr_rx_data),
	LPI_FUNCTION(swr_tx_clk),
	LPI_FUNCTION(swr_tx_data),
	LPI_FUNCTION(wsa_swr_clk),
	LPI_FUNCTION(wsa_swr_data),
पूर्ण;

अटल काष्ठा lpi_pinctrl_variant_data sm8250_lpi_data = अणु
	.pins = sm8250_lpi_pins,
	.npins = ARRAY_SIZE(sm8250_lpi_pins),
	.groups = sm8250_groups,
	.ngroups = ARRAY_SIZE(sm8250_groups),
	.functions = sm8250_functions,
	.nfunctions = ARRAY_SIZE(sm8250_functions),
पूर्ण;

अटल पूर्णांक lpi_gpio_पढ़ो(काष्ठा lpi_pinctrl *state, अचिन्हित पूर्णांक pin,
			 अचिन्हित पूर्णांक addr)
अणु
	वापस ioपढ़ो32(state->tlmm_base + LPI_TLMM_REG_OFFSET * pin + addr);
पूर्ण

अटल पूर्णांक lpi_gpio_ग_लिखो(काष्ठा lpi_pinctrl *state, अचिन्हित पूर्णांक pin,
			  अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक val)
अणु
	ioग_लिखो32(val, state->tlmm_base + LPI_TLMM_REG_OFFSET * pin + addr);

	वापस 0;
पूर्ण

अटल पूर्णांक lpi_gpio_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा lpi_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->data->ngroups;
पूर्ण

अटल स्थिर अक्षर *lpi_gpio_get_group_name(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक group)
अणु
	काष्ठा lpi_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->data->groups[group].name;
पूर्ण

अटल पूर्णांक lpi_gpio_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक group,
				   स्थिर अचिन्हित पूर्णांक **pins,
				   अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा lpi_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*pins = pctrl->data->groups[group].pins;
	*num_pins = pctrl->data->groups[group].npins;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops lpi_gpio_pinctrl_ops = अणु
	.get_groups_count	= lpi_gpio_get_groups_count,
	.get_group_name		= lpi_gpio_get_group_name,
	.get_group_pins		= lpi_gpio_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक lpi_gpio_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा lpi_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->data->nfunctions;
पूर्ण

अटल स्थिर अक्षर *lpi_gpio_get_function_name(काष्ठा pinctrl_dev *pctldev,
					      अचिन्हित पूर्णांक function)
अणु
	काष्ठा lpi_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->data->functions[function].name;
पूर्ण

अटल पूर्णांक lpi_gpio_get_function_groups(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक function,
					स्थिर अक्षर *स्थिर **groups,
					अचिन्हित *स्थिर num_qgroups)
अणु
	काष्ठा lpi_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctrl->data->functions[function].groups;
	*num_qgroups = pctrl->data->functions[function].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक lpi_gpio_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक function,
			    अचिन्हित पूर्णांक group_num)
अणु
	काष्ठा lpi_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा lpi_pingroup *g = &pctrl->data->groups[group_num];
	u32 val;
	पूर्णांक i, pin = g->pin;

	क्रम (i = 0; i < g->nfuncs; i++) अणु
		अगर (g->funcs[i] == function)
			अवरोध;
	पूर्ण

	अगर (WARN_ON(i == g->nfuncs))
		वापस -EINVAL;

	val = lpi_gpio_पढ़ो(pctrl, pin, LPI_GPIO_CFG_REG);
	u32p_replace_bits(&val, i, LPI_GPIO_FUNCTION_MASK);
	lpi_gpio_ग_लिखो(pctrl, pin, LPI_GPIO_CFG_REG, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops lpi_gpio_pinmux_ops = अणु
	.get_functions_count	= lpi_gpio_get_functions_count,
	.get_function_name	= lpi_gpio_get_function_name,
	.get_function_groups	= lpi_gpio_get_function_groups,
	.set_mux		= lpi_gpio_set_mux,
पूर्ण;

अटल पूर्णांक lpi_config_get(काष्ठा pinctrl_dev *pctldev,
			  अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	अचिन्हित पूर्णांक param = pinconf_to_config_param(*config);
	काष्ठा lpi_pinctrl *state = dev_get_drvdata(pctldev->dev);
	अचिन्हित पूर्णांक arg = 0;
	पूर्णांक is_out;
	पूर्णांक pull;
	u32 ctl_reg;

	ctl_reg = lpi_gpio_पढ़ो(state, pin, LPI_GPIO_CFG_REG);
	is_out = ctl_reg & LPI_GPIO_OE_MASK;
	pull = FIELD_GET(LPI_GPIO_PULL_MASK, ctl_reg);

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (pull == LPI_GPIO_BIAS_DISABLE)
			arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (pull == LPI_GPIO_PULL_DOWN)
			arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_BUS_HOLD:
		अगर (pull == LPI_GPIO_KEEPER)
			arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (pull == LPI_GPIO_PULL_UP)
			arg = 1;
		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
	हाल PIN_CONFIG_OUTPUT:
		अगर (is_out)
			arg = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);
	वापस 0;
पूर्ण

अटल पूर्णांक lpi_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक group,
			  अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक nconfs)
अणु
	काष्ठा lpi_pinctrl *pctrl = dev_get_drvdata(pctldev->dev);
	अचिन्हित पूर्णांक param, arg, pullup = LPI_GPIO_BIAS_DISABLE, strength = 2;
	bool value, output_enabled = false;
	स्थिर काष्ठा lpi_pingroup *g;
	अचिन्हित दीर्घ sval;
	पूर्णांक i, slew_offset;
	u32 val;

	g = &pctrl->data->groups[group];
	क्रम (i = 0; i < nconfs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			pullup = LPI_GPIO_BIAS_DISABLE;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			pullup = LPI_GPIO_PULL_DOWN;
			अवरोध;
		हाल PIN_CONFIG_BIAS_BUS_HOLD:
			pullup = LPI_GPIO_KEEPER;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			pullup = LPI_GPIO_PULL_UP;
			अवरोध;
		हाल PIN_CONFIG_INPUT_ENABLE:
			output_enabled = false;
			अवरोध;
		हाल PIN_CONFIG_OUTPUT:
			output_enabled = true;
			value = arg;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			strength = arg;
			अवरोध;
		हाल PIN_CONFIG_SLEW_RATE:
			अगर (arg > LPI_SLEW_RATE_MAX) अणु
				dev_err(pctldev->dev, "invalid slew rate %u for pin: %d\n",
					arg, group);
				वापस -EINVAL;
			पूर्ण

			slew_offset = g->slew_offset;
			अगर (slew_offset == NO_SLEW)
				अवरोध;

			mutex_lock(&pctrl->slew_access_lock);

			sval = ioपढ़ो32(pctrl->slew_base + LPI_SLEW_RATE_CTL_REG);
			sval &= ~(LPI_SLEW_RATE_MASK << slew_offset);
			sval |= arg << slew_offset;
			ioग_लिखो32(sval, pctrl->slew_base + LPI_SLEW_RATE_CTL_REG);

			mutex_unlock(&pctrl->slew_access_lock);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	val = lpi_gpio_पढ़ो(pctrl, group, LPI_GPIO_CFG_REG);

	u32p_replace_bits(&val, pullup, LPI_GPIO_PULL_MASK);
	u32p_replace_bits(&val, LPI_GPIO_DS_TO_VAL(strength),
			  LPI_GPIO_OUT_STRENGTH_MASK);
	u32p_replace_bits(&val, output_enabled, LPI_GPIO_OE_MASK);

	lpi_gpio_ग_लिखो(pctrl, group, LPI_GPIO_CFG_REG, val);

	अगर (output_enabled) अणु
		val = u32_encode_bits(value ? 1 : 0, LPI_GPIO_VALUE_OUT_MASK);
		lpi_gpio_ग_लिखो(pctrl, group, LPI_GPIO_VALUE_REG, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops lpi_gpio_pinconf_ops = अणु
	.is_generic			= true,
	.pin_config_group_get		= lpi_config_get,
	.pin_config_group_set		= lpi_config_set,
पूर्ण;

अटल पूर्णांक lpi_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा lpi_pinctrl *state = gpiochip_get_data(chip);
	अचिन्हित दीर्घ config;

	config = pinconf_to_config_packed(PIN_CONFIG_INPUT_ENABLE, 1);

	वापस lpi_config_set(state->ctrl, pin, &config, 1);
पूर्ण

अटल पूर्णांक lpi_gpio_direction_output(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक pin, पूर्णांक val)
अणु
	काष्ठा lpi_pinctrl *state = gpiochip_get_data(chip);
	अचिन्हित दीर्घ config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, val);

	वापस lpi_config_set(state->ctrl, pin, &config, 1);
पूर्ण

अटल पूर्णांक lpi_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा lpi_pinctrl *state = gpiochip_get_data(chip);

	वापस lpi_gpio_पढ़ो(state, pin, LPI_GPIO_VALUE_REG) &
		LPI_GPIO_VALUE_IN_MASK;
पूर्ण

अटल व्योम lpi_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक pin, पूर्णांक value)
अणु
	काष्ठा lpi_pinctrl *state = gpiochip_get_data(chip);
	अचिन्हित दीर्घ config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, value);

	lpi_config_set(state->ctrl, pin, &config, 1);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/seq_file.h>

अटल अचिन्हित पूर्णांक lpi_regval_to_drive(u32 val)
अणु
	वापस (val + 1) * 2;
पूर्ण

अटल व्योम lpi_gpio_dbg_show_one(काष्ठा seq_file *s,
				  काष्ठा pinctrl_dev *pctldev,
				  काष्ठा gpio_chip *chip,
				  अचिन्हित पूर्णांक offset,
				  अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा lpi_pinctrl *state = gpiochip_get_data(chip);
	काष्ठा pinctrl_pin_desc pindesc;
	अचिन्हित पूर्णांक func;
	पूर्णांक is_out;
	पूर्णांक drive;
	पूर्णांक pull;
	u32 ctl_reg;

	अटल स्थिर अक्षर * स्थिर pulls[] = अणु
		"no pull",
		"pull down",
		"keeper",
		"pull up"
	पूर्ण;

	pctldev = pctldev ? : state->ctrl;
	pindesc = pctldev->desc->pins[offset];
	ctl_reg = lpi_gpio_पढ़ो(state, offset, LPI_GPIO_CFG_REG);
	is_out = ctl_reg & LPI_GPIO_OE_MASK;

	func = FIELD_GET(LPI_GPIO_FUNCTION_MASK, ctl_reg);
	drive = FIELD_GET(LPI_GPIO_OUT_STRENGTH_MASK, ctl_reg);
	pull = FIELD_GET(LPI_GPIO_PULL_MASK, ctl_reg);

	seq_म_लिखो(s, " %-8s: %-3s %d", pindesc.name, is_out ? "out" : "in", func);
	seq_म_लिखो(s, " %dmA", lpi_regval_to_drive(drive));
	seq_म_लिखो(s, " %s", pulls[pull]);
पूर्ण

अटल व्योम lpi_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	अचिन्हित पूर्णांक gpio = chip->base;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < chip->ngpio; i++, gpio++) अणु
		lpi_gpio_dbg_show_one(s, शून्य, chip, i, gpio);
		seq_माला_दो(s, "\n");
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा lpi_gpio_dbg_show शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा gpio_chip lpi_gpio_ढाँचा = अणु
	.direction_input	= lpi_gpio_direction_input,
	.direction_output	= lpi_gpio_direction_output,
	.get			= lpi_gpio_get,
	.set			= lpi_gpio_set,
	.request		= gpiochip_generic_request,
	.मुक्त			= gpiochip_generic_मुक्त,
	.dbg_show		= lpi_gpio_dbg_show,
पूर्ण;

अटल पूर्णांक lpi_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा lpi_pinctrl_variant_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा lpi_pinctrl *pctrl;
	पूर्णांक ret;

	pctrl = devm_kzalloc(dev, माप(*pctrl), GFP_KERNEL);
	अगर (!pctrl)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pctrl);

	data = of_device_get_match_data(dev);
	अगर (!data)
		वापस -EINVAL;

	pctrl->data = data;
	pctrl->dev = &pdev->dev;

	pctrl->clks[0].id = "core";
	pctrl->clks[1].id = "audio";

	pctrl->tlmm_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pctrl->tlmm_base))
		वापस dev_err_probe(dev, PTR_ERR(pctrl->tlmm_base),
				     "TLMM resource not provided\n");

	pctrl->slew_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(pctrl->slew_base))
		वापस dev_err_probe(dev, PTR_ERR(pctrl->slew_base),
				     "Slew resource not provided\n");

	ret = devm_clk_bulk_get(dev, MAX_LPI_NUM_CLKS, pctrl->clks);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "Can't get clocks\n");

	ret = clk_bulk_prepare_enable(MAX_LPI_NUM_CLKS, pctrl->clks);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "Can't enable clocks\n");

	pctrl->desc.pctlops = &lpi_gpio_pinctrl_ops;
	pctrl->desc.pmxops = &lpi_gpio_pinmux_ops;
	pctrl->desc.confops = &lpi_gpio_pinconf_ops;
	pctrl->desc.owner = THIS_MODULE;
	pctrl->desc.name = dev_name(dev);
	pctrl->desc.pins = data->pins;
	pctrl->desc.npins = data->npins;
	pctrl->chip = lpi_gpio_ढाँचा;
	pctrl->chip.parent = dev;
	pctrl->chip.base = -1;
	pctrl->chip.ngpio = data->npins;
	pctrl->chip.label = dev_name(dev);
	pctrl->chip.of_gpio_n_cells = 2;
	pctrl->chip.can_sleep = false;

	mutex_init(&pctrl->slew_access_lock);

	pctrl->ctrl = devm_pinctrl_रेजिस्टर(dev, &pctrl->desc, pctrl);
	अगर (IS_ERR(pctrl->ctrl)) अणु
		ret = PTR_ERR(pctrl->ctrl);
		dev_err(dev, "failed to add pin controller\n");
		जाओ err_pinctrl;
	पूर्ण

	ret = devm_gpiochip_add_data(dev, &pctrl->chip, pctrl);
	अगर (ret) अणु
		dev_err(pctrl->dev, "can't add gpio chip\n");
		जाओ err_pinctrl;
	पूर्ण

	वापस 0;

err_pinctrl:
	mutex_destroy(&pctrl->slew_access_lock);
	clk_bulk_disable_unprepare(MAX_LPI_NUM_CLKS, pctrl->clks);

	वापस ret;
पूर्ण

अटल पूर्णांक lpi_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpi_pinctrl *pctrl = platक्रमm_get_drvdata(pdev);

	mutex_destroy(&pctrl->slew_access_lock);
	clk_bulk_disable_unprepare(MAX_LPI_NUM_CLKS, pctrl->clks);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpi_pinctrl_of_match[] = अणु
	अणु
	       .compatible = "qcom,sm8250-lpass-lpi-pinctrl",
	       .data = &sm8250_lpi_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpi_pinctrl_of_match);

अटल काष्ठा platक्रमm_driver lpi_pinctrl_driver = अणु
	.driver = अणु
		   .name = "qcom-lpass-lpi-pinctrl",
		   .of_match_table = lpi_pinctrl_of_match,
	पूर्ण,
	.probe = lpi_pinctrl_probe,
	.हटाओ = lpi_pinctrl_हटाओ,
पूर्ण;

module_platक्रमm_driver(lpi_pinctrl_driver);
MODULE_DESCRIPTION("QTI LPI GPIO pin control driver");
MODULE_LICENSE("GPL");
