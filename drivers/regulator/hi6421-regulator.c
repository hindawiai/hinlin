<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Device driver क्रम regulators in Hi6421 IC
//
// Copyright (c) <2011-2014> HiSilicon Technologies Co., Ltd.
//              http://www.hisilicon.com
// Copyright (c) <2013-2014> Linaro Ltd.
//              https://www.linaro.org
//
// Author: Guoकरोng Xu <guoकरोng.xu@linaro.org>

#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/hi6421-pmic.h>

/*
 * काष्ठा hi6421_regulator_pdata - Hi6421 regulator data of platक्रमm device
 * @lock: mutex to serialize regulator enable
 */
काष्ठा hi6421_regulator_pdata अणु
	काष्ठा mutex lock;
पूर्ण;

/*
 * काष्ठा hi6421_regulator_info - hi6421 regulator inक्रमmation
 * @desc: regulator description
 * @mode_mask: ECO mode biपंचांगask of LDOs; क्रम BUCKs, this masks sleep
 * @eco_microamp: eco mode load upper limit (in uA), valid क्रम LDOs only
 */
काष्ठा hi6421_regulator_info अणु
	काष्ठा regulator_desc	desc;
	u8		mode_mask;
	u32		eco_microamp;
पूर्ण;

/* HI6421 regulators */
क्रमागत hi6421_regulator_id अणु
	HI6421_LDO0,
	HI6421_LDO1,
	HI6421_LDO2,
	HI6421_LDO3,
	HI6421_LDO4,
	HI6421_LDO5,
	HI6421_LDO6,
	HI6421_LDO7,
	HI6421_LDO8,
	HI6421_LDO9,
	HI6421_LDO10,
	HI6421_LDO11,
	HI6421_LDO12,
	HI6421_LDO13,
	HI6421_LDO14,
	HI6421_LDO15,
	HI6421_LDO16,
	HI6421_LDO17,
	HI6421_LDO18,
	HI6421_LDO19,
	HI6421_LDO20,
	HI6421_LDOAUDIO,
	HI6421_BUCK0,
	HI6421_BUCK1,
	HI6421_BUCK2,
	HI6421_BUCK3,
	HI6421_BUCK4,
	HI6421_BUCK5,
	HI6421_NUM_REGULATORS,
पूर्ण;

/* LDO 0, 4~7, 9~14, 16~20 have same voltage table. */
अटल स्थिर अचिन्हित पूर्णांक lकरो_0_voltages[] = अणु
	1500000, 1800000, 2400000, 2500000,
	2600000, 2700000, 2850000, 3000000,
पूर्ण;

/* LDO 8, 15 have same voltage table. */
अटल स्थिर अचिन्हित पूर्णांक lकरो_8_voltages[] = अणु
	1500000, 1800000, 2400000, 2600000,
	2700000, 2850000, 3000000, 3300000,
पूर्ण;

/* Ranges are sorted in ascending order. */
अटल स्थिर काष्ठा linear_range lकरो_audio_volt_range[] = अणु
	REGULATOR_LINEAR_RANGE(2800000, 0, 3, 50000),
	REGULATOR_LINEAR_RANGE(3000000, 4, 7, 100000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक buck_3_voltages[] = अणु
	 950000, 1050000, 1100000, 1117000,
	1134000, 1150000, 1167000, 1200000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक buck_4_voltages[] = अणु
	1150000, 1200000, 1250000, 1350000,
	1700000, 1800000, 1900000, 2000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक buck_5_voltages[] = अणु
	1150000, 1200000, 1250000, 1350000,
	1600000, 1700000, 1800000, 1900000,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops hi6421_lकरो_ops;
अटल स्थिर काष्ठा regulator_ops hi6421_lकरो_linear_ops;
अटल स्थिर काष्ठा regulator_ops hi6421_lकरो_linear_range_ops;
अटल स्थिर काष्ठा regulator_ops hi6421_buck012_ops;
अटल स्थिर काष्ठा regulator_ops hi6421_buck345_ops;

#घोषणा HI6421_LDO_ENABLE_TIME (350)
/*
 * _id - LDO id name string
 * _match - of match name string
 * v_table - voltage table
 * vreg - voltage select रेजिस्टर
 * vmask - voltage select mask
 * ereg - enable रेजिस्टर
 * emask - enable mask
 * odelay - off/on delay समय in uS
 * ecomask - eco mode mask
 * ecoamp - eco mode load uppler limit in uA
 */
#घोषणा HI6421_LDO(_id, _match, v_table, vreg, vmask, ereg, emask,	\
		   odelay, ecomask, ecoamp)				\
	[HI6421_##_id] = अणु						\
		.desc = अणु						\
			.name		= #_id,				\
			.of_match        = of_match_ptr(#_match),	\
			.regulators_node = of_match_ptr("regulators"),	\
			.ops		= &hi6421_lकरो_ops,		\
			.type		= REGULATOR_VOLTAGE,		\
			.id		= HI6421_##_id,			\
			.owner		= THIS_MODULE,			\
			.n_voltages	= ARRAY_SIZE(v_table),		\
			.volt_table	= v_table,			\
			.vsel_reg	= HI6421_REG_TO_BUS_ADDR(vreg),	\
			.vsel_mask	= vmask,			\
			.enable_reg	= HI6421_REG_TO_BUS_ADDR(ereg),	\
			.enable_mask	= emask,			\
			.enable_समय	= HI6421_LDO_ENABLE_TIME,	\
			.off_on_delay	= odelay,			\
		पूर्ण,							\
		.mode_mask		= ecomask,			\
		.eco_microamp		= ecoamp,			\
	पूर्ण

/* HI6421 LDO1~3 are linear voltage regulators at fixed uV_step
 *
 * _id - LDO id name string
 * _match - of match name string
 * _min_uV - minimum voltage supported in uV
 * n_volt - number of votages available
 * vstep - voltage increase in each linear step in uV
 * vreg - voltage select रेजिस्टर
 * vmask - voltage select mask
 * ereg - enable रेजिस्टर
 * emask - enable mask
 * odelay - off/on delay समय in uS
 * ecomask - eco mode mask
 * ecoamp - eco mode load uppler limit in uA
 */
#घोषणा HI6421_LDO_LINEAR(_id, _match, _min_uV, n_volt, vstep, vreg, vmask,\
			  ereg, emask, odelay, ecomask, ecoamp)		\
	[HI6421_##_id] = अणु						\
		.desc = अणु						\
			.name		= #_id,				\
			.of_match        = of_match_ptr(#_match),	\
			.regulators_node = of_match_ptr("regulators"),	\
			.ops		= &hi6421_lकरो_linear_ops,	\
			.type		= REGULATOR_VOLTAGE,		\
			.id		= HI6421_##_id,			\
			.owner		= THIS_MODULE,			\
			.min_uV		= _min_uV,			\
			.n_voltages	= n_volt,			\
			.uV_step	= vstep,			\
			.vsel_reg	= HI6421_REG_TO_BUS_ADDR(vreg),	\
			.vsel_mask	= vmask,			\
			.enable_reg	= HI6421_REG_TO_BUS_ADDR(ereg),	\
			.enable_mask	= emask,			\
			.enable_समय	= HI6421_LDO_ENABLE_TIME,	\
			.off_on_delay	= odelay,			\
		पूर्ण,							\
		.mode_mask		= ecomask,			\
		.eco_microamp		= ecoamp,			\
	पूर्ण

/* HI6421 LDOAUDIO is a linear voltage regulator with two 4-step ranges
 *
 * _id - LDO id name string
 * _match - of match name string
 * n_volt - number of votages available
 * volt_ranges - array of linear_range
 * vstep - voltage increase in each linear step in uV
 * vreg - voltage select रेजिस्टर
 * vmask - voltage select mask
 * ereg - enable रेजिस्टर
 * emask - enable mask
 * odelay - off/on delay समय in uS
 * ecomask - eco mode mask
 * ecoamp - eco mode load uppler limit in uA
 */
#घोषणा HI6421_LDO_LINEAR_RANGE(_id, _match, n_volt, volt_ranges, vreg, vmask,\
				ereg, emask, odelay, ecomask, ecoamp)	\
	[HI6421_##_id] = अणु						\
		.desc = अणु						\
			.name		= #_id,				\
			.of_match        = of_match_ptr(#_match),	\
			.regulators_node = of_match_ptr("regulators"),	\
			.ops		= &hi6421_lकरो_linear_range_ops,	\
			.type		= REGULATOR_VOLTAGE,		\
			.id		= HI6421_##_id,			\
			.owner		= THIS_MODULE,			\
			.n_voltages	= n_volt,			\
			.linear_ranges	= volt_ranges,			\
			.n_linear_ranges = ARRAY_SIZE(volt_ranges),	\
			.vsel_reg	= HI6421_REG_TO_BUS_ADDR(vreg),	\
			.vsel_mask	= vmask,			\
			.enable_reg	= HI6421_REG_TO_BUS_ADDR(ereg),	\
			.enable_mask	= emask,			\
			.enable_समय	= HI6421_LDO_ENABLE_TIME,	\
			.off_on_delay	= odelay,			\
		पूर्ण,							\
		.mode_mask		= ecomask,			\
		.eco_microamp		= ecoamp,			\
	पूर्ण

/* HI6421 BUCK0/1/2 are linear voltage regulators at fixed uV_step
 *
 * _id - BUCK0/1/2 id name string
 * _match - of match name string
 * vreg - voltage select रेजिस्टर
 * vmask - voltage select mask
 * ereg - enable रेजिस्टर
 * emask - enable mask
 * sleepmask - mask of sleep mode
 * eसमय - enable समय
 * odelay - off/on delay समय in uS
 */
#घोषणा HI6421_BUCK012(_id, _match, vreg, vmask, ereg, emask, sleepmask,\
			eसमय, odelay)					\
	[HI6421_##_id] = अणु						\
		.desc = अणु						\
			.name		= #_id,				\
			.of_match        = of_match_ptr(#_match),	\
			.regulators_node = of_match_ptr("regulators"),	\
			.ops		= &hi6421_buck012_ops,		\
			.type		= REGULATOR_VOLTAGE,		\
			.id		= HI6421_##_id,			\
			.owner		= THIS_MODULE,			\
			.min_uV		= 700000,			\
			.n_voltages	= 128,				\
			.uV_step	= 7086,				\
			.vsel_reg	= HI6421_REG_TO_BUS_ADDR(vreg),	\
			.vsel_mask	= vmask,			\
			.enable_reg	= HI6421_REG_TO_BUS_ADDR(ereg),	\
			.enable_mask	= emask,			\
			.enable_समय	= eसमय,			\
			.off_on_delay	= odelay,			\
		पूर्ण,							\
		.mode_mask		= sleepmask,			\
	पूर्ण

/* HI6421 BUCK3/4/5 share similar configurations as LDOs, with exception
 *  that it supports SLEEP mode, so has dअगरferent .ops.
 *
 * _id - LDO id name string
 * _match - of match name string
 * v_table - voltage table
 * vreg - voltage select रेजिस्टर
 * vmask - voltage select mask
 * ereg - enable रेजिस्टर
 * emask - enable mask
 * odelay - off/on delay समय in uS
 * sleepmask - mask of sleep mode
 */
#घोषणा HI6421_BUCK345(_id, _match, v_table, vreg, vmask, ereg, emask,	\
			odelay, sleepmask)				\
	[HI6421_##_id] = अणु						\
		.desc = अणु						\
			.name		= #_id,				\
			.of_match        = of_match_ptr(#_match),	\
			.regulators_node = of_match_ptr("regulators"),	\
			.ops		= &hi6421_buck345_ops,		\
			.type		= REGULATOR_VOLTAGE,		\
			.id		= HI6421_##_id,			\
			.owner		= THIS_MODULE,			\
			.n_voltages	= ARRAY_SIZE(v_table),		\
			.volt_table	= v_table,			\
			.vsel_reg	= HI6421_REG_TO_BUS_ADDR(vreg),	\
			.vsel_mask	= vmask,			\
			.enable_reg	= HI6421_REG_TO_BUS_ADDR(ereg),	\
			.enable_mask	= emask,			\
			.enable_समय	= HI6421_LDO_ENABLE_TIME,	\
			.off_on_delay	= odelay,			\
		पूर्ण,							\
		.mode_mask		= sleepmask,			\
	पूर्ण

/* HI6421 regulator inक्रमmation */
अटल काष्ठा hi6421_regulator_info
		hi6421_regulator_info[HI6421_NUM_REGULATORS] = अणु
	HI6421_LDO(LDO0, hi6421_vout0, lकरो_0_voltages, 0x20, 0x07, 0x20, 0x10,
		   10000, 0x20, 8000),
	HI6421_LDO_LINEAR(LDO1, hi6421_vout1, 1700000, 4, 100000, 0x21, 0x03,
			  0x21, 0x10, 10000, 0x20, 5000),
	HI6421_LDO_LINEAR(LDO2, hi6421_vout2, 1050000, 8, 50000, 0x22, 0x07,
			  0x22, 0x10, 20000, 0x20, 8000),
	HI6421_LDO_LINEAR(LDO3, hi6421_vout3, 1050000, 8, 50000, 0x23, 0x07,
			  0x23, 0x10, 20000, 0x20, 8000),
	HI6421_LDO(LDO4, hi6421_vout4, lकरो_0_voltages, 0x24, 0x07, 0x24, 0x10,
		   20000, 0x20, 8000),
	HI6421_LDO(LDO5, hi6421_vout5, lकरो_0_voltages, 0x25, 0x07, 0x25, 0x10,
		   20000, 0x20, 8000),
	HI6421_LDO(LDO6, hi6421_vout6, lकरो_0_voltages, 0x26, 0x07, 0x26, 0x10,
		   20000, 0x20, 8000),
	HI6421_LDO(LDO7, hi6421_vout7, lकरो_0_voltages, 0x27, 0x07, 0x27, 0x10,
		   20000, 0x20, 5000),
	HI6421_LDO(LDO8, hi6421_vout8, lकरो_8_voltages, 0x28, 0x07, 0x28, 0x10,
		   20000, 0x20, 8000),
	HI6421_LDO(LDO9, hi6421_vout9, lकरो_0_voltages, 0x29, 0x07, 0x29, 0x10,
		   40000, 0x20, 8000),
	HI6421_LDO(LDO10, hi6421_vout10, lकरो_0_voltages, 0x2a, 0x07, 0x2a, 0x10,
		   40000, 0x20, 8000),
	HI6421_LDO(LDO11, hi6421_vout11, lकरो_0_voltages, 0x2b, 0x07, 0x2b, 0x10,
		   40000, 0x20, 8000),
	HI6421_LDO(LDO12, hi6421_vout12, lकरो_0_voltages, 0x2c, 0x07, 0x2c, 0x10,
		   40000, 0x20, 8000),
	HI6421_LDO(LDO13, hi6421_vout13, lकरो_0_voltages, 0x2d, 0x07, 0x2d, 0x10,
		   40000, 0x20, 8000),
	HI6421_LDO(LDO14, hi6421_vout14, lकरो_0_voltages, 0x2e, 0x07, 0x2e, 0x10,
		   40000, 0x20, 8000),
	HI6421_LDO(LDO15, hi6421_vout15, lकरो_8_voltages, 0x2f, 0x07, 0x2f, 0x10,
		   40000, 0x20, 8000),
	HI6421_LDO(LDO16, hi6421_vout16, lकरो_0_voltages, 0x30, 0x07, 0x30, 0x10,
		   40000, 0x20, 8000),
	HI6421_LDO(LDO17, hi6421_vout17, lकरो_0_voltages, 0x31, 0x07, 0x31, 0x10,
		   40000, 0x20, 8000),
	HI6421_LDO(LDO18, hi6421_vout18, lकरो_0_voltages, 0x32, 0x07, 0x32, 0x10,
		   40000, 0x20, 8000),
	HI6421_LDO(LDO19, hi6421_vout19, lकरो_0_voltages, 0x33, 0x07, 0x33, 0x10,
		   40000, 0x20, 8000),
	HI6421_LDO(LDO20, hi6421_vout20, lकरो_0_voltages, 0x34, 0x07, 0x34, 0x10,
		   40000, 0x20, 8000),
	HI6421_LDO_LINEAR_RANGE(LDOAUDIO, hi6421_vout_audio, 8,
				lकरो_audio_volt_range, 0x36, 0x70, 0x36, 0x01,
				40000, 0x02, 5000),
	HI6421_BUCK012(BUCK0, hi6421_buck0, 0x0d, 0x7f, 0x0c, 0x01, 0x10, 400,
		       20000),
	HI6421_BUCK012(BUCK1, hi6421_buck1, 0x0f, 0x7f, 0x0e, 0x01, 0x10, 400,
		       20000),
	HI6421_BUCK012(BUCK2, hi6421_buck2, 0x11, 0x7f, 0x10, 0x01, 0x10, 350,
		       100),
	HI6421_BUCK345(BUCK3, hi6421_buck3, buck_3_voltages, 0x13, 0x07, 0x12,
		       0x01, 20000, 0x10),
	HI6421_BUCK345(BUCK4, hi6421_buck4, buck_4_voltages, 0x15, 0x07, 0x14,
		       0x01, 20000, 0x10),
	HI6421_BUCK345(BUCK5, hi6421_buck5, buck_5_voltages, 0x17, 0x07, 0x16,
		       0x01, 20000, 0x10),
पूर्ण;

अटल पूर्णांक hi6421_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा hi6421_regulator_pdata *pdata;

	pdata = dev_get_drvdata(rdev->dev.parent);
	/* hi6421 spec requires regulator enablement must be serialized:
	 *  - Because when BUCK, LDO चयनing from off to on, it will have
	 *    a huge instantaneous current; so you can not turn on two or
	 *    more LDO or BUCKs simultaneously, or it may burn the chip.
	 */
	mutex_lock(&pdata->lock);

	/* call regulator regmap helper */
	regulator_enable_regmap(rdev);

	mutex_unlock(&pdata->lock);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक hi6421_regulator_lकरो_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा hi6421_regulator_info *info = rdev_get_drvdata(rdev);
	u32 reg_val;

	regmap_पढ़ो(rdev->regmap, rdev->desc->enable_reg, &reg_val);
	अगर (reg_val & info->mode_mask)
		वापस REGULATOR_MODE_IDLE;

	वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल अचिन्हित पूर्णांक hi6421_regulator_buck_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा hi6421_regulator_info *info = rdev_get_drvdata(rdev);
	u32 reg_val;

	regmap_पढ़ो(rdev->regmap, rdev->desc->enable_reg, &reg_val);
	अगर (reg_val & info->mode_mask)
		वापस REGULATOR_MODE_STANDBY;

	वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक hi6421_regulator_lकरो_set_mode(काष्ठा regulator_dev *rdev,
						अचिन्हित पूर्णांक mode)
अणु
	काष्ठा hi6421_regulator_info *info = rdev_get_drvdata(rdev);
	u32 new_mode;

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

	/* set mode */
	regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
			   info->mode_mask, new_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक hi6421_regulator_buck_set_mode(काष्ठा regulator_dev *rdev,
						अचिन्हित पूर्णांक mode)
अणु
	काष्ठा hi6421_regulator_info *info = rdev_get_drvdata(rdev);
	u32 new_mode;

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		new_mode = 0;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		new_mode = info->mode_mask;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set mode */
	regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
			   info->mode_mask, new_mode);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
hi6421_regulator_lकरो_get_optimum_mode(काष्ठा regulator_dev *rdev,
			पूर्णांक input_uV, पूर्णांक output_uV, पूर्णांक load_uA)
अणु
	काष्ठा hi6421_regulator_info *info = rdev_get_drvdata(rdev);

	अगर (load_uA > info->eco_microamp)
		वापस REGULATOR_MODE_NORMAL;

	वापस REGULATOR_MODE_IDLE;
पूर्ण

अटल स्थिर काष्ठा regulator_ops hi6421_lकरो_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = hi6421_regulator_enable,
	.disable = regulator_disable_regmap,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_mode = hi6421_regulator_lकरो_get_mode,
	.set_mode = hi6421_regulator_lकरो_set_mode,
	.get_optimum_mode = hi6421_regulator_lकरो_get_optimum_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops hi6421_lकरो_linear_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = hi6421_regulator_enable,
	.disable = regulator_disable_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_mode = hi6421_regulator_lकरो_get_mode,
	.set_mode = hi6421_regulator_lकरो_set_mode,
	.get_optimum_mode = hi6421_regulator_lकरो_get_optimum_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops hi6421_lकरो_linear_range_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = hi6421_regulator_enable,
	.disable = regulator_disable_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_mode = hi6421_regulator_lकरो_get_mode,
	.set_mode = hi6421_regulator_lकरो_set_mode,
	.get_optimum_mode = hi6421_regulator_lकरो_get_optimum_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops hi6421_buck012_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = hi6421_regulator_enable,
	.disable = regulator_disable_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_mode = hi6421_regulator_buck_get_mode,
	.set_mode = hi6421_regulator_buck_set_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops hi6421_buck345_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = hi6421_regulator_enable,
	.disable = regulator_disable_regmap,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_mode = hi6421_regulator_buck_get_mode,
	.set_mode = hi6421_regulator_buck_set_mode,
पूर्ण;

अटल पूर्णांक hi6421_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hi6421_pmic *pmic = dev_get_drvdata(pdev->dev.parent);
	काष्ठा hi6421_regulator_pdata *pdata;
	काष्ठा hi6421_regulator_info *info;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;
	mutex_init(&pdata->lock);
	platक्रमm_set_drvdata(pdev, pdata);

	क्रम (i = 0; i < ARRAY_SIZE(hi6421_regulator_info); i++) अणु
		/* assign per-regulator data */
		info = &hi6421_regulator_info[i];

		config.dev = pdev->dev.parent;
		config.driver_data = info;
		config.regmap = pmic->regmap;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &info->desc,
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register regulator %s\n",
				info->desc.name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hi6421_regulator_table[] = अणु
	अणु .name = "hi6421-regulator" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hi6421_regulator_table);

अटल काष्ठा platक्रमm_driver hi6421_regulator_driver = अणु
	.id_table = hi6421_regulator_table,
	.driver = अणु
		.name	= "hi6421-regulator",
	पूर्ण,
	.probe	= hi6421_regulator_probe,
पूर्ण;
module_platक्रमm_driver(hi6421_regulator_driver);

MODULE_AUTHOR("Guodong Xu <guodong.xu@linaro.org>");
MODULE_DESCRIPTION("Hi6421 regulator driver");
MODULE_LICENSE("GPL v2");
