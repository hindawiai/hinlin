<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SECCOMP_H

#समावेश <linux/unistd.h>

#घोषणा __NR_seccomp_पढ़ो __NR_पढ़ो
#घोषणा __NR_seccomp_ग_लिखो __NR_ग_लिखो
#घोषणा __NR_seccomp_निकास __NR_निकास
#घोषणा __NR_seccomp_sigवापस __NR_rt_sigवापस

#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
#घोषणा __SECCOMP_ARCH_LE		__AUDIT_ARCH_LE
#अन्यथा
#घोषणा __SECCOMP_ARCH_LE		0
#पूर्ण_अगर

#घोषणा SECCOMP_ARCH_NATIVE		(AUDIT_ARCH_SH | __SECCOMP_ARCH_LE)
#घोषणा SECCOMP_ARCH_NATIVE_NR		NR_syscalls
#घोषणा SECCOMP_ARCH_NATIVE_NAME	"sh"

#पूर्ण_अगर /* __ASM_SECCOMP_H */
