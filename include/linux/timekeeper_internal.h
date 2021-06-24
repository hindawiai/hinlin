<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * You SHOULD NOT be including this unless you're vsyscall
 * handling code or समयkeeping पूर्णांकernal code!
 */

#अगर_अघोषित _LINUX_TIMEKEEPER_INTERNAL_H
#घोषणा _LINUX_TIMEKEEPER_INTERNAL_H

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समय.स>

/**
 * काष्ठा tk_पढ़ो_base - base काष्ठाure क्रम समयkeeping पढ़ोout
 * @घड़ी:	Current घड़ीsource used क्रम समयkeeping.
 * @mask:	Biपंचांगask क्रम two's complement subtraction of non 64bit घड़ीs
 * @cycle_last: @घड़ी cycle value at last update
 * @mult:	(NTP adjusted) multiplier क्रम scaled math conversion
 * @shअगरt:	Shअगरt value क्रम scaled math conversion
 * @xसमय_nsec: Shअगरted (fractional) nano seconds offset क्रम पढ़ोout
 * @base:	kसमय_प्रकार (nanoseconds) base समय क्रम पढ़ोout
 * @base_real:	Nanoseconds base value क्रम घड़ी REALTIME पढ़ोout
 *
 * This काष्ठा has size 56 byte on 64 bit. Together with a seqcount it
 * occupies a single 64byte cache line.
 *
 * The काष्ठा is separate from काष्ठा समयkeeper as it is also used
 * क्रम a fast NMI safe accessors.
 *
 * @base_real is क्रम the fast NMI safe accessor to allow पढ़ोing घड़ी
 * realसमय from any context.
 */
काष्ठा tk_पढ़ो_base अणु
	काष्ठा घड़ीsource	*घड़ी;
	u64			mask;
	u64			cycle_last;
	u32			mult;
	u32			shअगरt;
	u64			xसमय_nsec;
	kसमय_प्रकार			base;
	u64			base_real;
पूर्ण;

/**
 * काष्ठा समयkeeper - Structure holding पूर्णांकernal समयkeeping values.
 * @tkr_mono:		The पढ़ोout base काष्ठाure क्रम CLOCK_MONOTONIC
 * @tkr_raw:		The पढ़ोout base काष्ठाure क्रम CLOCK_MONOTONIC_RAW
 * @xसमय_sec:		Current CLOCK_REALTIME समय in seconds
 * @kसमय_sec:		Current CLOCK_MONOTONIC समय in seconds
 * @wall_to_monotonic:	CLOCK_REALTIME to CLOCK_MONOTONIC offset
 * @offs_real:		Offset घड़ी monotonic -> घड़ी realसमय
 * @offs_boot:		Offset घड़ी monotonic -> घड़ी bootसमय
 * @offs_tai:		Offset घड़ी monotonic -> घड़ी tai
 * @tai_offset:		The current UTC to TAI offset in seconds
 * @घड़ी_was_set_seq:	The sequence number of घड़ी was set events
 * @cs_was_changed_seq:	The sequence number of घड़ीsource change events
 * @next_leap_kसमय:	CLOCK_MONOTONIC समय value of a pending leap-second
 * @raw_sec:		CLOCK_MONOTONIC_RAW  समय in seconds
 * @monotonic_to_boot:	CLOCK_MONOTONIC to CLOCK_BOOTTIME offset
 * @cycle_पूर्णांकerval:	Number of घड़ी cycles in one NTP पूर्णांकerval
 * @xसमय_पूर्णांकerval:	Number of घड़ी shअगरted nano seconds in one NTP
 *			पूर्णांकerval.
 * @xसमय_reमुख्यder:	Shअगरted nano seconds left over when rounding
 *			@cycle_पूर्णांकerval
 * @raw_पूर्णांकerval:	Shअगरted raw nano seconds accumulated per NTP पूर्णांकerval.
 * @ntp_error:		Dअगरference between accumulated समय and NTP समय in ntp
 *			shअगरted nano seconds.
 * @ntp_error_shअगरt:	Shअगरt conversion between घड़ी shअगरted nano seconds and
 *			ntp shअगरted nano seconds.
 * @last_warning:	Warning ratelimiter (DEBUG_TIMEKEEPING)
 * @underflow_seen:	Underflow warning flag (DEBUG_TIMEKEEPING)
 * @overflow_seen:	Overflow warning flag (DEBUG_TIMEKEEPING)
 *
 * Note: For बारpec(64) based पूर्णांकerfaces wall_to_monotonic is what
 * we need to add to xसमय (or xसमय corrected क्रम sub jअगरfie बार)
 * to get to monotonic समय.  Monotonic is pegged at zero at प्रणाली
 * boot समय, so wall_to_monotonic will be negative, however, we will
 * ALWAYS keep the tv_nsec part positive so we can use the usual
 * normalization.
 *
 * wall_to_monotonic is moved after resume from suspend क्रम the
 * monotonic समय not to jump. We need to add total_sleep_समय to
 * wall_to_monotonic to get the real boot based समय offset.
 *
 * wall_to_monotonic is no दीर्घer the boot समय, getbootसमय must be
 * used instead.
 *
 * @monotonic_to_bootसमय is a बारpec64 representation of @offs_boot to
 * accelerate the VDSO update क्रम CLOCK_BOOTTIME.
 */
काष्ठा समयkeeper अणु
	काष्ठा tk_पढ़ो_base	tkr_mono;
	काष्ठा tk_पढ़ो_base	tkr_raw;
	u64			xसमय_sec;
	अचिन्हित दीर्घ		kसमय_sec;
	काष्ठा बारpec64	wall_to_monotonic;
	kसमय_प्रकार			offs_real;
	kसमय_प्रकार			offs_boot;
	kसमय_प्रकार			offs_tai;
	s32			tai_offset;
	अचिन्हित पूर्णांक		घड़ी_was_set_seq;
	u8			cs_was_changed_seq;
	kसमय_प्रकार			next_leap_kसमय;
	u64			raw_sec;
	काष्ठा बारpec64	monotonic_to_boot;

	/* The following members are क्रम समयkeeping पूर्णांकernal use */
	u64			cycle_पूर्णांकerval;
	u64			xसमय_पूर्णांकerval;
	s64			xसमय_reमुख्यder;
	u64			raw_पूर्णांकerval;
	/* The ntp_tick_length() value currently being used.
	 * This cached copy ensures we consistently apply the tick
	 * length क्रम an entire tick, as ntp_tick_length may change
	 * mid-tick, and we करोn't want to apply that new value to
	 * the tick in progress.
	 */
	u64			ntp_tick;
	/* Dअगरference between accumulated समय and NTP समय in ntp
	 * shअगरted nano seconds. */
	s64			ntp_error;
	u32			ntp_error_shअगरt;
	u32			ntp_err_mult;
	/* Flag used to aव्योम updating NTP twice with same second */
	u32			skip_second_overflow;
#अगर_घोषित CONFIG_DEBUG_TIMEKEEPING
	दीर्घ			last_warning;
	/*
	 * These simple flag variables are managed
	 * without locks, which is racy, but they are
	 * ok since we करोn't really care about being
	 * super precise about how many events were
	 * seen, just that a problem was observed.
	 */
	पूर्णांक			underflow_seen;
	पूर्णांक			overflow_seen;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_GENERIC_TIME_VSYSCALL

बाह्य व्योम update_vsyscall(काष्ठा समयkeeper *tk);
बाह्य व्योम update_vsyscall_tz(व्योम);

#अन्यथा

अटल अंतरभूत व्योम update_vsyscall(काष्ठा समयkeeper *tk)
अणु
पूर्ण
अटल अंतरभूत व्योम update_vsyscall_tz(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_TIMEKEEPER_INTERNAL_H */
