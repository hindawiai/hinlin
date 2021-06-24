<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap2/mcbsp.c
 *
 * Copyright (C) 2008 Instituto Nokia de Tecnologia
 * Contact: Eduarकरो Valentin <eduarकरो.valentin@indt.org.br>
 *
 * Multichannel mode not supported.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_data/asoc-ti-mcbsp.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/omap-dma.h>

#समावेश "soc.h"
#समावेश "omap_device.h"
#समावेश "clock.h"

/*
 * FIXME: Find a mechanism to enable/disable runसमय the McBSP ICLK स्वतःidle.
 * Sidetone needs non-gated ICLK and sidetone स्वतःidle is broken.
 */
#समावेश "cm3xxx.h"
#समावेश "cm-regbits-34xx.h"

अटल पूर्णांक omap3_mcbsp_क्रमce_ick_on(काष्ठा clk *clk, bool क्रमce_on)
अणु
	अगर (!clk)
		वापस 0;

	अगर (क्रमce_on)
		वापस omap2_clk_deny_idle(clk);
	अन्यथा
		वापस omap2_clk_allow_idle(clk);
पूर्ण

व्योम __init omap3_mcbsp_init_pdata_callback(
					काष्ठा omap_mcbsp_platक्रमm_data *pdata)
अणु
	अगर (!pdata)
		वापस;

	pdata->क्रमce_ick_on = omap3_mcbsp_क्रमce_ick_on;
पूर्ण
