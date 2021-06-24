<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4a/घड़ी-sh7722.c
 *
 * SH7722 घड़ी framework support
 *
 * Copyright (C) 2009 Magnus Damm
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/clkdev.h>
#समावेश <linux/sh_clk.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <cpu/sh7722.h>

/* SH7722 रेजिस्टरs */
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

/* The dll block multiplies the 32khz r_clk, may be used instead of extal */
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

#घोषणा DIV4(_reg, _bit, _mask, _flags) \
  SH_CLK_DIV4(&pll_clk, _reg, _bit, _mask, _flags)

क्रमागत अणु DIV4_I, DIV4_U, DIV4_SH, DIV4_B, DIV4_B3, DIV4_P, DIV4_NR पूर्ण;

काष्ठा clk भाग4_clks[DIV4_NR] = अणु
	[DIV4_I] = DIV4(FRQCR, 20, 0x1fef, CLK_ENABLE_ON_INIT),
	[DIV4_U] = DIV4(FRQCR, 16, 0x1fff, CLK_ENABLE_ON_INIT),
	[DIV4_SH] = DIV4(FRQCR, 12, 0x1fff, CLK_ENABLE_ON_INIT),
	[DIV4_B] = DIV4(FRQCR, 8, 0x1fff, CLK_ENABLE_ON_INIT),
	[DIV4_B3] = DIV4(FRQCR, 4, 0x1fff, CLK_ENABLE_ON_INIT),
	[DIV4_P] = DIV4(FRQCR, 0, 0x1fff, 0),
पूर्ण;

क्रमागत अणु DIV4_IRDA, DIV4_ENABLE_NR पूर्ण;

काष्ठा clk भाग4_enable_clks[DIV4_ENABLE_NR] = अणु
	[DIV4_IRDA] = DIV4(IRDACLKCR, 0, 0x1fff, 0),
पूर्ण;

क्रमागत अणु DIV4_SIUA, DIV4_SIUB, DIV4_REPARENT_NR पूर्ण;

काष्ठा clk भाग4_reparent_clks[DIV4_REPARENT_NR] = अणु
	[DIV4_SIUA] = DIV4(SCLKACR, 0, 0x1fff, 0),
	[DIV4_SIUB] = DIV4(SCLKBCR, 0, 0x1fff, 0),
पूर्ण;

क्रमागत अणु DIV6_V, DIV6_NR पूर्ण;

काष्ठा clk भाग6_clks[DIV6_NR] = अणु
	[DIV6_V] = SH_CLK_DIV6(&pll_clk, VCLKCR, 0),
पूर्ण;

अटल काष्ठा clk mstp_clks[HWBLK_NR] = अणु
	[HWBLK_URAM]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_U], MSTPCR0, 28, CLK_ENABLE_ON_INIT),
	[HWBLK_XYMEM] = SH_CLK_MSTP32(&भाग4_clks[DIV4_B], MSTPCR0, 26, CLK_ENABLE_ON_INIT),
	[HWBLK_TMU]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 15, 0),
	[HWBLK_CMT]   = SH_CLK_MSTP32(&r_clk,		  MSTPCR0, 14, 0),
	[HWBLK_RWDT]  = SH_CLK_MSTP32(&r_clk,		  MSTPCR0, 13, 0),
	[HWBLK_FLCTL] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 10, 0),
	[HWBLK_SCIF0] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 7, 0),
	[HWBLK_SCIF1] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 6, 0),
	[HWBLK_SCIF2] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 5, 0),

	[HWBLK_IIC]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR1, 9, 0),
	[HWBLK_RTC]   = SH_CLK_MSTP32(&r_clk,		  MSTPCR1, 8, 0),

	[HWBLK_SDHI]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR2, 18, 0),
	[HWBLK_KEYSC] = SH_CLK_MSTP32(&r_clk,		  MSTPCR2, 14, 0),
	[HWBLK_USBF]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR2, 11, 0),
	[HWBLK_2DG]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_B], MSTPCR2, 9, 0),
	[HWBLK_SIU]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_B], MSTPCR2, 8, 0),
	[HWBLK_JPU]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_B], MSTPCR2, 6, 0),
	[HWBLK_VOU]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_B], MSTPCR2, 5, 0),
	[HWBLK_BEU]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_B], MSTPCR2, 4, 0),
	[HWBLK_CEU]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_B], MSTPCR2, 3, 0),
	[HWBLK_VEU]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_B], MSTPCR2, 2, 0),
	[HWBLK_VPU]   = SH_CLK_MSTP32(&भाग4_clks[DIV4_B], MSTPCR2, 1, 0),
	[HWBLK_LCDC]  = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR2, 0, 0),
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
	CLKDEV_CON_ID("uram0", &mstp_clks[HWBLK_URAM]),
	CLKDEV_CON_ID("xymem0", &mstp_clks[HWBLK_XYMEM]),

	CLKDEV_ICK_ID("fck", "sh-tmu.0", &mstp_clks[HWBLK_TMU]),

	CLKDEV_ICK_ID("fck", "sh-cmt-32.0", &mstp_clks[HWBLK_CMT]),
	CLKDEV_DEV_ID("sh-wdt.0", &mstp_clks[HWBLK_RWDT]),
	CLKDEV_CON_ID("flctl0", &mstp_clks[HWBLK_FLCTL]),

	CLKDEV_DEV_ID("sh-sci.0", &mstp_clks[HWBLK_SCIF0]),
	CLKDEV_DEV_ID("sh-sci.1", &mstp_clks[HWBLK_SCIF1]),
	CLKDEV_DEV_ID("sh-sci.2", &mstp_clks[HWBLK_SCIF2]),

	CLKDEV_DEV_ID("i2c-sh_mobile.0", &mstp_clks[HWBLK_IIC]),
	CLKDEV_CON_ID("rtc0", &mstp_clks[HWBLK_RTC]),
	CLKDEV_DEV_ID("sh_mobile_sdhi.0", &mstp_clks[HWBLK_SDHI]),
	CLKDEV_DEV_ID("sh_keysc.0", &mstp_clks[HWBLK_KEYSC]),
	CLKDEV_CON_ID("usbf0", &mstp_clks[HWBLK_USBF]),
	CLKDEV_CON_ID("2dg0", &mstp_clks[HWBLK_2DG]),
	CLKDEV_DEV_ID("siu-pcm-audio", &mstp_clks[HWBLK_SIU]),
	CLKDEV_DEV_ID("sh-vou.0", &mstp_clks[HWBLK_VOU]),
	CLKDEV_CON_ID("jpu0", &mstp_clks[HWBLK_JPU]),
	CLKDEV_CON_ID("beu0", &mstp_clks[HWBLK_BEU]),
	CLKDEV_DEV_ID("renesas-ceu.0", &mstp_clks[HWBLK_CEU]),
	CLKDEV_CON_ID("veu0", &mstp_clks[HWBLK_VEU]),
	CLKDEV_CON_ID("vpu0", &mstp_clks[HWBLK_VPU]),
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
		ret = clk_रेजिस्टर(मुख्य_clks[k]);

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
