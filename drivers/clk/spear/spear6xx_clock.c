<शैली गुरु>
/*
 * SPEAr6xx machines घड़ी framework source file
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clkdev.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock_types.h>
#समावेश "clk.h"

अटल DEFINE_SPINLOCK(_lock);

#घोषणा PLL1_CTR			(misc_base + 0x008)
#घोषणा PLL1_FRQ			(misc_base + 0x00C)
#घोषणा PLL2_CTR			(misc_base + 0x014)
#घोषणा PLL2_FRQ			(misc_base + 0x018)
#घोषणा PLL_CLK_CFG			(misc_base + 0x020)
	/* PLL_CLK_CFG रेजिस्टर masks */
	#घोषणा MCTR_CLK_SHIFT		28
	#घोषणा MCTR_CLK_MASK		3

#घोषणा CORE_CLK_CFG			(misc_base + 0x024)
	/* CORE CLK CFG रेजिस्टर masks */
	#घोषणा HCLK_RATIO_SHIFT	10
	#घोषणा HCLK_RATIO_MASK		2
	#घोषणा PCLK_RATIO_SHIFT	8
	#घोषणा PCLK_RATIO_MASK		2

#घोषणा PERIP_CLK_CFG			(misc_base + 0x028)
	/* PERIP_CLK_CFG रेजिस्टर masks */
	#घोषणा CLCD_CLK_SHIFT		2
	#घोषणा CLCD_CLK_MASK		2
	#घोषणा UART_CLK_SHIFT		4
	#घोषणा UART_CLK_MASK		1
	#घोषणा FIRDA_CLK_SHIFT		5
	#घोषणा FIRDA_CLK_MASK		2
	#घोषणा GPT0_CLK_SHIFT		8
	#घोषणा GPT1_CLK_SHIFT		10
	#घोषणा GPT2_CLK_SHIFT		11
	#घोषणा GPT3_CLK_SHIFT		12
	#घोषणा GPT_CLK_MASK		1

#घोषणा PERIP1_CLK_ENB			(misc_base + 0x02C)
	/* PERIP1_CLK_ENB रेजिस्टर masks */
	#घोषणा UART0_CLK_ENB		3
	#घोषणा UART1_CLK_ENB		4
	#घोषणा SSP0_CLK_ENB		5
	#घोषणा SSP1_CLK_ENB		6
	#घोषणा I2C_CLK_ENB		7
	#घोषणा JPEG_CLK_ENB		8
	#घोषणा FSMC_CLK_ENB		9
	#घोषणा FIRDA_CLK_ENB		10
	#घोषणा GPT2_CLK_ENB		11
	#घोषणा GPT3_CLK_ENB		12
	#घोषणा GPIO2_CLK_ENB		13
	#घोषणा SSP2_CLK_ENB		14
	#घोषणा ADC_CLK_ENB		15
	#घोषणा GPT1_CLK_ENB		11
	#घोषणा RTC_CLK_ENB		17
	#घोषणा GPIO1_CLK_ENB		18
	#घोषणा DMA_CLK_ENB		19
	#घोषणा SMI_CLK_ENB		21
	#घोषणा CLCD_CLK_ENB		22
	#घोषणा GMAC_CLK_ENB		23
	#घोषणा USBD_CLK_ENB		24
	#घोषणा USBH0_CLK_ENB		25
	#घोषणा USBH1_CLK_ENB		26

#घोषणा PRSC0_CLK_CFG			(misc_base + 0x044)
#घोषणा PRSC1_CLK_CFG			(misc_base + 0x048)
#घोषणा PRSC2_CLK_CFG			(misc_base + 0x04C)

#घोषणा CLCD_CLK_SYNT			(misc_base + 0x05C)
#घोषणा FIRDA_CLK_SYNT			(misc_base + 0x060)
#घोषणा UART_CLK_SYNT			(misc_base + 0x064)

/* vco rate configuration table, in ascending order of rates */
अटल काष्ठा pll_rate_tbl pll_rtbl[] = अणु
	अणु.mode = 0, .m = 0x53, .n = 0x0F, .p = 0x1पूर्ण, /* vco 332 & pll 166 MHz */
	अणु.mode = 0, .m = 0x85, .n = 0x0F, .p = 0x1पूर्ण, /* vco 532 & pll 266 MHz */
	अणु.mode = 0, .m = 0xA6, .n = 0x0F, .p = 0x1पूर्ण, /* vco 664 & pll 332 MHz */
पूर्ण;

/* aux rate configuration table, in ascending order of rates */
अटल काष्ठा aux_rate_tbl aux_rtbl[] = अणु
	/* For PLL1 = 332 MHz */
	अणु.xscale = 2, .yscale = 27, .eq = 0पूर्ण, /* 12.296 MHz */
	अणु.xscale = 2, .yscale = 8, .eq = 0पूर्ण, /* 41.5 MHz */
	अणु.xscale = 2, .yscale = 4, .eq = 0पूर्ण, /* 83 MHz */
	अणु.xscale = 1, .yscale = 2, .eq = 1पूर्ण, /* 166 MHz */
पूर्ण;

अटल स्थिर अक्षर *clcd_parents[] = अणु "pll3_clk", "clcd_syn_gclk", पूर्ण;
अटल स्थिर अक्षर *firda_parents[] = अणु "pll3_clk", "firda_syn_gclk", पूर्ण;
अटल स्थिर अक्षर *uart_parents[] = अणु "pll3_clk", "uart_syn_gclk", पूर्ण;
अटल स्थिर अक्षर *gpt0_1_parents[] = अणु "pll3_clk", "gpt0_1_syn_clk", पूर्ण;
अटल स्थिर अक्षर *gpt2_parents[] = अणु "pll3_clk", "gpt2_syn_clk", पूर्ण;
अटल स्थिर अक्षर *gpt3_parents[] = अणु "pll3_clk", "gpt3_syn_clk", पूर्ण;
अटल स्थिर अक्षर *ddr_parents[] = अणु "ahb_clk", "ahbmult2_clk", "none",
	"pll2_clk", पूर्ण;

/* gpt rate configuration table, in ascending order of rates */
अटल काष्ठा gpt_rate_tbl gpt_rtbl[] = अणु
	/* For pll1 = 332 MHz */
	अणु.mscale = 4, .nscale = 0पूर्ण, /* 41.5 MHz */
	अणु.mscale = 2, .nscale = 0पूर्ण, /* 55.3 MHz */
	अणु.mscale = 1, .nscale = 0पूर्ण, /* 83 MHz */
पूर्ण;

व्योम __init spear6xx_clk_init(व्योम __iomem *misc_base)
अणु
	काष्ठा clk *clk, *clk1;

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "osc_32k_clk", शून्य, 0, 32000);
	clk_रेजिस्टर_clkdev(clk, "osc_32k_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "osc_30m_clk", शून्य, 0, 30000000);
	clk_रेजिस्टर_clkdev(clk, "osc_30m_clk", शून्य);

	/* घड़ी derived from 32 KHz osc clk */
	clk = clk_रेजिस्टर_gate(शून्य, "rtc_spear", "osc_32k_clk", 0,
			PERIP1_CLK_ENB, RTC_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "rtc-spear");

	/* घड़ी derived from 30 MHz osc clk */
	clk = clk_रेजिस्टर_fixed_rate(शून्य, "pll3_clk", "osc_24m_clk", 0,
			48000000);
	clk_रेजिस्टर_clkdev(clk, "pll3_clk", शून्य);

	clk = clk_रेजिस्टर_vco_pll("vco1_clk", "pll1_clk", शून्य, "osc_30m_clk",
			0, PLL1_CTR, PLL1_FRQ, pll_rtbl, ARRAY_SIZE(pll_rtbl),
			&_lock, &clk1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "vco1_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "pll1_clk", शून्य);

	clk = clk_रेजिस्टर_vco_pll("vco2_clk", "pll2_clk", शून्य, "osc_30m_clk",
			0, PLL2_CTR, PLL2_FRQ, pll_rtbl, ARRAY_SIZE(pll_rtbl),
			&_lock, &clk1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "vco2_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "pll2_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "wdt_clk", "osc_30m_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "fc880000.wdt");

	/* घड़ी derived from pll1 clk */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "cpu_clk", "pll1_clk",
			CLK_SET_RATE_PARENT, 1, 1);
	clk_रेजिस्टर_clkdev(clk, "cpu_clk", शून्य);

	clk = clk_रेजिस्टर_भागider(शून्य, "ahb_clk", "pll1_clk",
			CLK_SET_RATE_PARENT, CORE_CLK_CFG, HCLK_RATIO_SHIFT,
			HCLK_RATIO_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "ahb_clk", शून्य);

	clk = clk_रेजिस्टर_aux("uart_syn_clk", "uart_syn_gclk", "pll1_clk", 0,
			UART_CLK_SYNT, शून्य, aux_rtbl, ARRAY_SIZE(aux_rtbl),
			&_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "uart_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "uart_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "uart_mclk", uart_parents,
			ARRAY_SIZE(uart_parents), CLK_SET_RATE_NO_REPARENT,
			PERIP_CLK_CFG, UART_CLK_SHIFT, UART_CLK_MASK, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "uart_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "uart0", "uart_mclk", 0, PERIP1_CLK_ENB,
			UART0_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0000000.serial");

	clk = clk_रेजिस्टर_gate(शून्य, "uart1", "uart_mclk", 0, PERIP1_CLK_ENB,
			UART1_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0080000.serial");

	clk = clk_रेजिस्टर_aux("firda_syn_clk", "firda_syn_gclk", "pll1_clk",
			0, FIRDA_CLK_SYNT, शून्य, aux_rtbl, ARRAY_SIZE(aux_rtbl),
			&_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "firda_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "firda_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "firda_mclk", firda_parents,
			ARRAY_SIZE(firda_parents), CLK_SET_RATE_NO_REPARENT,
			PERIP_CLK_CFG, FIRDA_CLK_SHIFT, FIRDA_CLK_MASK, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "firda_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "firda_clk", "firda_mclk", 0,
			PERIP1_CLK_ENB, FIRDA_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "firda");

	clk = clk_रेजिस्टर_aux("clcd_syn_clk", "clcd_syn_gclk", "pll1_clk",
			0, CLCD_CLK_SYNT, शून्य, aux_rtbl, ARRAY_SIZE(aux_rtbl),
			&_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "clcd_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "clcd_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "clcd_mclk", clcd_parents,
			ARRAY_SIZE(clcd_parents), CLK_SET_RATE_NO_REPARENT,
			PERIP_CLK_CFG, CLCD_CLK_SHIFT, CLCD_CLK_MASK, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "clcd_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "clcd_clk", "clcd_mclk", 0,
			PERIP1_CLK_ENB, CLCD_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "clcd");

	/* gpt घड़ीs */
	clk = clk_रेजिस्टर_gpt("gpt0_1_syn_clk", "pll1_clk", 0, PRSC0_CLK_CFG,
			gpt_rtbl, ARRAY_SIZE(gpt_rtbl), &_lock);
	clk_रेजिस्टर_clkdev(clk, "gpt0_1_syn_clk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "gpt0_mclk", gpt0_1_parents,
			ARRAY_SIZE(gpt0_1_parents), CLK_SET_RATE_NO_REPARENT,
			PERIP_CLK_CFG, GPT0_CLK_SHIFT, GPT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "gpt0");

	clk = clk_रेजिस्टर_mux(शून्य, "gpt1_mclk", gpt0_1_parents,
			ARRAY_SIZE(gpt0_1_parents), CLK_SET_RATE_NO_REPARENT,
			PERIP_CLK_CFG, GPT1_CLK_SHIFT, GPT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "gpt1_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "gpt1_clk", "gpt1_mclk", 0,
			PERIP1_CLK_ENB, GPT1_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "gpt1");

	clk = clk_रेजिस्टर_gpt("gpt2_syn_clk", "pll1_clk", 0, PRSC1_CLK_CFG,
			gpt_rtbl, ARRAY_SIZE(gpt_rtbl), &_lock);
	clk_रेजिस्टर_clkdev(clk, "gpt2_syn_clk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "gpt2_mclk", gpt2_parents,
			ARRAY_SIZE(gpt2_parents), CLK_SET_RATE_NO_REPARENT,
			PERIP_CLK_CFG, GPT2_CLK_SHIFT, GPT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "gpt2_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "gpt2_clk", "gpt2_mclk", 0,
			PERIP1_CLK_ENB, GPT2_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "gpt2");

	clk = clk_रेजिस्टर_gpt("gpt3_syn_clk", "pll1_clk", 0, PRSC2_CLK_CFG,
			gpt_rtbl, ARRAY_SIZE(gpt_rtbl), &_lock);
	clk_रेजिस्टर_clkdev(clk, "gpt3_syn_clk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "gpt3_mclk", gpt3_parents,
			ARRAY_SIZE(gpt3_parents), CLK_SET_RATE_NO_REPARENT,
			PERIP_CLK_CFG, GPT3_CLK_SHIFT, GPT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "gpt3_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "gpt3_clk", "gpt3_mclk", 0,
			PERIP1_CLK_ENB, GPT3_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "gpt3");

	/* घड़ी derived from pll3 clk */
	clk = clk_रेजिस्टर_gate(शून्य, "usbh0_clk", "pll3_clk", 0,
			PERIP1_CLK_ENB, USBH0_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e1800000.ehci");
	clk_रेजिस्टर_clkdev(clk, शून्य, "e1900000.ohci");

	clk = clk_रेजिस्टर_gate(शून्य, "usbh1_clk", "pll3_clk", 0,
			PERIP1_CLK_ENB, USBH1_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e2000000.ehci");
	clk_रेजिस्टर_clkdev(clk, शून्य, "e2100000.ohci");

	clk = clk_रेजिस्टर_gate(शून्य, "usbd_clk", "pll3_clk", 0, PERIP1_CLK_ENB,
			USBD_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "designware_udc");

	/* घड़ी derived from ahb clk */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "ahbmult2_clk", "ahb_clk", 0, 2,
			1);
	clk_रेजिस्टर_clkdev(clk, "ahbmult2_clk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "ddr_clk", ddr_parents,
			ARRAY_SIZE(ddr_parents), CLK_SET_RATE_NO_REPARENT,
			PLL_CLK_CFG, MCTR_CLK_SHIFT, MCTR_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "ddr_clk", शून्य);

	clk = clk_रेजिस्टर_भागider(शून्य, "apb_clk", "ahb_clk",
			CLK_SET_RATE_PARENT, CORE_CLK_CFG, PCLK_RATIO_SHIFT,
			PCLK_RATIO_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "apb_clk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "dma_clk", "ahb_clk", 0, PERIP1_CLK_ENB,
			DMA_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "fc400000.dma");

	clk = clk_रेजिस्टर_gate(शून्य, "fsmc_clk", "ahb_clk", 0, PERIP1_CLK_ENB,
			FSMC_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d1800000.flash");

	clk = clk_रेजिस्टर_gate(शून्य, "gmac_clk", "ahb_clk", 0, PERIP1_CLK_ENB,
			GMAC_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e0800000.ethernet");

	clk = clk_रेजिस्टर_gate(शून्य, "i2c_clk", "ahb_clk", 0, PERIP1_CLK_ENB,
			I2C_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0200000.i2c");

	clk = clk_रेजिस्टर_gate(शून्य, "jpeg_clk", "ahb_clk", 0, PERIP1_CLK_ENB,
			JPEG_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "jpeg");

	clk = clk_रेजिस्टर_gate(शून्य, "smi_clk", "ahb_clk", 0, PERIP1_CLK_ENB,
			SMI_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "fc000000.flash");

	/* घड़ी derived from apb clk */
	clk = clk_रेजिस्टर_gate(शून्य, "adc_clk", "apb_clk", 0, PERIP1_CLK_ENB,
			ADC_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d820b000.adc");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "gpio0_clk", "apb_clk", 0, 1, 1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "f0100000.gpio");

	clk = clk_रेजिस्टर_gate(शून्य, "gpio1_clk", "apb_clk", 0, PERIP1_CLK_ENB,
			GPIO1_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "fc980000.gpio");

	clk = clk_रेजिस्टर_gate(शून्य, "gpio2_clk", "apb_clk", 0, PERIP1_CLK_ENB,
			GPIO2_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d8100000.gpio");

	clk = clk_रेजिस्टर_gate(शून्य, "ssp0_clk", "apb_clk", 0, PERIP1_CLK_ENB,
			SSP0_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "ssp-pl022.0");

	clk = clk_रेजिस्टर_gate(शून्य, "ssp1_clk", "apb_clk", 0, PERIP1_CLK_ENB,
			SSP1_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "ssp-pl022.1");

	clk = clk_रेजिस्टर_gate(शून्य, "ssp2_clk", "apb_clk", 0, PERIP1_CLK_ENB,
			SSP2_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "ssp-pl022.2");
पूर्ण
