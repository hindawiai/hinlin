<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PM करोमुख्य driver क्रम Keystone2 devices
 *
 * Copyright 2013 Texas Instruments, Inc.
 *	Santosh Shilimkar <santosh.shillimkar@ti.com>
 *
 * Based on Kevins work on DAVINCI SOCs
 *	Kevin Hilman <khilman@linaro.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>

#समावेश "keystone.h"

अटल काष्ठा dev_pm_करोमुख्य keystone_pm_करोमुख्य = अणु
	.ops = अणु
		USE_PM_CLK_RUNTIME_OPS
		USE_PLATFORM_PM_SLEEP_OPS
	पूर्ण,
पूर्ण;

अटल काष्ठा pm_clk_notअगरier_block platक्रमm_करोमुख्य_notअगरier = अणु
	.pm_करोमुख्य = &keystone_pm_करोमुख्य,
	.con_ids = अणु शून्य पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_keystone_table[] = अणु
	अणु.compatible = "ti,k2hk"पूर्ण,
	अणु.compatible = "ti,k2e"पूर्ण,
	अणु.compatible = "ti,k2l"पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

पूर्णांक __init keystone_pm_runसमय_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_matching_node(शून्य, of_keystone_table);
	अगर (!np)
		वापस 0;

	pm_clk_add_notअगरier(&platक्रमm_bus_type, &platक्रमm_करोमुख्य_notअगरier);

	वापस 0;
पूर्ण
