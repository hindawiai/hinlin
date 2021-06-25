<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_SECCOMP_H
#घोषणा _ASM_S390_SECCOMP_H

#समावेश <linux/unistd.h>

#घोषणा __NR_seccomp_पढ़ो	__NR_पढ़ो
#घोषणा __NR_seccomp_ग_लिखो	__NR_ग_लिखो
#घोषणा __NR_seccomp_निकास	__NR_निकास
#घोषणा __NR_seccomp_sigवापस	__NR_sigवापस

#घोषणा __NR_seccomp_पढ़ो_32	__NR_पढ़ो
#घोषणा __NR_seccomp_ग_लिखो_32	__NR_ग_लिखो
#घोषणा __NR_seccomp_निकास_32	__NR_निकास
#घोषणा __NR_seccomp_sigवापस_32 __NR_sigवापस

#समावेश <यंत्र-generic/seccomp.h>

#घोषणा SECCOMP_ARCH_NATIVE		AUDIT_ARCH_S390X
#घोषणा SECCOMP_ARCH_NATIVE_NR		NR_syscalls
#घोषणा SECCOMP_ARCH_NATIVE_NAME	"s390x"
#अगर_घोषित CONFIG_COMPAT
# define SECCOMP_ARCH_COMPAT		AUDIT_ARCH_S390
# define SECCOMP_ARCH_COMPAT_NR		NR_syscalls
# define SECCOMP_ARCH_COMPAT_NAME	"s390"
#पूर्ण_अगर

#पूर्ण_अगर	/* _ASM_S390_SECCOMP_H */
