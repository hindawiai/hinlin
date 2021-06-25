<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/घड़ी.c - SuperH घड़ी framework
 *
 *  Copyright (C) 2005 - 2009  Paul Mundt
 *
 * This घड़ी framework is derived from the OMAP version by:
 *
 *	Copyright (C) 2004 - 2008 Nokia Corporation
 *	Written by Tuukka Tikkanen <tuukka.tikkanen@elektrobit.com>
 *
 *  Modअगरied क्रम omap shared घड़ी framework by Tony Lindgren <tony@atomide.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/machvec.h>

पूर्णांक __init clk_init(व्योम)
अणु
	पूर्णांक ret;

#अगर_अघोषित CONFIG_COMMON_CLK
	ret = arch_clk_init();
	अगर (unlikely(ret)) अणु
		pr_err("%s: CPU clock registration failed.\n", __func__);
		वापस ret;
	पूर्ण
#पूर्ण_अगर

	अगर (sh_mv.mv_clk_init) अणु
		ret = sh_mv.mv_clk_init();
		अगर (unlikely(ret)) अणु
			pr_err("%s: machvec clock initialization failed.\n",
			       __func__);
			वापस ret;
		पूर्ण
	पूर्ण

#अगर_अघोषित CONFIG_COMMON_CLK
	/* Kick the child घड़ीs.. */
	recalculate_root_घड़ीs();

	/* Enable the necessary init घड़ीs */
	clk_enable_init_घड़ीs();
#पूर्ण_अगर

	वापस ret;
पूर्ण


