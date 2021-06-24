<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * isl9305 - Intersil ISL9305 DCDC regulator
 *
 * Copyright 2014 Linaro Ltd
 *
 * Author: Mark Brown <broonie@kernel.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/isl9305.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>

/*
 * Registers
 */
#घोषणा ISL9305_DCD1OUT          0x0
#घोषणा ISL9305_DCD2OUT          0x1
#घोषणा ISL9305_LDO1OUT          0x2
#घोषणा ISL9305_LDO2OUT          0x3
#घोषणा ISL9305_DCD_PARAMETER    0x4
#घोषणा ISL9305_SYSTEM_PARAMETER 0x5
#घोषणा ISL9305_DCD_SRCTL        0x6

#घोषणा ISL9305_MAX_REG ISL9305_DCD_SRCTL

/*
 * DCD_PARAMETER
 */
#घोषणा ISL9305_DCD_PHASE   0x40
#घोषणा ISL9305_DCD2_ULTRA  0x20
#घोषणा ISL9305_DCD1_ULTRA  0x10
#घोषणा ISL9305_DCD2_BLD    0x08
#घोषणा ISL9305_DCD1_BLD    0x04
#घोषणा ISL9305_DCD2_MODE   0x02
#घोषणा ISL9305_DCD1_MODE   0x01

/*
 * SYSTEM_PARAMETER
 */
#घोषणा ISL9305_I2C_EN      0x40
#घोषणा ISL9305_DCDPOR_MASK 0x30
#घोषणा ISL9305_LDO2_EN     0x08
#घोषणा ISL9305_LDO1_EN     0x04
#घोषणा ISL9305_DCD2_EN     0x02
#घोषणा ISL9305_DCD1_EN     0x01

/*
 * DCD_SRCTL
 */
#घोषणा ISL9305_DCD2SR_MASK 0xc0
#घोषणा ISL9305_DCD1SR_MASK 0x07

अटल स्थिर काष्ठा regulator_ops isl9305_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc isl9305_regulators[] = अणु
	[ISL9305_DCD1] = अणु
		.name =		"DCD1",
		.of_match =	of_match_ptr("dcd1"),
		.regulators_node = of_match_ptr("regulators"),
		.n_voltages =	0x70,
		.min_uV =	825000,
		.uV_step =	25000,
		.vsel_reg =	ISL9305_DCD1OUT,
		.vsel_mask =	0x7f,
		.enable_reg =	ISL9305_SYSTEM_PARAMETER,
		.enable_mask =	ISL9305_DCD1_EN,
		.supply_name =	"VINDCD1",
		.ops =		&isl9305_ops,
		.owner =	THIS_MODULE,
	पूर्ण,
	[ISL9305_DCD2] = अणु
		.name =		"DCD2",
		.of_match =	of_match_ptr("dcd2"),
		.regulators_node = of_match_ptr("regulators"),
		.n_voltages =	0x70,
		.min_uV =	825000,
		.uV_step =	25000,
		.vsel_reg =	ISL9305_DCD2OUT,
		.vsel_mask =	0x7f,
		.enable_reg =	ISL9305_SYSTEM_PARAMETER,
		.enable_mask =	ISL9305_DCD2_EN,
		.supply_name =	"VINDCD2",
		.ops =		&isl9305_ops,
		.owner =	THIS_MODULE,
	पूर्ण,
	[ISL9305_LDO1] = अणु
		.name =		"LDO1",
		.of_match =	of_match_ptr("ldo1"),
		.regulators_node = of_match_ptr("regulators"),
		.n_voltages =	0x37,
		.min_uV =	900000,
		.uV_step =	50000,
		.vsel_reg =	ISL9305_LDO1OUT,
		.vsel_mask =	0x3f,
		.enable_reg =	ISL9305_SYSTEM_PARAMETER,
		.enable_mask =	ISL9305_LDO1_EN,
		.supply_name =	"VINLDO1",
		.ops =		&isl9305_ops,
		.owner =	THIS_MODULE,
	पूर्ण,
	[ISL9305_LDO2] = अणु
		.name =		"LDO2",
		.of_match =	of_match_ptr("ldo2"),
		.regulators_node = of_match_ptr("regulators"),
		.n_voltages =	0x37,
		.min_uV =	900000,
		.uV_step =	50000,
		.vsel_reg =	ISL9305_LDO2OUT,
		.vsel_mask =	0x3f,
		.enable_reg =	ISL9305_SYSTEM_PARAMETER,
		.enable_mask =	ISL9305_LDO2_EN,
		.supply_name =	"VINLDO2",
		.ops =		&isl9305_ops,
		.owner =	THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config isl9305_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = ISL9305_MAX_REG,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक isl9305_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा isl9305_pdata *pdata = i2c->dev.platक्रमm_data;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *regmap;
	पूर्णांक i, ret;

	regmap = devm_regmap_init_i2c(i2c, &isl9305_regmap);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "Failed to create regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	config.dev = &i2c->dev;

	क्रम (i = 0; i < ARRAY_SIZE(isl9305_regulators); i++) अणु
		अगर (pdata)
			config.init_data = pdata->init_data[i];
		अन्यथा
			config.init_data = शून्य;

		rdev = devm_regulator_रेजिस्टर(&i2c->dev,
					       &isl9305_regulators[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			ret = PTR_ERR(rdev);
			dev_err(&i2c->dev, "Failed to register %s: %d\n",
				isl9305_regulators[i].name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id isl9305_dt_ids[] = अणु
	अणु .compatible = "isl,isl9305" पूर्ण, /* क्रम backward compat., करोn't use */
	अणु .compatible = "isil,isl9305" पूर्ण,
	अणु .compatible = "isl,isl9305h" पूर्ण, /* क्रम backward compat., करोn't use */
	अणु .compatible = "isil,isl9305h" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, isl9305_dt_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id isl9305_i2c_id[] = अणु
	अणु "isl9305", पूर्ण,
	अणु "isl9305h", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, isl9305_i2c_id);

अटल काष्ठा i2c_driver isl9305_regulator_driver = अणु
	.driver = अणु
		.name = "isl9305",
		.of_match_table	= of_match_ptr(isl9305_dt_ids),
	पूर्ण,
	.probe_new = isl9305_i2c_probe,
	.id_table = isl9305_i2c_id,
पूर्ण;

module_i2c_driver(isl9305_regulator_driver);

MODULE_AUTHOR("Mark Brown");
MODULE_DESCRIPTION("Intersil ISL9305 DCDC regulator");
MODULE_LICENSE("GPL");
