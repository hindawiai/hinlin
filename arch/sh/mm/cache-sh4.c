<शैली गुरु>
/*
 * arch/sh/mm/cache-sh4.c
 *
 * Copyright (C) 1999, 2000, 2002  Niibe Yutaka
 * Copyright (C) 2001 - 2009  Paul Mundt
 * Copyright (C) 2003  Riअक्षरd Curnow
 * Copyright (c) 2007 STMicroelectronics (R&D) Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/fs.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cache_insns.h>
#समावेश <यंत्र/cacheflush.h>

/*
 * The maximum number of pages we support up to when करोing ranged dcache
 * flushing. Anything exceeding this will simply flush the dcache in its
 * entirety.
 */
#घोषणा MAX_ICACHE_PAGES	32

अटल व्योम __flush_cache_one(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ phys,
			       अचिन्हित दीर्घ exec_offset);

/*
 * Write back the range of D-cache, and purge the I-cache.
 *
 * Called from kernel/module.c:sys_init_module and routine क्रम a.out क्रमmat,
 * संकेत handler code and kprobes code
 */
अटल व्योम sh4_flush_icache_range(व्योम *args)
अणु
	काष्ठा flusher_data *data = args;
	अचिन्हित दीर्घ start, end;
	अचिन्हित दीर्घ flags, v;
	पूर्णांक i;

	start = data->addr1;
	end = data->addr2;

	/* If there are too many pages then just blow away the caches */
	अगर (((end - start) >> PAGE_SHIFT) >= MAX_ICACHE_PAGES) अणु
		local_flush_cache_all(शून्य);
		वापस;
	पूर्ण

	/*
	 * Selectively flush d-cache then invalidate the i-cache.
	 * This is inefficient, so only use this क्रम small ranges.
	 */
	start &= ~(L1_CACHE_BYTES-1);
	end += L1_CACHE_BYTES-1;
	end &= ~(L1_CACHE_BYTES-1);

	local_irq_save(flags);
	jump_to_uncached();

	क्रम (v = start; v < end; v += L1_CACHE_BYTES) अणु
		अचिन्हित दीर्घ icacheaddr;
		पूर्णांक j, n;

		__ocbwb(v);

		icacheaddr = CACHE_IC_ADDRESS_ARRAY | (v &
				cpu_data->icache.entry_mask);

		/* Clear i-cache line valid-bit */
		n = boot_cpu_data.icache.n_aliases;
		क्रम (i = 0; i < cpu_data->icache.ways; i++) अणु
			क्रम (j = 0; j < n; j++)
				__raw_ग_लिखोl(0, icacheaddr + (j * PAGE_SIZE));
			icacheaddr += cpu_data->icache.way_incr;
		पूर्ण
	पूर्ण

	back_to_cached();
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम flush_cache_one(अचिन्हित दीर्घ start, अचिन्हित दीर्घ phys)
अणु
	अचिन्हित दीर्घ flags, exec_offset = 0;

	/*
	 * All types of SH-4 require PC to be uncached to operate on the I-cache.
	 * Some types of SH-4 require PC to be uncached to operate on the D-cache.
	 */
	अगर ((boot_cpu_data.flags & CPU_HAS_P2_FLUSH_BUG) ||
	    (start < CACHE_OC_ADDRESS_ARRAY))
		exec_offset = cached_to_uncached;

	local_irq_save(flags);
	__flush_cache_one(start, phys, exec_offset);
	local_irq_restore(flags);
पूर्ण

/*
 * Write back & invalidate the D-cache of the page.
 * (To aव्योम "alias" issues)
 */
अटल व्योम sh4_flush_dcache_page(व्योम *arg)
अणु
	काष्ठा page *page = arg;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)page_address(page);
#अगर_अघोषित CONFIG_SMP
	काष्ठा address_space *mapping = page_mapping_file(page);

	अगर (mapping && !mapping_mapped(mapping))
		clear_bit(PG_dcache_clean, &page->flags);
	अन्यथा
#पूर्ण_अगर
		flush_cache_one(CACHE_OC_ADDRESS_ARRAY |
				(addr & shm_align_mask), page_to_phys(page));

	wmb();
पूर्ण

/* TODO: Selective icache invalidation through IC address array.. */
अटल व्योम flush_icache_all(व्योम)
अणु
	अचिन्हित दीर्घ flags, ccr;

	local_irq_save(flags);
	jump_to_uncached();

	/* Flush I-cache */
	ccr = __raw_पढ़ोl(SH_CCR);
	ccr |= CCR_CACHE_ICI;
	__raw_ग_लिखोl(ccr, SH_CCR);

	/*
	 * back_to_cached() will take care of the barrier क्रम us, करोn't add
	 * another one!
	 */

	back_to_cached();
	local_irq_restore(flags);
पूर्ण

अटल व्योम flush_dcache_all(व्योम)
अणु
	अचिन्हित दीर्घ addr, end_addr, entry_offset;

	end_addr = CACHE_OC_ADDRESS_ARRAY +
		(current_cpu_data.dcache.sets <<
		 current_cpu_data.dcache.entry_shअगरt) *
			current_cpu_data.dcache.ways;

	entry_offset = 1 << current_cpu_data.dcache.entry_shअगरt;

	क्रम (addr = CACHE_OC_ADDRESS_ARRAY; addr < end_addr; ) अणु
		__raw_ग_लिखोl(0, addr); addr += entry_offset;
		__raw_ग_लिखोl(0, addr); addr += entry_offset;
		__raw_ग_लिखोl(0, addr); addr += entry_offset;
		__raw_ग_लिखोl(0, addr); addr += entry_offset;
		__raw_ग_लिखोl(0, addr); addr += entry_offset;
		__raw_ग_लिखोl(0, addr); addr += entry_offset;
		__raw_ग_लिखोl(0, addr); addr += entry_offset;
		__raw_ग_लिखोl(0, addr); addr += entry_offset;
	पूर्ण
पूर्ण

अटल व्योम sh4_flush_cache_all(व्योम *unused)
अणु
	flush_dcache_all();
	flush_icache_all();
पूर्ण

/*
 * Note : (RPC) since the caches are physically tagged, the only poपूर्णांक
 * of flush_cache_mm क्रम SH-4 is to get rid of aliases from the
 * D-cache.  The assumption अन्यथाwhere, e.g. flush_cache_range, is that
 * lines can stay resident so दीर्घ as the भव address they were
 * accessed with (hence cache set) is in accord with the physical
 * address (i.e. tag).  It's no dअगरferent here.
 *
 * Caller takes mm->mmap_lock.
 */
अटल व्योम sh4_flush_cache_mm(व्योम *arg)
अणु
	काष्ठा mm_काष्ठा *mm = arg;

	अगर (cpu_context(smp_processor_id(), mm) == NO_CONTEXT)
		वापस;

	flush_dcache_all();
पूर्ण

/*
 * Write back and invalidate I/D-caches क्रम the page.
 *
 * ADDR: Virtual Address (U0 address)
 * PFN: Physical page number
 */
अटल व्योम sh4_flush_cache_page(व्योम *args)
अणु
	काष्ठा flusher_data *data = args;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा page *page;
	अचिन्हित दीर्घ address, pfn, phys;
	पूर्णांक map_coherent = 0;
	pmd_t *pmd;
	pte_t *pte;
	व्योम *vaddr;

	vma = data->vma;
	address = data->addr1 & PAGE_MASK;
	pfn = data->addr2;
	phys = pfn << PAGE_SHIFT;
	page = pfn_to_page(pfn);

	अगर (cpu_context(smp_processor_id(), vma->vm_mm) == NO_CONTEXT)
		वापस;

	pmd = pmd_off(vma->vm_mm, address);
	pte = pte_offset_kernel(pmd, address);

	/* If the page isn't present, there is nothing to करो here. */
	अगर (!(pte_val(*pte) & _PAGE_PRESENT))
		वापस;

	अगर ((vma->vm_mm == current->active_mm))
		vaddr = शून्य;
	अन्यथा अणु
		/*
		 * Use kmap_coherent or kmap_atomic to करो flushes क्रम
		 * another ASID than the current one.
		 */
		map_coherent = (current_cpu_data.dcache.n_aliases &&
			test_bit(PG_dcache_clean, &page->flags) &&
			page_mapcount(page));
		अगर (map_coherent)
			vaddr = kmap_coherent(page, address);
		अन्यथा
			vaddr = kmap_atomic(page);

		address = (अचिन्हित दीर्घ)vaddr;
	पूर्ण

	flush_cache_one(CACHE_OC_ADDRESS_ARRAY |
			(address & shm_align_mask), phys);

	अगर (vma->vm_flags & VM_EXEC)
		flush_icache_all();

	अगर (vaddr) अणु
		अगर (map_coherent)
			kunmap_coherent(vaddr);
		अन्यथा
			kunmap_atomic(vaddr);
	पूर्ण
पूर्ण

/*
 * Write back and invalidate D-caches.
 *
 * START, END: Virtual Address (U0 address)
 *
 * NOTE: We need to flush the _physical_ page entry.
 * Flushing the cache lines क्रम U0 only isn't enough.
 * We need to flush क्रम P1 too, which may contain aliases.
 */
अटल व्योम sh4_flush_cache_range(व्योम *args)
अणु
	काष्ठा flusher_data *data = args;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ start, end;

	vma = data->vma;
	start = data->addr1;
	end = data->addr2;

	अगर (cpu_context(smp_processor_id(), vma->vm_mm) == NO_CONTEXT)
		वापस;

	/*
	 * If cache is only 4k-per-way, there are never any 'aliases'.  Since
	 * the cache is physically tagged, the data can just be left in there.
	 */
	अगर (boot_cpu_data.dcache.n_aliases == 0)
		वापस;

	flush_dcache_all();

	अगर (vma->vm_flags & VM_EXEC)
		flush_icache_all();
पूर्ण

/**
 * __flush_cache_one
 *
 * @addr:  address in memory mapped cache array
 * @phys:  P1 address to flush (has to match tags अगर addr has 'A' bit
 *         set i.e. associative ग_लिखो)
 * @exec_offset: set to 0x20000000 अगर flush has to be executed from P2
 *               region अन्यथा 0x0
 *
 * The offset पूर्णांकo the cache array implied by 'addr' selects the
 * 'colour' of the भव address range that will be flushed.  The
 * operation (purge/ग_लिखो-back) is selected by the lower 2 bits of
 * 'phys'.
 */
अटल व्योम __flush_cache_one(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ phys,
			       अचिन्हित दीर्घ exec_offset)
अणु
	पूर्णांक way_count;
	अचिन्हित दीर्घ base_addr = addr;
	काष्ठा cache_info *dcache;
	अचिन्हित दीर्घ way_incr;
	अचिन्हित दीर्घ a, ea, p;
	अचिन्हित दीर्घ temp_pc;

	dcache = &boot_cpu_data.dcache;
	/* Write this way क्रम better assembly. */
	way_count = dcache->ways;
	way_incr = dcache->way_incr;

	/*
	 * Apply exec_offset (i.e. branch to P2 अगर required.).
	 *
	 * FIXME:
	 *
	 *	If I ग_लिखो "=r" क्रम the (temp_pc), it माला_दो this in r6 hence
	 *	trashing exec_offset beक्रमe it's been added on - why?  Hence
	 *	"=&r" as a 'workaround'
	 */
	यंत्र अस्थिर("mov.l 1f, %0\n\t"
		     "add   %1, %0\n\t"
		     "jmp   @%0\n\t"
		     "nop\n\t"
		     ".balign 4\n\t"
		     "1:  .long 2f\n\t"
		     "2:\n" : "=&r" (temp_pc) : "r" (exec_offset));

	/*
	 * We know there will be >=1 iteration, so ग_लिखो as करो-जबतक to aव्योम
	 * poपूर्णांकless nead-of-loop check क्रम 0 iterations.
	 */
	करो अणु
		ea = base_addr + PAGE_SIZE;
		a = base_addr;
		p = phys;

		करो अणु
			*(अस्थिर अचिन्हित दीर्घ *)a = p;
			/*
			 * Next line: पूर्णांकentionally not p+32, saves an add, p
			 * will करो since only the cache tag bits need to
			 * match.
			 */
			*(अस्थिर अचिन्हित दीर्घ *)(a+32) = p;
			a += 64;
			p += 64;
		पूर्ण जबतक (a < ea);

		base_addr += way_incr;
	पूर्ण जबतक (--way_count != 0);
पूर्ण

बाह्य व्योम __weak sh4__flush_region_init(व्योम);

/*
 * SH-4 has भवly indexed and physically tagged cache.
 */
व्योम __init sh4_cache_init(व्योम)
अणु
	prपूर्णांकk("PVR=%08x CVR=%08x PRR=%08x\n",
		__raw_पढ़ोl(CCN_PVR),
		__raw_पढ़ोl(CCN_CVR),
		__raw_पढ़ोl(CCN_PRR));

	local_flush_icache_range	= sh4_flush_icache_range;
	local_flush_dcache_page		= sh4_flush_dcache_page;
	local_flush_cache_all		= sh4_flush_cache_all;
	local_flush_cache_mm		= sh4_flush_cache_mm;
	local_flush_cache_dup_mm	= sh4_flush_cache_mm;
	local_flush_cache_page		= sh4_flush_cache_page;
	local_flush_cache_range		= sh4_flush_cache_range;

	sh4__flush_region_init();
पूर्ण
