<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2011-2012 Gabor Juhos <juhosg@खोलोwrt.org>
 */

#समावेश <linux/पन.स>
#समावेश <linux/serial_reg.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/setup.h>

#अगर_घोषित CONFIG_SOC_RT288X
#घोषणा EARLY_UART_BASE		0x300c00
#घोषणा CHIPID_BASE		0x300004
#या_अगर defined(CONFIG_SOC_MT7621)
#घोषणा EARLY_UART_BASE		0x1E000c00
#घोषणा CHIPID_BASE		0x1E000004
#अन्यथा
#घोषणा EARLY_UART_BASE		0x10000c00
#घोषणा CHIPID_BASE		0x10000004
#पूर्ण_अगर

#घोषणा MT7628_CHIP_NAME1	0x20203832

#घोषणा UART_REG_TX		0x04
#घोषणा UART_REG_LCR		0x0c
#घोषणा UART_REG_LSR		0x14
#घोषणा UART_REG_LSR_RT2880	0x1c

अटल __iomem व्योम *uart_membase = (__iomem व्योम *) KSEG1ADDR(EARLY_UART_BASE);
अटल __iomem व्योम *chipid_membase = (__iomem व्योम *) KSEG1ADDR(CHIPID_BASE);
अटल पूर्णांक init_complete;

अटल अंतरभूत व्योम uart_w32(u32 val, अचिन्हित reg)
अणु
	__raw_ग_लिखोl(val, uart_membase + reg);
पूर्ण

अटल अंतरभूत u32 uart_r32(अचिन्हित reg)
अणु
	वापस __raw_पढ़ोl(uart_membase + reg);
पूर्ण

अटल अंतरभूत पूर्णांक soc_is_mt7628(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_SOC_MT7620) &&
		(__raw_पढ़ोl(chipid_membase) == MT7628_CHIP_NAME1);
पूर्ण

अटल व्योम find_uart_base(व्योम)
अणु
	पूर्णांक i;

	अगर (!soc_is_mt7628())
		वापस;

	क्रम (i = 0; i < 3; i++) अणु
		u32 reg = uart_r32(UART_REG_LCR + (0x100 * i));

		अगर (!reg)
			जारी;

		uart_membase = (__iomem व्योम *) KSEG1ADDR(EARLY_UART_BASE +
							  (0x100 * i));
		अवरोध;
	पूर्ण
पूर्ण

व्योम prom_अक्षर_दो(अक्षर ch)
अणु
	अगर (!init_complete) अणु
		find_uart_base();
		init_complete = 1;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_SOC_MT7621) || soc_is_mt7628()) अणु
		uart_w32((अचिन्हित अक्षर)ch, UART_TX);
		जबतक ((uart_r32(UART_REG_LSR) & UART_LSR_THRE) == 0)
			;
	पूर्ण अन्यथा अणु
		जबतक ((uart_r32(UART_REG_LSR_RT2880) & UART_LSR_THRE) == 0)
			;
		uart_w32((अचिन्हित अक्षर)ch, UART_REG_TX);
		जबतक ((uart_r32(UART_REG_LSR_RT2880) & UART_LSR_THRE) == 0)
			;
	पूर्ण
पूर्ण
