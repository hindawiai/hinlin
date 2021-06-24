<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4a/घड़ी-sh7786.c
 *
 * SH7786 support क्रम the घड़ी framework
 *
 *  Copyright (C) 2010  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/clkdev.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/freq.h>

/*
 * Default rate क्रम the root input घड़ी, reset this with clk_set_rate()
 * from the platक्रमm code.
 */
अटल काष्ठा clk extal_clk = अणु
	.rate		= 33333333,
पूर्ण;

अटल अचिन्हित दीर्घ pll_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक multiplier;

	/*
	 * Clock modes 0, 1, and 2 use an x64 multiplier against PLL1,
	 * जबतक modes 3, 4, and 5 use an x32.
	 */
	multiplier = (sh_mv.mv_mode_pins() & 0xf) < 3 ? 64 : 32;

	वापस clk->parent->rate * multiplier;
पूर्ण

अटल काष्ठा sh_clk_ops pll_clk_ops = अणु
	.recalc		= pll_recalc,
पूर्ण;

अटल काष्ठा clk pll_clk = अणु
	.ops		= &pll_clk_ops,
	.parent		= &extal_clk,
	.flags		= CLK_ENABLE_ON_INIT,
पूर्ण;

अटल काष्ठा clk *clks[] = अणु
	&extal_clk,
	&pll_clk,
पूर्ण;

अटल अचिन्हित पूर्णांक भाग2[] = अणु 1, 2, 4, 6, 8, 12, 16, 18,
			       24, 32, 36, 48 पूर्ण;

अटल काष्ठा clk_भाग_mult_table भाग4_भाग_mult_table = अणु
	.भागisors = भाग2,
	.nr_भागisors = ARRAY_SIZE(भाग2),
पूर्ण;

अटल काष्ठा clk_भाग4_table भाग4_table = अणु
	.भाग_mult_table = &भाग4_भाग_mult_table,
पूर्ण;

क्रमागत अणु DIV4_I, DIV4_SH, DIV4_B, DIV4_DDR, DIV4_DU, DIV4_P, DIV4_NR पूर्ण;

#घोषणा DIV4(_bit, _mask, _flags) \
  SH_CLK_DIV4(&pll_clk, FRQMR1, _bit, _mask, _flags)

काष्ठा clk भाग4_clks[DIV4_NR] = अणु
	[DIV4_P] = DIV4(0, 0x0b40, 0),
	[DIV4_DU] = DIV4(4, 0x0010, 0),
	[DIV4_DDR] = DIV4(12, 0x0002, CLK_ENABLE_ON_INIT),
	[DIV4_B] = DIV4(16, 0x0360, CLK_ENABLE_ON_INIT),
	[DIV4_SH] = DIV4(20, 0x0002, CLK_ENABLE_ON_INIT),
	[DIV4_I] = DIV4(28, 0x0006, CLK_ENABLE_ON_INIT),
पूर्ण;

#घोषणा MSTPCR0		0xffc40030
#घोषणा MSTPCR1		0xffc40034

क्रमागत अणु MSTP029, MSTP028, MSTP027, MSTP026, MSTP025, MSTP024,
       MSTP023, MSTP022, MSTP021, MSTP020, MSTP017, MSTP016,
       MSTP015, MSTP014, MSTP011, MSTP010, MSTP009, MSTP008,
       MSTP005, MSTP004, MSTP002,
       MSTP112, MSTP110, MSTP109, MSTP108,
       MSTP105, MSTP104, MSTP103, MSTP102,
       MSTP_NR पूर्ण;

अटल काष्ठा clk mstp_clks[MSTP_NR] = अणु
	/* MSTPCR0 */
	[MSTP029] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 29, 0),
	[MSTP028] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 28, 0),
	[MSTP027] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 27, 0),
	[MSTP026] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 26, 0),
	[MSTP025] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 25, 0),
	[MSTP024] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 24, 0),
	[MSTP023] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 23, 0),
	[MSTP022] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 22, 0),
	[MSTP021] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 21, 0),
	[MSTP020] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 20, 0),
	[MSTP017] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 17, 0),
	[MSTP016] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 16, 0),
	[MSTP015] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 15, 0),
	[MSTP014] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 14, 0),
	[MSTP011] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 11, 0),
	[MSTP010] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 10, 0),
	[MSTP009] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 9, 0),
	[MSTP008] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 8, 0),
	[MSTP005] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 5, 0),
	[MSTP004] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 4, 0),
	[MSTP002] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 2, 0),

	/* MSTPCR1 */
	[MSTP112] = SH_CLK_MSTP32(शून्य, MSTPCR1, 12, 0),
	[MSTP110] = SH_CLK_MSTP32(शून्य, MSTPCR1, 10, 0),
	[MSTP109] = SH_CLK_MSTP32(शून्य, MSTPCR1, 9, 0),
	[MSTP108] = SH_CLK_MSTP32(शून्य, MSTPCR1, 8, 0),
	[MSTP105] = SH_CLK_MSTP32(शून्य, MSTPCR1, 5, 0),
	[MSTP104] = SH_CLK_MSTP32(शून्य, MSTPCR1, 4, 0),
	[MSTP103] = SH_CLK_MSTP32(शून्य, MSTPCR1, 3, 0),
	[MSTP102] = SH_CLK_MSTP32(शून्य, MSTPCR1, 2, 0),
पूर्ण;

अटल काष्ठा clk_lookup lookups[] = अणु
	/* मुख्य घड़ीs */
	CLKDEV_CON_ID("extal", &extal_clk),
	CLKDEV_CON_ID("pll_clk", &pll_clk),

	/* DIV4 घड़ीs */
	CLKDEV_CON_ID("peripheral_clk", &भाग4_clks[DIV4_P]),
	CLKDEV_CON_ID("du_clk", &भाग4_clks[DIV4_DU]),
	CLKDEV_CON_ID("ddr_clk", &भाग4_clks[DIV4_DDR]),
	CLKDEV_CON_ID("bus_clk", &भाग4_clks[DIV4_B]),
	CLKDEV_CON_ID("shyway_clk", &भाग4_clks[DIV4_SH]),
	CLKDEV_CON_ID("cpu_clk", &भाग4_clks[DIV4_I]),

	/* MSTP32 घड़ीs */
	CLKDEV_ICK_ID("fck", "sh-sci.5", &mstp_clks[MSTP029]),
	CLKDEV_ICK_ID("fck", "sh-sci.4", &mstp_clks[MSTP028]),
	CLKDEV_ICK_ID("fck", "sh-sci.3", &mstp_clks[MSTP027]),
	CLKDEV_ICK_ID("fck", "sh-sci.2", &mstp_clks[MSTP026]),
	CLKDEV_ICK_ID("fck", "sh-sci.1", &mstp_clks[MSTP025]),
	CLKDEV_ICK_ID("fck", "sh-sci.0", &mstp_clks[MSTP024]),

	CLKDEV_CON_ID("ssi3_fck", &mstp_clks[MSTP023]),
	CLKDEV_CON_ID("ssi2_fck", &mstp_clks[MSTP022]),
	CLKDEV_CON_ID("ssi1_fck", &mstp_clks[MSTP021]),
	CLKDEV_CON_ID("ssi0_fck", &mstp_clks[MSTP020]),
	CLKDEV_CON_ID("hac1_fck", &mstp_clks[MSTP017]),
	CLKDEV_CON_ID("hac0_fck", &mstp_clks[MSTP016]),
	CLKDEV_CON_ID("i2c1_fck", &mstp_clks[MSTP015]),
	CLKDEV_CON_ID("i2c0_fck", &mstp_clks[MSTP014]),

	CLKDEV_ICK_ID("fck", "sh-tmu.0", &mstp_clks[MSTP008]),
	CLKDEV_ICK_ID("fck", "sh-tmu.1", &mstp_clks[MSTP009]),
	CLKDEV_ICK_ID("fck", "sh-tmu.2", &mstp_clks[MSTP010]),
	CLKDEV_ICK_ID("fck", "sh-tmu.3", &mstp_clks[MSTP011]),

	CLKDEV_CON_ID("sdif1_fck", &mstp_clks[MSTP005]),
	CLKDEV_CON_ID("sdif0_fck", &mstp_clks[MSTP004]),
	CLKDEV_CON_ID("hspi_fck", &mstp_clks[MSTP002]),
	CLKDEV_CON_ID("usb_fck", &mstp_clks[MSTP112]),
	CLKDEV_CON_ID("pcie2_fck", &mstp_clks[MSTP110]),
	CLKDEV_CON_ID("pcie1_fck", &mstp_clks[MSTP109]),
	CLKDEV_CON_ID("pcie0_fck", &mstp_clks[MSTP108]),
	CLKDEV_CON_ID("dmac_11_6_fck", &mstp_clks[MSTP105]),
	CLKDEV_CON_ID("dmac_5_0_fck", &mstp_clks[MSTP104]),
	CLKDEV_CON_ID("du_fck", &mstp_clks[MSTP103]),
	CLKDEV_CON_ID("ether_fck", &mstp_clks[MSTP102]),
पूर्ण;

पूर्णांक __init arch_clk_init(व्योम)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < ARRAY_SIZE(clks); i++)
		ret |= clk_रेजिस्टर(clks[i]);

	clkdev_add_table(lookups, ARRAY_SIZE(lookups));

	अगर (!ret)
		ret = sh_clk_भाग4_रेजिस्टर(भाग4_clks, ARRAY_SIZE(भाग4_clks),
					   &भाग4_table);
	अगर (!ret)
		ret = sh_clk_mstp_रेजिस्टर(mstp_clks, MSTP_NR);

	वापस ret;
पूर्ण
