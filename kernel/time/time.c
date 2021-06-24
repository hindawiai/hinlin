<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  This file contains the पूर्णांकerface functions क्रम the various समय related
 *  प्रणाली calls: समय, sसमय, समय_लोofday, समय_रखोofday, adjसमय
 *
 * Modअगरication history:
 *
 * 1993-09-02    Philip Gladstone
 *      Created file with समय related functions from sched/core.c and adjसमयx()
 * 1993-10-08    Torsten Duwe
 *      adjसमय पूर्णांकerface update and CMOS घड़ी ग_लिखो code
 * 1995-08-13    Torsten Duwe
 *      kernel PLL updated to 1994-12-13 specs (rfc-1589)
 * 1999-01-16    Ulrich Windl
 *	Introduced error checking क्रम many हालs in adjसमयx().
 *	Updated NTP code according to technical memoअक्रमum Jan '96
 *	"A Kernel Model for Precision Timekeeping" by Dave Mills
 *	Allow समय_स्थिरant larger than MAXTC(6) क्रम NTP v4 (MAXTC == 10)
 *	(Even though the technical memoअक्रमum क्रमbids it)
 * 2004-07-14	 Christoph Lameter
 *	Added getnsसमयofday to allow the posix समयr functions to वापस
 *	with nanosecond accuracy
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयx.h>
#समावेश <linux/capability.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/security.h>
#समावेश <linux/fs.h>
#समावेश <linux/math64.h>
#समावेश <linux/ptrace.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/compat.h>
#समावेश <यंत्र/unistd.h>

#समावेश <generated/समयस्थिर.h>
#समावेश "timekeeping.h"

/*
 * The समयzone where the local प्रणाली is located.  Used as a शेष by some
 * programs who obtain this value by using समय_लोofday.
 */
काष्ठा समयzone sys_tz;

EXPORT_SYMBOL(sys_tz);

#अगर_घोषित __ARCH_WANT_SYS_TIME

/*
 * sys_समय() can be implemented in user-level using
 * sys_समय_लोofday().  Is this क्रम backwards compatibility?  If so,
 * why not move it पूर्णांकo the appropriate arch directory (क्रम those
 * architectures that need it).
 */
SYSCALL_DEFINE1(समय, __kernel_old_समय_प्रकार __user *, tloc)
अणु
	__kernel_old_समय_प्रकार i = (__kernel_old_समय_प्रकार)kसमय_get_real_seconds();

	अगर (tloc) अणु
		अगर (put_user(i,tloc))
			वापस -EFAULT;
	पूर्ण
	क्रमce_successful_syscall_वापस();
	वापस i;
पूर्ण

/*
 * sys_sसमय() can be implemented in user-level using
 * sys_समय_रखोofday().  Is this क्रम backwards compatibility?  If so,
 * why not move it पूर्णांकo the appropriate arch directory (क्रम those
 * architectures that need it).
 */

SYSCALL_DEFINE1(sसमय, __kernel_old_समय_प्रकार __user *, tptr)
अणु
	काष्ठा बारpec64 tv;
	पूर्णांक err;

	अगर (get_user(tv.tv_sec, tptr))
		वापस -EFAULT;

	tv.tv_nsec = 0;

	err = security_समय_रखो64(&tv, शून्य);
	अगर (err)
		वापस err;

	करो_समय_रखोofday64(&tv);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* __ARCH_WANT_SYS_TIME */

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
#अगर_घोषित __ARCH_WANT_SYS_TIME32

/* old_समय32_t is a 32 bit "long" and needs to get converted. */
SYSCALL_DEFINE1(समय32, old_समय32_t __user *, tloc)
अणु
	old_समय32_t i;

	i = (old_समय32_t)kसमय_get_real_seconds();

	अगर (tloc) अणु
		अगर (put_user(i,tloc))
			वापस -EFAULT;
	पूर्ण
	क्रमce_successful_syscall_वापस();
	वापस i;
पूर्ण

SYSCALL_DEFINE1(sसमय32, old_समय32_t __user *, tptr)
अणु
	काष्ठा बारpec64 tv;
	पूर्णांक err;

	अगर (get_user(tv.tv_sec, tptr))
		वापस -EFAULT;

	tv.tv_nsec = 0;

	err = security_समय_रखो64(&tv, शून्य);
	अगर (err)
		वापस err;

	करो_समय_रखोofday64(&tv);
	वापस 0;
पूर्ण

#पूर्ण_अगर /* __ARCH_WANT_SYS_TIME32 */
#पूर्ण_अगर

SYSCALL_DEFINE2(समय_लोofday, काष्ठा __kernel_old_समयval __user *, tv,
		काष्ठा समयzone __user *, tz)
अणु
	अगर (likely(tv != शून्य)) अणु
		काष्ठा बारpec64 ts;

		kसमय_get_real_ts64(&ts);
		अगर (put_user(ts.tv_sec, &tv->tv_sec) ||
		    put_user(ts.tv_nsec / 1000, &tv->tv_usec))
			वापस -EFAULT;
	पूर्ण
	अगर (unlikely(tz != शून्य)) अणु
		अगर (copy_to_user(tz, &sys_tz, माप(sys_tz)))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * In हाल क्रम some reason the CMOS घड़ी has not alपढ़ोy been running
 * in UTC, but in some local समय: The first समय we set the समयzone,
 * we will warp the घड़ी so that it is ticking UTC समय instead of
 * local समय. Presumably, अगर someone is setting the समयzone then we
 * are running in an environment where the programs understand about
 * समयzones. This should be करोne at boot समय in the /etc/rc script,
 * as soon as possible, so that the घड़ी can be set right. Otherwise,
 * various programs will get confused when the घड़ी माला_लो warped.
 */

पूर्णांक करो_sys_समय_रखोofday64(स्थिर काष्ठा बारpec64 *tv, स्थिर काष्ठा समयzone *tz)
अणु
	अटल पूर्णांक firstसमय = 1;
	पूर्णांक error = 0;

	अगर (tv && !बारpec64_valid_settod(tv))
		वापस -EINVAL;

	error = security_समय_रखो64(tv, tz);
	अगर (error)
		वापस error;

	अगर (tz) अणु
		/* Verअगरy we're within the +-15 hrs range */
		अगर (tz->tz_minuteswest > 15*60 || tz->tz_minuteswest < -15*60)
			वापस -EINVAL;

		sys_tz = *tz;
		update_vsyscall_tz();
		अगर (firstसमय) अणु
			firstसमय = 0;
			अगर (!tv)
				समयkeeping_warp_घड़ी();
		पूर्ण
	पूर्ण
	अगर (tv)
		वापस करो_समय_रखोofday64(tv);
	वापस 0;
पूर्ण

SYSCALL_DEFINE2(समय_रखोofday, काष्ठा __kernel_old_समयval __user *, tv,
		काष्ठा समयzone __user *, tz)
अणु
	काष्ठा बारpec64 new_ts;
	काष्ठा समयzone new_tz;

	अगर (tv) अणु
		अगर (get_user(new_ts.tv_sec, &tv->tv_sec) ||
		    get_user(new_ts.tv_nsec, &tv->tv_usec))
			वापस -EFAULT;

		अगर (new_ts.tv_nsec > USEC_PER_SEC || new_ts.tv_nsec < 0)
			वापस -EINVAL;

		new_ts.tv_nsec *= NSEC_PER_USEC;
	पूर्ण
	अगर (tz) अणु
		अगर (copy_from_user(&new_tz, tz, माप(*tz)))
			वापस -EFAULT;
	पूर्ण

	वापस करो_sys_समय_रखोofday64(tv ? &new_ts : शून्य, tz ? &new_tz : शून्य);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE2(समय_लोofday, काष्ठा old_समयval32 __user *, tv,
		       काष्ठा समयzone __user *, tz)
अणु
	अगर (tv) अणु
		काष्ठा बारpec64 ts;

		kसमय_get_real_ts64(&ts);
		अगर (put_user(ts.tv_sec, &tv->tv_sec) ||
		    put_user(ts.tv_nsec / 1000, &tv->tv_usec))
			वापस -EFAULT;
	पूर्ण
	अगर (tz) अणु
		अगर (copy_to_user(tz, &sys_tz, माप(sys_tz)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

COMPAT_SYSCALL_DEFINE2(समय_रखोofday, काष्ठा old_समयval32 __user *, tv,
		       काष्ठा समयzone __user *, tz)
अणु
	काष्ठा बारpec64 new_ts;
	काष्ठा समयzone new_tz;

	अगर (tv) अणु
		अगर (get_user(new_ts.tv_sec, &tv->tv_sec) ||
		    get_user(new_ts.tv_nsec, &tv->tv_usec))
			वापस -EFAULT;

		अगर (new_ts.tv_nsec > USEC_PER_SEC || new_ts.tv_nsec < 0)
			वापस -EINVAL;

		new_ts.tv_nsec *= NSEC_PER_USEC;
	पूर्ण
	अगर (tz) अणु
		अगर (copy_from_user(&new_tz, tz, माप(*tz)))
			वापस -EFAULT;
	पूर्ण

	वापस करो_sys_समय_रखोofday64(tv ? &new_ts : शून्य, tz ? &new_tz : शून्य);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
SYSCALL_DEFINE1(adjसमयx, काष्ठा __kernel_समयx __user *, txc_p)
अणु
	काष्ठा __kernel_समयx txc;		/* Local copy of parameter */
	पूर्णांक ret;

	/* Copy the user data space पूर्णांकo the kernel copy
	 * काष्ठाure. But bear in mind that the काष्ठाures
	 * may change
	 */
	अगर (copy_from_user(&txc, txc_p, माप(काष्ठा __kernel_समयx)))
		वापस -EFAULT;
	ret = करो_adjसमयx(&txc);
	वापस copy_to_user(txc_p, &txc, माप(काष्ठा __kernel_समयx)) ? -EFAULT : ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
पूर्णांक get_old_समयx32(काष्ठा __kernel_समयx *txc, स्थिर काष्ठा old_समयx32 __user *utp)
अणु
	काष्ठा old_समयx32 tx32;

	स_रखो(txc, 0, माप(काष्ठा __kernel_समयx));
	अगर (copy_from_user(&tx32, utp, माप(काष्ठा old_समयx32)))
		वापस -EFAULT;

	txc->modes = tx32.modes;
	txc->offset = tx32.offset;
	txc->freq = tx32.freq;
	txc->maxerror = tx32.maxerror;
	txc->esterror = tx32.esterror;
	txc->status = tx32.status;
	txc->स्थिरant = tx32.स्थिरant;
	txc->precision = tx32.precision;
	txc->tolerance = tx32.tolerance;
	txc->समय.tv_sec = tx32.समय.tv_sec;
	txc->समय.tv_usec = tx32.समय.tv_usec;
	txc->tick = tx32.tick;
	txc->ppsfreq = tx32.ppsfreq;
	txc->jitter = tx32.jitter;
	txc->shअगरt = tx32.shअगरt;
	txc->stabil = tx32.stabil;
	txc->jitcnt = tx32.jitcnt;
	txc->calcnt = tx32.calcnt;
	txc->errcnt = tx32.errcnt;
	txc->stbcnt = tx32.stbcnt;

	वापस 0;
पूर्ण

पूर्णांक put_old_समयx32(काष्ठा old_समयx32 __user *utp, स्थिर काष्ठा __kernel_समयx *txc)
अणु
	काष्ठा old_समयx32 tx32;

	स_रखो(&tx32, 0, माप(काष्ठा old_समयx32));
	tx32.modes = txc->modes;
	tx32.offset = txc->offset;
	tx32.freq = txc->freq;
	tx32.maxerror = txc->maxerror;
	tx32.esterror = txc->esterror;
	tx32.status = txc->status;
	tx32.स्थिरant = txc->स्थिरant;
	tx32.precision = txc->precision;
	tx32.tolerance = txc->tolerance;
	tx32.समय.tv_sec = txc->समय.tv_sec;
	tx32.समय.tv_usec = txc->समय.tv_usec;
	tx32.tick = txc->tick;
	tx32.ppsfreq = txc->ppsfreq;
	tx32.jitter = txc->jitter;
	tx32.shअगरt = txc->shअगरt;
	tx32.stabil = txc->stabil;
	tx32.jitcnt = txc->jitcnt;
	tx32.calcnt = txc->calcnt;
	tx32.errcnt = txc->errcnt;
	tx32.stbcnt = txc->stbcnt;
	tx32.tai = txc->tai;
	अगर (copy_to_user(utp, &tx32, माप(काष्ठा old_समयx32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

SYSCALL_DEFINE1(adjसमयx_समय32, काष्ठा old_समयx32 __user *, utp)
अणु
	काष्ठा __kernel_समयx txc;
	पूर्णांक err, ret;

	err = get_old_समयx32(&txc, utp);
	अगर (err)
		वापस err;

	ret = करो_adjसमयx(&txc);

	err = put_old_समयx32(utp, &txc);
	अगर (err)
		वापस err;

	वापस ret;
पूर्ण
#पूर्ण_अगर

/*
 * Convert jअगरfies to milliseconds and back.
 *
 * Aव्योम unnecessary multiplications/भागisions in the
 * two most common HZ हालs:
 */
अचिन्हित पूर्णांक jअगरfies_to_msecs(स्थिर अचिन्हित दीर्घ j)
अणु
#अगर HZ <= MSEC_PER_SEC && !(MSEC_PER_SEC % HZ)
	वापस (MSEC_PER_SEC / HZ) * j;
#या_अगर HZ > MSEC_PER_SEC && !(HZ % MSEC_PER_SEC)
	वापस (j + (HZ / MSEC_PER_SEC) - 1)/(HZ / MSEC_PER_SEC);
#अन्यथा
# अगर BITS_PER_LONG == 32
	वापस (HZ_TO_MSEC_MUL32 * j + (1ULL << HZ_TO_MSEC_SHR32) - 1) >>
	       HZ_TO_MSEC_SHR32;
# अन्यथा
	वापस DIV_ROUND_UP(j * HZ_TO_MSEC_NUM, HZ_TO_MSEC_DEN);
# endअगर
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(jअगरfies_to_msecs);

अचिन्हित पूर्णांक jअगरfies_to_usecs(स्थिर अचिन्हित दीर्घ j)
अणु
	/*
	 * Hz usually करोesn't go much further MSEC_PER_SEC.
	 * jअगरfies_to_usecs() and usecs_to_jअगरfies() depend on that.
	 */
	BUILD_BUG_ON(HZ > USEC_PER_SEC);

#अगर !(USEC_PER_SEC % HZ)
	वापस (USEC_PER_SEC / HZ) * j;
#अन्यथा
# अगर BITS_PER_LONG == 32
	वापस (HZ_TO_USEC_MUL32 * j) >> HZ_TO_USEC_SHR32;
# अन्यथा
	वापस (j * HZ_TO_USEC_NUM) / HZ_TO_USEC_DEN;
# endअगर
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(jअगरfies_to_usecs);

/*
 * स_गढ़ो64 - Converts date to seconds.
 * Converts Gregorian date to seconds since 1970-01-01 00:00:00.
 * Assumes input in normal date क्रमmat, i.e. 1980-12-31 23:59:59
 * => year=1980, mon=12, day=31, hour=23, min=59, sec=59.
 *
 * [For the Julian calendar (which was used in Russia beक्रमe 1917,
 * Britain & colonies beक्रमe 1752, anywhere अन्यथा beक्रमe 1582,
 * and is still in use by some communities) leave out the
 * -year/100+year/400 terms, and add 10.]
 *
 * This algorithm was first published by Gauss (I think).
 *
 * A leap second can be indicated by calling this function with sec as
 * 60 (allowable under ISO 8601).  The leap second is treated the same
 * as the following second since they करोn't exist in UNIX समय.
 *
 * An encoding of midnight at the end of the day as 24:00:00 - ie. midnight
 * tomorrow - (allowable under ISO 8601) is supported.
 */
समय64_t स_गढ़ो64(स्थिर अचिन्हित पूर्णांक year0, स्थिर अचिन्हित पूर्णांक mon0,
		स्थिर अचिन्हित पूर्णांक day, स्थिर अचिन्हित पूर्णांक hour,
		स्थिर अचिन्हित पूर्णांक min, स्थिर अचिन्हित पूर्णांक sec)
अणु
	अचिन्हित पूर्णांक mon = mon0, year = year0;

	/* 1..12 -> 11,12,1..10 */
	अगर (0 >= (पूर्णांक) (mon -= 2)) अणु
		mon += 12;	/* Puts Feb last since it has leap day */
		year -= 1;
	पूर्ण

	वापस ((((समय64_t)
		  (year/4 - year/100 + year/400 + 367*mon/12 + day) +
		  year*365 - 719499
	    )*24 + hour /* now have hours - midnight tomorrow handled here */
	  )*60 + min /* now have minutes */
	)*60 + sec; /* finally seconds */
पूर्ण
EXPORT_SYMBOL(स_गढ़ो64);

काष्ठा __kernel_old_समयval ns_to_kernel_old_समयval(स्थिर s64 nsec)
अणु
	काष्ठा बारpec64 ts = ns_to_बारpec64(nsec);
	काष्ठा __kernel_old_समयval tv;

	tv.tv_sec = ts.tv_sec;
	tv.tv_usec = (suseconds_t)ts.tv_nsec / 1000;

	वापस tv;
पूर्ण
EXPORT_SYMBOL(ns_to_kernel_old_समयval);

/**
 * set_normalized_बारpec - set बारpec sec and nsec parts and normalize
 *
 * @ts:		poपूर्णांकer to बारpec variable to be set
 * @sec:	seconds to set
 * @nsec:	nanoseconds to set
 *
 * Set seconds and nanoseconds field of a बारpec variable and
 * normalize to the बारpec storage क्रमmat
 *
 * Note: The tv_nsec part is always in the range of
 *	0 <= tv_nsec < NSEC_PER_SEC
 * For negative values only the tv_sec field is negative !
 */
व्योम set_normalized_बारpec64(काष्ठा बारpec64 *ts, समय64_t sec, s64 nsec)
अणु
	जबतक (nsec >= NSEC_PER_SEC) अणु
		/*
		 * The following यंत्र() prevents the compiler from
		 * optimising this loop पूर्णांकo a modulo operation. See
		 * also __iter_भाग_u64_rem() in include/linux/समय.स
		 */
		यंत्र("" : "+rm"(nsec));
		nsec -= NSEC_PER_SEC;
		++sec;
	पूर्ण
	जबतक (nsec < 0) अणु
		यंत्र("" : "+rm"(nsec));
		nsec += NSEC_PER_SEC;
		--sec;
	पूर्ण
	ts->tv_sec = sec;
	ts->tv_nsec = nsec;
पूर्ण
EXPORT_SYMBOL(set_normalized_बारpec64);

/**
 * ns_to_बारpec64 - Convert nanoseconds to बारpec64
 * @nsec:       the nanoseconds value to be converted
 *
 * Returns the बारpec64 representation of the nsec parameter.
 */
काष्ठा बारpec64 ns_to_बारpec64(स्थिर s64 nsec)
अणु
	काष्ठा बारpec64 ts = अणु 0, 0 पूर्ण;
	s32 rem;

	अगर (likely(nsec > 0)) अणु
		ts.tv_sec = भाग_u64_rem(nsec, NSEC_PER_SEC, &rem);
		ts.tv_nsec = rem;
	पूर्ण अन्यथा अगर (nsec < 0) अणु
		/*
		 * With negative बार, tv_sec poपूर्णांकs to the earlier
		 * second, and tv_nsec counts the nanoseconds since
		 * then, so tv_nsec is always a positive number.
		 */
		ts.tv_sec = -भाग_u64_rem(-nsec - 1, NSEC_PER_SEC, &rem) - 1;
		ts.tv_nsec = NSEC_PER_SEC - rem - 1;
	पूर्ण

	वापस ts;
पूर्ण
EXPORT_SYMBOL(ns_to_बारpec64);

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
 * the _msecs_to_jअगरfies helpers are the HZ dependent conversion
 * routines found in include/linux/jअगरfies.h
 */
अचिन्हित दीर्घ __msecs_to_jअगरfies(स्थिर अचिन्हित पूर्णांक m)
अणु
	/*
	 * Negative value, means infinite समयout:
	 */
	अगर ((पूर्णांक)m < 0)
		वापस MAX_JIFFY_OFFSET;
	वापस _msecs_to_jअगरfies(m);
पूर्ण
EXPORT_SYMBOL(__msecs_to_jअगरfies);

अचिन्हित दीर्घ __usecs_to_jअगरfies(स्थिर अचिन्हित पूर्णांक u)
अणु
	अगर (u > jअगरfies_to_usecs(MAX_JIFFY_OFFSET))
		वापस MAX_JIFFY_OFFSET;
	वापस _usecs_to_jअगरfies(u);
पूर्ण
EXPORT_SYMBOL(__usecs_to_jअगरfies);

/*
 * The TICK_NSEC - 1 rounds up the value to the next resolution.  Note
 * that a reमुख्यder subtract here would not करो the right thing as the
 * resolution values करोn't fall on second boundaries.  I.e. the line:
 * nsec -= nsec % TICK_NSEC; is NOT a correct resolution rounding.
 * Note that due to the small error in the multiplier here, this
 * rounding is incorrect क्रम sufficiently large values of tv_nsec, but
 * well क्रमmed बारpecs should have tv_nsec < NSEC_PER_SEC, so we're
 * OK.
 *
 * Rather, we just shअगरt the bits off the right.
 *
 * The >> (NSEC_JIFFIE_SC - SEC_JIFFIE_SC) converts the scaled nsec
 * value to a scaled second value.
 */

अचिन्हित दीर्घ
बारpec64_to_jअगरfies(स्थिर काष्ठा बारpec64 *value)
अणु
	u64 sec = value->tv_sec;
	दीर्घ nsec = value->tv_nsec + TICK_NSEC - 1;

	अगर (sec >= MAX_SEC_IN_JIFFIES)अणु
		sec = MAX_SEC_IN_JIFFIES;
		nsec = 0;
	पूर्ण
	वापस ((sec * SEC_CONVERSION) +
		(((u64)nsec * NSEC_CONVERSION) >>
		 (NSEC_JIFFIE_SC - SEC_JIFFIE_SC))) >> SEC_JIFFIE_SC;

पूर्ण
EXPORT_SYMBOL(बारpec64_to_jअगरfies);

व्योम
jअगरfies_to_बारpec64(स्थिर अचिन्हित दीर्घ jअगरfies, काष्ठा बारpec64 *value)
अणु
	/*
	 * Convert jअगरfies to nanoseconds and separate with
	 * one भागide.
	 */
	u32 rem;
	value->tv_sec = भाग_u64_rem((u64)jअगरfies * TICK_NSEC,
				    NSEC_PER_SEC, &rem);
	value->tv_nsec = rem;
पूर्ण
EXPORT_SYMBOL(jअगरfies_to_बारpec64);

/*
 * Convert jअगरfies/jअगरfies_64 to घड़ी_प्रकार and back.
 */
घड़ी_प्रकार jअगरfies_to_घड़ी_प्रकार(अचिन्हित दीर्घ x)
अणु
#अगर (TICK_NSEC % (NSEC_PER_SEC / USER_HZ)) == 0
# अगर HZ < USER_HZ
	वापस x * (USER_HZ / HZ);
# अन्यथा
	वापस x / (HZ / USER_HZ);
# endअगर
#अन्यथा
	वापस भाग_u64((u64)x * TICK_NSEC, NSEC_PER_SEC / USER_HZ);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(jअगरfies_to_घड़ी_प्रकार);

अचिन्हित दीर्घ घड़ी_प्रकार_to_jअगरfies(अचिन्हित दीर्घ x)
अणु
#अगर (HZ % USER_HZ)==0
	अगर (x >= ~0UL / (HZ / USER_HZ))
		वापस ~0UL;
	वापस x * (HZ / USER_HZ);
#अन्यथा
	/* Don't worry about loss of precision here .. */
	अगर (x >= ~0UL / HZ * USER_HZ)
		वापस ~0UL;

	/* .. but करो try to contain it here */
	वापस भाग_u64((u64)x * HZ, USER_HZ);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(घड़ी_प्रकार_to_jअगरfies);

u64 jअगरfies_64_to_घड़ी_प्रकार(u64 x)
अणु
#अगर (TICK_NSEC % (NSEC_PER_SEC / USER_HZ)) == 0
# अगर HZ < USER_HZ
	x = भाग_u64(x * USER_HZ, HZ);
# elअगर HZ > USER_HZ
	x = भाग_u64(x, HZ / USER_HZ);
# अन्यथा
	/* Nothing to करो */
# endअगर
#अन्यथा
	/*
	 * There are better ways that करोn't overflow early,
	 * but even this करोesn't overflow in hundreds of years
	 * in 64 bits, so..
	 */
	x = भाग_u64(x * TICK_NSEC, (NSEC_PER_SEC / USER_HZ));
#पूर्ण_अगर
	वापस x;
पूर्ण
EXPORT_SYMBOL(jअगरfies_64_to_घड़ी_प्रकार);

u64 nsec_to_घड़ी_प्रकार(u64 x)
अणु
#अगर (NSEC_PER_SEC % USER_HZ) == 0
	वापस भाग_u64(x, NSEC_PER_SEC / USER_HZ);
#या_अगर (USER_HZ % 512) == 0
	वापस भाग_u64(x * USER_HZ / 512, NSEC_PER_SEC / 512);
#अन्यथा
	/*
         * max relative error 5.7e-8 (1.8s per year) क्रम USER_HZ <= 1024,
         * overflow after 64.99 years.
         * exact क्रम HZ=60, 72, 90, 120, 144, 180, 300, 600, 900, ...
         */
	वापस भाग_u64(x * 9, (9ull * NSEC_PER_SEC + (USER_HZ / 2)) / USER_HZ);
#पूर्ण_अगर
पूर्ण

u64 jअगरfies64_to_nsecs(u64 j)
अणु
#अगर !(NSEC_PER_SEC % HZ)
	वापस (NSEC_PER_SEC / HZ) * j;
# अन्यथा
	वापस भाग_u64(j * HZ_TO_NSEC_NUM, HZ_TO_NSEC_DEN);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(jअगरfies64_to_nsecs);

u64 jअगरfies64_to_msecs(स्थिर u64 j)
अणु
#अगर HZ <= MSEC_PER_SEC && !(MSEC_PER_SEC % HZ)
	वापस (MSEC_PER_SEC / HZ) * j;
#अन्यथा
	वापस भाग_u64(j * HZ_TO_MSEC_NUM, HZ_TO_MSEC_DEN);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(jअगरfies64_to_msecs);

/**
 * nsecs_to_jअगरfies64 - Convert nsecs in u64 to jअगरfies64
 *
 * @n:	nsecs in u64
 *
 * Unlike अणुm,uपूर्णsecs_to_jअगरfies, type of input is not अचिन्हित पूर्णांक but u64.
 * And this करोesn't वापस MAX_JIFFY_OFFSET since this function is deचिन्हित
 * क्रम scheduler, not क्रम use in device drivers to calculate समयout value.
 *
 * note:
 *   NSEC_PER_SEC = 10^9 = (5^9 * 2^9) = (1953125 * 512)
 *   ULदीर्घ_उच्च ns = 18446744073.709551615 secs = about 584 years
 */
u64 nsecs_to_jअगरfies64(u64 n)
अणु
#अगर (NSEC_PER_SEC % HZ) == 0
	/* Common हाल, HZ = 100, 128, 200, 250, 256, 500, 512, 1000 etc. */
	वापस भाग_u64(n, NSEC_PER_SEC / HZ);
#या_अगर (HZ % 512) == 0
	/* overflow after 292 years अगर HZ = 1024 */
	वापस भाग_u64(n * HZ / 512, NSEC_PER_SEC / 512);
#अन्यथा
	/*
	 * Generic हाल - optimized क्रम हालs where HZ is a multiple of 3.
	 * overflow after 64.99 years, exact क्रम HZ = 60, 72, 90, 120 etc.
	 */
	वापस भाग_u64(n * 9, (9ull * NSEC_PER_SEC + HZ / 2) / HZ);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(nsecs_to_jअगरfies64);

/**
 * nsecs_to_jअगरfies - Convert nsecs in u64 to jअगरfies
 *
 * @n:	nsecs in u64
 *
 * Unlike अणुm,uपूर्णsecs_to_jअगरfies, type of input is not अचिन्हित पूर्णांक but u64.
 * And this करोesn't वापस MAX_JIFFY_OFFSET since this function is deचिन्हित
 * क्रम scheduler, not क्रम use in device drivers to calculate समयout value.
 *
 * note:
 *   NSEC_PER_SEC = 10^9 = (5^9 * 2^9) = (1953125 * 512)
 *   ULदीर्घ_उच्च ns = 18446744073.709551615 secs = about 584 years
 */
अचिन्हित दीर्घ nsecs_to_jअगरfies(u64 n)
अणु
	वापस (अचिन्हित दीर्घ)nsecs_to_jअगरfies64(n);
पूर्ण
EXPORT_SYMBOL_GPL(nsecs_to_jअगरfies);

/*
 * Add two बारpec64 values and करो a safety check क्रम overflow.
 * It's assumed that both values are valid (>= 0).
 * And, each बारpec64 is in normalized क्रमm.
 */
काष्ठा बारpec64 बारpec64_add_safe(स्थिर काष्ठा बारpec64 lhs,
				स्थिर काष्ठा बारpec64 rhs)
अणु
	काष्ठा बारpec64 res;

	set_normalized_बारpec64(&res, (समयu64_t) lhs.tv_sec + rhs.tv_sec,
			lhs.tv_nsec + rhs.tv_nsec);

	अगर (unlikely(res.tv_sec < lhs.tv_sec || res.tv_sec < rhs.tv_sec)) अणु
		res.tv_sec = TIME64_MAX;
		res.tv_nsec = 0;
	पूर्ण

	वापस res;
पूर्ण

पूर्णांक get_बारpec64(काष्ठा बारpec64 *ts,
		   स्थिर काष्ठा __kernel_बारpec __user *uts)
अणु
	काष्ठा __kernel_बारpec kts;
	पूर्णांक ret;

	ret = copy_from_user(&kts, uts, माप(kts));
	अगर (ret)
		वापस -EFAULT;

	ts->tv_sec = kts.tv_sec;

	/* Zero out the padding in compat mode */
	अगर (in_compat_syscall())
		kts.tv_nsec &= 0xFFFFFFFFUL;

	/* In 32-bit mode, this drops the padding */
	ts->tv_nsec = kts.tv_nsec;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(get_बारpec64);

पूर्णांक put_बारpec64(स्थिर काष्ठा बारpec64 *ts,
		   काष्ठा __kernel_बारpec __user *uts)
अणु
	काष्ठा __kernel_बारpec kts = अणु
		.tv_sec = ts->tv_sec,
		.tv_nsec = ts->tv_nsec
	पूर्ण;

	वापस copy_to_user(uts, &kts, माप(kts)) ? -EFAULT : 0;
पूर्ण
EXPORT_SYMBOL_GPL(put_बारpec64);

अटल पूर्णांक __get_old_बारpec32(काष्ठा बारpec64 *ts64,
				   स्थिर काष्ठा old_बारpec32 __user *cts)
अणु
	काष्ठा old_बारpec32 ts;
	पूर्णांक ret;

	ret = copy_from_user(&ts, cts, माप(ts));
	अगर (ret)
		वापस -EFAULT;

	ts64->tv_sec = ts.tv_sec;
	ts64->tv_nsec = ts.tv_nsec;

	वापस 0;
पूर्ण

अटल पूर्णांक __put_old_बारpec32(स्थिर काष्ठा बारpec64 *ts64,
				   काष्ठा old_बारpec32 __user *cts)
अणु
	काष्ठा old_बारpec32 ts = अणु
		.tv_sec = ts64->tv_sec,
		.tv_nsec = ts64->tv_nsec
	पूर्ण;
	वापस copy_to_user(cts, &ts, माप(ts)) ? -EFAULT : 0;
पूर्ण

पूर्णांक get_old_बारpec32(काष्ठा बारpec64 *ts, स्थिर व्योम __user *uts)
अणु
	अगर (COMPAT_USE_64BIT_TIME)
		वापस copy_from_user(ts, uts, माप(*ts)) ? -EFAULT : 0;
	अन्यथा
		वापस __get_old_बारpec32(ts, uts);
पूर्ण
EXPORT_SYMBOL_GPL(get_old_बारpec32);

पूर्णांक put_old_बारpec32(स्थिर काष्ठा बारpec64 *ts, व्योम __user *uts)
अणु
	अगर (COMPAT_USE_64BIT_TIME)
		वापस copy_to_user(uts, ts, माप(*ts)) ? -EFAULT : 0;
	अन्यथा
		वापस __put_old_बारpec32(ts, uts);
पूर्ण
EXPORT_SYMBOL_GPL(put_old_बारpec32);

पूर्णांक get_iसमयrspec64(काष्ठा iसमयrspec64 *it,
			स्थिर काष्ठा __kernel_iसमयrspec __user *uit)
अणु
	पूर्णांक ret;

	ret = get_बारpec64(&it->it_पूर्णांकerval, &uit->it_पूर्णांकerval);
	अगर (ret)
		वापस ret;

	ret = get_बारpec64(&it->it_value, &uit->it_value);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(get_iसमयrspec64);

पूर्णांक put_iसमयrspec64(स्थिर काष्ठा iसमयrspec64 *it,
			काष्ठा __kernel_iसमयrspec __user *uit)
अणु
	पूर्णांक ret;

	ret = put_बारpec64(&it->it_पूर्णांकerval, &uit->it_पूर्णांकerval);
	अगर (ret)
		वापस ret;

	ret = put_बारpec64(&it->it_value, &uit->it_value);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(put_iसमयrspec64);

पूर्णांक get_old_iसमयrspec32(काष्ठा iसमयrspec64 *its,
			स्थिर काष्ठा old_iसमयrspec32 __user *uits)
अणु

	अगर (__get_old_बारpec32(&its->it_पूर्णांकerval, &uits->it_पूर्णांकerval) ||
	    __get_old_बारpec32(&its->it_value, &uits->it_value))
		वापस -EFAULT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(get_old_iसमयrspec32);

पूर्णांक put_old_iसमयrspec32(स्थिर काष्ठा iसमयrspec64 *its,
			काष्ठा old_iसमयrspec32 __user *uits)
अणु
	अगर (__put_old_बारpec32(&its->it_पूर्णांकerval, &uits->it_पूर्णांकerval) ||
	    __put_old_बारpec32(&its->it_value, &uits->it_value))
		वापस -EFAULT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(put_old_iसमयrspec32);
