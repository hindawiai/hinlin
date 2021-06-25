<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh2/घड़ी-sh7619.c
 *
 * SH7619 support क्रम the घड़ी framework
 *
 *  Copyright (C) 2006  Yoshinori Sato
 *
 * Based on घड़ी-sh4.c
 *  Copyright (C) 2005  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/freq.h>
#समावेश <यंत्र/processor.h>

अटल स्थिर पूर्णांक pll1rate[] = अणु1,2पूर्ण;
अटल स्थिर पूर्णांक pfc_भागisors[] = अणु1,2,0,4पूर्ण;
अटल अचिन्हित पूर्णांक pll2_mult;

अटल व्योम master_clk_init(काष्ठा clk *clk)
अणु
	clk->rate *= pll2_mult * pll1rate[(__raw_पढ़ोw(FREQCR) >> 8) & 7];
पूर्ण

अटल काष्ठा sh_clk_ops sh7619_master_clk_ops = अणु
	.init		= master_clk_init,
पूर्ण;

अटल अचिन्हित दीर्घ module_clk_recalc(काष्ठा clk *clk)
अणु
	पूर्णांक idx = (__raw_पढ़ोw(FREQCR) & 0x0007);
	वापस clk->parent->rate / pfc_भागisors[idx];
पूर्ण

अटल काष्ठा sh_clk_ops sh7619_module_clk_ops = अणु
	.recalc		= module_clk_recalc,
पूर्ण;

अटल अचिन्हित दीर्घ bus_clk_recalc(काष्ठा clk *clk)
अणु
	वापस clk->parent->rate / pll1rate[(__raw_पढ़ोw(FREQCR) >> 8) & 7];
पूर्ण

अटल काष्ठा sh_clk_ops sh7619_bus_clk_ops = अणु
	.recalc		= bus_clk_recalc,
पूर्ण;

अटल काष्ठा sh_clk_ops sh7619_cpu_clk_ops = अणु
	.recalc		= followparent_recalc,
पूर्ण;

अटल काष्ठा sh_clk_ops *sh7619_clk_ops[] = अणु
	&sh7619_master_clk_ops,
	&sh7619_module_clk_ops,
	&sh7619_bus_clk_ops,
	&sh7619_cpu_clk_ops,
पूर्ण;

व्योम __init arch_init_clk_ops(काष्ठा sh_clk_ops **ops, पूर्णांक idx)
अणु
	अगर (test_mode_pin(MODE_PIN2 | MODE_PIN0) ||
	    test_mode_pin(MODE_PIN2 | MODE_PIN1))
		pll2_mult = 2;
	अन्यथा अगर (test_mode_pin(MODE_PIN0) || test_mode_pin(MODE_PIN1))
		pll2_mult = 4;

	BUG_ON(!pll2_mult);

	अगर (idx < ARRAY_SIZE(sh7619_clk_ops))
		*ops = sh7619_clk_ops[idx];
पूर्ण
