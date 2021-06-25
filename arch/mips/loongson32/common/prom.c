<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 Zhang, Keguang <keguang.zhang@gmail.com>
 *
 * Modअगरied from arch/mips/pnx833x/common/prom.c.
 */

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/serial_reg.h>
#समावेश <यंत्र/fw/fw.h>

#समावेश <loongson1.h>

अचिन्हित दीर्घ memsize;

व्योम __init prom_init(व्योम)
अणु
	व्योम __iomem *uart_base;

	fw_init_cmdline();

	memsize = fw_दो_पर्याl("memsize");
	अगर(!memsize)
		memsize = DEFAULT_MEMSIZE;

	अगर (म_माला(arcs_cmdline, "console=ttyS3"))
		uart_base = ioremap(LS1X_UART3_BASE, 0x0f);
	अन्यथा अगर (म_माला(arcs_cmdline, "console=ttyS2"))
		uart_base = ioremap(LS1X_UART2_BASE, 0x0f);
	अन्यथा अगर (म_माला(arcs_cmdline, "console=ttyS1"))
		uart_base = ioremap(LS1X_UART1_BASE, 0x0f);
	अन्यथा
		uart_base = ioremap(LS1X_UART0_BASE, 0x0f);
	setup_8250_early_prपूर्णांकk_port((अचिन्हित दीर्घ)uart_base, 0, 0);
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	memblock_add(0x0, (memsize << 20));
पूर्ण
