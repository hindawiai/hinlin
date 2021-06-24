<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * usr/include/linux/lp.h c.1991-1992 James Wiegand
 * many modअगरications copyright (C) 1992 Michael K. Johnson
 * Interrupt support added 1993 Nigel Gamble
 * Removed 8255 status defines from inside __KERNEL__ Marcelo Tosatti 
 */
#अगर_अघोषित _UAPI_LINUX_LP_H
#घोषणा _UAPI_LINUX_LP_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/*
 * Per POSIX guidelines, this module reserves the LP and lp prefixes
 * These are the lp_table[minor].flags flags...
 */
#घोषणा LP_EXIST 0x0001
#घोषणा LP_SELEC 0x0002
#घोषणा LP_BUSY	 0x0004
#घोषणा LP_BUSY_BIT_POS 2
#घोषणा LP_OFFL	 0x0008
#घोषणा LP_NOPA  0x0010
#घोषणा LP_ERR   0x0020
#घोषणा LP_ABORT 0x0040
#घोषणा LP_CAREFUL 0x0080 /* obsoleted -arca */
#घोषणा LP_ABORTOPEN 0x0100

#घोषणा LP_TRUST_IRQ_  0x0200 /* obsolete */
#घोषणा LP_NO_REVERSE  0x0400 /* No reverse mode available. */
#घोषणा LP_DATA_AVAIL  0x0800 /* Data is available. */

/* 
 * bit defines क्रम 8255 status port
 * base + 1
 * accessed with LP_S(minor), which माला_लो the byte...
 */
#घोषणा LP_PBUSY	0x80  /* inverted input, active high */
#घोषणा LP_PACK		0x40  /* unchanged input, active low */
#घोषणा LP_POUTPA	0x20  /* unchanged input, active high */
#घोषणा LP_PSELECD	0x10  /* unchanged input, active high */
#घोषणा LP_PERRORP	0x08  /* unchanged input, active low */

/* समयout क्रम each अक्षरacter.  This is relative to bus cycles -- it
 * is the count in a busy loop.  THIS IS THE VALUE TO CHANGE अगर you
 * have extremely slow prपूर्णांकing, or अगर the machine seems to slow करोwn
 * a lot when you prपूर्णांक.  If you have slow prपूर्णांकing, increase this
 * number and recompile, and अगर your प्रणाली माला_लो bogged करोwn, decrease
 * this number.  This can be changed with the tunelp(8) command as well.
 */

#घोषणा LP_INIT_CHAR 1000

/* The parallel port specs apparently say that there needs to be
 * a .5usec रुको beक्रमe and after the strobe.
 */

#घोषणा LP_INIT_WAIT 1

/* This is the amount of समय that the driver रुकोs क्रम the prपूर्णांकer to
 * catch up when the prपूर्णांकer's buffer appears to be filled.  If you
 * want to tune this and have a fast prपूर्णांकer (i.e. HPIIIP), decrease
 * this number, and अगर you have a slow prपूर्णांकer, increase this number.
 * This is in hundredths of a second, the शेष 2 being .05 second.
 * Or use the tunelp(8) command, which is especially nice अगर you want
 * change back and क्रमth between अक्षरacter and graphics prपूर्णांकing, which
 * are wildly dअगरferent...
 */

#घोषणा LP_INIT_TIME 2

/* IOCTL numbers */
#घोषणा LPCHAR   0x0601  /* corresponds to LP_INIT_CHAR */
#घोषणा LPTIME   0x0602  /* corresponds to LP_INIT_TIME */
#घोषणा LPABORT  0x0604  /* call with TRUE arg to पात on error,
			    FALSE to retry.  Default is retry.  */
#घोषणा LPSETIRQ 0x0605  /* call with new IRQ number,
			    or 0 क्रम polling (no IRQ) */
#घोषणा LPGETIRQ 0x0606  /* get the current IRQ number */
#घोषणा LPWAIT   0x0608  /* corresponds to LP_INIT_WAIT */
/* NOTE: LPCAREFUL is obsoleted and it' s always the शेष right now -arca */
#घोषणा LPCAREFUL   0x0609  /* call with TRUE arg to require out-of-paper, off-
			    line, and error indicators good on all ग_लिखोs,
			    FALSE to ignore them.  Default is ignore. */
#घोषणा LPABORTOPEN 0x060a  /* call with TRUE arg to पात खोलो() on error,
			    FALSE to ignore error.  Default is ignore.  */
#घोषणा LPGETSTATUS 0x060b  /* वापस LP_S(minor) */
#घोषणा LPRESET     0x060c  /* reset prपूर्णांकer */
#अगर_घोषित LP_STATS
#घोषणा LPGETSTATS  0x060d  /* get statistics (काष्ठा lp_stats) */
#पूर्ण_अगर
#घोषणा LPGETFLAGS  0x060e  /* get status flags */
#घोषणा LPSETTIMEOUT_OLD 0x060f /* set parport समयout */
#घोषणा LPSETTIMEOUT_NEW \
	_IOW(0x6, 0xf, __s64[2]) /* set parport समयout */
#अगर __BITS_PER_LONG == 64
#घोषणा LPSETTIMEOUT LPSETTIMEOUT_OLD
#अन्यथा
#घोषणा LPSETTIMEOUT (माप(समय_प्रकार) > माप(__kernel_दीर्घ_t) ? \
	LPSETTIMEOUT_NEW : LPSETTIMEOUT_OLD)
#पूर्ण_अगर

/* समयout क्रम prपूर्णांकk'ing a समयout, in jअगरfies (100ths of a second).
   This is also used क्रम re-checking error conditions अगर LP_ABORT is
   not set.  This is the शेष behavior. */

#घोषणा LP_TIMEOUT_INTERRUPT	(60 * HZ)
#घोषणा LP_TIMEOUT_POLLED	(10 * HZ)


#पूर्ण_अगर /* _UAPI_LINUX_LP_H */
