<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aptina Sensor PLL Configuration
 *
 * Copyright (C) 2012 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/gcd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/lcm.h>
#समावेश <linux/module.h>

#समावेश "aptina-pll.h"

पूर्णांक aptina_pll_calculate(काष्ठा device *dev,
			 स्थिर काष्ठा aptina_pll_limits *limits,
			 काष्ठा aptina_pll *pll)
अणु
	अचिन्हित पूर्णांक mf_min;
	अचिन्हित पूर्णांक mf_max;
	अचिन्हित पूर्णांक p1_min;
	अचिन्हित पूर्णांक p1_max;
	अचिन्हित पूर्णांक p1;
	अचिन्हित पूर्णांक भाग;

	dev_dbg(dev, "PLL: ext clock %u pix clock %u\n",
		pll->ext_घड़ी, pll->pix_घड़ी);

	अगर (pll->ext_घड़ी < limits->ext_घड़ी_min ||
	    pll->ext_घड़ी > limits->ext_घड़ी_max) अणु
		dev_err(dev, "pll: invalid external clock frequency.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pll->pix_घड़ी == 0 || pll->pix_घड़ी > limits->pix_घड़ी_max) अणु
		dev_err(dev, "pll: invalid pixel clock frequency.\n");
		वापस -EINVAL;
	पूर्ण

	/* Compute the multiplier M and combined N*P1 भागisor. */
	भाग = gcd(pll->pix_घड़ी, pll->ext_घड़ी);
	pll->m = pll->pix_घड़ी / भाग;
	भाग = pll->ext_घड़ी / भाग;

	/* We now have the smallest M and N*P1 values that will result in the
	 * desired pixel घड़ी frequency, but they might be out of the valid
	 * range. Compute the factor by which we should multiply them given the
	 * following स्थिरraपूर्णांकs:
	 *
	 * - minimum/maximum multiplier
	 * - minimum/maximum multiplier output घड़ी frequency assuming the
	 *   minimum/maximum N value
	 * - minimum/maximum combined N*P1 भागisor
	 */
	mf_min = DIV_ROUND_UP(limits->m_min, pll->m);
	mf_min = max(mf_min, limits->out_घड़ी_min /
		     (pll->ext_घड़ी / limits->n_min * pll->m));
	mf_min = max(mf_min, limits->n_min * limits->p1_min / भाग);
	mf_max = limits->m_max / pll->m;
	mf_max = min(mf_max, limits->out_घड़ी_max /
		    (pll->ext_घड़ी / limits->n_max * pll->m));
	mf_max = min(mf_max, DIV_ROUND_UP(limits->n_max * limits->p1_max, भाग));

	dev_dbg(dev, "pll: mf min %u max %u\n", mf_min, mf_max);
	अगर (mf_min > mf_max) अणु
		dev_err(dev, "pll: no valid combined N*P1 divisor.\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * We're looking क्रम the highest acceptable P1 value क्रम which a
	 * multiplier factor MF exists that fulfills the following conditions:
	 *
	 * 1. p1 is in the [p1_min, p1_max] range given by the limits and is
	 *    even
	 * 2. mf is in the [mf_min, mf_max] range computed above
	 * 3. भाग * mf is a multiple of p1, in order to compute
	 *	n = भाग * mf / p1
	 *	m = pll->m * mf
	 * 4. the पूर्णांकernal घड़ी frequency, given by ext_घड़ी / n, is in the
	 *    [पूर्णांक_घड़ी_min, पूर्णांक_घड़ी_max] range given by the limits
	 * 5. the output घड़ी frequency, given by ext_घड़ी / n * m, is in the
	 *    [out_घड़ी_min, out_घड़ी_max] range given by the limits
	 *
	 * The first naive approach is to iterate over all p1 values acceptable
	 * according to (1) and all mf values acceptable according to (2), and
	 * stop at the first combination that fulfills (3), (4) and (5). This
	 * has a O(n^2) complनिकासy.
	 *
	 * Instead of iterating over all mf values in the [mf_min, mf_max] range
	 * we can compute the mf increment between two acceptable values
	 * according to (3) with
	 *
	 *	mf_inc = p1 / gcd(भाग, p1)			(6)
	 *
	 * and round the minimum up to the nearest multiple of mf_inc. This will
	 * restrict the number of mf values to be checked.
	 *
	 * Furthermore, conditions (4) and (5) only restrict the range of
	 * acceptable p1 and mf values by modअगरying the minimum and maximum
	 * limits. (5) can be expressed as
	 *
	 *	ext_घड़ी / (भाग * mf / p1) * m * mf >= out_घड़ी_min
	 *	ext_घड़ी / (भाग * mf / p1) * m * mf <= out_घड़ी_max
	 *
	 * or
	 *
	 *	p1 >= out_घड़ी_min * भाग / (ext_घड़ी * m)	(7)
	 *	p1 <= out_घड़ी_max * भाग / (ext_घड़ी * m)
	 *
	 * Similarly, (4) can be expressed as
	 *
	 *	mf >= ext_घड़ी * p1 / (पूर्णांक_घड़ी_max * भाग)	(8)
	 *	mf <= ext_घड़ी * p1 / (पूर्णांक_घड़ी_min * भाग)
	 *
	 * We can thus iterate over the restricted p1 range defined by the
	 * combination of (1) and (7), and then compute the restricted mf range
	 * defined by the combination of (2), (6) and (8). If the resulting mf
	 * range is not empty, any value in the mf range is acceptable. We thus
	 * select the mf lwoer bound and the corresponding p1 value.
	 */
	अगर (limits->p1_min == 0) अणु
		dev_err(dev, "pll: P1 minimum value must be >0.\n");
		वापस -EINVAL;
	पूर्ण

	p1_min = max(limits->p1_min, DIV_ROUND_UP(limits->out_घड़ी_min * भाग,
		     pll->ext_घड़ी * pll->m));
	p1_max = min(limits->p1_max, limits->out_घड़ी_max * भाग /
		     (pll->ext_घड़ी * pll->m));

	क्रम (p1 = p1_max & ~1; p1 >= p1_min; p1 -= 2) अणु
		अचिन्हित पूर्णांक mf_inc = p1 / gcd(भाग, p1);
		अचिन्हित पूर्णांक mf_high;
		अचिन्हित पूर्णांक mf_low;

		mf_low = roundup(max(mf_min, DIV_ROUND_UP(pll->ext_घड़ी * p1,
					limits->पूर्णांक_घड़ी_max * भाग)), mf_inc);
		mf_high = min(mf_max, pll->ext_घड़ी * p1 /
			      (limits->पूर्णांक_घड़ी_min * भाग));

		अगर (mf_low > mf_high)
			जारी;

		pll->n = भाग * mf_low / p1;
		pll->m *= mf_low;
		pll->p1 = p1;
		dev_dbg(dev, "PLL: N %u M %u P1 %u\n", pll->n, pll->m, pll->p1);
		वापस 0;
	पूर्ण

	dev_err(dev, "pll: no valid N and P1 divisors found.\n");
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(aptina_pll_calculate);

MODULE_DESCRIPTION("Aptina PLL Helpers");
MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_LICENSE("GPL v2");
