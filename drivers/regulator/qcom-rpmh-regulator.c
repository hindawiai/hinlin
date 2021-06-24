<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018-2021, The Linux Foundation. All rights reserved.

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>

#समावेश <soc/qcom/cmd-db.h>
#समावेश <soc/qcom/rpmh.h>

#समावेश <dt-bindings/regulator/qcom,rpmh-regulator.h>

/**
 * क्रमागत rpmh_regulator_type - supported RPMh accelerator types
 * @VRM:	RPMh VRM accelerator which supports voting on enable, voltage,
 *		and mode of LDO, SMPS, and BOB type PMIC regulators.
 * @XOB:	RPMh XOB accelerator which supports voting on the enable state
 *		of PMIC regulators.
 */
क्रमागत rpmh_regulator_type अणु
	VRM,
	XOB,
पूर्ण;

#घोषणा RPMH_REGULATOR_REG_VRM_VOLTAGE		0x0
#घोषणा RPMH_REGULATOR_REG_ENABLE		0x4
#घोषणा RPMH_REGULATOR_REG_VRM_MODE		0x8

#घोषणा PMIC4_LDO_MODE_RETENTION		4
#घोषणा PMIC4_LDO_MODE_LPM			5
#घोषणा PMIC4_LDO_MODE_HPM			7

#घोषणा PMIC4_SMPS_MODE_RETENTION		4
#घोषणा PMIC4_SMPS_MODE_PFM			5
#घोषणा PMIC4_SMPS_MODE_AUTO			6
#घोषणा PMIC4_SMPS_MODE_PWM			7

#घोषणा PMIC4_BOB_MODE_PASS			0
#घोषणा PMIC4_BOB_MODE_PFM			1
#घोषणा PMIC4_BOB_MODE_AUTO			2
#घोषणा PMIC4_BOB_MODE_PWM			3

#घोषणा PMIC5_LDO_MODE_RETENTION		3
#घोषणा PMIC5_LDO_MODE_LPM			4
#घोषणा PMIC5_LDO_MODE_HPM			7

#घोषणा PMIC5_SMPS_MODE_RETENTION		3
#घोषणा PMIC5_SMPS_MODE_PFM			4
#घोषणा PMIC5_SMPS_MODE_AUTO			6
#घोषणा PMIC5_SMPS_MODE_PWM			7

#घोषणा PMIC5_BOB_MODE_PASS			2
#घोषणा PMIC5_BOB_MODE_PFM			4
#घोषणा PMIC5_BOB_MODE_AUTO			6
#घोषणा PMIC5_BOB_MODE_PWM			7

/**
 * काष्ठा rpmh_vreg_hw_data - RPMh regulator hardware configurations
 * @regulator_type:		RPMh accelerator type used to manage this
 *				regulator
 * @ops:			Poपूर्णांकer to regulator ops callback काष्ठाure
 * @voltage_range:		The single range of voltages supported by this
 *				PMIC regulator type
 * @n_voltages:			The number of unique voltage set poपूर्णांकs defined
 *				by voltage_range
 * @hpm_min_load_uA:		Minimum load current in microamps that requires
 *				high घातer mode (HPM) operation.  This is used
 *				क्रम LDO hardware type regulators only.
 * @pmic_mode_map:		Array indexed by regulator framework mode
 *				containing PMIC hardware modes.  Must be large
 *				enough to index all framework modes supported
 *				by this regulator hardware type.
 * @of_map_mode:		Maps an RPMH_REGULATOR_MODE_* mode value defined
 *				in device tree to a regulator framework mode
 */
काष्ठा rpmh_vreg_hw_data अणु
	क्रमागत rpmh_regulator_type		regulator_type;
	स्थिर काष्ठा regulator_ops		*ops;
	स्थिर काष्ठा linear_range	voltage_range;
	पूर्णांक					n_voltages;
	पूर्णांक					hpm_min_load_uA;
	स्थिर पूर्णांक				*pmic_mode_map;
	अचिन्हित पूर्णांक			      (*of_map_mode)(अचिन्हित पूर्णांक mode);
पूर्ण;

/**
 * काष्ठा rpmh_vreg - inभागidual RPMh regulator data काष्ठाure encapsulating a
 *		single regulator device
 * @dev:			Device poपूर्णांकer क्रम the top-level PMIC RPMh
 *				regulator parent device.  This is used as a
 *				handle in RPMh ग_लिखो requests.
 * @addr:			Base address of the regulator resource within
 *				an RPMh accelerator
 * @rdesc:			Regulator descriptor
 * @hw_data:			PMIC regulator configuration data क्रम this RPMh
 *				regulator
 * @always_रुको_क्रम_ack:	Boolean flag indicating अगर a request must always
 *				रुको क्रम an ACK from RPMh beक्रमe continuing even
 *				अगर it corresponds to a strictly lower घातer
 *				state (e.g. enabled --> disabled).
 * @enabled:			Flag indicating अगर the regulator is enabled or
 *				not
 * @bypassed:			Boolean indicating अगर the regulator is in
 *				bypass (pass-through) mode or not.  This is
 *				only used by BOB rpmh-regulator resources.
 * @voltage_selector:		Selector used क्रम get_voltage_sel() and
 *				set_voltage_sel() callbacks
 * @mode:			RPMh VRM regulator current framework mode
 */
काष्ठा rpmh_vreg अणु
	काष्ठा device			*dev;
	u32				addr;
	काष्ठा regulator_desc		rdesc;
	स्थिर काष्ठा rpmh_vreg_hw_data	*hw_data;
	bool				always_रुको_क्रम_ack;

	पूर्णांक				enabled;
	bool				bypassed;
	पूर्णांक				voltage_selector;
	अचिन्हित पूर्णांक			mode;
पूर्ण;

/**
 * काष्ठा rpmh_vreg_init_data - initialization data क्रम an RPMh regulator
 * @name:			Name क्रम the regulator which also corresponds
 *				to the device tree subnode name of the regulator
 * @resource_name:		RPMh regulator resource name क्रमmat string.
 *				This must include exactly one field: '%s' which
 *				is filled at run-समय with the PMIC ID provided
 *				by device tree property qcom,pmic-id.  Example:
 *				"ldo%s1" क्रम RPMh resource "ldoa1".
 * @supply_name:		Parent supply regulator name
 * @hw_data:			Configuration data क्रम this PMIC regulator type
 */
काष्ठा rpmh_vreg_init_data अणु
	स्थिर अक्षर			*name;
	स्थिर अक्षर			*resource_name;
	स्थिर अक्षर			*supply_name;
	स्थिर काष्ठा rpmh_vreg_hw_data	*hw_data;
पूर्ण;

/**
 * rpmh_regulator_send_request() - send the request to RPMh
 * @vreg:		Poपूर्णांकer to the RPMh regulator
 * @cmd:		Poपूर्णांकer to the RPMh command to send
 * @रुको_क्रम_ack:	Boolean indicating अगर execution must रुको until the
 *			request has been acknowledged as complete
 *
 * Return: 0 on success, त्रुटि_सं on failure
 */
अटल पूर्णांक rpmh_regulator_send_request(काष्ठा rpmh_vreg *vreg,
			काष्ठा tcs_cmd *cmd, bool रुको_क्रम_ack)
अणु
	पूर्णांक ret;

	अगर (रुको_क्रम_ack || vreg->always_रुको_क्रम_ack)
		ret = rpmh_ग_लिखो(vreg->dev, RPMH_ACTIVE_ONLY_STATE, cmd, 1);
	अन्यथा
		ret = rpmh_ग_लिखो_async(vreg->dev, RPMH_ACTIVE_ONLY_STATE, cmd,
					1);

	वापस ret;
पूर्ण

अटल पूर्णांक _rpmh_regulator_vrm_set_voltage_sel(काष्ठा regulator_dev *rdev,
				अचिन्हित पूर्णांक selector, bool रुको_क्रम_ack)
अणु
	काष्ठा rpmh_vreg *vreg = rdev_get_drvdata(rdev);
	काष्ठा tcs_cmd cmd = अणु
		.addr = vreg->addr + RPMH_REGULATOR_REG_VRM_VOLTAGE,
	पूर्ण;
	पूर्णांक ret;

	/* VRM voltage control रेजिस्टर is set with voltage in millivolts. */
	cmd.data = DIV_ROUND_UP(regulator_list_voltage_linear_range(rdev,
							selector), 1000);

	ret = rpmh_regulator_send_request(vreg, &cmd, रुको_क्रम_ack);
	अगर (!ret)
		vreg->voltage_selector = selector;

	वापस ret;
पूर्ण

अटल पूर्णांक rpmh_regulator_vrm_set_voltage_sel(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक selector)
अणु
	काष्ठा rpmh_vreg *vreg = rdev_get_drvdata(rdev);

	अगर (vreg->enabled == -EINVAL) अणु
		/*
		 * Cache the voltage and send it later when the regulator is
		 * enabled or disabled.
		 */
		vreg->voltage_selector = selector;
		वापस 0;
	पूर्ण

	वापस _rpmh_regulator_vrm_set_voltage_sel(rdev, selector,
					selector > vreg->voltage_selector);
पूर्ण

अटल पूर्णांक rpmh_regulator_vrm_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा rpmh_vreg *vreg = rdev_get_drvdata(rdev);

	वापस vreg->voltage_selector;
पूर्ण

अटल पूर्णांक rpmh_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा rpmh_vreg *vreg = rdev_get_drvdata(rdev);

	वापस vreg->enabled;
पूर्ण

अटल पूर्णांक rpmh_regulator_set_enable_state(काष्ठा regulator_dev *rdev,
					bool enable)
अणु
	काष्ठा rpmh_vreg *vreg = rdev_get_drvdata(rdev);
	काष्ठा tcs_cmd cmd = अणु
		.addr = vreg->addr + RPMH_REGULATOR_REG_ENABLE,
		.data = enable,
	पूर्ण;
	पूर्णांक ret;

	अगर (vreg->enabled == -EINVAL &&
	    vreg->voltage_selector != -ENOTRECOVERABLE) अणु
		ret = _rpmh_regulator_vrm_set_voltage_sel(rdev,
						vreg->voltage_selector, true);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = rpmh_regulator_send_request(vreg, &cmd, enable);
	अगर (!ret)
		vreg->enabled = enable;

	वापस ret;
पूर्ण

अटल पूर्णांक rpmh_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	वापस rpmh_regulator_set_enable_state(rdev, true);
पूर्ण

अटल पूर्णांक rpmh_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	वापस rpmh_regulator_set_enable_state(rdev, false);
पूर्ण

अटल पूर्णांक rpmh_regulator_vrm_set_mode_bypass(काष्ठा rpmh_vreg *vreg,
					अचिन्हित पूर्णांक mode, bool bypassed)
अणु
	काष्ठा tcs_cmd cmd = अणु
		.addr = vreg->addr + RPMH_REGULATOR_REG_VRM_MODE,
	पूर्ण;
	पूर्णांक pmic_mode;

	अगर (mode > REGULATOR_MODE_STANDBY)
		वापस -EINVAL;

	pmic_mode = vreg->hw_data->pmic_mode_map[mode];
	अगर (pmic_mode < 0)
		वापस pmic_mode;

	अगर (bypassed)
		cmd.data = PMIC4_BOB_MODE_PASS;
	अन्यथा
		cmd.data = pmic_mode;

	वापस rpmh_regulator_send_request(vreg, &cmd, true);
पूर्ण

अटल पूर्णांक rpmh_regulator_vrm_set_mode(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक mode)
अणु
	काष्ठा rpmh_vreg *vreg = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	अगर (mode == vreg->mode)
		वापस 0;

	ret = rpmh_regulator_vrm_set_mode_bypass(vreg, mode, vreg->bypassed);
	अगर (!ret)
		vreg->mode = mode;

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक rpmh_regulator_vrm_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा rpmh_vreg *vreg = rdev_get_drvdata(rdev);

	वापस vreg->mode;
पूर्ण

/**
 * rpmh_regulator_vrm_set_load() - set the regulator mode based upon the load
 *		current requested
 * @rdev:		Regulator device poपूर्णांकer क्रम the rpmh-regulator
 * @load_uA:		Aggregated load current in microamps
 *
 * This function is used in the regulator_ops क्रम VRM type RPMh regulator
 * devices.
 *
 * Return: 0 on success, त्रुटि_सं on failure
 */
अटल पूर्णांक rpmh_regulator_vrm_set_load(काष्ठा regulator_dev *rdev, पूर्णांक load_uA)
अणु
	काष्ठा rpmh_vreg *vreg = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक mode;

	अगर (load_uA >= vreg->hw_data->hpm_min_load_uA)
		mode = REGULATOR_MODE_NORMAL;
	अन्यथा
		mode = REGULATOR_MODE_IDLE;

	वापस rpmh_regulator_vrm_set_mode(rdev, mode);
पूर्ण

अटल पूर्णांक rpmh_regulator_vrm_set_bypass(काष्ठा regulator_dev *rdev,
				bool enable)
अणु
	काष्ठा rpmh_vreg *vreg = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	अगर (vreg->bypassed == enable)
		वापस 0;

	ret = rpmh_regulator_vrm_set_mode_bypass(vreg, vreg->mode, enable);
	अगर (!ret)
		vreg->bypassed = enable;

	वापस ret;
पूर्ण

अटल पूर्णांक rpmh_regulator_vrm_get_bypass(काष्ठा regulator_dev *rdev,
				bool *enable)
अणु
	काष्ठा rpmh_vreg *vreg = rdev_get_drvdata(rdev);

	*enable = vreg->bypassed;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops rpmh_regulator_vrm_ops = अणु
	.enable			= rpmh_regulator_enable,
	.disable		= rpmh_regulator_disable,
	.is_enabled		= rpmh_regulator_is_enabled,
	.set_voltage_sel	= rpmh_regulator_vrm_set_voltage_sel,
	.get_voltage_sel	= rpmh_regulator_vrm_get_voltage_sel,
	.list_voltage		= regulator_list_voltage_linear_range,
	.set_mode		= rpmh_regulator_vrm_set_mode,
	.get_mode		= rpmh_regulator_vrm_get_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rpmh_regulator_vrm_drms_ops = अणु
	.enable			= rpmh_regulator_enable,
	.disable		= rpmh_regulator_disable,
	.is_enabled		= rpmh_regulator_is_enabled,
	.set_voltage_sel	= rpmh_regulator_vrm_set_voltage_sel,
	.get_voltage_sel	= rpmh_regulator_vrm_get_voltage_sel,
	.list_voltage		= regulator_list_voltage_linear_range,
	.set_mode		= rpmh_regulator_vrm_set_mode,
	.get_mode		= rpmh_regulator_vrm_get_mode,
	.set_load		= rpmh_regulator_vrm_set_load,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rpmh_regulator_vrm_bypass_ops = अणु
	.enable			= rpmh_regulator_enable,
	.disable		= rpmh_regulator_disable,
	.is_enabled		= rpmh_regulator_is_enabled,
	.set_voltage_sel	= rpmh_regulator_vrm_set_voltage_sel,
	.get_voltage_sel	= rpmh_regulator_vrm_get_voltage_sel,
	.list_voltage		= regulator_list_voltage_linear_range,
	.set_mode		= rpmh_regulator_vrm_set_mode,
	.get_mode		= rpmh_regulator_vrm_get_mode,
	.set_bypass		= rpmh_regulator_vrm_set_bypass,
	.get_bypass		= rpmh_regulator_vrm_get_bypass,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rpmh_regulator_xob_ops = अणु
	.enable			= rpmh_regulator_enable,
	.disable		= rpmh_regulator_disable,
	.is_enabled		= rpmh_regulator_is_enabled,
पूर्ण;

/**
 * rpmh_regulator_init_vreg() - initialize all attributes of an rpmh-regulator
 * @vreg:		Poपूर्णांकer to the inभागidual rpmh-regulator resource
 * @dev:			Poपूर्णांकer to the top level rpmh-regulator PMIC device
 * @node:		Poपूर्णांकer to the inभागidual rpmh-regulator resource
 *			device node
 * @pmic_id:		String used to identअगरy the top level rpmh-regulator
 *			PMIC device on the board
 * @pmic_rpmh_data:	Poपूर्णांकer to a null-terminated array of rpmh-regulator
 *			resources defined क्रम the top level PMIC device
 *
 * Return: 0 on success, त्रुटि_सं on failure
 */
अटल पूर्णांक rpmh_regulator_init_vreg(काष्ठा rpmh_vreg *vreg, काष्ठा device *dev,
			काष्ठा device_node *node, स्थिर अक्षर *pmic_id,
			स्थिर काष्ठा rpmh_vreg_init_data *pmic_rpmh_data)
अणु
	काष्ठा regulator_config reg_config = अणुपूर्ण;
	अक्षर rpmh_resource_name[20] = "";
	स्थिर काष्ठा rpmh_vreg_init_data *rpmh_data;
	काष्ठा regulator_init_data *init_data;
	काष्ठा regulator_dev *rdev;
	पूर्णांक ret;

	vreg->dev = dev;

	क्रम (rpmh_data = pmic_rpmh_data; rpmh_data->name; rpmh_data++)
		अगर (of_node_name_eq(node, rpmh_data->name))
			अवरोध;

	अगर (!rpmh_data->name) अणु
		dev_err(dev, "Unknown regulator %pOFn\n", node);
		वापस -EINVAL;
	पूर्ण

	scnम_लिखो(rpmh_resource_name, माप(rpmh_resource_name),
		rpmh_data->resource_name, pmic_id);

	vreg->addr = cmd_db_पढ़ो_addr(rpmh_resource_name);
	अगर (!vreg->addr) अणु
		dev_err(dev, "%pOFn: could not find RPMh address for resource %s\n",
			node, rpmh_resource_name);
		वापस -ENODEV;
	पूर्ण

	vreg->rdesc.name = rpmh_data->name;
	vreg->rdesc.supply_name = rpmh_data->supply_name;
	vreg->hw_data = rpmh_data->hw_data;

	vreg->enabled = -EINVAL;
	vreg->voltage_selector = -ENOTRECOVERABLE;
	vreg->mode = REGULATOR_MODE_INVALID;

	अगर (rpmh_data->hw_data->n_voltages) अणु
		vreg->rdesc.linear_ranges = &rpmh_data->hw_data->voltage_range;
		vreg->rdesc.n_linear_ranges = 1;
		vreg->rdesc.n_voltages = rpmh_data->hw_data->n_voltages;
	पूर्ण

	vreg->always_रुको_क्रम_ack = of_property_पढ़ो_bool(node,
						"qcom,always-wait-for-ack");

	vreg->rdesc.owner	= THIS_MODULE;
	vreg->rdesc.type	= REGULATOR_VOLTAGE;
	vreg->rdesc.ops		= vreg->hw_data->ops;
	vreg->rdesc.of_map_mode	= vreg->hw_data->of_map_mode;

	init_data = of_get_regulator_init_data(dev, node, &vreg->rdesc);
	अगर (!init_data)
		वापस -ENOMEM;

	अगर (rpmh_data->hw_data->regulator_type == XOB &&
	    init_data->स्थिरraपूर्णांकs.min_uV &&
	    init_data->स्थिरraपूर्णांकs.min_uV == init_data->स्थिरraपूर्णांकs.max_uV) अणु
		vreg->rdesc.fixed_uV = init_data->स्थिरraपूर्णांकs.min_uV;
		vreg->rdesc.n_voltages = 1;
	पूर्ण

	reg_config.dev		= dev;
	reg_config.init_data	= init_data;
	reg_config.of_node	= node;
	reg_config.driver_data	= vreg;

	rdev = devm_regulator_रेजिस्टर(dev, &vreg->rdesc, &reg_config);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(dev, "%pOFn: devm_regulator_register() failed, ret=%d\n",
			node, ret);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "%pOFn regulator registered for RPMh resource %s @ 0x%05X\n",
		node, rpmh_resource_name, vreg->addr);

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक pmic_mode_map_pmic4_lकरो[REGULATOR_MODE_STANDBY + 1] = अणु
	[REGULATOR_MODE_INVALID] = -EINVAL,
	[REGULATOR_MODE_STANDBY] = PMIC4_LDO_MODE_RETENTION,
	[REGULATOR_MODE_IDLE]    = PMIC4_LDO_MODE_LPM,
	[REGULATOR_MODE_NORMAL]  = PMIC4_LDO_MODE_HPM,
	[REGULATOR_MODE_FAST]    = -EINVAL,
पूर्ण;

अटल स्थिर पूर्णांक pmic_mode_map_pmic5_lकरो[REGULATOR_MODE_STANDBY + 1] = अणु
	[REGULATOR_MODE_INVALID] = -EINVAL,
	[REGULATOR_MODE_STANDBY] = PMIC5_LDO_MODE_RETENTION,
	[REGULATOR_MODE_IDLE]    = PMIC5_LDO_MODE_LPM,
	[REGULATOR_MODE_NORMAL]  = PMIC5_LDO_MODE_HPM,
	[REGULATOR_MODE_FAST]    = -EINVAL,
पूर्ण;

अटल अचिन्हित पूर्णांक rpmh_regulator_pmic4_lकरो_of_map_mode(अचिन्हित पूर्णांक rpmh_mode)
अणु
	अचिन्हित पूर्णांक mode;

	चयन (rpmh_mode) अणु
	हाल RPMH_REGULATOR_MODE_HPM:
		mode = REGULATOR_MODE_NORMAL;
		अवरोध;
	हाल RPMH_REGULATOR_MODE_LPM:
		mode = REGULATOR_MODE_IDLE;
		अवरोध;
	हाल RPMH_REGULATOR_MODE_RET:
		mode = REGULATOR_MODE_STANDBY;
		अवरोध;
	शेष:
		mode = REGULATOR_MODE_INVALID;
		अवरोध;
	पूर्ण

	वापस mode;
पूर्ण

अटल स्थिर पूर्णांक pmic_mode_map_pmic4_smps[REGULATOR_MODE_STANDBY + 1] = अणु
	[REGULATOR_MODE_INVALID] = -EINVAL,
	[REGULATOR_MODE_STANDBY] = PMIC4_SMPS_MODE_RETENTION,
	[REGULATOR_MODE_IDLE]    = PMIC4_SMPS_MODE_PFM,
	[REGULATOR_MODE_NORMAL]  = PMIC4_SMPS_MODE_AUTO,
	[REGULATOR_MODE_FAST]    = PMIC4_SMPS_MODE_PWM,
पूर्ण;

अटल स्थिर पूर्णांक pmic_mode_map_pmic5_smps[REGULATOR_MODE_STANDBY + 1] = अणु
	[REGULATOR_MODE_INVALID] = -EINVAL,
	[REGULATOR_MODE_STANDBY] = PMIC5_SMPS_MODE_RETENTION,
	[REGULATOR_MODE_IDLE]    = PMIC5_SMPS_MODE_PFM,
	[REGULATOR_MODE_NORMAL]  = PMIC5_SMPS_MODE_AUTO,
	[REGULATOR_MODE_FAST]    = PMIC5_SMPS_MODE_PWM,
पूर्ण;

अटल अचिन्हित पूर्णांक
rpmh_regulator_pmic4_smps_of_map_mode(अचिन्हित पूर्णांक rpmh_mode)
अणु
	अचिन्हित पूर्णांक mode;

	चयन (rpmh_mode) अणु
	हाल RPMH_REGULATOR_MODE_HPM:
		mode = REGULATOR_MODE_FAST;
		अवरोध;
	हाल RPMH_REGULATOR_MODE_AUTO:
		mode = REGULATOR_MODE_NORMAL;
		अवरोध;
	हाल RPMH_REGULATOR_MODE_LPM:
		mode = REGULATOR_MODE_IDLE;
		अवरोध;
	हाल RPMH_REGULATOR_MODE_RET:
		mode = REGULATOR_MODE_STANDBY;
		अवरोध;
	शेष:
		mode = REGULATOR_MODE_INVALID;
		अवरोध;
	पूर्ण

	वापस mode;
पूर्ण

अटल स्थिर पूर्णांक pmic_mode_map_pmic4_bob[REGULATOR_MODE_STANDBY + 1] = अणु
	[REGULATOR_MODE_INVALID] = -EINVAL,
	[REGULATOR_MODE_STANDBY] = -EINVAL,
	[REGULATOR_MODE_IDLE]    = PMIC4_BOB_MODE_PFM,
	[REGULATOR_MODE_NORMAL]  = PMIC4_BOB_MODE_AUTO,
	[REGULATOR_MODE_FAST]    = PMIC4_BOB_MODE_PWM,
पूर्ण;

अटल स्थिर पूर्णांक pmic_mode_map_pmic5_bob[REGULATOR_MODE_STANDBY + 1] = अणु
	[REGULATOR_MODE_INVALID] = -EINVAL,
	[REGULATOR_MODE_STANDBY] = -EINVAL,
	[REGULATOR_MODE_IDLE]    = PMIC5_BOB_MODE_PFM,
	[REGULATOR_MODE_NORMAL]  = PMIC5_BOB_MODE_AUTO,
	[REGULATOR_MODE_FAST]    = PMIC5_BOB_MODE_PWM,
पूर्ण;

अटल अचिन्हित पूर्णांक rpmh_regulator_pmic4_bob_of_map_mode(अचिन्हित पूर्णांक rpmh_mode)
अणु
	अचिन्हित पूर्णांक mode;

	चयन (rpmh_mode) अणु
	हाल RPMH_REGULATOR_MODE_HPM:
		mode = REGULATOR_MODE_FAST;
		अवरोध;
	हाल RPMH_REGULATOR_MODE_AUTO:
		mode = REGULATOR_MODE_NORMAL;
		अवरोध;
	हाल RPMH_REGULATOR_MODE_LPM:
		mode = REGULATOR_MODE_IDLE;
		अवरोध;
	शेष:
		mode = REGULATOR_MODE_INVALID;
		अवरोध;
	पूर्ण

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic4_plकरो = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_drms_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(1664000, 0, 255, 8000),
	.n_voltages = 256,
	.hpm_min_load_uA = 10000,
	.pmic_mode_map = pmic_mode_map_pmic4_lकरो,
	.of_map_mode = rpmh_regulator_pmic4_lकरो_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic4_plकरो_lv = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_drms_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(1256000, 0, 127, 8000),
	.n_voltages = 128,
	.hpm_min_load_uA = 10000,
	.pmic_mode_map = pmic_mode_map_pmic4_lकरो,
	.of_map_mode = rpmh_regulator_pmic4_lकरो_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic4_nlकरो = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_drms_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(312000, 0, 127, 8000),
	.n_voltages = 128,
	.hpm_min_load_uA = 30000,
	.pmic_mode_map = pmic_mode_map_pmic4_lकरो,
	.of_map_mode = rpmh_regulator_pmic4_lकरो_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic4_hfsmps3 = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(320000, 0, 215, 8000),
	.n_voltages = 216,
	.pmic_mode_map = pmic_mode_map_pmic4_smps,
	.of_map_mode = rpmh_regulator_pmic4_smps_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic4_ftsmps426 = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(320000, 0, 258, 4000),
	.n_voltages = 259,
	.pmic_mode_map = pmic_mode_map_pmic4_smps,
	.of_map_mode = rpmh_regulator_pmic4_smps_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic4_bob = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_bypass_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(1824000, 0, 83, 32000),
	.n_voltages = 84,
	.pmic_mode_map = pmic_mode_map_pmic4_bob,
	.of_map_mode = rpmh_regulator_pmic4_bob_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic4_lvs = अणु
	.regulator_type = XOB,
	.ops = &rpmh_regulator_xob_ops,
	/* LVS hardware करोes not support voltage or mode configuration. */
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic5_plकरो = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_drms_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(1504000, 0, 255, 8000),
	.n_voltages = 256,
	.hpm_min_load_uA = 10000,
	.pmic_mode_map = pmic_mode_map_pmic5_lकरो,
	.of_map_mode = rpmh_regulator_pmic4_lकरो_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic5_plकरो_lv = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_drms_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(1504000, 0, 62, 8000),
	.n_voltages = 63,
	.hpm_min_load_uA = 10000,
	.pmic_mode_map = pmic_mode_map_pmic5_lकरो,
	.of_map_mode = rpmh_regulator_pmic4_lकरो_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic5_nlकरो = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_drms_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(320000, 0, 123, 8000),
	.n_voltages = 124,
	.hpm_min_load_uA = 30000,
	.pmic_mode_map = pmic_mode_map_pmic5_lकरो,
	.of_map_mode = rpmh_regulator_pmic4_lकरो_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic5_hfsmps510 = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(320000, 0, 215, 8000),
	.n_voltages = 216,
	.pmic_mode_map = pmic_mode_map_pmic5_smps,
	.of_map_mode = rpmh_regulator_pmic4_smps_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic5_ftsmps510 = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(300000, 0, 263, 4000),
	.n_voltages = 264,
	.pmic_mode_map = pmic_mode_map_pmic5_smps,
	.of_map_mode = rpmh_regulator_pmic4_smps_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic5_ftsmps520 = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(300000, 0, 263, 4000),
	.n_voltages = 264,
	.pmic_mode_map = pmic_mode_map_pmic5_smps,
	.of_map_mode = rpmh_regulator_pmic4_smps_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic5_hfsmps515 = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(320000, 0, 235, 16000),
	.n_voltages = 236,
	.pmic_mode_map = pmic_mode_map_pmic5_smps,
	.of_map_mode = rpmh_regulator_pmic4_smps_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic5_hfsmps515_1 = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(900000, 0, 4, 16000),
	.n_voltages = 5,
	.pmic_mode_map = pmic_mode_map_pmic5_smps,
	.of_map_mode = rpmh_regulator_pmic4_smps_of_map_mode,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_hw_data pmic5_bob = अणु
	.regulator_type = VRM,
	.ops = &rpmh_regulator_vrm_bypass_ops,
	.voltage_range = REGULATOR_LINEAR_RANGE(3000000, 0, 31, 32000),
	.n_voltages = 32,
	.pmic_mode_map = pmic_mode_map_pmic5_bob,
	.of_map_mode = rpmh_regulator_pmic4_bob_of_map_mode,
पूर्ण;

#घोषणा RPMH_VREG(_name, _resource_name, _hw_data, _supply_name) \
अणु \
	.name		= _name, \
	.resource_name	= _resource_name, \
	.hw_data	= _hw_data, \
	.supply_name	= _supply_name, \
पूर्ण

अटल स्थिर काष्ठा rpmh_vreg_init_data pm8998_vreg_data[] = अणु
	RPMH_VREG("smps1",  "smp%s1",  &pmic4_ftsmps426, "vdd-s1"),
	RPMH_VREG("smps2",  "smp%s2",  &pmic4_ftsmps426, "vdd-s2"),
	RPMH_VREG("smps3",  "smp%s3",  &pmic4_hfsmps3,   "vdd-s3"),
	RPMH_VREG("smps4",  "smp%s4",  &pmic4_hfsmps3,   "vdd-s4"),
	RPMH_VREG("smps5",  "smp%s5",  &pmic4_hfsmps3,   "vdd-s5"),
	RPMH_VREG("smps6",  "smp%s6",  &pmic4_ftsmps426, "vdd-s6"),
	RPMH_VREG("smps7",  "smp%s7",  &pmic4_ftsmps426, "vdd-s7"),
	RPMH_VREG("smps8",  "smp%s8",  &pmic4_ftsmps426, "vdd-s8"),
	RPMH_VREG("smps9",  "smp%s9",  &pmic4_ftsmps426, "vdd-s9"),
	RPMH_VREG("smps10", "smp%s10", &pmic4_ftsmps426, "vdd-s10"),
	RPMH_VREG("smps11", "smp%s11", &pmic4_ftsmps426, "vdd-s11"),
	RPMH_VREG("smps12", "smp%s12", &pmic4_ftsmps426, "vdd-s12"),
	RPMH_VREG("smps13", "smp%s13", &pmic4_ftsmps426, "vdd-s13"),
	RPMH_VREG("ldo1",   "ldo%s1",  &pmic4_nlकरो,      "vdd-l1-l27"),
	RPMH_VREG("ldo2",   "ldo%s2",  &pmic4_nlकरो,      "vdd-l2-l8-l17"),
	RPMH_VREG("ldo3",   "ldo%s3",  &pmic4_nlकरो,      "vdd-l3-l11"),
	RPMH_VREG("ldo4",   "ldo%s4",  &pmic4_nlकरो,      "vdd-l4-l5"),
	RPMH_VREG("ldo5",   "ldo%s5",  &pmic4_nlकरो,      "vdd-l4-l5"),
	RPMH_VREG("ldo6",   "ldo%s6",  &pmic4_plकरो,      "vdd-l6"),
	RPMH_VREG("ldo7",   "ldo%s7",  &pmic4_plकरो_lv,   "vdd-l7-l12-l14-l15"),
	RPMH_VREG("ldo8",   "ldo%s8",  &pmic4_nlकरो,      "vdd-l2-l8-l17"),
	RPMH_VREG("ldo9",   "ldo%s9",  &pmic4_plकरो,      "vdd-l9"),
	RPMH_VREG("ldo10",  "ldo%s10", &pmic4_plकरो,      "vdd-l10-l23-l25"),
	RPMH_VREG("ldo11",  "ldo%s11", &pmic4_nlकरो,      "vdd-l3-l11"),
	RPMH_VREG("ldo12",  "ldo%s12", &pmic4_plकरो_lv,   "vdd-l7-l12-l14-l15"),
	RPMH_VREG("ldo13",  "ldo%s13", &pmic4_plकरो,      "vdd-l13-l19-l21"),
	RPMH_VREG("ldo14",  "ldo%s14", &pmic4_plकरो_lv,   "vdd-l7-l12-l14-l15"),
	RPMH_VREG("ldo15",  "ldo%s15", &pmic4_plकरो_lv,   "vdd-l7-l12-l14-l15"),
	RPMH_VREG("ldo16",  "ldo%s16", &pmic4_plकरो,      "vdd-l16-l28"),
	RPMH_VREG("ldo17",  "ldo%s17", &pmic4_nlकरो,      "vdd-l2-l8-l17"),
	RPMH_VREG("ldo18",  "ldo%s18", &pmic4_plकरो,      "vdd-l18-l22"),
	RPMH_VREG("ldo19",  "ldo%s19", &pmic4_plकरो,      "vdd-l13-l19-l21"),
	RPMH_VREG("ldo20",  "ldo%s20", &pmic4_plकरो,      "vdd-l20-l24"),
	RPMH_VREG("ldo21",  "ldo%s21", &pmic4_plकरो,      "vdd-l13-l19-l21"),
	RPMH_VREG("ldo22",  "ldo%s22", &pmic4_plकरो,      "vdd-l18-l22"),
	RPMH_VREG("ldo23",  "ldo%s23", &pmic4_plकरो,      "vdd-l10-l23-l25"),
	RPMH_VREG("ldo24",  "ldo%s24", &pmic4_plकरो,      "vdd-l20-l24"),
	RPMH_VREG("ldo25",  "ldo%s25", &pmic4_plकरो,      "vdd-l10-l23-l25"),
	RPMH_VREG("ldo26",  "ldo%s26", &pmic4_nlकरो,      "vdd-l26"),
	RPMH_VREG("ldo27",  "ldo%s27", &pmic4_nlकरो,      "vdd-l1-l27"),
	RPMH_VREG("ldo28",  "ldo%s28", &pmic4_plकरो,      "vdd-l16-l28"),
	RPMH_VREG("lvs1",   "vs%s1",   &pmic4_lvs,       "vin-lvs-1-2"),
	RPMH_VREG("lvs2",   "vs%s2",   &pmic4_lvs,       "vin-lvs-1-2"),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pmi8998_vreg_data[] = अणु
	RPMH_VREG("bob",    "bob%s1",  &pmic4_bob,       "vdd-bob"),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pm8005_vreg_data[] = अणु
	RPMH_VREG("smps1",  "smp%s1",  &pmic4_ftsmps426, "vdd-s1"),
	RPMH_VREG("smps2",  "smp%s2",  &pmic4_ftsmps426, "vdd-s2"),
	RPMH_VREG("smps3",  "smp%s3",  &pmic4_ftsmps426, "vdd-s3"),
	RPMH_VREG("smps4",  "smp%s4",  &pmic4_ftsmps426, "vdd-s4"),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pm8150_vreg_data[] = अणु
	RPMH_VREG("smps1",  "smp%s1",  &pmic5_ftsmps510, "vdd-s1"),
	RPMH_VREG("smps2",  "smp%s2",  &pmic5_ftsmps510, "vdd-s2"),
	RPMH_VREG("smps3",  "smp%s3",  &pmic5_ftsmps510, "vdd-s3"),
	RPMH_VREG("smps4",  "smp%s4",  &pmic5_hfsmps510,   "vdd-s4"),
	RPMH_VREG("smps5",  "smp%s5",  &pmic5_hfsmps510,   "vdd-s5"),
	RPMH_VREG("smps6",  "smp%s6",  &pmic5_ftsmps510, "vdd-s6"),
	RPMH_VREG("smps7",  "smp%s7",  &pmic5_ftsmps510, "vdd-s7"),
	RPMH_VREG("smps8",  "smp%s8",  &pmic5_ftsmps510, "vdd-s8"),
	RPMH_VREG("smps9",  "smp%s9",  &pmic5_ftsmps510, "vdd-s9"),
	RPMH_VREG("smps10", "smp%s10", &pmic5_ftsmps510, "vdd-s10"),
	RPMH_VREG("ldo1",   "ldo%s1",  &pmic5_nlकरो,      "vdd-l1-l8-l11"),
	RPMH_VREG("ldo2",   "ldo%s2",  &pmic5_plकरो,      "vdd-l2-l10"),
	RPMH_VREG("ldo3",   "ldo%s3",  &pmic5_nlकरो,      "vdd-l3-l4-l5-l18"),
	RPMH_VREG("ldo4",   "ldo%s4",  &pmic5_nlकरो,      "vdd-l3-l4-l5-l18"),
	RPMH_VREG("ldo5",   "ldo%s5",  &pmic5_nlकरो,      "vdd-l3-l4-l5-l18"),
	RPMH_VREG("ldo6",   "ldo%s6",  &pmic5_nlकरो,      "vdd-l6-l9"),
	RPMH_VREG("ldo7",   "ldo%s7",  &pmic5_plकरो,      "vdd-l7-l12-l14-l15"),
	RPMH_VREG("ldo8",   "ldo%s8",  &pmic5_nlकरो,      "vdd-l1-l8-l11"),
	RPMH_VREG("ldo9",   "ldo%s9",  &pmic5_nlकरो,      "vdd-l6-l9"),
	RPMH_VREG("ldo10",  "ldo%s10", &pmic5_plकरो,      "vdd-l2-l10"),
	RPMH_VREG("ldo11",  "ldo%s11", &pmic5_nlकरो,      "vdd-l1-l8-l11"),
	RPMH_VREG("ldo12",  "ldo%s12", &pmic5_plकरो_lv,   "vdd-l7-l12-l14-l15"),
	RPMH_VREG("ldo13",  "ldo%s13", &pmic5_plकरो,      "vdd-l13-l16-l17"),
	RPMH_VREG("ldo14",  "ldo%s14", &pmic5_plकरो_lv,   "vdd-l7-l12-l14-l15"),
	RPMH_VREG("ldo15",  "ldo%s15", &pmic5_plकरो_lv,   "vdd-l7-l12-l14-l15"),
	RPMH_VREG("ldo16",  "ldo%s16", &pmic5_plकरो,      "vdd-l13-l16-l17"),
	RPMH_VREG("ldo17",  "ldo%s17", &pmic5_plकरो,      "vdd-l13-l16-l17"),
	RPMH_VREG("ldo18",  "ldo%s18", &pmic5_nlकरो,      "vdd-l3-l4-l5-l18"),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pm8150l_vreg_data[] = अणु
	RPMH_VREG("smps1",  "smp%s1",  &pmic5_ftsmps510, "vdd-s1"),
	RPMH_VREG("smps2",  "smp%s2",  &pmic5_ftsmps510, "vdd-s2"),
	RPMH_VREG("smps3",  "smp%s3",  &pmic5_ftsmps510, "vdd-s3"),
	RPMH_VREG("smps4",  "smp%s4",  &pmic5_ftsmps510, "vdd-s4"),
	RPMH_VREG("smps5",  "smp%s5",  &pmic5_ftsmps510, "vdd-s5"),
	RPMH_VREG("smps6",  "smp%s6",  &pmic5_ftsmps510, "vdd-s6"),
	RPMH_VREG("smps7",  "smp%s7",  &pmic5_ftsmps510, "vdd-s7"),
	RPMH_VREG("smps8",  "smp%s8",  &pmic5_hfsmps510, "vdd-s8"),
	RPMH_VREG("ldo1",   "ldo%s1",  &pmic5_plकरो_lv,   "vdd-l1-l8"),
	RPMH_VREG("ldo2",   "ldo%s2",  &pmic5_nlकरो,      "vdd-l2-l3"),
	RPMH_VREG("ldo3",   "ldo%s3",  &pmic5_nlकरो,      "vdd-l2-l3"),
	RPMH_VREG("ldo4",   "ldo%s4",  &pmic5_plकरो,      "vdd-l4-l5-l6"),
	RPMH_VREG("ldo5",   "ldo%s5",  &pmic5_plकरो,      "vdd-l4-l5-l6"),
	RPMH_VREG("ldo6",   "ldo%s6",  &pmic5_plकरो,      "vdd-l4-l5-l6"),
	RPMH_VREG("ldo7",   "ldo%s7",  &pmic5_plकरो,      "vdd-l7-l11"),
	RPMH_VREG("ldo8",   "ldo%s8",  &pmic5_plकरो_lv,   "vdd-l1-l8"),
	RPMH_VREG("ldo9",   "ldo%s9",  &pmic5_plकरो,      "vdd-l9-l10"),
	RPMH_VREG("ldo10",  "ldo%s10", &pmic5_plकरो,      "vdd-l9-l10"),
	RPMH_VREG("ldo11",  "ldo%s11", &pmic5_plकरो,      "vdd-l7-l11"),
	RPMH_VREG("bob",    "bob%s1",  &pmic5_bob,       "vdd-bob"),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pm8350_vreg_data[] = अणु
	RPMH_VREG("smps1",  "smp%s1",  &pmic5_ftsmps510, "vdd-s1"),
	RPMH_VREG("smps2",  "smp%s2",  &pmic5_ftsmps510, "vdd-s2"),
	RPMH_VREG("smps3",  "smp%s3",  &pmic5_ftsmps510, "vdd-s3"),
	RPMH_VREG("smps4",  "smp%s4",  &pmic5_ftsmps510, "vdd-s4"),
	RPMH_VREG("smps5",  "smp%s5",  &pmic5_ftsmps510, "vdd-s5"),
	RPMH_VREG("smps6",  "smp%s6",  &pmic5_ftsmps510, "vdd-s6"),
	RPMH_VREG("smps7",  "smp%s7",  &pmic5_ftsmps510, "vdd-s7"),
	RPMH_VREG("smps8",  "smp%s8",  &pmic5_ftsmps510, "vdd-s8"),
	RPMH_VREG("smps9",  "smp%s9",  &pmic5_ftsmps510, "vdd-s9"),
	RPMH_VREG("smps10", "smp%s10", &pmic5_hfsmps510, "vdd-s10"),
	RPMH_VREG("smps11", "smp%s11", &pmic5_hfsmps510, "vdd-s11"),
	RPMH_VREG("smps12", "smp%s12", &pmic5_hfsmps510, "vdd-s12"),
	RPMH_VREG("ldo1",   "ldo%s1",  &pmic5_nlकरो,      "vdd-l1-l4"),
	RPMH_VREG("ldo2",   "ldo%s2",  &pmic5_plकरो,      "vdd-l2-l7"),
	RPMH_VREG("ldo3",   "ldo%s3",  &pmic5_nlकरो,      "vdd-l3-l5"),
	RPMH_VREG("ldo4",   "ldo%s4",  &pmic5_nlकरो,      "vdd-l1-l4"),
	RPMH_VREG("ldo5",   "ldo%s5",  &pmic5_nlकरो,      "vdd-l3-l5"),
	RPMH_VREG("ldo6",   "ldo%s6",  &pmic5_nlकरो,      "vdd-l6-l9-l10"),
	RPMH_VREG("ldo7",   "ldo%s7",  &pmic5_plकरो,      "vdd-l2-l7"),
	RPMH_VREG("ldo8",   "ldo%s8",  &pmic5_nlकरो,      "vdd-l8"),
	RPMH_VREG("ldo9",   "ldo%s9",  &pmic5_nlकरो,      "vdd-l6-l9-l10"),
	RPMH_VREG("ldo10",  "ldo%s10", &pmic5_nlकरो,      "vdd-l6-l9-l10"),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pm8350c_vreg_data[] = अणु
	RPMH_VREG("smps1",  "smp%s1",  &pmic5_hfsmps515, "vdd-s1"),
	RPMH_VREG("smps2",  "smp%s2",  &pmic5_ftsmps510, "vdd-s2"),
	RPMH_VREG("smps3",  "smp%s3",  &pmic5_ftsmps510, "vdd-s3"),
	RPMH_VREG("smps4",  "smp%s4",  &pmic5_ftsmps510, "vdd-s4"),
	RPMH_VREG("smps5",  "smp%s5",  &pmic5_ftsmps510, "vdd-s5"),
	RPMH_VREG("smps6",  "smp%s6",  &pmic5_ftsmps510, "vdd-s6"),
	RPMH_VREG("smps7",  "smp%s7",  &pmic5_ftsmps510, "vdd-s7"),
	RPMH_VREG("smps8",  "smp%s8",  &pmic5_ftsmps510, "vdd-s8"),
	RPMH_VREG("smps9",  "smp%s9",  &pmic5_ftsmps510, "vdd-s9"),
	RPMH_VREG("smps10", "smp%s10", &pmic5_ftsmps510, "vdd-s10"),
	RPMH_VREG("ldo1",   "ldo%s1",  &pmic5_plकरो_lv,   "vdd-l1-l12"),
	RPMH_VREG("ldo2",   "ldo%s2",  &pmic5_plकरो_lv,   "vdd-l2-l8"),
	RPMH_VREG("ldo3",   "ldo%s3",  &pmic5_plकरो,      "vdd-l3-l4-l5-l7-l13"),
	RPMH_VREG("ldo4",   "ldo%s4",  &pmic5_plकरो,      "vdd-l3-l4-l5-l7-l13"),
	RPMH_VREG("ldo5",   "ldo%s5",  &pmic5_plकरो,      "vdd-l3-l4-l5-l7-l13"),
	RPMH_VREG("ldo6",   "ldo%s6",  &pmic5_plकरो,      "vdd-l6-l9-l11"),
	RPMH_VREG("ldo7",   "ldo%s7",  &pmic5_plकरो,      "vdd-l3-l4-l5-l7-l13"),
	RPMH_VREG("ldo8",   "ldo%s8",  &pmic5_plकरो_lv,   "vdd-l2-l8"),
	RPMH_VREG("ldo9",   "ldo%s9",  &pmic5_plकरो,      "vdd-l6-l9-l11"),
	RPMH_VREG("ldo10",  "ldo%s10", &pmic5_nlकरो,      "vdd-l10"),
	RPMH_VREG("ldo11",  "ldo%s11", &pmic5_plकरो,      "vdd-l6-l9-l11"),
	RPMH_VREG("ldo12",  "ldo%s12", &pmic5_plकरो_lv,   "vdd-l1-l12"),
	RPMH_VREG("ldo13",  "ldo%s13", &pmic5_plकरो,      "vdd-l3-l4-l5-l7-l13"),
	RPMH_VREG("bob",    "bob%s1",  &pmic5_bob,       "vdd-bob"),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pm8009_vreg_data[] = अणु
	RPMH_VREG("smps1",  "smp%s1",  &pmic5_hfsmps510, "vdd-s1"),
	RPMH_VREG("smps2",  "smp%s2",  &pmic5_hfsmps515, "vdd-s2"),
	RPMH_VREG("ldo1",   "ldo%s1",  &pmic5_nlकरो,      "vdd-l1"),
	RPMH_VREG("ldo2",   "ldo%s2",  &pmic5_nlकरो,      "vdd-l2"),
	RPMH_VREG("ldo3",   "ldo%s3",  &pmic5_nlकरो,      "vdd-l3"),
	RPMH_VREG("ldo4",   "ldo%s4",  &pmic5_nlकरो,      "vdd-l4"),
	RPMH_VREG("ldo5",   "ldo%s5",  &pmic5_plकरो,      "vdd-l5-l6"),
	RPMH_VREG("ldo6",   "ldo%s6",  &pmic5_plकरो,      "vdd-l5-l6"),
	RPMH_VREG("ldo7",   "ldo%s7",  &pmic5_plकरो_lv,   "vdd-l7"),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pm8009_1_vreg_data[] = अणु
	RPMH_VREG("smps1",  "smp%s1",  &pmic5_hfsmps510, "vdd-s1"),
	RPMH_VREG("smps2",  "smp%s2",  &pmic5_hfsmps515_1, "vdd-s2"),
	RPMH_VREG("ldo1",   "ldo%s1",  &pmic5_nlकरो,      "vdd-l1"),
	RPMH_VREG("ldo2",   "ldo%s2",  &pmic5_nlकरो,      "vdd-l2"),
	RPMH_VREG("ldo3",   "ldo%s3",  &pmic5_nlकरो,      "vdd-l3"),
	RPMH_VREG("ldo4",   "ldo%s4",  &pmic5_nlकरो,      "vdd-l4"),
	RPMH_VREG("ldo5",   "ldo%s5",  &pmic5_plकरो,      "vdd-l5-l6"),
	RPMH_VREG("ldo6",   "ldo%s6",  &pmic5_plकरो,      "vdd-l5-l6"),
	RPMH_VREG("ldo7",   "ldo%s6",  &pmic5_plकरो_lv,   "vdd-l7"),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pm6150_vreg_data[] = अणु
	RPMH_VREG("smps1",  "smp%s1",  &pmic5_ftsmps510, "vdd-s1"),
	RPMH_VREG("smps2",  "smp%s2",  &pmic5_ftsmps510, "vdd-s2"),
	RPMH_VREG("smps3",  "smp%s3",  &pmic5_ftsmps510, "vdd-s3"),
	RPMH_VREG("smps4",  "smp%s4",  &pmic5_hfsmps510, "vdd-s4"),
	RPMH_VREG("smps5",  "smp%s5",  &pmic5_hfsmps510, "vdd-s5"),
	RPMH_VREG("ldo1",   "ldo%s1",  &pmic5_nlकरो,      "vdd-l1"),
	RPMH_VREG("ldo2",   "ldo%s2",  &pmic5_nlकरो,      "vdd-l2-l3"),
	RPMH_VREG("ldo3",   "ldo%s3",  &pmic5_nlकरो,      "vdd-l2-l3"),
	RPMH_VREG("ldo4",   "ldo%s4",  &pmic5_nlकरो,      "vdd-l4-l7-l8"),
	RPMH_VREG("ldo5",   "ldo%s5",  &pmic5_plकरो,   "vdd-l5-l16-l17-l18-l19"),
	RPMH_VREG("ldo6",   "ldo%s6",  &pmic5_nlकरो,      "vdd-l6"),
	RPMH_VREG("ldo7",   "ldo%s7",  &pmic5_nlकरो,      "vdd-l4-l7-l8"),
	RPMH_VREG("ldo8",   "ldo%s8",  &pmic5_nlकरो,      "vdd-l4-l7-l8"),
	RPMH_VREG("ldo9",   "ldo%s9",  &pmic5_nlकरो,      "vdd-l9"),
	RPMH_VREG("ldo10",  "ldo%s10", &pmic5_plकरो_lv,   "vdd-l10-l14-l15"),
	RPMH_VREG("ldo11",  "ldo%s11", &pmic5_plकरो_lv,   "vdd-l11-l12-l13"),
	RPMH_VREG("ldo12",  "ldo%s12", &pmic5_plकरो_lv,   "vdd-l11-l12-l13"),
	RPMH_VREG("ldo13",  "ldo%s13", &pmic5_plकरो_lv,   "vdd-l11-l12-l13"),
	RPMH_VREG("ldo14",  "ldo%s14", &pmic5_plकरो_lv,   "vdd-l10-l14-l15"),
	RPMH_VREG("ldo15",  "ldo%s15", &pmic5_plकरो_lv,   "vdd-l10-l14-l15"),
	RPMH_VREG("ldo16",  "ldo%s16", &pmic5_plकरो,   "vdd-l5-l16-l17-l18-l19"),
	RPMH_VREG("ldo17",  "ldo%s17", &pmic5_plकरो,   "vdd-l5-l16-l17-l18-l19"),
	RPMH_VREG("ldo18",  "ldo%s18", &pmic5_plकरो,   "vdd-l5-l16-l17-l18-l19"),
	RPMH_VREG("ldo19",  "ldo%s19", &pmic5_plकरो,   "vdd-l5-l16-l17-l18-l19"),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pm6150l_vreg_data[] = अणु
	RPMH_VREG("smps1",  "smp%s1",  &pmic5_ftsmps510, "vdd-s1"),
	RPMH_VREG("smps2",  "smp%s2",  &pmic5_ftsmps510, "vdd-s2"),
	RPMH_VREG("smps3",  "smp%s3",  &pmic5_ftsmps510, "vdd-s3"),
	RPMH_VREG("smps4",  "smp%s4",  &pmic5_ftsmps510, "vdd-s4"),
	RPMH_VREG("smps5",  "smp%s5",  &pmic5_ftsmps510, "vdd-s5"),
	RPMH_VREG("smps6",  "smp%s6",  &pmic5_ftsmps510, "vdd-s6"),
	RPMH_VREG("smps7",  "smp%s7",  &pmic5_ftsmps510, "vdd-s7"),
	RPMH_VREG("smps8",  "smp%s8",  &pmic5_hfsmps510, "vdd-s8"),
	RPMH_VREG("ldo1",   "ldo%s1",  &pmic5_plकरो_lv,   "vdd-l1-l8"),
	RPMH_VREG("ldo2",   "ldo%s2",  &pmic5_nlकरो,      "vdd-l2-l3"),
	RPMH_VREG("ldo3",   "ldo%s3",  &pmic5_nlकरो,      "vdd-l2-l3"),
	RPMH_VREG("ldo4",   "ldo%s4",  &pmic5_plकरो,      "vdd-l4-l5-l6"),
	RPMH_VREG("ldo5",   "ldo%s5",  &pmic5_plकरो,      "vdd-l4-l5-l6"),
	RPMH_VREG("ldo6",   "ldo%s6",  &pmic5_plकरो,      "vdd-l4-l5-l6"),
	RPMH_VREG("ldo7",   "ldo%s7",  &pmic5_plकरो,      "vdd-l7-l11"),
	RPMH_VREG("ldo8",   "ldo%s8",  &pmic5_plकरो,      "vdd-l1-l8"),
	RPMH_VREG("ldo9",   "ldo%s9",  &pmic5_plकरो,      "vdd-l9-l10"),
	RPMH_VREG("ldo10",  "ldo%s10", &pmic5_plकरो,      "vdd-l9-l10"),
	RPMH_VREG("ldo11",  "ldo%s11", &pmic5_plकरो,      "vdd-l7-l11"),
	RPMH_VREG("bob",    "bob%s1",  &pmic5_bob,       "vdd-bob"),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pmx55_vreg_data[] = अणु
	RPMH_VREG("smps1",   "smp%s1",    &pmic5_ftsmps510, "vdd-s1"),
	RPMH_VREG("smps2",   "smp%s2",    &pmic5_hfsmps510, "vdd-s2"),
	RPMH_VREG("smps3",   "smp%s3",    &pmic5_hfsmps510, "vdd-s3"),
	RPMH_VREG("smps4",   "smp%s4",    &pmic5_hfsmps510, "vdd-s4"),
	RPMH_VREG("smps5",   "smp%s5",    &pmic5_hfsmps510, "vdd-s5"),
	RPMH_VREG("smps6",   "smp%s6",    &pmic5_ftsmps510, "vdd-s6"),
	RPMH_VREG("smps7",   "smp%s7",    &pmic5_hfsmps510, "vdd-s7"),
	RPMH_VREG("ldo1",    "ldo%s1",    &pmic5_nlकरो,      "vdd-l1-l2"),
	RPMH_VREG("ldo2",    "ldo%s2",    &pmic5_nlकरो,      "vdd-l1-l2"),
	RPMH_VREG("ldo3",    "ldo%s3",    &pmic5_nlकरो,      "vdd-l3-l9"),
	RPMH_VREG("ldo4",    "ldo%s4",    &pmic5_nlकरो,      "vdd-l4-l12"),
	RPMH_VREG("ldo5",    "ldo%s5",    &pmic5_plकरो,      "vdd-l5-l6"),
	RPMH_VREG("ldo6",    "ldo%s6",    &pmic5_plकरो,      "vdd-l5-l6"),
	RPMH_VREG("ldo7",    "ldo%s7",    &pmic5_nlकरो,      "vdd-l7-l8"),
	RPMH_VREG("ldo8",    "ldo%s8",    &pmic5_nlकरो,      "vdd-l7-l8"),
	RPMH_VREG("ldo9",    "ldo%s9",    &pmic5_nlकरो,      "vdd-l3-l9"),
	RPMH_VREG("ldo10",   "ldo%s10",   &pmic5_plकरो,      "vdd-l10-l11-l13"),
	RPMH_VREG("ldo11",   "ldo%s11",   &pmic5_plकरो,      "vdd-l10-l11-l13"),
	RPMH_VREG("ldo12",   "ldo%s12",   &pmic5_nlकरो,      "vdd-l4-l12"),
	RPMH_VREG("ldo13",   "ldo%s13",   &pmic5_plकरो,      "vdd-l10-l11-l13"),
	RPMH_VREG("ldo14",   "ldo%s14",   &pmic5_nlकरो,      "vdd-l14"),
	RPMH_VREG("ldo15",   "ldo%s15",   &pmic5_nlकरो,      "vdd-l15"),
	RPMH_VREG("ldo16",   "ldo%s16",   &pmic5_plकरो,      "vdd-l16"),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pm7325_vreg_data[] = अणु
	RPMH_VREG("smps1",  "smp%s1",  &pmic5_hfsmps510, "vdd-s1"),
	RPMH_VREG("smps2",  "smp%s2",  &pmic5_ftsmps520, "vdd-s2"),
	RPMH_VREG("smps3",  "smp%s3",  &pmic5_ftsmps520, "vdd-s3"),
	RPMH_VREG("smps4",  "smp%s4",  &pmic5_ftsmps520, "vdd-s4"),
	RPMH_VREG("smps5",  "smp%s5",  &pmic5_ftsmps520, "vdd-s5"),
	RPMH_VREG("smps6",  "smp%s6",  &pmic5_ftsmps520, "vdd-s6"),
	RPMH_VREG("smps7",  "smp%s7",  &pmic5_ftsmps520, "vdd-s7"),
	RPMH_VREG("smps8",  "smp%s8",  &pmic5_hfsmps510, "vdd-s8"),
	RPMH_VREG("ldo1",   "ldo%s1",  &pmic5_nlकरो,      "vdd-l1-l4-l12-l15"),
	RPMH_VREG("ldo2",   "ldo%s2",  &pmic5_plकरो,      "vdd-l2-l7"),
	RPMH_VREG("ldo3",   "ldo%s3",  &pmic5_nlकरो,      "vdd-l3"),
	RPMH_VREG("ldo4",   "ldo%s4",  &pmic5_nlकरो,      "vdd-l1-l4-l12-l15"),
	RPMH_VREG("ldo5",   "ldo%s5",  &pmic5_nlकरो,      "vdd-l5"),
	RPMH_VREG("ldo6",   "ldo%s6",  &pmic5_nlकरो,      "vdd-l6-l9-l10"),
	RPMH_VREG("ldo7",   "ldo%s7",  &pmic5_plकरो,      "vdd-l2-l7"),
	RPMH_VREG("ldo8",   "ldo%s8",  &pmic5_nlकरो,      "vdd-l8"),
	RPMH_VREG("ldo9",   "ldo%s9",  &pmic5_nlकरो,      "vdd-l6-l9-l10"),
	RPMH_VREG("ldo10",  "ldo%s10", &pmic5_nlकरो,      "vdd-l6-l9-l10"),
	RPMH_VREG("ldo11",  "ldo%s11", &pmic5_plकरो_lv,   "vdd-l11-l17-l18-l19"),
	RPMH_VREG("ldo12",  "ldo%s12", &pmic5_nlकरो,      "vdd-l1-l4-l12-l15"),
	RPMH_VREG("ldo13",  "ldo%s13", &pmic5_nlकरो,      "vdd-l13"),
	RPMH_VREG("ldo14",  "ldo%s14", &pmic5_nlकरो,      "vdd-l14-l16"),
	RPMH_VREG("ldo15",  "ldo%s15", &pmic5_nlकरो,      "vdd-l1-l4-l12-l15"),
	RPMH_VREG("ldo16",  "ldo%s16", &pmic5_nlकरो,      "vdd-l14-l16"),
	RPMH_VREG("ldo17",  "ldo%s17", &pmic5_plकरो_lv,   "vdd-l11-l17-l18-l19"),
	RPMH_VREG("ldo18",  "ldo%s18", &pmic5_plकरो_lv,   "vdd-l11-l17-l18-l19"),
	RPMH_VREG("ldo19",  "ldo%s19", &pmic5_plकरो_lv,   "vdd-l11-l17-l18-l19"),
पूर्ण;

अटल स्थिर काष्ठा rpmh_vreg_init_data pmr735a_vreg_data[] = अणु
	RPMH_VREG("smps1",  "smp%s1",  &pmic5_ftsmps520, "vdd-s1"),
	RPMH_VREG("smps2",  "smp%s2",  &pmic5_ftsmps520, "vdd-s2"),
	RPMH_VREG("smps3",  "smp%s3",  &pmic5_hfsmps510, "vdd-s3"),
	RPMH_VREG("ldo1",   "ldo%s1",  &pmic5_nlकरो,      "vdd-l1-l2"),
	RPMH_VREG("ldo2",   "ldo%s2",  &pmic5_nlकरो,      "vdd-l1-l2"),
	RPMH_VREG("ldo3",   "ldo%s3",  &pmic5_nlकरो,      "vdd-l3"),
	RPMH_VREG("ldo4",   "ldo%s4",  &pmic5_plकरो_lv,   "vdd-l4"),
	RPMH_VREG("ldo5",   "ldo%s5",  &pmic5_nlकरो,      "vdd-l5-l6"),
	RPMH_VREG("ldo6",   "ldo%s6",  &pmic5_nlकरो,      "vdd-l5-l6"),
	RPMH_VREG("ldo7",   "ldo%s7",  &pmic5_plकरो,      "vdd-l7-bob"),
पूर्ण;

अटल पूर्णांक rpmh_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा rpmh_vreg_init_data *vreg_data;
	काष्ठा device_node *node;
	काष्ठा rpmh_vreg *vreg;
	स्थिर अक्षर *pmic_id;
	पूर्णांक ret;

	vreg_data = of_device_get_match_data(dev);
	अगर (!vreg_data)
		वापस -ENODEV;

	ret = of_property_पढ़ो_string(dev->of_node, "qcom,pmic-id", &pmic_id);
	अगर (ret < 0) अणु
		dev_err(dev, "qcom,pmic-id missing in DT node\n");
		वापस ret;
	पूर्ण

	क्रम_each_available_child_of_node(dev->of_node, node) अणु
		vreg = devm_kzalloc(dev, माप(*vreg), GFP_KERNEL);
		अगर (!vreg) अणु
			of_node_put(node);
			वापस -ENOMEM;
		पूर्ण

		ret = rpmh_regulator_init_vreg(vreg, dev, node, pmic_id,
						vreg_data);
		अगर (ret < 0) अणु
			of_node_put(node);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused rpmh_regulator_match_table[] = अणु
	अणु
		.compatible = "qcom,pm8005-rpmh-regulators",
		.data = pm8005_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pm8009-rpmh-regulators",
		.data = pm8009_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pm8009-1-rpmh-regulators",
		.data = pm8009_1_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pm8150-rpmh-regulators",
		.data = pm8150_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pm8150l-rpmh-regulators",
		.data = pm8150l_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pm8350-rpmh-regulators",
		.data = pm8350_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pm8350c-rpmh-regulators",
		.data = pm8350c_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pm8998-rpmh-regulators",
		.data = pm8998_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pmi8998-rpmh-regulators",
		.data = pmi8998_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pm6150-rpmh-regulators",
		.data = pm6150_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pm6150l-rpmh-regulators",
		.data = pm6150l_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pmc8180-rpmh-regulators",
		.data = pm8150_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pmc8180c-rpmh-regulators",
		.data = pm8150l_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pmx55-rpmh-regulators",
		.data = pmx55_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pm7325-rpmh-regulators",
		.data = pm7325_vreg_data,
	पूर्ण,
	अणु
		.compatible = "qcom,pmr735a-rpmh-regulators",
		.data = pmr735a_vreg_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rpmh_regulator_match_table);

अटल काष्ठा platक्रमm_driver rpmh_regulator_driver = अणु
	.driver = अणु
		.name = "qcom-rpmh-regulator",
		.of_match_table	= of_match_ptr(rpmh_regulator_match_table),
	पूर्ण,
	.probe = rpmh_regulator_probe,
पूर्ण;
module_platक्रमm_driver(rpmh_regulator_driver);

MODULE_DESCRIPTION("Qualcomm RPMh regulator driver");
MODULE_LICENSE("GPL v2");
