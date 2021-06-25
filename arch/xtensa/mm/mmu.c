<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xtensa mmu stuff
 *
 * Extracted from init.c
 */
#समावेश <linux/memblock.h>
#समावेश <linux/percpu.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/cache.h>

#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/initialize_mmu.h>
#समावेश <यंत्र/पन.स>

#अगर defined(CONFIG_HIGHMEM)
अटल व्योम * __init init_pmd(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ n_pages)
अणु
	pmd_t *pmd = pmd_off_k(vaddr);
	pte_t *pte;
	अचिन्हित दीर्घ i;

	n_pages = ALIGN(n_pages, PTRS_PER_PTE);

	pr_debug("%s: vaddr: 0x%08lx, n_pages: %ld\n",
		 __func__, vaddr, n_pages);

	pte = memblock_alloc_low(n_pages * माप(pte_t), PAGE_SIZE);
	अगर (!pte)
		panic("%s: Failed to allocate %lu bytes align=%lx\n",
		      __func__, n_pages * माप(pte_t), PAGE_SIZE);

	क्रम (i = 0; i < n_pages; ++i)
		pte_clear(शून्य, 0, pte + i);

	क्रम (i = 0; i < n_pages; i += PTRS_PER_PTE, ++pmd) अणु
		pte_t *cur_pte = pte + i;

		BUG_ON(!pmd_none(*pmd));
		set_pmd(pmd, __pmd(((अचिन्हित दीर्घ)cur_pte) & PAGE_MASK));
		BUG_ON(cur_pte != pte_offset_kernel(pmd, 0));
		pr_debug("%s: pmd: 0x%p, pte: 0x%p\n",
			 __func__, pmd, cur_pte);
	पूर्ण
	वापस pte;
पूर्ण

अटल व्योम __init fixedrange_init(व्योम)
अणु
	BUILD_BUG_ON(FIXADDR_START < TLBTEMP_BASE_1 + TLBTEMP_SIZE);
	init_pmd(FIXADDR_START, __end_of_fixed_addresses);
पूर्ण
#पूर्ण_अगर

व्योम __init paging_init(व्योम)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	fixedrange_init();
	pkmap_page_table = init_pmd(PKMAP_BASE, LAST_PKMAP);
	kmap_init();
#पूर्ण_अगर
पूर्ण

/*
 * Flush the mmu and reset associated रेजिस्टर to शेष values.
 */
व्योम init_mmu(व्योम)
अणु
#अगर !(XCHAL_HAVE_PTP_MMU && XCHAL_HAVE_SPANNING_WAY)
	/*
	 * Writing zeros to the inकाष्ठाion and data TLBCFG special
	 * रेजिस्टरs ensure that valid values exist in the रेजिस्टर.
	 *
	 * For existing PGSZID<w> fields, zero selects the first element
	 * of the page-size array.  For nonexistent PGSZID<w> fields,
	 * zero is the best value to ग_लिखो.  Also, when changing PGSZID<w>
	 * fields, the corresponding TLB must be flushed.
	 */
	set_itlbcfg_रेजिस्टर(0);
	set_dtlbcfg_रेजिस्टर(0);
#पूर्ण_अगर
	init_kio();
	local_flush_tlb_all();

	/* Set rasid रेजिस्टर to a known value. */

	set_rasid_रेजिस्टर(ASID_INSERT(ASID_USER_FIRST));

	/* Set PTEVADDR special रेजिस्टर to the start of the page
	 * table, which is in kernel mappable space (ie. not
	 * अटलally mapped).  This रेजिस्टर's value is undefined on
	 * reset.
	 */
	set_ptevaddr_रेजिस्टर(XCHAL_PAGE_TABLE_VADDR);
पूर्ण

व्योम init_kio(व्योम)
अणु
#अगर XCHAL_HAVE_PTP_MMU && XCHAL_HAVE_SPANNING_WAY && defined(CONFIG_OF)
	/*
	 * Update the IO area mapping in हाल xtensa_kio_paddr has changed
	 */
	ग_लिखो_dtlb_entry(__pte(xtensa_kio_paddr + CA_WRITEBACK),
			XCHAL_KIO_CACHED_VADDR + 6);
	ग_लिखो_itlb_entry(__pte(xtensa_kio_paddr + CA_WRITEBACK),
			XCHAL_KIO_CACHED_VADDR + 6);
	ग_लिखो_dtlb_entry(__pte(xtensa_kio_paddr + CA_BYPASS),
			XCHAL_KIO_BYPASS_VADDR + 6);
	ग_लिखो_itlb_entry(__pte(xtensa_kio_paddr + CA_BYPASS),
			XCHAL_KIO_BYPASS_VADDR + 6);
#पूर्ण_अगर
पूर्ण
