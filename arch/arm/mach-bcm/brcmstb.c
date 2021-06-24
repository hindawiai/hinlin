<शैली गुरु>
/*
 * Copyright (C) 2013-2014 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

/*
 * Storage क्रम debug-macro.S's state.
 *
 * This must be in .data not .bss so that it माला_लो initialized each समय the
 * kernel is loaded. The data is declared here rather than debug-macro.S so
 * that multiple inclusions of debug-macro.S poपूर्णांक at the same data.
 */
u32 brcmstb_uart_config[3] = अणु
	/* Debug UART initialization required */
	1,
	/* Debug UART physical address */
	0,
	/* Debug UART भव address */
	0,
पूर्ण;

अटल व्योम __init brcmstb_init_irq(व्योम)
अणु
	irqchip_init();
पूर्ण

अटल स्थिर अक्षर *स्थिर brcmstb_match[] __initस्थिर = अणु
	"brcm,bcm7445",
	"brcm,brcmstb",
	शून्य
पूर्ण;

DT_MACHINE_START(BRCMSTB, "Broadcom STB (Flattened Device Tree)")
	.dt_compat	= brcmstb_match,
	.init_irq	= brcmstb_init_irq,
MACHINE_END
