<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SECCOMP_H
#घोषणा _ASM_X86_SECCOMP_H

#समावेश <यंत्र/unistd.h>

#अगर_घोषित CONFIG_X86_32
#घोषणा __NR_seccomp_sigवापस		__NR_sigवापस
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
#समावेश <यंत्र/ia32_unistd.h>
#घोषणा __NR_seccomp_पढ़ो_32		__NR_ia32_पढ़ो
#घोषणा __NR_seccomp_ग_लिखो_32		__NR_ia32_ग_लिखो
#घोषणा __NR_seccomp_निकास_32		__NR_ia32_निकास
#घोषणा __NR_seccomp_sigवापस_32	__NR_ia32_sigवापस
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_64
# define SECCOMP_ARCH_NATIVE		AUDIT_ARCH_X86_64
# define SECCOMP_ARCH_NATIVE_NR		NR_syscalls
# define SECCOMP_ARCH_NATIVE_NAME	"x86_64"
# अगरdef CONFIG_COMPAT
#  define SECCOMP_ARCH_COMPAT		AUDIT_ARCH_I386
#  define SECCOMP_ARCH_COMPAT_NR	IA32_NR_syscalls
#  define SECCOMP_ARCH_COMPAT_NAME	"ia32"
# endअगर
/*
 * x32 will have __X32_SYSCALL_BIT set in syscall number. We करोn't support
 * caching them and they are treated as out of range syscalls, which will
 * always pass through the BPF filter.
 */
#अन्यथा /* !CONFIG_X86_64 */
# define SECCOMP_ARCH_NATIVE		AUDIT_ARCH_I386
# define SECCOMP_ARCH_NATIVE_NR	        NR_syscalls
# define SECCOMP_ARCH_NATIVE_NAME	"ia32"
#पूर्ण_अगर

#समावेश <यंत्र-generic/seccomp.h>

#पूर्ण_अगर /* _ASM_X86_SECCOMP_H */
