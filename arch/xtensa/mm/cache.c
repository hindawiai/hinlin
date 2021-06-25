<शैली गुरु>
/*
 * arch/xtensa/mm/cache.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001-2006 Tensilica Inc.
 *
 * Chris Zankel	<chris@zankel.net>
 * Joe Taylor
 * Marc Gauthier
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/memblock.h>
#समावेश <linux/swap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/bootparam.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/page.h>

/* 
 * Note:
 * The kernel provides one architecture bit PG_arch_1 in the page flags that 
 * can be used क्रम cache coherency.
 *
 * I$-D$ coherency.
 *
 * The Xtensa architecture करोesn't keep the inकाष्ठाion cache coherent with
 * the data cache. We use the architecture bit to indicate अगर the caches
 * are coherent. The kernel clears this bit whenever a page is added to the
 * page cache. At that समय, the caches might not be in sync. We, thereक्रमe,
 * define this flag as 'clean' अगर set.
 *
 * D-cache aliasing.
 *
 * With cache aliasing, we have to always flush the cache when pages are
 * unmapped (see tlb_start_vma(). So, we use this flag to indicate a dirty
 * page.
 * 
 *
 *
 */

#अगर (DCACHE_WAY_SIZE > PAGE_SIZE)
अटल अंतरभूत व्योम kmap_invalidate_coherent(काष्ठा page *page,
					    अचिन्हित दीर्घ vaddr)
अणु
	अगर (!DCACHE_ALIAS_EQ(page_to_phys(page), vaddr)) अणु
		अचिन्हित दीर्घ kvaddr;

		अगर (!PageHighMem(page)) अणु
			kvaddr = (अचिन्हित दीर्घ)page_to_virt(page);

			__invalidate_dcache_page(kvaddr);
		पूर्ण अन्यथा अणु
			kvaddr = TLBTEMP_BASE_1 +
				(page_to_phys(page) & DCACHE_ALIAS_MASK);

			preempt_disable();
			__invalidate_dcache_page_alias(kvaddr,
						       page_to_phys(page));
			preempt_enable();
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम *coherent_kvaddr(काष्ठा page *page, अचिन्हित दीर्घ base,
				    अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ *paddr)
अणु
	*paddr = page_to_phys(page);
	वापस (व्योम *)(base + (vaddr & DCACHE_ALIAS_MASK));
पूर्ण

व्योम clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr)
अणु
	अचिन्हित दीर्घ paddr;
	व्योम *kvaddr = coherent_kvaddr(page, TLBTEMP_BASE_1, vaddr, &paddr);

	preempt_disable();
	kmap_invalidate_coherent(page, vaddr);
	set_bit(PG_arch_1, &page->flags);
	clear_page_alias(kvaddr, paddr);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(clear_user_highpage);

व्योम copy_user_highpage(काष्ठा page *dst, काष्ठा page *src,
			अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ dst_paddr, src_paddr;
	व्योम *dst_vaddr = coherent_kvaddr(dst, TLBTEMP_BASE_1, vaddr,
					  &dst_paddr);
	व्योम *src_vaddr = coherent_kvaddr(src, TLBTEMP_BASE_2, vaddr,
					  &src_paddr);

	preempt_disable();
	kmap_invalidate_coherent(dst, vaddr);
	set_bit(PG_arch_1, &dst->flags);
	copy_page_alias(dst_vaddr, src_vaddr, dst_paddr, src_paddr);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(copy_user_highpage);

/*
 * Any समय the kernel ग_लिखोs to a user page cache page, or it is about to
 * पढ़ो from a page cache page this routine is called.
 *
 */

व्योम flush_dcache_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_mapping_file(page);

	/*
	 * If we have a mapping but the page is not mapped to user-space
	 * yet, we simply mark this page dirty and defer flushing the 
	 * caches until update_mmu().
	 */

	अगर (mapping && !mapping_mapped(mapping)) अणु
		अगर (!test_bit(PG_arch_1, &page->flags))
			set_bit(PG_arch_1, &page->flags);
		वापस;

	पूर्ण अन्यथा अणु

		अचिन्हित दीर्घ phys = page_to_phys(page);
		अचिन्हित दीर्घ temp = page->index << PAGE_SHIFT;
		अचिन्हित दीर्घ alias = !(DCACHE_ALIAS_EQ(temp, phys));
		अचिन्हित दीर्घ virt;

		/* 
		 * Flush the page in kernel space and user space.
		 * Note that we can omit that step अगर aliasing is not
		 * an issue, but we करो have to synchronize I$ and D$
		 * अगर we have a mapping.
		 */

		अगर (!alias && !mapping)
			वापस;

		preempt_disable();
		virt = TLBTEMP_BASE_1 + (phys & DCACHE_ALIAS_MASK);
		__flush_invalidate_dcache_page_alias(virt, phys);

		virt = TLBTEMP_BASE_1 + (temp & DCACHE_ALIAS_MASK);

		अगर (alias)
			__flush_invalidate_dcache_page_alias(virt, phys);

		अगर (mapping)
			__invalidate_icache_page_alias(virt, phys);
		preempt_enable();
	पूर्ण

	/* There shouldn't be an entry in the cache क्रम this page anymore. */
पूर्ण
EXPORT_SYMBOL(flush_dcache_page);

/*
 * For now, flush the whole cache. FIXME??
 */

व्योम local_flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
		       अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	__flush_invalidate_dcache_all();
	__invalidate_icache_all();
पूर्ण
EXPORT_SYMBOL(local_flush_cache_range);

/* 
 * Remove any entry in the cache क्रम this page. 
 *
 * Note that this function is only called क्रम user pages, so use the
 * alias versions of the cache flush functions.
 */

व्योम local_flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		      अचिन्हित दीर्घ pfn)
अणु
	/* Note that we have to use the 'alias' address to aव्योम multi-hit */

	अचिन्हित दीर्घ phys = page_to_phys(pfn_to_page(pfn));
	अचिन्हित दीर्घ virt = TLBTEMP_BASE_1 + (address & DCACHE_ALIAS_MASK);

	preempt_disable();
	__flush_invalidate_dcache_page_alias(virt, phys);
	__invalidate_icache_page_alias(virt, phys);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(local_flush_cache_page);

#पूर्ण_अगर /* DCACHE_WAY_SIZE > PAGE_SIZE */

व्योम
update_mmu_cache(काष्ठा vm_area_काष्ठा * vma, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	अचिन्हित दीर्घ pfn = pte_pfn(*ptep);
	काष्ठा page *page;

	अगर (!pfn_valid(pfn))
		वापस;

	page = pfn_to_page(pfn);

	/* Invalidate old entry in TLBs */

	flush_tlb_page(vma, addr);

#अगर (DCACHE_WAY_SIZE > PAGE_SIZE)

	अगर (!PageReserved(page) && test_bit(PG_arch_1, &page->flags)) अणु
		अचिन्हित दीर्घ phys = page_to_phys(page);
		अचिन्हित दीर्घ पंचांगp;

		preempt_disable();
		पंचांगp = TLBTEMP_BASE_1 + (phys & DCACHE_ALIAS_MASK);
		__flush_invalidate_dcache_page_alias(पंचांगp, phys);
		पंचांगp = TLBTEMP_BASE_1 + (addr & DCACHE_ALIAS_MASK);
		__flush_invalidate_dcache_page_alias(पंचांगp, phys);
		__invalidate_icache_page_alias(पंचांगp, phys);
		preempt_enable();

		clear_bit(PG_arch_1, &page->flags);
	पूर्ण
#अन्यथा
	अगर (!PageReserved(page) && !test_bit(PG_arch_1, &page->flags)
	    && (vma->vm_flags & VM_EXEC) != 0) अणु
		अचिन्हित दीर्घ paddr = (अचिन्हित दीर्घ)kmap_atomic(page);
		__flush_dcache_page(paddr);
		__invalidate_icache_page(paddr);
		set_bit(PG_arch_1, &page->flags);
		kunmap_atomic((व्योम *)paddr);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * access_process_vm() has called get_user_pages(), which has करोne a
 * flush_dcache_page() on the page.
 */

#अगर (DCACHE_WAY_SIZE > PAGE_SIZE)

व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
		अचिन्हित दीर्घ vaddr, व्योम *dst, स्थिर व्योम *src,
		अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ phys = page_to_phys(page);
	अचिन्हित दीर्घ alias = !(DCACHE_ALIAS_EQ(vaddr, phys));

	/* Flush and invalidate user page अगर aliased. */

	अगर (alias) अणु
		अचिन्हित दीर्घ t = TLBTEMP_BASE_1 + (vaddr & DCACHE_ALIAS_MASK);
		preempt_disable();
		__flush_invalidate_dcache_page_alias(t, phys);
		preempt_enable();
	पूर्ण

	/* Copy data */
	
	स_नकल(dst, src, len);

	/*
	 * Flush and invalidate kernel page अगर aliased and synchronize 
	 * data and inकाष्ठाion caches क्रम executable pages. 
	 */

	अगर (alias) अणु
		अचिन्हित दीर्घ t = TLBTEMP_BASE_1 + (vaddr & DCACHE_ALIAS_MASK);

		preempt_disable();
		__flush_invalidate_dcache_range((अचिन्हित दीर्घ) dst, len);
		अगर ((vma->vm_flags & VM_EXEC) != 0)
			__invalidate_icache_page_alias(t, phys);
		preempt_enable();

	पूर्ण अन्यथा अगर ((vma->vm_flags & VM_EXEC) != 0) अणु
		__flush_dcache_range((अचिन्हित दीर्घ)dst,len);
		__invalidate_icache_range((अचिन्हित दीर्घ) dst, len);
	पूर्ण
पूर्ण

बाह्य व्योम copy_from_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
		अचिन्हित दीर्घ vaddr, व्योम *dst, स्थिर व्योम *src,
		अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ phys = page_to_phys(page);
	अचिन्हित दीर्घ alias = !(DCACHE_ALIAS_EQ(vaddr, phys));

	/*
	 * Flush user page अगर aliased. 
	 * (Note: a simply flush would be sufficient) 
	 */

	अगर (alias) अणु
		अचिन्हित दीर्घ t = TLBTEMP_BASE_1 + (vaddr & DCACHE_ALIAS_MASK);
		preempt_disable();
		__flush_invalidate_dcache_page_alias(t, phys);
		preempt_enable();
	पूर्ण

	स_नकल(dst, src, len);
पूर्ण

#पूर्ण_अगर
