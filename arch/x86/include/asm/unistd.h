<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_UNISTD_H
#घोषणा _ASM_X86_UNISTD_H 1

#समावेश <uapi/यंत्र/unistd.h>


# अगरdef CONFIG_X86_32

#  include <यंत्र/unistd_32.h>
#  define __ARCH_WANT_STAT64
#  define __ARCH_WANT_SYS_IPC
#  define __ARCH_WANT_SYS_OLD_MMAP
#  define __ARCH_WANT_SYS_OLD_SELECT

#  define __NR_ia32_syscall_max __NR_syscall_max

# अन्यथा

#  include <यंत्र/unistd_64.h>
#  include <यंत्र/unistd_64_x32.h>
#  include <यंत्र/unistd_32_ia32.h>
#  define __ARCH_WANT_SYS_TIME
#  define __ARCH_WANT_SYS_UTIME
#  define __ARCH_WANT_COMPAT_SYS_PREADV64
#  define __ARCH_WANT_COMPAT_SYS_PWRITEV64
#  define __ARCH_WANT_COMPAT_SYS_PREADV64V2
#  define __ARCH_WANT_COMPAT_SYS_PWRITEV64V2

# endअगर

# define NR_syscalls (__NR_syscall_max + 1)
# define X32_NR_syscalls (__NR_x32_syscall_max + 1)
# define IA32_NR_syscalls (__NR_ia32_syscall_max + 1)

# define __ARCH_WANT_NEW_STAT
# define __ARCH_WANT_OLD_READसूची
# define __ARCH_WANT_OLD_STAT
# define __ARCH_WANT_SYS_ALARM
# define __ARCH_WANT_SYS_FADVISE64
# define __ARCH_WANT_SYS_GETHOSTNAME
# define __ARCH_WANT_SYS_GETPGRP
# define __ARCH_WANT_SYS_NICE
# define __ARCH_WANT_SYS_OLDUMOUNT
# define __ARCH_WANT_SYS_OLD_GETRLIMIT
# define __ARCH_WANT_SYS_OLD_UNAME
# define __ARCH_WANT_SYS_PAUSE
# define __ARCH_WANT_SYS_SIGNAL
# define __ARCH_WANT_SYS_SIGPENDING
# define __ARCH_WANT_SYS_SIGPROCMASK
# define __ARCH_WANT_SYS_SOCKETCALL
# define __ARCH_WANT_SYS_TIME32
# define __ARCH_WANT_SYS_UTIME32
# define __ARCH_WANT_SYS_WAITPID
# define __ARCH_WANT_SYS_FORK
# define __ARCH_WANT_SYS_VFORK
# define __ARCH_WANT_SYS_CLONE
# define __ARCH_WANT_SYS_CLONE3

#पूर्ण_अगर /* _ASM_X86_UNISTD_H */
