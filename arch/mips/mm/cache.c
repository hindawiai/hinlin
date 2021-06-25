<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 - 2003, 06, 07 by Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2007 MIPS Technologies, Inc.
 */
#समावेश <linux/fs.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/kernel.h>
#समावेश <linux/linkage.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/pgtable.h>

/* Cache operations. */
व्योम (*flush_cache_all)(व्योम);
व्योम (*__flush_cache_all)(व्योम);
EXPORT_SYMBOL_GPL(__flush_cache_all);
व्योम (*flush_cache_mm)(काष्ठा mm_काष्ठा *mm);
व्योम (*flush_cache_range)(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
	अचिन्हित दीर्घ end);
व्योम (*flush_cache_page)(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page,
	अचिन्हित दीर्घ pfn);
व्योम (*flush_icache_range)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
EXPORT_SYMBOL_GPL(flush_icache_range);
व्योम (*local_flush_icache_range)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
EXPORT_SYMBOL_GPL(local_flush_icache_range);
व्योम (*__flush_icache_user_range)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम (*__local_flush_icache_user_range)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
EXPORT_SYMBOL_GPL(__local_flush_icache_user_range);

व्योम (*__flush_cache_vmap)(व्योम);
व्योम (*__flush_cache_vunmap)(व्योम);

व्योम (*__flush_kernel_vmap_range)(अचिन्हित दीर्घ vaddr, पूर्णांक size);
EXPORT_SYMBOL_GPL(__flush_kernel_vmap_range);

/* MIPS specअगरic cache operations */
व्योम (*local_flush_data_cache_page)(व्योम * addr);
व्योम (*flush_data_cache_page)(अचिन्हित दीर्घ addr);
व्योम (*flush_icache_all)(व्योम);

EXPORT_SYMBOL_GPL(local_flush_data_cache_page);
EXPORT_SYMBOL(flush_data_cache_page);
EXPORT_SYMBOL(flush_icache_all);

#अगर_घोषित CONFIG_DMA_NONCOHERENT

/* DMA cache operations. */
व्योम (*_dma_cache_wback_inv)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size);
व्योम (*_dma_cache_wback)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size);
व्योम (*_dma_cache_inv)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size);

#पूर्ण_अगर /* CONFIG_DMA_NONCOHERENT */

/*
 * We could optimize the हाल where the cache argument is not BCACHE but
 * that seems very atypical use ...
 */
SYSCALL_DEFINE3(cacheflush, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, bytes,
	अचिन्हित पूर्णांक, cache)
अणु
	अगर (bytes == 0)
		वापस 0;
	अगर (!access_ok((व्योम __user *) addr, bytes))
		वापस -EFAULT;

	__flush_icache_user_range(addr, addr + bytes);

	वापस 0;
पूर्ण

व्योम __flush_dcache_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_mapping_file(page);
	अचिन्हित दीर्घ addr;

	अगर (mapping && !mapping_mapped(mapping)) अणु
		SetPageDcacheDirty(page);
		वापस;
	पूर्ण

	/*
	 * We could delay the flush क्रम the !page_mapping हाल too.  But that
	 * हाल is क्रम exec env/arg pages and those are %99 certainly going to
	 * get faulted पूर्णांकo the tlb (and thus flushed) anyways.
	 */
	अगर (PageHighMem(page))
		addr = (अचिन्हित दीर्घ)kmap_atomic(page);
	अन्यथा
		addr = (अचिन्हित दीर्घ)page_address(page);

	flush_data_cache_page(addr);

	अगर (PageHighMem(page))
		kunmap_atomic((व्योम *)addr);
पूर्ण

EXPORT_SYMBOL(__flush_dcache_page);

व्योम __flush_anon_page(काष्ठा page *page, अचिन्हित दीर्घ vmaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) page_address(page);

	अगर (pages_करो_alias(addr, vmaddr)) अणु
		अगर (page_mapcount(page) && !Page_dcache_dirty(page)) अणु
			व्योम *kaddr;

			kaddr = kmap_coherent(page, vmaddr);
			flush_data_cache_page((अचिन्हित दीर्घ)kaddr);
			kunmap_coherent();
		पूर्ण अन्यथा
			flush_data_cache_page(addr);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(__flush_anon_page);

व्योम __update_cache(अचिन्हित दीर्घ address, pte_t pte)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ pfn, addr;
	पूर्णांक exec = !pte_no_exec(pte) && !cpu_has_ic_fills_f_dc;

	pfn = pte_pfn(pte);
	अगर (unlikely(!pfn_valid(pfn)))
		वापस;
	page = pfn_to_page(pfn);
	अगर (Page_dcache_dirty(page)) अणु
		अगर (PageHighMem(page))
			addr = (अचिन्हित दीर्घ)kmap_atomic(page);
		अन्यथा
			addr = (अचिन्हित दीर्घ)page_address(page);

		अगर (exec || pages_करो_alias(addr, address & PAGE_MASK))
			flush_data_cache_page(addr);

		अगर (PageHighMem(page))
			kunmap_atomic((व्योम *)addr);

		ClearPageDcacheDirty(page);
	पूर्ण
पूर्ण

अचिन्हित दीर्घ _page_cachable_शेष;
EXPORT_SYMBOL(_page_cachable_शेष);

#घोषणा PM(p)	__pgprot(_page_cachable_शेष | (p))

अटल अंतरभूत व्योम setup_protection_map(व्योम)
अणु
	protection_map[0]  = PM(_PAGE_PRESENT | _PAGE_NO_EXEC | _PAGE_NO_READ);
	protection_map[1]  = PM(_PAGE_PRESENT | _PAGE_NO_EXEC);
	protection_map[2]  = PM(_PAGE_PRESENT | _PAGE_NO_EXEC | _PAGE_NO_READ);
	protection_map[3]  = PM(_PAGE_PRESENT | _PAGE_NO_EXEC);
	protection_map[4]  = PM(_PAGE_PRESENT);
	protection_map[5]  = PM(_PAGE_PRESENT);
	protection_map[6]  = PM(_PAGE_PRESENT);
	protection_map[7]  = PM(_PAGE_PRESENT);

	protection_map[8]  = PM(_PAGE_PRESENT | _PAGE_NO_EXEC | _PAGE_NO_READ);
	protection_map[9]  = PM(_PAGE_PRESENT | _PAGE_NO_EXEC);
	protection_map[10] = PM(_PAGE_PRESENT | _PAGE_NO_EXEC | _PAGE_WRITE |
				_PAGE_NO_READ);
	protection_map[11] = PM(_PAGE_PRESENT | _PAGE_NO_EXEC | _PAGE_WRITE);
	protection_map[12] = PM(_PAGE_PRESENT);
	protection_map[13] = PM(_PAGE_PRESENT);
	protection_map[14] = PM(_PAGE_PRESENT | _PAGE_WRITE);
	protection_map[15] = PM(_PAGE_PRESENT | _PAGE_WRITE);
पूर्ण

#अघोषित PM

व्योम cpu_cache_init(व्योम)
अणु
	अगर (cpu_has_3k_cache) अणु
		बाह्य व्योम __weak r3k_cache_init(व्योम);

		r3k_cache_init();
	पूर्ण
	अगर (cpu_has_4k_cache) अणु
		बाह्य व्योम __weak r4k_cache_init(व्योम);

		r4k_cache_init();
	पूर्ण
	अगर (cpu_has_tx39_cache) अणु
		बाह्य व्योम __weak tx39_cache_init(व्योम);

		tx39_cache_init();
	पूर्ण

	अगर (cpu_has_octeon_cache) अणु
		बाह्य व्योम __weak octeon_cache_init(व्योम);

		octeon_cache_init();
	पूर्ण

	setup_protection_map();
पूर्ण
