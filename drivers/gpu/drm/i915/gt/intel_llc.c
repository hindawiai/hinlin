<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/cpufreq.h>

#समावेश "i915_drv.h"
#समावेश "intel_gt.h"
#समावेश "intel_llc.h"
#समावेश "intel_sideband.h"

काष्ठा ia_स्थिरants अणु
	अचिन्हित पूर्णांक min_gpu_freq;
	अचिन्हित पूर्णांक max_gpu_freq;

	अचिन्हित पूर्णांक min_ring_freq;
	अचिन्हित पूर्णांक max_ia_freq;
पूर्ण;

अटल काष्ठा पूर्णांकel_gt *llc_to_gt(काष्ठा पूर्णांकel_llc *llc)
अणु
	वापस container_of(llc, काष्ठा पूर्णांकel_gt, llc);
पूर्ण

अटल अचिन्हित पूर्णांक cpu_max_MHz(व्योम)
अणु
	काष्ठा cpufreq_policy *policy;
	अचिन्हित पूर्णांक max_khz;

	policy = cpufreq_cpu_get(0);
	अगर (policy) अणु
		max_khz = policy->cpuinfo.max_freq;
		cpufreq_cpu_put(policy);
	पूर्ण अन्यथा अणु
		/*
		 * Default to measured freq अगर none found, PCU will ensure we
		 * करोn't go over
		 */
		max_khz = tsc_khz;
	पूर्ण

	वापस max_khz / 1000;
पूर्ण

अटल bool get_ia_स्थिरants(काष्ठा पूर्णांकel_llc *llc,
			     काष्ठा ia_स्थिरants *स्थिरs)
अणु
	काष्ठा drm_i915_निजी *i915 = llc_to_gt(llc)->i915;
	काष्ठा पूर्णांकel_rps *rps = &llc_to_gt(llc)->rps;

	अगर (!HAS_LLC(i915) || IS_DGFX(i915))
		वापस false;

	अगर (rps->max_freq <= rps->min_freq)
		वापस false;

	स्थिरs->max_ia_freq = cpu_max_MHz();

	स्थिरs->min_ring_freq =
		पूर्णांकel_uncore_पढ़ो(llc_to_gt(llc)->uncore, DCLK) & 0xf;
	/* convert DDR frequency from units of 266.6MHz to bandwidth */
	स्थिरs->min_ring_freq = mult_frac(स्थिरs->min_ring_freq, 8, 3);

	स्थिरs->min_gpu_freq = rps->min_freq;
	स्थिरs->max_gpu_freq = rps->max_freq;
	अगर (INTEL_GEN(i915) >= 9) अणु
		/* Convert GT frequency to 50 HZ units */
		स्थिरs->min_gpu_freq /= GEN9_FREQ_SCALER;
		स्थिरs->max_gpu_freq /= GEN9_FREQ_SCALER;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम calc_ia_freq(काष्ठा पूर्णांकel_llc *llc,
			 अचिन्हित पूर्णांक gpu_freq,
			 स्थिर काष्ठा ia_स्थिरants *स्थिरs,
			 अचिन्हित पूर्णांक *out_ia_freq,
			 अचिन्हित पूर्णांक *out_ring_freq)
अणु
	काष्ठा drm_i915_निजी *i915 = llc_to_gt(llc)->i915;
	स्थिर पूर्णांक dअगरf = स्थिरs->max_gpu_freq - gpu_freq;
	अचिन्हित पूर्णांक ia_freq = 0, ring_freq = 0;

	अगर (INTEL_GEN(i915) >= 9) अणु
		/*
		 * ring_freq = 2 * GT. ring_freq is in 100MHz units
		 * No न्यूनमान required क्रम ring frequency on SKL.
		 */
		ring_freq = gpu_freq;
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 8) अणु
		/* max(2 * GT, DDR). NB: GT is 50MHz units */
		ring_freq = max(स्थिरs->min_ring_freq, gpu_freq);
	पूर्ण अन्यथा अगर (IS_HASWELL(i915)) अणु
		ring_freq = mult_frac(gpu_freq, 5, 4);
		ring_freq = max(स्थिरs->min_ring_freq, ring_freq);
		/* leave ia_freq as the शेष, chosen by cpufreq */
	पूर्ण अन्यथा अणु
		स्थिर पूर्णांक min_freq = 15;
		स्थिर पूर्णांक scale = 180;

		/*
		 * On older processors, there is no separate ring
		 * घड़ी करोमुख्य, so in order to boost the bandwidth
		 * of the ring, we need to upघड़ी the CPU (ia_freq).
		 *
		 * For GPU frequencies less than 750MHz,
		 * just use the lowest ring freq.
		 */
		अगर (gpu_freq < min_freq)
			ia_freq = 800;
		अन्यथा
			ia_freq = स्थिरs->max_ia_freq - dअगरf * scale / 2;
		ia_freq = DIV_ROUND_CLOSEST(ia_freq, 100);
	पूर्ण

	*out_ia_freq = ia_freq;
	*out_ring_freq = ring_freq;
पूर्ण

अटल व्योम gen6_update_ring_freq(काष्ठा पूर्णांकel_llc *llc)
अणु
	काष्ठा drm_i915_निजी *i915 = llc_to_gt(llc)->i915;
	काष्ठा ia_स्थिरants स्थिरs;
	अचिन्हित पूर्णांक gpu_freq;

	अगर (!get_ia_स्थिरants(llc, &स्थिरs))
		वापस;

	/*
	 * For each potential GPU frequency, load a ring frequency we'd like
	 * to use क्रम memory access.  We करो this by specअगरying the IA frequency
	 * the PCU should use as a reference to determine the ring frequency.
	 */
	क्रम (gpu_freq = स्थिरs.max_gpu_freq;
	     gpu_freq >= स्थिरs.min_gpu_freq;
	     gpu_freq--) अणु
		अचिन्हित पूर्णांक ia_freq, ring_freq;

		calc_ia_freq(llc, gpu_freq, &स्थिरs, &ia_freq, &ring_freq);
		sandybridge_pcode_ग_लिखो(i915,
					GEN6_PCODE_WRITE_MIN_FREQ_TABLE,
					ia_freq << GEN6_PCODE_FREQ_IA_RATIO_SHIFT |
					ring_freq << GEN6_PCODE_FREQ_RING_RATIO_SHIFT |
					gpu_freq);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_llc_enable(काष्ठा पूर्णांकel_llc *llc)
अणु
	gen6_update_ring_freq(llc);
पूर्ण

व्योम पूर्णांकel_llc_disable(काष्ठा पूर्णांकel_llc *llc)
अणु
	/* Currently there is no HW configuration to be करोne to disable. */
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_llc.c"
#पूर्ण_अगर
