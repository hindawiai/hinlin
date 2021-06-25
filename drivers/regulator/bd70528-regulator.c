<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 ROHM Semiconductors
// bd70528-regulator.c ROHM BD70528MWV regulator driver

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/rohm-bd70528.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>

#घोषणा BUCK_RAMPRATE_250MV 0
#घोषणा BUCK_RAMPRATE_125MV 1
#घोषणा BUCK_RAMP_MAX 250

अटल स्थिर काष्ठा linear_range bd70528_buck1_volts[] = अणु
	REGULATOR_LINEAR_RANGE(1200000, 0x00, 0x1, 600000),
	REGULATOR_LINEAR_RANGE(2750000, 0x2, 0xf, 50000),
पूर्ण;
अटल स्थिर काष्ठा linear_range bd70528_buck2_volts[] = अणु
	REGULATOR_LINEAR_RANGE(1200000, 0x00, 0x1, 300000),
	REGULATOR_LINEAR_RANGE(1550000, 0x2, 0xd, 50000),
	REGULATOR_LINEAR_RANGE(3000000, 0xe, 0xf, 300000),
पूर्ण;
अटल स्थिर काष्ठा linear_range bd70528_buck3_volts[] = अणु
	REGULATOR_LINEAR_RANGE(800000, 0x00, 0xd, 50000),
	REGULATOR_LINEAR_RANGE(1800000, 0xe, 0xf, 0),
पूर्ण;

/* All LDOs have same voltage ranges */
अटल स्थिर काष्ठा linear_range bd70528_lकरो_volts[] = अणु
	REGULATOR_LINEAR_RANGE(1650000, 0x0, 0x07, 50000),
	REGULATOR_LINEAR_RANGE(2100000, 0x8, 0x0f, 100000),
	REGULATOR_LINEAR_RANGE(2850000, 0x10, 0x19, 50000),
	REGULATOR_LINEAR_RANGE(3300000, 0x19, 0x1f, 0),
पूर्ण;

/* Also both LEDs support same voltages */
अटल स्थिर अचिन्हित पूर्णांक led_volts[] = अणु
	20000, 30000
पूर्ण;

अटल पूर्णांक bd70528_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	अगर (ramp_delay > 0 && ramp_delay <= BUCK_RAMP_MAX) अणु
		अचिन्हित पूर्णांक ramp_value = BUCK_RAMPRATE_250MV;

		अगर (ramp_delay <= 125)
			ramp_value = BUCK_RAMPRATE_125MV;

		वापस regmap_update_bits(rdev->regmap, rdev->desc->vsel_reg,
				  BD70528_MASK_BUCK_RAMP,
				  ramp_value << BD70528_SIFT_BUCK_RAMP);
	पूर्ण
	dev_err(&rdev->dev, "%s: ramp_delay: %d not supported\n",
		rdev->desc->name, ramp_delay);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bd70528_led_set_voltage_sel(काष्ठा regulator_dev *rdev,
				       अचिन्हित पूर्णांक sel)
अणु
	पूर्णांक ret;

	ret = regulator_is_enabled_regmap(rdev);
	अगर (ret < 0)
		वापस ret;

	अगर (ret == 0)
		वापस regulator_set_voltage_sel_regmap(rdev, sel);

	dev_err(&rdev->dev,
		"LED voltage change not allowed when led is enabled\n");

	वापस -EBUSY;
पूर्ण

अटल स्थिर काष्ठा regulator_ops bd70528_buck_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.set_ramp_delay = bd70528_set_ramp_delay,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops bd70528_lकरो_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops bd70528_led_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_table,
	.set_voltage_sel = bd70528_led_set_voltage_sel,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc bd70528_desc[] = अणु
	अणु
		.name = "buck1",
		.of_match = of_match_ptr("BUCK1"),
		.regulators_node = of_match_ptr("regulators"),
		.id = BD70528_BUCK1,
		.ops = &bd70528_buck_ops,
		.type = REGULATOR_VOLTAGE,
		.linear_ranges = bd70528_buck1_volts,
		.n_linear_ranges = ARRAY_SIZE(bd70528_buck1_volts),
		.n_voltages = BD70528_BUCK_VOLTS,
		.enable_reg = BD70528_REG_BUCK1_EN,
		.enable_mask = BD70528_MASK_RUN_EN,
		.vsel_reg = BD70528_REG_BUCK1_VOLT,
		.vsel_mask = BD70528_MASK_BUCK_VOLT,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "buck2",
		.of_match = of_match_ptr("BUCK2"),
		.regulators_node = of_match_ptr("regulators"),
		.id = BD70528_BUCK2,
		.ops = &bd70528_buck_ops,
		.type = REGULATOR_VOLTAGE,
		.linear_ranges = bd70528_buck2_volts,
		.n_linear_ranges = ARRAY_SIZE(bd70528_buck2_volts),
		.n_voltages = BD70528_BUCK_VOLTS,
		.enable_reg = BD70528_REG_BUCK2_EN,
		.enable_mask = BD70528_MASK_RUN_EN,
		.vsel_reg = BD70528_REG_BUCK2_VOLT,
		.vsel_mask = BD70528_MASK_BUCK_VOLT,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "buck3",
		.of_match = of_match_ptr("BUCK3"),
		.regulators_node = of_match_ptr("regulators"),
		.id = BD70528_BUCK3,
		.ops = &bd70528_buck_ops,
		.type = REGULATOR_VOLTAGE,
		.linear_ranges = bd70528_buck3_volts,
		.n_linear_ranges = ARRAY_SIZE(bd70528_buck3_volts),
		.n_voltages = BD70528_BUCK_VOLTS,
		.enable_reg = BD70528_REG_BUCK3_EN,
		.enable_mask = BD70528_MASK_RUN_EN,
		.vsel_reg = BD70528_REG_BUCK3_VOLT,
		.vsel_mask = BD70528_MASK_BUCK_VOLT,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "ldo1",
		.of_match = of_match_ptr("LDO1"),
		.regulators_node = of_match_ptr("regulators"),
		.id = BD70528_LDO1,
		.ops = &bd70528_lकरो_ops,
		.type = REGULATOR_VOLTAGE,
		.linear_ranges = bd70528_lकरो_volts,
		.n_linear_ranges = ARRAY_SIZE(bd70528_lकरो_volts),
		.n_voltages = BD70528_LDO_VOLTS,
		.enable_reg = BD70528_REG_LDO1_EN,
		.enable_mask = BD70528_MASK_RUN_EN,
		.vsel_reg = BD70528_REG_LDO1_VOLT,
		.vsel_mask = BD70528_MASK_LDO_VOLT,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "ldo2",
		.of_match = of_match_ptr("LDO2"),
		.regulators_node = of_match_ptr("regulators"),
		.id = BD70528_LDO2,
		.ops = &bd70528_lकरो_ops,
		.type = REGULATOR_VOLTAGE,
		.linear_ranges = bd70528_lकरो_volts,
		.n_linear_ranges = ARRAY_SIZE(bd70528_lकरो_volts),
		.n_voltages = BD70528_LDO_VOLTS,
		.enable_reg = BD70528_REG_LDO2_EN,
		.enable_mask = BD70528_MASK_RUN_EN,
		.vsel_reg = BD70528_REG_LDO2_VOLT,
		.vsel_mask = BD70528_MASK_LDO_VOLT,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "ldo3",
		.of_match = of_match_ptr("LDO3"),
		.regulators_node = of_match_ptr("regulators"),
		.id = BD70528_LDO3,
		.ops = &bd70528_lकरो_ops,
		.type = REGULATOR_VOLTAGE,
		.linear_ranges = bd70528_lकरो_volts,
		.n_linear_ranges = ARRAY_SIZE(bd70528_lकरो_volts),
		.n_voltages = BD70528_LDO_VOLTS,
		.enable_reg = BD70528_REG_LDO3_EN,
		.enable_mask = BD70528_MASK_RUN_EN,
		.vsel_reg = BD70528_REG_LDO3_VOLT,
		.vsel_mask = BD70528_MASK_LDO_VOLT,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "ldo_led1",
		.of_match = of_match_ptr("LDO_LED1"),
		.regulators_node = of_match_ptr("regulators"),
		.id = BD70528_LED1,
		.ops = &bd70528_led_ops,
		.type = REGULATOR_VOLTAGE,
		.volt_table = &led_volts[0],
		.n_voltages = ARRAY_SIZE(led_volts),
		.enable_reg = BD70528_REG_LED_EN,
		.enable_mask = BD70528_MASK_LED1_EN,
		.vsel_reg = BD70528_REG_LED_VOLT,
		.vsel_mask = BD70528_MASK_LED1_VOLT,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "ldo_led2",
		.of_match = of_match_ptr("LDO_LED2"),
		.regulators_node = of_match_ptr("regulators"),
		.id = BD70528_LED2,
		.ops = &bd70528_led_ops,
		.type = REGULATOR_VOLTAGE,
		.volt_table = &led_volts[0],
		.n_voltages = ARRAY_SIZE(led_volts),
		.enable_reg = BD70528_REG_LED_EN,
		.enable_mask = BD70528_MASK_LED2_EN,
		.vsel_reg = BD70528_REG_LED_VOLT,
		.vsel_mask = BD70528_MASK_LED2_VOLT,
		.owner = THIS_MODULE,
	पूर्ण,

पूर्ण;

अटल पूर्णांक bd70528_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा regulator_config config = अणु
		.dev = pdev->dev.parent,
	पूर्ण;

	config.regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!config.regmap)
		वापस -ENODEV;

	क्रम (i = 0; i < ARRAY_SIZE(bd70528_desc); i++) अणु
		काष्ठा regulator_dev *rdev;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &bd70528_desc[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev,
				"failed to register %s regulator\n",
				bd70528_desc[i].name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bd70528_regulator = अणु
	.driver = अणु
		.name = "bd70528-pmic"
	पूर्ण,
	.probe = bd70528_probe,
पूर्ण;

module_platक्रमm_driver(bd70528_regulator);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("BD70528 voltage regulator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bd70528-pmic");
