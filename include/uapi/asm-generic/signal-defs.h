<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_GENERIC_SIGNAL_DEFS_H
#घोषणा __ASM_GENERIC_SIGNAL_DEFS_H

#समावेश <linux/compiler.h>

/*
 * SA_FLAGS values:
 *
 * SA_NOCLDSTOP flag to turn off SIGCHLD when children stop.
 * SA_NOCLDWAIT flag on SIGCHLD to inhibit zombies.
 * SA_SIGINFO delivers the संकेत with SIGINFO काष्ठाs.
 * SA_ONSTACK indicates that a रेजिस्टरed stack_t will be used.
 * SA_RESTART flag to get restarting संकेतs (which were the शेष दीर्घ ago)
 * SA_NODEFER prevents the current संकेत from being masked in the handler.
 * SA_RESETHAND clears the handler when the संकेत is delivered.
 * SA_UNSUPPORTED is a flag bit that will never be supported. Kernels from
 * beक्रमe the पूर्णांकroduction of SA_UNSUPPORTED did not clear unknown bits from
 * sa_flags when पढ़ो using the oldact argument to sigaction and rt_sigaction,
 * so this bit allows flag bit support to be detected from userspace जबतक
 * allowing an old kernel to be distinguished from a kernel that supports every
 * flag bit.
 * SA_EXPOSE_TAGBITS exposes an architecture-defined set of tag bits in
 * siginfo.si_addr.
 *
 * SA_ONESHOT and SA_NOMASK are the historical Linux names क्रम the Single
 * Unix names RESETHAND and NODEFER respectively.
 */
#अगर_अघोषित SA_NOCLDSTOP
#घोषणा SA_NOCLDSTOP	0x00000001
#पूर्ण_अगर
#अगर_अघोषित SA_NOCLDWAIT
#घोषणा SA_NOCLDWAIT	0x00000002
#पूर्ण_अगर
#अगर_अघोषित SA_SIGINFO
#घोषणा SA_SIGINFO	0x00000004
#पूर्ण_अगर
/* 0x00000008 used on alpha, mips, parisc */
/* 0x00000010 used on alpha, parisc */
/* 0x00000020 used on alpha, parisc, sparc */
/* 0x00000040 used on alpha, parisc */
/* 0x00000080 used on parisc */
/* 0x00000100 used on sparc */
/* 0x00000200 used on sparc */
#घोषणा SA_UNSUPPORTED	0x00000400
#घोषणा SA_EXPOSE_TAGBITS	0x00000800
/* 0x00010000 used on mips */
/* 0x01000000 used on x86 */
/* 0x02000000 used on x86 */
/*
 * New architectures should not define the obsolete
 *	SA_RESTORER	0x04000000
 */
#अगर_अघोषित SA_ONSTACK
#घोषणा SA_ONSTACK	0x08000000
#पूर्ण_अगर
#अगर_अघोषित SA_RESTART
#घोषणा SA_RESTART	0x10000000
#पूर्ण_अगर
#अगर_अघोषित SA_NODEFER
#घोषणा SA_NODEFER	0x40000000
#पूर्ण_अगर
#अगर_अघोषित SA_RESETHAND
#घोषणा SA_RESETHAND	0x80000000
#पूर्ण_अगर

#घोषणा SA_NOMASK	SA_NODEFER
#घोषणा SA_ONESHOT	SA_RESETHAND

#अगर_अघोषित SIG_BLOCK
#घोषणा SIG_BLOCK          0	/* क्रम blocking संकेतs */
#पूर्ण_अगर
#अगर_अघोषित SIG_UNBLOCK
#घोषणा SIG_UNBLOCK        1	/* क्रम unblocking संकेतs */
#पूर्ण_अगर
#अगर_अघोषित SIG_SETMASK
#घोषणा SIG_SETMASK        2	/* क्रम setting the संकेत mask */
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
प्रकार व्योम __संकेतfn_t(पूर्णांक);
प्रकार __संकेतfn_t __user *__sighandler_t;

प्रकार व्योम __restorefn_t(व्योम);
प्रकार __restorefn_t __user *__sigrestore_t;

#घोषणा संक_पूर्व	((__क्रमce __sighandler_t)0)	/* शेष संकेत handling */
#घोषणा संक_छोड़ो	((__क्रमce __sighandler_t)1)	/* ignore संकेत */
#घोषणा संक_त्रुटि	((__क्रमce __sighandler_t)-1)	/* error वापस from संकेत */
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_GENERIC_SIGNAL_DEFS_H */
