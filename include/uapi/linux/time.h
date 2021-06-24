<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_TIME_H
#घोषणा _UAPI_LINUX_TIME_H

#समावेश <linux/types.h>
#समावेश <linux/समय_प्रकारypes.h>

#अगर_अघोषित __KERNEL__
#अगर_अघोषित _STRUCT_TIMESPEC
#घोषणा _STRUCT_TIMESPEC
काष्ठा बारpec अणु
	__kernel_old_समय_प्रकार	tv_sec;		/* seconds */
	दीर्घ			tv_nsec;	/* nanoseconds */
पूर्ण;
#पूर्ण_अगर

काष्ठा समयval अणु
	__kernel_old_समय_प्रकार	tv_sec;		/* seconds */
	__kernel_suseconds_t	tv_usec;	/* microseconds */
पूर्ण;

काष्ठा iसमयrspec अणु
	काष्ठा बारpec it_पूर्णांकerval;/* समयr period */
	काष्ठा बारpec it_value;	/* समयr expiration */
पूर्ण;

काष्ठा iसमयrval अणु
	काष्ठा समयval it_पूर्णांकerval;/* समयr पूर्णांकerval */
	काष्ठा समयval it_value;	/* current value */
पूर्ण;
#पूर्ण_अगर

काष्ठा समयzone अणु
	पूर्णांक	tz_minuteswest;	/* minutes west of Greenwich */
	पूर्णांक	tz_dstसमय;	/* type of dst correction */
पूर्ण;

/*
 * Names of the पूर्णांकerval समयrs, and काष्ठाure
 * defining a समयr setting:
 */
#घोषणा	ITIMER_REAL		0
#घोषणा	ITIMER_VIRTUAL		1
#घोषणा	ITIMER_PROF		2

/*
 * The IDs of the various प्रणाली घड़ीs (क्रम POSIX.1b पूर्णांकerval समयrs):
 */
#घोषणा CLOCK_REALTIME			0
#घोषणा CLOCK_MONOTONIC			1
#घोषणा CLOCK_PROCESS_CPUTIME_ID	2
#घोषणा CLOCK_THREAD_CPUTIME_ID		3
#घोषणा CLOCK_MONOTONIC_RAW		4
#घोषणा CLOCK_REALTIME_COARSE		5
#घोषणा CLOCK_MONOTONIC_COARSE		6
#घोषणा CLOCK_BOOTTIME			7
#घोषणा CLOCK_REALTIME_ALARM		8
#घोषणा CLOCK_BOOTTIME_ALARM		9
/*
 * The driver implementing this got हटाओd. The घड़ी ID is kept as a
 * place holder. Do not reuse!
 */
#घोषणा CLOCK_SGI_CYCLE			10
#घोषणा CLOCK_TAI			11

#घोषणा MAX_CLOCKS			16
#घोषणा CLOCKS_MASK			(CLOCK_REALTIME | CLOCK_MONOTONIC)
#घोषणा CLOCKS_MONO			CLOCK_MONOTONIC

/*
 * The various flags क्रम setting POSIX.1b पूर्णांकerval समयrs:
 */
#घोषणा TIMER_ABSTIME			0x01

#पूर्ण_अगर /* _UAPI_LINUX_TIME_H */
