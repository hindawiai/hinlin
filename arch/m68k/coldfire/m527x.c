<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	m527x.c  -- platक्रमm support क्रम ColdFire 527x based boards
 *
 *	Sub-architcture dependent initialization code क्रम the Freescale
 *	5270/5271 and 5274/5275 CPUs.
 *
 *	Copyright (C) 1999-2004, Greg Ungerer (gerg@snapgear.com)
 *	Copyright (C) 2001-2004, SnapGear Inc. (www.snapgear.com)
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

DEFINE_CLK(pll, "pll.0", MCF_CLK);
DEFINE_CLK(sys, "sys.0", MCF_BUSCLK);
DEFINE_CLK(mcfpit0, "mcfpit.0", MCF_CLK);
DEFINE_CLK(mcfpit1, "mcfpit.1", MCF_CLK);
DEFINE_CLK(mcfpit2, "mcfpit.2", MCF_CLK);
DEFINE_CLK(mcfpit3, "mcfpit.3", MCF_CLK);
DEFINE_CLK(mcfuart0, "mcfuart.0", MCF_BUSCLK);
DEFINE_CLK(mcfuart1, "mcfuart.1", MCF_BUSCLK);
DEFINE_CLK(mcfuart2, "mcfuart.2", MCF_BUSCLK);
DEFINE_CLK(mcfqspi0, "mcfqspi.0", MCF_BUSCLK);
DEFINE_CLK(fec0, "fec.0", MCF_BUSCLK);
DEFINE_CLK(fec1, "fec.1", MCF_BUSCLK);
DEFINE_CLK(mcfi2c0, "imx1-i2c.0", MCF_BUSCLK);

काष्ठा clk *mcf_clks[] = अणु
	&clk_pll,
	&clk_sys,
	&clk_mcfpit0,
	&clk_mcfpit1,
	&clk_mcfpit2,
	&clk_mcfpit3,
	&clk_mcfuart0,
	&clk_mcfuart1,
	&clk_mcfuart2,
	&clk_mcfqspi0,
	&clk_fec0,
	&clk_fec1,
	&clk_mcfi2c0,
	शून्य
पूर्ण;

/***************************************************************************/

अटल व्योम __init m527x_qspi_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI)
#अगर defined(CONFIG_M5271)
	u16 par;

	/* setup QSPS pins क्रम QSPI with gpio CS control */
	ग_लिखोb(0x1f, MCFGPIO_PAR_QSPI);
	/* and CS2 & CS3 as gpio */
	par = पढ़ोw(MCFGPIO_PAR_TIMER);
	par &= 0x3f3f;
	ग_लिखोw(par, MCFGPIO_PAR_TIMER);
#या_अगर defined(CONFIG_M5275)
	/* setup QSPS pins क्रम QSPI with gpio CS control */
	ग_लिखोw(0x003e, MCFGPIO_PAR_QSPI);
#पूर्ण_अगर
#पूर्ण_अगर /* IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI) */
पूर्ण

/***************************************************************************/

अटल व्योम __init m527x_i2c_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C_IMX)
#अगर defined(CONFIG_M5271)
	u8 par;

	/* setup Port FECI2C Pin Assignment Register क्रम I2C */
	/*  set PAR_SCL to SCL and PAR_SDA to SDA */
	par = पढ़ोb(MCFGPIO_PAR_FECI2C);
	par |= 0x0f;
	ग_लिखोb(par, MCFGPIO_PAR_FECI2C);
#या_अगर defined(CONFIG_M5275)
	u16 par;

	/* setup Port FECI2C Pin Assignment Register क्रम I2C */
	/*  set PAR_SCL to SCL and PAR_SDA to SDA */
	par = पढ़ोw(MCFGPIO_PAR_FECI2C);
	par |= 0x0f;
	ग_लिखोw(par, MCFGPIO_PAR_FECI2C);
#पूर्ण_अगर
#पूर्ण_अगर /* IS_ENABLED(CONFIG_I2C_IMX) */
पूर्ण

/***************************************************************************/

अटल व्योम __init m527x_uarts_init(व्योम)
अणु
	u16 sepmask;

	/*
	 * External Pin Mask Setting & Enable External Pin क्रम Interface
	 */
	sepmask = पढ़ोw(MCFGPIO_PAR_UART);
	sepmask |= UART0_ENABLE_MASK | UART1_ENABLE_MASK | UART2_ENABLE_MASK;
	ग_लिखोw(sepmask, MCFGPIO_PAR_UART);
पूर्ण

/***************************************************************************/

अटल व्योम __init m527x_fec_init(व्योम)
अणु
	u8 v;

	/* Set multi-function pins to ethernet mode क्रम fec0 */
#अगर defined(CONFIG_M5271)
	v = पढ़ोb(MCFGPIO_PAR_FECI2C);
	ग_लिखोb(v | 0xf0, MCFGPIO_PAR_FECI2C);
#अन्यथा
	u16 par;

	par = पढ़ोw(MCFGPIO_PAR_FECI2C);
	ग_लिखोw(par | 0xf00, MCFGPIO_PAR_FECI2C);
	v = पढ़ोb(MCFGPIO_PAR_FEC0HL);
	ग_लिखोb(v | 0xc0, MCFGPIO_PAR_FEC0HL);

	/* Set multi-function pins to ethernet mode क्रम fec1 */
	par = पढ़ोw(MCFGPIO_PAR_FECI2C);
	ग_लिखोw(par | 0xa0, MCFGPIO_PAR_FECI2C);
	v = पढ़ोb(MCFGPIO_PAR_FEC1HL);
	ग_लिखोb(v | 0xc0, MCFGPIO_PAR_FEC1HL);
#पूर्ण_अगर
पूर्ण

/***************************************************************************/

व्योम __init config_BSP(अक्षर *commandp, पूर्णांक size)
अणु
	mach_sched_init = hw_समयr_init;
	m527x_uarts_init();
	m527x_fec_init();
	m527x_qspi_init();
	m527x_i2c_init();
पूर्ण

/***************************************************************************/
