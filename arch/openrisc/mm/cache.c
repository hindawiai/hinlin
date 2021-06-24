<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC cache.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2015 Jan Henrik Weinstock <jan.weinstock@rwth-aachen.de>
 */

#समावेश <यंत्र/spr.h>
#समावेश <यंत्र/spr_defs.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

अटल __always_अंतरभूत व्योम cache_loop(काष्ठा page *page, स्थिर अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ paddr = page_to_pfn(page) << PAGE_SHIFT;
	अचिन्हित दीर्घ line = paddr & ~(L1_CACHE_BYTES - 1);

	जबतक (line < paddr + PAGE_SIZE) अणु
		mtspr(reg, line);
		line += L1_CACHE_BYTES;
	पूर्ण
पूर्ण

व्योम local_dcache_page_flush(काष्ठा page *page)
अणु
	cache_loop(page, SPR_DCBFR);
पूर्ण
EXPORT_SYMBOL(local_dcache_page_flush);

व्योम local_icache_page_inv(काष्ठा page *page)
अणु
	cache_loop(page, SPR_ICBIR);
पूर्ण
EXPORT_SYMBOL(local_icache_page_inv);

व्योम update_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
	pte_t *pte)
अणु
	अचिन्हित दीर्घ pfn = pte_val(*pte) >> PAGE_SHIFT;
	काष्ठा page *page = pfn_to_page(pfn);
	पूर्णांक dirty = !test_and_set_bit(PG_dc_clean, &page->flags);

	/*
	 * Since icaches करो not snoop क्रम updated data on OpenRISC, we
	 * must ग_लिखो back and invalidate any dirty pages manually. We
	 * can skip data pages, since they will not end up in icaches.
	 */
	अगर ((vma->vm_flags & VM_EXEC) && dirty)
		sync_icache_dcache(page);
पूर्ण

