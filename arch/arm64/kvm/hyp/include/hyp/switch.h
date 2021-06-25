<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __ARM64_KVM_HYP_SWITCH_H__
#घोषणा __ARM64_KVM_HYP_SWITCH_H__

#समावेश <hyp/adjust_pc.h>

#समावेश <linux/arm-smccc.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/types.h>
#समावेश <linux/jump_label.h>
#समावेश <uapi/linux/psci.h>

#समावेश <kvm/arm_psci.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/extable.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/thपढ़ो_info.h>

बाह्य काष्ठा exception_table_entry __start___kvm_ex_table;
बाह्य काष्ठा exception_table_entry __stop___kvm_ex_table;

/* Check whether the FP regs were dirtied जबतक in the host-side run loop: */
अटल अंतरभूत bool update_fp_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * When the प्रणाली करोesn't support FP/SIMD, we cannot rely on
	 * the _TIF_FOREIGN_FPSTATE flag. However, we always inject an
	 * पात on the very first access to FP and thus we should never
	 * see KVM_ARM64_FP_ENABLED. For added safety, make sure we always
	 * trap the accesses.
	 */
	अगर (!प्रणाली_supports_fpsimd() ||
	    vcpu->arch.host_thपढ़ो_info->flags & _TIF_FOREIGN_FPSTATE)
		vcpu->arch.flags &= ~(KVM_ARM64_FP_ENABLED |
				      KVM_ARM64_FP_HOST);

	वापस !!(vcpu->arch.flags & KVM_ARM64_FP_ENABLED);
पूर्ण

/* Save the 32-bit only FPSIMD प्रणाली रेजिस्टर state */
अटल अंतरभूत व्योम __fpsimd_save_fpexc32(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!vcpu_el1_is_32bit(vcpu))
		वापस;

	__vcpu_sys_reg(vcpu, FPEXC32_EL2) = पढ़ो_sysreg(fpexc32_el2);
पूर्ण

अटल अंतरभूत व्योम __activate_traps_fpsimd32(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * We are about to set CPTR_EL2.TFP to trap all भग्नing poपूर्णांक
	 * रेजिस्टर accesses to EL2, however, the ARM ARM clearly states that
	 * traps are only taken to EL2 अगर the operation would not otherwise
	 * trap to EL1.  Thereक्रमe, always make sure that क्रम 32-bit guests,
	 * we set FPEXC.EN to prevent traps to EL1, when setting the TFP bit.
	 * If FP/ASIMD is not implemented, FPEXC is UNDEFINED and any access to
	 * it will cause an exception.
	 */
	अगर (vcpu_el1_is_32bit(vcpu) && प्रणाली_supports_fpsimd()) अणु
		ग_लिखो_sysreg(1 << 30, fpexc32_el2);
		isb();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __activate_traps_common(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Trap on AArch32 cp15 c15 (impdef sysregs) accesses (EL1 or EL0) */
	ग_लिखो_sysreg(1 << 15, hstr_el2);

	/*
	 * Make sure we trap PMU access from EL0 to EL2. Also sanitize
	 * PMSELR_EL0 to make sure it never contains the cycle
	 * counter, which could make a PMXEVCNTR_EL0 access UNDEF at
	 * EL1 instead of being trapped to EL2.
	 */
	अगर (kvm_arm_support_pmu_v3()) अणु
		ग_लिखो_sysreg(0, pmselr_el0);
		ग_लिखो_sysreg(ARMV8_PMU_USERENR_MASK, pmuserenr_el0);
	पूर्ण
	ग_लिखो_sysreg(vcpu->arch.mdcr_el2, mdcr_el2);
पूर्ण

अटल अंतरभूत व्योम __deactivate_traps_common(व्योम)
अणु
	ग_लिखो_sysreg(0, hstr_el2);
	अगर (kvm_arm_support_pmu_v3())
		ग_लिखो_sysreg(0, pmuserenr_el0);
पूर्ण

अटल अंतरभूत व्योम ___activate_traps(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 hcr = vcpu->arch.hcr_el2;

	अगर (cpus_have_final_cap(ARM64_WORKAROUND_CAVIUM_TX2_219_TVM))
		hcr |= HCR_TVM;

	ग_लिखो_sysreg(hcr, hcr_el2);

	अगर (cpus_have_final_cap(ARM64_HAS_RAS_EXTN) && (hcr & HCR_VSE))
		ग_लिखो_sysreg_s(vcpu->arch.vsesr_el2, SYS_VSESR_EL2);
पूर्ण

अटल अंतरभूत व्योम ___deactivate_traps(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * If we pended a भव पात, preserve it until it माला_लो
	 * cleared. See D1.14.3 (Virtual Interrupts) क्रम details, but
	 * the crucial bit is "On taking a vSError पूर्णांकerrupt,
	 * HCR_EL2.VSE is cleared to 0."
	 */
	अगर (vcpu->arch.hcr_el2 & HCR_VSE) अणु
		vcpu->arch.hcr_el2 &= ~HCR_VSE;
		vcpu->arch.hcr_el2 |= पढ़ो_sysreg(hcr_el2) & HCR_VSE;
	पूर्ण
पूर्ण

अटल अंतरभूत bool __translate_far_to_hpfar(u64 far, u64 *hpfar)
अणु
	u64 par, पंचांगp;

	/*
	 * Resolve the IPA the hard way using the guest VA.
	 *
	 * Stage-1 translation alपढ़ोy validated the memory access
	 * rights. As such, we can use the EL1 translation regime, and
	 * करोn't have to distinguish between EL0 and EL1 access.
	 *
	 * We करो need to save/restore PAR_EL1 though, as we haven't
	 * saved the guest context yet, and we may वापस early...
	 */
	par = पढ़ो_sysreg_par();
	अगर (!__kvm_at("s1e1r", far))
		पंचांगp = पढ़ो_sysreg_par();
	अन्यथा
		पंचांगp = SYS_PAR_EL1_F; /* back to the guest */
	ग_लिखो_sysreg(par, par_el1);

	अगर (unlikely(पंचांगp & SYS_PAR_EL1_F))
		वापस false; /* Translation failed, back to guest */

	/* Convert PAR to HPFAR क्रमmat */
	*hpfar = PAR_TO_HPFAR(पंचांगp);
	वापस true;
पूर्ण

अटल अंतरभूत bool __get_fault_info(u64 esr, काष्ठा kvm_vcpu_fault_info *fault)
अणु
	u64 hpfar, far;

	far = पढ़ो_sysreg_el2(SYS_FAR);

	/*
	 * The HPFAR can be invalid अगर the stage 2 fault did not
	 * happen during a stage 1 page table walk (the ESR_EL2.S1PTW
	 * bit is clear) and one of the two following हालs are true:
	 *   1. The fault was due to a permission fault
	 *   2. The processor carries errata 834220
	 *
	 * Thereक्रमe, क्रम all non S1PTW faults where we either have a
	 * permission fault or the errata workaround is enabled, we
	 * resolve the IPA using the AT inकाष्ठाion.
	 */
	अगर (!(esr & ESR_ELx_S1PTW) &&
	    (cpus_have_final_cap(ARM64_WORKAROUND_834220) ||
	     (esr & ESR_ELx_FSC_TYPE) == FSC_PERM)) अणु
		अगर (!__translate_far_to_hpfar(far, &hpfar))
			वापस false;
	पूर्ण अन्यथा अणु
		hpfar = पढ़ो_sysreg(hpfar_el2);
	पूर्ण

	fault->far_el2 = far;
	fault->hpfar_el2 = hpfar;
	वापस true;
पूर्ण

अटल अंतरभूत bool __populate_fault_info(काष्ठा kvm_vcpu *vcpu)
अणु
	u8 ec;
	u64 esr;

	esr = vcpu->arch.fault.esr_el2;
	ec = ESR_ELx_EC(esr);

	अगर (ec != ESR_ELx_EC_DABT_LOW && ec != ESR_ELx_EC_IABT_LOW)
		वापस true;

	वापस __get_fault_info(esr, &vcpu->arch.fault);
पूर्ण

अटल अंतरभूत व्योम __hyp_sve_save_host(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा thपढ़ो_काष्ठा *thपढ़ो;

	thपढ़ो = container_of(vcpu->arch.host_fpsimd_state, काष्ठा thपढ़ो_काष्ठा,
			      uw.fpsimd_state);

	__sve_save_state(sve_pffr(thपढ़ो), &vcpu->arch.host_fpsimd_state->fpsr);
पूर्ण

अटल अंतरभूत व्योम __hyp_sve_restore_guest(काष्ठा kvm_vcpu *vcpu)
अणु
	sve_cond_update_zcr_vq(vcpu_sve_max_vq(vcpu) - 1, SYS_ZCR_EL2);
	__sve_restore_state(vcpu_sve_pffr(vcpu),
			    &vcpu->arch.ctxt.fp_regs.fpsr);
	ग_लिखो_sysreg_el1(__vcpu_sys_reg(vcpu, ZCR_EL1), SYS_ZCR);
पूर्ण

/* Check क्रम an FPSIMD/SVE trap and handle as appropriate */
अटल अंतरभूत bool __hyp_handle_fpsimd(काष्ठा kvm_vcpu *vcpu)
अणु
	bool sve_guest, sve_host;
	u8 esr_ec;
	u64 reg;

	अगर (!प्रणाली_supports_fpsimd())
		वापस false;

	अगर (प्रणाली_supports_sve()) अणु
		sve_guest = vcpu_has_sve(vcpu);
		sve_host = vcpu->arch.flags & KVM_ARM64_HOST_SVE_IN_USE;
	पूर्ण अन्यथा अणु
		sve_guest = false;
		sve_host = false;
	पूर्ण

	esr_ec = kvm_vcpu_trap_get_class(vcpu);
	अगर (esr_ec != ESR_ELx_EC_FP_ASIMD &&
	    esr_ec != ESR_ELx_EC_SVE)
		वापस false;

	/* Don't handle SVE traps क्रम non-SVE vcpus here: */
	अगर (!sve_guest && esr_ec != ESR_ELx_EC_FP_ASIMD)
		वापस false;

	/* Valid trap.  Switch the context: */
	अगर (has_vhe()) अणु
		reg = CPACR_EL1_FPEN;
		अगर (sve_guest)
			reg |= CPACR_EL1_ZEN;

		sysreg_clear_set(cpacr_el1, 0, reg);
	पूर्ण अन्यथा अणु
		reg = CPTR_EL2_TFP;
		अगर (sve_guest)
			reg |= CPTR_EL2_TZ;

		sysreg_clear_set(cptr_el2, reg, 0);
	पूर्ण
	isb();

	अगर (vcpu->arch.flags & KVM_ARM64_FP_HOST) अणु
		अगर (sve_host)
			__hyp_sve_save_host(vcpu);
		अन्यथा
			__fpsimd_save_state(vcpu->arch.host_fpsimd_state);

		vcpu->arch.flags &= ~KVM_ARM64_FP_HOST;
	पूर्ण

	अगर (sve_guest)
		__hyp_sve_restore_guest(vcpu);
	अन्यथा
		__fpsimd_restore_state(&vcpu->arch.ctxt.fp_regs);

	/* Skip restoring fpexc32 क्रम AArch64 guests */
	अगर (!(पढ़ो_sysreg(hcr_el2) & HCR_RW))
		ग_लिखो_sysreg(__vcpu_sys_reg(vcpu, FPEXC32_EL2), fpexc32_el2);

	vcpu->arch.flags |= KVM_ARM64_FP_ENABLED;

	वापस true;
पूर्ण

अटल अंतरभूत bool handle_tx2_tvm(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 sysreg = esr_sys64_to_sysreg(kvm_vcpu_get_esr(vcpu));
	पूर्णांक rt = kvm_vcpu_sys_get_rt(vcpu);
	u64 val = vcpu_get_reg(vcpu, rt);

	/*
	 * The normal sysreg handling code expects to see the traps,
	 * let's not करो anything here.
	 */
	अगर (vcpu->arch.hcr_el2 & HCR_TVM)
		वापस false;

	चयन (sysreg) अणु
	हाल SYS_SCTLR_EL1:
		ग_लिखो_sysreg_el1(val, SYS_SCTLR);
		अवरोध;
	हाल SYS_TTBR0_EL1:
		ग_लिखो_sysreg_el1(val, SYS_TTBR0);
		अवरोध;
	हाल SYS_TTBR1_EL1:
		ग_लिखो_sysreg_el1(val, SYS_TTBR1);
		अवरोध;
	हाल SYS_TCR_EL1:
		ग_लिखो_sysreg_el1(val, SYS_TCR);
		अवरोध;
	हाल SYS_ESR_EL1:
		ग_लिखो_sysreg_el1(val, SYS_ESR);
		अवरोध;
	हाल SYS_FAR_EL1:
		ग_लिखो_sysreg_el1(val, SYS_FAR);
		अवरोध;
	हाल SYS_AFSR0_EL1:
		ग_लिखो_sysreg_el1(val, SYS_AFSR0);
		अवरोध;
	हाल SYS_AFSR1_EL1:
		ग_लिखो_sysreg_el1(val, SYS_AFSR1);
		अवरोध;
	हाल SYS_MAIR_EL1:
		ग_लिखो_sysreg_el1(val, SYS_MAIR);
		अवरोध;
	हाल SYS_AMAIR_EL1:
		ग_लिखो_sysreg_el1(val, SYS_AMAIR);
		अवरोध;
	हाल SYS_CONTEXTIDR_EL1:
		ग_लिखो_sysreg_el1(val, SYS_CONTEXTIDR);
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	__kvm_skip_instr(vcpu);
	वापस true;
पूर्ण

अटल अंतरभूत bool esr_is_ptrauth_trap(u32 esr)
अणु
	u32 ec = ESR_ELx_EC(esr);

	अगर (ec == ESR_ELx_EC_PAC)
		वापस true;

	अगर (ec != ESR_ELx_EC_SYS64)
		वापस false;

	चयन (esr_sys64_to_sysreg(esr)) अणु
	हाल SYS_APIAKEYLO_EL1:
	हाल SYS_APIAKEYHI_EL1:
	हाल SYS_APIBKEYLO_EL1:
	हाल SYS_APIBKEYHI_EL1:
	हाल SYS_APDAKEYLO_EL1:
	हाल SYS_APDAKEYHI_EL1:
	हाल SYS_APDBKEYLO_EL1:
	हाल SYS_APDBKEYHI_EL1:
	हाल SYS_APGAKEYLO_EL1:
	हाल SYS_APGAKEYHI_EL1:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

#घोषणा __ptrauth_save_key(ctxt, key)					\
	करो अणु								\
	u64 __val;                                                      \
	__val = पढ़ो_sysreg_s(SYS_ ## key ## KEYLO_EL1);                \
	ctxt_sys_reg(ctxt, key ## KEYLO_EL1) = __val;                   \
	__val = पढ़ो_sysreg_s(SYS_ ## key ## KEYHI_EL1);                \
	ctxt_sys_reg(ctxt, key ## KEYHI_EL1) = __val;                   \
पूर्ण जबतक(0)

DECLARE_PER_CPU(काष्ठा kvm_cpu_context, kvm_hyp_ctxt);

अटल अंतरभूत bool __hyp_handle_ptrauth(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpu_context *ctxt;
	u64 val;

	अगर (!vcpu_has_ptrauth(vcpu) ||
	    !esr_is_ptrauth_trap(kvm_vcpu_get_esr(vcpu)))
		वापस false;

	ctxt = this_cpu_ptr(&kvm_hyp_ctxt);
	__ptrauth_save_key(ctxt, APIA);
	__ptrauth_save_key(ctxt, APIB);
	__ptrauth_save_key(ctxt, APDA);
	__ptrauth_save_key(ctxt, APDB);
	__ptrauth_save_key(ctxt, APGA);

	vcpu_ptrauth_enable(vcpu);

	val = पढ़ो_sysreg(hcr_el2);
	val |= (HCR_API | HCR_APK);
	ग_लिखो_sysreg(val, hcr_el2);

	वापस true;
पूर्ण

/*
 * Return true when we were able to fixup the guest निकास and should वापस to
 * the guest, false when we should restore the host state and वापस to the
 * मुख्य run loop.
 */
अटल अंतरभूत bool fixup_guest_निकास(काष्ठा kvm_vcpu *vcpu, u64 *निकास_code)
अणु
	अगर (ARM_EXCEPTION_CODE(*निकास_code) != ARM_EXCEPTION_IRQ)
		vcpu->arch.fault.esr_el2 = पढ़ो_sysreg_el2(SYS_ESR);

	अगर (ARM_SERROR_PENDING(*निकास_code)) अणु
		u8 esr_ec = kvm_vcpu_trap_get_class(vcpu);

		/*
		 * HVC alपढ़ोy have an adjusted PC, which we need to
		 * correct in order to वापस to after having injected
		 * the SError.
		 *
		 * SMC, on the other hand, is *trapped*, meaning its
		 * preferred वापस address is the SMC itself.
		 */
		अगर (esr_ec == ESR_ELx_EC_HVC32 || esr_ec == ESR_ELx_EC_HVC64)
			ग_लिखो_sysreg_el2(पढ़ो_sysreg_el2(SYS_ELR) - 4, SYS_ELR);
	पूर्ण

	/*
	 * We're using the raw exception code in order to only process
	 * the trap अगर no SError is pending. We will come back to the
	 * same PC once the SError has been injected, and replay the
	 * trapping inकाष्ठाion.
	 */
	अगर (*निकास_code != ARM_EXCEPTION_TRAP)
		जाओ निकास;

	अगर (cpus_have_final_cap(ARM64_WORKAROUND_CAVIUM_TX2_219_TVM) &&
	    kvm_vcpu_trap_get_class(vcpu) == ESR_ELx_EC_SYS64 &&
	    handle_tx2_tvm(vcpu))
		जाओ guest;

	/*
	 * We trap the first access to the FP/SIMD to save the host context
	 * and restore the guest context lazily.
	 * If FP/SIMD is not implemented, handle the trap and inject an
	 * undefined inकाष्ठाion exception to the guest.
	 * Similarly क्रम trapped SVE accesses.
	 */
	अगर (__hyp_handle_fpsimd(vcpu))
		जाओ guest;

	अगर (__hyp_handle_ptrauth(vcpu))
		जाओ guest;

	अगर (!__populate_fault_info(vcpu))
		जाओ guest;

	अगर (अटल_branch_unlikely(&vgic_v2_cpuअगर_trap)) अणु
		bool valid;

		valid = kvm_vcpu_trap_get_class(vcpu) == ESR_ELx_EC_DABT_LOW &&
			kvm_vcpu_trap_get_fault_type(vcpu) == FSC_FAULT &&
			kvm_vcpu_dabt_isvalid(vcpu) &&
			!kvm_vcpu_abt_issea(vcpu) &&
			!kvm_vcpu_abt_iss1tw(vcpu);

		अगर (valid) अणु
			पूर्णांक ret = __vgic_v2_perक्रमm_cpuअगर_access(vcpu);

			अगर (ret == 1)
				जाओ guest;

			/* Promote an illegal access to an SError.*/
			अगर (ret == -1)
				*निकास_code = ARM_EXCEPTION_EL1_SERROR;

			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (अटल_branch_unlikely(&vgic_v3_cpuअगर_trap) &&
	    (kvm_vcpu_trap_get_class(vcpu) == ESR_ELx_EC_SYS64 ||
	     kvm_vcpu_trap_get_class(vcpu) == ESR_ELx_EC_CP15_32)) अणु
		पूर्णांक ret = __vgic_v3_perक्रमm_cpuअगर_access(vcpu);

		अगर (ret == 1)
			जाओ guest;
	पूर्ण

निकास:
	/* Return to the host kernel and handle the निकास */
	वापस false;

guest:
	/* Re-enter the guest */
	यंत्र(ALTERNATIVE("nop", "dmb sy", ARM64_WORKAROUND_1508412));
	वापस true;
पूर्ण

अटल अंतरभूत व्योम __kvm_unexpected_el2_exception(व्योम)
अणु
	बाह्य अक्षर __guest_निकास_panic[];
	अचिन्हित दीर्घ addr, fixup;
	काष्ठा exception_table_entry *entry, *end;
	अचिन्हित दीर्घ elr_el2 = पढ़ो_sysreg(elr_el2);

	entry = &__start___kvm_ex_table;
	end = &__stop___kvm_ex_table;

	जबतक (entry < end) अणु
		addr = (अचिन्हित दीर्घ)&entry->insn + entry->insn;
		fixup = (अचिन्हित दीर्घ)&entry->fixup + entry->fixup;

		अगर (addr != elr_el2) अणु
			entry++;
			जारी;
		पूर्ण

		ग_लिखो_sysreg(fixup, elr_el2);
		वापस;
	पूर्ण

	/* Trigger a panic after restoring the hyp context. */
	ग_लिखो_sysreg(__guest_निकास_panic, elr_el2);
पूर्ण

#पूर्ण_अगर /* __ARM64_KVM_HYP_SWITCH_H__ */
