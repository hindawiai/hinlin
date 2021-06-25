<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/video/backlight/vgg2432a4.c
 *
 * VGG2432A4 (ILI9320) LCD controller driver.
 *
 * Copyright 2007 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
*/

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/lcd.h>
#समावेश <linux/module.h>

#समावेश <linux/spi/spi.h>

#समावेश <video/ili9320.h>

#समावेश "ili9320.h"

/* Device initialisation sequences */

अटल स्थिर काष्ठा ili9320_reg vgg_init1[] = अणु
	अणु
		.address = ILI9320_POWER1,
		.value	 = ILI9320_POWER1_AP(0) | ILI9320_POWER1_BT(0),
	पूर्ण, अणु
		.address = ILI9320_POWER2,
		.value	 = (ILI9320_POWER2_VC(7) |
			    ILI9320_POWER2_DC0(0) | ILI9320_POWER2_DC1(0)),
	पूर्ण, अणु
		.address = ILI9320_POWER3,
		.value	 = ILI9320_POWER3_VRH(0),
	पूर्ण, अणु
		.address = ILI9320_POWER4,
		.value	 = ILI9320_POWER4_VREOUT(0),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ili9320_reg vgg_init2[] = अणु
	अणु
		.address = ILI9320_POWER1,
		.value   = (ILI9320_POWER1_AP(3) | ILI9320_POWER1_APE |
			    ILI9320_POWER1_BT(7) | ILI9320_POWER1_SAP),
	पूर्ण, अणु
		.address = ILI9320_POWER2,
		.value   = ILI9320_POWER2_VC(7) | ILI9320_POWER2_DC0(3),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ili9320_reg vgg_gamma[] = अणु
	अणु
		.address = ILI9320_GAMMA1,
		.value	 = 0x0000,
	पूर्ण, अणु
		.address = ILI9320_GAMMA2,
		.value   = 0x0505,
	पूर्ण, अणु
		.address = ILI9320_GAMMA3,
		.value	 = 0x0004,
	पूर्ण, अणु
		.address = ILI9320_GAMMA4,
		.value	 = 0x0006,
	पूर्ण, अणु
		.address = ILI9320_GAMMA5,
		.value	 = 0x0707,
	पूर्ण, अणु
		.address = ILI9320_GAMMA6,
		.value	 = 0x0105,
	पूर्ण, अणु
		.address = ILI9320_GAMMA7,
		.value	 = 0x0002,
	पूर्ण, अणु
		.address = ILI9320_GAMMA8,
		.value	 = 0x0707,
	पूर्ण, अणु
		.address = ILI9320_GAMMA9,
		.value	 = 0x0704,
	पूर्ण, अणु
		.address = ILI9320_GAMMA10,
		.value	 = 0x807,
	पूर्ण

पूर्ण;

अटल स्थिर काष्ठा ili9320_reg vgg_init0[] = अणु
	[0]	= अणु
		/* set direction and scan mode gate */
		.address = ILI9320_DRIVER,
		.value	 = ILI9320_DRIVER_SS,
	पूर्ण, अणु
		.address = ILI9320_DRIVEWAVE,
		.value	 = (ILI9320_DRIVEWAVE_MUSTSET |
			    ILI9320_DRIVEWAVE_EOR | ILI9320_DRIVEWAVE_BC),
	पूर्ण, अणु
		.address = ILI9320_ENTRYMODE,
		.value	 = ILI9320_ENTRYMODE_ID(3) | ILI9320_ENTRYMODE_BGR,
	पूर्ण, अणु
		.address = ILI9320_RESIZING,
		.value	 = 0x0,
	पूर्ण,
पूर्ण;


अटल पूर्णांक vgg2432a4_lcd_init(काष्ठा ili9320 *lcd,
			      काष्ठा ili9320_platdata *cfg)
अणु
	अचिन्हित पूर्णांक addr;
	पूर्णांक ret;

	/* Set VCore beक्रमe anything अन्यथा (VGG243237-6UFLWA) */
	ret = ili9320_ग_लिखो(lcd, 0x00e5, 0x8000);
	अगर (ret)
		जाओ err_initial;

	/* Start the oscillator up beक्रमe we can करो anything अन्यथा. */
	ret = ili9320_ग_लिखो(lcd, ILI9320_OSCILATION, ILI9320_OSCILATION_OSC);
	अगर (ret)
		जाओ err_initial;

	/* must रुको at-lesat 10ms after starting */
	mdelay(15);

	ret = ili9320_ग_लिखो_regs(lcd, vgg_init0, ARRAY_SIZE(vgg_init0));
	अगर (ret != 0)
		जाओ err_initial;

	ili9320_ग_लिखो(lcd, ILI9320_DISPLAY2, cfg->display2);
	ili9320_ग_लिखो(lcd, ILI9320_DISPLAY3, cfg->display3);
	ili9320_ग_लिखो(lcd, ILI9320_DISPLAY4, cfg->display4);

	ili9320_ग_लिखो(lcd, ILI9320_RGB_IF1, cfg->rgb_अगर1);
	ili9320_ग_लिखो(lcd, ILI9320_FRAMEMAKER, 0x0);
	ili9320_ग_लिखो(lcd, ILI9320_RGB_IF2, cfg->rgb_अगर2);

	ret = ili9320_ग_लिखो_regs(lcd, vgg_init1, ARRAY_SIZE(vgg_init1));
	अगर (ret != 0)
		जाओ err_vgg;

	mdelay(300);

	ret = ili9320_ग_लिखो_regs(lcd, vgg_init2, ARRAY_SIZE(vgg_init2));
	अगर (ret != 0)
		जाओ err_vgg2;

	mdelay(100);

	ili9320_ग_लिखो(lcd, ILI9320_POWER3, 0x13c);

	mdelay(100);

	ili9320_ग_लिखो(lcd, ILI9320_POWER4, 0x1c00);
	ili9320_ग_लिखो(lcd, ILI9320_POWER7, 0x000e);

	mdelay(100);

	ili9320_ग_लिखो(lcd, ILI9320_GRAM_HORIZ_ADDR, 0x00);
	ili9320_ग_लिखो(lcd, ILI9320_GRAM_VERT_ADD, 0x00);

	ret = ili9320_ग_लिखो_regs(lcd, vgg_gamma, ARRAY_SIZE(vgg_gamma));
	अगर (ret != 0)
		जाओ err_vgg3;

	ili9320_ग_लिखो(lcd, ILI9320_HORIZ_START, 0x0);
	ili9320_ग_लिखो(lcd, ILI9320_HORIZ_END, cfg->hsize - 1);
	ili9320_ग_लिखो(lcd, ILI9320_VERT_START, 0x0);
	ili9320_ग_लिखो(lcd, ILI9320_VERT_END, cfg->vsize - 1);

	ili9320_ग_लिखो(lcd, ILI9320_DRIVER2,
		      ILI9320_DRIVER2_NL(((cfg->vsize - 240) / 8) + 0x1D));

	ili9320_ग_लिखो(lcd, ILI9320_BASE_IMAGE, 0x1);
	ili9320_ग_लिखो(lcd, ILI9320_VERT_SCROLL, 0x00);

	क्रम (addr = ILI9320_PARTIAL1_POSITION; addr <= ILI9320_PARTIAL2_END;
	     addr++) अणु
		ili9320_ग_लिखो(lcd, addr, 0x0);
	पूर्ण

	ili9320_ग_लिखो(lcd, ILI9320_INTERFACE1, 0x10);
	ili9320_ग_लिखो(lcd, ILI9320_INTERFACE2, cfg->पूर्णांकerface2);
	ili9320_ग_लिखो(lcd, ILI9320_INTERFACE3, cfg->पूर्णांकerface3);
	ili9320_ग_लिखो(lcd, ILI9320_INTERFACE4, cfg->पूर्णांकerface4);
	ili9320_ग_लिखो(lcd, ILI9320_INTERFACE5, cfg->पूर्णांकerface5);
	ili9320_ग_लिखो(lcd, ILI9320_INTERFACE6, cfg->पूर्णांकerface6);

	lcd->display1 = (ILI9320_DISPLAY1_D(3) | ILI9320_DISPLAY1_DTE |
			 ILI9320_DISPLAY1_GON | ILI9320_DISPLAY1_BASEE |
			 0x40);

	ili9320_ग_लिखो(lcd, ILI9320_DISPLAY1, lcd->display1);

	वापस 0;

 err_vgg3:
 err_vgg2:
 err_vgg:
 err_initial:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक vgg2432a4_suspend(काष्ठा device *dev)
अणु
	वापस ili9320_suspend(dev_get_drvdata(dev));
पूर्ण
अटल पूर्णांक vgg2432a4_resume(काष्ठा device *dev)
अणु
	वापस ili9320_resume(dev_get_drvdata(dev));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा ili9320_client vgg2432a4_client = अणु
	.name	= "VGG2432A4",
	.init	= vgg2432a4_lcd_init,
पूर्ण;

/* Device probe */

अटल पूर्णांक vgg2432a4_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;

	ret = ili9320_probe_spi(spi, &vgg2432a4_client);
	अगर (ret != 0) अणु
		dev_err(&spi->dev, "failed to initialise ili9320\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vgg2432a4_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस ili9320_हटाओ(spi_get_drvdata(spi));
पूर्ण

अटल व्योम vgg2432a4_shutकरोwn(काष्ठा spi_device *spi)
अणु
	ili9320_shutकरोwn(spi_get_drvdata(spi));
पूर्ण

अटल SIMPLE_DEV_PM_OPS(vgg2432a4_pm_ops, vgg2432a4_suspend, vgg2432a4_resume);

अटल काष्ठा spi_driver vgg2432a4_driver = अणु
	.driver = अणु
		.name		= "VGG2432A4",
		.pm		= &vgg2432a4_pm_ops,
	पूर्ण,
	.probe		= vgg2432a4_probe,
	.हटाओ		= vgg2432a4_हटाओ,
	.shutकरोwn	= vgg2432a4_shutकरोwn,
पूर्ण;

module_spi_driver(vgg2432a4_driver);

MODULE_AUTHOR("Ben Dooks <ben-linux@fluff.org>");
MODULE_DESCRIPTION("VGG2432A4 LCD Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:VGG2432A4");
