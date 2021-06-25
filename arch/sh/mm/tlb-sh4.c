<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/sh/mm/tlb-sh4.c
 *
 * SH-4 specअगरic TLB operations
 *
 * Copyright (C) 1999  Niibe Yutaka
 * Copyright (C) 2002 - 2007 Paul Mundt
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
	vpn = (address & MMU_VPN_MASK) | get_asid();
	__raw_ग_लिखोl(vpn, MMU_PTEH);

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
#अन्यथा
	अगर (cpu_data->flags & CPU_HAS_PTEA) अणु
		/* The last 3 bits and the first one of pteval contains
		 * the PTEA timing control and space attribute bits
		 */
		__raw_ग_लिखोl(copy_ptea_attributes(pteval), MMU_PTEA);
	पूर्ण
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

व्योम local_flush_tlb_one(अचिन्हित दीर्घ asid, अचिन्हित दीर्घ page)
अणु
	अचिन्हित दीर्घ addr, data;

	/*
	 * NOTE: PTEH.ASID should be set to this MM
	 *       _AND_ we need to ग_लिखो ASID to the array.
	 *
	 * It would be simple अगर we didn't need to set PTEH.ASID...
	 */
	addr = MMU_UTLB_ADDRESS_ARRAY | MMU_PAGE_ASSOC_BIT;
	data = page | asid; /* VALID bit is off */
	jump_to_uncached();
	__raw_ग_लिखोl(data, addr);
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
