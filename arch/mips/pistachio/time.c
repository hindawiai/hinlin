<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pistachio घड़ीsource/समयr setup
 *
 * Copyright (C) 2014 Google, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_clk.h>

#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/समय.स>

अचिन्हित पूर्णांक get_c0_compare_पूर्णांक(व्योम)
अणु
	वापस gic_get_c0_compare_पूर्णांक();
पूर्ण

पूर्णांक get_c0_perfcount_पूर्णांक(व्योम)
अणु
	वापस gic_get_c0_perfcount_पूर्णांक();
पूर्ण
EXPORT_SYMBOL_GPL(get_c0_perfcount_पूर्णांक);

पूर्णांक get_c0_fdc_पूर्णांक(व्योम)
अणु
	वापस gic_get_c0_fdc_पूर्णांक();
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा clk *clk;

	of_clk_init(शून्य);
	समयr_probe();

	np = of_get_cpu_node(0, शून्य);
	अगर (!np) अणु
		pr_err("Failed to get CPU node\n");
		वापस;
	पूर्ण

	clk = of_clk_get(np, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("Failed to get CPU clock: %ld\n", PTR_ERR(clk));
		वापस;
	पूर्ण

	mips_hpt_frequency = clk_get_rate(clk) / 2;
	clk_put(clk);
पूर्ण
