<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backlight control code क्रम Sharp Zaurus SL-5500
 *
 * Copyright 2005 John Lenz <lenz@cs.wisc.edu>
 * Maपूर्णांकainer: Pavel Machek <pavel@ucw.cz> (unless John wants to :-)
 *
 * This driver assumes single CPU. That's okay, because collie is
 * slightly old hardware, and no one is going to retrofit second CPU to
 * old PDA.
 */

/* LCD घातer functions */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>

#समावेश <यंत्र/hardware/locomo.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/sharpsl_param.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "../../../arch/arm/mach-sa1100/generic.h"

अटल काष्ठा backlight_device *locomolcd_bl_device;
अटल काष्ठा locomo_dev *locomolcd_dev;
अटल अचिन्हित दीर्घ locomolcd_flags;
#घोषणा LOCOMOLCD_SUSPENDED     0x01

अटल व्योम locomolcd_on(पूर्णांक comadj)
अणु
	locomo_gpio_set_dir(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_VSHA_ON, 0);
	locomo_gpio_ग_लिखो(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_VSHA_ON, 1);
	mdelay(2);

	locomo_gpio_set_dir(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_VSHD_ON, 0);
	locomo_gpio_ग_लिखो(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_VSHD_ON, 1);
	mdelay(2);

	locomo_m62332_senddata(locomolcd_dev, comadj, 0);
	mdelay(5);

	locomo_gpio_set_dir(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_VEE_ON, 0);
	locomo_gpio_ग_लिखो(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_VEE_ON, 1);
	mdelay(10);

	/* TFTCRST | CPSOUT=0 | CPSEN */
	locomo_ग_लिखोl(0x01, locomolcd_dev->mapbase + LOCOMO_TC);

	/* Set CPSD */
	locomo_ग_लिखोl(6, locomolcd_dev->mapbase + LOCOMO_CPSD);

	/* TFTCRST | CPSOUT=0 | CPSEN */
	locomo_ग_लिखोl((0x04 | 0x01), locomolcd_dev->mapbase + LOCOMO_TC);
	mdelay(10);

	locomo_gpio_set_dir(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_MOD, 0);
	locomo_gpio_ग_लिखो(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_MOD, 1);
पूर्ण

अटल व्योम locomolcd_off(पूर्णांक comadj)
अणु
	/* TFTCRST=1 | CPSOUT=1 | CPSEN = 0 */
	locomo_ग_लिखोl(0x06, locomolcd_dev->mapbase + LOCOMO_TC);
	mdelay(1);

	locomo_gpio_ग_लिखो(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_VSHA_ON, 0);
	mdelay(110);

	locomo_gpio_ग_लिखो(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_VEE_ON, 0);
	mdelay(700);

	/* TFTCRST=0 | CPSOUT=0 | CPSEN = 0 */
	locomo_ग_लिखोl(0, locomolcd_dev->mapbase + LOCOMO_TC);
	locomo_gpio_ग_लिखो(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_MOD, 0);
	locomo_gpio_ग_लिखो(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_VSHD_ON, 0);
पूर्ण

व्योम locomolcd_घातer(पूर्णांक on)
अणु
	पूर्णांक comadj = sharpsl_param.comadj;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	अगर (!locomolcd_dev) अणु
		local_irq_restore(flags);
		वापस;
	पूर्ण

	/* पढ़ो comadj */
	अगर (comadj == -1 && machine_is_collie())
		comadj = 128;
	अगर (comadj == -1 && machine_is_poodle())
		comadj = 118;

	अगर (on)
		locomolcd_on(comadj);
	अन्यथा
		locomolcd_off(comadj);

	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(locomolcd_घातer);

अटल पूर्णांक current_पूर्णांकensity;

अटल पूर्णांक locomolcd_set_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	पूर्णांक पूर्णांकensity = backlight_get_brightness(bd);

	अगर (locomolcd_flags & LOCOMOLCD_SUSPENDED)
		पूर्णांकensity = 0;

	चयन (पूर्णांकensity) अणु
	/*
	 * AC and non-AC are handled dअगरferently,
	 * but produce same results in sharp code?
	 */
	हाल 0:
		locomo_frontlight_set(locomolcd_dev, 0, 0, 161);
		अवरोध;
	हाल 1:
		locomo_frontlight_set(locomolcd_dev, 117, 0, 161);
		अवरोध;
	हाल 2:
		locomo_frontlight_set(locomolcd_dev, 163, 0, 148);
		अवरोध;
	हाल 3:
		locomo_frontlight_set(locomolcd_dev, 194, 0, 161);
		अवरोध;
	हाल 4:
		locomo_frontlight_set(locomolcd_dev, 194, 1, 161);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	current_पूर्णांकensity = पूर्णांकensity;
	वापस 0;
पूर्ण

अटल पूर्णांक locomolcd_get_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	वापस current_पूर्णांकensity;
पूर्ण

अटल स्थिर काष्ठा backlight_ops locomobl_data = अणु
	.get_brightness = locomolcd_get_पूर्णांकensity,
	.update_status  = locomolcd_set_पूर्णांकensity,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक locomolcd_suspend(काष्ठा device *dev)
अणु
	locomolcd_flags |= LOCOMOLCD_SUSPENDED;
	locomolcd_set_पूर्णांकensity(locomolcd_bl_device);
	वापस 0;
पूर्ण

अटल पूर्णांक locomolcd_resume(काष्ठा device *dev)
अणु
	locomolcd_flags &= ~LOCOMOLCD_SUSPENDED;
	locomolcd_set_पूर्णांकensity(locomolcd_bl_device);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(locomolcd_pm_ops, locomolcd_suspend, locomolcd_resume);

अटल पूर्णांक locomolcd_probe(काष्ठा locomo_dev *ldev)
अणु
	काष्ठा backlight_properties props;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	locomolcd_dev = ldev;

	locomo_gpio_set_dir(ldev->dev.parent, LOCOMO_GPIO_FL_VR, 0);

	/*
	 * the poodle_lcd_घातer function is called क्रम the first समय
	 * from fs_initcall, which is beक्रमe locomo is activated.
	 * We need to recall poodle_lcd_घातer here
	 */
	अगर (machine_is_poodle())
		locomolcd_घातer(1);

	local_irq_restore(flags);

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = 4;
	locomolcd_bl_device = backlight_device_रेजिस्टर("locomo-bl",
							&ldev->dev, शून्य,
							&locomobl_data, &props);

	अगर (IS_ERR(locomolcd_bl_device))
		वापस PTR_ERR(locomolcd_bl_device);

	/* Set up frontlight so that screen is पढ़ोable */
	locomolcd_bl_device->props.brightness = 2;
	locomolcd_set_पूर्णांकensity(locomolcd_bl_device);

	वापस 0;
पूर्ण

अटल व्योम locomolcd_हटाओ(काष्ठा locomo_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	locomolcd_bl_device->props.brightness = 0;
	locomolcd_bl_device->props.घातer = 0;
	locomolcd_set_पूर्णांकensity(locomolcd_bl_device);

	backlight_device_unरेजिस्टर(locomolcd_bl_device);
	local_irq_save(flags);
	locomolcd_dev = शून्य;
	local_irq_restore(flags);
पूर्ण

अटल काष्ठा locomo_driver poodle_lcd_driver = अणु
	.drv = अणु
		.name	= "locomo-backlight",
		.pm	= &locomolcd_pm_ops,
	पूर्ण,
	.devid	= LOCOMO_DEVID_BACKLIGHT,
	.probe	= locomolcd_probe,
	.हटाओ	= locomolcd_हटाओ,
पूर्ण;

अटल पूर्णांक __init locomolcd_init(व्योम)
अणु
	वापस locomo_driver_रेजिस्टर(&poodle_lcd_driver);
पूर्ण

अटल व्योम __निकास locomolcd_निकास(व्योम)
अणु
	locomo_driver_unरेजिस्टर(&poodle_lcd_driver);
पूर्ण

module_init(locomolcd_init);
module_निकास(locomolcd_निकास);

MODULE_AUTHOR("John Lenz <lenz@cs.wisc.edu>, Pavel Machek <pavel@ucw.cz>");
MODULE_DESCRIPTION("Collie LCD driver");
MODULE_LICENSE("GPL");
