<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LP8788 MFD - lकरो regulator driver
 *
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/mfd/lp8788.h>

/* रेजिस्टर address */
#घोषणा LP8788_EN_LDO_A			0x0D	/* DLDO 1 ~ 8 */
#घोषणा LP8788_EN_LDO_B			0x0E	/* DLDO 9 ~ 12, ALDO 1 ~ 4 */
#घोषणा LP8788_EN_LDO_C			0x0F	/* ALDO 5 ~ 10 */
#घोषणा LP8788_EN_SEL			0x10
#घोषणा LP8788_DLDO1_VOUT		0x2E
#घोषणा LP8788_DLDO2_VOUT		0x2F
#घोषणा LP8788_DLDO3_VOUT		0x30
#घोषणा LP8788_DLDO4_VOUT		0x31
#घोषणा LP8788_DLDO5_VOUT		0x32
#घोषणा LP8788_DLDO6_VOUT		0x33
#घोषणा LP8788_DLDO7_VOUT		0x34
#घोषणा LP8788_DLDO8_VOUT		0x35
#घोषणा LP8788_DLDO9_VOUT		0x36
#घोषणा LP8788_DLDO10_VOUT		0x37
#घोषणा LP8788_DLDO11_VOUT		0x38
#घोषणा LP8788_DLDO12_VOUT		0x39
#घोषणा LP8788_ALDO1_VOUT		0x3A
#घोषणा LP8788_ALDO2_VOUT		0x3B
#घोषणा LP8788_ALDO3_VOUT		0x3C
#घोषणा LP8788_ALDO4_VOUT		0x3D
#घोषणा LP8788_ALDO5_VOUT		0x3E
#घोषणा LP8788_ALDO6_VOUT		0x3F
#घोषणा LP8788_ALDO7_VOUT		0x40
#घोषणा LP8788_ALDO8_VOUT		0x41
#घोषणा LP8788_ALDO9_VOUT		0x42
#घोषणा LP8788_ALDO10_VOUT		0x43
#घोषणा LP8788_DLDO1_TIMESTEP		0x44

/* mask/shअगरt bits */
#घोषणा LP8788_EN_DLDO1_M		BIT(0)	/* Addr 0Dh ~ 0Fh */
#घोषणा LP8788_EN_DLDO2_M		BIT(1)
#घोषणा LP8788_EN_DLDO3_M		BIT(2)
#घोषणा LP8788_EN_DLDO4_M		BIT(3)
#घोषणा LP8788_EN_DLDO5_M		BIT(4)
#घोषणा LP8788_EN_DLDO6_M		BIT(5)
#घोषणा LP8788_EN_DLDO7_M		BIT(6)
#घोषणा LP8788_EN_DLDO8_M		BIT(7)
#घोषणा LP8788_EN_DLDO9_M		BIT(0)
#घोषणा LP8788_EN_DLDO10_M		BIT(1)
#घोषणा LP8788_EN_DLDO11_M		BIT(2)
#घोषणा LP8788_EN_DLDO12_M		BIT(3)
#घोषणा LP8788_EN_ALDO1_M		BIT(4)
#घोषणा LP8788_EN_ALDO2_M		BIT(5)
#घोषणा LP8788_EN_ALDO3_M		BIT(6)
#घोषणा LP8788_EN_ALDO4_M		BIT(7)
#घोषणा LP8788_EN_ALDO5_M		BIT(0)
#घोषणा LP8788_EN_ALDO6_M		BIT(1)
#घोषणा LP8788_EN_ALDO7_M		BIT(2)
#घोषणा LP8788_EN_ALDO8_M		BIT(3)
#घोषणा LP8788_EN_ALDO9_M		BIT(4)
#घोषणा LP8788_EN_ALDO10_M		BIT(5)
#घोषणा LP8788_EN_SEL_DLDO911_M		BIT(0)	/* Addr 10h */
#घोषणा LP8788_EN_SEL_DLDO7_M		BIT(1)
#घोषणा LP8788_EN_SEL_ALDO7_M		BIT(2)
#घोषणा LP8788_EN_SEL_ALDO5_M		BIT(3)
#घोषणा LP8788_EN_SEL_ALDO234_M		BIT(4)
#घोषणा LP8788_EN_SEL_ALDO1_M		BIT(5)
#घोषणा LP8788_VOUT_5BIT_M		0x1F	/* Addr 2Eh ~ 43h */
#घोषणा LP8788_VOUT_4BIT_M		0x0F
#घोषणा LP8788_VOUT_3BIT_M		0x07
#घोषणा LP8788_VOUT_1BIT_M		0x01
#घोषणा LP8788_STARTUP_TIME_M		0xF8	/* Addr 44h ~ 59h */
#घोषणा LP8788_STARTUP_TIME_S		3

#घोषणा ENABLE_TIME_USEC		32

क्रमागत lp8788_lकरो_id अणु
	DLDO1,
	DLDO2,
	DLDO3,
	DLDO4,
	DLDO5,
	DLDO6,
	DLDO7,
	DLDO8,
	DLDO9,
	DLDO10,
	DLDO11,
	DLDO12,
	ALDO1,
	ALDO2,
	ALDO3,
	ALDO4,
	ALDO5,
	ALDO6,
	ALDO7,
	ALDO8,
	ALDO9,
	ALDO10,
पूर्ण;

काष्ठा lp8788_lकरो अणु
	काष्ठा lp8788 *lp;
	काष्ठा regulator_desc *desc;
	काष्ठा regulator_dev *regulator;
	काष्ठा gpio_desc *ena_gpiod;
पूर्ण;

/* DLDO 1, 2, 3, 9 voltage table */
अटल स्थिर पूर्णांक lp8788_dlकरो1239_vtbl[] = अणु
	1800000, 1900000, 2000000, 2100000, 2200000, 2300000, 2400000, 2500000,
	2600000, 2700000, 2800000, 2900000, 3000000, 2850000, 2850000, 2850000,
	2850000, 2850000, 2850000, 2850000, 2850000, 2850000, 2850000, 2850000,
	2850000, 2850000, 2850000, 2850000, 2850000, 2850000, 2850000, 2850000,
पूर्ण;

/* DLDO 4 voltage table */
अटल स्थिर पूर्णांक lp8788_dlकरो4_vtbl[] = अणु 1800000, 3000000 पूर्ण;

/* DLDO 5, 7, 8 and ALDO 6 voltage table */
अटल स्थिर पूर्णांक lp8788_dlकरो578_alकरो6_vtbl[] = अणु
	1800000, 1900000, 2000000, 2100000, 2200000, 2300000, 2400000, 2500000,
	2600000, 2700000, 2800000, 2900000, 3000000, 3000000, 3000000, 3000000,
पूर्ण;

/* DLDO 6 voltage table */
अटल स्थिर पूर्णांक lp8788_dlकरो6_vtbl[] = अणु
	3000000, 3100000, 3200000, 3300000, 3400000, 3500000, 3600000, 3600000,
पूर्ण;

/* DLDO 10, 11 voltage table */
अटल स्थिर पूर्णांक lp8788_dlकरो1011_vtbl[] = अणु
	1100000, 1150000, 1200000, 1250000, 1300000, 1350000, 1400000, 1450000,
	1500000, 1500000, 1500000, 1500000, 1500000, 1500000, 1500000, 1500000,
पूर्ण;

/* ALDO 1 voltage table */
अटल स्थिर पूर्णांक lp8788_alकरो1_vtbl[] = अणु 1800000, 2850000 पूर्ण;

/* ALDO 7 voltage table */
अटल स्थिर पूर्णांक lp8788_alकरो7_vtbl[] = अणु
	1200000, 1300000, 1400000, 1500000, 1600000, 1700000, 1800000, 1800000,
पूर्ण;

अटल पूर्णांक lp8788_lकरो_enable_समय(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा lp8788_lकरो *lकरो = rdev_get_drvdata(rdev);
	क्रमागत lp8788_lकरो_id id = rdev_get_id(rdev);
	u8 val, addr = LP8788_DLDO1_TIMESTEP + id;

	अगर (lp8788_पढ़ो_byte(lकरो->lp, addr, &val))
		वापस -EINVAL;

	val = (val & LP8788_STARTUP_TIME_M) >> LP8788_STARTUP_TIME_S;

	वापस ENABLE_TIME_USEC * val;
पूर्ण

अटल स्थिर काष्ठा regulator_ops lp8788_lकरो_voltage_table_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.enable_समय = lp8788_lकरो_enable_समय,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops lp8788_lकरो_voltage_fixed_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.enable_समय = lp8788_lकरो_enable_समय,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc lp8788_dlकरो_desc[] = अणु
	अणु
		.name = "dldo1",
		.id = DLDO1,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_dlकरो1239_vtbl),
		.volt_table = lp8788_dlकरो1239_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_DLDO1_VOUT,
		.vsel_mask = LP8788_VOUT_5BIT_M,
		.enable_reg = LP8788_EN_LDO_A,
		.enable_mask = LP8788_EN_DLDO1_M,
	पूर्ण,
	अणु
		.name = "dldo2",
		.id = DLDO2,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_dlकरो1239_vtbl),
		.volt_table = lp8788_dlकरो1239_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_DLDO2_VOUT,
		.vsel_mask = LP8788_VOUT_5BIT_M,
		.enable_reg = LP8788_EN_LDO_A,
		.enable_mask = LP8788_EN_DLDO2_M,
	पूर्ण,
	अणु
		.name = "dldo3",
		.id = DLDO3,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_dlकरो1239_vtbl),
		.volt_table = lp8788_dlकरो1239_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_DLDO3_VOUT,
		.vsel_mask = LP8788_VOUT_5BIT_M,
		.enable_reg = LP8788_EN_LDO_A,
		.enable_mask = LP8788_EN_DLDO3_M,
	पूर्ण,
	अणु
		.name = "dldo4",
		.id = DLDO4,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_dlकरो4_vtbl),
		.volt_table = lp8788_dlकरो4_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_DLDO4_VOUT,
		.vsel_mask = LP8788_VOUT_1BIT_M,
		.enable_reg = LP8788_EN_LDO_A,
		.enable_mask = LP8788_EN_DLDO4_M,
	पूर्ण,
	अणु
		.name = "dldo5",
		.id = DLDO5,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_dlकरो578_alकरो6_vtbl),
		.volt_table = lp8788_dlकरो578_alकरो6_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_DLDO5_VOUT,
		.vsel_mask = LP8788_VOUT_4BIT_M,
		.enable_reg = LP8788_EN_LDO_A,
		.enable_mask = LP8788_EN_DLDO5_M,
	पूर्ण,
	अणु
		.name = "dldo6",
		.id = DLDO6,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_dlकरो6_vtbl),
		.volt_table = lp8788_dlकरो6_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_DLDO6_VOUT,
		.vsel_mask = LP8788_VOUT_3BIT_M,
		.enable_reg = LP8788_EN_LDO_A,
		.enable_mask = LP8788_EN_DLDO6_M,
	पूर्ण,
	अणु
		.name = "dldo7",
		.id = DLDO7,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_dlकरो578_alकरो6_vtbl),
		.volt_table = lp8788_dlकरो578_alकरो6_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_DLDO7_VOUT,
		.vsel_mask = LP8788_VOUT_4BIT_M,
		.enable_reg = LP8788_EN_LDO_A,
		.enable_mask = LP8788_EN_DLDO7_M,
	पूर्ण,
	अणु
		.name = "dldo8",
		.id = DLDO8,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_dlकरो578_alकरो6_vtbl),
		.volt_table = lp8788_dlकरो578_alकरो6_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_DLDO8_VOUT,
		.vsel_mask = LP8788_VOUT_4BIT_M,
		.enable_reg = LP8788_EN_LDO_A,
		.enable_mask = LP8788_EN_DLDO8_M,
	पूर्ण,
	अणु
		.name = "dldo9",
		.id = DLDO9,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_dlकरो1239_vtbl),
		.volt_table = lp8788_dlकरो1239_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_DLDO9_VOUT,
		.vsel_mask = LP8788_VOUT_5BIT_M,
		.enable_reg = LP8788_EN_LDO_B,
		.enable_mask = LP8788_EN_DLDO9_M,
	पूर्ण,
	अणु
		.name = "dldo10",
		.id = DLDO10,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_dlकरो1011_vtbl),
		.volt_table = lp8788_dlकरो1011_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_DLDO10_VOUT,
		.vsel_mask = LP8788_VOUT_4BIT_M,
		.enable_reg = LP8788_EN_LDO_B,
		.enable_mask = LP8788_EN_DLDO10_M,
	पूर्ण,
	अणु
		.name = "dldo11",
		.id = DLDO11,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_dlकरो1011_vtbl),
		.volt_table = lp8788_dlकरो1011_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_DLDO11_VOUT,
		.vsel_mask = LP8788_VOUT_4BIT_M,
		.enable_reg = LP8788_EN_LDO_B,
		.enable_mask = LP8788_EN_DLDO11_M,
	पूर्ण,
	अणु
		.name = "dldo12",
		.id = DLDO12,
		.ops = &lp8788_lकरो_voltage_fixed_ops,
		.n_voltages = 1,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP8788_EN_LDO_B,
		.enable_mask = LP8788_EN_DLDO12_M,
		.min_uV = 2500000,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc lp8788_alकरो_desc[] = अणु
	अणु
		.name = "aldo1",
		.id = ALDO1,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_alकरो1_vtbl),
		.volt_table = lp8788_alकरो1_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_ALDO1_VOUT,
		.vsel_mask = LP8788_VOUT_1BIT_M,
		.enable_reg = LP8788_EN_LDO_B,
		.enable_mask = LP8788_EN_ALDO1_M,
	पूर्ण,
	अणु
		.name = "aldo2",
		.id = ALDO2,
		.ops = &lp8788_lकरो_voltage_fixed_ops,
		.n_voltages = 1,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP8788_EN_LDO_B,
		.enable_mask = LP8788_EN_ALDO2_M,
		.min_uV = 2850000,
	पूर्ण,
	अणु
		.name = "aldo3",
		.id = ALDO3,
		.ops = &lp8788_lकरो_voltage_fixed_ops,
		.n_voltages = 1,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP8788_EN_LDO_B,
		.enable_mask = LP8788_EN_ALDO3_M,
		.min_uV = 2850000,
	पूर्ण,
	अणु
		.name = "aldo4",
		.id = ALDO4,
		.ops = &lp8788_lकरो_voltage_fixed_ops,
		.n_voltages = 1,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP8788_EN_LDO_B,
		.enable_mask = LP8788_EN_ALDO4_M,
		.min_uV = 2850000,
	पूर्ण,
	अणु
		.name = "aldo5",
		.id = ALDO5,
		.ops = &lp8788_lकरो_voltage_fixed_ops,
		.n_voltages = 1,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP8788_EN_LDO_C,
		.enable_mask = LP8788_EN_ALDO5_M,
		.min_uV = 2850000,
	पूर्ण,
	अणु
		.name = "aldo6",
		.id = ALDO6,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_dlकरो578_alकरो6_vtbl),
		.volt_table = lp8788_dlकरो578_alकरो6_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_ALDO6_VOUT,
		.vsel_mask = LP8788_VOUT_4BIT_M,
		.enable_reg = LP8788_EN_LDO_C,
		.enable_mask = LP8788_EN_ALDO6_M,
	पूर्ण,
	अणु
		.name = "aldo7",
		.id = ALDO7,
		.ops = &lp8788_lकरो_voltage_table_ops,
		.n_voltages = ARRAY_SIZE(lp8788_alकरो7_vtbl),
		.volt_table = lp8788_alकरो7_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8788_ALDO7_VOUT,
		.vsel_mask = LP8788_VOUT_3BIT_M,
		.enable_reg = LP8788_EN_LDO_C,
		.enable_mask = LP8788_EN_ALDO7_M,
	पूर्ण,
	अणु
		.name = "aldo8",
		.id = ALDO8,
		.ops = &lp8788_lकरो_voltage_fixed_ops,
		.n_voltages = 1,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP8788_EN_LDO_C,
		.enable_mask = LP8788_EN_ALDO8_M,
		.min_uV = 2500000,
	पूर्ण,
	अणु
		.name = "aldo9",
		.id = ALDO9,
		.ops = &lp8788_lकरो_voltage_fixed_ops,
		.n_voltages = 1,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP8788_EN_LDO_C,
		.enable_mask = LP8788_EN_ALDO9_M,
		.min_uV = 2500000,
	पूर्ण,
	अणु
		.name = "aldo10",
		.id = ALDO10,
		.ops = &lp8788_lकरो_voltage_fixed_ops,
		.n_voltages = 1,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP8788_EN_LDO_C,
		.enable_mask = LP8788_EN_ALDO10_M,
		.min_uV = 1100000,
	पूर्ण,
पूर्ण;

अटल पूर्णांक lp8788_config_lकरो_enable_mode(काष्ठा platक्रमm_device *pdev,
					काष्ठा lp8788_lकरो *lकरो,
					क्रमागत lp8788_lकरो_id id)
अणु
	काष्ठा lp8788 *lp = lकरो->lp;
	क्रमागत lp8788_ext_lकरो_en_id enable_id;
	अटल स्थिर u8 en_mask[] = अणु
		[EN_ALDO1]   = LP8788_EN_SEL_ALDO1_M,
		[EN_ALDO234] = LP8788_EN_SEL_ALDO234_M,
		[EN_ALDO5]   = LP8788_EN_SEL_ALDO5_M,
		[EN_ALDO7]   = LP8788_EN_SEL_ALDO7_M,
		[EN_DLDO7]   = LP8788_EN_SEL_DLDO7_M,
		[EN_DLDO911] = LP8788_EN_SEL_DLDO911_M,
	पूर्ण;

	चयन (id) अणु
	हाल DLDO7:
		enable_id = EN_DLDO7;
		अवरोध;
	हाल DLDO9:
	हाल DLDO11:
		enable_id = EN_DLDO911;
		अवरोध;
	हाल ALDO1:
		enable_id = EN_ALDO1;
		अवरोध;
	हाल ALDO2 ... ALDO4:
		enable_id = EN_ALDO234;
		अवरोध;
	हाल ALDO5:
		enable_id = EN_ALDO5;
		अवरोध;
	हाल ALDO7:
		enable_id = EN_ALDO7;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	/*
	 * Do not use devm* here: the regulator core takes over the
	 * lअगरecycle management of the GPIO descriptor.
	 * FIXME: check शेष mode क्रम GPIO here: high or low?
	 */
	lकरो->ena_gpiod = gpiod_get_index_optional(&pdev->dev,
					       "enable",
					       enable_id,
					       GPIOD_OUT_HIGH |
					       GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	अगर (IS_ERR(lकरो->ena_gpiod))
		वापस PTR_ERR(lकरो->ena_gpiod);

	/* अगर no GPIO क्रम lकरो pin, then set शेष enable mode */
	अगर (!lकरो->ena_gpiod)
		जाओ set_शेष_lकरो_enable_mode;

	वापस 0;

set_शेष_lकरो_enable_mode:
	वापस lp8788_update_bits(lp, LP8788_EN_SEL, en_mask[enable_id], 0);
पूर्ण

अटल पूर्णांक lp8788_dlकरो_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक id = pdev->id;
	काष्ठा lp8788_lकरो *lकरो;
	काष्ठा regulator_config cfg = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक ret;

	lकरो = devm_kzalloc(&pdev->dev, माप(काष्ठा lp8788_lकरो), GFP_KERNEL);
	अगर (!lकरो)
		वापस -ENOMEM;

	lकरो->lp = lp;
	ret = lp8788_config_lकरो_enable_mode(pdev, lकरो, id);
	अगर (ret)
		वापस ret;

	अगर (lकरो->ena_gpiod)
		cfg.ena_gpiod = lकरो->ena_gpiod;

	cfg.dev = pdev->dev.parent;
	cfg.init_data = lp->pdata ? lp->pdata->dlकरो_data[id] : शून्य;
	cfg.driver_data = lकरो;
	cfg.regmap = lp->regmap;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &lp8788_dlकरो_desc[id], &cfg);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(&pdev->dev, "DLDO%d regulator register err = %d\n",
				id + 1, ret);
		वापस ret;
	पूर्ण

	lकरो->regulator = rdev;
	platक्रमm_set_drvdata(pdev, lकरो);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lp8788_dlकरो_driver = अणु
	.probe = lp8788_dlकरो_probe,
	.driver = अणु
		.name = LP8788_DEV_DLDO,
	पूर्ण,
पूर्ण;

अटल पूर्णांक lp8788_alकरो_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक id = pdev->id;
	काष्ठा lp8788_lकरो *lकरो;
	काष्ठा regulator_config cfg = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक ret;

	lकरो = devm_kzalloc(&pdev->dev, माप(काष्ठा lp8788_lकरो), GFP_KERNEL);
	अगर (!lकरो)
		वापस -ENOMEM;

	lकरो->lp = lp;
	ret = lp8788_config_lकरो_enable_mode(pdev, lकरो, id + ALDO1);
	अगर (ret)
		वापस ret;

	अगर (lकरो->ena_gpiod)
		cfg.ena_gpiod = lकरो->ena_gpiod;

	cfg.dev = pdev->dev.parent;
	cfg.init_data = lp->pdata ? lp->pdata->alकरो_data[id] : शून्य;
	cfg.driver_data = lकरो;
	cfg.regmap = lp->regmap;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &lp8788_alकरो_desc[id], &cfg);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(&pdev->dev, "ALDO%d regulator register err = %d\n",
				id + 1, ret);
		वापस ret;
	पूर्ण

	lकरो->regulator = rdev;
	platक्रमm_set_drvdata(pdev, lकरो);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lp8788_alकरो_driver = अणु
	.probe = lp8788_alकरो_probe,
	.driver = अणु
		.name = LP8788_DEV_ALDO,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&lp8788_dlकरो_driver,
	&lp8788_alकरो_driver,
पूर्ण;

अटल पूर्णांक __init lp8788_lकरो_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
subsys_initcall(lp8788_lकरो_init);

अटल व्योम __निकास lp8788_lकरो_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_निकास(lp8788_lकरो_निकास);

MODULE_DESCRIPTION("TI LP8788 LDO Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lp8788-dldo");
MODULE_ALIAS("platform:lp8788-aldo");
