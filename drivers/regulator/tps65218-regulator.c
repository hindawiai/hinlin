<शैली गुरु>
/*
 * tps65218-regulator.c
 *
 * Regulator driver क्रम TPS65218 PMIC
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether expressed or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mfd/tps65218.h>

#घोषणा TPS65218_REGULATOR(_name, _of, _id, _type, _ops, _n, _vr, _vm, _er, \
			   _em, _cr, _cm, _lr, _nlr, _delay, _fuv, _sr, _sm, \
			   _ct, _ncl) \
	अणु							\
		.name			= _name,		\
		.of_match		= _of,			\
		.id			= _id,			\
		.ops			= &_ops,		\
		.n_voltages		= _n,			\
		.type			= _type,	\
		.owner			= THIS_MODULE,		\
		.vsel_reg		= _vr,			\
		.vsel_mask		= _vm,			\
		.csel_reg		= _cr,			\
		.csel_mask		= _cm,			\
		.curr_table		= _ct,			\
		.n_current_limits	= _ncl,			\
		.enable_reg		= _er,			\
		.enable_mask		= _em,			\
		.volt_table		= शून्य,			\
		.linear_ranges		= _lr,			\
		.n_linear_ranges	= _nlr,			\
		.ramp_delay		= _delay,		\
		.fixed_uV		= _fuv,			\
		.bypass_reg	= _sr,				\
		.bypass_mask	= _sm,				\
	पूर्ण							\

अटल स्थिर काष्ठा linear_range dcdc1_dcdc2_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(850000, 0x0, 0x32, 10000),
	REGULATOR_LINEAR_RANGE(1375000, 0x33, 0x3f, 25000),
पूर्ण;

अटल स्थिर काष्ठा linear_range lकरो1_dcdc3_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(900000, 0x0, 0x1a, 25000),
	REGULATOR_LINEAR_RANGE(1600000, 0x1b, 0x3f, 50000),
पूर्ण;

अटल स्थिर काष्ठा linear_range dcdc4_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1175000, 0x0, 0xf, 25000),
	REGULATOR_LINEAR_RANGE(1600000, 0x10, 0x34, 50000),
पूर्ण;

अटल पूर्णांक tps65218_pmic_set_voltage_sel(काष्ठा regulator_dev *dev,
					 अचिन्हित selector)
अणु
	पूर्णांक ret;
	काष्ठा tps65218 *tps = rdev_get_drvdata(dev);
	अचिन्हित पूर्णांक rid = rdev_get_id(dev);

	/* Set the voltage based on vsel value and ग_लिखो protect level is 2 */
	ret = tps65218_set_bits(tps, dev->desc->vsel_reg, dev->desc->vsel_mask,
				selector, TPS65218_PROTECT_L1);

	/* Set GO bit क्रम DCDC1/2 to initiate voltage transistion */
	चयन (rid) अणु
	हाल TPS65218_DCDC_1:
	हाल TPS65218_DCDC_2:
		ret = tps65218_set_bits(tps, TPS65218_REG_CONTRL_SLEW_RATE,
					TPS65218_SLEW_RATE_GO,
					TPS65218_SLEW_RATE_GO,
					TPS65218_PROTECT_L1);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tps65218_pmic_enable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps65218 *tps = rdev_get_drvdata(dev);
	पूर्णांक rid = rdev_get_id(dev);

	अगर (rid < TPS65218_DCDC_1 || rid > TPS65218_LDO_1)
		वापस -EINVAL;

	/* Enable the regulator and password protection is level 1 */
	वापस tps65218_set_bits(tps, dev->desc->enable_reg,
				 dev->desc->enable_mask, dev->desc->enable_mask,
				 TPS65218_PROTECT_L1);
पूर्ण

अटल पूर्णांक tps65218_pmic_disable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps65218 *tps = rdev_get_drvdata(dev);
	पूर्णांक rid = rdev_get_id(dev);

	अगर (rid < TPS65218_DCDC_1 || rid > TPS65218_LDO_1)
		वापस -EINVAL;

	/* Disable the regulator and password protection is level 1 */
	वापस tps65218_clear_bits(tps, dev->desc->enable_reg,
				   dev->desc->enable_mask, TPS65218_PROTECT_L1);
पूर्ण

अटल पूर्णांक tps65218_pmic_set_suspend_enable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps65218 *tps = rdev_get_drvdata(dev);
	अचिन्हित पूर्णांक rid = rdev_get_id(dev);

	अगर (rid > TPS65218_LDO_1)
		वापस -EINVAL;

	वापस tps65218_clear_bits(tps, dev->desc->bypass_reg,
				   dev->desc->bypass_mask,
				   TPS65218_PROTECT_L1);
पूर्ण

अटल पूर्णांक tps65218_pmic_set_suspend_disable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps65218 *tps = rdev_get_drvdata(dev);
	अचिन्हित पूर्णांक rid = rdev_get_id(dev);

	अगर (rid > TPS65218_LDO_1)
		वापस -EINVAL;

	/*
	 * Certain revisions of TPS65218 will need to have DCDC3 regulator
	 * enabled always, otherwise an immediate प्रणाली reboot will occur
	 * during घातeroff.
	 */
	अगर (rid == TPS65218_DCDC_3 && tps->rev == TPS65218_REV_2_1)
		वापस 0;

	अगर (!tps->strobes[rid]) अणु
		अगर (rid == TPS65218_DCDC_3)
			tps->strobes[rid] = 3;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	वापस tps65218_set_bits(tps, dev->desc->bypass_reg,
				 dev->desc->bypass_mask,
				 tps->strobes[rid], TPS65218_PROTECT_L1);
पूर्ण

/* Operations permitted on DCDC1, DCDC2 */
अटल स्थिर काष्ठा regulator_ops tps65218_dcdc12_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= tps65218_pmic_enable,
	.disable		= tps65218_pmic_disable,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= tps65218_pmic_set_voltage_sel,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_suspend_enable	= tps65218_pmic_set_suspend_enable,
	.set_suspend_disable	= tps65218_pmic_set_suspend_disable,
पूर्ण;

/* Operations permitted on DCDC3, DCDC4 and LDO1 */
अटल स्थिर काष्ठा regulator_ops tps65218_lकरो1_dcdc34_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= tps65218_pmic_enable,
	.disable		= tps65218_pmic_disable,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= tps65218_pmic_set_voltage_sel,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.set_suspend_enable	= tps65218_pmic_set_suspend_enable,
	.set_suspend_disable	= tps65218_pmic_set_suspend_disable,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ls3_currents[] = अणु 100000, 200000, 500000, 1000000 पूर्ण;

अटल पूर्णांक tps65218_pmic_set_input_current_lim(काष्ठा regulator_dev *dev,
					       पूर्णांक lim_uA)
अणु
	अचिन्हित पूर्णांक index = 0;
	अचिन्हित पूर्णांक num_currents = ARRAY_SIZE(ls3_currents);
	काष्ठा tps65218 *tps = rdev_get_drvdata(dev);

	जबतक (index < num_currents && ls3_currents[index] != lim_uA)
		index++;

	अगर (index == num_currents)
		वापस -EINVAL;

	वापस tps65218_set_bits(tps, dev->desc->csel_reg, dev->desc->csel_mask,
				 index << __builtin_ctz(dev->desc->csel_mask),
				 TPS65218_PROTECT_L1);
पूर्ण

अटल पूर्णांक tps65218_pmic_set_current_limit(काष्ठा regulator_dev *dev,
					   पूर्णांक min_uA, पूर्णांक max_uA)
अणु
	पूर्णांक index = 0;
	अचिन्हित पूर्णांक num_currents = ARRAY_SIZE(ls3_currents);
	काष्ठा tps65218 *tps = rdev_get_drvdata(dev);

	जबतक (index < num_currents && ls3_currents[index] <= max_uA)
		index++;

	index--;

	अगर (index < 0 || ls3_currents[index] < min_uA)
		वापस -EINVAL;

	वापस tps65218_set_bits(tps, dev->desc->csel_reg, dev->desc->csel_mask,
				 index << __builtin_ctz(dev->desc->csel_mask),
				 TPS65218_PROTECT_L1);
पूर्ण

अटल स्थिर काष्ठा regulator_ops tps65218_ls23_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= tps65218_pmic_enable,
	.disable		= tps65218_pmic_disable,
	.set_input_current_limit = tps65218_pmic_set_input_current_lim,
	.set_current_limit	= tps65218_pmic_set_current_limit,
	.get_current_limit	= regulator_get_current_limit_regmap,
पूर्ण;

/* Operations permitted on DCDC5, DCDC6 */
अटल स्थिर काष्ठा regulator_ops tps65218_dcdc56_pmic_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= tps65218_pmic_enable,
	.disable		= tps65218_pmic_disable,
	.set_suspend_enable	= tps65218_pmic_set_suspend_enable,
	.set_suspend_disable	= tps65218_pmic_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc regulators[] = अणु
	TPS65218_REGULATOR("DCDC1", "regulator-dcdc1", TPS65218_DCDC_1,
			   REGULATOR_VOLTAGE, tps65218_dcdc12_ops, 64,
			   TPS65218_REG_CONTROL_DCDC1,
			   TPS65218_CONTROL_DCDC1_MASK, TPS65218_REG_ENABLE1,
			   TPS65218_ENABLE1_DC1_EN, 0, 0, dcdc1_dcdc2_ranges,
			   2, 4000, 0, TPS65218_REG_SEQ3,
			   TPS65218_SEQ3_DC1_SEQ_MASK, शून्य, 0),
	TPS65218_REGULATOR("DCDC2", "regulator-dcdc2", TPS65218_DCDC_2,
			   REGULATOR_VOLTAGE, tps65218_dcdc12_ops, 64,
			   TPS65218_REG_CONTROL_DCDC2,
			   TPS65218_CONTROL_DCDC2_MASK, TPS65218_REG_ENABLE1,
			   TPS65218_ENABLE1_DC2_EN, 0, 0, dcdc1_dcdc2_ranges,
			   2, 4000, 0, TPS65218_REG_SEQ3,
			   TPS65218_SEQ3_DC2_SEQ_MASK, शून्य, 0),
	TPS65218_REGULATOR("DCDC3", "regulator-dcdc3", TPS65218_DCDC_3,
			   REGULATOR_VOLTAGE, tps65218_lकरो1_dcdc34_ops, 64,
			   TPS65218_REG_CONTROL_DCDC3,
			   TPS65218_CONTROL_DCDC3_MASK, TPS65218_REG_ENABLE1,
			   TPS65218_ENABLE1_DC3_EN, 0, 0, lकरो1_dcdc3_ranges, 2,
			   0, 0, TPS65218_REG_SEQ4, TPS65218_SEQ4_DC3_SEQ_MASK,
			   शून्य, 0),
	TPS65218_REGULATOR("DCDC4", "regulator-dcdc4", TPS65218_DCDC_4,
			   REGULATOR_VOLTAGE, tps65218_lकरो1_dcdc34_ops, 53,
			   TPS65218_REG_CONTROL_DCDC4,
			   TPS65218_CONTROL_DCDC4_MASK, TPS65218_REG_ENABLE1,
			   TPS65218_ENABLE1_DC4_EN, 0, 0, dcdc4_ranges, 2,
			   0, 0, TPS65218_REG_SEQ4, TPS65218_SEQ4_DC4_SEQ_MASK,
			   शून्य, 0),
	TPS65218_REGULATOR("DCDC5", "regulator-dcdc5", TPS65218_DCDC_5,
			   REGULATOR_VOLTAGE, tps65218_dcdc56_pmic_ops, 1, -1,
			   -1, TPS65218_REG_ENABLE1, TPS65218_ENABLE1_DC5_EN, 0,
			   0, शून्य, 0, 0, 1000000, TPS65218_REG_SEQ5,
			   TPS65218_SEQ5_DC5_SEQ_MASK, शून्य, 0),
	TPS65218_REGULATOR("DCDC6", "regulator-dcdc6", TPS65218_DCDC_6,
			   REGULATOR_VOLTAGE, tps65218_dcdc56_pmic_ops, 1, -1,
			   -1, TPS65218_REG_ENABLE1, TPS65218_ENABLE1_DC6_EN, 0,
			   0, शून्य, 0, 0, 1800000, TPS65218_REG_SEQ5,
			   TPS65218_SEQ5_DC6_SEQ_MASK, शून्य, 0),
	TPS65218_REGULATOR("LDO1", "regulator-ldo1", TPS65218_LDO_1,
			   REGULATOR_VOLTAGE, tps65218_lकरो1_dcdc34_ops, 64,
			   TPS65218_REG_CONTROL_LDO1,
			   TPS65218_CONTROL_LDO1_MASK, TPS65218_REG_ENABLE2,
			   TPS65218_ENABLE2_LDO1_EN, 0, 0, lकरो1_dcdc3_ranges,
			   2, 0, 0, TPS65218_REG_SEQ6,
			   TPS65218_SEQ6_LDO1_SEQ_MASK, शून्य, 0),
	TPS65218_REGULATOR("LS2", "regulator-ls2", TPS65218_LS_2,
			   REGULATOR_CURRENT, tps65218_ls23_ops, 0, 0, 0,
			   TPS65218_REG_ENABLE2, TPS65218_ENABLE2_LS2_EN,
			   TPS65218_REG_CONFIG2, TPS65218_CONFIG2_LS2ILIM_MASK,
			   शून्य, 0, 0, 0, 0, 0, ls3_currents,
			   ARRAY_SIZE(ls3_currents)),
	TPS65218_REGULATOR("LS3", "regulator-ls3", TPS65218_LS_3,
			   REGULATOR_CURRENT, tps65218_ls23_ops, 0, 0, 0,
			   TPS65218_REG_ENABLE2, TPS65218_ENABLE2_LS3_EN,
			   TPS65218_REG_CONFIG2, TPS65218_CONFIG2_LS3ILIM_MASK,
			   शून्य, 0, 0, 0, 0, 0, ls3_currents,
			   ARRAY_SIZE(ls3_currents)),
पूर्ण;

अटल पूर्णांक tps65218_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65218 *tps = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक val;

	config.dev = &pdev->dev;
	config.dev->of_node = tps->dev->of_node;
	config.driver_data = tps;
	config.regmap = tps->regmap;

	/* Allocate memory क्रम strobes */
	tps->strobes = devm_kसुस्मृति(&pdev->dev,
				    TPS65218_NUM_REGULATOR, माप(u8),
				    GFP_KERNEL);
	अगर (!tps->strobes)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(regulators); i++) अणु
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(tps->dev, "failed to register %s regulator\n",
				pdev->name);
			वापस PTR_ERR(rdev);
		पूर्ण

		ret = regmap_पढ़ो(tps->regmap, regulators[i].bypass_reg, &val);
		अगर (ret)
			वापस ret;

		tps->strobes[i] = val & regulators[i].bypass_mask;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id tps65218_regulator_id_table[] = अणु
	अणु "tps65218-regulator", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, tps65218_regulator_id_table);

अटल काष्ठा platक्रमm_driver tps65218_regulator_driver = अणु
	.driver = अणु
		.name = "tps65218-pmic",
	पूर्ण,
	.probe = tps65218_regulator_probe,
	.id_table = tps65218_regulator_id_table,
पूर्ण;

module_platक्रमm_driver(tps65218_regulator_driver);

MODULE_AUTHOR("J Keerthy <j-keerthy@ti.com>");
MODULE_DESCRIPTION("TPS65218 voltage regulator driver");
MODULE_ALIAS("platform:tps65218-pmic");
MODULE_LICENSE("GPL v2");
