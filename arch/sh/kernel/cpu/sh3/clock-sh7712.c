<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh3/घड़ी-sh7712.c
 *
 * SH7712 support क्रम the घड़ी framework
 *
 *  Copyright (C) 2007  Andrew Murray <amurray@mpc-data.co.uk>
 *
 * Based on arch/sh/kernel/cpu/sh3/घड़ी-sh3.c
 *  Copyright (C) 2005  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/freq.h>
#समावेश <यंत्र/पन.स>

अटल पूर्णांक multipliers[] = अणु 1, 2, 3 पूर्ण;
अटल पूर्णांक भागisors[]    = अणु 1, 2, 3, 4, 6 पूर्ण;

अटल व्योम master_clk_init(काष्ठा clk *clk)
अणु
	पूर्णांक frqcr = __raw_पढ़ोw(FRQCR);
	पूर्णांक idx = (frqcr & 0x0300) >> 8;

	clk->rate *= multipliers[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7712_master_clk_ops = अणु
	.init		= master_clk_init,
पूर्ण;

अटल अचिन्हित दीर्घ module_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक frqcr = __raw_पढ़ोw(FRQCR);
	पूर्णांक idx = frqcr & 0x0007;

	वापस clk->parent->rate / भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7712_module_clk_ops = अणु
	.recalc		= module_clk_recalc,
पूर्ण;

अटल अचिन्हित दीर्घ cpu_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक frqcr = __raw_पढ़ोw(FRQCR);
	पूर्णांक idx = (frqcr & 0x0030) >> 4;

	वापस clk->parent->rate / भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7712_cpu_clk_ops = अणु
	.recalc		= cpu_clk_recalc,
पूर्ण;

अटल काष्ठा sh_clk_ops *sh7712_clk_ops[] = अणु
	&sh7712_master_clk_ops,
	&sh7712_module_clk_ops,
	&sh7712_cpu_clk_ops,
पूर्ण;

व्योम __init arch_init_clk_ops(काष्ठा sh_clk_ops **ops, पूर्णांक idx)
अणु
	अगर (idx < ARRAY_SIZE(sh7712_clk_ops))
		*ops = sh7712_clk_ops[idx];
पूर्ण

