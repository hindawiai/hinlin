<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_SECCOMP_H
#घोषणा _ASM_SECCOMP_H

#समावेश <यंत्र/unistd.h>

#समावेश <यंत्र-generic/seccomp.h>

#अगर_घोषित CONFIG_64BIT
# define SECCOMP_ARCH_NATIVE		AUDIT_ARCH_RISCV64
# define SECCOMP_ARCH_NATIVE_NR		NR_syscalls
# define SECCOMP_ARCH_NATIVE_NAME	"riscv64"
#अन्यथा /* !CONFIG_64BIT */
# define SECCOMP_ARCH_NATIVE		AUDIT_ARCH_RISCV32
# define SECCOMP_ARCH_NATIVE_NR		NR_syscalls
# define SECCOMP_ARCH_NATIVE_NAME	"riscv32"
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_SECCOMP_H */
