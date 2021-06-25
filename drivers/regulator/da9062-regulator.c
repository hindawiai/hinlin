<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Regulator device driver क्रम DA9061 and DA9062.
// Copyright (C) 2015-2017  Dialog Semiconductor

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/da9062/core.h>
#समावेश <linux/mfd/da9062/रेजिस्टरs.h>
#समावेश <dt-bindings/regulator/dlg,da9063-regulator.h>

/* Regulator IDs */
क्रमागत अणु
	DA9061_ID_BUCK1,
	DA9061_ID_BUCK2,
	DA9061_ID_BUCK3,
	DA9061_ID_LDO1,
	DA9061_ID_LDO2,
	DA9061_ID_LDO3,
	DA9061_ID_LDO4,
	DA9061_MAX_REGULATORS,
पूर्ण;

क्रमागत अणु
	DA9062_ID_BUCK1,
	DA9062_ID_BUCK2,
	DA9062_ID_BUCK3,
	DA9062_ID_BUCK4,
	DA9062_ID_LDO1,
	DA9062_ID_LDO2,
	DA9062_ID_LDO3,
	DA9062_ID_LDO4,
	DA9062_MAX_REGULATORS,
पूर्ण;

/* Regulator capabilities and रेजिस्टरs description */
काष्ठा da9062_regulator_info अणु
	काष्ठा regulator_desc desc;
	/* Main रेजिस्टर fields */
	काष्ठा reg_field mode;
	काष्ठा reg_field suspend;
	काष्ठा reg_field sleep;
	काष्ठा reg_field suspend_sleep;
	अचिन्हित पूर्णांक suspend_vsel_reg;
	/* Event detection bit */
	काष्ठा reg_field oc_event;
पूर्ण;

/* Single regulator settings */
काष्ठा da9062_regulator अणु
	काष्ठा regulator_desc			desc;
	काष्ठा regulator_dev			*rdev;
	काष्ठा da9062				*hw;
	स्थिर काष्ठा da9062_regulator_info	*info;

	काष्ठा regmap_field			*mode;
	काष्ठा regmap_field			*suspend;
	काष्ठा regmap_field			*sleep;
	काष्ठा regmap_field			*suspend_sleep;
पूर्ण;

/* Encapsulates all inक्रमmation क्रम the regulators driver */
काष्ठा da9062_regulators अणु
	पूर्णांक					irq_lकरो_lim;
	अचिन्हित				n_regulators;
	/* Array size to be defined during init. Keep at end. */
	काष्ठा da9062_regulator			regulator[];
पूर्ण;

/* Regulator operations */

/* Current limits array (in uA)
 * - DA9061_ID_[BUCK1|BUCK3]
 * - DA9062_ID_[BUCK1|BUCK2|BUCK4]
 * Entry indexes corresponds to रेजिस्टर values.
 */
अटल स्थिर अचिन्हित पूर्णांक da9062_buck_a_limits[] = अणु
	 500000,  600000,  700000,  800000,  900000, 1000000, 1100000, 1200000,
	1300000, 1400000, 1500000, 1600000, 1700000, 1800000, 1900000, 2000000
पूर्ण;

/* Current limits array (in uA)
 * - DA9061_ID_BUCK2
 * - DA9062_ID_BUCK3
 * Entry indexes corresponds to रेजिस्टर values.
 */
अटल स्थिर अचिन्हित पूर्णांक da9062_buck_b_limits[] = अणु
	1500000, 1600000, 1700000, 1800000, 1900000, 2000000, 2100000, 2200000,
	2300000, 2400000, 2500000, 2600000, 2700000, 2800000, 2900000, 3000000
पूर्ण;

अटल अचिन्हित पूर्णांक da9062_map_buck_mode(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल DA9063_BUCK_MODE_SLEEP:
		वापस REGULATOR_MODE_STANDBY;
	हाल DA9063_BUCK_MODE_SYNC:
		वापस REGULATOR_MODE_FAST;
	हाल DA9063_BUCK_MODE_AUTO:
		वापस REGULATOR_MODE_NORMAL;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

अटल पूर्णांक da9062_buck_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित mode)
अणु
	काष्ठा da9062_regulator *regl = rdev_get_drvdata(rdev);
	अचिन्हित val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = DA9063_BUCK_MODE_SYNC;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = DA9063_BUCK_MODE_AUTO;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = DA9063_BUCK_MODE_SLEEP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_field_ग_लिखो(regl->mode, val);
पूर्ण

/*
 * Bucks use single mode रेजिस्टर field क्रम normal operation
 * and suspend state.
 * There are 3 modes to map to: FAST, NORMAL, and STANDBY.
 */

अटल अचिन्हित da9062_buck_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9062_regulator *regl = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(regl->mode, &val);
	अगर (ret < 0)
		वापस ret;

	चयन (val) अणु
	शेष:
		/* Sleep flag bit decides the mode */
		अवरोध;
	हाल DA9063_BUCK_MODE_SLEEP:
		वापस REGULATOR_MODE_STANDBY;
	हाल DA9063_BUCK_MODE_SYNC:
		वापस REGULATOR_MODE_FAST;
	हाल DA9063_BUCK_MODE_AUTO:
		वापस REGULATOR_MODE_NORMAL;
	पूर्ण

	ret = regmap_field_पढ़ो(regl->sleep, &val);
	अगर (ret < 0)
		वापस 0;

	अगर (val)
		वापस REGULATOR_MODE_STANDBY;
	अन्यथा
		वापस REGULATOR_MODE_FAST;
पूर्ण

/*
 * LDOs use sleep flags - one क्रम normal and one क्रम suspend state.
 * There are 2 modes to map to: NORMAL and STANDBY (sleep) क्रम each state.
 */

अटल पूर्णांक da9062_lकरो_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित mode)
अणु
	काष्ठा da9062_regulator *regl = rdev_get_drvdata(rdev);
	अचिन्हित val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		val = 0;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_field_ग_लिखो(regl->sleep, val);
पूर्ण

अटल अचिन्हित da9062_lकरो_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9062_regulator *regl = rdev_get_drvdata(rdev);
	पूर्णांक ret, val;

	ret = regmap_field_पढ़ो(regl->sleep, &val);
	अगर (ret < 0)
		वापस 0;

	अगर (val)
		वापस REGULATOR_MODE_STANDBY;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक da9062_buck_get_status(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret = regulator_is_enabled_regmap(rdev);

	अगर (ret == 0) अणु
		ret = REGULATOR_STATUS_OFF;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		ret = da9062_buck_get_mode(rdev);
		अगर (ret > 0)
			ret = regulator_mode_to_status(ret);
		अन्यथा अगर (ret == 0)
			ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da9062_lकरो_get_status(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret = regulator_is_enabled_regmap(rdev);

	अगर (ret == 0) अणु
		ret = REGULATOR_STATUS_OFF;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		ret = da9062_lकरो_get_mode(rdev);
		अगर (ret > 0)
			ret = regulator_mode_to_status(ret);
		अन्यथा अगर (ret == 0)
			ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da9062_set_suspend_voltage(काष्ठा regulator_dev *rdev, पूर्णांक uv)
अणु
	काष्ठा da9062_regulator *regl = rdev_get_drvdata(rdev);
	स्थिर काष्ठा da9062_regulator_info *rinfo = regl->info;
	पूर्णांक ret, sel;

	sel = regulator_map_voltage_linear(rdev, uv, uv);
	अगर (sel < 0)
		वापस sel;

	sel <<= ffs(rdev->desc->vsel_mask) - 1;

	ret = regmap_update_bits(regl->hw->regmap, rinfo->suspend_vsel_reg,
				 rdev->desc->vsel_mask, sel);

	वापस ret;
पूर्ण

अटल पूर्णांक da9062_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9062_regulator *regl = rdev_get_drvdata(rdev);

	वापस regmap_field_ग_लिखो(regl->suspend, 1);
पूर्ण

अटल पूर्णांक da9062_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9062_regulator *regl = rdev_get_drvdata(rdev);

	वापस regmap_field_ग_लिखो(regl->suspend, 0);
पूर्ण

अटल पूर्णांक da9062_buck_set_suspend_mode(काष्ठा regulator_dev *rdev,
					अचिन्हित mode)
अणु
	काष्ठा da9062_regulator *regl = rdev_get_drvdata(rdev);
	पूर्णांक val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = DA9063_BUCK_MODE_SYNC;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = DA9063_BUCK_MODE_AUTO;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = DA9063_BUCK_MODE_SLEEP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_field_ग_लिखो(regl->mode, val);
पूर्ण

अटल पूर्णांक da9062_lकरो_set_suspend_mode(काष्ठा regulator_dev *rdev,
						अचिन्हित mode)
अणु
	काष्ठा da9062_regulator *regl = rdev_get_drvdata(rdev);
	अचिन्हित val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		val = 0;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_field_ग_लिखो(regl->suspend_sleep, val);
पूर्ण

अटल स्थिर काष्ठा regulator_ops da9062_buck_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.set_current_limit	= regulator_set_current_limit_regmap,
	.get_current_limit	= regulator_get_current_limit_regmap,
	.set_mode		= da9062_buck_set_mode,
	.get_mode		= da9062_buck_get_mode,
	.get_status		= da9062_buck_get_status,
	.set_suspend_voltage	= da9062_set_suspend_voltage,
	.set_suspend_enable	= da9062_suspend_enable,
	.set_suspend_disable	= da9062_suspend_disable,
	.set_suspend_mode	= da9062_buck_set_suspend_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops da9062_lकरो_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.set_mode		= da9062_lकरो_set_mode,
	.get_mode		= da9062_lकरो_get_mode,
	.get_status		= da9062_lकरो_get_status,
	.set_suspend_voltage	= da9062_set_suspend_voltage,
	.set_suspend_enable	= da9062_suspend_enable,
	.set_suspend_disable	= da9062_suspend_disable,
	.set_suspend_mode	= da9062_lकरो_set_suspend_mode,
पूर्ण;

/* DA9061 Regulator inक्रमmation */
अटल स्थिर काष्ठा da9062_regulator_info local_da9061_regulator_info[] = अणु
	अणु
		.desc.id = DA9061_ID_BUCK1,
		.desc.name = "DA9061 BUCK1",
		.desc.of_match = of_match_ptr("buck1"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (300) * 1000,
		.desc.uV_step = (10) * 1000,
		.desc.n_voltages = ((1570) - (300))/(10) + 1,
		.desc.curr_table = da9062_buck_a_limits,
		.desc.n_current_limits = ARRAY_SIZE(da9062_buck_a_limits),
		.desc.csel_reg = DA9062AA_BUCK_ILIM_C,
		.desc.csel_mask = DA9062AA_BUCK1_ILIM_MASK,
		.desc.enable_reg = DA9062AA_BUCK1_CONT,
		.desc.enable_mask = DA9062AA_BUCK1_EN_MASK,
		.desc.vsel_reg = DA9062AA_VBUCK1_A,
		.desc.vsel_mask = DA9062AA_VBUCK1_A_MASK,
		.desc.linear_min_sel = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sleep = REG_FIELD(DA9062AA_VBUCK1_A,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK1_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK1_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VBUCK1_B,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK1_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK1_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VBUCK1_B,
		.mode = REG_FIELD(DA9062AA_BUCK1_CFG,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK1_MODE_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK1_MODE_MASK)) - 1),
		.suspend = REG_FIELD(DA9062AA_BUCK1_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK1_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_BUCK1_CONF_MASK) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9061_ID_BUCK2,
		.desc.name = "DA9061 BUCK2",
		.desc.of_match = of_match_ptr("buck2"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (800) * 1000,
		.desc.uV_step = (20) * 1000,
		.desc.n_voltages = ((3340) - (800))/(20) + 1,
		.desc.curr_table = da9062_buck_b_limits,
		.desc.n_current_limits = ARRAY_SIZE(da9062_buck_b_limits),
		.desc.csel_reg = DA9062AA_BUCK_ILIM_A,
		.desc.csel_mask = DA9062AA_BUCK3_ILIM_MASK,
		.desc.enable_reg = DA9062AA_BUCK3_CONT,
		.desc.enable_mask = DA9062AA_BUCK3_EN_MASK,
		.desc.vsel_reg = DA9062AA_VBUCK3_A,
		.desc.vsel_mask = DA9062AA_VBUCK3_A_MASK,
		.desc.linear_min_sel = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sleep = REG_FIELD(DA9062AA_VBUCK3_A,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK3_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK3_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VBUCK3_B,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK3_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK3_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VBUCK3_B,
		.mode = REG_FIELD(DA9062AA_BUCK3_CFG,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK3_MODE_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK3_MODE_MASK)) - 1),
		.suspend = REG_FIELD(DA9062AA_BUCK3_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK3_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_BUCK3_CONF_MASK) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9061_ID_BUCK3,
		.desc.name = "DA9061 BUCK3",
		.desc.of_match = of_match_ptr("buck3"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (530) * 1000,
		.desc.uV_step = (10) * 1000,
		.desc.n_voltages = ((1800) - (530))/(10) + 1,
		.desc.curr_table = da9062_buck_a_limits,
		.desc.n_current_limits = ARRAY_SIZE(da9062_buck_a_limits),
		.desc.csel_reg = DA9062AA_BUCK_ILIM_B,
		.desc.csel_mask = DA9062AA_BUCK4_ILIM_MASK,
		.desc.enable_reg = DA9062AA_BUCK4_CONT,
		.desc.enable_mask = DA9062AA_BUCK4_EN_MASK,
		.desc.vsel_reg = DA9062AA_VBUCK4_A,
		.desc.vsel_mask = DA9062AA_VBUCK4_A_MASK,
		.desc.linear_min_sel = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sleep = REG_FIELD(DA9062AA_VBUCK4_A,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK4_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK4_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VBUCK4_B,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK4_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK4_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VBUCK4_B,
		.mode = REG_FIELD(DA9062AA_BUCK4_CFG,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK4_MODE_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK4_MODE_MASK)) - 1),
		.suspend = REG_FIELD(DA9062AA_BUCK4_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK4_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_BUCK4_CONF_MASK) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9061_ID_LDO1,
		.desc.name = "DA9061 LDO1",
		.desc.of_match = of_match_ptr("ldo1"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_lकरो_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_voltages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VLDO_A_MIN_SEL,
		.desc.enable_reg = DA9062AA_LDO1_CONT,
		.desc.enable_mask = DA9062AA_LDO1_EN_MASK,
		.desc.vsel_reg = DA9062AA_VLDO1_A,
		.desc.vsel_mask = DA9062AA_VLDO1_A_MASK,
		.desc.linear_min_sel = DA9062AA_VLDO_A_MIN_SEL,
		.sleep = REG_FIELD(DA9062AA_VLDO1_A,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO1_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO1_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VLDO1_B,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO1_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO1_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VLDO1_B,
		.suspend = REG_FIELD(DA9062AA_LDO1_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO1_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_LDO1_CONF_MASK) - 1),
		.oc_event = REG_FIELD(DA9062AA_STATUS_D,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO1_ILIM_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO1_ILIM_MASK)) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9061_ID_LDO2,
		.desc.name = "DA9061 LDO2",
		.desc.of_match = of_match_ptr("ldo2"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_lकरो_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_voltages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VLDO_A_MIN_SEL,
		.desc.enable_reg = DA9062AA_LDO2_CONT,
		.desc.enable_mask = DA9062AA_LDO2_EN_MASK,
		.desc.vsel_reg = DA9062AA_VLDO2_A,
		.desc.vsel_mask = DA9062AA_VLDO2_A_MASK,
		.desc.linear_min_sel = DA9062AA_VLDO_A_MIN_SEL,
		.sleep = REG_FIELD(DA9062AA_VLDO2_A,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO2_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO2_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VLDO2_B,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO2_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO2_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VLDO2_B,
		.suspend = REG_FIELD(DA9062AA_LDO2_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO2_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_LDO2_CONF_MASK) - 1),
		.oc_event = REG_FIELD(DA9062AA_STATUS_D,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO2_ILIM_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO2_ILIM_MASK)) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9061_ID_LDO3,
		.desc.name = "DA9061 LDO3",
		.desc.of_match = of_match_ptr("ldo3"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_lकरो_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_voltages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VLDO_A_MIN_SEL,
		.desc.enable_reg = DA9062AA_LDO3_CONT,
		.desc.enable_mask = DA9062AA_LDO3_EN_MASK,
		.desc.vsel_reg = DA9062AA_VLDO3_A,
		.desc.vsel_mask = DA9062AA_VLDO3_A_MASK,
		.desc.linear_min_sel = DA9062AA_VLDO_A_MIN_SEL,
		.sleep = REG_FIELD(DA9062AA_VLDO3_A,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO3_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO3_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VLDO3_B,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO3_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO3_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VLDO3_B,
		.suspend = REG_FIELD(DA9062AA_LDO3_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO3_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_LDO3_CONF_MASK) - 1),
		.oc_event = REG_FIELD(DA9062AA_STATUS_D,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO3_ILIM_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO3_ILIM_MASK)) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9061_ID_LDO4,
		.desc.name = "DA9061 LDO4",
		.desc.of_match = of_match_ptr("ldo4"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_lकरो_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_voltages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VLDO_A_MIN_SEL,
		.desc.enable_reg = DA9062AA_LDO4_CONT,
		.desc.enable_mask = DA9062AA_LDO4_EN_MASK,
		.desc.vsel_reg = DA9062AA_VLDO4_A,
		.desc.vsel_mask = DA9062AA_VLDO4_A_MASK,
		.desc.linear_min_sel = DA9062AA_VLDO_A_MIN_SEL,
		.sleep = REG_FIELD(DA9062AA_VLDO4_A,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO4_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO4_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VLDO4_B,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO4_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO4_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VLDO4_B,
		.suspend = REG_FIELD(DA9062AA_LDO4_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO4_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_LDO4_CONF_MASK) - 1),
		.oc_event = REG_FIELD(DA9062AA_STATUS_D,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO4_ILIM_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO4_ILIM_MASK)) - 1),
	पूर्ण,
पूर्ण;

/* DA9062 Regulator inक्रमmation */
अटल स्थिर काष्ठा da9062_regulator_info local_da9062_regulator_info[] = अणु
	अणु
		.desc.id = DA9062_ID_BUCK1,
		.desc.name = "DA9062 BUCK1",
		.desc.of_match = of_match_ptr("buck1"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (300) * 1000,
		.desc.uV_step = (10) * 1000,
		.desc.n_voltages = ((1570) - (300))/(10) + 1,
		.desc.curr_table = da9062_buck_a_limits,
		.desc.n_current_limits = ARRAY_SIZE(da9062_buck_a_limits),
		.desc.csel_reg = DA9062AA_BUCK_ILIM_C,
		.desc.csel_mask = DA9062AA_BUCK1_ILIM_MASK,
		.desc.enable_reg = DA9062AA_BUCK1_CONT,
		.desc.enable_mask = DA9062AA_BUCK1_EN_MASK,
		.desc.vsel_reg = DA9062AA_VBUCK1_A,
		.desc.vsel_mask = DA9062AA_VBUCK1_A_MASK,
		.desc.linear_min_sel = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sleep = REG_FIELD(DA9062AA_VBUCK1_A,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK1_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK1_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VBUCK1_B,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK1_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK1_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VBUCK1_B,
		.mode = REG_FIELD(DA9062AA_BUCK1_CFG,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK1_MODE_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK1_MODE_MASK)) - 1),
		.suspend = REG_FIELD(DA9062AA_BUCK1_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK1_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_BUCK1_CONF_MASK) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9062_ID_BUCK2,
		.desc.name = "DA9062 BUCK2",
		.desc.of_match = of_match_ptr("buck2"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (300) * 1000,
		.desc.uV_step = (10) * 1000,
		.desc.n_voltages = ((1570) - (300))/(10) + 1,
		.desc.curr_table = da9062_buck_a_limits,
		.desc.n_current_limits = ARRAY_SIZE(da9062_buck_a_limits),
		.desc.csel_reg = DA9062AA_BUCK_ILIM_C,
		.desc.csel_mask = DA9062AA_BUCK2_ILIM_MASK,
		.desc.enable_reg = DA9062AA_BUCK2_CONT,
		.desc.enable_mask = DA9062AA_BUCK2_EN_MASK,
		.desc.vsel_reg = DA9062AA_VBUCK2_A,
		.desc.vsel_mask = DA9062AA_VBUCK2_A_MASK,
		.desc.linear_min_sel = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sleep = REG_FIELD(DA9062AA_VBUCK2_A,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK2_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK2_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VBUCK2_B,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK2_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK2_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VBUCK2_B,
		.mode = REG_FIELD(DA9062AA_BUCK2_CFG,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK2_MODE_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK2_MODE_MASK)) - 1),
		.suspend = REG_FIELD(DA9062AA_BUCK2_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK2_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_BUCK2_CONF_MASK) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9062_ID_BUCK3,
		.desc.name = "DA9062 BUCK3",
		.desc.of_match = of_match_ptr("buck3"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (800) * 1000,
		.desc.uV_step = (20) * 1000,
		.desc.n_voltages = ((3340) - (800))/(20) + 1,
		.desc.curr_table = da9062_buck_b_limits,
		.desc.n_current_limits = ARRAY_SIZE(da9062_buck_b_limits),
		.desc.csel_reg = DA9062AA_BUCK_ILIM_A,
		.desc.csel_mask = DA9062AA_BUCK3_ILIM_MASK,
		.desc.enable_reg = DA9062AA_BUCK3_CONT,
		.desc.enable_mask = DA9062AA_BUCK3_EN_MASK,
		.desc.vsel_reg = DA9062AA_VBUCK3_A,
		.desc.vsel_mask = DA9062AA_VBUCK3_A_MASK,
		.desc.linear_min_sel = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sleep = REG_FIELD(DA9062AA_VBUCK3_A,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK3_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK3_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VBUCK3_B,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK3_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK3_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VBUCK3_B,
		.mode = REG_FIELD(DA9062AA_BUCK3_CFG,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK3_MODE_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK3_MODE_MASK)) - 1),
		.suspend = REG_FIELD(DA9062AA_BUCK3_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK3_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_BUCK3_CONF_MASK) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9062_ID_BUCK4,
		.desc.name = "DA9062 BUCK4",
		.desc.of_match = of_match_ptr("buck4"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_buck_ops,
		.desc.min_uV = (530) * 1000,
		.desc.uV_step = (10) * 1000,
		.desc.n_voltages = ((1800) - (530))/(10) + 1,
		.desc.curr_table = da9062_buck_a_limits,
		.desc.n_current_limits = ARRAY_SIZE(da9062_buck_a_limits),
		.desc.csel_reg = DA9062AA_BUCK_ILIM_B,
		.desc.csel_mask = DA9062AA_BUCK4_ILIM_MASK,
		.desc.enable_reg = DA9062AA_BUCK4_CONT,
		.desc.enable_mask = DA9062AA_BUCK4_EN_MASK,
		.desc.vsel_reg = DA9062AA_VBUCK4_A,
		.desc.vsel_mask = DA9062AA_VBUCK4_A_MASK,
		.desc.linear_min_sel = 0,
		.desc.of_map_mode = da9062_map_buck_mode,
		.sleep = REG_FIELD(DA9062AA_VBUCK4_A,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK4_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK4_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VBUCK4_B,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK4_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK4_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VBUCK4_B,
		.mode = REG_FIELD(DA9062AA_BUCK4_CFG,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK4_MODE_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_BUCK4_MODE_MASK)) - 1),
		.suspend = REG_FIELD(DA9062AA_BUCK4_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_BUCK4_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_BUCK4_CONF_MASK) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9062_ID_LDO1,
		.desc.name = "DA9062 LDO1",
		.desc.of_match = of_match_ptr("ldo1"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_lकरो_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_voltages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VLDO_A_MIN_SEL,
		.desc.enable_reg = DA9062AA_LDO1_CONT,
		.desc.enable_mask = DA9062AA_LDO1_EN_MASK,
		.desc.vsel_reg = DA9062AA_VLDO1_A,
		.desc.vsel_mask = DA9062AA_VLDO1_A_MASK,
		.desc.linear_min_sel = DA9062AA_VLDO_A_MIN_SEL,
		.sleep = REG_FIELD(DA9062AA_VLDO1_A,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO1_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO1_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VLDO1_B,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO1_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO1_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VLDO1_B,
		.suspend = REG_FIELD(DA9062AA_LDO1_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO1_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_LDO1_CONF_MASK) - 1),
		.oc_event = REG_FIELD(DA9062AA_STATUS_D,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO1_ILIM_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO1_ILIM_MASK)) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9062_ID_LDO2,
		.desc.name = "DA9062 LDO2",
		.desc.of_match = of_match_ptr("ldo2"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_lकरो_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_voltages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VLDO_A_MIN_SEL,
		.desc.enable_reg = DA9062AA_LDO2_CONT,
		.desc.enable_mask = DA9062AA_LDO2_EN_MASK,
		.desc.vsel_reg = DA9062AA_VLDO2_A,
		.desc.vsel_mask = DA9062AA_VLDO2_A_MASK,
		.desc.linear_min_sel = DA9062AA_VLDO_A_MIN_SEL,
		.sleep = REG_FIELD(DA9062AA_VLDO2_A,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO2_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO2_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VLDO2_B,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO2_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO2_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VLDO2_B,
		.suspend = REG_FIELD(DA9062AA_LDO2_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO2_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_LDO2_CONF_MASK) - 1),
		.oc_event = REG_FIELD(DA9062AA_STATUS_D,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO2_ILIM_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO2_ILIM_MASK)) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9062_ID_LDO3,
		.desc.name = "DA9062 LDO3",
		.desc.of_match = of_match_ptr("ldo3"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_lकरो_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_voltages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VLDO_A_MIN_SEL,
		.desc.enable_reg = DA9062AA_LDO3_CONT,
		.desc.enable_mask = DA9062AA_LDO3_EN_MASK,
		.desc.vsel_reg = DA9062AA_VLDO3_A,
		.desc.vsel_mask = DA9062AA_VLDO3_A_MASK,
		.desc.linear_min_sel = DA9062AA_VLDO_A_MIN_SEL,
		.sleep = REG_FIELD(DA9062AA_VLDO3_A,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO3_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO3_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VLDO3_B,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO3_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO3_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VLDO3_B,
		.suspend = REG_FIELD(DA9062AA_LDO3_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO3_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_LDO3_CONF_MASK) - 1),
		.oc_event = REG_FIELD(DA9062AA_STATUS_D,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO3_ILIM_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO3_ILIM_MASK)) - 1),
	पूर्ण,
	अणु
		.desc.id = DA9062_ID_LDO4,
		.desc.name = "DA9062 LDO4",
		.desc.of_match = of_match_ptr("ldo4"),
		.desc.regulators_node = of_match_ptr("regulators"),
		.desc.ops = &da9062_lकरो_ops,
		.desc.min_uV = (900) * 1000,
		.desc.uV_step = (50) * 1000,
		.desc.n_voltages = ((3600) - (900))/(50) + 1
				+ DA9062AA_VLDO_A_MIN_SEL,
		.desc.enable_reg = DA9062AA_LDO4_CONT,
		.desc.enable_mask = DA9062AA_LDO4_EN_MASK,
		.desc.vsel_reg = DA9062AA_VLDO4_A,
		.desc.vsel_mask = DA9062AA_VLDO4_A_MASK,
		.desc.linear_min_sel = DA9062AA_VLDO_A_MIN_SEL,
		.sleep = REG_FIELD(DA9062AA_VLDO4_A,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO4_SL_A_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO4_SL_A_MASK)) - 1),
		.suspend_sleep = REG_FIELD(DA9062AA_VLDO4_B,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO4_SL_B_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO4_SL_B_MASK)) - 1),
		.suspend_vsel_reg = DA9062AA_VLDO4_B,
		.suspend = REG_FIELD(DA9062AA_LDO4_CONT,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO4_CONF_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz(DA9062AA_LDO4_CONF_MASK) - 1),
		.oc_event = REG_FIELD(DA9062AA_STATUS_D,
			__builtin_ffs((पूर्णांक)DA9062AA_LDO4_ILIM_MASK) - 1,
			माप(अचिन्हित पूर्णांक) * 8 -
			__builtin_clz((DA9062AA_LDO4_ILIM_MASK)) - 1),
	पूर्ण,
पूर्ण;

/* Regulator पूर्णांकerrupt handlers */
अटल irqवापस_t da9062_lकरो_lim_event(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9062_regulators *regulators = data;
	काष्ठा da9062 *hw = regulators->regulator[0].hw;
	काष्ठा da9062_regulator *regl;
	पूर्णांक handled = IRQ_NONE;
	पूर्णांक bits, i, ret;

	ret = regmap_पढ़ो(hw->regmap, DA9062AA_STATUS_D, &bits);
	अगर (ret < 0) अणु
		dev_err(hw->dev,
			"Failed to read LDO overcurrent indicator\n");
		जाओ lकरो_lim_error;
	पूर्ण

	क्रम (i = regulators->n_regulators - 1; i >= 0; i--) अणु
		regl = &regulators->regulator[i];
		अगर (regl->info->oc_event.reg != DA9062AA_STATUS_D)
			जारी;

		अगर (BIT(regl->info->oc_event.lsb) & bits) अणु
			regulator_notअगरier_call_chain(regl->rdev,
					REGULATOR_EVENT_OVER_CURRENT, शून्य);
			handled = IRQ_HANDLED;
		पूर्ण
	पूर्ण

lकरो_lim_error:
	वापस handled;
पूर्ण

अटल पूर्णांक da9062_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9062 *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा da9062_regulators *regulators;
	काष्ठा da9062_regulator *regl;
	काष्ठा regulator_config config = अणु पूर्ण;
	स्थिर काष्ठा da9062_regulator_info *rinfo;
	पूर्णांक irq, n, ret;
	पूर्णांक max_regulators;

	चयन (chip->chip_type) अणु
	हाल COMPAT_TYPE_DA9061:
		max_regulators = DA9061_MAX_REGULATORS;
		rinfo = local_da9061_regulator_info;
		अवरोध;
	हाल COMPAT_TYPE_DA9062:
		max_regulators = DA9062_MAX_REGULATORS;
		rinfo = local_da9062_regulator_info;
		अवरोध;
	शेष:
		dev_err(chip->dev, "Unrecognised chip type\n");
		वापस -ENODEV;
	पूर्ण

	/* Allocate memory required by usable regulators */
	regulators = devm_kzalloc(&pdev->dev, काष्ठा_size(regulators, regulator,
				  max_regulators), GFP_KERNEL);
	अगर (!regulators)
		वापस -ENOMEM;

	regulators->n_regulators = max_regulators;
	platक्रमm_set_drvdata(pdev, regulators);

	क्रम (n = 0; n < regulators->n_regulators; n++) अणु
		/* Initialise regulator काष्ठाure */
		regl = &regulators->regulator[n];
		regl->hw = chip;
		regl->info = &rinfo[n];
		regl->desc = regl->info->desc;
		regl->desc.type = REGULATOR_VOLTAGE;
		regl->desc.owner = THIS_MODULE;

		अगर (regl->info->mode.reg) अणु
			regl->mode = devm_regmap_field_alloc(
					&pdev->dev,
					chip->regmap,
					regl->info->mode);
			अगर (IS_ERR(regl->mode))
				वापस PTR_ERR(regl->mode);
		पूर्ण

		अगर (regl->info->suspend.reg) अणु
			regl->suspend = devm_regmap_field_alloc(
					&pdev->dev,
					chip->regmap,
					regl->info->suspend);
			अगर (IS_ERR(regl->suspend))
				वापस PTR_ERR(regl->suspend);
		पूर्ण

		अगर (regl->info->sleep.reg) अणु
			regl->sleep = devm_regmap_field_alloc(
					&pdev->dev,
					chip->regmap,
					regl->info->sleep);
			अगर (IS_ERR(regl->sleep))
				वापस PTR_ERR(regl->sleep);
		पूर्ण

		अगर (regl->info->suspend_sleep.reg) अणु
			regl->suspend_sleep = devm_regmap_field_alloc(
					&pdev->dev,
					chip->regmap,
					regl->info->suspend_sleep);
			अगर (IS_ERR(regl->suspend_sleep))
				वापस PTR_ERR(regl->suspend_sleep);
		पूर्ण

		/* Register regulator */
		स_रखो(&config, 0, माप(config));
		config.dev = chip->dev;
		config.driver_data = regl;
		config.regmap = chip->regmap;

		regl->rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regl->desc,
						     &config);
		अगर (IS_ERR(regl->rdev)) अणु
			dev_err(&pdev->dev,
				"Failed to register %s regulator\n",
				regl->desc.name);
			वापस PTR_ERR(regl->rdev);
		पूर्ण
	पूर्ण

	/* LDOs overcurrent event support */
	irq = platक्रमm_get_irq_byname(pdev, "LDO_LIM");
	अगर (irq < 0)
		वापस irq;
	regulators->irq_lकरो_lim = irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
					शून्य, da9062_lकरो_lim_event,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					"LDO_LIM", regulators);
	अगर (ret) अणु
		dev_warn(&pdev->dev,
			 "Failed to request LDO_LIM IRQ.\n");
		regulators->irq_lकरो_lim = -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9062_regulator_driver = अणु
	.driver = अणु
		.name = "da9062-regulators",
	पूर्ण,
	.probe = da9062_regulator_probe,
पूर्ण;

अटल पूर्णांक __init da9062_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&da9062_regulator_driver);
पूर्ण
subsys_initcall(da9062_regulator_init);

अटल व्योम __निकास da9062_regulator_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&da9062_regulator_driver);
पूर्ण
module_निकास(da9062_regulator_cleanup);

/* Module inक्रमmation */
MODULE_AUTHOR("S Twiss <stwiss.opensource@diasemi.com>");
MODULE_DESCRIPTION("REGULATOR device driver for Dialog DA9062 and DA9061");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9062-regulators");
