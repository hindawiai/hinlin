<शैली गुरु>
/*
 * Copyright IBM Corporation, 2015
 * Author Aneesh Kumar K.V <aneesh.kumar@linux.ibm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#समावेश <linux/mm.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mmu.h>

पूर्णांक __hash_page_4K(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access, अचिन्हित दीर्घ vsid,
		   pte_t *ptep, अचिन्हित दीर्घ trap, अचिन्हित दीर्घ flags,
		   पूर्णांक ssize, पूर्णांक subpg_prot)
अणु
	real_pte_t rpte;
	अचिन्हित दीर्घ hpte_group;
	अचिन्हित दीर्घ rflags, pa;
	अचिन्हित दीर्घ old_pte, new_pte;
	अचिन्हित दीर्घ vpn, hash, slot;
	अचिन्हित दीर्घ shअगरt = mmu_psize_defs[MMU_PAGE_4K].shअगरt;

	/*
	 * atomically mark the linux large page PTE busy and dirty
	 */
	करो अणु
		pte_t pte = READ_ONCE(*ptep);

		old_pte = pte_val(pte);
		/* If PTE busy, retry the access */
		अगर (unlikely(old_pte & H_PAGE_BUSY))
			वापस 0;
		/* If PTE permissions करोn't match, take page fault */
		अगर (unlikely(!check_pte_access(access, old_pte)))
			वापस 1;
		/*
		 * Try to lock the PTE, add ACCESSED and सूचीTY अगर it was
		 * a ग_लिखो access. Since this is 4K insert of 64K page size
		 * also add H_PAGE_COMBO
		 */
		new_pte = old_pte | H_PAGE_BUSY | _PAGE_ACCESSED;
		अगर (access & _PAGE_WRITE)
			new_pte |= _PAGE_सूचीTY;
	पूर्ण जबतक (!pte_xchg(ptep, __pte(old_pte), __pte(new_pte)));

	/*
	 * PP bits. _PAGE_USER is alपढ़ोy PP bit 0x2, so we only
	 * need to add in 0x1 अगर it's a पढ़ो-only user page
	 */
	rflags = htab_convert_pte_flags(new_pte, flags);
	rpte = __real_pte(__pte(old_pte), ptep, PTRS_PER_PTE);

	अगर (cpu_has_feature(CPU_FTR_NOEXECUTE) &&
	    !cpu_has_feature(CPU_FTR_COHERENT_ICACHE))
		rflags = hash_page_करो_lazy_icache(rflags, __pte(old_pte), trap);

	vpn  = hpt_vpn(ea, vsid, ssize);
	अगर (unlikely(old_pte & H_PAGE_HASHPTE)) अणु
		/*
		 * There MIGHT be an HPTE क्रम this pte
		 */
		अचिन्हित दीर्घ gslot = pte_get_hash_gslot(vpn, shअगरt, ssize,
							 rpte, 0);

		अगर (mmu_hash_ops.hpte_updatepp(gslot, rflags, vpn, MMU_PAGE_4K,
					       MMU_PAGE_4K, ssize, flags) == -1)
			old_pte &= ~_PAGE_HPTEFLAGS;
	पूर्ण

	अगर (likely(!(old_pte & H_PAGE_HASHPTE))) अणु

		pa = pte_pfn(__pte(old_pte)) << PAGE_SHIFT;
		hash = hpt_hash(vpn, shअगरt, ssize);

repeat:
		hpte_group = (hash & htab_hash_mask) * HPTES_PER_GROUP;

		/* Insert पूर्णांकo the hash table, primary slot */
		slot = mmu_hash_ops.hpte_insert(hpte_group, vpn, pa, rflags, 0,
						MMU_PAGE_4K, MMU_PAGE_4K, ssize);
		/*
		 * Primary is full, try the secondary
		 */
		अगर (unlikely(slot == -1)) अणु
			hpte_group = (~hash & htab_hash_mask) * HPTES_PER_GROUP;
			slot = mmu_hash_ops.hpte_insert(hpte_group, vpn, pa,
							rflags,
							HPTE_V_SECONDARY,
							MMU_PAGE_4K,
							MMU_PAGE_4K, ssize);
			अगर (slot == -1) अणु
				अगर (mftb() & 0x1)
					hpte_group = (hash & htab_hash_mask) *
							HPTES_PER_GROUP;
				mmu_hash_ops.hpte_हटाओ(hpte_group);
				/*
				 * FIXME!! Should be try the group from which we हटाओd ?
				 */
				जाओ repeat;
			पूर्ण
		पूर्ण
		/*
		 * Hypervisor failure. Restore old pte and वापस -1
		 * similar to __hash_page_*
		 */
		अगर (unlikely(slot == -2)) अणु
			*ptep = __pte(old_pte);
			hash_failure_debug(ea, access, vsid, trap, ssize,
					   MMU_PAGE_4K, MMU_PAGE_4K, old_pte);
			वापस -1;
		पूर्ण
		new_pte = (new_pte & ~_PAGE_HPTEFLAGS) | H_PAGE_HASHPTE;
		new_pte |= pte_set_hidx(ptep, rpte, 0, slot, PTRS_PER_PTE);
	पूर्ण
	*ptep = __pte(new_pte & ~H_PAGE_BUSY);
	वापस 0;
पूर्ण
