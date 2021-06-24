<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 96, 97, 98, 99, 2000 by Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 *
 * Changed प्रणाली calls macros _syscall5 - _syscall7 to push args 5 to 7 onto
 * the stack. Robin Farine क्रम ACN S.A, Copyright (C) 1996 by ACN S.A
 */
#अगर_अघोषित _ASM_UNISTD_H
#घोषणा _ASM_UNISTD_H

#समावेश <uapi/यंत्र/unistd.h>
#समावेश <यंत्र/unistd_nr_n32.h>
#समावेश <यंत्र/unistd_nr_n64.h>
#समावेश <यंत्र/unistd_nr_o32.h>

#अगर_घोषित CONFIG_MIPS32_N32
#घोषणा NR_syscalls  (__NR_N32_Linux + __NR_N32_Linux_syscalls)
#या_अगर defined(CONFIG_64BIT)
#घोषणा NR_syscalls  (__NR_64_Linux + __NR_64_Linux_syscalls)
#अन्यथा
#घोषणा NR_syscalls  (__NR_O32_Linux + __NR_O32_Linux_syscalls)
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#घोषणा __ARCH_WANT_NEW_STAT
#घोषणा __ARCH_WANT_OLD_READसूची
#घोषणा __ARCH_WANT_SYS_ALARM
#घोषणा __ARCH_WANT_SYS_GETHOSTNAME
#घोषणा __ARCH_WANT_SYS_IPC
#घोषणा __ARCH_WANT_SYS_PAUSE
#घोषणा __ARCH_WANT_SYS_UTIME
#घोषणा __ARCH_WANT_SYS_UTIME32
#घोषणा __ARCH_WANT_SYS_WAITPID
#घोषणा __ARCH_WANT_SYS_SOCKETCALL
#घोषणा __ARCH_WANT_SYS_GETPGRP
#घोषणा __ARCH_WANT_SYS_NICE
#घोषणा __ARCH_WANT_SYS_OLD_UNAME
#घोषणा __ARCH_WANT_SYS_OLDUMOUNT
#घोषणा __ARCH_WANT_SYS_SIGPENDING
#घोषणा __ARCH_WANT_SYS_SIGPROCMASK
# अगरdef CONFIG_32BIT
#  define __ARCH_WANT_STAT64
#  define __ARCH_WANT_SYS_TIME32
# endअगर
# अगरdef CONFIG_MIPS32_O32
#  define __ARCH_WANT_SYS_TIME32
# endअगर
#घोषणा __ARCH_WANT_SYS_FORK
#घोषणा __ARCH_WANT_SYS_CLONE
#घोषणा __ARCH_WANT_SYS_CLONE3

/* whitelists क्रम checksyscalls */
#घोषणा __IGNORE_fadvise64_64

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_UNISTD_H */
