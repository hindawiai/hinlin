<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2011 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2013 John Crispin <john@phrozen.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk.h>

#समावेश <यंत्र/समय.स>

#समावेश "common.h"

काष्ठा clk अणु
	काष्ठा clk_lookup cl;
	अचिन्हित दीर्घ rate;
पूर्ण;

व्योम ralink_clk_add(स्थिर अक्षर *dev, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk *clk = kzalloc(माप(काष्ठा clk), GFP_KERNEL);

	अगर (!clk)
		panic("failed to add clock");

	clk->cl.dev_id = dev;
	clk->cl.clk = clk;

	clk->rate = rate;

	clkdev_add(&clk->cl);
पूर्ण

/*
 * Linux घड़ी API
 */
पूर्णांक clk_enable(काष्ठा clk *clk)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(clk_enable);

व्योम clk_disable(काष्ठा clk *clk)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(clk_disable);

अचिन्हित दीर्घ clk_get_rate(काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस 0;

	वापस clk->rate;
पूर्ण
EXPORT_SYMBOL_GPL(clk_get_rate);

पूर्णांक clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_rate);

दीर्घ clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(clk_round_rate);

पूर्णांक clk_set_parent(काष्ठा clk *clk, काष्ठा clk *parent)
अणु
	WARN_ON(clk);
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(clk_set_parent);

काष्ठा clk *clk_get_parent(काष्ठा clk *clk)
अणु
	WARN_ON(clk);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(clk_get_parent);

व्योम __init plat_समय_init(व्योम)
अणु
	काष्ठा clk *clk;

	ralink_of_remap();

	ralink_clk_init();
	clk = clk_get_sys("cpu", शून्य);
	अगर (IS_ERR(clk))
		panic("unable to get CPU clock, err=%ld", PTR_ERR(clk));
	pr_info("CPU Clock: %ldMHz\n", clk_get_rate(clk) / 1000000);
	mips_hpt_frequency = clk_get_rate(clk) / 2;
	clk_put(clk);
	समयr_probe();
पूर्ण
