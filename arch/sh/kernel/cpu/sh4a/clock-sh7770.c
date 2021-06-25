<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4a/घड़ी-sh7770.c
 *
 * SH7770 support क्रम the घड़ी framework
 *
 *  Copyright (C) 2005  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/freq.h>
#समावेश <यंत्र/पन.स>

अटल पूर्णांक अगरc_भागisors[] = अणु 1, 1, 1, 1, 1, 1, 1, 1 पूर्ण;
अटल पूर्णांक bfc_भागisors[] = अणु 1, 1, 1, 1, 1, 8,12, 1 पूर्ण;
अटल पूर्णांक pfc_भागisors[] = अणु 1, 8, 1,10,12,16, 1, 1 पूर्ण;

अटल व्योम master_clk_init(काष्ठा clk *clk)
अणु
	clk->rate *= pfc_भागisors[(__raw_पढ़ोl(FRQCR) >> 28) & 0x000f];
पूर्ण

अटल काष्ठा sh_clk_ops sh7770_master_clk_ops = अणु
	.init		= master_clk_init,
पूर्ण;

अटल अचिन्हित दीर्घ module_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = ((__raw_पढ़ोl(FRQCR) >> 28) & 0x000f);
	वापस clk->parent->rate / pfc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7770_module_clk_ops = अणु
	.recalc		= module_clk_recalc,
पूर्ण;

अटल अचिन्हित दीर्घ bus_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = (__raw_पढ़ोl(FRQCR) & 0x000f);
	वापस clk->parent->rate / bfc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7770_bus_clk_ops = अणु
	.recalc		= bus_clk_recalc,
पूर्ण;

अटल अचिन्हित दीर्घ cpu_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = ((__raw_पढ़ोl(FRQCR) >> 24) & 0x000f);
	वापस clk->parent->rate / अगरc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7770_cpu_clk_ops = अणु
	.recalc		= cpu_clk_recalc,
पूर्ण;

अटल काष्ठा sh_clk_ops *sh7770_clk_ops[] = अणु
	&sh7770_master_clk_ops,
	&sh7770_module_clk_ops,
	&sh7770_bus_clk_ops,
	&sh7770_cpu_clk_ops,
पूर्ण;

व्योम __init arch_init_clk_ops(काष्ठा sh_clk_ops **ops, पूर्णांक idx)
अणु
	अगर (idx < ARRAY_SIZE(sh7770_clk_ops))
		*ops = sh7770_clk_ops[idx];
पूर्ण

