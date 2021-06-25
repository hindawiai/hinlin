<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
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

#समावेश <dt-bindings/pinctrl/qcom,pmic-gpपन.स>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"

#घोषणा PMIC_GPIO_ADDRESS_RANGE			0x100

/* type and subtype रेजिस्टरs base address offsets */
#घोषणा PMIC_GPIO_REG_TYPE			0x4
#घोषणा PMIC_GPIO_REG_SUBTYPE			0x5

/* GPIO peripheral type and subtype out_values */
#घोषणा PMIC_GPIO_TYPE				0x10
#घोषणा PMIC_GPIO_SUBTYPE_GPIO_4CH		0x1
#घोषणा PMIC_GPIO_SUBTYPE_GPIOC_4CH		0x5
#घोषणा PMIC_GPIO_SUBTYPE_GPIO_8CH		0x9
#घोषणा PMIC_GPIO_SUBTYPE_GPIOC_8CH		0xd
#घोषणा PMIC_GPIO_SUBTYPE_GPIO_LV		0x10
#घोषणा PMIC_GPIO_SUBTYPE_GPIO_MV		0x11

#घोषणा PMIC_MPP_REG_RT_STS			0x10
#घोषणा PMIC_MPP_REG_RT_STS_VAL_MASK		0x1

/* control रेजिस्टर base address offsets */
#घोषणा PMIC_GPIO_REG_MODE_CTL			0x40
#घोषणा PMIC_GPIO_REG_DIG_VIN_CTL		0x41
#घोषणा PMIC_GPIO_REG_DIG_PULL_CTL		0x42
#घोषणा PMIC_GPIO_REG_LV_MV_DIG_OUT_SOURCE_CTL	0x44
#घोषणा PMIC_GPIO_REG_DIG_IN_CTL		0x43
#घोषणा PMIC_GPIO_REG_DIG_OUT_CTL		0x45
#घोषणा PMIC_GPIO_REG_EN_CTL			0x46
#घोषणा PMIC_GPIO_REG_LV_MV_ANA_PASS_THRU_SEL	0x4A

/* PMIC_GPIO_REG_MODE_CTL */
#घोषणा PMIC_GPIO_REG_MODE_VALUE_SHIFT		0x1
#घोषणा PMIC_GPIO_REG_MODE_FUNCTION_SHIFT	1
#घोषणा PMIC_GPIO_REG_MODE_FUNCTION_MASK	0x7
#घोषणा PMIC_GPIO_REG_MODE_सूची_SHIFT		4
#घोषणा PMIC_GPIO_REG_MODE_सूची_MASK		0x7

#घोषणा PMIC_GPIO_MODE_DIGITAL_INPUT		0
#घोषणा PMIC_GPIO_MODE_DIGITAL_OUTPUT		1
#घोषणा PMIC_GPIO_MODE_DIGITAL_INPUT_OUTPUT	2
#घोषणा PMIC_GPIO_MODE_ANALOG_PASS_THRU		3
#घोषणा PMIC_GPIO_REG_LV_MV_MODE_सूची_MASK	0x3

/* PMIC_GPIO_REG_DIG_VIN_CTL */
#घोषणा PMIC_GPIO_REG_VIN_SHIFT			0
#घोषणा PMIC_GPIO_REG_VIN_MASK			0x7

/* PMIC_GPIO_REG_DIG_PULL_CTL */
#घोषणा PMIC_GPIO_REG_PULL_SHIFT		0
#घोषणा PMIC_GPIO_REG_PULL_MASK			0x7

#घोषणा PMIC_GPIO_PULL_DOWN			4
#घोषणा PMIC_GPIO_PULL_DISABLE			5

/* PMIC_GPIO_REG_LV_MV_DIG_OUT_SOURCE_CTL क्रम LV/MV */
#घोषणा PMIC_GPIO_LV_MV_OUTPUT_INVERT		0x80
#घोषणा PMIC_GPIO_LV_MV_OUTPUT_INVERT_SHIFT	7
#घोषणा PMIC_GPIO_LV_MV_OUTPUT_SOURCE_SEL_MASK	0xF

/* PMIC_GPIO_REG_DIG_IN_CTL */
#घोषणा PMIC_GPIO_LV_MV_DIG_IN_DTEST_EN		0x80
#घोषणा PMIC_GPIO_LV_MV_DIG_IN_DTEST_SEL_MASK	0x7
#घोषणा PMIC_GPIO_DIG_IN_DTEST_SEL_MASK		0xf

/* PMIC_GPIO_REG_DIG_OUT_CTL */
#घोषणा PMIC_GPIO_REG_OUT_STRENGTH_SHIFT	0
#घोषणा PMIC_GPIO_REG_OUT_STRENGTH_MASK		0x3
#घोषणा PMIC_GPIO_REG_OUT_TYPE_SHIFT		4
#घोषणा PMIC_GPIO_REG_OUT_TYPE_MASK		0x3

/*
 * Output type - indicates pin should be configured as push-pull,
 * खोलो drain or खोलो source.
 */
#घोषणा PMIC_GPIO_OUT_BUF_CMOS			0
#घोषणा PMIC_GPIO_OUT_BUF_OPEN_DRAIN_NMOS	1
#घोषणा PMIC_GPIO_OUT_BUF_OPEN_DRAIN_PMOS	2

/* PMIC_GPIO_REG_EN_CTL */
#घोषणा PMIC_GPIO_REG_MASTER_EN_SHIFT		7

#घोषणा PMIC_GPIO_PHYSICAL_OFFSET		1

/* PMIC_GPIO_REG_LV_MV_ANA_PASS_THRU_SEL */
#घोषणा PMIC_GPIO_LV_MV_ANA_MUX_SEL_MASK		0x3

/* Qualcomm specअगरic pin configurations */
#घोषणा PMIC_GPIO_CONF_PULL_UP			(PIN_CONFIG_END + 1)
#घोषणा PMIC_GPIO_CONF_STRENGTH			(PIN_CONFIG_END + 2)
#घोषणा PMIC_GPIO_CONF_ATEST			(PIN_CONFIG_END + 3)
#घोषणा PMIC_GPIO_CONF_ANALOG_PASS		(PIN_CONFIG_END + 4)
#घोषणा PMIC_GPIO_CONF_DTEST_BUFFER		(PIN_CONFIG_END + 5)

/* The index of each function in pmic_gpio_functions[] array */
क्रमागत pmic_gpio_func_index अणु
	PMIC_GPIO_FUNC_INDEX_NORMAL,
	PMIC_GPIO_FUNC_INDEX_PAIRED,
	PMIC_GPIO_FUNC_INDEX_FUNC1,
	PMIC_GPIO_FUNC_INDEX_FUNC2,
	PMIC_GPIO_FUNC_INDEX_FUNC3,
	PMIC_GPIO_FUNC_INDEX_FUNC4,
	PMIC_GPIO_FUNC_INDEX_DTEST1,
	PMIC_GPIO_FUNC_INDEX_DTEST2,
	PMIC_GPIO_FUNC_INDEX_DTEST3,
	PMIC_GPIO_FUNC_INDEX_DTEST4,
पूर्ण;

/**
 * काष्ठा pmic_gpio_pad - keep current GPIO settings
 * @base: Address base in SPMI device.
 * @is_enabled: Set to false when GPIO should be put in high Z state.
 * @out_value: Cached pin output value
 * @have_buffer: Set to true अगर GPIO output could be configured in push-pull,
 *	खोलो-drain or खोलो-source mode.
 * @output_enabled: Set to true अगर GPIO output logic is enabled.
 * @input_enabled: Set to true अगर GPIO input buffer logic is enabled.
 * @analog_pass: Set to true अगर GPIO is in analog-pass-through mode.
 * @lv_mv_type: Set to true अगर GPIO subtype is GPIO_LV(0x10) or GPIO_MV(0x11).
 * @num_sources: Number of घातer-sources supported by this GPIO.
 * @घातer_source: Current घातer-source used.
 * @buffer_type: Push-pull, खोलो-drain or खोलो-source.
 * @pullup: Constant current which flow trough GPIO output buffer.
 * @strength: No, Low, Medium, High
 * @function: See pmic_gpio_functions[]
 * @atest: the ATEST selection क्रम GPIO analog-pass-through mode
 * @dtest_buffer: the DTEST buffer selection क्रम digital input mode.
 */
काष्ठा pmic_gpio_pad अणु
	u16		base;
	bool		is_enabled;
	bool		out_value;
	bool		have_buffer;
	bool		output_enabled;
	bool		input_enabled;
	bool		analog_pass;
	bool		lv_mv_type;
	अचिन्हित पूर्णांक	num_sources;
	अचिन्हित पूर्णांक	घातer_source;
	अचिन्हित पूर्णांक	buffer_type;
	अचिन्हित पूर्णांक	pullup;
	अचिन्हित पूर्णांक	strength;
	अचिन्हित पूर्णांक	function;
	अचिन्हित पूर्णांक	atest;
	अचिन्हित पूर्णांक	dtest_buffer;
पूर्ण;

काष्ठा pmic_gpio_state अणु
	काष्ठा device	*dev;
	काष्ठा regmap	*map;
	काष्ठा pinctrl_dev *ctrl;
	काष्ठा gpio_chip chip;
	काष्ठा irq_chip irq;
पूर्ण;

अटल स्थिर काष्ठा pinconf_generic_params pmic_gpio_bindings[] = अणु
	अणु"qcom,pull-up-strength",	PMIC_GPIO_CONF_PULL_UP,		0पूर्ण,
	अणु"qcom,drive-strength",		PMIC_GPIO_CONF_STRENGTH,	0पूर्ण,
	अणु"qcom,atest",			PMIC_GPIO_CONF_ATEST,		0पूर्ण,
	अणु"qcom,analog-pass",		PMIC_GPIO_CONF_ANALOG_PASS,	0पूर्ण,
	अणु"qcom,dtest-buffer",           PMIC_GPIO_CONF_DTEST_BUFFER,    0पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर काष्ठा pin_config_item pmic_conf_items[ARRAY_SIZE(pmic_gpio_bindings)] = अणु
	PCONFDUMP(PMIC_GPIO_CONF_PULL_UP,  "pull up strength", शून्य, true),
	PCONFDUMP(PMIC_GPIO_CONF_STRENGTH, "drive-strength", शून्य, true),
	PCONFDUMP(PMIC_GPIO_CONF_ATEST, "atest", शून्य, true),
	PCONFDUMP(PMIC_GPIO_CONF_ANALOG_PASS, "analog-pass", शून्य, true),
	PCONFDUMP(PMIC_GPIO_CONF_DTEST_BUFFER, "dtest-buffer", शून्य, true),
पूर्ण;
#पूर्ण_अगर

अटल स्थिर अक्षर *स्थिर pmic_gpio_groups[] = अणु
	"gpio1", "gpio2", "gpio3", "gpio4", "gpio5", "gpio6", "gpio7", "gpio8",
	"gpio9", "gpio10", "gpio11", "gpio12", "gpio13", "gpio14", "gpio15",
	"gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21", "gpio22",
	"gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28", "gpio29",
	"gpio30", "gpio31", "gpio32", "gpio33", "gpio34", "gpio35", "gpio36",
पूर्ण;

अटल स्थिर अक्षर *स्थिर pmic_gpio_functions[] = अणु
	[PMIC_GPIO_FUNC_INDEX_NORMAL]	= PMIC_GPIO_FUNC_NORMAL,
	[PMIC_GPIO_FUNC_INDEX_PAIRED]	= PMIC_GPIO_FUNC_PAIRED,
	[PMIC_GPIO_FUNC_INDEX_FUNC1]	= PMIC_GPIO_FUNC_FUNC1,
	[PMIC_GPIO_FUNC_INDEX_FUNC2]	= PMIC_GPIO_FUNC_FUNC2,
	[PMIC_GPIO_FUNC_INDEX_FUNC3]	= PMIC_GPIO_FUNC_FUNC3,
	[PMIC_GPIO_FUNC_INDEX_FUNC4]	= PMIC_GPIO_FUNC_FUNC4,
	[PMIC_GPIO_FUNC_INDEX_DTEST1]	= PMIC_GPIO_FUNC_DTEST1,
	[PMIC_GPIO_FUNC_INDEX_DTEST2]	= PMIC_GPIO_FUNC_DTEST2,
	[PMIC_GPIO_FUNC_INDEX_DTEST3]	= PMIC_GPIO_FUNC_DTEST3,
	[PMIC_GPIO_FUNC_INDEX_DTEST4]	= PMIC_GPIO_FUNC_DTEST4,
पूर्ण;

अटल पूर्णांक pmic_gpio_पढ़ो(काष्ठा pmic_gpio_state *state,
			  काष्ठा pmic_gpio_pad *pad, अचिन्हित पूर्णांक addr)
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

अटल पूर्णांक pmic_gpio_ग_लिखो(काष्ठा pmic_gpio_state *state,
			   काष्ठा pmic_gpio_pad *pad, अचिन्हित पूर्णांक addr,
			   अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(state->map, pad->base + addr, val);
	अगर (ret < 0)
		dev_err(state->dev, "write 0x%x failed\n", addr);

	वापस ret;
पूर्ण

अटल पूर्णांक pmic_gpio_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	/* Every PIN is a group */
	वापस pctldev->desc->npins;
पूर्ण

अटल स्थिर अक्षर *pmic_gpio_get_group_name(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित pin)
अणु
	वापस pctldev->desc->pins[pin].name;
पूर्ण

अटल पूर्णांक pmic_gpio_get_group_pins(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
				    स्थिर अचिन्हित **pins, अचिन्हित *num_pins)
अणु
	*pins = &pctldev->desc->pins[pin].number;
	*num_pins = 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops pmic_gpio_pinctrl_ops = अणु
	.get_groups_count	= pmic_gpio_get_groups_count,
	.get_group_name		= pmic_gpio_get_group_name,
	.get_group_pins		= pmic_gpio_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक pmic_gpio_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(pmic_gpio_functions);
पूर्ण

अटल स्थिर अक्षर *pmic_gpio_get_function_name(काष्ठा pinctrl_dev *pctldev,
					       अचिन्हित function)
अणु
	वापस pmic_gpio_functions[function];
पूर्ण

अटल पूर्णांक pmic_gpio_get_function_groups(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित function,
					 स्थिर अक्षर *स्थिर **groups,
					 अचिन्हित *स्थिर num_qgroups)
अणु
	*groups = pmic_gpio_groups;
	*num_qgroups = pctldev->desc->npins;
	वापस 0;
पूर्ण

अटल पूर्णांक pmic_gpio_set_mux(काष्ठा pinctrl_dev *pctldev, अचिन्हित function,
				अचिन्हित pin)
अणु
	काष्ठा pmic_gpio_state *state = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pmic_gpio_pad *pad;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (function > PMIC_GPIO_FUNC_INDEX_DTEST4) अणु
		pr_err("function: %d is not defined\n", function);
		वापस -EINVAL;
	पूर्ण

	pad = pctldev->desc->pins[pin].drv_data;
	/*
	 * Non-LV/MV subtypes only support 2 special functions,
	 * offsetting the dtestx function values by 2
	 */
	अगर (!pad->lv_mv_type) अणु
		अगर (function == PMIC_GPIO_FUNC_INDEX_FUNC3 ||
				function == PMIC_GPIO_FUNC_INDEX_FUNC4) अणु
			pr_err("LV/MV subtype doesn't have func3/func4\n");
			वापस -EINVAL;
		पूर्ण
		अगर (function >= PMIC_GPIO_FUNC_INDEX_DTEST1)
			function -= (PMIC_GPIO_FUNC_INDEX_DTEST1 -
					PMIC_GPIO_FUNC_INDEX_FUNC3);
	पूर्ण

	pad->function = function;

	अगर (pad->analog_pass)
		val = PMIC_GPIO_MODE_ANALOG_PASS_THRU;
	अन्यथा अगर (pad->output_enabled && pad->input_enabled)
		val = PMIC_GPIO_MODE_DIGITAL_INPUT_OUTPUT;
	अन्यथा अगर (pad->output_enabled)
		val = PMIC_GPIO_MODE_DIGITAL_OUTPUT;
	अन्यथा
		val = PMIC_GPIO_MODE_DIGITAL_INPUT;

	अगर (pad->lv_mv_type) अणु
		ret = pmic_gpio_ग_लिखो(state, pad,
				PMIC_GPIO_REG_MODE_CTL, val);
		अगर (ret < 0)
			वापस ret;

		val = pad->atest - 1;
		ret = pmic_gpio_ग_लिखो(state, pad,
				PMIC_GPIO_REG_LV_MV_ANA_PASS_THRU_SEL, val);
		अगर (ret < 0)
			वापस ret;

		val = pad->out_value
			<< PMIC_GPIO_LV_MV_OUTPUT_INVERT_SHIFT;
		val |= pad->function
			& PMIC_GPIO_LV_MV_OUTPUT_SOURCE_SEL_MASK;
		ret = pmic_gpio_ग_लिखो(state, pad,
			PMIC_GPIO_REG_LV_MV_DIG_OUT_SOURCE_CTL, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		val = val << PMIC_GPIO_REG_MODE_सूची_SHIFT;
		val |= pad->function << PMIC_GPIO_REG_MODE_FUNCTION_SHIFT;
		val |= pad->out_value & PMIC_GPIO_REG_MODE_VALUE_SHIFT;

		ret = pmic_gpio_ग_लिखो(state, pad, PMIC_GPIO_REG_MODE_CTL, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	val = pad->is_enabled << PMIC_GPIO_REG_MASTER_EN_SHIFT;

	वापस pmic_gpio_ग_लिखो(state, pad, PMIC_GPIO_REG_EN_CTL, val);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops pmic_gpio_pinmux_ops = अणु
	.get_functions_count	= pmic_gpio_get_functions_count,
	.get_function_name	= pmic_gpio_get_function_name,
	.get_function_groups	= pmic_gpio_get_function_groups,
	.set_mux		= pmic_gpio_set_mux,
पूर्ण;

अटल पूर्णांक pmic_gpio_config_get(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	अचिन्हित param = pinconf_to_config_param(*config);
	काष्ठा pmic_gpio_pad *pad;
	अचिन्हित arg;

	pad = pctldev->desc->pins[pin].drv_data;

	चयन (param) अणु
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		अगर (pad->buffer_type != PMIC_GPIO_OUT_BUF_CMOS)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		अगर (pad->buffer_type != PMIC_GPIO_OUT_BUF_OPEN_DRAIN_NMOS)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_OPEN_SOURCE:
		अगर (pad->buffer_type != PMIC_GPIO_OUT_BUF_OPEN_DRAIN_PMOS)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (pad->pullup != PMIC_GPIO_PULL_DOWN)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (pad->pullup != PMIC_GPIO_PULL_DISABLE)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (pad->pullup != PMIC_GPIO_PULL_UP_30)
			वापस -EINVAL;
		arg = 1;
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
	हाल PMIC_GPIO_CONF_PULL_UP:
		arg = pad->pullup;
		अवरोध;
	हाल PMIC_GPIO_CONF_STRENGTH:
		arg = pad->strength;
		अवरोध;
	हाल PMIC_GPIO_CONF_ATEST:
		arg = pad->atest;
		अवरोध;
	हाल PMIC_GPIO_CONF_ANALOG_PASS:
		arg = pad->analog_pass;
		अवरोध;
	हाल PMIC_GPIO_CONF_DTEST_BUFFER:
		arg = pad->dtest_buffer;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);
	वापस 0;
पूर्ण

अटल पूर्णांक pmic_gpio_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
				अचिन्हित दीर्घ *configs, अचिन्हित nconfs)
अणु
	काष्ठा pmic_gpio_state *state = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pmic_gpio_pad *pad;
	अचिन्हित param, arg;
	अचिन्हित पूर्णांक val;
	पूर्णांक i, ret;

	pad = pctldev->desc->pins[pin].drv_data;

	pad->is_enabled = true;
	क्रम (i = 0; i < nconfs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_DRIVE_PUSH_PULL:
			pad->buffer_type = PMIC_GPIO_OUT_BUF_CMOS;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
			अगर (!pad->have_buffer)
				वापस -EINVAL;
			pad->buffer_type = PMIC_GPIO_OUT_BUF_OPEN_DRAIN_NMOS;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_OPEN_SOURCE:
			अगर (!pad->have_buffer)
				वापस -EINVAL;
			pad->buffer_type = PMIC_GPIO_OUT_BUF_OPEN_DRAIN_PMOS;
			अवरोध;
		हाल PIN_CONFIG_BIAS_DISABLE:
			pad->pullup = PMIC_GPIO_PULL_DISABLE;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			pad->pullup = PMIC_GPIO_PULL_UP_30;
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			अगर (arg)
				pad->pullup = PMIC_GPIO_PULL_DOWN;
			अन्यथा
				pad->pullup = PMIC_GPIO_PULL_DISABLE;
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
		हाल PMIC_GPIO_CONF_PULL_UP:
			अगर (arg > PMIC_GPIO_PULL_UP_1P5_30)
				वापस -EINVAL;
			pad->pullup = arg;
			अवरोध;
		हाल PMIC_GPIO_CONF_STRENGTH:
			अगर (arg > PMIC_GPIO_STRENGTH_LOW)
				वापस -EINVAL;
			pad->strength = arg;
			अवरोध;
		हाल PMIC_GPIO_CONF_ATEST:
			अगर (!pad->lv_mv_type || arg > 4)
				वापस -EINVAL;
			pad->atest = arg;
			अवरोध;
		हाल PMIC_GPIO_CONF_ANALOG_PASS:
			अगर (!pad->lv_mv_type)
				वापस -EINVAL;
			pad->analog_pass = true;
			अवरोध;
		हाल PMIC_GPIO_CONF_DTEST_BUFFER:
			अगर (arg > 4)
				वापस -EINVAL;
			pad->dtest_buffer = arg;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	val = pad->घातer_source << PMIC_GPIO_REG_VIN_SHIFT;

	ret = pmic_gpio_ग_लिखो(state, pad, PMIC_GPIO_REG_DIG_VIN_CTL, val);
	अगर (ret < 0)
		वापस ret;

	val = pad->pullup << PMIC_GPIO_REG_PULL_SHIFT;

	ret = pmic_gpio_ग_लिखो(state, pad, PMIC_GPIO_REG_DIG_PULL_CTL, val);
	अगर (ret < 0)
		वापस ret;

	val = pad->buffer_type << PMIC_GPIO_REG_OUT_TYPE_SHIFT;
	val |= pad->strength << PMIC_GPIO_REG_OUT_STRENGTH_SHIFT;

	ret = pmic_gpio_ग_लिखो(state, pad, PMIC_GPIO_REG_DIG_OUT_CTL, val);
	अगर (ret < 0)
		वापस ret;

	अगर (pad->dtest_buffer == 0) अणु
		val = 0;
	पूर्ण अन्यथा अणु
		अगर (pad->lv_mv_type) अणु
			val = pad->dtest_buffer - 1;
			val |= PMIC_GPIO_LV_MV_DIG_IN_DTEST_EN;
		पूर्ण अन्यथा अणु
			val = BIT(pad->dtest_buffer - 1);
		पूर्ण
	पूर्ण
	ret = pmic_gpio_ग_लिखो(state, pad, PMIC_GPIO_REG_DIG_IN_CTL, val);
	अगर (ret < 0)
		वापस ret;

	अगर (pad->analog_pass)
		val = PMIC_GPIO_MODE_ANALOG_PASS_THRU;
	अन्यथा अगर (pad->output_enabled && pad->input_enabled)
		val = PMIC_GPIO_MODE_DIGITAL_INPUT_OUTPUT;
	अन्यथा अगर (pad->output_enabled)
		val = PMIC_GPIO_MODE_DIGITAL_OUTPUT;
	अन्यथा
		val = PMIC_GPIO_MODE_DIGITAL_INPUT;

	अगर (pad->lv_mv_type) अणु
		ret = pmic_gpio_ग_लिखो(state, pad,
				PMIC_GPIO_REG_MODE_CTL, val);
		अगर (ret < 0)
			वापस ret;

		val = pad->atest - 1;
		ret = pmic_gpio_ग_लिखो(state, pad,
				PMIC_GPIO_REG_LV_MV_ANA_PASS_THRU_SEL, val);
		अगर (ret < 0)
			वापस ret;

		val = pad->out_value
			<< PMIC_GPIO_LV_MV_OUTPUT_INVERT_SHIFT;
		val |= pad->function
			& PMIC_GPIO_LV_MV_OUTPUT_SOURCE_SEL_MASK;
		ret = pmic_gpio_ग_लिखो(state, pad,
			PMIC_GPIO_REG_LV_MV_DIG_OUT_SOURCE_CTL, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		val = val << PMIC_GPIO_REG_MODE_सूची_SHIFT;
		val |= pad->function << PMIC_GPIO_REG_MODE_FUNCTION_SHIFT;
		val |= pad->out_value & PMIC_GPIO_REG_MODE_VALUE_SHIFT;

		ret = pmic_gpio_ग_लिखो(state, pad, PMIC_GPIO_REG_MODE_CTL, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	val = pad->is_enabled << PMIC_GPIO_REG_MASTER_EN_SHIFT;

	ret = pmic_gpio_ग_लिखो(state, pad, PMIC_GPIO_REG_EN_CTL, val);

	वापस ret;
पूर्ण

अटल व्योम pmic_gpio_config_dbg_show(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा seq_file *s, अचिन्हित pin)
अणु
	काष्ठा pmic_gpio_state *state = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pmic_gpio_pad *pad;
	पूर्णांक ret, val, function;

	अटल स्थिर अक्षर *स्थिर biases[] = अणु
		"pull-up 30uA", "pull-up 1.5uA", "pull-up 31.5uA",
		"pull-up 1.5uA + 30uA boost", "pull-down 10uA", "no pull"
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर buffer_types[] = अणु
		"push-pull", "open-drain", "open-source"
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर strengths[] = अणु
		"no", "high", "medium", "low"
	पूर्ण;

	pad = pctldev->desc->pins[pin].drv_data;

	seq_म_लिखो(s, " gpio%-2d:", pin + PMIC_GPIO_PHYSICAL_OFFSET);

	val = pmic_gpio_पढ़ो(state, pad, PMIC_GPIO_REG_EN_CTL);

	अगर (val < 0 || !(val >> PMIC_GPIO_REG_MASTER_EN_SHIFT)) अणु
		seq_माला_दो(s, " ---");
	पूर्ण अन्यथा अणु
		अगर (pad->input_enabled) अणु
			ret = pmic_gpio_पढ़ो(state, pad, PMIC_MPP_REG_RT_STS);
			अगर (ret < 0)
				वापस;

			ret &= PMIC_MPP_REG_RT_STS_VAL_MASK;
			pad->out_value = ret;
		पूर्ण
		/*
		 * For the non-LV/MV subtypes only 2 special functions are
		 * available, offsetting the dtest function values by 2.
		 */
		function = pad->function;
		अगर (!pad->lv_mv_type &&
				pad->function >= PMIC_GPIO_FUNC_INDEX_FUNC3)
			function += PMIC_GPIO_FUNC_INDEX_DTEST1 -
				PMIC_GPIO_FUNC_INDEX_FUNC3;

		अगर (pad->analog_pass)
			seq_माला_दो(s, " analog-pass");
		अन्यथा
			seq_म_लिखो(s, " %-4s",
					pad->output_enabled ? "out" : "in");
		seq_म_लिखो(s, " %-4s", pad->out_value ? "high" : "low");
		seq_म_लिखो(s, " %-7s", pmic_gpio_functions[function]);
		seq_म_लिखो(s, " vin-%d", pad->घातer_source);
		seq_म_लिखो(s, " %-27s", biases[pad->pullup]);
		seq_म_लिखो(s, " %-10s", buffer_types[pad->buffer_type]);
		seq_म_लिखो(s, " %-7s", strengths[pad->strength]);
		seq_म_लिखो(s, " atest-%d", pad->atest);
		seq_म_लिखो(s, " dtest-%d", pad->dtest_buffer);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pinconf_ops pmic_gpio_pinconf_ops = अणु
	.is_generic			= true,
	.pin_config_group_get		= pmic_gpio_config_get,
	.pin_config_group_set		= pmic_gpio_config_set,
	.pin_config_group_dbg_show	= pmic_gpio_config_dbg_show,
पूर्ण;

अटल पूर्णांक pmic_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा pmic_gpio_state *state = gpiochip_get_data(chip);
	अचिन्हित दीर्घ config;

	config = pinconf_to_config_packed(PIN_CONFIG_INPUT_ENABLE, 1);

	वापस pmic_gpio_config_set(state->ctrl, pin, &config, 1);
पूर्ण

अटल पूर्णांक pmic_gpio_direction_output(काष्ठा gpio_chip *chip,
				      अचिन्हित pin, पूर्णांक val)
अणु
	काष्ठा pmic_gpio_state *state = gpiochip_get_data(chip);
	अचिन्हित दीर्घ config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, val);

	वापस pmic_gpio_config_set(state->ctrl, pin, &config, 1);
पूर्ण

अटल पूर्णांक pmic_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा pmic_gpio_state *state = gpiochip_get_data(chip);
	काष्ठा pmic_gpio_pad *pad;
	पूर्णांक ret;

	pad = state->ctrl->desc->pins[pin].drv_data;

	अगर (!pad->is_enabled)
		वापस -EINVAL;

	अगर (pad->input_enabled) अणु
		ret = pmic_gpio_पढ़ो(state, pad, PMIC_MPP_REG_RT_STS);
		अगर (ret < 0)
			वापस ret;

		pad->out_value = ret & PMIC_MPP_REG_RT_STS_VAL_MASK;
	पूर्ण

	वापस !!pad->out_value;
पूर्ण

अटल व्योम pmic_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित pin, पूर्णांक value)
अणु
	काष्ठा pmic_gpio_state *state = gpiochip_get_data(chip);
	अचिन्हित दीर्घ config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, value);

	pmic_gpio_config_set(state->ctrl, pin, &config, 1);
पूर्ण

अटल पूर्णांक pmic_gpio_of_xlate(काष्ठा gpio_chip *chip,
			      स्थिर काष्ठा of_phandle_args *gpio_desc,
			      u32 *flags)
अणु
	अगर (chip->of_gpio_n_cells < 2)
		वापस -EINVAL;

	अगर (flags)
		*flags = gpio_desc->args[1];

	वापस gpio_desc->args[0] - PMIC_GPIO_PHYSICAL_OFFSET;
पूर्ण

अटल व्योम pmic_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	काष्ठा pmic_gpio_state *state = gpiochip_get_data(chip);
	अचिन्हित i;

	क्रम (i = 0; i < chip->ngpio; i++) अणु
		pmic_gpio_config_dbg_show(state->ctrl, s, i);
		seq_माला_दो(s, "\n");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा gpio_chip pmic_gpio_gpio_ढाँचा = अणु
	.direction_input	= pmic_gpio_direction_input,
	.direction_output	= pmic_gpio_direction_output,
	.get			= pmic_gpio_get,
	.set			= pmic_gpio_set,
	.request		= gpiochip_generic_request,
	.मुक्त			= gpiochip_generic_मुक्त,
	.of_xlate		= pmic_gpio_of_xlate,
	.dbg_show		= pmic_gpio_dbg_show,
पूर्ण;

अटल पूर्णांक pmic_gpio_populate(काष्ठा pmic_gpio_state *state,
			      काष्ठा pmic_gpio_pad *pad)
अणु
	पूर्णांक type, subtype, val, dir;

	type = pmic_gpio_पढ़ो(state, pad, PMIC_GPIO_REG_TYPE);
	अगर (type < 0)
		वापस type;

	अगर (type != PMIC_GPIO_TYPE) अणु
		dev_err(state->dev, "incorrect block type 0x%x at 0x%x\n",
			type, pad->base);
		वापस -ENODEV;
	पूर्ण

	subtype = pmic_gpio_पढ़ो(state, pad, PMIC_GPIO_REG_SUBTYPE);
	अगर (subtype < 0)
		वापस subtype;

	चयन (subtype) अणु
	हाल PMIC_GPIO_SUBTYPE_GPIO_4CH:
		pad->have_buffer = true;
		fallthrough;
	हाल PMIC_GPIO_SUBTYPE_GPIOC_4CH:
		pad->num_sources = 4;
		अवरोध;
	हाल PMIC_GPIO_SUBTYPE_GPIO_8CH:
		pad->have_buffer = true;
		fallthrough;
	हाल PMIC_GPIO_SUBTYPE_GPIOC_8CH:
		pad->num_sources = 8;
		अवरोध;
	हाल PMIC_GPIO_SUBTYPE_GPIO_LV:
		pad->num_sources = 1;
		pad->have_buffer = true;
		pad->lv_mv_type = true;
		अवरोध;
	हाल PMIC_GPIO_SUBTYPE_GPIO_MV:
		pad->num_sources = 2;
		pad->have_buffer = true;
		pad->lv_mv_type = true;
		अवरोध;
	शेष:
		dev_err(state->dev, "unknown GPIO type 0x%x\n", subtype);
		वापस -ENODEV;
	पूर्ण

	अगर (pad->lv_mv_type) अणु
		val = pmic_gpio_पढ़ो(state, pad,
				PMIC_GPIO_REG_LV_MV_DIG_OUT_SOURCE_CTL);
		अगर (val < 0)
			वापस val;

		pad->out_value = !!(val & PMIC_GPIO_LV_MV_OUTPUT_INVERT);
		pad->function = val & PMIC_GPIO_LV_MV_OUTPUT_SOURCE_SEL_MASK;

		val = pmic_gpio_पढ़ो(state, pad, PMIC_GPIO_REG_MODE_CTL);
		अगर (val < 0)
			वापस val;

		dir = val & PMIC_GPIO_REG_LV_MV_MODE_सूची_MASK;
	पूर्ण अन्यथा अणु
		val = pmic_gpio_पढ़ो(state, pad, PMIC_GPIO_REG_MODE_CTL);
		अगर (val < 0)
			वापस val;

		pad->out_value = val & PMIC_GPIO_REG_MODE_VALUE_SHIFT;

		dir = val >> PMIC_GPIO_REG_MODE_सूची_SHIFT;
		dir &= PMIC_GPIO_REG_MODE_सूची_MASK;
		pad->function = val >> PMIC_GPIO_REG_MODE_FUNCTION_SHIFT;
		pad->function &= PMIC_GPIO_REG_MODE_FUNCTION_MASK;
	पूर्ण

	चयन (dir) अणु
	हाल PMIC_GPIO_MODE_DIGITAL_INPUT:
		pad->input_enabled = true;
		pad->output_enabled = false;
		अवरोध;
	हाल PMIC_GPIO_MODE_DIGITAL_OUTPUT:
		pad->input_enabled = false;
		pad->output_enabled = true;
		अवरोध;
	हाल PMIC_GPIO_MODE_DIGITAL_INPUT_OUTPUT:
		pad->input_enabled = true;
		pad->output_enabled = true;
		अवरोध;
	हाल PMIC_GPIO_MODE_ANALOG_PASS_THRU:
		अगर (!pad->lv_mv_type)
			वापस -ENODEV;
		pad->analog_pass = true;
		अवरोध;
	शेष:
		dev_err(state->dev, "unknown GPIO direction\n");
		वापस -ENODEV;
	पूर्ण

	val = pmic_gpio_पढ़ो(state, pad, PMIC_GPIO_REG_DIG_VIN_CTL);
	अगर (val < 0)
		वापस val;

	pad->घातer_source = val >> PMIC_GPIO_REG_VIN_SHIFT;
	pad->घातer_source &= PMIC_GPIO_REG_VIN_MASK;

	val = pmic_gpio_पढ़ो(state, pad, PMIC_GPIO_REG_DIG_PULL_CTL);
	अगर (val < 0)
		वापस val;

	pad->pullup = val >> PMIC_GPIO_REG_PULL_SHIFT;
	pad->pullup &= PMIC_GPIO_REG_PULL_MASK;

	val = pmic_gpio_पढ़ो(state, pad, PMIC_GPIO_REG_DIG_IN_CTL);
	अगर (val < 0)
		वापस val;

	अगर (pad->lv_mv_type && (val & PMIC_GPIO_LV_MV_DIG_IN_DTEST_EN))
		pad->dtest_buffer =
			(val & PMIC_GPIO_LV_MV_DIG_IN_DTEST_SEL_MASK) + 1;
	अन्यथा अगर (!pad->lv_mv_type)
		pad->dtest_buffer = ffs(val);
	अन्यथा
		pad->dtest_buffer = 0;

	val = pmic_gpio_पढ़ो(state, pad, PMIC_GPIO_REG_DIG_OUT_CTL);
	अगर (val < 0)
		वापस val;

	pad->strength = val >> PMIC_GPIO_REG_OUT_STRENGTH_SHIFT;
	pad->strength &= PMIC_GPIO_REG_OUT_STRENGTH_MASK;

	pad->buffer_type = val >> PMIC_GPIO_REG_OUT_TYPE_SHIFT;
	pad->buffer_type &= PMIC_GPIO_REG_OUT_TYPE_MASK;

	अगर (pad->lv_mv_type) अणु
		val = pmic_gpio_पढ़ो(state, pad,
				PMIC_GPIO_REG_LV_MV_ANA_PASS_THRU_SEL);
		अगर (val < 0)
			वापस val;
		pad->atest = (val & PMIC_GPIO_LV_MV_ANA_MUX_SEL_MASK) + 1;
	पूर्ण

	/* Pin could be disabled with PIN_CONFIG_BIAS_HIGH_IMPEDANCE */
	pad->is_enabled = true;
	वापस 0;
पूर्ण

अटल पूर्णांक pmic_gpio_करोमुख्य_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
				      काष्ठा irq_fwspec *fwspec,
				      अचिन्हित दीर्घ *hwirq,
				      अचिन्हित पूर्णांक *type)
अणु
	काष्ठा pmic_gpio_state *state = container_of(करोमुख्य->host_data,
						     काष्ठा pmic_gpio_state,
						     chip);

	अगर (fwspec->param_count != 2 ||
	    fwspec->param[0] < 1 || fwspec->param[0] > state->chip.ngpio)
		वापस -EINVAL;

	*hwirq = fwspec->param[0] - PMIC_GPIO_PHYSICAL_OFFSET;
	*type = fwspec->param[1];

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक pmic_gpio_child_offset_to_irq(काष्ठा gpio_chip *chip,
						  अचिन्हित पूर्णांक offset)
अणु
	वापस offset + PMIC_GPIO_PHYSICAL_OFFSET;
पूर्ण

अटल पूर्णांक pmic_gpio_child_to_parent_hwirq(काष्ठा gpio_chip *chip,
					   अचिन्हित पूर्णांक child_hwirq,
					   अचिन्हित पूर्णांक child_type,
					   अचिन्हित पूर्णांक *parent_hwirq,
					   अचिन्हित पूर्णांक *parent_type)
अणु
	*parent_hwirq = child_hwirq + 0xc0;
	*parent_type = child_type;

	वापस 0;
पूर्ण

अटल पूर्णांक pmic_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा irq_करोमुख्य *parent_करोमुख्य;
	काष्ठा device_node *parent_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pinctrl_pin_desc *pindesc;
	काष्ठा pinctrl_desc *pctrldesc;
	काष्ठा pmic_gpio_pad *pad, *pads;
	काष्ठा pmic_gpio_state *state;
	काष्ठा gpio_irq_chip *girq;
	पूर्णांक ret, npins, i;
	u32 reg;

	ret = of_property_पढ़ो_u32(dev->of_node, "reg", &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "missing base address");
		वापस ret;
	पूर्ण

	npins = (uपूर्णांकptr_t) device_get_match_data(&pdev->dev);

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

	pctrldesc->pctlops = &pmic_gpio_pinctrl_ops;
	pctrldesc->pmxops = &pmic_gpio_pinmux_ops;
	pctrldesc->confops = &pmic_gpio_pinconf_ops;
	pctrldesc->owner = THIS_MODULE;
	pctrldesc->name = dev_name(dev);
	pctrldesc->pins = pindesc;
	pctrldesc->npins = npins;
	pctrldesc->num_custom_params = ARRAY_SIZE(pmic_gpio_bindings);
	pctrldesc->custom_params = pmic_gpio_bindings;
#अगर_घोषित CONFIG_DEBUG_FS
	pctrldesc->custom_conf_items = pmic_conf_items;
#पूर्ण_अगर

	क्रम (i = 0; i < npins; i++, pindesc++) अणु
		pad = &pads[i];
		pindesc->drv_data = pad;
		pindesc->number = i;
		pindesc->name = pmic_gpio_groups[i];

		pad->base = reg + i * PMIC_GPIO_ADDRESS_RANGE;

		ret = pmic_gpio_populate(state, pad);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	state->chip = pmic_gpio_gpio_ढाँचा;
	state->chip.parent = dev;
	state->chip.base = -1;
	state->chip.ngpio = npins;
	state->chip.label = dev_name(dev);
	state->chip.of_gpio_n_cells = 2;
	state->chip.can_sleep = false;

	state->ctrl = devm_pinctrl_रेजिस्टर(dev, pctrldesc, state);
	अगर (IS_ERR(state->ctrl))
		वापस PTR_ERR(state->ctrl);

	parent_node = of_irq_find_parent(state->dev->of_node);
	अगर (!parent_node)
		वापस -ENXIO;

	parent_करोमुख्य = irq_find_host(parent_node);
	of_node_put(parent_node);
	अगर (!parent_करोमुख्य)
		वापस -ENXIO;

	state->irq.name = "spmi-gpio",
	state->irq.irq_ack = irq_chip_ack_parent,
	state->irq.irq_mask = irq_chip_mask_parent,
	state->irq.irq_unmask = irq_chip_unmask_parent,
	state->irq.irq_set_type = irq_chip_set_type_parent,
	state->irq.irq_set_wake = irq_chip_set_wake_parent,
	state->irq.flags = IRQCHIP_MASK_ON_SUSPEND,

	girq = &state->chip.irq;
	girq->chip = &state->irq;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;
	girq->fwnode = of_node_to_fwnode(state->dev->of_node);
	girq->parent_करोमुख्य = parent_करोमुख्य;
	girq->child_to_parent_hwirq = pmic_gpio_child_to_parent_hwirq;
	girq->populate_parent_alloc_arg = gpiochip_populate_parent_fwspec_fourcell;
	girq->child_offset_to_irq = pmic_gpio_child_offset_to_irq;
	girq->child_irq_करोमुख्य_ops.translate = pmic_gpio_करोमुख्य_translate;

	ret = gpiochip_add_data(&state->chip, state);
	अगर (ret) अणु
		dev_err(state->dev, "can't add gpio chip\n");
		वापस ret;
	पूर्ण

	/*
	 * For DeviceTree-supported प्रणालीs, the gpio core checks the
	 * pinctrl's device node क्रम the "gpio-ranges" property.
	 * If it is present, it takes care of adding the pin ranges
	 * क्रम the driver. In this हाल the driver can skip ahead.
	 *
	 * In order to reमुख्य compatible with older, existing DeviceTree
	 * files which करोn't set the "gpio-ranges" property or प्रणालीs that
	 * utilize ACPI the driver has to call gpiochip_add_pin_range().
	 */
	अगर (!of_property_पढ़ो_bool(dev->of_node, "gpio-ranges")) अणु
		ret = gpiochip_add_pin_range(&state->chip, dev_name(dev), 0, 0,
					     npins);
		अगर (ret) अणु
			dev_err(dev, "failed to add pin range\n");
			जाओ err_range;
		पूर्ण
	पूर्ण

	वापस 0;

err_range:
	gpiochip_हटाओ(&state->chip);
	वापस ret;
पूर्ण

अटल पूर्णांक pmic_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pmic_gpio_state *state = platक्रमm_get_drvdata(pdev);

	gpiochip_हटाओ(&state->chip);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pmic_gpio_of_match[] = अणु
	अणु .compatible = "qcom,pm8005-gpio", .data = (व्योम *) 4 पूर्ण,
	अणु .compatible = "qcom,pm8916-gpio", .data = (व्योम *) 4 पूर्ण,
	अणु .compatible = "qcom,pm8941-gpio", .data = (व्योम *) 36 पूर्ण,
	/* pm8950 has 8 GPIOs with holes on 3 */
	अणु .compatible = "qcom,pm8950-gpio", .data = (व्योम *) 8 पूर्ण,
	अणु .compatible = "qcom,pmi8950-gpio", .data = (व्योम *) 2 पूर्ण,
	अणु .compatible = "qcom,pm8994-gpio", .data = (व्योम *) 22 पूर्ण,
	अणु .compatible = "qcom,pmi8994-gpio", .data = (व्योम *) 10 पूर्ण,
	अणु .compatible = "qcom,pm8998-gpio", .data = (व्योम *) 26 पूर्ण,
	अणु .compatible = "qcom,pmi8998-gpio", .data = (व्योम *) 14 पूर्ण,
	अणु .compatible = "qcom,pma8084-gpio", .data = (व्योम *) 22 पूर्ण,
	/* pms405 has 12 GPIOs with holes on 1, 9, and 10 */
	अणु .compatible = "qcom,pms405-gpio", .data = (व्योम *) 12 पूर्ण,
	/* pm660 has 13 GPIOs with holes on 1, 5, 6, 7, 8 and 10 */
	अणु .compatible = "qcom,pm660-gpio", .data = (व्योम *) 13 पूर्ण,
	/* pm660l has 12 GPIOs with holes on 1, 2, 10, 11 and 12 */
	अणु .compatible = "qcom,pm660l-gpio", .data = (व्योम *) 12 पूर्ण,
	/* pm8150 has 10 GPIOs with holes on 2, 5, 7 and 8 */
	अणु .compatible = "qcom,pm8150-gpio", .data = (व्योम *) 10 पूर्ण,
	/* pm8150b has 12 GPIOs with holes on 3, r and 7 */
	अणु .compatible = "qcom,pm8150b-gpio", .data = (व्योम *) 12 पूर्ण,
	/* pm8150l has 12 GPIOs with holes on 7 */
	अणु .compatible = "qcom,pm8150l-gpio", .data = (व्योम *) 12 पूर्ण,
	अणु .compatible = "qcom,pm8350-gpio", .data = (व्योम *) 10 पूर्ण,
	अणु .compatible = "qcom,pm8350b-gpio", .data = (व्योम *) 8 पूर्ण,
	अणु .compatible = "qcom,pm8350c-gpio", .data = (व्योम *) 9 पूर्ण,
	अणु .compatible = "qcom,pmk8350-gpio", .data = (व्योम *) 4 पूर्ण,
	अणु .compatible = "qcom,pmr735a-gpio", .data = (व्योम *) 4 पूर्ण,
	अणु .compatible = "qcom,pmr735b-gpio", .data = (व्योम *) 4 पूर्ण,
	अणु .compatible = "qcom,pm6150-gpio", .data = (व्योम *) 10 पूर्ण,
	अणु .compatible = "qcom,pm6150l-gpio", .data = (व्योम *) 12 पूर्ण,
	अणु .compatible = "qcom,pm8008-gpio", .data = (व्योम *) 2 पूर्ण,
	/* pmx55 has 11 GPIOs with holes on 3, 7, 10, 11 */
	अणु .compatible = "qcom,pmx55-gpio", .data = (व्योम *) 11 पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, pmic_gpio_of_match);

अटल काष्ठा platक्रमm_driver pmic_gpio_driver = अणु
	.driver = अणु
		   .name = "qcom-spmi-gpio",
		   .of_match_table = pmic_gpio_of_match,
	पूर्ण,
	.probe	= pmic_gpio_probe,
	.हटाओ = pmic_gpio_हटाओ,
पूर्ण;

module_platक्रमm_driver(pmic_gpio_driver);

MODULE_AUTHOR("Ivan T. Ivanov <iivanov@mm-sol.com>");
MODULE_DESCRIPTION("Qualcomm SPMI PMIC GPIO pin control driver");
MODULE_ALIAS("platform:qcom-spmi-gpio");
MODULE_LICENSE("GPL v2");
