<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NTP state machine पूर्णांकerfaces and logic.
 *
 * This code was मुख्यly moved from kernel/समयr.c and kernel/समय.c
 * Please see those files क्रम relevant copyright info and historical
 * changelogs.
 */
#समावेश <linux/capability.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/math64.h>
#समावेश <linux/समयx.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/audit.h>

#समावेश "ntp_internal.h"
#समावेश "timekeeping_internal.h"


/*
 * NTP समयkeeping variables:
 *
 * Note: All of the NTP state is रक्षित by the समयkeeping locks.
 */


/* USER_HZ period (usecs): */
अचिन्हित दीर्घ			tick_usec = USER_TICK_USEC;

/* SHIFTED_HZ period (nsecs): */
अचिन्हित दीर्घ			tick_nsec;

अटल u64			tick_length;
अटल u64			tick_length_base;

#घोषणा SECS_PER_DAY		86400
#घोषणा MAX_TICKADJ		500LL		/* usecs */
#घोषणा MAX_TICKADJ_SCALED \
	(((MAX_TICKADJ * NSEC_PER_USEC) << NTP_SCALE_SHIFT) / NTP_INTERVAL_FREQ)
#घोषणा MAX_TAI_OFFSET		100000

/*
 * phase-lock loop variables
 */

/*
 * घड़ी synchronization status
 *
 * (TIME_ERROR prevents overwriting the CMOS घड़ी)
 */
अटल पूर्णांक			समय_state = TIME_OK;

/* घड़ी status bits:							*/
अटल पूर्णांक			समय_status = STA_UNSYNC;

/* समय adjusपंचांगent (nsecs):						*/
अटल s64			समय_offset;

/* pll समय स्थिरant:							*/
अटल दीर्घ			समय_स्थिरant = 2;

/* maximum error (usecs):						*/
अटल दीर्घ			समय_maxerror = NTP_PHASE_LIMIT;

/* estimated error (usecs):						*/
अटल दीर्घ			समय_esterror = NTP_PHASE_LIMIT;

/* frequency offset (scaled nsecs/secs):				*/
अटल s64			समय_freq;

/* समय at last adjusपंचांगent (secs):					*/
अटल समय64_t		समय_refसमय;

अटल दीर्घ			समय_adjust;

/* स्थिरant (boot-param configurable) NTP tick adjusपंचांगent (upscaled)	*/
अटल s64			ntp_tick_adj;

/* second value of the next pending leapsecond, or TIME64_MAX अगर no leap */
अटल समय64_t			ntp_next_leap_sec = TIME64_MAX;

#अगर_घोषित CONFIG_NTP_PPS

/*
 * The following variables are used when a pulse-per-second (PPS) संकेत
 * is available. They establish the engineering parameters of the घड़ी
 * discipline loop when controlled by the PPS संकेत.
 */
#घोषणा PPS_VALID	10	/* PPS संकेत watchकरोg max (s) */
#घोषणा PPS_POPCORN	4	/* popcorn spike threshold (shअगरt) */
#घोषणा PPS_INTMIN	2	/* min freq पूर्णांकerval (s) (shअगरt) */
#घोषणा PPS_INTMAX	8	/* max freq पूर्णांकerval (s) (shअगरt) */
#घोषणा PPS_INTCOUNT	4	/* number of consecutive good पूर्णांकervals to
				   increase pps_shअगरt or consecutive bad
				   पूर्णांकervals to decrease it */
#घोषणा PPS_MAXWANDER	100000	/* max PPS freq wander (ns/s) */

अटल पूर्णांक pps_valid;		/* संकेत watchकरोg counter */
अटल दीर्घ pps_tf[3];		/* phase median filter */
अटल दीर्घ pps_jitter;		/* current jitter (ns) */
अटल काष्ठा बारpec64 pps_fbase; /* beginning of the last freq पूर्णांकerval */
अटल पूर्णांक pps_shअगरt;		/* current पूर्णांकerval duration (s) (shअगरt) */
अटल पूर्णांक pps_पूर्णांकcnt;		/* पूर्णांकerval counter */
अटल s64 pps_freq;		/* frequency offset (scaled ns/s) */
अटल दीर्घ pps_stabil;		/* current stability (scaled ns/s) */

/*
 * PPS संकेत quality monitors
 */
अटल दीर्घ pps_calcnt;		/* calibration पूर्णांकervals */
अटल दीर्घ pps_jitcnt;		/* jitter limit exceeded */
अटल दीर्घ pps_stbcnt;		/* stability limit exceeded */
अटल दीर्घ pps_errcnt;		/* calibration errors */


/* PPS kernel consumer compensates the whole phase error immediately.
 * Otherwise, reduce the offset by a fixed factor बार the समय स्थिरant.
 */
अटल अंतरभूत s64 ntp_offset_chunk(s64 offset)
अणु
	अगर (समय_status & STA_PPSTIME && समय_status & STA_PPSSIGNAL)
		वापस offset;
	अन्यथा
		वापस shअगरt_right(offset, SHIFT_PLL + समय_स्थिरant);
पूर्ण

अटल अंतरभूत व्योम pps_reset_freq_पूर्णांकerval(व्योम)
अणु
	/* the PPS calibration पूर्णांकerval may end
	   surprisingly early */
	pps_shअगरt = PPS_INTMIN;
	pps_पूर्णांकcnt = 0;
पूर्ण

/**
 * pps_clear - Clears the PPS state variables
 */
अटल अंतरभूत व्योम pps_clear(व्योम)
अणु
	pps_reset_freq_पूर्णांकerval();
	pps_tf[0] = 0;
	pps_tf[1] = 0;
	pps_tf[2] = 0;
	pps_fbase.tv_sec = pps_fbase.tv_nsec = 0;
	pps_freq = 0;
पूर्ण

/* Decrease pps_valid to indicate that another second has passed since
 * the last PPS संकेत. When it reaches 0, indicate that PPS संकेत is
 * missing.
 */
अटल अंतरभूत व्योम pps_dec_valid(व्योम)
अणु
	अगर (pps_valid > 0)
		pps_valid--;
	अन्यथा अणु
		समय_status &= ~(STA_PPSSIGNAL | STA_PPSJITTER |
				 STA_PPSWANDER | STA_PPSERROR);
		pps_clear();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pps_set_freq(s64 freq)
अणु
	pps_freq = freq;
पूर्ण

अटल अंतरभूत पूर्णांक is_error_status(पूर्णांक status)
अणु
	वापस (status & (STA_UNSYNC|STA_CLOCKERR))
		/* PPS संकेत lost when either PPS समय or
		 * PPS frequency synchronization requested
		 */
		|| ((status & (STA_PPSFREQ|STA_PPSTIME))
			&& !(status & STA_PPSSIGNAL))
		/* PPS jitter exceeded when
		 * PPS समय synchronization requested */
		|| ((status & (STA_PPSTIME|STA_PPSJITTER))
			== (STA_PPSTIME|STA_PPSJITTER))
		/* PPS wander exceeded or calibration error when
		 * PPS frequency synchronization requested
		 */
		|| ((status & STA_PPSFREQ)
			&& (status & (STA_PPSWANDER|STA_PPSERROR)));
पूर्ण

अटल अंतरभूत व्योम pps_fill_समयx(काष्ठा __kernel_समयx *txc)
अणु
	txc->ppsfreq	   = shअगरt_right((pps_freq >> PPM_SCALE_INV_SHIFT) *
					 PPM_SCALE_INV, NTP_SCALE_SHIFT);
	txc->jitter	   = pps_jitter;
	अगर (!(समय_status & STA_न_अंकO))
		txc->jitter = pps_jitter / NSEC_PER_USEC;
	txc->shअगरt	   = pps_shअगरt;
	txc->stabil	   = pps_stabil;
	txc->jitcnt	   = pps_jitcnt;
	txc->calcnt	   = pps_calcnt;
	txc->errcnt	   = pps_errcnt;
	txc->stbcnt	   = pps_stbcnt;
पूर्ण

#अन्यथा /* !CONFIG_NTP_PPS */

अटल अंतरभूत s64 ntp_offset_chunk(s64 offset)
अणु
	वापस shअगरt_right(offset, SHIFT_PLL + समय_स्थिरant);
पूर्ण

अटल अंतरभूत व्योम pps_reset_freq_पूर्णांकerval(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम pps_clear(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम pps_dec_valid(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम pps_set_freq(s64 freq) अणुपूर्ण

अटल अंतरभूत पूर्णांक is_error_status(पूर्णांक status)
अणु
	वापस status & (STA_UNSYNC|STA_CLOCKERR);
पूर्ण

अटल अंतरभूत व्योम pps_fill_समयx(काष्ठा __kernel_समयx *txc)
अणु
	/* PPS is not implemented, so these are zero */
	txc->ppsfreq	   = 0;
	txc->jitter	   = 0;
	txc->shअगरt	   = 0;
	txc->stabil	   = 0;
	txc->jitcnt	   = 0;
	txc->calcnt	   = 0;
	txc->errcnt	   = 0;
	txc->stbcnt	   = 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_NTP_PPS */


/**
 * ntp_synced - Returns 1 अगर the NTP status is not UNSYNC
 *
 */
अटल अंतरभूत पूर्णांक ntp_synced(व्योम)
अणु
	वापस !(समय_status & STA_UNSYNC);
पूर्ण


/*
 * NTP methods:
 */

/*
 * Update (tick_length, tick_length_base, tick_nsec), based
 * on (tick_usec, ntp_tick_adj, समय_freq):
 */
अटल व्योम ntp_update_frequency(व्योम)
अणु
	u64 second_length;
	u64 new_base;

	second_length		 = (u64)(tick_usec * NSEC_PER_USEC * USER_HZ)
						<< NTP_SCALE_SHIFT;

	second_length		+= ntp_tick_adj;
	second_length		+= समय_freq;

	tick_nsec		 = भाग_u64(second_length, HZ) >> NTP_SCALE_SHIFT;
	new_base		 = भाग_u64(second_length, NTP_INTERVAL_FREQ);

	/*
	 * Don't रुको क्रम the next second_overflow, apply
	 * the change to the tick length immediately:
	 */
	tick_length		+= new_base - tick_length_base;
	tick_length_base	 = new_base;
पूर्ण

अटल अंतरभूत s64 ntp_update_offset_fll(s64 offset64, दीर्घ secs)
अणु
	समय_status &= ~STA_MODE;

	अगर (secs < MINSEC)
		वापस 0;

	अगर (!(समय_status & STA_FLL) && (secs <= MAXSEC))
		वापस 0;

	समय_status |= STA_MODE;

	वापस भाग64_दीर्घ(offset64 << (NTP_SCALE_SHIFT - SHIFT_FLL), secs);
पूर्ण

अटल व्योम ntp_update_offset(दीर्घ offset)
अणु
	s64 freq_adj;
	s64 offset64;
	दीर्घ secs;

	अगर (!(समय_status & STA_PLL))
		वापस;

	अगर (!(समय_status & STA_न_अंकO)) अणु
		/* Make sure the multiplication below won't overflow */
		offset = clamp(offset, -USEC_PER_SEC, USEC_PER_SEC);
		offset *= NSEC_PER_USEC;
	पूर्ण

	/*
	 * Scale the phase adjusपंचांगent and
	 * clamp to the operating range.
	 */
	offset = clamp(offset, -MAXPHASE, MAXPHASE);

	/*
	 * Select how the frequency is to be controlled
	 * and in which mode (PLL or FLL).
	 */
	secs = (दीर्घ)(__kसमय_get_real_seconds() - समय_refसमय);
	अगर (unlikely(समय_status & STA_FREQHOLD))
		secs = 0;

	समय_refसमय = __kसमय_get_real_seconds();

	offset64    = offset;
	freq_adj    = ntp_update_offset_fll(offset64, secs);

	/*
	 * Clamp update पूर्णांकerval to reduce PLL gain with low
	 * sampling rate (e.g. पूर्णांकermittent network connection)
	 * to aव्योम instability.
	 */
	अगर (unlikely(secs > 1 << (SHIFT_PLL + 1 + समय_स्थिरant)))
		secs = 1 << (SHIFT_PLL + 1 + समय_स्थिरant);

	freq_adj    += (offset64 * secs) <<
			(NTP_SCALE_SHIFT - 2 * (SHIFT_PLL + 2 + समय_स्थिरant));

	freq_adj    = min(freq_adj + समय_freq, MAXFREQ_SCALED);

	समय_freq   = max(freq_adj, -MAXFREQ_SCALED);

	समय_offset = भाग_s64(offset64 << NTP_SCALE_SHIFT, NTP_INTERVAL_FREQ);
पूर्ण

/**
 * ntp_clear - Clears the NTP state variables
 */
व्योम ntp_clear(व्योम)
अणु
	समय_adjust	= 0;		/* stop active adjसमय() */
	समय_status	|= STA_UNSYNC;
	समय_maxerror	= NTP_PHASE_LIMIT;
	समय_esterror	= NTP_PHASE_LIMIT;

	ntp_update_frequency();

	tick_length	= tick_length_base;
	समय_offset	= 0;

	ntp_next_leap_sec = TIME64_MAX;
	/* Clear PPS state variables */
	pps_clear();
पूर्ण


u64 ntp_tick_length(व्योम)
अणु
	वापस tick_length;
पूर्ण

/**
 * ntp_get_next_leap - Returns the next leapsecond in CLOCK_REALTIME kसमय_प्रकार
 *
 * Provides the समय of the next leapsecond against CLOCK_REALTIME in
 * a kसमय_प्रकार क्रमmat. Returns KTIME_MAX अगर no leapsecond is pending.
 */
kसमय_प्रकार ntp_get_next_leap(व्योम)
अणु
	kसमय_प्रकार ret;

	अगर ((समय_state == TIME_INS) && (समय_status & STA_INS))
		वापस kसमय_set(ntp_next_leap_sec, 0);
	ret = KTIME_MAX;
	वापस ret;
पूर्ण

/*
 * this routine handles the overflow of the microsecond field
 *
 * The tricky bits of code to handle the accurate घड़ी support
 * were provided by Dave Mills (Mills@UDEL.EDU) of NTP fame.
 * They were originally developed क्रम SUN and DEC kernels.
 * All the kuकरोs should go to Dave क्रम this stuff.
 *
 * Also handles leap second processing, and वापसs leap offset
 */
पूर्णांक second_overflow(समय64_t secs)
अणु
	s64 delta;
	पूर्णांक leap = 0;
	s32 rem;

	/*
	 * Leap second processing. If in leap-insert state at the end of the
	 * day, the प्रणाली घड़ी is set back one second; अगर in leap-delete
	 * state, the प्रणाली घड़ी is set ahead one second.
	 */
	चयन (समय_state) अणु
	हाल TIME_OK:
		अगर (समय_status & STA_INS) अणु
			समय_state = TIME_INS;
			भाग_s64_rem(secs, SECS_PER_DAY, &rem);
			ntp_next_leap_sec = secs + SECS_PER_DAY - rem;
		पूर्ण अन्यथा अगर (समय_status & STA_DEL) अणु
			समय_state = TIME_DEL;
			भाग_s64_rem(secs + 1, SECS_PER_DAY, &rem);
			ntp_next_leap_sec = secs + SECS_PER_DAY - rem;
		पूर्ण
		अवरोध;
	हाल TIME_INS:
		अगर (!(समय_status & STA_INS)) अणु
			ntp_next_leap_sec = TIME64_MAX;
			समय_state = TIME_OK;
		पूर्ण अन्यथा अगर (secs == ntp_next_leap_sec) अणु
			leap = -1;
			समय_state = TIME_OOP;
			prपूर्णांकk(KERN_NOTICE
				"Clock: inserting leap second 23:59:60 UTC\n");
		पूर्ण
		अवरोध;
	हाल TIME_DEL:
		अगर (!(समय_status & STA_DEL)) अणु
			ntp_next_leap_sec = TIME64_MAX;
			समय_state = TIME_OK;
		पूर्ण अन्यथा अगर (secs == ntp_next_leap_sec) अणु
			leap = 1;
			ntp_next_leap_sec = TIME64_MAX;
			समय_state = TIME_WAIT;
			prपूर्णांकk(KERN_NOTICE
				"Clock: deleting leap second 23:59:59 UTC\n");
		पूर्ण
		अवरोध;
	हाल TIME_OOP:
		ntp_next_leap_sec = TIME64_MAX;
		समय_state = TIME_WAIT;
		अवरोध;
	हाल TIME_WAIT:
		अगर (!(समय_status & (STA_INS | STA_DEL)))
			समय_state = TIME_OK;
		अवरोध;
	पूर्ण


	/* Bump the maxerror field */
	समय_maxerror += MAXFREQ / NSEC_PER_USEC;
	अगर (समय_maxerror > NTP_PHASE_LIMIT) अणु
		समय_maxerror = NTP_PHASE_LIMIT;
		समय_status |= STA_UNSYNC;
	पूर्ण

	/* Compute the phase adjusपंचांगent क्रम the next second */
	tick_length	 = tick_length_base;

	delta		 = ntp_offset_chunk(समय_offset);
	समय_offset	-= delta;
	tick_length	+= delta;

	/* Check PPS संकेत */
	pps_dec_valid();

	अगर (!समय_adjust)
		जाओ out;

	अगर (समय_adjust > MAX_TICKADJ) अणु
		समय_adjust -= MAX_TICKADJ;
		tick_length += MAX_TICKADJ_SCALED;
		जाओ out;
	पूर्ण

	अगर (समय_adjust < -MAX_TICKADJ) अणु
		समय_adjust += MAX_TICKADJ;
		tick_length -= MAX_TICKADJ_SCALED;
		जाओ out;
	पूर्ण

	tick_length += (s64)(समय_adjust * NSEC_PER_USEC / NTP_INTERVAL_FREQ)
							 << NTP_SCALE_SHIFT;
	समय_adjust = 0;

out:
	वापस leap;
पूर्ण

#अगर defined(CONFIG_GENERIC_CMOS_UPDATE) || defined(CONFIG_RTC_SYSTOHC)
अटल व्योम sync_hw_घड़ी(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(sync_work, sync_hw_घड़ी);
अटल काष्ठा hrसमयr sync_hrसमयr;
#घोषणा SYNC_PERIOD_NS (11ULL * 60 * NSEC_PER_SEC)

अटल क्रमागत hrसमयr_restart sync_समयr_callback(काष्ठा hrसमयr *समयr)
अणु
	queue_work(प्रणाली_मुक्तzable_घातer_efficient_wq, &sync_work);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम sched_sync_hw_घड़ी(अचिन्हित दीर्घ offset_nsec, bool retry)
अणु
	kसमय_प्रकार exp = kसमय_set(kसमय_get_real_seconds(), 0);

	अगर (retry)
		exp = kसमय_add_ns(exp, 2ULL * NSEC_PER_SEC - offset_nsec);
	अन्यथा
		exp = kसमय_add_ns(exp, SYNC_PERIOD_NS - offset_nsec);

	hrसमयr_start(&sync_hrसमयr, exp, HRTIMER_MODE_ABS);
पूर्ण

/*
 * Check whether @now is correct versus the required समय to update the RTC
 * and calculate the value which needs to be written to the RTC so that the
 * next seconds increment of the RTC after the ग_लिखो is aligned with the next
 * seconds increment of घड़ी REALTIME.
 *
 * tsched     t1 ग_लिखो(t2.tv_sec - 1sec))	t2 RTC increments seconds
 *
 * t2.tv_nsec == 0
 * tsched = t2 - set_offset_nsec
 * newval = t2 - NSEC_PER_SEC
 *
 * ==> neval = tsched + set_offset_nsec - NSEC_PER_SEC
 *
 * As the execution of this code is not guaranteed to happen exactly at
 * tsched this allows it to happen within a fuzzy region:
 *
 *	असल(now - tsched) < FUZZ
 *
 * If @now is not inside the allowed winकरोw the function वापसs false.
 */
अटल अंतरभूत bool rtc_tv_nsec_ok(अचिन्हित दीर्घ set_offset_nsec,
				  काष्ठा बारpec64 *to_set,
				  स्थिर काष्ठा बारpec64 *now)
अणु
	/* Allowed error in tv_nsec, arbitrarily set to 5 jअगरfies in ns. */
	स्थिर अचिन्हित दीर्घ TIME_SET_NSEC_FUZZ = TICK_NSEC * 5;
	काष्ठा बारpec64 delay = अणु.tv_sec = -1,
				   .tv_nsec = set_offset_nsecपूर्ण;

	*to_set = बारpec64_add(*now, delay);

	अगर (to_set->tv_nsec < TIME_SET_NSEC_FUZZ) अणु
		to_set->tv_nsec = 0;
		वापस true;
	पूर्ण

	अगर (to_set->tv_nsec > NSEC_PER_SEC - TIME_SET_NSEC_FUZZ) अणु
		to_set->tv_sec++;
		to_set->tv_nsec = 0;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_GENERIC_CMOS_UPDATE
पूर्णांक __weak update_persistent_घड़ी64(काष्ठा बारpec64 now64)
अणु
	वापस -ENODEV;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक update_persistent_घड़ी64(काष्ठा बारpec64 now64)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_RTC_SYSTOHC
/* Save NTP synchronized समय to the RTC */
अटल पूर्णांक update_rtc(काष्ठा बारpec64 *to_set, अचिन्हित दीर्घ *offset_nsec)
अणु
	काष्ठा rtc_device *rtc;
	काष्ठा rtc_समय पंचांग;
	पूर्णांक err = -ENODEV;

	rtc = rtc_class_खोलो(CONFIG_RTC_SYSTOHC_DEVICE);
	अगर (!rtc)
		वापस -ENODEV;

	अगर (!rtc->ops || !rtc->ops->set_समय)
		जाओ out_बंद;

	/* First call might not have the correct offset */
	अगर (*offset_nsec == rtc->set_offset_nsec) अणु
		rtc_समय64_to_पंचांग(to_set->tv_sec, &पंचांग);
		err = rtc_set_समय(rtc, &पंचांग);
	पूर्ण अन्यथा अणु
		/* Store the update offset and let the caller try again */
		*offset_nsec = rtc->set_offset_nsec;
		err = -EAGAIN;
	पूर्ण
out_बंद:
	rtc_class_बंद(rtc);
	वापस err;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक update_rtc(काष्ठा बारpec64 *to_set, अचिन्हित दीर्घ *offset_nsec)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

/*
 * If we have an बाह्यally synchronized Linux घड़ी, then update RTC घड़ी
 * accordingly every ~11 minutes. Generally RTCs can only store second
 * precision, but many RTCs will adjust the phase of their second tick to
 * match the moment of update. This infraकाष्ठाure arranges to call to the RTC
 * set at the correct moment to phase synchronize the RTC second tick over
 * with the kernel घड़ी.
 */
अटल व्योम sync_hw_घड़ी(काष्ठा work_काष्ठा *work)
अणु
	/*
	 * The शेष synchronization offset is 500ms क्रम the deprecated
	 * update_persistent_घड़ी64() under the assumption that it uses
	 * the infamous CMOS घड़ी (MC146818).
	 */
	अटल अचिन्हित दीर्घ offset_nsec = NSEC_PER_SEC / 2;
	काष्ठा बारpec64 now, to_set;
	पूर्णांक res = -EAGAIN;

	/*
	 * Don't update अगर STA_UNSYNC is set and अगर ntp_notअगरy_cmos_समयr()
	 * managed to schedule the work between the समयr firing and the
	 * work being able to rearm the समयr. Wait क्रम the समयr to expire.
	 */
	अगर (!ntp_synced() || hrसमयr_is_queued(&sync_hrसमयr))
		वापस;

	kसमय_get_real_ts64(&now);
	/* If @now is not in the allowed winकरोw, try again */
	अगर (!rtc_tv_nsec_ok(offset_nsec, &to_set, &now))
		जाओ rearm;

	/* Take समयzone adjusted RTCs पूर्णांकo account */
	अगर (persistent_घड़ी_is_local)
		to_set.tv_sec -= (sys_tz.tz_minuteswest * 60);

	/* Try the legacy RTC first. */
	res = update_persistent_घड़ी64(to_set);
	अगर (res != -ENODEV)
		जाओ rearm;

	/* Try the RTC class */
	res = update_rtc(&to_set, &offset_nsec);
	अगर (res == -ENODEV)
		वापस;
rearm:
	sched_sync_hw_घड़ी(offset_nsec, res != 0);
पूर्ण

व्योम ntp_notअगरy_cmos_समयr(व्योम)
अणु
	/*
	 * When the work is currently executed but has not yet the समयr
	 * rearmed this queues the work immediately again. No big issue,
	 * just a poपूर्णांकless work scheduled.
	 */
	अगर (ntp_synced() && !hrसमयr_is_queued(&sync_hrसमयr))
		queue_work(प्रणाली_मुक्तzable_घातer_efficient_wq, &sync_work);
पूर्ण

अटल व्योम __init ntp_init_cmos_sync(व्योम)
अणु
	hrसमयr_init(&sync_hrसमयr, CLOCK_REALTIME, HRTIMER_MODE_ABS);
	sync_hrसमयr.function = sync_समयr_callback;
पूर्ण
#अन्यथा /* CONFIG_GENERIC_CMOS_UPDATE) || defined(CONFIG_RTC_SYSTOHC) */
अटल अंतरभूत व्योम __init ntp_init_cmos_sync(व्योम) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_GENERIC_CMOS_UPDATE) || defined(CONFIG_RTC_SYSTOHC) */

/*
 * Propagate a new txc->status value पूर्णांकo the NTP state:
 */
अटल अंतरभूत व्योम process_adj_status(स्थिर काष्ठा __kernel_समयx *txc)
अणु
	अगर ((समय_status & STA_PLL) && !(txc->status & STA_PLL)) अणु
		समय_state = TIME_OK;
		समय_status = STA_UNSYNC;
		ntp_next_leap_sec = TIME64_MAX;
		/* restart PPS frequency calibration */
		pps_reset_freq_पूर्णांकerval();
	पूर्ण

	/*
	 * If we turn on PLL adjusपंचांगents then reset the
	 * reference समय to current समय.
	 */
	अगर (!(समय_status & STA_PLL) && (txc->status & STA_PLL))
		समय_refसमय = __kसमय_get_real_seconds();

	/* only set allowed bits */
	समय_status &= STA_RONLY;
	समय_status |= txc->status & ~STA_RONLY;
पूर्ण


अटल अंतरभूत व्योम process_adjसमयx_modes(स्थिर काष्ठा __kernel_समयx *txc,
					  s32 *समय_प्रकारai)
अणु
	अगर (txc->modes & ADJ_STATUS)
		process_adj_status(txc);

	अगर (txc->modes & ADJ_न_अंकO)
		समय_status |= STA_न_अंकO;

	अगर (txc->modes & ADJ_MICRO)
		समय_status &= ~STA_न_अंकO;

	अगर (txc->modes & ADJ_FREQUENCY) अणु
		समय_freq = txc->freq * PPM_SCALE;
		समय_freq = min(समय_freq, MAXFREQ_SCALED);
		समय_freq = max(समय_freq, -MAXFREQ_SCALED);
		/* update pps_freq */
		pps_set_freq(समय_freq);
	पूर्ण

	अगर (txc->modes & ADJ_MAXERROR)
		समय_maxerror = txc->maxerror;

	अगर (txc->modes & ADJ_ESTERROR)
		समय_esterror = txc->esterror;

	अगर (txc->modes & ADJ_TIMECONST) अणु
		समय_स्थिरant = txc->स्थिरant;
		अगर (!(समय_status & STA_न_अंकO))
			समय_स्थिरant += 4;
		समय_स्थिरant = min(समय_स्थिरant, (दीर्घ)MAXTC);
		समय_स्थिरant = max(समय_स्थिरant, 0l);
	पूर्ण

	अगर (txc->modes & ADJ_TAI &&
			txc->स्थिरant >= 0 && txc->स्थिरant <= MAX_TAI_OFFSET)
		*समय_प्रकारai = txc->स्थिरant;

	अगर (txc->modes & ADJ_OFFSET)
		ntp_update_offset(txc->offset);

	अगर (txc->modes & ADJ_TICK)
		tick_usec = txc->tick;

	अगर (txc->modes & (ADJ_TICK|ADJ_FREQUENCY|ADJ_OFFSET))
		ntp_update_frequency();
पूर्ण


/*
 * adjसमयx मुख्यly allows पढ़ोing (and writing, अगर superuser) of
 * kernel समय-keeping variables. used by xntpd.
 */
पूर्णांक __करो_adjसमयx(काष्ठा __kernel_समयx *txc, स्थिर काष्ठा बारpec64 *ts,
		  s32 *समय_प्रकारai, काष्ठा audit_ntp_data *ad)
अणु
	पूर्णांक result;

	अगर (txc->modes & ADJ_ADJTIME) अणु
		दीर्घ save_adjust = समय_adjust;

		अगर (!(txc->modes & ADJ_OFFSET_READONLY)) अणु
			/* adjसमय() is independent from ntp_adjसमय() */
			समय_adjust = txc->offset;
			ntp_update_frequency();

			audit_ntp_set_old(ad, AUDIT_NTP_ADJUST,	save_adjust);
			audit_ntp_set_new(ad, AUDIT_NTP_ADJUST,	समय_adjust);
		पूर्ण
		txc->offset = save_adjust;
	पूर्ण अन्यथा अणु
		/* If there are input parameters, then process them: */
		अगर (txc->modes) अणु
			audit_ntp_set_old(ad, AUDIT_NTP_OFFSET,	समय_offset);
			audit_ntp_set_old(ad, AUDIT_NTP_FREQ,	समय_freq);
			audit_ntp_set_old(ad, AUDIT_NTP_STATUS,	समय_status);
			audit_ntp_set_old(ad, AUDIT_NTP_TAI,	*समय_प्रकारai);
			audit_ntp_set_old(ad, AUDIT_NTP_TICK,	tick_usec);

			process_adjसमयx_modes(txc, समय_प्रकारai);

			audit_ntp_set_new(ad, AUDIT_NTP_OFFSET,	समय_offset);
			audit_ntp_set_new(ad, AUDIT_NTP_FREQ,	समय_freq);
			audit_ntp_set_new(ad, AUDIT_NTP_STATUS,	समय_status);
			audit_ntp_set_new(ad, AUDIT_NTP_TAI,	*समय_प्रकारai);
			audit_ntp_set_new(ad, AUDIT_NTP_TICK,	tick_usec);
		पूर्ण

		txc->offset = shअगरt_right(समय_offset * NTP_INTERVAL_FREQ,
				  NTP_SCALE_SHIFT);
		अगर (!(समय_status & STA_न_अंकO))
			txc->offset = (u32)txc->offset / NSEC_PER_USEC;
	पूर्ण

	result = समय_state;	/* mostly `TIME_OK' */
	/* check क्रम errors */
	अगर (is_error_status(समय_status))
		result = TIME_ERROR;

	txc->freq	   = shअगरt_right((समय_freq >> PPM_SCALE_INV_SHIFT) *
					 PPM_SCALE_INV, NTP_SCALE_SHIFT);
	txc->maxerror	   = समय_maxerror;
	txc->esterror	   = समय_esterror;
	txc->status	   = समय_status;
	txc->स्थिरant	   = समय_स्थिरant;
	txc->precision	   = 1;
	txc->tolerance	   = MAXFREQ_SCALED / PPM_SCALE;
	txc->tick	   = tick_usec;
	txc->tai	   = *समय_प्रकारai;

	/* fill PPS status fields */
	pps_fill_समयx(txc);

	txc->समय.tv_sec = ts->tv_sec;
	txc->समय.tv_usec = ts->tv_nsec;
	अगर (!(समय_status & STA_न_अंकO))
		txc->समय.tv_usec = ts->tv_nsec / NSEC_PER_USEC;

	/* Handle leapsec adjusपंचांगents */
	अगर (unlikely(ts->tv_sec >= ntp_next_leap_sec)) अणु
		अगर ((समय_state == TIME_INS) && (समय_status & STA_INS)) अणु
			result = TIME_OOP;
			txc->tai++;
			txc->समय.tv_sec--;
		पूर्ण
		अगर ((समय_state == TIME_DEL) && (समय_status & STA_DEL)) अणु
			result = TIME_WAIT;
			txc->tai--;
			txc->समय.tv_sec++;
		पूर्ण
		अगर ((समय_state == TIME_OOP) &&
					(ts->tv_sec == ntp_next_leap_sec)) अणु
			result = TIME_WAIT;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

#अगर_घोषित	CONFIG_NTP_PPS

/* actually काष्ठा pps_normसमय is good old काष्ठा बारpec, but it is
 * semantically dअगरferent (and it is the reason why it was invented):
 * pps_normसमय.nsec has a range of ( -NSEC_PER_SEC / 2, NSEC_PER_SEC / 2 ]
 * जबतक बारpec.tv_nsec has a range of [0, NSEC_PER_SEC) */
काष्ठा pps_normसमय अणु
	s64		sec;	/* seconds */
	दीर्घ		nsec;	/* nanoseconds */
पूर्ण;

/* normalize the बारtamp so that nsec is in the
   ( -NSEC_PER_SEC / 2, NSEC_PER_SEC / 2 ] पूर्णांकerval */
अटल अंतरभूत काष्ठा pps_normसमय pps_normalize_ts(काष्ठा बारpec64 ts)
अणु
	काष्ठा pps_normसमय norm = अणु
		.sec = ts.tv_sec,
		.nsec = ts.tv_nsec
	पूर्ण;

	अगर (norm.nsec > (NSEC_PER_SEC >> 1)) अणु
		norm.nsec -= NSEC_PER_SEC;
		norm.sec++;
	पूर्ण

	वापस norm;
पूर्ण

/* get current phase correction and jitter */
अटल अंतरभूत दीर्घ pps_phase_filter_get(दीर्घ *jitter)
अणु
	*jitter = pps_tf[0] - pps_tf[1];
	अगर (*jitter < 0)
		*jitter = -*jitter;

	/* TODO: test various filters */
	वापस pps_tf[0];
पूर्ण

/* add the sample to the phase filter */
अटल अंतरभूत व्योम pps_phase_filter_add(दीर्घ err)
अणु
	pps_tf[2] = pps_tf[1];
	pps_tf[1] = pps_tf[0];
	pps_tf[0] = err;
पूर्ण

/* decrease frequency calibration पूर्णांकerval length.
 * It is halved after four consecutive unstable पूर्णांकervals.
 */
अटल अंतरभूत व्योम pps_dec_freq_पूर्णांकerval(व्योम)
अणु
	अगर (--pps_पूर्णांकcnt <= -PPS_INTCOUNT) अणु
		pps_पूर्णांकcnt = -PPS_INTCOUNT;
		अगर (pps_shअगरt > PPS_INTMIN) अणु
			pps_shअगरt--;
			pps_पूर्णांकcnt = 0;
		पूर्ण
	पूर्ण
पूर्ण

/* increase frequency calibration पूर्णांकerval length.
 * It is द्विगुनd after four consecutive stable पूर्णांकervals.
 */
अटल अंतरभूत व्योम pps_inc_freq_पूर्णांकerval(व्योम)
अणु
	अगर (++pps_पूर्णांकcnt >= PPS_INTCOUNT) अणु
		pps_पूर्णांकcnt = PPS_INTCOUNT;
		अगर (pps_shअगरt < PPS_INTMAX) अणु
			pps_shअगरt++;
			pps_पूर्णांकcnt = 0;
		पूर्ण
	पूर्ण
पूर्ण

/* update घड़ी frequency based on MONOTONIC_RAW घड़ी PPS संकेत
 * बारtamps
 *
 * At the end of the calibration पूर्णांकerval the dअगरference between the
 * first and last MONOTONIC_RAW घड़ी बारtamps भागided by the length
 * of the पूर्णांकerval becomes the frequency update. If the पूर्णांकerval was
 * too दीर्घ, the data are discarded.
 * Returns the dअगरference between old and new frequency values.
 */
अटल दीर्घ hardpps_update_freq(काष्ठा pps_normसमय freq_norm)
अणु
	दीर्घ delta, delta_mod;
	s64 ftemp;

	/* check अगर the frequency पूर्णांकerval was too दीर्घ */
	अगर (freq_norm.sec > (2 << pps_shअगरt)) अणु
		समय_status |= STA_PPSERROR;
		pps_errcnt++;
		pps_dec_freq_पूर्णांकerval();
		prपूर्णांकk_deferred(KERN_ERR
			"hardpps: PPSERROR: interval too long - %lld s\n",
			freq_norm.sec);
		वापस 0;
	पूर्ण

	/* here the raw frequency offset and wander (stability) is
	 * calculated. If the wander is less than the wander threshold
	 * the पूर्णांकerval is increased; otherwise it is decreased.
	 */
	ftemp = भाग_s64(((s64)(-freq_norm.nsec)) << NTP_SCALE_SHIFT,
			freq_norm.sec);
	delta = shअगरt_right(ftemp - pps_freq, NTP_SCALE_SHIFT);
	pps_freq = ftemp;
	अगर (delta > PPS_MAXWANDER || delta < -PPS_MAXWANDER) अणु
		prपूर्णांकk_deferred(KERN_WARNING
				"hardpps: PPSWANDER: change=%ld\n", delta);
		समय_status |= STA_PPSWANDER;
		pps_stbcnt++;
		pps_dec_freq_पूर्णांकerval();
	पूर्ण अन्यथा अणु	/* good sample */
		pps_inc_freq_पूर्णांकerval();
	पूर्ण

	/* the stability metric is calculated as the average of recent
	 * frequency changes, but is used only क्रम perक्रमmance
	 * monitoring
	 */
	delta_mod = delta;
	अगर (delta_mod < 0)
		delta_mod = -delta_mod;
	pps_stabil += (भाग_s64(((s64)delta_mod) <<
				(NTP_SCALE_SHIFT - SHIFT_USEC),
				NSEC_PER_USEC) - pps_stabil) >> PPS_INTMIN;

	/* अगर enabled, the प्रणाली घड़ी frequency is updated */
	अगर ((समय_status & STA_PPSFREQ) != 0 &&
	    (समय_status & STA_FREQHOLD) == 0) अणु
		समय_freq = pps_freq;
		ntp_update_frequency();
	पूर्ण

	वापस delta;
पूर्ण

/* correct REALTIME घड़ी phase error against PPS संकेत */
अटल व्योम hardpps_update_phase(दीर्घ error)
अणु
	दीर्घ correction = -error;
	दीर्घ jitter;

	/* add the sample to the median filter */
	pps_phase_filter_add(correction);
	correction = pps_phase_filter_get(&jitter);

	/* Nominal jitter is due to PPS संकेत noise. If it exceeds the
	 * threshold, the sample is discarded; otherwise, अगर so enabled,
	 * the समय offset is updated.
	 */
	अगर (jitter > (pps_jitter << PPS_POPCORN)) अणु
		prपूर्णांकk_deferred(KERN_WARNING
				"hardpps: PPSJITTER: jitter=%ld, limit=%ld\n",
				jitter, (pps_jitter << PPS_POPCORN));
		समय_status |= STA_PPSJITTER;
		pps_jitcnt++;
	पूर्ण अन्यथा अगर (समय_status & STA_PPSTIME) अणु
		/* correct the समय using the phase offset */
		समय_offset = भाग_s64(((s64)correction) << NTP_SCALE_SHIFT,
				NTP_INTERVAL_FREQ);
		/* cancel running adjसमय() */
		समय_adjust = 0;
	पूर्ण
	/* update jitter */
	pps_jitter += (jitter - pps_jitter) >> PPS_INTMIN;
पूर्ण

/*
 * __hardpps() - discipline CPU घड़ी oscillator to बाह्यal PPS संकेत
 *
 * This routine is called at each PPS संकेत arrival in order to
 * discipline the CPU घड़ी oscillator to the PPS संकेत. It takes two
 * parameters: REALTIME and MONOTONIC_RAW घड़ी बारtamps. The क्रमmer
 * is used to correct घड़ी phase error and the latter is used to
 * correct the frequency.
 *
 * This code is based on David Mills's reference nanokernel
 * implementation. It was mostly rewritten but keeps the same idea.
 */
व्योम __hardpps(स्थिर काष्ठा बारpec64 *phase_ts, स्थिर काष्ठा बारpec64 *raw_ts)
अणु
	काष्ठा pps_normसमय pts_norm, freq_norm;

	pts_norm = pps_normalize_ts(*phase_ts);

	/* clear the error bits, they will be set again अगर needed */
	समय_status &= ~(STA_PPSJITTER | STA_PPSWANDER | STA_PPSERROR);

	/* indicate संकेत presence */
	समय_status |= STA_PPSSIGNAL;
	pps_valid = PPS_VALID;

	/* when called क्रम the first समय,
	 * just start the frequency पूर्णांकerval */
	अगर (unlikely(pps_fbase.tv_sec == 0)) अणु
		pps_fbase = *raw_ts;
		वापस;
	पूर्ण

	/* ok, now we have a base क्रम frequency calculation */
	freq_norm = pps_normalize_ts(बारpec64_sub(*raw_ts, pps_fbase));

	/* check that the संकेत is in the range
	 * [1s - MAXFREQ us, 1s + MAXFREQ us], otherwise reject it */
	अगर ((freq_norm.sec == 0) ||
			(freq_norm.nsec > MAXFREQ * freq_norm.sec) ||
			(freq_norm.nsec < -MAXFREQ * freq_norm.sec)) अणु
		समय_status |= STA_PPSJITTER;
		/* restart the frequency calibration पूर्णांकerval */
		pps_fbase = *raw_ts;
		prपूर्णांकk_deferred(KERN_ERR "hardpps: PPSJITTER: bad pulse\n");
		वापस;
	पूर्ण

	/* संकेत is ok */

	/* check अगर the current frequency पूर्णांकerval is finished */
	अगर (freq_norm.sec >= (1 << pps_shअगरt)) अणु
		pps_calcnt++;
		/* restart the frequency calibration पूर्णांकerval */
		pps_fbase = *raw_ts;
		hardpps_update_freq(freq_norm);
	पूर्ण

	hardpps_update_phase(pts_norm.nsec);

पूर्ण
#पूर्ण_अगर	/* CONFIG_NTP_PPS */

अटल पूर्णांक __init ntp_tick_adj_setup(अक्षर *str)
अणु
	पूर्णांक rc = kstrtos64(str, 0, &ntp_tick_adj);
	अगर (rc)
		वापस rc;

	ntp_tick_adj <<= NTP_SCALE_SHIFT;
	वापस 1;
पूर्ण

__setup("ntp_tick_adj=", ntp_tick_adj_setup);

व्योम __init ntp_init(व्योम)
अणु
	ntp_clear();
	ntp_init_cmos_sync();
पूर्ण
