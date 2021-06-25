<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ZynqMP pin controller
 *
 * Copyright (C) 2020 Xilinx, Inc.
 *
 * Sai Krishna Potthuri <lakshmi.sai.krishna.potthuri@xilinx.com>
 * Rajan Vaja <rajan.vaja@xilinx.com>
 */

#समावेश <dt-bindings/pinctrl/pinctrl-zynqmp.h>

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/firmware/xlnx-zynqmp.h>

#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश "core.h"
#समावेश "pinctrl-utils.h"

#घोषणा ZYNQMP_PIN_PREFIX			"MIO"
#घोषणा PINCTRL_GET_FUNC_NAME_RESP_LEN		16
#घोषणा MAX_FUNC_NAME_LEN			16
#घोषणा MAX_GROUP_PIN				50
#घोषणा MAX_PIN_GROUPS				50
#घोषणा END_OF_FUNCTIONS			"END_OF_FUNCTIONS"
#घोषणा NUM_GROUPS_PER_RESP			6

#घोषणा PINCTRL_GET_FUNC_GROUPS_RESP_LEN	12
#घोषणा PINCTRL_GET_PIN_GROUPS_RESP_LEN		12
#घोषणा NA_GROUP				0xFFFF
#घोषणा RESERVED_GROUP				0xFFFE

#घोषणा DRIVE_STRENGTH_2MA	2
#घोषणा DRIVE_STRENGTH_4MA	4
#घोषणा DRIVE_STRENGTH_8MA	8
#घोषणा DRIVE_STRENGTH_12MA	12

/**
 * काष्ठा zynqmp_pmux_function - a pinmux function
 * @name:	Name of the pin mux function
 * @groups:	List of pin groups क्रम this function
 * @ngroups:	Number of entries in @groups
 * @node:	Firmware node matching with the function
 *
 * This काष्ठाure holds inक्रमmation about pin control function
 * and function group names supporting that function.
 */
काष्ठा zynqmp_pmux_function अणु
	अक्षर name[MAX_FUNC_NAME_LEN];
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित पूर्णांक ngroups;
पूर्ण;

/**
 * काष्ठा zynqmp_pinctrl - driver data
 * @pctrl:	Pin control device
 * @groups:	Pin groups
 * @ngroups:	Number of @groups
 * @funcs:	Pin mux functions
 * @nfuncs:	Number of @funcs
 *
 * This काष्ठा is stored as driver data and used to retrieve
 * inक्रमmation regarding pin control functions, groups and
 * group pins.
 */
काष्ठा zynqmp_pinctrl अणु
	काष्ठा pinctrl_dev *pctrl;
	स्थिर काष्ठा zynqmp_pctrl_group *groups;
	अचिन्हित पूर्णांक ngroups;
	स्थिर काष्ठा zynqmp_pmux_function *funcs;
	अचिन्हित पूर्णांक nfuncs;
पूर्ण;

/**
 * काष्ठा zynqmp_pctrl_group - Pin control group info
 * @name:	Group name
 * @pins:	Group pin numbers
 * @npins:	Number of pins in the group
 */
काष्ठा zynqmp_pctrl_group अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक pins[MAX_GROUP_PIN];
	अचिन्हित पूर्णांक npins;
पूर्ण;

अटल काष्ठा pinctrl_desc zynqmp_desc;

अटल पूर्णांक zynqmp_pctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा zynqmp_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->ngroups;
पूर्ण

अटल स्थिर अक्षर *zynqmp_pctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					       अचिन्हित पूर्णांक selector)
अणु
	काष्ठा zynqmp_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->groups[selector].name;
पूर्ण

अटल पूर्णांक zynqmp_pctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित पूर्णांक selector,
				       स्थिर अचिन्हित पूर्णांक **pins,
				       अचिन्हित पूर्णांक *npins)
अणु
	काष्ठा zynqmp_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*pins = pctrl->groups[selector].pins;
	*npins = pctrl->groups[selector].npins;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops zynqmp_pctrl_ops = अणु
	.get_groups_count = zynqmp_pctrl_get_groups_count,
	.get_group_name = zynqmp_pctrl_get_group_name,
	.get_group_pins = zynqmp_pctrl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_all,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक zynqmp_pinmux_request_pin(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक pin)
अणु
	पूर्णांक ret;

	ret = zynqmp_pm_pinctrl_request(pin);
	अगर (ret) अणु
		dev_err(pctldev->dev, "request failed for pin %u\n", pin);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zynqmp_pmux_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा zynqmp_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->nfuncs;
पूर्ण

अटल स्थिर अक्षर *zynqmp_pmux_get_function_name(काष्ठा pinctrl_dev *pctldev,
						 अचिन्हित पूर्णांक selector)
अणु
	काष्ठा zynqmp_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->funcs[selector].name;
पूर्ण

/**
 * zynqmp_pmux_get_function_groups() - Get groups क्रम the function
 * @pctldev:	Pincontrol device poपूर्णांकer.
 * @selector:	Function ID
 * @groups:	Group names.
 * @num_groups:	Number of function groups.
 *
 * Get function's group count and group names.
 */
अटल पूर्णांक zynqmp_pmux_get_function_groups(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक selector,
					   स्थिर अक्षर * स्थिर **groups,
					   अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा zynqmp_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctrl->funcs[selector].groups;
	*num_groups = pctrl->funcs[selector].ngroups;

	वापस 0;
पूर्ण

/**
 * zynqmp_pinmux_set_mux() - Set requested function क्रम the group
 * @pctldev:	Pincontrol device poपूर्णांकer.
 * @function:	Function ID.
 * @group:	Group ID.
 *
 * Loop through all pins of the group and call firmware API
 * to set requested function क्रम all pins in the group.
 *
 * Return: 0 on success अन्यथा error code.
 */
अटल पूर्णांक zynqmp_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक function,
				 अचिन्हित पूर्णांक group)
अणु
	काष्ठा zynqmp_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा zynqmp_pctrl_group *pgrp = &pctrl->groups[group];
	पूर्णांक ret, i;

	क्रम (i = 0; i < pgrp->npins; i++) अणु
		अचिन्हित पूर्णांक pin = pgrp->pins[i];

		ret = zynqmp_pm_pinctrl_set_function(pin, function);
		अगर (ret) अणु
			dev_err(pctldev->dev, "set mux failed for pin %u\n",
				pin);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zynqmp_pinmux_release_pin(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक pin)
अणु
	पूर्णांक ret;

	ret = zynqmp_pm_pinctrl_release(pin);
	अगर (ret) अणु
		dev_err(pctldev->dev, "free pin failed for pin %u\n",
			pin);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops zynqmp_pinmux_ops = अणु
	.request = zynqmp_pinmux_request_pin,
	.get_functions_count = zynqmp_pmux_get_functions_count,
	.get_function_name = zynqmp_pmux_get_function_name,
	.get_function_groups = zynqmp_pmux_get_function_groups,
	.set_mux = zynqmp_pinmux_set_mux,
	.मुक्त = zynqmp_pinmux_release_pin,
पूर्ण;

/**
 * zynqmp_pinconf_cfg_get() - get config value क्रम the pin
 * @pctldev:	Pin control device poपूर्णांकer.
 * @pin:	Pin number.
 * @config:	Value of config param.
 *
 * Get value of the requested configuration parameter क्रम the
 * given pin.
 *
 * Return: 0 on success अन्यथा error code.
 */
अटल पूर्णांक zynqmp_pinconf_cfg_get(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक pin,
				  अचिन्हित दीर्घ *config)
अणु
	अचिन्हित पूर्णांक arg, param = pinconf_to_config_param(*config);
	पूर्णांक ret;

	अगर (pin >= zynqmp_desc.npins)
		वापस -EOPNOTSUPP;

	चयन (param) अणु
	हाल PIN_CONFIG_SLEW_RATE:
		param = PM_PINCTRL_CONFIG_SLEW_RATE;
		ret = zynqmp_pm_pinctrl_get_config(pin, param, &arg);
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		param = PM_PINCTRL_CONFIG_PULL_CTRL;
		ret = zynqmp_pm_pinctrl_get_config(pin, param, &arg);
		अगर (arg != PM_PINCTRL_BIAS_PULL_UP)
			वापस -EINVAL;

		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		param = PM_PINCTRL_CONFIG_PULL_CTRL;
		ret = zynqmp_pm_pinctrl_get_config(pin, param, &arg);
		अगर (arg != PM_PINCTRL_BIAS_PULL_DOWN)
			वापस -EINVAL;

		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_BIAS_DISABLE:
		param = PM_PINCTRL_CONFIG_BIAS_STATUS;
		ret = zynqmp_pm_pinctrl_get_config(pin, param, &arg);
		अगर (arg != PM_PINCTRL_BIAS_DISABLE)
			वापस -EINVAL;

		arg = 1;
		अवरोध;
	हाल PIN_CONFIG_POWER_SOURCE:
		param = PM_PINCTRL_CONFIG_VOLTAGE_STATUS;
		ret = zynqmp_pm_pinctrl_get_config(pin, param, &arg);
		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		param = PM_PINCTRL_CONFIG_SCHMITT_CMOS;
		ret = zynqmp_pm_pinctrl_get_config(pin, param, &arg);
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		param = PM_PINCTRL_CONFIG_DRIVE_STRENGTH;
		ret = zynqmp_pm_pinctrl_get_config(pin, param, &arg);
		चयन (arg) अणु
		हाल PM_PINCTRL_DRIVE_STRENGTH_2MA:
			arg = DRIVE_STRENGTH_2MA;
			अवरोध;
		हाल PM_PINCTRL_DRIVE_STRENGTH_4MA:
			arg = DRIVE_STRENGTH_4MA;
			अवरोध;
		हाल PM_PINCTRL_DRIVE_STRENGTH_8MA:
			arg = DRIVE_STRENGTH_8MA;
			अवरोध;
		हाल PM_PINCTRL_DRIVE_STRENGTH_12MA:
			arg = DRIVE_STRENGTH_12MA;
			अवरोध;
		शेष:
			/* Invalid drive strength */
			dev_warn(pctldev->dev,
				 "Invalid drive strength for pin %d\n",
				 pin);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस ret;

	param = pinconf_to_config_param(*config);
	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

/**
 * zynqmp_pinconf_cfg_set() - Set requested config क्रम the pin
 * @pctldev:		Pincontrol device poपूर्णांकer.
 * @pin:		Pin number.
 * @configs:		Configuration to set.
 * @num_configs:	Number of configurations.
 *
 * Loop through all configurations and call firmware API
 * to set requested configurations क्रम the pin.
 *
 * Return: 0 on success अन्यथा error code.
 */
अटल पूर्णांक zynqmp_pinconf_cfg_set(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक pin, अचिन्हित दीर्घ *configs,
				  अचिन्हित पूर्णांक num_configs)
अणु
	पूर्णांक i, ret;

	अगर (pin >= zynqmp_desc.npins)
		वापस -EOPNOTSUPP;

	क्रम (i = 0; i < num_configs; i++) अणु
		अचिन्हित पूर्णांक param = pinconf_to_config_param(configs[i]);
		अचिन्हित पूर्णांक arg = pinconf_to_config_argument(configs[i]);
		अचिन्हित पूर्णांक value;

		चयन (param) अणु
		हाल PIN_CONFIG_SLEW_RATE:
			param = PM_PINCTRL_CONFIG_SLEW_RATE;
			ret = zynqmp_pm_pinctrl_set_config(pin, param, arg);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			param = PM_PINCTRL_CONFIG_PULL_CTRL;
			arg = PM_PINCTRL_BIAS_PULL_UP;
			ret = zynqmp_pm_pinctrl_set_config(pin, param, arg);
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			param = PM_PINCTRL_CONFIG_PULL_CTRL;
			arg = PM_PINCTRL_BIAS_PULL_DOWN;
			ret = zynqmp_pm_pinctrl_set_config(pin, param, arg);
			अवरोध;
		हाल PIN_CONFIG_BIAS_DISABLE:
			param = PM_PINCTRL_CONFIG_BIAS_STATUS;
			arg = PM_PINCTRL_BIAS_DISABLE;
			ret = zynqmp_pm_pinctrl_set_config(pin, param, arg);
			अवरोध;
		हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			param = PM_PINCTRL_CONFIG_SCHMITT_CMOS;
			ret = zynqmp_pm_pinctrl_set_config(pin, param, arg);
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			चयन (arg) अणु
			हाल DRIVE_STRENGTH_2MA:
				value = PM_PINCTRL_DRIVE_STRENGTH_2MA;
				अवरोध;
			हाल DRIVE_STRENGTH_4MA:
				value = PM_PINCTRL_DRIVE_STRENGTH_4MA;
				अवरोध;
			हाल DRIVE_STRENGTH_8MA:
				value = PM_PINCTRL_DRIVE_STRENGTH_8MA;
				अवरोध;
			हाल DRIVE_STRENGTH_12MA:
				value = PM_PINCTRL_DRIVE_STRENGTH_12MA;
				अवरोध;
			शेष:
				/* Invalid drive strength */
				dev_warn(pctldev->dev,
					 "Invalid drive strength for pin %d\n",
					 pin);
				वापस -EINVAL;
			पूर्ण

			param = PM_PINCTRL_CONFIG_DRIVE_STRENGTH;
			ret = zynqmp_pm_pinctrl_set_config(pin, param, value);
			अवरोध;
		हाल PIN_CONFIG_POWER_SOURCE:
			param = PM_PINCTRL_CONFIG_VOLTAGE_STATUS;
			ret = zynqmp_pm_pinctrl_get_config(pin, param, &value);

			अगर (arg != value)
				dev_warn(pctldev->dev,
					 "Invalid IO Standard requested for pin %d\n",
					 pin);

			अवरोध;
		हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		हाल PIN_CONFIG_MODE_LOW_POWER:
			/*
			 * These हालs are mentioned in dts but configurable
			 * रेजिस्टरs are unknown. So falling through to ignore
			 * boot समय warnings as of now.
			 */
			ret = 0;
			अवरोध;
		शेष:
			dev_warn(pctldev->dev,
				 "unsupported configuration parameter '%u'\n",
				 param);
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);
		अगर (ret)
			dev_warn(pctldev->dev,
				 "failed to set: pin %u param %u value %u\n",
				 pin, param, arg);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zynqmp_pinconf_group_set() - Set requested config क्रम the group
 * @pctldev:		Pincontrol device poपूर्णांकer.
 * @selector:		Group ID.
 * @configs:		Configuration to set.
 * @num_configs:	Number of configurations.
 *
 * Call function to set configs क्रम each pin in the group.
 *
 * Return: 0 on success अन्यथा error code.
 */
अटल पूर्णांक zynqmp_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				    अचिन्हित पूर्णांक selector,
				    अचिन्हित दीर्घ *configs,
				    अचिन्हित पूर्णांक num_configs)
अणु
	पूर्णांक i, ret;
	काष्ठा zynqmp_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा zynqmp_pctrl_group *pgrp = &pctrl->groups[selector];

	क्रम (i = 0; i < pgrp->npins; i++) अणु
		ret = zynqmp_pinconf_cfg_set(pctldev, pgrp->pins[i], configs,
					     num_configs);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops zynqmp_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = zynqmp_pinconf_cfg_get,
	.pin_config_set = zynqmp_pinconf_cfg_set,
	.pin_config_group_set = zynqmp_pinconf_group_set,
पूर्ण;

अटल काष्ठा pinctrl_desc zynqmp_desc = अणु
	.name = "zynqmp_pinctrl",
	.owner = THIS_MODULE,
	.pctlops = &zynqmp_pctrl_ops,
	.pmxops = &zynqmp_pinmux_ops,
	.confops = &zynqmp_pinconf_ops,
पूर्ण;

अटल पूर्णांक zynqmp_pinctrl_get_function_groups(u32 fid, u32 index, u16 *groups)
अणु
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	qdata.qid = PM_QID_PINCTRL_GET_FUNCTION_GROUPS;
	qdata.arg1 = fid;
	qdata.arg2 = index;

	ret = zynqmp_pm_query_data(qdata, payload);
	अगर (ret)
		वापस ret;

	स_नकल(groups, &payload[1], PINCTRL_GET_FUNC_GROUPS_RESP_LEN);

	वापस ret;
पूर्ण

अटल पूर्णांक zynqmp_pinctrl_get_func_num_groups(u32 fid, अचिन्हित पूर्णांक *ngroups)
अणु
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	qdata.qid = PM_QID_PINCTRL_GET_NUM_FUNCTION_GROUPS;
	qdata.arg1 = fid;

	ret = zynqmp_pm_query_data(qdata, payload);
	अगर (ret)
		वापस ret;

	*ngroups = payload[1];

	वापस ret;
पूर्ण

/**
 * zynqmp_pinctrl_prepare_func_groups() - prepare function and groups data
 * @dev:	Device poपूर्णांकer.
 * @fid:	Function ID.
 * @func:	Function data.
 * @groups:	Groups data.
 *
 * Query firmware to get group IDs क्रम each function. Firmware वापसs
 * group IDs. Based on group index क्रम the function, group names in
 * the function are stored. For example, the first group in "eth0" function
 * is named as "eth0_0" and second group as "eth0_1" and so on.
 *
 * Based on the group ID received from the firmware, function stores name of
 * the group क्रम that group ID. For example, अगर "eth0" first group ID
 * is x, groups[x] name will be stored as "eth0_0".
 *
 * Once करोne क्रम each function, each function would have its group names
 * and each groups would also have their names.
 *
 * Return: 0 on success अन्यथा error code.
 */
अटल पूर्णांक zynqmp_pinctrl_prepare_func_groups(काष्ठा device *dev, u32 fid,
					      काष्ठा zynqmp_pmux_function *func,
					      काष्ठा zynqmp_pctrl_group *groups)
अणु
	u16 resp[NUM_GROUPS_PER_RESP] = अणु0पूर्ण;
	स्थिर अक्षर **fgroups;
	पूर्णांक ret = 0, index, i;

	fgroups = devm_kzalloc(dev, माप(*fgroups) * func->ngroups, GFP_KERNEL);
	अगर (!fgroups)
		वापस -ENOMEM;

	क्रम (index = 0; index < func->ngroups; index += NUM_GROUPS_PER_RESP) अणु
		ret = zynqmp_pinctrl_get_function_groups(fid, index, resp);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < NUM_GROUPS_PER_RESP; i++) अणु
			अगर (resp[i] == NA_GROUP)
				जाओ करोne;

			अगर (resp[i] == RESERVED_GROUP)
				जारी;

			fgroups[index + i] = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							    "%s_%d_grp",
							    func->name,
							    index + i);
			अगर (!fgroups[index + i])
				वापस -ENOMEM;

			groups[resp[i]].name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
							      "%s_%d_grp",
							      func->name,
							      index + i);
			अगर (!groups[resp[i]].name)
				वापस -ENOMEM;
		पूर्ण
	पूर्ण
करोne:
	func->groups = fgroups;

	वापस ret;
पूर्ण

अटल व्योम zynqmp_pinctrl_get_function_name(u32 fid, अक्षर *name)
अणु
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 payload[PAYLOAD_ARG_CNT];

	qdata.qid = PM_QID_PINCTRL_GET_FUNCTION_NAME;
	qdata.arg1 = fid;

	/*
	 * Name of the function is maximum 16 bytes and cannot
	 * accommodate the वापस value in SMC buffers, hence ignoring
	 * the वापस value क्रम this specअगरic qid.
	 */
	zynqmp_pm_query_data(qdata, payload);
	स_नकल(name, payload, PINCTRL_GET_FUNC_NAME_RESP_LEN);
पूर्ण

अटल पूर्णांक zynqmp_pinctrl_get_num_functions(अचिन्हित पूर्णांक *nfuncs)
अणु
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	qdata.qid = PM_QID_PINCTRL_GET_NUM_FUNCTIONS;

	ret = zynqmp_pm_query_data(qdata, payload);
	अगर (ret)
		वापस ret;

	*nfuncs = payload[1];

	वापस ret;
पूर्ण

अटल पूर्णांक zynqmp_pinctrl_get_pin_groups(u32 pin, u32 index, u16 *groups)
अणु
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	qdata.qid = PM_QID_PINCTRL_GET_PIN_GROUPS;
	qdata.arg1 = pin;
	qdata.arg2 = index;

	ret = zynqmp_pm_query_data(qdata, payload);
	अगर (ret)
		वापस ret;

	स_नकल(groups, &payload[1], PINCTRL_GET_PIN_GROUPS_RESP_LEN);

	वापस ret;
पूर्ण

अटल व्योम zynqmp_pinctrl_group_add_pin(काष्ठा zynqmp_pctrl_group *group,
					 अचिन्हित पूर्णांक pin)
अणु
	group->pins[group->npins++] = pin;
पूर्ण

/**
 * zynqmp_pinctrl_create_pin_groups() - assign pins to respective groups
 * @dev:	Device poपूर्णांकer.
 * @groups:	Groups data.
 * @pin:	Pin number.
 *
 * Query firmware to get groups available क्रम the given pin.
 * Based on the firmware response(group IDs क्रम the pin), add
 * pin number to the respective group's pin array.
 *
 * Once all pins are queries, each groups would have its number
 * of pins and pin numbers data.
 *
 * Return: 0 on success अन्यथा error code.
 */
अटल पूर्णांक zynqmp_pinctrl_create_pin_groups(काष्ठा device *dev,
					    काष्ठा zynqmp_pctrl_group *groups,
					    अचिन्हित पूर्णांक pin)
अणु
	u16 resp[NUM_GROUPS_PER_RESP] = अणु0पूर्ण;
	पूर्णांक ret, i, index = 0;

	करो अणु
		ret = zynqmp_pinctrl_get_pin_groups(pin, index, resp);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < NUM_GROUPS_PER_RESP; i++) अणु
			अगर (resp[i] == NA_GROUP)
				वापस ret;

			अगर (resp[i] == RESERVED_GROUP)
				जारी;

			zynqmp_pinctrl_group_add_pin(&groups[resp[i]], pin);
		पूर्ण
		index += NUM_GROUPS_PER_RESP;
	पूर्ण जबतक (index <= MAX_PIN_GROUPS);

	वापस ret;
पूर्ण

/**
 * zynqmp_pinctrl_prepare_group_pins() - prepare each group's pin data
 * @dev:	Device poपूर्णांकer.
 * @groups:	Groups data.
 * @ngroups:	Number of groups.
 *
 * Prepare pin number and number of pins data क्रम each pins.
 *
 * Return: 0 on success अन्यथा error code.
 */
अटल पूर्णांक zynqmp_pinctrl_prepare_group_pins(काष्ठा device *dev,
					     काष्ठा zynqmp_pctrl_group *groups,
					     अचिन्हित पूर्णांक ngroups)
अणु
	अचिन्हित पूर्णांक pin;
	पूर्णांक ret;

	क्रम (pin = 0; pin < zynqmp_desc.npins; pin++) अणु
		ret = zynqmp_pinctrl_create_pin_groups(dev, groups, pin);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zynqmp_pinctrl_prepare_function_info() - prepare function info
 * @dev:	Device poपूर्णांकer.
 * @pctrl:	Pin control driver data.
 *
 * Query firmware क्रम functions, groups and pin inक्रमmation and
 * prepare pin control driver data.
 *
 * Query number of functions and number of function groups (number
 * of groups in given function) to allocate required memory buffers
 * क्रम functions and groups. Once buffers are allocated to store
 * functions and groups data, query and store required inक्रमmation
 * (number of groups and group names क्रम each function, number of
 * pins and pin numbers क्रम each group).
 *
 * Return: 0 on success अन्यथा error code.
 */
अटल पूर्णांक zynqmp_pinctrl_prepare_function_info(काष्ठा device *dev,
						काष्ठा zynqmp_pinctrl *pctrl)
अणु
	काष्ठा zynqmp_pmux_function *funcs;
	काष्ठा zynqmp_pctrl_group *groups;
	पूर्णांक ret, i;

	ret = zynqmp_pinctrl_get_num_functions(&pctrl->nfuncs);
	अगर (ret)
		वापस ret;

	funcs = devm_kzalloc(dev, माप(*funcs) * pctrl->nfuncs, GFP_KERNEL);
	अगर (!funcs)
		वापस -ENOMEM;

	क्रम (i = 0; i < pctrl->nfuncs; i++) अणु
		zynqmp_pinctrl_get_function_name(i, funcs[i].name);

		ret = zynqmp_pinctrl_get_func_num_groups(i, &funcs[i].ngroups);
		अगर (ret)
			वापस ret;

		pctrl->ngroups += funcs[i].ngroups;
	पूर्ण

	groups = devm_kzalloc(dev, माप(*groups) * pctrl->ngroups, GFP_KERNEL);
	अगर (!groups)
		वापस -ENOMEM;

	क्रम (i = 0; i < pctrl->nfuncs; i++) अणु
		ret = zynqmp_pinctrl_prepare_func_groups(dev, i, &funcs[i],
							 groups);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = zynqmp_pinctrl_prepare_group_pins(dev, groups, pctrl->ngroups);
	अगर (ret)
		वापस ret;

	pctrl->funcs = funcs;
	pctrl->groups = groups;

	वापस ret;
पूर्ण

अटल पूर्णांक zynqmp_pinctrl_get_num_pins(अचिन्हित पूर्णांक *npins)
अणु
	काष्ठा zynqmp_pm_query_data qdata = अणु0पूर्ण;
	u32 payload[PAYLOAD_ARG_CNT];
	पूर्णांक ret;

	qdata.qid = PM_QID_PINCTRL_GET_NUM_PINS;

	ret = zynqmp_pm_query_data(qdata, payload);
	अगर (ret)
		वापस ret;

	*npins = payload[1];

	वापस ret;
पूर्ण

/**
 * zynqmp_pinctrl_prepare_pin_desc() - prepare pin description info
 * @dev:		Device poपूर्णांकer.
 * @zynqmp_pins:	Pin inक्रमmation.
 * @npins:		Number of pins.
 *
 * Query number of pins inक्रमmation from firmware and prepare pin
 * description containing pin number and pin name.
 *
 * Return: 0 on success अन्यथा error code.
 */
अटल पूर्णांक zynqmp_pinctrl_prepare_pin_desc(काष्ठा device *dev,
					   स्थिर काष्ठा pinctrl_pin_desc
					   **zynqmp_pins,
					   अचिन्हित पूर्णांक *npins)
अणु
	काष्ठा pinctrl_pin_desc *pins, *pin;
	पूर्णांक ret;
	पूर्णांक i;

	ret = zynqmp_pinctrl_get_num_pins(npins);
	अगर (ret)
		वापस ret;

	pins = devm_kzalloc(dev, माप(*pins) * *npins, GFP_KERNEL);
	अगर (!pins)
		वापस -ENOMEM;

	क्रम (i = 0; i < *npins; i++) अणु
		pin = &pins[i];
		pin->number = i;
		pin->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s%d",
					   ZYNQMP_PIN_PREFIX, i);
		अगर (!pin->name)
			वापस -ENOMEM;
	पूर्ण

	*zynqmp_pins = pins;

	वापस 0;
पूर्ण

अटल पूर्णांक zynqmp_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynqmp_pinctrl *pctrl;
	पूर्णांक ret;

	pctrl = devm_kzalloc(&pdev->dev, माप(*pctrl), GFP_KERNEL);
	अगर (!pctrl)
		वापस -ENOMEM;

	ret = zynqmp_pinctrl_prepare_pin_desc(&pdev->dev,
					      &zynqmp_desc.pins,
					      &zynqmp_desc.npins);
	अगर (ret) अणु
		dev_err(&pdev->dev, "pin desc prepare fail with %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = zynqmp_pinctrl_prepare_function_info(&pdev->dev, pctrl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "function info prepare fail with %d\n",
			ret);
		वापस ret;
	पूर्ण

	pctrl->pctrl = pinctrl_रेजिस्टर(&zynqmp_desc, &pdev->dev, pctrl);
	अगर (IS_ERR(pctrl->pctrl))
		वापस PTR_ERR(pctrl->pctrl);

	platक्रमm_set_drvdata(pdev, pctrl);

	वापस ret;
पूर्ण

अटल पूर्णांक zynqmp_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynqmp_pinctrl *pctrl = platक्रमm_get_drvdata(pdev);

	pinctrl_unरेजिस्टर(pctrl->pctrl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zynqmp_pinctrl_of_match[] = अणु
	अणु .compatible = "xlnx,zynqmp-pinctrl" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, zynqmp_pinctrl_of_match);

अटल काष्ठा platक्रमm_driver zynqmp_pinctrl_driver = अणु
	.driver = अणु
		.name = "zynqmp-pinctrl",
		.of_match_table = zynqmp_pinctrl_of_match,
	पूर्ण,
	.probe = zynqmp_pinctrl_probe,
	.हटाओ = zynqmp_pinctrl_हटाओ,
पूर्ण;

module_platक्रमm_driver(zynqmp_pinctrl_driver);

MODULE_AUTHOR("Sai Krishna Potthuri <lakshmi.sai.krishna.potthuri@xilinx.com>");
MODULE_DESCRIPTION("ZynqMP Pin Controller Driver");
MODULE_LICENSE("GPL v2");
