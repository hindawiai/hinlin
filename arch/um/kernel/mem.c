<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/module.h>
#समावेश <linux/memblock.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/page.h>
#समावेश <as-layout.h>
#समावेश <init.h>
#समावेश <kern.h>
#समावेश <kern_util.h>
#समावेश <mem_user.h>
#समावेश <os.h>

/* allocated in paging_init, zeroed in mem_init, and unchanged thereafter */
अचिन्हित दीर्घ *empty_zero_page = शून्य;
EXPORT_SYMBOL(empty_zero_page);

/*
 * Initialized during boot, and पढ़ोonly क्रम initializing page tables
 * afterwards
 */
pgd_t swapper_pg_dir[PTRS_PER_PGD];

/* Initialized at boot समय, and पढ़ोonly after that */
अचिन्हित दीर्घ दीर्घ highmem;
EXPORT_SYMBOL(highmem);
पूर्णांक kदो_स्मृति_ok = 0;

/* Used during early boot */
अटल अचिन्हित दीर्घ brk_end;

व्योम __init mem_init(व्योम)
अणु
	/* clear the zero-page */
	स_रखो(empty_zero_page, 0, PAGE_SIZE);

	/* Map in the area just after the brk now that kदो_स्मृति is about
	 * to be turned on.
	 */
	brk_end = (अचिन्हित दीर्घ) UML_ROUND_UP(sbrk(0));
	map_memory(brk_end, __pa(brk_end), uml_reserved - brk_end, 1, 1, 0);
	memblock_मुक्त(__pa(brk_end), uml_reserved - brk_end);
	uml_reserved = brk_end;

	/* this will put all low memory onto the मुक्तlists */
	memblock_मुक्त_all();
	max_low_pfn = totalram_pages();
	max_pfn = max_low_pfn;
	kदो_स्मृति_ok = 1;
पूर्ण

/*
 * Create a page table and place a poपूर्णांकer to it in a middle page
 * directory entry.
 */
अटल व्योम __init one_page_table_init(pmd_t *pmd)
अणु
	अगर (pmd_none(*pmd)) अणु
		pte_t *pte = (pte_t *) memblock_alloc_low(PAGE_SIZE,
							  PAGE_SIZE);
		अगर (!pte)
			panic("%s: Failed to allocate %lu bytes align=%lx\n",
			      __func__, PAGE_SIZE, PAGE_SIZE);

		set_pmd(pmd, __pmd(_KERNPG_TABLE +
					   (अचिन्हित दीर्घ) __pa(pte)));
		BUG_ON(pte != pte_offset_kernel(pmd, 0));
	पूर्ण
पूर्ण

अटल व्योम __init one_md_table_init(pud_t *pud)
अणु
#अगर_घोषित CONFIG_3_LEVEL_PGTABLES
	pmd_t *pmd_table = (pmd_t *) memblock_alloc_low(PAGE_SIZE, PAGE_SIZE);
	अगर (!pmd_table)
		panic("%s: Failed to allocate %lu bytes align=%lx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	set_pud(pud, __pud(_KERNPG_TABLE + (अचिन्हित दीर्घ) __pa(pmd_table)));
	अगर (pmd_table != pmd_offset(pud, 0))
		BUG();
#पूर्ण_अगर
पूर्ण

अटल व्योम __init fixrange_init(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				 pgd_t *pgd_base)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	पूर्णांक i, j;
	अचिन्हित दीर्घ vaddr;

	vaddr = start;
	i = pgd_index(vaddr);
	j = pmd_index(vaddr);
	pgd = pgd_base + i;

	क्रम ( ; (i < PTRS_PER_PGD) && (vaddr < end); pgd++, i++) अणु
		p4d = p4d_offset(pgd, vaddr);
		pud = pud_offset(p4d, vaddr);
		अगर (pud_none(*pud))
			one_md_table_init(pud);
		pmd = pmd_offset(pud, vaddr);
		क्रम (; (j < PTRS_PER_PMD) && (vaddr < end); pmd++, j++) अणु
			one_page_table_init(pmd);
			vaddr += PMD_SIZE;
		पूर्ण
		j = 0;
	पूर्ण
पूर्ण

अटल व्योम __init fixaddr_user_init( व्योम)
अणु
#अगर_घोषित CONFIG_ARCH_REUSE_HOST_VSYSCALL_AREA
	दीर्घ size = FIXADDR_USER_END - FIXADDR_USER_START;
	pte_t *pte;
	phys_t p;
	अचिन्हित दीर्घ v, vaddr = FIXADDR_USER_START;

	अगर (!size)
		वापस;

	fixrange_init( FIXADDR_USER_START, FIXADDR_USER_END, swapper_pg_dir);
	v = (अचिन्हित दीर्घ) memblock_alloc_low(size, PAGE_SIZE);
	अगर (!v)
		panic("%s: Failed to allocate %lu bytes align=%lx\n",
		      __func__, size, PAGE_SIZE);

	स_नकल((व्योम *) v , (व्योम *) FIXADDR_USER_START, size);
	p = __pa(v);
	क्रम ( ; size > 0; size -= PAGE_SIZE, vaddr += PAGE_SIZE,
		      p += PAGE_SIZE) अणु
		pte = virt_to_kpte(vaddr);
		pte_set_val(*pte, p, PAGE_READONLY);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0 पूर्ण;
	अचिन्हित दीर्घ vaddr;

	empty_zero_page = (अचिन्हित दीर्घ *) memblock_alloc_low(PAGE_SIZE,
							       PAGE_SIZE);
	अगर (!empty_zero_page)
		panic("%s: Failed to allocate %lu bytes align=%lx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	max_zone_pfn[ZONE_NORMAL] = end_iomem >> PAGE_SHIFT;
	मुक्त_area_init(max_zone_pfn);

	/*
	 * Fixed mappings, only the page table काष्ठाure has to be
	 * created - mappings will be set by set_fixmap():
	 */
	vaddr = __fix_to_virt(__end_of_fixed_addresses - 1) & PMD_MASK;
	fixrange_init(vaddr, FIXADDR_TOP, swapper_pg_dir);

	fixaddr_user_init();
पूर्ण

/*
 * This can't करो anything because nothing in the kernel image can be मुक्तd
 * since it's not in kernel physical memory.
 */

व्योम मुक्त_iniपंचांगem(व्योम)
अणु
पूर्ण

/* Allocate and मुक्त page tables. */

pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *pgd = (pgd_t *)__get_मुक्त_page(GFP_KERNEL);

	अगर (pgd) अणु
		स_रखो(pgd, 0, USER_PTRS_PER_PGD * माप(pgd_t));
		स_नकल(pgd + USER_PTRS_PER_PGD,
		       swapper_pg_dir + USER_PTRS_PER_PGD,
		       (PTRS_PER_PGD - USER_PTRS_PER_PGD) * माप(pgd_t));
	पूर्ण
	वापस pgd;
पूर्ण

व्योम *uml_kदो_स्मृति(पूर्णांक size, पूर्णांक flags)
अणु
	वापस kदो_स्मृति(size, flags);
पूर्ण
