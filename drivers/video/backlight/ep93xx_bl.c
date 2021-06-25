<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Cirrus EP93xx lcd backlight
 *
 * Copyright (c) 2010 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * This driver controls the pulse width modulated brightness control output,
 * BRIGHT, on the Cirrus EP9307, EP9312, and EP9315 processors.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>

#घोषणा EP93XX_MAX_COUNT		255
#घोषणा EP93XX_MAX_BRIGHT		255
#घोषणा EP93XX_DEF_BRIGHT		128

काष्ठा ep93xxbl अणु
	व्योम __iomem *mmio;
	पूर्णांक brightness;
पूर्ण;

अटल पूर्णांक ep93xxbl_set(काष्ठा backlight_device *bl, पूर्णांक brightness)
अणु
	काष्ठा ep93xxbl *ep93xxbl = bl_get_data(bl);

	ग_लिखोl((brightness << 8) | EP93XX_MAX_COUNT, ep93xxbl->mmio);

	ep93xxbl->brightness = brightness;

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xxbl_update_status(काष्ठा backlight_device *bl)
अणु
	वापस ep93xxbl_set(bl, backlight_get_brightness(bl));
पूर्ण

अटल पूर्णांक ep93xxbl_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा ep93xxbl *ep93xxbl = bl_get_data(bl);

	वापस ep93xxbl->brightness;
पूर्ण

अटल स्थिर काष्ठा backlight_ops ep93xxbl_ops = अणु
	.update_status	= ep93xxbl_update_status,
	.get_brightness	= ep93xxbl_get_brightness,
पूर्ण;

अटल पूर्णांक ep93xxbl_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा ep93xxbl *ep93xxbl;
	काष्ठा backlight_device *bl;
	काष्ठा backlight_properties props;
	काष्ठा resource *res;

	ep93xxbl = devm_kzalloc(&dev->dev, माप(*ep93xxbl), GFP_KERNEL);
	अगर (!ep93xxbl)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENXIO;

	/*
	 * FIXME - We करोn't करो a request_mem_region here because we are
	 * sharing the रेजिस्टर space with the framebuffer driver (see
	 * drivers/video/ep93xx-fb.c) and करोing so will cause the second
	 * loaded driver to वापस -EBUSY.
	 *
	 * NOTE: No locking is required; the framebuffer करोes not touch
	 * this रेजिस्टर.
	 */
	ep93xxbl->mmio = devm_ioremap(&dev->dev, res->start,
				      resource_size(res));
	अगर (!ep93xxbl->mmio)
		वापस -ENXIO;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = EP93XX_MAX_BRIGHT;
	bl = devm_backlight_device_रेजिस्टर(&dev->dev, dev->name, &dev->dev,
					ep93xxbl, &ep93xxbl_ops, &props);
	अगर (IS_ERR(bl))
		वापस PTR_ERR(bl);

	bl->props.brightness = EP93XX_DEF_BRIGHT;

	platक्रमm_set_drvdata(dev, bl);

	ep93xxbl_update_status(bl);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ep93xxbl_suspend(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bl = dev_get_drvdata(dev);

	वापस ep93xxbl_set(bl, 0);
पूर्ण

अटल पूर्णांक ep93xxbl_resume(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bl = dev_get_drvdata(dev);

	backlight_update_status(bl);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ep93xxbl_pm_ops, ep93xxbl_suspend, ep93xxbl_resume);

अटल काष्ठा platक्रमm_driver ep93xxbl_driver = अणु
	.driver		= अणु
		.name	= "ep93xx-bl",
		.pm	= &ep93xxbl_pm_ops,
	पूर्ण,
	.probe		= ep93xxbl_probe,
पूर्ण;

module_platक्रमm_driver(ep93xxbl_driver);

MODULE_DESCRIPTION("EP93xx Backlight Driver");
MODULE_AUTHOR("H Hartley Sweeten <hsweeten@visionengravers.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ep93xx-bl");
