<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * x86 KFENCE support.
 *
 * Copyright (C) 2020, Google LLC.
 */

#अगर_अघोषित _ASM_X86_KFENCE_H
#घोषणा _ASM_X86_KFENCE_H

#समावेश <linux/bug.h>
#समावेश <linux/kfence.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/pgtable.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/tlbflush.h>

/* Force 4K pages क्रम __kfence_pool. */
अटल अंतरभूत bool arch_kfence_init_pool(व्योम)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = (अचिन्हित दीर्घ)__kfence_pool; is_kfence_address((व्योम *)addr);
	     addr += PAGE_SIZE) अणु
		अचिन्हित पूर्णांक level;

		अगर (!lookup_address(addr, &level))
			वापस false;

		अगर (level != PG_LEVEL_4K)
			set_memory_4k(addr, 1);
	पूर्ण

	वापस true;
पूर्ण

/* Protect the given page and flush TLB. */
अटल अंतरभूत bool kfence_protect_page(अचिन्हित दीर्घ addr, bool protect)
अणु
	अचिन्हित पूर्णांक level;
	pte_t *pte = lookup_address(addr, &level);

	अगर (WARN_ON(!pte || level != PG_LEVEL_4K))
		वापस false;

	/*
	 * We need to aव्योम IPIs, as we may get KFENCE allocations or faults
	 * with पूर्णांकerrupts disabled. Thereक्रमe, the below is best-efक्रमt, and
	 * करोes not flush TLBs on all CPUs. We can tolerate some inaccuracy;
	 * lazy fault handling takes care of faults after the page is PRESENT.
	 */

	अगर (protect)
		set_pte(pte, __pte(pte_val(*pte) & ~_PAGE_PRESENT));
	अन्यथा
		set_pte(pte, __pte(pte_val(*pte) | _PAGE_PRESENT));

	/*
	 * Flush this CPU's TLB, assuming whoever did the allocation/मुक्त is
	 * likely to जारी running on this CPU.
	 */
	preempt_disable();
	flush_tlb_one_kernel(addr);
	preempt_enable();
	वापस true;
पूर्ण

#पूर्ण_अगर /* _ASM_X86_KFENCE_H */
