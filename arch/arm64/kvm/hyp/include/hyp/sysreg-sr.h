<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __ARM64_KVM_HYP_SYSREG_SR_H__
#घोषणा __ARM64_KVM_HYP_SYSREG_SR_H__

#समावेश <linux/compiler.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_hyp.h>

अटल अंतरभूत व्योम __sysreg_save_common_state(काष्ठा kvm_cpu_context *ctxt)
अणु
	ctxt_sys_reg(ctxt, MDSCR_EL1)	= पढ़ो_sysreg(mdscr_el1);
पूर्ण

अटल अंतरभूत व्योम __sysreg_save_user_state(काष्ठा kvm_cpu_context *ctxt)
अणु
	ctxt_sys_reg(ctxt, TPIDR_EL0)	= पढ़ो_sysreg(tpidr_el0);
	ctxt_sys_reg(ctxt, TPIDRRO_EL0)	= पढ़ो_sysreg(tpidrro_el0);
पूर्ण

अटल अंतरभूत व्योम __sysreg_save_el1_state(काष्ठा kvm_cpu_context *ctxt)
अणु
	ctxt_sys_reg(ctxt, CSSELR_EL1)	= पढ़ो_sysreg(csselr_el1);
	ctxt_sys_reg(ctxt, SCTLR_EL1)	= पढ़ो_sysreg_el1(SYS_SCTLR);
	ctxt_sys_reg(ctxt, CPACR_EL1)	= पढ़ो_sysreg_el1(SYS_CPACR);
	ctxt_sys_reg(ctxt, TTBR0_EL1)	= पढ़ो_sysreg_el1(SYS_TTBR0);
	ctxt_sys_reg(ctxt, TTBR1_EL1)	= पढ़ो_sysreg_el1(SYS_TTBR1);
	ctxt_sys_reg(ctxt, TCR_EL1)	= पढ़ो_sysreg_el1(SYS_TCR);
	ctxt_sys_reg(ctxt, ESR_EL1)	= पढ़ो_sysreg_el1(SYS_ESR);
	ctxt_sys_reg(ctxt, AFSR0_EL1)	= पढ़ो_sysreg_el1(SYS_AFSR0);
	ctxt_sys_reg(ctxt, AFSR1_EL1)	= पढ़ो_sysreg_el1(SYS_AFSR1);
	ctxt_sys_reg(ctxt, FAR_EL1)	= पढ़ो_sysreg_el1(SYS_FAR);
	ctxt_sys_reg(ctxt, MAIR_EL1)	= पढ़ो_sysreg_el1(SYS_MAIR);
	ctxt_sys_reg(ctxt, VBAR_EL1)	= पढ़ो_sysreg_el1(SYS_VBAR);
	ctxt_sys_reg(ctxt, CONTEXTIDR_EL1) = पढ़ो_sysreg_el1(SYS_CONTEXTIDR);
	ctxt_sys_reg(ctxt, AMAIR_EL1)	= पढ़ो_sysreg_el1(SYS_AMAIR);
	ctxt_sys_reg(ctxt, CNTKCTL_EL1)	= पढ़ो_sysreg_el1(SYS_CNTKCTL);
	ctxt_sys_reg(ctxt, PAR_EL1)	= पढ़ो_sysreg_par();
	ctxt_sys_reg(ctxt, TPIDR_EL1)	= पढ़ो_sysreg(tpidr_el1);

	ctxt_sys_reg(ctxt, SP_EL1)	= पढ़ो_sysreg(sp_el1);
	ctxt_sys_reg(ctxt, ELR_EL1)	= पढ़ो_sysreg_el1(SYS_ELR);
	ctxt_sys_reg(ctxt, SPSR_EL1)	= पढ़ो_sysreg_el1(SYS_SPSR);
पूर्ण

अटल अंतरभूत व्योम __sysreg_save_el2_वापस_state(काष्ठा kvm_cpu_context *ctxt)
अणु
	ctxt->regs.pc			= पढ़ो_sysreg_el2(SYS_ELR);
	ctxt->regs.pstate		= पढ़ो_sysreg_el2(SYS_SPSR);

	अगर (cpus_have_final_cap(ARM64_HAS_RAS_EXTN))
		ctxt_sys_reg(ctxt, DISR_EL1) = पढ़ो_sysreg_s(SYS_VDISR_EL2);
पूर्ण

अटल अंतरभूत व्योम __sysreg_restore_common_state(काष्ठा kvm_cpu_context *ctxt)
अणु
	ग_लिखो_sysreg(ctxt_sys_reg(ctxt, MDSCR_EL1),  mdscr_el1);
पूर्ण

अटल अंतरभूत व्योम __sysreg_restore_user_state(काष्ठा kvm_cpu_context *ctxt)
अणु
	ग_लिखो_sysreg(ctxt_sys_reg(ctxt, TPIDR_EL0),	tpidr_el0);
	ग_लिखो_sysreg(ctxt_sys_reg(ctxt, TPIDRRO_EL0),	tpidrro_el0);
पूर्ण

अटल अंतरभूत व्योम __sysreg_restore_el1_state(काष्ठा kvm_cpu_context *ctxt)
अणु
	ग_लिखो_sysreg(ctxt_sys_reg(ctxt, MPIDR_EL1),	vmpidr_el2);
	ग_लिखो_sysreg(ctxt_sys_reg(ctxt, CSSELR_EL1),	csselr_el1);

	अगर (has_vhe() ||
	    !cpus_have_final_cap(ARM64_WORKAROUND_SPECULATIVE_AT)) अणु
		ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, SCTLR_EL1),	SYS_SCTLR);
		ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, TCR_EL1),	SYS_TCR);
	पूर्ण अन्यथा	अगर (!ctxt->__hyp_running_vcpu) अणु
		/*
		 * Must only be करोne क्रम guest रेजिस्टरs, hence the context
		 * test. We're coming from the host, so SCTLR.M is alपढ़ोy
		 * set. Pairs with nVHE's __activate_traps().
		 */
		ग_लिखो_sysreg_el1((ctxt_sys_reg(ctxt, TCR_EL1) |
				  TCR_EPD1_MASK | TCR_EPD0_MASK),
				 SYS_TCR);
		isb();
	पूर्ण

	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, CPACR_EL1),	SYS_CPACR);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, TTBR0_EL1),	SYS_TTBR0);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, TTBR1_EL1),	SYS_TTBR1);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, ESR_EL1),	SYS_ESR);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, AFSR0_EL1),	SYS_AFSR0);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, AFSR1_EL1),	SYS_AFSR1);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, FAR_EL1),	SYS_FAR);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, MAIR_EL1),	SYS_MAIR);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, VBAR_EL1),	SYS_VBAR);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, CONTEXTIDR_EL1), SYS_CONTEXTIDR);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, AMAIR_EL1),	SYS_AMAIR);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, CNTKCTL_EL1), SYS_CNTKCTL);
	ग_लिखो_sysreg(ctxt_sys_reg(ctxt, PAR_EL1),	par_el1);
	ग_लिखो_sysreg(ctxt_sys_reg(ctxt, TPIDR_EL1),	tpidr_el1);

	अगर (!has_vhe() &&
	    cpus_have_final_cap(ARM64_WORKAROUND_SPECULATIVE_AT) &&
	    ctxt->__hyp_running_vcpu) अणु
		/*
		 * Must only be करोne क्रम host रेजिस्टरs, hence the context
		 * test. Pairs with nVHE's __deactivate_traps().
		 */
		isb();
		/*
		 * At this stage, and thanks to the above isb(), S2 is
		 * deconfigured and disabled. We can now restore the host's
		 * S1 configuration: SCTLR, and only then TCR.
		 */
		ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, SCTLR_EL1),	SYS_SCTLR);
		isb();
		ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, TCR_EL1),	SYS_TCR);
	पूर्ण

	ग_लिखो_sysreg(ctxt_sys_reg(ctxt, SP_EL1),	sp_el1);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, ELR_EL1),	SYS_ELR);
	ग_लिखो_sysreg_el1(ctxt_sys_reg(ctxt, SPSR_EL1),	SYS_SPSR);
पूर्ण

अटल अंतरभूत व्योम __sysreg_restore_el2_वापस_state(काष्ठा kvm_cpu_context *ctxt)
अणु
	u64 pstate = ctxt->regs.pstate;
	u64 mode = pstate & PSR_AA32_MODE_MASK;

	/*
	 * Safety check to ensure we're setting the CPU up to enter the guest
	 * in a less privileged mode.
	 *
	 * If we are attempting a वापस to EL2 or higher in AArch64 state,
	 * program SPSR_EL2 with M=EL2h and the IL bit set which ensures that
	 * we'll take an illegal exception state exception immediately after
	 * the ERET to the guest.  Attempts to वापस to AArch32 Hyp will
	 * result in an illegal exception वापस because EL2's execution state
	 * is determined by SCR_EL3.RW.
	 */
	अगर (!(mode & PSR_MODE32_BIT) && mode >= PSR_MODE_EL2t)
		pstate = PSR_MODE_EL2h | PSR_IL_BIT;

	ग_लिखो_sysreg_el2(ctxt->regs.pc,			SYS_ELR);
	ग_लिखो_sysreg_el2(pstate,			SYS_SPSR);

	अगर (cpus_have_final_cap(ARM64_HAS_RAS_EXTN))
		ग_लिखो_sysreg_s(ctxt_sys_reg(ctxt, DISR_EL1), SYS_VDISR_EL2);
पूर्ण

अटल अंतरभूत व्योम __sysreg32_save_state(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!vcpu_el1_is_32bit(vcpu))
		वापस;

	vcpu->arch.ctxt.spsr_abt = पढ़ो_sysreg(spsr_abt);
	vcpu->arch.ctxt.spsr_und = पढ़ो_sysreg(spsr_und);
	vcpu->arch.ctxt.spsr_irq = पढ़ो_sysreg(spsr_irq);
	vcpu->arch.ctxt.spsr_fiq = पढ़ो_sysreg(spsr_fiq);

	__vcpu_sys_reg(vcpu, DACR32_EL2) = पढ़ो_sysreg(dacr32_el2);
	__vcpu_sys_reg(vcpu, IFSR32_EL2) = पढ़ो_sysreg(अगरsr32_el2);

	अगर (has_vhe() || vcpu->arch.flags & KVM_ARM64_DEBUG_सूचीTY)
		__vcpu_sys_reg(vcpu, DBGVCR32_EL2) = पढ़ो_sysreg(dbgvcr32_el2);
पूर्ण

अटल अंतरभूत व्योम __sysreg32_restore_state(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!vcpu_el1_is_32bit(vcpu))
		वापस;

	ग_लिखो_sysreg(vcpu->arch.ctxt.spsr_abt, spsr_abt);
	ग_लिखो_sysreg(vcpu->arch.ctxt.spsr_und, spsr_und);
	ग_लिखो_sysreg(vcpu->arch.ctxt.spsr_irq, spsr_irq);
	ग_लिखो_sysreg(vcpu->arch.ctxt.spsr_fiq, spsr_fiq);

	ग_लिखो_sysreg(__vcpu_sys_reg(vcpu, DACR32_EL2), dacr32_el2);
	ग_लिखो_sysreg(__vcpu_sys_reg(vcpu, IFSR32_EL2), अगरsr32_el2);

	अगर (has_vhe() || vcpu->arch.flags & KVM_ARM64_DEBUG_सूचीTY)
		ग_लिखो_sysreg(__vcpu_sys_reg(vcpu, DBGVCR32_EL2), dbgvcr32_el2);
पूर्ण

#पूर्ण_अगर /* __ARM64_KVM_HYP_SYSREG_SR_H__ */
