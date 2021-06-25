<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_SECCOMP_H
#घोषणा _ASM_POWERPC_SECCOMP_H

#समावेश <linux/unistd.h>

#घोषणा __NR_seccomp_sigवापस_32 __NR_sigवापस

#समावेश <यंत्र-generic/seccomp.h>

#अगर_घोषित __LITTLE_ENDIAN__
#घोषणा __SECCOMP_ARCH_LE		__AUDIT_ARCH_LE
#घोषणा __SECCOMP_ARCH_LE_NAME		"le"
#अन्यथा
#घोषणा __SECCOMP_ARCH_LE		0
#घोषणा __SECCOMP_ARCH_LE_NAME
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
# define SECCOMP_ARCH_NATIVE		(AUDIT_ARCH_PPC64 | __SECCOMP_ARCH_LE)
# define SECCOMP_ARCH_NATIVE_NR		NR_syscalls
# define SECCOMP_ARCH_NATIVE_NAME	"ppc64" __SECCOMP_ARCH_LE_NAME
# अगरdef CONFIG_COMPAT
#  define SECCOMP_ARCH_COMPAT		(AUDIT_ARCH_PPC | __SECCOMP_ARCH_LE)
#  define SECCOMP_ARCH_COMPAT_NR	NR_syscalls
#  define SECCOMP_ARCH_COMPAT_NAME	"ppc" __SECCOMP_ARCH_LE_NAME
# endअगर
#अन्यथा /* !CONFIG_PPC64 */
# define SECCOMP_ARCH_NATIVE		(AUDIT_ARCH_PPC | __SECCOMP_ARCH_LE)
# define SECCOMP_ARCH_NATIVE_NR		NR_syscalls
# define SECCOMP_ARCH_NATIVE_NAME	"ppc" __SECCOMP_ARCH_LE_NAME
#पूर्ण_अगर

#पूर्ण_अगर	/* _ASM_POWERPC_SECCOMP_H */
