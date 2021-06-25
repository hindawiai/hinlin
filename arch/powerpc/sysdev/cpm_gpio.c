<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common CPM GPIO wrapper क्रम the CPM GPIO ports
 *
 * Author: Christophe Leroy <christophe.leroy@c-s.fr>
 *
 * Copyright 2017 CS Systemes d'Inक्रमmation.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/cpm.h>
#अगर_घोषित CONFIG_8xx_GPIO
#समावेश <यंत्र/cpm1.h>
#पूर्ण_अगर

अटल पूर्णांक cpm_gpio_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	पूर्णांक (*gp_add)(काष्ठा device *dev) = of_device_get_match_data(dev);

	अगर (!gp_add)
		वापस -ENODEV;

	वापस gp_add(dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id cpm_gpio_match[] = अणु
#अगर_घोषित CONFIG_8xx_GPIO
	अणु
		.compatible = "fsl,cpm1-pario-bank-a",
		.data = cpm1_gpiochip_add16,
	पूर्ण,
	अणु
		.compatible = "fsl,cpm1-pario-bank-b",
		.data = cpm1_gpiochip_add32,
	पूर्ण,
	अणु
		.compatible = "fsl,cpm1-pario-bank-c",
		.data = cpm1_gpiochip_add16,
	पूर्ण,
	अणु
		.compatible = "fsl,cpm1-pario-bank-d",
		.data = cpm1_gpiochip_add16,
	पूर्ण,
	/* Port E uses CPM2 layout */
	अणु
		.compatible = "fsl,cpm1-pario-bank-e",
		.data = cpm2_gpiochip_add32,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.compatible = "fsl,cpm2-pario-bank",
		.data = cpm2_gpiochip_add32,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpm_gpio_match);

अटल काष्ठा platक्रमm_driver cpm_gpio_driver = अणु
	.probe		= cpm_gpio_probe,
	.driver		= अणु
		.name	= "cpm-gpio",
		.of_match_table	= cpm_gpio_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init cpm_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&cpm_gpio_driver);
पूर्ण
arch_initcall(cpm_gpio_init);

MODULE_AUTHOR("Christophe Leroy <christophe.leroy@c-s.fr>");
MODULE_DESCRIPTION("Driver for CPM GPIO");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:cpm-gpio");
