<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2/3/4 DPLL घड़ी functions
 *
 * Copyright (C) 2005-2008 Texas Instruments, Inc.
 * Copyright (C) 2004-2010 Nokia Corporation
 *
 * Contacts:
 * Riअक्षरd Woodruff <r-woodruff2@ti.com>
 * Paul Walmsley
 */
#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk/ti.h>

#समावेश <यंत्र/भाग64.h>

#समावेश "clock.h"

/* DPLL rate rounding: minimum DPLL multiplier, भागider values */
#घोषणा DPLL_MIN_MULTIPLIER		2
#घोषणा DPLL_MIN_DIVIDER		1

/* Possible error results from _dpll_test_mult */
#घोषणा DPLL_MULT_UNDERFLOW		-1

/*
 * Scale factor to mitigate rounकरोff errors in DPLL rate rounding.
 * The higher the scale factor, the greater the risk of arithmetic overflow,
 * but the बंदr the rounded rate to the target rate.  DPLL_SCALE_FACTOR
 * must be a घातer of DPLL_SCALE_BASE.
 */
#घोषणा DPLL_SCALE_FACTOR		64
#घोषणा DPLL_SCALE_BASE			2
#घोषणा DPLL_ROUNDING_VAL		((DPLL_SCALE_BASE / 2) * \
					 (DPLL_SCALE_FACTOR / DPLL_SCALE_BASE))

/*
 * DPLL valid Fपूर्णांक frequency range क्रम OMAP36xx and OMAP4xxx.
 * From device data manual section 4.3 "DPLL and DLL Specifications".
 */
#घोषणा OMAP3PLUS_DPLL_FINT_JTYPE_MIN	500000
#घोषणा OMAP3PLUS_DPLL_FINT_JTYPE_MAX	2500000

/* _dpll_test_fपूर्णांक() वापस codes */
#घोषणा DPLL_FINT_UNDERFLOW		-1
#घोषणा DPLL_FINT_INVALID		-2

/* Private functions */

/*
 * _dpll_test_fपूर्णांक - test whether an Fपूर्णांक value is valid क्रम the DPLL
 * @clk: DPLL काष्ठा clk to test
 * @n: भागider value (N) to test
 *
 * Tests whether a particular भागider @n will result in a valid DPLL
 * पूर्णांकernal घड़ी frequency Fपूर्णांक. See the 34xx TRM 4.7.6.2 "DPLL Jitter
 * Correction".  Returns 0 अगर OK, -1 अगर the enclosing loop can terminate
 * (assuming that it is counting N upwards), or -2 अगर the enclosing loop
 * should skip to the next iteration (again assuming N is increasing).
 */
अटल पूर्णांक _dpll_test_fपूर्णांक(काष्ठा clk_hw_omap *clk, अचिन्हित पूर्णांक n)
अणु
	काष्ठा dpll_data *dd;
	दीर्घ fपूर्णांक, fपूर्णांक_min, fपूर्णांक_max;
	पूर्णांक ret = 0;

	dd = clk->dpll_data;

	/* DPLL भागider must result in a valid jitter correction val */
	fपूर्णांक = clk_hw_get_rate(clk_hw_get_parent(&clk->hw)) / n;

	अगर (dd->flags & DPLL_J_TYPE) अणु
		fपूर्णांक_min = OMAP3PLUS_DPLL_FINT_JTYPE_MIN;
		fपूर्णांक_max = OMAP3PLUS_DPLL_FINT_JTYPE_MAX;
	पूर्ण अन्यथा अणु
		fपूर्णांक_min = ti_clk_get_features()->fपूर्णांक_min;
		fपूर्णांक_max = ti_clk_get_features()->fपूर्णांक_max;
	पूर्ण

	अगर (!fपूर्णांक_min || !fपूर्णांक_max) अणु
		WARN(1, "No fint limits available!\n");
		वापस DPLL_FINT_INVALID;
	पूर्ण

	अगर (fपूर्णांक < ti_clk_get_features()->fपूर्णांक_min) अणु
		pr_debug("rejecting n=%d due to Fint failure, lowering max_divider\n",
			 n);
		dd->max_भागider = n;
		ret = DPLL_FINT_UNDERFLOW;
	पूर्ण अन्यथा अगर (fपूर्णांक > ti_clk_get_features()->fपूर्णांक_max) अणु
		pr_debug("rejecting n=%d due to Fint failure, boosting min_divider\n",
			 n);
		dd->min_भागider = n;
		ret = DPLL_FINT_INVALID;
	पूर्ण अन्यथा अगर (fपूर्णांक > ti_clk_get_features()->fपूर्णांक_band1_max &&
		   fपूर्णांक < ti_clk_get_features()->fपूर्णांक_band2_min) अणु
		pr_debug("rejecting n=%d due to Fint failure\n", n);
		ret = DPLL_FINT_INVALID;
	पूर्ण

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ _dpll_compute_new_rate(अचिन्हित दीर्घ parent_rate,
					    अचिन्हित पूर्णांक m, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ दीर्घ num;

	num = (अचिन्हित दीर्घ दीर्घ)parent_rate * m;
	करो_भाग(num, n);
	वापस num;
पूर्ण

/*
 * _dpll_test_mult - test a DPLL multiplier value
 * @m: poपूर्णांकer to the DPLL m (multiplier) value under test
 * @n: current DPLL n (भागider) value under test
 * @new_rate: poपूर्णांकer to storage क्रम the resulting rounded rate
 * @target_rate: the desired DPLL rate
 * @parent_rate: the DPLL's parent घड़ी rate
 *
 * This code tests a DPLL multiplier value, ensuring that the
 * resulting rate will not be higher than the target_rate, and that
 * the multiplier value itself is valid क्रम the DPLL.  Initially, the
 * पूर्णांकeger poपूर्णांकed to by the m argument should be prescaled by
 * multiplying by DPLL_SCALE_FACTOR.  The code will replace this with
 * a non-scaled m upon वापस.  This non-scaled m will result in a
 * new_rate as बंद as possible to target_rate (but not greater than
 * target_rate) given the current (parent_rate, n, prescaled m)
 * triple. Returns DPLL_MULT_UNDERFLOW in the event that the
 * non-scaled m attempted to underflow, which can allow the calling
 * function to bail out early; or 0 upon success.
 */
अटल पूर्णांक _dpll_test_mult(पूर्णांक *m, पूर्णांक n, अचिन्हित दीर्घ *new_rate,
			   अचिन्हित दीर्घ target_rate,
			   अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक r = 0, carry = 0;

	/* Unscale m and round अगर necessary */
	अगर (*m % DPLL_SCALE_FACTOR >= DPLL_ROUNDING_VAL)
		carry = 1;
	*m = (*m / DPLL_SCALE_FACTOR) + carry;

	/*
	 * The new rate must be <= the target rate to aव्योम programming
	 * a rate that is impossible क्रम the hardware to handle
	 */
	*new_rate = _dpll_compute_new_rate(parent_rate, *m, n);
	अगर (*new_rate > target_rate) अणु
		(*m)--;
		*new_rate = 0;
	पूर्ण

	/* Guard against m underflow */
	अगर (*m < DPLL_MIN_MULTIPLIER) अणु
		*m = DPLL_MIN_MULTIPLIER;
		*new_rate = 0;
		r = DPLL_MULT_UNDERFLOW;
	पूर्ण

	अगर (*new_rate == 0)
		*new_rate = _dpll_compute_new_rate(parent_rate, *m, n);

	वापस r;
पूर्ण

/**
 * _omap2_dpll_is_in_bypass - check अगर DPLL is in bypass mode or not
 * @v: bitfield value of the DPLL enable
 *
 * Checks given DPLL enable bitfield to see whether the DPLL is in bypass
 * mode or not. Returns 1 अगर the DPLL is in bypass, 0 otherwise.
 */
अटल पूर्णांक _omap2_dpll_is_in_bypass(u32 v)
अणु
	u8 mask, val;

	mask = ti_clk_get_features()->dpll_bypass_vals;

	/*
	 * Each set bit in the mask corresponds to a bypass value equal
	 * to the bitshअगरt. Go through each set-bit in the mask and
	 * compare against the given रेजिस्टर value.
	 */
	जबतक (mask) अणु
		val = __ffs(mask);
		mask ^= (1 << val);
		अगर (v == val)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* Public functions */
u8 omap2_init_dpll_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	u32 v;
	काष्ठा dpll_data *dd;

	dd = clk->dpll_data;
	अगर (!dd)
		वापस -EINVAL;

	v = ti_clk_ll_ops->clk_पढ़ोl(&dd->control_reg);
	v &= dd->enable_mask;
	v >>= __ffs(dd->enable_mask);

	/* Reparent the काष्ठा clk in हाल the dpll is in bypass */
	अगर (_omap2_dpll_is_in_bypass(v))
		वापस 1;

	वापस 0;
पूर्ण

/**
 * omap2_get_dpll_rate - वापसs the current DPLL CLKOUT rate
 * @clk: काष्ठा clk * of a DPLL
 *
 * DPLLs can be locked or bypassed - basically, enabled or disabled.
 * When locked, the DPLL output depends on the M and N values.  When
 * bypassed, on OMAP2xxx, the output rate is either the 32KiHz घड़ी
 * or sys_clk.  Bypass rates on OMAP3 depend on the DPLL: DPLLs 1 and
 * 2 are bypassed with dpll1_fclk and dpll2_fclk respectively
 * (generated by DPLL3), जबतक DPLL 3, 4, and 5 bypass rates are sys_clk.
 * Returns the current DPLL CLKOUT rate (*not* CLKOUTX2) अगर the DPLL is
 * locked, or the appropriate bypass rate अगर the DPLL is bypassed, or 0
 * अगर the घड़ी @clk is not a DPLL.
 */
अचिन्हित दीर्घ omap2_get_dpll_rate(काष्ठा clk_hw_omap *clk)
अणु
	u64 dpll_clk;
	u32 dpll_mult, dpll_भाग, v;
	काष्ठा dpll_data *dd;

	dd = clk->dpll_data;
	अगर (!dd)
		वापस 0;

	/* Return bypass rate अगर DPLL is bypassed */
	v = ti_clk_ll_ops->clk_पढ़ोl(&dd->control_reg);
	v &= dd->enable_mask;
	v >>= __ffs(dd->enable_mask);

	अगर (_omap2_dpll_is_in_bypass(v))
		वापस clk_hw_get_rate(dd->clk_bypass);

	v = ti_clk_ll_ops->clk_पढ़ोl(&dd->mult_भाग1_reg);
	dpll_mult = v & dd->mult_mask;
	dpll_mult >>= __ffs(dd->mult_mask);
	dpll_भाग = v & dd->भाग1_mask;
	dpll_भाग >>= __ffs(dd->भाग1_mask);

	dpll_clk = (u64)clk_hw_get_rate(dd->clk_ref) * dpll_mult;
	करो_भाग(dpll_clk, dpll_भाग + 1);

	वापस dpll_clk;
पूर्ण

/* DPLL rate rounding code */

/**
 * omap2_dpll_round_rate - round a target rate क्रम an OMAP DPLL
 * @hw: काष्ठा clk_hw containing the काष्ठा clk * क्रम a DPLL
 * @target_rate: desired DPLL घड़ी rate
 * @parent_rate: parent's DPLL घड़ी rate
 *
 * Given a DPLL and a desired target rate, round the target rate to a
 * possible, programmable rate क्रम this DPLL.  Attempts to select the
 * minimum possible n.  Stores the computed (m, n) in the DPLL's
 * dpll_data काष्ठाure so set_rate() will not need to call this
 * (expensive) function again.  Returns ~0 अगर the target rate cannot
 * be rounded, or the rounded rate upon success.
 */
दीर्घ omap2_dpll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ target_rate,
			   अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	पूर्णांक m, n, r, scaled_max_m;
	पूर्णांक min_delta_m = पूर्णांक_उच्च, min_delta_n = पूर्णांक_उच्च;
	अचिन्हित दीर्घ scaled_rt_rp;
	अचिन्हित दीर्घ new_rate = 0;
	काष्ठा dpll_data *dd;
	अचिन्हित दीर्घ ref_rate;
	दीर्घ delta;
	दीर्घ prev_min_delta = दीर्घ_उच्च;
	स्थिर अक्षर *clk_name;

	अगर (!clk || !clk->dpll_data)
		वापस ~0;

	dd = clk->dpll_data;

	अगर (dd->max_rate && target_rate > dd->max_rate)
		target_rate = dd->max_rate;

	ref_rate = clk_hw_get_rate(dd->clk_ref);
	clk_name = clk_hw_get_name(hw);
	pr_debug("clock: %s: starting DPLL round_rate, target rate %lu\n",
		 clk_name, target_rate);

	scaled_rt_rp = target_rate / (ref_rate / DPLL_SCALE_FACTOR);
	scaled_max_m = dd->max_multiplier * DPLL_SCALE_FACTOR;

	dd->last_rounded_rate = 0;

	क्रम (n = dd->min_भागider; n <= dd->max_भागider; n++) अणु
		/* Is the (input clk, भागider) pair valid क्रम the DPLL? */
		r = _dpll_test_fपूर्णांक(clk, n);
		अगर (r == DPLL_FINT_UNDERFLOW)
			अवरोध;
		अन्यथा अगर (r == DPLL_FINT_INVALID)
			जारी;

		/* Compute the scaled DPLL multiplier, based on the भागider */
		m = scaled_rt_rp * n;

		/*
		 * Since we're counting n up, a m overflow means we
		 * can bail out completely (since as n increases in
		 * the next iteration, there's no way that m can
		 * increase beyond the current m)
		 */
		अगर (m > scaled_max_m)
			अवरोध;

		r = _dpll_test_mult(&m, n, &new_rate, target_rate,
				    ref_rate);

		/* m can't be set low enough क्रम this n - try with a larger n */
		अगर (r == DPLL_MULT_UNDERFLOW)
			जारी;

		/* skip rates above our target rate */
		delta = target_rate - new_rate;
		अगर (delta < 0)
			जारी;

		अगर (delta < prev_min_delta) अणु
			prev_min_delta = delta;
			min_delta_m = m;
			min_delta_n = n;
		पूर्ण

		pr_debug("clock: %s: m = %d: n = %d: new_rate = %lu\n",
			 clk_name, m, n, new_rate);

		अगर (delta == 0)
			अवरोध;
	पूर्ण

	अगर (prev_min_delta == दीर्घ_उच्च) अणु
		pr_debug("clock: %s: cannot round to rate %lu\n",
			 clk_name, target_rate);
		वापस ~0;
	पूर्ण

	dd->last_rounded_m = min_delta_m;
	dd->last_rounded_n = min_delta_n;
	dd->last_rounded_rate = target_rate - prev_min_delta;

	वापस dd->last_rounded_rate;
पूर्ण
