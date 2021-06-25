<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4/घड़ी-sh4.c
 *
 * Generic SH-4 support क्रम the घड़ी framework
 *
 *  Copyright (C) 2005  Paul Mundt
 *
 * FRQCR parsing hacked out of arch/sh/kernel/समय.c
 *
 *  Copyright (C) 1999  Tetsuya Okada & Niibe Yutaka
 *  Copyright (C) 2000  Philipp Rumpf <prumpf@tux.org>
 *  Copyright (C) 2002, 2003, 2004  Paul Mundt
 *  Copyright (C) 2002  M. R. Brown  <mrbrown@linux-sh.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/freq.h>
#समावेश <यंत्र/पन.स>

अटल पूर्णांक अगरc_भागisors[] = अणु 1, 2, 3, 4, 6, 8, 1, 1 पूर्ण;
#घोषणा bfc_भागisors अगरc_भागisors	/* Same */
अटल पूर्णांक pfc_भागisors[] = अणु 2, 3, 4, 6, 8, 2, 2, 2 पूर्ण;

अटल व्योम master_clk_init(काष्ठा clk *clk)
अणु
	clk->rate *= pfc_भागisors[__raw_पढ़ोw(FRQCR) & 0x0007];
पूर्ण

अटल काष्ठा sh_clk_ops sh4_master_clk_ops = अणु
	.init		= master_clk_init,
पूर्ण;

अटल अचिन्हित दीर्घ module_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = (__raw_पढ़ोw(FRQCR) & 0x0007);
	वापस clk->parent->rate / pfc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh4_module_clk_ops = अणु
	.recalc		= module_clk_recalc,
पूर्ण;

अटल अचिन्हित दीर्घ bus_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = (__raw_पढ़ोw(FRQCR) >> 3) & 0x0007;
	वापस clk->parent->rate / bfc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh4_bus_clk_ops = अणु
	.recalc		= bus_clk_recalc,
पूर्ण;

अटल अचिन्हित दीर्घ cpu_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = (__raw_पढ़ोw(FRQCR) >> 6) & 0x0007;
	वापस clk->parent->rate / अगरc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh4_cpu_clk_ops = अणु
	.recalc		= cpu_clk_recalc,
पूर्ण;

अटल काष्ठा sh_clk_ops *sh4_clk_ops[] = अणु
	&sh4_master_clk_ops,
	&sh4_module_clk_ops,
	&sh4_bus_clk_ops,
	&sh4_cpu_clk_ops,
पूर्ण;

व्योम __init arch_init_clk_ops(काष्ठा sh_clk_ops **ops, पूर्णांक idx)
अणु
	अगर (idx < ARRAY_SIZE(sh4_clk_ops))
		*ops = sh4_clk_ops[idx];
पूर्ण

