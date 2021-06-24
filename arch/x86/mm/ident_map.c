<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Helper routines क्रम building identity mapping page tables. This is
 * included by both the compressed kernel and the regular kernel.
 */

अटल व्योम ident_pmd_init(काष्ठा x86_mapping_info *info, pmd_t *pmd_page,
			   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	addr &= PMD_MASK;
	क्रम (; addr < end; addr += PMD_SIZE) अणु
		pmd_t *pmd = pmd_page + pmd_index(addr);

		अगर (pmd_present(*pmd))
			जारी;

		set_pmd(pmd, __pmd((addr - info->offset) | info->page_flag));
	पूर्ण
पूर्ण

अटल पूर्णांक ident_pud_init(काष्ठा x86_mapping_info *info, pud_t *pud_page,
			  अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;

	क्रम (; addr < end; addr = next) अणु
		pud_t *pud = pud_page + pud_index(addr);
		pmd_t *pmd;

		next = (addr & PUD_MASK) + PUD_SIZE;
		अगर (next > end)
			next = end;

		अगर (info->direct_gbpages) अणु
			pud_t pudval;

			अगर (pud_present(*pud))
				जारी;

			addr &= PUD_MASK;
			pudval = __pud((addr - info->offset) | info->page_flag);
			set_pud(pud, pudval);
			जारी;
		पूर्ण

		अगर (pud_present(*pud)) अणु
			pmd = pmd_offset(pud, 0);
			ident_pmd_init(info, pmd, addr, next);
			जारी;
		पूर्ण
		pmd = (pmd_t *)info->alloc_pgt_page(info->context);
		अगर (!pmd)
			वापस -ENOMEM;
		ident_pmd_init(info, pmd, addr, next);
		set_pud(pud, __pud(__pa(pmd) | info->kernpg_flag));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ident_p4d_init(काष्ठा x86_mapping_info *info, p4d_t *p4d_page,
			  अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;
	पूर्णांक result;

	क्रम (; addr < end; addr = next) अणु
		p4d_t *p4d = p4d_page + p4d_index(addr);
		pud_t *pud;

		next = (addr & P4D_MASK) + P4D_SIZE;
		अगर (next > end)
			next = end;

		अगर (p4d_present(*p4d)) अणु
			pud = pud_offset(p4d, 0);
			result = ident_pud_init(info, pud, addr, next);
			अगर (result)
				वापस result;

			जारी;
		पूर्ण
		pud = (pud_t *)info->alloc_pgt_page(info->context);
		अगर (!pud)
			वापस -ENOMEM;

		result = ident_pud_init(info, pud, addr, next);
		अगर (result)
			वापस result;

		set_p4d(p4d, __p4d(__pa(pud) | info->kernpg_flag));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक kernel_ident_mapping_init(काष्ठा x86_mapping_info *info, pgd_t *pgd_page,
			      अचिन्हित दीर्घ pstart, अचिन्हित दीर्घ pend)
अणु
	अचिन्हित दीर्घ addr = pstart + info->offset;
	अचिन्हित दीर्घ end = pend + info->offset;
	अचिन्हित दीर्घ next;
	पूर्णांक result;

	/* Set the शेष pagetable flags अगर not supplied */
	अगर (!info->kernpg_flag)
		info->kernpg_flag = _KERNPG_TABLE;

	/* Filter out unsupported __PAGE_KERNEL_* bits: */
	info->kernpg_flag &= __शेष_kernel_pte_mask;

	क्रम (; addr < end; addr = next) अणु
		pgd_t *pgd = pgd_page + pgd_index(addr);
		p4d_t *p4d;

		next = (addr & PGसूची_MASK) + PGसूची_SIZE;
		अगर (next > end)
			next = end;

		अगर (pgd_present(*pgd)) अणु
			p4d = p4d_offset(pgd, 0);
			result = ident_p4d_init(info, p4d, addr, next);
			अगर (result)
				वापस result;
			जारी;
		पूर्ण

		p4d = (p4d_t *)info->alloc_pgt_page(info->context);
		अगर (!p4d)
			वापस -ENOMEM;
		result = ident_p4d_init(info, p4d, addr, next);
		अगर (result)
			वापस result;
		अगर (pgtable_l5_enabled()) अणु
			set_pgd(pgd, __pgd(__pa(p4d) | info->kernpg_flag));
		पूर्ण अन्यथा अणु
			/*
			 * With p4d folded, pgd is equal to p4d.
			 * The pgd entry has to poपूर्णांक to the pud page table in this हाल.
			 */
			pud_t *pud = pud_offset(p4d, 0);
			set_pgd(pgd, __pgd(__pa(pud) | info->kernpg_flag));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
