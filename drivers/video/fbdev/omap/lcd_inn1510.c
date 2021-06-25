<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LCD panel support क्रम the TI OMAP1510 Innovator board
 *
 * Copyright (C) 2004 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>

#समावेश <mach/hardware.h>

#समावेश "omapfb.h"

अटल पूर्णांक innovator1510_panel_enable(काष्ठा lcd_panel *panel)
अणु
	__raw_ग_लिखोb(0x7, OMAP1510_FPGA_LCD_PANEL_CONTROL);
	वापस 0;
पूर्ण

अटल व्योम innovator1510_panel_disable(काष्ठा lcd_panel *panel)
अणु
	__raw_ग_लिखोb(0x0, OMAP1510_FPGA_LCD_PANEL_CONTROL);
पूर्ण

अटल काष्ठा lcd_panel innovator1510_panel = अणु
	.name		= "inn1510",
	.config		= OMAP_LCDC_PANEL_TFT,

	.bpp		= 16,
	.data_lines	= 16,
	.x_res		= 240,
	.y_res		= 320,
	.pixel_घड़ी	= 12500,
	.hsw		= 40,
	.hfp		= 40,
	.hbp		= 72,
	.vsw		= 1,
	.vfp		= 1,
	.vbp		= 0,
	.pcd		= 12,

	.enable		= innovator1510_panel_enable,
	.disable	= innovator1510_panel_disable,
पूर्ण;

अटल पूर्णांक innovator1510_panel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	omapfb_रेजिस्टर_panel(&innovator1510_panel);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver innovator1510_panel_driver = अणु
	.probe		= innovator1510_panel_probe,
	.driver		= अणु
		.name	= "lcd_inn1510",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(innovator1510_panel_driver);

MODULE_AUTHOR("Imre Deak");
MODULE_DESCRIPTION("LCD panel support for the TI OMAP1510 Innovator board");
MODULE_LICENSE("GPL");
