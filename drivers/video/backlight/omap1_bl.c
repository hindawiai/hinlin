<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Backlight driver क्रम OMAP based boards.
 *
 * Copyright (c) 2006 Andrzej Zaborowski  <balrog@zabor.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_data/omap1_bl.h>

#समावेश <mach/hardware.h>
#समावेश <mach/mux.h>

#घोषणा OMAPBL_MAX_INTENSITY		0xff

काष्ठा omap_backlight अणु
	पूर्णांक घातermode;
	पूर्णांक current_पूर्णांकensity;

	काष्ठा device *dev;
	काष्ठा omap_backlight_config *pdata;
पूर्ण;

अटल अंतरभूत व्योम omapbl_send_पूर्णांकensity(पूर्णांक पूर्णांकensity)
अणु
	omap_ग_लिखोb(पूर्णांकensity, OMAP_PWL_ENABLE);
पूर्ण

अटल अंतरभूत व्योम omapbl_send_enable(पूर्णांक enable)
अणु
	omap_ग_लिखोb(enable, OMAP_PWL_CLK_ENABLE);
पूर्ण

अटल व्योम omapbl_blank(काष्ठा omap_backlight *bl, पूर्णांक mode)
अणु
	अगर (bl->pdata->set_घातer)
		bl->pdata->set_घातer(bl->dev, mode);

	चयन (mode) अणु
	हाल FB_BLANK_NORMAL:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_POWERDOWN:
		omapbl_send_पूर्णांकensity(0);
		omapbl_send_enable(0);
		अवरोध;

	हाल FB_BLANK_UNBLANK:
		omapbl_send_पूर्णांकensity(bl->current_पूर्णांकensity);
		omapbl_send_enable(1);
		अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक omapbl_suspend(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bl_dev = dev_get_drvdata(dev);
	काष्ठा omap_backlight *bl = bl_get_data(bl_dev);

	omapbl_blank(bl, FB_BLANK_POWERDOWN);
	वापस 0;
पूर्ण

अटल पूर्णांक omapbl_resume(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bl_dev = dev_get_drvdata(dev);
	काष्ठा omap_backlight *bl = bl_get_data(bl_dev);

	omapbl_blank(bl, bl->घातermode);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक omapbl_set_घातer(काष्ठा backlight_device *dev, पूर्णांक state)
अणु
	काष्ठा omap_backlight *bl = bl_get_data(dev);

	omapbl_blank(bl, state);
	bl->घातermode = state;

	वापस 0;
पूर्ण

अटल पूर्णांक omapbl_update_status(काष्ठा backlight_device *dev)
अणु
	काष्ठा omap_backlight *bl = bl_get_data(dev);

	अगर (bl->current_पूर्णांकensity != dev->props.brightness) अणु
		अगर (bl->घातermode == FB_BLANK_UNBLANK)
			omapbl_send_पूर्णांकensity(dev->props.brightness);
		bl->current_पूर्णांकensity = dev->props.brightness;
	पूर्ण

	अगर (dev->props.fb_blank != bl->घातermode)
		omapbl_set_घातer(dev, dev->props.fb_blank);

	वापस 0;
पूर्ण

अटल पूर्णांक omapbl_get_पूर्णांकensity(काष्ठा backlight_device *dev)
अणु
	काष्ठा omap_backlight *bl = bl_get_data(dev);

	वापस bl->current_पूर्णांकensity;
पूर्ण

अटल स्थिर काष्ठा backlight_ops omapbl_ops = अणु
	.get_brightness = omapbl_get_पूर्णांकensity,
	.update_status  = omapbl_update_status,
पूर्ण;

अटल पूर्णांक omapbl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *dev;
	काष्ठा omap_backlight *bl;
	काष्ठा omap_backlight_config *pdata = dev_get_platdata(&pdev->dev);

	अगर (!pdata)
		वापस -ENXIO;

	bl = devm_kzalloc(&pdev->dev, माप(काष्ठा omap_backlight),
			  GFP_KERNEL);
	अगर (unlikely(!bl))
		वापस -ENOMEM;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = OMAPBL_MAX_INTENSITY;
	dev = devm_backlight_device_रेजिस्टर(&pdev->dev, "omap-bl", &pdev->dev,
					bl, &omapbl_ops, &props);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);

	bl->घातermode = FB_BLANK_POWERDOWN;
	bl->current_पूर्णांकensity = 0;

	bl->pdata = pdata;
	bl->dev = &pdev->dev;

	platक्रमm_set_drvdata(pdev, dev);

	omap_cfg_reg(PWL);	/* Conflicts with UART3 */

	dev->props.fb_blank = FB_BLANK_UNBLANK;
	dev->props.brightness = pdata->शेष_पूर्णांकensity;
	omapbl_update_status(dev);

	dev_info(&pdev->dev, "OMAP LCD backlight initialised\n");

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(omapbl_pm_ops, omapbl_suspend, omapbl_resume);

अटल काष्ठा platक्रमm_driver omapbl_driver = अणु
	.probe		= omapbl_probe,
	.driver		= अणु
		.name	= "omap-bl",
		.pm	= &omapbl_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omapbl_driver);

MODULE_AUTHOR("Andrzej Zaborowski <balrog@zabor.org>");
MODULE_DESCRIPTION("OMAP LCD Backlight driver");
MODULE_LICENSE("GPL");
