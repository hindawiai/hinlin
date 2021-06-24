<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cachectl.h>

#घोषणा PG_dcache_clean		PG_arch_1

व्योम flush_dcache_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping;

	अगर (page == ZERO_PAGE(0))
		वापस;

	mapping = page_mapping_file(page);

	अगर (mapping && !page_mapcount(page))
		clear_bit(PG_dcache_clean, &page->flags);
	अन्यथा अणु
		dcache_wbinv_all();
		अगर (mapping)
			icache_inv_all();
		set_bit(PG_dcache_clean, &page->flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flush_dcache_page);

व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
	pte_t *ptep)
अणु
	अचिन्हित दीर्घ pfn = pte_pfn(*ptep);
	काष्ठा page *page;

	अगर (!pfn_valid(pfn))
		वापस;

	page = pfn_to_page(pfn);
	अगर (page == ZERO_PAGE(0))
		वापस;

	अगर (!test_and_set_bit(PG_dcache_clean, &page->flags))
		dcache_wbinv_all();

	अगर (page_mapping_file(page)) अणु
		अगर (vma->vm_flags & VM_EXEC)
			icache_inv_all();
	पूर्ण
पूर्ण

व्योम flush_kernel_dcache_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping;

	mapping = page_mapping_file(page);

	अगर (!mapping || mapping_mapped(mapping))
		dcache_wbinv_all();
पूर्ण
EXPORT_SYMBOL(flush_kernel_dcache_page);

व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
	अचिन्हित दीर्घ end)
अणु
	dcache_wbinv_all();

	अगर (vma->vm_flags & VM_EXEC)
		icache_inv_all();
पूर्ण
