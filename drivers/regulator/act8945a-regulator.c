<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Voltage regulation driver क्रम active-semi ACT8945A PMIC
 *
 * Copyright (C) 2015 Aपंचांगel Corporation
 *
 * Author: Wenyou Yang <wenyou.yang@aपंचांगel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <dt-bindings/regulator/active-semi,8945a-regulator.h>

/**
 * ACT8945A Global Register Map.
 */
#घोषणा ACT8945A_SYS_MODE	0x00
#घोषणा ACT8945A_SYS_CTRL	0x01
#घोषणा ACT8945A_SYS_UNLK_REGS	0x0b
#घोषणा ACT8945A_DCDC1_VSET1	0x20
#घोषणा ACT8945A_DCDC1_VSET2	0x21
#घोषणा ACT8945A_DCDC1_CTRL	0x22
#घोषणा ACT8945A_DCDC1_SUS	0x24
#घोषणा ACT8945A_DCDC2_VSET1	0x30
#घोषणा ACT8945A_DCDC2_VSET2	0x31
#घोषणा ACT8945A_DCDC2_CTRL	0x32
#घोषणा ACT8945A_DCDC2_SUS	0x34
#घोषणा ACT8945A_DCDC3_VSET1	0x40
#घोषणा ACT8945A_DCDC3_VSET2	0x41
#घोषणा ACT8945A_DCDC3_CTRL	0x42
#घोषणा ACT8945A_DCDC3_SUS	0x44
#घोषणा ACT8945A_LDO1_VSET	0x50
#घोषणा ACT8945A_LDO1_CTRL	0x51
#घोषणा ACT8945A_LDO1_SUS	0x52
#घोषणा ACT8945A_LDO2_VSET	0x54
#घोषणा ACT8945A_LDO2_CTRL	0x55
#घोषणा ACT8945A_LDO2_SUS	0x56
#घोषणा ACT8945A_LDO3_VSET	0x60
#घोषणा ACT8945A_LDO3_CTRL	0x61
#घोषणा ACT8945A_LDO3_SUS	0x62
#घोषणा ACT8945A_LDO4_VSET	0x64
#घोषणा ACT8945A_LDO4_CTRL	0x65
#घोषणा ACT8945A_LDO4_SUS	0x66

/**
 * Field Definitions.
 */
#घोषणा ACT8945A_ENA		0x80	/* ON - [7] */
#घोषणा ACT8945A_VSEL_MASK	0x3F	/* VSET - [5:0] */

/**
 * ACT8945A Voltage Number
 */
#घोषणा ACT8945A_VOLTAGE_NUM	64

क्रमागत अणु
	ACT8945A_ID_DCDC1,
	ACT8945A_ID_DCDC2,
	ACT8945A_ID_DCDC3,
	ACT8945A_ID_LDO1,
	ACT8945A_ID_LDO2,
	ACT8945A_ID_LDO3,
	ACT8945A_ID_LDO4,
	ACT8945A_ID_MAX,
पूर्ण;

काष्ठा act8945a_pmic अणु
	काष्ठा regmap *regmap;
	u32 op_mode[ACT8945A_ID_MAX];
पूर्ण;

अटल स्थिर काष्ठा linear_range act8945a_voltage_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0, 23, 25000),
	REGULATOR_LINEAR_RANGE(1200000, 24, 47, 50000),
	REGULATOR_LINEAR_RANGE(2400000, 48, 63, 100000),
पूर्ण;

अटल पूर्णांक act8945a_set_suspend_state(काष्ठा regulator_dev *rdev, bool enable)
अणु
	काष्ठा regmap *regmap = rdev->regmap;
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक reg, val;

	चयन (id) अणु
	हाल ACT8945A_ID_DCDC1:
		reg = ACT8945A_DCDC1_SUS;
		val = 0xa8;
		अवरोध;
	हाल ACT8945A_ID_DCDC2:
		reg = ACT8945A_DCDC2_SUS;
		val = 0xa8;
		अवरोध;
	हाल ACT8945A_ID_DCDC3:
		reg = ACT8945A_DCDC3_SUS;
		val = 0xa8;
		अवरोध;
	हाल ACT8945A_ID_LDO1:
		reg = ACT8945A_LDO1_SUS;
		val = 0xe8;
		अवरोध;
	हाल ACT8945A_ID_LDO2:
		reg = ACT8945A_LDO2_SUS;
		val = 0xe8;
		अवरोध;
	हाल ACT8945A_ID_LDO3:
		reg = ACT8945A_LDO3_SUS;
		val = 0xe8;
		अवरोध;
	हाल ACT8945A_ID_LDO4:
		reg = ACT8945A_LDO4_SUS;
		val = 0xe8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (enable)
		val |= BIT(4);

	/*
	 * Ask the PMIC to enable/disable this output when entering hibernate
	 * mode.
	 */
	वापस regmap_ग_लिखो(regmap, reg, val);
पूर्ण

अटल पूर्णांक act8945a_set_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	वापस act8945a_set_suspend_state(rdev, true);
पूर्ण

अटल पूर्णांक act8945a_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	वापस act8945a_set_suspend_state(rdev, false);
पूर्ण

अटल अचिन्हित पूर्णांक act8945a_of_map_mode(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल ACT8945A_REGULATOR_MODE_FIXED:
	हाल ACT8945A_REGULATOR_MODE_NORMAL:
		वापस REGULATOR_MODE_NORMAL;
	हाल ACT8945A_REGULATOR_MODE_LOWPOWER:
		वापस REGULATOR_MODE_STANDBY;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

अटल पूर्णांक act8945a_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा act8945a_pmic *act8945a = rdev_get_drvdata(rdev);
	काष्ठा regmap *regmap = rdev->regmap;
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक reg, ret, val = 0;

	चयन (id) अणु
	हाल ACT8945A_ID_DCDC1:
		reg = ACT8945A_DCDC1_CTRL;
		अवरोध;
	हाल ACT8945A_ID_DCDC2:
		reg = ACT8945A_DCDC2_CTRL;
		अवरोध;
	हाल ACT8945A_ID_DCDC3:
		reg = ACT8945A_DCDC3_CTRL;
		अवरोध;
	हाल ACT8945A_ID_LDO1:
		reg = ACT8945A_LDO1_CTRL;
		अवरोध;
	हाल ACT8945A_ID_LDO2:
		reg = ACT8945A_LDO2_CTRL;
		अवरोध;
	हाल ACT8945A_ID_LDO3:
		reg = ACT8945A_LDO3_CTRL;
		अवरोध;
	हाल ACT8945A_ID_LDO4:
		reg = ACT8945A_LDO4_CTRL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (mode) अणु
	हाल REGULATOR_MODE_STANDBY:
		अगर (id > ACT8945A_ID_DCDC3)
			val = BIT(5);
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		अगर (id <= ACT8945A_ID_DCDC3)
			val = BIT(5);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(regmap, reg, BIT(5), val);
	अगर (ret)
		वापस ret;

	act8945a->op_mode[id] = mode;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक act8945a_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा act8945a_pmic *act8945a = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);

	अगर (id < ACT8945A_ID_DCDC1 || id >= ACT8945A_ID_MAX)
		वापस -EINVAL;

	वापस act8945a->op_mode[id];
पूर्ण

अटल स्थिर काष्ठा regulator_ops act8945a_ops = अणु
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.set_mode		= act8945a_set_mode,
	.get_mode		= act8945a_get_mode,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_suspend_enable	= act8945a_set_suspend_enable,
	.set_suspend_disable	= act8945a_set_suspend_disable,
पूर्ण;

#घोषणा ACT89xx_REG(_name, _family, _id, _vsel_reg, _supply)		\
	[_family##_ID_##_id] = अणु					\
		.name			= _name,			\
		.supply_name		= _supply,			\
		.of_match		= of_match_ptr("REG_"#_id),	\
		.of_map_mode		= act8945a_of_map_mode,		\
		.regulators_node	= of_match_ptr("regulators"),	\
		.id			= _family##_ID_##_id,		\
		.type			= REGULATOR_VOLTAGE,		\
		.ops			= &act8945a_ops,		\
		.n_voltages		= ACT8945A_VOLTAGE_NUM,		\
		.linear_ranges		= act8945a_voltage_ranges,	\
		.n_linear_ranges	= ARRAY_SIZE(act8945a_voltage_ranges), \
		.vsel_reg		= _family##_##_id##_##_vsel_reg, \
		.vsel_mask		= ACT8945A_VSEL_MASK,		\
		.enable_reg		= _family##_##_id##_CTRL,	\
		.enable_mask		= ACT8945A_ENA,			\
		.owner			= THIS_MODULE,			\
	पूर्ण

अटल स्थिर काष्ठा regulator_desc act8945a_regulators[] = अणु
	ACT89xx_REG("DCDC_REG1", ACT8945A, DCDC1, VSET1, "vp1"),
	ACT89xx_REG("DCDC_REG2", ACT8945A, DCDC2, VSET1, "vp2"),
	ACT89xx_REG("DCDC_REG3", ACT8945A, DCDC3, VSET1, "vp3"),
	ACT89xx_REG("LDO_REG1", ACT8945A, LDO1, VSET, "inl45"),
	ACT89xx_REG("LDO_REG2", ACT8945A, LDO2, VSET, "inl45"),
	ACT89xx_REG("LDO_REG3", ACT8945A, LDO3, VSET, "inl67"),
	ACT89xx_REG("LDO_REG4", ACT8945A, LDO4, VSET, "inl67"),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc act8945a_alt_regulators[] = अणु
	ACT89xx_REG("DCDC_REG1", ACT8945A, DCDC1, VSET2, "vp1"),
	ACT89xx_REG("DCDC_REG2", ACT8945A, DCDC2, VSET2, "vp2"),
	ACT89xx_REG("DCDC_REG3", ACT8945A, DCDC3, VSET2, "vp3"),
	ACT89xx_REG("LDO_REG1", ACT8945A, LDO1, VSET, "inl45"),
	ACT89xx_REG("LDO_REG2", ACT8945A, LDO2, VSET, "inl45"),
	ACT89xx_REG("LDO_REG3", ACT8945A, LDO3, VSET, "inl67"),
	ACT89xx_REG("LDO_REG4", ACT8945A, LDO4, VSET, "inl67"),
पूर्ण;

अटल पूर्णांक act8945a_pmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator_config config = अणु पूर्ण;
	स्थिर काष्ठा regulator_desc *regulators;
	काष्ठा act8945a_pmic *act8945a;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i, num_regulators;
	bool voltage_select;

	act8945a = devm_kzalloc(&pdev->dev, माप(*act8945a), GFP_KERNEL);
	अगर (!act8945a)
		वापस -ENOMEM;

	act8945a->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!act8945a->regmap) अणु
		dev_err(&pdev->dev,
			"could not retrieve regmap from parent device\n");
		वापस -EINVAL;
	पूर्ण

	voltage_select = of_property_पढ़ो_bool(pdev->dev.parent->of_node,
					       "active-semi,vsel-high");

	अगर (voltage_select) अणु
		regulators = act8945a_alt_regulators;
		num_regulators = ARRAY_SIZE(act8945a_alt_regulators);
	पूर्ण अन्यथा अणु
		regulators = act8945a_regulators;
		num_regulators = ARRAY_SIZE(act8945a_regulators);
	पूर्ण

	config.dev = &pdev->dev;
	config.dev->of_node = pdev->dev.parent->of_node;
	config.driver_data = act8945a;
	क्रम (i = 0; i < num_regulators; i++) अणु
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev,
				"failed to register %s regulator\n",
				regulators[i].name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, act8945a);

	/* Unlock expert रेजिस्टरs. */
	वापस regmap_ग_लिखो(act8945a->regmap, ACT8945A_SYS_UNLK_REGS, 0xef);
पूर्ण

अटल पूर्णांक __maybe_unused act8945a_suspend(काष्ठा device *pdev)
अणु
	काष्ठा act8945a_pmic *act8945a = dev_get_drvdata(pdev);

	/*
	 * Ask the PMIC to enter the suspend mode on the next PWRHLD
	 * transition.
	 */
	वापस regmap_ग_लिखो(act8945a->regmap, ACT8945A_SYS_CTRL, 0x42);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(act8945a_pm, act8945a_suspend, शून्य);

अटल व्योम act8945a_pmic_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा act8945a_pmic *act8945a = platक्रमm_get_drvdata(pdev);

	/*
	 * Ask the PMIC to shutकरोwn everything on the next PWRHLD transition.
	 */
	regmap_ग_लिखो(act8945a->regmap, ACT8945A_SYS_CTRL, 0x0);
पूर्ण

अटल काष्ठा platक्रमm_driver act8945a_pmic_driver = अणु
	.driver = अणु
		.name = "act8945a-regulator",
		.pm = &act8945a_pm,
	पूर्ण,
	.probe = act8945a_pmic_probe,
	.shutकरोwn = act8945a_pmic_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(act8945a_pmic_driver);

MODULE_DESCRIPTION("Active-semi ACT8945A voltage regulator driver");
MODULE_AUTHOR("Wenyou Yang <wenyou.yang@atmel.com>");
MODULE_LICENSE("GPL");
