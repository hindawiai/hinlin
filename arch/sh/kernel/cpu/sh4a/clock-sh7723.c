<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4a/घड़ी-sh7723.c
 *
 * SH7723 घड़ी framework support
 *
 * Copyright (C) 2009 Magnus Damm
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/sh_clk.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <cpu/sh7723.h>

/* SH7723 रेजिस्टरs */
#घोषणा FRQCR		0xa4150000
#घोषणा VCLKCR		0xa4150004
#घोषणा SCLKACR		0xa4150008
#घोषणा SCLKBCR		0xa415000c
#घोषणा IRDACLKCR	0xa4150018
#घोषणा PLLCR		0xa4150024
#घोषणा MSTPCR0		0xa4150030
#घोषणा MSTPCR1		0xa4150034
#घोषणा MSTPCR2		0xa4150038
#घोषणा DLLFRQ		0xa4150050

/* Fixed 32 KHz root घड़ी क्रम RTC and Power Management purposes */
अटल काष्ठा clk r_clk = अणु
	.rate           = 32768,
पूर्ण;

/*
 * Default rate क्रम the root input घड़ी, reset this with clk_set_rate()
 * from the platक्रमm code.
 */
काष्ठा clk extal_clk = अणु
	.rate		= 33333333,
पूर्ण;

/* The dll multiplies the 32khz r_clk, may be used instead of extal */
अटल अचिन्हित दीर्घ dll_recalc(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ mult;

	अगर (__raw_पढ़ोl(PLLCR) & 0x1000)
		mult = __raw_पढ़ोl(DLLFRQ);
	अन्यथा
		mult = 0;

	वापस clk->parent->rate * mult;
पूर्ण

अटल काष्ठा sh_clk_ops dll_clk_ops = अणु
	.recalc		= dll_recalc,
पूर्ण;

अटल काष्ठा clk dll_clk = अणु
	.ops		= &dll_clk_ops,
	.parent		= &r_clk,
	.flags		= CLK_ENABLE_ON_INIT,
पूर्ण;

अटल अचिन्हित दीर्घ pll_recalc(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ mult = 1;
	अचिन्हित दीर्घ भाग = 1;

	अगर (__raw_पढ़ोl(PLLCR) & 0x4000)
		mult = (((__raw_पढ़ोl(FRQCR) >> 24) & 0x1f) + 1);
	अन्यथा
		भाग = 2;

	वापस (clk->parent->rate * mult) / भाग;
पूर्ण

अटल काष्ठा sh_clk_ops pll_clk_ops = अणु
	.recalc		= pll_recalc,
पूर्ण;

अटल काष्ठा clk pll_clk = अणु
	.ops		= &pll_clk_ops,
	.flags		= CLK_ENABLE_ON_INIT,
पूर्ण;

काष्ठा clk *मुख्य_clks[] = अणु
	&r_clk,
	&extal_clk,
	&dll_clk,
	&pll_clk,
पूर्ण;

अटल पूर्णांक multipliers[] = अणु 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1 पूर्ण;
अटल पूर्णांक भागisors[] = अणु 1, 3, 2, 5, 3, 4, 5, 6, 8, 10, 12, 16, 20 पूर्ण;

अटल काष्ठा clk_भाग_mult_table भाग4_भाग_mult_table = अणु
	.भागisors = भागisors,
	.nr_भागisors = ARRAY_SIZE(भागisors),
	.multipliers = multipliers,
	.nr_multipliers = ARRAY_SIZE(multipliers),
पूर्ण;

अटल काष्ठा clk_भाग4_table भाग4_table = अणु
	.भाग_mult_table = &भाग4_भाग_mult_table,
पूर्ण;

क्रमागत अणु DIV4_I, DIV4_U, DIV4_SH, DIV4_B, DIV4_B3, DIV4_P, DIV4_NR पूर्ण;

#घोषणा DIV4(_reg, _bit, _mask, _flags) \
  SH_CLK_DIV4(&pll_clk, _reg, _bit, _mask, _flags)

काष्ठा clk भाग4_clks[DIV4_NR] = अणु
	[DIV4_I] = DIV4(FRQCR, 20, 0x0dbf, CLK_ENABLE_ON_INIT),
	[DIV4_U] = DIV4(FRQCR, 16, 0x0dbf, CLK_ENABLE_ON_INIT),
	[DIV4_SH] = DIV4(FRQCR, 12, 0x0dbf, CLK_ENABLE_ON_INIT),
	[DIV4_B] = DIV4(FRQCR, 8, 0x0dbf, CLK_ENABLE_ON_INIT),
	[DIV4_B3] = DIV4(FRQCR, 4, 0x0db4, CLK_ENABLE_ON_INIT),
	[DIV4_P] = DIV4(FRQCR, 0, 0x0dbf, 0),
पूर्ण;

क्रमागत अणु DIV4_IRDA, DIV4_ENABLE_NR पूर्ण;

काष्ठा clk भाग4_enable_clks[DIV4_ENABLE_NR] = अणु
	[DIV4_IRDA] = DIV4(IRDACLKCR, 0, 0x0dbf, 0),
पूर्ण;

क्रमागत अणु DIV4_SIUA, DIV4_SIUB, DIV4_REPARENT_NR पूर्ण;

काष्ठा clk भाग4_reparent_clks[DIV4_REPARENT_NR] = अणु
	[DIV4_SIUA] = DIV4(SCLKACR, 0, 0x0dbf, 0),
	[DIV4_SIUB] = DIV4(SCLKBCR, 0, 0x0dbf, 0),
पूर्ण;
क्रमागत अणु DIV6_V, DIV6_NR पूर्ण;

काष्ठा clk भाग6_clks[DIV6_NR] = अणु
	[DIV6_V] = SH_CLK_DIV6(&pll_clk, VCLKCR, 0),
पूर्ण;

अटल काष्ठा clk mstp_clks[] = अणु
	/* See page 60 of Datasheet V1.0: Overview -> Block Diagram */
	[HWBLK_TLB]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_I],  MSTPCR0, 31, CLK_ENABLE_ON_INIT),
	[HWBLK_IC]     = SH_CLK_MSTP32(&भाग4_clks[DIV4_I],  MSTPCR0, 30, CLK_ENABLE_ON_INIT),
	[HWBLK_OC]     = SH_CLK_MSTP32(&भाग4_clks[DIV4_I],  MSTPCR0, 29, CLK_ENABLE_ON_INIT),
	[HWBLK_L2C]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_SH], MSTPCR0, 28, CLK_ENABLE_ON_INIT),
	[HWBLK_ILMEM]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_I],  MSTPCR0, 27, CLK_ENABLE_ON_INIT),
	[HWBLK_FPU]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_I],  MSTPCR0, 24, CLK_ENABLE_ON_INIT),
	[HWBLK_INTC]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_I],  MSTPCR0, 22, CLK_ENABLE_ON_INIT),
	[HWBLK_DMAC0]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR0, 21, 0),
	[HWBLK_SHYWAY] = SH_CLK_MSTP32(&भाग4_clks[DIV4_SH], MSTPCR0, 20, CLK_ENABLE_ON_INIT),
	[HWBLK_HUDI]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_P],  MSTPCR0, 19, 0),
	[HWBLK_UBC]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_I],  MSTPCR0, 17, 0),
	[HWBLK_TMU0]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_P],  MSTPCR0, 15, 0),
	[HWBLK_CMT]    = SH_CLK_MSTP32(&r_clk,		    MSTPCR0, 14, 0),
	[HWBLK_RWDT]   = SH_CLK_MSTP32(&r_clk,		    MSTPCR0, 13, 0),
	[HWBLK_DMAC1]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR0, 12, 0),
	[HWBLK_TMU1]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_P],  MSTPCR0, 11, 0),
	[HWBLK_FLCTL]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_P],  MSTPCR0, 10, 0),
	[HWBLK_SCIF0]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_P],  MSTPCR0, 9, 0),
	[HWBLK_SCIF1]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_P],  MSTPCR0, 8, 0),
	[HWBLK_SCIF2]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_P],  MSTPCR0, 7, 0),
	[HWBLK_SCIF3]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR0, 6, 0),
	[HWBLK_SCIF4]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR0, 5, 0),
	[HWBLK_SCIF5]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR0, 4, 0),
	[HWBLK_MSIOF0] = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR0, 2, 0),
	[HWBLK_MSIOF1] = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR0, 1, 0),
	[HWBLK_MERAM]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_SH], MSTPCR0, 0, 0),

	[HWBLK_IIC]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_P],  MSTPCR1, 9, 0),
	[HWBLK_RTC]    = SH_CLK_MSTP32(&r_clk,		    MSTPCR1, 8, 0),

	[HWBLK_ATAPI]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_SH], MSTPCR2, 28, 0),
	[HWBLK_ADC]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_P],  MSTPCR2, 27, 0),
	[HWBLK_TPU]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 25, 0),
	[HWBLK_IRDA]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_P],  MSTPCR2, 24, 0),
	[HWBLK_TSIF]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 22, 0),
	[HWBLK_ICB]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 21, CLK_ENABLE_ON_INIT),
	[HWBLK_SDHI0]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 18, 0),
	[HWBLK_SDHI1]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 17, 0),
	[HWBLK_KEYSC]  = SH_CLK_MSTP32(&r_clk,		    MSTPCR2, 14, 0),
	[HWBLK_USB]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 11, 0),
	[HWBLK_2DG]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 10, 0),
	[HWBLK_SIU]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 8, 0),
	[HWBLK_VEU2H1] = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 6, 0),
	[HWBLK_VOU]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 5, 0),
	[HWBLK_BEU]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 4, 0),
	[HWBLK_CEU]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 3, 0),
	[HWBLK_VEU2H0] = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 2, 0),
	[HWBLK_VPU]    = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 1, 0),
	[HWBLK_LCDC]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_B],  MSTPCR2, 0, 0),
पूर्ण;

अटल काष्ठा clk_lookup lookups[] = अणु
	/* मुख्य घड़ीs */
	CLKDEV_CON_ID("rclk", &r_clk),
	CLKDEV_CON_ID("extal", &extal_clk),
	CLKDEV_CON_ID("dll_clk", &dll_clk),
	CLKDEV_CON_ID("pll_clk", &pll_clk),

	/* DIV4 घड़ीs */
	CLKDEV_CON_ID("cpu_clk", &भाग4_clks[DIV4_I]),
	CLKDEV_CON_ID("umem_clk", &भाग4_clks[DIV4_U]),
	CLKDEV_CON_ID("shyway_clk", &भाग4_clks[DIV4_SH]),
	CLKDEV_CON_ID("bus_clk", &भाग4_clks[DIV4_B]),
	CLKDEV_CON_ID("b3_clk", &भाग4_clks[DIV4_B3]),
	CLKDEV_CON_ID("peripheral_clk", &भाग4_clks[DIV4_P]),
	CLKDEV_CON_ID("irda_clk", &भाग4_enable_clks[DIV4_IRDA]),
	CLKDEV_CON_ID("siua_clk", &भाग4_reparent_clks[DIV4_SIUA]),
	CLKDEV_CON_ID("siub_clk", &भाग4_reparent_clks[DIV4_SIUB]),

	/* DIV6 घड़ीs */
	CLKDEV_CON_ID("video_clk", &भाग6_clks[DIV6_V]),

	/* MSTP घड़ीs */
	CLKDEV_CON_ID("tlb0", &mstp_clks[HWBLK_TLB]),
	CLKDEV_CON_ID("ic0", &mstp_clks[HWBLK_IC]),
	CLKDEV_CON_ID("oc0", &mstp_clks[HWBLK_OC]),
	CLKDEV_CON_ID("l2c0", &mstp_clks[HWBLK_L2C]),
	CLKDEV_CON_ID("ilmem0", &mstp_clks[HWBLK_ILMEM]),
	CLKDEV_CON_ID("fpu0", &mstp_clks[HWBLK_FPU]),
	CLKDEV_CON_ID("intc0", &mstp_clks[HWBLK_INTC]),
	CLKDEV_DEV_ID("sh-dma-engine.0", &mstp_clks[HWBLK_DMAC0]),
	CLKDEV_CON_ID("sh0", &mstp_clks[HWBLK_SHYWAY]),
	CLKDEV_CON_ID("hudi0", &mstp_clks[HWBLK_HUDI]),
	CLKDEV_CON_ID("ubc0", &mstp_clks[HWBLK_UBC]),
	CLKDEV_ICK_ID("fck", "sh-cmt-32.0", &mstp_clks[HWBLK_CMT]),
	CLKDEV_DEV_ID("sh-wdt.0", &mstp_clks[HWBLK_RWDT]),
	CLKDEV_DEV_ID("sh-dma-engine.1", &mstp_clks[HWBLK_DMAC1]),
	CLKDEV_CON_ID("flctl0", &mstp_clks[HWBLK_FLCTL]),
	CLKDEV_DEV_ID("spi_sh_msiof.0", &mstp_clks[HWBLK_MSIOF0]),
	CLKDEV_DEV_ID("spi_sh_msiof.1", &mstp_clks[HWBLK_MSIOF1]),
	CLKDEV_DEV_ID("sh_mobile_meram.0", &mstp_clks[HWBLK_MERAM]),
	CLKDEV_DEV_ID("i2c-sh_mobile.0", &mstp_clks[HWBLK_IIC]),
	CLKDEV_CON_ID("rtc0", &mstp_clks[HWBLK_RTC]),
	CLKDEV_CON_ID("atapi0", &mstp_clks[HWBLK_ATAPI]),
	CLKDEV_CON_ID("adc0", &mstp_clks[HWBLK_ADC]),
	CLKDEV_CON_ID("tpu0", &mstp_clks[HWBLK_TPU]),
	CLKDEV_CON_ID("irda0", &mstp_clks[HWBLK_IRDA]),
	CLKDEV_CON_ID("tsif0", &mstp_clks[HWBLK_TSIF]),
	CLKDEV_CON_ID("icb0", &mstp_clks[HWBLK_ICB]),
	CLKDEV_DEV_ID("sh_mobile_sdhi.0", &mstp_clks[HWBLK_SDHI0]),
	CLKDEV_DEV_ID("sh_mobile_sdhi.1", &mstp_clks[HWBLK_SDHI1]),
	CLKDEV_DEV_ID("sh_keysc.0", &mstp_clks[HWBLK_KEYSC]),
	CLKDEV_CON_ID("usb0", &mstp_clks[HWBLK_USB]),
	CLKDEV_CON_ID("2dg0", &mstp_clks[HWBLK_2DG]),
	CLKDEV_DEV_ID("siu-pcm-audio", &mstp_clks[HWBLK_SIU]),
	CLKDEV_CON_ID("veu1", &mstp_clks[HWBLK_VEU2H1]),
	CLKDEV_DEV_ID("sh-vou.0", &mstp_clks[HWBLK_VOU]),
	CLKDEV_CON_ID("beu0", &mstp_clks[HWBLK_BEU]),
	CLKDEV_DEV_ID("ceu.0", &mstp_clks[HWBLK_CEU]),
	CLKDEV_CON_ID("veu0", &mstp_clks[HWBLK_VEU2H0]),
	CLKDEV_CON_ID("vpu0", &mstp_clks[HWBLK_VPU]),

	CLKDEV_ICK_ID("fck", "sh-tmu.0", &mstp_clks[HWBLK_TMU0]),
	CLKDEV_ICK_ID("fck", "sh-tmu.1", &mstp_clks[HWBLK_TMU1]),

	CLKDEV_ICK_ID("fck", "sh-sci.0", &mstp_clks[HWBLK_SCIF0]),
	CLKDEV_ICK_ID("fck", "sh-sci.1", &mstp_clks[HWBLK_SCIF1]),
	CLKDEV_ICK_ID("fck", "sh-sci.2", &mstp_clks[HWBLK_SCIF2]),
	CLKDEV_ICK_ID("fck", "sh-sci.3", &mstp_clks[HWBLK_SCIF3]),
	CLKDEV_ICK_ID("fck", "sh-sci.4", &mstp_clks[HWBLK_SCIF4]),
	CLKDEV_ICK_ID("fck", "sh-sci.5", &mstp_clks[HWBLK_SCIF5]),

	CLKDEV_DEV_ID("sh_mobile_lcdc_fb.0", &mstp_clks[HWBLK_LCDC]),
पूर्ण;

पूर्णांक __init arch_clk_init(व्योम)
अणु
	पूर्णांक k, ret = 0;

	/* स्वतःdetect extal or dll configuration */
	अगर (__raw_पढ़ोl(PLLCR) & 0x1000)
		pll_clk.parent = &dll_clk;
	अन्यथा
		pll_clk.parent = &extal_clk;

	क्रम (k = 0; !ret && (k < ARRAY_SIZE(मुख्य_clks)); k++)
		ret |= clk_रेजिस्टर(मुख्य_clks[k]);

	clkdev_add_table(lookups, ARRAY_SIZE(lookups));

	अगर (!ret)
		ret = sh_clk_भाग4_रेजिस्टर(भाग4_clks, DIV4_NR, &भाग4_table);

	अगर (!ret)
		ret = sh_clk_भाग4_enable_रेजिस्टर(भाग4_enable_clks,
					DIV4_ENABLE_NR, &भाग4_table);

	अगर (!ret)
		ret = sh_clk_भाग4_reparent_रेजिस्टर(भाग4_reparent_clks,
					DIV4_REPARENT_NR, &भाग4_table);

	अगर (!ret)
		ret = sh_clk_भाग6_रेजिस्टर(भाग6_clks, DIV6_NR);

	अगर (!ret)
		ret = sh_clk_mstp_रेजिस्टर(mstp_clks, HWBLK_NR);

	वापस ret;
पूर्ण
