<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/sh/mm/tlb-sh3.c
 *
 * SH-3 specअगरic TLB operations
 *
 * Copyright (C) 1999  Niibe Yutaka
 * Copyright (C) 2002  Paul Mundt
 */
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
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

	pteval = pte_val(pte);

	/* Set PTEL रेजिस्टर */
	pteval &= _PAGE_FLAGS_HARDWARE_MASK; /* drop software flags */
	/* conveniently, we want all the software flags to be 0 anyway */
	__raw_ग_लिखोl(pteval, MMU_PTEL);

	/* Load the TLB */
	यंत्र अस्थिर("ldtlb": /* no output */ : /* no input */ : "memory");
	local_irq_restore(flags);
पूर्ण

व्योम local_flush_tlb_one(अचिन्हित दीर्घ asid, अचिन्हित दीर्घ page)
अणु
	अचिन्हित दीर्घ addr, data;
	पूर्णांक i, ways = MMU_NTLB_WAYS;

	/*
	 * NOTE: PTEH.ASID should be set to this MM
	 *       _AND_ we need to ग_लिखो ASID to the array.
	 *
	 * It would be simple अगर we didn't need to set PTEH.ASID...
	 */
	addr = MMU_TLB_ADDRESS_ARRAY | (page & 0x1F000);
	data = (page & 0xfffe0000) | asid; /* VALID bit is off */

	अगर ((current_cpu_data.flags & CPU_HAS_MMU_PAGE_ASSOC)) अणु
		addr |= MMU_PAGE_ASSOC_BIT;
		ways = 1;	/* we alपढ़ोy know the way .. */
	पूर्ण

	क्रम (i = 0; i < ways; i++)
		__raw_ग_लिखोl(data, addr + (i << 8));
पूर्ण

व्योम local_flush_tlb_all(व्योम)
अणु
	अचिन्हित दीर्घ flags, status;

	/*
	 * Flush all the TLB.
	 *
	 * Write to the MMU control रेजिस्टर's bit:
	 *	TF-bit क्रम SH-3, TI-bit क्रम SH-4.
	 *      It's same position, bit #2.
	 */
	local_irq_save(flags);
	status = __raw_पढ़ोl(MMUCR);
	status |= 0x04;
	__raw_ग_लिखोl(status, MMUCR);
	ctrl_barrier();
	local_irq_restore(flags);
पूर्ण
