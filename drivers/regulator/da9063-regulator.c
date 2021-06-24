<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Regulator driver क्रम DA9063 PMIC series
//
// Copyright 2012 Dialog Semiconductors Ltd.
// Copyright 2013 Philipp Zabel, Pengutronix
//
// Author: Krystian Garbaciak <krystian.garbaciak@diasemi.com>

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
#समावेश <linux/mfd/da9063/core.h>
#समावेश <linux/mfd/da9063/रेजिस्टरs.h>


/* Definition क्रम रेजिस्टरing regmap bit fields using a mask */
#घोषणा BFIELD(_reg, _mask) \
	REG_FIELD(_reg, __builtin_ffs((पूर्णांक)_mask) - 1, \
		माप(अचिन्हित पूर्णांक) * 8 - __builtin_clz((_mask)) - 1)

/* DA9063 and DA9063L regulator IDs */
क्रमागत अणु
	/* BUCKs */
	DA9063_ID_BCORE1,
	DA9063_ID_BCORE2,
	DA9063_ID_BPRO,
	DA9063_ID_BMEM,
	DA9063_ID_BIO,
	DA9063_ID_BPERI,

	/* BCORE1 and BCORE2 in merged mode */
	DA9063_ID_BCORES_MERGED,
	/* BMEM and BIO in merged mode */
	DA9063_ID_BMEM_BIO_MERGED,
	/* When two BUCKs are merged, they cannot be reused separately */

	/* LDOs on both DA9063 and DA9063L */
	DA9063_ID_LDO3,
	DA9063_ID_LDO7,
	DA9063_ID_LDO8,
	DA9063_ID_LDO9,
	DA9063_ID_LDO11,

	/* DA9063-only LDOs */
	DA9063_ID_LDO1,
	DA9063_ID_LDO2,
	DA9063_ID_LDO4,
	DA9063_ID_LDO5,
	DA9063_ID_LDO6,
	DA9063_ID_LDO10,
पूर्ण;

/* Old regulator platक्रमm data */
काष्ठा da9063_regulator_data अणु
	पूर्णांक				id;
	काष्ठा regulator_init_data	*initdata;
पूर्ण;

काष्ठा da9063_regulators_pdata अणु
	अचिन्हित पूर्णांक			n_regulators;
	काष्ठा da9063_regulator_data	*regulator_data;
पूर्ण;

/* Regulator capabilities and रेजिस्टरs description */
काष्ठा da9063_regulator_info अणु
	काष्ठा regulator_desc desc;

	/* DA9063 मुख्य रेजिस्टर fields */
	काष्ठा reg_field mode;		/* buck mode of operation */
	काष्ठा reg_field suspend;
	काष्ठा reg_field sleep;
	काष्ठा reg_field suspend_sleep;
	अचिन्हित पूर्णांक suspend_vsel_reg;

	/* DA9063 event detection bit */
	काष्ठा reg_field oc_event;
पूर्ण;

/* Macros क्रम LDO */
#घोषणा DA9063_LDO(chip, regl_name, min_mV, step_mV, max_mV) \
	.desc.id = chip##_ID_##regl_name, \
	.desc.name = __stringअगरy(chip##_##regl_name), \
	.desc.ops = &da9063_lकरो_ops, \
	.desc.min_uV = (min_mV) * 1000, \
	.desc.uV_step = (step_mV) * 1000, \
	.desc.n_voltages = (((max_mV) - (min_mV))/(step_mV) + 1 \
		+ (DA9063_V##regl_name##_BIAS)), \
	.desc.enable_reg = DA9063_REG_##regl_name##_CONT, \
	.desc.enable_mask = DA9063_LDO_EN, \
	.desc.vsel_reg = DA9063_REG_V##regl_name##_A, \
	.desc.vsel_mask = DA9063_V##regl_name##_MASK, \
	.desc.linear_min_sel = DA9063_V##regl_name##_BIAS, \
	.sleep = BFIELD(DA9063_REG_V##regl_name##_A, DA9063_LDO_SL), \
	.suspend = BFIELD(DA9063_REG_##regl_name##_CONT, DA9063_LDO_CONF), \
	.suspend_sleep = BFIELD(DA9063_REG_V##regl_name##_B, DA9063_LDO_SL), \
	.suspend_vsel_reg = DA9063_REG_V##regl_name##_B

/* Macros क्रम voltage DC/DC converters (BUCKs) */
#घोषणा DA9063_BUCK(chip, regl_name, min_mV, step_mV, max_mV, limits_array, \
		    creg, cmask) \
	.desc.id = chip##_ID_##regl_name, \
	.desc.name = __stringअगरy(chip##_##regl_name), \
	.desc.ops = &da9063_buck_ops, \
	.desc.min_uV = (min_mV) * 1000, \
	.desc.uV_step = (step_mV) * 1000, \
	.desc.n_voltages = ((max_mV) - (min_mV))/(step_mV) + 1, \
	.desc.csel_reg = (creg), \
	.desc.csel_mask = (cmask), \
	.desc.curr_table = limits_array, \
	.desc.n_current_limits = ARRAY_SIZE(limits_array)

#घोषणा DA9063_BUCK_COMMON_FIELDS(regl_name) \
	.desc.enable_reg = DA9063_REG_##regl_name##_CONT, \
	.desc.enable_mask = DA9063_BUCK_EN, \
	.desc.vsel_reg = DA9063_REG_V##regl_name##_A, \
	.desc.vsel_mask = DA9063_VBUCK_MASK, \
	.desc.linear_min_sel = DA9063_VBUCK_BIAS, \
	.sleep = BFIELD(DA9063_REG_V##regl_name##_A, DA9063_BUCK_SL), \
	.suspend = BFIELD(DA9063_REG_##regl_name##_CONT, DA9063_BUCK_CONF), \
	.suspend_sleep = BFIELD(DA9063_REG_V##regl_name##_B, DA9063_BUCK_SL), \
	.suspend_vsel_reg = DA9063_REG_V##regl_name##_B, \
	.mode = BFIELD(DA9063_REG_##regl_name##_CFG, DA9063_BUCK_MODE_MASK)

/* Defines asignment of regulators info table to chip model */
काष्ठा da9063_dev_model अणु
	स्थिर काष्ठा da9063_regulator_info	*regulator_info;
	अचिन्हित पूर्णांक				n_regulators;
	क्रमागत da9063_type			type;
पूर्ण;

/* Single regulator settings */
काष्ठा da9063_regulator अणु
	काष्ठा regulator_desc			desc;
	काष्ठा regulator_dev			*rdev;
	काष्ठा da9063				*hw;
	स्थिर काष्ठा da9063_regulator_info	*info;

	काष्ठा regmap_field			*mode;
	काष्ठा regmap_field			*suspend;
	काष्ठा regmap_field			*sleep;
	काष्ठा regmap_field			*suspend_sleep;
पूर्ण;

/* Encapsulates all inक्रमmation क्रम the regulators driver */
काष्ठा da9063_regulators अणु
	अचिन्हित पूर्णांक				n_regulators;
	/* Array size to be defined during init. Keep at end. */
	काष्ठा da9063_regulator			regulator[];
पूर्ण;

/* BUCK modes क्रम DA9063 */
क्रमागत अणु
	BUCK_MODE_MANUAL,	/* 0 */
	BUCK_MODE_SLEEP,	/* 1 */
	BUCK_MODE_SYNC,		/* 2 */
	BUCK_MODE_AUTO		/* 3 */
पूर्ण;

/* Regulator operations */

/*
 * Current limits array (in uA) क्रम BCORE1, BCORE2, BPRO.
 * Entry indexes corresponds to रेजिस्टर values.
 */
अटल स्थिर अचिन्हित पूर्णांक da9063_buck_a_limits[] = अणु
	 500000,  600000,  700000,  800000,  900000, 1000000, 1100000, 1200000,
	1300000, 1400000, 1500000, 1600000, 1700000, 1800000, 1900000, 2000000
पूर्ण;

/*
 * Current limits array (in uA) क्रम BMEM, BIO, BPERI.
 * Entry indexes corresponds to रेजिस्टर values.
 */
अटल स्थिर अचिन्हित पूर्णांक da9063_buck_b_limits[] = अणु
	1500000, 1600000, 1700000, 1800000, 1900000, 2000000, 2100000, 2200000,
	2300000, 2400000, 2500000, 2600000, 2700000, 2800000, 2900000, 3000000
पूर्ण;

/*
 * Current limits array (in uA) क्रम merged BCORE1 and BCORE2.
 * Entry indexes corresponds to रेजिस्टर values.
 */
अटल स्थिर अचिन्हित पूर्णांक da9063_bcores_merged_limits[] = अणु
	1000000, 1200000, 1400000, 1600000, 1800000, 2000000, 2200000, 2400000,
	2600000, 2800000, 3000000, 3200000, 3400000, 3600000, 3800000, 4000000
पूर्ण;

/*
 * Current limits array (in uA) क्रम merged BMEM and BIO.
 * Entry indexes corresponds to रेजिस्टर values.
 */
अटल स्थिर अचिन्हित पूर्णांक da9063_bmem_bio_merged_limits[] = अणु
	3000000, 3200000, 3400000, 3600000, 3800000, 4000000, 4200000, 4400000,
	4600000, 4800000, 5000000, 5200000, 5400000, 5600000, 5800000, 6000000
पूर्ण;

अटल पूर्णांक da9063_buck_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा da9063_regulator *regl = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = BUCK_MODE_SYNC;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = BUCK_MODE_AUTO;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = BUCK_MODE_SLEEP;
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

अटल अचिन्हित पूर्णांक da9063_buck_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9063_regulator *regl = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(regl->mode, &val);
	अगर (ret < 0)
		वापस ret;

	चयन (val) अणु
	शेष:
	हाल BUCK_MODE_MANUAL:
		/* Sleep flag bit decides the mode */
		अवरोध;
	हाल BUCK_MODE_SLEEP:
		वापस REGULATOR_MODE_STANDBY;
	हाल BUCK_MODE_SYNC:
		वापस REGULATOR_MODE_FAST;
	हाल BUCK_MODE_AUTO:
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

अटल पूर्णांक da9063_lकरो_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा da9063_regulator *regl = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक val;

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

अटल अचिन्हित पूर्णांक da9063_lकरो_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9063_regulator *regl = rdev_get_drvdata(rdev);
	पूर्णांक ret, val;

	ret = regmap_field_पढ़ो(regl->sleep, &val);
	अगर (ret < 0)
		वापस 0;

	अगर (val)
		वापस REGULATOR_MODE_STANDBY;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक da9063_buck_get_status(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret = regulator_is_enabled_regmap(rdev);

	अगर (ret == 0) अणु
		ret = REGULATOR_STATUS_OFF;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		ret = da9063_buck_get_mode(rdev);
		अगर (ret > 0)
			ret = regulator_mode_to_status(ret);
		अन्यथा अगर (ret == 0)
			ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da9063_lकरो_get_status(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret = regulator_is_enabled_regmap(rdev);

	अगर (ret == 0) अणु
		ret = REGULATOR_STATUS_OFF;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		ret = da9063_lकरो_get_mode(rdev);
		अगर (ret > 0)
			ret = regulator_mode_to_status(ret);
		अन्यथा अगर (ret == 0)
			ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da9063_set_suspend_voltage(काष्ठा regulator_dev *rdev, पूर्णांक uV)
अणु
	काष्ठा da9063_regulator *regl = rdev_get_drvdata(rdev);
	स्थिर काष्ठा da9063_regulator_info *rinfo = regl->info;
	पूर्णांक ret, sel;

	sel = regulator_map_voltage_linear(rdev, uV, uV);
	अगर (sel < 0)
		वापस sel;

	sel <<= ffs(rdev->desc->vsel_mask) - 1;

	ret = regmap_update_bits(regl->hw->regmap, rinfo->suspend_vsel_reg,
				 rdev->desc->vsel_mask, sel);

	वापस ret;
पूर्ण

अटल पूर्णांक da9063_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9063_regulator *regl = rdev_get_drvdata(rdev);

	वापस regmap_field_ग_लिखो(regl->suspend, 1);
पूर्ण

अटल पूर्णांक da9063_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9063_regulator *regl = rdev_get_drvdata(rdev);

	वापस regmap_field_ग_लिखो(regl->suspend, 0);
पूर्ण

अटल पूर्णांक da9063_buck_set_suspend_mode(काष्ठा regulator_dev *rdev,
				अचिन्हित पूर्णांक mode)
अणु
	काष्ठा da9063_regulator *regl = rdev_get_drvdata(rdev);
	पूर्णांक val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = BUCK_MODE_SYNC;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = BUCK_MODE_AUTO;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = BUCK_MODE_SLEEP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_field_ग_लिखो(regl->mode, val);
पूर्ण

अटल पूर्णांक da9063_lकरो_set_suspend_mode(काष्ठा regulator_dev *rdev,
				अचिन्हित पूर्णांक mode)
अणु
	काष्ठा da9063_regulator *regl = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक val;

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

अटल स्थिर काष्ठा regulator_ops da9063_buck_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.set_current_limit	= regulator_set_current_limit_regmap,
	.get_current_limit	= regulator_get_current_limit_regmap,
	.set_mode		= da9063_buck_set_mode,
	.get_mode		= da9063_buck_get_mode,
	.get_status		= da9063_buck_get_status,
	.set_suspend_voltage	= da9063_set_suspend_voltage,
	.set_suspend_enable	= da9063_suspend_enable,
	.set_suspend_disable	= da9063_suspend_disable,
	.set_suspend_mode	= da9063_buck_set_suspend_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops da9063_lकरो_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.set_mode		= da9063_lकरो_set_mode,
	.get_mode		= da9063_lकरो_get_mode,
	.get_status		= da9063_lकरो_get_status,
	.set_suspend_voltage	= da9063_set_suspend_voltage,
	.set_suspend_enable	= da9063_suspend_enable,
	.set_suspend_disable	= da9063_suspend_disable,
	.set_suspend_mode	= da9063_lकरो_set_suspend_mode,
पूर्ण;

/* Info of regulators क्रम DA9063 */
अटल स्थिर काष्ठा da9063_regulator_info da9063_regulator_info[] = अणु
	अणु
		DA9063_BUCK(DA9063, BCORE1, 300, 10, 1570,
			    da9063_buck_a_limits,
			    DA9063_REG_BUCK_ILIM_C, DA9063_BCORE1_ILIM_MASK),
		DA9063_BUCK_COMMON_FIELDS(BCORE1),
	पूर्ण,
	अणु
		DA9063_BUCK(DA9063, BCORE2, 300, 10, 1570,
			    da9063_buck_a_limits,
			    DA9063_REG_BUCK_ILIM_C, DA9063_BCORE2_ILIM_MASK),
		DA9063_BUCK_COMMON_FIELDS(BCORE2),
	पूर्ण,
	अणु
		DA9063_BUCK(DA9063, BPRO, 530, 10, 1800,
			    da9063_buck_a_limits,
			    DA9063_REG_BUCK_ILIM_B, DA9063_BPRO_ILIM_MASK),
		DA9063_BUCK_COMMON_FIELDS(BPRO),
	पूर्ण,
	अणु
		DA9063_BUCK(DA9063, BMEM, 800, 20, 3340,
			    da9063_buck_b_limits,
			    DA9063_REG_BUCK_ILIM_A, DA9063_BMEM_ILIM_MASK),
		DA9063_BUCK_COMMON_FIELDS(BMEM),
	पूर्ण,
	अणु
		DA9063_BUCK(DA9063, BIO, 800, 20, 3340,
			    da9063_buck_b_limits,
			    DA9063_REG_BUCK_ILIM_A, DA9063_BIO_ILIM_MASK),
		DA9063_BUCK_COMMON_FIELDS(BIO),
	पूर्ण,
	अणु
		DA9063_BUCK(DA9063, BPERI, 800, 20, 3340,
			    da9063_buck_b_limits,
			    DA9063_REG_BUCK_ILIM_B, DA9063_BPERI_ILIM_MASK),
		DA9063_BUCK_COMMON_FIELDS(BPERI),
	पूर्ण,
	अणु
		DA9063_BUCK(DA9063, BCORES_MERGED, 300, 10, 1570,
			    da9063_bcores_merged_limits,
			    DA9063_REG_BUCK_ILIM_C, DA9063_BCORE1_ILIM_MASK),
		/* BCORES_MERGED uses the same रेजिस्टर fields as BCORE1 */
		DA9063_BUCK_COMMON_FIELDS(BCORE1),
	पूर्ण,
	अणु
		DA9063_BUCK(DA9063, BMEM_BIO_MERGED, 800, 20, 3340,
			    da9063_bmem_bio_merged_limits,
			    DA9063_REG_BUCK_ILIM_A, DA9063_BMEM_ILIM_MASK),
		/* BMEM_BIO_MERGED uses the same रेजिस्टर fields as BMEM */
		DA9063_BUCK_COMMON_FIELDS(BMEM),
	पूर्ण,
	अणु
		DA9063_LDO(DA9063, LDO3, 900, 20, 3440),
		.oc_event = BFIELD(DA9063_REG_STATUS_D, DA9063_LDO3_LIM),
	पूर्ण,
	अणु
		DA9063_LDO(DA9063, LDO7, 900, 50, 3600),
		.oc_event = BFIELD(DA9063_REG_STATUS_D, DA9063_LDO7_LIM),
	पूर्ण,
	अणु
		DA9063_LDO(DA9063, LDO8, 900, 50, 3600),
		.oc_event = BFIELD(DA9063_REG_STATUS_D, DA9063_LDO8_LIM),
	पूर्ण,
	अणु
		DA9063_LDO(DA9063, LDO9, 950, 50, 3600),
	पूर्ण,
	अणु
		DA9063_LDO(DA9063, LDO11, 900, 50, 3600),
		.oc_event = BFIELD(DA9063_REG_STATUS_D, DA9063_LDO11_LIM),
	पूर्ण,

	/* The following LDOs are present only on DA9063, not on DA9063L */
	अणु
		DA9063_LDO(DA9063, LDO1, 600, 20, 1860),
	पूर्ण,
	अणु
		DA9063_LDO(DA9063, LDO2, 600, 20, 1860),
	पूर्ण,
	अणु
		DA9063_LDO(DA9063, LDO4, 900, 20, 3440),
		.oc_event = BFIELD(DA9063_REG_STATUS_D, DA9063_LDO4_LIM),
	पूर्ण,
	अणु
		DA9063_LDO(DA9063, LDO5, 900, 50, 3600),
	पूर्ण,
	अणु
		DA9063_LDO(DA9063, LDO6, 900, 50, 3600),
	पूर्ण,

	अणु
		DA9063_LDO(DA9063, LDO10, 900, 50, 3600),
	पूर्ण,
पूर्ण;

/* Link chip model with regulators info table */
अटल काष्ठा da9063_dev_model regulators_models[] = अणु
	अणु
		.regulator_info = da9063_regulator_info,
		.n_regulators = ARRAY_SIZE(da9063_regulator_info),
		.type = PMIC_TYPE_DA9063,
	पूर्ण,
	अणु
		.regulator_info = da9063_regulator_info,
		.n_regulators = ARRAY_SIZE(da9063_regulator_info) - 6,
		.type = PMIC_TYPE_DA9063L,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* Regulator पूर्णांकerrupt handlers */
अटल irqवापस_t da9063_lकरो_lim_event(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9063_regulators *regulators = data;
	काष्ठा da9063 *hw = regulators->regulator[0].hw;
	काष्ठा da9063_regulator *regl;
	पूर्णांक bits, i, ret;

	ret = regmap_पढ़ो(hw->regmap, DA9063_REG_STATUS_D, &bits);
	अगर (ret < 0)
		वापस IRQ_NONE;

	क्रम (i = regulators->n_regulators - 1; i >= 0; i--) अणु
		regl = &regulators->regulator[i];
		अगर (regl->info->oc_event.reg != DA9063_REG_STATUS_D)
			जारी;

		अगर (BIT(regl->info->oc_event.lsb) & bits) अणु
			regulator_notअगरier_call_chain(regl->rdev,
					REGULATOR_EVENT_OVER_CURRENT, शून्य);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Probing and Initialisation functions
 */
अटल स्थिर काष्ठा regulator_init_data *da9063_get_regulator_initdata(
		स्थिर काष्ठा da9063_regulators_pdata *regl_pdata, पूर्णांक id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < regl_pdata->n_regulators; i++) अणु
		अगर (id == regl_pdata->regulator_data[i].id)
			वापस regl_pdata->regulator_data[i].initdata;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा of_regulator_match da9063_matches[] = अणु
	[DA9063_ID_BCORE1]           = अणु .name = "bcore1"           पूर्ण,
	[DA9063_ID_BCORE2]           = अणु .name = "bcore2"           पूर्ण,
	[DA9063_ID_BPRO]             = अणु .name = "bpro",            पूर्ण,
	[DA9063_ID_BMEM]             = अणु .name = "bmem",            पूर्ण,
	[DA9063_ID_BIO]              = अणु .name = "bio",             पूर्ण,
	[DA9063_ID_BPERI]            = अणु .name = "bperi",           पूर्ण,
	[DA9063_ID_BCORES_MERGED]    = अणु .name = "bcores-merged"    पूर्ण,
	[DA9063_ID_BMEM_BIO_MERGED]  = अणु .name = "bmem-bio-merged", पूर्ण,
	[DA9063_ID_LDO3]             = अणु .name = "ldo3",            पूर्ण,
	[DA9063_ID_LDO7]             = अणु .name = "ldo7",            पूर्ण,
	[DA9063_ID_LDO8]             = अणु .name = "ldo8",            पूर्ण,
	[DA9063_ID_LDO9]             = अणु .name = "ldo9",            पूर्ण,
	[DA9063_ID_LDO11]            = अणु .name = "ldo11",           पूर्ण,
	/* The following LDOs are present only on DA9063, not on DA9063L */
	[DA9063_ID_LDO1]             = अणु .name = "ldo1",            पूर्ण,
	[DA9063_ID_LDO2]             = अणु .name = "ldo2",            पूर्ण,
	[DA9063_ID_LDO4]             = अणु .name = "ldo4",            पूर्ण,
	[DA9063_ID_LDO5]             = अणु .name = "ldo5",            पूर्ण,
	[DA9063_ID_LDO6]             = अणु .name = "ldo6",            पूर्ण,
	[DA9063_ID_LDO10]            = अणु .name = "ldo10",           पूर्ण,
पूर्ण;

अटल काष्ठा da9063_regulators_pdata *da9063_parse_regulators_dt(
		काष्ठा platक्रमm_device *pdev,
		काष्ठा of_regulator_match **da9063_reg_matches)
अणु
	काष्ठा da9063 *da9063 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा da9063_regulators_pdata *pdata;
	काष्ठा da9063_regulator_data *rdata;
	काष्ठा device_node *node;
	पूर्णांक da9063_matches_len = ARRAY_SIZE(da9063_matches);
	पूर्णांक i, n, num;

	अगर (da9063->type == PMIC_TYPE_DA9063L)
		da9063_matches_len -= 6;

	node = of_get_child_by_name(pdev->dev.parent->of_node, "regulators");
	अगर (!node) अणु
		dev_err(&pdev->dev, "Regulators device node not found\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	num = of_regulator_match(&pdev->dev, node, da9063_matches,
				 da9063_matches_len);
	of_node_put(node);
	अगर (num < 0) अणु
		dev_err(&pdev->dev, "Failed to match regulators\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	pdata->regulator_data = devm_kसुस्मृति(&pdev->dev,
					num, माप(*pdata->regulator_data),
					GFP_KERNEL);
	अगर (!pdata->regulator_data)
		वापस ERR_PTR(-ENOMEM);
	pdata->n_regulators = num;

	n = 0;
	क्रम (i = 0; i < da9063_matches_len; i++) अणु
		अगर (!da9063_matches[i].init_data)
			जारी;

		rdata = &pdata->regulator_data[n];
		rdata->id = i;
		rdata->initdata = da9063_matches[i].init_data;

		n++;
	पूर्ण

	*da9063_reg_matches = da9063_matches;
	वापस pdata;
पूर्ण

अटल पूर्णांक da9063_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9063 *da9063 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा of_regulator_match *da9063_reg_matches = शून्य;
	काष्ठा da9063_regulators_pdata *regl_pdata;
	स्थिर काष्ठा da9063_dev_model *model;
	काष्ठा da9063_regulators *regulators;
	काष्ठा da9063_regulator *regl;
	काष्ठा regulator_config config;
	bool bcores_merged, bmem_bio_merged;
	पूर्णांक id, irq, n, n_regulators, ret, val;

	regl_pdata = da9063_parse_regulators_dt(pdev, &da9063_reg_matches);

	अगर (IS_ERR(regl_pdata) || regl_pdata->n_regulators == 0) अणु
		dev_err(&pdev->dev,
			"No regulators defined for the platform\n");
		वापस -ENODEV;
	पूर्ण

	/* Find regulators set क्रम particular device model */
	क्रम (model = regulators_models; model->regulator_info; model++) अणु
		अगर (model->type == da9063->type)
			अवरोध;
	पूर्ण
	अगर (!model->regulator_info) अणु
		dev_err(&pdev->dev, "Chip model not recognised (%u)\n",
			da9063->type);
		वापस -ENODEV;
	पूर्ण

	ret = regmap_पढ़ो(da9063->regmap, DA9063_REG_CONFIG_H, &val);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Error while reading BUCKs configuration\n");
		वापस ret;
	पूर्ण
	bcores_merged = val & DA9063_BCORE_MERGE;
	bmem_bio_merged = val & DA9063_BUCK_MERGE;

	n_regulators = model->n_regulators;
	अगर (bcores_merged)
		n_regulators -= 2; /* हटाओ BCORE1, BCORE2 */
	अन्यथा
		n_regulators--;    /* हटाओ BCORES_MERGED */
	अगर (bmem_bio_merged)
		n_regulators -= 2; /* हटाओ BMEM, BIO */
	अन्यथा
		n_regulators--;    /* हटाओ BMEM_BIO_MERGED */

	/* Allocate memory required by usable regulators */
	regulators = devm_kzalloc(&pdev->dev, काष्ठा_size(regulators,
				  regulator, n_regulators), GFP_KERNEL);
	अगर (!regulators)
		वापस -ENOMEM;

	regulators->n_regulators = n_regulators;
	platक्रमm_set_drvdata(pdev, regulators);

	/* Register all regulators declared in platक्रमm inक्रमmation */
	n = 0;
	id = 0;
	जबतक (n < regulators->n_regulators) अणु
		/* Skip regulator IDs depending on merge mode configuration */
		चयन (id) अणु
		हाल DA9063_ID_BCORE1:
		हाल DA9063_ID_BCORE2:
			अगर (bcores_merged) अणु
				id++;
				जारी;
			पूर्ण
			अवरोध;
		हाल DA9063_ID_BMEM:
		हाल DA9063_ID_BIO:
			अगर (bmem_bio_merged) अणु
				id++;
				जारी;
			पूर्ण
			अवरोध;
		हाल DA9063_ID_BCORES_MERGED:
			अगर (!bcores_merged) अणु
				id++;
				जारी;
			पूर्ण
			अवरोध;
		हाल DA9063_ID_BMEM_BIO_MERGED:
			अगर (!bmem_bio_merged) अणु
				id++;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		/* Initialise regulator काष्ठाure */
		regl = &regulators->regulator[n];
		regl->hw = da9063;
		regl->info = &model->regulator_info[id];
		regl->desc = regl->info->desc;
		regl->desc.type = REGULATOR_VOLTAGE;
		regl->desc.owner = THIS_MODULE;

		अगर (regl->info->mode.reg) अणु
			regl->mode = devm_regmap_field_alloc(&pdev->dev,
					da9063->regmap, regl->info->mode);
			अगर (IS_ERR(regl->mode))
				वापस PTR_ERR(regl->mode);
		पूर्ण

		अगर (regl->info->suspend.reg) अणु
			regl->suspend = devm_regmap_field_alloc(&pdev->dev,
					da9063->regmap, regl->info->suspend);
			अगर (IS_ERR(regl->suspend))
				वापस PTR_ERR(regl->suspend);
		पूर्ण

		अगर (regl->info->sleep.reg) अणु
			regl->sleep = devm_regmap_field_alloc(&pdev->dev,
					da9063->regmap, regl->info->sleep);
			अगर (IS_ERR(regl->sleep))
				वापस PTR_ERR(regl->sleep);
		पूर्ण

		अगर (regl->info->suspend_sleep.reg) अणु
			regl->suspend_sleep = devm_regmap_field_alloc(&pdev->dev,
				da9063->regmap, regl->info->suspend_sleep);
			अगर (IS_ERR(regl->suspend_sleep))
				वापस PTR_ERR(regl->suspend_sleep);
		पूर्ण

		/* Register regulator */
		स_रखो(&config, 0, माप(config));
		config.dev = &pdev->dev;
		config.init_data = da9063_get_regulator_initdata(regl_pdata, id);
		config.driver_data = regl;
		अगर (da9063_reg_matches)
			config.of_node = da9063_reg_matches[id].of_node;
		config.regmap = da9063->regmap;
		regl->rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regl->desc,
						     &config);
		अगर (IS_ERR(regl->rdev)) अणु
			dev_err(&pdev->dev,
				"Failed to register %s regulator\n",
				regl->desc.name);
			वापस PTR_ERR(regl->rdev);
		पूर्ण
		id++;
		n++;
	पूर्ण

	/* LDOs overcurrent event support */
	irq = platक्रमm_get_irq_byname(pdev, "LDO_LIM");
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
				शून्य, da9063_lकरो_lim_event,
				IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				"LDO_LIM", regulators);
	अगर (ret)
		dev_err(&pdev->dev, "Failed to request LDO_LIM IRQ.\n");

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver da9063_regulator_driver = अणु
	.driver = अणु
		.name = DA9063_DRVNAME_REGULATORS,
	पूर्ण,
	.probe = da9063_regulator_probe,
पूर्ण;

अटल पूर्णांक __init da9063_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&da9063_regulator_driver);
पूर्ण
subsys_initcall(da9063_regulator_init);

अटल व्योम __निकास da9063_regulator_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&da9063_regulator_driver);
पूर्ण
module_निकास(da9063_regulator_cleanup);


/* Module inक्रमmation */
MODULE_AUTHOR("Krystian Garbaciak <krystian.garbaciak@diasemi.com>");
MODULE_DESCRIPTION("DA9063 regulators driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DA9063_DRVNAME_REGULATORS);
