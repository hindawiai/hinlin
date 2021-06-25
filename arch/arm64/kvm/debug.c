<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Debug and Guest Debug support
 *
 * Copyright (C) 2015 - Linaro Ltd
 * Author: Alex Bennथऊe <alex.bennee@linaro.org>
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>

#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_arm.h>
#समावेश <यंत्र/kvm_emulate.h>

#समावेश "trace.h"

/* These are the bits of MDSCR_EL1 we may manipulate */
#घोषणा MDSCR_EL1_DEBUG_MASK	(DBG_MDSCR_SS | \
				DBG_MDSCR_KDE | \
				DBG_MDSCR_MDE)

अटल DEFINE_PER_CPU(u32, mdcr_el2);

/**
 * save/restore_guest_debug_regs
 *
 * For some debug operations we need to tweak some guest रेजिस्टरs. As
 * a result we need to save the state of those रेजिस्टरs beक्रमe we
 * make those modअगरications.
 *
 * Guest access to MDSCR_EL1 is trapped by the hypervisor and handled
 * after we have restored the preserved value to the मुख्य context.
 */
अटल व्योम save_guest_debug_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 val = vcpu_पढ़ो_sys_reg(vcpu, MDSCR_EL1);

	vcpu->arch.guest_debug_preserved.mdscr_el1 = val;

	trace_kvm_arm_set_dreg32("Saved MDSCR_EL1",
				vcpu->arch.guest_debug_preserved.mdscr_el1);
पूर्ण

अटल व्योम restore_guest_debug_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 val = vcpu->arch.guest_debug_preserved.mdscr_el1;

	vcpu_ग_लिखो_sys_reg(vcpu, val, MDSCR_EL1);

	trace_kvm_arm_set_dreg32("Restored MDSCR_EL1",
				vcpu_पढ़ो_sys_reg(vcpu, MDSCR_EL1));
पूर्ण

/**
 * kvm_arm_init_debug - grab what we need क्रम debug
 *
 * Currently the sole task of this function is to retrieve the initial
 * value of mdcr_el2 so we can preserve MDCR_EL2.HPMN which has
 * presumably been set-up by some knowledgeable bootcode.
 *
 * It is called once per-cpu during CPU hyp initialisation.
 */

व्योम kvm_arm_init_debug(व्योम)
अणु
	__this_cpu_ग_लिखो(mdcr_el2, kvm_call_hyp_ret(__kvm_get_mdcr_el2));
पूर्ण

/**
 * kvm_arm_setup_mdcr_el2 - configure vcpu mdcr_el2 value
 *
 * @vcpu:	the vcpu poपूर्णांकer
 *
 * This ensures we will trap access to:
 *  - Perक्रमmance monitors (MDCR_EL2_TPM/MDCR_EL2_TPMCR)
 *  - Debug ROM Address (MDCR_EL2_TDRA)
 *  - OS related रेजिस्टरs (MDCR_EL2_TDOSA)
 *  - Statistical profiler (MDCR_EL2_TPMS/MDCR_EL2_E2PB)
 *  - Self-hosted Trace Filter controls (MDCR_EL2_TTRF)
 *  - Self-hosted Trace (MDCR_EL2_TTRF/MDCR_EL2_E2TB)
 */
अटल व्योम kvm_arm_setup_mdcr_el2(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * This also clears MDCR_EL2_E2PB_MASK and MDCR_EL2_E2TB_MASK
	 * to disable guest access to the profiling and trace buffers
	 */
	vcpu->arch.mdcr_el2 = __this_cpu_पढ़ो(mdcr_el2) & MDCR_EL2_HPMN_MASK;
	vcpu->arch.mdcr_el2 |= (MDCR_EL2_TPM |
				MDCR_EL2_TPMS |
				MDCR_EL2_TTRF |
				MDCR_EL2_TPMCR |
				MDCR_EL2_TDRA |
				MDCR_EL2_TDOSA);

	/* Is the VM being debugged by userspace? */
	अगर (vcpu->guest_debug)
		/* Route all software debug exceptions to EL2 */
		vcpu->arch.mdcr_el2 |= MDCR_EL2_TDE;

	/*
	 * Trap debug रेजिस्टर access when one of the following is true:
	 *  - Userspace is using the hardware to debug the guest
	 *  (KVM_GUESTDBG_USE_HW is set).
	 *  - The guest is not using debug (KVM_ARM64_DEBUG_सूचीTY is clear).
	 */
	अगर ((vcpu->guest_debug & KVM_GUESTDBG_USE_HW) ||
	    !(vcpu->arch.flags & KVM_ARM64_DEBUG_सूचीTY))
		vcpu->arch.mdcr_el2 |= MDCR_EL2_TDA;

	trace_kvm_arm_set_dreg32("MDCR_EL2", vcpu->arch.mdcr_el2);
पूर्ण

/**
 * kvm_arm_vcpu_init_debug - setup vcpu debug traps
 *
 * @vcpu:	the vcpu poपूर्णांकer
 *
 * Set vcpu initial mdcr_el2 value.
 */
व्योम kvm_arm_vcpu_init_debug(काष्ठा kvm_vcpu *vcpu)
अणु
	preempt_disable();
	kvm_arm_setup_mdcr_el2(vcpu);
	preempt_enable();
पूर्ण

/**
 * kvm_arm_reset_debug_ptr - reset the debug ptr to poपूर्णांक to the vcpu state
 */

व्योम kvm_arm_reset_debug_ptr(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.debug_ptr = &vcpu->arch.vcpu_debug_state;
पूर्ण

/**
 * kvm_arm_setup_debug - set up debug related stuff
 *
 * @vcpu:	the vcpu poपूर्णांकer
 *
 * This is called beक्रमe each entry पूर्णांकo the hypervisor to setup any
 * debug related रेजिस्टरs.
 *
 * Additionally, KVM only traps guest accesses to the debug रेजिस्टरs अगर
 * the guest is not actively using them (see the KVM_ARM64_DEBUG_सूचीTY
 * flag on vcpu->arch.flags).  Since the guest must not पूर्णांकerfere
 * with the hardware state when debugging the guest, we must ensure that
 * trapping is enabled whenever we are debugging the guest using the
 * debug रेजिस्टरs.
 */

व्योम kvm_arm_setup_debug(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ mdscr, orig_mdcr_el2 = vcpu->arch.mdcr_el2;

	trace_kvm_arm_setup_debug(vcpu, vcpu->guest_debug);

	kvm_arm_setup_mdcr_el2(vcpu);

	/* Is Guest debugging in effect? */
	अगर (vcpu->guest_debug) अणु
		/* Save guest debug state */
		save_guest_debug_regs(vcpu);

		/*
		 * Single Step (ARM ARM D2.12.3 The software step state
		 * machine)
		 *
		 * If we are करोing Single Step we need to manipulate
		 * the guest's MDSCR_EL1.SS and PSTATE.SS. Once the
		 * step has occurred the hypervisor will trap the
		 * debug exception and we वापस to userspace.
		 *
		 * If the guest attempts to single step its userspace
		 * we would have to deal with a trapped exception
		 * जबतक in the guest kernel. Because this would be
		 * hard to unwind we suppress the guest's ability to
		 * करो so by masking MDSCR_EL.SS.
		 *
		 * This confuses guest debuggers which use
		 * single-step behind the scenes but everything
		 * वापसs to normal once the host is no दीर्घer
		 * debugging the प्रणाली.
		 */
		अगर (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP) अणु
			*vcpu_cpsr(vcpu) |=  DBG_SPSR_SS;
			mdscr = vcpu_पढ़ो_sys_reg(vcpu, MDSCR_EL1);
			mdscr |= DBG_MDSCR_SS;
			vcpu_ग_लिखो_sys_reg(vcpu, mdscr, MDSCR_EL1);
		पूर्ण अन्यथा अणु
			mdscr = vcpu_पढ़ो_sys_reg(vcpu, MDSCR_EL1);
			mdscr &= ~DBG_MDSCR_SS;
			vcpu_ग_लिखो_sys_reg(vcpu, mdscr, MDSCR_EL1);
		पूर्ण

		trace_kvm_arm_set_dreg32("SPSR_EL2", *vcpu_cpsr(vcpu));

		/*
		 * HW Breakpoपूर्णांकs and watchpoपूर्णांकs
		 *
		 * We simply चयन the debug_ptr to poपूर्णांक to our new
		 * बाह्यal_debug_state which has been populated by the
		 * debug ioctl. The existing KVM_ARM64_DEBUG_सूचीTY
		 * mechanism ensures the रेजिस्टरs are updated on the
		 * world चयन.
		 */
		अगर (vcpu->guest_debug & KVM_GUESTDBG_USE_HW) अणु
			/* Enable अवरोधpoपूर्णांकs/watchpoपूर्णांकs */
			mdscr = vcpu_पढ़ो_sys_reg(vcpu, MDSCR_EL1);
			mdscr |= DBG_MDSCR_MDE;
			vcpu_ग_लिखो_sys_reg(vcpu, mdscr, MDSCR_EL1);

			vcpu->arch.debug_ptr = &vcpu->arch.बाह्यal_debug_state;
			vcpu->arch.flags |= KVM_ARM64_DEBUG_सूचीTY;

			trace_kvm_arm_set_regset("BKPTS", get_num_brps(),
						&vcpu->arch.debug_ptr->dbg_bcr[0],
						&vcpu->arch.debug_ptr->dbg_bvr[0]);

			trace_kvm_arm_set_regset("WAPTS", get_num_wrps(),
						&vcpu->arch.debug_ptr->dbg_wcr[0],
						&vcpu->arch.debug_ptr->dbg_wvr[0]);
		पूर्ण
	पूर्ण

	BUG_ON(!vcpu->guest_debug &&
		vcpu->arch.debug_ptr != &vcpu->arch.vcpu_debug_state);

	/* If KDE or MDE are set, perक्रमm a full save/restore cycle. */
	अगर (vcpu_पढ़ो_sys_reg(vcpu, MDSCR_EL1) & (DBG_MDSCR_KDE | DBG_MDSCR_MDE))
		vcpu->arch.flags |= KVM_ARM64_DEBUG_सूचीTY;

	/* Write mdcr_el2 changes since vcpu_load on VHE प्रणालीs */
	अगर (has_vhe() && orig_mdcr_el2 != vcpu->arch.mdcr_el2)
		ग_लिखो_sysreg(vcpu->arch.mdcr_el2, mdcr_el2);

	trace_kvm_arm_set_dreg32("MDSCR_EL1", vcpu_पढ़ो_sys_reg(vcpu, MDSCR_EL1));
पूर्ण

व्योम kvm_arm_clear_debug(काष्ठा kvm_vcpu *vcpu)
अणु
	trace_kvm_arm_clear_debug(vcpu->guest_debug);

	अगर (vcpu->guest_debug) अणु
		restore_guest_debug_regs(vcpu);

		/*
		 * If we were using HW debug we need to restore the
		 * debug_ptr to the guest debug state.
		 */
		अगर (vcpu->guest_debug & KVM_GUESTDBG_USE_HW) अणु
			kvm_arm_reset_debug_ptr(vcpu);

			trace_kvm_arm_set_regset("BKPTS", get_num_brps(),
						&vcpu->arch.debug_ptr->dbg_bcr[0],
						&vcpu->arch.debug_ptr->dbg_bvr[0]);

			trace_kvm_arm_set_regset("WAPTS", get_num_wrps(),
						&vcpu->arch.debug_ptr->dbg_wcr[0],
						&vcpu->arch.debug_ptr->dbg_wvr[0]);
		पूर्ण
	पूर्ण
पूर्ण

व्योम kvm_arch_vcpu_load_debug_state_flags(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 dfr0;

	/* For VHE, there is nothing to करो */
	अगर (has_vhe())
		वापस;

	dfr0 = पढ़ो_sysreg(id_aa64dfr0_el1);
	/*
	 * If SPE is present on this CPU and is available at current EL,
	 * we may need to check अगर the host state needs to be saved.
	 */
	अगर (cpuid_feature_extract_अचिन्हित_field(dfr0, ID_AA64DFR0_PMSVER_SHIFT) &&
	    !(पढ़ो_sysreg_s(SYS_PMBIDR_EL1) & BIT(SYS_PMBIDR_EL1_P_SHIFT)))
		vcpu->arch.flags |= KVM_ARM64_DEBUG_STATE_SAVE_SPE;

	/* Check अगर we have TRBE implemented and available at the host */
	अगर (cpuid_feature_extract_अचिन्हित_field(dfr0, ID_AA64DFR0_TRBE_SHIFT) &&
	    !(पढ़ो_sysreg_s(SYS_TRBIDR_EL1) & TRBIDR_PROG))
		vcpu->arch.flags |= KVM_ARM64_DEBUG_STATE_SAVE_TRBE;
पूर्ण

व्योम kvm_arch_vcpu_put_debug_state_flags(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.flags &= ~(KVM_ARM64_DEBUG_STATE_SAVE_SPE |
			      KVM_ARM64_DEBUG_STATE_SAVE_TRBE);
पूर्ण
