<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Staging board support क्रम Armadillo 800 eva.
 * Enable not-yet-DT-capable devices here.
 *
 * Based on board-armadillo800eva.c
 *
 * Copyright (C) 2012 Renesas Solutions Corp.
 * Copyright (C) 2012 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/fb.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>

#समावेश <video/sh_mobile_lcdc.h>

#समावेश "board.h"

अटल काष्ठा fb_videomode lcdc0_mode = अणु
	.name		= "AMPIER/AM-800480",
	.xres		= 800,
	.yres		= 480,
	.left_margin	= 88,
	.right_margin	= 40,
	.hsync_len	= 128,
	.upper_margin	= 20,
	.lower_margin	= 5,
	.vsync_len	= 5,
	.sync		= 0,
पूर्ण;

अटल काष्ठा sh_mobile_lcdc_info lcdc0_info = अणु
	.घड़ी_source	= LCDC_CLK_BUS,
	.ch[0] = अणु
		.chan		= LCDC_CHAN_MAINLCD,
		.fourcc		= V4L2_PIX_FMT_RGB565,
		.पूर्णांकerface_type	= RGB24,
		.घड़ी_भागider	= 5,
		.flags		= 0,
		.lcd_modes	= &lcdc0_mode,
		.num_modes	= 1,
		.panel_cfg = अणु
			.width	= 111,
			.height = 68,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource lcdc0_resources[] = अणु
	DEFINE_RES_MEM_NAMED(0xfe940000, 0x4000, "LCD0"),
	DEFINE_RES_IRQ(177 + 32),
पूर्ण;

अटल काष्ठा platक्रमm_device lcdc0_device = अणु
	.name		= "sh_mobile_lcdc_fb",
	.num_resources	= ARRAY_SIZE(lcdc0_resources),
	.resource	= lcdc0_resources,
	.id		= 0,
	.dev	= अणु
		.platक्रमm_data	= &lcdc0_info,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा board_staging_clk lcdc0_घड़ीs[] __initस्थिर = अणु
	अणु "lcdc0", शून्य, "sh_mobile_lcdc_fb.0" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा board_staging_dev armadillo800eva_devices[] __initस्थिर = अणु
	अणु
		.pdev	 = &lcdc0_device,
		.घड़ीs	 = lcdc0_घड़ीs,
		.nघड़ीs = ARRAY_SIZE(lcdc0_घड़ीs),
		.करोमुख्य	 = "/system-controller@e6180000/pm-domains/c5/a4lc@1"
	पूर्ण,
पूर्ण;

अटल व्योम __init armadillo800eva_init(व्योम)
अणु
	board_staging_gic_setup_xlate("arm,pl390", 32);
	board_staging_रेजिस्टर_devices(armadillo800eva_devices,
				       ARRAY_SIZE(armadillo800eva_devices));
पूर्ण

board_staging("renesas,armadillo800eva", armadillo800eva_init);
