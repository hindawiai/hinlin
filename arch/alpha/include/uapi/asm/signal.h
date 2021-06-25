<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASMAXP_SIGNAL_H
#घोषणा _UAPI_ASMAXP_SIGNAL_H

#समावेश <linux/types.h>

/* Aव्योम too many header ordering problems.  */
काष्ठा siginfo;

#अगर_अघोषित __KERNEL__
/* Here we must cater to libcs that poke about in kernel headers.  */

#घोषणा NSIG		32
प्रकार अचिन्हित दीर्घ sigset_t;

#पूर्ण_अगर /* __KERNEL__ */


/*
 * Linux/AXP has dअगरferent संकेत numbers that Linux/i386: I'm trying
 * to make it OSF/1 binary compatible, at least क्रम normal binaries.
 */
#घोषणा SIGHUP		 1
#घोषणा संक_विघ्न		 2
#घोषणा SIGQUIT		 3
#घोषणा संक_अवैध		 4
#घोषणा SIGTRAP		 5
#घोषणा SIGABRT		 6
#घोषणा SIGEMT		 7
#घोषणा संक_भ_त्रुटि		 8
#घोषणा SIGKILL		 9
#घोषणा SIGBUS		10
#घोषणा संक_अंश		11
#घोषणा SIGSYS		12
#घोषणा SIGPIPE		13
#घोषणा SIGALRM		14
#घोषणा संक_इति		15
#घोषणा SIGURG		16
#घोषणा SIGSTOP		17
#घोषणा SIGTSTP		18
#घोषणा SIGCONT		19
#घोषणा SIGCHLD		20
#घोषणा SIGTTIN		21
#घोषणा SIGTTOU		22
#घोषणा SIGIO		23
#घोषणा SIGXCPU		24
#घोषणा SIGXFSZ		25
#घोषणा SIGVTALRM	26
#घोषणा SIGPROF		27
#घोषणा SIGWINCH	28
#घोषणा SIGINFO		29
#घोषणा SIGUSR1		30
#घोषणा SIGUSR2		31

#घोषणा SIGPOLL	SIGIO
#घोषणा SIGPWR	SIGINFO
#घोषणा SIGIOT	SIGABRT

/* These should not be considered स्थिरants from userland.  */
#घोषणा SIGRTMIN	32
#घोषणा SIGRTMAX	_NSIG

#घोषणा SA_ONSTACK	0x00000001
#घोषणा SA_RESTART	0x00000002
#घोषणा SA_NOCLDSTOP	0x00000004
#घोषणा SA_NODEFER	0x00000008
#घोषणा SA_RESETHAND	0x00000010
#घोषणा SA_NOCLDWAIT	0x00000020
#घोषणा SA_SIGINFO	0x00000040

#घोषणा SA_ONESHOT	SA_RESETHAND
#घोषणा SA_NOMASK	SA_NODEFER

#घोषणा MINSIGSTKSZ	4096
#घोषणा SIGSTKSZ	16384

#घोषणा SIG_BLOCK          1	/* क्रम blocking संकेतs */
#घोषणा SIG_UNBLOCK        2	/* क्रम unblocking संकेतs */
#घोषणा SIG_SETMASK        3	/* क्रम setting the संकेत mask */

#समावेश <यंत्र-generic/संकेत-defs.h>

#अगर_अघोषित __KERNEL__
/* Here we must cater to libcs that poke about in kernel headers.  */

काष्ठा sigaction अणु
	जोड़ अणु
	  __sighandler_t	_sa_handler;
	  व्योम (*_sa_sigaction)(पूर्णांक, काष्ठा siginfo *, व्योम *);
	पूर्ण _u;
	sigset_t	sa_mask;
	पूर्णांक		sa_flags;
पूर्ण;

#घोषणा sa_handler	_u._sa_handler
#घोषणा sa_sigaction	_u._sa_sigaction

#पूर्ण_अगर /* __KERNEL__ */

प्रकार काष्ठा sigaltstack अणु
	व्योम __user *ss_sp;
	पूर्णांक ss_flags;
	माप_प्रकार ss_size;
पूर्ण stack_t;

/* sigstack(2) is deprecated, and will be withdrawn in a future version
   of the X/Open CAE Specअगरication.  Use sigaltstack instead.  It is only
   implemented here क्रम OSF/1 compatibility.  */

काष्ठा sigstack अणु
	व्योम __user *ss_sp;
	पूर्णांक ss_onstack;
पूर्ण;


#पूर्ण_अगर /* _UAPI_ASMAXP_SIGNAL_H */
