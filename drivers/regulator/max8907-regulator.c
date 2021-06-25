<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max8907-regulator.c -- support regulators in max8907
 *
 * Copyright (C) 2010 Gyungoh Yoo <jack.yoo@maxim-ic.com>
 * Copyright (C) 2010-2012, NVIDIA CORPORATION. All rights reserved.
 *
 * Portions based on drivers/regulator/tps65910-regulator.c,
 *     Copyright 2010 Texas Instruments Inc.
 *     Author: Graeme Gregory <gg@slimlogic.co.uk>
 *     Author: Jorge Eduarकरो Candelaria <jedu@slimlogic.co.uk>
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/max8907.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा MAX8907_II2RR_VERSION_MASK	0xF0
#घोषणा MAX8907_II2RR_VERSION_REV_A	0x00
#घोषणा MAX8907_II2RR_VERSION_REV_B	0x10
#घोषणा MAX8907_II2RR_VERSION_REV_C	0x30

काष्ठा max8907_regulator अणु
	काष्ठा regulator_desc desc[MAX8907_NUM_REGULATORS];
पूर्ण;

#घोषणा REG_MBATT() \
	[MAX8907_MBATT] = अणु \
		.name = "MBATT", \
		.supply_name = "mbatt", \
		.id = MAX8907_MBATT, \
		.ops = &max8907_mbatt_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
	पूर्ण

#घोषणा REG_LDO(ids, supply, base, min, max, step) \
	[MAX8907_##ids] = अणु \
		.name = #ids, \
		.supply_name = supply, \
		.id = MAX8907_##ids, \
		.n_voltages = ((max) - (min)) / (step) + 1, \
		.ops = &max8907_lकरो_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
		.min_uV = (min), \
		.uV_step = (step), \
		.vsel_reg = (base) + MAX8907_VOUT, \
		.vsel_mask = 0x3f, \
		.enable_reg = (base) + MAX8907_CTL, \
		.enable_mask = MAX8907_MASK_LDO_EN, \
	पूर्ण

#घोषणा REG_FIXED(ids, supply, voltage) \
	[MAX8907_##ids] = अणु \
		.name = #ids, \
		.supply_name = supply, \
		.id = MAX8907_##ids, \
		.n_voltages = 1, \
		.ops = &max8907_fixed_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
		.min_uV = (voltage), \
	पूर्ण

#घोषणा REG_OUT5V(ids, supply, base, voltage) \
	[MAX8907_##ids] = अणु \
		.name = #ids, \
		.supply_name = supply, \
		.id = MAX8907_##ids, \
		.n_voltages = 1, \
		.ops = &max8907_out5v_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
		.min_uV = (voltage), \
		.enable_reg = (base), \
		.enable_mask = MAX8907_MASK_OUT5V_EN, \
	पूर्ण

#घोषणा REG_BBAT(ids, supply, base, min, max, step) \
	[MAX8907_##ids] = अणु \
		.name = #ids, \
		.supply_name = supply, \
		.id = MAX8907_##ids, \
		.n_voltages = ((max) - (min)) / (step) + 1, \
		.ops = &max8907_bbat_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
		.min_uV = (min), \
		.uV_step = (step), \
		.vsel_reg = (base), \
		.vsel_mask = MAX8907_MASK_VBBATTCV, \
	पूर्ण

#घोषणा LDO_750_50(id, supply, base) REG_LDO(id, supply, (base), \
			750000, 3900000, 50000)
#घोषणा LDO_650_25(id, supply, base) REG_LDO(id, supply, (base), \
			650000, 2225000, 25000)

अटल स्थिर काष्ठा regulator_ops max8907_mbatt_ops = अणु
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8907_lकरो_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8907_lकरो_hwctl_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8907_fixed_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8907_out5v_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8907_out5v_hwctl_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8907_bbat_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc max8907_regulators[] = अणु
	REG_MBATT(),
	REG_LDO(SD1, "in-v1", MAX8907_REG_SDCTL1, 650000, 2225000, 25000),
	REG_LDO(SD2, "in-v2", MAX8907_REG_SDCTL2, 637500, 1425000, 12500),
	REG_LDO(SD3, "in-v3", MAX8907_REG_SDCTL3, 750000, 3900000, 50000),
	LDO_750_50(LDO1, "in1", MAX8907_REG_LDOCTL1),
	LDO_650_25(LDO2, "in2", MAX8907_REG_LDOCTL2),
	LDO_650_25(LDO3, "in3", MAX8907_REG_LDOCTL3),
	LDO_750_50(LDO4, "in4", MAX8907_REG_LDOCTL4),
	LDO_750_50(LDO5, "in5", MAX8907_REG_LDOCTL5),
	LDO_750_50(LDO6, "in6", MAX8907_REG_LDOCTL6),
	LDO_750_50(LDO7, "in7", MAX8907_REG_LDOCTL7),
	LDO_750_50(LDO8, "in8", MAX8907_REG_LDOCTL8),
	LDO_750_50(LDO9, "in9", MAX8907_REG_LDOCTL9),
	LDO_750_50(LDO10, "in10", MAX8907_REG_LDOCTL10),
	LDO_750_50(LDO11, "in11", MAX8907_REG_LDOCTL11),
	LDO_750_50(LDO12, "in12", MAX8907_REG_LDOCTL12),
	LDO_750_50(LDO13, "in13", MAX8907_REG_LDOCTL13),
	LDO_750_50(LDO14, "in14", MAX8907_REG_LDOCTL14),
	LDO_750_50(LDO15, "in15", MAX8907_REG_LDOCTL15),
	LDO_750_50(LDO16, "in16", MAX8907_REG_LDOCTL16),
	LDO_650_25(LDO17, "in17", MAX8907_REG_LDOCTL17),
	LDO_650_25(LDO18, "in18", MAX8907_REG_LDOCTL18),
	LDO_750_50(LDO19, "in19", MAX8907_REG_LDOCTL19),
	LDO_750_50(LDO20, "in20", MAX8907_REG_LDOCTL20),
	REG_OUT5V(OUT5V, "mbatt", MAX8907_REG_OUT5VEN, 5000000),
	REG_OUT5V(OUT33V, "mbatt",  MAX8907_REG_OUT33VEN, 3300000),
	REG_BBAT(BBAT, "MBATT", MAX8907_REG_BBAT_CNFG,
						2400000, 3000000, 200000),
	REG_FIXED(SDBY, "MBATT", 1200000),
	REG_FIXED(VRTC, "MBATT", 3300000),
पूर्ण;

#अगर_घोषित CONFIG_OF

#घोषणा MATCH(_name, _id) \
	[MAX8907_##_id] = अणु \
		.name = #_name, \
		.driver_data = (व्योम *)&max8907_regulators[MAX8907_##_id], \
	पूर्ण

अटल काष्ठा of_regulator_match max8907_matches[] = अणु
	MATCH(mbatt, MBATT),
	MATCH(sd1, SD1),
	MATCH(sd2, SD2),
	MATCH(sd3, SD3),
	MATCH(lकरो1, LDO1),
	MATCH(lकरो2, LDO2),
	MATCH(lकरो3, LDO3),
	MATCH(lकरो4, LDO4),
	MATCH(lकरो5, LDO5),
	MATCH(lकरो6, LDO6),
	MATCH(lकरो7, LDO7),
	MATCH(lकरो8, LDO8),
	MATCH(lकरो9, LDO9),
	MATCH(lकरो10, LDO10),
	MATCH(lकरो11, LDO11),
	MATCH(lकरो12, LDO12),
	MATCH(lकरो13, LDO13),
	MATCH(lकरो14, LDO14),
	MATCH(lकरो15, LDO15),
	MATCH(lकरो16, LDO16),
	MATCH(lकरो17, LDO17),
	MATCH(lकरो18, LDO18),
	MATCH(lकरो19, LDO19),
	MATCH(lकरो20, LDO20),
	MATCH(out5v, OUT5V),
	MATCH(out33v, OUT33V),
	MATCH(bbat, BBAT),
	MATCH(sdby, SDBY),
	MATCH(vrtc, VRTC),
पूर्ण;

अटल पूर्णांक max8907_regulator_parse_dt(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np, *regulators;
	पूर्णांक ret;

	np = pdev->dev.parent->of_node;
	अगर (!np)
		वापस 0;

	regulators = of_get_child_by_name(np, "regulators");
	अगर (!regulators) अणु
		dev_err(&pdev->dev, "regulators node not found\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_regulator_match(&pdev->dev, regulators, max8907_matches,
				 ARRAY_SIZE(max8907_matches));
	of_node_put(regulators);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Error parsing regulator init data: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा regulator_init_data *match_init_data(पूर्णांक index)
अणु
	वापस max8907_matches[index].init_data;
पूर्ण

अटल अंतरभूत काष्ठा device_node *match_of_node(पूर्णांक index)
अणु
	वापस max8907_matches[index].of_node;
पूर्ण
#अन्यथा
अटल पूर्णांक max8907_regulator_parse_dt(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा regulator_init_data *match_init_data(पूर्णांक index)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *match_of_node(पूर्णांक index)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक max8907_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8907 *max8907 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max8907_platक्रमm_data *pdata = dev_get_platdata(max8907->dev);
	पूर्णांक ret;
	काष्ठा max8907_regulator *pmic;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;
	काष्ठा regulator_config config = अणुपूर्ण;
	काष्ठा regulator_init_data *idata;
	स्थिर अक्षर *mbatt_rail_name = शून्य;

	ret = max8907_regulator_parse_dt(pdev);
	अगर (ret)
		वापस ret;

	pmic = devm_kzalloc(&pdev->dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pmic);

	स_नकल(pmic->desc, max8907_regulators, माप(pmic->desc));

	/* Backwards compatibility with MAX8907B; SD1 uses dअगरferent voltages */
	ret = regmap_पढ़ो(max8907->regmap_gen, MAX8907_REG_II2RR, &val);
	अगर (ret)
		वापस ret;

	अगर ((val & MAX8907_II2RR_VERSION_MASK) ==
	    MAX8907_II2RR_VERSION_REV_B) अणु
		pmic->desc[MAX8907_SD1].min_uV = 637500;
		pmic->desc[MAX8907_SD1].uV_step = 12500;
		pmic->desc[MAX8907_SD1].n_voltages =
						(1425000 - 637500) / 12500 + 1;
	पूर्ण

	क्रम (i = 0; i < MAX8907_NUM_REGULATORS; i++) अणु
		काष्ठा regulator_dev *rdev;

		config.dev = pdev->dev.parent;
		अगर (pdata)
			idata = pdata->init_data[i];
		अन्यथा
			idata = match_init_data(i);
		config.init_data = idata;
		config.driver_data = pmic;
		config.regmap = max8907->regmap_gen;
		config.of_node = match_of_node(i);

		चयन (pmic->desc[i].id) अणु
		हाल MAX8907_MBATT:
			अगर (idata && idata->स्थिरraपूर्णांकs.name)
				mbatt_rail_name = idata->स्थिरraपूर्णांकs.name;
			अन्यथा
				mbatt_rail_name = pmic->desc[i].name;
			अवरोध;
		हाल MAX8907_BBAT:
		हाल MAX8907_SDBY:
		हाल MAX8907_VRTC:
			idata->supply_regulator = mbatt_rail_name;
			अवरोध;
		पूर्ण

		अगर (pmic->desc[i].ops == &max8907_lकरो_ops) अणु
			ret = regmap_पढ़ो(config.regmap, pmic->desc[i].enable_reg,
				    &val);
			अगर (ret)
				वापस ret;

			अगर ((val & MAX8907_MASK_LDO_SEQ) !=
			    MAX8907_MASK_LDO_SEQ)
				pmic->desc[i].ops = &max8907_lकरो_hwctl_ops;
		पूर्ण अन्यथा अगर (pmic->desc[i].ops == &max8907_out5v_ops) अणु
			ret = regmap_पढ़ो(config.regmap, pmic->desc[i].enable_reg,
				    &val);
			अगर (ret)
				वापस ret;

			अगर ((val & (MAX8907_MASK_OUT5V_VINEN |
						MAX8907_MASK_OUT5V_ENSRC)) !=
			    MAX8907_MASK_OUT5V_ENSRC)
				pmic->desc[i].ops = &max8907_out5v_hwctl_ops;
		पूर्ण

		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
						&pmic->desc[i], &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev,
				"failed to register %s regulator\n",
				pmic->desc[i].name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver max8907_regulator_driver = अणु
	.driver = अणु
		   .name = "max8907-regulator",
		   पूर्ण,
	.probe = max8907_regulator_probe,
पूर्ण;

अटल पूर्णांक __init max8907_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&max8907_regulator_driver);
पूर्ण

subsys_initcall(max8907_regulator_init);

अटल व्योम __निकास max8907_reg_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&max8907_regulator_driver);
पूर्ण

module_निकास(max8907_reg_निकास);

MODULE_DESCRIPTION("MAX8907 regulator driver");
MODULE_AUTHOR("Gyungoh Yoo <jack.yoo@maxim-ic.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:max8907-regulator");
