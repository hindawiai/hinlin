<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LCD panel support क्रम the TI OMAP OSK board
 *
 * Copyright (C) 2004 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 * Adapted क्रम OSK by <dirk.behme@de.bosch.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>

#समावेश <mach/hardware.h>
#समावेश <mach/mux.h>

#समावेश "omapfb.h"

अटल पूर्णांक osk_panel_enable(काष्ठा lcd_panel *panel)
अणु
	/* configure PWL pin */
	omap_cfg_reg(PWL);

	/* Enable PWL unit */
	omap_ग_लिखोb(0x01, OMAP_PWL_CLK_ENABLE);

	/* Set PWL level */
	omap_ग_लिखोb(0xFF, OMAP_PWL_ENABLE);

	/* set GPIO2 high (lcd घातer enabled) */
	gpio_set_value(2, 1);

	वापस 0;
पूर्ण

अटल व्योम osk_panel_disable(काष्ठा lcd_panel *panel)
अणु
	/* Set PWL level to zero */
	omap_ग_लिखोb(0x00, OMAP_PWL_ENABLE);

	/* Disable PWL unit */
	omap_ग_लिखोb(0x00, OMAP_PWL_CLK_ENABLE);

	/* set GPIO2 low */
	gpio_set_value(2, 0);
पूर्ण

अटल काष्ठा lcd_panel osk_panel = अणु
	.name		= "osk",
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

	.enable		= osk_panel_enable,
	.disable	= osk_panel_disable,
पूर्ण;

अटल पूर्णांक osk_panel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	omapfb_रेजिस्टर_panel(&osk_panel);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver osk_panel_driver = अणु
	.probe		= osk_panel_probe,
	.driver		= अणु
		.name	= "lcd_osk",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(osk_panel_driver);

MODULE_AUTHOR("Imre Deak");
MODULE_DESCRIPTION("LCD panel support for the TI OMAP OSK board");
MODULE_LICENSE("GPL");
