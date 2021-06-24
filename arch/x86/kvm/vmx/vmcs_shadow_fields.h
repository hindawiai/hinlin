<शैली गुरु>
#अगर !defined(SHADOW_FIELD_RO) && !defined(SHADOW_FIELD_RW)
BUILD_BUG_ON(1)
#पूर्ण_अगर

#अगर_अघोषित SHADOW_FIELD_RO
#घोषणा SHADOW_FIELD_RO(x, y)
#पूर्ण_अगर
#अगर_अघोषित SHADOW_FIELD_RW
#घोषणा SHADOW_FIELD_RW(x, y)
#पूर्ण_अगर

/*
 * We करो NOT shaकरोw fields that are modअगरied when L0
 * traps and emulates any vmx inकाष्ठाion (e.g. VMPTRLD,
 * VMXON...) executed by L1.
 * For example, VM_INSTRUCTION_ERROR is पढ़ो
 * by L1 अगर a vmx inकाष्ठाion fails (part of the error path).
 * Note the code assumes this logic. If क्रम some reason
 * we start shaकरोwing these fields then we need to
 * क्रमce a shaकरोw sync when L0 emulates vmx inकाष्ठाions
 * (e.g. क्रमce a sync अगर VM_INSTRUCTION_ERROR is modअगरied
 * by nested_vmx_failValid)
 *
 * When adding or removing fields here, note that shaकरोwed
 * fields must always be synced by prepare_vmcs02, not just
 * prepare_vmcs02_rare.
 */

/*
 * Keeping the fields ordered by size is an attempt at improving
 * branch prediction in vmcs12_पढ़ो_any and vmcs12_ग_लिखो_any.
 */

/* 16-bits */
SHADOW_FIELD_RW(GUEST_INTR_STATUS, guest_पूर्णांकr_status)
SHADOW_FIELD_RW(GUEST_PML_INDEX, guest_pml_index)
SHADOW_FIELD_RW(HOST_FS_SELECTOR, host_fs_selector)
SHADOW_FIELD_RW(HOST_GS_SELECTOR, host_gs_selector)

/* 32-bits */
SHADOW_FIELD_RO(VM_EXIT_REASON, vm_निकास_reason)
SHADOW_FIELD_RO(VM_EXIT_INTR_INFO, vm_निकास_पूर्णांकr_info)
SHADOW_FIELD_RO(VM_EXIT_INSTRUCTION_LEN, vm_निकास_inकाष्ठाion_len)
SHADOW_FIELD_RO(IDT_VECTORING_INFO_FIELD, idt_vectoring_info_field)
SHADOW_FIELD_RO(IDT_VECTORING_ERROR_CODE, idt_vectoring_error_code)
SHADOW_FIELD_RO(VM_EXIT_INTR_ERROR_CODE, vm_निकास_पूर्णांकr_error_code)
SHADOW_FIELD_RO(GUEST_CS_AR_BYTES, guest_cs_ar_bytes)
SHADOW_FIELD_RO(GUEST_SS_AR_BYTES, guest_ss_ar_bytes)
SHADOW_FIELD_RW(CPU_BASED_VM_EXEC_CONTROL, cpu_based_vm_exec_control)
SHADOW_FIELD_RW(PIN_BASED_VM_EXEC_CONTROL, pin_based_vm_exec_control)
SHADOW_FIELD_RW(EXCEPTION_BITMAP, exception_biपंचांगap)
SHADOW_FIELD_RW(VM_ENTRY_EXCEPTION_ERROR_CODE, vm_entry_exception_error_code)
SHADOW_FIELD_RW(VM_ENTRY_INTR_INFO_FIELD, vm_entry_पूर्णांकr_info_field)
SHADOW_FIELD_RW(VM_ENTRY_INSTRUCTION_LEN, vm_entry_inकाष्ठाion_len)
SHADOW_FIELD_RW(TPR_THRESHOLD, tpr_threshold)
SHADOW_FIELD_RW(GUEST_INTERRUPTIBILITY_INFO, guest_पूर्णांकerruptibility_info)
SHADOW_FIELD_RW(VMX_PREEMPTION_TIMER_VALUE, vmx_preemption_समयr_value)

/* Natural width */
SHADOW_FIELD_RO(EXIT_QUALIFICATION, निकास_qualअगरication)
SHADOW_FIELD_RO(GUEST_LINEAR_ADDRESS, guest_linear_address)
SHADOW_FIELD_RW(GUEST_RIP, guest_rip)
SHADOW_FIELD_RW(GUEST_RSP, guest_rsp)
SHADOW_FIELD_RW(GUEST_CR0, guest_cr0)
SHADOW_FIELD_RW(GUEST_CR3, guest_cr3)
SHADOW_FIELD_RW(GUEST_CR4, guest_cr4)
SHADOW_FIELD_RW(GUEST_RFLAGS, guest_rflags)
SHADOW_FIELD_RW(CR0_GUEST_HOST_MASK, cr0_guest_host_mask)
SHADOW_FIELD_RW(CR0_READ_SHADOW, cr0_पढ़ो_shaकरोw)
SHADOW_FIELD_RW(CR4_READ_SHADOW, cr4_पढ़ो_shaकरोw)
SHADOW_FIELD_RW(HOST_FS_BASE, host_fs_base)
SHADOW_FIELD_RW(HOST_GS_BASE, host_gs_base)

/* 64-bit */
SHADOW_FIELD_RO(GUEST_PHYSICAL_ADDRESS, guest_physical_address)
SHADOW_FIELD_RO(GUEST_PHYSICAL_ADDRESS_HIGH, guest_physical_address)

#अघोषित SHADOW_FIELD_RO
#अघोषित SHADOW_FIELD_RW
