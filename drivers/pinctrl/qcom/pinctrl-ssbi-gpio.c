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

#समावेश <dt-bindings/pinctrl/qcom,pmic-gpपन.स>

#समावेश "../core.h"
#समावेश "../pinctrl-utils.h"

/* mode */
#घोषणा PM8XXX_GPIO_MODE_ENABLED	BIT(0)
#घोषणा PM8XXX_GPIO_MODE_INPUT		0
#घोषणा PM8XXX_GPIO_MODE_OUTPUT		2

/* output buffer */
#घोषणा PM8XXX_GPIO_PUSH_PULL		0
#घोषणा PM8XXX_GPIO_OPEN_DRAIN		1

/* bias */
#घोषणा PM8XXX_GPIO_BIAS_PU_30		0
#घोषणा PM8XXX_GPIO_BIAS_PU_1P5		1
#घोषणा PM8XXX_GPIO_BIAS_PU_31P5	2
#घोषणा PM8XXX_GPIO_BIAS_PU_1P5_30	3
#घोषणा PM8XXX_GPIO_BIAS_PD		4
#घोषणा PM8XXX_GPIO_BIAS_NP		5

/* GPIO रेजिस्टरs */
#घोषणा SSBI_REG_ADDR_GPIO_BASE		0x150
#घोषणा SSBI_REG_ADDR_GPIO(n)		(SSBI_REG_ADDR_GPIO_BASE + n)

#घोषणा PM8XXX_BANK_WRITE		BIT(7)

#घोषणा PM8XXX_MAX_GPIOS               44

#घोषणा PM8XXX_GPIO_PHYSICAL_OFFSET	1

/* custom pinconf parameters */
#घोषणा PM8XXX_QCOM_DRIVE_STRENGH      (PIN_CONFIG_END + 1)
#घोषणा PM8XXX_QCOM_PULL_UP_STRENGTH   (PIN_CONFIG_END + 2)

/**
 * काष्ठा pm8xxx_pin_data - dynamic configuration क्रम a pin
 * @reg:               address of the control रेजिस्टर
 * @घातer_source:      logical selected voltage source, mapping in अटल data
 *                     is used translate to रेजिस्टर values
 * @mode:              operating mode क्रम the pin (input/output)
 * @खोलो_drain:        output buffer configured as खोलो-drain (vs push-pull)
 * @output_value:      configured output value
 * @bias:              रेजिस्टर view of configured bias
 * @pull_up_strength:  placeholder क्रम selected pull up strength
 *                     only used to configure bias when pull up is selected
 * @output_strength:   selector of output-strength
 * @disable:           pin disabled / configured as tristate
 * @function:          pinmux selector
 * @inverted:          pin logic is inverted
 */
काष्ठा pm8xxx_pin_data अणु
	अचिन्हित reg;
	u8 घातer_source;
	u8 mode;
	bool खोलो_drain;
	bool output_value;
	u8 bias;
	u8 pull_up_strength;
	u8 output_strength;
	bool disable;
	u8 function;
	bool inverted;
पूर्ण;

काष्ठा pm8xxx_gpio अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा pinctrl_dev *pctrl;
	काष्ठा gpio_chip chip;

	काष्ठा pinctrl_desc desc;
	अचिन्हित npins;
पूर्ण;

अटल स्थिर काष्ठा pinconf_generic_params pm8xxx_gpio_bindings[] = अणु
	अणु"qcom,drive-strength",		PM8XXX_QCOM_DRIVE_STRENGH,	0पूर्ण,
	अणु"qcom,pull-up-strength",	PM8XXX_QCOM_PULL_UP_STRENGTH,	0पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर काष्ठा pin_config_item pm8xxx_conf_items[ARRAY_SIZE(pm8xxx_gpio_bindings)] = अणु
	PCONFDUMP(PM8XXX_QCOM_DRIVE_STRENGH, "drive-strength", शून्य, true),
	PCONFDUMP(PM8XXX_QCOM_PULL_UP_STRENGTH,  "pull up strength", शून्य, true),
पूर्ण;
#पूर्ण_अगर

अटल स्थिर अक्षर * स्थिर pm8xxx_groups[PM8XXX_MAX_GPIOS] = अणु
	"gpio1", "gpio2", "gpio3", "gpio4", "gpio5", "gpio6", "gpio7", "gpio8",
	"gpio9", "gpio10", "gpio11", "gpio12", "gpio13", "gpio14", "gpio15",
	"gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21", "gpio22",
	"gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28", "gpio29",
	"gpio30", "gpio31", "gpio32", "gpio33", "gpio34", "gpio35", "gpio36",
	"gpio37", "gpio38", "gpio39", "gpio40", "gpio41", "gpio42", "gpio43",
	"gpio44",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pm8xxx_gpio_functions[] = अणु
	PMIC_GPIO_FUNC_NORMAL, PMIC_GPIO_FUNC_PAIRED,
	PMIC_GPIO_FUNC_FUNC1, PMIC_GPIO_FUNC_FUNC2,
	PMIC_GPIO_FUNC_DTEST1, PMIC_GPIO_FUNC_DTEST2,
	PMIC_GPIO_FUNC_DTEST3, PMIC_GPIO_FUNC_DTEST4,
पूर्ण;

अटल पूर्णांक pm8xxx_पढ़ो_bank(काष्ठा pm8xxx_gpio *pctrl,
			    काष्ठा pm8xxx_pin_data *pin, पूर्णांक bank)
अणु
	अचिन्हित पूर्णांक val = bank << 4;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(pctrl->regmap, pin->reg, val);
	अगर (ret) अणु
		dev_err(pctrl->dev, "failed to select bank %d\n", bank);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(pctrl->regmap, pin->reg, &val);
	अगर (ret) अणु
		dev_err(pctrl->dev, "failed to read register %d\n", bank);
		वापस ret;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक pm8xxx_ग_लिखो_bank(काष्ठा pm8xxx_gpio *pctrl,
			     काष्ठा pm8xxx_pin_data *pin,
			     पूर्णांक bank,
			     u8 val)
अणु
	पूर्णांक ret;

	val |= PM8XXX_BANK_WRITE;
	val |= bank << 4;

	ret = regmap_ग_लिखो(pctrl->regmap, pin->reg, val);
	अगर (ret)
		dev_err(pctrl->dev, "failed to write register\n");

	वापस ret;
पूर्ण

अटल पूर्णांक pm8xxx_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा pm8xxx_gpio *pctrl = pinctrl_dev_get_drvdata(pctldev);

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
	काष्ठा pm8xxx_gpio *pctrl = pinctrl_dev_get_drvdata(pctldev);

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
	वापस ARRAY_SIZE(pm8xxx_gpio_functions);
पूर्ण

अटल स्थिर अक्षर *pm8xxx_get_function_name(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित function)
अणु
	वापस pm8xxx_gpio_functions[function];
पूर्ण

अटल पूर्णांक pm8xxx_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित function,
				      स्थिर अक्षर * स्थिर **groups,
				      अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा pm8xxx_gpio *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pm8xxx_groups;
	*num_groups = pctrl->npins;
	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित function,
				 अचिन्हित group)
अणु
	काष्ठा pm8xxx_gpio *pctrl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[group].drv_data;
	u8 val;

	pin->function = function;
	val = pin->function << 1;

	pm8xxx_ग_लिखो_bank(pctrl, pin, 4, val);

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
	काष्ठा pm8xxx_gpio *pctrl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	अचिन्हित param = pinconf_to_config_param(*config);
	अचिन्हित arg;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (pin->bias != PM8XXX_GPIO_BIAS_NP)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (pin->bias != PM8XXX_GPIO_BIAS_PD)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (pin->bias > PM8XXX_GPIO_BIAS_PU_1P5_30)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PM8XXX_QCOM_PULL_UP_STRENGTH:
		arg = pin->pull_up_strength;
		अवरोध;
	हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		अगर (!pin->disable)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
		अगर (pin->mode != PM8XXX_GPIO_MODE_INPUT)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		अगर (pin->mode & PM8XXX_GPIO_MODE_OUTPUT)
			arg = pin->output_value;
		अन्यथा
			arg = 0;
		अवरोध;
	हाल PIN_CONFIG_POWER_SOURCE:
		arg = pin->घातer_source;
		अवरोध;
	हाल PM8XXX_QCOM_DRIVE_STRENGH:
		arg = pin->output_strength;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		अगर (pin->खोलो_drain)
			वापस -EINVAL;
		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		अगर (!pin->खोलो_drain)
			वापस -EINVAL;
		arg = 1;
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
	काष्ठा pm8xxx_gpio *pctrl = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	अचिन्हित param;
	अचिन्हित arg;
	अचिन्हित i;
	u8 banks = 0;
	u8 val;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
			pin->bias = PM8XXX_GPIO_BIAS_NP;
			banks |= BIT(2);
			pin->disable = 0;
			banks |= BIT(3);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			pin->bias = PM8XXX_GPIO_BIAS_PD;
			banks |= BIT(2);
			pin->disable = 0;
			banks |= BIT(3);
			अवरोध;
		हाल PM8XXX_QCOM_PULL_UP_STRENGTH:
			अगर (arg > PM8XXX_GPIO_BIAS_PU_1P5_30) अणु
				dev_err(pctrl->dev, "invalid pull-up strength\n");
				वापस -EINVAL;
			पूर्ण
			pin->pull_up_strength = arg;
			fallthrough;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			pin->bias = pin->pull_up_strength;
			banks |= BIT(2);
			pin->disable = 0;
			banks |= BIT(3);
			अवरोध;
		हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			pin->disable = 1;
			banks |= BIT(3);
			अवरोध;
		हाल PIN_CONFIG_INPUT_ENABLE:
			pin->mode = PM8XXX_GPIO_MODE_INPUT;
			banks |= BIT(0) | BIT(1);
			अवरोध;
		हाल PIN_CONFIG_OUTPUT:
			pin->mode = PM8XXX_GPIO_MODE_OUTPUT;
			pin->output_value = !!arg;
			banks |= BIT(0) | BIT(1);
			अवरोध;
		हाल PIN_CONFIG_POWER_SOURCE:
			pin->घातer_source = arg;
			banks |= BIT(0);
			अवरोध;
		हाल PM8XXX_QCOM_DRIVE_STRENGH:
			अगर (arg > PMIC_GPIO_STRENGTH_LOW) अणु
				dev_err(pctrl->dev, "invalid drive strength\n");
				वापस -EINVAL;
			पूर्ण
			pin->output_strength = arg;
			banks |= BIT(3);
			अवरोध;
		हाल PIN_CONFIG_DRIVE_PUSH_PULL:
			pin->खोलो_drain = 0;
			banks |= BIT(1);
			अवरोध;
		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
			pin->खोलो_drain = 1;
			banks |= BIT(1);
			अवरोध;
		शेष:
			dev_err(pctrl->dev,
				"unsupported config parameter: %x\n",
				param);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (banks & BIT(0)) अणु
		val = pin->घातer_source << 1;
		val |= PM8XXX_GPIO_MODE_ENABLED;
		pm8xxx_ग_लिखो_bank(pctrl, pin, 0, val);
	पूर्ण

	अगर (banks & BIT(1)) अणु
		val = pin->mode << 2;
		val |= pin->खोलो_drain << 1;
		val |= pin->output_value;
		pm8xxx_ग_लिखो_bank(pctrl, pin, 1, val);
	पूर्ण

	अगर (banks & BIT(2)) अणु
		val = pin->bias << 1;
		pm8xxx_ग_लिखो_bank(pctrl, pin, 2, val);
	पूर्ण

	अगर (banks & BIT(3)) अणु
		val = pin->output_strength << 2;
		val |= pin->disable;
		pm8xxx_ग_लिखो_bank(pctrl, pin, 3, val);
	पूर्ण

	अगर (banks & BIT(4)) अणु
		val = pin->function << 1;
		pm8xxx_ग_लिखो_bank(pctrl, pin, 4, val);
	पूर्ण

	अगर (banks & BIT(5)) अणु
		val = 0;
		अगर (!pin->inverted)
			val |= BIT(3);
		pm8xxx_ग_लिखो_bank(pctrl, pin, 5, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops pm8xxx_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_group_get = pm8xxx_pin_config_get,
	.pin_config_group_set = pm8xxx_pin_config_set,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_desc pm8xxx_pinctrl_desc = अणु
	.name = "pm8xxx_gpio",
	.pctlops = &pm8xxx_pinctrl_ops,
	.pmxops = &pm8xxx_pinmux_ops,
	.confops = &pm8xxx_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक pm8xxx_gpio_direction_input(काष्ठा gpio_chip *chip,
				       अचिन्हित offset)
अणु
	काष्ठा pm8xxx_gpio *pctrl = gpiochip_get_data(chip);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	u8 val;

	pin->mode = PM8XXX_GPIO_MODE_INPUT;
	val = pin->mode << 2;

	pm8xxx_ग_लिखो_bank(pctrl, pin, 1, val);

	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset,
					पूर्णांक value)
अणु
	काष्ठा pm8xxx_gpio *pctrl = gpiochip_get_data(chip);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	u8 val;

	pin->mode = PM8XXX_GPIO_MODE_OUTPUT;
	pin->output_value = !!value;

	val = pin->mode << 2;
	val |= pin->खोलो_drain << 1;
	val |= pin->output_value;

	pm8xxx_ग_लिखो_bank(pctrl, pin, 1, val);

	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा pm8xxx_gpio *pctrl = gpiochip_get_data(chip);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	पूर्णांक ret, irq;
	bool state;

	अगर (pin->mode == PM8XXX_GPIO_MODE_OUTPUT)
		वापस pin->output_value;

	irq = chip->to_irq(chip, offset);
	अगर (irq >= 0) अणु
		ret = irq_get_irqchip_state(irq, IRQCHIP_STATE_LINE_LEVEL,
					    &state);
		अगर (!ret)
			ret = !!state;
	पूर्ण अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल व्योम pm8xxx_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा pm8xxx_gpio *pctrl = gpiochip_get_data(chip);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	u8 val;

	pin->output_value = !!value;

	val = pin->mode << 2;
	val |= pin->खोलो_drain << 1;
	val |= pin->output_value;

	pm8xxx_ग_लिखो_bank(pctrl, pin, 1, val);
पूर्ण

अटल पूर्णांक pm8xxx_gpio_of_xlate(काष्ठा gpio_chip *chip,
				स्थिर काष्ठा of_phandle_args *gpio_desc,
				u32 *flags)
अणु
	अगर (chip->of_gpio_n_cells < 2)
		वापस -EINVAL;

	अगर (flags)
		*flags = gpio_desc->args[1];

	वापस gpio_desc->args[0] - PM8XXX_GPIO_PHYSICAL_OFFSET;
पूर्ण


#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/seq_file.h>

अटल व्योम pm8xxx_gpio_dbg_show_one(काष्ठा seq_file *s,
				  काष्ठा pinctrl_dev *pctldev,
				  काष्ठा gpio_chip *chip,
				  अचिन्हित offset,
				  अचिन्हित gpio)
अणु
	काष्ठा pm8xxx_gpio *pctrl = gpiochip_get_data(chip);
	काष्ठा pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;

	अटल स्थिर अक्षर * स्थिर modes[] = अणु
		"in", "both", "out", "off"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर biases[] = अणु
		"pull-up 30uA", "pull-up 1.5uA", "pull-up 31.5uA",
		"pull-up 1.5uA + 30uA boost", "pull-down 10uA", "no pull"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर buffer_types[] = अणु
		"push-pull", "open-drain"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर strengths[] = अणु
		"no", "high", "medium", "low"
	पूर्ण;

	seq_म_लिखो(s, " gpio%-2d:", offset + PM8XXX_GPIO_PHYSICAL_OFFSET);
	अगर (pin->disable) अणु
		seq_माला_दो(s, " ---");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(s, " %-4s", modes[pin->mode]);
		seq_म_लिखो(s, " %-7s", pm8xxx_gpio_functions[pin->function]);
		seq_म_लिखो(s, " VIN%d", pin->घातer_source);
		seq_म_लिखो(s, " %-27s", biases[pin->bias]);
		seq_म_लिखो(s, " %-10s", buffer_types[pin->खोलो_drain]);
		seq_म_लिखो(s, " %-4s", pin->output_value ? "high" : "low");
		seq_म_लिखो(s, " %-7s", strengths[pin->output_strength]);
		अगर (pin->inverted)
			seq_माला_दो(s, " inverted");
	पूर्ण
पूर्ण

अटल व्योम pm8xxx_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	अचिन्हित gpio = chip->base;
	अचिन्हित i;

	क्रम (i = 0; i < chip->ngpio; i++, gpio++) अणु
		pm8xxx_gpio_dbg_show_one(s, शून्य, chip, i, gpio);
		seq_माला_दो(s, "\n");
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा pm8xxx_gpio_dbg_show शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा gpio_chip pm8xxx_gpio_ढाँचा = अणु
	.direction_input = pm8xxx_gpio_direction_input,
	.direction_output = pm8xxx_gpio_direction_output,
	.get = pm8xxx_gpio_get,
	.set = pm8xxx_gpio_set,
	.of_xlate = pm8xxx_gpio_of_xlate,
	.dbg_show = pm8xxx_gpio_dbg_show,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक pm8xxx_pin_populate(काष्ठा pm8xxx_gpio *pctrl,
			       काष्ठा pm8xxx_pin_data *pin)
अणु
	पूर्णांक val;

	val = pm8xxx_पढ़ो_bank(pctrl, pin, 0);
	अगर (val < 0)
		वापस val;

	pin->घातer_source = (val >> 1) & 0x7;

	val = pm8xxx_पढ़ो_bank(pctrl, pin, 1);
	अगर (val < 0)
		वापस val;

	pin->mode = (val >> 2) & 0x3;
	pin->खोलो_drain = !!(val & BIT(1));
	pin->output_value = val & BIT(0);

	val = pm8xxx_पढ़ो_bank(pctrl, pin, 2);
	अगर (val < 0)
		वापस val;

	pin->bias = (val >> 1) & 0x7;
	अगर (pin->bias <= PM8XXX_GPIO_BIAS_PU_1P5_30)
		pin->pull_up_strength = pin->bias;
	अन्यथा
		pin->pull_up_strength = PM8XXX_GPIO_BIAS_PU_30;

	val = pm8xxx_पढ़ो_bank(pctrl, pin, 3);
	अगर (val < 0)
		वापस val;

	pin->output_strength = (val >> 2) & 0x3;
	pin->disable = val & BIT(0);

	val = pm8xxx_पढ़ो_bank(pctrl, pin, 4);
	अगर (val < 0)
		वापस val;

	pin->function = (val >> 1) & 0x7;

	val = pm8xxx_पढ़ो_bank(pctrl, pin, 5);
	अगर (val < 0)
		वापस val;

	pin->inverted = !(val & BIT(3));

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip pm8xxx_irq_chip = अणु
	.name = "ssbi-gpio",
	.irq_mask_ack = irq_chip_mask_ack_parent,
	.irq_unmask = irq_chip_unmask_parent,
	.irq_set_type = irq_chip_set_type_parent,
	.flags = IRQCHIP_MASK_ON_SUSPEND | IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल पूर्णांक pm8xxx_करोमुख्य_translate(काष्ठा irq_करोमुख्य *करोमुख्य,
				   काष्ठा irq_fwspec *fwspec,
				   अचिन्हित दीर्घ *hwirq,
				   अचिन्हित पूर्णांक *type)
अणु
	काष्ठा pm8xxx_gpio *pctrl = container_of(करोमुख्य->host_data,
						 काष्ठा pm8xxx_gpio, chip);

	अगर (fwspec->param_count != 2 || fwspec->param[0] < 1 ||
	    fwspec->param[0] > pctrl->chip.ngpio)
		वापस -EINVAL;

	*hwirq = fwspec->param[0] - PM8XXX_GPIO_PHYSICAL_OFFSET;
	*type = fwspec->param[1];

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक pm8xxx_child_offset_to_irq(काष्ठा gpio_chip *chip,
					       अचिन्हित पूर्णांक offset)
अणु
	वापस offset + PM8XXX_GPIO_PHYSICAL_OFFSET;
पूर्ण

अटल पूर्णांक pm8xxx_child_to_parent_hwirq(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक child_hwirq,
					अचिन्हित पूर्णांक child_type,
					अचिन्हित पूर्णांक *parent_hwirq,
					अचिन्हित पूर्णांक *parent_type)
अणु
	*parent_hwirq = child_hwirq + 0xc0;
	*parent_type = child_type;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pm8xxx_gpio_of_match[] = अणु
	अणु .compatible = "qcom,pm8018-gpio", .data = (व्योम *) 6 पूर्ण,
	अणु .compatible = "qcom,pm8038-gpio", .data = (व्योम *) 12 पूर्ण,
	अणु .compatible = "qcom,pm8058-gpio", .data = (व्योम *) 44 पूर्ण,
	अणु .compatible = "qcom,pm8917-gpio", .data = (व्योम *) 38 पूर्ण,
	अणु .compatible = "qcom,pm8921-gpio", .data = (व्योम *) 44 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pm8xxx_gpio_of_match);

अटल पूर्णांक pm8xxx_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm8xxx_pin_data *pin_data;
	काष्ठा irq_करोमुख्य *parent_करोमुख्य;
	काष्ठा device_node *parent_node;
	काष्ठा pinctrl_pin_desc *pins;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा pm8xxx_gpio *pctrl;
	पूर्णांक ret, i;

	pctrl = devm_kzalloc(&pdev->dev, माप(*pctrl), GFP_KERNEL);
	अगर (!pctrl)
		वापस -ENOMEM;

	pctrl->dev = &pdev->dev;
	pctrl->npins = (uपूर्णांकptr_t) device_get_match_data(&pdev->dev);

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
		pin_data[i].reg = SSBI_REG_ADDR_GPIO(i);

		ret = pm8xxx_pin_populate(pctrl, &pin_data[i]);
		अगर (ret)
			वापस ret;

		pins[i].number = i;
		pins[i].name = pm8xxx_groups[i];
		pins[i].drv_data = &pin_data[i];
	पूर्ण
	pctrl->desc.pins = pins;

	pctrl->desc.num_custom_params = ARRAY_SIZE(pm8xxx_gpio_bindings);
	pctrl->desc.custom_params = pm8xxx_gpio_bindings;
#अगर_घोषित CONFIG_DEBUG_FS
	pctrl->desc.custom_conf_items = pm8xxx_conf_items;
#पूर्ण_अगर

	pctrl->pctrl = devm_pinctrl_रेजिस्टर(&pdev->dev, &pctrl->desc, pctrl);
	अगर (IS_ERR(pctrl->pctrl)) अणु
		dev_err(&pdev->dev, "couldn't register pm8xxx gpio driver\n");
		वापस PTR_ERR(pctrl->pctrl);
	पूर्ण

	pctrl->chip = pm8xxx_gpio_ढाँचा;
	pctrl->chip.base = -1;
	pctrl->chip.parent = &pdev->dev;
	pctrl->chip.of_node = pdev->dev.of_node;
	pctrl->chip.of_gpio_n_cells = 2;
	pctrl->chip.label = dev_name(pctrl->dev);
	pctrl->chip.ngpio = pctrl->npins;

	parent_node = of_irq_find_parent(pctrl->dev->of_node);
	अगर (!parent_node)
		वापस -ENXIO;

	parent_करोमुख्य = irq_find_host(parent_node);
	of_node_put(parent_node);
	अगर (!parent_करोमुख्य)
		वापस -ENXIO;

	girq = &pctrl->chip.irq;
	girq->chip = &pm8xxx_irq_chip;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;
	girq->fwnode = of_node_to_fwnode(pctrl->dev->of_node);
	girq->parent_करोमुख्य = parent_करोमुख्य;
	girq->child_to_parent_hwirq = pm8xxx_child_to_parent_hwirq;
	girq->populate_parent_alloc_arg = gpiochip_populate_parent_fwspec_twocell;
	girq->child_offset_to_irq = pm8xxx_child_offset_to_irq;
	girq->child_irq_करोमुख्य_ops.translate = pm8xxx_करोमुख्य_translate;

	ret = gpiochip_add_data(&pctrl->chip, pctrl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed register gpiochip\n");
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
	अगर (!of_property_पढ़ो_bool(pctrl->dev->of_node, "gpio-ranges")) अणु
		ret = gpiochip_add_pin_range(&pctrl->chip, dev_name(pctrl->dev),
					     0, 0, pctrl->chip.ngpio);
		अगर (ret) अणु
			dev_err(pctrl->dev, "failed to add pin range\n");
			जाओ unरेजिस्टर_gpiochip;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, pctrl);

	dev_dbg(&pdev->dev, "Qualcomm pm8xxx gpio driver probed\n");

	वापस 0;

unरेजिस्टर_gpiochip:
	gpiochip_हटाओ(&pctrl->chip);

	वापस ret;
पूर्ण

अटल पूर्णांक pm8xxx_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm8xxx_gpio *pctrl = platक्रमm_get_drvdata(pdev);

	gpiochip_हटाओ(&pctrl->chip);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pm8xxx_gpio_driver = अणु
	.driver = अणु
		.name = "qcom-ssbi-gpio",
		.of_match_table = pm8xxx_gpio_of_match,
	पूर्ण,
	.probe = pm8xxx_gpio_probe,
	.हटाओ = pm8xxx_gpio_हटाओ,
पूर्ण;

module_platक्रमm_driver(pm8xxx_gpio_driver);

MODULE_AUTHOR("Bjorn Andersson <bjorn.andersson@sonymobile.com>");
MODULE_DESCRIPTION("Qualcomm PM8xxx GPIO driver");
MODULE_LICENSE("GPL v2");
