<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/video/backlight/platक्रमm_lcd.c
 *
 * Copyright 2008 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Generic platक्रमm-device LCD घातer control पूर्णांकerface.
*/

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/lcd.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#समावेश <video/platक्रमm_lcd.h>

काष्ठा platक्रमm_lcd अणु
	काष्ठा device		*us;
	काष्ठा lcd_device	*lcd;
	काष्ठा plat_lcd_data	*pdata;

	अचिन्हित पूर्णांक		 घातer;
	अचिन्हित पूर्णांक		 suspended:1;
पूर्ण;

अटल अंतरभूत काष्ठा platक्रमm_lcd *to_our_lcd(काष्ठा lcd_device *lcd)
अणु
	वापस lcd_get_data(lcd);
पूर्ण

अटल पूर्णांक platक्रमm_lcd_get_घातer(काष्ठा lcd_device *lcd)
अणु
	काष्ठा platक्रमm_lcd *plcd = to_our_lcd(lcd);

	वापस plcd->घातer;
पूर्ण

अटल पूर्णांक platक्रमm_lcd_set_घातer(काष्ठा lcd_device *lcd, पूर्णांक घातer)
अणु
	काष्ठा platक्रमm_lcd *plcd = to_our_lcd(lcd);
	पूर्णांक lcd_घातer = 1;

	अगर (घातer == FB_BLANK_POWERDOWN || plcd->suspended)
		lcd_घातer = 0;

	plcd->pdata->set_घातer(plcd->pdata, lcd_घातer);
	plcd->घातer = घातer;

	वापस 0;
पूर्ण

अटल पूर्णांक platक्रमm_lcd_match(काष्ठा lcd_device *lcd, काष्ठा fb_info *info)
अणु
	काष्ठा platक्रमm_lcd *plcd = to_our_lcd(lcd);
	काष्ठा plat_lcd_data *pdata = plcd->pdata;

	अगर (pdata->match_fb)
		वापस pdata->match_fb(pdata, info);

	वापस plcd->us->parent == info->device;
पूर्ण

अटल काष्ठा lcd_ops platक्रमm_lcd_ops = अणु
	.get_घातer	= platक्रमm_lcd_get_घातer,
	.set_घातer	= platक्रमm_lcd_set_घातer,
	.check_fb	= platक्रमm_lcd_match,
पूर्ण;

अटल पूर्णांक platक्रमm_lcd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_lcd_data *pdata;
	काष्ठा platक्रमm_lcd *plcd;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(dev, "no platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->probe) अणु
		err = pdata->probe(pdata);
		अगर (err)
			वापस err;
	पूर्ण

	plcd = devm_kzalloc(&pdev->dev, माप(काष्ठा platक्रमm_lcd),
			    GFP_KERNEL);
	अगर (!plcd)
		वापस -ENOMEM;

	plcd->us = dev;
	plcd->pdata = pdata;
	plcd->lcd = devm_lcd_device_रेजिस्टर(&pdev->dev, dev_name(dev), dev,
						plcd, &platक्रमm_lcd_ops);
	अगर (IS_ERR(plcd->lcd)) अणु
		dev_err(dev, "cannot register lcd device\n");
		वापस PTR_ERR(plcd->lcd);
	पूर्ण

	platक्रमm_set_drvdata(pdev, plcd);
	platक्रमm_lcd_set_घातer(plcd->lcd, FB_BLANK_NORMAL);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक platक्रमm_lcd_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_lcd *plcd = dev_get_drvdata(dev);

	plcd->suspended = 1;
	platक्रमm_lcd_set_घातer(plcd->lcd, plcd->घातer);

	वापस 0;
पूर्ण

अटल पूर्णांक platक्रमm_lcd_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_lcd *plcd = dev_get_drvdata(dev);

	plcd->suspended = 0;
	platक्रमm_lcd_set_घातer(plcd->lcd, plcd->घातer);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(platक्रमm_lcd_pm_ops, platक्रमm_lcd_suspend,
			platक्रमm_lcd_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id platक्रमm_lcd_of_match[] = अणु
	अणु .compatible = "platform-lcd" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, platक्रमm_lcd_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver platक्रमm_lcd_driver = अणु
	.driver		= अणु
		.name	= "platform-lcd",
		.pm	= &platक्रमm_lcd_pm_ops,
		.of_match_table = of_match_ptr(platक्रमm_lcd_of_match),
	पूर्ण,
	.probe		= platक्रमm_lcd_probe,
पूर्ण;

module_platक्रमm_driver(platक्रमm_lcd_driver);

MODULE_AUTHOR("Ben Dooks <ben-linux@fluff.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:platform-lcd");
