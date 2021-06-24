<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tools/testing/selftests/kvm/lib/x86_64/vmx.c
 *
 * Copyright (C) 2018, Google LLC.
 */

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "../kvm_util_internal.h"
#समावेश "processor.h"
#समावेश "vmx.h"

#घोषणा PAGE_SHIFT_4K  12

#घोषणा KVM_EPT_PAGE_TABLE_MIN_PADDR 0x1c0000

bool enable_evmcs;

काष्ठा hv_enlightened_vmcs *current_evmcs;
काष्ठा hv_vp_assist_page *current_vp_assist;

काष्ठा eptPageTableEntry अणु
	uपूर्णांक64_t पढ़ोable:1;
	uपूर्णांक64_t writable:1;
	uपूर्णांक64_t executable:1;
	uपूर्णांक64_t memory_type:3;
	uपूर्णांक64_t ignore_pat:1;
	uपूर्णांक64_t page_size:1;
	uपूर्णांक64_t accessed:1;
	uपूर्णांक64_t dirty:1;
	uपूर्णांक64_t ignored_11_10:2;
	uपूर्णांक64_t address:40;
	uपूर्णांक64_t ignored_62_52:11;
	uपूर्णांक64_t suppress_ve:1;
पूर्ण;

काष्ठा eptPageTablePoपूर्णांकer अणु
	uपूर्णांक64_t memory_type:3;
	uपूर्णांक64_t page_walk_length:3;
	uपूर्णांक64_t ad_enabled:1;
	uपूर्णांक64_t reserved_11_07:5;
	uपूर्णांक64_t address:40;
	uपूर्णांक64_t reserved_63_52:12;
पूर्ण;
पूर्णांक vcpu_enable_evmcs(काष्ठा kvm_vm *vm, पूर्णांक vcpu_id)
अणु
	uपूर्णांक16_t evmcs_ver;

	काष्ठा kvm_enable_cap enable_evmcs_cap = अणु
		.cap = KVM_CAP_HYPERV_ENLIGHTENED_VMCS,
		 .args[0] = (अचिन्हित दीर्घ)&evmcs_ver
	पूर्ण;

	vcpu_ioctl(vm, vcpu_id, KVM_ENABLE_CAP, &enable_evmcs_cap);

	/* KVM should वापस supported EVMCS version range */
	TEST_ASSERT(((evmcs_ver >> 8) >= (evmcs_ver & 0xff)) &&
		    (evmcs_ver & 0xff) > 0,
		    "Incorrect EVMCS version range: %x:%x\n",
		    evmcs_ver & 0xff, evmcs_ver >> 8);

	वापस evmcs_ver;
पूर्ण

/* Allocate memory regions क्रम nested VMX tests.
 *
 * Input Args:
 *   vm - The VM to allocate guest-भव addresses in.
 *
 * Output Args:
 *   p_vmx_gva - The guest भव address क्रम the काष्ठा vmx_pages.
 *
 * Return:
 *   Poपूर्णांकer to काष्ठाure with the addresses of the VMX areas.
 */
काष्ठा vmx_pages *
vcpu_alloc_vmx(काष्ठा kvm_vm *vm, vm_vaddr_t *p_vmx_gva)
अणु
	vm_vaddr_t vmx_gva = vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	काष्ठा vmx_pages *vmx = addr_gva2hva(vm, vmx_gva);

	/* Setup of a region of guest memory क्रम the vmxon region. */
	vmx->vmxon = (व्योम *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->vmxon_hva = addr_gva2hva(vm, (uपूर्णांकptr_t)vmx->vmxon);
	vmx->vmxon_gpa = addr_gva2gpa(vm, (uपूर्णांकptr_t)vmx->vmxon);

	/* Setup of a region of guest memory क्रम a vmcs. */
	vmx->vmcs = (व्योम *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->vmcs_hva = addr_gva2hva(vm, (uपूर्णांकptr_t)vmx->vmcs);
	vmx->vmcs_gpa = addr_gva2gpa(vm, (uपूर्णांकptr_t)vmx->vmcs);

	/* Setup of a region of guest memory क्रम the MSR biपंचांगap. */
	vmx->msr = (व्योम *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->msr_hva = addr_gva2hva(vm, (uपूर्णांकptr_t)vmx->msr);
	vmx->msr_gpa = addr_gva2gpa(vm, (uपूर्णांकptr_t)vmx->msr);
	स_रखो(vmx->msr_hva, 0, getpagesize());

	/* Setup of a region of guest memory क्रम the shaकरोw VMCS. */
	vmx->shaकरोw_vmcs = (व्योम *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->shaकरोw_vmcs_hva = addr_gva2hva(vm, (uपूर्णांकptr_t)vmx->shaकरोw_vmcs);
	vmx->shaकरोw_vmcs_gpa = addr_gva2gpa(vm, (uपूर्णांकptr_t)vmx->shaकरोw_vmcs);

	/* Setup of a region of guest memory क्रम the VMREAD and VMWRITE biपंचांगaps. */
	vmx->vmपढ़ो = (व्योम *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->vmपढ़ो_hva = addr_gva2hva(vm, (uपूर्णांकptr_t)vmx->vmपढ़ो);
	vmx->vmपढ़ो_gpa = addr_gva2gpa(vm, (uपूर्णांकptr_t)vmx->vmपढ़ो);
	स_रखो(vmx->vmपढ़ो_hva, 0, getpagesize());

	vmx->vmग_लिखो = (व्योम *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->vmग_लिखो_hva = addr_gva2hva(vm, (uपूर्णांकptr_t)vmx->vmग_लिखो);
	vmx->vmग_लिखो_gpa = addr_gva2gpa(vm, (uपूर्णांकptr_t)vmx->vmग_लिखो);
	स_रखो(vmx->vmग_लिखो_hva, 0, getpagesize());

	/* Setup of a region of guest memory क्रम the VP Assist page. */
	vmx->vp_assist = (व्योम *)vm_vaddr_alloc(vm, getpagesize(),
						0x10000, 0, 0);
	vmx->vp_assist_hva = addr_gva2hva(vm, (uपूर्णांकptr_t)vmx->vp_assist);
	vmx->vp_assist_gpa = addr_gva2gpa(vm, (uपूर्णांकptr_t)vmx->vp_assist);

	/* Setup of a region of guest memory क्रम the enlightened VMCS. */
	vmx->enlightened_vmcs = (व्योम *)vm_vaddr_alloc(vm, getpagesize(),
						       0x10000, 0, 0);
	vmx->enlightened_vmcs_hva =
		addr_gva2hva(vm, (uपूर्णांकptr_t)vmx->enlightened_vmcs);
	vmx->enlightened_vmcs_gpa =
		addr_gva2gpa(vm, (uपूर्णांकptr_t)vmx->enlightened_vmcs);

	*p_vmx_gva = vmx_gva;
	वापस vmx;
पूर्ण

bool prepare_क्रम_vmx_operation(काष्ठा vmx_pages *vmx)
अणु
	uपूर्णांक64_t feature_control;
	uपूर्णांक64_t required;
	अचिन्हित दीर्घ cr0;
	अचिन्हित दीर्घ cr4;

	/*
	 * Ensure bits in CR0 and CR4 are valid in VMX operation:
	 * - Bit X is 1 in _FIXED0: bit X is fixed to 1 in CRx.
	 * - Bit X is 0 in _FIXED1: bit X is fixed to 0 in CRx.
	 */
	__यंत्र__ __अस्थिर__("mov %%cr0, %0" : "=r"(cr0) : : "memory");
	cr0 &= rdmsr(MSR_IA32_VMX_CR0_FIXED1);
	cr0 |= rdmsr(MSR_IA32_VMX_CR0_FIXED0);
	__यंत्र__ __अस्थिर__("mov %0, %%cr0" : : "r"(cr0) : "memory");

	__यंत्र__ __अस्थिर__("mov %%cr4, %0" : "=r"(cr4) : : "memory");
	cr4 &= rdmsr(MSR_IA32_VMX_CR4_FIXED1);
	cr4 |= rdmsr(MSR_IA32_VMX_CR4_FIXED0);
	/* Enable VMX operation */
	cr4 |= X86_CR4_VMXE;
	__यंत्र__ __अस्थिर__("mov %0, %%cr4" : : "r"(cr4) : "memory");

	/*
	 * Configure IA32_FEATURE_CONTROL MSR to allow VMXON:
	 *  Bit 0: Lock bit. If clear, VMXON causes a #GP.
	 *  Bit 2: Enables VMXON outside of SMX operation. If clear, VMXON
	 *    outside of SMX causes a #GP.
	 */
	required = FEAT_CTL_VMX_ENABLED_OUTSIDE_SMX;
	required |= FEAT_CTL_LOCKED;
	feature_control = rdmsr(MSR_IA32_FEAT_CTL);
	अगर ((feature_control & required) != required)
		wrmsr(MSR_IA32_FEAT_CTL, feature_control | required);

	/* Enter VMX root operation. */
	*(uपूर्णांक32_t *)(vmx->vmxon) = vmcs_revision();
	अगर (vmxon(vmx->vmxon_gpa))
		वापस false;

	वापस true;
पूर्ण

bool load_vmcs(काष्ठा vmx_pages *vmx)
अणु
	अगर (!enable_evmcs) अणु
		/* Load a VMCS. */
		*(uपूर्णांक32_t *)(vmx->vmcs) = vmcs_revision();
		अगर (vmclear(vmx->vmcs_gpa))
			वापस false;

		अगर (vmptrld(vmx->vmcs_gpa))
			वापस false;

		/* Setup shaकरोw VMCS, करो not load it yet. */
		*(uपूर्णांक32_t *)(vmx->shaकरोw_vmcs) =
			vmcs_revision() | 0x80000000ul;
		अगर (vmclear(vmx->shaकरोw_vmcs_gpa))
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (evmcs_vmptrld(vmx->enlightened_vmcs_gpa,
				  vmx->enlightened_vmcs))
			वापस false;
		current_evmcs->revision_id = EVMCS_VERSION;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Initialize the control fields to the most basic settings possible.
 */
अटल अंतरभूत व्योम init_vmcs_control_fields(काष्ठा vmx_pages *vmx)
अणु
	uपूर्णांक32_t sec_exec_ctl = 0;

	vmग_लिखो(VIRTUAL_PROCESSOR_ID, 0);
	vmग_लिखो(POSTED_INTR_NV, 0);

	vmग_लिखो(PIN_BASED_VM_EXEC_CONTROL, rdmsr(MSR_IA32_VMX_TRUE_PINBASED_CTLS));

	अगर (vmx->eptp_gpa) अणु
		uपूर्णांक64_t ept_paddr;
		काष्ठा eptPageTablePoपूर्णांकer eptp = अणु
			.memory_type = VMX_BASIC_MEM_TYPE_WB,
			.page_walk_length = 3, /* + 1 */
			.ad_enabled = !!(rdmsr(MSR_IA32_VMX_EPT_VPID_CAP) & VMX_EPT_VPID_CAP_AD_BITS),
			.address = vmx->eptp_gpa >> PAGE_SHIFT_4K,
		पूर्ण;

		स_नकल(&ept_paddr, &eptp, माप(ept_paddr));
		vmग_लिखो(EPT_POINTER, ept_paddr);
		sec_exec_ctl |= SECONDARY_EXEC_ENABLE_EPT;
	पूर्ण

	अगर (!vmग_लिखो(SECONDARY_VM_EXEC_CONTROL, sec_exec_ctl))
		vmग_लिखो(CPU_BASED_VM_EXEC_CONTROL,
			rdmsr(MSR_IA32_VMX_TRUE_PROCBASED_CTLS) | CPU_BASED_ACTIVATE_SECONDARY_CONTROLS);
	अन्यथा अणु
		vmग_लिखो(CPU_BASED_VM_EXEC_CONTROL, rdmsr(MSR_IA32_VMX_TRUE_PROCBASED_CTLS));
		GUEST_ASSERT(!sec_exec_ctl);
	पूर्ण

	vmग_लिखो(EXCEPTION_BITMAP, 0);
	vmग_लिखो(PAGE_FAULT_ERROR_CODE_MASK, 0);
	vmग_लिखो(PAGE_FAULT_ERROR_CODE_MATCH, -1); /* Never match */
	vmग_लिखो(CR3_TARGET_COUNT, 0);
	vmग_लिखो(VM_EXIT_CONTROLS, rdmsr(MSR_IA32_VMX_EXIT_CTLS) |
		VM_EXIT_HOST_ADDR_SPACE_SIZE);	  /* 64-bit host */
	vmग_लिखो(VM_EXIT_MSR_STORE_COUNT, 0);
	vmग_लिखो(VM_EXIT_MSR_LOAD_COUNT, 0);
	vmग_लिखो(VM_ENTRY_CONTROLS, rdmsr(MSR_IA32_VMX_ENTRY_CTLS) |
		VM_ENTRY_IA32E_MODE);		  /* 64-bit guest */
	vmग_लिखो(VM_ENTRY_MSR_LOAD_COUNT, 0);
	vmग_लिखो(VM_ENTRY_INTR_INFO_FIELD, 0);
	vmग_लिखो(TPR_THRESHOLD, 0);

	vmग_लिखो(CR0_GUEST_HOST_MASK, 0);
	vmग_लिखो(CR4_GUEST_HOST_MASK, 0);
	vmग_लिखो(CR0_READ_SHADOW, get_cr0());
	vmग_लिखो(CR4_READ_SHADOW, get_cr4());

	vmग_लिखो(MSR_BITMAP, vmx->msr_gpa);
	vmग_लिखो(VMREAD_BITMAP, vmx->vmपढ़ो_gpa);
	vmग_लिखो(VMWRITE_BITMAP, vmx->vmग_लिखो_gpa);
पूर्ण

/*
 * Initialize the host state fields based on the current host state, with
 * the exception of HOST_RSP and HOST_RIP, which should be set by vmlaunch
 * or vmresume.
 */
अटल अंतरभूत व्योम init_vmcs_host_state(व्योम)
अणु
	uपूर्णांक32_t निकास_controls = vmपढ़ोz(VM_EXIT_CONTROLS);

	vmग_लिखो(HOST_ES_SELECTOR, get_es());
	vmग_लिखो(HOST_CS_SELECTOR, get_cs());
	vmग_लिखो(HOST_SS_SELECTOR, get_ss());
	vmग_लिखो(HOST_DS_SELECTOR, get_ds());
	vmग_लिखो(HOST_FS_SELECTOR, get_fs());
	vmग_लिखो(HOST_GS_SELECTOR, get_gs());
	vmग_लिखो(HOST_TR_SELECTOR, get_tr());

	अगर (निकास_controls & VM_EXIT_LOAD_IA32_PAT)
		vmग_लिखो(HOST_IA32_PAT, rdmsr(MSR_IA32_CR_PAT));
	अगर (निकास_controls & VM_EXIT_LOAD_IA32_EFER)
		vmग_लिखो(HOST_IA32_EFER, rdmsr(MSR_EFER));
	अगर (निकास_controls & VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL)
		vmग_लिखो(HOST_IA32_PERF_GLOBAL_CTRL,
			rdmsr(MSR_CORE_PERF_GLOBAL_CTRL));

	vmग_लिखो(HOST_IA32_SYSENTER_CS, rdmsr(MSR_IA32_SYSENTER_CS));

	vmग_लिखो(HOST_CR0, get_cr0());
	vmग_लिखो(HOST_CR3, get_cr3());
	vmग_लिखो(HOST_CR4, get_cr4());
	vmग_लिखो(HOST_FS_BASE, rdmsr(MSR_FS_BASE));
	vmग_लिखो(HOST_GS_BASE, rdmsr(MSR_GS_BASE));
	vmग_लिखो(HOST_TR_BASE,
		get_desc64_base((काष्ठा desc64 *)(get_gdt().address + get_tr())));
	vmग_लिखो(HOST_GDTR_BASE, get_gdt().address);
	vmग_लिखो(HOST_IDTR_BASE, get_idt().address);
	vmग_लिखो(HOST_IA32_SYSENTER_ESP, rdmsr(MSR_IA32_SYSENTER_ESP));
	vmग_लिखो(HOST_IA32_SYSENTER_EIP, rdmsr(MSR_IA32_SYSENTER_EIP));
पूर्ण

/*
 * Initialize the guest state fields essentially as a clone of
 * the host state fields. Some host state fields have fixed
 * values, and we set the corresponding guest state fields accordingly.
 */
अटल अंतरभूत व्योम init_vmcs_guest_state(व्योम *rip, व्योम *rsp)
अणु
	vmग_लिखो(GUEST_ES_SELECTOR, vmपढ़ोz(HOST_ES_SELECTOR));
	vmग_लिखो(GUEST_CS_SELECTOR, vmपढ़ोz(HOST_CS_SELECTOR));
	vmग_लिखो(GUEST_SS_SELECTOR, vmपढ़ोz(HOST_SS_SELECTOR));
	vmग_लिखो(GUEST_DS_SELECTOR, vmपढ़ोz(HOST_DS_SELECTOR));
	vmग_लिखो(GUEST_FS_SELECTOR, vmपढ़ोz(HOST_FS_SELECTOR));
	vmग_लिखो(GUEST_GS_SELECTOR, vmपढ़ोz(HOST_GS_SELECTOR));
	vmग_लिखो(GUEST_LDTR_SELECTOR, 0);
	vmग_लिखो(GUEST_TR_SELECTOR, vmपढ़ोz(HOST_TR_SELECTOR));
	vmग_लिखो(GUEST_INTR_STATUS, 0);
	vmग_लिखो(GUEST_PML_INDEX, 0);

	vmग_लिखो(VMCS_LINK_POINTER, -1ll);
	vmग_लिखो(GUEST_IA32_DEBUGCTL, 0);
	vmग_लिखो(GUEST_IA32_PAT, vmपढ़ोz(HOST_IA32_PAT));
	vmग_लिखो(GUEST_IA32_EFER, vmपढ़ोz(HOST_IA32_EFER));
	vmग_लिखो(GUEST_IA32_PERF_GLOBAL_CTRL,
		vmपढ़ोz(HOST_IA32_PERF_GLOBAL_CTRL));

	vmग_लिखो(GUEST_ES_LIMIT, -1);
	vmग_लिखो(GUEST_CS_LIMIT, -1);
	vmग_लिखो(GUEST_SS_LIMIT, -1);
	vmग_लिखो(GUEST_DS_LIMIT, -1);
	vmग_लिखो(GUEST_FS_LIMIT, -1);
	vmग_लिखो(GUEST_GS_LIMIT, -1);
	vmग_लिखो(GUEST_LDTR_LIMIT, -1);
	vmग_लिखो(GUEST_TR_LIMIT, 0x67);
	vmग_लिखो(GUEST_GDTR_LIMIT, 0xffff);
	vmग_लिखो(GUEST_IDTR_LIMIT, 0xffff);
	vmग_लिखो(GUEST_ES_AR_BYTES,
		vmपढ़ोz(GUEST_ES_SELECTOR) == 0 ? 0x10000 : 0xc093);
	vmग_लिखो(GUEST_CS_AR_BYTES, 0xa09b);
	vmग_लिखो(GUEST_SS_AR_BYTES, 0xc093);
	vmग_लिखो(GUEST_DS_AR_BYTES,
		vmपढ़ोz(GUEST_DS_SELECTOR) == 0 ? 0x10000 : 0xc093);
	vmग_लिखो(GUEST_FS_AR_BYTES,
		vmपढ़ोz(GUEST_FS_SELECTOR) == 0 ? 0x10000 : 0xc093);
	vmग_लिखो(GUEST_GS_AR_BYTES,
		vmपढ़ोz(GUEST_GS_SELECTOR) == 0 ? 0x10000 : 0xc093);
	vmग_लिखो(GUEST_LDTR_AR_BYTES, 0x10000);
	vmग_लिखो(GUEST_TR_AR_BYTES, 0x8b);
	vmग_लिखो(GUEST_INTERRUPTIBILITY_INFO, 0);
	vmग_लिखो(GUEST_ACTIVITY_STATE, 0);
	vmग_लिखो(GUEST_SYSENTER_CS, vmपढ़ोz(HOST_IA32_SYSENTER_CS));
	vmग_लिखो(VMX_PREEMPTION_TIMER_VALUE, 0);

	vmग_लिखो(GUEST_CR0, vmपढ़ोz(HOST_CR0));
	vmग_लिखो(GUEST_CR3, vmपढ़ोz(HOST_CR3));
	vmग_लिखो(GUEST_CR4, vmपढ़ोz(HOST_CR4));
	vmग_लिखो(GUEST_ES_BASE, 0);
	vmग_लिखो(GUEST_CS_BASE, 0);
	vmग_लिखो(GUEST_SS_BASE, 0);
	vmग_लिखो(GUEST_DS_BASE, 0);
	vmग_लिखो(GUEST_FS_BASE, vmपढ़ोz(HOST_FS_BASE));
	vmग_लिखो(GUEST_GS_BASE, vmपढ़ोz(HOST_GS_BASE));
	vmग_लिखो(GUEST_LDTR_BASE, 0);
	vmग_लिखो(GUEST_TR_BASE, vmपढ़ोz(HOST_TR_BASE));
	vmग_लिखो(GUEST_GDTR_BASE, vmपढ़ोz(HOST_GDTR_BASE));
	vmग_लिखो(GUEST_IDTR_BASE, vmपढ़ोz(HOST_IDTR_BASE));
	vmग_लिखो(GUEST_DR7, 0x400);
	vmग_लिखो(GUEST_RSP, (uपूर्णांक64_t)rsp);
	vmग_लिखो(GUEST_RIP, (uपूर्णांक64_t)rip);
	vmग_लिखो(GUEST_RFLAGS, 2);
	vmग_लिखो(GUEST_PENDING_DBG_EXCEPTIONS, 0);
	vmग_लिखो(GUEST_SYSENTER_ESP, vmपढ़ोz(HOST_IA32_SYSENTER_ESP));
	vmग_लिखो(GUEST_SYSENTER_EIP, vmपढ़ोz(HOST_IA32_SYSENTER_EIP));
पूर्ण

व्योम prepare_vmcs(काष्ठा vmx_pages *vmx, व्योम *guest_rip, व्योम *guest_rsp)
अणु
	init_vmcs_control_fields(vmx);
	init_vmcs_host_state();
	init_vmcs_guest_state(guest_rip, guest_rsp);
पूर्ण

bool nested_vmx_supported(व्योम)
अणु
	काष्ठा kvm_cpuid_entry2 *entry = kvm_get_supported_cpuid_entry(1);

	वापस entry->ecx & CPUID_VMX;
पूर्ण

व्योम nested_vmx_check_supported(व्योम)
अणु
	अगर (!nested_vmx_supported()) अणु
		prपूर्णांक_skip("nested VMX not enabled");
		निकास(KSFT_SKIP);
	पूर्ण
पूर्ण

व्योम nested_pg_map(काष्ठा vmx_pages *vmx, काष्ठा kvm_vm *vm,
	 	   uपूर्णांक64_t nested_paddr, uपूर्णांक64_t paddr, uपूर्णांक32_t eptp_memslot)
अणु
	uपूर्णांक16_t index[4];
	काष्ठा eptPageTableEntry *pml4e;

	TEST_ASSERT(vm->mode == VM_MODE_PXXV48_4K, "Attempt to use "
		    "unknown or unsupported guest mode, mode: 0x%x", vm->mode);

	TEST_ASSERT((nested_paddr % vm->page_size) == 0,
		    "Nested physical address not on page boundary,\n"
		    "  nested_paddr: 0x%lx vm->page_size: 0x%x",
		    nested_paddr, vm->page_size);
	TEST_ASSERT((nested_paddr >> vm->page_shअगरt) <= vm->max_gfn,
		    "Physical address beyond beyond maximum supported,\n"
		    "  nested_paddr: 0x%lx vm->max_gfn: 0x%lx vm->page_size: 0x%x",
		    paddr, vm->max_gfn, vm->page_size);
	TEST_ASSERT((paddr % vm->page_size) == 0,
		    "Physical address not on page boundary,\n"
		    "  paddr: 0x%lx vm->page_size: 0x%x",
		    paddr, vm->page_size);
	TEST_ASSERT((paddr >> vm->page_shअगरt) <= vm->max_gfn,
		    "Physical address beyond beyond maximum supported,\n"
		    "  paddr: 0x%lx vm->max_gfn: 0x%lx vm->page_size: 0x%x",
		    paddr, vm->max_gfn, vm->page_size);

	index[0] = (nested_paddr >> 12) & 0x1ffu;
	index[1] = (nested_paddr >> 21) & 0x1ffu;
	index[2] = (nested_paddr >> 30) & 0x1ffu;
	index[3] = (nested_paddr >> 39) & 0x1ffu;

	/* Allocate page directory poपूर्णांकer table अगर not present. */
	pml4e = vmx->eptp_hva;
	अगर (!pml4e[index[3]].पढ़ोable) अणु
		pml4e[index[3]].address = vm_phy_page_alloc(vm,
			  KVM_EPT_PAGE_TABLE_MIN_PADDR, eptp_memslot)
			>> vm->page_shअगरt;
		pml4e[index[3]].writable = true;
		pml4e[index[3]].पढ़ोable = true;
		pml4e[index[3]].executable = true;
	पूर्ण

	/* Allocate page directory table अगर not present. */
	काष्ठा eptPageTableEntry *pdpe;
	pdpe = addr_gpa2hva(vm, pml4e[index[3]].address * vm->page_size);
	अगर (!pdpe[index[2]].पढ़ोable) अणु
		pdpe[index[2]].address = vm_phy_page_alloc(vm,
			  KVM_EPT_PAGE_TABLE_MIN_PADDR, eptp_memslot)
			>> vm->page_shअगरt;
		pdpe[index[2]].writable = true;
		pdpe[index[2]].पढ़ोable = true;
		pdpe[index[2]].executable = true;
	पूर्ण

	/* Allocate page table अगर not present. */
	काष्ठा eptPageTableEntry *pde;
	pde = addr_gpa2hva(vm, pdpe[index[2]].address * vm->page_size);
	अगर (!pde[index[1]].पढ़ोable) अणु
		pde[index[1]].address = vm_phy_page_alloc(vm,
			  KVM_EPT_PAGE_TABLE_MIN_PADDR, eptp_memslot)
			>> vm->page_shअगरt;
		pde[index[1]].writable = true;
		pde[index[1]].पढ़ोable = true;
		pde[index[1]].executable = true;
	पूर्ण

	/* Fill in page table entry. */
	काष्ठा eptPageTableEntry *pte;
	pte = addr_gpa2hva(vm, pde[index[1]].address * vm->page_size);
	pte[index[0]].address = paddr >> vm->page_shअगरt;
	pte[index[0]].writable = true;
	pte[index[0]].पढ़ोable = true;
	pte[index[0]].executable = true;

	/*
	 * For now mark these as accessed and dirty because the only
	 * testहाल we have needs that.  Can be reconsidered later.
	 */
	pte[index[0]].accessed = true;
	pte[index[0]].dirty = true;
पूर्ण

/*
 * Map a range of EPT guest physical addresses to the VM's physical address
 *
 * Input Args:
 *   vm - Virtual Machine
 *   nested_paddr - Nested guest physical address to map
 *   paddr - VM Physical Address
 *   size - The size of the range to map
 *   eptp_memslot - Memory region slot क्रम new भव translation tables
 *
 * Output Args: None
 *
 * Return: None
 *
 * Within the VM given by vm, creates a nested guest translation क्रम the
 * page range starting at nested_paddr to the page range starting at paddr.
 */
व्योम nested_map(काष्ठा vmx_pages *vmx, काष्ठा kvm_vm *vm,
		uपूर्णांक64_t nested_paddr, uपूर्णांक64_t paddr, uपूर्णांक64_t size,
		uपूर्णांक32_t eptp_memslot)
अणु
	माप_प्रकार page_size = vm->page_size;
	माप_प्रकार npages = size / page_size;

	TEST_ASSERT(nested_paddr + size > nested_paddr, "Vaddr overflow");
	TEST_ASSERT(paddr + size > paddr, "Paddr overflow");

	जबतक (npages--) अणु
		nested_pg_map(vmx, vm, nested_paddr, paddr, eptp_memslot);
		nested_paddr += page_size;
		paddr += page_size;
	पूर्ण
पूर्ण

/* Prepare an identity extended page table that maps all the
 * physical pages in VM.
 */
व्योम nested_map_memslot(काष्ठा vmx_pages *vmx, काष्ठा kvm_vm *vm,
			uपूर्णांक32_t memslot, uपूर्णांक32_t eptp_memslot)
अणु
	sparsebit_idx_t i, last;
	काष्ठा userspace_mem_region *region =
		memslot2region(vm, memslot);

	i = (region->region.guest_phys_addr >> vm->page_shअगरt) - 1;
	last = i + (region->region.memory_size >> vm->page_shअगरt);
	क्रम (;;) अणु
		i = sparsebit_next_clear(region->unused_phy_pages, i);
		अगर (i > last)
			अवरोध;

		nested_map(vmx, vm,
			   (uपूर्णांक64_t)i << vm->page_shअगरt,
			   (uपूर्णांक64_t)i << vm->page_shअगरt,
			   1 << vm->page_shअगरt,
			   eptp_memslot);
	पूर्ण
पूर्ण

व्योम prepare_eptp(काष्ठा vmx_pages *vmx, काष्ठा kvm_vm *vm,
		  uपूर्णांक32_t eptp_memslot)
अणु
	vmx->eptp = (व्योम *)vm_vaddr_alloc(vm, getpagesize(), 0x10000, 0, 0);
	vmx->eptp_hva = addr_gva2hva(vm, (uपूर्णांकptr_t)vmx->eptp);
	vmx->eptp_gpa = addr_gva2gpa(vm, (uपूर्णांकptr_t)vmx->eptp);
पूर्ण

व्योम prepare_भवize_apic_accesses(काष्ठा vmx_pages *vmx, काष्ठा kvm_vm *vm,
				      uपूर्णांक32_t eptp_memslot)
अणु
	vmx->apic_access = (व्योम *)vm_vaddr_alloc(vm, getpagesize(),
						  0x10000, 0, 0);
	vmx->apic_access_hva = addr_gva2hva(vm, (uपूर्णांकptr_t)vmx->apic_access);
	vmx->apic_access_gpa = addr_gva2gpa(vm, (uपूर्णांकptr_t)vmx->apic_access);
पूर्ण
