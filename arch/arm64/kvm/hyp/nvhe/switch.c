<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <hyp/चयन.h>
#समावेश <hyp/sysreg-sr.h>

#समावेश <linux/arm-smccc.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/types.h>
#समावेश <linux/jump_label.h>
#समावेश <uapi/linux/psci.h>

#समावेश <kvm/arm_psci.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/thपढ़ो_info.h>

#समावेश <nvhe/mem_protect.h>

/* Non-VHE specअगरic context */
DEFINE_PER_CPU(काष्ठा kvm_host_data, kvm_host_data);
DEFINE_PER_CPU(काष्ठा kvm_cpu_context, kvm_hyp_ctxt);
DEFINE_PER_CPU(अचिन्हित दीर्घ, kvm_hyp_vector);

अटल व्योम __activate_traps(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 val;

	___activate_traps(vcpu);
	__activate_traps_common(vcpu);

	val = CPTR_EL2_DEFAULT;
	val |= CPTR_EL2_TTA | CPTR_EL2_TAM;
	अगर (!update_fp_enabled(vcpu)) अणु
		val |= CPTR_EL2_TFP | CPTR_EL2_TZ;
		__activate_traps_fpsimd32(vcpu);
	पूर्ण

	ग_लिखो_sysreg(val, cptr_el2);
	ग_लिखो_sysreg(__this_cpu_पढ़ो(kvm_hyp_vector), vbar_el2);

	अगर (cpus_have_final_cap(ARM64_WORKAROUND_SPECULATIVE_AT)) अणु
		काष्ठा kvm_cpu_context *ctxt = &vcpu->arch.ctxt;

		isb();
		/*
		 * At this stage, and thanks to the above isb(), S2 is
		 * configured and enabled. We can now restore the guest's S1
		 * configuration: SCTLR, and only then TCR.
		 */
		ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, SCTLR_EL1),	SYS_SCTLR);
		isb();
		ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, TCR_EL1),	SYS_TCR);
	पूर्ण
पूर्ण

अटल व्योम __deactivate_traps(काष्ठा kvm_vcpu *vcpu)
अणु
	बाह्य अक्षर __kvm_hyp_host_vector[];
	u64 mdcr_el2, cptr;

	___deactivate_traps(vcpu);

	mdcr_el2 = पढ़ो_sysreg(mdcr_el2);

	अगर (cpus_have_final_cap(ARM64_WORKAROUND_SPECULATIVE_AT)) अणु
		u64 val;

		/*
		 * Set the TCR and SCTLR रेजिस्टरs in the exact opposite
		 * sequence as __activate_traps (first prevent walks,
		 * then क्रमce the MMU on). A generous sprinkling of isb()
		 * ensure that things happen in this exact order.
		 */
		val = पढ़ो_sysreg_el1(SYS_TCR);
		ग_लिखो_sysreg_el1(val | TCR_EPD1_MASK | TCR_EPD0_MASK, SYS_TCR);
		isb();
		val = पढ़ो_sysreg_el1(SYS_SCTLR);
		ग_लिखो_sysreg_el1(val | SCTLR_ELx_M, SYS_SCTLR);
		isb();
	पूर्ण

	__deactivate_traps_common();

	mdcr_el2 &= MDCR_EL2_HPMN_MASK;
	mdcr_el2 |= MDCR_EL2_E2PB_MASK << MDCR_EL2_E2PB_SHIFT;
	mdcr_el2 |= MDCR_EL2_E2TB_MASK << MDCR_EL2_E2TB_SHIFT;

	ग_लिखो_sysreg(mdcr_el2, mdcr_el2);
	ग_लिखो_sysreg(this_cpu_ptr(&kvm_init_params)->hcr_el2, hcr_el2);

	cptr = CPTR_EL2_DEFAULT;
	अगर (vcpu_has_sve(vcpu) && (vcpu->arch.flags & KVM_ARM64_FP_ENABLED))
		cptr |= CPTR_EL2_TZ;

	ग_लिखो_sysreg(cptr, cptr_el2);
	ग_लिखो_sysreg(__kvm_hyp_host_vector, vbar_el2);
पूर्ण

/* Save VGICv3 state on non-VHE प्रणालीs */
अटल व्योम __hyp_vgic_save_state(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (अटल_branch_unlikely(&kvm_vgic_global_state.gicv3_cpuअगर)) अणु
		__vgic_v3_save_state(&vcpu->arch.vgic_cpu.vgic_v3);
		__vgic_v3_deactivate_traps(&vcpu->arch.vgic_cpu.vgic_v3);
	पूर्ण
पूर्ण

/* Restore VGICv3 state on non_VEH प्रणालीs */
अटल व्योम __hyp_vgic_restore_state(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (अटल_branch_unlikely(&kvm_vgic_global_state.gicv3_cpuअगर)) अणु
		__vgic_v3_activate_traps(&vcpu->arch.vgic_cpu.vgic_v3);
		__vgic_v3_restore_state(&vcpu->arch.vgic_cpu.vgic_v3);
	पूर्ण
पूर्ण

/**
 * Disable host events, enable guest events
 */
अटल bool __pmu_चयन_to_guest(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	काष्ठा kvm_host_data *host;
	काष्ठा kvm_pmu_events *pmu;

	host = container_of(host_ctxt, काष्ठा kvm_host_data, host_ctxt);
	pmu = &host->pmu_events;

	अगर (pmu->events_host)
		ग_लिखो_sysreg(pmu->events_host, pmcntenclr_el0);

	अगर (pmu->events_guest)
		ग_लिखो_sysreg(pmu->events_guest, pmcntenset_el0);

	वापस (pmu->events_host || pmu->events_guest);
पूर्ण

/**
 * Disable guest events, enable host events
 */
अटल व्योम __pmu_चयन_to_host(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	काष्ठा kvm_host_data *host;
	काष्ठा kvm_pmu_events *pmu;

	host = container_of(host_ctxt, काष्ठा kvm_host_data, host_ctxt);
	pmu = &host->pmu_events;

	अगर (pmu->events_guest)
		ग_लिखो_sysreg(pmu->events_guest, pmcntenclr_el0);

	अगर (pmu->events_host)
		ग_लिखो_sysreg(pmu->events_host, pmcntenset_el0);
पूर्ण

/* Switch to the guest क्रम legacy non-VHE प्रणालीs */
पूर्णांक __kvm_vcpu_run(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpu_context *host_ctxt;
	काष्ठा kvm_cpu_context *guest_ctxt;
	bool pmu_चयन_needed;
	u64 निकास_code;

	/*
	 * Having IRQs masked via PMR when entering the guest means the GIC
	 * will not संकेत the CPU of पूर्णांकerrupts of lower priority, and the
	 * only way to get out will be via guest exceptions.
	 * Naturally, we want to aव्योम this.
	 */
	अगर (प्रणाली_uses_irq_prio_masking()) अणु
		gic_ग_लिखो_pmr(GIC_PRIO_IRQON | GIC_PRIO_PSR_I_SET);
		pmr_sync();
	पूर्ण

	host_ctxt = &this_cpu_ptr(&kvm_host_data)->host_ctxt;
	host_ctxt->__hyp_running_vcpu = vcpu;
	guest_ctxt = &vcpu->arch.ctxt;

	pmu_चयन_needed = __pmu_चयन_to_guest(host_ctxt);

	__sysreg_save_state_nvhe(host_ctxt);
	/*
	 * We must flush and disable the SPE buffer क्रम nVHE, as
	 * the translation regime(EL1&0) is going to be loaded with
	 * that of the guest. And we must करो this beक्रमe we change the
	 * translation regime to EL2 (via MDCR_EL2_E2PB == 0) and
	 * beक्रमe we load guest Stage1.
	 */
	__debug_save_host_buffers_nvhe(vcpu);

	__kvm_adjust_pc(vcpu);

	/*
	 * We must restore the 32-bit state beक्रमe the sysregs, thanks
	 * to erratum #852523 (Cortex-A57) or #853709 (Cortex-A72).
	 *
	 * Also, and in order to be able to deal with erratum #1319537 (A57)
	 * and #1319367 (A72), we must ensure that all VM-related sysreg are
	 * restored beक्रमe we enable S2 translation.
	 */
	__sysreg32_restore_state(vcpu);
	__sysreg_restore_state_nvhe(guest_ctxt);

	__load_guest_stage2(kern_hyp_va(vcpu->arch.hw_mmu));
	__activate_traps(vcpu);

	__hyp_vgic_restore_state(vcpu);
	__समयr_enable_traps(vcpu);

	__debug_चयन_to_guest(vcpu);

	करो अणु
		/* Jump in the fire! */
		निकास_code = __guest_enter(vcpu);

		/* And we're baaack! */
	पूर्ण जबतक (fixup_guest_निकास(vcpu, &निकास_code));

	__sysreg_save_state_nvhe(guest_ctxt);
	__sysreg32_save_state(vcpu);
	__समयr_disable_traps(vcpu);
	__hyp_vgic_save_state(vcpu);

	__deactivate_traps(vcpu);
	__load_host_stage2();

	__sysreg_restore_state_nvhe(host_ctxt);

	अगर (vcpu->arch.flags & KVM_ARM64_FP_ENABLED)
		__fpsimd_save_fpexc32(vcpu);

	__debug_चयन_to_host(vcpu);
	/*
	 * This must come after restoring the host sysregs, since a non-VHE
	 * प्रणाली may enable SPE here and make use of the TTBRs.
	 */
	__debug_restore_host_buffers_nvhe(vcpu);

	अगर (pmu_चयन_needed)
		__pmu_चयन_to_host(host_ctxt);

	/* Returning to host will clear PSR.I, remask PMR अगर needed */
	अगर (प्रणाली_uses_irq_prio_masking())
		gic_ग_लिखो_pmr(GIC_PRIO_IRQOFF);

	host_ctxt->__hyp_running_vcpu = शून्य;

	वापस निकास_code;
पूर्ण

व्योम __noवापस hyp_panic(व्योम)
अणु
	u64 spsr = पढ़ो_sysreg_el2(SYS_SPSR);
	u64 elr = पढ़ो_sysreg_el2(SYS_ELR);
	u64 par = पढ़ो_sysreg_par();
	काष्ठा kvm_cpu_context *host_ctxt;
	काष्ठा kvm_vcpu *vcpu;

	host_ctxt = &this_cpu_ptr(&kvm_host_data)->host_ctxt;
	vcpu = host_ctxt->__hyp_running_vcpu;

	अगर (vcpu) अणु
		__समयr_disable_traps(vcpu);
		__deactivate_traps(vcpu);
		__load_host_stage2();
		__sysreg_restore_state_nvhe(host_ctxt);
	पूर्ण

	__hyp_करो_panic(host_ctxt, spsr, elr, par);
	unreachable();
पूर्ण

यंत्रlinkage व्योम kvm_unexpected_el2_exception(व्योम)
अणु
	वापस __kvm_unexpected_el2_exception();
पूर्ण
