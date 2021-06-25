<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulators driver क्रम Marvell 88PM800
 *
 * Copyright (C) 2012 Marvell International Ltd.
 * Joseph(Yossi) Hanin <yhanin@marvell.com>
 * Yi Zhang <yizhang@marvell.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mfd/88pm80x.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/regulator/of_regulator.h>

/* LDO1 with DVC[0..3] */
#घोषणा PM800_LDO1_VOUT		(0x08) /* VOUT1 */
#घोषणा PM800_LDO1_VOUT_2	(0x09)
#घोषणा PM800_LDO1_VOUT_3	(0x0A)
#घोषणा PM800_LDO2_VOUT		(0x0B)
#घोषणा PM800_LDO3_VOUT		(0x0C)
#घोषणा PM800_LDO4_VOUT		(0x0D)
#घोषणा PM800_LDO5_VOUT		(0x0E)
#घोषणा PM800_LDO6_VOUT		(0x0F)
#घोषणा PM800_LDO7_VOUT		(0x10)
#घोषणा PM800_LDO8_VOUT		(0x11)
#घोषणा PM800_LDO9_VOUT		(0x12)
#घोषणा PM800_LDO10_VOUT	(0x13)
#घोषणा PM800_LDO11_VOUT	(0x14)
#घोषणा PM800_LDO12_VOUT	(0x15)
#घोषणा PM800_LDO13_VOUT	(0x16)
#घोषणा PM800_LDO14_VOUT	(0x17)
#घोषणा PM800_LDO15_VOUT	(0x18)
#घोषणा PM800_LDO16_VOUT	(0x19)
#घोषणा PM800_LDO17_VOUT	(0x1A)
#घोषणा PM800_LDO18_VOUT	(0x1B)
#घोषणा PM800_LDO19_VOUT	(0x1C)

/* BUCK1 with DVC[0..3] */
#घोषणा PM800_BUCK1		(0x3C)
#घोषणा PM800_BUCK1_1		(0x3D)
#घोषणा PM800_BUCK1_2		(0x3E)
#घोषणा PM800_BUCK1_3		(0x3F)
#घोषणा PM800_BUCK2		(0x40)
#घोषणा PM800_BUCK3		(0x41)
#घोषणा PM800_BUCK4		(0x42)
#घोषणा PM800_BUCK4_1		(0x43)
#घोषणा PM800_BUCK4_2		(0x44)
#घोषणा PM800_BUCK4_3		(0x45)
#घोषणा PM800_BUCK5		(0x46)

#घोषणा PM800_BUCK_ENA		(0x50)
#घोषणा PM800_LDO_ENA1_1	(0x51)
#घोषणा PM800_LDO_ENA1_2	(0x52)
#घोषणा PM800_LDO_ENA1_3	(0x53)

#घोषणा PM800_LDO_ENA2_1	(0x56)
#घोषणा PM800_LDO_ENA2_2	(0x57)
#घोषणा PM800_LDO_ENA2_3	(0x58)

#घोषणा PM800_BUCK1_MISC1	(0x78)
#घोषणा PM800_BUCK3_MISC1	(0x7E)
#घोषणा PM800_BUCK4_MISC1	(0x81)
#घोषणा PM800_BUCK5_MISC1	(0x84)

काष्ठा pm800_regulator_info अणु
	काष्ठा regulator_desc desc;
	पूर्णांक max_ua;
पूर्ण;

/*
 * vreg - the buck regs string.
 * ereg - the string क्रम the enable रेजिस्टर.
 * ebit - the bit number in the enable रेजिस्टर.
 * amax - the current
 * Buck has 2 kinds of voltage steps. It is easy to find voltage by ranges,
 * not the स्थिरant voltage table.
 * n_volt - Number of available selectors
 */
#घोषणा PM800_BUCK(match, vreg, ereg, ebit, amax, volt_ranges, n_volt)	\
अणु									\
	.desc	= अणु							\
		.name			= #vreg,			\
		.of_match		= of_match_ptr(#match),		\
		.regulators_node	= of_match_ptr("regulators"),	\
		.ops			= &pm800_volt_range_ops,	\
		.type			= REGULATOR_VOLTAGE,		\
		.id			= PM800_ID_##vreg,		\
		.owner			= THIS_MODULE,			\
		.n_voltages		= n_volt,			\
		.linear_ranges		= volt_ranges,			\
		.n_linear_ranges	= ARRAY_SIZE(volt_ranges),	\
		.vsel_reg		= PM800_##vreg,			\
		.vsel_mask		= 0x7f,				\
		.enable_reg		= PM800_##ereg,			\
		.enable_mask		= 1 << (ebit),			\
	पूर्ण,								\
	.max_ua	= (amax),						\
पूर्ण

/*
 * vreg - the LDO regs string
 * ereg -  the string क्रम the enable रेजिस्टर.
 * ebit - the bit number in the enable रेजिस्टर.
 * amax - the current
 * volt_table - the LDO voltage table
 * For all the LDOes, there are too many ranges. Using volt_table will be
 * simpler and faster.
 */
#घोषणा PM800_LDO(match, vreg, ereg, ebit, amax, lकरो_volt_table)	\
अणु									\
	.desc	= अणु							\
		.name			= #vreg,			\
		.of_match		= of_match_ptr(#match),		\
		.regulators_node	= of_match_ptr("regulators"),	\
		.ops			= &pm800_volt_table_ops,	\
		.type			= REGULATOR_VOLTAGE,		\
		.id			= PM800_ID_##vreg,		\
		.owner			= THIS_MODULE,			\
		.n_voltages		= ARRAY_SIZE(lकरो_volt_table),	\
		.vsel_reg		= PM800_##vreg##_VOUT,		\
		.vsel_mask		= 0xf,				\
		.enable_reg		= PM800_##ereg,			\
		.enable_mask		= 1 << (ebit),			\
		.volt_table		= lकरो_volt_table,		\
	पूर्ण,								\
	.max_ua	= (amax),						\
पूर्ण

/* Ranges are sorted in ascending order. */
अटल स्थिर काष्ठा linear_range buck1_volt_range[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0, 0x4f, 12500),
	REGULATOR_LINEAR_RANGE(1600000, 0x50, 0x54, 50000),
पूर्ण;

/* BUCK 2~5 have same ranges. */
अटल स्थिर काष्ठा linear_range buck2_5_volt_range[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0, 0x4f, 12500),
	REGULATOR_LINEAR_RANGE(1600000, 0x50, 0x72, 50000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो1_volt_table[] = अणु
	600000,  650000,  700000,  750000,  800000,  850000,  900000,  950000,
	1000000, 1050000, 1100000, 1150000, 1200000, 1300000, 1400000, 1500000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो2_volt_table[] = अणु
	1700000, 1800000, 1900000, 2000000, 2100000, 2500000, 2700000, 2800000,
पूर्ण;

/* LDO 3~17 have same voltage table. */
अटल स्थिर अचिन्हित पूर्णांक lकरो3_17_volt_table[] = अणु
	1200000, 1250000, 1700000, 1800000, 1850000, 1900000, 2500000, 2600000,
	2700000, 2750000, 2800000, 2850000, 2900000, 3000000, 3100000, 3300000,
पूर्ण;

/* LDO 18~19 have same voltage table. */
अटल स्थिर अचिन्हित पूर्णांक lकरो18_19_volt_table[] = अणु
	1700000, 1800000, 1900000, 2500000, 2800000, 2900000, 3100000, 3300000,
पूर्ण;

अटल पूर्णांक pm800_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pm800_regulator_info *info = rdev_get_drvdata(rdev);

	वापस info->max_ua;
पूर्ण

अटल स्थिर काष्ठा regulator_ops pm800_volt_range_ops = अणु
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.get_current_limit	= pm800_get_current_limit,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pm800_volt_table_ops = अणु
	.list_voltage		= regulator_list_voltage_table,
	.map_voltage		= regulator_map_voltage_iterate,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.get_current_limit	= pm800_get_current_limit,
पूर्ण;

/* The array is indexed by id(PM800_ID_XXX) */
अटल काष्ठा pm800_regulator_info pm800_regulator_info[] = अणु
	PM800_BUCK(buck1, BUCK1, BUCK_ENA, 0, 3000000, buck1_volt_range, 0x55),
	PM800_BUCK(buck2, BUCK2, BUCK_ENA, 1, 1200000, buck2_5_volt_range, 0x73),
	PM800_BUCK(buck3, BUCK3, BUCK_ENA, 2, 1200000, buck2_5_volt_range, 0x73),
	PM800_BUCK(buck4, BUCK4, BUCK_ENA, 3, 1200000, buck2_5_volt_range, 0x73),
	PM800_BUCK(buck5, BUCK5, BUCK_ENA, 4, 1200000, buck2_5_volt_range, 0x73),

	PM800_LDO(lकरो1, LDO1, LDO_ENA1_1, 0, 200000, lकरो1_volt_table),
	PM800_LDO(lकरो2, LDO2, LDO_ENA1_1, 1, 10000, lकरो2_volt_table),
	PM800_LDO(lकरो3, LDO3, LDO_ENA1_1, 2, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो4, LDO4, LDO_ENA1_1, 3, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो5, LDO5, LDO_ENA1_1, 4, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो6, LDO6, LDO_ENA1_1, 5, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो7, LDO7, LDO_ENA1_1, 6, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो8, LDO8, LDO_ENA1_1, 7, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो9, LDO9, LDO_ENA1_2, 0, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो10, LDO10, LDO_ENA1_2, 1, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो11, LDO11, LDO_ENA1_2, 2, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो12, LDO12, LDO_ENA1_2, 3, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो13, LDO13, LDO_ENA1_2, 4, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो14, LDO14, LDO_ENA1_2, 5, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो15, LDO15, LDO_ENA1_2, 6, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो16, LDO16, LDO_ENA1_2, 7, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो17, LDO17, LDO_ENA1_3, 0, 300000, lकरो3_17_volt_table),
	PM800_LDO(lकरो18, LDO18, LDO_ENA1_3, 1, 200000, lकरो18_19_volt_table),
	PM800_LDO(lकरो19, LDO19, LDO_ENA1_3, 2, 200000, lकरो18_19_volt_table),
पूर्ण;

अटल पूर्णांक pm800_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm80x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा pm80x_platक्रमm_data *pdata = dev_get_platdata(pdev->dev.parent);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_init_data *init_data;
	पूर्णांक i, ret;

	अगर (pdata && pdata->num_regulators) अणु
		अचिन्हित पूर्णांक count = 0;

		/* Check whether num_regulator is valid. */
		क्रम (i = 0; i < ARRAY_SIZE(pdata->regulators); i++) अणु
			अगर (pdata->regulators[i])
				count++;
		पूर्ण
		अगर (count != pdata->num_regulators)
			वापस -EINVAL;
	पूर्ण

	config.dev = chip->dev;
	config.regmap = chip->subchip->regmap_घातer;
	क्रम (i = 0; i < PM800_ID_RG_MAX; i++) अणु
		काष्ठा regulator_dev *regulator;

		अगर (pdata && pdata->num_regulators) अणु
			init_data = pdata->regulators[i];
			अगर (!init_data)
				जारी;

			config.init_data = init_data;
		पूर्ण

		config.driver_data = &pm800_regulator_info[i];

		regulator = devm_regulator_रेजिस्टर(&pdev->dev,
				&pm800_regulator_info[i].desc, &config);
		अगर (IS_ERR(regulator)) अणु
			ret = PTR_ERR(regulator);
			dev_err(&pdev->dev, "Failed to register %s\n",
					pm800_regulator_info[i].desc.name);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pm800_regulator_driver = अणु
	.driver		= अणु
		.name	= "88pm80x-regulator",
	पूर्ण,
	.probe		= pm800_regulator_probe,
पूर्ण;

module_platक्रमm_driver(pm800_regulator_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joseph(Yossi) Hanin <yhanin@marvell.com>");
MODULE_DESCRIPTION("Regulator Driver for Marvell 88PM800 PMIC");
MODULE_ALIAS("platform:88pm800-regulator");
