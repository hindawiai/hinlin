<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh2a/घड़ी-sh7269.c
 *
 * SH7269 घड़ी framework support
 *
 * Copyright (C) 2012  Phil Edworthy
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/clkdev.h>
#समावेश <यंत्र/घड़ी.h>

/* SH7269 रेजिस्टरs */
#घोषणा FRQCR		0xfffe0010
#घोषणा STBCR3 		0xfffe0408
#घोषणा STBCR4 		0xfffe040c
#घोषणा STBCR5 		0xfffe0410
#घोषणा STBCR6 		0xfffe0414
#घोषणा STBCR7 		0xfffe0418

#घोषणा PLL_RATE 20

/* Fixed 32 KHz root घड़ी क्रम RTC */
अटल काष्ठा clk r_clk = अणु
	.rate           = 32768,
पूर्ण;

/*
 * Default rate क्रम the root input घड़ी, reset this with clk_set_rate()
 * from the platक्रमm code.
 */
अटल काष्ठा clk extal_clk = अणु
	.rate		= 13340000,
पूर्ण;

अटल अचिन्हित दीर्घ pll_recalc(काष्ठा clk *clk)
अणु
	वापस clk->parent->rate * PLL_RATE;
पूर्ण

अटल काष्ठा sh_clk_ops pll_clk_ops = अणु
	.recalc		= pll_recalc,
पूर्ण;

अटल काष्ठा clk pll_clk = अणु
	.ops		= &pll_clk_ops,
	.parent		= &extal_clk,
	.flags		= CLK_ENABLE_ON_INIT,
पूर्ण;

अटल अचिन्हित दीर्घ peripheral0_recalc(काष्ठा clk *clk)
अणु
	वापस clk->parent->rate / 8;
पूर्ण

अटल काष्ठा sh_clk_ops peripheral0_clk_ops = अणु
	.recalc		= peripheral0_recalc,
पूर्ण;

अटल काष्ठा clk peripheral0_clk = अणु
	.ops		= &peripheral0_clk_ops,
	.parent		= &pll_clk,
	.flags		= CLK_ENABLE_ON_INIT,
पूर्ण;

अटल अचिन्हित दीर्घ peripheral1_recalc(काष्ठा clk *clk)
अणु
	वापस clk->parent->rate / 4;
पूर्ण

अटल काष्ठा sh_clk_ops peripheral1_clk_ops = अणु
	.recalc		= peripheral1_recalc,
पूर्ण;

अटल काष्ठा clk peripheral1_clk = अणु
	.ops		= &peripheral1_clk_ops,
	.parent		= &pll_clk,
	.flags		= CLK_ENABLE_ON_INIT,
पूर्ण;

काष्ठा clk *मुख्य_clks[] = अणु
	&r_clk,
	&extal_clk,
	&pll_clk,
	&peripheral0_clk,
	&peripheral1_clk,
पूर्ण;

अटल पूर्णांक भाग2[] = अणु 1, 2, 0, 4 पूर्ण;

अटल काष्ठा clk_भाग_mult_table भाग4_भाग_mult_table = अणु
	.भागisors = भाग2,
	.nr_भागisors = ARRAY_SIZE(भाग2),
पूर्ण;

अटल काष्ठा clk_भाग4_table भाग4_table = अणु
	.भाग_mult_table = &भाग4_भाग_mult_table,
पूर्ण;

क्रमागत अणु DIV4_I, DIV4_B,
       DIV4_NR पूर्ण;

#घोषणा DIV4(_reg, _bit, _mask, _flags) \
  SH_CLK_DIV4(&pll_clk, _reg, _bit, _mask, _flags)

/* The mask field specअगरies the भाग2 entries that are valid */
काष्ठा clk भाग4_clks[DIV4_NR] = अणु
	[DIV4_I]  = DIV4(FRQCR, 8, 0xB, CLK_ENABLE_REG_16BIT
					| CLK_ENABLE_ON_INIT),
	[DIV4_B]  = DIV4(FRQCR, 4, 0xA, CLK_ENABLE_REG_16BIT
					| CLK_ENABLE_ON_INIT),
पूर्ण;

क्रमागत अणु MSTP72,
	MSTP60,
	MSTP47, MSTP46, MSTP45, MSTP44, MSTP43, MSTP42, MSTP41, MSTP40,
	MSTP35, MSTP32, MSTP30,
	MSTP_NR पूर्ण;

अटल काष्ठा clk mstp_clks[MSTP_NR] = अणु
	[MSTP72] = SH_CLK_MSTP8(&peripheral0_clk, STBCR7, 2, 0), /* CMT */
	[MSTP60] = SH_CLK_MSTP8(&peripheral1_clk, STBCR6, 0, 0), /* USB */
	[MSTP47] = SH_CLK_MSTP8(&peripheral1_clk, STBCR4, 7, 0), /* SCIF0 */
	[MSTP46] = SH_CLK_MSTP8(&peripheral1_clk, STBCR4, 6, 0), /* SCIF1 */
	[MSTP45] = SH_CLK_MSTP8(&peripheral1_clk, STBCR4, 5, 0), /* SCIF2 */
	[MSTP44] = SH_CLK_MSTP8(&peripheral1_clk, STBCR4, 4, 0), /* SCIF3 */
	[MSTP43] = SH_CLK_MSTP8(&peripheral1_clk, STBCR4, 3, 0), /* SCIF4 */
	[MSTP42] = SH_CLK_MSTP8(&peripheral1_clk, STBCR4, 2, 0), /* SCIF5 */
	[MSTP41] = SH_CLK_MSTP8(&peripheral1_clk, STBCR4, 1, 0), /* SCIF6 */
	[MSTP40] = SH_CLK_MSTP8(&peripheral1_clk, STBCR4, 0, 0), /* SCIF7 */
	[MSTP35] = SH_CLK_MSTP8(&peripheral0_clk, STBCR3, 5, 0), /* MTU2 */
	[MSTP32] = SH_CLK_MSTP8(&peripheral1_clk, STBCR3, 2, 0), /* ADC */
	[MSTP30] = SH_CLK_MSTP8(&r_clk, STBCR3, 0, 0), /* RTC */
पूर्ण;

अटल काष्ठा clk_lookup lookups[] = अणु
	/* मुख्य घड़ीs */
	CLKDEV_CON_ID("rclk", &r_clk),
	CLKDEV_CON_ID("extal", &extal_clk),
	CLKDEV_CON_ID("pll_clk", &pll_clk),
	CLKDEV_CON_ID("peripheral_clk", &peripheral1_clk),

	/* DIV4 घड़ीs */
	CLKDEV_CON_ID("cpu_clk", &भाग4_clks[DIV4_I]),
	CLKDEV_CON_ID("bus_clk", &भाग4_clks[DIV4_B]),

	/* MSTP घड़ीs */
	CLKDEV_ICK_ID("fck", "sh-sci.0", &mstp_clks[MSTP47]),
	CLKDEV_ICK_ID("fck", "sh-sci.1", &mstp_clks[MSTP46]),
	CLKDEV_ICK_ID("fck", "sh-sci.2", &mstp_clks[MSTP45]),
	CLKDEV_ICK_ID("fck", "sh-sci.3", &mstp_clks[MSTP44]),
	CLKDEV_ICK_ID("fck", "sh-sci.4", &mstp_clks[MSTP43]),
	CLKDEV_ICK_ID("fck", "sh-sci.5", &mstp_clks[MSTP42]),
	CLKDEV_ICK_ID("fck", "sh-sci.6", &mstp_clks[MSTP41]),
	CLKDEV_ICK_ID("fck", "sh-sci.7", &mstp_clks[MSTP40]),
	CLKDEV_ICK_ID("fck", "sh-cmt-16.0", &mstp_clks[MSTP72]),
	CLKDEV_CON_ID("usb0", &mstp_clks[MSTP60]),
	CLKDEV_ICK_ID("fck", "sh-mtu2", &mstp_clks[MSTP35]),
	CLKDEV_CON_ID("adc0", &mstp_clks[MSTP32]),
	CLKDEV_CON_ID("rtc0", &mstp_clks[MSTP30]),
पूर्ण;

पूर्णांक __init arch_clk_init(व्योम)
अणु
	पूर्णांक k, ret = 0;

	क्रम (k = 0; !ret && (k < ARRAY_SIZE(मुख्य_clks)); k++)
		ret = clk_रेजिस्टर(मुख्य_clks[k]);

	clkdev_add_table(lookups, ARRAY_SIZE(lookups));

	अगर (!ret)
		ret = sh_clk_भाग4_रेजिस्टर(भाग4_clks, DIV4_NR, &भाग4_table);

	अगर (!ret)
		ret = sh_clk_mstp_रेजिस्टर(mstp_clks, MSTP_NR);

	वापस ret;
पूर्ण
