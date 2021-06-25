<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4a/घड़ी-sh7780.c
 *
 * SH7780 support क्रम the घड़ी framework
 *
 *  Copyright (C) 2005  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/clkdev.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/freq.h>
#समावेश <यंत्र/पन.स>

अटल पूर्णांक अगरc_भागisors[] = अणु 2, 4 पूर्ण;
अटल पूर्णांक bfc_भागisors[] = अणु 1, 1, 1, 8, 12, 16, 24, 1 पूर्ण;
अटल पूर्णांक pfc_भागisors[] = अणु 1, 24, 24, 1 पूर्ण;
अटल पूर्णांक cfc_भागisors[] = अणु 1, 1, 4, 1, 6, 1, 1, 1 पूर्ण;

अटल व्योम master_clk_init(काष्ठा clk *clk)
अणु
	clk->rate *= pfc_भागisors[__raw_पढ़ोl(FRQCR) & 0x0003];
पूर्ण

अटल काष्ठा sh_clk_ops sh7780_master_clk_ops = अणु
	.init		= master_clk_init,
पूर्ण;

अटल अचिन्हित दीर्घ module_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = (__raw_पढ़ोl(FRQCR) & 0x0003);
	वापस clk->parent->rate / pfc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7780_module_clk_ops = अणु
	.recalc		= module_clk_recalc,
पूर्ण;

अटल अचिन्हित दीर्घ bus_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = ((__raw_पढ़ोl(FRQCR) >> 16) & 0x0007);
	वापस clk->parent->rate / bfc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7780_bus_clk_ops = अणु
	.recalc		= bus_clk_recalc,
पूर्ण;

अटल अचिन्हित दीर्घ cpu_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = ((__raw_पढ़ोl(FRQCR) >> 24) & 0x0001);
	वापस clk->parent->rate / अगरc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7780_cpu_clk_ops = अणु
	.recalc		= cpu_clk_recalc,
पूर्ण;

अटल काष्ठा sh_clk_ops *sh7780_clk_ops[] = अणु
	&sh7780_master_clk_ops,
	&sh7780_module_clk_ops,
	&sh7780_bus_clk_ops,
	&sh7780_cpu_clk_ops,
पूर्ण;

व्योम __init arch_init_clk_ops(काष्ठा sh_clk_ops **ops, पूर्णांक idx)
अणु
	अगर (idx < ARRAY_SIZE(sh7780_clk_ops))
		*ops = sh7780_clk_ops[idx];
पूर्ण

अटल अचिन्हित दीर्घ shyway_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = ((__raw_पढ़ोl(FRQCR) >> 20) & 0x0007);
	वापस clk->parent->rate / cfc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7780_shyway_clk_ops = अणु
	.recalc		= shyway_clk_recalc,
पूर्ण;

अटल काष्ठा clk sh7780_shyway_clk = अणु
	.flags		= CLK_ENABLE_ON_INIT,
	.ops		= &sh7780_shyway_clk_ops,
पूर्ण;

/*
 * Additional SH7780-specअगरic on-chip घड़ीs that aren't alपढ़ोy part of the
 * घड़ी framework
 */
अटल काष्ठा clk *sh7780_onchip_घड़ीs[] = अणु
	&sh7780_shyway_clk,
पूर्ण;

अटल काष्ठा clk_lookup lookups[] = अणु
	/* मुख्य घड़ीs */
	CLKDEV_CON_ID("shyway_clk", &sh7780_shyway_clk),
पूर्ण;

पूर्णांक __init arch_clk_init(व्योम)
अणु
	काष्ठा clk *clk;
	पूर्णांक i, ret = 0;

	cpg_clk_init();

	clk = clk_get(शून्य, "master_clk");
	क्रम (i = 0; i < ARRAY_SIZE(sh7780_onchip_घड़ीs); i++) अणु
		काष्ठा clk *clkp = sh7780_onchip_घड़ीs[i];

		clkp->parent = clk;
		ret |= clk_रेजिस्टर(clkp);
	पूर्ण

	clk_put(clk);

	clkdev_add_table(lookups, ARRAY_SIZE(lookups));

	वापस ret;
पूर्ण
