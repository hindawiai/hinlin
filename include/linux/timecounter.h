<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * linux/include/linux/समयcounter.h
 *
 * based on code that migrated away from
 * linux/include/linux/घड़ीsource.h
 */
#अगर_अघोषित _LINUX_TIMECOUNTER_H
#घोषणा _LINUX_TIMECOUNTER_H

#समावेश <linux/types.h>

/* simplअगरy initialization of mask field */
#घोषणा CYCLECOUNTER_MASK(bits) (u64)((bits) < 64 ? ((1ULL<<(bits))-1) : -1)

/**
 * काष्ठा cyclecounter - hardware असलtraction क्रम a मुक्त running counter
 *	Provides completely state-मुक्त accessors to the underlying hardware.
 *	Depending on which hardware it पढ़ोs, the cycle counter may wrap
 *	around quickly. Locking rules (अगर necessary) have to be defined
 *	by the implementor and user of specअगरic instances of this API.
 *
 * @पढ़ो:		वापसs the current cycle value
 * @mask:		biपंचांगask क्रम two's complement
 *			subtraction of non 64 bit counters,
 *			see CYCLECOUNTER_MASK() helper macro
 * @mult:		cycle to nanosecond multiplier
 * @shअगरt:		cycle to nanosecond भागisor (घातer of two)
 */
काष्ठा cyclecounter अणु
	u64 (*पढ़ो)(स्थिर काष्ठा cyclecounter *cc);
	u64 mask;
	u32 mult;
	u32 shअगरt;
पूर्ण;

/**
 * काष्ठा समयcounter - layer above a %काष्ठा cyclecounter which counts nanoseconds
 *	Contains the state needed by समयcounter_पढ़ो() to detect
 *	cycle counter wrap around. Initialize with
 *	समयcounter_init(). Also used to convert cycle counts पूर्णांकo the
 *	corresponding nanosecond counts with समयcounter_cyc2समय(). Users
 *	of this code are responsible क्रम initializing the underlying
 *	cycle counter hardware, locking issues and पढ़ोing the समय
 *	more often than the cycle counter wraps around. The nanosecond
 *	counter will only wrap around after ~585 years.
 *
 * @cc:			the cycle counter used by this instance
 * @cycle_last:		most recent cycle counter value seen by
 *			समयcounter_पढ़ो()
 * @nsec:		continuously increasing count
 * @mask:		bit mask क्रम मुख्यtaining the 'frac' field
 * @frac:		accumulated fractional nanoseconds
 */
काष्ठा समयcounter अणु
	स्थिर काष्ठा cyclecounter *cc;
	u64 cycle_last;
	u64 nsec;
	u64 mask;
	u64 frac;
पूर्ण;

/**
 * cyclecounter_cyc2ns - converts cycle counter cycles to nanoseconds
 * @cc:		Poपूर्णांकer to cycle counter.
 * @cycles:	Cycles
 * @mask:	bit mask क्रम मुख्यtaining the 'frac' field
 * @frac:	poपूर्णांकer to storage क्रम the fractional nanoseconds.
 */
अटल अंतरभूत u64 cyclecounter_cyc2ns(स्थिर काष्ठा cyclecounter *cc,
				      u64 cycles, u64 mask, u64 *frac)
अणु
	u64 ns = (u64) cycles;

	ns = (ns * cc->mult) + *frac;
	*frac = ns & mask;
	वापस ns >> cc->shअगरt;
पूर्ण

/**
 * समयcounter_adjसमय - Shअगरts the समय of the घड़ी.
 * @delta:	Desired change in nanoseconds.
 */
अटल अंतरभूत व्योम समयcounter_adjसमय(काष्ठा समयcounter *tc, s64 delta)
अणु
	tc->nsec += delta;
पूर्ण

/**
 * समयcounter_init - initialize a समय counter
 * @tc:			Poपूर्णांकer to समय counter which is to be initialized/reset
 * @cc:			A cycle counter, पढ़ोy to be used.
 * @start_tstamp:	Arbitrary initial समय stamp.
 *
 * After this call the current cycle रेजिस्टर (roughly) corresponds to
 * the initial समय stamp. Every call to समयcounter_पढ़ो() increments
 * the समय stamp counter by the number of elapsed nanoseconds.
 */
बाह्य व्योम समयcounter_init(काष्ठा समयcounter *tc,
			     स्थिर काष्ठा cyclecounter *cc,
			     u64 start_tstamp);

/**
 * समयcounter_पढ़ो - वापस nanoseconds elapsed since समयcounter_init()
 *                    plus the initial समय stamp
 * @tc:          Poपूर्णांकer to समय counter.
 *
 * In other words, keeps track of समय since the same epoch as
 * the function which generated the initial समय stamp.
 */
बाह्य u64 समयcounter_पढ़ो(काष्ठा समयcounter *tc);

/**
 * समयcounter_cyc2समय - convert a cycle counter to same
 *                        समय base as values वापसed by
 *                        समयcounter_पढ़ो()
 * @tc:		Poपूर्णांकer to समय counter.
 * @cycle_tstamp:	a value वापसed by tc->cc->पढ़ो()
 *
 * Cycle counts that are converted correctly as दीर्घ as they
 * fall पूर्णांकo the पूर्णांकerval [-1/2 max cycle count, +1/2 max cycle count],
 * with "max cycle count" == cs->mask+1.
 *
 * This allows conversion of cycle counter values which were generated
 * in the past.
 */
बाह्य u64 समयcounter_cyc2समय(स्थिर काष्ठा समयcounter *tc,
				u64 cycle_tstamp);

#पूर्ण_अगर
