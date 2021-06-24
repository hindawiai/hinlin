<शैली गुरु>
/*
 * Copyright (C) 2012-2014 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */


#समावेश <linux/init.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>

#समावेश "bcm_kona_smc.h"
#समावेश "kona_l2_cache.h"

व्योम __init kona_l2_cache_init(व्योम)
अणु
	अचिन्हित पूर्णांक result;
	पूर्णांक ret;

	ret = bcm_kona_smc_init();
	अगर (ret) अणु
		pr_info("Secure API not available (%d). Skipping L2 init.\n",
			ret);
		वापस;
	पूर्ण

	result = bcm_kona_smc(SSAPI_ENABLE_L2_CACHE, 0, 0, 0, 0);
	अगर (result != SEC_ROM_RET_OK) अणु
		pr_err("Secure Monitor call failed (%u)! Skipping L2 init.\n",
			result);
		वापस;
	पूर्ण

	/*
	 * The aux_val and aux_mask have no effect since L2 cache is alपढ़ोy
	 * enabled.  Pass 0s क्रम aux_val and 1s क्रम aux_mask क्रम शेष value.
	 */
	ret = l2x0_of_init(0, ~0);
	अगर (ret)
		pr_err("Couldn't enable L2 cache: %d\n", ret);
पूर्ण
