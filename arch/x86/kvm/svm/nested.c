<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel-based Virtual Machine driver क्रम Linux
 *
 * AMD SVM support
 *
 * Copyright (C) 2006 Qumranet, Inc.
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 *
 * Authors:
 *   Yaniv Kamay  <yaniv@qumranet.com>
 *   Avi Kivity   <avi@qumranet.com>
 */

#घोषणा pr_fmt(fmt) "SVM: " fmt

#समावेश <linux/kvm_types.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/msr-index.h>
#समावेश <यंत्र/debugreg.h>

#समावेश "kvm_emulate.h"
#समावेश "trace.h"
#समावेश "mmu.h"
#समावेश "x86.h"
#समावेश "cpuid.h"
#समावेश "lapic.h"
#समावेश "svm.h"

#घोषणा CC KVM_NESTED_VMENTER_CONSISTENCY_CHECK

अटल व्योम nested_svm_inject_npf_निकास(काष्ठा kvm_vcpu *vcpu,
				       काष्ठा x86_exception *fault)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (svm->vmcb->control.निकास_code != SVM_EXIT_NPF) अणु
		/*
		 * TODO: track the cause of the nested page fault, and
		 * correctly fill in the high bits of निकास_info_1.
		 */
		svm->vmcb->control.निकास_code = SVM_EXIT_NPF;
		svm->vmcb->control.निकास_code_hi = 0;
		svm->vmcb->control.निकास_info_1 = (1ULL << 32);
		svm->vmcb->control.निकास_info_2 = fault->address;
	पूर्ण

	svm->vmcb->control.निकास_info_1 &= ~0xffffffffULL;
	svm->vmcb->control.निकास_info_1 |= fault->error_code;

	nested_svm_vmनिकास(svm);
पूर्ण

अटल व्योम svm_inject_page_fault_nested(काष्ठा kvm_vcpu *vcpu, काष्ठा x86_exception *fault)
अणु
       काष्ठा vcpu_svm *svm = to_svm(vcpu);
       WARN_ON(!is_guest_mode(vcpu));

       अगर (vmcb_is_पूर्णांकercept(&svm->nested.ctl, INTERCEPT_EXCEPTION_OFFSET + PF_VECTOR) &&
	   !svm->nested.nested_run_pending) अणु
               svm->vmcb->control.निकास_code = SVM_EXIT_EXCP_BASE + PF_VECTOR;
               svm->vmcb->control.निकास_code_hi = 0;
               svm->vmcb->control.निकास_info_1 = fault->error_code;
               svm->vmcb->control.निकास_info_2 = fault->address;
               nested_svm_vmनिकास(svm);
       पूर्ण अन्यथा अणु
               kvm_inject_page_fault(vcpu, fault);
       पूर्ण
पूर्ण

अटल u64 nested_svm_get_tdp_pdptr(काष्ठा kvm_vcpu *vcpu, पूर्णांक index)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u64 cr3 = svm->nested.ctl.nested_cr3;
	u64 pdpte;
	पूर्णांक ret;

	ret = kvm_vcpu_पढ़ो_guest_page(vcpu, gpa_to_gfn(cr3), &pdpte,
				       offset_in_page(cr3) + index * 8, 8);
	अगर (ret)
		वापस 0;
	वापस pdpte;
पूर्ण

अटल अचिन्हित दीर्घ nested_svm_get_tdp_cr3(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	वापस svm->nested.ctl.nested_cr3;
पूर्ण

अटल व्योम nested_svm_init_mmu_context(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	WARN_ON(mmu_is_nested(vcpu));

	vcpu->arch.mmu = &vcpu->arch.guest_mmu;
	kvm_init_shaकरोw_npt_mmu(vcpu, X86_CR0_PG, svm->vmcb01.ptr->save.cr4,
				svm->vmcb01.ptr->save.efer,
				svm->nested.ctl.nested_cr3);
	vcpu->arch.mmu->get_guest_pgd     = nested_svm_get_tdp_cr3;
	vcpu->arch.mmu->get_pdptr         = nested_svm_get_tdp_pdptr;
	vcpu->arch.mmu->inject_page_fault = nested_svm_inject_npf_निकास;
	reset_shaकरोw_zero_bits_mask(vcpu, vcpu->arch.mmu);
	vcpu->arch.walk_mmu              = &vcpu->arch.nested_mmu;
पूर्ण

अटल व्योम nested_svm_uninit_mmu_context(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.mmu = &vcpu->arch.root_mmu;
	vcpu->arch.walk_mmu = &vcpu->arch.root_mmu;
पूर्ण

व्योम recalc_पूर्णांकercepts(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा vmcb_control_area *c, *h, *g;
	अचिन्हित पूर्णांक i;

	vmcb_mark_dirty(svm->vmcb, VMCB_INTERCEPTS);

	अगर (!is_guest_mode(&svm->vcpu))
		वापस;

	c = &svm->vmcb->control;
	h = &svm->vmcb01.ptr->control;
	g = &svm->nested.ctl;

	क्रम (i = 0; i < MAX_INTERCEPT; i++)
		c->पूर्णांकercepts[i] = h->पूर्णांकercepts[i];

	अगर (g->पूर्णांक_ctl & V_INTR_MASKING_MASK) अणु
		/* We only want the cr8 पूर्णांकercept bits of L1 */
		vmcb_clr_पूर्णांकercept(c, INTERCEPT_CR8_READ);
		vmcb_clr_पूर्णांकercept(c, INTERCEPT_CR8_WRITE);

		/*
		 * Once running L2 with HF_VINTR_MASK, EFLAGS.IF करोes not
		 * affect any पूर्णांकerrupt we may want to inject; thereक्रमe,
		 * पूर्णांकerrupt winकरोw vmनिकासs are irrelevant to L0.
		 */
		vmcb_clr_पूर्णांकercept(c, INTERCEPT_VINTR);
	पूर्ण

	/* We करोn't want to see VMMCALLs from a nested guest */
	vmcb_clr_पूर्णांकercept(c, INTERCEPT_VMMCALL);

	क्रम (i = 0; i < MAX_INTERCEPT; i++)
		c->पूर्णांकercepts[i] |= g->पूर्णांकercepts[i];
पूर्ण

अटल व्योम copy_vmcb_control_area(काष्ठा vmcb_control_area *dst,
				   काष्ठा vmcb_control_area *from)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_INTERCEPT; i++)
		dst->पूर्णांकercepts[i] = from->पूर्णांकercepts[i];

	dst->iopm_base_pa         = from->iopm_base_pa;
	dst->msrpm_base_pa        = from->msrpm_base_pa;
	dst->tsc_offset           = from->tsc_offset;
	/* asid not copied, it is handled manually क्रम svm->vmcb.  */
	dst->tlb_ctl              = from->tlb_ctl;
	dst->पूर्णांक_ctl              = from->पूर्णांक_ctl;
	dst->पूर्णांक_vector           = from->पूर्णांक_vector;
	dst->पूर्णांक_state            = from->पूर्णांक_state;
	dst->निकास_code            = from->निकास_code;
	dst->निकास_code_hi         = from->निकास_code_hi;
	dst->निकास_info_1          = from->निकास_info_1;
	dst->निकास_info_2          = from->निकास_info_2;
	dst->निकास_पूर्णांक_info        = from->निकास_पूर्णांक_info;
	dst->निकास_पूर्णांक_info_err    = from->निकास_पूर्णांक_info_err;
	dst->nested_ctl           = from->nested_ctl;
	dst->event_inj            = from->event_inj;
	dst->event_inj_err        = from->event_inj_err;
	dst->nested_cr3           = from->nested_cr3;
	dst->virt_ext              = from->virt_ext;
	dst->छोड़ो_filter_count   = from->छोड़ो_filter_count;
	dst->छोड़ो_filter_thresh  = from->छोड़ो_filter_thresh;
पूर्ण

अटल bool nested_svm_vmrun_msrpm(काष्ठा vcpu_svm *svm)
अणु
	/*
	 * This function merges the msr permission biपंचांगaps of kvm and the
	 * nested vmcb. It is optimized in that it only merges the parts where
	 * the kvm msr permission biपंचांगap may contain zero bits
	 */
	पूर्णांक i;

	अगर (!(vmcb_is_पूर्णांकercept(&svm->nested.ctl, INTERCEPT_MSR_PROT)))
		वापस true;

	क्रम (i = 0; i < MSRPM_OFFSETS; i++) अणु
		u32 value, p;
		u64 offset;

		अगर (msrpm_offsets[i] == 0xffffffff)
			अवरोध;

		p      = msrpm_offsets[i];
		offset = svm->nested.ctl.msrpm_base_pa + (p * 4);

		अगर (kvm_vcpu_पढ़ो_guest(&svm->vcpu, offset, &value, 4))
			वापस false;

		svm->nested.msrpm[p] = svm->msrpm[p] | value;
	पूर्ण

	svm->vmcb->control.msrpm_base_pa = __sme_set(__pa(svm->nested.msrpm));

	वापस true;
पूर्ण

/*
 * Bits 11:0 of biपंचांगap address are ignored by hardware
 */
अटल bool nested_svm_check_biपंचांगap_pa(काष्ठा kvm_vcpu *vcpu, u64 pa, u32 size)
अणु
	u64 addr = PAGE_ALIGN(pa);

	वापस kvm_vcpu_is_legal_gpa(vcpu, addr) &&
	    kvm_vcpu_is_legal_gpa(vcpu, addr + size - 1);
पूर्ण

अटल bool nested_vmcb_check_controls(काष्ठा kvm_vcpu *vcpu,
				       काष्ठा vmcb_control_area *control)
अणु
	अगर (CC(!vmcb_is_पूर्णांकercept(control, INTERCEPT_VMRUN)))
		वापस false;

	अगर (CC(control->asid == 0))
		वापस false;

	अगर (CC((control->nested_ctl & SVM_NESTED_CTL_NP_ENABLE) && !npt_enabled))
		वापस false;

	अगर (CC(!nested_svm_check_biपंचांगap_pa(vcpu, control->msrpm_base_pa,
					   MSRPM_SIZE)))
		वापस false;
	अगर (CC(!nested_svm_check_biपंचांगap_pa(vcpu, control->iopm_base_pa,
					   IOPM_SIZE)))
		वापस false;

	वापस true;
पूर्ण

अटल bool nested_vmcb_check_cr3_cr4(काष्ठा kvm_vcpu *vcpu,
				      काष्ठा vmcb_save_area *save)
अणु
	/*
	 * These checks are also perक्रमmed by KVM_SET_SREGS,
	 * except that EFER.LMA is not checked by SVM against
	 * CR0.PG && EFER.LME.
	 */
	अगर ((save->efer & EFER_LME) && (save->cr0 & X86_CR0_PG)) अणु
		अगर (CC(!(save->cr4 & X86_CR4_PAE)) ||
		    CC(!(save->cr0 & X86_CR0_PE)) ||
		    CC(kvm_vcpu_is_illegal_gpa(vcpu, save->cr3)))
			वापस false;
	पूर्ण

	अगर (CC(!kvm_is_valid_cr4(vcpu, save->cr4)))
		वापस false;

	वापस true;
पूर्ण

/* Common checks that apply to both L1 and L2 state.  */
अटल bool nested_vmcb_valid_sregs(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा vmcb_save_area *save)
अणु
	/*
	 * FIXME: these should be करोne after copying the fields,
	 * to aव्योम TOC/TOU races.  For these save area checks
	 * the possible damage is limited since kvm_set_cr0 and
	 * kvm_set_cr4 handle failure; EFER_SVME is an exception
	 * so it is क्रमce-set later in nested_prepare_vmcb_save.
	 */
	अगर (CC(!(save->efer & EFER_SVME)))
		वापस false;

	अगर (CC((save->cr0 & X86_CR0_CD) == 0 && (save->cr0 & X86_CR0_NW)) ||
	    CC(save->cr0 & ~0xffffffffULL))
		वापस false;

	अगर (CC(!kvm_dr6_valid(save->dr6)) || CC(!kvm_dr7_valid(save->dr7)))
		वापस false;

	अगर (!nested_vmcb_check_cr3_cr4(vcpu, save))
		वापस false;

	अगर (CC(!kvm_valid_efer(vcpu, save->efer)))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम nested_load_control_from_vmcb12(काष्ठा vcpu_svm *svm,
					    काष्ठा vmcb_control_area *control)
अणु
	copy_vmcb_control_area(&svm->nested.ctl, control);

	/* Copy it here because nested_svm_check_controls will check it.  */
	svm->nested.ctl.asid           = control->asid;
	svm->nested.ctl.msrpm_base_pa &= ~0x0fffULL;
	svm->nested.ctl.iopm_base_pa  &= ~0x0fffULL;
पूर्ण

/*
 * Synchronize fields that are written by the processor, so that
 * they can be copied back पूर्णांकo the vmcb12.
 */
व्योम nested_sync_control_from_vmcb02(काष्ठा vcpu_svm *svm)
अणु
	u32 mask;
	svm->nested.ctl.event_inj      = svm->vmcb->control.event_inj;
	svm->nested.ctl.event_inj_err  = svm->vmcb->control.event_inj_err;

	/* Only a few fields of पूर्णांक_ctl are written by the processor.  */
	mask = V_IRQ_MASK | V_TPR_MASK;
	अगर (!(svm->nested.ctl.पूर्णांक_ctl & V_INTR_MASKING_MASK) &&
	    svm_is_पूर्णांकercept(svm, INTERCEPT_VINTR)) अणु
		/*
		 * In order to request an पूर्णांकerrupt winकरोw, L0 is usurping
		 * svm->vmcb->control.पूर्णांक_ctl and possibly setting V_IRQ
		 * even अगर it was clear in L1's VMCB.  Restoring it would be
		 * wrong.  However, in this हाल V_IRQ will reमुख्य true until
		 * पूर्णांकerrupt_winकरोw_पूर्णांकerception calls svm_clear_vपूर्णांकr and
		 * restores पूर्णांक_ctl.  We can just leave it aside.
		 */
		mask &= ~V_IRQ_MASK;
	पूर्ण
	svm->nested.ctl.पूर्णांक_ctl        &= ~mask;
	svm->nested.ctl.पूर्णांक_ctl        |= svm->vmcb->control.पूर्णांक_ctl & mask;
पूर्ण

/*
 * Transfer any event that L0 or L1 wanted to inject पूर्णांकo L2 to
 * EXIT_INT_INFO.
 */
अटल व्योम nested_save_pending_event_to_vmcb12(काष्ठा vcpu_svm *svm,
						काष्ठा vmcb *vmcb12)
अणु
	काष्ठा kvm_vcpu *vcpu = &svm->vcpu;
	u32 निकास_पूर्णांक_info = 0;
	अचिन्हित पूर्णांक nr;

	अगर (vcpu->arch.exception.injected) अणु
		nr = vcpu->arch.exception.nr;
		निकास_पूर्णांक_info = nr | SVM_EVTINJ_VALID | SVM_EVTINJ_TYPE_EXEPT;

		अगर (vcpu->arch.exception.has_error_code) अणु
			निकास_पूर्णांक_info |= SVM_EVTINJ_VALID_ERR;
			vmcb12->control.निकास_पूर्णांक_info_err =
				vcpu->arch.exception.error_code;
		पूर्ण

	पूर्ण अन्यथा अगर (vcpu->arch.nmi_injected) अणु
		निकास_पूर्णांक_info = SVM_EVTINJ_VALID | SVM_EVTINJ_TYPE_NMI;

	पूर्ण अन्यथा अगर (vcpu->arch.पूर्णांकerrupt.injected) अणु
		nr = vcpu->arch.पूर्णांकerrupt.nr;
		निकास_पूर्णांक_info = nr | SVM_EVTINJ_VALID;

		अगर (vcpu->arch.पूर्णांकerrupt.soft)
			निकास_पूर्णांक_info |= SVM_EVTINJ_TYPE_SOFT;
		अन्यथा
			निकास_पूर्णांक_info |= SVM_EVTINJ_TYPE_INTR;
	पूर्ण

	vmcb12->control.निकास_पूर्णांक_info = निकास_पूर्णांक_info;
पूर्ण

अटल अंतरभूत bool nested_npt_enabled(काष्ठा vcpu_svm *svm)
अणु
	वापस svm->nested.ctl.nested_ctl & SVM_NESTED_CTL_NP_ENABLE;
पूर्ण

/*
 * Load guest's/host's cr3 on nested vmentry or vmनिकास. @nested_npt is true
 * अगर we are emulating VM-Entry पूर्णांकo a guest with NPT enabled.
 */
अटल पूर्णांक nested_svm_load_cr3(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr3,
			       bool nested_npt)
अणु
	अगर (CC(kvm_vcpu_is_illegal_gpa(vcpu, cr3)))
		वापस -EINVAL;

	अगर (!nested_npt && is_pae_paging(vcpu) &&
	    (cr3 != kvm_पढ़ो_cr3(vcpu) || pdptrs_changed(vcpu))) अणु
		अगर (CC(!load_pdptrs(vcpu, vcpu->arch.walk_mmu, cr3)))
			वापस -EINVAL;
	पूर्ण

	/*
	 * TODO: optimize unconditional TLB flush/MMU sync here and in
	 * kvm_init_shaकरोw_npt_mmu().
	 */
	अगर (!nested_npt)
		kvm_mmu_new_pgd(vcpu, cr3, false, false);

	vcpu->arch.cr3 = cr3;
	kvm_रेजिस्टर_mark_available(vcpu, VCPU_EXREG_CR3);

	kvm_init_mmu(vcpu, false);

	वापस 0;
पूर्ण

व्योम nested_vmcb02_compute_g_pat(काष्ठा vcpu_svm *svm)
अणु
	अगर (!svm->nested.vmcb02.ptr)
		वापस;

	/* FIXME: merge g_pat from vmcb01 and vmcb12.  */
	svm->nested.vmcb02.ptr->save.g_pat = svm->vmcb01.ptr->save.g_pat;
पूर्ण

अटल व्योम nested_vmcb02_prepare_save(काष्ठा vcpu_svm *svm, काष्ठा vmcb *vmcb12)
अणु
	bool new_vmcb12 = false;

	nested_vmcb02_compute_g_pat(svm);

	/* Load the nested guest state */
	अगर (svm->nested.vmcb12_gpa != svm->nested.last_vmcb12_gpa) अणु
		new_vmcb12 = true;
		svm->nested.last_vmcb12_gpa = svm->nested.vmcb12_gpa;
	पूर्ण

	अगर (unlikely(new_vmcb12 || vmcb_is_dirty(vmcb12, VMCB_SEG))) अणु
		svm->vmcb->save.es = vmcb12->save.es;
		svm->vmcb->save.cs = vmcb12->save.cs;
		svm->vmcb->save.ss = vmcb12->save.ss;
		svm->vmcb->save.ds = vmcb12->save.ds;
		svm->vmcb->save.cpl = vmcb12->save.cpl;
		vmcb_mark_dirty(svm->vmcb, VMCB_SEG);
	पूर्ण

	अगर (unlikely(new_vmcb12 || vmcb_is_dirty(vmcb12, VMCB_DT))) अणु
		svm->vmcb->save.gdtr = vmcb12->save.gdtr;
		svm->vmcb->save.idtr = vmcb12->save.idtr;
		vmcb_mark_dirty(svm->vmcb, VMCB_DT);
	पूर्ण

	kvm_set_rflags(&svm->vcpu, vmcb12->save.rflags | X86_EFLAGS_FIXED);

	/*
	 * Force-set EFER_SVME even though it is checked earlier on the
	 * VMCB12, because the guest can flip the bit between the check
	 * and now.  Clearing EFER_SVME would call svm_मुक्त_nested.
	 */
	svm_set_efer(&svm->vcpu, vmcb12->save.efer | EFER_SVME);

	svm_set_cr0(&svm->vcpu, vmcb12->save.cr0);
	svm_set_cr4(&svm->vcpu, vmcb12->save.cr4);

	svm->vcpu.arch.cr2 = vmcb12->save.cr2;

	kvm_rax_ग_लिखो(&svm->vcpu, vmcb12->save.rax);
	kvm_rsp_ग_लिखो(&svm->vcpu, vmcb12->save.rsp);
	kvm_rip_ग_लिखो(&svm->vcpu, vmcb12->save.rip);

	/* In हाल we करोn't even reach vcpu_run, the fields are not updated */
	svm->vmcb->save.rax = vmcb12->save.rax;
	svm->vmcb->save.rsp = vmcb12->save.rsp;
	svm->vmcb->save.rip = vmcb12->save.rip;

	/* These bits will be set properly on the first execution when new_vmc12 is true */
	अगर (unlikely(new_vmcb12 || vmcb_is_dirty(vmcb12, VMCB_DR))) अणु
		svm->vmcb->save.dr7 = vmcb12->save.dr7 | DR7_FIXED_1;
		svm->vcpu.arch.dr6  = vmcb12->save.dr6 | DR6_ACTIVE_LOW;
		vmcb_mark_dirty(svm->vmcb, VMCB_DR);
	पूर्ण
पूर्ण

अटल व्योम nested_vmcb02_prepare_control(काष्ठा vcpu_svm *svm)
अणु
	स्थिर u32 mask = V_INTR_MASKING_MASK | V_GIF_ENABLE_MASK | V_GIF_MASK;

	/*
	 * Filled at निकास: निकास_code, निकास_code_hi, निकास_info_1, निकास_info_2,
	 * निकास_पूर्णांक_info, निकास_पूर्णांक_info_err, next_rip, insn_len, insn_bytes.
	 */

	/*
	 * Also covers avic_vapic_bar, avic_backing_page, avic_logical_id,
	 * avic_physical_id.
	 */
	WARN_ON(svm->vmcb01.ptr->control.पूर्णांक_ctl & AVIC_ENABLE_MASK);

	/* Copied from vmcb01.  msrpm_base can be overwritten later.  */
	svm->vmcb->control.nested_ctl = svm->vmcb01.ptr->control.nested_ctl;
	svm->vmcb->control.iopm_base_pa = svm->vmcb01.ptr->control.iopm_base_pa;
	svm->vmcb->control.msrpm_base_pa = svm->vmcb01.ptr->control.msrpm_base_pa;

	/* Done at vmrun: asid.  */

	/* Also overwritten later अगर necessary.  */
	svm->vmcb->control.tlb_ctl = TLB_CONTROL_DO_NOTHING;

	/* nested_cr3.  */
	अगर (nested_npt_enabled(svm))
		nested_svm_init_mmu_context(&svm->vcpu);

	svm->vmcb->control.tsc_offset = svm->vcpu.arch.tsc_offset =
		svm->vcpu.arch.l1_tsc_offset + svm->nested.ctl.tsc_offset;

	svm->vmcb->control.पूर्णांक_ctl             =
		(svm->nested.ctl.पूर्णांक_ctl & ~mask) |
		(svm->vmcb01.ptr->control.पूर्णांक_ctl & mask);

	svm->vmcb->control.virt_ext            = svm->nested.ctl.virt_ext;
	svm->vmcb->control.पूर्णांक_vector          = svm->nested.ctl.पूर्णांक_vector;
	svm->vmcb->control.पूर्णांक_state           = svm->nested.ctl.पूर्णांक_state;
	svm->vmcb->control.event_inj           = svm->nested.ctl.event_inj;
	svm->vmcb->control.event_inj_err       = svm->nested.ctl.event_inj_err;

	svm->vmcb->control.छोड़ो_filter_count  = svm->nested.ctl.छोड़ो_filter_count;
	svm->vmcb->control.छोड़ो_filter_thresh = svm->nested.ctl.छोड़ो_filter_thresh;

	/* Enter Guest-Mode */
	enter_guest_mode(&svm->vcpu);

	/*
	 * Merge guest and host पूर्णांकercepts - must be called with vcpu in
	 * guest-mode to take effect.
	 */
	recalc_पूर्णांकercepts(svm);
पूर्ण

अटल व्योम nested_svm_copy_common_state(काष्ठा vmcb *from_vmcb, काष्ठा vmcb *to_vmcb)
अणु
	/*
	 * Some VMCB state is shared between L1 and L2 and thus has to be
	 * moved at the समय of nested vmrun and vmनिकास.
	 *
	 * VMLOAD/VMSAVE state would also beदीर्घ in this category, but KVM
	 * always perक्रमms VMLOAD and VMSAVE from the VMCB01.
	 */
	to_vmcb->save.spec_ctrl = from_vmcb->save.spec_ctrl;
पूर्ण

पूर्णांक enter_svm_guest_mode(काष्ठा kvm_vcpu *vcpu, u64 vmcb12_gpa,
			 काष्ठा vmcb *vmcb12)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	पूर्णांक ret;

	trace_kvm_nested_vmrun(svm->vmcb->save.rip, vmcb12_gpa,
			       vmcb12->save.rip,
			       vmcb12->control.पूर्णांक_ctl,
			       vmcb12->control.event_inj,
			       vmcb12->control.nested_ctl);

	trace_kvm_nested_पूर्णांकercepts(vmcb12->control.पूर्णांकercepts[INTERCEPT_CR] & 0xffff,
				    vmcb12->control.पूर्णांकercepts[INTERCEPT_CR] >> 16,
				    vmcb12->control.पूर्णांकercepts[INTERCEPT_EXCEPTION],
				    vmcb12->control.पूर्णांकercepts[INTERCEPT_WORD3],
				    vmcb12->control.पूर्णांकercepts[INTERCEPT_WORD4],
				    vmcb12->control.पूर्णांकercepts[INTERCEPT_WORD5]);


	svm->nested.vmcb12_gpa = vmcb12_gpa;

	WARN_ON(svm->vmcb == svm->nested.vmcb02.ptr);

	nested_svm_copy_common_state(svm->vmcb01.ptr, svm->nested.vmcb02.ptr);

	svm_चयन_vmcb(svm, &svm->nested.vmcb02);
	nested_vmcb02_prepare_control(svm);
	nested_vmcb02_prepare_save(svm, vmcb12);

	ret = nested_svm_load_cr3(&svm->vcpu, vmcb12->save.cr3,
				  nested_npt_enabled(svm));
	अगर (ret)
		वापस ret;

	अगर (!npt_enabled)
		vcpu->arch.mmu->inject_page_fault = svm_inject_page_fault_nested;

	svm_set_gअगर(svm, true);

	वापस 0;
पूर्ण

पूर्णांक nested_svm_vmrun(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	पूर्णांक ret;
	काष्ठा vmcb *vmcb12;
	काष्ठा kvm_host_map map;
	u64 vmcb12_gpa;

	++vcpu->stat.nested_run;

	अगर (is_smm(vcpu)) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 1;
	पूर्ण

	vmcb12_gpa = svm->vmcb->save.rax;
	ret = kvm_vcpu_map(vcpu, gpa_to_gfn(vmcb12_gpa), &map);
	अगर (ret == -EINVAL) अणु
		kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण अन्यथा अगर (ret) अणु
		वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
	पूर्ण

	ret = kvm_skip_emulated_inकाष्ठाion(vcpu);

	vmcb12 = map.hva;

	अगर (WARN_ON_ONCE(!svm->nested.initialized))
		वापस -EINVAL;

	nested_load_control_from_vmcb12(svm, &vmcb12->control);

	अगर (!nested_vmcb_valid_sregs(vcpu, &vmcb12->save) ||
	    !nested_vmcb_check_controls(vcpu, &svm->nested.ctl)) अणु
		vmcb12->control.निकास_code    = SVM_EXIT_ERR;
		vmcb12->control.निकास_code_hi = 0;
		vmcb12->control.निकास_info_1  = 0;
		vmcb12->control.निकास_info_2  = 0;
		जाओ out;
	पूर्ण


	/* Clear पूर्णांकernal status */
	kvm_clear_exception_queue(vcpu);
	kvm_clear_पूर्णांकerrupt_queue(vcpu);

	/*
	 * Since vmcb01 is not in use, we can use it to store some of the L1
	 * state.
	 */
	svm->vmcb01.ptr->save.efer   = vcpu->arch.efer;
	svm->vmcb01.ptr->save.cr0    = kvm_पढ़ो_cr0(vcpu);
	svm->vmcb01.ptr->save.cr4    = vcpu->arch.cr4;
	svm->vmcb01.ptr->save.rflags = kvm_get_rflags(vcpu);
	svm->vmcb01.ptr->save.rip    = kvm_rip_पढ़ो(vcpu);

	अगर (!npt_enabled)
		svm->vmcb01.ptr->save.cr3 = kvm_पढ़ो_cr3(vcpu);

	svm->nested.nested_run_pending = 1;

	अगर (enter_svm_guest_mode(vcpu, vmcb12_gpa, vmcb12))
		जाओ out_निकास_err;

	अगर (nested_svm_vmrun_msrpm(svm))
		जाओ out;

out_निकास_err:
	svm->nested.nested_run_pending = 0;

	svm->vmcb->control.निकास_code    = SVM_EXIT_ERR;
	svm->vmcb->control.निकास_code_hi = 0;
	svm->vmcb->control.निकास_info_1  = 0;
	svm->vmcb->control.निकास_info_2  = 0;

	nested_svm_vmनिकास(svm);

out:
	kvm_vcpu_unmap(vcpu, &map, true);

	वापस ret;
पूर्ण

व्योम nested_svm_vmloadsave(काष्ठा vmcb *from_vmcb, काष्ठा vmcb *to_vmcb)
अणु
	to_vmcb->save.fs = from_vmcb->save.fs;
	to_vmcb->save.gs = from_vmcb->save.gs;
	to_vmcb->save.tr = from_vmcb->save.tr;
	to_vmcb->save.ldtr = from_vmcb->save.ldtr;
	to_vmcb->save.kernel_gs_base = from_vmcb->save.kernel_gs_base;
	to_vmcb->save.star = from_vmcb->save.star;
	to_vmcb->save.lstar = from_vmcb->save.lstar;
	to_vmcb->save.cstar = from_vmcb->save.cstar;
	to_vmcb->save.sfmask = from_vmcb->save.sfmask;
	to_vmcb->save.sysenter_cs = from_vmcb->save.sysenter_cs;
	to_vmcb->save.sysenter_esp = from_vmcb->save.sysenter_esp;
	to_vmcb->save.sysenter_eip = from_vmcb->save.sysenter_eip;
पूर्ण

पूर्णांक nested_svm_vmनिकास(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा kvm_vcpu *vcpu = &svm->vcpu;
	काष्ठा vmcb *vmcb12;
	काष्ठा vmcb *vmcb = svm->vmcb;
	काष्ठा kvm_host_map map;
	पूर्णांक rc;

	/* Triple faults in L2 should never escape. */
	WARN_ON_ONCE(kvm_check_request(KVM_REQ_TRIPLE_FAULT, vcpu));

	rc = kvm_vcpu_map(vcpu, gpa_to_gfn(svm->nested.vmcb12_gpa), &map);
	अगर (rc) अणु
		अगर (rc == -EINVAL)
			kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण

	vmcb12 = map.hva;

	/* Exit Guest-Mode */
	leave_guest_mode(vcpu);
	svm->nested.vmcb12_gpa = 0;
	WARN_ON_ONCE(svm->nested.nested_run_pending);

	kvm_clear_request(KVM_REQ_GET_NESTED_STATE_PAGES, vcpu);

	/* in हाल we halted in L2 */
	svm->vcpu.arch.mp_state = KVM_MP_STATE_RUNNABLE;

	/* Give the current vmcb to the guest */

	vmcb12->save.es     = vmcb->save.es;
	vmcb12->save.cs     = vmcb->save.cs;
	vmcb12->save.ss     = vmcb->save.ss;
	vmcb12->save.ds     = vmcb->save.ds;
	vmcb12->save.gdtr   = vmcb->save.gdtr;
	vmcb12->save.idtr   = vmcb->save.idtr;
	vmcb12->save.efer   = svm->vcpu.arch.efer;
	vmcb12->save.cr0    = kvm_पढ़ो_cr0(vcpu);
	vmcb12->save.cr3    = kvm_पढ़ो_cr3(vcpu);
	vmcb12->save.cr2    = vmcb->save.cr2;
	vmcb12->save.cr4    = svm->vcpu.arch.cr4;
	vmcb12->save.rflags = kvm_get_rflags(vcpu);
	vmcb12->save.rip    = kvm_rip_पढ़ो(vcpu);
	vmcb12->save.rsp    = kvm_rsp_पढ़ो(vcpu);
	vmcb12->save.rax    = kvm_rax_पढ़ो(vcpu);
	vmcb12->save.dr7    = vmcb->save.dr7;
	vmcb12->save.dr6    = svm->vcpu.arch.dr6;
	vmcb12->save.cpl    = vmcb->save.cpl;

	vmcb12->control.पूर्णांक_state         = vmcb->control.पूर्णांक_state;
	vmcb12->control.निकास_code         = vmcb->control.निकास_code;
	vmcb12->control.निकास_code_hi      = vmcb->control.निकास_code_hi;
	vmcb12->control.निकास_info_1       = vmcb->control.निकास_info_1;
	vmcb12->control.निकास_info_2       = vmcb->control.निकास_info_2;

	अगर (vmcb12->control.निकास_code != SVM_EXIT_ERR)
		nested_save_pending_event_to_vmcb12(svm, vmcb12);

	अगर (svm->nrips_enabled)
		vmcb12->control.next_rip  = vmcb->control.next_rip;

	vmcb12->control.पूर्णांक_ctl           = svm->nested.ctl.पूर्णांक_ctl;
	vmcb12->control.tlb_ctl           = svm->nested.ctl.tlb_ctl;
	vmcb12->control.event_inj         = svm->nested.ctl.event_inj;
	vmcb12->control.event_inj_err     = svm->nested.ctl.event_inj_err;

	vmcb12->control.छोड़ो_filter_count =
		svm->vmcb->control.छोड़ो_filter_count;
	vmcb12->control.छोड़ो_filter_thresh =
		svm->vmcb->control.छोड़ो_filter_thresh;

	nested_svm_copy_common_state(svm->nested.vmcb02.ptr, svm->vmcb01.ptr);

	svm_चयन_vmcb(svm, &svm->vmcb01);

	/*
	 * On vmनिकास the  GIF is set to false and
	 * no event can be injected in L1.
	 */
	svm_set_gअगर(svm, false);
	svm->vmcb->control.निकास_पूर्णांक_info = 0;

	svm->vcpu.arch.tsc_offset = svm->vcpu.arch.l1_tsc_offset;
	अगर (svm->vmcb->control.tsc_offset != svm->vcpu.arch.tsc_offset) अणु
		svm->vmcb->control.tsc_offset = svm->vcpu.arch.tsc_offset;
		vmcb_mark_dirty(svm->vmcb, VMCB_INTERCEPTS);
	पूर्ण

	svm->nested.ctl.nested_cr3 = 0;

	/*
	 * Restore processor state that had been saved in vmcb01
	 */
	kvm_set_rflags(vcpu, svm->vmcb->save.rflags);
	svm_set_efer(vcpu, svm->vmcb->save.efer);
	svm_set_cr0(vcpu, svm->vmcb->save.cr0 | X86_CR0_PE);
	svm_set_cr4(vcpu, svm->vmcb->save.cr4);
	kvm_rax_ग_लिखो(vcpu, svm->vmcb->save.rax);
	kvm_rsp_ग_लिखो(vcpu, svm->vmcb->save.rsp);
	kvm_rip_ग_लिखो(vcpu, svm->vmcb->save.rip);

	svm->vcpu.arch.dr7 = DR7_FIXED_1;
	kvm_update_dr7(&svm->vcpu);

	trace_kvm_nested_vmनिकास_inject(vmcb12->control.निकास_code,
				       vmcb12->control.निकास_info_1,
				       vmcb12->control.निकास_info_2,
				       vmcb12->control.निकास_पूर्णांक_info,
				       vmcb12->control.निकास_पूर्णांक_info_err,
				       KVM_ISA_SVM);

	kvm_vcpu_unmap(vcpu, &map, true);

	nested_svm_uninit_mmu_context(vcpu);

	rc = nested_svm_load_cr3(vcpu, svm->vmcb->save.cr3, false);
	अगर (rc)
		वापस 1;

	/*
	 * Drop what we picked up क्रम L2 via svm_complete_पूर्णांकerrupts() so it
	 * करोesn't end up in L1.
	 */
	svm->vcpu.arch.nmi_injected = false;
	kvm_clear_exception_queue(vcpu);
	kvm_clear_पूर्णांकerrupt_queue(vcpu);

	/*
	 * If we are here following the completion of a VMRUN that
	 * is being single-stepped, queue the pending #DB पूर्णांकercept
	 * right now so that it an be accounted क्रम beक्रमe we execute
	 * L1's next inकाष्ठाion.
	 */
	अगर (unlikely(svm->vmcb->save.rflags & X86_EFLAGS_TF))
		kvm_queue_exception(&(svm->vcpu), DB_VECTOR);

	वापस 0;
पूर्ण

अटल व्योम nested_svm_triple_fault(काष्ठा kvm_vcpu *vcpu)
अणु
	nested_svm_simple_vmनिकास(to_svm(vcpu), SVM_EXIT_SHUTDOWN);
पूर्ण

पूर्णांक svm_allocate_nested(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा page *vmcb02_page;

	अगर (svm->nested.initialized)
		वापस 0;

	vmcb02_page = alloc_page(GFP_KERNEL_ACCOUNT | __GFP_ZERO);
	अगर (!vmcb02_page)
		वापस -ENOMEM;
	svm->nested.vmcb02.ptr = page_address(vmcb02_page);
	svm->nested.vmcb02.pa = __sme_set(page_to_pfn(vmcb02_page) << PAGE_SHIFT);

	svm->nested.msrpm = svm_vcpu_alloc_msrpm();
	अगर (!svm->nested.msrpm)
		जाओ err_मुक्त_vmcb02;
	svm_vcpu_init_msrpm(&svm->vcpu, svm->nested.msrpm);

	svm->nested.initialized = true;
	वापस 0;

err_मुक्त_vmcb02:
	__मुक्त_page(vmcb02_page);
	वापस -ENOMEM;
पूर्ण

व्योम svm_मुक्त_nested(काष्ठा vcpu_svm *svm)
अणु
	अगर (!svm->nested.initialized)
		वापस;

	svm_vcpu_मुक्त_msrpm(svm->nested.msrpm);
	svm->nested.msrpm = शून्य;

	__मुक्त_page(virt_to_page(svm->nested.vmcb02.ptr));
	svm->nested.vmcb02.ptr = शून्य;

	/*
	 * When last_vmcb12_gpa matches the current vmcb12 gpa,
	 * some vmcb12 fields are not loaded अगर they are marked clean
	 * in the vmcb12, since in this हाल they are up to date alपढ़ोy.
	 *
	 * When the vmcb02 is मुक्तd, this optimization becomes invalid.
	 */
	svm->nested.last_vmcb12_gpa = INVALID_GPA;

	svm->nested.initialized = false;
पूर्ण

/*
 * Forcibly leave nested mode in order to be able to reset the VCPU later on.
 */
व्योम svm_leave_nested(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा kvm_vcpu *vcpu = &svm->vcpu;

	अगर (is_guest_mode(vcpu)) अणु
		svm->nested.nested_run_pending = 0;
		svm->nested.vmcb12_gpa = INVALID_GPA;

		leave_guest_mode(vcpu);

		svm_चयन_vmcb(svm, &svm->vmcb01);

		nested_svm_uninit_mmu_context(vcpu);
		vmcb_mark_all_dirty(svm->vmcb);
	पूर्ण

	kvm_clear_request(KVM_REQ_GET_NESTED_STATE_PAGES, vcpu);
पूर्ण

अटल पूर्णांक nested_svm_निकास_handled_msr(काष्ठा vcpu_svm *svm)
अणु
	u32 offset, msr, value;
	पूर्णांक ग_लिखो, mask;

	अगर (!(vmcb_is_पूर्णांकercept(&svm->nested.ctl, INTERCEPT_MSR_PROT)))
		वापस NESTED_EXIT_HOST;

	msr    = svm->vcpu.arch.regs[VCPU_REGS_RCX];
	offset = svm_msrpm_offset(msr);
	ग_लिखो  = svm->vmcb->control.निकास_info_1 & 1;
	mask   = 1 << ((2 * (msr & 0xf)) + ग_लिखो);

	अगर (offset == MSR_INVALID)
		वापस NESTED_EXIT_DONE;

	/* Offset is in 32 bit units but need in 8 bit units */
	offset *= 4;

	अगर (kvm_vcpu_पढ़ो_guest(&svm->vcpu, svm->nested.ctl.msrpm_base_pa + offset, &value, 4))
		वापस NESTED_EXIT_DONE;

	वापस (value & mask) ? NESTED_EXIT_DONE : NESTED_EXIT_HOST;
पूर्ण

अटल पूर्णांक nested_svm_पूर्णांकercept_ioio(काष्ठा vcpu_svm *svm)
अणु
	अचिन्हित port, size, iopm_len;
	u16 val, mask;
	u8 start_bit;
	u64 gpa;

	अगर (!(vmcb_is_पूर्णांकercept(&svm->nested.ctl, INTERCEPT_IOIO_PROT)))
		वापस NESTED_EXIT_HOST;

	port = svm->vmcb->control.निकास_info_1 >> 16;
	size = (svm->vmcb->control.निकास_info_1 & SVM_IOIO_SIZE_MASK) >>
		SVM_IOIO_SIZE_SHIFT;
	gpa  = svm->nested.ctl.iopm_base_pa + (port / 8);
	start_bit = port % 8;
	iopm_len = (start_bit + size > 8) ? 2 : 1;
	mask = (0xf >> (4 - size)) << start_bit;
	val = 0;

	अगर (kvm_vcpu_पढ़ो_guest(&svm->vcpu, gpa, &val, iopm_len))
		वापस NESTED_EXIT_DONE;

	वापस (val & mask) ? NESTED_EXIT_DONE : NESTED_EXIT_HOST;
पूर्ण

अटल पूर्णांक nested_svm_पूर्णांकercept(काष्ठा vcpu_svm *svm)
अणु
	u32 निकास_code = svm->vmcb->control.निकास_code;
	पूर्णांक vmनिकास = NESTED_EXIT_HOST;

	चयन (निकास_code) अणु
	हाल SVM_EXIT_MSR:
		vmनिकास = nested_svm_निकास_handled_msr(svm);
		अवरोध;
	हाल SVM_EXIT_IOIO:
		vmनिकास = nested_svm_पूर्णांकercept_ioio(svm);
		अवरोध;
	हाल SVM_EXIT_READ_CR0 ... SVM_EXIT_WRITE_CR8: अणु
		अगर (vmcb_is_पूर्णांकercept(&svm->nested.ctl, निकास_code))
			vmनिकास = NESTED_EXIT_DONE;
		अवरोध;
	पूर्ण
	हाल SVM_EXIT_READ_DR0 ... SVM_EXIT_WRITE_DR7: अणु
		अगर (vmcb_is_पूर्णांकercept(&svm->nested.ctl, निकास_code))
			vmनिकास = NESTED_EXIT_DONE;
		अवरोध;
	पूर्ण
	हाल SVM_EXIT_EXCP_BASE ... SVM_EXIT_EXCP_BASE + 0x1f: अणु
		/*
		 * Host-पूर्णांकercepted exceptions have been checked alपढ़ोy in
		 * nested_svm_निकास_special.  There is nothing to करो here,
		 * the vmनिकास is injected by svm_check_nested_events.
		 */
		vmनिकास = NESTED_EXIT_DONE;
		अवरोध;
	पूर्ण
	हाल SVM_EXIT_ERR: अणु
		vmनिकास = NESTED_EXIT_DONE;
		अवरोध;
	पूर्ण
	शेष: अणु
		अगर (vmcb_is_पूर्णांकercept(&svm->nested.ctl, निकास_code))
			vmनिकास = NESTED_EXIT_DONE;
	पूर्ण
	पूर्ण

	वापस vmनिकास;
पूर्ण

पूर्णांक nested_svm_निकास_handled(काष्ठा vcpu_svm *svm)
अणु
	पूर्णांक vmनिकास;

	vmनिकास = nested_svm_पूर्णांकercept(svm);

	अगर (vmनिकास == NESTED_EXIT_DONE)
		nested_svm_vmनिकास(svm);

	वापस vmनिकास;
पूर्ण

पूर्णांक nested_svm_check_permissions(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!(vcpu->arch.efer & EFER_SVME) || !is_paging(vcpu)) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 1;
	पूर्ण

	अगर (to_svm(vcpu)->vmcb->save.cpl) अणु
		kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool nested_निकास_on_exception(काष्ठा vcpu_svm *svm)
अणु
	अचिन्हित पूर्णांक nr = svm->vcpu.arch.exception.nr;

	वापस (svm->nested.ctl.पूर्णांकercepts[INTERCEPT_EXCEPTION] & BIT(nr));
पूर्ण

अटल व्योम nested_svm_inject_exception_vmनिकास(काष्ठा vcpu_svm *svm)
अणु
	अचिन्हित पूर्णांक nr = svm->vcpu.arch.exception.nr;

	svm->vmcb->control.निकास_code = SVM_EXIT_EXCP_BASE + nr;
	svm->vmcb->control.निकास_code_hi = 0;

	अगर (svm->vcpu.arch.exception.has_error_code)
		svm->vmcb->control.निकास_info_1 = svm->vcpu.arch.exception.error_code;

	/*
	 * EXITINFO2 is undefined क्रम all exception पूर्णांकercepts other
	 * than #PF.
	 */
	अगर (nr == PF_VECTOR) अणु
		अगर (svm->vcpu.arch.exception.nested_apf)
			svm->vmcb->control.निकास_info_2 = svm->vcpu.arch.apf.nested_apf_token;
		अन्यथा अगर (svm->vcpu.arch.exception.has_payload)
			svm->vmcb->control.निकास_info_2 = svm->vcpu.arch.exception.payload;
		अन्यथा
			svm->vmcb->control.निकास_info_2 = svm->vcpu.arch.cr2;
	पूर्ण अन्यथा अगर (nr == DB_VECTOR) अणु
		/* See inject_pending_event.  */
		kvm_deliver_exception_payload(&svm->vcpu);
		अगर (svm->vcpu.arch.dr7 & DR7_GD) अणु
			svm->vcpu.arch.dr7 &= ~DR7_GD;
			kvm_update_dr7(&svm->vcpu);
		पूर्ण
	पूर्ण अन्यथा
		WARN_ON(svm->vcpu.arch.exception.has_payload);

	nested_svm_vmनिकास(svm);
पूर्ण

अटल अंतरभूत bool nested_निकास_on_init(काष्ठा vcpu_svm *svm)
अणु
	वापस vmcb_is_पूर्णांकercept(&svm->nested.ctl, INTERCEPT_INIT);
पूर्ण

अटल पूर्णांक svm_check_nested_events(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	bool block_nested_events =
		kvm_event_needs_reinjection(vcpu) || svm->nested.nested_run_pending;
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	अगर (lapic_in_kernel(vcpu) &&
	    test_bit(KVM_APIC_INIT, &apic->pending_events)) अणु
		अगर (block_nested_events)
			वापस -EBUSY;
		अगर (!nested_निकास_on_init(svm))
			वापस 0;
		nested_svm_simple_vmनिकास(svm, SVM_EXIT_INIT);
		वापस 0;
	पूर्ण

	अगर (vcpu->arch.exception.pending) अणु
		/*
		 * Only a pending nested run can block a pending exception.
		 * Otherwise an injected NMI/पूर्णांकerrupt should either be
		 * lost or delivered to the nested hypervisor in the EXITINTINFO
		 * vmcb field, जबतक delivering the pending exception.
		 */
		अगर (svm->nested.nested_run_pending)
                        वापस -EBUSY;
		अगर (!nested_निकास_on_exception(svm))
			वापस 0;
		nested_svm_inject_exception_vmनिकास(svm);
		वापस 0;
	पूर्ण

	अगर (vcpu->arch.smi_pending && !svm_smi_blocked(vcpu)) अणु
		अगर (block_nested_events)
			वापस -EBUSY;
		अगर (!nested_निकास_on_smi(svm))
			वापस 0;
		nested_svm_simple_vmनिकास(svm, SVM_EXIT_SMI);
		वापस 0;
	पूर्ण

	अगर (vcpu->arch.nmi_pending && !svm_nmi_blocked(vcpu)) अणु
		अगर (block_nested_events)
			वापस -EBUSY;
		अगर (!nested_निकास_on_nmi(svm))
			वापस 0;
		nested_svm_simple_vmनिकास(svm, SVM_EXIT_NMI);
		वापस 0;
	पूर्ण

	अगर (kvm_cpu_has_पूर्णांकerrupt(vcpu) && !svm_पूर्णांकerrupt_blocked(vcpu)) अणु
		अगर (block_nested_events)
			वापस -EBUSY;
		अगर (!nested_निकास_on_पूर्णांकr(svm))
			वापस 0;
		trace_kvm_nested_पूर्णांकr_vmनिकास(svm->vmcb->save.rip);
		nested_svm_simple_vmनिकास(svm, SVM_EXIT_INTR);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक nested_svm_निकास_special(काष्ठा vcpu_svm *svm)
अणु
	u32 निकास_code = svm->vmcb->control.निकास_code;

	चयन (निकास_code) अणु
	हाल SVM_EXIT_INTR:
	हाल SVM_EXIT_NMI:
	हाल SVM_EXIT_NPF:
		वापस NESTED_EXIT_HOST;
	हाल SVM_EXIT_EXCP_BASE ... SVM_EXIT_EXCP_BASE + 0x1f: अणु
		u32 excp_bits = 1 << (निकास_code - SVM_EXIT_EXCP_BASE);

		अगर (svm->vmcb01.ptr->control.पूर्णांकercepts[INTERCEPT_EXCEPTION] &
		    excp_bits)
			वापस NESTED_EXIT_HOST;
		अन्यथा अगर (निकास_code == SVM_EXIT_EXCP_BASE + PF_VECTOR &&
			 svm->vcpu.arch.apf.host_apf_flags)
			/* Trap async PF even अगर not shaकरोwing */
			वापस NESTED_EXIT_HOST;
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस NESTED_EXIT_CONTINUE;
पूर्ण

अटल पूर्णांक svm_get_nested_state(काष्ठा kvm_vcpu *vcpu,
				काष्ठा kvm_nested_state __user *user_kvm_nested_state,
				u32 user_data_size)
अणु
	काष्ठा vcpu_svm *svm;
	काष्ठा kvm_nested_state kvm_state = अणु
		.flags = 0,
		.क्रमmat = KVM_STATE_NESTED_FORMAT_SVM,
		.size = माप(kvm_state),
	पूर्ण;
	काष्ठा vmcb __user *user_vmcb = (काष्ठा vmcb __user *)
		&user_kvm_nested_state->data.svm[0];

	अगर (!vcpu)
		वापस kvm_state.size + KVM_STATE_NESTED_SVM_VMCB_SIZE;

	svm = to_svm(vcpu);

	अगर (user_data_size < kvm_state.size)
		जाओ out;

	/* First fill in the header and copy it out.  */
	अगर (is_guest_mode(vcpu)) अणु
		kvm_state.hdr.svm.vmcb_pa = svm->nested.vmcb12_gpa;
		kvm_state.size += KVM_STATE_NESTED_SVM_VMCB_SIZE;
		kvm_state.flags |= KVM_STATE_NESTED_GUEST_MODE;

		अगर (svm->nested.nested_run_pending)
			kvm_state.flags |= KVM_STATE_NESTED_RUN_PENDING;
	पूर्ण

	अगर (gअगर_set(svm))
		kvm_state.flags |= KVM_STATE_NESTED_GIF_SET;

	अगर (copy_to_user(user_kvm_nested_state, &kvm_state, माप(kvm_state)))
		वापस -EFAULT;

	अगर (!is_guest_mode(vcpu))
		जाओ out;

	/*
	 * Copy over the full size of the VMCB rather than just the size
	 * of the काष्ठाs.
	 */
	अगर (clear_user(user_vmcb, KVM_STATE_NESTED_SVM_VMCB_SIZE))
		वापस -EFAULT;
	अगर (copy_to_user(&user_vmcb->control, &svm->nested.ctl,
			 माप(user_vmcb->control)))
		वापस -EFAULT;
	अगर (copy_to_user(&user_vmcb->save, &svm->vmcb01.ptr->save,
			 माप(user_vmcb->save)))
		वापस -EFAULT;
out:
	वापस kvm_state.size;
पूर्ण

अटल पूर्णांक svm_set_nested_state(काष्ठा kvm_vcpu *vcpu,
				काष्ठा kvm_nested_state __user *user_kvm_nested_state,
				काष्ठा kvm_nested_state *kvm_state)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा vmcb __user *user_vmcb = (काष्ठा vmcb __user *)
		&user_kvm_nested_state->data.svm[0];
	काष्ठा vmcb_control_area *ctl;
	काष्ठा vmcb_save_area *save;
	पूर्णांक ret;
	u32 cr0;

	BUILD_BUG_ON(माप(काष्ठा vmcb_control_area) + माप(काष्ठा vmcb_save_area) >
		     KVM_STATE_NESTED_SVM_VMCB_SIZE);

	अगर (kvm_state->क्रमmat != KVM_STATE_NESTED_FORMAT_SVM)
		वापस -EINVAL;

	अगर (kvm_state->flags & ~(KVM_STATE_NESTED_GUEST_MODE |
				 KVM_STATE_NESTED_RUN_PENDING |
				 KVM_STATE_NESTED_GIF_SET))
		वापस -EINVAL;

	/*
	 * If in guest mode, vcpu->arch.efer actually refers to the L2 guest's
	 * EFER.SVME, but EFER.SVME still has to be 1 क्रम VMRUN to succeed.
	 */
	अगर (!(vcpu->arch.efer & EFER_SVME)) अणु
		/* GIF=1 and no guest mode are required अगर SVME=0.  */
		अगर (kvm_state->flags != KVM_STATE_NESTED_GIF_SET)
			वापस -EINVAL;
	पूर्ण

	/* SMM temporarily disables SVM, so we cannot be in guest mode.  */
	अगर (is_smm(vcpu) && (kvm_state->flags & KVM_STATE_NESTED_GUEST_MODE))
		वापस -EINVAL;

	अगर (!(kvm_state->flags & KVM_STATE_NESTED_GUEST_MODE)) अणु
		svm_leave_nested(svm);
		svm_set_gअगर(svm, !!(kvm_state->flags & KVM_STATE_NESTED_GIF_SET));
		वापस 0;
	पूर्ण

	अगर (!page_address_valid(vcpu, kvm_state->hdr.svm.vmcb_pa))
		वापस -EINVAL;
	अगर (kvm_state->size < माप(*kvm_state) + KVM_STATE_NESTED_SVM_VMCB_SIZE)
		वापस -EINVAL;

	ret  = -ENOMEM;
	ctl  = kzalloc(माप(*ctl),  GFP_KERNEL_ACCOUNT);
	save = kzalloc(माप(*save), GFP_KERNEL_ACCOUNT);
	अगर (!ctl || !save)
		जाओ out_मुक्त;

	ret = -EFAULT;
	अगर (copy_from_user(ctl, &user_vmcb->control, माप(*ctl)))
		जाओ out_मुक्त;
	अगर (copy_from_user(save, &user_vmcb->save, माप(*save)))
		जाओ out_मुक्त;

	ret = -EINVAL;
	अगर (!nested_vmcb_check_controls(vcpu, ctl))
		जाओ out_मुक्त;

	/*
	 * Processor state contains L2 state.  Check that it is
	 * valid क्रम guest mode (see nested_vmcb_check_save).
	 */
	cr0 = kvm_पढ़ो_cr0(vcpu);
        अगर (((cr0 & X86_CR0_CD) == 0) && (cr0 & X86_CR0_NW))
		जाओ out_मुक्त;

	/*
	 * Validate host state saved from beक्रमe VMRUN (see
	 * nested_svm_check_permissions).
	 */
	अगर (!(save->cr0 & X86_CR0_PG) ||
	    !(save->cr0 & X86_CR0_PE) ||
	    (save->rflags & X86_EFLAGS_VM) ||
	    !nested_vmcb_valid_sregs(vcpu, save))
		जाओ out_मुक्त;

	/*
	 * All checks करोne, we can enter guest mode. Userspace provides
	 * vmcb12.control, which will be combined with L1 and stored पूर्णांकo
	 * vmcb02, and the L1 save state which we store in vmcb01.
	 * L2 रेजिस्टरs अगर needed are moved from the current VMCB to VMCB02.
	 */

	अगर (is_guest_mode(vcpu))
		svm_leave_nested(svm);
	अन्यथा
		svm->nested.vmcb02.ptr->save = svm->vmcb01.ptr->save;

	svm_set_gअगर(svm, !!(kvm_state->flags & KVM_STATE_NESTED_GIF_SET));

	svm->nested.nested_run_pending =
		!!(kvm_state->flags & KVM_STATE_NESTED_RUN_PENDING);

	svm->nested.vmcb12_gpa = kvm_state->hdr.svm.vmcb_pa;

	svm->vmcb01.ptr->save.es = save->es;
	svm->vmcb01.ptr->save.cs = save->cs;
	svm->vmcb01.ptr->save.ss = save->ss;
	svm->vmcb01.ptr->save.ds = save->ds;
	svm->vmcb01.ptr->save.gdtr = save->gdtr;
	svm->vmcb01.ptr->save.idtr = save->idtr;
	svm->vmcb01.ptr->save.rflags = save->rflags | X86_EFLAGS_FIXED;
	svm->vmcb01.ptr->save.efer = save->efer;
	svm->vmcb01.ptr->save.cr0 = save->cr0;
	svm->vmcb01.ptr->save.cr3 = save->cr3;
	svm->vmcb01.ptr->save.cr4 = save->cr4;
	svm->vmcb01.ptr->save.rax = save->rax;
	svm->vmcb01.ptr->save.rsp = save->rsp;
	svm->vmcb01.ptr->save.rip = save->rip;
	svm->vmcb01.ptr->save.cpl = 0;

	nested_load_control_from_vmcb12(svm, ctl);

	svm_चयन_vmcb(svm, &svm->nested.vmcb02);

	nested_vmcb02_prepare_control(svm);

	kvm_make_request(KVM_REQ_GET_NESTED_STATE_PAGES, vcpu);
	ret = 0;
out_मुक्त:
	kमुक्त(save);
	kमुक्त(ctl);

	वापस ret;
पूर्ण

अटल bool svm_get_nested_state_pages(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (WARN_ON(!is_guest_mode(vcpu)))
		वापस true;

	अगर (nested_svm_load_cr3(&svm->vcpu, vcpu->arch.cr3,
				nested_npt_enabled(svm)))
		वापस false;

	अगर (!nested_svm_vmrun_msrpm(svm)) अणु
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->पूर्णांकernal.suberror =
			KVM_INTERNAL_ERROR_EMULATION;
		vcpu->run->पूर्णांकernal.ndata = 0;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

काष्ठा kvm_x86_nested_ops svm_nested_ops = अणु
	.check_events = svm_check_nested_events,
	.triple_fault = nested_svm_triple_fault,
	.get_nested_state_pages = svm_get_nested_state_pages,
	.get_state = svm_get_nested_state,
	.set_state = svm_set_nested_state,
पूर्ण;
