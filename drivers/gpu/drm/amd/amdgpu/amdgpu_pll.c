<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "atom.h"
#समावेश "atombios_encoders.h"
#समावेश "amdgpu_pll.h"
#समावेश <यंत्र/भाग64.h>
#समावेश <linux/gcd.h>

/**
 * amdgpu_pll_reduce_ratio - fractional number reduction
 *
 * @nom: nominator
 * @den: denominator
 * @nom_min: minimum value क्रम nominator
 * @den_min: minimum value क्रम denominator
 *
 * Find the greatest common भागisor and apply it on both nominator and
 * denominator, but make nominator and denominator are at least as large
 * as their minimum values.
 */
अटल व्योम amdgpu_pll_reduce_ratio(अचिन्हित *nom, अचिन्हित *den,
				    अचिन्हित nom_min, अचिन्हित den_min)
अणु
	अचिन्हित पंचांगp;

	/* reduce the numbers to a simpler ratio */
	पंचांगp = gcd(*nom, *den);
	*nom /= पंचांगp;
	*den /= पंचांगp;

	/* make sure nominator is large enough */
	अगर (*nom < nom_min) अणु
		पंचांगp = DIV_ROUND_UP(nom_min, *nom);
		*nom *= पंचांगp;
		*den *= पंचांगp;
	पूर्ण

	/* make sure the denominator is large enough */
	अगर (*den < den_min) अणु
		पंचांगp = DIV_ROUND_UP(den_min, *den);
		*nom *= पंचांगp;
		*den *= पंचांगp;
	पूर्ण
पूर्ण

/**
 * amdgpu_pll_get_fb_ref_भाग - feedback and ref भागider calculation
 *
 * @nom: nominator
 * @den: denominator
 * @post_भाग: post भागider
 * @fb_भाग_max: feedback भागider maximum
 * @ref_भाग_max: reference भागider maximum
 * @fb_भाग: resulting feedback भागider
 * @ref_भाग: resulting reference भागider
 *
 * Calculate feedback and reference भागider क्रम a given post भागider. Makes
 * sure we stay within the limits.
 */
अटल व्योम amdgpu_pll_get_fb_ref_भाग(अचिन्हित nom, अचिन्हित den, अचिन्हित post_भाग,
				      अचिन्हित fb_भाग_max, अचिन्हित ref_भाग_max,
				      अचिन्हित *fb_भाग, अचिन्हित *ref_भाग)
अणु
	/* limit reference * post भागider to a maximum */
	ref_भाग_max = min(128 / post_भाग, ref_भाग_max);

	/* get matching reference and feedback भागider */
	*ref_भाग = min(max(DIV_ROUND_CLOSEST(den, post_भाग), 1u), ref_भाग_max);
	*fb_भाग = DIV_ROUND_CLOSEST(nom * *ref_भाग * post_भाग, den);

	/* limit fb भागider to its maximum */
	अगर (*fb_भाग > fb_भाग_max) अणु
		*ref_भाग = DIV_ROUND_CLOSEST(*ref_भाग * fb_भाग_max, *fb_भाग);
		*fb_भाग = fb_भाग_max;
	पूर्ण
पूर्ण

/**
 * amdgpu_pll_compute - compute PLL paramaters
 *
 * @pll: inक्रमmation about the PLL
 * @freq: requested frequency
 * @करोt_घड़ी_p: resulting pixel घड़ी
 * @fb_भाग_p: resulting feedback भागider
 * @frac_fb_भाग_p: fractional part of the feedback भागider
 * @ref_भाग_p: resulting reference भागider
 * @post_भाग_p: resulting reference भागider
 *
 * Try to calculate the PLL parameters to generate the given frequency:
 * करोt_घड़ी = (ref_freq * feedback_भाग) / (ref_भाग * post_भाग)
 */
व्योम amdgpu_pll_compute(काष्ठा amdgpu_pll *pll,
			u32 freq,
			u32 *करोt_घड़ी_p,
			u32 *fb_भाग_p,
			u32 *frac_fb_भाग_p,
			u32 *ref_भाग_p,
			u32 *post_भाग_p)
अणु
	अचिन्हित target_घड़ी = pll->flags & AMDGPU_PLL_USE_FRAC_FB_DIV ?
		freq : freq / 10;

	अचिन्हित fb_भाग_min, fb_भाग_max, fb_भाग;
	अचिन्हित post_भाग_min, post_भाग_max, post_भाग;
	अचिन्हित ref_भाग_min, ref_भाग_max, ref_भाग;
	अचिन्हित post_भाग_best, dअगरf_best;
	अचिन्हित nom, den;

	/* determine allowed feedback भागider range */
	fb_भाग_min = pll->min_feedback_भाग;
	fb_भाग_max = pll->max_feedback_भाग;

	अगर (pll->flags & AMDGPU_PLL_USE_FRAC_FB_DIV) अणु
		fb_भाग_min *= 10;
		fb_भाग_max *= 10;
	पूर्ण

	/* determine allowed ref भागider range */
	अगर (pll->flags & AMDGPU_PLL_USE_REF_DIV)
		ref_भाग_min = pll->reference_भाग;
	अन्यथा
		ref_भाग_min = pll->min_ref_भाग;

	अगर (pll->flags & AMDGPU_PLL_USE_FRAC_FB_DIV &&
	    pll->flags & AMDGPU_PLL_USE_REF_DIV)
		ref_भाग_max = pll->reference_भाग;
	अन्यथा
		ref_भाग_max = pll->max_ref_भाग;

	/* determine allowed post भागider range */
	अगर (pll->flags & AMDGPU_PLL_USE_POST_DIV) अणु
		post_भाग_min = pll->post_भाग;
		post_भाग_max = pll->post_भाग;
	पूर्ण अन्यथा अणु
		अचिन्हित vco_min, vco_max;

		अगर (pll->flags & AMDGPU_PLL_IS_LCD) अणु
			vco_min = pll->lcd_pll_out_min;
			vco_max = pll->lcd_pll_out_max;
		पूर्ण अन्यथा अणु
			vco_min = pll->pll_out_min;
			vco_max = pll->pll_out_max;
		पूर्ण

		अगर (pll->flags & AMDGPU_PLL_USE_FRAC_FB_DIV) अणु
			vco_min *= 10;
			vco_max *= 10;
		पूर्ण

		post_भाग_min = vco_min / target_घड़ी;
		अगर ((target_घड़ी * post_भाग_min) < vco_min)
			++post_भाग_min;
		अगर (post_भाग_min < pll->min_post_भाग)
			post_भाग_min = pll->min_post_भाग;

		post_भाग_max = vco_max / target_घड़ी;
		अगर ((target_घड़ी * post_भाग_max) > vco_max)
			--post_भाग_max;
		अगर (post_भाग_max > pll->max_post_भाग)
			post_भाग_max = pll->max_post_भाग;
	पूर्ण

	/* represent the searched ratio as fractional number */
	nom = target_घड़ी;
	den = pll->reference_freq;

	/* reduce the numbers to a simpler ratio */
	amdgpu_pll_reduce_ratio(&nom, &den, fb_भाग_min, post_भाग_min);

	/* now search क्रम a post भागider */
	अगर (pll->flags & AMDGPU_PLL_PREFER_MINM_OVER_MAXP)
		post_भाग_best = post_भाग_min;
	अन्यथा
		post_भाग_best = post_भाग_max;
	dअगरf_best = ~0;

	क्रम (post_भाग = post_भाग_min; post_भाग <= post_भाग_max; ++post_भाग) अणु
		अचिन्हित dअगरf;
		amdgpu_pll_get_fb_ref_भाग(nom, den, post_भाग, fb_भाग_max,
					  ref_भाग_max, &fb_भाग, &ref_भाग);
		dअगरf = असल(target_घड़ी - (pll->reference_freq * fb_भाग) /
			(ref_भाग * post_भाग));

		अगर (dअगरf < dअगरf_best || (dअगरf == dअगरf_best &&
		    !(pll->flags & AMDGPU_PLL_PREFER_MINM_OVER_MAXP))) अणु

			post_भाग_best = post_भाग;
			dअगरf_best = dअगरf;
		पूर्ण
	पूर्ण
	post_भाग = post_भाग_best;

	/* get the feedback and reference भागider क्रम the optimal value */
	amdgpu_pll_get_fb_ref_भाग(nom, den, post_भाग, fb_भाग_max, ref_भाग_max,
				  &fb_भाग, &ref_भाग);

	/* reduce the numbers to a simpler ratio once more */
	/* this also makes sure that the reference भागider is large enough */
	amdgpu_pll_reduce_ratio(&fb_भाग, &ref_भाग, fb_भाग_min, ref_भाग_min);

	/* aव्योम high jitter with small fractional भागiders */
	अगर (pll->flags & AMDGPU_PLL_USE_FRAC_FB_DIV && (fb_भाग % 10)) अणु
		fb_भाग_min = max(fb_भाग_min, (9 - (fb_भाग % 10)) * 20 + 60);
		अगर (fb_भाग < fb_भाग_min) अणु
			अचिन्हित पंचांगp = DIV_ROUND_UP(fb_भाग_min, fb_भाग);
			fb_भाग *= पंचांगp;
			ref_भाग *= पंचांगp;
		पूर्ण
	पूर्ण

	/* and finally save the result */
	अगर (pll->flags & AMDGPU_PLL_USE_FRAC_FB_DIV) अणु
		*fb_भाग_p = fb_भाग / 10;
		*frac_fb_भाग_p = fb_भाग % 10;
	पूर्ण अन्यथा अणु
		*fb_भाग_p = fb_भाग;
		*frac_fb_भाग_p = 0;
	पूर्ण

	*करोt_घड़ी_p = ((pll->reference_freq * *fb_भाग_p * 10) +
			(pll->reference_freq * *frac_fb_भाग_p)) /
		       (ref_भाग * post_भाग * 10);
	*ref_भाग_p = ref_भाग;
	*post_भाग_p = post_भाग;

	DRM_DEBUG_KMS("%d - %d, pll dividers - fb: %d.%d ref: %d, post %d\n",
		      freq, *करोt_घड़ी_p * 10, *fb_भाग_p, *frac_fb_भाग_p,
		      ref_भाग, post_भाग);
पूर्ण

/**
 * amdgpu_pll_get_use_mask - look up a mask of which pplls are in use
 *
 * @crtc: drm crtc
 *
 * Returns the mask of which PPLLs (Pixel PLLs) are in use.
 */
u32 amdgpu_pll_get_use_mask(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_crtc *test_crtc;
	काष्ठा amdgpu_crtc *test_amdgpu_crtc;
	u32 pll_in_use = 0;

	list_क्रम_each_entry(test_crtc, &dev->mode_config.crtc_list, head) अणु
		अगर (crtc == test_crtc)
			जारी;

		test_amdgpu_crtc = to_amdgpu_crtc(test_crtc);
		अगर (test_amdgpu_crtc->pll_id != ATOM_PPLL_INVALID)
			pll_in_use |= (1 << test_amdgpu_crtc->pll_id);
	पूर्ण
	वापस pll_in_use;
पूर्ण

/**
 * amdgpu_pll_get_shared_dp_ppll - वापस the PPLL used by another crtc क्रम DP
 *
 * @crtc: drm crtc
 *
 * Returns the PPLL (Pixel PLL) used by another crtc/encoder which is
 * also in DP mode.  For DP, a single PPLL can be used क्रम all DP
 * crtcs/encoders.
 */
पूर्णांक amdgpu_pll_get_shared_dp_ppll(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_crtc *test_crtc;
	काष्ठा amdgpu_crtc *test_amdgpu_crtc;

	list_क्रम_each_entry(test_crtc, &dev->mode_config.crtc_list, head) अणु
		अगर (crtc == test_crtc)
			जारी;
		test_amdgpu_crtc = to_amdgpu_crtc(test_crtc);
		अगर (test_amdgpu_crtc->encoder &&
		    ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(test_amdgpu_crtc->encoder))) अणु
			/* क्रम DP use the same PLL क्रम all */
			अगर (test_amdgpu_crtc->pll_id != ATOM_PPLL_INVALID)
				वापस test_amdgpu_crtc->pll_id;
		पूर्ण
	पूर्ण
	वापस ATOM_PPLL_INVALID;
पूर्ण

/**
 * amdgpu_pll_get_shared_nondp_ppll - वापस the PPLL used by another non-DP crtc
 *
 * @crtc: drm crtc
 *
 * Returns the PPLL (Pixel PLL) used by another non-DP crtc/encoder which can
 * be shared (i.e., same घड़ी).
 */
पूर्णांक amdgpu_pll_get_shared_nondp_ppll(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_crtc *test_crtc;
	काष्ठा amdgpu_crtc *test_amdgpu_crtc;
	u32 adjusted_घड़ी, test_adjusted_घड़ी;

	adjusted_घड़ी = amdgpu_crtc->adjusted_घड़ी;

	अगर (adjusted_घड़ी == 0)
		वापस ATOM_PPLL_INVALID;

	list_क्रम_each_entry(test_crtc, &dev->mode_config.crtc_list, head) अणु
		अगर (crtc == test_crtc)
			जारी;
		test_amdgpu_crtc = to_amdgpu_crtc(test_crtc);
		अगर (test_amdgpu_crtc->encoder &&
		    !ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(test_amdgpu_crtc->encoder))) अणु
			/* check अगर we are alपढ़ोy driving this connector with another crtc */
			अगर (test_amdgpu_crtc->connector == amdgpu_crtc->connector) अणु
				/* अगर we are, वापस that pll */
				अगर (test_amdgpu_crtc->pll_id != ATOM_PPLL_INVALID)
					वापस test_amdgpu_crtc->pll_id;
			पूर्ण
			/* क्रम non-DP check the घड़ी */
			test_adjusted_घड़ी = test_amdgpu_crtc->adjusted_घड़ी;
			अगर ((crtc->mode.घड़ी == test_crtc->mode.घड़ी) &&
			    (adjusted_घड़ी == test_adjusted_घड़ी) &&
			    (amdgpu_crtc->ss_enabled == test_amdgpu_crtc->ss_enabled) &&
			    (test_amdgpu_crtc->pll_id != ATOM_PPLL_INVALID))
				वापस test_amdgpu_crtc->pll_id;
		पूर्ण
	पूर्ण
	वापस ATOM_PPLL_INVALID;
पूर्ण
