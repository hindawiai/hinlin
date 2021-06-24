<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LCD panel support क्रम the Palm Zire71
 *
 * Original version : Roमुख्य Goyet
 * Current version : Laurent Gonzalez
 * Modअगरied क्रम zire71 : Marek Vasut
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>

#समावेश "omapfb.h"

अटल अचिन्हित दीर्घ palmz71_panel_get_caps(काष्ठा lcd_panel *panel)
अणु
	वापस OMAPFB_CAPS_SET_BACKLIGHT;
पूर्ण

अटल काष्ठा lcd_panel palmz71_panel = अणु
	.name		= "palmz71",
	.config		= OMAP_LCDC_PANEL_TFT | OMAP_LCDC_INV_VSYNC |
			  OMAP_LCDC_INV_HSYNC | OMAP_LCDC_HSVS_RISING_EDGE |
			  OMAP_LCDC_HSVS_OPPOSITE,
	.data_lines	= 16,
	.bpp		= 16,
	.pixel_घड़ी	= 24000,
	.x_res		= 320,
	.y_res		= 320,
	.hsw		= 4,
	.hfp		= 8,
	.hbp		= 28,
	.vsw		= 1,
	.vfp		= 8,
	.vbp		= 7,
	.pcd		= 0,

	.get_caps	= palmz71_panel_get_caps,
पूर्ण;

अटल पूर्णांक palmz71_panel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	omapfb_रेजिस्टर_panel(&palmz71_panel);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver palmz71_panel_driver = अणु
	.probe		= palmz71_panel_probe,
	.driver		= अणु
		.name	= "lcd_palmz71",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(palmz71_panel_driver);

MODULE_AUTHOR("Romain Goyet, Laurent Gonzalez, Marek Vasut");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LCD panel support for the Palm Zire71");
