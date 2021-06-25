<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max14577.c - Regulator driver क्रम the Maxim 14577/77836
//
// Copyright (C) 2013,2014 Samsung Electronics
// Krzysztof Kozlowski <krzk@kernel.org>

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/mfd/max14577.h>
#समावेश <linux/mfd/max14577-निजी.h>
#समावेश <linux/regulator/of_regulator.h>

अटल पूर्णांक max14577_reg_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक rid = rdev_get_id(rdev);
	काष्ठा regmap *rmap = rdev->regmap;
	u8 reg_data;

	चयन (rid) अणु
	हाल MAX14577_CHARGER:
		max14577_पढ़ो_reg(rmap, MAX14577_CHG_REG_CHG_CTRL2, &reg_data);
		अगर ((reg_data & CHGCTRL2_MBCHOSTEN_MASK) == 0)
			वापस 0;
		max14577_पढ़ो_reg(rmap, MAX14577_CHG_REG_STATUS3, &reg_data);
		अगर ((reg_data & STATUS3_CGMBC_MASK) == 0)
			वापस 0;
		/* MBCHOSTEN and CGMBC are on */
		वापस 1;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक max14577_reg_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	u8 reg_data;
	काष्ठा regmap *rmap = rdev->regmap;
	काष्ठा max14577 *max14577 = rdev_get_drvdata(rdev);
	स्थिर काष्ठा maxim_अक्षरger_current *limits =
		&maxim_अक्षरger_currents[max14577->dev_type];

	अगर (rdev_get_id(rdev) != MAX14577_CHARGER)
		वापस -EINVAL;

	max14577_पढ़ो_reg(rmap, MAX14577_CHG_REG_CHG_CTRL4, &reg_data);

	अगर ((reg_data & CHGCTRL4_MBCICHWRCL_MASK) == 0)
		वापस limits->min;

	reg_data = ((reg_data & CHGCTRL4_MBCICHWRCH_MASK) >>
			CHGCTRL4_MBCICHWRCH_SHIFT);
	वापस limits->high_start + reg_data * limits->high_step;
पूर्ण

अटल पूर्णांक max14577_reg_set_current_limit(काष्ठा regulator_dev *rdev,
		पूर्णांक min_uA, पूर्णांक max_uA)
अणु
	u8 reg_data;
	पूर्णांक ret;
	काष्ठा max14577 *max14577 = rdev_get_drvdata(rdev);
	स्थिर काष्ठा maxim_अक्षरger_current *limits =
		&maxim_अक्षरger_currents[max14577->dev_type];

	अगर (rdev_get_id(rdev) != MAX14577_CHARGER)
		वापस -EINVAL;

	ret = maxim_अक्षरger_calc_reg_current(limits, min_uA, max_uA, &reg_data);
	अगर (ret)
		वापस ret;

	वापस max14577_update_reg(rdev->regmap, MAX14577_CHG_REG_CHG_CTRL4,
			CHGCTRL4_MBCICHWRCL_MASK | CHGCTRL4_MBCICHWRCH_MASK,
			reg_data);
पूर्ण

अटल स्थिर काष्ठा regulator_ops max14577_safeout_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.list_voltage		= regulator_list_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max14577_अक्षरger_ops = अणु
	.is_enabled		= max14577_reg_is_enabled,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_current_limit	= max14577_reg_get_current_limit,
	.set_current_limit	= max14577_reg_set_current_limit,
पूर्ण;

#घोषणा MAX14577_SAFEOUT_REG	अणु \
	.name		= "SAFEOUT", \
	.of_match	= of_match_ptr("SAFEOUT"), \
	.regulators_node = of_match_ptr("regulators"), \
	.id		= MAX14577_SAFEOUT, \
	.ops		= &max14577_safeout_ops, \
	.type		= REGULATOR_VOLTAGE, \
	.owner		= THIS_MODULE, \
	.n_voltages	= 1, \
	.min_uV		= MAX14577_REGULATOR_SAFEOUT_VOLTAGE, \
	.enable_reg	= MAX14577_REG_CONTROL2, \
	.enable_mask	= CTRL2_SFOUTORD_MASK, \
पूर्ण
#घोषणा MAX14577_CHARGER_REG	अणु \
	.name		= "CHARGER", \
	.of_match	= of_match_ptr("CHARGER"), \
	.regulators_node = of_match_ptr("regulators"), \
	.id		= MAX14577_CHARGER, \
	.ops		= &max14577_अक्षरger_ops, \
	.type		= REGULATOR_CURRENT, \
	.owner		= THIS_MODULE, \
	.enable_reg	= MAX14577_CHG_REG_CHG_CTRL2, \
	.enable_mask	= CHGCTRL2_MBCHOSTEN_MASK, \
पूर्ण

अटल स्थिर काष्ठा regulator_desc max14577_supported_regulators[] = अणु
	[MAX14577_SAFEOUT] = MAX14577_SAFEOUT_REG,
	[MAX14577_CHARGER] = MAX14577_CHARGER_REG,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max77836_lकरो_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	/* TODO: add .set_suspend_mode */
पूर्ण;

#घोषणा MAX77836_LDO_REG(num)	अणु \
	.name		= "LDO" # num, \
	.of_match	= of_match_ptr("LDO" # num), \
	.regulators_node = of_match_ptr("regulators"), \
	.id		= MAX77836_LDO ## num, \
	.ops		= &max77836_lकरो_ops, \
	.type		= REGULATOR_VOLTAGE, \
	.owner		= THIS_MODULE, \
	.n_voltages	= MAX77836_REGULATOR_LDO_VOLTAGE_STEPS_NUM, \
	.min_uV		= MAX77836_REGULATOR_LDO_VOLTAGE_MIN, \
	.uV_step	= MAX77836_REGULATOR_LDO_VOLTAGE_STEP, \
	.enable_reg	= MAX77836_LDO_REG_CNFG1_LDO ## num, \
	.enable_mask	= MAX77836_CNFG1_LDO_PWRMD_MASK, \
	.vsel_reg	= MAX77836_LDO_REG_CNFG1_LDO ## num, \
	.vsel_mask	= MAX77836_CNFG1_LDO_TV_MASK, \
पूर्ण

अटल स्थिर काष्ठा regulator_desc max77836_supported_regulators[] = अणु
	[MAX14577_SAFEOUT] = MAX14577_SAFEOUT_REG,
	[MAX14577_CHARGER] = MAX14577_CHARGER_REG,
	[MAX77836_LDO1] = MAX77836_LDO_REG(1),
	[MAX77836_LDO2] = MAX77836_LDO_REG(2),
पूर्ण;

/*
 * Registers क्रम regulators of max77836 use dअगरferent I2C slave addresses so
 * dअगरferent regmaps must be used क्रम them.
 *
 * Returns proper regmap क्रम accessing regulator passed by id.
 */
अटल काष्ठा regmap *max14577_get_regmap(काष्ठा max14577 *max14577,
		पूर्णांक reg_id)
अणु
	चयन (max14577->dev_type) अणु
	हाल MAXIM_DEVICE_TYPE_MAX77836:
		चयन (reg_id) अणु
		हाल MAX77836_SAFEOUT ... MAX77836_CHARGER:
			वापस max14577->regmap;
		शेष:
			/* MAX77836_LDO1 ... MAX77836_LDO2 */
			वापस max14577->regmap_pmic;
		पूर्ण

	हाल MAXIM_DEVICE_TYPE_MAX14577:
	शेष:
		वापस max14577->regmap;
	पूर्ण
पूर्ण

अटल पूर्णांक max14577_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max14577 *max14577 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max14577_platक्रमm_data *pdata = dev_get_platdata(max14577->dev);
	पूर्णांक i, ret = 0;
	काष्ठा regulator_config config = अणुपूर्ण;
	स्थिर काष्ठा regulator_desc *supported_regulators;
	अचिन्हित पूर्णांक supported_regulators_size;
	क्रमागत maxim_device_type dev_type = max14577->dev_type;

	चयन (dev_type) अणु
	हाल MAXIM_DEVICE_TYPE_MAX77836:
		supported_regulators = max77836_supported_regulators;
		supported_regulators_size = ARRAY_SIZE(max77836_supported_regulators);
		अवरोध;
	हाल MAXIM_DEVICE_TYPE_MAX14577:
	शेष:
		supported_regulators = max14577_supported_regulators;
		supported_regulators_size = ARRAY_SIZE(max14577_supported_regulators);
	पूर्ण

	config.dev = max14577->dev;
	config.driver_data = max14577;

	क्रम (i = 0; i < supported_regulators_size; i++) अणु
		काष्ठा regulator_dev *regulator;
		/*
		 * Index of supported_regulators[] is also the id and must
		 * match index of pdata->regulators[].
		 */
		अगर (pdata && pdata->regulators) अणु
			config.init_data = pdata->regulators[i].initdata;
			config.of_node = pdata->regulators[i].of_node;
		पूर्ण
		config.regmap = max14577_get_regmap(max14577,
				supported_regulators[i].id);

		regulator = devm_regulator_रेजिस्टर(&pdev->dev,
				&supported_regulators[i], &config);
		अगर (IS_ERR(regulator)) अणु
			ret = PTR_ERR(regulator);
			dev_err(&pdev->dev,
					"Regulator init failed for %d/%s with error: %d\n",
					i, supported_regulators[i].name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max14577_regulator_id[] = अणु
	अणु "max14577-regulator", MAXIM_DEVICE_TYPE_MAX14577, पूर्ण,
	अणु "max77836-regulator", MAXIM_DEVICE_TYPE_MAX77836, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max14577_regulator_id);

अटल काष्ठा platक्रमm_driver max14577_regulator_driver = अणु
	.driver = अणु
		   .name = "max14577-regulator",
		   पूर्ण,
	.probe		= max14577_regulator_probe,
	.id_table	= max14577_regulator_id,
पूर्ण;

अटल पूर्णांक __init max14577_regulator_init(व्योम)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(max14577_supported_regulators) != MAX14577_REGULATOR_NUM);
	BUILD_BUG_ON(ARRAY_SIZE(max77836_supported_regulators) != MAX77836_REGULATOR_NUM);

	BUILD_BUG_ON(MAX77836_REGULATOR_LDO_VOLTAGE_MIN +
			(MAX77836_REGULATOR_LDO_VOLTAGE_STEP *
			  (MAX77836_REGULATOR_LDO_VOLTAGE_STEPS_NUM - 1)) !=
			MAX77836_REGULATOR_LDO_VOLTAGE_MAX);

	वापस platक्रमm_driver_रेजिस्टर(&max14577_regulator_driver);
पूर्ण
subsys_initcall(max14577_regulator_init);

अटल व्योम __निकास max14577_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&max14577_regulator_driver);
पूर्ण
module_निकास(max14577_regulator_निकास);

MODULE_AUTHOR("Krzysztof Kozlowski <krzk@kernel.org>");
MODULE_DESCRIPTION("Maxim 14577/77836 regulator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:max14577-regulator");
MODULE_ALIAS("platform:max77836-regulator");
