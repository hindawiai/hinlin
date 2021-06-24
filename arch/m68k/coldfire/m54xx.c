<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	m54xx.c  -- platक्रमm support क्रम ColdFire 54xx based boards
 *
 *	Copyright (C) 2010, Philippe De Muyter <phdm@macqel.be>
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/clk.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/m54xxsim.h>
#समावेश <यंत्र/mcfuart.h>
#समावेश <यंत्र/mcfclk.h>
#समावेश <यंत्र/m54xxgpt.h>
#अगर_घोषित CONFIG_MMU
#समावेश <यंत्र/mmu_context.h>
#पूर्ण_अगर

/***************************************************************************/

DEFINE_CLK(pll, "pll.0", MCF_CLK);
DEFINE_CLK(sys, "sys.0", MCF_BUSCLK);
DEFINE_CLK(mcfslt0, "mcfslt.0", MCF_BUSCLK);
DEFINE_CLK(mcfslt1, "mcfslt.1", MCF_BUSCLK);
DEFINE_CLK(mcfuart0, "mcfuart.0", MCF_BUSCLK);
DEFINE_CLK(mcfuart1, "mcfuart.1", MCF_BUSCLK);
DEFINE_CLK(mcfuart2, "mcfuart.2", MCF_BUSCLK);
DEFINE_CLK(mcfuart3, "mcfuart.3", MCF_BUSCLK);
DEFINE_CLK(mcfi2c0, "imx1-i2c.0", MCF_BUSCLK);

काष्ठा clk *mcf_clks[] = अणु
	&clk_pll,
	&clk_sys,
	&clk_mcfslt0,
	&clk_mcfslt1,
	&clk_mcfuart0,
	&clk_mcfuart1,
	&clk_mcfuart2,
	&clk_mcfuart3,
	&clk_mcfi2c0,
	शून्य
पूर्ण;

/***************************************************************************/

अटल व्योम __init m54xx_uarts_init(व्योम)
अणु
	/* enable io pins */
	__raw_ग_लिखोb(MCF_PAR_PSC_TXD | MCF_PAR_PSC_RXD, MCFGPIO_PAR_PSC0);
	__raw_ग_लिखोb(MCF_PAR_PSC_TXD | MCF_PAR_PSC_RXD | MCF_PAR_PSC_RTS_RTS,
		MCFGPIO_PAR_PSC1);
	__raw_ग_लिखोb(MCF_PAR_PSC_TXD | MCF_PAR_PSC_RXD | MCF_PAR_PSC_RTS_RTS |
		MCF_PAR_PSC_CTS_CTS, MCFGPIO_PAR_PSC2);
	__raw_ग_लिखोb(MCF_PAR_PSC_TXD | MCF_PAR_PSC_RXD, MCFGPIO_PAR_PSC3);
पूर्ण

/***************************************************************************/

अटल व्योम __init m54xx_i2c_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C_IMX)
	u32 r;

	/* set the fec/i2c/irq pin assignment रेजिस्टर क्रम i2c */
	r = पढ़ोl(MCF_PAR_FECI2CIRQ);
	r |= MCF_PAR_FECI2CIRQ_SDA | MCF_PAR_FECI2CIRQ_SCL;
	ग_लिखोl(r, MCF_PAR_FECI2CIRQ);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_I2C_IMX) */
पूर्ण

/***************************************************************************/

अटल व्योम mcf54xx_reset(व्योम)
अणु
	/* disable पूर्णांकerrupts and enable the watchकरोg */
	यंत्र("movew #0x2700, %sr\n");
	__raw_ग_लिखोl(0, MCF_GPT_GMS0);
	__raw_ग_लिखोl(MCF_GPT_GCIR_CNT(1), MCF_GPT_GCIR0);
	__raw_ग_लिखोl(MCF_GPT_GMS_WDEN | MCF_GPT_GMS_CE | MCF_GPT_GMS_TMS(4),
		MCF_GPT_GMS0);
पूर्ण

/***************************************************************************/

व्योम __init config_BSP(अक्षर *commandp, पूर्णांक size)
अणु
	mach_reset = mcf54xx_reset;
	mach_sched_init = hw_समयr_init;
	m54xx_uarts_init();
	m54xx_i2c_init();
पूर्ण

/***************************************************************************/
