<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hisilicon HiP04 घड़ी driver
 *
 * Copyright (c) 2013-2014 Hisilicon Limited.
 * Copyright (c) 2013-2014 Linaro Limited.
 *
 * Author: Haojian Zhuang <haojian.zhuang@linaro.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/hip04-घड़ी.h>

#समावेश "clk.h"

/* fixed rate घड़ीs */
अटल काष्ठा hisi_fixed_rate_घड़ी hip04_fixed_rate_clks[] __initdata = अणु
	अणु HIP04_OSC50M,   "osc50m",   शून्य, 0, 50000000, पूर्ण,
	अणु HIP04_CLK_50M,  "clk50m",   शून्य, 0, 50000000, पूर्ण,
	अणु HIP04_CLK_168M, "clk168m",  शून्य, 0, 168750000, पूर्ण,
पूर्ण;

अटल व्योम __init hip04_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा hisi_घड़ी_data *clk_data;

	clk_data = hisi_clk_init(np, HIP04_NR_CLKS);
	अगर (!clk_data)
		वापस;

	hisi_clk_रेजिस्टर_fixed_rate(hip04_fixed_rate_clks,
				     ARRAY_SIZE(hip04_fixed_rate_clks),
				     clk_data);
पूर्ण
CLK_OF_DECLARE(hip04_clk, "hisilicon,hip04-clock", hip04_clk_init);
