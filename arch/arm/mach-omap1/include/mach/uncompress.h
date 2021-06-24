<शैली गुरु>
/*
 * arch/arm/plat-omap/include/mach/uncompress.h
 *
 * Serial port stubs क्रम kernel decompress status messages
 *
 * Initially based on:
 * linux-2.4.15-rmk1-dsplinux1.6/arch/arm/plat-omap/include/mach1510/uncompress.h
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

#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "serial.h"

#घोषणा MDR1_MODE_MASK			0x07

अस्थिर u8 *uart_base;
पूर्णांक uart_shअगरt;

/*
 * Store the DEBUG_LL uart number पूर्णांकo memory.
 * See also debug-macro.S, and serial.c क्रम related code.
 */
अटल व्योम set_omap_uart_info(अचिन्हित अक्षर port)
अणु
	/*
	 * Get address of some.bss variable and round it करोwn
	 * a la CONFIG_AUTO_ZRELADDR.
	 */
	u32 ram_start = (u32)&uart_shअगरt & 0xf8000000;
	u32 *uart_info = (u32 *)(ram_start + OMAP_UART_INFO_OFS);
	*uart_info = port;
पूर्ण

अटल अंतरभूत व्योम अ_दो(पूर्णांक c)
अणु
	अगर (!uart_base)
		वापस;

	/* Check क्रम UART 16x mode */
	अगर ((uart_base[UART_OMAP_MDR1 << uart_shअगरt] & MDR1_MODE_MASK) != 0)
		वापस;

	जबतक (!(uart_base[UART_LSR << uart_shअगरt] & UART_LSR_THRE))
		barrier();
	uart_base[UART_TX << uart_shअगरt] = c;
पूर्ण

अटल अंतरभूत व्योम flush(व्योम)
अणु
पूर्ण

/*
 * Macros to configure UART1 and debug UART
 */
#घोषणा _DEBUG_LL_ENTRY(mach, dbg_uart, dbg_shft, dbg_id)		\
	अगर (machine_is_##mach()) अणु					\
		uart_base = (अस्थिर u8 *)(dbg_uart);			\
		uart_shअगरt = (dbg_shft);				\
		port = (dbg_id);					\
		set_omap_uart_info(port);				\
		अवरोध;							\
	पूर्ण

#घोषणा DEBUG_LL_OMAP7XX(p, mach)					\
	_DEBUG_LL_ENTRY(mach, OMAP1_UART##p##_BASE, OMAP7XX_PORT_SHIFT,	\
		OMAP1UART##p)

#घोषणा DEBUG_LL_OMAP1(p, mach)						\
	_DEBUG_LL_ENTRY(mach, OMAP1_UART##p##_BASE, OMAP_PORT_SHIFT,	\
		OMAP1UART##p)

अटल अंतरभूत व्योम arch_decomp_setup(व्योम)
अणु
	पूर्णांक port = 0;

	/*
	 * Initialize the port based on the machine ID from the bootloader.
	 * Note that we're using macros here instead of चयन statement
	 * as machine_is functions are optimized out क्रम the boards that
	 * are not selected.
	 */
	करो अणु
		/* omap7xx/8xx based boards using UART1 with shअगरt 0 */
		DEBUG_LL_OMAP7XX(1, herald);
		DEBUG_LL_OMAP7XX(1, omap_perseus2);

		/* omap15xx/16xx based boards using UART1 */
		DEBUG_LL_OMAP1(1, ams_delta);
		DEBUG_LL_OMAP1(1, nokia770);
		DEBUG_LL_OMAP1(1, omap_h2);
		DEBUG_LL_OMAP1(1, omap_h3);
		DEBUG_LL_OMAP1(1, omap_innovator);
		DEBUG_LL_OMAP1(1, omap_osk);
		DEBUG_LL_OMAP1(1, omap_palmte);
		DEBUG_LL_OMAP1(1, omap_palmz71);

		/* omap15xx/16xx based boards using UART2 */
		DEBUG_LL_OMAP1(2, omap_palmtt);

		/* omap15xx/16xx based boards using UART3 */
		DEBUG_LL_OMAP1(3, sx1);
	पूर्ण जबतक (0);
पूर्ण
