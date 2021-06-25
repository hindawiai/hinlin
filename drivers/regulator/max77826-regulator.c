<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
//
// max77826-regulator.c  - regulator driver क्रम Maxim MAX77826
//
// Author: Iskren Chernev <iskren.chernev@gmail.com>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>

क्रमागत max77826_रेजिस्टरs अणु
	MAX77826_REG_INT_SRC = 0x00,
	MAX77826_REG_SYS_INT,
	MAX77826_REG_INT1,
	MAX77826_REG_INT2,
	MAX77826_REG_BB_INT,
	MAX77826_REG_INT_SRC_M,
	MAX77826_REG_TOPSYS_INT_M,
	MAX77826_REG_INT1_M,
	MAX77826_REG_INT2_M,
	MAX77826_REG_BB_INT_M,
	MAX77826_REG_TOPSYS_STAT,
	MAX77826_REG_STAT1,
	MAX77826_REG_STAT2,
	MAX77826_REG_BB_STAT,
	/* 0x0E - 0x0F: Reserved */
	MAX77826_REG_LDO_OPMD1 = 0x10,
	MAX77826_REG_LDO_OPMD2,
	MAX77826_REG_LDO_OPMD3,
	MAX77826_REG_LDO_OPMD4,
	MAX77826_REG_B_BB_OPMD,
	/* 0x15 - 0x1F: Reserved */
	MAX77826_REG_LDO1_CFG = 0x20,
	MAX77826_REG_LDO2_CFG,
	MAX77826_REG_LDO3_CFG,
	MAX77826_REG_LDO4_CFG,
	MAX77826_REG_LDO5_CFG,
	MAX77826_REG_LDO6_CFG,
	MAX77826_REG_LDO7_CFG,
	MAX77826_REG_LDO8_CFG,
	MAX77826_REG_LDO9_CFG,
	MAX77826_REG_LDO10_CFG,
	MAX77826_REG_LDO11_CFG,
	MAX77826_REG_LDO12_CFG,
	MAX77826_REG_LDO13_CFG,
	MAX77826_REG_LDO14_CFG,
	MAX77826_REG_LDO15_CFG,
	/* 0x2F: Reserved */
	MAX77826_REG_BUCK_CFG = 0x30,
	MAX77826_REG_BUCK_VOUT,
	MAX77826_REG_BB_CFG,
	MAX77826_REG_BB_VOUT,
	/* 0x34 - 0x3F: Reserved */
	MAX77826_REG_BUCK_SS_FREQ = 0x40,
	MAX77826_REG_UVLO_FALL,
	/* 0x42 - 0xCE: Reserved */
	MAX77826_REG_DEVICE_ID = 0xCF,
पूर्ण;

क्रमागत max77826_regulators अणु
	MAX77826_LDO1 = 0,
	MAX77826_LDO2,
	MAX77826_LDO3,
	MAX77826_LDO4,
	MAX77826_LDO5,
	MAX77826_LDO6,
	MAX77826_LDO7,
	MAX77826_LDO8,
	MAX77826_LDO9,
	MAX77826_LDO10,
	MAX77826_LDO11,
	MAX77826_LDO12,
	MAX77826_LDO13,
	MAX77826_LDO14,
	MAX77826_LDO15,
	MAX77826_BUCK,
	MAX77826_BUCKBOOST,
	MAX77826_MAX_REGULATORS,
पूर्ण;

#घोषणा MAX77826_MASK_LDO		0x7f
#घोषणा MAX77826_MASK_BUCK		0xff
#घोषणा MAX77826_MASK_BUCKBOOST		0x7f
#घोषणा MAX77826_BUCK_RAMP_DELAY	12500

/* values in mV */
/* क्रम LDO1-3 */
#घोषणा MAX77826_NMOS_LDO_VOLT_MIN	600000
#घोषणा MAX77826_NMOS_LDO_VOLT_MAX	2187500
#घोषणा MAX77826_NMOS_LDO_VOLT_STEP	12500

/* क्रम LDO4-15 */
#घोषणा MAX77826_PMOS_LDO_VOLT_MIN	800000
#घोषणा MAX77826_PMOS_LDO_VOLT_MAX	3975000
#घोषणा MAX77826_PMOS_LDO_VOLT_STEP	25000

/* क्रम BUCK */
#घोषणा MAX77826_BUCK_VOLT_MIN		500000
#घोषणा MAX77826_BUCK_VOLT_MAX		1800000
#घोषणा MAX77826_BUCK_VOLT_STEP		6250

/* क्रम BUCKBOOST */
#घोषणा MAX77826_BUCKBOOST_VOLT_MIN	2600000
#घोषणा MAX77826_BUCKBOOST_VOLT_MAX	4187500
#घोषणा MAX77826_BUCKBOOST_VOLT_STEP	12500
#घोषणा MAX77826_VOLT_RANGE(_type)					\
	((MAX77826_ ## _type ## _VOLT_MAX -				\
	  MAX77826_ ## _type ## _VOLT_MIN) /				\
	 MAX77826_ ## _type ## _VOLT_STEP + 1)

#घोषणा MAX77826_LDO(_id, _type)					\
	[MAX77826_LDO ## _id] = अणु					\
		.id = MAX77826_LDO ## _id,				\
		.name = "LDO"#_id,					\
		.of_match = of_match_ptr("LDO"#_id),			\
		.regulators_node = "regulators",			\
		.ops = &max77826_most_ops,				\
		.min_uV = MAX77826_ ## _type ## _LDO_VOLT_MIN,		\
		.uV_step = MAX77826_ ## _type ## _LDO_VOLT_STEP,	\
		.n_voltages = MAX77826_VOLT_RANGE(_type ## _LDO),	\
		.enable_reg = MAX77826_REG_LDO_OPMD1 + (_id - 1) / 4,	\
		.enable_mask = BIT(((_id - 1) % 4) * 2 + 1),		\
		.vsel_reg = MAX77826_REG_LDO1_CFG + (_id - 1),		\
		.vsel_mask = MAX77826_MASK_LDO,				\
		.owner = THIS_MODULE,					\
	पूर्ण

#घोषणा MAX77826_BUCK(_idx, _id, _ops)					\
	[MAX77826_ ## _id] = अणु						\
		.id = MAX77826_ ## _id,					\
		.name = #_id,						\
		.of_match = of_match_ptr(#_id),				\
		.regulators_node = "regulators",			\
		.ops = &_ops,						\
		.min_uV =  MAX77826_ ## _id ## _VOLT_MIN,		\
		.uV_step = MAX77826_ ## _id ## _VOLT_STEP,		\
		.n_voltages = MAX77826_VOLT_RANGE(_id),			\
		.enable_reg = MAX77826_REG_B_BB_OPMD,			\
		.enable_mask = BIT(_idx * 2 + 1),			\
		.vsel_reg = MAX77826_REG_BUCK_VOUT + _idx * 2,		\
		.vsel_mask = MAX77826_MASK_ ## _id,			\
		.owner = THIS_MODULE,					\
	पूर्ण



काष्ठा max77826_regulator_info अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_desc *rdesc;
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77826_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MAX77826_REG_DEVICE_ID,
पूर्ण;

अटल पूर्णांक max77826_set_voltage_समय_sel(काष्ठा regulator_dev *,
				अचिन्हित पूर्णांक old_selector,
				अचिन्हित पूर्णांक new_selector);

अटल स्थिर काष्ठा regulator_ops max77826_most_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max77826_buck_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= max77826_set_voltage_समय_sel,
पूर्ण;

अटल काष्ठा regulator_desc max77826_regulators_desc[] = अणु
	MAX77826_LDO(1, NMOS),
	MAX77826_LDO(2, NMOS),
	MAX77826_LDO(3, NMOS),
	MAX77826_LDO(4, PMOS),
	MAX77826_LDO(5, PMOS),
	MAX77826_LDO(6, PMOS),
	MAX77826_LDO(7, PMOS),
	MAX77826_LDO(8, PMOS),
	MAX77826_LDO(9, PMOS),
	MAX77826_LDO(10, PMOS),
	MAX77826_LDO(11, PMOS),
	MAX77826_LDO(12, PMOS),
	MAX77826_LDO(13, PMOS),
	MAX77826_LDO(14, PMOS),
	MAX77826_LDO(15, PMOS),
	MAX77826_BUCK(0, BUCK, max77826_buck_ops),
	MAX77826_BUCK(1, BUCKBOOST, max77826_most_ops),
पूर्ण;

अटल पूर्णांक max77826_set_voltage_समय_sel(काष्ठा regulator_dev *rdev,
				अचिन्हित पूर्णांक old_selector,
				अचिन्हित पूर्णांक new_selector)
अणु
	अगर (new_selector > old_selector) अणु
		वापस DIV_ROUND_UP(MAX77826_BUCK_VOLT_STEP *
				(new_selector - old_selector),
				MAX77826_BUCK_RAMP_DELAY);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77826_पढ़ो_device_id(काष्ठा regmap *regmap, काष्ठा device *dev)
अणु
	अचिन्हित पूर्णांक device_id;
	पूर्णांक res;

	res = regmap_पढ़ो(regmap, MAX77826_REG_DEVICE_ID, &device_id);
	अगर (!res)
		dev_dbg(dev, "DEVICE_ID: 0x%x\n", device_id);

	वापस res;
पूर्ण

अटल पूर्णांक max77826_i2c_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा max77826_regulator_info *info;
	काष्ठा regulator_config config = अणुपूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *regmap;
	पूर्णांक i;

	info = devm_kzalloc(dev, माप(काष्ठा max77826_regulator_info),
				GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->rdesc = max77826_regulators_desc;
	regmap = devm_regmap_init_i2c(client, &max77826_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to allocate regmap!\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	info->regmap = regmap;
	i2c_set_clientdata(client, info);

	config.dev = dev;
	config.regmap = regmap;
	config.driver_data = info;

	क्रम (i = 0; i < MAX77826_MAX_REGULATORS; i++) अणु
		rdev = devm_regulator_रेजिस्टर(dev,
					       &max77826_regulators_desc[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(dev, "Failed to register regulator!\n");
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस max77826_पढ़ो_device_id(regmap, dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused max77826_of_match[] = अणु
	अणु .compatible = "maxim,max77826" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max77826_of_match);

अटल स्थिर काष्ठा i2c_device_id max77826_id[] = अणु
	अणु "max77826-regulator" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max77826_id);

अटल काष्ठा i2c_driver max77826_regulator_driver = अणु
	.driver = अणु
		.name = "max77826",
		.of_match_table = of_match_ptr(max77826_of_match),
	पूर्ण,
	.probe_new = max77826_i2c_probe,
	.id_table = max77826_id,
पूर्ण;
module_i2c_driver(max77826_regulator_driver);

MODULE_AUTHOR("Iskren Chernev <iskren.chernev@gmail.com>");
MODULE_DESCRIPTION("MAX77826 PMIC regulator driver");
MODULE_LICENSE("GPL");
