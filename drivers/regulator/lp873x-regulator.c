<शैली गुरु>
/*
 * Regulator driver क्रम LP873X PMIC
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - https://www.ti.com/
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

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/lp873x.h>

#घोषणा LP873X_REGULATOR(_name, _id, _of, _ops, _n, _vr, _vm, _er, _em, \
			 _delay, _lr, _cr)				\
	[_id] = अणु							\
		.desc = अणु						\
			.name			= _name,		\
			.supply_name		= _of "-in",		\
			.id			= _id,			\
			.of_match		= of_match_ptr(_of),	\
			.regulators_node	= of_match_ptr("regulators"),\
			.ops			= &_ops,		\
			.n_voltages		= _n,			\
			.type			= REGULATOR_VOLTAGE,	\
			.owner			= THIS_MODULE,		\
			.vsel_reg		= _vr,			\
			.vsel_mask		= _vm,			\
			.enable_reg		= _er,			\
			.enable_mask		= _em,			\
			.ramp_delay		= _delay,		\
			.linear_ranges		= _lr,			\
			.n_linear_ranges	= ARRAY_SIZE(_lr),	\
			.curr_table	= lp873x_buck_uA,		\
			.n_current_limits = ARRAY_SIZE(lp873x_buck_uA),	\
			.csel_reg	= (_cr),			\
			.csel_mask	= LP873X_BUCK0_CTRL_2_BUCK0_ILIM,\
		पूर्ण,							\
		.ctrl2_reg = _cr,					\
	पूर्ण

काष्ठा lp873x_regulator अणु
	काष्ठा regulator_desc desc;
	अचिन्हित पूर्णांक ctrl2_reg;
पूर्ण;

अटल स्थिर काष्ठा lp873x_regulator regulators[];

अटल स्थिर काष्ठा linear_range buck0_buck1_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(0, 0x0, 0x13, 0),
	REGULATOR_LINEAR_RANGE(700000, 0x14, 0x17, 10000),
	REGULATOR_LINEAR_RANGE(735000, 0x18, 0x9d, 5000),
	REGULATOR_LINEAR_RANGE(1420000, 0x9e, 0xff, 20000),
पूर्ण;

अटल स्थिर काष्ठा linear_range lकरो0_lकरो1_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(800000, 0x0, 0x19, 100000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lp873x_buck_ramp_delay[] = अणु
	30000, 15000, 10000, 7500, 3800, 1900, 940, 470
पूर्ण;

/* LP873X BUCK current limit */
अटल स्थिर अचिन्हित पूर्णांक lp873x_buck_uA[] = अणु
	1500000, 2000000, 2500000, 3000000, 3500000, 4000000,
पूर्ण;

अटल पूर्णांक lp873x_buck_set_ramp_delay(काष्ठा regulator_dev *rdev,
				      पूर्णांक ramp_delay)
अणु
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा lp873x *lp873 = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	अगर (ramp_delay <= 470)
		reg = 7;
	अन्यथा अगर (ramp_delay <= 940)
		reg = 6;
	अन्यथा अगर (ramp_delay <= 1900)
		reg = 5;
	अन्यथा अगर (ramp_delay <= 3800)
		reg = 4;
	अन्यथा अगर (ramp_delay <= 7500)
		reg = 3;
	अन्यथा अगर (ramp_delay <= 10000)
		reg = 2;
	अन्यथा अगर (ramp_delay <= 15000)
		reg = 1;
	अन्यथा
		reg = 0;

	ret = regmap_update_bits(lp873->regmap, regulators[id].ctrl2_reg,
				 LP873X_BUCK0_CTRL_2_BUCK0_SLEW_RATE,
				 reg << __ffs(LP873X_BUCK0_CTRL_2_BUCK0_SLEW_RATE));
	अगर (ret) अणु
		dev_err(lp873->dev, "SLEW RATE write failed: %d\n", ret);
		वापस ret;
	पूर्ण

	rdev->स्थिरraपूर्णांकs->ramp_delay = lp873x_buck_ramp_delay[reg];

	वापस 0;
पूर्ण

/* Operations permitted on BUCK0, BUCK1 */
अटल स्थिर काष्ठा regulator_ops lp873x_buck01_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_ramp_delay		= lp873x_buck_set_ramp_delay,
	.set_current_limit	= regulator_set_current_limit_regmap,
	.get_current_limit	= regulator_get_current_limit_regmap,
पूर्ण;

/* Operations permitted on LDO0 and LDO1 */
अटल स्थिर काष्ठा regulator_ops lp873x_lकरो01_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
पूर्ण;

अटल स्थिर काष्ठा lp873x_regulator regulators[] = अणु
	LP873X_REGULATOR("BUCK0", LP873X_BUCK_0, "buck0", lp873x_buck01_ops,
			 256, LP873X_REG_BUCK0_VOUT,
			 LP873X_BUCK0_VOUT_BUCK0_VSET, LP873X_REG_BUCK0_CTRL_1,
			 LP873X_BUCK0_CTRL_1_BUCK0_EN, 10000,
			 buck0_buck1_ranges, LP873X_REG_BUCK0_CTRL_2),
	LP873X_REGULATOR("BUCK1", LP873X_BUCK_1, "buck1", lp873x_buck01_ops,
			 256, LP873X_REG_BUCK1_VOUT,
			 LP873X_BUCK1_VOUT_BUCK1_VSET, LP873X_REG_BUCK1_CTRL_1,
			 LP873X_BUCK1_CTRL_1_BUCK1_EN, 10000,
			 buck0_buck1_ranges, LP873X_REG_BUCK1_CTRL_2),
	LP873X_REGULATOR("LDO0", LP873X_LDO_0, "ldo0", lp873x_lकरो01_ops, 26,
			 LP873X_REG_LDO0_VOUT, LP873X_LDO0_VOUT_LDO0_VSET,
			 LP873X_REG_LDO0_CTRL,
			 LP873X_LDO0_CTRL_LDO0_EN, 0, lकरो0_lकरो1_ranges, 0xFF),
	LP873X_REGULATOR("LDO1", LP873X_LDO_1, "ldo1", lp873x_lकरो01_ops, 26,
			 LP873X_REG_LDO1_VOUT, LP873X_LDO1_VOUT_LDO1_VSET,
			 LP873X_REG_LDO1_CTRL,
			 LP873X_LDO1_CTRL_LDO1_EN, 0, lकरो0_lकरो1_ranges, 0xFF),
पूर्ण;

अटल पूर्णांक lp873x_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp873x *lp873 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	platक्रमm_set_drvdata(pdev, lp873);

	config.dev = &pdev->dev;
	config.dev->of_node = lp873->dev->of_node;
	config.driver_data = lp873;
	config.regmap = lp873->regmap;

	क्रम (i = 0; i < ARRAY_SIZE(regulators); i++) अणु
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[i].desc,
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(lp873->dev, "failed to register %s regulator\n",
				pdev->name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id lp873x_regulator_id_table[] = अणु
	अणु "lp873x-regulator", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, lp873x_regulator_id_table);

अटल काष्ठा platक्रमm_driver lp873x_regulator_driver = अणु
	.driver = अणु
		.name = "lp873x-pmic",
	पूर्ण,
	.probe = lp873x_regulator_probe,
	.id_table = lp873x_regulator_id_table,
पूर्ण;
module_platक्रमm_driver(lp873x_regulator_driver);

MODULE_AUTHOR("J Keerthy <j-keerthy@ti.com>");
MODULE_DESCRIPTION("LP873X voltage regulator driver");
MODULE_ALIAS("platform:lp873x-pmic");
MODULE_LICENSE("GPL v2");
