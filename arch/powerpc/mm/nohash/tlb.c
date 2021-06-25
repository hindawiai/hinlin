<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains the routines क्रम TLB flushing.
 * On machines where the MMU करोes not use a hash table to store भव to
 * physical translations (ie, SW loaded TLBs or Book3E compilant processors,
 * this करोes -not- include 603 however which shares the implementation with
 * hash based processors)
 *
 *  -- BenH
 *
 * Copyright 2008,2009 Ben Herrenschmidt <benh@kernel.crashing.org>
 *                     IBM Corp.
 *
 *  Derived from arch/ppc/mm/init.c:
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/preempt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/hugetlb.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/hugetlb.h>
#समावेश <यंत्र/paca.h>

#समावेश <mm/mmu_decl.h>

/*
 * This काष्ठा lists the sw-supported page sizes.  The hardawre MMU may support
 * other sizes not listed here.   The .ind field is only used on MMUs that have
 * indirect page table entries.
 */
#अगर defined(CONFIG_PPC_BOOK3E_MMU) || defined(CONFIG_PPC_8xx)
#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
काष्ठा mmu_psize_def mmu_psize_defs[MMU_PAGE_COUNT] = अणु
	[MMU_PAGE_4K] = अणु
		.shअगरt	= 12,
		.enc	= BOOK3E_PAGESZ_4K,
	पूर्ण,
	[MMU_PAGE_2M] = अणु
		.shअगरt	= 21,
		.enc	= BOOK3E_PAGESZ_2M,
	पूर्ण,
	[MMU_PAGE_4M] = अणु
		.shअगरt	= 22,
		.enc	= BOOK3E_PAGESZ_4M,
	पूर्ण,
	[MMU_PAGE_16M] = अणु
		.shअगरt	= 24,
		.enc	= BOOK3E_PAGESZ_16M,
	पूर्ण,
	[MMU_PAGE_64M] = अणु
		.shअगरt	= 26,
		.enc	= BOOK3E_PAGESZ_64M,
	पूर्ण,
	[MMU_PAGE_256M] = अणु
		.shअगरt	= 28,
		.enc	= BOOK3E_PAGESZ_256M,
	पूर्ण,
	[MMU_PAGE_1G] = अणु
		.shअगरt	= 30,
		.enc	= BOOK3E_PAGESZ_1GB,
	पूर्ण,
पूर्ण;
#या_अगर defined(CONFIG_PPC_8xx)
काष्ठा mmu_psize_def mmu_psize_defs[MMU_PAGE_COUNT] = अणु
	[MMU_PAGE_4K] = अणु
		.shअगरt	= 12,
	पूर्ण,
	[MMU_PAGE_16K] = अणु
		.shअगरt	= 14,
	पूर्ण,
	[MMU_PAGE_512K] = अणु
		.shअगरt	= 19,
	पूर्ण,
	[MMU_PAGE_8M] = अणु
		.shअगरt	= 23,
	पूर्ण,
पूर्ण;
#अन्यथा
काष्ठा mmu_psize_def mmu_psize_defs[MMU_PAGE_COUNT] = अणु
	[MMU_PAGE_4K] = अणु
		.shअगरt	= 12,
		.ind	= 20,
		.enc	= BOOK3E_PAGESZ_4K,
	पूर्ण,
	[MMU_PAGE_16K] = अणु
		.shअगरt	= 14,
		.enc	= BOOK3E_PAGESZ_16K,
	पूर्ण,
	[MMU_PAGE_64K] = अणु
		.shअगरt	= 16,
		.ind	= 28,
		.enc	= BOOK3E_PAGESZ_64K,
	पूर्ण,
	[MMU_PAGE_1M] = अणु
		.shअगरt	= 20,
		.enc	= BOOK3E_PAGESZ_1M,
	पूर्ण,
	[MMU_PAGE_16M] = अणु
		.shअगरt	= 24,
		.ind	= 36,
		.enc	= BOOK3E_PAGESZ_16M,
	पूर्ण,
	[MMU_PAGE_256M] = अणु
		.shअगरt	= 28,
		.enc	= BOOK3E_PAGESZ_256M,
	पूर्ण,
	[MMU_PAGE_1G] = अणु
		.shअगरt	= 30,
		.enc	= BOOK3E_PAGESZ_1GB,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_FSL_BOOKE */

अटल अंतरभूत पूर्णांक mmu_get_tsize(पूर्णांक psize)
अणु
	वापस mmu_psize_defs[psize].enc;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक mmu_get_tsize(पूर्णांक psize)
अणु
	/* This isn't used on !Book3E क्रम now */
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_BOOK3E_MMU */

/* The variables below are currently only used on 64-bit Book3E
 * though this will probably be made common with other nohash
 * implementations at some poपूर्णांक
 */
#अगर_घोषित CONFIG_PPC64

पूर्णांक mmu_linear_psize;		/* Page size used क्रम the linear mapping */
पूर्णांक mmu_pte_psize;		/* Page size used क्रम PTE pages */
पूर्णांक mmu_vmemmap_psize;		/* Page size used क्रम the भव mem map */
पूर्णांक book3e_htw_mode;		/* HW tablewalk?  Value is PPC_HTW_* */
अचिन्हित दीर्घ linear_map_top;	/* Top of linear mapping */


/*
 * Number of bytes to add to SPRN_SPRG_TLB_EXFRAME on crit/mcheck/debug
 * exceptions.  This is used क्रम bolted and e6500 TLB miss handlers which
 * करो not modअगरy this SPRG in the TLB miss code; क्रम other TLB miss handlers,
 * this is set to zero.
 */
पूर्णांक extlb_level_exc;

#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
/* next_tlbcam_idx is used to round-robin tlbcam entry assignment */
DEFINE_PER_CPU(पूर्णांक, next_tlbcam_idx);
EXPORT_PER_CPU_SYMBOL(next_tlbcam_idx);
#पूर्ण_अगर

/*
 * Base TLB flushing operations:
 *
 *  - flush_tlb_mm(mm) flushes the specअगरied mm context TLB's
 *  - flush_tlb_page(vma, vmaddr) flushes one page
 *  - flush_tlb_range(vma, start, end) flushes a range of pages
 *  - flush_tlb_kernel_range(start, end) flushes kernel pages
 *
 *  - local_* variants of page and mm only apply to the current
 *    processor
 */

/*
 * These are the base non-SMP variants of page and mm flushing
 */
व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित पूर्णांक pid;

	preempt_disable();
	pid = mm->context.id;
	अगर (pid != MMU_NO_CONTEXT)
		_tlbil_pid(pid);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(local_flush_tlb_mm);

व्योम __local_flush_tlb_page(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr,
			    पूर्णांक tsize, पूर्णांक ind)
अणु
	अचिन्हित पूर्णांक pid;

	preempt_disable();
	pid = mm ? mm->context.id : 0;
	अगर (pid != MMU_NO_CONTEXT)
		_tlbil_va(vmaddr, pid, tsize, ind);
	preempt_enable();
पूर्ण

व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr)
अणु
	__local_flush_tlb_page(vma ? vma->vm_mm : शून्य, vmaddr,
			       mmu_get_tsize(mmu_भव_psize), 0);
पूर्ण
EXPORT_SYMBOL(local_flush_tlb_page);

/*
 * And here are the SMP non-local implementations
 */
#अगर_घोषित CONFIG_SMP

अटल DEFINE_RAW_SPINLOCK(tlbivax_lock);

काष्ठा tlb_flush_param अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक pid;
	अचिन्हित पूर्णांक tsize;
	अचिन्हित पूर्णांक ind;
पूर्ण;

अटल व्योम करो_flush_tlb_mm_ipi(व्योम *param)
अणु
	काष्ठा tlb_flush_param *p = param;

	_tlbil_pid(p ? p->pid : 0);
पूर्ण

अटल व्योम करो_flush_tlb_page_ipi(व्योम *param)
अणु
	काष्ठा tlb_flush_param *p = param;

	_tlbil_va(p->addr, p->pid, p->tsize, p->ind);
पूर्ण


/* Note on invalidations and PID:
 *
 * We snapshot the PID with preempt disabled. At this poपूर्णांक, it can still
 * change either because:
 * - our context is being stolen (PID -> NO_CONTEXT) on another CPU
 * - we are invaliating some target that isn't currently running here
 *   and is concurrently acquiring a new PID on another CPU
 * - some other CPU is re-acquiring a lost PID क्रम this mm
 * etc...
 *
 * However, this shouldn't be a problem as we only guarantee
 * invalidation of TLB entries present prior to this call, so we
 * करोn't care about the PID changing, and invalidating a stale PID
 * is generally harmless.
 */

व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित पूर्णांक pid;

	preempt_disable();
	pid = mm->context.id;
	अगर (unlikely(pid == MMU_NO_CONTEXT))
		जाओ no_context;
	अगर (!mm_is_core_local(mm)) अणु
		काष्ठा tlb_flush_param p = अणु .pid = pid पूर्ण;
		/* Ignores smp_processor_id() even अगर set. */
		smp_call_function_many(mm_cpumask(mm),
				       करो_flush_tlb_mm_ipi, &p, 1);
	पूर्ण
	_tlbil_pid(pid);
 no_context:
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(flush_tlb_mm);

व्योम __flush_tlb_page(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr,
		      पूर्णांक tsize, पूर्णांक ind)
अणु
	काष्ठा cpumask *cpu_mask;
	अचिन्हित पूर्णांक pid;

	/*
	 * This function as well as __local_flush_tlb_page() must only be called
	 * क्रम user contexts.
	 */
	अगर (WARN_ON(!mm))
		वापस;

	preempt_disable();
	pid = mm->context.id;
	अगर (unlikely(pid == MMU_NO_CONTEXT))
		जाओ bail;
	cpu_mask = mm_cpumask(mm);
	अगर (!mm_is_core_local(mm)) अणु
		/* If broadcast tlbivax is supported, use it */
		अगर (mmu_has_feature(MMU_FTR_USE_TLBIVAX_BCAST)) अणु
			पूर्णांक lock = mmu_has_feature(MMU_FTR_LOCK_BCAST_INVAL);
			अगर (lock)
				raw_spin_lock(&tlbivax_lock);
			_tlbivax_bcast(vmaddr, pid, tsize, ind);
			अगर (lock)
				raw_spin_unlock(&tlbivax_lock);
			जाओ bail;
		पूर्ण अन्यथा अणु
			काष्ठा tlb_flush_param p = अणु
				.pid = pid,
				.addr = vmaddr,
				.tsize = tsize,
				.ind = ind,
			पूर्ण;
			/* Ignores smp_processor_id() even अगर set in cpu_mask */
			smp_call_function_many(cpu_mask,
					       करो_flush_tlb_page_ipi, &p, 1);
		पूर्ण
	पूर्ण
	_tlbil_va(vmaddr, pid, tsize, ind);
 bail:
	preempt_enable();
पूर्ण

व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr)
अणु
#अगर_घोषित CONFIG_HUGETLB_PAGE
	अगर (vma && is_vm_hugetlb_page(vma))
		flush_hugetlb_page(vma, vmaddr);
#पूर्ण_अगर

	__flush_tlb_page(vma ? vma->vm_mm : शून्य, vmaddr,
			 mmu_get_tsize(mmu_भव_psize), 0);
पूर्ण
EXPORT_SYMBOL(flush_tlb_page);

#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_PPC_47x
व्योम __init early_init_mmu_47x(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ root = of_get_flat_dt_root();
	अगर (of_get_flat_dt_prop(root, "cooperative-partition", शून्य))
		mmu_clear_feature(MMU_FTR_USE_TLBIVAX_BCAST);
#पूर्ण_अगर /* CONFIG_SMP */
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_47x */

/*
 * Flush kernel TLB entries in the given range
 */
व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
#अगर_घोषित CONFIG_SMP
	preempt_disable();
	smp_call_function(करो_flush_tlb_mm_ipi, शून्य, 1);
	_tlbil_pid(0);
	preempt_enable();
#अन्यथा
	_tlbil_pid(0);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(flush_tlb_kernel_range);

/*
 * Currently, क्रम range flushing, we just करो a full mm flush. This should
 * be optimized based on a threshold on the size of the range, since
 * some implementation can stack multiple tlbivax beक्रमe a tlbsync but
 * क्रम now, we keep it that way
 */
व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		     अचिन्हित दीर्घ end)

अणु
	अगर (end - start == PAGE_SIZE && !(start & ~PAGE_MASK))
		flush_tlb_page(vma, start);
	अन्यथा
		flush_tlb_mm(vma->vm_mm);
पूर्ण
EXPORT_SYMBOL(flush_tlb_range);

व्योम tlb_flush(काष्ठा mmu_gather *tlb)
अणु
	flush_tlb_mm(tlb->mm);
पूर्ण

/*
 * Below are functions specअगरic to the 64-bit variant of Book3E though that
 * may change in the future
 */

#अगर_घोषित CONFIG_PPC64

/*
 * Handling of भव linear page tables or indirect TLB entries
 * flushing when PTE pages are मुक्तd
 */
व्योम tlb_flush_pgtable(काष्ठा mmu_gather *tlb, अचिन्हित दीर्घ address)
अणु
	पूर्णांक tsize = mmu_psize_defs[mmu_pte_psize].enc;

	अगर (book3e_htw_mode != PPC_HTW_NONE) अणु
		अचिन्हित दीर्घ start = address & PMD_MASK;
		अचिन्हित दीर्घ end = address + PMD_SIZE;
		अचिन्हित दीर्घ size = 1UL << mmu_psize_defs[mmu_pte_psize].shअगरt;

		/* This isn't the most optimal, ideally we would factor out the
		 * जबतक preempt & CPU mask mucking around, or even the IPI but
		 * it will करो क्रम now
		 */
		जबतक (start < end) अणु
			__flush_tlb_page(tlb->mm, start, tsize, 1);
			start += size;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ rmask = 0xf000000000000000ul;
		अचिन्हित दीर्घ rid = (address & rmask) | 0x1000000000000000ul;
		अचिन्हित दीर्घ vpte = address & ~rmask;

		vpte = (vpte >> (PAGE_SHIFT - 3)) & ~0xffful;
		vpte |= rid;
		__flush_tlb_page(tlb->mm, vpte, tsize, 0);
	पूर्ण
पूर्ण

अटल व्योम setup_page_sizes(व्योम)
अणु
	अचिन्हित पूर्णांक tlb0cfg;
	अचिन्हित पूर्णांक tlb0ps;
	अचिन्हित पूर्णांक eptcfg;
	पूर्णांक i, psize;

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
	अचिन्हित पूर्णांक mmucfg = mfspr(SPRN_MMUCFG);
	पूर्णांक fsl_mmu = mmu_has_feature(MMU_FTR_TYPE_FSL_E);

	अगर (fsl_mmu && (mmucfg & MMUCFG_MAVN) == MMUCFG_MAVN_V1) अणु
		अचिन्हित पूर्णांक tlb1cfg = mfspr(SPRN_TLB1CFG);
		अचिन्हित पूर्णांक min_pg, max_pg;

		min_pg = (tlb1cfg & TLBnCFG_MINSIZE) >> TLBnCFG_MINSIZE_SHIFT;
		max_pg = (tlb1cfg & TLBnCFG_MAXSIZE) >> TLBnCFG_MAXSIZE_SHIFT;

		क्रम (psize = 0; psize < MMU_PAGE_COUNT; ++psize) अणु
			काष्ठा mmu_psize_def *def;
			अचिन्हित पूर्णांक shअगरt;

			def = &mmu_psize_defs[psize];
			shअगरt = def->shअगरt;

			अगर (shअगरt == 0 || shअगरt & 1)
				जारी;

			/* adjust to be in terms of 4^shअगरt Kb */
			shअगरt = (shअगरt - 10) >> 1;

			अगर ((shअगरt >= min_pg) && (shअगरt <= max_pg))
				def->flags |= MMU_PAGE_SIZE_सूचीECT;
		पूर्ण

		जाओ out;
	पूर्ण

	अगर (fsl_mmu && (mmucfg & MMUCFG_MAVN) == MMUCFG_MAVN_V2) अणु
		u32 tlb1cfg, tlb1ps;

		tlb0cfg = mfspr(SPRN_TLB0CFG);
		tlb1cfg = mfspr(SPRN_TLB1CFG);
		tlb1ps = mfspr(SPRN_TLB1PS);
		eptcfg = mfspr(SPRN_EPTCFG);

		अगर ((tlb1cfg & TLBnCFG_IND) && (tlb0cfg & TLBnCFG_PT))
			book3e_htw_mode = PPC_HTW_E6500;

		/*
		 * We expect 4K subpage size and unrestricted indirect size.
		 * The lack of a restriction on indirect size is a Freescale
		 * extension, indicated by PSn = 0 but SPSn != 0.
		 */
		अगर (eptcfg != 2)
			book3e_htw_mode = PPC_HTW_NONE;

		क्रम (psize = 0; psize < MMU_PAGE_COUNT; ++psize) अणु
			काष्ठा mmu_psize_def *def = &mmu_psize_defs[psize];

			अगर (!def->shअगरt)
				जारी;

			अगर (tlb1ps & (1U << (def->shअगरt - 10))) अणु
				def->flags |= MMU_PAGE_SIZE_सूचीECT;

				अगर (book3e_htw_mode && psize == MMU_PAGE_2M)
					def->flags |= MMU_PAGE_SIZE_INसूचीECT;
			पूर्ण
		पूर्ण

		जाओ out;
	पूर्ण
#पूर्ण_अगर

	tlb0cfg = mfspr(SPRN_TLB0CFG);
	tlb0ps = mfspr(SPRN_TLB0PS);
	eptcfg = mfspr(SPRN_EPTCFG);

	/* Look क्रम supported direct sizes */
	क्रम (psize = 0; psize < MMU_PAGE_COUNT; ++psize) अणु
		काष्ठा mmu_psize_def *def = &mmu_psize_defs[psize];

		अगर (tlb0ps & (1U << (def->shअगरt - 10)))
			def->flags |= MMU_PAGE_SIZE_सूचीECT;
	पूर्ण

	/* Indirect page sizes supported ? */
	अगर ((tlb0cfg & TLBnCFG_IND) == 0 ||
	    (tlb0cfg & TLBnCFG_PT) == 0)
		जाओ out;

	book3e_htw_mode = PPC_HTW_IBM;

	/* Now, we only deal with one IND page size क्रम each
	 * direct size. Hopefully all implementations today are
	 * unambiguous, but we might want to be careful in the
	 * future.
	 */
	क्रम (i = 0; i < 3; i++) अणु
		अचिन्हित पूर्णांक ps, sps;

		sps = eptcfg & 0x1f;
		eptcfg >>= 5;
		ps = eptcfg & 0x1f;
		eptcfg >>= 5;
		अगर (!ps || !sps)
			जारी;
		क्रम (psize = 0; psize < MMU_PAGE_COUNT; psize++) अणु
			काष्ठा mmu_psize_def *def = &mmu_psize_defs[psize];

			अगर (ps == (def->shअगरt - 10))
				def->flags |= MMU_PAGE_SIZE_INसूचीECT;
			अगर (sps == (def->shअगरt - 10))
				def->ind = ps + 10;
		पूर्ण
	पूर्ण

out:
	/* Cleanup array and prपूर्णांक summary */
	pr_info("MMU: Supported page sizes\n");
	क्रम (psize = 0; psize < MMU_PAGE_COUNT; ++psize) अणु
		काष्ठा mmu_psize_def *def = &mmu_psize_defs[psize];
		स्थिर अक्षर *__page_type_names[] = अणु
			"unsupported",
			"direct",
			"indirect",
			"direct & indirect"
		पूर्ण;
		अगर (def->flags == 0) अणु
			def->shअगरt = 0;	
			जारी;
		पूर्ण
		pr_info("  %8ld KB as %s\n", 1ul << (def->shअगरt - 10),
			__page_type_names[def->flags & 0x3]);
	पूर्ण
पूर्ण

अटल व्योम setup_mmu_htw(व्योम)
अणु
	/*
	 * If we want to use HW tablewalk, enable it by patching the TLB miss
	 * handlers to branch to the one dedicated to it.
	 */

	चयन (book3e_htw_mode) अणु
	हाल PPC_HTW_IBM:
		patch_exception(0x1c0, exc_data_tlb_miss_htw_book3e);
		patch_exception(0x1e0, exc_inकाष्ठाion_tlb_miss_htw_book3e);
		अवरोध;
#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
	हाल PPC_HTW_E6500:
		extlb_level_exc = EX_TLB_SIZE;
		patch_exception(0x1c0, exc_data_tlb_miss_e6500_book3e);
		patch_exception(0x1e0, exc_inकाष्ठाion_tlb_miss_e6500_book3e);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
	pr_info("MMU: Book3E HW tablewalk %s\n",
		book3e_htw_mode != PPC_HTW_NONE ? "enabled" : "not supported");
पूर्ण

/*
 * Early initialization of the MMU TLB code
 */
अटल व्योम early_init_this_mmu(व्योम)
अणु
	अचिन्हित पूर्णांक mas4;

	/* Set MAS4 based on page table setting */

	mas4 = 0x4 << MAS4_WIMGED_SHIFT;
	चयन (book3e_htw_mode) अणु
	हाल PPC_HTW_E6500:
		mas4 |= MAS4_INDD;
		mas4 |= BOOK3E_PAGESZ_2M << MAS4_TSIZED_SHIFT;
		mas4 |= MAS4_TLBSELD(1);
		mmu_pte_psize = MMU_PAGE_2M;
		अवरोध;

	हाल PPC_HTW_IBM:
		mas4 |= MAS4_INDD;
		mas4 |=	BOOK3E_PAGESZ_1M << MAS4_TSIZED_SHIFT;
		mmu_pte_psize = MMU_PAGE_1M;
		अवरोध;

	हाल PPC_HTW_NONE:
		mas4 |=	BOOK3E_PAGESZ_4K << MAS4_TSIZED_SHIFT;
		mmu_pte_psize = mmu_भव_psize;
		अवरोध;
	पूर्ण
	mtspr(SPRN_MAS4, mas4);

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
	अगर (mmu_has_feature(MMU_FTR_TYPE_FSL_E)) अणु
		अचिन्हित पूर्णांक num_cams;
		bool map = true;

		/* use a quarter of the TLBCAM क्रम bolted linear map */
		num_cams = (mfspr(SPRN_TLB1CFG) & TLBnCFG_N_ENTRY) / 4;

		/*
		 * Only करो the mapping once per core, or अन्यथा the
		 * transient mapping would cause problems.
		 */
#अगर_घोषित CONFIG_SMP
		अगर (hweight32(get_tensr()) > 1)
			map = false;
#पूर्ण_अगर

		अगर (map)
			linear_map_top = map_mem_in_cams(linear_map_top,
							 num_cams, false);
	पूर्ण
#पूर्ण_अगर

	/* A sync won't hurt us after mucking around with
	 * the MMU configuration
	 */
	mb();
पूर्ण

अटल व्योम __init early_init_mmu_global(व्योम)
अणु
	/* XXX This will have to be decided at runसमय, but right
	 * now our boot and TLB miss code hard wires it. Ideally
	 * we should find out a suitable page size and patch the
	 * TLB miss code (either that or use the PACA to store
	 * the value we want)
	 */
	mmu_linear_psize = MMU_PAGE_1G;

	/* XXX This should be decided at runसमय based on supported
	 * page sizes in the TLB, but क्रम now let's assume 16M is
	 * always there and a good fit (which it probably is)
	 *
	 * Freescale booke only supports 4K pages in TLB0, so use that.
	 */
	अगर (mmu_has_feature(MMU_FTR_TYPE_FSL_E))
		mmu_vmemmap_psize = MMU_PAGE_4K;
	अन्यथा
		mmu_vmemmap_psize = MMU_PAGE_16M;

	/* XXX This code only checks क्रम TLB 0 capabilities and करोesn't
	 *     check what page size combos are supported by the HW. It
	 *     also करोesn't handle the हाल where a separate array holds
	 *     the IND entries from the array loaded by the PT.
	 */
	/* Look क्रम supported page sizes */
	setup_page_sizes();

	/* Look क्रम HW tablewalk support */
	setup_mmu_htw();

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
	अगर (mmu_has_feature(MMU_FTR_TYPE_FSL_E)) अणु
		अगर (book3e_htw_mode == PPC_HTW_NONE) अणु
			extlb_level_exc = EX_TLB_SIZE;
			patch_exception(0x1c0, exc_data_tlb_miss_bolted_book3e);
			patch_exception(0x1e0,
				exc_inकाष्ठाion_tlb_miss_bolted_book3e);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Set the global containing the top of the linear mapping
	 * क्रम use by the TLB miss code
	 */
	linear_map_top = memblock_end_of_DRAM();

	ioremap_bot = IOREMAP_BASE;
पूर्ण

अटल व्योम __init early_mmu_set_memory_limit(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
	अगर (mmu_has_feature(MMU_FTR_TYPE_FSL_E)) अणु
		/*
		 * Limit memory so we करोnt have linear faults.
		 * Unlike memblock_set_current_limit, which limits
		 * memory available during early boot, this permanently
		 * reduces the memory available to Linux.  We need to
		 * करो this because highmem is not supported on 64-bit.
		 */
		memblock_enक्रमce_memory_limit(linear_map_top);
	पूर्ण
#पूर्ण_अगर

	memblock_set_current_limit(linear_map_top);
पूर्ण

/* boot cpu only */
व्योम __init early_init_mmu(व्योम)
अणु
	early_init_mmu_global();
	early_init_this_mmu();
	early_mmu_set_memory_limit();
पूर्ण

व्योम early_init_mmu_secondary(व्योम)
अणु
	early_init_this_mmu();
पूर्ण

व्योम setup_initial_memory_limit(phys_addr_t first_memblock_base,
				phys_addr_t first_memblock_size)
अणु
	/* On non-FSL Embedded 64-bit, we adjust the RMA size to match
	 * the bolted TLB entry. We know क्रम now that only 1G
	 * entries are supported though that may eventually
	 * change.
	 *
	 * on FSL Embedded 64-bit, usually all RAM is bolted, but with
	 * unusual memory sizes it's possible क्रम some RAM to not be mapped
	 * (such RAM is not used at all by Linux, since we करोn't support
	 * highmem on 64-bit).  We limit ppc64_rma_size to what would be
	 * mappable अगर this memblock is the only one.  Additional memblocks
	 * can only increase, not decrease, the amount that ends up getting
	 * mapped.  We still limit max to 1G even अगर we'll eventually map
	 * more.  This is due to what the early init code is set up to करो.
	 *
	 * We crop it to the size of the first MEMBLOCK to
	 * aव्योम going over total available memory just in हाल...
	 */
#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
	अगर (early_mmu_has_feature(MMU_FTR_TYPE_FSL_E)) अणु
		अचिन्हित दीर्घ linear_sz;
		अचिन्हित पूर्णांक num_cams;

		/* use a quarter of the TLBCAM क्रम bolted linear map */
		num_cams = (mfspr(SPRN_TLB1CFG) & TLBnCFG_N_ENTRY) / 4;

		linear_sz = map_mem_in_cams(first_memblock_size, num_cams,
					    true);

		ppc64_rma_size = min_t(u64, linear_sz, 0x40000000);
	पूर्ण अन्यथा
#पूर्ण_अगर
		ppc64_rma_size = min_t(u64, first_memblock_size, 0x40000000);

	/* Finally limit subsequent allocations */
	memblock_set_current_limit(first_memblock_base + ppc64_rma_size);
पूर्ण
#अन्यथा /* ! CONFIG_PPC64 */
व्योम __init early_init_mmu(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_47x
	early_init_mmu_47x();
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_MM_SLICES
	mm_ctx_set_slb_addr_limit(&init_mm.context, SLB_ADDR_LIMIT_DEFAULT);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */
