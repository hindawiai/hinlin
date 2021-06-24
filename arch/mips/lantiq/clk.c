<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2010 Thomas Langer <thomas.langer@lantiq.com>
 * Copyright (C) 2010 John Crispin <john@phrozen.org>
 */
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <lantiq_soc.h>

#समावेश "clk.h"
#समावेश "prom.h"

/* lantiq socs have 3 अटल घड़ीs */
अटल काष्ठा clk cpu_clk_generic[4];

व्योम clkdev_add_अटल(अचिन्हित दीर्घ cpu, अचिन्हित दीर्घ fpi,
			अचिन्हित दीर्घ io, अचिन्हित दीर्घ ppe)
अणु
	cpu_clk_generic[0].rate = cpu;
	cpu_clk_generic[1].rate = fpi;
	cpu_clk_generic[2].rate = io;
	cpu_clk_generic[3].rate = ppe;
पूर्ण

काष्ठा clk *clk_get_cpu(व्योम)
अणु
	वापस &cpu_clk_generic[0];
पूर्ण

काष्ठा clk *clk_get_fpi(व्योम)
अणु
	वापस &cpu_clk_generic[1];
पूर्ण
EXPORT_SYMBOL_GPL(clk_get_fpi);

काष्ठा clk *clk_get_io(व्योम)
अणु
	वापस &cpu_clk_generic[2];
पूर्ण

काष्ठा clk *clk_get_ppe(व्योम)
अणु
	वापस &cpu_clk_generic[3];
पूर्ण
EXPORT_SYMBOL_GPL(clk_get_ppe);

अटल अंतरभूत पूर्णांक clk_good(काष्ठा clk *clk)
अणु
	वापस clk && !IS_ERR(clk);
पूर्ण

अचिन्हित दीर्घ clk_get_rate(काष्ठा clk *clk)
अणु
	अगर (unlikely(!clk_good(clk)))
		वापस 0;

	अगर (clk->rate != 0)
		वापस clk->rate;

	अगर (clk->get_rate != शून्य)
		वापस clk->get_rate();

	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_get_rate);

पूर्णांक clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अगर (unlikely(!clk_good(clk)))
		वापस 0;
	अगर (clk->rates && *clk->rates) अणु
		अचिन्हित दीर्घ *r = clk->rates;

		जबतक (*r && (*r != rate))
			r++;
		अगर (!*r) अणु
			pr_err("clk %s.%s: trying to set invalid rate %ld\n",
				clk->cl.dev_id, clk->cl.con_id, rate);
			वापस -1;
		पूर्ण
	पूर्ण
	clk->rate = rate;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_set_rate);

दीर्घ clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	अगर (unlikely(!clk_good(clk)))
		वापस 0;
	अगर (clk->rates && *clk->rates) अणु
		अचिन्हित दीर्घ *r = clk->rates;

		जबतक (*r && (*r != rate))
			r++;
		अगर (!*r) अणु
			वापस clk->rate;
		पूर्ण
	पूर्ण
	वापस rate;
पूर्ण
EXPORT_SYMBOL(clk_round_rate);

पूर्णांक clk_enable(काष्ठा clk *clk)
अणु
	अगर (unlikely(!clk_good(clk)))
		वापस -1;

	अगर (clk->enable)
		वापस clk->enable(clk);

	वापस -1;
पूर्ण
EXPORT_SYMBOL(clk_enable);

व्योम clk_disable(काष्ठा clk *clk)
अणु
	अगर (unlikely(!clk_good(clk)))
		वापस;

	अगर (clk->disable)
		clk->disable(clk);
पूर्ण
EXPORT_SYMBOL(clk_disable);

पूर्णांक clk_activate(काष्ठा clk *clk)
अणु
	अगर (unlikely(!clk_good(clk)))
		वापस -1;

	अगर (clk->activate)
		वापस clk->activate(clk);

	वापस -1;
पूर्ण
EXPORT_SYMBOL(clk_activate);

व्योम clk_deactivate(काष्ठा clk *clk)
अणु
	अगर (unlikely(!clk_good(clk)))
		वापस;

	अगर (clk->deactivate)
		clk->deactivate(clk);
पूर्ण
EXPORT_SYMBOL(clk_deactivate);

अटल अंतरभूत u32 get_counter_resolution(व्योम)
अणु
	u32 res;

	__यंत्र__ __अस्थिर__(
		".set	push\n"
		".set	mips32r2\n"
		"rdhwr	%0, $3\n"
		".set pop\n"
		: "=&r" (res)
		: /* no input */
		: "memory");

	वापस res;
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	काष्ठा clk *clk;

	ltq_soc_init();

	clk = clk_get_cpu();
	mips_hpt_frequency = clk_get_rate(clk) / get_counter_resolution();
	ग_लिखो_c0_compare(पढ़ो_c0_count());
	pr_info("CPU Clock: %ldMHz\n", clk_get_rate(clk) / 1000000);
	clk_put(clk);
पूर्ण
