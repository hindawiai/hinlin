<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TLB Management (flush/create/diagnostics) क्रम ARC700
 *
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: Aug 2011
 *  -Reपूर्णांकroduce duplicate PD fixup - some customer chips still have the issue
 *
 * vineetg: May 2011
 *  -No need to flush_cache_page( ) क्रम each call to update_mmu_cache()
 *   some of the LMBench tests improved amazingly
 *      = page-fault thrice as fast (75 usec to 28 usec)
 *      = mmap twice as fast (9.6 msec to 4.6 msec),
 *      = विभाजन (5.3 msec to 3.7 msec)
 *
 * vineetg: April 2011 :
 *  -MMU v3: PDअणु0,1पूर्ण bits layout changed: They करोn't overlap anymore,
 *      helps aव्योम a shअगरt when preparing PD0 from PTE
 *
 * vineetg: April 2011 : Preparing क्रम MMU V3
 *  -MMU v2/v3 BCRs decoded dअगरferently
 *  -Remove TLB_SIZE hardcoding as it's variable now: 256 or 512
 *  -tlb_entry_erase( ) can be व्योम
 *  -local_flush_tlb_range( ):
 *      = need not "ceil" @end
 *      = walks MMU only अगर range spans < 32 entries, as opposed to 256
 *
 * Vineetg: Sept 10th 2008
 *  -Changes related to MMU v2 (Rel 4.8)
 *
 * Vineetg: Aug 29th 2008
 *  -In TLB Flush operations (Metal Fix MMU) there is a explicit command to
 *    flush Micro-TLBS. If TLB Index Reg is invalid prior to TLBIVUTLB cmd,
 *    it fails. Thus need to load it with ANY valid value beक्रमe invoking
 *    TLBIVUTLB cmd
 *
 * Vineetg: Aug 21th 2008:
 *  -Reduced the duration of IRQ lockouts in TLB Flush routines
 *  -Multiple copies of TLB erase code separated पूर्णांकo a "single" function
 *  -In TLB Flush routines, पूर्णांकerrupt disabling moved UP to retrieve ASID
 *       in पूर्णांकerrupt-safe region.
 *
 * Vineetg: April 23rd Bug #93131
 *    Problem: tlb_flush_kernel_range() करोesn't करो anything अगर the range to
 *              flush is more than the size of TLB itself.
 *
 * Rahul Trivedi : Codito Technologies 2004
 */

#समावेश <linux/module.h>
#समावेश <linux/bug.h>
#समावेश <linux/mm_types.h>

#समावेश <यंत्र/arcregs.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mmu.h>

/*			Need क्रम ARC MMU v2
 *
 * ARC700 MMU-v1 had a Joपूर्णांक-TLB क्रम Code and Data and is 2 way set-assoc.
 * For a स_नकल operation with 3 players (src/dst/code) such that all 3 pages
 * map पूर्णांकo same set, there would be contention क्रम the 2 ways causing severe
 * Thrashing.
 *
 * Although J-TLB is 2 way set assoc, ARC700 caches J-TLB पूर्णांकo uTLBS which has
 * much higher associativity. u-D-TLB is 8 ways, u-I-TLB is 4 ways.
 * Given this, the thrashing problem should never happen because once the 3
 * J-TLB entries are created (even though 3rd will knock out one of the prev
 * two), the u-D-TLB and u-I-TLB will have what is required to accomplish स_नकल
 *
 * Yet we still see the Thrashing because a J-TLB Write cause flush of u-TLBs.
 * This is a simple design क्रम keeping them in sync. So what करो we करो?
 * The solution which James came up was pretty neat. It utilised the assoc
 * of uTLBs by not invalidating always but only when असलolutely necessary.
 *
 * - Existing TLB commands work as beक्रमe
 * - New command (TLBWriteNI) क्रम TLB ग_लिखो without clearing uTLBs
 * - New command (TLBIVUTLB) to invalidate uTLBs.
 *
 * The uTLBs need only be invalidated when pages are being हटाओd from the
 * OS page table. If a 'victim' TLB entry is being overwritten in the मुख्य TLB
 * as a result of a miss, the हटाओd entry is still allowed to exist in the
 * uTLBs as it is still valid and present in the OS page table. This allows the
 * full associativity of the uTLBs to hide the limited associativity of the मुख्य
 * TLB.
 *
 * During a miss handler, the new "TLBWriteNI" command is used to load
 * entries without clearing the uTLBs.
 *
 * When the OS page table is updated, TLB entries that may be associated with a
 * हटाओd page are हटाओd (flushed) from the TLB using TLBWrite. In this
 * circumstance, the uTLBs must also be cleared. This is करोne by using the
 * existing TLBWrite command. An explicit IVUTLB is also required क्रम those
 * corner हालs when TLBWrite was not executed at all because the corresp
 * J-TLB entry got evicted/replaced.
 */


/* A copy of the ASID from the PID reg is kept in asid_cache */
DEFINE_PER_CPU(अचिन्हित पूर्णांक, asid_cache) = MM_CTXT_FIRST_CYCLE;

अटल पूर्णांक __पढ़ो_mostly pae_exists;

/*
 * Utility Routine to erase a J-TLB entry
 * Caller needs to setup Index Reg (manually or via getIndex)
 */
अटल अंतरभूत व्योम __tlb_entry_erase(व्योम)
अणु
	ग_लिखो_aux_reg(ARC_REG_TLBPD1, 0);

	अगर (is_pae40_enabled())
		ग_लिखो_aux_reg(ARC_REG_TLBPD1HI, 0);

	ग_लिखो_aux_reg(ARC_REG_TLBPD0, 0);
	ग_लिखो_aux_reg(ARC_REG_TLBCOMMAND, TLBWrite);
पूर्ण

अटल व्योम utlb_invalidate(व्योम)
अणु
#अगर (CONFIG_ARC_MMU_VER >= 2)

#अगर (CONFIG_ARC_MMU_VER == 2)
	/* MMU v2 पूर्णांकroduced the uTLB Flush command.
	 * There was however an obscure hardware bug, where uTLB flush would
	 * fail when a prior probe क्रम J-TLB (both totally unrelated) would
	 * वापस lkup err - because the entry didn't exist in MMU.
	 * The Workaround was to set Index reg with some valid value, prior to
	 * flush. This was fixed in MMU v3
	 */
	अचिन्हित पूर्णांक idx;

	/* make sure INDEX Reg is valid */
	idx = पढ़ो_aux_reg(ARC_REG_TLBINDEX);

	/* If not ग_लिखो some dummy val */
	अगर (unlikely(idx & TLB_LKUP_ERR))
		ग_लिखो_aux_reg(ARC_REG_TLBINDEX, 0xa);
#पूर्ण_अगर

	ग_लिखो_aux_reg(ARC_REG_TLBCOMMAND, TLBIVUTLB);
#पूर्ण_अगर

पूर्ण

#अगर (CONFIG_ARC_MMU_VER < 4)

अटल अंतरभूत अचिन्हित पूर्णांक tlb_entry_lkup(अचिन्हित दीर्घ vaddr_n_asid)
अणु
	अचिन्हित पूर्णांक idx;

	ग_लिखो_aux_reg(ARC_REG_TLBPD0, vaddr_n_asid);

	ग_लिखो_aux_reg(ARC_REG_TLBCOMMAND, TLBProbe);
	idx = पढ़ो_aux_reg(ARC_REG_TLBINDEX);

	वापस idx;
पूर्ण

अटल व्योम tlb_entry_erase(अचिन्हित पूर्णांक vaddr_n_asid)
अणु
	अचिन्हित पूर्णांक idx;

	/* Locate the TLB entry क्रम this vaddr + ASID */
	idx = tlb_entry_lkup(vaddr_n_asid);

	/* No error means entry found, zero it out */
	अगर (likely(!(idx & TLB_LKUP_ERR))) अणु
		__tlb_entry_erase();
	पूर्ण अन्यथा अणु
		/* Duplicate entry error */
		WARN(idx == TLB_DUP_ERR, "Probe returned Dup PD for %x\n",
					   vaddr_n_asid);
	पूर्ण
पूर्ण

अटल व्योम tlb_entry_insert(अचिन्हित पूर्णांक pd0, pte_t pd1)
अणु
	अचिन्हित पूर्णांक idx;

	/*
	 * First verअगरy अगर entry क्रम this vaddr+ASID alपढ़ोy exists
	 * This also sets up PD0 (vaddr, ASID..) क्रम final commit
	 */
	idx = tlb_entry_lkup(pd0);

	/*
	 * If Not alपढ़ोy present get a मुक्त slot from MMU.
	 * Otherwise, Probe would have located the entry and set INDEX Reg
	 * with existing location. This will cause Write CMD to over-ग_लिखो
	 * existing entry with new PD0 and PD1
	 */
	अगर (likely(idx & TLB_LKUP_ERR))
		ग_लिखो_aux_reg(ARC_REG_TLBCOMMAND, TLBGetIndex);

	/* setup the other half of TLB entry (pfn, rwx..) */
	ग_लिखो_aux_reg(ARC_REG_TLBPD1, pd1);

	/*
	 * Commit the Entry to MMU
	 * It करोesn't sound safe to use the TLBWriteNI cmd here
	 * which करोesn't flush uTLBs. I'd rather be safe than sorry.
	 */
	ग_लिखो_aux_reg(ARC_REG_TLBCOMMAND, TLBWrite);
पूर्ण

#अन्यथा	/* CONFIG_ARC_MMU_VER >= 4) */

अटल व्योम tlb_entry_erase(अचिन्हित पूर्णांक vaddr_n_asid)
अणु
	ग_लिखो_aux_reg(ARC_REG_TLBPD0, vaddr_n_asid | _PAGE_PRESENT);
	ग_लिखो_aux_reg(ARC_REG_TLBCOMMAND, TLBDeleteEntry);
पूर्ण

अटल व्योम tlb_entry_insert(अचिन्हित पूर्णांक pd0, pte_t pd1)
अणु
	ग_लिखो_aux_reg(ARC_REG_TLBPD0, pd0);
	ग_लिखो_aux_reg(ARC_REG_TLBPD1, pd1);

	अगर (is_pae40_enabled())
		ग_लिखो_aux_reg(ARC_REG_TLBPD1HI, (u64)pd1 >> 32);

	ग_लिखो_aux_reg(ARC_REG_TLBCOMMAND, TLBInsertEntry);
पूर्ण

#पूर्ण_अगर

/*
 * Un-conditionally (without lookup) erase the entire MMU contents
 */

noअंतरभूत व्योम local_flush_tlb_all(व्योम)
अणु
	काष्ठा cpuinfo_arc_mmu *mmu = &cpuinfo_arc700[smp_processor_id()].mmu;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक entry;
	पूर्णांक num_tlb = mmu->sets * mmu->ways;

	local_irq_save(flags);

	/* Load PD0 and PD1 with ढाँचा क्रम a Blank Entry */
	ग_लिखो_aux_reg(ARC_REG_TLBPD1, 0);

	अगर (is_pae40_enabled())
		ग_लिखो_aux_reg(ARC_REG_TLBPD1HI, 0);

	ग_लिखो_aux_reg(ARC_REG_TLBPD0, 0);

	क्रम (entry = 0; entry < num_tlb; entry++) अणु
		/* ग_लिखो this entry to the TLB */
		ग_लिखो_aux_reg(ARC_REG_TLBINDEX, entry);
		ग_लिखो_aux_reg(ARC_REG_TLBCOMMAND, TLBWriteNI);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE)) अणु
		स्थिर पूर्णांक stlb_idx = 0x800;

		/* Blank sTLB entry */
		ग_लिखो_aux_reg(ARC_REG_TLBPD0, _PAGE_HW_SZ);

		क्रम (entry = stlb_idx; entry < stlb_idx + 16; entry++) अणु
			ग_लिखो_aux_reg(ARC_REG_TLBINDEX, entry);
			ग_लिखो_aux_reg(ARC_REG_TLBCOMMAND, TLBWriteNI);
		पूर्ण
	पूर्ण

	utlb_invalidate();

	local_irq_restore(flags);
पूर्ण

/*
 * Flush the entire MM क्रम userland. The fastest way is to move to Next ASID
 */
noअंतरभूत व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * Small optimisation courtesy IA64
	 * flush_mm called during विभाजन,निकास,munmap etc, multiple बार as well.
	 * Only क्रम विभाजन( ) करो we need to move parent to a new MMU ctxt,
	 * all other हालs are NOPs, hence this check.
	 */
	अगर (atomic_पढ़ो(&mm->mm_users) == 0)
		वापस;

	/*
	 * - Move to a new ASID, but only अगर the mm is still wired in
	 *   (Android Binder ended up calling this क्रम vma->mm != tsk->mm,
	 *    causing h/w - s/w ASID to get out of sync)
	 * - Also get_new_mmu_context() new implementation allocates a new
	 *   ASID only अगर it is not allocated alपढ़ोy - so unallocate first
	 */
	destroy_context(mm);
	अगर (current->mm == mm)
		get_new_mmu_context(mm);
पूर्ण

/*
 * Flush a Range of TLB entries क्रम userland.
 * @start is inclusive, जबतक @end is exclusive
 * Dअगरference between this and Kernel Range Flush is
 *  -Here the fastest way (अगर range is too large) is to move to next ASID
 *      without करोing any explicit Shootकरोwn
 *  -In हाल of kernel Flush, entry has to be shot करोwn explicitly
 */
व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ end)
अणु
	स्थिर अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ flags;

	/* If range @start to @end is more than 32 TLB entries deep,
	 * its better to move to a new ASID rather than searching क्रम
	 * inभागidual entries and then shooting them करोwn
	 *
	 * The calc above is rough, करोesn't account क्रम unaligned parts,
	 * since this is heuristics based anyways
	 */
	अगर (unlikely((end - start) >= PAGE_SIZE * 32)) अणु
		local_flush_tlb_mm(vma->vm_mm);
		वापस;
	पूर्ण

	/*
	 * @start moved to page start: this alone suffices क्रम checking
	 * loop end condition below, w/o need क्रम aligning @end to end
	 * e.g. 2000 to 4001 will anyhow loop twice
	 */
	start &= PAGE_MASK;

	local_irq_save(flags);

	अगर (asid_mm(vma->vm_mm, cpu) != MM_CTXT_NO_ASID) अणु
		जबतक (start < end) अणु
			tlb_entry_erase(start | hw_pid(vma->vm_mm, cpu));
			start += PAGE_SIZE;
		पूर्ण
	पूर्ण

	local_irq_restore(flags);
पूर्ण

/* Flush the kernel TLB entries - vदो_स्मृति/modules (Global from MMU perspective)
 *  @start, @end पूर्णांकerpreted as kvaddr
 * Interestingly, shared TLB entries can also be flushed using just
 * @start,@end alone (पूर्णांकerpreted as user vaddr), although technically SASID
 * is also needed. However our smart TLbProbe lookup takes care of that.
 */
व्योम local_flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ flags;

	/* exactly same as above, except क्रम TLB entry not taking ASID */

	अगर (unlikely((end - start) >= PAGE_SIZE * 32)) अणु
		local_flush_tlb_all();
		वापस;
	पूर्ण

	start &= PAGE_MASK;

	local_irq_save(flags);
	जबतक (start < end) अणु
		tlb_entry_erase(start);
		start += PAGE_SIZE;
	पूर्ण

	local_irq_restore(flags);
पूर्ण

/*
 * Delete TLB entry in MMU क्रम a given page (??? address)
 * NOTE One TLB entry contains translation क्रम single PAGE
 */

व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	स्थिर अचिन्हित पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ flags;

	/* Note that it is critical that पूर्णांकerrupts are DISABLED between
	 * checking the ASID and using it flush the TLB entry
	 */
	local_irq_save(flags);

	अगर (asid_mm(vma->vm_mm, cpu) != MM_CTXT_NO_ASID) अणु
		tlb_entry_erase((page & PAGE_MASK) | hw_pid(vma->vm_mm, cpu));
	पूर्ण

	local_irq_restore(flags);
पूर्ण

#अगर_घोषित CONFIG_SMP

काष्ठा tlb_args अणु
	काष्ठा vm_area_काष्ठा *ta_vma;
	अचिन्हित दीर्घ ta_start;
	अचिन्हित दीर्घ ta_end;
पूर्ण;

अटल अंतरभूत व्योम ipi_flush_tlb_page(व्योम *arg)
अणु
	काष्ठा tlb_args *ta = arg;

	local_flush_tlb_page(ta->ta_vma, ta->ta_start);
पूर्ण

अटल अंतरभूत व्योम ipi_flush_tlb_range(व्योम *arg)
अणु
	काष्ठा tlb_args *ta = arg;

	local_flush_tlb_range(ta->ta_vma, ta->ta_start, ta->ta_end);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत व्योम ipi_flush_pmd_tlb_range(व्योम *arg)
अणु
	काष्ठा tlb_args *ta = arg;

	local_flush_pmd_tlb_range(ta->ta_vma, ta->ta_start, ta->ta_end);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम ipi_flush_tlb_kernel_range(व्योम *arg)
अणु
	काष्ठा tlb_args *ta = (काष्ठा tlb_args *)arg;

	local_flush_tlb_kernel_range(ta->ta_start, ta->ta_end);
पूर्ण

व्योम flush_tlb_all(व्योम)
अणु
	on_each_cpu((smp_call_func_t)local_flush_tlb_all, शून्य, 1);
पूर्ण

व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	on_each_cpu_mask(mm_cpumask(mm), (smp_call_func_t)local_flush_tlb_mm,
			 mm, 1);
पूर्ण

व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ uaddr)
अणु
	काष्ठा tlb_args ta = अणु
		.ta_vma = vma,
		.ta_start = uaddr
	पूर्ण;

	on_each_cpu_mask(mm_cpumask(vma->vm_mm), ipi_flush_tlb_page, &ta, 1);
पूर्ण

व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		     अचिन्हित दीर्घ end)
अणु
	काष्ठा tlb_args ta = अणु
		.ta_vma = vma,
		.ta_start = start,
		.ta_end = end
	पूर्ण;

	on_each_cpu_mask(mm_cpumask(vma->vm_mm), ipi_flush_tlb_range, &ta, 1);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
व्योम flush_pmd_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			 अचिन्हित दीर्घ end)
अणु
	काष्ठा tlb_args ta = अणु
		.ta_vma = vma,
		.ta_start = start,
		.ta_end = end
	पूर्ण;

	on_each_cpu_mask(mm_cpumask(vma->vm_mm), ipi_flush_pmd_tlb_range, &ta, 1);
पूर्ण
#पूर्ण_अगर

व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा tlb_args ta = अणु
		.ta_start = start,
		.ta_end = end
	पूर्ण;

	on_each_cpu(ipi_flush_tlb_kernel_range, &ta, 1);
पूर्ण
#पूर्ण_अगर

/*
 * Routine to create a TLB entry
 */
व्योम create_tlb(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vaddr, pte_t *ptep)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक asid_or_sasid, rwx;
	अचिन्हित दीर्घ pd0;
	pte_t pd1;

	/*
	 * create_tlb() assumes that current->mm == vma->mm, since
	 * -it ASID क्रम TLB entry is fetched from MMU ASID reg (valid क्रम curr)
	 * -completes the lazy ग_लिखो to SASID reg (again valid क्रम curr tsk)
	 *
	 * Removing the assumption involves
	 * -Using vma->mm->contextअणुASID,SASIDपूर्ण, as opposed to MMU reg.
	 * -Fix the TLB paranoid debug code to not trigger false negatives.
	 * -More importantly it makes this handler inconsistent with fast-path
	 *  TLB Refill handler which always deals with "current"
	 *
	 * Lets see the use हालs when current->mm != vma->mm and we land here
	 *  1. execve->copy_strings()->__get_user_pages->handle_mm_fault
	 *     Here VM wants to pre-install a TLB entry क्रम user stack जबतक
	 *     current->mm still poपूर्णांकs to pre-execve mm (hence the condition).
	 *     However the stack vaddr is soon relocated (अक्रमomization) and
	 *     move_page_tables() tries to unकरो that TLB entry.
	 *     Thus not creating TLB entry is not any worse.
	 *
	 *  2. ptrace(POKETEXT) causes a CoW - debugger(current) inserting a
	 *     अवरोधpoपूर्णांक in debugged task. Not creating a TLB now is not
	 *     perक्रमmance critical.
	 *
	 * Both the हालs above are not good enough क्रम code churn.
	 */
	अगर (current->active_mm != vma->vm_mm)
		वापस;

	local_irq_save(flags);

	tlb_paranoid_check(asid_mm(vma->vm_mm, smp_processor_id()), vaddr);

	vaddr &= PAGE_MASK;

	/* update this PTE credentials */
	pte_val(*ptep) |= (_PAGE_PRESENT | _PAGE_ACCESSED);

	/* Create HW TLB(PD0,PD1) from PTE  */

	/* ASID क्रम this task */
	asid_or_sasid = पढ़ो_aux_reg(ARC_REG_PID) & 0xff;

	pd0 = vaddr | asid_or_sasid | (pte_val(*ptep) & PTE_BITS_IN_PD0);

	/*
	 * ARC MMU provides fully orthogonal access bits क्रम K/U mode,
	 * however Linux only saves 1 set to save PTE real-estate
	 * Here we convert 3 PTE bits पूर्णांकo 6 MMU bits:
	 * -Kernel only entries have Kr Kw Kx 0 0 0
	 * -User entries have mirrored K and U bits
	 */
	rwx = pte_val(*ptep) & PTE_BITS_RWX;

	अगर (pte_val(*ptep) & _PAGE_GLOBAL)
		rwx <<= 3;		/* r w x => Kr Kw Kx 0 0 0 */
	अन्यथा
		rwx |= (rwx << 3);	/* r w x => Kr Kw Kx Ur Uw Ux */

	pd1 = rwx | (pte_val(*ptep) & PTE_BITS_NON_RWX_IN_PD1);

	tlb_entry_insert(pd0, pd1);

	local_irq_restore(flags);
पूर्ण

/*
 * Called at the end of pagefault, क्रम a userspace mapped page
 *  -pre-install the corresponding TLB entry पूर्णांकo MMU
 *  -Finalize the delayed D-cache flush of kernel mapping of page due to
 *  	flush_dcache_page(), copy_user_page()
 *
 * Note that flush (when करोne) involves both WBACK - so physical page is
 * in sync as well as INV - so any non-congruent aliases करोn't reमुख्य
 */
व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vaddr_unaligned,
		      pte_t *ptep)
अणु
	अचिन्हित दीर्घ vaddr = vaddr_unaligned & PAGE_MASK;
	phys_addr_t paddr = pte_val(*ptep) & PAGE_MASK_PHYS;
	काष्ठा page *page = pfn_to_page(pte_pfn(*ptep));

	create_tlb(vma, vaddr, ptep);

	अगर (page == ZERO_PAGE(0)) अणु
		वापस;
	पूर्ण

	/*
	 * Exec page : Independent of aliasing/page-color considerations,
	 *	       since icache करोesn't snoop dcache on ARC, any dirty
	 *	       K-mapping of a code page needs to be wback+inv so that
	 *	       icache fetch by userspace sees code correctly.
	 * !EXEC page: If K-mapping is NOT congruent to U-mapping, flush it
	 *	       so userspace sees the right data.
	 *  (Aव्योमs the flush क्रम Non-exec + congruent mapping हाल)
	 */
	अगर ((vma->vm_flags & VM_EXEC) ||
	     addr_not_cache_congruent(paddr, vaddr)) अणु

		पूर्णांक dirty = !test_and_set_bit(PG_dc_clean, &page->flags);
		अगर (dirty) अणु
			/* wback + inv dcache lines (K-mapping) */
			__flush_dcache_page(paddr, paddr);

			/* invalidate any existing icache lines (U-mapping) */
			अगर (vma->vm_flags & VM_EXEC)
				__inv_icache_page(paddr, vaddr);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE

/*
 * MMUv4 in HS38x cores supports Super Pages which are basis क्रम Linux THP
 * support.
 *
 * Normal and Super pages can co-exist (ofcourse not overlap) in TLB with a
 * new bit "SZ" in TLB page descriptor to distinguish between them.
 * Super Page size is configurable in hardware (4K to 16M), but fixed once
 * RTL builds.
 *
 * The exact THP size a Linux configuration will support is a function of:
 *  - MMU page size (typical 8K, RTL fixed)
 *  - software page walker address split between PGD:PTE:PFN (typical
 *    11:8:13, but can be changed with 1 line)
 * So क्रम above शेष, THP size supported is 8K * (2^8) = 2M
 *
 * Default Page Walker is 2 levels, PGD:PTE:PFN, which in THP regime
 * reduces to 1 level (as PTE is folded पूर्णांकo PGD and canonically referred
 * to as PMD).
 * Thus THP PMD accessors are implemented in terms of PTE (just like sparc)
 */

व्योम update_mmu_cache_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
				 pmd_t *pmd)
अणु
	pte_t pte = __pte(pmd_val(*pmd));
	update_mmu_cache(vma, addr, &pte);
पूर्ण

व्योम pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				pgtable_t pgtable)
अणु
	काष्ठा list_head *lh = (काष्ठा list_head *) pgtable;

	निश्चित_spin_locked(&mm->page_table_lock);

	/* FIFO */
	अगर (!pmd_huge_pte(mm, pmdp))
		INIT_LIST_HEAD(lh);
	अन्यथा
		list_add(lh, (काष्ठा list_head *) pmd_huge_pte(mm, pmdp));
	pmd_huge_pte(mm, pmdp) = pgtable;
पूर्ण

pgtable_t pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp)
अणु
	काष्ठा list_head *lh;
	pgtable_t pgtable;

	निश्चित_spin_locked(&mm->page_table_lock);

	pgtable = pmd_huge_pte(mm, pmdp);
	lh = (काष्ठा list_head *) pgtable;
	अगर (list_empty(lh))
		pmd_huge_pte(mm, pmdp) = शून्य;
	अन्यथा अणु
		pmd_huge_pte(mm, pmdp) = (pgtable_t) lh->next;
		list_del(lh);
	पूर्ण

	pte_val(pgtable[0]) = 0;
	pte_val(pgtable[1]) = 0;

	वापस pgtable;
पूर्ण

व्योम local_flush_pmd_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			       अचिन्हित दीर्घ end)
अणु
	अचिन्हित पूर्णांक cpu;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	cpu = smp_processor_id();

	अगर (likely(asid_mm(vma->vm_mm, cpu) != MM_CTXT_NO_ASID)) अणु
		अचिन्हित पूर्णांक asid = hw_pid(vma->vm_mm, cpu);

		/* No need to loop here: this will always be क्रम 1 Huge Page */
		tlb_entry_erase(start | _PAGE_HW_SZ | asid);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

#पूर्ण_अगर

/* Read the Cache Build Configuration Registers, Decode them and save पूर्णांकo
 * the cpuinfo काष्ठाure क्रम later use.
 * No Validation is करोne here, simply पढ़ो/convert the BCRs
 */
व्योम पढ़ो_decode_mmu_bcr(व्योम)
अणु
	काष्ठा cpuinfo_arc_mmu *mmu = &cpuinfo_arc700[smp_processor_id()].mmu;
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा bcr_mmu_1_2 अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
		अचिन्हित पूर्णांक ver:8, ways:4, sets:4, u_itlb:8, u_dtlb:8;
#अन्यथा
		अचिन्हित पूर्णांक u_dtlb:8, u_itlb:8, sets:4, ways:4, ver:8;
#पूर्ण_अगर
	पूर्ण *mmu2;

	काष्ठा bcr_mmu_3 अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक ver:8, ways:4, sets:4, res:3, sasid:1, pg_sz:4,
		     u_itlb:4, u_dtlb:4;
#अन्यथा
	अचिन्हित पूर्णांक u_dtlb:4, u_itlb:4, pg_sz:4, sasid:1, res:3, sets:4,
		     ways:4, ver:8;
#पूर्ण_अगर
	पूर्ण *mmu3;

	काष्ठा bcr_mmu_4 अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक ver:8, sasid:1, sz1:4, sz0:4, res:2, pae:1,
		     n_ways:2, n_entry:2, n_super:2, u_itlb:3, u_dtlb:3;
#अन्यथा
	/*           DTLB      ITLB      JES        JE         JA      */
	अचिन्हित पूर्णांक u_dtlb:3, u_itlb:3, n_super:2, n_entry:2, n_ways:2,
		     pae:1, res:2, sz0:4, sz1:4, sasid:1, ver:8;
#पूर्ण_अगर
	पूर्ण *mmu4;

	पंचांगp = पढ़ो_aux_reg(ARC_REG_MMU_BCR);
	mmu->ver = (पंचांगp >> 24);

	अगर (is_isa_arcompact()) अणु
		अगर (mmu->ver <= 2) अणु
			mmu2 = (काष्ठा bcr_mmu_1_2 *)&पंचांगp;
			mmu->pg_sz_k = TO_KB(0x2000);
			mmu->sets = 1 << mmu2->sets;
			mmu->ways = 1 << mmu2->ways;
			mmu->u_dtlb = mmu2->u_dtlb;
			mmu->u_itlb = mmu2->u_itlb;
		पूर्ण अन्यथा अणु
			mmu3 = (काष्ठा bcr_mmu_3 *)&पंचांगp;
			mmu->pg_sz_k = 1 << (mmu3->pg_sz - 1);
			mmu->sets = 1 << mmu3->sets;
			mmu->ways = 1 << mmu3->ways;
			mmu->u_dtlb = mmu3->u_dtlb;
			mmu->u_itlb = mmu3->u_itlb;
			mmu->sasid = mmu3->sasid;
		पूर्ण
	पूर्ण अन्यथा अणु
		mmu4 = (काष्ठा bcr_mmu_4 *)&पंचांगp;
		mmu->pg_sz_k = 1 << (mmu4->sz0 - 1);
		mmu->s_pg_sz_m = 1 << (mmu4->sz1 - 11);
		mmu->sets = 64 << mmu4->n_entry;
		mmu->ways = mmu4->n_ways * 2;
		mmu->u_dtlb = mmu4->u_dtlb * 4;
		mmu->u_itlb = mmu4->u_itlb * 4;
		mmu->sasid = mmu4->sasid;
		pae_exists = mmu->pae = mmu4->pae;
	पूर्ण
पूर्ण

अक्षर *arc_mmu_mumbojumbo(पूर्णांक cpu_id, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक n = 0;
	काष्ठा cpuinfo_arc_mmu *p_mmu = &cpuinfo_arc700[cpu_id].mmu;
	अक्षर super_pg[64] = "";

	अगर (p_mmu->s_pg_sz_m)
		scnम_लिखो(super_pg, 64, "%dM Super Page %s",
			  p_mmu->s_pg_sz_m,
			  IS_USED_CFG(CONFIG_TRANSPARENT_HUGEPAGE));

	n += scnम_लिखो(buf + n, len - n,
		      "MMU [v%x]\t: %dk PAGE, %sJTLB %d (%dx%d), uDTLB %d, uITLB %d%s%s\n",
		       p_mmu->ver, p_mmu->pg_sz_k, super_pg,
		       p_mmu->sets * p_mmu->ways, p_mmu->sets, p_mmu->ways,
		       p_mmu->u_dtlb, p_mmu->u_itlb,
		       IS_AVAIL2(p_mmu->pae, ", PAE40 ", CONFIG_ARC_HAS_PAE40));

	वापस buf;
पूर्ण

पूर्णांक pae40_exist_but_not_enab(व्योम)
अणु
	वापस pae_exists && !is_pae40_enabled();
पूर्ण

व्योम arc_mmu_init(व्योम)
अणु
	काष्ठा cpuinfo_arc_mmu *mmu = &cpuinfo_arc700[smp_processor_id()].mmu;
	अक्षर str[256];
	पूर्णांक compat = 0;

	pr_info("%s", arc_mmu_mumbojumbo(0, str, माप(str)));

	/*
	 * Can't be करोne in processor.h due to header include dependencies
	 */
	BUILD_BUG_ON(!IS_ALIGNED((CONFIG_ARC_KVADDR_SIZE << 20), PMD_SIZE));

	/*
	 * stack top size sanity check,
	 * Can't be करोne in processor.h due to header include dependencies
	 */
	BUILD_BUG_ON(!IS_ALIGNED(STACK_TOP, PMD_SIZE));

	/*
	 * Ensure that MMU features assumed by kernel exist in hardware.
	 * For older ARC700 cpus, it has to be exact match, since the MMU
	 * revisions were not backwards compatible (MMUv3 TLB layout changed
	 * so even अगर kernel क्रम v2 didn't use any new cmds of v3, it would
	 * still not work.
	 * For HS cpus, MMUv4 was baseline and v5 is backwards compatible
	 * (will run older software).
	 */
	अगर (is_isa_arcompact() && mmu->ver == CONFIG_ARC_MMU_VER)
		compat = 1;
	अन्यथा अगर (is_isa_arcv2() && mmu->ver >= CONFIG_ARC_MMU_VER)
		compat = 1;

	अगर (!compat) अणु
		panic("MMU ver %d doesn't match kernel built for %d...\n",
		      mmu->ver, CONFIG_ARC_MMU_VER);
	पूर्ण

	अगर (mmu->pg_sz_k != TO_KB(PAGE_SIZE))
		panic("MMU pg size != PAGE_SIZE (%luk)\n", TO_KB(PAGE_SIZE));

	अगर (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE) &&
	    mmu->s_pg_sz_m != TO_MB(HPAGE_PMD_SIZE))
		panic("MMU Super pg size != Linux HPAGE_PMD_SIZE (%luM)\n",
		      (अचिन्हित दीर्घ)TO_MB(HPAGE_PMD_SIZE));

	अगर (IS_ENABLED(CONFIG_ARC_HAS_PAE40) && !mmu->pae)
		panic("Hardware doesn't support PAE40\n");

	/* Enable the MMU */
	ग_लिखो_aux_reg(ARC_REG_PID, MMU_ENABLE);

	/* In smp we use this reg क्रम पूर्णांकerrupt 1 scratch */
#अगर_घोषित ARC_USE_SCRATCH_REG
	/* swapper_pg_dir is the pgd क्रम the kernel, used by vदो_स्मृति */
	ग_लिखो_aux_reg(ARC_REG_SCRATCH_DATA0, swapper_pg_dir);
#पूर्ण_अगर

	अगर (pae40_exist_but_not_enab())
		ग_लिखो_aux_reg(ARC_REG_TLBPD1HI, 0);
पूर्ण

/*
 * TLB Programmer's Model uses Linear Indexes: 0 to अणु255, 511पूर्ण क्रम 128 x अणु2,4पूर्ण
 * The mapping is Column-first.
 *		---------------------	-----------
 *		|way0|way1|way2|way3|	|way0|way1|
 *		---------------------	-----------
 * [set0]	|  0 |  1 |  2 |  3 |	|  0 |  1 |
 * [set1]	|  4 |  5 |  6 |  7 |	|  2 |  3 |
 *		~		    ~	~	  ~
 * [set127]	| 508| 509| 510| 511|	| 254| 255|
 *		---------------------	-----------
 * For normal operations we करोn't(must not) care how above works since
 * MMU cmd getIndex(vaddr) असलtracts that out.
 * However क्रम walking WAYS of a SET, we need to know this
 */
#घोषणा SET_WAY_TO_IDX(mmu, set, way)  ((set) * mmu->ways + (way))

/* Handling of Duplicate PD (TLB entry) in MMU.
 * -Could be due to buggy customer tapeouts or obscure kernel bugs
 * -MMU complaपूर्णांकs not at the समय of duplicate PD installation, but at the
 *      समय of lookup matching multiple ways.
 * -Ideally these should never happen - but अगर they करो - workaround by deleting
 *      the duplicate one.
 * -Knob to be verbose abt it.(TODO: hook them up to debugfs)
 */
अस्थिर पूर्णांक dup_pd_silent; /* Be silent abt it or complain (शेष) */

व्योम करो_tlb_overlap_fault(अचिन्हित दीर्घ cause, अचिन्हित दीर्घ address,
			  काष्ठा pt_regs *regs)
अणु
	काष्ठा cpuinfo_arc_mmu *mmu = &cpuinfo_arc700[smp_processor_id()].mmu;
	अचिन्हित दीर्घ flags;
	पूर्णांक set, n_ways = mmu->ways;

	n_ways = min(n_ways, 4);
	BUG_ON(mmu->ways > 4);

	local_irq_save(flags);

	/* loop thru all sets of TLB */
	क्रम (set = 0; set < mmu->sets; set++) अणु

		पूर्णांक is_valid, way;
		अचिन्हित पूर्णांक pd0[4];

		/* पढ़ो out all the ways of current set */
		क्रम (way = 0, is_valid = 0; way < n_ways; way++) अणु
			ग_लिखो_aux_reg(ARC_REG_TLBINDEX,
					  SET_WAY_TO_IDX(mmu, set, way));
			ग_लिखो_aux_reg(ARC_REG_TLBCOMMAND, TLBRead);
			pd0[way] = पढ़ो_aux_reg(ARC_REG_TLBPD0);
			is_valid |= pd0[way] & _PAGE_PRESENT;
			pd0[way] &= PAGE_MASK;
		पूर्ण

		/* If all the WAYS in SET are empty, skip to next SET */
		अगर (!is_valid)
			जारी;

		/* Scan the set क्रम duplicate ways: needs a nested loop */
		क्रम (way = 0; way < n_ways - 1; way++) अणु

			पूर्णांक n;

			अगर (!pd0[way])
				जारी;

			क्रम (n = way + 1; n < n_ways; n++) अणु
				अगर (pd0[way] != pd0[n])
					जारी;

				अगर (!dup_pd_silent)
					pr_info("Dup TLB PD0 %08x @ set %d ways %d,%d\n",
						pd0[way], set, way, n);

				/*
				 * clear entry @way and not @n.
				 * This is critical to our optimised loop
				 */
				pd0[way] = 0;
				ग_लिखो_aux_reg(ARC_REG_TLBINDEX,
						SET_WAY_TO_IDX(mmu, set, way));
				__tlb_entry_erase();
			पूर्ण
		पूर्ण
	पूर्ण

	local_irq_restore(flags);
पूर्ण

/***********************************************************************
 * Diagnostic Routines
 *  -Called from Low Level TLB Handlers अगर things करोn;t look good
 **********************************************************************/

#अगर_घोषित CONFIG_ARC_DBG_TLB_PARANOIA

/*
 * Low Level ASM TLB handler calls this अगर it finds that HW and SW ASIDS
 * करोn't match
 */
व्योम prपूर्णांक_asid_mismatch(पूर्णांक mm_asid, पूर्णांक mmu_asid, पूर्णांक is_fast_path)
अणु
	pr_emerg("ASID Mismatch in %s Path Handler: sw-pid=0x%x hw-pid=0x%x\n",
	       is_fast_path ? "Fast" : "Slow", mm_asid, mmu_asid);

	__यंत्र__ __अस्थिर__("flag 1");
पूर्ण

व्योम tlb_paranoid_check(अचिन्हित पूर्णांक mm_asid, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित पूर्णांक mmu_asid;

	mmu_asid = पढ़ो_aux_reg(ARC_REG_PID) & 0xff;

	/*
	 * At the समय of a TLB miss/installation
	 *   - HW version needs to match SW version
	 *   - SW needs to have a valid ASID
	 */
	अगर (addr < 0x70000000 &&
	    ((mm_asid == MM_CTXT_NO_ASID) ||
	      (mmu_asid != (mm_asid & MM_CTXT_ASID_MASK))))
		prपूर्णांक_asid_mismatch(mm_asid, mmu_asid, 0);
पूर्ण
#पूर्ण_अगर
