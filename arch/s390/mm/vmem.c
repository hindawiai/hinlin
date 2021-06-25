<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2006
 *    Author(s): Heiko Carstens <heiko.carstens@de.ibm.com>
 */

#समावेश <linux/memory_hotplug.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pfn.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/set_memory.h>

अटल DEFINE_MUTEX(vmem_mutex);

अटल व्योम __ref *vmem_alloc_pages(अचिन्हित पूर्णांक order)
अणु
	अचिन्हित दीर्घ size = PAGE_SIZE << order;

	अगर (slab_is_available())
		वापस (व्योम *)__get_मुक्त_pages(GFP_KERNEL, order);
	वापस memblock_alloc(size, size);
पूर्ण

अटल व्योम vmem_मुक्त_pages(अचिन्हित दीर्घ addr, पूर्णांक order)
अणु
	/* We करोn't expect boot memory to be हटाओd ever. */
	अगर (!slab_is_available() ||
	    WARN_ON_ONCE(PageReserved(virt_to_page(addr))))
		वापस;
	मुक्त_pages(addr, order);
पूर्ण

व्योम *vmem_crst_alloc(अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ *table;

	table = vmem_alloc_pages(CRST_ALLOC_ORDER);
	अगर (table)
		crst_table_init(table, val);
	वापस table;
पूर्ण

pte_t __ref *vmem_pte_alloc(व्योम)
अणु
	अचिन्हित दीर्घ size = PTRS_PER_PTE * माप(pte_t);
	pte_t *pte;

	अगर (slab_is_available())
		pte = (pte_t *) page_table_alloc(&init_mm);
	अन्यथा
		pte = (pte_t *) memblock_alloc(size, size);
	अगर (!pte)
		वापस शून्य;
	स_रखो64((u64 *)pte, _PAGE_INVALID, PTRS_PER_PTE);
	वापस pte;
पूर्ण

अटल व्योम vmem_pte_मुक्त(अचिन्हित दीर्घ *table)
अणु
	/* We करोn't expect boot memory to be हटाओd ever. */
	अगर (!slab_is_available() ||
	    WARN_ON_ONCE(PageReserved(virt_to_page(table))))
		वापस;
	page_table_मुक्त(&init_mm, table);
पूर्ण

#घोषणा PAGE_UNUSED 0xFD

/*
 * The unused vmemmap range, which was not yet स_रखो(PAGE_UNUSED) ranges
 * from unused_sub_pmd_start to next PMD_SIZE boundary.
 */
अटल अचिन्हित दीर्घ unused_sub_pmd_start;

अटल व्योम vmemmap_flush_unused_sub_pmd(व्योम)
अणु
	अगर (!unused_sub_pmd_start)
		वापस;
	स_रखो((व्योम *)unused_sub_pmd_start, PAGE_UNUSED,
	       ALIGN(unused_sub_pmd_start, PMD_SIZE) - unused_sub_pmd_start);
	unused_sub_pmd_start = 0;
पूर्ण

अटल व्योम vmemmap_mark_sub_pmd_used(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/*
	 * As we expect to add in the same granularity as we हटाओ, it's
	 * sufficient to mark only some piece used to block the memmap page from
	 * getting हटाओd (just in हाल the memmap never माला_लो initialized,
	 * e.g., because the memory block never माला_लो onlined).
	 */
	स_रखो((व्योम *)start, 0, माप(काष्ठा page));
पूर्ण

अटल व्योम vmemmap_use_sub_pmd(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/*
	 * We only optimize अगर the new used range directly follows the
	 * previously unused range (esp., when populating consecutive sections).
	 */
	अगर (unused_sub_pmd_start == start) अणु
		unused_sub_pmd_start = end;
		अगर (likely(IS_ALIGNED(unused_sub_pmd_start, PMD_SIZE)))
			unused_sub_pmd_start = 0;
		वापस;
	पूर्ण
	vmemmap_flush_unused_sub_pmd();
	vmemmap_mark_sub_pmd_used(start, end);
पूर्ण

अटल व्योम vmemmap_use_new_sub_pmd(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ page = ALIGN_DOWN(start, PMD_SIZE);

	vmemmap_flush_unused_sub_pmd();

	/* Could be our memmap page is filled with PAGE_UNUSED alपढ़ोy ... */
	vmemmap_mark_sub_pmd_used(start, end);

	/* Mark the unused parts of the new memmap page PAGE_UNUSED. */
	अगर (!IS_ALIGNED(start, PMD_SIZE))
		स_रखो((व्योम *)page, PAGE_UNUSED, start - page);
	/*
	 * We want to aव्योम स_रखो(PAGE_UNUSED) when populating the vmemmap of
	 * consecutive sections. Remember क्रम the last added PMD the last
	 * unused range in the populated PMD.
	 */
	अगर (!IS_ALIGNED(end, PMD_SIZE))
		unused_sub_pmd_start = end;
पूर्ण

/* Returns true अगर the PMD is completely unused and can be मुक्तd. */
अटल bool vmemmap_unuse_sub_pmd(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ page = ALIGN_DOWN(start, PMD_SIZE);

	vmemmap_flush_unused_sub_pmd();
	स_रखो((व्योम *)start, PAGE_UNUSED, end - start);
	वापस !स_प्रथम_inv((व्योम *)page, PAGE_UNUSED, PMD_SIZE);
पूर्ण

/* __ref: we'll only call vmemmap_alloc_block() via vmemmap_populate() */
अटल पूर्णांक __ref modअगरy_pte_table(pmd_t *pmd, अचिन्हित दीर्घ addr,
				  अचिन्हित दीर्घ end, bool add, bool direct)
अणु
	अचिन्हित दीर्घ prot, pages = 0;
	पूर्णांक ret = -ENOMEM;
	pte_t *pte;

	prot = pgprot_val(PAGE_KERNEL);
	अगर (!MACHINE_HAS_NX)
		prot &= ~_PAGE_NOEXEC;

	pte = pte_offset_kernel(pmd, addr);
	क्रम (; addr < end; addr += PAGE_SIZE, pte++) अणु
		अगर (!add) अणु
			अगर (pte_none(*pte))
				जारी;
			अगर (!direct)
				vmem_मुक्त_pages((अचिन्हित दीर्घ) pfn_to_virt(pte_pfn(*pte)), 0);
			pte_clear(&init_mm, addr, pte);
		पूर्ण अन्यथा अगर (pte_none(*pte)) अणु
			अगर (!direct) अणु
				व्योम *new_page = vmemmap_alloc_block(PAGE_SIZE, NUMA_NO_NODE);

				अगर (!new_page)
					जाओ out;
				pte_val(*pte) = __pa(new_page) | prot;
			पूर्ण अन्यथा अणु
				pte_val(*pte) = __pa(addr) | prot;
			पूर्ण
		पूर्ण अन्यथा अणु
			जारी;
		पूर्ण
		pages++;
	पूर्ण
	ret = 0;
out:
	अगर (direct)
		update_page_count(PG_सूचीECT_MAP_4K, add ? pages : -pages);
	वापस ret;
पूर्ण

अटल व्योम try_मुक्त_pte_table(pmd_t *pmd, अचिन्हित दीर्घ start)
अणु
	pte_t *pte;
	पूर्णांक i;

	/* We can safely assume this is fully in 1:1 mapping & vmemmap area */
	pte = pte_offset_kernel(pmd, start);
	क्रम (i = 0; i < PTRS_PER_PTE; i++, pte++) अणु
		अगर (!pte_none(*pte))
			वापस;
	पूर्ण
	vmem_pte_मुक्त((अचिन्हित दीर्घ *) pmd_deref(*pmd));
	pmd_clear(pmd);
पूर्ण

/* __ref: we'll only call vmemmap_alloc_block() via vmemmap_populate() */
अटल पूर्णांक __ref modअगरy_pmd_table(pud_t *pud, अचिन्हित दीर्घ addr,
				  अचिन्हित दीर्घ end, bool add, bool direct)
अणु
	अचिन्हित दीर्घ next, prot, pages = 0;
	पूर्णांक ret = -ENOMEM;
	pmd_t *pmd;
	pte_t *pte;

	prot = pgprot_val(SEGMENT_KERNEL);
	अगर (!MACHINE_HAS_NX)
		prot &= ~_SEGMENT_ENTRY_NOEXEC;

	pmd = pmd_offset(pud, addr);
	क्रम (; addr < end; addr = next, pmd++) अणु
		next = pmd_addr_end(addr, end);
		अगर (!add) अणु
			अगर (pmd_none(*pmd))
				जारी;
			अगर (pmd_large(*pmd)) अणु
				अगर (IS_ALIGNED(addr, PMD_SIZE) &&
				    IS_ALIGNED(next, PMD_SIZE)) अणु
					अगर (!direct)
						vmem_मुक्त_pages(pmd_deref(*pmd), get_order(PMD_SIZE));
					pmd_clear(pmd);
					pages++;
				पूर्ण अन्यथा अगर (!direct && vmemmap_unuse_sub_pmd(addr, next)) अणु
					vmem_मुक्त_pages(pmd_deref(*pmd), get_order(PMD_SIZE));
					pmd_clear(pmd);
				पूर्ण
				जारी;
			पूर्ण
		पूर्ण अन्यथा अगर (pmd_none(*pmd)) अणु
			अगर (IS_ALIGNED(addr, PMD_SIZE) &&
			    IS_ALIGNED(next, PMD_SIZE) &&
			    MACHINE_HAS_EDAT1 && addr && direct &&
			    !debug_pagealloc_enabled()) अणु
				pmd_val(*pmd) = __pa(addr) | prot;
				pages++;
				जारी;
			पूर्ण अन्यथा अगर (!direct && MACHINE_HAS_EDAT1) अणु
				व्योम *new_page;

				/*
				 * Use 1MB frames क्रम vmemmap अगर available. We
				 * always use large frames even अगर they are only
				 * partially used. Otherwise we would have also
				 * page tables since vmemmap_populate माला_लो
				 * called क्रम each section separately.
				 */
				new_page = vmemmap_alloc_block(PMD_SIZE, NUMA_NO_NODE);
				अगर (new_page) अणु
					pmd_val(*pmd) = __pa(new_page) | prot;
					अगर (!IS_ALIGNED(addr, PMD_SIZE) ||
					    !IS_ALIGNED(next, PMD_SIZE)) अणु
						vmemmap_use_new_sub_pmd(addr, next);
					पूर्ण
					जारी;
				पूर्ण
			पूर्ण
			pte = vmem_pte_alloc();
			अगर (!pte)
				जाओ out;
			pmd_populate(&init_mm, pmd, pte);
		पूर्ण अन्यथा अगर (pmd_large(*pmd)) अणु
			अगर (!direct)
				vmemmap_use_sub_pmd(addr, next);
			जारी;
		पूर्ण
		ret = modअगरy_pte_table(pmd, addr, next, add, direct);
		अगर (ret)
			जाओ out;
		अगर (!add)
			try_मुक्त_pte_table(pmd, addr & PMD_MASK);
	पूर्ण
	ret = 0;
out:
	अगर (direct)
		update_page_count(PG_सूचीECT_MAP_1M, add ? pages : -pages);
	वापस ret;
पूर्ण

अटल व्योम try_मुक्त_pmd_table(pud_t *pud, अचिन्हित दीर्घ start)
अणु
	स्थिर अचिन्हित दीर्घ end = start + PUD_SIZE;
	pmd_t *pmd;
	पूर्णांक i;

	/* Don't mess with any tables not fully in 1:1 mapping & vmemmap area */
	अगर (end > VMALLOC_START)
		वापस;
#अगर_घोषित CONFIG_KASAN
	अगर (start < KASAN_SHADOW_END && KASAN_SHADOW_START > end)
		वापस;
#पूर्ण_अगर
	pmd = pmd_offset(pud, start);
	क्रम (i = 0; i < PTRS_PER_PMD; i++, pmd++)
		अगर (!pmd_none(*pmd))
			वापस;
	vmem_मुक्त_pages(pud_deref(*pud), CRST_ALLOC_ORDER);
	pud_clear(pud);
पूर्ण

अटल पूर्णांक modअगरy_pud_table(p4d_t *p4d, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			    bool add, bool direct)
अणु
	अचिन्हित दीर्घ next, prot, pages = 0;
	पूर्णांक ret = -ENOMEM;
	pud_t *pud;
	pmd_t *pmd;

	prot = pgprot_val(REGION3_KERNEL);
	अगर (!MACHINE_HAS_NX)
		prot &= ~_REGION_ENTRY_NOEXEC;
	pud = pud_offset(p4d, addr);
	क्रम (; addr < end; addr = next, pud++) अणु
		next = pud_addr_end(addr, end);
		अगर (!add) अणु
			अगर (pud_none(*pud))
				जारी;
			अगर (pud_large(*pud)) अणु
				अगर (IS_ALIGNED(addr, PUD_SIZE) &&
				    IS_ALIGNED(next, PUD_SIZE)) अणु
					pud_clear(pud);
					pages++;
				पूर्ण
				जारी;
			पूर्ण
		पूर्ण अन्यथा अगर (pud_none(*pud)) अणु
			अगर (IS_ALIGNED(addr, PUD_SIZE) &&
			    IS_ALIGNED(next, PUD_SIZE) &&
			    MACHINE_HAS_EDAT2 && addr && direct &&
			    !debug_pagealloc_enabled()) अणु
				pud_val(*pud) = __pa(addr) | prot;
				pages++;
				जारी;
			पूर्ण
			pmd = vmem_crst_alloc(_SEGMENT_ENTRY_EMPTY);
			अगर (!pmd)
				जाओ out;
			pud_populate(&init_mm, pud, pmd);
		पूर्ण अन्यथा अगर (pud_large(*pud)) अणु
			जारी;
		पूर्ण
		ret = modअगरy_pmd_table(pud, addr, next, add, direct);
		अगर (ret)
			जाओ out;
		अगर (!add)
			try_मुक्त_pmd_table(pud, addr & PUD_MASK);
	पूर्ण
	ret = 0;
out:
	अगर (direct)
		update_page_count(PG_सूचीECT_MAP_2G, add ? pages : -pages);
	वापस ret;
पूर्ण

अटल व्योम try_मुक्त_pud_table(p4d_t *p4d, अचिन्हित दीर्घ start)
अणु
	स्थिर अचिन्हित दीर्घ end = start + P4D_SIZE;
	pud_t *pud;
	पूर्णांक i;

	/* Don't mess with any tables not fully in 1:1 mapping & vmemmap area */
	अगर (end > VMALLOC_START)
		वापस;
#अगर_घोषित CONFIG_KASAN
	अगर (start < KASAN_SHADOW_END && KASAN_SHADOW_START > end)
		वापस;
#पूर्ण_अगर

	pud = pud_offset(p4d, start);
	क्रम (i = 0; i < PTRS_PER_PUD; i++, pud++) अणु
		अगर (!pud_none(*pud))
			वापस;
	पूर्ण
	vmem_मुक्त_pages(p4d_deref(*p4d), CRST_ALLOC_ORDER);
	p4d_clear(p4d);
पूर्ण

अटल पूर्णांक modअगरy_p4d_table(pgd_t *pgd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			    bool add, bool direct)
अणु
	अचिन्हित दीर्घ next;
	पूर्णांक ret = -ENOMEM;
	p4d_t *p4d;
	pud_t *pud;

	p4d = p4d_offset(pgd, addr);
	क्रम (; addr < end; addr = next, p4d++) अणु
		next = p4d_addr_end(addr, end);
		अगर (!add) अणु
			अगर (p4d_none(*p4d))
				जारी;
		पूर्ण अन्यथा अगर (p4d_none(*p4d)) अणु
			pud = vmem_crst_alloc(_REGION3_ENTRY_EMPTY);
			अगर (!pud)
				जाओ out;
			p4d_populate(&init_mm, p4d, pud);
		पूर्ण
		ret = modअगरy_pud_table(p4d, addr, next, add, direct);
		अगर (ret)
			जाओ out;
		अगर (!add)
			try_मुक्त_pud_table(p4d, addr & P4D_MASK);
	पूर्ण
	ret = 0;
out:
	वापस ret;
पूर्ण

अटल व्योम try_मुक्त_p4d_table(pgd_t *pgd, अचिन्हित दीर्घ start)
अणु
	स्थिर अचिन्हित दीर्घ end = start + PGसूची_SIZE;
	p4d_t *p4d;
	पूर्णांक i;

	/* Don't mess with any tables not fully in 1:1 mapping & vmemmap area */
	अगर (end > VMALLOC_START)
		वापस;
#अगर_घोषित CONFIG_KASAN
	अगर (start < KASAN_SHADOW_END && KASAN_SHADOW_START > end)
		वापस;
#पूर्ण_अगर

	p4d = p4d_offset(pgd, start);
	क्रम (i = 0; i < PTRS_PER_P4D; i++, p4d++) अणु
		अगर (!p4d_none(*p4d))
			वापस;
	पूर्ण
	vmem_मुक्त_pages(pgd_deref(*pgd), CRST_ALLOC_ORDER);
	pgd_clear(pgd);
पूर्ण

अटल पूर्णांक modअगरy_pagetable(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, bool add,
			    bool direct)
अणु
	अचिन्हित दीर्घ addr, next;
	पूर्णांक ret = -ENOMEM;
	pgd_t *pgd;
	p4d_t *p4d;

	अगर (WARN_ON_ONCE(!PAGE_ALIGNED(start | end)))
		वापस -EINVAL;
	क्रम (addr = start; addr < end; addr = next) अणु
		next = pgd_addr_end(addr, end);
		pgd = pgd_offset_k(addr);

		अगर (!add) अणु
			अगर (pgd_none(*pgd))
				जारी;
		पूर्ण अन्यथा अगर (pgd_none(*pgd)) अणु
			p4d = vmem_crst_alloc(_REGION2_ENTRY_EMPTY);
			अगर (!p4d)
				जाओ out;
			pgd_populate(&init_mm, pgd, p4d);
		पूर्ण
		ret = modअगरy_p4d_table(pgd, addr, next, add, direct);
		अगर (ret)
			जाओ out;
		अगर (!add)
			try_मुक्त_p4d_table(pgd, addr & PGसूची_MASK);
	पूर्ण
	ret = 0;
out:
	अगर (!add)
		flush_tlb_kernel_range(start, end);
	वापस ret;
पूर्ण

अटल पूर्णांक add_pagetable(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, bool direct)
अणु
	वापस modअगरy_pagetable(start, end, true, direct);
पूर्ण

अटल पूर्णांक हटाओ_pagetable(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, bool direct)
अणु
	वापस modअगरy_pagetable(start, end, false, direct);
पूर्ण

/*
 * Add a physical memory range to the 1:1 mapping.
 */
अटल पूर्णांक vmem_add_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
	वापस add_pagetable(start, start + size, true);
पूर्ण

/*
 * Remove a physical memory range from the 1:1 mapping.
 */
अटल व्योम vmem_हटाओ_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
	हटाओ_pagetable(start, start + size, true);
पूर्ण

/*
 * Add a backed mem_map array to the भव mem_map array.
 */
पूर्णांक __meminit vmemmap_populate(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक node,
			       काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	पूर्णांक ret;

	mutex_lock(&vmem_mutex);
	/* We करोn't care about the node, just use NUMA_NO_NODE on allocations */
	ret = add_pagetable(start, end, false);
	अगर (ret)
		हटाओ_pagetable(start, end, false);
	mutex_unlock(&vmem_mutex);
	वापस ret;
पूर्ण

व्योम vmemmap_मुक्त(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		  काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	mutex_lock(&vmem_mutex);
	हटाओ_pagetable(start, end, false);
	mutex_unlock(&vmem_mutex);
पूर्ण

व्योम vmem_हटाओ_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
	mutex_lock(&vmem_mutex);
	vmem_हटाओ_range(start, size);
	mutex_unlock(&vmem_mutex);
पूर्ण

काष्ठा range arch_get_mappable_range(व्योम)
अणु
	काष्ठा range mhp_range;

	mhp_range.start = 0;
	mhp_range.end =  VMEM_MAX_PHYS - 1;
	वापस mhp_range;
पूर्ण

पूर्णांक vmem_add_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
	काष्ठा range range = arch_get_mappable_range();
	पूर्णांक ret;

	अगर (start < range.start ||
	    start + size > range.end + 1 ||
	    start + size < start)
		वापस -दुस्फल;

	mutex_lock(&vmem_mutex);
	ret = vmem_add_range(start, size);
	अगर (ret)
		vmem_हटाओ_range(start, size);
	mutex_unlock(&vmem_mutex);
	वापस ret;
पूर्ण

/*
 * map whole physical memory to भव memory (identity mapping)
 * we reserve enough space in the vदो_स्मृति area क्रम vmemmap to hotplug
 * additional memory segments.
 */
व्योम __init vmem_map_init(व्योम)
अणु
	phys_addr_t base, end;
	u64 i;

	क्रम_each_mem_range(i, &base, &end)
		vmem_add_range(base, end - base);
	__set_memory((अचिन्हित दीर्घ)_stext,
		     (अचिन्हित दीर्घ)(_etext - _stext) >> PAGE_SHIFT,
		     SET_MEMORY_RO | SET_MEMORY_X);
	__set_memory((अचिन्हित दीर्घ)_etext,
		     (अचिन्हित दीर्घ)(__end_rodata - _etext) >> PAGE_SHIFT,
		     SET_MEMORY_RO);
	__set_memory((अचिन्हित दीर्घ)_sinittext,
		     (अचिन्हित दीर्घ)(_einittext - _sinittext) >> PAGE_SHIFT,
		     SET_MEMORY_RO | SET_MEMORY_X);
	__set_memory(__stext_dma, (__etext_dma - __stext_dma) >> PAGE_SHIFT,
		     SET_MEMORY_RO | SET_MEMORY_X);

	/* we need lowcore executable क्रम our LPSWE inकाष्ठाions */
	set_memory_x(0, 1);

	pr_info("Write protected kernel read-only data: %luk\n",
		(अचिन्हित दीर्घ)(__end_rodata - _stext) >> 10);
पूर्ण
