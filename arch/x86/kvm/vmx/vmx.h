<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_VMX_H
#घोषणा __KVM_X86_VMX_H

#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kvm.h>
#समावेश <यंत्र/पूर्णांकel_pt.h>

#समावेश "capabilities.h"
#समावेश "kvm_cache_regs.h"
#समावेश "posted_intr.h"
#समावेश "vmcs.h"
#समावेश "vmx_ops.h"
#समावेश "cpuid.h"

बाह्य स्थिर u32 vmx_msr_index[];

#घोषणा MSR_TYPE_R	1
#घोषणा MSR_TYPE_W	2
#घोषणा MSR_TYPE_RW	3

#घोषणा X2APIC_MSR(r) (APIC_BASE_MSR + ((r) >> 4))

#अगर_घोषित CONFIG_X86_64
#घोषणा MAX_NR_USER_RETURN_MSRS	7
#अन्यथा
#घोषणा MAX_NR_USER_RETURN_MSRS	4
#पूर्ण_अगर

#घोषणा MAX_NR_LOADSTORE_MSRS	8

काष्ठा vmx_msrs अणु
	अचिन्हित पूर्णांक		nr;
	काष्ठा vmx_msr_entry	val[MAX_NR_LOADSTORE_MSRS];
पूर्ण;

काष्ठा vmx_uret_msr अणु
	bool load_पूर्णांकo_hardware;
	u64 data;
	u64 mask;
पूर्ण;

क्रमागत segment_cache_field अणु
	SEG_FIELD_SEL = 0,
	SEG_FIELD_BASE = 1,
	SEG_FIELD_LIMIT = 2,
	SEG_FIELD_AR = 3,

	SEG_FIELD_NR = 4
पूर्ण;

#घोषणा RTIT_ADDR_RANGE		4

काष्ठा pt_ctx अणु
	u64 ctl;
	u64 status;
	u64 output_base;
	u64 output_mask;
	u64 cr3_match;
	u64 addr_a[RTIT_ADDR_RANGE];
	u64 addr_b[RTIT_ADDR_RANGE];
पूर्ण;

काष्ठा pt_desc अणु
	u64 ctl_biपंचांगask;
	u32 addr_range;
	u32 caps[PT_CPUID_REGS_NUM * PT_CPUID_LEAVES];
	काष्ठा pt_ctx host;
	काष्ठा pt_ctx guest;
पूर्ण;

जोड़ vmx_निकास_reason अणु
	काष्ठा अणु
		u32	basic			: 16;
		u32	reserved16		: 1;
		u32	reserved17		: 1;
		u32	reserved18		: 1;
		u32	reserved19		: 1;
		u32	reserved20		: 1;
		u32	reserved21		: 1;
		u32	reserved22		: 1;
		u32	reserved23		: 1;
		u32	reserved24		: 1;
		u32	reserved25		: 1;
		u32	bus_lock_detected	: 1;
		u32	enclave_mode		: 1;
		u32	smi_pending_mtf		: 1;
		u32	smi_from_vmx_root	: 1;
		u32	reserved30		: 1;
		u32	failed_vmentry		: 1;
	पूर्ण;
	u32 full;
पूर्ण;

#घोषणा vcpu_to_lbr_desc(vcpu) (&to_vmx(vcpu)->lbr_desc)
#घोषणा vcpu_to_lbr_records(vcpu) (&to_vmx(vcpu)->lbr_desc.records)

bool पूर्णांकel_pmu_lbr_is_compatible(काष्ठा kvm_vcpu *vcpu);
bool पूर्णांकel_pmu_lbr_is_enabled(काष्ठा kvm_vcpu *vcpu);

पूर्णांक पूर्णांकel_pmu_create_guest_lbr_event(काष्ठा kvm_vcpu *vcpu);
व्योम vmx_passthrough_lbr_msrs(काष्ठा kvm_vcpu *vcpu);

काष्ठा lbr_desc अणु
	/* Basic info about guest LBR records. */
	काष्ठा x86_pmu_lbr records;

	/*
	 * Emulate LBR feature via passthrough LBR रेजिस्टरs when the
	 * per-vcpu guest LBR event is scheduled on the current pcpu.
	 *
	 * The records may be inaccurate अगर the host reclaims the LBR.
	 */
	काष्ठा perf_event *event;

	/* True अगर LBRs are marked as not पूर्णांकercepted in the MSR biपंचांगap */
	bool msr_passthrough;
पूर्ण;

/*
 * The nested_vmx काष्ठाure is part of vcpu_vmx, and holds inक्रमmation we need
 * क्रम correct emulation of VMX (i.e., nested VMX) on this vcpu.
 */
काष्ठा nested_vmx अणु
	/* Has the level1 guest करोne vmxon? */
	bool vmxon;
	gpa_t vmxon_ptr;
	bool pml_full;

	/* The guest-physical address of the current VMCS L1 keeps क्रम L2 */
	gpa_t current_vmptr;
	/*
	 * Cache of the guest's VMCS, existing outside of guest memory.
	 * Loaded from guest memory during VMPTRLD. Flushed to guest
	 * memory during VMCLEAR and VMPTRLD.
	 */
	काष्ठा vmcs12 *cached_vmcs12;
	/*
	 * Cache of the guest's shaकरोw VMCS, existing outside of guest
	 * memory. Loaded from guest memory during VM entry. Flushed
	 * to guest memory during VM निकास.
	 */
	काष्ठा vmcs12 *cached_shaकरोw_vmcs12;

	/*
	 * Indicates अगर the shaकरोw vmcs or enlightened vmcs must be updated
	 * with the data held by काष्ठा vmcs12.
	 */
	bool need_vmcs12_to_shaकरोw_sync;
	bool dirty_vmcs12;

	/*
	 * Indicates lazily loaded guest state has not yet been decached from
	 * vmcs02.
	 */
	bool need_sync_vmcs02_to_vmcs12_rare;

	/*
	 * vmcs02 has been initialized, i.e. state that is स्थिरant क्रम
	 * vmcs02 has been written to the backing VMCS.  Initialization
	 * is delayed until L1 actually attempts to run a nested VM.
	 */
	bool vmcs02_initialized;

	bool change_vmcs01_भव_apic_mode;
	bool reload_vmcs01_apic_access_page;
	bool update_vmcs01_cpu_dirty_logging;

	/*
	 * Enlightened VMCS has been enabled. It करोes not mean that L1 has to
	 * use it. However, VMX features available to L1 will be limited based
	 * on what the enlightened VMCS supports.
	 */
	bool enlightened_vmcs_enabled;

	/* L2 must run next, and mustn't decide to निकास to L1. */
	bool nested_run_pending;

	/* Pending MTF VM-निकास पूर्णांकo L1.  */
	bool mtf_pending;

	काष्ठा loaded_vmcs vmcs02;

	/*
	 * Guest pages referred to in the vmcs02 with host-physical
	 * poपूर्णांकers, so we must keep them pinned जबतक L2 runs.
	 */
	काष्ठा page *apic_access_page;
	काष्ठा kvm_host_map भव_apic_map;
	काष्ठा kvm_host_map pi_desc_map;

	काष्ठा kvm_host_map msr_biपंचांगap_map;

	काष्ठा pi_desc *pi_desc;
	bool pi_pending;
	u16 posted_पूर्णांकr_nv;

	काष्ठा hrसमयr preemption_समयr;
	u64 preemption_समयr_deadline;
	bool has_preemption_समयr_deadline;
	bool preemption_समयr_expired;

	/* to migrate it to L2 अगर VM_ENTRY_LOAD_DEBUG_CONTROLS is off */
	u64 vmcs01_debugctl;
	u64 vmcs01_guest_bndcfgs;

	/* to migrate it to L1 अगर L2 ग_लिखोs to L1's CR8 directly */
	पूर्णांक l1_tpr_threshold;

	u16 vpid02;
	u16 last_vpid;

	काष्ठा nested_vmx_msrs msrs;

	/* SMM related state */
	काष्ठा अणु
		/* in VMX operation on SMM entry? */
		bool vmxon;
		/* in guest mode on SMM entry? */
		bool guest_mode;
	पूर्ण smm;

	gpa_t hv_evmcs_vmptr;
	काष्ठा kvm_host_map hv_evmcs_map;
	काष्ठा hv_enlightened_vmcs *hv_evmcs;
पूर्ण;

काष्ठा vcpu_vmx अणु
	काष्ठा kvm_vcpu       vcpu;
	u8                    fail;
	u8		      msr_biपंचांगap_mode;

	/*
	 * If true, host state has been stored in vmx->loaded_vmcs क्रम
	 * the CPU रेजिस्टरs that only need to be चयनed when transitioning
	 * to/from the kernel, and the रेजिस्टरs have been loaded with guest
	 * values.  If false, host state is loaded in the CPU रेजिस्टरs
	 * and vmx->loaded_vmcs->host_state is invalid.
	 */
	bool		      guest_state_loaded;

	अचिन्हित दीर्घ         निकास_qualअगरication;
	u32                   निकास_पूर्णांकr_info;
	u32                   idt_vectoring_info;
	uदीर्घ                 rflags;

	/*
	 * User वापस MSRs are always emulated when enabled in the guest, but
	 * only loaded पूर्णांकo hardware when necessary, e.g. SYSCALL #UDs outside
	 * of 64-bit mode or अगर EFER.SCE=1, thus the SYSCALL MSRs करोn't need to
	 * be loaded पूर्णांकo hardware अगर those conditions aren't met.
	 * nr_active_uret_msrs tracks the number of MSRs that need to be loaded
	 * पूर्णांकo hardware when running the guest.  guest_uret_msrs[] is resorted
	 * whenever the number of "active" uret MSRs is modअगरied.
	 */
	काष्ठा vmx_uret_msr   guest_uret_msrs[MAX_NR_USER_RETURN_MSRS];
	पूर्णांक                   nr_active_uret_msrs;
	bool                  guest_uret_msrs_loaded;
#अगर_घोषित CONFIG_X86_64
	u64		      msr_host_kernel_gs_base;
	u64		      msr_guest_kernel_gs_base;
#पूर्ण_अगर

	u64		      spec_ctrl;
	u32		      msr_ia32_umरुको_control;

	u32 secondary_exec_control;

	/*
	 * loaded_vmcs poपूर्णांकs to the VMCS currently used in this vcpu. For a
	 * non-nested (L1) guest, it always poपूर्णांकs to vmcs01. For a nested
	 * guest (L2), it poपूर्णांकs to a dअगरferent VMCS.
	 */
	काष्ठा loaded_vmcs    vmcs01;
	काष्ठा loaded_vmcs   *loaded_vmcs;

	काष्ठा msr_स्वतःload अणु
		काष्ठा vmx_msrs guest;
		काष्ठा vmx_msrs host;
	पूर्ण msr_स्वतःload;

	काष्ठा msr_स्वतःstore अणु
		काष्ठा vmx_msrs guest;
	पूर्ण msr_स्वतःstore;

	काष्ठा अणु
		पूर्णांक vm86_active;
		uदीर्घ save_rflags;
		काष्ठा kvm_segment segs[8];
	पूर्ण rmode;
	काष्ठा अणु
		u32 biपंचांगask; /* 4 bits per segment (1 bit per field) */
		काष्ठा kvm_save_segment अणु
			u16 selector;
			अचिन्हित दीर्घ base;
			u32 limit;
			u32 ar;
		पूर्ण seg[8];
	पूर्ण segment_cache;
	पूर्णांक vpid;
	bool emulation_required;

	जोड़ vmx_निकास_reason निकास_reason;

	/* Posted पूर्णांकerrupt descriptor */
	काष्ठा pi_desc pi_desc;

	/* Support क्रम a guest hypervisor (nested VMX) */
	काष्ठा nested_vmx nested;

	/* Dynamic PLE winकरोw. */
	अचिन्हित पूर्णांक ple_winकरोw;
	bool ple_winकरोw_dirty;

	bool req_immediate_निकास;

	/* Support क्रम PML */
#घोषणा PML_ENTITY_NUM		512
	काष्ठा page *pml_pg;

	/* apic deadline value in host tsc */
	u64 hv_deadline_tsc;

	u64 current_tsc_ratio;

	अचिन्हित दीर्घ host_debugctlmsr;

	/*
	 * Only bits masked by msr_ia32_feature_control_valid_bits can be set in
	 * msr_ia32_feature_control. FEAT_CTL_LOCKED is always included
	 * in msr_ia32_feature_control_valid_bits.
	 */
	u64 msr_ia32_feature_control;
	u64 msr_ia32_feature_control_valid_bits;
	/* SGX Launch Control खुला key hash */
	u64 msr_ia32_sgxlepubkeyhash[4];

#अगर IS_ENABLED(CONFIG_HYPERV)
	u64 hv_root_ept;
#पूर्ण_अगर

	काष्ठा pt_desc pt_desc;
	काष्ठा lbr_desc lbr_desc;

	/* Save desired MSR पूर्णांकercept (पढ़ो: pass-through) state */
#घोषणा MAX_POSSIBLE_PASSTHROUGH_MSRS	13
	काष्ठा अणु
		DECLARE_BITMAP(पढ़ो, MAX_POSSIBLE_PASSTHROUGH_MSRS);
		DECLARE_BITMAP(ग_लिखो, MAX_POSSIBLE_PASSTHROUGH_MSRS);
	पूर्ण shaकरोw_msr_पूर्णांकercept;
पूर्ण;

काष्ठा kvm_vmx अणु
	काष्ठा kvm kvm;

	अचिन्हित पूर्णांक tss_addr;
	bool ept_identity_pagetable_करोne;
	gpa_t ept_identity_map_addr;

#अगर IS_ENABLED(CONFIG_HYPERV)
	hpa_t hv_root_ept;
	spinlock_t hv_root_ept_lock;
#पूर्ण_अगर
पूर्ण;

bool nested_vmx_allowed(काष्ठा kvm_vcpu *vcpu);
व्योम vmx_vcpu_load_vmcs(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu,
			काष्ठा loaded_vmcs *buddy);
पूर्णांक allocate_vpid(व्योम);
व्योम मुक्त_vpid(पूर्णांक vpid);
व्योम vmx_set_स्थिरant_host_state(काष्ठा vcpu_vmx *vmx);
व्योम vmx_prepare_चयन_to_guest(काष्ठा kvm_vcpu *vcpu);
व्योम vmx_set_host_fs_gs(काष्ठा vmcs_host_state *host, u16 fs_sel, u16 gs_sel,
			अचिन्हित दीर्घ fs_base, अचिन्हित दीर्घ gs_base);
पूर्णांक vmx_get_cpl(काष्ठा kvm_vcpu *vcpu);
अचिन्हित दीर्घ vmx_get_rflags(काष्ठा kvm_vcpu *vcpu);
व्योम vmx_set_rflags(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ rflags);
u32 vmx_get_पूर्णांकerrupt_shaकरोw(काष्ठा kvm_vcpu *vcpu);
व्योम vmx_set_पूर्णांकerrupt_shaकरोw(काष्ठा kvm_vcpu *vcpu, पूर्णांक mask);
पूर्णांक vmx_set_efer(काष्ठा kvm_vcpu *vcpu, u64 efer);
व्योम vmx_set_cr0(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr0);
व्योम vmx_set_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr4);
व्योम set_cr4_guest_host_mask(काष्ठा vcpu_vmx *vmx);
व्योम ept_save_pdptrs(काष्ठा kvm_vcpu *vcpu);
व्योम vmx_get_segment(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_segment *var, पूर्णांक seg);
व्योम vmx_set_segment(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_segment *var, पूर्णांक seg);
u64 स्थिरruct_eptp(काष्ठा kvm_vcpu *vcpu, hpa_t root_hpa, पूर्णांक root_level);

व्योम vmx_update_exception_biपंचांगap(काष्ठा kvm_vcpu *vcpu);
व्योम vmx_update_msr_biपंचांगap(काष्ठा kvm_vcpu *vcpu);
bool vmx_nmi_blocked(काष्ठा kvm_vcpu *vcpu);
bool vmx_पूर्णांकerrupt_blocked(काष्ठा kvm_vcpu *vcpu);
bool vmx_get_nmi_mask(काष्ठा kvm_vcpu *vcpu);
व्योम vmx_set_nmi_mask(काष्ठा kvm_vcpu *vcpu, bool masked);
व्योम vmx_set_भव_apic_mode(काष्ठा kvm_vcpu *vcpu);
काष्ठा vmx_uret_msr *vmx_find_uret_msr(काष्ठा vcpu_vmx *vmx, u32 msr);
व्योम pt_update_पूर्णांकercept_क्रम_msr(काष्ठा kvm_vcpu *vcpu);
व्योम vmx_update_host_rsp(काष्ठा vcpu_vmx *vmx, अचिन्हित दीर्घ host_rsp);
bool __vmx_vcpu_run(काष्ठा vcpu_vmx *vmx, अचिन्हित दीर्घ *regs, bool launched);
पूर्णांक vmx_find_loadstore_msr_slot(काष्ठा vmx_msrs *m, u32 msr);
व्योम vmx_ept_load_pdptrs(काष्ठा kvm_vcpu *vcpu);

व्योम vmx_disable_पूर्णांकercept_क्रम_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, पूर्णांक type);
व्योम vmx_enable_पूर्णांकercept_क्रम_msr(काष्ठा kvm_vcpu *vcpu, u32 msr, पूर्णांक type);

अटल अंतरभूत व्योम vmx_set_पूर्णांकercept_क्रम_msr(काष्ठा kvm_vcpu *vcpu, u32 msr,
					     पूर्णांक type, bool value)
अणु
	अगर (value)
		vmx_enable_पूर्णांकercept_क्रम_msr(vcpu, msr, type);
	अन्यथा
		vmx_disable_पूर्णांकercept_क्रम_msr(vcpu, msr, type);
पूर्ण

व्योम vmx_update_cpu_dirty_logging(काष्ठा kvm_vcpu *vcpu);

अटल अंतरभूत u8 vmx_get_rvi(व्योम)
अणु
	वापस vmcs_पढ़ो16(GUEST_INTR_STATUS) & 0xff;
पूर्ण

#घोषणा BUILD_CONTROLS_SHADOW(lname, uname)				    \
अटल अंतरभूत व्योम lname##_controls_set(काष्ठा vcpu_vmx *vmx, u32 val)	    \
अणु									    \
	अगर (vmx->loaded_vmcs->controls_shaकरोw.lname != val) अणु		    \
		vmcs_ग_लिखो32(uname, val);				    \
		vmx->loaded_vmcs->controls_shaकरोw.lname = val;		    \
	पूर्ण								    \
पूर्ण									    \
अटल अंतरभूत u32 lname##_controls_get(काष्ठा vcpu_vmx *vmx)		    \
अणु									    \
	वापस vmx->loaded_vmcs->controls_shaकरोw.lname;			    \
पूर्ण									    \
अटल अंतरभूत व्योम lname##_controls_setbit(काष्ठा vcpu_vmx *vmx, u32 val)   \
अणु									    \
	lname##_controls_set(vmx, lname##_controls_get(vmx) | val);	    \
पूर्ण									    \
अटल अंतरभूत व्योम lname##_controls_clearbit(काष्ठा vcpu_vmx *vmx, u32 val) \
अणु									    \
	lname##_controls_set(vmx, lname##_controls_get(vmx) & ~val);	    \
पूर्ण
BUILD_CONTROLS_SHADOW(vm_entry, VM_ENTRY_CONTROLS)
BUILD_CONTROLS_SHADOW(vm_निकास, VM_EXIT_CONTROLS)
BUILD_CONTROLS_SHADOW(pin, PIN_BASED_VM_EXEC_CONTROL)
BUILD_CONTROLS_SHADOW(exec, CPU_BASED_VM_EXEC_CONTROL)
BUILD_CONTROLS_SHADOW(secondary_exec, SECONDARY_VM_EXEC_CONTROL)

अटल अंतरभूत व्योम vmx_रेजिस्टर_cache_reset(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.regs_avail = ~((1 << VCPU_REGS_RIP) | (1 << VCPU_REGS_RSP)
				  | (1 << VCPU_EXREG_RFLAGS)
				  | (1 << VCPU_EXREG_PDPTR)
				  | (1 << VCPU_EXREG_SEGMENTS)
				  | (1 << VCPU_EXREG_CR0)
				  | (1 << VCPU_EXREG_CR3)
				  | (1 << VCPU_EXREG_CR4)
				  | (1 << VCPU_EXREG_EXIT_INFO_1)
				  | (1 << VCPU_EXREG_EXIT_INFO_2));
	vcpu->arch.regs_dirty = 0;
पूर्ण

अटल अंतरभूत u32 vmx_vmentry_ctrl(व्योम)
अणु
	u32 vmentry_ctrl = vmcs_config.vmentry_ctrl;
	अगर (vmx_pt_mode_is_प्रणाली())
		vmentry_ctrl &= ~(VM_ENTRY_PT_CONCEAL_PIP |
				  VM_ENTRY_LOAD_IA32_RTIT_CTL);
	/* Loading of EFER and PERF_GLOBAL_CTRL are toggled dynamically */
	वापस vmentry_ctrl &
		~(VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL | VM_ENTRY_LOAD_IA32_EFER);
पूर्ण

अटल अंतरभूत u32 vmx_vmनिकास_ctrl(व्योम)
अणु
	u32 vmनिकास_ctrl = vmcs_config.vmनिकास_ctrl;
	अगर (vmx_pt_mode_is_प्रणाली())
		vmनिकास_ctrl &= ~(VM_EXIT_PT_CONCEAL_PIP |
				 VM_EXIT_CLEAR_IA32_RTIT_CTL);
	/* Loading of EFER and PERF_GLOBAL_CTRL are toggled dynamically */
	वापस vmनिकास_ctrl &
		~(VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL | VM_EXIT_LOAD_IA32_EFER);
पूर्ण

u32 vmx_exec_control(काष्ठा vcpu_vmx *vmx);
u32 vmx_pin_based_exec_ctrl(काष्ठा vcpu_vmx *vmx);

अटल अंतरभूत काष्ठा kvm_vmx *to_kvm_vmx(काष्ठा kvm *kvm)
अणु
	वापस container_of(kvm, काष्ठा kvm_vmx, kvm);
पूर्ण

अटल अंतरभूत काष्ठा vcpu_vmx *to_vmx(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस container_of(vcpu, काष्ठा vcpu_vmx, vcpu);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ vmx_get_निकास_qual(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (!kvm_रेजिस्टर_is_available(vcpu, VCPU_EXREG_EXIT_INFO_1)) अणु
		kvm_रेजिस्टर_mark_available(vcpu, VCPU_EXREG_EXIT_INFO_1);
		vmx->निकास_qualअगरication = vmcs_पढ़ोl(EXIT_QUALIFICATION);
	पूर्ण
	वापस vmx->निकास_qualअगरication;
पूर्ण

अटल अंतरभूत u32 vmx_get_पूर्णांकr_info(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (!kvm_रेजिस्टर_is_available(vcpu, VCPU_EXREG_EXIT_INFO_2)) अणु
		kvm_रेजिस्टर_mark_available(vcpu, VCPU_EXREG_EXIT_INFO_2);
		vmx->निकास_पूर्णांकr_info = vmcs_पढ़ो32(VM_EXIT_INTR_INFO);
	पूर्ण
	वापस vmx->निकास_पूर्णांकr_info;
पूर्ण

काष्ठा vmcs *alloc_vmcs_cpu(bool shaकरोw, पूर्णांक cpu, gfp_t flags);
व्योम मुक्त_vmcs(काष्ठा vmcs *vmcs);
पूर्णांक alloc_loaded_vmcs(काष्ठा loaded_vmcs *loaded_vmcs);
व्योम मुक्त_loaded_vmcs(काष्ठा loaded_vmcs *loaded_vmcs);
व्योम loaded_vmcs_clear(काष्ठा loaded_vmcs *loaded_vmcs);

अटल अंतरभूत काष्ठा vmcs *alloc_vmcs(bool shaकरोw)
अणु
	वापस alloc_vmcs_cpu(shaकरोw, raw_smp_processor_id(),
			      GFP_KERNEL_ACCOUNT);
पूर्ण

अटल अंतरभूत व्योम decache_tsc_multiplier(काष्ठा vcpu_vmx *vmx)
अणु
	vmx->current_tsc_ratio = vmx->vcpu.arch.tsc_scaling_ratio;
	vmcs_ग_लिखो64(TSC_MULTIPLIER, vmx->current_tsc_ratio);
पूर्ण

अटल अंतरभूत bool vmx_has_रुकोpkg(काष्ठा vcpu_vmx *vmx)
अणु
	वापस vmx->secondary_exec_control &
		SECONDARY_EXEC_ENABLE_USR_WAIT_PAUSE;
पूर्ण

अटल अंतरभूत bool vmx_need_pf_पूर्णांकercept(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!enable_ept)
		वापस true;

	वापस allow_smaller_maxphyaddr && cpuid_maxphyaddr(vcpu) < boot_cpu_data.x86_phys_bits;
पूर्ण

अटल अंतरभूत bool is_unrestricted_guest(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस enable_unrestricted_guest && (!is_guest_mode(vcpu) ||
	    (secondary_exec_controls_get(to_vmx(vcpu)) &
	    SECONDARY_EXEC_UNRESTRICTED_GUEST));
पूर्ण

bool __vmx_guest_state_valid(काष्ठा kvm_vcpu *vcpu);
अटल अंतरभूत bool vmx_guest_state_valid(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस is_unrestricted_guest(vcpu) || __vmx_guest_state_valid(vcpu);
पूर्ण

व्योम dump_vmcs(काष्ठा kvm_vcpu *vcpu);

#पूर्ण_अगर /* __KVM_X86_VMX_H */
