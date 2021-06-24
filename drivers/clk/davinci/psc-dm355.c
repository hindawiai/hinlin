<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PSC घड़ी descriptions क्रम TI DaVinci DM355
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
LPSC_CLKDEV1(spi1_clkdev,		शून्य,		"spi_davinci.1");
LPSC_CLKDEV1(mmcsd1_clkdev,		शून्य,		"dm6441-mmc.1");
LPSC_CLKDEV1(mcbsp1_clkdev,		शून्य,		"davinci-mcbsp.1");
LPSC_CLKDEV1(usb_clkdev,		"usb",		शून्य);
LPSC_CLKDEV1(spi2_clkdev,		शून्य,		"spi_davinci.2");
LPSC_CLKDEV1(aemअगर_clkdev,		"aemif",	शून्य);
LPSC_CLKDEV1(mmcsd0_clkdev,		शून्य,		"dm6441-mmc.0");
LPSC_CLKDEV1(mcbsp0_clkdev,		शून्य,		"davinci-mcbsp.0");
LPSC_CLKDEV1(i2c_clkdev,		शून्य,		"i2c_davinci.1");
LPSC_CLKDEV1(uart0_clkdev,		शून्य,		"serial8250.0");
LPSC_CLKDEV1(uart1_clkdev,		शून्य,		"serial8250.1");
LPSC_CLKDEV1(uart2_clkdev,		शून्य,		"serial8250.2");
LPSC_CLKDEV1(spi0_clkdev,		शून्य,		"spi_davinci.0");
/* REVISIT: gpio-davinci.c should be modअगरied to drop con_id */
LPSC_CLKDEV1(gpio_clkdev,		"gpio",		शून्य);
LPSC_CLKDEV1(समयr0_clkdev,		"timer0",	शून्य);
LPSC_CLKDEV1(समयr2_clkdev,		शून्य,		"davinci-wdt");
LPSC_CLKDEV1(vpss_dac_clkdev,		"vpss_dac",	शून्य);

अटल स्थिर काष्ठा davinci_lpsc_clk_info dm355_psc_info[] = अणु
	LPSC(0,  0, vpss_master, pll1_sysclk4, vpss_master_clkdev, 0),
	LPSC(1,  0, vpss_slave,  pll1_sysclk4, vpss_slave_clkdev,  0),
	LPSC(5,  0, समयr3,      pll1_auxclk,  शून्य,               0),
	LPSC(6,  0, spi1,        pll1_sysclk2, spi1_clkdev,        0),
	LPSC(7,  0, mmcsd1,      pll1_sysclk2, mmcsd1_clkdev,      0),
	LPSC(8,  0, asp1,        pll1_sysclk2, mcbsp1_clkdev,      0),
	LPSC(9,  0, usb,         pll1_sysclk2, usb_clkdev,         0),
	LPSC(10, 0, pwm3,        pll1_auxclk,  शून्य,               0),
	LPSC(11, 0, spi2,        pll1_sysclk2, spi2_clkdev,        0),
	LPSC(12, 0, rto,         pll1_auxclk,  शून्य,               0),
	LPSC(14, 0, aemअगर,       pll1_sysclk2, aemअगर_clkdev,       0),
	LPSC(15, 0, mmcsd0,      pll1_sysclk2, mmcsd0_clkdev,      0),
	LPSC(17, 0, asp0,        pll1_sysclk2, mcbsp0_clkdev,      0),
	LPSC(18, 0, i2c,         pll1_auxclk,  i2c_clkdev,         0),
	LPSC(19, 0, uart0,       pll1_auxclk,  uart0_clkdev,       0),
	LPSC(20, 0, uart1,       pll1_auxclk,  uart1_clkdev,       0),
	LPSC(21, 0, uart2,       pll1_sysclk2, uart2_clkdev,       0),
	LPSC(22, 0, spi0,        pll1_sysclk2, spi0_clkdev,        0),
	LPSC(23, 0, pwm0,        pll1_auxclk,  शून्य,               0),
	LPSC(24, 0, pwm1,        pll1_auxclk,  शून्य,               0),
	LPSC(25, 0, pwm2,        pll1_auxclk,  शून्य,               0),
	LPSC(26, 0, gpio,        pll1_sysclk2, gpio_clkdev,        0),
	LPSC(27, 0, समयr0,      pll1_auxclk,  समयr0_clkdev,      LPSC_ALWAYS_ENABLED),
	LPSC(28, 0, समयr1,      pll1_auxclk,  शून्य,               0),
	/* REVISIT: why can't this be disabled? */
	LPSC(29, 0, समयr2,      pll1_auxclk,  समयr2_clkdev,      LPSC_ALWAYS_ENABLED),
	LPSC(31, 0, arm,         pll1_sysclk1, शून्य,               LPSC_ALWAYS_ENABLED),
	LPSC(40, 0, mjcp,        pll1_sysclk1, शून्य,               0),
	LPSC(41, 0, vpss_dac,    pll1_sysclk3, vpss_dac_clkdev,    0),
	अणु पूर्ण
पूर्ण;

पूर्णांक dm355_psc_init(काष्ठा device *dev, व्योम __iomem *base)
अणु
	वापस davinci_psc_रेजिस्टर_घड़ीs(dev, dm355_psc_info, 42, base);
पूर्ण

अटल काष्ठा clk_bulk_data dm355_psc_parent_clks[] = अणु
	अणु .id = "pll1_sysclk1" पूर्ण,
	अणु .id = "pll1_sysclk2" पूर्ण,
	अणु .id = "pll1_sysclk3" पूर्ण,
	अणु .id = "pll1_sysclk4" पूर्ण,
	अणु .id = "pll1_auxclk"  पूर्ण,
पूर्ण;

स्थिर काष्ठा davinci_psc_init_data dm355_psc_init_data = अणु
	.parent_clks		= dm355_psc_parent_clks,
	.num_parent_clks	= ARRAY_SIZE(dm355_psc_parent_clks),
	.psc_init		= &dm355_psc_init,
पूर्ण;
