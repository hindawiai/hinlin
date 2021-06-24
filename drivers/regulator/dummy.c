<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dummy.c
 *
 * Copyright 2010 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *
 * This is useful क्रम प्रणालीs with mixed controllable and
 * non-controllable regulators, as well as क्रम allowing testing on
 * प्रणालीs with no controllable regulators.
 */

#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>

#समावेश "dummy.h"

काष्ठा regulator_dev *dummy_regulator_rdev;

अटल स्थिर काष्ठा regulator_init_data dummy_initdata = अणु
	.स्थिरraपूर्णांकs = अणु
		.always_on = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops dummy_ops;

अटल स्थिर काष्ठा regulator_desc dummy_desc = अणु
	.name = "regulator-dummy",
	.id = -1,
	.type = REGULATOR_VOLTAGE,
	.owner = THIS_MODULE,
	.ops = &dummy_ops,
पूर्ण;

अटल पूर्णांक dummy_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक ret;

	config.dev = &pdev->dev;
	config.init_data = &dummy_initdata;

	dummy_regulator_rdev = regulator_रेजिस्टर(&dummy_desc, &config);
	अगर (IS_ERR(dummy_regulator_rdev)) अणु
		ret = PTR_ERR(dummy_regulator_rdev);
		pr_err("Failed to register regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dummy_regulator_driver = अणु
	.probe		= dummy_regulator_probe,
	.driver		= अणु
		.name		= "reg-dummy",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *dummy_pdev;

व्योम __init regulator_dummy_init(व्योम)
अणु
	पूर्णांक ret;

	dummy_pdev = platक्रमm_device_alloc("reg-dummy", -1);
	अगर (!dummy_pdev) अणु
		pr_err("Failed to allocate dummy regulator device\n");
		वापस;
	पूर्ण

	ret = platक्रमm_device_add(dummy_pdev);
	अगर (ret != 0) अणु
		pr_err("Failed to register dummy regulator device: %d\n", ret);
		platक्रमm_device_put(dummy_pdev);
		वापस;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&dummy_regulator_driver);
	अगर (ret != 0) अणु
		pr_err("Failed to register dummy regulator driver: %d\n", ret);
		platक्रमm_device_unरेजिस्टर(dummy_pdev);
	पूर्ण
पूर्ण
