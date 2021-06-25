<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4a/घड़ी-sh7785.c
 *
 * SH7785 support क्रम the घड़ी framework
 *
 *  Copyright (C) 2007 - 2010  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/cpufreq.h>
#समावेश <linux/clkdev.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/freq.h>
#समावेश <cpu/sh7785.h>

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

	multiplier = test_mode_pin(MODE_PIN4) ? 36 : 72;

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

क्रमागत अणु DIV4_I, DIV4_U, DIV4_SH, DIV4_B, DIV4_DDR, DIV4_GA,
	DIV4_DU, DIV4_P, DIV4_NR पूर्ण;

#घोषणा DIV4(_bit, _mask, _flags) \
  SH_CLK_DIV4(&pll_clk, FRQMR1, _bit, _mask, _flags)

काष्ठा clk भाग4_clks[DIV4_NR] = अणु
	[DIV4_P] = DIV4(0, 0x0f80, 0),
	[DIV4_DU] = DIV4(4, 0x0ff0, 0),
	[DIV4_GA] = DIV4(8, 0x0030, 0),
	[DIV4_DDR] = DIV4(12, 0x000c, CLK_ENABLE_ON_INIT),
	[DIV4_B] = DIV4(16, 0x0fe0, CLK_ENABLE_ON_INIT),
	[DIV4_SH] = DIV4(20, 0x000c, CLK_ENABLE_ON_INIT),
	[DIV4_U] = DIV4(24, 0x000c, CLK_ENABLE_ON_INIT),
	[DIV4_I] = DIV4(28, 0x000e, CLK_ENABLE_ON_INIT),
पूर्ण;

#घोषणा MSTPCR0		0xffc80030
#घोषणा MSTPCR1		0xffc80034

क्रमागत अणु MSTP029, MSTP028, MSTP027, MSTP026, MSTP025, MSTP024,
       MSTP021, MSTP020, MSTP017, MSTP016,
       MSTP013, MSTP012, MSTP009, MSTP008, MSTP003, MSTP002,
       MSTP119, MSTP117, MSTP105, MSTP104, MSTP100,
       MSTP_NR पूर्ण;

अटल काष्ठा clk mstp_clks[MSTP_NR] = अणु
	/* MSTPCR0 */
	[MSTP029] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 29, 0),
	[MSTP028] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 28, 0),
	[MSTP027] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 27, 0),
	[MSTP026] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 26, 0),
	[MSTP025] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 25, 0),
	[MSTP024] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 24, 0),
	[MSTP021] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 21, 0),
	[MSTP020] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 20, 0),
	[MSTP017] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 17, 0),
	[MSTP016] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 16, 0),
	[MSTP013] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 13, 0),
	[MSTP012] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 12, 0),
	[MSTP009] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 9, 0),
	[MSTP008] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 8, 0),
	[MSTP003] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 3, 0),
	[MSTP002] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 2, 0),

	/* MSTPCR1 */
	[MSTP119] = SH_CLK_MSTP32(शून्य, MSTPCR1, 19, 0),
	[MSTP117] = SH_CLK_MSTP32(शून्य, MSTPCR1, 17, 0),
	[MSTP105] = SH_CLK_MSTP32(शून्य, MSTPCR1, 5, 0),
	[MSTP104] = SH_CLK_MSTP32(शून्य, MSTPCR1, 4, 0),
	[MSTP100] = SH_CLK_MSTP32(शून्य, MSTPCR1, 0, 0),
पूर्ण;

अटल काष्ठा clk_lookup lookups[] = अणु
	/* मुख्य घड़ीs */
	CLKDEV_CON_ID("extal", &extal_clk),
	CLKDEV_CON_ID("pll_clk", &pll_clk),

	/* DIV4 घड़ीs */
	CLKDEV_CON_ID("peripheral_clk", &भाग4_clks[DIV4_P]),
	CLKDEV_CON_ID("du_clk", &भाग4_clks[DIV4_DU]),
	CLKDEV_CON_ID("ga_clk", &भाग4_clks[DIV4_GA]),
	CLKDEV_CON_ID("ddr_clk", &भाग4_clks[DIV4_DDR]),
	CLKDEV_CON_ID("bus_clk", &भाग4_clks[DIV4_B]),
	CLKDEV_CON_ID("shyway_clk", &भाग4_clks[DIV4_SH]),
	CLKDEV_CON_ID("umem_clk", &भाग4_clks[DIV4_U]),
	CLKDEV_CON_ID("cpu_clk", &भाग4_clks[DIV4_I]),

	/* MSTP32 घड़ीs */
	CLKDEV_ICK_ID("fck", "sh-sci.5", &mstp_clks[MSTP029]),
	CLKDEV_ICK_ID("fck", "sh-sci.4", &mstp_clks[MSTP028]),
	CLKDEV_ICK_ID("fck", "sh-sci.3", &mstp_clks[MSTP027]),
	CLKDEV_ICK_ID("fck", "sh-sci.2", &mstp_clks[MSTP026]),
	CLKDEV_ICK_ID("fck", "sh-sci.1", &mstp_clks[MSTP025]),
	CLKDEV_ICK_ID("fck", "sh-sci.0", &mstp_clks[MSTP024]),

	CLKDEV_CON_ID("ssi1_fck", &mstp_clks[MSTP021]),
	CLKDEV_CON_ID("ssi0_fck", &mstp_clks[MSTP020]),
	CLKDEV_CON_ID("hac1_fck", &mstp_clks[MSTP017]),
	CLKDEV_CON_ID("hac0_fck", &mstp_clks[MSTP016]),
	CLKDEV_CON_ID("mmcif_fck", &mstp_clks[MSTP013]),
	CLKDEV_CON_ID("flctl_fck", &mstp_clks[MSTP012]),

	CLKDEV_ICK_ID("fck", "sh-tmu.0", &mstp_clks[MSTP008]),
	CLKDEV_ICK_ID("fck", "sh-tmu.1", &mstp_clks[MSTP009]),

	CLKDEV_CON_ID("siof_fck", &mstp_clks[MSTP003]),
	CLKDEV_CON_ID("hspi_fck", &mstp_clks[MSTP002]),
	CLKDEV_CON_ID("hudi_fck", &mstp_clks[MSTP119]),
	CLKDEV_CON_ID("ubc0", &mstp_clks[MSTP117]),
	CLKDEV_CON_ID("dmac_11_6_fck", &mstp_clks[MSTP105]),
	CLKDEV_CON_ID("dmac_5_0_fck", &mstp_clks[MSTP104]),
	CLKDEV_CON_ID("gdta_fck", &mstp_clks[MSTP100]),
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
