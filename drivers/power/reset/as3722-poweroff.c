<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Power off driver क्रम ams AS3722 device.
 *
 * Copyright (c) 2013, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */

#समावेश <linux/mfd/as3722.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

काष्ठा as3722_घातeroff अणु
	काष्ठा device *dev;
	काष्ठा as3722 *as3722;
पूर्ण;

अटल काष्ठा as3722_घातeroff *as3722_pm_घातeroff;

अटल व्योम as3722_pm_घातer_off(व्योम)
अणु
	पूर्णांक ret;

	अगर (!as3722_pm_घातeroff) अणु
		pr_err("AS3722 poweroff is not initialised\n");
		वापस;
	पूर्ण

	ret = as3722_update_bits(as3722_pm_घातeroff->as3722,
		AS3722_RESET_CONTROL_REG, AS3722_POWER_OFF, AS3722_POWER_OFF);
	अगर (ret < 0)
		dev_err(as3722_pm_घातeroff->dev,
			"RESET_CONTROL_REG update failed, %d\n", ret);
पूर्ण

अटल पूर्णांक as3722_घातeroff_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा as3722_घातeroff *as3722_घातeroff;
	काष्ठा device_node *np = pdev->dev.parent->of_node;

	अगर (!np)
		वापस -EINVAL;

	अगर (!of_property_पढ़ो_bool(np, "ams,system-power-controller"))
		वापस 0;

	as3722_घातeroff = devm_kzalloc(&pdev->dev, माप(*as3722_घातeroff),
				GFP_KERNEL);
	अगर (!as3722_घातeroff)
		वापस -ENOMEM;

	as3722_घातeroff->as3722 = dev_get_drvdata(pdev->dev.parent);
	as3722_घातeroff->dev = &pdev->dev;
	as3722_pm_घातeroff = as3722_घातeroff;
	अगर (!pm_घातer_off)
		pm_घातer_off = as3722_pm_घातer_off;

	वापस 0;
पूर्ण

अटल पूर्णांक as3722_घातeroff_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pm_घातer_off == as3722_pm_घातer_off)
		pm_घातer_off = शून्य;
	as3722_pm_घातeroff = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver as3722_घातeroff_driver = अणु
	.driver = अणु
		.name = "as3722-power-off",
	पूर्ण,
	.probe = as3722_घातeroff_probe,
	.हटाओ = as3722_घातeroff_हटाओ,
पूर्ण;

module_platक्रमm_driver(as3722_घातeroff_driver);

MODULE_DESCRIPTION("Power off driver for ams AS3722 PMIC Device");
MODULE_ALIAS("platform:as3722-power-off");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
