<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	m5206.c  -- platक्रमm support क्रम ColdFire 5206 based boards
 *
 *	Copyright (C) 1999-2002, Greg Ungerer (gerg@snapgear.com)
 * 	Copyright (C) 2000-2001, Lineo Inc. (www.lineo.com) 
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
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
DEFINE_CLK(mcfi2c0, "imx1-i2c.0", MCF_BUSCLK);

काष्ठा clk *mcf_clks[] = अणु
	&clk_pll,
	&clk_sys,
	&clk_mcfपंचांगr0,
	&clk_mcfपंचांगr1,
	&clk_mcfuart0,
	&clk_mcfuart1,
	&clk_mcfi2c0,
	शून्य
पूर्ण;

/***************************************************************************/

अटल व्योम __init m5206_i2c_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C_IMX)
	ग_लिखोb(MCFSIM_ICR_AUTOVEC | MCFSIM_ICR_LEVEL5 | MCFSIM_ICR_PRI0,
	       MCFSIM_I2CICR);
	mcf_mapirq2imr(MCF_IRQ_I2C0, MCFINTC_I2C);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_I2C_IMX) */
पूर्ण

व्योम __init config_BSP(अक्षर *commandp, पूर्णांक size)
अणु
#अगर defined(CONFIG_NETtel)
	/* Copy command line from FLASH to local buffer... */
	स_नकल(commandp, (अक्षर *) 0xf0004000, size);
	commandp[size-1] = 0;
#पूर्ण_अगर /* CONFIG_NETtel */

	mach_sched_init = hw_समयr_init;

	/* Only support the बाह्यal पूर्णांकerrupts on their primary level */
	mcf_mapirq2imr(25, MCFINTC_EINT1);
	mcf_mapirq2imr(28, MCFINTC_EINT4);
	mcf_mapirq2imr(31, MCFINTC_EINT7);
	m5206_i2c_init();
पूर्ण

/***************************************************************************/
