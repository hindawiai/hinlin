<शैली गुरु>
/*
 * Runसमय PM support code क्रम DaVinci
 *
 * Author: Kevin Hilman
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#समावेश <linux/init.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>

अटल काष्ठा dev_pm_करोमुख्य davinci_pm_करोमुख्य = अणु
	.ops = अणु
		USE_PM_CLK_RUNTIME_OPS
		USE_PLATFORM_PM_SLEEP_OPS
	पूर्ण,
पूर्ण;

अटल काष्ठा pm_clk_notअगरier_block platक्रमm_bus_notअगरier = अणु
	.pm_करोमुख्य = &davinci_pm_करोमुख्य,
	.con_ids = अणु "fck", "master", "slave", शून्य पूर्ण,
पूर्ण;

अटल पूर्णांक __init davinci_pm_runसमय_init(व्योम)
अणु
	अगर (of_have_populated_dt())
		वापस 0;

	/* Use pm_clk as fallback अगर we're not using genpd. */
	pm_clk_add_notअगरier(&platक्रमm_bus_type, &platक्रमm_bus_notअगरier);

	वापस 0;
पूर्ण
core_initcall(davinci_pm_runसमय_init);
