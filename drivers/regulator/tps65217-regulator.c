<शैली गुरु>
/*
 * tps65217-regulator.c
 *
 * Regulator driver क्रम TPS65217 PMIC
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mfd/tps65217.h>

#घोषणा TPS65217_REGULATOR(_name, _id, _of_match, _ops, _n, _vr, _vm, _em, \
			   _t, _lr, _nlr,  _sr, _sm)	\
	अणु						\
		.name		= _name,		\
		.id		= _id,			\
		.of_match       = of_match_ptr(_of_match),    \
		.regulators_node= of_match_ptr("regulators"), \
		.ops		= &_ops,		\
		.n_voltages	= _n,			\
		.type		= REGULATOR_VOLTAGE,	\
		.owner		= THIS_MODULE,		\
		.vsel_reg	= _vr,			\
		.vsel_mask	= _vm,			\
		.enable_reg	= TPS65217_REG_ENABLE,	\
		.enable_mask	= _em,			\
		.volt_table	= _t,			\
		.linear_ranges	= _lr,			\
		.n_linear_ranges = _nlr,		\
		.bypass_reg	= _sr,			\
		.bypass_mask	= _sm,			\
	पूर्ण						\

अटल स्थिर अचिन्हित पूर्णांक LDO1_VSEL_table[] = अणु
	1000000, 1100000, 1200000, 1250000,
	1300000, 1350000, 1400000, 1500000,
	1600000, 1800000, 2500000, 2750000,
	2800000, 3000000, 3100000, 3300000,
पूर्ण;

अटल स्थिर काष्ठा linear_range tps65217_uv1_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(900000, 0, 24, 25000),
	REGULATOR_LINEAR_RANGE(1550000, 25, 52, 50000),
	REGULATOR_LINEAR_RANGE(3000000, 53, 55, 100000),
	REGULATOR_LINEAR_RANGE(3300000, 56, 63, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range tps65217_uv2_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1500000, 0, 8, 50000),
	REGULATOR_LINEAR_RANGE(2000000, 9, 13, 100000),
	REGULATOR_LINEAR_RANGE(2450000, 14, 31, 50000),
पूर्ण;

अटल पूर्णांक tps65217_pmic_enable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps65217 *tps = rdev_get_drvdata(dev);
	पूर्णांक rid = rdev_get_id(dev);

	अगर (rid < TPS65217_DCDC_1 || rid > TPS65217_LDO_4)
		वापस -EINVAL;

	/* Enable the regulator and password protection is level 1 */
	वापस tps65217_set_bits(tps, TPS65217_REG_ENABLE,
				 dev->desc->enable_mask, dev->desc->enable_mask,
				 TPS65217_PROTECT_L1);
पूर्ण

अटल पूर्णांक tps65217_pmic_disable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps65217 *tps = rdev_get_drvdata(dev);
	पूर्णांक rid = rdev_get_id(dev);

	अगर (rid < TPS65217_DCDC_1 || rid > TPS65217_LDO_4)
		वापस -EINVAL;

	/* Disable the regulator and password protection is level 1 */
	वापस tps65217_clear_bits(tps, TPS65217_REG_ENABLE,
				   dev->desc->enable_mask, TPS65217_PROTECT_L1);
पूर्ण

अटल पूर्णांक tps65217_pmic_set_voltage_sel(काष्ठा regulator_dev *dev,
					 अचिन्हित selector)
अणु
	पूर्णांक ret;
	काष्ठा tps65217 *tps = rdev_get_drvdata(dev);
	अचिन्हित पूर्णांक rid = rdev_get_id(dev);

	/* Set the voltage based on vsel value and ग_लिखो protect level is 2 */
	ret = tps65217_set_bits(tps, dev->desc->vsel_reg, dev->desc->vsel_mask,
				selector, TPS65217_PROTECT_L2);

	/* Set GO bit क्रम DCDCx to initiate voltage transistion */
	चयन (rid) अणु
	हाल TPS65217_DCDC_1 ... TPS65217_DCDC_3:
		ret = tps65217_set_bits(tps, TPS65217_REG_DEFSLEW,
				       TPS65217_DEFSLEW_GO, TPS65217_DEFSLEW_GO,
				       TPS65217_PROTECT_L2);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tps65217_pmic_set_suspend_enable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps65217 *tps = rdev_get_drvdata(dev);
	अचिन्हित पूर्णांक rid = rdev_get_id(dev);

	अगर (rid > TPS65217_LDO_4)
		वापस -EINVAL;

	वापस tps65217_clear_bits(tps, dev->desc->bypass_reg,
				   dev->desc->bypass_mask,
				   TPS65217_PROTECT_L1);
पूर्ण

अटल पूर्णांक tps65217_pmic_set_suspend_disable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps65217 *tps = rdev_get_drvdata(dev);
	अचिन्हित पूर्णांक rid = rdev_get_id(dev);

	अगर (rid > TPS65217_LDO_4)
		वापस -EINVAL;

	अगर (!tps->strobes[rid])
		वापस -EINVAL;

	वापस tps65217_set_bits(tps, dev->desc->bypass_reg,
				 dev->desc->bypass_mask,
				 tps->strobes[rid], TPS65217_PROTECT_L1);
पूर्ण

/* Operations permitted on DCDCx, LDO2, LDO3 and LDO4 */
अटल स्थिर काष्ठा regulator_ops tps65217_pmic_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= tps65217_pmic_enable,
	.disable		= tps65217_pmic_disable,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= tps65217_pmic_set_voltage_sel,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.set_suspend_enable	= tps65217_pmic_set_suspend_enable,
	.set_suspend_disable	= tps65217_pmic_set_suspend_disable,
पूर्ण;

/* Operations permitted on LDO1 */
अटल स्थिर काष्ठा regulator_ops tps65217_pmic_lकरो1_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= tps65217_pmic_enable,
	.disable		= tps65217_pmic_disable,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= tps65217_pmic_set_voltage_sel,
	.list_voltage		= regulator_list_voltage_table,
	.map_voltage		= regulator_map_voltage_ascend,
	.set_suspend_enable	= tps65217_pmic_set_suspend_enable,
	.set_suspend_disable	= tps65217_pmic_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc regulators[] = अणु
	TPS65217_REGULATOR("DCDC1", TPS65217_DCDC_1, "dcdc1",
			   tps65217_pmic_ops, 64, TPS65217_REG_DEFDCDC1,
			   TPS65217_DEFDCDCX_DCDC_MASK, TPS65217_ENABLE_DC1_EN,
			   शून्य, tps65217_uv1_ranges,
			   ARRAY_SIZE(tps65217_uv1_ranges), TPS65217_REG_SEQ1,
			   TPS65217_SEQ1_DC1_SEQ_MASK),
	TPS65217_REGULATOR("DCDC2", TPS65217_DCDC_2, "dcdc2",
			   tps65217_pmic_ops, 64, TPS65217_REG_DEFDCDC2,
			   TPS65217_DEFDCDCX_DCDC_MASK, TPS65217_ENABLE_DC2_EN,
			   शून्य, tps65217_uv1_ranges,
			   ARRAY_SIZE(tps65217_uv1_ranges), TPS65217_REG_SEQ1,
			   TPS65217_SEQ1_DC2_SEQ_MASK),
	TPS65217_REGULATOR("DCDC3", TPS65217_DCDC_3, "dcdc3",
			   tps65217_pmic_ops, 64, TPS65217_REG_DEFDCDC3,
			   TPS65217_DEFDCDCX_DCDC_MASK, TPS65217_ENABLE_DC3_EN,
			   शून्य, tps65217_uv1_ranges,
			   ARRAY_SIZE(tps65217_uv1_ranges), TPS65217_REG_SEQ2,
			   TPS65217_SEQ2_DC3_SEQ_MASK),
	TPS65217_REGULATOR("LDO1", TPS65217_LDO_1, "ldo1",
			   tps65217_pmic_lकरो1_ops, 16, TPS65217_REG_DEFLDO1,
			   TPS65217_DEFLDO1_LDO1_MASK, TPS65217_ENABLE_LDO1_EN,
			   LDO1_VSEL_table, शून्य, 0, TPS65217_REG_SEQ2,
			   TPS65217_SEQ2_LDO1_SEQ_MASK),
	TPS65217_REGULATOR("LDO2", TPS65217_LDO_2, "ldo2", tps65217_pmic_ops,
			   64, TPS65217_REG_DEFLDO2,
			   TPS65217_DEFLDO2_LDO2_MASK, TPS65217_ENABLE_LDO2_EN,
			   शून्य, tps65217_uv1_ranges,
			   ARRAY_SIZE(tps65217_uv1_ranges), TPS65217_REG_SEQ3,
			   TPS65217_SEQ3_LDO2_SEQ_MASK),
	TPS65217_REGULATOR("LDO3", TPS65217_LDO_3, "ldo3", tps65217_pmic_ops,
			   32, TPS65217_REG_DEFLS1, TPS65217_DEFLDO3_LDO3_MASK,
			   TPS65217_ENABLE_LS1_EN | TPS65217_DEFLDO3_LDO3_EN,
			   शून्य, tps65217_uv2_ranges,
			   ARRAY_SIZE(tps65217_uv2_ranges), TPS65217_REG_SEQ3,
			   TPS65217_SEQ3_LDO3_SEQ_MASK),
	TPS65217_REGULATOR("LDO4", TPS65217_LDO_4, "ldo4", tps65217_pmic_ops,
			   32, TPS65217_REG_DEFLS2, TPS65217_DEFLDO4_LDO4_MASK,
			   TPS65217_ENABLE_LS2_EN | TPS65217_DEFLDO4_LDO4_EN,
			   शून्य, tps65217_uv2_ranges,
			   ARRAY_SIZE(tps65217_uv2_ranges), TPS65217_REG_SEQ4,
			   TPS65217_SEQ4_LDO4_SEQ_MASK),
पूर्ण;

अटल पूर्णांक tps65217_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65217 *tps = dev_get_drvdata(pdev->dev.parent);
	काष्ठा tps65217_board *pdata = dev_get_platdata(tps->dev);
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक val;

	/* Allocate memory क्रम strobes */
	tps->strobes = devm_kसुस्मृति(&pdev->dev,
				    TPS65217_NUM_REGULATOR, माप(u8),
				    GFP_KERNEL);
	अगर (!tps->strobes)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, tps);

	क्रम (i = 0; i < TPS65217_NUM_REGULATOR; i++) अणु
		/* Register the regulators */
		config.dev = tps->dev;
		अगर (pdata)
			config.init_data = pdata->tps65217_init_data[i];
		config.driver_data = tps;
		config.regmap = tps->regmap;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(tps->dev, "failed to register %s regulator\n",
				pdev->name);
			वापस PTR_ERR(rdev);
		पूर्ण

		/* Store शेष strobe info */
		ret = tps65217_reg_पढ़ो(tps, regulators[i].bypass_reg, &val);
		अगर (ret)
			वापस ret;

		tps->strobes[i] = val & regulators[i].bypass_mask;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tps65217_regulator_driver = अणु
	.driver = अणु
		.name = "tps65217-pmic",
	पूर्ण,
	.probe = tps65217_regulator_probe,
पूर्ण;

अटल पूर्णांक __init tps65217_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tps65217_regulator_driver);
पूर्ण
subsys_initcall(tps65217_regulator_init);

अटल व्योम __निकास tps65217_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tps65217_regulator_driver);
पूर्ण
module_निकास(tps65217_regulator_निकास);

MODULE_AUTHOR("AnilKumar Ch <anilkumar@ti.com>");
MODULE_DESCRIPTION("TPS65217 voltage regulator driver");
MODULE_ALIAS("platform:tps65217-pmic");
MODULE_LICENSE("GPL v2");
