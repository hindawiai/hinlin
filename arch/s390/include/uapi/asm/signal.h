<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  S390 version
 *
 *  Derived from "include/asm-i386/signal.h"
 */

#अगर_अघोषित _UAPI_ASMS390_SIGNAL_H
#घोषणा _UAPI_ASMS390_SIGNAL_H

#समावेश <linux/types.h>
#समावेश <linux/समय.स>

/* Aव्योम too many header ordering problems.  */
काष्ठा siginfo;
काष्ठा pt_regs;

#अगर_अघोषित __KERNEL__
/* Here we must cater to libcs that poke about in kernel headers.  */

#घोषणा NSIG            32
प्रकार अचिन्हित दीर्घ sigset_t;

#पूर्ण_अगर /* __KERNEL__ */

#घोषणा SIGHUP           1
#घोषणा संक_विघ्न           2
#घोषणा SIGQUIT          3
#घोषणा संक_अवैध           4
#घोषणा SIGTRAP          5
#घोषणा SIGABRT          6
#घोषणा SIGIOT           6
#घोषणा SIGBUS           7
#घोषणा संक_भ_त्रुटि           8
#घोषणा SIGKILL          9
#घोषणा SIGUSR1         10
#घोषणा संक_अंश         11
#घोषणा SIGUSR2         12
#घोषणा SIGPIPE         13
#घोषणा SIGALRM         14
#घोषणा संक_इति         15
#घोषणा SIGSTKFLT       16
#घोषणा SIGCHLD         17
#घोषणा SIGCONT         18
#घोषणा SIGSTOP         19
#घोषणा SIGTSTP         20
#घोषणा SIGTTIN         21
#घोषणा SIGTTOU         22
#घोषणा SIGURG          23
#घोषणा SIGXCPU         24
#घोषणा SIGXFSZ         25
#घोषणा SIGVTALRM       26
#घोषणा SIGPROF         27
#घोषणा SIGWINCH        28
#घोषणा SIGIO           29
#घोषणा SIGPOLL         SIGIO
/*
#घोषणा SIGLOST         29
*/
#घोषणा SIGPWR          30
#घोषणा SIGSYS		31
#घोषणा SIGUNUSED       31

/* These should not be considered स्थिरants from userland.  */
#घोषणा SIGRTMIN        32
#घोषणा SIGRTMAX        _NSIG

#घोषणा SA_RESTORER     0x04000000

#घोषणा MINSIGSTKSZ     2048
#घोषणा SIGSTKSZ        8192

#समावेश <यंत्र-generic/संकेत-defs.h>

#अगर_अघोषित __KERNEL__

/*
 * There are two प्रणाली calls in regard to sigaction, sys_rt_sigaction
 * and sys_sigaction. Internally the kernel uses the काष्ठा old_sigaction
 * क्रम the older sys_sigaction प्रणाली call, and the kernel version of the
 * काष्ठा sigaction क्रम the newer sys_rt_sigaction.
 *
 * The uapi definition क्रम काष्ठा sigaction has made a strange distinction
 * between 31-bit and 64-bit in the past. For 64-bit the uapi काष्ठाure
 * looks like the kernel काष्ठा sigaction, but क्रम 31-bit it used to
 * look like the kernel काष्ठा old_sigaction. That practically made the
 * काष्ठाure unusable क्रम either प्रणाली call. To get around this problem
 * the glibc always had its own definitions क्रम the sigaction काष्ठाures.
 *
 * The current काष्ठा sigaction uapi definition below is suitable क्रम the
 * sys_rt_sigaction प्रणाली call only.
 */
काष्ठा sigaction अणु
        जोड़ अणु
          __sighandler_t _sa_handler;
          व्योम (*_sa_sigaction)(पूर्णांक, काष्ठा siginfo *, व्योम *);
        पूर्ण _u;
        अचिन्हित दीर्घ sa_flags;
        व्योम (*sa_restorer)(व्योम);
	sigset_t sa_mask;
पूर्ण;

#घोषणा sa_handler      _u._sa_handler
#घोषणा sa_sigaction    _u._sa_sigaction

#पूर्ण_अगर /* __KERNEL__ */

प्रकार काष्ठा sigaltstack अणु
        व्योम __user *ss_sp;
        पूर्णांक ss_flags;
        माप_प्रकार ss_size;
पूर्ण stack_t;


#पूर्ण_अगर /* _UAPI_ASMS390_SIGNAL_H */
