<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	525x.c  -- platक्रमm support क्रम ColdFire 525x based boards
 *
 *	Copyright (C) 2012, Steven King <sfking@fdwdc.com>
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfclk.h>

/***************************************************************************/

DEFINE_CLK(pll, "pll.0", MCF_CLK);
DEFINE_CLK(sys, "sys.0", MCF_BUSCLK);
DEFINE_CLK(mcfपंचांगr0, "mcftmr.0", MCF_BUSCLK);
DEFINE_CLK(mcfपंचांगr1, "mcftmr.1", MCF_BUSCLK);
DEFINE_CLK(mcfuart0, "mcfuart.0", MCF_BUSCLK);
DEFINE_CLK(mcfuart1, "mcfuart.1", MCF_BUSCLK);
DEFINE_CLK(mcfqspi0, "mcfqspi.0", MCF_BUSCLK);
DEFINE_CLK(mcfi2c0, "imx1-i2c.0", MCF_BUSCLK);
DEFINE_CLK(mcfi2c1, "imx1-i2c.1", MCF_BUSCLK);

काष्ठा clk *mcf_clks[] = अणु
	&clk_pll,
	&clk_sys,
	&clk_mcfपंचांगr0,
	&clk_mcfपंचांगr1,
	&clk_mcfuart0,
	&clk_mcfuart1,
	&clk_mcfqspi0,
	&clk_mcfi2c0,
	&clk_mcfi2c1,
	शून्य
पूर्ण;

/***************************************************************************/

अटल व्योम __init m525x_qspi_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI)
	/* set the GPIO function क्रम the qspi cs gpios */
	/* FIXME: replace with pinmux/pinctl support */
	u32 f = पढ़ोl(MCFSIM2_GPIOFUNC);
	f |= (1 << MCFQSPI_CS2) | (1 << MCFQSPI_CS1) | (1 << MCFQSPI_CS0);
	ग_लिखोl(f, MCFSIM2_GPIOFUNC);

	/* QSPI irq setup */
	ग_लिखोb(MCFSIM_ICR_AUTOVEC | MCFSIM_ICR_LEVEL4 | MCFSIM_ICR_PRI0,
	       MCFSIM_QSPIICR);
	mcf_mapirq2imr(MCF_IRQ_QSPI, MCFINTC_QSPI);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI) */
पूर्ण

अटल व्योम __init m525x_i2c_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C_IMX)
	u32 r;

	/* first I2C controller uses regular irq setup */
	ग_लिखोb(MCFSIM_ICR_AUTOVEC | MCFSIM_ICR_LEVEL5 | MCFSIM_ICR_PRI0,
	       MCFSIM_I2CICR);
	mcf_mapirq2imr(MCF_IRQ_I2C0, MCFINTC_I2C);

	/* second I2C controller is completely dअगरferent */
	r = पढ़ोl(MCFINTC2_INTPRI_REG(MCF_IRQ_I2C1));
	r &= ~MCFINTC2_INTPRI_BITS(0xf, MCF_IRQ_I2C1);
	r |= MCFINTC2_INTPRI_BITS(0x5, MCF_IRQ_I2C1);
	ग_लिखोl(r, MCFINTC2_INTPRI_REG(MCF_IRQ_I2C1));
#पूर्ण_अगर /* IS_ENABLED(CONFIG_I2C_IMX) */
पूर्ण

/***************************************************************************/

व्योम __init config_BSP(अक्षर *commandp, पूर्णांक size)
अणु
	mach_sched_init = hw_समयr_init;

	m525x_qspi_init();
	m525x_i2c_init();
पूर्ण

/***************************************************************************/
