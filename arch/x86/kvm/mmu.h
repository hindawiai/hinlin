<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_X86_MMU_H
#घोषणा __KVM_X86_MMU_H

#समावेश <linux/kvm_host.h>
#समावेश "kvm_cache_regs.h"
#समावेश "cpuid.h"

#घोषणा PT64_PT_BITS 9
#घोषणा PT64_ENT_PER_PAGE (1 << PT64_PT_BITS)
#घोषणा PT32_PT_BITS 10
#घोषणा PT32_ENT_PER_PAGE (1 << PT32_PT_BITS)

#घोषणा PT_WRITABLE_SHIFT 1
#घोषणा PT_USER_SHIFT 2

#घोषणा PT_PRESENT_MASK (1ULL << 0)
#घोषणा PT_WRITABLE_MASK (1ULL << PT_WRITABLE_SHIFT)
#घोषणा PT_USER_MASK (1ULL << PT_USER_SHIFT)
#घोषणा PT_PWT_MASK (1ULL << 3)
#घोषणा PT_PCD_MASK (1ULL << 4)
#घोषणा PT_ACCESSED_SHIFT 5
#घोषणा PT_ACCESSED_MASK (1ULL << PT_ACCESSED_SHIFT)
#घोषणा PT_सूचीTY_SHIFT 6
#घोषणा PT_सूचीTY_MASK (1ULL << PT_सूचीTY_SHIFT)
#घोषणा PT_PAGE_SIZE_SHIFT 7
#घोषणा PT_PAGE_SIZE_MASK (1ULL << PT_PAGE_SIZE_SHIFT)
#घोषणा PT_PAT_MASK (1ULL << 7)
#घोषणा PT_GLOBAL_MASK (1ULL << 8)
#घोषणा PT64_NX_SHIFT 63
#घोषणा PT64_NX_MASK (1ULL << PT64_NX_SHIFT)

#घोषणा PT_PAT_SHIFT 7
#घोषणा PT_सूची_PAT_SHIFT 12
#घोषणा PT_सूची_PAT_MASK (1ULL << PT_सूची_PAT_SHIFT)

#घोषणा PT32_सूची_PSE36_SIZE 4
#घोषणा PT32_सूची_PSE36_SHIFT 13
#घोषणा PT32_सूची_PSE36_MASK \
	(((1ULL << PT32_सूची_PSE36_SIZE) - 1) << PT32_सूची_PSE36_SHIFT)

#घोषणा PT64_ROOT_5LEVEL 5
#घोषणा PT64_ROOT_4LEVEL 4
#घोषणा PT32_ROOT_LEVEL 2
#घोषणा PT32E_ROOT_LEVEL 3

अटल __always_अंतरभूत u64 rsvd_bits(पूर्णांक s, पूर्णांक e)
अणु
	BUILD_BUG_ON(__builtin_स्थिरant_p(e) && __builtin_स्थिरant_p(s) && e < s);

	अगर (__builtin_स्थिरant_p(e))
		BUILD_BUG_ON(e > 63);
	अन्यथा
		e &= 63;

	अगर (e < s)
		वापस 0;

	वापस ((2ULL << (e - s)) - 1) << s;
पूर्ण

व्योम kvm_mmu_set_mmio_spte_mask(u64 mmio_value, u64 mmio_mask, u64 access_mask);
व्योम kvm_mmu_set_ept_masks(bool has_ad_bits, bool has_exec_only);

व्योम
reset_shaकरोw_zero_bits_mask(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu *context);

व्योम kvm_init_mmu(काष्ठा kvm_vcpu *vcpu, bool reset_roots);
व्योम kvm_init_shaकरोw_npt_mmu(काष्ठा kvm_vcpu *vcpu, u32 cr0, u32 cr4, u32 efer,
			     gpa_t nested_cr3);
व्योम kvm_init_shaकरोw_ept_mmu(काष्ठा kvm_vcpu *vcpu, bool execonly,
			     bool accessed_dirty, gpa_t new_eptp);
bool kvm_can_करो_async_pf(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_handle_page_fault(काष्ठा kvm_vcpu *vcpu, u64 error_code,
				u64 fault_address, अक्षर *insn, पूर्णांक insn_len);

पूर्णांक kvm_mmu_load(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_mmu_unload(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_mmu_sync_roots(काष्ठा kvm_vcpu *vcpu);

अटल अंतरभूत पूर्णांक kvm_mmu_reload(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (likely(vcpu->arch.mmu->root_hpa != INVALID_PAGE))
		वापस 0;

	वापस kvm_mmu_load(vcpu);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvm_get_pcid(काष्ठा kvm_vcpu *vcpu, gpa_t cr3)
अणु
	BUILD_BUG_ON((X86_CR3_PCID_MASK & PAGE_MASK) != 0);

	वापस kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_PCIDE)
	       ? cr3 & X86_CR3_PCID_MASK
	       : 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvm_get_active_pcid(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_get_pcid(vcpu, kvm_पढ़ो_cr3(vcpu));
पूर्ण

अटल अंतरभूत व्योम kvm_mmu_load_pgd(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 root_hpa = vcpu->arch.mmu->root_hpa;

	अगर (!VALID_PAGE(root_hpa))
		वापस;

	अटल_call(kvm_x86_load_mmu_pgd)(vcpu, root_hpa,
					  vcpu->arch.mmu->shaकरोw_root_level);
पूर्ण

पूर्णांक kvm_tdp_page_fault(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, u32 error_code,
		       bool prefault);

अटल अंतरभूत पूर्णांक kvm_mmu_करो_page_fault(काष्ठा kvm_vcpu *vcpu, gpa_t cr2_or_gpa,
					u32 err, bool prefault)
अणु
#अगर_घोषित CONFIG_RETPOLINE
	अगर (likely(vcpu->arch.mmu->page_fault == kvm_tdp_page_fault))
		वापस kvm_tdp_page_fault(vcpu, cr2_or_gpa, err, prefault);
#पूर्ण_अगर
	वापस vcpu->arch.mmu->page_fault(vcpu, cr2_or_gpa, err, prefault);
पूर्ण

/*
 * Currently, we have two sorts of ग_लिखो-protection, a) the first one
 * ग_लिखो-protects guest page to sync the guest modअगरication, b) another one is
 * used to sync dirty biपंचांगap when we करो KVM_GET_सूचीTY_LOG. The dअगरferences
 * between these two sorts are:
 * 1) the first हाल clears MMU-writable bit.
 * 2) the first हाल requires flushing tlb immediately aव्योमing corrupting
 *    shaकरोw page table between all vcpus so it should be in the protection of
 *    mmu-lock. And the another हाल करोes not need to flush tlb until वापसing
 *    the dirty biपंचांगap to userspace since it only ग_लिखो-protects the page
 *    logged in the biपंचांगap, that means the page in the dirty biपंचांगap is not
 *    missed, so it can flush tlb out of mmu-lock.
 *
 * So, there is the problem: the first हाल can meet the corrupted tlb caused
 * by another हाल which ग_लिखो-protects pages but without flush tlb
 * immediately. In order to making the first हाल be aware this problem we let
 * it flush tlb अगर we try to ग_लिखो-protect a spte whose MMU-writable bit
 * is set, it works since another हाल never touches MMU-writable bit.
 *
 * Anyway, whenever a spte is updated (only permission and status bits are
 * changed) we need to check whether the spte with MMU-writable becomes
 * पढ़ोonly, अगर that happens, we need to flush tlb. Fortunately,
 * mmu_spte_update() has alपढ़ोy handled it perfectly.
 *
 * The rules to use MMU-writable and PT_WRITABLE_MASK:
 * - अगर we want to see अगर it has writable tlb entry or अगर the spte can be
 *   writable on the mmu mapping, check MMU-writable, this is the most
 *   हाल, otherwise
 * - अगर we fix page fault on the spte or करो ग_लिखो-protection by dirty logging,
 *   check PT_WRITABLE_MASK.
 *
 * TODO: पूर्णांकroduce APIs to split these two हालs.
 */
अटल अंतरभूत bool is_writable_pte(अचिन्हित दीर्घ pte)
अणु
	वापस pte & PT_WRITABLE_MASK;
पूर्ण

अटल अंतरभूत bool is_ग_लिखो_protection(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_पढ़ो_cr0_bits(vcpu, X86_CR0_WP);
पूर्ण

/*
 * Check अगर a given access (described through the I/D, W/R and U/S bits of a
 * page fault error code pfec) causes a permission fault with the given PTE
 * access rights (in ACC_* क्रमmat).
 *
 * Return zero अगर the access करोes not fault; वापस the page fault error code
 * अगर the access faults.
 */
अटल अंतरभूत u8 permission_fault(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu *mmu,
				  अचिन्हित pte_access, अचिन्हित pte_pkey,
				  अचिन्हित pfec)
अणु
	पूर्णांक cpl = अटल_call(kvm_x86_get_cpl)(vcpu);
	अचिन्हित दीर्घ rflags = अटल_call(kvm_x86_get_rflags)(vcpu);

	/*
	 * If CPL < 3, SMAP prevention are disabled अगर EFLAGS.AC = 1.
	 *
	 * If CPL = 3, SMAP applies to all supervisor-mode data accesses
	 * (these are implicit supervisor accesses) regardless of the value
	 * of EFLAGS.AC.
	 *
	 * This computes (cpl < 3) && (rflags & X86_EFLAGS_AC), leaving
	 * the result in X86_EFLAGS_AC. We then insert it in place of
	 * the PFERR_RSVD_MASK bit; this bit will always be zero in pfec,
	 * but it will be one in index अगर SMAP checks are being overridden.
	 * It is important to keep this branchless.
	 */
	अचिन्हित दीर्घ smap = (cpl - 3) & (rflags & X86_EFLAGS_AC);
	पूर्णांक index = (pfec >> 1) +
		    (smap >> (X86_EFLAGS_AC_BIT - PFERR_RSVD_BIT + 1));
	bool fault = (mmu->permissions[index] >> pte_access) & 1;
	u32 errcode = PFERR_PRESENT_MASK;

	WARN_ON(pfec & (PFERR_PK_MASK | PFERR_RSVD_MASK));
	अगर (unlikely(mmu->pkru_mask)) अणु
		u32 pkru_bits, offset;

		/*
		* PKRU defines 32 bits, there are 16 करोमुख्यs and 2
		* attribute bits per करोमुख्य in pkru.  pte_pkey is the
		* index of the protection करोमुख्य, so pte_pkey * 2 is
		* is the index of the first bit क्रम the करोमुख्य.
		*/
		pkru_bits = (vcpu->arch.pkru >> (pte_pkey * 2)) & 3;

		/* clear present bit, replace PFEC.RSVD with ACC_USER_MASK. */
		offset = (pfec & ~1) +
			((pte_access & PT_USER_MASK) << (PFERR_RSVD_BIT - PT_USER_SHIFT));

		pkru_bits &= mmu->pkru_mask >> offset;
		errcode |= -pkru_bits & PFERR_PK_MASK;
		fault |= (pkru_bits != 0);
	पूर्ण

	वापस -(u32)fault & errcode;
पूर्ण

व्योम kvm_zap_gfn_range(काष्ठा kvm *kvm, gfn_t gfn_start, gfn_t gfn_end);

पूर्णांक kvm_arch_ग_लिखो_log_dirty(काष्ठा kvm_vcpu *vcpu);

पूर्णांक kvm_mmu_post_init_vm(काष्ठा kvm *kvm);
व्योम kvm_mmu_pre_destroy_vm(काष्ठा kvm *kvm);

#पूर्ण_अगर
