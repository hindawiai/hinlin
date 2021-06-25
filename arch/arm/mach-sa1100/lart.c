<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/arm/mach-sa1100/lart.c
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <video/sa1100fb.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/page.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <linux/platक्रमm_data/mfd-mcp-sa11x0.h>
#समावेश <mach/irqs.h>

#समावेश "generic.h"

अटल काष्ठा mcp_plat_data lart_mcp_data = अणु
	.mccr0		= MCCR0_ADM,
	.sclk_rate	= 11981000,
पूर्ण;

#अगर_घोषित LART_GREY_LCD
अटल काष्ठा sa1100fb_mach_info lart_grey_info = अणु
	.pixघड़ी	= 150000,	.bpp		= 4,
	.xres		= 320,		.yres		= 240,

	.hsync_len	= 1,		.vsync_len	= 1,
	.left_margin	= 4,		.upper_margin	= 0,
	.right_margin	= 2,		.lower_margin	= 0,

	.cmap_greyscale	= 1,
	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,

	.lccr0		= LCCR0_Mono | LCCR0_Sngl | LCCR0_Pas | LCCR0_4PixMono,
	.lccr3		= LCCR3_OutEnH | LCCR3_PixRsEdg | LCCR3_ACBsDiv(512),
पूर्ण;
#पूर्ण_अगर
#अगर_घोषित LART_COLOR_LCD
अटल काष्ठा sa1100fb_mach_info lart_color_info = अणु
	.pixघड़ी	= 150000,	.bpp		= 16,
	.xres		= 320,		.yres		= 240,

	.hsync_len	= 2,		.vsync_len	= 3,
	.left_margin	= 69,		.upper_margin	= 14,
	.right_margin	= 8,		.lower_margin	= 4,

	.lccr0		= LCCR0_Color | LCCR0_Sngl | LCCR0_Act,
	.lccr3		= LCCR3_OutEnH | LCCR3_PixFlEdg | LCCR3_ACBsDiv(512),
पूर्ण;
#पूर्ण_अगर
#अगर_घोषित LART_VIDEO_OUT
अटल काष्ठा sa1100fb_mach_info lart_video_info = अणु
	.pixघड़ी	= 39721,	.bpp		= 16,
	.xres		= 640,		.yres		= 480,

	.hsync_len	= 95,		.vsync_len	= 2,
	.left_margin	= 40,		.upper_margin	= 32,
	.right_margin	= 24,		.lower_margin	= 11,

	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,

	.lccr0		= LCCR0_Color | LCCR0_Sngl | LCCR0_Act,
	.lccr3		= LCCR3_OutEnL | LCCR3_PixFlEdg | LCCR3_ACBsDiv(512),
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित LART_KIT01_LCD
अटल काष्ठा sa1100fb_mach_info lart_kit01_info = अणु
	.pixघड़ी	= 63291,	.bpp		= 16,
	.xres		= 640,		.yres		= 480,

	.hsync_len	= 64,		.vsync_len	= 3,
	.left_margin	= 122,		.upper_margin	= 45,
	.right_margin	= 10,		.lower_margin	= 10,

	.lccr0		= LCCR0_Color | LCCR0_Sngl | LCCR0_Act,
	.lccr3		= LCCR3_OutEnH | LCCR3_PixFlEdg
पूर्ण;
#पूर्ण_अगर

अटल व्योम __init lart_init(व्योम)
अणु
	काष्ठा sa1100fb_mach_info *inf = शून्य;

#अगर_घोषित LART_GREY_LCD
	inf = &lart_grey_info;
#पूर्ण_अगर
#अगर_घोषित LART_COLOR_LCD
	inf = &lart_color_info;
#पूर्ण_अगर
#अगर_घोषित LART_VIDEO_OUT
	inf = &lart_video_info;
#पूर्ण_अगर
#अगर_घोषित LART_KIT01_LCD
	inf = &lart_kit01_info;
#पूर्ण_अगर

	अगर (inf)
		sa11x0_रेजिस्टर_lcd(inf);

	sa11x0_ppc_configure_mcp();
	sa11x0_रेजिस्टर_mcp(&lart_mcp_data);
पूर्ण

अटल काष्ठा map_desc lart_io_desc[] __initdata = अणु
	अणु	/* मुख्य flash memory */
		.भव	=  0xe8000000,
		.pfn		= __phys_to_pfn(0x00000000),
		.length		= 0x00400000,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* मुख्य flash, alternative location */
		.भव	=  0xec000000,
		.pfn		= __phys_to_pfn(0x08000000),
		.length		= 0x00400000,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

/* LEDs */
काष्ठा gpio_led lart_gpio_leds[] = अणु
	अणु
		.name			= "lart:red",
		.शेष_trigger	= "cpu0",
		.gpio			= 23,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data lart_gpio_led_info = अणु
	.leds		= lart_gpio_leds,
	.num_leds	= ARRAY_SIZE(lart_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device lart_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &lart_gpio_led_info,
	पूर्ण
पूर्ण;
अटल व्योम __init lart_map_io(व्योम)
अणु
	sa1100_map_io();
	iotable_init(lart_io_desc, ARRAY_SIZE(lart_io_desc));

	sa1100_रेजिस्टर_uart(0, 3);
	sa1100_रेजिस्टर_uart(1, 1);
	sa1100_रेजिस्टर_uart(2, 2);

	GAFR |= (GPIO_UART_TXD | GPIO_UART_RXD);
	GPDR |= GPIO_UART_TXD;
	GPDR &= ~GPIO_UART_RXD;
	PPAR |= PPAR_UPR;

	platक्रमm_device_रेजिस्टर(&lart_leds);
पूर्ण

MACHINE_START(LART, "LART")
	.atag_offset	= 0x100,
	.map_io		= lart_map_io,
	.nr_irqs	= SA1100_NR_IRQS,
	.init_irq	= sa1100_init_irq,
	.init_machine	= lart_init,
	.init_late	= sa11x0_init_late,
	.init_समय	= sa1100_समयr_init,
	.restart	= sa11x0_restart,
MACHINE_END
