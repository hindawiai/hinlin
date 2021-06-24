<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/mm/flush.c
 *
 * Copyright (C) 1995-2002 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/tlbflush.h>

व्योम sync_icache_aliases(व्योम *kaddr, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)kaddr;

	अगर (icache_is_aliasing()) अणु
		__clean_dcache_area_pou(kaddr, len);
		__flush_icache_all();
	पूर्ण अन्यथा अणु
		/*
		 * Don't issue kick_all_cpus_sync() after I-cache invalidation
		 * क्रम user mappings.
		 */
		__flush_icache_range(addr, addr + len);
	पूर्ण
पूर्ण

अटल व्योम flush_ptrace_access(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
				अचिन्हित दीर्घ uaddr, व्योम *kaddr,
				अचिन्हित दीर्घ len)
अणु
	अगर (vma->vm_flags & VM_EXEC)
		sync_icache_aliases(kaddr, len);
पूर्ण

/*
 * Copy user data from/to a page which is mapped पूर्णांकo a dअगरferent processes
 * address space.  Really, we want to allow our "user space" model to handle
 * this.
 */
व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
		       अचिन्हित दीर्घ uaddr, व्योम *dst, स्थिर व्योम *src,
		       अचिन्हित दीर्घ len)
अणु
	स_नकल(dst, src, len);
	flush_ptrace_access(vma, page, uaddr, dst, len);
पूर्ण

व्योम __sync_icache_dcache(pte_t pte)
अणु
	काष्ठा page *page = pte_page(pte);

	अगर (!test_bit(PG_dcache_clean, &page->flags)) अणु
		sync_icache_aliases(page_address(page), page_size(page));
		set_bit(PG_dcache_clean, &page->flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__sync_icache_dcache);

/*
 * This function is called when a page has been modअगरied by the kernel. Mark
 * it as dirty क्रम later flushing when mapped in user space (अगर executable,
 * see __sync_icache_dcache).
 */
व्योम flush_dcache_page(काष्ठा page *page)
अणु
	अगर (test_bit(PG_dcache_clean, &page->flags))
		clear_bit(PG_dcache_clean, &page->flags);
पूर्ण
EXPORT_SYMBOL(flush_dcache_page);

/*
 * Additional functions defined in assembly.
 */
EXPORT_SYMBOL(__flush_icache_range);

#अगर_घोषित CONFIG_ARCH_HAS_PMEM_API
व्योम arch_wb_cache_pmem(व्योम *addr, माप_प्रकार size)
अणु
	/* Ensure order against any prior non-cacheable ग_लिखोs */
	dmb(osh);
	__clean_dcache_area_pop(addr, size);
पूर्ण
EXPORT_SYMBOL_GPL(arch_wb_cache_pmem);

व्योम arch_invalidate_pmem(व्योम *addr, माप_प्रकार size)
अणु
	__inval_dcache_area(addr, size);
पूर्ण
EXPORT_SYMBOL_GPL(arch_invalidate_pmem);
#पूर्ण_अगर
