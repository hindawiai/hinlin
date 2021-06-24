<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Lochnagar regulator driver
//
// Copyright (c) 2017-2018 Cirrus Logic, Inc. and
//                         Cirrus Logic International Semiconductor Ltd.
//
// Author: Charles Keepax <ckeepax@खोलोsource.cirrus.com>

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>

#समावेश <linux/mfd/lochnagar.h>
#समावेश <linux/mfd/lochnagar1_regs.h>
#समावेश <linux/mfd/lochnagar2_regs.h>

अटल स्थिर काष्ठा regulator_ops lochnagar_micvdd_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,

	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,

	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा linear_range lochnagar_micvdd_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1000000, 0,    0xC, 50000),
	REGULATOR_LINEAR_RANGE(1700000, 0xD, 0x1F, 100000),
पूर्ण;

अटल पूर्णांक lochnagar_micbias_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा lochnagar *lochnagar = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	mutex_lock(&lochnagar->analogue_config_lock);

	ret = regulator_enable_regmap(rdev);
	अगर (ret < 0)
		जाओ err;

	ret = lochnagar_update_config(lochnagar);

err:
	mutex_unlock(&lochnagar->analogue_config_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक lochnagar_micbias_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा lochnagar *lochnagar = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	mutex_lock(&lochnagar->analogue_config_lock);

	ret = regulator_disable_regmap(rdev);
	अगर (ret < 0)
		जाओ err;

	ret = lochnagar_update_config(lochnagar);

err:
	mutex_unlock(&lochnagar->analogue_config_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops lochnagar_micbias_ops = अणु
	.enable = lochnagar_micbias_enable,
	.disable = lochnagar_micbias_disable,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops lochnagar_vddcore_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,

	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,

	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा linear_range lochnagar_vddcore_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0,    0x7, 0),
	REGULATOR_LINEAR_RANGE(600000, 0x8, 0x41, 12500),
पूर्ण;

क्रमागत lochnagar_regulators अणु
	LOCHNAGAR_MICVDD,
	LOCHNAGAR_MIC1VDD,
	LOCHNAGAR_MIC2VDD,
	LOCHNAGAR_VDDCORE,
पूर्ण;

अटल पूर्णांक lochnagar_micbias_of_parse(काष्ठा device_node *np,
				      स्थिर काष्ठा regulator_desc *desc,
				      काष्ठा regulator_config *config)
अणु
	काष्ठा lochnagar *lochnagar = config->driver_data;
	पूर्णांक shअगरt = (desc->id - LOCHNAGAR_MIC1VDD) *
		    LOCHNAGAR2_P2_MICBIAS_SRC_SHIFT;
	पूर्णांक mask = LOCHNAGAR2_P1_MICBIAS_SRC_MASK << shअगरt;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "cirrus,micbias-input", &val);
	अगर (ret >= 0) अणु
		mutex_lock(&lochnagar->analogue_config_lock);
		ret = regmap_update_bits(lochnagar->regmap,
					 LOCHNAGAR2_ANALOGUE_PATH_CTRL2,
					 mask, val << shअगरt);
		mutex_unlock(&lochnagar->analogue_config_lock);
		अगर (ret < 0) अणु
			dev_err(lochnagar->dev,
				"Failed to update micbias source: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_desc lochnagar_regulators[] = अणु
	[LOCHNAGAR_MICVDD] = अणु
		.name = "MICVDD",
		.supply_name = "SYSVDD",
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 32,
		.ops = &lochnagar_micvdd_ops,

		.id = LOCHNAGAR_MICVDD,
		.of_match = of_match_ptr("MICVDD"),

		.enable_reg = LOCHNAGAR2_MICVDD_CTRL1,
		.enable_mask = LOCHNAGAR2_MICVDD_REG_ENA_MASK,
		.vsel_reg = LOCHNAGAR2_MICVDD_CTRL2,
		.vsel_mask = LOCHNAGAR2_MICVDD_VSEL_MASK,

		.linear_ranges = lochnagar_micvdd_ranges,
		.n_linear_ranges = ARRAY_SIZE(lochnagar_micvdd_ranges),

		.enable_समय = 3000,
		.ramp_delay = 1000,

		.owner = THIS_MODULE,
	पूर्ण,
	[LOCHNAGAR_MIC1VDD] = अणु
		.name = "MIC1VDD",
		.supply_name = "MICBIAS1",
		.type = REGULATOR_VOLTAGE,
		.ops = &lochnagar_micbias_ops,

		.id = LOCHNAGAR_MIC1VDD,
		.of_match = of_match_ptr("MIC1VDD"),
		.of_parse_cb = lochnagar_micbias_of_parse,

		.enable_reg = LOCHNAGAR2_ANALOGUE_PATH_CTRL2,
		.enable_mask = LOCHNAGAR2_P1_INPUT_BIAS_ENA_MASK,

		.owner = THIS_MODULE,
	पूर्ण,
	[LOCHNAGAR_MIC2VDD] = अणु
		.name = "MIC2VDD",
		.supply_name = "MICBIAS2",
		.type = REGULATOR_VOLTAGE,
		.ops = &lochnagar_micbias_ops,

		.id = LOCHNAGAR_MIC2VDD,
		.of_match = of_match_ptr("MIC2VDD"),
		.of_parse_cb = lochnagar_micbias_of_parse,

		.enable_reg = LOCHNAGAR2_ANALOGUE_PATH_CTRL2,
		.enable_mask = LOCHNAGAR2_P2_INPUT_BIAS_ENA_MASK,

		.owner = THIS_MODULE,
	पूर्ण,
	[LOCHNAGAR_VDDCORE] = अणु
		.name = "VDDCORE",
		.supply_name = "SYSVDD",
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 66,
		.ops = &lochnagar_vddcore_ops,

		.id = LOCHNAGAR_VDDCORE,
		.of_match = of_match_ptr("VDDCORE"),

		.enable_reg = LOCHNAGAR2_VDDCORE_CDC_CTRL1,
		.enable_mask = LOCHNAGAR2_VDDCORE_CDC_REG_ENA_MASK,
		.vsel_reg = LOCHNAGAR2_VDDCORE_CDC_CTRL2,
		.vsel_mask = LOCHNAGAR2_VDDCORE_CDC_VSEL_MASK,

		.linear_ranges = lochnagar_vddcore_ranges,
		.n_linear_ranges = ARRAY_SIZE(lochnagar_vddcore_ranges),

		.enable_समय = 3000,
		.ramp_delay = 1000,
		.off_on_delay = 15000,

		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id lochnagar_of_match[] = अणु
	अणु
		.compatible = "cirrus,lochnagar2-micvdd",
		.data = &lochnagar_regulators[LOCHNAGAR_MICVDD],
	पूर्ण,
	अणु
		.compatible = "cirrus,lochnagar2-mic1vdd",
		.data = &lochnagar_regulators[LOCHNAGAR_MIC1VDD],
	पूर्ण,
	अणु
		.compatible = "cirrus,lochnagar2-mic2vdd",
		.data = &lochnagar_regulators[LOCHNAGAR_MIC2VDD],
	पूर्ण,
	अणु
		.compatible = "cirrus,lochnagar2-vddcore",
		.data = &lochnagar_regulators[LOCHNAGAR_VDDCORE],
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lochnagar_of_match);

अटल पूर्णांक lochnagar_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा lochnagar *lochnagar = dev_get_drvdata(dev->parent);
	काष्ठा regulator_config config = अणु पूर्ण;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा regulator_desc *desc;
	काष्ठा regulator_dev *rdev;
	पूर्णांक ret;

	config.dev = dev;
	config.regmap = lochnagar->regmap;
	config.driver_data = lochnagar;

	of_id = of_match_device(lochnagar_of_match, dev);
	अगर (!of_id)
		वापस -EINVAL;

	desc = of_id->data;

	rdev = devm_regulator_रेजिस्टर(dev, desc, &config);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(dev, "Failed to register %s regulator: %d\n",
			desc->name, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lochnagar_regulator_driver = अणु
	.driver = अणु
		.name = "lochnagar-regulator",
		.of_match_table = of_match_ptr(lochnagar_of_match),
	पूर्ण,

	.probe = lochnagar_regulator_probe,
पूर्ण;
module_platक्रमm_driver(lochnagar_regulator_driver);

MODULE_AUTHOR("Charles Keepax <ckeepax@opensource.cirrus.com>");
MODULE_DESCRIPTION("Regulator driver for Cirrus Logic Lochnagar Board");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:lochnagar-regulator");
