<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_RPS_TYPES_H
#घोषणा INTEL_RPS_TYPES_H

#समावेश <linux/atomic.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

काष्ठा पूर्णांकel_ips अणु
	u64 last_count1;
	अचिन्हित दीर्घ last_समय1;
	अचिन्हित दीर्घ chipset_घातer;
	u64 last_count2;
	u64 last_समय2;
	अचिन्हित दीर्घ gfx_घातer;
	u8 corr;

	पूर्णांक c, m;
पूर्ण;

काष्ठा पूर्णांकel_rps_ei अणु
	kसमय_प्रकार kसमय;
	u32 render_c0;
	u32 media_c0;
पूर्ण;

क्रमागत अणु
	INTEL_RPS_ENABLED = 0,
	INTEL_RPS_ACTIVE,
	INTEL_RPS_INTERRUPTS,
	INTEL_RPS_TIMER,
पूर्ण;

काष्ठा पूर्णांकel_rps अणु
	काष्ठा mutex lock; /* protects enabling and the worker */

	/*
	 * work, पूर्णांकerrupts_enabled and pm_iir are रक्षित by
	 * dev_priv->irq_lock
	 */
	काष्ठा समयr_list समयr;
	काष्ठा work_काष्ठा work;
	अचिन्हित दीर्घ flags;

	kसमय_प्रकार pm_बारtamp;
	u32 pm_पूर्णांकerval;
	u32 pm_iir;

	/* PM पूर्णांकerrupt bits that should never be masked */
	u32 pm_पूर्णांकrmsk_mbz;
	u32 pm_events;

	/* Frequencies are stored in potentially platक्रमm dependent multiples.
	 * In other words, *_freq needs to be multiplied by X to be पूर्णांकeresting.
	 * Soft limits are those which are used क्रम the dynamic reघड़ीing करोne
	 * by the driver (उठाओ frequencies under heavy loads, and lower क्रम
	 * lighter loads). Hard limits are those imposed by the hardware.
	 *
	 * A distinction is made क्रम overघड़ीing, which is never enabled by
	 * शेष, and is considered to be above the hard limit अगर it's
	 * possible at all.
	 */
	u8 cur_freq;		/* Current frequency (cached, may not == HW) */
	u8 last_freq;		/* Last SWREQ frequency */
	u8 min_freq_softlimit;	/* Minimum frequency permitted by the driver */
	u8 max_freq_softlimit;	/* Max frequency permitted by the driver */
	u8 max_freq;		/* Maximum frequency, RP0 अगर not overघड़ीing */
	u8 min_freq;		/* AKA RPn. Minimum frequency */
	u8 boost_freq;		/* Frequency to request when रुको boosting */
	u8 idle_freq;		/* Frequency to request when we are idle */
	u8 efficient_freq;	/* AKA RPe. Pre-determined balanced frequency */
	u8 rp1_freq;		/* "less than" RP0 घातer/freqency */
	u8 rp0_freq;		/* Non-overघड़ीed max frequency. */
	u16 gpll_ref_freq;	/* vlv/chv GPLL reference frequency */

	पूर्णांक last_adj;

	काष्ठा अणु
		काष्ठा mutex mutex;

		क्रमागत अणु LOW_POWER, BETWEEN, HIGH_POWER पूर्ण mode;
		अचिन्हित पूर्णांक पूर्णांकeractive;

		u8 up_threshold; /* Current %busy required to uplock */
		u8 करोwn_threshold; /* Current %busy required to करोwnघड़ी */
	पूर्ण घातer;

	atomic_t num_रुकोers;
	अचिन्हित पूर्णांक boosts;

	/* manual wa residency calculations */
	काष्ठा पूर्णांकel_rps_ei ei;
	काष्ठा पूर्णांकel_ips ips;
पूर्ण;

#पूर्ण_अगर /* INTEL_RPS_TYPES_H */
