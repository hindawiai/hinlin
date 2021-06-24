<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Kernel समयkeeping code and accessor functions. Based on code from
 *  समयr.c, moved in commit 8524070b7982.
 */
#समावेश <linux/समयkeeper_पूर्णांकernal.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/percpu.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/nmi.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समय.स>
#समावेश <linux/tick.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/pvघड़ी_gtod.h>
#समावेश <linux/compiler.h>
#समावेश <linux/audit.h>

#समावेश "tick-internal.h"
#समावेश "ntp_internal.h"
#समावेश "timekeeping_internal.h"

#घोषणा TK_CLEAR_NTP		(1 << 0)
#घोषणा TK_MIRROR		(1 << 1)
#घोषणा TK_CLOCK_WAS_SET	(1 << 2)

क्रमागत समयkeeping_adv_mode अणु
	/* Update समयkeeper when a tick has passed */
	TK_ADV_TICK,

	/* Update समयkeeper on a direct frequency change */
	TK_ADV_FREQ
पूर्ण;

DEFINE_RAW_SPINLOCK(समयkeeper_lock);

/*
 * The most important data क्रम पढ़ोout fits पूर्णांकo a single 64 byte
 * cache line.
 */
अटल काष्ठा अणु
	seqcount_raw_spinlock_t	seq;
	काष्ठा समयkeeper	समयkeeper;
पूर्ण tk_core ____cacheline_aligned = अणु
	.seq = SEQCNT_RAW_SPINLOCK_ZERO(tk_core.seq, &समयkeeper_lock),
पूर्ण;

अटल काष्ठा समयkeeper shaकरोw_समयkeeper;

/* flag क्रम अगर समयkeeping is suspended */
पूर्णांक __पढ़ो_mostly समयkeeping_suspended;

/**
 * काष्ठा tk_fast - NMI safe समयkeeper
 * @seq:	Sequence counter क्रम protecting updates. The lowest bit
 *		is the index क्रम the tk_पढ़ो_base array
 * @base:	tk_पढ़ो_base array. Access is indexed by the lowest bit of
 *		@seq.
 *
 * See @update_fast_समयkeeper() below.
 */
काष्ठा tk_fast अणु
	seqcount_latch_t	seq;
	काष्ठा tk_पढ़ो_base	base[2];
पूर्ण;

/* Suspend-समय cycles value क्रम halted fast समयkeeper. */
अटल u64 cycles_at_suspend;

अटल u64 dummy_घड़ी_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	अगर (समयkeeping_suspended)
		वापस cycles_at_suspend;
	वापस local_घड़ी();
पूर्ण

अटल काष्ठा घड़ीsource dummy_घड़ी = अणु
	.पढ़ो = dummy_घड़ी_पढ़ो,
पूर्ण;

/*
 * Boot समय initialization which allows local_घड़ी() to be utilized
 * during early boot when घड़ीsources are not available. local_घड़ी()
 * वापसs nanoseconds alपढ़ोy so no conversion is required, hence mult=1
 * and shअगरt=0. When the first proper घड़ीsource is installed then
 * the fast समय keepers are updated with the correct values.
 */
#घोषणा FAST_TK_INIT						\
	अणु							\
		.घड़ी		= &dummy_घड़ी,			\
		.mask		= CLOCKSOURCE_MASK(64),		\
		.mult		= 1,				\
		.shअगरt		= 0,				\
	पूर्ण

अटल काष्ठा tk_fast tk_fast_mono ____cacheline_aligned = अणु
	.seq     = SEQCNT_LATCH_ZERO(tk_fast_mono.seq),
	.base[0] = FAST_TK_INIT,
	.base[1] = FAST_TK_INIT,
पूर्ण;

अटल काष्ठा tk_fast tk_fast_raw  ____cacheline_aligned = अणु
	.seq     = SEQCNT_LATCH_ZERO(tk_fast_raw.seq),
	.base[0] = FAST_TK_INIT,
	.base[1] = FAST_TK_INIT,
पूर्ण;

अटल अंतरभूत व्योम tk_normalize_xसमय(काष्ठा समयkeeper *tk)
अणु
	जबतक (tk->tkr_mono.xसमय_nsec >= ((u64)NSEC_PER_SEC << tk->tkr_mono.shअगरt)) अणु
		tk->tkr_mono.xसमय_nsec -= (u64)NSEC_PER_SEC << tk->tkr_mono.shअगरt;
		tk->xसमय_sec++;
	पूर्ण
	जबतक (tk->tkr_raw.xसमय_nsec >= ((u64)NSEC_PER_SEC << tk->tkr_raw.shअगरt)) अणु
		tk->tkr_raw.xसमय_nsec -= (u64)NSEC_PER_SEC << tk->tkr_raw.shअगरt;
		tk->raw_sec++;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा बारpec64 tk_xसमय(स्थिर काष्ठा समयkeeper *tk)
अणु
	काष्ठा बारpec64 ts;

	ts.tv_sec = tk->xसमय_sec;
	ts.tv_nsec = (दीर्घ)(tk->tkr_mono.xसमय_nsec >> tk->tkr_mono.shअगरt);
	वापस ts;
पूर्ण

अटल व्योम tk_set_xसमय(काष्ठा समयkeeper *tk, स्थिर काष्ठा बारpec64 *ts)
अणु
	tk->xसमय_sec = ts->tv_sec;
	tk->tkr_mono.xसमय_nsec = (u64)ts->tv_nsec << tk->tkr_mono.shअगरt;
पूर्ण

अटल व्योम tk_xसमय_add(काष्ठा समयkeeper *tk, स्थिर काष्ठा बारpec64 *ts)
अणु
	tk->xसमय_sec += ts->tv_sec;
	tk->tkr_mono.xसमय_nsec += (u64)ts->tv_nsec << tk->tkr_mono.shअगरt;
	tk_normalize_xसमय(tk);
पूर्ण

अटल व्योम tk_set_wall_to_mono(काष्ठा समयkeeper *tk, काष्ठा बारpec64 wपंचांग)
अणु
	काष्ठा बारpec64 पंचांगp;

	/*
	 * Verअगरy consistency of: offset_real = -wall_to_monotonic
	 * beक्रमe modअगरying anything
	 */
	set_normalized_बारpec64(&पंचांगp, -tk->wall_to_monotonic.tv_sec,
					-tk->wall_to_monotonic.tv_nsec);
	WARN_ON_ONCE(tk->offs_real != बारpec64_to_kसमय(पंचांगp));
	tk->wall_to_monotonic = wपंचांग;
	set_normalized_बारpec64(&पंचांगp, -wपंचांग.tv_sec, -wपंचांग.tv_nsec);
	tk->offs_real = बारpec64_to_kसमय(पंचांगp);
	tk->offs_tai = kसमय_add(tk->offs_real, kसमय_set(tk->tai_offset, 0));
पूर्ण

अटल अंतरभूत व्योम tk_update_sleep_समय(काष्ठा समयkeeper *tk, kसमय_प्रकार delta)
अणु
	tk->offs_boot = kसमय_add(tk->offs_boot, delta);
	/*
	 * Timespec representation क्रम VDSO update to aव्योम 64bit भागision
	 * on every update.
	 */
	tk->monotonic_to_boot = kसमय_प्रकारo_बारpec64(tk->offs_boot);
पूर्ण

/*
 * tk_घड़ी_पढ़ो - atomic घड़ीsource पढ़ो() helper
 *
 * This helper is necessary to use in the पढ़ो paths because, जबतक the
 * seqcount ensures we करोn't वापस a bad value जबतक काष्ठाures are updated,
 * it करोesn't protect from potential crashes. There is the possibility that
 * the tkr's घड़ीsource may change between the पढ़ो reference, and the
 * घड़ी reference passed to the पढ़ो function.  This can cause crashes अगर
 * the wrong घड़ीsource is passed to the wrong पढ़ो function.
 * This isn't necessary to use when holding the समयkeeper_lock or करोing
 * a पढ़ो of the fast-समयkeeper tkrs (which is रक्षित by its own locking
 * and update logic).
 */
अटल अंतरभूत u64 tk_घड़ी_पढ़ो(स्थिर काष्ठा tk_पढ़ो_base *tkr)
अणु
	काष्ठा घड़ीsource *घड़ी = READ_ONCE(tkr->घड़ी);

	वापस घड़ी->पढ़ो(घड़ी);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_TIMEKEEPING
#घोषणा WARNING_FREQ (HZ*300) /* 5 minute rate-limiting */

अटल व्योम समयkeeping_check_update(काष्ठा समयkeeper *tk, u64 offset)
अणु

	u64 max_cycles = tk->tkr_mono.घड़ी->max_cycles;
	स्थिर अक्षर *name = tk->tkr_mono.घड़ी->name;

	अगर (offset > max_cycles) अणु
		prपूर्णांकk_deferred("WARNING: timekeeping: Cycle offset (%lld) is larger than allowed by the '%s' clock's max_cycles value (%lld): time overflow danger\n",
				offset, name, max_cycles);
		prपूर्णांकk_deferred("         timekeeping: Your kernel is sick, but tries to cope by capping time updates\n");
	पूर्ण अन्यथा अणु
		अगर (offset > (max_cycles >> 1)) अणु
			prपूर्णांकk_deferred("INFO: timekeeping: Cycle offset (%lld) is larger than the '%s' clock's 50%% safety margin (%lld)\n",
					offset, name, max_cycles >> 1);
			prपूर्णांकk_deferred("      timekeeping: Your kernel is still fine, but is feeling a bit nervous\n");
		पूर्ण
	पूर्ण

	अगर (tk->underflow_seen) अणु
		अगर (jअगरfies - tk->last_warning > WARNING_FREQ) अणु
			prपूर्णांकk_deferred("WARNING: Underflow in clocksource '%s' observed, time update ignored.\n", name);
			prपूर्णांकk_deferred("         Please report this, consider using a different clocksource, if possible.\n");
			prपूर्णांकk_deferred("         Your kernel is probably still fine.\n");
			tk->last_warning = jअगरfies;
		पूर्ण
		tk->underflow_seen = 0;
	पूर्ण

	अगर (tk->overflow_seen) अणु
		अगर (jअगरfies - tk->last_warning > WARNING_FREQ) अणु
			prपूर्णांकk_deferred("WARNING: Overflow in clocksource '%s' observed, time update capped.\n", name);
			prपूर्णांकk_deferred("         Please report this, consider using a different clocksource, if possible.\n");
			prपूर्णांकk_deferred("         Your kernel is probably still fine.\n");
			tk->last_warning = jअगरfies;
		पूर्ण
		tk->overflow_seen = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u64 समयkeeping_get_delta(स्थिर काष्ठा tk_पढ़ो_base *tkr)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	u64 now, last, mask, max, delta;
	अचिन्हित पूर्णांक seq;

	/*
	 * Since we're called holding a seqcount, the data may shअगरt
	 * under us जबतक we're करोing the calculation. This can cause
	 * false positives, since we'd note a problem but throw the
	 * results away. So nest another seqcount here to atomically
	 * grab the poपूर्णांकs we are checking with.
	 */
	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);
		now = tk_घड़ी_पढ़ो(tkr);
		last = tkr->cycle_last;
		mask = tkr->mask;
		max = tkr->घड़ी->max_cycles;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	delta = घड़ीsource_delta(now, last, mask);

	/*
	 * Try to catch underflows by checking अगर we are seeing small
	 * mask-relative negative values.
	 */
	अगर (unlikely((~delta & mask) < (mask >> 3))) अणु
		tk->underflow_seen = 1;
		delta = 0;
	पूर्ण

	/* Cap delta value to the max_cycles values to aव्योम mult overflows */
	अगर (unlikely(delta > max)) अणु
		tk->overflow_seen = 1;
		delta = tkr->घड़ी->max_cycles;
	पूर्ण

	वापस delta;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम समयkeeping_check_update(काष्ठा समयkeeper *tk, u64 offset)
अणु
पूर्ण
अटल अंतरभूत u64 समयkeeping_get_delta(स्थिर काष्ठा tk_पढ़ो_base *tkr)
अणु
	u64 cycle_now, delta;

	/* पढ़ो घड़ीsource */
	cycle_now = tk_घड़ी_पढ़ो(tkr);

	/* calculate the delta since the last update_wall_समय */
	delta = घड़ीsource_delta(cycle_now, tkr->cycle_last, tkr->mask);

	वापस delta;
पूर्ण
#पूर्ण_अगर

/**
 * tk_setup_पूर्णांकernals - Set up पूर्णांकernals to use घड़ीsource घड़ी.
 *
 * @tk:		The target समयkeeper to setup.
 * @घड़ी:		Poपूर्णांकer to घड़ीsource.
 *
 * Calculates a fixed cycle/nsec पूर्णांकerval क्रम a given घड़ीsource/adjusपंचांगent
 * pair and पूर्णांकerval request.
 *
 * Unless you're the समयkeeping code, you should not be using this!
 */
अटल व्योम tk_setup_पूर्णांकernals(काष्ठा समयkeeper *tk, काष्ठा घड़ीsource *घड़ी)
अणु
	u64 पूर्णांकerval;
	u64 पंचांगp, ntpपूर्णांकerval;
	काष्ठा घड़ीsource *old_घड़ी;

	++tk->cs_was_changed_seq;
	old_घड़ी = tk->tkr_mono.घड़ी;
	tk->tkr_mono.घड़ी = घड़ी;
	tk->tkr_mono.mask = घड़ी->mask;
	tk->tkr_mono.cycle_last = tk_घड़ी_पढ़ो(&tk->tkr_mono);

	tk->tkr_raw.घड़ी = घड़ी;
	tk->tkr_raw.mask = घड़ी->mask;
	tk->tkr_raw.cycle_last = tk->tkr_mono.cycle_last;

	/* Do the ns -> cycle conversion first, using original mult */
	पंचांगp = NTP_INTERVAL_LENGTH;
	पंचांगp <<= घड़ी->shअगरt;
	ntpपूर्णांकerval = पंचांगp;
	पंचांगp += घड़ी->mult/2;
	करो_भाग(पंचांगp, घड़ी->mult);
	अगर (पंचांगp == 0)
		पंचांगp = 1;

	पूर्णांकerval = (u64) पंचांगp;
	tk->cycle_पूर्णांकerval = पूर्णांकerval;

	/* Go back from cycles -> shअगरted ns */
	tk->xसमय_पूर्णांकerval = पूर्णांकerval * घड़ी->mult;
	tk->xसमय_reमुख्यder = ntpपूर्णांकerval - tk->xसमय_पूर्णांकerval;
	tk->raw_पूर्णांकerval = पूर्णांकerval * घड़ी->mult;

	 /* अगर changing घड़ीs, convert xसमय_nsec shअगरt units */
	अगर (old_घड़ी) अणु
		पूर्णांक shअगरt_change = घड़ी->shअगरt - old_घड़ी->shअगरt;
		अगर (shअगरt_change < 0) अणु
			tk->tkr_mono.xसमय_nsec >>= -shअगरt_change;
			tk->tkr_raw.xसमय_nsec >>= -shअगरt_change;
		पूर्ण अन्यथा अणु
			tk->tkr_mono.xसमय_nsec <<= shअगरt_change;
			tk->tkr_raw.xसमय_nsec <<= shअगरt_change;
		पूर्ण
	पूर्ण

	tk->tkr_mono.shअगरt = घड़ी->shअगरt;
	tk->tkr_raw.shअगरt = घड़ी->shअगरt;

	tk->ntp_error = 0;
	tk->ntp_error_shअगरt = NTP_SCALE_SHIFT - घड़ी->shअगरt;
	tk->ntp_tick = ntpपूर्णांकerval << tk->ntp_error_shअगरt;

	/*
	 * The समयkeeper keeps its own mult values क्रम the currently
	 * active घड़ीsource. These value will be adjusted via NTP
	 * to counteract घड़ी drअगरting.
	 */
	tk->tkr_mono.mult = घड़ी->mult;
	tk->tkr_raw.mult = घड़ी->mult;
	tk->ntp_err_mult = 0;
	tk->skip_second_overflow = 0;
पूर्ण

/* Timekeeper helper functions. */

अटल अंतरभूत u64 समयkeeping_delta_to_ns(स्थिर काष्ठा tk_पढ़ो_base *tkr, u64 delta)
अणु
	u64 nsec;

	nsec = delta * tkr->mult + tkr->xसमय_nsec;
	nsec >>= tkr->shअगरt;

	वापस nsec;
पूर्ण

अटल अंतरभूत u64 समयkeeping_get_ns(स्थिर काष्ठा tk_पढ़ो_base *tkr)
अणु
	u64 delta;

	delta = समयkeeping_get_delta(tkr);
	वापस समयkeeping_delta_to_ns(tkr, delta);
पूर्ण

अटल अंतरभूत u64 समयkeeping_cycles_to_ns(स्थिर काष्ठा tk_पढ़ो_base *tkr, u64 cycles)
अणु
	u64 delta;

	/* calculate the delta since the last update_wall_समय */
	delta = घड़ीsource_delta(cycles, tkr->cycle_last, tkr->mask);
	वापस समयkeeping_delta_to_ns(tkr, delta);
पूर्ण

/**
 * update_fast_समयkeeper - Update the fast and NMI safe monotonic समयkeeper.
 * @tkr: Timekeeping पढ़ोout base from which we take the update
 * @tkf: Poपूर्णांकer to NMI safe समयkeeper
 *
 * We want to use this from any context including NMI and tracing /
 * instrumenting the समयkeeping code itself.
 *
 * Employ the latch technique; see @raw_ग_लिखो_seqcount_latch.
 *
 * So अगर a NMI hits the update of base[0] then it will use base[1]
 * which is still consistent. In the worst हाल this can result is a
 * slightly wrong बारtamp (a few nanoseconds). See
 * @kसमय_get_mono_fast_ns.
 */
अटल व्योम update_fast_समयkeeper(स्थिर काष्ठा tk_पढ़ो_base *tkr,
				   काष्ठा tk_fast *tkf)
अणु
	काष्ठा tk_पढ़ो_base *base = tkf->base;

	/* Force पढ़ोers off to base[1] */
	raw_ग_लिखो_seqcount_latch(&tkf->seq);

	/* Update base[0] */
	स_नकल(base, tkr, माप(*base));

	/* Force पढ़ोers back to base[0] */
	raw_ग_लिखो_seqcount_latch(&tkf->seq);

	/* Update base[1] */
	स_नकल(base + 1, base, माप(*base));
पूर्ण

अटल __always_अंतरभूत u64 __kसमय_get_fast_ns(काष्ठा tk_fast *tkf)
अणु
	काष्ठा tk_पढ़ो_base *tkr;
	अचिन्हित पूर्णांक seq;
	u64 now;

	करो अणु
		seq = raw_पढ़ो_seqcount_latch(&tkf->seq);
		tkr = tkf->base + (seq & 0x01);
		now = kसमय_प्रकारo_ns(tkr->base);

		now += समयkeeping_delta_to_ns(tkr,
				घड़ीsource_delta(
					tk_घड़ी_पढ़ो(tkr),
					tkr->cycle_last,
					tkr->mask));
	पूर्ण जबतक (पढ़ो_seqcount_latch_retry(&tkf->seq, seq));

	वापस now;
पूर्ण

/**
 * kसमय_get_mono_fast_ns - Fast NMI safe access to घड़ी monotonic
 *
 * This बारtamp is not guaranteed to be monotonic across an update.
 * The बारtamp is calculated by:
 *
 *	now = base_mono + घड़ी_delta * slope
 *
 * So अगर the update lowers the slope, पढ़ोers who are क्रमced to the
 * not yet updated second array are still using the old steeper slope.
 *
 * पंचांगono
 * ^
 * |    o  n
 * |   o n
 * |  u
 * | o
 * |o
 * |12345678---> पढ़ोer order
 *
 * o = old slope
 * u = update
 * n = new slope
 *
 * So पढ़ोer 6 will observe समय going backwards versus पढ़ोer 5.
 *
 * While other CPUs are likely to be able to observe that, the only way
 * क्रम a CPU local observation is when an NMI hits in the middle of
 * the update. Timestamps taken from that NMI context might be ahead
 * of the following बारtamps. Callers need to be aware of that and
 * deal with it.
 */
u64 kसमय_get_mono_fast_ns(व्योम)
अणु
	वापस __kसमय_get_fast_ns(&tk_fast_mono);
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get_mono_fast_ns);

/**
 * kसमय_get_raw_fast_ns - Fast NMI safe access to घड़ी monotonic raw
 *
 * Contrary to kसमय_get_mono_fast_ns() this is always correct because the
 * conversion factor is not affected by NTP/PTP correction.
 */
u64 kसमय_get_raw_fast_ns(व्योम)
अणु
	वापस __kसमय_get_fast_ns(&tk_fast_raw);
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get_raw_fast_ns);

/**
 * kसमय_get_boot_fast_ns - NMI safe and fast access to boot घड़ी.
 *
 * To keep it NMI safe since we're accessing from tracing, we're not using a
 * separate समयkeeper with updates to monotonic घड़ी and boot offset
 * रक्षित with seqcounts. This has the following minor side effects:
 *
 * (1) Its possible that a बारtamp be taken after the boot offset is updated
 * but beक्रमe the समयkeeper is updated. If this happens, the new boot offset
 * is added to the old समयkeeping making the घड़ी appear to update slightly
 * earlier:
 *    CPU 0                                        CPU 1
 *    समयkeeping_inject_sleepसमय64()
 *    __समयkeeping_inject_sleepसमय(tk, delta);
 *                                                 बारtamp();
 *    समयkeeping_update(tk, TK_CLEAR_NTP...);
 *
 * (2) On 32-bit प्रणालीs, the 64-bit boot offset (tk->offs_boot) may be
 * partially updated.  Since the tk->offs_boot update is a rare event, this
 * should be a rare occurrence which postprocessing should be able to handle.
 *
 * The caveats vs. बारtamp ordering as करोcumented क्रम kसमय_get_fast_ns()
 * apply as well.
 */
u64 notrace kसमय_get_boot_fast_ns(व्योम)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;

	वापस (kसमय_get_mono_fast_ns() + kसमय_प्रकारo_ns(tk->offs_boot));
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get_boot_fast_ns);

अटल __always_अंतरभूत u64 __kसमय_get_real_fast(काष्ठा tk_fast *tkf, u64 *mono)
अणु
	काष्ठा tk_पढ़ो_base *tkr;
	u64 basem, baser, delta;
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = raw_पढ़ो_seqcount_latch(&tkf->seq);
		tkr = tkf->base + (seq & 0x01);
		basem = kसमय_प्रकारo_ns(tkr->base);
		baser = kसमय_प्रकारo_ns(tkr->base_real);

		delta = समयkeeping_delta_to_ns(tkr,
				घड़ीsource_delta(tk_घड़ी_पढ़ो(tkr),
				tkr->cycle_last, tkr->mask));
	पूर्ण जबतक (पढ़ो_seqcount_latch_retry(&tkf->seq, seq));

	अगर (mono)
		*mono = basem + delta;
	वापस baser + delta;
पूर्ण

/**
 * kसमय_get_real_fast_ns: - NMI safe and fast access to घड़ी realसमय.
 *
 * See kसमय_get_fast_ns() क्रम करोcumentation of the समय stamp ordering.
 */
u64 kसमय_get_real_fast_ns(व्योम)
अणु
	वापस __kसमय_get_real_fast(&tk_fast_mono, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get_real_fast_ns);

/**
 * kसमय_get_fast_बारtamps: - NMI safe बारtamps
 * @snapshot:	Poपूर्णांकer to बारtamp storage
 *
 * Stores घड़ी monotonic, bootसमय and realसमय बारtamps.
 *
 * Boot समय is a racy access on 32bit प्रणालीs अगर the sleep समय injection
 * happens late during resume and not in समयkeeping_resume(). That could
 * be aव्योमed by expanding काष्ठा tk_पढ़ो_base with boot offset क्रम 32bit
 * and adding more overhead to the update. As this is a hard to observe
 * once per resume event which can be filtered with reasonable efक्रमt using
 * the accurate mono/real बारtamps, it's probably not worth the trouble.
 *
 * Aside of that it might be possible on 32 and 64 bit to observe the
 * following when the sleep समय injection happens late:
 *
 * CPU 0				CPU 1
 * समयkeeping_resume()
 * kसमय_get_fast_बारtamps()
 *	mono, real = __kसमय_get_real_fast()
 *					inject_sleep_समय()
 *					   update boot offset
 *	boot = mono + bootoffset;
 *
 * That means that boot समय alपढ़ोy has the sleep समय adjusपंचांगent, but
 * real समय करोes not. On the next पढ़ोout both are in sync again.
 *
 * Preventing this क्रम 64bit is not really feasible without destroying the
 * careful cache layout of the समयkeeper because the sequence count and
 * काष्ठा tk_पढ़ो_base would then need two cache lines instead of one.
 *
 * Access to the समय keeper घड़ी source is disabled across the innermost
 * steps of suspend/resume. The accessors still work, but the बारtamps
 * are frozen until समय keeping is resumed which happens very early.
 *
 * For regular suspend/resume there is no observable dअगरference vs. sched
 * घड़ी, but it might affect some of the nasty low level debug prपूर्णांकks.
 *
 * OTOH, access to sched घड़ी is not guaranteed across suspend/resume on
 * all प्रणालीs either so it depends on the hardware in use.
 *
 * If that turns out to be a real problem then this could be mitigated by
 * using sched घड़ी in a similar way as during early boot. But it's not as
 * trivial as on early boot because it needs some careful protection
 * against the घड़ी monotonic बारtamp jumping backwards on resume.
 */
व्योम kसमय_get_fast_बारtamps(काष्ठा kसमय_प्रकारimestamps *snapshot)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;

	snapshot->real = __kसमय_get_real_fast(&tk_fast_mono, &snapshot->mono);
	snapshot->boot = snapshot->mono + kसमय_प्रकारo_ns(data_race(tk->offs_boot));
पूर्ण

/**
 * halt_fast_समयkeeper - Prevent fast समयkeeper from accessing घड़ीsource.
 * @tk: Timekeeper to snapshot.
 *
 * It generally is unsafe to access the घड़ीsource after समयkeeping has been
 * suspended, so take a snapshot of the पढ़ोout base of @tk and use it as the
 * fast समयkeeper's पढ़ोout base जबतक suspended.  It will वापस the same
 * number of cycles every समय until समयkeeping is resumed at which समय the
 * proper पढ़ोout base क्रम the fast समयkeeper will be restored स्वतःmatically.
 */
अटल व्योम halt_fast_समयkeeper(स्थिर काष्ठा समयkeeper *tk)
अणु
	अटल काष्ठा tk_पढ़ो_base tkr_dummy;
	स्थिर काष्ठा tk_पढ़ो_base *tkr = &tk->tkr_mono;

	स_नकल(&tkr_dummy, tkr, माप(tkr_dummy));
	cycles_at_suspend = tk_घड़ी_पढ़ो(tkr);
	tkr_dummy.घड़ी = &dummy_घड़ी;
	tkr_dummy.base_real = tkr->base + tk->offs_real;
	update_fast_समयkeeper(&tkr_dummy, &tk_fast_mono);

	tkr = &tk->tkr_raw;
	स_नकल(&tkr_dummy, tkr, माप(tkr_dummy));
	tkr_dummy.घड़ी = &dummy_घड़ी;
	update_fast_समयkeeper(&tkr_dummy, &tk_fast_raw);
पूर्ण

अटल RAW_NOTIFIER_HEAD(pvघड़ी_gtod_chain);

अटल व्योम update_pvघड़ी_gtod(काष्ठा समयkeeper *tk, bool was_set)
अणु
	raw_notअगरier_call_chain(&pvघड़ी_gtod_chain, was_set, tk);
पूर्ण

/**
 * pvघड़ी_gtod_रेजिस्टर_notअगरier - रेजिस्टर a pvघड़ी समयdata update listener
 * @nb: Poपूर्णांकer to the notअगरier block to रेजिस्टर
 */
पूर्णांक pvघड़ी_gtod_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);
	ret = raw_notअगरier_chain_रेजिस्टर(&pvघड़ी_gtod_chain, nb);
	update_pvघड़ी_gtod(tk, true);
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pvघड़ी_gtod_रेजिस्टर_notअगरier);

/**
 * pvघड़ी_gtod_unरेजिस्टर_notअगरier - unरेजिस्टर a pvघड़ी
 * समयdata update listener
 * @nb: Poपूर्णांकer to the notअगरier block to unरेजिस्टर
 */
पूर्णांक pvघड़ी_gtod_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);
	ret = raw_notअगरier_chain_unरेजिस्टर(&pvघड़ी_gtod_chain, nb);
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pvघड़ी_gtod_unरेजिस्टर_notअगरier);

/*
 * tk_update_leap_state - helper to update the next_leap_kसमय
 */
अटल अंतरभूत व्योम tk_update_leap_state(काष्ठा समयkeeper *tk)
अणु
	tk->next_leap_kसमय = ntp_get_next_leap();
	अगर (tk->next_leap_kसमय != KTIME_MAX)
		/* Convert to monotonic समय */
		tk->next_leap_kसमय = kसमय_sub(tk->next_leap_kसमय, tk->offs_real);
पूर्ण

/*
 * Update the kसमय_प्रकार based scalar nsec members of the समयkeeper
 */
अटल अंतरभूत व्योम tk_update_kसमय_data(काष्ठा समयkeeper *tk)
अणु
	u64 seconds;
	u32 nsec;

	/*
	 * The xसमय based monotonic पढ़ोout is:
	 *	nsec = (xसमय_sec + wपंचांग_sec) * 1e9 + wपंचांग_nsec + now();
	 * The kसमय based monotonic पढ़ोout is:
	 *	nsec = base_mono + now();
	 * ==> base_mono = (xसमय_sec + wपंचांग_sec) * 1e9 + wपंचांग_nsec
	 */
	seconds = (u64)(tk->xसमय_sec + tk->wall_to_monotonic.tv_sec);
	nsec = (u32) tk->wall_to_monotonic.tv_nsec;
	tk->tkr_mono.base = ns_to_kसमय(seconds * NSEC_PER_SEC + nsec);

	/*
	 * The sum of the nanoseconds portions of xसमय and
	 * wall_to_monotonic can be greater/equal one second. Take
	 * this पूर्णांकo account beक्रमe updating tk->kसमय_sec.
	 */
	nsec += (u32)(tk->tkr_mono.xसमय_nsec >> tk->tkr_mono.shअगरt);
	अगर (nsec >= NSEC_PER_SEC)
		seconds++;
	tk->kसमय_sec = seconds;

	/* Update the monotonic raw base */
	tk->tkr_raw.base = ns_to_kसमय(tk->raw_sec * NSEC_PER_SEC);
पूर्ण

/* must hold समयkeeper_lock */
अटल व्योम समयkeeping_update(काष्ठा समयkeeper *tk, अचिन्हित पूर्णांक action)
अणु
	अगर (action & TK_CLEAR_NTP) अणु
		tk->ntp_error = 0;
		ntp_clear();
	पूर्ण

	tk_update_leap_state(tk);
	tk_update_kसमय_data(tk);

	update_vsyscall(tk);
	update_pvघड़ी_gtod(tk, action & TK_CLOCK_WAS_SET);

	tk->tkr_mono.base_real = tk->tkr_mono.base + tk->offs_real;
	update_fast_समयkeeper(&tk->tkr_mono, &tk_fast_mono);
	update_fast_समयkeeper(&tk->tkr_raw,  &tk_fast_raw);

	अगर (action & TK_CLOCK_WAS_SET)
		tk->घड़ी_was_set_seq++;
	/*
	 * The mirroring of the data to the shaकरोw-समयkeeper needs
	 * to happen last here to ensure we करोn't over-ग_लिखो the
	 * समयkeeper काष्ठाure on the next update with stale data
	 */
	अगर (action & TK_MIRROR)
		स_नकल(&shaकरोw_समयkeeper, &tk_core.समयkeeper,
		       माप(tk_core.समयkeeper));
पूर्ण

/**
 * समयkeeping_क्रमward_now - update घड़ी to the current समय
 * @tk:		Poपूर्णांकer to the समयkeeper to update
 *
 * Forward the current घड़ी to update its state since the last call to
 * update_wall_समय(). This is useful beक्रमe signअगरicant घड़ी changes,
 * as it aव्योमs having to deal with this समय offset explicitly.
 */
अटल व्योम समयkeeping_क्रमward_now(काष्ठा समयkeeper *tk)
अणु
	u64 cycle_now, delta;

	cycle_now = tk_घड़ी_पढ़ो(&tk->tkr_mono);
	delta = घड़ीsource_delta(cycle_now, tk->tkr_mono.cycle_last, tk->tkr_mono.mask);
	tk->tkr_mono.cycle_last = cycle_now;
	tk->tkr_raw.cycle_last  = cycle_now;

	tk->tkr_mono.xसमय_nsec += delta * tk->tkr_mono.mult;
	tk->tkr_raw.xसमय_nsec += delta * tk->tkr_raw.mult;

	tk_normalize_xसमय(tk);
पूर्ण

/**
 * kसमय_get_real_ts64 - Returns the समय of day in a बारpec64.
 * @ts:		poपूर्णांकer to the बारpec to be set
 *
 * Returns the समय of day in a बारpec64 (WARN अगर suspended).
 */
व्योम kसमय_get_real_ts64(काष्ठा बारpec64 *ts)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित पूर्णांक seq;
	u64 nsecs;

	WARN_ON(समयkeeping_suspended);

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);

		ts->tv_sec = tk->xसमय_sec;
		nsecs = समयkeeping_get_ns(&tk->tkr_mono);

	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	ts->tv_nsec = 0;
	बारpec64_add_ns(ts, nsecs);
पूर्ण
EXPORT_SYMBOL(kसमय_get_real_ts64);

kसमय_प्रकार kसमय_get(व्योम)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित पूर्णांक seq;
	kसमय_प्रकार base;
	u64 nsecs;

	WARN_ON(समयkeeping_suspended);

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);
		base = tk->tkr_mono.base;
		nsecs = समयkeeping_get_ns(&tk->tkr_mono);

	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	वापस kसमय_add_ns(base, nsecs);
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get);

u32 kसमय_get_resolution_ns(व्योम)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित पूर्णांक seq;
	u32 nsecs;

	WARN_ON(समयkeeping_suspended);

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);
		nsecs = tk->tkr_mono.mult >> tk->tkr_mono.shअगरt;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	वापस nsecs;
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get_resolution_ns);

अटल kसमय_प्रकार *offsets[TK_OFFS_MAX] = अणु
	[TK_OFFS_REAL]	= &tk_core.समयkeeper.offs_real,
	[TK_OFFS_BOOT]	= &tk_core.समयkeeper.offs_boot,
	[TK_OFFS_TAI]	= &tk_core.समयkeeper.offs_tai,
पूर्ण;

kसमय_प्रकार kसमय_get_with_offset(क्रमागत tk_offsets offs)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित पूर्णांक seq;
	kसमय_प्रकार base, *offset = offsets[offs];
	u64 nsecs;

	WARN_ON(समयkeeping_suspended);

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);
		base = kसमय_add(tk->tkr_mono.base, *offset);
		nsecs = समयkeeping_get_ns(&tk->tkr_mono);

	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	वापस kसमय_add_ns(base, nsecs);

पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get_with_offset);

kसमय_प्रकार kसमय_get_coarse_with_offset(क्रमागत tk_offsets offs)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित पूर्णांक seq;
	kसमय_प्रकार base, *offset = offsets[offs];
	u64 nsecs;

	WARN_ON(समयkeeping_suspended);

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);
		base = kसमय_add(tk->tkr_mono.base, *offset);
		nsecs = tk->tkr_mono.xसमय_nsec >> tk->tkr_mono.shअगरt;

	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	वापस kसमय_add_ns(base, nsecs);
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get_coarse_with_offset);

/**
 * kसमय_mono_to_any() - convert monotonic समय to any other समय
 * @पंचांगono:	समय to convert.
 * @offs:	which offset to use
 */
kसमय_प्रकार kसमय_mono_to_any(kसमय_प्रकार पंचांगono, क्रमागत tk_offsets offs)
अणु
	kसमय_प्रकार *offset = offsets[offs];
	अचिन्हित पूर्णांक seq;
	kसमय_प्रकार tconv;

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);
		tconv = kसमय_add(पंचांगono, *offset);
	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	वापस tconv;
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_mono_to_any);

/**
 * kसमय_get_raw - Returns the raw monotonic समय in kसमय_प्रकार क्रमmat
 */
kसमय_प्रकार kसमय_get_raw(व्योम)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित पूर्णांक seq;
	kसमय_प्रकार base;
	u64 nsecs;

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);
		base = tk->tkr_raw.base;
		nsecs = समयkeeping_get_ns(&tk->tkr_raw);

	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	वापस kसमय_add_ns(base, nsecs);
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get_raw);

/**
 * kसमय_get_ts64 - get the monotonic घड़ी in बारpec64 क्रमmat
 * @ts:		poपूर्णांकer to बारpec variable
 *
 * The function calculates the monotonic घड़ी from the realसमय
 * घड़ी and the wall_to_monotonic offset and stores the result
 * in normalized बारpec64 क्रमmat in the variable poपूर्णांकed to by @ts.
 */
व्योम kसमय_get_ts64(काष्ठा बारpec64 *ts)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	काष्ठा बारpec64 tomono;
	अचिन्हित पूर्णांक seq;
	u64 nsec;

	WARN_ON(समयkeeping_suspended);

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);
		ts->tv_sec = tk->xसमय_sec;
		nsec = समयkeeping_get_ns(&tk->tkr_mono);
		tomono = tk->wall_to_monotonic;

	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	ts->tv_sec += tomono.tv_sec;
	ts->tv_nsec = 0;
	बारpec64_add_ns(ts, nsec + tomono.tv_nsec);
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get_ts64);

/**
 * kसमय_get_seconds - Get the seconds portion of CLOCK_MONOTONIC
 *
 * Returns the seconds portion of CLOCK_MONOTONIC with a single non
 * serialized पढ़ो. tk->kसमय_sec is of type 'unsigned long' so this
 * works on both 32 and 64 bit प्रणालीs. On 32 bit प्रणालीs the पढ़ोout
 * covers ~136 years of upसमय which should be enough to prevent
 * premature wrap arounds.
 */
समय64_t kसमय_get_seconds(व्योम)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;

	WARN_ON(समयkeeping_suspended);
	वापस tk->kसमय_sec;
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get_seconds);

/**
 * kसमय_get_real_seconds - Get the seconds portion of CLOCK_REALTIME
 *
 * Returns the wall घड़ी seconds since 1970.
 *
 * For 64bit प्रणालीs the fast access to tk->xसमय_sec is preserved. On
 * 32bit प्रणालीs the access must be रक्षित with the sequence
 * counter to provide "atomic" access to the 64bit tk->xसमय_sec
 * value.
 */
समय64_t kसमय_get_real_seconds(व्योम)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	समय64_t seconds;
	अचिन्हित पूर्णांक seq;

	अगर (IS_ENABLED(CONFIG_64BIT))
		वापस tk->xसमय_sec;

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);
		seconds = tk->xसमय_sec;

	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	वापस seconds;
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get_real_seconds);

/**
 * __kसमय_get_real_seconds - The same as kसमय_get_real_seconds
 * but without the sequence counter protect. This पूर्णांकernal function
 * is called just when समयkeeping lock is alपढ़ोy held.
 */
noinstr समय64_t __kसमय_get_real_seconds(व्योम)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;

	वापस tk->xसमय_sec;
पूर्ण

/**
 * kसमय_get_snapshot - snapshots the realसमय/monotonic raw घड़ीs with counter
 * @sysसमय_snapshot:	poपूर्णांकer to काष्ठा receiving the प्रणाली समय snapshot
 */
व्योम kसमय_get_snapshot(काष्ठा प्रणाली_समय_snapshot *sysसमय_snapshot)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित पूर्णांक seq;
	kसमय_प्रकार base_raw;
	kसमय_प्रकार base_real;
	u64 nsec_raw;
	u64 nsec_real;
	u64 now;

	WARN_ON_ONCE(समयkeeping_suspended);

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);
		now = tk_घड़ी_पढ़ो(&tk->tkr_mono);
		sysसमय_snapshot->cs_id = tk->tkr_mono.घड़ी->id;
		sysसमय_snapshot->cs_was_changed_seq = tk->cs_was_changed_seq;
		sysसमय_snapshot->घड़ी_was_set_seq = tk->घड़ी_was_set_seq;
		base_real = kसमय_add(tk->tkr_mono.base,
				      tk_core.समयkeeper.offs_real);
		base_raw = tk->tkr_raw.base;
		nsec_real = समयkeeping_cycles_to_ns(&tk->tkr_mono, now);
		nsec_raw  = समयkeeping_cycles_to_ns(&tk->tkr_raw, now);
	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	sysसमय_snapshot->cycles = now;
	sysसमय_snapshot->real = kसमय_add_ns(base_real, nsec_real);
	sysसमय_snapshot->raw = kसमय_add_ns(base_raw, nsec_raw);
पूर्ण
EXPORT_SYMBOL_GPL(kसमय_get_snapshot);

/* Scale base by mult/भाग checking क्रम overflow */
अटल पूर्णांक scale64_check_overflow(u64 mult, u64 भाग, u64 *base)
अणु
	u64 पंचांगp, rem;

	पंचांगp = भाग64_u64_rem(*base, भाग, &rem);

	अगर (((पूर्णांक)माप(u64)*8 - fls64(mult) < fls64(पंचांगp)) ||
	    ((पूर्णांक)माप(u64)*8 - fls64(mult) < fls64(rem)))
		वापस -EOVERFLOW;
	पंचांगp *= mult;

	rem = भाग64_u64(rem * mult, भाग);
	*base = पंचांगp + rem;
	वापस 0;
पूर्ण

/**
 * adjust_historical_crosststamp - adjust crossबारtamp previous to current पूर्णांकerval
 * @history:			Snapshot representing start of history
 * @partial_history_cycles:	Cycle offset पूर्णांकo history (fractional part)
 * @total_history_cycles:	Total history length in cycles
 * @discontinuity:		True indicates घड़ी was set on history period
 * @ts:				Cross बारtamp that should be adjusted using
 *	partial/total ratio
 *
 * Helper function used by get_device_प्रणाली_crosststamp() to correct the
 * crossबारtamp corresponding to the start of the current पूर्णांकerval to the
 * प्रणाली counter value (बारtamp poपूर्णांक) provided by the driver. The
 * total_history_* quantities are the total history starting at the provided
 * reference poपूर्णांक and ending at the start of the current पूर्णांकerval. The cycle
 * count between the driver बारtamp poपूर्णांक and the start of the current
 * पूर्णांकerval is partial_history_cycles.
 */
अटल पूर्णांक adjust_historical_crosststamp(काष्ठा प्रणाली_समय_snapshot *history,
					 u64 partial_history_cycles,
					 u64 total_history_cycles,
					 bool discontinuity,
					 काष्ठा प्रणाली_device_crosststamp *ts)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	u64 corr_raw, corr_real;
	bool पूर्णांकerp_क्रमward;
	पूर्णांक ret;

	अगर (total_history_cycles == 0 || partial_history_cycles == 0)
		वापस 0;

	/* Interpolate लघुest distance from beginning or end of history */
	पूर्णांकerp_क्रमward = partial_history_cycles > total_history_cycles / 2;
	partial_history_cycles = पूर्णांकerp_क्रमward ?
		total_history_cycles - partial_history_cycles :
		partial_history_cycles;

	/*
	 * Scale the monotonic raw समय delta by:
	 *	partial_history_cycles / total_history_cycles
	 */
	corr_raw = (u64)kसमय_प्रकारo_ns(
		kसमय_sub(ts->sys_monoraw, history->raw));
	ret = scale64_check_overflow(partial_history_cycles,
				     total_history_cycles, &corr_raw);
	अगर (ret)
		वापस ret;

	/*
	 * If there is a discontinuity in the history, scale monotonic raw
	 *	correction by:
	 *	mult(real)/mult(raw) yielding the realसमय correction
	 * Otherwise, calculate the realसमय correction similar to monotonic
	 *	raw calculation
	 */
	अगर (discontinuity) अणु
		corr_real = mul_u64_u32_भाग
			(corr_raw, tk->tkr_mono.mult, tk->tkr_raw.mult);
	पूर्ण अन्यथा अणु
		corr_real = (u64)kसमय_प्रकारo_ns(
			kसमय_sub(ts->sys_realसमय, history->real));
		ret = scale64_check_overflow(partial_history_cycles,
					     total_history_cycles, &corr_real);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Fixup monotonic raw and real समय समय values */
	अगर (पूर्णांकerp_क्रमward) अणु
		ts->sys_monoraw = kसमय_add_ns(history->raw, corr_raw);
		ts->sys_realसमय = kसमय_add_ns(history->real, corr_real);
	पूर्ण अन्यथा अणु
		ts->sys_monoraw = kसमय_sub_ns(ts->sys_monoraw, corr_raw);
		ts->sys_realसमय = kसमय_sub_ns(ts->sys_realसमय, corr_real);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * cycle_between - true अगर test occurs chronologically between beक्रमe and after
 */
अटल bool cycle_between(u64 beक्रमe, u64 test, u64 after)
अणु
	अगर (test > beक्रमe && test < after)
		वापस true;
	अगर (test < beक्रमe && beक्रमe > after)
		वापस true;
	वापस false;
पूर्ण

/**
 * get_device_प्रणाली_crosststamp - Synchronously capture प्रणाली/device बारtamp
 * @get_समय_fn:	Callback to get simultaneous device समय and
 *	प्रणाली counter from the device driver
 * @ctx:		Context passed to get_समय_fn()
 * @history_begin:	Historical reference poपूर्णांक used to पूर्णांकerpolate प्रणाली
 *	समय when counter provided by the driver is beक्रमe the current पूर्णांकerval
 * @xtstamp:		Receives simultaneously captured प्रणाली and device समय
 *
 * Reads a बारtamp from a device and correlates it to प्रणाली समय
 */
पूर्णांक get_device_प्रणाली_crosststamp(पूर्णांक (*get_समय_fn)
				  (kसमय_प्रकार *device_समय,
				   काष्ठा प्रणाली_counterval_t *sys_counterval,
				   व्योम *ctx),
				  व्योम *ctx,
				  काष्ठा प्रणाली_समय_snapshot *history_begin,
				  काष्ठा प्रणाली_device_crosststamp *xtstamp)
अणु
	काष्ठा प्रणाली_counterval_t प्रणाली_counterval;
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	u64 cycles, now, पूर्णांकerval_start;
	अचिन्हित पूर्णांक घड़ी_was_set_seq = 0;
	kसमय_प्रकार base_real, base_raw;
	u64 nsec_real, nsec_raw;
	u8 cs_was_changed_seq;
	अचिन्हित पूर्णांक seq;
	bool करो_पूर्णांकerp;
	पूर्णांक ret;

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);
		/*
		 * Try to synchronously capture device समय and a प्रणाली
		 * counter value calling back पूर्णांकo the device driver
		 */
		ret = get_समय_fn(&xtstamp->device, &प्रणाली_counterval, ctx);
		अगर (ret)
			वापस ret;

		/*
		 * Verअगरy that the घड़ीsource associated with the captured
		 * प्रणाली counter value is the same as the currently installed
		 * समयkeeper घड़ीsource
		 */
		अगर (tk->tkr_mono.घड़ी != प्रणाली_counterval.cs)
			वापस -ENODEV;
		cycles = प्रणाली_counterval.cycles;

		/*
		 * Check whether the प्रणाली counter value provided by the
		 * device driver is on the current समयkeeping पूर्णांकerval.
		 */
		now = tk_घड़ी_पढ़ो(&tk->tkr_mono);
		पूर्णांकerval_start = tk->tkr_mono.cycle_last;
		अगर (!cycle_between(पूर्णांकerval_start, cycles, now)) अणु
			घड़ी_was_set_seq = tk->घड़ी_was_set_seq;
			cs_was_changed_seq = tk->cs_was_changed_seq;
			cycles = पूर्णांकerval_start;
			करो_पूर्णांकerp = true;
		पूर्ण अन्यथा अणु
			करो_पूर्णांकerp = false;
		पूर्ण

		base_real = kसमय_add(tk->tkr_mono.base,
				      tk_core.समयkeeper.offs_real);
		base_raw = tk->tkr_raw.base;

		nsec_real = समयkeeping_cycles_to_ns(&tk->tkr_mono,
						     प्रणाली_counterval.cycles);
		nsec_raw = समयkeeping_cycles_to_ns(&tk->tkr_raw,
						    प्रणाली_counterval.cycles);
	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	xtstamp->sys_realसमय = kसमय_add_ns(base_real, nsec_real);
	xtstamp->sys_monoraw = kसमय_add_ns(base_raw, nsec_raw);

	/*
	 * Interpolate अगर necessary, adjusting back from the start of the
	 * current पूर्णांकerval
	 */
	अगर (करो_पूर्णांकerp) अणु
		u64 partial_history_cycles, total_history_cycles;
		bool discontinuity;

		/*
		 * Check that the counter value occurs after the provided
		 * history reference and that the history करोesn't cross a
		 * घड़ीsource change
		 */
		अगर (!history_begin ||
		    !cycle_between(history_begin->cycles,
				   प्रणाली_counterval.cycles, cycles) ||
		    history_begin->cs_was_changed_seq != cs_was_changed_seq)
			वापस -EINVAL;
		partial_history_cycles = cycles - प्रणाली_counterval.cycles;
		total_history_cycles = cycles - history_begin->cycles;
		discontinuity =
			history_begin->घड़ी_was_set_seq != घड़ी_was_set_seq;

		ret = adjust_historical_crosststamp(history_begin,
						    partial_history_cycles,
						    total_history_cycles,
						    discontinuity, xtstamp);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(get_device_प्रणाली_crosststamp);

/**
 * करो_समय_रखोofday64 - Sets the समय of day.
 * @ts:     poपूर्णांकer to the बारpec64 variable containing the new समय
 *
 * Sets the समय of day to the new समय and update NTP and notअगरy hrसमयrs
 */
पूर्णांक करो_समय_रखोofday64(स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	काष्ठा बारpec64 ts_delta, xt;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!बारpec64_valid_settod(ts))
		वापस -EINVAL;

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);
	ग_लिखो_seqcount_begin(&tk_core.seq);

	समयkeeping_क्रमward_now(tk);

	xt = tk_xसमय(tk);
	ts_delta.tv_sec = ts->tv_sec - xt.tv_sec;
	ts_delta.tv_nsec = ts->tv_nsec - xt.tv_nsec;

	अगर (बारpec64_compare(&tk->wall_to_monotonic, &ts_delta) > 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	tk_set_wall_to_mono(tk, बारpec64_sub(tk->wall_to_monotonic, ts_delta));

	tk_set_xसमय(tk, ts);
out:
	समयkeeping_update(tk, TK_CLEAR_NTP | TK_MIRROR | TK_CLOCK_WAS_SET);

	ग_लिखो_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);

	/* संकेत hrसमयrs about समय change */
	घड़ी_was_set();

	अगर (!ret)
		audit_tk_injoffset(ts_delta);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(करो_समय_रखोofday64);

/**
 * समयkeeping_inject_offset - Adds or subtracts from the current समय.
 * @ts:		Poपूर्णांकer to the बारpec variable containing the offset
 *
 * Adds or subtracts an offset value from the current समय.
 */
अटल पूर्णांक समयkeeping_inject_offset(स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित दीर्घ flags;
	काष्ठा बारpec64 पंचांगp;
	पूर्णांक ret = 0;

	अगर (ts->tv_nsec < 0 || ts->tv_nsec >= NSEC_PER_SEC)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);
	ग_लिखो_seqcount_begin(&tk_core.seq);

	समयkeeping_क्रमward_now(tk);

	/* Make sure the proposed value is valid */
	पंचांगp = बारpec64_add(tk_xसमय(tk), *ts);
	अगर (बारpec64_compare(&tk->wall_to_monotonic, ts) > 0 ||
	    !बारpec64_valid_settod(&पंचांगp)) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	tk_xसमय_add(tk, ts);
	tk_set_wall_to_mono(tk, बारpec64_sub(tk->wall_to_monotonic, *ts));

error: /* even अगर we error out, we क्रमwarded the समय, so call update */
	समयkeeping_update(tk, TK_CLEAR_NTP | TK_MIRROR | TK_CLOCK_WAS_SET);

	ग_लिखो_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);

	/* संकेत hrसमयrs about समय change */
	घड़ी_was_set();

	वापस ret;
पूर्ण

/*
 * Indicates अगर there is an offset between the प्रणाली घड़ी and the hardware
 * घड़ी/persistent घड़ी/rtc.
 */
पूर्णांक persistent_घड़ी_is_local;

/*
 * Adjust the समय obtained from the CMOS to be UTC समय instead of
 * local समय.
 *
 * This is ugly, but preferable to the alternatives.  Otherwise we
 * would either need to ग_लिखो a program to करो it in /etc/rc (and risk
 * confusion अगर the program माला_लो run more than once; it would also be
 * hard to make the program warp the घड़ी precisely n hours)  or
 * compile in the समयzone inक्रमmation पूर्णांकo the kernel.  Bad, bad....
 *
 *						- TYT, 1992-01-01
 *
 * The best thing to करो is to keep the CMOS घड़ी in universal समय (UTC)
 * as real UNIX machines always करो it. This aव्योमs all headaches about
 * daylight saving बार and warping kernel घड़ीs.
 */
व्योम समयkeeping_warp_घड़ी(व्योम)
अणु
	अगर (sys_tz.tz_minuteswest != 0) अणु
		काष्ठा बारpec64 adjust;

		persistent_घड़ी_is_local = 1;
		adjust.tv_sec = sys_tz.tz_minuteswest * 60;
		adjust.tv_nsec = 0;
		समयkeeping_inject_offset(&adjust);
	पूर्ण
पूर्ण

/*
 * __समयkeeping_set_tai_offset - Sets the TAI offset from UTC and monotonic
 */
अटल व्योम __समयkeeping_set_tai_offset(काष्ठा समयkeeper *tk, s32 tai_offset)
अणु
	tk->tai_offset = tai_offset;
	tk->offs_tai = kसमय_add(tk->offs_real, kसमय_set(tai_offset, 0));
पूर्ण

/*
 * change_घड़ीsource - Swaps घड़ीsources अगर a new one is available
 *
 * Accumulates current समय पूर्णांकerval and initializes new घड़ीsource
 */
अटल पूर्णांक change_घड़ीsource(व्योम *data)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	काष्ठा घड़ीsource *new, *old = शून्य;
	अचिन्हित दीर्घ flags;
	bool change = false;

	new = (काष्ठा घड़ीsource *) data;

	/*
	 * If the cs is in module, get a module reference. Succeeds
	 * क्रम built-in code (owner == शून्य) as well.
	 */
	अगर (try_module_get(new->owner)) अणु
		अगर (!new->enable || new->enable(new) == 0)
			change = true;
		अन्यथा
			module_put(new->owner);
	पूर्ण

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);
	ग_लिखो_seqcount_begin(&tk_core.seq);

	समयkeeping_क्रमward_now(tk);

	अगर (change) अणु
		old = tk->tkr_mono.घड़ी;
		tk_setup_पूर्णांकernals(tk, new);
	पूर्ण

	समयkeeping_update(tk, TK_CLEAR_NTP | TK_MIRROR | TK_CLOCK_WAS_SET);

	ग_लिखो_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);

	अगर (old) अणु
		अगर (old->disable)
			old->disable(old);

		module_put(old->owner);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * समयkeeping_notअगरy - Install a new घड़ी source
 * @घड़ी:		poपूर्णांकer to the घड़ी source
 *
 * This function is called from घड़ीsource.c after a new, better घड़ी
 * source has been रेजिस्टरed. The caller holds the घड़ीsource_mutex.
 */
पूर्णांक समयkeeping_notअगरy(काष्ठा घड़ीsource *घड़ी)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;

	अगर (tk->tkr_mono.घड़ी == घड़ी)
		वापस 0;
	stop_machine(change_घड़ीsource, घड़ी, शून्य);
	tick_घड़ी_notअगरy();
	वापस tk->tkr_mono.घड़ी == घड़ी ? 0 : -1;
पूर्ण

/**
 * kसमय_get_raw_ts64 - Returns the raw monotonic समय in a बारpec
 * @ts:		poपूर्णांकer to the बारpec64 to be set
 *
 * Returns the raw monotonic समय (completely un-modअगरied by ntp)
 */
व्योम kसमय_get_raw_ts64(काष्ठा बारpec64 *ts)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित पूर्णांक seq;
	u64 nsecs;

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);
		ts->tv_sec = tk->raw_sec;
		nsecs = समयkeeping_get_ns(&tk->tkr_raw);

	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	ts->tv_nsec = 0;
	बारpec64_add_ns(ts, nsecs);
पूर्ण
EXPORT_SYMBOL(kसमय_get_raw_ts64);


/**
 * समयkeeping_valid_क्रम_hres - Check अगर समयkeeping is suitable क्रम hres
 */
पूर्णांक समयkeeping_valid_क्रम_hres(व्योम)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित पूर्णांक seq;
	पूर्णांक ret;

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);

		ret = tk->tkr_mono.घड़ी->flags & CLOCK_SOURCE_VALID_FOR_HRES;

	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	वापस ret;
पूर्ण

/**
 * समयkeeping_max_deferment - Returns max समय the घड़ीsource can be deferred
 */
u64 समयkeeping_max_deferment(व्योम)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित पूर्णांक seq;
	u64 ret;

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);

		ret = tk->tkr_mono.घड़ी->max_idle_ns;

	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	वापस ret;
पूर्ण

/**
 * पढ़ो_persistent_घड़ी64 -  Return समय from the persistent घड़ी.
 * @ts: Poपूर्णांकer to the storage क्रम the पढ़ोout value
 *
 * Weak dummy function क्रम arches that करो not yet support it.
 * Reads the समय from the battery backed persistent घड़ी.
 * Returns a बारpec with tv_sec=0 and tv_nsec=0 अगर unsupported.
 *
 *  XXX - Do be sure to हटाओ it once all arches implement it.
 */
व्योम __weak पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	ts->tv_sec = 0;
	ts->tv_nsec = 0;
पूर्ण

/**
 * पढ़ो_persistent_wall_and_boot_offset - Read persistent घड़ी, and also offset
 *                                        from the boot.
 *
 * Weak dummy function क्रम arches that करो not yet support it.
 * @wall_समय:	- current समय as वापसed by persistent घड़ी
 * @boot_offset: - offset that is defined as wall_समय - boot_समय
 *
 * The शेष function calculates offset based on the current value of
 * local_घड़ी(). This way architectures that support sched_घड़ी() but करोn't
 * support dedicated boot समय घड़ी will provide the best estimate of the
 * boot समय.
 */
व्योम __weak __init
पढ़ो_persistent_wall_and_boot_offset(काष्ठा बारpec64 *wall_समय,
				     काष्ठा बारpec64 *boot_offset)
अणु
	पढ़ो_persistent_घड़ी64(wall_समय);
	*boot_offset = ns_to_बारpec64(local_घड़ी());
पूर्ण

/*
 * Flag reflecting whether समयkeeping_resume() has injected sleepसमय.
 *
 * The flag starts of false and is only set when a suspend reaches
 * समयkeeping_suspend(), समयkeeping_resume() sets it to false when the
 * समयkeeper घड़ीsource is not stopping across suspend and has been
 * used to update sleep समय. If the समयkeeper घड़ीsource has stopped
 * then the flag stays true and is used by the RTC resume code to decide
 * whether sleepसमय must be injected and अगर so the flag माला_लो false then.
 *
 * If a suspend fails beक्रमe reaching समयkeeping_resume() then the flag
 * stays false and prevents erroneous sleepसमय injection.
 */
अटल bool suspend_timing_needed;

/* Flag क्रम अगर there is a persistent घड़ी on this platक्रमm */
अटल bool persistent_घड़ी_exists;

/*
 * समयkeeping_init - Initializes the घड़ीsource and common समयkeeping values
 */
व्योम __init समयkeeping_init(व्योम)
अणु
	काष्ठा बारpec64 wall_समय, boot_offset, wall_to_mono;
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	काष्ठा घड़ीsource *घड़ी;
	अचिन्हित दीर्घ flags;

	पढ़ो_persistent_wall_and_boot_offset(&wall_समय, &boot_offset);
	अगर (बारpec64_valid_settod(&wall_समय) &&
	    बारpec64_to_ns(&wall_समय) > 0) अणु
		persistent_घड़ी_exists = true;
	पूर्ण अन्यथा अगर (बारpec64_to_ns(&wall_समय) != 0) अणु
		pr_warn("Persistent clock returned invalid value");
		wall_समय = (काष्ठा बारpec64)अणु0पूर्ण;
	पूर्ण

	अगर (बारpec64_compare(&wall_समय, &boot_offset) < 0)
		boot_offset = (काष्ठा बारpec64)अणु0पूर्ण;

	/*
	 * We want set wall_to_mono, so the following is true:
	 * wall समय + wall_to_mono = boot समय
	 */
	wall_to_mono = बारpec64_sub(boot_offset, wall_समय);

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);
	ग_लिखो_seqcount_begin(&tk_core.seq);
	ntp_init();

	घड़ी = घड़ीsource_शेष_घड़ी();
	अगर (घड़ी->enable)
		घड़ी->enable(घड़ी);
	tk_setup_पूर्णांकernals(tk, घड़ी);

	tk_set_xसमय(tk, &wall_समय);
	tk->raw_sec = 0;

	tk_set_wall_to_mono(tk, wall_to_mono);

	समयkeeping_update(tk, TK_MIRROR | TK_CLOCK_WAS_SET);

	ग_लिखो_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);
पूर्ण

/* समय in seconds when suspend began क्रम persistent घड़ी */
अटल काष्ठा बारpec64 समयkeeping_suspend_समय;

/**
 * __समयkeeping_inject_sleepसमय - Internal function to add sleep पूर्णांकerval
 * @tk:		Poपूर्णांकer to the समयkeeper to be updated
 * @delta:	Poपूर्णांकer to the delta value in बारpec64 क्रमmat
 *
 * Takes a बारpec offset measuring a suspend पूर्णांकerval and properly
 * adds the sleep offset to the समयkeeping variables.
 */
अटल व्योम __समयkeeping_inject_sleepसमय(काष्ठा समयkeeper *tk,
					   स्थिर काष्ठा बारpec64 *delta)
अणु
	अगर (!बारpec64_valid_strict(delta)) अणु
		prपूर्णांकk_deferred(KERN_WARNING
				"__timekeeping_inject_sleeptime: Invalid "
				"sleep delta value!\n");
		वापस;
	पूर्ण
	tk_xसमय_add(tk, delta);
	tk_set_wall_to_mono(tk, बारpec64_sub(tk->wall_to_monotonic, *delta));
	tk_update_sleep_समय(tk, बारpec64_to_kसमय(*delta));
	tk_debug_account_sleep_समय(delta);
पूर्ण

#अगर defined(CONFIG_PM_SLEEP) && defined(CONFIG_RTC_HCTOSYS_DEVICE)
/**
 * We have three kinds of समय sources to use क्रम sleep समय
 * injection, the preference order is:
 * 1) non-stop घड़ीsource
 * 2) persistent घड़ी (ie: RTC accessible when irqs are off)
 * 3) RTC
 *
 * 1) and 2) are used by समयkeeping, 3) by RTC subप्रणाली.
 * If प्रणाली has neither 1) nor 2), 3) will be used finally.
 *
 *
 * If समयkeeping has injected sleepसमय via either 1) or 2),
 * 3) becomes needless, so in this हाल we करोn't need to call
 * rtc_resume(), and this is what समयkeeping_rtc_skipresume()
 * means.
 */
bool समयkeeping_rtc_skipresume(व्योम)
अणु
	वापस !suspend_timing_needed;
पूर्ण

/**
 * 1) can be determined whether to use or not only when करोing
 * समयkeeping_resume() which is invoked after rtc_suspend(),
 * so we can't skip rtc_suspend() surely अगर प्रणाली has 1).
 *
 * But अगर प्रणाली has 2), 2) will definitely be used, so in this
 * हाल we करोn't need to call rtc_suspend(), and this is what
 * समयkeeping_rtc_skipsuspend() means.
 */
bool समयkeeping_rtc_skipsuspend(व्योम)
अणु
	वापस persistent_घड़ी_exists;
पूर्ण

/**
 * समयkeeping_inject_sleepसमय64 - Adds suspend पूर्णांकerval to समयekeeping values
 * @delta: poपूर्णांकer to a बारpec64 delta value
 *
 * This hook is क्रम architectures that cannot support पढ़ो_persistent_घड़ी64
 * because their RTC/persistent घड़ी is only accessible when irqs are enabled.
 * and also करोn't have an effective nonstop घड़ीsource.
 *
 * This function should only be called by rtc_resume(), and allows
 * a suspend offset to be injected पूर्णांकo the समयkeeping values.
 */
व्योम समयkeeping_inject_sleepसमय64(स्थिर काष्ठा बारpec64 *delta)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);
	ग_लिखो_seqcount_begin(&tk_core.seq);

	suspend_timing_needed = false;

	समयkeeping_क्रमward_now(tk);

	__समयkeeping_inject_sleepसमय(tk, delta);

	समयkeeping_update(tk, TK_CLEAR_NTP | TK_MIRROR | TK_CLOCK_WAS_SET);

	ग_लिखो_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);

	/* संकेत hrसमयrs about समय change */
	घड़ी_was_set();
पूर्ण
#पूर्ण_अगर

/**
 * समयkeeping_resume - Resumes the generic समयkeeping subप्रणाली.
 */
व्योम समयkeeping_resume(व्योम)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	काष्ठा घड़ीsource *घड़ी = tk->tkr_mono.घड़ी;
	अचिन्हित दीर्घ flags;
	काष्ठा बारpec64 ts_new, ts_delta;
	u64 cycle_now, nsec;
	bool inject_sleepसमय = false;

	पढ़ो_persistent_घड़ी64(&ts_new);

	घड़ीevents_resume();
	घड़ीsource_resume();

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);
	ग_लिखो_seqcount_begin(&tk_core.seq);

	/*
	 * After प्रणाली resumes, we need to calculate the suspended समय and
	 * compensate it क्रम the OS समय. There are 3 sources that could be
	 * used: Nonstop घड़ीsource during suspend, persistent घड़ी and rtc
	 * device.
	 *
	 * One specअगरic platक्रमm may have 1 or 2 or all of them, and the
	 * preference will be:
	 *	suspend-nonstop घड़ीsource -> persistent घड़ी -> rtc
	 * The less preferred source will only be tried अगर there is no better
	 * usable source. The rtc part is handled separately in rtc core code.
	 */
	cycle_now = tk_घड़ी_पढ़ो(&tk->tkr_mono);
	nsec = घड़ीsource_stop_suspend_timing(घड़ी, cycle_now);
	अगर (nsec > 0) अणु
		ts_delta = ns_to_बारpec64(nsec);
		inject_sleepसमय = true;
	पूर्ण अन्यथा अगर (बारpec64_compare(&ts_new, &समयkeeping_suspend_समय) > 0) अणु
		ts_delta = बारpec64_sub(ts_new, समयkeeping_suspend_समय);
		inject_sleepसमय = true;
	पूर्ण

	अगर (inject_sleepसमय) अणु
		suspend_timing_needed = false;
		__समयkeeping_inject_sleepसमय(tk, &ts_delta);
	पूर्ण

	/* Re-base the last cycle value */
	tk->tkr_mono.cycle_last = cycle_now;
	tk->tkr_raw.cycle_last  = cycle_now;

	tk->ntp_error = 0;
	समयkeeping_suspended = 0;
	समयkeeping_update(tk, TK_MIRROR | TK_CLOCK_WAS_SET);
	ग_लिखो_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);

	touch_softlockup_watchकरोg();

	tick_resume();
	hrसमयrs_resume();
पूर्ण

पूर्णांक समयkeeping_suspend(व्योम)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित दीर्घ flags;
	काष्ठा बारpec64		delta, delta_delta;
	अटल काष्ठा बारpec64	old_delta;
	काष्ठा घड़ीsource *curr_घड़ी;
	u64 cycle_now;

	पढ़ो_persistent_घड़ी64(&समयkeeping_suspend_समय);

	/*
	 * On some प्रणालीs the persistent_घड़ी can not be detected at
	 * समयkeeping_init by its वापस value, so अगर we see a valid
	 * value वापसed, update the persistent_घड़ी_exists flag.
	 */
	अगर (समयkeeping_suspend_समय.tv_sec || समयkeeping_suspend_समय.tv_nsec)
		persistent_घड़ी_exists = true;

	suspend_timing_needed = true;

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);
	ग_लिखो_seqcount_begin(&tk_core.seq);
	समयkeeping_क्रमward_now(tk);
	समयkeeping_suspended = 1;

	/*
	 * Since we've called क्रमward_now, cycle_last stores the value
	 * just पढ़ो from the current घड़ीsource. Save this to potentially
	 * use in suspend timing.
	 */
	curr_घड़ी = tk->tkr_mono.घड़ी;
	cycle_now = tk->tkr_mono.cycle_last;
	घड़ीsource_start_suspend_timing(curr_घड़ी, cycle_now);

	अगर (persistent_घड़ी_exists) अणु
		/*
		 * To aव्योम drअगरt caused by repeated suspend/resumes,
		 * which each can add ~1 second drअगरt error,
		 * try to compensate so the dअगरference in प्रणाली समय
		 * and persistent_घड़ी समय stays बंद to स्थिरant.
		 */
		delta = बारpec64_sub(tk_xसमय(tk), समयkeeping_suspend_समय);
		delta_delta = बारpec64_sub(delta, old_delta);
		अगर (असल(delta_delta.tv_sec) >= 2) अणु
			/*
			 * अगर delta_delta is too large, assume समय correction
			 * has occurred and set old_delta to the current delta.
			 */
			old_delta = delta;
		पूर्ण अन्यथा अणु
			/* Otherwise try to adjust old_प्रणाली to compensate */
			समयkeeping_suspend_समय =
				बारpec64_add(समयkeeping_suspend_समय, delta_delta);
		पूर्ण
	पूर्ण

	समयkeeping_update(tk, TK_MIRROR);
	halt_fast_समयkeeper(tk);
	ग_लिखो_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);

	tick_suspend();
	घड़ीsource_suspend();
	घड़ीevents_suspend();

	वापस 0;
पूर्ण

/* sysfs resume/suspend bits क्रम समयkeeping */
अटल काष्ठा syscore_ops समयkeeping_syscore_ops = अणु
	.resume		= समयkeeping_resume,
	.suspend	= समयkeeping_suspend,
पूर्ण;

अटल पूर्णांक __init समयkeeping_init_ops(व्योम)
अणु
	रेजिस्टर_syscore_ops(&समयkeeping_syscore_ops);
	वापस 0;
पूर्ण
device_initcall(समयkeeping_init_ops);

/*
 * Apply a multiplier adjusपंचांगent to the समयkeeper
 */
अटल __always_अंतरभूत व्योम समयkeeping_apply_adjusपंचांगent(काष्ठा समयkeeper *tk,
							 s64 offset,
							 s32 mult_adj)
अणु
	s64 पूर्णांकerval = tk->cycle_पूर्णांकerval;

	अगर (mult_adj == 0) अणु
		वापस;
	पूर्ण अन्यथा अगर (mult_adj == -1) अणु
		पूर्णांकerval = -पूर्णांकerval;
		offset = -offset;
	पूर्ण अन्यथा अगर (mult_adj != 1) अणु
		पूर्णांकerval *= mult_adj;
		offset *= mult_adj;
	पूर्ण

	/*
	 * So the following can be confusing.
	 *
	 * To keep things simple, lets assume mult_adj == 1 क्रम now.
	 *
	 * When mult_adj != 1, remember that the पूर्णांकerval and offset values
	 * have been appropriately scaled so the math is the same.
	 *
	 * The basic idea here is that we're increasing the multiplier
	 * by one, this causes the xसमय_पूर्णांकerval to be incremented by
	 * one cycle_पूर्णांकerval. This is because:
	 *	xसमय_पूर्णांकerval = cycle_पूर्णांकerval * mult
	 * So अगर mult is being incremented by one:
	 *	xसमय_पूर्णांकerval = cycle_पूर्णांकerval * (mult + 1)
	 * Its the same as:
	 *	xसमय_पूर्णांकerval = (cycle_पूर्णांकerval * mult) + cycle_पूर्णांकerval
	 * Which can be लघुened to:
	 *	xसमय_पूर्णांकerval += cycle_पूर्णांकerval
	 *
	 * So offset stores the non-accumulated cycles. Thus the current
	 * समय (in shअगरted nanoseconds) is:
	 *	now = (offset * adj) + xसमय_nsec
	 * Now, even though we're adjusting the घड़ी frequency, we have
	 * to keep समय consistent. In other words, we can't jump back
	 * in समय, and we also want to aव्योम jumping क्रमward in समय.
	 *
	 * So given the same offset value, we need the समय to be the same
	 * both beक्रमe and after the freq adjusपंचांगent.
	 *	now = (offset * adj_1) + xसमय_nsec_1
	 *	now = (offset * adj_2) + xसमय_nsec_2
	 * So:
	 *	(offset * adj_1) + xसमय_nsec_1 =
	 *		(offset * adj_2) + xसमय_nsec_2
	 * And we know:
	 *	adj_2 = adj_1 + 1
	 * So:
	 *	(offset * adj_1) + xसमय_nsec_1 =
	 *		(offset * (adj_1+1)) + xसमय_nsec_2
	 *	(offset * adj_1) + xसमय_nsec_1 =
	 *		(offset * adj_1) + offset + xसमय_nsec_2
	 * Canceling the sides:
	 *	xसमय_nsec_1 = offset + xसमय_nsec_2
	 * Which gives us:
	 *	xसमय_nsec_2 = xसमय_nsec_1 - offset
	 * Which simplअगरies to:
	 *	xसमय_nsec -= offset
	 */
	अगर ((mult_adj > 0) && (tk->tkr_mono.mult + mult_adj < mult_adj)) अणु
		/* NTP adjusपंचांगent caused घड़ीsource mult overflow */
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	tk->tkr_mono.mult += mult_adj;
	tk->xसमय_पूर्णांकerval += पूर्णांकerval;
	tk->tkr_mono.xसमय_nsec -= offset;
पूर्ण

/*
 * Adjust the समयkeeper's multiplier to the correct frequency
 * and also to reduce the accumulated error value.
 */
अटल व्योम समयkeeping_adjust(काष्ठा समयkeeper *tk, s64 offset)
अणु
	u32 mult;

	/*
	 * Determine the multiplier from the current NTP tick length.
	 * Aव्योम expensive भागision when the tick length करोesn't change.
	 */
	अगर (likely(tk->ntp_tick == ntp_tick_length())) अणु
		mult = tk->tkr_mono.mult - tk->ntp_err_mult;
	पूर्ण अन्यथा अणु
		tk->ntp_tick = ntp_tick_length();
		mult = भाग64_u64((tk->ntp_tick >> tk->ntp_error_shअगरt) -
				 tk->xसमय_reमुख्यder, tk->cycle_पूर्णांकerval);
	पूर्ण

	/*
	 * If the घड़ी is behind the NTP समय, increase the multiplier by 1
	 * to catch up with it. If it's ahead and there was a reमुख्यder in the
	 * tick भागision, the घड़ी will slow करोwn. Otherwise it will stay
	 * ahead until the tick length changes to a non-भागisible value.
	 */
	tk->ntp_err_mult = tk->ntp_error > 0 ? 1 : 0;
	mult += tk->ntp_err_mult;

	समयkeeping_apply_adjusपंचांगent(tk, offset, mult - tk->tkr_mono.mult);

	अगर (unlikely(tk->tkr_mono.घड़ी->maxadj &&
		(असल(tk->tkr_mono.mult - tk->tkr_mono.घड़ी->mult)
			> tk->tkr_mono.घड़ी->maxadj))) अणु
		prपूर्णांकk_once(KERN_WARNING
			"Adjusting %s more than 11%% (%ld vs %ld)\n",
			tk->tkr_mono.घड़ी->name, (दीर्घ)tk->tkr_mono.mult,
			(दीर्घ)tk->tkr_mono.घड़ी->mult + tk->tkr_mono.घड़ी->maxadj);
	पूर्ण

	/*
	 * It may be possible that when we entered this function, xसमय_nsec
	 * was very small.  Further, अगर we're slightly speeding the घड़ीsource
	 * in the code above, its possible the required corrective factor to
	 * xसमय_nsec could cause it to underflow.
	 *
	 * Now, since we have alपढ़ोy accumulated the second and the NTP
	 * subप्रणाली has been notअगरied via second_overflow(), we need to skip
	 * the next update.
	 */
	अगर (unlikely((s64)tk->tkr_mono.xसमय_nsec < 0)) अणु
		tk->tkr_mono.xसमय_nsec += (u64)NSEC_PER_SEC <<
							tk->tkr_mono.shअगरt;
		tk->xसमय_sec--;
		tk->skip_second_overflow = 1;
	पूर्ण
पूर्ण

/*
 * accumulate_nsecs_to_secs - Accumulates nsecs पूर्णांकo secs
 *
 * Helper function that accumulates the nsecs greater than a second
 * from the xसमय_nsec field to the xसमय_secs field.
 * It also calls पूर्णांकo the NTP code to handle leapsecond processing.
 */
अटल अंतरभूत अचिन्हित पूर्णांक accumulate_nsecs_to_secs(काष्ठा समयkeeper *tk)
अणु
	u64 nsecps = (u64)NSEC_PER_SEC << tk->tkr_mono.shअगरt;
	अचिन्हित पूर्णांक घड़ी_set = 0;

	जबतक (tk->tkr_mono.xसमय_nsec >= nsecps) अणु
		पूर्णांक leap;

		tk->tkr_mono.xसमय_nsec -= nsecps;
		tk->xसमय_sec++;

		/*
		 * Skip NTP update अगर this second was accumulated beक्रमe,
		 * i.e. xसमय_nsec underflowed in समयkeeping_adjust()
		 */
		अगर (unlikely(tk->skip_second_overflow)) अणु
			tk->skip_second_overflow = 0;
			जारी;
		पूर्ण

		/* Figure out अगर its a leap sec and apply अगर needed */
		leap = second_overflow(tk->xसमय_sec);
		अगर (unlikely(leap)) अणु
			काष्ठा बारpec64 ts;

			tk->xसमय_sec += leap;

			ts.tv_sec = leap;
			ts.tv_nsec = 0;
			tk_set_wall_to_mono(tk,
				बारpec64_sub(tk->wall_to_monotonic, ts));

			__समयkeeping_set_tai_offset(tk, tk->tai_offset - leap);

			घड़ी_set = TK_CLOCK_WAS_SET;
		पूर्ण
	पूर्ण
	वापस घड़ी_set;
पूर्ण

/*
 * logarithmic_accumulation - shअगरted accumulation of cycles
 *
 * This functions accumulates a shअगरted पूर्णांकerval of cycles पूर्णांकo
 * a shअगरted पूर्णांकerval nanoseconds. Allows क्रम O(log) accumulation
 * loop.
 *
 * Returns the unconsumed cycles.
 */
अटल u64 logarithmic_accumulation(काष्ठा समयkeeper *tk, u64 offset,
				    u32 shअगरt, अचिन्हित पूर्णांक *घड़ी_set)
अणु
	u64 पूर्णांकerval = tk->cycle_पूर्णांकerval << shअगरt;
	u64 snsec_per_sec;

	/* If the offset is smaller than a shअगरted पूर्णांकerval, करो nothing */
	अगर (offset < पूर्णांकerval)
		वापस offset;

	/* Accumulate one shअगरted पूर्णांकerval */
	offset -= पूर्णांकerval;
	tk->tkr_mono.cycle_last += पूर्णांकerval;
	tk->tkr_raw.cycle_last  += पूर्णांकerval;

	tk->tkr_mono.xसमय_nsec += tk->xसमय_पूर्णांकerval << shअगरt;
	*घड़ी_set |= accumulate_nsecs_to_secs(tk);

	/* Accumulate raw समय */
	tk->tkr_raw.xसमय_nsec += tk->raw_पूर्णांकerval << shअगरt;
	snsec_per_sec = (u64)NSEC_PER_SEC << tk->tkr_raw.shअगरt;
	जबतक (tk->tkr_raw.xसमय_nsec >= snsec_per_sec) अणु
		tk->tkr_raw.xसमय_nsec -= snsec_per_sec;
		tk->raw_sec++;
	पूर्ण

	/* Accumulate error between NTP and घड़ी पूर्णांकerval */
	tk->ntp_error += tk->ntp_tick << shअगरt;
	tk->ntp_error -= (tk->xसमय_पूर्णांकerval + tk->xसमय_reमुख्यder) <<
						(tk->ntp_error_shअगरt + shअगरt);

	वापस offset;
पूर्ण

/*
 * समयkeeping_advance - Updates the समयkeeper to the current समय and
 * current NTP tick length
 */
अटल व्योम समयkeeping_advance(क्रमागत समयkeeping_adv_mode mode)
अणु
	काष्ठा समयkeeper *real_tk = &tk_core.समयkeeper;
	काष्ठा समयkeeper *tk = &shaकरोw_समयkeeper;
	u64 offset;
	पूर्णांक shअगरt = 0, maxshअगरt;
	अचिन्हित पूर्णांक घड़ी_set = 0;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);

	/* Make sure we're fully resumed: */
	अगर (unlikely(समयkeeping_suspended))
		जाओ out;

	offset = घड़ीsource_delta(tk_घड़ी_पढ़ो(&tk->tkr_mono),
				   tk->tkr_mono.cycle_last, tk->tkr_mono.mask);

	/* Check अगर there's really nothing to करो */
	अगर (offset < real_tk->cycle_पूर्णांकerval && mode == TK_ADV_TICK)
		जाओ out;

	/* Do some additional sanity checking */
	समयkeeping_check_update(tk, offset);

	/*
	 * With NO_HZ we may have to accumulate many cycle_पूर्णांकervals
	 * (think "ticks") worth of समय at once. To करो this efficiently,
	 * we calculate the largest करोubling multiple of cycle_पूर्णांकervals
	 * that is smaller than the offset.  We then accumulate that
	 * chunk in one go, and then try to consume the next smaller
	 * द्विगुनd multiple.
	 */
	shअगरt = ilog2(offset) - ilog2(tk->cycle_पूर्णांकerval);
	shअगरt = max(0, shअगरt);
	/* Bound shअगरt to one less than what overflows tick_length */
	maxshअगरt = (64 - (ilog2(ntp_tick_length())+1)) - 1;
	shअगरt = min(shअगरt, maxshअगरt);
	जबतक (offset >= tk->cycle_पूर्णांकerval) अणु
		offset = logarithmic_accumulation(tk, offset, shअगरt,
							&घड़ी_set);
		अगर (offset < tk->cycle_पूर्णांकerval<<shअगरt)
			shअगरt--;
	पूर्ण

	/* Adjust the multiplier to correct NTP error */
	समयkeeping_adjust(tk, offset);

	/*
	 * Finally, make sure that after the rounding
	 * xसमय_nsec isn't larger than NSEC_PER_SEC
	 */
	घड़ी_set |= accumulate_nsecs_to_secs(tk);

	ग_लिखो_seqcount_begin(&tk_core.seq);
	/*
	 * Update the real समयkeeper.
	 *
	 * We could aव्योम this स_नकल by चयनing poपूर्णांकers, but that
	 * requires changes to all other समयkeeper usage sites as
	 * well, i.e. move the समयkeeper poपूर्णांकer getter पूर्णांकo the
	 * spinlocked/seqcount रक्षित sections. And we trade this
	 * स_नकल under the tk_core.seq against one beक्रमe we start
	 * updating.
	 */
	समयkeeping_update(tk, घड़ी_set);
	स_नकल(real_tk, tk, माप(*tk));
	/* The स_नकल must come last. Do not put anything here! */
	ग_लिखो_seqcount_end(&tk_core.seq);
out:
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);
	अगर (घड़ी_set)
		/* Have to call _delayed version, since in irq context*/
		घड़ी_was_set_delayed();
पूर्ण

/**
 * update_wall_समय - Uses the current घड़ीsource to increment the wall समय
 *
 */
व्योम update_wall_समय(व्योम)
अणु
	समयkeeping_advance(TK_ADV_TICK);
पूर्ण

/**
 * getbootसमय64 - Return the real समय of प्रणाली boot.
 * @ts:		poपूर्णांकer to the बारpec64 to be set
 *
 * Returns the wall-समय of boot in a बारpec64.
 *
 * This is based on the wall_to_monotonic offset and the total suspend
 * समय. Calls to समय_रखोofday will affect the value वापसed (which
 * basically means that however wrong your real समय घड़ी is at boot समय,
 * you get the right समय here).
 */
व्योम getbootसमय64(काष्ठा बारpec64 *ts)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	kसमय_प्रकार t = kसमय_sub(tk->offs_real, tk->offs_boot);

	*ts = kसमय_प्रकारo_बारpec64(t);
पूर्ण
EXPORT_SYMBOL_GPL(getbootसमय64);

व्योम kसमय_get_coarse_real_ts64(काष्ठा बारpec64 *ts)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);

		*ts = tk_xसमय(tk);
	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));
पूर्ण
EXPORT_SYMBOL(kसमय_get_coarse_real_ts64);

व्योम kसमय_get_coarse_ts64(काष्ठा बारpec64 *ts)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	काष्ठा बारpec64 now, mono;
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);

		now = tk_xसमय(tk);
		mono = tk->wall_to_monotonic;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	set_normalized_बारpec64(ts, now.tv_sec + mono.tv_sec,
				now.tv_nsec + mono.tv_nsec);
पूर्ण
EXPORT_SYMBOL(kसमय_get_coarse_ts64);

/*
 * Must hold jअगरfies_lock
 */
व्योम करो_समयr(अचिन्हित दीर्घ ticks)
अणु
	jअगरfies_64 += ticks;
	calc_global_load();
पूर्ण

/**
 * kसमय_get_update_offsets_now - hrसमयr helper
 * @cwsseq:	poपूर्णांकer to check and store the घड़ी was set sequence number
 * @offs_real:	poपूर्णांकer to storage क्रम monotonic -> realसमय offset
 * @offs_boot:	poपूर्णांकer to storage क्रम monotonic -> bootसमय offset
 * @offs_tai:	poपूर्णांकer to storage क्रम monotonic -> घड़ी tai offset
 *
 * Returns current monotonic समय and updates the offsets अगर the
 * sequence number in @cwsseq and समयkeeper.घड़ी_was_set_seq are
 * dअगरferent.
 *
 * Called from hrसमयr_पूर्णांकerrupt() or retrigger_next_event()
 */
kसमय_प्रकार kसमय_get_update_offsets_now(अचिन्हित पूर्णांक *cwsseq, kसमय_प्रकार *offs_real,
				     kसमय_प्रकार *offs_boot, kसमय_प्रकार *offs_tai)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	अचिन्हित पूर्णांक seq;
	kसमय_प्रकार base;
	u64 nsecs;

	करो अणु
		seq = पढ़ो_seqcount_begin(&tk_core.seq);

		base = tk->tkr_mono.base;
		nsecs = समयkeeping_get_ns(&tk->tkr_mono);
		base = kसमय_add_ns(base, nsecs);

		अगर (*cwsseq != tk->घड़ी_was_set_seq) अणु
			*cwsseq = tk->घड़ी_was_set_seq;
			*offs_real = tk->offs_real;
			*offs_boot = tk->offs_boot;
			*offs_tai = tk->offs_tai;
		पूर्ण

		/* Handle leapsecond insertion adjusपंचांगents */
		अगर (unlikely(base >= tk->next_leap_kसमय))
			*offs_real = kसमय_sub(tk->offs_real, kसमय_set(1, 0));

	पूर्ण जबतक (पढ़ो_seqcount_retry(&tk_core.seq, seq));

	वापस base;
पूर्ण

/*
 * समयkeeping_validate_समयx - Ensures the समयx is ok क्रम use in करो_adjसमयx
 */
अटल पूर्णांक समयkeeping_validate_समयx(स्थिर काष्ठा __kernel_समयx *txc)
अणु
	अगर (txc->modes & ADJ_ADJTIME) अणु
		/* singleshot must not be used with any other mode bits */
		अगर (!(txc->modes & ADJ_OFFSET_SINGLESHOT))
			वापस -EINVAL;
		अगर (!(txc->modes & ADJ_OFFSET_READONLY) &&
		    !capable(CAP_SYS_TIME))
			वापस -EPERM;
	पूर्ण अन्यथा अणु
		/* In order to modअगरy anything, you gotta be super-user! */
		अगर (txc->modes && !capable(CAP_SYS_TIME))
			वापस -EPERM;
		/*
		 * अगर the quartz is off by more than 10% then
		 * something is VERY wrong!
		 */
		अगर (txc->modes & ADJ_TICK &&
		    (txc->tick <  900000/USER_HZ ||
		     txc->tick > 1100000/USER_HZ))
			वापस -EINVAL;
	पूर्ण

	अगर (txc->modes & ADJ_SETOFFSET) अणु
		/* In order to inject समय, you gotta be super-user! */
		अगर (!capable(CAP_SYS_TIME))
			वापस -EPERM;

		/*
		 * Validate अगर a बारpec/समयval used to inject a समय
		 * offset is valid.  Offsets can be positive or negative, so
		 * we करोn't check tv_sec. The value of the समयval/बारpec
		 * is the sum of its fields,but *NOTE*:
		 * The field tv_usec/tv_nsec must always be non-negative and
		 * we can't have more nanoseconds/microseconds than a second.
		 */
		अगर (txc->समय.tv_usec < 0)
			वापस -EINVAL;

		अगर (txc->modes & ADJ_न_अंकO) अणु
			अगर (txc->समय.tv_usec >= NSEC_PER_SEC)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (txc->समय.tv_usec >= USEC_PER_SEC)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Check क्रम potential multiplication overflows that can
	 * only happen on 64-bit प्रणालीs:
	 */
	अगर ((txc->modes & ADJ_FREQUENCY) && (BITS_PER_LONG == 64)) अणु
		अगर (Lदीर्घ_न्यून / PPM_SCALE > txc->freq)
			वापस -EINVAL;
		अगर (Lदीर्घ_उच्च / PPM_SCALE < txc->freq)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


/**
 * करो_adjसमयx() - Accessor function to NTP __करो_adjसमयx function
 */
पूर्णांक करो_adjसमयx(काष्ठा __kernel_समयx *txc)
अणु
	काष्ठा समयkeeper *tk = &tk_core.समयkeeper;
	काष्ठा audit_ntp_data ad;
	अचिन्हित दीर्घ flags;
	काष्ठा बारpec64 ts;
	s32 orig_tai, tai;
	पूर्णांक ret;

	/* Validate the data beक्रमe disabling पूर्णांकerrupts */
	ret = समयkeeping_validate_समयx(txc);
	अगर (ret)
		वापस ret;

	अगर (txc->modes & ADJ_SETOFFSET) अणु
		काष्ठा बारpec64 delta;
		delta.tv_sec  = txc->समय.tv_sec;
		delta.tv_nsec = txc->समय.tv_usec;
		अगर (!(txc->modes & ADJ_न_अंकO))
			delta.tv_nsec *= 1000;
		ret = समयkeeping_inject_offset(&delta);
		अगर (ret)
			वापस ret;

		audit_tk_injoffset(delta);
	पूर्ण

	audit_ntp_init(&ad);

	kसमय_get_real_ts64(&ts);

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);
	ग_लिखो_seqcount_begin(&tk_core.seq);

	orig_tai = tai = tk->tai_offset;
	ret = __करो_adjसमयx(txc, &ts, &tai, &ad);

	अगर (tai != orig_tai) अणु
		__समयkeeping_set_tai_offset(tk, tai);
		समयkeeping_update(tk, TK_MIRROR | TK_CLOCK_WAS_SET);
	पूर्ण
	tk_update_leap_state(tk);

	ग_लिखो_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);

	audit_ntp_log(&ad);

	/* Update the multiplier immediately अगर frequency was set directly */
	अगर (txc->modes & (ADJ_FREQUENCY | ADJ_TICK))
		समयkeeping_advance(TK_ADV_FREQ);

	अगर (tai != orig_tai)
		घड़ी_was_set();

	ntp_notअगरy_cmos_समयr();

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_NTP_PPS
/**
 * hardpps() - Accessor function to NTP __hardpps function
 */
व्योम hardpps(स्थिर काष्ठा बारpec64 *phase_ts, स्थिर काष्ठा बारpec64 *raw_ts)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);
	ग_लिखो_seqcount_begin(&tk_core.seq);

	__hardpps(phase_ts, raw_ts);

	ग_लिखो_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);
पूर्ण
EXPORT_SYMBOL(hardpps);
#पूर्ण_अगर /* CONFIG_NTP_PPS */
