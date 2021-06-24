<शैली गुरु>
/*
 * Copyright (C) 2009 Texas Instruments
 * Added OMAP4 support- Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित __ASM_ARCH_SERIAL_H
#घोषणा __ASM_ARCH_SERIAL_H

#समावेश <linux/init.h>

/*
 * Memory entry used क्रम the DEBUG_LL UART configuration, relative to
 * start of RAM. See also uncompress.h and debug-macro.S.
 *
 * Note that using a memory location क्रम storing the UART configuration
 * has at least two limitations:
 *
 * 1. Kernel uncompress code cannot overlap OMAP_UART_INFO as the
 *    uncompress code could then partially overग_लिखो itself
 * 2. We assume prपूर्णांकascii is called at least once beक्रमe paging_init,
 *    and addruart has a chance to पढ़ो OMAP_UART_INFO
 */
#घोषणा OMAP_UART_INFO_OFS	0x3ffc

#घोषणा OMAP_PORT_SHIFT		2
#घोषणा OMAP7XX_PORT_SHIFT	0

#घोषणा OMAP1510_BASE_BAUD	(12000000/16)
#घोषणा OMAP16XX_BASE_BAUD	(48000000/16)

/*
 * DEBUG_LL port encoding stored पूर्णांकo the UART1 scratchpad रेजिस्टर by
 * decomp_setup in uncompress.h
 */
#घोषणा OMAP1UART1		11
#घोषणा OMAP1UART2		12
#घोषणा OMAP1UART3		13

#अगर_अघोषित __ASSEMBLER__
बाह्य व्योम omap_serial_init(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर
