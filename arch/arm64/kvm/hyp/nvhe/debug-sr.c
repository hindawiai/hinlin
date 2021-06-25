<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <hyp/debug-sr.h>

#समावेश <linux/compiler.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>

अटल व्योम __debug_save_spe(u64 *pmscr_el1)
अणु
	u64 reg;

	/* Clear pmscr in हाल of early वापस */
	*pmscr_el1 = 0;

	/*
	 * At this poपूर्णांक, we know that this CPU implements
	 * SPE and is available to the host.
	 * Check अगर the host is actually using it ?
	 */
	reg = पढ़ो_sysreg_s(SYS_PMBLIMITR_EL1);
	अगर (!(reg & BIT(SYS_PMBLIMITR_EL1_E_SHIFT)))
		वापस;

	/* Yes; save the control रेजिस्टर and disable data generation */
	*pmscr_el1 = पढ़ो_sysreg_s(SYS_PMSCR_EL1);
	ग_लिखो_sysreg_s(0, SYS_PMSCR_EL1);
	isb();

	/* Now drain all buffered data to memory */
	psb_csync();
	dsb(nsh);
पूर्ण

अटल व्योम __debug_restore_spe(u64 pmscr_el1)
अणु
	अगर (!pmscr_el1)
		वापस;

	/* The host page table is installed, but not yet synchronised */
	isb();

	/* Re-enable data generation */
	ग_लिखो_sysreg_s(pmscr_el1, SYS_PMSCR_EL1);
पूर्ण

अटल व्योम __debug_save_trace(u64 *trfcr_el1)
अणु
	*trfcr_el1 = 0;

	/* Check अगर the TRBE is enabled */
	अगर (!(पढ़ो_sysreg_s(SYS_TRBLIMITR_EL1) & TRBLIMITR_ENABLE))
		वापस;
	/*
	 * Prohibit trace generation जबतक we are in guest.
	 * Since access to TRFCR_EL1 is trapped, the guest can't
	 * modअगरy the filtering set by the host.
	 */
	*trfcr_el1 = पढ़ो_sysreg_s(SYS_TRFCR_EL1);
	ग_लिखो_sysreg_s(0, SYS_TRFCR_EL1);
	isb();
	/* Drain the trace buffer to memory */
	tsb_csync();
	dsb(nsh);
पूर्ण

अटल व्योम __debug_restore_trace(u64 trfcr_el1)
अणु
	अगर (!trfcr_el1)
		वापस;

	/* Restore trace filter controls */
	ग_लिखो_sysreg_s(trfcr_el1, SYS_TRFCR_EL1);
पूर्ण

व्योम __debug_save_host_buffers_nvhe(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Disable and flush SPE data generation */
	अगर (vcpu->arch.flags & KVM_ARM64_DEBUG_STATE_SAVE_SPE)
		__debug_save_spe(&vcpu->arch.host_debug_state.pmscr_el1);
	/* Disable and flush Self-Hosted Trace generation */
	अगर (vcpu->arch.flags & KVM_ARM64_DEBUG_STATE_SAVE_TRBE)
		__debug_save_trace(&vcpu->arch.host_debug_state.trfcr_el1);
पूर्ण

व्योम __debug_चयन_to_guest(काष्ठा kvm_vcpu *vcpu)
अणु
	__debug_चयन_to_guest_common(vcpu);
पूर्ण

व्योम __debug_restore_host_buffers_nvhe(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.flags & KVM_ARM64_DEBUG_STATE_SAVE_SPE)
		__debug_restore_spe(vcpu->arch.host_debug_state.pmscr_el1);
	अगर (vcpu->arch.flags & KVM_ARM64_DEBUG_STATE_SAVE_TRBE)
		__debug_restore_trace(vcpu->arch.host_debug_state.trfcr_el1);
पूर्ण

व्योम __debug_चयन_to_host(काष्ठा kvm_vcpu *vcpu)
अणु
	__debug_चयन_to_host_common(vcpu);
पूर्ण

u32 __kvm_get_mdcr_el2(व्योम)
अणु
	वापस पढ़ो_sysreg(mdcr_el2);
पूर्ण
