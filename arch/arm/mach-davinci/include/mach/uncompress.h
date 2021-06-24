<शैली गुरु>
/*
 * Serial port stubs क्रम kernel decompress status messages
 *
 * Initially based on:
 * arch/arm/plat-omap/include/mach/uncompress.h
 *
 * Original copyrights follow.
 *
 * Copyright (C) 2000 RidgeRun, Inc.
 * Author: Greg Lonnon <glonnon@ridgerun.com>
 *
 * Rewritten by:
 * Author: <source@mvista.com>
 * 2004 (c) MontaVista Software, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/types.h>
#समावेश <linux/serial_reg.h>

#समावेश <यंत्र/mach-types.h>

#समावेश <mach/serial.h>

#घोषणा IOMEM(x)	((व्योम __क्रमce __iomem *)(x))

u32 *uart;

/* PORT_16C550A, in polled non-fअगरo mode */
अटल अंतरभूत व्योम अ_दो(अक्षर c)
अणु
	अगर (!uart)
		वापस;

	जबतक (!(uart[UART_LSR] & UART_LSR_THRE))
		barrier();
	uart[UART_TX] = c;
पूर्ण

अटल अंतरभूत व्योम flush(व्योम)
अणु
	अगर (!uart)
		वापस;

	जबतक (!(uart[UART_LSR] & UART_LSR_THRE))
		barrier();
पूर्ण

अटल अंतरभूत व्योम set_uart_info(u32 phys)
अणु
	uart = (u32 *)phys;
पूर्ण

#घोषणा _DEBUG_LL_ENTRY(machine, phys)				\
	अणु							\
		अगर (machine_is_##machine()) अणु			\
			set_uart_info(phys);			\
			अवरोध;					\
		पूर्ण						\
	पूर्ण

#घोषणा DEBUG_LL_DAVINCI(machine, port)				\
	_DEBUG_LL_ENTRY(machine, DAVINCI_UART##port##_BASE)

#घोषणा DEBUG_LL_DA8XX(machine, port)				\
	_DEBUG_LL_ENTRY(machine, DA8XX_UART##port##_BASE)

अटल अंतरभूत व्योम __arch_decomp_setup(अचिन्हित दीर्घ arch_id)
अणु
	/*
	 * Initialize the port based on the machine ID from the bootloader.
	 * Note that we're using macros here instead of चयन statement
	 * as machine_is functions are optimized out क्रम the boards that
	 * are not selected.
	 */
	करो अणु
		/* Davinci boards */
		DEBUG_LL_DAVINCI(davinci_evm,		0);
		DEBUG_LL_DAVINCI(sffsdr,		0);
		DEBUG_LL_DAVINCI(neuros_osd2,		0);
		DEBUG_LL_DAVINCI(davinci_dm355_evm,	0);
		DEBUG_LL_DAVINCI(dm355_leopard,		0);
		DEBUG_LL_DAVINCI(davinci_dm6467_evm,	0);
		DEBUG_LL_DAVINCI(davinci_dm365_evm,	0);

		/* DA8xx boards */
		DEBUG_LL_DA8XX(davinci_da830_evm,	2);
		DEBUG_LL_DA8XX(davinci_da850_evm,	2);
		DEBUG_LL_DA8XX(mityomapl138,		1);
		DEBUG_LL_DA8XX(omapl138_hawkboard,	2);
	पूर्ण जबतक (0);
पूर्ण

#घोषणा arch_decomp_setup()	__arch_decomp_setup(arch_id)
