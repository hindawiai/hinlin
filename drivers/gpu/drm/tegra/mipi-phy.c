<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 NVIDIA Corporation
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>

#समावेश "mipi-phy.h"

/*
 * Default D-PHY timings based on MIPI D-PHY specअगरication. Derived from the
 * valid ranges specअगरied in Section 6.9, Table 14, Page 40 of the D-PHY
 * specअगरication (v1.2) with minor adjusपंचांगents.
 */
पूर्णांक mipi_dphy_timing_get_शेष(काष्ठा mipi_dphy_timing *timing,
				 अचिन्हित दीर्घ period)
अणु
	timing->clkmiss = 0;
	timing->clkpost = 70 + 52 * period;
	timing->clkpre = 8;
	timing->clkprepare = 65;
	timing->clksettle = 95;
	timing->clktermen = 0;
	timing->clktrail = 80;
	timing->clkzero = 260;
	timing->dtermen = 0;
	timing->eot = 0;
	timing->hsनिकास = 120;
	timing->hsprepare = 65 + 5 * period;
	timing->hszero = 145 + 5 * period;
	timing->hssettle = 85 + 6 * period;
	timing->hsskip = 40;

	/*
	 * The MIPI D-PHY specअगरication (Section 6.9, v1.2, Table 14, Page 40)
	 * contains this क्रमmula as:
	 *
	 *     T_HS-TRAIL = max(n * 8 * period, 60 + n * 4 * period)
	 *
	 * where n = 1 क्रम क्रमward-direction HS mode and n = 4 क्रम reverse-
	 * direction HS mode. There's only one setting and this function करोes
	 * not parameterize on anything other that period, so this code will
	 * assumes that reverse-direction HS mode is supported and uses n = 4.
	 */
	timing->hstrail = max(4 * 8 * period, 60 + 4 * 4 * period);

	timing->init = 100000;
	timing->lpx = 60;
	timing->taget = 5 * timing->lpx;
	timing->tago = 4 * timing->lpx;
	timing->tasure = 2 * timing->lpx;
	timing->wakeup = 1000000;

	वापस 0;
पूर्ण

/*
 * Validate D-PHY timing according to MIPI D-PHY specअगरication (v1.2, Section
 * Section 6.9 "Global Operation Timing Parameters").
 */
पूर्णांक mipi_dphy_timing_validate(काष्ठा mipi_dphy_timing *timing,
			      अचिन्हित दीर्घ period)
अणु
	अगर (timing->clkmiss > 60)
		वापस -EINVAL;

	अगर (timing->clkpost < (60 + 52 * period))
		वापस -EINVAL;

	अगर (timing->clkpre < 8)
		वापस -EINVAL;

	अगर (timing->clkprepare < 38 || timing->clkprepare > 95)
		वापस -EINVAL;

	अगर (timing->clksettle < 95 || timing->clksettle > 300)
		वापस -EINVAL;

	अगर (timing->clktermen > 38)
		वापस -EINVAL;

	अगर (timing->clktrail < 60)
		वापस -EINVAL;

	अगर (timing->clkprepare + timing->clkzero < 300)
		वापस -EINVAL;

	अगर (timing->dtermen > 35 + 4 * period)
		वापस -EINVAL;

	अगर (timing->eot > 105 + 12 * period)
		वापस -EINVAL;

	अगर (timing->hsनिकास < 100)
		वापस -EINVAL;

	अगर (timing->hsprepare < 40 + 4 * period ||
	    timing->hsprepare > 85 + 6 * period)
		वापस -EINVAL;

	अगर (timing->hsprepare + timing->hszero < 145 + 10 * period)
		वापस -EINVAL;

	अगर ((timing->hssettle < 85 + 6 * period) ||
	    (timing->hssettle > 145 + 10 * period))
		वापस -EINVAL;

	अगर (timing->hsskip < 40 || timing->hsskip > 55 + 4 * period)
		वापस -EINVAL;

	अगर (timing->hstrail < max(8 * period, 60 + 4 * period))
		वापस -EINVAL;

	अगर (timing->init < 100000)
		वापस -EINVAL;

	अगर (timing->lpx < 50)
		वापस -EINVAL;

	अगर (timing->taget != 5 * timing->lpx)
		वापस -EINVAL;

	अगर (timing->tago != 4 * timing->lpx)
		वापस -EINVAL;

	अगर (timing->tasure < timing->lpx || timing->tasure > 2 * timing->lpx)
		वापस -EINVAL;

	अगर (timing->wakeup < 1000000)
		वापस -EINVAL;

	वापस 0;
पूर्ण
