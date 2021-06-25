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

/*
 * Return true, अगर the entry has a slot value which
 * the software considers as invalid.
 */
अटल अंतरभूत bool hpte_soft_invalid(अचिन्हित दीर्घ hidx)
अणु
	वापस ((hidx & 0xfUL) == 0xfUL);
पूर्ण

/*
 * index from 0 - 15
 */
bool __rpte_sub_valid(real_pte_t rpte, अचिन्हित दीर्घ index)
अणु
	वापस !(hpte_soft_invalid(__rpte_to_hidx(rpte, index)));
पूर्ण

पूर्णांक __hash_page_4K(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access, अचिन्हित दीर्घ vsid,
		   pte_t *ptep, अचिन्हित दीर्घ trap, अचिन्हित दीर्घ flags,
		   पूर्णांक ssize, पूर्णांक subpg_prot)
अणु
	real_pte_t rpte;
	अचिन्हित दीर्घ hpte_group;
	अचिन्हित पूर्णांक subpg_index;
	अचिन्हित दीर्घ rflags, pa;
	अचिन्हित दीर्घ old_pte, new_pte, subpg_pte;
	अचिन्हित दीर्घ vpn, hash, slot, gslot;
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
		new_pte = old_pte | H_PAGE_BUSY | _PAGE_ACCESSED | H_PAGE_COMBO;
		अगर (access & _PAGE_WRITE)
			new_pte |= _PAGE_सूचीTY;
	पूर्ण जबतक (!pte_xchg(ptep, __pte(old_pte), __pte(new_pte)));

	/*
	 * Handle the subpage protection bits
	 */
	subpg_pte = new_pte & ~subpg_prot;
	rflags = htab_convert_pte_flags(subpg_pte, flags);

	अगर (cpu_has_feature(CPU_FTR_NOEXECUTE) &&
	    !cpu_has_feature(CPU_FTR_COHERENT_ICACHE)) अणु

		/*
		 * No CPU has hugepages but lacks no execute, so we
		 * करोn't need to worry about that हाल
		 */
		rflags = hash_page_करो_lazy_icache(rflags, __pte(old_pte), trap);
	पूर्ण

	subpg_index = (ea & (PAGE_SIZE - 1)) >> shअगरt;
	vpn  = hpt_vpn(ea, vsid, ssize);
	rpte = __real_pte(__pte(old_pte), ptep, PTRS_PER_PTE);
	/*
	 *None of the sub 4k page is hashed
	 */
	अगर (!(old_pte & H_PAGE_HASHPTE))
		जाओ htab_insert_hpte;
	/*
	 * Check अगर the pte was alपढ़ोy inserted पूर्णांकo the hash table
	 * as a 64k HW page, and invalidate the 64k HPTE अगर so.
	 */
	अगर (!(old_pte & H_PAGE_COMBO)) अणु
		flush_hash_page(vpn, rpte, MMU_PAGE_64K, ssize, flags);
		/*
		 * clear the old slot details from the old and new pte.
		 * On hash insert failure we use old pte value and we करोn't
		 * want slot inक्रमmation there अगर we have a insert failure.
		 */
		old_pte &= ~H_PAGE_HASHPTE;
		new_pte &= ~H_PAGE_HASHPTE;
		जाओ htab_insert_hpte;
	पूर्ण
	/*
	 * Check क्रम sub page valid and update
	 */
	अगर (__rpte_sub_valid(rpte, subpg_index)) अणु
		पूर्णांक ret;

		gslot = pte_get_hash_gslot(vpn, shअगरt, ssize, rpte,
					   subpg_index);
		ret = mmu_hash_ops.hpte_updatepp(gslot, rflags, vpn,
						 MMU_PAGE_4K, MMU_PAGE_4K,
						 ssize, flags);

		/*
		 * If we failed because typically the HPTE wasn't really here
		 * we try an insertion.
		 */
		अगर (ret == -1)
			जाओ htab_insert_hpte;

		*ptep = __pte(new_pte & ~H_PAGE_BUSY);
		वापस 0;
	पूर्ण

htab_insert_hpte:

	/*
	 * Initialize all hidx entries to invalid value, the first समय
	 * the PTE is about to allocate a 4K HPTE.
	 */
	अगर (!(old_pte & H_PAGE_COMBO))
		rpte.hidx = INVALID_RPTE_HIDX;

	/*
	 * handle H_PAGE_4K_PFN हाल
	 */
	अगर (old_pte & H_PAGE_4K_PFN) अणु
		/*
		 * All the sub 4k page have the same
		 * physical address.
		 */
		pa = pte_pfn(__pte(old_pte)) << HW_PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		pa = pte_pfn(__pte(old_pte)) << PAGE_SHIFT;
		pa += (subpg_index << shअगरt);
	पूर्ण
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
		bool soft_invalid;

		hpte_group = (~hash & htab_hash_mask) * HPTES_PER_GROUP;
		slot = mmu_hash_ops.hpte_insert(hpte_group, vpn, pa,
						rflags, HPTE_V_SECONDARY,
						MMU_PAGE_4K, MMU_PAGE_4K,
						ssize);

		soft_invalid = hpte_soft_invalid(slot);
		अगर (unlikely(soft_invalid)) अणु
			/*
			 * We got a valid slot from a hardware poपूर्णांक of view.
			 * but we cannot use it, because we use this special
			 * value; as defined by hpte_soft_invalid(), to track
			 * invalid slots. We cannot use it. So invalidate it.
			 */
			gslot = slot & _PTEIDX_GROUP_IX;
			mmu_hash_ops.hpte_invalidate(hpte_group + gslot, vpn,
						     MMU_PAGE_4K, MMU_PAGE_4K,
						     ssize, 0);
		पूर्ण

		अगर (unlikely(slot == -1 || soft_invalid)) अणु
			/*
			 * For soft invalid slot, let's ensure that we release a
			 * slot from the primary, with the hope that we will
			 * acquire that slot next समय we try. This will ensure
			 * that we करो not get the same soft-invalid slot.
			 */
			अगर (soft_invalid || (mftb() & 0x1))
				hpte_group = (hash & htab_hash_mask) * HPTES_PER_GROUP;

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

	new_pte |= pte_set_hidx(ptep, rpte, subpg_index, slot, PTRS_PER_PTE);
	new_pte |= H_PAGE_HASHPTE;

	*ptep = __pte(new_pte & ~H_PAGE_BUSY);
	वापस 0;
पूर्ण

पूर्णांक __hash_page_64K(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access,
		    अचिन्हित दीर्घ vsid, pte_t *ptep, अचिन्हित दीर्घ trap,
		    अचिन्हित दीर्घ flags, पूर्णांक ssize)
अणु
	real_pte_t rpte;
	अचिन्हित दीर्घ hpte_group;
	अचिन्हित दीर्घ rflags, pa;
	अचिन्हित दीर्घ old_pte, new_pte;
	अचिन्हित दीर्घ vpn, hash, slot;
	अचिन्हित दीर्घ shअगरt = mmu_psize_defs[MMU_PAGE_64K].shअगरt;

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
		 * Check अगर PTE has the cache-inhibit bit set
		 * If so, bail out and refault as a 4k page
		 */
		अगर (!mmu_has_feature(MMU_FTR_CI_LARGE_PAGE) &&
		    unlikely(pte_ci(pte)))
			वापस 0;
		/*
		 * Try to lock the PTE, add ACCESSED and सूचीTY अगर it was
		 * a ग_लिखो access.
		 */
		new_pte = old_pte | H_PAGE_BUSY | _PAGE_ACCESSED;
		अगर (access & _PAGE_WRITE)
			new_pte |= _PAGE_सूचीTY;
	पूर्ण जबतक (!pte_xchg(ptep, __pte(old_pte), __pte(new_pte)));

	rflags = htab_convert_pte_flags(new_pte, flags);
	rpte = __real_pte(__pte(old_pte), ptep, PTRS_PER_PTE);

	अगर (cpu_has_feature(CPU_FTR_NOEXECUTE) &&
	    !cpu_has_feature(CPU_FTR_COHERENT_ICACHE))
		rflags = hash_page_करो_lazy_icache(rflags, __pte(old_pte), trap);

	vpn  = hpt_vpn(ea, vsid, ssize);
	अगर (unlikely(old_pte & H_PAGE_HASHPTE)) अणु
		अचिन्हित दीर्घ gslot;

		/*
		 * There MIGHT be an HPTE क्रम this pte
		 */
		gslot = pte_get_hash_gslot(vpn, shअगरt, ssize, rpte, 0);
		अगर (mmu_hash_ops.hpte_updatepp(gslot, rflags, vpn, MMU_PAGE_64K,
					       MMU_PAGE_64K, ssize,
					       flags) == -1)
			old_pte &= ~_PAGE_HPTEFLAGS;
	पूर्ण

	अगर (likely(!(old_pte & H_PAGE_HASHPTE))) अणु

		pa = pte_pfn(__pte(old_pte)) << PAGE_SHIFT;
		hash = hpt_hash(vpn, shअगरt, ssize);

repeat:
		hpte_group = (hash & htab_hash_mask) * HPTES_PER_GROUP;

		/* Insert पूर्णांकo the hash table, primary slot */
		slot = mmu_hash_ops.hpte_insert(hpte_group, vpn, pa, rflags, 0,
						MMU_PAGE_64K, MMU_PAGE_64K,
						ssize);
		/*
		 * Primary is full, try the secondary
		 */
		अगर (unlikely(slot == -1)) अणु
			hpte_group = (~hash & htab_hash_mask) * HPTES_PER_GROUP;
			slot = mmu_hash_ops.hpte_insert(hpte_group, vpn, pa,
							rflags,
							HPTE_V_SECONDARY,
							MMU_PAGE_64K,
							MMU_PAGE_64K, ssize);
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
					   MMU_PAGE_64K, MMU_PAGE_64K, old_pte);
			वापस -1;
		पूर्ण

		new_pte = (new_pte & ~_PAGE_HPTEFLAGS) | H_PAGE_HASHPTE;
		new_pte |= pte_set_hidx(ptep, rpte, 0, slot, PTRS_PER_PTE);
	पूर्ण
	*ptep = __pte(new_pte & ~H_PAGE_BUSY);
	वापस 0;
पूर्ण
