<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Modअगरied 1998-2001, 2003
 *	David Mosberger-Tang <davidm@hpl.hp.com>, Hewlett-Packard Co
 *
 * Unक्रमtunately, this file is being included by bits/संकेत.स in
 * glibc-2.x.  Hence the #अगर_घोषित __KERNEL__ ugliness.
 */
#अगर_अघोषित _UAPI_ASM_IA64_SIGNAL_H
#घोषणा _UAPI_ASM_IA64_SIGNAL_H


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
/* संकेत 31 is no दीर्घer "unused", but the SIGUNUSED macro reमुख्यs क्रम backwards compatibility */
#घोषणा	SIGUNUSED	31

/* These should not be considered स्थिरants from userland.  */
#घोषणा SIGRTMIN	32
#घोषणा SIGRTMAX	_NSIG

#घोषणा SA_RESTORER	0x04000000

/*
 * The minimum stack size needs to be fairly large because we want to
 * be sure that an app compiled क्रम today's CPUs will जारी to run
 * on all future CPU models.  The CPU model matters because the संकेत
 * frame needs to have space क्रम the complete machine state, including
 * all physical stacked रेजिस्टरs.  The number of physical stacked
 * रेजिस्टरs is CPU model dependent, but given that the width of
 * ar.rsc.loadrs is 14 bits, we can assume that they'll never take up
 * more than 16KB of space.
 */
#अगर 1
  /*
   * This is a stupid typo: the value was _meant_ to be 131072 (0x20000), but I typed it
   * in wrong. ;-(  To preserve backwards compatibility, we leave the kernel at the
   * incorrect value and fix libc only.
   */
# define MINSIGSTKSZ	131027	/* min. stack size क्रम sigaltstack() */
#अन्यथा
# define MINSIGSTKSZ	131072	/* min. stack size क्रम sigaltstack() */
#पूर्ण_अगर
#घोषणा SIGSTKSZ	262144	/* शेष stack size क्रम sigaltstack() */


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


# endअगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _UAPI_ASM_IA64_SIGNAL_H */
