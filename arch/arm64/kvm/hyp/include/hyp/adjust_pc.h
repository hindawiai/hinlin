<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Guest PC manipulation helpers
 *
 * Copyright (C) 2012,2013 - ARM Ltd
 * Copyright (C) 2020 - Google LLC
 * Author: Marc Zyngier <maz@kernel.org>
 */

#अगर_अघोषित __ARM64_KVM_HYP_ADJUST_PC_H__
#घोषणा __ARM64_KVM_HYP_ADJUST_PC_H__

#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_host.h>

अटल अंतरभूत व्योम kvm_skip_instr(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu_mode_is_32bit(vcpu)) अणु
		kvm_skip_instr32(vcpu);
	पूर्ण अन्यथा अणु
		*vcpu_pc(vcpu) += 4;
		*vcpu_cpsr(vcpu) &= ~PSR_BTYPE_MASK;
	पूर्ण

	/* advance the singlestep state machine */
	*vcpu_cpsr(vcpu) &= ~DBG_SPSR_SS;
पूर्ण

/*
 * Skip an inकाष्ठाion which has been emulated at hyp जबतक most guest sysregs
 * are live.
 */
अटल अंतरभूत व्योम __kvm_skip_instr(काष्ठा kvm_vcpu *vcpu)
अणु
	*vcpu_pc(vcpu) = पढ़ो_sysreg_el2(SYS_ELR);
	vcpu_gp_regs(vcpu)->pstate = पढ़ो_sysreg_el2(SYS_SPSR);

	kvm_skip_instr(vcpu);

	ग_लिखो_sysreg_el2(vcpu_gp_regs(vcpu)->pstate, SYS_SPSR);
	ग_लिखो_sysreg_el2(*vcpu_pc(vcpu), SYS_ELR);
पूर्ण

/*
 * Skip an inकाष्ठाion जबतक host sysregs are live.
 * Assumes host is always 64-bit.
 */
अटल अंतरभूत व्योम kvm_skip_host_instr(व्योम)
अणु
	ग_लिखो_sysreg_el2(पढ़ो_sysreg_el2(SYS_ELR) + 4, SYS_ELR);
पूर्ण

#पूर्ण_अगर
