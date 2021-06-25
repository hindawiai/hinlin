<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Fault injection क्रम both 32 and 64bit guests.
 *
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Based on arch/arm/kvm/emulate.c
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/esr.h>

अटल व्योम inject_abt64(काष्ठा kvm_vcpu *vcpu, bool is_iabt, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ cpsr = *vcpu_cpsr(vcpu);
	bool is_aarch32 = vcpu_mode_is_32bit(vcpu);
	u32 esr = 0;

	vcpu->arch.flags |= (KVM_ARM64_EXCEPT_AA64_EL1		|
			     KVM_ARM64_EXCEPT_AA64_ELx_SYNC	|
			     KVM_ARM64_PENDING_EXCEPTION);

	vcpu_ग_लिखो_sys_reg(vcpu, addr, FAR_EL1);

	/*
	 * Build an अणुi,dपूर्णपात, depending on the level and the
	 * inकाष्ठाion set. Report an बाह्यal synchronous पात.
	 */
	अगर (kvm_vcpu_trap_il_is32bit(vcpu))
		esr |= ESR_ELx_IL;

	/*
	 * Here, the guest runs in AArch64 mode when in EL1. If we get
	 * an AArch32 fault, it means we managed to trap an EL0 fault.
	 */
	अगर (is_aarch32 || (cpsr & PSR_MODE_MASK) == PSR_MODE_EL0t)
		esr |= (ESR_ELx_EC_IABT_LOW << ESR_ELx_EC_SHIFT);
	अन्यथा
		esr |= (ESR_ELx_EC_IABT_CUR << ESR_ELx_EC_SHIFT);

	अगर (!is_iabt)
		esr |= ESR_ELx_EC_DABT_LOW << ESR_ELx_EC_SHIFT;

	vcpu_ग_लिखो_sys_reg(vcpu, esr | ESR_ELx_FSC_EXTABT, ESR_EL1);
पूर्ण

अटल व्योम inject_undef64(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 esr = (ESR_ELx_EC_UNKNOWN << ESR_ELx_EC_SHIFT);

	vcpu->arch.flags |= (KVM_ARM64_EXCEPT_AA64_EL1		|
			     KVM_ARM64_EXCEPT_AA64_ELx_SYNC	|
			     KVM_ARM64_PENDING_EXCEPTION);

	/*
	 * Build an unknown exception, depending on the inकाष्ठाion
	 * set.
	 */
	अगर (kvm_vcpu_trap_il_is32bit(vcpu))
		esr |= ESR_ELx_IL;

	vcpu_ग_लिखो_sys_reg(vcpu, esr, ESR_EL1);
पूर्ण

#घोषणा DFSR_FSC_EXTABT_LPAE	0x10
#घोषणा DFSR_FSC_EXTABT_nLPAE	0x08
#घोषणा DFSR_LPAE		BIT(9)
#घोषणा TTBCR_EAE		BIT(31)

अटल व्योम inject_undef32(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.flags |= (KVM_ARM64_EXCEPT_AA32_UND |
			     KVM_ARM64_PENDING_EXCEPTION);
पूर्ण

/*
 * Modelled after TakeDataAbortException() and TakePrefetchAbortException
 * pseuकरोcode.
 */
अटल व्योम inject_abt32(काष्ठा kvm_vcpu *vcpu, bool is_pabt, u32 addr)
अणु
	u64 far;
	u32 fsr;

	/* Give the guest an IMPLEMENTATION DEFINED exception */
	अगर (vcpu_पढ़ो_sys_reg(vcpu, TCR_EL1) & TTBCR_EAE) अणु
		fsr = DFSR_LPAE | DFSR_FSC_EXTABT_LPAE;
	पूर्ण अन्यथा अणु
		/* no need to shuffle FS[4] पूर्णांकo DFSR[10] as its 0 */
		fsr = DFSR_FSC_EXTABT_nLPAE;
	पूर्ण

	far = vcpu_पढ़ो_sys_reg(vcpu, FAR_EL1);

	अगर (is_pabt) अणु
		vcpu->arch.flags |= (KVM_ARM64_EXCEPT_AA32_IABT |
				     KVM_ARM64_PENDING_EXCEPTION);
		far &= GENMASK(31, 0);
		far |= (u64)addr << 32;
		vcpu_ग_लिखो_sys_reg(vcpu, fsr, IFSR32_EL2);
	पूर्ण अन्यथा अणु /* !iabt */
		vcpu->arch.flags |= (KVM_ARM64_EXCEPT_AA32_DABT |
				     KVM_ARM64_PENDING_EXCEPTION);
		far &= GENMASK(63, 32);
		far |= addr;
		vcpu_ग_लिखो_sys_reg(vcpu, fsr, ESR_EL1);
	पूर्ण

	vcpu_ग_लिखो_sys_reg(vcpu, far, FAR_EL1);
पूर्ण

/**
 * kvm_inject_dabt - inject a data पात पूर्णांकo the guest
 * @vcpu: The VCPU to receive the data पात
 * @addr: The address to report in the DFAR
 *
 * It is assumed that this code is called from the VCPU thपढ़ो and that the
 * VCPU thereक्रमe is not currently executing guest code.
 */
व्योम kvm_inject_dabt(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ addr)
अणु
	अगर (vcpu_el1_is_32bit(vcpu))
		inject_abt32(vcpu, false, addr);
	अन्यथा
		inject_abt64(vcpu, false, addr);
पूर्ण

/**
 * kvm_inject_pabt - inject a prefetch पात पूर्णांकo the guest
 * @vcpu: The VCPU to receive the prefetch पात
 * @addr: The address to report in the DFAR
 *
 * It is assumed that this code is called from the VCPU thपढ़ो and that the
 * VCPU thereक्रमe is not currently executing guest code.
 */
व्योम kvm_inject_pabt(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ addr)
अणु
	अगर (vcpu_el1_is_32bit(vcpu))
		inject_abt32(vcpu, true, addr);
	अन्यथा
		inject_abt64(vcpu, true, addr);
पूर्ण

/**
 * kvm_inject_undefined - inject an undefined inकाष्ठाion पूर्णांकo the guest
 * @vcpu: The vCPU in which to inject the exception
 *
 * It is assumed that this code is called from the VCPU thपढ़ो and that the
 * VCPU thereक्रमe is not currently executing guest code.
 */
व्योम kvm_inject_undefined(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu_el1_is_32bit(vcpu))
		inject_undef32(vcpu);
	अन्यथा
		inject_undef64(vcpu);
पूर्ण

व्योम kvm_set_sei_esr(काष्ठा kvm_vcpu *vcpu, u64 esr)
अणु
	vcpu_set_vsesr(vcpu, esr & ESR_ELx_ISS_MASK);
	*vcpu_hcr(vcpu) |= HCR_VSE;
पूर्ण

/**
 * kvm_inject_vabt - inject an async पात / SError पूर्णांकo the guest
 * @vcpu: The VCPU to receive the exception
 *
 * It is assumed that this code is called from the VCPU thपढ़ो and that the
 * VCPU thereक्रमe is not currently executing guest code.
 *
 * Systems with the RAS Extensions specअगरy an imp-def ESR (ISV/IDS = 1) with
 * the reमुख्यing ISS all-zeros so that this error is not पूर्णांकerpreted as an
 * uncategorized RAS error. Without the RAS Extensions we can't specअगरy an ESR
 * value, so the CPU generates an imp-def value.
 */
व्योम kvm_inject_vabt(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_set_sei_esr(vcpu, ESR_ELx_ISV);
पूर्ण
