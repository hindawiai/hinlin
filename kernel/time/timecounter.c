<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Based on घड़ीsource code. See commit 74d23cc704d1
 */
#समावेश <linux/export.h>
#समावेश <linux/समयcounter.h>

व्योम समयcounter_init(काष्ठा समयcounter *tc,
		      स्थिर काष्ठा cyclecounter *cc,
		      u64 start_tstamp)
अणु
	tc->cc = cc;
	tc->cycle_last = cc->पढ़ो(cc);
	tc->nsec = start_tstamp;
	tc->mask = (1ULL << cc->shअगरt) - 1;
	tc->frac = 0;
पूर्ण
EXPORT_SYMBOL_GPL(समयcounter_init);

/**
 * समयcounter_पढ़ो_delta - get nanoseconds since last call of this function
 * @tc:         Poपूर्णांकer to समय counter
 *
 * When the underlying cycle counter runs over, this will be handled
 * correctly as दीर्घ as it करोes not run over more than once between
 * calls.
 *
 * The first call to this function क्रम a new समय counter initializes
 * the समय tracking and वापसs an undefined result.
 */
अटल u64 समयcounter_पढ़ो_delta(काष्ठा समयcounter *tc)
अणु
	u64 cycle_now, cycle_delta;
	u64 ns_offset;

	/* पढ़ो cycle counter: */
	cycle_now = tc->cc->पढ़ो(tc->cc);

	/* calculate the delta since the last समयcounter_पढ़ो_delta(): */
	cycle_delta = (cycle_now - tc->cycle_last) & tc->cc->mask;

	/* convert to nanoseconds: */
	ns_offset = cyclecounter_cyc2ns(tc->cc, cycle_delta,
					tc->mask, &tc->frac);

	/* update समय stamp of समयcounter_पढ़ो_delta() call: */
	tc->cycle_last = cycle_now;

	वापस ns_offset;
पूर्ण

u64 समयcounter_पढ़ो(काष्ठा समयcounter *tc)
अणु
	u64 nsec;

	/* increment समय by nanoseconds since last call */
	nsec = समयcounter_पढ़ो_delta(tc);
	nsec += tc->nsec;
	tc->nsec = nsec;

	वापस nsec;
पूर्ण
EXPORT_SYMBOL_GPL(समयcounter_पढ़ो);

/*
 * This is like cyclecounter_cyc2ns(), but it is used क्रम computing a
 * समय previous to the समय stored in the cycle counter.
 */
अटल u64 cc_cyc2ns_backwards(स्थिर काष्ठा cyclecounter *cc,
			       u64 cycles, u64 mask, u64 frac)
अणु
	u64 ns = (u64) cycles;

	ns = ((ns * cc->mult) - frac) >> cc->shअगरt;

	वापस ns;
पूर्ण

u64 समयcounter_cyc2समय(स्थिर काष्ठा समयcounter *tc,
			 u64 cycle_tstamp)
अणु
	u64 delta = (cycle_tstamp - tc->cycle_last) & tc->cc->mask;
	u64 nsec = tc->nsec, frac = tc->frac;

	/*
	 * Instead of always treating cycle_tstamp as more recent
	 * than tc->cycle_last, detect when it is too far in the
	 * future and treat it as old समय stamp instead.
	 */
	अगर (delta > tc->cc->mask / 2) अणु
		delta = (tc->cycle_last - cycle_tstamp) & tc->cc->mask;
		nsec -= cc_cyc2ns_backwards(tc->cc, delta, tc->mask, frac);
	पूर्ण अन्यथा अणु
		nsec += cyclecounter_cyc2ns(tc->cc, delta, tc->mask, &frac);
	पूर्ण

	वापस nsec;
पूर्ण
EXPORT_SYMBOL_GPL(समयcounter_cyc2समय);
