<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_VMX_CAPS_H
#घोषणा __KVM_X86_VMX_CAPS_H

#समावेश <यंत्र/vmx.h>

#समावेश "lapic.h"

बाह्य bool __पढ़ो_mostly enable_vpid;
बाह्य bool __पढ़ो_mostly flexpriority_enabled;
बाह्य bool __पढ़ो_mostly enable_ept;
बाह्य bool __पढ़ो_mostly enable_unrestricted_guest;
बाह्य bool __पढ़ो_mostly enable_ept_ad_bits;
बाह्य bool __पढ़ो_mostly enable_pml;
बाह्य bool __पढ़ो_mostly enable_apicv;
बाह्य पूर्णांक __पढ़ो_mostly pt_mode;

#घोषणा PT_MODE_SYSTEM		0
#घोषणा PT_MODE_HOST_GUEST	1

#घोषणा PMU_CAP_FW_WRITES	(1ULL << 13)
#घोषणा PMU_CAP_LBR_FMT		0x3f

#घोषणा DEBUGCTLMSR_LBR_MASK		(DEBUGCTLMSR_LBR | DEBUGCTLMSR_FREEZE_LBRS_ON_PMI)

काष्ठा nested_vmx_msrs अणु
	/*
	 * We only store the "true" versions of the VMX capability MSRs. We
	 * generate the "non-true" versions by setting the must-be-1 bits
	 * according to the SDM.
	 */
	u32 procbased_ctls_low;
	u32 procbased_ctls_high;
	u32 secondary_ctls_low;
	u32 secondary_ctls_high;
	u32 pinbased_ctls_low;
	u32 pinbased_ctls_high;
	u32 निकास_ctls_low;
	u32 निकास_ctls_high;
	u32 entry_ctls_low;
	u32 entry_ctls_high;
	u32 misc_low;
	u32 misc_high;
	u32 ept_caps;
	u32 vpid_caps;
	u64 basic;
	u64 cr0_fixed0;
	u64 cr0_fixed1;
	u64 cr4_fixed0;
	u64 cr4_fixed1;
	u64 vmcs_क्रमागत;
	u64 vmfunc_controls;
पूर्ण;

काष्ठा vmcs_config अणु
	पूर्णांक size;
	पूर्णांक order;
	u32 basic_cap;
	u32 revision_id;
	u32 pin_based_exec_ctrl;
	u32 cpu_based_exec_ctrl;
	u32 cpu_based_2nd_exec_ctrl;
	u32 vmनिकास_ctrl;
	u32 vmentry_ctrl;
	काष्ठा nested_vmx_msrs nested;
पूर्ण;
बाह्य काष्ठा vmcs_config vmcs_config;

काष्ठा vmx_capability अणु
	u32 ept;
	u32 vpid;
पूर्ण;
बाह्य काष्ठा vmx_capability vmx_capability;

अटल अंतरभूत bool cpu_has_vmx_basic_inout(व्योम)
अणु
	वापस	(((u64)vmcs_config.basic_cap << 32) & VMX_BASIC_INOUT);
पूर्ण

अटल अंतरभूत bool cpu_has_भव_nmis(व्योम)
अणु
	वापस vmcs_config.pin_based_exec_ctrl & PIN_BASED_VIRTUAL_NMIS;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_preemption_समयr(व्योम)
अणु
	वापस vmcs_config.pin_based_exec_ctrl &
		PIN_BASED_VMX_PREEMPTION_TIMER;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_posted_पूर्णांकr(व्योम)
अणु
	वापस vmcs_config.pin_based_exec_ctrl & PIN_BASED_POSTED_INTR;
पूर्ण

अटल अंतरभूत bool cpu_has_load_ia32_efer(व्योम)
अणु
	वापस (vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_EFER) &&
	       (vmcs_config.vmनिकास_ctrl & VM_EXIT_LOAD_IA32_EFER);
पूर्ण

अटल अंतरभूत bool cpu_has_load_perf_global_ctrl(व्योम)
अणु
	वापस (vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL) &&
	       (vmcs_config.vmनिकास_ctrl & VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL);
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_mpx(व्योम)
अणु
	वापस (vmcs_config.vmनिकास_ctrl & VM_EXIT_CLEAR_BNDCFGS) &&
		(vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_BNDCFGS);
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_tpr_shaकरोw(व्योम)
अणु
	वापस vmcs_config.cpu_based_exec_ctrl & CPU_BASED_TPR_SHADOW;
पूर्ण

अटल अंतरभूत bool cpu_need_tpr_shaकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस cpu_has_vmx_tpr_shaकरोw() && lapic_in_kernel(vcpu);
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_msr_biपंचांगap(व्योम)
अणु
	वापस vmcs_config.cpu_based_exec_ctrl & CPU_BASED_USE_MSR_BITMAPS;
पूर्ण

अटल अंतरभूत bool cpu_has_secondary_exec_ctrls(व्योम)
अणु
	वापस vmcs_config.cpu_based_exec_ctrl &
		CPU_BASED_ACTIVATE_SECONDARY_CONTROLS;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_भवize_apic_accesses(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_ept(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_ENABLE_EPT;
पूर्ण

अटल अंतरभूत bool vmx_umip_emulated(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_DESC;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_rdtscp(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_ENABLE_RDTSCP;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_भवize_x2apic_mode(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_vpid(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_ENABLE_VPID;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_wbinvd_निकास(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_WBINVD_EXITING;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_unrestricted_guest(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_UNRESTRICTED_GUEST;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_apic_रेजिस्टर_virt(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_APIC_REGISTER_VIRT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_भव_पूर्णांकr_delivery(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_ple(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_PAUSE_LOOP_EXITING;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_rdअक्रम(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_RDRAND_EXITING;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_invpcid(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_ENABLE_INVPCID;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_vmfunc(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_ENABLE_VMFUNC;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_shaकरोw_vmcs(व्योम)
अणु
	u64 vmx_msr;

	/* check अगर the cpu supports writing r/o निकास inक्रमmation fields */
	rdmsrl(MSR_IA32_VMX_MISC, vmx_msr);
	अगर (!(vmx_msr & MSR_IA32_VMX_MISC_VMWRITE_SHADOW_RO_FIELDS))
		वापस false;

	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_SHADOW_VMCS;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_encls_vmनिकास(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_ENCLS_EXITING;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_rdseed(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_RDSEED_EXITING;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_pml(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl & SECONDARY_EXEC_ENABLE_PML;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_xsaves(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_XSAVES;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_रुकोpkg(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_ENABLE_USR_WAIT_PAUSE;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_tsc_scaling(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_TSC_SCALING;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_bus_lock_detection(व्योम)
अणु
	वापस vmcs_config.cpu_based_2nd_exec_ctrl &
	    SECONDARY_EXEC_BUS_LOCK_DETECTION;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_apicv(व्योम)
अणु
	वापस cpu_has_vmx_apic_रेजिस्टर_virt() &&
		cpu_has_vmx_भव_पूर्णांकr_delivery() &&
		cpu_has_vmx_posted_पूर्णांकr();
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_flexpriority(व्योम)
अणु
	वापस cpu_has_vmx_tpr_shaकरोw() &&
		cpu_has_vmx_भवize_apic_accesses();
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_ept_execute_only(व्योम)
अणु
	वापस vmx_capability.ept & VMX_EPT_EXECUTE_ONLY_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_ept_4levels(व्योम)
अणु
	वापस vmx_capability.ept & VMX_EPT_PAGE_WALK_4_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_ept_5levels(व्योम)
अणु
	वापस vmx_capability.ept & VMX_EPT_PAGE_WALK_5_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_ept_mt_wb(व्योम)
अणु
	वापस vmx_capability.ept & VMX_EPTP_WB_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_ept_2m_page(व्योम)
अणु
	वापस vmx_capability.ept & VMX_EPT_2MB_PAGE_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_ept_1g_page(व्योम)
अणु
	वापस vmx_capability.ept & VMX_EPT_1GB_PAGE_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_ept_ad_bits(व्योम)
अणु
	वापस vmx_capability.ept & VMX_EPT_AD_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_invept_context(व्योम)
अणु
	वापस vmx_capability.ept & VMX_EPT_EXTENT_CONTEXT_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_invept_global(व्योम)
अणु
	वापस vmx_capability.ept & VMX_EPT_EXTENT_GLOBAL_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_invvpid(व्योम)
अणु
	वापस vmx_capability.vpid & VMX_VPID_INVVPID_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_invvpid_inभागidual_addr(व्योम)
अणु
	वापस vmx_capability.vpid & VMX_VPID_EXTENT_INDIVIDUAL_ADDR_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_invvpid_single(व्योम)
अणु
	वापस vmx_capability.vpid & VMX_VPID_EXTENT_SINGLE_CONTEXT_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_invvpid_global(व्योम)
अणु
	वापस vmx_capability.vpid & VMX_VPID_EXTENT_GLOBAL_CONTEXT_BIT;
पूर्ण

अटल अंतरभूत bool cpu_has_vmx_पूर्णांकel_pt(व्योम)
अणु
	u64 vmx_msr;

	rdmsrl(MSR_IA32_VMX_MISC, vmx_msr);
	वापस (vmx_msr & MSR_IA32_VMX_MISC_INTEL_PT) &&
		(vmcs_config.cpu_based_2nd_exec_ctrl & SECONDARY_EXEC_PT_USE_GPA) &&
		(vmcs_config.vmनिकास_ctrl & VM_EXIT_CLEAR_IA32_RTIT_CTL) &&
		(vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_RTIT_CTL);
पूर्ण

/*
 * Processor Trace can operate in one of three modes:
 *  a. प्रणाली-wide: trace both host/guest and output to host buffer
 *  b. host-only:   only trace host and output to host buffer
 *  c. host-guest:  trace host and guest simultaneously and output to their
 *                  respective buffer
 *
 * KVM currently only supports (a) and (c).
 */
अटल अंतरभूत bool vmx_pt_mode_is_प्रणाली(व्योम)
अणु
	वापस pt_mode == PT_MODE_SYSTEM;
पूर्ण
अटल अंतरभूत bool vmx_pt_mode_is_host_guest(व्योम)
अणु
	वापस pt_mode == PT_MODE_HOST_GUEST;
पूर्ण

अटल अंतरभूत u64 vmx_get_perf_capabilities(व्योम)
अणु
	u64 perf_cap = 0;

	अगर (boot_cpu_has(X86_FEATURE_PDCM))
		rdmsrl(MSR_IA32_PERF_CAPABILITIES, perf_cap);

	perf_cap &= PMU_CAP_LBR_FMT;

	/*
	 * Since counters are भवized, KVM would support full
	 * width counting unconditionally, even अगर the host lacks it.
	 */
	वापस PMU_CAP_FW_WRITES | perf_cap;
पूर्ण

अटल अंतरभूत u64 vmx_supported_debugctl(व्योम)
अणु
	u64 debugctl = 0;

	अगर (boot_cpu_has(X86_FEATURE_BUS_LOCK_DETECT))
		debugctl |= DEBUGCTLMSR_BUS_LOCK_DETECT;

	अगर (vmx_get_perf_capabilities() & PMU_CAP_LBR_FMT)
		debugctl |= DEBUGCTLMSR_LBR_MASK;

	वापस debugctl;
पूर्ण

#पूर्ण_अगर /* __KVM_X86_VMX_CAPS_H */
