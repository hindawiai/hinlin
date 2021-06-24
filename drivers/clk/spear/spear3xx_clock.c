<शैली गुरु>
/*
 * SPEAr3xx machines घड़ी framework source file
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
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
	#घोषणा GEN_SYNTH2_3_CLK_SHIFT	18
	#घोषणा GEN_SYNTH2_3_CLK_MASK	1

	#घोषणा HCLK_RATIO_SHIFT	10
	#घोषणा HCLK_RATIO_MASK		2
	#घोषणा PCLK_RATIO_SHIFT	8
	#घोषणा PCLK_RATIO_MASK		2

#घोषणा PERIP_CLK_CFG			(misc_base + 0x028)
	/* PERIP_CLK_CFG रेजिस्टर masks */
	#घोषणा UART_CLK_SHIFT		4
	#घोषणा UART_CLK_MASK		1
	#घोषणा FIRDA_CLK_SHIFT		5
	#घोषणा FIRDA_CLK_MASK		2
	#घोषणा GPT0_CLK_SHIFT		8
	#घोषणा GPT1_CLK_SHIFT		11
	#घोषणा GPT2_CLK_SHIFT		12
	#घोषणा GPT_CLK_MASK		1

#घोषणा PERIP1_CLK_ENB			(misc_base + 0x02C)
	/* PERIP1_CLK_ENB रेजिस्टर masks */
	#घोषणा UART_CLK_ENB		3
	#घोषणा SSP_CLK_ENB		5
	#घोषणा I2C_CLK_ENB		7
	#घोषणा JPEG_CLK_ENB		8
	#घोषणा FIRDA_CLK_ENB		10
	#घोषणा GPT1_CLK_ENB		11
	#घोषणा GPT2_CLK_ENB		12
	#घोषणा ADC_CLK_ENB		15
	#घोषणा RTC_CLK_ENB		17
	#घोषणा GPIO_CLK_ENB		18
	#घोषणा DMA_CLK_ENB		19
	#घोषणा SMI_CLK_ENB		21
	#घोषणा GMAC_CLK_ENB		23
	#घोषणा USBD_CLK_ENB		24
	#घोषणा USBH_CLK_ENB		25
	#घोषणा C3_CLK_ENB		31

#घोषणा RAS_CLK_ENB			(misc_base + 0x034)
	#घोषणा RAS_AHB_CLK_ENB		0
	#घोषणा RAS_PLL1_CLK_ENB	1
	#घोषणा RAS_APB_CLK_ENB		2
	#घोषणा RAS_32K_CLK_ENB		3
	#घोषणा RAS_24M_CLK_ENB		4
	#घोषणा RAS_48M_CLK_ENB		5
	#घोषणा RAS_PLL2_CLK_ENB	7
	#घोषणा RAS_SYNT0_CLK_ENB	8
	#घोषणा RAS_SYNT1_CLK_ENB	9
	#घोषणा RAS_SYNT2_CLK_ENB	10
	#घोषणा RAS_SYNT3_CLK_ENB	11

#घोषणा PRSC0_CLK_CFG			(misc_base + 0x044)
#घोषणा PRSC1_CLK_CFG			(misc_base + 0x048)
#घोषणा PRSC2_CLK_CFG			(misc_base + 0x04C)
#घोषणा AMEM_CLK_CFG			(misc_base + 0x050)
	#घोषणा AMEM_CLK_ENB		0

#घोषणा CLCD_CLK_SYNT			(misc_base + 0x05C)
#घोषणा FIRDA_CLK_SYNT			(misc_base + 0x060)
#घोषणा UART_CLK_SYNT			(misc_base + 0x064)
#घोषणा GMAC_CLK_SYNT			(misc_base + 0x068)
#घोषणा GEN0_CLK_SYNT			(misc_base + 0x06C)
#घोषणा GEN1_CLK_SYNT			(misc_base + 0x070)
#घोषणा GEN2_CLK_SYNT			(misc_base + 0x074)
#घोषणा GEN3_CLK_SYNT			(misc_base + 0x078)

/* pll rate configuration table, in ascending order of rates */
अटल काष्ठा pll_rate_tbl pll_rtbl[] = अणु
	अणु.mode = 0, .m = 0x53, .n = 0x0C, .p = 0x1पूर्ण, /* vco 332 & pll 166 MHz */
	अणु.mode = 0, .m = 0x85, .n = 0x0C, .p = 0x1पूर्ण, /* vco 532 & pll 266 MHz */
	अणु.mode = 0, .m = 0xA6, .n = 0x0C, .p = 0x1पूर्ण, /* vco 664 & pll 332 MHz */
पूर्ण;

/* aux rate configuration table, in ascending order of rates */
अटल काष्ठा aux_rate_tbl aux_rtbl[] = अणु
	/* For PLL1 = 332 MHz */
	अणु.xscale = 1, .yscale = 81, .eq = 0पूर्ण, /* 2.049 MHz */
	अणु.xscale = 1, .yscale = 59, .eq = 0पूर्ण, /* 2.822 MHz */
	अणु.xscale = 2, .yscale = 81, .eq = 0पूर्ण, /* 4.098 MHz */
	अणु.xscale = 3, .yscale = 89, .eq = 0पूर्ण, /* 5.644 MHz */
	अणु.xscale = 4, .yscale = 81, .eq = 0पूर्ण, /* 8.197 MHz */
	अणु.xscale = 4, .yscale = 59, .eq = 0पूर्ण, /* 11.254 MHz */
	अणु.xscale = 2, .yscale = 27, .eq = 0पूर्ण, /* 12.296 MHz */
	अणु.xscale = 2, .yscale = 8, .eq = 0पूर्ण, /* 41.5 MHz */
	अणु.xscale = 2, .yscale = 4, .eq = 0पूर्ण, /* 83 MHz */
	अणु.xscale = 1, .yscale = 2, .eq = 1पूर्ण, /* 166 MHz */
पूर्ण;

/* gpt rate configuration table, in ascending order of rates */
अटल काष्ठा gpt_rate_tbl gpt_rtbl[] = अणु
	/* For pll1 = 332 MHz */
	अणु.mscale = 4, .nscale = 0पूर्ण, /* 41.5 MHz */
	अणु.mscale = 2, .nscale = 0पूर्ण, /* 55.3 MHz */
	अणु.mscale = 1, .nscale = 0पूर्ण, /* 83 MHz */
पूर्ण;

/* घड़ी parents */
अटल स्थिर अक्षर *uart0_parents[] = अणु "pll3_clk", "uart_syn_gclk", पूर्ण;
अटल स्थिर अक्षर *firda_parents[] = अणु "pll3_clk", "firda_syn_gclk",
पूर्ण;
अटल स्थिर अक्षर *gpt0_parents[] = अणु "pll3_clk", "gpt0_syn_clk", पूर्ण;
अटल स्थिर अक्षर *gpt1_parents[] = अणु "pll3_clk", "gpt1_syn_clk", पूर्ण;
अटल स्थिर अक्षर *gpt2_parents[] = अणु "pll3_clk", "gpt2_syn_clk", पूर्ण;
अटल स्थिर अक्षर *gen2_3_parents[] = अणु "pll1_clk", "pll2_clk", पूर्ण;
अटल स्थिर अक्षर *ddr_parents[] = अणु "ahb_clk", "ahbmult2_clk", "none",
	"pll2_clk", पूर्ण;

#अगर_घोषित CONFIG_MACH_SPEAR300
अटल व्योम __init spear300_clk_init(व्योम)
अणु
	काष्ठा clk *clk;

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "clcd_clk", "ras_pll3_clk", 0,
			1, 1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "60000000.clcd");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "fsmc_clk", "ras_ahb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "94000000.flash");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "sdhci_clk", "ras_ahb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "70000000.sdhci");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "gpio1_clk", "ras_apb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "a9000000.gpio");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "kbd_clk", "ras_apb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "a0000000.kbd");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spear300_clk_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

/* array of all spear 310 घड़ी lookups */
#अगर_घोषित CONFIG_MACH_SPEAR310
अटल व्योम __init spear310_clk_init(व्योम)
अणु
	काष्ठा clk *clk;

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "emi_clk", "ras_ahb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, "emi", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "fsmc_clk", "ras_ahb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "44000000.flash");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "tdm_clk", "ras_ahb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "tdm");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "uart1_clk", "ras_apb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b2000000.serial");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "uart2_clk", "ras_apb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b2080000.serial");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "uart3_clk", "ras_apb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b2100000.serial");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "uart4_clk", "ras_apb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b2180000.serial");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "uart5_clk", "ras_apb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b2200000.serial");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spear310_clk_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

/* array of all spear 320 घड़ी lookups */
#अगर_घोषित CONFIG_MACH_SPEAR320

#घोषणा SPEAR320_CONTROL_REG		(soc_config_base + 0x0010)
#घोषणा SPEAR320_EXT_CTRL_REG		(soc_config_base + 0x0018)

	#घोषणा SPEAR320_UARTX_PCLK_MASK		0x1
	#घोषणा SPEAR320_UART2_PCLK_SHIFT		8
	#घोषणा SPEAR320_UART3_PCLK_SHIFT		9
	#घोषणा SPEAR320_UART4_PCLK_SHIFT		10
	#घोषणा SPEAR320_UART5_PCLK_SHIFT		11
	#घोषणा SPEAR320_UART6_PCLK_SHIFT		12
	#घोषणा SPEAR320_RS485_PCLK_SHIFT		13
	#घोषणा SMII_PCLK_SHIFT				18
	#घोषणा SMII_PCLK_MASK				2
	#घोषणा SMII_PCLK_VAL_PAD			0x0
	#घोषणा SMII_PCLK_VAL_PLL2			0x1
	#घोषणा SMII_PCLK_VAL_SYNTH0			0x2
	#घोषणा SDHCI_PCLK_SHIFT			15
	#घोषणा SDHCI_PCLK_MASK				1
	#घोषणा SDHCI_PCLK_VAL_48M			0x0
	#घोषणा SDHCI_PCLK_VAL_SYNTH3			0x1
	#घोषणा I2S_REF_PCLK_SHIFT			8
	#घोषणा I2S_REF_PCLK_MASK			1
	#घोषणा I2S_REF_PCLK_SYNTH_VAL			0x1
	#घोषणा I2S_REF_PCLK_PLL2_VAL			0x0
	#घोषणा UART1_PCLK_SHIFT			6
	#घोषणा UART1_PCLK_MASK				1
	#घोषणा SPEAR320_UARTX_PCLK_VAL_SYNTH1		0x0
	#घोषणा SPEAR320_UARTX_PCLK_VAL_APB		0x1

अटल स्थिर अक्षर *i2s_ref_parents[] = अणु "ras_pll2_clk", "ras_syn2_gclk", पूर्ण;
अटल स्थिर अक्षर *sdhci_parents[] = अणु "ras_pll3_clk", "ras_syn3_gclk", पूर्ण;
अटल स्थिर अक्षर *smii0_parents[] = अणु "smii_125m_pad", "ras_pll2_clk",
	"ras_syn0_gclk", पूर्ण;
अटल स्थिर अक्षर *uartx_parents[] = अणु "ras_syn1_gclk", "ras_apb_clk", पूर्ण;

अटल व्योम __init spear320_clk_init(व्योम __iomem *soc_config_base,
				     काष्ठा clk *ras_apb_clk)
अणु
	काष्ठा clk *clk;

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "smii_125m_pad_clk", शून्य,
			0, 125000000);
	clk_रेजिस्टर_clkdev(clk, "smii_125m_pad", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "clcd_clk", "ras_pll3_clk", 0,
			1, 1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "90000000.clcd");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "emi_clk", "ras_ahb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, "emi", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "fsmc_clk", "ras_ahb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "4c000000.flash");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "i2c1_clk", "ras_ahb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "a7000000.i2c");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "pwm_clk", "ras_ahb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "a8000000.pwm");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "ssp1_clk", "ras_ahb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "a5000000.spi");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "ssp2_clk", "ras_ahb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "a6000000.spi");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "can0_clk", "ras_apb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "c_can_platform.0");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "can1_clk", "ras_apb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "c_can_platform.1");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "i2s_clk", "ras_apb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "a9400000.i2s");

	clk = clk_रेजिस्टर_mux(शून्य, "i2s_ref_clk", i2s_ref_parents,
			ARRAY_SIZE(i2s_ref_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR320_CONTROL_REG, I2S_REF_PCLK_SHIFT,
			I2S_REF_PCLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "i2s_ref_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "i2s_sclk", "i2s_ref_clk",
			CLK_SET_RATE_PARENT, 1,
			4);
	clk_रेजिस्टर_clkdev(clk, "i2s_sclk", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "macb1_clk", "ras_apb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, "hclk", "aa000000.eth");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "macb2_clk", "ras_apb_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, "hclk", "ab000000.eth");

	clk = clk_रेजिस्टर_mux(शून्य, "rs485_clk", uartx_parents,
			ARRAY_SIZE(uartx_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR320_EXT_CTRL_REG, SPEAR320_RS485_PCLK_SHIFT,
			SPEAR320_UARTX_PCLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "a9300000.serial");

	clk = clk_रेजिस्टर_mux(शून्य, "sdhci_clk", sdhci_parents,
			ARRAY_SIZE(sdhci_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR320_CONTROL_REG, SDHCI_PCLK_SHIFT, SDHCI_PCLK_MASK,
			0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "70000000.sdhci");

	clk = clk_रेजिस्टर_mux(शून्य, "smii_pclk", smii0_parents,
			ARRAY_SIZE(smii0_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR320_CONTROL_REG, SMII_PCLK_SHIFT, SMII_PCLK_MASK,
			0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "smii_pclk");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "smii_clk", "smii_pclk", 0, 1, 1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "smii");

	clk = clk_रेजिस्टर_mux(शून्य, "uart1_clk", uartx_parents,
			ARRAY_SIZE(uartx_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR320_CONTROL_REG, UART1_PCLK_SHIFT, UART1_PCLK_MASK,
			0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "a3000000.serial");
	/* Enक्रमce ras_apb_clk */
	clk_set_parent(clk, ras_apb_clk);

	clk = clk_रेजिस्टर_mux(शून्य, "uart2_clk", uartx_parents,
			ARRAY_SIZE(uartx_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR320_EXT_CTRL_REG, SPEAR320_UART2_PCLK_SHIFT,
			SPEAR320_UARTX_PCLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "a4000000.serial");
	/* Enक्रमce ras_apb_clk */
	clk_set_parent(clk, ras_apb_clk);

	clk = clk_रेजिस्टर_mux(शून्य, "uart3_clk", uartx_parents,
			ARRAY_SIZE(uartx_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR320_EXT_CTRL_REG, SPEAR320_UART3_PCLK_SHIFT,
			SPEAR320_UARTX_PCLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "a9100000.serial");

	clk = clk_रेजिस्टर_mux(शून्य, "uart4_clk", uartx_parents,
			ARRAY_SIZE(uartx_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR320_EXT_CTRL_REG, SPEAR320_UART4_PCLK_SHIFT,
			SPEAR320_UARTX_PCLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "a9200000.serial");

	clk = clk_रेजिस्टर_mux(शून्य, "uart5_clk", uartx_parents,
			ARRAY_SIZE(uartx_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR320_EXT_CTRL_REG, SPEAR320_UART5_PCLK_SHIFT,
			SPEAR320_UARTX_PCLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "60000000.serial");

	clk = clk_रेजिस्टर_mux(शून्य, "uart6_clk", uartx_parents,
			ARRAY_SIZE(uartx_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR320_EXT_CTRL_REG, SPEAR320_UART6_PCLK_SHIFT,
			SPEAR320_UARTX_PCLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "60100000.serial");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spear320_clk_init(व्योम __iomem *sb, काष्ठा clk *rc) अणु पूर्ण
#पूर्ण_अगर

व्योम __init spear3xx_clk_init(व्योम __iomem *misc_base, व्योम __iomem *soc_config_base)
अणु
	काष्ठा clk *clk, *clk1, *ras_apb_clk;

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "osc_32k_clk", शून्य, 0, 32000);
	clk_रेजिस्टर_clkdev(clk, "osc_32k_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "osc_24m_clk", शून्य, 0, 24000000);
	clk_रेजिस्टर_clkdev(clk, "osc_24m_clk", शून्य);

	/* घड़ी derived from 32 KHz osc clk */
	clk = clk_रेजिस्टर_gate(शून्य, "rtc-spear", "osc_32k_clk", 0,
			PERIP1_CLK_ENB, RTC_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "fc900000.rtc");

	/* घड़ी derived from 24 MHz osc clk */
	clk = clk_रेजिस्टर_fixed_rate(शून्य, "pll3_clk", "osc_24m_clk", 0,
			48000000);
	clk_रेजिस्टर_clkdev(clk, "pll3_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "wdt_clk", "osc_24m_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, शून्य, "fc880000.wdt");

	clk = clk_रेजिस्टर_vco_pll("vco1_clk", "pll1_clk", शून्य,
			"osc_24m_clk", 0, PLL1_CTR, PLL1_FRQ, pll_rtbl,
			ARRAY_SIZE(pll_rtbl), &_lock, &clk1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "vco1_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "pll1_clk", शून्य);

	clk = clk_रेजिस्टर_vco_pll("vco2_clk", "pll2_clk", शून्य,
			"osc_24m_clk", 0, PLL2_CTR, PLL2_FRQ, pll_rtbl,
			ARRAY_SIZE(pll_rtbl), &_lock, &clk1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "vco2_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "pll2_clk", शून्य);

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

	clk = clk_रेजिस्टर_mux(शून्य, "uart0_mclk", uart0_parents,
			ARRAY_SIZE(uart0_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			PERIP_CLK_CFG, UART_CLK_SHIFT, UART_CLK_MASK, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "uart0_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "uart0", "uart0_mclk",
			CLK_SET_RATE_PARENT, PERIP1_CLK_ENB, UART_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0000000.serial");

	clk = clk_रेजिस्टर_aux("firda_syn_clk", "firda_syn_gclk", "pll1_clk", 0,
			FIRDA_CLK_SYNT, शून्य, aux_rtbl, ARRAY_SIZE(aux_rtbl),
			&_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "firda_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "firda_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "firda_mclk", firda_parents,
			ARRAY_SIZE(firda_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			PERIP_CLK_CFG, FIRDA_CLK_SHIFT, FIRDA_CLK_MASK, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "firda_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "firda_clk", "firda_mclk",
			CLK_SET_RATE_PARENT, PERIP1_CLK_ENB, FIRDA_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "firda");

	/* gpt घड़ीs */
	clk_रेजिस्टर_gpt("gpt0_syn_clk", "pll1_clk", 0, PRSC0_CLK_CFG, gpt_rtbl,
			ARRAY_SIZE(gpt_rtbl), &_lock);
	clk = clk_रेजिस्टर_mux(शून्य, "gpt0_clk", gpt0_parents,
			ARRAY_SIZE(gpt0_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			PERIP_CLK_CFG, GPT0_CLK_SHIFT, GPT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "gpt0");

	clk_रेजिस्टर_gpt("gpt1_syn_clk", "pll1_clk", 0, PRSC1_CLK_CFG, gpt_rtbl,
			ARRAY_SIZE(gpt_rtbl), &_lock);
	clk = clk_रेजिस्टर_mux(शून्य, "gpt1_mclk", gpt1_parents,
			ARRAY_SIZE(gpt1_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			PERIP_CLK_CFG, GPT1_CLK_SHIFT, GPT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "gpt1_mclk", शून्य);
	clk = clk_रेजिस्टर_gate(शून्य, "gpt1_clk", "gpt1_mclk",
			CLK_SET_RATE_PARENT, PERIP1_CLK_ENB, GPT1_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "gpt1");

	clk_रेजिस्टर_gpt("gpt2_syn_clk", "pll1_clk", 0, PRSC2_CLK_CFG, gpt_rtbl,
			ARRAY_SIZE(gpt_rtbl), &_lock);
	clk = clk_रेजिस्टर_mux(शून्य, "gpt2_mclk", gpt2_parents,
			ARRAY_SIZE(gpt2_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			PERIP_CLK_CFG, GPT2_CLK_SHIFT, GPT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "gpt2_mclk", शून्य);
	clk = clk_रेजिस्टर_gate(शून्य, "gpt2_clk", "gpt2_mclk",
			CLK_SET_RATE_PARENT, PERIP1_CLK_ENB, GPT2_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "gpt2");

	/* general synths घड़ीs */
	clk = clk_रेजिस्टर_aux("gen0_syn_clk", "gen0_syn_gclk", "pll1_clk",
			0, GEN0_CLK_SYNT, शून्य, aux_rtbl, ARRAY_SIZE(aux_rtbl),
			&_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "gen0_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "gen0_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_aux("gen1_syn_clk", "gen1_syn_gclk", "pll1_clk",
			0, GEN1_CLK_SYNT, शून्य, aux_rtbl, ARRAY_SIZE(aux_rtbl),
			&_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "gen1_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "gen1_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "gen2_3_par_clk", gen2_3_parents,
			ARRAY_SIZE(gen2_3_parents), CLK_SET_RATE_NO_REPARENT,
			CORE_CLK_CFG, GEN_SYNTH2_3_CLK_SHIFT,
			GEN_SYNTH2_3_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "gen2_3_par_clk", शून्य);

	clk = clk_रेजिस्टर_aux("gen2_syn_clk", "gen2_syn_gclk",
			"gen2_3_par_clk", 0, GEN2_CLK_SYNT, शून्य, aux_rtbl,
			ARRAY_SIZE(aux_rtbl), &_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "gen2_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "gen2_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_aux("gen3_syn_clk", "gen3_syn_gclk",
			"gen2_3_par_clk", 0, GEN3_CLK_SYNT, शून्य, aux_rtbl,
			ARRAY_SIZE(aux_rtbl), &_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "gen3_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "gen3_syn_gclk", शून्य);

	/* घड़ी derived from pll3 clk */
	clk = clk_रेजिस्टर_gate(शून्य, "usbh_clk", "pll3_clk", 0, PERIP1_CLK_ENB,
			USBH_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e1800000.ehci");
	clk_रेजिस्टर_clkdev(clk, शून्य, "e1900000.ohci");
	clk_रेजिस्टर_clkdev(clk, शून्य, "e2100000.ohci");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "usbh.0_clk", "usbh_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, "usbh.0_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "usbh.1_clk", "usbh_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, "usbh.1_clk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "usbd_clk", "pll3_clk", 0, PERIP1_CLK_ENB,
			USBD_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e1100000.usbd");

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

	clk = clk_रेजिस्टर_gate(शून्य, "amem_clk", "ahb_clk", 0, AMEM_CLK_CFG,
			AMEM_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "amem_clk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "c3_clk", "ahb_clk", 0, PERIP1_CLK_ENB,
			C3_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "c3_clk");

	clk = clk_रेजिस्टर_gate(शून्य, "dma_clk", "ahb_clk", 0, PERIP1_CLK_ENB,
			DMA_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "fc400000.dma");

	clk = clk_रेजिस्टर_gate(शून्य, "gmac_clk", "ahb_clk", 0, PERIP1_CLK_ENB,
			GMAC_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e0800000.eth");

	clk = clk_रेजिस्टर_gate(शून्य, "i2c0_clk", "ahb_clk", 0, PERIP1_CLK_ENB,
			I2C_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0180000.i2c");

	clk = clk_रेजिस्टर_gate(शून्य, "jpeg_clk", "ahb_clk", 0, PERIP1_CLK_ENB,
			JPEG_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "jpeg");

	clk = clk_रेजिस्टर_gate(शून्य, "smi_clk", "ahb_clk", 0, PERIP1_CLK_ENB,
			SMI_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "fc000000.flash");

	/* घड़ी derived from apb clk */
	clk = clk_रेजिस्टर_gate(शून्य, "adc_clk", "apb_clk", 0, PERIP1_CLK_ENB,
			ADC_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0080000.adc");

	clk = clk_रेजिस्टर_gate(शून्य, "gpio0_clk", "apb_clk", 0, PERIP1_CLK_ENB,
			GPIO_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "fc980000.gpio");

	clk = clk_रेजिस्टर_gate(शून्य, "ssp0_clk", "apb_clk", 0, PERIP1_CLK_ENB,
			SSP_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0100000.spi");

	/* RAS clk enable */
	clk = clk_रेजिस्टर_gate(शून्य, "ras_ahb_clk", "ahb_clk", 0, RAS_CLK_ENB,
			RAS_AHB_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "ras_ahb_clk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "ras_apb_clk", "apb_clk", 0, RAS_CLK_ENB,
			RAS_APB_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "ras_apb_clk", शून्य);
	ras_apb_clk = clk;

	clk = clk_रेजिस्टर_gate(शून्य, "ras_32k_clk", "osc_32k_clk", 0,
			RAS_CLK_ENB, RAS_32K_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "ras_32k_clk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "ras_24m_clk", "osc_24m_clk", 0,
			RAS_CLK_ENB, RAS_24M_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "ras_24m_clk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "ras_pll1_clk", "pll1_clk", 0,
			RAS_CLK_ENB, RAS_PLL1_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "ras_pll1_clk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "ras_pll2_clk", "pll2_clk", 0,
			RAS_CLK_ENB, RAS_PLL2_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "ras_pll2_clk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "ras_pll3_clk", "pll3_clk", 0,
			RAS_CLK_ENB, RAS_48M_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "ras_pll3_clk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "ras_syn0_gclk", "gen0_syn_gclk",
			CLK_SET_RATE_PARENT, RAS_CLK_ENB, RAS_SYNT0_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "ras_syn0_gclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "ras_syn1_gclk", "gen1_syn_gclk",
			CLK_SET_RATE_PARENT, RAS_CLK_ENB, RAS_SYNT1_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "ras_syn1_gclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "ras_syn2_gclk", "gen2_syn_gclk",
			CLK_SET_RATE_PARENT, RAS_CLK_ENB, RAS_SYNT2_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "ras_syn2_gclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "ras_syn3_gclk", "gen3_syn_gclk",
			CLK_SET_RATE_PARENT, RAS_CLK_ENB, RAS_SYNT3_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "ras_syn3_gclk", शून्य);

	अगर (of_machine_is_compatible("st,spear300"))
		spear300_clk_init();
	अन्यथा अगर (of_machine_is_compatible("st,spear310"))
		spear310_clk_init();
	अन्यथा अगर (of_machine_is_compatible("st,spear320"))
		spear320_clk_init(soc_config_base, ras_apb_clk);
पूर्ण
