<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * tools/testing/selftests/kvm/include/vmx.h
 *
 * Copyright (C) 2018, Red Hat, Inc.
 *
 */

#अगर_अघोषित SELFTEST_KVM_EVMCS_H
#घोषणा SELFTEST_KVM_EVMCS_H

#समावेश <मानक_निवेशt.h>
#समावेश "vmx.h"

#घोषणा u16 uपूर्णांक16_t
#घोषणा u32 uपूर्णांक32_t
#घोषणा u64 uपूर्णांक64_t

#घोषणा EVMCS_VERSION 1

बाह्य bool enable_evmcs;

काष्ठा hv_vp_assist_page अणु
	__u32 apic_assist;
	__u32 reserved;
	__u64 vtl_control[2];
	__u64 nested_enlightenments_control[2];
	__u32 enlighten_vmentry;
	__u64 current_nested_vmcs;
पूर्ण;

काष्ठा hv_enlightened_vmcs अणु
	u32 revision_id;
	u32 पात;

	u16 host_es_selector;
	u16 host_cs_selector;
	u16 host_ss_selector;
	u16 host_ds_selector;
	u16 host_fs_selector;
	u16 host_gs_selector;
	u16 host_tr_selector;

	u64 host_ia32_pat;
	u64 host_ia32_efer;

	u64 host_cr0;
	u64 host_cr3;
	u64 host_cr4;

	u64 host_ia32_sysenter_esp;
	u64 host_ia32_sysenter_eip;
	u64 host_rip;
	u32 host_ia32_sysenter_cs;

	u32 pin_based_vm_exec_control;
	u32 vm_निकास_controls;
	u32 secondary_vm_exec_control;

	u64 io_biपंचांगap_a;
	u64 io_biपंचांगap_b;
	u64 msr_biपंचांगap;

	u16 guest_es_selector;
	u16 guest_cs_selector;
	u16 guest_ss_selector;
	u16 guest_ds_selector;
	u16 guest_fs_selector;
	u16 guest_gs_selector;
	u16 guest_ldtr_selector;
	u16 guest_tr_selector;

	u32 guest_es_limit;
	u32 guest_cs_limit;
	u32 guest_ss_limit;
	u32 guest_ds_limit;
	u32 guest_fs_limit;
	u32 guest_gs_limit;
	u32 guest_ldtr_limit;
	u32 guest_tr_limit;
	u32 guest_gdtr_limit;
	u32 guest_idtr_limit;

	u32 guest_es_ar_bytes;
	u32 guest_cs_ar_bytes;
	u32 guest_ss_ar_bytes;
	u32 guest_ds_ar_bytes;
	u32 guest_fs_ar_bytes;
	u32 guest_gs_ar_bytes;
	u32 guest_ldtr_ar_bytes;
	u32 guest_tr_ar_bytes;

	u64 guest_es_base;
	u64 guest_cs_base;
	u64 guest_ss_base;
	u64 guest_ds_base;
	u64 guest_fs_base;
	u64 guest_gs_base;
	u64 guest_ldtr_base;
	u64 guest_tr_base;
	u64 guest_gdtr_base;
	u64 guest_idtr_base;

	u64 padding64_1[3];

	u64 vm_निकास_msr_store_addr;
	u64 vm_निकास_msr_load_addr;
	u64 vm_entry_msr_load_addr;

	u64 cr3_target_value0;
	u64 cr3_target_value1;
	u64 cr3_target_value2;
	u64 cr3_target_value3;

	u32 page_fault_error_code_mask;
	u32 page_fault_error_code_match;

	u32 cr3_target_count;
	u32 vm_निकास_msr_store_count;
	u32 vm_निकास_msr_load_count;
	u32 vm_entry_msr_load_count;

	u64 tsc_offset;
	u64 भव_apic_page_addr;
	u64 vmcs_link_poपूर्णांकer;

	u64 guest_ia32_debugctl;
	u64 guest_ia32_pat;
	u64 guest_ia32_efer;

	u64 guest_pdptr0;
	u64 guest_pdptr1;
	u64 guest_pdptr2;
	u64 guest_pdptr3;

	u64 guest_pending_dbg_exceptions;
	u64 guest_sysenter_esp;
	u64 guest_sysenter_eip;

	u32 guest_activity_state;
	u32 guest_sysenter_cs;

	u64 cr0_guest_host_mask;
	u64 cr4_guest_host_mask;
	u64 cr0_पढ़ो_shaकरोw;
	u64 cr4_पढ़ो_shaकरोw;
	u64 guest_cr0;
	u64 guest_cr3;
	u64 guest_cr4;
	u64 guest_dr7;

	u64 host_fs_base;
	u64 host_gs_base;
	u64 host_tr_base;
	u64 host_gdtr_base;
	u64 host_idtr_base;
	u64 host_rsp;

	u64 ept_poपूर्णांकer;

	u16 भव_processor_id;
	u16 padding16[3];

	u64 padding64_2[5];
	u64 guest_physical_address;

	u32 vm_inकाष्ठाion_error;
	u32 vm_निकास_reason;
	u32 vm_निकास_पूर्णांकr_info;
	u32 vm_निकास_पूर्णांकr_error_code;
	u32 idt_vectoring_info_field;
	u32 idt_vectoring_error_code;
	u32 vm_निकास_inकाष्ठाion_len;
	u32 vmx_inकाष्ठाion_info;

	u64 निकास_qualअगरication;
	u64 निकास_io_inकाष्ठाion_ecx;
	u64 निकास_io_inकाष्ठाion_esi;
	u64 निकास_io_inकाष्ठाion_edi;
	u64 निकास_io_inकाष्ठाion_eip;

	u64 guest_linear_address;
	u64 guest_rsp;
	u64 guest_rflags;

	u32 guest_पूर्णांकerruptibility_info;
	u32 cpu_based_vm_exec_control;
	u32 exception_biपंचांगap;
	u32 vm_entry_controls;
	u32 vm_entry_पूर्णांकr_info_field;
	u32 vm_entry_exception_error_code;
	u32 vm_entry_inकाष्ठाion_len;
	u32 tpr_threshold;

	u64 guest_rip;

	u32 hv_clean_fields;
	u32 hv_padding_32;
	u32 hv_synthetic_controls;
	काष्ठा अणु
		u32 nested_flush_hypercall:1;
		u32 msr_biपंचांगap:1;
		u32 reserved:30;
	पूर्ण hv_enlightenments_control;
	u32 hv_vp_id;

	u64 hv_vm_id;
	u64 partition_assist_page;
	u64 padding64_4[4];
	u64 guest_bndcfgs;
	u64 padding64_5[7];
	u64 xss_निकास_biपंचांगap;
	u64 padding64_6[7];
पूर्ण;

#घोषणा HV_X64_MSR_VP_ASSIST_PAGE		0x40000073
#घोषणा HV_X64_MSR_VP_ASSIST_PAGE_ENABLE	0x00000001
#घोषणा HV_X64_MSR_VP_ASSIST_PAGE_ADDRESS_SHIFT	12
#घोषणा HV_X64_MSR_VP_ASSIST_PAGE_ADDRESS_MASK	\
		(~((1ull << HV_X64_MSR_VP_ASSIST_PAGE_ADDRESS_SHIFT) - 1))

बाह्य काष्ठा hv_enlightened_vmcs *current_evmcs;
बाह्य काष्ठा hv_vp_assist_page *current_vp_assist;

पूर्णांक vcpu_enable_evmcs(काष्ठा kvm_vm *vm, पूर्णांक vcpu_id);

अटल अंतरभूत पूर्णांक enable_vp_assist(uपूर्णांक64_t vp_assist_pa, व्योम *vp_assist)
अणु
	u64 val = (vp_assist_pa & HV_X64_MSR_VP_ASSIST_PAGE_ADDRESS_MASK) |
		HV_X64_MSR_VP_ASSIST_PAGE_ENABLE;

	wrmsr(HV_X64_MSR_VP_ASSIST_PAGE, val);

	current_vp_assist = vp_assist;

	enable_evmcs = true;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक evmcs_vmptrld(uपूर्णांक64_t vmcs_pa, व्योम *vmcs)
अणु
	current_vp_assist->current_nested_vmcs = vmcs_pa;
	current_vp_assist->enlighten_vmentry = 1;

	current_evmcs = vmcs;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक evmcs_vmptrst(uपूर्णांक64_t *value)
अणु
	*value = current_vp_assist->current_nested_vmcs &
		~HV_X64_MSR_VP_ASSIST_PAGE_ENABLE;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक evmcs_vmपढ़ो(uपूर्णांक64_t encoding, uपूर्णांक64_t *value)
अणु
	चयन (encoding) अणु
	हाल GUEST_RIP:
		*value = current_evmcs->guest_rip;
		अवरोध;
	हाल GUEST_RSP:
		*value = current_evmcs->guest_rsp;
		अवरोध;
	हाल GUEST_RFLAGS:
		*value = current_evmcs->guest_rflags;
		अवरोध;
	हाल HOST_IA32_PAT:
		*value = current_evmcs->host_ia32_pat;
		अवरोध;
	हाल HOST_IA32_EFER:
		*value = current_evmcs->host_ia32_efer;
		अवरोध;
	हाल HOST_CR0:
		*value = current_evmcs->host_cr0;
		अवरोध;
	हाल HOST_CR3:
		*value = current_evmcs->host_cr3;
		अवरोध;
	हाल HOST_CR4:
		*value = current_evmcs->host_cr4;
		अवरोध;
	हाल HOST_IA32_SYSENTER_ESP:
		*value = current_evmcs->host_ia32_sysenter_esp;
		अवरोध;
	हाल HOST_IA32_SYSENTER_EIP:
		*value = current_evmcs->host_ia32_sysenter_eip;
		अवरोध;
	हाल HOST_RIP:
		*value = current_evmcs->host_rip;
		अवरोध;
	हाल IO_BITMAP_A:
		*value = current_evmcs->io_biपंचांगap_a;
		अवरोध;
	हाल IO_BITMAP_B:
		*value = current_evmcs->io_biपंचांगap_b;
		अवरोध;
	हाल MSR_BITMAP:
		*value = current_evmcs->msr_biपंचांगap;
		अवरोध;
	हाल GUEST_ES_BASE:
		*value = current_evmcs->guest_es_base;
		अवरोध;
	हाल GUEST_CS_BASE:
		*value = current_evmcs->guest_cs_base;
		अवरोध;
	हाल GUEST_SS_BASE:
		*value = current_evmcs->guest_ss_base;
		अवरोध;
	हाल GUEST_DS_BASE:
		*value = current_evmcs->guest_ds_base;
		अवरोध;
	हाल GUEST_FS_BASE:
		*value = current_evmcs->guest_fs_base;
		अवरोध;
	हाल GUEST_GS_BASE:
		*value = current_evmcs->guest_gs_base;
		अवरोध;
	हाल GUEST_LDTR_BASE:
		*value = current_evmcs->guest_ldtr_base;
		अवरोध;
	हाल GUEST_TR_BASE:
		*value = current_evmcs->guest_tr_base;
		अवरोध;
	हाल GUEST_GDTR_BASE:
		*value = current_evmcs->guest_gdtr_base;
		अवरोध;
	हाल GUEST_IDTR_BASE:
		*value = current_evmcs->guest_idtr_base;
		अवरोध;
	हाल TSC_OFFSET:
		*value = current_evmcs->tsc_offset;
		अवरोध;
	हाल VIRTUAL_APIC_PAGE_ADDR:
		*value = current_evmcs->भव_apic_page_addr;
		अवरोध;
	हाल VMCS_LINK_POINTER:
		*value = current_evmcs->vmcs_link_poपूर्णांकer;
		अवरोध;
	हाल GUEST_IA32_DEBUGCTL:
		*value = current_evmcs->guest_ia32_debugctl;
		अवरोध;
	हाल GUEST_IA32_PAT:
		*value = current_evmcs->guest_ia32_pat;
		अवरोध;
	हाल GUEST_IA32_EFER:
		*value = current_evmcs->guest_ia32_efer;
		अवरोध;
	हाल GUEST_PDPTR0:
		*value = current_evmcs->guest_pdptr0;
		अवरोध;
	हाल GUEST_PDPTR1:
		*value = current_evmcs->guest_pdptr1;
		अवरोध;
	हाल GUEST_PDPTR2:
		*value = current_evmcs->guest_pdptr2;
		अवरोध;
	हाल GUEST_PDPTR3:
		*value = current_evmcs->guest_pdptr3;
		अवरोध;
	हाल GUEST_PENDING_DBG_EXCEPTIONS:
		*value = current_evmcs->guest_pending_dbg_exceptions;
		अवरोध;
	हाल GUEST_SYSENTER_ESP:
		*value = current_evmcs->guest_sysenter_esp;
		अवरोध;
	हाल GUEST_SYSENTER_EIP:
		*value = current_evmcs->guest_sysenter_eip;
		अवरोध;
	हाल CR0_GUEST_HOST_MASK:
		*value = current_evmcs->cr0_guest_host_mask;
		अवरोध;
	हाल CR4_GUEST_HOST_MASK:
		*value = current_evmcs->cr4_guest_host_mask;
		अवरोध;
	हाल CR0_READ_SHADOW:
		*value = current_evmcs->cr0_पढ़ो_shaकरोw;
		अवरोध;
	हाल CR4_READ_SHADOW:
		*value = current_evmcs->cr4_पढ़ो_shaकरोw;
		अवरोध;
	हाल GUEST_CR0:
		*value = current_evmcs->guest_cr0;
		अवरोध;
	हाल GUEST_CR3:
		*value = current_evmcs->guest_cr3;
		अवरोध;
	हाल GUEST_CR4:
		*value = current_evmcs->guest_cr4;
		अवरोध;
	हाल GUEST_DR7:
		*value = current_evmcs->guest_dr7;
		अवरोध;
	हाल HOST_FS_BASE:
		*value = current_evmcs->host_fs_base;
		अवरोध;
	हाल HOST_GS_BASE:
		*value = current_evmcs->host_gs_base;
		अवरोध;
	हाल HOST_TR_BASE:
		*value = current_evmcs->host_tr_base;
		अवरोध;
	हाल HOST_GDTR_BASE:
		*value = current_evmcs->host_gdtr_base;
		अवरोध;
	हाल HOST_IDTR_BASE:
		*value = current_evmcs->host_idtr_base;
		अवरोध;
	हाल HOST_RSP:
		*value = current_evmcs->host_rsp;
		अवरोध;
	हाल EPT_POINTER:
		*value = current_evmcs->ept_poपूर्णांकer;
		अवरोध;
	हाल GUEST_BNDCFGS:
		*value = current_evmcs->guest_bndcfgs;
		अवरोध;
	हाल XSS_EXIT_BITMAP:
		*value = current_evmcs->xss_निकास_biपंचांगap;
		अवरोध;
	हाल GUEST_PHYSICAL_ADDRESS:
		*value = current_evmcs->guest_physical_address;
		अवरोध;
	हाल EXIT_QUALIFICATION:
		*value = current_evmcs->निकास_qualअगरication;
		अवरोध;
	हाल GUEST_LINEAR_ADDRESS:
		*value = current_evmcs->guest_linear_address;
		अवरोध;
	हाल VM_EXIT_MSR_STORE_ADDR:
		*value = current_evmcs->vm_निकास_msr_store_addr;
		अवरोध;
	हाल VM_EXIT_MSR_LOAD_ADDR:
		*value = current_evmcs->vm_निकास_msr_load_addr;
		अवरोध;
	हाल VM_ENTRY_MSR_LOAD_ADDR:
		*value = current_evmcs->vm_entry_msr_load_addr;
		अवरोध;
	हाल CR3_TARGET_VALUE0:
		*value = current_evmcs->cr3_target_value0;
		अवरोध;
	हाल CR3_TARGET_VALUE1:
		*value = current_evmcs->cr3_target_value1;
		अवरोध;
	हाल CR3_TARGET_VALUE2:
		*value = current_evmcs->cr3_target_value2;
		अवरोध;
	हाल CR3_TARGET_VALUE3:
		*value = current_evmcs->cr3_target_value3;
		अवरोध;
	हाल TPR_THRESHOLD:
		*value = current_evmcs->tpr_threshold;
		अवरोध;
	हाल GUEST_INTERRUPTIBILITY_INFO:
		*value = current_evmcs->guest_पूर्णांकerruptibility_info;
		अवरोध;
	हाल CPU_BASED_VM_EXEC_CONTROL:
		*value = current_evmcs->cpu_based_vm_exec_control;
		अवरोध;
	हाल EXCEPTION_BITMAP:
		*value = current_evmcs->exception_biपंचांगap;
		अवरोध;
	हाल VM_ENTRY_CONTROLS:
		*value = current_evmcs->vm_entry_controls;
		अवरोध;
	हाल VM_ENTRY_INTR_INFO_FIELD:
		*value = current_evmcs->vm_entry_पूर्णांकr_info_field;
		अवरोध;
	हाल VM_ENTRY_EXCEPTION_ERROR_CODE:
		*value = current_evmcs->vm_entry_exception_error_code;
		अवरोध;
	हाल VM_ENTRY_INSTRUCTION_LEN:
		*value = current_evmcs->vm_entry_inकाष्ठाion_len;
		अवरोध;
	हाल HOST_IA32_SYSENTER_CS:
		*value = current_evmcs->host_ia32_sysenter_cs;
		अवरोध;
	हाल PIN_BASED_VM_EXEC_CONTROL:
		*value = current_evmcs->pin_based_vm_exec_control;
		अवरोध;
	हाल VM_EXIT_CONTROLS:
		*value = current_evmcs->vm_निकास_controls;
		अवरोध;
	हाल SECONDARY_VM_EXEC_CONTROL:
		*value = current_evmcs->secondary_vm_exec_control;
		अवरोध;
	हाल GUEST_ES_LIMIT:
		*value = current_evmcs->guest_es_limit;
		अवरोध;
	हाल GUEST_CS_LIMIT:
		*value = current_evmcs->guest_cs_limit;
		अवरोध;
	हाल GUEST_SS_LIMIT:
		*value = current_evmcs->guest_ss_limit;
		अवरोध;
	हाल GUEST_DS_LIMIT:
		*value = current_evmcs->guest_ds_limit;
		अवरोध;
	हाल GUEST_FS_LIMIT:
		*value = current_evmcs->guest_fs_limit;
		अवरोध;
	हाल GUEST_GS_LIMIT:
		*value = current_evmcs->guest_gs_limit;
		अवरोध;
	हाल GUEST_LDTR_LIMIT:
		*value = current_evmcs->guest_ldtr_limit;
		अवरोध;
	हाल GUEST_TR_LIMIT:
		*value = current_evmcs->guest_tr_limit;
		अवरोध;
	हाल GUEST_GDTR_LIMIT:
		*value = current_evmcs->guest_gdtr_limit;
		अवरोध;
	हाल GUEST_IDTR_LIMIT:
		*value = current_evmcs->guest_idtr_limit;
		अवरोध;
	हाल GUEST_ES_AR_BYTES:
		*value = current_evmcs->guest_es_ar_bytes;
		अवरोध;
	हाल GUEST_CS_AR_BYTES:
		*value = current_evmcs->guest_cs_ar_bytes;
		अवरोध;
	हाल GUEST_SS_AR_BYTES:
		*value = current_evmcs->guest_ss_ar_bytes;
		अवरोध;
	हाल GUEST_DS_AR_BYTES:
		*value = current_evmcs->guest_ds_ar_bytes;
		अवरोध;
	हाल GUEST_FS_AR_BYTES:
		*value = current_evmcs->guest_fs_ar_bytes;
		अवरोध;
	हाल GUEST_GS_AR_BYTES:
		*value = current_evmcs->guest_gs_ar_bytes;
		अवरोध;
	हाल GUEST_LDTR_AR_BYTES:
		*value = current_evmcs->guest_ldtr_ar_bytes;
		अवरोध;
	हाल GUEST_TR_AR_BYTES:
		*value = current_evmcs->guest_tr_ar_bytes;
		अवरोध;
	हाल GUEST_ACTIVITY_STATE:
		*value = current_evmcs->guest_activity_state;
		अवरोध;
	हाल GUEST_SYSENTER_CS:
		*value = current_evmcs->guest_sysenter_cs;
		अवरोध;
	हाल VM_INSTRUCTION_ERROR:
		*value = current_evmcs->vm_inकाष्ठाion_error;
		अवरोध;
	हाल VM_EXIT_REASON:
		*value = current_evmcs->vm_निकास_reason;
		अवरोध;
	हाल VM_EXIT_INTR_INFO:
		*value = current_evmcs->vm_निकास_पूर्णांकr_info;
		अवरोध;
	हाल VM_EXIT_INTR_ERROR_CODE:
		*value = current_evmcs->vm_निकास_पूर्णांकr_error_code;
		अवरोध;
	हाल IDT_VECTORING_INFO_FIELD:
		*value = current_evmcs->idt_vectoring_info_field;
		अवरोध;
	हाल IDT_VECTORING_ERROR_CODE:
		*value = current_evmcs->idt_vectoring_error_code;
		अवरोध;
	हाल VM_EXIT_INSTRUCTION_LEN:
		*value = current_evmcs->vm_निकास_inकाष्ठाion_len;
		अवरोध;
	हाल VMX_INSTRUCTION_INFO:
		*value = current_evmcs->vmx_inकाष्ठाion_info;
		अवरोध;
	हाल PAGE_FAULT_ERROR_CODE_MASK:
		*value = current_evmcs->page_fault_error_code_mask;
		अवरोध;
	हाल PAGE_FAULT_ERROR_CODE_MATCH:
		*value = current_evmcs->page_fault_error_code_match;
		अवरोध;
	हाल CR3_TARGET_COUNT:
		*value = current_evmcs->cr3_target_count;
		अवरोध;
	हाल VM_EXIT_MSR_STORE_COUNT:
		*value = current_evmcs->vm_निकास_msr_store_count;
		अवरोध;
	हाल VM_EXIT_MSR_LOAD_COUNT:
		*value = current_evmcs->vm_निकास_msr_load_count;
		अवरोध;
	हाल VM_ENTRY_MSR_LOAD_COUNT:
		*value = current_evmcs->vm_entry_msr_load_count;
		अवरोध;
	हाल HOST_ES_SELECTOR:
		*value = current_evmcs->host_es_selector;
		अवरोध;
	हाल HOST_CS_SELECTOR:
		*value = current_evmcs->host_cs_selector;
		अवरोध;
	हाल HOST_SS_SELECTOR:
		*value = current_evmcs->host_ss_selector;
		अवरोध;
	हाल HOST_DS_SELECTOR:
		*value = current_evmcs->host_ds_selector;
		अवरोध;
	हाल HOST_FS_SELECTOR:
		*value = current_evmcs->host_fs_selector;
		अवरोध;
	हाल HOST_GS_SELECTOR:
		*value = current_evmcs->host_gs_selector;
		अवरोध;
	हाल HOST_TR_SELECTOR:
		*value = current_evmcs->host_tr_selector;
		अवरोध;
	हाल GUEST_ES_SELECTOR:
		*value = current_evmcs->guest_es_selector;
		अवरोध;
	हाल GUEST_CS_SELECTOR:
		*value = current_evmcs->guest_cs_selector;
		अवरोध;
	हाल GUEST_SS_SELECTOR:
		*value = current_evmcs->guest_ss_selector;
		अवरोध;
	हाल GUEST_DS_SELECTOR:
		*value = current_evmcs->guest_ds_selector;
		अवरोध;
	हाल GUEST_FS_SELECTOR:
		*value = current_evmcs->guest_fs_selector;
		अवरोध;
	हाल GUEST_GS_SELECTOR:
		*value = current_evmcs->guest_gs_selector;
		अवरोध;
	हाल GUEST_LDTR_SELECTOR:
		*value = current_evmcs->guest_ldtr_selector;
		अवरोध;
	हाल GUEST_TR_SELECTOR:
		*value = current_evmcs->guest_tr_selector;
		अवरोध;
	हाल VIRTUAL_PROCESSOR_ID:
		*value = current_evmcs->भव_processor_id;
		अवरोध;
	शेष: वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक evmcs_vmग_लिखो(uपूर्णांक64_t encoding, uपूर्णांक64_t value)
अणु
	चयन (encoding) अणु
	हाल GUEST_RIP:
		current_evmcs->guest_rip = value;
		अवरोध;
	हाल GUEST_RSP:
		current_evmcs->guest_rsp = value;
		अवरोध;
	हाल GUEST_RFLAGS:
		current_evmcs->guest_rflags = value;
		अवरोध;
	हाल HOST_IA32_PAT:
		current_evmcs->host_ia32_pat = value;
		अवरोध;
	हाल HOST_IA32_EFER:
		current_evmcs->host_ia32_efer = value;
		अवरोध;
	हाल HOST_CR0:
		current_evmcs->host_cr0 = value;
		अवरोध;
	हाल HOST_CR3:
		current_evmcs->host_cr3 = value;
		अवरोध;
	हाल HOST_CR4:
		current_evmcs->host_cr4 = value;
		अवरोध;
	हाल HOST_IA32_SYSENTER_ESP:
		current_evmcs->host_ia32_sysenter_esp = value;
		अवरोध;
	हाल HOST_IA32_SYSENTER_EIP:
		current_evmcs->host_ia32_sysenter_eip = value;
		अवरोध;
	हाल HOST_RIP:
		current_evmcs->host_rip = value;
		अवरोध;
	हाल IO_BITMAP_A:
		current_evmcs->io_biपंचांगap_a = value;
		अवरोध;
	हाल IO_BITMAP_B:
		current_evmcs->io_biपंचांगap_b = value;
		अवरोध;
	हाल MSR_BITMAP:
		current_evmcs->msr_biपंचांगap = value;
		अवरोध;
	हाल GUEST_ES_BASE:
		current_evmcs->guest_es_base = value;
		अवरोध;
	हाल GUEST_CS_BASE:
		current_evmcs->guest_cs_base = value;
		अवरोध;
	हाल GUEST_SS_BASE:
		current_evmcs->guest_ss_base = value;
		अवरोध;
	हाल GUEST_DS_BASE:
		current_evmcs->guest_ds_base = value;
		अवरोध;
	हाल GUEST_FS_BASE:
		current_evmcs->guest_fs_base = value;
		अवरोध;
	हाल GUEST_GS_BASE:
		current_evmcs->guest_gs_base = value;
		अवरोध;
	हाल GUEST_LDTR_BASE:
		current_evmcs->guest_ldtr_base = value;
		अवरोध;
	हाल GUEST_TR_BASE:
		current_evmcs->guest_tr_base = value;
		अवरोध;
	हाल GUEST_GDTR_BASE:
		current_evmcs->guest_gdtr_base = value;
		अवरोध;
	हाल GUEST_IDTR_BASE:
		current_evmcs->guest_idtr_base = value;
		अवरोध;
	हाल TSC_OFFSET:
		current_evmcs->tsc_offset = value;
		अवरोध;
	हाल VIRTUAL_APIC_PAGE_ADDR:
		current_evmcs->भव_apic_page_addr = value;
		अवरोध;
	हाल VMCS_LINK_POINTER:
		current_evmcs->vmcs_link_poपूर्णांकer = value;
		अवरोध;
	हाल GUEST_IA32_DEBUGCTL:
		current_evmcs->guest_ia32_debugctl = value;
		अवरोध;
	हाल GUEST_IA32_PAT:
		current_evmcs->guest_ia32_pat = value;
		अवरोध;
	हाल GUEST_IA32_EFER:
		current_evmcs->guest_ia32_efer = value;
		अवरोध;
	हाल GUEST_PDPTR0:
		current_evmcs->guest_pdptr0 = value;
		अवरोध;
	हाल GUEST_PDPTR1:
		current_evmcs->guest_pdptr1 = value;
		अवरोध;
	हाल GUEST_PDPTR2:
		current_evmcs->guest_pdptr2 = value;
		अवरोध;
	हाल GUEST_PDPTR3:
		current_evmcs->guest_pdptr3 = value;
		अवरोध;
	हाल GUEST_PENDING_DBG_EXCEPTIONS:
		current_evmcs->guest_pending_dbg_exceptions = value;
		अवरोध;
	हाल GUEST_SYSENTER_ESP:
		current_evmcs->guest_sysenter_esp = value;
		अवरोध;
	हाल GUEST_SYSENTER_EIP:
		current_evmcs->guest_sysenter_eip = value;
		अवरोध;
	हाल CR0_GUEST_HOST_MASK:
		current_evmcs->cr0_guest_host_mask = value;
		अवरोध;
	हाल CR4_GUEST_HOST_MASK:
		current_evmcs->cr4_guest_host_mask = value;
		अवरोध;
	हाल CR0_READ_SHADOW:
		current_evmcs->cr0_पढ़ो_shaकरोw = value;
		अवरोध;
	हाल CR4_READ_SHADOW:
		current_evmcs->cr4_पढ़ो_shaकरोw = value;
		अवरोध;
	हाल GUEST_CR0:
		current_evmcs->guest_cr0 = value;
		अवरोध;
	हाल GUEST_CR3:
		current_evmcs->guest_cr3 = value;
		अवरोध;
	हाल GUEST_CR4:
		current_evmcs->guest_cr4 = value;
		अवरोध;
	हाल GUEST_DR7:
		current_evmcs->guest_dr7 = value;
		अवरोध;
	हाल HOST_FS_BASE:
		current_evmcs->host_fs_base = value;
		अवरोध;
	हाल HOST_GS_BASE:
		current_evmcs->host_gs_base = value;
		अवरोध;
	हाल HOST_TR_BASE:
		current_evmcs->host_tr_base = value;
		अवरोध;
	हाल HOST_GDTR_BASE:
		current_evmcs->host_gdtr_base = value;
		अवरोध;
	हाल HOST_IDTR_BASE:
		current_evmcs->host_idtr_base = value;
		अवरोध;
	हाल HOST_RSP:
		current_evmcs->host_rsp = value;
		अवरोध;
	हाल EPT_POINTER:
		current_evmcs->ept_poपूर्णांकer = value;
		अवरोध;
	हाल GUEST_BNDCFGS:
		current_evmcs->guest_bndcfgs = value;
		अवरोध;
	हाल XSS_EXIT_BITMAP:
		current_evmcs->xss_निकास_biपंचांगap = value;
		अवरोध;
	हाल GUEST_PHYSICAL_ADDRESS:
		current_evmcs->guest_physical_address = value;
		अवरोध;
	हाल EXIT_QUALIFICATION:
		current_evmcs->निकास_qualअगरication = value;
		अवरोध;
	हाल GUEST_LINEAR_ADDRESS:
		current_evmcs->guest_linear_address = value;
		अवरोध;
	हाल VM_EXIT_MSR_STORE_ADDR:
		current_evmcs->vm_निकास_msr_store_addr = value;
		अवरोध;
	हाल VM_EXIT_MSR_LOAD_ADDR:
		current_evmcs->vm_निकास_msr_load_addr = value;
		अवरोध;
	हाल VM_ENTRY_MSR_LOAD_ADDR:
		current_evmcs->vm_entry_msr_load_addr = value;
		अवरोध;
	हाल CR3_TARGET_VALUE0:
		current_evmcs->cr3_target_value0 = value;
		अवरोध;
	हाल CR3_TARGET_VALUE1:
		current_evmcs->cr3_target_value1 = value;
		अवरोध;
	हाल CR3_TARGET_VALUE2:
		current_evmcs->cr3_target_value2 = value;
		अवरोध;
	हाल CR3_TARGET_VALUE3:
		current_evmcs->cr3_target_value3 = value;
		अवरोध;
	हाल TPR_THRESHOLD:
		current_evmcs->tpr_threshold = value;
		अवरोध;
	हाल GUEST_INTERRUPTIBILITY_INFO:
		current_evmcs->guest_पूर्णांकerruptibility_info = value;
		अवरोध;
	हाल CPU_BASED_VM_EXEC_CONTROL:
		current_evmcs->cpu_based_vm_exec_control = value;
		अवरोध;
	हाल EXCEPTION_BITMAP:
		current_evmcs->exception_biपंचांगap = value;
		अवरोध;
	हाल VM_ENTRY_CONTROLS:
		current_evmcs->vm_entry_controls = value;
		अवरोध;
	हाल VM_ENTRY_INTR_INFO_FIELD:
		current_evmcs->vm_entry_पूर्णांकr_info_field = value;
		अवरोध;
	हाल VM_ENTRY_EXCEPTION_ERROR_CODE:
		current_evmcs->vm_entry_exception_error_code = value;
		अवरोध;
	हाल VM_ENTRY_INSTRUCTION_LEN:
		current_evmcs->vm_entry_inकाष्ठाion_len = value;
		अवरोध;
	हाल HOST_IA32_SYSENTER_CS:
		current_evmcs->host_ia32_sysenter_cs = value;
		अवरोध;
	हाल PIN_BASED_VM_EXEC_CONTROL:
		current_evmcs->pin_based_vm_exec_control = value;
		अवरोध;
	हाल VM_EXIT_CONTROLS:
		current_evmcs->vm_निकास_controls = value;
		अवरोध;
	हाल SECONDARY_VM_EXEC_CONTROL:
		current_evmcs->secondary_vm_exec_control = value;
		अवरोध;
	हाल GUEST_ES_LIMIT:
		current_evmcs->guest_es_limit = value;
		अवरोध;
	हाल GUEST_CS_LIMIT:
		current_evmcs->guest_cs_limit = value;
		अवरोध;
	हाल GUEST_SS_LIMIT:
		current_evmcs->guest_ss_limit = value;
		अवरोध;
	हाल GUEST_DS_LIMIT:
		current_evmcs->guest_ds_limit = value;
		अवरोध;
	हाल GUEST_FS_LIMIT:
		current_evmcs->guest_fs_limit = value;
		अवरोध;
	हाल GUEST_GS_LIMIT:
		current_evmcs->guest_gs_limit = value;
		अवरोध;
	हाल GUEST_LDTR_LIMIT:
		current_evmcs->guest_ldtr_limit = value;
		अवरोध;
	हाल GUEST_TR_LIMIT:
		current_evmcs->guest_tr_limit = value;
		अवरोध;
	हाल GUEST_GDTR_LIMIT:
		current_evmcs->guest_gdtr_limit = value;
		अवरोध;
	हाल GUEST_IDTR_LIMIT:
		current_evmcs->guest_idtr_limit = value;
		अवरोध;
	हाल GUEST_ES_AR_BYTES:
		current_evmcs->guest_es_ar_bytes = value;
		अवरोध;
	हाल GUEST_CS_AR_BYTES:
		current_evmcs->guest_cs_ar_bytes = value;
		अवरोध;
	हाल GUEST_SS_AR_BYTES:
		current_evmcs->guest_ss_ar_bytes = value;
		अवरोध;
	हाल GUEST_DS_AR_BYTES:
		current_evmcs->guest_ds_ar_bytes = value;
		अवरोध;
	हाल GUEST_FS_AR_BYTES:
		current_evmcs->guest_fs_ar_bytes = value;
		अवरोध;
	हाल GUEST_GS_AR_BYTES:
		current_evmcs->guest_gs_ar_bytes = value;
		अवरोध;
	हाल GUEST_LDTR_AR_BYTES:
		current_evmcs->guest_ldtr_ar_bytes = value;
		अवरोध;
	हाल GUEST_TR_AR_BYTES:
		current_evmcs->guest_tr_ar_bytes = value;
		अवरोध;
	हाल GUEST_ACTIVITY_STATE:
		current_evmcs->guest_activity_state = value;
		अवरोध;
	हाल GUEST_SYSENTER_CS:
		current_evmcs->guest_sysenter_cs = value;
		अवरोध;
	हाल VM_INSTRUCTION_ERROR:
		current_evmcs->vm_inकाष्ठाion_error = value;
		अवरोध;
	हाल VM_EXIT_REASON:
		current_evmcs->vm_निकास_reason = value;
		अवरोध;
	हाल VM_EXIT_INTR_INFO:
		current_evmcs->vm_निकास_पूर्णांकr_info = value;
		अवरोध;
	हाल VM_EXIT_INTR_ERROR_CODE:
		current_evmcs->vm_निकास_पूर्णांकr_error_code = value;
		अवरोध;
	हाल IDT_VECTORING_INFO_FIELD:
		current_evmcs->idt_vectoring_info_field = value;
		अवरोध;
	हाल IDT_VECTORING_ERROR_CODE:
		current_evmcs->idt_vectoring_error_code = value;
		अवरोध;
	हाल VM_EXIT_INSTRUCTION_LEN:
		current_evmcs->vm_निकास_inकाष्ठाion_len = value;
		अवरोध;
	हाल VMX_INSTRUCTION_INFO:
		current_evmcs->vmx_inकाष्ठाion_info = value;
		अवरोध;
	हाल PAGE_FAULT_ERROR_CODE_MASK:
		current_evmcs->page_fault_error_code_mask = value;
		अवरोध;
	हाल PAGE_FAULT_ERROR_CODE_MATCH:
		current_evmcs->page_fault_error_code_match = value;
		अवरोध;
	हाल CR3_TARGET_COUNT:
		current_evmcs->cr3_target_count = value;
		अवरोध;
	हाल VM_EXIT_MSR_STORE_COUNT:
		current_evmcs->vm_निकास_msr_store_count = value;
		अवरोध;
	हाल VM_EXIT_MSR_LOAD_COUNT:
		current_evmcs->vm_निकास_msr_load_count = value;
		अवरोध;
	हाल VM_ENTRY_MSR_LOAD_COUNT:
		current_evmcs->vm_entry_msr_load_count = value;
		अवरोध;
	हाल HOST_ES_SELECTOR:
		current_evmcs->host_es_selector = value;
		अवरोध;
	हाल HOST_CS_SELECTOR:
		current_evmcs->host_cs_selector = value;
		अवरोध;
	हाल HOST_SS_SELECTOR:
		current_evmcs->host_ss_selector = value;
		अवरोध;
	हाल HOST_DS_SELECTOR:
		current_evmcs->host_ds_selector = value;
		अवरोध;
	हाल HOST_FS_SELECTOR:
		current_evmcs->host_fs_selector = value;
		अवरोध;
	हाल HOST_GS_SELECTOR:
		current_evmcs->host_gs_selector = value;
		अवरोध;
	हाल HOST_TR_SELECTOR:
		current_evmcs->host_tr_selector = value;
		अवरोध;
	हाल GUEST_ES_SELECTOR:
		current_evmcs->guest_es_selector = value;
		अवरोध;
	हाल GUEST_CS_SELECTOR:
		current_evmcs->guest_cs_selector = value;
		अवरोध;
	हाल GUEST_SS_SELECTOR:
		current_evmcs->guest_ss_selector = value;
		अवरोध;
	हाल GUEST_DS_SELECTOR:
		current_evmcs->guest_ds_selector = value;
		अवरोध;
	हाल GUEST_FS_SELECTOR:
		current_evmcs->guest_fs_selector = value;
		अवरोध;
	हाल GUEST_GS_SELECTOR:
		current_evmcs->guest_gs_selector = value;
		अवरोध;
	हाल GUEST_LDTR_SELECTOR:
		current_evmcs->guest_ldtr_selector = value;
		अवरोध;
	हाल GUEST_TR_SELECTOR:
		current_evmcs->guest_tr_selector = value;
		अवरोध;
	हाल VIRTUAL_PROCESSOR_ID:
		current_evmcs->भव_processor_id = value;
		अवरोध;
	शेष: वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक evmcs_vmlaunch(व्योम)
अणु
	पूर्णांक ret;

	current_evmcs->hv_clean_fields = 0;

	__यंत्र__ __अस्थिर__("push %%rbp;"
			     "push %%rcx;"
			     "push %%rdx;"
			     "push %%rsi;"
			     "push %%rdi;"
			     "push $0;"
			     "mov %%rsp, (%[host_rsp]);"
			     "lea 1f(%%rip), %%rax;"
			     "mov %%rax, (%[host_rip]);"
			     "vmlaunch;"
			     "incq (%%rsp);"
			     "1: pop %%rax;"
			     "pop %%rdi;"
			     "pop %%rsi;"
			     "pop %%rdx;"
			     "pop %%rcx;"
			     "pop %%rbp;"
			     : [ret]"=&a"(ret)
			     : [host_rsp]"r"
			       ((uपूर्णांक64_t)&current_evmcs->host_rsp),
			       [host_rip]"r"
			       ((uपूर्णांक64_t)&current_evmcs->host_rip)
			     : "memory", "cc", "rbx", "r8", "r9", "r10",
			       "r11", "r12", "r13", "r14", "r15");
	वापस ret;
पूर्ण

/*
 * No guest state (e.g. GPRs) is established by this vmresume.
 */
अटल अंतरभूत पूर्णांक evmcs_vmresume(व्योम)
अणु
	पूर्णांक ret;

	current_evmcs->hv_clean_fields = 0;

	__यंत्र__ __अस्थिर__("push %%rbp;"
			     "push %%rcx;"
			     "push %%rdx;"
			     "push %%rsi;"
			     "push %%rdi;"
			     "push $0;"
			     "mov %%rsp, (%[host_rsp]);"
			     "lea 1f(%%rip), %%rax;"
			     "mov %%rax, (%[host_rip]);"
			     "vmresume;"
			     "incq (%%rsp);"
			     "1: pop %%rax;"
			     "pop %%rdi;"
			     "pop %%rsi;"
			     "pop %%rdx;"
			     "pop %%rcx;"
			     "pop %%rbp;"
			     : [ret]"=&a"(ret)
			     : [host_rsp]"r"
			       ((uपूर्णांक64_t)&current_evmcs->host_rsp),
			       [host_rip]"r"
			       ((uपूर्णांक64_t)&current_evmcs->host_rip)
			     : "memory", "cc", "rbx", "r8", "r9", "r10",
			       "r11", "r12", "r13", "r14", "r15");
	वापस ret;
पूर्ण

#पूर्ण_अगर /* !SELFTEST_KVM_EVMCS_H */
