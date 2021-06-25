<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Device driver क्रम regulators in Hi6421V530 IC
//
// Copyright (c) <2017> HiSilicon Technologies Co., Ltd.
//              http://www.hisilicon.com
// Copyright (c) <2017> Linaro Ltd.
//              https://www.linaro.org
//
// Author: Wang Xiaoyin <hw.wangxiaoyin@hisilicon.com>
//         Guoकरोng Xu <guoकरोng.xu@linaro.org>

#समावेश <linux/mfd/hi6421-pmic.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>

/*
 * काष्ठा hi6421v530_regulator_info - hi6421v530 regulator inक्रमmation
 * @desc: regulator description
 * @mode_mask: ECO mode biपंचांगask of LDOs; क्रम BUCKs, this masks sleep
 * @eco_microamp: eco mode load upper limit (in uA), valid क्रम LDOs only
 */
काष्ठा hi6421v530_regulator_info अणु
	काष्ठा regulator_desc rdesc;
	u8 mode_mask;
	u32 eco_microamp;
पूर्ण;

/* HI6421v530 regulators */
क्रमागत hi6421v530_regulator_id अणु
	HI6421V530_LDO3,
	HI6421V530_LDO9,
	HI6421V530_LDO11,
	HI6421V530_LDO15,
	HI6421V530_LDO16,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_3_voltages[] = अणु
	1800000, 1825000, 1850000, 1875000,
	1900000, 1925000, 1950000, 1975000,
	2000000, 2025000, 2050000, 2075000,
	2100000, 2125000, 2150000, 2200000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_9_11_voltages[] = अणु
	1750000, 1800000, 1825000, 2800000,
	2850000, 2950000, 3000000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_15_16_voltages[] = अणु
	1750000, 1800000, 2400000, 2600000,
	2700000, 2850000, 2950000, 3000000,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops hi6421v530_lकरो_ops;

#घोषणा HI6421V530_LDO_ENABLE_TIME (350)

/*
 * _id - LDO id name string
 * v_table - voltage table
 * vreg - voltage select रेजिस्टर
 * vmask - voltage select mask
 * ereg - enable रेजिस्टर
 * emask - enable mask
 * odelay - off/on delay समय in uS
 * ecomask - eco mode mask
 * ecoamp - eco mode load uppler limit in uA
 */
#घोषणा HI6421V530_LDO(_ID, v_table, vreg, vmask, ereg, emask,		\
		   odelay, ecomask, ecoamp) अणु				\
	.rdesc = अणु							\
		.name		 = #_ID,				\
		.of_match        = of_match_ptr(#_ID),			\
		.regulators_node = of_match_ptr("regulators"),		\
		.ops		 = &hi6421v530_lकरो_ops,			\
		.type		 = REGULATOR_VOLTAGE,			\
		.id		 = HI6421V530_##_ID,			\
		.owner		 = THIS_MODULE,				\
		.n_voltages	 = ARRAY_SIZE(v_table),			\
		.volt_table	 = v_table,				\
		.vsel_reg	 = HI6421_REG_TO_BUS_ADDR(vreg),	\
		.vsel_mask	 = vmask,				\
		.enable_reg	 = HI6421_REG_TO_BUS_ADDR(ereg),	\
		.enable_mask	 = emask,				\
		.enable_समय	 = HI6421V530_LDO_ENABLE_TIME,		\
		.off_on_delay	 = odelay,				\
	पूर्ण,								\
	.mode_mask	= ecomask,					\
	.eco_microamp	= ecoamp,					\
पूर्ण

/* HI6421V530 regulator inक्रमmation */

अटल काष्ठा hi6421v530_regulator_info hi6421v530_regulator_info[] = अणु
	HI6421V530_LDO(LDO3, lकरो_3_voltages, 0x061, 0xf, 0x060, 0x2,
		   20000, 0x6, 8000),
	HI6421V530_LDO(LDO9, lकरो_9_11_voltages, 0x06b, 0x7, 0x06a, 0x2,
		   40000, 0x6, 8000),
	HI6421V530_LDO(LDO11, lकरो_9_11_voltages, 0x06f, 0x7, 0x06e, 0x2,
		   40000, 0x6, 8000),
	HI6421V530_LDO(LDO15, lकरो_15_16_voltages, 0x077, 0x7, 0x076, 0x2,
		   40000, 0x6, 8000),
	HI6421V530_LDO(LDO16, lकरो_15_16_voltages, 0x079, 0x7, 0x078, 0x2,
		   40000, 0x6, 8000),
पूर्ण;

अटल अचिन्हित पूर्णांक hi6421v530_regulator_lकरो_get_mode(
					काष्ठा regulator_dev *rdev)
अणु
	काष्ठा hi6421v530_regulator_info *info;
	अचिन्हित पूर्णांक reg_val;

	info = rdev_get_drvdata(rdev);
	regmap_पढ़ो(rdev->regmap, rdev->desc->enable_reg, &reg_val);

	अगर (reg_val & (info->mode_mask))
		वापस REGULATOR_MODE_IDLE;

	वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक hi6421v530_regulator_lकरो_set_mode(काष्ठा regulator_dev *rdev,
						अचिन्हित पूर्णांक mode)
अणु
	काष्ठा hi6421v530_regulator_info *info;
	अचिन्हित पूर्णांक new_mode;

	info = rdev_get_drvdata(rdev);
	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		new_mode = 0;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		new_mode = info->mode_mask;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
			   info->mode_mask, new_mode);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा regulator_ops hi6421v530_lकरो_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_mode = hi6421v530_regulator_lकरो_get_mode,
	.set_mode = hi6421v530_regulator_lकरो_set_mode,
पूर्ण;

अटल पूर्णांक hi6421v530_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hi6421_pmic *pmic;
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_config config = अणु पूर्ण;
	अचिन्हित पूर्णांक i;

	pmic = dev_get_drvdata(pdev->dev.parent);
	अगर (!pmic) अणु
		dev_err(&pdev->dev, "no pmic in the regulator parent node\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(hi6421v530_regulator_info); i++) अणु
		config.dev = pdev->dev.parent;
		config.regmap = pmic->regmap;
		config.driver_data = &hi6421v530_regulator_info[i];

		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
				&hi6421v530_regulator_info[i].rdesc,
				&config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register regulator %s\n",
				hi6421v530_regulator_info[i].rdesc.name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hi6421v530_regulator_table[] = अणु
	अणु .name = "hi6421v530-regulator" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hi6421v530_regulator_table);

अटल काष्ठा platक्रमm_driver hi6421v530_regulator_driver = अणु
	.id_table = hi6421v530_regulator_table,
	.driver = अणु
		.name	= "hi6421v530-regulator",
	पूर्ण,
	.probe	= hi6421v530_regulator_probe,
पूर्ण;
module_platक्रमm_driver(hi6421v530_regulator_driver);

MODULE_AUTHOR("Wang Xiaoyin <hw.wangxiaoyin@hisilicon.com>");
MODULE_DESCRIPTION("Hi6421v530 regulator driver");
MODULE_LICENSE("GPL v2");
