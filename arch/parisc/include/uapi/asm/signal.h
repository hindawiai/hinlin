<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_PARISC_SIGNAL_H
#घोषणा _UAPI_ASM_PARISC_SIGNAL_H

#घोषणा SIGHUP		 1
#घोषणा संक_विघ्न		 2
#घोषणा SIGQUIT		 3
#घोषणा संक_अवैध		 4
#घोषणा SIGTRAP		 5
#घोषणा SIGABRT		 6
#घोषणा SIGIOT		 6
#घोषणा SIGSTKFLT	 7
#घोषणा संक_भ_त्रुटि		 8
#घोषणा SIGKILL		 9
#घोषणा SIGBUS		10
#घोषणा संक_अंश		11
#घोषणा SIGXCPU		12
#घोषणा SIGPIPE		13
#घोषणा SIGALRM		14
#घोषणा संक_इति		15
#घोषणा SIGUSR1		16
#घोषणा SIGUSR2		17
#घोषणा SIGCHLD		18
#घोषणा SIGPWR		19
#घोषणा SIGVTALRM	20
#घोषणा SIGPROF		21
#घोषणा SIGIO		22
#घोषणा SIGPOLL		SIGIO
#घोषणा SIGWINCH	23
#घोषणा SIGSTOP		24
#घोषणा SIGTSTP		25
#घोषणा SIGCONT		26
#घोषणा SIGTTIN		27
#घोषणा SIGTTOU		28
#घोषणा SIGURG		29
#घोषणा SIGXFSZ		30
#घोषणा SIGUNUSED	31
#घोषणा SIGSYS		31

/* These should not be considered स्थिरants from userland.  */
#घोषणा SIGRTMIN	32
#घोषणा SIGRTMAX	_NSIG

#घोषणा SA_ONSTACK	0x00000001
#घोषणा SA_RESETHAND	0x00000004
#घोषणा SA_NOCLDSTOP	0x00000008
#घोषणा SA_SIGINFO	0x00000010
#घोषणा SA_NODEFER	0x00000020
#घोषणा SA_RESTART	0x00000040
#घोषणा SA_NOCLDWAIT	0x00000080

#घोषणा SA_NOMASK	SA_NODEFER
#घोषणा SA_ONESHOT	SA_RESETHAND

#घोषणा MINSIGSTKSZ	2048
#घोषणा SIGSTKSZ	8192

#समावेश <यंत्र-generic/संकेत-defs.h>

# अगरndef __ASSEMBLY__

#  include <linux/types.h>

/* Aव्योम too many header ordering problems.  */
काष्ठा siginfo;

प्रकार काष्ठा sigaltstack अणु
	व्योम __user *ss_sp;
	पूर्णांक ss_flags;
	माप_प्रकार ss_size;
पूर्ण stack_t;

#पूर्ण_अगर /* !__ASSEMBLY */
#पूर्ण_अगर /* _UAPI_ASM_PARISC_SIGNAL_H */
