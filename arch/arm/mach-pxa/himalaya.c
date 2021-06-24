<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/himalaya.c
 *
 * Hardware definitions क्रम the HTC Himalaya
 *
 * Based on 2.6.21-hh20's himalaya.c and himalaya_lcd.c
 *
 * Copyright (c) 2008 Zbynek Michl <Zbynek.Michl@seznam.cz>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/fb.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <video/w100fb.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "pxa25x.h"

#समावेश "generic.h"

/* ---------------------- Himalaya LCD definitions -------------------- */

अटल काष्ठा w100_gen_regs himalaya_lcd_regs = अणु
	.lcd_क्रमmat =        0x00000003,
	.lcdd_cntl1 =        0x00000000,
	.lcdd_cntl2 =        0x0003ffff,
	.genlcd_cntl1 =      0x00fff003,
	.genlcd_cntl2 =      0x00000003,
	.genlcd_cntl3 =      0x000102aa,
पूर्ण;

अटल काष्ठा w100_mode himalaya4_lcd_mode = अणु
	.xres 		= 240,
	.yres 		= 320,
	.left_margin 	= 0,
	.right_margin 	= 31,
	.upper_margin 	= 15,
	.lower_margin 	= 0,
	.crtc_ss	= 0x80150014,
	.crtc_ls	= 0xa0fb00f7,
	.crtc_gs	= 0xc0080007,
	.crtc_vpos_gs	= 0x00080007,
	.crtc_rev	= 0x0000000a,
	.crtc_dclk	= 0x81700030,
	.crtc_gclk	= 0x8015010f,
	.crtc_goe	= 0x00000000,
	.pll_freq 	= 80,
	.pixclk_भागider = 15,
	.pixclk_भागider_rotated = 15,
	.pixclk_src     = CLK_SRC_PLL,
	.sysclk_भागider = 0,
	.sysclk_src     = CLK_SRC_PLL,
पूर्ण;

अटल काष्ठा w100_mode himalaya6_lcd_mode = अणु
	.xres 		= 240,
	.yres 		= 320,
	.left_margin 	= 9,
	.right_margin 	= 8,
	.upper_margin 	= 5,
	.lower_margin 	= 4,
	.crtc_ss	= 0x80150014,
	.crtc_ls	= 0xa0fb00f7,
	.crtc_gs	= 0xc0080007,
	.crtc_vpos_gs	= 0x00080007,
	.crtc_rev	= 0x0000000a,
	.crtc_dclk	= 0xa1700030,
	.crtc_gclk	= 0x8015010f,
	.crtc_goe	= 0x00000000,
	.pll_freq 	= 95,
	.pixclk_भागider = 0xb,
	.pixclk_भागider_rotated = 4,
	.pixclk_src     = CLK_SRC_PLL,
	.sysclk_भागider = 1,
	.sysclk_src     = CLK_SRC_PLL,
पूर्ण;

अटल काष्ठा w100_gpio_regs himalaya_w100_gpio_info = अणु
	.init_data1 = 0xffff0000,	/* GPIO_DATA  */
	.gpio_dir1  = 0x00000000,	/* GPIO_CNTL1 */
	.gpio_oe1   = 0x003c0000,	/* GPIO_CNTL2 */
	.init_data2 = 0x00000000,	/* GPIO_DATA2 */
	.gpio_dir2  = 0x00000000,	/* GPIO_CNTL3 */
	.gpio_oe2   = 0x00000000,	/* GPIO_CNTL4 */
पूर्ण;

अटल काष्ठा w100fb_mach_info himalaya_fb_info = अणु
	.num_modes  = 1,
	.regs       = &himalaya_lcd_regs,
	.gpio       = &himalaya_w100_gpio_info,
	.xtal_freq = 16000000,
पूर्ण;

अटल काष्ठा resource himalaya_fb_resources[] = अणु
	[0] = अणु
		.start	= 0x08000000,
		.end	= 0x08ffffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device himalaya_fb_device = अणु
	.name           = "w100fb",
	.id             = -1,
	.dev            = अणु
		.platक्रमm_data  = &himalaya_fb_info,
	पूर्ण,
	.num_resources  = ARRAY_SIZE(himalaya_fb_resources),
	.resource       = himalaya_fb_resources,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&himalaya_fb_device,
पूर्ण;

अटल व्योम __init himalaya_lcd_init(व्योम)
अणु
	पूर्णांक himalaya_boardid;

	himalaya_boardid = 0x4; /* hardcoded (detection needs ASIC3 functions) */
	prपूर्णांकk(KERN_INFO "himalaya LCD Driver init. boardid=%d\n",
		himalaya_boardid);

	चयन (himalaya_boardid) अणु
	हाल 0x4:
		himalaya_fb_info.modelist = &himalaya4_lcd_mode;
	अवरोध;
	हाल 0x6:
		himalaya_fb_info.modelist = &himalaya6_lcd_mode;
	अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "himalaya lcd_init: unknown boardid=%d. Using 0x4\n",
			himalaya_boardid);
		himalaya_fb_info.modelist = &himalaya4_lcd_mode;
	पूर्ण
पूर्ण

अटल व्योम __init himalaya_init(व्योम)
अणु
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	himalaya_lcd_init();
	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
पूर्ण


MACHINE_START(HIMALAYA, "HTC Himalaya")
	.atag_offset = 0x100,
	.map_io = pxa25x_map_io,
	.nr_irqs = PXA_NR_IRQS,
	.init_irq = pxa25x_init_irq,
	.handle_irq = pxa25x_handle_irq,
	.init_machine = himalaya_init,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END
