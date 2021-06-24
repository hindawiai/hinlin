<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_KVM_PARA_H
#घोषणा _UAPI__LINUX_KVM_PARA_H

/*
 * This header file provides a method क्रम making a hypercall to the host
 * Architectures should define:
 * - kvm_hypercall0, kvm_hypercall1...
 * - kvm_arch_para_features
 * - kvm_para_available
 */

/* Return values क्रम hypercalls */
#घोषणा KVM_ENOSYS		1000
#घोषणा KVM_EFAULT		EFAULT
#घोषणा KVM_EINVAL		EINVAL
#घोषणा KVM_E2BIG		E2BIG
#घोषणा KVM_EPERM		EPERM
#घोषणा KVM_EOPNOTSUPP		95

#घोषणा KVM_HC_VAPIC_POLL_IRQ		1
#घोषणा KVM_HC_MMU_OP			2
#घोषणा KVM_HC_FEATURES			3
#घोषणा KVM_HC_PPC_MAP_MAGIC_PAGE	4
#घोषणा KVM_HC_KICK_CPU			5
#घोषणा KVM_HC_MIPS_GET_CLOCK_FREQ	6
#घोषणा KVM_HC_MIPS_EXIT_VM		7
#घोषणा KVM_HC_MIPS_CONSOLE_OUTPUT	8
#घोषणा KVM_HC_CLOCK_PAIRING		9
#घोषणा KVM_HC_SEND_IPI		10
#घोषणा KVM_HC_SCHED_YIELD		11

/*
 * hypercalls use architecture specअगरic
 */
#समावेश <यंत्र/kvm_para.h>

#पूर्ण_अगर /* _UAPI__LINUX_KVM_PARA_H */
