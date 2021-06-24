<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Derived from arch/arm/kvm/handle_निकास.c:
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/esr.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/traps.h>

#समावेश <kvm/arm_hypercalls.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace_handle_exit.h"

प्रकार पूर्णांक (*निकास_handle_fn)(काष्ठा kvm_vcpu *);

अटल व्योम kvm_handle_guest_serror(काष्ठा kvm_vcpu *vcpu, u32 esr)
अणु
	अगर (!arm64_is_ras_serror(esr) || arm64_is_fatal_ras_serror(शून्य, esr))
		kvm_inject_vabt(vcpu);
पूर्ण

अटल पूर्णांक handle_hvc(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret;

	trace_kvm_hvc_arm64(*vcpu_pc(vcpu), vcpu_get_reg(vcpu, 0),
			    kvm_vcpu_hvc_get_imm(vcpu));
	vcpu->स्थिति.सvc_निकास_stat++;

	ret = kvm_hvc_call_handler(vcpu);
	अगर (ret < 0) अणु
		vcpu_set_reg(vcpu, 0, ~0UL);
		वापस 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक handle_smc(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * "If an SMC inकाष्ठाion executed at Non-secure EL1 is
	 * trapped to EL2 because HCR_EL2.TSC is 1, the exception is a
	 * Trap exception, not a Secure Monitor Call exception [...]"
	 *
	 * We need to advance the PC after the trap, as it would
	 * otherwise वापस to the same address...
	 */
	vcpu_set_reg(vcpu, 0, ~0UL);
	kvm_incr_pc(vcpu);
	वापस 1;
पूर्ण

/*
 * Guest access to FP/ASIMD रेजिस्टरs are routed to this handler only
 * when the प्रणाली करोesn't support FP/ASIMD.
 */
अटल पूर्णांक handle_no_fpsimd(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_inject_undefined(vcpu);
	वापस 1;
पूर्ण

/**
 * kvm_handle_wfx - handle a रुको-क्रम-पूर्णांकerrupts or रुको-क्रम-event
 *		    inकाष्ठाion executed by a guest
 *
 * @vcpu:	the vcpu poपूर्णांकer
 *
 * WFE: Yield the CPU and come back to this vcpu when the scheduler
 * decides to.
 * WFI: Simply call kvm_vcpu_block(), which will halt execution of
 * world-चयनes and schedule other host processes until there is an
 * incoming IRQ or FIQ to the VM.
 */
अटल पूर्णांक kvm_handle_wfx(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (kvm_vcpu_get_esr(vcpu) & ESR_ELx_WFx_ISS_WFE) अणु
		trace_kvm_wfx_arm64(*vcpu_pc(vcpu), true);
		vcpu->stat.wfe_निकास_stat++;
		kvm_vcpu_on_spin(vcpu, vcpu_mode_priv(vcpu));
	पूर्ण अन्यथा अणु
		trace_kvm_wfx_arm64(*vcpu_pc(vcpu), false);
		vcpu->stat.wfi_निकास_stat++;
		kvm_vcpu_block(vcpu);
		kvm_clear_request(KVM_REQ_UNHALT, vcpu);
	पूर्ण

	kvm_incr_pc(vcpu);

	वापस 1;
पूर्ण

/**
 * kvm_handle_guest_debug - handle a debug exception inकाष्ठाion
 *
 * @vcpu:	the vcpu poपूर्णांकer
 *
 * We route all debug exceptions through the same handler. If both the
 * guest and host are using the same debug facilities it will be up to
 * userspace to re-inject the correct exception क्रम guest delivery.
 *
 * @वापस: 0 (जबतक setting vcpu->run->निकास_reason), -1 क्रम error
 */
अटल पूर्णांक kvm_handle_guest_debug(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	u32 esr = kvm_vcpu_get_esr(vcpu);
	पूर्णांक ret = 0;

	run->निकास_reason = KVM_EXIT_DEBUG;
	run->debug.arch.hsr = esr;

	चयन (ESR_ELx_EC(esr)) अणु
	हाल ESR_ELx_EC_WATCHPT_LOW:
		run->debug.arch.far = vcpu->arch.fault.far_el2;
		fallthrough;
	हाल ESR_ELx_EC_SOFTSTP_LOW:
	हाल ESR_ELx_EC_BREAKPT_LOW:
	हाल ESR_ELx_EC_BKPT32:
	हाल ESR_ELx_EC_BRK64:
		अवरोध;
	शेष:
		kvm_err("%s: un-handled case esr: %#08x\n",
			__func__, (अचिन्हित पूर्णांक) esr);
		ret = -1;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_handle_unknown_ec(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 esr = kvm_vcpu_get_esr(vcpu);

	kvm_pr_unimpl("Unknown exception class: esr: %#08x -- %s\n",
		      esr, esr_get_class_string(esr));

	kvm_inject_undefined(vcpu);
	वापस 1;
पूर्ण

अटल पूर्णांक handle_sve(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Until SVE is supported क्रम guests: */
	kvm_inject_undefined(vcpu);
	वापस 1;
पूर्ण

/*
 * Guest usage of a ptrauth inकाष्ठाion (which the guest EL1 did not turn पूर्णांकo
 * a NOP). If we get here, it is that we didn't fixup ptrauth on निकास, and all
 * that we can करो is give the guest an UNDEF.
 */
अटल पूर्णांक kvm_handle_ptrauth(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_inject_undefined(vcpu);
	वापस 1;
पूर्ण

अटल निकास_handle_fn arm_निकास_handlers[] = अणु
	[0 ... ESR_ELx_EC_MAX]	= kvm_handle_unknown_ec,
	[ESR_ELx_EC_WFx]	= kvm_handle_wfx,
	[ESR_ELx_EC_CP15_32]	= kvm_handle_cp15_32,
	[ESR_ELx_EC_CP15_64]	= kvm_handle_cp15_64,
	[ESR_ELx_EC_CP14_MR]	= kvm_handle_cp14_32,
	[ESR_ELx_EC_CP14_LS]	= kvm_handle_cp14_load_store,
	[ESR_ELx_EC_CP14_64]	= kvm_handle_cp14_64,
	[ESR_ELx_EC_HVC32]	= handle_hvc,
	[ESR_ELx_EC_SMC32]	= handle_smc,
	[ESR_ELx_EC_HVC64]	= handle_hvc,
	[ESR_ELx_EC_SMC64]	= handle_smc,
	[ESR_ELx_EC_SYS64]	= kvm_handle_sys_reg,
	[ESR_ELx_EC_SVE]	= handle_sve,
	[ESR_ELx_EC_IABT_LOW]	= kvm_handle_guest_पात,
	[ESR_ELx_EC_DABT_LOW]	= kvm_handle_guest_पात,
	[ESR_ELx_EC_SOFTSTP_LOW]= kvm_handle_guest_debug,
	[ESR_ELx_EC_WATCHPT_LOW]= kvm_handle_guest_debug,
	[ESR_ELx_EC_BREAKPT_LOW]= kvm_handle_guest_debug,
	[ESR_ELx_EC_BKPT32]	= kvm_handle_guest_debug,
	[ESR_ELx_EC_BRK64]	= kvm_handle_guest_debug,
	[ESR_ELx_EC_FP_ASIMD]	= handle_no_fpsimd,
	[ESR_ELx_EC_PAC]	= kvm_handle_ptrauth,
पूर्ण;

अटल निकास_handle_fn kvm_get_निकास_handler(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 esr = kvm_vcpu_get_esr(vcpu);
	u8 esr_ec = ESR_ELx_EC(esr);

	वापस arm_निकास_handlers[esr_ec];
पूर्ण

/*
 * We may be single-stepping an emulated inकाष्ठाion. If the emulation
 * has been completed in the kernel, we can वापस to userspace with a
 * KVM_EXIT_DEBUG, otherwise userspace needs to complete its
 * emulation first.
 */
अटल पूर्णांक handle_trap_exceptions(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक handled;

	/*
	 * See ARM ARM B1.14.1: "Hyp traps on inकाष्ठाions
	 * that fail their condition code check"
	 */
	अगर (!kvm_condition_valid(vcpu)) अणु
		kvm_incr_pc(vcpu);
		handled = 1;
	पूर्ण अन्यथा अणु
		निकास_handle_fn निकास_handler;

		निकास_handler = kvm_get_निकास_handler(vcpu);
		handled = निकास_handler(vcpu);
	पूर्ण

	वापस handled;
पूर्ण

/*
 * Return > 0 to वापस to guest, < 0 on error, 0 (and set निकास_reason) on
 * proper निकास to userspace.
 */
पूर्णांक handle_निकास(काष्ठा kvm_vcpu *vcpu, पूर्णांक exception_index)
अणु
	काष्ठा kvm_run *run = vcpu->run;

	exception_index = ARM_EXCEPTION_CODE(exception_index);

	चयन (exception_index) अणु
	हाल ARM_EXCEPTION_IRQ:
		वापस 1;
	हाल ARM_EXCEPTION_EL1_SERROR:
		वापस 1;
	हाल ARM_EXCEPTION_TRAP:
		वापस handle_trap_exceptions(vcpu);
	हाल ARM_EXCEPTION_HYP_GONE:
		/*
		 * EL2 has been reset to the hyp-stub. This happens when a guest
		 * is pre-empted by kvm_reboot()'s shutकरोwn call.
		 */
		run->निकास_reason = KVM_EXIT_FAIL_ENTRY;
		वापस 0;
	हाल ARM_EXCEPTION_IL:
		/*
		 * We attempted an illegal exception वापस.  Guest state must
		 * have been corrupted somehow.  Give up.
		 */
		run->निकास_reason = KVM_EXIT_FAIL_ENTRY;
		वापस -EINVAL;
	शेष:
		kvm_pr_unimpl("Unsupported exception type: %d",
			      exception_index);
		run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		वापस 0;
	पूर्ण
पूर्ण

/* For निकास types that need handling beक्रमe we can be preempted */
व्योम handle_निकास_early(काष्ठा kvm_vcpu *vcpu, पूर्णांक exception_index)
अणु
	अगर (ARM_SERROR_PENDING(exception_index)) अणु
		अगर (this_cpu_has_cap(ARM64_HAS_RAS_EXTN)) अणु
			u64 disr = kvm_vcpu_get_disr(vcpu);

			kvm_handle_guest_serror(vcpu, disr_to_esr(disr));
		पूर्ण अन्यथा अणु
			kvm_inject_vabt(vcpu);
		पूर्ण

		वापस;
	पूर्ण

	exception_index = ARM_EXCEPTION_CODE(exception_index);

	अगर (exception_index == ARM_EXCEPTION_EL1_SERROR)
		kvm_handle_guest_serror(vcpu, kvm_vcpu_get_esr(vcpu));
पूर्ण

व्योम __noवापस __cold nvhe_hyp_panic_handler(u64 esr, u64 spsr, u64 elr,
					      u64 par, uपूर्णांकptr_t vcpu,
					      u64 far, u64 hpfar) अणु
	u64 elr_in_kimg = __phys_to_kimg(__hyp_pa(elr));
	u64 hyp_offset = elr_in_kimg - kaslr_offset() - elr;
	u64 mode = spsr & PSR_MODE_MASK;

	/*
	 * The nVHE hyp symbols are not included by kallsyms to aव्योम issues
	 * with aliasing. That means that the symbols cannot be prपूर्णांकed with the
	 * "%pS" क्रमmat specअगरier, so fall back to the vmlinux address अगर
	 * there's no better option.
	 */
	अगर (mode != PSR_MODE_EL2t && mode != PSR_MODE_EL2h) अणु
		kvm_err("Invalid host exception to nVHE hyp!\n");
	पूर्ण अन्यथा अगर (ESR_ELx_EC(esr) == ESR_ELx_EC_BRK64 &&
		   (esr & ESR_ELx_BRK64_ISS_COMMENT_MASK) == BUG_BRK_IMM) अणु
		काष्ठा bug_entry *bug = find_bug(elr_in_kimg);
		स्थिर अक्षर *file = शून्य;
		अचिन्हित पूर्णांक line = 0;

		/* All hyp bugs, including warnings, are treated as fatal. */
		अगर (bug)
			bug_get_file_line(bug, &file, &line);

		अगर (file)
			kvm_err("nVHE hyp BUG at: %s:%u!\n", file, line);
		अन्यथा
			kvm_err("nVHE hyp BUG at: %016llx!\n", elr + hyp_offset);
	पूर्ण अन्यथा अणु
		kvm_err("nVHE hyp panic at: %016llx!\n", elr + hyp_offset);
	पूर्ण

	/*
	 * Hyp has panicked and we're going to handle that by panicking the
	 * kernel. The kernel offset will be revealed in the panic so we're
	 * also safe to reveal the hyp offset as a debugging aid क्रम translating
	 * hyp VAs to vmlinux addresses.
	 */
	kvm_err("Hyp Offset: 0x%llx\n", hyp_offset);

	panic("HYP panic:\nPS:%08llx PC:%016llx ESR:%08llx\nFAR:%016llx HPFAR:%016llx PAR:%016llx\nVCPU:%016lx\n",
	      spsr, elr, esr, far, hpfar, par, vcpu);
पूर्ण
