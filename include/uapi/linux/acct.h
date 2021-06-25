<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  BSD Process Accounting क्रम Linux - Definitions
 *
 *  Author: Marco van Wieringen (mvw@planets.elm.net)
 *
 *  This header file contains the definitions needed to implement
 *  BSD-style process accounting. The kernel accounting code and all
 *  user-level programs that try to करो something useful with the
 *  process accounting log must include this file.
 *
 *  Copyright (C) 1995 - 1997 Marco van Wieringen - ELM Consultancy B.V.
 *
 */

#अगर_अघोषित _UAPI_LINUX_ACCT_H
#घोषणा _UAPI_LINUX_ACCT_H

#समावेश <linux/types.h>

#समावेश <यंत्र/param.h>
#समावेश <यंत्र/byteorder.h>

/* 
 *  comp_t is a 16-bit "floating" poपूर्णांक number with a 3-bit base 8
 *  exponent and a 13-bit fraction.
 *  comp2_t is 24-bit with 5-bit base 2 exponent and 20 bit fraction
 *  (leading 1 not stored).
 *  See linux/kernel/acct.c क्रम the specअगरic encoding प्रणालीs used.
 */

प्रकार __u16	comp_t;
प्रकार __u32	comp2_t;

/*
 *   accounting file record
 *
 *   This काष्ठाure contains all of the inक्रमmation written out to the
 *   process accounting file whenever a process निकासs.
 */

#घोषणा ACCT_COMM	16

काष्ठा acct
अणु
	अक्षर		ac_flag;		/* Flags */
	अक्षर		ac_version;		/* Always set to ACCT_VERSION */
	/* क्रम binary compatibility back until 2.0 */
	__u16		ac_uid16;		/* LSB of Real User ID */
	__u16		ac_gid16;		/* LSB of Real Group ID */
	__u16		ac_tty;			/* Control Terminal */
	/* __u32 range means बार from 1970 to 2106 */
	__u32		ac_bसमय;		/* Process Creation Time */
	comp_t		ac_uसमय;		/* User Time */
	comp_t		ac_sसमय;		/* System Time */
	comp_t		ac_eसमय;		/* Elapsed Time */
	comp_t		ac_mem;			/* Average Memory Usage */
	comp_t		ac_io;			/* Chars Transferred */
	comp_t		ac_rw;			/* Blocks Read or Written */
	comp_t		ac_minflt;		/* Minor Pagefaults */
	comp_t		ac_majflt;		/* Major Pagefaults */
	comp_t		ac_swaps;		/* Number of Swaps */
/* m68k had no padding here. */
#अगर !defined(CONFIG_M68K) || !defined(__KERNEL__)
	__u16		ac_ahz;			/* AHZ */
#पूर्ण_अगर
	__u32		ac_निकासcode;		/* Exitcode */
	अक्षर		ac_comm[ACCT_COMM + 1];	/* Command Name */
	__u8		ac_eसमय_hi;		/* Elapsed Time MSB */
	__u16		ac_eसमय_lo;		/* Elapsed Time LSB */
	__u32		ac_uid;			/* Real User ID */
	__u32		ac_gid;			/* Real Group ID */
पूर्ण;

काष्ठा acct_v3
अणु
	अक्षर		ac_flag;		/* Flags */
	अक्षर		ac_version;		/* Always set to ACCT_VERSION */
	__u16		ac_tty;			/* Control Terminal */
	__u32		ac_निकासcode;		/* Exitcode */
	__u32		ac_uid;			/* Real User ID */
	__u32		ac_gid;			/* Real Group ID */
	__u32		ac_pid;			/* Process ID */
	__u32		ac_ppid;		/* Parent Process ID */
	/* __u32 range means बार from 1970 to 2106 */
	__u32		ac_bसमय;		/* Process Creation Time */
#अगर_घोषित __KERNEL__
	__u32		ac_eसमय;		/* Elapsed Time */
#अन्यथा
	भग्न		ac_eसमय;		/* Elapsed Time */
#पूर्ण_अगर
	comp_t		ac_uसमय;		/* User Time */
	comp_t		ac_sसमय;		/* System Time */
	comp_t		ac_mem;			/* Average Memory Usage */
	comp_t		ac_io;			/* Chars Transferred */
	comp_t		ac_rw;			/* Blocks Read or Written */
	comp_t		ac_minflt;		/* Minor Pagefaults */
	comp_t		ac_majflt;		/* Major Pagefaults */
	comp_t		ac_swaps;		/* Number of Swaps */
	अक्षर		ac_comm[ACCT_COMM];	/* Command Name */
पूर्ण;

/*
 *  accounting flags
 */
				/* bit set when the process ... */
#घोषणा AFORK		0x01	/* ... executed विभाजन, but did not exec */
#घोषणा ASU		0x02	/* ... used super-user privileges */
#घोषणा ACOMPAT		0x04	/* ... used compatibility mode (VAX only not used) */
#घोषणा ACORE		0x08	/* ... dumped core */
#घोषणा AXSIG		0x10	/* ... was समाप्तed by a संकेत */

#अगर defined(__BYTE_ORDER) ? __BYTE_ORDER == __BIG_ENDIAN : defined(__BIG_ENDIAN)
#घोषणा ACCT_BYTEORDER	0x80	/* accounting file is big endian */
#या_अगर defined(__BYTE_ORDER) ? __BYTE_ORDER == __LITTLE_ENDIAN : defined(__LITTLE_ENDIAN)
#घोषणा ACCT_BYTEORDER	0x00	/* accounting file is little endian */
#अन्यथा
#त्रुटि unspecअगरied endianness
#पूर्ण_अगर

#अगर_अघोषित __KERNEL__
#घोषणा ACCT_VERSION	2
#घोषणा AHZ		(HZ)
#पूर्ण_अगर	/* __KERNEL */


#पूर्ण_अगर /* _UAPI_LINUX_ACCT_H */
