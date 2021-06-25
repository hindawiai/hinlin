<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1997, 1998, 1999, 2000 Ralf Baechle ralf@gnu.org
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2002 MIPS Technologies, Inc.  All rights reserved.
 */
#समावेश <linux/cpu_pm.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/hazards.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbmisc.h>

बाह्य व्योम build_tlb_refill_handler(व्योम);

/*
 * LOONGSON-2 has a 4 entry itlb which is a subset of jtlb, LOONGSON-3 has
 * a 4 entry itlb and a 4 entry dtlb which are subsets of jtlb. Unक्रमtunately,
 * itlb/dtlb are not totally transparent to software.
 */
अटल अंतरभूत व्योम flush_micro_tlb(व्योम)
अणु
	चयन (current_cpu_type()) अणु
	हाल CPU_LOONGSON2EF:
		ग_लिखो_c0_diag(LOONGSON_DIAG_ITLB);
		अवरोध;
	हाल CPU_LOONGSON64:
		ग_लिखो_c0_diag(LOONGSON_DIAG_ITLB | LOONGSON_DIAG_DTLB);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम flush_micro_tlb_vm(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->vm_flags & VM_EXEC)
		flush_micro_tlb();
पूर्ण

व्योम local_flush_tlb_all(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ old_ctx;
	पूर्णांक entry, ftlbhighset;

	local_irq_save(flags);
	/* Save old context and create impossible VPN2 value */
	old_ctx = पढ़ो_c0_entryhi();
	htw_stop();
	ग_लिखो_c0_entrylo0(0);
	ग_लिखो_c0_entrylo1(0);

	entry = num_wired_entries();

	/*
	 * Blast 'em all away.
	 * If there are any wired entries, fall back to iterating
	 */
	अगर (cpu_has_tlbinv && !entry) अणु
		अगर (current_cpu_data.tlbsizevtlb) अणु
			ग_लिखो_c0_index(0);
			mtc0_tlbw_hazard();
			tlbinvf();  /* invalidate VTLB */
		पूर्ण
		ftlbhighset = current_cpu_data.tlbsizevtlb +
			current_cpu_data.tlbsizeftlbsets;
		क्रम (entry = current_cpu_data.tlbsizevtlb;
		     entry < ftlbhighset;
		     entry++) अणु
			ग_लिखो_c0_index(entry);
			mtc0_tlbw_hazard();
			tlbinvf();  /* invalidate one FTLB set */
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (entry < current_cpu_data.tlbsize) अणु
			/* Make sure all entries dअगरfer. */
			ग_लिखो_c0_entryhi(UNIQUE_ENTRYHI(entry));
			ग_लिखो_c0_index(entry);
			mtc0_tlbw_hazard();
			tlb_ग_लिखो_indexed();
			entry++;
		पूर्ण
	पूर्ण
	tlbw_use_hazard();
	ग_लिखो_c0_entryhi(old_ctx);
	htw_start();
	flush_micro_tlb();
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(local_flush_tlb_all);

व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
	अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	पूर्णांक cpu = smp_processor_id();

	अगर (cpu_context(cpu, mm) != 0) अणु
		अचिन्हित दीर्घ size, flags;

		local_irq_save(flags);
		start = round_करोwn(start, PAGE_SIZE << 1);
		end = round_up(end, PAGE_SIZE << 1);
		size = (end - start) >> (PAGE_SHIFT + 1);
		अगर (size <= (current_cpu_data.tlbsizeftlbsets ?
			     current_cpu_data.tlbsize / 8 :
			     current_cpu_data.tlbsize / 2)) अणु
			अचिन्हित दीर्घ old_entryhi, old_mmid;
			पूर्णांक newpid = cpu_asid(cpu, mm);

			old_entryhi = पढ़ो_c0_entryhi();
			अगर (cpu_has_mmid) अणु
				old_mmid = पढ़ो_c0_memorymapid();
				ग_लिखो_c0_memorymapid(newpid);
			पूर्ण

			htw_stop();
			जबतक (start < end) अणु
				पूर्णांक idx;

				अगर (cpu_has_mmid)
					ग_लिखो_c0_entryhi(start);
				अन्यथा
					ग_लिखो_c0_entryhi(start | newpid);
				start += (PAGE_SIZE << 1);
				mtc0_tlbw_hazard();
				tlb_probe();
				tlb_probe_hazard();
				idx = पढ़ो_c0_index();
				ग_लिखो_c0_entrylo0(0);
				ग_लिखो_c0_entrylo1(0);
				अगर (idx < 0)
					जारी;
				/* Make sure all entries dअगरfer. */
				ग_लिखो_c0_entryhi(UNIQUE_ENTRYHI(idx));
				mtc0_tlbw_hazard();
				tlb_ग_लिखो_indexed();
			पूर्ण
			tlbw_use_hazard();
			ग_लिखो_c0_entryhi(old_entryhi);
			अगर (cpu_has_mmid)
				ग_लिखो_c0_memorymapid(old_mmid);
			htw_start();
		पूर्ण अन्यथा अणु
			drop_mmu_context(mm);
		पूर्ण
		flush_micro_tlb();
		local_irq_restore(flags);
	पूर्ण
पूर्ण

व्योम local_flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ size, flags;

	local_irq_save(flags);
	size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	size = (size + 1) >> 1;
	अगर (size <= (current_cpu_data.tlbsizeftlbsets ?
		     current_cpu_data.tlbsize / 8 :
		     current_cpu_data.tlbsize / 2)) अणु
		पूर्णांक pid = पढ़ो_c0_entryhi();

		start &= (PAGE_MASK << 1);
		end += ((PAGE_SIZE << 1) - 1);
		end &= (PAGE_MASK << 1);
		htw_stop();

		जबतक (start < end) अणु
			पूर्णांक idx;

			ग_लिखो_c0_entryhi(start);
			start += (PAGE_SIZE << 1);
			mtc0_tlbw_hazard();
			tlb_probe();
			tlb_probe_hazard();
			idx = पढ़ो_c0_index();
			ग_लिखो_c0_entrylo0(0);
			ग_लिखो_c0_entrylo1(0);
			अगर (idx < 0)
				जारी;
			/* Make sure all entries dअगरfer. */
			ग_लिखो_c0_entryhi(UNIQUE_ENTRYHI(idx));
			mtc0_tlbw_hazard();
			tlb_ग_लिखो_indexed();
		पूर्ण
		tlbw_use_hazard();
		ग_लिखो_c0_entryhi(pid);
		htw_start();
	पूर्ण अन्यथा अणु
		local_flush_tlb_all();
	पूर्ण
	flush_micro_tlb();
	local_irq_restore(flags);
पूर्ण

व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	पूर्णांक cpu = smp_processor_id();

	अगर (cpu_context(cpu, vma->vm_mm) != 0) अणु
		अचिन्हित दीर्घ old_mmid;
		अचिन्हित दीर्घ flags, old_entryhi;
		पूर्णांक idx;

		page &= (PAGE_MASK << 1);
		local_irq_save(flags);
		old_entryhi = पढ़ो_c0_entryhi();
		htw_stop();
		अगर (cpu_has_mmid) अणु
			old_mmid = पढ़ो_c0_memorymapid();
			ग_लिखो_c0_entryhi(page);
			ग_लिखो_c0_memorymapid(cpu_asid(cpu, vma->vm_mm));
		पूर्ण अन्यथा अणु
			ग_लिखो_c0_entryhi(page | cpu_asid(cpu, vma->vm_mm));
		पूर्ण
		mtc0_tlbw_hazard();
		tlb_probe();
		tlb_probe_hazard();
		idx = पढ़ो_c0_index();
		ग_लिखो_c0_entrylo0(0);
		ग_लिखो_c0_entrylo1(0);
		अगर (idx < 0)
			जाओ finish;
		/* Make sure all entries dअगरfer. */
		ग_लिखो_c0_entryhi(UNIQUE_ENTRYHI(idx));
		mtc0_tlbw_hazard();
		tlb_ग_लिखो_indexed();
		tlbw_use_hazard();

	finish:
		ग_लिखो_c0_entryhi(old_entryhi);
		अगर (cpu_has_mmid)
			ग_लिखो_c0_memorymapid(old_mmid);
		htw_start();
		flush_micro_tlb_vm(vma);
		local_irq_restore(flags);
	पूर्ण
पूर्ण

/*
 * This one is only used क्रम pages with the global bit set so we करोn't care
 * much about the ASID.
 */
व्योम local_flush_tlb_one(अचिन्हित दीर्घ page)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक oldpid, idx;

	local_irq_save(flags);
	oldpid = पढ़ो_c0_entryhi();
	htw_stop();
	page &= (PAGE_MASK << 1);
	ग_लिखो_c0_entryhi(page);
	mtc0_tlbw_hazard();
	tlb_probe();
	tlb_probe_hazard();
	idx = पढ़ो_c0_index();
	ग_लिखो_c0_entrylo0(0);
	ग_लिखो_c0_entrylo1(0);
	अगर (idx >= 0) अणु
		/* Make sure all entries dअगरfer. */
		ग_लिखो_c0_entryhi(UNIQUE_ENTRYHI(idx));
		mtc0_tlbw_hazard();
		tlb_ग_लिखो_indexed();
		tlbw_use_hazard();
	पूर्ण
	ग_लिखो_c0_entryhi(oldpid);
	htw_start();
	flush_micro_tlb();
	local_irq_restore(flags);
पूर्ण

/*
 * We will need multiple versions of update_mmu_cache(), one that just
 * updates the TLB with the new pte(s), and another which also checks
 * क्रम the R4k "end of page" hardware bug and करोes the needy.
 */
व्योम __update_tlb(काष्ठा vm_area_काष्ठा * vma, अचिन्हित दीर्घ address, pte_t pte)
अणु
	अचिन्हित दीर्घ flags;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;
	पूर्णांक idx, pid;

	/*
	 * Handle debugger faulting in क्रम debugee.
	 */
	अगर (current->active_mm != vma->vm_mm)
		वापस;

	local_irq_save(flags);

	htw_stop();
	address &= (PAGE_MASK << 1);
	अगर (cpu_has_mmid) अणु
		ग_लिखो_c0_entryhi(address);
	पूर्ण अन्यथा अणु
		pid = पढ़ो_c0_entryhi() & cpu_asid_mask(&current_cpu_data);
		ग_लिखो_c0_entryhi(address | pid);
	पूर्ण
	pgdp = pgd_offset(vma->vm_mm, address);
	mtc0_tlbw_hazard();
	tlb_probe();
	tlb_probe_hazard();
	p4dp = p4d_offset(pgdp, address);
	pudp = pud_offset(p4dp, address);
	pmdp = pmd_offset(pudp, address);
	idx = पढ़ो_c0_index();
#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	/* this could be a huge page  */
	अगर (pmd_huge(*pmdp)) अणु
		अचिन्हित दीर्घ lo;
		ग_लिखो_c0_pagemask(PM_HUGE_MASK);
		ptep = (pte_t *)pmdp;
		lo = pte_to_entrylo(pte_val(*ptep));
		ग_लिखो_c0_entrylo0(lo);
		ग_लिखो_c0_entrylo1(lo + (HPAGE_SIZE >> 7));

		mtc0_tlbw_hazard();
		अगर (idx < 0)
			tlb_ग_लिखो_अक्रमom();
		अन्यथा
			tlb_ग_लिखो_indexed();
		tlbw_use_hazard();
		ग_लिखो_c0_pagemask(PM_DEFAULT_MASK);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		ptep = pte_offset_map(pmdp, address);

#अगर defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_CPU_MIPS32)
#अगर_घोषित CONFIG_XPA
		ग_लिखो_c0_entrylo0(pte_to_entrylo(ptep->pte_high));
		अगर (cpu_has_xpa)
			ग_लिखोx_c0_entrylo0(ptep->pte_low & _PFNX_MASK);
		ptep++;
		ग_लिखो_c0_entrylo1(pte_to_entrylo(ptep->pte_high));
		अगर (cpu_has_xpa)
			ग_लिखोx_c0_entrylo1(ptep->pte_low & _PFNX_MASK);
#अन्यथा
		ग_लिखो_c0_entrylo0(ptep->pte_high);
		ptep++;
		ग_लिखो_c0_entrylo1(ptep->pte_high);
#पूर्ण_अगर
#अन्यथा
		ग_लिखो_c0_entrylo0(pte_to_entrylo(pte_val(*ptep++)));
		ग_लिखो_c0_entrylo1(pte_to_entrylo(pte_val(*ptep)));
#पूर्ण_अगर
		mtc0_tlbw_hazard();
		अगर (idx < 0)
			tlb_ग_लिखो_अक्रमom();
		अन्यथा
			tlb_ग_लिखो_indexed();
	पूर्ण
	tlbw_use_hazard();
	htw_start();
	flush_micro_tlb_vm(vma);
	local_irq_restore(flags);
पूर्ण

व्योम add_wired_entry(अचिन्हित दीर्घ entrylo0, अचिन्हित दीर्घ entrylo1,
		     अचिन्हित दीर्घ entryhi, अचिन्हित दीर्घ pagemask)
अणु
#अगर_घोषित CONFIG_XPA
	panic("Broken for XPA kernels");
#अन्यथा
	अचिन्हित पूर्णांक old_mmid;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ wired;
	अचिन्हित दीर्घ old_pagemask;
	अचिन्हित दीर्घ old_ctx;

	local_irq_save(flags);
	अगर (cpu_has_mmid) अणु
		old_mmid = पढ़ो_c0_memorymapid();
		ग_लिखो_c0_memorymapid(MMID_KERNEL_WIRED);
	पूर्ण
	/* Save old context and create impossible VPN2 value */
	old_ctx = पढ़ो_c0_entryhi();
	htw_stop();
	old_pagemask = पढ़ो_c0_pagemask();
	wired = num_wired_entries();
	ग_लिखो_c0_wired(wired + 1);
	ग_लिखो_c0_index(wired);
	tlbw_use_hazard();	/* What is the hazard here? */
	ग_लिखो_c0_pagemask(pagemask);
	ग_लिखो_c0_entryhi(entryhi);
	ग_लिखो_c0_entrylo0(entrylo0);
	ग_लिखो_c0_entrylo1(entrylo1);
	mtc0_tlbw_hazard();
	tlb_ग_लिखो_indexed();
	tlbw_use_hazard();

	ग_लिखो_c0_entryhi(old_ctx);
	अगर (cpu_has_mmid)
		ग_लिखो_c0_memorymapid(old_mmid);
	tlbw_use_hazard();	/* What is the hazard here? */
	htw_start();
	ग_लिखो_c0_pagemask(old_pagemask);
	local_flush_tlb_all();
	local_irq_restore(flags);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE

पूर्णांक has_transparent_hugepage(व्योम)
अणु
	अटल अचिन्हित पूर्णांक mask = -1;

	अगर (mask == -1) अणु	/* first call comes during __init */
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		ग_लिखो_c0_pagemask(PM_HUGE_MASK);
		back_to_back_c0_hazard();
		mask = पढ़ो_c0_pagemask();
		ग_लिखो_c0_pagemask(PM_DEFAULT_MASK);
		local_irq_restore(flags);
	पूर्ण
	वापस mask == PM_HUGE_MASK;
पूर्ण
EXPORT_SYMBOL(has_transparent_hugepage);

#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE  */

/*
 * Used क्रम loading TLB entries beक्रमe trap_init() has started, when we
 * करोn't actually want to add a wired entry which reमुख्यs throughout the
 * lअगरeसमय of the प्रणाली
 */

पूर्णांक temp_tlb_entry;

__init पूर्णांक add_temporary_entry(अचिन्हित दीर्घ entrylo0, अचिन्हित दीर्घ entrylo1,
			       अचिन्हित दीर्घ entryhi, अचिन्हित दीर्घ pagemask)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ wired;
	अचिन्हित दीर्घ old_pagemask;
	अचिन्हित दीर्घ old_ctx;

	local_irq_save(flags);
	/* Save old context and create impossible VPN2 value */
	htw_stop();
	old_ctx = पढ़ो_c0_entryhi();
	old_pagemask = पढ़ो_c0_pagemask();
	wired = num_wired_entries();
	अगर (--temp_tlb_entry < wired) अणु
		prपूर्णांकk(KERN_WARNING
		       "No TLB space left for add_temporary_entry\n");
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	ग_लिखो_c0_index(temp_tlb_entry);
	ग_लिखो_c0_pagemask(pagemask);
	ग_लिखो_c0_entryhi(entryhi);
	ग_लिखो_c0_entrylo0(entrylo0);
	ग_लिखो_c0_entrylo1(entrylo1);
	mtc0_tlbw_hazard();
	tlb_ग_लिखो_indexed();
	tlbw_use_hazard();

	ग_लिखो_c0_entryhi(old_ctx);
	ग_लिखो_c0_pagemask(old_pagemask);
	htw_start();
out:
	local_irq_restore(flags);
	वापस ret;
पूर्ण

अटल पूर्णांक ntlb;
अटल पूर्णांक __init set_ntlb(अक्षर *str)
अणु
	get_option(&str, &ntlb);
	वापस 1;
पूर्ण

__setup("ntlb=", set_ntlb);

/*
 * Configure TLB (क्रम init or after a CPU has been घातered off).
 */
अटल व्योम r4k_tlb_configure(व्योम)
अणु
	/*
	 * You should never change this रेजिस्टर:
	 *   - On R4600 1.7 the tlbp never hits क्रम pages smaller than
	 *     the value in the c0_pagemask रेजिस्टर.
	 *   - The entire mm handling assumes the c0_pagemask रेजिस्टर to
	 *     be set to fixed-size pages.
	 */
	ग_लिखो_c0_pagemask(PM_DEFAULT_MASK);
	back_to_back_c0_hazard();
	अगर (पढ़ो_c0_pagemask() != PM_DEFAULT_MASK)
		panic("MMU doesn't support PAGE_SIZE=0x%lx", PAGE_SIZE);

	ग_लिखो_c0_wired(0);
	अगर (current_cpu_type() == CPU_R10000 ||
	    current_cpu_type() == CPU_R12000 ||
	    current_cpu_type() == CPU_R14000 ||
	    current_cpu_type() == CPU_R16000)
		ग_लिखो_c0_framemask(0);

	अगर (cpu_has_rixi) अणु
		/*
		 * Enable the no पढ़ो, no exec bits, and enable large physical
		 * address.
		 */
#अगर_घोषित CONFIG_64BIT
		set_c0_pagegrain(PG_RIE | PG_XIE | PG_ELPA);
#अन्यथा
		set_c0_pagegrain(PG_RIE | PG_XIE);
#पूर्ण_अगर
	पूर्ण

	temp_tlb_entry = current_cpu_data.tlbsize - 1;

	/* From this poपूर्णांक on the ARC firmware is dead.	 */
	local_flush_tlb_all();

	/* Did I tell you that ARC SUCKS?  */
पूर्ण

व्योम tlb_init(व्योम)
अणु
	r4k_tlb_configure();

	अगर (ntlb) अणु
		अगर (ntlb > 1 && ntlb <= current_cpu_data.tlbsize) अणु
			पूर्णांक wired = current_cpu_data.tlbsize - ntlb;
			ग_लिखो_c0_wired(wired);
			ग_लिखो_c0_index(wired-1);
			prपूर्णांकk("Restricting TLB to %d entries\n", ntlb);
		पूर्ण अन्यथा
			prपूर्णांकk("Ignoring invalid argument ntlb=%d\n", ntlb);
	पूर्ण

	build_tlb_refill_handler();
पूर्ण

अटल पूर्णांक r4k_tlb_pm_notअगरier(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd,
			       व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_PM_ENTER_FAILED:
	हाल CPU_PM_EXIT:
		r4k_tlb_configure();
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block r4k_tlb_pm_notअगरier_block = अणु
	.notअगरier_call = r4k_tlb_pm_notअगरier,
पूर्ण;

अटल पूर्णांक __init r4k_tlb_init_pm(व्योम)
अणु
	वापस cpu_pm_रेजिस्टर_notअगरier(&r4k_tlb_pm_notअगरier_block);
पूर्ण
arch_initcall(r4k_tlb_init_pm);
