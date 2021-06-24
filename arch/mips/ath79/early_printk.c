<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Atheros AR7XXX/AR9XXX SoC early prपूर्णांकk support
 *
 *  Copyright (C) 2008-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 */

#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/serial_reg.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/setup.h>

#समावेश <यंत्र/mach-ath79/ath79.h>
#समावेश <यंत्र/mach-ath79/ar71xx_regs.h>
#समावेश <यंत्र/mach-ath79/ar933x_uart.h>

अटल व्योम (*_prom_अक्षर_दो)(अक्षर);

अटल अंतरभूत व्योम prom_अक्षर_दो_रुको(व्योम __iomem *reg, u32 mask, u32 val)
अणु
	u32 t;

	करो अणु
		t = __raw_पढ़ोl(reg);
		अगर ((t & mask) == val)
			अवरोध;
	पूर्ण जबतक (1);
पूर्ण

#घोषणा BOTH_EMPTY (UART_LSR_TEMT | UART_LSR_THRE)

अटल व्योम prom_अक्षर_दो_ar71xx(अक्षर ch)
अणु
	व्योम __iomem *base = (व्योम __iomem *)(KSEG1ADDR(AR71XX_UART_BASE));

	prom_अक्षर_दो_रुको(base + UART_LSR * 4, BOTH_EMPTY, BOTH_EMPTY);
	__raw_ग_लिखोl((अचिन्हित अक्षर)ch, base + UART_TX * 4);
	prom_अक्षर_दो_रुको(base + UART_LSR * 4, BOTH_EMPTY, BOTH_EMPTY);
पूर्ण

अटल व्योम prom_अक्षर_दो_ar933x(अक्षर ch)
अणु
	व्योम __iomem *base = (व्योम __iomem *)(KSEG1ADDR(AR933X_UART_BASE));

	prom_अक्षर_दो_रुको(base + AR933X_UART_DATA_REG, AR933X_UART_DATA_TX_CSR,
			  AR933X_UART_DATA_TX_CSR);
	__raw_ग_लिखोl(AR933X_UART_DATA_TX_CSR | (अचिन्हित अक्षर)ch,
		     base + AR933X_UART_DATA_REG);
	prom_अक्षर_दो_रुको(base + AR933X_UART_DATA_REG, AR933X_UART_DATA_TX_CSR,
			  AR933X_UART_DATA_TX_CSR);
पूर्ण

अटल व्योम prom_अक्षर_दो_dummy(अक्षर ch)
अणु
	/* nothing to करो */
पूर्ण

अटल व्योम prom_enable_uart(u32 id)
अणु
	व्योम __iomem *gpio_base;
	u32 uart_en;
	u32 t;

	चयन (id) अणु
	हाल REV_ID_MAJOR_AR71XX:
		uart_en = AR71XX_GPIO_FUNC_UART_EN;
		अवरोध;

	हाल REV_ID_MAJOR_AR7240:
	हाल REV_ID_MAJOR_AR7241:
	हाल REV_ID_MAJOR_AR7242:
		uart_en = AR724X_GPIO_FUNC_UART_EN;
		अवरोध;

	हाल REV_ID_MAJOR_AR913X:
		uart_en = AR913X_GPIO_FUNC_UART_EN;
		अवरोध;

	हाल REV_ID_MAJOR_AR9330:
	हाल REV_ID_MAJOR_AR9331:
		uart_en = AR933X_GPIO_FUNC_UART_EN;
		अवरोध;

	हाल REV_ID_MAJOR_AR9341:
	हाल REV_ID_MAJOR_AR9342:
	हाल REV_ID_MAJOR_AR9344:
		/* TODO */
	शेष:
		वापस;
	पूर्ण

	gpio_base = (व्योम __iomem *)KSEG1ADDR(AR71XX_GPIO_BASE);
	t = __raw_पढ़ोl(gpio_base + AR71XX_GPIO_REG_FUNC);
	t |= uart_en;
	__raw_ग_लिखोl(t, gpio_base + AR71XX_GPIO_REG_FUNC);
पूर्ण

अटल व्योम prom_अक्षर_दो_init(व्योम)
अणु
	व्योम __iomem *base;
	u32 id;

	base = (व्योम __iomem *)(KSEG1ADDR(AR71XX_RESET_BASE));
	id = __raw_पढ़ोl(base + AR71XX_RESET_REG_REV_ID);
	id &= REV_ID_MAJOR_MASK;

	चयन (id) अणु
	हाल REV_ID_MAJOR_AR71XX:
	हाल REV_ID_MAJOR_AR7240:
	हाल REV_ID_MAJOR_AR7241:
	हाल REV_ID_MAJOR_AR7242:
	हाल REV_ID_MAJOR_AR913X:
	हाल REV_ID_MAJOR_AR9341:
	हाल REV_ID_MAJOR_AR9342:
	हाल REV_ID_MAJOR_AR9344:
	हाल REV_ID_MAJOR_QCA9533:
	हाल REV_ID_MAJOR_QCA9533_V2:
	हाल REV_ID_MAJOR_QCA9556:
	हाल REV_ID_MAJOR_QCA9558:
	हाल REV_ID_MAJOR_TP9343:
	हाल REV_ID_MAJOR_QCA956X:
		_prom_अक्षर_दो = prom_अक्षर_दो_ar71xx;
		अवरोध;

	हाल REV_ID_MAJOR_AR9330:
	हाल REV_ID_MAJOR_AR9331:
		_prom_अक्षर_दो = prom_अक्षर_दो_ar933x;
		अवरोध;

	शेष:
		_prom_अक्षर_दो = prom_अक्षर_दो_dummy;
		वापस;
	पूर्ण

	prom_enable_uart(id);
पूर्ण

व्योम prom_अक्षर_दो(अक्षर ch)
अणु
	अगर (!_prom_अक्षर_दो)
		prom_अक्षर_दो_init();

	_prom_अक्षर_दो(ch);
पूर्ण
