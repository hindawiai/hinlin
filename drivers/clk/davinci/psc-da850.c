<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PSC घड़ी descriptions क्रम TI DA850/OMAP-L138/AM18XX
 *
 * Copyright (C) 2018 David Lechner <david@lechnology.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/types.h>

#समावेश "psc.h"

LPSC_CLKDEV1(emअगरa_clkdev,	शून्य,		"ti-aemif");
LPSC_CLKDEV1(spi0_clkdev,	शून्य,		"spi_davinci.0");
LPSC_CLKDEV1(mmcsd0_clkdev,	शून्य,		"da830-mmc.0");
LPSC_CLKDEV1(uart0_clkdev,	शून्य,		"serial8250.0");
/* REVISIT: used dev_id instead of con_id */
LPSC_CLKDEV1(arm_clkdev,	"arm",		शून्य);
LPSC_CLKDEV1(dsp_clkdev,	शून्य,		"davinci-rproc.0");

अटल स्थिर काष्ठा davinci_lpsc_clk_info da850_psc0_info[] = अणु
	LPSC(0,  0, tpcc0,   pll0_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(1,  0, tptc0,   pll0_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(2,  0, tptc1,   pll0_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(3,  0, emअगरa,   async1,       emअगरa_clkdev,  0),
	LPSC(4,  0, spi0,    pll0_sysclk2, spi0_clkdev,   0),
	LPSC(5,  0, mmcsd0,  pll0_sysclk2, mmcsd0_clkdev, 0),
	LPSC(6,  0, aपूर्णांकc,   pll0_sysclk4, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(7,  0, arm_rom, pll0_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(9,  0, uart0,   pll0_sysclk2, uart0_clkdev,  0),
	LPSC(13, 0, pruss,   pll0_sysclk2, शून्य,          0),
	LPSC(14, 0, arm,     pll0_sysclk6, arm_clkdev,    LPSC_ALWAYS_ENABLED | LPSC_SET_RATE_PARENT),
	LPSC(15, 1, dsp,     pll0_sysclk1, dsp_clkdev,    LPSC_FORCE | LPSC_LOCAL_RESET),
	अणु पूर्ण
पूर्ण;

LPSC_CLKDEV3(usb0_clkdev,	"fck",	"da830-usb-phy-clks",
				शून्य,	"musb-da8xx",
				शून्य,	"cppi41-dmaengine");
LPSC_CLKDEV1(usb1_clkdev,	शून्य,	"ohci-da8xx");
/* REVISIT: gpio-davinci.c should be modअगरied to drop con_id */
LPSC_CLKDEV1(gpio_clkdev,	"gpio",	शून्य);
LPSC_CLKDEV2(emac_clkdev,	शून्य,	"davinci_emac.1",
				"fck",	"davinci_mdio.0");
LPSC_CLKDEV1(mcasp0_clkdev,	शून्य,	"davinci-mcasp.0");
LPSC_CLKDEV1(sata_clkdev,	"fck",	"ahci_da850");
LPSC_CLKDEV1(vpअगर_clkdev,	शून्य,	"vpif");
LPSC_CLKDEV1(spi1_clkdev,	शून्य,	"spi_davinci.1");
LPSC_CLKDEV1(i2c1_clkdev,	शून्य,	"i2c_davinci.2");
LPSC_CLKDEV1(uart1_clkdev,	शून्य,	"serial8250.1");
LPSC_CLKDEV1(uart2_clkdev,	शून्य,	"serial8250.2");
LPSC_CLKDEV1(mcbsp0_clkdev,	शून्य,	"davinci-mcbsp.0");
LPSC_CLKDEV1(mcbsp1_clkdev,	शून्य,	"davinci-mcbsp.1");
LPSC_CLKDEV1(lcdc_clkdev,	"fck",	"da8xx_lcdc.0");
LPSC_CLKDEV3(ehrpwm_clkdev,	"fck",	"ehrpwm.0",
				"fck",	"ehrpwm.1",
				शून्य,	"da830-tbclksync");
LPSC_CLKDEV1(mmcsd1_clkdev,	शून्य,	"da830-mmc.1");
LPSC_CLKDEV3(ecap_clkdev,	"fck",	"ecap.0",
				"fck",	"ecap.1",
				"fck",	"ecap.2");

अटल काष्ठा reset_control_lookup da850_psc0_reset_lookup_table[] = अणु
	RESET_LOOKUP("da850-psc0", 15, "davinci-rproc.0", शून्य),
पूर्ण;

अटल पूर्णांक da850_psc0_init(काष्ठा device *dev, व्योम __iomem *base)
अणु
	reset_controller_add_lookup(da850_psc0_reset_lookup_table,
				    ARRAY_SIZE(da850_psc0_reset_lookup_table));
	वापस davinci_psc_रेजिस्टर_घड़ीs(dev, da850_psc0_info, 16, base);
पूर्ण

अटल पूर्णांक of_da850_psc0_init(काष्ठा device *dev, व्योम __iomem *base)
अणु
	वापस of_davinci_psc_clk_init(dev, da850_psc0_info, 16, base);
पूर्ण

अटल काष्ठा clk_bulk_data da850_psc0_parent_clks[] = अणु
	अणु .id = "pll0_sysclk1" पूर्ण,
	अणु .id = "pll0_sysclk2" पूर्ण,
	अणु .id = "pll0_sysclk4" पूर्ण,
	अणु .id = "pll0_sysclk6" पूर्ण,
	अणु .id = "async1"       पूर्ण,
पूर्ण;

स्थिर काष्ठा davinci_psc_init_data da850_psc0_init_data = अणु
	.parent_clks		= da850_psc0_parent_clks,
	.num_parent_clks	= ARRAY_SIZE(da850_psc0_parent_clks),
	.psc_init		= &da850_psc0_init,
पूर्ण;

स्थिर काष्ठा davinci_psc_init_data of_da850_psc0_init_data = अणु
	.parent_clks		= da850_psc0_parent_clks,
	.num_parent_clks	= ARRAY_SIZE(da850_psc0_parent_clks),
	.psc_init		= &of_da850_psc0_init,
पूर्ण;

अटल स्थिर काष्ठा davinci_lpsc_clk_info da850_psc1_info[] = अणु
	LPSC(0,  0, tpcc1,  pll0_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(1,  0, usb0,   pll0_sysclk2, usb0_clkdev,   0),
	LPSC(2,  0, usb1,   pll0_sysclk4, usb1_clkdev,   0),
	LPSC(3,  0, gpio,   pll0_sysclk4, gpio_clkdev,   0),
	LPSC(5,  0, emac,   pll0_sysclk4, emac_clkdev,   0),
	LPSC(6,  0, ddr,    pll0_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	LPSC(7,  0, mcasp0, async3,       mcasp0_clkdev, 0),
	LPSC(8,  0, sata,   pll0_sysclk2, sata_clkdev,   LPSC_FORCE),
	LPSC(9,  0, vpअगर,   pll0_sysclk2, vpअगर_clkdev,   0),
	LPSC(10, 0, spi1,   async3,       spi1_clkdev,   0),
	LPSC(11, 0, i2c1,   pll0_sysclk4, i2c1_clkdev,   0),
	LPSC(12, 0, uart1,  async3,       uart1_clkdev,  0),
	LPSC(13, 0, uart2,  async3,       uart2_clkdev,  0),
	LPSC(14, 0, mcbsp0, async3,       mcbsp0_clkdev, 0),
	LPSC(15, 0, mcbsp1, async3,       mcbsp1_clkdev, 0),
	LPSC(16, 0, lcdc,   pll0_sysclk2, lcdc_clkdev,   0),
	LPSC(17, 0, ehrpwm, async3,       ehrpwm_clkdev, 0),
	LPSC(18, 0, mmcsd1, pll0_sysclk2, mmcsd1_clkdev, 0),
	LPSC(20, 0, ecap,   async3,       ecap_clkdev,   0),
	LPSC(21, 0, tptc2,  pll0_sysclk2, शून्य,          LPSC_ALWAYS_ENABLED),
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक da850_psc1_init(काष्ठा device *dev, व्योम __iomem *base)
अणु
	वापस davinci_psc_रेजिस्टर_घड़ीs(dev, da850_psc1_info, 32, base);
पूर्ण

अटल पूर्णांक of_da850_psc1_init(काष्ठा device *dev, व्योम __iomem *base)
अणु
	वापस of_davinci_psc_clk_init(dev, da850_psc1_info, 32, base);
पूर्ण

अटल काष्ठा clk_bulk_data da850_psc1_parent_clks[] = अणु
	अणु .id = "pll0_sysclk2" पूर्ण,
	अणु .id = "pll0_sysclk4" पूर्ण,
	अणु .id = "async3"       पूर्ण,
पूर्ण;

स्थिर काष्ठा davinci_psc_init_data da850_psc1_init_data = अणु
	.parent_clks		= da850_psc1_parent_clks,
	.num_parent_clks	= ARRAY_SIZE(da850_psc1_parent_clks),
	.psc_init		= &da850_psc1_init,
पूर्ण;

स्थिर काष्ठा davinci_psc_init_data of_da850_psc1_init_data = अणु
	.parent_clks		= da850_psc1_parent_clks,
	.num_parent_clks	= ARRAY_SIZE(da850_psc1_parent_clks),
	.psc_init		= &of_da850_psc1_init,
पूर्ण;
