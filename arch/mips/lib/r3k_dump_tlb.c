<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Dump R3000 TLB क्रम debugging purposes.
 *
 * Copyright (C) 1994, 1995 by Walकरोrf Electronics, written by Ralf Baechle.
 * Copyright (C) 1999 by Silicon Graphics, Inc.
 * Copyright (C) 1999 by Harald Koerfgen
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/tlbdebug.h>

बाह्य पूर्णांक r3k_have_wired_reg;

व्योम dump_tlb_regs(व्योम)
अणु
	pr_info("Index    : %0x\n", पढ़ो_c0_index());
	pr_info("EntryHi  : %0lx\n", पढ़ो_c0_entryhi());
	pr_info("EntryLo  : %0lx\n", पढ़ो_c0_entrylo0());
	अगर (r3k_have_wired_reg)
		pr_info("Wired    : %0x\n", पढ़ो_c0_wired());
पूर्ण

अटल व्योम dump_tlb(पूर्णांक first, पूर्णांक last)
अणु
	पूर्णांक	i;
	अचिन्हित पूर्णांक asid;
	अचिन्हित दीर्घ entryhi, entrylo0, asid_mask;

	asid_mask = cpu_asid_mask(&current_cpu_data);
	asid = पढ़ो_c0_entryhi() & asid_mask;

	क्रम (i = first; i <= last; i++) अणु
		ग_लिखो_c0_index(i<<8);
		__यंत्र__ __अस्थिर__(
			".set\tnoreorder\n\t"
			"tlbr\n\t"
			"nop\n\t"
			".set\treorder");
		entryhi	 = पढ़ो_c0_entryhi();
		entrylo0 = पढ़ो_c0_entrylo0();

		/* Unused entries have a भव address of KSEG0.  */
		अगर ((entryhi & PAGE_MASK) != KSEG0 &&
		    (entrylo0 & R3K_ENTRYLO_G ||
		     (entryhi & asid_mask) == asid)) अणु
			/*
			 * Only prपूर्णांक entries in use
			 */
			prपूर्णांकk("Index: %2d ", i);

			pr_cont("va=%08lx asid=%08lx"
				"  [pa=%06lx n=%d d=%d v=%d g=%d]",
				entryhi & PAGE_MASK,
				entryhi & asid_mask,
				entrylo0 & PAGE_MASK,
				(entrylo0 & R3K_ENTRYLO_N) ? 1 : 0,
				(entrylo0 & R3K_ENTRYLO_D) ? 1 : 0,
				(entrylo0 & R3K_ENTRYLO_V) ? 1 : 0,
				(entrylo0 & R3K_ENTRYLO_G) ? 1 : 0);
		पूर्ण
	पूर्ण
	prपूर्णांकk("\n");

	ग_लिखो_c0_entryhi(asid);
पूर्ण

व्योम dump_tlb_all(व्योम)
अणु
	dump_tlb(0, current_cpu_data.tlbsize - 1);
पूर्ण
