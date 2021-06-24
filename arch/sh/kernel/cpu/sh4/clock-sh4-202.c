<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4/घड़ी-sh4-202.c
 *
 * Additional SH4-202 support क्रम the घड़ी framework
 *
 *  Copyright (C) 2005  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/clkdev.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/freq.h>

#घोषणा CPG2_FRQCR3	0xfe0a0018

अटल पूर्णांक frqcr3_भागisors[] = अणु 1, 2, 3, 4, 6, 8, 16 पूर्ण;
अटल पूर्णांक frqcr3_values[]   = अणु 0, 1, 2, 3, 4, 5, 6  पूर्ण;

अटल अचिन्हित दीर्घ emi_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = __raw_पढ़ोl(CPG2_FRQCR3) & 0x0007;
	वापस clk->parent->rate / frqcr3_भागisors[idx];
पूर्ण

अटल अंतरभूत पूर्णांक frqcr3_lookup(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक भागisor = clk->parent->rate / rate;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(frqcr3_भागisors); i++)
		अगर (frqcr3_भागisors[i] == भागisor)
			वापस frqcr3_values[i];

	/* Safe fallback */
	वापस 5;
पूर्ण

अटल काष्ठा sh_clk_ops sh4202_emi_clk_ops = अणु
	.recalc		= emi_clk_recalc,
पूर्ण;

अटल काष्ठा clk sh4202_emi_clk = अणु
	.flags		= CLK_ENABLE_ON_INIT,
	.ops		= &sh4202_emi_clk_ops,
पूर्ण;

अटल अचिन्हित दीर्घ femi_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = (__raw_पढ़ोl(CPG2_FRQCR3) >> 3) & 0x0007;
	वापस clk->parent->rate / frqcr3_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh4202_femi_clk_ops = अणु
	.recalc		= femi_clk_recalc,
पूर्ण;

अटल काष्ठा clk sh4202_femi_clk = अणु
	.flags		= CLK_ENABLE_ON_INIT,
	.ops		= &sh4202_femi_clk_ops,
पूर्ण;

अटल व्योम shoc_clk_init(काष्ठा clk *clk)
अणु
	पूर्णांक i;

	/*
	 * For some reason, the shoc_clk seems to be set to some really
	 * insane value at boot (values outside of the allowable frequency
	 * range क्रम instance). We deal with this by scaling it back करोwn
	 * to something sensible just in हाल.
	 *
	 * Start scaling from the high end करोwn until we find something
	 * that passes rate verअगरication..
	 */
	क्रम (i = 0; i < ARRAY_SIZE(frqcr3_भागisors); i++) अणु
		पूर्णांक भागisor = frqcr3_भागisors[i];

		अगर (clk->ops->set_rate(clk, clk->parent->rate / भागisor) == 0)
			अवरोध;
	पूर्ण

	WARN_ON(i == ARRAY_SIZE(frqcr3_भागisors));	/* Undefined घड़ी */
पूर्ण

अटल अचिन्हित दीर्घ shoc_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = (__raw_पढ़ोl(CPG2_FRQCR3) >> 6) & 0x0007;
	वापस clk->parent->rate / frqcr3_भागisors[idx];
पूर्ण

अटल पूर्णांक shoc_clk_verअगरy_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk *bclk = clk_get(शून्य, "bus_clk");
	अचिन्हित दीर्घ bclk_rate = clk_get_rate(bclk);

	clk_put(bclk);

	अगर (rate > bclk_rate)
		वापस 1;
	अगर (rate > 66000000)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक shoc_clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ frqcr3;
	अचिन्हित पूर्णांक पंचांगp;

	/* Make sure we have something sensible to चयन to */
	अगर (shoc_clk_verअगरy_rate(clk, rate) != 0)
		वापस -EINVAL;

	पंचांगp = frqcr3_lookup(clk, rate);

	frqcr3 = __raw_पढ़ोl(CPG2_FRQCR3);
	frqcr3 &= ~(0x0007 << 6);
	frqcr3 |= पंचांगp << 6;
	__raw_ग_लिखोl(frqcr3, CPG2_FRQCR3);

	clk->rate = clk->parent->rate / frqcr3_भागisors[पंचांगp];

	वापस 0;
पूर्ण

अटल काष्ठा sh_clk_ops sh4202_shoc_clk_ops = अणु
	.init		= shoc_clk_init,
	.recalc		= shoc_clk_recalc,
	.set_rate	= shoc_clk_set_rate,
पूर्ण;

अटल काष्ठा clk sh4202_shoc_clk = अणु
	.flags		= CLK_ENABLE_ON_INIT,
	.ops		= &sh4202_shoc_clk_ops,
पूर्ण;

अटल काष्ठा clk *sh4202_onchip_घड़ीs[] = अणु
	&sh4202_emi_clk,
	&sh4202_femi_clk,
	&sh4202_shoc_clk,
पूर्ण;

अटल काष्ठा clk_lookup lookups[] = अणु
	/* मुख्य घड़ीs */
	CLKDEV_CON_ID("emi_clk", &sh4202_emi_clk),
	CLKDEV_CON_ID("femi_clk", &sh4202_femi_clk),
	CLKDEV_CON_ID("shoc_clk", &sh4202_shoc_clk),
पूर्ण;

पूर्णांक __init arch_clk_init(व्योम)
अणु
	काष्ठा clk *clk;
	पूर्णांक i, ret = 0;

	cpg_clk_init();

	clk = clk_get(शून्य, "master_clk");
	क्रम (i = 0; i < ARRAY_SIZE(sh4202_onchip_घड़ीs); i++) अणु
		काष्ठा clk *clkp = sh4202_onchip_घड़ीs[i];

		clkp->parent = clk;
		ret |= clk_रेजिस्टर(clkp);
	पूर्ण

	clk_put(clk);

	clkdev_add_table(lookups, ARRAY_SIZE(lookups));

	वापस ret;
पूर्ण
