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

#अगर_अघोषित __SVM_SVM_H
#घोषणा __SVM_SVM_H

#समावेश <linux/kvm_types.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/bits.h>

#समावेश <यंत्र/svm.h>
#समावेश <यंत्र/sev-common.h>

#घोषणा __sme_page_pa(x) __sme_set(page_to_pfn(x) << PAGE_SHIFT)

#घोषणा	IOPM_SIZE PAGE_SIZE * 3
#घोषणा	MSRPM_SIZE PAGE_SIZE * 2

#घोषणा MAX_सूचीECT_ACCESS_MSRS	20
#घोषणा MSRPM_OFFSETS	16
बाह्य u32 msrpm_offsets[MSRPM_OFFSETS] __पढ़ो_mostly;
बाह्य bool npt_enabled;

क्रमागत अणु
	VMCB_INTERCEPTS, /* Intercept vectors, TSC offset,
			    छोड़ो filter count */
	VMCB_PERM_MAP,   /* IOPM Base and MSRPM Base */
	VMCB_ASID,	 /* ASID */
	VMCB_INTR,	 /* पूर्णांक_ctl, पूर्णांक_vector */
	VMCB_NPT,        /* npt_en, nCR3, gPAT */
	VMCB_CR,	 /* CR0, CR3, CR4, EFER */
	VMCB_DR,         /* DR6, DR7 */
	VMCB_DT,         /* GDT, IDT */
	VMCB_SEG,        /* CS, DS, SS, ES, CPL */
	VMCB_CR2,        /* CR2 only */
	VMCB_LBR,        /* DBGCTL, BR_FROM, BR_TO, LAST_EX_FROM, LAST_EX_TO */
	VMCB_AVIC,       /* AVIC APIC_BAR, AVIC APIC_BACKING_PAGE,
			  * AVIC PHYSICAL_TABLE poपूर्णांकer,
			  * AVIC LOGICAL_TABLE poपूर्णांकer
			  */
	VMCB_सूचीTY_MAX,
पूर्ण;

/* TPR and CR2 are always written beक्रमe VMRUN */
#घोषणा VMCB_ALWAYS_सूचीTY_MASK	((1U << VMCB_INTR) | (1U << VMCB_CR2))

काष्ठा kvm_sev_info अणु
	bool active;		/* SEV enabled guest */
	bool es_active;		/* SEV-ES enabled guest */
	अचिन्हित पूर्णांक asid;	/* ASID used क्रम this guest */
	अचिन्हित पूर्णांक handle;	/* SEV firmware handle */
	पूर्णांक fd;			/* SEV device fd */
	अचिन्हित दीर्घ pages_locked; /* Number of pages locked */
	काष्ठा list_head regions_list;  /* List of रेजिस्टरed regions */
	u64 ap_jump_table;	/* SEV-ES AP Jump Table address */
	काष्ठा kvm *enc_context_owner; /* Owner of copied encryption context */
	काष्ठा misc_cg *misc_cg; /* For misc cgroup accounting */
पूर्ण;

काष्ठा kvm_svm अणु
	काष्ठा kvm kvm;

	/* Struct members क्रम AVIC */
	u32 avic_vm_id;
	काष्ठा page *avic_logical_id_table_page;
	काष्ठा page *avic_physical_id_table_page;
	काष्ठा hlist_node hnode;

	काष्ठा kvm_sev_info sev_info;
पूर्ण;

काष्ठा kvm_vcpu;

काष्ठा kvm_vmcb_info अणु
	काष्ठा vmcb *ptr;
	अचिन्हित दीर्घ pa;
	पूर्णांक cpu;
	uपूर्णांक64_t asid_generation;
पूर्ण;

काष्ठा svm_nested_state अणु
	काष्ठा kvm_vmcb_info vmcb02;
	u64 hsave_msr;
	u64 vm_cr_msr;
	u64 vmcb12_gpa;
	u64 last_vmcb12_gpa;

	/* These are the merged vectors */
	u32 *msrpm;

	/* A VMRUN has started but has not yet been perक्रमmed, so
	 * we cannot inject a nested vmनिकास yet.  */
	bool nested_run_pending;

	/* cache क्रम control fields of the guest */
	काष्ठा vmcb_control_area ctl;

	bool initialized;
पूर्ण;

काष्ठा vcpu_svm अणु
	काष्ठा kvm_vcpu vcpu;
	/* vmcb always poपूर्णांकs at current_vmcb->ptr, it's purely a लघुhand. */
	काष्ठा vmcb *vmcb;
	काष्ठा kvm_vmcb_info vmcb01;
	काष्ठा kvm_vmcb_info *current_vmcb;
	काष्ठा svm_cpu_data *svm_data;
	u32 asid;
	u32 sysenter_esp_hi;
	u32 sysenter_eip_hi;
	uपूर्णांक64_t tsc_aux;

	u64 msr_decfg;

	u64 next_rip;

	u64 spec_ctrl;
	/*
	 * Contains guest-controlled bits of VIRT_SPEC_CTRL, which will be
	 * translated पूर्णांकo the appropriate L2_CFG bits on the host to
	 * perक्रमm speculative control.
	 */
	u64 virt_spec_ctrl;

	u32 *msrpm;

	uदीर्घ nmi_iret_rip;

	काष्ठा svm_nested_state nested;

	bool nmi_singlestep;
	u64 nmi_singlestep_guest_rflags;

	अचिन्हित पूर्णांक3_injected;
	अचिन्हित दीर्घ पूर्णांक3_rip;

	/* cached guest cpuid flags क्रम faster access */
	bool nrips_enabled	: 1;

	u32 ldr_reg;
	u32 dfr_reg;
	काष्ठा page *avic_backing_page;
	u64 *avic_physical_id_cache;
	bool avic_is_running;

	/*
	 * Per-vcpu list of काष्ठा amd_svm_iommu_ir:
	 * This is used मुख्यly to store पूर्णांकerrupt remapping inक्रमmation used
	 * when update the vcpu affinity. This aव्योमs the need to scan क्रम
	 * IRTE and try to match ga_tag in the IOMMU driver.
	 */
	काष्ठा list_head ir_list;
	spinlock_t ir_list_lock;

	/* Save desired MSR पूर्णांकercept (पढ़ो: pass-through) state */
	काष्ठा अणु
		DECLARE_BITMAP(पढ़ो, MAX_सूचीECT_ACCESS_MSRS);
		DECLARE_BITMAP(ग_लिखो, MAX_सूचीECT_ACCESS_MSRS);
	पूर्ण shaकरोw_msr_पूर्णांकercept;

	/* SEV-ES support */
	काष्ठा vmcb_save_area *vmsa;
	काष्ठा ghcb *ghcb;
	काष्ठा kvm_host_map ghcb_map;
	bool received_first_sipi;

	/* SEV-ES scratch area support */
	व्योम *ghcb_sa;
	u64 ghcb_sa_len;
	bool ghcb_sa_sync;
	bool ghcb_sa_मुक्त;

	bool guest_state_loaded;
पूर्ण;

काष्ठा svm_cpu_data अणु
	पूर्णांक cpu;

	u64 asid_generation;
	u32 max_asid;
	u32 next_asid;
	u32 min_asid;
	काष्ठा kvm_ldttss_desc *tss_desc;

	काष्ठा page *save_area;
	काष्ठा vmcb *current_vmcb;

	/* index = sev_asid, value = vmcb poपूर्णांकer */
	काष्ठा vmcb **sev_vmcbs;
पूर्ण;

DECLARE_PER_CPU(काष्ठा svm_cpu_data *, svm_data);

व्योम recalc_पूर्णांकercepts(काष्ठा vcpu_svm *svm);

अटल अंतरभूत काष्ठा kvm_svm *to_kvm_svm(काष्ठा kvm *kvm)
अणु
	वापस container_of(kvm, काष्ठा kvm_svm, kvm);
पूर्ण

अटल अंतरभूत bool sev_guest(काष्ठा kvm *kvm)
अणु
#अगर_घोषित CONFIG_KVM_AMD_SEV
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;

	वापस sev->active;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool sev_es_guest(काष्ठा kvm *kvm)
अणु
#अगर_घोषित CONFIG_KVM_AMD_SEV
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;

	वापस sev_guest(kvm) && sev->es_active;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम vmcb_mark_all_dirty(काष्ठा vmcb *vmcb)
अणु
	vmcb->control.clean = 0;
पूर्ण

अटल अंतरभूत व्योम vmcb_mark_all_clean(काष्ठा vmcb *vmcb)
अणु
	vmcb->control.clean = ((1 << VMCB_सूचीTY_MAX) - 1)
			       & ~VMCB_ALWAYS_सूचीTY_MASK;
पूर्ण

अटल अंतरभूत व्योम vmcb_mark_dirty(काष्ठा vmcb *vmcb, पूर्णांक bit)
अणु
	vmcb->control.clean &= ~(1 << bit);
पूर्ण

अटल अंतरभूत bool vmcb_is_dirty(काष्ठा vmcb *vmcb, पूर्णांक bit)
अणु
        वापस !test_bit(bit, (अचिन्हित दीर्घ *)&vmcb->control.clean);
पूर्ण

अटल अंतरभूत काष्ठा vcpu_svm *to_svm(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस container_of(vcpu, काष्ठा vcpu_svm, vcpu);
पूर्ण

अटल अंतरभूत व्योम vmcb_set_पूर्णांकercept(काष्ठा vmcb_control_area *control, u32 bit)
अणु
	WARN_ON_ONCE(bit >= 32 * MAX_INTERCEPT);
	__set_bit(bit, (अचिन्हित दीर्घ *)&control->पूर्णांकercepts);
पूर्ण

अटल अंतरभूत व्योम vmcb_clr_पूर्णांकercept(काष्ठा vmcb_control_area *control, u32 bit)
अणु
	WARN_ON_ONCE(bit >= 32 * MAX_INTERCEPT);
	__clear_bit(bit, (अचिन्हित दीर्घ *)&control->पूर्णांकercepts);
पूर्ण

अटल अंतरभूत bool vmcb_is_पूर्णांकercept(काष्ठा vmcb_control_area *control, u32 bit)
अणु
	WARN_ON_ONCE(bit >= 32 * MAX_INTERCEPT);
	वापस test_bit(bit, (अचिन्हित दीर्घ *)&control->पूर्णांकercepts);
पूर्ण

अटल अंतरभूत व्योम set_dr_पूर्णांकercepts(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा vmcb *vmcb = svm->vmcb01.ptr;

	अगर (!sev_es_guest(svm->vcpu.kvm)) अणु
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR0_READ);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR1_READ);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR2_READ);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR3_READ);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR4_READ);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR5_READ);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR6_READ);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR0_WRITE);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR1_WRITE);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR2_WRITE);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR3_WRITE);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR4_WRITE);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR5_WRITE);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR6_WRITE);
	पूर्ण

	vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR7_READ);
	vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR7_WRITE);

	recalc_पूर्णांकercepts(svm);
पूर्ण

अटल अंतरभूत व्योम clr_dr_पूर्णांकercepts(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा vmcb *vmcb = svm->vmcb01.ptr;

	vmcb->control.पूर्णांकercepts[INTERCEPT_DR] = 0;

	/* DR7 access must reमुख्य पूर्णांकercepted क्रम an SEV-ES guest */
	अगर (sev_es_guest(svm->vcpu.kvm)) अणु
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR7_READ);
		vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_DR7_WRITE);
	पूर्ण

	recalc_पूर्णांकercepts(svm);
पूर्ण

अटल अंतरभूत व्योम set_exception_पूर्णांकercept(काष्ठा vcpu_svm *svm, u32 bit)
अणु
	काष्ठा vmcb *vmcb = svm->vmcb01.ptr;

	WARN_ON_ONCE(bit >= 32);
	vmcb_set_पूर्णांकercept(&vmcb->control, INTERCEPT_EXCEPTION_OFFSET + bit);

	recalc_पूर्णांकercepts(svm);
पूर्ण

अटल अंतरभूत व्योम clr_exception_पूर्णांकercept(काष्ठा vcpu_svm *svm, u32 bit)
अणु
	काष्ठा vmcb *vmcb = svm->vmcb01.ptr;

	WARN_ON_ONCE(bit >= 32);
	vmcb_clr_पूर्णांकercept(&vmcb->control, INTERCEPT_EXCEPTION_OFFSET + bit);

	recalc_पूर्णांकercepts(svm);
पूर्ण

अटल अंतरभूत व्योम svm_set_पूर्णांकercept(काष्ठा vcpu_svm *svm, पूर्णांक bit)
अणु
	काष्ठा vmcb *vmcb = svm->vmcb01.ptr;

	vmcb_set_पूर्णांकercept(&vmcb->control, bit);

	recalc_पूर्णांकercepts(svm);
पूर्ण

अटल अंतरभूत व्योम svm_clr_पूर्णांकercept(काष्ठा vcpu_svm *svm, पूर्णांक bit)
अणु
	काष्ठा vmcb *vmcb = svm->vmcb01.ptr;

	vmcb_clr_पूर्णांकercept(&vmcb->control, bit);

	recalc_पूर्णांकercepts(svm);
पूर्ण

अटल अंतरभूत bool svm_is_पूर्णांकercept(काष्ठा vcpu_svm *svm, पूर्णांक bit)
अणु
	वापस vmcb_is_पूर्णांकercept(&svm->vmcb->control, bit);
पूर्ण

अटल अंतरभूत bool vgअगर_enabled(काष्ठा vcpu_svm *svm)
अणु
	वापस !!(svm->vmcb->control.पूर्णांक_ctl & V_GIF_ENABLE_MASK);
पूर्ण

अटल अंतरभूत व्योम enable_gअगर(काष्ठा vcpu_svm *svm)
अणु
	अगर (vgअगर_enabled(svm))
		svm->vmcb->control.पूर्णांक_ctl |= V_GIF_MASK;
	अन्यथा
		svm->vcpu.arch.hflags |= HF_GIF_MASK;
पूर्ण

अटल अंतरभूत व्योम disable_gअगर(काष्ठा vcpu_svm *svm)
अणु
	अगर (vgअगर_enabled(svm))
		svm->vmcb->control.पूर्णांक_ctl &= ~V_GIF_MASK;
	अन्यथा
		svm->vcpu.arch.hflags &= ~HF_GIF_MASK;
पूर्ण

अटल अंतरभूत bool gअगर_set(काष्ठा vcpu_svm *svm)
अणु
	अगर (vgअगर_enabled(svm))
		वापस !!(svm->vmcb->control.पूर्णांक_ctl & V_GIF_MASK);
	अन्यथा
		वापस !!(svm->vcpu.arch.hflags & HF_GIF_MASK);
पूर्ण

/* svm.c */
#घोषणा MSR_INVALID				0xffffffffU

बाह्य bool dump_invalid_vmcb;

u32 svm_msrpm_offset(u32 msr);
u32 *svm_vcpu_alloc_msrpm(व्योम);
व्योम svm_vcpu_init_msrpm(काष्ठा kvm_vcpu *vcpu, u32 *msrpm);
व्योम svm_vcpu_मुक्त_msrpm(u32 *msrpm);

पूर्णांक svm_set_efer(काष्ठा kvm_vcpu *vcpu, u64 efer);
व्योम svm_set_cr0(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr0);
व्योम svm_set_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr4);
व्योम svm_flush_tlb(काष्ठा kvm_vcpu *vcpu);
व्योम disable_nmi_singlestep(काष्ठा vcpu_svm *svm);
bool svm_smi_blocked(काष्ठा kvm_vcpu *vcpu);
bool svm_nmi_blocked(काष्ठा kvm_vcpu *vcpu);
bool svm_पूर्णांकerrupt_blocked(काष्ठा kvm_vcpu *vcpu);
व्योम svm_set_gअगर(काष्ठा vcpu_svm *svm, bool value);
पूर्णांक svm_invoke_निकास_handler(काष्ठा kvm_vcpu *vcpu, u64 निकास_code);
व्योम set_msr_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu, u32 *msrpm, u32 msr,
			  पूर्णांक पढ़ो, पूर्णांक ग_लिखो);

/* nested.c */

#घोषणा NESTED_EXIT_HOST	0	/* Exit handled on host level */
#घोषणा NESTED_EXIT_DONE	1	/* Exit caused nested vmनिकास  */
#घोषणा NESTED_EXIT_CONTINUE	2	/* Further checks needed      */

अटल अंतरभूत bool nested_svm_भवize_tpr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	वापस is_guest_mode(vcpu) && (svm->nested.ctl.पूर्णांक_ctl & V_INTR_MASKING_MASK);
पूर्ण

अटल अंतरभूत bool nested_निकास_on_smi(काष्ठा vcpu_svm *svm)
अणु
	वापस vmcb_is_पूर्णांकercept(&svm->nested.ctl, INTERCEPT_SMI);
पूर्ण

अटल अंतरभूत bool nested_निकास_on_पूर्णांकr(काष्ठा vcpu_svm *svm)
अणु
	वापस vmcb_is_पूर्णांकercept(&svm->nested.ctl, INTERCEPT_INTR);
पूर्ण

अटल अंतरभूत bool nested_निकास_on_nmi(काष्ठा vcpu_svm *svm)
अणु
	वापस vmcb_is_पूर्णांकercept(&svm->nested.ctl, INTERCEPT_NMI);
पूर्ण

पूर्णांक enter_svm_guest_mode(काष्ठा kvm_vcpu *vcpu, u64 vmcb_gpa, काष्ठा vmcb *vmcb12);
व्योम svm_leave_nested(काष्ठा vcpu_svm *svm);
व्योम svm_मुक्त_nested(काष्ठा vcpu_svm *svm);
पूर्णांक svm_allocate_nested(काष्ठा vcpu_svm *svm);
पूर्णांक nested_svm_vmrun(काष्ठा kvm_vcpu *vcpu);
व्योम nested_svm_vmloadsave(काष्ठा vmcb *from_vmcb, काष्ठा vmcb *to_vmcb);
पूर्णांक nested_svm_vmनिकास(काष्ठा vcpu_svm *svm);

अटल अंतरभूत पूर्णांक nested_svm_simple_vmनिकास(काष्ठा vcpu_svm *svm, u32 निकास_code)
अणु
	svm->vmcb->control.निकास_code   = निकास_code;
	svm->vmcb->control.निकास_info_1 = 0;
	svm->vmcb->control.निकास_info_2 = 0;
	वापस nested_svm_vmनिकास(svm);
पूर्ण

पूर्णांक nested_svm_निकास_handled(काष्ठा vcpu_svm *svm);
पूर्णांक nested_svm_check_permissions(काष्ठा kvm_vcpu *vcpu);
पूर्णांक nested_svm_check_exception(काष्ठा vcpu_svm *svm, अचिन्हित nr,
			       bool has_error_code, u32 error_code);
पूर्णांक nested_svm_निकास_special(काष्ठा vcpu_svm *svm);
व्योम nested_sync_control_from_vmcb02(काष्ठा vcpu_svm *svm);
व्योम nested_vmcb02_compute_g_pat(काष्ठा vcpu_svm *svm);
व्योम svm_चयन_vmcb(काष्ठा vcpu_svm *svm, काष्ठा kvm_vmcb_info *target_vmcb);

बाह्य काष्ठा kvm_x86_nested_ops svm_nested_ops;

/* avic.c */

#घोषणा AVIC_LOGICAL_ID_ENTRY_GUEST_PHYSICAL_ID_MASK	(0xFF)
#घोषणा AVIC_LOGICAL_ID_ENTRY_VALID_BIT			31
#घोषणा AVIC_LOGICAL_ID_ENTRY_VALID_MASK		(1 << 31)

#घोषणा AVIC_PHYSICAL_ID_ENTRY_HOST_PHYSICAL_ID_MASK	(0xFFULL)
#घोषणा AVIC_PHYSICAL_ID_ENTRY_BACKING_PAGE_MASK	(0xFFFFFFFFFFULL << 12)
#घोषणा AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK		(1ULL << 62)
#घोषणा AVIC_PHYSICAL_ID_ENTRY_VALID_MASK		(1ULL << 63)

#घोषणा VMCB_AVIC_APIC_BAR_MASK		0xFFFFFFFFFF000ULL

बाह्य bool avic;

अटल अंतरभूत व्योम avic_update_vapic_bar(काष्ठा vcpu_svm *svm, u64 data)
अणु
	svm->vmcb->control.avic_vapic_bar = data & VMCB_AVIC_APIC_BAR_MASK;
	vmcb_mark_dirty(svm->vmcb, VMCB_AVIC);
पूर्ण

अटल अंतरभूत bool avic_vcpu_is_running(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u64 *entry = svm->avic_physical_id_cache;

	अगर (!entry)
		वापस false;

	वापस (READ_ONCE(*entry) & AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK);
पूर्ण

पूर्णांक avic_ga_log_notअगरier(u32 ga_tag);
व्योम avic_vm_destroy(काष्ठा kvm *kvm);
पूर्णांक avic_vm_init(काष्ठा kvm *kvm);
व्योम avic_init_vmcb(काष्ठा vcpu_svm *svm);
व्योम svm_toggle_avic_क्रम_irq_winकरोw(काष्ठा kvm_vcpu *vcpu, bool activate);
पूर्णांक avic_incomplete_ipi_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu);
पूर्णांक avic_unaccelerated_access_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu);
पूर्णांक avic_init_vcpu(काष्ठा vcpu_svm *svm);
व्योम avic_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu);
व्योम avic_vcpu_put(काष्ठा kvm_vcpu *vcpu);
व्योम avic_post_state_restore(काष्ठा kvm_vcpu *vcpu);
व्योम svm_set_भव_apic_mode(काष्ठा kvm_vcpu *vcpu);
व्योम svm_refresh_apicv_exec_ctrl(काष्ठा kvm_vcpu *vcpu);
bool svm_check_apicv_inhibit_reasons(uदीर्घ bit);
व्योम svm_pre_update_apicv_exec_ctrl(काष्ठा kvm *kvm, bool activate);
व्योम svm_load_eoi_निकासmap(काष्ठा kvm_vcpu *vcpu, u64 *eoi_निकास_biपंचांगap);
व्योम svm_hwapic_irr_update(काष्ठा kvm_vcpu *vcpu, पूर्णांक max_irr);
व्योम svm_hwapic_isr_update(काष्ठा kvm_vcpu *vcpu, पूर्णांक max_isr);
पूर्णांक svm_deliver_avic_पूर्णांकr(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec);
bool svm_dy_apicv_has_pending_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu);
पूर्णांक svm_update_pi_irte(काष्ठा kvm *kvm, अचिन्हित पूर्णांक host_irq,
		       uपूर्णांक32_t guest_irq, bool set);
व्योम svm_vcpu_blocking(काष्ठा kvm_vcpu *vcpu);
व्योम svm_vcpu_unblocking(काष्ठा kvm_vcpu *vcpu);

/* sev.c */

#घोषणा GHCB_VERSION_MAX	1ULL
#घोषणा GHCB_VERSION_MIN	1ULL


बाह्य अचिन्हित पूर्णांक max_sev_asid;

व्योम sev_vm_destroy(काष्ठा kvm *kvm);
पूर्णांक svm_mem_enc_op(काष्ठा kvm *kvm, व्योम __user *argp);
पूर्णांक svm_रेजिस्टर_enc_region(काष्ठा kvm *kvm,
			    काष्ठा kvm_enc_region *range);
पूर्णांक svm_unरेजिस्टर_enc_region(काष्ठा kvm *kvm,
			      काष्ठा kvm_enc_region *range);
पूर्णांक svm_vm_copy_asid_from(काष्ठा kvm *kvm, अचिन्हित पूर्णांक source_fd);
व्योम pre_sev_run(काष्ठा vcpu_svm *svm, पूर्णांक cpu);
व्योम __init sev_set_cpu_caps(व्योम);
व्योम __init sev_hardware_setup(व्योम);
व्योम sev_hardware_tearकरोwn(व्योम);
पूर्णांक sev_cpu_init(काष्ठा svm_cpu_data *sd);
व्योम sev_मुक्त_vcpu(काष्ठा kvm_vcpu *vcpu);
पूर्णांक sev_handle_vmgनिकास(काष्ठा kvm_vcpu *vcpu);
पूर्णांक sev_es_string_io(काष्ठा vcpu_svm *svm, पूर्णांक size, अचिन्हित पूर्णांक port, पूर्णांक in);
व्योम sev_es_init_vmcb(काष्ठा vcpu_svm *svm);
व्योम sev_es_create_vcpu(काष्ठा vcpu_svm *svm);
व्योम sev_vcpu_deliver_sipi_vector(काष्ठा kvm_vcpu *vcpu, u8 vector);
व्योम sev_es_prepare_guest_चयन(काष्ठा vcpu_svm *svm, अचिन्हित पूर्णांक cpu);
व्योम sev_es_unmap_ghcb(काष्ठा vcpu_svm *svm);

/* vmenter.S */

व्योम __svm_sev_es_vcpu_run(अचिन्हित दीर्घ vmcb_pa);
व्योम __svm_vcpu_run(अचिन्हित दीर्घ vmcb_pa, अचिन्हित दीर्घ *regs);

#पूर्ण_अगर
