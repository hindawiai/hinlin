<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh2a/घड़ी-sh7264.c
 *
 * SH7264 घड़ी framework support
 *
 * Copyright (C) 2012  Phil Edworthy
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/clkdev.h>
#समावेश <यंत्र/घड़ी.h>

/* SH7264 रेजिस्टरs */
#घोषणा FRQCR		0xfffe0010
#घोषणा STBCR3		0xfffe0408
#घोषणा STBCR4		0xfffe040c
#घोषणा STBCR5		0xfffe0410
#घोषणा STBCR6		0xfffe0414
#घोषणा STBCR7		0xfffe0418
#घोषणा STBCR8		0xfffe041c

अटल स्थिर अचिन्हित पूर्णांक pll1rate[] = अणु8, 12पूर्ण;

अटल अचिन्हित पूर्णांक pll1_भाग;

/* Fixed 32 KHz root घड़ी क्रम RTC */
अटल काष्ठा clk r_clk = अणु
	.rate           = 32768,
पूर्ण;

/*
 * Default rate क्रम the root input घड़ी, reset this with clk_set_rate()
 * from the platक्रमm code.
 */
अटल काष्ठा clk extal_clk = अणु
	.rate		= 18000000,
पूर्ण;

अटल अचिन्हित दीर्घ pll_recalc(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ rate = clk->parent->rate / pll1_भाग;
	वापस rate * pll1rate[(__raw_पढ़ोw(FRQCR) >> 8) & 1];
पूर्ण

अटल काष्ठा sh_clk_ops pll_clk_ops = अणु
	.recalc		= pll_recalc,
पूर्ण;

अटल काष्ठा clk pll_clk = अणु
	.ops		= &pll_clk_ops,
	.parent		= &extal_clk,
	.flags		= CLK_ENABLE_ON_INIT,
पूर्ण;

काष्ठा clk *मुख्य_clks[] = अणु
	&r_clk,
	&extal_clk,
	&pll_clk,
पूर्ण;

अटल पूर्णांक भाग2[] = अणु 1, 2, 3, 4, 6, 8, 12 पूर्ण;

अटल काष्ठा clk_भाग_mult_table भाग4_भाग_mult_table = अणु
	.भागisors = भाग2,
	.nr_भागisors = ARRAY_SIZE(भाग2),
पूर्ण;

अटल काष्ठा clk_भाग4_table भाग4_table = अणु
	.भाग_mult_table = &भाग4_भाग_mult_table,
पूर्ण;

क्रमागत अणु DIV4_I, DIV4_P,
       DIV4_NR पूर्ण;

#घोषणा DIV4(_reg, _bit, _mask, _flags) \
  SH_CLK_DIV4(&pll_clk, _reg, _bit, _mask, _flags)

/* The mask field specअगरies the भाग2 entries that are valid */
काष्ठा clk भाग4_clks[DIV4_NR] = अणु
	[DIV4_I] = DIV4(FRQCR, 4, 0x7,  CLK_ENABLE_REG_16BIT
					| CLK_ENABLE_ON_INIT),
	[DIV4_P] = DIV4(FRQCR, 0, 0x78, CLK_ENABLE_REG_16BIT),
पूर्ण;

क्रमागत अणु	MSTP77, MSTP74, MSTP72,
	MSTP60,
	MSTP35, MSTP34, MSTP33, MSTP32, MSTP30,
	MSTP_NR पूर्ण;

अटल काष्ठा clk mstp_clks[MSTP_NR] = अणु
	[MSTP77] = SH_CLK_MSTP8(&भाग4_clks[DIV4_P], STBCR7, 7, 0), /* SCIF */
	[MSTP74] = SH_CLK_MSTP8(&भाग4_clks[DIV4_P], STBCR7, 4, 0), /* VDC */
	[MSTP72] = SH_CLK_MSTP8(&भाग4_clks[DIV4_P], STBCR7, 2, 0), /* CMT */
	[MSTP60] = SH_CLK_MSTP8(&भाग4_clks[DIV4_P], STBCR6, 0, 0), /* USB */
	[MSTP35] = SH_CLK_MSTP8(&भाग4_clks[DIV4_P], STBCR3, 6, 0), /* MTU2 */
	[MSTP34] = SH_CLK_MSTP8(&भाग4_clks[DIV4_P], STBCR3, 4, 0), /* SDHI0 */
	[MSTP33] = SH_CLK_MSTP8(&भाग4_clks[DIV4_P], STBCR3, 3, 0), /* SDHI1 */
	[MSTP32] = SH_CLK_MSTP8(&भाग4_clks[DIV4_P], STBCR3, 2, 0), /* ADC */
	[MSTP30] = SH_CLK_MSTP8(&r_clk, STBCR3, 0, 0),	/* RTC */
पूर्ण;

अटल काष्ठा clk_lookup lookups[] = अणु
	/* मुख्य घड़ीs */
	CLKDEV_CON_ID("rclk", &r_clk),
	CLKDEV_CON_ID("extal", &extal_clk),
	CLKDEV_CON_ID("pll_clk", &pll_clk),

	/* DIV4 घड़ीs */
	CLKDEV_CON_ID("cpu_clk", &भाग4_clks[DIV4_I]),
	CLKDEV_CON_ID("peripheral_clk", &भाग4_clks[DIV4_P]),

	/* MSTP घड़ीs */
	CLKDEV_ICK_ID("fck", "sh-sci.0", &mstp_clks[MSTP77]),
	CLKDEV_ICK_ID("fck", "sh-sci.1", &mstp_clks[MSTP77]),
	CLKDEV_ICK_ID("fck", "sh-sci.2", &mstp_clks[MSTP77]),
	CLKDEV_ICK_ID("fck", "sh-sci.3", &mstp_clks[MSTP77]),
	CLKDEV_ICK_ID("fck", "sh-sci.4", &mstp_clks[MSTP77]),
	CLKDEV_ICK_ID("fck", "sh-sci.5", &mstp_clks[MSTP77]),
	CLKDEV_ICK_ID("fck", "sh-sci.6", &mstp_clks[MSTP77]),
	CLKDEV_ICK_ID("fck", "sh-sci.7", &mstp_clks[MSTP77]),
	CLKDEV_CON_ID("vdc3", &mstp_clks[MSTP74]),
	CLKDEV_ICK_ID("fck", "sh-cmt-16.0", &mstp_clks[MSTP72]),
	CLKDEV_CON_ID("usb0", &mstp_clks[MSTP60]),
	CLKDEV_ICK_ID("fck", "sh-mtu2", &mstp_clks[MSTP35]),
	CLKDEV_CON_ID("sdhi0", &mstp_clks[MSTP34]),
	CLKDEV_CON_ID("sdhi1", &mstp_clks[MSTP33]),
	CLKDEV_CON_ID("adc0", &mstp_clks[MSTP32]),
	CLKDEV_CON_ID("rtc0", &mstp_clks[MSTP30]),
पूर्ण;

पूर्णांक __init arch_clk_init(व्योम)
अणु
	पूर्णांक k, ret = 0;

	अगर (test_mode_pin(MODE_PIN0)) अणु
		अगर (test_mode_pin(MODE_PIN1))
			pll1_भाग = 3;
		अन्यथा
			pll1_भाग = 4;
	पूर्ण अन्यथा
		pll1_भाग = 1;

	क्रम (k = 0; !ret && (k < ARRAY_SIZE(मुख्य_clks)); k++)
		ret = clk_रेजिस्टर(मुख्य_clks[k]);

	clkdev_add_table(lookups, ARRAY_SIZE(lookups));

	अगर (!ret)
		ret = sh_clk_भाग4_रेजिस्टर(भाग4_clks, DIV4_NR, &भाग4_table);

	अगर (!ret)
		ret = sh_clk_mstp_रेजिस्टर(mstp_clks, MSTP_NR);

	वापस ret;
पूर्ण
