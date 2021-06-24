<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2019 SiFive
 */

#समावेश <linux/pagewalk.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/bitops.h>
#समावेश <यंत्र/set_memory.h>

काष्ठा pageattr_masks अणु
	pgprot_t set_mask;
	pgprot_t clear_mask;
पूर्ण;

अटल अचिन्हित दीर्घ set_pageattr_masks(अचिन्हित दीर्घ val, काष्ठा mm_walk *walk)
अणु
	काष्ठा pageattr_masks *masks = walk->निजी;
	अचिन्हित दीर्घ new_val = val;

	new_val &= ~(pgprot_val(masks->clear_mask));
	new_val |= (pgprot_val(masks->set_mask));

	वापस new_val;
पूर्ण

अटल पूर्णांक pageattr_pgd_entry(pgd_t *pgd, अचिन्हित दीर्घ addr,
			      अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	pgd_t val = READ_ONCE(*pgd);

	अगर (pgd_leaf(val)) अणु
		val = __pgd(set_pageattr_masks(pgd_val(val), walk));
		set_pgd(pgd, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pageattr_p4d_entry(p4d_t *p4d, अचिन्हित दीर्घ addr,
			      अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	p4d_t val = READ_ONCE(*p4d);

	अगर (p4d_leaf(val)) अणु
		val = __p4d(set_pageattr_masks(p4d_val(val), walk));
		set_p4d(p4d, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pageattr_pud_entry(pud_t *pud, अचिन्हित दीर्घ addr,
			      अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	pud_t val = READ_ONCE(*pud);

	अगर (pud_leaf(val)) अणु
		val = __pud(set_pageattr_masks(pud_val(val), walk));
		set_pud(pud, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pageattr_pmd_entry(pmd_t *pmd, अचिन्हित दीर्घ addr,
			      अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	pmd_t val = READ_ONCE(*pmd);

	अगर (pmd_leaf(val)) अणु
		val = __pmd(set_pageattr_masks(pmd_val(val), walk));
		set_pmd(pmd, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pageattr_pte_entry(pte_t *pte, अचिन्हित दीर्घ addr,
			      अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	pte_t val = READ_ONCE(*pte);

	val = __pte(set_pageattr_masks(pte_val(val), walk));
	set_pte(pte, val);

	वापस 0;
पूर्ण

अटल पूर्णांक pageattr_pte_hole(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ next,
			     पूर्णांक depth, काष्ठा mm_walk *walk)
अणु
	/* Nothing to करो here */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops pageattr_ops = अणु
	.pgd_entry = pageattr_pgd_entry,
	.p4d_entry = pageattr_p4d_entry,
	.pud_entry = pageattr_pud_entry,
	.pmd_entry = pageattr_pmd_entry,
	.pte_entry = pageattr_pte_entry,
	.pte_hole = pageattr_pte_hole,
पूर्ण;

अटल पूर्णांक __set_memory(अचिन्हित दीर्घ addr, पूर्णांक numpages, pgprot_t set_mask,
			pgprot_t clear_mask)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ start = addr;
	अचिन्हित दीर्घ end = start + PAGE_SIZE * numpages;
	काष्ठा pageattr_masks masks = अणु
		.set_mask = set_mask,
		.clear_mask = clear_mask
	पूर्ण;

	अगर (!numpages)
		वापस 0;

	mmap_पढ़ो_lock(&init_mm);
	ret =  walk_page_range_novma(&init_mm, start, end, &pageattr_ops, शून्य,
				     &masks);
	mmap_पढ़ो_unlock(&init_mm);

	flush_tlb_kernel_range(start, end);

	वापस ret;
पूर्ण

पूर्णांक set_memory_rw_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस __set_memory(addr, numpages, __pgprot(_PAGE_READ | _PAGE_WRITE),
			    __pgprot(_PAGE_EXEC));
पूर्ण

पूर्णांक set_memory_ro(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस __set_memory(addr, numpages, __pgprot(_PAGE_READ),
			    __pgprot(_PAGE_WRITE));
पूर्ण

पूर्णांक set_memory_rw(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस __set_memory(addr, numpages, __pgprot(_PAGE_READ | _PAGE_WRITE),
			    __pgprot(0));
पूर्ण

पूर्णांक set_memory_x(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस __set_memory(addr, numpages, __pgprot(_PAGE_EXEC), __pgprot(0));
पूर्ण

पूर्णांक set_memory_nx(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	वापस __set_memory(addr, numpages, __pgprot(0), __pgprot(_PAGE_EXEC));
पूर्ण

पूर्णांक set_direct_map_invalid_noflush(काष्ठा page *page)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)page_address(page);
	अचिन्हित दीर्घ end = start + PAGE_SIZE;
	काष्ठा pageattr_masks masks = अणु
		.set_mask = __pgprot(0),
		.clear_mask = __pgprot(_PAGE_PRESENT)
	पूर्ण;

	mmap_पढ़ो_lock(&init_mm);
	ret = walk_page_range(&init_mm, start, end, &pageattr_ops, &masks);
	mmap_पढ़ो_unlock(&init_mm);

	वापस ret;
पूर्ण

पूर्णांक set_direct_map_शेष_noflush(काष्ठा page *page)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)page_address(page);
	अचिन्हित दीर्घ end = start + PAGE_SIZE;
	काष्ठा pageattr_masks masks = अणु
		.set_mask = PAGE_KERNEL,
		.clear_mask = __pgprot(0)
	पूर्ण;

	mmap_पढ़ो_lock(&init_mm);
	ret = walk_page_range(&init_mm, start, end, &pageattr_ops, &masks);
	mmap_पढ़ो_unlock(&init_mm);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
व्योम __kernel_map_pages(काष्ठा page *page, पूर्णांक numpages, पूर्णांक enable)
अणु
	अगर (!debug_pagealloc_enabled())
		वापस;

	अगर (enable)
		__set_memory((अचिन्हित दीर्घ)page_address(page), numpages,
			     __pgprot(_PAGE_PRESENT), __pgprot(0));
	अन्यथा
		__set_memory((अचिन्हित दीर्घ)page_address(page), numpages,
			     __pgprot(0), __pgprot(_PAGE_PRESENT));
पूर्ण
#पूर्ण_अगर

bool kernel_page_present(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)page_address(page);
	pgd_t *pgd;
	pud_t *pud;
	p4d_t *p4d;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_offset_k(addr);
	अगर (!pgd_present(*pgd))
		वापस false;

	p4d = p4d_offset(pgd, addr);
	अगर (!p4d_present(*p4d))
		वापस false;

	pud = pud_offset(p4d, addr);
	अगर (!pud_present(*pud))
		वापस false;

	pmd = pmd_offset(pud, addr);
	अगर (!pmd_present(*pmd))
		वापस false;

	pte = pte_offset_kernel(pmd, addr);
	वापस pte_present(*pte);
पूर्ण
