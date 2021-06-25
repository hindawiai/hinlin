<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <hyp/sysreg-sr.h>

#समावेश <linux/compiler.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_hyp.h>

/*
 * VHE: Host and guest must save mdscr_el1 and sp_el0 (and the PC and
 * pstate, which are handled as part of the el2 वापस state) on every
 * चयन (sp_el0 is being dealt with in the assembly code).
 * tpidr_el0 and tpidrro_el0 only need to be चयनed when going
 * to host userspace or a dअगरferent VCPU.  EL1 रेजिस्टरs only need to be
 * चयनed when potentially going to run a dअगरferent VCPU.  The latter two
 * classes are handled as part of kvm_arch_vcpu_load and kvm_arch_vcpu_put.
 */

व्योम sysreg_save_host_state_vhe(काष्ठा kvm_cpu_context *ctxt)
अणु
	__sysreg_save_common_state(ctxt);
पूर्ण
NOKPROBE_SYMBOL(sysreg_save_host_state_vhe);

व्योम sysreg_save_guest_state_vhe(काष्ठा kvm_cpu_context *ctxt)
अणु
	__sysreg_save_common_state(ctxt);
	__sysreg_save_el2_वापस_state(ctxt);
पूर्ण
NOKPROBE_SYMBOL(sysreg_save_guest_state_vhe);

व्योम sysreg_restore_host_state_vhe(काष्ठा kvm_cpu_context *ctxt)
अणु
	__sysreg_restore_common_state(ctxt);
पूर्ण
NOKPROBE_SYMBOL(sysreg_restore_host_state_vhe);

व्योम sysreg_restore_guest_state_vhe(काष्ठा kvm_cpu_context *ctxt)
अणु
	__sysreg_restore_common_state(ctxt);
	__sysreg_restore_el2_वापस_state(ctxt);
पूर्ण
NOKPROBE_SYMBOL(sysreg_restore_guest_state_vhe);

/**
 * kvm_vcpu_load_sysregs_vhe - Load guest प्रणाली रेजिस्टरs to the physical CPU
 *
 * @vcpu: The VCPU poपूर्णांकer
 *
 * Load प्रणाली रेजिस्टरs that करो not affect the host's execution, क्रम
 * example EL1 प्रणाली रेजिस्टरs on a VHE प्रणाली where the host kernel
 * runs at EL2.  This function is called from KVM's vcpu_load() function
 * and loading प्रणाली रेजिस्टर state early aव्योमs having to load them on
 * every entry to the VM.
 */
व्योम kvm_vcpu_load_sysregs_vhe(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpu_context *guest_ctxt = &vcpu->arch.ctxt;
	काष्ठा kvm_cpu_context *host_ctxt;

	host_ctxt = &this_cpu_ptr(&kvm_host_data)->host_ctxt;
	__sysreg_save_user_state(host_ctxt);

	/*
	 * Load guest EL1 and user state
	 *
	 * We must restore the 32-bit state beक्रमe the sysregs, thanks
	 * to erratum #852523 (Cortex-A57) or #853709 (Cortex-A72).
	 */
	__sysreg32_restore_state(vcpu);
	__sysreg_restore_user_state(guest_ctxt);
	__sysreg_restore_el1_state(guest_ctxt);

	vcpu->arch.sysregs_loaded_on_cpu = true;

	activate_traps_vhe_load(vcpu);
पूर्ण

/**
 * kvm_vcpu_put_sysregs_vhe - Restore host प्रणाली रेजिस्टरs to the physical CPU
 *
 * @vcpu: The VCPU poपूर्णांकer
 *
 * Save guest प्रणाली रेजिस्टरs that करो not affect the host's execution, क्रम
 * example EL1 प्रणाली रेजिस्टरs on a VHE प्रणाली where the host kernel
 * runs at EL2.  This function is called from KVM's vcpu_put() function
 * and deferring saving प्रणाली रेजिस्टर state until we're no दीर्घer running the
 * VCPU aव्योमs having to save them on every निकास from the VM.
 */
व्योम kvm_vcpu_put_sysregs_vhe(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpu_context *guest_ctxt = &vcpu->arch.ctxt;
	काष्ठा kvm_cpu_context *host_ctxt;

	host_ctxt = &this_cpu_ptr(&kvm_host_data)->host_ctxt;
	deactivate_traps_vhe_put();

	__sysreg_save_el1_state(guest_ctxt);
	__sysreg_save_user_state(guest_ctxt);
	__sysreg32_save_state(vcpu);

	/* Restore host user state */
	__sysreg_restore_user_state(host_ctxt);

	vcpu->arch.sysregs_loaded_on_cpu = false;
पूर्ण
