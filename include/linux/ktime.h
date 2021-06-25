<शैली गुरु>
/*
 *  include/linux/kसमय.स
 *
 *  kसमय_प्रकार - nanosecond-resolution समय क्रमmat.
 *
 *   Copyright(C) 2005, Thomas Gleixner <tglx@linutronix.de>
 *   Copyright(C) 2005, Red Hat, Inc., Ingo Molnar
 *
 *  data type definitions, declarations, prototypes and macros.
 *
 *  Started by: Thomas Gleixner and Ingo Molnar
 *
 *  Credits:
 *
 *  	Roman Zippel provided the ideas and primary code snippets of
 *  	the kसमय_प्रकार जोड़ and further simplअगरications of the original
 *  	code.
 *
 *  For licencing details see kernel-base/COPYING
 */
#अगर_अघोषित _LINUX_KTIME_H
#घोषणा _LINUX_KTIME_H

#समावेश <linux/समय.स>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/bug.h>

/* Nanosecond scalar representation क्रम kernel समय values */
प्रकार s64	kसमय_प्रकार;

/**
 * kसमय_set - Set a kसमय_प्रकार variable from a seconds/nanoseconds value
 * @secs:	seconds to set
 * @nsecs:	nanoseconds to set
 *
 * Return: The kसमय_प्रकार representation of the value.
 */
अटल अंतरभूत kसमय_प्रकार kसमय_set(स्थिर s64 secs, स्थिर अचिन्हित दीर्घ nsecs)
अणु
	अगर (unlikely(secs >= KTIME_SEC_MAX))
		वापस KTIME_MAX;

	वापस secs * NSEC_PER_SEC + (s64)nsecs;
पूर्ण

/* Subtract two kसमय_प्रकार variables. rem = lhs -rhs: */
#घोषणा kसमय_sub(lhs, rhs)	((lhs) - (rhs))

/* Add two kसमय_प्रकार variables. res = lhs + rhs: */
#घोषणा kसमय_add(lhs, rhs)	((lhs) + (rhs))

/*
 * Same as kसमय_add(), but aव्योमs undefined behaviour on overflow; however,
 * this means that you must check the result क्रम overflow yourself.
 */
#घोषणा kसमय_add_unsafe(lhs, rhs)	((u64) (lhs) + (rhs))

/*
 * Add a kसमय_प्रकार variable and a scalar nanosecond value.
 * res = kt + nsval:
 */
#घोषणा kसमय_add_ns(kt, nsval)		((kt) + (nsval))

/*
 * Subtract a scalar nanosecod from a kसमय_प्रकार variable
 * res = kt - nsval:
 */
#घोषणा kसमय_sub_ns(kt, nsval)		((kt) - (nsval))

/* convert a बारpec64 to kसमय_प्रकार क्रमmat: */
अटल अंतरभूत kसमय_प्रकार बारpec64_to_kसमय(काष्ठा बारpec64 ts)
अणु
	वापस kसमय_set(ts.tv_sec, ts.tv_nsec);
पूर्ण

/* Map the kसमय_प्रकार to बारpec conversion to ns_to_बारpec function */
#घोषणा kसमय_प्रकारo_बारpec64(kt)		ns_to_बारpec64((kt))

/* Convert kसमय_प्रकार to nanoseconds */
अटल अंतरभूत s64 kसमय_प्रकारo_ns(स्थिर kसमय_प्रकार kt)
अणु
	वापस kt;
पूर्ण

/**
 * kसमय_compare - Compares two kसमय_प्रकार variables क्रम less, greater or equal
 * @cmp1:	comparable1
 * @cmp2:	comparable2
 *
 * Return: ...
 *   cmp1  < cmp2: वापस <0
 *   cmp1 == cmp2: वापस 0
 *   cmp1  > cmp2: वापस >0
 */
अटल अंतरभूत पूर्णांक kसमय_compare(स्थिर kसमय_प्रकार cmp1, स्थिर kसमय_प्रकार cmp2)
अणु
	अगर (cmp1 < cmp2)
		वापस -1;
	अगर (cmp1 > cmp2)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * kसमय_after - Compare अगर a kसमय_प्रकार value is bigger than another one.
 * @cmp1:	comparable1
 * @cmp2:	comparable2
 *
 * Return: true अगर cmp1 happened after cmp2.
 */
अटल अंतरभूत bool kसमय_after(स्थिर kसमय_प्रकार cmp1, स्थिर kसमय_प्रकार cmp2)
अणु
	वापस kसमय_compare(cmp1, cmp2) > 0;
पूर्ण

/**
 * kसमय_beक्रमe - Compare अगर a kसमय_प्रकार value is smaller than another one.
 * @cmp1:	comparable1
 * @cmp2:	comparable2
 *
 * Return: true अगर cmp1 happened beक्रमe cmp2.
 */
अटल अंतरभूत bool kसमय_beक्रमe(स्थिर kसमय_प्रकार cmp1, स्थिर kसमय_प्रकार cmp2)
अणु
	वापस kसमय_compare(cmp1, cmp2) < 0;
पूर्ण

#अगर BITS_PER_LONG < 64
बाह्य s64 __kसमय_भागns(स्थिर kसमय_प्रकार kt, s64 भाग);
अटल अंतरभूत s64 kसमय_भागns(स्थिर kसमय_प्रकार kt, s64 भाग)
अणु
	/*
	 * Negative भागisors could cause an inf loop,
	 * so bug out here.
	 */
	BUG_ON(भाग < 0);
	अगर (__builtin_स्थिरant_p(भाग) && !(भाग >> 32)) अणु
		s64 ns = kt;
		u64 पंचांगp = ns < 0 ? -ns : ns;

		करो_भाग(पंचांगp, भाग);
		वापस ns < 0 ? -पंचांगp : पंचांगp;
	पूर्ण अन्यथा अणु
		वापस __kसमय_भागns(kt, भाग);
	पूर्ण
पूर्ण
#अन्यथा /* BITS_PER_LONG < 64 */
अटल अंतरभूत s64 kसमय_भागns(स्थिर kसमय_प्रकार kt, s64 भाग)
अणु
	/*
	 * 32-bit implementation cannot handle negative भागisors,
	 * so catch them on 64bit as well.
	 */
	WARN_ON(भाग < 0);
	वापस kt / भाग;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत s64 kसमय_प्रकारo_us(स्थिर kसमय_प्रकार kt)
अणु
	वापस kसमय_भागns(kt, NSEC_PER_USEC);
पूर्ण

अटल अंतरभूत s64 kसमय_प्रकारo_ms(स्थिर kसमय_प्रकार kt)
अणु
	वापस kसमय_भागns(kt, NSEC_PER_MSEC);
पूर्ण

अटल अंतरभूत s64 kसमय_us_delta(स्थिर kसमय_प्रकार later, स्थिर kसमय_प्रकार earlier)
अणु
       वापस kसमय_प्रकारo_us(kसमय_sub(later, earlier));
पूर्ण

अटल अंतरभूत s64 kसमय_ms_delta(स्थिर kसमय_प्रकार later, स्थिर kसमय_प्रकार earlier)
अणु
	वापस kसमय_प्रकारo_ms(kसमय_sub(later, earlier));
पूर्ण

अटल अंतरभूत kसमय_प्रकार kसमय_add_us(स्थिर kसमय_प्रकार kt, स्थिर u64 usec)
अणु
	वापस kसमय_add_ns(kt, usec * NSEC_PER_USEC);
पूर्ण

अटल अंतरभूत kसमय_प्रकार kसमय_add_ms(स्थिर kसमय_प्रकार kt, स्थिर u64 msec)
अणु
	वापस kसमय_add_ns(kt, msec * NSEC_PER_MSEC);
पूर्ण

अटल अंतरभूत kसमय_प्रकार kसमय_sub_us(स्थिर kसमय_प्रकार kt, स्थिर u64 usec)
अणु
	वापस kसमय_sub_ns(kt, usec * NSEC_PER_USEC);
पूर्ण

अटल अंतरभूत kसमय_प्रकार kसमय_sub_ms(स्थिर kसमय_प्रकार kt, स्थिर u64 msec)
अणु
	वापस kसमय_sub_ns(kt, msec * NSEC_PER_MSEC);
पूर्ण

बाह्य kसमय_प्रकार kसमय_add_safe(स्थिर kसमय_प्रकार lhs, स्थिर kसमय_प्रकार rhs);

/**
 * kसमय_प्रकारo_बारpec64_cond - convert a kसमय_प्रकार variable to बारpec64
 *			    क्रमmat only अगर the variable contains data
 * @kt:		the kसमय_प्रकार variable to convert
 * @ts:		the बारpec variable to store the result in
 *
 * Return: %true अगर there was a successful conversion, %false अगर kt was 0.
 */
अटल अंतरभूत __must_check bool kसमय_प्रकारo_बारpec64_cond(स्थिर kसमय_प्रकार kt,
						       काष्ठा बारpec64 *ts)
अणु
	अगर (kt) अणु
		*ts = kसमय_प्रकारo_बारpec64(kt);
		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

#समावेश <vdso/kसमय.स>

अटल अंतरभूत kसमय_प्रकार ns_to_kसमय(u64 ns)
अणु
	वापस ns;
पूर्ण

अटल अंतरभूत kसमय_प्रकार ms_to_kसमय(u64 ms)
अणु
	वापस ms * NSEC_PER_MSEC;
पूर्ण

# include <linux/समयkeeping.h>

#पूर्ण_अगर
