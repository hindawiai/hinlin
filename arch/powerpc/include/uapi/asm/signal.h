<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_POWERPC_SIGNAL_H
#घोषणा _UAPI_ASM_POWERPC_SIGNAL_H

#समावेश <linux/types.h>

#घोषणा _NSIG		64
#अगर_घोषित __घातerpc64__
#घोषणा _NSIG_BPW	64
#अन्यथा
#घोषणा _NSIG_BPW	32
#पूर्ण_अगर
#घोषणा _NSIG_WORDS	(_NSIG / _NSIG_BPW)

प्रकार अचिन्हित दीर्घ old_sigset_t;		/* at least 32 bits */

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ sig[_NSIG_WORDS];
पूर्ण sigset_t;

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

#घोषणा SA_RESTORER	0x04000000U

#घोषणा MINSIGSTKSZ	2048
#घोषणा SIGSTKSZ	8192

#समावेश <यंत्र-generic/संकेत-defs.h>

#अगर_अघोषित __KERNEL__
काष्ठा old_sigaction अणु
	__sighandler_t sa_handler;
	old_sigset_t sa_mask;
	अचिन्हित दीर्घ sa_flags;
	__sigrestore_t sa_restorer;
पूर्ण;

काष्ठा sigaction अणु
	__sighandler_t sa_handler;
	अचिन्हित दीर्घ sa_flags;
	__sigrestore_t sa_restorer;
	sigset_t sa_mask;		/* mask last क्रम extensibility */
पूर्ण;
#पूर्ण_अगर

प्रकार काष्ठा sigaltstack अणु
	व्योम __user *ss_sp;
	पूर्णांक ss_flags;
	माप_प्रकार ss_size;
पूर्ण stack_t;


#अगर_अघोषित __घातerpc64__
/*
 * These are parameters to dbg_sigवापस syscall.  They enable or
 * disable certain debugging things that can be करोne from संकेत
 * handlers.  The dbg_sigवापस syscall *must* be called from a
 * SA_SIGINFO संकेत so the ucontext can be passed to it.  It takes an
 * array of काष्ठा sig_dbg_op, which has the debug operations to
 * perक्रमm beक्रमe वापसing from the संकेत.
 */
काष्ठा sig_dbg_op अणु
	पूर्णांक dbg_type;
	अचिन्हित दीर्घ dbg_value;
पूर्ण;

/* Enable or disable single-stepping.  The value sets the state. */
#घोषणा SIG_DBG_SINGLE_STEPPING		1

/* Enable or disable branch tracing.  The value sets the state. */
#घोषणा SIG_DBG_BRANCH_TRACING		2
#पूर्ण_अगर /* ! __घातerpc64__ */

#पूर्ण_अगर /* _UAPI_ASM_POWERPC_SIGNAL_H */
