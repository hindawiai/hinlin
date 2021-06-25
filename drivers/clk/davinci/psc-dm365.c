<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PSC घड़ी descriptions क्रम TI DaVinci DM365
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

LPSC_CLKDEV1(vpss_slave_clkdev,		"slave",	"vpss");
LPSC_CLKDEV1(spi1_clkdev,		शून्य,		"spi_davinci.1");
LPSC_CLKDEV1(mmcsd1_clkdev,		शून्य,		"da830-mmc.1");
LPSC_CLKDEV1(asp0_clkdev,		शून्य,		"davinci-mcbsp");
LPSC_CLKDEV1(usb_clkdev,		"usb",		शून्य);
LPSC_CLKDEV1(spi2_clkdev,		शून्य,		"spi_davinci.2");
LPSC_CLKDEV2(aemअगर_clkdev,		"aemif",	शून्य,
					शून्य,		"ti-aemif");
LPSC_CLKDEV1(mmcsd0_clkdev,		शून्य,		"da830-mmc.0");
LPSC_CLKDEV1(i2c_clkdev,		शून्य,		"i2c_davinci.1");
LPSC_CLKDEV1(uart0_clkdev,		शून्य,		"serial8250.0");
LPSC_CLKDEV1(uart1_clkdev,		शून्य,		"serial8250.1");
LPSC_CLKDEV1(spi0_clkdev,		शून्य,		"spi_davinci.0");
/* REVISIT: gpio-davinci.c should be modअगरied to drop con_id */
LPSC_CLKDEV1(gpio_clkdev,		"gpio",		शून्य);
LPSC_CLKDEV1(समयr0_clkdev,		"timer0",	शून्य);
LPSC_CLKDEV1(समयr2_clkdev,		शून्य,		"davinci-wdt");
LPSC_CLKDEV1(spi3_clkdev,		शून्य,		"spi_davinci.3");
LPSC_CLKDEV1(spi4_clkdev,		शून्य,		"spi_davinci.4");
LPSC_CLKDEV2(emac_clkdev,		शून्य,		"davinci_emac.1",
					"fck",		"davinci_mdio.0");
LPSC_CLKDEV1(voice_codec_clkdev,	शून्य,		"davinci_voicecodec");
LPSC_CLKDEV1(vpss_dac_clkdev,		"vpss_dac",	शून्य);
LPSC_CLKDEV1(vpss_master_clkdev,	"master",	"vpss");

अटल स्थिर काष्ठा davinci_lpsc_clk_info dm365_psc_info[] = अणु
	LPSC(1,  0, vpss_slave,  pll1_sysclk5, vpss_slave_clkdev,  0),
	LPSC(5,  0, समयr3,      pll1_auxclk,  शून्य,               0),
	LPSC(6,  0, spi1,        pll1_sysclk4, spi1_clkdev,        0),
	LPSC(7,  0, mmcsd1,      pll1_sysclk4, mmcsd1_clkdev,      0),
	LPSC(8,  0, asp0,        pll1_sysclk4, asp0_clkdev,        0),
	LPSC(9,  0, usb,         pll1_auxclk,  usb_clkdev,         0),
	LPSC(10, 0, pwm3,        pll1_auxclk,  शून्य,               0),
	LPSC(11, 0, spi2,        pll1_sysclk4, spi2_clkdev,        0),
	LPSC(12, 0, rto,         pll1_sysclk4, शून्य,               0),
	LPSC(14, 0, aemअगर,       pll1_sysclk4, aemअगर_clkdev,       0),
	LPSC(15, 0, mmcsd0,      pll1_sysclk8, mmcsd0_clkdev,      0),
	LPSC(18, 0, i2c,         pll1_auxclk,  i2c_clkdev,         0),
	LPSC(19, 0, uart0,       pll1_auxclk,  uart0_clkdev,       0),
	LPSC(20, 0, uart1,       pll1_sysclk4, uart1_clkdev,       0),
	LPSC(22, 0, spi0,        pll1_sysclk4, spi0_clkdev,        0),
	LPSC(23, 0, pwm0,        pll1_auxclk,  शून्य,               0),
	LPSC(24, 0, pwm1,        pll1_auxclk,  शून्य,               0),
	LPSC(25, 0, pwm2,        pll1_auxclk,  शून्य,               0),
	LPSC(26, 0, gpio,        pll1_sysclk4, gpio_clkdev,        0),
	LPSC(27, 0, समयr0,      pll1_auxclk,  समयr0_clkdev,      LPSC_ALWAYS_ENABLED),
	LPSC(28, 0, समयr1,      pll1_auxclk,  शून्य,               0),
	/* REVISIT: why can't this be disabled? */
	LPSC(29, 0, समयr2,      pll1_auxclk,  समयr2_clkdev,      LPSC_ALWAYS_ENABLED),
	LPSC(31, 0, arm,         pll2_sysclk2, शून्य,               LPSC_ALWAYS_ENABLED),
	LPSC(38, 0, spi3,        pll1_sysclk4, spi3_clkdev,        0),
	LPSC(39, 0, spi4,        pll1_auxclk,  spi4_clkdev,        0),
	LPSC(40, 0, emac,        pll1_sysclk4, emac_clkdev,        0),
	/*
	 * The TRM (ARM Subप्रणाली User's Guide) shows two घड़ीs input पूर्णांकo
	 * voice codec module (PLL2 SYSCLK4 with a DIV2 and PLL1 SYSCLK4). Its
	 * not fully clear from करोcumentation which घड़ी should be considered
	 * as parent क्रम PSC. The घड़ी chosen here is to मुख्यtain
	 * compatibility with existing code in arch/arm/mach-davinci/dm365.c
	 */
	LPSC(44, 0, voice_codec, pll2_sysclk4, voice_codec_clkdev, 0),
	/*
	 * Its not fully clear from TRM (ARM Subप्रणाली User's Guide) as to what
	 * the parent of VPSS DAC LPSC should actually be. PLL1 SYSCLK3 feeds
	 * पूर्णांकo HDVICP and MJCP. The घड़ी chosen here is to reमुख्य compatible
	 * with code existing in arch/arm/mach-davinci/dm365.c
	 */
	LPSC(46, 0, vpss_dac,    pll1_sysclk3, vpss_dac_clkdev,    0),
	LPSC(47, 0, vpss_master, pll1_sysclk5, vpss_master_clkdev, 0),
	LPSC(50, 0, mjcp,        pll1_sysclk3, शून्य,               0),
	अणु पूर्ण
पूर्ण;

पूर्णांक dm365_psc_init(काष्ठा device *dev, व्योम __iomem *base)
अणु
	वापस davinci_psc_रेजिस्टर_घड़ीs(dev, dm365_psc_info, 52, base);
पूर्ण

अटल काष्ठा clk_bulk_data dm365_psc_parent_clks[] = अणु
	अणु .id = "pll1_sysclk1" पूर्ण,
	अणु .id = "pll1_sysclk3" पूर्ण,
	अणु .id = "pll1_sysclk4" पूर्ण,
	अणु .id = "pll1_sysclk5" पूर्ण,
	अणु .id = "pll1_sysclk8" पूर्ण,
	अणु .id = "pll2_sysclk2" पूर्ण,
	अणु .id = "pll2_sysclk4" पूर्ण,
	अणु .id = "pll1_auxclk"  पूर्ण,
पूर्ण;

स्थिर काष्ठा davinci_psc_init_data dm365_psc_init_data = अणु
	.parent_clks		= dm365_psc_parent_clks,
	.num_parent_clks	= ARRAY_SIZE(dm365_psc_parent_clks),
	.psc_init		= &dm365_psc_init,
पूर्ण;
