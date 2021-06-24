<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * Copyright (c) David L. Mills 1993                                         *
 *                                                                           *
 * Permission to use, copy, modअगरy, and distribute this software and its     *
 * करोcumentation क्रम any purpose and without fee is hereby granted, provided *
 * that the above copyright notice appears in all copies and that both the   *
 * copyright notice and this permission notice appear in supporting          *
 * करोcumentation, and that the name University of Delaware not be used in    *
 * advertising or खुलाity pertaining to distribution of the software       *
 * without specअगरic, written prior permission.  The University of Delaware   *
 * makes no representations about the suitability this software क्रम any      *
 * purpose.  It is provided "as is" without express or implied warranty.     *
 *                                                                           *
 *****************************************************************************/

/*
 * Modअगरication history समयx.h
 *
 * 29 Dec 97	Russell King
 *	Moved CLOCK_TICK_RATE, CLOCK_TICK_FACTOR and FINETUNE to यंत्र/समयx.h
 *	क्रम ARM machines
 *
 *  9 Jan 97    Adrian Sun
 *      Shअगरted LATCH define to allow access to alpha machines.
 *
 * 26 Sep 94	David L. Mills
 *	Added defines क्रम hybrid phase/frequency-lock loop.
 *
 * 19 Mar 94	David L. Mills
 *	Moved defines from kernel routines to header file and added new
 *	defines क्रम PPS phase-lock loop.
 *
 * 20 Feb 94	David L. Mills
 *	Revised status codes and काष्ठाures क्रम बाह्यal घड़ी and PPS
 *	संकेत discipline.
 *
 * 28 Nov 93	David L. Mills
 *	Adjusted parameters to improve stability and increase poll
 *	पूर्णांकerval.
 *
 * 17 Sep 93    David L. Mills
 *      Created file $NTP/include/sys/समयx.h
 * 07 Oct 93    Torsten Duwe
 *      Derived linux/समयx.h
 * 1995-08-13    Torsten Duwe
 *      kernel PLL updated to 1994-12-13 specs (rfc-1589)
 * 1997-08-30    Ulrich Windl
 *      Added new स्थिरant NTP_PHASE_LIMIT
 * 2004-08-12    Christoph Lameter
 *      Reworked समय पूर्णांकerpolation logic
 */
#अगर_अघोषित _UAPI_LINUX_TIMEX_H
#घोषणा _UAPI_LINUX_TIMEX_H

#समावेश <linux/समय.स>

#घोषणा NTP_API		4	/* NTP API version */

#अगर_अघोषित __KERNEL__
/*
 * syscall पूर्णांकerface - used (मुख्यly by NTP daemon)
 * to discipline kernel घड़ी oscillator
 */
काष्ठा समयx अणु
	अचिन्हित पूर्णांक modes;	/* mode selector */
	__kernel_दीर्घ_t offset;	/* समय offset (usec) */
	__kernel_दीर्घ_t freq;	/* frequency offset (scaled ppm) */
	__kernel_दीर्घ_t maxerror;/* maximum error (usec) */
	__kernel_दीर्घ_t esterror;/* estimated error (usec) */
	पूर्णांक status;		/* घड़ी command/status */
	__kernel_दीर्घ_t स्थिरant;/* pll समय स्थिरant */
	__kernel_दीर्घ_t precision;/* घड़ी precision (usec) (पढ़ो only) */
	__kernel_दीर्घ_t tolerance;/* घड़ी frequency tolerance (ppm)
				   * (पढ़ो only)
				   */
	काष्ठा समयval समय;	/* (पढ़ो only, except क्रम ADJ_SETOFFSET) */
	__kernel_दीर्घ_t tick;	/* (modअगरied) usecs between घड़ी ticks */

	__kernel_दीर्घ_t ppsfreq;/* pps frequency (scaled ppm) (ro) */
	__kernel_दीर्घ_t jitter; /* pps jitter (us) (ro) */
	पूर्णांक shअगरt;              /* पूर्णांकerval duration (s) (shअगरt) (ro) */
	__kernel_दीर्घ_t stabil;            /* pps stability (scaled ppm) (ro) */
	__kernel_दीर्घ_t jitcnt; /* jitter limit exceeded (ro) */
	__kernel_दीर्घ_t calcnt; /* calibration पूर्णांकervals (ro) */
	__kernel_दीर्घ_t errcnt; /* calibration errors (ro) */
	__kernel_दीर्घ_t stbcnt; /* stability limit exceeded (ro) */

	पूर्णांक tai;		/* TAI offset (ro) */

	पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32;
	पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32;
	पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32;
पूर्ण;
#पूर्ण_अगर

काष्ठा __kernel_समयx_समयval अणु
	__kernel_समय64_t       tv_sec;
	दीर्घ दीर्घ		tv_usec;
पूर्ण;

काष्ठा __kernel_समयx अणु
	अचिन्हित पूर्णांक modes;	/* mode selector */
	पूर्णांक :32;            /* pad */
	दीर्घ दीर्घ offset;	/* समय offset (usec) */
	दीर्घ दीर्घ freq;	/* frequency offset (scaled ppm) */
	दीर्घ दीर्घ maxerror;/* maximum error (usec) */
	दीर्घ दीर्घ esterror;/* estimated error (usec) */
	पूर्णांक status;		/* घड़ी command/status */
	पूर्णांक :32;            /* pad */
	दीर्घ दीर्घ स्थिरant;/* pll समय स्थिरant */
	दीर्घ दीर्घ precision;/* घड़ी precision (usec) (पढ़ो only) */
	दीर्घ दीर्घ tolerance;/* घड़ी frequency tolerance (ppm)
				   * (पढ़ो only)
				   */
	काष्ठा __kernel_समयx_समयval समय;	/* (पढ़ो only, except क्रम ADJ_SETOFFSET) */
	दीर्घ दीर्घ tick;	/* (modअगरied) usecs between घड़ी ticks */

	दीर्घ दीर्घ ppsfreq;/* pps frequency (scaled ppm) (ro) */
	दीर्घ दीर्घ jitter; /* pps jitter (us) (ro) */
	पूर्णांक shअगरt;              /* पूर्णांकerval duration (s) (shअगरt) (ro) */
	पूर्णांक :32;            /* pad */
	दीर्घ दीर्घ stabil;            /* pps stability (scaled ppm) (ro) */
	दीर्घ दीर्घ jitcnt; /* jitter limit exceeded (ro) */
	दीर्घ दीर्घ calcnt; /* calibration पूर्णांकervals (ro) */
	दीर्घ दीर्घ errcnt; /* calibration errors (ro) */
	दीर्घ दीर्घ stbcnt; /* stability limit exceeded (ro) */

	पूर्णांक tai;		/* TAI offset (ro) */

	पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32;
	पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32;
	पूर्णांक  :32; पूर्णांक  :32; पूर्णांक  :32;
पूर्ण;

/*
 * Mode codes (समयx.mode)
 */
#घोषणा ADJ_OFFSET		0x0001	/* समय offset */
#घोषणा ADJ_FREQUENCY		0x0002	/* frequency offset */
#घोषणा ADJ_MAXERROR		0x0004	/* maximum समय error */
#घोषणा ADJ_ESTERROR		0x0008	/* estimated समय error */
#घोषणा ADJ_STATUS		0x0010	/* घड़ी status */
#घोषणा ADJ_TIMECONST		0x0020	/* pll समय स्थिरant */
#घोषणा ADJ_TAI			0x0080	/* set TAI offset */
#घोषणा ADJ_SETOFFSET		0x0100  /* add 'time' to current समय */
#घोषणा ADJ_MICRO		0x1000	/* select microsecond resolution */
#घोषणा ADJ_न_अंकO		0x2000	/* select nanosecond resolution */
#घोषणा ADJ_TICK		0x4000	/* tick value */

#अगर_अघोषित __KERNEL__
#घोषणा ADJ_OFFSET_SINGLESHOT	0x8001	/* old-fashioned adjसमय */
#घोषणा ADJ_OFFSET_SS_READ	0xa001	/* पढ़ो-only adjसमय */
#पूर्ण_अगर

/* NTP userland likes the MOD_ prefix better */
#घोषणा MOD_OFFSET	ADJ_OFFSET
#घोषणा MOD_FREQUENCY	ADJ_FREQUENCY
#घोषणा MOD_MAXERROR	ADJ_MAXERROR
#घोषणा MOD_ESTERROR	ADJ_ESTERROR
#घोषणा MOD_STATUS	ADJ_STATUS
#घोषणा MOD_TIMECONST	ADJ_TIMECONST
#घोषणा MOD_TAI	ADJ_TAI
#घोषणा MOD_MICRO	ADJ_MICRO
#घोषणा MOD_न_अंकO	ADJ_न_अंकO


/*
 * Status codes (समयx.status)
 */
#घोषणा STA_PLL		0x0001	/* enable PLL updates (rw) */
#घोषणा STA_PPSFREQ	0x0002	/* enable PPS freq discipline (rw) */
#घोषणा STA_PPSTIME	0x0004	/* enable PPS समय discipline (rw) */
#घोषणा STA_FLL		0x0008	/* select frequency-lock mode (rw) */

#घोषणा STA_INS		0x0010	/* insert leap (rw) */
#घोषणा STA_DEL		0x0020	/* delete leap (rw) */
#घोषणा STA_UNSYNC	0x0040	/* घड़ी unsynchronized (rw) */
#घोषणा STA_FREQHOLD	0x0080	/* hold frequency (rw) */

#घोषणा STA_PPSSIGNAL	0x0100	/* PPS संकेत present (ro) */
#घोषणा STA_PPSJITTER	0x0200	/* PPS संकेत jitter exceeded (ro) */
#घोषणा STA_PPSWANDER	0x0400	/* PPS संकेत wander exceeded (ro) */
#घोषणा STA_PPSERROR	0x0800	/* PPS संकेत calibration error (ro) */

#घोषणा STA_CLOCKERR	0x1000	/* घड़ी hardware fault (ro) */
#घोषणा STA_न_अंकO	0x2000	/* resolution (0 = us, 1 = ns) (ro) */
#घोषणा STA_MODE	0x4000	/* mode (0 = PLL, 1 = FLL) (ro) */
#घोषणा STA_CLK		0x8000	/* घड़ी source (0 = A, 1 = B) (ro) */

/* पढ़ो-only bits */
#घोषणा STA_RONLY (STA_PPSSIGNAL | STA_PPSJITTER | STA_PPSWANDER | \
	STA_PPSERROR | STA_CLOCKERR | STA_न_अंकO | STA_MODE | STA_CLK)

/*
 * Clock states (समय_state)
 */
#घोषणा TIME_OK		0	/* घड़ी synchronized, no leap second */
#घोषणा TIME_INS	1	/* insert leap second */
#घोषणा TIME_DEL	2	/* delete leap second */
#घोषणा TIME_OOP	3	/* leap second in progress */
#घोषणा TIME_WAIT	4	/* leap second has occurred */
#घोषणा TIME_ERROR	5	/* घड़ी not synchronized */
#घोषणा TIME_BAD	TIME_ERROR /* bw compat */


#पूर्ण_अगर /* _UAPI_LINUX_TIMEX_H */
