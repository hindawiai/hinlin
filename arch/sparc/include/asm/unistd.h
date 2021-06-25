<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * System calls under the Sparc.
 *
 * Don't be scared by the ugly clobbers, it is the only way I can
 * think of right now to क्रमce the arguments पूर्णांकo fixed रेजिस्टरs
 * beक्रमe the trap पूर्णांकo the प्रणाली call with gcc 'asm' statements.
 *
 * Copyright (C) 1995, 2007 David S. Miller (davem@davemloft.net)
 *
 * SunOS compatibility based upon preliminary work which is:
 *
 * Copyright (C) 1995 Adrian M. Rodriguez (adrian@remus.rutgers.edu)
 */
#अगर_अघोषित _SPARC_UNISTD_H
#घोषणा _SPARC_UNISTD_H

#समावेश <uapi/यंत्र/unistd.h>

#घोषणा NR_syscalls	__NR_syscalls

#अगर_घोषित __32bit_syscall_numbers__
#अन्यथा
#घोषणा __NR_समय		231 /* Linux sparc32                               */
#पूर्ण_अगर
#घोषणा __ARCH_WANT_NEW_STAT
#घोषणा __ARCH_WANT_OLD_READसूची
#घोषणा __ARCH_WANT_STAT64
#घोषणा __ARCH_WANT_SYS_ALARM
#घोषणा __ARCH_WANT_SYS_GETHOSTNAME
#घोषणा __ARCH_WANT_SYS_PAUSE
#घोषणा __ARCH_WANT_SYS_SIGNAL
#घोषणा __ARCH_WANT_SYS_TIME32
#घोषणा __ARCH_WANT_SYS_UTIME32
#घोषणा __ARCH_WANT_SYS_WAITPID
#घोषणा __ARCH_WANT_SYS_SOCKETCALL
#घोषणा __ARCH_WANT_SYS_FADVISE64
#घोषणा __ARCH_WANT_SYS_GETPGRP
#घोषणा __ARCH_WANT_SYS_NICE
#घोषणा __ARCH_WANT_SYS_OLDUMOUNT
#घोषणा __ARCH_WANT_SYS_SIGPENDING
#घोषणा __ARCH_WANT_SYS_SIGPROCMASK
#अगर_घोषित __32bit_syscall_numbers__
#घोषणा __ARCH_WANT_SYS_IPC
#अन्यथा
#घोषणा __ARCH_WANT_SYS_TIME
#घोषणा __ARCH_WANT_SYS_UTIME
#घोषणा __ARCH_WANT_COMPAT_SYS_SENDखाता
#पूर्ण_अगर

#अगर_घोषित __32bit_syscall_numbers__
/* Sparc 32-bit only has the "setresuid32", "getresuid32" variants,
 * it never had the plain ones and there is no value to adding those
 * old versions पूर्णांकo the syscall table.
 */
#घोषणा __IGNORE_setresuid
#घोषणा __IGNORE_getresuid
#घोषणा __IGNORE_setresgid
#घोषणा __IGNORE_getresgid
#पूर्ण_अगर

#पूर्ण_अगर /* _SPARC_UNISTD_H */
