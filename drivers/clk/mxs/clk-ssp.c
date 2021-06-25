<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 DENX Software Engineering, GmbH
 *
 * Pulled from code:
 * Portions copyright (C) 2003 Russell King, PXA MMCI Driver
 * Portions copyright (C) 2004-2005 Pierre Ossman, W83L51xD SD/MMC driver
 *
 * Copyright 2008 Embedded Alley Solutions, Inc.
 * Copyright 2009-2011 Freescale Semiconductor, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/spi/mxs-spi.h>

व्योम mxs_ssp_set_clk_rate(काष्ठा mxs_ssp *ssp, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक ssp_clk, ssp_sck;
	u32 घड़ी_भागide, घड़ी_rate;
	u32 val;

	ssp_clk = clk_get_rate(ssp->clk);

	क्रम (घड़ी_भागide = 2; घड़ी_भागide <= 254; घड़ी_भागide += 2) अणु
		घड़ी_rate = DIV_ROUND_UP(ssp_clk, rate * घड़ी_भागide);
		घड़ी_rate = (घड़ी_rate > 0) ? घड़ी_rate - 1 : 0;
		अगर (घड़ी_rate <= 255)
			अवरोध;
	पूर्ण

	अगर (घड़ी_भागide > 254) अणु
		dev_err(ssp->dev,
			"%s: cannot set clock to %d\n", __func__, rate);
		वापस;
	पूर्ण

	ssp_sck = ssp_clk / घड़ी_भागide / (1 + घड़ी_rate);

	val = पढ़ोl(ssp->base + HW_SSP_TIMING(ssp));
	val &= ~(BM_SSP_TIMING_CLOCK_DIVIDE | BM_SSP_TIMING_CLOCK_RATE);
	val |= BF_SSP(घड़ी_भागide, TIMING_CLOCK_DIVIDE);
	val |= BF_SSP(घड़ी_rate, TIMING_CLOCK_RATE);
	ग_लिखोl(val, ssp->base + HW_SSP_TIMING(ssp));

	ssp->clk_rate = ssp_sck;

	dev_dbg(ssp->dev,
		"%s: clock_divide %d, clock_rate %d, ssp_clk %d, rate_actual %d, rate_requested %d\n",
		__func__, घड़ी_भागide, घड़ी_rate, ssp_clk, ssp_sck, rate);
पूर्ण
EXPORT_SYMBOL_GPL(mxs_ssp_set_clk_rate);
