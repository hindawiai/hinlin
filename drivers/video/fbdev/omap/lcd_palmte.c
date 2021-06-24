<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LCD panel support क्रम the Palm Tungsten E
 *
 * Original version : Roमुख्य Goyet <r.goyet@gmail.com>
 * Current version : Laurent Gonzalez <palmte.linux@मुक्त.fr>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>

#समावेश "omapfb.h"

अटल काष्ठा lcd_panel palmte_panel = अणु
	.name		= "palmte",
	.config		= OMAP_LCDC_PANEL_TFT | OMAP_LCDC_INV_VSYNC |
			  OMAP_LCDC_INV_HSYNC | OMAP_LCDC_HSVS_RISING_EDGE |
			  OMAP_LCDC_HSVS_OPPOSITE,

	.data_lines	= 16,
	.bpp		= 8,
	.pixel_घड़ी	= 12000,
	.x_res		= 320,
	.y_res		= 320,
	.hsw		= 4,
	.hfp		= 8,
	.hbp		= 28,
	.vsw		= 1,
	.vfp		= 8,
	.vbp		= 7,
	.pcd		= 0,
पूर्ण;

अटल पूर्णांक palmte_panel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	omapfb_रेजिस्टर_panel(&palmte_panel);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver palmte_panel_driver = अणु
	.probe		= palmte_panel_probe,
	.driver		= अणु
		.name	= "lcd_palmte",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(palmte_panel_driver);

MODULE_AUTHOR("Romain Goyet <r.goyet@gmail.com>, Laurent Gonzalez <palmte.linux@free.fr>");
MODULE_DESCRIPTION("LCD panel support for the Palm Tungsten E");
MODULE_LICENSE("GPL");
