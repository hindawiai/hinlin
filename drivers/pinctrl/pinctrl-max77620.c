<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MAX77620 pin control driver.
 *
 * Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author:
 *	Chaitanya Bandi <bandik@nvidia.com>
 *	Laxman Dewangan <ldewangan@nvidia.com>
 */

#समावेश <linux/mfd/max77620.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "core.h"
#समावेश "pinconf.h"
#समावेश "pinctrl-utils.h"

#घोषणा MAX77620_PIN_NUM 8

क्रमागत max77620_pin_ppdrv अणु
	MAX77620_PIN_UNCONFIG_DRV,
	MAX77620_PIN_OD_DRV,
	MAX77620_PIN_PP_DRV,
पूर्ण;

#घोषणा MAX77620_ACTIVE_FPS_SOURCE		(PIN_CONFIG_END + 1)
#घोषणा MAX77620_ACTIVE_FPS_POWER_ON_SLOTS	(PIN_CONFIG_END + 2)
#घोषणा MAX77620_ACTIVE_FPS_POWER_DOWN_SLOTS	(PIN_CONFIG_END + 3)
#घोषणा MAX77620_SUSPEND_FPS_SOURCE		(PIN_CONFIG_END + 4)
#घोषणा MAX77620_SUSPEND_FPS_POWER_ON_SLOTS	(PIN_CONFIG_END + 5)
#घोषणा MAX77620_SUSPEND_FPS_POWER_DOWN_SLOTS	(PIN_CONFIG_END + 6)

काष्ठा max77620_pin_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित पूर्णांक ngroups;
	पूर्णांक mux_option;
पूर्ण;

अटल स्थिर काष्ठा pinconf_generic_params max77620_cfg_params[] = अणु
	अणु
		.property = "maxim,active-fps-source",
		.param = MAX77620_ACTIVE_FPS_SOURCE,
	पूर्ण, अणु
		.property = "maxim,active-fps-power-up-slot",
		.param = MAX77620_ACTIVE_FPS_POWER_ON_SLOTS,
	पूर्ण, अणु
		.property = "maxim,active-fps-power-down-slot",
		.param = MAX77620_ACTIVE_FPS_POWER_DOWN_SLOTS,
	पूर्ण, अणु
		.property = "maxim,suspend-fps-source",
		.param = MAX77620_SUSPEND_FPS_SOURCE,
	पूर्ण, अणु
		.property = "maxim,suspend-fps-power-up-slot",
		.param = MAX77620_SUSPEND_FPS_POWER_ON_SLOTS,
	पूर्ण, अणु
		.property = "maxim,suspend-fps-power-down-slot",
		.param = MAX77620_SUSPEND_FPS_POWER_DOWN_SLOTS,
	पूर्ण,
पूर्ण;

क्रमागत max77620_alternate_pinmux_option अणु
	MAX77620_PINMUX_GPIO				= 0,
	MAX77620_PINMUX_LOW_POWER_MODE_CONTROL_IN	= 1,
	MAX77620_PINMUX_FLEXIBLE_POWER_SEQUENCER_OUT	= 2,
	MAX77620_PINMUX_32K_OUT1			= 3,
	MAX77620_PINMUX_SD0_DYNAMIC_VOLTAGE_SCALING_IN	= 4,
	MAX77620_PINMUX_SD1_DYNAMIC_VOLTAGE_SCALING_IN	= 5,
	MAX77620_PINMUX_REFERENCE_OUT			= 6,
पूर्ण;

काष्ठा max77620_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक pins[1];
	अचिन्हित पूर्णांक npins;
	क्रमागत max77620_alternate_pinmux_option alt_option;
पूर्ण;

काष्ठा max77620_pin_info अणु
	क्रमागत max77620_pin_ppdrv drv_type;
	पूर्णांक pull_config;
पूर्ण;

काष्ठा max77620_fps_config अणु
	पूर्णांक active_fps_src;
	पूर्णांक active_घातer_up_slots;
	पूर्णांक active_घातer_करोwn_slots;
	पूर्णांक suspend_fps_src;
	पूर्णांक suspend_घातer_up_slots;
	पूर्णांक suspend_घातer_करोwn_slots;
पूर्ण;

काष्ठा max77620_pctrl_info अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
	काष्ठा regmap *rmap;
	पूर्णांक pins_current_opt[MAX77620_GPIO_NR];
	स्थिर काष्ठा max77620_pin_function *functions;
	अचिन्हित पूर्णांक num_functions;
	स्थिर काष्ठा max77620_pingroup *pin_groups;
	पूर्णांक num_pin_groups;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक num_pins;
	काष्ठा max77620_pin_info pin_info[MAX77620_PIN_NUM];
	काष्ठा max77620_fps_config fps_config[MAX77620_PIN_NUM];
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc max77620_pins_desc[] = अणु
	PINCTRL_PIN(MAX77620_GPIO0, "gpio0"),
	PINCTRL_PIN(MAX77620_GPIO1, "gpio1"),
	PINCTRL_PIN(MAX77620_GPIO2, "gpio2"),
	PINCTRL_PIN(MAX77620_GPIO3, "gpio3"),
	PINCTRL_PIN(MAX77620_GPIO4, "gpio4"),
	PINCTRL_PIN(MAX77620_GPIO5, "gpio5"),
	PINCTRL_PIN(MAX77620_GPIO6, "gpio6"),
	PINCTRL_PIN(MAX77620_GPIO7, "gpio7"),
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

#घोषणा FUNCTION_GROUP(fname, mux)			\
	अणु						\
		.name = fname,				\
		.groups = gpio_groups,			\
		.ngroups = ARRAY_SIZE(gpio_groups),	\
		.mux_option = MAX77620_PINMUX_##mux,	\
	पूर्ण

अटल स्थिर काष्ठा max77620_pin_function max77620_pin_function[] = अणु
	FUNCTION_GROUP("gpio", GPIO),
	FUNCTION_GROUP("lpm-control-in", LOW_POWER_MODE_CONTROL_IN),
	FUNCTION_GROUP("fps-out", FLEXIBLE_POWER_SEQUENCER_OUT),
	FUNCTION_GROUP("32k-out1", 32K_OUT1),
	FUNCTION_GROUP("sd0-dvs-in", SD0_DYNAMIC_VOLTAGE_SCALING_IN),
	FUNCTION_GROUP("sd1-dvs-in", SD1_DYNAMIC_VOLTAGE_SCALING_IN),
	FUNCTION_GROUP("reference-out", REFERENCE_OUT),
पूर्ण;

#घोषणा MAX77620_PINGROUP(pg_name, pin_id, option) \
	अणु								\
		.name = #pg_name,					\
		.pins = अणुMAX77620_##pin_idपूर्ण,				\
		.npins = 1,						\
		.alt_option = MAX77620_PINMUX_##option,			\
	पूर्ण

अटल स्थिर काष्ठा max77620_pingroup max77620_pingroups[] = अणु
	MAX77620_PINGROUP(gpio0, GPIO0, LOW_POWER_MODE_CONTROL_IN),
	MAX77620_PINGROUP(gpio1, GPIO1, FLEXIBLE_POWER_SEQUENCER_OUT),
	MAX77620_PINGROUP(gpio2, GPIO2, FLEXIBLE_POWER_SEQUENCER_OUT),
	MAX77620_PINGROUP(gpio3, GPIO3, FLEXIBLE_POWER_SEQUENCER_OUT),
	MAX77620_PINGROUP(gpio4, GPIO4, 32K_OUT1),
	MAX77620_PINGROUP(gpio5, GPIO5, SD0_DYNAMIC_VOLTAGE_SCALING_IN),
	MAX77620_PINGROUP(gpio6, GPIO6, SD1_DYNAMIC_VOLTAGE_SCALING_IN),
	MAX77620_PINGROUP(gpio7, GPIO7, REFERENCE_OUT),
पूर्ण;

अटल पूर्णांक max77620_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा max77620_pctrl_info *mpci = pinctrl_dev_get_drvdata(pctldev);

	वापस mpci->num_pin_groups;
पूर्ण

अटल स्थिर अक्षर *max77620_pinctrl_get_group_name(
		काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक group)
अणु
	काष्ठा max77620_pctrl_info *mpci = pinctrl_dev_get_drvdata(pctldev);

	वापस mpci->pin_groups[group].name;
पूर्ण

अटल पूर्णांक max77620_pinctrl_get_group_pins(
		काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक group,
		स्थिर अचिन्हित पूर्णांक **pins, अचिन्हित पूर्णांक *num_pins)
अणु
	काष्ठा max77620_pctrl_info *mpci = pinctrl_dev_get_drvdata(pctldev);

	*pins = mpci->pin_groups[group].pins;
	*num_pins = mpci->pin_groups[group].npins;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops max77620_pinctrl_ops = अणु
	.get_groups_count = max77620_pinctrl_get_groups_count,
	.get_group_name = max77620_pinctrl_get_group_name,
	.get_group_pins = max77620_pinctrl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक max77620_pinctrl_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा max77620_pctrl_info *mpci = pinctrl_dev_get_drvdata(pctldev);

	वापस mpci->num_functions;
पूर्ण

अटल स्थिर अक्षर *max77620_pinctrl_get_func_name(काष्ठा pinctrl_dev *pctldev,
						  अचिन्हित पूर्णांक function)
अणु
	काष्ठा max77620_pctrl_info *mpci = pinctrl_dev_get_drvdata(pctldev);

	वापस mpci->functions[function].name;
पूर्ण

अटल पूर्णांक max77620_pinctrl_get_func_groups(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित पूर्णांक function,
					    स्थिर अक्षर * स्थिर **groups,
					    अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	काष्ठा max77620_pctrl_info *mpci = pinctrl_dev_get_drvdata(pctldev);

	*groups = mpci->functions[function].groups;
	*num_groups = mpci->functions[function].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_pinctrl_enable(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक function, अचिन्हित पूर्णांक group)
अणु
	काष्ठा max77620_pctrl_info *mpci = pinctrl_dev_get_drvdata(pctldev);
	u8 val;
	पूर्णांक ret;

	अगर (function == MAX77620_PINMUX_GPIO) अणु
		val = 0;
	पूर्ण अन्यथा अगर (function == mpci->pin_groups[group].alt_option) अणु
		val = 1 << group;
	पूर्ण अन्यथा अणु
		dev_err(mpci->dev, "GPIO %u doesn't have function %u\n",
			group, function);
		वापस -EINVAL;
	पूर्ण
	ret = regmap_update_bits(mpci->rmap, MAX77620_REG_AME_GPIO,
				 BIT(group), val);
	अगर (ret < 0)
		dev_err(mpci->dev, "REG AME GPIO update failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops max77620_pinmux_ops = अणु
	.get_functions_count	= max77620_pinctrl_get_funcs_count,
	.get_function_name	= max77620_pinctrl_get_func_name,
	.get_function_groups	= max77620_pinctrl_get_func_groups,
	.set_mux		= max77620_pinctrl_enable,
पूर्ण;

अटल पूर्णांक max77620_pinconf_get(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *config)
अणु
	काष्ठा max77620_pctrl_info *mpci = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा device *dev = mpci->dev;
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	अचिन्हित पूर्णांक val;
	पूर्णांक arg = 0;
	पूर्णांक ret;

	चयन (param) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		अगर (mpci->pin_info[pin].drv_type == MAX77620_PIN_OD_DRV)
			arg = 1;
		अवरोध;

	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		अगर (mpci->pin_info[pin].drv_type == MAX77620_PIN_PP_DRV)
			arg = 1;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		ret = regmap_पढ़ो(mpci->rmap, MAX77620_REG_PUE_GPIO, &val);
		अगर (ret < 0) अणु
			dev_err(dev, "Reg PUE_GPIO read failed: %d\n", ret);
			वापस ret;
		पूर्ण
		अगर (val & BIT(pin))
			arg = 1;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		ret = regmap_पढ़ो(mpci->rmap, MAX77620_REG_PDE_GPIO, &val);
		अगर (ret < 0) अणु
			dev_err(dev, "Reg PDE_GPIO read failed: %d\n", ret);
			वापस ret;
		पूर्ण
		अगर (val & BIT(pin))
			arg = 1;
		अवरोध;

	शेष:
		dev_err(dev, "Properties not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, (u16)arg);

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_get_शेष_fps(काष्ठा max77620_pctrl_info *mpci,
				    पूर्णांक addr, पूर्णांक *fps)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(mpci->rmap, addr, &val);
	अगर (ret < 0) अणु
		dev_err(mpci->dev, "Reg PUE_GPIO read failed: %d\n", ret);
		वापस ret;
	पूर्ण
	*fps = (val & MAX77620_FPS_SRC_MASK) >> MAX77620_FPS_SRC_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक max77620_set_fps_param(काष्ठा max77620_pctrl_info *mpci,
				  पूर्णांक pin, पूर्णांक param)
अणु
	काष्ठा max77620_fps_config *fps_config = &mpci->fps_config[pin];
	पूर्णांक addr, ret;
	पूर्णांक param_val;
	पूर्णांक mask, shअगरt;

	अगर ((pin < MAX77620_GPIO1) || (pin > MAX77620_GPIO3))
		वापस 0;

	addr = MAX77620_REG_FPS_GPIO1 + pin - 1;
	चयन (param) अणु
	हाल MAX77620_ACTIVE_FPS_SOURCE:
	हाल MAX77620_SUSPEND_FPS_SOURCE:
		mask = MAX77620_FPS_SRC_MASK;
		shअगरt = MAX77620_FPS_SRC_SHIFT;
		param_val = fps_config->active_fps_src;
		अगर (param == MAX77620_SUSPEND_FPS_SOURCE)
			param_val = fps_config->suspend_fps_src;
		अवरोध;

	हाल MAX77620_ACTIVE_FPS_POWER_ON_SLOTS:
	हाल MAX77620_SUSPEND_FPS_POWER_ON_SLOTS:
		mask = MAX77620_FPS_PU_PERIOD_MASK;
		shअगरt = MAX77620_FPS_PU_PERIOD_SHIFT;
		param_val = fps_config->active_घातer_up_slots;
		अगर (param == MAX77620_SUSPEND_FPS_POWER_ON_SLOTS)
			param_val = fps_config->suspend_घातer_up_slots;
		अवरोध;

	हाल MAX77620_ACTIVE_FPS_POWER_DOWN_SLOTS:
	हाल MAX77620_SUSPEND_FPS_POWER_DOWN_SLOTS:
		mask = MAX77620_FPS_PD_PERIOD_MASK;
		shअगरt = MAX77620_FPS_PD_PERIOD_SHIFT;
		param_val = fps_config->active_घातer_करोwn_slots;
		अगर (param == MAX77620_SUSPEND_FPS_POWER_DOWN_SLOTS)
			param_val = fps_config->suspend_घातer_करोwn_slots;
		अवरोध;

	शेष:
		dev_err(mpci->dev, "Invalid parameter %d for pin %d\n",
			param, pin);
		वापस -EINVAL;
	पूर्ण

	अगर (param_val < 0)
		वापस 0;

	ret = regmap_update_bits(mpci->rmap, addr, mask, param_val << shअगरt);
	अगर (ret < 0)
		dev_err(mpci->dev, "Reg 0x%02x update failed %d\n", addr, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक max77620_pinconf_set(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *configs,
				अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा max77620_pctrl_info *mpci = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा device *dev = mpci->dev;
	काष्ठा max77620_fps_config *fps_config;
	पूर्णांक param;
	u32 param_val;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक pu_val;
	अचिन्हित पूर्णांक pd_val;
	पूर्णांक addr, ret;
	पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		param_val = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
			val = param_val ? 0 : 1;
			ret = regmap_update_bits(mpci->rmap,
						 MAX77620_REG_GPIO0 + pin,
						 MAX77620_CNFG_GPIO_DRV_MASK,
						 val);
			अगर (ret)
				जाओ report_update_failure;

			mpci->pin_info[pin].drv_type = val ?
				MAX77620_PIN_PP_DRV : MAX77620_PIN_OD_DRV;
			अवरोध;

		हाल PIN_CONFIG_DRIVE_PUSH_PULL:
			val = param_val ? 1 : 0;
			ret = regmap_update_bits(mpci->rmap,
						 MAX77620_REG_GPIO0 + pin,
						 MAX77620_CNFG_GPIO_DRV_MASK,
						 val);
			अगर (ret)
				जाओ report_update_failure;

			mpci->pin_info[pin].drv_type = val ?
				MAX77620_PIN_PP_DRV : MAX77620_PIN_OD_DRV;
			अवरोध;

		हाल MAX77620_ACTIVE_FPS_SOURCE:
		हाल MAX77620_ACTIVE_FPS_POWER_ON_SLOTS:
		हाल MAX77620_ACTIVE_FPS_POWER_DOWN_SLOTS:
			अगर ((pin < MAX77620_GPIO1) || (pin > MAX77620_GPIO3))
				वापस -EINVAL;

			fps_config = &mpci->fps_config[pin];

			अगर ((param == MAX77620_ACTIVE_FPS_SOURCE) &&
			    (param_val == MAX77620_FPS_SRC_DEF)) अणु
				addr = MAX77620_REG_FPS_GPIO1 + pin - 1;
				ret = max77620_get_शेष_fps(
						mpci, addr,
						&fps_config->active_fps_src);
				अगर (ret < 0)
					वापस ret;
				अवरोध;
			पूर्ण

			अगर (param == MAX77620_ACTIVE_FPS_SOURCE)
				fps_config->active_fps_src = param_val;
			अन्यथा अगर (param == MAX77620_ACTIVE_FPS_POWER_ON_SLOTS)
				fps_config->active_घातer_up_slots = param_val;
			अन्यथा
				fps_config->active_घातer_करोwn_slots = param_val;

			ret = max77620_set_fps_param(mpci, pin, param);
			अगर (ret < 0)
				वापस ret;
			अवरोध;

		हाल MAX77620_SUSPEND_FPS_SOURCE:
		हाल MAX77620_SUSPEND_FPS_POWER_ON_SLOTS:
		हाल MAX77620_SUSPEND_FPS_POWER_DOWN_SLOTS:
			अगर ((pin < MAX77620_GPIO1) || (pin > MAX77620_GPIO3))
				वापस -EINVAL;

			fps_config = &mpci->fps_config[pin];

			अगर ((param == MAX77620_SUSPEND_FPS_SOURCE) &&
			    (param_val == MAX77620_FPS_SRC_DEF)) अणु
				addr = MAX77620_REG_FPS_GPIO1 + pin - 1;
				ret = max77620_get_शेष_fps(
						mpci, addr,
						&fps_config->suspend_fps_src);
				अगर (ret < 0)
					वापस ret;
				अवरोध;
			पूर्ण

			अगर (param == MAX77620_SUSPEND_FPS_SOURCE)
				fps_config->suspend_fps_src = param_val;
			अन्यथा अगर (param == MAX77620_SUSPEND_FPS_POWER_ON_SLOTS)
				fps_config->suspend_घातer_up_slots = param_val;
			अन्यथा
				fps_config->suspend_घातer_करोwn_slots =
								param_val;
			अवरोध;

		हाल PIN_CONFIG_BIAS_PULL_UP:
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			pu_val = (param == PIN_CONFIG_BIAS_PULL_UP) ?
							BIT(pin) : 0;
			pd_val = (param == PIN_CONFIG_BIAS_PULL_DOWN) ?
							BIT(pin) : 0;

			ret = regmap_update_bits(mpci->rmap,
						 MAX77620_REG_PUE_GPIO,
						 BIT(pin), pu_val);
			अगर (ret < 0) अणु
				dev_err(dev, "PUE_GPIO update failed: %d\n",
					ret);
				वापस ret;
			पूर्ण

			ret = regmap_update_bits(mpci->rmap,
						 MAX77620_REG_PDE_GPIO,
						 BIT(pin), pd_val);
			अगर (ret < 0) अणु
				dev_err(dev, "PDE_GPIO update failed: %d\n",
					ret);
				वापस ret;
			पूर्ण
			अवरोध;

		शेष:
			dev_err(dev, "Properties not supported\n");
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;

report_update_failure:
	dev_err(dev, "Reg 0x%02x update failed %d\n",
		MAX77620_REG_GPIO0 + pin, ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops max77620_pinconf_ops = अणु
	.pin_config_get = max77620_pinconf_get,
	.pin_config_set = max77620_pinconf_set,
पूर्ण;

अटल काष्ठा pinctrl_desc max77620_pinctrl_desc = अणु
	.pctlops = &max77620_pinctrl_ops,
	.pmxops = &max77620_pinmux_ops,
	.confops = &max77620_pinconf_ops,
पूर्ण;

अटल पूर्णांक max77620_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77620_chip *max77620 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max77620_pctrl_info *mpci;
	पूर्णांक i;

	mpci = devm_kzalloc(&pdev->dev, माप(*mpci), GFP_KERNEL);
	अगर (!mpci)
		वापस -ENOMEM;

	mpci->dev = &pdev->dev;
	mpci->dev->of_node = pdev->dev.parent->of_node;
	mpci->rmap = max77620->rmap;

	mpci->pins = max77620_pins_desc;
	mpci->num_pins = ARRAY_SIZE(max77620_pins_desc);
	mpci->functions = max77620_pin_function;
	mpci->num_functions = ARRAY_SIZE(max77620_pin_function);
	mpci->pin_groups = max77620_pingroups;
	mpci->num_pin_groups = ARRAY_SIZE(max77620_pingroups);
	platक्रमm_set_drvdata(pdev, mpci);

	max77620_pinctrl_desc.name = dev_name(&pdev->dev);
	max77620_pinctrl_desc.pins = max77620_pins_desc;
	max77620_pinctrl_desc.npins = ARRAY_SIZE(max77620_pins_desc);
	max77620_pinctrl_desc.num_custom_params =
				ARRAY_SIZE(max77620_cfg_params);
	max77620_pinctrl_desc.custom_params = max77620_cfg_params;

	क्रम (i = 0; i < MAX77620_PIN_NUM; ++i) अणु
		mpci->fps_config[i].active_fps_src = -1;
		mpci->fps_config[i].active_घातer_up_slots = -1;
		mpci->fps_config[i].active_घातer_करोwn_slots = -1;
		mpci->fps_config[i].suspend_fps_src = -1;
		mpci->fps_config[i].suspend_घातer_up_slots = -1;
		mpci->fps_config[i].suspend_घातer_करोwn_slots = -1;
	पूर्ण

	mpci->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, &max77620_pinctrl_desc,
					   mpci);
	अगर (IS_ERR(mpci->pctl)) अणु
		dev_err(&pdev->dev, "Couldn't register pinctrl driver\n");
		वापस PTR_ERR(mpci->pctl);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max77620_suspend_fps_param[] = अणु
	MAX77620_SUSPEND_FPS_SOURCE,
	MAX77620_SUSPEND_FPS_POWER_ON_SLOTS,
	MAX77620_SUSPEND_FPS_POWER_DOWN_SLOTS,
पूर्ण;

अटल पूर्णांक max77620_active_fps_param[] = अणु
	MAX77620_ACTIVE_FPS_SOURCE,
	MAX77620_ACTIVE_FPS_POWER_ON_SLOTS,
	MAX77620_ACTIVE_FPS_POWER_DOWN_SLOTS,
पूर्ण;

अटल पूर्णांक max77620_pinctrl_suspend(काष्ठा device *dev)
अणु
	काष्ठा max77620_pctrl_info *mpci = dev_get_drvdata(dev);
	पूर्णांक pin, p;

	क्रम (pin = 0; pin < MAX77620_PIN_NUM; ++pin) अणु
		अगर ((pin < MAX77620_GPIO1) || (pin > MAX77620_GPIO3))
			जारी;
		क्रम (p = 0; p < 3; ++p)
			max77620_set_fps_param(
				mpci, pin, max77620_suspend_fps_param[p]);
	पूर्ण

	वापस 0;
पूर्ण;

अटल पूर्णांक max77620_pinctrl_resume(काष्ठा device *dev)
अणु
	काष्ठा max77620_pctrl_info *mpci = dev_get_drvdata(dev);
	पूर्णांक pin, p;

	क्रम (pin = 0; pin < MAX77620_PIN_NUM; ++pin) अणु
		अगर ((pin < MAX77620_GPIO1) || (pin > MAX77620_GPIO3))
			जारी;
		क्रम (p = 0; p < 3; ++p)
			max77620_set_fps_param(
				mpci, pin, max77620_active_fps_param[p]);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops max77620_pinctrl_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(
		max77620_pinctrl_suspend, max77620_pinctrl_resume)
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id max77620_pinctrl_devtype[] = अणु
	अणु .name = "max77620-pinctrl", पूर्ण,
	अणु .name = "max20024-pinctrl", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max77620_pinctrl_devtype);

अटल काष्ठा platक्रमm_driver max77620_pinctrl_driver = अणु
	.driver = अणु
		.name = "max77620-pinctrl",
		.pm = &max77620_pinctrl_pm_ops,
	पूर्ण,
	.probe = max77620_pinctrl_probe,
	.id_table = max77620_pinctrl_devtype,
पूर्ण;

module_platक्रमm_driver(max77620_pinctrl_driver);

MODULE_DESCRIPTION("MAX77620/MAX20024 pin control driver");
MODULE_AUTHOR("Chaitanya Bandi<bandik@nvidia.com>");
MODULE_AUTHOR("Laxman Dewangan<ldewangan@nvidia.com>");
MODULE_ALIAS("platform:max77620-pinctrl");
MODULE_LICENSE("GPL v2");
