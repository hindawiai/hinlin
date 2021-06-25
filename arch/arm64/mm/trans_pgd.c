<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Transitional page tables क्रम kexec and hibernate
 *
 * This file derived from: arch/arm64/kernel/hibernate.c
 *
 * Copyright (c) 2020, Microsoft Corporation.
 * Pavel Tatashin <pasha.tatashin@soleen.com>
 *
 */

/*
 * Transitional tables are used during प्रणाली transferring from one world to
 * another: such as during hibernate restore, and kexec reboots. During these
 * phases one cannot rely on page table not being overwritten. This is because
 * hibernate and kexec can overग_लिखो the current page tables during transition.
 */

#समावेश <यंत्र/trans_pgd.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/pgtable.h>
#समावेश <linux/suspend.h>
#समावेश <linux/bug.h>
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>

अटल व्योम *trans_alloc(काष्ठा trans_pgd_info *info)
अणु
	वापस info->trans_alloc_page(info->trans_alloc_arg);
पूर्ण

अटल व्योम _copy_pte(pte_t *dst_ptep, pte_t *src_ptep, अचिन्हित दीर्घ addr)
अणु
	pte_t pte = READ_ONCE(*src_ptep);

	अगर (pte_valid(pte)) अणु
		/*
		 * Resume will overग_लिखो areas that may be marked
		 * पढ़ो only (code, rodata). Clear the RDONLY bit from
		 * the temporary mappings we use during restore.
		 */
		set_pte(dst_ptep, pte_mkग_लिखो(pte));
	पूर्ण अन्यथा अगर (debug_pagealloc_enabled() && !pte_none(pte)) अणु
		/*
		 * debug_pagealloc will हटाओd the PTE_VALID bit अगर
		 * the page isn't in use by the resume kernel. It may have
		 * been in use by the original kernel, in which हाल we need
		 * to put it back in our copy to करो the restore.
		 *
		 * Beक्रमe marking this entry valid, check the pfn should
		 * be mapped.
		 */
		BUG_ON(!pfn_valid(pte_pfn(pte)));

		set_pte(dst_ptep, pte_mkpresent(pte_mkग_लिखो(pte)));
	पूर्ण
पूर्ण

अटल पूर्णांक copy_pte(काष्ठा trans_pgd_info *info, pmd_t *dst_pmdp,
		    pmd_t *src_pmdp, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	pte_t *src_ptep;
	pte_t *dst_ptep;
	अचिन्हित दीर्घ addr = start;

	dst_ptep = trans_alloc(info);
	अगर (!dst_ptep)
		वापस -ENOMEM;
	pmd_populate_kernel(शून्य, dst_pmdp, dst_ptep);
	dst_ptep = pte_offset_kernel(dst_pmdp, start);

	src_ptep = pte_offset_kernel(src_pmdp, start);
	करो अणु
		_copy_pte(dst_ptep, src_ptep, addr);
	पूर्ण जबतक (dst_ptep++, src_ptep++, addr += PAGE_SIZE, addr != end);

	वापस 0;
पूर्ण

अटल पूर्णांक copy_pmd(काष्ठा trans_pgd_info *info, pud_t *dst_pudp,
		    pud_t *src_pudp, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	pmd_t *src_pmdp;
	pmd_t *dst_pmdp;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ addr = start;

	अगर (pud_none(READ_ONCE(*dst_pudp))) अणु
		dst_pmdp = trans_alloc(info);
		अगर (!dst_pmdp)
			वापस -ENOMEM;
		pud_populate(शून्य, dst_pudp, dst_pmdp);
	पूर्ण
	dst_pmdp = pmd_offset(dst_pudp, start);

	src_pmdp = pmd_offset(src_pudp, start);
	करो अणु
		pmd_t pmd = READ_ONCE(*src_pmdp);

		next = pmd_addr_end(addr, end);
		अगर (pmd_none(pmd))
			जारी;
		अगर (pmd_table(pmd)) अणु
			अगर (copy_pte(info, dst_pmdp, src_pmdp, addr, next))
				वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			set_pmd(dst_pmdp,
				__pmd(pmd_val(pmd) & ~PMD_SECT_RDONLY));
		पूर्ण
	पूर्ण जबतक (dst_pmdp++, src_pmdp++, addr = next, addr != end);

	वापस 0;
पूर्ण

अटल पूर्णांक copy_pud(काष्ठा trans_pgd_info *info, p4d_t *dst_p4dp,
		    p4d_t *src_p4dp, अचिन्हित दीर्घ start,
		    अचिन्हित दीर्घ end)
अणु
	pud_t *dst_pudp;
	pud_t *src_pudp;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ addr = start;

	अगर (p4d_none(READ_ONCE(*dst_p4dp))) अणु
		dst_pudp = trans_alloc(info);
		अगर (!dst_pudp)
			वापस -ENOMEM;
		p4d_populate(शून्य, dst_p4dp, dst_pudp);
	पूर्ण
	dst_pudp = pud_offset(dst_p4dp, start);

	src_pudp = pud_offset(src_p4dp, start);
	करो अणु
		pud_t pud = READ_ONCE(*src_pudp);

		next = pud_addr_end(addr, end);
		अगर (pud_none(pud))
			जारी;
		अगर (pud_table(pud)) अणु
			अगर (copy_pmd(info, dst_pudp, src_pudp, addr, next))
				वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			set_pud(dst_pudp,
				__pud(pud_val(pud) & ~PUD_SECT_RDONLY));
		पूर्ण
	पूर्ण जबतक (dst_pudp++, src_pudp++, addr = next, addr != end);

	वापस 0;
पूर्ण

अटल पूर्णांक copy_p4d(काष्ठा trans_pgd_info *info, pgd_t *dst_pgdp,
		    pgd_t *src_pgdp, अचिन्हित दीर्घ start,
		    अचिन्हित दीर्घ end)
अणु
	p4d_t *dst_p4dp;
	p4d_t *src_p4dp;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ addr = start;

	dst_p4dp = p4d_offset(dst_pgdp, start);
	src_p4dp = p4d_offset(src_pgdp, start);
	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (p4d_none(READ_ONCE(*src_p4dp)))
			जारी;
		अगर (copy_pud(info, dst_p4dp, src_p4dp, addr, next))
			वापस -ENOMEM;
	पूर्ण जबतक (dst_p4dp++, src_p4dp++, addr = next, addr != end);

	वापस 0;
पूर्ण

अटल पूर्णांक copy_page_tables(काष्ठा trans_pgd_info *info, pgd_t *dst_pgdp,
			    अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ addr = start;
	pgd_t *src_pgdp = pgd_offset_k(start);

	dst_pgdp = pgd_offset_pgd(dst_pgdp, start);
	करो अणु
		next = pgd_addr_end(addr, end);
		अगर (pgd_none(READ_ONCE(*src_pgdp)))
			जारी;
		अगर (copy_p4d(info, dst_pgdp, src_pgdp, addr, next))
			वापस -ENOMEM;
	पूर्ण जबतक (dst_pgdp++, src_pgdp++, addr = next, addr != end);

	वापस 0;
पूर्ण

/*
 * Create trans_pgd and copy linear map.
 * info:	contains allocator and its argument
 * dst_pgdp:	new page table that is created, and to which map is copied.
 * start:	Start of the पूर्णांकerval (inclusive).
 * end:		End of the पूर्णांकerval (exclusive).
 *
 * Returns 0 on success, and -ENOMEM on failure.
 */
पूर्णांक trans_pgd_create_copy(काष्ठा trans_pgd_info *info, pgd_t **dst_pgdp,
			  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	पूर्णांक rc;
	pgd_t *trans_pgd = trans_alloc(info);

	अगर (!trans_pgd) अणु
		pr_err("Failed to allocate memory for temporary page tables.\n");
		वापस -ENOMEM;
	पूर्ण

	rc = copy_page_tables(info, trans_pgd, start, end);
	अगर (!rc)
		*dst_pgdp = trans_pgd;

	वापस rc;
पूर्ण

/*
 * Add map entry to trans_pgd क्रम a base-size page at PTE level.
 * info:	contains allocator and its argument
 * trans_pgd:	page table in which new map is added.
 * page:	page to be mapped.
 * dst_addr:	new VA address क्रम the page
 * pgprot:	protection क्रम the page.
 *
 * Returns 0 on success, and -ENOMEM on failure.
 */
पूर्णांक trans_pgd_map_page(काष्ठा trans_pgd_info *info, pgd_t *trans_pgd,
		       व्योम *page, अचिन्हित दीर्घ dst_addr, pgprot_t pgprot)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	pgdp = pgd_offset_pgd(trans_pgd, dst_addr);
	अगर (pgd_none(READ_ONCE(*pgdp))) अणु
		p4dp = trans_alloc(info);
		अगर (!pgdp)
			वापस -ENOMEM;
		pgd_populate(शून्य, pgdp, p4dp);
	पूर्ण

	p4dp = p4d_offset(pgdp, dst_addr);
	अगर (p4d_none(READ_ONCE(*p4dp))) अणु
		pudp = trans_alloc(info);
		अगर (!pudp)
			वापस -ENOMEM;
		p4d_populate(शून्य, p4dp, pudp);
	पूर्ण

	pudp = pud_offset(p4dp, dst_addr);
	अगर (pud_none(READ_ONCE(*pudp))) अणु
		pmdp = trans_alloc(info);
		अगर (!pmdp)
			वापस -ENOMEM;
		pud_populate(शून्य, pudp, pmdp);
	पूर्ण

	pmdp = pmd_offset(pudp, dst_addr);
	अगर (pmd_none(READ_ONCE(*pmdp))) अणु
		ptep = trans_alloc(info);
		अगर (!ptep)
			वापस -ENOMEM;
		pmd_populate_kernel(शून्य, pmdp, ptep);
	पूर्ण

	ptep = pte_offset_kernel(pmdp, dst_addr);
	set_pte(ptep, pfn_pte(virt_to_pfn(page), pgprot));

	वापस 0;
पूर्ण

/*
 * The page we want to idmap may be outside the range covered by VA_BITS that
 * can be built using the kernel's p?d_populate() helpers. As a one off, क्रम a
 * single page, we build these page tables bottom up and just assume that will
 * need the maximum T0SZ.
 *
 * Returns 0 on success, and -ENOMEM on failure.
 * On success trans_ttbr0 contains page table with idmapped page, t0sz is set to
 * maximum T0SZ क्रम this page.
 */
पूर्णांक trans_pgd_idmap_page(काष्ठा trans_pgd_info *info, phys_addr_t *trans_ttbr0,
			 अचिन्हित दीर्घ *t0sz, व्योम *page)
अणु
	phys_addr_t dst_addr = virt_to_phys(page);
	अचिन्हित दीर्घ pfn = __phys_to_pfn(dst_addr);
	पूर्णांक max_msb = (dst_addr & GENMASK(52, 48)) ? 51 : 47;
	पूर्णांक bits_mapped = PAGE_SHIFT - 4;
	अचिन्हित दीर्घ level_mask, prev_level_entry, *levels[4];
	पूर्णांक this_level, index, level_lsb, level_msb;

	dst_addr &= PAGE_MASK;
	prev_level_entry = pte_val(pfn_pte(pfn, PAGE_KERNEL_EXEC));

	क्रम (this_level = 3; this_level >= 0; this_level--) अणु
		levels[this_level] = trans_alloc(info);
		अगर (!levels[this_level])
			वापस -ENOMEM;

		level_lsb = ARM64_HW_PGTABLE_LEVEL_SHIFT(this_level);
		level_msb = min(level_lsb + bits_mapped, max_msb);
		level_mask = GENMASK_ULL(level_msb, level_lsb);

		index = (dst_addr & level_mask) >> level_lsb;
		*(levels[this_level] + index) = prev_level_entry;

		pfn = virt_to_pfn(levels[this_level]);
		prev_level_entry = pte_val(pfn_pte(pfn,
						   __pgprot(PMD_TYPE_TABLE)));

		अगर (level_msb == max_msb)
			अवरोध;
	पूर्ण

	*trans_ttbr0 = phys_to_ttbr(__pfn_to_phys(pfn));
	*t0sz = TCR_T0SZ(max_msb + 1);

	वापस 0;
पूर्ण
