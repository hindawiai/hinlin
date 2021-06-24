<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulators driver क्रम Maxim max8925
 *
 * Copyright (C) 2009 Marvell International Ltd.
 *      Haojian Zhuang <haojian.zhuang@marvell.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mfd/max8925.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा SD1_DVM_VMIN		850000
#घोषणा SD1_DVM_VMAX		1000000
#घोषणा SD1_DVM_STEP		50000
#घोषणा SD1_DVM_SHIFT		5		/* SDCTL1 bit5 */
#घोषणा SD1_DVM_EN		6		/* SDV1 bit 6 */

/* bit definitions in LDO control रेजिस्टरs */
#घोषणा LDO_SEQ_I2C		0x7		/* Power U/D by i2c */
#घोषणा LDO_SEQ_MASK		0x7		/* Power U/D sequence mask */
#घोषणा LDO_SEQ_SHIFT		2		/* Power U/D sequence offset */
#घोषणा LDO_I2C_EN		0x1		/* Enable by i2c */
#घोषणा LDO_I2C_EN_MASK		0x1		/* Enable mask by i2c */
#घोषणा LDO_I2C_EN_SHIFT	0		/* Enable offset by i2c */

काष्ठा max8925_regulator_info अणु
	काष्ठा regulator_desc	desc;
	काष्ठा i2c_client	*i2c;

	पूर्णांक	vol_reg;
	पूर्णांक	enable_reg;
पूर्ण;

अटल पूर्णांक max8925_set_voltage_sel(काष्ठा regulator_dev *rdev,
				   अचिन्हित पूर्णांक selector)
अणु
	काष्ठा max8925_regulator_info *info = rdev_get_drvdata(rdev);
	अचिन्हित अक्षर mask = rdev->desc->n_voltages - 1;

	वापस max8925_set_bits(info->i2c, info->vol_reg, mask, selector);
पूर्ण

अटल पूर्णांक max8925_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8925_regulator_info *info = rdev_get_drvdata(rdev);
	अचिन्हित अक्षर data, mask;
	पूर्णांक ret;

	ret = max8925_reg_पढ़ो(info->i2c, info->vol_reg);
	अगर (ret < 0)
		वापस ret;
	mask = rdev->desc->n_voltages - 1;
	data = ret & mask;

	वापस data;
पूर्ण

अटल पूर्णांक max8925_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8925_regulator_info *info = rdev_get_drvdata(rdev);

	वापस max8925_set_bits(info->i2c, info->enable_reg,
				LDO_SEQ_MASK << LDO_SEQ_SHIFT |
				LDO_I2C_EN_MASK << LDO_I2C_EN_SHIFT,
				LDO_SEQ_I2C << LDO_SEQ_SHIFT |
				LDO_I2C_EN << LDO_I2C_EN_SHIFT);
पूर्ण

अटल पूर्णांक max8925_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8925_regulator_info *info = rdev_get_drvdata(rdev);

	वापस max8925_set_bits(info->i2c, info->enable_reg,
				LDO_SEQ_MASK << LDO_SEQ_SHIFT |
				LDO_I2C_EN_MASK << LDO_I2C_EN_SHIFT,
				LDO_SEQ_I2C << LDO_SEQ_SHIFT);
पूर्ण

अटल पूर्णांक max8925_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8925_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक lकरो_seq, ret;

	ret = max8925_reg_पढ़ो(info->i2c, info->enable_reg);
	अगर (ret < 0)
		वापस ret;
	lकरो_seq = (ret >> LDO_SEQ_SHIFT) & LDO_SEQ_MASK;
	अगर (lकरो_seq != LDO_SEQ_I2C)
		वापस 1;
	अन्यथा
		वापस ret & (LDO_I2C_EN_MASK << LDO_I2C_EN_SHIFT);
पूर्ण

अटल पूर्णांक max8925_set_dvm_voltage(काष्ठा regulator_dev *rdev, पूर्णांक uV)
अणु
	काष्ठा max8925_regulator_info *info = rdev_get_drvdata(rdev);
	अचिन्हित अक्षर data, mask;

	अगर (uV < SD1_DVM_VMIN || uV > SD1_DVM_VMAX)
		वापस -EINVAL;

	data = DIV_ROUND_UP(uV - SD1_DVM_VMIN, SD1_DVM_STEP);
	data <<= SD1_DVM_SHIFT;
	mask = 3 << SD1_DVM_SHIFT;

	वापस max8925_set_bits(info->i2c, info->enable_reg, mask, data);
पूर्ण

अटल पूर्णांक max8925_set_dvm_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8925_regulator_info *info = rdev_get_drvdata(rdev);

	वापस max8925_set_bits(info->i2c, info->vol_reg, 1 << SD1_DVM_EN,
				1 << SD1_DVM_EN);
पूर्ण

अटल पूर्णांक max8925_set_dvm_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8925_regulator_info *info = rdev_get_drvdata(rdev);

	वापस max8925_set_bits(info->i2c, info->vol_reg, 1 << SD1_DVM_EN, 0);
पूर्ण

अटल स्थिर काष्ठा regulator_ops max8925_regulator_sdv_ops = अणु
	.map_voltage		= regulator_map_voltage_linear,
	.list_voltage		= regulator_list_voltage_linear,
	.set_voltage_sel	= max8925_set_voltage_sel,
	.get_voltage_sel	= max8925_get_voltage_sel,
	.enable			= max8925_enable,
	.disable		= max8925_disable,
	.is_enabled		= max8925_is_enabled,
	.set_suspend_voltage	= max8925_set_dvm_voltage,
	.set_suspend_enable	= max8925_set_dvm_enable,
	.set_suspend_disable	= max8925_set_dvm_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8925_regulator_lकरो_ops = अणु
	.map_voltage		= regulator_map_voltage_linear,
	.list_voltage		= regulator_list_voltage_linear,
	.set_voltage_sel	= max8925_set_voltage_sel,
	.get_voltage_sel	= max8925_get_voltage_sel,
	.enable			= max8925_enable,
	.disable		= max8925_disable,
	.is_enabled		= max8925_is_enabled,
पूर्ण;

#घोषणा MAX8925_SDV(_id, min, max, step)			\
अणु								\
	.desc	= अणु						\
		.name	= "SDV" #_id,				\
		.of_match = of_match_ptr("SDV" #_id),		\
		.regulators_node = of_match_ptr("regulators"),	\
		.ops	= &max8925_regulator_sdv_ops,		\
		.type	= REGULATOR_VOLTAGE,			\
		.id	= MAX8925_ID_SD##_id,			\
		.owner	= THIS_MODULE,				\
		.n_voltages = 64,				\
		.min_uV = min * 1000,				\
		.uV_step = step * 1000,				\
	पूर्ण,							\
	.vol_reg	= MAX8925_SDV##_id,			\
	.enable_reg	= MAX8925_SDCTL##_id,			\
पूर्ण

#घोषणा MAX8925_LDO(_id, min, max, step)			\
अणु								\
	.desc	= अणु						\
		.name	= "LDO" #_id,				\
		.of_match = of_match_ptr("LDO" #_id),		\
		.regulators_node = of_match_ptr("regulators"),	\
		.ops	= &max8925_regulator_lकरो_ops,		\
		.type	= REGULATOR_VOLTAGE,			\
		.id	= MAX8925_ID_LDO##_id,			\
		.owner	= THIS_MODULE,				\
		.n_voltages = 64,				\
		.min_uV = min * 1000,				\
		.uV_step = step * 1000,				\
	पूर्ण,							\
	.vol_reg	= MAX8925_LDOVOUT##_id,			\
	.enable_reg	= MAX8925_LDOCTL##_id,			\
पूर्ण

अटल काष्ठा max8925_regulator_info max8925_regulator_info[] = अणु
	MAX8925_SDV(1, 637.5, 1425, 12.5),
	MAX8925_SDV(2,   650, 2225,   25),
	MAX8925_SDV(3,   750, 3900,   50),

	MAX8925_LDO(1,  750, 3900, 50),
	MAX8925_LDO(2,  650, 2250, 25),
	MAX8925_LDO(3,  650, 2250, 25),
	MAX8925_LDO(4,  750, 3900, 50),
	MAX8925_LDO(5,  750, 3900, 50),
	MAX8925_LDO(6,  750, 3900, 50),
	MAX8925_LDO(7,  750, 3900, 50),
	MAX8925_LDO(8,  750, 3900, 50),
	MAX8925_LDO(9,  750, 3900, 50),
	MAX8925_LDO(10, 750, 3900, 50),
	MAX8925_LDO(11, 750, 3900, 50),
	MAX8925_LDO(12, 750, 3900, 50),
	MAX8925_LDO(13, 750, 3900, 50),
	MAX8925_LDO(14, 750, 3900, 50),
	MAX8925_LDO(15, 750, 3900, 50),
	MAX8925_LDO(16, 750, 3900, 50),
	MAX8925_LDO(17, 650, 2250, 25),
	MAX8925_LDO(18, 650, 2250, 25),
	MAX8925_LDO(19, 750, 3900, 50),
	MAX8925_LDO(20, 750, 3900, 50),
पूर्ण;

अटल पूर्णांक max8925_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_init_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा max8925_regulator_info *ri;
	काष्ठा resource *res;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	res = platक्रमm_get_resource(pdev, IORESOURCE_REG, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "No REG resource!\n");
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(max8925_regulator_info); i++) अणु
		ri = &max8925_regulator_info[i];
		अगर (ri->vol_reg == res->start)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(max8925_regulator_info)) अणु
		dev_err(&pdev->dev, "Failed to find regulator %llu\n",
			(अचिन्हित दीर्घ दीर्घ)res->start);
		वापस -EINVAL;
	पूर्ण
	ri->i2c = chip->i2c;

	config.dev = chip->dev;
	config.driver_data = ri;

	अगर (pdata)
		config.init_data = pdata;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &ri->desc, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(&pdev->dev, "failed to register regulator %s\n",
				ri->desc.name);
		वापस PTR_ERR(rdev);
	पूर्ण

	platक्रमm_set_drvdata(pdev, rdev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver max8925_regulator_driver = अणु
	.driver		= अणु
		.name	= "max8925-regulator",
	पूर्ण,
	.probe		= max8925_regulator_probe,
पूर्ण;

अटल पूर्णांक __init max8925_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&max8925_regulator_driver);
पूर्ण
subsys_initcall(max8925_regulator_init);

अटल व्योम __निकास max8925_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&max8925_regulator_driver);
पूर्ण
module_निकास(max8925_regulator_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_DESCRIPTION("Regulator Driver for Maxim 8925 PMIC");
MODULE_ALIAS("platform:max8925-regulator");
