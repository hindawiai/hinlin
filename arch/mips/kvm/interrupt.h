<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * KVM/MIPS: Interrupts
 * Copyright (C) 2012  MIPS Technologies, Inc.  All rights reserved.
 * Authors: Sanjay Lal <sanjayl@kymasys.com>
 */

/*
 * MIPS Exception Priorities, exceptions (including पूर्णांकerrupts) are queued up
 * क्रम the guest in the order specअगरied by their priorities
 */

#घोषणा MIPS_EXC_RESET              0
#घोषणा MIPS_EXC_SRESET             1
#घोषणा MIPS_EXC_DEBUG_ST           2
#घोषणा MIPS_EXC_DEBUG              3
#घोषणा MIPS_EXC_DDB                4
#घोषणा MIPS_EXC_NMI                5
#घोषणा MIPS_EXC_MCHK               6
#घोषणा MIPS_EXC_INT_TIMER          7
#घोषणा MIPS_EXC_INT_IO_1           8
#घोषणा MIPS_EXC_INT_IO_2           9
#घोषणा MIPS_EXC_EXECUTE            10
#घोषणा MIPS_EXC_INT_IPI_1          11
#घोषणा MIPS_EXC_INT_IPI_2          12
#घोषणा MIPS_EXC_MAX                13
/* XXXSL More to follow */

#घोषणा C_TI        (_ULCAST_(1) << 30)

बाह्य u32 *kvm_priority_to_irq;
u32 kvm_irq_to_priority(u32 irq);

पूर्णांक kvm_mips_pending_समयr(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_mips_deliver_पूर्णांकerrupts(काष्ठा kvm_vcpu *vcpu, u32 cause);
