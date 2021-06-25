<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Kernel-based Virtual Machine driver क्रम Linux
 *
 * This module enables machines with Intel VT-x extensions to run भव
 * machines without emulation or binary translation.
 *
 * MMU support
 *
 * Copyright (C) 2006 Qumranet, Inc.
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 *
 * Authors:
 *   Yaniv Kamay  <yaniv@qumranet.com>
 *   Avi Kivity   <avi@qumranet.com>
 */

/*
 * We need the mmu code to access both 32-bit and 64-bit guest ptes,
 * so the code in this file is compiled twice, once per pte size.
 */

#अगर PTTYPE == 64
	#घोषणा pt_element_t u64
	#घोषणा guest_walker guest_walker64
	#घोषणा FNAME(name) paging##64_##name
	#घोषणा PT_BASE_ADDR_MASK PT64_BASE_ADDR_MASK
	#घोषणा PT_LVL_ADDR_MASK(lvl) PT64_LVL_ADDR_MASK(lvl)
	#घोषणा PT_LVL_OFFSET_MASK(lvl) PT64_LVL_OFFSET_MASK(lvl)
	#घोषणा PT_INDEX(addr, level) PT64_INDEX(addr, level)
	#घोषणा PT_LEVEL_BITS PT64_LEVEL_BITS
	#घोषणा PT_GUEST_सूचीTY_SHIFT PT_सूचीTY_SHIFT
	#घोषणा PT_GUEST_ACCESSED_SHIFT PT_ACCESSED_SHIFT
	#घोषणा PT_HAVE_ACCESSED_सूचीTY(mmu) true
	#अगर_घोषित CONFIG_X86_64
	#घोषणा PT_MAX_FULL_LEVELS PT64_ROOT_MAX_LEVEL
	#घोषणा CMPXCHG cmpxchg
	#अन्यथा
	#घोषणा CMPXCHG cmpxchg64
	#घोषणा PT_MAX_FULL_LEVELS 2
	#पूर्ण_अगर
#या_अगर PTTYPE == 32
	#घोषणा pt_element_t u32
	#घोषणा guest_walker guest_walker32
	#घोषणा FNAME(name) paging##32_##name
	#घोषणा PT_BASE_ADDR_MASK PT32_BASE_ADDR_MASK
	#घोषणा PT_LVL_ADDR_MASK(lvl) PT32_LVL_ADDR_MASK(lvl)
	#घोषणा PT_LVL_OFFSET_MASK(lvl) PT32_LVL_OFFSET_MASK(lvl)
	#घोषणा PT_INDEX(addr, level) PT32_INDEX(addr, level)
	#घोषणा PT_LEVEL_BITS PT32_LEVEL_BITS
	#घोषणा PT_MAX_FULL_LEVELS 2
	#घोषणा PT_GUEST_सूचीTY_SHIFT PT_सूचीTY_SHIFT
	#घोषणा PT_GUEST_ACCESSED_SHIFT PT_ACCESSED_SHIFT
	#घोषणा PT_HAVE_ACCESSED_सूचीTY(mmu) true
	#घोषणा CMPXCHG cmpxchg
#या_अगर PTTYPE == PTTYPE_EPT
	#घोषणा pt_element_t u64
	#घोषणा guest_walker guest_walkerEPT
	#घोषणा FNAME(name) ept_##name
	#घोषणा PT_BASE_ADDR_MASK PT64_BASE_ADDR_MASK
	#घोषणा PT_LVL_ADDR_MASK(lvl) PT64_LVL_ADDR_MASK(lvl)
	#घोषणा PT_LVL_OFFSET_MASK(lvl) PT64_LVL_OFFSET_MASK(lvl)
	#घोषणा PT_INDEX(addr, level) PT64_INDEX(addr, level)
	#घोषणा PT_LEVEL_BITS PT64_LEVEL_BITS
	#घोषणा PT_GUEST_सूचीTY_SHIFT 9
	#घोषणा PT_GUEST_ACCESSED_SHIFT 8
	#घोषणा PT_HAVE_ACCESSED_सूचीTY(mmu) ((mmu)->ept_ad)
	#घोषणा CMPXCHG cmpxchg64
	#घोषणा PT_MAX_FULL_LEVELS PT64_ROOT_MAX_LEVEL
#अन्यथा
	#त्रुटि Invalid PTTYPE value
#पूर्ण_अगर

#घोषणा PT_GUEST_सूचीTY_MASK    (1 << PT_GUEST_सूचीTY_SHIFT)
#घोषणा PT_GUEST_ACCESSED_MASK (1 << PT_GUEST_ACCESSED_SHIFT)

#घोषणा gpte_to_gfn_lvl FNAME(gpte_to_gfn_lvl)
#घोषणा gpte_to_gfn(pte) gpte_to_gfn_lvl((pte), PG_LEVEL_4K)

/*
 * The guest_walker काष्ठाure emulates the behavior of the hardware page
 * table walker.
 */
काष्ठा guest_walker अणु
	पूर्णांक level;
	अचिन्हित max_level;
	gfn_t table_gfn[PT_MAX_FULL_LEVELS];
	pt_element_t ptes[PT_MAX_FULL_LEVELS];
	pt_element_t prefetch_ptes[PTE_PREFETCH_NUM];
	gpa_t pte_gpa[PT_MAX_FULL_LEVELS];
	pt_element_t __user *ptep_user[PT_MAX_FULL_LEVELS];
	bool pte_writable[PT_MAX_FULL_LEVELS];
	अचिन्हित पूर्णांक pt_access[PT_MAX_FULL_LEVELS];
	अचिन्हित पूर्णांक pte_access;
	gfn_t gfn;
	काष्ठा x86_exception fault;
पूर्ण;

अटल gfn_t gpte_to_gfn_lvl(pt_element_t gpte, पूर्णांक lvl)
अणु
	वापस (gpte & PT_LVL_ADDR_MASK(lvl)) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत व्योम FNAME(protect_clean_gpte)(काष्ठा kvm_mmu *mmu, अचिन्हित *access,
					     अचिन्हित gpte)
अणु
	अचिन्हित mask;

	/* dirty bit is not supported, so no need to track it */
	अगर (!PT_HAVE_ACCESSED_सूचीTY(mmu))
		वापस;

	BUILD_BUG_ON(PT_WRITABLE_MASK != ACC_WRITE_MASK);

	mask = (अचिन्हित)~ACC_WRITE_MASK;
	/* Allow ग_लिखो access to dirty gptes */
	mask |= (gpte >> (PT_GUEST_सूचीTY_SHIFT - PT_WRITABLE_SHIFT)) &
		PT_WRITABLE_MASK;
	*access &= mask;
पूर्ण

अटल अंतरभूत पूर्णांक FNAME(is_present_gpte)(अचिन्हित दीर्घ pte)
अणु
#अगर PTTYPE != PTTYPE_EPT
	वापस pte & PT_PRESENT_MASK;
#अन्यथा
	वापस pte & 7;
#पूर्ण_अगर
पूर्ण

अटल bool FNAME(is_bad_mt_xwr)(काष्ठा rsvd_bits_validate *rsvd_check, u64 gpte)
अणु
#अगर PTTYPE != PTTYPE_EPT
	वापस false;
#अन्यथा
	वापस __is_bad_mt_xwr(rsvd_check, gpte);
#पूर्ण_अगर
पूर्ण

अटल bool FNAME(is_rsvd_bits_set)(काष्ठा kvm_mmu *mmu, u64 gpte, पूर्णांक level)
अणु
	वापस __is_rsvd_bits_set(&mmu->guest_rsvd_check, gpte, level) ||
	       FNAME(is_bad_mt_xwr)(&mmu->guest_rsvd_check, gpte);
पूर्ण

अटल पूर्णांक FNAME(cmpxchg_gpte)(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu *mmu,
			       pt_element_t __user *ptep_user, अचिन्हित index,
			       pt_element_t orig_pte, pt_element_t new_pte)
अणु
	पूर्णांक npages;
	pt_element_t ret;
	pt_element_t *table;
	काष्ठा page *page;

	npages = get_user_pages_fast((अचिन्हित दीर्घ)ptep_user, 1, FOLL_WRITE, &page);
	अगर (likely(npages == 1)) अणु
		table = kmap_atomic(page);
		ret = CMPXCHG(&table[index], orig_pte, new_pte);
		kunmap_atomic(table);

		kvm_release_page_dirty(page);
	पूर्ण अन्यथा अणु
		काष्ठा vm_area_काष्ठा *vma;
		अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)ptep_user & PAGE_MASK;
		अचिन्हित दीर्घ pfn;
		अचिन्हित दीर्घ paddr;

		mmap_पढ़ो_lock(current->mm);
		vma = find_vma_पूर्णांकersection(current->mm, vaddr, vaddr + PAGE_SIZE);
		अगर (!vma || !(vma->vm_flags & VM_PFNMAP)) अणु
			mmap_पढ़ो_unlock(current->mm);
			वापस -EFAULT;
		पूर्ण
		pfn = ((vaddr - vma->vm_start) >> PAGE_SHIFT) + vma->vm_pgoff;
		paddr = pfn << PAGE_SHIFT;
		table = memremap(paddr, PAGE_SIZE, MEMREMAP_WB);
		अगर (!table) अणु
			mmap_पढ़ो_unlock(current->mm);
			वापस -EFAULT;
		पूर्ण
		ret = CMPXCHG(&table[index], orig_pte, new_pte);
		memunmap(table);
		mmap_पढ़ो_unlock(current->mm);
	पूर्ण

	वापस (ret != orig_pte);
पूर्ण

अटल bool FNAME(prefetch_invalid_gpte)(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा kvm_mmu_page *sp, u64 *spte,
				  u64 gpte)
अणु
	अगर (!FNAME(is_present_gpte)(gpte))
		जाओ no_present;

	/* अगर accessed bit is not supported prefetch non accessed gpte */
	अगर (PT_HAVE_ACCESSED_सूचीTY(vcpu->arch.mmu) &&
	    !(gpte & PT_GUEST_ACCESSED_MASK))
		जाओ no_present;

	अगर (FNAME(is_rsvd_bits_set)(vcpu->arch.mmu, gpte, PG_LEVEL_4K))
		जाओ no_present;

	वापस false;

no_present:
	drop_spte(vcpu->kvm, spte);
	वापस true;
पूर्ण

/*
 * For PTTYPE_EPT, a page table can be executable but not पढ़ोable
 * on supported processors. Thereक्रमe, set_spte करोes not स्वतःmatically
 * set bit 0 अगर execute only is supported. Here, we repurpose ACC_USER_MASK
 * to signअगरy पढ़ोability since it isn't used in the EPT हाल
 */
अटल अंतरभूत अचिन्हित FNAME(gpte_access)(u64 gpte)
अणु
	अचिन्हित access;
#अगर PTTYPE == PTTYPE_EPT
	access = ((gpte & VMX_EPT_WRITABLE_MASK) ? ACC_WRITE_MASK : 0) |
		((gpte & VMX_EPT_EXECUTABLE_MASK) ? ACC_EXEC_MASK : 0) |
		((gpte & VMX_EPT_READABLE_MASK) ? ACC_USER_MASK : 0);
#अन्यथा
	BUILD_BUG_ON(ACC_EXEC_MASK != PT_PRESENT_MASK);
	BUILD_BUG_ON(ACC_EXEC_MASK != 1);
	access = gpte & (PT_WRITABLE_MASK | PT_USER_MASK | PT_PRESENT_MASK);
	/* Combine NX with P (which is set here) to get ACC_EXEC_MASK.  */
	access ^= (gpte >> PT64_NX_SHIFT);
#पूर्ण_अगर

	वापस access;
पूर्ण

अटल पूर्णांक FNAME(update_accessed_dirty_bits)(काष्ठा kvm_vcpu *vcpu,
					     काष्ठा kvm_mmu *mmu,
					     काष्ठा guest_walker *walker,
					     gpa_t addr, पूर्णांक ग_लिखो_fault)
अणु
	अचिन्हित level, index;
	pt_element_t pte, orig_pte;
	pt_element_t __user *ptep_user;
	gfn_t table_gfn;
	पूर्णांक ret;

	/* dirty/accessed bits are not supported, so no need to update them */
	अगर (!PT_HAVE_ACCESSED_सूचीTY(mmu))
		वापस 0;

	क्रम (level = walker->max_level; level >= walker->level; --level) अणु
		pte = orig_pte = walker->ptes[level - 1];
		table_gfn = walker->table_gfn[level - 1];
		ptep_user = walker->ptep_user[level - 1];
		index = offset_in_page(ptep_user) / माप(pt_element_t);
		अगर (!(pte & PT_GUEST_ACCESSED_MASK)) अणु
			trace_kvm_mmu_set_accessed_bit(table_gfn, index, माप(pte));
			pte |= PT_GUEST_ACCESSED_MASK;
		पूर्ण
		अगर (level == walker->level && ग_लिखो_fault &&
				!(pte & PT_GUEST_सूचीTY_MASK)) अणु
			trace_kvm_mmu_set_dirty_bit(table_gfn, index, माप(pte));
#अगर PTTYPE == PTTYPE_EPT
			अगर (kvm_x86_ops.nested_ops->ग_लिखो_log_dirty(vcpu, addr))
				वापस -EINVAL;
#पूर्ण_अगर
			pte |= PT_GUEST_सूचीTY_MASK;
		पूर्ण
		अगर (pte == orig_pte)
			जारी;

		/*
		 * If the slot is पढ़ो-only, simply करो not process the accessed
		 * and dirty bits.  This is the correct thing to करो अगर the slot
		 * is ROM, and page tables in पढ़ो-as-ROM/ग_लिखो-as-MMIO slots
		 * are only supported अगर the accessed and dirty bits are alपढ़ोy
		 * set in the ROM (so that MMIO ग_लिखोs are never needed).
		 *
		 * Note that NPT करोes not allow this at all and faults, since
		 * it always wants nested page table entries क्रम the guest
		 * page tables to be writable.  And EPT works but will simply
		 * overग_लिखो the पढ़ो-only memory to set the accessed and dirty
		 * bits.
		 */
		अगर (unlikely(!walker->pte_writable[level - 1]))
			जारी;

		ret = FNAME(cmpxchg_gpte)(vcpu, mmu, ptep_user, index, orig_pte, pte);
		अगर (ret)
			वापस ret;

		kvm_vcpu_mark_page_dirty(vcpu, table_gfn);
		walker->ptes[level - 1] = pte;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित FNAME(gpte_pkeys)(काष्ठा kvm_vcpu *vcpu, u64 gpte)
अणु
	अचिन्हित pkeys = 0;
#अगर PTTYPE == 64
	pte_t pte = अणु.pte = gpteपूर्ण;

	pkeys = pte_flags_pkey(pte_flags(pte));
#पूर्ण_अगर
	वापस pkeys;
पूर्ण

/*
 * Fetch a guest pte क्रम a guest भव address, or क्रम an L2's GPA.
 */
अटल पूर्णांक FNAME(walk_addr_generic)(काष्ठा guest_walker *walker,
				    काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu *mmu,
				    gpa_t addr, u32 access)
अणु
	पूर्णांक ret;
	pt_element_t pte;
	pt_element_t __user *ptep_user;
	gfn_t table_gfn;
	u64 pt_access, pte_access;
	अचिन्हित index, accessed_dirty, pte_pkey;
	अचिन्हित nested_access;
	gpa_t pte_gpa;
	bool have_ad;
	पूर्णांक offset;
	u64 walk_nx_mask = 0;
	स्थिर पूर्णांक ग_लिखो_fault = access & PFERR_WRITE_MASK;
	स्थिर पूर्णांक user_fault  = access & PFERR_USER_MASK;
	स्थिर पूर्णांक fetch_fault = access & PFERR_FETCH_MASK;
	u16 errcode = 0;
	gpa_t real_gpa;
	gfn_t gfn;

	trace_kvm_mmu_pagetable_walk(addr, access);
retry_walk:
	walker->level = mmu->root_level;
	pte           = mmu->get_guest_pgd(vcpu);
	have_ad       = PT_HAVE_ACCESSED_सूचीTY(mmu);

#अगर PTTYPE == 64
	walk_nx_mask = 1ULL << PT64_NX_SHIFT;
	अगर (walker->level == PT32E_ROOT_LEVEL) अणु
		pte = mmu->get_pdptr(vcpu, (addr >> 30) & 3);
		trace_kvm_mmu_paging_element(pte, walker->level);
		अगर (!FNAME(is_present_gpte)(pte))
			जाओ error;
		--walker->level;
	पूर्ण
#पूर्ण_अगर
	walker->max_level = walker->level;
	ASSERT(!(is_दीर्घ_mode(vcpu) && !is_pae(vcpu)));

	/*
	 * FIXME: on Intel processors, loads of the PDPTE रेजिस्टरs क्रम PAE paging
	 * by the MOV to CR inकाष्ठाion are treated as पढ़ोs and करो not cause the
	 * processor to set the dirty flag in any EPT paging-काष्ठाure entry.
	 */
	nested_access = (have_ad ? PFERR_WRITE_MASK : 0) | PFERR_USER_MASK;

	pte_access = ~0;
	++walker->level;

	करो अणु
		अचिन्हित दीर्घ host_addr;

		pt_access = pte_access;
		--walker->level;

		index = PT_INDEX(addr, walker->level);
		table_gfn = gpte_to_gfn(pte);
		offset    = index * माप(pt_element_t);
		pte_gpa   = gfn_to_gpa(table_gfn) + offset;

		BUG_ON(walker->level < 1);
		walker->table_gfn[walker->level - 1] = table_gfn;
		walker->pte_gpa[walker->level - 1] = pte_gpa;

		real_gpa = mmu->translate_gpa(vcpu, gfn_to_gpa(table_gfn),
					      nested_access,
					      &walker->fault);

		/*
		 * FIXME: This can happen अगर emulation (क्रम of an INS/OUTS
		 * inकाष्ठाion) triggers a nested page fault.  The निकास
		 * qualअगरication / निकास info field will incorrectly have
		 * "guest page access" as the nested page fault's cause,
		 * instead of "guest page structure access".  To fix this,
		 * the x86_exception काष्ठा should be augmented with enough
		 * inक्रमmation to fix the निकास_qualअगरication or निकास_info_1
		 * fields.
		 */
		अगर (unlikely(real_gpa == UNMAPPED_GVA))
			वापस 0;

		host_addr = kvm_vcpu_gfn_to_hva_prot(vcpu, gpa_to_gfn(real_gpa),
					    &walker->pte_writable[walker->level - 1]);
		अगर (unlikely(kvm_is_error_hva(host_addr)))
			जाओ error;

		ptep_user = (pt_element_t __user *)((व्योम *)host_addr + offset);
		अगर (unlikely(__get_user(pte, ptep_user)))
			जाओ error;
		walker->ptep_user[walker->level - 1] = ptep_user;

		trace_kvm_mmu_paging_element(pte, walker->level);

		/*
		 * Inverting the NX it lets us AND it like other
		 * permission bits.
		 */
		pte_access = pt_access & (pte ^ walk_nx_mask);

		अगर (unlikely(!FNAME(is_present_gpte)(pte)))
			जाओ error;

		अगर (unlikely(FNAME(is_rsvd_bits_set)(mmu, pte, walker->level))) अणु
			errcode = PFERR_RSVD_MASK | PFERR_PRESENT_MASK;
			जाओ error;
		पूर्ण

		walker->ptes[walker->level - 1] = pte;

		/* Convert to ACC_*_MASK flags क्रम काष्ठा guest_walker.  */
		walker->pt_access[walker->level - 1] = FNAME(gpte_access)(pt_access ^ walk_nx_mask);
	पूर्ण जबतक (!is_last_gpte(mmu, walker->level, pte));

	pte_pkey = FNAME(gpte_pkeys)(vcpu, pte);
	accessed_dirty = have_ad ? pte_access & PT_GUEST_ACCESSED_MASK : 0;

	/* Convert to ACC_*_MASK flags क्रम काष्ठा guest_walker.  */
	walker->pte_access = FNAME(gpte_access)(pte_access ^ walk_nx_mask);
	errcode = permission_fault(vcpu, mmu, walker->pte_access, pte_pkey, access);
	अगर (unlikely(errcode))
		जाओ error;

	gfn = gpte_to_gfn_lvl(pte, walker->level);
	gfn += (addr & PT_LVL_OFFSET_MASK(walker->level)) >> PAGE_SHIFT;

	अगर (PTTYPE == 32 && walker->level > PG_LEVEL_4K && is_cpuid_PSE36())
		gfn += pse36_gfn_delta(pte);

	real_gpa = mmu->translate_gpa(vcpu, gfn_to_gpa(gfn), access, &walker->fault);
	अगर (real_gpa == UNMAPPED_GVA)
		वापस 0;

	walker->gfn = real_gpa >> PAGE_SHIFT;

	अगर (!ग_लिखो_fault)
		FNAME(protect_clean_gpte)(mmu, &walker->pte_access, pte);
	अन्यथा
		/*
		 * On a ग_लिखो fault, fold the dirty bit पूर्णांकo accessed_dirty.
		 * For modes without A/D bits support accessed_dirty will be
		 * always clear.
		 */
		accessed_dirty &= pte >>
			(PT_GUEST_सूचीTY_SHIFT - PT_GUEST_ACCESSED_SHIFT);

	अगर (unlikely(!accessed_dirty)) अणु
		ret = FNAME(update_accessed_dirty_bits)(vcpu, mmu, walker,
							addr, ग_लिखो_fault);
		अगर (unlikely(ret < 0))
			जाओ error;
		अन्यथा अगर (ret)
			जाओ retry_walk;
	पूर्ण

	pgprपूर्णांकk("%s: pte %llx pte_access %x pt_access %x\n",
		 __func__, (u64)pte, walker->pte_access,
		 walker->pt_access[walker->level - 1]);
	वापस 1;

error:
	errcode |= ग_लिखो_fault | user_fault;
	अगर (fetch_fault && (mmu->nx ||
			    kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_SMEP)))
		errcode |= PFERR_FETCH_MASK;

	walker->fault.vector = PF_VECTOR;
	walker->fault.error_code_valid = true;
	walker->fault.error_code = errcode;

#अगर PTTYPE == PTTYPE_EPT
	/*
	 * Use PFERR_RSVD_MASK in error_code to to tell अगर EPT
	 * misconfiguration requires to be injected. The detection is
	 * करोne by is_rsvd_bits_set() above.
	 *
	 * We set up the value of निकास_qualअगरication to inject:
	 * [2:0] - Derive from the access bits. The निकास_qualअगरication might be
	 *         out of date अगर it is serving an EPT misconfiguration.
	 * [5:3] - Calculated by the page walk of the guest EPT page tables
	 * [7:8] - Derived from [7:8] of real निकास_qualअगरication
	 *
	 * The other bits are set to 0.
	 */
	अगर (!(errcode & PFERR_RSVD_MASK)) अणु
		vcpu->arch.निकास_qualअगरication &= 0x180;
		अगर (ग_लिखो_fault)
			vcpu->arch.निकास_qualअगरication |= EPT_VIOLATION_ACC_WRITE;
		अगर (user_fault)
			vcpu->arch.निकास_qualअगरication |= EPT_VIOLATION_ACC_READ;
		अगर (fetch_fault)
			vcpu->arch.निकास_qualअगरication |= EPT_VIOLATION_ACC_INSTR;
		vcpu->arch.निकास_qualअगरication |= (pte_access & 0x7) << 3;
	पूर्ण
#पूर्ण_अगर
	walker->fault.address = addr;
	walker->fault.nested_page_fault = mmu != vcpu->arch.walk_mmu;
	walker->fault.async_page_fault = false;

	trace_kvm_mmu_walker_error(walker->fault.error_code);
	वापस 0;
पूर्ण

अटल पूर्णांक FNAME(walk_addr)(काष्ठा guest_walker *walker,
			    काष्ठा kvm_vcpu *vcpu, gpa_t addr, u32 access)
अणु
	वापस FNAME(walk_addr_generic)(walker, vcpu, vcpu->arch.mmu, addr,
					access);
पूर्ण

#अगर PTTYPE != PTTYPE_EPT
अटल पूर्णांक FNAME(walk_addr_nested)(काष्ठा guest_walker *walker,
				   काष्ठा kvm_vcpu *vcpu, gva_t addr,
				   u32 access)
अणु
	वापस FNAME(walk_addr_generic)(walker, vcpu, &vcpu->arch.nested_mmu,
					addr, access);
पूर्ण
#पूर्ण_अगर

अटल bool
FNAME(prefetch_gpte)(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu_page *sp,
		     u64 *spte, pt_element_t gpte, bool no_dirty_log)
अणु
	अचिन्हित pte_access;
	gfn_t gfn;
	kvm_pfn_t pfn;

	अगर (FNAME(prefetch_invalid_gpte)(vcpu, sp, spte, gpte))
		वापस false;

	pgprपूर्णांकk("%s: gpte %llx spte %p\n", __func__, (u64)gpte, spte);

	gfn = gpte_to_gfn(gpte);
	pte_access = sp->role.access & FNAME(gpte_access)(gpte);
	FNAME(protect_clean_gpte)(vcpu->arch.mmu, &pte_access, gpte);
	pfn = pte_prefetch_gfn_to_pfn(vcpu, gfn,
			no_dirty_log && (pte_access & ACC_WRITE_MASK));
	अगर (is_error_pfn(pfn))
		वापस false;

	/*
	 * we call mmu_set_spte() with host_writable = true because
	 * pte_prefetch_gfn_to_pfn always माला_लो a writable pfn.
	 */
	mmu_set_spte(vcpu, spte, pte_access, false, PG_LEVEL_4K, gfn, pfn,
		     true, true);

	kvm_release_pfn_clean(pfn);
	वापस true;
पूर्ण

अटल व्योम FNAME(update_pte)(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu_page *sp,
			      u64 *spte, स्थिर व्योम *pte)
अणु
	pt_element_t gpte = *(स्थिर pt_element_t *)pte;

	FNAME(prefetch_gpte)(vcpu, sp, spte, gpte, false);
पूर्ण

अटल bool FNAME(gpte_changed)(काष्ठा kvm_vcpu *vcpu,
				काष्ठा guest_walker *gw, पूर्णांक level)
अणु
	pt_element_t curr_pte;
	gpa_t base_gpa, pte_gpa = gw->pte_gpa[level - 1];
	u64 mask;
	पूर्णांक r, index;

	अगर (level == PG_LEVEL_4K) अणु
		mask = PTE_PREFETCH_NUM * माप(pt_element_t) - 1;
		base_gpa = pte_gpa & ~mask;
		index = (pte_gpa - base_gpa) / माप(pt_element_t);

		r = kvm_vcpu_पढ़ो_guest_atomic(vcpu, base_gpa,
				gw->prefetch_ptes, माप(gw->prefetch_ptes));
		curr_pte = gw->prefetch_ptes[index];
	पूर्ण अन्यथा
		r = kvm_vcpu_पढ़ो_guest_atomic(vcpu, pte_gpa,
				  &curr_pte, माप(curr_pte));

	वापस r || curr_pte != gw->ptes[level - 1];
पूर्ण

अटल व्योम FNAME(pte_prefetch)(काष्ठा kvm_vcpu *vcpu, काष्ठा guest_walker *gw,
				u64 *sptep)
अणु
	काष्ठा kvm_mmu_page *sp;
	pt_element_t *gptep = gw->prefetch_ptes;
	u64 *spte;
	पूर्णांक i;

	sp = sptep_to_sp(sptep);

	अगर (sp->role.level > PG_LEVEL_4K)
		वापस;

	/*
	 * If addresses are being invalidated, skip prefetching to aव्योम
	 * accidentally prefetching those addresses.
	 */
	अगर (unlikely(vcpu->kvm->mmu_notअगरier_count))
		वापस;

	अगर (sp->role.direct)
		वापस __direct_pte_prefetch(vcpu, sp, sptep);

	i = (sptep - sp->spt) & ~(PTE_PREFETCH_NUM - 1);
	spte = sp->spt + i;

	क्रम (i = 0; i < PTE_PREFETCH_NUM; i++, spte++) अणु
		अगर (spte == sptep)
			जारी;

		अगर (is_shaकरोw_present_pte(*spte))
			जारी;

		अगर (!FNAME(prefetch_gpte)(vcpu, sp, spte, gptep[i], true))
			अवरोध;
	पूर्ण
पूर्ण

/*
 * Fetch a shaकरोw pte क्रम a specअगरic level in the paging hierarchy.
 * If the guest tries to ग_लिखो a ग_लिखो-रक्षित page, we need to
 * emulate this operation, वापस 1 to indicate this हाल.
 */
अटल पूर्णांक FNAME(fetch)(काष्ठा kvm_vcpu *vcpu, gpa_t addr,
			 काष्ठा guest_walker *gw, u32 error_code,
			 पूर्णांक max_level, kvm_pfn_t pfn, bool map_writable,
			 bool prefault)
अणु
	bool nx_huge_page_workaround_enabled = is_nx_huge_page_enabled();
	bool ग_लिखो_fault = error_code & PFERR_WRITE_MASK;
	bool exec = error_code & PFERR_FETCH_MASK;
	bool huge_page_disallowed = exec && nx_huge_page_workaround_enabled;
	काष्ठा kvm_mmu_page *sp = शून्य;
	काष्ठा kvm_shaकरोw_walk_iterator it;
	अचिन्हित पूर्णांक direct_access, access;
	पूर्णांक top_level, level, req_level, ret;
	gfn_t base_gfn = gw->gfn;

	direct_access = gw->pte_access;

	top_level = vcpu->arch.mmu->root_level;
	अगर (top_level == PT32E_ROOT_LEVEL)
		top_level = PT32_ROOT_LEVEL;
	/*
	 * Verअगरy that the top-level gpte is still there.  Since the page
	 * is a root page, it is either ग_लिखो रक्षित (and cannot be
	 * changed from now on) or it is invalid (in which हाल, we करोn't
	 * really care अगर it changes underneath us after this poपूर्णांक).
	 */
	अगर (FNAME(gpte_changed)(vcpu, gw, top_level))
		जाओ out_gpte_changed;

	अगर (WARN_ON(!VALID_PAGE(vcpu->arch.mmu->root_hpa)))
		जाओ out_gpte_changed;

	क्रम (shaकरोw_walk_init(&it, vcpu, addr);
	     shaकरोw_walk_okay(&it) && it.level > gw->level;
	     shaकरोw_walk_next(&it)) अणु
		gfn_t table_gfn;

		clear_sp_ग_लिखो_flooding_count(it.sptep);
		drop_large_spte(vcpu, it.sptep);

		sp = शून्य;
		अगर (!is_shaकरोw_present_pte(*it.sptep)) अणु
			table_gfn = gw->table_gfn[it.level - 2];
			access = gw->pt_access[it.level - 2];
			sp = kvm_mmu_get_page(vcpu, table_gfn, addr, it.level-1,
					      false, access);
		पूर्ण

		/*
		 * Verअगरy that the gpte in the page we've just ग_लिखो
		 * रक्षित is still there.
		 */
		अगर (FNAME(gpte_changed)(vcpu, gw, it.level - 1))
			जाओ out_gpte_changed;

		अगर (sp)
			link_shaकरोw_page(vcpu, it.sptep, sp);
	पूर्ण

	level = kvm_mmu_hugepage_adjust(vcpu, gw->gfn, max_level, &pfn,
					huge_page_disallowed, &req_level);

	trace_kvm_mmu_spte_requested(addr, gw->level, pfn);

	क्रम (; shaकरोw_walk_okay(&it); shaकरोw_walk_next(&it)) अणु
		clear_sp_ग_लिखो_flooding_count(it.sptep);

		/*
		 * We cannot overग_लिखो existing page tables with an NX
		 * large page, as the leaf could be executable.
		 */
		अगर (nx_huge_page_workaround_enabled)
			disallowed_hugepage_adjust(*it.sptep, gw->gfn, it.level,
						   &pfn, &level);

		base_gfn = gw->gfn & ~(KVM_PAGES_PER_HPAGE(it.level) - 1);
		अगर (it.level == level)
			अवरोध;

		validate_direct_spte(vcpu, it.sptep, direct_access);

		drop_large_spte(vcpu, it.sptep);

		अगर (!is_shaकरोw_present_pte(*it.sptep)) अणु
			sp = kvm_mmu_get_page(vcpu, base_gfn, addr,
					      it.level - 1, true, direct_access);
			link_shaकरोw_page(vcpu, it.sptep, sp);
			अगर (huge_page_disallowed && req_level >= it.level)
				account_huge_nx_page(vcpu->kvm, sp);
		पूर्ण
	पूर्ण

	ret = mmu_set_spte(vcpu, it.sptep, gw->pte_access, ग_लिखो_fault,
			   it.level, base_gfn, pfn, prefault, map_writable);
	अगर (ret == RET_PF_SPURIOUS)
		वापस ret;

	FNAME(pte_prefetch)(vcpu, gw, it.sptep);
	++vcpu->stat.pf_fixed;
	वापस ret;

out_gpte_changed:
	वापस RET_PF_RETRY;
पूर्ण

 /*
 * To see whether the mapped gfn can ग_लिखो its page table in the current
 * mapping.
 *
 * It is the helper function of FNAME(page_fault). When guest uses large page
 * size to map the writable gfn which is used as current page table, we should
 * क्रमce kvm to use small page size to map it because new shaकरोw page will be
 * created when kvm establishes shaकरोw page table that stop kvm using large
 * page size. Do it early can aव्योम unnecessary #PF and emulation.
 *
 * @ग_लिखो_fault_to_shaकरोw_pgtable will वापस true अगर the fault gfn is
 * currently used as its page table.
 *
 * Note: the PDPT page table is not checked क्रम PAE-32 bit guest. It is ok
 * since the PDPT is always shaकरोwed, that means, we can not use large page
 * size to map the gfn which is used as PDPT.
 */
अटल bool
FNAME(is_self_change_mapping)(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा guest_walker *walker, bool user_fault,
			      bool *ग_लिखो_fault_to_shaकरोw_pgtable)
अणु
	पूर्णांक level;
	gfn_t mask = ~(KVM_PAGES_PER_HPAGE(walker->level) - 1);
	bool self_changed = false;

	अगर (!(walker->pte_access & ACC_WRITE_MASK ||
	      (!is_ग_लिखो_protection(vcpu) && !user_fault)))
		वापस false;

	क्रम (level = walker->level; level <= walker->max_level; level++) अणु
		gfn_t gfn = walker->gfn ^ walker->table_gfn[level - 1];

		self_changed |= !(gfn & mask);
		*ग_लिखो_fault_to_shaकरोw_pgtable |= !gfn;
	पूर्ण

	वापस self_changed;
पूर्ण

/*
 * Page fault handler.  There are several causes क्रम a page fault:
 *   - there is no shaकरोw pte क्रम the guest pte
 *   - ग_लिखो access through a shaकरोw pte marked पढ़ो only so that we can set
 *     the dirty bit
 *   - ग_लिखो access to a shaकरोw pte marked पढ़ो only so we can update the page
 *     dirty biपंचांगap, when userspace requests it
 *   - mmio access; in this हाल we will never install a present shaकरोw pte
 *   - normal guest page fault due to the guest pte marked not present, not
 *     writable, or not executable
 *
 *  Returns: 1 अगर we need to emulate the inकाष्ठाion, 0 otherwise, or
 *           a negative value on error.
 */
अटल पूर्णांक FNAME(page_fault)(काष्ठा kvm_vcpu *vcpu, gpa_t addr, u32 error_code,
			     bool prefault)
अणु
	bool ग_लिखो_fault = error_code & PFERR_WRITE_MASK;
	bool user_fault = error_code & PFERR_USER_MASK;
	काष्ठा guest_walker walker;
	पूर्णांक r;
	kvm_pfn_t pfn;
	hva_t hva;
	अचिन्हित दीर्घ mmu_seq;
	bool map_writable, is_self_change_mapping;
	पूर्णांक max_level;

	pgprपूर्णांकk("%s: addr %lx err %x\n", __func__, addr, error_code);

	/*
	 * If PFEC.RSVD is set, this is a shaकरोw page fault.
	 * The bit needs to be cleared beक्रमe walking guest page tables.
	 */
	error_code &= ~PFERR_RSVD_MASK;

	/*
	 * Look up the guest pte क्रम the faulting address.
	 */
	r = FNAME(walk_addr)(&walker, vcpu, addr, error_code);

	/*
	 * The page is not mapped by the guest.  Let the guest handle it.
	 */
	अगर (!r) अणु
		pgprपूर्णांकk("%s: guest page fault\n", __func__);
		अगर (!prefault)
			kvm_inject_emulated_page_fault(vcpu, &walker.fault);

		वापस RET_PF_RETRY;
	पूर्ण

	अगर (page_fault_handle_page_track(vcpu, error_code, walker.gfn)) अणु
		shaकरोw_page_table_clear_flood(vcpu, addr);
		वापस RET_PF_EMULATE;
	पूर्ण

	r = mmu_topup_memory_caches(vcpu, true);
	अगर (r)
		वापस r;

	vcpu->arch.ग_लिखो_fault_to_shaकरोw_pgtable = false;

	is_self_change_mapping = FNAME(is_self_change_mapping)(vcpu,
	      &walker, user_fault, &vcpu->arch.ग_लिखो_fault_to_shaकरोw_pgtable);

	अगर (is_self_change_mapping)
		max_level = PG_LEVEL_4K;
	अन्यथा
		max_level = walker.level;

	mmu_seq = vcpu->kvm->mmu_notअगरier_seq;
	smp_rmb();

	अगर (try_async_pf(vcpu, prefault, walker.gfn, addr, &pfn, &hva,
			 ग_लिखो_fault, &map_writable))
		वापस RET_PF_RETRY;

	अगर (handle_abnormal_pfn(vcpu, addr, walker.gfn, pfn, walker.pte_access, &r))
		वापस r;

	/*
	 * Do not change pte_access अगर the pfn is a mmio page, otherwise
	 * we will cache the incorrect access पूर्णांकo mmio spte.
	 */
	अगर (ग_लिखो_fault && !(walker.pte_access & ACC_WRITE_MASK) &&
	     !is_ग_लिखो_protection(vcpu) && !user_fault &&
	      !is_noslot_pfn(pfn)) अणु
		walker.pte_access |= ACC_WRITE_MASK;
		walker.pte_access &= ~ACC_USER_MASK;

		/*
		 * If we converted a user page to a kernel page,
		 * so that the kernel can ग_लिखो to it when cr0.wp=0,
		 * then we should prevent the kernel from executing it
		 * अगर SMEP is enabled.
		 */
		अगर (kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_SMEP))
			walker.pte_access &= ~ACC_EXEC_MASK;
	पूर्ण

	r = RET_PF_RETRY;
	ग_लिखो_lock(&vcpu->kvm->mmu_lock);
	अगर (!is_noslot_pfn(pfn) && mmu_notअगरier_retry_hva(vcpu->kvm, mmu_seq, hva))
		जाओ out_unlock;

	kvm_mmu_audit(vcpu, AUDIT_PRE_PAGE_FAULT);
	r = make_mmu_pages_available(vcpu);
	अगर (r)
		जाओ out_unlock;
	r = FNAME(fetch)(vcpu, addr, &walker, error_code, max_level, pfn,
			 map_writable, prefault);
	kvm_mmu_audit(vcpu, AUDIT_POST_PAGE_FAULT);

out_unlock:
	ग_लिखो_unlock(&vcpu->kvm->mmu_lock);
	kvm_release_pfn_clean(pfn);
	वापस r;
पूर्ण

अटल gpa_t FNAME(get_level1_sp_gpa)(काष्ठा kvm_mmu_page *sp)
अणु
	पूर्णांक offset = 0;

	WARN_ON(sp->role.level != PG_LEVEL_4K);

	अगर (PTTYPE == 32)
		offset = sp->role.quadrant << PT64_LEVEL_BITS;

	वापस gfn_to_gpa(sp->gfn) + offset * माप(pt_element_t);
पूर्ण

अटल व्योम FNAME(invlpg)(काष्ठा kvm_vcpu *vcpu, gva_t gva, hpa_t root_hpa)
अणु
	काष्ठा kvm_shaकरोw_walk_iterator iterator;
	काष्ठा kvm_mmu_page *sp;
	u64 old_spte;
	पूर्णांक level;
	u64 *sptep;

	vcpu_clear_mmio_info(vcpu, gva);

	/*
	 * No need to check वापस value here, rmap_can_add() can
	 * help us to skip pte prefetch later.
	 */
	mmu_topup_memory_caches(vcpu, true);

	अगर (!VALID_PAGE(root_hpa)) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	ग_लिखो_lock(&vcpu->kvm->mmu_lock);
	क्रम_each_shaकरोw_entry_using_root(vcpu, root_hpa, gva, iterator) अणु
		level = iterator.level;
		sptep = iterator.sptep;

		sp = sptep_to_sp(sptep);
		old_spte = *sptep;
		अगर (is_last_spte(old_spte, level)) अणु
			pt_element_t gpte;
			gpa_t pte_gpa;

			अगर (!sp->unsync)
				अवरोध;

			pte_gpa = FNAME(get_level1_sp_gpa)(sp);
			pte_gpa += (sptep - sp->spt) * माप(pt_element_t);

			mmu_page_zap_pte(vcpu->kvm, sp, sptep, शून्य);
			अगर (is_shaकरोw_present_pte(old_spte))
				kvm_flush_remote_tlbs_with_address(vcpu->kvm,
					sp->gfn, KVM_PAGES_PER_HPAGE(sp->role.level));

			अगर (!rmap_can_add(vcpu))
				अवरोध;

			अगर (kvm_vcpu_पढ़ो_guest_atomic(vcpu, pte_gpa, &gpte,
						       माप(pt_element_t)))
				अवरोध;

			FNAME(update_pte)(vcpu, sp, sptep, &gpte);
		पूर्ण

		अगर (!is_shaकरोw_present_pte(*sptep) || !sp->unsync_children)
			अवरोध;
	पूर्ण
	ग_लिखो_unlock(&vcpu->kvm->mmu_lock);
पूर्ण

/* Note, @addr is a GPA when gva_to_gpa() translates an L2 GPA to an L1 GPA. */
अटल gpa_t FNAME(gva_to_gpa)(काष्ठा kvm_vcpu *vcpu, gpa_t addr, u32 access,
			       काष्ठा x86_exception *exception)
अणु
	काष्ठा guest_walker walker;
	gpa_t gpa = UNMAPPED_GVA;
	पूर्णांक r;

	r = FNAME(walk_addr)(&walker, vcpu, addr, access);

	अगर (r) अणु
		gpa = gfn_to_gpa(walker.gfn);
		gpa |= addr & ~PAGE_MASK;
	पूर्ण अन्यथा अगर (exception)
		*exception = walker.fault;

	वापस gpa;
पूर्ण

#अगर PTTYPE != PTTYPE_EPT
/* Note, gva_to_gpa_nested() is only used to translate L2 GVAs. */
अटल gpa_t FNAME(gva_to_gpa_nested)(काष्ठा kvm_vcpu *vcpu, gpa_t vaddr,
				      u32 access,
				      काष्ठा x86_exception *exception)
अणु
	काष्ठा guest_walker walker;
	gpa_t gpa = UNMAPPED_GVA;
	पूर्णांक r;

#अगर_अघोषित CONFIG_X86_64
	/* A 64-bit GVA should be impossible on 32-bit KVM. */
	WARN_ON_ONCE(vaddr >> 32);
#पूर्ण_अगर

	r = FNAME(walk_addr_nested)(&walker, vcpu, vaddr, access);

	अगर (r) अणु
		gpa = gfn_to_gpa(walker.gfn);
		gpa |= vaddr & ~PAGE_MASK;
	पूर्ण अन्यथा अगर (exception)
		*exception = walker.fault;

	वापस gpa;
पूर्ण
#पूर्ण_अगर

/*
 * Using the cached inक्रमmation from sp->gfns is safe because:
 * - The spte has a reference to the काष्ठा page, so the pfn क्रम a given gfn
 *   can't change unless all sptes poपूर्णांकing to it are nuked first.
 *
 * Note:
 *   We should flush all tlbs अगर spte is dropped even though guest is
 *   responsible क्रम it. Since अगर we करोn't, kvm_mmu_notअगरier_invalidate_page
 *   and kvm_mmu_notअगरier_invalidate_range_start detect the mapping page isn't
 *   used by guest then tlbs are not flushed, so guest is allowed to access the
 *   मुक्तd pages.
 *   And we increase kvm->tlbs_dirty to delay tlbs flush in this हाल.
 */
अटल पूर्णांक FNAME(sync_page)(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu_page *sp)
अणु
	पूर्णांक i, nr_present = 0;
	bool host_writable;
	gpa_t first_pte_gpa;
	पूर्णांक set_spte_ret = 0;

	/* direct kvm_mmu_page can not be unsync. */
	BUG_ON(sp->role.direct);

	first_pte_gpa = FNAME(get_level1_sp_gpa)(sp);

	क्रम (i = 0; i < PT64_ENT_PER_PAGE; i++) अणु
		अचिन्हित pte_access;
		pt_element_t gpte;
		gpa_t pte_gpa;
		gfn_t gfn;

		अगर (!sp->spt[i])
			जारी;

		pte_gpa = first_pte_gpa + i * माप(pt_element_t);

		अगर (kvm_vcpu_पढ़ो_guest_atomic(vcpu, pte_gpa, &gpte,
					       माप(pt_element_t)))
			वापस 0;

		अगर (FNAME(prefetch_invalid_gpte)(vcpu, sp, &sp->spt[i], gpte)) अणु
			/*
			 * Update spte beक्रमe increasing tlbs_dirty to make
			 * sure no tlb flush is lost after spte is zapped; see
			 * the comments in kvm_flush_remote_tlbs().
			 */
			smp_wmb();
			vcpu->kvm->tlbs_dirty++;
			जारी;
		पूर्ण

		gfn = gpte_to_gfn(gpte);
		pte_access = sp->role.access;
		pte_access &= FNAME(gpte_access)(gpte);
		FNAME(protect_clean_gpte)(vcpu->arch.mmu, &pte_access, gpte);

		अगर (sync_mmio_spte(vcpu, &sp->spt[i], gfn, pte_access,
		      &nr_present))
			जारी;

		अगर (gfn != sp->gfns[i]) अणु
			drop_spte(vcpu->kvm, &sp->spt[i]);
			/*
			 * The same as above where we are करोing
			 * prefetch_invalid_gpte().
			 */
			smp_wmb();
			vcpu->kvm->tlbs_dirty++;
			जारी;
		पूर्ण

		nr_present++;

		host_writable = sp->spt[i] & shaकरोw_host_writable_mask;

		set_spte_ret |= set_spte(vcpu, &sp->spt[i],
					 pte_access, PG_LEVEL_4K,
					 gfn, spte_to_pfn(sp->spt[i]),
					 true, false, host_writable);
	पूर्ण

	अगर (set_spte_ret & SET_SPTE_NEED_REMOTE_TLB_FLUSH)
		kvm_flush_remote_tlbs(vcpu->kvm);

	वापस nr_present;
पूर्ण

#अघोषित pt_element_t
#अघोषित guest_walker
#अघोषित FNAME
#अघोषित PT_BASE_ADDR_MASK
#अघोषित PT_INDEX
#अघोषित PT_LVL_ADDR_MASK
#अघोषित PT_LVL_OFFSET_MASK
#अघोषित PT_LEVEL_BITS
#अघोषित PT_MAX_FULL_LEVELS
#अघोषित gpte_to_gfn
#अघोषित gpte_to_gfn_lvl
#अघोषित CMPXCHG
#अघोषित PT_GUEST_ACCESSED_MASK
#अघोषित PT_GUEST_सूचीTY_MASK
#अघोषित PT_GUEST_सूचीTY_SHIFT
#अघोषित PT_GUEST_ACCESSED_SHIFT
#अघोषित PT_HAVE_ACCESSED_सूचीTY
