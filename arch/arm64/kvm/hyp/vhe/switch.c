<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <hyp/चयन.h>

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

/* VHE specअगरic context */
DEFINE_PER_CPU(काष्ठा kvm_host_data, kvm_host_data);
DEFINE_PER_CPU(काष्ठा kvm_cpu_context, kvm_hyp_ctxt);
DEFINE_PER_CPU(अचिन्हित दीर्घ, kvm_hyp_vector);

अटल व्योम __activate_traps(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 val;

	___activate_traps(vcpu);

	val = पढ़ो_sysreg(cpacr_el1);
	val |= CPACR_EL1_TTA;
	val &= ~CPACR_EL1_ZEN;

	/*
	 * With VHE (HCR.E2H == 1), accesses to CPACR_EL1 are routed to
	 * CPTR_EL2. In general, CPACR_EL1 has the same layout as CPTR_EL2,
	 * except क्रम some missing controls, such as TAM.
	 * In this हाल, CPTR_EL2.TAM has the same position with or without
	 * VHE (HCR.E2H == 1) which allows us to use here the CPTR_EL2.TAM
	 * shअगरt value क्रम trapping the AMU accesses.
	 */

	val |= CPTR_EL2_TAM;

	अगर (update_fp_enabled(vcpu)) अणु
		अगर (vcpu_has_sve(vcpu))
			val |= CPACR_EL1_ZEN;
	पूर्ण अन्यथा अणु
		val &= ~CPACR_EL1_FPEN;
		__activate_traps_fpsimd32(vcpu);
	पूर्ण

	ग_लिखो_sysreg(val, cpacr_el1);

	ग_लिखो_sysreg(__this_cpu_पढ़ो(kvm_hyp_vector), vbar_el1);
पूर्ण
NOKPROBE_SYMBOL(__activate_traps);

अटल व्योम __deactivate_traps(काष्ठा kvm_vcpu *vcpu)
अणु
	बाह्य अक्षर vectors[];	/* kernel exception vectors */

	___deactivate_traps(vcpu);

	ग_लिखो_sysreg(HCR_HOST_VHE_FLAGS, hcr_el2);

	/*
	 * ARM errata 1165522 and 1530923 require the actual execution of the
	 * above beक्रमe we can चयन to the EL2/EL0 translation regime used by
	 * the host.
	 */
	यंत्र(ALTERNATIVE("nop", "isb", ARM64_WORKAROUND_SPECULATIVE_AT));

	ग_लिखो_sysreg(CPACR_EL1_DEFAULT, cpacr_el1);
	ग_लिखो_sysreg(vectors, vbar_el1);
पूर्ण
NOKPROBE_SYMBOL(__deactivate_traps);

व्योम activate_traps_vhe_load(काष्ठा kvm_vcpu *vcpu)
अणु
	__activate_traps_common(vcpu);
पूर्ण

व्योम deactivate_traps_vhe_put(व्योम)
अणु
	u64 mdcr_el2 = पढ़ो_sysreg(mdcr_el2);

	mdcr_el2 &= MDCR_EL2_HPMN_MASK |
		    MDCR_EL2_E2PB_MASK << MDCR_EL2_E2PB_SHIFT |
		    MDCR_EL2_TPMS;

	ग_लिखो_sysreg(mdcr_el2, mdcr_el2);

	__deactivate_traps_common();
पूर्ण

/* Switch to the guest क्रम VHE प्रणालीs running in EL2 */
अटल पूर्णांक __kvm_vcpu_run_vhe(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpu_context *host_ctxt;
	काष्ठा kvm_cpu_context *guest_ctxt;
	u64 निकास_code;

	host_ctxt = &this_cpu_ptr(&kvm_host_data)->host_ctxt;
	host_ctxt->__hyp_running_vcpu = vcpu;
	guest_ctxt = &vcpu->arch.ctxt;

	sysreg_save_host_state_vhe(host_ctxt);

	/*
	 * ARM erratum 1165522 requires us to configure both stage 1 and
	 * stage 2 translation क्रम the guest context beक्रमe we clear
	 * HCR_EL2.TGE.
	 *
	 * We have alपढ़ोy configured the guest's stage 1 translation in
	 * kvm_vcpu_load_sysregs_vhe above.  We must now call
	 * __load_guest_stage2 beक्रमe __activate_traps, because
	 * __load_guest_stage2 configures stage 2 translation, and
	 * __activate_traps clear HCR_EL2.TGE (among other things).
	 */
	__load_guest_stage2(vcpu->arch.hw_mmu);
	__activate_traps(vcpu);

	__kvm_adjust_pc(vcpu);

	sysreg_restore_guest_state_vhe(guest_ctxt);
	__debug_चयन_to_guest(vcpu);

	करो अणु
		/* Jump in the fire! */
		निकास_code = __guest_enter(vcpu);

		/* And we're baaack! */
	पूर्ण जबतक (fixup_guest_निकास(vcpu, &निकास_code));

	sysreg_save_guest_state_vhe(guest_ctxt);

	__deactivate_traps(vcpu);

	sysreg_restore_host_state_vhe(host_ctxt);

	अगर (vcpu->arch.flags & KVM_ARM64_FP_ENABLED)
		__fpsimd_save_fpexc32(vcpu);

	__debug_चयन_to_host(vcpu);

	वापस निकास_code;
पूर्ण
NOKPROBE_SYMBOL(__kvm_vcpu_run_vhe);

पूर्णांक __kvm_vcpu_run(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret;

	local_daअगर_mask();

	/*
	 * Having IRQs masked via PMR when entering the guest means the GIC
	 * will not संकेत the CPU of पूर्णांकerrupts of lower priority, and the
	 * only way to get out will be via guest exceptions.
	 * Naturally, we want to aव्योम this.
	 *
	 * local_daअगर_mask() alपढ़ोy sets GIC_PRIO_PSR_I_SET, we just need a
	 * dsb to ensure the redistributor is क्रमwards EL2 IRQs to the CPU.
	 */
	pmr_sync();

	ret = __kvm_vcpu_run_vhe(vcpu);

	/*
	 * local_daअगर_restore() takes care to properly restore PSTATE.DAIF
	 * and the GIC PMR अगर the host is using IRQ priorities.
	 */
	local_daअगर_restore(DAIF_PROCCTX_NOIRQ);

	/*
	 * When we निकास from the guest we change a number of CPU configuration
	 * parameters, such as traps.  Make sure these changes take effect
	 * beक्रमe running the host or additional guests.
	 */
	isb();

	वापस ret;
पूर्ण

अटल व्योम __hyp_call_panic(u64 spsr, u64 elr, u64 par)
अणु
	काष्ठा kvm_cpu_context *host_ctxt;
	काष्ठा kvm_vcpu *vcpu;

	host_ctxt = &this_cpu_ptr(&kvm_host_data)->host_ctxt;
	vcpu = host_ctxt->__hyp_running_vcpu;

	__deactivate_traps(vcpu);
	sysreg_restore_host_state_vhe(host_ctxt);

	panic("HYP panic:\nPS:%08llx PC:%016llx ESR:%08llx\nFAR:%016llx HPFAR:%016llx PAR:%016llx\nVCPU:%p\n",
	      spsr, elr,
	      पढ़ो_sysreg_el2(SYS_ESR), पढ़ो_sysreg_el2(SYS_FAR),
	      पढ़ो_sysreg(hpfar_el2), par, vcpu);
पूर्ण
NOKPROBE_SYMBOL(__hyp_call_panic);

व्योम __noवापस hyp_panic(व्योम)
अणु
	u64 spsr = पढ़ो_sysreg_el2(SYS_SPSR);
	u64 elr = पढ़ो_sysreg_el2(SYS_ELR);
	u64 par = पढ़ो_sysreg_par();

	__hyp_call_panic(spsr, elr, par);
	unreachable();
पूर्ण

यंत्रlinkage व्योम kvm_unexpected_el2_exception(व्योम)
अणु
	वापस __kvm_unexpected_el2_exception();
पूर्ण
