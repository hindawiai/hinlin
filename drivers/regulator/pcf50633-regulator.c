<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* NXP PCF50633 PMIC Driver
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Author: Balaji Rao <balajirrao@खोलोmoko.org>
 * All rights reserved.
 *
 * Broken करोwn from monstrous PCF50633 driver मुख्यly by
 * Harald Welte and Andy Green and Werner Almesberger
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mfd/pcf50633/core.h>
#समावेश <linux/mfd/pcf50633/pmic.h>

#घोषणा PCF50633_REGULATOR(_name, _id, _min_uV, _uV_step, _min_sel, _n) \
	अणु							\
		.name = _name,					\
		.id = PCF50633_REGULATOR_##_id,			\
		.ops = &pcf50633_regulator_ops,			\
		.n_voltages = _n,				\
		.min_uV = _min_uV,				\
		.uV_step = _uV_step,				\
		.linear_min_sel = _min_sel,			\
		.type = REGULATOR_VOLTAGE,			\
		.owner = THIS_MODULE,				\
		.vsel_reg = PCF50633_REG_##_id##OUT,		\
		.vsel_mask = 0xff,				\
		.enable_reg = PCF50633_REG_##_id##OUT + 1,	\
		.enable_mask = PCF50633_REGULATOR_ON,		\
	पूर्ण

अटल स्थिर काष्ठा regulator_ops pcf50633_regulator_ops = अणु
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc regulators[] = अणु
	[PCF50633_REGULATOR_AUTO] =
		PCF50633_REGULATOR("auto", AUTO, 1800000, 25000, 0x2f, 128),
	[PCF50633_REGULATOR_DOWN1] =
		PCF50633_REGULATOR("down1", DOWN1, 625000, 25000, 0, 96),
	[PCF50633_REGULATOR_DOWN2] =
		PCF50633_REGULATOR("down2", DOWN2, 625000, 25000, 0, 96),
	[PCF50633_REGULATOR_LDO1] =
		PCF50633_REGULATOR("ldo1", LDO1, 900000, 100000, 0, 28),
	[PCF50633_REGULATOR_LDO2] =
		PCF50633_REGULATOR("ldo2", LDO2, 900000, 100000, 0, 28),
	[PCF50633_REGULATOR_LDO3] =
		PCF50633_REGULATOR("ldo3", LDO3, 900000, 100000, 0, 28),
	[PCF50633_REGULATOR_LDO4] =
		PCF50633_REGULATOR("ldo4", LDO4, 900000, 100000, 0, 28),
	[PCF50633_REGULATOR_LDO5] =
		PCF50633_REGULATOR("ldo5", LDO5, 900000, 100000, 0, 28),
	[PCF50633_REGULATOR_LDO6] =
		PCF50633_REGULATOR("ldo6", LDO6, 900000, 100000, 0, 28),
	[PCF50633_REGULATOR_HCLDO] =
		PCF50633_REGULATOR("hcldo", HCLDO, 900000, 100000, 0, 28),
	[PCF50633_REGULATOR_MEMLDO] =
		PCF50633_REGULATOR("memldo", MEMLDO, 900000, 100000, 0, 28),
पूर्ण;

अटल पूर्णांक pcf50633_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator_dev *rdev;
	काष्ठा pcf50633 *pcf;
	काष्ठा regulator_config config = अणु पूर्ण;

	/* Alपढ़ोy set by core driver */
	pcf = dev_to_pcf50633(pdev->dev.parent);

	config.dev = &pdev->dev;
	config.init_data = dev_get_platdata(&pdev->dev);
	config.driver_data = pcf;
	config.regmap = pcf->regmap;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[pdev->id],
				       &config);
	अगर (IS_ERR(rdev))
		वापस PTR_ERR(rdev);

	platक्रमm_set_drvdata(pdev, rdev);

	अगर (pcf->pdata->regulator_रेजिस्टरed)
		pcf->pdata->regulator_रेजिस्टरed(pcf, pdev->id);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pcf50633_regulator_driver = अणु
	.driver = अणु
		.name = "pcf50633-regulator",
	पूर्ण,
	.probe = pcf50633_regulator_probe,
पूर्ण;

अटल पूर्णांक __init pcf50633_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pcf50633_regulator_driver);
पूर्ण
subsys_initcall(pcf50633_regulator_init);

अटल व्योम __निकास pcf50633_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&pcf50633_regulator_driver);
पूर्ण
module_निकास(pcf50633_regulator_निकास);

MODULE_AUTHOR("Balaji Rao <balajirrao@openmoko.org>");
MODULE_DESCRIPTION("PCF50633 regulator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pcf50633-regulator");
