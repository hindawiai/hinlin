<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC tlb.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Julius Baxter <julius.baxter@orsoc.se>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/spr_defs.h>

#घोषणा NO_CONTEXT -1

#घोषणा NUM_DTLB_SETS (1 << ((mfspr(SPR_IMMUCFGR) & SPR_IMMUCFGR_NTS) >> \
			    SPR_DMMUCFGR_NTS_OFF))
#घोषणा NUM_ITLB_SETS (1 << ((mfspr(SPR_IMMUCFGR) & SPR_IMMUCFGR_NTS) >> \
			    SPR_IMMUCFGR_NTS_OFF))
#घोषणा DTLB_OFFSET(addr) (((addr) >> PAGE_SHIFT) & (NUM_DTLB_SETS-1))
#घोषणा ITLB_OFFSET(addr) (((addr) >> PAGE_SHIFT) & (NUM_ITLB_SETS-1))
/*
 * Invalidate all TLB entries.
 *
 * This comes करोwn to setting the 'valid' bit क्रम all xTLBMR रेजिस्टरs to 0.
 * Easiest way to accomplish this is to just zero out the xTLBMR रेजिस्टर
 * completely.
 *
 */

व्योम local_flush_tlb_all(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ num_tlb_sets;

	/* Determine number of sets क्रम IMMU. */
	/* FIXME: Assumption is I & D nsets equal. */
	num_tlb_sets = NUM_ITLB_SETS;

	क्रम (i = 0; i < num_tlb_sets; i++) अणु
		mtspr_off(SPR_DTLBMR_BASE(0), i, 0);
		mtspr_off(SPR_ITLBMR_BASE(0), i, 0);
	पूर्ण
पूर्ण

#घोषणा have_dtlbeir (mfspr(SPR_DMMUCFGR) & SPR_DMMUCFGR_TEIRI)
#घोषणा have_itlbeir (mfspr(SPR_IMMUCFGR) & SPR_IMMUCFGR_TEIRI)

/*
 * Invalidate a single page.  This is what the xTLBEIR रेजिस्टर is क्रम.
 *
 * There's no point in checking the vma for PAGE_EXEC to determine whether it's
 * the data or inकाष्ठाion TLB that should be flushed... that would take more
 * than the few inकाष्ठाions that the following compiles करोwn to!
 *
 * The हाल where we करोn't have the xTLBEIR रेजिस्टर really only works क्रम
 * MMU's with a single way and is hard-coded that way.
 */

#घोषणा flush_dtlb_page_eir(addr) mtspr(SPR_DTLBEIR, addr)
#घोषणा flush_dtlb_page_no_eir(addr) \
	mtspr_off(SPR_DTLBMR_BASE(0), DTLB_OFFSET(addr), 0);

#घोषणा flush_itlb_page_eir(addr) mtspr(SPR_ITLBEIR, addr)
#घोषणा flush_itlb_page_no_eir(addr) \
	mtspr_off(SPR_ITLBMR_BASE(0), ITLB_OFFSET(addr), 0);

व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	अगर (have_dtlbeir)
		flush_dtlb_page_eir(addr);
	अन्यथा
		flush_dtlb_page_no_eir(addr);

	अगर (have_itlbeir)
		flush_itlb_page_eir(addr);
	अन्यथा
		flush_itlb_page_no_eir(addr);
पूर्ण

व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	पूर्णांक addr;
	bool dtlbeir;
	bool itlbeir;

	dtlbeir = have_dtlbeir;
	itlbeir = have_itlbeir;

	क्रम (addr = start; addr < end; addr += PAGE_SIZE) अणु
		अगर (dtlbeir)
			flush_dtlb_page_eir(addr);
		अन्यथा
			flush_dtlb_page_no_eir(addr);

		अगर (itlbeir)
			flush_itlb_page_eir(addr);
		अन्यथा
			flush_itlb_page_no_eir(addr);
	पूर्ण
पूर्ण

/*
 * Invalidate the selected mm context only.
 *
 * FIXME: Due to some bug here, we're flushing everything क्रम now.
 * This should be changed to loop over over mm and call flush_tlb_range.
 */

व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु

	/* Was seeing bugs with the mm काष्ठा passed to us. Scrapped most of
	   this function. */
	/* Several architctures करो this */
	local_flush_tlb_all();
पूर्ण

/* called in schedule() just beक्रमe actually करोing the चयन_to */

व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
	       काष्ठा task_काष्ठा *next_tsk)
अणु
	अचिन्हित पूर्णांक cpu;

	अगर (unlikely(prev == next))
		वापस;

	cpu = smp_processor_id();

	cpumask_clear_cpu(cpu, mm_cpumask(prev));
	cpumask_set_cpu(cpu, mm_cpumask(next));

	/* remember the pgd क्रम the fault handlers
	 * this is similar to the pgd रेजिस्टर in some other CPU's.
	 * we need our own copy of it because current and active_mm
	 * might be invalid at poपूर्णांकs where we still need to derefer
	 * the pgd.
	 */
	current_pgd[cpu] = next->pgd;

	/* We करोn't have context support implemented, so flush all
	 * entries beदीर्घing to previous map
	 */
	local_flush_tlb_mm(prev);
पूर्ण

/*
 * Initialize the context related info क्रम a new mm_काष्ठा
 * instance.
 */

पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	mm->context = NO_CONTEXT;
	वापस 0;
पूर्ण

/* called by __निकास_mm to destroy the used MMU context अगर any beक्रमe
 * destroying the mm itself. this is only called when the last user of the mm
 * drops it.
 */

व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	flush_tlb_mm(mm);

पूर्ण

/* called once during VM initialization, from init.c */

व्योम __init tlb_init(व्योम)
अणु
	/* Do nothing... */
	/* invalidate the entire TLB */
	/* flush_tlb_all(); */
पूर्ण
