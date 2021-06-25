<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulators driver क्रम Marvell 88PM8607
 *
 * Copyright (C) 2009 Marvell International Ltd.
 *	Haojian Zhuang <haojian.zhuang@marvell.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mfd/88pm860x.h>
#समावेश <linux/module.h>

काष्ठा pm8607_regulator_info अणु
	काष्ठा regulator_desc	desc;

	अचिन्हित पूर्णांक	*vol_suspend;

	पूर्णांक	slope_द्विगुन;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक BUCK1_table[] = अणु
	 725000,  750000,  775000,  800000,  825000,  850000,  875000,  900000,
	 925000,  950000,  975000, 1000000, 1025000, 1050000, 1075000, 1100000,
	1125000, 1150000, 1175000, 1200000, 1225000, 1250000, 1275000, 1300000,
	1325000, 1350000, 1375000, 1400000, 1425000, 1450000, 1475000, 1500000,
	      0,   25000,   50000,   75000,  100000,  125000,  150000,  175000,
	 200000,  225000,  250000,  275000,  300000,  325000,  350000,  375000,
	 400000,  425000,  450000,  475000,  500000,  525000,  550000,  575000,
	 600000,  625000,  650000,  675000,  700000,  725000,  750000,  775000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक BUCK1_suspend_table[] = अणु
	      0,   25000,   50000,   75000,  100000,  125000,  150000,  175000,
	 200000,  225000,  250000,  275000,  300000,  325000,  350000,  375000,
	 400000,  425000,  450000,  475000,  500000,  525000,  550000,  575000,
	 600000,  625000,  650000,  675000,  700000,  725000,  750000,  775000,
	 800000,  825000,  850000,  875000,  900000,  925000,  950000,  975000,
	1000000, 1025000, 1050000, 1075000, 1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000, 1300000, 1325000, 1350000, 1375000,
	1400000, 1425000, 1450000, 1475000, 1500000, 1500000, 1500000, 1500000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक BUCK2_table[] = अणु
	      0,   50000,  100000,  150000,  200000,  250000,  300000,  350000,
	 400000,  450000,  500000,  550000,  600000,  650000,  700000,  750000,
	 800000,  850000,  900000,  950000, 1000000, 1050000, 1100000, 1150000,
	1200000, 1250000, 1300000, 1350000, 1400000, 1450000, 1500000, 1550000,
	1600000, 1650000, 1700000, 1750000, 1800000, 1850000, 1900000, 1950000,
	2000000, 2050000, 2100000, 2150000, 2200000, 2250000, 2300000, 2350000,
	2400000, 2450000, 2500000, 2550000, 2600000, 2650000, 2700000, 2750000,
	2800000, 2850000, 2900000, 2950000, 3000000, 3000000, 3000000, 3000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक BUCK2_suspend_table[] = अणु
	      0,   50000,  100000,  150000,  200000,  250000,  300000,  350000,
	 400000,  450000,  500000,  550000,  600000,  650000,  700000,  750000,
	 800000,  850000,  900000,  950000, 1000000, 1050000, 1100000, 1150000,
	1200000, 1250000, 1300000, 1350000, 1400000, 1450000, 1500000, 1550000,
	1600000, 1650000, 1700000, 1750000, 1800000, 1850000, 1900000, 1950000,
	2000000, 2050000, 2100000, 2150000, 2200000, 2250000, 2300000, 2350000,
	2400000, 2450000, 2500000, 2550000, 2600000, 2650000, 2700000, 2750000,
	2800000, 2850000, 2900000, 2950000, 3000000, 3000000, 3000000, 3000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक BUCK3_table[] = अणु
	      0,   25000,   50000,   75000,  100000,  125000,  150000,  175000,
	 200000,  225000,  250000,  275000,  300000,  325000,  350000,  375000,
	 400000,  425000,  450000,  475000,  500000,  525000,  550000,  575000,
	 600000,  625000,  650000,  675000,  700000,  725000,  750000,  775000,
	 800000,  825000,  850000,  875000,  900000,  925000,  950000,  975000,
	1000000, 1025000, 1050000, 1075000, 1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000, 1300000, 1325000, 1350000, 1375000,
	1400000, 1425000, 1450000, 1475000, 1500000, 1500000, 1500000, 1500000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक BUCK3_suspend_table[] = अणु
	      0,   25000,   50000,   75000,  100000,  125000,  150000,  175000,
	 200000,  225000,  250000,  275000,  300000,  325000,  350000,  375000,
	 400000,  425000,  450000,  475000,  500000,  525000,  550000,  575000,
	 600000,  625000,  650000,  675000,  700000,  725000,  750000,  775000,
	 800000,  825000,  850000,  875000,  900000,  925000,  950000,  975000,
	1000000, 1025000, 1050000, 1075000, 1100000, 1125000, 1150000, 1175000,
	1200000, 1225000, 1250000, 1275000, 1300000, 1325000, 1350000, 1375000,
	1400000, 1425000, 1450000, 1475000, 1500000, 1500000, 1500000, 1500000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO1_table[] = अणु
	1800000, 1200000, 2800000, 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO1_suspend_table[] = अणु
	1800000, 1200000, 0, 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO2_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO2_suspend_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO3_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO3_suspend_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO4_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2900000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO4_suspend_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2900000, 2900000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO5_table[] = अणु
	2900000, 3000000, 3100000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO5_suspend_table[] = अणु
	2900000, 0, 0, 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO6_table[] = अणु
	1800000, 1850000, 2600000, 2650000, 2700000, 2750000, 2800000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO6_suspend_table[] = अणु
	1800000, 1850000, 2600000, 2650000, 2700000, 2750000, 2800000, 2900000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO7_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO7_suspend_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO8_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO8_suspend_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO9_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO9_suspend_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO10_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 3300000,
	1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO10_suspend_table[] = अणु
	1800000, 1850000, 1900000, 2700000, 2750000, 2800000, 2850000, 2900000,
	1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO12_table[] = अणु
	1800000, 1900000, 2700000, 2800000, 2900000, 3000000, 3100000, 3300000,
	1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO12_suspend_table[] = अणु
	1800000, 1900000, 2700000, 2800000, 2900000, 2900000, 2900000, 2900000,
	1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000, 1200000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO13_table[] = अणु
	1200000, 1300000, 1800000, 2000000, 2500000, 2800000, 3000000, 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO13_suspend_table[] = अणु
	0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO14_table[] = अणु
	1800000, 1850000, 2700000, 2750000, 2800000, 2850000, 2900000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक LDO14_suspend_table[] = अणु
	1800000, 1850000, 2700000, 2750000, 2800000, 2850000, 2900000, 2900000,
पूर्ण;

अटल पूर्णांक pm8607_list_voltage(काष्ठा regulator_dev *rdev, अचिन्हित index)
अणु
	काष्ठा pm8607_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	ret = regulator_list_voltage_table(rdev, index);
	अगर (ret < 0)
		वापस ret;

	अगर (info->slope_द्विगुन)
		ret <<= 1;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops pm8607_regulator_ops = अणु
	.list_voltage	= pm8607_list_voltage,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pm8606_preg_ops = अणु
	.enable		= regulator_enable_regmap,
	.disable	= regulator_disable_regmap,
	.is_enabled	= regulator_is_enabled_regmap,
पूर्ण;

#घोषणा PM8606_PREG(ereg, ebit)						\
अणु									\
	.desc	= अणु							\
		.name	= "PREG",					\
		.of_match = of_match_ptr("PREG"),			\
		.regulators_node = of_match_ptr("regulators"),		\
		.ops	= &pm8606_preg_ops,				\
		.type	= REGULATOR_CURRENT,				\
		.id	= PM8606_ID_PREG,				\
		.owner	= THIS_MODULE,					\
		.enable_reg = PM8606_##ereg,				\
		.enable_mask = (ebit),					\
		.enable_is_inverted = true,				\
	पूर्ण,								\
पूर्ण

#घोषणा PM8607_DVC(vreg, ureg, ubit, ereg, ebit)			\
अणु									\
	.desc	= अणु							\
		.name	= #vreg,					\
		.of_match = of_match_ptr(#vreg),			\
		.regulators_node = of_match_ptr("regulators"),		\
		.ops	= &pm8607_regulator_ops,			\
		.type	= REGULATOR_VOLTAGE,				\
		.id	= PM8607_ID_##vreg,				\
		.owner	= THIS_MODULE,					\
		.volt_table = vreg##_table,				\
		.n_voltages = ARRAY_SIZE(vreg##_table),			\
		.vsel_reg = PM8607_##vreg,				\
		.vsel_mask = ARRAY_SIZE(vreg##_table) - 1,		\
		.apply_reg = PM8607_##ureg,				\
		.apply_bit = (ubit),					\
		.enable_reg = PM8607_##ereg,				\
		.enable_mask = 1 << (ebit),				\
	पूर्ण,								\
	.slope_द्विगुन	= (0),						\
	.vol_suspend	= (अचिन्हित पूर्णांक *)&vreg##_suspend_table,	\
पूर्ण

#घोषणा PM8607_LDO(_id, vreg, shअगरt, ereg, ebit)			\
अणु									\
	.desc	= अणु							\
		.name	= "LDO" #_id,					\
		.of_match = of_match_ptr("LDO" #_id),			\
		.regulators_node = of_match_ptr("regulators"),		\
		.ops	= &pm8607_regulator_ops,			\
		.type	= REGULATOR_VOLTAGE,				\
		.id	= PM8607_ID_LDO##_id,				\
		.owner	= THIS_MODULE,					\
		.volt_table = LDO##_id##_table,				\
		.n_voltages = ARRAY_SIZE(LDO##_id##_table),		\
		.vsel_reg = PM8607_##vreg,				\
		.vsel_mask = (ARRAY_SIZE(LDO##_id##_table) - 1) << (shअगरt), \
		.enable_reg = PM8607_##ereg,				\
		.enable_mask = 1 << (ebit),				\
	पूर्ण,								\
	.slope_द्विगुन	= (0),						\
	.vol_suspend	= (अचिन्हित पूर्णांक *)&LDO##_id##_suspend_table,	\
पूर्ण

अटल काष्ठा pm8607_regulator_info pm8607_regulator_info[] = अणु
	PM8607_DVC(BUCK1, GO, BIT(0), SUPPLIES_EN11, 0),
	PM8607_DVC(BUCK2, GO, BIT(1), SUPPLIES_EN11, 1),
	PM8607_DVC(BUCK3, GO, BIT(2), SUPPLIES_EN11, 2),

	PM8607_LDO(1,         LDO1, 0, SUPPLIES_EN11, 3),
	PM8607_LDO(2,         LDO2, 0, SUPPLIES_EN11, 4),
	PM8607_LDO(3,         LDO3, 0, SUPPLIES_EN11, 5),
	PM8607_LDO(4,         LDO4, 0, SUPPLIES_EN11, 6),
	PM8607_LDO(5,         LDO5, 0, SUPPLIES_EN11, 7),
	PM8607_LDO(6,         LDO6, 0, SUPPLIES_EN12, 0),
	PM8607_LDO(7,         LDO7, 0, SUPPLIES_EN12, 1),
	PM8607_LDO(8,         LDO8, 0, SUPPLIES_EN12, 2),
	PM8607_LDO(9,         LDO9, 0, SUPPLIES_EN12, 3),
	PM8607_LDO(10,        LDO10, 0, SUPPLIES_EN12, 4),
	PM8607_LDO(12,        LDO12, 0, SUPPLIES_EN12, 5),
	PM8607_LDO(13, VIBRATOR_SET, 1, VIBRATOR_SET, 0),
	PM8607_LDO(14,        LDO14, 0, SUPPLIES_EN12, 6),
पूर्ण;

अटल काष्ठा pm8607_regulator_info pm8606_regulator_info[] = अणु
	PM8606_PREG(PREREGULATORB, 5),
पूर्ण;

अटल पूर्णांक pm8607_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा pm8607_regulator_info *info = शून्य;
	काष्ठा regulator_init_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा resource *res;
	पूर्णांक i;

	res = platक्रमm_get_resource(pdev, IORESOURCE_REG, 0);
	अगर (res) अणु
		/* There're resources in 88PM8607 regulator driver */
		क्रम (i = 0; i < ARRAY_SIZE(pm8607_regulator_info); i++) अणु
			info = &pm8607_regulator_info[i];
			अगर (info->desc.vsel_reg == res->start)
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(pm8607_regulator_info)) अणु
			dev_err(&pdev->dev, "Failed to find regulator %llu\n",
				(अचिन्हित दीर्घ दीर्घ)res->start);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* There's no resource in 88PM8606 PREG regulator driver */
		info = &pm8606_regulator_info[0];
		/* i is used to check regulator ID */
		i = -1;
	पूर्ण

	/* check DVC ramp slope द्विगुन */
	अगर ((i == PM8607_ID_BUCK3) && chip->buck3_द्विगुन)
		info->slope_द्विगुन = 1;

	config.dev = chip->dev;
	config.driver_data = info;

	अगर (pdata)
		config.init_data = pdata;

	अगर (chip->id == CHIP_PM8607)
		config.regmap = chip->regmap;
	अन्यथा
		config.regmap = chip->regmap_companion;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &info->desc, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(&pdev->dev, "failed to register regulator %s\n",
			info->desc.name);
		वापस PTR_ERR(rdev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id pm8607_regulator_driver_ids[] = अणु
	अणु
		.name	= "88pm860x-regulator",
		.driver_data	= 0,
	पूर्ण, अणु
		.name	= "88pm860x-preg",
		.driver_data	= 0,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, pm8607_regulator_driver_ids);

अटल काष्ठा platक्रमm_driver pm8607_regulator_driver = अणु
	.driver		= अणु
		.name	= "88pm860x-regulator",
	पूर्ण,
	.probe		= pm8607_regulator_probe,
	.id_table	= pm8607_regulator_driver_ids,
पूर्ण;

अटल पूर्णांक __init pm8607_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pm8607_regulator_driver);
पूर्ण
subsys_initcall(pm8607_regulator_init);

अटल व्योम __निकास pm8607_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&pm8607_regulator_driver);
पूर्ण
module_निकास(pm8607_regulator_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_DESCRIPTION("Regulator Driver for Marvell 88PM8607 PMIC");
MODULE_ALIAS("platform:88pm8607-regulator");
