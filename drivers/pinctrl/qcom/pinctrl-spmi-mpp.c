<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <dt-bindings/pinctrl/qcom,pmic-mpp.h>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"

#घोषणा PMIC_MPP_ADDRESS_RANGE			0x100

/*
 * Pull Up Values - it indicates whether a pull-up should be
 * applied क्रम bidirectional mode only. The hardware ignores the
 * configuration when operating in other modes.
 */
#घोषणा PMIC_MPP_PULL_UP_0P6KOHM		0
#घोषणा PMIC_MPP_PULL_UP_10KOHM			1
#घोषणा PMIC_MPP_PULL_UP_30KOHM			2
#घोषणा PMIC_MPP_PULL_UP_OPEN			3

/* type रेजिस्टरs base address bases */
#घोषणा PMIC_MPP_REG_TYPE			0x4
#घोषणा PMIC_MPP_REG_SUBTYPE			0x5

/* mpp peripheral type and subtype values */
#घोषणा PMIC_MPP_TYPE				0x11
#घोषणा PMIC_MPP_SUBTYPE_4CH_NO_ANA_OUT		0x3
#घोषणा PMIC_MPP_SUBTYPE_ULT_4CH_NO_ANA_OUT	0x4
#घोषणा PMIC_MPP_SUBTYPE_4CH_NO_SINK		0x5
#घोषणा PMIC_MPP_SUBTYPE_ULT_4CH_NO_SINK	0x6
#घोषणा PMIC_MPP_SUBTYPE_4CH_FULL_FUNC		0x7
#घोषणा PMIC_MPP_SUBTYPE_8CH_FULL_FUNC		0xf

#घोषणा PMIC_MPP_REG_RT_STS			0x10
#घोषणा PMIC_MPP_REG_RT_STS_VAL_MASK		0x1

/* control रेजिस्टर base address bases */
#घोषणा PMIC_MPP_REG_MODE_CTL			0x40
#घोषणा PMIC_MPP_REG_DIG_VIN_CTL		0x41
#घोषणा PMIC_MPP_REG_DIG_PULL_CTL		0x42
#घोषणा PMIC_MPP_REG_DIG_IN_CTL			0x43
#घोषणा PMIC_MPP_REG_EN_CTL			0x46
#घोषणा PMIC_MPP_REG_AOUT_CTL			0x48
#घोषणा PMIC_MPP_REG_AIN_CTL			0x4a
#घोषणा PMIC_MPP_REG_SINK_CTL			0x4c

/* PMIC_MPP_REG_MODE_CTL */
#घोषणा PMIC_MPP_REG_MODE_VALUE_MASK		0x1
#घोषणा PMIC_MPP_REG_MODE_FUNCTION_SHIFT	1
#घोषणा PMIC_MPP_REG_MODE_FUNCTION_MASK		0x7
#घोषणा PMIC_MPP_REG_MODE_सूची_SHIFT		4
#घोषणा PMIC_MPP_REG_MODE_सूची_MASK		0x7

/* PMIC_MPP_REG_DIG_VIN_CTL */
#घोषणा PMIC_MPP_REG_VIN_SHIFT			0
#घोषणा PMIC_MPP_REG_VIN_MASK			0x7

/* PMIC_MPP_REG_DIG_PULL_CTL */
#घोषणा PMIC_MPP_REG_PULL_SHIFT			0
#घोषणा PMIC_MPP_REG_PULL_MASK			0x7

/* PMIC_MPP_REG_EN_CTL */
#घोषणा PMIC_MPP_REG_MASTER_EN_SHIFT		7

/* PMIC_MPP_REG_AIN_CTL */
#घोषणा PMIC_MPP_REG_AIN_ROUTE_SHIFT		0
#घोषणा PMIC_MPP_REG_AIN_ROUTE_MASK		0x7

#घोषणा PMIC_MPP_MODE_DIGITAL_INPUT		0
#घोषणा PMIC_MPP_MODE_DIGITAL_OUTPUT		1
#घोषणा PMIC_MPP_MODE_DIGITAL_BIसूची		2
#घोषणा PMIC_MPP_MODE_ANALOG_BIसूची		3
#घोषणा PMIC_MPP_MODE_ANALOG_INPUT		4
#घोषणा PMIC_MPP_MODE_ANALOG_OUTPUT		5
#घोषणा PMIC_MPP_MODE_CURRENT_SINK		6

#घोषणा PMIC_MPP_SELECTOR_NORMAL		0
#घोषणा PMIC_MPP_SELECTOR_PAIRED		1
#घोषणा PMIC_MPP_SELECTOR_DTEST_FIRST		4

#घोषणा PMIC_MPP_PHYSICAL_OFFSET		1

/* Qualcomm specअगरic pin configurations */
#घोषणा PMIC_MPP_CONF_AMUX_ROUTE		(PIN_CONFIG_END + 1)
#घोषणा PMIC_MPP_CONF_ANALOG_LEVEL		(PIN_CONFIG_END + 2)
#घोषणा PMIC_MPP_CONF_DTEST_SELECTOR		(PIN_CONFIG_END + 3)
#घोषणा PMIC_MPP_CONF_PAIRED			(PIN_CONFIG_END + 4)

/**
 * काष्ठा pmic_mpp_pad - keep current MPP settings
 * @base: Address base in SPMI device.
 * @irq: IRQ number which this MPP generate.
 * @is_enabled: Set to false when MPP should be put in high Z state.
 * @out_value: Cached pin output value.
 * @output_enabled: Set to true अगर MPP output logic is enabled.
 * @input_enabled: Set to true अगर MPP input buffer logic is enabled.
 * @paired: Pin operates in paired mode
 * @has_pullup: Pin has support to configure pullup
 * @num_sources: Number of घातer-sources supported by this MPP.
 * @घातer_source: Current घातer-source used.
 * @amux_input: Set the source क्रम analog input.
 * @aout_level: Analog output level
 * @pullup: Pullup resistor value. Valid in Bidirectional mode only.
 * @function: See pmic_mpp_functions[].
 * @drive_strength: Amount of current in sink mode
 * @dtest: DTEST route selector
 */
काष्ठा pmic_mpp_pad अणु
	u16		base;
	पूर्णांक		irq;
	bool		is_enabled;
	bool		out_value;
	bool		output_enabled;
	bool		input_enabled;
	bool		paired;
	bool		has_pullup;
	अचिन्हित पूर्णांक	num_sources;
	अचिन्हित पूर्णांक	घातer_source;
	अचिन्हित पूर्णांक	amux_input;
	अचिन्हित पूर्णांक	aout_level;
	अचिन्हित पूर्णांक	pullup;
	अचिन्हित पूर्णांक	function;
	अचिन्हित पूर्णांक	drive_strength;
	अचिन्हित पूर्णांक	dtest;
पूर्ण;

काष्ठा pmic_mpp_state अणु
	काष्ठा device	*dev;
	काष्ठा regmap	*map;
	काष्ठा pinctrl_dev *ctrl;
	काष्ठा gpio_chip chip;
पूर्ण;

अटल स्थिर काष्ठा pinconf_generic_params pmic_mpp_bindings[] = अणु
	अणु"qcom,amux-route",	PMIC_MPP_CONF_AMUX_ROUTE,	0पूर्ण,
	अणु"qcom,analog-level",	PMIC_MPP_CONF_ANALOG_LEVEL,	0पूर्ण,
	अणु"qcom,dtest",		PMIC_MPP_CONF_DTEST_SELECTOR,	0पूर्ण,
	अणु"qcom,paired",		PMIC_MPP_CONF_PAIRED,		0पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर काष्ठा pin_config_item pmic_conf_items[] = अणु
	PCONFDUMP(PMIC_MPP_CONF_AMUX_ROUTE, "analog mux", शून्य, true),
	PCONFDUMP(PMIC_MPP_CONF_ANALOG_LEVEL, "analog level", शून्य, true),
	PCONFDUMP(PMIC_MPP_CONF_DTEST_SELECTOR, "dtest", शून्य, true),
	PCONFDUMP(PMIC_MPP_CONF_PAIRED, "paired", शून्य, false),
पूर्ण;
#पूर्ण_अगर

अटल स्थिर अक्षर *स्थिर pmic_mpp_groups[] = अणु
	"mpp1", "mpp2", "mpp3", "mpp4", "mpp5", "mpp6", "mpp7", "mpp8",
पूर्ण;

#घोषणा PMIC_MPP_DIGITAL	0
#घोषणा PMIC_MPP_ANALOG		1
#घोषणा PMIC_MPP_SINK		2

अटल स्थिर अक्षर *स्थिर pmic_mpp_functions[] = अणु
	"digital", "analog", "sink"
पूर्ण;

अटल पूर्णांक pmic_mpp_पढ़ो(काष्ठा pmic_mpp_state *state,
			 काष्ठा pmic_mpp_pad *pad, अचिन्हित पूर्णांक addr)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(state->map, pad->base + addr, &val);
	अगर (ret < 0)
		dev_err(state->dev, "read 0x%x failed\n", addr);
	अन्यथा
		ret = val;

	वापस ret;
पूर्ण

अटल पूर्णांक pmic_mpp_ग_लिखो(काष्ठा pmic_mpp_state *state,
			  काष्ठा pmic_mpp_pad *pad, अचिन्हित पूर्णांक addr,
			  अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(state->map, pad->base + addr, val);
	अगर (ret < 0)
		dev_err(state->dev, "write 0x%x failed\n", addr);

	वापस ret;
पूर्ण

अटल पूर्णांक pmic_mpp_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	/* Every PIN is a group */
	वापस pctldev->desc->npins;
पूर्ण

अटल स्थिर अक्षर *pmic_mpp_get_group_name(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित pin)
अणु
	वापस pctldev->desc->pins[pin].name;
पूर्ण

अटल पूर्णांक pmic_mpp_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित pin,
				   स्थिर अचिन्हित **pins, अचिन्हित *num_pins)
अणु
	*pins = &pctldev->desc->pins[pin].number;
	*num_pins = 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops pmic_mpp_pinctrl_ops = अणु
	.get_groups_count	= pmic_mpp_get_groups_count,
	.get_group_name		= pmic_mpp_get_group_name,
	.get_group_pins		= pmic_mpp_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक pmic_mpp_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(pmic_mpp_functions);
पूर्ण

अटल स्थिर अक्षर *pmic_mpp_get_function_name(काष्ठा pinctrl_dev *pctldev,
					      अचिन्हित function)
अणु
	वापस pmic_mpp_functions[function];
पूर्ण

अटल पूर्णांक pmic_mpp_get_function_groups(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित function,
					स्थिर अक्षर *स्थिर **groups,
					अचिन्हित *स्थिर num_qgroups)
अणु
	*groups = pmic_mpp_groups;
	*num_qgroups = pctldev->desc->npins;
	वापस 0;
पूर्ण

अटल पूर्णांक pmic_mpp_ग_लिखो_mode_ctl(काष्ठा pmic_mpp_state *state,
				   काष्ठा pmic_mpp_pad *pad)
अणु
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक sel;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक en;

	चयन (pad->function) अणु
	हाल PMIC_MPP_ANALOG:
		अगर (pad->input_enabled && pad->output_enabled)
			mode = PMIC_MPP_MODE_ANALOG_BIसूची;
		अन्यथा अगर (pad->input_enabled)
			mode = PMIC_MPP_MODE_ANALOG_INPUT;
		अन्यथा
			mode = PMIC_MPP_MODE_ANALOG_OUTPUT;
		अवरोध;
	हाल PMIC_MPP_DIGITAL:
		अगर (pad->input_enabled && pad->output_enabled)
			mode = PMIC_MPP_MODE_DIGITAL_BIसूची;
		अन्यथा अगर (pad->input_enabled)
			mode = PMIC_MPP_MODE_DIGITAL_INPUT;
		अन्यथा
			mode = PMIC_MPP_MODE_DIGITAL_OUTPUT;
		अवरोध;
	हाल PMIC_MPP_SINK:
	शेष:
		mode = PMIC_MPP_MODE_CURRENT_SINK;
		अवरोध;
	पूर्ण

	अगर (pad->dtest)
		sel = PMIC_MPP_SELECTOR_DTEST_FIRST + pad->dtest - 1;
	अन्यथा अगर (pad->paired)
		sel = PMIC_MPP_SELECTOR_PAIRED;
	अन्यथा
		sel = PMIC_MPP_SELECTOR_NORMAL;

	en = !!pad->out_value;

	val = mode << PMIC_MPP_REG_MODE_सूची_SHIFT |
	      sel << PMIC_MPP_REG_MODE_FUNCTION_SHIFT |
	      en;

	वापस pmic_mpp_ग_लिखो(state, pad, PMIC_MPP_REG_MODE_CTL, val);
पूर्ण

अटल पूर्णांक pmic_mpp_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित function,
				अचिन्हित pin)
अणु
	काष्ठा pmic_mpp_state *state = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pmic_mpp_pad *pad;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	pad = pctldev->desc->pins[pin].drv_data;

	pad->function = function;

	ret = pmic_mpp_ग_लिखो_mode_ctl(state, pad);
	अगर (ret < 0)
		वापस ret;

	val = pad->is_enabled << PMIC_MPP_REG_MASTER_EN_SHIFT;

	वापस pmic_mpp_ग_लिखो(state, pad, PMIC_MPP_REG_EN_CTL, val);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops pmic_mpp_pinmux_ops = अणु
	.get_functions_count	= pmic_mpp_get_functions_count,
	.get_function_name	= pmic_mpp_get_function_name,
	.get_function_groups	= pmic_mpp_get_function_groups,
	.set_mux		= pmic_mpp_set_mux,
पूर्ण;

अटल पूर्णांक pmic_mpp_config_get(काष्ठा pinctrl_dev *pctldev,
			       अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	अचिन्हित param = pinconf_to_config_param(*config);
	काष्ठा pmic_mpp_pad *pad;
	अचिन्हित arg = 0;

	pad = pctldev->desc->pins[pin].drv_data;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (pad->pullup != PMIC_MPP_PULL_UP_OPEN)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		चयन (pad->pullup) अणु
		हाल PMIC_MPP_PULL_UP_0P6KOHM:
			arg = 600;
			अवरोध;
		हाल PMIC_MPP_PULL_UP_10KOHM:
			arg = 10000;
			अवरोध;
		हाल PMIC_MPP_PULL_UP_30KOHM:
			arg = 30000;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		अगर (pad->is_enabled)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_POWER_SOURCE:
		arg = pad->घातer_source;
		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
		अगर (!pad->input_enabled)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		arg = pad->out_value;
		अवरोध;
	हाल PMIC_MPP_CONF_DTEST_SELECTOR:
		arg = pad->dtest;
		अवरोध;
	हाल PMIC_MPP_CONF_AMUX_ROUTE:
		arg = pad->amux_input;
		अवरोध;
	हाल PMIC_MPP_CONF_PAIRED:
		अगर (!pad->paired)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		arg = pad->drive_strength;
		अवरोध;
	हाल PMIC_MPP_CONF_ANALOG_LEVEL:
		arg = pad->aout_level;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Convert रेजिस्टर value to pinconf value */
	*config = pinconf_to_config_packed(param, arg);
	वापस 0;
पूर्ण

अटल पूर्णांक pmic_mpp_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			       अचिन्हित दीर्घ *configs, अचिन्हित nconfs)
अणु
	काष्ठा pmic_mpp_state *state = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pmic_mpp_pad *pad;
	अचिन्हित param, arg;
	अचिन्हित पूर्णांक val;
	पूर्णांक i, ret;

	pad = pctldev->desc->pins[pin].drv_data;

	/* Make it possible to enable the pin, by not setting high impedance */
	pad->is_enabled = true;

	क्रम (i = 0; i < nconfs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			pad->pullup = PMIC_MPP_PULL_UP_OPEN;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			चयन (arg) अणु
			हाल 600:
				pad->pullup = PMIC_MPP_PULL_UP_0P6KOHM;
				अवरोध;
			हाल 10000:
				pad->pullup = PMIC_MPP_PULL_UP_10KOHM;
				अवरोध;
			हाल 30000:
				pad->pullup = PMIC_MPP_PULL_UP_30KOHM;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			pad->is_enabled = false;
			अवरोध;
		हाल PIN_CONFIG_POWER_SOURCE:
			अगर (arg >= pad->num_sources)
				वापस -EINVAL;
			pad->घातer_source = arg;
			अवरोध;
		हाल PIN_CONFIG_INPUT_ENABLE:
			pad->input_enabled = arg ? true : false;
			अवरोध;
		हाल PIN_CONFIG_OUTPUT:
			pad->output_enabled = true;
			pad->out_value = arg;
			अवरोध;
		हाल PMIC_MPP_CONF_DTEST_SELECTOR:
			pad->dtest = arg;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			pad->drive_strength = arg;
			अवरोध;
		हाल PMIC_MPP_CONF_AMUX_ROUTE:
			अगर (arg >= PMIC_MPP_AMUX_ROUTE_ABUS4)
				वापस -EINVAL;
			pad->amux_input = arg;
			अवरोध;
		हाल PMIC_MPP_CONF_ANALOG_LEVEL:
			pad->aout_level = arg;
			अवरोध;
		हाल PMIC_MPP_CONF_PAIRED:
			pad->paired = !!arg;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	val = pad->घातer_source << PMIC_MPP_REG_VIN_SHIFT;

	ret = pmic_mpp_ग_लिखो(state, pad, PMIC_MPP_REG_DIG_VIN_CTL, val);
	अगर (ret < 0)
		वापस ret;

	अगर (pad->has_pullup) अणु
		val = pad->pullup << PMIC_MPP_REG_PULL_SHIFT;

		ret = pmic_mpp_ग_लिखो(state, pad, PMIC_MPP_REG_DIG_PULL_CTL,
				     val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	val = pad->amux_input & PMIC_MPP_REG_AIN_ROUTE_MASK;

	ret = pmic_mpp_ग_लिखो(state, pad, PMIC_MPP_REG_AIN_CTL, val);
	अगर (ret < 0)
		वापस ret;

	ret = pmic_mpp_ग_लिखो(state, pad, PMIC_MPP_REG_AOUT_CTL, pad->aout_level);
	अगर (ret < 0)
		वापस ret;

	ret = pmic_mpp_ग_लिखो_mode_ctl(state, pad);
	अगर (ret < 0)
		वापस ret;

	ret = pmic_mpp_ग_लिखो(state, pad, PMIC_MPP_REG_SINK_CTL, pad->drive_strength);
	अगर (ret < 0)
		वापस ret;

	val = pad->is_enabled << PMIC_MPP_REG_MASTER_EN_SHIFT;

	वापस pmic_mpp_ग_लिखो(state, pad, PMIC_MPP_REG_EN_CTL, val);
पूर्ण

अटल व्योम pmic_mpp_config_dbg_show(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा seq_file *s, अचिन्हित pin)
अणु
	काष्ठा pmic_mpp_state *state = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pmic_mpp_pad *pad;
	पूर्णांक ret;

	अटल स्थिर अक्षर *स्थिर biases[] = अणु
		"0.6kOhm", "10kOhm", "30kOhm", "Disabled"
	पूर्ण;

	pad = pctldev->desc->pins[pin].drv_data;

	seq_म_लिखो(s, " mpp%-2d:", pin + PMIC_MPP_PHYSICAL_OFFSET);

	अगर (!pad->is_enabled) अणु
		seq_माला_दो(s, " ---");
	पूर्ण अन्यथा अणु

		अगर (pad->input_enabled) अणु
			ret = pmic_mpp_पढ़ो(state, pad, PMIC_MPP_REG_RT_STS);
			अगर (ret < 0)
				वापस;

			ret &= PMIC_MPP_REG_RT_STS_VAL_MASK;
			pad->out_value = ret;
		पूर्ण

		seq_म_लिखो(s, " %-4s", pad->output_enabled ? "out" : "in");
		seq_म_लिखो(s, " %-7s", pmic_mpp_functions[pad->function]);
		seq_म_लिखो(s, " vin-%d", pad->घातer_source);
		seq_म_लिखो(s, " %d", pad->aout_level);
		अगर (pad->has_pullup)
			seq_म_लिखो(s, " %-8s", biases[pad->pullup]);
		seq_म_लिखो(s, " %-4s", pad->out_value ? "high" : "low");
		अगर (pad->dtest)
			seq_म_लिखो(s, " dtest%d", pad->dtest);
		अगर (pad->paired)
			seq_माला_दो(s, " paired");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pinconf_ops pmic_mpp_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_group_get		= pmic_mpp_config_get,
	.pin_config_group_set		= pmic_mpp_config_set,
	.pin_config_group_dbg_show	= pmic_mpp_config_dbg_show,
पूर्ण;

अटल पूर्णांक pmic_mpp_direction_input(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा pmic_mpp_state *state = gpiochip_get_data(chip);
	अचिन्हित दीर्घ config;

	config = pinconf_to_config_packed(PIN_CONFIG_INPUT_ENABLE, 1);

	वापस pmic_mpp_config_set(state->ctrl, pin, &config, 1);
पूर्ण

अटल पूर्णांक pmic_mpp_direction_output(काष्ठा gpio_chip *chip,
				     अचिन्हित pin, पूर्णांक val)
अणु
	काष्ठा pmic_mpp_state *state = gpiochip_get_data(chip);
	अचिन्हित दीर्घ config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, val);

	वापस pmic_mpp_config_set(state->ctrl, pin, &config, 1);
पूर्ण

अटल पूर्णांक pmic_mpp_get(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा pmic_mpp_state *state = gpiochip_get_data(chip);
	काष्ठा pmic_mpp_pad *pad;
	पूर्णांक ret;

	pad = state->ctrl->desc->pins[pin].drv_data;

	अगर (pad->input_enabled) अणु
		ret = pmic_mpp_पढ़ो(state, pad, PMIC_MPP_REG_RT_STS);
		अगर (ret < 0)
			वापस ret;

		pad->out_value = ret & PMIC_MPP_REG_RT_STS_VAL_MASK;
	पूर्ण

	वापस !!pad->out_value;
पूर्ण

अटल व्योम pmic_mpp_set(काष्ठा gpio_chip *chip, अचिन्हित pin, पूर्णांक value)
अणु
	काष्ठा pmic_mpp_state *state = gpiochip_get_data(chip);
	अचिन्हित दीर्घ config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, value);

	pmic_mpp_config_set(state->ctrl, pin, &config, 1);
पूर्ण

अटल पूर्णांक pmic_mpp_of_xlate(काष्ठा gpio_chip *chip,
			     स्थिर काष्ठा of_phandle_args *gpio_desc,
			     u32 *flags)
अणु
	अगर (chip->of_gpio_n_cells < 2)
		वापस -EINVAL;

	अगर (flags)
		*flags = gpio_desc->args[1];

	वापस gpio_desc->args[0] - PMIC_MPP_PHYSICAL_OFFSET;
पूर्ण

अटल पूर्णांक pmic_mpp_to_irq(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा pmic_mpp_state *state = gpiochip_get_data(chip);
	काष्ठा pmic_mpp_pad *pad;

	pad = state->ctrl->desc->pins[pin].drv_data;

	वापस pad->irq;
पूर्ण

अटल व्योम pmic_mpp_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	काष्ठा pmic_mpp_state *state = gpiochip_get_data(chip);
	अचिन्हित i;

	क्रम (i = 0; i < chip->ngpio; i++) अणु
		pmic_mpp_config_dbg_show(state->ctrl, s, i);
		seq_माला_दो(s, "\n");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा gpio_chip pmic_mpp_gpio_ढाँचा = अणु
	.direction_input	= pmic_mpp_direction_input,
	.direction_output	= pmic_mpp_direction_output,
	.get			= pmic_mpp_get,
	.set			= pmic_mpp_set,
	.request		= gpiochip_generic_request,
	.मुक्त			= gpiochip_generic_मुक्त,
	.of_xlate		= pmic_mpp_of_xlate,
	.to_irq			= pmic_mpp_to_irq,
	.dbg_show		= pmic_mpp_dbg_show,
पूर्ण;

अटल पूर्णांक pmic_mpp_populate(काष्ठा pmic_mpp_state *state,
			     काष्ठा pmic_mpp_pad *pad)
अणु
	पूर्णांक type, subtype, val, dir;
	अचिन्हित पूर्णांक sel;

	type = pmic_mpp_पढ़ो(state, pad, PMIC_MPP_REG_TYPE);
	अगर (type < 0)
		वापस type;

	अगर (type != PMIC_MPP_TYPE) अणु
		dev_err(state->dev, "incorrect block type 0x%x at 0x%x\n",
			type, pad->base);
		वापस -ENODEV;
	पूर्ण

	subtype = pmic_mpp_पढ़ो(state, pad, PMIC_MPP_REG_SUBTYPE);
	अगर (subtype < 0)
		वापस subtype;

	चयन (subtype) अणु
	हाल PMIC_MPP_SUBTYPE_4CH_NO_ANA_OUT:
	हाल PMIC_MPP_SUBTYPE_ULT_4CH_NO_ANA_OUT:
	हाल PMIC_MPP_SUBTYPE_4CH_NO_SINK:
	हाल PMIC_MPP_SUBTYPE_ULT_4CH_NO_SINK:
	हाल PMIC_MPP_SUBTYPE_4CH_FULL_FUNC:
		pad->num_sources = 4;
		अवरोध;
	हाल PMIC_MPP_SUBTYPE_8CH_FULL_FUNC:
		pad->num_sources = 8;
		अवरोध;
	शेष:
		dev_err(state->dev, "unknown MPP type 0x%x at 0x%x\n",
			subtype, pad->base);
		वापस -ENODEV;
	पूर्ण

	val = pmic_mpp_पढ़ो(state, pad, PMIC_MPP_REG_MODE_CTL);
	अगर (val < 0)
		वापस val;

	pad->out_value = val & PMIC_MPP_REG_MODE_VALUE_MASK;

	dir = val >> PMIC_MPP_REG_MODE_सूची_SHIFT;
	dir &= PMIC_MPP_REG_MODE_सूची_MASK;

	चयन (dir) अणु
	हाल PMIC_MPP_MODE_DIGITAL_INPUT:
		pad->input_enabled = true;
		pad->output_enabled = false;
		pad->function = PMIC_MPP_DIGITAL;
		अवरोध;
	हाल PMIC_MPP_MODE_DIGITAL_OUTPUT:
		pad->input_enabled = false;
		pad->output_enabled = true;
		pad->function = PMIC_MPP_DIGITAL;
		अवरोध;
	हाल PMIC_MPP_MODE_DIGITAL_BIसूची:
		pad->input_enabled = true;
		pad->output_enabled = true;
		pad->function = PMIC_MPP_DIGITAL;
		अवरोध;
	हाल PMIC_MPP_MODE_ANALOG_BIसूची:
		pad->input_enabled = true;
		pad->output_enabled = true;
		pad->function = PMIC_MPP_ANALOG;
		अवरोध;
	हाल PMIC_MPP_MODE_ANALOG_INPUT:
		pad->input_enabled = true;
		pad->output_enabled = false;
		pad->function = PMIC_MPP_ANALOG;
		अवरोध;
	हाल PMIC_MPP_MODE_ANALOG_OUTPUT:
		pad->input_enabled = false;
		pad->output_enabled = true;
		pad->function = PMIC_MPP_ANALOG;
		अवरोध;
	हाल PMIC_MPP_MODE_CURRENT_SINK:
		pad->input_enabled = false;
		pad->output_enabled = true;
		pad->function = PMIC_MPP_SINK;
		अवरोध;
	शेष:
		dev_err(state->dev, "unknown MPP direction\n");
		वापस -ENODEV;
	पूर्ण

	sel = val >> PMIC_MPP_REG_MODE_FUNCTION_SHIFT;
	sel &= PMIC_MPP_REG_MODE_FUNCTION_MASK;

	अगर (sel >= PMIC_MPP_SELECTOR_DTEST_FIRST)
		pad->dtest = sel + 1;
	अन्यथा अगर (sel == PMIC_MPP_SELECTOR_PAIRED)
		pad->paired = true;

	val = pmic_mpp_पढ़ो(state, pad, PMIC_MPP_REG_DIG_VIN_CTL);
	अगर (val < 0)
		वापस val;

	pad->घातer_source = val >> PMIC_MPP_REG_VIN_SHIFT;
	pad->घातer_source &= PMIC_MPP_REG_VIN_MASK;

	अगर (subtype != PMIC_MPP_SUBTYPE_ULT_4CH_NO_ANA_OUT &&
	    subtype != PMIC_MPP_SUBTYPE_ULT_4CH_NO_SINK) अणु
		val = pmic_mpp_पढ़ो(state, pad, PMIC_MPP_REG_DIG_PULL_CTL);
		अगर (val < 0)
			वापस val;

		pad->pullup = val >> PMIC_MPP_REG_PULL_SHIFT;
		pad->pullup &= PMIC_MPP_REG_PULL_MASK;
		pad->has_pullup = true;
	पूर्ण

	val = pmic_mpp_पढ़ो(state, pad, PMIC_MPP_REG_AIN_CTL);
	अगर (val < 0)
		वापस val;

	pad->amux_input = val >> PMIC_MPP_REG_AIN_ROUTE_SHIFT;
	pad->amux_input &= PMIC_MPP_REG_AIN_ROUTE_MASK;

	val = pmic_mpp_पढ़ो(state, pad, PMIC_MPP_REG_SINK_CTL);
	अगर (val < 0)
		वापस val;

	pad->drive_strength = val;

	val = pmic_mpp_पढ़ो(state, pad, PMIC_MPP_REG_AOUT_CTL);
	अगर (val < 0)
		वापस val;

	pad->aout_level = val;

	val = pmic_mpp_पढ़ो(state, pad, PMIC_MPP_REG_EN_CTL);
	अगर (val < 0)
		वापस val;

	pad->is_enabled = !!val;

	वापस 0;
पूर्ण

अटल पूर्णांक pmic_mpp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pinctrl_pin_desc *pindesc;
	काष्ठा pinctrl_desc *pctrldesc;
	काष्ठा pmic_mpp_pad *pad, *pads;
	काष्ठा pmic_mpp_state *state;
	पूर्णांक ret, npins, i;
	u32 reg;

	ret = of_property_पढ़ो_u32(dev->of_node, "reg", &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "missing base address");
		वापस ret;
	पूर्ण

	npins = platक्रमm_irq_count(pdev);
	अगर (!npins)
		वापस -EINVAL;
	अगर (npins < 0)
		वापस npins;

	BUG_ON(npins > ARRAY_SIZE(pmic_mpp_groups));

	state = devm_kzalloc(dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, state);

	state->dev = &pdev->dev;
	state->map = dev_get_regmap(dev->parent, शून्य);

	pindesc = devm_kसुस्मृति(dev, npins, माप(*pindesc), GFP_KERNEL);
	अगर (!pindesc)
		वापस -ENOMEM;

	pads = devm_kसुस्मृति(dev, npins, माप(*pads), GFP_KERNEL);
	अगर (!pads)
		वापस -ENOMEM;

	pctrldesc = devm_kzalloc(dev, माप(*pctrldesc), GFP_KERNEL);
	अगर (!pctrldesc)
		वापस -ENOMEM;

	pctrldesc->pctlops = &pmic_mpp_pinctrl_ops;
	pctrldesc->pmxops = &pmic_mpp_pinmux_ops;
	pctrldesc->confops = &pmic_mpp_pinconf_ops;
	pctrldesc->owner = THIS_MODULE;
	pctrldesc->name = dev_name(dev);
	pctrldesc->pins = pindesc;
	pctrldesc->npins = npins;

	pctrldesc->num_custom_params = ARRAY_SIZE(pmic_mpp_bindings);
	pctrldesc->custom_params = pmic_mpp_bindings;
#अगर_घोषित CONFIG_DEBUG_FS
	pctrldesc->custom_conf_items = pmic_conf_items;
#पूर्ण_अगर

	क्रम (i = 0; i < npins; i++, pindesc++) अणु
		pad = &pads[i];
		pindesc->drv_data = pad;
		pindesc->number = i;
		pindesc->name = pmic_mpp_groups[i];

		pad->irq = platक्रमm_get_irq(pdev, i);
		अगर (pad->irq < 0)
			वापस pad->irq;

		pad->base = reg + i * PMIC_MPP_ADDRESS_RANGE;

		ret = pmic_mpp_populate(state, pad);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	state->chip = pmic_mpp_gpio_ढाँचा;
	state->chip.parent = dev;
	state->chip.base = -1;
	state->chip.ngpio = npins;
	state->chip.label = dev_name(dev);
	state->chip.of_gpio_n_cells = 2;
	state->chip.can_sleep = false;

	state->ctrl = devm_pinctrl_रेजिस्टर(dev, pctrldesc, state);
	अगर (IS_ERR(state->ctrl))
		वापस PTR_ERR(state->ctrl);

	ret = gpiochip_add_data(&state->chip, state);
	अगर (ret) अणु
		dev_err(state->dev, "can't add gpio chip\n");
		वापस ret;
	पूर्ण

	ret = gpiochip_add_pin_range(&state->chip, dev_name(dev), 0, 0, npins);
	अगर (ret) अणु
		dev_err(dev, "failed to add pin range\n");
		जाओ err_range;
	पूर्ण

	वापस 0;

err_range:
	gpiochip_हटाओ(&state->chip);
	वापस ret;
पूर्ण

अटल पूर्णांक pmic_mpp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pmic_mpp_state *state = platक्रमm_get_drvdata(pdev);

	gpiochip_हटाओ(&state->chip);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pmic_mpp_of_match[] = अणु
	अणु .compatible = "qcom,pm8019-mpp" पूर्ण,	/* 6 MPP's */
	अणु .compatible = "qcom,pm8841-mpp" पूर्ण,	/* 4 MPP's */
	अणु .compatible = "qcom,pm8916-mpp" पूर्ण,	/* 4 MPP's */
	अणु .compatible = "qcom,pm8941-mpp" पूर्ण,	/* 8 MPP's */
	अणु .compatible = "qcom,pm8950-mpp" पूर्ण,	/* 4 MPP's */
	अणु .compatible = "qcom,pmi8950-mpp" पूर्ण,	/* 4 MPP's */
	अणु .compatible = "qcom,pm8994-mpp" पूर्ण,	/* 8 MPP's */
	अणु .compatible = "qcom,pma8084-mpp" पूर्ण,	/* 8 MPP's */
	अणु .compatible = "qcom,spmi-mpp" पूर्ण,	/* Generic */
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, pmic_mpp_of_match);

अटल काष्ठा platक्रमm_driver pmic_mpp_driver = अणु
	.driver = अणु
		   .name = "qcom-spmi-mpp",
		   .of_match_table = pmic_mpp_of_match,
	पूर्ण,
	.probe	= pmic_mpp_probe,
	.हटाओ = pmic_mpp_हटाओ,
पूर्ण;

module_platक्रमm_driver(pmic_mpp_driver);

MODULE_AUTHOR("Ivan T. Ivanov <iivanov@mm-sol.com>");
MODULE_DESCRIPTION("Qualcomm SPMI PMIC MPP pin control driver");
MODULE_ALIAS("platform:qcom-spmi-mpp");
MODULE_LICENSE("GPL v2");
