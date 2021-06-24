<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Force-disables a regulator to घातer करोwn a device
 *
 * Michael Klein <michael@fossekall.de>
 *
 * Copyright (C) 2020 Michael Klein
 *
 * Based on the gpio-घातeroff driver.
 */
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा TIMEOUT_MS 3000

/*
 * Hold configuration here, cannot be more than one instance of the driver
 * since pm_घातer_off itself is global.
 */
अटल काष्ठा regulator *cpu_regulator;

अटल व्योम regulator_घातeroff_करो_घातeroff(व्योम)
अणु
	अगर (cpu_regulator && regulator_is_enabled(cpu_regulator))
		regulator_क्रमce_disable(cpu_regulator);

	/* give it some समय */
	mdelay(TIMEOUT_MS);

	WARN_ON(1);
पूर्ण

अटल पूर्णांक regulator_घातeroff_probe(काष्ठा platक्रमm_device *pdev)
अणु
	/* If a pm_घातer_off function has alपढ़ोy been added, leave it alone */
	अगर (pm_घातer_off != शून्य) अणु
		dev_err(&pdev->dev,
			"%s: pm_power_off function already registered\n",
			__func__);
		वापस -EBUSY;
	पूर्ण

	cpu_regulator = devm_regulator_get(&pdev->dev, "cpu");
	अगर (IS_ERR(cpu_regulator))
		वापस PTR_ERR(cpu_regulator);

	pm_घातer_off = &regulator_घातeroff_करो_घातeroff;
	वापस 0;
पूर्ण

अटल पूर्णांक regulator_घातeroff_हटाओ(__maybe_unused काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pm_घातer_off == &regulator_घातeroff_करो_घातeroff)
		pm_घातer_off = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_regulator_घातeroff_match[] = अणु
	अणु .compatible = "regulator-poweroff", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver regulator_घातeroff_driver = अणु
	.probe = regulator_घातeroff_probe,
	.हटाओ = regulator_घातeroff_हटाओ,
	.driver = अणु
		.name = "poweroff-regulator",
		.of_match_table = of_regulator_घातeroff_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(regulator_घातeroff_driver);

MODULE_AUTHOR("Michael Klein <michael@fossekall.de>");
MODULE_DESCRIPTION("Regulator poweroff driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:poweroff-regulator");
