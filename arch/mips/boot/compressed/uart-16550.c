<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * 16550 compatible uart based serial debug support क्रम zboot
 */

#समावेश <linux/types.h>
#समावेश <linux/serial_reg.h>

#समावेश <यंत्र/addrspace.h>

#अगर defined(CONFIG_MACH_LOONGSON64) || defined(CONFIG_MIPS_MALTA)
#घोषणा UART_BASE 0x1fd003f8
#घोषणा PORT(offset) (CKSEG1ADDR(UART_BASE) + (offset))
#पूर्ण_अगर

#अगर_घोषित CONFIG_AR7
#समावेश <ar7.h>
#घोषणा PORT(offset) (CKSEG1ADDR(AR7_REGS_UART0) + (4 * offset))
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_INGENIC
#घोषणा INGENIC_UART0_BASE_ADDR	0x10030000
#घोषणा PORT(offset) (CKSEG1ADDR(INGENIC_UART0_BASE_ADDR) + (4 * offset))
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_XLR
#घोषणा UART0_BASE  0x1EF14000
#घोषणा PORT(offset) (CKSEG1ADDR(UART0_BASE) + (4 * offset))
#घोषणा IOTYPE अचिन्हित पूर्णांक
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_XLP
#घोषणा UART0_BASE  0x18030100
#घोषणा PORT(offset) (CKSEG1ADDR(UART0_BASE) + (4 * offset))
#घोषणा IOTYPE अचिन्हित पूर्णांक
#पूर्ण_अगर

#अगर_अघोषित IOTYPE
#घोषणा IOTYPE अक्षर
#पूर्ण_अगर

#अगर_अघोषित PORT
#त्रुटि please define the serial port address क्रम your own machine
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक serial_in(पूर्णांक offset)
अणु
	वापस *((अस्थिर IOTYPE *)PORT(offset)) & 0xFF;
पूर्ण

अटल अंतरभूत व्योम serial_out(पूर्णांक offset, पूर्णांक value)
अणु
	*((अस्थिर IOTYPE *)PORT(offset)) = value & 0xFF;
पूर्ण

व्योम अ_दो(अक्षर c)
अणु
	पूर्णांक समयout = 1000000;

	जबतक (((serial_in(UART_LSR) & UART_LSR_THRE) == 0) && (समयout-- > 0))
		;

	serial_out(UART_TX, c);
पूर्ण
