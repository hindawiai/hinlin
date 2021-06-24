<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	m5249.c  -- platक्रमm support क्रम ColdFire 5249 based boards
 *
 *	Copyright (C) 2002, Greg Ungerer (gerg@snapgear.com)
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

#अगर_घोषित CONFIG_M5249C3

अटल काष्ठा resource m5249_smc91x_resources[] = अणु
	अणु
		.start		= 0xe0000300,
		.end		= 0xe0000300 + 0x100,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= MCF_IRQ_GPIO6,
		.end		= MCF_IRQ_GPIO6,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device m5249_smc91x = अणु
	.name			= "smc91x",
	.id			= 0,
	.num_resources		= ARRAY_SIZE(m5249_smc91x_resources),
	.resource		= m5249_smc91x_resources,
पूर्ण;

#पूर्ण_अगर /* CONFIG_M5249C3 */

अटल काष्ठा platक्रमm_device *m5249_devices[] __initdata = अणु
#अगर_घोषित CONFIG_M5249C3
	&m5249_smc91x,
#पूर्ण_अगर
पूर्ण;

/***************************************************************************/

अटल व्योम __init m5249_qspi_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI)
	/* QSPI irq setup */
	ग_लिखोb(MCFSIM_ICR_AUTOVEC | MCFSIM_ICR_LEVEL4 | MCFSIM_ICR_PRI0,
	       MCFSIM_QSPIICR);
	mcf_mapirq2imr(MCF_IRQ_QSPI, MCFINTC_QSPI);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI) */
पूर्ण

/***************************************************************************/

अटल व्योम __init m5249_i2c_init(व्योम)
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
#पूर्ण_अगर /* CONFIG_I2C_IMX */
पूर्ण

/***************************************************************************/

#अगर_घोषित CONFIG_M5249C3

अटल व्योम __init m5249_smc91x_init(व्योम)
अणु
	u32  gpio;

	/* Set the GPIO line as पूर्णांकerrupt source क्रम smc91x device */
	gpio = पढ़ोl(MCFSIM2_GPIOINTENABLE);
	ग_लिखोl(gpio | 0x40, MCFSIM2_GPIOINTENABLE);

	gpio = पढ़ोl(MCFINTC2_INTPRI5);
	ग_लिखोl(gpio | 0x04000000, MCFINTC2_INTPRI5);
पूर्ण

#पूर्ण_अगर /* CONFIG_M5249C3 */

/***************************************************************************/

व्योम __init config_BSP(अक्षर *commandp, पूर्णांक size)
अणु
	mach_sched_init = hw_समयr_init;

#अगर_घोषित CONFIG_M5249C3
	m5249_smc91x_init();
#पूर्ण_अगर
	m5249_qspi_init();
	m5249_i2c_init();
पूर्ण

/***************************************************************************/

अटल पूर्णांक __init init_BSP(व्योम)
अणु
	platक्रमm_add_devices(m5249_devices, ARRAY_SIZE(m5249_devices));
	वापस 0;
पूर्ण

arch_initcall(init_BSP);

/***************************************************************************/
