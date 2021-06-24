<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/plat-iop/gpio.c
 * GPIO handling क्रम Intel IOP3xx processors.
 *
 * Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा IOP3XX_GPOE	0x0000
#घोषणा IOP3XX_GPID	0x0004
#घोषणा IOP3XX_GPOD	0x0008

अटल पूर्णांक iop3xx_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_chip *gc;
	व्योम __iomem *base;
	पूर्णांक err;

	gc = devm_kzalloc(&pdev->dev, माप(*gc), GFP_KERNEL);
	अगर (!gc)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	err = bgpio_init(gc, &pdev->dev, 1, base + IOP3XX_GPID,
			 base + IOP3XX_GPOD, शून्य, शून्य, base + IOP3XX_GPOE, 0);
	अगर (err)
		वापस err;

	gc->base = 0;
	gc->owner = THIS_MODULE;
	gc->label = "gpio-iop";

	वापस devm_gpiochip_add_data(&pdev->dev, gc, शून्य);
पूर्ण

अटल काष्ठा platक्रमm_driver iop3xx_gpio_driver = अणु
	.driver = अणु
		.name = "gpio-iop",
	पूर्ण,
	.probe = iop3xx_gpio_probe,
पूर्ण;

अटल पूर्णांक __init iop3xx_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&iop3xx_gpio_driver);
पूर्ण
arch_initcall(iop3xx_gpio_init);

MODULE_DESCRIPTION("GPIO handling for Intel IOP3xx processors");
MODULE_AUTHOR("Lennert Buytenhek <buytenh@wantstofly.org>");
MODULE_LICENSE("GPL");
