<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * KVM/MIPS: Interrupt delivery
 *
 * Copyright (C) 2012  MIPS Technologies, Inc.  All rights reserved.
 * Authors: Sanjay Lal <sanjayl@kymasys.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश <linux/kvm_host.h>

#समावेश "interrupt.h"

व्योम kvm_mips_deliver_पूर्णांकerrupts(काष्ठा kvm_vcpu *vcpu, u32 cause)
अणु
	अचिन्हित दीर्घ *pending = &vcpu->arch.pending_exceptions;
	अचिन्हित दीर्घ *pending_clr = &vcpu->arch.pending_exceptions_clr;
	अचिन्हित पूर्णांक priority;

	अगर (!(*pending) && !(*pending_clr))
		वापस;

	priority = __ffs(*pending_clr);
	जबतक (priority <= MIPS_EXC_MAX) अणु
		kvm_mips_callbacks->irq_clear(vcpu, priority, cause);

		priority = find_next_bit(pending_clr,
					 BITS_PER_BYTE * माप(*pending_clr),
					 priority + 1);
	पूर्ण

	priority = __ffs(*pending);
	जबतक (priority <= MIPS_EXC_MAX) अणु
		kvm_mips_callbacks->irq_deliver(vcpu, priority, cause);

		priority = find_next_bit(pending,
					 BITS_PER_BYTE * माप(*pending),
					 priority + 1);
	पूर्ण

पूर्ण

पूर्णांक kvm_mips_pending_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस test_bit(MIPS_EXC_INT_TIMER, &vcpu->arch.pending_exceptions);
पूर्ण
