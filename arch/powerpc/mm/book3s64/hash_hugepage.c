<शैली गुरु>
/*
 * Copyright IBM Corporation, 2013
 * Author Aneesh Kumar K.V <aneesh.kumar@linux.ibm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * PPC64 THP Support क्रम hash based MMUs
 */
#समावेश <linux/mm.h>
#समावेश <यंत्र/machdep.h>

पूर्णांक __hash_page_thp(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access, अचिन्हित दीर्घ vsid,
		    pmd_t *pmdp, अचिन्हित दीर्घ trap, अचिन्हित दीर्घ flags,
		    पूर्णांक ssize, अचिन्हित पूर्णांक psize)
अणु
	अचिन्हित पूर्णांक index, valid;
	अचिन्हित अक्षर *hpte_slot_array;
	अचिन्हित दीर्घ rflags, pa, hidx;
	अचिन्हित दीर्घ old_pmd, new_pmd;
	पूर्णांक ret, lpsize = MMU_PAGE_16M;
	अचिन्हित दीर्घ vpn, hash, shअगरt, slot;

	/*
	 * atomically mark the linux large page PMD busy and dirty
	 */
	करो अणु
		pmd_t pmd = READ_ONCE(*pmdp);

		old_pmd = pmd_val(pmd);
		/* If PMD busy, retry the access */
		अगर (unlikely(old_pmd & H_PAGE_BUSY))
			वापस 0;
		/* If PMD permissions करोn't match, take page fault */
		अगर (unlikely(!check_pte_access(access, old_pmd)))
			वापस 1;
		/*
		 * Try to lock the PTE, add ACCESSED and सूचीTY अगर it was
		 * a ग_लिखो access
		 */
		new_pmd = old_pmd | H_PAGE_BUSY | _PAGE_ACCESSED;
		अगर (access & _PAGE_WRITE)
			new_pmd |= _PAGE_सूचीTY;
	पूर्ण जबतक (!pmd_xchg(pmdp, __pmd(old_pmd), __pmd(new_pmd)));

	/*
	 * Make sure this is thp or devmap entry
	 */
	अगर (!(old_pmd & (H_PAGE_THP_HUGE | _PAGE_DEVMAP)))
		वापस 0;

	rflags = htab_convert_pte_flags(new_pmd, flags);

#अगर 0
	अगर (!cpu_has_feature(CPU_FTR_COHERENT_ICACHE)) अणु

		/*
		 * No CPU has hugepages but lacks no execute, so we
		 * करोn't need to worry about that हाल
		 */
		rflags = hash_page_करो_lazy_icache(rflags, __pte(old_pte), trap);
	पूर्ण
#पूर्ण_अगर
	/*
	 * Find the slot index details क्रम this ea, using base page size.
	 */
	shअगरt = mmu_psize_defs[psize].shअगरt;
	index = (ea & ~HPAGE_PMD_MASK) >> shअगरt;
	BUG_ON(index >= PTE_FRAG_SIZE);

	vpn = hpt_vpn(ea, vsid, ssize);
	hpte_slot_array = get_hpte_slot_array(pmdp);
	अगर (psize == MMU_PAGE_4K) अणु
		/*
		 * invalidate the old hpte entry अगर we have that mapped via 64K
		 * base page size. This is because demote_segment won't flush
		 * hash page table entries.
		 */
		अगर ((old_pmd & H_PAGE_HASHPTE) && !(old_pmd & H_PAGE_COMBO)) अणु
			flush_hash_hugepage(vsid, ea, pmdp, MMU_PAGE_64K,
					    ssize, flags);
			/*
			 * With THP, we also clear the slot inक्रमmation with
			 * respect to all the 64K hash pte mapping the 16MB
			 * page. They are all invalid now. This make sure we
			 * करोn't find the slot valid when we fault with 4k
			 * base page size.
			 *
			 */
			स_रखो(hpte_slot_array, 0, PTE_FRAG_SIZE);
		पूर्ण
	पूर्ण

	valid = hpte_valid(hpte_slot_array, index);
	अगर (valid) अणु
		/* update the hpte bits */
		hash = hpt_hash(vpn, shअगरt, ssize);
		hidx =  hpte_hash_index(hpte_slot_array, index);
		अगर (hidx & _PTEIDX_SECONDARY)
			hash = ~hash;
		slot = (hash & htab_hash_mask) * HPTES_PER_GROUP;
		slot += hidx & _PTEIDX_GROUP_IX;

		ret = mmu_hash_ops.hpte_updatepp(slot, rflags, vpn,
						 psize, lpsize, ssize, flags);
		/*
		 * We failed to update, try to insert a new entry.
		 */
		अगर (ret == -1) अणु
			/*
			 * large pte is marked busy, so we can be sure
			 * nobody is looking at hpte_slot_array. hence we can
			 * safely update this here.
			 */
			valid = 0;
			hpte_slot_array[index] = 0;
		पूर्ण
	पूर्ण

	अगर (!valid) अणु
		अचिन्हित दीर्घ hpte_group;

		hash = hpt_hash(vpn, shअगरt, ssize);
		/* insert new entry */
		pa = pmd_pfn(__pmd(old_pmd)) << PAGE_SHIFT;
		new_pmd |= H_PAGE_HASHPTE;

repeat:
		hpte_group = (hash & htab_hash_mask) * HPTES_PER_GROUP;

		/* Insert पूर्णांकo the hash table, primary slot */
		slot = mmu_hash_ops.hpte_insert(hpte_group, vpn, pa, rflags, 0,
						psize, lpsize, ssize);
		/*
		 * Primary is full, try the secondary
		 */
		अगर (unlikely(slot == -1)) अणु
			hpte_group = (~hash & htab_hash_mask) * HPTES_PER_GROUP;
			slot = mmu_hash_ops.hpte_insert(hpte_group, vpn, pa,
							rflags,
							HPTE_V_SECONDARY,
							psize, lpsize, ssize);
			अगर (slot == -1) अणु
				अगर (mftb() & 0x1)
					hpte_group = (hash & htab_hash_mask) *
							HPTES_PER_GROUP;

				mmu_hash_ops.hpte_हटाओ(hpte_group);
				जाओ repeat;
			पूर्ण
		पूर्ण
		/*
		 * Hypervisor failure. Restore old pmd and वापस -1
		 * similar to __hash_page_*
		 */
		अगर (unlikely(slot == -2)) अणु
			*pmdp = __pmd(old_pmd);
			hash_failure_debug(ea, access, vsid, trap, ssize,
					   psize, lpsize, old_pmd);
			वापस -1;
		पूर्ण
		/*
		 * large pte is marked busy, so we can be sure
		 * nobody is looking at hpte_slot_array. hence we can
		 * safely update this here.
		 */
		mark_hpte_slot_valid(hpte_slot_array, index, slot);
	पूर्ण
	/*
	 * Mark the pte with H_PAGE_COMBO, अगर we are trying to hash it with
	 * base page size 4k.
	 */
	अगर (psize == MMU_PAGE_4K)
		new_pmd |= H_PAGE_COMBO;
	/*
	 * The hpte valid is stored in the pgtable whose address is in the
	 * second half of the PMD. Order this against clearing of the busy bit in
	 * huge pmd.
	 */
	smp_wmb();
	*pmdp = __pmd(new_pmd & ~H_PAGE_BUSY);
	वापस 0;
पूर्ण
