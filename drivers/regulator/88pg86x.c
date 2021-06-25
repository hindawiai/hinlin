<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regmap.h>

अटल स्थिर काष्ठा regulator_ops pg86x_ops = अणु
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
पूर्ण;

अटल स्थिर काष्ठा linear_range pg86x_buck1_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(      0,  0, 10,     0),
	REGULATOR_LINEAR_RANGE(1000000, 11, 34, 25000),
	REGULATOR_LINEAR_RANGE(1600000, 35, 47, 50000),
पूर्ण;

अटल स्थिर काष्ठा linear_range pg86x_buck2_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(      0,  0, 15,     0),
	REGULATOR_LINEAR_RANGE(1000000, 16, 39, 25000),
	REGULATOR_LINEAR_RANGE(1600000, 40, 52, 50000),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pg86x_regulators[] = अणु
	अणु
		.id = 0,
		.type = REGULATOR_VOLTAGE,
		.name = "buck1",
		.of_match = of_match_ptr("buck1"),
		.n_voltages = 11 + 24 + 13,
		.linear_ranges = pg86x_buck1_ranges,
		.n_linear_ranges = 3,
		.vsel_reg  = 0x24,
		.vsel_mask = 0xff,
		.ops = &pg86x_ops,
		.owner = THIS_MODULE
	पूर्ण,
	अणु
		.id = 1,
		.type = REGULATOR_VOLTAGE,
		.name = "buck2",
		.of_match = of_match_ptr("buck2"),
		.n_voltages = 16 + 24 + 13,
		.linear_ranges = pg86x_buck2_ranges,
		.n_linear_ranges = 3,
		.vsel_reg  = 0x13,
		.vsel_mask = 0xff,
		.ops = &pg86x_ops,
		.owner = THIS_MODULE
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config pg86x_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक pg86x_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	पूर्णांक id, ret;
	काष्ठा regulator_config config = अणु.dev = &i2c->devपूर्ण;
	काष्ठा regmap *regmap = devm_regmap_init_i2c(i2c, &pg86x_regmap);

	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (id = 0; id < ARRAY_SIZE(pg86x_regulators); id++) अणु
		काष्ठा regulator_dev *rdev;
		rdev = devm_regulator_रेजिस्टर(&i2c->dev,
					       &pg86x_regulators[id],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			ret = PTR_ERR(rdev);
			dev_err(&i2c->dev, "failed to register %s: %d\n",
				pg86x_regulators[id].name, ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused pg86x_dt_ids[] = अणु
	अणु .compatible = "marvell,88pg867" पूर्ण,
	अणु .compatible = "marvell,88pg868" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pg86x_dt_ids);

अटल स्थिर काष्ठा i2c_device_id pg86x_i2c_id[] = अणु
	अणु "88pg867", पूर्ण,
	अणु "88pg868", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pg86x_i2c_id);

अटल काष्ठा i2c_driver pg86x_regulator_driver = अणु
	.driver = अणु
		.name = "88pg86x",
		.of_match_table = of_match_ptr(pg86x_dt_ids),
	पूर्ण,
	.probe_new = pg86x_i2c_probe,
	.id_table = pg86x_i2c_id,
पूर्ण;

module_i2c_driver(pg86x_regulator_driver);

MODULE_DESCRIPTION("Marvell 88PG86X voltage regulator");
MODULE_AUTHOR("Alexander Monakov <amonakov@gmail.com>");
MODULE_LICENSE("GPL");
