<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PPC64 Huge TLB Page Support क्रम hash based MMUs (POWER4 and later)
 *
 * Copyright (C) 2003 David Gibson, IBM Corporation.
 *
 * Based on the IA-32 version:
 * Copyright (C) 2002, Rohit Seth <rohit.seth@पूर्णांकel.com>
 */

#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/machdep.h>

अचिन्हित पूर्णांक hpage_shअगरt;
EXPORT_SYMBOL(hpage_shअगरt);

पूर्णांक __hash_page_huge(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access, अचिन्हित दीर्घ vsid,
		     pte_t *ptep, अचिन्हित दीर्घ trap, अचिन्हित दीर्घ flags,
		     पूर्णांक ssize, अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक mmu_psize)
अणु
	real_pte_t rpte;
	अचिन्हित दीर्घ vpn;
	अचिन्हित दीर्घ old_pte, new_pte;
	अचिन्हित दीर्घ rflags, pa;
	दीर्घ slot, offset;

	BUG_ON(shअगरt != mmu_psize_defs[mmu_psize].shअगरt);

	/* Search the Linux page table क्रम a match with va */
	vpn = hpt_vpn(ea, vsid, ssize);

	/*
	 * At this poपूर्णांक, we have a pte (old_pte) which can be used to build
	 * or update an HPTE. There are 2 हालs:
	 *
	 * 1. There is a valid (present) pte with no associated HPTE (this is
	 *	the most common हाल)
	 * 2. There is a valid (present) pte with an associated HPTE. The
	 *	current values of the pp bits in the HPTE prevent access
	 *	because we are करोing software सूचीTY bit management and the
	 *	page is currently not सूचीTY.
	 */


	करो अणु
		old_pte = pte_val(*ptep);
		/* If PTE busy, retry the access */
		अगर (unlikely(old_pte & H_PAGE_BUSY))
			वापस 0;
		/* If PTE permissions करोn't match, take page fault */
		अगर (unlikely(!check_pte_access(access, old_pte)))
			वापस 1;

		/*
		 * Try to lock the PTE, add ACCESSED and सूचीTY अगर it was
		 * a ग_लिखो access
		 */
		new_pte = old_pte | H_PAGE_BUSY | _PAGE_ACCESSED;
		अगर (access & _PAGE_WRITE)
			new_pte |= _PAGE_सूचीTY;
	पूर्ण जबतक(!pte_xchg(ptep, __pte(old_pte), __pte(new_pte)));

	/* Make sure this is a hugetlb entry */
	अगर (old_pte & (H_PAGE_THP_HUGE | _PAGE_DEVMAP))
		वापस 0;

	rflags = htab_convert_pte_flags(new_pte, flags);
	अगर (unlikely(mmu_psize == MMU_PAGE_16G))
		offset = PTRS_PER_PUD;
	अन्यथा
		offset = PTRS_PER_PMD;
	rpte = __real_pte(__pte(old_pte), ptep, offset);

	अगर (!cpu_has_feature(CPU_FTR_COHERENT_ICACHE))
		/*
		 * No CPU has hugepages but lacks no execute, so we
		 * करोn't need to worry about that हाल
		 */
		rflags = hash_page_करो_lazy_icache(rflags, __pte(old_pte), trap);

	/* Check अगर pte alपढ़ोy has an hpte (हाल 2) */
	अगर (unlikely(old_pte & H_PAGE_HASHPTE)) अणु
		/* There MIGHT be an HPTE क्रम this pte */
		अचिन्हित दीर्घ gslot;

		gslot = pte_get_hash_gslot(vpn, shअगरt, ssize, rpte, 0);
		अगर (mmu_hash_ops.hpte_updatepp(gslot, rflags, vpn, mmu_psize,
					       mmu_psize, ssize, flags) == -1)
			old_pte &= ~_PAGE_HPTEFLAGS;
	पूर्ण

	अगर (likely(!(old_pte & H_PAGE_HASHPTE))) अणु
		अचिन्हित दीर्घ hash = hpt_hash(vpn, shअगरt, ssize);

		pa = pte_pfn(__pte(old_pte)) << PAGE_SHIFT;

		/* clear HPTE slot inक्रमmations in new PTE */
		new_pte = (new_pte & ~_PAGE_HPTEFLAGS) | H_PAGE_HASHPTE;

		slot = hpte_insert_repeating(hash, vpn, pa, rflags, 0,
					     mmu_psize, ssize);

		/*
		 * Hypervisor failure. Restore old pte and वापस -1
		 * similar to __hash_page_*
		 */
		अगर (unlikely(slot == -2)) अणु
			*ptep = __pte(old_pte);
			hash_failure_debug(ea, access, vsid, trap, ssize,
					   mmu_psize, mmu_psize, old_pte);
			वापस -1;
		पूर्ण

		new_pte |= pte_set_hidx(ptep, rpte, 0, slot, offset);
	पूर्ण

	/*
	 * No need to use ldarx/stdcx here
	 */
	*ptep = __pte(new_pte & ~H_PAGE_BUSY);
	वापस 0;
पूर्ण

pte_t huge_ptep_modअगरy_prot_start(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	अचिन्हित दीर्घ pte_val;
	/*
	 * Clear the _PAGE_PRESENT so that no hardware parallel update is
	 * possible. Also keep the pte_present true so that we करोn't take
	 * wrong fault.
	 */
	pte_val = pte_update(vma->vm_mm, addr, ptep,
			     _PAGE_PRESENT, _PAGE_INVALID, 1);

	वापस __pte(pte_val);
पूर्ण

व्योम huge_ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
				  pte_t *ptep, pte_t old_pte, pte_t pte)
अणु

	अगर (radix_enabled())
		वापस radix__huge_ptep_modअगरy_prot_commit(vma, addr, ptep,
							   old_pte, pte);
	set_huge_pte_at(vma->vm_mm, addr, ptep, pte);
पूर्ण

व्योम hugetlbpage_init_शेष(व्योम)
अणु
	/* Set शेष large page size. Currently, we pick 16M or 1M
	 * depending on what is available
	 */
	अगर (mmu_psize_defs[MMU_PAGE_16M].shअगरt)
		hpage_shअगरt = mmu_psize_defs[MMU_PAGE_16M].shअगरt;
	अन्यथा अगर (mmu_psize_defs[MMU_PAGE_1M].shअगरt)
		hpage_shअगरt = mmu_psize_defs[MMU_PAGE_1M].shअगरt;
	अन्यथा अगर (mmu_psize_defs[MMU_PAGE_2M].shअगरt)
		hpage_shअगरt = mmu_psize_defs[MMU_PAGE_2M].shअगरt;
पूर्ण
