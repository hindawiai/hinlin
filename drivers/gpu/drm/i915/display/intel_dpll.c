<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */
#समावेश <linux/kernel.h>
#समावेश "intel_crtc.h"
#समावेश "intel_display_types.h"
#समावेश "intel_display.h"
#समावेश "intel_dpll.h"
#समावेश "intel_lvds.h"
#समावेश "intel_panel.h"
#समावेश "intel_sideband.h"

काष्ठा पूर्णांकel_limit अणु
	काष्ठा अणु
		पूर्णांक min, max;
	पूर्ण करोt, vco, n, m, m1, m2, p, p1;

	काष्ठा अणु
		पूर्णांक करोt_limit;
		पूर्णांक p2_slow, p2_fast;
	पूर्ण p2;
पूर्ण;
अटल स्थिर काष्ठा पूर्णांकel_limit पूर्णांकel_limits_i8xx_dac = अणु
	.करोt = अणु .min = 25000, .max = 350000 पूर्ण,
	.vco = अणु .min = 908000, .max = 1512000 पूर्ण,
	.n = अणु .min = 2, .max = 16 पूर्ण,
	.m = अणु .min = 96, .max = 140 पूर्ण,
	.m1 = अणु .min = 18, .max = 26 पूर्ण,
	.m2 = अणु .min = 6, .max = 16 पूर्ण,
	.p = अणु .min = 4, .max = 128 पूर्ण,
	.p1 = अणु .min = 2, .max = 33 पूर्ण,
	.p2 = अणु .करोt_limit = 165000,
		.p2_slow = 4, .p2_fast = 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit पूर्णांकel_limits_i8xx_dvo = अणु
	.करोt = अणु .min = 25000, .max = 350000 पूर्ण,
	.vco = अणु .min = 908000, .max = 1512000 पूर्ण,
	.n = अणु .min = 2, .max = 16 पूर्ण,
	.m = अणु .min = 96, .max = 140 पूर्ण,
	.m1 = अणु .min = 18, .max = 26 पूर्ण,
	.m2 = अणु .min = 6, .max = 16 पूर्ण,
	.p = अणु .min = 4, .max = 128 पूर्ण,
	.p1 = अणु .min = 2, .max = 33 पूर्ण,
	.p2 = अणु .करोt_limit = 165000,
		.p2_slow = 4, .p2_fast = 4 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit पूर्णांकel_limits_i8xx_lvds = अणु
	.करोt = अणु .min = 25000, .max = 350000 पूर्ण,
	.vco = अणु .min = 908000, .max = 1512000 पूर्ण,
	.n = अणु .min = 2, .max = 16 पूर्ण,
	.m = अणु .min = 96, .max = 140 पूर्ण,
	.m1 = अणु .min = 18, .max = 26 पूर्ण,
	.m2 = अणु .min = 6, .max = 16 पूर्ण,
	.p = अणु .min = 4, .max = 128 पूर्ण,
	.p1 = अणु .min = 1, .max = 6 पूर्ण,
	.p2 = अणु .करोt_limit = 165000,
		.p2_slow = 14, .p2_fast = 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit पूर्णांकel_limits_i9xx_sdvo = अणु
	.करोt = अणु .min = 20000, .max = 400000 पूर्ण,
	.vco = अणु .min = 1400000, .max = 2800000 पूर्ण,
	.n = अणु .min = 1, .max = 6 पूर्ण,
	.m = अणु .min = 70, .max = 120 पूर्ण,
	.m1 = अणु .min = 8, .max = 18 पूर्ण,
	.m2 = अणु .min = 3, .max = 7 पूर्ण,
	.p = अणु .min = 5, .max = 80 पूर्ण,
	.p1 = अणु .min = 1, .max = 8 पूर्ण,
	.p2 = अणु .करोt_limit = 200000,
		.p2_slow = 10, .p2_fast = 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit पूर्णांकel_limits_i9xx_lvds = अणु
	.करोt = अणु .min = 20000, .max = 400000 पूर्ण,
	.vco = अणु .min = 1400000, .max = 2800000 पूर्ण,
	.n = अणु .min = 1, .max = 6 पूर्ण,
	.m = अणु .min = 70, .max = 120 पूर्ण,
	.m1 = अणु .min = 8, .max = 18 पूर्ण,
	.m2 = अणु .min = 3, .max = 7 पूर्ण,
	.p = अणु .min = 7, .max = 98 पूर्ण,
	.p1 = अणु .min = 1, .max = 8 पूर्ण,
	.p2 = अणु .करोt_limit = 112000,
		.p2_slow = 14, .p2_fast = 7 पूर्ण,
पूर्ण;


अटल स्थिर काष्ठा पूर्णांकel_limit पूर्णांकel_limits_g4x_sdvo = अणु
	.करोt = अणु .min = 25000, .max = 270000 पूर्ण,
	.vco = अणु .min = 1750000, .max = 3500000पूर्ण,
	.n = अणु .min = 1, .max = 4 पूर्ण,
	.m = अणु .min = 104, .max = 138 पूर्ण,
	.m1 = अणु .min = 17, .max = 23 पूर्ण,
	.m2 = अणु .min = 5, .max = 11 पूर्ण,
	.p = अणु .min = 10, .max = 30 पूर्ण,
	.p1 = अणु .min = 1, .max = 3पूर्ण,
	.p2 = अणु .करोt_limit = 270000,
		.p2_slow = 10,
		.p2_fast = 10
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit पूर्णांकel_limits_g4x_hdmi = अणु
	.करोt = अणु .min = 22000, .max = 400000 पूर्ण,
	.vco = अणु .min = 1750000, .max = 3500000पूर्ण,
	.n = अणु .min = 1, .max = 4 पूर्ण,
	.m = अणु .min = 104, .max = 138 पूर्ण,
	.m1 = अणु .min = 16, .max = 23 पूर्ण,
	.m2 = अणु .min = 5, .max = 11 पूर्ण,
	.p = अणु .min = 5, .max = 80 पूर्ण,
	.p1 = अणु .min = 1, .max = 8पूर्ण,
	.p2 = अणु .करोt_limit = 165000,
		.p2_slow = 10, .p2_fast = 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit पूर्णांकel_limits_g4x_single_channel_lvds = अणु
	.करोt = अणु .min = 20000, .max = 115000 पूर्ण,
	.vco = अणु .min = 1750000, .max = 3500000 पूर्ण,
	.n = अणु .min = 1, .max = 3 पूर्ण,
	.m = अणु .min = 104, .max = 138 पूर्ण,
	.m1 = अणु .min = 17, .max = 23 पूर्ण,
	.m2 = अणु .min = 5, .max = 11 पूर्ण,
	.p = अणु .min = 28, .max = 112 पूर्ण,
	.p1 = अणु .min = 2, .max = 8 पूर्ण,
	.p2 = अणु .करोt_limit = 0,
		.p2_slow = 14, .p2_fast = 14
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit पूर्णांकel_limits_g4x_dual_channel_lvds = अणु
	.करोt = अणु .min = 80000, .max = 224000 पूर्ण,
	.vco = अणु .min = 1750000, .max = 3500000 पूर्ण,
	.n = अणु .min = 1, .max = 3 पूर्ण,
	.m = अणु .min = 104, .max = 138 पूर्ण,
	.m1 = अणु .min = 17, .max = 23 पूर्ण,
	.m2 = अणु .min = 5, .max = 11 पूर्ण,
	.p = अणु .min = 14, .max = 42 पूर्ण,
	.p1 = अणु .min = 2, .max = 6 पूर्ण,
	.p2 = अणु .करोt_limit = 0,
		.p2_slow = 7, .p2_fast = 7
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit pnv_limits_sdvo = अणु
	.करोt = अणु .min = 20000, .max = 400000पूर्ण,
	.vco = अणु .min = 1700000, .max = 3500000 पूर्ण,
	/* Pineview's Ncounter is a ring counter */
	.n = अणु .min = 3, .max = 6 पूर्ण,
	.m = अणु .min = 2, .max = 256 पूर्ण,
	/* Pineview only has one combined m भागider, which we treat as m2. */
	.m1 = अणु .min = 0, .max = 0 पूर्ण,
	.m2 = अणु .min = 0, .max = 254 पूर्ण,
	.p = अणु .min = 5, .max = 80 पूर्ण,
	.p1 = अणु .min = 1, .max = 8 पूर्ण,
	.p2 = अणु .करोt_limit = 200000,
		.p2_slow = 10, .p2_fast = 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit pnv_limits_lvds = अणु
	.करोt = अणु .min = 20000, .max = 400000 पूर्ण,
	.vco = अणु .min = 1700000, .max = 3500000 पूर्ण,
	.n = अणु .min = 3, .max = 6 पूर्ण,
	.m = अणु .min = 2, .max = 256 पूर्ण,
	.m1 = अणु .min = 0, .max = 0 पूर्ण,
	.m2 = अणु .min = 0, .max = 254 पूर्ण,
	.p = अणु .min = 7, .max = 112 पूर्ण,
	.p1 = अणु .min = 1, .max = 8 पूर्ण,
	.p2 = अणु .करोt_limit = 112000,
		.p2_slow = 14, .p2_fast = 14 पूर्ण,
पूर्ण;

/* Ironlake / Sandybridge
 *
 * We calculate घड़ी using (रेजिस्टर_value + 2) क्रम N/M1/M2, so here
 * the range value क्रम them is (actual_value - 2).
 */
अटल स्थिर काष्ठा पूर्णांकel_limit ilk_limits_dac = अणु
	.करोt = अणु .min = 25000, .max = 350000 पूर्ण,
	.vco = अणु .min = 1760000, .max = 3510000 पूर्ण,
	.n = अणु .min = 1, .max = 5 पूर्ण,
	.m = अणु .min = 79, .max = 127 पूर्ण,
	.m1 = अणु .min = 12, .max = 22 पूर्ण,
	.m2 = अणु .min = 5, .max = 9 पूर्ण,
	.p = अणु .min = 5, .max = 80 पूर्ण,
	.p1 = अणु .min = 1, .max = 8 पूर्ण,
	.p2 = अणु .करोt_limit = 225000,
		.p2_slow = 10, .p2_fast = 5 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit ilk_limits_single_lvds = अणु
	.करोt = अणु .min = 25000, .max = 350000 पूर्ण,
	.vco = अणु .min = 1760000, .max = 3510000 पूर्ण,
	.n = अणु .min = 1, .max = 3 पूर्ण,
	.m = अणु .min = 79, .max = 118 पूर्ण,
	.m1 = अणु .min = 12, .max = 22 पूर्ण,
	.m2 = अणु .min = 5, .max = 9 पूर्ण,
	.p = अणु .min = 28, .max = 112 पूर्ण,
	.p1 = अणु .min = 2, .max = 8 पूर्ण,
	.p2 = अणु .करोt_limit = 225000,
		.p2_slow = 14, .p2_fast = 14 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit ilk_limits_dual_lvds = अणु
	.करोt = अणु .min = 25000, .max = 350000 पूर्ण,
	.vco = अणु .min = 1760000, .max = 3510000 पूर्ण,
	.n = अणु .min = 1, .max = 3 पूर्ण,
	.m = अणु .min = 79, .max = 127 पूर्ण,
	.m1 = अणु .min = 12, .max = 22 पूर्ण,
	.m2 = अणु .min = 5, .max = 9 पूर्ण,
	.p = अणु .min = 14, .max = 56 पूर्ण,
	.p1 = अणु .min = 2, .max = 8 पूर्ण,
	.p2 = अणु .करोt_limit = 225000,
		.p2_slow = 7, .p2_fast = 7 पूर्ण,
पूर्ण;

/* LVDS 100mhz refclk limits. */
अटल स्थिर काष्ठा पूर्णांकel_limit ilk_limits_single_lvds_100m = अणु
	.करोt = अणु .min = 25000, .max = 350000 पूर्ण,
	.vco = अणु .min = 1760000, .max = 3510000 पूर्ण,
	.n = अणु .min = 1, .max = 2 पूर्ण,
	.m = अणु .min = 79, .max = 126 पूर्ण,
	.m1 = अणु .min = 12, .max = 22 पूर्ण,
	.m2 = अणु .min = 5, .max = 9 पूर्ण,
	.p = अणु .min = 28, .max = 112 पूर्ण,
	.p1 = अणु .min = 2, .max = 8 पूर्ण,
	.p2 = अणु .करोt_limit = 225000,
		.p2_slow = 14, .p2_fast = 14 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit ilk_limits_dual_lvds_100m = अणु
	.करोt = अणु .min = 25000, .max = 350000 पूर्ण,
	.vco = अणु .min = 1760000, .max = 3510000 पूर्ण,
	.n = अणु .min = 1, .max = 3 पूर्ण,
	.m = अणु .min = 79, .max = 126 पूर्ण,
	.m1 = अणु .min = 12, .max = 22 पूर्ण,
	.m2 = अणु .min = 5, .max = 9 पूर्ण,
	.p = अणु .min = 14, .max = 42 पूर्ण,
	.p1 = अणु .min = 2, .max = 6 पूर्ण,
	.p2 = अणु .करोt_limit = 225000,
		.p2_slow = 7, .p2_fast = 7 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit पूर्णांकel_limits_vlv = अणु
	 /*
	  * These are the data rate limits (measured in fast घड़ीs)
	  * since those are the strictest limits we have. The fast
	  * घड़ी and actual rate limits are more relaxed, so checking
	  * them would make no dअगरference.
	  */
	.करोt = अणु .min = 25000 * 5, .max = 270000 * 5 पूर्ण,
	.vco = अणु .min = 4000000, .max = 6000000 पूर्ण,
	.n = अणु .min = 1, .max = 7 पूर्ण,
	.m1 = अणु .min = 2, .max = 3 पूर्ण,
	.m2 = अणु .min = 11, .max = 156 पूर्ण,
	.p1 = अणु .min = 2, .max = 3 पूर्ण,
	.p2 = अणु .p2_slow = 2, .p2_fast = 20 पूर्ण, /* slow=min, fast=max */
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit पूर्णांकel_limits_chv = अणु
	/*
	 * These are the data rate limits (measured in fast घड़ीs)
	 * since those are the strictest limits we have.  The fast
	 * घड़ी and actual rate limits are more relaxed, so checking
	 * them would make no dअगरference.
	 */
	.करोt = अणु .min = 25000 * 5, .max = 540000 * 5पूर्ण,
	.vco = अणु .min = 4800000, .max = 6480000 पूर्ण,
	.n = अणु .min = 1, .max = 1 पूर्ण,
	.m1 = अणु .min = 2, .max = 2 पूर्ण,
	.m2 = अणु .min = 24 << 22, .max = 175 << 22 पूर्ण,
	.p1 = अणु .min = 2, .max = 4 पूर्ण,
	.p2 = अणु	.p2_slow = 1, .p2_fast = 14 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_limit पूर्णांकel_limits_bxt = अणु
	/* FIXME: find real करोt limits */
	.करोt = अणु .min = 0, .max = पूर्णांक_उच्च पूर्ण,
	.vco = अणु .min = 4800000, .max = 6700000 पूर्ण,
	.n = अणु .min = 1, .max = 1 पूर्ण,
	.m1 = अणु .min = 2, .max = 2 पूर्ण,
	/* FIXME: find real m2 limits */
	.m2 = अणु .min = 2 << 22, .max = 255 << 22 पूर्ण,
	.p1 = अणु .min = 2, .max = 4 पूर्ण,
	.p2 = अणु .p2_slow = 1, .p2_fast = 20 पूर्ण,
पूर्ण;

/*
 * Platक्रमm specअगरic helpers to calculate the port PLL loopback- (घड़ी.m),
 * and post-भागider (घड़ी.p) values, pre- (घड़ी.vco) and post-भागided fast
 * (घड़ी.करोt) घड़ी rates. This fast करोt घड़ी is fed to the port's IO logic.
 * The helpers' वापस value is the rate of the घड़ी that is fed to the
 * display engine's pipe which can be the above fast करोt घड़ी rate or a
 * भागided-करोwn version of it.
 */
/* m1 is reserved as 0 in Pineview, n is a ring counter */
पूर्णांक pnv_calc_dpll_params(पूर्णांक refclk, काष्ठा dpll *घड़ी)
अणु
	घड़ी->m = घड़ी->m2 + 2;
	घड़ी->p = घड़ी->p1 * घड़ी->p2;
	अगर (WARN_ON(घड़ी->n == 0 || घड़ी->p == 0))
		वापस 0;
	घड़ी->vco = DIV_ROUND_CLOSEST(refclk * घड़ी->m, घड़ी->n);
	घड़ी->करोt = DIV_ROUND_CLOSEST(घड़ी->vco, घड़ी->p);

	वापस घड़ी->करोt;
पूर्ण

अटल u32 i9xx_dpll_compute_m(काष्ठा dpll *dpll)
अणु
	वापस 5 * (dpll->m1 + 2) + (dpll->m2 + 2);
पूर्ण

पूर्णांक i9xx_calc_dpll_params(पूर्णांक refclk, काष्ठा dpll *घड़ी)
अणु
	घड़ी->m = i9xx_dpll_compute_m(घड़ी);
	घड़ी->p = घड़ी->p1 * घड़ी->p2;
	अगर (WARN_ON(घड़ी->n + 2 == 0 || घड़ी->p == 0))
		वापस 0;
	घड़ी->vco = DIV_ROUND_CLOSEST(refclk * घड़ी->m, घड़ी->n + 2);
	घड़ी->करोt = DIV_ROUND_CLOSEST(घड़ी->vco, घड़ी->p);

	वापस घड़ी->करोt;
पूर्ण

पूर्णांक vlv_calc_dpll_params(पूर्णांक refclk, काष्ठा dpll *घड़ी)
अणु
	घड़ी->m = घड़ी->m1 * घड़ी->m2;
	घड़ी->p = घड़ी->p1 * घड़ी->p2;
	अगर (WARN_ON(घड़ी->n == 0 || घड़ी->p == 0))
		वापस 0;
	घड़ी->vco = DIV_ROUND_CLOSEST(refclk * घड़ी->m, घड़ी->n);
	घड़ी->करोt = DIV_ROUND_CLOSEST(घड़ी->vco, घड़ी->p);

	वापस घड़ी->करोt / 5;
पूर्ण

पूर्णांक chv_calc_dpll_params(पूर्णांक refclk, काष्ठा dpll *घड़ी)
अणु
	घड़ी->m = घड़ी->m1 * घड़ी->m2;
	घड़ी->p = घड़ी->p1 * घड़ी->p2;
	अगर (WARN_ON(घड़ी->n == 0 || घड़ी->p == 0))
		वापस 0;
	घड़ी->vco = DIV_ROUND_CLOSEST_ULL(mul_u32_u32(refclk, घड़ी->m),
					   घड़ी->n << 22);
	घड़ी->करोt = DIV_ROUND_CLOSEST(घड़ी->vco, घड़ी->p);

	वापस घड़ी->करोt / 5;
पूर्ण

/*
 * Returns whether the given set of भागisors are valid क्रम a given refclk with
 * the given connectors.
 */
अटल bool पूर्णांकel_pll_is_valid(काष्ठा drm_i915_निजी *dev_priv,
			       स्थिर काष्ठा पूर्णांकel_limit *limit,
			       स्थिर काष्ठा dpll *घड़ी)
अणु
	अगर (घड़ी->n < limit->n.min || limit->n.max < घड़ी->n)
		वापस false;
	अगर (घड़ी->p1 < limit->p1.min || limit->p1.max < घड़ी->p1)
		वापस false;
	अगर (घड़ी->m2 < limit->m2.min || limit->m2.max < घड़ी->m2)
		वापस false;
	अगर (घड़ी->m1 < limit->m1.min || limit->m1.max < घड़ी->m1)
		वापस false;

	अगर (!IS_PINEVIEW(dev_priv) && !IS_VALLEYVIEW(dev_priv) &&
	    !IS_CHERRYVIEW(dev_priv) && !IS_GEN9_LP(dev_priv))
		अगर (घड़ी->m1 <= घड़ी->m2)
			वापस false;

	अगर (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv) &&
	    !IS_GEN9_LP(dev_priv)) अणु
		अगर (घड़ी->p < limit->p.min || limit->p.max < घड़ी->p)
			वापस false;
		अगर (घड़ी->m < limit->m.min || limit->m.max < घड़ी->m)
			वापस false;
	पूर्ण

	अगर (घड़ी->vco < limit->vco.min || limit->vco.max < घड़ी->vco)
		वापस false;
	/* XXX: We may need to be checking "Dot clock" depending on the multiplier,
	 * connector, etc., rather than just a single range.
	 */
	अगर (घड़ी->करोt < limit->करोt.min || limit->करोt.max < घड़ी->करोt)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक
i9xx_select_p2_भाग(स्थिर काष्ठा पूर्णांकel_limit *limit,
		   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
		   पूर्णांक target)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS)) अणु
		/*
		 * For LVDS just rely on its current settings क्रम dual-channel.
		 * We haven't figured out how to reliably set up dअगरferent
		 * single/dual channel state, अगर we even can.
		 */
		अगर (पूर्णांकel_is_dual_link_lvds(dev_priv))
			वापस limit->p2.p2_fast;
		अन्यथा
			वापस limit->p2.p2_slow;
	पूर्ण अन्यथा अणु
		अगर (target < limit->p2.करोt_limit)
			वापस limit->p2.p2_slow;
		अन्यथा
			वापस limit->p2.p2_fast;
	पूर्ण
पूर्ण

/*
 * Returns a set of भागisors क्रम the desired target घड़ी with the given
 * refclk, or FALSE.  The वापसed values represent the घड़ी equation:
 * reflck * (5 * (m1 + 2) + (m2 + 2)) / (n + 2) / p1 / p2.
 *
 * Target and reference घड़ीs are specअगरied in kHz.
 *
 * If match_घड़ी is provided, then best_घड़ी P भागider must match the P
 * भागider from @match_घड़ी used क्रम LVDS करोwnघड़ीing.
 */
अटल bool
i9xx_find_best_dpll(स्थिर काष्ठा पूर्णांकel_limit *limit,
		    काष्ठा पूर्णांकel_crtc_state *crtc_state,
		    पूर्णांक target, पूर्णांक refclk, काष्ठा dpll *match_घड़ी,
		    काष्ठा dpll *best_घड़ी)
अणु
	काष्ठा drm_device *dev = crtc_state->uapi.crtc->dev;
	काष्ठा dpll घड़ी;
	पूर्णांक err = target;

	स_रखो(best_घड़ी, 0, माप(*best_घड़ी));

	घड़ी.p2 = i9xx_select_p2_भाग(limit, crtc_state, target);

	क्रम (घड़ी.m1 = limit->m1.min; घड़ी.m1 <= limit->m1.max;
	     घड़ी.m1++) अणु
		क्रम (घड़ी.m2 = limit->m2.min;
		     घड़ी.m2 <= limit->m2.max; घड़ी.m2++) अणु
			अगर (घड़ी.m2 >= घड़ी.m1)
				अवरोध;
			क्रम (घड़ी.n = limit->n.min;
			     घड़ी.n <= limit->n.max; घड़ी.n++) अणु
				क्रम (घड़ी.p1 = limit->p1.min;
					घड़ी.p1 <= limit->p1.max; घड़ी.p1++) अणु
					पूर्णांक this_err;

					i9xx_calc_dpll_params(refclk, &घड़ी);
					अगर (!पूर्णांकel_pll_is_valid(to_i915(dev),
								limit,
								&घड़ी))
						जारी;
					अगर (match_घड़ी &&
					    घड़ी.p != match_घड़ी->p)
						जारी;

					this_err = असल(घड़ी.करोt - target);
					अगर (this_err < err) अणु
						*best_घड़ी = घड़ी;
						err = this_err;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस (err != target);
पूर्ण

/*
 * Returns a set of भागisors क्रम the desired target घड़ी with the given
 * refclk, or FALSE.  The वापसed values represent the घड़ी equation:
 * reflck * (5 * (m1 + 2) + (m2 + 2)) / (n + 2) / p1 / p2.
 *
 * Target and reference घड़ीs are specअगरied in kHz.
 *
 * If match_घड़ी is provided, then best_घड़ी P भागider must match the P
 * भागider from @match_घड़ी used क्रम LVDS करोwnघड़ीing.
 */
अटल bool
pnv_find_best_dpll(स्थिर काष्ठा पूर्णांकel_limit *limit,
		   काष्ठा पूर्णांकel_crtc_state *crtc_state,
		   पूर्णांक target, पूर्णांक refclk, काष्ठा dpll *match_घड़ी,
		   काष्ठा dpll *best_घड़ी)
अणु
	काष्ठा drm_device *dev = crtc_state->uapi.crtc->dev;
	काष्ठा dpll घड़ी;
	पूर्णांक err = target;

	स_रखो(best_घड़ी, 0, माप(*best_घड़ी));

	घड़ी.p2 = i9xx_select_p2_भाग(limit, crtc_state, target);

	क्रम (घड़ी.m1 = limit->m1.min; घड़ी.m1 <= limit->m1.max;
	     घड़ी.m1++) अणु
		क्रम (घड़ी.m2 = limit->m2.min;
		     घड़ी.m2 <= limit->m2.max; घड़ी.m2++) अणु
			क्रम (घड़ी.n = limit->n.min;
			     घड़ी.n <= limit->n.max; घड़ी.n++) अणु
				क्रम (घड़ी.p1 = limit->p1.min;
					घड़ी.p1 <= limit->p1.max; घड़ी.p1++) अणु
					पूर्णांक this_err;

					pnv_calc_dpll_params(refclk, &घड़ी);
					अगर (!पूर्णांकel_pll_is_valid(to_i915(dev),
								limit,
								&घड़ी))
						जारी;
					अगर (match_घड़ी &&
					    घड़ी.p != match_घड़ी->p)
						जारी;

					this_err = असल(घड़ी.करोt - target);
					अगर (this_err < err) अणु
						*best_घड़ी = घड़ी;
						err = this_err;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस (err != target);
पूर्ण

/*
 * Returns a set of भागisors क्रम the desired target घड़ी with the given
 * refclk, or FALSE.  The वापसed values represent the घड़ी equation:
 * reflck * (5 * (m1 + 2) + (m2 + 2)) / (n + 2) / p1 / p2.
 *
 * Target and reference घड़ीs are specअगरied in kHz.
 *
 * If match_घड़ी is provided, then best_घड़ी P भागider must match the P
 * भागider from @match_घड़ी used क्रम LVDS करोwnघड़ीing.
 */
अटल bool
g4x_find_best_dpll(स्थिर काष्ठा पूर्णांकel_limit *limit,
		   काष्ठा पूर्णांकel_crtc_state *crtc_state,
		   पूर्णांक target, पूर्णांक refclk, काष्ठा dpll *match_घड़ी,
		   काष्ठा dpll *best_घड़ी)
अणु
	काष्ठा drm_device *dev = crtc_state->uapi.crtc->dev;
	काष्ठा dpll घड़ी;
	पूर्णांक max_n;
	bool found = false;
	/* approximately equals target * 0.00585 */
	पूर्णांक err_most = (target >> 8) + (target >> 9);

	स_रखो(best_घड़ी, 0, माप(*best_घड़ी));

	घड़ी.p2 = i9xx_select_p2_भाग(limit, crtc_state, target);

	max_n = limit->n.max;
	/* based on hardware requirement, prefer smaller n to precision */
	क्रम (घड़ी.n = limit->n.min; घड़ी.n <= max_n; घड़ी.n++) अणु
		/* based on hardware requirement, prefere larger m1,m2 */
		क्रम (घड़ी.m1 = limit->m1.max;
		     घड़ी.m1 >= limit->m1.min; घड़ी.m1--) अणु
			क्रम (घड़ी.m2 = limit->m2.max;
			     घड़ी.m2 >= limit->m2.min; घड़ी.m2--) अणु
				क्रम (घड़ी.p1 = limit->p1.max;
				     घड़ी.p1 >= limit->p1.min; घड़ी.p1--) अणु
					पूर्णांक this_err;

					i9xx_calc_dpll_params(refclk, &घड़ी);
					अगर (!पूर्णांकel_pll_is_valid(to_i915(dev),
								limit,
								&घड़ी))
						जारी;

					this_err = असल(घड़ी.करोt - target);
					अगर (this_err < err_most) अणु
						*best_घड़ी = घड़ी;
						err_most = this_err;
						max_n = घड़ी.n;
						found = true;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस found;
पूर्ण

/*
 * Check अगर the calculated PLL configuration is more optimal compared to the
 * best configuration and error found so far. Return the calculated error.
 */
अटल bool vlv_PLL_is_optimal(काष्ठा drm_device *dev, पूर्णांक target_freq,
			       स्थिर काष्ठा dpll *calculated_घड़ी,
			       स्थिर काष्ठा dpll *best_घड़ी,
			       अचिन्हित पूर्णांक best_error_ppm,
			       अचिन्हित पूर्णांक *error_ppm)
अणु
	/*
	 * For CHV ignore the error and consider only the P value.
	 * Prefer a bigger P value based on HW requirements.
	 */
	अगर (IS_CHERRYVIEW(to_i915(dev))) अणु
		*error_ppm = 0;

		वापस calculated_घड़ी->p > best_घड़ी->p;
	पूर्ण

	अगर (drm_WARN_ON_ONCE(dev, !target_freq))
		वापस false;

	*error_ppm = भाग_u64(1000000ULL *
				असल(target_freq - calculated_घड़ी->करोt),
			     target_freq);
	/*
	 * Prefer a better P value over a better (smaller) error अगर the error
	 * is small. Ensure this preference क्रम future configurations too by
	 * setting the error to 0.
	 */
	अगर (*error_ppm < 100 && calculated_घड़ी->p > best_घड़ी->p) अणु
		*error_ppm = 0;

		वापस true;
	पूर्ण

	वापस *error_ppm + 10 < best_error_ppm;
पूर्ण

/*
 * Returns a set of भागisors क्रम the desired target घड़ी with the given
 * refclk, or FALSE.  The वापसed values represent the घड़ी equation:
 * reflck * (5 * (m1 + 2) + (m2 + 2)) / (n + 2) / p1 / p2.
 */
अटल bool
vlv_find_best_dpll(स्थिर काष्ठा पूर्णांकel_limit *limit,
		   काष्ठा पूर्णांकel_crtc_state *crtc_state,
		   पूर्णांक target, पूर्णांक refclk, काष्ठा dpll *match_घड़ी,
		   काष्ठा dpll *best_घड़ी)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा dpll घड़ी;
	अचिन्हित पूर्णांक bestppm = 1000000;
	/* min update 19.2 MHz */
	पूर्णांक max_n = min(limit->n.max, refclk / 19200);
	bool found = false;

	target *= 5; /* fast घड़ी */

	स_रखो(best_घड़ी, 0, माप(*best_घड़ी));

	/* based on hardware requirement, prefer smaller n to precision */
	क्रम (घड़ी.n = limit->n.min; घड़ी.n <= max_n; घड़ी.n++) अणु
		क्रम (घड़ी.p1 = limit->p1.max; घड़ी.p1 >= limit->p1.min; घड़ी.p1--) अणु
			क्रम (घड़ी.p2 = limit->p2.p2_fast; घड़ी.p2 >= limit->p2.p2_slow;
			     घड़ी.p2 -= घड़ी.p2 > 10 ? 2 : 1) अणु
				घड़ी.p = घड़ी.p1 * घड़ी.p2;
				/* based on hardware requirement, prefer bigger m1,m2 values */
				क्रम (घड़ी.m1 = limit->m1.min; घड़ी.m1 <= limit->m1.max; घड़ी.m1++) अणु
					अचिन्हित पूर्णांक ppm;

					घड़ी.m2 = DIV_ROUND_CLOSEST(target * घड़ी.p * घड़ी.n,
								     refclk * घड़ी.m1);

					vlv_calc_dpll_params(refclk, &घड़ी);

					अगर (!पूर्णांकel_pll_is_valid(to_i915(dev),
								limit,
								&घड़ी))
						जारी;

					अगर (!vlv_PLL_is_optimal(dev, target,
								&घड़ी,
								best_घड़ी,
								bestppm, &ppm))
						जारी;

					*best_घड़ी = घड़ी;
					bestppm = ppm;
					found = true;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

/*
 * Returns a set of भागisors क्रम the desired target घड़ी with the given
 * refclk, or FALSE.  The वापसed values represent the घड़ी equation:
 * reflck * (5 * (m1 + 2) + (m2 + 2)) / (n + 2) / p1 / p2.
 */
अटल bool
chv_find_best_dpll(स्थिर काष्ठा पूर्णांकel_limit *limit,
		   काष्ठा पूर्णांकel_crtc_state *crtc_state,
		   पूर्णांक target, पूर्णांक refclk, काष्ठा dpll *match_घड़ी,
		   काष्ठा dpll *best_घड़ी)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_device *dev = crtc->base.dev;
	अचिन्हित पूर्णांक best_error_ppm;
	काष्ठा dpll घड़ी;
	u64 m2;
	पूर्णांक found = false;

	स_रखो(best_घड़ी, 0, माप(*best_घड़ी));
	best_error_ppm = 1000000;

	/*
	 * Based on hardware करोc, the n always set to 1, and m1 always
	 * set to 2.  If requires to support 200Mhz refclk, we need to
	 * revisit this because n may not 1 anymore.
	 */
	घड़ी.n = 1;
	घड़ी.m1 = 2;
	target *= 5;	/* fast घड़ी */

	क्रम (घड़ी.p1 = limit->p1.max; घड़ी.p1 >= limit->p1.min; घड़ी.p1--) अणु
		क्रम (घड़ी.p2 = limit->p2.p2_fast;
				घड़ी.p2 >= limit->p2.p2_slow;
				घड़ी.p2 -= घड़ी.p2 > 10 ? 2 : 1) अणु
			अचिन्हित पूर्णांक error_ppm;

			घड़ी.p = घड़ी.p1 * घड़ी.p2;

			m2 = DIV_ROUND_CLOSEST_ULL(mul_u32_u32(target, घड़ी.p * घड़ी.n) << 22,
						   refclk * घड़ी.m1);

			अगर (m2 > पूर्णांक_उच्च/घड़ी.m1)
				जारी;

			घड़ी.m2 = m2;

			chv_calc_dpll_params(refclk, &घड़ी);

			अगर (!पूर्णांकel_pll_is_valid(to_i915(dev), limit, &घड़ी))
				जारी;

			अगर (!vlv_PLL_is_optimal(dev, target, &घड़ी, best_घड़ी,
						best_error_ppm, &error_ppm))
				जारी;

			*best_घड़ी = घड़ी;
			best_error_ppm = error_ppm;
			found = true;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

bool bxt_find_best_dpll(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			काष्ठा dpll *best_घड़ी)
अणु
	पूर्णांक refclk = 100000;
	स्थिर काष्ठा पूर्णांकel_limit *limit = &पूर्णांकel_limits_bxt;

	वापस chv_find_best_dpll(limit, crtc_state,
				  crtc_state->port_घड़ी, refclk,
				  शून्य, best_घड़ी);
पूर्ण

अटल u32 pnv_dpll_compute_fp(काष्ठा dpll *dpll)
अणु
	वापस (1 << dpll->n) << 16 | dpll->m2;
पूर्ण

अटल व्योम i9xx_update_pll_भागiders(काष्ठा पूर्णांकel_crtc *crtc,
				     काष्ठा पूर्णांकel_crtc_state *crtc_state,
				     काष्ठा dpll *reduced_घड़ी)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 fp, fp2 = 0;

	अगर (IS_PINEVIEW(dev_priv)) अणु
		fp = pnv_dpll_compute_fp(&crtc_state->dpll);
		अगर (reduced_घड़ी)
			fp2 = pnv_dpll_compute_fp(reduced_घड़ी);
	पूर्ण अन्यथा अणु
		fp = i9xx_dpll_compute_fp(&crtc_state->dpll);
		अगर (reduced_घड़ी)
			fp2 = i9xx_dpll_compute_fp(reduced_घड़ी);
	पूर्ण

	crtc_state->dpll_hw_state.fp0 = fp;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS) &&
	    reduced_घड़ी) अणु
		crtc_state->dpll_hw_state.fp1 = fp2;
	पूर्ण अन्यथा अणु
		crtc_state->dpll_hw_state.fp1 = fp;
	पूर्ण
पूर्ण

अटल व्योम i9xx_compute_dpll(काष्ठा पूर्णांकel_crtc *crtc,
			      काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      काष्ठा dpll *reduced_घड़ी)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 dpll;
	काष्ठा dpll *घड़ी = &crtc_state->dpll;

	i9xx_update_pll_भागiders(crtc, crtc_state, reduced_घड़ी);

	dpll = DPLL_VGA_MODE_DIS;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS))
		dpll |= DPLLB_MODE_LVDS;
	अन्यथा
		dpll |= DPLLB_MODE_DAC_SERIAL;

	अगर (IS_I945G(dev_priv) || IS_I945GM(dev_priv) ||
	    IS_G33(dev_priv) || IS_PINEVIEW(dev_priv)) अणु
		dpll |= (crtc_state->pixel_multiplier - 1)
			<< SDVO_MULTIPLIER_SHIFT_HIRES;
	पूर्ण

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_SDVO) ||
	    पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		dpll |= DPLL_SDVO_HIGH_SPEED;

	अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state))
		dpll |= DPLL_SDVO_HIGH_SPEED;

	/* compute biपंचांगask from p1 value */
	अगर (IS_PINEVIEW(dev_priv))
		dpll |= (1 << (घड़ी->p1 - 1)) << DPLL_FPA01_P1_POST_DIV_SHIFT_PINEVIEW;
	अन्यथा अणु
		dpll |= (1 << (घड़ी->p1 - 1)) << DPLL_FPA01_P1_POST_DIV_SHIFT;
		अगर (IS_G4X(dev_priv) && reduced_घड़ी)
			dpll |= (1 << (reduced_घड़ी->p1 - 1)) << DPLL_FPA1_P1_POST_DIV_SHIFT;
	पूर्ण
	चयन (घड़ी->p2) अणु
	हाल 5:
		dpll |= DPLL_DAC_SERIAL_P2_CLOCK_DIV_5;
		अवरोध;
	हाल 7:
		dpll |= DPLLB_LVDS_P2_CLOCK_DIV_7;
		अवरोध;
	हाल 10:
		dpll |= DPLL_DAC_SERIAL_P2_CLOCK_DIV_10;
		अवरोध;
	हाल 14:
		dpll |= DPLLB_LVDS_P2_CLOCK_DIV_14;
		अवरोध;
	पूर्ण
	अगर (DISPLAY_VER(dev_priv) >= 4)
		dpll |= (6 << PLL_LOAD_PULSE_PHASE_SHIFT);

	अगर (crtc_state->sdvo_tv_घड़ी)
		dpll |= PLL_REF_INPUT_TVCLKINBC;
	अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS) &&
		 पूर्णांकel_panel_use_ssc(dev_priv))
		dpll |= PLLB_REF_INPUT_SPREADSPECTRUMIN;
	अन्यथा
		dpll |= PLL_REF_INPUT_DREFCLK;

	dpll |= DPLL_VCO_ENABLE;
	crtc_state->dpll_hw_state.dpll = dpll;

	अगर (DISPLAY_VER(dev_priv) >= 4) अणु
		u32 dpll_md = (crtc_state->pixel_multiplier - 1)
			<< DPLL_MD_UDI_MULTIPLIER_SHIFT;
		crtc_state->dpll_hw_state.dpll_md = dpll_md;
	पूर्ण
पूर्ण

अटल व्योम i8xx_compute_dpll(काष्ठा पूर्णांकel_crtc *crtc,
			      काष्ठा पूर्णांकel_crtc_state *crtc_state,
			      काष्ठा dpll *reduced_घड़ी)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 dpll;
	काष्ठा dpll *घड़ी = &crtc_state->dpll;

	i9xx_update_pll_भागiders(crtc, crtc_state, reduced_घड़ी);

	dpll = DPLL_VGA_MODE_DIS;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS)) अणु
		dpll |= (1 << (घड़ी->p1 - 1)) << DPLL_FPA01_P1_POST_DIV_SHIFT;
	पूर्ण अन्यथा अणु
		अगर (घड़ी->p1 == 2)
			dpll |= PLL_P1_DIVIDE_BY_TWO;
		अन्यथा
			dpll |= (घड़ी->p1 - 2) << DPLL_FPA01_P1_POST_DIV_SHIFT;
		अगर (घड़ी->p2 == 4)
			dpll |= PLL_P2_DIVIDE_BY_4;
	पूर्ण

	/*
	 * Bspec:
	 * "[Almaकरोr Errataपूर्ण: For the correct operation of the muxed DVO pins
	 *  (GDEVSELB/I2Cdata, GIRDBY/I2CClk) and (GFRAMEB/DVI_Data,
	 *  GTRDYB/DVI_Clk): Bit 31 (DPLL VCO Enable) and Bit 30 (2X Clock
	 *  Enable) must be set to ै 1ै  in both the DPLL A Control Register
	 *  (06014h-06017h) and DPLL B Control Register (06018h-0601Bh)."
	 *
	 * For simplicity We simply keep both bits always enabled in
	 * both DPLLS. The spec says we should disable the DVO 2X घड़ी
	 * when not needed, but this seems to work fine in practice.
	 */
	अगर (IS_I830(dev_priv) ||
	    पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DVO))
		dpll |= DPLL_DVO_2X_MODE;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS) &&
	    पूर्णांकel_panel_use_ssc(dev_priv))
		dpll |= PLLB_REF_INPUT_SPREADSPECTRUMIN;
	अन्यथा
		dpll |= PLL_REF_INPUT_DREFCLK;

	dpll |= DPLL_VCO_ENABLE;
	crtc_state->dpll_hw_state.dpll = dpll;
पूर्ण

अटल पूर्णांक hsw_crtc_compute_घड़ी(काष्ठा पूर्णांकel_crtc *crtc,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(crtc_state->uapi.state);

	अगर (!पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DSI) ||
	    DISPLAY_VER(dev_priv) >= 11) अणु
		काष्ठा पूर्णांकel_encoder *encoder =
			पूर्णांकel_get_crtc_new_encoder(state, crtc_state);

		अगर (!पूर्णांकel_reserve_shared_dplls(state, crtc, encoder)) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "failed to find PLL for pipe %c\n",
				    pipe_name(crtc->pipe));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ilk_needs_fb_cb_tune(काष्ठा dpll *dpll, पूर्णांक factor)
अणु
	वापस i9xx_dpll_compute_m(dpll) < factor * dpll->n;
पूर्ण


अटल व्योम ilk_compute_dpll(काष्ठा पूर्णांकel_crtc *crtc,
			     काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     काष्ठा dpll *reduced_घड़ी)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 dpll, fp, fp2;
	पूर्णांक factor;

	/* Enable स्वतःtuning of the PLL घड़ी (अगर permissible) */
	factor = 21;
	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS)) अणु
		अगर ((पूर्णांकel_panel_use_ssc(dev_priv) &&
		     dev_priv->vbt.lvds_ssc_freq == 100000) ||
		    (HAS_PCH_IBX(dev_priv) &&
		     पूर्णांकel_is_dual_link_lvds(dev_priv)))
			factor = 25;
	पूर्ण अन्यथा अगर (crtc_state->sdvo_tv_घड़ी) अणु
		factor = 20;
	पूर्ण

	fp = i9xx_dpll_compute_fp(&crtc_state->dpll);

	अगर (ilk_needs_fb_cb_tune(&crtc_state->dpll, factor))
		fp |= FP_CB_TUNE;

	अगर (reduced_घड़ी) अणु
		fp2 = i9xx_dpll_compute_fp(reduced_घड़ी);

		अगर (reduced_घड़ी->m < factor * reduced_घड़ी->n)
			fp2 |= FP_CB_TUNE;
	पूर्ण अन्यथा अणु
		fp2 = fp;
	पूर्ण

	dpll = 0;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS))
		dpll |= DPLLB_MODE_LVDS;
	अन्यथा
		dpll |= DPLLB_MODE_DAC_SERIAL;

	dpll |= (crtc_state->pixel_multiplier - 1)
		<< PLL_REF_SDVO_HDMI_MULTIPLIER_SHIFT;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_SDVO) ||
	    पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		dpll |= DPLL_SDVO_HIGH_SPEED;

	अगर (पूर्णांकel_crtc_has_dp_encoder(crtc_state))
		dpll |= DPLL_SDVO_HIGH_SPEED;

	/*
	 * The high speed IO घड़ी is only really required क्रम
	 * SDVO/HDMI/DP, but we also enable it क्रम CRT to make it
	 * possible to share the DPLL between CRT and HDMI. Enabling
	 * the घड़ी needlessly करोes no real harm, except use up a
	 * bit of घातer potentially.
	 *
	 * We'll limit this to IVB with 3 pipes, since it has only two
	 * DPLLs and so DPLL sharing is the only way to get three pipes
	 * driving PCH ports at the same समय. On SNB we could करो this,
	 * and potentially aव्योम enabling the second DPLL, but it's not
	 * clear अगर it''s a win or loss घातer wise. No poपूर्णांक in करोing
	 * this on ILK at all since it has a fixed DPLL<->pipe mapping.
	 */
	अगर (INTEL_NUM_PIPES(dev_priv) == 3 &&
	    पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_ANALOG))
		dpll |= DPLL_SDVO_HIGH_SPEED;

	/* compute biपंचांगask from p1 value */
	dpll |= (1 << (crtc_state->dpll.p1 - 1)) << DPLL_FPA01_P1_POST_DIV_SHIFT;
	/* also FPA1 */
	dpll |= (1 << (crtc_state->dpll.p1 - 1)) << DPLL_FPA1_P1_POST_DIV_SHIFT;

	चयन (crtc_state->dpll.p2) अणु
	हाल 5:
		dpll |= DPLL_DAC_SERIAL_P2_CLOCK_DIV_5;
		अवरोध;
	हाल 7:
		dpll |= DPLLB_LVDS_P2_CLOCK_DIV_7;
		अवरोध;
	हाल 10:
		dpll |= DPLL_DAC_SERIAL_P2_CLOCK_DIV_10;
		अवरोध;
	हाल 14:
		dpll |= DPLLB_LVDS_P2_CLOCK_DIV_14;
		अवरोध;
	पूर्ण

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS) &&
	    पूर्णांकel_panel_use_ssc(dev_priv))
		dpll |= PLLB_REF_INPUT_SPREADSPECTRUMIN;
	अन्यथा
		dpll |= PLL_REF_INPUT_DREFCLK;

	dpll |= DPLL_VCO_ENABLE;

	crtc_state->dpll_hw_state.dpll = dpll;
	crtc_state->dpll_hw_state.fp0 = fp;
	crtc_state->dpll_hw_state.fp1 = fp2;
पूर्ण

अटल पूर्णांक ilk_crtc_compute_घड़ी(काष्ठा पूर्णांकel_crtc *crtc,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(crtc_state->uapi.state);
	स्थिर काष्ठा पूर्णांकel_limit *limit;
	पूर्णांक refclk = 120000;

	स_रखो(&crtc_state->dpll_hw_state, 0,
	       माप(crtc_state->dpll_hw_state));

	/* CPU eDP is the only output that करोesn't need a PCH PLL of its own. */
	अगर (!crtc_state->has_pch_encoder)
		वापस 0;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS)) अणु
		अगर (पूर्णांकel_panel_use_ssc(dev_priv)) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "using SSC reference clock of %d kHz\n",
				    dev_priv->vbt.lvds_ssc_freq);
			refclk = dev_priv->vbt.lvds_ssc_freq;
		पूर्ण

		अगर (पूर्णांकel_is_dual_link_lvds(dev_priv)) अणु
			अगर (refclk == 100000)
				limit = &ilk_limits_dual_lvds_100m;
			अन्यथा
				limit = &ilk_limits_dual_lvds;
		पूर्ण अन्यथा अणु
			अगर (refclk == 100000)
				limit = &ilk_limits_single_lvds_100m;
			अन्यथा
				limit = &ilk_limits_single_lvds;
		पूर्ण
	पूर्ण अन्यथा अणु
		limit = &ilk_limits_dac;
	पूर्ण

	अगर (!crtc_state->घड़ी_set &&
	    !g4x_find_best_dpll(limit, crtc_state, crtc_state->port_घड़ी,
				refclk, शून्य, &crtc_state->dpll)) अणु
		drm_err(&dev_priv->drm,
			"Couldn't find PLL settings for mode!\n");
		वापस -EINVAL;
	पूर्ण

	ilk_compute_dpll(crtc, crtc_state, शून्य);

	अगर (!पूर्णांकel_reserve_shared_dplls(state, crtc, शून्य)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "failed to find PLL for pipe %c\n",
			    pipe_name(crtc->pipe));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम vlv_compute_dpll(काष्ठा पूर्णांकel_crtc *crtc,
		      काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	pipe_config->dpll_hw_state.dpll = DPLL_INTEGRATED_REF_CLK_VLV |
		DPLL_REF_CLK_ENABLE_VLV | DPLL_VGA_MODE_DIS;
	अगर (crtc->pipe != PIPE_A)
		pipe_config->dpll_hw_state.dpll |= DPLL_INTEGRATED_CRI_CLK_VLV;

	/* DPLL not used with DSI, but still need the rest set up */
	अगर (!पूर्णांकel_crtc_has_type(pipe_config, INTEL_OUTPUT_DSI))
		pipe_config->dpll_hw_state.dpll |= DPLL_VCO_ENABLE |
			DPLL_EXT_BUFFER_ENABLE_VLV;

	pipe_config->dpll_hw_state.dpll_md =
		(pipe_config->pixel_multiplier - 1) << DPLL_MD_UDI_MULTIPLIER_SHIFT;
पूर्ण

व्योम chv_compute_dpll(काष्ठा पूर्णांकel_crtc *crtc,
		      काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	pipe_config->dpll_hw_state.dpll = DPLL_SSC_REF_CLK_CHV |
		DPLL_REF_CLK_ENABLE_VLV | DPLL_VGA_MODE_DIS;
	अगर (crtc->pipe != PIPE_A)
		pipe_config->dpll_hw_state.dpll |= DPLL_INTEGRATED_CRI_CLK_VLV;

	/* DPLL not used with DSI, but still need the rest set up */
	अगर (!पूर्णांकel_crtc_has_type(pipe_config, INTEL_OUTPUT_DSI))
		pipe_config->dpll_hw_state.dpll |= DPLL_VCO_ENABLE;

	pipe_config->dpll_hw_state.dpll_md =
		(pipe_config->pixel_multiplier - 1) << DPLL_MD_UDI_MULTIPLIER_SHIFT;
पूर्ण

अटल पूर्णांक chv_crtc_compute_घड़ी(काष्ठा पूर्णांकel_crtc *crtc,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांक refclk = 100000;
	स्थिर काष्ठा पूर्णांकel_limit *limit = &पूर्णांकel_limits_chv;
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc_state->uapi.crtc->dev);

	स_रखो(&crtc_state->dpll_hw_state, 0,
	       माप(crtc_state->dpll_hw_state));

	अगर (!crtc_state->घड़ी_set &&
	    !chv_find_best_dpll(limit, crtc_state, crtc_state->port_घड़ी,
				refclk, शून्य, &crtc_state->dpll)) अणु
		drm_err(&i915->drm, "Couldn't find PLL settings for mode!\n");
		वापस -EINVAL;
	पूर्ण

	chv_compute_dpll(crtc, crtc_state);

	वापस 0;
पूर्ण

अटल पूर्णांक vlv_crtc_compute_घड़ी(काष्ठा पूर्णांकel_crtc *crtc,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांक refclk = 100000;
	स्थिर काष्ठा पूर्णांकel_limit *limit = &पूर्णांकel_limits_vlv;
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc_state->uapi.crtc->dev);

	स_रखो(&crtc_state->dpll_hw_state, 0,
	       माप(crtc_state->dpll_hw_state));

	अगर (!crtc_state->घड़ी_set &&
	    !vlv_find_best_dpll(limit, crtc_state, crtc_state->port_घड़ी,
				refclk, शून्य, &crtc_state->dpll)) अणु
		drm_err(&i915->drm,  "Couldn't find PLL settings for mode!\n");
		वापस -EINVAL;
	पूर्ण

	vlv_compute_dpll(crtc, crtc_state);

	वापस 0;
पूर्ण

अटल पूर्णांक g4x_crtc_compute_घड़ी(काष्ठा पूर्णांकel_crtc *crtc,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_limit *limit;
	पूर्णांक refclk = 96000;

	स_रखो(&crtc_state->dpll_hw_state, 0,
	       माप(crtc_state->dpll_hw_state));

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS)) अणु
		अगर (पूर्णांकel_panel_use_ssc(dev_priv)) अणु
			refclk = dev_priv->vbt.lvds_ssc_freq;
			drm_dbg_kms(&dev_priv->drm,
				    "using SSC reference clock of %d kHz\n",
				    refclk);
		पूर्ण

		अगर (पूर्णांकel_is_dual_link_lvds(dev_priv))
			limit = &पूर्णांकel_limits_g4x_dual_channel_lvds;
		अन्यथा
			limit = &पूर्णांकel_limits_g4x_single_channel_lvds;
	पूर्ण अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI) ||
		   पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_ANALOG)) अणु
		limit = &पूर्णांकel_limits_g4x_hdmi;
	पूर्ण अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_SDVO)) अणु
		limit = &पूर्णांकel_limits_g4x_sdvo;
	पूर्ण अन्यथा अणु
		/* The option is क्रम other outमाला_दो */
		limit = &पूर्णांकel_limits_i9xx_sdvo;
	पूर्ण

	अगर (!crtc_state->घड़ी_set &&
	    !g4x_find_best_dpll(limit, crtc_state, crtc_state->port_घड़ी,
				refclk, शून्य, &crtc_state->dpll)) अणु
		drm_err(&dev_priv->drm,
			"Couldn't find PLL settings for mode!\n");
		वापस -EINVAL;
	पूर्ण

	i9xx_compute_dpll(crtc, crtc_state, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक pnv_crtc_compute_घड़ी(काष्ठा पूर्णांकel_crtc *crtc,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	स्थिर काष्ठा पूर्णांकel_limit *limit;
	पूर्णांक refclk = 96000;

	स_रखो(&crtc_state->dpll_hw_state, 0,
	       माप(crtc_state->dpll_hw_state));

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS)) अणु
		अगर (पूर्णांकel_panel_use_ssc(dev_priv)) अणु
			refclk = dev_priv->vbt.lvds_ssc_freq;
			drm_dbg_kms(&dev_priv->drm,
				    "using SSC reference clock of %d kHz\n",
				    refclk);
		पूर्ण

		limit = &pnv_limits_lvds;
	पूर्ण अन्यथा अणु
		limit = &pnv_limits_sdvo;
	पूर्ण

	अगर (!crtc_state->घड़ी_set &&
	    !pnv_find_best_dpll(limit, crtc_state, crtc_state->port_घड़ी,
				refclk, शून्य, &crtc_state->dpll)) अणु
		drm_err(&dev_priv->drm,
			"Couldn't find PLL settings for mode!\n");
		वापस -EINVAL;
	पूर्ण

	i9xx_compute_dpll(crtc, crtc_state, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक i9xx_crtc_compute_घड़ी(काष्ठा पूर्णांकel_crtc *crtc,
				   काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	स्थिर काष्ठा पूर्णांकel_limit *limit;
	पूर्णांक refclk = 96000;

	स_रखो(&crtc_state->dpll_hw_state, 0,
	       माप(crtc_state->dpll_hw_state));

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS)) अणु
		अगर (पूर्णांकel_panel_use_ssc(dev_priv)) अणु
			refclk = dev_priv->vbt.lvds_ssc_freq;
			drm_dbg_kms(&dev_priv->drm,
				    "using SSC reference clock of %d kHz\n",
				    refclk);
		पूर्ण

		limit = &पूर्णांकel_limits_i9xx_lvds;
	पूर्ण अन्यथा अणु
		limit = &पूर्णांकel_limits_i9xx_sdvo;
	पूर्ण

	अगर (!crtc_state->घड़ी_set &&
	    !i9xx_find_best_dpll(limit, crtc_state, crtc_state->port_घड़ी,
				 refclk, शून्य, &crtc_state->dpll)) अणु
		drm_err(&dev_priv->drm,
			"Couldn't find PLL settings for mode!\n");
		वापस -EINVAL;
	पूर्ण

	i9xx_compute_dpll(crtc, crtc_state, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक i8xx_crtc_compute_घड़ी(काष्ठा पूर्णांकel_crtc *crtc,
				   काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	स्थिर काष्ठा पूर्णांकel_limit *limit;
	पूर्णांक refclk = 48000;

	स_रखो(&crtc_state->dpll_hw_state, 0,
	       माप(crtc_state->dpll_hw_state));

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_LVDS)) अणु
		अगर (पूर्णांकel_panel_use_ssc(dev_priv)) अणु
			refclk = dev_priv->vbt.lvds_ssc_freq;
			drm_dbg_kms(&dev_priv->drm,
				    "using SSC reference clock of %d kHz\n",
				    refclk);
		पूर्ण

		limit = &पूर्णांकel_limits_i8xx_lvds;
	पूर्ण अन्यथा अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DVO)) अणु
		limit = &पूर्णांकel_limits_i8xx_dvo;
	पूर्ण अन्यथा अणु
		limit = &पूर्णांकel_limits_i8xx_dac;
	पूर्ण

	अगर (!crtc_state->घड़ी_set &&
	    !i9xx_find_best_dpll(limit, crtc_state, crtc_state->port_घड़ी,
				 refclk, शून्य, &crtc_state->dpll)) अणु
		drm_err(&dev_priv->drm,
			"Couldn't find PLL settings for mode!\n");
		वापस -EINVAL;
	पूर्ण

	i8xx_compute_dpll(crtc, crtc_state, शून्य);

	वापस 0;
पूर्ण

व्योम
पूर्णांकel_dpll_init_घड़ी_hook(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 9 || HAS_DDI(dev_priv))
		dev_priv->display.crtc_compute_घड़ी = hsw_crtc_compute_घड़ी;
	अन्यथा अगर (HAS_PCH_SPLIT(dev_priv))
		dev_priv->display.crtc_compute_घड़ी = ilk_crtc_compute_घड़ी;
	अन्यथा अगर (IS_CHERRYVIEW(dev_priv))
		dev_priv->display.crtc_compute_घड़ी = chv_crtc_compute_घड़ी;
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
		dev_priv->display.crtc_compute_घड़ी = vlv_crtc_compute_घड़ी;
	अन्यथा अगर (IS_G4X(dev_priv))
		dev_priv->display.crtc_compute_घड़ी = g4x_crtc_compute_घड़ी;
	अन्यथा अगर (IS_PINEVIEW(dev_priv))
		dev_priv->display.crtc_compute_घड़ी = pnv_crtc_compute_घड़ी;
	अन्यथा अगर (!IS_DISPLAY_VER(dev_priv, 2))
		dev_priv->display.crtc_compute_घड़ी = i9xx_crtc_compute_घड़ी;
	अन्यथा
		dev_priv->display.crtc_compute_घड़ी = i8xx_crtc_compute_घड़ी;
पूर्ण

अटल bool i9xx_has_pps(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (IS_I830(dev_priv))
		वापस false;

	वापस IS_PINEVIEW(dev_priv) || IS_MOBILE(dev_priv);
पूर्ण

व्योम i9xx_enable_pll(काष्ठा पूर्णांकel_crtc *crtc,
		     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	i915_reg_t reg = DPLL(crtc->pipe);
	u32 dpll = crtc_state->dpll_hw_state.dpll;
	पूर्णांक i;

	निश्चित_pipe_disabled(dev_priv, crtc_state->cpu_transcoder);

	/* PLL is रक्षित by panel, make sure we can ग_लिखो it */
	अगर (i9xx_has_pps(dev_priv))
		निश्चित_panel_unlocked(dev_priv, crtc->pipe);

	/*
	 * Apparently we need to have VGA mode enabled prior to changing
	 * the P1/P2 भागiders. Otherwise the DPLL will keep using the old
	 * भागiders, even though the रेजिस्टर value करोes change.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, dpll & ~DPLL_VGA_MODE_DIS);
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, dpll);

	/* Wait क्रम the घड़ीs to stabilize. */
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	udelay(150);

	अगर (DISPLAY_VER(dev_priv) >= 4) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DPLL_MD(crtc->pipe),
			       crtc_state->dpll_hw_state.dpll_md);
	पूर्ण अन्यथा अणु
		/* The pixel multiplier can only be updated once the
		 * DPLL is enabled and the घड़ीs are stable.
		 *
		 * So ग_लिखो it again.
		 */
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, dpll);
	पूर्ण

	/* We करो this three बार क्रम luck */
	क्रम (i = 0; i < 3; i++) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, dpll);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
		udelay(150); /* रुको क्रम warmup */
	पूर्ण
पूर्ण

अटल व्योम vlv_pllb_recal_opamp(काष्ठा drm_i915_निजी *dev_priv,
				 क्रमागत pipe pipe)
अणु
	u32 reg_val;

	/*
	 * PLLB opamp always calibrates to max value of 0x3f, क्रमce enable it
	 * and set it to a reasonable value instead.
	 */
	reg_val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PLL_DW9(1));
	reg_val &= 0xffffff00;
	reg_val |= 0x00000030;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW9(1), reg_val);

	reg_val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_REF_DW13);
	reg_val &= 0x00ffffff;
	reg_val |= 0x8c000000;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_REF_DW13, reg_val);

	reg_val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PLL_DW9(1));
	reg_val &= 0xffffff00;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW9(1), reg_val);

	reg_val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_REF_DW13);
	reg_val &= 0x00ffffff;
	reg_val |= 0xb0000000;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_REF_DW13, reg_val);
पूर्ण

अटल व्योम _vlv_enable_pll(काष्ठा पूर्णांकel_crtc *crtc,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe), pipe_config->dpll_hw_state.dpll);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DPLL(pipe));
	udelay(150);

	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, DPLL(pipe), DPLL_LOCK_VLV, 1))
		drm_err(&dev_priv->drm, "DPLL %d failed to lock\n", pipe);
पूर्ण

व्योम vlv_enable_pll(काष्ठा पूर्णांकel_crtc *crtc,
		    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	निश्चित_pipe_disabled(dev_priv, pipe_config->cpu_transcoder);

	/* PLL is रक्षित by panel, make sure we can ग_लिखो it */
	निश्चित_panel_unlocked(dev_priv, pipe);

	अगर (pipe_config->dpll_hw_state.dpll & DPLL_VCO_ENABLE)
		_vlv_enable_pll(crtc, pipe_config);

	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL_MD(pipe),
		       pipe_config->dpll_hw_state.dpll_md);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DPLL_MD(pipe));
पूर्ण


अटल व्योम _chv_enable_pll(काष्ठा पूर्णांकel_crtc *crtc,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	क्रमागत dpio_channel port = vlv_pipe_to_channel(pipe);
	u32 पंचांगp;

	vlv_dpio_get(dev_priv);

	/* Enable back the 10bit घड़ी to display controller */
	पंचांगp = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_CMN_DW14(port));
	पंचांगp |= DPIO_DCLKP_EN;
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_CMN_DW14(port), पंचांगp);

	vlv_dpio_put(dev_priv);

	/*
	 * Need to रुको > 100ns between dclkp घड़ी enable bit and PLL enable.
	 */
	udelay(1);

	/* Enable PLL */
	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe), pipe_config->dpll_hw_state.dpll);

	/* Check PLL is locked */
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, DPLL(pipe), DPLL_LOCK_VLV, 1))
		drm_err(&dev_priv->drm, "PLL %d failed to lock\n", pipe);
पूर्ण

व्योम chv_enable_pll(काष्ठा पूर्णांकel_crtc *crtc,
		    स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	निश्चित_pipe_disabled(dev_priv, pipe_config->cpu_transcoder);

	/* PLL is रक्षित by panel, make sure we can ग_लिखो it */
	निश्चित_panel_unlocked(dev_priv, pipe);

	अगर (pipe_config->dpll_hw_state.dpll & DPLL_VCO_ENABLE)
		_chv_enable_pll(crtc, pipe_config);

	अगर (pipe != PIPE_A) अणु
		/*
		 * WaPixelRepeatModeFixForC0:chv
		 *
		 * DPLLCMD is AWOL. Use chicken bits to propagate
		 * the value from DPLLBMD to either pipe B or C.
		 */
		पूर्णांकel_de_ग_लिखो(dev_priv, CBR4_VLV, CBR_DPLLBMD_PIPE(pipe));
		पूर्णांकel_de_ग_लिखो(dev_priv, DPLL_MD(PIPE_B),
			       pipe_config->dpll_hw_state.dpll_md);
		पूर्णांकel_de_ग_लिखो(dev_priv, CBR4_VLV, 0);
		dev_priv->chv_dpll_md[pipe] = pipe_config->dpll_hw_state.dpll_md;

		/*
		 * DPLLB VGA mode also seems to cause problems.
		 * We should always have it disabled.
		 */
		drm_WARN_ON(&dev_priv->drm,
			    (पूर्णांकel_de_पढ़ो(dev_priv, DPLL(PIPE_B)) &
			     DPLL_VGA_MODE_DIS) == 0);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DPLL_MD(pipe),
			       pipe_config->dpll_hw_state.dpll_md);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, DPLL_MD(pipe));
	पूर्ण
पूर्ण

व्योम vlv_prepare_pll(काष्ठा पूर्णांकel_crtc *crtc,
		     स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 mभाग;
	u32 bestn, besपंचांग1, besपंचांग2, bestp1, bestp2;
	u32 coreclk, reg_val;

	/* Enable Refclk */
	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe),
		       pipe_config->dpll_hw_state.dpll & ~(DPLL_VCO_ENABLE | DPLL_EXT_BUFFER_ENABLE_VLV));

	/* No need to actually set up the DPLL with DSI */
	अगर ((pipe_config->dpll_hw_state.dpll & DPLL_VCO_ENABLE) == 0)
		वापस;

	vlv_dpio_get(dev_priv);

	bestn = pipe_config->dpll.n;
	besपंचांग1 = pipe_config->dpll.m1;
	besपंचांग2 = pipe_config->dpll.m2;
	bestp1 = pipe_config->dpll.p1;
	bestp2 = pipe_config->dpll.p2;

	/* See eDP HDMI DPIO driver vbios notes करोc */

	/* PLL B needs special handling */
	अगर (pipe == PIPE_B)
		vlv_pllb_recal_opamp(dev_priv, pipe);

	/* Set up Tx target क्रम periodic Rcomp update */
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW9_BCAST, 0x0100000f);

	/* Disable target IRef on PLL */
	reg_val = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PLL_DW8(pipe));
	reg_val &= 0x00ffffff;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW8(pipe), reg_val);

	/* Disable fast lock */
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_CMN_DW0, 0x610);

	/* Set idtafcrecal beक्रमe PLL is enabled */
	mभाग = ((besपंचांग1 << DPIO_M1DIV_SHIFT) | (besपंचांग2 & DPIO_M2DIV_MASK));
	mभाग |= ((bestp1 << DPIO_P1_SHIFT) | (bestp2 << DPIO_P2_SHIFT));
	mभाग |= ((bestn << DPIO_N_SHIFT));
	mभाग |= (1 << DPIO_K_SHIFT);

	/*
	 * Post भागider depends on pixel घड़ी rate, DAC vs digital (and LVDS,
	 * but we करोn't support that).
	 * Note: करोn't use the DAC post भागider as it seems unstable.
	 */
	mभाग |= (DPIO_POST_DIV_HDMIDP << DPIO_POST_DIV_SHIFT);
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW3(pipe), mभाग);

	mभाग |= DPIO_ENABLE_CALIBRATION;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW3(pipe), mभाग);

	/* Set HBR and RBR LPF coefficients */
	अगर (pipe_config->port_घड़ी == 162000 ||
	    पूर्णांकel_crtc_has_type(pipe_config, INTEL_OUTPUT_ANALOG) ||
	    पूर्णांकel_crtc_has_type(pipe_config, INTEL_OUTPUT_HDMI))
		vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW10(pipe),
				 0x009f0003);
	अन्यथा
		vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW10(pipe),
				 0x00d0000f);

	अगर (पूर्णांकel_crtc_has_dp_encoder(pipe_config)) अणु
		/* Use SSC source */
		अगर (pipe == PIPE_A)
			vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW5(pipe),
					 0x0df40000);
		अन्यथा
			vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW5(pipe),
					 0x0df70000);
	पूर्ण अन्यथा अणु /* HDMI or VGA */
		/* Use bend source */
		अगर (pipe == PIPE_A)
			vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW5(pipe),
					 0x0df70000);
		अन्यथा
			vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW5(pipe),
					 0x0df40000);
	पूर्ण

	coreclk = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PLL_DW7(pipe));
	coreclk = (coreclk & 0x0000ff00) | 0x01c00000;
	अगर (पूर्णांकel_crtc_has_dp_encoder(pipe_config))
		coreclk |= 0x01000000;
	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW7(pipe), coreclk);

	vlv_dpio_ग_लिखो(dev_priv, pipe, VLV_PLL_DW11(pipe), 0x87871000);

	vlv_dpio_put(dev_priv);
पूर्ण

व्योम chv_prepare_pll(काष्ठा पूर्णांकel_crtc *crtc,
		     स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = crtc->pipe;
	क्रमागत dpio_channel port = vlv_pipe_to_channel(pipe);
	u32 loopfilter, tribuf_calcntr;
	u32 bestn, besपंचांग1, besपंचांग2, bestp1, bestp2, besपंचांग2_frac;
	u32 dpio_val;
	पूर्णांक vco;

	/* Enable Refclk and SSC */
	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe),
		       pipe_config->dpll_hw_state.dpll & ~DPLL_VCO_ENABLE);

	/* No need to actually set up the DPLL with DSI */
	अगर ((pipe_config->dpll_hw_state.dpll & DPLL_VCO_ENABLE) == 0)
		वापस;

	bestn = pipe_config->dpll.n;
	besपंचांग2_frac = pipe_config->dpll.m2 & 0x3fffff;
	besपंचांग1 = pipe_config->dpll.m1;
	besपंचांग2 = pipe_config->dpll.m2 >> 22;
	bestp1 = pipe_config->dpll.p1;
	bestp2 = pipe_config->dpll.p2;
	vco = pipe_config->dpll.vco;
	dpio_val = 0;
	loopfilter = 0;

	vlv_dpio_get(dev_priv);

	/* p1 and p2 भागider */
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_CMN_DW13(port),
			5 << DPIO_CHV_S1_DIV_SHIFT |
			bestp1 << DPIO_CHV_P1_DIV_SHIFT |
			bestp2 << DPIO_CHV_P2_DIV_SHIFT |
			1 << DPIO_CHV_K_DIV_SHIFT);

	/* Feedback post-भागider - m2 */
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_PLL_DW0(port), besपंचांग2);

	/* Feedback refclk भागider - n and m1 */
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_PLL_DW1(port),
			DPIO_CHV_M1_DIV_BY_2 |
			1 << DPIO_CHV_N_DIV_SHIFT);

	/* M2 fraction भागision */
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_PLL_DW2(port), besपंचांग2_frac);

	/* M2 fraction भागision enable */
	dpio_val = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_PLL_DW3(port));
	dpio_val &= ~(DPIO_CHV_FEEDFWD_GAIN_MASK | DPIO_CHV_FRAC_DIV_EN);
	dpio_val |= (2 << DPIO_CHV_FEEDFWD_GAIN_SHIFT);
	अगर (besपंचांग2_frac)
		dpio_val |= DPIO_CHV_FRAC_DIV_EN;
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_PLL_DW3(port), dpio_val);

	/* Program digital lock detect threshold */
	dpio_val = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_PLL_DW9(port));
	dpio_val &= ~(DPIO_CHV_INT_LOCK_THRESHOLD_MASK |
					DPIO_CHV_INT_LOCK_THRESHOLD_SEL_COARSE);
	dpio_val |= (0x5 << DPIO_CHV_INT_LOCK_THRESHOLD_SHIFT);
	अगर (!besपंचांग2_frac)
		dpio_val |= DPIO_CHV_INT_LOCK_THRESHOLD_SEL_COARSE;
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_PLL_DW9(port), dpio_val);

	/* Loop filter */
	अगर (vco == 5400000) अणु
		loopfilter |= (0x3 << DPIO_CHV_PROP_COEFF_SHIFT);
		loopfilter |= (0x8 << DPIO_CHV_INT_COEFF_SHIFT);
		loopfilter |= (0x1 << DPIO_CHV_GAIN_CTRL_SHIFT);
		tribuf_calcntr = 0x9;
	पूर्ण अन्यथा अगर (vco <= 6200000) अणु
		loopfilter |= (0x5 << DPIO_CHV_PROP_COEFF_SHIFT);
		loopfilter |= (0xB << DPIO_CHV_INT_COEFF_SHIFT);
		loopfilter |= (0x3 << DPIO_CHV_GAIN_CTRL_SHIFT);
		tribuf_calcntr = 0x9;
	पूर्ण अन्यथा अगर (vco <= 6480000) अणु
		loopfilter |= (0x4 << DPIO_CHV_PROP_COEFF_SHIFT);
		loopfilter |= (0x9 << DPIO_CHV_INT_COEFF_SHIFT);
		loopfilter |= (0x3 << DPIO_CHV_GAIN_CTRL_SHIFT);
		tribuf_calcntr = 0x8;
	पूर्ण अन्यथा अणु
		/* Not supported. Apply the same limits as in the max हाल */
		loopfilter |= (0x4 << DPIO_CHV_PROP_COEFF_SHIFT);
		loopfilter |= (0x9 << DPIO_CHV_INT_COEFF_SHIFT);
		loopfilter |= (0x3 << DPIO_CHV_GAIN_CTRL_SHIFT);
		tribuf_calcntr = 0;
	पूर्ण
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_PLL_DW6(port), loopfilter);

	dpio_val = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_PLL_DW8(port));
	dpio_val &= ~DPIO_CHV_TDC_TARGET_CNT_MASK;
	dpio_val |= (tribuf_calcntr << DPIO_CHV_TDC_TARGET_CNT_SHIFT);
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_PLL_DW8(port), dpio_val);

	/* AFC Recal */
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_CMN_DW14(port),
			vlv_dpio_पढ़ो(dev_priv, pipe, CHV_CMN_DW14(port)) |
			DPIO_AFC_RECAL);

	vlv_dpio_put(dev_priv);
पूर्ण

/**
 * vlv_क्रमce_pll_on - क्रमcibly enable just the PLL
 * @dev_priv: i915 निजी काष्ठाure
 * @pipe: pipe PLL to enable
 * @dpll: PLL configuration
 *
 * Enable the PLL क्रम @pipe using the supplied @dpll config. To be used
 * in हालs where we need the PLL enabled even when @pipe is not going to
 * be enabled.
 */
पूर्णांक vlv_क्रमce_pll_on(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe,
		     स्थिर काष्ठा dpll *dpll)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);
	काष्ठा पूर्णांकel_crtc_state *pipe_config;

	pipe_config = पूर्णांकel_crtc_state_alloc(crtc);
	अगर (!pipe_config)
		वापस -ENOMEM;

	pipe_config->cpu_transcoder = (क्रमागत transcoder)pipe;
	pipe_config->pixel_multiplier = 1;
	pipe_config->dpll = *dpll;

	अगर (IS_CHERRYVIEW(dev_priv)) अणु
		chv_compute_dpll(crtc, pipe_config);
		chv_prepare_pll(crtc, pipe_config);
		chv_enable_pll(crtc, pipe_config);
	पूर्ण अन्यथा अणु
		vlv_compute_dpll(crtc, pipe_config);
		vlv_prepare_pll(crtc, pipe_config);
		vlv_enable_pll(crtc, pipe_config);
	पूर्ण

	kमुक्त(pipe_config);

	वापस 0;
पूर्ण

व्योम vlv_disable_pll(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	u32 val;

	/* Make sure the pipe isn't still relying on us */
	निश्चित_pipe_disabled(dev_priv, (क्रमागत transcoder)pipe);

	val = DPLL_INTEGRATED_REF_CLK_VLV |
		DPLL_REF_CLK_ENABLE_VLV | DPLL_VGA_MODE_DIS;
	अगर (pipe != PIPE_A)
		val |= DPLL_INTEGRATED_CRI_CLK_VLV;

	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe), val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DPLL(pipe));
पूर्ण

व्योम chv_disable_pll(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	क्रमागत dpio_channel port = vlv_pipe_to_channel(pipe);
	u32 val;

	/* Make sure the pipe isn't still relying on us */
	निश्चित_pipe_disabled(dev_priv, (क्रमागत transcoder)pipe);

	val = DPLL_SSC_REF_CLK_CHV |
		DPLL_REF_CLK_ENABLE_VLV | DPLL_VGA_MODE_DIS;
	अगर (pipe != PIPE_A)
		val |= DPLL_INTEGRATED_CRI_CLK_VLV;

	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe), val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DPLL(pipe));

	vlv_dpio_get(dev_priv);

	/* Disable 10bit घड़ी to display controller */
	val = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_CMN_DW14(port));
	val &= ~DPIO_DCLKP_EN;
	vlv_dpio_ग_लिखो(dev_priv, pipe, CHV_CMN_DW14(port), val);

	vlv_dpio_put(dev_priv);
पूर्ण

व्योम i9xx_disable_pll(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	/* Don't disable pipe or pipe PLLs अगर needed */
	अगर (IS_I830(dev_priv))
		वापस;

	/* Make sure the pipe isn't still relying on us */
	निश्चित_pipe_disabled(dev_priv, crtc_state->cpu_transcoder);

	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe), DPLL_VGA_MODE_DIS);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DPLL(pipe));
पूर्ण


/**
 * vlv_क्रमce_pll_off - क्रमcibly disable just the PLL
 * @dev_priv: i915 निजी काष्ठाure
 * @pipe: pipe PLL to disable
 *
 * Disable the PLL क्रम @pipe. To be used in हालs where we need
 * the PLL enabled even when @pipe is not going to be enabled.
 */
व्योम vlv_क्रमce_pll_off(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	अगर (IS_CHERRYVIEW(dev_priv))
		chv_disable_pll(dev_priv, pipe);
	अन्यथा
		vlv_disable_pll(dev_priv, pipe);
पूर्ण
