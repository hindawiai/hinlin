<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_JIFFIES_H
#घोषणा _LINUX_JIFFIES_H

#समावेश <linux/cache.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/math64.h>
#समावेश <linux/minmax.h>
#समावेश <linux/types.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <vdso/jअगरfies.h>
#समावेश <यंत्र/param.h>			/* क्रम HZ */
#समावेश <generated/समयस्थिर.h>

/*
 * The following defines establish the engineering parameters of the PLL
 * model. The HZ variable establishes the समयr पूर्णांकerrupt frequency, 100 Hz
 * क्रम the SunOS kernel, 256 Hz क्रम the Ultrix kernel and 1024 Hz क्रम the
 * OSF/1 kernel. The SHIFT_HZ define expresses the same value as the
 * nearest घातer of two in order to aव्योम hardware multiply operations.
 */
#अगर HZ >= 12 && HZ < 24
# define SHIFT_HZ	4
#या_अगर HZ >= 24 && HZ < 48
# define SHIFT_HZ	5
#या_अगर HZ >= 48 && HZ < 96
# define SHIFT_HZ	6
#या_अगर HZ >= 96 && HZ < 192
# define SHIFT_HZ	7
#या_अगर HZ >= 192 && HZ < 384
# define SHIFT_HZ	8
#या_अगर HZ >= 384 && HZ < 768
# define SHIFT_HZ	9
#या_अगर HZ >= 768 && HZ < 1536
# define SHIFT_HZ	10
#या_अगर HZ >= 1536 && HZ < 3072
# define SHIFT_HZ	11
#या_अगर HZ >= 3072 && HZ < 6144
# define SHIFT_HZ	12
#या_अगर HZ >= 6144 && HZ < 12288
# define SHIFT_HZ	13
#अन्यथा
# error Invalid value of HZ.
#पूर्ण_अगर

/* Suppose we want to भागide two numbers NOM and DEN: NOM/DEN, then we can
 * improve accuracy by shअगरting LSH bits, hence calculating:
 *     (NOM << LSH) / DEN
 * This however means trouble क्रम large NOM, because (NOM << LSH) may no
 * दीर्घer fit in 32 bits. The following way of calculating this gives us
 * some slack, under the following conditions:
 *   - (NOM / DEN) fits in (32 - LSH) bits.
 *   - (NOM % DEN) fits in (32 - LSH) bits.
 */
#घोषणा SH_DIV(NOM,DEN,LSH) (   (((NOM) / (DEN)) << (LSH))              \
                             + ((((NOM) % (DEN)) << (LSH)) + (DEN) / 2) / (DEN))

/* LATCH is used in the पूर्णांकerval समयr and ftape setup. */
#घोषणा LATCH ((CLOCK_TICK_RATE + HZ/2) / HZ)	/* For भागider */

बाह्य पूर्णांक रेजिस्टर_refined_jअगरfies(दीर्घ घड़ी_प्रकारick_rate);

/* TICK_USEC is the समय between ticks in usec assuming SHIFTED_HZ */
#घोषणा TICK_USEC ((USEC_PER_SEC + HZ/2) / HZ)

/* USER_TICK_USEC is the समय between ticks in usec assuming fake USER_HZ */
#घोषणा USER_TICK_USEC ((1000000UL + USER_HZ/2) / USER_HZ)

#अगर_अघोषित __jअगरfy_arch_data
#घोषणा __jअगरfy_arch_data
#पूर्ण_अगर

/*
 * The 64-bit value is not atomic - you MUST NOT पढ़ो it
 * without sampling the sequence number in jअगरfies_lock.
 * get_jअगरfies_64() will करो this क्रम you as appropriate.
 */
बाह्य u64 __cacheline_aligned_in_smp jअगरfies_64;
बाह्य अचिन्हित दीर्घ अस्थिर __cacheline_aligned_in_smp __jअगरfy_arch_data jअगरfies;

#अगर (BITS_PER_LONG < 64)
u64 get_jअगरfies_64(व्योम);
#अन्यथा
अटल अंतरभूत u64 get_jअगरfies_64(व्योम)
अणु
	वापस (u64)jअगरfies;
पूर्ण
#पूर्ण_अगर

/*
 *	These अंतरभूतs deal with समयr wrapping correctly. You are 
 *	strongly encouraged to use them
 *	1. Because people otherwise क्रमget
 *	2. Because अगर the समयr wrap changes in future you won't have to
 *	   alter your driver code.
 *
 * समय_after(a,b) वापसs true अगर the समय a is after समय b.
 *
 * Do this with "<0" and ">=0" to only test the sign of the result. A
 * good compiler would generate better code (and a really good compiler
 * wouldn't care). Gcc is currently neither.
 */
#घोषणा समय_after(a,b)		\
	(typecheck(अचिन्हित दीर्घ, a) && \
	 typecheck(अचिन्हित दीर्घ, b) && \
	 ((दीर्घ)((b) - (a)) < 0))
#घोषणा समय_beक्रमe(a,b)	समय_after(b,a)

#घोषणा समय_after_eq(a,b)	\
	(typecheck(अचिन्हित दीर्घ, a) && \
	 typecheck(अचिन्हित दीर्घ, b) && \
	 ((दीर्घ)((a) - (b)) >= 0))
#घोषणा समय_beक्रमe_eq(a,b)	समय_after_eq(b,a)

/*
 * Calculate whether a is in the range of [b, c].
 */
#घोषणा समय_in_range(a,b,c) \
	(समय_after_eq(a,b) && \
	 समय_beक्रमe_eq(a,c))

/*
 * Calculate whether a is in the range of [b, c).
 */
#घोषणा समय_in_range_खोलो(a,b,c) \
	(समय_after_eq(a,b) && \
	 समय_beक्रमe(a,c))

/* Same as above, but करोes so with platक्रमm independent 64bit types.
 * These must be used when utilizing jअगरfies_64 (i.e. वापस value of
 * get_jअगरfies_64() */
#घोषणा समय_after64(a,b)	\
	(typecheck(__u64, a) &&	\
	 typecheck(__u64, b) && \
	 ((__s64)((b) - (a)) < 0))
#घोषणा समय_beक्रमe64(a,b)	समय_after64(b,a)

#घोषणा समय_after_eq64(a,b)	\
	(typecheck(__u64, a) && \
	 typecheck(__u64, b) && \
	 ((__s64)((a) - (b)) >= 0))
#घोषणा समय_beक्रमe_eq64(a,b)	समय_after_eq64(b,a)

#घोषणा समय_in_range64(a, b, c) \
	(समय_after_eq64(a, b) && \
	 समय_beक्रमe_eq64(a, c))

/*
 * These four macros compare jअगरfies and 'a' क्रम convenience.
 */

/* समय_is_beक्रमe_jअगरfies(a) वापस true अगर a is beक्रमe jअगरfies */
#घोषणा समय_is_beक्रमe_jअगरfies(a) समय_after(jअगरfies, a)
#घोषणा समय_is_beक्रमe_jअगरfies64(a) समय_after64(get_jअगरfies_64(), a)

/* समय_is_after_jअगरfies(a) वापस true अगर a is after jअगरfies */
#घोषणा समय_is_after_jअगरfies(a) समय_beक्रमe(jअगरfies, a)
#घोषणा समय_is_after_jअगरfies64(a) समय_beक्रमe64(get_jअगरfies_64(), a)

/* समय_is_beक्रमe_eq_jअगरfies(a) वापस true अगर a is beक्रमe or equal to jअगरfies*/
#घोषणा समय_is_beक्रमe_eq_jअगरfies(a) समय_after_eq(jअगरfies, a)
#घोषणा समय_is_beक्रमe_eq_jअगरfies64(a) समय_after_eq64(get_jअगरfies_64(), a)

/* समय_is_after_eq_jअगरfies(a) वापस true अगर a is after or equal to jअगरfies*/
#घोषणा समय_is_after_eq_jअगरfies(a) समय_beक्रमe_eq(jअगरfies, a)
#घोषणा समय_is_after_eq_jअगरfies64(a) समय_beक्रमe_eq64(get_jअगरfies_64(), a)

/*
 * Have the 32 bit jअगरfies value wrap 5 minutes after boot
 * so jअगरfies wrap bugs show up earlier.
 */
#घोषणा INITIAL_JIFFIES ((अचिन्हित दीर्घ)(अचिन्हित पूर्णांक) (-300*HZ))

/*
 * Change समयval to jअगरfies, trying to aव्योम the
 * most obvious overflows..
 *
 * And some not so obvious.
 *
 * Note that we करोn't want to वापस दीर्घ_उच्च, because
 * क्रम various समयout reasons we often end up having
 * to रुको "jiffies+1" in order to guarantee that we रुको
 * at _least_ "jiffies" - so "jiffies+1" had better still
 * be positive.
 */
#घोषणा MAX_JIFFY_OFFSET ((दीर्घ_उच्च >> 1)-1)

बाह्य अचिन्हित दीर्घ preset_lpj;

/*
 * We want to करो realistic conversions of समय so we need to use the same
 * values the update wall घड़ी code uses as the jअगरfies size.  This value
 * is: TICK_NSEC (which is defined in समयx.h).  This
 * is a स्थिरant and is in nanoseconds.  We will use scaled math
 * with a set of scales defined here as SEC_JIFFIE_SC,  USEC_JIFFIE_SC and
 * NSEC_JIFFIE_SC.  Note that these defines contain nothing but
 * स्थिरants and so are computed at compile समय.  SHIFT_HZ (computed in
 * समयx.h) adjusts the scaling क्रम dअगरferent HZ values.

 * Scaled math???  What is that?
 *
 * Scaled math is a way to करो पूर्णांकeger math on values that would,
 * otherwise, either overflow, underflow, or cause undesired भाग
 * inकाष्ठाions to appear in the execution path.  In लघु, we "scale"
 * up the opeअक्रमs so they take more bits (more precision, less
 * underflow), करो the desired operation and then "scale" the result back
 * by the same amount.  If we करो the scaling by shअगरting we aव्योम the
 * costly mpy and the dastardly भाग inकाष्ठाions.

 * Suppose, क्रम example, we want to convert from seconds to jअगरfies
 * where jअगरfies is defined in nanoseconds as NSEC_PER_JIFFIE.  The
 * simple math is: jअगरf = (sec * NSEC_PER_SEC) / NSEC_PER_JIFFIE; We
 * observe that (NSEC_PER_SEC / NSEC_PER_JIFFIE) is a स्थिरant which we
 * might calculate at compile समय, however, the result will only have
 * about 3-4 bits of precision (less क्रम smaller values of HZ).
 *
 * So, we scale as follows:
 * jअगरf = (sec) * (NSEC_PER_SEC / NSEC_PER_JIFFIE);
 * jअगरf = ((sec) * ((NSEC_PER_SEC * SCALE)/ NSEC_PER_JIFFIE)) / SCALE;
 * Then we make SCALE a घातer of two so:
 * jअगरf = ((sec) * ((NSEC_PER_SEC << SCALE)/ NSEC_PER_JIFFIE)) >> SCALE;
 * Now we define:
 * #घोषणा SEC_CONV = ((NSEC_PER_SEC << SCALE)/ NSEC_PER_JIFFIE))
 * jअगरf = (sec * SEC_CONV) >> SCALE;
 *
 * Often the math we use will expand beyond 32-bits so we tell C how to
 * करो this and pass the 64-bit result of the mpy through the ">> SCALE"
 * which should take the result back to 32-bits.  We want this expansion
 * to capture as much precision as possible.  At the same समय we करोn't
 * want to overflow so we pick the SCALE to aव्योम this.  In this file,
 * that means using a dअगरferent scale क्रम each range of HZ values (as
 * defined in समयx.h).
 *
 * For those who want to know, gcc will give a 64-bit result from a "*"
 * चालक अगर the result is a दीर्घ दीर्घ AND at least one of the
 * opeअक्रमs is cast to दीर्घ दीर्घ (usually just prior to the "*" so as
 * not to confuse it पूर्णांकo thinking it really has a 64-bit opeअक्रम,
 * which, buy the way, it can करो, but it takes more code and at least 2
 * mpys).

 * We also need to be aware that one second in nanoseconds is only a
 * couple of bits away from overflowing a 32-bit word, so we MUST use
 * 64-bits to get the full range समय in nanoseconds.

 */

/*
 * Here are the scales we will use.  One क्रम seconds, nanoseconds and
 * microseconds.
 *
 * Within the limits of cpp we करो a rough cut at the SEC_JIFFIE_SC and
 * check अगर the sign bit is set.  If not, we bump the shअगरt count by 1.
 * (Gets an extra bit of precision where we can use it.)
 * We know it is set क्रम HZ = 1024 and HZ = 100 not क्रम 1000.
 * Haven't tested others.

 * Limits of cpp (क्रम #अगर expressions) only दीर्घ (no दीर्घ दीर्घ), but
 * then we only need the most signicant bit.
 */

#घोषणा SEC_JIFFIE_SC (31 - SHIFT_HZ)
#अगर !((((NSEC_PER_SEC << 2) / TICK_NSEC) << (SEC_JIFFIE_SC - 2)) & 0x80000000)
#अघोषित SEC_JIFFIE_SC
#घोषणा SEC_JIFFIE_SC (32 - SHIFT_HZ)
#पूर्ण_अगर
#घोषणा NSEC_JIFFIE_SC (SEC_JIFFIE_SC + 29)
#घोषणा SEC_CONVERSION ((अचिन्हित दीर्घ)((((u64)NSEC_PER_SEC << SEC_JIFFIE_SC) +\
                                TICK_NSEC -1) / (u64)TICK_NSEC))

#घोषणा NSEC_CONVERSION ((अचिन्हित दीर्घ)((((u64)1 << NSEC_JIFFIE_SC) +\
                                        TICK_NSEC -1) / (u64)TICK_NSEC))
/*
 * The maximum jअगरfie value is (MAX_INT >> 1).  Here we translate that
 * पूर्णांकo seconds.  The 64-bit हाल will overflow अगर we are not careful,
 * so use the messy SH_DIV macro to करो it.  Still all स्थिरants.
 */
#अगर BITS_PER_LONG < 64
# define MAX_SEC_IN_JIFFIES \
	(दीर्घ)((u64)((u64)MAX_JIFFY_OFFSET * TICK_NSEC) / NSEC_PER_SEC)
#अन्यथा	/* take care of overflow on 64 bits machines */
# define MAX_SEC_IN_JIFFIES \
	(SH_DIV((MAX_JIFFY_OFFSET >> SEC_JIFFIE_SC) * TICK_NSEC, NSEC_PER_SEC, 1) - 1)

#पूर्ण_अगर

/*
 * Convert various समय units to each other:
 */
बाह्य अचिन्हित पूर्णांक jअगरfies_to_msecs(स्थिर अचिन्हित दीर्घ j);
बाह्य अचिन्हित पूर्णांक jअगरfies_to_usecs(स्थिर अचिन्हित दीर्घ j);

अटल अंतरभूत u64 jअगरfies_to_nsecs(स्थिर अचिन्हित दीर्घ j)
अणु
	वापस (u64)jअगरfies_to_usecs(j) * NSEC_PER_USEC;
पूर्ण

बाह्य u64 jअगरfies64_to_nsecs(u64 j);
बाह्य u64 jअगरfies64_to_msecs(u64 j);

बाह्य अचिन्हित दीर्घ __msecs_to_jअगरfies(स्थिर अचिन्हित पूर्णांक m);
#अगर HZ <= MSEC_PER_SEC && !(MSEC_PER_SEC % HZ)
/*
 * HZ is equal to or smaller than 1000, and 1000 is a nice round
 * multiple of HZ, भागide with the factor between them, but round
 * upwards:
 */
अटल अंतरभूत अचिन्हित दीर्घ _msecs_to_jअगरfies(स्थिर अचिन्हित पूर्णांक m)
अणु
	वापस (m + (MSEC_PER_SEC / HZ) - 1) / (MSEC_PER_SEC / HZ);
पूर्ण
#या_अगर HZ > MSEC_PER_SEC && !(HZ % MSEC_PER_SEC)
/*
 * HZ is larger than 1000, and HZ is a nice round multiple of 1000 -
 * simply multiply with the factor between them.
 *
 * But first make sure the multiplication result cannot overflow:
 */
अटल अंतरभूत अचिन्हित दीर्घ _msecs_to_jअगरfies(स्थिर अचिन्हित पूर्णांक m)
अणु
	अगर (m > jअगरfies_to_msecs(MAX_JIFFY_OFFSET))
		वापस MAX_JIFFY_OFFSET;
	वापस m * (HZ / MSEC_PER_SEC);
पूर्ण
#अन्यथा
/*
 * Generic हाल - multiply, round and भागide. But first check that अगर
 * we are करोing a net multiplication, that we wouldn't overflow:
 */
अटल अंतरभूत अचिन्हित दीर्घ _msecs_to_jअगरfies(स्थिर अचिन्हित पूर्णांक m)
अणु
	अगर (HZ > MSEC_PER_SEC && m > jअगरfies_to_msecs(MAX_JIFFY_OFFSET))
		वापस MAX_JIFFY_OFFSET;

	वापस (MSEC_TO_HZ_MUL32 * m + MSEC_TO_HZ_ADJ32) >> MSEC_TO_HZ_SHR32;
पूर्ण
#पूर्ण_अगर
/**
 * msecs_to_jअगरfies: - convert milliseconds to jअगरfies
 * @m:	समय in milliseconds
 *
 * conversion is करोne as follows:
 *
 * - negative values mean 'infinite timeout' (MAX_JIFFY_OFFSET)
 *
 * - 'too large' values [that would result in larger than
 *   MAX_JIFFY_OFFSET values] mean 'infinite timeout' too.
 *
 * - all other values are converted to jअगरfies by either multiplying
 *   the input value by a factor or भागiding it with a factor and
 *   handling any 32-bit overflows.
 *   क्रम the details see __msecs_to_jअगरfies()
 *
 * msecs_to_jअगरfies() checks क्रम the passed in value being a स्थिरant
 * via __builtin_स्थिरant_p() allowing gcc to eliminate most of the
 * code, __msecs_to_jअगरfies() is called अगर the value passed करोes not
 * allow स्थिरant folding and the actual conversion must be करोne at
 * runसमय.
 * the HZ range specअगरic helpers _msecs_to_jअगरfies() are called both
 * directly here and from __msecs_to_jअगरfies() in the हाल where
 * स्थिरant folding is not possible.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ msecs_to_jअगरfies(स्थिर अचिन्हित पूर्णांक m)
अणु
	अगर (__builtin_स्थिरant_p(m)) अणु
		अगर ((पूर्णांक)m < 0)
			वापस MAX_JIFFY_OFFSET;
		वापस _msecs_to_jअगरfies(m);
	पूर्ण अन्यथा अणु
		वापस __msecs_to_jअगरfies(m);
	पूर्ण
पूर्ण

बाह्य अचिन्हित दीर्घ __usecs_to_jअगरfies(स्थिर अचिन्हित पूर्णांक u);
#अगर !(USEC_PER_SEC % HZ)
अटल अंतरभूत अचिन्हित दीर्घ _usecs_to_jअगरfies(स्थिर अचिन्हित पूर्णांक u)
अणु
	वापस (u + (USEC_PER_SEC / HZ) - 1) / (USEC_PER_SEC / HZ);
पूर्ण
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ _usecs_to_jअगरfies(स्थिर अचिन्हित पूर्णांक u)
अणु
	वापस (USEC_TO_HZ_MUL32 * u + USEC_TO_HZ_ADJ32)
		>> USEC_TO_HZ_SHR32;
पूर्ण
#पूर्ण_अगर

/**
 * usecs_to_jअगरfies: - convert microseconds to jअगरfies
 * @u:	समय in microseconds
 *
 * conversion is करोne as follows:
 *
 * - 'too large' values [that would result in larger than
 *   MAX_JIFFY_OFFSET values] mean 'infinite timeout' too.
 *
 * - all other values are converted to jअगरfies by either multiplying
 *   the input value by a factor or भागiding it with a factor and
 *   handling any 32-bit overflows as क्रम msecs_to_jअगरfies.
 *
 * usecs_to_jअगरfies() checks क्रम the passed in value being a स्थिरant
 * via __builtin_स्थिरant_p() allowing gcc to eliminate most of the
 * code, __usecs_to_jअगरfies() is called अगर the value passed करोes not
 * allow स्थिरant folding and the actual conversion must be करोne at
 * runसमय.
 * the HZ range specअगरic helpers _usecs_to_jअगरfies() are called both
 * directly here and from __msecs_to_jअगरfies() in the हाल where
 * स्थिरant folding is not possible.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ usecs_to_jअगरfies(स्थिर अचिन्हित पूर्णांक u)
अणु
	अगर (__builtin_स्थिरant_p(u)) अणु
		अगर (u > jअगरfies_to_usecs(MAX_JIFFY_OFFSET))
			वापस MAX_JIFFY_OFFSET;
		वापस _usecs_to_jअगरfies(u);
	पूर्ण अन्यथा अणु
		वापस __usecs_to_jअगरfies(u);
	पूर्ण
पूर्ण

बाह्य अचिन्हित दीर्घ बारpec64_to_jअगरfies(स्थिर काष्ठा बारpec64 *value);
बाह्य व्योम jअगरfies_to_बारpec64(स्थिर अचिन्हित दीर्घ jअगरfies,
				  काष्ठा बारpec64 *value);
बाह्य घड़ी_प्रकार jअगरfies_to_घड़ी_प्रकार(अचिन्हित दीर्घ x);
अटल अंतरभूत घड़ी_प्रकार jअगरfies_delta_to_घड़ी_प्रकार(दीर्घ delta)
अणु
	वापस jअगरfies_to_घड़ी_प्रकार(max(0L, delta));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक jअगरfies_delta_to_msecs(दीर्घ delta)
अणु
	वापस jअगरfies_to_msecs(max(0L, delta));
पूर्ण

बाह्य अचिन्हित दीर्घ घड़ी_प्रकार_to_jअगरfies(अचिन्हित दीर्घ x);
बाह्य u64 jअगरfies_64_to_घड़ी_प्रकार(u64 x);
बाह्य u64 nsec_to_घड़ी_प्रकार(u64 x);
बाह्य u64 nsecs_to_jअगरfies64(u64 n);
बाह्य अचिन्हित दीर्घ nsecs_to_jअगरfies(u64 n);

#घोषणा TIMESTAMP_SIZE	30

#पूर्ण_अगर
