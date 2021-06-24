<शैली गुरु>
/*
 * arch/sh/mm/tlb-pteaex.c
 *
 * TLB operations क्रम SH-X3 CPUs featuring PTE ASID Extensions.
 *
 * Copyright (C) 2009 Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cacheflush.h>

व्योम __update_tlb(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, pte_t pte)
अणु
	अचिन्हित दीर्घ flags, pteval, vpn;

	/*
	 * Handle debugger faulting in क्रम debugee.
	 */
	अगर (vma && current->active_mm != vma->vm_mm)
		वापस;

	local_irq_save(flags);

	/* Set PTEH रेजिस्टर */
	vpn = address & MMU_VPN_MASK;
	__raw_ग_लिखोl(vpn, MMU_PTEH);

	/* Set PTEAEX */
	__raw_ग_लिखोl(get_asid(), MMU_PTEAEX);

	pteval = pte.pte_low;

	/* Set PTEA रेजिस्टर */
#अगर_घोषित CONFIG_X2TLB
	/*
	 * For the extended mode TLB this is trivial, only the ESZ and
	 * EPR bits need to be written out to PTEA, with the reमुख्यder of
	 * the protection bits (with the exception of the compat-mode SZ
	 * and PR bits, which are cleared) being written out in PTEL.
	 */
	__raw_ग_लिखोl(pte.pte_high, MMU_PTEA);
#पूर्ण_अगर

	/* Set PTEL रेजिस्टर */
	pteval &= _PAGE_FLAGS_HARDWARE_MASK; /* drop software flags */
#अगर_घोषित CONFIG_CACHE_WRITETHROUGH
	pteval |= _PAGE_WT;
#पूर्ण_अगर
	/* conveniently, we want all the software flags to be 0 anyway */
	__raw_ग_लिखोl(pteval, MMU_PTEL);

	/* Load the TLB */
	यंत्र अस्थिर("ldtlb": /* no output */ : /* no input */ : "memory");
	local_irq_restore(flags);
पूर्ण

/*
 * While SH-X2 extended TLB mode splits out the memory-mapped I/UTLB
 * data arrays, SH-X3 cores with PTEAEX split out the memory-mapped
 * address arrays. In compat mode the second array is inaccessible, जबतक
 * in extended mode, the legacy 8-bit ASID field in address array 1 has
 * undefined behaviour.
 */
व्योम local_flush_tlb_one(अचिन्हित दीर्घ asid, अचिन्हित दीर्घ page)
अणु
	jump_to_uncached();
	__raw_ग_लिखोl(page, MMU_UTLB_ADDRESS_ARRAY | MMU_PAGE_ASSOC_BIT);
	__raw_ग_लिखोl(asid, MMU_UTLB_ADDRESS_ARRAY2 | MMU_PAGE_ASSOC_BIT);
	__raw_ग_लिखोl(page, MMU_ITLB_ADDRESS_ARRAY | MMU_PAGE_ASSOC_BIT);
	__raw_ग_लिखोl(asid, MMU_ITLB_ADDRESS_ARRAY2 | MMU_PAGE_ASSOC_BIT);
	back_to_cached();
पूर्ण

व्योम local_flush_tlb_all(व्योम)
अणु
	अचिन्हित दीर्घ flags, status;
	पूर्णांक i;

	/*
	 * Flush all the TLB.
	 */
	local_irq_save(flags);
	jump_to_uncached();

	status = __raw_पढ़ोl(MMUCR);
	status = ((status & MMUCR_URB) >> MMUCR_URB_SHIFT);

	अगर (status == 0)
		status = MMUCR_URB_NENTRIES;

	क्रम (i = 0; i < status; i++)
		__raw_ग_लिखोl(0x0, MMU_UTLB_ADDRESS_ARRAY | (i << 8));

	क्रम (i = 0; i < 4; i++)
		__raw_ग_लिखोl(0x0, MMU_ITLB_ADDRESS_ARRAY | (i << 8));

	back_to_cached();
	ctrl_barrier();
	local_irq_restore(flags);
पूर्ण
