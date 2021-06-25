<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-ep93xx/micro9.c
 *
 * Copyright (C) 2006 Contec Steuerungstechnik & Automation GmbH
 *                    Manfred Gruber <m.gruber@tirol.com>
 * Copyright (C) 2009 Contec Steuerungstechnik & Automation GmbH
 *                    Hubert Feurstein <hubert.feurstein@contec.at>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>

#समावेश "hardware.h"

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "soc.h"

/*************************************************************************
 * Micro9 NOR Flash
 *
 * Micro9-High has up to 64MB of 32-bit flash on CS1
 * Micro9-Mid has up to 64MB of either 32-bit or 16-bit flash on CS1
 * Micro9-Lite uses a separate MTD map driver क्रम flash support
 * Micro9-Slim has up to 64MB of either 32-bit or 16-bit flash on CS1
 *************************************************************************/
अटल अचिन्हित पूर्णांक __init micro9_detect_bootwidth(व्योम)
अणु
	u32 v;

	/* Detect the bus width of the बाह्यal flash memory */
	v = __raw_पढ़ोl(EP93XX_SYSCON_SYSCFG);
	अगर (v & EP93XX_SYSCON_SYSCFG_LCSN7)
		वापस 4; /* 32-bit */
	अन्यथा
		वापस 2; /* 16-bit */
पूर्ण

अटल व्योम __init micro9_रेजिस्टर_flash(व्योम)
अणु
	अचिन्हित पूर्णांक width;

	अगर (machine_is_micro9())
		width = 4;
	अन्यथा अगर (machine_is_micro9m() || machine_is_micro9s())
		width = micro9_detect_bootwidth();
	अन्यथा
		width = 0;

	अगर (width)
		ep93xx_रेजिस्टर_flash(width, EP93XX_CS1_PHYS_BASE, SZ_64M);
पूर्ण


/*************************************************************************
 * Micro9 Ethernet
 *************************************************************************/
अटल काष्ठा ep93xx_eth_data __initdata micro9_eth_data = अणु
	.phy_id		= 0x1f,
पूर्ण;


अटल व्योम __init micro9_init_machine(व्योम)
अणु
	ep93xx_init_devices();
	ep93xx_रेजिस्टर_eth(&micro9_eth_data, 1);
	micro9_रेजिस्टर_flash();
पूर्ण


#अगर_घोषित CONFIG_MACH_MICRO9H
MACHINE_START(MICRO9, "Contec Micro9-High")
	/* Maपूर्णांकainer: Hubert Feurstein <hubert.feurstein@contec.at> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= micro9_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_MICRO9M
MACHINE_START(MICRO9M, "Contec Micro9-Mid")
	/* Maपूर्णांकainer: Hubert Feurstein <hubert.feurstein@contec.at> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= micro9_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_MICRO9L
MACHINE_START(MICRO9L, "Contec Micro9-Lite")
	/* Maपूर्णांकainer: Hubert Feurstein <hubert.feurstein@contec.at> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= micro9_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_MICRO9S
MACHINE_START(MICRO9S, "Contec Micro9-Slim")
	/* Maपूर्णांकainer: Hubert Feurstein <hubert.feurstein@contec.at> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= micro9_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
#पूर्ण_अगर
