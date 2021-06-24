<शैली गुरु>
/*
 * tps65023-regulator.c
 *
 * Supports TPS65023 Regulator
 *
 * Copyright (C) 2009 Texas Instrument Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>

/* Register definitions */
#घोषणा	TPS65023_REG_VERSION		0
#घोषणा	TPS65023_REG_PGOODZ		1
#घोषणा	TPS65023_REG_MASK		2
#घोषणा	TPS65023_REG_REG_CTRL		3
#घोषणा	TPS65023_REG_CON_CTRL		4
#घोषणा	TPS65023_REG_CON_CTRL2		5
#घोषणा	TPS65023_REG_DEF_CORE		6
#घोषणा	TPS65023_REG_DEFSLEW		7
#घोषणा	TPS65023_REG_LDO_CTRL		8

/* PGOODZ bitfields */
#घोषणा	TPS65023_PGOODZ_PWRFAILZ	BIT(7)
#घोषणा	TPS65023_PGOODZ_LOWBATTZ	BIT(6)
#घोषणा	TPS65023_PGOODZ_VDCDC1		BIT(5)
#घोषणा	TPS65023_PGOODZ_VDCDC2		BIT(4)
#घोषणा	TPS65023_PGOODZ_VDCDC3		BIT(3)
#घोषणा	TPS65023_PGOODZ_LDO2		BIT(2)
#घोषणा	TPS65023_PGOODZ_LDO1		BIT(1)

/* MASK bitfields */
#घोषणा	TPS65023_MASK_PWRFAILZ		BIT(7)
#घोषणा	TPS65023_MASK_LOWBATTZ		BIT(6)
#घोषणा	TPS65023_MASK_VDCDC1		BIT(5)
#घोषणा	TPS65023_MASK_VDCDC2		BIT(4)
#घोषणा	TPS65023_MASK_VDCDC3		BIT(3)
#घोषणा	TPS65023_MASK_LDO2		BIT(2)
#घोषणा	TPS65023_MASK_LDO1		BIT(1)

/* REG_CTRL bitfields */
#घोषणा TPS65023_REG_CTRL_VDCDC1_EN	BIT(5)
#घोषणा TPS65023_REG_CTRL_VDCDC2_EN	BIT(4)
#घोषणा TPS65023_REG_CTRL_VDCDC3_EN	BIT(3)
#घोषणा TPS65023_REG_CTRL_LDO2_EN	BIT(2)
#घोषणा TPS65023_REG_CTRL_LDO1_EN	BIT(1)

/* REG_CTRL2 bitfields */
#घोषणा TPS65023_REG_CTRL2_GO		BIT(7)
#घोषणा TPS65023_REG_CTRL2_CORE_ADJ	BIT(6)
#घोषणा TPS65023_REG_CTRL2_DCDC2	BIT(2)
#घोषणा TPS65023_REG_CTRL2_DCDC1	BIT(1)
#घोषणा TPS65023_REG_CTRL2_DCDC3	BIT(0)

/* Number of step-करोwn converters available */
#घोषणा TPS65023_NUM_DCDC		3
/* Number of LDO voltage regulators  available */
#घोषणा TPS65023_NUM_LDO		2
/* Number of total regulators available */
#घोषणा TPS65023_NUM_REGULATOR	(TPS65023_NUM_DCDC + TPS65023_NUM_LDO)

/* DCDCs */
#घोषणा TPS65023_DCDC_1			0
#घोषणा TPS65023_DCDC_2			1
#घोषणा TPS65023_DCDC_3			2
/* LDOs */
#घोषणा TPS65023_LDO_1			3
#घोषणा TPS65023_LDO_2			4

#घोषणा TPS65023_MAX_REG_ID		TPS65023_LDO_2

#घोषणा TPS65023_REGULATOR_DCDC(_num, _t, _em)			\
	अणु							\
		.name		= "VDCDC"#_num,			\
		.of_match	= of_match_ptr("VDCDC"#_num),	\
		.regulators_node = of_match_ptr("regulators"),	\
		.id		= TPS65023_DCDC_##_num,		\
		.n_voltages     = ARRAY_SIZE(_t),		\
		.ops		= &tps65023_dcdc_ops,		\
		.type		= REGULATOR_VOLTAGE,		\
		.owner		= THIS_MODULE,			\
		.volt_table	= _t,				\
		.vsel_reg	= TPS65023_REG_DEF_CORE,	\
		.vsel_mask	= ARRAY_SIZE(_t) - 1,		\
		.enable_mask	= _em,				\
		.enable_reg	= TPS65023_REG_REG_CTRL,	\
		.apply_reg	= TPS65023_REG_CON_CTRL2,	\
		.apply_bit	= TPS65023_REG_CTRL2_GO,	\
	पूर्ण							\

#घोषणा TPS65023_REGULATOR_LDO(_num, _t, _vm)			\
	अणु							\
		.name		= "LDO"#_num,			\
		.of_match	= of_match_ptr("LDO"#_num),	\
		.regulators_node = of_match_ptr("regulators"),	\
		.id		= TPS65023_LDO_##_num,		\
		.n_voltages     = ARRAY_SIZE(_t),		\
		.ops		= &tps65023_lकरो_ops,		\
		.type		= REGULATOR_VOLTAGE,		\
		.owner		= THIS_MODULE,			\
		.volt_table	= _t,				\
		.vsel_reg	= TPS65023_REG_LDO_CTRL,	\
		.vsel_mask	= _vm,				\
		.enable_mask	= 1 << (_num),			\
		.enable_reg	= TPS65023_REG_REG_CTRL,	\
	पूर्ण							\

/* Supported voltage values क्रम regulators */
अटल स्थिर अचिन्हित पूर्णांक VCORE_VSEL_table[] = अणु
	800000, 825000, 850000, 875000,
	900000, 925000, 950000, 975000,
	1000000, 1025000, 1050000, 1075000,
	1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000,
	1300000, 1325000, 1350000, 1375000,
	1400000, 1425000, 1450000, 1475000,
	1500000, 1525000, 1550000, 1600000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक DCDC_FIXED_3300000_VSEL_table[] = अणु
	3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक DCDC_FIXED_1800000_VSEL_table[] = अणु
	1800000,
पूर्ण;

/* Supported voltage values क्रम LDO regulators क्रम tps65020 */
अटल स्थिर अचिन्हित पूर्णांक TPS65020_LDO_VSEL_table[] = अणु
	1000000, 1050000, 1100000, 1300000,
	1800000, 2500000, 3000000, 3300000,
पूर्ण;

/* Supported voltage values क्रम LDO regulators
 * क्रम tps65021 and tps65023 */
अटल स्थिर अचिन्हित पूर्णांक TPS65023_LDO1_VSEL_table[] = अणु
	1000000, 1100000, 1300000, 1800000,
	2200000, 2600000, 2800000, 3150000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक TPS65023_LDO2_VSEL_table[] = अणु
	1050000, 1200000, 1300000, 1800000,
	2500000, 2800000, 3000000, 3300000,
पूर्ण;

/* PMIC details */
काष्ठा tps_pmic अणु
	काष्ठा regulator_dev *rdev[TPS65023_NUM_REGULATOR];
	स्थिर काष्ठा tps_driver_data *driver_data;
	काष्ठा regmap *regmap;
पूर्ण;

/* Struct passed as driver data */
काष्ठा tps_driver_data अणु
	स्थिर काष्ठा regulator_desc *desc;
	u8 core_regulator;
पूर्ण;

अटल पूर्णांक tps65023_dcdc_get_voltage_sel(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps_pmic *tps = rdev_get_drvdata(dev);
	पूर्णांक dcdc = rdev_get_id(dev);

	अगर (dcdc < TPS65023_DCDC_1 || dcdc > TPS65023_DCDC_3)
		वापस -EINVAL;

	अगर (dcdc != tps->driver_data->core_regulator)
		वापस 0;

	वापस regulator_get_voltage_sel_regmap(dev);
पूर्ण

अटल पूर्णांक tps65023_dcdc_set_voltage_sel(काष्ठा regulator_dev *dev,
					 अचिन्हित selector)
अणु
	काष्ठा tps_pmic *tps = rdev_get_drvdata(dev);
	पूर्णांक dcdc = rdev_get_id(dev);

	अगर (dcdc != tps->driver_data->core_regulator)
		वापस -EINVAL;

	वापस regulator_set_voltage_sel_regmap(dev, selector);
पूर्ण

/* Operations permitted on VDCDCx */
अटल स्थिर काष्ठा regulator_ops tps65023_dcdc_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.get_voltage_sel = tps65023_dcdc_get_voltage_sel,
	.set_voltage_sel = tps65023_dcdc_set_voltage_sel,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
पूर्ण;

/* Operations permitted on LDOx */
अटल स्थिर काष्ठा regulator_ops tps65023_lकरो_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tps65023_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc tps65020_regulators[] = अणु
	TPS65023_REGULATOR_DCDC(1, DCDC_FIXED_3300000_VSEL_table, 0x20),
	TPS65023_REGULATOR_DCDC(2, DCDC_FIXED_1800000_VSEL_table, 0x10),
	TPS65023_REGULATOR_DCDC(3, VCORE_VSEL_table, 0x08),
	TPS65023_REGULATOR_LDO(1, TPS65020_LDO_VSEL_table, 0x07),
	TPS65023_REGULATOR_LDO(2, TPS65020_LDO_VSEL_table, 0x70),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc tps65021_regulators[] = अणु
	TPS65023_REGULATOR_DCDC(1, DCDC_FIXED_3300000_VSEL_table, 0x20),
	TPS65023_REGULATOR_DCDC(2, DCDC_FIXED_1800000_VSEL_table, 0x10),
	TPS65023_REGULATOR_DCDC(3, VCORE_VSEL_table, 0x08),
	TPS65023_REGULATOR_LDO(1, TPS65023_LDO1_VSEL_table, 0x07),
	TPS65023_REGULATOR_LDO(2, TPS65023_LDO2_VSEL_table, 0x70),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc tps65023_regulators[] = अणु
	TPS65023_REGULATOR_DCDC(1, VCORE_VSEL_table, 0x20),
	TPS65023_REGULATOR_DCDC(2, DCDC_FIXED_3300000_VSEL_table, 0x10),
	TPS65023_REGULATOR_DCDC(3, DCDC_FIXED_1800000_VSEL_table, 0x08),
	TPS65023_REGULATOR_LDO(1, TPS65023_LDO1_VSEL_table, 0x07),
	TPS65023_REGULATOR_LDO(2, TPS65023_LDO2_VSEL_table, 0x70),
पूर्ण;

अटल काष्ठा tps_driver_data tps65020_drv_data = अणु
	.desc = tps65020_regulators,
	.core_regulator = TPS65023_DCDC_3,
पूर्ण;

अटल काष्ठा tps_driver_data tps65021_drv_data = अणु
	.desc = tps65021_regulators,
	.core_regulator = TPS65023_DCDC_3,
पूर्ण;

अटल काष्ठा tps_driver_data tps65023_drv_data = अणु
	.desc = tps65023_regulators,
	.core_regulator = TPS65023_DCDC_1,
पूर्ण;

अटल पूर्णांक tps_65023_probe(काष्ठा i2c_client *client,
				     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regulator_init_data *init_data = dev_get_platdata(&client->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा tps_pmic *tps;
	पूर्णांक i;
	पूर्णांक error;

	tps = devm_kzalloc(&client->dev, माप(*tps), GFP_KERNEL);
	अगर (!tps)
		वापस -ENOMEM;

	tps->driver_data = (काष्ठा tps_driver_data *)id->driver_data;

	tps->regmap = devm_regmap_init_i2c(client, &tps65023_regmap_config);
	अगर (IS_ERR(tps->regmap)) अणु
		error = PTR_ERR(tps->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			error);
		वापस error;
	पूर्ण

	/* common क्रम all regulators */
	config.dev = &client->dev;
	config.driver_data = tps;
	config.regmap = tps->regmap;

	क्रम (i = 0; i < TPS65023_NUM_REGULATOR; i++) अणु
		अगर (init_data)
			config.init_data = &init_data[i];

		/* Register the regulators */
		tps->rdev[i] = devm_regulator_रेजिस्टर(&client->dev,
					&tps->driver_data->desc[i], &config);
		अगर (IS_ERR(tps->rdev[i])) अणु
			dev_err(&client->dev, "failed to register %s\n",
				id->name);
			वापस PTR_ERR(tps->rdev[i]);
		पूर्ण
	पूर्ण

	i2c_set_clientdata(client, tps);

	/* Enable setting output voltage by I2C */
	regmap_update_bits(tps->regmap, TPS65023_REG_CON_CTRL2,
			   TPS65023_REG_CTRL2_CORE_ADJ, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused tps65023_of_match[] = अणु
	अणु .compatible = "ti,tps65020", .data = &tps65020_drv_dataपूर्ण,
	अणु .compatible = "ti,tps65021", .data = &tps65021_drv_dataपूर्ण,
	अणु .compatible = "ti,tps65023", .data = &tps65023_drv_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tps65023_of_match);

अटल स्थिर काष्ठा i2c_device_id tps_65023_id[] = अणु
	अणु
		.name = "tps65023",
		.driver_data = (kernel_uदीर्घ_t)&tps65023_drv_data
	पूर्ण, अणु
		.name = "tps65021",
		.driver_data = (kernel_uदीर्घ_t)&tps65021_drv_data
	पूर्ण, अणु
		.name = "tps65020",
		.driver_data = (kernel_uदीर्घ_t)&tps65020_drv_data
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tps_65023_id);

अटल काष्ठा i2c_driver tps_65023_i2c_driver = अणु
	.driver = अणु
		.name = "tps65023",
		.of_match_table = of_match_ptr(tps65023_of_match),
	पूर्ण,
	.probe = tps_65023_probe,
	.id_table = tps_65023_id,
पूर्ण;

अटल पूर्णांक __init tps_65023_init(व्योम)
अणु
	वापस i2c_add_driver(&tps_65023_i2c_driver);
पूर्ण
subsys_initcall(tps_65023_init);

अटल व्योम __निकास tps_65023_cleanup(व्योम)
अणु
	i2c_del_driver(&tps_65023_i2c_driver);
पूर्ण
module_निकास(tps_65023_cleanup);

MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("TPS65023 voltage regulator driver");
MODULE_LICENSE("GPL v2");
