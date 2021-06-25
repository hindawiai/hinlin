<शैली गुरु>
/*
 * arch/arm/mach-spear13xx/spear1340_घड़ी.c
 *
 * SPEAr1340 machine घड़ी framework source file
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clkdev.h>
#समावेश <linux/clk/spear.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/spinlock_types.h>
#समावेश "clk.h"

/* Clock Configuration Registers */
#घोषणा SPEAR1340_SYS_CLK_CTRL			(misc_base + 0x200)
	#घोषणा SPEAR1340_HCLK_SRC_SEL_SHIFT	27
	#घोषणा SPEAR1340_HCLK_SRC_SEL_MASK	1
	#घोषणा SPEAR1340_SCLK_SRC_SEL_SHIFT	23
	#घोषणा SPEAR1340_SCLK_SRC_SEL_MASK	3

/* PLL related रेजिस्टरs and bit values */
#घोषणा SPEAR1340_PLL_CFG			(misc_base + 0x210)
	/* PLL_CFG bit values */
	#घोषणा SPEAR1340_CLCD_SYNT_CLK_MASK		1
	#घोषणा SPEAR1340_CLCD_SYNT_CLK_SHIFT		31
	#घोषणा SPEAR1340_GEN_SYNT2_3_CLK_SHIFT		29
	#घोषणा SPEAR1340_GEN_SYNT_CLK_MASK		2
	#घोषणा SPEAR1340_GEN_SYNT0_1_CLK_SHIFT		27
	#घोषणा SPEAR1340_PLL_CLK_MASK			2
	#घोषणा SPEAR1340_PLL3_CLK_SHIFT		24
	#घोषणा SPEAR1340_PLL2_CLK_SHIFT		22
	#घोषणा SPEAR1340_PLL1_CLK_SHIFT		20

#घोषणा SPEAR1340_PLL1_CTR			(misc_base + 0x214)
#घोषणा SPEAR1340_PLL1_FRQ			(misc_base + 0x218)
#घोषणा SPEAR1340_PLL2_CTR			(misc_base + 0x220)
#घोषणा SPEAR1340_PLL2_FRQ			(misc_base + 0x224)
#घोषणा SPEAR1340_PLL3_CTR			(misc_base + 0x22C)
#घोषणा SPEAR1340_PLL3_FRQ			(misc_base + 0x230)
#घोषणा SPEAR1340_PLL4_CTR			(misc_base + 0x238)
#घोषणा SPEAR1340_PLL4_FRQ			(misc_base + 0x23C)
#घोषणा SPEAR1340_PERIP_CLK_CFG			(misc_base + 0x244)
	/* PERIP_CLK_CFG bit values */
	#घोषणा SPEAR1340_SPDIF_CLK_MASK		1
	#घोषणा SPEAR1340_SPDIF_OUT_CLK_SHIFT		15
	#घोषणा SPEAR1340_SPDIF_IN_CLK_SHIFT		14
	#घोषणा SPEAR1340_GPT3_CLK_SHIFT		13
	#घोषणा SPEAR1340_GPT2_CLK_SHIFT		12
	#घोषणा SPEAR1340_GPT_CLK_MASK			1
	#घोषणा SPEAR1340_GPT1_CLK_SHIFT		9
	#घोषणा SPEAR1340_GPT0_CLK_SHIFT		8
	#घोषणा SPEAR1340_UART_CLK_MASK			2
	#घोषणा SPEAR1340_UART1_CLK_SHIFT		6
	#घोषणा SPEAR1340_UART0_CLK_SHIFT		4
	#घोषणा SPEAR1340_CLCD_CLK_MASK			2
	#घोषणा SPEAR1340_CLCD_CLK_SHIFT		2
	#घोषणा SPEAR1340_C3_CLK_MASK			1
	#घोषणा SPEAR1340_C3_CLK_SHIFT			1

#घोषणा SPEAR1340_GMAC_CLK_CFG			(misc_base + 0x248)
	#घोषणा SPEAR1340_GMAC_PHY_CLK_MASK		1
	#घोषणा SPEAR1340_GMAC_PHY_CLK_SHIFT		2
	#घोषणा SPEAR1340_GMAC_PHY_INPUT_CLK_MASK	2
	#घोषणा SPEAR1340_GMAC_PHY_INPUT_CLK_SHIFT	0

#घोषणा SPEAR1340_I2S_CLK_CFG			(misc_base + 0x24C)
	/* I2S_CLK_CFG रेजिस्टर mask */
	#घोषणा SPEAR1340_I2S_SCLK_X_MASK		0x1F
	#घोषणा SPEAR1340_I2S_SCLK_X_SHIFT		27
	#घोषणा SPEAR1340_I2S_SCLK_Y_MASK		0x1F
	#घोषणा SPEAR1340_I2S_SCLK_Y_SHIFT		22
	#घोषणा SPEAR1340_I2S_SCLK_EQ_SEL_SHIFT		21
	#घोषणा SPEAR1340_I2S_SCLK_SYNTH_ENB		20
	#घोषणा SPEAR1340_I2S_PRS1_CLK_X_MASK		0xFF
	#घोषणा SPEAR1340_I2S_PRS1_CLK_X_SHIFT		12
	#घोषणा SPEAR1340_I2S_PRS1_CLK_Y_MASK		0xFF
	#घोषणा SPEAR1340_I2S_PRS1_CLK_Y_SHIFT		4
	#घोषणा SPEAR1340_I2S_PRS1_EQ_SEL_SHIFT		3
	#घोषणा SPEAR1340_I2S_REF_SEL_MASK		1
	#घोषणा SPEAR1340_I2S_REF_SHIFT			2
	#घोषणा SPEAR1340_I2S_SRC_CLK_MASK		2
	#घोषणा SPEAR1340_I2S_SRC_CLK_SHIFT		0

#घोषणा SPEAR1340_C3_CLK_SYNT			(misc_base + 0x250)
#घोषणा SPEAR1340_UART0_CLK_SYNT		(misc_base + 0x254)
#घोषणा SPEAR1340_UART1_CLK_SYNT		(misc_base + 0x258)
#घोषणा SPEAR1340_GMAC_CLK_SYNT			(misc_base + 0x25C)
#घोषणा SPEAR1340_SDHCI_CLK_SYNT		(misc_base + 0x260)
#घोषणा SPEAR1340_CFXD_CLK_SYNT			(misc_base + 0x264)
#घोषणा SPEAR1340_ADC_CLK_SYNT			(misc_base + 0x270)
#घोषणा SPEAR1340_AMBA_CLK_SYNT			(misc_base + 0x274)
#घोषणा SPEAR1340_CLCD_CLK_SYNT			(misc_base + 0x27C)
#घोषणा SPEAR1340_SYS_CLK_SYNT			(misc_base + 0x284)
#घोषणा SPEAR1340_GEN_CLK_SYNT0			(misc_base + 0x28C)
#घोषणा SPEAR1340_GEN_CLK_SYNT1			(misc_base + 0x294)
#घोषणा SPEAR1340_GEN_CLK_SYNT2			(misc_base + 0x29C)
#घोषणा SPEAR1340_GEN_CLK_SYNT3			(misc_base + 0x304)
#घोषणा SPEAR1340_PERIP1_CLK_ENB		(misc_base + 0x30C)
	#घोषणा SPEAR1340_RTC_CLK_ENB			31
	#घोषणा SPEAR1340_ADC_CLK_ENB			30
	#घोषणा SPEAR1340_C3_CLK_ENB			29
	#घोषणा SPEAR1340_CLCD_CLK_ENB			27
	#घोषणा SPEAR1340_DMA_CLK_ENB			25
	#घोषणा SPEAR1340_GPIO1_CLK_ENB			24
	#घोषणा SPEAR1340_GPIO0_CLK_ENB			23
	#घोषणा SPEAR1340_GPT1_CLK_ENB			22
	#घोषणा SPEAR1340_GPT0_CLK_ENB			21
	#घोषणा SPEAR1340_I2S_PLAY_CLK_ENB		20
	#घोषणा SPEAR1340_I2S_REC_CLK_ENB		19
	#घोषणा SPEAR1340_I2C0_CLK_ENB			18
	#घोषणा SPEAR1340_SSP_CLK_ENB			17
	#घोषणा SPEAR1340_UART0_CLK_ENB			15
	#घोषणा SPEAR1340_PCIE_SATA_CLK_ENB		12
	#घोषणा SPEAR1340_UOC_CLK_ENB			11
	#घोषणा SPEAR1340_UHC1_CLK_ENB			10
	#घोषणा SPEAR1340_UHC0_CLK_ENB			9
	#घोषणा SPEAR1340_GMAC_CLK_ENB			8
	#घोषणा SPEAR1340_CFXD_CLK_ENB			7
	#घोषणा SPEAR1340_SDHCI_CLK_ENB			6
	#घोषणा SPEAR1340_SMI_CLK_ENB			5
	#घोषणा SPEAR1340_FSMC_CLK_ENB			4
	#घोषणा SPEAR1340_SYSRAM0_CLK_ENB		3
	#घोषणा SPEAR1340_SYSRAM1_CLK_ENB		2
	#घोषणा SPEAR1340_SYSROM_CLK_ENB		1
	#घोषणा SPEAR1340_BUS_CLK_ENB			0

#घोषणा SPEAR1340_PERIP2_CLK_ENB		(misc_base + 0x310)
	#घोषणा SPEAR1340_THSENS_CLK_ENB		8
	#घोषणा SPEAR1340_I2S_REF_PAD_CLK_ENB		7
	#घोषणा SPEAR1340_ACP_CLK_ENB			6
	#घोषणा SPEAR1340_GPT3_CLK_ENB			5
	#घोषणा SPEAR1340_GPT2_CLK_ENB			4
	#घोषणा SPEAR1340_KBD_CLK_ENB			3
	#घोषणा SPEAR1340_CPU_DBG_CLK_ENB		2
	#घोषणा SPEAR1340_DDR_CORE_CLK_ENB		1
	#घोषणा SPEAR1340_DDR_CTRL_CLK_ENB		0

#घोषणा SPEAR1340_PERIP3_CLK_ENB		(misc_base + 0x314)
	#घोषणा SPEAR1340_PLGPIO_CLK_ENB		18
	#घोषणा SPEAR1340_VIDEO_DEC_CLK_ENB		16
	#घोषणा SPEAR1340_VIDEO_ENC_CLK_ENB		15
	#घोषणा SPEAR1340_SPDIF_OUT_CLK_ENB		13
	#घोषणा SPEAR1340_SPDIF_IN_CLK_ENB		12
	#घोषणा SPEAR1340_VIDEO_IN_CLK_ENB		11
	#घोषणा SPEAR1340_CAM0_CLK_ENB			10
	#घोषणा SPEAR1340_CAM1_CLK_ENB			9
	#घोषणा SPEAR1340_CAM2_CLK_ENB			8
	#घोषणा SPEAR1340_CAM3_CLK_ENB			7
	#घोषणा SPEAR1340_MALI_CLK_ENB			6
	#घोषणा SPEAR1340_CEC0_CLK_ENB			5
	#घोषणा SPEAR1340_CEC1_CLK_ENB			4
	#घोषणा SPEAR1340_PWM_CLK_ENB			3
	#घोषणा SPEAR1340_I2C1_CLK_ENB			2
	#घोषणा SPEAR1340_UART1_CLK_ENB			1

अटल DEFINE_SPINLOCK(_lock);

/* pll rate configuration table, in ascending order of rates */
अटल काष्ठा pll_rate_tbl pll_rtbl[] = अणु
	/* PCLK 24MHz */
	अणु.mode = 0, .m = 0x83, .n = 0x04, .p = 0x5पूर्ण, /* vco 1572, pll 49.125 MHz */
	अणु.mode = 0, .m = 0x7D, .n = 0x06, .p = 0x3पूर्ण, /* vco 1000, pll 125 MHz */
	अणु.mode = 0, .m = 0x64, .n = 0x06, .p = 0x1पूर्ण, /* vco 800, pll 400 MHz */
	अणु.mode = 0, .m = 0x7D, .n = 0x06, .p = 0x1पूर्ण, /* vco 1000, pll 500 MHz */
	अणु.mode = 0, .m = 0xA6, .n = 0x06, .p = 0x1पूर्ण, /* vco 1328, pll 664 MHz */
	अणु.mode = 0, .m = 0xC8, .n = 0x06, .p = 0x1पूर्ण, /* vco 1600, pll 800 MHz */
	अणु.mode = 0, .m = 0x7D, .n = 0x06, .p = 0x0पूर्ण, /* vco 1, pll 1 GHz */
	अणु.mode = 0, .m = 0x96, .n = 0x06, .p = 0x0पूर्ण, /* vco 1200, pll 1200 MHz */
पूर्ण;

/* vco-pll4 rate configuration table, in ascending order of rates */
अटल काष्ठा pll_rate_tbl pll4_rtbl[] = अणु
	अणु.mode = 0, .m = 0x7D, .n = 0x06, .p = 0x2पूर्ण, /* vco 1000, pll 250 MHz */
	अणु.mode = 0, .m = 0xA6, .n = 0x06, .p = 0x2पूर्ण, /* vco 1328, pll 332 MHz */
	अणु.mode = 0, .m = 0xC8, .n = 0x06, .p = 0x2पूर्ण, /* vco 1600, pll 400 MHz */
	अणु.mode = 0, .m = 0x7D, .n = 0x06, .p = 0x0पूर्ण, /* vco 1, pll 1 GHz */
पूर्ण;

/*
 * All below entries generate 166 MHz क्रम
 * dअगरferent values of vco1भाग2
 */
अटल काष्ठा frac_rate_tbl amba_synth_rtbl[] = अणु
	अणु.भाग = 0x073A8पूर्ण, /* क्रम vco1भाग2 = 600 MHz */
	अणु.भाग = 0x06062पूर्ण, /* क्रम vco1भाग2 = 500 MHz */
	अणु.भाग = 0x04D1Bपूर्ण, /* क्रम vco1भाग2 = 400 MHz */
	अणु.भाग = 0x04000पूर्ण, /* क्रम vco1भाग2 = 332 MHz */
	अणु.भाग = 0x03031पूर्ण, /* क्रम vco1भाग2 = 250 MHz */
	अणु.भाग = 0x0268Dपूर्ण, /* क्रम vco1भाग2 = 200 MHz */
पूर्ण;

/*
 * Synthesizer Clock derived from vcoभाग2. This घड़ी is one of the
 * possible घड़ीs to feed cpu directly.
 * We can program this synthesizer to make cpu run on dअगरferent घड़ी
 * frequencies.
 * Following table provides configuration values to let cpu run on 200,
 * 250, 332, 400 or 500 MHz considering dअगरferent possibilites of input
 * (vco1भाग2) घड़ी.
 *
 * --------------------------------------------------------------------
 * vco1भाग2(Mhz)	fout(Mhz)	cpuclk = fout/2		भाग
 * --------------------------------------------------------------------
 * 400			200		100			0x04000
 * 400			250		125			0x03333
 * 400			332		166			0x0268D
 * 400			400		200			0x02000
 * --------------------------------------------------------------------
 * 500			200		100			0x05000
 * 500			250		125			0x04000
 * 500			332		166			0x03031
 * 500			400		200			0x02800
 * 500			500		250			0x02000
 * --------------------------------------------------------------------
 * 600			200		100			0x06000
 * 600			250		125			0x04CCE
 * 600			332		166			0x039D5
 * 600			400		200			0x03000
 * 600			500		250			0x02666
 * --------------------------------------------------------------------
 * 664			200		100			0x06a38
 * 664			250		125			0x054FD
 * 664			332		166			0x04000
 * 664			400		200			0x0351E
 * 664			500		250			0x02A7E
 * --------------------------------------------------------------------
 * 800			200		100			0x08000
 * 800			250		125			0x06666
 * 800			332		166			0x04D18
 * 800			400		200			0x04000
 * 800			500		250			0x03333
 * --------------------------------------------------------------------
 * sys rate configuration table is in descending order of भागisor.
 */
अटल काष्ठा frac_rate_tbl sys_synth_rtbl[] = अणु
	अणु.भाग = 0x08000पूर्ण,
	अणु.भाग = 0x06a38पूर्ण,
	अणु.भाग = 0x06666पूर्ण,
	अणु.भाग = 0x06000पूर्ण,
	अणु.भाग = 0x054FDपूर्ण,
	अणु.भाग = 0x05000पूर्ण,
	अणु.भाग = 0x04D18पूर्ण,
	अणु.भाग = 0x04CCEपूर्ण,
	अणु.भाग = 0x04000पूर्ण,
	अणु.भाग = 0x039D5पूर्ण,
	अणु.भाग = 0x0351Eपूर्ण,
	अणु.भाग = 0x03333पूर्ण,
	अणु.भाग = 0x03031पूर्ण,
	अणु.भाग = 0x03000पूर्ण,
	अणु.भाग = 0x02A7Eपूर्ण,
	अणु.भाग = 0x02800पूर्ण,
	अणु.भाग = 0x0268Dपूर्ण,
	अणु.भाग = 0x02666पूर्ण,
	अणु.भाग = 0x02000पूर्ण,
पूर्ण;

/* aux rate configuration table, in ascending order of rates */
अटल काष्ठा aux_rate_tbl aux_rtbl[] = अणु
	/* 12.29MHz क्रम vic1भाग2=600MHz and 10.24MHz क्रम VCO1भाग2=500MHz */
	अणु.xscale = 5, .yscale = 122, .eq = 0पूर्ण,
	/* 14.70MHz क्रम vic1भाग2=600MHz and 12.29MHz क्रम VCO1भाग2=500MHz */
	अणु.xscale = 10, .yscale = 204, .eq = 0पूर्ण,
	/* 48MHz क्रम vic1भाग2=600MHz and 40 MHz क्रम VCO1भाग2=500MHz */
	अणु.xscale = 4, .yscale = 25, .eq = 0पूर्ण,
	/* 57.14MHz क्रम vic1भाग2=600MHz and 48 MHz क्रम VCO1भाग2=500MHz */
	अणु.xscale = 4, .yscale = 21, .eq = 0पूर्ण,
	/* 83.33MHz क्रम vic1भाग2=600MHz and 69.44MHz क्रम VCO1भाग2=500MHz */
	अणु.xscale = 5, .yscale = 18, .eq = 0पूर्ण,
	/* 100MHz क्रम vic1भाग2=600MHz and 83.33 MHz क्रम VCO1भाग2=500MHz */
	अणु.xscale = 2, .yscale = 6, .eq = 0पूर्ण,
	/* 125MHz क्रम vic1भाग2=600MHz and 104.1MHz क्रम VCO1भाग2=500MHz */
	अणु.xscale = 5, .yscale = 12, .eq = 0पूर्ण,
	/* 150MHz क्रम vic1भाग2=600MHz and 125MHz क्रम VCO1भाग2=500MHz */
	अणु.xscale = 2, .yscale = 4, .eq = 0पूर्ण,
	/* 166MHz क्रम vic1भाग2=600MHz and 138.88MHz क्रम VCO1भाग2=500MHz */
	अणु.xscale = 5, .yscale = 18, .eq = 1पूर्ण,
	/* 200MHz क्रम vic1भाग2=600MHz and 166MHz क्रम VCO1भाग2=500MHz */
	अणु.xscale = 1, .yscale = 3, .eq = 1पूर्ण,
	/* 250MHz क्रम vic1भाग2=600MHz and 208.33MHz क्रम VCO1भाग2=500MHz */
	अणु.xscale = 5, .yscale = 12, .eq = 1पूर्ण,
	/* 300MHz क्रम vic1भाग2=600MHz and 250MHz क्रम VCO1भाग2=500MHz */
	अणु.xscale = 1, .yscale = 2, .eq = 1पूर्ण,
पूर्ण;

/* gmac rate configuration table, in ascending order of rates */
अटल काष्ठा aux_rate_tbl gmac_rtbl[] = अणु
	/* For gmac phy input clk */
	अणु.xscale = 2, .yscale = 6, .eq = 0पूर्ण, /* भागided by 6 */
	अणु.xscale = 2, .yscale = 4, .eq = 0पूर्ण, /* भागided by 4 */
	अणु.xscale = 1, .yscale = 3, .eq = 1पूर्ण, /* भागided by 3 */
	अणु.xscale = 1, .yscale = 2, .eq = 1पूर्ण, /* भागided by 2 */
पूर्ण;

/* clcd rate configuration table, in ascending order of rates */
अटल काष्ठा frac_rate_tbl clcd_rtbl[] = अणु
	अणु.भाग = 0x18000पूर्ण, /* 25 Mhz , क्रम vc01भाग4 = 300 MHz*/
	अणु.भाग = 0x1638Eपूर्ण, /* 27 Mhz , क्रम vc01भाग4 = 300 MHz*/
	अणु.भाग = 0x14000पूर्ण, /* 25 Mhz , क्रम vc01भाग4 = 250 MHz*/
	अणु.भाग = 0x1284Bपूर्ण, /* 27 Mhz , क्रम vc01भाग4 = 250 MHz*/
	अणु.भाग = 0x0D8D3पूर्ण, /* 58 Mhz , क्रम vco1भाग4 = 393 MHz */
	अणु.भाग = 0x0B72Cपूर्ण, /* 58 Mhz , क्रम vco1भाग4 = 332 MHz */
	अणु.भाग = 0x0A584पूर्ण, /* 58 Mhz , क्रम vco1भाग4 = 300 MHz */
	अणु.भाग = 0x093B1पूर्ण, /* 65 Mhz , क्रम vc01भाग4 = 300 MHz*/
	अणु.भाग = 0x089EEपूर्ण, /* 58 Mhz , क्रम vc01भाग4 = 250 MHz*/
	अणु.भाग = 0x081BAपूर्ण, /* 74 Mhz , क्रम vc01भाग4 = 300 MHz*/
	अणु.भाग = 0x07BA0पूर्ण, /* 65 Mhz , क्रम vc01भाग4 = 250 MHz*/
	अणु.भाग = 0x06f1Cपूर्ण, /* 72 Mhz , क्रम vc01भाग4 = 250 MHz*/
	अणु.भाग = 0x06E58पूर्ण, /* 58 Mhz , क्रम vco1भाग4 = 200 MHz */
	अणु.भाग = 0x06c1Bपूर्ण, /* 74 Mhz , क्रम vc01भाग4 = 250 MHz*/
	अणु.भाग = 0x058E3पूर्ण, /* 108 Mhz , क्रम vc01भाग4 = 300 MHz*/
	अणु.भाग = 0x04A12पूर्ण, /* 108 Mhz , क्रम vc01भाग4 = 250 MHz*/
	अणु.भाग = 0x040A5पूर्ण, /* 148.5 Mhz , क्रम vc01भाग4 = 300 MHz*/
	अणु.भाग = 0x0378Eपूर्ण, /* 144 Mhz , क्रम vc01भाग4 = 250 MHz*/
	अणु.भाग = 0x0360Dपूर्ण, /* 148 Mhz , क्रम vc01भाग4 = 250 MHz*/
	अणु.भाग = 0x035E0पूर्ण, /* 148.5 MHz, क्रम vc01भाग4 = 250 MHz*/
पूर्ण;

/* i2s prescaler1 masks */
अटल स्थिर काष्ठा aux_clk_masks i2s_prs1_masks = अणु
	.eq_sel_mask = AUX_EQ_SEL_MASK,
	.eq_sel_shअगरt = SPEAR1340_I2S_PRS1_EQ_SEL_SHIFT,
	.eq1_mask = AUX_EQ1_SEL,
	.eq2_mask = AUX_EQ2_SEL,
	.xscale_sel_mask = SPEAR1340_I2S_PRS1_CLK_X_MASK,
	.xscale_sel_shअगरt = SPEAR1340_I2S_PRS1_CLK_X_SHIFT,
	.yscale_sel_mask = SPEAR1340_I2S_PRS1_CLK_Y_MASK,
	.yscale_sel_shअगरt = SPEAR1340_I2S_PRS1_CLK_Y_SHIFT,
पूर्ण;

/* i2s sclk (bit घड़ी) syynthesizers masks */
अटल स्थिर काष्ठा aux_clk_masks i2s_sclk_masks = अणु
	.eq_sel_mask = AUX_EQ_SEL_MASK,
	.eq_sel_shअगरt = SPEAR1340_I2S_SCLK_EQ_SEL_SHIFT,
	.eq1_mask = AUX_EQ1_SEL,
	.eq2_mask = AUX_EQ2_SEL,
	.xscale_sel_mask = SPEAR1340_I2S_SCLK_X_MASK,
	.xscale_sel_shअगरt = SPEAR1340_I2S_SCLK_X_SHIFT,
	.yscale_sel_mask = SPEAR1340_I2S_SCLK_Y_MASK,
	.yscale_sel_shअगरt = SPEAR1340_I2S_SCLK_Y_SHIFT,
	.enable_bit = SPEAR1340_I2S_SCLK_SYNTH_ENB,
पूर्ण;

/* i2s prs1 aux rate configuration table, in ascending order of rates */
अटल काष्ठा aux_rate_tbl i2s_prs1_rtbl[] = अणु
	/* For parent clk = 49.152 MHz */
	अणु.xscale = 1, .yscale = 12, .eq = 0पूर्ण, /* 2.048 MHz, smp freq = 8Khz */
	अणु.xscale = 11, .yscale = 96, .eq = 0पूर्ण, /* 2.816 MHz, smp freq = 11Khz */
	अणु.xscale = 1, .yscale = 6, .eq = 0पूर्ण, /* 4.096 MHz, smp freq = 16Khz */
	अणु.xscale = 11, .yscale = 48, .eq = 0पूर्ण, /* 5.632 MHz, smp freq = 22Khz */

	/*
	 * with parent clk = 49.152, freq gen is 8.192 MHz, smp freq = 32Khz
	 * with parent clk = 12.288, freq gen is 2.048 MHz, smp freq = 8Khz
	 */
	अणु.xscale = 1, .yscale = 3, .eq = 0पूर्ण,

	/* For parent clk = 49.152 MHz */
	अणु.xscale = 17, .yscale = 37, .eq = 0पूर्ण, /* 11.289 MHz, smp freq = 44Khz*/
	अणु.xscale = 1, .yscale = 2, .eq = 0पूर्ण, /* 12.288 MHz, smp freq = 48Khz*/
पूर्ण;

/* i2s sclk aux rate configuration table, in ascending order of rates */
अटल काष्ठा aux_rate_tbl i2s_sclk_rtbl[] = अणु
	/* For sclk = ref_clk * x/2/y */
	अणु.xscale = 1, .yscale = 4, .eq = 0पूर्ण,
	अणु.xscale = 1, .yscale = 2, .eq = 0पूर्ण,
पूर्ण;

/* adc rate configuration table, in ascending order of rates */
/* possible adc range is 2.5 MHz to 20 MHz. */
अटल काष्ठा aux_rate_tbl adc_rtbl[] = अणु
	/* For ahb = 166.67 MHz */
	अणु.xscale = 1, .yscale = 31, .eq = 0पूर्ण, /* 2.68 MHz */
	अणु.xscale = 2, .yscale = 21, .eq = 0पूर्ण, /* 7.94 MHz */
	अणु.xscale = 4, .yscale = 21, .eq = 0पूर्ण, /* 15.87 MHz */
	अणु.xscale = 10, .yscale = 42, .eq = 0पूर्ण, /* 19.84 MHz */
पूर्ण;

/* General synth rate configuration table, in ascending order of rates */
अटल काष्ठा frac_rate_tbl gen_rtbl[] = अणु
	अणु.भाग = 0x1A92Bपूर्ण, /* 22.5792 MHz क्रम vco1भाग4=300 MHz*/
	अणु.भाग = 0x186A0पूर्ण, /* 24.576 MHz क्रम vco1भाग4=300 MHz*/
	अणु.भाग = 0x18000पूर्ण, /* 25 MHz क्रम vco1भाग4=300 MHz*/
	अणु.भाग = 0x1624Eपूर्ण, /* 22.5792 MHz क्रम vco1भाग4=250 MHz*/
	अणु.भाग = 0x14585पूर्ण, /* 24.576 MHz क्रम vco1भाग4=250 MHz*/
	अणु.भाग = 0x14000पूर्ण, /* 25 MHz क्रम vco1भाग4=250 MHz*/
	अणु.भाग = 0x0D495पूर्ण, /* 45.1584 MHz क्रम vco1भाग4=300 MHz*/
	अणु.भाग = 0x0C000पूर्ण, /* 50 MHz क्रम vco1भाग4=300 MHz*/
	अणु.भाग = 0x0B127पूर्ण, /* 45.1584 MHz क्रम vco1भाग4=250 MHz*/
	अणु.भाग = 0x0A000पूर्ण, /* 50 MHz क्रम vco1भाग4=250 MHz*/
	अणु.भाग = 0x07530पूर्ण, /* 81.92 MHz क्रम vco1भाग4=300 MHz*/
	अणु.भाग = 0x061A8पूर्ण, /* 81.92 MHz क्रम vco1भाग4=250 MHz*/
	अणु.भाग = 0x06000पूर्ण, /* 100 MHz क्रम vco1भाग4=300 MHz*/
	अणु.भाग = 0x05000पूर्ण, /* 100 MHz क्रम vco1भाग4=250 MHz*/
	अणु.भाग = 0x03000पूर्ण, /* 200 MHz क्रम vco1भाग4=300 MHz*/
	अणु.भाग = 0x02DB6पूर्ण, /* 210 MHz क्रम vco1भाग4=300 MHz*/
	अणु.भाग = 0x02BA2पूर्ण, /* 220 MHz क्रम vco1भाग4=300 MHz*/
	अणु.भाग = 0x029BDपूर्ण, /* 230 MHz क्रम vco1भाग4=300 MHz*/
	अणु.भाग = 0x02800पूर्ण, /* 200 MHz क्रम vco1भाग4=250 MHz*/
	अणु.भाग = 0x02666पूर्ण, /* 250 MHz क्रम vco1भाग4=300 MHz*/
	अणु.भाग = 0x02620पूर्ण, /* 210 MHz क्रम vco1भाग4=250 MHz*/
	अणु.भाग = 0x02460पूर्ण, /* 220 MHz क्रम vco1भाग4=250 MHz*/
	अणु.भाग = 0x022C0पूर्ण, /* 230 MHz क्रम vco1भाग4=250 MHz*/
	अणु.भाग = 0x02160पूर्ण, /* 240 MHz क्रम vco1भाग4=250 MHz*/
	अणु.भाग = 0x02000पूर्ण, /* 250 MHz क्रम vco1भाग4=250 MHz*/
पूर्ण;

/* घड़ी parents */
अटल स्थिर अक्षर *vco_parents[] = अणु "osc_24m_clk", "osc_25m_clk", पूर्ण;
अटल स्थिर अक्षर *sys_parents[] = अणु "pll1_clk", "pll1_clk", "pll1_clk",
	"pll1_clk", "sys_syn_clk", "sys_syn_clk", "pll2_clk", "pll3_clk", पूर्ण;
अटल स्थिर अक्षर *ahb_parents[] = अणु "cpu_div3_clk", "amba_syn_clk", पूर्ण;
अटल स्थिर अक्षर *gpt_parents[] = अणु "osc_24m_clk", "apb_clk", पूर्ण;
अटल स्थिर अक्षर *uart0_parents[] = अणु "pll5_clk", "osc_24m_clk",
	"uart0_syn_gclk", पूर्ण;
अटल स्थिर अक्षर *uart1_parents[] = अणु "pll5_clk", "osc_24m_clk",
	"uart1_syn_gclk", पूर्ण;
अटल स्थिर अक्षर *c3_parents[] = अणु "pll5_clk", "c3_syn_gclk", पूर्ण;
अटल स्थिर अक्षर *gmac_phy_input_parents[] = अणु "gmii_pad_clk", "pll2_clk",
	"osc_25m_clk", पूर्ण;
अटल स्थिर अक्षर *gmac_phy_parents[] = अणु "phy_input_mclk", "phy_syn_gclk", पूर्ण;
अटल स्थिर अक्षर *clcd_synth_parents[] = अणु "vco1div4_clk", "pll2_clk", पूर्ण;
अटल स्थिर अक्षर *clcd_pixel_parents[] = अणु "pll5_clk", "clcd_syn_clk", पूर्ण;
अटल स्थिर अक्षर *i2s_src_parents[] = अणु "vco1div2_clk", "pll2_clk", "pll3_clk",
	"i2s_src_pad_clk", पूर्ण;
अटल स्थिर अक्षर *i2s_ref_parents[] = अणु "i2s_src_mclk", "i2s_prs1_clk", पूर्ण;
अटल स्थिर अक्षर *spdअगर_out_parents[] = अणु "i2s_src_pad_clk", "gen_syn2_clk", पूर्ण;
अटल स्थिर अक्षर *spdअगर_in_parents[] = अणु "pll2_clk", "gen_syn3_clk", पूर्ण;

अटल स्थिर अक्षर *gen_synth0_1_parents[] = अणु "vco1div4_clk", "vco3div2_clk",
	"pll3_clk", पूर्ण;
अटल स्थिर अक्षर *gen_synth2_3_parents[] = अणु "vco1div4_clk", "vco2div2_clk",
	"pll2_clk", पूर्ण;

व्योम __init spear1340_clk_init(व्योम __iomem *misc_base)
अणु
	काष्ठा clk *clk, *clk1;

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "osc_32k_clk", शून्य, 0, 32000);
	clk_रेजिस्टर_clkdev(clk, "osc_32k_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "osc_24m_clk", शून्य, 0, 24000000);
	clk_रेजिस्टर_clkdev(clk, "osc_24m_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "osc_25m_clk", शून्य, 0, 25000000);
	clk_रेजिस्टर_clkdev(clk, "osc_25m_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "gmii_pad_clk", शून्य, 0, 125000000);
	clk_रेजिस्टर_clkdev(clk, "gmii_pad_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "i2s_src_pad_clk", शून्य, 0,
				      12288000);
	clk_रेजिस्टर_clkdev(clk, "i2s_src_pad_clk", शून्य);

	/* घड़ी derived from 32 KHz osc clk */
	clk = clk_रेजिस्टर_gate(शून्य, "rtc-spear", "osc_32k_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_RTC_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e0580000.rtc");

	/* घड़ी derived from 24 or 25 MHz osc clk */
	/* vco-pll */
	clk = clk_रेजिस्टर_mux(शून्य, "vco1_mclk", vco_parents,
			ARRAY_SIZE(vco_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PLL_CFG, SPEAR1340_PLL1_CLK_SHIFT,
			SPEAR1340_PLL_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "vco1_mclk", शून्य);
	clk = clk_रेजिस्टर_vco_pll("vco1_clk", "pll1_clk", शून्य, "vco1_mclk", 0,
			SPEAR1340_PLL1_CTR, SPEAR1340_PLL1_FRQ, pll_rtbl,
			ARRAY_SIZE(pll_rtbl), &_lock, &clk1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "vco1_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "pll1_clk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "vco2_mclk", vco_parents,
			ARRAY_SIZE(vco_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PLL_CFG, SPEAR1340_PLL2_CLK_SHIFT,
			SPEAR1340_PLL_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "vco2_mclk", शून्य);
	clk = clk_रेजिस्टर_vco_pll("vco2_clk", "pll2_clk", शून्य, "vco2_mclk", 0,
			SPEAR1340_PLL2_CTR, SPEAR1340_PLL2_FRQ, pll_rtbl,
			ARRAY_SIZE(pll_rtbl), &_lock, &clk1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "vco2_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "pll2_clk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "vco3_mclk", vco_parents,
			ARRAY_SIZE(vco_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PLL_CFG, SPEAR1340_PLL3_CLK_SHIFT,
			SPEAR1340_PLL_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "vco3_mclk", शून्य);
	clk = clk_रेजिस्टर_vco_pll("vco3_clk", "pll3_clk", शून्य, "vco3_mclk", 0,
			SPEAR1340_PLL3_CTR, SPEAR1340_PLL3_FRQ, pll_rtbl,
			ARRAY_SIZE(pll_rtbl), &_lock, &clk1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "vco3_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "pll3_clk", शून्य);

	clk = clk_रेजिस्टर_vco_pll("vco4_clk", "pll4_clk", शून्य, "osc_24m_clk",
			0, SPEAR1340_PLL4_CTR, SPEAR1340_PLL4_FRQ, pll4_rtbl,
			ARRAY_SIZE(pll4_rtbl), &_lock, &clk1, शून्य);
	clk_रेजिस्टर_clkdev(clk, "vco4_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "pll4_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "pll5_clk", "osc_24m_clk", 0,
			48000000);
	clk_रेजिस्टर_clkdev(clk, "pll5_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_rate(शून्य, "pll6_clk", "osc_25m_clk", 0,
			25000000);
	clk_रेजिस्टर_clkdev(clk, "pll6_clk", शून्य);

	/* vco भाग n घड़ीs */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "vco1div2_clk", "vco1_clk", 0, 1,
			2);
	clk_रेजिस्टर_clkdev(clk, "vco1div2_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "vco1div4_clk", "vco1_clk", 0, 1,
			4);
	clk_रेजिस्टर_clkdev(clk, "vco1div4_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "vco2div2_clk", "vco2_clk", 0, 1,
			2);
	clk_रेजिस्टर_clkdev(clk, "vco2div2_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "vco3div2_clk", "vco3_clk", 0, 1,
			2);
	clk_रेजिस्टर_clkdev(clk, "vco3div2_clk", शून्य);

	/* peripherals */
	clk_रेजिस्टर_fixed_factor(शून्य, "thermal_clk", "osc_24m_clk", 0, 1,
			128);
	clk = clk_रेजिस्टर_gate(शून्य, "thermal_gclk", "thermal_clk", 0,
			SPEAR1340_PERIP2_CLK_ENB, SPEAR1340_THSENS_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e07008c4.thermal");

	/* घड़ी derived from pll4 clk */
	clk = clk_रेजिस्टर_fixed_factor(शून्य, "ddr_clk", "pll4_clk", 0, 1,
			1);
	clk_रेजिस्टर_clkdev(clk, "ddr_clk", शून्य);

	/* घड़ी derived from pll1 clk */
	clk = clk_रेजिस्टर_frac("sys_syn_clk", "vco1div2_clk", 0,
			SPEAR1340_SYS_CLK_SYNT, sys_synth_rtbl,
			ARRAY_SIZE(sys_synth_rtbl), &_lock);
	clk_रेजिस्टर_clkdev(clk, "sys_syn_clk", शून्य);

	clk = clk_रेजिस्टर_frac("amba_syn_clk", "vco1div2_clk", 0,
			SPEAR1340_AMBA_CLK_SYNT, amba_synth_rtbl,
			ARRAY_SIZE(amba_synth_rtbl), &_lock);
	clk_रेजिस्टर_clkdev(clk, "amba_syn_clk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "sys_mclk", sys_parents,
			ARRAY_SIZE(sys_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_SYS_CLK_CTRL, SPEAR1340_SCLK_SRC_SEL_SHIFT,
			SPEAR1340_SCLK_SRC_SEL_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "sys_mclk", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "cpu_clk", "sys_mclk", 0, 1,
			2);
	clk_रेजिस्टर_clkdev(clk, "cpu_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "cpu_div3_clk", "cpu_clk", 0, 1,
			3);
	clk_रेजिस्टर_clkdev(clk, "cpu_div3_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "wdt_clk", "cpu_clk", 0, 1,
			2);
	clk_रेजिस्टर_clkdev(clk, शून्य, "ec800620.wdt");

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "smp_twd_clk", "cpu_clk", 0, 1,
			2);
	clk_रेजिस्टर_clkdev(clk, शून्य, "smp_twd");

	clk = clk_रेजिस्टर_mux(शून्य, "ahb_clk", ahb_parents,
			ARRAY_SIZE(ahb_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_SYS_CLK_CTRL, SPEAR1340_HCLK_SRC_SEL_SHIFT,
			SPEAR1340_HCLK_SRC_SEL_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "ahb_clk", शून्य);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, "apb_clk", "ahb_clk", 0, 1,
			2);
	clk_रेजिस्टर_clkdev(clk, "apb_clk", शून्य);

	/* gpt घड़ीs */
	clk = clk_रेजिस्टर_mux(शून्य, "gpt0_mclk", gpt_parents,
			ARRAY_SIZE(gpt_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PERIP_CLK_CFG, SPEAR1340_GPT0_CLK_SHIFT,
			SPEAR1340_GPT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "gpt0_mclk", शून्य);
	clk = clk_रेजिस्टर_gate(शून्य, "gpt0_clk", "gpt0_mclk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_GPT0_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "gpt0");

	clk = clk_रेजिस्टर_mux(शून्य, "gpt1_mclk", gpt_parents,
			ARRAY_SIZE(gpt_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PERIP_CLK_CFG, SPEAR1340_GPT1_CLK_SHIFT,
			SPEAR1340_GPT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "gpt1_mclk", शून्य);
	clk = clk_रेजिस्टर_gate(शून्य, "gpt1_clk", "gpt1_mclk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_GPT1_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "gpt1");

	clk = clk_रेजिस्टर_mux(शून्य, "gpt2_mclk", gpt_parents,
			ARRAY_SIZE(gpt_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PERIP_CLK_CFG, SPEAR1340_GPT2_CLK_SHIFT,
			SPEAR1340_GPT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "gpt2_mclk", शून्य);
	clk = clk_रेजिस्टर_gate(शून्य, "gpt2_clk", "gpt2_mclk", 0,
			SPEAR1340_PERIP2_CLK_ENB, SPEAR1340_GPT2_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "gpt2");

	clk = clk_रेजिस्टर_mux(शून्य, "gpt3_mclk", gpt_parents,
			ARRAY_SIZE(gpt_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PERIP_CLK_CFG, SPEAR1340_GPT3_CLK_SHIFT,
			SPEAR1340_GPT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "gpt3_mclk", शून्य);
	clk = clk_रेजिस्टर_gate(शून्य, "gpt3_clk", "gpt3_mclk", 0,
			SPEAR1340_PERIP2_CLK_ENB, SPEAR1340_GPT3_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "gpt3");

	/* others */
	clk = clk_रेजिस्टर_aux("uart0_syn_clk", "uart0_syn_gclk",
			"vco1div2_clk", 0, SPEAR1340_UART0_CLK_SYNT, शून्य,
			aux_rtbl, ARRAY_SIZE(aux_rtbl), &_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "uart0_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "uart0_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "uart0_mclk", uart0_parents,
			ARRAY_SIZE(uart0_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PERIP_CLK_CFG, SPEAR1340_UART0_CLK_SHIFT,
			SPEAR1340_UART_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "uart0_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "uart0_clk", "uart0_mclk",
			CLK_SET_RATE_PARENT, SPEAR1340_PERIP1_CLK_ENB,
			SPEAR1340_UART0_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e0000000.serial");

	clk = clk_रेजिस्टर_aux("uart1_syn_clk", "uart1_syn_gclk",
			"vco1div2_clk", 0, SPEAR1340_UART1_CLK_SYNT, शून्य,
			aux_rtbl, ARRAY_SIZE(aux_rtbl), &_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "uart1_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "uart1_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "uart1_mclk", uart1_parents,
			ARRAY_SIZE(uart1_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PERIP_CLK_CFG, SPEAR1340_UART1_CLK_SHIFT,
			SPEAR1340_UART_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "uart1_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "uart1_clk", "uart1_mclk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_UART1_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b4100000.serial");

	clk = clk_रेजिस्टर_aux("sdhci_syn_clk", "sdhci_syn_gclk",
			"vco1div2_clk", 0, SPEAR1340_SDHCI_CLK_SYNT, शून्य,
			aux_rtbl, ARRAY_SIZE(aux_rtbl), &_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "sdhci_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "sdhci_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "sdhci_clk", "sdhci_syn_gclk",
			CLK_SET_RATE_PARENT, SPEAR1340_PERIP1_CLK_ENB,
			SPEAR1340_SDHCI_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b3000000.sdhci");

	clk = clk_रेजिस्टर_aux("cfxd_syn_clk", "cfxd_syn_gclk", "vco1div2_clk",
			0, SPEAR1340_CFXD_CLK_SYNT, शून्य, aux_rtbl,
			ARRAY_SIZE(aux_rtbl), &_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "cfxd_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "cfxd_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "cfxd_clk", "cfxd_syn_gclk",
			CLK_SET_RATE_PARENT, SPEAR1340_PERIP1_CLK_ENB,
			SPEAR1340_CFXD_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b2800000.cf");
	clk_रेजिस्टर_clkdev(clk, शून्य, "arasan_xd");

	clk = clk_रेजिस्टर_aux("c3_syn_clk", "c3_syn_gclk", "vco1div2_clk", 0,
			SPEAR1340_C3_CLK_SYNT, शून्य, aux_rtbl,
			ARRAY_SIZE(aux_rtbl), &_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "c3_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "c3_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "c3_mclk", c3_parents,
			ARRAY_SIZE(c3_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PERIP_CLK_CFG, SPEAR1340_C3_CLK_SHIFT,
			SPEAR1340_C3_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "c3_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "c3_clk", "c3_mclk", CLK_SET_RATE_PARENT,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_C3_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e1800000.c3");

	/* gmac */
	clk = clk_रेजिस्टर_mux(शून्य, "phy_input_mclk", gmac_phy_input_parents,
			ARRAY_SIZE(gmac_phy_input_parents),
			CLK_SET_RATE_NO_REPARENT, SPEAR1340_GMAC_CLK_CFG,
			SPEAR1340_GMAC_PHY_INPUT_CLK_SHIFT,
			SPEAR1340_GMAC_PHY_INPUT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "phy_input_mclk", शून्य);

	clk = clk_रेजिस्टर_aux("phy_syn_clk", "phy_syn_gclk", "phy_input_mclk",
			0, SPEAR1340_GMAC_CLK_SYNT, शून्य, gmac_rtbl,
			ARRAY_SIZE(gmac_rtbl), &_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "phy_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "phy_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "phy_mclk", gmac_phy_parents,
			ARRAY_SIZE(gmac_phy_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PERIP_CLK_CFG, SPEAR1340_GMAC_PHY_CLK_SHIFT,
			SPEAR1340_GMAC_PHY_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "stmmacphy.0", शून्य);

	/* clcd */
	clk = clk_रेजिस्टर_mux(शून्य, "clcd_syn_mclk", clcd_synth_parents,
			ARRAY_SIZE(clcd_synth_parents),
			CLK_SET_RATE_NO_REPARENT, SPEAR1340_CLCD_CLK_SYNT,
			SPEAR1340_CLCD_SYNT_CLK_SHIFT,
			SPEAR1340_CLCD_SYNT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "clcd_syn_mclk", शून्य);

	clk = clk_रेजिस्टर_frac("clcd_syn_clk", "clcd_syn_mclk", 0,
			SPEAR1340_CLCD_CLK_SYNT, clcd_rtbl,
			ARRAY_SIZE(clcd_rtbl), &_lock);
	clk_रेजिस्टर_clkdev(clk, "clcd_syn_clk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "clcd_pixel_mclk", clcd_pixel_parents,
			ARRAY_SIZE(clcd_pixel_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PERIP_CLK_CFG, SPEAR1340_CLCD_CLK_SHIFT,
			SPEAR1340_CLCD_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "clcd_pixel_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "clcd_clk", "clcd_pixel_mclk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_CLCD_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e1000000.clcd");

	/* i2s */
	clk = clk_रेजिस्टर_mux(शून्य, "i2s_src_mclk", i2s_src_parents,
			ARRAY_SIZE(i2s_src_parents), CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_I2S_CLK_CFG, SPEAR1340_I2S_SRC_CLK_SHIFT,
			SPEAR1340_I2S_SRC_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "i2s_src_mclk", शून्य);

	clk = clk_रेजिस्टर_aux("i2s_prs1_clk", शून्य, "i2s_src_mclk",
			CLK_SET_RATE_PARENT, SPEAR1340_I2S_CLK_CFG,
			&i2s_prs1_masks, i2s_prs1_rtbl,
			ARRAY_SIZE(i2s_prs1_rtbl), &_lock, शून्य);
	clk_रेजिस्टर_clkdev(clk, "i2s_prs1_clk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "i2s_ref_mclk", i2s_ref_parents,
			ARRAY_SIZE(i2s_ref_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_I2S_CLK_CFG, SPEAR1340_I2S_REF_SHIFT,
			SPEAR1340_I2S_REF_SEL_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "i2s_ref_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "i2s_ref_pad_clk", "i2s_ref_mclk", 0,
			SPEAR1340_PERIP2_CLK_ENB, SPEAR1340_I2S_REF_PAD_CLK_ENB,
			0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "i2s_ref_pad_clk", शून्य);

	clk = clk_रेजिस्टर_aux("i2s_sclk_clk", "i2s_sclk_gclk", "i2s_ref_mclk",
			0, SPEAR1340_I2S_CLK_CFG, &i2s_sclk_masks,
			i2s_sclk_rtbl, ARRAY_SIZE(i2s_sclk_rtbl), &_lock,
			&clk1);
	clk_रेजिस्टर_clkdev(clk, "i2s_sclk_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "i2s_sclk_gclk", शून्य);

	/* घड़ी derived from ahb clk */
	clk = clk_रेजिस्टर_gate(शून्य, "i2c0_clk", "ahb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_I2C0_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e0280000.i2c");

	clk = clk_रेजिस्टर_gate(शून्य, "i2c1_clk", "ahb_clk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_I2C1_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b4000000.i2c");

	clk = clk_रेजिस्टर_gate(शून्य, "dma_clk", "ahb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_DMA_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "ea800000.dma");
	clk_रेजिस्टर_clkdev(clk, शून्य, "eb000000.dma");

	clk = clk_रेजिस्टर_gate(शून्य, "gmac_clk", "ahb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_GMAC_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e2000000.eth");

	clk = clk_रेजिस्टर_gate(शून्य, "fsmc_clk", "ahb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_FSMC_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b0000000.flash");

	clk = clk_रेजिस्टर_gate(शून्य, "smi_clk", "ahb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_SMI_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "ea000000.flash");

	clk = clk_रेजिस्टर_gate(शून्य, "usbh0_clk", "ahb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_UHC0_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e4000000.ohci");
	clk_रेजिस्टर_clkdev(clk, शून्य, "e4800000.ehci");

	clk = clk_रेजिस्टर_gate(शून्य, "usbh1_clk", "ahb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_UHC1_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e5000000.ohci");
	clk_रेजिस्टर_clkdev(clk, शून्य, "e5800000.ehci");

	clk = clk_रेजिस्टर_gate(शून्य, "uoc_clk", "ahb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_UOC_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e3800000.otg");

	clk = clk_रेजिस्टर_gate(शून्य, "pcie_sata_clk", "ahb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_PCIE_SATA_CLK_ENB,
			0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b1000000.pcie");
	clk_रेजिस्टर_clkdev(clk, शून्य, "b1000000.ahci");

	clk = clk_रेजिस्टर_gate(शून्य, "sysram0_clk", "ahb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_SYSRAM0_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "sysram0_clk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "sysram1_clk", "ahb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_SYSRAM1_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "sysram1_clk", शून्य);

	clk = clk_रेजिस्टर_aux("adc_syn_clk", "adc_syn_gclk", "ahb_clk",
			0, SPEAR1340_ADC_CLK_SYNT, शून्य, adc_rtbl,
			ARRAY_SIZE(adc_rtbl), &_lock, &clk1);
	clk_रेजिस्टर_clkdev(clk, "adc_syn_clk", शून्य);
	clk_रेजिस्टर_clkdev(clk1, "adc_syn_gclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "adc_clk", "adc_syn_gclk",
			CLK_SET_RATE_PARENT, SPEAR1340_PERIP1_CLK_ENB,
			SPEAR1340_ADC_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e0080000.adc");

	/* घड़ी derived from apb clk */
	clk = clk_रेजिस्टर_gate(शून्य, "ssp_clk", "apb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_SSP_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e0100000.spi");

	clk = clk_रेजिस्टर_gate(शून्य, "gpio0_clk", "apb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_GPIO0_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e0600000.gpio");

	clk = clk_रेजिस्टर_gate(शून्य, "gpio1_clk", "apb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_GPIO1_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e0680000.gpio");

	clk = clk_रेजिस्टर_gate(शून्य, "i2s_play_clk", "apb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_I2S_PLAY_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b2400000.i2s-play");

	clk = clk_रेजिस्टर_gate(शून्य, "i2s_rec_clk", "apb_clk", 0,
			SPEAR1340_PERIP1_CLK_ENB, SPEAR1340_I2S_REC_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "b2000000.i2s-rec");

	clk = clk_रेजिस्टर_gate(शून्य, "kbd_clk", "apb_clk", 0,
			SPEAR1340_PERIP2_CLK_ENB, SPEAR1340_KBD_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e0300000.kbd");

	/* RAS clks */
	clk = clk_रेजिस्टर_mux(शून्य, "gen_syn0_1_mclk", gen_synth0_1_parents,
			ARRAY_SIZE(gen_synth0_1_parents),
			CLK_SET_RATE_NO_REPARENT, SPEAR1340_PLL_CFG,
			SPEAR1340_GEN_SYNT0_1_CLK_SHIFT,
			SPEAR1340_GEN_SYNT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "gen_syn0_1_mclk", शून्य);

	clk = clk_रेजिस्टर_mux(शून्य, "gen_syn2_3_mclk", gen_synth2_3_parents,
			ARRAY_SIZE(gen_synth2_3_parents),
			CLK_SET_RATE_NO_REPARENT, SPEAR1340_PLL_CFG,
			SPEAR1340_GEN_SYNT2_3_CLK_SHIFT,
			SPEAR1340_GEN_SYNT_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "gen_syn2_3_mclk", शून्य);

	clk = clk_रेजिस्टर_frac("gen_syn0_clk", "gen_syn0_1_mclk", 0,
			SPEAR1340_GEN_CLK_SYNT0, gen_rtbl, ARRAY_SIZE(gen_rtbl),
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "gen_syn0_clk", शून्य);

	clk = clk_रेजिस्टर_frac("gen_syn1_clk", "gen_syn0_1_mclk", 0,
			SPEAR1340_GEN_CLK_SYNT1, gen_rtbl, ARRAY_SIZE(gen_rtbl),
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "gen_syn1_clk", शून्य);

	clk = clk_रेजिस्टर_frac("gen_syn2_clk", "gen_syn2_3_mclk", 0,
			SPEAR1340_GEN_CLK_SYNT2, gen_rtbl, ARRAY_SIZE(gen_rtbl),
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "gen_syn2_clk", शून्य);

	clk = clk_रेजिस्टर_frac("gen_syn3_clk", "gen_syn2_3_mclk", 0,
			SPEAR1340_GEN_CLK_SYNT3, gen_rtbl, ARRAY_SIZE(gen_rtbl),
			&_lock);
	clk_रेजिस्टर_clkdev(clk, "gen_syn3_clk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "mali_clk", "gen_syn3_clk",
			CLK_SET_RATE_PARENT, SPEAR1340_PERIP3_CLK_ENB,
			SPEAR1340_MALI_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "mali");

	clk = clk_रेजिस्टर_gate(शून्य, "cec0_clk", "ahb_clk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_CEC0_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "spear_cec.0");

	clk = clk_रेजिस्टर_gate(शून्य, "cec1_clk", "ahb_clk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_CEC1_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "spear_cec.1");

	clk = clk_रेजिस्टर_mux(शून्य, "spdif_out_mclk", spdअगर_out_parents,
			ARRAY_SIZE(spdअगर_out_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PERIP_CLK_CFG, SPEAR1340_SPDIF_OUT_CLK_SHIFT,
			SPEAR1340_SPDIF_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "spdif_out_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "spdif_out_clk", "spdif_out_mclk",
			CLK_SET_RATE_PARENT, SPEAR1340_PERIP3_CLK_ENB,
			SPEAR1340_SPDIF_OUT_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0000000.spdif-out");

	clk = clk_रेजिस्टर_mux(शून्य, "spdif_in_mclk", spdअगर_in_parents,
			ARRAY_SIZE(spdअगर_in_parents),
			CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
			SPEAR1340_PERIP_CLK_CFG, SPEAR1340_SPDIF_IN_CLK_SHIFT,
			SPEAR1340_SPDIF_CLK_MASK, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, "spdif_in_mclk", शून्य);

	clk = clk_रेजिस्टर_gate(शून्य, "spdif_in_clk", "spdif_in_mclk",
			CLK_SET_RATE_PARENT, SPEAR1340_PERIP3_CLK_ENB,
			SPEAR1340_SPDIF_IN_CLK_ENB, 0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0100000.spdif-in");

	clk = clk_रेजिस्टर_gate(शून्य, "acp_clk", "ahb_clk", 0,
			SPEAR1340_PERIP2_CLK_ENB, SPEAR1340_ACP_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "acp_clk");

	clk = clk_रेजिस्टर_gate(शून्य, "plgpio_clk", "ahb_clk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_PLGPIO_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e2800000.gpio");

	clk = clk_रेजिस्टर_gate(शून्य, "video_dec_clk", "ahb_clk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_VIDEO_DEC_CLK_ENB,
			0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "video_dec");

	clk = clk_रेजिस्टर_gate(शून्य, "video_enc_clk", "ahb_clk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_VIDEO_ENC_CLK_ENB,
			0, &_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "video_enc");

	clk = clk_रेजिस्टर_gate(शून्य, "video_in_clk", "ahb_clk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_VIDEO_IN_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "spear_vip");

	clk = clk_रेजिस्टर_gate(शून्य, "cam0_clk", "ahb_clk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_CAM0_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0200000.cam0");

	clk = clk_रेजिस्टर_gate(शून्य, "cam1_clk", "ahb_clk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_CAM1_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0300000.cam1");

	clk = clk_रेजिस्टर_gate(शून्य, "cam2_clk", "ahb_clk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_CAM2_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0400000.cam2");

	clk = clk_रेजिस्टर_gate(शून्य, "cam3_clk", "ahb_clk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_CAM3_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "d0500000.cam3");

	clk = clk_रेजिस्टर_gate(शून्य, "pwm_clk", "ahb_clk", 0,
			SPEAR1340_PERIP3_CLK_ENB, SPEAR1340_PWM_CLK_ENB, 0,
			&_lock);
	clk_रेजिस्टर_clkdev(clk, शून्य, "e0180000.pwm");
पूर्ण
