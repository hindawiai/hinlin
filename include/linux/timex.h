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
#अगर_अघोषित _LINUX_TIMEX_H
#घोषणा _LINUX_TIMEX_H

#समावेश <uapi/linux/समयx.h>

#घोषणा ADJ_ADJTIME		0x8000	/* चयन between adjसमय/adjसमयx modes */
#घोषणा ADJ_OFFSET_SINGLESHOT	0x0001	/* old-fashioned adjसमय */
#घोषणा ADJ_OFFSET_READONLY	0x2000	/* पढ़ो-only adjसमय */
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/param.h>

#समावेश <यंत्र/समयx.h>

#अगर_अघोषित अक्रमom_get_entropy
/*
 * The अक्रमom_get_entropy() function is used by the /dev/अक्रमom driver
 * in order to extract entropy via the relative unpredictability of
 * when an पूर्णांकerrupt takes places versus a high speed, fine-grained
 * timing source or cycle counter.  Since it will be occurred on every
 * single पूर्णांकerrupt, it must have a very low cost/overhead.
 *
 * By शेष we use get_cycles() क्रम this purpose, but inभागidual
 * architectures may override this in their यंत्र/समयx.h header file.
 */
#घोषणा अक्रमom_get_entropy()	get_cycles()
#पूर्ण_अगर

/*
 * SHIFT_PLL is used as a dampening factor to define how much we
 * adjust the frequency correction क्रम a given offset in PLL mode.
 * It also used in dampening the offset correction, to define how
 * much of the current value in समय_offset we correct क्रम each
 * second. Changing this value changes the stअगरfness of the ntp
 * adjusपंचांगent code. A lower value makes it more flexible, reducing
 * NTP convergence समय. A higher value makes it stअगरfer, increasing
 * convergence समय, but making the घड़ी more stable.
 *
 * In David Mills' nanokernel reference implementation SHIFT_PLL is 4.
 * However this seems to increase convergence समय much too दीर्घ.
 *
 * https://lists.ntp.org/pipermail/hackers/2008-January/003487.hपंचांगl
 *
 * In the above mailing list discussion, it seems the value of 4
 * was appropriate क्रम other Unix प्रणालीs with HZ=100, and that
 * SHIFT_PLL should be decreased as HZ increases. However, Linux's
 * घड़ी steering implementation is HZ independent.
 *
 * Through experimentation, a SHIFT_PLL value of 2 was found to allow
 * क्रम fast convergence (very similar to the NTPv3 code used prior to
 * v2.6.19), with good घड़ी stability.
 *
 *
 * SHIFT_FLL is used as a dampening factor to define how much we
 * adjust the frequency correction क्रम a given offset in FLL mode.
 * In David Mills' nanokernel reference implementation SHIFT_FLL is 2.
 *
 * MAXTC establishes the maximum समय स्थिरant of the PLL.
 */
#घोषणा SHIFT_PLL	2	/* PLL frequency factor (shअगरt) */
#घोषणा SHIFT_FLL	2	/* FLL frequency factor (shअगरt) */
#घोषणा MAXTC		10	/* maximum समय स्थिरant (shअगरt) */

/*
 * SHIFT_USEC defines the scaling (shअगरt) of the समय_freq and
 * समय_प्रकारolerance variables, which represent the current frequency
 * offset and maximum frequency tolerance.
 */
#घोषणा SHIFT_USEC 16		/* frequency offset scale (shअगरt) */
#घोषणा PPM_SCALE ((s64)NSEC_PER_USEC << (NTP_SCALE_SHIFT - SHIFT_USEC))
#घोषणा PPM_SCALE_INV_SHIFT 19
#घोषणा PPM_SCALE_INV ((1LL << (PPM_SCALE_INV_SHIFT + NTP_SCALE_SHIFT)) / \
		       PPM_SCALE + 1)

#घोषणा MAXPHASE 500000000L	/* max phase error (ns) */
#घोषणा MAXFREQ 500000		/* max frequency error (ns/s) */
#घोषणा MAXFREQ_SCALED ((s64)MAXFREQ << NTP_SCALE_SHIFT)
#घोषणा MINSEC 256		/* min पूर्णांकerval between updates (s) */
#घोषणा MAXSEC 2048		/* max पूर्णांकerval between updates (s) */
#घोषणा NTP_PHASE_LIMIT ((MAXPHASE / NSEC_PER_USEC) << 5) /* beyond max. dispersion */

/*
 * kernel variables
 * Note: maximum error = NTP sync distance = dispersion + delay / 2;
 * estimated error = NTP dispersion.
 */
बाह्य अचिन्हित दीर्घ tick_usec;		/* USER_HZ period (usec) */
बाह्य अचिन्हित दीर्घ tick_nsec;		/* SHIFTED_HZ period (nsec) */

/* Required to safely shअगरt negative values */
#घोषणा shअगरt_right(x, s) (अणु	\
	__typeof__(x) __x = (x);	\
	__typeof__(s) __s = (s);	\
	__x < 0 ? -(-__x >> __s) : __x >> __s;	\
पूर्ण)

#घोषणा NTP_SCALE_SHIFT		32

#घोषणा NTP_INTERVAL_FREQ  (HZ)
#घोषणा NTP_INTERVAL_LENGTH (NSEC_PER_SEC/NTP_INTERVAL_FREQ)

बाह्य पूर्णांक करो_adjसमयx(काष्ठा __kernel_समयx *);
बाह्य पूर्णांक करो_घड़ी_adjसमय(स्थिर घड़ीid_t which_घड़ी, काष्ठा __kernel_समयx * ktx);

बाह्य व्योम hardpps(स्थिर काष्ठा बारpec64 *, स्थिर काष्ठा बारpec64 *);

पूर्णांक पढ़ो_current_समयr(अचिन्हित दीर्घ *समयr_val);

/* The घड़ी frequency of the i8253/i8254 PIT */
#घोषणा PIT_TICK_RATE 1193182ul

#पूर्ण_अगर /* LINUX_TIMEX_H */
