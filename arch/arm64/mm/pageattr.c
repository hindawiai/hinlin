<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/tlbflush.h>

काष्ठा page_change_data अणु
	pgprot_t set_mask;
	pgprot_t clear_mask;
पूर्ण;

bool rodata_full __ro_after_init = IS_ENABLED(CONFIG_RODATA_FULL_DEFAULT_ENABLED);

अटल पूर्णांक change_page_range(pte_t *ptep, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	काष्ठा page_change_data *cdata = data;
	pte_t pte = READ_ONCE(*ptep);

	pte = clear_pte_bit(pte, cdata->clear_mask);
	pte = set_pte_bit(pte, cdata->set_mask);

	set_pte(ptep, pte);
	वापस 0;
पूर्ण

/*
 * This function assumes that the range is mapped with PAGE_SIZE pages.
 */
अटल पूर्णांक __change_memory_common(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
				pgprot_t set_mask, pgprot_t clear_mask)
अणु
	काष्ठा page_change_data data;
	पूर्णांक ret;

	data.set_mask = set_mask;
	data.clear_mask = clear_mask;

	ret = apply_to_page_range(&init_mm, start, size, change_page_range,
					&data);

	flush_tlb_kernel_range(start, start + size);
	वापस ret;
पूर्ण

अटल पूर्णांक change_memory_common(अचिन्हित दीर्घ addr, पूर्णांक numpages,
				pgprot_t set_mask, pgprot_t clear_mask)
अणु
	अचिन्हित दीर्घ start = addr;
	अचिन्हित दीर्घ size = PAGE_SIZE * numpages;
	अचिन्हित दीर्घ end = start + size;
	काष्ठा vm_काष्ठा *area;
	पूर्णांक i;

	अगर (!PAGE_ALIGNED(addr)) अणु
		start &= PAGE_MASK;
		end = start + size;
		WARN_ON_ONCE(1);
	पूर्ण

	/*
	 * Kernel VA mappings are always live, and splitting live section
	 * mappings पूर्णांकo page mappings may cause TLB conflicts. This means
	 * we have to ensure that changing the permission bits of the range
	 * we are operating on करोes not result in such splitting.
	 *
	 * Let's restrict ourselves to mappings created by vदो_स्मृति (or vmap).
	 * Those are guaranteed to consist entirely of page mappings, and
	 * splitting is never needed.
	 *
	 * So check whether the [addr, addr + size) पूर्णांकerval is entirely
	 * covered by precisely one VM area that has the VM_ALLOC flag set.
	 */
	area = find_vm_area((व्योम *)addr);
	अगर (!area ||
	    end > (अचिन्हित दीर्घ)area->addr + area->size ||
	    !(area->flags & VM_ALLOC))
		वापस -EINVAL;

	अगर (!numpages)
		वापस 0;

	/*
	 * If we are manipulating पढ़ो-only permissions, apply the same
	 * change to the linear mapping of the pages that back this VM area.
	 */
	अगर (rodata_full && (pgprot_val(set_mask) == PTE_RDONLY ||
			    pgprot_val(clear_mask) == PTE_RDONLY)) अणु
		क्रम (i = 0; i < area->nr_pages; i++) अणु
			__change_memory_common((u64)page_address(area->pages[i]),
					       PAGE_SIZE, set_mask, clear_mask);
		पूर्ण
	पूर्ण

	/*
	 * Get rid of potentially aliasing lazily unmapped vm areas that may
	 * have permissions set that deviate from the ones we are setting here.
	 */
	vm_unmap_aliases();

	वापस __change_memory_common(start, size, set_mask, clear_mask);
पूर्ण

पूर्णांक set_memory_ro(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_memory_common(addr, numpages,
					__pgprot(PTE_RDONLY),
					__pgprot(PTE_WRITE));
पूर्ण

पूर्णांक set_memory_rw(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_memory_common(addr, numpages,
					__pgprot(PTE_WRITE),
					__pgprot(PTE_RDONLY));
पूर्ण

पूर्णांक set_memory_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_memory_common(addr, numpages,
					__pgprot(PTE_PXN),
					__pgprot(PTE_MAYBE_GP));
पूर्ण

पूर्णांक set_memory_x(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस change_memory_common(addr, numpages,
					__pgprot(PTE_MAYBE_GP),
					__pgprot(PTE_PXN));
पूर्ण

पूर्णांक set_memory_valid(अचिन्हित दीर्घ addr, पूर्णांक numpages, पूर्णांक enable)
अणु
	अगर (enable)
		वापस __change_memory_common(addr, PAGE_SIZE * numpages,
					__pgprot(PTE_VALID),
					__pgprot(0));
	अन्यथा
		वापस __change_memory_common(addr, PAGE_SIZE * numpages,
					__pgprot(0),
					__pgprot(PTE_VALID));
पूर्ण

पूर्णांक set_direct_map_invalid_noflush(काष्ठा page *page)
अणु
	काष्ठा page_change_data data = अणु
		.set_mask = __pgprot(0),
		.clear_mask = __pgprot(PTE_VALID),
	पूर्ण;

	अगर (!debug_pagealloc_enabled() && !rodata_full)
		वापस 0;

	वापस apply_to_page_range(&init_mm,
				   (अचिन्हित दीर्घ)page_address(page),
				   PAGE_SIZE, change_page_range, &data);
पूर्ण

पूर्णांक set_direct_map_शेष_noflush(काष्ठा page *page)
अणु
	काष्ठा page_change_data data = अणु
		.set_mask = __pgprot(PTE_VALID | PTE_WRITE),
		.clear_mask = __pgprot(PTE_RDONLY),
	पूर्ण;

	अगर (!debug_pagealloc_enabled() && !rodata_full)
		वापस 0;

	वापस apply_to_page_range(&init_mm,
				   (अचिन्हित दीर्घ)page_address(page),
				   PAGE_SIZE, change_page_range, &data);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
व्योम __kernel_map_pages(काष्ठा page *page, पूर्णांक numpages, पूर्णांक enable)
अणु
	अगर (!debug_pagealloc_enabled() && !rodata_full)
		वापस;

	set_memory_valid((अचिन्हित दीर्घ)page_address(page), numpages, enable);
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_PAGEALLOC */

/*
 * This function is used to determine अगर a linear map page has been marked as
 * not-valid. Walk the page table and check the PTE_VALID bit. This is based
 * on kern_addr_valid(), which almost करोes what we need.
 *
 * Because this is only called on the kernel linear map,  p?d_sect() implies
 * p?d_present(). When debug_pagealloc is enabled, sections mappings are
 * disabled.
 */
bool kernel_page_present(काष्ठा page *page)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp, pud;
	pmd_t *pmdp, pmd;
	pte_t *ptep;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)page_address(page);

	अगर (!debug_pagealloc_enabled() && !rodata_full)
		वापस true;

	pgdp = pgd_offset_k(addr);
	अगर (pgd_none(READ_ONCE(*pgdp)))
		वापस false;

	p4dp = p4d_offset(pgdp, addr);
	अगर (p4d_none(READ_ONCE(*p4dp)))
		वापस false;

	pudp = pud_offset(p4dp, addr);
	pud = READ_ONCE(*pudp);
	अगर (pud_none(pud))
		वापस false;
	अगर (pud_sect(pud))
		वापस true;

	pmdp = pmd_offset(pudp, addr);
	pmd = READ_ONCE(*pmdp);
	अगर (pmd_none(pmd))
		वापस false;
	अगर (pmd_sect(pmd))
		वापस true;

	ptep = pte_offset_kernel(pmdp, addr);
	वापस pte_valid(READ_ONCE(*ptep));
पूर्ण
