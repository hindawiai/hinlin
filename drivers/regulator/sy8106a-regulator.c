<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// sy8106a-regulator.c - Regulator device driver क्रम SY8106A
//
// Copyright (C) 2016 Ondधej Jirman <megous@megous.com>
// Copyright (c) 2017-2018 Icenowy Zheng <icenowy@aosc.io>

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा SY8106A_REG_VOUT1_SEL		0x01
#घोषणा SY8106A_REG_VOUT_COM		0x02
#घोषणा SY8106A_REG_VOUT1_SEL_MASK	0x7f
#घोषणा SY8106A_DISABLE_REG		BIT(0)
/*
 * The I2C controlled voltage will only work when this bit is set; otherwise
 * it will behave like a fixed regulator.
 */
#घोषणा SY8106A_GO_BIT			BIT(7)

अटल स्थिर काष्ठा regmap_config sy8106a_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops sy8106a_ops = अणु
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
	/* Enabling/disabling the regulator is not yet implemented */
पूर्ण;

/* Default limits measured in millivolts */
#घोषणा SY8106A_MIN_MV		680
#घोषणा SY8106A_MAX_MV		1950
#घोषणा SY8106A_STEP_MV		10

अटल स्थिर काष्ठा regulator_desc sy8106a_reg = अणु
	.name = "SY8106A",
	.id = 0,
	.ops = &sy8106a_ops,
	.type = REGULATOR_VOLTAGE,
	.n_voltages = ((SY8106A_MAX_MV - SY8106A_MIN_MV) / SY8106A_STEP_MV) + 1,
	.min_uV = (SY8106A_MIN_MV * 1000),
	.uV_step = (SY8106A_STEP_MV * 1000),
	.vsel_reg = SY8106A_REG_VOUT1_SEL,
	.vsel_mask = SY8106A_REG_VOUT1_SEL_MASK,
	/*
	 * This ramp_delay is a conservative शेष value which works on
	 * H3/H5 boards VDD-CPUX situations.
	 */
	.ramp_delay = 200,
	.owner = THIS_MODULE,
पूर्ण;

/*
 * I2C driver पूर्णांकerface functions
 */
अटल पूर्णांक sy8106a_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक reg, vsel;
	u32 fixed_voltage;
	पूर्णांक error;

	error = of_property_पढ़ो_u32(dev->of_node, "silergy,fixed-microvolt",
				     &fixed_voltage);
	अगर (error)
		वापस error;

	अगर (fixed_voltage < SY8106A_MIN_MV * 1000 ||
	    fixed_voltage > SY8106A_MAX_MV * 1000)
		वापस -EINVAL;

	regmap = devm_regmap_init_i2c(i2c, &sy8106a_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		error = PTR_ERR(regmap);
		dev_err(dev, "Failed to allocate register map: %d\n", error);
		वापस error;
	पूर्ण

	config.dev = &i2c->dev;
	config.regmap = regmap;

	config.of_node = dev->of_node;
	config.init_data = of_get_regulator_init_data(dev, dev->of_node,
						      &sy8106a_reg);

	अगर (!config.init_data)
		वापस -ENOMEM;

	/* Ensure GO_BIT is enabled when probing */
	error = regmap_पढ़ो(regmap, SY8106A_REG_VOUT1_SEL, &reg);
	अगर (error)
		वापस error;

	अगर (!(reg & SY8106A_GO_BIT)) अणु
		vsel = (fixed_voltage / 1000 - SY8106A_MIN_MV) /
		       SY8106A_STEP_MV;

		error = regmap_ग_लिखो(regmap, SY8106A_REG_VOUT1_SEL,
				     vsel | SY8106A_GO_BIT);
		अगर (error)
			वापस error;
	पूर्ण

	/* Probe regulator */
	rdev = devm_regulator_रेजिस्टर(&i2c->dev, &sy8106a_reg, &config);
	अगर (IS_ERR(rdev)) अणु
		error = PTR_ERR(rdev);
		dev_err(&i2c->dev, "Failed to register SY8106A regulator: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused sy8106a_i2c_of_match[] = अणु
	अणु .compatible = "silergy,sy8106a" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sy8106a_i2c_of_match);

अटल स्थिर काष्ठा i2c_device_id sy8106a_i2c_id[] = अणु
	अणु "sy8106a", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sy8106a_i2c_id);

अटल काष्ठा i2c_driver sy8106a_regulator_driver = अणु
	.driver = अणु
		.name = "sy8106a",
		.of_match_table	= of_match_ptr(sy8106a_i2c_of_match),
	पूर्ण,
	.probe_new = sy8106a_i2c_probe,
	.id_table = sy8106a_i2c_id,
पूर्ण;

module_i2c_driver(sy8106a_regulator_driver);

MODULE_AUTHOR("Ondधej Jirman <megous@megous.com>");
MODULE_AUTHOR("Icenowy Zheng <icenowy@aosc.io>");
MODULE_DESCRIPTION("Regulator device driver for Silergy SY8106A");
MODULE_LICENSE("GPL");
