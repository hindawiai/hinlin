<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LCD panel support क्रम the TI OMAP H3 board
 *
 * Copyright (C) 2004 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/tps65010.h>
#समावेश <linux/gpपन.स>

#समावेश "omapfb.h"

#घोषणा MODULE_NAME	"omapfb-lcd_h3"

अटल पूर्णांक h3_panel_enable(काष्ठा lcd_panel *panel)
अणु
	पूर्णांक r = 0;

	/* GPIO1 and GPIO2 of TPS65010 send LCD_ENBKL and LCD_ENVDD संकेतs */
	r = tps65010_set_gpio_out_value(GPIO1, HIGH);
	अगर (!r)
		r = tps65010_set_gpio_out_value(GPIO2, HIGH);
	अगर (r)
		pr_err(MODULE_NAME ": Unable to turn on LCD panel\n");

	वापस r;
पूर्ण

अटल व्योम h3_panel_disable(काष्ठा lcd_panel *panel)
अणु
	पूर्णांक r = 0;

	/* GPIO1 and GPIO2 of TPS65010 send LCD_ENBKL and LCD_ENVDD संकेतs */
	r = tps65010_set_gpio_out_value(GPIO1, LOW);
	अगर (!r)
		tps65010_set_gpio_out_value(GPIO2, LOW);
	अगर (r)
		pr_err(MODULE_NAME ": Unable to turn off LCD panel\n");
पूर्ण

अटल काष्ठा lcd_panel h3_panel = अणु
	.name		= "h3",
	.config		= OMAP_LCDC_PANEL_TFT,

	.data_lines	= 16,
	.bpp		= 16,
	.x_res		= 240,
	.y_res		= 320,
	.pixel_घड़ी	= 12000,
	.hsw		= 12,
	.hfp		= 14,
	.hbp		= 72 - 12,
	.vsw		= 1,
	.vfp		= 1,
	.vbp		= 0,
	.pcd		= 0,

	.enable		= h3_panel_enable,
	.disable	= h3_panel_disable,
पूर्ण;

अटल पूर्णांक h3_panel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	omapfb_रेजिस्टर_panel(&h3_panel);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver h3_panel_driver = अणु
	.probe		= h3_panel_probe,
	.driver		= अणु
		.name	= "lcd_h3",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(h3_panel_driver);

MODULE_AUTHOR("Imre Deak");
MODULE_DESCRIPTION("LCD panel support for the TI OMAP H3 board");
MODULE_LICENSE("GPL");
