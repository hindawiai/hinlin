<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulator driver क्रम the Richtek RT5033
 *
 * Copyright (C) 2014 Samsung Electronics, Co., Ltd.
 * Author: Beomho Seo <beomho.seo@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/mfd/rt5033.h>
#समावेश <linux/mfd/rt5033-निजी.h>
#समावेश <linux/regulator/of_regulator.h>

अटल स्थिर काष्ठा regulator_ops rt5033_safe_lकरो_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.list_voltage		= regulator_list_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rt5033_buck_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc rt5033_supported_regulators[] = अणु
	[RT5033_BUCK] = अणु
		.name		= "BUCK",
		.of_match	= of_match_ptr("BUCK"),
		.regulators_node = of_match_ptr("regulators"),
		.id		= RT5033_BUCK,
		.ops		= &rt5033_buck_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
		.n_voltages	= RT5033_REGULATOR_BUCK_VOLTAGE_STEP_NUM,
		.min_uV		= RT5033_REGULATOR_BUCK_VOLTAGE_MIN,
		.uV_step	= RT5033_REGULATOR_BUCK_VOLTAGE_STEP,
		.enable_reg	= RT5033_REG_CTRL,
		.enable_mask	= RT5033_CTRL_EN_BUCK_MASK,
		.vsel_reg	= RT5033_REG_BUCK_CTRL,
		.vsel_mask	= RT5033_BUCK_CTRL_MASK,
	पूर्ण,
	[RT5033_LDO] = अणु
		.name		= "LDO",
		.of_match	= of_match_ptr("LDO"),
		.regulators_node = of_match_ptr("regulators"),
		.id		= RT5033_LDO,
		.ops		= &rt5033_buck_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
		.n_voltages	= RT5033_REGULATOR_LDO_VOLTAGE_STEP_NUM,
		.min_uV		= RT5033_REGULATOR_LDO_VOLTAGE_MIN,
		.uV_step	= RT5033_REGULATOR_LDO_VOLTAGE_STEP,
		.enable_reg	= RT5033_REG_CTRL,
		.enable_mask	= RT5033_CTRL_EN_LDO_MASK,
		.vsel_reg	= RT5033_REG_LDO_CTRL,
		.vsel_mask	= RT5033_LDO_CTRL_MASK,
	पूर्ण,
	[RT5033_SAFE_LDO] = अणु
		.name		= "SAFE_LDO",
		.of_match	= of_match_ptr("SAFE_LDO"),
		.regulators_node = of_match_ptr("regulators"),
		.id		= RT5033_SAFE_LDO,
		.ops		= &rt5033_safe_lकरो_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
		.n_voltages	= 1,
		.min_uV		= RT5033_REGULATOR_SAFE_LDO_VOLTAGE,
		.enable_reg	= RT5033_REG_CTRL,
		.enable_mask	= RT5033_CTRL_EN_SAFE_LDO_MASK,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rt5033_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rt5033_dev *rt5033 = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक ret, i;
	काष्ठा regulator_config config = अणुपूर्ण;

	config.dev = rt5033->dev;
	config.driver_data = rt5033;

	क्रम (i = 0; i < ARRAY_SIZE(rt5033_supported_regulators); i++) अणु
		काष्ठा regulator_dev *regulator;

		config.regmap = rt5033->regmap;

		regulator = devm_regulator_रेजिस्टर(&pdev->dev,
				&rt5033_supported_regulators[i], &config);
		अगर (IS_ERR(regulator)) अणु
			ret = PTR_ERR(regulator);
			dev_err(&pdev->dev,
				"Regulator init failed %d: with error: %d\n",
				i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id rt5033_regulator_id[] = अणु
	अणु "rt5033-regulator", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, rt5033_regulator_id);

अटल काष्ठा platक्रमm_driver rt5033_regulator_driver = अणु
	.driver = अणु
		.name = "rt5033-regulator",
	पूर्ण,
	.probe		= rt5033_regulator_probe,
	.id_table	= rt5033_regulator_id,
पूर्ण;
module_platक्रमm_driver(rt5033_regulator_driver);

MODULE_DESCRIPTION("Richtek RT5033 Regulator driver");
MODULE_AUTHOR("Beomho Seo <beomho.seo@samsung.com>");
MODULE_LICENSE("GPL");
