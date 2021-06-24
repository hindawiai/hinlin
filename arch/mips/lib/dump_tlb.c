<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Dump R4x00 TLB क्रम debugging purposes.
 *
 * Copyright (C) 1994, 1995 by Walकरोrf Electronics, written by Ralf Baechle.
 * Copyright (C) 1999 by Silicon Graphics, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/hazards.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/tlbdebug.h>

व्योम dump_tlb_regs(व्योम)
अणु
	स्थिर पूर्णांक field = 2 * माप(अचिन्हित दीर्घ);

	pr_info("Index    : %0x\n", पढ़ो_c0_index());
	pr_info("PageMask : %0x\n", पढ़ो_c0_pagemask());
	अगर (cpu_has_guestid)
		pr_info("GuestCtl1: %0x\n", पढ़ो_c0_guestctl1());
	pr_info("EntryHi  : %0*lx\n", field, पढ़ो_c0_entryhi());
	pr_info("EntryLo0 : %0*lx\n", field, पढ़ो_c0_entrylo0());
	pr_info("EntryLo1 : %0*lx\n", field, पढ़ो_c0_entrylo1());
	pr_info("Wired    : %0x\n", पढ़ो_c0_wired());
	चयन (current_cpu_type()) अणु
	हाल CPU_R10000:
	हाल CPU_R12000:
	हाल CPU_R14000:
	हाल CPU_R16000:
		pr_info("FrameMask: %0x\n", पढ़ो_c0_framemask());
		अवरोध;
	पूर्ण
	अगर (cpu_has_small_pages || cpu_has_rixi || cpu_has_xpa)
		pr_info("PageGrain: %0x\n", पढ़ो_c0_pagegrain());
	अगर (cpu_has_htw) अणु
		pr_info("PWField  : %0*lx\n", field, पढ़ो_c0_pwfield());
		pr_info("PWSize   : %0*lx\n", field, पढ़ो_c0_pwsize());
		pr_info("PWCtl    : %0x\n", पढ़ो_c0_pwctl());
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *msk2str(अचिन्हित पूर्णांक mask)
अणु
	चयन (mask) अणु
	हाल PM_4K:	वापस "4kb";
	हाल PM_16K:	वापस "16kb";
	हाल PM_64K:	वापस "64kb";
	हाल PM_256K:	वापस "256kb";
#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
	हाल PM_8K:	वापस "8kb";
	हाल PM_32K:	वापस "32kb";
	हाल PM_128K:	वापस "128kb";
	हाल PM_512K:	वापस "512kb";
	हाल PM_2M:	वापस "2Mb";
	हाल PM_8M:	वापस "8Mb";
	हाल PM_32M:	वापस "32Mb";
#पूर्ण_अगर
#अगर_अघोषित CONFIG_CPU_VR41XX
	हाल PM_1M:	वापस "1Mb";
	हाल PM_4M:	वापस "4Mb";
	हाल PM_16M:	वापस "16Mb";
	हाल PM_64M:	वापस "64Mb";
	हाल PM_256M:	वापस "256Mb";
	हाल PM_1G:	वापस "1Gb";
#पूर्ण_अगर
	पूर्ण
	वापस "";
पूर्ण

अटल व्योम dump_tlb(पूर्णांक first, पूर्णांक last)
अणु
	अचिन्हित दीर्घ s_entryhi, entryhi, asid, mmid;
	अचिन्हित दीर्घ दीर्घ entrylo0, entrylo1, pa;
	अचिन्हित पूर्णांक s_index, s_pagemask, s_guestctl1 = 0;
	अचिन्हित पूर्णांक pagemask, guestctl1 = 0, c0, c1, i;
	अचिन्हित दीर्घ asidmask = cpu_asid_mask(&current_cpu_data);
	पूर्णांक asidwidth = DIV_ROUND_UP(ilog2(asidmask) + 1, 4);
	अचिन्हित दीर्घ s_mmid;
#अगर_घोषित CONFIG_32BIT
	bool xpa = cpu_has_xpa && (पढ़ो_c0_pagegrain() & PG_ELPA);
	पूर्णांक pwidth = xpa ? 11 : 8;
	पूर्णांक vwidth = 8;
#अन्यथा
	bool xpa = false;
	पूर्णांक pwidth = 11;
	पूर्णांक vwidth = 11;
#पूर्ण_अगर

	s_pagemask = पढ़ो_c0_pagemask();
	s_entryhi = पढ़ो_c0_entryhi();
	s_index = पढ़ो_c0_index();

	अगर (cpu_has_mmid)
		asid = s_mmid = पढ़ो_c0_memorymapid();
	अन्यथा
		asid = s_entryhi & asidmask;

	अगर (cpu_has_guestid)
		s_guestctl1 = पढ़ो_c0_guestctl1();

	क्रम (i = first; i <= last; i++) अणु
		ग_लिखो_c0_index(i);
		mtc0_tlbr_hazard();
		tlb_पढ़ो();
		tlb_पढ़ो_hazard();
		pagemask = पढ़ो_c0_pagemask();
		entryhi	 = पढ़ो_c0_entryhi();
		entrylo0 = पढ़ो_c0_entrylo0();
		entrylo1 = पढ़ो_c0_entrylo1();

		अगर (cpu_has_mmid)
			mmid = पढ़ो_c0_memorymapid();
		अन्यथा
			mmid = entryhi & asidmask;

		अगर (cpu_has_guestid)
			guestctl1 = पढ़ो_c0_guestctl1();

		/* EHINV bit marks entire entry as invalid */
		अगर (cpu_has_tlbinv && entryhi & MIPS_ENTRYHI_EHINV)
			जारी;
		/*
		 * Prior to tlbinv, unused entries have a भव address of
		 * CKSEG0.
		 */
		अगर ((entryhi & ~0x1ffffUL) == CKSEG0)
			जारी;
		/*
		 * ASID takes effect in असलence of G (global) bit.
		 * We check both G bits, even though architecturally they should
		 * match one another, because some revisions of the SB1 core may
		 * leave only a single G bit set after a machine check exception
		 * due to duplicate TLB entry.
		 */
		अगर (!((entrylo0 | entrylo1) & ENTRYLO_G) && (mmid != asid))
			जारी;

		/*
		 * Only prपूर्णांक entries in use
		 */
		prपूर्णांकk("Index: %2d pgmask=%s ", i, msk2str(pagemask));

		c0 = (entrylo0 & ENTRYLO_C) >> ENTRYLO_C_SHIFT;
		c1 = (entrylo1 & ENTRYLO_C) >> ENTRYLO_C_SHIFT;

		pr_cont("va=%0*lx asid=%0*lx",
			vwidth, (entryhi & ~0x1fffUL),
			asidwidth, mmid);
		अगर (cpu_has_guestid)
			pr_cont(" gid=%02lx",
				(guestctl1 & MIPS_GCTL1_RID)
					>> MIPS_GCTL1_RID_SHIFT);
		/* RI/XI are in awkward places, so mask them off separately */
		pa = entrylo0 & ~(MIPS_ENTRYLO_RI | MIPS_ENTRYLO_XI);
		अगर (xpa)
			pa |= (अचिन्हित दीर्घ दीर्घ)पढ़ोx_c0_entrylo0() << 30;
		pa = (pa << 6) & PAGE_MASK;
		pr_cont("\n\t[");
		अगर (cpu_has_rixi)
			pr_cont("ri=%d xi=%d ",
				(entrylo0 & MIPS_ENTRYLO_RI) ? 1 : 0,
				(entrylo0 & MIPS_ENTRYLO_XI) ? 1 : 0);
		pr_cont("pa=%0*llx c=%d d=%d v=%d g=%d] [",
			pwidth, pa, c0,
			(entrylo0 & ENTRYLO_D) ? 1 : 0,
			(entrylo0 & ENTRYLO_V) ? 1 : 0,
			(entrylo0 & ENTRYLO_G) ? 1 : 0);
		/* RI/XI are in awkward places, so mask them off separately */
		pa = entrylo1 & ~(MIPS_ENTRYLO_RI | MIPS_ENTRYLO_XI);
		अगर (xpa)
			pa |= (अचिन्हित दीर्घ दीर्घ)पढ़ोx_c0_entrylo1() << 30;
		pa = (pa << 6) & PAGE_MASK;
		अगर (cpu_has_rixi)
			pr_cont("ri=%d xi=%d ",
				(entrylo1 & MIPS_ENTRYLO_RI) ? 1 : 0,
				(entrylo1 & MIPS_ENTRYLO_XI) ? 1 : 0);
		pr_cont("pa=%0*llx c=%d d=%d v=%d g=%d]\n",
			pwidth, pa, c1,
			(entrylo1 & ENTRYLO_D) ? 1 : 0,
			(entrylo1 & ENTRYLO_V) ? 1 : 0,
			(entrylo1 & ENTRYLO_G) ? 1 : 0);
	पूर्ण
	prपूर्णांकk("\n");

	ग_लिखो_c0_entryhi(s_entryhi);
	ग_लिखो_c0_index(s_index);
	ग_लिखो_c0_pagemask(s_pagemask);
	अगर (cpu_has_guestid)
		ग_लिखो_c0_guestctl1(s_guestctl1);
पूर्ण

व्योम dump_tlb_all(व्योम)
अणु
	dump_tlb(0, current_cpu_data.tlbsize - 1);
पूर्ण
