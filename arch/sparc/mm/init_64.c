<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  arch/sparc64/mm/init.c
 *
 *  Copyright (C) 1996-1999 David S. Miller (davem@caip.rutgers.edu)
 *  Copyright (C) 1997-1999 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */
 
#समावेश <linux/extable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/initrd.h>
#समावेश <linux/swap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/poison.h>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/cache.h>
#समावेश <linux/sort.h>
#समावेश <linux/ioport.h>
#समावेश <linux/percpu.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/head.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/starfire.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tsb.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mdesc.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>

#समावेश "init_64.h"

अचिन्हित दीर्घ kern_linear_pte_xor[4] __पढ़ो_mostly;
अटल अचिन्हित दीर्घ page_cache4v_flag;

/* A biपंचांगap, two bits क्रम every 256MB of physical memory.  These two
 * bits determine what page size we use क्रम kernel linear
 * translations.  They क्रमm an index पूर्णांकo kern_linear_pte_xor[].  The
 * value in the indexed slot is XOR'd with the TLB miss भव
 * address to क्रमm the resulting TTE.  The mapping is:
 *
 *	0	==>	4MB
 *	1	==>	256MB
 *	2	==>	2GB
 *	3	==>	16GB
 *
 * All sun4v chips support 256MB pages.  Only SPARC-T4 and later
 * support 2GB pages, and hopefully future cpus will support the 16GB
 * pages as well.  For slots 2 and 3, we encode a 256MB TTE xor there
 * अगर these larger page sizes are not supported by the cpu.
 *
 * It would be nice to determine this from the machine description
 * 'cpu' properties, but we need to have this table setup beक्रमe the
 * MDESC is initialized.
 */

#अगर_अघोषित CONFIG_DEBUG_PAGEALLOC
/* A special kernel TSB क्रम 4MB, 256MB, 2GB and 16GB linear mappings.
 * Space is allocated क्रम this right after the trap table in
 * arch/sparc64/kernel/head.S
 */
बाह्य काष्ठा tsb swapper_4m_tsb[KERNEL_TSB4M_NENTRIES];
#पूर्ण_अगर
बाह्य काष्ठा tsb swapper_tsb[KERNEL_TSB_NENTRIES];

अटल अचिन्हित दीर्घ cpu_pgsz_mask;

#घोषणा MAX_BANKS	1024

अटल काष्ठा linux_prom64_रेजिस्टरs pavail[MAX_BANKS];
अटल पूर्णांक pavail_ents;

u64 numa_latency[MAX_NUMNODES][MAX_NUMNODES];

अटल पूर्णांक cmp_p64(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *x = a, *y = b;

	अगर (x->phys_addr > y->phys_addr)
		वापस 1;
	अगर (x->phys_addr < y->phys_addr)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम __init पढ़ो_obp_memory(स्थिर अक्षर *property,
				   काष्ठा linux_prom64_रेजिस्टरs *regs,
				   पूर्णांक *num_ents)
अणु
	phandle node = prom_finddevice("/memory");
	पूर्णांक prop_size = prom_getproplen(node, property);
	पूर्णांक ents, ret, i;

	ents = prop_size / माप(काष्ठा linux_prom64_रेजिस्टरs);
	अगर (ents > MAX_BANKS) अणु
		prom_म_लिखो("The machine has more %s property entries than "
			    "this kernel can support (%d).\n",
			    property, MAX_BANKS);
		prom_halt();
	पूर्ण

	ret = prom_getproperty(node, property, (अक्षर *) regs, prop_size);
	अगर (ret == -1) अणु
		prom_म_लिखो("Couldn't get %s property from /memory.\n",
				property);
		prom_halt();
	पूर्ण

	/* Sanitize what we got from the firmware, by page aligning
	 * everything.
	 */
	क्रम (i = 0; i < ents; i++) अणु
		अचिन्हित दीर्घ base, size;

		base = regs[i].phys_addr;
		size = regs[i].reg_size;

		size &= PAGE_MASK;
		अगर (base & ~PAGE_MASK) अणु
			अचिन्हित दीर्घ new_base = PAGE_ALIGN(base);

			size -= new_base - base;
			अगर ((दीर्घ) size < 0L)
				size = 0UL;
			base = new_base;
		पूर्ण
		अगर (size == 0UL) अणु
			/* If it is empty, simply get rid of it.
			 * This simplअगरies the logic of the other
			 * functions that process these arrays.
			 */
			स_हटाओ(&regs[i], &regs[i + 1],
				(ents - i - 1) * माप(regs[0]));
			i--;
			ents--;
			जारी;
		पूर्ण
		regs[i].phys_addr = base;
		regs[i].reg_size = size;
	पूर्ण

	*num_ents = ents;

	sort(regs, ents, माप(काष्ठा linux_prom64_रेजिस्टरs),
	     cmp_p64, शून्य);
पूर्ण

/* Kernel physical address base and size in bytes.  */
अचिन्हित दीर्घ kern_base __पढ़ो_mostly;
अचिन्हित दीर्घ kern_size __पढ़ो_mostly;

/* Initial ramdisk setup */
बाह्य अचिन्हित दीर्घ sparc_ramdisk_image64;
बाह्य अचिन्हित पूर्णांक sparc_ramdisk_image;
बाह्य अचिन्हित पूर्णांक sparc_ramdisk_size;

काष्ठा page *mem_map_zero __पढ़ो_mostly;
EXPORT_SYMBOL(mem_map_zero);

अचिन्हित पूर्णांक sparc64_highest_unlocked_tlb_ent __पढ़ो_mostly;

अचिन्हित दीर्घ sparc64_kern_pri_context __पढ़ो_mostly;
अचिन्हित दीर्घ sparc64_kern_pri_nuc_bits __पढ़ो_mostly;
अचिन्हित दीर्घ sparc64_kern_sec_context __पढ़ो_mostly;

पूर्णांक num_kernel_image_mappings;

#अगर_घोषित CONFIG_DEBUG_DCFLUSH
atomic_t dcpage_flushes = ATOMIC_INIT(0);
#अगर_घोषित CONFIG_SMP
atomic_t dcpage_flushes_xcall = ATOMIC_INIT(0);
#पूर्ण_अगर
#पूर्ण_अगर

अंतरभूत व्योम flush_dcache_page_impl(काष्ठा page *page)
अणु
	BUG_ON(tlb_type == hypervisor);
#अगर_घोषित CONFIG_DEBUG_DCFLUSH
	atomic_inc(&dcpage_flushes);
#पूर्ण_अगर

#अगर_घोषित DCACHE_ALIASING_POSSIBLE
	__flush_dcache_page(page_address(page),
			    ((tlb_type == spitfire) &&
			     page_mapping_file(page) != शून्य));
#अन्यथा
	अगर (page_mapping_file(page) != शून्य &&
	    tlb_type == spitfire)
		__flush_icache_page(__pa(page_address(page)));
#पूर्ण_अगर
पूर्ण

#घोषणा PG_dcache_dirty		PG_arch_1
#घोषणा PG_dcache_cpu_shअगरt	32UL
#घोषणा PG_dcache_cpu_mask	\
	((1UL<<ilog2(roundup_घात_of_two(NR_CPUS)))-1UL)

#घोषणा dcache_dirty_cpu(page) \
	(((page)->flags >> PG_dcache_cpu_shअगरt) & PG_dcache_cpu_mask)

अटल अंतरभूत व्योम set_dcache_dirty(काष्ठा page *page, पूर्णांक this_cpu)
अणु
	अचिन्हित दीर्घ mask = this_cpu;
	अचिन्हित दीर्घ non_cpu_bits;

	non_cpu_bits = ~(PG_dcache_cpu_mask << PG_dcache_cpu_shअगरt);
	mask = (mask << PG_dcache_cpu_shअगरt) | (1UL << PG_dcache_dirty);

	__यंत्र__ __अस्थिर__("1:\n\t"
			     "ldx	[%2], %%g7\n\t"
			     "and	%%g7, %1, %%g1\n\t"
			     "or	%%g1, %0, %%g1\n\t"
			     "casx	[%2], %%g7, %%g1\n\t"
			     "cmp	%%g7, %%g1\n\t"
			     "bne,pn	%%xcc, 1b\n\t"
			     " nop"
			     : /* no outमाला_दो */
			     : "r" (mask), "r" (non_cpu_bits), "r" (&page->flags)
			     : "g1", "g7");
पूर्ण

अटल अंतरभूत व्योम clear_dcache_dirty_cpu(काष्ठा page *page, अचिन्हित दीर्घ cpu)
अणु
	अचिन्हित दीर्घ mask = (1UL << PG_dcache_dirty);

	__यंत्र__ __अस्थिर__("! test_and_clear_dcache_dirty\n"
			     "1:\n\t"
			     "ldx	[%2], %%g7\n\t"
			     "srlx	%%g7, %4, %%g1\n\t"
			     "and	%%g1, %3, %%g1\n\t"
			     "cmp	%%g1, %0\n\t"
			     "bne,pn	%%icc, 2f\n\t"
			     " andn	%%g7, %1, %%g1\n\t"
			     "casx	[%2], %%g7, %%g1\n\t"
			     "cmp	%%g7, %%g1\n\t"
			     "bne,pn	%%xcc, 1b\n\t"
			     " nop\n"
			     "2:"
			     : /* no outमाला_दो */
			     : "r" (cpu), "r" (mask), "r" (&page->flags),
			       "i" (PG_dcache_cpu_mask),
			       "i" (PG_dcache_cpu_shअगरt)
			     : "g1", "g7");
पूर्ण

अटल अंतरभूत व्योम tsb_insert(काष्ठा tsb *ent, अचिन्हित दीर्घ tag, अचिन्हित दीर्घ pte)
अणु
	अचिन्हित दीर्घ tsb_addr = (अचिन्हित दीर्घ) ent;

	अगर (tlb_type == cheetah_plus || tlb_type == hypervisor)
		tsb_addr = __pa(tsb_addr);

	__tsb_insert(tsb_addr, tag, pte);
पूर्ण

अचिन्हित दीर्घ _PAGE_ALL_SZ_BITS __पढ़ो_mostly;

अटल व्योम flush_dcache(अचिन्हित दीर्घ pfn)
अणु
	काष्ठा page *page;

	page = pfn_to_page(pfn);
	अगर (page) अणु
		अचिन्हित दीर्घ pg_flags;

		pg_flags = page->flags;
		अगर (pg_flags & (1UL << PG_dcache_dirty)) अणु
			पूर्णांक cpu = ((pg_flags >> PG_dcache_cpu_shअगरt) &
				   PG_dcache_cpu_mask);
			पूर्णांक this_cpu = get_cpu();

			/* This is just to optimize away some function calls
			 * in the SMP हाल.
			 */
			अगर (cpu == this_cpu)
				flush_dcache_page_impl(page);
			अन्यथा
				smp_flush_dcache_page_impl(page, cpu);

			clear_dcache_dirty_cpu(page, cpu);

			put_cpu();
		पूर्ण
	पूर्ण
पूर्ण

/* mm->context.lock must be held */
अटल व्योम __update_mmu_tsb_insert(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ tsb_index,
				    अचिन्हित दीर्घ tsb_hash_shअगरt, अचिन्हित दीर्घ address,
				    अचिन्हित दीर्घ tte)
अणु
	काष्ठा tsb *tsb = mm->context.tsb_block[tsb_index].tsb;
	अचिन्हित दीर्घ tag;

	अगर (unlikely(!tsb))
		वापस;

	tsb += ((address >> tsb_hash_shअगरt) &
		(mm->context.tsb_block[tsb_index].tsb_nentries - 1UL));
	tag = (address >> 22UL);
	tsb_insert(tsb, tag, tte);
पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
अटल पूर्णांक __init hugetlbpage_init(व्योम)
अणु
	hugetlb_add_hstate(HPAGE_64K_SHIFT - PAGE_SHIFT);
	hugetlb_add_hstate(HPAGE_SHIFT - PAGE_SHIFT);
	hugetlb_add_hstate(HPAGE_256MB_SHIFT - PAGE_SHIFT);
	hugetlb_add_hstate(HPAGE_2GB_SHIFT - PAGE_SHIFT);

	वापस 0;
पूर्ण

arch_initcall(hugetlbpage_init);

अटल व्योम __init pud_huge_patch(व्योम)
अणु
	काष्ठा pud_huge_patch_entry *p;
	अचिन्हित दीर्घ addr;

	p = &__pud_huge_patch;
	addr = p->addr;
	*(अचिन्हित पूर्णांक *)addr = p->insn;

	__यंत्र__ __अस्थिर__("flush %0" : : "r" (addr));
पूर्ण

bool __init arch_hugetlb_valid_size(अचिन्हित दीर्घ size)
अणु
	अचिन्हित पूर्णांक hugepage_shअगरt = ilog2(size);
	अचिन्हित लघु hv_pgsz_idx;
	अचिन्हित पूर्णांक hv_pgsz_mask;

	चयन (hugepage_shअगरt) अणु
	हाल HPAGE_16GB_SHIFT:
		hv_pgsz_mask = HV_PGSZ_MASK_16GB;
		hv_pgsz_idx = HV_PGSZ_IDX_16GB;
		pud_huge_patch();
		अवरोध;
	हाल HPAGE_2GB_SHIFT:
		hv_pgsz_mask = HV_PGSZ_MASK_2GB;
		hv_pgsz_idx = HV_PGSZ_IDX_2GB;
		अवरोध;
	हाल HPAGE_256MB_SHIFT:
		hv_pgsz_mask = HV_PGSZ_MASK_256MB;
		hv_pgsz_idx = HV_PGSZ_IDX_256MB;
		अवरोध;
	हाल HPAGE_SHIFT:
		hv_pgsz_mask = HV_PGSZ_MASK_4MB;
		hv_pgsz_idx = HV_PGSZ_IDX_4MB;
		अवरोध;
	हाल HPAGE_64K_SHIFT:
		hv_pgsz_mask = HV_PGSZ_MASK_64K;
		hv_pgsz_idx = HV_PGSZ_IDX_64K;
		अवरोध;
	शेष:
		hv_pgsz_mask = 0;
	पूर्ण

	अगर ((hv_pgsz_mask & cpu_pgsz_mask) == 0U)
		वापस false;

	वापस true;
पूर्ण
#पूर्ण_अगर	/* CONFIG_HUGETLB_PAGE */

व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ flags;
	bool is_huge_tsb;
	pte_t pte = *ptep;

	अगर (tlb_type != hypervisor) अणु
		अचिन्हित दीर्घ pfn = pte_pfn(pte);

		अगर (pfn_valid(pfn))
			flush_dcache(pfn);
	पूर्ण

	mm = vma->vm_mm;

	/* Don't insert a non-valid PTE into the TSB, we'll deadlock.  */
	अगर (!pte_accessible(mm, pte))
		वापस;

	spin_lock_irqsave(&mm->context.lock, flags);

	is_huge_tsb = false;
#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	अगर (mm->context.hugetlb_pte_count || mm->context.thp_pte_count) अणु
		अचिन्हित दीर्घ hugepage_size = PAGE_SIZE;

		अगर (is_vm_hugetlb_page(vma))
			hugepage_size = huge_page_size(hstate_vma(vma));

		अगर (hugepage_size >= PUD_SIZE) अणु
			अचिन्हित दीर्घ mask = 0x1ffc00000UL;

			/* Transfer bits [32:22] from address to resolve
			 * at 4M granularity.
			 */
			pte_val(pte) &= ~mask;
			pte_val(pte) |= (address & mask);
		पूर्ण अन्यथा अगर (hugepage_size >= PMD_SIZE) अणु
			/* We are fabricating 8MB pages using 4MB
			 * real hw pages.
			 */
			pte_val(pte) |= (address & (1UL << REAL_HPAGE_SHIFT));
		पूर्ण

		अगर (hugepage_size >= PMD_SIZE) अणु
			__update_mmu_tsb_insert(mm, MM_TSB_HUGE,
				REAL_HPAGE_SHIFT, address, pte_val(pte));
			is_huge_tsb = true;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (!is_huge_tsb)
		__update_mmu_tsb_insert(mm, MM_TSB_BASE, PAGE_SHIFT,
					address, pte_val(pte));

	spin_unlock_irqrestore(&mm->context.lock, flags);
पूर्ण

व्योम flush_dcache_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping;
	पूर्णांक this_cpu;

	अगर (tlb_type == hypervisor)
		वापस;

	/* Do not bother with the expensive D-cache flush अगर it
	 * is merely the zero page.  The 'bigcore' testहाल in GDB
	 * causes this हाल to run millions of बार.
	 */
	अगर (page == ZERO_PAGE(0))
		वापस;

	this_cpu = get_cpu();

	mapping = page_mapping_file(page);
	अगर (mapping && !mapping_mapped(mapping)) अणु
		पूर्णांक dirty = test_bit(PG_dcache_dirty, &page->flags);
		अगर (dirty) अणु
			पूर्णांक dirty_cpu = dcache_dirty_cpu(page);

			अगर (dirty_cpu == this_cpu)
				जाओ out;
			smp_flush_dcache_page_impl(page, dirty_cpu);
		पूर्ण
		set_dcache_dirty(page, this_cpu);
	पूर्ण अन्यथा अणु
		/* We could delay the flush क्रम the !page_mapping
		 * हाल too.  But that हाल is क्रम exec env/arg
		 * pages and those are %99 certainly going to get
		 * faulted पूर्णांकo the tlb (and thus flushed) anyways.
		 */
		flush_dcache_page_impl(page);
	पूर्ण

out:
	put_cpu();
पूर्ण
EXPORT_SYMBOL(flush_dcache_page);

व्योम __kprobes flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/* Cheetah and Hypervisor platक्रमm cpus have coherent I-cache. */
	अगर (tlb_type == spitfire) अणु
		अचिन्हित दीर्घ kaddr;

		/* This code only runs on Spitfire cpus so this is
		 * why we can assume _PAGE_PADDR_4U.
		 */
		क्रम (kaddr = start; kaddr < end; kaddr += PAGE_SIZE) अणु
			अचिन्हित दीर्घ paddr, mask = _PAGE_PADDR_4U;

			अगर (kaddr >= PAGE_OFFSET)
				paddr = kaddr & mask;
			अन्यथा अणु
				pte_t *ptep = virt_to_kpte(kaddr);

				paddr = pte_val(*ptep) & mask;
			पूर्ण
			__flush_icache_page(paddr);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flush_icache_range);

व्योम mmu_info(काष्ठा seq_file *m)
अणु
	अटल स्थिर अक्षर *pgsz_strings[] = अणु
		"8K", "64K", "512K", "4MB", "32MB",
		"256MB", "2GB", "16GB",
	पूर्ण;
	पूर्णांक i, prपूर्णांकed;

	अगर (tlb_type == cheetah)
		seq_म_लिखो(m, "MMU Type\t: Cheetah\n");
	अन्यथा अगर (tlb_type == cheetah_plus)
		seq_म_लिखो(m, "MMU Type\t: Cheetah+\n");
	अन्यथा अगर (tlb_type == spitfire)
		seq_म_लिखो(m, "MMU Type\t: Spitfire\n");
	अन्यथा अगर (tlb_type == hypervisor)
		seq_म_लिखो(m, "MMU Type\t: Hypervisor (sun4v)\n");
	अन्यथा
		seq_म_लिखो(m, "MMU Type\t: ???\n");

	seq_म_लिखो(m, "MMU PGSZs\t: ");
	prपूर्णांकed = 0;
	क्रम (i = 0; i < ARRAY_SIZE(pgsz_strings); i++) अणु
		अगर (cpu_pgsz_mask & (1UL << i)) अणु
			seq_म_लिखो(m, "%s%s",
				   prपूर्णांकed ? "," : "", pgsz_strings[i]);
			prपूर्णांकed++;
		पूर्ण
	पूर्ण
	seq_अ_दो(m, '\n');

#अगर_घोषित CONFIG_DEBUG_DCFLUSH
	seq_म_लिखो(m, "DCPageFlushes\t: %d\n",
		   atomic_पढ़ो(&dcpage_flushes));
#अगर_घोषित CONFIG_SMP
	seq_म_लिखो(m, "DCPageFlushesXC\t: %d\n",
		   atomic_पढ़ो(&dcpage_flushes_xcall));
#पूर्ण_अगर /* CONFIG_SMP */
#पूर्ण_अगर /* CONFIG_DEBUG_DCFLUSH */
पूर्ण

काष्ठा linux_prom_translation prom_trans[512] __पढ़ो_mostly;
अचिन्हित पूर्णांक prom_trans_ents __पढ़ो_mostly;

अचिन्हित दीर्घ kern_locked_tte_data;

/* The obp translations are saved based on 8k pagesize, since obp can
 * use a mixture of pagesizes. Misses to the LOW_OBP_ADDRESS ->
 * HI_OBP_ADDRESS range are handled in ktlb.S.
 */
अटल अंतरभूत पूर्णांक in_obp_range(अचिन्हित दीर्घ vaddr)
अणु
	वापस (vaddr >= LOW_OBP_ADDRESS &&
		vaddr < HI_OBP_ADDRESS);
पूर्ण

अटल पूर्णांक cmp_ptrans(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा linux_prom_translation *x = a, *y = b;

	अगर (x->virt > y->virt)
		वापस 1;
	अगर (x->virt < y->virt)
		वापस -1;
	वापस 0;
पूर्ण

/* Read OBP translations property पूर्णांकo 'prom_trans[]'.  */
अटल व्योम __init पढ़ो_obp_translations(व्योम)
अणु
	पूर्णांक n, node, ents, first, last, i;

	node = prom_finddevice("/virtual-memory");
	n = prom_getproplen(node, "translations");
	अगर (unlikely(n == 0 || n == -1)) अणु
		prom_म_लिखो("prom_mappings: Couldn't get size.\n");
		prom_halt();
	पूर्ण
	अगर (unlikely(n > माप(prom_trans))) अणु
		prom_म_लिखो("prom_mappings: Size %d is too big.\n", n);
		prom_halt();
	पूर्ण

	अगर ((n = prom_getproperty(node, "translations",
				  (अक्षर *)&prom_trans[0],
				  माप(prom_trans))) == -1) अणु
		prom_म_लिखो("prom_mappings: Couldn't get property.\n");
		prom_halt();
	पूर्ण

	n = n / माप(काष्ठा linux_prom_translation);

	ents = n;

	sort(prom_trans, ents, माप(काष्ठा linux_prom_translation),
	     cmp_ptrans, शून्य);

	/* Now kick out all the non-OBP entries.  */
	क्रम (i = 0; i < ents; i++) अणु
		अगर (in_obp_range(prom_trans[i].virt))
			अवरोध;
	पूर्ण
	first = i;
	क्रम (; i < ents; i++) अणु
		अगर (!in_obp_range(prom_trans[i].virt))
			अवरोध;
	पूर्ण
	last = i;

	क्रम (i = 0; i < (last - first); i++) अणु
		काष्ठा linux_prom_translation *src = &prom_trans[i + first];
		काष्ठा linux_prom_translation *dest = &prom_trans[i];

		*dest = *src;
	पूर्ण
	क्रम (; i < ents; i++) अणु
		काष्ठा linux_prom_translation *dest = &prom_trans[i];
		dest->virt = dest->size = dest->data = 0x0UL;
	पूर्ण

	prom_trans_ents = last - first;

	अगर (tlb_type == spitfire) अणु
		/* Clear diag TTE bits. */
		क्रम (i = 0; i < prom_trans_ents; i++)
			prom_trans[i].data &= ~0x0003fe0000000000UL;
	पूर्ण

	/* Force execute bit on.  */
	क्रम (i = 0; i < prom_trans_ents; i++)
		prom_trans[i].data |= (tlb_type == hypervisor ?
				       _PAGE_EXEC_4V : _PAGE_EXEC_4U);
पूर्ण

अटल व्योम __init hypervisor_tlb_lock(अचिन्हित दीर्घ vaddr,
				       अचिन्हित दीर्घ pte,
				       अचिन्हित दीर्घ mmu)
अणु
	अचिन्हित दीर्घ ret = sun4v_mmu_map_perm_addr(vaddr, 0, pte, mmu);

	अगर (ret != 0) अणु
		prom_म_लिखो("hypervisor_tlb_lock[%lx:%x:%lx:%lx]: "
			    "errors with %lx\n", vaddr, 0, pte, mmu, ret);
		prom_halt();
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ kern_large_tte(अचिन्हित दीर्घ paddr);

अटल व्योम __init remap_kernel(व्योम)
अणु
	अचिन्हित दीर्घ phys_page, tte_vaddr, tte_data;
	पूर्णांक i, tlb_ent = sparc64_highest_locked_tlbent();

	tte_vaddr = (अचिन्हित दीर्घ) KERNBASE;
	phys_page = (prom_boot_mapping_phys_low >> ILOG2_4MB) << ILOG2_4MB;
	tte_data = kern_large_tte(phys_page);

	kern_locked_tte_data = tte_data;

	/* Now lock us पूर्णांकo the TLBs via Hypervisor or OBP. */
	अगर (tlb_type == hypervisor) अणु
		क्रम (i = 0; i < num_kernel_image_mappings; i++) अणु
			hypervisor_tlb_lock(tte_vaddr, tte_data, HV_MMU_DMMU);
			hypervisor_tlb_lock(tte_vaddr, tte_data, HV_MMU_IMMU);
			tte_vaddr += 0x400000;
			tte_data += 0x400000;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < num_kernel_image_mappings; i++) अणु
			prom_dtlb_load(tlb_ent - i, tte_data, tte_vaddr);
			prom_itlb_load(tlb_ent - i, tte_data, tte_vaddr);
			tte_vaddr += 0x400000;
			tte_data += 0x400000;
		पूर्ण
		sparc64_highest_unlocked_tlb_ent = tlb_ent - i;
	पूर्ण
	अगर (tlb_type == cheetah_plus) अणु
		sparc64_kern_pri_context = (CTX_CHEETAH_PLUS_CTX0 |
					    CTX_CHEETAH_PLUS_NUC);
		sparc64_kern_pri_nuc_bits = CTX_CHEETAH_PLUS_NUC;
		sparc64_kern_sec_context = CTX_CHEETAH_PLUS_CTX0;
	पूर्ण
पूर्ण


अटल व्योम __init inherit_prom_mappings(व्योम)
अणु
	/* Now fixup OBP's idea about where we really are mapped. */
	prपूर्णांकk("Remapping the kernel... ");
	remap_kernel();
	prपूर्णांकk("done.\n");
पूर्ण

व्योम prom_world(पूर्णांक enter)
अणु
	अगर (!enter)
		set_fs(get_fs());

	__यंत्र__ __अस्थिर__("flushw");
पूर्ण

व्योम __flush_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ va;

	अगर (tlb_type == spitfire) अणु
		पूर्णांक n = 0;

		क्रम (va = start; va < end; va += 32) अणु
			spitfire_put_dcache_tag(va & 0x3fe0, 0x0);
			अगर (++n >= 512)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (tlb_type == cheetah || tlb_type == cheetah_plus) अणु
		start = __pa(start);
		end = __pa(end);
		क्रम (va = start; va < end; va += 32)
			__यंत्र__ __अस्थिर__("stxa %%g0, [%0] %1\n\t"
					     "membar #Sync"
					     : /* no outमाला_दो */
					     : "r" (va),
					       "i" (ASI_DCACHE_INVALIDATE));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__flush_dcache_range);

/* get_new_mmu_context() uses "cache + 1".  */
DEFINE_SPINLOCK(ctx_alloc_lock);
अचिन्हित दीर्घ tlb_context_cache = CTX_FIRST_VERSION;
#घोषणा MAX_CTX_NR	(1UL << CTX_NR_BITS)
#घोषणा CTX_BMAP_SLOTS	BITS_TO_LONGS(MAX_CTX_NR)
DECLARE_BITMAP(mmu_context_bmap, MAX_CTX_NR);
DEFINE_PER_CPU(काष्ठा mm_काष्ठा *, per_cpu_secondary_mm) = अणु0पूर्ण;

अटल व्योम mmu_context_wrap(व्योम)
अणु
	अचिन्हित दीर्घ old_ver = tlb_context_cache & CTX_VERSION_MASK;
	अचिन्हित दीर्घ new_ver, new_ctx, old_ctx;
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक cpu;

	biपंचांगap_zero(mmu_context_bmap, 1 << CTX_NR_BITS);

	/* Reserve kernel context */
	set_bit(0, mmu_context_bmap);

	new_ver = (tlb_context_cache & CTX_VERSION_MASK) + CTX_FIRST_VERSION;
	अगर (unlikely(new_ver == 0))
		new_ver = CTX_FIRST_VERSION;
	tlb_context_cache = new_ver;

	/*
	 * Make sure that any new mm that are added पूर्णांकo per_cpu_secondary_mm,
	 * are going to go through get_new_mmu_context() path.
	 */
	mb();

	/*
	 * Updated versions to current on those CPUs that had valid secondary
	 * contexts
	 */
	क्रम_each_online_cpu(cpu) अणु
		/*
		 * If a new mm is stored after we took this mm from the array,
		 * it will go पूर्णांकo get_new_mmu_context() path, because we
		 * alपढ़ोy bumped the version in tlb_context_cache.
		 */
		mm = per_cpu(per_cpu_secondary_mm, cpu);

		अगर (unlikely(!mm || mm == &init_mm))
			जारी;

		old_ctx = mm->context.sparc64_ctx_val;
		अगर (likely((old_ctx & CTX_VERSION_MASK) == old_ver)) अणु
			new_ctx = (old_ctx & ~CTX_VERSION_MASK) | new_ver;
			set_bit(new_ctx & CTX_NR_MASK, mmu_context_bmap);
			mm->context.sparc64_ctx_val = new_ctx;
		पूर्ण
	पूर्ण
पूर्ण

/* Caller करोes TLB context flushing on local CPU अगर necessary.
 * The caller also ensures that CTX_VALID(mm->context) is false.
 *
 * We must be careful about boundary हालs so that we never
 * let the user have CTX 0 (nucleus) or we ever use a CTX
 * version of zero (and thus NO_CONTEXT would not be caught
 * by version mis-match tests in mmu_context.h).
 *
 * Always invoked with पूर्णांकerrupts disabled.
 */
व्योम get_new_mmu_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ ctx, new_ctx;
	अचिन्हित दीर्घ orig_pgsz_bits;

	spin_lock(&ctx_alloc_lock);
retry:
	/* wrap might have happened, test again अगर our context became valid */
	अगर (unlikely(CTX_VALID(mm->context)))
		जाओ out;
	orig_pgsz_bits = (mm->context.sparc64_ctx_val & CTX_PGSZ_MASK);
	ctx = (tlb_context_cache + 1) & CTX_NR_MASK;
	new_ctx = find_next_zero_bit(mmu_context_bmap, 1 << CTX_NR_BITS, ctx);
	अगर (new_ctx >= (1 << CTX_NR_BITS)) अणु
		new_ctx = find_next_zero_bit(mmu_context_bmap, ctx, 1);
		अगर (new_ctx >= ctx) अणु
			mmu_context_wrap();
			जाओ retry;
		पूर्ण
	पूर्ण
	अगर (mm->context.sparc64_ctx_val)
		cpumask_clear(mm_cpumask(mm));
	mmu_context_bmap[new_ctx>>6] |= (1UL << (new_ctx & 63));
	new_ctx |= (tlb_context_cache & CTX_VERSION_MASK);
	tlb_context_cache = new_ctx;
	mm->context.sparc64_ctx_val = new_ctx | orig_pgsz_bits;
out:
	spin_unlock(&ctx_alloc_lock);
पूर्ण

अटल पूर्णांक numa_enabled = 1;
अटल पूर्णांक numa_debug;

अटल पूर्णांक __init early_numa(अक्षर *p)
अणु
	अगर (!p)
		वापस 0;

	अगर (म_माला(p, "off"))
		numa_enabled = 0;

	अगर (म_माला(p, "debug"))
		numa_debug = 1;

	वापस 0;
पूर्ण
early_param("numa", early_numa);

#घोषणा numadbg(f, a...) \
करो अणु	अगर (numa_debug) \
		prपूर्णांकk(KERN_INFO f, ## a); \
पूर्ण जबतक (0)

अटल व्योम __init find_ramdisk(अचिन्हित दीर्घ phys_base)
अणु
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (sparc_ramdisk_image || sparc_ramdisk_image64) अणु
		अचिन्हित दीर्घ ramdisk_image;

		/* Older versions of the bootloader only supported a
		 * 32-bit physical address क्रम the ramdisk image
		 * location, stored at sparc_ramdisk_image.  Newer
		 * SILO versions set sparc_ramdisk_image to zero and
		 * provide a full 64-bit physical address at
		 * sparc_ramdisk_image64.
		 */
		ramdisk_image = sparc_ramdisk_image;
		अगर (!ramdisk_image)
			ramdisk_image = sparc_ramdisk_image64;

		/* Another bootloader quirk.  The bootloader normalizes
		 * the physical address to KERNBASE, so we have to
		 * factor that back out and add in the lowest valid
		 * physical page address to get the true physical address.
		 */
		ramdisk_image -= KERNBASE;
		ramdisk_image += phys_base;

		numadbg("Found ramdisk at physical address 0x%lx, size %u\n",
			ramdisk_image, sparc_ramdisk_size);

		initrd_start = ramdisk_image;
		initrd_end = ramdisk_image + sparc_ramdisk_size;

		memblock_reserve(initrd_start, sparc_ramdisk_size);

		initrd_start += PAGE_OFFSET;
		initrd_end += PAGE_OFFSET;
	पूर्ण
#पूर्ण_अगर
पूर्ण

काष्ठा node_mem_mask अणु
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ match;
पूर्ण;
अटल काष्ठा node_mem_mask node_masks[MAX_NUMNODES];
अटल पूर्णांक num_node_masks;

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES

काष्ठा mdesc_mlgroup अणु
	u64	node;
	u64	latency;
	u64	match;
	u64	mask;
पूर्ण;

अटल काष्ठा mdesc_mlgroup *mlgroups;
अटल पूर्णांक num_mlgroups;

पूर्णांक numa_cpu_lookup_table[NR_CPUS];
cpumask_t numa_cpumask_lookup_table[MAX_NUMNODES];

काष्ठा mdesc_mblock अणु
	u64	base;
	u64	size;
	u64	offset; /* RA-to-PA */
पूर्ण;
अटल काष्ठा mdesc_mblock *mblocks;
अटल पूर्णांक num_mblocks;

अटल काष्ठा mdesc_mblock * __init addr_to_mblock(अचिन्हित दीर्घ addr)
अणु
	काष्ठा mdesc_mblock *m = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < num_mblocks; i++) अणु
		m = &mblocks[i];

		अगर (addr >= m->base &&
		    addr < (m->base + m->size)) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	वापस m;
पूर्ण

अटल u64 __init memblock_nid_range_sun4u(u64 start, u64 end, पूर्णांक *nid)
अणु
	पूर्णांक prev_nid, new_nid;

	prev_nid = NUMA_NO_NODE;
	क्रम ( ; start < end; start += PAGE_SIZE) अणु
		क्रम (new_nid = 0; new_nid < num_node_masks; new_nid++) अणु
			काष्ठा node_mem_mask *p = &node_masks[new_nid];

			अगर ((start & p->mask) == p->match) अणु
				अगर (prev_nid == NUMA_NO_NODE)
					prev_nid = new_nid;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (new_nid == num_node_masks) अणु
			prev_nid = 0;
			WARN_ONCE(1, "addr[%Lx] doesn't match a NUMA node rule. Some memory will be owned by node 0.",
				  start);
			अवरोध;
		पूर्ण

		अगर (prev_nid != new_nid)
			अवरोध;
	पूर्ण
	*nid = prev_nid;

	वापस start > end ? end : start;
पूर्ण

अटल u64 __init memblock_nid_range(u64 start, u64 end, पूर्णांक *nid)
अणु
	u64 ret_end, pa_start, m_mask, m_match, m_end;
	काष्ठा mdesc_mblock *mblock;
	पूर्णांक _nid, i;

	अगर (tlb_type != hypervisor)
		वापस memblock_nid_range_sun4u(start, end, nid);

	mblock = addr_to_mblock(start);
	अगर (!mblock) अणु
		WARN_ONCE(1, "memblock_nid_range: Can't find mblock addr[%Lx]",
			  start);

		_nid = 0;
		ret_end = end;
		जाओ करोne;
	पूर्ण

	pa_start = start + mblock->offset;
	m_match = 0;
	m_mask = 0;

	क्रम (_nid = 0; _nid < num_node_masks; _nid++) अणु
		काष्ठा node_mem_mask *स्थिर m = &node_masks[_nid];

		अगर ((pa_start & m->mask) == m->match) अणु
			m_match = m->match;
			m_mask = m->mask;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (num_node_masks == _nid) अणु
		/* We could not find NUMA group, so शेष to 0, but lets
		 * search क्रम latency group, so we could calculate the correct
		 * end address that we वापस
		 */
		_nid = 0;

		क्रम (i = 0; i < num_mlgroups; i++) अणु
			काष्ठा mdesc_mlgroup *स्थिर m = &mlgroups[i];

			अगर ((pa_start & m->mask) == m->match) अणु
				m_match = m->match;
				m_mask = m->mask;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == num_mlgroups) अणु
			WARN_ONCE(1, "memblock_nid_range: Can't find latency group addr[%Lx]",
				  start);

			ret_end = end;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/*
	 * Each latency group has match and mask, and each memory block has an
	 * offset.  An address beदीर्घs to a latency group अगर its address matches
	 * the following क्रमmula: ((addr + offset) & mask) == match
	 * It is, however, slow to check every single page अगर it matches a
	 * particular latency group. As optimization we calculate end value by
	 * using bit arithmetics.
	 */
	m_end = m_match + (1ul << __ffs(m_mask)) - mblock->offset;
	m_end += pa_start & ~((1ul << fls64(m_mask)) - 1);
	ret_end = m_end > end ? end : m_end;

करोne:
	*nid = _nid;
	वापस ret_end;
पूर्ण
#पूर्ण_अगर

/* This must be invoked after perक्रमming all of the necessary
 * memblock_set_node() calls क्रम 'nid'.  We need to be able to get
 * correct data from get_pfn_range_क्रम_nid().
 */
अटल व्योम __init allocate_node_data(पूर्णांक nid)
अणु
	काष्ठा pglist_data *p;
	अचिन्हित दीर्घ start_pfn, end_pfn;
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES

	NODE_DATA(nid) = memblock_alloc_node(माप(काष्ठा pglist_data),
					     SMP_CACHE_BYTES, nid);
	अगर (!NODE_DATA(nid)) अणु
		prom_म_लिखो("Cannot allocate pglist_data for nid[%d]\n", nid);
		prom_halt();
	पूर्ण

	NODE_DATA(nid)->node_id = nid;
#पूर्ण_अगर

	p = NODE_DATA(nid);

	get_pfn_range_क्रम_nid(nid, &start_pfn, &end_pfn);
	p->node_start_pfn = start_pfn;
	p->node_spanned_pages = end_pfn - start_pfn;
पूर्ण

अटल व्योम init_node_masks_nonnuma(व्योम)
अणु
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	पूर्णांक i;
#पूर्ण_अगर

	numadbg("Initializing tables for non-numa.\n");

	node_masks[0].mask = 0;
	node_masks[0].match = 0;
	num_node_masks = 1;

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	क्रम (i = 0; i < NR_CPUS; i++)
		numa_cpu_lookup_table[i] = 0;

	cpumask_setall(&numa_cpumask_lookup_table[0]);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
काष्ठा pglist_data *node_data[MAX_NUMNODES];

EXPORT_SYMBOL(numa_cpu_lookup_table);
EXPORT_SYMBOL(numa_cpumask_lookup_table);
EXPORT_SYMBOL(node_data);

अटल पूर्णांक scan_pio_क्रम_cfg_handle(काष्ठा mdesc_handle *md, u64 pio,
				   u32 cfg_handle)
अणु
	u64 arc;

	mdesc_क्रम_each_arc(arc, md, pio, MDESC_ARC_TYPE_FWD) अणु
		u64 target = mdesc_arc_target(md, arc);
		स्थिर u64 *val;

		val = mdesc_get_property(md, target,
					 "cfg-handle", शून्य);
		अगर (val && *val == cfg_handle)
			वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक scan_arcs_क्रम_cfg_handle(काष्ठा mdesc_handle *md, u64 grp,
				    u32 cfg_handle)
अणु
	u64 arc, candidate, best_latency = ~(u64)0;

	candidate = MDESC_NODE_शून्य;
	mdesc_क्रम_each_arc(arc, md, grp, MDESC_ARC_TYPE_FWD) अणु
		u64 target = mdesc_arc_target(md, arc);
		स्थिर अक्षर *name = mdesc_node_name(md, target);
		स्थिर u64 *val;

		अगर (म_भेद(name, "pio-latency-group"))
			जारी;

		val = mdesc_get_property(md, target, "latency", शून्य);
		अगर (!val)
			जारी;

		अगर (*val < best_latency) अणु
			candidate = target;
			best_latency = *val;
		पूर्ण
	पूर्ण

	अगर (candidate == MDESC_NODE_शून्य)
		वापस -ENODEV;

	वापस scan_pio_क्रम_cfg_handle(md, candidate, cfg_handle);
पूर्ण

पूर्णांक of_node_to_nid(काष्ठा device_node *dp)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *regs;
	काष्ठा mdesc_handle *md;
	u32 cfg_handle;
	पूर्णांक count, nid;
	u64 grp;

	/* This is the right thing to करो on currently supported
	 * SUN4U NUMA platक्रमms as well, as the PCI controller करोes
	 * not sit behind any particular memory controller.
	 */
	अगर (!mlgroups)
		वापस -1;

	regs = of_get_property(dp, "reg", शून्य);
	अगर (!regs)
		वापस -1;

	cfg_handle = (regs->phys_addr >> 32UL) & 0x0fffffff;

	md = mdesc_grab();

	count = 0;
	nid = NUMA_NO_NODE;
	mdesc_क्रम_each_node_by_name(md, grp, "group") अणु
		अगर (!scan_arcs_क्रम_cfg_handle(md, grp, cfg_handle)) अणु
			nid = count;
			अवरोध;
		पूर्ण
		count++;
	पूर्ण

	mdesc_release(md);

	वापस nid;
पूर्ण

अटल व्योम __init add_node_ranges(व्योम)
अणु
	phys_addr_t start, end;
	अचिन्हित दीर्घ prev_max;
	u64 i;

memblock_resized:
	prev_max = memblock.memory.max;

	क्रम_each_mem_range(i, &start, &end) अणु
		जबतक (start < end) अणु
			अचिन्हित दीर्घ this_end;
			पूर्णांक nid;

			this_end = memblock_nid_range(start, end, &nid);

			numadbg("Setting memblock NUMA node nid[%d] "
				"start[%llx] end[%lx]\n",
				nid, start, this_end);

			memblock_set_node(start, this_end - start,
					  &memblock.memory, nid);
			अगर (memblock.memory.max != prev_max)
				जाओ memblock_resized;
			start = this_end;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init grab_mlgroups(काष्ठा mdesc_handle *md)
अणु
	अचिन्हित दीर्घ paddr;
	पूर्णांक count = 0;
	u64 node;

	mdesc_क्रम_each_node_by_name(md, node, "memory-latency-group")
		count++;
	अगर (!count)
		वापस -ENOENT;

	paddr = memblock_phys_alloc(count * माप(काष्ठा mdesc_mlgroup),
				    SMP_CACHE_BYTES);
	अगर (!paddr)
		वापस -ENOMEM;

	mlgroups = __va(paddr);
	num_mlgroups = count;

	count = 0;
	mdesc_क्रम_each_node_by_name(md, node, "memory-latency-group") अणु
		काष्ठा mdesc_mlgroup *m = &mlgroups[count++];
		स्थिर u64 *val;

		m->node = node;

		val = mdesc_get_property(md, node, "latency", शून्य);
		m->latency = *val;
		val = mdesc_get_property(md, node, "address-match", शून्य);
		m->match = *val;
		val = mdesc_get_property(md, node, "address-mask", शून्य);
		m->mask = *val;

		numadbg("MLGROUP[%d]: node[%llx] latency[%llx] "
			"match[%llx] mask[%llx]\n",
			count - 1, m->node, m->latency, m->match, m->mask);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init grab_mblocks(काष्ठा mdesc_handle *md)
अणु
	अचिन्हित दीर्घ paddr;
	पूर्णांक count = 0;
	u64 node;

	mdesc_क्रम_each_node_by_name(md, node, "mblock")
		count++;
	अगर (!count)
		वापस -ENOENT;

	paddr = memblock_phys_alloc(count * माप(काष्ठा mdesc_mblock),
				    SMP_CACHE_BYTES);
	अगर (!paddr)
		वापस -ENOMEM;

	mblocks = __va(paddr);
	num_mblocks = count;

	count = 0;
	mdesc_क्रम_each_node_by_name(md, node, "mblock") अणु
		काष्ठा mdesc_mblock *m = &mblocks[count++];
		स्थिर u64 *val;

		val = mdesc_get_property(md, node, "base", शून्य);
		m->base = *val;
		val = mdesc_get_property(md, node, "size", शून्य);
		m->size = *val;
		val = mdesc_get_property(md, node,
					 "address-congruence-offset", शून्य);

		/* The address-congruence-offset property is optional.
		 * Explicity zero it be identअगरty this.
		 */
		अगर (val)
			m->offset = *val;
		अन्यथा
			m->offset = 0UL;

		numadbg("MBLOCK[%d]: base[%llx] size[%llx] offset[%llx]\n",
			count - 1, m->base, m->size, m->offset);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init numa_parse_mdesc_group_cpus(काष्ठा mdesc_handle *md,
					       u64 grp, cpumask_t *mask)
अणु
	u64 arc;

	cpumask_clear(mask);

	mdesc_क्रम_each_arc(arc, md, grp, MDESC_ARC_TYPE_BACK) अणु
		u64 target = mdesc_arc_target(md, arc);
		स्थिर अक्षर *name = mdesc_node_name(md, target);
		स्थिर u64 *id;

		अगर (म_भेद(name, "cpu"))
			जारी;
		id = mdesc_get_property(md, target, "id", शून्य);
		अगर (*id < nr_cpu_ids)
			cpumask_set_cpu(*id, mask);
	पूर्ण
पूर्ण

अटल काष्ठा mdesc_mlgroup * __init find_mlgroup(u64 node)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_mlgroups; i++) अणु
		काष्ठा mdesc_mlgroup *m = &mlgroups[i];
		अगर (m->node == node)
			वापस m;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक __node_distance(पूर्णांक from, पूर्णांक to)
अणु
	अगर ((from >= MAX_NUMNODES) || (to >= MAX_NUMNODES)) अणु
		pr_warn("Returning default NUMA distance value for %d->%d\n",
			from, to);
		वापस (from == to) ? LOCAL_DISTANCE : REMOTE_DISTANCE;
	पूर्ण
	वापस numa_latency[from][to];
पूर्ण
EXPORT_SYMBOL(__node_distance);

अटल पूर्णांक __init find_best_numa_node_क्रम_mlgroup(काष्ठा mdesc_mlgroup *grp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NUMNODES; i++) अणु
		काष्ठा node_mem_mask *n = &node_masks[i];

		अगर ((grp->mask == n->mask) && (grp->match == n->match))
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

अटल व्योम __init find_numa_latencies_क्रम_group(काष्ठा mdesc_handle *md,
						 u64 grp, पूर्णांक index)
अणु
	u64 arc;

	mdesc_क्रम_each_arc(arc, md, grp, MDESC_ARC_TYPE_FWD) अणु
		पूर्णांक tnode;
		u64 target = mdesc_arc_target(md, arc);
		काष्ठा mdesc_mlgroup *m = find_mlgroup(target);

		अगर (!m)
			जारी;
		tnode = find_best_numa_node_क्रम_mlgroup(m);
		अगर (tnode == MAX_NUMNODES)
			जारी;
		numa_latency[index][tnode] = m->latency;
	पूर्ण
पूर्ण

अटल पूर्णांक __init numa_attach_mlgroup(काष्ठा mdesc_handle *md, u64 grp,
				      पूर्णांक index)
अणु
	काष्ठा mdesc_mlgroup *candidate = शून्य;
	u64 arc, best_latency = ~(u64)0;
	काष्ठा node_mem_mask *n;

	mdesc_क्रम_each_arc(arc, md, grp, MDESC_ARC_TYPE_FWD) अणु
		u64 target = mdesc_arc_target(md, arc);
		काष्ठा mdesc_mlgroup *m = find_mlgroup(target);
		अगर (!m)
			जारी;
		अगर (m->latency < best_latency) अणु
			candidate = m;
			best_latency = m->latency;
		पूर्ण
	पूर्ण
	अगर (!candidate)
		वापस -ENOENT;

	अगर (num_node_masks != index) अणु
		prपूर्णांकk(KERN_ERR "Inconsistent NUMA state, "
		       "index[%d] != num_node_masks[%d]\n",
		       index, num_node_masks);
		वापस -EINVAL;
	पूर्ण

	n = &node_masks[num_node_masks++];

	n->mask = candidate->mask;
	n->match = candidate->match;

	numadbg("NUMA NODE[%d]: mask[%lx] match[%lx] (latency[%llx])\n",
		index, n->mask, n->match, candidate->latency);

	वापस 0;
पूर्ण

अटल पूर्णांक __init numa_parse_mdesc_group(काष्ठा mdesc_handle *md, u64 grp,
					 पूर्णांक index)
अणु
	cpumask_t mask;
	पूर्णांक cpu;

	numa_parse_mdesc_group_cpus(md, grp, &mask);

	क्रम_each_cpu(cpu, &mask)
		numa_cpu_lookup_table[cpu] = index;
	cpumask_copy(&numa_cpumask_lookup_table[index], &mask);

	अगर (numa_debug) अणु
		prपूर्णांकk(KERN_INFO "NUMA GROUP[%d]: cpus [ ", index);
		क्रम_each_cpu(cpu, &mask)
			prपूर्णांकk("%d ", cpu);
		prपूर्णांकk("]\n");
	पूर्ण

	वापस numa_attach_mlgroup(md, grp, index);
पूर्ण

अटल पूर्णांक __init numa_parse_mdesc(व्योम)
अणु
	काष्ठा mdesc_handle *md = mdesc_grab();
	पूर्णांक i, j, err, count;
	u64 node;

	node = mdesc_node_by_name(md, MDESC_NODE_शून्य, "latency-groups");
	अगर (node == MDESC_NODE_शून्य) अणु
		mdesc_release(md);
		वापस -ENOENT;
	पूर्ण

	err = grab_mblocks(md);
	अगर (err < 0)
		जाओ out;

	err = grab_mlgroups(md);
	अगर (err < 0)
		जाओ out;

	count = 0;
	mdesc_क्रम_each_node_by_name(md, node, "group") अणु
		err = numa_parse_mdesc_group(md, node, count);
		अगर (err < 0)
			अवरोध;
		count++;
	पूर्ण

	count = 0;
	mdesc_क्रम_each_node_by_name(md, node, "group") अणु
		find_numa_latencies_क्रम_group(md, node, count);
		count++;
	पूर्ण

	/* Normalize numa latency matrix according to ACPI SLIT spec. */
	क्रम (i = 0; i < MAX_NUMNODES; i++) अणु
		u64 self_latency = numa_latency[i][i];

		क्रम (j = 0; j < MAX_NUMNODES; j++) अणु
			numa_latency[i][j] =
				(numa_latency[i][j] * LOCAL_DISTANCE) /
				self_latency;
		पूर्ण
	पूर्ण

	add_node_ranges();

	क्रम (i = 0; i < num_node_masks; i++) अणु
		allocate_node_data(i);
		node_set_online(i);
	पूर्ण

	err = 0;
out:
	mdesc_release(md);
	वापस err;
पूर्ण

अटल पूर्णांक __init numa_parse_jbus(व्योम)
अणु
	अचिन्हित दीर्घ cpu, index;

	/* NUMA node id is encoded in bits 36 and higher, and there is
	 * a 1-to-1 mapping from CPU ID to NUMA node ID.
	 */
	index = 0;
	क्रम_each_present_cpu(cpu) अणु
		numa_cpu_lookup_table[cpu] = index;
		cpumask_copy(&numa_cpumask_lookup_table[index], cpumask_of(cpu));
		node_masks[index].mask = ~((1UL << 36UL) - 1UL);
		node_masks[index].match = cpu << 36UL;

		index++;
	पूर्ण
	num_node_masks = index;

	add_node_ranges();

	क्रम (index = 0; index < num_node_masks; index++) अणु
		allocate_node_data(index);
		node_set_online(index);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init numa_parse_sun4u(व्योम)
अणु
	अगर (tlb_type == cheetah || tlb_type == cheetah_plus) अणु
		अचिन्हित दीर्घ ver;

		__यंत्र__ ("rdpr %%ver, %0" : "=r" (ver));
		अगर ((ver >> 32UL) == __JALAPENO_ID ||
		    (ver >> 32UL) == __SERRANO_ID)
			वापस numa_parse_jbus();
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक __init booपंचांगem_init_numa(व्योम)
अणु
	पूर्णांक i, j;
	पूर्णांक err = -1;

	numadbg("bootmem_init_numa()\n");

	/* Some sane शेषs क्रम numa latency values */
	क्रम (i = 0; i < MAX_NUMNODES; i++) अणु
		क्रम (j = 0; j < MAX_NUMNODES; j++)
			numa_latency[i][j] = (i == j) ?
				LOCAL_DISTANCE : REMOTE_DISTANCE;
	पूर्ण

	अगर (numa_enabled) अणु
		अगर (tlb_type == hypervisor)
			err = numa_parse_mdesc();
		अन्यथा
			err = numa_parse_sun4u();
	पूर्ण
	वापस err;
पूर्ण

#अन्यथा

अटल पूर्णांक booपंचांगem_init_numa(व्योम)
अणु
	वापस -1;
पूर्ण

#पूर्ण_अगर

अटल व्योम __init booपंचांगem_init_nonnuma(व्योम)
अणु
	अचिन्हित दीर्घ top_of_ram = memblock_end_of_DRAM();
	अचिन्हित दीर्घ total_ram = memblock_phys_mem_size();

	numadbg("bootmem_init_nonnuma()\n");

	prपूर्णांकk(KERN_INFO "Top of RAM: 0x%lx, Total RAM: 0x%lx\n",
	       top_of_ram, total_ram);
	prपूर्णांकk(KERN_INFO "Memory hole size: %ldMB\n",
	       (top_of_ram - total_ram) >> 20);

	init_node_masks_nonnuma();
	memblock_set_node(0, PHYS_ADDR_MAX, &memblock.memory, 0);
	allocate_node_data(0);
	node_set_online(0);
पूर्ण

अटल अचिन्हित दीर्घ __init booपंचांगem_init(अचिन्हित दीर्घ phys_base)
अणु
	अचिन्हित दीर्घ end_pfn;

	end_pfn = memblock_end_of_DRAM() >> PAGE_SHIFT;
	max_pfn = max_low_pfn = end_pfn;
	min_low_pfn = (phys_base >> PAGE_SHIFT);

	अगर (booपंचांगem_init_numa() < 0)
		booपंचांगem_init_nonnuma();

	/* Dump memblock with node info. */
	memblock_dump_all();

	/* XXX cpu notअगरier XXX */

	sparse_init();

	वापस end_pfn;
पूर्ण

अटल काष्ठा linux_prom64_रेजिस्टरs pall[MAX_BANKS] __initdata;
अटल पूर्णांक pall_ents __initdata;

अटल अचिन्हित दीर्घ max_phys_bits = 40;

bool kern_addr_valid(अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	अगर ((दीर्घ)addr < 0L) अणु
		अचिन्हित दीर्घ pa = __pa(addr);

		अगर ((pa >> max_phys_bits) != 0UL)
			वापस false;

		वापस pfn_valid(pa >> PAGE_SHIFT);
	पूर्ण

	अगर (addr >= (अचिन्हित दीर्घ) KERNBASE &&
	    addr < (अचिन्हित दीर्घ)&_end)
		वापस true;

	pgd = pgd_offset_k(addr);
	अगर (pgd_none(*pgd))
		वापस false;

	p4d = p4d_offset(pgd, addr);
	अगर (p4d_none(*p4d))
		वापस false;

	pud = pud_offset(p4d, addr);
	अगर (pud_none(*pud))
		वापस false;

	अगर (pud_large(*pud))
		वापस pfn_valid(pud_pfn(*pud));

	pmd = pmd_offset(pud, addr);
	अगर (pmd_none(*pmd))
		वापस false;

	अगर (pmd_large(*pmd))
		वापस pfn_valid(pmd_pfn(*pmd));

	pte = pte_offset_kernel(pmd, addr);
	अगर (pte_none(*pte))
		वापस false;

	वापस pfn_valid(pte_pfn(*pte));
पूर्ण
EXPORT_SYMBOL(kern_addr_valid);

अटल अचिन्हित दीर्घ __ref kernel_map_hugepud(अचिन्हित दीर्घ vstart,
					      अचिन्हित दीर्घ vend,
					      pud_t *pud)
अणु
	स्थिर अचिन्हित दीर्घ mask16gb = (1UL << 34) - 1UL;
	u64 pte_val = vstart;

	/* Each PUD is 8GB */
	अगर ((vstart & mask16gb) ||
	    (vend - vstart <= mask16gb)) अणु
		pte_val ^= kern_linear_pte_xor[2];
		pud_val(*pud) = pte_val | _PAGE_PUD_HUGE;

		वापस vstart + PUD_SIZE;
	पूर्ण

	pte_val ^= kern_linear_pte_xor[3];
	pte_val |= _PAGE_PUD_HUGE;

	vend = vstart + mask16gb + 1UL;
	जबतक (vstart < vend) अणु
		pud_val(*pud) = pte_val;

		pte_val += PUD_SIZE;
		vstart += PUD_SIZE;
		pud++;
	पूर्ण
	वापस vstart;
पूर्ण

अटल bool kernel_can_map_hugepud(अचिन्हित दीर्घ vstart, अचिन्हित दीर्घ vend,
				   bool guard)
अणु
	अगर (guard && !(vstart & ~PUD_MASK) && (vend - vstart) >= PUD_SIZE)
		वापस true;

	वापस false;
पूर्ण

अटल अचिन्हित दीर्घ __ref kernel_map_hugepmd(अचिन्हित दीर्घ vstart,
					      अचिन्हित दीर्घ vend,
					      pmd_t *pmd)
अणु
	स्थिर अचिन्हित दीर्घ mask256mb = (1UL << 28) - 1UL;
	स्थिर अचिन्हित दीर्घ mask2gb = (1UL << 31) - 1UL;
	u64 pte_val = vstart;

	/* Each PMD is 8MB */
	अगर ((vstart & mask256mb) ||
	    (vend - vstart <= mask256mb)) अणु
		pte_val ^= kern_linear_pte_xor[0];
		pmd_val(*pmd) = pte_val | _PAGE_PMD_HUGE;

		वापस vstart + PMD_SIZE;
	पूर्ण

	अगर ((vstart & mask2gb) ||
	    (vend - vstart <= mask2gb)) अणु
		pte_val ^= kern_linear_pte_xor[1];
		pte_val |= _PAGE_PMD_HUGE;
		vend = vstart + mask256mb + 1UL;
	पूर्ण अन्यथा अणु
		pte_val ^= kern_linear_pte_xor[2];
		pte_val |= _PAGE_PMD_HUGE;
		vend = vstart + mask2gb + 1UL;
	पूर्ण

	जबतक (vstart < vend) अणु
		pmd_val(*pmd) = pte_val;

		pte_val += PMD_SIZE;
		vstart += PMD_SIZE;
		pmd++;
	पूर्ण

	वापस vstart;
पूर्ण

अटल bool kernel_can_map_hugepmd(अचिन्हित दीर्घ vstart, अचिन्हित दीर्घ vend,
				   bool guard)
अणु
	अगर (guard && !(vstart & ~PMD_MASK) && (vend - vstart) >= PMD_SIZE)
		वापस true;

	वापस false;
पूर्ण

अटल अचिन्हित दीर्घ __ref kernel_map_range(अचिन्हित दीर्घ pstart,
					    अचिन्हित दीर्घ pend, pgprot_t prot,
					    bool use_huge)
अणु
	अचिन्हित दीर्घ vstart = PAGE_OFFSET + pstart;
	अचिन्हित दीर्घ vend = PAGE_OFFSET + pend;
	अचिन्हित दीर्घ alloc_bytes = 0UL;

	अगर ((vstart & ~PAGE_MASK) || (vend & ~PAGE_MASK)) अणु
		prom_म_लिखो("kernel_map: Unaligned physmem[%lx:%lx]\n",
			    vstart, vend);
		prom_halt();
	पूर्ण

	जबतक (vstart < vend) अणु
		अचिन्हित दीर्घ this_end, paddr = __pa(vstart);
		pgd_t *pgd = pgd_offset_k(vstart);
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;
		pte_t *pte;

		अगर (pgd_none(*pgd)) अणु
			pud_t *new;

			new = memblock_alloc_from(PAGE_SIZE, PAGE_SIZE,
						  PAGE_SIZE);
			अगर (!new)
				जाओ err_alloc;
			alloc_bytes += PAGE_SIZE;
			pgd_populate(&init_mm, pgd, new);
		पूर्ण

		p4d = p4d_offset(pgd, vstart);
		अगर (p4d_none(*p4d)) अणु
			pud_t *new;

			new = memblock_alloc_from(PAGE_SIZE, PAGE_SIZE,
						  PAGE_SIZE);
			अगर (!new)
				जाओ err_alloc;
			alloc_bytes += PAGE_SIZE;
			p4d_populate(&init_mm, p4d, new);
		पूर्ण

		pud = pud_offset(p4d, vstart);
		अगर (pud_none(*pud)) अणु
			pmd_t *new;

			अगर (kernel_can_map_hugepud(vstart, vend, use_huge)) अणु
				vstart = kernel_map_hugepud(vstart, vend, pud);
				जारी;
			पूर्ण
			new = memblock_alloc_from(PAGE_SIZE, PAGE_SIZE,
						  PAGE_SIZE);
			अगर (!new)
				जाओ err_alloc;
			alloc_bytes += PAGE_SIZE;
			pud_populate(&init_mm, pud, new);
		पूर्ण

		pmd = pmd_offset(pud, vstart);
		अगर (pmd_none(*pmd)) अणु
			pte_t *new;

			अगर (kernel_can_map_hugepmd(vstart, vend, use_huge)) अणु
				vstart = kernel_map_hugepmd(vstart, vend, pmd);
				जारी;
			पूर्ण
			new = memblock_alloc_from(PAGE_SIZE, PAGE_SIZE,
						  PAGE_SIZE);
			अगर (!new)
				जाओ err_alloc;
			alloc_bytes += PAGE_SIZE;
			pmd_populate_kernel(&init_mm, pmd, new);
		पूर्ण

		pte = pte_offset_kernel(pmd, vstart);
		this_end = (vstart + PMD_SIZE) & PMD_MASK;
		अगर (this_end > vend)
			this_end = vend;

		जबतक (vstart < this_end) अणु
			pte_val(*pte) = (paddr | pgprot_val(prot));

			vstart += PAGE_SIZE;
			paddr += PAGE_SIZE;
			pte++;
		पूर्ण
	पूर्ण

	वापस alloc_bytes;

err_alloc:
	panic("%s: Failed to allocate %lu bytes align=%lx from=%lx\n",
	      __func__, PAGE_SIZE, PAGE_SIZE, PAGE_SIZE);
	वापस -ENOMEM;
पूर्ण

अटल व्योम __init flush_all_kernel_tsbs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KERNEL_TSB_NENTRIES; i++) अणु
		काष्ठा tsb *ent = &swapper_tsb[i];

		ent->tag = (1UL << TSB_TAG_INVALID_BIT);
	पूर्ण
#अगर_अघोषित CONFIG_DEBUG_PAGEALLOC
	क्रम (i = 0; i < KERNEL_TSB4M_NENTRIES; i++) अणु
		काष्ठा tsb *ent = &swapper_4m_tsb[i];

		ent->tag = (1UL << TSB_TAG_INVALID_BIT);
	पूर्ण
#पूर्ण_अगर
पूर्ण

बाह्य अचिन्हित पूर्णांक kvmap_linear_patch[1];

अटल व्योम __init kernel_physical_mapping_init(व्योम)
अणु
	अचिन्हित दीर्घ i, mem_alloced = 0UL;
	bool use_huge = true;

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
	use_huge = false;
#पूर्ण_अगर
	क्रम (i = 0; i < pall_ents; i++) अणु
		अचिन्हित दीर्घ phys_start, phys_end;

		phys_start = pall[i].phys_addr;
		phys_end = phys_start + pall[i].reg_size;

		mem_alloced += kernel_map_range(phys_start, phys_end,
						PAGE_KERNEL, use_huge);
	पूर्ण

	prपूर्णांकk("Allocated %ld bytes for kernel page tables.\n",
	       mem_alloced);

	kvmap_linear_patch[0] = 0x01000000; /* nop */
	flushi(&kvmap_linear_patch[0]);

	flush_all_kernel_tsbs();

	__flush_tlb_all();
पूर्ण

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
व्योम __kernel_map_pages(काष्ठा page *page, पूर्णांक numpages, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ phys_start = page_to_pfn(page) << PAGE_SHIFT;
	अचिन्हित दीर्घ phys_end = phys_start + (numpages * PAGE_SIZE);

	kernel_map_range(phys_start, phys_end,
			 (enable ? PAGE_KERNEL : __pgprot(0)), false);

	flush_tsb_kernel_range(PAGE_OFFSET + phys_start,
			       PAGE_OFFSET + phys_end);

	/* we should perक्रमm an IPI and flush all tlbs,
	 * but that can deadlock->flush only current cpu.
	 */
	__flush_tlb_kernel_range(PAGE_OFFSET + phys_start,
				 PAGE_OFFSET + phys_end);
पूर्ण
#पूर्ण_अगर

अचिन्हित दीर्घ __init find_ecache_flush_span(अचिन्हित दीर्घ size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pavail_ents; i++) अणु
		अगर (pavail[i].reg_size >= size)
			वापस pavail[i].phys_addr;
	पूर्ण

	वापस ~0UL;
पूर्ण

अचिन्हित दीर्घ PAGE_OFFSET;
EXPORT_SYMBOL(PAGE_OFFSET);

अचिन्हित दीर्घ VMALLOC_END   = 0x0000010000000000UL;
EXPORT_SYMBOL(VMALLOC_END);

अचिन्हित दीर्घ sparc64_va_hole_top =    0xfffff80000000000UL;
अचिन्हित दीर्घ sparc64_va_hole_bottom = 0x0000080000000000UL;

अटल व्योम __init setup_page_offset(व्योम)
अणु
	अगर (tlb_type == cheetah || tlb_type == cheetah_plus) अणु
		/* Cheetah/Panther support a full 64-bit भव
		 * address, so we can use all that our page tables
		 * support.
		 */
		sparc64_va_hole_top =    0xfff0000000000000UL;
		sparc64_va_hole_bottom = 0x0010000000000000UL;

		max_phys_bits = 42;
	पूर्ण अन्यथा अगर (tlb_type == hypervisor) अणु
		चयन (sun4v_chip_type) अणु
		हाल SUN4V_CHIP_NIAGARA1:
		हाल SUN4V_CHIP_NIAGARA2:
			/* T1 and T2 support 48-bit भव addresses.  */
			sparc64_va_hole_top =    0xffff800000000000UL;
			sparc64_va_hole_bottom = 0x0000800000000000UL;

			max_phys_bits = 39;
			अवरोध;
		हाल SUN4V_CHIP_NIAGARA3:
			/* T3 supports 48-bit भव addresses.  */
			sparc64_va_hole_top =    0xffff800000000000UL;
			sparc64_va_hole_bottom = 0x0000800000000000UL;

			max_phys_bits = 43;
			अवरोध;
		हाल SUN4V_CHIP_NIAGARA4:
		हाल SUN4V_CHIP_NIAGARA5:
		हाल SUN4V_CHIP_SPARC64X:
		हाल SUN4V_CHIP_SPARC_M6:
			/* T4 and later support 52-bit भव addresses.  */
			sparc64_va_hole_top =    0xfff8000000000000UL;
			sparc64_va_hole_bottom = 0x0008000000000000UL;
			max_phys_bits = 47;
			अवरोध;
		हाल SUN4V_CHIP_SPARC_M7:
		हाल SUN4V_CHIP_SPARC_SN:
			/* M7 and later support 52-bit भव addresses.  */
			sparc64_va_hole_top =    0xfff8000000000000UL;
			sparc64_va_hole_bottom = 0x0008000000000000UL;
			max_phys_bits = 49;
			अवरोध;
		हाल SUN4V_CHIP_SPARC_M8:
		शेष:
			/* M8 and later support 54-bit भव addresses.
			 * However, restricting M8 and above VA bits to 53
			 * as 4-level page table cannot support more than
			 * 53 VA bits.
			 */
			sparc64_va_hole_top =    0xfff0000000000000UL;
			sparc64_va_hole_bottom = 0x0010000000000000UL;
			max_phys_bits = 51;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (max_phys_bits > MAX_PHYS_ADDRESS_BITS) अणु
		prom_म_लिखो("MAX_PHYS_ADDRESS_BITS is too small, need %lu\n",
			    max_phys_bits);
		prom_halt();
	पूर्ण

	PAGE_OFFSET = sparc64_va_hole_top;
	VMALLOC_END = ((sparc64_va_hole_bottom >> 1) +
		       (sparc64_va_hole_bottom >> 2));

	pr_info("MM: PAGE_OFFSET is 0x%016lx (max_phys_bits == %lu)\n",
		PAGE_OFFSET, max_phys_bits);
	pr_info("MM: VMALLOC [0x%016lx --> 0x%016lx]\n",
		VMALLOC_START, VMALLOC_END);
	pr_info("MM: VMEMMAP [0x%016lx --> 0x%016lx]\n",
		VMEMMAP_BASE, VMEMMAP_BASE << 1);
पूर्ण

अटल व्योम __init tsb_phys_patch(व्योम)
अणु
	काष्ठा tsb_ldquad_phys_patch_entry *pquad;
	काष्ठा tsb_phys_patch_entry *p;

	pquad = &__tsb_ldquad_phys_patch;
	जबतक (pquad < &__tsb_ldquad_phys_patch_end) अणु
		अचिन्हित दीर्घ addr = pquad->addr;

		अगर (tlb_type == hypervisor)
			*(अचिन्हित पूर्णांक *) addr = pquad->sun4v_insn;
		अन्यथा
			*(अचिन्हित पूर्णांक *) addr = pquad->sun4u_insn;
		wmb();
		__यंत्र__ __अस्थिर__("flush	%0"
				     : /* no outमाला_दो */
				     : "r" (addr));

		pquad++;
	पूर्ण

	p = &__tsb_phys_patch;
	जबतक (p < &__tsb_phys_patch_end) अणु
		अचिन्हित दीर्घ addr = p->addr;

		*(अचिन्हित पूर्णांक *) addr = p->insn;
		wmb();
		__यंत्र__ __अस्थिर__("flush	%0"
				     : /* no outमाला_दो */
				     : "r" (addr));

		p++;
	पूर्ण
पूर्ण

/* Don't mark as init, we give this to the Hypervisor.  */
#अगर_अघोषित CONFIG_DEBUG_PAGEALLOC
#घोषणा NUM_KTSB_DESCR	2
#अन्यथा
#घोषणा NUM_KTSB_DESCR	1
#पूर्ण_अगर
अटल काष्ठा hv_tsb_descr ktsb_descr[NUM_KTSB_DESCR];

/* The swapper TSBs are loaded with a base sequence of:
 *
 *	sethi	%uhi(SYMBOL), REG1
 *	sethi	%hi(SYMBOL), REG2
 *	or	REG1, %ulo(SYMBOL), REG1
 *	or	REG2, %lo(SYMBOL), REG2
 *	sllx	REG1, 32, REG1
 *	or	REG1, REG2, REG1
 *
 * When we use physical addressing क्रम the TSB accesses, we patch the
 * first four inकाष्ठाions in the above sequence.
 */

अटल व्योम patch_one_ktsb_phys(अचिन्हित पूर्णांक *start, अचिन्हित पूर्णांक *end, अचिन्हित दीर्घ pa)
अणु
	अचिन्हित दीर्घ high_bits, low_bits;

	high_bits = (pa >> 32) & 0xffffffff;
	low_bits = (pa >> 0) & 0xffffffff;

	जबतक (start < end) अणु
		अचिन्हित पूर्णांक *ia = (अचिन्हित पूर्णांक *)(अचिन्हित दीर्घ)*start;

		ia[0] = (ia[0] & ~0x3fffff) | (high_bits >> 10);
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (ia));

		ia[1] = (ia[1] & ~0x3fffff) | (low_bits >> 10);
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (ia + 1));

		ia[2] = (ia[2] & ~0x1fff) | (high_bits & 0x3ff);
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (ia + 2));

		ia[3] = (ia[3] & ~0x1fff) | (low_bits & 0x3ff);
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (ia + 3));

		start++;
	पूर्ण
पूर्ण

अटल व्योम ktsb_phys_patch(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक __swapper_tsb_phys_patch;
	बाह्य अचिन्हित पूर्णांक __swapper_tsb_phys_patch_end;
	अचिन्हित दीर्घ ktsb_pa;

	ktsb_pa = kern_base + ((अचिन्हित दीर्घ)&swapper_tsb[0] - KERNBASE);
	patch_one_ktsb_phys(&__swapper_tsb_phys_patch,
			    &__swapper_tsb_phys_patch_end, ktsb_pa);
#अगर_अघोषित CONFIG_DEBUG_PAGEALLOC
	अणु
	बाह्य अचिन्हित पूर्णांक __swapper_4m_tsb_phys_patch;
	बाह्य अचिन्हित पूर्णांक __swapper_4m_tsb_phys_patch_end;
	ktsb_pa = (kern_base +
		   ((अचिन्हित दीर्घ)&swapper_4m_tsb[0] - KERNBASE));
	patch_one_ktsb_phys(&__swapper_4m_tsb_phys_patch,
			    &__swapper_4m_tsb_phys_patch_end, ktsb_pa);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init sun4v_ktsb_init(व्योम)
अणु
	अचिन्हित दीर्घ ktsb_pa;

	/* First KTSB क्रम PAGE_SIZE mappings.  */
	ktsb_pa = kern_base + ((अचिन्हित दीर्घ)&swapper_tsb[0] - KERNBASE);

	चयन (PAGE_SIZE) अणु
	हाल 8 * 1024:
	शेष:
		ktsb_descr[0].pgsz_idx = HV_PGSZ_IDX_8K;
		ktsb_descr[0].pgsz_mask = HV_PGSZ_MASK_8K;
		अवरोध;

	हाल 64 * 1024:
		ktsb_descr[0].pgsz_idx = HV_PGSZ_IDX_64K;
		ktsb_descr[0].pgsz_mask = HV_PGSZ_MASK_64K;
		अवरोध;

	हाल 512 * 1024:
		ktsb_descr[0].pgsz_idx = HV_PGSZ_IDX_512K;
		ktsb_descr[0].pgsz_mask = HV_PGSZ_MASK_512K;
		अवरोध;

	हाल 4 * 1024 * 1024:
		ktsb_descr[0].pgsz_idx = HV_PGSZ_IDX_4MB;
		ktsb_descr[0].pgsz_mask = HV_PGSZ_MASK_4MB;
		अवरोध;
	पूर्ण

	ktsb_descr[0].assoc = 1;
	ktsb_descr[0].num_ttes = KERNEL_TSB_NENTRIES;
	ktsb_descr[0].ctx_idx = 0;
	ktsb_descr[0].tsb_base = ktsb_pa;
	ktsb_descr[0].resv = 0;

#अगर_अघोषित CONFIG_DEBUG_PAGEALLOC
	/* Second KTSB क्रम 4MB/256MB/2GB/16GB mappings.  */
	ktsb_pa = (kern_base +
		   ((अचिन्हित दीर्घ)&swapper_4m_tsb[0] - KERNBASE));

	ktsb_descr[1].pgsz_idx = HV_PGSZ_IDX_4MB;
	ktsb_descr[1].pgsz_mask = ((HV_PGSZ_MASK_4MB |
				    HV_PGSZ_MASK_256MB |
				    HV_PGSZ_MASK_2GB |
				    HV_PGSZ_MASK_16GB) &
				   cpu_pgsz_mask);
	ktsb_descr[1].assoc = 1;
	ktsb_descr[1].num_ttes = KERNEL_TSB4M_NENTRIES;
	ktsb_descr[1].ctx_idx = 0;
	ktsb_descr[1].tsb_base = ktsb_pa;
	ktsb_descr[1].resv = 0;
#पूर्ण_अगर
पूर्ण

व्योम sun4v_ktsb_रेजिस्टर(व्योम)
अणु
	अचिन्हित दीर्घ pa, ret;

	pa = kern_base + ((अचिन्हित दीर्घ)&ktsb_descr[0] - KERNBASE);

	ret = sun4v_mmu_tsb_ctx0(NUM_KTSB_DESCR, pa);
	अगर (ret != 0) अणु
		prom_म_लिखो("hypervisor_mmu_tsb_ctx0[%lx]: "
			    "errors with %lx\n", pa, ret);
		prom_halt();
	पूर्ण
पूर्ण

अटल व्योम __init sun4u_linear_pte_xor_finalize(व्योम)
अणु
#अगर_अघोषित CONFIG_DEBUG_PAGEALLOC
	/* This is where we would add Panther support क्रम
	 * 32MB and 256MB pages.
	 */
#पूर्ण_अगर
पूर्ण

अटल व्योम __init sun4v_linear_pte_xor_finalize(व्योम)
अणु
	अचिन्हित दीर्घ pagecv_flag;

	/* Bit 9 of TTE is no दीर्घer CV bit on M7 processor and it instead
	 * enables MCD error. Do not set bit 9 on M7 processor.
	 */
	चयन (sun4v_chip_type) अणु
	हाल SUN4V_CHIP_SPARC_M7:
	हाल SUN4V_CHIP_SPARC_M8:
	हाल SUN4V_CHIP_SPARC_SN:
		pagecv_flag = 0x00;
		अवरोध;
	शेष:
		pagecv_flag = _PAGE_CV_4V;
		अवरोध;
	पूर्ण
#अगर_अघोषित CONFIG_DEBUG_PAGEALLOC
	अगर (cpu_pgsz_mask & HV_PGSZ_MASK_256MB) अणु
		kern_linear_pte_xor[1] = (_PAGE_VALID | _PAGE_SZ256MB_4V) ^
			PAGE_OFFSET;
		kern_linear_pte_xor[1] |= (_PAGE_CP_4V | pagecv_flag |
					   _PAGE_P_4V | _PAGE_W_4V);
	पूर्ण अन्यथा अणु
		kern_linear_pte_xor[1] = kern_linear_pte_xor[0];
	पूर्ण

	अगर (cpu_pgsz_mask & HV_PGSZ_MASK_2GB) अणु
		kern_linear_pte_xor[2] = (_PAGE_VALID | _PAGE_SZ2GB_4V) ^
			PAGE_OFFSET;
		kern_linear_pte_xor[2] |= (_PAGE_CP_4V | pagecv_flag |
					   _PAGE_P_4V | _PAGE_W_4V);
	पूर्ण अन्यथा अणु
		kern_linear_pte_xor[2] = kern_linear_pte_xor[1];
	पूर्ण

	अगर (cpu_pgsz_mask & HV_PGSZ_MASK_16GB) अणु
		kern_linear_pte_xor[3] = (_PAGE_VALID | _PAGE_SZ16GB_4V) ^
			PAGE_OFFSET;
		kern_linear_pte_xor[3] |= (_PAGE_CP_4V | pagecv_flag |
					   _PAGE_P_4V | _PAGE_W_4V);
	पूर्ण अन्यथा अणु
		kern_linear_pte_xor[3] = kern_linear_pte_xor[2];
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* paging_init() sets up the page tables */

अटल अचिन्हित दीर्घ last_valid_pfn;

अटल व्योम sun4u_pgprot_init(व्योम);
अटल व्योम sun4v_pgprot_init(व्योम);

#घोषणा _PAGE_CACHE_4U	(_PAGE_CP_4U | _PAGE_CV_4U)
#घोषणा _PAGE_CACHE_4V	(_PAGE_CP_4V | _PAGE_CV_4V)
#घोषणा __सूचीTY_BITS_4U	 (_PAGE_MODIFIED_4U | _PAGE_WRITE_4U | _PAGE_W_4U)
#घोषणा __सूचीTY_BITS_4V	 (_PAGE_MODIFIED_4V | _PAGE_WRITE_4V | _PAGE_W_4V)
#घोषणा __ACCESS_BITS_4U (_PAGE_ACCESSED_4U | _PAGE_READ_4U | _PAGE_R)
#घोषणा __ACCESS_BITS_4V (_PAGE_ACCESSED_4V | _PAGE_READ_4V | _PAGE_R)

/* We need to exclude reserved regions. This exclusion will include
 * vmlinux and initrd. To be more precise the initrd size could be used to
 * compute a new lower limit because it is मुक्तd later during initialization.
 */
अटल व्योम __init reduce_memory(phys_addr_t limit_ram)
अणु
	limit_ram += memblock_reserved_size();
	memblock_enक्रमce_memory_limit(limit_ram);
पूर्ण

व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ end_pfn, shअगरt, phys_base;
	अचिन्हित दीर्घ real_end, i;

	setup_page_offset();

	/* These build समय checkes make sure that the dcache_dirty_cpu()
	 * page->flags usage will work.
	 *
	 * When a page माला_लो marked as dcache-dirty, we store the
	 * cpu number starting at bit 32 in the page->flags.  Also,
	 * functions like clear_dcache_dirty_cpu use the cpu mask
	 * in 13-bit चिन्हित-immediate inकाष्ठाion fields.
	 */

	/*
	 * Page flags must not reach पूर्णांकo upper 32 bits that are used
	 * क्रम the cpu number
	 */
	BUILD_BUG_ON(NR_PAGEFLAGS > 32);

	/*
	 * The bit fields placed in the high range must not reach below
	 * the 32 bit boundary. Otherwise we cannot place the cpu field
	 * at the 32 bit boundary.
	 */
	BUILD_BUG_ON(SECTIONS_WIDTH + NODES_WIDTH + ZONES_WIDTH +
		ilog2(roundup_घात_of_two(NR_CPUS)) > 32);

	BUILD_BUG_ON(NR_CPUS > 4096);

	kern_base = (prom_boot_mapping_phys_low >> ILOG2_4MB) << ILOG2_4MB;
	kern_size = (अचिन्हित दीर्घ)&_end - (अचिन्हित दीर्घ)KERNBASE;

	/* Invalidate both kernel TSBs.  */
	स_रखो(swapper_tsb, 0x40, माप(swapper_tsb));
#अगर_अघोषित CONFIG_DEBUG_PAGEALLOC
	स_रखो(swapper_4m_tsb, 0x40, माप(swapper_4m_tsb));
#पूर्ण_अगर

	/* TTE.cv bit on sparc v9 occupies the same position as TTE.mcde
	 * bit on M7 processor. This is a conflicting usage of the same
	 * bit. Enabling TTE.cv on M7 would turn on Memory Corruption
	 * Detection error on all pages and this will lead to problems
	 * later. Kernel करोes not run with MCD enabled and hence rest
	 * of the required steps to fully configure memory corruption
	 * detection are not taken. We need to ensure TTE.mcde is not
	 * set on M7 processor. Compute the value of cacheability
	 * flag क्रम use later taking this पूर्णांकo consideration.
	 */
	चयन (sun4v_chip_type) अणु
	हाल SUN4V_CHIP_SPARC_M7:
	हाल SUN4V_CHIP_SPARC_M8:
	हाल SUN4V_CHIP_SPARC_SN:
		page_cache4v_flag = _PAGE_CP_4V;
		अवरोध;
	शेष:
		page_cache4v_flag = _PAGE_CACHE_4V;
		अवरोध;
	पूर्ण

	अगर (tlb_type == hypervisor)
		sun4v_pgprot_init();
	अन्यथा
		sun4u_pgprot_init();

	अगर (tlb_type == cheetah_plus ||
	    tlb_type == hypervisor) अणु
		tsb_phys_patch();
		ktsb_phys_patch();
	पूर्ण

	अगर (tlb_type == hypervisor)
		sun4v_patch_tlb_handlers();

	/* Find available physical memory...
	 *
	 * Read it twice in order to work around a bug in खोलोfirmware.
	 * The call to grab this table itself can cause खोलोfirmware to
	 * allocate memory, which in turn can take away some space from
	 * the list of available memory.  Reading it twice makes sure
	 * we really करो get the final value.
	 */
	पढ़ो_obp_translations();
	पढ़ो_obp_memory("reg", &pall[0], &pall_ents);
	पढ़ो_obp_memory("available", &pavail[0], &pavail_ents);
	पढ़ो_obp_memory("available", &pavail[0], &pavail_ents);

	phys_base = 0xffffffffffffffffUL;
	क्रम (i = 0; i < pavail_ents; i++) अणु
		phys_base = min(phys_base, pavail[i].phys_addr);
		memblock_add(pavail[i].phys_addr, pavail[i].reg_size);
	पूर्ण

	memblock_reserve(kern_base, kern_size);

	find_ramdisk(phys_base);

	अगर (cmdline_memory_size)
		reduce_memory(cmdline_memory_size);

	memblock_allow_resize();
	memblock_dump_all();

	set_bit(0, mmu_context_bmap);

	shअगरt = kern_base + PAGE_OFFSET - ((अचिन्हित दीर्घ)KERNBASE);

	real_end = (अचिन्हित दीर्घ)_end;
	num_kernel_image_mappings = DIV_ROUND_UP(real_end - KERNBASE, 1 << ILOG2_4MB);
	prपूर्णांकk("Kernel: Using %d locked TLB entries for main kernel image.\n",
	       num_kernel_image_mappings);

	/* Set kernel pgd to upper alias so physical page computations
	 * work.
	 */
	init_mm.pgd += ((shअगरt) / (माप(pgd_t)));
	
	स_रखो(swapper_pg_dir, 0, माप(swapper_pg_dir));

	inherit_prom_mappings();
	
	/* Ok, we can use our TLB miss and winकरोw trap handlers safely.  */
	setup_tba();

	__flush_tlb_all();

	prom_build_devicetree();
	of_populate_present_mask();
#अगर_अघोषित CONFIG_SMP
	of_fill_in_cpu_data();
#पूर्ण_अगर

	अगर (tlb_type == hypervisor) अणु
		sun4v_mdesc_init();
		mdesc_populate_present_mask(cpu_all_mask);
#अगर_अघोषित CONFIG_SMP
		mdesc_fill_in_cpu_data(cpu_all_mask);
#पूर्ण_अगर
		mdesc_get_page_sizes(cpu_all_mask, &cpu_pgsz_mask);

		sun4v_linear_pte_xor_finalize();

		sun4v_ktsb_init();
		sun4v_ktsb_रेजिस्टर();
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ impl, ver;

		cpu_pgsz_mask = (HV_PGSZ_MASK_8K | HV_PGSZ_MASK_64K |
				 HV_PGSZ_MASK_512K | HV_PGSZ_MASK_4MB);

		__यंत्र__ __अस्थिर__("rdpr %%ver, %0" : "=r" (ver));
		impl = ((ver >> 32) & 0xffff);
		अगर (impl == PANTHER_IMPL)
			cpu_pgsz_mask |= (HV_PGSZ_MASK_32MB |
					  HV_PGSZ_MASK_256MB);

		sun4u_linear_pte_xor_finalize();
	पूर्ण

	/* Flush the TLBs and the 4M TSB so that the updated linear
	 * pte XOR settings are realized क्रम all mappings.
	 */
	__flush_tlb_all();
#अगर_अघोषित CONFIG_DEBUG_PAGEALLOC
	स_रखो(swapper_4m_tsb, 0x40, माप(swapper_4m_tsb));
#पूर्ण_अगर
	__flush_tlb_all();

	/* Setup booपंचांगem... */
	last_valid_pfn = end_pfn = booपंचांगem_init(phys_base);

	kernel_physical_mapping_init();

	अणु
		अचिन्हित दीर्घ max_zone_pfns[MAX_NR_ZONES];

		स_रखो(max_zone_pfns, 0, माप(max_zone_pfns));

		max_zone_pfns[ZONE_NORMAL] = end_pfn;

		मुक्त_area_init(max_zone_pfns);
	पूर्ण

	prपूर्णांकk("Booting Linux...\n");
पूर्ण

पूर्णांक page_in_phys_avail(अचिन्हित दीर्घ paddr)
अणु
	पूर्णांक i;

	paddr &= PAGE_MASK;

	क्रम (i = 0; i < pavail_ents; i++) अणु
		अचिन्हित दीर्घ start, end;

		start = pavail[i].phys_addr;
		end = start + pavail[i].reg_size;

		अगर (paddr >= start && paddr < end)
			वापस 1;
	पूर्ण
	अगर (paddr >= kern_base && paddr < (kern_base + kern_size))
		वापस 1;
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर (paddr >= __pa(initrd_start) &&
	    paddr < __pa(PAGE_ALIGN(initrd_end)))
		वापस 1;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम __init रेजिस्टर_page_booपंचांगem_info(व्योम)
अणु
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	पूर्णांक i;

	क्रम_each_online_node(i)
		अगर (NODE_DATA(i)->node_spanned_pages)
			रेजिस्टर_page_booपंचांगem_info_node(NODE_DATA(i));
#पूर्ण_अगर
पूर्ण
व्योम __init mem_init(व्योम)
अणु
	high_memory = __va(last_valid_pfn << PAGE_SHIFT);

	memblock_मुक्त_all();

	/*
	 * Must be करोne after boot memory is put on मुक्तlist, because here we
	 * might set fields in deferred काष्ठा pages that have not yet been
	 * initialized, and memblock_मुक्त_all() initializes all the reserved
	 * deferred pages क्रम us.
	 */
	रेजिस्टर_page_booपंचांगem_info();

	/*
	 * Set up the zero page, mark it reserved, so that page count
	 * is not manipulated when मुक्तing the page from user ptes.
	 */
	mem_map_zero = alloc_pages(GFP_KERNEL|__GFP_ZERO, 0);
	अगर (mem_map_zero == शून्य) अणु
		prom_म_लिखो("paging_init: Cannot alloc zero page.\n");
		prom_halt();
	पूर्ण
	mark_page_reserved(mem_map_zero);


	अगर (tlb_type == cheetah || tlb_type == cheetah_plus)
		cheetah_ecache_flush_init();
पूर्ण

व्योम मुक्त_iniपंचांगem(व्योम)
अणु
	अचिन्हित दीर्घ addr, initend;
	पूर्णांक करो_मुक्त = 1;

	/* If the physical memory maps were trimmed by kernel command
	 * line options, करोn't even try मुक्तing this iniपंचांगem stuff up.
	 * The kernel image could have been in the trimmed out region
	 * and अगर so the मुक्तing below will मुक्त invalid page काष्ठाs.
	 */
	अगर (cmdline_memory_size)
		करो_मुक्त = 0;

	/*
	 * The init section is aligned to 8k in vmlinux.lds. Page align क्रम >8k pagesizes.
	 */
	addr = PAGE_ALIGN((अचिन्हित दीर्घ)(__init_begin));
	initend = (अचिन्हित दीर्घ)(__init_end) & PAGE_MASK;
	क्रम (; addr < initend; addr += PAGE_SIZE) अणु
		अचिन्हित दीर्घ page;

		page = (addr +
			((अचिन्हित दीर्घ) __va(kern_base)) -
			((अचिन्हित दीर्घ) KERNBASE));
		स_रखो((व्योम *)addr, POISON_FREE_INITMEM, PAGE_SIZE);

		अगर (करो_मुक्त)
			मुक्त_reserved_page(virt_to_page(page));
	पूर्ण
पूर्ण

pgprot_t PAGE_KERNEL __पढ़ो_mostly;
EXPORT_SYMBOL(PAGE_KERNEL);

pgprot_t PAGE_KERNEL_LOCKED __पढ़ो_mostly;
pgprot_t PAGE_COPY __पढ़ो_mostly;

pgprot_t PAGE_SHARED __पढ़ो_mostly;
EXPORT_SYMBOL(PAGE_SHARED);

अचिन्हित दीर्घ pg_iobits __पढ़ो_mostly;

अचिन्हित दीर्घ _PAGE_IE __पढ़ो_mostly;
EXPORT_SYMBOL(_PAGE_IE);

अचिन्हित दीर्घ _PAGE_E __पढ़ो_mostly;
EXPORT_SYMBOL(_PAGE_E);

अचिन्हित दीर्घ _PAGE_CACHE __पढ़ो_mostly;
EXPORT_SYMBOL(_PAGE_CACHE);

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
पूर्णांक __meminit vmemmap_populate(अचिन्हित दीर्घ vstart, अचिन्हित दीर्घ vend,
			       पूर्णांक node, काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ pte_base;

	pte_base = (_PAGE_VALID | _PAGE_SZ4MB_4U |
		    _PAGE_CP_4U | _PAGE_CV_4U |
		    _PAGE_P_4U | _PAGE_W_4U);
	अगर (tlb_type == hypervisor)
		pte_base = (_PAGE_VALID | _PAGE_SZ4MB_4V |
			    page_cache4v_flag | _PAGE_P_4V | _PAGE_W_4V);

	pte_base |= _PAGE_PMD_HUGE;

	vstart = vstart & PMD_MASK;
	vend = ALIGN(vend, PMD_SIZE);
	क्रम (; vstart < vend; vstart += PMD_SIZE) अणु
		pgd_t *pgd = vmemmap_pgd_populate(vstart, node);
		अचिन्हित दीर्घ pte;
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;

		अगर (!pgd)
			वापस -ENOMEM;

		p4d = vmemmap_p4d_populate(pgd, vstart, node);
		अगर (!p4d)
			वापस -ENOMEM;

		pud = vmemmap_pud_populate(p4d, vstart, node);
		अगर (!pud)
			वापस -ENOMEM;

		pmd = pmd_offset(pud, vstart);
		pte = pmd_val(*pmd);
		अगर (!(pte & _PAGE_VALID)) अणु
			व्योम *block = vmemmap_alloc_block(PMD_SIZE, node);

			अगर (!block)
				वापस -ENOMEM;

			pmd_val(*pmd) = pte_base | __pa(block);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम vmemmap_मुक्त(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SPARSEMEM_VMEMMAP */

अटल व्योम prot_init_common(अचिन्हित दीर्घ page_none,
			     अचिन्हित दीर्घ page_shared,
			     अचिन्हित दीर्घ page_copy,
			     अचिन्हित दीर्घ page_पढ़ोonly,
			     अचिन्हित दीर्घ page_exec_bit)
अणु
	PAGE_COPY = __pgprot(page_copy);
	PAGE_SHARED = __pgprot(page_shared);

	protection_map[0x0] = __pgprot(page_none);
	protection_map[0x1] = __pgprot(page_पढ़ोonly & ~page_exec_bit);
	protection_map[0x2] = __pgprot(page_copy & ~page_exec_bit);
	protection_map[0x3] = __pgprot(page_copy & ~page_exec_bit);
	protection_map[0x4] = __pgprot(page_पढ़ोonly);
	protection_map[0x5] = __pgprot(page_पढ़ोonly);
	protection_map[0x6] = __pgprot(page_copy);
	protection_map[0x7] = __pgprot(page_copy);
	protection_map[0x8] = __pgprot(page_none);
	protection_map[0x9] = __pgprot(page_पढ़ोonly & ~page_exec_bit);
	protection_map[0xa] = __pgprot(page_shared & ~page_exec_bit);
	protection_map[0xb] = __pgprot(page_shared & ~page_exec_bit);
	protection_map[0xc] = __pgprot(page_पढ़ोonly);
	protection_map[0xd] = __pgprot(page_पढ़ोonly);
	protection_map[0xe] = __pgprot(page_shared);
	protection_map[0xf] = __pgprot(page_shared);
पूर्ण

अटल व्योम __init sun4u_pgprot_init(व्योम)
अणु
	अचिन्हित दीर्घ page_none, page_shared, page_copy, page_पढ़ोonly;
	अचिन्हित दीर्घ page_exec_bit;
	पूर्णांक i;

	PAGE_KERNEL = __pgprot (_PAGE_PRESENT_4U | _PAGE_VALID |
				_PAGE_CACHE_4U | _PAGE_P_4U |
				__ACCESS_BITS_4U | __सूचीTY_BITS_4U |
				_PAGE_EXEC_4U);
	PAGE_KERNEL_LOCKED = __pgprot (_PAGE_PRESENT_4U | _PAGE_VALID |
				       _PAGE_CACHE_4U | _PAGE_P_4U |
				       __ACCESS_BITS_4U | __सूचीTY_BITS_4U |
				       _PAGE_EXEC_4U | _PAGE_L_4U);

	_PAGE_IE = _PAGE_IE_4U;
	_PAGE_E = _PAGE_E_4U;
	_PAGE_CACHE = _PAGE_CACHE_4U;

	pg_iobits = (_PAGE_VALID | _PAGE_PRESENT_4U | __सूचीTY_BITS_4U |
		     __ACCESS_BITS_4U | _PAGE_E_4U);

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
	kern_linear_pte_xor[0] = _PAGE_VALID ^ PAGE_OFFSET;
#अन्यथा
	kern_linear_pte_xor[0] = (_PAGE_VALID | _PAGE_SZ4MB_4U) ^
		PAGE_OFFSET;
#पूर्ण_अगर
	kern_linear_pte_xor[0] |= (_PAGE_CP_4U | _PAGE_CV_4U |
				   _PAGE_P_4U | _PAGE_W_4U);

	क्रम (i = 1; i < 4; i++)
		kern_linear_pte_xor[i] = kern_linear_pte_xor[0];

	_PAGE_ALL_SZ_BITS =  (_PAGE_SZ4MB_4U | _PAGE_SZ512K_4U |
			      _PAGE_SZ64K_4U | _PAGE_SZ8K_4U |
			      _PAGE_SZ32MB_4U | _PAGE_SZ256MB_4U);


	page_none = _PAGE_PRESENT_4U | _PAGE_ACCESSED_4U | _PAGE_CACHE_4U;
	page_shared = (_PAGE_VALID | _PAGE_PRESENT_4U | _PAGE_CACHE_4U |
		       __ACCESS_BITS_4U | _PAGE_WRITE_4U | _PAGE_EXEC_4U);
	page_copy   = (_PAGE_VALID | _PAGE_PRESENT_4U | _PAGE_CACHE_4U |
		       __ACCESS_BITS_4U | _PAGE_EXEC_4U);
	page_पढ़ोonly   = (_PAGE_VALID | _PAGE_PRESENT_4U | _PAGE_CACHE_4U |
			   __ACCESS_BITS_4U | _PAGE_EXEC_4U);

	page_exec_bit = _PAGE_EXEC_4U;

	prot_init_common(page_none, page_shared, page_copy, page_पढ़ोonly,
			 page_exec_bit);
पूर्ण

अटल व्योम __init sun4v_pgprot_init(व्योम)
अणु
	अचिन्हित दीर्घ page_none, page_shared, page_copy, page_पढ़ोonly;
	अचिन्हित दीर्घ page_exec_bit;
	पूर्णांक i;

	PAGE_KERNEL = __pgprot (_PAGE_PRESENT_4V | _PAGE_VALID |
				page_cache4v_flag | _PAGE_P_4V |
				__ACCESS_BITS_4V | __सूचीTY_BITS_4V |
				_PAGE_EXEC_4V);
	PAGE_KERNEL_LOCKED = PAGE_KERNEL;

	_PAGE_IE = _PAGE_IE_4V;
	_PAGE_E = _PAGE_E_4V;
	_PAGE_CACHE = page_cache4v_flag;

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
	kern_linear_pte_xor[0] = _PAGE_VALID ^ PAGE_OFFSET;
#अन्यथा
	kern_linear_pte_xor[0] = (_PAGE_VALID | _PAGE_SZ4MB_4V) ^
		PAGE_OFFSET;
#पूर्ण_अगर
	kern_linear_pte_xor[0] |= (page_cache4v_flag | _PAGE_P_4V |
				   _PAGE_W_4V);

	क्रम (i = 1; i < 4; i++)
		kern_linear_pte_xor[i] = kern_linear_pte_xor[0];

	pg_iobits = (_PAGE_VALID | _PAGE_PRESENT_4V | __सूचीTY_BITS_4V |
		     __ACCESS_BITS_4V | _PAGE_E_4V);

	_PAGE_ALL_SZ_BITS = (_PAGE_SZ16GB_4V | _PAGE_SZ2GB_4V |
			     _PAGE_SZ256MB_4V | _PAGE_SZ32MB_4V |
			     _PAGE_SZ4MB_4V | _PAGE_SZ512K_4V |
			     _PAGE_SZ64K_4V | _PAGE_SZ8K_4V);

	page_none = _PAGE_PRESENT_4V | _PAGE_ACCESSED_4V | page_cache4v_flag;
	page_shared = (_PAGE_VALID | _PAGE_PRESENT_4V | page_cache4v_flag |
		       __ACCESS_BITS_4V | _PAGE_WRITE_4V | _PAGE_EXEC_4V);
	page_copy   = (_PAGE_VALID | _PAGE_PRESENT_4V | page_cache4v_flag |
		       __ACCESS_BITS_4V | _PAGE_EXEC_4V);
	page_पढ़ोonly = (_PAGE_VALID | _PAGE_PRESENT_4V | page_cache4v_flag |
			 __ACCESS_BITS_4V | _PAGE_EXEC_4V);

	page_exec_bit = _PAGE_EXEC_4V;

	prot_init_common(page_none, page_shared, page_copy, page_पढ़ोonly,
			 page_exec_bit);
पूर्ण

अचिन्हित दीर्घ pte_sz_bits(अचिन्हित दीर्घ sz)
अणु
	अगर (tlb_type == hypervisor) अणु
		चयन (sz) अणु
		हाल 8 * 1024:
		शेष:
			वापस _PAGE_SZ8K_4V;
		हाल 64 * 1024:
			वापस _PAGE_SZ64K_4V;
		हाल 512 * 1024:
			वापस _PAGE_SZ512K_4V;
		हाल 4 * 1024 * 1024:
			वापस _PAGE_SZ4MB_4V;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (sz) अणु
		हाल 8 * 1024:
		शेष:
			वापस _PAGE_SZ8K_4U;
		हाल 64 * 1024:
			वापस _PAGE_SZ64K_4U;
		हाल 512 * 1024:
			वापस _PAGE_SZ512K_4U;
		हाल 4 * 1024 * 1024:
			वापस _PAGE_SZ4MB_4U;
		पूर्ण
	पूर्ण
पूर्ण

pte_t mk_pte_io(अचिन्हित दीर्घ page, pgprot_t prot, पूर्णांक space, अचिन्हित दीर्घ page_size)
अणु
	pte_t pte;

	pte_val(pte)  = page | pgprot_val(pgprot_noncached(prot));
	pte_val(pte) |= (((अचिन्हित दीर्घ)space) << 32);
	pte_val(pte) |= pte_sz_bits(page_size);

	वापस pte;
पूर्ण

अटल अचिन्हित दीर्घ kern_large_tte(अचिन्हित दीर्घ paddr)
अणु
	अचिन्हित दीर्घ val;

	val = (_PAGE_VALID | _PAGE_SZ4MB_4U |
	       _PAGE_CP_4U | _PAGE_CV_4U | _PAGE_P_4U |
	       _PAGE_EXEC_4U | _PAGE_L_4U | _PAGE_W_4U);
	अगर (tlb_type == hypervisor)
		val = (_PAGE_VALID | _PAGE_SZ4MB_4V |
		       page_cache4v_flag | _PAGE_P_4V |
		       _PAGE_EXEC_4V | _PAGE_W_4V);

	वापस val | paddr;
पूर्ण

/* If not locked, zap it. */
व्योम __flush_tlb_all(व्योम)
अणु
	अचिन्हित दीर्घ pstate;
	पूर्णांक i;

	__यंत्र__ __अस्थिर__("flushw\n\t"
			     "rdpr	%%pstate, %0\n\t"
			     "wrpr	%0, %1, %%pstate"
			     : "=r" (pstate)
			     : "i" (PSTATE_IE));
	अगर (tlb_type == hypervisor) अणु
		sun4v_mmu_demap_all();
	पूर्ण अन्यथा अगर (tlb_type == spitfire) अणु
		क्रम (i = 0; i < 64; i++) अणु
			/* Spitfire Errata #32 workaround */
			/* NOTE: Always runs on spitfire, so no
			 *       cheetah+ page size encodings.
			 */
			__यंत्र__ __अस्थिर__("stxa	%0, [%1] %2\n\t"
					     "flush	%%g6"
					     : /* No outमाला_दो */
					     : "r" (0),
					     "r" (PRIMARY_CONTEXT), "i" (ASI_DMMU));

			अगर (!(spitfire_get_dtlb_data(i) & _PAGE_L_4U)) अणु
				__यंत्र__ __अस्थिर__("stxa %%g0, [%0] %1\n\t"
						     "membar #Sync"
						     : /* no outमाला_दो */
						     : "r" (TLB_TAG_ACCESS), "i" (ASI_DMMU));
				spitfire_put_dtlb_data(i, 0x0UL);
			पूर्ण

			/* Spitfire Errata #32 workaround */
			/* NOTE: Always runs on spitfire, so no
			 *       cheetah+ page size encodings.
			 */
			__यंत्र__ __अस्थिर__("stxa	%0, [%1] %2\n\t"
					     "flush	%%g6"
					     : /* No outमाला_दो */
					     : "r" (0),
					     "r" (PRIMARY_CONTEXT), "i" (ASI_DMMU));

			अगर (!(spitfire_get_itlb_data(i) & _PAGE_L_4U)) अणु
				__यंत्र__ __अस्थिर__("stxa %%g0, [%0] %1\n\t"
						     "membar #Sync"
						     : /* no outमाला_दो */
						     : "r" (TLB_TAG_ACCESS), "i" (ASI_IMMU));
				spitfire_put_itlb_data(i, 0x0UL);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (tlb_type == cheetah || tlb_type == cheetah_plus) अणु
		cheetah_flush_dtlb_all();
		cheetah_flush_itlb_all();
	पूर्ण
	__यंत्र__ __अस्थिर__("wrpr	%0, 0, %%pstate"
			     : : "r" (pstate));
पूर्ण

pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा page *page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	pte_t *pte = शून्य;

	अगर (page)
		pte = (pte_t *) page_address(page);

	वापस pte;
पूर्ण

pgtable_t pte_alloc_one(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा page *page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	अगर (!page)
		वापस शून्य;
	अगर (!pgtable_pte_page_ctor(page)) अणु
		__मुक्त_page(page);
		वापस शून्य;
	पूर्ण
	वापस (pte_t *) page_address(page);
पूर्ण

व्योम pte_मुक्त_kernel(काष्ठा mm_काष्ठा *mm, pte_t *pte)
अणु
	मुक्त_page((अचिन्हित दीर्घ)pte);
पूर्ण

अटल व्योम __pte_मुक्त(pgtable_t pte)
अणु
	काष्ठा page *page = virt_to_page(pte);

	pgtable_pte_page_dtor(page);
	__मुक्त_page(page);
पूर्ण

व्योम pte_मुक्त(काष्ठा mm_काष्ठा *mm, pgtable_t pte)
अणु
	__pte_मुक्त(pte);
पूर्ण

व्योम pgtable_मुक्त(व्योम *table, bool is_page)
अणु
	अगर (is_page)
		__pte_मुक्त(table);
	अन्यथा
		kmem_cache_मुक्त(pgtable_cache, table);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
व्योम update_mmu_cache_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			  pmd_t *pmd)
अणु
	अचिन्हित दीर्घ pte, flags;
	काष्ठा mm_काष्ठा *mm;
	pmd_t entry = *pmd;

	अगर (!pmd_large(entry) || !pmd_young(entry))
		वापस;

	pte = pmd_val(entry);

	/* Don't insert a non-valid PMD into the TSB, we'll deadlock.  */
	अगर (!(pte & _PAGE_VALID))
		वापस;

	/* We are fabricating 8MB pages using 4MB real hw pages.  */
	pte |= (addr & (1UL << REAL_HPAGE_SHIFT));

	mm = vma->vm_mm;

	spin_lock_irqsave(&mm->context.lock, flags);

	अगर (mm->context.tsb_block[MM_TSB_HUGE].tsb != शून्य)
		__update_mmu_tsb_insert(mm, MM_TSB_HUGE, REAL_HPAGE_SHIFT,
					addr, pte);

	spin_unlock_irqrestore(&mm->context.lock, flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
अटल व्योम context_reload(व्योम *__data)
अणु
	काष्ठा mm_काष्ठा *mm = __data;

	अगर (mm == current->mm)
		load_secondary_context(mm);
पूर्ण

व्योम hugetlb_setup(काष्ठा pt_regs *regs)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा tsb_config *tp;

	अगर (faulthandler_disabled() || !mm) अणु
		स्थिर काष्ठा exception_table_entry *entry;

		entry = search_exception_tables(regs->tpc);
		अगर (entry) अणु
			regs->tpc = entry->fixup;
			regs->tnpc = regs->tpc + 4;
			वापस;
		पूर्ण
		pr_alert("Unexpected HugeTLB setup in atomic context.\n");
		die_अगर_kernel("HugeTSB in atomic", regs);
	पूर्ण

	tp = &mm->context.tsb_block[MM_TSB_HUGE];
	अगर (likely(tp->tsb == शून्य))
		tsb_grow(mm, MM_TSB_HUGE, 0);

	tsb_context_चयन(mm);
	smp_tsb_sync(mm);

	/* On UltraSPARC-III+ and later, configure the second half of
	 * the Data-TLB क्रम huge pages.
	 */
	अगर (tlb_type == cheetah_plus) अणु
		bool need_context_reload = false;
		अचिन्हित दीर्घ ctx;

		spin_lock_irq(&ctx_alloc_lock);
		ctx = mm->context.sparc64_ctx_val;
		ctx &= ~CTX_PGSZ_MASK;
		ctx |= CTX_PGSZ_BASE << CTX_PGSZ0_SHIFT;
		ctx |= CTX_PGSZ_HUGE << CTX_PGSZ1_SHIFT;

		अगर (ctx != mm->context.sparc64_ctx_val) अणु
			/* When changing the page size fields, we
			 * must perक्रमm a context flush so that no
			 * stale entries match.  This flush must
			 * occur with the original context रेजिस्टर
			 * settings.
			 */
			करो_flush_tlb_mm(mm);

			/* Reload the context रेजिस्टर of all processors
			 * also executing in this address space.
			 */
			mm->context.sparc64_ctx_val = ctx;
			need_context_reload = true;
		पूर्ण
		spin_unlock_irq(&ctx_alloc_lock);

		अगर (need_context_reload)
			on_each_cpu(context_reload, mm, 0);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल काष्ठा resource code_resource = अणु
	.name	= "Kernel code",
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM
पूर्ण;

अटल काष्ठा resource data_resource = अणु
	.name	= "Kernel data",
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM
पूर्ण;

अटल काष्ठा resource bss_resource = अणु
	.name	= "Kernel bss",
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM
पूर्ण;

अटल अंतरभूत resource_माप_प्रकार compute_kern_paddr(व्योम *addr)
अणु
	वापस (resource_माप_प्रकार) (addr - KERNBASE + kern_base);
पूर्ण

अटल व्योम __init kernel_lds_init(व्योम)
अणु
	code_resource.start = compute_kern_paddr(_text);
	code_resource.end   = compute_kern_paddr(_etext - 1);
	data_resource.start = compute_kern_paddr(_etext);
	data_resource.end   = compute_kern_paddr(_edata - 1);
	bss_resource.start  = compute_kern_paddr(__bss_start);
	bss_resource.end    = compute_kern_paddr(_end - 1);
पूर्ण

अटल पूर्णांक __init report_memory(व्योम)
अणु
	पूर्णांक i;
	काष्ठा resource *res;

	kernel_lds_init();

	क्रम (i = 0; i < pavail_ents; i++) अणु
		res = kzalloc(माप(काष्ठा resource), GFP_KERNEL);

		अगर (!res) अणु
			pr_warn("Failed to allocate source.\n");
			अवरोध;
		पूर्ण

		res->name = "System RAM";
		res->start = pavail[i].phys_addr;
		res->end = pavail[i].phys_addr + pavail[i].reg_size - 1;
		res->flags = IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM;

		अगर (insert_resource(&iomem_resource, res) < 0) अणु
			pr_warn("Resource insertion failed.\n");
			अवरोध;
		पूर्ण

		insert_resource(res, &code_resource);
		insert_resource(res, &data_resource);
		insert_resource(res, &bss_resource);
	पूर्ण

	वापस 0;
पूर्ण
arch_initcall(report_memory);

#अगर_घोषित CONFIG_SMP
#घोषणा करो_flush_tlb_kernel_range	smp_flush_tlb_kernel_range
#अन्यथा
#घोषणा करो_flush_tlb_kernel_range	__flush_tlb_kernel_range
#पूर्ण_अगर

व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (start < HI_OBP_ADDRESS && end > LOW_OBP_ADDRESS) अणु
		अगर (start < LOW_OBP_ADDRESS) अणु
			flush_tsb_kernel_range(start, LOW_OBP_ADDRESS);
			करो_flush_tlb_kernel_range(start, LOW_OBP_ADDRESS);
		पूर्ण
		अगर (end > HI_OBP_ADDRESS) अणु
			flush_tsb_kernel_range(HI_OBP_ADDRESS, end);
			करो_flush_tlb_kernel_range(HI_OBP_ADDRESS, end);
		पूर्ण
	पूर्ण अन्यथा अणु
		flush_tsb_kernel_range(start, end);
		करो_flush_tlb_kernel_range(start, end);
	पूर्ण
पूर्ण

व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
	अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	अक्षर *vfrom, *vto;

	vfrom = kmap_atomic(from);
	vto = kmap_atomic(to);
	copy_user_page(vto, vfrom, vaddr, to);
	kunmap_atomic(vto);
	kunmap_atomic(vfrom);

	/* If this page has ADI enabled, copy over any ADI tags
	 * as well
	 */
	अगर (vma->vm_flags & VM_SPARC_ADI) अणु
		अचिन्हित दीर्घ pfrom, pto, i, adi_tag;

		pfrom = page_to_phys(from);
		pto = page_to_phys(to);

		क्रम (i = pfrom; i < (pfrom + PAGE_SIZE); i += adi_blksize()) अणु
			यंत्र अस्थिर("ldxa [%1] %2, %0\n\t"
					: "=r" (adi_tag)
					:  "r" (i), "i" (ASI_MCD_REAL));
			यंत्र अस्थिर("stxa %0, [%1] %2\n\t"
					:
					: "r" (adi_tag), "r" (pto),
					  "i" (ASI_MCD_REAL));
			pto += adi_blksize();
		पूर्ण
		यंत्र अस्थिर("membar #Sync\n\t");
	पूर्ण
पूर्ण
EXPORT_SYMBOL(copy_user_highpage);

व्योम copy_highpage(काष्ठा page *to, काष्ठा page *from)
अणु
	अक्षर *vfrom, *vto;

	vfrom = kmap_atomic(from);
	vto = kmap_atomic(to);
	copy_page(vto, vfrom);
	kunmap_atomic(vto);
	kunmap_atomic(vfrom);

	/* If this platक्रमm is ADI enabled, copy any ADI tags
	 * as well
	 */
	अगर (adi_capable()) अणु
		अचिन्हित दीर्घ pfrom, pto, i, adi_tag;

		pfrom = page_to_phys(from);
		pto = page_to_phys(to);

		क्रम (i = pfrom; i < (pfrom + PAGE_SIZE); i += adi_blksize()) अणु
			यंत्र अस्थिर("ldxa [%1] %2, %0\n\t"
					: "=r" (adi_tag)
					:  "r" (i), "i" (ASI_MCD_REAL));
			यंत्र अस्थिर("stxa %0, [%1] %2\n\t"
					:
					: "r" (adi_tag), "r" (pto),
					  "i" (ASI_MCD_REAL));
			pto += adi_blksize();
		पूर्ण
		यंत्र अस्थिर("membar #Sync\n\t");
	पूर्ण
पूर्ण
EXPORT_SYMBOL(copy_highpage);
