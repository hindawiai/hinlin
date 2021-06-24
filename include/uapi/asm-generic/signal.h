<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__ASM_GENERIC_SIGNAL_H
#घोषणा _UAPI__ASM_GENERIC_SIGNAL_H

#समावेश <linux/types.h>

#घोषणा _NSIG		64
#घोषणा _NSIG_BPW	__BITS_PER_LONG
#घोषणा _NSIG_WORDS	(_NSIG / _NSIG_BPW)

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
#अगर_अघोषित SIGRTMAX
#घोषणा SIGRTMAX	_NSIG
#पूर्ण_अगर

#अगर !defined MINSIGSTKSZ || !defined SIGSTKSZ
#घोषणा MINSIGSTKSZ	2048
#घोषणा SIGSTKSZ	8192
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ sig[_NSIG_WORDS];
पूर्ण sigset_t;

/* not actually used, but required क्रम linux/syscalls.h */
प्रकार अचिन्हित दीर्घ old_sigset_t;

#समावेश <यंत्र-generic/संकेत-defs.h>

#अगर_घोषित SA_RESTORER
#घोषणा __ARCH_HAS_SA_RESTORER
#पूर्ण_अगर

#अगर_अघोषित __KERNEL__
काष्ठा sigaction अणु
	__sighandler_t sa_handler;
	अचिन्हित दीर्घ sa_flags;
#अगर_घोषित SA_RESTORER
	__sigrestore_t sa_restorer;
#पूर्ण_अगर
	sigset_t sa_mask;		/* mask last क्रम extensibility */
पूर्ण;
#पूर्ण_अगर

प्रकार काष्ठा sigaltstack अणु
	व्योम __user *ss_sp;
	पूर्णांक ss_flags;
	माप_प्रकार ss_size;
पूर्ण stack_t;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _UAPI__ASM_GENERIC_SIGNAL_H */
