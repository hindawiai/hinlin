<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulator driver क्रम LP87565 PMIC
 *
 * Copyright (C) 2017 Texas Instruments Incorporated - https://www.ti.com/
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/lp87565.h>

#घोषणा LP87565_REGULATOR(_name, _id, _of, _ops, _n, _vr, _vm,		\
			  _er, _em, _ev, _delay, _lr, _cr)		\
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
			.enable_val		= _ev,			\
			.ramp_delay		= _delay,		\
			.linear_ranges		= _lr,			\
			.n_linear_ranges	= ARRAY_SIZE(_lr),	\
			.curr_table = lp87565_buck_uA,			\
			.n_current_limits = ARRAY_SIZE(lp87565_buck_uA),\
			.csel_reg = (_cr),				\
			.csel_mask = LP87565_BUCK_CTRL_2_ILIM,		\
		पूर्ण,							\
		.ctrl2_reg = _cr,					\
	पूर्ण

काष्ठा lp87565_regulator अणु
	काष्ठा regulator_desc desc;
	अचिन्हित पूर्णांक ctrl2_reg;
पूर्ण;

अटल स्थिर काष्ठा lp87565_regulator regulators[];

अटल स्थिर काष्ठा linear_range buck0_1_2_3_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0xA, 0x17, 10000),
	REGULATOR_LINEAR_RANGE(735000, 0x18, 0x9d, 5000),
	REGULATOR_LINEAR_RANGE(1420000, 0x9e, 0xff, 20000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lp87565_buck_ramp_delay[] = अणु
	30000, 15000, 10000, 7500, 3800, 1900, 940, 470
पूर्ण;

/* LP87565 BUCK current limit */
अटल स्थिर अचिन्हित पूर्णांक lp87565_buck_uA[] = अणु
	1500000, 2000000, 2500000, 3000000, 3500000, 4000000, 4500000, 5000000,
पूर्ण;

अटल पूर्णांक lp87565_buck_set_ramp_delay(काष्ठा regulator_dev *rdev,
				       पूर्णांक ramp_delay)
अणु
	पूर्णांक id = rdev_get_id(rdev);
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

	ret = regmap_update_bits(rdev->regmap, regulators[id].ctrl2_reg,
				 LP87565_BUCK_CTRL_2_SLEW_RATE,
				 reg << __ffs(LP87565_BUCK_CTRL_2_SLEW_RATE));
	अगर (ret) अणु
		dev_err(&rdev->dev, "SLEW RATE write failed: %d\n", ret);
		वापस ret;
	पूर्ण

	rdev->स्थिरraपूर्णांकs->ramp_delay = lp87565_buck_ramp_delay[reg];

	/* Conservatively give a 15% margin */
	rdev->स्थिरraपूर्णांकs->ramp_delay =
				rdev->स्थिरraपूर्णांकs->ramp_delay * 85 / 100;

	वापस 0;
पूर्ण

/* Operations permitted on BUCKs */
अटल स्थिर काष्ठा regulator_ops lp87565_buck_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_ramp_delay		= lp87565_buck_set_ramp_delay,
	.set_current_limit	= regulator_set_current_limit_regmap,
	.get_current_limit	= regulator_get_current_limit_regmap,
पूर्ण;

अटल स्थिर काष्ठा lp87565_regulator regulators[] = अणु
	LP87565_REGULATOR("BUCK0", LP87565_BUCK_0, "buck0", lp87565_buck_ops,
			  256, LP87565_REG_BUCK0_VOUT, LP87565_BUCK_VSET,
			  LP87565_REG_BUCK0_CTRL_1,
			  LP87565_BUCK_CTRL_1_EN |
			  LP87565_BUCK_CTRL_1_EN_PIN_CTRL,
			  LP87565_BUCK_CTRL_1_EN, 3230,
			  buck0_1_2_3_ranges, LP87565_REG_BUCK0_CTRL_2),
	LP87565_REGULATOR("BUCK1", LP87565_BUCK_1, "buck1", lp87565_buck_ops,
			  256, LP87565_REG_BUCK1_VOUT, LP87565_BUCK_VSET,
			  LP87565_REG_BUCK1_CTRL_1,
			  LP87565_BUCK_CTRL_1_EN |
			  LP87565_BUCK_CTRL_1_EN_PIN_CTRL,
			  LP87565_BUCK_CTRL_1_EN, 3230,
			  buck0_1_2_3_ranges, LP87565_REG_BUCK1_CTRL_2),
	LP87565_REGULATOR("BUCK2", LP87565_BUCK_2, "buck2", lp87565_buck_ops,
			  256, LP87565_REG_BUCK2_VOUT, LP87565_BUCK_VSET,
			  LP87565_REG_BUCK2_CTRL_1,
			  LP87565_BUCK_CTRL_1_EN |
			  LP87565_BUCK_CTRL_1_EN_PIN_CTRL,
			  LP87565_BUCK_CTRL_1_EN, 3230,
			  buck0_1_2_3_ranges, LP87565_REG_BUCK2_CTRL_2),
	LP87565_REGULATOR("BUCK3", LP87565_BUCK_3, "buck3", lp87565_buck_ops,
			  256, LP87565_REG_BUCK3_VOUT, LP87565_BUCK_VSET,
			  LP87565_REG_BUCK3_CTRL_1,
			  LP87565_BUCK_CTRL_1_EN |
			  LP87565_BUCK_CTRL_1_EN_PIN_CTRL,
			  LP87565_BUCK_CTRL_1_EN, 3230,
			  buck0_1_2_3_ranges, LP87565_REG_BUCK3_CTRL_2),
	LP87565_REGULATOR("BUCK10", LP87565_BUCK_10, "buck10", lp87565_buck_ops,
			  256, LP87565_REG_BUCK0_VOUT, LP87565_BUCK_VSET,
			  LP87565_REG_BUCK0_CTRL_1,
			  LP87565_BUCK_CTRL_1_EN |
			  LP87565_BUCK_CTRL_1_EN_PIN_CTRL |
			  LP87565_BUCK_CTRL_1_FPWM_MP_0_2,
			  LP87565_BUCK_CTRL_1_EN |
			  LP87565_BUCK_CTRL_1_FPWM_MP_0_2, 3230,
			  buck0_1_2_3_ranges, LP87565_REG_BUCK0_CTRL_2),
	LP87565_REGULATOR("BUCK23", LP87565_BUCK_23, "buck23", lp87565_buck_ops,
			  256, LP87565_REG_BUCK2_VOUT, LP87565_BUCK_VSET,
			  LP87565_REG_BUCK2_CTRL_1,
			  LP87565_BUCK_CTRL_1_EN |
			  LP87565_BUCK_CTRL_1_EN_PIN_CTRL,
			  LP87565_BUCK_CTRL_1_EN, 3230,
			  buck0_1_2_3_ranges, LP87565_REG_BUCK2_CTRL_2),
	LP87565_REGULATOR("BUCK3210", LP87565_BUCK_3210, "buck3210",
			  lp87565_buck_ops, 256, LP87565_REG_BUCK0_VOUT,
			  LP87565_BUCK_VSET, LP87565_REG_BUCK0_CTRL_1,
			  LP87565_BUCK_CTRL_1_EN |
			  LP87565_BUCK_CTRL_1_EN_PIN_CTRL |
			  LP87565_BUCK_CTRL_1_FPWM_MP_0_2,
			  LP87565_BUCK_CTRL_1_EN |
			  LP87565_BUCK_CTRL_1_FPWM_MP_0_2, 3230,
			  buck0_1_2_3_ranges, LP87565_REG_BUCK0_CTRL_2),
पूर्ण;

अटल पूर्णांक lp87565_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp87565 *lp87565 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i, min_idx, max_idx;

	platक्रमm_set_drvdata(pdev, lp87565);

	config.dev = &pdev->dev;
	config.dev->of_node = lp87565->dev->of_node;
	config.driver_data = lp87565;
	config.regmap = lp87565->regmap;

	चयन (lp87565->dev_type) अणु
	हाल LP87565_DEVICE_TYPE_LP87565_Q1:
		min_idx = LP87565_BUCK_10;
		max_idx = LP87565_BUCK_23;
		अवरोध;
	हाल LP87565_DEVICE_TYPE_LP87561_Q1:
		min_idx = LP87565_BUCK_3210;
		max_idx = LP87565_BUCK_3210;
		अवरोध;
	शेष:
		min_idx = LP87565_BUCK_0;
		max_idx = LP87565_BUCK_3;
		अवरोध;
	पूर्ण

	क्रम (i = min_idx; i <= max_idx; i++) अणु
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[i].desc,
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(lp87565->dev, "failed to register %s regulator\n",
				pdev->name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id lp87565_regulator_id_table[] = अणु
	अणु "lp87565-regulator", पूर्ण,
	अणु "lp87565-q1-regulator", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, lp87565_regulator_id_table);

अटल काष्ठा platक्रमm_driver lp87565_regulator_driver = अणु
	.driver = अणु
		.name = "lp87565-pmic",
	पूर्ण,
	.probe = lp87565_regulator_probe,
	.id_table = lp87565_regulator_id_table,
पूर्ण;
module_platक्रमm_driver(lp87565_regulator_driver);

MODULE_AUTHOR("J Keerthy <j-keerthy@ti.com>");
MODULE_DESCRIPTION("LP87565 voltage regulator driver");
MODULE_LICENSE("GPL v2");
