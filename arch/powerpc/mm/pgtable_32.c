<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains the routines setting up the linux page tables.
 *  -- paulus
 *
 *  Derived from arch/ppc/mm/init.c:
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/early_ioremap.h>

#समावेश <mm/mmu_decl.h>

बाह्य अक्षर etext[], _stext[], _sinittext[], _einittext[];

अटल u8 early_fixmap_pagetable[FIXMAP_PTE_SIZE] __page_aligned_data;

notrace व्योम __init early_ioremap_init(व्योम)
अणु
	अचिन्हित दीर्घ addr = ALIGN_DOWN(FIXADDR_START, PGसूची_SIZE);
	pte_t *ptep = (pte_t *)early_fixmap_pagetable;
	pmd_t *pmdp = pmd_off_k(addr);

	क्रम (; (s32)(FIXADDR_TOP - addr) > 0;
	     addr += PGसूची_SIZE, ptep += PTRS_PER_PTE, pmdp++)
		pmd_populate_kernel(&init_mm, pmdp, ptep);

	early_ioremap_setup();
पूर्ण

अटल व्योम __init *early_alloc_pgtable(अचिन्हित दीर्घ size)
अणु
	व्योम *ptr = memblock_alloc(size, size);

	अगर (!ptr)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, size, size);

	वापस ptr;
पूर्ण

pte_t __init *early_pte_alloc_kernel(pmd_t *pmdp, अचिन्हित दीर्घ va)
अणु
	अगर (pmd_none(*pmdp)) अणु
		pte_t *ptep = early_alloc_pgtable(PTE_FRAG_SIZE);

		pmd_populate_kernel(&init_mm, pmdp, ptep);
	पूर्ण
	वापस pte_offset_kernel(pmdp, va);
पूर्ण


पूर्णांक __ref map_kernel_page(अचिन्हित दीर्घ va, phys_addr_t pa, pgprot_t prot)
अणु
	pmd_t *pd;
	pte_t *pg;
	पूर्णांक err = -ENOMEM;

	/* Use upper 10 bits of VA to index the first level map */
	pd = pmd_off_k(va);
	/* Use middle 10 bits of VA to index the second-level map */
	अगर (likely(slab_is_available()))
		pg = pte_alloc_kernel(pd, va);
	अन्यथा
		pg = early_pte_alloc_kernel(pd, va);
	अगर (pg) अणु
		err = 0;
		/* The PTE should never be alपढ़ोy set nor present in the
		 * hash table
		 */
		BUG_ON((pte_present(*pg) | pte_hashpte(*pg)) && pgprot_val(prot));
		set_pte_at(&init_mm, va, pg, pfn_pte(pa >> PAGE_SHIFT, prot));
	पूर्ण
	smp_wmb();
	वापस err;
पूर्ण

/*
 * Map in a chunk of physical memory starting at start.
 */
अटल व्योम __init __mapin_ram_chunk(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ top)
अणु
	अचिन्हित दीर्घ v, s;
	phys_addr_t p;
	पूर्णांक ktext;

	s = offset;
	v = PAGE_OFFSET + s;
	p = memstart_addr + s;
	क्रम (; s < top; s += PAGE_SIZE) अणु
		ktext = ((अक्षर *)v >= _stext && (अक्षर *)v < etext) ||
			((अक्षर *)v >= _sinittext && (अक्षर *)v < _einittext);
		map_kernel_page(v, p, ktext ? PAGE_KERNEL_TEXT : PAGE_KERNEL);
		v += PAGE_SIZE;
		p += PAGE_SIZE;
	पूर्ण
पूर्ण

व्योम __init mapin_ram(व्योम)
अणु
	phys_addr_t base, end;
	u64 i;

	क्रम_each_mem_range(i, &base, &end) अणु
		phys_addr_t top = min(end, total_lowmem);

		अगर (base >= top)
			जारी;
		base = mmu_mapin_ram(base, top);
		__mapin_ram_chunk(base, top);
	पूर्ण
पूर्ण

अटल पूर्णांक __change_page_attr_noflush(काष्ठा page *page, pgprot_t prot)
अणु
	pte_t *kpte;
	अचिन्हित दीर्घ address;

	BUG_ON(PageHighMem(page));
	address = (अचिन्हित दीर्घ)page_address(page);

	अगर (v_block_mapped(address))
		वापस 0;
	kpte = virt_to_kpte(address);
	अगर (!kpte)
		वापस -EINVAL;
	__set_pte_at(&init_mm, address, kpte, mk_pte(page, prot), 0);

	वापस 0;
पूर्ण

/*
 * Change the page attributes of an page in the linear mapping.
 *
 * THIS DOES NOTHING WITH BAT MAPPINGS, DEBUG USE ONLY
 */
अटल पूर्णांक change_page_attr(काष्ठा page *page, पूर्णांक numpages, pgprot_t prot)
अणु
	पूर्णांक i, err = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा page *start = page;

	local_irq_save(flags);
	क्रम (i = 0; i < numpages; i++, page++) अणु
		err = __change_page_attr_noflush(page, prot);
		अगर (err)
			अवरोध;
	पूर्ण
	wmb();
	local_irq_restore(flags);
	flush_tlb_kernel_range((अचिन्हित दीर्घ)page_address(start),
			       (अचिन्हित दीर्घ)page_address(page));
	वापस err;
पूर्ण

व्योम mark_iniपंचांगem_nx(व्योम)
अणु
	काष्ठा page *page = virt_to_page(_sinittext);
	अचिन्हित दीर्घ numpages = PFN_UP((अचिन्हित दीर्घ)_einittext) -
				 PFN_DOWN((अचिन्हित दीर्घ)_sinittext);

	अगर (v_block_mapped((अचिन्हित दीर्घ)_sinittext))
		mmu_mark_iniपंचांगem_nx();
	अन्यथा
		change_page_attr(page, numpages, PAGE_KERNEL);
पूर्ण

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
व्योम mark_rodata_ro(व्योम)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ numpages;

	अगर (v_block_mapped((अचिन्हित दीर्घ)_stext + 1)) अणु
		mmu_mark_rodata_ro();
		ptdump_check_wx();
		वापस;
	पूर्ण

	page = virt_to_page(_stext);
	numpages = PFN_UP((अचिन्हित दीर्घ)_etext) -
		   PFN_DOWN((अचिन्हित दीर्घ)_stext);

	change_page_attr(page, numpages, PAGE_KERNEL_ROX);
	/*
	 * mark .rodata as पढ़ो only. Use __init_begin rather than __end_rodata
	 * to cover NOTES and EXCEPTION_TABLE.
	 */
	page = virt_to_page(__start_rodata);
	numpages = PFN_UP((अचिन्हित दीर्घ)__init_begin) -
		   PFN_DOWN((अचिन्हित दीर्घ)__start_rodata);

	change_page_attr(page, numpages, PAGE_KERNEL_RO);

	// mark_iniपंचांगem_nx() should have alपढ़ोy run by now
	ptdump_check_wx();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_PAGEALLOC
व्योम __kernel_map_pages(काष्ठा page *page, पूर्णांक numpages, पूर्णांक enable)
अणु
	अगर (PageHighMem(page))
		वापस;

	change_page_attr(page, numpages, enable ? PAGE_KERNEL : __pgprot(0));
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_PAGEALLOC */
