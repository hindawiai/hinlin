<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh3/घड़ी-sh7705.c
 *
 * SH7705 support क्रम the घड़ी framework
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

/*
 * SH7705 uses the same भागisors as the generic SH-3 हाल, it's just the
 * FRQCR layout that is a bit dअगरferent..
 */
अटल पूर्णांक stc_multipliers[] = अणु 1, 2, 3, 4, 6, 1, 1, 1 पूर्ण;
अटल पूर्णांक अगरc_भागisors[]    = अणु 1, 2, 3, 4, 1, 1, 1, 1 पूर्ण;
अटल पूर्णांक pfc_भागisors[]    = अणु 1, 2, 3, 4, 6, 1, 1, 1 पूर्ण;

अटल व्योम master_clk_init(काष्ठा clk *clk)
अणु
	clk->rate *= pfc_भागisors[__raw_पढ़ोw(FRQCR) & 0x0003];
पूर्ण

अटल काष्ठा sh_clk_ops sh7705_master_clk_ops = अणु
	.init		= master_clk_init,
पूर्ण;

अटल अचिन्हित दीर्घ module_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = __raw_पढ़ोw(FRQCR) & 0x0003;
	वापस clk->parent->rate / pfc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7705_module_clk_ops = अणु
	.recalc		= module_clk_recalc,
पूर्ण;

अटल अचिन्हित दीर्घ bus_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = (__raw_पढ़ोw(FRQCR) & 0x0300) >> 8;
	वापस clk->parent->rate / stc_multipliers[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7705_bus_clk_ops = अणु
	.recalc		= bus_clk_recalc,
पूर्ण;

अटल अचिन्हित दीर्घ cpu_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = (__raw_पढ़ोw(FRQCR) & 0x0030) >> 4;
	वापस clk->parent->rate / अगरc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7705_cpu_clk_ops = अणु
	.recalc		= cpu_clk_recalc,
पूर्ण;

अटल काष्ठा sh_clk_ops *sh7705_clk_ops[] = अणु
	&sh7705_master_clk_ops,
	&sh7705_module_clk_ops,
	&sh7705_bus_clk_ops,
	&sh7705_cpu_clk_ops,
पूर्ण;

व्योम __init arch_init_clk_ops(काष्ठा sh_clk_ops **ops, पूर्णांक idx)
अणु
	अगर (idx < ARRAY_SIZE(sh7705_clk_ops))
		*ops = sh7705_clk_ops[idx];
पूर्ण

