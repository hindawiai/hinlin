<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LCD panel support क्रम the TI OMAP1610 Innovator board
 *
 * Copyright (C) 2004 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/gpपन.स>
#समावेश "omapfb.h"

#घोषणा MODULE_NAME	"omapfb-lcd_h3"

अटल पूर्णांक innovator1610_panel_init(काष्ठा lcd_panel *panel,
				    काष्ठा omapfb_device *fbdev)
अणु
	पूर्णांक r = 0;

	/* configure GPIO(14, 15) as outमाला_दो */
	अगर (gpio_request_one(14, GPIOF_OUT_INIT_LOW, "lcd_en0")) अणु
		pr_err(MODULE_NAME ": can't request GPIO 14\n");
		r = -1;
		जाओ निकास;
	पूर्ण
	अगर (gpio_request_one(15, GPIOF_OUT_INIT_LOW, "lcd_en1")) अणु
		pr_err(MODULE_NAME ": can't request GPIO 15\n");
		gpio_मुक्त(14);
		r = -1;
		जाओ निकास;
	पूर्ण
निकास:
	वापस r;
पूर्ण

अटल व्योम innovator1610_panel_cleanup(काष्ठा lcd_panel *panel)
अणु
	gpio_मुक्त(15);
	gpio_मुक्त(14);
पूर्ण

अटल पूर्णांक innovator1610_panel_enable(काष्ठा lcd_panel *panel)
अणु
	/* set GPIO14 and GPIO15 high */
	gpio_set_value(14, 1);
	gpio_set_value(15, 1);
	वापस 0;
पूर्ण

अटल व्योम innovator1610_panel_disable(काष्ठा lcd_panel *panel)
अणु
	/* set GPIO13, GPIO14 and GPIO15 low */
	gpio_set_value(14, 0);
	gpio_set_value(15, 0);
पूर्ण

अटल काष्ठा lcd_panel innovator1610_panel = अणु
	.name		= "inn1610",
	.config		= OMAP_LCDC_PANEL_TFT,

	.bpp		= 16,
	.data_lines	= 16,
	.x_res		= 320,
	.y_res		= 240,
	.pixel_घड़ी	= 12500,
	.hsw		= 40,
	.hfp		= 40,
	.hbp		= 72,
	.vsw		= 1,
	.vfp		= 1,
	.vbp		= 0,
	.pcd		= 12,

	.init		= innovator1610_panel_init,
	.cleanup	= innovator1610_panel_cleanup,
	.enable		= innovator1610_panel_enable,
	.disable	= innovator1610_panel_disable,
पूर्ण;

अटल पूर्णांक innovator1610_panel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	omapfb_रेजिस्टर_panel(&innovator1610_panel);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver innovator1610_panel_driver = अणु
	.probe		= innovator1610_panel_probe,
	.driver		= अणु
		.name	= "lcd_inn1610",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(innovator1610_panel_driver);

MODULE_AUTHOR("Imre Deak");
MODULE_DESCRIPTION("LCD panel support for the TI OMAP1610 Innovator board");
MODULE_LICENSE("GPL");
