<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP3/4 - specअगरic DPLL control functions
 *
 * Copyright (C) 2009-2010 Texas Instruments, Inc.
 * Copyright (C) 2009-2010 Nokia Corporation
 *
 * Written by Paul Walmsley
 * Testing and पूर्णांकegration fixes by Jouni Hथघgander
 *
 * 36xx support added by Vishwanath BS, Riअक्षरd Woodruff, and Nishanth
 * Menon
 *
 * Parts of this code are based on code written by
 * Riअक्षरd Woodruff, Tony Lindgren, Tuukka Tikkanen, Karthik Dasu
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk/ti.h>

#समावेश "clock.h"

/* CM_AUTOIDLE_PLL*.AUTO_* bit values */
#घोषणा DPLL_AUTOIDLE_DISABLE			0x0
#घोषणा DPLL_AUTOIDLE_LOW_POWER_STOP		0x1

#घोषणा MAX_DPLL_WAIT_TRIES		1000000

#घोषणा OMAP3XXX_EN_DPLL_LOCKED		0x7

/* Forward declarations */
अटल u32 omap3_dpll_स्वतःidle_पढ़ो(काष्ठा clk_hw_omap *clk);
अटल व्योम omap3_dpll_deny_idle(काष्ठा clk_hw_omap *clk);
अटल व्योम omap3_dpll_allow_idle(काष्ठा clk_hw_omap *clk);

/* Private functions */

/* _omap3_dpll_ग_लिखो_clken - ग_लिखो clken_bits arg to a DPLL's enable bits */
अटल व्योम _omap3_dpll_ग_लिखो_clken(काष्ठा clk_hw_omap *clk, u8 clken_bits)
अणु
	स्थिर काष्ठा dpll_data *dd;
	u32 v;

	dd = clk->dpll_data;

	v = ti_clk_ll_ops->clk_पढ़ोl(&dd->control_reg);
	v &= ~dd->enable_mask;
	v |= clken_bits << __ffs(dd->enable_mask);
	ti_clk_ll_ops->clk_ग_लिखोl(v, &dd->control_reg);
पूर्ण

/* _omap3_रुको_dpll_status: रुको क्रम a DPLL to enter a specअगरic state */
अटल पूर्णांक _omap3_रुको_dpll_status(काष्ठा clk_hw_omap *clk, u8 state)
अणु
	स्थिर काष्ठा dpll_data *dd;
	पूर्णांक i = 0;
	पूर्णांक ret = -EINVAL;
	स्थिर अक्षर *clk_name;

	dd = clk->dpll_data;
	clk_name = clk_hw_get_name(&clk->hw);

	state <<= __ffs(dd->idlest_mask);

	जबतक (((ti_clk_ll_ops->clk_पढ़ोl(&dd->idlest_reg) & dd->idlest_mask)
		!= state) && i < MAX_DPLL_WAIT_TRIES) अणु
		i++;
		udelay(1);
	पूर्ण

	अगर (i == MAX_DPLL_WAIT_TRIES) अणु
		pr_err("clock: %s failed transition to '%s'\n",
		       clk_name, (state) ? "locked" : "bypassed");
	पूर्ण अन्यथा अणु
		pr_debug("clock: %s transition to '%s' in %d loops\n",
			 clk_name, (state) ? "locked" : "bypassed", i);

		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/* From 3430 TRM ES2 4.7.6.2 */
अटल u16 _omap3_dpll_compute_freqsel(काष्ठा clk_hw_omap *clk, u8 n)
अणु
	अचिन्हित दीर्घ fपूर्णांक;
	u16 f = 0;

	fपूर्णांक = clk_hw_get_rate(clk->dpll_data->clk_ref) / n;

	pr_debug("clock: fint is %lu\n", fपूर्णांक);

	अगर (fपूर्णांक >= 750000 && fपूर्णांक <= 1000000)
		f = 0x3;
	अन्यथा अगर (fपूर्णांक > 1000000 && fपूर्णांक <= 1250000)
		f = 0x4;
	अन्यथा अगर (fपूर्णांक > 1250000 && fपूर्णांक <= 1500000)
		f = 0x5;
	अन्यथा अगर (fपूर्णांक > 1500000 && fपूर्णांक <= 1750000)
		f = 0x6;
	अन्यथा अगर (fपूर्णांक > 1750000 && fपूर्णांक <= 2100000)
		f = 0x7;
	अन्यथा अगर (fपूर्णांक > 7500000 && fपूर्णांक <= 10000000)
		f = 0xB;
	अन्यथा अगर (fपूर्णांक > 10000000 && fपूर्णांक <= 12500000)
		f = 0xC;
	अन्यथा अगर (fपूर्णांक > 12500000 && fपूर्णांक <= 15000000)
		f = 0xD;
	अन्यथा अगर (fपूर्णांक > 15000000 && fपूर्णांक <= 17500000)
		f = 0xE;
	अन्यथा अगर (fपूर्णांक > 17500000 && fपूर्णांक <= 21000000)
		f = 0xF;
	अन्यथा
		pr_debug("clock: unknown freqsel setting for %d\n", n);

	वापस f;
पूर्ण

/**
 * _omap3_noncore_dpll_lock - inकाष्ठा a DPLL to lock and रुको क्रम पढ़ोiness
 * @clk: poपूर्णांकer to a DPLL काष्ठा clk
 *
 * Inकाष्ठाs a non-CORE DPLL to lock.  Waits क्रम the DPLL to report
 * पढ़ोiness beक्रमe वापसing.  Will save and restore the DPLL's
 * स्वतःidle state across the enable, per the CDP code.  If the DPLL
 * locked successfully, वापस 0; अगर the DPLL did not lock in the समय
 * allotted, or DPLL3 was passed in, वापस -EINVAL.
 */
अटल पूर्णांक _omap3_noncore_dpll_lock(काष्ठा clk_hw_omap *clk)
अणु
	स्थिर काष्ठा dpll_data *dd;
	u8 ai;
	u8 state = 1;
	पूर्णांक r = 0;

	pr_debug("clock: locking DPLL %s\n", clk_hw_get_name(&clk->hw));

	dd = clk->dpll_data;
	state <<= __ffs(dd->idlest_mask);

	/* Check अगर alपढ़ोy locked */
	अगर ((ti_clk_ll_ops->clk_पढ़ोl(&dd->idlest_reg) & dd->idlest_mask) ==
	    state)
		जाओ करोne;

	ai = omap3_dpll_स्वतःidle_पढ़ो(clk);

	अगर (ai)
		omap3_dpll_deny_idle(clk);

	_omap3_dpll_ग_लिखो_clken(clk, DPLL_LOCKED);

	r = _omap3_रुको_dpll_status(clk, 1);

	अगर (ai)
		omap3_dpll_allow_idle(clk);

करोne:
	वापस r;
पूर्ण

/**
 * _omap3_noncore_dpll_bypass - inकाष्ठा a DPLL to bypass and रुको क्रम पढ़ोiness
 * @clk: poपूर्णांकer to a DPLL काष्ठा clk
 *
 * Inकाष्ठाs a non-CORE DPLL to enter low-घातer bypass mode.  In
 * bypass mode, the DPLL's rate is set equal to its parent clock's
 * rate.  Waits क्रम the DPLL to report पढ़ोiness beक्रमe वापसing.
 * Will save and restore the DPLL's स्वतःidle state across the enable,
 * per the CDP code.  If the DPLL entered bypass mode successfully,
 * वापस 0; अगर the DPLL did not enter bypass in the समय allotted, or
 * DPLL3 was passed in, or the DPLL करोes not support low-घातer bypass,
 * वापस -EINVAL.
 */
अटल पूर्णांक _omap3_noncore_dpll_bypass(काष्ठा clk_hw_omap *clk)
अणु
	पूर्णांक r;
	u8 ai;

	अगर (!(clk->dpll_data->modes & (1 << DPLL_LOW_POWER_BYPASS)))
		वापस -EINVAL;

	pr_debug("clock: configuring DPLL %s for low-power bypass\n",
		 clk_hw_get_name(&clk->hw));

	ai = omap3_dpll_स्वतःidle_पढ़ो(clk);

	_omap3_dpll_ग_लिखो_clken(clk, DPLL_LOW_POWER_BYPASS);

	r = _omap3_रुको_dpll_status(clk, 0);

	अगर (ai)
		omap3_dpll_allow_idle(clk);

	वापस r;
पूर्ण

/**
 * _omap3_noncore_dpll_stop - inकाष्ठा a DPLL to stop
 * @clk: poपूर्णांकer to a DPLL काष्ठा clk
 *
 * Inकाष्ठाs a non-CORE DPLL to enter low-घातer stop. Will save and
 * restore the DPLL's स्वतःidle state across the stop, per the CDP
 * code.  If DPLL3 was passed in, or the DPLL करोes not support
 * low-घातer stop, वापस -EINVAL; otherwise, वापस 0.
 */
अटल पूर्णांक _omap3_noncore_dpll_stop(काष्ठा clk_hw_omap *clk)
अणु
	u8 ai;

	अगर (!(clk->dpll_data->modes & (1 << DPLL_LOW_POWER_STOP)))
		वापस -EINVAL;

	pr_debug("clock: stopping DPLL %s\n", clk_hw_get_name(&clk->hw));

	ai = omap3_dpll_स्वतःidle_पढ़ो(clk);

	_omap3_dpll_ग_लिखो_clken(clk, DPLL_LOW_POWER_STOP);

	अगर (ai)
		omap3_dpll_allow_idle(clk);

	वापस 0;
पूर्ण

/**
 * _lookup_dco - Lookup DCO used by j-type DPLL
 * @clk: poपूर्णांकer to a DPLL काष्ठा clk
 * @dco: digital control oscillator selector
 * @m: DPLL multiplier to set
 * @n: DPLL भागider to set
 *
 * See 36xx TRM section 3.5.3.3.3.2 "Type B DPLL (Low-Jitter)"
 *
 * XXX This code is not needed क्रम 3430/AM35xx; can it be optimized
 * out in non-multi-OMAP builds क्रम those chips?
 */
अटल व्योम _lookup_dco(काष्ठा clk_hw_omap *clk, u8 *dco, u16 m, u8 n)
अणु
	अचिन्हित दीर्घ fपूर्णांक, clkinp; /* watch out क्रम overflow */

	clkinp = clk_hw_get_rate(clk_hw_get_parent(&clk->hw));
	fपूर्णांक = (clkinp / n) * m;

	अगर (fपूर्णांक < 1000000000)
		*dco = 2;
	अन्यथा
		*dco = 4;
पूर्ण

/**
 * _lookup_sdभाग - Calculate sigma delta भागider क्रम j-type DPLL
 * @clk: poपूर्णांकer to a DPLL काष्ठा clk
 * @sd_भाग: target sigma-delta भागider
 * @m: DPLL multiplier to set
 * @n: DPLL भागider to set
 *
 * See 36xx TRM section 3.5.3.3.3.2 "Type B DPLL (Low-Jitter)"
 *
 * XXX This code is not needed क्रम 3430/AM35xx; can it be optimized
 * out in non-multi-OMAP builds क्रम those chips?
 */
अटल व्योम _lookup_sdभाग(काष्ठा clk_hw_omap *clk, u8 *sd_भाग, u16 m, u8 n)
अणु
	अचिन्हित दीर्घ clkinp, sd; /* watch out क्रम overflow */
	पूर्णांक mod1, mod2;

	clkinp = clk_hw_get_rate(clk_hw_get_parent(&clk->hw));

	/*
	 * target sigma-delta to near 250MHz
	 * sd = उच्चमान[(m/(n+1)) * (clkinp_MHz / 250)]
	 */
	clkinp /= 100000; /* shअगरt from MHz to 10*Hz क्रम 38.4 and 19.2 */
	mod1 = (clkinp * m) % (250 * n);
	sd = (clkinp * m) / (250 * n);
	mod2 = sd % 10;
	sd /= 10;

	अगर (mod1 || mod2)
		sd++;
	*sd_भाग = sd;
पूर्ण

/**
 * _omap3_noncore_dpll_program - set non-core DPLL M,N values directly
 * @clk:	काष्ठा clk * of DPLL to set
 * @freqsel:	FREQSEL value to set
 *
 * Program the DPLL with the last M, N values calculated, and रुको क्रम
 * the DPLL to lock. Returns -EINVAL upon error, or 0 upon success.
 */
अटल पूर्णांक omap3_noncore_dpll_program(काष्ठा clk_hw_omap *clk, u16 freqsel)
अणु
	काष्ठा dpll_data *dd = clk->dpll_data;
	u8 dco, sd_भाग, ai = 0;
	u32 v;
	bool errata_i810;

	/* 3430 ES2 TRM: 4.7.6.9 DPLL Programming Sequence */
	_omap3_noncore_dpll_bypass(clk);

	/*
	 * Set jitter correction. Jitter correction applicable क्रम OMAP343X
	 * only since freqsel field is no दीर्घer present on other devices.
	 */
	अगर (ti_clk_get_features()->flags & TI_CLK_DPLL_HAS_FREQSEL) अणु
		v = ti_clk_ll_ops->clk_पढ़ोl(&dd->control_reg);
		v &= ~dd->freqsel_mask;
		v |= freqsel << __ffs(dd->freqsel_mask);
		ti_clk_ll_ops->clk_ग_लिखोl(v, &dd->control_reg);
	पूर्ण

	/* Set DPLL multiplier, भागider */
	v = ti_clk_ll_ops->clk_पढ़ोl(&dd->mult_भाग1_reg);

	/* Handle Duty Cycle Correction */
	अगर (dd->dcc_mask) अणु
		अगर (dd->last_rounded_rate >= dd->dcc_rate)
			v |= dd->dcc_mask; /* Enable DCC */
		अन्यथा
			v &= ~dd->dcc_mask; /* Disable DCC */
	पूर्ण

	v &= ~(dd->mult_mask | dd->भाग1_mask);
	v |= dd->last_rounded_m << __ffs(dd->mult_mask);
	v |= (dd->last_rounded_n - 1) << __ffs(dd->भाग1_mask);

	/* Configure dco and sd_भाग क्रम dplls that have these fields */
	अगर (dd->dco_mask) अणु
		_lookup_dco(clk, &dco, dd->last_rounded_m, dd->last_rounded_n);
		v &= ~(dd->dco_mask);
		v |= dco << __ffs(dd->dco_mask);
	पूर्ण
	अगर (dd->sdभाग_mask) अणु
		_lookup_sdभाग(clk, &sd_भाग, dd->last_rounded_m,
			      dd->last_rounded_n);
		v &= ~(dd->sdभाग_mask);
		v |= sd_भाग << __ffs(dd->sdभाग_mask);
	पूर्ण

	/*
	 * Errata i810 - DPLL controller can get stuck जबतक transitioning
	 * to a घातer saving state. Software must ensure the DPLL can not
	 * transition to a low घातer state जबतक changing M/N values.
	 * Easiest way to accomplish this is to prevent DPLL स्वतःidle
	 * beक्रमe करोing the M/N re-program.
	 */
	errata_i810 = ti_clk_get_features()->flags & TI_CLK_ERRATA_I810;

	अगर (errata_i810) अणु
		ai = omap3_dpll_स्वतःidle_पढ़ो(clk);
		अगर (ai) अणु
			omap3_dpll_deny_idle(clk);

			/* OCP barrier */
			omap3_dpll_स्वतःidle_पढ़ो(clk);
		पूर्ण
	पूर्ण

	ti_clk_ll_ops->clk_ग_लिखोl(v, &dd->mult_भाग1_reg);

	/* Set 4X multiplier and low-घातer mode */
	अगर (dd->m4xen_mask || dd->lpmode_mask) अणु
		v = ti_clk_ll_ops->clk_पढ़ोl(&dd->control_reg);

		अगर (dd->m4xen_mask) अणु
			अगर (dd->last_rounded_m4xen)
				v |= dd->m4xen_mask;
			अन्यथा
				v &= ~dd->m4xen_mask;
		पूर्ण

		अगर (dd->lpmode_mask) अणु
			अगर (dd->last_rounded_lpmode)
				v |= dd->lpmode_mask;
			अन्यथा
				v &= ~dd->lpmode_mask;
		पूर्ण

		ti_clk_ll_ops->clk_ग_लिखोl(v, &dd->control_reg);
	पूर्ण

	/* We let the घड़ी framework set the other output भागiders later */

	/* REVISIT: Set ramp-up delay? */

	_omap3_noncore_dpll_lock(clk);

	अगर (errata_i810 && ai)
		omap3_dpll_allow_idle(clk);

	वापस 0;
पूर्ण

/* Public functions */

/**
 * omap3_dpll_recalc - recalculate DPLL rate
 * @hw: काष्ठा clk_hw containing the DPLL काष्ठा clk
 * @parent_rate: घड़ी rate of the DPLL parent
 *
 * Recalculate and propagate the DPLL rate.
 */
अचिन्हित दीर्घ omap3_dpll_recalc(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);

	वापस omap2_get_dpll_rate(clk);
पूर्ण

/* Non-CORE DPLL (e.g., DPLLs that करो not control SDRC) घड़ी functions */

/**
 * omap3_noncore_dpll_enable - inकाष्ठा a DPLL to enter bypass or lock mode
 * @hw: काष्ठा clk_hw containing then poपूर्णांकer to a DPLL काष्ठा clk
 *
 * Inकाष्ठाs a non-CORE DPLL to enable, e.g., to enter bypass or lock.
 * The choice of modes depends on the DPLL's programmed rate: अगर it is
 * the same as the DPLL's parent घड़ी, it will enter bypass;
 * otherwise, it will enter lock.  This code will रुको क्रम the DPLL to
 * indicate पढ़ोiness beक्रमe वापसing, unless the DPLL takes too दीर्घ
 * to enter the target state.  Intended to be used as the काष्ठा clk's
 * enable function.  If DPLL3 was passed in, or the DPLL करोes not
 * support low-घातer stop, or अगर the DPLL took too दीर्घ to enter
 * bypass or lock, वापस -EINVAL; otherwise, वापस 0.
 */
पूर्णांक omap3_noncore_dpll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	पूर्णांक r;
	काष्ठा dpll_data *dd;
	काष्ठा clk_hw *parent;

	dd = clk->dpll_data;
	अगर (!dd)
		वापस -EINVAL;

	अगर (clk->clkdm) अणु
		r = ti_clk_ll_ops->clkdm_clk_enable(clk->clkdm, hw->clk);
		अगर (r) अणु
			WARN(1,
			     "%s: could not enable %s's clockdomain %s: %d\n",
			     __func__, clk_hw_get_name(hw),
			     clk->clkdm_name, r);
			वापस r;
		पूर्ण
	पूर्ण

	parent = clk_hw_get_parent(hw);

	अगर (clk_hw_get_rate(hw) == clk_hw_get_rate(dd->clk_bypass)) अणु
		WARN_ON(parent != dd->clk_bypass);
		r = _omap3_noncore_dpll_bypass(clk);
	पूर्ण अन्यथा अणु
		WARN_ON(parent != dd->clk_ref);
		r = _omap3_noncore_dpll_lock(clk);
	पूर्ण

	वापस r;
पूर्ण

/**
 * omap3_noncore_dpll_disable - inकाष्ठा a DPLL to enter low-घातer stop
 * @hw: काष्ठा clk_hw containing then poपूर्णांकer to a DPLL काष्ठा clk
 *
 * Inकाष्ठाs a non-CORE DPLL to enter low-घातer stop.  This function is
 * पूर्णांकended क्रम use in काष्ठा clkops.  No वापस value.
 */
व्योम omap3_noncore_dpll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);

	_omap3_noncore_dpll_stop(clk);
	अगर (clk->clkdm)
		ti_clk_ll_ops->clkdm_clk_disable(clk->clkdm, hw->clk);
पूर्ण

/* Non-CORE DPLL rate set code */

/**
 * omap3_noncore_dpll_determine_rate - determine rate क्रम a DPLL
 * @hw: poपूर्णांकer to the घड़ी to determine rate क्रम
 * @req: target rate request
 *
 * Determines which DPLL mode to use क्रम reaching a desired target rate.
 * Checks whether the DPLL shall be in bypass or locked mode, and अगर
 * locked, calculates the M,N values क्रम the DPLL via round-rate.
 * Returns a 0 on success, negative error value in failure.
 */
पूर्णांक omap3_noncore_dpll_determine_rate(काष्ठा clk_hw *hw,
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
		req->rate = omap2_dpll_round_rate(hw, req->rate,
					  &req->best_parent_rate);
		req->best_parent_hw = dd->clk_ref;
	पूर्ण

	req->best_parent_rate = req->rate;

	वापस 0;
पूर्ण

/**
 * omap3_noncore_dpll_set_parent - set parent क्रम a DPLL घड़ी
 * @hw: poपूर्णांकer to the घड़ी to set parent क्रम
 * @index: parent index to select
 *
 * Sets parent क्रम a DPLL घड़ी. This sets the DPLL पूर्णांकo bypass or
 * locked mode. Returns 0 with success, negative error value otherwise.
 */
पूर्णांक omap3_noncore_dpll_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	पूर्णांक ret;

	अगर (!hw)
		वापस -EINVAL;

	अगर (index)
		ret = _omap3_noncore_dpll_bypass(clk);
	अन्यथा
		ret = _omap3_noncore_dpll_lock(clk);

	वापस ret;
पूर्ण

/**
 * omap3_noncore_dpll_set_rate - set rate क्रम a DPLL घड़ी
 * @hw: poपूर्णांकer to the घड़ी to set parent क्रम
 * @rate: target rate क्रम the घड़ी
 * @parent_rate: rate of the parent घड़ी
 *
 * Sets rate क्रम a DPLL घड़ी. First checks अगर the घड़ी parent is
 * reference घड़ी (in bypass mode, the rate of the घड़ी can't be
 * changed) and proceeds with the rate change operation. Returns 0
 * with success, negative error value otherwise.
 */
पूर्णांक omap3_noncore_dpll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	काष्ठा dpll_data *dd;
	u16 freqsel = 0;
	पूर्णांक ret;

	अगर (!hw || !rate)
		वापस -EINVAL;

	dd = clk->dpll_data;
	अगर (!dd)
		वापस -EINVAL;

	अगर (clk_hw_get_parent(hw) != dd->clk_ref)
		वापस -EINVAL;

	अगर (dd->last_rounded_rate == 0)
		वापस -EINVAL;

	/* Freqsel is available only on OMAP343X devices */
	अगर (ti_clk_get_features()->flags & TI_CLK_DPLL_HAS_FREQSEL) अणु
		freqsel = _omap3_dpll_compute_freqsel(clk, dd->last_rounded_n);
		WARN_ON(!freqsel);
	पूर्ण

	pr_debug("%s: %s: set rate: locking rate to %lu.\n", __func__,
		 clk_hw_get_name(hw), rate);

	ret = omap3_noncore_dpll_program(clk, freqsel);

	वापस ret;
पूर्ण

/**
 * omap3_noncore_dpll_set_rate_and_parent - set rate and parent क्रम a DPLL घड़ी
 * @hw: poपूर्णांकer to the घड़ी to set rate and parent क्रम
 * @rate: target rate क्रम the DPLL
 * @parent_rate: घड़ी rate of the DPLL parent
 * @index: new parent index क्रम the DPLL, 0 - reference, 1 - bypass
 *
 * Sets rate and parent क्रम a DPLL घड़ी. If new parent is the bypass
 * घड़ी, only selects the parent. Otherwise proceeds with a rate
 * change, as this will effectively also change the parent as the
 * DPLL is put पूर्णांकo locked mode. Returns 0 with success, negative error
 * value otherwise.
 */
पूर्णांक omap3_noncore_dpll_set_rate_and_parent(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ rate,
					   अचिन्हित दीर्घ parent_rate,
					   u8 index)
अणु
	पूर्णांक ret;

	अगर (!hw || !rate)
		वापस -EINVAL;

	/*
	 * clk-ref at index[0], in which हाल we only need to set rate,
	 * the parent will be changed स्वतःmatically with the lock sequence.
	 * With clk-bypass हाल we only need to change parent.
	 */
	अगर (index)
		ret = omap3_noncore_dpll_set_parent(hw, index);
	अन्यथा
		ret = omap3_noncore_dpll_set_rate(hw, rate, parent_rate);

	वापस ret;
पूर्ण

/* DPLL स्वतःidle पढ़ो/set code */

/**
 * omap3_dpll_स्वतःidle_पढ़ो - पढ़ो a DPLL's स्वतःidle bits
 * @clk: काष्ठा clk * of the DPLL to पढ़ो
 *
 * Return the DPLL's स्वतःidle bits, shअगरted करोwn to bit 0.  Returns
 * -EINVAL अगर passed a null poपूर्णांकer or अगर the काष्ठा clk करोes not
 * appear to refer to a DPLL.
 */
अटल u32 omap3_dpll_स्वतःidle_पढ़ो(काष्ठा clk_hw_omap *clk)
अणु
	स्थिर काष्ठा dpll_data *dd;
	u32 v;

	अगर (!clk || !clk->dpll_data)
		वापस -EINVAL;

	dd = clk->dpll_data;

	अगर (!dd->स्वतःidle_mask)
		वापस -EINVAL;

	v = ti_clk_ll_ops->clk_पढ़ोl(&dd->स्वतःidle_reg);
	v &= dd->स्वतःidle_mask;
	v >>= __ffs(dd->स्वतःidle_mask);

	वापस v;
पूर्ण

/**
 * omap3_dpll_allow_idle - enable DPLL स्वतःidle bits
 * @clk: काष्ठा clk * of the DPLL to operate on
 *
 * Enable DPLL स्वतःmatic idle control.  This स्वतःmatic idle mode
 * चयनing takes effect only when the DPLL is locked, at least on
 * OMAP3430.  The DPLL will enter low-घातer stop when its करोwnstream
 * घड़ीs are gated.  No वापस value.
 */
अटल व्योम omap3_dpll_allow_idle(काष्ठा clk_hw_omap *clk)
अणु
	स्थिर काष्ठा dpll_data *dd;
	u32 v;

	अगर (!clk || !clk->dpll_data)
		वापस;

	dd = clk->dpll_data;

	अगर (!dd->स्वतःidle_mask)
		वापस;

	/*
	 * REVISIT: CORE DPLL can optionally enter low-घातer bypass
	 * by writing 0x5 instead of 0x1.  Add some mechanism to
	 * optionally enter this mode.
	 */
	v = ti_clk_ll_ops->clk_पढ़ोl(&dd->स्वतःidle_reg);
	v &= ~dd->स्वतःidle_mask;
	v |= DPLL_AUTOIDLE_LOW_POWER_STOP << __ffs(dd->स्वतःidle_mask);
	ti_clk_ll_ops->clk_ग_लिखोl(v, &dd->स्वतःidle_reg);
पूर्ण

/**
 * omap3_dpll_deny_idle - prevent DPLL from स्वतःmatically idling
 * @clk: काष्ठा clk * of the DPLL to operate on
 *
 * Disable DPLL स्वतःmatic idle control.  No वापस value.
 */
अटल व्योम omap3_dpll_deny_idle(काष्ठा clk_hw_omap *clk)
अणु
	स्थिर काष्ठा dpll_data *dd;
	u32 v;

	अगर (!clk || !clk->dpll_data)
		वापस;

	dd = clk->dpll_data;

	अगर (!dd->स्वतःidle_mask)
		वापस;

	v = ti_clk_ll_ops->clk_पढ़ोl(&dd->स्वतःidle_reg);
	v &= ~dd->स्वतःidle_mask;
	v |= DPLL_AUTOIDLE_DISABLE << __ffs(dd->स्वतःidle_mask);
	ti_clk_ll_ops->clk_ग_लिखोl(v, &dd->स्वतःidle_reg);
पूर्ण

/* Clock control क्रम DPLL outमाला_दो */

/* Find the parent DPLL क्रम the given clkoutx2 घड़ी */
अटल काष्ठा clk_hw_omap *omap3_find_clkoutx2_dpll(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *pclk = शून्य;

	/* Walk up the parents of clk, looking क्रम a DPLL */
	करो अणु
		करो अणु
			hw = clk_hw_get_parent(hw);
		पूर्ण जबतक (hw && (!omap2_clk_is_hw_omap(hw)));
		अगर (!hw)
			अवरोध;
		pclk = to_clk_hw_omap(hw);
	पूर्ण जबतक (pclk && !pclk->dpll_data);

	/* clk करोes not have a DPLL as a parent?  error in the घड़ी data */
	अगर (!pclk) अणु
		WARN_ON(1);
		वापस शून्य;
	पूर्ण

	वापस pclk;
पूर्ण

/**
 * omap3_clkoutx2_recalc - recalculate DPLL X2 output भव घड़ी rate
 * @hw: poपूर्णांकer  काष्ठा clk_hw
 * @parent_rate: घड़ी rate of the DPLL parent
 *
 * Using parent घड़ी DPLL data, look up DPLL state.  If locked, set our
 * rate to the dpll_clk * 2; otherwise, just use dpll_clk.
 */
अचिन्हित दीर्घ omap3_clkoutx2_recalc(काष्ठा clk_hw *hw,
				    अचिन्हित दीर्घ parent_rate)
अणु
	स्थिर काष्ठा dpll_data *dd;
	अचिन्हित दीर्घ rate;
	u32 v;
	काष्ठा clk_hw_omap *pclk = शून्य;

	अगर (!parent_rate)
		वापस 0;

	pclk = omap3_find_clkoutx2_dpll(hw);

	अगर (!pclk)
		वापस 0;

	dd = pclk->dpll_data;

	WARN_ON(!dd->enable_mask);

	v = ti_clk_ll_ops->clk_पढ़ोl(&dd->control_reg) & dd->enable_mask;
	v >>= __ffs(dd->enable_mask);
	अगर ((v != OMAP3XXX_EN_DPLL_LOCKED) || (dd->flags & DPLL_J_TYPE))
		rate = parent_rate;
	अन्यथा
		rate = parent_rate * 2;
	वापस rate;
पूर्ण

/**
 * omap3_core_dpll_save_context - Save the m and n values of the भागider
 * @hw: poपूर्णांकer  काष्ठा clk_hw
 *
 * Beक्रमe the dpll रेजिस्टरs are lost save the last rounded rate m and n
 * and the enable mask.
 */
पूर्णांक omap3_core_dpll_save_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	काष्ठा dpll_data *dd;
	u32 v;

	dd = clk->dpll_data;

	v = ti_clk_ll_ops->clk_पढ़ोl(&dd->control_reg);
	clk->context = (v & dd->enable_mask) >> __ffs(dd->enable_mask);

	अगर (clk->context == DPLL_LOCKED) अणु
		v = ti_clk_ll_ops->clk_पढ़ोl(&dd->mult_भाग1_reg);
		dd->last_rounded_m = (v & dd->mult_mask) >>
						__ffs(dd->mult_mask);
		dd->last_rounded_n = ((v & dd->भाग1_mask) >>
						__ffs(dd->भाग1_mask)) + 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * omap3_core_dpll_restore_context - restore the m and n values of the भागider
 * @hw: poपूर्णांकer  काष्ठा clk_hw
 *
 * Restore the last rounded rate m and n
 * and the enable mask.
 */
व्योम omap3_core_dpll_restore_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	स्थिर काष्ठा dpll_data *dd;
	u32 v;

	dd = clk->dpll_data;

	अगर (clk->context == DPLL_LOCKED) अणु
		_omap3_dpll_ग_लिखो_clken(clk, 0x4);
		_omap3_रुको_dpll_status(clk, 0);

		v = ti_clk_ll_ops->clk_पढ़ोl(&dd->mult_भाग1_reg);
		v &= ~(dd->mult_mask | dd->भाग1_mask);
		v |= dd->last_rounded_m << __ffs(dd->mult_mask);
		v |= (dd->last_rounded_n - 1) << __ffs(dd->भाग1_mask);
		ti_clk_ll_ops->clk_ग_लिखोl(v, &dd->mult_भाग1_reg);

		_omap3_dpll_ग_लिखो_clken(clk, DPLL_LOCKED);
		_omap3_रुको_dpll_status(clk, 1);
	पूर्ण अन्यथा अणु
		_omap3_dpll_ग_लिखो_clken(clk, clk->context);
	पूर्ण
पूर्ण

/**
 * omap3_non_core_dpll_save_context - Save the m and n values of the भागider
 * @hw: poपूर्णांकer  काष्ठा clk_hw
 *
 * Beक्रमe the dpll रेजिस्टरs are lost save the last rounded rate m and n
 * and the enable mask.
 */
पूर्णांक omap3_noncore_dpll_save_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	काष्ठा dpll_data *dd;
	u32 v;

	dd = clk->dpll_data;

	v = ti_clk_ll_ops->clk_पढ़ोl(&dd->control_reg);
	clk->context = (v & dd->enable_mask) >> __ffs(dd->enable_mask);

	अगर (clk->context == DPLL_LOCKED) अणु
		v = ti_clk_ll_ops->clk_पढ़ोl(&dd->mult_भाग1_reg);
		dd->last_rounded_m = (v & dd->mult_mask) >>
						__ffs(dd->mult_mask);
		dd->last_rounded_n = ((v & dd->भाग1_mask) >>
						__ffs(dd->भाग1_mask)) + 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * omap3_core_dpll_restore_context - restore the m and n values of the भागider
 * @hw: poपूर्णांकer  काष्ठा clk_hw
 *
 * Restore the last rounded rate m and n
 * and the enable mask.
 */
व्योम omap3_noncore_dpll_restore_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	स्थिर काष्ठा dpll_data *dd;
	u32 ctrl, mult_भाग1;

	dd = clk->dpll_data;

	ctrl = ti_clk_ll_ops->clk_पढ़ोl(&dd->control_reg);
	mult_भाग1 = ti_clk_ll_ops->clk_पढ़ोl(&dd->mult_भाग1_reg);

	अगर (clk->context == ((ctrl & dd->enable_mask) >>
			     __ffs(dd->enable_mask)) &&
	    dd->last_rounded_m == ((mult_भाग1 & dd->mult_mask) >>
				   __ffs(dd->mult_mask)) &&
	    dd->last_rounded_n == ((mult_भाग1 & dd->भाग1_mask) >>
				   __ffs(dd->भाग1_mask)) + 1) अणु
		/* nothing to be करोne */
		वापस;
	पूर्ण

	अगर (clk->context == DPLL_LOCKED)
		omap3_noncore_dpll_program(clk, 0);
	अन्यथा
		_omap3_dpll_ग_लिखो_clken(clk, clk->context);
पूर्ण

/* OMAP3/4 non-CORE DPLL clkops */
स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap3_dpll = अणु
	.allow_idle	= omap3_dpll_allow_idle,
	.deny_idle	= omap3_dpll_deny_idle,
पूर्ण;

/**
 * omap3_dpll4_set_rate - set rate क्रम omap3 per-dpll
 * @hw: घड़ी to change
 * @rate: target rate क्रम घड़ी
 * @parent_rate: घड़ी rate of the DPLL parent
 *
 * Check अगर the current SoC supports the per-dpll reprogram operation
 * or not, and then करो the rate change अगर supported. Returns -EINVAL
 * अगर not supported, 0 क्रम success, and potential error codes from the
 * घड़ी rate change.
 */
पूर्णांक omap3_dpll4_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			 अचिन्हित दीर्घ parent_rate)
अणु
	/*
	 * According to the 12-5 CDP code from TI, "Limitation 2.5"
	 * on 3430ES1 prevents us from changing DPLL multipliers or भागiders
	 * on DPLL4.
	 */
	अगर (ti_clk_get_features()->flags & TI_CLK_DPLL4_DENY_REPROGRAM) अणु
		pr_err("clock: DPLL4 cannot change rate due to silicon 'Limitation 2.5' on 3430ES1.\n");
		वापस -EINVAL;
	पूर्ण

	वापस omap3_noncore_dpll_set_rate(hw, rate, parent_rate);
पूर्ण

/**
 * omap3_dpll4_set_rate_and_parent - set rate and parent क्रम omap3 per-dpll
 * @hw: घड़ी to change
 * @rate: target rate क्रम घड़ी
 * @parent_rate: rate of the parent घड़ी
 * @index: parent index, 0 - reference घड़ी, 1 - bypass घड़ी
 *
 * Check अगर the current SoC support the per-dpll reprogram operation
 * or not, and then करो the rate + parent change अगर supported. Returns
 * -EINVAL अगर not supported, 0 क्रम success, and potential error codes
 * from the घड़ी rate change.
 */
पूर्णांक omap3_dpll4_set_rate_and_parent(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate, u8 index)
अणु
	अगर (ti_clk_get_features()->flags & TI_CLK_DPLL4_DENY_REPROGRAM) अणु
		pr_err("clock: DPLL4 cannot change rate due to silicon 'Limitation 2.5' on 3430ES1.\n");
		वापस -EINVAL;
	पूर्ण

	वापस omap3_noncore_dpll_set_rate_and_parent(hw, rate, parent_rate,
						      index);
पूर्ण

/* Apply DM3730 errata sprz319 advisory 2.1. */
अटल bool omap3_dpll5_apply_errata(काष्ठा clk_hw *hw,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा omap3_dpll5_settings अणु
		अचिन्हित पूर्णांक rate, m, n;
	पूर्ण;

	अटल स्थिर काष्ठा omap3_dpll5_settings precomputed[] = अणु
		/*
		 * From DM3730 errata advisory 2.1, table 35 and 36.
		 * The N value is increased by 1 compared to the tables as the
		 * errata lists रेजिस्टर values जबतक last_rounded_field is the
		 * real भागider value.
		 */
		अणु 12000000,  80,  0 + 1 पूर्ण,
		अणु 13000000, 443,  5 + 1 पूर्ण,
		अणु 19200000,  50,  0 + 1 पूर्ण,
		अणु 26000000, 443, 11 + 1 पूर्ण,
		अणु 38400000,  25,  0 + 1 पूर्ण
	पूर्ण;

	स्थिर काष्ठा omap3_dpll5_settings *d;
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	काष्ठा dpll_data *dd;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(precomputed); ++i) अणु
		अगर (parent_rate == precomputed[i].rate)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(precomputed))
		वापस false;

	d = &precomputed[i];

	/* Update the M, N and rounded rate values and program the DPLL. */
	dd = clk->dpll_data;
	dd->last_rounded_m = d->m;
	dd->last_rounded_n = d->n;
	dd->last_rounded_rate = भाग_u64((u64)parent_rate * d->m, d->n);
	omap3_noncore_dpll_program(clk, 0);

	वापस true;
पूर्ण

/**
 * omap3_dpll5_set_rate - set rate क्रम omap3 dpll5
 * @hw: घड़ी to change
 * @rate: target rate क्रम घड़ी
 * @parent_rate: rate of the parent घड़ी
 *
 * Set rate क्रम the DPLL5 घड़ी. Apply the sprz319 advisory 2.1 on OMAP36xx अगर
 * the DPLL is used क्रम USB host (detected through the requested rate).
 */
पूर्णांक omap3_dpll5_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			 अचिन्हित दीर्घ parent_rate)
अणु
	अगर (rate == OMAP3_DPLL5_FREQ_FOR_USBHOST * 8) अणु
		अगर (omap3_dpll5_apply_errata(hw, parent_rate))
			वापस 0;
	पूर्ण

	वापस omap3_noncore_dpll_set_rate(hw, rate, parent_rate);
पूर्ण
