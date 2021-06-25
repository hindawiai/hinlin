<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 * Copyright (c) 2015, Sony Mobile Communications AB
 */

#समावेश <linux/hwspinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "hwspinlock_internal.h"

#घोषणा QCOM_MUTEX_APPS_PROC_ID	1
#घोषणा QCOM_MUTEX_NUM_LOCKS	32

अटल पूर्णांक qcom_hwspinlock_trylock(काष्ठा hwspinlock *lock)
अणु
	काष्ठा regmap_field *field = lock->priv;
	u32 lock_owner;
	पूर्णांक ret;

	ret = regmap_field_ग_लिखो(field, QCOM_MUTEX_APPS_PROC_ID);
	अगर (ret)
		वापस ret;

	ret = regmap_field_पढ़ो(field, &lock_owner);
	अगर (ret)
		वापस ret;

	वापस lock_owner == QCOM_MUTEX_APPS_PROC_ID;
पूर्ण

अटल व्योम qcom_hwspinlock_unlock(काष्ठा hwspinlock *lock)
अणु
	काष्ठा regmap_field *field = lock->priv;
	u32 lock_owner;
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(field, &lock_owner);
	अगर (ret) अणु
		pr_err("%s: unable to query spinlock owner\n", __func__);
		वापस;
	पूर्ण

	अगर (lock_owner != QCOM_MUTEX_APPS_PROC_ID) अणु
		pr_err("%s: spinlock not owned by us (actual owner is %d)\n",
				__func__, lock_owner);
	पूर्ण

	ret = regmap_field_ग_लिखो(field, 0);
	अगर (ret)
		pr_err("%s: failed to unlock spinlock\n", __func__);
पूर्ण

अटल स्थिर काष्ठा hwspinlock_ops qcom_hwspinlock_ops = अणु
	.trylock	= qcom_hwspinlock_trylock,
	.unlock		= qcom_hwspinlock_unlock,
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_hwspinlock_of_match[] = अणु
	अणु .compatible = "qcom,sfpb-mutex" पूर्ण,
	अणु .compatible = "qcom,tcsr-mutex" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_hwspinlock_of_match);

अटल काष्ठा regmap *qcom_hwspinlock_probe_syscon(काष्ठा platक्रमm_device *pdev,
						   u32 *base, u32 *stride)
अणु
	काष्ठा device_node *syscon;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	syscon = of_parse_phandle(pdev->dev.of_node, "syscon", 0);
	अगर (!syscon)
		वापस ERR_PTR(-ENODEV);

	regmap = syscon_node_to_regmap(syscon);
	of_node_put(syscon);
	अगर (IS_ERR(regmap))
		वापस regmap;

	ret = of_property_पढ़ो_u32_index(pdev->dev.of_node, "syscon", 1, base);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "no offset in syscon\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ret = of_property_पढ़ो_u32_index(pdev->dev.of_node, "syscon", 2, stride);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "no stride syscon\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस regmap;
पूर्ण

अटल स्थिर काष्ठा regmap_config tcsr_mutex_config = अणु
	.reg_bits		= 32,
	.reg_stride		= 4,
	.val_bits		= 32,
	.max_रेजिस्टर		= 0x40000,
	.fast_io		= true,
पूर्ण;

अटल काष्ठा regmap *qcom_hwspinlock_probe_mmio(काष्ठा platक्रमm_device *pdev,
						 u32 *offset, u32 *stride)
अणु
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *base;

	/* All modern platक्रमm has offset 0 and stride of 4k */
	*offset = 0;
	*stride = 0x1000;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस ERR_CAST(base);

	वापस devm_regmap_init_mmio(dev, base, &tcsr_mutex_config);
पूर्ण

अटल पूर्णांक qcom_hwspinlock_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hwspinlock_device *bank;
	काष्ठा reg_field field;
	काष्ठा regmap *regmap;
	माप_प्रकार array_size;
	u32 stride;
	u32 base;
	पूर्णांक i;

	regmap = qcom_hwspinlock_probe_syscon(pdev, &base, &stride);
	अगर (IS_ERR(regmap) && PTR_ERR(regmap) == -ENODEV)
		regmap = qcom_hwspinlock_probe_mmio(pdev, &base, &stride);

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	array_size = QCOM_MUTEX_NUM_LOCKS * माप(काष्ठा hwspinlock);
	bank = devm_kzalloc(&pdev->dev, माप(*bank) + array_size, GFP_KERNEL);
	अगर (!bank)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, bank);

	क्रम (i = 0; i < QCOM_MUTEX_NUM_LOCKS; i++) अणु
		field.reg = base + i * stride;
		field.lsb = 0;
		field.msb = 31;

		bank->lock[i].priv = devm_regmap_field_alloc(&pdev->dev,
							     regmap, field);
	पूर्ण

	वापस devm_hwspin_lock_रेजिस्टर(&pdev->dev, bank, &qcom_hwspinlock_ops,
					 0, QCOM_MUTEX_NUM_LOCKS);
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_hwspinlock_driver = अणु
	.probe		= qcom_hwspinlock_probe,
	.driver		= अणु
		.name	= "qcom_hwspinlock",
		.of_match_table = qcom_hwspinlock_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init qcom_hwspinlock_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&qcom_hwspinlock_driver);
पूर्ण
/* board init code might need to reserve hwspinlocks क्रम predefined purposes */
postcore_initcall(qcom_hwspinlock_init);

अटल व्योम __निकास qcom_hwspinlock_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&qcom_hwspinlock_driver);
पूर्ण
module_निकास(qcom_hwspinlock_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Hardware spinlock driver for Qualcomm SoCs");
