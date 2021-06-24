<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// sky81452-regulator.c	SKY81452 regulator driver
//
// Copyright 2014 Skyworks Solutions Inc.
// Author : Gyungoh Yoo <jack.yoo@skyworksinc.com>

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>

/* रेजिस्टरs */
#घोषणा SKY81452_REG1	0x01
#घोषणा SKY81452_REG3	0x03

/* bit mask */
#घोषणा SKY81452_LEN	0x40
#घोषणा SKY81452_LOUT	0x1F

अटल स्थिर काष्ठा regulator_ops sky81452_reg_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल स्थिर काष्ठा linear_range sky81452_reg_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(4500000, 0, 14, 250000),
	REGULATOR_LINEAR_RANGE(9000000, 15, 31, 1000000),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc sky81452_reg = अणु
	.name = "LOUT",
	.of_match = of_match_ptr("lout"),
	.regulators_node = of_match_ptr("regulator"),
	.ops = &sky81452_reg_ops,
	.type = REGULATOR_VOLTAGE,
	.owner = THIS_MODULE,
	.n_voltages = SKY81452_LOUT + 1,
	.linear_ranges = sky81452_reg_ranges,
	.n_linear_ranges = ARRAY_SIZE(sky81452_reg_ranges),
	.vsel_reg = SKY81452_REG3,
	.vsel_mask = SKY81452_LOUT,
	.enable_reg = SKY81452_REG1,
	.enable_mask = SKY81452_LEN,
पूर्ण;

अटल पूर्णांक sky81452_reg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा regulator_init_data *init_data = dev_get_platdata(dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;

	config.dev = dev->parent;
	config.init_data = init_data;
	config.of_node = dev->of_node;
	config.regmap = dev_get_drvdata(dev->parent);

	rdev = devm_regulator_रेजिस्टर(dev, &sky81452_reg, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(dev, "failed to register. err=%ld\n", PTR_ERR(rdev));
		वापस PTR_ERR(rdev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, rdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sky81452_reg_driver = अणु
	.driver = अणु
		.name = "sky81452-regulator",
	पूर्ण,
	.probe = sky81452_reg_probe,
पूर्ण;

module_platक्रमm_driver(sky81452_reg_driver);

MODULE_DESCRIPTION("Skyworks SKY81452 Regulator driver");
MODULE_AUTHOR("Gyungoh Yoo <jack.yoo@skyworksinc.com>");
MODULE_LICENSE("GPL v2");
