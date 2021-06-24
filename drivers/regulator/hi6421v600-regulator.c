<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Device driver क्रम regulators in Hisi IC
//
// Copyright (c) 2013 Linaro Ltd.
// Copyright (c) 2011 HiSilicon Ltd.
// Copyright (c) 2020-2021 Huawei Technologies Co., Ltd
//
// Guoकरोng Xu <guoकरोng.xu@linaro.org>

#समावेश <linux/delay.h>
#समावेश <linux/mfd/hi6421-spmi-pmic.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/spmi.h>

काष्ठा hi6421_spmi_reg_info अणु
	काष्ठा regulator_desc	desc;
	काष्ठा hi6421_spmi_pmic *pmic;
	u8			eco_mode_mask;
	u32			eco_uA;

	/* Serialize regulator enable logic */
	काष्ठा mutex enable_mutex;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो3_voltages[] = अणु
	1500000, 1550000, 1600000, 1650000,
	1700000, 1725000, 1750000, 1775000,
	1800000, 1825000, 1850000, 1875000,
	1900000, 1925000, 1950000, 2000000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो4_voltages[] = अणु
	1725000, 1750000, 1775000, 1800000,
	1825000, 1850000, 1875000, 1900000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो9_voltages[] = अणु
	1750000, 1800000, 1825000, 2800000,
	2850000, 2950000, 3000000, 3300000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो15_voltages[] = अणु
	1800000, 1850000, 2400000, 2600000,
	2700000, 2850000, 2950000, 3000000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो17_voltages[] = अणु
	2500000, 2600000, 2700000, 2800000,
	3000000, 3100000, 3200000, 3300000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो34_voltages[] = अणु
	2600000, 2700000, 2800000, 2900000,
	3000000, 3100000, 3200000, 3300000
पूर्ण;

/**
 * HI6421V600_LDO() - specअगरy a LDO घातer line
 * @_id: LDO id name string
 * @vtable: voltage table
 * @ereg: enable रेजिस्टर
 * @emask: enable mask
 * @vreg: voltage select रेजिस्टर
 * @odelay: off/on delay समय in uS
 * @eसमय: enable समय in uS
 * @ecomask: eco mode mask
 * @ecoamp: eco mode load uppler limit in uA
 */
#घोषणा HI6421V600_LDO(_id, vtable, ereg, emask, vreg,			       \
		       odelay, eसमय, ecomask, ecoamp)			       \
	[HI6421V600_##_id] = अणु						       \
		.desc = अणु						       \
			.name		= #_id,				       \
			.of_match        = of_match_ptr(#_id),		       \
			.regulators_node = of_match_ptr("regulators"),	       \
			.ops		= &hi6421_spmi_lकरो_rops,	       \
			.type		= REGULATOR_VOLTAGE,		       \
			.id		= HI6421V600_##_id,		       \
			.owner		= THIS_MODULE,			       \
			.volt_table	= vtable,			       \
			.n_voltages	= ARRAY_SIZE(vtable),		       \
			.vsel_mask	= ARRAY_SIZE(vtable) - 1,	       \
			.vsel_reg	= vreg,				       \
			.enable_reg	= ereg,				       \
			.enable_mask	= emask,			       \
			.enable_समय	= eसमय,			       \
			.ramp_delay	= eसमय,			       \
			.off_on_delay	= odelay,			       \
		पूर्ण,							       \
		.eco_mode_mask		= ecomask,			       \
		.eco_uA			= ecoamp,			       \
	पूर्ण

अटल पूर्णांक hi6421_spmi_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा hi6421_spmi_reg_info *sreg = rdev_get_drvdata(rdev);
	काष्ठा hi6421_spmi_pmic *pmic = sreg->pmic;
	पूर्णांक ret;

	/* cannot enable more than one regulator at one समय */
	mutex_lock(&sreg->enable_mutex);

	ret = regmap_update_bits(pmic->regmap, rdev->desc->enable_reg,
				 rdev->desc->enable_mask,
				 rdev->desc->enable_mask);

	/* Aव्योम घातering up multiple devices at the same समय */
	usleep_range(rdev->desc->off_on_delay, rdev->desc->off_on_delay + 60);

	mutex_unlock(&sreg->enable_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक hi6421_spmi_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा hi6421_spmi_reg_info *sreg = rdev_get_drvdata(rdev);
	काष्ठा hi6421_spmi_pmic *pmic = sreg->pmic;

	वापस regmap_update_bits(pmic->regmap, rdev->desc->enable_reg,
				  rdev->desc->enable_mask, 0);
पूर्ण

अटल अचिन्हित पूर्णांक hi6421_spmi_regulator_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा hi6421_spmi_reg_info *sreg = rdev_get_drvdata(rdev);
	काष्ठा hi6421_spmi_pmic *pmic = sreg->pmic;
	u32 reg_val;

	regmap_पढ़ो(pmic->regmap, rdev->desc->enable_reg, &reg_val);

	अगर (reg_val & sreg->eco_mode_mask)
		वापस REGULATOR_MODE_IDLE;

	वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक hi6421_spmi_regulator_set_mode(काष्ठा regulator_dev *rdev,
					  अचिन्हित पूर्णांक mode)
अणु
	काष्ठा hi6421_spmi_reg_info *sreg = rdev_get_drvdata(rdev);
	काष्ठा hi6421_spmi_pmic *pmic = sreg->pmic;
	u32 val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		val = 0;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		val = sreg->eco_mode_mask << (ffs(sreg->eco_mode_mask) - 1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(pmic->regmap, rdev->desc->enable_reg,
				  sreg->eco_mode_mask, val);
पूर्ण

अटल अचिन्हित पूर्णांक
hi6421_spmi_regulator_get_optimum_mode(काष्ठा regulator_dev *rdev,
				       पूर्णांक input_uV, पूर्णांक output_uV,
				       पूर्णांक load_uA)
अणु
	काष्ठा hi6421_spmi_reg_info *sreg = rdev_get_drvdata(rdev);

	अगर (!sreg->eco_uA || ((अचिन्हित पूर्णांक)load_uA > sreg->eco_uA))
		वापस REGULATOR_MODE_NORMAL;

	वापस REGULATOR_MODE_IDLE;
पूर्ण

अटल स्थिर काष्ठा regulator_ops hi6421_spmi_lकरो_rops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = hi6421_spmi_regulator_enable,
	.disable = hi6421_spmi_regulator_disable,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_iterate,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_mode = hi6421_spmi_regulator_get_mode,
	.set_mode = hi6421_spmi_regulator_set_mode,
	.get_optimum_mode = hi6421_spmi_regulator_get_optimum_mode,
पूर्ण;

/* HI6421v600 regulators with known रेजिस्टरs */
क्रमागत hi6421_spmi_regulator_id अणु
	HI6421V600_LDO3,
	HI6421V600_LDO4,
	HI6421V600_LDO9,
	HI6421V600_LDO15,
	HI6421V600_LDO16,
	HI6421V600_LDO17,
	HI6421V600_LDO33,
	HI6421V600_LDO34,
पूर्ण;

अटल काष्ठा hi6421_spmi_reg_info regulator_info[] = अणु
	HI6421V600_LDO(LDO3, lकरो3_voltages,
		       0x16, 0x01, 0x51,
		       20000, 120,
		       0, 0),
	HI6421V600_LDO(LDO4, lकरो4_voltages,
		       0x17, 0x01, 0x52,
		       20000, 120,
		       0x10, 10000),
	HI6421V600_LDO(LDO9, lकरो9_voltages,
		       0x1c, 0x01, 0x57,
		       20000, 360,
		       0x10, 10000),
	HI6421V600_LDO(LDO15, lकरो15_voltages,
		       0x21, 0x01, 0x5c,
		       20000, 360,
		       0x10, 10000),
	HI6421V600_LDO(LDO16, lकरो15_voltages,
		       0x22, 0x01, 0x5d,
		       20000, 360,
		       0x10, 10000),
	HI6421V600_LDO(LDO17, lकरो17_voltages,
		       0x23, 0x01, 0x5e,
		       20000, 120,
		       0x10, 10000),
	HI6421V600_LDO(LDO33, lकरो17_voltages,
		       0x32, 0x01, 0x6d,
		       20000, 120,
		       0, 0),
	HI6421V600_LDO(LDO34, lकरो34_voltages,
		       0x33, 0x01, 0x6e,
		       20000, 120,
		       0, 0),
पूर्ण;

अटल पूर्णांक hi6421_spmi_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *pmic_dev = pdev->dev.parent;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा hi6421_spmi_reg_info *sreg;
	काष्ठा hi6421_spmi_reg_info *info;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hi6421_spmi_pmic *pmic;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	/*
	 * This driver is meant to be called by hi6421-spmi-core,
	 * which should first set drvdata. If this करोesn't happen, hit
	 * a warn on and वापस.
	 */
	pmic = dev_get_drvdata(pmic_dev);
	अगर (WARN_ON(!pmic))
		वापस -ENODEV;

	sreg = devm_kzalloc(dev, माप(*sreg), GFP_KERNEL);
	अगर (!sreg)
		वापस -ENOMEM;

	sreg->pmic = pmic;
	mutex_init(&sreg->enable_mutex);

	क्रम (i = 0; i < ARRAY_SIZE(regulator_info); i++) अणु
		info = &regulator_info[i];

		config.dev = pdev->dev.parent;
		config.driver_data = sreg;
		config.regmap = pmic->regmap;

		rdev = devm_regulator_रेजिस्टर(dev, &info->desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(dev, "failed to register %s\n",
				info->desc.name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hi6421_spmi_regulator_table[] = अणु
	अणु .name = "hi6421v600-regulator" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hi6421_spmi_regulator_table);

अटल काष्ठा platक्रमm_driver hi6421_spmi_regulator_driver = अणु
	.id_table = hi6421_spmi_regulator_table,
	.driver = अणु
		.name = "hi6421v600-regulator",
	पूर्ण,
	.probe	= hi6421_spmi_regulator_probe,
पूर्ण;
module_platक्रमm_driver(hi6421_spmi_regulator_driver);

MODULE_DESCRIPTION("Hi6421v600 SPMI regulator driver");
MODULE_LICENSE("GPL v2");

