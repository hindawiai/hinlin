<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TIMEKEEPING_H
#घोषणा _LINUX_TIMEKEEPING_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/घड़ीsource_ids.h>

/* Included from linux/kसमय.स */

व्योम समयkeeping_init(व्योम);
बाह्य पूर्णांक समयkeeping_suspended;

/* Architecture समयr tick functions: */
बाह्य व्योम legacy_समयr_tick(अचिन्हित दीर्घ ticks);

/*
 * Get and set समयofday
 */
बाह्य पूर्णांक करो_समय_रखोofday64(स्थिर काष्ठा बारpec64 *ts);
बाह्य पूर्णांक करो_sys_समय_रखोofday64(स्थिर काष्ठा बारpec64 *tv,
				 स्थिर काष्ठा समयzone *tz);

/*
 * kसमय_get() family: पढ़ो the current समय in a multitude of ways,
 *
 * The शेष समय reference is CLOCK_MONOTONIC, starting at
 * boot समय but not counting the समय spent in suspend.
 * For other references, use the functions with "real", "clocktai",
 * "boottime" and "raw" suffixes.
 *
 * To get the समय in a dअगरferent क्रमmat, use the ones wit
 * "ns", "ts64" and "seconds" suffix.
 *
 * See Documentation/core-api/समयkeeping.rst क्रम more details.
 */


/*
 * बारpec64 based पूर्णांकerfaces
 */
बाह्य व्योम kसमय_get_raw_ts64(काष्ठा बारpec64 *ts);
बाह्य व्योम kसमय_get_ts64(काष्ठा बारpec64 *ts);
बाह्य व्योम kसमय_get_real_ts64(काष्ठा बारpec64 *tv);
बाह्य व्योम kसमय_get_coarse_ts64(काष्ठा बारpec64 *ts);
बाह्य व्योम kसमय_get_coarse_real_ts64(काष्ठा बारpec64 *ts);

व्योम getbootसमय64(काष्ठा बारpec64 *ts);

/*
 * समय64_t base पूर्णांकerfaces
 */
बाह्य समय64_t kसमय_get_seconds(व्योम);
बाह्य समय64_t __kसमय_get_real_seconds(व्योम);
बाह्य समय64_t kसमय_get_real_seconds(व्योम);

/*
 * kसमय_प्रकार based पूर्णांकerfaces
 */

क्रमागत tk_offsets अणु
	TK_OFFS_REAL,
	TK_OFFS_BOOT,
	TK_OFFS_TAI,
	TK_OFFS_MAX,
पूर्ण;

बाह्य kसमय_प्रकार kसमय_get(व्योम);
बाह्य kसमय_प्रकार kसमय_get_with_offset(क्रमागत tk_offsets offs);
बाह्य kसमय_प्रकार kसमय_get_coarse_with_offset(क्रमागत tk_offsets offs);
बाह्य kसमय_प्रकार kसमय_mono_to_any(kसमय_प्रकार पंचांगono, क्रमागत tk_offsets offs);
बाह्य kसमय_प्रकार kसमय_get_raw(व्योम);
बाह्य u32 kसमय_get_resolution_ns(व्योम);

/**
 * kसमय_get_real - get the real (wall-) समय in kसमय_प्रकार क्रमmat
 */
अटल अंतरभूत kसमय_प्रकार kसमय_get_real(व्योम)
अणु
	वापस kसमय_get_with_offset(TK_OFFS_REAL);
पूर्ण

अटल अंतरभूत kसमय_प्रकार kसमय_get_coarse_real(व्योम)
अणु
	वापस kसमय_get_coarse_with_offset(TK_OFFS_REAL);
पूर्ण

/**
 * kसमय_get_bootसमय - Returns monotonic समय since boot in kसमय_प्रकार क्रमmat
 *
 * This is similar to CLOCK_MONTONIC/kसमय_get, but also includes the
 * समय spent in suspend.
 */
अटल अंतरभूत kसमय_प्रकार kसमय_get_bootसमय(व्योम)
अणु
	वापस kसमय_get_with_offset(TK_OFFS_BOOT);
पूर्ण

अटल अंतरभूत kसमय_प्रकार kसमय_get_coarse_bootसमय(व्योम)
अणु
	वापस kसमय_get_coarse_with_offset(TK_OFFS_BOOT);
पूर्ण

/**
 * kसमय_get_घड़ीtai - Returns the TAI समय of day in kसमय_प्रकार क्रमmat
 */
अटल अंतरभूत kसमय_प्रकार kसमय_get_घड़ीtai(व्योम)
अणु
	वापस kसमय_get_with_offset(TK_OFFS_TAI);
पूर्ण

अटल अंतरभूत kसमय_प्रकार kसमय_get_coarse_घड़ीtai(व्योम)
अणु
	वापस kसमय_get_coarse_with_offset(TK_OFFS_TAI);
पूर्ण

अटल अंतरभूत kसमय_प्रकार kसमय_get_coarse(व्योम)
अणु
	काष्ठा बारpec64 ts;

	kसमय_get_coarse_ts64(&ts);
	वापस बारpec64_to_kसमय(ts);
पूर्ण

अटल अंतरभूत u64 kसमय_get_coarse_ns(व्योम)
अणु
	वापस kसमय_प्रकारo_ns(kसमय_get_coarse());
पूर्ण

अटल अंतरभूत u64 kसमय_get_coarse_real_ns(व्योम)
अणु
	वापस kसमय_प्रकारo_ns(kसमय_get_coarse_real());
पूर्ण

अटल अंतरभूत u64 kसमय_get_coarse_bootसमय_ns(व्योम)
अणु
	वापस kसमय_प्रकारo_ns(kसमय_get_coarse_bootसमय());
पूर्ण

अटल अंतरभूत u64 kसमय_get_coarse_घड़ीtai_ns(व्योम)
अणु
	वापस kसमय_प्रकारo_ns(kसमय_get_coarse_घड़ीtai());
पूर्ण

/**
 * kसमय_mono_to_real - Convert monotonic समय to घड़ी realसमय
 */
अटल अंतरभूत kसमय_प्रकार kसमय_mono_to_real(kसमय_प्रकार mono)
अणु
	वापस kसमय_mono_to_any(mono, TK_OFFS_REAL);
पूर्ण

अटल अंतरभूत u64 kसमय_get_ns(व्योम)
अणु
	वापस kसमय_प्रकारo_ns(kसमय_get());
पूर्ण

अटल अंतरभूत u64 kसमय_get_real_ns(व्योम)
अणु
	वापस kसमय_प्रकारo_ns(kसमय_get_real());
पूर्ण

अटल अंतरभूत u64 kसमय_get_bootसमय_ns(व्योम)
अणु
	वापस kसमय_प्रकारo_ns(kसमय_get_bootसमय());
पूर्ण

अटल अंतरभूत u64 kसमय_get_घड़ीtai_ns(व्योम)
अणु
	वापस kसमय_प्रकारo_ns(kसमय_get_घड़ीtai());
पूर्ण

अटल अंतरभूत u64 kसमय_get_raw_ns(व्योम)
अणु
	वापस kसमय_प्रकारo_ns(kसमय_get_raw());
पूर्ण

बाह्य u64 kसमय_get_mono_fast_ns(व्योम);
बाह्य u64 kसमय_get_raw_fast_ns(व्योम);
बाह्य u64 kसमय_get_boot_fast_ns(व्योम);
बाह्य u64 kसमय_get_real_fast_ns(व्योम);

/*
 * बारpec64/समय64_t पूर्णांकerfaces utilizing the kसमय based ones
 * क्रम API completeness, these could be implemented more efficiently
 * अगर needed.
 */
अटल अंतरभूत व्योम kसमय_get_bootसमय_प्रकारs64(काष्ठा बारpec64 *ts)
अणु
	*ts = kसमय_प्रकारo_बारpec64(kसमय_get_bootसमय());
पूर्ण

अटल अंतरभूत व्योम kसमय_get_coarse_bootसमय_प्रकारs64(काष्ठा बारpec64 *ts)
अणु
	*ts = kसमय_प्रकारo_बारpec64(kसमय_get_coarse_bootसमय());
पूर्ण

अटल अंतरभूत समय64_t kसमय_get_bootसमय_seconds(व्योम)
अणु
	वापस kसमय_भागns(kसमय_get_coarse_bootसमय(), NSEC_PER_SEC);
पूर्ण

अटल अंतरभूत व्योम kसमय_get_घड़ीtai_ts64(काष्ठा बारpec64 *ts)
अणु
	*ts = kसमय_प्रकारo_बारpec64(kसमय_get_घड़ीtai());
पूर्ण

अटल अंतरभूत व्योम kसमय_get_coarse_घड़ीtai_ts64(काष्ठा बारpec64 *ts)
अणु
	*ts = kसमय_प्रकारo_बारpec64(kसमय_get_coarse_घड़ीtai());
पूर्ण

अटल अंतरभूत समय64_t kसमय_get_घड़ीtai_seconds(व्योम)
अणु
	वापस kसमय_भागns(kसमय_get_coarse_घड़ीtai(), NSEC_PER_SEC);
पूर्ण

/*
 * RTC specअगरic
 */
बाह्य bool समयkeeping_rtc_skipsuspend(व्योम);
बाह्य bool समयkeeping_rtc_skipresume(व्योम);

बाह्य व्योम समयkeeping_inject_sleepसमय64(स्थिर काष्ठा बारpec64 *delta);

/*
 * काष्ठा kसमय_प्रकारimestanps - Simultaneous mono/boot/real बारtamps
 * @mono:	Monotonic बारtamp
 * @boot:	Bootसमय बारtamp
 * @real:	Realसमय बारtamp
 */
काष्ठा kसमय_प्रकारimestamps अणु
	u64		mono;
	u64		boot;
	u64		real;
पूर्ण;

/**
 * काष्ठा प्रणाली_समय_snapshot - simultaneous raw/real समय capture with
 *				 counter value
 * @cycles:	Clocksource counter value to produce the प्रणाली बार
 * @real:	Realसमय प्रणाली समय
 * @raw:	Monotonic raw प्रणाली समय
 * @घड़ी_was_set_seq:	The sequence number of घड़ी was set events
 * @cs_was_changed_seq:	The sequence number of घड़ीsource change events
 */
काष्ठा प्रणाली_समय_snapshot अणु
	u64			cycles;
	kसमय_प्रकार			real;
	kसमय_प्रकार			raw;
	क्रमागत घड़ीsource_ids	cs_id;
	अचिन्हित पूर्णांक		घड़ी_was_set_seq;
	u8			cs_was_changed_seq;
पूर्ण;

/**
 * काष्ठा प्रणाली_device_crosststamp - प्रणाली/device cross-बारtamp
 *				      (synchronized capture)
 * @device:		Device समय
 * @sys_realसमय:	Realसमय simultaneous with device समय
 * @sys_monoraw:	Monotonic raw simultaneous with device समय
 */
काष्ठा प्रणाली_device_crosststamp अणु
	kसमय_प्रकार device;
	kसमय_प्रकार sys_realसमय;
	kसमय_प्रकार sys_monoraw;
पूर्ण;

/**
 * काष्ठा प्रणाली_counterval_t - प्रणाली counter value with the poपूर्णांकer to the
 *				corresponding घड़ीsource
 * @cycles:	System counter value
 * @cs:		Clocksource corresponding to प्रणाली counter value. Used by
 *		समयkeeping code to verअगरy comparibility of two cycle values
 */
काष्ठा प्रणाली_counterval_t अणु
	u64			cycles;
	काष्ठा घड़ीsource	*cs;
पूर्ण;

/*
 * Get cross बारtamp between प्रणाली घड़ी and device घड़ी
 */
बाह्य पूर्णांक get_device_प्रणाली_crosststamp(
			पूर्णांक (*get_समय_fn)(kसमय_प्रकार *device_समय,
				काष्ठा प्रणाली_counterval_t *प्रणाली_counterval,
				व्योम *ctx),
			व्योम *ctx,
			काष्ठा प्रणाली_समय_snapshot *history,
			काष्ठा प्रणाली_device_crosststamp *xtstamp);

/*
 * Simultaneously snapshot realसमय and monotonic raw घड़ीs
 */
बाह्य व्योम kसमय_get_snapshot(काष्ठा प्रणाली_समय_snapshot *sysसमय_snapshot);

/* NMI safe mono/boot/realसमय बारtamps */
बाह्य व्योम kसमय_get_fast_बारtamps(काष्ठा kसमय_प्रकारimestamps *snap);

/*
 * Persistent घड़ी related पूर्णांकerfaces
 */
बाह्य पूर्णांक persistent_घड़ी_is_local;

बाह्य व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts);
व्योम पढ़ो_persistent_wall_and_boot_offset(काष्ठा बारpec64 *wall_घड़ी,
					  काष्ठा बारpec64 *boot_offset);
#अगर_घोषित CONFIG_GENERIC_CMOS_UPDATE
बाह्य पूर्णांक update_persistent_घड़ी64(काष्ठा बारpec64 now);
#पूर्ण_अगर

#पूर्ण_अगर
