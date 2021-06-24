<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/mm/memory.c
 *
 *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 */

/*
 * demand-loading started 01.12.91 - seems it is high on the list of
 * things wanted, and it should be easy to implement. - Linus
 */

/*
 * Ok, demand-loading was easy, shared pages a little bit tricker. Shared
 * pages started 02.12.91, seems to work. - Linus.
 *
 * Tested sharing by executing about 30 /bin/sh: under the old kernel it
 * would have taken more than the 6M I have मुक्त, but it worked well as
 * far as I could see.
 *
 * Also corrected some "invalidate()"s - I wasn't करोing enough of them.
 */

/*
 * Real VM (paging to/from disk) started 18.12.91. Much more work and
 * thought has to go पूर्णांकo this. Oh, well..
 * 19.12.91  -  works, somewhat. Someबार I get faults, करोn't know why.
 *		Found it. Everything seems to work now.
 * 20.12.91  -  Ok, making the swap-device changeable like the root.
 */

/*
 * 05.04.94  -  Multi-page memory management added क्रम v1.1.
 *              Idea by Alex Bligh (alex@cconcepts.co.uk)
 *
 * 16.07.99  -  Support of BIGMEM added by Gerhard Wichert, Siemens AG
 *		(Gerhard.Wichert@pdb.siemens.de)
 *
 * Aug/Sep 2004 Changed to four level page tables (Andi Kleen)
 */

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/numa_balancing.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/mman.h>
#समावेश <linux/swap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/memremap.h>
#समावेश <linux/ksm.h>
#समावेश <linux/rmap.h>
#समावेश <linux/export.h>
#समावेश <linux/delayacct.h>
#समावेश <linux/init.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/swapops.h>
#समावेश <linux/elf.h>
#समावेश <linux/gfp.h>
#समावेश <linux/migrate.h>
#समावेश <linux/माला.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/userfaultfd_k.h>
#समावेश <linux/dax.h>
#समावेश <linux/oom.h>
#समावेश <linux/numa.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <trace/events/kस्मृति.स>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "pgalloc-track.h"
#समावेश "internal.h"

#अगर defined(LAST_CPUPID_NOT_IN_PAGE_FLAGS) && !defined(CONFIG_COMPILE_TEST)
#warning Unक्रमtunate NUMA and NUMA Balancing config, growing page-frame क्रम last_cpupid.
#पूर्ण_अगर

#अगर_अघोषित CONFIG_NEED_MULTIPLE_NODES
/* use the per-pgdat data instead क्रम discontigmem - mbligh */
अचिन्हित दीर्घ max_mapnr;
EXPORT_SYMBOL(max_mapnr);

काष्ठा page *mem_map;
EXPORT_SYMBOL(mem_map);
#पूर्ण_अगर

/*
 * A number of key प्रणालीs in x86 including ioremap() rely on the assumption
 * that high_memory defines the upper bound on direct map memory, then end
 * of ZONE_NORMAL.  Under CONFIG_DISCONTIG this means that max_low_pfn and
 * highstart_pfn must be the same; there must be no gap between ZONE_NORMAL
 * and ZONE_HIGHMEM.
 */
व्योम *high_memory;
EXPORT_SYMBOL(high_memory);

/*
 * Ranकरोmize the address space (stacks, mmaps, brk, etc.).
 *
 * ( When CONFIG_COMPAT_BRK=y we exclude brk from अक्रमomization,
 *   as ancient (libc5 based) binaries can segfault. )
 */
पूर्णांक अक्रमomize_va_space __पढ़ो_mostly =
#अगर_घोषित CONFIG_COMPAT_BRK
					1;
#अन्यथा
					2;
#पूर्ण_अगर

#अगर_अघोषित arch_faults_on_old_pte
अटल अंतरभूत bool arch_faults_on_old_pte(व्योम)
अणु
	/*
	 * Those arches which करोn't have hw access flag feature need to
	 * implement their own helper. By शेष, "true" means pagefault
	 * will be hit on old pte.
	 */
	वापस true;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_wants_old_prefaulted_pte
अटल अंतरभूत bool arch_wants_old_prefaulted_pte(व्योम)
अणु
	/*
	 * Transitioning a PTE from 'old' to 'young' can be expensive on
	 * some architectures, even अगर it's perक्रमmed in hardware. By
	 * शेष, "false" means prefaulted entries will be 'young'.
	 */
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init disable_अक्रमmaps(अक्षर *s)
अणु
	अक्रमomize_va_space = 0;
	वापस 1;
पूर्ण
__setup("norandmaps", disable_अक्रमmaps);

अचिन्हित दीर्घ zero_pfn __पढ़ो_mostly;
EXPORT_SYMBOL(zero_pfn);

अचिन्हित दीर्घ highest_memmap_pfn __पढ़ो_mostly;

/*
 * CONFIG_MMU architectures set up ZERO_PAGE in their paging_init()
 */
अटल पूर्णांक __init init_zero_pfn(व्योम)
अणु
	zero_pfn = page_to_pfn(ZERO_PAGE(0));
	वापस 0;
पूर्ण
early_initcall(init_zero_pfn);

व्योम mm_trace_rss_stat(काष्ठा mm_काष्ठा *mm, पूर्णांक member, दीर्घ count)
अणु
	trace_rss_stat(mm, member, count);
पूर्ण

#अगर defined(SPLIT_RSS_COUNTING)

व्योम sync_mm_rss(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_MM_COUNTERS; i++) अणु
		अगर (current->rss_stat.count[i]) अणु
			add_mm_counter(mm, i, current->rss_stat.count[i]);
			current->rss_stat.count[i] = 0;
		पूर्ण
	पूर्ण
	current->rss_stat.events = 0;
पूर्ण

अटल व्योम add_mm_counter_fast(काष्ठा mm_काष्ठा *mm, पूर्णांक member, पूर्णांक val)
अणु
	काष्ठा task_काष्ठा *task = current;

	अगर (likely(task->mm == mm))
		task->rss_stat.count[member] += val;
	अन्यथा
		add_mm_counter(mm, member, val);
पूर्ण
#घोषणा inc_mm_counter_fast(mm, member) add_mm_counter_fast(mm, member, 1)
#घोषणा dec_mm_counter_fast(mm, member) add_mm_counter_fast(mm, member, -1)

/* sync counter once per 64 page faults */
#घोषणा TASK_RSS_EVENTS_THRESH	(64)
अटल व्योम check_sync_rss_stat(काष्ठा task_काष्ठा *task)
अणु
	अगर (unlikely(task != current))
		वापस;
	अगर (unlikely(task->rss_stat.events++ > TASK_RSS_EVENTS_THRESH))
		sync_mm_rss(task->mm);
पूर्ण
#अन्यथा /* SPLIT_RSS_COUNTING */

#घोषणा inc_mm_counter_fast(mm, member) inc_mm_counter(mm, member)
#घोषणा dec_mm_counter_fast(mm, member) dec_mm_counter(mm, member)

अटल व्योम check_sync_rss_stat(काष्ठा task_काष्ठा *task)
अणु
पूर्ण

#पूर्ण_अगर /* SPLIT_RSS_COUNTING */

/*
 * Note: this करोesn't मुक्त the actual pages themselves. That
 * has been handled earlier when unmapping all the memory regions.
 */
अटल व्योम मुक्त_pte_range(काष्ठा mmu_gather *tlb, pmd_t *pmd,
			   अचिन्हित दीर्घ addr)
अणु
	pgtable_t token = pmd_pgtable(*pmd);
	pmd_clear(pmd);
	pte_मुक्त_tlb(tlb, token, addr);
	mm_dec_nr_ptes(tlb->mm);
पूर्ण

अटल अंतरभूत व्योम मुक्त_pmd_range(काष्ठा mmu_gather *tlb, pud_t *pud,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ start;

	start = addr;
	pmd = pmd_offset(pud, addr);
	करो अणु
		next = pmd_addr_end(addr, end);
		अगर (pmd_none_or_clear_bad(pmd))
			जारी;
		मुक्त_pte_range(tlb, pmd, addr);
	पूर्ण जबतक (pmd++, addr = next, addr != end);

	start &= PUD_MASK;
	अगर (start < न्यूनमान)
		वापस;
	अगर (उच्चमानing) अणु
		उच्चमानing &= PUD_MASK;
		अगर (!उच्चमानing)
			वापस;
	पूर्ण
	अगर (end - 1 > उच्चमानing - 1)
		वापस;

	pmd = pmd_offset(pud, start);
	pud_clear(pud);
	pmd_मुक्त_tlb(tlb, pmd, start);
	mm_dec_nr_pmds(tlb->mm);
पूर्ण

अटल अंतरभूत व्योम मुक्त_pud_range(काष्ठा mmu_gather *tlb, p4d_t *p4d,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ start;

	start = addr;
	pud = pud_offset(p4d, addr);
	करो अणु
		next = pud_addr_end(addr, end);
		अगर (pud_none_or_clear_bad(pud))
			जारी;
		मुक्त_pmd_range(tlb, pud, addr, next, न्यूनमान, उच्चमानing);
	पूर्ण जबतक (pud++, addr = next, addr != end);

	start &= P4D_MASK;
	अगर (start < न्यूनमान)
		वापस;
	अगर (उच्चमानing) अणु
		उच्चमानing &= P4D_MASK;
		अगर (!उच्चमानing)
			वापस;
	पूर्ण
	अगर (end - 1 > उच्चमानing - 1)
		वापस;

	pud = pud_offset(p4d, start);
	p4d_clear(p4d);
	pud_मुक्त_tlb(tlb, pud, start);
	mm_dec_nr_puds(tlb->mm);
पूर्ण

अटल अंतरभूत व्योम मुक्त_p4d_range(काष्ठा mmu_gather *tlb, pgd_t *pgd,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	p4d_t *p4d;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ start;

	start = addr;
	p4d = p4d_offset(pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (p4d_none_or_clear_bad(p4d))
			जारी;
		मुक्त_pud_range(tlb, p4d, addr, next, न्यूनमान, उच्चमानing);
	पूर्ण जबतक (p4d++, addr = next, addr != end);

	start &= PGसूची_MASK;
	अगर (start < न्यूनमान)
		वापस;
	अगर (उच्चमानing) अणु
		उच्चमानing &= PGसूची_MASK;
		अगर (!उच्चमानing)
			वापस;
	पूर्ण
	अगर (end - 1 > उच्चमानing - 1)
		वापस;

	p4d = p4d_offset(pgd, start);
	pgd_clear(pgd);
	p4d_मुक्त_tlb(tlb, p4d, start);
पूर्ण

/*
 * This function मुक्तs user-level page tables of a process.
 */
व्योम मुक्त_pgd_range(काष्ठा mmu_gather *tlb,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	pgd_t *pgd;
	अचिन्हित दीर्घ next;

	/*
	 * The next few lines have given us lots of grief...
	 *
	 * Why are we testing PMD* at this top level?  Because often
	 * there will be no work to करो at all, and we'd prefer not to
	 * go all the way करोwn to the bottom just to discover that.
	 *
	 * Why all these "- 1"s?  Because 0 represents both the bottom
	 * of the address space and the top of it (using -1 क्रम the
	 * top wouldn't help much: the masks would करो the wrong thing).
	 * The rule is that addr 0 and न्यूनमान 0 refer to the bottom of
	 * the address space, but end 0 and उच्चमानing 0 refer to the top
	 * Comparisons need to use "end - 1" and "ceiling - 1" (though
	 * that end 0 हाल should be mythical).
	 *
	 * Wherever addr is brought up or उच्चमानing brought करोwn, we must
	 * be careful to reject "the opposite 0" beक्रमe it confuses the
	 * subsequent tests.  But what about where end is brought करोwn
	 * by PMD_SIZE below? no, end can't go करोwn to 0 there.
	 *
	 * Whereas we round start (addr) and उच्चमानing करोwn, by dअगरferent
	 * masks at dअगरferent levels, in order to test whether a table
	 * now has no other vmas using it, so can be मुक्तd, we करोn't
	 * bother to round न्यूनमान or end up - the tests करोn't need that.
	 */

	addr &= PMD_MASK;
	अगर (addr < न्यूनमान) अणु
		addr += PMD_SIZE;
		अगर (!addr)
			वापस;
	पूर्ण
	अगर (उच्चमानing) अणु
		उच्चमानing &= PMD_MASK;
		अगर (!उच्चमानing)
			वापस;
	पूर्ण
	अगर (end - 1 > उच्चमानing - 1)
		end -= PMD_SIZE;
	अगर (addr > end - 1)
		वापस;
	/*
	 * We add page table cache pages with PAGE_SIZE,
	 * (see pte_मुक्त_tlb()), flush the tlb अगर we need
	 */
	tlb_change_page_size(tlb, PAGE_SIZE);
	pgd = pgd_offset(tlb->mm, addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		अगर (pgd_none_or_clear_bad(pgd))
			जारी;
		मुक्त_p4d_range(tlb, pgd, addr, next, न्यूनमान, उच्चमानing);
	पूर्ण जबतक (pgd++, addr = next, addr != end);
पूर्ण

व्योम मुक्त_pgtables(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	जबतक (vma) अणु
		काष्ठा vm_area_काष्ठा *next = vma->vm_next;
		अचिन्हित दीर्घ addr = vma->vm_start;

		/*
		 * Hide vma from rmap and truncate_pagecache beक्रमe मुक्तing
		 * pgtables
		 */
		unlink_anon_vmas(vma);
		unlink_file_vma(vma);

		अगर (is_vm_hugetlb_page(vma)) अणु
			hugetlb_मुक्त_pgd_range(tlb, addr, vma->vm_end,
				न्यूनमान, next ? next->vm_start : उच्चमानing);
		पूर्ण अन्यथा अणु
			/*
			 * Optimization: gather nearby vmas पूर्णांकo one call करोwn
			 */
			जबतक (next && next->vm_start <= vma->vm_end + PMD_SIZE
			       && !is_vm_hugetlb_page(next)) अणु
				vma = next;
				next = vma->vm_next;
				unlink_anon_vmas(vma);
				unlink_file_vma(vma);
			पूर्ण
			मुक्त_pgd_range(tlb, addr, vma->vm_end,
				न्यूनमान, next ? next->vm_start : उच्चमानing);
		पूर्ण
		vma = next;
	पूर्ण
पूर्ण

पूर्णांक __pte_alloc(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	spinlock_t *ptl;
	pgtable_t new = pte_alloc_one(mm);
	अगर (!new)
		वापस -ENOMEM;

	/*
	 * Ensure all pte setup (eg. pte page lock and page clearing) are
	 * visible beक्रमe the pte is made visible to other CPUs by being
	 * put पूर्णांकo page tables.
	 *
	 * The other side of the story is the poपूर्णांकer chasing in the page
	 * table walking code (when walking the page table without locking;
	 * ie. most of the समय). Fortunately, these data accesses consist
	 * of a chain of data-dependent loads, meaning most CPUs (alpha
	 * being the notable exception) will alपढ़ोy guarantee loads are
	 * seen in-order. See the alpha page table accessors क्रम the
	 * smp_rmb() barriers in page table walking code.
	 */
	smp_wmb(); /* Could be smp_wmb__xxx(beक्रमe|after)_spin_lock */

	ptl = pmd_lock(mm, pmd);
	अगर (likely(pmd_none(*pmd))) अणु	/* Has another populated it ? */
		mm_inc_nr_ptes(mm);
		pmd_populate(mm, pmd, new);
		new = शून्य;
	पूर्ण
	spin_unlock(ptl);
	अगर (new)
		pte_मुक्त(mm, new);
	वापस 0;
पूर्ण

पूर्णांक __pte_alloc_kernel(pmd_t *pmd)
अणु
	pte_t *new = pte_alloc_one_kernel(&init_mm);
	अगर (!new)
		वापस -ENOMEM;

	smp_wmb(); /* See comment in __pte_alloc */

	spin_lock(&init_mm.page_table_lock);
	अगर (likely(pmd_none(*pmd))) अणु	/* Has another populated it ? */
		pmd_populate_kernel(&init_mm, pmd, new);
		new = शून्य;
	पूर्ण
	spin_unlock(&init_mm.page_table_lock);
	अगर (new)
		pte_मुक्त_kernel(&init_mm, new);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम init_rss_vec(पूर्णांक *rss)
अणु
	स_रखो(rss, 0, माप(पूर्णांक) * NR_MM_COUNTERS);
पूर्ण

अटल अंतरभूत व्योम add_mm_rss_vec(काष्ठा mm_काष्ठा *mm, पूर्णांक *rss)
अणु
	पूर्णांक i;

	अगर (current->mm == mm)
		sync_mm_rss(mm);
	क्रम (i = 0; i < NR_MM_COUNTERS; i++)
		अगर (rss[i])
			add_mm_counter(mm, i, rss[i]);
पूर्ण

/*
 * This function is called to prपूर्णांक an error when a bad pte
 * is found. For example, we might have a PFN-mapped pte in
 * a region that करोesn't allow it.
 *
 * The calling function must still handle the error.
 */
अटल व्योम prपूर्णांक_bad_pte(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			  pte_t pte, काष्ठा page *page)
अणु
	pgd_t *pgd = pgd_offset(vma->vm_mm, addr);
	p4d_t *p4d = p4d_offset(pgd, addr);
	pud_t *pud = pud_offset(p4d, addr);
	pmd_t *pmd = pmd_offset(pud, addr);
	काष्ठा address_space *mapping;
	pgoff_t index;
	अटल अचिन्हित दीर्घ resume;
	अटल अचिन्हित दीर्घ nr_shown;
	अटल अचिन्हित दीर्घ nr_unshown;

	/*
	 * Allow a burst of 60 reports, then keep quiet क्रम that minute;
	 * or allow a steady drip of one report per second.
	 */
	अगर (nr_shown == 60) अणु
		अगर (समय_beक्रमe(jअगरfies, resume)) अणु
			nr_unshown++;
			वापस;
		पूर्ण
		अगर (nr_unshown) अणु
			pr_alert("BUG: Bad page map: %lu messages suppressed\n",
				 nr_unshown);
			nr_unshown = 0;
		पूर्ण
		nr_shown = 0;
	पूर्ण
	अगर (nr_shown++ == 0)
		resume = jअगरfies + 60 * HZ;

	mapping = vma->vm_file ? vma->vm_file->f_mapping : शून्य;
	index = linear_page_index(vma, addr);

	pr_alert("BUG: Bad page map in process %s  pte:%08llx pmd:%08llx\n",
		 current->comm,
		 (दीर्घ दीर्घ)pte_val(pte), (दीर्घ दीर्घ)pmd_val(*pmd));
	अगर (page)
		dump_page(page, "bad pte");
	pr_alert("addr:%px vm_flags:%08lx anon_vma:%px mapping:%px index:%lx\n",
		 (व्योम *)addr, vma->vm_flags, vma->anon_vma, mapping, index);
	pr_alert("file:%pD fault:%ps mmap:%ps readpage:%ps\n",
		 vma->vm_file,
		 vma->vm_ops ? vma->vm_ops->fault : शून्य,
		 vma->vm_file ? vma->vm_file->f_op->mmap : शून्य,
		 mapping ? mapping->a_ops->पढ़ोpage : शून्य);
	dump_stack();
	add_taपूर्णांक(TAINT_BAD_PAGE, LOCKDEP_NOW_UNRELIABLE);
पूर्ण

/*
 * vm_normal_page -- This function माला_लो the "struct page" associated with a pte.
 *
 * "Special" mappings करो not wish to be associated with a "struct page" (either
 * it करोesn't exist, or it exists but they don't want to touch it). In this
 * हाल, शून्य is वापसed here. "Normal" mappings करो have a काष्ठा page.
 *
 * There are 2 broad हालs. Firstly, an architecture may define a pte_special()
 * pte bit, in which हाल this function is trivial. Secondly, an architecture
 * may not have a spare pte bit, which requires a more complicated scheme,
 * described below.
 *
 * A raw VM_PFNMAP mapping (ie. one that is not COWed) is always considered a
 * special mapping (even अगर there are underlying and valid "struct pages").
 * COWed pages of a VM_PFNMAP are always normal.
 *
 * The way we recognize COWed pages within VM_PFNMAP mappings is through the
 * rules set up by "remap_pfn_range()": the vma will have the VM_PFNMAP bit
 * set, and the vm_pgoff will poपूर्णांक to the first PFN mapped: thus every special
 * mapping will always honor the rule
 *
 *	pfn_of_page == vma->vm_pgoff + ((addr - vma->vm_start) >> PAGE_SHIFT)
 *
 * And क्रम normal mappings this is false.
 *
 * This restricts such mappings to be a linear translation from भव address
 * to pfn. To get around this restriction, we allow arbitrary mappings so दीर्घ
 * as the vma is not a COW mapping; in that हाल, we know that all ptes are
 * special (because none can have been COWed).
 *
 *
 * In order to support COW of arbitrary special mappings, we have VM_MIXEDMAP.
 *
 * VM_MIXEDMAP mappings can likewise contain memory with or without "काष्ठा
 * page" backing, however the dअगरference is that _all_ pages with a काष्ठा
 * page (that is, those where pfn_valid is true) are refcounted and considered
 * normal pages by the VM. The disadvantage is that pages are refcounted
 * (which can be slower and simply not an option क्रम some PFNMAP users). The
 * advantage is that we करोn't have to follow the strict linearity rule of
 * PFNMAP mappings in order to support COWable mappings.
 *
 */
काष्ठा page *vm_normal_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			    pte_t pte)
अणु
	अचिन्हित दीर्घ pfn = pte_pfn(pte);

	अगर (IS_ENABLED(CONFIG_ARCH_HAS_PTE_SPECIAL)) अणु
		अगर (likely(!pte_special(pte)))
			जाओ check_pfn;
		अगर (vma->vm_ops && vma->vm_ops->find_special_page)
			वापस vma->vm_ops->find_special_page(vma, addr);
		अगर (vma->vm_flags & (VM_PFNMAP | VM_MIXEDMAP))
			वापस शून्य;
		अगर (is_zero_pfn(pfn))
			वापस शून्य;
		अगर (pte_devmap(pte))
			वापस शून्य;

		prपूर्णांक_bad_pte(vma, addr, pte, शून्य);
		वापस शून्य;
	पूर्ण

	/* !CONFIG_ARCH_HAS_PTE_SPECIAL हाल follows: */

	अगर (unlikely(vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP))) अणु
		अगर (vma->vm_flags & VM_MIXEDMAP) अणु
			अगर (!pfn_valid(pfn))
				वापस शून्य;
			जाओ out;
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ off;
			off = (addr - vma->vm_start) >> PAGE_SHIFT;
			अगर (pfn == vma->vm_pgoff + off)
				वापस शून्य;
			अगर (!is_cow_mapping(vma->vm_flags))
				वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (is_zero_pfn(pfn))
		वापस शून्य;

check_pfn:
	अगर (unlikely(pfn > highest_memmap_pfn)) अणु
		prपूर्णांक_bad_pte(vma, addr, pte, शून्य);
		वापस शून्य;
	पूर्ण

	/*
	 * NOTE! We still have PageReserved() pages in the page tables.
	 * eg. VDSO mappings can cause them to exist.
	 */
out:
	वापस pfn_to_page(pfn);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
काष्ठा page *vm_normal_page_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
				pmd_t pmd)
अणु
	अचिन्हित दीर्घ pfn = pmd_pfn(pmd);

	/*
	 * There is no pmd_special() but there may be special pmds, e.g.
	 * in a direct-access (dax) mapping, so let's just replicate the
	 * !CONFIG_ARCH_HAS_PTE_SPECIAL हाल from vm_normal_page() here.
	 */
	अगर (unlikely(vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP))) अणु
		अगर (vma->vm_flags & VM_MIXEDMAP) अणु
			अगर (!pfn_valid(pfn))
				वापस शून्य;
			जाओ out;
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ off;
			off = (addr - vma->vm_start) >> PAGE_SHIFT;
			अगर (pfn == vma->vm_pgoff + off)
				वापस शून्य;
			अगर (!is_cow_mapping(vma->vm_flags))
				वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (pmd_devmap(pmd))
		वापस शून्य;
	अगर (is_huge_zero_pmd(pmd))
		वापस शून्य;
	अगर (unlikely(pfn > highest_memmap_pfn))
		वापस शून्य;

	/*
	 * NOTE! We still have PageReserved() pages in the page tables.
	 * eg. VDSO mappings can cause them to exist.
	 */
out:
	वापस pfn_to_page(pfn);
पूर्ण
#पूर्ण_अगर

/*
 * copy one vm_area from one task to the other. Assumes the page tables
 * alपढ़ोy present in the new task to be cleared in the whole range
 * covered by this vma.
 */

अटल अचिन्हित दीर्घ
copy_nonpresent_pte(काष्ठा mm_काष्ठा *dst_mm, काष्ठा mm_काष्ठा *src_mm,
		pte_t *dst_pte, pte_t *src_pte, काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, पूर्णांक *rss)
अणु
	अचिन्हित दीर्घ vm_flags = vma->vm_flags;
	pte_t pte = *src_pte;
	काष्ठा page *page;
	swp_entry_t entry = pte_to_swp_entry(pte);

	अगर (likely(!non_swap_entry(entry))) अणु
		अगर (swap_duplicate(entry) < 0)
			वापस entry.val;

		/* make sure dst_mm is on swapoff's mmlist. */
		अगर (unlikely(list_empty(&dst_mm->mmlist))) अणु
			spin_lock(&mmlist_lock);
			अगर (list_empty(&dst_mm->mmlist))
				list_add(&dst_mm->mmlist,
						&src_mm->mmlist);
			spin_unlock(&mmlist_lock);
		पूर्ण
		rss[MM_SWAPENTS]++;
	पूर्ण अन्यथा अगर (is_migration_entry(entry)) अणु
		page = migration_entry_to_page(entry);

		rss[mm_counter(page)]++;

		अगर (is_ग_लिखो_migration_entry(entry) &&
				is_cow_mapping(vm_flags)) अणु
			/*
			 * COW mappings require pages in both
			 * parent and child to be set to पढ़ो.
			 */
			make_migration_entry_पढ़ो(&entry);
			pte = swp_entry_to_pte(entry);
			अगर (pte_swp_soft_dirty(*src_pte))
				pte = pte_swp_mksoft_dirty(pte);
			अगर (pte_swp_uffd_wp(*src_pte))
				pte = pte_swp_mkuffd_wp(pte);
			set_pte_at(src_mm, addr, src_pte, pte);
		पूर्ण
	पूर्ण अन्यथा अगर (is_device_निजी_entry(entry)) अणु
		page = device_निजी_entry_to_page(entry);

		/*
		 * Update rss count even क्रम unaddressable pages, as
		 * they should treated just like normal pages in this
		 * respect.
		 *
		 * We will likely want to have some new rss counters
		 * क्रम unaddressable pages, at some poपूर्णांक. But क्रम now
		 * keep things as they are.
		 */
		get_page(page);
		rss[mm_counter(page)]++;
		page_dup_rmap(page, false);

		/*
		 * We करो not preserve soft-dirty inक्रमmation, because so
		 * far, checkpoपूर्णांक/restore is the only feature that
		 * requires that. And checkpoपूर्णांक/restore करोes not work
		 * when a device driver is involved (you cannot easily
		 * save and restore device driver state).
		 */
		अगर (is_ग_लिखो_device_निजी_entry(entry) &&
		    is_cow_mapping(vm_flags)) अणु
			make_device_निजी_entry_पढ़ो(&entry);
			pte = swp_entry_to_pte(entry);
			अगर (pte_swp_uffd_wp(*src_pte))
				pte = pte_swp_mkuffd_wp(pte);
			set_pte_at(src_mm, addr, src_pte, pte);
		पूर्ण
	पूर्ण
	set_pte_at(dst_mm, addr, dst_pte, pte);
	वापस 0;
पूर्ण

/*
 * Copy a present and normal page अगर necessary.
 *
 * NOTE! The usual हाल is that this करोesn't need to करो
 * anything, and can just वापस a positive value. That
 * will let the caller know that it can just increase
 * the page refcount and re-use the pte the traditional
 * way.
 *
 * But _अगर_ we need to copy it because it needs to be
 * pinned in the parent (and the child should get its own
 * copy rather than just a reference to the same page),
 * we'll करो that here and वापस zero to let the caller
 * know we're करोne.
 *
 * And अगर we need a pre-allocated page but करोn't yet have
 * one, वापस a negative error to let the pपुनः_स्मृतिation
 * code know so that it can करो so outside the page table
 * lock.
 */
अटल अंतरभूत पूर्णांक
copy_present_page(काष्ठा vm_area_काष्ठा *dst_vma, काष्ठा vm_area_काष्ठा *src_vma,
		  pte_t *dst_pte, pte_t *src_pte, अचिन्हित दीर्घ addr, पूर्णांक *rss,
		  काष्ठा page **pपुनः_स्मृति, pte_t pte, काष्ठा page *page)
अणु
	काष्ठा page *new_page;

	/*
	 * What we want to करो is to check whether this page may
	 * have been pinned by the parent process.  If so,
	 * instead of wrprotect the pte on both sides, we copy
	 * the page immediately so that we'll always guarantee
	 * the pinned page won't be अक्रमomly replaced in the
	 * future.
	 *
	 * The page pinning checks are just "has this mm ever
	 * seen pinning", aदीर्घ with the (inexact) check of
	 * the page count. That might give false positives क्रम
	 * क्रम pinning, but it will work correctly.
	 */
	अगर (likely(!page_needs_cow_क्रम_dma(src_vma, page)))
		वापस 1;

	new_page = *pपुनः_स्मृति;
	अगर (!new_page)
		वापस -EAGAIN;

	/*
	 * We have a pपुनः_स्मृति page, all good!  Take it
	 * over and copy the page & arm it.
	 */
	*pपुनः_स्मृति = शून्य;
	copy_user_highpage(new_page, page, addr, src_vma);
	__SetPageUptodate(new_page);
	page_add_new_anon_rmap(new_page, dst_vma, addr, false);
	lru_cache_add_inactive_or_unevictable(new_page, dst_vma);
	rss[mm_counter(new_page)]++;

	/* All करोne, just insert the new page copy in the child */
	pte = mk_pte(new_page, dst_vma->vm_page_prot);
	pte = maybe_mkग_लिखो(pte_सूची_गढ़ोty(pte), dst_vma);
	set_pte_at(dst_vma->vm_mm, addr, dst_pte, pte);
	वापस 0;
पूर्ण

/*
 * Copy one pte.  Returns 0 अगर succeeded, or -EAGAIN अगर one pपुनः_स्मृतिated page
 * is required to copy this pte.
 */
अटल अंतरभूत पूर्णांक
copy_present_pte(काष्ठा vm_area_काष्ठा *dst_vma, काष्ठा vm_area_काष्ठा *src_vma,
		 pte_t *dst_pte, pte_t *src_pte, अचिन्हित दीर्घ addr, पूर्णांक *rss,
		 काष्ठा page **pपुनः_स्मृति)
अणु
	काष्ठा mm_काष्ठा *src_mm = src_vma->vm_mm;
	अचिन्हित दीर्घ vm_flags = src_vma->vm_flags;
	pte_t pte = *src_pte;
	काष्ठा page *page;

	page = vm_normal_page(src_vma, addr, pte);
	अगर (page) अणु
		पूर्णांक retval;

		retval = copy_present_page(dst_vma, src_vma, dst_pte, src_pte,
					   addr, rss, pपुनः_स्मृति, pte, page);
		अगर (retval <= 0)
			वापस retval;

		get_page(page);
		page_dup_rmap(page, false);
		rss[mm_counter(page)]++;
	पूर्ण

	/*
	 * If it's a COW mapping, ग_लिखो protect it both
	 * in the parent and the child
	 */
	अगर (is_cow_mapping(vm_flags) && pte_ग_लिखो(pte)) अणु
		ptep_set_wrprotect(src_mm, addr, src_pte);
		pte = pte_wrprotect(pte);
	पूर्ण

	/*
	 * If it's a shared mapping, mark it clean in
	 * the child
	 */
	अगर (vm_flags & VM_SHARED)
		pte = pte_mkclean(pte);
	pte = pte_mkold(pte);

	/*
	 * Make sure the _PAGE_UFFD_WP bit is cleared अगर the new VMA
	 * करोes not have the VM_UFFD_WP, which means that the uffd
	 * विभाजन event is not enabled.
	 */
	अगर (!(vm_flags & VM_UFFD_WP))
		pte = pte_clear_uffd_wp(pte);

	set_pte_at(dst_vma->vm_mm, addr, dst_pte, pte);
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा page *
page_copy_pपुनः_स्मृति(काष्ठा mm_काष्ठा *src_mm, काष्ठा vm_area_काष्ठा *vma,
		   अचिन्हित दीर्घ addr)
अणु
	काष्ठा page *new_page;

	new_page = alloc_page_vma(GFP_HIGHUSER_MOVABLE, vma, addr);
	अगर (!new_page)
		वापस शून्य;

	अगर (mem_cgroup_अक्षरge(new_page, src_mm, GFP_KERNEL)) अणु
		put_page(new_page);
		वापस शून्य;
	पूर्ण
	cgroup_throttle_swaprate(new_page, GFP_KERNEL);

	वापस new_page;
पूर्ण

अटल पूर्णांक
copy_pte_range(काष्ठा vm_area_काष्ठा *dst_vma, काष्ठा vm_area_काष्ठा *src_vma,
	       pmd_t *dst_pmd, pmd_t *src_pmd, अचिन्हित दीर्घ addr,
	       अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *dst_mm = dst_vma->vm_mm;
	काष्ठा mm_काष्ठा *src_mm = src_vma->vm_mm;
	pte_t *orig_src_pte, *orig_dst_pte;
	pte_t *src_pte, *dst_pte;
	spinlock_t *src_ptl, *dst_ptl;
	पूर्णांक progress, ret = 0;
	पूर्णांक rss[NR_MM_COUNTERS];
	swp_entry_t entry = (swp_entry_t)अणु0पूर्ण;
	काष्ठा page *pपुनः_स्मृति = शून्य;

again:
	progress = 0;
	init_rss_vec(rss);

	dst_pte = pte_alloc_map_lock(dst_mm, dst_pmd, addr, &dst_ptl);
	अगर (!dst_pte) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	src_pte = pte_offset_map(src_pmd, addr);
	src_ptl = pte_lockptr(src_mm, src_pmd);
	spin_lock_nested(src_ptl, SINGLE_DEPTH_NESTING);
	orig_src_pte = src_pte;
	orig_dst_pte = dst_pte;
	arch_enter_lazy_mmu_mode();

	करो अणु
		/*
		 * We are holding two locks at this poपूर्णांक - either of them
		 * could generate latencies in another task on another CPU.
		 */
		अगर (progress >= 32) अणु
			progress = 0;
			अगर (need_resched() ||
			    spin_needअवरोध(src_ptl) || spin_needअवरोध(dst_ptl))
				अवरोध;
		पूर्ण
		अगर (pte_none(*src_pte)) अणु
			progress++;
			जारी;
		पूर्ण
		अगर (unlikely(!pte_present(*src_pte))) अणु
			entry.val = copy_nonpresent_pte(dst_mm, src_mm,
							dst_pte, src_pte,
							src_vma, addr, rss);
			अगर (entry.val)
				अवरोध;
			progress += 8;
			जारी;
		पूर्ण
		/* copy_present_pte() will clear `*pपुनः_स्मृति' अगर consumed */
		ret = copy_present_pte(dst_vma, src_vma, dst_pte, src_pte,
				       addr, rss, &pपुनः_स्मृति);
		/*
		 * If we need a pre-allocated page क्रम this pte, drop the
		 * locks, allocate, and try again.
		 */
		अगर (unlikely(ret == -EAGAIN))
			अवरोध;
		अगर (unlikely(pपुनः_स्मृति)) अणु
			/*
			 * pre-alloc page cannot be reused by next समय so as
			 * to strictly follow mempolicy (e.g., alloc_page_vma()
			 * will allocate page according to address).  This
			 * could only happen अगर one pinned pte changed.
			 */
			put_page(pपुनः_स्मृति);
			pपुनः_स्मृति = शून्य;
		पूर्ण
		progress += 8;
	पूर्ण जबतक (dst_pte++, src_pte++, addr += PAGE_SIZE, addr != end);

	arch_leave_lazy_mmu_mode();
	spin_unlock(src_ptl);
	pte_unmap(orig_src_pte);
	add_mm_rss_vec(dst_mm, rss);
	pte_unmap_unlock(orig_dst_pte, dst_ptl);
	cond_resched();

	अगर (entry.val) अणु
		अगर (add_swap_count_continuation(entry, GFP_KERNEL) < 0) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		entry.val = 0;
	पूर्ण अन्यथा अगर (ret) अणु
		WARN_ON_ONCE(ret != -EAGAIN);
		pपुनः_स्मृति = page_copy_pपुनः_स्मृति(src_mm, src_vma, addr);
		अगर (!pपुनः_स्मृति)
			वापस -ENOMEM;
		/* We've captured and resolved the error. Reset, try again. */
		ret = 0;
	पूर्ण
	अगर (addr != end)
		जाओ again;
out:
	अगर (unlikely(pपुनः_स्मृति))
		put_page(pपुनः_स्मृति);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
copy_pmd_range(काष्ठा vm_area_काष्ठा *dst_vma, काष्ठा vm_area_काष्ठा *src_vma,
	       pud_t *dst_pud, pud_t *src_pud, अचिन्हित दीर्घ addr,
	       अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *dst_mm = dst_vma->vm_mm;
	काष्ठा mm_काष्ठा *src_mm = src_vma->vm_mm;
	pmd_t *src_pmd, *dst_pmd;
	अचिन्हित दीर्घ next;

	dst_pmd = pmd_alloc(dst_mm, dst_pud, addr);
	अगर (!dst_pmd)
		वापस -ENOMEM;
	src_pmd = pmd_offset(src_pud, addr);
	करो अणु
		next = pmd_addr_end(addr, end);
		अगर (is_swap_pmd(*src_pmd) || pmd_trans_huge(*src_pmd)
			|| pmd_devmap(*src_pmd)) अणु
			पूर्णांक err;
			VM_BUG_ON_VMA(next-addr != HPAGE_PMD_SIZE, src_vma);
			err = copy_huge_pmd(dst_mm, src_mm,
					    dst_pmd, src_pmd, addr, src_vma);
			अगर (err == -ENOMEM)
				वापस -ENOMEM;
			अगर (!err)
				जारी;
			/* fall through */
		पूर्ण
		अगर (pmd_none_or_clear_bad(src_pmd))
			जारी;
		अगर (copy_pte_range(dst_vma, src_vma, dst_pmd, src_pmd,
				   addr, next))
			वापस -ENOMEM;
	पूर्ण जबतक (dst_pmd++, src_pmd++, addr = next, addr != end);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
copy_pud_range(काष्ठा vm_area_काष्ठा *dst_vma, काष्ठा vm_area_काष्ठा *src_vma,
	       p4d_t *dst_p4d, p4d_t *src_p4d, अचिन्हित दीर्घ addr,
	       अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *dst_mm = dst_vma->vm_mm;
	काष्ठा mm_काष्ठा *src_mm = src_vma->vm_mm;
	pud_t *src_pud, *dst_pud;
	अचिन्हित दीर्घ next;

	dst_pud = pud_alloc(dst_mm, dst_p4d, addr);
	अगर (!dst_pud)
		वापस -ENOMEM;
	src_pud = pud_offset(src_p4d, addr);
	करो अणु
		next = pud_addr_end(addr, end);
		अगर (pud_trans_huge(*src_pud) || pud_devmap(*src_pud)) अणु
			पूर्णांक err;

			VM_BUG_ON_VMA(next-addr != HPAGE_PUD_SIZE, src_vma);
			err = copy_huge_pud(dst_mm, src_mm,
					    dst_pud, src_pud, addr, src_vma);
			अगर (err == -ENOMEM)
				वापस -ENOMEM;
			अगर (!err)
				जारी;
			/* fall through */
		पूर्ण
		अगर (pud_none_or_clear_bad(src_pud))
			जारी;
		अगर (copy_pmd_range(dst_vma, src_vma, dst_pud, src_pud,
				   addr, next))
			वापस -ENOMEM;
	पूर्ण जबतक (dst_pud++, src_pud++, addr = next, addr != end);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
copy_p4d_range(काष्ठा vm_area_काष्ठा *dst_vma, काष्ठा vm_area_काष्ठा *src_vma,
	       pgd_t *dst_pgd, pgd_t *src_pgd, अचिन्हित दीर्घ addr,
	       अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *dst_mm = dst_vma->vm_mm;
	p4d_t *src_p4d, *dst_p4d;
	अचिन्हित दीर्घ next;

	dst_p4d = p4d_alloc(dst_mm, dst_pgd, addr);
	अगर (!dst_p4d)
		वापस -ENOMEM;
	src_p4d = p4d_offset(src_pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (p4d_none_or_clear_bad(src_p4d))
			जारी;
		अगर (copy_pud_range(dst_vma, src_vma, dst_p4d, src_p4d,
				   addr, next))
			वापस -ENOMEM;
	पूर्ण जबतक (dst_p4d++, src_p4d++, addr = next, addr != end);
	वापस 0;
पूर्ण

पूर्णांक
copy_page_range(काष्ठा vm_area_काष्ठा *dst_vma, काष्ठा vm_area_काष्ठा *src_vma)
अणु
	pgd_t *src_pgd, *dst_pgd;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ addr = src_vma->vm_start;
	अचिन्हित दीर्घ end = src_vma->vm_end;
	काष्ठा mm_काष्ठा *dst_mm = dst_vma->vm_mm;
	काष्ठा mm_काष्ठा *src_mm = src_vma->vm_mm;
	काष्ठा mmu_notअगरier_range range;
	bool is_cow;
	पूर्णांक ret;

	/*
	 * Don't copy ptes where a page fault will fill them correctly.
	 * Fork becomes much lighter when there are big shared or निजी
	 * पढ़ोonly mappings. The tradeoff is that copy_page_range is more
	 * efficient than faulting.
	 */
	अगर (!(src_vma->vm_flags & (VM_HUGETLB | VM_PFNMAP | VM_MIXEDMAP)) &&
	    !src_vma->anon_vma)
		वापस 0;

	अगर (is_vm_hugetlb_page(src_vma))
		वापस copy_hugetlb_page_range(dst_mm, src_mm, src_vma);

	अगर (unlikely(src_vma->vm_flags & VM_PFNMAP)) अणु
		/*
		 * We करो not मुक्त on error हालs below as हटाओ_vma
		 * माला_लो called on error from higher level routine
		 */
		ret = track_pfn_copy(src_vma);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * We need to invalidate the secondary MMU mappings only when
	 * there could be a permission करोwngrade on the ptes of the
	 * parent mm. And a permission करोwngrade will only happen अगर
	 * is_cow_mapping() वापसs true.
	 */
	is_cow = is_cow_mapping(src_vma->vm_flags);

	अगर (is_cow) अणु
		mmu_notअगरier_range_init(&range, MMU_NOTIFY_PROTECTION_PAGE,
					0, src_vma, src_mm, addr, end);
		mmu_notअगरier_invalidate_range_start(&range);
		/*
		 * Disabling preemption is not needed क्रम the ग_लिखो side, as
		 * the पढ़ो side करोesn't spin, but goes to the mmap_lock.
		 *
		 * Use the raw variant of the seqcount_t ग_लिखो API to aव्योम
		 * lockdep complaining about preemptibility.
		 */
		mmap_निश्चित_ग_लिखो_locked(src_mm);
		raw_ग_लिखो_seqcount_begin(&src_mm->ग_लिखो_protect_seq);
	पूर्ण

	ret = 0;
	dst_pgd = pgd_offset(dst_mm, addr);
	src_pgd = pgd_offset(src_mm, addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		अगर (pgd_none_or_clear_bad(src_pgd))
			जारी;
		अगर (unlikely(copy_p4d_range(dst_vma, src_vma, dst_pgd, src_pgd,
					    addr, next))) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (dst_pgd++, src_pgd++, addr = next, addr != end);

	अगर (is_cow) अणु
		raw_ग_लिखो_seqcount_end(&src_mm->ग_लिखो_protect_seq);
		mmu_notअगरier_invalidate_range_end(&range);
	पूर्ण
	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ zap_pte_range(काष्ठा mmu_gather *tlb,
				काष्ठा vm_area_काष्ठा *vma, pmd_t *pmd,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				काष्ठा zap_details *details)
अणु
	काष्ठा mm_काष्ठा *mm = tlb->mm;
	पूर्णांक क्रमce_flush = 0;
	पूर्णांक rss[NR_MM_COUNTERS];
	spinlock_t *ptl;
	pte_t *start_pte;
	pte_t *pte;
	swp_entry_t entry;

	tlb_change_page_size(tlb, PAGE_SIZE);
again:
	init_rss_vec(rss);
	start_pte = pte_offset_map_lock(mm, pmd, addr, &ptl);
	pte = start_pte;
	flush_tlb_batched_pending(mm);
	arch_enter_lazy_mmu_mode();
	करो अणु
		pte_t ptent = *pte;
		अगर (pte_none(ptent))
			जारी;

		अगर (need_resched())
			अवरोध;

		अगर (pte_present(ptent)) अणु
			काष्ठा page *page;

			page = vm_normal_page(vma, addr, ptent);
			अगर (unlikely(details) && page) अणु
				/*
				 * unmap_shared_mapping_pages() wants to
				 * invalidate cache without truncating:
				 * unmap shared but keep निजी pages.
				 */
				अगर (details->check_mapping &&
				    details->check_mapping != page_rmapping(page))
					जारी;
			पूर्ण
			ptent = ptep_get_and_clear_full(mm, addr, pte,
							tlb->fullmm);
			tlb_हटाओ_tlb_entry(tlb, pte, addr);
			अगर (unlikely(!page))
				जारी;

			अगर (!PageAnon(page)) अणु
				अगर (pte_dirty(ptent)) अणु
					क्रमce_flush = 1;
					set_page_dirty(page);
				पूर्ण
				अगर (pte_young(ptent) &&
				    likely(!(vma->vm_flags & VM_SEQ_READ)))
					mark_page_accessed(page);
			पूर्ण
			rss[mm_counter(page)]--;
			page_हटाओ_rmap(page, false);
			अगर (unlikely(page_mapcount(page) < 0))
				prपूर्णांक_bad_pte(vma, addr, ptent, page);
			अगर (unlikely(__tlb_हटाओ_page(tlb, page))) अणु
				क्रमce_flush = 1;
				addr += PAGE_SIZE;
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		entry = pte_to_swp_entry(ptent);
		अगर (is_device_निजी_entry(entry)) अणु
			काष्ठा page *page = device_निजी_entry_to_page(entry);

			अगर (unlikely(details && details->check_mapping)) अणु
				/*
				 * unmap_shared_mapping_pages() wants to
				 * invalidate cache without truncating:
				 * unmap shared but keep निजी pages.
				 */
				अगर (details->check_mapping !=
				    page_rmapping(page))
					जारी;
			पूर्ण

			pte_clear_not_present_full(mm, addr, pte, tlb->fullmm);
			rss[mm_counter(page)]--;
			page_हटाओ_rmap(page, false);
			put_page(page);
			जारी;
		पूर्ण

		/* If details->check_mapping, we leave swap entries. */
		अगर (unlikely(details))
			जारी;

		अगर (!non_swap_entry(entry))
			rss[MM_SWAPENTS]--;
		अन्यथा अगर (is_migration_entry(entry)) अणु
			काष्ठा page *page;

			page = migration_entry_to_page(entry);
			rss[mm_counter(page)]--;
		पूर्ण
		अगर (unlikely(!मुक्त_swap_and_cache(entry)))
			prपूर्णांक_bad_pte(vma, addr, ptent, शून्य);
		pte_clear_not_present_full(mm, addr, pte, tlb->fullmm);
	पूर्ण जबतक (pte++, addr += PAGE_SIZE, addr != end);

	add_mm_rss_vec(mm, rss);
	arch_leave_lazy_mmu_mode();

	/* Do the actual TLB flush beक्रमe dropping ptl */
	अगर (क्रमce_flush)
		tlb_flush_mmu_tlbonly(tlb);
	pte_unmap_unlock(start_pte, ptl);

	/*
	 * If we क्रमced a TLB flush (either due to running out of
	 * batch buffers or because we needed to flush dirty TLB
	 * entries beक्रमe releasing the ptl), मुक्त the batched
	 * memory too. Restart अगर we didn't करो everything.
	 */
	अगर (क्रमce_flush) अणु
		क्रमce_flush = 0;
		tlb_flush_mmu(tlb);
	पूर्ण

	अगर (addr != end) अणु
		cond_resched();
		जाओ again;
	पूर्ण

	वापस addr;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ zap_pmd_range(काष्ठा mmu_gather *tlb,
				काष्ठा vm_area_काष्ठा *vma, pud_t *pud,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				काष्ठा zap_details *details)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;

	pmd = pmd_offset(pud, addr);
	करो अणु
		next = pmd_addr_end(addr, end);
		अगर (is_swap_pmd(*pmd) || pmd_trans_huge(*pmd) || pmd_devmap(*pmd)) अणु
			अगर (next - addr != HPAGE_PMD_SIZE)
				__split_huge_pmd(vma, pmd, addr, false, शून्य);
			अन्यथा अगर (zap_huge_pmd(tlb, vma, pmd, addr))
				जाओ next;
			/* fall through */
		पूर्ण अन्यथा अगर (details && details->single_page &&
			   PageTransCompound(details->single_page) &&
			   next - addr == HPAGE_PMD_SIZE && pmd_none(*pmd)) अणु
			spinlock_t *ptl = pmd_lock(tlb->mm, pmd);
			/*
			 * Take and drop THP pmd lock so that we cannot वापस
			 * prematurely, जबतक zap_huge_pmd() has cleared *pmd,
			 * but not yet decremented compound_mapcount().
			 */
			spin_unlock(ptl);
		पूर्ण

		/*
		 * Here there can be other concurrent MADV_DONTNEED or
		 * trans huge page faults running, and अगर the pmd is
		 * none or trans huge it can change under us. This is
		 * because MADV_DONTNEED holds the mmap_lock in पढ़ो
		 * mode.
		 */
		अगर (pmd_none_or_trans_huge_or_clear_bad(pmd))
			जाओ next;
		next = zap_pte_range(tlb, vma, pmd, addr, next, details);
next:
		cond_resched();
	पूर्ण जबतक (pmd++, addr = next, addr != end);

	वापस addr;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ zap_pud_range(काष्ठा mmu_gather *tlb,
				काष्ठा vm_area_काष्ठा *vma, p4d_t *p4d,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				काष्ठा zap_details *details)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;

	pud = pud_offset(p4d, addr);
	करो अणु
		next = pud_addr_end(addr, end);
		अगर (pud_trans_huge(*pud) || pud_devmap(*pud)) अणु
			अगर (next - addr != HPAGE_PUD_SIZE) अणु
				mmap_निश्चित_locked(tlb->mm);
				split_huge_pud(vma, pud, addr);
			पूर्ण अन्यथा अगर (zap_huge_pud(tlb, vma, pud, addr))
				जाओ next;
			/* fall through */
		पूर्ण
		अगर (pud_none_or_clear_bad(pud))
			जारी;
		next = zap_pmd_range(tlb, vma, pud, addr, next, details);
next:
		cond_resched();
	पूर्ण जबतक (pud++, addr = next, addr != end);

	वापस addr;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ zap_p4d_range(काष्ठा mmu_gather *tlb,
				काष्ठा vm_area_काष्ठा *vma, pgd_t *pgd,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				काष्ठा zap_details *details)
अणु
	p4d_t *p4d;
	अचिन्हित दीर्घ next;

	p4d = p4d_offset(pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (p4d_none_or_clear_bad(p4d))
			जारी;
		next = zap_pud_range(tlb, vma, p4d, addr, next, details);
	पूर्ण जबतक (p4d++, addr = next, addr != end);

	वापस addr;
पूर्ण

व्योम unmap_page_range(काष्ठा mmu_gather *tlb,
			     काष्ठा vm_area_काष्ठा *vma,
			     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			     काष्ठा zap_details *details)
अणु
	pgd_t *pgd;
	अचिन्हित दीर्घ next;

	BUG_ON(addr >= end);
	tlb_start_vma(tlb, vma);
	pgd = pgd_offset(vma->vm_mm, addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		अगर (pgd_none_or_clear_bad(pgd))
			जारी;
		next = zap_p4d_range(tlb, vma, pgd, addr, next, details);
	पूर्ण जबतक (pgd++, addr = next, addr != end);
	tlb_end_vma(tlb, vma);
पूर्ण


अटल व्योम unmap_single_vma(काष्ठा mmu_gather *tlb,
		काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start_addr,
		अचिन्हित दीर्घ end_addr,
		काष्ठा zap_details *details)
अणु
	अचिन्हित दीर्घ start = max(vma->vm_start, start_addr);
	अचिन्हित दीर्घ end;

	अगर (start >= vma->vm_end)
		वापस;
	end = min(vma->vm_end, end_addr);
	अगर (end <= vma->vm_start)
		वापस;

	अगर (vma->vm_file)
		uprobe_munmap(vma, start, end);

	अगर (unlikely(vma->vm_flags & VM_PFNMAP))
		untrack_pfn(vma, 0, 0);

	अगर (start != end) अणु
		अगर (unlikely(is_vm_hugetlb_page(vma))) अणु
			/*
			 * It is undesirable to test vma->vm_file as it
			 * should be non-null क्रम valid hugetlb area.
			 * However, vm_file will be शून्य in the error
			 * cleanup path of mmap_region. When
			 * hugetlbfs ->mmap method fails,
			 * mmap_region() nullअगरies vma->vm_file
			 * beक्रमe calling this function to clean up.
			 * Since no pte has actually been setup, it is
			 * safe to करो nothing in this हाल.
			 */
			अगर (vma->vm_file) अणु
				i_mmap_lock_ग_लिखो(vma->vm_file->f_mapping);
				__unmap_hugepage_range_final(tlb, vma, start, end, शून्य);
				i_mmap_unlock_ग_लिखो(vma->vm_file->f_mapping);
			पूर्ण
		पूर्ण अन्यथा
			unmap_page_range(tlb, vma, start, end, details);
	पूर्ण
पूर्ण

/**
 * unmap_vmas - unmap a range of memory covered by a list of vma's
 * @tlb: address of the caller's काष्ठा mmu_gather
 * @vma: the starting vma
 * @start_addr: भव address at which to start unmapping
 * @end_addr: भव address at which to end unmapping
 *
 * Unmap all pages in the vma list.
 *
 * Only addresses between `start' and `end' will be unmapped.
 *
 * The VMA list must be sorted in ascending भव address order.
 *
 * unmap_vmas() assumes that the caller will flush the whole unmapped address
 * range after unmap_vmas() वापसs.  So the only responsibility here is to
 * ensure that any thus-far unmapped pages are flushed beक्रमe unmap_vmas()
 * drops the lock and schedules.
 */
व्योम unmap_vmas(काष्ठा mmu_gather *tlb,
		काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start_addr,
		अचिन्हित दीर्घ end_addr)
अणु
	काष्ठा mmu_notअगरier_range range;

	mmu_notअगरier_range_init(&range, MMU_NOTIFY_UNMAP, 0, vma, vma->vm_mm,
				start_addr, end_addr);
	mmu_notअगरier_invalidate_range_start(&range);
	क्रम ( ; vma && vma->vm_start < end_addr; vma = vma->vm_next)
		unmap_single_vma(tlb, vma, start_addr, end_addr, शून्य);
	mmu_notअगरier_invalidate_range_end(&range);
पूर्ण

/**
 * zap_page_range - हटाओ user pages in a given range
 * @vma: vm_area_काष्ठा holding the applicable pages
 * @start: starting address of pages to zap
 * @size: number of bytes to zap
 *
 * Caller must protect the VMA list
 */
व्योम zap_page_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ size)
अणु
	काष्ठा mmu_notअगरier_range range;
	काष्ठा mmu_gather tlb;

	lru_add_drain();
	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, vma->vm_mm,
				start, start + size);
	tlb_gather_mmu(&tlb, vma->vm_mm);
	update_hiwater_rss(vma->vm_mm);
	mmu_notअगरier_invalidate_range_start(&range);
	क्रम ( ; vma && vma->vm_start < range.end; vma = vma->vm_next)
		unmap_single_vma(&tlb, vma, start, range.end, शून्य);
	mmu_notअगरier_invalidate_range_end(&range);
	tlb_finish_mmu(&tlb);
पूर्ण

/**
 * zap_page_range_single - हटाओ user pages in a given range
 * @vma: vm_area_काष्ठा holding the applicable pages
 * @address: starting address of pages to zap
 * @size: number of bytes to zap
 * @details: details of shared cache invalidation
 *
 * The range must fit पूर्णांकo one VMA.
 */
अटल व्योम zap_page_range_single(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		अचिन्हित दीर्घ size, काष्ठा zap_details *details)
अणु
	काष्ठा mmu_notअगरier_range range;
	काष्ठा mmu_gather tlb;

	lru_add_drain();
	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, vma->vm_mm,
				address, address + size);
	tlb_gather_mmu(&tlb, vma->vm_mm);
	update_hiwater_rss(vma->vm_mm);
	mmu_notअगरier_invalidate_range_start(&range);
	unmap_single_vma(&tlb, vma, address, range.end, details);
	mmu_notअगरier_invalidate_range_end(&range);
	tlb_finish_mmu(&tlb);
पूर्ण

/**
 * zap_vma_ptes - हटाओ ptes mapping the vma
 * @vma: vm_area_काष्ठा holding ptes to be zapped
 * @address: starting address of pages to zap
 * @size: number of bytes to zap
 *
 * This function only unmaps ptes asचिन्हित to VM_PFNMAP vmas.
 *
 * The entire address range must be fully contained within the vma.
 *
 */
व्योम zap_vma_ptes(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		अचिन्हित दीर्घ size)
अणु
	अगर (address < vma->vm_start || address + size > vma->vm_end ||
	    		!(vma->vm_flags & VM_PFNMAP))
		वापस;

	zap_page_range_single(vma, address, size, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(zap_vma_ptes);

अटल pmd_t *walk_to_pmd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset(mm, addr);
	p4d = p4d_alloc(mm, pgd, addr);
	अगर (!p4d)
		वापस शून्य;
	pud = pud_alloc(mm, p4d, addr);
	अगर (!pud)
		वापस शून्य;
	pmd = pmd_alloc(mm, pud, addr);
	अगर (!pmd)
		वापस शून्य;

	VM_BUG_ON(pmd_trans_huge(*pmd));
	वापस pmd;
पूर्ण

pte_t *__get_locked_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			spinlock_t **ptl)
अणु
	pmd_t *pmd = walk_to_pmd(mm, addr);

	अगर (!pmd)
		वापस शून्य;
	वापस pte_alloc_map_lock(mm, pmd, addr, ptl);
पूर्ण

अटल पूर्णांक validate_page_beक्रमe_insert(काष्ठा page *page)
अणु
	अगर (PageAnon(page) || PageSlab(page) || page_has_type(page))
		वापस -EINVAL;
	flush_dcache_page(page);
	वापस 0;
पूर्ण

अटल पूर्णांक insert_page_पूर्णांकo_pte_locked(काष्ठा mm_काष्ठा *mm, pte_t *pte,
			अचिन्हित दीर्घ addr, काष्ठा page *page, pgprot_t prot)
अणु
	अगर (!pte_none(*pte))
		वापस -EBUSY;
	/* Ok, finally just insert the thing.. */
	get_page(page);
	inc_mm_counter_fast(mm, mm_counter_file(page));
	page_add_file_rmap(page, false);
	set_pte_at(mm, addr, pte, mk_pte(page, prot));
	वापस 0;
पूर्ण

/*
 * This is the old fallback क्रम page remapping.
 *
 * For historical reasons, it only allows reserved pages. Only
 * old drivers should use this, and they needed to mark their
 * pages reserved क्रम the old functions anyway.
 */
अटल पूर्णांक insert_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			काष्ठा page *page, pgprot_t prot)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	पूर्णांक retval;
	pte_t *pte;
	spinlock_t *ptl;

	retval = validate_page_beक्रमe_insert(page);
	अगर (retval)
		जाओ out;
	retval = -ENOMEM;
	pte = get_locked_pte(mm, addr, &ptl);
	अगर (!pte)
		जाओ out;
	retval = insert_page_पूर्णांकo_pte_locked(mm, pte, addr, page, prot);
	pte_unmap_unlock(pte, ptl);
out:
	वापस retval;
पूर्ण

#अगर_घोषित pte_index
अटल पूर्णांक insert_page_in_batch_locked(काष्ठा mm_काष्ठा *mm, pte_t *pte,
			अचिन्हित दीर्घ addr, काष्ठा page *page, pgprot_t prot)
अणु
	पूर्णांक err;

	अगर (!page_count(page))
		वापस -EINVAL;
	err = validate_page_beक्रमe_insert(page);
	अगर (err)
		वापस err;
	वापस insert_page_पूर्णांकo_pte_locked(mm, pte, addr, page, prot);
पूर्ण

/* insert_pages() amortizes the cost of spinlock operations
 * when inserting pages in a loop. Arch *must* define pte_index.
 */
अटल पूर्णांक insert_pages(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			काष्ठा page **pages, अचिन्हित दीर्घ *num, pgprot_t prot)
अणु
	pmd_t *pmd = शून्य;
	pte_t *start_pte, *pte;
	spinlock_t *pte_lock;
	काष्ठा mm_काष्ठा *स्थिर mm = vma->vm_mm;
	अचिन्हित दीर्घ curr_page_idx = 0;
	अचिन्हित दीर्घ reमुख्यing_pages_total = *num;
	अचिन्हित दीर्घ pages_to_ग_लिखो_in_pmd;
	पूर्णांक ret;
more:
	ret = -EFAULT;
	pmd = walk_to_pmd(mm, addr);
	अगर (!pmd)
		जाओ out;

	pages_to_ग_लिखो_in_pmd = min_t(अचिन्हित दीर्घ,
		reमुख्यing_pages_total, PTRS_PER_PTE - pte_index(addr));

	/* Allocate the PTE अगर necessary; takes PMD lock once only. */
	ret = -ENOMEM;
	अगर (pte_alloc(mm, pmd))
		जाओ out;

	जबतक (pages_to_ग_लिखो_in_pmd) अणु
		पूर्णांक pte_idx = 0;
		स्थिर पूर्णांक batch_size = min_t(पूर्णांक, pages_to_ग_लिखो_in_pmd, 8);

		start_pte = pte_offset_map_lock(mm, pmd, addr, &pte_lock);
		क्रम (pte = start_pte; pte_idx < batch_size; ++pte, ++pte_idx) अणु
			पूर्णांक err = insert_page_in_batch_locked(mm, pte,
				addr, pages[curr_page_idx], prot);
			अगर (unlikely(err)) अणु
				pte_unmap_unlock(start_pte, pte_lock);
				ret = err;
				reमुख्यing_pages_total -= pte_idx;
				जाओ out;
			पूर्ण
			addr += PAGE_SIZE;
			++curr_page_idx;
		पूर्ण
		pte_unmap_unlock(start_pte, pte_lock);
		pages_to_ग_लिखो_in_pmd -= batch_size;
		reमुख्यing_pages_total -= batch_size;
	पूर्ण
	अगर (reमुख्यing_pages_total)
		जाओ more;
	ret = 0;
out:
	*num = reमुख्यing_pages_total;
	वापस ret;
पूर्ण
#पूर्ण_अगर  /* अगरdef pte_index */

/**
 * vm_insert_pages - insert multiple pages पूर्णांकo user vma, batching the pmd lock.
 * @vma: user vma to map to
 * @addr: target start user address of these pages
 * @pages: source kernel pages
 * @num: in: number of pages to map. out: number of pages that were *not*
 * mapped. (0 means all pages were successfully mapped).
 *
 * Preferred over vm_insert_page() when inserting multiple pages.
 *
 * In हाल of error, we may have mapped a subset of the provided
 * pages. It is the caller's responsibility to account क्रम this हाल.
 *
 * The same restrictions apply as in vm_insert_page().
 */
पूर्णांक vm_insert_pages(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			काष्ठा page **pages, अचिन्हित दीर्घ *num)
अणु
#अगर_घोषित pte_index
	स्थिर अचिन्हित दीर्घ end_addr = addr + (*num * PAGE_SIZE) - 1;

	अगर (addr < vma->vm_start || end_addr >= vma->vm_end)
		वापस -EFAULT;
	अगर (!(vma->vm_flags & VM_MIXEDMAP)) अणु
		BUG_ON(mmap_पढ़ो_trylock(vma->vm_mm));
		BUG_ON(vma->vm_flags & VM_PFNMAP);
		vma->vm_flags |= VM_MIXEDMAP;
	पूर्ण
	/* Defer page refcount checking till we're about to map that page. */
	वापस insert_pages(vma, addr, pages, num, vma->vm_page_prot);
#अन्यथा
	अचिन्हित दीर्घ idx = 0, pgcount = *num;
	पूर्णांक err = -EINVAL;

	क्रम (; idx < pgcount; ++idx) अणु
		err = vm_insert_page(vma, addr + (PAGE_SIZE * idx), pages[idx]);
		अगर (err)
			अवरोध;
	पूर्ण
	*num = pgcount - idx;
	वापस err;
#पूर्ण_अगर  /* अगरdef pte_index */
पूर्ण
EXPORT_SYMBOL(vm_insert_pages);

/**
 * vm_insert_page - insert single page पूर्णांकo user vma
 * @vma: user vma to map to
 * @addr: target user address of this page
 * @page: source kernel page
 *
 * This allows drivers to insert inभागidual pages they've allocated
 * पूर्णांकo a user vma.
 *
 * The page has to be a nice clean _inभागidual_ kernel allocation.
 * If you allocate a compound page, you need to have marked it as
 * such (__GFP_COMP), or manually just split the page up yourself
 * (see split_page()).
 *
 * NOTE! Traditionally this was करोne with "remap_pfn_range()" which
 * took an arbitrary page protection parameter. This करोesn't allow
 * that. Your vma protection will have to be set up correctly, which
 * means that अगर you want a shared writable mapping, you'd better
 * ask क्रम a shared writable mapping!
 *
 * The page करोes not need to be reserved.
 *
 * Usually this function is called from f_op->mmap() handler
 * under mm->mmap_lock ग_लिखो-lock, so it can change vma->vm_flags.
 * Caller must set VM_MIXEDMAP on vma अगर it wants to call this
 * function from other places, क्रम example from page-fault handler.
 *
 * Return: %0 on success, negative error code otherwise.
 */
पूर्णांक vm_insert_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			काष्ठा page *page)
अणु
	अगर (addr < vma->vm_start || addr >= vma->vm_end)
		वापस -EFAULT;
	अगर (!page_count(page))
		वापस -EINVAL;
	अगर (!(vma->vm_flags & VM_MIXEDMAP)) अणु
		BUG_ON(mmap_पढ़ो_trylock(vma->vm_mm));
		BUG_ON(vma->vm_flags & VM_PFNMAP);
		vma->vm_flags |= VM_MIXEDMAP;
	पूर्ण
	वापस insert_page(vma, addr, page, vma->vm_page_prot);
पूर्ण
EXPORT_SYMBOL(vm_insert_page);

/*
 * __vm_map_pages - maps range of kernel pages पूर्णांकo user vma
 * @vma: user vma to map to
 * @pages: poपूर्णांकer to array of source kernel pages
 * @num: number of pages in page array
 * @offset: user's requested vm_pgoff
 *
 * This allows drivers to map range of kernel pages पूर्णांकo a user vma.
 *
 * Return: 0 on success and error code otherwise.
 */
अटल पूर्णांक __vm_map_pages(काष्ठा vm_area_काष्ठा *vma, काष्ठा page **pages,
				अचिन्हित दीर्घ num, अचिन्हित दीर्घ offset)
अणु
	अचिन्हित दीर्घ count = vma_pages(vma);
	अचिन्हित दीर्घ uaddr = vma->vm_start;
	पूर्णांक ret, i;

	/* Fail अगर the user requested offset is beyond the end of the object */
	अगर (offset >= num)
		वापस -ENXIO;

	/* Fail अगर the user requested size exceeds available object size */
	अगर (count > num - offset)
		वापस -ENXIO;

	क्रम (i = 0; i < count; i++) अणु
		ret = vm_insert_page(vma, uaddr, pages[offset + i]);
		अगर (ret < 0)
			वापस ret;
		uaddr += PAGE_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vm_map_pages - maps range of kernel pages starts with non zero offset
 * @vma: user vma to map to
 * @pages: poपूर्णांकer to array of source kernel pages
 * @num: number of pages in page array
 *
 * Maps an object consisting of @num pages, catering क्रम the user's
 * requested vm_pgoff
 *
 * If we fail to insert any page पूर्णांकo the vma, the function will वापस
 * immediately leaving any previously inserted pages present.  Callers
 * from the mmap handler may immediately वापस the error as their caller
 * will destroy the vma, removing any successfully inserted pages. Other
 * callers should make their own arrangements क्रम calling unmap_region().
 *
 * Context: Process context. Called by mmap handlers.
 * Return: 0 on success and error code otherwise.
 */
पूर्णांक vm_map_pages(काष्ठा vm_area_काष्ठा *vma, काष्ठा page **pages,
				अचिन्हित दीर्घ num)
अणु
	वापस __vm_map_pages(vma, pages, num, vma->vm_pgoff);
पूर्ण
EXPORT_SYMBOL(vm_map_pages);

/**
 * vm_map_pages_zero - map range of kernel pages starts with zero offset
 * @vma: user vma to map to
 * @pages: poपूर्णांकer to array of source kernel pages
 * @num: number of pages in page array
 *
 * Similar to vm_map_pages(), except that it explicitly sets the offset
 * to 0. This function is पूर्णांकended क्रम the drivers that did not consider
 * vm_pgoff.
 *
 * Context: Process context. Called by mmap handlers.
 * Return: 0 on success and error code otherwise.
 */
पूर्णांक vm_map_pages_zero(काष्ठा vm_area_काष्ठा *vma, काष्ठा page **pages,
				अचिन्हित दीर्घ num)
अणु
	वापस __vm_map_pages(vma, pages, num, 0);
पूर्ण
EXPORT_SYMBOL(vm_map_pages_zero);

अटल vm_fault_t insert_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			pfn_t pfn, pgprot_t prot, bool mkग_लिखो)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pte_t *pte, entry;
	spinlock_t *ptl;

	pte = get_locked_pte(mm, addr, &ptl);
	अगर (!pte)
		वापस VM_FAULT_OOM;
	अगर (!pte_none(*pte)) अणु
		अगर (mkग_लिखो) अणु
			/*
			 * For पढ़ो faults on निजी mappings the PFN passed
			 * in may not match the PFN we have mapped अगर the
			 * mapped PFN is a ग_लिखोable COW page.  In the mkग_लिखो
			 * हाल we are creating a writable PTE क्रम a shared
			 * mapping and we expect the PFNs to match. If they
			 * करोn't match, we are likely racing with block
			 * allocation and mapping invalidation so just skip the
			 * update.
			 */
			अगर (pte_pfn(*pte) != pfn_t_to_pfn(pfn)) अणु
				WARN_ON_ONCE(!is_zero_pfn(pte_pfn(*pte)));
				जाओ out_unlock;
			पूर्ण
			entry = pte_mkyoung(*pte);
			entry = maybe_mkग_लिखो(pte_सूची_गढ़ोty(entry), vma);
			अगर (ptep_set_access_flags(vma, addr, pte, entry, 1))
				update_mmu_cache(vma, addr, pte);
		पूर्ण
		जाओ out_unlock;
	पूर्ण

	/* Ok, finally just insert the thing.. */
	अगर (pfn_t_devmap(pfn))
		entry = pte_mkdevmap(pfn_t_pte(pfn, prot));
	अन्यथा
		entry = pte_mkspecial(pfn_t_pte(pfn, prot));

	अगर (mkग_लिखो) अणु
		entry = pte_mkyoung(entry);
		entry = maybe_mkग_लिखो(pte_सूची_गढ़ोty(entry), vma);
	पूर्ण

	set_pte_at(mm, addr, pte, entry);
	update_mmu_cache(vma, addr, pte); /* XXX: why not क्रम insert_page? */

out_unlock:
	pte_unmap_unlock(pte, ptl);
	वापस VM_FAULT_NOPAGE;
पूर्ण

/**
 * vmf_insert_pfn_prot - insert single pfn पूर्णांकo user vma with specअगरied pgprot
 * @vma: user vma to map to
 * @addr: target user address of this page
 * @pfn: source kernel pfn
 * @pgprot: pgprot flags क्रम the inserted page
 *
 * This is exactly like vmf_insert_pfn(), except that it allows drivers
 * to override pgprot on a per-page basis.
 *
 * This only makes sense क्रम IO mappings, and it makes no sense क्रम
 * COW mappings.  In general, using multiple vmas is preferable;
 * vmf_insert_pfn_prot should only be used अगर using multiple VMAs is
 * impractical.
 *
 * See vmf_insert_mixed_prot() क्रम a discussion of the implication of using
 * a value of @pgprot dअगरferent from that of @vma->vm_page_prot.
 *
 * Context: Process context.  May allocate using %GFP_KERNEL.
 * Return: vm_fault_t value.
 */
vm_fault_t vmf_insert_pfn_prot(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ pfn, pgprot_t pgprot)
अणु
	/*
	 * Technically, architectures with pte_special can aव्योम all these
	 * restrictions (same क्रम remap_pfn_range).  However we would like
	 * consistency in testing and feature parity among all, so we should
	 * try to keep these invariants in place क्रम everybody.
	 */
	BUG_ON(!(vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)));
	BUG_ON((vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)) ==
						(VM_PFNMAP|VM_MIXEDMAP));
	BUG_ON((vma->vm_flags & VM_PFNMAP) && is_cow_mapping(vma->vm_flags));
	BUG_ON((vma->vm_flags & VM_MIXEDMAP) && pfn_valid(pfn));

	अगर (addr < vma->vm_start || addr >= vma->vm_end)
		वापस VM_FAULT_SIGBUS;

	अगर (!pfn_modअगरy_allowed(pfn, pgprot))
		वापस VM_FAULT_SIGBUS;

	track_pfn_insert(vma, &pgprot, __pfn_to_pfn_t(pfn, PFN_DEV));

	वापस insert_pfn(vma, addr, __pfn_to_pfn_t(pfn, PFN_DEV), pgprot,
			false);
पूर्ण
EXPORT_SYMBOL(vmf_insert_pfn_prot);

/**
 * vmf_insert_pfn - insert single pfn पूर्णांकo user vma
 * @vma: user vma to map to
 * @addr: target user address of this page
 * @pfn: source kernel pfn
 *
 * Similar to vm_insert_page, this allows drivers to insert inभागidual pages
 * they've allocated पूर्णांकo a user vma. Same comments apply.
 *
 * This function should only be called from a vm_ops->fault handler, and
 * in that हाल the handler should वापस the result of this function.
 *
 * vma cannot be a COW mapping.
 *
 * As this is called only क्रम pages that करो not currently exist, we
 * करो not need to flush old भव caches or the TLB.
 *
 * Context: Process context.  May allocate using %GFP_KERNEL.
 * Return: vm_fault_t value.
 */
vm_fault_t vmf_insert_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ pfn)
अणु
	वापस vmf_insert_pfn_prot(vma, addr, pfn, vma->vm_page_prot);
पूर्ण
EXPORT_SYMBOL(vmf_insert_pfn);

अटल bool vm_mixed_ok(काष्ठा vm_area_काष्ठा *vma, pfn_t pfn)
अणु
	/* these checks mirror the पात conditions in vm_normal_page */
	अगर (vma->vm_flags & VM_MIXEDMAP)
		वापस true;
	अगर (pfn_t_devmap(pfn))
		वापस true;
	अगर (pfn_t_special(pfn))
		वापस true;
	अगर (is_zero_pfn(pfn_t_to_pfn(pfn)))
		वापस true;
	वापस false;
पूर्ण

अटल vm_fault_t __vm_insert_mixed(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pfn_t pfn, pgprot_t pgprot,
		bool mkग_लिखो)
अणु
	पूर्णांक err;

	BUG_ON(!vm_mixed_ok(vma, pfn));

	अगर (addr < vma->vm_start || addr >= vma->vm_end)
		वापस VM_FAULT_SIGBUS;

	track_pfn_insert(vma, &pgprot, pfn);

	अगर (!pfn_modअगरy_allowed(pfn_t_to_pfn(pfn), pgprot))
		वापस VM_FAULT_SIGBUS;

	/*
	 * If we करोn't have pte special, then we have to use the pfn_valid()
	 * based VM_MIXEDMAP scheme (see vm_normal_page), and thus we *must*
	 * refcount the page अगर pfn_valid is true (hence insert_page rather
	 * than insert_pfn).  If a zero_pfn were inserted पूर्णांकo a VM_MIXEDMAP
	 * without pte special, it would there be refcounted as a normal page.
	 */
	अगर (!IS_ENABLED(CONFIG_ARCH_HAS_PTE_SPECIAL) &&
	    !pfn_t_devmap(pfn) && pfn_t_valid(pfn)) अणु
		काष्ठा page *page;

		/*
		 * At this poपूर्णांक we are committed to insert_page()
		 * regardless of whether the caller specअगरied flags that
		 * result in pfn_t_has_page() == false.
		 */
		page = pfn_to_page(pfn_t_to_pfn(pfn));
		err = insert_page(vma, addr, page, pgprot);
	पूर्ण अन्यथा अणु
		वापस insert_pfn(vma, addr, pfn, pgprot, mkग_लिखो);
	पूर्ण

	अगर (err == -ENOMEM)
		वापस VM_FAULT_OOM;
	अगर (err < 0 && err != -EBUSY)
		वापस VM_FAULT_SIGBUS;

	वापस VM_FAULT_NOPAGE;
पूर्ण

/**
 * vmf_insert_mixed_prot - insert single pfn पूर्णांकo user vma with specअगरied pgprot
 * @vma: user vma to map to
 * @addr: target user address of this page
 * @pfn: source kernel pfn
 * @pgprot: pgprot flags क्रम the inserted page
 *
 * This is exactly like vmf_insert_mixed(), except that it allows drivers
 * to override pgprot on a per-page basis.
 *
 * Typically this function should be used by drivers to set caching- and
 * encryption bits dअगरferent than those of @vma->vm_page_prot, because
 * the caching- or encryption mode may not be known at mmap() समय.
 * This is ok as दीर्घ as @vma->vm_page_prot is not used by the core vm
 * to set caching and encryption bits क्रम those vmas (except क्रम COW pages).
 * This is ensured by core vm only modअगरying these page table entries using
 * functions that करोn't touch caching- or encryption bits, using pte_modअगरy()
 * अगर needed. (See क्रम example mprotect()).
 * Also when new page-table entries are created, this is only करोne using the
 * fault() callback, and never using the value of vma->vm_page_prot,
 * except क्रम page-table entries that poपूर्णांक to anonymous pages as the result
 * of COW.
 *
 * Context: Process context.  May allocate using %GFP_KERNEL.
 * Return: vm_fault_t value.
 */
vm_fault_t vmf_insert_mixed_prot(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
				 pfn_t pfn, pgprot_t pgprot)
अणु
	वापस __vm_insert_mixed(vma, addr, pfn, pgprot, false);
पूर्ण
EXPORT_SYMBOL(vmf_insert_mixed_prot);

vm_fault_t vmf_insert_mixed(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		pfn_t pfn)
अणु
	वापस __vm_insert_mixed(vma, addr, pfn, vma->vm_page_prot, false);
पूर्ण
EXPORT_SYMBOL(vmf_insert_mixed);

/*
 *  If the insertion of PTE failed because someone अन्यथा alपढ़ोy added a
 *  dअगरferent entry in the mean समय, we treat that as success as we assume
 *  the same entry was actually inserted.
 */
vm_fault_t vmf_insert_mixed_mkग_लिखो(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pfn_t pfn)
अणु
	वापस __vm_insert_mixed(vma, addr, pfn, vma->vm_page_prot, true);
पूर्ण
EXPORT_SYMBOL(vmf_insert_mixed_mkग_लिखो);

/*
 * maps a range of physical memory पूर्णांकo the requested pages. the old
 * mappings are हटाओd. any references to nonexistent pages results
 * in null mappings (currently treated as "copy-on-access")
 */
अटल पूर्णांक remap_pte_range(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pte_t *pte, *mapped_pte;
	spinlock_t *ptl;
	पूर्णांक err = 0;

	mapped_pte = pte = pte_alloc_map_lock(mm, pmd, addr, &ptl);
	अगर (!pte)
		वापस -ENOMEM;
	arch_enter_lazy_mmu_mode();
	करो अणु
		BUG_ON(!pte_none(*pte));
		अगर (!pfn_modअगरy_allowed(pfn, prot)) अणु
			err = -EACCES;
			अवरोध;
		पूर्ण
		set_pte_at(mm, addr, pte, pte_mkspecial(pfn_pte(pfn, prot)));
		pfn++;
	पूर्ण जबतक (pte++, addr += PAGE_SIZE, addr != end);
	arch_leave_lazy_mmu_mode();
	pte_unmap_unlock(mapped_pte, ptl);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक remap_pmd_range(काष्ठा mm_काष्ठा *mm, pud_t *pud,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;
	पूर्णांक err;

	pfn -= addr >> PAGE_SHIFT;
	pmd = pmd_alloc(mm, pud, addr);
	अगर (!pmd)
		वापस -ENOMEM;
	VM_BUG_ON(pmd_trans_huge(*pmd));
	करो अणु
		next = pmd_addr_end(addr, end);
		err = remap_pte_range(mm, pmd, addr, next,
				pfn + (addr >> PAGE_SHIFT), prot);
		अगर (err)
			वापस err;
	पूर्ण जबतक (pmd++, addr = next, addr != end);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक remap_pud_range(काष्ठा mm_काष्ठा *mm, p4d_t *p4d,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;
	पूर्णांक err;

	pfn -= addr >> PAGE_SHIFT;
	pud = pud_alloc(mm, p4d, addr);
	अगर (!pud)
		वापस -ENOMEM;
	करो अणु
		next = pud_addr_end(addr, end);
		err = remap_pmd_range(mm, pud, addr, next,
				pfn + (addr >> PAGE_SHIFT), prot);
		अगर (err)
			वापस err;
	पूर्ण जबतक (pud++, addr = next, addr != end);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक remap_p4d_range(काष्ठा mm_काष्ठा *mm, pgd_t *pgd,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	p4d_t *p4d;
	अचिन्हित दीर्घ next;
	पूर्णांक err;

	pfn -= addr >> PAGE_SHIFT;
	p4d = p4d_alloc(mm, pgd, addr);
	अगर (!p4d)
		वापस -ENOMEM;
	करो अणु
		next = p4d_addr_end(addr, end);
		err = remap_pud_range(mm, p4d, addr, next,
				pfn + (addr >> PAGE_SHIFT), prot);
		अगर (err)
			वापस err;
	पूर्ण जबतक (p4d++, addr = next, addr != end);
	वापस 0;
पूर्ण

/*
 * Variant of remap_pfn_range that करोes not call track_pfn_remap.  The caller
 * must have pre-validated the caching bits of the pgprot_t.
 */
पूर्णांक remap_pfn_range_notrack(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	pgd_t *pgd;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ end = addr + PAGE_ALIGN(size);
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	पूर्णांक err;

	अगर (WARN_ON_ONCE(!PAGE_ALIGNED(addr)))
		वापस -EINVAL;

	/*
	 * Physically remapped pages are special. Tell the
	 * rest of the world about it:
	 *   VM_IO tells people not to look at these pages
	 *	(accesses can have side effects).
	 *   VM_PFNMAP tells the core MM that the base pages are just
	 *	raw PFN mappings, and करो not have a "struct page" associated
	 *	with them.
	 *   VM_DONTEXPAND
	 *      Disable vma merging and expanding with mremap().
	 *   VM_DONTDUMP
	 *      Omit vma from core dump, even when VM_IO turned off.
	 *
	 * There's a horrible special हाल to handle copy-on-ग_लिखो
	 * behaviour that some programs depend on. We mark the "original"
	 * un-COW'ed pages by matching them up with "vma->vm_pgoff".
	 * See vm_normal_page() क्रम details.
	 */
	अगर (is_cow_mapping(vma->vm_flags)) अणु
		अगर (addr != vma->vm_start || end != vma->vm_end)
			वापस -EINVAL;
		vma->vm_pgoff = pfn;
	पूर्ण

	vma->vm_flags |= VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP;

	BUG_ON(addr >= end);
	pfn -= addr >> PAGE_SHIFT;
	pgd = pgd_offset(mm, addr);
	flush_cache_range(vma, addr, end);
	करो अणु
		next = pgd_addr_end(addr, end);
		err = remap_p4d_range(mm, pgd, addr, next,
				pfn + (addr >> PAGE_SHIFT), prot);
		अगर (err)
			वापस err;
	पूर्ण जबतक (pgd++, addr = next, addr != end);

	वापस 0;
पूर्ण

/**
 * remap_pfn_range - remap kernel memory to userspace
 * @vma: user vma to map to
 * @addr: target page aligned user address to start at
 * @pfn: page frame number of kernel physical memory address
 * @size: size of mapping area
 * @prot: page protection flags क्रम this mapping
 *
 * Note: this is only safe अगर the mm semaphore is held when called.
 *
 * Return: %0 on success, negative error code otherwise.
 */
पूर्णांक remap_pfn_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		    अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	पूर्णांक err;

	err = track_pfn_remap(vma, &prot, pfn, addr, PAGE_ALIGN(size));
	अगर (err)
		वापस -EINVAL;

	err = remap_pfn_range_notrack(vma, addr, pfn, size, prot);
	अगर (err)
		untrack_pfn(vma, pfn, PAGE_ALIGN(size));
	वापस err;
पूर्ण
EXPORT_SYMBOL(remap_pfn_range);

/**
 * vm_iomap_memory - remap memory to userspace
 * @vma: user vma to map to
 * @start: start of the physical memory to be mapped
 * @len: size of area
 *
 * This is a simplअगरied io_remap_pfn_range() क्रम common driver use. The
 * driver just needs to give us the physical memory range to be mapped,
 * we'll figure out the rest from the vma inक्रमmation.
 *
 * NOTE! Some drivers might want to tweak vma->vm_page_prot first to get
 * whatever ग_लिखो-combining details or similar.
 *
 * Return: %0 on success, negative error code otherwise.
 */
पूर्णांक vm_iomap_memory(काष्ठा vm_area_काष्ठा *vma, phys_addr_t start, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ vm_len, pfn, pages;

	/* Check that the physical memory area passed in looks valid */
	अगर (start + len < start)
		वापस -EINVAL;
	/*
	 * You *really* shouldn't map things that aren't page-aligned,
	 * but we've historically allowed it because IO memory might
	 * just have smaller alignment.
	 */
	len += start & ~PAGE_MASK;
	pfn = start >> PAGE_SHIFT;
	pages = (len + ~PAGE_MASK) >> PAGE_SHIFT;
	अगर (pfn + pages < pfn)
		वापस -EINVAL;

	/* We start the mapping 'vm_pgoff' pages पूर्णांकo the area */
	अगर (vma->vm_pgoff > pages)
		वापस -EINVAL;
	pfn += vma->vm_pgoff;
	pages -= vma->vm_pgoff;

	/* Can we fit all of the mapping? */
	vm_len = vma->vm_end - vma->vm_start;
	अगर (vm_len >> PAGE_SHIFT > pages)
		वापस -EINVAL;

	/* Ok, let it rip */
	वापस io_remap_pfn_range(vma, vma->vm_start, pfn, vm_len, vma->vm_page_prot);
पूर्ण
EXPORT_SYMBOL(vm_iomap_memory);

अटल पूर्णांक apply_to_pte_range(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				     pte_fn_t fn, व्योम *data, bool create,
				     pgtbl_mod_mask *mask)
अणु
	pte_t *pte, *mapped_pte;
	पूर्णांक err = 0;
	spinlock_t *ptl;

	अगर (create) अणु
		mapped_pte = pte = (mm == &init_mm) ?
			pte_alloc_kernel_track(pmd, addr, mask) :
			pte_alloc_map_lock(mm, pmd, addr, &ptl);
		अगर (!pte)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		mapped_pte = pte = (mm == &init_mm) ?
			pte_offset_kernel(pmd, addr) :
			pte_offset_map_lock(mm, pmd, addr, &ptl);
	पूर्ण

	BUG_ON(pmd_huge(*pmd));

	arch_enter_lazy_mmu_mode();

	अगर (fn) अणु
		करो अणु
			अगर (create || !pte_none(*pte)) अणु
				err = fn(pte++, addr, data);
				अगर (err)
					अवरोध;
			पूर्ण
		पूर्ण जबतक (addr += PAGE_SIZE, addr != end);
	पूर्ण
	*mask |= PGTBL_PTE_MODIFIED;

	arch_leave_lazy_mmu_mode();

	अगर (mm != &init_mm)
		pte_unmap_unlock(mapped_pte, ptl);
	वापस err;
पूर्ण

अटल पूर्णांक apply_to_pmd_range(काष्ठा mm_काष्ठा *mm, pud_t *pud,
				     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				     pte_fn_t fn, व्योम *data, bool create,
				     pgtbl_mod_mask *mask)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;
	पूर्णांक err = 0;

	BUG_ON(pud_huge(*pud));

	अगर (create) अणु
		pmd = pmd_alloc_track(mm, pud, addr, mask);
		अगर (!pmd)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		pmd = pmd_offset(pud, addr);
	पूर्ण
	करो अणु
		next = pmd_addr_end(addr, end);
		अगर (pmd_none(*pmd) && !create)
			जारी;
		अगर (WARN_ON_ONCE(pmd_leaf(*pmd)))
			वापस -EINVAL;
		अगर (!pmd_none(*pmd) && WARN_ON_ONCE(pmd_bad(*pmd))) अणु
			अगर (!create)
				जारी;
			pmd_clear_bad(pmd);
		पूर्ण
		err = apply_to_pte_range(mm, pmd, addr, next,
					 fn, data, create, mask);
		अगर (err)
			अवरोध;
	पूर्ण जबतक (pmd++, addr = next, addr != end);

	वापस err;
पूर्ण

अटल पूर्णांक apply_to_pud_range(काष्ठा mm_काष्ठा *mm, p4d_t *p4d,
				     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				     pte_fn_t fn, व्योम *data, bool create,
				     pgtbl_mod_mask *mask)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;
	पूर्णांक err = 0;

	अगर (create) अणु
		pud = pud_alloc_track(mm, p4d, addr, mask);
		अगर (!pud)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		pud = pud_offset(p4d, addr);
	पूर्ण
	करो अणु
		next = pud_addr_end(addr, end);
		अगर (pud_none(*pud) && !create)
			जारी;
		अगर (WARN_ON_ONCE(pud_leaf(*pud)))
			वापस -EINVAL;
		अगर (!pud_none(*pud) && WARN_ON_ONCE(pud_bad(*pud))) अणु
			अगर (!create)
				जारी;
			pud_clear_bad(pud);
		पूर्ण
		err = apply_to_pmd_range(mm, pud, addr, next,
					 fn, data, create, mask);
		अगर (err)
			अवरोध;
	पूर्ण जबतक (pud++, addr = next, addr != end);

	वापस err;
पूर्ण

अटल पूर्णांक apply_to_p4d_range(काष्ठा mm_काष्ठा *mm, pgd_t *pgd,
				     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				     pte_fn_t fn, व्योम *data, bool create,
				     pgtbl_mod_mask *mask)
अणु
	p4d_t *p4d;
	अचिन्हित दीर्घ next;
	पूर्णांक err = 0;

	अगर (create) अणु
		p4d = p4d_alloc_track(mm, pgd, addr, mask);
		अगर (!p4d)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		p4d = p4d_offset(pgd, addr);
	पूर्ण
	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (p4d_none(*p4d) && !create)
			जारी;
		अगर (WARN_ON_ONCE(p4d_leaf(*p4d)))
			वापस -EINVAL;
		अगर (!p4d_none(*p4d) && WARN_ON_ONCE(p4d_bad(*p4d))) अणु
			अगर (!create)
				जारी;
			p4d_clear_bad(p4d);
		पूर्ण
		err = apply_to_pud_range(mm, p4d, addr, next,
					 fn, data, create, mask);
		अगर (err)
			अवरोध;
	पूर्ण जबतक (p4d++, addr = next, addr != end);

	वापस err;
पूर्ण

अटल पूर्णांक __apply_to_page_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ size, pte_fn_t fn,
				 व्योम *data, bool create)
अणु
	pgd_t *pgd;
	अचिन्हित दीर्घ start = addr, next;
	अचिन्हित दीर्घ end = addr + size;
	pgtbl_mod_mask mask = 0;
	पूर्णांक err = 0;

	अगर (WARN_ON(addr >= end))
		वापस -EINVAL;

	pgd = pgd_offset(mm, addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		अगर (pgd_none(*pgd) && !create)
			जारी;
		अगर (WARN_ON_ONCE(pgd_leaf(*pgd)))
			वापस -EINVAL;
		अगर (!pgd_none(*pgd) && WARN_ON_ONCE(pgd_bad(*pgd))) अणु
			अगर (!create)
				जारी;
			pgd_clear_bad(pgd);
		पूर्ण
		err = apply_to_p4d_range(mm, pgd, addr, next,
					 fn, data, create, &mask);
		अगर (err)
			अवरोध;
	पूर्ण जबतक (pgd++, addr = next, addr != end);

	अगर (mask & ARCH_PAGE_TABLE_SYNC_MASK)
		arch_sync_kernel_mappings(start, start + size);

	वापस err;
पूर्ण

/*
 * Scan a region of भव memory, filling in page tables as necessary
 * and calling a provided function on each leaf page table.
 */
पूर्णांक apply_to_page_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ size, pte_fn_t fn, व्योम *data)
अणु
	वापस __apply_to_page_range(mm, addr, size, fn, data, true);
पूर्ण
EXPORT_SYMBOL_GPL(apply_to_page_range);

/*
 * Scan a region of भव memory, calling a provided function on
 * each leaf page table where it exists.
 *
 * Unlike apply_to_page_range, this करोes _not_ fill in page tables
 * where they are असलent.
 */
पूर्णांक apply_to_existing_page_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ size, pte_fn_t fn, व्योम *data)
अणु
	वापस __apply_to_page_range(mm, addr, size, fn, data, false);
पूर्ण
EXPORT_SYMBOL_GPL(apply_to_existing_page_range);

/*
 * handle_pte_fault chooses page fault handler according to an entry which was
 * पढ़ो non-atomically.  Beक्रमe making any commiपंचांगent, on those architectures
 * or configurations (e.g. i386 with PAE) which might give a mix of unmatched
 * parts, करो_swap_page must check under lock beक्रमe unmapping the pte and
 * proceeding (but करो_wp_page is only called after alपढ़ोy making such a check;
 * and करो_anonymous_page can safely check later on).
 */
अटल अंतरभूत पूर्णांक pte_unmap_same(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
				pte_t *page_table, pte_t orig_pte)
अणु
	पूर्णांक same = 1;
#अगर defined(CONFIG_SMP) || defined(CONFIG_PREEMPTION)
	अगर (माप(pte_t) > माप(अचिन्हित दीर्घ)) अणु
		spinlock_t *ptl = pte_lockptr(mm, pmd);
		spin_lock(ptl);
		same = pte_same(*page_table, orig_pte);
		spin_unlock(ptl);
	पूर्ण
#पूर्ण_अगर
	pte_unmap(page_table);
	वापस same;
पूर्ण

अटल अंतरभूत bool cow_user_page(काष्ठा page *dst, काष्ठा page *src,
				 काष्ठा vm_fault *vmf)
अणु
	bool ret;
	व्योम *kaddr;
	व्योम __user *uaddr;
	bool locked = false;
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ addr = vmf->address;

	अगर (likely(src)) अणु
		copy_user_highpage(dst, src, addr, vma);
		वापस true;
	पूर्ण

	/*
	 * If the source page was a PFN mapping, we करोn't have
	 * a "struct page" क्रम it. We करो a best-efक्रमt copy by
	 * just copying from the original user address. If that
	 * fails, we just zero-fill it. Live with it.
	 */
	kaddr = kmap_atomic(dst);
	uaddr = (व्योम __user *)(addr & PAGE_MASK);

	/*
	 * On architectures with software "accessed" bits, we would
	 * take a द्विगुन page fault, so mark it accessed here.
	 */
	अगर (arch_faults_on_old_pte() && !pte_young(vmf->orig_pte)) अणु
		pte_t entry;

		vmf->pte = pte_offset_map_lock(mm, vmf->pmd, addr, &vmf->ptl);
		locked = true;
		अगर (!likely(pte_same(*vmf->pte, vmf->orig_pte))) अणु
			/*
			 * Other thपढ़ो has alपढ़ोy handled the fault
			 * and update local tlb only
			 */
			update_mmu_tlb(vma, addr, vmf->pte);
			ret = false;
			जाओ pte_unlock;
		पूर्ण

		entry = pte_mkyoung(vmf->orig_pte);
		अगर (ptep_set_access_flags(vma, addr, vmf->pte, entry, 0))
			update_mmu_cache(vma, addr, vmf->pte);
	पूर्ण

	/*
	 * This really shouldn't fail, because the page is there
	 * in the page tables. But it might just be unपढ़ोable,
	 * in which हाल we just give up and fill the result with
	 * zeroes.
	 */
	अगर (__copy_from_user_inatomic(kaddr, uaddr, PAGE_SIZE)) अणु
		अगर (locked)
			जाओ warn;

		/* Re-validate under PTL अगर the page is still mapped */
		vmf->pte = pte_offset_map_lock(mm, vmf->pmd, addr, &vmf->ptl);
		locked = true;
		अगर (!likely(pte_same(*vmf->pte, vmf->orig_pte))) अणु
			/* The PTE changed under us, update local tlb */
			update_mmu_tlb(vma, addr, vmf->pte);
			ret = false;
			जाओ pte_unlock;
		पूर्ण

		/*
		 * The same page can be mapped back since last copy attempt.
		 * Try to copy again under PTL.
		 */
		अगर (__copy_from_user_inatomic(kaddr, uaddr, PAGE_SIZE)) अणु
			/*
			 * Give a warn in हाल there can be some obscure
			 * use-हाल
			 */
warn:
			WARN_ON_ONCE(1);
			clear_page(kaddr);
		पूर्ण
	पूर्ण

	ret = true;

pte_unlock:
	अगर (locked)
		pte_unmap_unlock(vmf->pte, vmf->ptl);
	kunmap_atomic(kaddr);
	flush_dcache_page(dst);

	वापस ret;
पूर्ण

अटल gfp_t __get_fault_gfp_mask(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *vm_file = vma->vm_file;

	अगर (vm_file)
		वापस mapping_gfp_mask(vm_file->f_mapping) | __GFP_FS | __GFP_IO;

	/*
	 * Special mappings (e.g. VDSO) करो not have any file so fake
	 * a शेष GFP_KERNEL क्रम them.
	 */
	वापस GFP_KERNEL;
पूर्ण

/*
 * Notअगरy the address space that the page is about to become writable so that
 * it can prohibit this or रुको क्रम the page to get पूर्णांकo an appropriate state.
 *
 * We करो this without the lock held, so that it can sleep अगर it needs to.
 */
अटल vm_fault_t करो_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	vm_fault_t ret;
	काष्ठा page *page = vmf->page;
	अचिन्हित पूर्णांक old_flags = vmf->flags;

	vmf->flags = FAULT_FLAG_WRITE|FAULT_FLAG_MKWRITE;

	अगर (vmf->vma->vm_file &&
	    IS_SWAPखाता(vmf->vma->vm_file->f_mapping->host))
		वापस VM_FAULT_SIGBUS;

	ret = vmf->vma->vm_ops->page_mkग_लिखो(vmf);
	/* Restore original flags so that caller is not surprised */
	vmf->flags = old_flags;
	अगर (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE)))
		वापस ret;
	अगर (unlikely(!(ret & VM_FAULT_LOCKED))) अणु
		lock_page(page);
		अगर (!page->mapping) अणु
			unlock_page(page);
			वापस 0; /* retry */
		पूर्ण
		ret |= VM_FAULT_LOCKED;
	पूर्ण अन्यथा
		VM_BUG_ON_PAGE(!PageLocked(page), page);
	वापस ret;
पूर्ण

/*
 * Handle dirtying of a page in shared file mapping on a ग_लिखो fault.
 *
 * The function expects the page to be locked and unlocks it.
 */
अटल vm_fault_t fault_dirty_shared_page(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा address_space *mapping;
	काष्ठा page *page = vmf->page;
	bool dirtied;
	bool page_mkग_लिखो = vma->vm_ops && vma->vm_ops->page_mkग_लिखो;

	dirtied = set_page_dirty(page);
	VM_BUG_ON_PAGE(PageAnon(page), page);
	/*
	 * Take a local copy of the address_space - page.mapping may be zeroed
	 * by truncate after unlock_page().   The address_space itself reमुख्यs
	 * pinned by vma->vm_file's reference.  We rely on unlock_page()'s
	 * release semantics to prevent the compiler from unकरोing this copying.
	 */
	mapping = page_rmapping(page);
	unlock_page(page);

	अगर (!page_mkग_लिखो)
		file_update_समय(vma->vm_file);

	/*
	 * Throttle page dirtying rate करोwn to ग_लिखोback speed.
	 *
	 * mapping may be शून्य here because some device drivers करो not
	 * set page.mapping but still dirty their pages
	 *
	 * Drop the mmap_lock beक्रमe रुकोing on IO, अगर we can. The file
	 * is pinning the mapping, as per above.
	 */
	अगर ((dirtied || page_mkग_लिखो) && mapping) अणु
		काष्ठा file *fpin;

		fpin = maybe_unlock_mmap_क्रम_io(vmf, शून्य);
		balance_dirty_pages_ratelimited(mapping);
		अगर (fpin) अणु
			fput(fpin);
			वापस VM_FAULT_RETRY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Handle ग_लिखो page faults क्रम pages that can be reused in the current vma
 *
 * This can happen either due to the mapping being with the VM_SHARED flag,
 * or due to us being the last reference standing to the page. In either
 * हाल, all we need to करो here is to mark the page as writable and update
 * any related book-keeping.
 */
अटल अंतरभूत व्योम wp_page_reuse(काष्ठा vm_fault *vmf)
	__releases(vmf->ptl)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा page *page = vmf->page;
	pte_t entry;
	/*
	 * Clear the pages cpupid inक्रमmation as the existing
	 * inक्रमmation potentially beदीर्घs to a now completely
	 * unrelated process.
	 */
	अगर (page)
		page_cpupid_xchg_last(page, (1 << LAST_CPUPID_SHIFT) - 1);

	flush_cache_page(vma, vmf->address, pte_pfn(vmf->orig_pte));
	entry = pte_mkyoung(vmf->orig_pte);
	entry = maybe_mkग_लिखो(pte_सूची_गढ़ोty(entry), vma);
	अगर (ptep_set_access_flags(vma, vmf->address, vmf->pte, entry, 1))
		update_mmu_cache(vma, vmf->address, vmf->pte);
	pte_unmap_unlock(vmf->pte, vmf->ptl);
	count_vm_event(PGREUSE);
पूर्ण

/*
 * Handle the हाल of a page which we actually need to copy to a new page.
 *
 * Called with mmap_lock locked and the old page referenced, but
 * without the ptl held.
 *
 * High level logic flow:
 *
 * - Allocate a page, copy the content of the old page to the new one.
 * - Handle book keeping and accounting - cgroups, mmu-notअगरiers, etc.
 * - Take the PTL. If the pte changed, bail out and release the allocated page
 * - If the pte is still the way we remember it, update the page table and all
 *   relevant references. This includes dropping the reference the page-table
 *   held to the old page, as well as updating the rmap.
 * - In any हाल, unlock the PTL and drop the reference we took to the old page.
 */
अटल vm_fault_t wp_page_copy(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा page *old_page = vmf->page;
	काष्ठा page *new_page = शून्य;
	pte_t entry;
	पूर्णांक page_copied = 0;
	काष्ठा mmu_notअगरier_range range;

	अगर (unlikely(anon_vma_prepare(vma)))
		जाओ oom;

	अगर (is_zero_pfn(pte_pfn(vmf->orig_pte))) अणु
		new_page = alloc_zeroed_user_highpage_movable(vma,
							      vmf->address);
		अगर (!new_page)
			जाओ oom;
	पूर्ण अन्यथा अणु
		new_page = alloc_page_vma(GFP_HIGHUSER_MOVABLE, vma,
				vmf->address);
		अगर (!new_page)
			जाओ oom;

		अगर (!cow_user_page(new_page, old_page, vmf)) अणु
			/*
			 * COW failed, अगर the fault was solved by other,
			 * it's fine. If not, userspace would re-fault on
			 * the same address and we will handle the fault
			 * from the second attempt.
			 */
			put_page(new_page);
			अगर (old_page)
				put_page(old_page);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (mem_cgroup_अक्षरge(new_page, mm, GFP_KERNEL))
		जाओ oom_मुक्त_new;
	cgroup_throttle_swaprate(new_page, GFP_KERNEL);

	__SetPageUptodate(new_page);

	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, mm,
				vmf->address & PAGE_MASK,
				(vmf->address & PAGE_MASK) + PAGE_SIZE);
	mmu_notअगरier_invalidate_range_start(&range);

	/*
	 * Re-check the pte - we dropped the lock
	 */
	vmf->pte = pte_offset_map_lock(mm, vmf->pmd, vmf->address, &vmf->ptl);
	अगर (likely(pte_same(*vmf->pte, vmf->orig_pte))) अणु
		अगर (old_page) अणु
			अगर (!PageAnon(old_page)) अणु
				dec_mm_counter_fast(mm,
						mm_counter_file(old_page));
				inc_mm_counter_fast(mm, MM_ANONPAGES);
			पूर्ण
		पूर्ण अन्यथा अणु
			inc_mm_counter_fast(mm, MM_ANONPAGES);
		पूर्ण
		flush_cache_page(vma, vmf->address, pte_pfn(vmf->orig_pte));
		entry = mk_pte(new_page, vma->vm_page_prot);
		entry = pte_sw_mkyoung(entry);
		entry = maybe_mkग_लिखो(pte_सूची_गढ़ोty(entry), vma);

		/*
		 * Clear the pte entry and flush it first, beक्रमe updating the
		 * pte with the new entry, to keep TLBs on dअगरferent CPUs in
		 * sync. This code used to set the new PTE then flush TLBs, but
		 * that left a winकरोw where the new PTE could be loaded पूर्णांकo
		 * some TLBs जबतक the old PTE reमुख्यs in others.
		 */
		ptep_clear_flush_notअगरy(vma, vmf->address, vmf->pte);
		page_add_new_anon_rmap(new_page, vma, vmf->address, false);
		lru_cache_add_inactive_or_unevictable(new_page, vma);
		/*
		 * We call the notअगरy macro here because, when using secondary
		 * mmu page tables (such as kvm shaकरोw page tables), we want the
		 * new page to be mapped directly पूर्णांकo the secondary page table.
		 */
		set_pte_at_notअगरy(mm, vmf->address, vmf->pte, entry);
		update_mmu_cache(vma, vmf->address, vmf->pte);
		अगर (old_page) अणु
			/*
			 * Only after चयनing the pte to the new page may
			 * we हटाओ the mapcount here. Otherwise another
			 * process may come and find the rmap count decremented
			 * beक्रमe the pte is चयनed to the new page, and
			 * "reuse" the old page writing पूर्णांकo it जबतक our pte
			 * here still poपूर्णांकs पूर्णांकo it and can be पढ़ो by other
			 * thपढ़ोs.
			 *
			 * The critical issue is to order this
			 * page_हटाओ_rmap with the ptp_clear_flush above.
			 * Those stores are ordered by (अगर nothing अन्यथा,)
			 * the barrier present in the atomic_add_negative
			 * in page_हटाओ_rmap.
			 *
			 * Then the TLB flush in ptep_clear_flush ensures that
			 * no process can access the old page beक्रमe the
			 * decremented mapcount is visible. And the old page
			 * cannot be reused until after the decremented
			 * mapcount is visible. So transitively, TLBs to
			 * old page will be flushed beक्रमe it can be reused.
			 */
			page_हटाओ_rmap(old_page, false);
		पूर्ण

		/* Free the old page.. */
		new_page = old_page;
		page_copied = 1;
	पूर्ण अन्यथा अणु
		update_mmu_tlb(vma, vmf->address, vmf->pte);
	पूर्ण

	अगर (new_page)
		put_page(new_page);

	pte_unmap_unlock(vmf->pte, vmf->ptl);
	/*
	 * No need to द्विगुन call mmu_notअगरier->invalidate_range() callback as
	 * the above ptep_clear_flush_notअगरy() did alपढ़ोy call it.
	 */
	mmu_notअगरier_invalidate_range_only_end(&range);
	अगर (old_page) अणु
		/*
		 * Don't let another task, with possibly unlocked vma,
		 * keep the mlocked page.
		 */
		अगर (page_copied && (vma->vm_flags & VM_LOCKED)) अणु
			lock_page(old_page);	/* LRU manipulation */
			अगर (PageMlocked(old_page))
				munlock_vma_page(old_page);
			unlock_page(old_page);
		पूर्ण
		put_page(old_page);
	पूर्ण
	वापस page_copied ? VM_FAULT_WRITE : 0;
oom_मुक्त_new:
	put_page(new_page);
oom:
	अगर (old_page)
		put_page(old_page);
	वापस VM_FAULT_OOM;
पूर्ण

/**
 * finish_mkग_लिखो_fault - finish page fault क्रम a shared mapping, making PTE
 *			  ग_लिखोable once the page is prepared
 *
 * @vmf: काष्ठाure describing the fault
 *
 * This function handles all that is needed to finish a ग_लिखो page fault in a
 * shared mapping due to PTE being पढ़ो-only once the mapped page is prepared.
 * It handles locking of PTE and modअगरying it.
 *
 * The function expects the page to be locked or other protection against
 * concurrent faults / ग_लिखोback (such as DAX radix tree locks).
 *
 * Return: %VM_FAULT_WRITE on success, %0 when PTE got changed beक्रमe
 * we acquired PTE lock.
 */
vm_fault_t finish_mkग_लिखो_fault(काष्ठा vm_fault *vmf)
अणु
	WARN_ON_ONCE(!(vmf->vma->vm_flags & VM_SHARED));
	vmf->pte = pte_offset_map_lock(vmf->vma->vm_mm, vmf->pmd, vmf->address,
				       &vmf->ptl);
	/*
	 * We might have raced with another page fault जबतक we released the
	 * pte_offset_map_lock.
	 */
	अगर (!pte_same(*vmf->pte, vmf->orig_pte)) अणु
		update_mmu_tlb(vmf->vma, vmf->address, vmf->pte);
		pte_unmap_unlock(vmf->pte, vmf->ptl);
		वापस VM_FAULT_NOPAGE;
	पूर्ण
	wp_page_reuse(vmf);
	वापस 0;
पूर्ण

/*
 * Handle ग_लिखो page faults क्रम VM_MIXEDMAP or VM_PFNMAP क्रम a VM_SHARED
 * mapping
 */
अटल vm_fault_t wp_pfn_shared(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;

	अगर (vma->vm_ops && vma->vm_ops->pfn_mkग_लिखो) अणु
		vm_fault_t ret;

		pte_unmap_unlock(vmf->pte, vmf->ptl);
		vmf->flags |= FAULT_FLAG_MKWRITE;
		ret = vma->vm_ops->pfn_mkग_लिखो(vmf);
		अगर (ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE))
			वापस ret;
		वापस finish_mkग_लिखो_fault(vmf);
	पूर्ण
	wp_page_reuse(vmf);
	वापस VM_FAULT_WRITE;
पूर्ण

अटल vm_fault_t wp_page_shared(काष्ठा vm_fault *vmf)
	__releases(vmf->ptl)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	vm_fault_t ret = VM_FAULT_WRITE;

	get_page(vmf->page);

	अगर (vma->vm_ops && vma->vm_ops->page_mkग_लिखो) अणु
		vm_fault_t पंचांगp;

		pte_unmap_unlock(vmf->pte, vmf->ptl);
		पंचांगp = करो_page_mkग_लिखो(vmf);
		अगर (unlikely(!पंचांगp || (पंचांगp &
				      (VM_FAULT_ERROR | VM_FAULT_NOPAGE)))) अणु
			put_page(vmf->page);
			वापस पंचांगp;
		पूर्ण
		पंचांगp = finish_mkग_लिखो_fault(vmf);
		अगर (unlikely(पंचांगp & (VM_FAULT_ERROR | VM_FAULT_NOPAGE))) अणु
			unlock_page(vmf->page);
			put_page(vmf->page);
			वापस पंचांगp;
		पूर्ण
	पूर्ण अन्यथा अणु
		wp_page_reuse(vmf);
		lock_page(vmf->page);
	पूर्ण
	ret |= fault_dirty_shared_page(vmf);
	put_page(vmf->page);

	वापस ret;
पूर्ण

/*
 * This routine handles present pages, when users try to ग_लिखो
 * to a shared page. It is करोne by copying the page to a new address
 * and decrementing the shared-page counter क्रम the old page.
 *
 * Note that this routine assumes that the protection checks have been
 * करोne by the caller (the low-level page fault routine in most हालs).
 * Thus we can safely just mark it writable once we've करोne any necessary
 * COW.
 *
 * We also mark the page dirty at this poपूर्णांक even though the page will
 * change only once the ग_लिखो actually happens. This aव्योमs a few races,
 * and potentially makes it more efficient.
 *
 * We enter with non-exclusive mmap_lock (to exclude vma changes,
 * but allow concurrent faults), with pte both mapped and locked.
 * We वापस with mmap_lock still held, but pte unmapped and unlocked.
 */
अटल vm_fault_t करो_wp_page(काष्ठा vm_fault *vmf)
	__releases(vmf->ptl)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;

	अगर (userfaultfd_pte_wp(vma, *vmf->pte)) अणु
		pte_unmap_unlock(vmf->pte, vmf->ptl);
		वापस handle_userfault(vmf, VM_UFFD_WP);
	पूर्ण

	/*
	 * Userfaultfd ग_लिखो-protect can defer flushes. Ensure the TLB
	 * is flushed in this हाल beक्रमe copying.
	 */
	अगर (unlikely(userfaultfd_wp(vmf->vma) &&
		     mm_tlb_flush_pending(vmf->vma->vm_mm)))
		flush_tlb_page(vmf->vma, vmf->address);

	vmf->page = vm_normal_page(vma, vmf->address, vmf->orig_pte);
	अगर (!vmf->page) अणु
		/*
		 * VM_MIXEDMAP !pfn_valid() हाल, or VM_SOFTसूचीTY clear on a
		 * VM_PFNMAP VMA.
		 *
		 * We should not cow pages in a shared ग_लिखोable mapping.
		 * Just mark the pages writable and/or call ops->pfn_mkग_लिखो.
		 */
		अगर ((vma->vm_flags & (VM_WRITE|VM_SHARED)) ==
				     (VM_WRITE|VM_SHARED))
			वापस wp_pfn_shared(vmf);

		pte_unmap_unlock(vmf->pte, vmf->ptl);
		वापस wp_page_copy(vmf);
	पूर्ण

	/*
	 * Take out anonymous pages first, anonymous shared vmas are
	 * not dirty accountable.
	 */
	अगर (PageAnon(vmf->page)) अणु
		काष्ठा page *page = vmf->page;

		/* PageKsm() करोesn't necessarily उठाओ the page refcount */
		अगर (PageKsm(page) || page_count(page) != 1)
			जाओ copy;
		अगर (!trylock_page(page))
			जाओ copy;
		अगर (PageKsm(page) || page_mapcount(page) != 1 || page_count(page) != 1) अणु
			unlock_page(page);
			जाओ copy;
		पूर्ण
		/*
		 * Ok, we've got the only map reference, and the only
		 * page count reference, and the page is locked,
		 * it's dark out, and we're wearing sunglasses. Hit it.
		 */
		unlock_page(page);
		wp_page_reuse(vmf);
		वापस VM_FAULT_WRITE;
	पूर्ण अन्यथा अगर (unlikely((vma->vm_flags & (VM_WRITE|VM_SHARED)) ==
					(VM_WRITE|VM_SHARED))) अणु
		वापस wp_page_shared(vmf);
	पूर्ण
copy:
	/*
	 * Ok, we need to copy. Oh, well..
	 */
	get_page(vmf->page);

	pte_unmap_unlock(vmf->pte, vmf->ptl);
	वापस wp_page_copy(vmf);
पूर्ण

अटल व्योम unmap_mapping_range_vma(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start_addr, अचिन्हित दीर्घ end_addr,
		काष्ठा zap_details *details)
अणु
	zap_page_range_single(vma, start_addr, end_addr - start_addr, details);
पूर्ण

अटल अंतरभूत व्योम unmap_mapping_range_tree(काष्ठा rb_root_cached *root,
					    काष्ठा zap_details *details)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	pgoff_t vba, vea, zba, zea;

	vma_पूर्णांकerval_tree_क्रमeach(vma, root,
			details->first_index, details->last_index) अणु

		vba = vma->vm_pgoff;
		vea = vba + vma_pages(vma) - 1;
		zba = details->first_index;
		अगर (zba < vba)
			zba = vba;
		zea = details->last_index;
		अगर (zea > vea)
			zea = vea;

		unmap_mapping_range_vma(vma,
			((zba - vba) << PAGE_SHIFT) + vma->vm_start,
			((zea - vba + 1) << PAGE_SHIFT) + vma->vm_start,
				details);
	पूर्ण
पूर्ण

/**
 * unmap_mapping_page() - Unmap single page from processes.
 * @page: The locked page to be unmapped.
 *
 * Unmap this page from any userspace process which still has it mmaped.
 * Typically, क्रम efficiency, the range of nearby pages has alपढ़ोy been
 * unmapped by unmap_mapping_pages() or unmap_mapping_range().  But once
 * truncation or invalidation holds the lock on a page, it may find that
 * the page has been remapped again: and then uses unmap_mapping_page()
 * to unmap it finally.
 */
व्योम unmap_mapping_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा zap_details details = अणु पूर्ण;

	VM_BUG_ON(!PageLocked(page));
	VM_BUG_ON(PageTail(page));

	details.check_mapping = mapping;
	details.first_index = page->index;
	details.last_index = page->index + thp_nr_pages(page) - 1;
	details.single_page = page;

	i_mmap_lock_ग_लिखो(mapping);
	अगर (unlikely(!RB_EMPTY_ROOT(&mapping->i_mmap.rb_root)))
		unmap_mapping_range_tree(&mapping->i_mmap, &details);
	i_mmap_unlock_ग_लिखो(mapping);
पूर्ण

/**
 * unmap_mapping_pages() - Unmap pages from processes.
 * @mapping: The address space containing pages to be unmapped.
 * @start: Index of first page to be unmapped.
 * @nr: Number of pages to be unmapped.  0 to unmap to end of file.
 * @even_cows: Whether to unmap even निजी COWed pages.
 *
 * Unmap the pages in this address space from any userspace process which
 * has them mmaped.  Generally, you want to हटाओ COWed pages as well when
 * a file is being truncated, but not when invalidating pages from the page
 * cache.
 */
व्योम unmap_mapping_pages(काष्ठा address_space *mapping, pgoff_t start,
		pgoff_t nr, bool even_cows)
अणु
	काष्ठा zap_details details = अणु पूर्ण;

	details.check_mapping = even_cows ? शून्य : mapping;
	details.first_index = start;
	details.last_index = start + nr - 1;
	अगर (details.last_index < details.first_index)
		details.last_index = अच_दीर्घ_उच्च;

	i_mmap_lock_ग_लिखो(mapping);
	अगर (unlikely(!RB_EMPTY_ROOT(&mapping->i_mmap.rb_root)))
		unmap_mapping_range_tree(&mapping->i_mmap, &details);
	i_mmap_unlock_ग_लिखो(mapping);
पूर्ण

/**
 * unmap_mapping_range - unmap the portion of all mmaps in the specअगरied
 * address_space corresponding to the specअगरied byte range in the underlying
 * file.
 *
 * @mapping: the address space containing mmaps to be unmapped.
 * @holebegin: byte in first page to unmap, relative to the start of
 * the underlying file.  This will be rounded करोwn to a PAGE_SIZE
 * boundary.  Note that this is dअगरferent from truncate_pagecache(), which
 * must keep the partial page.  In contrast, we must get rid of
 * partial pages.
 * @holelen: size of prospective hole in bytes.  This will be rounded
 * up to a PAGE_SIZE boundary.  A holelen of zero truncates to the
 * end of the file.
 * @even_cows: 1 when truncating a file, unmap even निजी COWed pages;
 * but 0 when invalidating pagecache, करोn't throw away निजी data.
 */
व्योम unmap_mapping_range(काष्ठा address_space *mapping,
		loff_t स्थिर holebegin, loff_t स्थिर holelen, पूर्णांक even_cows)
अणु
	pgoff_t hba = holebegin >> PAGE_SHIFT;
	pgoff_t hlen = (holelen + PAGE_SIZE - 1) >> PAGE_SHIFT;

	/* Check क्रम overflow. */
	अगर (माप(holelen) > माप(hlen)) अणु
		दीर्घ दीर्घ holeend =
			(holebegin + holelen + PAGE_SIZE - 1) >> PAGE_SHIFT;
		अगर (holeend & ~(दीर्घ दीर्घ)अच_दीर्घ_उच्च)
			hlen = अच_दीर्घ_उच्च - hba + 1;
	पूर्ण

	unmap_mapping_pages(mapping, hba, hlen, even_cows);
पूर्ण
EXPORT_SYMBOL(unmap_mapping_range);

/*
 * We enter with non-exclusive mmap_lock (to exclude vma changes,
 * but allow concurrent faults), and pte mapped but not yet locked.
 * We वापस with pte unmapped and unlocked.
 *
 * We वापस with the mmap_lock locked or unlocked in the same हालs
 * as करोes filemap_fault().
 */
vm_fault_t करो_swap_page(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा page *page = शून्य, *swapcache;
	swp_entry_t entry;
	pte_t pte;
	पूर्णांक locked;
	पूर्णांक exclusive = 0;
	vm_fault_t ret = 0;
	व्योम *shaकरोw = शून्य;

	अगर (!pte_unmap_same(vma->vm_mm, vmf->pmd, vmf->pte, vmf->orig_pte))
		जाओ out;

	entry = pte_to_swp_entry(vmf->orig_pte);
	अगर (unlikely(non_swap_entry(entry))) अणु
		अगर (is_migration_entry(entry)) अणु
			migration_entry_रुको(vma->vm_mm, vmf->pmd,
					     vmf->address);
		पूर्ण अन्यथा अगर (is_device_निजी_entry(entry)) अणु
			vmf->page = device_निजी_entry_to_page(entry);
			ret = vmf->page->pgmap->ops->migrate_to_ram(vmf);
		पूर्ण अन्यथा अगर (is_hwpoison_entry(entry)) अणु
			ret = VM_FAULT_HWPOISON;
		पूर्ण अन्यथा अणु
			prपूर्णांक_bad_pte(vma, vmf->address, vmf->orig_pte, शून्य);
			ret = VM_FAULT_SIGBUS;
		पूर्ण
		जाओ out;
	पूर्ण


	delayacct_set_flag(current, DELAYACCT_PF_SWAPIN);
	page = lookup_swap_cache(entry, vma, vmf->address);
	swapcache = page;

	अगर (!page) अणु
		काष्ठा swap_info_काष्ठा *si = swp_swap_info(entry);

		अगर (data_race(si->flags & SWP_SYNCHRONOUS_IO) &&
		    __swap_count(entry) == 1) अणु
			/* skip swapcache */
			page = alloc_page_vma(GFP_HIGHUSER_MOVABLE, vma,
							vmf->address);
			अगर (page) अणु
				__SetPageLocked(page);
				__SetPageSwapBacked(page);

				अगर (mem_cgroup_swapin_अक्षरge_page(page,
					vma->vm_mm, GFP_KERNEL, entry)) अणु
					ret = VM_FAULT_OOM;
					जाओ out_page;
				पूर्ण
				mem_cgroup_swapin_unअक्षरge_swap(entry);

				shaकरोw = get_shaकरोw_from_swap_cache(entry);
				अगर (shaकरोw)
					workingset_refault(page, shaकरोw);

				lru_cache_add(page);

				/* To provide entry to swap_पढ़ोpage() */
				set_page_निजी(page, entry.val);
				swap_पढ़ोpage(page, true);
				set_page_निजी(page, 0);
			पूर्ण
		पूर्ण अन्यथा अणु
			page = swapin_पढ़ोahead(entry, GFP_HIGHUSER_MOVABLE,
						vmf);
			swapcache = page;
		पूर्ण

		अगर (!page) अणु
			/*
			 * Back out अगर somebody अन्यथा faulted in this pte
			 * जबतक we released the pte lock.
			 */
			vmf->pte = pte_offset_map_lock(vma->vm_mm, vmf->pmd,
					vmf->address, &vmf->ptl);
			अगर (likely(pte_same(*vmf->pte, vmf->orig_pte)))
				ret = VM_FAULT_OOM;
			delayacct_clear_flag(current, DELAYACCT_PF_SWAPIN);
			जाओ unlock;
		पूर्ण

		/* Had to पढ़ो the page from swap area: Major fault */
		ret = VM_FAULT_MAJOR;
		count_vm_event(PGMAJFAULT);
		count_memcg_event_mm(vma->vm_mm, PGMAJFAULT);
	पूर्ण अन्यथा अगर (PageHWPoison(page)) अणु
		/*
		 * hwpoisoned dirty swapcache pages are kept क्रम समाप्तing
		 * owner processes (which may be unknown at hwpoison समय)
		 */
		ret = VM_FAULT_HWPOISON;
		delayacct_clear_flag(current, DELAYACCT_PF_SWAPIN);
		जाओ out_release;
	पूर्ण

	locked = lock_page_or_retry(page, vma->vm_mm, vmf->flags);

	delayacct_clear_flag(current, DELAYACCT_PF_SWAPIN);
	अगर (!locked) अणु
		ret |= VM_FAULT_RETRY;
		जाओ out_release;
	पूर्ण

	/*
	 * Make sure try_to_मुक्त_swap or reuse_swap_page or swapoff did not
	 * release the swapcache from under us.  The page pin, and pte_same
	 * test below, are not enough to exclude that.  Even अगर it is still
	 * swapcache, we need to check that the page's swap has not changed.
	 */
	अगर (unlikely((!PageSwapCache(page) ||
			page_निजी(page) != entry.val)) && swapcache)
		जाओ out_page;

	page = ksm_might_need_to_copy(page, vma, vmf->address);
	अगर (unlikely(!page)) अणु
		ret = VM_FAULT_OOM;
		page = swapcache;
		जाओ out_page;
	पूर्ण

	cgroup_throttle_swaprate(page, GFP_KERNEL);

	/*
	 * Back out अगर somebody अन्यथा alपढ़ोy faulted in this pte.
	 */
	vmf->pte = pte_offset_map_lock(vma->vm_mm, vmf->pmd, vmf->address,
			&vmf->ptl);
	अगर (unlikely(!pte_same(*vmf->pte, vmf->orig_pte)))
		जाओ out_nomap;

	अगर (unlikely(!PageUptodate(page))) अणु
		ret = VM_FAULT_SIGBUS;
		जाओ out_nomap;
	पूर्ण

	/*
	 * The page isn't present yet, go ahead with the fault.
	 *
	 * Be careful about the sequence of operations here.
	 * To get its accounting right, reuse_swap_page() must be called
	 * जबतक the page is counted on swap but not yet in mapcount i.e.
	 * beक्रमe page_add_anon_rmap() and swap_मुक्त(); try_to_मुक्त_swap()
	 * must be called after the swap_मुक्त(), or it will never succeed.
	 */

	inc_mm_counter_fast(vma->vm_mm, MM_ANONPAGES);
	dec_mm_counter_fast(vma->vm_mm, MM_SWAPENTS);
	pte = mk_pte(page, vma->vm_page_prot);
	अगर ((vmf->flags & FAULT_FLAG_WRITE) && reuse_swap_page(page, शून्य)) अणु
		pte = maybe_mkग_लिखो(pte_सूची_गढ़ोty(pte), vma);
		vmf->flags &= ~FAULT_FLAG_WRITE;
		ret |= VM_FAULT_WRITE;
		exclusive = RMAP_EXCLUSIVE;
	पूर्ण
	flush_icache_page(vma, page);
	अगर (pte_swp_soft_dirty(vmf->orig_pte))
		pte = pte_mksoft_dirty(pte);
	अगर (pte_swp_uffd_wp(vmf->orig_pte)) अणु
		pte = pte_mkuffd_wp(pte);
		pte = pte_wrprotect(pte);
	पूर्ण
	set_pte_at(vma->vm_mm, vmf->address, vmf->pte, pte);
	arch_करो_swap_page(vma->vm_mm, vma, vmf->address, pte, vmf->orig_pte);
	vmf->orig_pte = pte;

	/* ksm created a completely new copy */
	अगर (unlikely(page != swapcache && swapcache)) अणु
		page_add_new_anon_rmap(page, vma, vmf->address, false);
		lru_cache_add_inactive_or_unevictable(page, vma);
	पूर्ण अन्यथा अणु
		करो_page_add_anon_rmap(page, vma, vmf->address, exclusive);
	पूर्ण

	swap_मुक्त(entry);
	अगर (mem_cgroup_swap_full(page) ||
	    (vma->vm_flags & VM_LOCKED) || PageMlocked(page))
		try_to_मुक्त_swap(page);
	unlock_page(page);
	अगर (page != swapcache && swapcache) अणु
		/*
		 * Hold the lock to aव्योम the swap entry to be reused
		 * until we take the PT lock क्रम the pte_same() check
		 * (to aव्योम false positives from pte_same). For
		 * further safety release the lock after the swap_मुक्त
		 * so that the swap count won't change under a
		 * parallel locked swapcache.
		 */
		unlock_page(swapcache);
		put_page(swapcache);
	पूर्ण

	अगर (vmf->flags & FAULT_FLAG_WRITE) अणु
		ret |= करो_wp_page(vmf);
		अगर (ret & VM_FAULT_ERROR)
			ret &= VM_FAULT_ERROR;
		जाओ out;
	पूर्ण

	/* No need to invalidate - it was non-present beक्रमe */
	update_mmu_cache(vma, vmf->address, vmf->pte);
unlock:
	pte_unmap_unlock(vmf->pte, vmf->ptl);
out:
	वापस ret;
out_nomap:
	pte_unmap_unlock(vmf->pte, vmf->ptl);
out_page:
	unlock_page(page);
out_release:
	put_page(page);
	अगर (page != swapcache && swapcache) अणु
		unlock_page(swapcache);
		put_page(swapcache);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * We enter with non-exclusive mmap_lock (to exclude vma changes,
 * but allow concurrent faults), and pte mapped but not yet locked.
 * We वापस with mmap_lock still held, but pte unmapped and unlocked.
 */
अटल vm_fault_t करो_anonymous_page(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा page *page;
	vm_fault_t ret = 0;
	pte_t entry;

	/* File mapping without ->vm_ops ? */
	अगर (vma->vm_flags & VM_SHARED)
		वापस VM_FAULT_SIGBUS;

	/*
	 * Use pte_alloc() instead of pte_alloc_map().  We can't run
	 * pte_offset_map() on pmds where a huge pmd might be created
	 * from a dअगरferent thपढ़ो.
	 *
	 * pte_alloc_map() is safe to use under mmap_ग_लिखो_lock(mm) or when
	 * parallel thपढ़ोs are excluded by other means.
	 *
	 * Here we only have mmap_पढ़ो_lock(mm).
	 */
	अगर (pte_alloc(vma->vm_mm, vmf->pmd))
		वापस VM_FAULT_OOM;

	/* See comment in handle_pte_fault() */
	अगर (unlikely(pmd_trans_unstable(vmf->pmd)))
		वापस 0;

	/* Use the zero-page क्रम पढ़ोs */
	अगर (!(vmf->flags & FAULT_FLAG_WRITE) &&
			!mm_क्रमbids_zeropage(vma->vm_mm)) अणु
		entry = pte_mkspecial(pfn_pte(my_zero_pfn(vmf->address),
						vma->vm_page_prot));
		vmf->pte = pte_offset_map_lock(vma->vm_mm, vmf->pmd,
				vmf->address, &vmf->ptl);
		अगर (!pte_none(*vmf->pte)) अणु
			update_mmu_tlb(vma, vmf->address, vmf->pte);
			जाओ unlock;
		पूर्ण
		ret = check_stable_address_space(vma->vm_mm);
		अगर (ret)
			जाओ unlock;
		/* Deliver the page fault to userland, check inside PT lock */
		अगर (userfaultfd_missing(vma)) अणु
			pte_unmap_unlock(vmf->pte, vmf->ptl);
			वापस handle_userfault(vmf, VM_UFFD_MISSING);
		पूर्ण
		जाओ setpte;
	पूर्ण

	/* Allocate our own निजी page. */
	अगर (unlikely(anon_vma_prepare(vma)))
		जाओ oom;
	page = alloc_zeroed_user_highpage_movable(vma, vmf->address);
	अगर (!page)
		जाओ oom;

	अगर (mem_cgroup_अक्षरge(page, vma->vm_mm, GFP_KERNEL))
		जाओ oom_मुक्त_page;
	cgroup_throttle_swaprate(page, GFP_KERNEL);

	/*
	 * The memory barrier inside __SetPageUptodate makes sure that
	 * preceding stores to the page contents become visible beक्रमe
	 * the set_pte_at() ग_लिखो.
	 */
	__SetPageUptodate(page);

	entry = mk_pte(page, vma->vm_page_prot);
	entry = pte_sw_mkyoung(entry);
	अगर (vma->vm_flags & VM_WRITE)
		entry = pte_mkग_लिखो(pte_सूची_गढ़ोty(entry));

	vmf->pte = pte_offset_map_lock(vma->vm_mm, vmf->pmd, vmf->address,
			&vmf->ptl);
	अगर (!pte_none(*vmf->pte)) अणु
		update_mmu_cache(vma, vmf->address, vmf->pte);
		जाओ release;
	पूर्ण

	ret = check_stable_address_space(vma->vm_mm);
	अगर (ret)
		जाओ release;

	/* Deliver the page fault to userland, check inside PT lock */
	अगर (userfaultfd_missing(vma)) अणु
		pte_unmap_unlock(vmf->pte, vmf->ptl);
		put_page(page);
		वापस handle_userfault(vmf, VM_UFFD_MISSING);
	पूर्ण

	inc_mm_counter_fast(vma->vm_mm, MM_ANONPAGES);
	page_add_new_anon_rmap(page, vma, vmf->address, false);
	lru_cache_add_inactive_or_unevictable(page, vma);
setpte:
	set_pte_at(vma->vm_mm, vmf->address, vmf->pte, entry);

	/* No need to invalidate - it was non-present beक्रमe */
	update_mmu_cache(vma, vmf->address, vmf->pte);
unlock:
	pte_unmap_unlock(vmf->pte, vmf->ptl);
	वापस ret;
release:
	put_page(page);
	जाओ unlock;
oom_मुक्त_page:
	put_page(page);
oom:
	वापस VM_FAULT_OOM;
पूर्ण

/*
 * The mmap_lock must have been held on entry, and may have been
 * released depending on flags and vma->vm_ops->fault() वापस value.
 * See filemap_fault() and __lock_page_retry().
 */
अटल vm_fault_t __करो_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	vm_fault_t ret;

	/*
	 * Pपुनः_स्मृतिate pte beक्रमe we take page_lock because this might lead to
	 * deadlocks क्रम memcg reclaim which रुकोs क्रम pages under ग_लिखोback:
	 *				lock_page(A)
	 *				SetPageWriteback(A)
	 *				unlock_page(A)
	 * lock_page(B)
	 *				lock_page(B)
	 * pte_alloc_one
	 *   shrink_page_list
	 *     रुको_on_page_ग_लिखोback(A)
	 *				SetPageWriteback(B)
	 *				unlock_page(B)
	 *				# flush A, B to clear the ग_लिखोback
	 */
	अगर (pmd_none(*vmf->pmd) && !vmf->pपुनः_स्मृति_pte) अणु
		vmf->pपुनः_स्मृति_pte = pte_alloc_one(vma->vm_mm);
		अगर (!vmf->pपुनः_स्मृति_pte)
			वापस VM_FAULT_OOM;
		smp_wmb(); /* See comment in __pte_alloc() */
	पूर्ण

	ret = vma->vm_ops->fault(vmf);
	अगर (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE | VM_FAULT_RETRY |
			    VM_FAULT_DONE_COW)))
		वापस ret;

	अगर (unlikely(PageHWPoison(vmf->page))) अणु
		अगर (ret & VM_FAULT_LOCKED)
			unlock_page(vmf->page);
		put_page(vmf->page);
		vmf->page = शून्य;
		वापस VM_FAULT_HWPOISON;
	पूर्ण

	अगर (unlikely(!(ret & VM_FAULT_LOCKED)))
		lock_page(vmf->page);
	अन्यथा
		VM_BUG_ON_PAGE(!PageLocked(vmf->page), vmf->page);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल व्योम deposit_pपुनः_स्मृति_pte(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;

	pgtable_trans_huge_deposit(vma->vm_mm, vmf->pmd, vmf->pपुनः_स्मृति_pte);
	/*
	 * We are going to consume the pपुनः_स्मृति table,
	 * count that as nr_ptes.
	 */
	mm_inc_nr_ptes(vma->vm_mm);
	vmf->pपुनः_स्मृति_pte = शून्य;
पूर्ण

vm_fault_t करो_set_pmd(काष्ठा vm_fault *vmf, काष्ठा page *page)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	bool ग_लिखो = vmf->flags & FAULT_FLAG_WRITE;
	अचिन्हित दीर्घ haddr = vmf->address & HPAGE_PMD_MASK;
	pmd_t entry;
	पूर्णांक i;
	vm_fault_t ret = VM_FAULT_FALLBACK;

	अगर (!transhuge_vma_suitable(vma, haddr))
		वापस ret;

	page = compound_head(page);
	अगर (compound_order(page) != HPAGE_PMD_ORDER)
		वापस ret;

	/*
	 * Archs like ppc64 need additional space to store inक्रमmation
	 * related to pte entry. Use the pपुनः_स्मृतिated table क्रम that.
	 */
	अगर (arch_needs_pgtable_deposit() && !vmf->pपुनः_स्मृति_pte) अणु
		vmf->pपुनः_स्मृति_pte = pte_alloc_one(vma->vm_mm);
		अगर (!vmf->pपुनः_स्मृति_pte)
			वापस VM_FAULT_OOM;
		smp_wmb(); /* See comment in __pte_alloc() */
	पूर्ण

	vmf->ptl = pmd_lock(vma->vm_mm, vmf->pmd);
	अगर (unlikely(!pmd_none(*vmf->pmd)))
		जाओ out;

	क्रम (i = 0; i < HPAGE_PMD_NR; i++)
		flush_icache_page(vma, page + i);

	entry = mk_huge_pmd(page, vma->vm_page_prot);
	अगर (ग_लिखो)
		entry = maybe_pmd_mkग_लिखो(pmd_सूची_गढ़ोty(entry), vma);

	add_mm_counter(vma->vm_mm, mm_counter_file(page), HPAGE_PMD_NR);
	page_add_file_rmap(page, true);
	/*
	 * deposit and withdraw with pmd lock held
	 */
	अगर (arch_needs_pgtable_deposit())
		deposit_pपुनः_स्मृति_pte(vmf);

	set_pmd_at(vma->vm_mm, haddr, vmf->pmd, entry);

	update_mmu_cache_pmd(vma, haddr, vmf->pmd);

	/* fault is handled */
	ret = 0;
	count_vm_event(THP_खाता_MAPPED);
out:
	spin_unlock(vmf->ptl);
	वापस ret;
पूर्ण
#अन्यथा
vm_fault_t करो_set_pmd(काष्ठा vm_fault *vmf, काष्ठा page *page)
अणु
	वापस VM_FAULT_FALLBACK;
पूर्ण
#पूर्ण_अगर

व्योम करो_set_pte(काष्ठा vm_fault *vmf, काष्ठा page *page, अचिन्हित दीर्घ addr)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	bool ग_लिखो = vmf->flags & FAULT_FLAG_WRITE;
	bool prefault = vmf->address != addr;
	pte_t entry;

	flush_icache_page(vma, page);
	entry = mk_pte(page, vma->vm_page_prot);

	अगर (prefault && arch_wants_old_prefaulted_pte())
		entry = pte_mkold(entry);
	अन्यथा
		entry = pte_sw_mkyoung(entry);

	अगर (ग_लिखो)
		entry = maybe_mkग_लिखो(pte_सूची_गढ़ोty(entry), vma);
	/* copy-on-ग_लिखो page */
	अगर (ग_लिखो && !(vma->vm_flags & VM_SHARED)) अणु
		inc_mm_counter_fast(vma->vm_mm, MM_ANONPAGES);
		page_add_new_anon_rmap(page, vma, addr, false);
		lru_cache_add_inactive_or_unevictable(page, vma);
	पूर्ण अन्यथा अणु
		inc_mm_counter_fast(vma->vm_mm, mm_counter_file(page));
		page_add_file_rmap(page, false);
	पूर्ण
	set_pte_at(vma->vm_mm, addr, vmf->pte, entry);
पूर्ण

/**
 * finish_fault - finish page fault once we have prepared the page to fault
 *
 * @vmf: काष्ठाure describing the fault
 *
 * This function handles all that is needed to finish a page fault once the
 * page to fault in is prepared. It handles locking of PTEs, inserts PTE क्रम
 * given page, adds reverse page mapping, handles memcg अक्षरges and LRU
 * addition.
 *
 * The function expects the page to be locked and on success it consumes a
 * reference of a page being mapped (क्रम the PTE which maps it).
 *
 * Return: %0 on success, %VM_FAULT_ code in हाल of error.
 */
vm_fault_t finish_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा page *page;
	vm_fault_t ret;

	/* Did we COW the page? */
	अगर ((vmf->flags & FAULT_FLAG_WRITE) && !(vma->vm_flags & VM_SHARED))
		page = vmf->cow_page;
	अन्यथा
		page = vmf->page;

	/*
	 * check even क्रम पढ़ो faults because we might have lost our CoWed
	 * page
	 */
	अगर (!(vma->vm_flags & VM_SHARED)) अणु
		ret = check_stable_address_space(vma->vm_mm);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (pmd_none(*vmf->pmd)) अणु
		अगर (PageTransCompound(page)) अणु
			ret = करो_set_pmd(vmf, page);
			अगर (ret != VM_FAULT_FALLBACK)
				वापस ret;
		पूर्ण

		अगर (unlikely(pte_alloc(vma->vm_mm, vmf->pmd)))
			वापस VM_FAULT_OOM;
	पूर्ण

	/* See comment in handle_pte_fault() */
	अगर (pmd_devmap_trans_unstable(vmf->pmd))
		वापस 0;

	vmf->pte = pte_offset_map_lock(vma->vm_mm, vmf->pmd,
				      vmf->address, &vmf->ptl);
	ret = 0;
	/* Re-check under ptl */
	अगर (likely(pte_none(*vmf->pte)))
		करो_set_pte(vmf, page, vmf->address);
	अन्यथा
		ret = VM_FAULT_NOPAGE;

	update_mmu_tlb(vma, vmf->address, vmf->pte);
	pte_unmap_unlock(vmf->pte, vmf->ptl);
	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ fault_around_bytes __पढ़ो_mostly =
	roundकरोwn_घात_of_two(65536);

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक fault_around_bytes_get(व्योम *data, u64 *val)
अणु
	*val = fault_around_bytes;
	वापस 0;
पूर्ण

/*
 * fault_around_bytes must be rounded करोwn to the nearest page order as it's
 * what करो_fault_around() expects to see.
 */
अटल पूर्णांक fault_around_bytes_set(व्योम *data, u64 val)
अणु
	अगर (val / PAGE_SIZE > PTRS_PER_PTE)
		वापस -EINVAL;
	अगर (val > PAGE_SIZE)
		fault_around_bytes = roundकरोwn_घात_of_two(val);
	अन्यथा
		fault_around_bytes = PAGE_SIZE; /* roundकरोwn_घात_of_two(0) is undefined */
	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fault_around_bytes_fops,
		fault_around_bytes_get, fault_around_bytes_set, "%llu\n");

अटल पूर्णांक __init fault_around_debugfs(व्योम)
अणु
	debugfs_create_file_unsafe("fault_around_bytes", 0644, शून्य, शून्य,
				   &fault_around_bytes_fops);
	वापस 0;
पूर्ण
late_initcall(fault_around_debugfs);
#पूर्ण_अगर

/*
 * करो_fault_around() tries to map few pages around the fault address. The hope
 * is that the pages will be needed soon and this will lower the number of
 * faults to handle.
 *
 * It uses vm_ops->map_pages() to map the pages, which skips the page अगर it's
 * not पढ़ोy to be mapped: not up-to-date, locked, etc.
 *
 * This function is called with the page table lock taken. In the split ptlock
 * हाल the page table lock only protects only those entries which beदीर्घ to
 * the page table corresponding to the fault address.
 *
 * This function करोesn't cross the VMA boundaries, in order to call map_pages()
 * only once.
 *
 * fault_around_bytes defines how many bytes we'll try to map.
 * करो_fault_around() expects it to be set to a घातer of two less than or equal
 * to PTRS_PER_PTE.
 *
 * The भव address of the area that we map is naturally aligned to
 * fault_around_bytes rounded करोwn to the machine page size
 * (and thereक्रमe to page order).  This way it's easier to guarantee
 * that we करोn't cross page table boundaries.
 */
अटल vm_fault_t करो_fault_around(काष्ठा vm_fault *vmf)
अणु
	अचिन्हित दीर्घ address = vmf->address, nr_pages, mask;
	pgoff_t start_pgoff = vmf->pgoff;
	pgoff_t end_pgoff;
	पूर्णांक off;

	nr_pages = READ_ONCE(fault_around_bytes) >> PAGE_SHIFT;
	mask = ~(nr_pages * PAGE_SIZE - 1) & PAGE_MASK;

	address = max(address & mask, vmf->vma->vm_start);
	off = ((vmf->address - address) >> PAGE_SHIFT) & (PTRS_PER_PTE - 1);
	start_pgoff -= off;

	/*
	 *  end_pgoff is either the end of the page table, the end of
	 *  the vma or nr_pages from start_pgoff, depending what is nearest.
	 */
	end_pgoff = start_pgoff -
		((address >> PAGE_SHIFT) & (PTRS_PER_PTE - 1)) +
		PTRS_PER_PTE - 1;
	end_pgoff = min3(end_pgoff, vma_pages(vmf->vma) + vmf->vma->vm_pgoff - 1,
			start_pgoff + nr_pages - 1);

	अगर (pmd_none(*vmf->pmd)) अणु
		vmf->pपुनः_स्मृति_pte = pte_alloc_one(vmf->vma->vm_mm);
		अगर (!vmf->pपुनः_स्मृति_pte)
			वापस VM_FAULT_OOM;
		smp_wmb(); /* See comment in __pte_alloc() */
	पूर्ण

	वापस vmf->vma->vm_ops->map_pages(vmf, start_pgoff, end_pgoff);
पूर्ण

अटल vm_fault_t करो_पढ़ो_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	vm_fault_t ret = 0;

	/*
	 * Let's call ->map_pages() first and use ->fault() as fallback
	 * अगर page by the offset is not पढ़ोy to be mapped (cold cache or
	 * something).
	 */
	अगर (vma->vm_ops->map_pages && fault_around_bytes >> PAGE_SHIFT > 1) अणु
		ret = करो_fault_around(vmf);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = __करो_fault(vmf);
	अगर (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE | VM_FAULT_RETRY)))
		वापस ret;

	ret |= finish_fault(vmf);
	unlock_page(vmf->page);
	अगर (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE | VM_FAULT_RETRY)))
		put_page(vmf->page);
	वापस ret;
पूर्ण

अटल vm_fault_t करो_cow_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	vm_fault_t ret;

	अगर (unlikely(anon_vma_prepare(vma)))
		वापस VM_FAULT_OOM;

	vmf->cow_page = alloc_page_vma(GFP_HIGHUSER_MOVABLE, vma, vmf->address);
	अगर (!vmf->cow_page)
		वापस VM_FAULT_OOM;

	अगर (mem_cgroup_अक्षरge(vmf->cow_page, vma->vm_mm, GFP_KERNEL)) अणु
		put_page(vmf->cow_page);
		वापस VM_FAULT_OOM;
	पूर्ण
	cgroup_throttle_swaprate(vmf->cow_page, GFP_KERNEL);

	ret = __करो_fault(vmf);
	अगर (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE | VM_FAULT_RETRY)))
		जाओ unअक्षरge_out;
	अगर (ret & VM_FAULT_DONE_COW)
		वापस ret;

	copy_user_highpage(vmf->cow_page, vmf->page, vmf->address, vma);
	__SetPageUptodate(vmf->cow_page);

	ret |= finish_fault(vmf);
	unlock_page(vmf->page);
	put_page(vmf->page);
	अगर (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE | VM_FAULT_RETRY)))
		जाओ unअक्षरge_out;
	वापस ret;
unअक्षरge_out:
	put_page(vmf->cow_page);
	वापस ret;
पूर्ण

अटल vm_fault_t करो_shared_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	vm_fault_t ret, पंचांगp;

	ret = __करो_fault(vmf);
	अगर (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE | VM_FAULT_RETRY)))
		वापस ret;

	/*
	 * Check अगर the backing address space wants to know that the page is
	 * about to become writable
	 */
	अगर (vma->vm_ops->page_mkग_लिखो) अणु
		unlock_page(vmf->page);
		पंचांगp = करो_page_mkग_लिखो(vmf);
		अगर (unlikely(!पंचांगp ||
				(पंचांगp & (VM_FAULT_ERROR | VM_FAULT_NOPAGE)))) अणु
			put_page(vmf->page);
			वापस पंचांगp;
		पूर्ण
	पूर्ण

	ret |= finish_fault(vmf);
	अगर (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE |
					VM_FAULT_RETRY))) अणु
		unlock_page(vmf->page);
		put_page(vmf->page);
		वापस ret;
	पूर्ण

	ret |= fault_dirty_shared_page(vmf);
	वापस ret;
पूर्ण

/*
 * We enter with non-exclusive mmap_lock (to exclude vma changes,
 * but allow concurrent faults).
 * The mmap_lock may have been released depending on flags and our
 * वापस value.  See filemap_fault() and __lock_page_or_retry().
 * If mmap_lock is released, vma may become invalid (क्रम example
 * by other thपढ़ो calling munmap()).
 */
अटल vm_fault_t करो_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा mm_काष्ठा *vm_mm = vma->vm_mm;
	vm_fault_t ret;

	/*
	 * The VMA was not fully populated on mmap() or missing VM_DONTEXPAND
	 */
	अगर (!vma->vm_ops->fault) अणु
		/*
		 * If we find a migration pmd entry or a none pmd entry, which
		 * should never happen, वापस SIGBUS
		 */
		अगर (unlikely(!pmd_present(*vmf->pmd)))
			ret = VM_FAULT_SIGBUS;
		अन्यथा अणु
			vmf->pte = pte_offset_map_lock(vmf->vma->vm_mm,
						       vmf->pmd,
						       vmf->address,
						       &vmf->ptl);
			/*
			 * Make sure this is not a temporary clearing of pte
			 * by holding ptl and checking again. A R/M/W update
			 * of pte involves: take ptl, clearing the pte so that
			 * we करोn't have concurrent modअगरication by hardware
			 * followed by an update.
			 */
			अगर (unlikely(pte_none(*vmf->pte)))
				ret = VM_FAULT_SIGBUS;
			अन्यथा
				ret = VM_FAULT_NOPAGE;

			pte_unmap_unlock(vmf->pte, vmf->ptl);
		पूर्ण
	पूर्ण अन्यथा अगर (!(vmf->flags & FAULT_FLAG_WRITE))
		ret = करो_पढ़ो_fault(vmf);
	अन्यथा अगर (!(vma->vm_flags & VM_SHARED))
		ret = करो_cow_fault(vmf);
	अन्यथा
		ret = करो_shared_fault(vmf);

	/* pपुनः_स्मृतिated pagetable is unused: मुक्त it */
	अगर (vmf->pपुनः_स्मृति_pte) अणु
		pte_मुक्त(vm_mm, vmf->pपुनः_स्मृति_pte);
		vmf->pपुनः_स्मृति_pte = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक numa_migrate_prep(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ addr, पूर्णांक page_nid,
				पूर्णांक *flags)
अणु
	get_page(page);

	count_vm_numa_event(NUMA_HINT_FAULTS);
	अगर (page_nid == numa_node_id()) अणु
		count_vm_numa_event(NUMA_HINT_FAULTS_LOCAL);
		*flags |= TNF_FAULT_LOCAL;
	पूर्ण

	वापस mpol_misplaced(page, vma, addr);
पूर्ण

अटल vm_fault_t करो_numa_page(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा page *page = शून्य;
	पूर्णांक page_nid = NUMA_NO_NODE;
	पूर्णांक last_cpupid;
	पूर्णांक target_nid;
	pte_t pte, old_pte;
	bool was_writable = pte_savedग_लिखो(vmf->orig_pte);
	पूर्णांक flags = 0;

	/*
	 * The "pte" at this poपूर्णांक cannot be used safely without
	 * validation through pte_unmap_same(). It's of NUMA type but
	 * the pfn may be screwed अगर the पढ़ो is non atomic.
	 */
	vmf->ptl = pte_lockptr(vma->vm_mm, vmf->pmd);
	spin_lock(vmf->ptl);
	अगर (unlikely(!pte_same(*vmf->pte, vmf->orig_pte))) अणु
		pte_unmap_unlock(vmf->pte, vmf->ptl);
		जाओ out;
	पूर्ण

	/* Get the normal PTE  */
	old_pte = ptep_get(vmf->pte);
	pte = pte_modअगरy(old_pte, vma->vm_page_prot);

	page = vm_normal_page(vma, vmf->address, pte);
	अगर (!page)
		जाओ out_map;

	/* TODO: handle PTE-mapped THP */
	अगर (PageCompound(page))
		जाओ out_map;

	/*
	 * Aव्योम grouping on RO pages in general. RO pages shouldn't hurt as
	 * much anyway since they can be in shared cache state. This misses
	 * the हाल where a mapping is writable but the process never ग_लिखोs
	 * to it but pte_ग_लिखो माला_लो cleared during protection updates and
	 * pte_dirty has unpredictable behaviour between PTE scan updates,
	 * background ग_लिखोback, dirty balancing and application behaviour.
	 */
	अगर (!was_writable)
		flags |= TNF_NO_GROUP;

	/*
	 * Flag अगर the page is shared between multiple address spaces. This
	 * is later used when determining whether to group tasks together
	 */
	अगर (page_mapcount(page) > 1 && (vma->vm_flags & VM_SHARED))
		flags |= TNF_SHARED;

	last_cpupid = page_cpupid_last(page);
	page_nid = page_to_nid(page);
	target_nid = numa_migrate_prep(page, vma, vmf->address, page_nid,
			&flags);
	अगर (target_nid == NUMA_NO_NODE) अणु
		put_page(page);
		जाओ out_map;
	पूर्ण
	pte_unmap_unlock(vmf->pte, vmf->ptl);

	/* Migrate to the requested node */
	अगर (migrate_misplaced_page(page, vma, target_nid)) अणु
		page_nid = target_nid;
		flags |= TNF_MIGRATED;
	पूर्ण अन्यथा अणु
		flags |= TNF_MIGRATE_FAIL;
		vmf->pte = pte_offset_map(vmf->pmd, vmf->address);
		spin_lock(vmf->ptl);
		अगर (unlikely(!pte_same(*vmf->pte, vmf->orig_pte))) अणु
			pte_unmap_unlock(vmf->pte, vmf->ptl);
			जाओ out;
		पूर्ण
		जाओ out_map;
	पूर्ण

out:
	अगर (page_nid != NUMA_NO_NODE)
		task_numa_fault(last_cpupid, page_nid, 1, flags);
	वापस 0;
out_map:
	/*
	 * Make it present again, depending on how arch implements
	 * non-accessible ptes, some can allow access by kernel mode.
	 */
	old_pte = ptep_modअगरy_prot_start(vma, vmf->address, vmf->pte);
	pte = pte_modअगरy(old_pte, vma->vm_page_prot);
	pte = pte_mkyoung(pte);
	अगर (was_writable)
		pte = pte_mkग_लिखो(pte);
	ptep_modअगरy_prot_commit(vma, vmf->address, vmf->pte, old_pte, pte);
	update_mmu_cache(vma, vmf->address, vmf->pte);
	pte_unmap_unlock(vmf->pte, vmf->ptl);
	जाओ out;
पूर्ण

अटल अंतरभूत vm_fault_t create_huge_pmd(काष्ठा vm_fault *vmf)
अणु
	अगर (vma_is_anonymous(vmf->vma))
		वापस करो_huge_pmd_anonymous_page(vmf);
	अगर (vmf->vma->vm_ops->huge_fault)
		वापस vmf->vma->vm_ops->huge_fault(vmf, PE_SIZE_PMD);
	वापस VM_FAULT_FALLBACK;
पूर्ण

/* `अंतरभूत' is required to aव्योम gcc 4.1.2 build error */
अटल अंतरभूत vm_fault_t wp_huge_pmd(काष्ठा vm_fault *vmf, pmd_t orig_pmd)
अणु
	अगर (vma_is_anonymous(vmf->vma)) अणु
		अगर (userfaultfd_huge_pmd_wp(vmf->vma, orig_pmd))
			वापस handle_userfault(vmf, VM_UFFD_WP);
		वापस करो_huge_pmd_wp_page(vmf, orig_pmd);
	पूर्ण
	अगर (vmf->vma->vm_ops->huge_fault) अणु
		vm_fault_t ret = vmf->vma->vm_ops->huge_fault(vmf, PE_SIZE_PMD);

		अगर (!(ret & VM_FAULT_FALLBACK))
			वापस ret;
	पूर्ण

	/* COW or ग_लिखो-notअगरy handled on pte level: split pmd. */
	__split_huge_pmd(vmf->vma, vmf->pmd, vmf->address, false, शून्य);

	वापस VM_FAULT_FALLBACK;
पूर्ण

अटल vm_fault_t create_huge_pud(काष्ठा vm_fault *vmf)
अणु
#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE) &&			\
	defined(CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD)
	/* No support क्रम anonymous transparent PUD pages yet */
	अगर (vma_is_anonymous(vmf->vma))
		जाओ split;
	अगर (vmf->vma->vm_ops->huge_fault) अणु
		vm_fault_t ret = vmf->vma->vm_ops->huge_fault(vmf, PE_SIZE_PUD);

		अगर (!(ret & VM_FAULT_FALLBACK))
			वापस ret;
	पूर्ण
split:
	/* COW or ग_लिखो-notअगरy not handled on PUD level: split pud.*/
	__split_huge_pud(vmf->vma, vmf->pud, vmf->address);
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
	वापस VM_FAULT_FALLBACK;
पूर्ण

अटल vm_fault_t wp_huge_pud(काष्ठा vm_fault *vmf, pud_t orig_pud)
अणु
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	/* No support क्रम anonymous transparent PUD pages yet */
	अगर (vma_is_anonymous(vmf->vma))
		वापस VM_FAULT_FALLBACK;
	अगर (vmf->vma->vm_ops->huge_fault)
		वापस vmf->vma->vm_ops->huge_fault(vmf, PE_SIZE_PUD);
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
	वापस VM_FAULT_FALLBACK;
पूर्ण

/*
 * These routines also need to handle stuff like marking pages dirty
 * and/or accessed क्रम architectures that करोn't करो it in hardware (most
 * RISC architectures).  The early dirtying is also good on the i386.
 *
 * There is also a hook called "update_mmu_cache()" that architectures
 * with बाह्यal mmu caches can use to update those (ie the Sparc or
 * PowerPC hashed page tables that act as extended TLBs).
 *
 * We enter with non-exclusive mmap_lock (to exclude vma changes, but allow
 * concurrent faults).
 *
 * The mmap_lock may have been released depending on flags and our वापस value.
 * See filemap_fault() and __lock_page_or_retry().
 */
अटल vm_fault_t handle_pte_fault(काष्ठा vm_fault *vmf)
अणु
	pte_t entry;

	अगर (unlikely(pmd_none(*vmf->pmd))) अणु
		/*
		 * Leave __pte_alloc() until later: because vm_ops->fault may
		 * want to allocate huge page, and अगर we expose page table
		 * क्रम an instant, it will be dअगरficult to retract from
		 * concurrent faults and from rmap lookups.
		 */
		vmf->pte = शून्य;
	पूर्ण अन्यथा अणु
		/*
		 * If a huge pmd materialized under us just retry later.  Use
		 * pmd_trans_unstable() via pmd_devmap_trans_unstable() instead
		 * of pmd_trans_huge() to ensure the pmd didn't become
		 * pmd_trans_huge under us and then back to pmd_none, as a
		 * result of MADV_DONTNEED running immediately after a huge pmd
		 * fault in a dअगरferent thपढ़ो of this mm, in turn leading to a
		 * misleading pmd_trans_huge() retval. All we have to ensure is
		 * that it is a regular pmd that we can walk with
		 * pte_offset_map() and we can करो that through an atomic पढ़ो
		 * in C, which is what pmd_trans_unstable() provides.
		 */
		अगर (pmd_devmap_trans_unstable(vmf->pmd))
			वापस 0;
		/*
		 * A regular pmd is established and it can't morph पूर्णांकo a huge
		 * pmd from under us anymore at this poपूर्णांक because we hold the
		 * mmap_lock पढ़ो mode and khugepaged takes it in ग_लिखो mode.
		 * So now it's safe to run pte_offset_map().
		 */
		vmf->pte = pte_offset_map(vmf->pmd, vmf->address);
		vmf->orig_pte = *vmf->pte;

		/*
		 * some architectures can have larger ptes than wordsize,
		 * e.g.ppc44x-defconfig has CONFIG_PTE_64BIT=y and
		 * CONFIG_32BIT=y, so READ_ONCE cannot guarantee atomic
		 * accesses.  The code below just needs a consistent view
		 * क्रम the अगरs and we later द्विगुन check anyway with the
		 * ptl lock held. So here a barrier will करो.
		 */
		barrier();
		अगर (pte_none(vmf->orig_pte)) अणु
			pte_unmap(vmf->pte);
			vmf->pte = शून्य;
		पूर्ण
	पूर्ण

	अगर (!vmf->pte) अणु
		अगर (vma_is_anonymous(vmf->vma))
			वापस करो_anonymous_page(vmf);
		अन्यथा
			वापस करो_fault(vmf);
	पूर्ण

	अगर (!pte_present(vmf->orig_pte))
		वापस करो_swap_page(vmf);

	अगर (pte_protnone(vmf->orig_pte) && vma_is_accessible(vmf->vma))
		वापस करो_numa_page(vmf);

	vmf->ptl = pte_lockptr(vmf->vma->vm_mm, vmf->pmd);
	spin_lock(vmf->ptl);
	entry = vmf->orig_pte;
	अगर (unlikely(!pte_same(*vmf->pte, entry))) अणु
		update_mmu_tlb(vmf->vma, vmf->address, vmf->pte);
		जाओ unlock;
	पूर्ण
	अगर (vmf->flags & FAULT_FLAG_WRITE) अणु
		अगर (!pte_ग_लिखो(entry))
			वापस करो_wp_page(vmf);
		entry = pte_सूची_गढ़ोty(entry);
	पूर्ण
	entry = pte_mkyoung(entry);
	अगर (ptep_set_access_flags(vmf->vma, vmf->address, vmf->pte, entry,
				vmf->flags & FAULT_FLAG_WRITE)) अणु
		update_mmu_cache(vmf->vma, vmf->address, vmf->pte);
	पूर्ण अन्यथा अणु
		/* Skip spurious TLB flush क्रम retried page fault */
		अगर (vmf->flags & FAULT_FLAG_TRIED)
			जाओ unlock;
		/*
		 * This is needed only क्रम protection faults but the arch code
		 * is not yet telling us अगर this is a protection fault or not.
		 * This still aव्योमs useless tlb flushes क्रम .text page faults
		 * with thपढ़ोs.
		 */
		अगर (vmf->flags & FAULT_FLAG_WRITE)
			flush_tlb_fix_spurious_fault(vmf->vma, vmf->address);
	पूर्ण
unlock:
	pte_unmap_unlock(vmf->pte, vmf->ptl);
	वापस 0;
पूर्ण

/*
 * By the समय we get here, we alपढ़ोy hold the mm semaphore
 *
 * The mmap_lock may have been released depending on flags and our
 * वापस value.  See filemap_fault() and __lock_page_or_retry().
 */
अटल vm_fault_t __handle_mm_fault(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा vm_fault vmf = अणु
		.vma = vma,
		.address = address & PAGE_MASK,
		.flags = flags,
		.pgoff = linear_page_index(vma, address),
		.gfp_mask = __get_fault_gfp_mask(vma),
	पूर्ण;
	अचिन्हित पूर्णांक dirty = flags & FAULT_FLAG_WRITE;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pgd_t *pgd;
	p4d_t *p4d;
	vm_fault_t ret;

	pgd = pgd_offset(mm, address);
	p4d = p4d_alloc(mm, pgd, address);
	अगर (!p4d)
		वापस VM_FAULT_OOM;

	vmf.pud = pud_alloc(mm, p4d, address);
	अगर (!vmf.pud)
		वापस VM_FAULT_OOM;
retry_pud:
	अगर (pud_none(*vmf.pud) && __transparent_hugepage_enabled(vma)) अणु
		ret = create_huge_pud(&vmf);
		अगर (!(ret & VM_FAULT_FALLBACK))
			वापस ret;
	पूर्ण अन्यथा अणु
		pud_t orig_pud = *vmf.pud;

		barrier();
		अगर (pud_trans_huge(orig_pud) || pud_devmap(orig_pud)) अणु

			/* NUMA हाल क्रम anonymous PUDs would go here */

			अगर (dirty && !pud_ग_लिखो(orig_pud)) अणु
				ret = wp_huge_pud(&vmf, orig_pud);
				अगर (!(ret & VM_FAULT_FALLBACK))
					वापस ret;
			पूर्ण अन्यथा अणु
				huge_pud_set_accessed(&vmf, orig_pud);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	vmf.pmd = pmd_alloc(mm, vmf.pud, address);
	अगर (!vmf.pmd)
		वापस VM_FAULT_OOM;

	/* Huge pud page fault raced with pmd_alloc? */
	अगर (pud_trans_unstable(vmf.pud))
		जाओ retry_pud;

	अगर (pmd_none(*vmf.pmd) && __transparent_hugepage_enabled(vma)) अणु
		ret = create_huge_pmd(&vmf);
		अगर (!(ret & VM_FAULT_FALLBACK))
			वापस ret;
	पूर्ण अन्यथा अणु
		pmd_t orig_pmd = *vmf.pmd;

		barrier();
		अगर (unlikely(is_swap_pmd(orig_pmd))) अणु
			VM_BUG_ON(thp_migration_supported() &&
					  !is_pmd_migration_entry(orig_pmd));
			अगर (is_pmd_migration_entry(orig_pmd))
				pmd_migration_entry_रुको(mm, vmf.pmd);
			वापस 0;
		पूर्ण
		अगर (pmd_trans_huge(orig_pmd) || pmd_devmap(orig_pmd)) अणु
			अगर (pmd_protnone(orig_pmd) && vma_is_accessible(vma))
				वापस करो_huge_pmd_numa_page(&vmf, orig_pmd);

			अगर (dirty && !pmd_ग_लिखो(orig_pmd)) अणु
				ret = wp_huge_pmd(&vmf, orig_pmd);
				अगर (!(ret & VM_FAULT_FALLBACK))
					वापस ret;
			पूर्ण अन्यथा अणु
				huge_pmd_set_accessed(&vmf, orig_pmd);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस handle_pte_fault(&vmf);
पूर्ण

/**
 * mm_account_fault - Do page fault accounting
 *
 * @regs: the pt_regs काष्ठा poपूर्णांकer.  When set to शून्य, will skip accounting
 *        of perf event counters, but we'll still करो the per-task accounting to
 *        the task who triggered this page fault.
 * @address: the faulted address.
 * @flags: the fault flags.
 * @ret: the fault retcode.
 *
 * This will take care of most of the page fault accounting.  Meanजबतक, it
 * will also include the PERF_COUNT_SW_PAGE_FAULTS_[MAJ|MIN] perf counter
 * updates.  However, note that the handling of PERF_COUNT_SW_PAGE_FAULTS should
 * still be in per-arch page fault handlers at the entry of page fault.
 */
अटल अंतरभूत व्योम mm_account_fault(काष्ठा pt_regs *regs,
				    अचिन्हित दीर्घ address, अचिन्हित पूर्णांक flags,
				    vm_fault_t ret)
अणु
	bool major;

	/*
	 * We करोn't करो accounting क्रम some specअगरic faults:
	 *
	 * - Unsuccessful faults (e.g. when the address wasn't valid).  That
	 *   includes arch_vma_access_permitted() failing beक्रमe reaching here.
	 *   So this is not a "this many hardware page faults" counter.  We
	 *   should use the hw profiling क्रम that.
	 *
	 * - Incomplete faults (VM_FAULT_RETRY).  They will only be counted
	 *   once they're completed.
	 */
	अगर (ret & (VM_FAULT_ERROR | VM_FAULT_RETRY))
		वापस;

	/*
	 * We define the fault as a major fault when the final successful fault
	 * is VM_FAULT_MAJOR, or अगर it retried (which implies that we couldn't
	 * handle it immediately previously).
	 */
	major = (ret & VM_FAULT_MAJOR) || (flags & FAULT_FLAG_TRIED);

	अगर (major)
		current->maj_flt++;
	अन्यथा
		current->min_flt++;

	/*
	 * If the fault is करोne क्रम GUP, regs will be शून्य.  We only करो the
	 * accounting क्रम the per thपढ़ो fault counters who triggered the
	 * fault, and we skip the perf event updates.
	 */
	अगर (!regs)
		वापस;

	अगर (major)
		perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ, 1, regs, address);
	अन्यथा
		perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN, 1, regs, address);
पूर्ण

/*
 * By the समय we get here, we alपढ़ोy hold the mm semaphore
 *
 * The mmap_lock may have been released depending on flags and our
 * वापस value.  See filemap_fault() and __lock_page_or_retry().
 */
vm_fault_t handle_mm_fault(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			   अचिन्हित पूर्णांक flags, काष्ठा pt_regs *regs)
अणु
	vm_fault_t ret;

	__set_current_state(TASK_RUNNING);

	count_vm_event(PGFAULT);
	count_memcg_event_mm(vma->vm_mm, PGFAULT);

	/* करो counter updates beक्रमe entering really critical section. */
	check_sync_rss_stat(current);

	अगर (!arch_vma_access_permitted(vma, flags & FAULT_FLAG_WRITE,
					    flags & FAULT_FLAG_INSTRUCTION,
					    flags & FAULT_FLAG_REMOTE))
		वापस VM_FAULT_संक_अंश;

	/*
	 * Enable the memcg OOM handling क्रम faults triggered in user
	 * space.  Kernel faults are handled more gracefully.
	 */
	अगर (flags & FAULT_FLAG_USER)
		mem_cgroup_enter_user_fault();

	अगर (unlikely(is_vm_hugetlb_page(vma)))
		ret = hugetlb_fault(vma->vm_mm, vma, address, flags);
	अन्यथा
		ret = __handle_mm_fault(vma, address, flags);

	अगर (flags & FAULT_FLAG_USER) अणु
		mem_cgroup_निकास_user_fault();
		/*
		 * The task may have entered a memcg OOM situation but
		 * अगर the allocation error was handled gracefully (no
		 * VM_FAULT_OOM), there is no need to समाप्त anything.
		 * Just clean up the OOM state peacefully.
		 */
		अगर (task_in_memcg_oom(current) && !(ret & VM_FAULT_OOM))
			mem_cgroup_oom_synchronize(false);
	पूर्ण

	mm_account_fault(regs, address, flags, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(handle_mm_fault);

#अगर_अघोषित __PAGETABLE_P4D_FOLDED
/*
 * Allocate p4d page table.
 * We've alपढ़ोy handled the fast-path in-line.
 */
पूर्णांक __p4d_alloc(काष्ठा mm_काष्ठा *mm, pgd_t *pgd, अचिन्हित दीर्घ address)
अणु
	p4d_t *new = p4d_alloc_one(mm, address);
	अगर (!new)
		वापस -ENOMEM;

	smp_wmb(); /* See comment in __pte_alloc */

	spin_lock(&mm->page_table_lock);
	अगर (pgd_present(*pgd))		/* Another has populated it */
		p4d_मुक्त(mm, new);
	अन्यथा
		pgd_populate(mm, pgd, new);
	spin_unlock(&mm->page_table_lock);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* __PAGETABLE_P4D_FOLDED */

#अगर_अघोषित __PAGETABLE_PUD_FOLDED
/*
 * Allocate page upper directory.
 * We've alपढ़ोy handled the fast-path in-line.
 */
पूर्णांक __pud_alloc(काष्ठा mm_काष्ठा *mm, p4d_t *p4d, अचिन्हित दीर्घ address)
अणु
	pud_t *new = pud_alloc_one(mm, address);
	अगर (!new)
		वापस -ENOMEM;

	smp_wmb(); /* See comment in __pte_alloc */

	spin_lock(&mm->page_table_lock);
	अगर (!p4d_present(*p4d)) अणु
		mm_inc_nr_puds(mm);
		p4d_populate(mm, p4d, new);
	पूर्ण अन्यथा	/* Another has populated it */
		pud_मुक्त(mm, new);
	spin_unlock(&mm->page_table_lock);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* __PAGETABLE_PUD_FOLDED */

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
/*
 * Allocate page middle directory.
 * We've alपढ़ोy handled the fast-path in-line.
 */
पूर्णांक __pmd_alloc(काष्ठा mm_काष्ठा *mm, pud_t *pud, अचिन्हित दीर्घ address)
अणु
	spinlock_t *ptl;
	pmd_t *new = pmd_alloc_one(mm, address);
	अगर (!new)
		वापस -ENOMEM;

	smp_wmb(); /* See comment in __pte_alloc */

	ptl = pud_lock(mm, pud);
	अगर (!pud_present(*pud)) अणु
		mm_inc_nr_pmds(mm);
		pud_populate(mm, pud, new);
	पूर्ण अन्यथा	/* Another has populated it */
		pmd_मुक्त(mm, new);
	spin_unlock(ptl);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* __PAGETABLE_PMD_FOLDED */

पूर्णांक follow_invalidate_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
			  काष्ठा mmu_notअगरier_range *range, pte_t **ptepp,
			  pmd_t **pmdpp, spinlock_t **ptlp)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *ptep;

	pgd = pgd_offset(mm, address);
	अगर (pgd_none(*pgd) || unlikely(pgd_bad(*pgd)))
		जाओ out;

	p4d = p4d_offset(pgd, address);
	अगर (p4d_none(*p4d) || unlikely(p4d_bad(*p4d)))
		जाओ out;

	pud = pud_offset(p4d, address);
	अगर (pud_none(*pud) || unlikely(pud_bad(*pud)))
		जाओ out;

	pmd = pmd_offset(pud, address);
	VM_BUG_ON(pmd_trans_huge(*pmd));

	अगर (pmd_huge(*pmd)) अणु
		अगर (!pmdpp)
			जाओ out;

		अगर (range) अणु
			mmu_notअगरier_range_init(range, MMU_NOTIFY_CLEAR, 0,
						शून्य, mm, address & PMD_MASK,
						(address & PMD_MASK) + PMD_SIZE);
			mmu_notअगरier_invalidate_range_start(range);
		पूर्ण
		*ptlp = pmd_lock(mm, pmd);
		अगर (pmd_huge(*pmd)) अणु
			*pmdpp = pmd;
			वापस 0;
		पूर्ण
		spin_unlock(*ptlp);
		अगर (range)
			mmu_notअगरier_invalidate_range_end(range);
	पूर्ण

	अगर (pmd_none(*pmd) || unlikely(pmd_bad(*pmd)))
		जाओ out;

	अगर (range) अणु
		mmu_notअगरier_range_init(range, MMU_NOTIFY_CLEAR, 0, शून्य, mm,
					address & PAGE_MASK,
					(address & PAGE_MASK) + PAGE_SIZE);
		mmu_notअगरier_invalidate_range_start(range);
	पूर्ण
	ptep = pte_offset_map_lock(mm, pmd, address, ptlp);
	अगर (!pte_present(*ptep))
		जाओ unlock;
	*ptepp = ptep;
	वापस 0;
unlock:
	pte_unmap_unlock(ptep, *ptlp);
	अगर (range)
		mmu_notअगरier_invalidate_range_end(range);
out:
	वापस -EINVAL;
पूर्ण

/**
 * follow_pte - look up PTE at a user भव address
 * @mm: the mm_काष्ठा of the target address space
 * @address: user भव address
 * @ptepp: location to store found PTE
 * @ptlp: location to store the lock क्रम the PTE
 *
 * On a successful वापस, the poपूर्णांकer to the PTE is stored in @ptepp;
 * the corresponding lock is taken and its location is stored in @ptlp.
 * The contents of the PTE are only stable until @ptlp is released;
 * any further use, अगर any, must be रक्षित against invalidation
 * with MMU notअगरiers.
 *
 * Only IO mappings and raw PFN mappings are allowed.  The mmap semaphore
 * should be taken क्रम पढ़ो.
 *
 * KVM uses this function.  While it is arguably less bad than ``follow_pfn``,
 * it is not a good general-purpose API.
 *
 * Return: zero on success, -ve otherwise.
 */
पूर्णांक follow_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
	       pte_t **ptepp, spinlock_t **ptlp)
अणु
	वापस follow_invalidate_pte(mm, address, शून्य, ptepp, शून्य, ptlp);
पूर्ण
EXPORT_SYMBOL_GPL(follow_pte);

/**
 * follow_pfn - look up PFN at a user भव address
 * @vma: memory mapping
 * @address: user भव address
 * @pfn: location to store found PFN
 *
 * Only IO mappings and raw PFN mappings are allowed.
 *
 * This function करोes not allow the caller to पढ़ो the permissions
 * of the PTE.  Do not use it.
 *
 * Return: zero and the pfn at @pfn on success, -ve otherwise.
 */
पूर्णांक follow_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
	अचिन्हित दीर्घ *pfn)
अणु
	पूर्णांक ret = -EINVAL;
	spinlock_t *ptl;
	pte_t *ptep;

	अगर (!(vma->vm_flags & (VM_IO | VM_PFNMAP)))
		वापस ret;

	ret = follow_pte(vma->vm_mm, address, &ptep, &ptl);
	अगर (ret)
		वापस ret;
	*pfn = pte_pfn(*ptep);
	pte_unmap_unlock(ptep, ptl);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(follow_pfn);

#अगर_घोषित CONFIG_HAVE_IOREMAP_PROT
पूर्णांक follow_phys(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, अचिन्हित पूर्णांक flags,
		अचिन्हित दीर्घ *prot, resource_माप_प्रकार *phys)
अणु
	पूर्णांक ret = -EINVAL;
	pte_t *ptep, pte;
	spinlock_t *ptl;

	अगर (!(vma->vm_flags & (VM_IO | VM_PFNMAP)))
		जाओ out;

	अगर (follow_pte(vma->vm_mm, address, &ptep, &ptl))
		जाओ out;
	pte = *ptep;

	अगर ((flags & FOLL_WRITE) && !pte_ग_लिखो(pte))
		जाओ unlock;

	*prot = pgprot_val(pte_pgprot(pte));
	*phys = (resource_माप_प्रकार)pte_pfn(pte) << PAGE_SHIFT;

	ret = 0;
unlock:
	pte_unmap_unlock(ptep, ptl);
out:
	वापस ret;
पूर्ण

/**
 * generic_access_phys - generic implementation क्रम iomem mmap access
 * @vma: the vma to access
 * @addr: userspace address, not relative offset within @vma
 * @buf: buffer to पढ़ो/ग_लिखो
 * @len: length of transfer
 * @ग_लिखो: set to FOLL_WRITE when writing, otherwise पढ़ोing
 *
 * This is a generic implementation क्रम &vm_operations_काष्ठा.access क्रम an
 * iomem mapping. This callback is used by access_process_vm() when the @vma is
 * not page based.
 */
पूर्णांक generic_access_phys(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो)
अणु
	resource_माप_प्रकार phys_addr;
	अचिन्हित दीर्घ prot = 0;
	व्योम __iomem *maddr;
	pte_t *ptep, pte;
	spinlock_t *ptl;
	पूर्णांक offset = offset_in_page(addr);
	पूर्णांक ret = -EINVAL;

	अगर (!(vma->vm_flags & (VM_IO | VM_PFNMAP)))
		वापस -EINVAL;

retry:
	अगर (follow_pte(vma->vm_mm, addr, &ptep, &ptl))
		वापस -EINVAL;
	pte = *ptep;
	pte_unmap_unlock(ptep, ptl);

	prot = pgprot_val(pte_pgprot(pte));
	phys_addr = (resource_माप_प्रकार)pte_pfn(pte) << PAGE_SHIFT;

	अगर ((ग_लिखो & FOLL_WRITE) && !pte_ग_लिखो(pte))
		वापस -EINVAL;

	maddr = ioremap_prot(phys_addr, PAGE_ALIGN(len + offset), prot);
	अगर (!maddr)
		वापस -ENOMEM;

	अगर (follow_pte(vma->vm_mm, addr, &ptep, &ptl))
		जाओ out_unmap;

	अगर (!pte_same(pte, *ptep)) अणु
		pte_unmap_unlock(ptep, ptl);
		iounmap(maddr);

		जाओ retry;
	पूर्ण

	अगर (ग_लिखो)
		स_नकल_toio(maddr + offset, buf, len);
	अन्यथा
		स_नकल_fromio(buf, maddr + offset, len);
	ret = len;
	pte_unmap_unlock(ptep, ptl);
out_unmap:
	iounmap(maddr);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(generic_access_phys);
#पूर्ण_अगर

/*
 * Access another process' address space as given in mm.
 */
पूर्णांक __access_remote_vm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, व्योम *buf,
		       पूर्णांक len, अचिन्हित पूर्णांक gup_flags)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	व्योम *old_buf = buf;
	पूर्णांक ग_लिखो = gup_flags & FOLL_WRITE;

	अगर (mmap_पढ़ो_lock_समाप्तable(mm))
		वापस 0;

	/* ignore errors, just check how much was successfully transferred */
	जबतक (len) अणु
		पूर्णांक bytes, ret, offset;
		व्योम *maddr;
		काष्ठा page *page = शून्य;

		ret = get_user_pages_remote(mm, addr, 1,
				gup_flags, &page, &vma, शून्य);
		अगर (ret <= 0) अणु
#अगर_अघोषित CONFIG_HAVE_IOREMAP_PROT
			अवरोध;
#अन्यथा
			/*
			 * Check अगर this is a VM_IO | VM_PFNMAP VMA, which
			 * we can access using slightly dअगरferent code.
			 */
			vma = find_vma(mm, addr);
			अगर (!vma || vma->vm_start > addr)
				अवरोध;
			अगर (vma->vm_ops && vma->vm_ops->access)
				ret = vma->vm_ops->access(vma, addr, buf,
							  len, ग_लिखो);
			अगर (ret <= 0)
				अवरोध;
			bytes = ret;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			bytes = len;
			offset = addr & (PAGE_SIZE-1);
			अगर (bytes > PAGE_SIZE-offset)
				bytes = PAGE_SIZE-offset;

			maddr = kmap(page);
			अगर (ग_लिखो) अणु
				copy_to_user_page(vma, page, addr,
						  maddr + offset, buf, bytes);
				set_page_dirty_lock(page);
			पूर्ण अन्यथा अणु
				copy_from_user_page(vma, page, addr,
						    buf, maddr + offset, bytes);
			पूर्ण
			kunmap(page);
			put_page(page);
		पूर्ण
		len -= bytes;
		buf += bytes;
		addr += bytes;
	पूर्ण
	mmap_पढ़ो_unlock(mm);

	वापस buf - old_buf;
पूर्ण

/**
 * access_remote_vm - access another process' address space
 * @mm:		the mm_काष्ठा of the target address space
 * @addr:	start address to access
 * @buf:	source or destination buffer
 * @len:	number of bytes to transfer
 * @gup_flags:	flags modअगरying lookup behaviour
 *
 * The caller must hold a reference on @mm.
 *
 * Return: number of bytes copied from source to destination.
 */
पूर्णांक access_remote_vm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		व्योम *buf, पूर्णांक len, अचिन्हित पूर्णांक gup_flags)
अणु
	वापस __access_remote_vm(mm, addr, buf, len, gup_flags);
पूर्ण

/*
 * Access another process' address space.
 * Source/target buffer must be kernel space,
 * Do not walk the page table directly, use get_user_pages
 */
पूर्णांक access_process_vm(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ addr,
		व्योम *buf, पूर्णांक len, अचिन्हित पूर्णांक gup_flags)
अणु
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक ret;

	mm = get_task_mm(tsk);
	अगर (!mm)
		वापस 0;

	ret = __access_remote_vm(mm, addr, buf, len, gup_flags);

	mmput(mm);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(access_process_vm);

/*
 * Prपूर्णांक the name of a VMA.
 */
व्योम prपूर्णांक_vma_addr(अक्षर *prefix, अचिन्हित दीर्घ ip)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;

	/*
	 * we might be running from an atomic context so we cannot sleep
	 */
	अगर (!mmap_पढ़ो_trylock(mm))
		वापस;

	vma = find_vma(mm, ip);
	अगर (vma && vma->vm_file) अणु
		काष्ठा file *f = vma->vm_file;
		अक्षर *buf = (अक्षर *)__get_मुक्त_page(GFP_NOWAIT);
		अगर (buf) अणु
			अक्षर *p;

			p = file_path(f, buf, PAGE_SIZE);
			अगर (IS_ERR(p))
				p = "?";
			prपूर्णांकk("%s%s[%lx+%lx]", prefix, kbasename(p),
					vma->vm_start,
					vma->vm_end - vma->vm_start);
			मुक्त_page((अचिन्हित दीर्घ)buf);
		पूर्ण
	पूर्ण
	mmap_पढ़ो_unlock(mm);
पूर्ण

#अगर defined(CONFIG_PROVE_LOCKING) || defined(CONFIG_DEBUG_ATOMIC_SLEEP)
व्योम __might_fault(स्थिर अक्षर *file, पूर्णांक line)
अणु
	/*
	 * Some code (nfs/sunrpc) uses socket ops on kernel memory जबतक
	 * holding the mmap_lock, this is safe because kernel memory करोesn't
	 * get paged out, thereक्रमe we'll never actually fault, and the
	 * below annotations will generate false positives.
	 */
	अगर (uaccess_kernel())
		वापस;
	अगर (pagefault_disabled())
		वापस;
	__might_sleep(file, line, 0);
#अगर defined(CONFIG_DEBUG_ATOMIC_SLEEP)
	अगर (current->mm)
		might_lock_पढ़ो(&current->mm->mmap_lock);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(__might_fault);
#पूर्ण_अगर

#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE) || defined(CONFIG_HUGETLBFS)
/*
 * Process all subpages of the specअगरied huge page with the specअगरied
 * operation.  The target subpage will be processed last to keep its
 * cache lines hot.
 */
अटल अंतरभूत व्योम process_huge_page(
	अचिन्हित दीर्घ addr_hपूर्णांक, अचिन्हित पूर्णांक pages_per_huge_page,
	व्योम (*process_subpage)(अचिन्हित दीर्घ addr, पूर्णांक idx, व्योम *arg),
	व्योम *arg)
अणु
	पूर्णांक i, n, base, l;
	अचिन्हित दीर्घ addr = addr_hपूर्णांक &
		~(((अचिन्हित दीर्घ)pages_per_huge_page << PAGE_SHIFT) - 1);

	/* Process target subpage last to keep its cache lines hot */
	might_sleep();
	n = (addr_hपूर्णांक - addr) / PAGE_SIZE;
	अगर (2 * n <= pages_per_huge_page) अणु
		/* If target subpage in first half of huge page */
		base = 0;
		l = n;
		/* Process subpages at the end of huge page */
		क्रम (i = pages_per_huge_page - 1; i >= 2 * n; i--) अणु
			cond_resched();
			process_subpage(addr + i * PAGE_SIZE, i, arg);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If target subpage in second half of huge page */
		base = pages_per_huge_page - 2 * (pages_per_huge_page - n);
		l = pages_per_huge_page - n;
		/* Process subpages at the begin of huge page */
		क्रम (i = 0; i < base; i++) अणु
			cond_resched();
			process_subpage(addr + i * PAGE_SIZE, i, arg);
		पूर्ण
	पूर्ण
	/*
	 * Process reमुख्यing subpages in left-right-left-right pattern
	 * towards the target subpage
	 */
	क्रम (i = 0; i < l; i++) अणु
		पूर्णांक left_idx = base + i;
		पूर्णांक right_idx = base + 2 * l - 1 - i;

		cond_resched();
		process_subpage(addr + left_idx * PAGE_SIZE, left_idx, arg);
		cond_resched();
		process_subpage(addr + right_idx * PAGE_SIZE, right_idx, arg);
	पूर्ण
पूर्ण

अटल व्योम clear_gigantic_page(काष्ठा page *page,
				अचिन्हित दीर्घ addr,
				अचिन्हित पूर्णांक pages_per_huge_page)
अणु
	पूर्णांक i;
	काष्ठा page *p = page;

	might_sleep();
	क्रम (i = 0; i < pages_per_huge_page;
	     i++, p = mem_map_next(p, page, i)) अणु
		cond_resched();
		clear_user_highpage(p, addr + i * PAGE_SIZE);
	पूर्ण
पूर्ण

अटल व्योम clear_subpage(अचिन्हित दीर्घ addr, पूर्णांक idx, व्योम *arg)
अणु
	काष्ठा page *page = arg;

	clear_user_highpage(page + idx, addr);
पूर्ण

व्योम clear_huge_page(काष्ठा page *page,
		     अचिन्हित दीर्घ addr_hपूर्णांक, अचिन्हित पूर्णांक pages_per_huge_page)
अणु
	अचिन्हित दीर्घ addr = addr_hपूर्णांक &
		~(((अचिन्हित दीर्घ)pages_per_huge_page << PAGE_SHIFT) - 1);

	अगर (unlikely(pages_per_huge_page > MAX_ORDER_NR_PAGES)) अणु
		clear_gigantic_page(page, addr, pages_per_huge_page);
		वापस;
	पूर्ण

	process_huge_page(addr_hपूर्णांक, pages_per_huge_page, clear_subpage, page);
पूर्ण

अटल व्योम copy_user_gigantic_page(काष्ठा page *dst, काष्ठा page *src,
				    अचिन्हित दीर्घ addr,
				    काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित पूर्णांक pages_per_huge_page)
अणु
	पूर्णांक i;
	काष्ठा page *dst_base = dst;
	काष्ठा page *src_base = src;

	क्रम (i = 0; i < pages_per_huge_page; ) अणु
		cond_resched();
		copy_user_highpage(dst, src, addr + i*PAGE_SIZE, vma);

		i++;
		dst = mem_map_next(dst, dst_base, i);
		src = mem_map_next(src, src_base, i);
	पूर्ण
पूर्ण

काष्ठा copy_subpage_arg अणु
	काष्ठा page *dst;
	काष्ठा page *src;
	काष्ठा vm_area_काष्ठा *vma;
पूर्ण;

अटल व्योम copy_subpage(अचिन्हित दीर्घ addr, पूर्णांक idx, व्योम *arg)
अणु
	काष्ठा copy_subpage_arg *copy_arg = arg;

	copy_user_highpage(copy_arg->dst + idx, copy_arg->src + idx,
			   addr, copy_arg->vma);
पूर्ण

व्योम copy_user_huge_page(काष्ठा page *dst, काष्ठा page *src,
			 अचिन्हित दीर्घ addr_hपूर्णांक, काष्ठा vm_area_काष्ठा *vma,
			 अचिन्हित पूर्णांक pages_per_huge_page)
अणु
	अचिन्हित दीर्घ addr = addr_hपूर्णांक &
		~(((अचिन्हित दीर्घ)pages_per_huge_page << PAGE_SHIFT) - 1);
	काष्ठा copy_subpage_arg arg = अणु
		.dst = dst,
		.src = src,
		.vma = vma,
	पूर्ण;

	अगर (unlikely(pages_per_huge_page > MAX_ORDER_NR_PAGES)) अणु
		copy_user_gigantic_page(dst, src, addr, vma,
					pages_per_huge_page);
		वापस;
	पूर्ण

	process_huge_page(addr_hपूर्णांक, pages_per_huge_page, copy_subpage, &arg);
पूर्ण

दीर्घ copy_huge_page_from_user(काष्ठा page *dst_page,
				स्थिर व्योम __user *usr_src,
				अचिन्हित पूर्णांक pages_per_huge_page,
				bool allow_pagefault)
अणु
	व्योम *src = (व्योम *)usr_src;
	व्योम *page_kaddr;
	अचिन्हित दीर्घ i, rc = 0;
	अचिन्हित दीर्घ ret_val = pages_per_huge_page * PAGE_SIZE;
	काष्ठा page *subpage = dst_page;

	क्रम (i = 0; i < pages_per_huge_page;
	     i++, subpage = mem_map_next(subpage, dst_page, i)) अणु
		अगर (allow_pagefault)
			page_kaddr = kmap(subpage);
		अन्यथा
			page_kaddr = kmap_atomic(subpage);
		rc = copy_from_user(page_kaddr,
				(स्थिर व्योम __user *)(src + i * PAGE_SIZE),
				PAGE_SIZE);
		अगर (allow_pagefault)
			kunmap(subpage);
		अन्यथा
			kunmap_atomic(page_kaddr);

		ret_val -= (PAGE_SIZE - rc);
		अगर (rc)
			अवरोध;

		cond_resched();
	पूर्ण
	वापस ret_val;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE || CONFIG_HUGETLBFS */

#अगर USE_SPLIT_PTE_PTLOCKS && ALLOC_SPLIT_PTLOCKS

अटल काष्ठा kmem_cache *page_ptl_cachep;

व्योम __init ptlock_cache_init(व्योम)
अणु
	page_ptl_cachep = kmem_cache_create("page->ptl", माप(spinlock_t), 0,
			SLAB_PANIC, शून्य);
पूर्ण

bool ptlock_alloc(काष्ठा page *page)
अणु
	spinlock_t *ptl;

	ptl = kmem_cache_alloc(page_ptl_cachep, GFP_KERNEL);
	अगर (!ptl)
		वापस false;
	page->ptl = ptl;
	वापस true;
पूर्ण

व्योम ptlock_मुक्त(काष्ठा page *page)
अणु
	kmem_cache_मुक्त(page_ptl_cachep, page->ptl);
पूर्ण
#पूर्ण_अगर
