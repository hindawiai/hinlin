<शैली गुरु>
/*
 * arch/sh/mm/tlb-urb.c
 *
 * TLB entry wiring helpers क्रम URB-equipped parts.
 *
 * Copyright (C) 2010  Matt Fleming
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/mmu_context.h>

/*
 * Load the entry क्रम 'addr' पूर्णांकo the TLB and wire the entry.
 */
व्योम tlb_wire_entry(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr, pte_t pte)
अणु
	अचिन्हित दीर्घ status, flags;
	पूर्णांक urb;

	local_irq_save(flags);

	status = __raw_पढ़ोl(MMUCR);
	urb = (status & MMUCR_URB) >> MMUCR_URB_SHIFT;
	status &= ~MMUCR_URC;

	/*
	 * Make sure we're not trying to wire the last TLB entry slot.
	 */
	BUG_ON(!--urb);

	urb = urb % MMUCR_URB_NENTRIES;

	/*
	 * Insert this entry पूर्णांकo the highest non-wired TLB slot (via
	 * the URC field).
	 */
	status |= (urb << MMUCR_URC_SHIFT);
	__raw_ग_लिखोl(status, MMUCR);
	ctrl_barrier();

	/* Load the entry पूर्णांकo the TLB */
	__update_tlb(vma, addr, pte);

	/* ... and wire it up. */
	status = __raw_पढ़ोl(MMUCR);

	status &= ~MMUCR_URB;
	status |= (urb << MMUCR_URB_SHIFT);

	__raw_ग_लिखोl(status, MMUCR);
	ctrl_barrier();

	local_irq_restore(flags);
पूर्ण

/*
 * Unwire the last wired TLB entry.
 *
 * It should also be noted that it is not possible to wire and unwire
 * TLB entries in an arbitrary order. If you wire TLB entry N, followed
 * by entry N+1, you must unwire entry N+1 first, then entry N. In this
 * respect, it works like a stack or LIFO queue.
 */
व्योम tlb_unwire_entry(व्योम)
अणु
	अचिन्हित दीर्घ status, flags;
	पूर्णांक urb;

	local_irq_save(flags);

	status = __raw_पढ़ोl(MMUCR);
	urb = (status & MMUCR_URB) >> MMUCR_URB_SHIFT;
	status &= ~MMUCR_URB;

	/*
	 * Make sure we're not trying to unwire a TLB entry when none
	 * have been wired.
	 */
	BUG_ON(urb++ == MMUCR_URB_NENTRIES);

	urb = urb % MMUCR_URB_NENTRIES;

	status |= (urb << MMUCR_URB_SHIFT);
	__raw_ग_लिखोl(status, MMUCR);
	ctrl_barrier();

	local_irq_restore(flags);
पूर्ण
