<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Lemote, Inc. & Institute of Computing Technology
 * Author: Fuxin Zhang, zhangfx@lemote.com
 *
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/hpet.h>

#समावेश <loongson.h>
#समावेश <linux/clk.h>
#समावेश <linux/of_clk.h>

व्योम __init plat_समय_init(व्योम)
अणु
	काष्ठा clk *clk;
	काष्ठा device_node *np;

	अगर (loongson_sysconf.fw_पूर्णांकerface == LOONGSON_DTB) अणु
		of_clk_init(शून्य);

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

		cpu_घड़ी_freq = clk_get_rate(clk);
		clk_put(clk);
	पूर्ण

	/* setup mips r4k समयr */
	mips_hpt_frequency = cpu_घड़ी_freq / 2;

#अगर_घोषित CONFIG_RS780_HPET
	setup_hpet_समयr();
#पूर्ण_अगर
पूर्ण
