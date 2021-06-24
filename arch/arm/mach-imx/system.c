<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 1999 ARM Limited
 * Copyright (C) 2000 Deep Blue Solutions Ltd
 * Copyright 2006-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2008 Juergen Beisert, kernel@pengutronix.de
 * Copyright 2009 Ilya Yanok, Emcraft Systems Ltd, yanok@emcraft.com
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>

#समावेश "common.h"
#समावेश "hardware.h"

अटल व्योम __iomem *wकरोg_base;
अटल काष्ठा clk *wकरोg_clk;
अटल पूर्णांक wcr_enable = (1 << 2);

/*
 * Reset the प्रणाली. It is called by machine_restart().
 */
व्योम mxc_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	अगर (!wकरोg_base)
		जाओ reset_fallback;

	अगर (!IS_ERR(wकरोg_clk))
		clk_enable(wकरोg_clk);

	/* Assert SRS संकेत */
	imx_ग_लिखोw(wcr_enable, wकरोg_base);
	/*
	 * Due to imx6q errata ERR004346 (WDOG: WDOG SRS bit requires to be
	 * written twice), we add another two ग_लिखोs to ensure there must be at
	 * least two ग_लिखोs happen in the same one 32kHz घड़ी period.  We save
	 * the target check here, since the ग_लिखोs shouldn't be a huge burden
	 * क्रम other platक्रमms.
	 */
	imx_ग_लिखोw(wcr_enable, wकरोg_base);
	imx_ग_लिखोw(wcr_enable, wकरोg_base);

	/* रुको क्रम reset to निश्चित... */
	mdelay(500);

	pr_err("%s: Watchdog reset failed to assert reset\n", __func__);

	/* delay to allow the serial port to show the message */
	mdelay(50);

reset_fallback:
	/* we'll take a jump through zero as a poor second */
	soft_restart(0);
पूर्ण

व्योम __init mxc_arch_reset_init(व्योम __iomem *base)
अणु
	wकरोg_base = base;

	wकरोg_clk = clk_get_sys("imx2-wdt.0", शून्य);
	अगर (IS_ERR(wकरोg_clk))
		pr_warn("%s: failed to get wdog clock\n", __func__);
	अन्यथा
		clk_prepare(wकरोg_clk);
पूर्ण

#अगर_घोषित CONFIG_SOC_IMX1
व्योम __init imx1_reset_init(व्योम __iomem *base)
अणु
	wcr_enable = (1 << 0);
	mxc_arch_reset_init(base);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CACHE_L2X0
व्योम __init imx_init_l2cache(व्योम)
अणु
	व्योम __iomem *l2x0_base;
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक val;

	np = of_find_compatible_node(शून्य, शून्य, "arm,pl310-cache");
	अगर (!np)
		वापस;

	l2x0_base = of_iomap(np, 0);
	अगर (!l2x0_base)
		जाओ put_node;

	अगर (!(पढ़ोl_relaxed(l2x0_base + L2X0_CTRL) & L2X0_CTRL_EN)) अणु
		/* Configure the L2 PREFETCH and POWER रेजिस्टरs */
		val = पढ़ोl_relaxed(l2x0_base + L310_PREFETCH_CTRL);
		val |= L310_PREFETCH_CTRL_DBL_LINEFILL |
			L310_PREFETCH_CTRL_INSTR_PREFETCH |
			L310_PREFETCH_CTRL_DATA_PREFETCH;

		/* Set perfetch offset to improve perक्रमmance */
		val &= ~L310_PREFETCH_CTRL_OFFSET_MASK;
		val |= 15;

		ग_लिखोl_relaxed(val, l2x0_base + L310_PREFETCH_CTRL);
	पूर्ण

	iounmap(l2x0_base);
put_node:
	of_node_put(np);
पूर्ण
#पूर्ण_अगर
