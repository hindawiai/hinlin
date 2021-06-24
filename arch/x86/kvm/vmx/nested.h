<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_VMX_NESTED_H
#घोषणा __KVM_X86_VMX_NESTED_H

#समावेश "kvm_cache_regs.h"
#समावेश "vmcs12.h"
#समावेश "vmx.h"

/*
 * Status वापसed by nested_vmx_enter_non_root_mode():
 */
क्रमागत nvmx_vmentry_status अणु
	NVMX_VMENTRY_SUCCESS,		/* Entered VMX non-root mode */
	NVMX_VMENTRY_VMFAIL,		/* Consistency check VMFail */
	NVMX_VMENTRY_VMEXIT,		/* Consistency check VMExit */
	NVMX_VMENTRY_KVM_INTERNAL_ERROR,/* KVM पूर्णांकernal error */
पूर्ण;

व्योम vmx_leave_nested(काष्ठा kvm_vcpu *vcpu);
व्योम nested_vmx_setup_ctls_msrs(काष्ठा nested_vmx_msrs *msrs, u32 ept_caps);
व्योम nested_vmx_hardware_unsetup(व्योम);
__init पूर्णांक nested_vmx_hardware_setup(पूर्णांक (*निकास_handlers[])(काष्ठा kvm_vcpu *));
व्योम nested_vmx_set_vmcs_shaकरोwing_biपंचांगap(व्योम);
व्योम nested_vmx_मुक्त_vcpu(काष्ठा kvm_vcpu *vcpu);
क्रमागत nvmx_vmentry_status nested_vmx_enter_non_root_mode(काष्ठा kvm_vcpu *vcpu,
						     bool from_vmentry);
bool nested_vmx_reflect_vmनिकास(काष्ठा kvm_vcpu *vcpu);
व्योम nested_vmx_vmनिकास(काष्ठा kvm_vcpu *vcpu, u32 vm_निकास_reason,
		       u32 निकास_पूर्णांकr_info, अचिन्हित दीर्घ निकास_qualअगरication);
व्योम nested_sync_vmcs12_to_shaकरोw(काष्ठा kvm_vcpu *vcpu);
पूर्णांक vmx_set_vmx_msr(काष्ठा kvm_vcpu *vcpu, u32 msr_index, u64 data);
पूर्णांक vmx_get_vmx_msr(काष्ठा nested_vmx_msrs *msrs, u32 msr_index, u64 *pdata);
पूर्णांक get_vmx_mem_address(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ निकास_qualअगरication,
			u32 vmx_inकाष्ठाion_info, bool wr, पूर्णांक len, gva_t *ret);
व्योम nested_vmx_pmu_entry_निकास_ctls_update(काष्ठा kvm_vcpu *vcpu);
व्योम nested_mark_vmcs12_pages_dirty(काष्ठा kvm_vcpu *vcpu);
bool nested_vmx_check_io_biपंचांगaps(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक port,
				 पूर्णांक size);

अटल अंतरभूत काष्ठा vmcs12 *get_vmcs12(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस to_vmx(vcpu)->nested.cached_vmcs12;
पूर्ण

अटल अंतरभूत काष्ठा vmcs12 *get_shaकरोw_vmcs12(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस to_vmx(vcpu)->nested.cached_shaकरोw_vmcs12;
पूर्ण

/*
 * Note: the same condition is checked against the state provided by userspace
 * in vmx_set_nested_state; अगर it is satisfied, the nested state must include
 * the VMCS12.
 */
अटल अंतरभूत पूर्णांक vmx_has_valid_vmcs12(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * In हाल we करो two consecutive get/set_nested_state()s जबतक L2 was
	 * running hv_evmcs may end up not being mapped (we map it from
	 * nested_vmx_run()/vmx_vcpu_run()). Check is_guest_mode() as we always
	 * have vmcs12 अगर it is true.
	 */
	वापस is_guest_mode(vcpu) || vmx->nested.current_vmptr != -1ull ||
		vmx->nested.hv_evmcs;
पूर्ण

अटल अंतरभूत u16 nested_get_vpid02(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	वापस vmx->nested.vpid02 ? vmx->nested.vpid02 : vmx->vpid;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ nested_ept_get_eptp(काष्ठा kvm_vcpu *vcpu)
अणु
	/* वापस the page table to be shaकरोwed - in our हाल, EPT12 */
	वापस get_vmcs12(vcpu)->ept_poपूर्णांकer;
पूर्ण

अटल अंतरभूत bool nested_ept_ad_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस nested_ept_get_eptp(vcpu) & VMX_EPTP_AD_ENABLE_BIT;
पूर्ण

/*
 * Return the cr0 value that a nested guest would पढ़ो. This is a combination
 * of the real cr0 used to run the guest (guest_cr0), and the bits shaकरोwed by
 * its hypervisor (cr0_पढ़ो_shaकरोw).
 */
अटल अंतरभूत अचिन्हित दीर्घ nested_पढ़ो_cr0(काष्ठा vmcs12 *fields)
अणु
	वापस (fields->guest_cr0 & ~fields->cr0_guest_host_mask) |
		(fields->cr0_पढ़ो_shaकरोw & fields->cr0_guest_host_mask);
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ nested_पढ़ो_cr4(काष्ठा vmcs12 *fields)
अणु
	वापस (fields->guest_cr4 & ~fields->cr4_guest_host_mask) |
		(fields->cr4_पढ़ो_shaकरोw & fields->cr4_guest_host_mask);
पूर्ण

अटल अंतरभूत अचिन्हित nested_cpu_vmx_misc_cr3_count(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vmx_misc_cr3_count(to_vmx(vcpu)->nested.msrs.misc_low);
पूर्ण

/*
 * Do the भव VMX capability MSRs specअगरy that L1 can use VMWRITE
 * to modअगरy any valid field of the VMCS, or are the VM-निकास
 * inक्रमmation fields पढ़ो-only?
 */
अटल अंतरभूत bool nested_cpu_has_vmग_लिखो_any_field(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस to_vmx(vcpu)->nested.msrs.misc_low &
		MSR_IA32_VMX_MISC_VMWRITE_SHADOW_RO_FIELDS;
पूर्ण

अटल अंतरभूत bool nested_cpu_has_zero_length_injection(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस to_vmx(vcpu)->nested.msrs.misc_low & VMX_MISC_ZERO_LEN_INS;
पूर्ण

अटल अंतरभूत bool nested_cpu_supports_monitor_trap_flag(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस to_vmx(vcpu)->nested.msrs.procbased_ctls_high &
			CPU_BASED_MONITOR_TRAP_FLAG;
पूर्ण

अटल अंतरभूत bool nested_cpu_has_vmx_shaकरोw_vmcs(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस to_vmx(vcpu)->nested.msrs.secondary_ctls_high &
		SECONDARY_EXEC_SHADOW_VMCS;
पूर्ण

अटल अंतरभूत bool nested_cpu_has(काष्ठा vmcs12 *vmcs12, u32 bit)
अणु
	वापस vmcs12->cpu_based_vm_exec_control & bit;
पूर्ण

अटल अंतरभूत bool nested_cpu_has2(काष्ठा vmcs12 *vmcs12, u32 bit)
अणु
	वापस (vmcs12->cpu_based_vm_exec_control &
			CPU_BASED_ACTIVATE_SECONDARY_CONTROLS) &&
		(vmcs12->secondary_vm_exec_control & bit);
पूर्ण

अटल अंतरभूत bool nested_cpu_has_preemption_समयr(काष्ठा vmcs12 *vmcs12)
अणु
	वापस vmcs12->pin_based_vm_exec_control &
		PIN_BASED_VMX_PREEMPTION_TIMER;
पूर्ण

अटल अंतरभूत bool nested_cpu_has_nmi_निकासing(काष्ठा vmcs12 *vmcs12)
अणु
	वापस vmcs12->pin_based_vm_exec_control & PIN_BASED_NMI_EXITING;
पूर्ण

अटल अंतरभूत bool nested_cpu_has_भव_nmis(काष्ठा vmcs12 *vmcs12)
अणु
	वापस vmcs12->pin_based_vm_exec_control & PIN_BASED_VIRTUAL_NMIS;
पूर्ण

अटल अंतरभूत पूर्णांक nested_cpu_has_mtf(काष्ठा vmcs12 *vmcs12)
अणु
	वापस nested_cpu_has(vmcs12, CPU_BASED_MONITOR_TRAP_FLAG);
पूर्ण

अटल अंतरभूत पूर्णांक nested_cpu_has_ept(काष्ठा vmcs12 *vmcs12)
अणु
	वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_ENABLE_EPT);
पूर्ण

अटल अंतरभूत bool nested_cpu_has_xsaves(काष्ठा vmcs12 *vmcs12)
अणु
	वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_XSAVES);
पूर्ण

अटल अंतरभूत bool nested_cpu_has_pml(काष्ठा vmcs12 *vmcs12)
अणु
	वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_ENABLE_PML);
पूर्ण

अटल अंतरभूत bool nested_cpu_has_virt_x2apic_mode(काष्ठा vmcs12 *vmcs12)
अणु
	वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE);
पूर्ण

अटल अंतरभूत bool nested_cpu_has_vpid(काष्ठा vmcs12 *vmcs12)
अणु
	वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_ENABLE_VPID);
पूर्ण

अटल अंतरभूत bool nested_cpu_has_apic_reg_virt(काष्ठा vmcs12 *vmcs12)
अणु
	वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_APIC_REGISTER_VIRT);
पूर्ण

अटल अंतरभूत bool nested_cpu_has_vid(काष्ठा vmcs12 *vmcs12)
अणु
	वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY);
पूर्ण

अटल अंतरभूत bool nested_cpu_has_posted_पूर्णांकr(काष्ठा vmcs12 *vmcs12)
अणु
	वापस vmcs12->pin_based_vm_exec_control & PIN_BASED_POSTED_INTR;
पूर्ण

अटल अंतरभूत bool nested_cpu_has_vmfunc(काष्ठा vmcs12 *vmcs12)
अणु
	वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_ENABLE_VMFUNC);
पूर्ण

अटल अंतरभूत bool nested_cpu_has_eptp_चयनing(काष्ठा vmcs12 *vmcs12)
अणु
	वापस nested_cpu_has_vmfunc(vmcs12) &&
		(vmcs12->vm_function_control &
		 VMX_VMFUNC_EPTP_SWITCHING);
पूर्ण

अटल अंतरभूत bool nested_cpu_has_shaकरोw_vmcs(काष्ठा vmcs12 *vmcs12)
अणु
	वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_SHADOW_VMCS);
पूर्ण

अटल अंतरभूत bool nested_cpu_has_save_preemption_समयr(काष्ठा vmcs12 *vmcs12)
अणु
	वापस vmcs12->vm_निकास_controls &
	    VM_EXIT_SAVE_VMX_PREEMPTION_TIMER;
पूर्ण

अटल अंतरभूत bool nested_निकास_on_nmi(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस nested_cpu_has_nmi_निकासing(get_vmcs12(vcpu));
पूर्ण

/*
 * In nested भवization, check अगर L1 asked to निकास on बाह्यal पूर्णांकerrupts.
 * For most existing hypervisors, this will always वापस true.
 */
अटल अंतरभूत bool nested_निकास_on_पूर्णांकr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस get_vmcs12(vcpu)->pin_based_vm_exec_control &
		PIN_BASED_EXT_INTR_MASK;
पूर्ण

अटल अंतरभूत bool nested_cpu_has_encls_निकास(काष्ठा vmcs12 *vmcs12)
अणु
	वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_ENCLS_EXITING);
पूर्ण

/*
 * अगर fixed0[i] == 1: val[i] must be 1
 * अगर fixed1[i] == 0: val[i] must be 0
 */
अटल अंतरभूत bool fixed_bits_valid(u64 val, u64 fixed0, u64 fixed1)
अणु
	वापस ((val & fixed1) | fixed0) == val;
पूर्ण

अटल अंतरभूत bool nested_guest_cr0_valid(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ val)
अणु
	u64 fixed0 = to_vmx(vcpu)->nested.msrs.cr0_fixed0;
	u64 fixed1 = to_vmx(vcpu)->nested.msrs.cr0_fixed1;
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);

	अगर (to_vmx(vcpu)->nested.msrs.secondary_ctls_high &
		SECONDARY_EXEC_UNRESTRICTED_GUEST &&
	    nested_cpu_has2(vmcs12, SECONDARY_EXEC_UNRESTRICTED_GUEST))
		fixed0 &= ~(X86_CR0_PE | X86_CR0_PG);

	वापस fixed_bits_valid(val, fixed0, fixed1);
पूर्ण

अटल अंतरभूत bool nested_host_cr0_valid(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ val)
अणु
	u64 fixed0 = to_vmx(vcpu)->nested.msrs.cr0_fixed0;
	u64 fixed1 = to_vmx(vcpu)->nested.msrs.cr0_fixed1;

	वापस fixed_bits_valid(val, fixed0, fixed1);
पूर्ण

अटल अंतरभूत bool nested_cr4_valid(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ val)
अणु
	u64 fixed0 = to_vmx(vcpu)->nested.msrs.cr4_fixed0;
	u64 fixed1 = to_vmx(vcpu)->nested.msrs.cr4_fixed1;

	वापस fixed_bits_valid(val, fixed0, fixed1);
पूर्ण

/* No dअगरference in the restrictions on guest and host CR4 in VMX operation. */
#घोषणा nested_guest_cr4_valid	nested_cr4_valid
#घोषणा nested_host_cr4_valid	nested_cr4_valid

बाह्य काष्ठा kvm_x86_nested_ops vmx_nested_ops;

#पूर्ण_अगर /* __KVM_X86_VMX_NESTED_H */
