<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Power off by restarting and let u-boot keep hold of the machine
 * until the user presses a button क्रम example.
 *
 * Andrew Lunn <andrew@lunn.ch>
 *
 * Copyright (C) 2012 Andrew Lunn
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/module.h>
#समावेश <linux/reboot.h>

अटल व्योम restart_घातeroff_करो_घातeroff(व्योम)
अणु
	reboot_mode = REBOOT_HARD;
	machine_restart(शून्य);
पूर्ण

अटल पूर्णांक restart_घातeroff_probe(काष्ठा platक्रमm_device *pdev)
अणु
	/* If a pm_घातer_off function has alपढ़ोy been added, leave it alone */
	अगर (pm_घातer_off != शून्य) अणु
		dev_err(&pdev->dev,
			"pm_power_off function already registered");
		वापस -EBUSY;
	पूर्ण

	pm_घातer_off = &restart_घातeroff_करो_घातeroff;
	वापस 0;
पूर्ण

अटल पूर्णांक restart_घातeroff_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pm_घातer_off == &restart_घातeroff_करो_घातeroff)
		pm_घातer_off = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_restart_घातeroff_match[] = अणु
	अणु .compatible = "restart-poweroff", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_restart_घातeroff_match);

अटल काष्ठा platक्रमm_driver restart_घातeroff_driver = अणु
	.probe = restart_घातeroff_probe,
	.हटाओ = restart_घातeroff_हटाओ,
	.driver = अणु
		.name = "poweroff-restart",
		.of_match_table = of_restart_घातeroff_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(restart_घातeroff_driver);

MODULE_AUTHOR("Andrew Lunn <andrew@lunn.ch");
MODULE_DESCRIPTION("restart poweroff driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:poweroff-restart");
