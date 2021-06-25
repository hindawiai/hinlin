<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TIME64_H
#घोषणा _LINUX_TIME64_H

#समावेश <linux/math64.h>
#समावेश <vdso/समय64.h>

प्रकार __s64 समय64_t;
प्रकार __u64 समयu64_t;

#समावेश <uapi/linux/समय.स>

काष्ठा बारpec64 अणु
	समय64_t	tv_sec;			/* seconds */
	दीर्घ		tv_nsec;		/* nanoseconds */
पूर्ण;

काष्ठा iसमयrspec64 अणु
	काष्ठा बारpec64 it_पूर्णांकerval;
	काष्ठा बारpec64 it_value;
पूर्ण;

/* Located here क्रम बारpec[64]_valid_strict */
#घोषणा TIME64_MAX			((s64)~((u64)1 << 63))
#घोषणा TIME64_MIN			(-TIME64_MAX - 1)

#घोषणा KTIME_MAX			((s64)~((u64)1 << 63))
#घोषणा KTIME_SEC_MAX			(KTIME_MAX / NSEC_PER_SEC)

/*
 * Limits क्रम समय_रखोofday():
 *
 * To prevent setting the समय बंद to the wraparound poपूर्णांक समय setting
 * is limited so a reasonable upसमय can be accomodated. Upसमय of 30 years
 * should be really sufficient, which means the cutoff is 2232. At that
 * poपूर्णांक the cutoff is just a small part of the larger problem.
 */
#घोषणा TIME_UPTIME_SEC_MAX		(30LL * 365 * 24 *3600)
#घोषणा TIME_SETTOD_SEC_MAX		(KTIME_SEC_MAX - TIME_UPTIME_SEC_MAX)

अटल अंतरभूत पूर्णांक बारpec64_equal(स्थिर काष्ठा बारpec64 *a,
				   स्थिर काष्ठा बारpec64 *b)
अणु
	वापस (a->tv_sec == b->tv_sec) && (a->tv_nsec == b->tv_nsec);
पूर्ण

/*
 * lhs < rhs:  वापस <0
 * lhs == rhs: वापस 0
 * lhs > rhs:  वापस >0
 */
अटल अंतरभूत पूर्णांक बारpec64_compare(स्थिर काष्ठा बारpec64 *lhs, स्थिर काष्ठा बारpec64 *rhs)
अणु
	अगर (lhs->tv_sec < rhs->tv_sec)
		वापस -1;
	अगर (lhs->tv_sec > rhs->tv_sec)
		वापस 1;
	वापस lhs->tv_nsec - rhs->tv_nsec;
पूर्ण

बाह्य व्योम set_normalized_बारpec64(काष्ठा बारpec64 *ts, समय64_t sec, s64 nsec);

अटल अंतरभूत काष्ठा बारpec64 बारpec64_add(काष्ठा बारpec64 lhs,
						काष्ठा बारpec64 rhs)
अणु
	काष्ठा बारpec64 ts_delta;
	set_normalized_बारpec64(&ts_delta, lhs.tv_sec + rhs.tv_sec,
				lhs.tv_nsec + rhs.tv_nsec);
	वापस ts_delta;
पूर्ण

/*
 * sub = lhs - rhs, in normalized क्रमm
 */
अटल अंतरभूत काष्ठा बारpec64 बारpec64_sub(काष्ठा बारpec64 lhs,
						काष्ठा बारpec64 rhs)
अणु
	काष्ठा बारpec64 ts_delta;
	set_normalized_बारpec64(&ts_delta, lhs.tv_sec - rhs.tv_sec,
				lhs.tv_nsec - rhs.tv_nsec);
	वापस ts_delta;
पूर्ण

/*
 * Returns true अगर the बारpec64 is norm, false अगर denorm:
 */
अटल अंतरभूत bool बारpec64_valid(स्थिर काष्ठा बारpec64 *ts)
अणु
	/* Dates beक्रमe 1970 are bogus */
	अगर (ts->tv_sec < 0)
		वापस false;
	/* Can't have more nanoseconds then a second */
	अगर ((अचिन्हित दीर्घ)ts->tv_nsec >= NSEC_PER_SEC)
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool बारpec64_valid_strict(स्थिर काष्ठा बारpec64 *ts)
अणु
	अगर (!बारpec64_valid(ts))
		वापस false;
	/* Disallow values that could overflow kसमय_प्रकार */
	अगर ((अचिन्हित दीर्घ दीर्घ)ts->tv_sec >= KTIME_SEC_MAX)
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool बारpec64_valid_settod(स्थिर काष्ठा बारpec64 *ts)
अणु
	अगर (!बारpec64_valid(ts))
		वापस false;
	/* Disallow values which cause overflow issues vs. CLOCK_REALTIME */
	अगर ((अचिन्हित दीर्घ दीर्घ)ts->tv_sec >= TIME_SETTOD_SEC_MAX)
		वापस false;
	वापस true;
पूर्ण

/**
 * बारpec64_to_ns - Convert बारpec64 to nanoseconds
 * @ts:		poपूर्णांकer to the बारpec64 variable to be converted
 *
 * Returns the scalar nanosecond representation of the बारpec64
 * parameter.
 */
अटल अंतरभूत s64 बारpec64_to_ns(स्थिर काष्ठा बारpec64 *ts)
अणु
	/* Prevent multiplication overflow */
	अगर ((अचिन्हित दीर्घ दीर्घ)ts->tv_sec >= KTIME_SEC_MAX)
		वापस KTIME_MAX;

	वापस ((s64) ts->tv_sec * NSEC_PER_SEC) + ts->tv_nsec;
पूर्ण

/**
 * ns_to_बारpec64 - Convert nanoseconds to बारpec64
 * @nsec:	the nanoseconds value to be converted
 *
 * Returns the बारpec64 representation of the nsec parameter.
 */
बाह्य काष्ठा बारpec64 ns_to_बारpec64(स्थिर s64 nsec);

/**
 * बारpec64_add_ns - Adds nanoseconds to a बारpec64
 * @a:		poपूर्णांकer to बारpec64 to be incremented
 * @ns:		अचिन्हित nanoseconds value to be added
 *
 * This must always be अंतरभूतd because its used from the x86-64 vdso,
 * which cannot call other kernel functions.
 */
अटल __always_अंतरभूत व्योम बारpec64_add_ns(काष्ठा बारpec64 *a, u64 ns)
अणु
	a->tv_sec += __iter_भाग_u64_rem(a->tv_nsec + ns, NSEC_PER_SEC, &ns);
	a->tv_nsec = ns;
पूर्ण

/*
 * बारpec64_add_safe assumes both values are positive and checks क्रम
 * overflow. It will वापस TIME64_MAX in हाल of overflow.
 */
बाह्य काष्ठा बारpec64 बारpec64_add_safe(स्थिर काष्ठा बारpec64 lhs,
					 स्थिर काष्ठा बारpec64 rhs);

#पूर्ण_अगर /* _LINUX_TIME64_H */
