<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/objtool.h>
#समावेश <linux/percpu.h>

#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/mmu_context.h>

#समावेश "cpuid.h"
#समावेश "hyperv.h"
#समावेश "mmu.h"
#समावेश "nested.h"
#समावेश "pmu.h"
#समावेश "sgx.h"
#समावेश "trace.h"
#समावेश "vmx.h"
#समावेश "x86.h"

अटल bool __पढ़ो_mostly enable_shaकरोw_vmcs = 1;
module_param_named(enable_shaकरोw_vmcs, enable_shaकरोw_vmcs, bool, S_IRUGO);

अटल bool __पढ़ो_mostly nested_early_check = 0;
module_param(nested_early_check, bool, S_IRUGO);

#घोषणा CC KVM_NESTED_VMENTER_CONSISTENCY_CHECK

/*
 * Hyper-V requires all of these, so mark them as supported even though
 * they are just treated the same as all-context.
 */
#घोषणा VMX_VPID_EXTENT_SUPPORTED_MASK		\
	(VMX_VPID_EXTENT_INDIVIDUAL_ADDR_BIT |	\
	VMX_VPID_EXTENT_SINGLE_CONTEXT_BIT |	\
	VMX_VPID_EXTENT_GLOBAL_CONTEXT_BIT |	\
	VMX_VPID_EXTENT_SINGLE_NON_GLOBAL_BIT)

#घोषणा VMX_MISC_EMULATED_PREEMPTION_TIMER_RATE 5

क्रमागत अणु
	VMX_VMREAD_BITMAP,
	VMX_VMWRITE_BITMAP,
	VMX_BITMAP_NR
पूर्ण;
अटल अचिन्हित दीर्घ *vmx_biपंचांगap[VMX_BITMAP_NR];

#घोषणा vmx_vmपढ़ो_biपंचांगap                    (vmx_biपंचांगap[VMX_VMREAD_BITMAP])
#घोषणा vmx_vmग_लिखो_biपंचांगap                   (vmx_biपंचांगap[VMX_VMWRITE_BITMAP])

काष्ठा shaकरोw_vmcs_field अणु
	u16	encoding;
	u16	offset;
पूर्ण;
अटल काष्ठा shaकरोw_vmcs_field shaकरोw_पढ़ो_only_fields[] = अणु
#घोषणा SHADOW_FIELD_RO(x, y) अणु x, दुरत्व(काष्ठा vmcs12, y) पूर्ण,
#समावेश "vmcs_shadow_fields.h"
पूर्ण;
अटल पूर्णांक max_shaकरोw_पढ़ो_only_fields =
	ARRAY_SIZE(shaकरोw_पढ़ो_only_fields);

अटल काष्ठा shaकरोw_vmcs_field shaकरोw_पढ़ो_ग_लिखो_fields[] = अणु
#घोषणा SHADOW_FIELD_RW(x, y) अणु x, दुरत्व(काष्ठा vmcs12, y) पूर्ण,
#समावेश "vmcs_shadow_fields.h"
पूर्ण;
अटल पूर्णांक max_shaकरोw_पढ़ो_ग_लिखो_fields =
	ARRAY_SIZE(shaकरोw_पढ़ो_ग_लिखो_fields);

अटल व्योम init_vmcs_shaकरोw_fields(व्योम)
अणु
	पूर्णांक i, j;

	स_रखो(vmx_vmपढ़ो_biपंचांगap, 0xff, PAGE_SIZE);
	स_रखो(vmx_vmग_लिखो_biपंचांगap, 0xff, PAGE_SIZE);

	क्रम (i = j = 0; i < max_shaकरोw_पढ़ो_only_fields; i++) अणु
		काष्ठा shaकरोw_vmcs_field entry = shaकरोw_पढ़ो_only_fields[i];
		u16 field = entry.encoding;

		अगर (vmcs_field_width(field) == VMCS_FIELD_WIDTH_U64 &&
		    (i + 1 == max_shaकरोw_पढ़ो_only_fields ||
		     shaकरोw_पढ़ो_only_fields[i + 1].encoding != field + 1))
			pr_err("Missing field from shadow_read_only_field %x\n",
			       field + 1);

		clear_bit(field, vmx_vmपढ़ो_biपंचांगap);
		अगर (field & 1)
#अगर_घोषित CONFIG_X86_64
			जारी;
#अन्यथा
			entry.offset += माप(u32);
#पूर्ण_अगर
		shaकरोw_पढ़ो_only_fields[j++] = entry;
	पूर्ण
	max_shaकरोw_पढ़ो_only_fields = j;

	क्रम (i = j = 0; i < max_shaकरोw_पढ़ो_ग_लिखो_fields; i++) अणु
		काष्ठा shaकरोw_vmcs_field entry = shaकरोw_पढ़ो_ग_लिखो_fields[i];
		u16 field = entry.encoding;

		अगर (vmcs_field_width(field) == VMCS_FIELD_WIDTH_U64 &&
		    (i + 1 == max_shaकरोw_पढ़ो_ग_लिखो_fields ||
		     shaकरोw_पढ़ो_ग_लिखो_fields[i + 1].encoding != field + 1))
			pr_err("Missing field from shadow_read_write_field %x\n",
			       field + 1);

		WARN_ONCE(field >= GUEST_ES_AR_BYTES &&
			  field <= GUEST_TR_AR_BYTES,
			  "Update vmcs12_write_any() to drop reserved bits from AR_BYTES");

		/*
		 * PML and the preemption समयr can be emulated, but the
		 * processor cannot vmग_लिखो to fields that करोn't exist
		 * on bare metal.
		 */
		चयन (field) अणु
		हाल GUEST_PML_INDEX:
			अगर (!cpu_has_vmx_pml())
				जारी;
			अवरोध;
		हाल VMX_PREEMPTION_TIMER_VALUE:
			अगर (!cpu_has_vmx_preemption_समयr())
				जारी;
			अवरोध;
		हाल GUEST_INTR_STATUS:
			अगर (!cpu_has_vmx_apicv())
				जारी;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		clear_bit(field, vmx_vmग_लिखो_biपंचांगap);
		clear_bit(field, vmx_vmपढ़ो_biपंचांगap);
		अगर (field & 1)
#अगर_घोषित CONFIG_X86_64
			जारी;
#अन्यथा
			entry.offset += माप(u32);
#पूर्ण_अगर
		shaकरोw_पढ़ो_ग_लिखो_fields[j++] = entry;
	पूर्ण
	max_shaकरोw_पढ़ो_ग_लिखो_fields = j;
पूर्ण

/*
 * The following 3 functions, nested_vmx_succeed()/failValid()/failInvalid(),
 * set the success or error code of an emulated VMX inकाष्ठाion (as specअगरied
 * by Vol 2B, VMX Inकाष्ठाion Reference, "Conventions"), and skip the emulated
 * inकाष्ठाion.
 */
अटल पूर्णांक nested_vmx_succeed(काष्ठा kvm_vcpu *vcpu)
अणु
	vmx_set_rflags(vcpu, vmx_get_rflags(vcpu)
			& ~(X86_EFLAGS_CF | X86_EFLAGS_PF | X86_EFLAGS_AF |
			    X86_EFLAGS_ZF | X86_EFLAGS_SF | X86_EFLAGS_OF));
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल पूर्णांक nested_vmx_failInvalid(काष्ठा kvm_vcpu *vcpu)
अणु
	vmx_set_rflags(vcpu, (vmx_get_rflags(vcpu)
			& ~(X86_EFLAGS_PF | X86_EFLAGS_AF | X86_EFLAGS_ZF |
			    X86_EFLAGS_SF | X86_EFLAGS_OF))
			| X86_EFLAGS_CF);
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल पूर्णांक nested_vmx_failValid(काष्ठा kvm_vcpu *vcpu,
				u32 vm_inकाष्ठाion_error)
अणु
	vmx_set_rflags(vcpu, (vmx_get_rflags(vcpu)
			& ~(X86_EFLAGS_CF | X86_EFLAGS_PF | X86_EFLAGS_AF |
			    X86_EFLAGS_SF | X86_EFLAGS_OF))
			| X86_EFLAGS_ZF);
	get_vmcs12(vcpu)->vm_inकाष्ठाion_error = vm_inकाष्ठाion_error;
	/*
	 * We करोn't need to क्रमce a shaकरोw sync because
	 * VM_INSTRUCTION_ERROR is not shaकरोwed
	 */
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल पूर्णांक nested_vmx_fail(काष्ठा kvm_vcpu *vcpu, u32 vm_inकाष्ठाion_error)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * failValid ग_लिखोs the error number to the current VMCS, which
	 * can't be done if there isn't a current VMCS.
	 */
	अगर (vmx->nested.current_vmptr == -1ull && !vmx->nested.hv_evmcs)
		वापस nested_vmx_failInvalid(vcpu);

	वापस nested_vmx_failValid(vcpu, vm_inकाष्ठाion_error);
पूर्ण

अटल व्योम nested_vmx_पात(काष्ठा kvm_vcpu *vcpu, u32 indicator)
अणु
	/* TODO: not to reset guest simply here. */
	kvm_make_request(KVM_REQ_TRIPLE_FAULT, vcpu);
	pr_debug_ratelimited("kvm: nested vmx abort, indicator %d\n", indicator);
पूर्ण

अटल अंतरभूत bool vmx_control_verअगरy(u32 control, u32 low, u32 high)
अणु
	वापस fixed_bits_valid(control, low, high);
पूर्ण

अटल अंतरभूत u64 vmx_control_msr(u32 low, u32 high)
अणु
	वापस low | ((u64)high << 32);
पूर्ण

अटल व्योम vmx_disable_shaकरोw_vmcs(काष्ठा vcpu_vmx *vmx)
अणु
	secondary_exec_controls_clearbit(vmx, SECONDARY_EXEC_SHADOW_VMCS);
	vmcs_ग_लिखो64(VMCS_LINK_POINTER, -1ull);
	vmx->nested.need_vmcs12_to_shaकरोw_sync = false;
पूर्ण

अटल अंतरभूत व्योम nested_release_evmcs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (!vmx->nested.hv_evmcs)
		वापस;

	kvm_vcpu_unmap(vcpu, &vmx->nested.hv_evmcs_map, true);
	vmx->nested.hv_evmcs_vmptr = 0;
	vmx->nested.hv_evmcs = शून्य;
पूर्ण

अटल व्योम vmx_sync_vmcs_host_state(काष्ठा vcpu_vmx *vmx,
				     काष्ठा loaded_vmcs *prev)
अणु
	काष्ठा vmcs_host_state *dest, *src;

	अगर (unlikely(!vmx->guest_state_loaded))
		वापस;

	src = &prev->host_state;
	dest = &vmx->loaded_vmcs->host_state;

	vmx_set_host_fs_gs(dest, src->fs_sel, src->gs_sel, src->fs_base, src->gs_base);
	dest->ldt_sel = src->ldt_sel;
#अगर_घोषित CONFIG_X86_64
	dest->ds_sel = src->ds_sel;
	dest->es_sel = src->es_sel;
#पूर्ण_अगर
पूर्ण

अटल व्योम vmx_चयन_vmcs(काष्ठा kvm_vcpu *vcpu, काष्ठा loaded_vmcs *vmcs)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा loaded_vmcs *prev;
	पूर्णांक cpu;

	अगर (WARN_ON_ONCE(vmx->loaded_vmcs == vmcs))
		वापस;

	cpu = get_cpu();
	prev = vmx->loaded_vmcs;
	vmx->loaded_vmcs = vmcs;
	vmx_vcpu_load_vmcs(vcpu, cpu, prev);
	vmx_sync_vmcs_host_state(vmx, prev);
	put_cpu();

	vmx_रेजिस्टर_cache_reset(vcpu);
पूर्ण

/*
 * Free whatever needs to be मुक्तd from vmx->nested when L1 goes करोwn, or
 * just stops using VMX.
 */
अटल व्योम मुक्त_nested(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (WARN_ON_ONCE(vmx->loaded_vmcs != &vmx->vmcs01))
		vmx_चयन_vmcs(vcpu, &vmx->vmcs01);

	अगर (!vmx->nested.vmxon && !vmx->nested.smm.vmxon)
		वापस;

	kvm_clear_request(KVM_REQ_GET_NESTED_STATE_PAGES, vcpu);

	vmx->nested.vmxon = false;
	vmx->nested.smm.vmxon = false;
	मुक्त_vpid(vmx->nested.vpid02);
	vmx->nested.posted_पूर्णांकr_nv = -1;
	vmx->nested.current_vmptr = -1ull;
	अगर (enable_shaकरोw_vmcs) अणु
		vmx_disable_shaकरोw_vmcs(vmx);
		vmcs_clear(vmx->vmcs01.shaकरोw_vmcs);
		मुक्त_vmcs(vmx->vmcs01.shaकरोw_vmcs);
		vmx->vmcs01.shaकरोw_vmcs = शून्य;
	पूर्ण
	kमुक्त(vmx->nested.cached_vmcs12);
	vmx->nested.cached_vmcs12 = शून्य;
	kमुक्त(vmx->nested.cached_shaकरोw_vmcs12);
	vmx->nested.cached_shaकरोw_vmcs12 = शून्य;
	/* Unpin physical memory we referred to in the vmcs02 */
	अगर (vmx->nested.apic_access_page) अणु
		kvm_release_page_clean(vmx->nested.apic_access_page);
		vmx->nested.apic_access_page = शून्य;
	पूर्ण
	kvm_vcpu_unmap(vcpu, &vmx->nested.भव_apic_map, true);
	kvm_vcpu_unmap(vcpu, &vmx->nested.pi_desc_map, true);
	vmx->nested.pi_desc = शून्य;

	kvm_mmu_मुक्त_roots(vcpu, &vcpu->arch.guest_mmu, KVM_MMU_ROOTS_ALL);

	nested_release_evmcs(vcpu);

	मुक्त_loaded_vmcs(&vmx->nested.vmcs02);
पूर्ण

/*
 * Ensure that the current vmcs of the logical processor is the
 * vmcs01 of the vcpu beक्रमe calling मुक्त_nested().
 */
व्योम nested_vmx_मुक्त_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu_load(vcpu);
	vmx_leave_nested(vcpu);
	vcpu_put(vcpu);
पूर्ण

अटल व्योम nested_ept_inject_page_fault(काष्ठा kvm_vcpu *vcpu,
		काष्ठा x86_exception *fault)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u32 vm_निकास_reason;
	अचिन्हित दीर्घ निकास_qualअगरication = vcpu->arch.निकास_qualअगरication;

	अगर (vmx->nested.pml_full) अणु
		vm_निकास_reason = EXIT_REASON_PML_FULL;
		vmx->nested.pml_full = false;
		निकास_qualअगरication &= INTR_INFO_UNBLOCK_NMI;
	पूर्ण अन्यथा अगर (fault->error_code & PFERR_RSVD_MASK)
		vm_निकास_reason = EXIT_REASON_EPT_MISCONFIG;
	अन्यथा
		vm_निकास_reason = EXIT_REASON_EPT_VIOLATION;

	nested_vmx_vmनिकास(vcpu, vm_निकास_reason, 0, निकास_qualअगरication);
	vmcs12->guest_physical_address = fault->address;
पूर्ण

अटल व्योम nested_ept_init_mmu_context(काष्ठा kvm_vcpu *vcpu)
अणु
	WARN_ON(mmu_is_nested(vcpu));

	vcpu->arch.mmu = &vcpu->arch.guest_mmu;
	kvm_init_shaकरोw_ept_mmu(vcpu,
			to_vmx(vcpu)->nested.msrs.ept_caps &
			VMX_EPT_EXECUTE_ONLY_BIT,
			nested_ept_ad_enabled(vcpu),
			nested_ept_get_eptp(vcpu));
	vcpu->arch.mmu->get_guest_pgd     = nested_ept_get_eptp;
	vcpu->arch.mmu->inject_page_fault = nested_ept_inject_page_fault;
	vcpu->arch.mmu->get_pdptr         = kvm_pdptr_पढ़ो;

	vcpu->arch.walk_mmu              = &vcpu->arch.nested_mmu;
पूर्ण

अटल व्योम nested_ept_uninit_mmu_context(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.mmu = &vcpu->arch.root_mmu;
	vcpu->arch.walk_mmu = &vcpu->arch.root_mmu;
पूर्ण

अटल bool nested_vmx_is_page_fault_vmनिकास(काष्ठा vmcs12 *vmcs12,
					    u16 error_code)
अणु
	bool inequality, bit;

	bit = (vmcs12->exception_biपंचांगap & (1u << PF_VECTOR)) != 0;
	inequality =
		(error_code & vmcs12->page_fault_error_code_mask) !=
		 vmcs12->page_fault_error_code_match;
	वापस inequality ^ bit;
पूर्ण


/*
 * KVM wants to inject page-faults which it got to the guest. This function
 * checks whether in a nested guest, we need to inject them to L1 or L2.
 */
अटल पूर्णांक nested_vmx_check_exception(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ *निकास_qual)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	अचिन्हित पूर्णांक nr = vcpu->arch.exception.nr;
	bool has_payload = vcpu->arch.exception.has_payload;
	अचिन्हित दीर्घ payload = vcpu->arch.exception.payload;

	अगर (nr == PF_VECTOR) अणु
		अगर (vcpu->arch.exception.nested_apf) अणु
			*निकास_qual = vcpu->arch.apf.nested_apf_token;
			वापस 1;
		पूर्ण
		अगर (nested_vmx_is_page_fault_vmनिकास(vmcs12,
						    vcpu->arch.exception.error_code)) अणु
			*निकास_qual = has_payload ? payload : vcpu->arch.cr2;
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अगर (vmcs12->exception_biपंचांगap & (1u << nr)) अणु
		अगर (nr == DB_VECTOR) अणु
			अगर (!has_payload) अणु
				payload = vcpu->arch.dr6;
				payload &= ~DR6_BT;
				payload ^= DR6_ACTIVE_LOW;
			पूर्ण
			*निकास_qual = payload;
		पूर्ण अन्यथा
			*निकास_qual = 0;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम vmx_inject_page_fault_nested(काष्ठा kvm_vcpu *vcpu,
		काष्ठा x86_exception *fault)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);

	WARN_ON(!is_guest_mode(vcpu));

	अगर (nested_vmx_is_page_fault_vmनिकास(vmcs12, fault->error_code) &&
		!to_vmx(vcpu)->nested.nested_run_pending) अणु
		vmcs12->vm_निकास_पूर्णांकr_error_code = fault->error_code;
		nested_vmx_vmनिकास(vcpu, EXIT_REASON_EXCEPTION_NMI,
				  PF_VECTOR | INTR_TYPE_HARD_EXCEPTION |
				  INTR_INFO_DELIVER_CODE_MASK | INTR_INFO_VALID_MASK,
				  fault->address);
	पूर्ण अन्यथा अणु
		kvm_inject_page_fault(vcpu, fault);
	पूर्ण
पूर्ण

अटल पूर्णांक nested_vmx_check_io_biपंचांगap_controls(काष्ठा kvm_vcpu *vcpu,
					       काष्ठा vmcs12 *vmcs12)
अणु
	अगर (!nested_cpu_has(vmcs12, CPU_BASED_USE_IO_BITMAPS))
		वापस 0;

	अगर (CC(!page_address_valid(vcpu, vmcs12->io_biपंचांगap_a)) ||
	    CC(!page_address_valid(vcpu, vmcs12->io_biपंचांगap_b)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_msr_biपंचांगap_controls(काष्ठा kvm_vcpu *vcpu,
						काष्ठा vmcs12 *vmcs12)
अणु
	अगर (!nested_cpu_has(vmcs12, CPU_BASED_USE_MSR_BITMAPS))
		वापस 0;

	अगर (CC(!page_address_valid(vcpu, vmcs12->msr_biपंचांगap)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_tpr_shaकरोw_controls(काष्ठा kvm_vcpu *vcpu,
						काष्ठा vmcs12 *vmcs12)
अणु
	अगर (!nested_cpu_has(vmcs12, CPU_BASED_TPR_SHADOW))
		वापस 0;

	अगर (CC(!page_address_valid(vcpu, vmcs12->भव_apic_page_addr)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Check अगर MSR is पूर्णांकercepted क्रम L01 MSR biपंचांगap.
 */
अटल bool msr_ग_लिखो_पूर्णांकercepted_l01(काष्ठा kvm_vcpu *vcpu, u32 msr)
अणु
	अचिन्हित दीर्घ *msr_biपंचांगap;
	पूर्णांक f = माप(अचिन्हित दीर्घ);

	अगर (!cpu_has_vmx_msr_biपंचांगap())
		वापस true;

	msr_biपंचांगap = to_vmx(vcpu)->vmcs01.msr_biपंचांगap;

	अगर (msr <= 0x1fff) अणु
		वापस !!test_bit(msr, msr_biपंचांगap + 0x800 / f);
	पूर्ण अन्यथा अगर ((msr >= 0xc0000000) && (msr <= 0xc0001fff)) अणु
		msr &= 0x1fff;
		वापस !!test_bit(msr, msr_biपंचांगap + 0xc00 / f);
	पूर्ण

	वापस true;
पूर्ण

/*
 * If a msr is allowed by L0, we should check whether it is allowed by L1.
 * The corresponding bit will be cleared unless both of L0 and L1 allow it.
 */
अटल व्योम nested_vmx_disable_पूर्णांकercept_क्रम_msr(अचिन्हित दीर्घ *msr_biपंचांगap_l1,
					       अचिन्हित दीर्घ *msr_biपंचांगap_nested,
					       u32 msr, पूर्णांक type)
अणु
	पूर्णांक f = माप(अचिन्हित दीर्घ);

	/*
	 * See Intel PRM Vol. 3, 20.6.9 (MSR-Biपंचांगap Address). Early manuals
	 * have the ग_लिखो-low and पढ़ो-high biपंचांगap offsets the wrong way round.
	 * We can control MSRs 0x00000000-0x00001fff and 0xc0000000-0xc0001fff.
	 */
	अगर (msr <= 0x1fff) अणु
		अगर (type & MSR_TYPE_R &&
		   !test_bit(msr, msr_biपंचांगap_l1 + 0x000 / f))
			/* पढ़ो-low */
			__clear_bit(msr, msr_biपंचांगap_nested + 0x000 / f);

		अगर (type & MSR_TYPE_W &&
		   !test_bit(msr, msr_biपंचांगap_l1 + 0x800 / f))
			/* ग_लिखो-low */
			__clear_bit(msr, msr_biपंचांगap_nested + 0x800 / f);

	पूर्ण अन्यथा अगर ((msr >= 0xc0000000) && (msr <= 0xc0001fff)) अणु
		msr &= 0x1fff;
		अगर (type & MSR_TYPE_R &&
		   !test_bit(msr, msr_biपंचांगap_l1 + 0x400 / f))
			/* पढ़ो-high */
			__clear_bit(msr, msr_biपंचांगap_nested + 0x400 / f);

		अगर (type & MSR_TYPE_W &&
		   !test_bit(msr, msr_biपंचांगap_l1 + 0xc00 / f))
			/* ग_लिखो-high */
			__clear_bit(msr, msr_biपंचांगap_nested + 0xc00 / f);

	पूर्ण
पूर्ण

अटल अंतरभूत व्योम enable_x2apic_msr_पूर्णांकercepts(अचिन्हित दीर्घ *msr_biपंचांगap)
अणु
	पूर्णांक msr;

	क्रम (msr = 0x800; msr <= 0x8ff; msr += BITS_PER_LONG) अणु
		अचिन्हित word = msr / BITS_PER_LONG;

		msr_biपंचांगap[word] = ~0;
		msr_biपंचांगap[word + (0x800 / माप(दीर्घ))] = ~0;
	पूर्ण
पूर्ण

/*
 * Merge L0's and L1's MSR biपंचांगap, वापस false to indicate that
 * we करो not use the hardware.
 */
अटल अंतरभूत bool nested_vmx_prepare_msr_biपंचांगap(काष्ठा kvm_vcpu *vcpu,
						 काष्ठा vmcs12 *vmcs12)
अणु
	पूर्णांक msr;
	अचिन्हित दीर्घ *msr_biपंचांगap_l1;
	अचिन्हित दीर्घ *msr_biपंचांगap_l0 = to_vmx(vcpu)->nested.vmcs02.msr_biपंचांगap;
	काष्ठा kvm_host_map *map = &to_vmx(vcpu)->nested.msr_biपंचांगap_map;

	/* Nothing to करो अगर the MSR biपंचांगap is not in use.  */
	अगर (!cpu_has_vmx_msr_biपंचांगap() ||
	    !nested_cpu_has(vmcs12, CPU_BASED_USE_MSR_BITMAPS))
		वापस false;

	अगर (kvm_vcpu_map(vcpu, gpa_to_gfn(vmcs12->msr_biपंचांगap), map))
		वापस false;

	msr_biपंचांगap_l1 = (अचिन्हित दीर्घ *)map->hva;

	/*
	 * To keep the control flow simple, pay eight 8-byte ग_लिखोs (sixteen
	 * 4-byte ग_लिखोs on 32-bit प्रणालीs) up front to enable पूर्णांकercepts क्रम
	 * the x2APIC MSR range and selectively disable them below.
	 */
	enable_x2apic_msr_पूर्णांकercepts(msr_biपंचांगap_l0);

	अगर (nested_cpu_has_virt_x2apic_mode(vmcs12)) अणु
		अगर (nested_cpu_has_apic_reg_virt(vmcs12)) अणु
			/*
			 * L0 need not पूर्णांकercept पढ़ोs क्रम MSRs between 0x800
			 * and 0x8ff, it just lets the processor take the value
			 * from the भव-APIC page; take those 256 bits
			 * directly from the L1 biपंचांगap.
			 */
			क्रम (msr = 0x800; msr <= 0x8ff; msr += BITS_PER_LONG) अणु
				अचिन्हित word = msr / BITS_PER_LONG;

				msr_biपंचांगap_l0[word] = msr_biपंचांगap_l1[word];
			पूर्ण
		पूर्ण

		nested_vmx_disable_पूर्णांकercept_क्रम_msr(
			msr_biपंचांगap_l1, msr_biपंचांगap_l0,
			X2APIC_MSR(APIC_TASKPRI),
			MSR_TYPE_R | MSR_TYPE_W);

		अगर (nested_cpu_has_vid(vmcs12)) अणु
			nested_vmx_disable_पूर्णांकercept_क्रम_msr(
				msr_biपंचांगap_l1, msr_biपंचांगap_l0,
				X2APIC_MSR(APIC_EOI),
				MSR_TYPE_W);
			nested_vmx_disable_पूर्णांकercept_क्रम_msr(
				msr_biपंचांगap_l1, msr_biपंचांगap_l0,
				X2APIC_MSR(APIC_SELF_IPI),
				MSR_TYPE_W);
		पूर्ण
	पूर्ण

	/* KVM unconditionally exposes the FS/GS base MSRs to L1. */
#अगर_घोषित CONFIG_X86_64
	nested_vmx_disable_पूर्णांकercept_क्रम_msr(msr_biपंचांगap_l1, msr_biपंचांगap_l0,
					     MSR_FS_BASE, MSR_TYPE_RW);

	nested_vmx_disable_पूर्णांकercept_क्रम_msr(msr_biपंचांगap_l1, msr_biपंचांगap_l0,
					     MSR_GS_BASE, MSR_TYPE_RW);

	nested_vmx_disable_पूर्णांकercept_क्रम_msr(msr_biपंचांगap_l1, msr_biपंचांगap_l0,
					     MSR_KERNEL_GS_BASE, MSR_TYPE_RW);
#पूर्ण_अगर

	/*
	 * Checking the L0->L1 biपंचांगap is trying to verअगरy two things:
	 *
	 * 1. L0 gave a permission to L1 to actually passthrough the MSR. This
	 *    ensures that we करो not accidentally generate an L02 MSR biपंचांगap
	 *    from the L12 MSR biपंचांगap that is too permissive.
	 * 2. That L1 or L2s have actually used the MSR. This aव्योमs
	 *    unnecessarily merging of the biपंचांगap अगर the MSR is unused. This
	 *    works properly because we only update the L01 MSR biपंचांगap lazily.
	 *    So even अगर L0 should pass L1 these MSRs, the L01 biपंचांगap is only
	 *    updated to reflect this when L1 (or its L2s) actually ग_लिखो to
	 *    the MSR.
	 */
	अगर (!msr_ग_लिखो_पूर्णांकercepted_l01(vcpu, MSR_IA32_SPEC_CTRL))
		nested_vmx_disable_पूर्णांकercept_क्रम_msr(
					msr_biपंचांगap_l1, msr_biपंचांगap_l0,
					MSR_IA32_SPEC_CTRL,
					MSR_TYPE_R | MSR_TYPE_W);

	अगर (!msr_ग_लिखो_पूर्णांकercepted_l01(vcpu, MSR_IA32_PRED_CMD))
		nested_vmx_disable_पूर्णांकercept_क्रम_msr(
					msr_biपंचांगap_l1, msr_biपंचांगap_l0,
					MSR_IA32_PRED_CMD,
					MSR_TYPE_W);

	kvm_vcpu_unmap(vcpu, &to_vmx(vcpu)->nested.msr_biपंचांगap_map, false);

	वापस true;
पूर्ण

अटल व्योम nested_cache_shaकरोw_vmcs12(काष्ठा kvm_vcpu *vcpu,
				       काष्ठा vmcs12 *vmcs12)
अणु
	काष्ठा kvm_host_map map;
	काष्ठा vmcs12 *shaकरोw;

	अगर (!nested_cpu_has_shaकरोw_vmcs(vmcs12) ||
	    vmcs12->vmcs_link_poपूर्णांकer == -1ull)
		वापस;

	shaकरोw = get_shaकरोw_vmcs12(vcpu);

	अगर (kvm_vcpu_map(vcpu, gpa_to_gfn(vmcs12->vmcs_link_poपूर्णांकer), &map))
		वापस;

	स_नकल(shaकरोw, map.hva, VMCS12_SIZE);
	kvm_vcpu_unmap(vcpu, &map, false);
पूर्ण

अटल व्योम nested_flush_cached_shaकरोw_vmcs12(काष्ठा kvm_vcpu *vcpu,
					      काष्ठा vmcs12 *vmcs12)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (!nested_cpu_has_shaकरोw_vmcs(vmcs12) ||
	    vmcs12->vmcs_link_poपूर्णांकer == -1ull)
		वापस;

	kvm_ग_लिखो_guest(vmx->vcpu.kvm, vmcs12->vmcs_link_poपूर्णांकer,
			get_shaकरोw_vmcs12(vcpu), VMCS12_SIZE);
पूर्ण

/*
 * In nested भवization, check अगर L1 has set
 * VM_EXIT_ACK_INTR_ON_EXIT
 */
अटल bool nested_निकास_पूर्णांकr_ack_set(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस get_vmcs12(vcpu)->vm_निकास_controls &
		VM_EXIT_ACK_INTR_ON_EXIT;
पूर्ण

अटल पूर्णांक nested_vmx_check_apic_access_controls(काष्ठा kvm_vcpu *vcpu,
					  काष्ठा vmcs12 *vmcs12)
अणु
	अगर (nested_cpu_has2(vmcs12, SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES) &&
	    CC(!page_address_valid(vcpu, vmcs12->apic_access_addr)))
		वापस -EINVAL;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_apicv_controls(काष्ठा kvm_vcpu *vcpu,
					   काष्ठा vmcs12 *vmcs12)
अणु
	अगर (!nested_cpu_has_virt_x2apic_mode(vmcs12) &&
	    !nested_cpu_has_apic_reg_virt(vmcs12) &&
	    !nested_cpu_has_vid(vmcs12) &&
	    !nested_cpu_has_posted_पूर्णांकr(vmcs12))
		वापस 0;

	/*
	 * If भवize x2apic mode is enabled,
	 * भवize apic access must be disabled.
	 */
	अगर (CC(nested_cpu_has_virt_x2apic_mode(vmcs12) &&
	       nested_cpu_has2(vmcs12, SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES)))
		वापस -EINVAL;

	/*
	 * If भव पूर्णांकerrupt delivery is enabled,
	 * we must निकास on बाह्यal पूर्णांकerrupts.
	 */
	अगर (CC(nested_cpu_has_vid(vmcs12) && !nested_निकास_on_पूर्णांकr(vcpu)))
		वापस -EINVAL;

	/*
	 * bits 15:8 should be zero in posted_पूर्णांकr_nv,
	 * the descriptor address has been alपढ़ोy checked
	 * in nested_get_vmcs12_pages.
	 *
	 * bits 5:0 of posted_पूर्णांकr_desc_addr should be zero.
	 */
	अगर (nested_cpu_has_posted_पूर्णांकr(vmcs12) &&
	   (CC(!nested_cpu_has_vid(vmcs12)) ||
	    CC(!nested_निकास_पूर्णांकr_ack_set(vcpu)) ||
	    CC((vmcs12->posted_पूर्णांकr_nv & 0xff00)) ||
	    CC(!kvm_vcpu_is_legal_aligned_gpa(vcpu, vmcs12->posted_पूर्णांकr_desc_addr, 64))))
		वापस -EINVAL;

	/* tpr shaकरोw is needed by all apicv features. */
	अगर (CC(!nested_cpu_has(vmcs12, CPU_BASED_TPR_SHADOW)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_msr_चयन(काष्ठा kvm_vcpu *vcpu,
				       u32 count, u64 addr)
अणु
	अगर (count == 0)
		वापस 0;

	अगर (!kvm_vcpu_is_legal_aligned_gpa(vcpu, addr, 16) ||
	    !kvm_vcpu_is_legal_gpa(vcpu, (addr + count * माप(काष्ठा vmx_msr_entry) - 1)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_निकास_msr_चयन_controls(काष्ठा kvm_vcpu *vcpu,
						     काष्ठा vmcs12 *vmcs12)
अणु
	अगर (CC(nested_vmx_check_msr_चयन(vcpu,
					   vmcs12->vm_निकास_msr_load_count,
					   vmcs12->vm_निकास_msr_load_addr)) ||
	    CC(nested_vmx_check_msr_चयन(vcpu,
					   vmcs12->vm_निकास_msr_store_count,
					   vmcs12->vm_निकास_msr_store_addr)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_entry_msr_चयन_controls(काष्ठा kvm_vcpu *vcpu,
                                                      काष्ठा vmcs12 *vmcs12)
अणु
	अगर (CC(nested_vmx_check_msr_चयन(vcpu,
					   vmcs12->vm_entry_msr_load_count,
					   vmcs12->vm_entry_msr_load_addr)))
                वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_pml_controls(काष्ठा kvm_vcpu *vcpu,
					 काष्ठा vmcs12 *vmcs12)
अणु
	अगर (!nested_cpu_has_pml(vmcs12))
		वापस 0;

	अगर (CC(!nested_cpu_has_ept(vmcs12)) ||
	    CC(!page_address_valid(vcpu, vmcs12->pml_address)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_unrestricted_guest_controls(काष्ठा kvm_vcpu *vcpu,
							काष्ठा vmcs12 *vmcs12)
अणु
	अगर (CC(nested_cpu_has2(vmcs12, SECONDARY_EXEC_UNRESTRICTED_GUEST) &&
	       !nested_cpu_has_ept(vmcs12)))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_mode_based_ept_exec_controls(काष्ठा kvm_vcpu *vcpu,
							 काष्ठा vmcs12 *vmcs12)
अणु
	अगर (CC(nested_cpu_has2(vmcs12, SECONDARY_EXEC_MODE_BASED_EPT_EXEC) &&
	       !nested_cpu_has_ept(vmcs12)))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_shaकरोw_vmcs_controls(काष्ठा kvm_vcpu *vcpu,
						 काष्ठा vmcs12 *vmcs12)
अणु
	अगर (!nested_cpu_has_shaकरोw_vmcs(vmcs12))
		वापस 0;

	अगर (CC(!page_address_valid(vcpu, vmcs12->vmपढ़ो_biपंचांगap)) ||
	    CC(!page_address_valid(vcpu, vmcs12->vmग_लिखो_biपंचांगap)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_msr_check_common(काष्ठा kvm_vcpu *vcpu,
				       काष्ठा vmx_msr_entry *e)
अणु
	/* x2APIC MSR accesses are not allowed */
	अगर (CC(vcpu->arch.apic_base & X2APIC_ENABLE && e->index >> 8 == 0x8))
		वापस -EINVAL;
	अगर (CC(e->index == MSR_IA32_UCODE_WRITE) || /* SDM Table 35-2 */
	    CC(e->index == MSR_IA32_UCODE_REV))
		वापस -EINVAL;
	अगर (CC(e->reserved != 0))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_load_msr_check(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा vmx_msr_entry *e)
अणु
	अगर (CC(e->index == MSR_FS_BASE) ||
	    CC(e->index == MSR_GS_BASE) ||
	    CC(e->index == MSR_IA32_SMM_MONITOR_CTL) || /* SMM is not supported */
	    nested_vmx_msr_check_common(vcpu, e))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_store_msr_check(काष्ठा kvm_vcpu *vcpu,
				      काष्ठा vmx_msr_entry *e)
अणु
	अगर (CC(e->index == MSR_IA32_SMBASE) || /* SMM is not supported */
	    nested_vmx_msr_check_common(vcpu, e))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल u32 nested_vmx_max_atomic_चयन_msrs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u64 vmx_misc = vmx_control_msr(vmx->nested.msrs.misc_low,
				       vmx->nested.msrs.misc_high);

	वापस (vmx_misc_max_msr(vmx_misc) + 1) * VMX_MISC_MSR_LIST_MULTIPLIER;
पूर्ण

/*
 * Load guest's/host's msr at nested entry/निकास.
 * वापस 0 क्रम success, entry index क्रम failure.
 *
 * One of the failure modes क्रम MSR load/store is when a list exceeds the
 * भव hardware's capacity. To मुख्यtain compatibility with hardware inयंत्रuch
 * as possible, process all valid entries beक्रमe failing rather than precheck
 * क्रम a capacity violation.
 */
अटल u32 nested_vmx_load_msr(काष्ठा kvm_vcpu *vcpu, u64 gpa, u32 count)
अणु
	u32 i;
	काष्ठा vmx_msr_entry e;
	u32 max_msr_list_size = nested_vmx_max_atomic_चयन_msrs(vcpu);

	क्रम (i = 0; i < count; i++) अणु
		अगर (unlikely(i >= max_msr_list_size))
			जाओ fail;

		अगर (kvm_vcpu_पढ़ो_guest(vcpu, gpa + i * माप(e),
					&e, माप(e))) अणु
			pr_debug_ratelimited(
				"%s cannot read MSR entry (%u, 0x%08llx)\n",
				__func__, i, gpa + i * माप(e));
			जाओ fail;
		पूर्ण
		अगर (nested_vmx_load_msr_check(vcpu, &e)) अणु
			pr_debug_ratelimited(
				"%s check failed (%u, 0x%x, 0x%x)\n",
				__func__, i, e.index, e.reserved);
			जाओ fail;
		पूर्ण
		अगर (kvm_set_msr(vcpu, e.index, e.value)) अणु
			pr_debug_ratelimited(
				"%s cannot write MSR (%u, 0x%x, 0x%llx)\n",
				__func__, i, e.index, e.value);
			जाओ fail;
		पूर्ण
	पूर्ण
	वापस 0;
fail:
	/* Note, max_msr_list_size is at most 4096, i.e. this can't wrap. */
	वापस i + 1;
पूर्ण

अटल bool nested_vmx_get_vmनिकास_msr_value(काष्ठा kvm_vcpu *vcpu,
					    u32 msr_index,
					    u64 *data)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * If the L0 hypervisor stored a more accurate value क्रम the TSC that
	 * करोes not include the समय taken क्रम emulation of the L2->L1
	 * VM-निकास in L0, use the more accurate value.
	 */
	अगर (msr_index == MSR_IA32_TSC) अणु
		पूर्णांक i = vmx_find_loadstore_msr_slot(&vmx->msr_स्वतःstore.guest,
						    MSR_IA32_TSC);

		अगर (i >= 0) अणु
			u64 val = vmx->msr_स्वतःstore.guest.val[i].value;

			*data = kvm_पढ़ो_l1_tsc(vcpu, val);
			वापस true;
		पूर्ण
	पूर्ण

	अगर (kvm_get_msr(vcpu, msr_index, data)) अणु
		pr_debug_ratelimited("%s cannot read MSR (0x%x)\n", __func__,
			msr_index);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool पढ़ो_and_check_msr_entry(काष्ठा kvm_vcpu *vcpu, u64 gpa, पूर्णांक i,
				     काष्ठा vmx_msr_entry *e)
अणु
	अगर (kvm_vcpu_पढ़ो_guest(vcpu,
				gpa + i * माप(*e),
				e, 2 * माप(u32))) अणु
		pr_debug_ratelimited(
			"%s cannot read MSR entry (%u, 0x%08llx)\n",
			__func__, i, gpa + i * माप(*e));
		वापस false;
	पूर्ण
	अगर (nested_vmx_store_msr_check(vcpu, e)) अणु
		pr_debug_ratelimited(
			"%s check failed (%u, 0x%x, 0x%x)\n",
			__func__, i, e->index, e->reserved);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक nested_vmx_store_msr(काष्ठा kvm_vcpu *vcpu, u64 gpa, u32 count)
अणु
	u64 data;
	u32 i;
	काष्ठा vmx_msr_entry e;
	u32 max_msr_list_size = nested_vmx_max_atomic_चयन_msrs(vcpu);

	क्रम (i = 0; i < count; i++) अणु
		अगर (unlikely(i >= max_msr_list_size))
			वापस -EINVAL;

		अगर (!पढ़ो_and_check_msr_entry(vcpu, gpa, i, &e))
			वापस -EINVAL;

		अगर (!nested_vmx_get_vmनिकास_msr_value(vcpu, e.index, &data))
			वापस -EINVAL;

		अगर (kvm_vcpu_ग_लिखो_guest(vcpu,
					 gpa + i * माप(e) +
					     दुरत्व(काष्ठा vmx_msr_entry, value),
					 &data, माप(data))) अणु
			pr_debug_ratelimited(
				"%s cannot write MSR (%u, 0x%x, 0x%llx)\n",
				__func__, i, e.index, data);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल bool nested_msr_store_list_has_msr(काष्ठा kvm_vcpu *vcpu, u32 msr_index)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	u32 count = vmcs12->vm_निकास_msr_store_count;
	u64 gpa = vmcs12->vm_निकास_msr_store_addr;
	काष्ठा vmx_msr_entry e;
	u32 i;

	क्रम (i = 0; i < count; i++) अणु
		अगर (!पढ़ो_and_check_msr_entry(vcpu, gpa, i, &e))
			वापस false;

		अगर (e.index == msr_index)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम prepare_vmx_msr_स्वतःstore_list(काष्ठा kvm_vcpu *vcpu,
					   u32 msr_index)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा vmx_msrs *स्वतःstore = &vmx->msr_स्वतःstore.guest;
	bool in_vmcs12_store_list;
	पूर्णांक msr_स्वतःstore_slot;
	bool in_स्वतःstore_list;
	पूर्णांक last;

	msr_स्वतःstore_slot = vmx_find_loadstore_msr_slot(स्वतःstore, msr_index);
	in_स्वतःstore_list = msr_स्वतःstore_slot >= 0;
	in_vmcs12_store_list = nested_msr_store_list_has_msr(vcpu, msr_index);

	अगर (in_vmcs12_store_list && !in_स्वतःstore_list) अणु
		अगर (स्वतःstore->nr == MAX_NR_LOADSTORE_MSRS) अणु
			/*
			 * Emulated VMEntry करोes not fail here.  Instead a less
			 * accurate value will be वापसed by
			 * nested_vmx_get_vmनिकास_msr_value() using kvm_get_msr()
			 * instead of पढ़ोing the value from the vmcs02 VMExit
			 * MSR-store area.
			 */
			pr_warn_ratelimited(
				"Not enough msr entries in msr_autostore.  Can't add msr %x\n",
				msr_index);
			वापस;
		पूर्ण
		last = स्वतःstore->nr++;
		स्वतःstore->val[last].index = msr_index;
	पूर्ण अन्यथा अगर (!in_vmcs12_store_list && in_स्वतःstore_list) अणु
		last = --स्वतःstore->nr;
		स्वतःstore->val[msr_स्वतःstore_slot] = स्वतःstore->val[last];
	पूर्ण
पूर्ण

/*
 * Returns true अगर the MMU needs to be sync'd on nested VM-Enter/VM-Exit.
 * tl;dr: the MMU needs a sync अगर L0 is using shaकरोw paging and L1 didn't
 * enable VPID क्रम L2 (implying it expects a TLB flush on VMX transitions).
 * Here's why.
 *
 * If EPT is enabled by L0 a sync is never needed:
 * - अगर it is disabled by L1, then L0 is not shaकरोwing L1 or L2 PTEs, there
 *   cannot be unsync'd SPTEs क्रम either L1 or L2.
 *
 * - अगर it is also enabled by L1, then L0 करोesn't need to sync on VM-Enter
 *   VM-Enter as VM-Enter isn't required to invalidate guest-physical mappings
 *   (irrespective of VPID), i.e. L1 can't rely on the (भव) CPU to flush
 *   stale guest-physical mappings क्रम L2 from the TLB.  And as above, L0 isn't
 *   shaकरोwing L1 PTEs so there are no unsync'd SPTEs to sync on VM-Exit.
 *
 * If EPT is disabled by L0:
 * - अगर VPID is enabled by L1 (क्रम L2), the situation is similar to when L1
 *   enables EPT: L0 करोesn't need to sync as VM-Enter and VM-Exit aren't
 *   required to invalidate linear mappings (EPT is disabled so there are
 *   no combined or guest-physical mappings), i.e. L1 can't rely on the
 *   (भव) CPU to flush stale linear mappings क्रम either L2 or itself (L1).
 *
 * - however अगर VPID is disabled by L1, then a sync is needed as L1 expects all
 *   linear mappings (EPT is disabled so there are no combined or guest-physical
 *   mappings) to be invalidated on both VM-Enter and VM-Exit.
 *
 * Note, this logic is subtly dअगरferent than nested_has_guest_tlb_tag(), which
 * additionally checks that L2 has been asचिन्हित a VPID (when EPT is disabled).
 * Whether or not L2 has been asचिन्हित a VPID by L0 is irrelevant with respect
 * to L1's expectations, e.g. L0 needs to invalidate hardware TLB entries अगर L2
 * करोesn't have a unique VPID to prevent reusing L1's entries (assuming L1 has
 * been asचिन्हित a VPID), but L0 करोesn't need to करो a MMU sync because L1
 * करोesn't expect stale (virtual) TLB entries to be flushed, i.e. L1 doesn't
 * know that L0 will flush the TLB and so L1 will करो INVVPID as needed to flush
 * stale TLB entries, at which poपूर्णांक L0 will sync L2's MMU.
 */
अटल bool nested_vmx_transition_mmu_sync(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !enable_ept && !nested_cpu_has_vpid(get_vmcs12(vcpu));
पूर्ण

/*
 * Load guest's/host's cr3 at nested entry/निकास.  @nested_ept is true अगर we are
 * emulating VM-Entry पूर्णांकo a guest with EPT enabled.  On failure, the expected
 * Exit Qualअगरication (क्रम a VM-Entry consistency check VM-Exit) is asचिन्हित to
 * @entry_failure_code.
 */
अटल पूर्णांक nested_vmx_load_cr3(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr3, bool nested_ept,
			       क्रमागत vm_entry_failure_code *entry_failure_code)
अणु
	अगर (CC(kvm_vcpu_is_illegal_gpa(vcpu, cr3))) अणु
		*entry_failure_code = ENTRY_FAIL_DEFAULT;
		वापस -EINVAL;
	पूर्ण

	/*
	 * If PAE paging and EPT are both on, CR3 is not used by the CPU and
	 * must not be dereferenced.
	 */
	अगर (!nested_ept && is_pae_paging(vcpu) &&
	    (cr3 != kvm_पढ़ो_cr3(vcpu) || pdptrs_changed(vcpu))) अणु
		अगर (CC(!load_pdptrs(vcpu, vcpu->arch.walk_mmu, cr3))) अणु
			*entry_failure_code = ENTRY_FAIL_PDPTE;
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Unconditionally skip the TLB flush on fast CR3 चयन, all TLB
	 * flushes are handled by nested_vmx_transition_tlb_flush().  See
	 * nested_vmx_transition_mmu_sync क्रम details on skipping the MMU sync.
	 */
	अगर (!nested_ept)
		kvm_mmu_new_pgd(vcpu, cr3, true,
				!nested_vmx_transition_mmu_sync(vcpu));

	vcpu->arch.cr3 = cr3;
	kvm_रेजिस्टर_mark_available(vcpu, VCPU_EXREG_CR3);

	kvm_init_mmu(vcpu, false);

	वापस 0;
पूर्ण

/*
 * Returns अगर KVM is able to config CPU to tag TLB entries
 * populated by L2 dअगरferently than TLB entries populated
 * by L1.
 *
 * If L0 uses EPT, L1 and L2 run with dअगरferent EPTP because
 * guest_mode is part of kvm_mmu_page_role. Thus, TLB entries
 * are tagged with dअगरferent EPTP.
 *
 * If L1 uses VPID and we allocated a vpid02, TLB entries are tagged
 * with dअगरferent VPID (L1 entries are tagged with vmx->vpid
 * जबतक L2 entries are tagged with vmx->nested.vpid02).
 */
अटल bool nested_has_guest_tlb_tag(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);

	वापस enable_ept ||
	       (nested_cpu_has_vpid(vmcs12) && to_vmx(vcpu)->nested.vpid02);
पूर्ण

अटल व्योम nested_vmx_transition_tlb_flush(काष्ठा kvm_vcpu *vcpu,
					    काष्ठा vmcs12 *vmcs12,
					    bool is_vmenter)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * If VPID is disabled, linear and combined mappings are flushed on
	 * VM-Enter/VM-Exit, and guest-physical mappings are valid only क्रम
	 * their associated EPTP.
	 */
	अगर (!enable_vpid)
		वापस;

	/*
	 * If vmcs12 करोesn't use VPID, L1 expects linear and combined mappings
	 * क्रम *all* contexts to be flushed on VM-Enter/VM-Exit.
	 *
	 * If VPID is enabled and used by vmc12, but L2 करोes not have a unique
	 * TLB tag (ASID), i.e. EPT is disabled and KVM was unable to allocate
	 * a VPID क्रम L2, flush the current context as the effective ASID is
	 * common to both L1 and L2.
	 *
	 * Defer the flush so that it runs after vmcs02.EPTP has been set by
	 * KVM_REQ_LOAD_MMU_PGD (अगर nested EPT is enabled) and to aव्योम
	 * redundant flushes further करोwn the nested pipeline.
	 *
	 * If a TLB flush isn't required due to any of the above, and vpid12 is
	 * changing then the new "virtual" VPID (vpid12) will reuse the same
	 * "real" VPID (vpid02), and so needs to be sync'd.  There is no direct
	 * mapping between vpid02 and vpid12, vpid02 is per-vCPU and reused क्रम
	 * all nested vCPUs.
	 */
	अगर (!nested_cpu_has_vpid(vmcs12)) अणु
		kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
	पूर्ण अन्यथा अगर (!nested_has_guest_tlb_tag(vcpu)) अणु
		kvm_make_request(KVM_REQ_TLB_FLUSH_CURRENT, vcpu);
	पूर्ण अन्यथा अगर (is_vmenter &&
		   vmcs12->भव_processor_id != vmx->nested.last_vpid) अणु
		vmx->nested.last_vpid = vmcs12->भव_processor_id;
		vpid_sync_context(nested_get_vpid02(vcpu));
	पूर्ण
पूर्ण

अटल bool is_bitwise_subset(u64 superset, u64 subset, u64 mask)
अणु
	superset &= mask;
	subset &= mask;

	वापस (superset | subset) == superset;
पूर्ण

अटल पूर्णांक vmx_restore_vmx_basic(काष्ठा vcpu_vmx *vmx, u64 data)
अणु
	स्थिर u64 feature_and_reserved =
		/* feature (except bit 48; see below) */
		BIT_ULL(49) | BIT_ULL(54) | BIT_ULL(55) |
		/* reserved */
		BIT_ULL(31) | GENMASK_ULL(47, 45) | GENMASK_ULL(63, 56);
	u64 vmx_basic = vmx->nested.msrs.basic;

	अगर (!is_bitwise_subset(vmx_basic, data, feature_and_reserved))
		वापस -EINVAL;

	/*
	 * KVM करोes not emulate a version of VMX that स्थिरrains physical
	 * addresses of VMX काष्ठाures (e.g. VMCS) to 32-bits.
	 */
	अगर (data & BIT_ULL(48))
		वापस -EINVAL;

	अगर (vmx_basic_vmcs_revision_id(vmx_basic) !=
	    vmx_basic_vmcs_revision_id(data))
		वापस -EINVAL;

	अगर (vmx_basic_vmcs_size(vmx_basic) > vmx_basic_vmcs_size(data))
		वापस -EINVAL;

	vmx->nested.msrs.basic = data;
	वापस 0;
पूर्ण

अटल पूर्णांक
vmx_restore_control_msr(काष्ठा vcpu_vmx *vmx, u32 msr_index, u64 data)
अणु
	u64 supported;
	u32 *lowp, *highp;

	चयन (msr_index) अणु
	हाल MSR_IA32_VMX_TRUE_PINBASED_CTLS:
		lowp = &vmx->nested.msrs.pinbased_ctls_low;
		highp = &vmx->nested.msrs.pinbased_ctls_high;
		अवरोध;
	हाल MSR_IA32_VMX_TRUE_PROCBASED_CTLS:
		lowp = &vmx->nested.msrs.procbased_ctls_low;
		highp = &vmx->nested.msrs.procbased_ctls_high;
		अवरोध;
	हाल MSR_IA32_VMX_TRUE_EXIT_CTLS:
		lowp = &vmx->nested.msrs.निकास_ctls_low;
		highp = &vmx->nested.msrs.निकास_ctls_high;
		अवरोध;
	हाल MSR_IA32_VMX_TRUE_ENTRY_CTLS:
		lowp = &vmx->nested.msrs.entry_ctls_low;
		highp = &vmx->nested.msrs.entry_ctls_high;
		अवरोध;
	हाल MSR_IA32_VMX_PROCBASED_CTLS2:
		lowp = &vmx->nested.msrs.secondary_ctls_low;
		highp = &vmx->nested.msrs.secondary_ctls_high;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	supported = vmx_control_msr(*lowp, *highp);

	/* Check must-be-1 bits are still 1. */
	अगर (!is_bitwise_subset(data, supported, GENMASK_ULL(31, 0)))
		वापस -EINVAL;

	/* Check must-be-0 bits are still 0. */
	अगर (!is_bitwise_subset(supported, data, GENMASK_ULL(63, 32)))
		वापस -EINVAL;

	*lowp = data;
	*highp = data >> 32;
	वापस 0;
पूर्ण

अटल पूर्णांक vmx_restore_vmx_misc(काष्ठा vcpu_vmx *vmx, u64 data)
अणु
	स्थिर u64 feature_and_reserved_bits =
		/* feature */
		BIT_ULL(5) | GENMASK_ULL(8, 6) | BIT_ULL(14) | BIT_ULL(15) |
		BIT_ULL(28) | BIT_ULL(29) | BIT_ULL(30) |
		/* reserved */
		GENMASK_ULL(13, 9) | BIT_ULL(31);
	u64 vmx_misc;

	vmx_misc = vmx_control_msr(vmx->nested.msrs.misc_low,
				   vmx->nested.msrs.misc_high);

	अगर (!is_bitwise_subset(vmx_misc, data, feature_and_reserved_bits))
		वापस -EINVAL;

	अगर ((vmx->nested.msrs.pinbased_ctls_high &
	     PIN_BASED_VMX_PREEMPTION_TIMER) &&
	    vmx_misc_preemption_समयr_rate(data) !=
	    vmx_misc_preemption_समयr_rate(vmx_misc))
		वापस -EINVAL;

	अगर (vmx_misc_cr3_count(data) > vmx_misc_cr3_count(vmx_misc))
		वापस -EINVAL;

	अगर (vmx_misc_max_msr(data) > vmx_misc_max_msr(vmx_misc))
		वापस -EINVAL;

	अगर (vmx_misc_mseg_revid(data) != vmx_misc_mseg_revid(vmx_misc))
		वापस -EINVAL;

	vmx->nested.msrs.misc_low = data;
	vmx->nested.msrs.misc_high = data >> 32;

	वापस 0;
पूर्ण

अटल पूर्णांक vmx_restore_vmx_ept_vpid_cap(काष्ठा vcpu_vmx *vmx, u64 data)
अणु
	u64 vmx_ept_vpid_cap;

	vmx_ept_vpid_cap = vmx_control_msr(vmx->nested.msrs.ept_caps,
					   vmx->nested.msrs.vpid_caps);

	/* Every bit is either reserved or a feature bit. */
	अगर (!is_bitwise_subset(vmx_ept_vpid_cap, data, -1ULL))
		वापस -EINVAL;

	vmx->nested.msrs.ept_caps = data;
	vmx->nested.msrs.vpid_caps = data >> 32;
	वापस 0;
पूर्ण

अटल पूर्णांक vmx_restore_fixed0_msr(काष्ठा vcpu_vmx *vmx, u32 msr_index, u64 data)
अणु
	u64 *msr;

	चयन (msr_index) अणु
	हाल MSR_IA32_VMX_CR0_FIXED0:
		msr = &vmx->nested.msrs.cr0_fixed0;
		अवरोध;
	हाल MSR_IA32_VMX_CR4_FIXED0:
		msr = &vmx->nested.msrs.cr4_fixed0;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	/*
	 * 1 bits (which indicates bits which "must-be-1" during VMX operation)
	 * must be 1 in the restored value.
	 */
	अगर (!is_bitwise_subset(data, *msr, -1ULL))
		वापस -EINVAL;

	*msr = data;
	वापस 0;
पूर्ण

/*
 * Called when userspace is restoring VMX MSRs.
 *
 * Returns 0 on success, non-0 otherwise.
 */
पूर्णांक vmx_set_vmx_msr(काष्ठा kvm_vcpu *vcpu, u32 msr_index, u64 data)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * Don't allow changes to the VMX capability MSRs जबतक the vCPU
	 * is in VMX operation.
	 */
	अगर (vmx->nested.vmxon)
		वापस -EBUSY;

	चयन (msr_index) अणु
	हाल MSR_IA32_VMX_BASIC:
		वापस vmx_restore_vmx_basic(vmx, data);
	हाल MSR_IA32_VMX_PINBASED_CTLS:
	हाल MSR_IA32_VMX_PROCBASED_CTLS:
	हाल MSR_IA32_VMX_EXIT_CTLS:
	हाल MSR_IA32_VMX_ENTRY_CTLS:
		/*
		 * The "non-true" VMX capability MSRs are generated from the
		 * "true" MSRs, so we करो not support restoring them directly.
		 *
		 * If userspace wants to emulate VMX_BASIC[55]=0, userspace
		 * should restore the "true" MSRs with the must-be-1 bits
		 * set according to the SDM Vol 3. A.2 "RESERVED CONTROLS AND
		 * DEFAULT SETTINGS".
		 */
		वापस -EINVAL;
	हाल MSR_IA32_VMX_TRUE_PINBASED_CTLS:
	हाल MSR_IA32_VMX_TRUE_PROCBASED_CTLS:
	हाल MSR_IA32_VMX_TRUE_EXIT_CTLS:
	हाल MSR_IA32_VMX_TRUE_ENTRY_CTLS:
	हाल MSR_IA32_VMX_PROCBASED_CTLS2:
		वापस vmx_restore_control_msr(vmx, msr_index, data);
	हाल MSR_IA32_VMX_MISC:
		वापस vmx_restore_vmx_misc(vmx, data);
	हाल MSR_IA32_VMX_CR0_FIXED0:
	हाल MSR_IA32_VMX_CR4_FIXED0:
		वापस vmx_restore_fixed0_msr(vmx, msr_index, data);
	हाल MSR_IA32_VMX_CR0_FIXED1:
	हाल MSR_IA32_VMX_CR4_FIXED1:
		/*
		 * These MSRs are generated based on the vCPU's CPUID, so we
		 * करो not support restoring them directly.
		 */
		वापस -EINVAL;
	हाल MSR_IA32_VMX_EPT_VPID_CAP:
		वापस vmx_restore_vmx_ept_vpid_cap(vmx, data);
	हाल MSR_IA32_VMX_VMCS_ENUM:
		vmx->nested.msrs.vmcs_क्रमागत = data;
		वापस 0;
	हाल MSR_IA32_VMX_VMFUNC:
		अगर (data & ~vmx->nested.msrs.vmfunc_controls)
			वापस -EINVAL;
		vmx->nested.msrs.vmfunc_controls = data;
		वापस 0;
	शेष:
		/*
		 * The rest of the VMX capability MSRs करो not support restore.
		 */
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Returns 0 on success, non-0 otherwise. */
पूर्णांक vmx_get_vmx_msr(काष्ठा nested_vmx_msrs *msrs, u32 msr_index, u64 *pdata)
अणु
	चयन (msr_index) अणु
	हाल MSR_IA32_VMX_BASIC:
		*pdata = msrs->basic;
		अवरोध;
	हाल MSR_IA32_VMX_TRUE_PINBASED_CTLS:
	हाल MSR_IA32_VMX_PINBASED_CTLS:
		*pdata = vmx_control_msr(
			msrs->pinbased_ctls_low,
			msrs->pinbased_ctls_high);
		अगर (msr_index == MSR_IA32_VMX_PINBASED_CTLS)
			*pdata |= PIN_BASED_ALWAYSON_WITHOUT_TRUE_MSR;
		अवरोध;
	हाल MSR_IA32_VMX_TRUE_PROCBASED_CTLS:
	हाल MSR_IA32_VMX_PROCBASED_CTLS:
		*pdata = vmx_control_msr(
			msrs->procbased_ctls_low,
			msrs->procbased_ctls_high);
		अगर (msr_index == MSR_IA32_VMX_PROCBASED_CTLS)
			*pdata |= CPU_BASED_ALWAYSON_WITHOUT_TRUE_MSR;
		अवरोध;
	हाल MSR_IA32_VMX_TRUE_EXIT_CTLS:
	हाल MSR_IA32_VMX_EXIT_CTLS:
		*pdata = vmx_control_msr(
			msrs->निकास_ctls_low,
			msrs->निकास_ctls_high);
		अगर (msr_index == MSR_IA32_VMX_EXIT_CTLS)
			*pdata |= VM_EXIT_ALWAYSON_WITHOUT_TRUE_MSR;
		अवरोध;
	हाल MSR_IA32_VMX_TRUE_ENTRY_CTLS:
	हाल MSR_IA32_VMX_ENTRY_CTLS:
		*pdata = vmx_control_msr(
			msrs->entry_ctls_low,
			msrs->entry_ctls_high);
		अगर (msr_index == MSR_IA32_VMX_ENTRY_CTLS)
			*pdata |= VM_ENTRY_ALWAYSON_WITHOUT_TRUE_MSR;
		अवरोध;
	हाल MSR_IA32_VMX_MISC:
		*pdata = vmx_control_msr(
			msrs->misc_low,
			msrs->misc_high);
		अवरोध;
	हाल MSR_IA32_VMX_CR0_FIXED0:
		*pdata = msrs->cr0_fixed0;
		अवरोध;
	हाल MSR_IA32_VMX_CR0_FIXED1:
		*pdata = msrs->cr0_fixed1;
		अवरोध;
	हाल MSR_IA32_VMX_CR4_FIXED0:
		*pdata = msrs->cr4_fixed0;
		अवरोध;
	हाल MSR_IA32_VMX_CR4_FIXED1:
		*pdata = msrs->cr4_fixed1;
		अवरोध;
	हाल MSR_IA32_VMX_VMCS_ENUM:
		*pdata = msrs->vmcs_क्रमागत;
		अवरोध;
	हाल MSR_IA32_VMX_PROCBASED_CTLS2:
		*pdata = vmx_control_msr(
			msrs->secondary_ctls_low,
			msrs->secondary_ctls_high);
		अवरोध;
	हाल MSR_IA32_VMX_EPT_VPID_CAP:
		*pdata = msrs->ept_caps |
			((u64)msrs->vpid_caps << 32);
		अवरोध;
	हाल MSR_IA32_VMX_VMFUNC:
		*pdata = msrs->vmfunc_controls;
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Copy the writable VMCS shaकरोw fields back to the VMCS12, in हाल they have
 * been modअगरied by the L1 guest.  Note, "writable" in this context means
 * "writable by the guest", i.e. tagged SHADOW_FIELD_RW; the set of
 * fields tagged SHADOW_FIELD_RO may or may not align with the "read-only"
 * VM-निकास inक्रमmation fields (which are actually writable अगर the vCPU is
 * configured to support "VMWRITE to any supported field in the VMCS").
 */
अटल व्योम copy_shaकरोw_to_vmcs12(काष्ठा vcpu_vmx *vmx)
अणु
	काष्ठा vmcs *shaकरोw_vmcs = vmx->vmcs01.shaकरोw_vmcs;
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(&vmx->vcpu);
	काष्ठा shaकरोw_vmcs_field field;
	अचिन्हित दीर्घ val;
	पूर्णांक i;

	अगर (WARN_ON(!shaकरोw_vmcs))
		वापस;

	preempt_disable();

	vmcs_load(shaकरोw_vmcs);

	क्रम (i = 0; i < max_shaकरोw_पढ़ो_ग_लिखो_fields; i++) अणु
		field = shaकरोw_पढ़ो_ग_लिखो_fields[i];
		val = __vmcs_पढ़ोl(field.encoding);
		vmcs12_ग_लिखो_any(vmcs12, field.encoding, field.offset, val);
	पूर्ण

	vmcs_clear(shaकरोw_vmcs);
	vmcs_load(vmx->loaded_vmcs->vmcs);

	preempt_enable();
पूर्ण

अटल व्योम copy_vmcs12_to_shaकरोw(काष्ठा vcpu_vmx *vmx)
अणु
	स्थिर काष्ठा shaकरोw_vmcs_field *fields[] = अणु
		shaकरोw_पढ़ो_ग_लिखो_fields,
		shaकरोw_पढ़ो_only_fields
	पूर्ण;
	स्थिर पूर्णांक max_fields[] = अणु
		max_shaकरोw_पढ़ो_ग_लिखो_fields,
		max_shaकरोw_पढ़ो_only_fields
	पूर्ण;
	काष्ठा vmcs *shaकरोw_vmcs = vmx->vmcs01.shaकरोw_vmcs;
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(&vmx->vcpu);
	काष्ठा shaकरोw_vmcs_field field;
	अचिन्हित दीर्घ val;
	पूर्णांक i, q;

	अगर (WARN_ON(!shaकरोw_vmcs))
		वापस;

	vmcs_load(shaकरोw_vmcs);

	क्रम (q = 0; q < ARRAY_SIZE(fields); q++) अणु
		क्रम (i = 0; i < max_fields[q]; i++) अणु
			field = fields[q][i];
			val = vmcs12_पढ़ो_any(vmcs12, field.encoding,
					      field.offset);
			__vmcs_ग_लिखोl(field.encoding, val);
		पूर्ण
	पूर्ण

	vmcs_clear(shaकरोw_vmcs);
	vmcs_load(vmx->loaded_vmcs->vmcs);
पूर्ण

अटल पूर्णांक copy_enlightened_to_vmcs12(काष्ठा vcpu_vmx *vmx)
अणु
	काष्ठा vmcs12 *vmcs12 = vmx->nested.cached_vmcs12;
	काष्ठा hv_enlightened_vmcs *evmcs = vmx->nested.hv_evmcs;

	/* HV_VMX_ENLIGHTENED_CLEAN_FIELD_NONE */
	vmcs12->tpr_threshold = evmcs->tpr_threshold;
	vmcs12->guest_rip = evmcs->guest_rip;

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_BASIC))) अणु
		vmcs12->guest_rsp = evmcs->guest_rsp;
		vmcs12->guest_rflags = evmcs->guest_rflags;
		vmcs12->guest_पूर्णांकerruptibility_info =
			evmcs->guest_पूर्णांकerruptibility_info;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_PROC))) अणु
		vmcs12->cpu_based_vm_exec_control =
			evmcs->cpu_based_vm_exec_control;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_EXCPN))) अणु
		vmcs12->exception_biपंचांगap = evmcs->exception_biपंचांगap;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_ENTRY))) अणु
		vmcs12->vm_entry_controls = evmcs->vm_entry_controls;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_EVENT))) अणु
		vmcs12->vm_entry_पूर्णांकr_info_field =
			evmcs->vm_entry_पूर्णांकr_info_field;
		vmcs12->vm_entry_exception_error_code =
			evmcs->vm_entry_exception_error_code;
		vmcs12->vm_entry_inकाष्ठाion_len =
			evmcs->vm_entry_inकाष्ठाion_len;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_HOST_GRP1))) अणु
		vmcs12->host_ia32_pat = evmcs->host_ia32_pat;
		vmcs12->host_ia32_efer = evmcs->host_ia32_efer;
		vmcs12->host_cr0 = evmcs->host_cr0;
		vmcs12->host_cr3 = evmcs->host_cr3;
		vmcs12->host_cr4 = evmcs->host_cr4;
		vmcs12->host_ia32_sysenter_esp = evmcs->host_ia32_sysenter_esp;
		vmcs12->host_ia32_sysenter_eip = evmcs->host_ia32_sysenter_eip;
		vmcs12->host_rip = evmcs->host_rip;
		vmcs12->host_ia32_sysenter_cs = evmcs->host_ia32_sysenter_cs;
		vmcs12->host_es_selector = evmcs->host_es_selector;
		vmcs12->host_cs_selector = evmcs->host_cs_selector;
		vmcs12->host_ss_selector = evmcs->host_ss_selector;
		vmcs12->host_ds_selector = evmcs->host_ds_selector;
		vmcs12->host_fs_selector = evmcs->host_fs_selector;
		vmcs12->host_gs_selector = evmcs->host_gs_selector;
		vmcs12->host_tr_selector = evmcs->host_tr_selector;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_GRP1))) अणु
		vmcs12->pin_based_vm_exec_control =
			evmcs->pin_based_vm_exec_control;
		vmcs12->vm_निकास_controls = evmcs->vm_निकास_controls;
		vmcs12->secondary_vm_exec_control =
			evmcs->secondary_vm_exec_control;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_IO_BITMAP))) अणु
		vmcs12->io_biपंचांगap_a = evmcs->io_biपंचांगap_a;
		vmcs12->io_biपंचांगap_b = evmcs->io_biपंचांगap_b;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_MSR_BITMAP))) अणु
		vmcs12->msr_biपंचांगap = evmcs->msr_biपंचांगap;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP2))) अणु
		vmcs12->guest_es_base = evmcs->guest_es_base;
		vmcs12->guest_cs_base = evmcs->guest_cs_base;
		vmcs12->guest_ss_base = evmcs->guest_ss_base;
		vmcs12->guest_ds_base = evmcs->guest_ds_base;
		vmcs12->guest_fs_base = evmcs->guest_fs_base;
		vmcs12->guest_gs_base = evmcs->guest_gs_base;
		vmcs12->guest_ldtr_base = evmcs->guest_ldtr_base;
		vmcs12->guest_tr_base = evmcs->guest_tr_base;
		vmcs12->guest_gdtr_base = evmcs->guest_gdtr_base;
		vmcs12->guest_idtr_base = evmcs->guest_idtr_base;
		vmcs12->guest_es_limit = evmcs->guest_es_limit;
		vmcs12->guest_cs_limit = evmcs->guest_cs_limit;
		vmcs12->guest_ss_limit = evmcs->guest_ss_limit;
		vmcs12->guest_ds_limit = evmcs->guest_ds_limit;
		vmcs12->guest_fs_limit = evmcs->guest_fs_limit;
		vmcs12->guest_gs_limit = evmcs->guest_gs_limit;
		vmcs12->guest_ldtr_limit = evmcs->guest_ldtr_limit;
		vmcs12->guest_tr_limit = evmcs->guest_tr_limit;
		vmcs12->guest_gdtr_limit = evmcs->guest_gdtr_limit;
		vmcs12->guest_idtr_limit = evmcs->guest_idtr_limit;
		vmcs12->guest_es_ar_bytes = evmcs->guest_es_ar_bytes;
		vmcs12->guest_cs_ar_bytes = evmcs->guest_cs_ar_bytes;
		vmcs12->guest_ss_ar_bytes = evmcs->guest_ss_ar_bytes;
		vmcs12->guest_ds_ar_bytes = evmcs->guest_ds_ar_bytes;
		vmcs12->guest_fs_ar_bytes = evmcs->guest_fs_ar_bytes;
		vmcs12->guest_gs_ar_bytes = evmcs->guest_gs_ar_bytes;
		vmcs12->guest_ldtr_ar_bytes = evmcs->guest_ldtr_ar_bytes;
		vmcs12->guest_tr_ar_bytes = evmcs->guest_tr_ar_bytes;
		vmcs12->guest_es_selector = evmcs->guest_es_selector;
		vmcs12->guest_cs_selector = evmcs->guest_cs_selector;
		vmcs12->guest_ss_selector = evmcs->guest_ss_selector;
		vmcs12->guest_ds_selector = evmcs->guest_ds_selector;
		vmcs12->guest_fs_selector = evmcs->guest_fs_selector;
		vmcs12->guest_gs_selector = evmcs->guest_gs_selector;
		vmcs12->guest_ldtr_selector = evmcs->guest_ldtr_selector;
		vmcs12->guest_tr_selector = evmcs->guest_tr_selector;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_GRP2))) अणु
		vmcs12->tsc_offset = evmcs->tsc_offset;
		vmcs12->भव_apic_page_addr = evmcs->भव_apic_page_addr;
		vmcs12->xss_निकास_biपंचांगap = evmcs->xss_निकास_biपंचांगap;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_CRDR))) अणु
		vmcs12->cr0_guest_host_mask = evmcs->cr0_guest_host_mask;
		vmcs12->cr4_guest_host_mask = evmcs->cr4_guest_host_mask;
		vmcs12->cr0_पढ़ो_shaकरोw = evmcs->cr0_पढ़ो_shaकरोw;
		vmcs12->cr4_पढ़ो_shaकरोw = evmcs->cr4_पढ़ो_shaकरोw;
		vmcs12->guest_cr0 = evmcs->guest_cr0;
		vmcs12->guest_cr3 = evmcs->guest_cr3;
		vmcs12->guest_cr4 = evmcs->guest_cr4;
		vmcs12->guest_dr7 = evmcs->guest_dr7;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_HOST_POINTER))) अणु
		vmcs12->host_fs_base = evmcs->host_fs_base;
		vmcs12->host_gs_base = evmcs->host_gs_base;
		vmcs12->host_tr_base = evmcs->host_tr_base;
		vmcs12->host_gdtr_base = evmcs->host_gdtr_base;
		vmcs12->host_idtr_base = evmcs->host_idtr_base;
		vmcs12->host_rsp = evmcs->host_rsp;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_CONTROL_XLAT))) अणु
		vmcs12->ept_poपूर्णांकer = evmcs->ept_poपूर्णांकer;
		vmcs12->भव_processor_id = evmcs->भव_processor_id;
	पूर्ण

	अगर (unlikely(!(evmcs->hv_clean_fields &
		       HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP1))) अणु
		vmcs12->vmcs_link_poपूर्णांकer = evmcs->vmcs_link_poपूर्णांकer;
		vmcs12->guest_ia32_debugctl = evmcs->guest_ia32_debugctl;
		vmcs12->guest_ia32_pat = evmcs->guest_ia32_pat;
		vmcs12->guest_ia32_efer = evmcs->guest_ia32_efer;
		vmcs12->guest_pdptr0 = evmcs->guest_pdptr0;
		vmcs12->guest_pdptr1 = evmcs->guest_pdptr1;
		vmcs12->guest_pdptr2 = evmcs->guest_pdptr2;
		vmcs12->guest_pdptr3 = evmcs->guest_pdptr3;
		vmcs12->guest_pending_dbg_exceptions =
			evmcs->guest_pending_dbg_exceptions;
		vmcs12->guest_sysenter_esp = evmcs->guest_sysenter_esp;
		vmcs12->guest_sysenter_eip = evmcs->guest_sysenter_eip;
		vmcs12->guest_bndcfgs = evmcs->guest_bndcfgs;
		vmcs12->guest_activity_state = evmcs->guest_activity_state;
		vmcs12->guest_sysenter_cs = evmcs->guest_sysenter_cs;
	पूर्ण

	/*
	 * Not used?
	 * vmcs12->vm_निकास_msr_store_addr = evmcs->vm_निकास_msr_store_addr;
	 * vmcs12->vm_निकास_msr_load_addr = evmcs->vm_निकास_msr_load_addr;
	 * vmcs12->vm_entry_msr_load_addr = evmcs->vm_entry_msr_load_addr;
	 * vmcs12->page_fault_error_code_mask =
	 *		evmcs->page_fault_error_code_mask;
	 * vmcs12->page_fault_error_code_match =
	 *		evmcs->page_fault_error_code_match;
	 * vmcs12->cr3_target_count = evmcs->cr3_target_count;
	 * vmcs12->vm_निकास_msr_store_count = evmcs->vm_निकास_msr_store_count;
	 * vmcs12->vm_निकास_msr_load_count = evmcs->vm_निकास_msr_load_count;
	 * vmcs12->vm_entry_msr_load_count = evmcs->vm_entry_msr_load_count;
	 */

	/*
	 * Read only fields:
	 * vmcs12->guest_physical_address = evmcs->guest_physical_address;
	 * vmcs12->vm_inकाष्ठाion_error = evmcs->vm_inकाष्ठाion_error;
	 * vmcs12->vm_निकास_reason = evmcs->vm_निकास_reason;
	 * vmcs12->vm_निकास_पूर्णांकr_info = evmcs->vm_निकास_पूर्णांकr_info;
	 * vmcs12->vm_निकास_पूर्णांकr_error_code = evmcs->vm_निकास_पूर्णांकr_error_code;
	 * vmcs12->idt_vectoring_info_field = evmcs->idt_vectoring_info_field;
	 * vmcs12->idt_vectoring_error_code = evmcs->idt_vectoring_error_code;
	 * vmcs12->vm_निकास_inकाष्ठाion_len = evmcs->vm_निकास_inकाष्ठाion_len;
	 * vmcs12->vmx_inकाष्ठाion_info = evmcs->vmx_inकाष्ठाion_info;
	 * vmcs12->निकास_qualअगरication = evmcs->निकास_qualअगरication;
	 * vmcs12->guest_linear_address = evmcs->guest_linear_address;
	 *
	 * Not present in काष्ठा vmcs12:
	 * vmcs12->निकास_io_inकाष्ठाion_ecx = evmcs->निकास_io_inकाष्ठाion_ecx;
	 * vmcs12->निकास_io_inकाष्ठाion_esi = evmcs->निकास_io_inकाष्ठाion_esi;
	 * vmcs12->निकास_io_inकाष्ठाion_edi = evmcs->निकास_io_inकाष्ठाion_edi;
	 * vmcs12->निकास_io_inकाष्ठाion_eip = evmcs->निकास_io_inकाष्ठाion_eip;
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक copy_vmcs12_to_enlightened(काष्ठा vcpu_vmx *vmx)
अणु
	काष्ठा vmcs12 *vmcs12 = vmx->nested.cached_vmcs12;
	काष्ठा hv_enlightened_vmcs *evmcs = vmx->nested.hv_evmcs;

	/*
	 * Should not be changed by KVM:
	 *
	 * evmcs->host_es_selector = vmcs12->host_es_selector;
	 * evmcs->host_cs_selector = vmcs12->host_cs_selector;
	 * evmcs->host_ss_selector = vmcs12->host_ss_selector;
	 * evmcs->host_ds_selector = vmcs12->host_ds_selector;
	 * evmcs->host_fs_selector = vmcs12->host_fs_selector;
	 * evmcs->host_gs_selector = vmcs12->host_gs_selector;
	 * evmcs->host_tr_selector = vmcs12->host_tr_selector;
	 * evmcs->host_ia32_pat = vmcs12->host_ia32_pat;
	 * evmcs->host_ia32_efer = vmcs12->host_ia32_efer;
	 * evmcs->host_cr0 = vmcs12->host_cr0;
	 * evmcs->host_cr3 = vmcs12->host_cr3;
	 * evmcs->host_cr4 = vmcs12->host_cr4;
	 * evmcs->host_ia32_sysenter_esp = vmcs12->host_ia32_sysenter_esp;
	 * evmcs->host_ia32_sysenter_eip = vmcs12->host_ia32_sysenter_eip;
	 * evmcs->host_rip = vmcs12->host_rip;
	 * evmcs->host_ia32_sysenter_cs = vmcs12->host_ia32_sysenter_cs;
	 * evmcs->host_fs_base = vmcs12->host_fs_base;
	 * evmcs->host_gs_base = vmcs12->host_gs_base;
	 * evmcs->host_tr_base = vmcs12->host_tr_base;
	 * evmcs->host_gdtr_base = vmcs12->host_gdtr_base;
	 * evmcs->host_idtr_base = vmcs12->host_idtr_base;
	 * evmcs->host_rsp = vmcs12->host_rsp;
	 * sync_vmcs02_to_vmcs12() करोesn't पढ़ो these:
	 * evmcs->io_biपंचांगap_a = vmcs12->io_biपंचांगap_a;
	 * evmcs->io_biपंचांगap_b = vmcs12->io_biपंचांगap_b;
	 * evmcs->msr_biपंचांगap = vmcs12->msr_biपंचांगap;
	 * evmcs->ept_poपूर्णांकer = vmcs12->ept_poपूर्णांकer;
	 * evmcs->xss_निकास_biपंचांगap = vmcs12->xss_निकास_biपंचांगap;
	 * evmcs->vm_निकास_msr_store_addr = vmcs12->vm_निकास_msr_store_addr;
	 * evmcs->vm_निकास_msr_load_addr = vmcs12->vm_निकास_msr_load_addr;
	 * evmcs->vm_entry_msr_load_addr = vmcs12->vm_entry_msr_load_addr;
	 * evmcs->tpr_threshold = vmcs12->tpr_threshold;
	 * evmcs->भव_processor_id = vmcs12->भव_processor_id;
	 * evmcs->exception_biपंचांगap = vmcs12->exception_biपंचांगap;
	 * evmcs->vmcs_link_poपूर्णांकer = vmcs12->vmcs_link_poपूर्णांकer;
	 * evmcs->pin_based_vm_exec_control = vmcs12->pin_based_vm_exec_control;
	 * evmcs->vm_निकास_controls = vmcs12->vm_निकास_controls;
	 * evmcs->secondary_vm_exec_control = vmcs12->secondary_vm_exec_control;
	 * evmcs->page_fault_error_code_mask =
	 *		vmcs12->page_fault_error_code_mask;
	 * evmcs->page_fault_error_code_match =
	 *		vmcs12->page_fault_error_code_match;
	 * evmcs->cr3_target_count = vmcs12->cr3_target_count;
	 * evmcs->भव_apic_page_addr = vmcs12->भव_apic_page_addr;
	 * evmcs->tsc_offset = vmcs12->tsc_offset;
	 * evmcs->guest_ia32_debugctl = vmcs12->guest_ia32_debugctl;
	 * evmcs->cr0_guest_host_mask = vmcs12->cr0_guest_host_mask;
	 * evmcs->cr4_guest_host_mask = vmcs12->cr4_guest_host_mask;
	 * evmcs->cr0_पढ़ो_shaकरोw = vmcs12->cr0_पढ़ो_shaकरोw;
	 * evmcs->cr4_पढ़ो_shaकरोw = vmcs12->cr4_पढ़ो_shaकरोw;
	 * evmcs->vm_निकास_msr_store_count = vmcs12->vm_निकास_msr_store_count;
	 * evmcs->vm_निकास_msr_load_count = vmcs12->vm_निकास_msr_load_count;
	 * evmcs->vm_entry_msr_load_count = vmcs12->vm_entry_msr_load_count;
	 *
	 * Not present in काष्ठा vmcs12:
	 * evmcs->निकास_io_inकाष्ठाion_ecx = vmcs12->निकास_io_inकाष्ठाion_ecx;
	 * evmcs->निकास_io_inकाष्ठाion_esi = vmcs12->निकास_io_inकाष्ठाion_esi;
	 * evmcs->निकास_io_inकाष्ठाion_edi = vmcs12->निकास_io_inकाष्ठाion_edi;
	 * evmcs->निकास_io_inकाष्ठाion_eip = vmcs12->निकास_io_inकाष्ठाion_eip;
	 */

	evmcs->guest_es_selector = vmcs12->guest_es_selector;
	evmcs->guest_cs_selector = vmcs12->guest_cs_selector;
	evmcs->guest_ss_selector = vmcs12->guest_ss_selector;
	evmcs->guest_ds_selector = vmcs12->guest_ds_selector;
	evmcs->guest_fs_selector = vmcs12->guest_fs_selector;
	evmcs->guest_gs_selector = vmcs12->guest_gs_selector;
	evmcs->guest_ldtr_selector = vmcs12->guest_ldtr_selector;
	evmcs->guest_tr_selector = vmcs12->guest_tr_selector;

	evmcs->guest_es_limit = vmcs12->guest_es_limit;
	evmcs->guest_cs_limit = vmcs12->guest_cs_limit;
	evmcs->guest_ss_limit = vmcs12->guest_ss_limit;
	evmcs->guest_ds_limit = vmcs12->guest_ds_limit;
	evmcs->guest_fs_limit = vmcs12->guest_fs_limit;
	evmcs->guest_gs_limit = vmcs12->guest_gs_limit;
	evmcs->guest_ldtr_limit = vmcs12->guest_ldtr_limit;
	evmcs->guest_tr_limit = vmcs12->guest_tr_limit;
	evmcs->guest_gdtr_limit = vmcs12->guest_gdtr_limit;
	evmcs->guest_idtr_limit = vmcs12->guest_idtr_limit;

	evmcs->guest_es_ar_bytes = vmcs12->guest_es_ar_bytes;
	evmcs->guest_cs_ar_bytes = vmcs12->guest_cs_ar_bytes;
	evmcs->guest_ss_ar_bytes = vmcs12->guest_ss_ar_bytes;
	evmcs->guest_ds_ar_bytes = vmcs12->guest_ds_ar_bytes;
	evmcs->guest_fs_ar_bytes = vmcs12->guest_fs_ar_bytes;
	evmcs->guest_gs_ar_bytes = vmcs12->guest_gs_ar_bytes;
	evmcs->guest_ldtr_ar_bytes = vmcs12->guest_ldtr_ar_bytes;
	evmcs->guest_tr_ar_bytes = vmcs12->guest_tr_ar_bytes;

	evmcs->guest_es_base = vmcs12->guest_es_base;
	evmcs->guest_cs_base = vmcs12->guest_cs_base;
	evmcs->guest_ss_base = vmcs12->guest_ss_base;
	evmcs->guest_ds_base = vmcs12->guest_ds_base;
	evmcs->guest_fs_base = vmcs12->guest_fs_base;
	evmcs->guest_gs_base = vmcs12->guest_gs_base;
	evmcs->guest_ldtr_base = vmcs12->guest_ldtr_base;
	evmcs->guest_tr_base = vmcs12->guest_tr_base;
	evmcs->guest_gdtr_base = vmcs12->guest_gdtr_base;
	evmcs->guest_idtr_base = vmcs12->guest_idtr_base;

	evmcs->guest_ia32_pat = vmcs12->guest_ia32_pat;
	evmcs->guest_ia32_efer = vmcs12->guest_ia32_efer;

	evmcs->guest_pdptr0 = vmcs12->guest_pdptr0;
	evmcs->guest_pdptr1 = vmcs12->guest_pdptr1;
	evmcs->guest_pdptr2 = vmcs12->guest_pdptr2;
	evmcs->guest_pdptr3 = vmcs12->guest_pdptr3;

	evmcs->guest_pending_dbg_exceptions =
		vmcs12->guest_pending_dbg_exceptions;
	evmcs->guest_sysenter_esp = vmcs12->guest_sysenter_esp;
	evmcs->guest_sysenter_eip = vmcs12->guest_sysenter_eip;

	evmcs->guest_activity_state = vmcs12->guest_activity_state;
	evmcs->guest_sysenter_cs = vmcs12->guest_sysenter_cs;

	evmcs->guest_cr0 = vmcs12->guest_cr0;
	evmcs->guest_cr3 = vmcs12->guest_cr3;
	evmcs->guest_cr4 = vmcs12->guest_cr4;
	evmcs->guest_dr7 = vmcs12->guest_dr7;

	evmcs->guest_physical_address = vmcs12->guest_physical_address;

	evmcs->vm_inकाष्ठाion_error = vmcs12->vm_inकाष्ठाion_error;
	evmcs->vm_निकास_reason = vmcs12->vm_निकास_reason;
	evmcs->vm_निकास_पूर्णांकr_info = vmcs12->vm_निकास_पूर्णांकr_info;
	evmcs->vm_निकास_पूर्णांकr_error_code = vmcs12->vm_निकास_पूर्णांकr_error_code;
	evmcs->idt_vectoring_info_field = vmcs12->idt_vectoring_info_field;
	evmcs->idt_vectoring_error_code = vmcs12->idt_vectoring_error_code;
	evmcs->vm_निकास_inकाष्ठाion_len = vmcs12->vm_निकास_inकाष्ठाion_len;
	evmcs->vmx_inकाष्ठाion_info = vmcs12->vmx_inकाष्ठाion_info;

	evmcs->निकास_qualअगरication = vmcs12->निकास_qualअगरication;

	evmcs->guest_linear_address = vmcs12->guest_linear_address;
	evmcs->guest_rsp = vmcs12->guest_rsp;
	evmcs->guest_rflags = vmcs12->guest_rflags;

	evmcs->guest_पूर्णांकerruptibility_info =
		vmcs12->guest_पूर्णांकerruptibility_info;
	evmcs->cpu_based_vm_exec_control = vmcs12->cpu_based_vm_exec_control;
	evmcs->vm_entry_controls = vmcs12->vm_entry_controls;
	evmcs->vm_entry_पूर्णांकr_info_field = vmcs12->vm_entry_पूर्णांकr_info_field;
	evmcs->vm_entry_exception_error_code =
		vmcs12->vm_entry_exception_error_code;
	evmcs->vm_entry_inकाष्ठाion_len = vmcs12->vm_entry_inकाष्ठाion_len;

	evmcs->guest_rip = vmcs12->guest_rip;

	evmcs->guest_bndcfgs = vmcs12->guest_bndcfgs;

	वापस 0;
पूर्ण

/*
 * This is an equivalent of the nested hypervisor executing the vmptrld
 * inकाष्ठाion.
 */
अटल क्रमागत nested_evmptrld_status nested_vmx_handle_enlightened_vmptrld(
	काष्ठा kvm_vcpu *vcpu, bool from_launch)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	bool evmcs_gpa_changed = false;
	u64 evmcs_gpa;

	अगर (likely(!vmx->nested.enlightened_vmcs_enabled))
		वापस EVMPTRLD_DISABLED;

	अगर (!nested_enlightened_vmentry(vcpu, &evmcs_gpa))
		वापस EVMPTRLD_DISABLED;

	अगर (unlikely(!vmx->nested.hv_evmcs ||
		     evmcs_gpa != vmx->nested.hv_evmcs_vmptr)) अणु
		अगर (!vmx->nested.hv_evmcs)
			vmx->nested.current_vmptr = -1ull;

		nested_release_evmcs(vcpu);

		अगर (kvm_vcpu_map(vcpu, gpa_to_gfn(evmcs_gpa),
				 &vmx->nested.hv_evmcs_map))
			वापस EVMPTRLD_ERROR;

		vmx->nested.hv_evmcs = vmx->nested.hv_evmcs_map.hva;

		/*
		 * Currently, KVM only supports eVMCS version 1
		 * (== KVM_EVMCS_VERSION) and thus we expect guest to set this
		 * value to first u32 field of eVMCS which should specअगरy eVMCS
		 * VersionNumber.
		 *
		 * Guest should be aware of supported eVMCS versions by host by
		 * examining CPUID.0x4000000A.EAX[0:15]. Host userspace VMM is
		 * expected to set this CPUID leaf according to the value
		 * वापसed in vmcs_version from nested_enable_evmcs().
		 *
		 * However, it turns out that Microsoft Hyper-V fails to comply
		 * to their own invented पूर्णांकerface: When Hyper-V use eVMCS, it
		 * just sets first u32 field of eVMCS to revision_id specअगरied
		 * in MSR_IA32_VMX_BASIC. Instead of used eVMCS version number
		 * which is one of the supported versions specअगरied in
		 * CPUID.0x4000000A.EAX[0:15].
		 *
		 * To overcome Hyper-V bug, we accept here either a supported
		 * eVMCS version or VMCS12 revision_id as valid values क्रम first
		 * u32 field of eVMCS.
		 */
		अगर ((vmx->nested.hv_evmcs->revision_id != KVM_EVMCS_VERSION) &&
		    (vmx->nested.hv_evmcs->revision_id != VMCS12_REVISION)) अणु
			nested_release_evmcs(vcpu);
			वापस EVMPTRLD_VMFAIL;
		पूर्ण

		vmx->nested.dirty_vmcs12 = true;
		vmx->nested.hv_evmcs_vmptr = evmcs_gpa;

		evmcs_gpa_changed = true;
		/*
		 * Unlike normal vmcs12, enlightened vmcs12 is not fully
		 * reloaded from guest's memory (पढ़ो only fields, fields not
		 * present in काष्ठा hv_enlightened_vmcs, ...). Make sure there
		 * are no leftovers.
		 */
		अगर (from_launch) अणु
			काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
			स_रखो(vmcs12, 0, माप(*vmcs12));
			vmcs12->hdr.revision_id = VMCS12_REVISION;
		पूर्ण

	पूर्ण

	/*
	 * Clean fields data can't be used on VMLAUNCH and when we चयन
	 * between dअगरferent L2 guests as KVM keeps a single VMCS12 per L1.
	 */
	अगर (from_launch || evmcs_gpa_changed)
		vmx->nested.hv_evmcs->hv_clean_fields &=
			~HV_VMX_ENLIGHTENED_CLEAN_FIELD_ALL;

	वापस EVMPTRLD_SUCCEEDED;
पूर्ण

व्योम nested_sync_vmcs12_to_shaकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (vmx->nested.hv_evmcs) अणु
		copy_vmcs12_to_enlightened(vmx);
		/* All fields are clean */
		vmx->nested.hv_evmcs->hv_clean_fields |=
			HV_VMX_ENLIGHTENED_CLEAN_FIELD_ALL;
	पूर्ण अन्यथा अणु
		copy_vmcs12_to_shaकरोw(vmx);
	पूर्ण

	vmx->nested.need_vmcs12_to_shaकरोw_sync = false;
पूर्ण

अटल क्रमागत hrसमयr_restart vmx_preemption_समयr_fn(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा vcpu_vmx *vmx =
		container_of(समयr, काष्ठा vcpu_vmx, nested.preemption_समयr);

	vmx->nested.preemption_समयr_expired = true;
	kvm_make_request(KVM_REQ_EVENT, &vmx->vcpu);
	kvm_vcpu_kick(&vmx->vcpu);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल u64 vmx_calc_preemption_समयr_value(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);

	u64 l1_scaled_tsc = kvm_पढ़ो_l1_tsc(vcpu, rdtsc()) >>
			    VMX_MISC_EMULATED_PREEMPTION_TIMER_RATE;

	अगर (!vmx->nested.has_preemption_समयr_deadline) अणु
		vmx->nested.preemption_समयr_deadline =
			vmcs12->vmx_preemption_समयr_value + l1_scaled_tsc;
		vmx->nested.has_preemption_समयr_deadline = true;
	पूर्ण
	वापस vmx->nested.preemption_समयr_deadline - l1_scaled_tsc;
पूर्ण

अटल व्योम vmx_start_preemption_समयr(काष्ठा kvm_vcpu *vcpu,
					u64 preemption_समयout)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * A समयr value of zero is architecturally guaranteed to cause
	 * a VMExit prior to executing any inकाष्ठाions in the guest.
	 */
	अगर (preemption_समयout == 0) अणु
		vmx_preemption_समयr_fn(&vmx->nested.preemption_समयr);
		वापस;
	पूर्ण

	अगर (vcpu->arch.भव_tsc_khz == 0)
		वापस;

	preemption_समयout <<= VMX_MISC_EMULATED_PREEMPTION_TIMER_RATE;
	preemption_समयout *= 1000000;
	करो_भाग(preemption_समयout, vcpu->arch.भव_tsc_khz);
	hrसमयr_start(&vmx->nested.preemption_समयr,
		      kसमय_add_ns(kसमय_get(), preemption_समयout),
		      HRTIMER_MODE_ABS_PINNED);
पूर्ण

अटल u64 nested_vmx_calc_efer(काष्ठा vcpu_vmx *vmx, काष्ठा vmcs12 *vmcs12)
अणु
	अगर (vmx->nested.nested_run_pending &&
	    (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_IA32_EFER))
		वापस vmcs12->guest_ia32_efer;
	अन्यथा अगर (vmcs12->vm_entry_controls & VM_ENTRY_IA32E_MODE)
		वापस vmx->vcpu.arch.efer | (EFER_LMA | EFER_LME);
	अन्यथा
		वापस vmx->vcpu.arch.efer & ~(EFER_LMA | EFER_LME);
पूर्ण

अटल व्योम prepare_vmcs02_स्थिरant_state(काष्ठा vcpu_vmx *vmx)
अणु
	/*
	 * If vmcs02 hasn't been initialized, set the स्थिरant vmcs02 state
	 * according to L0's settings (vmcs12 is irrelevant here).  Host
	 * fields that come from L0 and are not स्थिरant, e.g. HOST_CR3,
	 * will be set as needed prior to VMLAUNCH/VMRESUME.
	 */
	अगर (vmx->nested.vmcs02_initialized)
		वापस;
	vmx->nested.vmcs02_initialized = true;

	/*
	 * We करोn't care what the EPTP value is we just need to guarantee
	 * it's valid so we don't get a false positive when करोing early
	 * consistency checks.
	 */
	अगर (enable_ept && nested_early_check)
		vmcs_ग_लिखो64(EPT_POINTER,
			     स्थिरruct_eptp(&vmx->vcpu, 0, PT64_ROOT_4LEVEL));

	/* All VMFUNCs are currently emulated through L0 vmनिकासs.  */
	अगर (cpu_has_vmx_vmfunc())
		vmcs_ग_लिखो64(VM_FUNCTION_CONTROL, 0);

	अगर (cpu_has_vmx_posted_पूर्णांकr())
		vmcs_ग_लिखो16(POSTED_INTR_NV, POSTED_INTR_NESTED_VECTOR);

	अगर (cpu_has_vmx_msr_biपंचांगap())
		vmcs_ग_लिखो64(MSR_BITMAP, __pa(vmx->nested.vmcs02.msr_biपंचांगap));

	/*
	 * PML is emulated क्रम L2, but never enabled in hardware as the MMU
	 * handles A/D emulation.  Disabling PML क्रम L2 also aव्योमs having to
	 * deal with filtering out L2 GPAs from the buffer.
	 */
	अगर (enable_pml) अणु
		vmcs_ग_लिखो64(PML_ADDRESS, 0);
		vmcs_ग_लिखो16(GUEST_PML_INDEX, -1);
	पूर्ण

	अगर (cpu_has_vmx_encls_vmनिकास())
		vmcs_ग_लिखो64(ENCLS_EXITING_BITMAP, -1ull);

	/*
	 * Set the MSR load/store lists to match L0's settings.  Only the
	 * addresses are स्थिरant (क्रम vmcs02), the counts can change based
	 * on L2's behavior, e.g. चयनing to/from दीर्घ mode.
	 */
	vmcs_ग_लिखो64(VM_EXIT_MSR_STORE_ADDR, __pa(vmx->msr_स्वतःstore.guest.val));
	vmcs_ग_लिखो64(VM_EXIT_MSR_LOAD_ADDR, __pa(vmx->msr_स्वतःload.host.val));
	vmcs_ग_लिखो64(VM_ENTRY_MSR_LOAD_ADDR, __pa(vmx->msr_स्वतःload.guest.val));

	vmx_set_स्थिरant_host_state(vmx);
पूर्ण

अटल व्योम prepare_vmcs02_early_rare(काष्ठा vcpu_vmx *vmx,
				      काष्ठा vmcs12 *vmcs12)
अणु
	prepare_vmcs02_स्थिरant_state(vmx);

	vmcs_ग_लिखो64(VMCS_LINK_POINTER, -1ull);

	अगर (enable_vpid) अणु
		अगर (nested_cpu_has_vpid(vmcs12) && vmx->nested.vpid02)
			vmcs_ग_लिखो16(VIRTUAL_PROCESSOR_ID, vmx->nested.vpid02);
		अन्यथा
			vmcs_ग_लिखो16(VIRTUAL_PROCESSOR_ID, vmx->vpid);
	पूर्ण
पूर्ण

अटल व्योम prepare_vmcs02_early(काष्ठा vcpu_vmx *vmx, काष्ठा vmcs12 *vmcs12)
अणु
	u32 exec_control;
	u64 guest_efer = nested_vmx_calc_efer(vmx, vmcs12);

	अगर (vmx->nested.dirty_vmcs12 || vmx->nested.hv_evmcs)
		prepare_vmcs02_early_rare(vmx, vmcs12);

	/*
	 * PIN CONTROLS
	 */
	exec_control = vmx_pin_based_exec_ctrl(vmx);
	exec_control |= (vmcs12->pin_based_vm_exec_control &
			 ~PIN_BASED_VMX_PREEMPTION_TIMER);

	/* Posted पूर्णांकerrupts setting is only taken from vmcs12.  */
	अगर (nested_cpu_has_posted_पूर्णांकr(vmcs12)) अणु
		vmx->nested.posted_पूर्णांकr_nv = vmcs12->posted_पूर्णांकr_nv;
		vmx->nested.pi_pending = false;
	पूर्ण अन्यथा अणु
		exec_control &= ~PIN_BASED_POSTED_INTR;
	पूर्ण
	pin_controls_set(vmx, exec_control);

	/*
	 * EXEC CONTROLS
	 */
	exec_control = vmx_exec_control(vmx); /* L0's desires */
	exec_control &= ~CPU_BASED_INTR_WINDOW_EXITING;
	exec_control &= ~CPU_BASED_NMI_WINDOW_EXITING;
	exec_control &= ~CPU_BASED_TPR_SHADOW;
	exec_control |= vmcs12->cpu_based_vm_exec_control;

	vmx->nested.l1_tpr_threshold = -1;
	अगर (exec_control & CPU_BASED_TPR_SHADOW)
		vmcs_ग_लिखो32(TPR_THRESHOLD, vmcs12->tpr_threshold);
#अगर_घोषित CONFIG_X86_64
	अन्यथा
		exec_control |= CPU_BASED_CR8_LOAD_EXITING |
				CPU_BASED_CR8_STORE_EXITING;
#पूर्ण_अगर

	/*
	 * A vmनिकास (to either L1 hypervisor or L0 userspace) is always needed
	 * क्रम I/O port accesses.
	 */
	exec_control |= CPU_BASED_UNCOND_IO_EXITING;
	exec_control &= ~CPU_BASED_USE_IO_BITMAPS;

	/*
	 * This bit will be computed in nested_get_vmcs12_pages, because
	 * we करो not have access to L1's MSR biपंचांगap yet.  For now, keep
	 * the same bit as beक्रमe, hoping to aव्योम multiple VMWRITEs that
	 * only set/clear this bit.
	 */
	exec_control &= ~CPU_BASED_USE_MSR_BITMAPS;
	exec_control |= exec_controls_get(vmx) & CPU_BASED_USE_MSR_BITMAPS;

	exec_controls_set(vmx, exec_control);

	/*
	 * SECONDARY EXEC CONTROLS
	 */
	अगर (cpu_has_secondary_exec_ctrls()) अणु
		exec_control = vmx->secondary_exec_control;

		/* Take the following fields only from vmcs12 */
		exec_control &= ~(SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES |
				  SECONDARY_EXEC_ENABLE_INVPCID |
				  SECONDARY_EXEC_ENABLE_RDTSCP |
				  SECONDARY_EXEC_XSAVES |
				  SECONDARY_EXEC_ENABLE_USR_WAIT_PAUSE |
				  SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY |
				  SECONDARY_EXEC_APIC_REGISTER_VIRT |
				  SECONDARY_EXEC_ENABLE_VMFUNC);
		अगर (nested_cpu_has(vmcs12,
				   CPU_BASED_ACTIVATE_SECONDARY_CONTROLS))
			exec_control |= vmcs12->secondary_vm_exec_control;

		/* PML is emulated and never enabled in hardware क्रम L2. */
		exec_control &= ~SECONDARY_EXEC_ENABLE_PML;

		/* VMCS shaकरोwing क्रम L2 is emulated क्रम now */
		exec_control &= ~SECONDARY_EXEC_SHADOW_VMCS;

		/*
		 * Preset *DT निकासing when emulating UMIP, so that vmx_set_cr4()
		 * will not have to reग_लिखो the controls just क्रम this bit.
		 */
		अगर (!boot_cpu_has(X86_FEATURE_UMIP) && vmx_umip_emulated() &&
		    (vmcs12->guest_cr4 & X86_CR4_UMIP))
			exec_control |= SECONDARY_EXEC_DESC;

		अगर (exec_control & SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY)
			vmcs_ग_लिखो16(GUEST_INTR_STATUS,
				vmcs12->guest_पूर्णांकr_status);

		अगर (!nested_cpu_has2(vmcs12, SECONDARY_EXEC_UNRESTRICTED_GUEST))
		    exec_control &= ~SECONDARY_EXEC_UNRESTRICTED_GUEST;

		अगर (exec_control & SECONDARY_EXEC_ENCLS_EXITING)
			vmx_ग_लिखो_encls_biपंचांगap(&vmx->vcpu, vmcs12);

		secondary_exec_controls_set(vmx, exec_control);
	पूर्ण

	/*
	 * ENTRY CONTROLS
	 *
	 * vmcs12's VM_अणुENTRY,EXITपूर्ण_LOAD_IA32_EFER and VM_ENTRY_IA32E_MODE
	 * are emulated by vmx_set_efer() in prepare_vmcs02(), but speculate
	 * on the related bits (अगर supported by the CPU) in the hope that
	 * we can aव्योम VMWrites during vmx_set_efer().
	 */
	exec_control = (vmcs12->vm_entry_controls | vmx_vmentry_ctrl()) &
			~VM_ENTRY_IA32E_MODE & ~VM_ENTRY_LOAD_IA32_EFER;
	अगर (cpu_has_load_ia32_efer()) अणु
		अगर (guest_efer & EFER_LMA)
			exec_control |= VM_ENTRY_IA32E_MODE;
		अगर (guest_efer != host_efer)
			exec_control |= VM_ENTRY_LOAD_IA32_EFER;
	पूर्ण
	vm_entry_controls_set(vmx, exec_control);

	/*
	 * EXIT CONTROLS
	 *
	 * L2->L1 निकास controls are emulated - the hardware निकास is to L0 so
	 * we should use its निकास controls. Note that VM_EXIT_LOAD_IA32_EFER
	 * bits may be modअगरied by vmx_set_efer() in prepare_vmcs02().
	 */
	exec_control = vmx_vmनिकास_ctrl();
	अगर (cpu_has_load_ia32_efer() && guest_efer != host_efer)
		exec_control |= VM_EXIT_LOAD_IA32_EFER;
	vm_निकास_controls_set(vmx, exec_control);

	/*
	 * Interrupt/Exception Fields
	 */
	अगर (vmx->nested.nested_run_pending) अणु
		vmcs_ग_लिखो32(VM_ENTRY_INTR_INFO_FIELD,
			     vmcs12->vm_entry_पूर्णांकr_info_field);
		vmcs_ग_लिखो32(VM_ENTRY_EXCEPTION_ERROR_CODE,
			     vmcs12->vm_entry_exception_error_code);
		vmcs_ग_लिखो32(VM_ENTRY_INSTRUCTION_LEN,
			     vmcs12->vm_entry_inकाष्ठाion_len);
		vmcs_ग_लिखो32(GUEST_INTERRUPTIBILITY_INFO,
			     vmcs12->guest_पूर्णांकerruptibility_info);
		vmx->loaded_vmcs->nmi_known_unmasked =
			!(vmcs12->guest_पूर्णांकerruptibility_info & GUEST_INTR_STATE_NMI);
	पूर्ण अन्यथा अणु
		vmcs_ग_लिखो32(VM_ENTRY_INTR_INFO_FIELD, 0);
	पूर्ण
पूर्ण

अटल व्योम prepare_vmcs02_rare(काष्ठा vcpu_vmx *vmx, काष्ठा vmcs12 *vmcs12)
अणु
	काष्ठा hv_enlightened_vmcs *hv_evmcs = vmx->nested.hv_evmcs;

	अगर (!hv_evmcs || !(hv_evmcs->hv_clean_fields &
			   HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP2)) अणु
		vmcs_ग_लिखो16(GUEST_ES_SELECTOR, vmcs12->guest_es_selector);
		vmcs_ग_लिखो16(GUEST_CS_SELECTOR, vmcs12->guest_cs_selector);
		vmcs_ग_लिखो16(GUEST_SS_SELECTOR, vmcs12->guest_ss_selector);
		vmcs_ग_लिखो16(GUEST_DS_SELECTOR, vmcs12->guest_ds_selector);
		vmcs_ग_लिखो16(GUEST_FS_SELECTOR, vmcs12->guest_fs_selector);
		vmcs_ग_लिखो16(GUEST_GS_SELECTOR, vmcs12->guest_gs_selector);
		vmcs_ग_लिखो16(GUEST_LDTR_SELECTOR, vmcs12->guest_ldtr_selector);
		vmcs_ग_लिखो16(GUEST_TR_SELECTOR, vmcs12->guest_tr_selector);
		vmcs_ग_लिखो32(GUEST_ES_LIMIT, vmcs12->guest_es_limit);
		vmcs_ग_लिखो32(GUEST_CS_LIMIT, vmcs12->guest_cs_limit);
		vmcs_ग_लिखो32(GUEST_SS_LIMIT, vmcs12->guest_ss_limit);
		vmcs_ग_लिखो32(GUEST_DS_LIMIT, vmcs12->guest_ds_limit);
		vmcs_ग_लिखो32(GUEST_FS_LIMIT, vmcs12->guest_fs_limit);
		vmcs_ग_लिखो32(GUEST_GS_LIMIT, vmcs12->guest_gs_limit);
		vmcs_ग_लिखो32(GUEST_LDTR_LIMIT, vmcs12->guest_ldtr_limit);
		vmcs_ग_लिखो32(GUEST_TR_LIMIT, vmcs12->guest_tr_limit);
		vmcs_ग_लिखो32(GUEST_GDTR_LIMIT, vmcs12->guest_gdtr_limit);
		vmcs_ग_लिखो32(GUEST_IDTR_LIMIT, vmcs12->guest_idtr_limit);
		vmcs_ग_लिखो32(GUEST_CS_AR_BYTES, vmcs12->guest_cs_ar_bytes);
		vmcs_ग_लिखो32(GUEST_SS_AR_BYTES, vmcs12->guest_ss_ar_bytes);
		vmcs_ग_लिखो32(GUEST_ES_AR_BYTES, vmcs12->guest_es_ar_bytes);
		vmcs_ग_लिखो32(GUEST_DS_AR_BYTES, vmcs12->guest_ds_ar_bytes);
		vmcs_ग_लिखो32(GUEST_FS_AR_BYTES, vmcs12->guest_fs_ar_bytes);
		vmcs_ग_लिखो32(GUEST_GS_AR_BYTES, vmcs12->guest_gs_ar_bytes);
		vmcs_ग_लिखो32(GUEST_LDTR_AR_BYTES, vmcs12->guest_ldtr_ar_bytes);
		vmcs_ग_लिखो32(GUEST_TR_AR_BYTES, vmcs12->guest_tr_ar_bytes);
		vmcs_ग_लिखोl(GUEST_ES_BASE, vmcs12->guest_es_base);
		vmcs_ग_लिखोl(GUEST_CS_BASE, vmcs12->guest_cs_base);
		vmcs_ग_लिखोl(GUEST_SS_BASE, vmcs12->guest_ss_base);
		vmcs_ग_लिखोl(GUEST_DS_BASE, vmcs12->guest_ds_base);
		vmcs_ग_लिखोl(GUEST_FS_BASE, vmcs12->guest_fs_base);
		vmcs_ग_लिखोl(GUEST_GS_BASE, vmcs12->guest_gs_base);
		vmcs_ग_लिखोl(GUEST_LDTR_BASE, vmcs12->guest_ldtr_base);
		vmcs_ग_लिखोl(GUEST_TR_BASE, vmcs12->guest_tr_base);
		vmcs_ग_लिखोl(GUEST_GDTR_BASE, vmcs12->guest_gdtr_base);
		vmcs_ग_लिखोl(GUEST_IDTR_BASE, vmcs12->guest_idtr_base);

		vmx->segment_cache.biपंचांगask = 0;
	पूर्ण

	अगर (!hv_evmcs || !(hv_evmcs->hv_clean_fields &
			   HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP1)) अणु
		vmcs_ग_लिखो32(GUEST_SYSENTER_CS, vmcs12->guest_sysenter_cs);
		vmcs_ग_लिखोl(GUEST_PENDING_DBG_EXCEPTIONS,
			    vmcs12->guest_pending_dbg_exceptions);
		vmcs_ग_लिखोl(GUEST_SYSENTER_ESP, vmcs12->guest_sysenter_esp);
		vmcs_ग_लिखोl(GUEST_SYSENTER_EIP, vmcs12->guest_sysenter_eip);

		/*
		 * L1 may access the L2's PDPTR, so save them to स्थिरruct
		 * vmcs12
		 */
		अगर (enable_ept) अणु
			vmcs_ग_लिखो64(GUEST_PDPTR0, vmcs12->guest_pdptr0);
			vmcs_ग_लिखो64(GUEST_PDPTR1, vmcs12->guest_pdptr1);
			vmcs_ग_लिखो64(GUEST_PDPTR2, vmcs12->guest_pdptr2);
			vmcs_ग_लिखो64(GUEST_PDPTR3, vmcs12->guest_pdptr3);
		पूर्ण

		अगर (kvm_mpx_supported() && vmx->nested.nested_run_pending &&
		    (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_BNDCFGS))
			vmcs_ग_लिखो64(GUEST_BNDCFGS, vmcs12->guest_bndcfgs);
	पूर्ण

	अगर (nested_cpu_has_xsaves(vmcs12))
		vmcs_ग_लिखो64(XSS_EXIT_BITMAP, vmcs12->xss_निकास_biपंचांगap);

	/*
	 * Whether page-faults are trapped is determined by a combination of
	 * 3 settings: PFEC_MASK, PFEC_MATCH and EXCEPTION_BITMAP.PF.  If L0
	 * करोesn't care about page faults then we should set all of these to
	 * L1's desires. However, अगर L0 करोes care about (some) page faults, it
	 * is not easy (अगर at all possible?) to merge L0 and L1's desires, we
	 * simply ask to निकास on each and every L2 page fault. This is करोne by
	 * setting MASK=MATCH=0 and (see below) EB.PF=1.
	 * Note that below we करोn't need special code to set EB.PF beyond the
	 * "or"ing of the EB of vmcs01 and vmcs12, because when enable_ept,
	 * vmcs01's EB.PF is 0 so the "or" will take vmcs12's value, and when
	 * !enable_ept, EB.PF is 1, so the "or" will always be 1.
	 */
	अगर (vmx_need_pf_पूर्णांकercept(&vmx->vcpu)) अणु
		/*
		 * TODO: अगर both L0 and L1 need the same MASK and MATCH,
		 * go ahead and use it?
		 */
		vmcs_ग_लिखो32(PAGE_FAULT_ERROR_CODE_MASK, 0);
		vmcs_ग_लिखो32(PAGE_FAULT_ERROR_CODE_MATCH, 0);
	पूर्ण अन्यथा अणु
		vmcs_ग_लिखो32(PAGE_FAULT_ERROR_CODE_MASK, vmcs12->page_fault_error_code_mask);
		vmcs_ग_लिखो32(PAGE_FAULT_ERROR_CODE_MATCH, vmcs12->page_fault_error_code_match);
	पूर्ण

	अगर (cpu_has_vmx_apicv()) अणु
		vmcs_ग_लिखो64(EOI_EXIT_BITMAP0, vmcs12->eoi_निकास_biपंचांगap0);
		vmcs_ग_लिखो64(EOI_EXIT_BITMAP1, vmcs12->eoi_निकास_biपंचांगap1);
		vmcs_ग_लिखो64(EOI_EXIT_BITMAP2, vmcs12->eoi_निकास_biपंचांगap2);
		vmcs_ग_लिखो64(EOI_EXIT_BITMAP3, vmcs12->eoi_निकास_biपंचांगap3);
	पूर्ण

	/*
	 * Make sure the msr_स्वतःstore list is up to date beक्रमe we set the
	 * count in the vmcs02.
	 */
	prepare_vmx_msr_स्वतःstore_list(&vmx->vcpu, MSR_IA32_TSC);

	vmcs_ग_लिखो32(VM_EXIT_MSR_STORE_COUNT, vmx->msr_स्वतःstore.guest.nr);
	vmcs_ग_लिखो32(VM_EXIT_MSR_LOAD_COUNT, vmx->msr_स्वतःload.host.nr);
	vmcs_ग_लिखो32(VM_ENTRY_MSR_LOAD_COUNT, vmx->msr_स्वतःload.guest.nr);

	set_cr4_guest_host_mask(vmx);
पूर्ण

/*
 * prepare_vmcs02 is called when the L1 guest hypervisor runs its nested
 * L2 guest. L1 has a vmcs क्रम L2 (vmcs12), and this function "merges" it
 * with L0's requirements क्रम its guest (a.k.a. vmcs01), so we can run the L2
 * guest in a way that will both be appropriate to L1's requests, and our
 * needs. In addition to modअगरying the active vmcs (which is vmcs02), this
 * function also has additional necessary side-effects, like setting various
 * vcpu->arch fields.
 * Returns 0 on success, 1 on failure. Invalid state निकास qualअगरication code
 * is asचिन्हित to entry_failure_code on failure.
 */
अटल पूर्णांक prepare_vmcs02(काष्ठा kvm_vcpu *vcpu, काष्ठा vmcs12 *vmcs12,
			  क्रमागत vm_entry_failure_code *entry_failure_code)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा hv_enlightened_vmcs *hv_evmcs = vmx->nested.hv_evmcs;
	bool load_guest_pdptrs_vmcs12 = false;

	अगर (vmx->nested.dirty_vmcs12 || hv_evmcs) अणु
		prepare_vmcs02_rare(vmx, vmcs12);
		vmx->nested.dirty_vmcs12 = false;

		load_guest_pdptrs_vmcs12 = !hv_evmcs ||
			!(hv_evmcs->hv_clean_fields &
			  HV_VMX_ENLIGHTENED_CLEAN_FIELD_GUEST_GRP1);
	पूर्ण

	अगर (vmx->nested.nested_run_pending &&
	    (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_DEBUG_CONTROLS)) अणु
		kvm_set_dr(vcpu, 7, vmcs12->guest_dr7);
		vmcs_ग_लिखो64(GUEST_IA32_DEBUGCTL, vmcs12->guest_ia32_debugctl);
	पूर्ण अन्यथा अणु
		kvm_set_dr(vcpu, 7, vcpu->arch.dr7);
		vmcs_ग_लिखो64(GUEST_IA32_DEBUGCTL, vmx->nested.vmcs01_debugctl);
	पूर्ण
	अगर (kvm_mpx_supported() && (!vmx->nested.nested_run_pending ||
	    !(vmcs12->vm_entry_controls & VM_ENTRY_LOAD_BNDCFGS)))
		vmcs_ग_लिखो64(GUEST_BNDCFGS, vmx->nested.vmcs01_guest_bndcfgs);
	vmx_set_rflags(vcpu, vmcs12->guest_rflags);

	/* EXCEPTION_BITMAP and CR0_GUEST_HOST_MASK should basically be the
	 * bitwise-or of what L1 wants to trap क्रम L2, and what we want to
	 * trap. Note that CR0.TS also needs updating - we करो this later.
	 */
	vmx_update_exception_biपंचांगap(vcpu);
	vcpu->arch.cr0_guest_owned_bits &= ~vmcs12->cr0_guest_host_mask;
	vmcs_ग_लिखोl(CR0_GUEST_HOST_MASK, ~vcpu->arch.cr0_guest_owned_bits);

	अगर (vmx->nested.nested_run_pending &&
	    (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_IA32_PAT)) अणु
		vmcs_ग_लिखो64(GUEST_IA32_PAT, vmcs12->guest_ia32_pat);
		vcpu->arch.pat = vmcs12->guest_ia32_pat;
	पूर्ण अन्यथा अगर (vmcs_config.vmentry_ctrl & VM_ENTRY_LOAD_IA32_PAT) अणु
		vmcs_ग_लिखो64(GUEST_IA32_PAT, vmx->vcpu.arch.pat);
	पूर्ण

	vmcs_ग_लिखो64(TSC_OFFSET, vcpu->arch.tsc_offset);

	अगर (kvm_has_tsc_control)
		decache_tsc_multiplier(vmx);

	nested_vmx_transition_tlb_flush(vcpu, vmcs12, true);

	अगर (nested_cpu_has_ept(vmcs12))
		nested_ept_init_mmu_context(vcpu);

	/*
	 * This sets GUEST_CR0 to vmcs12->guest_cr0, possibly modअगरying those
	 * bits which we consider mandatory enabled.
	 * The CR0_READ_SHADOW is what L2 should have expected to पढ़ो given
	 * the specअगरications by L1; It's not enough to take
	 * vmcs12->cr0_पढ़ो_shaकरोw because on our cr0_guest_host_mask we we
	 * have more bits than L1 expected.
	 */
	vmx_set_cr0(vcpu, vmcs12->guest_cr0);
	vmcs_ग_लिखोl(CR0_READ_SHADOW, nested_पढ़ो_cr0(vmcs12));

	vmx_set_cr4(vcpu, vmcs12->guest_cr4);
	vmcs_ग_लिखोl(CR4_READ_SHADOW, nested_पढ़ो_cr4(vmcs12));

	vcpu->arch.efer = nested_vmx_calc_efer(vmx, vmcs12);
	/* Note: may modअगरy VM_ENTRY/EXIT_CONTROLS and GUEST/HOST_IA32_EFER */
	vmx_set_efer(vcpu, vcpu->arch.efer);

	/*
	 * Guest state is invalid and unrestricted guest is disabled,
	 * which means L1 attempted VMEntry to L2 with invalid state.
	 * Fail the VMEntry.
	 */
	अगर (CC(!vmx_guest_state_valid(vcpu))) अणु
		*entry_failure_code = ENTRY_FAIL_DEFAULT;
		वापस -EINVAL;
	पूर्ण

	/* Shaकरोw page tables on either EPT or shaकरोw page tables. */
	अगर (nested_vmx_load_cr3(vcpu, vmcs12->guest_cr3, nested_cpu_has_ept(vmcs12),
				entry_failure_code))
		वापस -EINVAL;

	/*
	 * Immediately ग_लिखो vmcs02.GUEST_CR3.  It will be propagated to vmcs12
	 * on nested VM-Exit, which can occur without actually running L2 and
	 * thus without hitting vmx_load_mmu_pgd(), e.g. अगर L1 is entering L2 with
	 * vmcs12.GUEST_ACTIVITYSTATE=HLT, in which हाल KVM will पूर्णांकercept the
	 * transition to HLT instead of running L2.
	 */
	अगर (enable_ept)
		vmcs_ग_लिखोl(GUEST_CR3, vmcs12->guest_cr3);

	/* Late preparation of GUEST_PDPTRs now that EFER and CRs are set. */
	अगर (load_guest_pdptrs_vmcs12 && nested_cpu_has_ept(vmcs12) &&
	    is_pae_paging(vcpu)) अणु
		vmcs_ग_लिखो64(GUEST_PDPTR0, vmcs12->guest_pdptr0);
		vmcs_ग_लिखो64(GUEST_PDPTR1, vmcs12->guest_pdptr1);
		vmcs_ग_लिखो64(GUEST_PDPTR2, vmcs12->guest_pdptr2);
		vmcs_ग_लिखो64(GUEST_PDPTR3, vmcs12->guest_pdptr3);
	पूर्ण

	अगर (!enable_ept)
		vcpu->arch.walk_mmu->inject_page_fault = vmx_inject_page_fault_nested;

	अगर ((vmcs12->vm_entry_controls & VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL) &&
	    WARN_ON_ONCE(kvm_set_msr(vcpu, MSR_CORE_PERF_GLOBAL_CTRL,
				     vmcs12->guest_ia32_perf_global_ctrl)))
		वापस -EINVAL;

	kvm_rsp_ग_लिखो(vcpu, vmcs12->guest_rsp);
	kvm_rip_ग_लिखो(vcpu, vmcs12->guest_rip);
	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_nmi_controls(काष्ठा vmcs12 *vmcs12)
अणु
	अगर (CC(!nested_cpu_has_nmi_निकासing(vmcs12) &&
	       nested_cpu_has_भव_nmis(vmcs12)))
		वापस -EINVAL;

	अगर (CC(!nested_cpu_has_भव_nmis(vmcs12) &&
	       nested_cpu_has(vmcs12, CPU_BASED_NMI_WINDOW_EXITING)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल bool nested_vmx_check_eptp(काष्ठा kvm_vcpu *vcpu, u64 new_eptp)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	/* Check क्रम memory type validity */
	चयन (new_eptp & VMX_EPTP_MT_MASK) अणु
	हाल VMX_EPTP_MT_UC:
		अगर (CC(!(vmx->nested.msrs.ept_caps & VMX_EPTP_UC_BIT)))
			वापस false;
		अवरोध;
	हाल VMX_EPTP_MT_WB:
		अगर (CC(!(vmx->nested.msrs.ept_caps & VMX_EPTP_WB_BIT)))
			वापस false;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	/* Page-walk levels validity. */
	चयन (new_eptp & VMX_EPTP_PWL_MASK) अणु
	हाल VMX_EPTP_PWL_5:
		अगर (CC(!(vmx->nested.msrs.ept_caps & VMX_EPT_PAGE_WALK_5_BIT)))
			वापस false;
		अवरोध;
	हाल VMX_EPTP_PWL_4:
		अगर (CC(!(vmx->nested.msrs.ept_caps & VMX_EPT_PAGE_WALK_4_BIT)))
			वापस false;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	/* Reserved bits should not be set */
	अगर (CC(kvm_vcpu_is_illegal_gpa(vcpu, new_eptp) || ((new_eptp >> 7) & 0x1f)))
		वापस false;

	/* AD, अगर set, should be supported */
	अगर (new_eptp & VMX_EPTP_AD_ENABLE_BIT) अणु
		अगर (CC(!(vmx->nested.msrs.ept_caps & VMX_EPT_AD_BIT)))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Checks related to VM-Execution Control Fields
 */
अटल पूर्णांक nested_check_vm_execution_controls(काष्ठा kvm_vcpu *vcpu,
                                              काष्ठा vmcs12 *vmcs12)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (CC(!vmx_control_verअगरy(vmcs12->pin_based_vm_exec_control,
				   vmx->nested.msrs.pinbased_ctls_low,
				   vmx->nested.msrs.pinbased_ctls_high)) ||
	    CC(!vmx_control_verअगरy(vmcs12->cpu_based_vm_exec_control,
				   vmx->nested.msrs.procbased_ctls_low,
				   vmx->nested.msrs.procbased_ctls_high)))
		वापस -EINVAL;

	अगर (nested_cpu_has(vmcs12, CPU_BASED_ACTIVATE_SECONDARY_CONTROLS) &&
	    CC(!vmx_control_verअगरy(vmcs12->secondary_vm_exec_control,
				   vmx->nested.msrs.secondary_ctls_low,
				   vmx->nested.msrs.secondary_ctls_high)))
		वापस -EINVAL;

	अगर (CC(vmcs12->cr3_target_count > nested_cpu_vmx_misc_cr3_count(vcpu)) ||
	    nested_vmx_check_io_biपंचांगap_controls(vcpu, vmcs12) ||
	    nested_vmx_check_msr_biपंचांगap_controls(vcpu, vmcs12) ||
	    nested_vmx_check_tpr_shaकरोw_controls(vcpu, vmcs12) ||
	    nested_vmx_check_apic_access_controls(vcpu, vmcs12) ||
	    nested_vmx_check_apicv_controls(vcpu, vmcs12) ||
	    nested_vmx_check_nmi_controls(vmcs12) ||
	    nested_vmx_check_pml_controls(vcpu, vmcs12) ||
	    nested_vmx_check_unrestricted_guest_controls(vcpu, vmcs12) ||
	    nested_vmx_check_mode_based_ept_exec_controls(vcpu, vmcs12) ||
	    nested_vmx_check_shaकरोw_vmcs_controls(vcpu, vmcs12) ||
	    CC(nested_cpu_has_vpid(vmcs12) && !vmcs12->भव_processor_id))
		वापस -EINVAL;

	अगर (!nested_cpu_has_preemption_समयr(vmcs12) &&
	    nested_cpu_has_save_preemption_समयr(vmcs12))
		वापस -EINVAL;

	अगर (nested_cpu_has_ept(vmcs12) &&
	    CC(!nested_vmx_check_eptp(vcpu, vmcs12->ept_poपूर्णांकer)))
		वापस -EINVAL;

	अगर (nested_cpu_has_vmfunc(vmcs12)) अणु
		अगर (CC(vmcs12->vm_function_control &
		       ~vmx->nested.msrs.vmfunc_controls))
			वापस -EINVAL;

		अगर (nested_cpu_has_eptp_चयनing(vmcs12)) अणु
			अगर (CC(!nested_cpu_has_ept(vmcs12)) ||
			    CC(!page_address_valid(vcpu, vmcs12->eptp_list_address)))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Checks related to VM-Exit Control Fields
 */
अटल पूर्णांक nested_check_vm_निकास_controls(काष्ठा kvm_vcpu *vcpu,
                                         काष्ठा vmcs12 *vmcs12)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (CC(!vmx_control_verअगरy(vmcs12->vm_निकास_controls,
				    vmx->nested.msrs.निकास_ctls_low,
				    vmx->nested.msrs.निकास_ctls_high)) ||
	    CC(nested_vmx_check_निकास_msr_चयन_controls(vcpu, vmcs12)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Checks related to VM-Entry Control Fields
 */
अटल पूर्णांक nested_check_vm_entry_controls(काष्ठा kvm_vcpu *vcpu,
					  काष्ठा vmcs12 *vmcs12)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (CC(!vmx_control_verअगरy(vmcs12->vm_entry_controls,
				    vmx->nested.msrs.entry_ctls_low,
				    vmx->nested.msrs.entry_ctls_high)))
		वापस -EINVAL;

	/*
	 * From the Intel SDM, volume 3:
	 * Fields relevant to VM-entry event injection must be set properly.
	 * These fields are the VM-entry पूर्णांकerruption-inक्रमmation field, the
	 * VM-entry exception error code, and the VM-entry inकाष्ठाion length.
	 */
	अगर (vmcs12->vm_entry_पूर्णांकr_info_field & INTR_INFO_VALID_MASK) अणु
		u32 पूर्णांकr_info = vmcs12->vm_entry_पूर्णांकr_info_field;
		u8 vector = पूर्णांकr_info & INTR_INFO_VECTOR_MASK;
		u32 पूर्णांकr_type = पूर्णांकr_info & INTR_INFO_INTR_TYPE_MASK;
		bool has_error_code = पूर्णांकr_info & INTR_INFO_DELIVER_CODE_MASK;
		bool should_have_error_code;
		bool urg = nested_cpu_has2(vmcs12,
					   SECONDARY_EXEC_UNRESTRICTED_GUEST);
		bool prot_mode = !urg || vmcs12->guest_cr0 & X86_CR0_PE;

		/* VM-entry पूर्णांकerruption-info field: पूर्णांकerruption type */
		अगर (CC(पूर्णांकr_type == INTR_TYPE_RESERVED) ||
		    CC(पूर्णांकr_type == INTR_TYPE_OTHER_EVENT &&
		       !nested_cpu_supports_monitor_trap_flag(vcpu)))
			वापस -EINVAL;

		/* VM-entry पूर्णांकerruption-info field: vector */
		अगर (CC(पूर्णांकr_type == INTR_TYPE_NMI_INTR && vector != NMI_VECTOR) ||
		    CC(पूर्णांकr_type == INTR_TYPE_HARD_EXCEPTION && vector > 31) ||
		    CC(पूर्णांकr_type == INTR_TYPE_OTHER_EVENT && vector != 0))
			वापस -EINVAL;

		/* VM-entry पूर्णांकerruption-info field: deliver error code */
		should_have_error_code =
			पूर्णांकr_type == INTR_TYPE_HARD_EXCEPTION && prot_mode &&
			x86_exception_has_error_code(vector);
		अगर (CC(has_error_code != should_have_error_code))
			वापस -EINVAL;

		/* VM-entry exception error code */
		अगर (CC(has_error_code &&
		       vmcs12->vm_entry_exception_error_code & GENMASK(31, 16)))
			वापस -EINVAL;

		/* VM-entry पूर्णांकerruption-info field: reserved bits */
		अगर (CC(पूर्णांकr_info & INTR_INFO_RESVD_BITS_MASK))
			वापस -EINVAL;

		/* VM-entry inकाष्ठाion length */
		चयन (पूर्णांकr_type) अणु
		हाल INTR_TYPE_SOFT_EXCEPTION:
		हाल INTR_TYPE_SOFT_INTR:
		हाल INTR_TYPE_PRIV_SW_EXCEPTION:
			अगर (CC(vmcs12->vm_entry_inकाष्ठाion_len > 15) ||
			    CC(vmcs12->vm_entry_inकाष्ठाion_len == 0 &&
			    CC(!nested_cpu_has_zero_length_injection(vcpu))))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (nested_vmx_check_entry_msr_चयन_controls(vcpu, vmcs12))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_controls(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा vmcs12 *vmcs12)
अणु
	अगर (nested_check_vm_execution_controls(vcpu, vmcs12) ||
	    nested_check_vm_निकास_controls(vcpu, vmcs12) ||
	    nested_check_vm_entry_controls(vcpu, vmcs12))
		वापस -EINVAL;

	अगर (to_vmx(vcpu)->nested.enlightened_vmcs_enabled)
		वापस nested_evmcs_check_controls(vmcs12);

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_host_state(काष्ठा kvm_vcpu *vcpu,
				       काष्ठा vmcs12 *vmcs12)
अणु
	bool ia32e;

	अगर (CC(!nested_host_cr0_valid(vcpu, vmcs12->host_cr0)) ||
	    CC(!nested_host_cr4_valid(vcpu, vmcs12->host_cr4)) ||
	    CC(kvm_vcpu_is_illegal_gpa(vcpu, vmcs12->host_cr3)))
		वापस -EINVAL;

	अगर (CC(is_noncanonical_address(vmcs12->host_ia32_sysenter_esp, vcpu)) ||
	    CC(is_noncanonical_address(vmcs12->host_ia32_sysenter_eip, vcpu)))
		वापस -EINVAL;

	अगर ((vmcs12->vm_निकास_controls & VM_EXIT_LOAD_IA32_PAT) &&
	    CC(!kvm_pat_valid(vmcs12->host_ia32_pat)))
		वापस -EINVAL;

	अगर ((vmcs12->vm_निकास_controls & VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL) &&
	    CC(!kvm_valid_perf_global_ctrl(vcpu_to_pmu(vcpu),
					   vmcs12->host_ia32_perf_global_ctrl)))
		वापस -EINVAL;

#अगर_घोषित CONFIG_X86_64
	ia32e = !!(vcpu->arch.efer & EFER_LMA);
#अन्यथा
	ia32e = false;
#पूर्ण_अगर

	अगर (ia32e) अणु
		अगर (CC(!(vmcs12->vm_निकास_controls & VM_EXIT_HOST_ADDR_SPACE_SIZE)) ||
		    CC(!(vmcs12->host_cr4 & X86_CR4_PAE)))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (CC(vmcs12->vm_निकास_controls & VM_EXIT_HOST_ADDR_SPACE_SIZE) ||
		    CC(vmcs12->vm_entry_controls & VM_ENTRY_IA32E_MODE) ||
		    CC(vmcs12->host_cr4 & X86_CR4_PCIDE) ||
		    CC((vmcs12->host_rip) >> 32))
			वापस -EINVAL;
	पूर्ण

	अगर (CC(vmcs12->host_cs_selector & (SEGMENT_RPL_MASK | SEGMENT_TI_MASK)) ||
	    CC(vmcs12->host_ss_selector & (SEGMENT_RPL_MASK | SEGMENT_TI_MASK)) ||
	    CC(vmcs12->host_ds_selector & (SEGMENT_RPL_MASK | SEGMENT_TI_MASK)) ||
	    CC(vmcs12->host_es_selector & (SEGMENT_RPL_MASK | SEGMENT_TI_MASK)) ||
	    CC(vmcs12->host_fs_selector & (SEGMENT_RPL_MASK | SEGMENT_TI_MASK)) ||
	    CC(vmcs12->host_gs_selector & (SEGMENT_RPL_MASK | SEGMENT_TI_MASK)) ||
	    CC(vmcs12->host_tr_selector & (SEGMENT_RPL_MASK | SEGMENT_TI_MASK)) ||
	    CC(vmcs12->host_cs_selector == 0) ||
	    CC(vmcs12->host_tr_selector == 0) ||
	    CC(vmcs12->host_ss_selector == 0 && !ia32e))
		वापस -EINVAL;

	अगर (CC(is_noncanonical_address(vmcs12->host_fs_base, vcpu)) ||
	    CC(is_noncanonical_address(vmcs12->host_gs_base, vcpu)) ||
	    CC(is_noncanonical_address(vmcs12->host_gdtr_base, vcpu)) ||
	    CC(is_noncanonical_address(vmcs12->host_idtr_base, vcpu)) ||
	    CC(is_noncanonical_address(vmcs12->host_tr_base, vcpu)) ||
	    CC(is_noncanonical_address(vmcs12->host_rip, vcpu)))
		वापस -EINVAL;

	/*
	 * If the load IA32_EFER VM-निकास control is 1, bits reserved in the
	 * IA32_EFER MSR must be 0 in the field क्रम that रेजिस्टर. In addition,
	 * the values of the LMA and LME bits in the field must each be that of
	 * the host address-space size VM-निकास control.
	 */
	अगर (vmcs12->vm_निकास_controls & VM_EXIT_LOAD_IA32_EFER) अणु
		अगर (CC(!kvm_valid_efer(vcpu, vmcs12->host_ia32_efer)) ||
		    CC(ia32e != !!(vmcs12->host_ia32_efer & EFER_LMA)) ||
		    CC(ia32e != !!(vmcs12->host_ia32_efer & EFER_LME)))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_vmcs_link_ptr(काष्ठा kvm_vcpu *vcpu,
					  काष्ठा vmcs12 *vmcs12)
अणु
	पूर्णांक r = 0;
	काष्ठा vmcs12 *shaकरोw;
	काष्ठा kvm_host_map map;

	अगर (vmcs12->vmcs_link_poपूर्णांकer == -1ull)
		वापस 0;

	अगर (CC(!page_address_valid(vcpu, vmcs12->vmcs_link_poपूर्णांकer)))
		वापस -EINVAL;

	अगर (CC(kvm_vcpu_map(vcpu, gpa_to_gfn(vmcs12->vmcs_link_poपूर्णांकer), &map)))
		वापस -EINVAL;

	shaकरोw = map.hva;

	अगर (CC(shaकरोw->hdr.revision_id != VMCS12_REVISION) ||
	    CC(shaकरोw->hdr.shaकरोw_vmcs != nested_cpu_has_shaकरोw_vmcs(vmcs12)))
		r = -EINVAL;

	kvm_vcpu_unmap(vcpu, &map, false);
	वापस r;
पूर्ण

/*
 * Checks related to Guest Non-रेजिस्टर State
 */
अटल पूर्णांक nested_check_guest_non_reg_state(काष्ठा vmcs12 *vmcs12)
अणु
	अगर (CC(vmcs12->guest_activity_state != GUEST_ACTIVITY_ACTIVE &&
	       vmcs12->guest_activity_state != GUEST_ACTIVITY_HLT &&
	       vmcs12->guest_activity_state != GUEST_ACTIVITY_WAIT_SIPI))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_guest_state(काष्ठा kvm_vcpu *vcpu,
					काष्ठा vmcs12 *vmcs12,
					क्रमागत vm_entry_failure_code *entry_failure_code)
अणु
	bool ia32e;

	*entry_failure_code = ENTRY_FAIL_DEFAULT;

	अगर (CC(!nested_guest_cr0_valid(vcpu, vmcs12->guest_cr0)) ||
	    CC(!nested_guest_cr4_valid(vcpu, vmcs12->guest_cr4)))
		वापस -EINVAL;

	अगर ((vmcs12->vm_entry_controls & VM_ENTRY_LOAD_DEBUG_CONTROLS) &&
	    CC(!kvm_dr7_valid(vmcs12->guest_dr7)))
		वापस -EINVAL;

	अगर ((vmcs12->vm_entry_controls & VM_ENTRY_LOAD_IA32_PAT) &&
	    CC(!kvm_pat_valid(vmcs12->guest_ia32_pat)))
		वापस -EINVAL;

	अगर (nested_vmx_check_vmcs_link_ptr(vcpu, vmcs12)) अणु
		*entry_failure_code = ENTRY_FAIL_VMCS_LINK_PTR;
		वापस -EINVAL;
	पूर्ण

	अगर ((vmcs12->vm_entry_controls & VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL) &&
	    CC(!kvm_valid_perf_global_ctrl(vcpu_to_pmu(vcpu),
					   vmcs12->guest_ia32_perf_global_ctrl)))
		वापस -EINVAL;

	/*
	 * If the load IA32_EFER VM-entry control is 1, the following checks
	 * are perक्रमmed on the field क्रम the IA32_EFER MSR:
	 * - Bits reserved in the IA32_EFER MSR must be 0.
	 * - Bit 10 (corresponding to IA32_EFER.LMA) must equal the value of
	 *   the IA-32e mode guest VM-निकास control. It must also be identical
	 *   to bit 8 (LME) अगर bit 31 in the CR0 field (corresponding to
	 *   CR0.PG) is 1.
	 */
	अगर (to_vmx(vcpu)->nested.nested_run_pending &&
	    (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_IA32_EFER)) अणु
		ia32e = (vmcs12->vm_entry_controls & VM_ENTRY_IA32E_MODE) != 0;
		अगर (CC(!kvm_valid_efer(vcpu, vmcs12->guest_ia32_efer)) ||
		    CC(ia32e != !!(vmcs12->guest_ia32_efer & EFER_LMA)) ||
		    CC(((vmcs12->guest_cr0 & X86_CR0_PG) &&
		     ia32e != !!(vmcs12->guest_ia32_efer & EFER_LME))))
			वापस -EINVAL;
	पूर्ण

	अगर ((vmcs12->vm_entry_controls & VM_ENTRY_LOAD_BNDCFGS) &&
	    (CC(is_noncanonical_address(vmcs12->guest_bndcfgs & PAGE_MASK, vcpu)) ||
	     CC((vmcs12->guest_bndcfgs & MSR_IA32_BNDCFGS_RSVD))))
		वापस -EINVAL;

	अगर (nested_check_guest_non_reg_state(vmcs12))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nested_vmx_check_vmentry_hw(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित दीर्घ cr3, cr4;
	bool vm_fail;

	अगर (!nested_early_check)
		वापस 0;

	अगर (vmx->msr_स्वतःload.host.nr)
		vmcs_ग_लिखो32(VM_EXIT_MSR_LOAD_COUNT, 0);
	अगर (vmx->msr_स्वतःload.guest.nr)
		vmcs_ग_लिखो32(VM_ENTRY_MSR_LOAD_COUNT, 0);

	preempt_disable();

	vmx_prepare_चयन_to_guest(vcpu);

	/*
	 * Induce a consistency check VMExit by clearing bit 1 in GUEST_RFLAGS,
	 * which is reserved to '1' by hardware.  GUEST_RFLAGS is guaranteed to
	 * be written (by prepare_vmcs02()) beक्रमe the "real" VMEnter, i.e.
	 * there is no need to preserve other bits or save/restore the field.
	 */
	vmcs_ग_लिखोl(GUEST_RFLAGS, 0);

	cr3 = __get_current_cr3_fast();
	अगर (unlikely(cr3 != vmx->loaded_vmcs->host_state.cr3)) अणु
		vmcs_ग_लिखोl(HOST_CR3, cr3);
		vmx->loaded_vmcs->host_state.cr3 = cr3;
	पूर्ण

	cr4 = cr4_पढ़ो_shaकरोw();
	अगर (unlikely(cr4 != vmx->loaded_vmcs->host_state.cr4)) अणु
		vmcs_ग_लिखोl(HOST_CR4, cr4);
		vmx->loaded_vmcs->host_state.cr4 = cr4;
	पूर्ण

	vm_fail = __vmx_vcpu_run(vmx, (अचिन्हित दीर्घ *)&vcpu->arch.regs,
				 vmx->loaded_vmcs->launched);

	अगर (vmx->msr_स्वतःload.host.nr)
		vmcs_ग_लिखो32(VM_EXIT_MSR_LOAD_COUNT, vmx->msr_स्वतःload.host.nr);
	अगर (vmx->msr_स्वतःload.guest.nr)
		vmcs_ग_लिखो32(VM_ENTRY_MSR_LOAD_COUNT, vmx->msr_स्वतःload.guest.nr);

	अगर (vm_fail) अणु
		u32 error = vmcs_पढ़ो32(VM_INSTRUCTION_ERROR);

		preempt_enable();

		trace_kvm_nested_vmenter_failed(
			"early hardware check VM-instruction error: ", error);
		WARN_ON_ONCE(error != VMXERR_ENTRY_INVALID_CONTROL_FIELD);
		वापस 1;
	पूर्ण

	/*
	 * VMExit clears RFLAGS.IF and DR7, even on a consistency check.
	 */
	अगर (hw_अवरोधpoपूर्णांक_active())
		set_debugreg(__this_cpu_पढ़ो(cpu_dr7), 7);
	local_irq_enable();
	preempt_enable();

	/*
	 * A non-failing VMEntry means we somehow entered guest mode with
	 * an illegal RIP, and that's just the tip of the iceberg.  There
	 * is no telling what memory has been modअगरied or what state has
	 * been exposed to unknown code.  Hitting this all but guarantees
	 * a (very critical) hardware issue.
	 */
	WARN_ON(!(vmcs_पढ़ो32(VM_EXIT_REASON) &
		VMX_EXIT_REASONS_FAILED_VMENTRY));

	वापस 0;
पूर्ण

अटल bool nested_get_evmcs_page(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	/*
	 * hv_evmcs may end up being not mapped after migration (when
	 * L2 was running), map it here to make sure vmcs12 changes are
	 * properly reflected.
	 */
	अगर (vmx->nested.enlightened_vmcs_enabled && !vmx->nested.hv_evmcs) अणु
		क्रमागत nested_evmptrld_status evmptrld_status =
			nested_vmx_handle_enlightened_vmptrld(vcpu, false);

		अगर (evmptrld_status == EVMPTRLD_VMFAIL ||
		    evmptrld_status == EVMPTRLD_ERROR)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool nested_get_vmcs12_pages(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा kvm_host_map *map;
	काष्ठा page *page;
	u64 hpa;

	अगर (nested_cpu_has2(vmcs12, SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES)) अणु
		/*
		 * Translate L1 physical address to host physical
		 * address क्रम vmcs02. Keep the page pinned, so this
		 * physical address reमुख्यs valid. We keep a reference
		 * to it so we can release it later.
		 */
		अगर (vmx->nested.apic_access_page) अणु /* shouldn't happen */
			kvm_release_page_clean(vmx->nested.apic_access_page);
			vmx->nested.apic_access_page = शून्य;
		पूर्ण
		page = kvm_vcpu_gpa_to_page(vcpu, vmcs12->apic_access_addr);
		अगर (!is_error_page(page)) अणु
			vmx->nested.apic_access_page = page;
			hpa = page_to_phys(vmx->nested.apic_access_page);
			vmcs_ग_लिखो64(APIC_ACCESS_ADDR, hpa);
		पूर्ण अन्यथा अणु
			pr_debug_ratelimited("%s: no backing 'struct page' for APIC-access address in vmcs12\n",
					     __func__);
			vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
			vcpu->run->पूर्णांकernal.suberror =
				KVM_INTERNAL_ERROR_EMULATION;
			vcpu->run->पूर्णांकernal.ndata = 0;
			वापस false;
		पूर्ण
	पूर्ण

	अगर (nested_cpu_has(vmcs12, CPU_BASED_TPR_SHADOW)) अणु
		map = &vmx->nested.भव_apic_map;

		अगर (!kvm_vcpu_map(vcpu, gpa_to_gfn(vmcs12->भव_apic_page_addr), map)) अणु
			vmcs_ग_लिखो64(VIRTUAL_APIC_PAGE_ADDR, pfn_to_hpa(map->pfn));
		पूर्ण अन्यथा अगर (nested_cpu_has(vmcs12, CPU_BASED_CR8_LOAD_EXITING) &&
		           nested_cpu_has(vmcs12, CPU_BASED_CR8_STORE_EXITING) &&
			   !nested_cpu_has2(vmcs12, SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES)) अणु
			/*
			 * The processor will never use the TPR shaकरोw, simply
			 * clear the bit from the execution control.  Such a
			 * configuration is useless, but it happens in tests.
			 * For any other configuration, failing the vm entry is
			 * _not_ what the processor करोes but it's basically the
			 * only possibility we have.
			 */
			exec_controls_clearbit(vmx, CPU_BASED_TPR_SHADOW);
		पूर्ण अन्यथा अणु
			/*
			 * Write an illegal value to VIRTUAL_APIC_PAGE_ADDR to
			 * क्रमce VM-Entry to fail.
			 */
			vmcs_ग_लिखो64(VIRTUAL_APIC_PAGE_ADDR, -1ull);
		पूर्ण
	पूर्ण

	अगर (nested_cpu_has_posted_पूर्णांकr(vmcs12)) अणु
		map = &vmx->nested.pi_desc_map;

		अगर (!kvm_vcpu_map(vcpu, gpa_to_gfn(vmcs12->posted_पूर्णांकr_desc_addr), map)) अणु
			vmx->nested.pi_desc =
				(काष्ठा pi_desc *)(((व्योम *)map->hva) +
				offset_in_page(vmcs12->posted_पूर्णांकr_desc_addr));
			vmcs_ग_लिखो64(POSTED_INTR_DESC_ADDR,
				     pfn_to_hpa(map->pfn) + offset_in_page(vmcs12->posted_पूर्णांकr_desc_addr));
		पूर्ण
	पूर्ण
	अगर (nested_vmx_prepare_msr_biपंचांगap(vcpu, vmcs12))
		exec_controls_setbit(vmx, CPU_BASED_USE_MSR_BITMAPS);
	अन्यथा
		exec_controls_clearbit(vmx, CPU_BASED_USE_MSR_BITMAPS);

	वापस true;
पूर्ण

अटल bool vmx_get_nested_state_pages(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!nested_get_evmcs_page(vcpu)) अणु
		pr_debug_ratelimited("%s: enlightened vmptrld failed\n",
				     __func__);
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->पूर्णांकernal.suberror =
			KVM_INTERNAL_ERROR_EMULATION;
		vcpu->run->पूर्णांकernal.ndata = 0;

		वापस false;
	पूर्ण

	अगर (is_guest_mode(vcpu) && !nested_get_vmcs12_pages(vcpu))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक nested_vmx_ग_लिखो_pml_buffer(काष्ठा kvm_vcpu *vcpu, gpa_t gpa)
अणु
	काष्ठा vmcs12 *vmcs12;
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	gpa_t dst;

	अगर (WARN_ON_ONCE(!is_guest_mode(vcpu)))
		वापस 0;

	अगर (WARN_ON_ONCE(vmx->nested.pml_full))
		वापस 1;

	/*
	 * Check अगर PML is enabled क्रम the nested guest. Whether eptp bit 6 is
	 * set is alपढ़ोy checked as part of A/D emulation.
	 */
	vmcs12 = get_vmcs12(vcpu);
	अगर (!nested_cpu_has_pml(vmcs12))
		वापस 0;

	अगर (vmcs12->guest_pml_index >= PML_ENTITY_NUM) अणु
		vmx->nested.pml_full = true;
		वापस 1;
	पूर्ण

	gpa &= ~0xFFFull;
	dst = vmcs12->pml_address + माप(u64) * vmcs12->guest_pml_index;

	अगर (kvm_ग_लिखो_guest_page(vcpu->kvm, gpa_to_gfn(dst), &gpa,
				 offset_in_page(dst), माप(gpa)))
		वापस 0;

	vmcs12->guest_pml_index--;

	वापस 0;
पूर्ण

/*
 * Intel's VMX Inकाष्ठाion Reference specअगरies a common set of prerequisites
 * क्रम running VMX inकाष्ठाions (except VMXON, whose prerequisites are
 * slightly dअगरferent). It also specअगरies what exception to inject otherwise.
 * Note that many of these exceptions have priority over VM निकासs, so they
 * करोn't have to be checked again here.
 */
अटल पूर्णांक nested_vmx_check_permission(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!to_vmx(vcpu)->nested.vmxon) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 0;
	पूर्ण

	अगर (vmx_get_cpl(vcpu)) अणु
		kvm_inject_gp(vcpu, 0);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल u8 vmx_has_apicv_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	u8 rvi = vmx_get_rvi();
	u8 vppr = kvm_lapic_get_reg(vcpu->arch.apic, APIC_PROCPRI);

	वापस ((rvi & 0xf0) > (vppr & 0xf0));
पूर्ण

अटल व्योम load_vmcs12_host_state(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा vmcs12 *vmcs12);

/*
 * If from_vmentry is false, this is being called from state restore (either RSM
 * or KVM_SET_NESTED_STATE).  Otherwise it's called from vmlaunch/vmresume.
 *
 * Returns:
 *	NVMX_VMENTRY_SUCCESS: Entered VMX non-root mode
 *	NVMX_VMENTRY_VMFAIL:  Consistency check VMFail
 *	NVMX_VMENTRY_VMEXIT:  Consistency check VMExit
 *	NVMX_VMENTRY_KVM_INTERNAL_ERROR: KVM पूर्णांकernal error
 */
क्रमागत nvmx_vmentry_status nested_vmx_enter_non_root_mode(काष्ठा kvm_vcpu *vcpu,
							bool from_vmentry)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	क्रमागत vm_entry_failure_code entry_failure_code;
	bool evaluate_pending_पूर्णांकerrupts;
	जोड़ vmx_निकास_reason निकास_reason = अणु
		.basic = EXIT_REASON_INVALID_STATE,
		.failed_vmentry = 1,
	पूर्ण;
	u32 failed_index;

	अगर (kvm_check_request(KVM_REQ_TLB_FLUSH_CURRENT, vcpu))
		kvm_vcpu_flush_tlb_current(vcpu);

	evaluate_pending_पूर्णांकerrupts = exec_controls_get(vmx) &
		(CPU_BASED_INTR_WINDOW_EXITING | CPU_BASED_NMI_WINDOW_EXITING);
	अगर (likely(!evaluate_pending_पूर्णांकerrupts) && kvm_vcpu_apicv_active(vcpu))
		evaluate_pending_पूर्णांकerrupts |= vmx_has_apicv_पूर्णांकerrupt(vcpu);

	अगर (!(vmcs12->vm_entry_controls & VM_ENTRY_LOAD_DEBUG_CONTROLS))
		vmx->nested.vmcs01_debugctl = vmcs_पढ़ो64(GUEST_IA32_DEBUGCTL);
	अगर (kvm_mpx_supported() &&
		!(vmcs12->vm_entry_controls & VM_ENTRY_LOAD_BNDCFGS))
		vmx->nested.vmcs01_guest_bndcfgs = vmcs_पढ़ो64(GUEST_BNDCFGS);

	/*
	 * Overग_लिखो vmcs01.GUEST_CR3 with L1's CR3 अगर EPT is disabled *and*
	 * nested early checks are disabled.  In the event of a "late" VM-Fail,
	 * i.e. a VM-Fail detected by hardware but not KVM, KVM must unwind its
	 * software model to the pre-VMEntry host state.  When EPT is disabled,
	 * GUEST_CR3 holds KVM's shadow CR3, not L1's "real" CR3, which causes
	 * nested_vmx_restore_host_state() to corrupt vcpu->arch.cr3.  Stuffing
	 * vmcs01.GUEST_CR3 results in the unwind naturally setting arch.cr3 to
	 * the correct value.  Smashing vmcs01.GUEST_CR3 is safe because nested
	 * VM-Exits, and the unwind, reset KVM's MMU, i.e. vmcs01.GUEST_CR3 is
	 * guaranteed to be overwritten with a shaकरोw CR3 prior to re-entering
	 * L1.  Don't stuff vmcs01.GUEST_CR3 when using nested early checks as
	 * KVM modअगरies vcpu->arch.cr3 अगर and only अगर the early hardware checks
	 * pass, and early VM-Fails करो not reset KVM's MMU, i.e. the VM-Fail
	 * path would need to manually save/restore vmcs01.GUEST_CR3.
	 */
	अगर (!enable_ept && !nested_early_check)
		vmcs_ग_लिखोl(GUEST_CR3, vcpu->arch.cr3);

	vmx_चयन_vmcs(vcpu, &vmx->nested.vmcs02);

	prepare_vmcs02_early(vmx, vmcs12);

	अगर (from_vmentry) अणु
		अगर (unlikely(!nested_get_vmcs12_pages(vcpu))) अणु
			vmx_चयन_vmcs(vcpu, &vmx->vmcs01);
			वापस NVMX_VMENTRY_KVM_INTERNAL_ERROR;
		पूर्ण

		अगर (nested_vmx_check_vmentry_hw(vcpu)) अणु
			vmx_चयन_vmcs(vcpu, &vmx->vmcs01);
			वापस NVMX_VMENTRY_VMFAIL;
		पूर्ण

		अगर (nested_vmx_check_guest_state(vcpu, vmcs12,
						 &entry_failure_code)) अणु
			निकास_reason.basic = EXIT_REASON_INVALID_STATE;
			vmcs12->निकास_qualअगरication = entry_failure_code;
			जाओ vmentry_fail_vmनिकास;
		पूर्ण
	पूर्ण

	enter_guest_mode(vcpu);
	अगर (vmcs12->cpu_based_vm_exec_control & CPU_BASED_USE_TSC_OFFSETTING)
		vcpu->arch.tsc_offset += vmcs12->tsc_offset;

	अगर (prepare_vmcs02(vcpu, vmcs12, &entry_failure_code)) अणु
		निकास_reason.basic = EXIT_REASON_INVALID_STATE;
		vmcs12->निकास_qualअगरication = entry_failure_code;
		जाओ vmentry_fail_vmनिकास_guest_mode;
	पूर्ण

	अगर (from_vmentry) अणु
		failed_index = nested_vmx_load_msr(vcpu,
						   vmcs12->vm_entry_msr_load_addr,
						   vmcs12->vm_entry_msr_load_count);
		अगर (failed_index) अणु
			निकास_reason.basic = EXIT_REASON_MSR_LOAD_FAIL;
			vmcs12->निकास_qualअगरication = failed_index;
			जाओ vmentry_fail_vmनिकास_guest_mode;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The MMU is not initialized to poपूर्णांक at the right entities yet and
		 * "get pages" would need to पढ़ो data from the guest (i.e. we will
		 * need to perक्रमm gpa to hpa translation). Request a call
		 * to nested_get_vmcs12_pages beक्रमe the next VM-entry.  The MSRs
		 * have alपढ़ोy been set at vmentry समय and should not be reset.
		 */
		kvm_make_request(KVM_REQ_GET_NESTED_STATE_PAGES, vcpu);
	पूर्ण

	/*
	 * If L1 had a pending IRQ/NMI until it executed
	 * VMLAUNCH/VMRESUME which wasn't delivered because it was
	 * disallowed (e.g. पूर्णांकerrupts disabled), L0 needs to
	 * evaluate अगर this pending event should cause an निकास from L2
	 * to L1 or delivered directly to L2 (e.g. In हाल L1 करोn't
	 * पूर्णांकercept EXTERNAL_INTERRUPT).
	 *
	 * Usually this would be handled by the processor noticing an
	 * IRQ/NMI winकरोw request, or checking RVI during evaluation of
	 * pending भव पूर्णांकerrupts.  However, this setting was करोne
	 * on VMCS01 and now VMCS02 is active instead. Thus, we क्रमce L0
	 * to perक्रमm pending event evaluation by requesting a KVM_REQ_EVENT.
	 */
	अगर (unlikely(evaluate_pending_पूर्णांकerrupts))
		kvm_make_request(KVM_REQ_EVENT, vcpu);

	/*
	 * Do not start the preemption समयr hrसमयr until after we know
	 * we are successful, so that only nested_vmx_vmनिकास needs to cancel
	 * the समयr.
	 */
	vmx->nested.preemption_समयr_expired = false;
	अगर (nested_cpu_has_preemption_समयr(vmcs12)) अणु
		u64 समयr_value = vmx_calc_preemption_समयr_value(vcpu);
		vmx_start_preemption_समयr(vcpu, समयr_value);
	पूर्ण

	/*
	 * Note no nested_vmx_succeed or nested_vmx_fail here. At this poपूर्णांक
	 * we are no दीर्घer running L1, and VMLAUNCH/VMRESUME has not yet
	 * वापसed as far as L1 is concerned. It will only वापस (and set
	 * the success flag) when L2 निकासs (see nested_vmx_vmनिकास()).
	 */
	वापस NVMX_VMENTRY_SUCCESS;

	/*
	 * A failed consistency check that leads to a VMExit during L1's
	 * VMEnter to L2 is a variation of a normal VMनिकास, as explained in
	 * 26.7 "VM-entry failures during or after loading guest state".
	 */
vmentry_fail_vmनिकास_guest_mode:
	अगर (vmcs12->cpu_based_vm_exec_control & CPU_BASED_USE_TSC_OFFSETTING)
		vcpu->arch.tsc_offset -= vmcs12->tsc_offset;
	leave_guest_mode(vcpu);

vmentry_fail_vmनिकास:
	vmx_चयन_vmcs(vcpu, &vmx->vmcs01);

	अगर (!from_vmentry)
		वापस NVMX_VMENTRY_VMEXIT;

	load_vmcs12_host_state(vcpu, vmcs12);
	vmcs12->vm_निकास_reason = निकास_reason.full;
	अगर (enable_shaकरोw_vmcs || vmx->nested.hv_evmcs)
		vmx->nested.need_vmcs12_to_shaकरोw_sync = true;
	वापस NVMX_VMENTRY_VMEXIT;
पूर्ण

/*
 * nested_vmx_run() handles a nested entry, i.e., a VMLAUNCH or VMRESUME on L1
 * क्रम running an L2 nested guest.
 */
अटल पूर्णांक nested_vmx_run(काष्ठा kvm_vcpu *vcpu, bool launch)
अणु
	काष्ठा vmcs12 *vmcs12;
	क्रमागत nvmx_vmentry_status status;
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u32 पूर्णांकerrupt_shaकरोw = vmx_get_पूर्णांकerrupt_shaकरोw(vcpu);
	क्रमागत nested_evmptrld_status evmptrld_status;

	++vcpu->stat.nested_run;

	अगर (!nested_vmx_check_permission(vcpu))
		वापस 1;

	evmptrld_status = nested_vmx_handle_enlightened_vmptrld(vcpu, launch);
	अगर (evmptrld_status == EVMPTRLD_ERROR) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 1;
	पूर्ण अन्यथा अगर (CC(evmptrld_status == EVMPTRLD_VMFAIL)) अणु
		वापस nested_vmx_failInvalid(vcpu);
	पूर्ण

	अगर (CC(!vmx->nested.hv_evmcs && vmx->nested.current_vmptr == -1ull))
		वापस nested_vmx_failInvalid(vcpu);

	vmcs12 = get_vmcs12(vcpu);

	/*
	 * Can't VMLAUNCH or VMRESUME a shaकरोw VMCS. Despite the fact
	 * that there *is* a valid VMCS poपूर्णांकer, RFLAGS.CF is set
	 * rather than RFLAGS.ZF, and no error number is stored to the
	 * VM-inकाष्ठाion error field.
	 */
	अगर (CC(vmcs12->hdr.shaकरोw_vmcs))
		वापस nested_vmx_failInvalid(vcpu);

	अगर (vmx->nested.hv_evmcs) अणु
		copy_enlightened_to_vmcs12(vmx);
		/* Enlightened VMCS करोesn't have launch state */
		vmcs12->launch_state = !launch;
	पूर्ण अन्यथा अगर (enable_shaकरोw_vmcs) अणु
		copy_shaकरोw_to_vmcs12(vmx);
	पूर्ण

	/*
	 * The nested entry process starts with enक्रमcing various prerequisites
	 * on vmcs12 as required by the Intel SDM, and act appropriately when
	 * they fail: As the SDM explains, some conditions should cause the
	 * inकाष्ठाion to fail, जबतक others will cause the inकाष्ठाion to seem
	 * to succeed, but वापस an EXIT_REASON_INVALID_STATE.
	 * To speed up the normal (success) code path, we should aव्योम checking
	 * क्रम misconfigurations which will anyway be caught by the processor
	 * when using the merged vmcs02.
	 */
	अगर (CC(पूर्णांकerrupt_shaकरोw & KVM_X86_SHADOW_INT_MOV_SS))
		वापस nested_vmx_fail(vcpu, VMXERR_ENTRY_EVENTS_BLOCKED_BY_MOV_SS);

	अगर (CC(vmcs12->launch_state == launch))
		वापस nested_vmx_fail(vcpu,
			launch ? VMXERR_VMLAUNCH_NONCLEAR_VMCS
			       : VMXERR_VMRESUME_NONLAUNCHED_VMCS);

	अगर (nested_vmx_check_controls(vcpu, vmcs12))
		वापस nested_vmx_fail(vcpu, VMXERR_ENTRY_INVALID_CONTROL_FIELD);

	अगर (nested_vmx_check_host_state(vcpu, vmcs12))
		वापस nested_vmx_fail(vcpu, VMXERR_ENTRY_INVALID_HOST_STATE_FIELD);

	/*
	 * We're finally करोne with prerequisite checking, and can start with
	 * the nested entry.
	 */
	vmx->nested.nested_run_pending = 1;
	vmx->nested.has_preemption_समयr_deadline = false;
	status = nested_vmx_enter_non_root_mode(vcpu, true);
	अगर (unlikely(status != NVMX_VMENTRY_SUCCESS))
		जाओ vmentry_failed;

	/* Emulate processing of posted पूर्णांकerrupts on VM-Enter. */
	अगर (nested_cpu_has_posted_पूर्णांकr(vmcs12) &&
	    kvm_apic_has_पूर्णांकerrupt(vcpu) == vmx->nested.posted_पूर्णांकr_nv) अणु
		vmx->nested.pi_pending = true;
		kvm_make_request(KVM_REQ_EVENT, vcpu);
		kvm_apic_clear_irr(vcpu, vmx->nested.posted_पूर्णांकr_nv);
	पूर्ण

	/* Hide L1D cache contents from the nested guest.  */
	vmx->vcpu.arch.l1tf_flush_l1d = true;

	/*
	 * Must happen outside of nested_vmx_enter_non_root_mode() as it will
	 * also be used as part of restoring nVMX state क्रम
	 * snapshot restore (migration).
	 *
	 * In this flow, it is assumed that vmcs12 cache was
	 * transferred as part of captured nVMX state and should
	 * thereक्रमe not be पढ़ो from guest memory (which may not
	 * exist on destination host yet).
	 */
	nested_cache_shaकरोw_vmcs12(vcpu, vmcs12);

	चयन (vmcs12->guest_activity_state) अणु
	हाल GUEST_ACTIVITY_HLT:
		/*
		 * If we're entering a halted L2 vcpu and the L2 vcpu won't be
		 * awakened by event injection or by an NMI-winकरोw VM-निकास or
		 * by an पूर्णांकerrupt-winकरोw VM-निकास, halt the vcpu.
		 */
		अगर (!(vmcs12->vm_entry_पूर्णांकr_info_field & INTR_INFO_VALID_MASK) &&
		    !nested_cpu_has(vmcs12, CPU_BASED_NMI_WINDOW_EXITING) &&
		    !(nested_cpu_has(vmcs12, CPU_BASED_INTR_WINDOW_EXITING) &&
		      (vmcs12->guest_rflags & X86_EFLAGS_IF))) अणु
			vmx->nested.nested_run_pending = 0;
			वापस kvm_vcpu_halt(vcpu);
		पूर्ण
		अवरोध;
	हाल GUEST_ACTIVITY_WAIT_SIPI:
		vmx->nested.nested_run_pending = 0;
		vcpu->arch.mp_state = KVM_MP_STATE_INIT_RECEIVED;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 1;

vmentry_failed:
	vmx->nested.nested_run_pending = 0;
	अगर (status == NVMX_VMENTRY_KVM_INTERNAL_ERROR)
		वापस 0;
	अगर (status == NVMX_VMENTRY_VMEXIT)
		वापस 1;
	WARN_ON_ONCE(status != NVMX_VMENTRY_VMFAIL);
	वापस nested_vmx_fail(vcpu, VMXERR_ENTRY_INVALID_CONTROL_FIELD);
पूर्ण

/*
 * On a nested निकास from L2 to L1, vmcs12.guest_cr0 might not be up-to-date
 * because L2 may have changed some cr0 bits directly (CR0_GUEST_HOST_MASK).
 * This function वापसs the new value we should put in vmcs12.guest_cr0.
 * It's not enough to just वापस the vmcs02 GUEST_CR0. Rather,
 *  1. Bits that neither L0 nor L1 trapped, were set directly by L2 and are now
 *     available in vmcs02 GUEST_CR0. (Note: It's enough to check that L0
 *     didn't trap the bit, because अगर L1 did, so would L0).
 *  2. Bits that L1 asked to trap (and thereक्रमe L0 also did) could not have
 *     been modअगरied by L2, and L1 knows it. So just leave the old value of
 *     the bit from vmcs12.guest_cr0. Note that the bit from vmcs02 GUEST_CR0
 *     isn't relevant, because अगर L0 traps this bit it can set it to anything.
 *  3. Bits that L1 didn't trap, but L0 did. L1 believes the guest could have
 *     changed these bits, and thereक्रमe they need to be updated, but L0
 *     didn't necessarily allow them to be changed in GUEST_CR0 - and rather
 *     put them in vmcs02 CR0_READ_SHADOW. So take these bits from there.
 */
अटल अंतरभूत अचिन्हित दीर्घ
vmcs12_guest_cr0(काष्ठा kvm_vcpu *vcpu, काष्ठा vmcs12 *vmcs12)
अणु
	वापस
	/*1*/	(vmcs_पढ़ोl(GUEST_CR0) & vcpu->arch.cr0_guest_owned_bits) |
	/*2*/	(vmcs12->guest_cr0 & vmcs12->cr0_guest_host_mask) |
	/*3*/	(vmcs_पढ़ोl(CR0_READ_SHADOW) & ~(vmcs12->cr0_guest_host_mask |
			vcpu->arch.cr0_guest_owned_bits));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
vmcs12_guest_cr4(काष्ठा kvm_vcpu *vcpu, काष्ठा vmcs12 *vmcs12)
अणु
	वापस
	/*1*/	(vmcs_पढ़ोl(GUEST_CR4) & vcpu->arch.cr4_guest_owned_bits) |
	/*2*/	(vmcs12->guest_cr4 & vmcs12->cr4_guest_host_mask) |
	/*3*/	(vmcs_पढ़ोl(CR4_READ_SHADOW) & ~(vmcs12->cr4_guest_host_mask |
			vcpu->arch.cr4_guest_owned_bits));
पूर्ण

अटल व्योम vmcs12_save_pending_event(काष्ठा kvm_vcpu *vcpu,
				      काष्ठा vmcs12 *vmcs12)
अणु
	u32 idt_vectoring;
	अचिन्हित पूर्णांक nr;

	अगर (vcpu->arch.exception.injected) अणु
		nr = vcpu->arch.exception.nr;
		idt_vectoring = nr | VECTORING_INFO_VALID_MASK;

		अगर (kvm_exception_is_soft(nr)) अणु
			vmcs12->vm_निकास_inकाष्ठाion_len =
				vcpu->arch.event_निकास_inst_len;
			idt_vectoring |= INTR_TYPE_SOFT_EXCEPTION;
		पूर्ण अन्यथा
			idt_vectoring |= INTR_TYPE_HARD_EXCEPTION;

		अगर (vcpu->arch.exception.has_error_code) अणु
			idt_vectoring |= VECTORING_INFO_DELIVER_CODE_MASK;
			vmcs12->idt_vectoring_error_code =
				vcpu->arch.exception.error_code;
		पूर्ण

		vmcs12->idt_vectoring_info_field = idt_vectoring;
	पूर्ण अन्यथा अगर (vcpu->arch.nmi_injected) अणु
		vmcs12->idt_vectoring_info_field =
			INTR_TYPE_NMI_INTR | INTR_INFO_VALID_MASK | NMI_VECTOR;
	पूर्ण अन्यथा अगर (vcpu->arch.पूर्णांकerrupt.injected) अणु
		nr = vcpu->arch.पूर्णांकerrupt.nr;
		idt_vectoring = nr | VECTORING_INFO_VALID_MASK;

		अगर (vcpu->arch.पूर्णांकerrupt.soft) अणु
			idt_vectoring |= INTR_TYPE_SOFT_INTR;
			vmcs12->vm_entry_inकाष्ठाion_len =
				vcpu->arch.event_निकास_inst_len;
		पूर्ण अन्यथा
			idt_vectoring |= INTR_TYPE_EXT_INTR;

		vmcs12->idt_vectoring_info_field = idt_vectoring;
	पूर्ण
पूर्ण


व्योम nested_mark_vmcs12_pages_dirty(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	gfn_t gfn;

	/*
	 * Don't need to mark the APIC access page dirty; it is never
	 * written to by the CPU during APIC भवization.
	 */

	अगर (nested_cpu_has(vmcs12, CPU_BASED_TPR_SHADOW)) अणु
		gfn = vmcs12->भव_apic_page_addr >> PAGE_SHIFT;
		kvm_vcpu_mark_page_dirty(vcpu, gfn);
	पूर्ण

	अगर (nested_cpu_has_posted_पूर्णांकr(vmcs12)) अणु
		gfn = vmcs12->posted_पूर्णांकr_desc_addr >> PAGE_SHIFT;
		kvm_vcpu_mark_page_dirty(vcpu, gfn);
	पूर्ण
पूर्ण

अटल व्योम vmx_complete_nested_posted_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	पूर्णांक max_irr;
	व्योम *vapic_page;
	u16 status;

	अगर (!vmx->nested.pi_desc || !vmx->nested.pi_pending)
		वापस;

	vmx->nested.pi_pending = false;
	अगर (!pi_test_and_clear_on(vmx->nested.pi_desc))
		वापस;

	max_irr = find_last_bit((अचिन्हित दीर्घ *)vmx->nested.pi_desc->pir, 256);
	अगर (max_irr != 256) अणु
		vapic_page = vmx->nested.भव_apic_map.hva;
		अगर (!vapic_page)
			वापस;

		__kvm_apic_update_irr(vmx->nested.pi_desc->pir,
			vapic_page, &max_irr);
		status = vmcs_पढ़ो16(GUEST_INTR_STATUS);
		अगर ((u8)max_irr > ((u8)status & 0xff)) अणु
			status &= ~0xff;
			status |= (u8)max_irr;
			vmcs_ग_लिखो16(GUEST_INTR_STATUS, status);
		पूर्ण
	पूर्ण

	nested_mark_vmcs12_pages_dirty(vcpu);
पूर्ण

अटल व्योम nested_vmx_inject_exception_vmनिकास(काष्ठा kvm_vcpu *vcpu,
					       अचिन्हित दीर्घ निकास_qual)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	अचिन्हित पूर्णांक nr = vcpu->arch.exception.nr;
	u32 पूर्णांकr_info = nr | INTR_INFO_VALID_MASK;

	अगर (vcpu->arch.exception.has_error_code) अणु
		vmcs12->vm_निकास_पूर्णांकr_error_code = vcpu->arch.exception.error_code;
		पूर्णांकr_info |= INTR_INFO_DELIVER_CODE_MASK;
	पूर्ण

	अगर (kvm_exception_is_soft(nr))
		पूर्णांकr_info |= INTR_TYPE_SOFT_EXCEPTION;
	अन्यथा
		पूर्णांकr_info |= INTR_TYPE_HARD_EXCEPTION;

	अगर (!(vmcs12->idt_vectoring_info_field & VECTORING_INFO_VALID_MASK) &&
	    vmx_get_nmi_mask(vcpu))
		पूर्णांकr_info |= INTR_INFO_UNBLOCK_NMI;

	nested_vmx_vmनिकास(vcpu, EXIT_REASON_EXCEPTION_NMI, पूर्णांकr_info, निकास_qual);
पूर्ण

/*
 * Returns true अगर a debug trap is pending delivery.
 *
 * In KVM, debug traps bear an exception payload. As such, the class of a #DB
 * exception may be inferred from the presence of an exception payload.
 */
अटल अंतरभूत bool vmx_pending_dbg_trap(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.exception.pending &&
			vcpu->arch.exception.nr == DB_VECTOR &&
			vcpu->arch.exception.payload;
पूर्ण

/*
 * Certain VM-निकासs set the 'pending debug exceptions' field to indicate a
 * recognized #DB (data or single-step) that has yet to be delivered. Since KVM
 * represents these debug traps with a payload that is said to be compatible
 * with the 'pending debug exceptions' field, ग_लिखो the payload to the VMCS
 * field अगर a VM-निकास is delivered beक्रमe the debug trap.
 */
अटल व्योम nested_vmx_update_pending_dbg(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vmx_pending_dbg_trap(vcpu))
		vmcs_ग_लिखोl(GUEST_PENDING_DBG_EXCEPTIONS,
			    vcpu->arch.exception.payload);
पूर्ण

अटल bool nested_vmx_preemption_समयr_pending(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस nested_cpu_has_preemption_समयr(get_vmcs12(vcpu)) &&
	       to_vmx(vcpu)->nested.preemption_समयr_expired;
पूर्ण

अटल पूर्णांक vmx_check_nested_events(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	अचिन्हित दीर्घ निकास_qual;
	bool block_nested_events =
	    vmx->nested.nested_run_pending || kvm_event_needs_reinjection(vcpu);
	bool mtf_pending = vmx->nested.mtf_pending;
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;

	/*
	 * Clear the MTF state. If a higher priority VM-निकास is delivered first,
	 * this state is discarded.
	 */
	अगर (!block_nested_events)
		vmx->nested.mtf_pending = false;

	अगर (lapic_in_kernel(vcpu) &&
		test_bit(KVM_APIC_INIT, &apic->pending_events)) अणु
		अगर (block_nested_events)
			वापस -EBUSY;
		nested_vmx_update_pending_dbg(vcpu);
		clear_bit(KVM_APIC_INIT, &apic->pending_events);
		अगर (vcpu->arch.mp_state != KVM_MP_STATE_INIT_RECEIVED)
			nested_vmx_vmनिकास(vcpu, EXIT_REASON_INIT_SIGNAL, 0, 0);
		वापस 0;
	पूर्ण

	अगर (lapic_in_kernel(vcpu) &&
	    test_bit(KVM_APIC_SIPI, &apic->pending_events)) अणु
		अगर (block_nested_events)
			वापस -EBUSY;

		clear_bit(KVM_APIC_SIPI, &apic->pending_events);
		अगर (vcpu->arch.mp_state == KVM_MP_STATE_INIT_RECEIVED)
			nested_vmx_vmनिकास(vcpu, EXIT_REASON_SIPI_SIGNAL, 0,
						apic->sipi_vector & 0xFFUL);
		वापस 0;
	पूर्ण

	/*
	 * Process any exceptions that are not debug traps beक्रमe MTF.
	 *
	 * Note that only a pending nested run can block a pending exception.
	 * Otherwise an injected NMI/पूर्णांकerrupt should either be
	 * lost or delivered to the nested hypervisor in the IDT_VECTORING_INFO,
	 * जबतक delivering the pending exception.
	 */

	अगर (vcpu->arch.exception.pending && !vmx_pending_dbg_trap(vcpu)) अणु
		अगर (vmx->nested.nested_run_pending)
			वापस -EBUSY;
		अगर (!nested_vmx_check_exception(vcpu, &निकास_qual))
			जाओ no_vmनिकास;
		nested_vmx_inject_exception_vmनिकास(vcpu, निकास_qual);
		वापस 0;
	पूर्ण

	अगर (mtf_pending) अणु
		अगर (block_nested_events)
			वापस -EBUSY;
		nested_vmx_update_pending_dbg(vcpu);
		nested_vmx_vmनिकास(vcpu, EXIT_REASON_MONITOR_TRAP_FLAG, 0, 0);
		वापस 0;
	पूर्ण

	अगर (vcpu->arch.exception.pending) अणु
		अगर (vmx->nested.nested_run_pending)
			वापस -EBUSY;
		अगर (!nested_vmx_check_exception(vcpu, &निकास_qual))
			जाओ no_vmनिकास;
		nested_vmx_inject_exception_vmनिकास(vcpu, निकास_qual);
		वापस 0;
	पूर्ण

	अगर (nested_vmx_preemption_समयr_pending(vcpu)) अणु
		अगर (block_nested_events)
			वापस -EBUSY;
		nested_vmx_vmनिकास(vcpu, EXIT_REASON_PREEMPTION_TIMER, 0, 0);
		वापस 0;
	पूर्ण

	अगर (vcpu->arch.smi_pending && !is_smm(vcpu)) अणु
		अगर (block_nested_events)
			वापस -EBUSY;
		जाओ no_vmनिकास;
	पूर्ण

	अगर (vcpu->arch.nmi_pending && !vmx_nmi_blocked(vcpu)) अणु
		अगर (block_nested_events)
			वापस -EBUSY;
		अगर (!nested_निकास_on_nmi(vcpu))
			जाओ no_vmनिकास;

		nested_vmx_vmनिकास(vcpu, EXIT_REASON_EXCEPTION_NMI,
				  NMI_VECTOR | INTR_TYPE_NMI_INTR |
				  INTR_INFO_VALID_MASK, 0);
		/*
		 * The NMI-triggered VM निकास counts as injection:
		 * clear this one and block further NMIs.
		 */
		vcpu->arch.nmi_pending = 0;
		vmx_set_nmi_mask(vcpu, true);
		वापस 0;
	पूर्ण

	अगर (kvm_cpu_has_पूर्णांकerrupt(vcpu) && !vmx_पूर्णांकerrupt_blocked(vcpu)) अणु
		अगर (block_nested_events)
			वापस -EBUSY;
		अगर (!nested_निकास_on_पूर्णांकr(vcpu))
			जाओ no_vmनिकास;
		nested_vmx_vmनिकास(vcpu, EXIT_REASON_EXTERNAL_INTERRUPT, 0, 0);
		वापस 0;
	पूर्ण

no_vmनिकास:
	vmx_complete_nested_posted_पूर्णांकerrupt(vcpu);
	वापस 0;
पूर्ण

अटल u32 vmx_get_preemption_समयr_value(काष्ठा kvm_vcpu *vcpu)
अणु
	kसमय_प्रकार reमुख्यing =
		hrसमयr_get_reमुख्यing(&to_vmx(vcpu)->nested.preemption_समयr);
	u64 value;

	अगर (kसमय_प्रकारo_ns(reमुख्यing) <= 0)
		वापस 0;

	value = kसमय_प्रकारo_ns(reमुख्यing) * vcpu->arch.भव_tsc_khz;
	करो_भाग(value, 1000000);
	वापस value >> VMX_MISC_EMULATED_PREEMPTION_TIMER_RATE;
पूर्ण

अटल bool is_vmcs12_ext_field(अचिन्हित दीर्घ field)
अणु
	चयन (field) अणु
	हाल GUEST_ES_SELECTOR:
	हाल GUEST_CS_SELECTOR:
	हाल GUEST_SS_SELECTOR:
	हाल GUEST_DS_SELECTOR:
	हाल GUEST_FS_SELECTOR:
	हाल GUEST_GS_SELECTOR:
	हाल GUEST_LDTR_SELECTOR:
	हाल GUEST_TR_SELECTOR:
	हाल GUEST_ES_LIMIT:
	हाल GUEST_CS_LIMIT:
	हाल GUEST_SS_LIMIT:
	हाल GUEST_DS_LIMIT:
	हाल GUEST_FS_LIMIT:
	हाल GUEST_GS_LIMIT:
	हाल GUEST_LDTR_LIMIT:
	हाल GUEST_TR_LIMIT:
	हाल GUEST_GDTR_LIMIT:
	हाल GUEST_IDTR_LIMIT:
	हाल GUEST_ES_AR_BYTES:
	हाल GUEST_DS_AR_BYTES:
	हाल GUEST_FS_AR_BYTES:
	हाल GUEST_GS_AR_BYTES:
	हाल GUEST_LDTR_AR_BYTES:
	हाल GUEST_TR_AR_BYTES:
	हाल GUEST_ES_BASE:
	हाल GUEST_CS_BASE:
	हाल GUEST_SS_BASE:
	हाल GUEST_DS_BASE:
	हाल GUEST_FS_BASE:
	हाल GUEST_GS_BASE:
	हाल GUEST_LDTR_BASE:
	हाल GUEST_TR_BASE:
	हाल GUEST_GDTR_BASE:
	हाल GUEST_IDTR_BASE:
	हाल GUEST_PENDING_DBG_EXCEPTIONS:
	हाल GUEST_BNDCFGS:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम sync_vmcs02_to_vmcs12_rare(काष्ठा kvm_vcpu *vcpu,
				       काष्ठा vmcs12 *vmcs12)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	vmcs12->guest_es_selector = vmcs_पढ़ो16(GUEST_ES_SELECTOR);
	vmcs12->guest_cs_selector = vmcs_पढ़ो16(GUEST_CS_SELECTOR);
	vmcs12->guest_ss_selector = vmcs_पढ़ो16(GUEST_SS_SELECTOR);
	vmcs12->guest_ds_selector = vmcs_पढ़ो16(GUEST_DS_SELECTOR);
	vmcs12->guest_fs_selector = vmcs_पढ़ो16(GUEST_FS_SELECTOR);
	vmcs12->guest_gs_selector = vmcs_पढ़ो16(GUEST_GS_SELECTOR);
	vmcs12->guest_ldtr_selector = vmcs_पढ़ो16(GUEST_LDTR_SELECTOR);
	vmcs12->guest_tr_selector = vmcs_पढ़ो16(GUEST_TR_SELECTOR);
	vmcs12->guest_es_limit = vmcs_पढ़ो32(GUEST_ES_LIMIT);
	vmcs12->guest_cs_limit = vmcs_पढ़ो32(GUEST_CS_LIMIT);
	vmcs12->guest_ss_limit = vmcs_पढ़ो32(GUEST_SS_LIMIT);
	vmcs12->guest_ds_limit = vmcs_पढ़ो32(GUEST_DS_LIMIT);
	vmcs12->guest_fs_limit = vmcs_पढ़ो32(GUEST_FS_LIMIT);
	vmcs12->guest_gs_limit = vmcs_पढ़ो32(GUEST_GS_LIMIT);
	vmcs12->guest_ldtr_limit = vmcs_पढ़ो32(GUEST_LDTR_LIMIT);
	vmcs12->guest_tr_limit = vmcs_पढ़ो32(GUEST_TR_LIMIT);
	vmcs12->guest_gdtr_limit = vmcs_पढ़ो32(GUEST_GDTR_LIMIT);
	vmcs12->guest_idtr_limit = vmcs_पढ़ो32(GUEST_IDTR_LIMIT);
	vmcs12->guest_es_ar_bytes = vmcs_पढ़ो32(GUEST_ES_AR_BYTES);
	vmcs12->guest_ds_ar_bytes = vmcs_पढ़ो32(GUEST_DS_AR_BYTES);
	vmcs12->guest_fs_ar_bytes = vmcs_पढ़ो32(GUEST_FS_AR_BYTES);
	vmcs12->guest_gs_ar_bytes = vmcs_पढ़ो32(GUEST_GS_AR_BYTES);
	vmcs12->guest_ldtr_ar_bytes = vmcs_पढ़ो32(GUEST_LDTR_AR_BYTES);
	vmcs12->guest_tr_ar_bytes = vmcs_पढ़ो32(GUEST_TR_AR_BYTES);
	vmcs12->guest_es_base = vmcs_पढ़ोl(GUEST_ES_BASE);
	vmcs12->guest_cs_base = vmcs_पढ़ोl(GUEST_CS_BASE);
	vmcs12->guest_ss_base = vmcs_पढ़ोl(GUEST_SS_BASE);
	vmcs12->guest_ds_base = vmcs_पढ़ोl(GUEST_DS_BASE);
	vmcs12->guest_fs_base = vmcs_पढ़ोl(GUEST_FS_BASE);
	vmcs12->guest_gs_base = vmcs_पढ़ोl(GUEST_GS_BASE);
	vmcs12->guest_ldtr_base = vmcs_पढ़ोl(GUEST_LDTR_BASE);
	vmcs12->guest_tr_base = vmcs_पढ़ोl(GUEST_TR_BASE);
	vmcs12->guest_gdtr_base = vmcs_पढ़ोl(GUEST_GDTR_BASE);
	vmcs12->guest_idtr_base = vmcs_पढ़ोl(GUEST_IDTR_BASE);
	vmcs12->guest_pending_dbg_exceptions =
		vmcs_पढ़ोl(GUEST_PENDING_DBG_EXCEPTIONS);
	अगर (kvm_mpx_supported())
		vmcs12->guest_bndcfgs = vmcs_पढ़ो64(GUEST_BNDCFGS);

	vmx->nested.need_sync_vmcs02_to_vmcs12_rare = false;
पूर्ण

अटल व्योम copy_vmcs02_to_vmcs12_rare(काष्ठा kvm_vcpu *vcpu,
				       काष्ठा vmcs12 *vmcs12)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	पूर्णांक cpu;

	अगर (!vmx->nested.need_sync_vmcs02_to_vmcs12_rare)
		वापस;


	WARN_ON_ONCE(vmx->loaded_vmcs != &vmx->vmcs01);

	cpu = get_cpu();
	vmx->loaded_vmcs = &vmx->nested.vmcs02;
	vmx_vcpu_load_vmcs(vcpu, cpu, &vmx->vmcs01);

	sync_vmcs02_to_vmcs12_rare(vcpu, vmcs12);

	vmx->loaded_vmcs = &vmx->vmcs01;
	vmx_vcpu_load_vmcs(vcpu, cpu, &vmx->nested.vmcs02);
	put_cpu();
पूर्ण

/*
 * Update the guest state fields of vmcs12 to reflect changes that
 * occurred जबतक L2 was running. (The "IA-32e mode guest" bit of the
 * VM-entry controls is also updated, since this is really a guest
 * state bit.)
 */
अटल व्योम sync_vmcs02_to_vmcs12(काष्ठा kvm_vcpu *vcpu, काष्ठा vmcs12 *vmcs12)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (vmx->nested.hv_evmcs)
		sync_vmcs02_to_vmcs12_rare(vcpu, vmcs12);

	vmx->nested.need_sync_vmcs02_to_vmcs12_rare = !vmx->nested.hv_evmcs;

	vmcs12->guest_cr0 = vmcs12_guest_cr0(vcpu, vmcs12);
	vmcs12->guest_cr4 = vmcs12_guest_cr4(vcpu, vmcs12);

	vmcs12->guest_rsp = kvm_rsp_पढ़ो(vcpu);
	vmcs12->guest_rip = kvm_rip_पढ़ो(vcpu);
	vmcs12->guest_rflags = vmcs_पढ़ोl(GUEST_RFLAGS);

	vmcs12->guest_cs_ar_bytes = vmcs_पढ़ो32(GUEST_CS_AR_BYTES);
	vmcs12->guest_ss_ar_bytes = vmcs_पढ़ो32(GUEST_SS_AR_BYTES);

	vmcs12->guest_पूर्णांकerruptibility_info =
		vmcs_पढ़ो32(GUEST_INTERRUPTIBILITY_INFO);

	अगर (vcpu->arch.mp_state == KVM_MP_STATE_HALTED)
		vmcs12->guest_activity_state = GUEST_ACTIVITY_HLT;
	अन्यथा अगर (vcpu->arch.mp_state == KVM_MP_STATE_INIT_RECEIVED)
		vmcs12->guest_activity_state = GUEST_ACTIVITY_WAIT_SIPI;
	अन्यथा
		vmcs12->guest_activity_state = GUEST_ACTIVITY_ACTIVE;

	अगर (nested_cpu_has_preemption_समयr(vmcs12) &&
	    vmcs12->vm_निकास_controls & VM_EXIT_SAVE_VMX_PREEMPTION_TIMER &&
	    !vmx->nested.nested_run_pending)
		vmcs12->vmx_preemption_समयr_value =
			vmx_get_preemption_समयr_value(vcpu);

	/*
	 * In some हालs (usually, nested EPT), L2 is allowed to change its
	 * own CR3 without निकासing. If it has changed it, we must keep it.
	 * Of course, अगर L0 is using shaकरोw page tables, GUEST_CR3 was defined
	 * by L0, not L1 or L2, so we mustn't unconditionally copy it to vmcs12.
	 *
	 * Additionally, restore L2's PDPTR to vmcs12.
	 */
	अगर (enable_ept) अणु
		vmcs12->guest_cr3 = vmcs_पढ़ोl(GUEST_CR3);
		अगर (nested_cpu_has_ept(vmcs12) && is_pae_paging(vcpu)) अणु
			vmcs12->guest_pdptr0 = vmcs_पढ़ो64(GUEST_PDPTR0);
			vmcs12->guest_pdptr1 = vmcs_पढ़ो64(GUEST_PDPTR1);
			vmcs12->guest_pdptr2 = vmcs_पढ़ो64(GUEST_PDPTR2);
			vmcs12->guest_pdptr3 = vmcs_पढ़ो64(GUEST_PDPTR3);
		पूर्ण
	पूर्ण

	vmcs12->guest_linear_address = vmcs_पढ़ोl(GUEST_LINEAR_ADDRESS);

	अगर (nested_cpu_has_vid(vmcs12))
		vmcs12->guest_पूर्णांकr_status = vmcs_पढ़ो16(GUEST_INTR_STATUS);

	vmcs12->vm_entry_controls =
		(vmcs12->vm_entry_controls & ~VM_ENTRY_IA32E_MODE) |
		(vm_entry_controls_get(to_vmx(vcpu)) & VM_ENTRY_IA32E_MODE);

	अगर (vmcs12->vm_निकास_controls & VM_EXIT_SAVE_DEBUG_CONTROLS)
		kvm_get_dr(vcpu, 7, (अचिन्हित दीर्घ *)&vmcs12->guest_dr7);

	अगर (vmcs12->vm_निकास_controls & VM_EXIT_SAVE_IA32_EFER)
		vmcs12->guest_ia32_efer = vcpu->arch.efer;
पूर्ण

/*
 * prepare_vmcs12 is part of what we need to करो when the nested L2 guest निकासs
 * and we want to prepare to run its L1 parent. L1 keeps a vmcs क्रम L2 (vmcs12),
 * and this function updates it to reflect the changes to the guest state जबतक
 * L2 was running (and perhaps made some निकासs which were handled directly by L0
 * without going back to L1), and to reflect the निकास reason.
 * Note that we करो not have to copy here all VMCS fields, just those that
 * could have changed by the L2 guest or the निकास - i.e., the guest-state and
 * निकास-inक्रमmation fields only. Other fields are modअगरied by L1 with VMWRITE,
 * which alपढ़ोy ग_लिखोs to vmcs12 directly.
 */
अटल व्योम prepare_vmcs12(काष्ठा kvm_vcpu *vcpu, काष्ठा vmcs12 *vmcs12,
			   u32 vm_निकास_reason, u32 निकास_पूर्णांकr_info,
			   अचिन्हित दीर्घ निकास_qualअगरication)
अणु
	/* update निकास inक्रमmation fields: */
	vmcs12->vm_निकास_reason = vm_निकास_reason;
	अगर (to_vmx(vcpu)->निकास_reason.enclave_mode)
		vmcs12->vm_निकास_reason |= VMX_EXIT_REASONS_SGX_ENCLAVE_MODE;
	vmcs12->निकास_qualअगरication = निकास_qualअगरication;
	vmcs12->vm_निकास_पूर्णांकr_info = निकास_पूर्णांकr_info;

	vmcs12->idt_vectoring_info_field = 0;
	vmcs12->vm_निकास_inकाष्ठाion_len = vmcs_पढ़ो32(VM_EXIT_INSTRUCTION_LEN);
	vmcs12->vmx_inकाष्ठाion_info = vmcs_पढ़ो32(VMX_INSTRUCTION_INFO);

	अगर (!(vmcs12->vm_निकास_reason & VMX_EXIT_REASONS_FAILED_VMENTRY)) अणु
		vmcs12->launch_state = 1;

		/* vm_entry_पूर्णांकr_info_field is cleared on निकास. Emulate this
		 * instead of पढ़ोing the real value. */
		vmcs12->vm_entry_पूर्णांकr_info_field &= ~INTR_INFO_VALID_MASK;

		/*
		 * Transfer the event that L0 or L1 may wanted to inject पूर्णांकo
		 * L2 to IDT_VECTORING_INFO_FIELD.
		 */
		vmcs12_save_pending_event(vcpu, vmcs12);

		/*
		 * According to spec, there's no need to store the guest's
		 * MSRs अगर the निकास is due to a VM-entry failure that occurs
		 * during or after loading the guest state. Since this निकास
		 * करोes not fall in that category, we need to save the MSRs.
		 */
		अगर (nested_vmx_store_msr(vcpu,
					 vmcs12->vm_निकास_msr_store_addr,
					 vmcs12->vm_निकास_msr_store_count))
			nested_vmx_पात(vcpu,
					 VMX_ABORT_SAVE_GUEST_MSR_FAIL);
	पूर्ण

	/*
	 * Drop what we picked up क्रम L2 via vmx_complete_पूर्णांकerrupts. It is
	 * preserved above and would only end up incorrectly in L1.
	 */
	vcpu->arch.nmi_injected = false;
	kvm_clear_exception_queue(vcpu);
	kvm_clear_पूर्णांकerrupt_queue(vcpu);
पूर्ण

/*
 * A part of what we need to when the nested L2 guest निकासs and we want to
 * run its L1 parent, is to reset L1's guest state to the host state specअगरied
 * in vmcs12.
 * This function is to be called not only on normal nested निकास, but also on
 * a nested entry failure, as explained in Intel's spec, 3B.23.7 ("VM-Entry
 * Failures During or After Loading Guest State").
 * This function should be called when the active VMCS is L1's (vmcs01).
 */
अटल व्योम load_vmcs12_host_state(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा vmcs12 *vmcs12)
अणु
	क्रमागत vm_entry_failure_code ignored;
	काष्ठा kvm_segment seg;

	अगर (vmcs12->vm_निकास_controls & VM_EXIT_LOAD_IA32_EFER)
		vcpu->arch.efer = vmcs12->host_ia32_efer;
	अन्यथा अगर (vmcs12->vm_निकास_controls & VM_EXIT_HOST_ADDR_SPACE_SIZE)
		vcpu->arch.efer |= (EFER_LMA | EFER_LME);
	अन्यथा
		vcpu->arch.efer &= ~(EFER_LMA | EFER_LME);
	vmx_set_efer(vcpu, vcpu->arch.efer);

	kvm_rsp_ग_लिखो(vcpu, vmcs12->host_rsp);
	kvm_rip_ग_लिखो(vcpu, vmcs12->host_rip);
	vmx_set_rflags(vcpu, X86_EFLAGS_FIXED);
	vmx_set_पूर्णांकerrupt_shaकरोw(vcpu, 0);

	/*
	 * Note that calling vmx_set_cr0 is important, even अगर cr0 hasn't
	 * actually changed, because vmx_set_cr0 refers to efer set above.
	 *
	 * CR0_GUEST_HOST_MASK is alपढ़ोy set in the original vmcs01
	 * (KVM करोesn't change it);
	 */
	vcpu->arch.cr0_guest_owned_bits = KVM_POSSIBLE_CR0_GUEST_BITS;
	vmx_set_cr0(vcpu, vmcs12->host_cr0);

	/* Same as above - no reason to call set_cr4_guest_host_mask().  */
	vcpu->arch.cr4_guest_owned_bits = ~vmcs_पढ़ोl(CR4_GUEST_HOST_MASK);
	vmx_set_cr4(vcpu, vmcs12->host_cr4);

	nested_ept_uninit_mmu_context(vcpu);

	/*
	 * Only PDPTE load can fail as the value of cr3 was checked on entry and
	 * couldn't have changed.
	 */
	अगर (nested_vmx_load_cr3(vcpu, vmcs12->host_cr3, false, &ignored))
		nested_vmx_पात(vcpu, VMX_ABORT_LOAD_HOST_PDPTE_FAIL);

	nested_vmx_transition_tlb_flush(vcpu, vmcs12, false);

	vmcs_ग_लिखो32(GUEST_SYSENTER_CS, vmcs12->host_ia32_sysenter_cs);
	vmcs_ग_लिखोl(GUEST_SYSENTER_ESP, vmcs12->host_ia32_sysenter_esp);
	vmcs_ग_लिखोl(GUEST_SYSENTER_EIP, vmcs12->host_ia32_sysenter_eip);
	vmcs_ग_लिखोl(GUEST_IDTR_BASE, vmcs12->host_idtr_base);
	vmcs_ग_लिखोl(GUEST_GDTR_BASE, vmcs12->host_gdtr_base);
	vmcs_ग_लिखो32(GUEST_IDTR_LIMIT, 0xFFFF);
	vmcs_ग_लिखो32(GUEST_GDTR_LIMIT, 0xFFFF);

	/* If not VM_EXIT_CLEAR_BNDCFGS, the L2 value propagates to L1.  */
	अगर (vmcs12->vm_निकास_controls & VM_EXIT_CLEAR_BNDCFGS)
		vmcs_ग_लिखो64(GUEST_BNDCFGS, 0);

	अगर (vmcs12->vm_निकास_controls & VM_EXIT_LOAD_IA32_PAT) अणु
		vmcs_ग_लिखो64(GUEST_IA32_PAT, vmcs12->host_ia32_pat);
		vcpu->arch.pat = vmcs12->host_ia32_pat;
	पूर्ण
	अगर (vmcs12->vm_निकास_controls & VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL)
		WARN_ON_ONCE(kvm_set_msr(vcpu, MSR_CORE_PERF_GLOBAL_CTRL,
					 vmcs12->host_ia32_perf_global_ctrl));

	/* Set L1 segment info according to Intel SDM
	    27.5.2 Loading Host Segment and Descriptor-Table Registers */
	seg = (काष्ठा kvm_segment) अणु
		.base = 0,
		.limit = 0xFFFFFFFF,
		.selector = vmcs12->host_cs_selector,
		.type = 11,
		.present = 1,
		.s = 1,
		.g = 1
	पूर्ण;
	अगर (vmcs12->vm_निकास_controls & VM_EXIT_HOST_ADDR_SPACE_SIZE)
		seg.l = 1;
	अन्यथा
		seg.db = 1;
	vmx_set_segment(vcpu, &seg, VCPU_SREG_CS);
	seg = (काष्ठा kvm_segment) अणु
		.base = 0,
		.limit = 0xFFFFFFFF,
		.type = 3,
		.present = 1,
		.s = 1,
		.db = 1,
		.g = 1
	पूर्ण;
	seg.selector = vmcs12->host_ds_selector;
	vmx_set_segment(vcpu, &seg, VCPU_SREG_DS);
	seg.selector = vmcs12->host_es_selector;
	vmx_set_segment(vcpu, &seg, VCPU_SREG_ES);
	seg.selector = vmcs12->host_ss_selector;
	vmx_set_segment(vcpu, &seg, VCPU_SREG_SS);
	seg.selector = vmcs12->host_fs_selector;
	seg.base = vmcs12->host_fs_base;
	vmx_set_segment(vcpu, &seg, VCPU_SREG_FS);
	seg.selector = vmcs12->host_gs_selector;
	seg.base = vmcs12->host_gs_base;
	vmx_set_segment(vcpu, &seg, VCPU_SREG_GS);
	seg = (काष्ठा kvm_segment) अणु
		.base = vmcs12->host_tr_base,
		.limit = 0x67,
		.selector = vmcs12->host_tr_selector,
		.type = 11,
		.present = 1
	पूर्ण;
	vmx_set_segment(vcpu, &seg, VCPU_SREG_TR);

	kvm_set_dr(vcpu, 7, 0x400);
	vmcs_ग_लिखो64(GUEST_IA32_DEBUGCTL, 0);

	अगर (cpu_has_vmx_msr_biपंचांगap())
		vmx_update_msr_biपंचांगap(vcpu);

	अगर (nested_vmx_load_msr(vcpu, vmcs12->vm_निकास_msr_load_addr,
				vmcs12->vm_निकास_msr_load_count))
		nested_vmx_पात(vcpu, VMX_ABORT_LOAD_HOST_MSR_FAIL);
पूर्ण

अटल अंतरभूत u64 nested_vmx_get_vmcs01_guest_efer(काष्ठा vcpu_vmx *vmx)
अणु
	काष्ठा vmx_uret_msr *efer_msr;
	अचिन्हित पूर्णांक i;

	अगर (vm_entry_controls_get(vmx) & VM_ENTRY_LOAD_IA32_EFER)
		वापस vmcs_पढ़ो64(GUEST_IA32_EFER);

	अगर (cpu_has_load_ia32_efer())
		वापस host_efer;

	क्रम (i = 0; i < vmx->msr_स्वतःload.guest.nr; ++i) अणु
		अगर (vmx->msr_स्वतःload.guest.val[i].index == MSR_EFER)
			वापस vmx->msr_स्वतःload.guest.val[i].value;
	पूर्ण

	efer_msr = vmx_find_uret_msr(vmx, MSR_EFER);
	अगर (efer_msr)
		वापस efer_msr->data;

	वापस host_efer;
पूर्ण

अटल व्योम nested_vmx_restore_host_state(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा vmx_msr_entry g, h;
	gpa_t gpa;
	u32 i, j;

	vcpu->arch.pat = vmcs_पढ़ो64(GUEST_IA32_PAT);

	अगर (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_DEBUG_CONTROLS) अणु
		/*
		 * L1's host DR7 is lost अगर KVM_GUESTDBG_USE_HW_BP is set
		 * as vmcs01.GUEST_DR7 contains a userspace defined value
		 * and vcpu->arch.dr7 is not squirreled away beक्रमe the
		 * nested VMENTER (not worth adding a variable in nested_vmx).
		 */
		अगर (vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP)
			kvm_set_dr(vcpu, 7, DR7_FIXED_1);
		अन्यथा
			WARN_ON(kvm_set_dr(vcpu, 7, vmcs_पढ़ोl(GUEST_DR7)));
	पूर्ण

	/*
	 * Note that calling vmx_set_अणुefer,cr0,cr4पूर्ण is important as they
	 * handle a variety of side effects to KVM's software model.
	 */
	vmx_set_efer(vcpu, nested_vmx_get_vmcs01_guest_efer(vmx));

	vcpu->arch.cr0_guest_owned_bits = KVM_POSSIBLE_CR0_GUEST_BITS;
	vmx_set_cr0(vcpu, vmcs_पढ़ोl(CR0_READ_SHADOW));

	vcpu->arch.cr4_guest_owned_bits = ~vmcs_पढ़ोl(CR4_GUEST_HOST_MASK);
	vmx_set_cr4(vcpu, vmcs_पढ़ोl(CR4_READ_SHADOW));

	nested_ept_uninit_mmu_context(vcpu);
	vcpu->arch.cr3 = vmcs_पढ़ोl(GUEST_CR3);
	kvm_रेजिस्टर_mark_available(vcpu, VCPU_EXREG_CR3);

	/*
	 * Use ept_save_pdptrs(vcpu) to load the MMU's cached PDPTRs
	 * from vmcs01 (अगर necessary).  The PDPTRs are not loaded on
	 * VMFail, like everything अन्यथा we just need to ensure our
	 * software model is up-to-date.
	 */
	अगर (enable_ept && is_pae_paging(vcpu))
		ept_save_pdptrs(vcpu);

	kvm_mmu_reset_context(vcpu);

	अगर (cpu_has_vmx_msr_biपंचांगap())
		vmx_update_msr_biपंचांगap(vcpu);

	/*
	 * This nasty bit of खोलो coding is a compromise between blindly
	 * loading L1's MSRs using the निकास load lists (incorrect emulation
	 * of VMFail), leaving the nested VM's MSRs in the software model
	 * (incorrect behavior) and snapshotting the modअगरied MSRs (too
	 * expensive since the lists are unbound by hardware).  For each
	 * MSR that was (prematurely) loaded from the nested VMEntry load
	 * list, reload it from the निकास load list अगर it exists and dअगरfers
	 * from the guest value.  The पूर्णांकent is to stuff host state as
	 * silently as possible, not to fully process the निकास load list.
	 */
	क्रम (i = 0; i < vmcs12->vm_entry_msr_load_count; i++) अणु
		gpa = vmcs12->vm_entry_msr_load_addr + (i * माप(g));
		अगर (kvm_vcpu_पढ़ो_guest(vcpu, gpa, &g, माप(g))) अणु
			pr_debug_ratelimited(
				"%s read MSR index failed (%u, 0x%08llx)\n",
				__func__, i, gpa);
			जाओ vmपात;
		पूर्ण

		क्रम (j = 0; j < vmcs12->vm_निकास_msr_load_count; j++) अणु
			gpa = vmcs12->vm_निकास_msr_load_addr + (j * माप(h));
			अगर (kvm_vcpu_पढ़ो_guest(vcpu, gpa, &h, माप(h))) अणु
				pr_debug_ratelimited(
					"%s read MSR failed (%u, 0x%08llx)\n",
					__func__, j, gpa);
				जाओ vmपात;
			पूर्ण
			अगर (h.index != g.index)
				जारी;
			अगर (h.value == g.value)
				अवरोध;

			अगर (nested_vmx_load_msr_check(vcpu, &h)) अणु
				pr_debug_ratelimited(
					"%s check failed (%u, 0x%x, 0x%x)\n",
					__func__, j, h.index, h.reserved);
				जाओ vmपात;
			पूर्ण

			अगर (kvm_set_msr(vcpu, h.index, h.value)) अणु
				pr_debug_ratelimited(
					"%s WRMSR failed (%u, 0x%x, 0x%llx)\n",
					__func__, j, h.index, h.value);
				जाओ vmपात;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस;

vmपात:
	nested_vmx_पात(vcpu, VMX_ABORT_LOAD_HOST_MSR_FAIL);
पूर्ण

/*
 * Emulate an निकास from nested guest (L2) to L1, i.e., prepare to run L1
 * and modअगरy vmcs12 to make it see what it would expect to see there अगर
 * L2 was its real guest. Must only be called when in L2 (is_guest_mode())
 */
व्योम nested_vmx_vmनिकास(काष्ठा kvm_vcpu *vcpu, u32 vm_निकास_reason,
		       u32 निकास_पूर्णांकr_info, अचिन्हित दीर्घ निकास_qualअगरication)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);

	/* trying to cancel vmlaunch/vmresume is a bug */
	WARN_ON_ONCE(vmx->nested.nested_run_pending);

	/* Similarly, triple faults in L2 should never escape. */
	WARN_ON_ONCE(kvm_check_request(KVM_REQ_TRIPLE_FAULT, vcpu));

	अगर (kvm_check_request(KVM_REQ_GET_NESTED_STATE_PAGES, vcpu)) अणु
		/*
		 * KVM_REQ_GET_NESTED_STATE_PAGES is also used to map
		 * Enlightened VMCS after migration and we still need to
		 * करो that when something is क्रमcing L2->L1 निकास prior to
		 * the first L2 run.
		 */
		(व्योम)nested_get_evmcs_page(vcpu);
	पूर्ण

	/* Service the TLB flush request क्रम L2 beक्रमe चयनing to L1. */
	अगर (kvm_check_request(KVM_REQ_TLB_FLUSH_CURRENT, vcpu))
		kvm_vcpu_flush_tlb_current(vcpu);

	/*
	 * VCPU_EXREG_PDPTR will be clobbered in arch/x86/kvm/vmx/vmx.h between
	 * now and the new vmentry.  Ensure that the VMCS02 PDPTR fields are
	 * up-to-date beक्रमe चयनing to L1.
	 */
	अगर (enable_ept && is_pae_paging(vcpu))
		vmx_ept_load_pdptrs(vcpu);

	leave_guest_mode(vcpu);

	अगर (nested_cpu_has_preemption_समयr(vmcs12))
		hrसमयr_cancel(&to_vmx(vcpu)->nested.preemption_समयr);

	अगर (vmcs12->cpu_based_vm_exec_control & CPU_BASED_USE_TSC_OFFSETTING)
		vcpu->arch.tsc_offset -= vmcs12->tsc_offset;

	अगर (likely(!vmx->fail)) अणु
		sync_vmcs02_to_vmcs12(vcpu, vmcs12);

		अगर (vm_निकास_reason != -1)
			prepare_vmcs12(vcpu, vmcs12, vm_निकास_reason,
				       निकास_पूर्णांकr_info, निकास_qualअगरication);

		/*
		 * Must happen outside of sync_vmcs02_to_vmcs12() as it will
		 * also be used to capture vmcs12 cache as part of
		 * capturing nVMX state क्रम snapshot (migration).
		 *
		 * Otherwise, this flush will dirty guest memory at a
		 * poपूर्णांक it is alपढ़ोy assumed by user-space to be
		 * immutable.
		 */
		nested_flush_cached_shaकरोw_vmcs12(vcpu, vmcs12);
	पूर्ण अन्यथा अणु
		/*
		 * The only expected VM-inकाष्ठाion error is "VM entry with
		 * invalid control field(s)." Anything अन्यथा indicates a
		 * problem with L0.  And we should never get here with a
		 * VMFail of any type अगर early consistency checks are enabled.
		 */
		WARN_ON_ONCE(vmcs_पढ़ो32(VM_INSTRUCTION_ERROR) !=
			     VMXERR_ENTRY_INVALID_CONTROL_FIELD);
		WARN_ON_ONCE(nested_early_check);
	पूर्ण

	vmx_चयन_vmcs(vcpu, &vmx->vmcs01);

	/* Update any VMCS fields that might have changed जबतक L2 ran */
	vmcs_ग_लिखो32(VM_EXIT_MSR_LOAD_COUNT, vmx->msr_स्वतःload.host.nr);
	vmcs_ग_लिखो32(VM_ENTRY_MSR_LOAD_COUNT, vmx->msr_स्वतःload.guest.nr);
	vmcs_ग_लिखो64(TSC_OFFSET, vcpu->arch.tsc_offset);
	अगर (vmx->nested.l1_tpr_threshold != -1)
		vmcs_ग_लिखो32(TPR_THRESHOLD, vmx->nested.l1_tpr_threshold);

	अगर (kvm_has_tsc_control)
		decache_tsc_multiplier(vmx);

	अगर (vmx->nested.change_vmcs01_भव_apic_mode) अणु
		vmx->nested.change_vmcs01_भव_apic_mode = false;
		vmx_set_भव_apic_mode(vcpu);
	पूर्ण

	अगर (vmx->nested.update_vmcs01_cpu_dirty_logging) अणु
		vmx->nested.update_vmcs01_cpu_dirty_logging = false;
		vmx_update_cpu_dirty_logging(vcpu);
	पूर्ण

	/* Unpin physical memory we referred to in vmcs02 */
	अगर (vmx->nested.apic_access_page) अणु
		kvm_release_page_clean(vmx->nested.apic_access_page);
		vmx->nested.apic_access_page = शून्य;
	पूर्ण
	kvm_vcpu_unmap(vcpu, &vmx->nested.भव_apic_map, true);
	kvm_vcpu_unmap(vcpu, &vmx->nested.pi_desc_map, true);
	vmx->nested.pi_desc = शून्य;

	अगर (vmx->nested.reload_vmcs01_apic_access_page) अणु
		vmx->nested.reload_vmcs01_apic_access_page = false;
		kvm_make_request(KVM_REQ_APIC_PAGE_RELOAD, vcpu);
	पूर्ण

	अगर ((vm_निकास_reason != -1) &&
	    (enable_shaकरोw_vmcs || vmx->nested.hv_evmcs))
		vmx->nested.need_vmcs12_to_shaकरोw_sync = true;

	/* in हाल we halted in L2 */
	vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;

	अगर (likely(!vmx->fail)) अणु
		अगर ((u16)vm_निकास_reason == EXIT_REASON_EXTERNAL_INTERRUPT &&
		    nested_निकास_पूर्णांकr_ack_set(vcpu)) अणु
			पूर्णांक irq = kvm_cpu_get_पूर्णांकerrupt(vcpu);
			WARN_ON(irq < 0);
			vmcs12->vm_निकास_पूर्णांकr_info = irq |
				INTR_INFO_VALID_MASK | INTR_TYPE_EXT_INTR;
		पूर्ण

		अगर (vm_निकास_reason != -1)
			trace_kvm_nested_vmनिकास_inject(vmcs12->vm_निकास_reason,
						       vmcs12->निकास_qualअगरication,
						       vmcs12->idt_vectoring_info_field,
						       vmcs12->vm_निकास_पूर्णांकr_info,
						       vmcs12->vm_निकास_पूर्णांकr_error_code,
						       KVM_ISA_VMX);

		load_vmcs12_host_state(vcpu, vmcs12);

		वापस;
	पूर्ण

	/*
	 * After an early L2 VM-entry failure, we're now back
	 * in L1 which thinks it just finished a VMLAUNCH or
	 * VMRESUME inकाष्ठाion, so we need to set the failure
	 * flag and the VM-inकाष्ठाion error field of the VMCS
	 * accordingly, and skip the emulated inकाष्ठाion.
	 */
	(व्योम)nested_vmx_fail(vcpu, VMXERR_ENTRY_INVALID_CONTROL_FIELD);

	/*
	 * Restore L1's host state to KVM's software model.  We're here
	 * because a consistency check was caught by hardware, which
	 * means some amount of guest state has been propagated to KVM's
	 * model and needs to be unwound to the host's state.
	 */
	nested_vmx_restore_host_state(vcpu);

	vmx->fail = 0;
पूर्ण

अटल व्योम nested_vmx_triple_fault(काष्ठा kvm_vcpu *vcpu)
अणु
	nested_vmx_vmनिकास(vcpu, EXIT_REASON_TRIPLE_FAULT, 0, 0);
पूर्ण

/*
 * Decode the memory-address opeअक्रम of a vmx inकाष्ठाion, as recorded on an
 * निकास caused by such an inकाष्ठाion (run by a guest hypervisor).
 * On success, वापसs 0. When the opeअक्रम is invalid, वापसs 1 and throws
 * #UD, #GP, or #SS.
 */
पूर्णांक get_vmx_mem_address(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ निकास_qualअगरication,
			u32 vmx_inकाष्ठाion_info, bool wr, पूर्णांक len, gva_t *ret)
अणु
	gva_t off;
	bool exn;
	काष्ठा kvm_segment s;

	/*
	 * According to Vol. 3B, "Inक्रमmation क्रम VM Exits Due to Inकाष्ठाion
	 * Execution", on an निकास, vmx_inकाष्ठाion_info holds most of the
	 * addressing components of the opeअक्रम. Only the displacement part
	 * is put in निकास_qualअगरication (see 3B, "Basic VM-Exit Information").
	 * For how an actual address is calculated from all these components,
	 * refer to Vol. 1, "Operand Addressing".
	 */
	पूर्णांक  scaling = vmx_inकाष्ठाion_info & 3;
	पूर्णांक  addr_size = (vmx_inकाष्ठाion_info >> 7) & 7;
	bool is_reg = vmx_inकाष्ठाion_info & (1u << 10);
	पूर्णांक  seg_reg = (vmx_inकाष्ठाion_info >> 15) & 7;
	पूर्णांक  index_reg = (vmx_inकाष्ठाion_info >> 18) & 0xf;
	bool index_is_valid = !(vmx_inकाष्ठाion_info & (1u << 22));
	पूर्णांक  base_reg       = (vmx_inकाष्ठाion_info >> 23) & 0xf;
	bool base_is_valid  = !(vmx_inकाष्ठाion_info & (1u << 27));

	अगर (is_reg) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 1;
	पूर्ण

	/* Addr = segment_base + offset */
	/* offset = base + [index * scale] + displacement */
	off = निकास_qualअगरication; /* holds the displacement */
	अगर (addr_size == 1)
		off = (gva_t)sign_extend64(off, 31);
	अन्यथा अगर (addr_size == 0)
		off = (gva_t)sign_extend64(off, 15);
	अगर (base_is_valid)
		off += kvm_रेजिस्टर_पढ़ो(vcpu, base_reg);
	अगर (index_is_valid)
		off += kvm_रेजिस्टर_पढ़ो(vcpu, index_reg) << scaling;
	vmx_get_segment(vcpu, &s, seg_reg);

	/*
	 * The effective address, i.e. @off, of a memory opeअक्रम is truncated
	 * based on the address size of the inकाष्ठाion.  Note that this is
	 * the *effective address*, i.e. the address prior to accounting क्रम
	 * the segment's base.
	 */
	अगर (addr_size == 1) /* 32 bit */
		off &= 0xffffffff;
	अन्यथा अगर (addr_size == 0) /* 16 bit */
		off &= 0xffff;

	/* Checks क्रम #GP/#SS exceptions. */
	exn = false;
	अगर (is_दीर्घ_mode(vcpu)) अणु
		/*
		 * The भव/linear address is never truncated in 64-bit
		 * mode, e.g. a 32-bit address size can yield a 64-bit भव
		 * address when using FS/GS with a non-zero base.
		 */
		अगर (seg_reg == VCPU_SREG_FS || seg_reg == VCPU_SREG_GS)
			*ret = s.base + off;
		अन्यथा
			*ret = off;

		/* Long mode: #GP(0)/#SS(0) अगर the memory address is in a
		 * non-canonical क्रमm. This is the only check on the memory
		 * destination क्रम दीर्घ mode!
		 */
		exn = is_noncanonical_address(*ret, vcpu);
	पूर्ण अन्यथा अणु
		/*
		 * When not in दीर्घ mode, the भव/linear address is
		 * unconditionally truncated to 32 bits regardless of the
		 * address size.
		 */
		*ret = (s.base + off) & 0xffffffff;

		/* Protected mode: apply checks क्रम segment validity in the
		 * following order:
		 * - segment type check (#GP(0) may be thrown)
		 * - usability check (#GP(0)/#SS(0))
		 * - limit check (#GP(0)/#SS(0))
		 */
		अगर (wr)
			/* #GP(0) अगर the destination opeअक्रम is located in a
			 * पढ़ो-only data segment or any code segment.
			 */
			exn = ((s.type & 0xa) == 0 || (s.type & 8));
		अन्यथा
			/* #GP(0) अगर the source opeअक्रम is located in an
			 * execute-only code segment
			 */
			exn = ((s.type & 0xa) == 8);
		अगर (exn) अणु
			kvm_queue_exception_e(vcpu, GP_VECTOR, 0);
			वापस 1;
		पूर्ण
		/* Protected mode: #GP(0)/#SS(0) अगर the segment is unusable.
		 */
		exn = (s.unusable != 0);

		/*
		 * Protected mode: #GP(0)/#SS(0) अगर the memory opeअक्रम is
		 * outside the segment limit.  All CPUs that support VMX ignore
		 * limit checks क्रम flat segments, i.e. segments with base==0,
		 * limit==0xffffffff and of type expand-up data or code.
		 */
		अगर (!(s.base == 0 && s.limit == 0xffffffff &&
		     ((s.type & 8) || !(s.type & 4))))
			exn = exn || ((u64)off + len - 1 > s.limit);
	पूर्ण
	अगर (exn) अणु
		kvm_queue_exception_e(vcpu,
				      seg_reg == VCPU_SREG_SS ?
						SS_VECTOR : GP_VECTOR,
				      0);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nested_vmx_pmu_entry_निकास_ctls_update(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx;

	अगर (!nested_vmx_allowed(vcpu))
		वापस;

	vmx = to_vmx(vcpu);
	अगर (kvm_x86_ops.pmu_ops->is_valid_msr(vcpu, MSR_CORE_PERF_GLOBAL_CTRL)) अणु
		vmx->nested.msrs.entry_ctls_high |=
				VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL;
		vmx->nested.msrs.निकास_ctls_high |=
				VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL;
	पूर्ण अन्यथा अणु
		vmx->nested.msrs.entry_ctls_high &=
				~VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL;
		vmx->nested.msrs.निकास_ctls_high &=
				~VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL;
	पूर्ण
पूर्ण

अटल पूर्णांक nested_vmx_get_vmptr(काष्ठा kvm_vcpu *vcpu, gpa_t *vmpoपूर्णांकer,
				पूर्णांक *ret)
अणु
	gva_t gva;
	काष्ठा x86_exception e;
	पूर्णांक r;

	अगर (get_vmx_mem_address(vcpu, vmx_get_निकास_qual(vcpu),
				vmcs_पढ़ो32(VMX_INSTRUCTION_INFO), false,
				माप(*vmpoपूर्णांकer), &gva)) अणु
		*ret = 1;
		वापस -EINVAL;
	पूर्ण

	r = kvm_पढ़ो_guest_virt(vcpu, gva, vmpoपूर्णांकer, माप(*vmpoपूर्णांकer), &e);
	अगर (r != X86EMUL_CONTINUE) अणु
		*ret = kvm_handle_memory_failure(vcpu, r, &e);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Allocate a shaकरोw VMCS and associate it with the currently loaded
 * VMCS, unless such a shaकरोw VMCS alपढ़ोy exists. The newly allocated
 * VMCS is also VMCLEARed, so that it is पढ़ोy क्रम use.
 */
अटल काष्ठा vmcs *alloc_shaकरोw_vmcs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा loaded_vmcs *loaded_vmcs = vmx->loaded_vmcs;

	/*
	 * We should allocate a shaकरोw vmcs क्रम vmcs01 only when L1
	 * executes VMXON and मुक्त it when L1 executes VMXOFF.
	 * As it is invalid to execute VMXON twice, we shouldn't reach
	 * here when vmcs01 alपढ़ोy have an allocated shaकरोw vmcs.
	 */
	WARN_ON(loaded_vmcs == &vmx->vmcs01 && loaded_vmcs->shaकरोw_vmcs);

	अगर (!loaded_vmcs->shaकरोw_vmcs) अणु
		loaded_vmcs->shaकरोw_vmcs = alloc_vmcs(true);
		अगर (loaded_vmcs->shaकरोw_vmcs)
			vmcs_clear(loaded_vmcs->shaकरोw_vmcs);
	पूर्ण
	वापस loaded_vmcs->shaकरोw_vmcs;
पूर्ण

अटल पूर्णांक enter_vmx_operation(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	पूर्णांक r;

	r = alloc_loaded_vmcs(&vmx->nested.vmcs02);
	अगर (r < 0)
		जाओ out_vmcs02;

	vmx->nested.cached_vmcs12 = kzalloc(VMCS12_SIZE, GFP_KERNEL_ACCOUNT);
	अगर (!vmx->nested.cached_vmcs12)
		जाओ out_cached_vmcs12;

	vmx->nested.cached_shaकरोw_vmcs12 = kzalloc(VMCS12_SIZE, GFP_KERNEL_ACCOUNT);
	अगर (!vmx->nested.cached_shaकरोw_vmcs12)
		जाओ out_cached_shaकरोw_vmcs12;

	अगर (enable_shaकरोw_vmcs && !alloc_shaकरोw_vmcs(vcpu))
		जाओ out_shaकरोw_vmcs;

	hrसमयr_init(&vmx->nested.preemption_समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_ABS_PINNED);
	vmx->nested.preemption_समयr.function = vmx_preemption_समयr_fn;

	vmx->nested.vpid02 = allocate_vpid();

	vmx->nested.vmcs02_initialized = false;
	vmx->nested.vmxon = true;

	अगर (vmx_pt_mode_is_host_guest()) अणु
		vmx->pt_desc.guest.ctl = 0;
		pt_update_पूर्णांकercept_क्रम_msr(vcpu);
	पूर्ण

	वापस 0;

out_shaकरोw_vmcs:
	kमुक्त(vmx->nested.cached_shaकरोw_vmcs12);

out_cached_shaकरोw_vmcs12:
	kमुक्त(vmx->nested.cached_vmcs12);

out_cached_vmcs12:
	मुक्त_loaded_vmcs(&vmx->nested.vmcs02);

out_vmcs02:
	वापस -ENOMEM;
पूर्ण

/*
 * Emulate the VMXON inकाष्ठाion.
 * Currently, we just remember that VMX is active, and करो not save or even
 * inspect the argument to VMXON (the so-called "VMXON pointer") because we
 * करो not currently need to store anything in that guest-allocated memory
 * region. Consequently, VMCLEAR and VMPTRLD also करो not verअगरy that the their
 * argument is dअगरferent from the VMXON poपूर्णांकer (which the spec says they करो).
 */
अटल पूर्णांक handle_vmon(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret;
	gpa_t vmptr;
	uपूर्णांक32_t revision;
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	स्थिर u64 VMXON_NEEDED_FEATURES = FEAT_CTL_LOCKED
		| FEAT_CTL_VMX_ENABLED_OUTSIDE_SMX;

	/*
	 * The Intel VMX Inकाष्ठाion Reference lists a bunch of bits that are
	 * prerequisite to running VMXON, most notably cr4.VMXE must be set to
	 * 1 (see vmx_is_valid_cr4() क्रम when we allow the guest to set this).
	 * Otherwise, we should fail with #UD.  But most faulting conditions
	 * have alपढ़ोy been checked by hardware, prior to the VM-निकास क्रम
	 * VMXON.  We करो test guest cr4.VMXE because processor CR4 always has
	 * that bit set to 1 in non-root mode.
	 */
	अगर (!kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_VMXE)) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 1;
	पूर्ण

	/* CPL=0 must be checked manually. */
	अगर (vmx_get_cpl(vcpu)) अणु
		kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण

	अगर (vmx->nested.vmxon)
		वापस nested_vmx_fail(vcpu, VMXERR_VMXON_IN_VMX_ROOT_OPERATION);

	अगर ((vmx->msr_ia32_feature_control & VMXON_NEEDED_FEATURES)
			!= VMXON_NEEDED_FEATURES) अणु
		kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण

	अगर (nested_vmx_get_vmptr(vcpu, &vmptr, &ret))
		वापस ret;

	/*
	 * SDM 3: 24.11.5
	 * The first 4 bytes of VMXON region contain the supported
	 * VMCS revision identअगरier
	 *
	 * Note - IA32_VMX_BASIC[48] will never be 1 क्रम the nested हाल;
	 * which replaces physical address width with 32
	 */
	अगर (!page_address_valid(vcpu, vmptr))
		वापस nested_vmx_failInvalid(vcpu);

	अगर (kvm_पढ़ो_guest(vcpu->kvm, vmptr, &revision, माप(revision)) ||
	    revision != VMCS12_REVISION)
		वापस nested_vmx_failInvalid(vcpu);

	vmx->nested.vmxon_ptr = vmptr;
	ret = enter_vmx_operation(vcpu);
	अगर (ret)
		वापस ret;

	वापस nested_vmx_succeed(vcpu);
पूर्ण

अटल अंतरभूत व्योम nested_release_vmcs12(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	अगर (vmx->nested.current_vmptr == -1ull)
		वापस;

	copy_vmcs02_to_vmcs12_rare(vcpu, get_vmcs12(vcpu));

	अगर (enable_shaकरोw_vmcs) अणु
		/* copy to memory all shaकरोwed fields in हाल
		   they were modअगरied */
		copy_shaकरोw_to_vmcs12(vmx);
		vmx_disable_shaकरोw_vmcs(vmx);
	पूर्ण
	vmx->nested.posted_पूर्णांकr_nv = -1;

	/* Flush VMCS12 to guest memory */
	kvm_vcpu_ग_लिखो_guest_page(vcpu,
				  vmx->nested.current_vmptr >> PAGE_SHIFT,
				  vmx->nested.cached_vmcs12, 0, VMCS12_SIZE);

	kvm_mmu_मुक्त_roots(vcpu, &vcpu->arch.guest_mmu, KVM_MMU_ROOTS_ALL);

	vmx->nested.current_vmptr = -1ull;
पूर्ण

/* Emulate the VMXOFF inकाष्ठाion */
अटल पूर्णांक handle_vmoff(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!nested_vmx_check_permission(vcpu))
		वापस 1;

	मुक्त_nested(vcpu);

	/* Process a latched INIT during समय CPU was in VMX operation */
	kvm_make_request(KVM_REQ_EVENT, vcpu);

	वापस nested_vmx_succeed(vcpu);
पूर्ण

/* Emulate the VMCLEAR inकाष्ठाion */
अटल पूर्णांक handle_vmclear(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u32 zero = 0;
	gpa_t vmptr;
	u64 evmcs_gpa;
	पूर्णांक r;

	अगर (!nested_vmx_check_permission(vcpu))
		वापस 1;

	अगर (nested_vmx_get_vmptr(vcpu, &vmptr, &r))
		वापस r;

	अगर (!page_address_valid(vcpu, vmptr))
		वापस nested_vmx_fail(vcpu, VMXERR_VMCLEAR_INVALID_ADDRESS);

	अगर (vmptr == vmx->nested.vmxon_ptr)
		वापस nested_vmx_fail(vcpu, VMXERR_VMCLEAR_VMXON_POINTER);

	/*
	 * When Enlightened VMEntry is enabled on the calling CPU we treat
	 * memory area poपूर्णांकer by vmptr as Enlightened VMCS (as there's no good
	 * way to distinguish it from VMCS12) and we must not corrupt it by
	 * writing to the non-existent 'launch_state' field. The area doesn't
	 * have to be the currently active EVMCS on the calling CPU and there's
	 * nothing KVM has to करो to transition it from 'active' to 'non-active'
	 * state. It is possible that the area will stay mapped as
	 * vmx->nested.hv_evmcs but this shouldn't be a problem.
	 */
	अगर (likely(!vmx->nested.enlightened_vmcs_enabled ||
		   !nested_enlightened_vmentry(vcpu, &evmcs_gpa))) अणु
		अगर (vmptr == vmx->nested.current_vmptr)
			nested_release_vmcs12(vcpu);

		kvm_vcpu_ग_लिखो_guest(vcpu,
				     vmptr + दुरत्व(काष्ठा vmcs12,
						      launch_state),
				     &zero, माप(zero));
	पूर्ण

	वापस nested_vmx_succeed(vcpu);
पूर्ण

/* Emulate the VMLAUNCH inकाष्ठाion */
अटल पूर्णांक handle_vmlaunch(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस nested_vmx_run(vcpu, true);
पूर्ण

/* Emulate the VMRESUME inकाष्ठाion */
अटल पूर्णांक handle_vmresume(काष्ठा kvm_vcpu *vcpu)
अणु

	वापस nested_vmx_run(vcpu, false);
पूर्ण

अटल पूर्णांक handle_vmपढ़ो(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vmcs12 *vmcs12 = is_guest_mode(vcpu) ? get_shaकरोw_vmcs12(vcpu)
						    : get_vmcs12(vcpu);
	अचिन्हित दीर्घ निकास_qualअगरication = vmx_get_निकास_qual(vcpu);
	u32 instr_info = vmcs_पढ़ो32(VMX_INSTRUCTION_INFO);
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा x86_exception e;
	अचिन्हित दीर्घ field;
	u64 value;
	gva_t gva = 0;
	लघु offset;
	पूर्णांक len, r;

	अगर (!nested_vmx_check_permission(vcpu))
		वापस 1;

	/*
	 * In VMX non-root operation, when the VMCS-link poपूर्णांकer is -1ull,
	 * any VMREAD sets the ALU flags क्रम VMfailInvalid.
	 */
	अगर (vmx->nested.current_vmptr == -1ull ||
	    (is_guest_mode(vcpu) &&
	     get_vmcs12(vcpu)->vmcs_link_poपूर्णांकer == -1ull))
		वापस nested_vmx_failInvalid(vcpu);

	/* Decode inकाष्ठाion info and find the field to पढ़ो */
	field = kvm_रेजिस्टर_पढ़ो(vcpu, (((instr_info) >> 28) & 0xf));

	offset = vmcs_field_to_offset(field);
	अगर (offset < 0)
		वापस nested_vmx_fail(vcpu, VMXERR_UNSUPPORTED_VMCS_COMPONENT);

	अगर (!is_guest_mode(vcpu) && is_vmcs12_ext_field(field))
		copy_vmcs02_to_vmcs12_rare(vcpu, vmcs12);

	/* Read the field, zero-extended to a u64 value */
	value = vmcs12_पढ़ो_any(vmcs12, field, offset);

	/*
	 * Now copy part of this value to रेजिस्टर or memory, as requested.
	 * Note that the number of bits actually copied is 32 or 64 depending
	 * on the guest's mode (32 or 64 bit), not on the given field's length.
	 */
	अगर (instr_info & BIT(10)) अणु
		kvm_रेजिस्टर_ग_लिखो(vcpu, (((instr_info) >> 3) & 0xf), value);
	पूर्ण अन्यथा अणु
		len = is_64_bit_mode(vcpu) ? 8 : 4;
		अगर (get_vmx_mem_address(vcpu, निकास_qualअगरication,
					instr_info, true, len, &gva))
			वापस 1;
		/* _प्रणाली ok, nested_vmx_check_permission has verअगरied cpl=0 */
		r = kvm_ग_लिखो_guest_virt_प्रणाली(vcpu, gva, &value, len, &e);
		अगर (r != X86EMUL_CONTINUE)
			वापस kvm_handle_memory_failure(vcpu, r, &e);
	पूर्ण

	वापस nested_vmx_succeed(vcpu);
पूर्ण

अटल bool is_shaकरोw_field_rw(अचिन्हित दीर्घ field)
अणु
	चयन (field) अणु
#घोषणा SHADOW_FIELD_RW(x, y) हाल x:
#समावेश "vmcs_shadow_fields.h"
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल bool is_shaकरोw_field_ro(अचिन्हित दीर्घ field)
अणु
	चयन (field) अणु
#घोषणा SHADOW_FIELD_RO(x, y) हाल x:
#समावेश "vmcs_shadow_fields.h"
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक handle_vmग_लिखो(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vmcs12 *vmcs12 = is_guest_mode(vcpu) ? get_shaकरोw_vmcs12(vcpu)
						    : get_vmcs12(vcpu);
	अचिन्हित दीर्घ निकास_qualअगरication = vmx_get_निकास_qual(vcpu);
	u32 instr_info = vmcs_पढ़ो32(VMX_INSTRUCTION_INFO);
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा x86_exception e;
	अचिन्हित दीर्घ field;
	लघु offset;
	gva_t gva;
	पूर्णांक len, r;

	/*
	 * The value to ग_लिखो might be 32 or 64 bits, depending on L1's दीर्घ
	 * mode, and eventually we need to ग_लिखो that पूर्णांकo a field of several
	 * possible lengths. The code below first zero-extends the value to 64
	 * bit (value), and then copies only the appropriate number of
	 * bits पूर्णांकo the vmcs12 field.
	 */
	u64 value = 0;

	अगर (!nested_vmx_check_permission(vcpu))
		वापस 1;

	/*
	 * In VMX non-root operation, when the VMCS-link poपूर्णांकer is -1ull,
	 * any VMWRITE sets the ALU flags क्रम VMfailInvalid.
	 */
	अगर (vmx->nested.current_vmptr == -1ull ||
	    (is_guest_mode(vcpu) &&
	     get_vmcs12(vcpu)->vmcs_link_poपूर्णांकer == -1ull))
		वापस nested_vmx_failInvalid(vcpu);

	अगर (instr_info & BIT(10))
		value = kvm_रेजिस्टर_पढ़ो(vcpu, (((instr_info) >> 3) & 0xf));
	अन्यथा अणु
		len = is_64_bit_mode(vcpu) ? 8 : 4;
		अगर (get_vmx_mem_address(vcpu, निकास_qualअगरication,
					instr_info, false, len, &gva))
			वापस 1;
		r = kvm_पढ़ो_guest_virt(vcpu, gva, &value, len, &e);
		अगर (r != X86EMUL_CONTINUE)
			वापस kvm_handle_memory_failure(vcpu, r, &e);
	पूर्ण

	field = kvm_रेजिस्टर_पढ़ो(vcpu, (((instr_info) >> 28) & 0xf));

	offset = vmcs_field_to_offset(field);
	अगर (offset < 0)
		वापस nested_vmx_fail(vcpu, VMXERR_UNSUPPORTED_VMCS_COMPONENT);

	/*
	 * If the vCPU supports "VMWRITE to any supported field in the
	 * VMCS," then the "पढ़ो-only" fields are actually पढ़ो/ग_लिखो.
	 */
	अगर (vmcs_field_पढ़ोonly(field) &&
	    !nested_cpu_has_vmग_लिखो_any_field(vcpu))
		वापस nested_vmx_fail(vcpu, VMXERR_VMWRITE_READ_ONLY_VMCS_COMPONENT);

	/*
	 * Ensure vmcs12 is up-to-date beक्रमe any VMWRITE that dirties
	 * vmcs12, अन्यथा we may crush a field or consume a stale value.
	 */
	अगर (!is_guest_mode(vcpu) && !is_shaकरोw_field_rw(field))
		copy_vmcs02_to_vmcs12_rare(vcpu, vmcs12);

	/*
	 * Some Intel CPUs पूर्णांकentionally drop the reserved bits of the AR byte
	 * fields on VMWRITE.  Emulate this behavior to ensure consistent KVM
	 * behavior regardless of the underlying hardware, e.g. अगर an AR_BYTE
	 * field is पूर्णांकercepted क्रम VMWRITE but not VMREAD (in L1), then VMREAD
	 * from L1 will वापस a dअगरferent value than VMREAD from L2 (L1 sees
	 * the stripped करोwn value, L2 sees the full value as stored by KVM).
	 */
	अगर (field >= GUEST_ES_AR_BYTES && field <= GUEST_TR_AR_BYTES)
		value &= 0x1f0ff;

	vmcs12_ग_लिखो_any(vmcs12, field, offset, value);

	/*
	 * Do not track vmcs12 dirty-state अगर in guest-mode as we actually
	 * dirty shaकरोw vmcs12 instead of vmcs12.  Fields that can be updated
	 * by L1 without a vmनिकास are always updated in the vmcs02, i.e. करोn't
	 * "dirty" vmcs12, all others go करोwn the prepare_vmcs02() slow path.
	 */
	अगर (!is_guest_mode(vcpu) && !is_shaकरोw_field_rw(field)) अणु
		/*
		 * L1 can पढ़ो these fields without निकासing, ensure the
		 * shaकरोw VMCS is up-to-date.
		 */
		अगर (enable_shaकरोw_vmcs && is_shaकरोw_field_ro(field)) अणु
			preempt_disable();
			vmcs_load(vmx->vmcs01.shaकरोw_vmcs);

			__vmcs_ग_लिखोl(field, value);

			vmcs_clear(vmx->vmcs01.shaकरोw_vmcs);
			vmcs_load(vmx->loaded_vmcs->vmcs);
			preempt_enable();
		पूर्ण
		vmx->nested.dirty_vmcs12 = true;
	पूर्ण

	वापस nested_vmx_succeed(vcpu);
पूर्ण

अटल व्योम set_current_vmptr(काष्ठा vcpu_vmx *vmx, gpa_t vmptr)
अणु
	vmx->nested.current_vmptr = vmptr;
	अगर (enable_shaकरोw_vmcs) अणु
		secondary_exec_controls_setbit(vmx, SECONDARY_EXEC_SHADOW_VMCS);
		vmcs_ग_लिखो64(VMCS_LINK_POINTER,
			     __pa(vmx->vmcs01.shaकरोw_vmcs));
		vmx->nested.need_vmcs12_to_shaकरोw_sync = true;
	पूर्ण
	vmx->nested.dirty_vmcs12 = true;
पूर्ण

/* Emulate the VMPTRLD inकाष्ठाion */
अटल पूर्णांक handle_vmptrld(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	gpa_t vmptr;
	पूर्णांक r;

	अगर (!nested_vmx_check_permission(vcpu))
		वापस 1;

	अगर (nested_vmx_get_vmptr(vcpu, &vmptr, &r))
		वापस r;

	अगर (!page_address_valid(vcpu, vmptr))
		वापस nested_vmx_fail(vcpu, VMXERR_VMPTRLD_INVALID_ADDRESS);

	अगर (vmptr == vmx->nested.vmxon_ptr)
		वापस nested_vmx_fail(vcpu, VMXERR_VMPTRLD_VMXON_POINTER);

	/* Forbid normal VMPTRLD अगर Enlightened version was used */
	अगर (vmx->nested.hv_evmcs)
		वापस 1;

	अगर (vmx->nested.current_vmptr != vmptr) अणु
		काष्ठा kvm_host_map map;
		काष्ठा vmcs12 *new_vmcs12;

		अगर (kvm_vcpu_map(vcpu, gpa_to_gfn(vmptr), &map)) अणु
			/*
			 * Reads from an unbacked page वापस all 1s,
			 * which means that the 32 bits located at the
			 * given physical address won't match the required
			 * VMCS12_REVISION identअगरier.
			 */
			वापस nested_vmx_fail(vcpu,
				VMXERR_VMPTRLD_INCORRECT_VMCS_REVISION_ID);
		पूर्ण

		new_vmcs12 = map.hva;

		अगर (new_vmcs12->hdr.revision_id != VMCS12_REVISION ||
		    (new_vmcs12->hdr.shaकरोw_vmcs &&
		     !nested_cpu_has_vmx_shaकरोw_vmcs(vcpu))) अणु
			kvm_vcpu_unmap(vcpu, &map, false);
			वापस nested_vmx_fail(vcpu,
				VMXERR_VMPTRLD_INCORRECT_VMCS_REVISION_ID);
		पूर्ण

		nested_release_vmcs12(vcpu);

		/*
		 * Load VMCS12 from guest memory since it is not alपढ़ोy
		 * cached.
		 */
		स_नकल(vmx->nested.cached_vmcs12, new_vmcs12, VMCS12_SIZE);
		kvm_vcpu_unmap(vcpu, &map, false);

		set_current_vmptr(vmx, vmptr);
	पूर्ण

	वापस nested_vmx_succeed(vcpu);
पूर्ण

/* Emulate the VMPTRST inकाष्ठाion */
अटल पूर्णांक handle_vmptrst(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ निकास_qual = vmx_get_निकास_qual(vcpu);
	u32 instr_info = vmcs_पढ़ो32(VMX_INSTRUCTION_INFO);
	gpa_t current_vmptr = to_vmx(vcpu)->nested.current_vmptr;
	काष्ठा x86_exception e;
	gva_t gva;
	पूर्णांक r;

	अगर (!nested_vmx_check_permission(vcpu))
		वापस 1;

	अगर (unlikely(to_vmx(vcpu)->nested.hv_evmcs))
		वापस 1;

	अगर (get_vmx_mem_address(vcpu, निकास_qual, instr_info,
				true, माप(gpa_t), &gva))
		वापस 1;
	/* *_प्रणाली ok, nested_vmx_check_permission has verअगरied cpl=0 */
	r = kvm_ग_लिखो_guest_virt_प्रणाली(vcpu, gva, (व्योम *)&current_vmptr,
					माप(gpa_t), &e);
	अगर (r != X86EMUL_CONTINUE)
		वापस kvm_handle_memory_failure(vcpu, r, &e);

	वापस nested_vmx_succeed(vcpu);
पूर्ण

#घोषणा EPTP_PA_MASK   GENMASK_ULL(51, 12)

अटल bool nested_ept_root_matches(hpa_t root_hpa, u64 root_eptp, u64 eptp)
अणु
	वापस VALID_PAGE(root_hpa) &&
		((root_eptp & EPTP_PA_MASK) == (eptp & EPTP_PA_MASK));
पूर्ण

/* Emulate the INVEPT inकाष्ठाion */
अटल पूर्णांक handle_invept(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u32 vmx_inकाष्ठाion_info, types;
	अचिन्हित दीर्घ type, roots_to_मुक्त;
	काष्ठा kvm_mmu *mmu;
	gva_t gva;
	काष्ठा x86_exception e;
	काष्ठा अणु
		u64 eptp, gpa;
	पूर्ण opeअक्रम;
	पूर्णांक i, r;

	अगर (!(vmx->nested.msrs.secondary_ctls_high &
	      SECONDARY_EXEC_ENABLE_EPT) ||
	    !(vmx->nested.msrs.ept_caps & VMX_EPT_INVEPT_BIT)) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 1;
	पूर्ण

	अगर (!nested_vmx_check_permission(vcpu))
		वापस 1;

	vmx_inकाष्ठाion_info = vmcs_पढ़ो32(VMX_INSTRUCTION_INFO);
	type = kvm_रेजिस्टर_पढ़ो(vcpu, (vmx_inकाष्ठाion_info >> 28) & 0xf);

	types = (vmx->nested.msrs.ept_caps >> VMX_EPT_EXTENT_SHIFT) & 6;

	अगर (type >= 32 || !(types & (1 << type)))
		वापस nested_vmx_fail(vcpu, VMXERR_INVALID_OPERAND_TO_INVEPT_INVVPID);

	/* According to the Intel VMX inकाष्ठाion reference, the memory
	 * opeअक्रम is पढ़ो even अगर it isn't needed (e.g., क्रम type==global)
	 */
	अगर (get_vmx_mem_address(vcpu, vmx_get_निकास_qual(vcpu),
			vmx_inकाष्ठाion_info, false, माप(opeअक्रम), &gva))
		वापस 1;
	r = kvm_पढ़ो_guest_virt(vcpu, gva, &opeअक्रम, माप(opeअक्रम), &e);
	अगर (r != X86EMUL_CONTINUE)
		वापस kvm_handle_memory_failure(vcpu, r, &e);

	/*
	 * Nested EPT roots are always held through guest_mmu,
	 * not root_mmu.
	 */
	mmu = &vcpu->arch.guest_mmu;

	चयन (type) अणु
	हाल VMX_EPT_EXTENT_CONTEXT:
		अगर (!nested_vmx_check_eptp(vcpu, opeअक्रम.eptp))
			वापस nested_vmx_fail(vcpu,
				VMXERR_INVALID_OPERAND_TO_INVEPT_INVVPID);

		roots_to_मुक्त = 0;
		अगर (nested_ept_root_matches(mmu->root_hpa, mmu->root_pgd,
					    opeअक्रम.eptp))
			roots_to_मुक्त |= KVM_MMU_ROOT_CURRENT;

		क्रम (i = 0; i < KVM_MMU_NUM_PREV_ROOTS; i++) अणु
			अगर (nested_ept_root_matches(mmu->prev_roots[i].hpa,
						    mmu->prev_roots[i].pgd,
						    opeअक्रम.eptp))
				roots_to_मुक्त |= KVM_MMU_ROOT_PREVIOUS(i);
		पूर्ण
		अवरोध;
	हाल VMX_EPT_EXTENT_GLOBAL:
		roots_to_मुक्त = KVM_MMU_ROOTS_ALL;
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	अगर (roots_to_मुक्त)
		kvm_mmu_मुक्त_roots(vcpu, mmu, roots_to_मुक्त);

	वापस nested_vmx_succeed(vcpu);
पूर्ण

अटल पूर्णांक handle_invvpid(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	u32 vmx_inकाष्ठाion_info;
	अचिन्हित दीर्घ type, types;
	gva_t gva;
	काष्ठा x86_exception e;
	काष्ठा अणु
		u64 vpid;
		u64 gla;
	पूर्ण opeअक्रम;
	u16 vpid02;
	पूर्णांक r;

	अगर (!(vmx->nested.msrs.secondary_ctls_high &
	      SECONDARY_EXEC_ENABLE_VPID) ||
			!(vmx->nested.msrs.vpid_caps & VMX_VPID_INVVPID_BIT)) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 1;
	पूर्ण

	अगर (!nested_vmx_check_permission(vcpu))
		वापस 1;

	vmx_inकाष्ठाion_info = vmcs_पढ़ो32(VMX_INSTRUCTION_INFO);
	type = kvm_रेजिस्टर_पढ़ो(vcpu, (vmx_inकाष्ठाion_info >> 28) & 0xf);

	types = (vmx->nested.msrs.vpid_caps &
			VMX_VPID_EXTENT_SUPPORTED_MASK) >> 8;

	अगर (type >= 32 || !(types & (1 << type)))
		वापस nested_vmx_fail(vcpu,
			VMXERR_INVALID_OPERAND_TO_INVEPT_INVVPID);

	/* according to the पूर्णांकel vmx inकाष्ठाion reference, the memory
	 * opeअक्रम is पढ़ो even अगर it isn't needed (e.g., क्रम type==global)
	 */
	अगर (get_vmx_mem_address(vcpu, vmx_get_निकास_qual(vcpu),
			vmx_inकाष्ठाion_info, false, माप(opeअक्रम), &gva))
		वापस 1;
	r = kvm_पढ़ो_guest_virt(vcpu, gva, &opeअक्रम, माप(opeअक्रम), &e);
	अगर (r != X86EMUL_CONTINUE)
		वापस kvm_handle_memory_failure(vcpu, r, &e);

	अगर (opeअक्रम.vpid >> 16)
		वापस nested_vmx_fail(vcpu,
			VMXERR_INVALID_OPERAND_TO_INVEPT_INVVPID);

	vpid02 = nested_get_vpid02(vcpu);
	चयन (type) अणु
	हाल VMX_VPID_EXTENT_INDIVIDUAL_ADDR:
		अगर (!opeअक्रम.vpid ||
		    is_noncanonical_address(opeअक्रम.gla, vcpu))
			वापस nested_vmx_fail(vcpu,
				VMXERR_INVALID_OPERAND_TO_INVEPT_INVVPID);
		vpid_sync_vcpu_addr(vpid02, opeअक्रम.gla);
		अवरोध;
	हाल VMX_VPID_EXTENT_SINGLE_CONTEXT:
	हाल VMX_VPID_EXTENT_SINGLE_NON_GLOBAL:
		अगर (!opeअक्रम.vpid)
			वापस nested_vmx_fail(vcpu,
				VMXERR_INVALID_OPERAND_TO_INVEPT_INVVPID);
		vpid_sync_context(vpid02);
		अवरोध;
	हाल VMX_VPID_EXTENT_ALL_CONTEXT:
		vpid_sync_context(vpid02);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
	पूर्ण

	/*
	 * Sync the shaकरोw page tables अगर EPT is disabled, L1 is invalidating
	 * linear mappings क्रम L2 (tagged with L2's VPID).  Free all roots as
	 * VPIDs are not tracked in the MMU role.
	 *
	 * Note, this operates on root_mmu, not guest_mmu, as L1 and L2 share
	 * an MMU when EPT is disabled.
	 *
	 * TODO: sync only the affected SPTEs क्रम INVDIVIDUAL_ADDR.
	 */
	अगर (!enable_ept)
		kvm_mmu_मुक्त_roots(vcpu, &vcpu->arch.root_mmu,
				   KVM_MMU_ROOTS_ALL);

	वापस nested_vmx_succeed(vcpu);
पूर्ण

अटल पूर्णांक nested_vmx_eptp_चयनing(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा vmcs12 *vmcs12)
अणु
	u32 index = kvm_rcx_पढ़ो(vcpu);
	u64 new_eptp;
	bool accessed_dirty;
	काष्ठा kvm_mmu *mmu = vcpu->arch.walk_mmu;

	अगर (!nested_cpu_has_eptp_चयनing(vmcs12) ||
	    !nested_cpu_has_ept(vmcs12))
		वापस 1;

	अगर (index >= VMFUNC_EPTP_ENTRIES)
		वापस 1;


	अगर (kvm_vcpu_पढ़ो_guest_page(vcpu, vmcs12->eptp_list_address >> PAGE_SHIFT,
				     &new_eptp, index * 8, 8))
		वापस 1;

	accessed_dirty = !!(new_eptp & VMX_EPTP_AD_ENABLE_BIT);

	/*
	 * If the (L2) guest करोes a vmfunc to the currently
	 * active ept poपूर्णांकer, we करोn't have to करो anything अन्यथा
	 */
	अगर (vmcs12->ept_poपूर्णांकer != new_eptp) अणु
		अगर (!nested_vmx_check_eptp(vcpu, new_eptp))
			वापस 1;

		mmu->ept_ad = accessed_dirty;
		mmu->mmu_role.base.ad_disabled = !accessed_dirty;
		vmcs12->ept_poपूर्णांकer = new_eptp;

		kvm_make_request(KVM_REQ_MMU_RELOAD, vcpu);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक handle_vmfunc(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा vmcs12 *vmcs12;
	u32 function = kvm_rax_पढ़ो(vcpu);

	/*
	 * VMFUNC is only supported क्रम nested guests, but we always enable the
	 * secondary control क्रम simplicity; क्रम non-nested mode, fake that we
	 * didn't by injecting #UD.
	 */
	अगर (!is_guest_mode(vcpu)) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 1;
	पूर्ण

	vmcs12 = get_vmcs12(vcpu);
	अगर ((vmcs12->vm_function_control & (1 << function)) == 0)
		जाओ fail;

	चयन (function) अणु
	हाल 0:
		अगर (nested_vmx_eptp_चयनing(vcpu, vmcs12))
			जाओ fail;
		अवरोध;
	शेष:
		जाओ fail;
	पूर्ण
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);

fail:
	/*
	 * This is effectively a reflected VM-Exit, as opposed to a synthesized
	 * nested VM-Exit.  Pass the original निकास reason, i.e. करोn't hardcode
	 * EXIT_REASON_VMFUNC as the निकास reason.
	 */
	nested_vmx_vmनिकास(vcpu, vmx->निकास_reason.full,
			  vmx_get_पूर्णांकr_info(vcpu),
			  vmx_get_निकास_qual(vcpu));
	वापस 1;
पूर्ण

/*
 * Return true अगर an IO inकाष्ठाion with the specअगरied port and size should cause
 * a VM-निकास पूर्णांकo L1.
 */
bool nested_vmx_check_io_biपंचांगaps(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक port,
				 पूर्णांक size)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	gpa_t biपंचांगap, last_biपंचांगap;
	u8 b;

	last_biपंचांगap = (gpa_t)-1;
	b = -1;

	जबतक (size > 0) अणु
		अगर (port < 0x8000)
			biपंचांगap = vmcs12->io_biपंचांगap_a;
		अन्यथा अगर (port < 0x10000)
			biपंचांगap = vmcs12->io_biपंचांगap_b;
		अन्यथा
			वापस true;
		biपंचांगap += (port & 0x7fff) / 8;

		अगर (last_biपंचांगap != biपंचांगap)
			अगर (kvm_vcpu_पढ़ो_guest(vcpu, biपंचांगap, &b, 1))
				वापस true;
		अगर (b & (1 << (port & 7)))
			वापस true;

		port++;
		size--;
		last_biपंचांगap = biपंचांगap;
	पूर्ण

	वापस false;
पूर्ण

अटल bool nested_vmx_निकास_handled_io(काष्ठा kvm_vcpu *vcpu,
				       काष्ठा vmcs12 *vmcs12)
अणु
	अचिन्हित दीर्घ निकास_qualअगरication;
	अचिन्हित लघु port;
	पूर्णांक size;

	अगर (!nested_cpu_has(vmcs12, CPU_BASED_USE_IO_BITMAPS))
		वापस nested_cpu_has(vmcs12, CPU_BASED_UNCOND_IO_EXITING);

	निकास_qualअगरication = vmx_get_निकास_qual(vcpu);

	port = निकास_qualअगरication >> 16;
	size = (निकास_qualअगरication & 7) + 1;

	वापस nested_vmx_check_io_biपंचांगaps(vcpu, port, size);
पूर्ण

/*
 * Return 1 अगर we should निकास from L2 to L1 to handle an MSR access,
 * rather than handle it ourselves in L0. I.e., check whether L1 expressed
 * disपूर्णांकerest in the current event (पढ़ो or ग_लिखो a specअगरic MSR) by using an
 * MSR biपंचांगap. This may be the हाल even when L0 करोesn't use MSR biपंचांगaps.
 */
अटल bool nested_vmx_निकास_handled_msr(काष्ठा kvm_vcpu *vcpu,
					काष्ठा vmcs12 *vmcs12,
					जोड़ vmx_निकास_reason निकास_reason)
अणु
	u32 msr_index = kvm_rcx_पढ़ो(vcpu);
	gpa_t biपंचांगap;

	अगर (!nested_cpu_has(vmcs12, CPU_BASED_USE_MSR_BITMAPS))
		वापस true;

	/*
	 * The MSR_BITMAP page is भागided पूर्णांकo four 1024-byte biपंचांगaps,
	 * क्रम the four combinations of पढ़ो/ग_लिखो and low/high MSR numbers.
	 * First we need to figure out which of the four to use:
	 */
	biपंचांगap = vmcs12->msr_biपंचांगap;
	अगर (निकास_reason.basic == EXIT_REASON_MSR_WRITE)
		biपंचांगap += 2048;
	अगर (msr_index >= 0xc0000000) अणु
		msr_index -= 0xc0000000;
		biपंचांगap += 1024;
	पूर्ण

	/* Then पढ़ो the msr_index'th bit from this biपंचांगap: */
	अगर (msr_index < 1024*8) अणु
		अचिन्हित अक्षर b;
		अगर (kvm_vcpu_पढ़ो_guest(vcpu, biपंचांगap + msr_index/8, &b, 1))
			वापस true;
		वापस 1 & (b >> (msr_index & 7));
	पूर्ण अन्यथा
		वापस true; /* let L1 handle the wrong parameter */
पूर्ण

/*
 * Return 1 अगर we should निकास from L2 to L1 to handle a CR access निकास,
 * rather than handle it ourselves in L0. I.e., check अगर L1 wanted to
 * पूर्णांकercept (via guest_host_mask etc.) the current event.
 */
अटल bool nested_vmx_निकास_handled_cr(काष्ठा kvm_vcpu *vcpu,
	काष्ठा vmcs12 *vmcs12)
अणु
	अचिन्हित दीर्घ निकास_qualअगरication = vmx_get_निकास_qual(vcpu);
	पूर्णांक cr = निकास_qualअगरication & 15;
	पूर्णांक reg;
	अचिन्हित दीर्घ val;

	चयन ((निकास_qualअगरication >> 4) & 3) अणु
	हाल 0: /* mov to cr */
		reg = (निकास_qualअगरication >> 8) & 15;
		val = kvm_रेजिस्टर_पढ़ो(vcpu, reg);
		चयन (cr) अणु
		हाल 0:
			अगर (vmcs12->cr0_guest_host_mask &
			    (val ^ vmcs12->cr0_पढ़ो_shaकरोw))
				वापस true;
			अवरोध;
		हाल 3:
			अगर (nested_cpu_has(vmcs12, CPU_BASED_CR3_LOAD_EXITING))
				वापस true;
			अवरोध;
		हाल 4:
			अगर (vmcs12->cr4_guest_host_mask &
			    (vmcs12->cr4_पढ़ो_shaकरोw ^ val))
				वापस true;
			अवरोध;
		हाल 8:
			अगर (nested_cpu_has(vmcs12, CPU_BASED_CR8_LOAD_EXITING))
				वापस true;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 2: /* clts */
		अगर ((vmcs12->cr0_guest_host_mask & X86_CR0_TS) &&
		    (vmcs12->cr0_पढ़ो_shaकरोw & X86_CR0_TS))
			वापस true;
		अवरोध;
	हाल 1: /* mov from cr */
		चयन (cr) अणु
		हाल 3:
			अगर (vmcs12->cpu_based_vm_exec_control &
			    CPU_BASED_CR3_STORE_EXITING)
				वापस true;
			अवरोध;
		हाल 8:
			अगर (vmcs12->cpu_based_vm_exec_control &
			    CPU_BASED_CR8_STORE_EXITING)
				वापस true;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 3: /* lmsw */
		/*
		 * lmsw can change bits 1..3 of cr0, and only set bit 0 of
		 * cr0. Other attempted changes are ignored, with no निकास.
		 */
		val = (निकास_qualअगरication >> LMSW_SOURCE_DATA_SHIFT) & 0x0f;
		अगर (vmcs12->cr0_guest_host_mask & 0xe &
		    (val ^ vmcs12->cr0_पढ़ो_shaकरोw))
			वापस true;
		अगर ((vmcs12->cr0_guest_host_mask & 0x1) &&
		    !(vmcs12->cr0_पढ़ो_shaकरोw & 0x1) &&
		    (val & 0x1))
			वापस true;
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल bool nested_vmx_निकास_handled_encls(काष्ठा kvm_vcpu *vcpu,
					  काष्ठा vmcs12 *vmcs12)
अणु
	u32 encls_leaf;

	अगर (!guest_cpuid_has(vcpu, X86_FEATURE_SGX) ||
	    !nested_cpu_has2(vmcs12, SECONDARY_EXEC_ENCLS_EXITING))
		वापस false;

	encls_leaf = kvm_rax_पढ़ो(vcpu);
	अगर (encls_leaf > 62)
		encls_leaf = 63;
	वापस vmcs12->encls_निकासing_biपंचांगap & BIT_ULL(encls_leaf);
पूर्ण

अटल bool nested_vmx_निकास_handled_vmcs_access(काष्ठा kvm_vcpu *vcpu,
	काष्ठा vmcs12 *vmcs12, gpa_t biपंचांगap)
अणु
	u32 vmx_inकाष्ठाion_info;
	अचिन्हित दीर्घ field;
	u8 b;

	अगर (!nested_cpu_has_shaकरोw_vmcs(vmcs12))
		वापस true;

	/* Decode inकाष्ठाion info and find the field to access */
	vmx_inकाष्ठाion_info = vmcs_पढ़ो32(VMX_INSTRUCTION_INFO);
	field = kvm_रेजिस्टर_पढ़ो(vcpu, (((vmx_inकाष्ठाion_info) >> 28) & 0xf));

	/* Out-of-range fields always cause a VM निकास from L2 to L1 */
	अगर (field >> 15)
		वापस true;

	अगर (kvm_vcpu_पढ़ो_guest(vcpu, biपंचांगap + field/8, &b, 1))
		वापस true;

	वापस 1 & (b >> (field & 7));
पूर्ण

अटल bool nested_vmx_निकास_handled_mtf(काष्ठा vmcs12 *vmcs12)
अणु
	u32 entry_पूर्णांकr_info = vmcs12->vm_entry_पूर्णांकr_info_field;

	अगर (nested_cpu_has_mtf(vmcs12))
		वापस true;

	/*
	 * An MTF VM-निकास may be injected पूर्णांकo the guest by setting the
	 * पूर्णांकerruption-type to 7 (other event) and the vector field to 0. Such
	 * is the हाल regardless of the 'monitor trap flag' VM-execution
	 * control.
	 */
	वापस entry_पूर्णांकr_info == (INTR_INFO_VALID_MASK
				   | INTR_TYPE_OTHER_EVENT);
पूर्ण

/*
 * Return true अगर L0 wants to handle an निकास from L2 regardless of whether or not
 * L1 wants the निकास.  Only call this when in is_guest_mode (L2).
 */
अटल bool nested_vmx_l0_wants_निकास(काष्ठा kvm_vcpu *vcpu,
				     जोड़ vmx_निकास_reason निकास_reason)
अणु
	u32 पूर्णांकr_info;

	चयन ((u16)निकास_reason.basic) अणु
	हाल EXIT_REASON_EXCEPTION_NMI:
		पूर्णांकr_info = vmx_get_पूर्णांकr_info(vcpu);
		अगर (is_nmi(पूर्णांकr_info))
			वापस true;
		अन्यथा अगर (is_page_fault(पूर्णांकr_info))
			वापस vcpu->arch.apf.host_apf_flags || !enable_ept;
		अन्यथा अगर (is_debug(पूर्णांकr_info) &&
			 vcpu->guest_debug &
			 (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP))
			वापस true;
		अन्यथा अगर (is_अवरोधpoपूर्णांक(पूर्णांकr_info) &&
			 vcpu->guest_debug & KVM_GUESTDBG_USE_SW_BP)
			वापस true;
		वापस false;
	हाल EXIT_REASON_EXTERNAL_INTERRUPT:
		वापस true;
	हाल EXIT_REASON_MCE_DURING_VMENTRY:
		वापस true;
	हाल EXIT_REASON_EPT_VIOLATION:
		/*
		 * L0 always deals with the EPT violation. If nested EPT is
		 * used, and the nested mmu code discovers that the address is
		 * missing in the guest EPT table (EPT12), the EPT violation
		 * will be injected with nested_ept_inject_page_fault()
		 */
		वापस true;
	हाल EXIT_REASON_EPT_MISCONFIG:
		/*
		 * L2 never uses directly L1's EPT, but rather L0's own EPT
		 * table (shaकरोw on EPT) or a merged EPT table that L0 built
		 * (EPT on EPT). So any problems with the काष्ठाure of the
		 * table is L0's fault.
		 */
		वापस true;
	हाल EXIT_REASON_PREEMPTION_TIMER:
		वापस true;
	हाल EXIT_REASON_PML_FULL:
		/*
		 * PML is emulated क्रम an L1 VMM and should never be enabled in
		 * vmcs02, always "handle" PML_FULL by निकासing to userspace.
		 */
		वापस true;
	हाल EXIT_REASON_VMFUNC:
		/* VM functions are emulated through L2->L0 vmनिकासs. */
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Return 1 अगर L1 wants to पूर्णांकercept an निकास from L2.  Only call this when in
 * is_guest_mode (L2).
 */
अटल bool nested_vmx_l1_wants_निकास(काष्ठा kvm_vcpu *vcpu,
				     जोड़ vmx_निकास_reason निकास_reason)
अणु
	काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);
	u32 पूर्णांकr_info;

	चयन ((u16)निकास_reason.basic) अणु
	हाल EXIT_REASON_EXCEPTION_NMI:
		पूर्णांकr_info = vmx_get_पूर्णांकr_info(vcpu);
		अगर (is_nmi(पूर्णांकr_info))
			वापस true;
		अन्यथा अगर (is_page_fault(पूर्णांकr_info))
			वापस true;
		वापस vmcs12->exception_biपंचांगap &
				(1u << (पूर्णांकr_info & INTR_INFO_VECTOR_MASK));
	हाल EXIT_REASON_EXTERNAL_INTERRUPT:
		वापस nested_निकास_on_पूर्णांकr(vcpu);
	हाल EXIT_REASON_TRIPLE_FAULT:
		वापस true;
	हाल EXIT_REASON_INTERRUPT_WINDOW:
		वापस nested_cpu_has(vmcs12, CPU_BASED_INTR_WINDOW_EXITING);
	हाल EXIT_REASON_NMI_WINDOW:
		वापस nested_cpu_has(vmcs12, CPU_BASED_NMI_WINDOW_EXITING);
	हाल EXIT_REASON_TASK_SWITCH:
		वापस true;
	हाल EXIT_REASON_CPUID:
		वापस true;
	हाल EXIT_REASON_HLT:
		वापस nested_cpu_has(vmcs12, CPU_BASED_HLT_EXITING);
	हाल EXIT_REASON_INVD:
		वापस true;
	हाल EXIT_REASON_INVLPG:
		वापस nested_cpu_has(vmcs12, CPU_BASED_INVLPG_EXITING);
	हाल EXIT_REASON_RDPMC:
		वापस nested_cpu_has(vmcs12, CPU_BASED_RDPMC_EXITING);
	हाल EXIT_REASON_RDRAND:
		वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_RDRAND_EXITING);
	हाल EXIT_REASON_RDSEED:
		वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_RDSEED_EXITING);
	हाल EXIT_REASON_RDTSC: हाल EXIT_REASON_RDTSCP:
		वापस nested_cpu_has(vmcs12, CPU_BASED_RDTSC_EXITING);
	हाल EXIT_REASON_VMREAD:
		वापस nested_vmx_निकास_handled_vmcs_access(vcpu, vmcs12,
			vmcs12->vmपढ़ो_biपंचांगap);
	हाल EXIT_REASON_VMWRITE:
		वापस nested_vmx_निकास_handled_vmcs_access(vcpu, vmcs12,
			vmcs12->vmग_लिखो_biपंचांगap);
	हाल EXIT_REASON_VMCALL: हाल EXIT_REASON_VMCLEAR:
	हाल EXIT_REASON_VMLAUNCH: हाल EXIT_REASON_VMPTRLD:
	हाल EXIT_REASON_VMPTRST: हाल EXIT_REASON_VMRESUME:
	हाल EXIT_REASON_VMOFF: हाल EXIT_REASON_VMON:
	हाल EXIT_REASON_INVEPT: हाल EXIT_REASON_INVVPID:
		/*
		 * VMX inकाष्ठाions trap unconditionally. This allows L1 to
		 * emulate them क्रम its L2 guest, i.e., allows 3-level nesting!
		 */
		वापस true;
	हाल EXIT_REASON_CR_ACCESS:
		वापस nested_vmx_निकास_handled_cr(vcpu, vmcs12);
	हाल EXIT_REASON_DR_ACCESS:
		वापस nested_cpu_has(vmcs12, CPU_BASED_MOV_DR_EXITING);
	हाल EXIT_REASON_IO_INSTRUCTION:
		वापस nested_vmx_निकास_handled_io(vcpu, vmcs12);
	हाल EXIT_REASON_GDTR_IDTR: हाल EXIT_REASON_LDTR_TR:
		वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_DESC);
	हाल EXIT_REASON_MSR_READ:
	हाल EXIT_REASON_MSR_WRITE:
		वापस nested_vmx_निकास_handled_msr(vcpu, vmcs12, निकास_reason);
	हाल EXIT_REASON_INVALID_STATE:
		वापस true;
	हाल EXIT_REASON_MWAIT_INSTRUCTION:
		वापस nested_cpu_has(vmcs12, CPU_BASED_MWAIT_EXITING);
	हाल EXIT_REASON_MONITOR_TRAP_FLAG:
		वापस nested_vmx_निकास_handled_mtf(vmcs12);
	हाल EXIT_REASON_MONITOR_INSTRUCTION:
		वापस nested_cpu_has(vmcs12, CPU_BASED_MONITOR_EXITING);
	हाल EXIT_REASON_PAUSE_INSTRUCTION:
		वापस nested_cpu_has(vmcs12, CPU_BASED_PAUSE_EXITING) ||
			nested_cpu_has2(vmcs12,
				SECONDARY_EXEC_PAUSE_LOOP_EXITING);
	हाल EXIT_REASON_MCE_DURING_VMENTRY:
		वापस true;
	हाल EXIT_REASON_TPR_BELOW_THRESHOLD:
		वापस nested_cpu_has(vmcs12, CPU_BASED_TPR_SHADOW);
	हाल EXIT_REASON_APIC_ACCESS:
	हाल EXIT_REASON_APIC_WRITE:
	हाल EXIT_REASON_EOI_INDUCED:
		/*
		 * The controls क्रम "virtualize APIC accesses," "APIC-
		 * रेजिस्टर भवization," and "भव-पूर्णांकerrupt
		 * delivery" only come from vmcs12.
		 */
		वापस true;
	हाल EXIT_REASON_INVPCID:
		वापस
			nested_cpu_has2(vmcs12, SECONDARY_EXEC_ENABLE_INVPCID) &&
			nested_cpu_has(vmcs12, CPU_BASED_INVLPG_EXITING);
	हाल EXIT_REASON_WBINVD:
		वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_WBINVD_EXITING);
	हाल EXIT_REASON_XSETBV:
		वापस true;
	हाल EXIT_REASON_XSAVES: हाल EXIT_REASON_XRSTORS:
		/*
		 * This should never happen, since it is not possible to
		 * set XSS to a non-zero value---neither in L1 nor in L2.
		 * If अगर it were, XSS would have to be checked against
		 * the XSS निकास biपंचांगap in vmcs12.
		 */
		वापस nested_cpu_has2(vmcs12, SECONDARY_EXEC_XSAVES);
	हाल EXIT_REASON_UMWAIT:
	हाल EXIT_REASON_TPAUSE:
		वापस nested_cpu_has2(vmcs12,
			SECONDARY_EXEC_ENABLE_USR_WAIT_PAUSE);
	हाल EXIT_REASON_ENCLS:
		वापस nested_vmx_निकास_handled_encls(vcpu, vmcs12);
	शेष:
		वापस true;
	पूर्ण
पूर्ण

/*
 * Conditionally reflect a VM-Exit पूर्णांकo L1.  Returns %true अगर the VM-Exit was
 * reflected पूर्णांकo L1.
 */
bool nested_vmx_reflect_vmनिकास(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	जोड़ vmx_निकास_reason निकास_reason = vmx->निकास_reason;
	अचिन्हित दीर्घ निकास_qual;
	u32 निकास_पूर्णांकr_info;

	WARN_ON_ONCE(vmx->nested.nested_run_pending);

	/*
	 * Late nested VM-Fail shares the same flow as nested VM-Exit since KVM
	 * has alपढ़ोy loaded L2's state.
	 */
	अगर (unlikely(vmx->fail)) अणु
		trace_kvm_nested_vmenter_failed(
			"hardware VM-instruction error: ",
			vmcs_पढ़ो32(VM_INSTRUCTION_ERROR));
		निकास_पूर्णांकr_info = 0;
		निकास_qual = 0;
		जाओ reflect_vmनिकास;
	पूर्ण

	trace_kvm_nested_vmनिकास(निकास_reason.full, vcpu, KVM_ISA_VMX);

	/* If L0 (KVM) wants the निकास, it trumps L1's desires. */
	अगर (nested_vmx_l0_wants_निकास(vcpu, निकास_reason))
		वापस false;

	/* If L1 करोesn't want the निकास, handle it in L0. */
	अगर (!nested_vmx_l1_wants_निकास(vcpu, निकास_reason))
		वापस false;

	/*
	 * vmcs.VM_EXIT_INTR_INFO is only valid क्रम EXCEPTION_NMI निकासs.  For
	 * EXTERNAL_INTERRUPT, the value क्रम vmcs12->vm_निकास_पूर्णांकr_info would
	 * need to be synthesized by querying the in-kernel LAPIC, but बाह्यal
	 * पूर्णांकerrupts are never reflected to L1 so it's a non-issue.
	 */
	निकास_पूर्णांकr_info = vmx_get_पूर्णांकr_info(vcpu);
	अगर (is_exception_with_error_code(निकास_पूर्णांकr_info)) अणु
		काष्ठा vmcs12 *vmcs12 = get_vmcs12(vcpu);

		vmcs12->vm_निकास_पूर्णांकr_error_code =
			vmcs_पढ़ो32(VM_EXIT_INTR_ERROR_CODE);
	पूर्ण
	निकास_qual = vmx_get_निकास_qual(vcpu);

reflect_vmनिकास:
	nested_vmx_vmनिकास(vcpu, निकास_reason.full, निकास_पूर्णांकr_info, निकास_qual);
	वापस true;
पूर्ण

अटल पूर्णांक vmx_get_nested_state(काष्ठा kvm_vcpu *vcpu,
				काष्ठा kvm_nested_state __user *user_kvm_nested_state,
				u32 user_data_size)
अणु
	काष्ठा vcpu_vmx *vmx;
	काष्ठा vmcs12 *vmcs12;
	काष्ठा kvm_nested_state kvm_state = अणु
		.flags = 0,
		.क्रमmat = KVM_STATE_NESTED_FORMAT_VMX,
		.size = माप(kvm_state),
		.hdr.vmx.flags = 0,
		.hdr.vmx.vmxon_pa = -1ull,
		.hdr.vmx.vmcs12_pa = -1ull,
		.hdr.vmx.preemption_समयr_deadline = 0,
	पूर्ण;
	काष्ठा kvm_vmx_nested_state_data __user *user_vmx_nested_state =
		&user_kvm_nested_state->data.vmx[0];

	अगर (!vcpu)
		वापस kvm_state.size + माप(*user_vmx_nested_state);

	vmx = to_vmx(vcpu);
	vmcs12 = get_vmcs12(vcpu);

	अगर (nested_vmx_allowed(vcpu) &&
	    (vmx->nested.vmxon || vmx->nested.smm.vmxon)) अणु
		kvm_state.hdr.vmx.vmxon_pa = vmx->nested.vmxon_ptr;
		kvm_state.hdr.vmx.vmcs12_pa = vmx->nested.current_vmptr;

		अगर (vmx_has_valid_vmcs12(vcpu)) अणु
			kvm_state.size += माप(user_vmx_nested_state->vmcs12);

			अगर (vmx->nested.hv_evmcs)
				kvm_state.flags |= KVM_STATE_NESTED_EVMCS;

			अगर (is_guest_mode(vcpu) &&
			    nested_cpu_has_shaकरोw_vmcs(vmcs12) &&
			    vmcs12->vmcs_link_poपूर्णांकer != -1ull)
				kvm_state.size += माप(user_vmx_nested_state->shaकरोw_vmcs12);
		पूर्ण

		अगर (vmx->nested.smm.vmxon)
			kvm_state.hdr.vmx.smm.flags |= KVM_STATE_NESTED_SMM_VMXON;

		अगर (vmx->nested.smm.guest_mode)
			kvm_state.hdr.vmx.smm.flags |= KVM_STATE_NESTED_SMM_GUEST_MODE;

		अगर (is_guest_mode(vcpu)) अणु
			kvm_state.flags |= KVM_STATE_NESTED_GUEST_MODE;

			अगर (vmx->nested.nested_run_pending)
				kvm_state.flags |= KVM_STATE_NESTED_RUN_PENDING;

			अगर (vmx->nested.mtf_pending)
				kvm_state.flags |= KVM_STATE_NESTED_MTF_PENDING;

			अगर (nested_cpu_has_preemption_समयr(vmcs12) &&
			    vmx->nested.has_preemption_समयr_deadline) अणु
				kvm_state.hdr.vmx.flags |=
					KVM_STATE_VMX_PREEMPTION_TIMER_DEADLINE;
				kvm_state.hdr.vmx.preemption_समयr_deadline =
					vmx->nested.preemption_समयr_deadline;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (user_data_size < kvm_state.size)
		जाओ out;

	अगर (copy_to_user(user_kvm_nested_state, &kvm_state, माप(kvm_state)))
		वापस -EFAULT;

	अगर (!vmx_has_valid_vmcs12(vcpu))
		जाओ out;

	/*
	 * When running L2, the authoritative vmcs12 state is in the
	 * vmcs02. When running L1, the authoritative vmcs12 state is
	 * in the shaकरोw or enlightened vmcs linked to vmcs01, unless
	 * need_vmcs12_to_shaकरोw_sync is set, in which हाल, the authoritative
	 * vmcs12 state is in the vmcs12 alपढ़ोy.
	 */
	अगर (is_guest_mode(vcpu)) अणु
		sync_vmcs02_to_vmcs12(vcpu, vmcs12);
		sync_vmcs02_to_vmcs12_rare(vcpu, vmcs12);
	पूर्ण अन्यथा  अणु
		copy_vmcs02_to_vmcs12_rare(vcpu, get_vmcs12(vcpu));
		अगर (!vmx->nested.need_vmcs12_to_shaकरोw_sync) अणु
			अगर (vmx->nested.hv_evmcs)
				copy_enlightened_to_vmcs12(vmx);
			अन्यथा अगर (enable_shaकरोw_vmcs)
				copy_shaकरोw_to_vmcs12(vmx);
		पूर्ण
	पूर्ण

	BUILD_BUG_ON(माप(user_vmx_nested_state->vmcs12) < VMCS12_SIZE);
	BUILD_BUG_ON(माप(user_vmx_nested_state->shaकरोw_vmcs12) < VMCS12_SIZE);

	/*
	 * Copy over the full allocated size of vmcs12 rather than just the size
	 * of the काष्ठा.
	 */
	अगर (copy_to_user(user_vmx_nested_state->vmcs12, vmcs12, VMCS12_SIZE))
		वापस -EFAULT;

	अगर (nested_cpu_has_shaकरोw_vmcs(vmcs12) &&
	    vmcs12->vmcs_link_poपूर्णांकer != -1ull) अणु
		अगर (copy_to_user(user_vmx_nested_state->shaकरोw_vmcs12,
				 get_shaकरोw_vmcs12(vcpu), VMCS12_SIZE))
			वापस -EFAULT;
	पूर्ण
out:
	वापस kvm_state.size;
पूर्ण

/*
 * Forcibly leave nested mode in order to be able to reset the VCPU later on.
 */
व्योम vmx_leave_nested(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (is_guest_mode(vcpu)) अणु
		to_vmx(vcpu)->nested.nested_run_pending = 0;
		nested_vmx_vmनिकास(vcpu, -1, 0, 0);
	पूर्ण
	मुक्त_nested(vcpu);
पूर्ण

अटल पूर्णांक vmx_set_nested_state(काष्ठा kvm_vcpu *vcpu,
				काष्ठा kvm_nested_state __user *user_kvm_nested_state,
				काष्ठा kvm_nested_state *kvm_state)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	काष्ठा vmcs12 *vmcs12;
	क्रमागत vm_entry_failure_code ignored;
	काष्ठा kvm_vmx_nested_state_data __user *user_vmx_nested_state =
		&user_kvm_nested_state->data.vmx[0];
	पूर्णांक ret;

	अगर (kvm_state->क्रमmat != KVM_STATE_NESTED_FORMAT_VMX)
		वापस -EINVAL;

	अगर (kvm_state->hdr.vmx.vmxon_pa == -1ull) अणु
		अगर (kvm_state->hdr.vmx.smm.flags)
			वापस -EINVAL;

		अगर (kvm_state->hdr.vmx.vmcs12_pa != -1ull)
			वापस -EINVAL;

		/*
		 * KVM_STATE_NESTED_EVMCS used to संकेत that KVM should
		 * enable eVMCS capability on vCPU. However, since then
		 * code was changed such that flag संकेतs vmcs12 should
		 * be copied पूर्णांकo eVMCS in guest memory.
		 *
		 * To preserve backwards compatability, allow user
		 * to set this flag even when there is no VMXON region.
		 */
		अगर (kvm_state->flags & ~KVM_STATE_NESTED_EVMCS)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (!nested_vmx_allowed(vcpu))
			वापस -EINVAL;

		अगर (!page_address_valid(vcpu, kvm_state->hdr.vmx.vmxon_pa))
			वापस -EINVAL;
	पूर्ण

	अगर ((kvm_state->hdr.vmx.smm.flags & KVM_STATE_NESTED_SMM_GUEST_MODE) &&
	    (kvm_state->flags & KVM_STATE_NESTED_GUEST_MODE))
		वापस -EINVAL;

	अगर (kvm_state->hdr.vmx.smm.flags &
	    ~(KVM_STATE_NESTED_SMM_GUEST_MODE | KVM_STATE_NESTED_SMM_VMXON))
		वापस -EINVAL;

	अगर (kvm_state->hdr.vmx.flags & ~KVM_STATE_VMX_PREEMPTION_TIMER_DEADLINE)
		वापस -EINVAL;

	/*
	 * SMM temporarily disables VMX, so we cannot be in guest mode,
	 * nor can VMLAUNCH/VMRESUME be pending.  Outside SMM, SMM flags
	 * must be zero.
	 */
	अगर (is_smm(vcpu) ?
		(kvm_state->flags &
		 (KVM_STATE_NESTED_GUEST_MODE | KVM_STATE_NESTED_RUN_PENDING))
		: kvm_state->hdr.vmx.smm.flags)
		वापस -EINVAL;

	अगर ((kvm_state->hdr.vmx.smm.flags & KVM_STATE_NESTED_SMM_GUEST_MODE) &&
	    !(kvm_state->hdr.vmx.smm.flags & KVM_STATE_NESTED_SMM_VMXON))
		वापस -EINVAL;

	अगर ((kvm_state->flags & KVM_STATE_NESTED_EVMCS) &&
		(!nested_vmx_allowed(vcpu) || !vmx->nested.enlightened_vmcs_enabled))
			वापस -EINVAL;

	vmx_leave_nested(vcpu);

	अगर (kvm_state->hdr.vmx.vmxon_pa == -1ull)
		वापस 0;

	vmx->nested.vmxon_ptr = kvm_state->hdr.vmx.vmxon_pa;
	ret = enter_vmx_operation(vcpu);
	अगर (ret)
		वापस ret;

	/* Empty 'VMXON' state is permitted अगर no VMCS loaded */
	अगर (kvm_state->size < माप(*kvm_state) + माप(*vmcs12)) अणु
		/* See vmx_has_valid_vmcs12.  */
		अगर ((kvm_state->flags & KVM_STATE_NESTED_GUEST_MODE) ||
		    (kvm_state->flags & KVM_STATE_NESTED_EVMCS) ||
		    (kvm_state->hdr.vmx.vmcs12_pa != -1ull))
			वापस -EINVAL;
		अन्यथा
			वापस 0;
	पूर्ण

	अगर (kvm_state->hdr.vmx.vmcs12_pa != -1ull) अणु
		अगर (kvm_state->hdr.vmx.vmcs12_pa == kvm_state->hdr.vmx.vmxon_pa ||
		    !page_address_valid(vcpu, kvm_state->hdr.vmx.vmcs12_pa))
			वापस -EINVAL;

		set_current_vmptr(vmx, kvm_state->hdr.vmx.vmcs12_pa);
	पूर्ण अन्यथा अगर (kvm_state->flags & KVM_STATE_NESTED_EVMCS) अणु
		/*
		 * nested_vmx_handle_enlightened_vmptrld() cannot be called
		 * directly from here as HV_X64_MSR_VP_ASSIST_PAGE may not be
		 * restored yet. EVMCS will be mapped from
		 * nested_get_vmcs12_pages().
		 */
		kvm_make_request(KVM_REQ_GET_NESTED_STATE_PAGES, vcpu);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (kvm_state->hdr.vmx.smm.flags & KVM_STATE_NESTED_SMM_VMXON) अणु
		vmx->nested.smm.vmxon = true;
		vmx->nested.vmxon = false;

		अगर (kvm_state->hdr.vmx.smm.flags & KVM_STATE_NESTED_SMM_GUEST_MODE)
			vmx->nested.smm.guest_mode = true;
	पूर्ण

	vmcs12 = get_vmcs12(vcpu);
	अगर (copy_from_user(vmcs12, user_vmx_nested_state->vmcs12, माप(*vmcs12)))
		वापस -EFAULT;

	अगर (vmcs12->hdr.revision_id != VMCS12_REVISION)
		वापस -EINVAL;

	अगर (!(kvm_state->flags & KVM_STATE_NESTED_GUEST_MODE))
		वापस 0;

	vmx->nested.nested_run_pending =
		!!(kvm_state->flags & KVM_STATE_NESTED_RUN_PENDING);

	vmx->nested.mtf_pending =
		!!(kvm_state->flags & KVM_STATE_NESTED_MTF_PENDING);

	ret = -EINVAL;
	अगर (nested_cpu_has_shaकरोw_vmcs(vmcs12) &&
	    vmcs12->vmcs_link_poपूर्णांकer != -1ull) अणु
		काष्ठा vmcs12 *shaकरोw_vmcs12 = get_shaकरोw_vmcs12(vcpu);

		अगर (kvm_state->size <
		    माप(*kvm_state) +
		    माप(user_vmx_nested_state->vmcs12) + माप(*shaकरोw_vmcs12))
			जाओ error_guest_mode;

		अगर (copy_from_user(shaकरोw_vmcs12,
				   user_vmx_nested_state->shaकरोw_vmcs12,
				   माप(*shaकरोw_vmcs12))) अणु
			ret = -EFAULT;
			जाओ error_guest_mode;
		पूर्ण

		अगर (shaकरोw_vmcs12->hdr.revision_id != VMCS12_REVISION ||
		    !shaकरोw_vmcs12->hdr.shaकरोw_vmcs)
			जाओ error_guest_mode;
	पूर्ण

	vmx->nested.has_preemption_समयr_deadline = false;
	अगर (kvm_state->hdr.vmx.flags & KVM_STATE_VMX_PREEMPTION_TIMER_DEADLINE) अणु
		vmx->nested.has_preemption_समयr_deadline = true;
		vmx->nested.preemption_समयr_deadline =
			kvm_state->hdr.vmx.preemption_समयr_deadline;
	पूर्ण

	अगर (nested_vmx_check_controls(vcpu, vmcs12) ||
	    nested_vmx_check_host_state(vcpu, vmcs12) ||
	    nested_vmx_check_guest_state(vcpu, vmcs12, &ignored))
		जाओ error_guest_mode;

	vmx->nested.dirty_vmcs12 = true;
	ret = nested_vmx_enter_non_root_mode(vcpu, false);
	अगर (ret)
		जाओ error_guest_mode;

	वापस 0;

error_guest_mode:
	vmx->nested.nested_run_pending = 0;
	वापस ret;
पूर्ण

व्योम nested_vmx_set_vmcs_shaकरोwing_biपंचांगap(व्योम)
अणु
	अगर (enable_shaकरोw_vmcs) अणु
		vmcs_ग_लिखो64(VMREAD_BITMAP, __pa(vmx_vmपढ़ो_biपंचांगap));
		vmcs_ग_लिखो64(VMWRITE_BITMAP, __pa(vmx_vmग_लिखो_biपंचांगap));
	पूर्ण
पूर्ण

/*
 * nested_vmx_setup_ctls_msrs() sets up variables containing the values to be
 * वापसed क्रम the various VMX controls MSRs when nested VMX is enabled.
 * The same values should also be used to verअगरy that vmcs12 control fields are
 * valid during nested entry from L1 to L2.
 * Each of these control msrs has a low and high 32-bit half: A low bit is on
 * अगर the corresponding bit in the (32-bit) control field *must* be on, and a
 * bit in the high half is on अगर the corresponding bit in the control field
 * may be on. See also vmx_control_verअगरy().
 */
व्योम nested_vmx_setup_ctls_msrs(काष्ठा nested_vmx_msrs *msrs, u32 ept_caps)
अणु
	/*
	 * Note that as a general rule, the high half of the MSRs (bits in
	 * the control fields which may be 1) should be initialized by the
	 * पूर्णांकersection of the underlying hardware's MSR (i.e., features which
	 * can be supported) and the list of features we want to expose -
	 * because they are known to be properly supported in our code.
	 * Also, usually, the low half of the MSRs (bits which must be 1) can
	 * be set to 0, meaning that L1 may turn off any of these bits. The
	 * reason is that अगर one of these bits is necessary, it will appear
	 * in vmcs01 and prepare_vmcs02, when it bitwise-or's the control
	 * fields of vmcs01 and vmcs02, will turn these bits off - and
	 * nested_vmx_l1_wants_निकास() will not pass related निकासs to L1.
	 * These rules have exceptions below.
	 */

	/* pin-based controls */
	rdmsr(MSR_IA32_VMX_PINBASED_CTLS,
		msrs->pinbased_ctls_low,
		msrs->pinbased_ctls_high);
	msrs->pinbased_ctls_low |=
		PIN_BASED_ALWAYSON_WITHOUT_TRUE_MSR;
	msrs->pinbased_ctls_high &=
		PIN_BASED_EXT_INTR_MASK |
		PIN_BASED_NMI_EXITING |
		PIN_BASED_VIRTUAL_NMIS |
		(enable_apicv ? PIN_BASED_POSTED_INTR : 0);
	msrs->pinbased_ctls_high |=
		PIN_BASED_ALWAYSON_WITHOUT_TRUE_MSR |
		PIN_BASED_VMX_PREEMPTION_TIMER;

	/* निकास controls */
	rdmsr(MSR_IA32_VMX_EXIT_CTLS,
		msrs->निकास_ctls_low,
		msrs->निकास_ctls_high);
	msrs->निकास_ctls_low =
		VM_EXIT_ALWAYSON_WITHOUT_TRUE_MSR;

	msrs->निकास_ctls_high &=
#अगर_घोषित CONFIG_X86_64
		VM_EXIT_HOST_ADDR_SPACE_SIZE |
#पूर्ण_अगर
		VM_EXIT_LOAD_IA32_PAT | VM_EXIT_SAVE_IA32_PAT |
		VM_EXIT_CLEAR_BNDCFGS | VM_EXIT_LOAD_IA32_PERF_GLOBAL_CTRL;
	msrs->निकास_ctls_high |=
		VM_EXIT_ALWAYSON_WITHOUT_TRUE_MSR |
		VM_EXIT_LOAD_IA32_EFER | VM_EXIT_SAVE_IA32_EFER |
		VM_EXIT_SAVE_VMX_PREEMPTION_TIMER | VM_EXIT_ACK_INTR_ON_EXIT;

	/* We support मुक्त control of debug control saving. */
	msrs->निकास_ctls_low &= ~VM_EXIT_SAVE_DEBUG_CONTROLS;

	/* entry controls */
	rdmsr(MSR_IA32_VMX_ENTRY_CTLS,
		msrs->entry_ctls_low,
		msrs->entry_ctls_high);
	msrs->entry_ctls_low =
		VM_ENTRY_ALWAYSON_WITHOUT_TRUE_MSR;
	msrs->entry_ctls_high &=
#अगर_घोषित CONFIG_X86_64
		VM_ENTRY_IA32E_MODE |
#पूर्ण_अगर
		VM_ENTRY_LOAD_IA32_PAT | VM_ENTRY_LOAD_BNDCFGS |
		VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL;
	msrs->entry_ctls_high |=
		(VM_ENTRY_ALWAYSON_WITHOUT_TRUE_MSR | VM_ENTRY_LOAD_IA32_EFER);

	/* We support मुक्त control of debug control loading. */
	msrs->entry_ctls_low &= ~VM_ENTRY_LOAD_DEBUG_CONTROLS;

	/* cpu-based controls */
	rdmsr(MSR_IA32_VMX_PROCBASED_CTLS,
		msrs->procbased_ctls_low,
		msrs->procbased_ctls_high);
	msrs->procbased_ctls_low =
		CPU_BASED_ALWAYSON_WITHOUT_TRUE_MSR;
	msrs->procbased_ctls_high &=
		CPU_BASED_INTR_WINDOW_EXITING |
		CPU_BASED_NMI_WINDOW_EXITING | CPU_BASED_USE_TSC_OFFSETTING |
		CPU_BASED_HLT_EXITING | CPU_BASED_INVLPG_EXITING |
		CPU_BASED_MWAIT_EXITING | CPU_BASED_CR3_LOAD_EXITING |
		CPU_BASED_CR3_STORE_EXITING |
#अगर_घोषित CONFIG_X86_64
		CPU_BASED_CR8_LOAD_EXITING | CPU_BASED_CR8_STORE_EXITING |
#पूर्ण_अगर
		CPU_BASED_MOV_DR_EXITING | CPU_BASED_UNCOND_IO_EXITING |
		CPU_BASED_USE_IO_BITMAPS | CPU_BASED_MONITOR_TRAP_FLAG |
		CPU_BASED_MONITOR_EXITING | CPU_BASED_RDPMC_EXITING |
		CPU_BASED_RDTSC_EXITING | CPU_BASED_PAUSE_EXITING |
		CPU_BASED_TPR_SHADOW | CPU_BASED_ACTIVATE_SECONDARY_CONTROLS;
	/*
	 * We can allow some features even when not supported by the
	 * hardware. For example, L1 can specअगरy an MSR biपंचांगap - and we
	 * can use it to aव्योम निकासs to L1 - even when L0 runs L2
	 * without MSR biपंचांगaps.
	 */
	msrs->procbased_ctls_high |=
		CPU_BASED_ALWAYSON_WITHOUT_TRUE_MSR |
		CPU_BASED_USE_MSR_BITMAPS;

	/* We support मुक्त control of CR3 access पूर्णांकerception. */
	msrs->procbased_ctls_low &=
		~(CPU_BASED_CR3_LOAD_EXITING | CPU_BASED_CR3_STORE_EXITING);

	/*
	 * secondary cpu-based controls.  Do not include those that
	 * depend on CPUID bits, they are added later by
	 * vmx_vcpu_after_set_cpuid.
	 */
	अगर (msrs->procbased_ctls_high & CPU_BASED_ACTIVATE_SECONDARY_CONTROLS)
		rdmsr(MSR_IA32_VMX_PROCBASED_CTLS2,
		      msrs->secondary_ctls_low,
		      msrs->secondary_ctls_high);

	msrs->secondary_ctls_low = 0;
	msrs->secondary_ctls_high &=
		SECONDARY_EXEC_DESC |
		SECONDARY_EXEC_ENABLE_RDTSCP |
		SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE |
		SECONDARY_EXEC_WBINVD_EXITING |
		SECONDARY_EXEC_APIC_REGISTER_VIRT |
		SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY |
		SECONDARY_EXEC_RDRAND_EXITING |
		SECONDARY_EXEC_ENABLE_INVPCID |
		SECONDARY_EXEC_RDSEED_EXITING |
		SECONDARY_EXEC_XSAVES;

	/*
	 * We can emulate "VMCS shadowing," even अगर the hardware
	 * करोesn't support it.
	 */
	msrs->secondary_ctls_high |=
		SECONDARY_EXEC_SHADOW_VMCS;

	अगर (enable_ept) अणु
		/* nested EPT: emulate EPT also to L1 */
		msrs->secondary_ctls_high |=
			SECONDARY_EXEC_ENABLE_EPT;
		msrs->ept_caps =
			VMX_EPT_PAGE_WALK_4_BIT |
			VMX_EPT_PAGE_WALK_5_BIT |
			VMX_EPTP_WB_BIT |
			VMX_EPT_INVEPT_BIT |
			VMX_EPT_EXECUTE_ONLY_BIT;

		msrs->ept_caps &= ept_caps;
		msrs->ept_caps |= VMX_EPT_EXTENT_GLOBAL_BIT |
			VMX_EPT_EXTENT_CONTEXT_BIT | VMX_EPT_2MB_PAGE_BIT |
			VMX_EPT_1GB_PAGE_BIT;
		अगर (enable_ept_ad_bits) अणु
			msrs->secondary_ctls_high |=
				SECONDARY_EXEC_ENABLE_PML;
			msrs->ept_caps |= VMX_EPT_AD_BIT;
		पूर्ण
	पूर्ण

	अगर (cpu_has_vmx_vmfunc()) अणु
		msrs->secondary_ctls_high |=
			SECONDARY_EXEC_ENABLE_VMFUNC;
		/*
		 * Advertise EPTP चयनing unconditionally
		 * since we emulate it
		 */
		अगर (enable_ept)
			msrs->vmfunc_controls =
				VMX_VMFUNC_EPTP_SWITCHING;
	पूर्ण

	/*
	 * Old versions of KVM use the single-context version without
	 * checking क्रम support, so declare that it is supported even
	 * though it is treated as global context.  The alternative is
	 * not failing the single-context invvpid, and it is worse.
	 */
	अगर (enable_vpid) अणु
		msrs->secondary_ctls_high |=
			SECONDARY_EXEC_ENABLE_VPID;
		msrs->vpid_caps = VMX_VPID_INVVPID_BIT |
			VMX_VPID_EXTENT_SUPPORTED_MASK;
	पूर्ण

	अगर (enable_unrestricted_guest)
		msrs->secondary_ctls_high |=
			SECONDARY_EXEC_UNRESTRICTED_GUEST;

	अगर (flexpriority_enabled)
		msrs->secondary_ctls_high |=
			SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES;

	अगर (enable_sgx)
		msrs->secondary_ctls_high |= SECONDARY_EXEC_ENCLS_EXITING;

	/* miscellaneous data */
	rdmsr(MSR_IA32_VMX_MISC,
		msrs->misc_low,
		msrs->misc_high);
	msrs->misc_low &= VMX_MISC_SAVE_EFER_LMA;
	msrs->misc_low |=
		MSR_IA32_VMX_MISC_VMWRITE_SHADOW_RO_FIELDS |
		VMX_MISC_EMULATED_PREEMPTION_TIMER_RATE |
		VMX_MISC_ACTIVITY_HLT |
		VMX_MISC_ACTIVITY_WAIT_SIPI;
	msrs->misc_high = 0;

	/*
	 * This MSR reports some inक्रमmation about VMX support. We
	 * should वापस inक्रमmation about the VMX we emulate क्रम the
	 * guest, and the VMCS काष्ठाure we give it - not about the
	 * VMX support of the underlying hardware.
	 */
	msrs->basic =
		VMCS12_REVISION |
		VMX_BASIC_TRUE_CTLS |
		((u64)VMCS12_SIZE << VMX_BASIC_VMCS_SIZE_SHIFT) |
		(VMX_BASIC_MEM_TYPE_WB << VMX_BASIC_MEM_TYPE_SHIFT);

	अगर (cpu_has_vmx_basic_inout())
		msrs->basic |= VMX_BASIC_INOUT;

	/*
	 * These MSRs specअगरy bits which the guest must keep fixed on
	 * जबतक L1 is in VMXON mode (in L1's root mode, or running an L2).
	 * We picked the standard core2 setting.
	 */
#घोषणा VMXON_CR0_ALWAYSON     (X86_CR0_PE | X86_CR0_PG | X86_CR0_NE)
#घोषणा VMXON_CR4_ALWAYSON     X86_CR4_VMXE
	msrs->cr0_fixed0 = VMXON_CR0_ALWAYSON;
	msrs->cr4_fixed0 = VMXON_CR4_ALWAYSON;

	/* These MSRs specअगरy bits which the guest must keep fixed off. */
	rdmsrl(MSR_IA32_VMX_CR0_FIXED1, msrs->cr0_fixed1);
	rdmsrl(MSR_IA32_VMX_CR4_FIXED1, msrs->cr4_fixed1);

	/* highest index: VMX_PREEMPTION_TIMER_VALUE */
	msrs->vmcs_क्रमागत = VMCS12_MAX_FIELD_INDEX << 1;
पूर्ण

व्योम nested_vmx_hardware_unsetup(व्योम)
अणु
	पूर्णांक i;

	अगर (enable_shaकरोw_vmcs) अणु
		क्रम (i = 0; i < VMX_BITMAP_NR; i++)
			मुक्त_page((अचिन्हित दीर्घ)vmx_biपंचांगap[i]);
	पूर्ण
पूर्ण

__init पूर्णांक nested_vmx_hardware_setup(पूर्णांक (*निकास_handlers[])(काष्ठा kvm_vcpu *))
अणु
	पूर्णांक i;

	अगर (!cpu_has_vmx_shaकरोw_vmcs())
		enable_shaकरोw_vmcs = 0;
	अगर (enable_shaकरोw_vmcs) अणु
		क्रम (i = 0; i < VMX_BITMAP_NR; i++) अणु
			/*
			 * The vmx_biपंचांगap is not tied to a VM and so should
			 * not be अक्षरged to a memcg.
			 */
			vmx_biपंचांगap[i] = (अचिन्हित दीर्घ *)
				__get_मुक्त_page(GFP_KERNEL);
			अगर (!vmx_biपंचांगap[i]) अणु
				nested_vmx_hardware_unsetup();
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		init_vmcs_shaकरोw_fields();
	पूर्ण

	निकास_handlers[EXIT_REASON_VMCLEAR]	= handle_vmclear;
	निकास_handlers[EXIT_REASON_VMLAUNCH]	= handle_vmlaunch;
	निकास_handlers[EXIT_REASON_VMPTRLD]	= handle_vmptrld;
	निकास_handlers[EXIT_REASON_VMPTRST]	= handle_vmptrst;
	निकास_handlers[EXIT_REASON_VMREAD]	= handle_vmपढ़ो;
	निकास_handlers[EXIT_REASON_VMRESUME]	= handle_vmresume;
	निकास_handlers[EXIT_REASON_VMWRITE]	= handle_vmग_लिखो;
	निकास_handlers[EXIT_REASON_VMOFF]	= handle_vmoff;
	निकास_handlers[EXIT_REASON_VMON]		= handle_vmon;
	निकास_handlers[EXIT_REASON_INVEPT]	= handle_invept;
	निकास_handlers[EXIT_REASON_INVVPID]	= handle_invvpid;
	निकास_handlers[EXIT_REASON_VMFUNC]	= handle_vmfunc;

	वापस 0;
पूर्ण

काष्ठा kvm_x86_nested_ops vmx_nested_ops = अणु
	.check_events = vmx_check_nested_events,
	.hv_समयr_pending = nested_vmx_preemption_समयr_pending,
	.triple_fault = nested_vmx_triple_fault,
	.get_state = vmx_get_nested_state,
	.set_state = vmx_set_nested_state,
	.get_nested_state_pages = vmx_get_nested_state_pages,
	.ग_लिखो_log_dirty = nested_vmx_ग_लिखो_pml_buffer,
	.enable_evmcs = nested_enable_evmcs,
	.get_evmcs_version = nested_get_evmcs_version,
पूर्ण;
