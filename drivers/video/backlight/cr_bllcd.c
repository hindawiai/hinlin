<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) Intel Corp. 2007.
 * All Rights Reserved.
 *
 * Intel funded Tungsten Graphics (http://www.tungstengraphics.com) to
 * develop this driver.
 *
 * This file is part of the Carillo Ranch video subप्रणाली driver.
 *
 * Authors:
 *   Thomas Hellstrom <thomas-at-tungstengraphics-करोt-com>
 *   Alan Hourihane <alanh-at-tungstengraphics-करोt-com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/lcd.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

/* The LVDS- and panel घातer controls sits on the
 * GPIO port of the ISA bridge.
 */

#घोषणा CRVML_DEVICE_LPC    0x27B8
#घोषणा CRVML_REG_GPIOBAR   0x48
#घोषणा CRVML_REG_GPIOEN    0x4C
#घोषणा CRVML_GPIOEN_BIT    (1 << 4)
#घोषणा CRVML_PANEL_PORT    0x38
#घोषणा CRVML_LVDS_ON       0x00000001
#घोषणा CRVML_PANEL_ON      0x00000002
#घोषणा CRVML_BACKLIGHT_OFF 0x00000004

/* The PLL Clock रेजिस्टर sits on Host bridge */
#घोषणा CRVML_DEVICE_MCH   0x5001
#घोषणा CRVML_REG_MCHBAR   0x44
#घोषणा CRVML_REG_MCHEN    0x54
#घोषणा CRVML_MCHEN_BIT    (1 << 28)
#घोषणा CRVML_MCHMAP_SIZE  4096
#घोषणा CRVML_REG_CLOCK    0xc3c
#घोषणा CRVML_CLOCK_SHIFT  8
#घोषणा CRVML_CLOCK_MASK   0x00000f00

अटल काष्ठा pci_dev *lpc_dev;
अटल u32 gpio_bar;

काष्ठा cr_panel अणु
	काष्ठा backlight_device *cr_backlight_device;
	काष्ठा lcd_device *cr_lcd_device;
पूर्ण;

अटल पूर्णांक cr_backlight_set_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	u32 addr = gpio_bar + CRVML_PANEL_PORT;
	u32 cur = inl(addr);

	अगर (backlight_get_brightness(bd) == 0) अणु
		/* OFF */
		cur |= CRVML_BACKLIGHT_OFF;
		outl(cur, addr);
	पूर्ण अन्यथा अणु
		/* FULL ON */
		cur &= ~CRVML_BACKLIGHT_OFF;
		outl(cur, addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cr_backlight_get_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	u32 addr = gpio_bar + CRVML_PANEL_PORT;
	u32 cur = inl(addr);
	u8 पूर्णांकensity;

	अगर (cur & CRVML_BACKLIGHT_OFF)
		पूर्णांकensity = 0;
	अन्यथा
		पूर्णांकensity = 1;

	वापस पूर्णांकensity;
पूर्ण

अटल स्थिर काष्ठा backlight_ops cr_backlight_ops = अणु
	.get_brightness = cr_backlight_get_पूर्णांकensity,
	.update_status = cr_backlight_set_पूर्णांकensity,
पूर्ण;

अटल व्योम cr_panel_on(व्योम)
अणु
	u32 addr = gpio_bar + CRVML_PANEL_PORT;
	u32 cur = inl(addr);

	अगर (!(cur & CRVML_PANEL_ON)) अणु
		/* Make sure LVDS controller is करोwn. */
		अगर (cur & 0x00000001) अणु
			cur &= ~CRVML_LVDS_ON;
			outl(cur, addr);
		पूर्ण
		/* Power up Panel */
		schedule_समयout(HZ / 10);
		cur |= CRVML_PANEL_ON;
		outl(cur, addr);
	पूर्ण

	/* Power up LVDS controller */

	अगर (!(cur & CRVML_LVDS_ON)) अणु
		schedule_समयout(HZ / 10);
		outl(cur | CRVML_LVDS_ON, addr);
	पूर्ण
पूर्ण

अटल व्योम cr_panel_off(व्योम)
अणु
	u32 addr = gpio_bar + CRVML_PANEL_PORT;
	u32 cur = inl(addr);

	/* Power करोwn LVDS controller first to aव्योम high currents */
	अगर (cur & CRVML_LVDS_ON) अणु
		cur &= ~CRVML_LVDS_ON;
		outl(cur, addr);
	पूर्ण
	अगर (cur & CRVML_PANEL_ON) अणु
		schedule_समयout(HZ / 10);
		outl(cur & ~CRVML_PANEL_ON, addr);
	पूर्ण
पूर्ण

अटल पूर्णांक cr_lcd_set_घातer(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	अगर (घातer == FB_BLANK_UNBLANK)
		cr_panel_on();
	अगर (घातer == FB_BLANK_POWERDOWN)
		cr_panel_off();

	वापस 0;
पूर्ण

अटल काष्ठा lcd_ops cr_lcd_ops = अणु
	.set_घातer = cr_lcd_set_घातer,
पूर्ण;

अटल पूर्णांक cr_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bdp;
	काष्ठा lcd_device *ldp;
	काष्ठा cr_panel *crp;
	u8 dev_en;

	lpc_dev = pci_get_device(PCI_VENDOR_ID_INTEL,
					CRVML_DEVICE_LPC, शून्य);
	अगर (!lpc_dev) अणु
		pr_err("INTEL CARILLO RANCH LPC not found.\n");
		वापस -ENODEV;
	पूर्ण

	pci_पढ़ो_config_byte(lpc_dev, CRVML_REG_GPIOEN, &dev_en);
	अगर (!(dev_en & CRVML_GPIOEN_BIT)) अणु
		pr_err("Carillo Ranch GPIO device was not enabled.\n");
		pci_dev_put(lpc_dev);
		वापस -ENODEV;
	पूर्ण

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	bdp = devm_backlight_device_रेजिस्टर(&pdev->dev, "cr-backlight",
					&pdev->dev, शून्य, &cr_backlight_ops,
					&props);
	अगर (IS_ERR(bdp)) अणु
		pci_dev_put(lpc_dev);
		वापस PTR_ERR(bdp);
	पूर्ण

	ldp = devm_lcd_device_रेजिस्टर(&pdev->dev, "cr-lcd", &pdev->dev, शून्य,
					&cr_lcd_ops);
	अगर (IS_ERR(ldp)) अणु
		pci_dev_put(lpc_dev);
		वापस PTR_ERR(ldp);
	पूर्ण

	pci_पढ़ो_config_dword(lpc_dev, CRVML_REG_GPIOBAR,
			      &gpio_bar);
	gpio_bar &= ~0x3F;

	crp = devm_kzalloc(&pdev->dev, माप(*crp), GFP_KERNEL);
	अगर (!crp) अणु
		pci_dev_put(lpc_dev);
		वापस -ENOMEM;
	पूर्ण

	crp->cr_backlight_device = bdp;
	crp->cr_lcd_device = ldp;
	crp->cr_backlight_device->props.घातer = FB_BLANK_UNBLANK;
	crp->cr_backlight_device->props.brightness = 0;
	cr_backlight_set_पूर्णांकensity(crp->cr_backlight_device);
	cr_lcd_set_घातer(crp->cr_lcd_device, FB_BLANK_UNBLANK);

	platक्रमm_set_drvdata(pdev, crp);

	वापस 0;
पूर्ण

अटल पूर्णांक cr_backlight_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cr_panel *crp = platक्रमm_get_drvdata(pdev);

	crp->cr_backlight_device->props.घातer = FB_BLANK_POWERDOWN;
	crp->cr_backlight_device->props.brightness = 0;
	crp->cr_backlight_device->props.max_brightness = 0;
	cr_backlight_set_पूर्णांकensity(crp->cr_backlight_device);
	cr_lcd_set_घातer(crp->cr_lcd_device, FB_BLANK_POWERDOWN);
	pci_dev_put(lpc_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cr_backlight_driver = अणु
	.probe = cr_backlight_probe,
	.हटाओ = cr_backlight_हटाओ,
	.driver = अणु
		   .name = "cr_backlight",
		   पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *crp;

अटल पूर्णांक __init cr_backlight_init(व्योम)
अणु
	पूर्णांक ret = platक्रमm_driver_रेजिस्टर(&cr_backlight_driver);

	अगर (ret)
		वापस ret;

	crp = platक्रमm_device_रेजिस्टर_simple("cr_backlight", -1, शून्य, 0);
	अगर (IS_ERR(crp)) अणु
		platक्रमm_driver_unरेजिस्टर(&cr_backlight_driver);
		वापस PTR_ERR(crp);
	पूर्ण

	pr_info("Carillo Ranch Backlight Driver Initialized.\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास cr_backlight_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(crp);
	platक्रमm_driver_unरेजिस्टर(&cr_backlight_driver);
पूर्ण

module_init(cr_backlight_init);
module_निकास(cr_backlight_निकास);

MODULE_AUTHOR("Tungsten Graphics Inc.");
MODULE_DESCRIPTION("Carillo Ranch Backlight Driver");
MODULE_LICENSE("GPL");
