<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/regulator/aat2870-regulator.c
 *
 * Copyright (c) 2011, NVIDIA Corporation.
 * Author: Jin Park <jinyoungp@nvidia.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mfd/aat2870.h>

काष्ठा aat2870_regulator अणु
	काष्ठा aat2870_data *aat2870;
	काष्ठा regulator_desc desc;

	u8 enable_addr;
	u8 enable_shअगरt;
	u8 enable_mask;

	u8 voltage_addr;
	u8 voltage_shअगरt;
	u8 voltage_mask;
पूर्ण;

अटल पूर्णांक aat2870_lकरो_set_voltage_sel(काष्ठा regulator_dev *rdev,
				       अचिन्हित selector)
अणु
	काष्ठा aat2870_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा aat2870_data *aat2870 = ri->aat2870;

	वापस aat2870->update(aat2870, ri->voltage_addr, ri->voltage_mask,
			       selector << ri->voltage_shअगरt);
पूर्ण

अटल पूर्णांक aat2870_lकरो_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा aat2870_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा aat2870_data *aat2870 = ri->aat2870;
	u8 val;
	पूर्णांक ret;

	ret = aat2870->पढ़ो(aat2870, ri->voltage_addr, &val);
	अगर (ret)
		वापस ret;

	वापस (val & ri->voltage_mask) >> ri->voltage_shअगरt;
पूर्ण

अटल पूर्णांक aat2870_lकरो_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा aat2870_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा aat2870_data *aat2870 = ri->aat2870;

	वापस aat2870->update(aat2870, ri->enable_addr, ri->enable_mask,
			       ri->enable_mask);
पूर्ण

अटल पूर्णांक aat2870_lकरो_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा aat2870_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा aat2870_data *aat2870 = ri->aat2870;

	वापस aat2870->update(aat2870, ri->enable_addr, ri->enable_mask, 0);
पूर्ण

अटल पूर्णांक aat2870_lकरो_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा aat2870_regulator *ri = rdev_get_drvdata(rdev);
	काष्ठा aat2870_data *aat2870 = ri->aat2870;
	u8 val;
	पूर्णांक ret;

	ret = aat2870->पढ़ो(aat2870, ri->enable_addr, &val);
	अगर (ret)
		वापस ret;

	वापस val & ri->enable_mask ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops aat2870_lकरो_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.set_voltage_sel = aat2870_lकरो_set_voltage_sel,
	.get_voltage_sel = aat2870_lकरो_get_voltage_sel,
	.enable = aat2870_lकरो_enable,
	.disable = aat2870_lकरो_disable,
	.is_enabled = aat2870_lकरो_is_enabled,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक aat2870_lकरो_voltages[] = अणु
	1200000, 1300000, 1500000, 1600000,
	1800000, 2000000, 2200000, 2500000,
	2600000, 2700000, 2800000, 2900000,
	3000000, 3100000, 3200000, 3300000,
पूर्ण;

#घोषणा AAT2870_LDO(ids)				\
	अणु						\
		.desc = अणु				\
			.name = #ids,			\
			.id = AAT2870_ID_##ids,		\
			.n_voltages = ARRAY_SIZE(aat2870_lकरो_voltages),	\
			.volt_table = aat2870_lकरो_voltages, \
			.ops = &aat2870_lकरो_ops,	\
			.type = REGULATOR_VOLTAGE,	\
			.owner = THIS_MODULE,		\
		पूर्ण,					\
	पूर्ण

अटल काष्ठा aat2870_regulator aat2870_regulators[] = अणु
	AAT2870_LDO(LDOA),
	AAT2870_LDO(LDOB),
	AAT2870_LDO(LDOC),
	AAT2870_LDO(LDOD),
पूर्ण;

अटल काष्ठा aat2870_regulator *aat2870_get_regulator(पूर्णांक id)
अणु
	काष्ठा aat2870_regulator *ri = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(aat2870_regulators); i++) अणु
		ri = &aat2870_regulators[i];
		अगर (ri->desc.id == id)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(aat2870_regulators))
		वापस शून्य;

	ri->enable_addr = AAT2870_LDO_EN;
	ri->enable_shअगरt = id - AAT2870_ID_LDOA;
	ri->enable_mask = 0x1 << ri->enable_shअगरt;

	ri->voltage_addr = (id - AAT2870_ID_LDOA) / 2 ?
			   AAT2870_LDO_CD : AAT2870_LDO_AB;
	ri->voltage_shअगरt = (id - AAT2870_ID_LDOA) % 2 ? 0 : 4;
	ri->voltage_mask = 0xF << ri->voltage_shअगरt;

	वापस ri;
पूर्ण

अटल पूर्णांक aat2870_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aat2870_regulator *ri;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;

	ri = aat2870_get_regulator(pdev->id);
	अगर (!ri) अणु
		dev_err(&pdev->dev, "Invalid device ID, %d\n", pdev->id);
		वापस -EINVAL;
	पूर्ण
	ri->aat2870 = dev_get_drvdata(pdev->dev.parent);

	config.dev = &pdev->dev;
	config.driver_data = ri;
	config.init_data = dev_get_platdata(&pdev->dev);

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &ri->desc, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(&pdev->dev, "Failed to register regulator %s\n",
			ri->desc.name);
		वापस PTR_ERR(rdev);
	पूर्ण
	platक्रमm_set_drvdata(pdev, rdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aat2870_regulator_driver = अणु
	.driver = अणु
		.name	= "aat2870-regulator",
	पूर्ण,
	.probe	= aat2870_regulator_probe,
पूर्ण;

अटल पूर्णांक __init aat2870_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&aat2870_regulator_driver);
पूर्ण
subsys_initcall(aat2870_regulator_init);

अटल व्योम __निकास aat2870_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&aat2870_regulator_driver);
पूर्ण
module_निकास(aat2870_regulator_निकास);

MODULE_DESCRIPTION("AnalogicTech AAT2870 Regulator");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jin Park <jinyoungp@nvidia.com>");
MODULE_ALIAS("platform:aat2870-regulator");
