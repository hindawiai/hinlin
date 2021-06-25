<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel-based Virtual Machine driver क्रम Linux
 *
 * Macros and functions to access KVM PTEs (also known as SPTEs)
 *
 * Copyright (C) 2006 Qumranet, Inc.
 * Copyright 2020 Red Hat, Inc. and/or its affiliates.
 */


#समावेश <linux/kvm_host.h>
#समावेश "mmu.h"
#समावेश "mmu_internal.h"
#समावेश "x86.h"
#समावेश "spte.h"

#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/vmx.h>

अटल bool __पढ़ो_mostly enable_mmio_caching = true;
module_param_named(mmio_caching, enable_mmio_caching, bool, 0444);

u64 __पढ़ो_mostly shaकरोw_host_writable_mask;
u64 __पढ़ो_mostly shaकरोw_mmu_writable_mask;
u64 __पढ़ो_mostly shaकरोw_nx_mask;
u64 __पढ़ो_mostly shaकरोw_x_mask; /* mutual exclusive with nx_mask */
u64 __पढ़ो_mostly shaकरोw_user_mask;
u64 __पढ़ो_mostly shaकरोw_accessed_mask;
u64 __पढ़ो_mostly shaकरोw_dirty_mask;
u64 __पढ़ो_mostly shaकरोw_mmio_value;
u64 __पढ़ो_mostly shaकरोw_mmio_mask;
u64 __पढ़ो_mostly shaकरोw_mmio_access_mask;
u64 __पढ़ो_mostly shaकरोw_present_mask;
u64 __पढ़ो_mostly shaकरोw_me_mask;
u64 __पढ़ो_mostly shaकरोw_acc_track_mask;

u64 __पढ़ो_mostly shaकरोw_nonpresent_or_rsvd_mask;
u64 __पढ़ो_mostly shaकरोw_nonpresent_or_rsvd_lower_gfn_mask;

u8 __पढ़ो_mostly shaकरोw_phys_bits;

अटल u64 generation_mmio_spte_mask(u64 gen)
अणु
	u64 mask;

	WARN_ON(gen & ~MMIO_SPTE_GEN_MASK);

	mask = (gen << MMIO_SPTE_GEN_LOW_SHIFT) & MMIO_SPTE_GEN_LOW_MASK;
	mask |= (gen << MMIO_SPTE_GEN_HIGH_SHIFT) & MMIO_SPTE_GEN_HIGH_MASK;
	वापस mask;
पूर्ण

u64 make_mmio_spte(काष्ठा kvm_vcpu *vcpu, u64 gfn, अचिन्हित पूर्णांक access)
अणु
	u64 gen = kvm_vcpu_memslots(vcpu)->generation & MMIO_SPTE_GEN_MASK;
	u64 spte = generation_mmio_spte_mask(gen);
	u64 gpa = gfn << PAGE_SHIFT;

	WARN_ON_ONCE(!shaकरोw_mmio_value);

	access &= shaकरोw_mmio_access_mask;
	spte |= shaकरोw_mmio_value | access;
	spte |= gpa | shaकरोw_nonpresent_or_rsvd_mask;
	spte |= (gpa & shaकरोw_nonpresent_or_rsvd_mask)
		<< SHADOW_NONPRESENT_OR_RSVD_MASK_LEN;

	वापस spte;
पूर्ण

अटल bool kvm_is_mmio_pfn(kvm_pfn_t pfn)
अणु
	अगर (pfn_valid(pfn))
		वापस !is_zero_pfn(pfn) && PageReserved(pfn_to_page(pfn)) &&
			/*
			 * Some reserved pages, such as those from NVDIMM
			 * DAX devices, are not क्रम MMIO, and can be mapped
			 * with cached memory type क्रम better perक्रमmance.
			 * However, the above check misconceives those pages
			 * as MMIO, and results in KVM mapping them with UC
			 * memory type, which would hurt the perक्रमmance.
			 * Thereक्रमe, we check the host memory type in addition
			 * and only treat UC/UC-/WC pages as MMIO.
			 */
			(!pat_enabled() || pat_pfn_immune_to_uc_mtrr(pfn));

	वापस !e820__mapped_raw_any(pfn_to_hpa(pfn),
				     pfn_to_hpa(pfn + 1) - 1,
				     E820_TYPE_RAM);
पूर्ण

पूर्णांक make_spte(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक pte_access, पूर्णांक level,
		     gfn_t gfn, kvm_pfn_t pfn, u64 old_spte, bool speculative,
		     bool can_unsync, bool host_writable, bool ad_disabled,
		     u64 *new_spte)
अणु
	u64 spte = SPTE_MMU_PRESENT_MASK;
	पूर्णांक ret = 0;

	अगर (ad_disabled)
		spte |= SPTE_TDP_AD_DISABLED_MASK;
	अन्यथा अगर (kvm_vcpu_ad_need_ग_लिखो_protect(vcpu))
		spte |= SPTE_TDP_AD_WRPROT_ONLY_MASK;

	/*
	 * Bits 62:52 of PAE SPTEs are reserved.  WARN अगर said bits are set
	 * अगर PAE paging may be employed (shaकरोw paging or any 32-bit KVM).
	 */
	WARN_ON_ONCE((!tdp_enabled || !IS_ENABLED(CONFIG_X86_64)) &&
		     (spte & SPTE_TDP_AD_MASK));

	/*
	 * For the EPT हाल, shaकरोw_present_mask is 0 अगर hardware
	 * supports exec-only page table entries.  In that हाल,
	 * ACC_USER_MASK and shaकरोw_user_mask are used to represent
	 * पढ़ो access.  See FNAME(gpte_access) in paging_पंचांगpl.h.
	 */
	spte |= shaकरोw_present_mask;
	अगर (!speculative)
		spte |= spte_shaकरोw_accessed_mask(spte);

	अगर (level > PG_LEVEL_4K && (pte_access & ACC_EXEC_MASK) &&
	    is_nx_huge_page_enabled()) अणु
		pte_access &= ~ACC_EXEC_MASK;
	पूर्ण

	अगर (pte_access & ACC_EXEC_MASK)
		spte |= shaकरोw_x_mask;
	अन्यथा
		spte |= shaकरोw_nx_mask;

	अगर (pte_access & ACC_USER_MASK)
		spte |= shaकरोw_user_mask;

	अगर (level > PG_LEVEL_4K)
		spte |= PT_PAGE_SIZE_MASK;
	अगर (tdp_enabled)
		spte |= अटल_call(kvm_x86_get_mt_mask)(vcpu, gfn,
			kvm_is_mmio_pfn(pfn));

	अगर (host_writable)
		spte |= shaकरोw_host_writable_mask;
	अन्यथा
		pte_access &= ~ACC_WRITE_MASK;

	अगर (!kvm_is_mmio_pfn(pfn))
		spte |= shaकरोw_me_mask;

	spte |= (u64)pfn << PAGE_SHIFT;

	अगर (pte_access & ACC_WRITE_MASK) अणु
		spte |= PT_WRITABLE_MASK | shaकरोw_mmu_writable_mask;

		/*
		 * Optimization: क्रम pte sync, अगर spte was writable the hash
		 * lookup is unnecessary (and expensive). Write protection
		 * is responsibility of mmu_get_page / kvm_sync_page.
		 * Same reasoning can be applied to dirty page accounting.
		 */
		अगर (!can_unsync && is_writable_pte(old_spte))
			जाओ out;

		अगर (mmu_need_ग_लिखो_protect(vcpu, gfn, can_unsync)) अणु
			pgprपूर्णांकk("%s: found shadow page for %llx, marking ro\n",
				 __func__, gfn);
			ret |= SET_SPTE_WRITE_PROTECTED_PT;
			pte_access &= ~ACC_WRITE_MASK;
			spte &= ~(PT_WRITABLE_MASK | shaकरोw_mmu_writable_mask);
		पूर्ण
	पूर्ण

	अगर (pte_access & ACC_WRITE_MASK)
		spte |= spte_shaकरोw_dirty_mask(spte);

	अगर (speculative)
		spte = mark_spte_क्रम_access_track(spte);

out:
	WARN_ON(is_mmio_spte(spte));
	*new_spte = spte;
	वापस ret;
पूर्ण

u64 make_nonleaf_spte(u64 *child_pt, bool ad_disabled)
अणु
	u64 spte = SPTE_MMU_PRESENT_MASK;

	spte |= __pa(child_pt) | shaकरोw_present_mask | PT_WRITABLE_MASK |
		shaकरोw_user_mask | shaकरोw_x_mask | shaकरोw_me_mask;

	अगर (ad_disabled)
		spte |= SPTE_TDP_AD_DISABLED_MASK;
	अन्यथा
		spte |= shaकरोw_accessed_mask;

	वापस spte;
पूर्ण

u64 kvm_mmu_changed_pte_notअगरier_make_spte(u64 old_spte, kvm_pfn_t new_pfn)
अणु
	u64 new_spte;

	new_spte = old_spte & ~PT64_BASE_ADDR_MASK;
	new_spte |= (u64)new_pfn << PAGE_SHIFT;

	new_spte &= ~PT_WRITABLE_MASK;
	new_spte &= ~shaकरोw_host_writable_mask;

	new_spte = mark_spte_क्रम_access_track(new_spte);

	वापस new_spte;
पूर्ण

अटल u8 kvm_get_shaकरोw_phys_bits(व्योम)
अणु
	/*
	 * boot_cpu_data.x86_phys_bits is reduced when MKTME or SME are detected
	 * in CPU detection code, but the processor treats those reduced bits as
	 * 'keyID' thus they are not reserved bits. Thereक्रमe KVM needs to look at
	 * the physical address bits reported by CPUID.
	 */
	अगर (likely(boot_cpu_data.extended_cpuid_level >= 0x80000008))
		वापस cpuid_eax(0x80000008) & 0xff;

	/*
	 * Quite weird to have VMX or SVM but not MAXPHYADDR; probably a VM with
	 * custom CPUID.  Proceed with whatever the kernel found since these features
	 * aren't भवizable (SME/SEV also require CPUIDs higher than 0x80000008).
	 */
	वापस boot_cpu_data.x86_phys_bits;
पूर्ण

u64 mark_spte_क्रम_access_track(u64 spte)
अणु
	अगर (spte_ad_enabled(spte))
		वापस spte & ~shaकरोw_accessed_mask;

	अगर (is_access_track_spte(spte))
		वापस spte;

	/*
	 * Making an Access Tracking PTE will result in removal of ग_लिखो access
	 * from the PTE. So, verअगरy that we will be able to restore the ग_लिखो
	 * access in the fast page fault path later on.
	 */
	WARN_ONCE((spte & PT_WRITABLE_MASK) &&
		  !spte_can_locklessly_be_made_writable(spte),
		  "kvm: Writable SPTE is not locklessly dirty-trackable\n");

	WARN_ONCE(spte & (SHADOW_ACC_TRACK_SAVED_BITS_MASK <<
			  SHADOW_ACC_TRACK_SAVED_BITS_SHIFT),
		  "kvm: Access Tracking saved bit locations are not zero\n");

	spte |= (spte & SHADOW_ACC_TRACK_SAVED_BITS_MASK) <<
		SHADOW_ACC_TRACK_SAVED_BITS_SHIFT;
	spte &= ~shaकरोw_acc_track_mask;

	वापस spte;
पूर्ण

व्योम kvm_mmu_set_mmio_spte_mask(u64 mmio_value, u64 mmio_mask, u64 access_mask)
अणु
	BUG_ON((u64)(अचिन्हित)access_mask != access_mask);
	WARN_ON(mmio_value & shaकरोw_nonpresent_or_rsvd_lower_gfn_mask);

	अगर (!enable_mmio_caching)
		mmio_value = 0;

	/*
	 * Disable MMIO caching अगर the MMIO value collides with the bits that
	 * are used to hold the relocated GFN when the L1TF mitigation is
	 * enabled.  This should never fire as there is no known hardware that
	 * can trigger this condition, e.g. SME/SEV CPUs that require a custom
	 * MMIO value are not susceptible to L1TF.
	 */
	अगर (WARN_ON(mmio_value & (shaकरोw_nonpresent_or_rsvd_mask <<
				  SHADOW_NONPRESENT_OR_RSVD_MASK_LEN)))
		mmio_value = 0;

	/*
	 * The masked MMIO value must obviously match itself and a हटाओd SPTE
	 * must not get a false positive.  Removed SPTEs and MMIO SPTEs should
	 * never collide as MMIO must set some RWX bits, and हटाओd SPTEs must
	 * not set any RWX bits.
	 */
	अगर (WARN_ON((mmio_value & mmio_mask) != mmio_value) ||
	    WARN_ON(mmio_value && (REMOVED_SPTE & mmio_mask) == mmio_value))
		mmio_value = 0;

	shaकरोw_mmio_value = mmio_value;
	shaकरोw_mmio_mask  = mmio_mask;
	shaकरोw_mmio_access_mask = access_mask;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_mmu_set_mmio_spte_mask);

व्योम kvm_mmu_set_ept_masks(bool has_ad_bits, bool has_exec_only)
अणु
	shaकरोw_user_mask	= VMX_EPT_READABLE_MASK;
	shaकरोw_accessed_mask	= has_ad_bits ? VMX_EPT_ACCESS_BIT : 0ull;
	shaकरोw_dirty_mask	= has_ad_bits ? VMX_EPT_सूचीTY_BIT : 0ull;
	shaकरोw_nx_mask		= 0ull;
	shaकरोw_x_mask		= VMX_EPT_EXECUTABLE_MASK;
	shaकरोw_present_mask	= has_exec_only ? 0ull : VMX_EPT_READABLE_MASK;
	shaकरोw_acc_track_mask	= VMX_EPT_RWX_MASK;
	shaकरोw_me_mask		= 0ull;

	shaकरोw_host_writable_mask = EPT_SPTE_HOST_WRITABLE;
	shaकरोw_mmu_writable_mask  = EPT_SPTE_MMU_WRITABLE;

	/*
	 * EPT Misconfigurations are generated अगर the value of bits 2:0
	 * of an EPT paging-काष्ठाure entry is 110b (ग_लिखो/execute).
	 */
	kvm_mmu_set_mmio_spte_mask(VMX_EPT_MISCONFIG_WX_VALUE,
				   VMX_EPT_RWX_MASK, 0);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_mmu_set_ept_masks);

व्योम kvm_mmu_reset_all_pte_masks(व्योम)
अणु
	u8 low_phys_bits;
	u64 mask;

	shaकरोw_phys_bits = kvm_get_shaकरोw_phys_bits();

	/*
	 * If the CPU has 46 or less physical address bits, then set an
	 * appropriate mask to guard against L1TF attacks. Otherwise, it is
	 * assumed that the CPU is not vulnerable to L1TF.
	 *
	 * Some Intel CPUs address the L1 cache using more PA bits than are
	 * reported by CPUID. Use the PA width of the L1 cache when possible
	 * to achieve more effective mitigation, e.g. अगर प्रणाली RAM overlaps
	 * the most signअगरicant bits of legal physical address space.
	 */
	shaकरोw_nonpresent_or_rsvd_mask = 0;
	low_phys_bits = boot_cpu_data.x86_phys_bits;
	अगर (boot_cpu_has_bug(X86_BUG_L1TF) &&
	    !WARN_ON_ONCE(boot_cpu_data.x86_cache_bits >=
			  52 - SHADOW_NONPRESENT_OR_RSVD_MASK_LEN)) अणु
		low_phys_bits = boot_cpu_data.x86_cache_bits
			- SHADOW_NONPRESENT_OR_RSVD_MASK_LEN;
		shaकरोw_nonpresent_or_rsvd_mask =
			rsvd_bits(low_phys_bits, boot_cpu_data.x86_cache_bits - 1);
	पूर्ण

	shaकरोw_nonpresent_or_rsvd_lower_gfn_mask =
		GENMASK_ULL(low_phys_bits - 1, PAGE_SHIFT);

	shaकरोw_user_mask	= PT_USER_MASK;
	shaकरोw_accessed_mask	= PT_ACCESSED_MASK;
	shaकरोw_dirty_mask	= PT_सूचीTY_MASK;
	shaकरोw_nx_mask		= PT64_NX_MASK;
	shaकरोw_x_mask		= 0;
	shaकरोw_present_mask	= PT_PRESENT_MASK;
	shaकरोw_acc_track_mask	= 0;
	shaकरोw_me_mask		= sme_me_mask;

	shaकरोw_host_writable_mask = DEFAULT_SPTE_HOST_WRITEABLE;
	shaकरोw_mmu_writable_mask  = DEFAULT_SPTE_MMU_WRITEABLE;

	/*
	 * Set a reserved PA bit in MMIO SPTEs to generate page faults with
	 * PFEC.RSVD=1 on MMIO accesses.  64-bit PTEs (PAE, x86-64, and EPT
	 * paging) support a maximum of 52 bits of PA, i.e. अगर the CPU supports
	 * 52-bit physical addresses then there are no reserved PA bits in the
	 * PTEs and so the reserved PA approach must be disabled.
	 */
	अगर (shaकरोw_phys_bits < 52)
		mask = BIT_ULL(51) | PT_PRESENT_MASK;
	अन्यथा
		mask = 0;

	kvm_mmu_set_mmio_spte_mask(mask, mask, ACC_WRITE_MASK | ACC_USER_MASK);
पूर्ण
