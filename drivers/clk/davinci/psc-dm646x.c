<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PSC घड़ी descriptions क्रम TI DaVinci DM646x
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/davinci.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

#समावेश "psc.h"

LPSC_CLKDEV1(ide_clkdev,	शून्य,		"palm_bk3710");
LPSC_CLKDEV2(emac_clkdev,	शून्य,		"davinci_emac.1",
				"fck",		"davinci_mdio.0");
LPSC_CLKDEV2(aemअगर_clkdev,	"aemif",	शून्य,
				शून्य,		"ti-aemif");
LPSC_CLKDEV1(mcasp0_clkdev,	शून्य,		"davinci-mcasp.0");
LPSC_CLKDEV1(mcasp1_clkdev,	शून्य,		"davinci-mcasp.1");
LPSC_CLKDEV1(uart0_clkdev,	शून्य,		"serial8250.0");
LPSC_CLKDEV1(uart1_clkdev,	शून्य,		"serial8250.1");
LPSC_CLKDEV1(uart2_clkdev,	शून्य,		"serial8250.2");
LPSC_CLKDEV1(i2c_clkdev,	शून्य,		"i2c_davinci.1");
/* REVISIT: gpio-davinci.c should be modअगरied to drop con_id */
LPSC_CLKDEV1(gpio_clkdev,	"gpio",		शून्य);
LPSC_CLKDEV1(समयr0_clkdev,	"timer0",	 शून्य);

अटल स्थिर काष्ठा davinci_lpsc_clk_info dm646x_psc_info[] = अणु
	LPSC(0,  0, arm,      pll1_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	/* REVISIT how to disable? */
	LPSC(1,  0, dsp,      pll1_sysclk1, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(4,  0, edma_cc,  pll1_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(5,  0, edma_tc0, pll1_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(6,  0, edma_tc1, pll1_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(7,  0, edma_tc2, pll1_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(8,  0, edma_tc3, pll1_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(10, 0, ide,      pll1_sysclk4, ide_clkdev,    0),
	LPSC(14, 0, emac,     pll1_sysclk3, emac_clkdev,   0),
	LPSC(16, 0, vpअगर0,    ref_clk,      शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(17, 0, vpअगर1,    ref_clk,      शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(21, 0, aemअगर,    pll1_sysclk3, aemअगर_clkdev,  LPSC_ALWAYS_ENABLED),
	LPSC(22, 0, mcasp0,   pll1_sysclk3, mcasp0_clkdev, 0),
	LPSC(23, 0, mcasp1,   pll1_sysclk3, mcasp1_clkdev, 0),
	LPSC(26, 0, uart0,    aux_clkin,    uart0_clkdev,  0),
	LPSC(27, 0, uart1,    aux_clkin,    uart1_clkdev,  0),
	LPSC(28, 0, uart2,    aux_clkin,    uart2_clkdev,  0),
	/* REVIST: disabling hangs प्रणाली */
	LPSC(29, 0, pwm0,     pll1_sysclk3, शून्य,          LPSC_ALWAYS_ENABLED),
	/* REVIST: disabling hangs प्रणाली */
	LPSC(30, 0, pwm1,     pll1_sysclk3, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(31, 0, i2c,      pll1_sysclk3, i2c_clkdev,    0),
	LPSC(33, 0, gpio,     pll1_sysclk3, gpio_clkdev,   0),
	LPSC(34, 0, समयr0,   pll1_sysclk3, समयr0_clkdev, LPSC_ALWAYS_ENABLED),
	LPSC(35, 0, समयr1,   pll1_sysclk3, शून्य,          0),
	अणु पूर्ण
पूर्ण;

पूर्णांक dm646x_psc_init(काष्ठा device *dev, व्योम __iomem *base)
अणु
	वापस davinci_psc_रेजिस्टर_घड़ीs(dev, dm646x_psc_info, 46, base);
पूर्ण

अटल काष्ठा clk_bulk_data dm646x_psc_parent_clks[] = अणु
	अणु .id = "ref_clk"      पूर्ण,
	अणु .id = "aux_clkin"    पूर्ण,
	अणु .id = "pll1_sysclk1" पूर्ण,
	अणु .id = "pll1_sysclk2" पूर्ण,
	अणु .id = "pll1_sysclk3" पूर्ण,
	अणु .id = "pll1_sysclk4" पूर्ण,
	अणु .id = "pll1_sysclk5" पूर्ण,
पूर्ण;

स्थिर काष्ठा davinci_psc_init_data dm646x_psc_init_data = अणु
	.parent_clks		= dm646x_psc_parent_clks,
	.num_parent_clks	= ARRAY_SIZE(dm646x_psc_parent_clks),
	.psc_init		= &dm646x_psc_init,
पूर्ण;
