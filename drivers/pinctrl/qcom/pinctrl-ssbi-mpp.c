<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Sony Mobile Communications AB.
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>

#समावेश <dt-bindings/pinctrl/qcom,pmic-mpp.h>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"

/* MPP रेजिस्टरs */
#घोषणा SSBI_REG_ADDR_MPP_BASE		0x50
#घोषणा SSBI_REG_ADDR_MPP(n)		(SSBI_REG_ADDR_MPP_BASE + n)

/* MPP Type: type */
#घोषणा PM8XXX_MPP_TYPE_D_INPUT         0
#घोषणा PM8XXX_MPP_TYPE_D_OUTPUT        1
#घोषणा PM8XXX_MPP_TYPE_D_BI_सूची        2
#घोषणा PM8XXX_MPP_TYPE_A_INPUT         3
#घोषणा PM8XXX_MPP_TYPE_A_OUTPUT        4
#घोषणा PM8XXX_MPP_TYPE_SINK            5
#घोषणा PM8XXX_MPP_TYPE_DTEST_SINK      6
#घोषणा PM8XXX_MPP_TYPE_DTEST_OUTPUT    7

/* Digital Input: control */
#घोषणा PM8XXX_MPP_DIN_TO_INT           0
#घोषणा PM8XXX_MPP_DIN_TO_DBUS1         1
#घोषणा PM8XXX_MPP_DIN_TO_DBUS2         2
#घोषणा PM8XXX_MPP_DIN_TO_DBUS3         3

/* Digital Output: control */
#घोषणा PM8XXX_MPP_DOUT_CTRL_LOW        0
#घोषणा PM8XXX_MPP_DOUT_CTRL_HIGH       1
#घोषणा PM8XXX_MPP_DOUT_CTRL_MPP        2
#घोषणा PM8XXX_MPP_DOUT_CTRL_INV_MPP    3

/* Bidirectional: control */
#घोषणा PM8XXX_MPP_BI_PULLUP_1KOHM      0
#घोषणा PM8XXX_MPP_BI_PULLUP_OPEN       1
#घोषणा PM8XXX_MPP_BI_PULLUP_10KOHM     2
#घोषणा PM8XXX_MPP_BI_PULLUP_30KOHM     3

/* Analog Output: control */
#घोषणा PM8XXX_MPP_AOUT_CTRL_DISABLE            0
#घोषणा PM8XXX_MPP_AOUT_CTRL_ENABLE             1
#घोषणा PM8XXX_MPP_AOUT_CTRL_MPP_HIGH_EN        2
#घोषणा PM8XXX_MPP_AOUT_CTRL_MPP_LOW_EN         3

/* Current Sink: control */
#घोषणा PM8XXX_MPP_CS_CTRL_DISABLE      0
#घोषणा PM8XXX_MPP_CS_CTRL_ENABLE       1
#घोषणा PM8XXX_MPP_CS_CTRL_MPP_HIGH_EN  2
#घोषणा PM8XXX_MPP_CS_CTRL_MPP_LOW_EN   3

/* DTEST Current Sink: control */
#घोषणा PM8XXX_MPP_DTEST_CS_CTRL_EN1    0
#घोषणा PM8XXX_MPP_DTEST_CS_CTRL_EN2    1
#घोषणा PM8XXX_MPP_DTEST_CS_CTRL_EN3    2
#घोषणा PM8XXX_MPP_DTEST_CS_CTRL_EN4    3

/* DTEST Digital Output: control */
#घोषणा PM8XXX_MPP_DTEST_DBUS1          0
#घोषणा PM8XXX_MPP_DTEST_DBUS2          1
#घोषणा PM8XXX_MPP_DTEST_DBUS3          2
#घोषणा PM8XXX_MPP_DTEST_DBUS4          3

/* custom pinconf parameters */
#घोषणा PM8XXX_CONFIG_AMUX		(PIN_CONFIG_END + 1)
#घोषणा PM8XXX_CONFIG_DTEST_SELECTOR	(PIN_CONFIG_END + 2)
#घोषणा PM8XXX_CONFIG_ALEVEL		(PIN_CONFIG_END + 3)
#घोषणा PM8XXX_CONFIG_PAIRED		(PIN_CONFIG_END + 4)

/**
 * काष्ठा pm8xxx_pin_data - dynamic configuration क्रम a pin
 * @reg:		address of the control रेजिस्टर
 * @irq:		IRQ from the PMIC पूर्णांकerrupt controller
 * @mode:		operating mode क्रम the pin (digital, analog or current sink)
 * @input:		pin is input
 * @output:		pin is output
 * @high_z:		pin is भग्नing
 * @paired:		mpp operates in paired mode
 * @output_value:	logical output value of the mpp
 * @घातer_source:	selected घातer source
 * @dtest:		DTEST route selector
 * @amux:		input muxing in analog mode
 * @aout_level:		selector of the output in analog mode
 * @drive_strength:	drive strength of the current sink
 * @pullup:		pull up value, when in digital bidirectional mode
 */
काष्ठा pm8xxx_pin_data अणु
	अचिन्हित reg;
	पूर्णांक irq;

	u8 mode;

	bool input;
	bool output;
	bool high_z;
	bool paired;
	bool output_value;

	u8 घातer_source;
	u8 dtest;
	u8 amux;
	u8 aout_level;
	u8 drive_strength;
	अचिन्हित pullup;
पूर्ण;

काष्ठा pm8xxx_mpp अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा pinctrl_dev *pctrl;
	काष्ठा gpio_chip chip;

	काष्ठा pinctrl_desc desc;
	अचिन्हित npins;
पूर्ण;

अटल स्थिर काष्ठा pinconf_generic_params pm8xxx_mpp_bindings[] = अणु
	अणु"qcom,amux-route",	PM8XXX_CONFIG_AMUX,		0पूर्ण,
	अणु"qcom,analog-level",	PM8XXX_CONFIG_ALEVEL,		0पूर्ण,
	अणु"qcom,dtest",		PM8XXX_CONFIG_DTEST_SELECTOR,	0पूर्ण,
	अणु"qcom,paired",		PM8XXX_CONFIG_PAIRED,		0पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर काष्ठा pin_config_item pm8xxx_conf_items[] = अणु
	PCONFDUMP(PM8XXX_CONFIG_AMUX, "analog mux", शून्य, true),
	PCONFDUMP(PM8XXX_CONFIG_ALEVEL, "analog level", शून्य, true),
	PCONFDUMP(PM8XXX_CONFIG_DTEST_SELECTOR, "dtest", शून्य, true),
	PCONFDUMP(PM8XXX_CONFIG_PAIRED, "paired", शून्य, false),
पूर्ण;
#पूर्ण_अगर

#घोषणा PM8XXX_MAX_MPPS	12
अटल स्थिर अक्षर * स्थिर pm8xxx_groups[PM8XXX_MAX_MPPS] = अणु
	"mpp1", "mpp2", "mpp3", "mpp4", "mpp5", "mpp6", "mpp7", "mpp8",
	"mpp9", "mpp10", "mpp11", "mpp12",
पूर्ण;

#घोषणा PM8XXX_MPP_DIGITAL	0
#घोषणा PM8XXX_MPP_ANALOG	1
#घोषणा PM8XXX_MPP_SINK		2

अटल स्थिर अक्षर * स्थिर pm8xxx_mpp_functions[] = अणु
	"digital", "analog", "sink",
पूर्ण;

अटल पूर्णांक pm8xxx_mpp_update(काष्ठा pm8xxx_mpp *pctrl,
			     काष्ठा pm8xxx_pin_data *pin)
अणु
	अचिन्हित level;
	अचिन्हित ctrl;
	अचिन्हित type;
	पूर्णांक ret;
	u8 val;

	चयन (pin->mode) अणु
	हाल PM8XXX_MPP_DIGITAL:
		अगर (pin->dtest) अणु
			type = PM8XXX_MPP_TYPE_DTEST_OUTPUT;
			ctrl = pin->dtest - 1;
		पूर्ण अन्यथा अगर (pin->input && pin->output) अणु
			type = PM8XXX_MPP_TYPE_D_BI_सूची;
			अगर (pin->high_z)
				ctrl = PM8XXX_MPP_BI_PULLUP_OPEN;
			अन्यथा अगर (pin->pullup == 600)
				ctrl = PM8XXX_MPP_BI_PULLUP_1KOHM;
			अन्यथा अगर (pin->pullup == 10000)
				ctrl = PM8XXX_MPP_BI_PULLUP_10KOHM;
			अन्यथा
				ctrl = PM8XXX_MPP_BI_PULLUP_30KOHM;
		पूर्ण अन्यथा अगर (pin->input) अणु
			type = PM8XXX_MPP_TYPE_D_INPUT;
			अगर (pin->dtest)
				ctrl = pin->dtest;
			अन्यथा
				ctrl = PM8XXX_MPP_DIN_TO_INT;
		पूर्ण अन्यथा अणु
			type = PM8XXX_MPP_TYPE_D_OUTPUT;
			ctrl = !!pin->output_value;
			अगर (pin->paired)
				ctrl |= BIT(1);
		पूर्ण

		level = pin->घातer_source;
		अवरोध;
	हाल PM8XXX_MPP_ANALOG:
		अगर (pin->output) अणु
			type = PM8XXX_MPP_TYPE_A_OUTPUT;
			level = pin->aout_level;
			ctrl = pin->output_value;
			अगर (pin->paired)
				ctrl |= BIT(1);
		पूर्ण अन्यथा अणु
			type = PM8XXX_MPP_TYPE_A_INPUT;
			level = pin->amux;
			ctrl = 0;
		पूर्ण
		अवरोध;
	हाल PM8XXX_MPP_SINK:
		level = (pin->drive_strength / 5) - 1;
		अगर (pin->dtest) अणु
			type = PM8XXX_MPP_TYPE_DTEST_SINK;
			ctrl = pin->dtest - 1;
		पूर्ण अन्यथा अणु
			type = PM8XXX_MPP_TYPE_SINK;
			ctrl = pin->output_value;
			अगर (pin->paired)
				ctrl |= BIT(1);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val = type << 5 | level << 2 | ctrl;
	ret = regmap_ग_लिखो(pctrl->regmap, pin->reg, val);
	अगर (ret)
		dev_err(pctrl->dev, "failed to write register\n");

	वापस ret;
पूर्ण

अटल पूर्णांक pm8xxx_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा pm8xxx_mpp *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->npins;
पूर्ण

अटल स्थिर अक्षर *pm8xxx_get_group_name(काष्ठा pinctrl_dev *pctldev,
					 अचिन्हित group)
अणु
	वापस pm8xxx_groups[group];
पूर्ण


अटल पूर्णांक pm8xxx_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित group,
				 स्थिर अचिन्हित **pins,
				 अचिन्हित *num_pins)
अणु
	काष्ठा pm8xxx_mpp *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*pins = &pctrl->desc.pins[group].number;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops pm8xxx_pinctrl_ops = अणु
	.get_groups_count	= pm8xxx_get_groups_count,
	.get_group_name		= pm8xxx_get_group_name,
	.get_group_pins         = pm8xxx_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_group,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक pm8xxx_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(pm8xxx_mpp_functions);
पूर्ण

अटल स्थिर अक्षर *pm8xxx_get_function_name(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित function)
अणु
	वापस pm8xxx_mpp_functions[function];
पूर्ण

अटल पूर्णांक pm8xxx_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित function,
				      स्थिर अक्षर * स्थिर **groups,
				      अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा pm8xxx_mpp *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pm8xxx_groups;
	*num_groups = pctrl->npins;
	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित function,
				 अचिन्हित group)
अणु
	काष्ठा pm8xxx_mpp *pctrl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[group].drv_data;

	pin->mode = function;
	pm8xxx_mpp_update(pctrl, pin);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops pm8xxx_pinmux_ops = अणु
	.get_functions_count	= pm8xxx_get_functions_count,
	.get_function_name	= pm8xxx_get_function_name,
	.get_function_groups	= pm8xxx_get_function_groups,
	.set_mux		= pm8xxx_pinmux_set_mux,
पूर्ण;

अटल पूर्णांक pm8xxx_pin_config_get(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक offset,
				 अचिन्हित दीर्घ *config)
अणु
	काष्ठा pm8xxx_mpp *pctrl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	अचिन्हित param = pinconf_to_config_param(*config);
	अचिन्हित arg;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_PULL_UP:
		arg = pin->pullup;
		अवरोध;
	हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		arg = pin->high_z;
		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
		arg = pin->input;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		arg = pin->output_value;
		अवरोध;
	हाल PIN_CONFIG_POWER_SOURCE:
		arg = pin->घातer_source;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		arg = pin->drive_strength;
		अवरोध;
	हाल PM8XXX_CONFIG_DTEST_SELECTOR:
		arg = pin->dtest;
		अवरोध;
	हाल PM8XXX_CONFIG_AMUX:
		arg = pin->amux;
		अवरोध;
	हाल PM8XXX_CONFIG_ALEVEL:
		arg = pin->aout_level;
		अवरोध;
	हाल PM8XXX_CONFIG_PAIRED:
		arg = pin->paired;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_pin_config_set(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक offset,
				 अचिन्हित दीर्घ *configs,
				 अचिन्हित num_configs)
अणु
	काष्ठा pm8xxx_mpp *pctrl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	अचिन्हित param;
	अचिन्हित arg;
	अचिन्हित i;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_UP:
			pin->pullup = arg;
			अवरोध;
		हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			pin->high_z = true;
			अवरोध;
		हाल PIN_CONFIG_INPUT_ENABLE:
			pin->input = true;
			अवरोध;
		हाल PIN_CONFIG_OUTPUT:
			pin->output = true;
			pin->output_value = !!arg;
			अवरोध;
		हाल PIN_CONFIG_POWER_SOURCE:
			pin->घातer_source = arg;
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			pin->drive_strength = arg;
			अवरोध;
		हाल PM8XXX_CONFIG_DTEST_SELECTOR:
			pin->dtest = arg;
			अवरोध;
		हाल PM8XXX_CONFIG_AMUX:
			pin->amux = arg;
			अवरोध;
		हाल PM8XXX_CONFIG_ALEVEL:
			pin->aout_level = arg;
			अवरोध;
		हाल PM8XXX_CONFIG_PAIRED:
			pin->paired = !!arg;
			अवरोध;
		शेष:
			dev_err(pctrl->dev,
				"unsupported config parameter: %x\n",
				param);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	pm8xxx_mpp_update(pctrl, pin);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops pm8xxx_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_group_get = pm8xxx_pin_config_get,
	.pin_config_group_set = pm8xxx_pin_config_set,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_desc pm8xxx_pinctrl_desc = अणु
	.name = "pm8xxx_mpp",
	.pctlops = &pm8xxx_pinctrl_ops,
	.pmxops = &pm8xxx_pinmux_ops,
	.confops = &pm8xxx_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक pm8xxx_mpp_direction_input(काष्ठा gpio_chip *chip,
				       अचिन्हित offset)
अणु
	काष्ठा pm8xxx_mpp *pctrl = gpiochip_get_data(chip);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;

	चयन (pin->mode) अणु
	हाल PM8XXX_MPP_DIGITAL:
		pin->input = true;
		अवरोध;
	हाल PM8XXX_MPP_ANALOG:
		pin->input = true;
		pin->output = true;
		अवरोध;
	हाल PM8XXX_MPP_SINK:
		वापस -EINVAL;
	पूर्ण

	pm8xxx_mpp_update(pctrl, pin);

	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_mpp_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset,
					पूर्णांक value)
अणु
	काष्ठा pm8xxx_mpp *pctrl = gpiochip_get_data(chip);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;

	चयन (pin->mode) अणु
	हाल PM8XXX_MPP_DIGITAL:
		pin->output = true;
		अवरोध;
	हाल PM8XXX_MPP_ANALOG:
		pin->input = false;
		pin->output = true;
		अवरोध;
	हाल PM8XXX_MPP_SINK:
		pin->input = false;
		pin->output = true;
		अवरोध;
	पूर्ण

	pm8xxx_mpp_update(pctrl, pin);

	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_mpp_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा pm8xxx_mpp *pctrl = gpiochip_get_data(chip);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	bool state;
	पूर्णांक ret;

	अगर (!pin->input)
		वापस !!pin->output_value;

	ret = irq_get_irqchip_state(pin->irq, IRQCHIP_STATE_LINE_LEVEL, &state);
	अगर (!ret)
		ret = !!state;

	वापस ret;
पूर्ण

अटल व्योम pm8xxx_mpp_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा pm8xxx_mpp *pctrl = gpiochip_get_data(chip);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;

	pin->output_value = !!value;

	pm8xxx_mpp_update(pctrl, pin);
पूर्ण

अटल पूर्णांक pm8xxx_mpp_of_xlate(काष्ठा gpio_chip *chip,
				स्थिर काष्ठा of_phandle_args *gpio_desc,
				u32 *flags)
अणु
	अगर (chip->of_gpio_n_cells < 2)
		वापस -EINVAL;

	अगर (flags)
		*flags = gpio_desc->args[1];

	वापस gpio_desc->args[0] - 1;
पूर्ण


अटल पूर्णांक pm8xxx_mpp_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा pm8xxx_mpp *pctrl = gpiochip_get_data(chip);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;

	वापस pin->irq;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/seq_file.h>

अटल व्योम pm8xxx_mpp_dbg_show_one(काष्ठा seq_file *s,
				  काष्ठा pinctrl_dev *pctldev,
				  काष्ठा gpio_chip *chip,
				  अचिन्हित offset,
				  अचिन्हित gpio)
अणु
	काष्ठा pm8xxx_mpp *pctrl = gpiochip_get_data(chip);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;

	अटल स्थिर अक्षर * स्थिर aout_lvls[] = अणु
		"1v25", "1v25_2", "0v625", "0v3125", "mpp", "abus1", "abus2",
		"abus3"
	पूर्ण;

	अटल स्थिर अक्षर * स्थिर amuxs[] = अणु
		"amux5", "amux6", "amux7", "amux8", "amux9", "abus1", "abus2",
		"abus3",
	पूर्ण;

	seq_म_लिखो(s, " mpp%-2d:", offset + 1);

	चयन (pin->mode) अणु
	हाल PM8XXX_MPP_DIGITAL:
		seq_माला_दो(s, " digital ");
		अगर (pin->dtest) अणु
			seq_म_लिखो(s, "dtest%d\n", pin->dtest);
		पूर्ण अन्यथा अगर (pin->input && pin->output) अणु
			अगर (pin->high_z)
				seq_माला_दो(s, "bi-dir high-z");
			अन्यथा
				seq_म_लिखो(s, "bi-dir %dOhm", pin->pullup);
		पूर्ण अन्यथा अगर (pin->input) अणु
			अगर (pin->dtest)
				seq_म_लिखो(s, "in dtest%d", pin->dtest);
			अन्यथा
				seq_माला_दो(s, "in gpio");
		पूर्ण अन्यथा अगर (pin->output) अणु
			seq_माला_दो(s, "out ");

			अगर (!pin->paired) अणु
				seq_माला_दो(s, pin->output_value ?
					 "high" : "low");
			पूर्ण अन्यथा अणु
				seq_माला_दो(s, pin->output_value ?
					 "inverted" : "follow");
			पूर्ण
		पूर्ण
		अवरोध;
	हाल PM8XXX_MPP_ANALOG:
		seq_माला_दो(s, " analog ");
		अगर (pin->output) अणु
			seq_म_लिखो(s, "out %s ", aout_lvls[pin->aout_level]);
			अगर (!pin->paired) अणु
				seq_माला_दो(s, pin->output_value ?
					 "high" : "low");
			पूर्ण अन्यथा अणु
				seq_माला_दो(s, pin->output_value ?
					 "inverted" : "follow");
			पूर्ण
		पूर्ण अन्यथा अणु
			seq_म_लिखो(s, "input mux %s", amuxs[pin->amux]);
		पूर्ण
		अवरोध;
	हाल PM8XXX_MPP_SINK:
		seq_म_लिखो(s, " sink %dmA ", pin->drive_strength);
		अगर (pin->dtest) अणु
			seq_म_लिखो(s, "dtest%d", pin->dtest);
		पूर्ण अन्यथा अणु
			अगर (!pin->paired) अणु
				seq_माला_दो(s, pin->output_value ?
					 "high" : "low");
			पूर्ण अन्यथा अणु
				seq_माला_दो(s, pin->output_value ?
					 "inverted" : "follow");
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pm8xxx_mpp_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	अचिन्हित gpio = chip->base;
	अचिन्हित i;

	क्रम (i = 0; i < chip->ngpio; i++, gpio++) अणु
		pm8xxx_mpp_dbg_show_one(s, शून्य, chip, i, gpio);
		seq_माला_दो(s, "\n");
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा pm8xxx_mpp_dbg_show शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा gpio_chip pm8xxx_mpp_ढाँचा = अणु
	.direction_input = pm8xxx_mpp_direction_input,
	.direction_output = pm8xxx_mpp_direction_output,
	.get = pm8xxx_mpp_get,
	.set = pm8xxx_mpp_set,
	.of_xlate = pm8xxx_mpp_of_xlate,
	.to_irq = pm8xxx_mpp_to_irq,
	.dbg_show = pm8xxx_mpp_dbg_show,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक pm8xxx_pin_populate(काष्ठा pm8xxx_mpp *pctrl,
			       काष्ठा pm8xxx_pin_data *pin)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित level;
	अचिन्हित ctrl;
	अचिन्हित type;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pctrl->regmap, pin->reg, &val);
	अगर (ret) अणु
		dev_err(pctrl->dev, "failed to read register\n");
		वापस ret;
	पूर्ण

	type = (val >> 5) & 7;
	level = (val >> 2) & 7;
	ctrl = (val) & 3;

	चयन (type) अणु
	हाल PM8XXX_MPP_TYPE_D_INPUT:
		pin->mode = PM8XXX_MPP_DIGITAL;
		pin->input = true;
		pin->घातer_source = level;
		pin->dtest = ctrl;
		अवरोध;
	हाल PM8XXX_MPP_TYPE_D_OUTPUT:
		pin->mode = PM8XXX_MPP_DIGITAL;
		pin->output = true;
		pin->घातer_source = level;
		pin->output_value = !!(ctrl & BIT(0));
		pin->paired = !!(ctrl & BIT(1));
		अवरोध;
	हाल PM8XXX_MPP_TYPE_D_BI_सूची:
		pin->mode = PM8XXX_MPP_DIGITAL;
		pin->input = true;
		pin->output = true;
		pin->घातer_source = level;
		चयन (ctrl) अणु
		हाल PM8XXX_MPP_BI_PULLUP_1KOHM:
			pin->pullup = 600;
			अवरोध;
		हाल PM8XXX_MPP_BI_PULLUP_OPEN:
			pin->high_z = true;
			अवरोध;
		हाल PM8XXX_MPP_BI_PULLUP_10KOHM:
			pin->pullup = 10000;
			अवरोध;
		हाल PM8XXX_MPP_BI_PULLUP_30KOHM:
			pin->pullup = 30000;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PM8XXX_MPP_TYPE_A_INPUT:
		pin->mode = PM8XXX_MPP_ANALOG;
		pin->input = true;
		pin->amux = level;
		अवरोध;
	हाल PM8XXX_MPP_TYPE_A_OUTPUT:
		pin->mode = PM8XXX_MPP_ANALOG;
		pin->output = true;
		pin->aout_level = level;
		pin->output_value = !!(ctrl & BIT(0));
		pin->paired = !!(ctrl & BIT(1));
		अवरोध;
	हाल PM8XXX_MPP_TYPE_SINK:
		pin->mode = PM8XXX_MPP_SINK;
		pin->drive_strength = 5 * (level + 1);
		pin->output_value = !!(ctrl & BIT(0));
		pin->paired = !!(ctrl & BIT(1));
		अवरोध;
	हाल PM8XXX_MPP_TYPE_DTEST_SINK:
		pin->mode = PM8XXX_MPP_SINK;
		pin->dtest = ctrl + 1;
		pin->drive_strength = 5 * (level + 1);
		अवरोध;
	हाल PM8XXX_MPP_TYPE_DTEST_OUTPUT:
		pin->mode = PM8XXX_MPP_DIGITAL;
		pin->घातer_source = level;
		अगर (ctrl >= 1)
			pin->dtest = ctrl;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pm8xxx_mpp_of_match[] = अणु
	अणु .compatible = "qcom,pm8018-mpp" पूर्ण,
	अणु .compatible = "qcom,pm8038-mpp" पूर्ण,
	अणु .compatible = "qcom,pm8058-mpp" पूर्ण,
	अणु .compatible = "qcom,pm8917-mpp" पूर्ण,
	अणु .compatible = "qcom,pm8821-mpp" पूर्ण,
	अणु .compatible = "qcom,pm8921-mpp" पूर्ण,
	अणु .compatible = "qcom,ssbi-mpp" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pm8xxx_mpp_of_match);

अटल पूर्णांक pm8xxx_mpp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm8xxx_pin_data *pin_data;
	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा pm8xxx_mpp *pctrl;
	पूर्णांक ret;
	पूर्णांक i, npins;

	pctrl = devm_kzalloc(&pdev->dev, माप(*pctrl), GFP_KERNEL);
	अगर (!pctrl)
		वापस -ENOMEM;

	pctrl->dev = &pdev->dev;
	npins = platक्रमm_irq_count(pdev);
	अगर (!npins)
		वापस -EINVAL;
	अगर (npins < 0)
		वापस npins;
	pctrl->npins = npins;

	pctrl->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!pctrl->regmap) अणु
		dev_err(&pdev->dev, "parent regmap unavailable\n");
		वापस -ENXIO;
	पूर्ण

	pctrl->desc = pm8xxx_pinctrl_desc;
	pctrl->desc.npins = pctrl->npins;

	pins = devm_kसुस्मृति(&pdev->dev,
			    pctrl->desc.npins,
			    माप(काष्ठा pinctrl_pin_desc),
			    GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	pin_data = devm_kसुस्मृति(&pdev->dev,
				pctrl->desc.npins,
				माप(काष्ठा pm8xxx_pin_data),
				GFP_KERNEL);
	अगर (!pin_data)
		वापस -ENOMEM;

	क्रम (i = 0; i < pctrl->desc.npins; i++) अणु
		pin_data[i].reg = SSBI_REG_ADDR_MPP(i);
		pin_data[i].irq = platक्रमm_get_irq(pdev, i);
		अगर (pin_data[i].irq < 0)
			वापस pin_data[i].irq;

		ret = pm8xxx_pin_populate(pctrl, &pin_data[i]);
		अगर (ret)
			वापस ret;

		pins[i].number = i;
		pins[i].name = pm8xxx_groups[i];
		pins[i].drv_data = &pin_data[i];
	पूर्ण
	pctrl->desc.pins = pins;

	pctrl->desc.num_custom_params = ARRAY_SIZE(pm8xxx_mpp_bindings);
	pctrl->desc.custom_params = pm8xxx_mpp_bindings;
#अगर_घोषित CONFIG_DEBUG_FS
	pctrl->desc.custom_conf_items = pm8xxx_conf_items;
#पूर्ण_अगर

	pctrl->pctrl = devm_pinctrl_रेजिस्टर(&pdev->dev, &pctrl->desc, pctrl);
	अगर (IS_ERR(pctrl->pctrl)) अणु
		dev_err(&pdev->dev, "couldn't register pm8xxx mpp driver\n");
		वापस PTR_ERR(pctrl->pctrl);
	पूर्ण

	pctrl->chip = pm8xxx_mpp_ढाँचा;
	pctrl->chip.base = -1;
	pctrl->chip.parent = &pdev->dev;
	pctrl->chip.of_node = pdev->dev.of_node;
	pctrl->chip.of_gpio_n_cells = 2;
	pctrl->chip.label = dev_name(pctrl->dev);
	pctrl->chip.ngpio = pctrl->npins;
	ret = gpiochip_add_data(&pctrl->chip, pctrl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed register gpiochip\n");
		वापस ret;
	पूर्ण

	ret = gpiochip_add_pin_range(&pctrl->chip,
				     dev_name(pctrl->dev),
				     0, 0, pctrl->chip.ngpio);
	अगर (ret) अणु
		dev_err(pctrl->dev, "failed to add pin range\n");
		जाओ unरेजिस्टर_gpiochip;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pctrl);

	dev_dbg(&pdev->dev, "Qualcomm pm8xxx mpp driver probed\n");

	वापस 0;

unरेजिस्टर_gpiochip:
	gpiochip_हटाओ(&pctrl->chip);

	वापस ret;
पूर्ण

अटल पूर्णांक pm8xxx_mpp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm8xxx_mpp *pctrl = platक्रमm_get_drvdata(pdev);

	gpiochip_हटाओ(&pctrl->chip);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pm8xxx_mpp_driver = अणु
	.driver = अणु
		.name = "qcom-ssbi-mpp",
		.of_match_table = pm8xxx_mpp_of_match,
	पूर्ण,
	.probe = pm8xxx_mpp_probe,
	.हटाओ = pm8xxx_mpp_हटाओ,
पूर्ण;

module_platक्रमm_driver(pm8xxx_mpp_driver);

MODULE_AUTHOR("Bjorn Andersson <bjorn.andersson@sonymobile.com>");
MODULE_DESCRIPTION("Qualcomm PM8xxx MPP driver");
MODULE_LICENSE("GPL v2");
