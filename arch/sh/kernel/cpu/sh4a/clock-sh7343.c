<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4a/घड़ी-sh7343.c
 *
 * SH7343 घड़ी framework support
 *
 * Copyright (C) 2009 Magnus Damm
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/clkdev.h>
#समावेश <यंत्र/घड़ी.h>

/* SH7343 रेजिस्टरs */
#घोषणा FRQCR		0xa4150000
#घोषणा VCLKCR		0xa4150004
#घोषणा SCLKACR		0xa4150008
#घोषणा SCLKBCR		0xa415000c
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

	अगर (__raw_पढ़ोl(PLLCR) & 0x4000)
		mult = (((__raw_पढ़ोl(FRQCR) >> 24) & 0x1f) + 1);

	वापस clk->parent->rate * mult;
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

क्रमागत अणु DIV4_I, DIV4_U, DIV4_SH, DIV4_B, DIV4_B3, DIV4_P,
       DIV4_SIUA, DIV4_SIUB, DIV4_NR पूर्ण;

#घोषणा DIV4(_reg, _bit, _mask, _flags) \
  SH_CLK_DIV4(&pll_clk, _reg, _bit, _mask, _flags)

काष्ठा clk भाग4_clks[DIV4_NR] = अणु
	[DIV4_I] = DIV4(FRQCR, 20, 0x1fff, CLK_ENABLE_ON_INIT),
	[DIV4_U] = DIV4(FRQCR, 16, 0x1fff, CLK_ENABLE_ON_INIT),
	[DIV4_SH] = DIV4(FRQCR, 12, 0x1fff, CLK_ENABLE_ON_INIT),
	[DIV4_B] = DIV4(FRQCR, 8, 0x1fff, CLK_ENABLE_ON_INIT),
	[DIV4_B3] = DIV4(FRQCR, 4, 0x1fff, CLK_ENABLE_ON_INIT),
	[DIV4_P] = DIV4(FRQCR, 0, 0x1fff, 0),
	[DIV4_SIUA] = DIV4(SCLKACR, 0, 0x1fff, 0),
	[DIV4_SIUB] = DIV4(SCLKBCR, 0, 0x1fff, 0),
पूर्ण;

क्रमागत अणु DIV6_V, DIV6_NR पूर्ण;

काष्ठा clk भाग6_clks[DIV6_NR] = अणु
	[DIV6_V] = SH_CLK_DIV6(&pll_clk, VCLKCR, 0),
पूर्ण;

#घोषणा MSTP(_parent, _reg, _bit, _flags) \
  SH_CLK_MSTP32(_parent, _reg, _bit, _flags)

क्रमागत अणु MSTP031, MSTP030, MSTP029, MSTP028, MSTP026,
       MSTP023, MSTP022, MSTP021, MSTP020, MSTP019, MSTP018, MSTP017, MSTP016,
       MSTP015, MSTP014, MSTP013, MSTP012, MSTP011, MSTP010,
       MSTP007, MSTP006, MSTP005, MSTP004, MSTP003, MSTP002, MSTP001,
       MSTP109, MSTP108, MSTP100,
       MSTP225, MSTP224, MSTP218, MSTP217, MSTP216,
       MSTP214, MSTP213, MSTP212, MSTP211, MSTP208,
       MSTP206, MSTP205, MSTP204, MSTP203, MSTP202, MSTP201, MSTP200,
       MSTP_NR पूर्ण;

अटल काष्ठा clk mstp_clks[MSTP_NR] = अणु
	[MSTP031] = MSTP(&भाग4_clks[DIV4_I], MSTPCR0, 31, CLK_ENABLE_ON_INIT),
	[MSTP030] = MSTP(&भाग4_clks[DIV4_I], MSTPCR0, 30, CLK_ENABLE_ON_INIT),
	[MSTP029] = MSTP(&भाग4_clks[DIV4_I], MSTPCR0, 29, CLK_ENABLE_ON_INIT),
	[MSTP028] = MSTP(&भाग4_clks[DIV4_U], MSTPCR0, 28, CLK_ENABLE_ON_INIT),
	[MSTP026] = MSTP(&भाग4_clks[DIV4_B], MSTPCR0, 26, CLK_ENABLE_ON_INIT),
	[MSTP023] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 23, 0),
	[MSTP022] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 22, 0),
	[MSTP021] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 21, 0),
	[MSTP020] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 20, 0),
	[MSTP019] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 19, 0),
	[MSTP017] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 17, 0),
	[MSTP015] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 15, 0),
	[MSTP014] = MSTP(&r_clk, MSTPCR0, 14, 0),
	[MSTP013] = MSTP(&r_clk, MSTPCR0, 13, 0),
	[MSTP011] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 11, 0),
	[MSTP010] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 10, 0),
	[MSTP007] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 7, 0),
	[MSTP006] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 6, 0),
	[MSTP005] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 5, 0),
	[MSTP004] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 4, 0),
	[MSTP003] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 3, 0),
	[MSTP002] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 2, 0),
	[MSTP001] = MSTP(&भाग4_clks[DIV4_P], MSTPCR0, 1, 0),

	[MSTP109] = MSTP(&भाग4_clks[DIV4_P], MSTPCR1, 9, 0),
	[MSTP108] = MSTP(&भाग4_clks[DIV4_P], MSTPCR1, 8, 0),

	[MSTP225] = MSTP(&भाग4_clks[DIV4_P], MSTPCR2, 25, 0),
	[MSTP224] = MSTP(&भाग4_clks[DIV4_P], MSTPCR2, 24, 0),
	[MSTP218] = MSTP(&भाग4_clks[DIV4_P], MSTPCR2, 18, 0),
	[MSTP217] = MSTP(&भाग4_clks[DIV4_P], MSTPCR2, 17, 0),
	[MSTP216] = MSTP(&भाग4_clks[DIV4_P], MSTPCR2, 16, 0),
	[MSTP214] = MSTP(&r_clk, MSTPCR2, 14, 0),
	[MSTP213] = MSTP(&भाग4_clks[DIV4_P], MSTPCR2, 13, 0),
	[MSTP212] = MSTP(&भाग4_clks[DIV4_P], MSTPCR2, 12, 0),
	[MSTP211] = MSTP(&भाग4_clks[DIV4_P], MSTPCR2, 11, 0),
	[MSTP208] = MSTP(&भाग4_clks[DIV4_B], MSTPCR2, 8, 0),
	[MSTP206] = MSTP(&भाग4_clks[DIV4_B], MSTPCR2, 6, CLK_ENABLE_ON_INIT),
	[MSTP205] = MSTP(&भाग4_clks[DIV4_B], MSTPCR2, 5, 0),
	[MSTP204] = MSTP(&भाग4_clks[DIV4_B], MSTPCR2, 4, 0),
	[MSTP203] = MSTP(&भाग4_clks[DIV4_B], MSTPCR2, 3, 0),
	[MSTP202] = MSTP(&भाग4_clks[DIV4_B], MSTPCR2, 2, CLK_ENABLE_ON_INIT),
	[MSTP201] = MSTP(&भाग4_clks[DIV4_B], MSTPCR2, 1, CLK_ENABLE_ON_INIT),
	[MSTP200] = MSTP(&भाग4_clks[DIV4_B], MSTPCR2, 0, 0),
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
	CLKDEV_CON_ID("siua_clk", &भाग4_clks[DIV4_SIUA]),
	CLKDEV_CON_ID("siub_clk", &भाग4_clks[DIV4_SIUB]),

	/* DIV6 घड़ीs */
	CLKDEV_CON_ID("video_clk", &भाग6_clks[DIV6_V]),

	/* MSTP32 घड़ीs */
	CLKDEV_CON_ID("tlb0", &mstp_clks[MSTP031]),
	CLKDEV_CON_ID("ic0", &mstp_clks[MSTP030]),
	CLKDEV_CON_ID("oc0", &mstp_clks[MSTP029]),
	CLKDEV_CON_ID("uram0", &mstp_clks[MSTP028]),
	CLKDEV_CON_ID("xymem0", &mstp_clks[MSTP026]),
	CLKDEV_CON_ID("intc3", &mstp_clks[MSTP023]),
	CLKDEV_CON_ID("intc0", &mstp_clks[MSTP022]),
	CLKDEV_CON_ID("dmac0", &mstp_clks[MSTP021]),
	CLKDEV_CON_ID("sh0", &mstp_clks[MSTP020]),
	CLKDEV_CON_ID("hudi0", &mstp_clks[MSTP019]),
	CLKDEV_CON_ID("ubc0", &mstp_clks[MSTP017]),
	CLKDEV_CON_ID("tmu_fck", &mstp_clks[MSTP015]),
	CLKDEV_ICK_ID("fck", "sh-cmt-32.0", &mstp_clks[MSTP014]),
	CLKDEV_CON_ID("rwdt0", &mstp_clks[MSTP013]),
	CLKDEV_CON_ID("mfi0", &mstp_clks[MSTP011]),
	CLKDEV_CON_ID("flctl0", &mstp_clks[MSTP010]),

	CLKDEV_ICK_ID("fck", "sh-sci.0", &mstp_clks[MSTP007]),
	CLKDEV_ICK_ID("fck", "sh-sci.1", &mstp_clks[MSTP006]),
	CLKDEV_ICK_ID("fck", "sh-sci.2", &mstp_clks[MSTP005]),
	CLKDEV_ICK_ID("fck", "sh-sci.3", &mstp_clks[MSTP004]),

	CLKDEV_CON_ID("sio0", &mstp_clks[MSTP003]),
	CLKDEV_CON_ID("siof0", &mstp_clks[MSTP002]),
	CLKDEV_CON_ID("siof1", &mstp_clks[MSTP001]),
	CLKDEV_DEV_ID("i2c-sh_mobile.0", &mstp_clks[MSTP109]),
	CLKDEV_DEV_ID("i2c-sh_mobile.1", &mstp_clks[MSTP108]),
	CLKDEV_CON_ID("tpu0", &mstp_clks[MSTP225]),
	CLKDEV_CON_ID("irda0", &mstp_clks[MSTP224]),
	CLKDEV_CON_ID("sdhi0", &mstp_clks[MSTP218]),
	CLKDEV_CON_ID("mmcif0", &mstp_clks[MSTP217]),
	CLKDEV_CON_ID("sim0", &mstp_clks[MSTP216]),
	CLKDEV_CON_ID("keysc0", &mstp_clks[MSTP214]),
	CLKDEV_CON_ID("tsif0", &mstp_clks[MSTP213]),
	CLKDEV_CON_ID("s3d40", &mstp_clks[MSTP212]),
	CLKDEV_CON_ID("usbf0", &mstp_clks[MSTP211]),
	CLKDEV_CON_ID("siu0", &mstp_clks[MSTP208]),
	CLKDEV_CON_ID("jpu0", &mstp_clks[MSTP206]),
	CLKDEV_CON_ID("vou0", &mstp_clks[MSTP205]),
	CLKDEV_CON_ID("beu0", &mstp_clks[MSTP204]),
	CLKDEV_CON_ID("ceu0", &mstp_clks[MSTP203]),
	CLKDEV_CON_ID("veu0", &mstp_clks[MSTP202]),
	CLKDEV_CON_ID("vpu0", &mstp_clks[MSTP201]),
	CLKDEV_CON_ID("lcdc0", &mstp_clks[MSTP200]),
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
		ret = sh_clk_भाग6_रेजिस्टर(भाग6_clks, DIV6_NR);

	अगर (!ret)
		ret = sh_clk_mstp_रेजिस्टर(mstp_clks, MSTP_NR);

	वापस ret;
पूर्ण
