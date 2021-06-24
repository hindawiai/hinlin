<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _ASM_SECCOMP_H
#घोषणा _ASM_SECCOMP_H

#समावेश <यंत्र-generic/seccomp.h>

#अगर_घोषित CONFIG_64BIT
# define SECCOMP_ARCH_NATIVE		AUDIT_ARCH_PARISC64
# define SECCOMP_ARCH_NATIVE_NR		NR_syscalls
# define SECCOMP_ARCH_NATIVE_NAME	"parisc64"
# अगरdef CONFIG_COMPAT
#  define SECCOMP_ARCH_COMPAT		AUDIT_ARCH_PARISC
#  define SECCOMP_ARCH_COMPAT_NR	NR_syscalls
#  define SECCOMP_ARCH_COMPAT_NAME	"parisc"
# endअगर
#अन्यथा /* !CONFIG_64BIT */
# define SECCOMP_ARCH_NATIVE		AUDIT_ARCH_PARISC
# define SECCOMP_ARCH_NATIVE_NR		NR_syscalls
# define SECCOMP_ARCH_NATIVE_NAME	"parisc"
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_SECCOMP_H */
