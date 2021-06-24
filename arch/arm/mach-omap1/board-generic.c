<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap1/board-generic.c
 *
 * Modअगरied from board-innovator1510.c
 *
 * Code क्रम generic OMAP board. Should work on many OMAP प्रणालीs where
 * the device drivers take care of all the necessary hardware initialization.
 * Do not put any board specअगरic code to this file; create a new machine
 * type अगर you need custom low-level initializations.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <mach/mux.h>

#समावेश <mach/usb.h>

#समावेश "common.h"

/* assume no Mini-AB port */

#अगर_घोषित CONFIG_ARCH_OMAP15XX
अटल काष्ठा omap_usb_config generic1510_usb_config __initdata = अणु
	.रेजिस्टर_host	= 1,
	.रेजिस्टर_dev	= 1,
	.hmc_mode	= 16,
	.pins[0]	= 3,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_OMAP16XX)
अटल काष्ठा omap_usb_config generic1610_usb_config __initdata = अणु
#अगर_घोषित CONFIG_USB_OTG
	.otg		= 1,
#पूर्ण_अगर
	.रेजिस्टर_host	= 1,
	.रेजिस्टर_dev	= 1,
	.hmc_mode	= 16,
	.pins[0]	= 6,
पूर्ण;
#पूर्ण_अगर

अटल व्योम __init omap_generic_init(व्योम)
अणु
#अगर_घोषित CONFIG_ARCH_OMAP15XX
	अगर (cpu_is_omap15xx()) अणु
		/* mux pins क्रम uarts */
		omap_cfg_reg(UART1_TX);
		omap_cfg_reg(UART1_RTS);
		omap_cfg_reg(UART2_TX);
		omap_cfg_reg(UART2_RTS);
		omap_cfg_reg(UART3_TX);
		omap_cfg_reg(UART3_RX);

		omap1_usb_init(&generic1510_usb_config);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_OMAP16XX)
	अगर (!cpu_is_omap1510()) अणु
		omap1_usb_init(&generic1610_usb_config);
	पूर्ण
#पूर्ण_अगर

	omap_serial_init();
	omap_रेजिस्टर_i2c_bus(1, 100, शून्य, 0);
पूर्ण

MACHINE_START(OMAP_GENERIC, "Generic OMAP1510/1610/1710")
	/* Maपूर्णांकainer: Tony Lindgren <tony@atomide.com> */
	.atag_offset	= 0x100,
	.map_io		= omap16xx_map_io,
	.init_early	= omap1_init_early,
	.init_irq	= omap1_init_irq,
	.handle_irq	= omap1_handle_irq,
	.init_machine	= omap_generic_init,
	.init_late	= omap1_init_late,
	.init_समय	= omap1_समयr_init,
	.restart	= omap1_restart,
MACHINE_END
