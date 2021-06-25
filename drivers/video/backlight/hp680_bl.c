<शैली गुरु>
/*
 *  Backlight Driver क्रम HP Jornada 680
 *
 *  Copyright (c) 2005 Andriy Skulysh
 *
 *  Based on Sharp's Corgi Backlight Driver
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>

#समावेश <cpu/dac.h>
#समावेश <mach/hp6xx.h>
#समावेश <यंत्र/hd64461.h>

#घोषणा HP680_MAX_INTENSITY 255
#घोषणा HP680_DEFAULT_INTENSITY 10

अटल पूर्णांक hp680bl_suspended;
अटल पूर्णांक current_पूर्णांकensity;
अटल DEFINE_SPINLOCK(bl_lock);

अटल व्योम hp680bl_send_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	अचिन्हित दीर्घ flags;
	u16 v;
	पूर्णांक पूर्णांकensity = backlight_get_brightness(bd);

	अगर (hp680bl_suspended)
		पूर्णांकensity = 0;

	spin_lock_irqsave(&bl_lock, flags);
	अगर (पूर्णांकensity && current_पूर्णांकensity == 0) अणु
		sh_dac_enable(DAC_LCD_BRIGHTNESS);
		v = inw(HD64461_GPBDR);
		v &= ~HD64461_GPBDR_LCDOFF;
		outw(v, HD64461_GPBDR);
		sh_dac_output(255-(u8)पूर्णांकensity, DAC_LCD_BRIGHTNESS);
	पूर्ण अन्यथा अगर (पूर्णांकensity == 0 && current_पूर्णांकensity != 0) अणु
		sh_dac_output(255-(u8)पूर्णांकensity, DAC_LCD_BRIGHTNESS);
		sh_dac_disable(DAC_LCD_BRIGHTNESS);
		v = inw(HD64461_GPBDR);
		v |= HD64461_GPBDR_LCDOFF;
		outw(v, HD64461_GPBDR);
	पूर्ण अन्यथा अगर (पूर्णांकensity) अणु
		sh_dac_output(255-(u8)पूर्णांकensity, DAC_LCD_BRIGHTNESS);
	पूर्ण
	spin_unlock_irqrestore(&bl_lock, flags);

	current_पूर्णांकensity = पूर्णांकensity;
पूर्ण


#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक hp680bl_suspend(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bd = dev_get_drvdata(dev);

	hp680bl_suspended = 1;
	hp680bl_send_पूर्णांकensity(bd);
	वापस 0;
पूर्ण

अटल पूर्णांक hp680bl_resume(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bd = dev_get_drvdata(dev);

	hp680bl_suspended = 0;
	hp680bl_send_पूर्णांकensity(bd);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(hp680bl_pm_ops, hp680bl_suspend, hp680bl_resume);

अटल पूर्णांक hp680bl_set_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	hp680bl_send_पूर्णांकensity(bd);
	वापस 0;
पूर्ण

अटल पूर्णांक hp680bl_get_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	वापस current_पूर्णांकensity;
पूर्ण

अटल स्थिर काष्ठा backlight_ops hp680bl_ops = अणु
	.get_brightness = hp680bl_get_पूर्णांकensity,
	.update_status  = hp680bl_set_पूर्णांकensity,
पूर्ण;

अटल पूर्णांक hp680bl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bd;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = HP680_MAX_INTENSITY;
	bd = devm_backlight_device_रेजिस्टर(&pdev->dev, "hp680-bl", &pdev->dev,
					शून्य, &hp680bl_ops, &props);
	अगर (IS_ERR(bd))
		वापस PTR_ERR(bd);

	platक्रमm_set_drvdata(pdev, bd);

	bd->props.brightness = HP680_DEFAULT_INTENSITY;
	hp680bl_send_पूर्णांकensity(bd);

	वापस 0;
पूर्ण

अटल पूर्णांक hp680bl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_device *bd = platक्रमm_get_drvdata(pdev);

	bd->props.brightness = 0;
	bd->props.घातer = 0;
	hp680bl_send_पूर्णांकensity(bd);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hp680bl_driver = अणु
	.probe		= hp680bl_probe,
	.हटाओ		= hp680bl_हटाओ,
	.driver		= अणु
		.name	= "hp680-bl",
		.pm	= &hp680bl_pm_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *hp680bl_device;

अटल पूर्णांक __init hp680bl_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&hp680bl_driver);
	अगर (ret)
		वापस ret;
	hp680bl_device = platक्रमm_device_रेजिस्टर_simple("hp680-bl", -1,
							शून्य, 0);
	अगर (IS_ERR(hp680bl_device)) अणु
		platक्रमm_driver_unरेजिस्टर(&hp680bl_driver);
		वापस PTR_ERR(hp680bl_device);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास hp680bl_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(hp680bl_device);
	platक्रमm_driver_unरेजिस्टर(&hp680bl_driver);
पूर्ण

module_init(hp680bl_init);
module_निकास(hp680bl_निकास);

MODULE_AUTHOR("Andriy Skulysh <askulysh@gmail.com>");
MODULE_DESCRIPTION("HP Jornada 680 Backlight Driver");
MODULE_LICENSE("GPL");
