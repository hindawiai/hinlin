<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-ep93xx/adssphere.c
 * ADS Sphere support.
 *
 * Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sizes.h>

#समावेश "hardware.h"

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "soc.h"

अटल काष्ठा ep93xx_eth_data __initdata adssphere_eth_data = अणु
	.phy_id		= 1,
पूर्ण;

अटल व्योम __init adssphere_init_machine(व्योम)
अणु
	ep93xx_init_devices();
	ep93xx_रेजिस्टर_flash(4, EP93XX_CS6_PHYS_BASE, SZ_32M);
	ep93xx_रेजिस्टर_eth(&adssphere_eth_data, 1);
पूर्ण

MACHINE_START(ADSSPHERE, "ADS Sphere board")
	/* Maपूर्णांकainer: Lennert Buytenhek <buytenh@wantstofly.org> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= adssphere_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
