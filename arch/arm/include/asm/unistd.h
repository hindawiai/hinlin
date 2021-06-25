<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/unistd.h
 *
 *  Copyright (C) 2001-2005 Russell King
 *
 * Please क्रमward _all_ changes to this file to rmk@arm.linux.org.uk,
 * no matter what the change is.  Thanks!
 */
#अगर_अघोषित __ASM_ARM_UNISTD_H
#घोषणा __ASM_ARM_UNISTD_H

#समावेश <uapi/यंत्र/unistd.h>
#समावेश <यंत्र/unistd-nr.h>

#घोषणा __ARCH_WANT_NEW_STAT
#घोषणा __ARCH_WANT_STAT64
#घोषणा __ARCH_WANT_SYS_GETHOSTNAME
#घोषणा __ARCH_WANT_SYS_PAUSE
#घोषणा __ARCH_WANT_SYS_GETPGRP
#घोषणा __ARCH_WANT_SYS_NICE
#घोषणा __ARCH_WANT_SYS_SIGPENDING
#घोषणा __ARCH_WANT_SYS_SIGPROCMASK
#घोषणा __ARCH_WANT_SYS_OLD_MMAP
#घोषणा __ARCH_WANT_SYS_OLD_SELECT
#घोषणा __ARCH_WANT_SYS_UTIME32

#अगर !defined(CONFIG_AEABI) || defined(CONFIG_OABI_COMPAT)
#घोषणा __ARCH_WANT_SYS_TIME32
#घोषणा __ARCH_WANT_SYS_IPC
#घोषणा __ARCH_WANT_SYS_OLDUMOUNT
#घोषणा __ARCH_WANT_SYS_ALARM
#घोषणा __ARCH_WANT_SYS_OLD_GETRLIMIT
#घोषणा __ARCH_WANT_OLD_READसूची
#घोषणा __ARCH_WANT_SYS_SOCKETCALL
#पूर्ण_अगर
#घोषणा __ARCH_WANT_SYS_FORK
#घोषणा __ARCH_WANT_SYS_VFORK
#घोषणा __ARCH_WANT_SYS_CLONE
#घोषणा __ARCH_WANT_SYS_CLONE3

/*
 * Unimplemented (or alternatively implemented) syscalls
 */
#घोषणा __IGNORE_fadvise64_64

#अगर_घोषित __ARM_EABI__
/*
 * The following syscalls are obsolete and no दीर्घer available क्रम EABI:
 *  __NR_समय
 *  __NR_umount
 *  __NR_sसमय
 *  __NR_alarm
 *  __NR_uसमय
 *  __NR_getrlimit
 *  __NR_select
 *  __NR_सूची_पढ़ो
 *  __NR_mmap
 *  __NR_socketcall
 *  __NR_syscall
 *  __NR_ipc
 */
#घोषणा __IGNORE_getrlimit
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_ARM_UNISTD_H */
