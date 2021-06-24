<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *  m520x.c  -- platक्रमm support क्रम ColdFire 520x based boards
 *
 *  Copyright (C) 2005,      Freescale (www.मुक्तscale.com)
 *  Copyright (C) 2005,      Intec Automation (mike@steroidmicros.com)
 *  Copyright (C) 1999-2007, Greg Ungerer (gerg@snapgear.com)
 *  Copyright (C) 2001-2003, SnapGear Inc. (www.snapgear.com)
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfuart.h>
#समावेश <यंत्र/mcfclk.h>

/***************************************************************************/

DEFINE_CLK(0, "flexbus", 2, MCF_CLK);
DEFINE_CLK(0, "fec.0", 12, MCF_CLK);
DEFINE_CLK(0, "edma", 17, MCF_CLK);
DEFINE_CLK(0, "intc.0", 18, MCF_CLK);
DEFINE_CLK(0, "iack.0", 21, MCF_CLK);
DEFINE_CLK(0, "imx1-i2c.0", 22, MCF_CLK);
DEFINE_CLK(0, "mcfqspi.0", 23, MCF_CLK);
DEFINE_CLK(0, "mcfuart.0", 24, MCF_BUSCLK);
DEFINE_CLK(0, "mcfuart.1", 25, MCF_BUSCLK);
DEFINE_CLK(0, "mcfuart.2", 26, MCF_BUSCLK);
DEFINE_CLK(0, "mcftmr.0", 28, MCF_CLK);
DEFINE_CLK(0, "mcftmr.1", 29, MCF_CLK);
DEFINE_CLK(0, "mcftmr.2", 30, MCF_CLK);
DEFINE_CLK(0, "mcftmr.3", 31, MCF_CLK);

DEFINE_CLK(0, "mcfpit.0", 32, MCF_CLK);
DEFINE_CLK(0, "mcfpit.1", 33, MCF_CLK);
DEFINE_CLK(0, "mcfeport.0", 34, MCF_CLK);
DEFINE_CLK(0, "mcfwdt.0", 35, MCF_CLK);
DEFINE_CLK(0, "pll.0", 36, MCF_CLK);
DEFINE_CLK(0, "sys.0", 40, MCF_BUSCLK);
DEFINE_CLK(0, "gpio.0", 41, MCF_BUSCLK);
DEFINE_CLK(0, "sdram.0", 42, MCF_CLK);

काष्ठा clk *mcf_clks[] = अणु
	&__clk_0_2, /* flexbus */
	&__clk_0_12, /* fec.0 */
	&__clk_0_17, /* edma */
	&__clk_0_18, /* पूर्णांकc.0 */
	&__clk_0_21, /* iack.0 */
	&__clk_0_22, /* imx1-i2c.0 */
	&__clk_0_23, /* mcfqspi.0 */
	&__clk_0_24, /* mcfuart.0 */
	&__clk_0_25, /* mcfuart.1 */
	&__clk_0_26, /* mcfuart.2 */
	&__clk_0_28, /* mcfपंचांगr.0 */
	&__clk_0_29, /* mcfपंचांगr.1 */
	&__clk_0_30, /* mcfपंचांगr.2 */
	&__clk_0_31, /* mcfपंचांगr.3 */

	&__clk_0_32, /* mcfpit.0 */
	&__clk_0_33, /* mcfpit.1 */
	&__clk_0_34, /* mcfeport.0 */
	&__clk_0_35, /* mcfwdt.0 */
	&__clk_0_36, /* pll.0 */
	&__clk_0_40, /* sys.0 */
	&__clk_0_41, /* gpio.0 */
	&__clk_0_42, /* sdram.0 */
	शून्य,
पूर्ण;

अटल काष्ठा clk * स्थिर enable_clks[] __initस्थिर = अणु
	&__clk_0_2, /* flexbus */
	&__clk_0_18, /* पूर्णांकc.0 */
	&__clk_0_21, /* iack.0 */
	&__clk_0_24, /* mcfuart.0 */
	&__clk_0_25, /* mcfuart.1 */
	&__clk_0_26, /* mcfuart.2 */

	&__clk_0_32, /* mcfpit.0 */
	&__clk_0_33, /* mcfpit.1 */
	&__clk_0_34, /* mcfeport.0 */
	&__clk_0_36, /* pll.0 */
	&__clk_0_40, /* sys.0 */
	&__clk_0_41, /* gpio.0 */
	&__clk_0_42, /* sdram.0 */
पूर्ण;

अटल काष्ठा clk * स्थिर disable_clks[] __initस्थिर = अणु
	&__clk_0_12, /* fec.0 */
	&__clk_0_17, /* edma */
	&__clk_0_22, /* imx1-i2c.0 */
	&__clk_0_23, /* mcfqspi.0 */
	&__clk_0_28, /* mcfपंचांगr.0 */
	&__clk_0_29, /* mcfपंचांगr.1 */
	&__clk_0_30, /* mcfपंचांगr.2 */
	&__clk_0_31, /* mcfपंचांगr.3 */
	&__clk_0_35, /* mcfwdt.0 */
पूर्ण;


अटल व्योम __init m520x_clk_init(व्योम)
अणु
	अचिन्हित i;

	/* make sure these घड़ीs are enabled */
	क्रम (i = 0; i < ARRAY_SIZE(enable_clks); ++i)
		__clk_init_enabled(enable_clks[i]);
	/* make sure these घड़ीs are disabled */
	क्रम (i = 0; i < ARRAY_SIZE(disable_clks); ++i)
		__clk_init_disabled(disable_clks[i]);
पूर्ण

/***************************************************************************/

अटल व्योम __init m520x_qspi_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI)
	u16 par;
	/* setup Port QS क्रम QSPI with gpio CS control */
	ग_लिखोb(0x3f, MCF_GPIO_PAR_QSPI);
	/* make U1CTS and U2RTS gpio क्रम cs_control */
	par = पढ़ोw(MCF_GPIO_PAR_UART);
	par &= 0x00ff;
	ग_लिखोw(par, MCF_GPIO_PAR_UART);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI) */
पूर्ण

/***************************************************************************/

अटल व्योम __init m520x_i2c_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C_IMX)
	u8 par;

	/* setup Port FECI2C Pin Assignment Register क्रम I2C */
	/*  set PAR_SCL to SCL and PAR_SDA to SDA */
	par = पढ़ोb(MCF_GPIO_PAR_FECI2C);
	par |= 0x0f;
	ग_लिखोb(par, MCF_GPIO_PAR_FECI2C);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_I2C_IMX) */
पूर्ण

/***************************************************************************/

अटल व्योम __init m520x_uarts_init(व्योम)
अणु
	u16 par;
	u8 par2;

	/* UART0 and UART1 GPIO pin setup */
	par = पढ़ोw(MCF_GPIO_PAR_UART);
	par |= MCF_GPIO_PAR_UART_PAR_UTXD0 | MCF_GPIO_PAR_UART_PAR_URXD0;
	par |= MCF_GPIO_PAR_UART_PAR_UTXD1 | MCF_GPIO_PAR_UART_PAR_URXD1;
	ग_लिखोw(par, MCF_GPIO_PAR_UART);

	/* UART1 GPIO pin setup */
	par2 = पढ़ोb(MCF_GPIO_PAR_FECI2C);
	par2 &= ~0x0F;
	par2 |= MCF_GPIO_PAR_FECI2C_PAR_SCL_UTXD2 |
		MCF_GPIO_PAR_FECI2C_PAR_SDA_URXD2;
	ग_लिखोb(par2, MCF_GPIO_PAR_FECI2C);
पूर्ण

/***************************************************************************/

अटल व्योम __init m520x_fec_init(व्योम)
अणु
	u8 v;

	/* Set multi-function pins to ethernet mode */
	v = पढ़ोb(MCF_GPIO_PAR_FEC);
	ग_लिखोb(v | 0xf0, MCF_GPIO_PAR_FEC);

	v = पढ़ोb(MCF_GPIO_PAR_FECI2C);
	ग_लिखोb(v | 0x0f, MCF_GPIO_PAR_FECI2C);
पूर्ण

/***************************************************************************/

व्योम __init config_BSP(अक्षर *commandp, पूर्णांक size)
अणु
	mach_sched_init = hw_समयr_init;
	m520x_clk_init();
	m520x_uarts_init();
	m520x_fec_init();
	m520x_qspi_init();
	m520x_i2c_init();
पूर्ण

/***************************************************************************/
