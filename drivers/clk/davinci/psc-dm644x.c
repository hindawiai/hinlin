<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PSC घड़ी descriptions क्रम TI DaVinci DM644x
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

LPSC_CLKDEV1(vpss_master_clkdev,	"master",	"vpss");
LPSC_CLKDEV1(vpss_slave_clkdev,		"slave",	"vpss");
LPSC_CLKDEV2(emac_clkdev,		शून्य,		"davinci_emac.1",
					"fck",		"davinci_mdio.0");
LPSC_CLKDEV1(usb_clkdev,		"usb",		शून्य);
LPSC_CLKDEV1(ide_clkdev,		शून्य,		"palm_bk3710");
LPSC_CLKDEV2(aemअगर_clkdev,		"aemif",	शून्य,
					शून्य,		"ti-aemif");
LPSC_CLKDEV1(mmcsd_clkdev,		शून्य,		"dm6441-mmc.0");
LPSC_CLKDEV1(asp0_clkdev,		शून्य,		"davinci-mcbsp");
LPSC_CLKDEV1(i2c_clkdev,		शून्य,		"i2c_davinci.1");
LPSC_CLKDEV1(uart0_clkdev,		शून्य,		"serial8250.0");
LPSC_CLKDEV1(uart1_clkdev,		शून्य,		"serial8250.1");
LPSC_CLKDEV1(uart2_clkdev,		शून्य,		"serial8250.2");
/* REVISIT: gpio-davinci.c should be modअगरied to drop con_id */
LPSC_CLKDEV1(gpio_clkdev,		"gpio",		शून्य);
LPSC_CLKDEV1(समयr0_clkdev,		"timer0",	शून्य);
LPSC_CLKDEV1(समयr2_clkdev,		शून्य,		"davinci-wdt");

अटल स्थिर काष्ठा davinci_lpsc_clk_info dm644x_psc_info[] = अणु
	LPSC(0,  0, vpss_master, pll1_sysclk3, vpss_master_clkdev, 0),
	LPSC(1,  0, vpss_slave,  pll1_sysclk3, vpss_slave_clkdev,  0),
	LPSC(6,  0, emac,        pll1_sysclk5, emac_clkdev,        0),
	LPSC(9,  0, usb,         pll1_sysclk5, usb_clkdev,         0),
	LPSC(10, 0, ide,         pll1_sysclk5, ide_clkdev,         0),
	LPSC(11, 0, vlynq,       pll1_sysclk5, शून्य,               0),
	LPSC(14, 0, aemअगर,       pll1_sysclk5, aemअगर_clkdev,       0),
	LPSC(15, 0, mmcsd,       pll1_sysclk5, mmcsd_clkdev,       0),
	LPSC(17, 0, asp0,        pll1_sysclk5, asp0_clkdev,        0),
	LPSC(18, 0, i2c,         pll1_auxclk,  i2c_clkdev,         0),
	LPSC(19, 0, uart0,       pll1_auxclk,  uart0_clkdev,       0),
	LPSC(20, 0, uart1,       pll1_auxclk,  uart1_clkdev,       0),
	LPSC(21, 0, uart2,       pll1_auxclk,  uart2_clkdev,       0),
	LPSC(22, 0, spi,         pll1_sysclk5, शून्य,               0),
	LPSC(23, 0, pwm0,        pll1_auxclk,  शून्य,               0),
	LPSC(24, 0, pwm1,        pll1_auxclk,  शून्य,               0),
	LPSC(25, 0, pwm2,        pll1_auxclk,  शून्य,               0),
	LPSC(26, 0, gpio,        pll1_sysclk5, gpio_clkdev,        0),
	LPSC(27, 0, समयr0,      pll1_auxclk,  समयr0_clkdev,      LPSC_ALWAYS_ENABLED),
	LPSC(28, 0, समयr1,      pll1_auxclk,  शून्य,               0),
	/* REVISIT: why can't this be disabled? */
	LPSC(29, 0, समयr2,      pll1_auxclk,  समयr2_clkdev,      LPSC_ALWAYS_ENABLED),
	LPSC(31, 0, arm,         pll1_sysclk2, शून्य,               LPSC_ALWAYS_ENABLED),
	/* REVISIT how to disable? */
	LPSC(39, 1, dsp,         pll1_sysclk1, शून्य,               LPSC_ALWAYS_ENABLED),
	/* REVISIT how to disable? */
	LPSC(40, 1, vicp,        pll1_sysclk2, शून्य,               LPSC_ALWAYS_ENABLED),
	अणु पूर्ण
पूर्ण;

पूर्णांक dm644x_psc_init(काष्ठा device *dev, व्योम __iomem *base)
अणु
	वापस davinci_psc_रेजिस्टर_घड़ीs(dev, dm644x_psc_info, 41, base);
पूर्ण

अटल काष्ठा clk_bulk_data dm644x_psc_parent_clks[] = अणु
	अणु .id = "pll1_sysclk1" पूर्ण,
	अणु .id = "pll1_sysclk2" पूर्ण,
	अणु .id = "pll1_sysclk3" पूर्ण,
	अणु .id = "pll1_sysclk5" पूर्ण,
	अणु .id = "pll1_auxclk"  पूर्ण,
पूर्ण;

स्थिर काष्ठा davinci_psc_init_data dm644x_psc_init_data = अणु
	.parent_clks		= dm644x_psc_parent_clks,
	.num_parent_clks	= ARRAY_SIZE(dm644x_psc_parent_clks),
	.psc_init		= &dm644x_psc_init,
पूर्ण;
