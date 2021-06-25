<शैली गुरु>
/*
 * Runसमय PM support code
 *
 *  Copyright (C) 2009-2010 Magnus Damm
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/sh_clk.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/slab.h>

अटल काष्ठा dev_pm_करोमुख्य शेष_pm_करोमुख्य = अणु
	.ops = अणु
		USE_PM_CLK_RUNTIME_OPS
		USE_PLATFORM_PM_SLEEP_OPS
	पूर्ण,
पूर्ण;

अटल काष्ठा pm_clk_notअगरier_block platक्रमm_bus_notअगरier = अणु
	.pm_करोमुख्य = &शेष_pm_करोमुख्य,
	.con_ids = अणु शून्य, पूर्ण,
पूर्ण;

अटल पूर्णांक __init sh_pm_runसमय_init(व्योम)
अणु
	pm_clk_add_notअगरier(&platक्रमm_bus_type, &platक्रमm_bus_notअगरier);
	वापस 0;
पूर्ण
core_initcall(sh_pm_runसमय_init);
