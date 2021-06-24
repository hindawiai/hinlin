<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * File: drivers/video/omap/lcd-htcherald.c
 *
 * LCD panel support क्रम the HTC Herald
 *
 * Copyright (C) 2009 Cory Maccarrone <darkstar6262@gmail.com>
 * Copyright (C) 2009 Wing Linux
 *
 * Based on the lcd_htcwizard.c file from the linwizard project:
 * Copyright (C) linwizard.sourceक्रमge.net
 * Author: Angelo Arrअगरano <miknix@gmail.com>
 * Based on lcd_h4 by Imre Deak <imre.deak@nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "omapfb.h"

/* Found on WIZ200 (miknix) and some HERA110 models (darkstar62) */
अटल काष्ठा lcd_panel htcherald_panel_1 = अणु
	.name		= "lcd_herald",
	.config		= OMAP_LCDC_PANEL_TFT |
			  OMAP_LCDC_INV_HSYNC |
			  OMAP_LCDC_INV_VSYNC |
			  OMAP_LCDC_INV_PIX_CLOCK,
	.bpp		= 16,
	.data_lines	= 16,
	.x_res		= 240,
	.y_res		= 320,
	.pixel_घड़ी	= 6093,
	.pcd		= 0, /* 15 */
	.hsw		= 10,
	.hfp		= 10,
	.hbp		= 20,
	.vsw		= 3,
	.vfp		= 2,
	.vbp		= 2,
पूर्ण;

अटल पूर्णांक htcherald_panel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	omapfb_रेजिस्टर_panel(&htcherald_panel_1);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver htcherald_panel_driver = अणु
	.probe		= htcherald_panel_probe,
	.driver		= अणु
		.name	= "lcd_htcherald",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(htcherald_panel_driver);

MODULE_AUTHOR("Cory Maccarrone");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LCD panel support for the HTC Herald");
