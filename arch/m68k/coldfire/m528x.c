<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	m528x.c  -- platक्रमm support क्रम ColdFire 528x based boards
 *
 *	Sub-architcture dependent initialization code क्रम the Freescale
 *	5280, 5281 and 5282 CPUs.
 *
 *	Copyright (C) 1999-2003, Greg Ungerer (gerg@snapgear.com)
 *	Copyright (C) 2001-2003, SnapGear Inc. (www.snapgear.com)
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
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
	&clk_mcfi2c0,
	शून्य
पूर्ण;

/***************************************************************************/

अटल व्योम __init m528x_qspi_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI)
	/* setup Port QS क्रम QSPI with gpio CS control */
	__raw_ग_लिखोb(0x07, MCFGPIO_PQSPAR);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI) */
पूर्ण

/***************************************************************************/

अटल व्योम __init m528x_i2c_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C_IMX)
	u16 paspar;

	/* setup Port AS Pin Assignment Register क्रम I2C */
	/*  set PASPA0 to SCL and PASPA1 to SDA */
	paspar = पढ़ोw(MCFGPIO_PASPAR);
	paspar |= 0xF;
	ग_लिखोw(paspar, MCFGPIO_PASPAR);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_I2C_IMX) */
पूर्ण

/***************************************************************************/

अटल व्योम __init m528x_uarts_init(व्योम)
अणु
	u8 port;

	/* make sure PUAPAR is set क्रम UART0 and UART1 */
	port = पढ़ोb(MCFGPIO_PUAPAR);
	port |= 0x03 | (0x03 << 2);
	ग_लिखोb(port, MCFGPIO_PUAPAR);
पूर्ण

/***************************************************************************/

अटल व्योम __init m528x_fec_init(व्योम)
अणु
	u16 v16;

	/* Set multi-function pins to ethernet mode क्रम fec0 */
	v16 = पढ़ोw(MCFGPIO_PASPAR);
	ग_लिखोw(v16 | 0xf00, MCFGPIO_PASPAR);
	ग_लिखोb(0xc0, MCFGPIO_PEHLPAR);
पूर्ण

/***************************************************************************/

#अगर_घोषित CONFIG_WILDFIRE
व्योम wildfire_halt(व्योम)
अणु
	ग_लिखोb(0, 0x30000007);
	ग_लिखोb(0x2, 0x30000007);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_WILDFIREMOD
व्योम wildfiremod_halt(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "WildFireMod hibernating...\n");

	/* Set portE.5 to Digital IO */
	ग_लिखोw(पढ़ोw(MCFGPIO_PEPAR) & ~(1 << (5 * 2)), MCFGPIO_PEPAR);

	/* Make portE.5 an output */
	ग_लिखोb(पढ़ोb(MCFGPIO_PDDR_E) | (1 << 5), MCFGPIO_PDDR_E);

	/* Now toggle portE.5 from low to high */
	ग_लिखोb(पढ़ोb(MCFGPIO_PODR_E) & ~(1 << 5), MCFGPIO_PODR_E);
	ग_लिखोb(पढ़ोb(MCFGPIO_PODR_E) | (1 << 5), MCFGPIO_PODR_E);

	prपूर्णांकk(KERN_EMERG "Failed to hibernate. Halting!\n");
पूर्ण
#पूर्ण_अगर

व्योम __init config_BSP(अक्षर *commandp, पूर्णांक size)
अणु
#अगर_घोषित CONFIG_WILDFIRE
	mach_halt = wildfire_halt;
#पूर्ण_अगर
#अगर_घोषित CONFIG_WILDFIREMOD
	mach_halt = wildfiremod_halt;
#पूर्ण_अगर
	mach_sched_init = hw_समयr_init;
	m528x_uarts_init();
	m528x_fec_init();
	m528x_qspi_init();
	m528x_i2c_init();
पूर्ण

/***************************************************************************/
