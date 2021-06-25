<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "intel_pm.h" /* पूर्णांकel_gpu_freq() */
#समावेश "selftest_llc.h"
#समावेश "intel_rps.h"

अटल पूर्णांक gen6_verअगरy_ring_freq(काष्ठा पूर्णांकel_llc *llc)
अणु
	काष्ठा drm_i915_निजी *i915 = llc_to_gt(llc)->i915;
	काष्ठा ia_स्थिरants स्थिरs;
	पूर्णांकel_wakeref_t wakeref;
	अचिन्हित पूर्णांक gpu_freq;
	पूर्णांक err = 0;

	wakeref = पूर्णांकel_runसमय_pm_get(llc_to_gt(llc)->uncore->rpm);

	अगर (!get_ia_स्थिरants(llc, &स्थिरs))
		जाओ out_rpm;

	क्रम (gpu_freq = स्थिरs.min_gpu_freq;
	     gpu_freq <= स्थिरs.max_gpu_freq;
	     gpu_freq++) अणु
		काष्ठा पूर्णांकel_rps *rps = &llc_to_gt(llc)->rps;

		अचिन्हित पूर्णांक ia_freq, ring_freq, found;
		u32 val;

		calc_ia_freq(llc, gpu_freq, &स्थिरs, &ia_freq, &ring_freq);

		val = gpu_freq;
		अगर (sandybridge_pcode_पढ़ो(i915,
					   GEN6_PCODE_READ_MIN_FREQ_TABLE,
					   &val, शून्य)) अणु
			pr_err("Failed to read freq table[%d], range [%d, %d]\n",
			       gpu_freq, स्थिरs.min_gpu_freq, स्थिरs.max_gpu_freq);
			err = -ENXIO;
			अवरोध;
		पूर्ण

		found = (val >> 0) & 0xff;
		अगर (found != ia_freq) अणु
			pr_err("Min freq table(%d/[%d, %d]):%dMHz did not match expected CPU freq, found %d, expected %d\n",
			       gpu_freq, स्थिरs.min_gpu_freq, स्थिरs.max_gpu_freq,
			       पूर्णांकel_gpu_freq(rps, gpu_freq * (INTEL_GEN(i915) >= 9 ? GEN9_FREQ_SCALER : 1)),
			       found, ia_freq);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		found = (val >> 8) & 0xff;
		अगर (found != ring_freq) अणु
			pr_err("Min freq table(%d/[%d, %d]):%dMHz did not match expected ring freq, found %d, expected %d\n",
			       gpu_freq, स्थिरs.min_gpu_freq, स्थिरs.max_gpu_freq,
			       पूर्णांकel_gpu_freq(rps, gpu_freq * (INTEL_GEN(i915) >= 9 ? GEN9_FREQ_SCALER : 1)),
			       found, ring_freq);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

out_rpm:
	पूर्णांकel_runसमय_pm_put(llc_to_gt(llc)->uncore->rpm, wakeref);
	वापस err;
पूर्ण

पूर्णांक st_llc_verअगरy(काष्ठा पूर्णांकel_llc *llc)
अणु
	वापस gen6_verअगरy_ring_freq(llc);
पूर्ण
