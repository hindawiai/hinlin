<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__SPARC_SIGNAL_H
#घोषणा _UAPI__SPARC_SIGNAL_H

#समावेश <यंत्र/sigcontext.h>
#समावेश <linux/compiler.h>


/* On the Sparc the संकेत handlers get passed a 'sub-signal' code
 * क्रम certain संकेत types, which we करोcument here.
 */
#घोषणा SIGHUP		 1
#घोषणा संक_विघ्न		 2
#घोषणा SIGQUIT		 3
#घोषणा संक_अवैध		 4
#घोषणा    SUBSIG_STACK       0
#घोषणा    SUBSIG_ILLINST     2
#घोषणा    SUBSIG_PRIVINST    3
#घोषणा    SUBSIG_BADTRAP(t)  (0x80 + (t))

#घोषणा SIGTRAP		 5
#घोषणा SIGABRT		 6
#घोषणा SIGIOT		 6

#घोषणा SIGEMT           7
#घोषणा    SUBSIG_TAG    10

#घोषणा संक_भ_त्रुटि		 8
#घोषणा    SUBSIG_FPDISABLED     0x400
#घोषणा    SUBSIG_FPERROR        0x404
#घोषणा    SUBSIG_FPINTOVFL      0x001
#घोषणा    SUBSIG_FPSTSIG        0x002
#घोषणा    SUBSIG_IDIVZERO       0x014
#घोषणा    SUBSIG_FPINEXACT      0x0c4
#घोषणा    SUBSIG_FPDIVZERO      0x0c8
#घोषणा    SUBSIG_FPUNFLOW       0x0cc
#घोषणा    SUBSIG_FPOPERROR      0x0d0
#घोषणा    SUBSIG_FPOVFLOW       0x0d4

#घोषणा SIGKILL		 9
#घोषणा SIGBUS          10
#घोषणा    SUBSIG_BUSTIMEOUT    1
#घोषणा    SUBSIG_ALIGNMENT     2
#घोषणा    SUBSIG_MISCERROR     5

#घोषणा संक_अंश		11
#घोषणा    SUBSIG_NOMAPPING     3
#घोषणा    SUBSIG_PROTECTION    4
#घोषणा    SUBSIG_SEGERROR      5

#घोषणा SIGSYS		12

#घोषणा SIGPIPE		13
#घोषणा SIGALRM		14
#घोषणा संक_इति		15
#घोषणा SIGURG          16

/* SunOS values which deviate from the Linux/i386 ones */
#घोषणा SIGSTOP		17
#घोषणा SIGTSTP		18
#घोषणा SIGCONT		19
#घोषणा SIGCHLD		20
#घोषणा SIGTTIN		21
#घोषणा SIGTTOU		22
#घोषणा SIGIO		23
#घोषणा SIGPOLL		SIGIO   /* SysV name क्रम SIGIO */
#घोषणा SIGXCPU		24
#घोषणा SIGXFSZ		25
#घोषणा SIGVTALRM	26
#घोषणा SIGPROF		27
#घोषणा SIGWINCH	28
#घोषणा SIGLOST		29
#घोषणा SIGPWR		SIGLOST
#घोषणा SIGUSR1		30
#घोषणा SIGUSR2		31

/* Most things should be clean enough to redefine this at will, अगर care
   is taken to make libc match.  */

#घोषणा __OLD_NSIG	32
#घोषणा __NEW_NSIG      64
#अगर_घोषित __arch64__
#घोषणा _NSIG_BPW       64
#अन्यथा
#घोषणा _NSIG_BPW       32
#पूर्ण_अगर
#घोषणा _NSIG_WORDS     (__NEW_NSIG / _NSIG_BPW)

#घोषणा SIGRTMIN       32
#घोषणा SIGRTMAX       __NEW_NSIG

#अगर defined(__KERNEL__) || defined(__WANT_POSIX1B_SIGNALS__)
#घोषणा _NSIG			__NEW_NSIG
#घोषणा __new_sigset_t		sigset_t
#घोषणा __new_sigaction		sigaction
#घोषणा __new_sigaction32	sigaction32
#घोषणा __old_sigset_t		old_sigset_t
#घोषणा __old_sigaction		old_sigaction
#घोषणा __old_sigaction32	old_sigaction32
#अन्यथा
#घोषणा _NSIG			__OLD_NSIG
#घोषणा NSIG			_NSIG
#घोषणा __old_sigset_t		sigset_t
#घोषणा __old_sigaction		sigaction
#घोषणा __old_sigaction32	sigaction32
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

प्रकार अचिन्हित दीर्घ __old_sigset_t;            /* at least 32 bits */

प्रकार काष्ठा अणु
       अचिन्हित दीर्घ sig[_NSIG_WORDS];
पूर्ण __new_sigset_t;

/* A SunOS sigstack */
काष्ठा sigstack अणु
	/* XXX 32-bit poपूर्णांकers pinhead XXX */
	अक्षर *the_stack;
	पूर्णांक   cur_status;
पूर्ण;

/* Sigvec flags */
#घोषणा _SV_SSTACK    1u    /* This संकेत handler should use sig-stack */
#घोषणा _SV_INTR      2u    /* Sig वापस should not restart प्रणाली call */
#घोषणा _SV_RESET     4u    /* Set handler to संक_पूर्व upon taken संकेत */
#घोषणा _SV_IGNCHILD  8u    /* Do not send SIGCHLD */

/*
 * sa_flags values: SA_STACK is not currently supported, but will allow the
 * usage of संकेत stacks by using the (now obsolete) sa_restorer field in
 * the sigaction काष्ठाure as a stack poपूर्णांकer. This is now possible due to
 * the changes in संकेत handling. LBT 010493.
 * SA_RESTART flag to get restarting संकेतs (which were the शेष दीर्घ ago)
 */
#घोषणा SA_NOCLDSTOP	_SV_IGNCHILD
#घोषणा SA_STACK	_SV_SSTACK
#घोषणा SA_ONSTACK	_SV_SSTACK
#घोषणा SA_RESTART	_SV_INTR
#घोषणा SA_RESETHAND	_SV_RESET
#घोषणा SA_NODEFER	0x20u
#घोषणा SA_NOCLDWAIT    0x100u
#घोषणा SA_SIGINFO      0x200u

#घोषणा SIG_BLOCK          0x01	/* क्रम blocking संकेतs */
#घोषणा SIG_UNBLOCK        0x02	/* क्रम unblocking संकेतs */
#घोषणा SIG_SETMASK        0x04	/* क्रम setting the संकेत mask */

#घोषणा MINSIGSTKSZ	4096
#घोषणा SIGSTKSZ	16384


#समावेश <यंत्र-generic/संकेत-defs.h>

#अगर_अघोषित __KERNEL__
काष्ठा __new_sigaction अणु
	__sighandler_t		sa_handler;
	अचिन्हित दीर्घ		sa_flags;
	__sigrestore_t		sa_restorer;  /* not used by Linux/SPARC yet */
	__new_sigset_t		sa_mask;
पूर्ण;

काष्ठा __old_sigaction अणु
	__sighandler_t		sa_handler;
	__old_sigset_t		sa_mask;
	अचिन्हित दीर्घ		sa_flags;
	व्योम			(*sa_restorer)(व्योम);  /* not used by Linux/SPARC yet */
पूर्ण;
#पूर्ण_अगर

प्रकार काष्ठा sigaltstack अणु
	व्योम			__user *ss_sp;
	पूर्णांक			ss_flags;
	माप_प्रकार			ss_size;
पूर्ण stack_t;


#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* _UAPI__SPARC_SIGNAL_H */
