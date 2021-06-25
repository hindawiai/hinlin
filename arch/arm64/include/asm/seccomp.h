<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm64/include/यंत्र/seccomp.h
 *
 * Copyright (C) 2014 Linaro Limited
 * Author: AKASHI Takahiro <takahiro.akashi@linaro.org>
 */
#अगर_अघोषित _ASM_SECCOMP_H
#घोषणा _ASM_SECCOMP_H

#समावेश <यंत्र/unistd.h>

#अगर_घोषित CONFIG_COMPAT
#घोषणा __NR_seccomp_पढ़ो_32		__NR_compat_पढ़ो
#घोषणा __NR_seccomp_ग_लिखो_32		__NR_compat_ग_लिखो
#घोषणा __NR_seccomp_निकास_32		__NR_compat_निकास
#घोषणा __NR_seccomp_sigवापस_32	__NR_compat_rt_sigवापस
#पूर्ण_अगर /* CONFIG_COMPAT */

#समावेश <यंत्र-generic/seccomp.h>

#घोषणा SECCOMP_ARCH_NATIVE		AUDIT_ARCH_AARCH64
#घोषणा SECCOMP_ARCH_NATIVE_NR		NR_syscalls
#घोषणा SECCOMP_ARCH_NATIVE_NAME	"aarch64"
#अगर_घोषित CONFIG_COMPAT
# define SECCOMP_ARCH_COMPAT		AUDIT_ARCH_ARM
# define SECCOMP_ARCH_COMPAT_NR	__NR_compat_syscalls
# define SECCOMP_ARCH_COMPAT_NAME	"arm"
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_SECCOMP_H */
