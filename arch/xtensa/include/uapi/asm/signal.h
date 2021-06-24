<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/यंत्र-xtensa/संकेत.स
 *
 * Swiped from SH.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _UAPI_XTENSA_SIGNAL_H
#घोषणा _UAPI_XTENSA_SIGNAL_H


#घोषणा _NSIG		64
#घोषणा _NSIG_BPW	32
#घोषणा _NSIG_WORDS	(_NSIG / _NSIG_BPW)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

/* Aव्योम too many header ordering problems.  */
काष्ठा siginfo;
प्रकार अचिन्हित दीर्घ old_sigset_t;		/* at least 32 bits */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ sig[_NSIG_WORDS];
पूर्ण sigset_t;

#पूर्ण_अगर

#घोषणा SIGHUP		 1
#घोषणा संक_विघ्न		 2
#घोषणा SIGQUIT		 3
#घोषणा संक_अवैध		 4
#घोषणा SIGTRAP		 5
#घोषणा SIGABRT		 6
#घोषणा SIGIOT		 6
#घोषणा SIGBUS		 7
#घोषणा संक_भ_त्रुटि		 8
#घोषणा SIGKILL		 9
#घोषणा SIGUSR1		10
#घोषणा संक_अंश		11
#घोषणा SIGUSR2		12
#घोषणा SIGPIPE		13
#घोषणा SIGALRM		14
#घोषणा संक_इति		15
#घोषणा SIGSTKFLT	16
#घोषणा SIGCHLD		17
#घोषणा SIGCONT		18
#घोषणा SIGSTOP		19
#घोषणा SIGTSTP		20
#घोषणा SIGTTIN		21
#घोषणा SIGTTOU		22
#घोषणा SIGURG		23
#घोषणा SIGXCPU		24
#घोषणा SIGXFSZ		25
#घोषणा SIGVTALRM	26
#घोषणा SIGPROF		27
#घोषणा SIGWINCH	28
#घोषणा SIGIO		29
#घोषणा SIGPOLL		SIGIO
/* #घोषणा SIGLOST		29 */
#घोषणा SIGPWR		30
#घोषणा SIGSYS		31
#घोषणा	SIGUNUSED	31

/* These should not be considered स्थिरants from userland.  */
#घोषणा SIGRTMIN	32
#घोषणा SIGRTMAX	(_NSIG-1)

#घोषणा SA_RESTORER	0x04000000

#घोषणा MINSIGSTKSZ	2048
#घोषणा SIGSTKSZ	8192

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र-generic/संकेत-defs.h>

#अगर_अघोषित __KERNEL__

/* Here we must cater to libcs that poke about in kernel headers.  */

काष्ठा sigaction अणु
	जोड़ अणु
	  __sighandler_t _sa_handler;
	  व्योम (*_sa_sigaction)(पूर्णांक, काष्ठा siginfo *, व्योम *);
	पूर्ण _u;
	sigset_t sa_mask;
	अचिन्हित दीर्घ sa_flags;
	व्योम (*sa_restorer)(व्योम);
पूर्ण;

#घोषणा sa_handler	_u._sa_handler
#घोषणा sa_sigaction	_u._sa_sigaction

#पूर्ण_अगर /* __KERNEL__ */

प्रकार काष्ठा sigaltstack अणु
	व्योम *ss_sp;
	पूर्णांक ss_flags;
	माप_प्रकार ss_size;
पूर्ण stack_t;

#पूर्ण_अगर	/* __ASSEMBLY__ */
#पूर्ण_अगर /* _UAPI_XTENSA_SIGNAL_H */
