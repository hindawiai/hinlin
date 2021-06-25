<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  Copyright(c) 2021 Intel Corporation. */

#समावेश <यंत्र/sgx.h>

#समावेश "cpuid.h"
#समावेश "kvm_cache_regs.h"
#समावेश "nested.h"
#समावेश "sgx.h"
#समावेश "vmx.h"
#समावेश "x86.h"

bool __पढ़ो_mostly enable_sgx = 1;
module_param_named(sgx, enable_sgx, bool, 0444);

/* Initial value of guest's भव SGX_LEPUBKEYHASHn MSRs */
अटल u64 sgx_pubkey_hash[4] __ro_after_init;

/*
 * ENCLS's memory opeअक्रमs use a fixed segment (DS) and a fixed
 * address size based on the mode.  Related prefixes are ignored.
 */
अटल पूर्णांक sgx_get_encls_gva(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ offset,
			     पूर्णांक size, पूर्णांक alignment, gva_t *gva)
अणु
	काष्ठा kvm_segment s;
	bool fault;

	/* Skip vmcs.GUEST_DS retrieval क्रम 64-bit mode to aव्योम VMREADs. */
	*gva = offset;
	अगर (!is_दीर्घ_mode(vcpu)) अणु
		vmx_get_segment(vcpu, &s, VCPU_SREG_DS);
		*gva += s.base;
	पूर्ण

	अगर (!IS_ALIGNED(*gva, alignment)) अणु
		fault = true;
	पूर्ण अन्यथा अगर (likely(is_दीर्घ_mode(vcpu))) अणु
		fault = is_noncanonical_address(*gva, vcpu);
	पूर्ण अन्यथा अणु
		*gva &= 0xffffffff;
		fault = (s.unusable) ||
			(s.type != 2 && s.type != 3) ||
			(*gva > s.limit) ||
			((s.base != 0 || s.limit != 0xffffffff) &&
			(((u64)*gva + size - 1) > s.limit + 1));
	पूर्ण
	अगर (fault)
		kvm_inject_gp(vcpu, 0);
	वापस fault ? -EINVAL : 0;
पूर्ण

अटल व्योम sgx_handle_emulation_failure(काष्ठा kvm_vcpu *vcpu, u64 addr,
					 अचिन्हित पूर्णांक size)
अणु
	vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
	vcpu->run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_EMULATION;
	vcpu->run->पूर्णांकernal.ndata = 2;
	vcpu->run->पूर्णांकernal.data[0] = addr;
	vcpu->run->पूर्णांकernal.data[1] = size;
पूर्ण

अटल पूर्णांक sgx_पढ़ो_hva(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ hva, व्योम *data,
			अचिन्हित पूर्णांक size)
अणु
	अगर (__copy_from_user(data, (व्योम __user *)hva, size)) अणु
		sgx_handle_emulation_failure(vcpu, hva, size);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sgx_gva_to_gpa(काष्ठा kvm_vcpu *vcpu, gva_t gva, bool ग_लिखो,
			  gpa_t *gpa)
अणु
	काष्ठा x86_exception ex;

	अगर (ग_लिखो)
		*gpa = kvm_mmu_gva_to_gpa_ग_लिखो(vcpu, gva, &ex);
	अन्यथा
		*gpa = kvm_mmu_gva_to_gpa_पढ़ो(vcpu, gva, &ex);

	अगर (*gpa == UNMAPPED_GVA) अणु
		kvm_inject_emulated_page_fault(vcpu, &ex);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sgx_gpa_to_hva(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, अचिन्हित दीर्घ *hva)
अणु
	*hva = kvm_vcpu_gfn_to_hva(vcpu, PFN_DOWN(gpa));
	अगर (kvm_is_error_hva(*hva)) अणु
		sgx_handle_emulation_failure(vcpu, gpa, 1);
		वापस -EFAULT;
	पूर्ण

	*hva |= gpa & ~PAGE_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक sgx_inject_fault(काष्ठा kvm_vcpu *vcpu, gva_t gva, पूर्णांक trapnr)
अणु
	काष्ठा x86_exception ex;

	/*
	 * A non-EPCM #PF indicates a bad userspace HVA.  This *should* check
	 * क्रम PFEC.SGX and not assume any #PF on SGX2 originated in the EPC,
	 * but the error code isn't (yet) plumbed through the ENCLS helpers.
	 */
	अगर (trapnr == PF_VECTOR && !boot_cpu_has(X86_FEATURE_SGX2)) अणु
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_EMULATION;
		vcpu->run->पूर्णांकernal.ndata = 0;
		वापस 0;
	पूर्ण

	/*
	 * If the guest thinks it's running on SGX2 hardware, inject an SGX
	 * #PF अगर the fault matches an EPCM fault signature (#GP on SGX1,
	 * #PF on SGX2).  The assumption is that EPCM faults are much more
	 * likely than a bad userspace address.
	 */
	अगर ((trapnr == PF_VECTOR || !boot_cpu_has(X86_FEATURE_SGX2)) &&
	    guest_cpuid_has(vcpu, X86_FEATURE_SGX2)) अणु
		स_रखो(&ex, 0, माप(ex));
		ex.vector = PF_VECTOR;
		ex.error_code = PFERR_PRESENT_MASK | PFERR_WRITE_MASK |
				PFERR_SGX_MASK;
		ex.address = gva;
		ex.error_code_valid = true;
		ex.nested_page_fault = false;
		kvm_inject_page_fault(vcpu, &ex);
	पूर्ण अन्यथा अणु
		kvm_inject_gp(vcpu, 0);
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक __handle_encls_ecreate(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा sgx_pageinfo *pageinfo,
				  अचिन्हित दीर्घ secs_hva,
				  gva_t secs_gva)
अणु
	काष्ठा sgx_secs *contents = (काष्ठा sgx_secs *)pageinfo->contents;
	काष्ठा kvm_cpuid_entry2 *sgx_12_0, *sgx_12_1;
	u64 attributes, xfrm, size;
	u32 miscselect;
	u8 max_size_log2;
	पूर्णांक trapnr, ret;

	sgx_12_0 = kvm_find_cpuid_entry(vcpu, 0x12, 0);
	sgx_12_1 = kvm_find_cpuid_entry(vcpu, 0x12, 1);
	अगर (!sgx_12_0 || !sgx_12_1) अणु
		vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		vcpu->run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_EMULATION;
		vcpu->run->पूर्णांकernal.ndata = 0;
		वापस 0;
	पूर्ण

	miscselect = contents->miscselect;
	attributes = contents->attributes;
	xfrm = contents->xfrm;
	size = contents->size;

	/* Enक्रमce restriction of access to the PROVISIONKEY. */
	अगर (!vcpu->kvm->arch.sgx_provisioning_allowed &&
	    (attributes & SGX_ATTR_PROVISIONKEY)) अणु
		अगर (sgx_12_1->eax & SGX_ATTR_PROVISIONKEY)
			pr_warn_once("KVM: SGX PROVISIONKEY advertised but not allowed\n");
		kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण

	/* Enक्रमce CPUID restrictions on MISCSELECT, ATTRIBUTES and XFRM. */
	अगर ((u32)miscselect & ~sgx_12_0->ebx ||
	    (u32)attributes & ~sgx_12_1->eax ||
	    (u32)(attributes >> 32) & ~sgx_12_1->ebx ||
	    (u32)xfrm & ~sgx_12_1->ecx ||
	    (u32)(xfrm >> 32) & ~sgx_12_1->edx) अणु
		kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण

	/* Enक्रमce CPUID restriction on max enclave size. */
	max_size_log2 = (attributes & SGX_ATTR_MODE64BIT) ? sgx_12_0->edx >> 8 :
							    sgx_12_0->edx;
	अगर (size >= BIT_ULL(max_size_log2))
		kvm_inject_gp(vcpu, 0);

	/*
	 * sgx_virt_ecreate() वापसs:
	 *  1) 0:	ECREATE was successful
	 *  2) -EFAULT:	ECREATE was run but faulted, and trapnr was set to the
	 *		exception number.
	 *  3) -EINVAL:	access_ok() on @secs_hva failed. This should never
	 *		happen as KVM checks host addresses at memslot creation.
	 *		sgx_virt_ecreate() has alपढ़ोy warned in this हाल.
	 */
	ret = sgx_virt_ecreate(pageinfo, (व्योम __user *)secs_hva, &trapnr);
	अगर (!ret)
		वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
	अगर (ret == -EFAULT)
		वापस sgx_inject_fault(vcpu, secs_gva, trapnr);

	वापस ret;
पूर्ण

अटल पूर्णांक handle_encls_ecreate(काष्ठा kvm_vcpu *vcpu)
अणु
	gva_t pageinfo_gva, secs_gva;
	gva_t metadata_gva, contents_gva;
	gpa_t metadata_gpa, contents_gpa, secs_gpa;
	अचिन्हित दीर्घ metadata_hva, contents_hva, secs_hva;
	काष्ठा sgx_pageinfo pageinfo;
	काष्ठा sgx_secs *contents;
	काष्ठा x86_exception ex;
	पूर्णांक r;

	अगर (sgx_get_encls_gva(vcpu, kvm_rbx_पढ़ो(vcpu), 32, 32, &pageinfo_gva) ||
	    sgx_get_encls_gva(vcpu, kvm_rcx_पढ़ो(vcpu), 4096, 4096, &secs_gva))
		वापस 1;

	/*
	 * Copy the PAGEINFO to local memory, its poपूर्णांकers need to be
	 * translated, i.e. we need to करो a deep copy/translate.
	 */
	r = kvm_पढ़ो_guest_virt(vcpu, pageinfo_gva, &pageinfo,
				माप(pageinfo), &ex);
	अगर (r == X86EMUL_PROPAGATE_FAULT) अणु
		kvm_inject_emulated_page_fault(vcpu, &ex);
		वापस 1;
	पूर्ण अन्यथा अगर (r != X86EMUL_CONTINUE) अणु
		sgx_handle_emulation_failure(vcpu, pageinfo_gva,
					     माप(pageinfo));
		वापस 0;
	पूर्ण

	अगर (sgx_get_encls_gva(vcpu, pageinfo.metadata, 64, 64, &metadata_gva) ||
	    sgx_get_encls_gva(vcpu, pageinfo.contents, 4096, 4096,
			      &contents_gva))
		वापस 1;

	/*
	 * Translate the SECINFO, SOURCE and SECS poपूर्णांकers from GVA to GPA.
	 * Resume the guest on failure to inject a #PF.
	 */
	अगर (sgx_gva_to_gpa(vcpu, metadata_gva, false, &metadata_gpa) ||
	    sgx_gva_to_gpa(vcpu, contents_gva, false, &contents_gpa) ||
	    sgx_gva_to_gpa(vcpu, secs_gva, true, &secs_gpa))
		वापस 1;

	/*
	 * ...and then to HVA.  The order of accesses isn't architectural, i.e.
	 * KVM करोesn't have to fully process one address at a समय.  Exit to
	 * userspace अगर a GPA is invalid.
	 */
	अगर (sgx_gpa_to_hva(vcpu, metadata_gpa, &metadata_hva) ||
	    sgx_gpa_to_hva(vcpu, contents_gpa, &contents_hva) ||
	    sgx_gpa_to_hva(vcpu, secs_gpa, &secs_hva))
		वापस 0;

	/*
	 * Copy contents पूर्णांकo kernel memory to prevent TOCTOU attack. E.g. the
	 * guest could करो ECREATE w/ SECS.SGX_ATTR_PROVISIONKEY=0, and
	 * simultaneously set SGX_ATTR_PROVISIONKEY to bypass the check to
	 * enक्रमce restriction of access to the PROVISIONKEY.
	 */
	contents = (काष्ठा sgx_secs *)__get_मुक्त_page(GFP_KERNEL_ACCOUNT);
	अगर (!contents)
		वापस -ENOMEM;

	/* Exit to userspace अगर copying from a host userspace address fails. */
	अगर (sgx_पढ़ो_hva(vcpu, contents_hva, (व्योम *)contents, PAGE_SIZE)) अणु
		मुक्त_page((अचिन्हित दीर्घ)contents);
		वापस 0;
	पूर्ण

	pageinfo.metadata = metadata_hva;
	pageinfo.contents = (u64)contents;

	r = __handle_encls_ecreate(vcpu, &pageinfo, secs_hva, secs_gva);

	मुक्त_page((अचिन्हित दीर्घ)contents);

	वापस r;
पूर्ण

अटल पूर्णांक handle_encls_einit(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ sig_hva, secs_hva, token_hva, rflags;
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);
	gva_t sig_gva, secs_gva, token_gva;
	gpa_t sig_gpa, secs_gpa, token_gpa;
	पूर्णांक ret, trapnr;

	अगर (sgx_get_encls_gva(vcpu, kvm_rbx_पढ़ो(vcpu), 1808, 4096, &sig_gva) ||
	    sgx_get_encls_gva(vcpu, kvm_rcx_पढ़ो(vcpu), 4096, 4096, &secs_gva) ||
	    sgx_get_encls_gva(vcpu, kvm_rdx_पढ़ो(vcpu), 304, 512, &token_gva))
		वापस 1;

	/*
	 * Translate the SIGSTRUCT, SECS and TOKEN poपूर्णांकers from GVA to GPA.
	 * Resume the guest on failure to inject a #PF.
	 */
	अगर (sgx_gva_to_gpa(vcpu, sig_gva, false, &sig_gpa) ||
	    sgx_gva_to_gpa(vcpu, secs_gva, true, &secs_gpa) ||
	    sgx_gva_to_gpa(vcpu, token_gva, false, &token_gpa))
		वापस 1;

	/*
	 * ...and then to HVA.  The order of accesses isn't architectural, i.e.
	 * KVM करोesn't have to fully process one address at a समय.  Exit to
	 * userspace अगर a GPA is invalid.  Note, all काष्ठाures are aligned and
	 * cannot split pages.
	 */
	अगर (sgx_gpa_to_hva(vcpu, sig_gpa, &sig_hva) ||
	    sgx_gpa_to_hva(vcpu, secs_gpa, &secs_hva) ||
	    sgx_gpa_to_hva(vcpu, token_gpa, &token_hva))
		वापस 0;

	ret = sgx_virt_einit((व्योम __user *)sig_hva, (व्योम __user *)token_hva,
			     (व्योम __user *)secs_hva,
			     vmx->msr_ia32_sgxlepubkeyhash, &trapnr);

	अगर (ret == -EFAULT)
		वापस sgx_inject_fault(vcpu, secs_gva, trapnr);

	/*
	 * sgx_virt_einit() वापसs -EINVAL when access_ok() fails on @sig_hva,
	 * @token_hva or @secs_hva. This should never happen as KVM checks host
	 * addresses at memslot creation. sgx_virt_einit() has alपढ़ोy warned
	 * in this हाल, so just वापस.
	 */
	अगर (ret < 0)
		वापस ret;

	rflags = vmx_get_rflags(vcpu) & ~(X86_EFLAGS_CF | X86_EFLAGS_PF |
					  X86_EFLAGS_AF | X86_EFLAGS_SF |
					  X86_EFLAGS_OF);
	अगर (ret)
		rflags |= X86_EFLAGS_ZF;
	अन्यथा
		rflags &= ~X86_EFLAGS_ZF;
	vmx_set_rflags(vcpu, rflags);

	kvm_rax_ग_लिखो(vcpu, ret);
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल अंतरभूत bool encls_leaf_enabled_in_guest(काष्ठा kvm_vcpu *vcpu, u32 leaf)
अणु
	अगर (!enable_sgx || !guest_cpuid_has(vcpu, X86_FEATURE_SGX))
		वापस false;

	अगर (leaf >= ECREATE && leaf <= ETRACK)
		वापस guest_cpuid_has(vcpu, X86_FEATURE_SGX1);

	अगर (leaf >= EAUG && leaf <= EMODT)
		वापस guest_cpuid_has(vcpu, X86_FEATURE_SGX2);

	वापस false;
पूर्ण

अटल अंतरभूत bool sgx_enabled_in_guest_bios(काष्ठा kvm_vcpu *vcpu)
अणु
	स्थिर u64 bits = FEAT_CTL_SGX_ENABLED | FEAT_CTL_LOCKED;

	वापस (to_vmx(vcpu)->msr_ia32_feature_control & bits) == bits;
पूर्ण

पूर्णांक handle_encls(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 leaf = (u32)kvm_rax_पढ़ो(vcpu);

	अगर (!encls_leaf_enabled_in_guest(vcpu, leaf)) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
	पूर्ण अन्यथा अगर (!sgx_enabled_in_guest_bios(vcpu)) अणु
		kvm_inject_gp(vcpu, 0);
	पूर्ण अन्यथा अणु
		अगर (leaf == ECREATE)
			वापस handle_encls_ecreate(vcpu);
		अगर (leaf == EINIT)
			वापस handle_encls_einit(vcpu);
		WARN(1, "KVM: unexpected exit on ENCLS[%u]", leaf);
		vcpu->run->निकास_reason = KVM_EXIT_UNKNOWN;
		vcpu->run->hw.hardware_निकास_reason = EXIT_REASON_ENCLS;
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

व्योम setup_शेष_sgx_lepubkeyhash(व्योम)
अणु
	/*
	 * Use Intel's शेष value क्रम Skylake hardware अगर Launch Control is
	 * not supported, i.e. Intel's hash is hardcoded पूर्णांकo silicon, or अगर
	 * Launch Control is supported and enabled, i.e. mimic the reset value
	 * and let the guest ग_लिखो the MSRs at will.  If Launch Control is
	 * supported but disabled, then use the current MSR values as the hash
	 * MSRs exist but are पढ़ो-only (locked and not writable).
	 */
	अगर (!enable_sgx || boot_cpu_has(X86_FEATURE_SGX_LC) ||
	    rdmsrl_safe(MSR_IA32_SGXLEPUBKEYHASH0, &sgx_pubkey_hash[0])) अणु
		sgx_pubkey_hash[0] = 0xa6053e051270b7acULL;
		sgx_pubkey_hash[1] = 0x6cfbe8ba8b3b413dULL;
		sgx_pubkey_hash[2] = 0xc4916d99f2b3735dULL;
		sgx_pubkey_hash[3] = 0xd4f8c05909f9bb3bULL;
	पूर्ण अन्यथा अणु
		/* MSR_IA32_SGXLEPUBKEYHASH0 is पढ़ो above */
		rdmsrl(MSR_IA32_SGXLEPUBKEYHASH1, sgx_pubkey_hash[1]);
		rdmsrl(MSR_IA32_SGXLEPUBKEYHASH2, sgx_pubkey_hash[2]);
		rdmsrl(MSR_IA32_SGXLEPUBKEYHASH3, sgx_pubkey_hash[3]);
	पूर्ण
पूर्ण

व्योम vcpu_setup_sgx_lepubkeyhash(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_vmx *vmx = to_vmx(vcpu);

	स_नकल(vmx->msr_ia32_sgxlepubkeyhash, sgx_pubkey_hash,
	       माप(sgx_pubkey_hash));
पूर्ण

/*
 * ECREATE must be पूर्णांकercepted to enक्रमce MISCSELECT, ATTRIBUTES and XFRM
 * restrictions अगर the guest's allowed-1 settings भागerge from hardware.
 */
अटल bool sgx_पूर्णांकercept_encls_ecreate(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpuid_entry2 *guest_cpuid;
	u32 eax, ebx, ecx, edx;

	अगर (!vcpu->kvm->arch.sgx_provisioning_allowed)
		वापस true;

	guest_cpuid = kvm_find_cpuid_entry(vcpu, 0x12, 0);
	अगर (!guest_cpuid)
		वापस true;

	cpuid_count(0x12, 0, &eax, &ebx, &ecx, &edx);
	अगर (guest_cpuid->ebx != ebx || guest_cpuid->edx != edx)
		वापस true;

	guest_cpuid = kvm_find_cpuid_entry(vcpu, 0x12, 1);
	अगर (!guest_cpuid)
		वापस true;

	cpuid_count(0x12, 1, &eax, &ebx, &ecx, &edx);
	अगर (guest_cpuid->eax != eax || guest_cpuid->ebx != ebx ||
	    guest_cpuid->ecx != ecx || guest_cpuid->edx != edx)
		वापस true;

	वापस false;
पूर्ण

व्योम vmx_ग_लिखो_encls_biपंचांगap(काष्ठा kvm_vcpu *vcpu, काष्ठा vmcs12 *vmcs12)
अणु
	/*
	 * There is no software enable bit क्रम SGX that is भवized by
	 * hardware, e.g. there's no CR4.SGXE, so when SGX is disabled in the
	 * guest (either by the host or by the guest's BIOS) but enabled in the
	 * host, trap all ENCLS leafs and inject #UD/#GP as needed to emulate
	 * the expected प्रणाली behavior क्रम ENCLS.
	 */
	u64 biपंचांगap = -1ull;

	/* Nothing to करो अगर hardware करोesn't support SGX */
	अगर (!cpu_has_vmx_encls_vmनिकास())
		वापस;

	अगर (guest_cpuid_has(vcpu, X86_FEATURE_SGX) &&
	    sgx_enabled_in_guest_bios(vcpu)) अणु
		अगर (guest_cpuid_has(vcpu, X86_FEATURE_SGX1)) अणु
			biपंचांगap &= ~GENMASK_ULL(ETRACK, ECREATE);
			अगर (sgx_पूर्णांकercept_encls_ecreate(vcpu))
				biपंचांगap |= (1 << ECREATE);
		पूर्ण

		अगर (guest_cpuid_has(vcpu, X86_FEATURE_SGX2))
			biपंचांगap &= ~GENMASK_ULL(EMODT, EAUG);

		/*
		 * Trap and execute EINIT अगर launch control is enabled in the
		 * host using the guest's values क्रम launch control MSRs, even
		 * अगर the guest's values are fixed to hardware शेष values.
		 * The MSRs are not loaded/saved on VM-Enter/VM-Exit as writing
		 * the MSRs is extraordinarily expensive.
		 */
		अगर (boot_cpu_has(X86_FEATURE_SGX_LC))
			biपंचांगap |= (1 << EINIT);

		अगर (!vmcs12 && is_guest_mode(vcpu))
			vmcs12 = get_vmcs12(vcpu);
		अगर (vmcs12 && nested_cpu_has_encls_निकास(vmcs12))
			biपंचांगap |= vmcs12->encls_निकासing_biपंचांगap;
	पूर्ण
	vmcs_ग_लिखो64(ENCLS_EXITING_BITMAP, biपंचांगap);
पूर्ण
