<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max77693.c - Regulator driver क्रम the Maxim 77693 and 77843
//
// Copyright (C) 2013-2015 Samsung Electronics
// Jonghwa Lee <jonghwa3.lee@samsung.com>
// Krzysztof Kozlowski <krzk@kernel.org>
//
// This driver is based on max77686.c

#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mfd/max77693.h>
#समावेश <linux/mfd/max77693-common.h>
#समावेश <linux/mfd/max77693-निजी.h>
#समावेश <linux/mfd/max77843-निजी.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regmap.h>

/*
 * ID क्रम MAX77843 regulators.
 * There is no need क्रम such क्रम MAX77693.
 */
क्रमागत max77843_regulator_type अणु
	MAX77843_SAFEOUT1 = 0,
	MAX77843_SAFEOUT2,
	MAX77843_CHARGER,

	MAX77843_NUM,
पूर्ण;

/* Register dअगरferences between अक्षरgers: MAX77693 and MAX77843 */
काष्ठा chg_reg_data अणु
	अचिन्हित पूर्णांक linear_reg;
	अचिन्हित पूर्णांक linear_mask;
	अचिन्हित पूर्णांक uA_step;
	अचिन्हित पूर्णांक min_sel;
पूर्ण;

/*
 * MAX77693 CHARGER regulator - Min : 20mA, Max : 2580mA, step : 20mA
 * 0x00, 0x01, 0x2, 0x03	= 60 mA
 * 0x04 ~ 0x7E			= (60 + (X - 3) * 20) mA
 * Actually क्रम MAX77693 the driver manipulates the maximum input current,
 * not the fast अक्षरge current (output). This should be fixed.
 *
 * On MAX77843 the calculation क्रमmula is the same (except values).
 * Fortunately it properly manipulates the fast अक्षरge current.
 */
अटल पूर्णांक max77693_chg_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	स्थिर काष्ठा chg_reg_data *reg_data = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक chg_min_uA = rdev->स्थिरraपूर्णांकs->min_uA;
	अचिन्हित पूर्णांक chg_max_uA = rdev->स्थिरraपूर्णांकs->max_uA;
	अचिन्हित पूर्णांक reg, sel;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rdev->regmap, reg_data->linear_reg, &reg);
	अगर (ret < 0)
		वापस ret;

	sel = reg & reg_data->linear_mask;

	/* the first four codes क्रम अक्षरger current are all 60mA */
	अगर (sel <= reg_data->min_sel)
		sel = 0;
	अन्यथा
		sel -= reg_data->min_sel;

	val = chg_min_uA + reg_data->uA_step * sel;
	अगर (val > chg_max_uA)
		वापस -EINVAL;

	वापस val;
पूर्ण

अटल पूर्णांक max77693_chg_set_current_limit(काष्ठा regulator_dev *rdev,
						पूर्णांक min_uA, पूर्णांक max_uA)
अणु
	स्थिर काष्ठा chg_reg_data *reg_data = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक chg_min_uA = rdev->स्थिरraपूर्णांकs->min_uA;
	पूर्णांक sel = 0;

	जबतक (chg_min_uA + reg_data->uA_step * sel < min_uA)
		sel++;

	अगर (chg_min_uA + reg_data->uA_step * sel > max_uA)
		वापस -EINVAL;

	/* the first four codes क्रम अक्षरger current are all 60mA */
	sel += reg_data->min_sel;

	वापस regmap_ग_लिखो(rdev->regmap, reg_data->linear_reg, sel);
पूर्ण
/* end of CHARGER regulator ops */

/* Returns regmap suitable क्रम given regulator on chosen device */
अटल काष्ठा regmap *max77693_get_regmap(क्रमागत max77693_types type,
					  काष्ठा max77693_dev *max77693,
					  पूर्णांक reg_id)
अणु
	अगर (type == TYPE_MAX77693)
		वापस max77693->regmap;

	/* Else: TYPE_MAX77843 */
	चयन (reg_id) अणु
	हाल MAX77843_SAFEOUT1:
	हाल MAX77843_SAFEOUT2:
		वापस max77693->regmap;
	हाल MAX77843_CHARGER:
		वापस max77693->regmap_chg;
	शेष:
		वापस max77693->regmap;
	पूर्ण
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक max77693_safeout_table[] = अणु
	4850000,
	4900000,
	4950000,
	3300000,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max77693_safeout_ops = अणु
	.list_voltage		= regulator_list_voltage_table,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max77693_अक्षरger_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_current_limit	= max77693_chg_get_current_limit,
	.set_current_limit	= max77693_chg_set_current_limit,
पूर्ण;

#घोषणा max77693_regulator_desc_esafeout(_num)	अणु		\
	.name		= "ESAFEOUT"#_num,			\
	.id		= MAX77693_ESAFEOUT##_num,		\
	.of_match	= of_match_ptr("ESAFEOUT"#_num),	\
	.regulators_node	= of_match_ptr("regulators"),	\
	.n_voltages	= 4,					\
	.ops		= &max77693_safeout_ops,		\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.volt_table	= max77693_safeout_table,		\
	.vsel_reg	= MAX77693_CHG_REG_SAFEOUT_CTRL,	\
	.vsel_mask	= SAFEOUT_CTRL_SAFEOUT##_num##_MASK,	\
	.enable_reg	= MAX77693_CHG_REG_SAFEOUT_CTRL,	\
	.enable_mask	= SAFEOUT_CTRL_ENSAFEOUT##_num##_MASK ,	\
पूर्ण

अटल स्थिर काष्ठा regulator_desc max77693_supported_regulators[] = अणु
	max77693_regulator_desc_esafeout(1),
	max77693_regulator_desc_esafeout(2),
	अणु
		.name = "CHARGER",
		.id = MAX77693_CHARGER,
		.of_match = of_match_ptr("CHARGER"),
		.regulators_node = of_match_ptr("regulators"),
		.ops = &max77693_अक्षरger_ops,
		.type = REGULATOR_CURRENT,
		.owner = THIS_MODULE,
		.enable_reg = MAX77693_CHG_REG_CHG_CNFG_00,
		.enable_mask = CHG_CNFG_00_CHG_MASK |
				CHG_CNFG_00_BUCK_MASK,
		.enable_val = CHG_CNFG_00_CHG_MASK | CHG_CNFG_00_BUCK_MASK,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा chg_reg_data max77693_chg_reg_data = अणु
	.linear_reg	= MAX77693_CHG_REG_CHG_CNFG_09,
	.linear_mask	= CHG_CNFG_09_CHGIN_ILIM_MASK,
	.uA_step	= 20000,
	.min_sel	= 3,
पूर्ण;

#घोषणा	max77843_regulator_desc_esafeout(num)	अणु			\
	.name		= "SAFEOUT" # num,				\
	.id		= MAX77843_SAFEOUT ## num,			\
	.ops		= &max77693_safeout_ops,			\
	.of_match	= of_match_ptr("SAFEOUT" # num),		\
	.regulators_node = of_match_ptr("regulators"),			\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.n_voltages	= ARRAY_SIZE(max77693_safeout_table),		\
	.volt_table	= max77693_safeout_table,			\
	.enable_reg	= MAX77843_SYS_REG_SAFEOUTCTRL,			\
	.enable_mask	= MAX77843_REG_SAFEOUTCTRL_ENSAFEOUT ## num,	\
	.vsel_reg	= MAX77843_SYS_REG_SAFEOUTCTRL,			\
	.vsel_mask	= MAX77843_REG_SAFEOUTCTRL_SAFEOUT ## num ## _MASK, \
पूर्ण

अटल स्थिर काष्ठा regulator_desc max77843_supported_regulators[] = अणु
	[MAX77843_SAFEOUT1] = max77843_regulator_desc_esafeout(1),
	[MAX77843_SAFEOUT2] = max77843_regulator_desc_esafeout(2),
	[MAX77843_CHARGER] = अणु
		.name		= "CHARGER",
		.id		= MAX77843_CHARGER,
		.ops		= &max77693_अक्षरger_ops,
		.of_match	= of_match_ptr("CHARGER"),
		.regulators_node = of_match_ptr("regulators"),
		.type		= REGULATOR_CURRENT,
		.owner		= THIS_MODULE,
		.enable_reg	= MAX77843_CHG_REG_CHG_CNFG_00,
		.enable_mask	= MAX77843_CHG_MASK,
		.enable_val	= MAX77843_CHG_MASK,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा chg_reg_data max77843_chg_reg_data = अणु
	.linear_reg	= MAX77843_CHG_REG_CHG_CNFG_02,
	.linear_mask	= MAX77843_CHG_FAST_CHG_CURRENT_MASK,
	.uA_step	= MAX77843_CHG_FAST_CHG_CURRENT_STEP,
	.min_sel	= 2,
पूर्ण;

अटल पूर्णांक max77693_pmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	क्रमागत max77693_types type = platक्रमm_get_device_id(pdev)->driver_data;
	काष्ठा max77693_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	स्थिर काष्ठा regulator_desc *regulators;
	अचिन्हित पूर्णांक regulators_size;
	पूर्णांक i;
	काष्ठा regulator_config config = अणु पूर्ण;

	config.dev = iodev->dev;

	चयन (type) अणु
	हाल TYPE_MAX77693:
		regulators = max77693_supported_regulators;
		regulators_size = ARRAY_SIZE(max77693_supported_regulators);
		config.driver_data = (व्योम *)&max77693_chg_reg_data;
		अवरोध;
	हाल TYPE_MAX77843:
		regulators = max77843_supported_regulators;
		regulators_size = ARRAY_SIZE(max77843_supported_regulators);
		config.driver_data = (व्योम *)&max77843_chg_reg_data;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported device type: %u\n", type);
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < regulators_size; i++) अणु
		काष्ठा regulator_dev *rdev;

		config.regmap = max77693_get_regmap(type, iodev,
						    regulators[i].id);

		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
						&regulators[i], &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev,
				"Failed to initialize regulator-%d\n", i);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max77693_pmic_id[] = अणु
	अणु "max77693-pmic", TYPE_MAX77693 पूर्ण,
	अणु "max77843-regulator", TYPE_MAX77843 पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(platक्रमm, max77693_pmic_id);

अटल काष्ठा platक्रमm_driver max77693_pmic_driver = अणु
	.driver = अणु
		   .name = "max77693-pmic",
		   पूर्ण,
	.probe = max77693_pmic_probe,
	.id_table = max77693_pmic_id,
पूर्ण;

अटल पूर्णांक __init max77693_pmic_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&max77693_pmic_driver);
पूर्ण
subsys_initcall(max77693_pmic_init);

अटल व्योम __निकास max77693_pmic_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&max77693_pmic_driver);
पूर्ण
module_निकास(max77693_pmic_cleanup);

MODULE_DESCRIPTION("MAXIM 77693/77843 regulator driver");
MODULE_AUTHOR("Jonghwa Lee <jonghwa3.lee@samsung.com>");
MODULE_AUTHOR("Krzysztof Kozlowski <krzk@kernel.org>");
MODULE_LICENSE("GPL");
