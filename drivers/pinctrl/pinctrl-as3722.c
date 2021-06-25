<शैली गुरु>
/*
 * ams AS3722 pin control and GPIO driver.
 *
 * Copyright (c) 2013, NVIDIA Corporation.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/as3722.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>

#समावेश "core.h"
#समावेश "pinconf.h"
#समावेश "pinctrl-utils.h"

#घोषणा AS3722_PIN_GPIO0		0
#घोषणा AS3722_PIN_GPIO1		1
#घोषणा AS3722_PIN_GPIO2		2
#घोषणा AS3722_PIN_GPIO3		3
#घोषणा AS3722_PIN_GPIO4		4
#घोषणा AS3722_PIN_GPIO5		5
#घोषणा AS3722_PIN_GPIO6		6
#घोषणा AS3722_PIN_GPIO7		7
#घोषणा AS3722_PIN_NUM			(AS3722_PIN_GPIO7 + 1)

#घोषणा AS3722_GPIO_MODE_PULL_UP           BIT(PIN_CONFIG_BIAS_PULL_UP)
#घोषणा AS3722_GPIO_MODE_PULL_DOWN         BIT(PIN_CONFIG_BIAS_PULL_DOWN)
#घोषणा AS3722_GPIO_MODE_HIGH_IMPED        BIT(PIN_CONFIG_BIAS_HIGH_IMPEDANCE)
#घोषणा AS3722_GPIO_MODE_OPEN_DRAIN        BIT(PIN_CONFIG_DRIVE_OPEN_DRAIN)

काष्ठा as3722_pin_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित ngroups;
	पूर्णांक mux_option;
पूर्ण;

काष्ठा as3722_gpio_pin_control अणु
	अचिन्हित mode_prop;
	पूर्णांक io_function;
पूर्ण;

काष्ठा as3722_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित pins[1];
	अचिन्हित npins;
पूर्ण;

काष्ठा as3722_pctrl_info अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
	काष्ठा as3722 *as3722;
	काष्ठा gpio_chip gpio_chip;
	पूर्णांक pins_current_opt[AS3722_PIN_NUM];
	स्थिर काष्ठा as3722_pin_function *functions;
	अचिन्हित num_functions;
	स्थिर काष्ठा as3722_pingroup *pin_groups;
	पूर्णांक num_pin_groups;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित num_pins;
	काष्ठा as3722_gpio_pin_control gpio_control[AS3722_PIN_NUM];
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc as3722_pins_desc[] = अणु
	PINCTRL_PIN(AS3722_PIN_GPIO0, "gpio0"),
	PINCTRL_PIN(AS3722_PIN_GPIO1, "gpio1"),
	PINCTRL_PIN(AS3722_PIN_GPIO2, "gpio2"),
	PINCTRL_PIN(AS3722_PIN_GPIO3, "gpio3"),
	PINCTRL_PIN(AS3722_PIN_GPIO4, "gpio4"),
	PINCTRL_PIN(AS3722_PIN_GPIO5, "gpio5"),
	PINCTRL_PIN(AS3722_PIN_GPIO6, "gpio6"),
	PINCTRL_PIN(AS3722_PIN_GPIO7, "gpio7"),
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpio_groups[] = अणु
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
पूर्ण;

क्रमागत as3722_pinmux_option अणु
	AS3722_PINMUX_GPIO			= 0,
	AS3722_PINMUX_INTERRUPT_OUT		= 1,
	AS3722_PINMUX_VSUB_VBAT_UNDEB_LOW_OUT	= 2,
	AS3722_PINMUX_GPIO_INTERRUPT		= 3,
	AS3722_PINMUX_PWM_INPUT			= 4,
	AS3722_PINMUX_VOLTAGE_IN_STBY		= 5,
	AS3722_PINMUX_OC_PG_SD0			= 6,
	AS3722_PINMUX_PG_OUT			= 7,
	AS3722_PINMUX_CLK32K_OUT		= 8,
	AS3722_PINMUX_WATCHDOG_INPUT		= 9,
	AS3722_PINMUX_SOFT_RESET_IN		= 11,
	AS3722_PINMUX_PWM_OUTPUT		= 12,
	AS3722_PINMUX_VSUB_VBAT_LOW_DEB_OUT	= 13,
	AS3722_PINMUX_OC_PG_SD6			= 14,
पूर्ण;

#घोषणा FUNCTION_GROUP(fname, mux)			\
	अणु						\
		.name = #fname,				\
		.groups = gpio_groups,			\
		.ngroups = ARRAY_SIZE(gpio_groups),	\
		.mux_option = AS3722_PINMUX_##mux,	\
	पूर्ण

अटल स्थिर काष्ठा as3722_pin_function as3722_pin_function[] = अणु
	FUNCTION_GROUP(gpio, GPIO),
	FUNCTION_GROUP(पूर्णांकerrupt-out, INTERRUPT_OUT),
	FUNCTION_GROUP(gpio-in-पूर्णांकerrupt, GPIO_INTERRUPT),
	FUNCTION_GROUP(vsup-vbat-low-undebounce-out, VSUB_VBAT_UNDEB_LOW_OUT),
	FUNCTION_GROUP(vsup-vbat-low-debounce-out, VSUB_VBAT_LOW_DEB_OUT),
	FUNCTION_GROUP(voltage-in-standby, VOLTAGE_IN_STBY),
	FUNCTION_GROUP(oc-pg-sd0, OC_PG_SD0),
	FUNCTION_GROUP(oc-pg-sd6, OC_PG_SD6),
	FUNCTION_GROUP(घातergood-out, PG_OUT),
	FUNCTION_GROUP(pwm-in, PWM_INPUT),
	FUNCTION_GROUP(pwm-out, PWM_OUTPUT),
	FUNCTION_GROUP(clk32k-out, CLK32K_OUT),
	FUNCTION_GROUP(watchकरोg-in, WATCHDOG_INPUT),
	FUNCTION_GROUP(soft-reset-in, SOFT_RESET_IN),
पूर्ण;

#घोषणा AS3722_PINGROUP(pg_name, pin_id) \
	अणु								\
		.name = #pg_name,					\
		.pins = अणुAS3722_PIN_##pin_idपूर्ण,				\
		.npins = 1,						\
	पूर्ण

अटल स्थिर काष्ठा as3722_pingroup as3722_pingroups[] = अणु
	AS3722_PINGROUP(gpio0,	GPIO0),
	AS3722_PINGROUP(gpio1,	GPIO1),
	AS3722_PINGROUP(gpio2,	GPIO2),
	AS3722_PINGROUP(gpio3,	GPIO3),
	AS3722_PINGROUP(gpio4,	GPIO4),
	AS3722_PINGROUP(gpio5,	GPIO5),
	AS3722_PINGROUP(gpio6,	GPIO6),
	AS3722_PINGROUP(gpio7,	GPIO7),
पूर्ण;

अटल पूर्णांक as3722_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);

	वापस as_pci->num_pin_groups;
पूर्ण

अटल स्थिर अक्षर *as3722_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित group)
अणु
	काष्ठा as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);

	वापस as_pci->pin_groups[group].name;
पूर्ण

अटल पूर्णांक as3722_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित group, स्थिर अचिन्हित **pins, अचिन्हित *num_pins)
अणु
	काष्ठा as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);

	*pins = as_pci->pin_groups[group].pins;
	*num_pins = as_pci->pin_groups[group].npins;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops as3722_pinctrl_ops = अणु
	.get_groups_count = as3722_pinctrl_get_groups_count,
	.get_group_name = as3722_pinctrl_get_group_name,
	.get_group_pins = as3722_pinctrl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक as3722_pinctrl_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);

	वापस as_pci->num_functions;
पूर्ण

अटल स्थिर अक्षर *as3722_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
			अचिन्हित function)
अणु
	काष्ठा as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);

	वापस as_pci->functions[function].name;
पूर्ण

अटल पूर्णांक as3722_pinctrl_get_func_groups(काष्ठा pinctrl_dev *pctldev,
		अचिन्हित function, स्थिर अक्षर * स्थिर **groups,
		अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);

	*groups = as_pci->functions[function].groups;
	*num_groups = as_pci->functions[function].ngroups;
	वापस 0;
पूर्ण

अटल पूर्णांक as3722_pinctrl_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित function,
		अचिन्हित group)
अणु
	काष्ठा as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक gpio_cntr_reg = AS3722_GPIOn_CONTROL_REG(group);
	u8 val = AS3722_GPIO_IOSF_VAL(as_pci->functions[function].mux_option);
	पूर्णांक ret;

	dev_dbg(as_pci->dev, "%s(): GPIO %u pin to function %u and val %u\n",
		__func__, group, function, val);

	ret = as3722_update_bits(as_pci->as3722, gpio_cntr_reg,
			AS3722_GPIO_IOSF_MASK, val);
	अगर (ret < 0) अणु
		dev_err(as_pci->dev, "GPIO%d_CTRL_REG update failed %d\n",
			group, ret);
		वापस ret;
	पूर्ण
	as_pci->gpio_control[group].io_function = function;

	चयन (val) अणु
	हाल AS3722_GPIO_IOSF_SD0_OUT:
	हाल AS3722_GPIO_IOSF_PWR_GOOD_OUT:
	हाल AS3722_GPIO_IOSF_Q32K_OUT:
	हाल AS3722_GPIO_IOSF_PWM_OUT:
	हाल AS3722_GPIO_IOSF_SD6_LOW_VOLT_LOW:
		ret = as3722_update_bits(as_pci->as3722, gpio_cntr_reg,
			AS3722_GPIO_MODE_MASK, AS3722_GPIO_MODE_OUTPUT_VDDH);
		अगर (ret < 0) अणु
			dev_err(as_pci->dev, "GPIO%d_CTRL update failed %d\n",
				group, ret);
			वापस ret;
		पूर्ण
		as_pci->gpio_control[group].mode_prop =
				AS3722_GPIO_MODE_OUTPUT_VDDH;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक as3722_pinctrl_gpio_get_mode(अचिन्हित gpio_mode_prop, bool input)
अणु
	अगर (gpio_mode_prop & AS3722_GPIO_MODE_HIGH_IMPED)
		वापस -EINVAL;

	अगर (gpio_mode_prop & AS3722_GPIO_MODE_OPEN_DRAIN) अणु
		अगर (gpio_mode_prop & AS3722_GPIO_MODE_PULL_UP)
			वापस AS3722_GPIO_MODE_IO_OPEN_DRAIN_PULL_UP;
		वापस AS3722_GPIO_MODE_IO_OPEN_DRAIN;
	पूर्ण
	अगर (input) अणु
		अगर (gpio_mode_prop & AS3722_GPIO_MODE_PULL_UP)
			वापस AS3722_GPIO_MODE_INPUT_PULL_UP;
		अन्यथा अगर (gpio_mode_prop & AS3722_GPIO_MODE_PULL_DOWN)
			वापस AS3722_GPIO_MODE_INPUT_PULL_DOWN;
		वापस AS3722_GPIO_MODE_INPUT;
	पूर्ण
	अगर (gpio_mode_prop & AS3722_GPIO_MODE_PULL_DOWN)
		वापस AS3722_GPIO_MODE_OUTPUT_VDDL;
	वापस AS3722_GPIO_MODE_OUTPUT_VDDH;
पूर्ण

अटल पूर्णांक as3722_pinctrl_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_gpio_range *range, अचिन्हित offset)
अणु
	काष्ठा as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);

	अगर (as_pci->gpio_control[offset].io_function)
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल पूर्णांक as3722_pinctrl_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_gpio_range *range, अचिन्हित offset, bool input)
अणु
	काष्ठा as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा as3722 *as3722 = as_pci->as3722;
	पूर्णांक mode;

	mode = as3722_pinctrl_gpio_get_mode(
			as_pci->gpio_control[offset].mode_prop, input);
	अगर (mode < 0) अणु
		dev_err(as_pci->dev, "%s direction for GPIO %d not supported\n",
			(input) ? "Input" : "Output", offset);
		वापस mode;
	पूर्ण

	वापस as3722_update_bits(as3722, AS3722_GPIOn_CONTROL_REG(offset),
				AS3722_GPIO_MODE_MASK, mode);
पूर्ण

अटल स्थिर काष्ठा pinmux_ops as3722_pinmux_ops = अणु
	.get_functions_count	= as3722_pinctrl_get_funcs_count,
	.get_function_name	= as3722_pinctrl_get_func_name,
	.get_function_groups	= as3722_pinctrl_get_func_groups,
	.set_mux		= as3722_pinctrl_set,
	.gpio_request_enable	= as3722_pinctrl_gpio_request_enable,
	.gpio_set_direction	= as3722_pinctrl_gpio_set_direction,
पूर्ण;

अटल पूर्णांक as3722_pinconf_get(काष्ठा pinctrl_dev *pctldev,
			अचिन्हित pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	पूर्णांक arg = 0;
	u16 prop;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		prop = AS3722_GPIO_MODE_PULL_UP |
				AS3722_GPIO_MODE_PULL_DOWN;
		अगर (!(as_pci->gpio_control[pin].mode_prop & prop))
			arg = 1;
		prop = 0;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		prop = AS3722_GPIO_MODE_PULL_UP;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		prop = AS3722_GPIO_MODE_PULL_DOWN;
		अवरोध;

	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		prop = AS3722_GPIO_MODE_OPEN_DRAIN;
		अवरोध;

	हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		prop = AS3722_GPIO_MODE_HIGH_IMPED;
		अवरोध;

	शेष:
		dev_err(as_pci->dev, "Properties not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (as_pci->gpio_control[pin].mode_prop & prop)
		arg = 1;

	*config = pinconf_to_config_packed(param, (u16)arg);
	वापस 0;
पूर्ण

अटल पूर्णांक as3722_pinconf_set(काष्ठा pinctrl_dev *pctldev,
			अचिन्हित pin, अचिन्हित दीर्घ *configs,
			अचिन्हित num_configs)
अणु
	काष्ठा as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param;
	पूर्णांक mode_prop;
	पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		mode_prop = as_pci->gpio_control[pin].mode_prop;

		चयन (param) अणु
		हाल PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
			अवरोध;

		हाल PIN_CONFIG_BIAS_DISABLE:
			mode_prop &= ~(AS3722_GPIO_MODE_PULL_UP |
					AS3722_GPIO_MODE_PULL_DOWN);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			mode_prop |= AS3722_GPIO_MODE_PULL_UP;
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			mode_prop |= AS3722_GPIO_MODE_PULL_DOWN;
			अवरोध;

		हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			mode_prop |= AS3722_GPIO_MODE_HIGH_IMPED;
			अवरोध;

		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
			mode_prop |= AS3722_GPIO_MODE_OPEN_DRAIN;
			अवरोध;

		शेष:
			dev_err(as_pci->dev, "Properties not supported\n");
			वापस -ENOTSUPP;
		पूर्ण

		as_pci->gpio_control[pin].mode_prop = mode_prop;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops as3722_pinconf_ops = अणु
	.pin_config_get = as3722_pinconf_get,
	.pin_config_set = as3722_pinconf_set,
पूर्ण;

अटल काष्ठा pinctrl_desc as3722_pinctrl_desc = अणु
	.pctlops = &as3722_pinctrl_ops,
	.pmxops = &as3722_pinmux_ops,
	.confops = &as3722_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक as3722_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा as3722_pctrl_info *as_pci = gpiochip_get_data(chip);
	काष्ठा as3722 *as3722 = as_pci->as3722;
	पूर्णांक ret;
	u32 reg;
	u32 control;
	u32 val;
	पूर्णांक mode;
	पूर्णांक invert_enable;

	ret = as3722_पढ़ो(as3722, AS3722_GPIOn_CONTROL_REG(offset), &control);
	अगर (ret < 0) अणु
		dev_err(as_pci->dev,
			"GPIO_CONTROL%d_REG read failed: %d\n", offset, ret);
		वापस ret;
	पूर्ण

	invert_enable = !!(control & AS3722_GPIO_INV);
	mode = control & AS3722_GPIO_MODE_MASK;
	चयन (mode) अणु
	हाल AS3722_GPIO_MODE_INPUT:
	हाल AS3722_GPIO_MODE_INPUT_PULL_UP:
	हाल AS3722_GPIO_MODE_INPUT_PULL_DOWN:
	हाल AS3722_GPIO_MODE_IO_OPEN_DRAIN:
	हाल AS3722_GPIO_MODE_IO_OPEN_DRAIN_PULL_UP:
		reg = AS3722_GPIO_SIGNAL_IN_REG;
		अवरोध;
	हाल AS3722_GPIO_MODE_OUTPUT_VDDH:
	हाल AS3722_GPIO_MODE_OUTPUT_VDDL:
		reg = AS3722_GPIO_SIGNAL_OUT_REG;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = as3722_पढ़ो(as3722, reg, &val);
	अगर (ret < 0) अणु
		dev_err(as_pci->dev,
			"GPIO_SIGNAL_IN_REG read failed: %d\n", ret);
		वापस ret;
	पूर्ण

	val = !!(val & AS3722_GPIOn_SIGNAL(offset));
	वापस (invert_enable) ? !val : val;
पूर्ण

अटल व्योम as3722_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset,
		पूर्णांक value)
अणु
	काष्ठा as3722_pctrl_info *as_pci = gpiochip_get_data(chip);
	काष्ठा as3722 *as3722 = as_pci->as3722;
	पूर्णांक en_invert;
	u32 val;
	पूर्णांक ret;

	ret = as3722_पढ़ो(as3722, AS3722_GPIOn_CONTROL_REG(offset), &val);
	अगर (ret < 0) अणु
		dev_err(as_pci->dev,
			"GPIO_CONTROL%d_REG read failed: %d\n", offset, ret);
		वापस;
	पूर्ण
	en_invert = !!(val & AS3722_GPIO_INV);

	अगर (value)
		val = (en_invert) ? 0 : AS3722_GPIOn_SIGNAL(offset);
	अन्यथा
		val = (en_invert) ? AS3722_GPIOn_SIGNAL(offset) : 0;

	ret = as3722_update_bits(as3722, AS3722_GPIO_SIGNAL_OUT_REG,
			AS3722_GPIOn_SIGNAL(offset), val);
	अगर (ret < 0)
		dev_err(as_pci->dev,
			"GPIO_SIGNAL_OUT_REG update failed: %d\n", ret);
पूर्ण

अटल पूर्णांक as3722_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + offset);
पूर्ण

अटल पूर्णांक as3722_gpio_direction_output(काष्ठा gpio_chip *chip,
		अचिन्हित offset, पूर्णांक value)
अणु
	as3722_gpio_set(chip, offset, value);
	वापस pinctrl_gpio_direction_output(chip->base + offset);
पूर्ण

अटल पूर्णांक as3722_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा as3722_pctrl_info *as_pci = gpiochip_get_data(chip);

	वापस as3722_irq_get_virq(as_pci->as3722, offset);
पूर्ण

अटल स्थिर काष्ठा gpio_chip as3722_gpio_chip = अणु
	.label			= "as3722-gpio",
	.owner			= THIS_MODULE,
	.request		= gpiochip_generic_request,
	.मुक्त			= gpiochip_generic_मुक्त,
	.get			= as3722_gpio_get,
	.set			= as3722_gpio_set,
	.direction_input	= as3722_gpio_direction_input,
	.direction_output	= as3722_gpio_direction_output,
	.to_irq			= as3722_gpio_to_irq,
	.can_sleep		= true,
	.ngpio			= AS3722_PIN_NUM,
	.base			= -1,
पूर्ण;

अटल पूर्णांक as3722_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा as3722_pctrl_info *as_pci;
	पूर्णांक ret;

	as_pci = devm_kzalloc(&pdev->dev, माप(*as_pci), GFP_KERNEL);
	अगर (!as_pci)
		वापस -ENOMEM;

	as_pci->dev = &pdev->dev;
	as_pci->dev->of_node = pdev->dev.parent->of_node;
	as_pci->as3722 = dev_get_drvdata(pdev->dev.parent);
	platक्रमm_set_drvdata(pdev, as_pci);

	as_pci->pins = as3722_pins_desc;
	as_pci->num_pins = ARRAY_SIZE(as3722_pins_desc);
	as_pci->functions = as3722_pin_function;
	as_pci->num_functions = ARRAY_SIZE(as3722_pin_function);
	as_pci->pin_groups = as3722_pingroups;
	as_pci->num_pin_groups = ARRAY_SIZE(as3722_pingroups);
	as3722_pinctrl_desc.name = dev_name(&pdev->dev);
	as3722_pinctrl_desc.pins = as3722_pins_desc;
	as3722_pinctrl_desc.npins = ARRAY_SIZE(as3722_pins_desc);
	as_pci->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, &as3722_pinctrl_desc,
					     as_pci);
	अगर (IS_ERR(as_pci->pctl)) अणु
		dev_err(&pdev->dev, "Couldn't register pinctrl driver\n");
		वापस PTR_ERR(as_pci->pctl);
	पूर्ण

	as_pci->gpio_chip = as3722_gpio_chip;
	as_pci->gpio_chip.parent = &pdev->dev;
	as_pci->gpio_chip.of_node = pdev->dev.parent->of_node;
	ret = gpiochip_add_data(&as_pci->gpio_chip, as_pci);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Couldn't register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	ret = gpiochip_add_pin_range(&as_pci->gpio_chip, dev_name(&pdev->dev),
				0, 0, AS3722_PIN_NUM);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Couldn't add pin range, %d\n", ret);
		जाओ fail_range_add;
	पूर्ण

	वापस 0;

fail_range_add:
	gpiochip_हटाओ(&as_pci->gpio_chip);
	वापस ret;
पूर्ण

अटल पूर्णांक as3722_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा as3722_pctrl_info *as_pci = platक्रमm_get_drvdata(pdev);

	gpiochip_हटाओ(&as_pci->gpio_chip);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id as3722_pinctrl_of_match[] = अणु
	अणु .compatible = "ams,as3722-pinctrl", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, as3722_pinctrl_of_match);

अटल काष्ठा platक्रमm_driver as3722_pinctrl_driver = अणु
	.driver = अणु
		.name = "as3722-pinctrl",
		.of_match_table = as3722_pinctrl_of_match,
	पूर्ण,
	.probe = as3722_pinctrl_probe,
	.हटाओ = as3722_pinctrl_हटाओ,
पूर्ण;
module_platक्रमm_driver(as3722_pinctrl_driver);

MODULE_ALIAS("platform:as3722-pinctrl");
MODULE_DESCRIPTION("AS3722 pin control and GPIO driver");
MODULE_AUTHOR("Laxman Dewangan<ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
