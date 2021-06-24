<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_M68K_SIGNAL_H
#घोषणा _UAPI_M68K_SIGNAL_H

#समावेश <linux/types.h>

/* Aव्योम too many header ordering problems.  */
काष्ठा siginfo;

#अगर_अघोषित __KERNEL__
/* Here we must cater to libcs that poke about in kernel headers.  */

#घोषणा NSIG		32
प्रकार अचिन्हित दीर्घ sigset_t;

#पूर्ण_अगर /* __KERNEL__ */

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
/*
#घोषणा SIGLOST		29
*/
#घोषणा SIGPWR		30
#घोषणा SIGSYS		31
#घोषणा	SIGUNUSED	31

/* These should not be considered स्थिरants from userland.  */
#घोषणा SIGRTMIN	32
#घोषणा SIGRTMAX	_NSIG

#घोषणा MINSIGSTKSZ	2048
#घोषणा SIGSTKSZ	8192

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
	व्योम __user *ss_sp;
	पूर्णांक ss_flags;
	माप_प्रकार ss_size;
पूर्ण stack_t;

#पूर्ण_अगर /* _UAPI_M68K_SIGNAL_H */
