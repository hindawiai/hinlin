<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	m5272.c  -- platक्रमm support क्रम ColdFire 5272 based boards
 *
 *	Copyright (C) 1999-2002, Greg Ungerer (gerg@snapgear.com)
 *	Copyright (C) 2001-2002, SnapGear Inc. (www.snapgear.com)
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfuart.h>
#समावेश <यंत्र/mcfclk.h>

/***************************************************************************/

/*
 *	Some platक्रमms need software versions of the GPIO data रेजिस्टरs.
 */
अचिन्हित लघु ppdata;
अचिन्हित अक्षर ledbank = 0xff;

/***************************************************************************/

DEFINE_CLK(pll, "pll.0", MCF_CLK);
DEFINE_CLK(sys, "sys.0", MCF_BUSCLK);
DEFINE_CLK(mcfपंचांगr0, "mcftmr.0", MCF_BUSCLK);
DEFINE_CLK(mcfपंचांगr1, "mcftmr.1", MCF_BUSCLK);
DEFINE_CLK(mcfपंचांगr2, "mcftmr.2", MCF_BUSCLK);
DEFINE_CLK(mcfपंचांगr3, "mcftmr.3", MCF_BUSCLK);
DEFINE_CLK(mcfuart0, "mcfuart.0", MCF_BUSCLK);
DEFINE_CLK(mcfuart1, "mcfuart.1", MCF_BUSCLK);
DEFINE_CLK(mcfqspi0, "mcfqspi.0", MCF_BUSCLK);
DEFINE_CLK(fec0, "fec.0", MCF_BUSCLK);

काष्ठा clk *mcf_clks[] = अणु
	&clk_pll,
	&clk_sys,
	&clk_mcfपंचांगr0,
	&clk_mcfपंचांगr1,
	&clk_mcfपंचांगr2,
	&clk_mcfपंचांगr3,
	&clk_mcfuart0,
	&clk_mcfuart1,
	&clk_mcfqspi0,
	&clk_fec0,
	शून्य
पूर्ण;

/***************************************************************************/

अटल व्योम __init m5272_uarts_init(व्योम)
अणु
	u32 v;

	/* Enable the output lines क्रम the serial ports */
	v = पढ़ोl(MCFSIM_PBCNT);
	v = (v & ~0x000000ff) | 0x00000055;
	ग_लिखोl(v, MCFSIM_PBCNT);

	v = पढ़ोl(MCFSIM_PDCNT);
	v = (v & ~0x000003fc) | 0x000002a8;
	ग_लिखोl(v, MCFSIM_PDCNT);
पूर्ण

/***************************************************************************/

अटल व्योम m5272_cpu_reset(व्योम)
अणु
	local_irq_disable();
	/* Set watchकरोg to reset, and enabled */
	__raw_ग_लिखोw(0, MCFSIM_WIRR);
	__raw_ग_लिखोw(1, MCFSIM_WRRR);
	__raw_ग_लिखोw(0, MCFSIM_WCR);
	क्रम (;;)
		/* रुको क्रम watchकरोg to समयout */;
पूर्ण

/***************************************************************************/

व्योम __init config_BSP(अक्षर *commandp, पूर्णांक size)
अणु
#अगर defined (CONFIG_MOD5272)
	/* Set base of device vectors to be 64 */
	ग_लिखोb(0x40, MCFSIM_PIVR);
#पूर्ण_अगर

#अगर defined(CONFIG_NETtel) || defined(CONFIG_SCALES)
	/* Copy command line from FLASH to local buffer... */
	स_नकल(commandp, (अक्षर *) 0xf0004000, size);
	commandp[size-1] = 0;
#या_अगर defined(CONFIG_CANCam)
	/* Copy command line from FLASH to local buffer... */
	स_नकल(commandp, (अक्षर *) 0xf0010000, size);
	commandp[size-1] = 0;
#पूर्ण_अगर

	mach_reset = m5272_cpu_reset;
	mach_sched_init = hw_समयr_init;
पूर्ण

/***************************************************************************/

/*
 * Some 5272 based boards have the FEC ethernet directly connected to
 * an ethernet चयन. In this हाल we need to use the fixed phy type,
 * and we need to declare it early in boot.
 */
अटल काष्ठा fixed_phy_status nettel_fixed_phy_status __initdata = अणु
	.link	= 1,
	.speed	= 100,
	.duplex	= 0,
पूर्ण;

/***************************************************************************/

अटल पूर्णांक __init init_BSP(व्योम)
अणु
	m5272_uarts_init();
	fixed_phy_add(PHY_POLL, 0, &nettel_fixed_phy_status);
	वापस 0;
पूर्ण

arch_initcall(init_BSP);

/***************************************************************************/
