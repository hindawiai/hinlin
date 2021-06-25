<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/घड़ीsource.h>

बाह्य काष्ठा of_device_id __समयr_of_table[];

अटल स्थिर काष्ठा of_device_id __समयr_of_table_sentinel
	__used __section("__timer_of_table_end");

व्योम __init समयr_probe(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *match;
	of_init_fn_1_ret init_func_ret;
	अचिन्हित समयrs = 0;
	पूर्णांक ret;

	क्रम_each_matching_node_and_match(np, __समयr_of_table, &match) अणु
		अगर (!of_device_is_available(np))
			जारी;

		init_func_ret = match->data;

		ret = init_func_ret(np);
		अगर (ret) अणु
			अगर (ret != -EPROBE_DEFER)
				pr_err("Failed to initialize '%pOF': %d\n", np,
				       ret);
			जारी;
		पूर्ण

		समयrs++;
	पूर्ण

	समयrs += acpi_probe_device_table(समयr);

	अगर (!समयrs)
		pr_crit("%s: no matching timers found\n", __func__);
पूर्ण
