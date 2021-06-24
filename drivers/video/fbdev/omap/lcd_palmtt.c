<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LCD panel support क्रम Palm Tungsten|T
 * Current version : Marek Vasut <marek.vasut@gmail.com>
 *
 * Modअगरied from lcd_inn1510.c
 */

/*
GPIO11 - backlight
GPIO12 - screen blanking
GPIO13 - screen blanking
*/

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>

#समावेश "omapfb.h"

अटल अचिन्हित दीर्घ palmtt_panel_get_caps(काष्ठा lcd_panel *panel)
अणु
	वापस OMAPFB_CAPS_SET_BACKLIGHT;
पूर्ण

अटल काष्ठा lcd_panel palmtt_panel = अणु
	.name		= "palmtt",
	.config		= OMAP_LCDC_PANEL_TFT | OMAP_LCDC_INV_VSYNC |
			OMAP_LCDC_INV_HSYNC | OMAP_LCDC_HSVS_RISING_EDGE |
			OMAP_LCDC_HSVS_OPPOSITE,
	.bpp		= 16,
	.data_lines	= 16,
	.x_res		= 320,
	.y_res		= 320,
	.pixel_घड़ी	= 10000,
	.hsw		= 4,
	.hfp		= 8,
	.hbp		= 28,
	.vsw		= 1,
	.vfp		= 8,
	.vbp		= 7,
	.pcd		= 0,

	.get_caps	= palmtt_panel_get_caps,
पूर्ण;

अटल पूर्णांक palmtt_panel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	omapfb_रेजिस्टर_panel(&palmtt_panel);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver palmtt_panel_driver = अणु
	.probe		= palmtt_panel_probe,
	.driver		= अणु
		.name	= "lcd_palmtt",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(palmtt_panel_driver);

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("LCD panel support for Palm Tungsten|T");
MODULE_LICENSE("GPL");
