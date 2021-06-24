<शैली गुरु>
/*
 * DaVinci serial device definitions
 *
 * Author: Kevin Hilman, MontaVista Software, Inc. <source@mvista.com>
 *
 * 2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#अगर_अघोषित __ASM_ARCH_SERIAL_H
#घोषणा __ASM_ARCH_SERIAL_H

#समावेश <यंत्र/memory.h>

#समावेश <mach/hardware.h>

#घोषणा DAVINCI_UART0_BASE	(IO_PHYS + 0x20000)
#घोषणा DAVINCI_UART1_BASE	(IO_PHYS + 0x20400)
#घोषणा DAVINCI_UART2_BASE	(IO_PHYS + 0x20800)

#घोषणा DA8XX_UART0_BASE	(IO_PHYS + 0x042000)
#घोषणा DA8XX_UART1_BASE	(IO_PHYS + 0x10c000)
#घोषणा DA8XX_UART2_BASE	(IO_PHYS + 0x10d000)

/* DaVinci UART रेजिस्टर offsets */
#घोषणा UART_DAVINCI_PWREMU		0x0c
#घोषणा UART_DM646X_SCR			0x10
#घोषणा UART_DM646X_SCR_TX_WATERMARK	0x08

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/platक्रमm_device.h>

बाह्य पूर्णांक davinci_serial_init(काष्ठा platक्रमm_device *);
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_ARCH_SERIAL_H */
