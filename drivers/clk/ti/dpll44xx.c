<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4-specअगरic DPLL control functions
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Rajendra Nayak
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/clk/ti.h>

#समावेश "clock.h"

/*
 * Maximum DPLL input frequency (FINT) and output frequency (FOUT) that
 * can supported when using the DPLL low-घातer mode. Frequencies are
 * defined in OMAP4430/60 Public TRM section 3.6.3.3.2 "Enable Control,
 * Status, and Low-Power Operation Mode".
 */
#घोषणा OMAP4_DPLL_LP_Fपूर्णांक_उच्च	1000000
#घोषणा OMAP4_DPLL_LP_FOUT_MAX	100000000

/*
 * Bitfield declarations
 */
#घोषणा OMAP4430_DPLL_CLKOUT_GATE_CTRL_MASK		BIT(8)
#घोषणा OMAP4430_DPLL_CLKOUTX2_GATE_CTRL_MASK		BIT(10)
#घोषणा OMAP4430_DPLL_REGM4XEN_MASK			BIT(11)

/* Static rate multiplier क्रम OMAP4 REGM4XEN घड़ीs */
#घोषणा OMAP4430_REGM4XEN_MULT				4

अटल व्योम omap4_dpllmx_allow_gatectrl(काष्ठा clk_hw_omap *clk)
अणु
	u32 v;
	u32 mask;

	अगर (!clk)
		वापस;

	mask = clk->flags & CLOCK_CLKOUTX2 ?
			OMAP4430_DPLL_CLKOUTX2_GATE_CTRL_MASK :
			OMAP4430_DPLL_CLKOUT_GATE_CTRL_MASK;

	v = ti_clk_ll_ops->clk_पढ़ोl(&clk->clksel_reg);
	/* Clear the bit to allow gatectrl */
	v &= ~mask;
	ti_clk_ll_ops->clk_ग_लिखोl(v, &clk->clksel_reg);
पूर्ण

अटल व्योम omap4_dpllmx_deny_gatectrl(काष्ठा clk_hw_omap *clk)
अणु
	u32 v;
	u32 mask;

	अगर (!clk)
		वापस;

	mask = clk->flags & CLOCK_CLKOUTX2 ?
			OMAP4430_DPLL_CLKOUTX2_GATE_CTRL_MASK :
			OMAP4430_DPLL_CLKOUT_GATE_CTRL_MASK;

	v = ti_clk_ll_ops->clk_पढ़ोl(&clk->clksel_reg);
	/* Set the bit to deny gatectrl */
	v |= mask;
	ti_clk_ll_ops->clk_ग_लिखोl(v, &clk->clksel_reg);
पूर्ण

स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap4_dpllmx = अणु
	.allow_idle	= omap4_dpllmx_allow_gatectrl,
	.deny_idle      = omap4_dpllmx_deny_gatectrl,
पूर्ण;

/**
 * omap4_dpll_lpmode_recalc - compute DPLL low-घातer setting
 * @dd: poपूर्णांकer to the dpll data काष्ठाure
 *
 * Calculates अगर low-घातer mode can be enabled based upon the last
 * multiplier and भागider values calculated. If low-घातer mode can be
 * enabled, then the bit to enable low-घातer mode is stored in the
 * last_rounded_lpmode variable. This implementation is based upon the
 * criteria क्रम enabling low-घातer mode as described in the OMAP4430/60
 * Public TRM section 3.6.3.3.2 "Enable Control, Status, and Low-Power
 * Operation Mode".
 */
अटल व्योम omap4_dpll_lpmode_recalc(काष्ठा dpll_data *dd)
अणु
	दीर्घ fपूर्णांक, fout;

	fपूर्णांक = clk_hw_get_rate(dd->clk_ref) / (dd->last_rounded_n + 1);
	fout = fपूर्णांक * dd->last_rounded_m;

	अगर ((fपूर्णांक < OMAP4_DPLL_LP_Fपूर्णांक_उच्च) && (fout < OMAP4_DPLL_LP_FOUT_MAX))
		dd->last_rounded_lpmode = 1;
	अन्यथा
		dd->last_rounded_lpmode = 0;
पूर्ण

/**
 * omap4_dpll_regm4xen_recalc - compute DPLL rate, considering REGM4XEN bit
 * @hw: poपूर्णांकer to the घड़ी to compute the rate क्रम
 * @parent_rate: घड़ी rate of the DPLL parent
 *
 * Compute the output rate क्रम the OMAP4 DPLL represented by @clk.
 * Takes the REGM4XEN bit पूर्णांकo consideration, which is needed क्रम the
 * OMAP4 ABE DPLL.  Returns the DPLL's output rate (beक्रमe M-भागiders)
 * upon success, or 0 upon error.
 */
अचिन्हित दीर्घ omap4_dpll_regm4xen_recalc(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	u32 v;
	अचिन्हित दीर्घ rate;
	काष्ठा dpll_data *dd;

	अगर (!clk || !clk->dpll_data)
		वापस 0;

	dd = clk->dpll_data;

	rate = omap2_get_dpll_rate(clk);

	/* regm4xen adds a multiplier of 4 to DPLL calculations */
	v = ti_clk_ll_ops->clk_पढ़ोl(&dd->control_reg);
	अगर (v & OMAP4430_DPLL_REGM4XEN_MASK)
		rate *= OMAP4430_REGM4XEN_MULT;

	वापस rate;
पूर्ण

/**
 * omap4_dpll_regm4xen_round_rate - round DPLL rate, considering REGM4XEN bit
 * @hw: काष्ठा hw_clk containing the काष्ठा clk * of the DPLL to round a rate क्रम
 * @target_rate: the desired rate of the DPLL
 * @parent_rate: घड़ी rate of the DPLL parent
 *
 * Compute the rate that would be programmed पूर्णांकo the DPLL hardware
 * क्रम @clk अगर set_rate() were to be provided with the rate
 * @target_rate.  Takes the REGM4XEN bit पूर्णांकo consideration, which is
 * needed क्रम the OMAP4 ABE DPLL.  Returns the rounded rate (beक्रमe
 * M-भागiders) upon success, -EINVAL अगर @clk is null or not a DPLL, or
 * ~0 अगर an error occurred in omap2_dpll_round_rate().
 */
दीर्घ omap4_dpll_regm4xen_round_rate(काष्ठा clk_hw *hw,
				    अचिन्हित दीर्घ target_rate,
				    अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	काष्ठा dpll_data *dd;
	दीर्घ r;

	अगर (!clk || !clk->dpll_data)
		वापस -EINVAL;

	dd = clk->dpll_data;

	dd->last_rounded_m4xen = 0;

	/*
	 * First try to compute the DPLL configuration क्रम
	 * target rate without using the 4X multiplier.
	 */
	r = omap2_dpll_round_rate(hw, target_rate, शून्य);
	अगर (r != ~0)
		जाओ out;

	/*
	 * If we did not find a valid DPLL configuration, try again, but
	 * this समय see अगर using the 4X multiplier can help. Enabling the
	 * 4X multiplier is equivalent to भागiding the target rate by 4.
	 */
	r = omap2_dpll_round_rate(hw, target_rate / OMAP4430_REGM4XEN_MULT,
				  शून्य);
	अगर (r == ~0)
		वापस r;

	dd->last_rounded_rate *= OMAP4430_REGM4XEN_MULT;
	dd->last_rounded_m4xen = 1;

out:
	omap4_dpll_lpmode_recalc(dd);

	वापस dd->last_rounded_rate;
पूर्ण

/**
 * omap4_dpll_regm4xen_determine_rate - determine rate क्रम a DPLL
 * @hw: poपूर्णांकer to the घड़ी to determine rate क्रम
 * @req: target rate request
 *
 * Determines which DPLL mode to use क्रम reaching a desired rate.
 * Checks whether the DPLL shall be in bypass or locked mode, and अगर
 * locked, calculates the M,N values क्रम the DPLL via round-rate.
 * Returns 0 on success and a negative error value otherwise.
 */
पूर्णांक omap4_dpll_regm4xen_determine_rate(काष्ठा clk_hw *hw,
				       काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	काष्ठा dpll_data *dd;

	अगर (!req->rate)
		वापस -EINVAL;

	dd = clk->dpll_data;
	अगर (!dd)
		वापस -EINVAL;

	अगर (clk_hw_get_rate(dd->clk_bypass) == req->rate &&
	    (dd->modes & (1 << DPLL_LOW_POWER_BYPASS))) अणु
		req->best_parent_hw = dd->clk_bypass;
	पूर्ण अन्यथा अणु
		req->rate = omap4_dpll_regm4xen_round_rate(hw, req->rate,
						&req->best_parent_rate);
		req->best_parent_hw = dd->clk_ref;
	पूर्ण

	req->best_parent_rate = req->rate;

	वापस 0;
पूर्ण
