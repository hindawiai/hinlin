<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4/घड़ी-sh7757.c
 *
 * SH7757 support क्रम the घड़ी framework
 *
 *  Copyright (C) 2009-2010  Renesas Solutions Corp.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/clkdev.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/freq.h>

/*
 * Default rate क्रम the root input घड़ी, reset this with clk_set_rate()
 * from the platक्रमm code.
 */
अटल काष्ठा clk extal_clk = अणु
	.rate		= 48000000,
पूर्ण;

अटल अचिन्हित दीर्घ pll_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक multiplier;

	multiplier = test_mode_pin(MODE_PIN0) ? 24 : 16;

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

अटल अचिन्हित पूर्णांक भाग2[] = अणु 1, 1, 2, 1, 1, 4, 1, 6,
			       1, 1, 1, 16, 1, 24, 1, 1 पूर्ण;

अटल काष्ठा clk_भाग_mult_table भाग4_भाग_mult_table = अणु
	.भागisors = भाग2,
	.nr_भागisors = ARRAY_SIZE(भाग2),
पूर्ण;

अटल काष्ठा clk_भाग4_table भाग4_table = अणु
	.भाग_mult_table = &भाग4_भाग_mult_table,
पूर्ण;

क्रमागत अणु DIV4_I, DIV4_SH, DIV4_P, DIV4_NR पूर्ण;

#घोषणा DIV4(_bit, _mask, _flags) \
  SH_CLK_DIV4(&pll_clk, FRQCR, _bit, _mask, _flags)

काष्ठा clk भाग4_clks[DIV4_NR] = अणु
	/*
	 * P घड़ी is always enable, because some P घड़ी modules is used
	 * by Host PC.
	 */
	[DIV4_P] = DIV4(0, 0x2800, CLK_ENABLE_ON_INIT),
	[DIV4_SH] = DIV4(12, 0x00a0, CLK_ENABLE_ON_INIT),
	[DIV4_I] = DIV4(20, 0x0004, CLK_ENABLE_ON_INIT),
पूर्ण;

#घोषणा MSTPCR0		0xffc80030
#घोषणा MSTPCR1		0xffc80034
#घोषणा MSTPCR2		0xffc10028

क्रमागत अणु MSTP004, MSTP000, MSTP127, MSTP114, MSTP113, MSTP112,
       MSTP111, MSTP110, MSTP103, MSTP102, MSTP220,
       MSTP_NR पूर्ण;

अटल काष्ठा clk mstp_clks[MSTP_NR] = अणु
	/* MSTPCR0 */
	[MSTP004] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 4, 0),
	[MSTP000] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR0, 0, 0),

	/* MSTPCR1 */
	[MSTP127] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR1, 27, 0),
	[MSTP114] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR1, 14, 0),
	[MSTP113] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR1, 13, 0),
	[MSTP112] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR1, 12, 0),
	[MSTP111] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR1, 11, 0),
	[MSTP110] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR1, 10, 0),
	[MSTP103] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR1, 3, 0),
	[MSTP102] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR1, 2, 0),

	/* MSTPCR2 */
	[MSTP220] = SH_CLK_MSTP32(&भाग4_clks[DIV4_P], MSTPCR2, 20, 0),
पूर्ण;

अटल काष्ठा clk_lookup lookups[] = अणु
	/* मुख्य घड़ीs */
	CLKDEV_CON_ID("extal", &extal_clk),
	CLKDEV_CON_ID("pll_clk", &pll_clk),

	/* DIV4 घड़ीs */
	CLKDEV_CON_ID("peripheral_clk", &भाग4_clks[DIV4_P]),
	CLKDEV_CON_ID("shyway_clk", &भाग4_clks[DIV4_SH]),
	CLKDEV_CON_ID("cpu_clk", &भाग4_clks[DIV4_I]),

	/* MSTP32 घड़ीs */
	CLKDEV_DEV_ID("sh_mobile_sdhi.0", &mstp_clks[MSTP004]),
	CLKDEV_CON_ID("riic0", &mstp_clks[MSTP000]),
	CLKDEV_CON_ID("riic1", &mstp_clks[MSTP000]),
	CLKDEV_CON_ID("riic2", &mstp_clks[MSTP000]),
	CLKDEV_CON_ID("riic3", &mstp_clks[MSTP000]),
	CLKDEV_CON_ID("riic4", &mstp_clks[MSTP000]),
	CLKDEV_CON_ID("riic5", &mstp_clks[MSTP000]),
	CLKDEV_CON_ID("riic6", &mstp_clks[MSTP000]),
	CLKDEV_CON_ID("riic7", &mstp_clks[MSTP000]),

	CLKDEV_ICK_ID("fck", "sh-tmu.0", &mstp_clks[MSTP113]),
	CLKDEV_ICK_ID("fck", "sh-tmu.1", &mstp_clks[MSTP114]),
	CLKDEV_ICK_ID("fck", "sh-sci.2", &mstp_clks[MSTP112]),
	CLKDEV_ICK_ID("fck", "sh-sci.1", &mstp_clks[MSTP111]),
	CLKDEV_ICK_ID("fck", "sh-sci.0", &mstp_clks[MSTP110]),

	CLKDEV_CON_ID("usb_fck", &mstp_clks[MSTP103]),
	CLKDEV_DEV_ID("renesas_usbhs.0", &mstp_clks[MSTP102]),
	CLKDEV_CON_ID("mmc0", &mstp_clks[MSTP220]),
	CLKDEV_DEV_ID("rspi.2", &mstp_clks[MSTP127]),
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

