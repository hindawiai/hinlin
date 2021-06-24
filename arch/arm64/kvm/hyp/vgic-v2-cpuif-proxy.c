<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <hyp/adjust_pc.h>

#समावेश <linux/compiler.h>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/swab.h>

#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>

अटल bool __is_be(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu_mode_is_32bit(vcpu))
		वापस !!(पढ़ो_sysreg_el2(SYS_SPSR) & PSR_AA32_E_BIT);

	वापस !!(पढ़ो_sysreg(SCTLR_EL1) & SCTLR_ELx_EE);
पूर्ण

/*
 * __vgic_v2_perक्रमm_cpuअगर_access -- perक्रमm a GICV access on behalf of the
 *				     guest.
 *
 * @vcpu: the offending vcpu
 *
 * Returns:
 *  1: GICV access successfully perक्रमmed
 *  0: Not a GICV access
 * -1: Illegal GICV access successfully perक्रमmed
 */
पूर्णांक __vgic_v2_perक्रमm_cpuअगर_access(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm *kvm = kern_hyp_va(vcpu->kvm);
	काष्ठा vgic_dist *vgic = &kvm->arch.vgic;
	phys_addr_t fault_ipa;
	व्योम __iomem *addr;
	पूर्णांक rd;

	/* Build the full address */
	fault_ipa  = kvm_vcpu_get_fault_ipa(vcpu);
	fault_ipa |= kvm_vcpu_get_hfar(vcpu) & GENMASK(11, 0);

	/* If not क्रम GICV, move on */
	अगर (fault_ipa <  vgic->vgic_cpu_base ||
	    fault_ipa >= (vgic->vgic_cpu_base + KVM_VGIC_V2_CPU_SIZE))
		वापस 0;

	/* Reject anything but a 32bit access */
	अगर (kvm_vcpu_dabt_get_as(vcpu) != माप(u32)) अणु
		__kvm_skip_instr(vcpu);
		वापस -1;
	पूर्ण

	/* Not aligned? Don't bother */
	अगर (fault_ipa & 3) अणु
		__kvm_skip_instr(vcpu);
		वापस -1;
	पूर्ण

	rd = kvm_vcpu_dabt_get_rd(vcpu);
	addr  = kvm_vgic_global_state.vcpu_hyp_va;
	addr += fault_ipa - vgic->vgic_cpu_base;

	अगर (kvm_vcpu_dabt_isग_लिखो(vcpu)) अणु
		u32 data = vcpu_get_reg(vcpu, rd);
		अगर (__is_be(vcpu)) अणु
			/* guest pre-swabbed data, unकरो this क्रम ग_लिखोl() */
			data = __kvm_swab32(data);
		पूर्ण
		ग_लिखोl_relaxed(data, addr);
	पूर्ण अन्यथा अणु
		u32 data = पढ़ोl_relaxed(addr);
		अगर (__is_be(vcpu)) अणु
			/* guest expects swabbed data */
			data = __kvm_swab32(data);
		पूर्ण
		vcpu_set_reg(vcpu, rd, data);
	पूर्ण

	__kvm_skip_instr(vcpu);

	वापस 1;
पूर्ण
