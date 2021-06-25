<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-lpc32xx/serial.c
 *
 * Author: Kevin Wells <kevin.wells@nxp.com>
 *
 * Copyright (C) 2010 NXP Semiconductors
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश "lpc32xx.h"
#समावेश "common.h"

#घोषणा LPC32XX_SUART_FIFO_SIZE	64

काष्ठा uartinit अणु
	अक्षर *uart_ck_name;
	u32 ck_mode_mask;
	व्योम __iomem *pभाग_clk_reg;
	resource_माप_प्रकार mapbase;
पूर्ण;

अटल काष्ठा uartinit uartinit_data[] __initdata = अणु
	अणु
		.uart_ck_name = "uart5_ck",
		.ck_mode_mask =
			LPC32XX_UART_CLKMODE_LOAD(LPC32XX_UART_CLKMODE_ON, 5),
		.pभाग_clk_reg = LPC32XX_CLKPWR_UART5_CLK_CTRL,
		.mapbase = LPC32XX_UART5_BASE,
	पूर्ण,
	अणु
		.uart_ck_name = "uart3_ck",
		.ck_mode_mask =
			LPC32XX_UART_CLKMODE_LOAD(LPC32XX_UART_CLKMODE_ON, 3),
		.pभाग_clk_reg = LPC32XX_CLKPWR_UART3_CLK_CTRL,
		.mapbase = LPC32XX_UART3_BASE,
	पूर्ण,
	अणु
		.uart_ck_name = "uart4_ck",
		.ck_mode_mask =
			LPC32XX_UART_CLKMODE_LOAD(LPC32XX_UART_CLKMODE_ON, 4),
		.pभाग_clk_reg = LPC32XX_CLKPWR_UART4_CLK_CTRL,
		.mapbase = LPC32XX_UART4_BASE,
	पूर्ण,
	अणु
		.uart_ck_name = "uart6_ck",
		.ck_mode_mask =
			LPC32XX_UART_CLKMODE_LOAD(LPC32XX_UART_CLKMODE_ON, 6),
		.pभाग_clk_reg = LPC32XX_CLKPWR_UART6_CLK_CTRL,
		.mapbase = LPC32XX_UART6_BASE,
	पूर्ण,
पूर्ण;

/* LPC3250 Errata HSUART.1: Hang workaround via loopback mode on inactivity */
व्योम lpc32xx_loopback_set(resource_माप_प्रकार mapbase, पूर्णांक state)
अणु
	पूर्णांक bit;
	u32 पंचांगp;

	चयन (mapbase) अणु
	हाल LPC32XX_HS_UART1_BASE:
		bit = 0;
		अवरोध;
	हाल LPC32XX_HS_UART2_BASE:
		bit = 1;
		अवरोध;
	हाल LPC32XX_HS_UART7_BASE:
		bit = 6;
		अवरोध;
	शेष:
		WARN(1, "lpc32xx_hs: Warning: Unknown port at %08x\n", mapbase);
		वापस;
	पूर्ण

	पंचांगp = पढ़ोl(LPC32XX_UARTCTL_CLOOP);
	अगर (state)
		पंचांगp |= (1 << bit);
	अन्यथा
		पंचांगp &= ~(1 << bit);
	ग_लिखोl(पंचांगp, LPC32XX_UARTCTL_CLOOP);
पूर्ण
EXPORT_SYMBOL_GPL(lpc32xx_loopback_set);

व्योम __init lpc32xx_serial_init(व्योम)
अणु
	u32 पंचांगp, clkmodes = 0;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक puart;
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(uartinit_data); i++) अणु
		clk = clk_get(शून्य, uartinit_data[i].uart_ck_name);
		अगर (!IS_ERR(clk)) अणु
			clk_enable(clk);
		पूर्ण

		/* Setup UART घड़ी modes क्रम all UARTs, disable स्वतःघड़ी */
		clkmodes |= uartinit_data[i].ck_mode_mask;

		/* pre-UART घड़ी भागider set to 1 */
		__raw_ग_लिखोl(0x0101, uartinit_data[i].pभाग_clk_reg);

		/*
		 * Force a flush of the RX FIFOs to work around a
		 * HW bug
		 */
		puart = uartinit_data[i].mapbase;
		__raw_ग_लिखोl(0xC1, LPC32XX_UART_IIR_FCR(puart));
		__raw_ग_लिखोl(0x00, LPC32XX_UART_DLL_FIFO(puart));
		j = LPC32XX_SUART_FIFO_SIZE;
		जबतक (j--)
			पंचांगp = __raw_पढ़ोl(
				LPC32XX_UART_DLL_FIFO(puart));
		__raw_ग_लिखोl(0, LPC32XX_UART_IIR_FCR(puart));
	पूर्ण

	/* This needs to be करोne after all UART घड़ीs are setup */
	__raw_ग_लिखोl(clkmodes, LPC32XX_UARTCTL_CLKMODE);
	क्रम (i = 0; i < ARRAY_SIZE(uartinit_data); i++) अणु
		/* Force a flush of the RX FIFOs to work around a HW bug */
		puart = uartinit_data[i].mapbase;
		__raw_ग_लिखोl(0xC1, LPC32XX_UART_IIR_FCR(puart));
		__raw_ग_लिखोl(0x00, LPC32XX_UART_DLL_FIFO(puart));
		j = LPC32XX_SUART_FIFO_SIZE;
		जबतक (j--)
			पंचांगp = __raw_पढ़ोl(LPC32XX_UART_DLL_FIFO(puart));
		__raw_ग_लिखोl(0, LPC32XX_UART_IIR_FCR(puart));
	पूर्ण

	/* Disable IrDA pulsing support on UART6 */
	पंचांगp = __raw_पढ़ोl(LPC32XX_UARTCTL_CTRL);
	पंचांगp |= LPC32XX_UART_UART6_IRDAMOD_BYPASS;
	__raw_ग_लिखोl(पंचांगp, LPC32XX_UARTCTL_CTRL);

	/* Disable UART5->USB transparent mode or USB won't work */
	पंचांगp = __raw_पढ़ोl(LPC32XX_UARTCTL_CTRL);
	पंचांगp &= ~LPC32XX_UART_U5_ROUTE_TO_USB;
	__raw_ग_लिखोl(पंचांगp, LPC32XX_UARTCTL_CTRL);
पूर्ण
