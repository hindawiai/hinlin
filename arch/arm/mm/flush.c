<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/flush.c
 *
 *  Copyright (C) 1995-2002 Russell King
 */
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cachetype.h>
#समावेश <यंत्र/highस्मृति.स>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <linux/hugetlb.h>

#समावेश "mm.h"

#अगर_घोषित CONFIG_ARM_HEAVY_MB
व्योम (*soc_mb)(व्योम);

व्योम arm_heavy_mb(व्योम)
अणु
#अगर_घोषित CONFIG_OUTER_CACHE_SYNC
	अगर (outer_cache.sync)
		outer_cache.sync();
#पूर्ण_अगर
	अगर (soc_mb)
		soc_mb();
पूर्ण
EXPORT_SYMBOL(arm_heavy_mb);
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_CACHE_VIPT

अटल व्योम flush_pfn_alias(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ vaddr)
अणु
	अचिन्हित दीर्घ to = FLUSH_ALIAS_START + (CACHE_COLOUR(vaddr) << PAGE_SHIFT);
	स्थिर पूर्णांक zero = 0;

	set_top_pte(to, pfn_pte(pfn, PAGE_KERNEL));

	यंत्र(	"mcrr	p15, 0, %1, %0, c14\n"
	"	mcr	p15, 0, %2, c7, c10, 4"
	    :
	    : "r" (to), "r" (to + PAGE_SIZE - 1), "r" (zero)
	    : "cc");
पूर्ण

अटल व्योम flush_icache_alias(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ va = FLUSH_ALIAS_START + (CACHE_COLOUR(vaddr) << PAGE_SHIFT);
	अचिन्हित दीर्घ offset = vaddr & (PAGE_SIZE - 1);
	अचिन्हित दीर्घ to;

	set_top_pte(va, pfn_pte(pfn, PAGE_KERNEL));
	to = va + offset;
	flush_icache_range(to, to + len);
पूर्ण

व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (cache_is_vivt()) अणु
		vivt_flush_cache_mm(mm);
		वापस;
	पूर्ण

	अगर (cache_is_vipt_aliasing()) अणु
		यंत्र(	"mcr	p15, 0, %0, c7, c14, 0\n"
		"	mcr	p15, 0, %0, c7, c10, 4"
		    :
		    : "r" (0)
		    : "cc");
	पूर्ण
पूर्ण

व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (cache_is_vivt()) अणु
		vivt_flush_cache_range(vma, start, end);
		वापस;
	पूर्ण

	अगर (cache_is_vipt_aliasing()) अणु
		यंत्र(	"mcr	p15, 0, %0, c7, c14, 0\n"
		"	mcr	p15, 0, %0, c7, c10, 4"
		    :
		    : "r" (0)
		    : "cc");
	पूर्ण

	अगर (vma->vm_flags & VM_EXEC)
		__flush_icache_all();
पूर्ण

व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ user_addr, अचिन्हित दीर्घ pfn)
अणु
	अगर (cache_is_vivt()) अणु
		vivt_flush_cache_page(vma, user_addr, pfn);
		वापस;
	पूर्ण

	अगर (cache_is_vipt_aliasing()) अणु
		flush_pfn_alias(pfn, user_addr);
		__flush_icache_all();
	पूर्ण

	अगर (vma->vm_flags & VM_EXEC && icache_is_vivt_asid_tagged())
		__flush_icache_all();
पूर्ण

#अन्यथा
#घोषणा flush_pfn_alias(pfn,vaddr)		करो अणु पूर्ण जबतक (0)
#घोषणा flush_icache_alias(pfn,vaddr,len)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा FLAG_PA_IS_EXEC 1
#घोषणा FLAG_PA_CORE_IN_MM 2

अटल व्योम flush_ptrace_access_other(व्योम *args)
अणु
	__flush_icache_all();
पूर्ण

अटल अंतरभूत
व्योम __flush_ptrace_access(काष्ठा page *page, अचिन्हित दीर्घ uaddr, व्योम *kaddr,
			   अचिन्हित दीर्घ len, अचिन्हित पूर्णांक flags)
अणु
	अगर (cache_is_vivt()) अणु
		अगर (flags & FLAG_PA_CORE_IN_MM) अणु
			अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)kaddr;
			__cpuc_coherent_kern_range(addr, addr + len);
		पूर्ण
		वापस;
	पूर्ण

	अगर (cache_is_vipt_aliasing()) अणु
		flush_pfn_alias(page_to_pfn(page), uaddr);
		__flush_icache_all();
		वापस;
	पूर्ण

	/* VIPT non-aliasing D-cache */
	अगर (flags & FLAG_PA_IS_EXEC) अणु
		अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)kaddr;
		अगर (icache_is_vipt_aliasing())
			flush_icache_alias(page_to_pfn(page), uaddr, len);
		अन्यथा
			__cpuc_coherent_kern_range(addr, addr + len);
		अगर (cache_ops_need_broadcast())
			smp_call_function(flush_ptrace_access_other,
					  शून्य, 1);
	पूर्ण
पूर्ण

अटल
व्योम flush_ptrace_access(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			 अचिन्हित दीर्घ uaddr, व्योम *kaddr, अचिन्हित दीर्घ len)
अणु
	अचिन्हित पूर्णांक flags = 0;
	अगर (cpumask_test_cpu(smp_processor_id(), mm_cpumask(vma->vm_mm)))
		flags |= FLAG_PA_CORE_IN_MM;
	अगर (vma->vm_flags & VM_EXEC)
		flags |= FLAG_PA_IS_EXEC;
	__flush_ptrace_access(page, uaddr, kaddr, len, flags);
पूर्ण

व्योम flush_uprobe_xol_access(काष्ठा page *page, अचिन्हित दीर्घ uaddr,
			     व्योम *kaddr, अचिन्हित दीर्घ len)
अणु
	अचिन्हित पूर्णांक flags = FLAG_PA_CORE_IN_MM|FLAG_PA_IS_EXEC;

	__flush_ptrace_access(page, uaddr, kaddr, len, flags);
पूर्ण

/*
 * Copy user data from/to a page which is mapped पूर्णांकo a dअगरferent
 * processes address space.  Really, we want to allow our "user
 * space" model to handle this.
 *
 * Note that this code needs to run on the current CPU.
 */
व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
		       अचिन्हित दीर्घ uaddr, व्योम *dst, स्थिर व्योम *src,
		       अचिन्हित दीर्घ len)
अणु
#अगर_घोषित CONFIG_SMP
	preempt_disable();
#पूर्ण_अगर
	स_नकल(dst, src, len);
	flush_ptrace_access(vma, page, uaddr, dst, len);
#अगर_घोषित CONFIG_SMP
	preempt_enable();
#पूर्ण_अगर
पूर्ण

व्योम __flush_dcache_page(काष्ठा address_space *mapping, काष्ठा page *page)
अणु
	/*
	 * Writeback any data associated with the kernel mapping of this
	 * page.  This ensures that data in the physical page is mutually
	 * coherent with the kernels mapping.
	 */
	अगर (!PageHighMem(page)) अणु
		__cpuc_flush_dcache_area(page_address(page), page_size(page));
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ i;
		अगर (cache_is_vipt_nonaliasing()) अणु
			क्रम (i = 0; i < compound_nr(page); i++) अणु
				व्योम *addr = kmap_atomic(page + i);
				__cpuc_flush_dcache_area(addr, PAGE_SIZE);
				kunmap_atomic(addr);
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < compound_nr(page); i++) अणु
				व्योम *addr = kmap_high_get(page + i);
				अगर (addr) अणु
					__cpuc_flush_dcache_area(addr, PAGE_SIZE);
					kunmap_high(page + i);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If this is a page cache page, and we have an aliasing VIPT cache,
	 * we only need to करो one flush - which would be at the relevant
	 * userspace colour, which is congruent with page->index.
	 */
	अगर (mapping && cache_is_vipt_aliasing())
		flush_pfn_alias(page_to_pfn(page),
				page->index << PAGE_SHIFT);
पूर्ण

अटल व्योम __flush_dcache_aliases(काष्ठा address_space *mapping, काष्ठा page *page)
अणु
	काष्ठा mm_काष्ठा *mm = current->active_mm;
	काष्ठा vm_area_काष्ठा *mpnt;
	pgoff_t pgoff;

	/*
	 * There are possible user space mappings of this page:
	 * - VIVT cache: we need to also ग_लिखो back and invalidate all user
	 *   data in the current VM view associated with this page.
	 * - aliasing VIPT: we only need to find one mapping of this page.
	 */
	pgoff = page->index;

	flush_dcache_mmap_lock(mapping);
	vma_पूर्णांकerval_tree_क्रमeach(mpnt, &mapping->i_mmap, pgoff, pgoff) अणु
		अचिन्हित दीर्घ offset;

		/*
		 * If this VMA is not in our MM, we can ignore it.
		 */
		अगर (mpnt->vm_mm != mm)
			जारी;
		अगर (!(mpnt->vm_flags & VM_MAYSHARE))
			जारी;
		offset = (pgoff - mpnt->vm_pgoff) << PAGE_SHIFT;
		flush_cache_page(mpnt, mpnt->vm_start + offset, page_to_pfn(page));
	पूर्ण
	flush_dcache_mmap_unlock(mapping);
पूर्ण

#अगर __LINUX_ARM_ARCH__ >= 6
व्योम __sync_icache_dcache(pte_t pteval)
अणु
	अचिन्हित दीर्घ pfn;
	काष्ठा page *page;
	काष्ठा address_space *mapping;

	अगर (cache_is_vipt_nonaliasing() && !pte_exec(pteval))
		/* only flush non-aliasing VIPT caches क्रम exec mappings */
		वापस;
	pfn = pte_pfn(pteval);
	अगर (!pfn_valid(pfn))
		वापस;

	page = pfn_to_page(pfn);
	अगर (cache_is_vipt_aliasing())
		mapping = page_mapping_file(page);
	अन्यथा
		mapping = शून्य;

	अगर (!test_and_set_bit(PG_dcache_clean, &page->flags))
		__flush_dcache_page(mapping, page);

	अगर (pte_exec(pteval))
		__flush_icache_all();
पूर्ण
#पूर्ण_अगर

/*
 * Ensure cache coherency between kernel mapping and userspace mapping
 * of this page.
 *
 * We have three हालs to consider:
 *  - VIPT non-aliasing cache: fully coherent so nothing required.
 *  - VIVT: fully aliasing, so we need to handle every alias in our
 *          current VM view.
 *  - VIPT aliasing: need to handle one alias in our current VM view.
 *
 * If we need to handle aliasing:
 *  If the page only exists in the page cache and there are no user
 *  space mappings, we can be lazy and remember that we may have dirty
 *  kernel cache lines क्रम later.  Otherwise, we assume we have
 *  aliasing mappings.
 *
 * Note that we disable the lazy flush क्रम SMP configurations where
 * the cache मुख्यtenance operations are not स्वतःmatically broadcasted.
 */
व्योम flush_dcache_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping;

	/*
	 * The zero page is never written to, so never has any dirty
	 * cache lines, and thereक्रमe never needs to be flushed.
	 */
	अगर (page == ZERO_PAGE(0))
		वापस;

	अगर (!cache_ops_need_broadcast() && cache_is_vipt_nonaliasing()) अणु
		अगर (test_bit(PG_dcache_clean, &page->flags))
			clear_bit(PG_dcache_clean, &page->flags);
		वापस;
	पूर्ण

	mapping = page_mapping_file(page);

	अगर (!cache_ops_need_broadcast() &&
	    mapping && !page_mapcount(page))
		clear_bit(PG_dcache_clean, &page->flags);
	अन्यथा अणु
		__flush_dcache_page(mapping, page);
		अगर (mapping && cache_is_vivt())
			__flush_dcache_aliases(mapping, page);
		अन्यथा अगर (mapping)
			__flush_icache_all();
		set_bit(PG_dcache_clean, &page->flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flush_dcache_page);

/*
 * Ensure cache coherency क्रम the kernel mapping of this page. We can
 * assume that the page is pinned via kmap.
 *
 * If the page only exists in the page cache and there are no user
 * space mappings, this is a no-op since the page was alपढ़ोy marked
 * dirty at creation.  Otherwise, we need to flush the dirty kernel
 * cache lines directly.
 */
व्योम flush_kernel_dcache_page(काष्ठा page *page)
अणु
	अगर (cache_is_vivt() || cache_is_vipt_aliasing()) अणु
		काष्ठा address_space *mapping;

		mapping = page_mapping_file(page);

		अगर (!mapping || mapping_mapped(mapping)) अणु
			व्योम *addr;

			addr = page_address(page);
			/*
			 * kmap_atomic() करोesn't set the page भव
			 * address क्रम highmem pages, and
			 * kunmap_atomic() takes care of cache
			 * flushing alपढ़ोy.
			 */
			अगर (!IS_ENABLED(CONFIG_HIGHMEM) || addr)
				__cpuc_flush_dcache_area(addr, PAGE_SIZE);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flush_kernel_dcache_page);

/*
 * Flush an anonymous page so that users of get_user_pages()
 * can safely access the data.  The expected sequence is:
 *
 *  get_user_pages()
 *    -> flush_anon_page
 *  स_नकल() to/from page
 *  अगर written to page, flush_dcache_page()
 */
व्योम __flush_anon_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page, अचिन्हित दीर्घ vmaddr)
अणु
	अचिन्हित दीर्घ pfn;

	/* VIPT non-aliasing caches need करो nothing */
	अगर (cache_is_vipt_nonaliasing())
		वापस;

	/*
	 * Write back and invalidate userspace mapping.
	 */
	pfn = page_to_pfn(page);
	अगर (cache_is_vivt()) अणु
		flush_cache_page(vma, vmaddr, pfn);
	पूर्ण अन्यथा अणु
		/*
		 * For aliasing VIPT, we can flush an alias of the
		 * userspace address only.
		 */
		flush_pfn_alias(pfn, vmaddr);
		__flush_icache_all();
	पूर्ण

	/*
	 * Invalidate kernel mapping.  No data should be contained
	 * in this mapping of the page.  FIXME: this is overसमाप्त
	 * since we actually ask क्रम a ग_लिखो-back and invalidate.
	 */
	__cpuc_flush_dcache_area(page_address(page), PAGE_SIZE);
पूर्ण
