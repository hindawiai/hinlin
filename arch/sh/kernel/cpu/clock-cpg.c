<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/clk.h>
#समावेश <linux/compiler.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/clkdev.h>
#समावेश <यंत्र/घड़ी.h>

अटल काष्ठा clk master_clk = अणु
	.flags		= CLK_ENABLE_ON_INIT,
	.rate		= CONFIG_SH_PCLK_FREQ,
पूर्ण;

अटल काष्ठा clk peripheral_clk = अणु
	.parent		= &master_clk,
	.flags		= CLK_ENABLE_ON_INIT,
पूर्ण;

अटल काष्ठा clk bus_clk = अणु
	.parent		= &master_clk,
	.flags		= CLK_ENABLE_ON_INIT,
पूर्ण;

अटल काष्ठा clk cpu_clk = अणु
	.parent		= &master_clk,
	.flags		= CLK_ENABLE_ON_INIT,
पूर्ण;

/*
 * The ordering of these घड़ीs matters, करो not change it.
 */
अटल काष्ठा clk *onchip_घड़ीs[] = अणु
	&master_clk,
	&peripheral_clk,
	&bus_clk,
	&cpu_clk,
पूर्ण;

अटल काष्ठा clk_lookup lookups[] = अणु
	/* मुख्य घड़ीs */
	CLKDEV_CON_ID("master_clk", &master_clk),
	CLKDEV_CON_ID("peripheral_clk", &peripheral_clk),
	CLKDEV_CON_ID("bus_clk", &bus_clk),
	CLKDEV_CON_ID("cpu_clk", &cpu_clk),
पूर्ण;

पूर्णांक __init __deprecated cpg_clk_init(व्योम)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < ARRAY_SIZE(onchip_घड़ीs); i++) अणु
		काष्ठा clk *clk = onchip_घड़ीs[i];
		arch_init_clk_ops(&clk->ops, i);
		अगर (clk->ops)
			ret |= clk_रेजिस्टर(clk);
	पूर्ण

	clkdev_add_table(lookups, ARRAY_SIZE(lookups));

	clk_add_alias("fck", "sh-tmu-sh3.0", "peripheral_clk", शून्य);
	clk_add_alias("fck", "sh-tmu.0", "peripheral_clk", शून्य);
	clk_add_alias("fck", "sh-tmu.1", "peripheral_clk", शून्य);
	clk_add_alias("fck", "sh-tmu.2", "peripheral_clk", शून्य);
	clk_add_alias("fck", "sh-mtu2", "peripheral_clk", शून्य);
	clk_add_alias("fck", "sh-cmt-16.0", "peripheral_clk", शून्य);
	clk_add_alias("fck", "sh-cmt-32.0", "peripheral_clk", शून्य);

	वापस ret;
पूर्ण

/*
 * Placeholder क्रम compatibility, until the lazy CPUs करो this
 * on their own.
 */
पूर्णांक __init __weak arch_clk_init(व्योम)
अणु
	वापस cpg_clk_init();
पूर्ण
