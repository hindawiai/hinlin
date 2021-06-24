<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018-2019 SiFive, Inc.
 * Wesley Terpstra
 * Paul Walmsley
 *
 * This library supports configuration parsing and reprogramming of
 * the CLN28HPC variant of the Analog Bits Wide Range PLL.  The
 * पूर्णांकention is क्रम this library to be reusable क्रम any device that
 * पूर्णांकegrates this PLL; thus the रेजिस्टर काष्ठाure and programming
 * details are expected to be provided by a separate IP block driver.
 *
 * The bulk of this code is primarily useful क्रम घड़ी configurations
 * that must operate at arbitrary rates, as opposed to घड़ी configurations
 * that are restricted by software or manufacturer guidance to a small,
 * pre-determined set of perक्रमmance poपूर्णांकs.
 *
 * References:
 * - Analog Bits "Wide Range PLL Datasheet", version 2015.10.01
 * - SiFive FU540-C000 Manual v1p0, Chapter 7 "Clocking and Reset"
 *   https://अटल.dev.sअगरive.com/FU540-C000-v1.0.pdf
 */

#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/log2.h>
#समावेश <linux/math64.h>
#समावेश <linux/clk/analogbits-wrpll-cln28hpc.h>

/* MIN_INPUT_FREQ: minimum input घड़ी frequency, in Hz (Fref_min) */
#घोषणा MIN_INPUT_FREQ			7000000

/* MAX_INPUT_FREQ: maximum input घड़ी frequency, in Hz (Fref_max) */
#घोषणा MAX_INPUT_FREQ			600000000

/* MIN_POST_DIVIDE_REF_FREQ: minimum post-भागider reference frequency, in Hz */
#घोषणा MIN_POST_DIVR_FREQ		7000000

/* MAX_POST_DIVIDE_REF_FREQ: maximum post-भागider reference frequency, in Hz */
#घोषणा MAX_POST_DIVR_FREQ		200000000

/* MIN_VCO_FREQ: minimum VCO frequency, in Hz (Fvco_min) */
#घोषणा MIN_VCO_FREQ			2400000000UL

/* MAX_VCO_FREQ: maximum VCO frequency, in Hz (Fvco_max) */
#घोषणा MAX_VCO_FREQ			4800000000ULL

/* MAX_DIVQ_DIVISOR: maximum output भागisor.  Selected by DIVQ = 6 */
#घोषणा MAX_DIVQ_DIVISOR		64

/* MAX_DIVR_DIVISOR: maximum reference भागisor.  Selected by DIVR = 63 */
#घोषणा MAX_DIVR_DIVISOR		64

/* MAX_LOCK_US: maximum PLL lock समय, in microseconds (tLOCK_max) */
#घोषणा MAX_LOCK_US			70

/*
 * ROUND_SHIFT: number of bits to shअगरt to aव्योम precision loss in the rounding
 *              algorithm
 */
#घोषणा ROUND_SHIFT			20

/*
 * Private functions
 */

/**
 * __wrpll_calc_filter_range() - determine PLL loop filter bandwidth
 * @post_भागr_freq: input घड़ी rate after the R भागider
 *
 * Select the value to be presented to the PLL RANGE input संकेतs, based
 * on the input घड़ी frequency after the post-R-भागider @post_भागr_freq.
 * This code follows the recommendations in the PLL datasheet क्रम filter
 * range selection.
 *
 * Return: The RANGE value to be presented to the PLL configuration inमाला_दो,
 *         or a negative वापस code upon error.
 */
अटल पूर्णांक __wrpll_calc_filter_range(अचिन्हित दीर्घ post_भागr_freq)
अणु
	अगर (post_भागr_freq < MIN_POST_DIVR_FREQ ||
	    post_भागr_freq > MAX_POST_DIVR_FREQ) अणु
		WARN(1, "%s: post-divider reference freq out of range: %lu",
		     __func__, post_भागr_freq);
		वापस -दुस्फल;
	पूर्ण

	चयन (post_भागr_freq) अणु
	हाल 0 ... 10999999:
		वापस 1;
	हाल 11000000 ... 17999999:
		वापस 2;
	हाल 18000000 ... 29999999:
		वापस 3;
	हाल 30000000 ... 49999999:
		वापस 4;
	हाल 50000000 ... 79999999:
		वापस 5;
	हाल 80000000 ... 129999999:
		वापस 6;
	पूर्ण

	वापस 7;
पूर्ण

/**
 * __wrpll_calc_fbभाग() - वापस feedback fixed भागide value
 * @c: ptr to a काष्ठा wrpll_cfg record to पढ़ो from
 *
 * The पूर्णांकernal feedback path includes a fixed by-two भागider; the
 * बाह्यal feedback path करोes not.  Return the appropriate भागider
 * value (2 or 1) depending on whether पूर्णांकernal or बाह्यal feedback
 * is enabled.  This code करोesn't test क्रम invalid configurations
 * (e.g. both or neither of WRPLL_FLAGS_*_FEEDBACK are set); it relies
 * on the caller to करो so.
 *
 * Context: Any context.  Caller must protect the memory poपूर्णांकed to by
 *          @c from simultaneous modअगरication.
 *
 * Return: 2 अगर पूर्णांकernal feedback is enabled or 1 अगर बाह्यal feedback
 *         is enabled.
 */
अटल u8 __wrpll_calc_fbभाग(स्थिर काष्ठा wrpll_cfg *c)
अणु
	वापस (c->flags & WRPLL_FLAGS_INT_FEEDBACK_MASK) ? 2 : 1;
पूर्ण

/**
 * __wrpll_calc_भागq() - determine DIVQ based on target PLL output घड़ी rate
 * @target_rate: target PLL output घड़ी rate
 * @vco_rate: poपूर्णांकer to a u64 to store the computed VCO rate पूर्णांकo
 *
 * Determine a reasonable value क्रम the PLL Q post-भागider, based on the
 * target output rate @target_rate क्रम the PLL.  Aदीर्घ with वापसing the
 * computed Q भागider value as the वापस value, this function stores the
 * desired target VCO rate पूर्णांकo the variable poपूर्णांकed to by @vco_rate.
 *
 * Context: Any context.  Caller must protect the memory poपूर्णांकed to by
 *          @vco_rate from simultaneous access or modअगरication.
 *
 * Return: a positive पूर्णांकeger DIVQ value to be programmed पूर्णांकo the hardware
 *         upon success, or 0 upon error (since 0 is an invalid DIVQ value)
 */
अटल u8 __wrpll_calc_भागq(u32 target_rate, u64 *vco_rate)
अणु
	u64 s;
	u8 भागq = 0;

	अगर (!vco_rate) अणु
		WARN_ON(1);
		जाओ wcd_out;
	पूर्ण

	s = भाग_u64(MAX_VCO_FREQ, target_rate);
	अगर (s <= 1) अणु
		भागq = 1;
		*vco_rate = MAX_VCO_FREQ;
	पूर्ण अन्यथा अगर (s > MAX_DIVQ_DIVISOR) अणु
		भागq = ilog2(MAX_DIVQ_DIVISOR);
		*vco_rate = MIN_VCO_FREQ;
	पूर्ण अन्यथा अणु
		भागq = ilog2(s);
		*vco_rate = (u64)target_rate << भागq;
	पूर्ण

wcd_out:
	वापस भागq;
पूर्ण

/**
 * __wrpll_update_parent_rate() - update PLL data when parent rate changes
 * @c: ptr to a काष्ठा wrpll_cfg record to ग_लिखो PLL data to
 * @parent_rate: PLL input refclk rate (pre-R-भागider)
 *
 * Pre-compute some data used by the PLL configuration algorithm when
 * the PLL's reference घड़ी rate changes.  The पूर्णांकention is to aव्योम
 * computation when the parent rate reमुख्यs स्थिरant - expected to be
 * the common हाल.
 *
 * Returns: 0 upon success or -दुस्फल अगर the reference घड़ी rate is
 * out of range.
 */
अटल पूर्णांक __wrpll_update_parent_rate(काष्ठा wrpll_cfg *c,
				      अचिन्हित दीर्घ parent_rate)
अणु
	u8 max_r_क्रम_parent;

	अगर (parent_rate > MAX_INPUT_FREQ || parent_rate < MIN_POST_DIVR_FREQ)
		वापस -दुस्फल;

	c->parent_rate = parent_rate;
	max_r_क्रम_parent = भाग_u64(parent_rate, MIN_POST_DIVR_FREQ);
	c->max_r = min_t(u8, MAX_DIVR_DIVISOR, max_r_क्रम_parent);

	c->init_r = DIV_ROUND_UP_ULL(parent_rate, MAX_POST_DIVR_FREQ);

	वापस 0;
पूर्ण

/**
 * wrpll_configure() - compute PLL configuration क्रम a target rate
 * @c: ptr to a काष्ठा wrpll_cfg record to ग_लिखो पूर्णांकo
 * @target_rate: target PLL output घड़ी rate (post-Q-भागider)
 * @parent_rate: PLL input refclk rate (pre-R-भागider)
 *
 * Compute the appropriate PLL संकेत configuration values and store
 * in PLL context @c.  PLL reprogramming is not glitchless, so the
 * caller should चयन any करोwnstream logic to a dअगरferent घड़ी
 * source or घड़ी-gate it beक्रमe presenting these values to the PLL
 * configuration संकेतs.
 *
 * The caller must pass this function a pre-initialized काष्ठा
 * wrpll_cfg record: either initialized to zero (with the
 * exception of the .name and .flags fields) or पढ़ो from the PLL.
 *
 * Context: Any context.  Caller must protect the memory poपूर्णांकed to by @c
 *          from simultaneous access or modअगरication.
 *
 * Return: 0 upon success; anything अन्यथा upon failure.
 */
पूर्णांक wrpll_configure_क्रम_rate(काष्ठा wrpll_cfg *c, u32 target_rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ ratio;
	u64 target_vco_rate, delta, best_delta, f_pre_भाग, vco, vco_pre;
	u32 best_f, f, post_भागr_freq;
	u8 fbभाग, भागq, best_r, r;
	पूर्णांक range;

	अगर (c->flags == 0) अणु
		WARN(1, "%s called with uninitialized PLL config", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Initialize rounding data अगर it hasn't been initialized alपढ़ोy */
	अगर (parent_rate != c->parent_rate) अणु
		अगर (__wrpll_update_parent_rate(c, parent_rate)) अणु
			pr_err("%s: PLL input rate is out of range\n",
			       __func__);
			वापस -दुस्फल;
		पूर्ण
	पूर्ण

	c->flags &= ~WRPLL_FLAGS_RESET_MASK;

	/* Put the PLL पूर्णांकo bypass अगर the user requests the parent घड़ी rate */
	अगर (target_rate == parent_rate) अणु
		c->flags |= WRPLL_FLAGS_BYPASS_MASK;
		वापस 0;
	पूर्ण

	c->flags &= ~WRPLL_FLAGS_BYPASS_MASK;

	/* Calculate the Q shअगरt and target VCO rate */
	भागq = __wrpll_calc_भागq(target_rate, &target_vco_rate);
	अगर (!भागq)
		वापस -1;
	c->भागq = भागq;

	/* Precalculate the pre-Q भागider target ratio */
	ratio = भाग64_u64((target_vco_rate << ROUND_SHIFT), parent_rate);

	fbभाग = __wrpll_calc_fbभाग(c);
	best_r = 0;
	best_f = 0;
	best_delta = MAX_VCO_FREQ;

	/*
	 * Consider all values क्रम R which land within
	 * [MIN_POST_DIVR_FREQ, MAX_POST_DIVR_FREQ]; prefer smaller R
	 */
	क्रम (r = c->init_r; r <= c->max_r; ++r) अणु
		f_pre_भाग = ratio * r;
		f = (f_pre_भाग + (1 << ROUND_SHIFT)) >> ROUND_SHIFT;
		f >>= (fbभाग - 1);

		post_भागr_freq = भाग_u64(parent_rate, r);
		vco_pre = fbभाग * post_भागr_freq;
		vco = vco_pre * f;

		/* Ensure rounding didn't take us out of range */
		अगर (vco > target_vco_rate) अणु
			--f;
			vco = vco_pre * f;
		पूर्ण अन्यथा अगर (vco < MIN_VCO_FREQ) अणु
			++f;
			vco = vco_pre * f;
		पूर्ण

		delta = असल(target_rate - vco);
		अगर (delta < best_delta) अणु
			best_delta = delta;
			best_r = r;
			best_f = f;
		पूर्ण
	पूर्ण

	c->भागr = best_r - 1;
	c->भागf = best_f - 1;

	post_भागr_freq = भाग_u64(parent_rate, best_r);

	/* Pick the best PLL jitter filter */
	range = __wrpll_calc_filter_range(post_भागr_freq);
	अगर (range < 0)
		वापस range;
	c->range = range;

	वापस 0;
पूर्ण

/**
 * wrpll_calc_output_rate() - calculate the PLL's target output rate
 * @c: ptr to a काष्ठा wrpll_cfg record to पढ़ो from
 * @parent_rate: PLL refclk rate
 *
 * Given a poपूर्णांकer to the PLL's current input configuration @c and the
 * PLL's input reference घड़ी rate @parent_rate (beक्रमe the R
 * pre-भागider), calculate the PLL's output घड़ी rate (after the Q
 * post-भागider).
 *
 * Context: Any context.  Caller must protect the memory poपूर्णांकed to by @c
 *          from simultaneous modअगरication.
 *
 * Return: the PLL's output घड़ी rate, in Hz.  The वापस value from
 *         this function is पूर्णांकended to be convenient to pass directly
 *         to the Linux घड़ी framework; thus there is no explicit
 *         error वापस value.
 */
अचिन्हित दीर्घ wrpll_calc_output_rate(स्थिर काष्ठा wrpll_cfg *c,
				     अचिन्हित दीर्घ parent_rate)
अणु
	u8 fbभाग;
	u64 n;

	अगर (c->flags & WRPLL_FLAGS_EXT_FEEDBACK_MASK) अणु
		WARN(1, "external feedback mode not yet supported");
		वापस अच_दीर्घ_उच्च;
	पूर्ण

	fbभाग = __wrpll_calc_fbभाग(c);
	n = parent_rate * fbभाग * (c->भागf + 1);
	n = भाग_u64(n, c->भागr + 1);
	n >>= c->भागq;

	वापस n;
पूर्ण

/**
 * wrpll_calc_max_lock_us() - वापस the समय क्रम the PLL to lock
 * @c: ptr to a काष्ठा wrpll_cfg record to पढ़ो from
 *
 * Return the minimum amount of समय (in microseconds) that the caller
 * must रुको after reprogramming the PLL to ensure that it is locked
 * to the input frequency and stable.  This is likely to depend on the DIVR
 * value; this is under discussion with the manufacturer.
 *
 * Return: the minimum amount of समय the caller must रुको क्रम the PLL
 *         to lock (in microseconds)
 */
अचिन्हित पूर्णांक wrpll_calc_max_lock_us(स्थिर काष्ठा wrpll_cfg *c)
अणु
	वापस MAX_LOCK_US;
पूर्ण
