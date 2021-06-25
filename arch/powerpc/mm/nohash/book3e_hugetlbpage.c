<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PPC Huge TLB Page Support क्रम Book3E MMU
 *
 * Copyright (C) 2009 David Gibson, IBM Corporation.
 * Copyright (C) 2011 Becky Bruce, Freescale Semiconductor
 *
 */
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>

#समावेश <यंत्र/mmu.h>

#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/paca.h>

अटल अंतरभूत पूर्णांक tlb1_next(व्योम)
अणु
	काष्ठा paca_काष्ठा *paca = get_paca();
	काष्ठा tlb_core_data *tcd;
	पूर्णांक this, next;

	tcd = paca->tcd_ptr;
	this = tcd->esel_next;

	next = this + 1;
	अगर (next >= tcd->esel_max)
		next = tcd->esel_first;

	tcd->esel_next = next;
	वापस this;
पूर्ण

अटल अंतरभूत व्योम book3e_tlb_lock(व्योम)
अणु
	काष्ठा paca_काष्ठा *paca = get_paca();
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक token = smp_processor_id() + 1;

	/*
	 * Besides being unnecessary in the असलence of SMT, this
	 * check prevents trying to करो lbarx/stbcx. on e5500 which
	 * करोesn't implement either feature.
	 */
	अगर (!cpu_has_feature(CPU_FTR_SMT))
		वापस;

	यंत्र अस्थिर("1: lbarx %0, 0, %1;"
		     "cmpwi %0, 0;"
		     "bne 2f;"
		     "stbcx. %2, 0, %1;"
		     "bne 1b;"
		     "b 3f;"
		     "2: lbzx %0, 0, %1;"
		     "cmpwi %0, 0;"
		     "bne 2b;"
		     "b 1b;"
		     "3:"
		     : "=&r" (पंचांगp)
		     : "r" (&paca->tcd_ptr->lock), "r" (token)
		     : "memory");
पूर्ण

अटल अंतरभूत व्योम book3e_tlb_unlock(व्योम)
अणु
	काष्ठा paca_काष्ठा *paca = get_paca();

	अगर (!cpu_has_feature(CPU_FTR_SMT))
		वापस;

	isync();
	paca->tcd_ptr->lock = 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक tlb1_next(व्योम)
अणु
	पूर्णांक index, ncams;

	ncams = mfspr(SPRN_TLB1CFG) & TLBnCFG_N_ENTRY;

	index = this_cpu_पढ़ो(next_tlbcam_idx);

	/* Just round-robin the entries and wrap when we hit the end */
	अगर (unlikely(index == ncams - 1))
		__this_cpu_ग_लिखो(next_tlbcam_idx, tlbcam_index);
	अन्यथा
		__this_cpu_inc(next_tlbcam_idx);

	वापस index;
पूर्ण

अटल अंतरभूत व्योम book3e_tlb_lock(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम book3e_tlb_unlock(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक book3e_tlb_exists(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ pid)
अणु
	पूर्णांक found = 0;

	mtspr(SPRN_MAS6, pid << 16);
	अगर (mmu_has_feature(MMU_FTR_USE_TLBRSRV)) अणु
		यंत्र अस्थिर(
			"li	%0,0\n"
			"tlbsx.	0,%1\n"
			"bne	1f\n"
			"li	%0,1\n"
			"1:\n"
			: "=&r"(found) : "r"(ea));
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर(
			"tlbsx	0,%1\n"
			"mfspr	%0,0x271\n"
			"srwi	%0,%0,31\n"
			: "=&r"(found) : "r"(ea));
	पूर्ण

	वापस found;
पूर्ण

अटल व्योम
book3e_hugetlb_preload(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ ea, pte_t pte)
अणु
	अचिन्हित दीर्घ mas1, mas2;
	u64 mas7_3;
	अचिन्हित दीर्घ psize, tsize, shअगरt;
	अचिन्हित दीर्घ flags;
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक index;

	अगर (unlikely(is_kernel_addr(ea)))
		वापस;

	mm = vma->vm_mm;

	psize = vma_mmu_pagesize(vma);
	shअगरt = __ilog2(psize);
	tsize = shअगरt - 10;
	/*
	 * We can't be interrupted while we're setting up the MAS
	 * regusters or after we've confirmed that no tlb exists.
	 */
	local_irq_save(flags);

	book3e_tlb_lock();

	अगर (unlikely(book3e_tlb_exists(ea, mm->context.id))) अणु
		book3e_tlb_unlock();
		local_irq_restore(flags);
		वापस;
	पूर्ण

	/* We have to use the CAM(TLB1) on FSL parts क्रम hugepages */
	index = tlb1_next();
	mtspr(SPRN_MAS0, MAS0_ESEL(index) | MAS0_TLBSEL(1));

	mas1 = MAS1_VALID | MAS1_TID(mm->context.id) | MAS1_TSIZE(tsize);
	mas2 = ea & ~((1UL << shअगरt) - 1);
	mas2 |= (pte_val(pte) >> PTE_WIMGE_SHIFT) & MAS2_WIMGE_MASK;
	mas7_3 = (u64)pte_pfn(pte) << PAGE_SHIFT;
	mas7_3 |= (pte_val(pte) >> PTE_BAP_SHIFT) & MAS3_BAP_MASK;
	अगर (!pte_dirty(pte))
		mas7_3 &= ~(MAS3_SW|MAS3_UW);

	mtspr(SPRN_MAS1, mas1);
	mtspr(SPRN_MAS2, mas2);

	अगर (mmu_has_feature(MMU_FTR_USE_PAIRED_MAS)) अणु
		mtspr(SPRN_MAS7_MAS3, mas7_3);
	पूर्ण अन्यथा अणु
		अगर (mmu_has_feature(MMU_FTR_BIG_PHYS))
			mtspr(SPRN_MAS7, upper_32_bits(mas7_3));
		mtspr(SPRN_MAS3, lower_32_bits(mas7_3));
	पूर्ण

	यंत्र अस्थिर ("tlbwe");

	book3e_tlb_unlock();
	local_irq_restore(flags);
पूर्ण

/*
 * This is called at the end of handling a user page fault, when the
 * fault has been handled by updating a PTE in the linux page tables.
 *
 * This must always be called with the pte lock held.
 */
व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	अगर (is_vm_hugetlb_page(vma))
		book3e_hugetlb_preload(vma, address, *ptep);
पूर्ण

व्योम flush_hugetlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr)
अणु
	काष्ठा hstate *hstate = hstate_file(vma->vm_file);
	अचिन्हित दीर्घ tsize = huge_page_shअगरt(hstate) - 10;

	__flush_tlb_page(vma->vm_mm, vmaddr, tsize, 0);
पूर्ण
