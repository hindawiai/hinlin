<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 96, 97, 98, 99, 2003 by Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित _UAPI_ASM_SIGNAL_H
#घोषणा _UAPI_ASM_SIGNAL_H

#समावेश <linux/types.h>

#घोषणा _NSIG		128
#घोषणा _NSIG_BPW	(माप(अचिन्हित दीर्घ) * 8)
#घोषणा _NSIG_WORDS	(_NSIG / _NSIG_BPW)

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ sig[_NSIG_WORDS];
पूर्ण sigset_t;

प्रकार अचिन्हित दीर्घ old_sigset_t;		/* at least 32 bits */

#घोषणा SIGHUP		 1	/* Hangup (POSIX).  */
#घोषणा संक_विघ्न		 2	/* Interrupt (ANSI).  */
#घोषणा SIGQUIT		 3	/* Quit (POSIX).  */
#घोषणा संक_अवैध		 4	/* Illegal inकाष्ठाion (ANSI).	*/
#घोषणा SIGTRAP		 5	/* Trace trap (POSIX).	*/
#घोषणा SIGIOT		 6	/* IOT trap (4.2 BSD).	*/
#घोषणा SIGABRT		 SIGIOT /* Abort (ANSI).  */
#घोषणा SIGEMT		 7
#घोषणा संक_भ_त्रुटि		 8	/* Floating-poपूर्णांक exception (ANSI).  */
#घोषणा SIGKILL		 9	/* Kill, unblockable (POSIX).  */
#घोषणा SIGBUS		10	/* BUS error (4.2 BSD).	 */
#घोषणा संक_अंश		11	/* Segmentation violation (ANSI).  */
#घोषणा SIGSYS		12
#घोषणा SIGPIPE		13	/* Broken pipe (POSIX).	 */
#घोषणा SIGALRM		14	/* Alarm घड़ी (POSIX).	 */
#घोषणा संक_इति		15	/* Termination (ANSI).	*/
#घोषणा SIGUSR1		16	/* User-defined संकेत 1 (POSIX).  */
#घोषणा SIGUSR2		17	/* User-defined संकेत 2 (POSIX).  */
#घोषणा SIGCHLD		18	/* Child status has changed (POSIX).  */
#घोषणा SIGCLD		SIGCHLD /* Same as SIGCHLD (System V).	*/
#घोषणा SIGPWR		19	/* Power failure restart (System V).  */
#घोषणा SIGWINCH	20	/* Winकरोw size change (4.3 BSD, Sun).  */
#घोषणा SIGURG		21	/* Urgent condition on socket (4.2 BSD).  */
#घोषणा SIGIO		22	/* I/O now possible (4.2 BSD).	*/
#घोषणा SIGPOLL		SIGIO	/* Pollable event occurred (System V).	*/
#घोषणा SIGSTOP		23	/* Stop, unblockable (POSIX).  */
#घोषणा SIGTSTP		24	/* Keyboard stop (POSIX).  */
#घोषणा SIGCONT		25	/* Continue (POSIX).  */
#घोषणा SIGTTIN		26	/* Background पढ़ो from tty (POSIX).  */
#घोषणा SIGTTOU		27	/* Background ग_लिखो to tty (POSIX).  */
#घोषणा SIGVTALRM	28	/* Virtual alarm घड़ी (4.2 BSD).  */
#घोषणा SIGPROF		29	/* Profiling alarm घड़ी (4.2 BSD).  */
#घोषणा SIGXCPU		30	/* CPU limit exceeded (4.2 BSD).  */
#घोषणा SIGXFSZ		31	/* File size limit exceeded (4.2 BSD).	*/

/* These should not be considered स्थिरants from userland.  */
#घोषणा SIGRTMIN	32
#घोषणा SIGRTMAX	_NSIG

/*
 * SA_RESTORER used to be defined as 0x04000000 but only the O32 ABI ever
 * supported its use and no libc was using it, so the entire sa-restorer
 * functionality was हटाओd with lmo commit 39bffc12c3580ab क्रम 2.5.48
 * retaining only the SA_RESTORER definition as a reminder to aव्योम
 * accidental reuse of the mask bit.
 */
#घोषणा SA_ONSTACK	0x08000000
#घोषणा SA_RESETHAND	0x80000000
#घोषणा SA_RESTART	0x10000000
#घोषणा SA_SIGINFO	0x00000008
#घोषणा SA_NODEFER	0x40000000
#घोषणा SA_NOCLDWAIT	0x00010000
#घोषणा SA_NOCLDSTOP	0x00000001

#घोषणा SA_NOMASK	SA_NODEFER
#घोषणा SA_ONESHOT	SA_RESETHAND

#घोषणा MINSIGSTKSZ    2048
#घोषणा SIGSTKSZ       8192


#घोषणा SIG_BLOCK	1	/* क्रम blocking संकेतs */
#घोषणा SIG_UNBLOCK	2	/* क्रम unblocking संकेतs */
#घोषणा SIG_SETMASK	3	/* क्रम setting the संकेत mask */

#समावेश <यंत्र-generic/संकेत-defs.h>

#अगर_अघोषित __KERNEL__
काष्ठा sigaction अणु
	अचिन्हित पूर्णांक	sa_flags;
	__sighandler_t	sa_handler;
	sigset_t	sa_mask;
पूर्ण;
#पूर्ण_अगर

/* IRIX compatible stack_t  */
प्रकार काष्ठा sigaltstack अणु
	व्योम __user *ss_sp;
	माप_प्रकार ss_size;
	पूर्णांक ss_flags;
पूर्ण stack_t;


#पूर्ण_अगर /* _UAPI_ASM_SIGNAL_H */
