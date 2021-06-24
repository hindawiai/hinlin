<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * File: arch/arm/plat-omap/fb.c
 *
 * Framebuffer device registration क्रम TI OMAP platक्रमms
 *
 * Copyright (C) 2006 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/memblock.h>
#समावेश <linux/पन.स>
#समावेश <linux/omapfb.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/mach/map.h>

#अगर IS_ENABLED(CONFIG_FB_OMAP)

अटल bool omapfb_lcd_configured;
अटल काष्ठा omapfb_platक्रमm_data omapfb_config;

अटल u64 omap_fb_dma_mask = ~(u32)0;

अटल काष्ठा platक्रमm_device omap_fb_device = अणु
	.name		= "omapfb",
	.id		= -1,
	.dev = अणु
		.dma_mask		= &omap_fb_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &omapfb_config,
	पूर्ण,
	.num_resources = 0,
पूर्ण;

व्योम __init omapfb_set_lcd_config(स्थिर काष्ठा omap_lcd_config *config)
अणु
	omapfb_config.lcd = *config;
	omapfb_lcd_configured = true;
पूर्ण

अटल पूर्णांक __init omap_init_fb(व्योम)
अणु
	/*
	 * If the board file has not set the lcd config with
	 * omapfb_set_lcd_config(), करोn't bother रेजिस्टरing the omapfb device
	 */
	अगर (!omapfb_lcd_configured)
		वापस 0;

	वापस platक्रमm_device_रेजिस्टर(&omap_fb_device);
पूर्ण

arch_initcall(omap_init_fb);

#अन्यथा

व्योम __init omapfb_set_lcd_config(स्थिर काष्ठा omap_lcd_config *config)
अणु
पूर्ण

#पूर्ण_अगर
