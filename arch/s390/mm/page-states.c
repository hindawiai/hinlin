<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2008
 *
 * Guest page hपूर्णांकing क्रम unused pages.
 *
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/page-states.h>

अटल पूर्णांक cmma_flag = 1;

अटल पूर्णांक __init cmma(अक्षर *str)
अणु
	bool enabled;

	अगर (!kstrtobool(str, &enabled))
		cmma_flag = enabled;
	वापस 1;
पूर्ण
__setup("cmma=", cmma);

अटल अंतरभूत पूर्णांक cmma_test_essa(व्योम)
अणु
	रेजिस्टर अचिन्हित दीर्घ पंचांगp यंत्र("0") = 0;
	रेजिस्टर पूर्णांक rc यंत्र("1");

	/* test ESSA_GET_STATE */
	यंत्र अस्थिर(
		"	.insn	rrf,0xb9ab0000,%1,%1,%2,0\n"
		"0:     la      %0,0\n"
		"1:\n"
		EX_TABLE(0b,1b)
		: "=&d" (rc), "+&d" (पंचांगp)
		: "i" (ESSA_GET_STATE), "0" (-EOPNOTSUPP));
	वापस rc;
पूर्ण

व्योम __init cmma_init(व्योम)
अणु
	अगर (!cmma_flag)
		वापस;
	अगर (cmma_test_essa()) अणु
		cmma_flag = 0;
		वापस;
	पूर्ण
	अगर (test_facility(147))
		cmma_flag = 2;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर get_page_state(काष्ठा page *page)
अणु
	अचिन्हित अक्षर state;

	यंत्र अस्थिर("	.insn	rrf,0xb9ab0000,%0,%1,%2,0"
		     : "=&d" (state)
		     : "a" (page_to_phys(page)),
		       "i" (ESSA_GET_STATE));
	वापस state & 0x3f;
पूर्ण

अटल अंतरभूत व्योम set_page_unused(काष्ठा page *page, पूर्णांक order)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0; i < (1 << order); i++)
		यंत्र अस्थिर(".insn rrf,0xb9ab0000,%0,%1,%2,0"
			     : "=&d" (rc)
			     : "a" (page_to_phys(page + i)),
			       "i" (ESSA_SET_UNUSED));
पूर्ण

अटल अंतरभूत व्योम set_page_stable_dat(काष्ठा page *page, पूर्णांक order)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0; i < (1 << order); i++)
		यंत्र अस्थिर(".insn rrf,0xb9ab0000,%0,%1,%2,0"
			     : "=&d" (rc)
			     : "a" (page_to_phys(page + i)),
			       "i" (ESSA_SET_STABLE));
पूर्ण

अटल अंतरभूत व्योम set_page_stable_nodat(काष्ठा page *page, पूर्णांक order)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0; i < (1 << order); i++)
		यंत्र अस्थिर(".insn rrf,0xb9ab0000,%0,%1,%2,0"
			     : "=&d" (rc)
			     : "a" (page_to_phys(page + i)),
			       "i" (ESSA_SET_STABLE_NODAT));
पूर्ण

अटल व्योम mark_kernel_pmd(pud_t *pud, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;
	काष्ठा page *page;
	pmd_t *pmd;

	pmd = pmd_offset(pud, addr);
	करो अणु
		next = pmd_addr_end(addr, end);
		अगर (pmd_none(*pmd) || pmd_large(*pmd))
			जारी;
		page = phys_to_page(pmd_val(*pmd));
		set_bit(PG_arch_1, &page->flags);
	पूर्ण जबतक (pmd++, addr = next, addr != end);
पूर्ण

अटल व्योम mark_kernel_pud(p4d_t *p4d, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;
	काष्ठा page *page;
	pud_t *pud;
	पूर्णांक i;

	pud = pud_offset(p4d, addr);
	करो अणु
		next = pud_addr_end(addr, end);
		अगर (pud_none(*pud) || pud_large(*pud))
			जारी;
		अगर (!pud_folded(*pud)) अणु
			page = phys_to_page(pud_val(*pud));
			क्रम (i = 0; i < 3; i++)
				set_bit(PG_arch_1, &page[i].flags);
		पूर्ण
		mark_kernel_pmd(pud, addr, next);
	पूर्ण जबतक (pud++, addr = next, addr != end);
पूर्ण

अटल व्योम mark_kernel_p4d(pgd_t *pgd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;
	काष्ठा page *page;
	p4d_t *p4d;
	पूर्णांक i;

	p4d = p4d_offset(pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (p4d_none(*p4d))
			जारी;
		अगर (!p4d_folded(*p4d)) अणु
			page = phys_to_page(p4d_val(*p4d));
			क्रम (i = 0; i < 3; i++)
				set_bit(PG_arch_1, &page[i].flags);
		पूर्ण
		mark_kernel_pud(p4d, addr, next);
	पूर्ण जबतक (p4d++, addr = next, addr != end);
पूर्ण

अटल व्योम mark_kernel_pgd(व्योम)
अणु
	अचिन्हित दीर्घ addr, next;
	काष्ठा page *page;
	pgd_t *pgd;
	पूर्णांक i;

	addr = 0;
	pgd = pgd_offset_k(addr);
	करो अणु
		next = pgd_addr_end(addr, MODULES_END);
		अगर (pgd_none(*pgd))
			जारी;
		अगर (!pgd_folded(*pgd)) अणु
			page = phys_to_page(pgd_val(*pgd));
			क्रम (i = 0; i < 3; i++)
				set_bit(PG_arch_1, &page[i].flags);
		पूर्ण
		mark_kernel_p4d(pgd, addr, next);
	पूर्ण जबतक (pgd++, addr = next, addr != MODULES_END);
पूर्ण

व्योम __init cmma_init_nodat(व्योम)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ start, end, ix;
	पूर्णांक i;

	अगर (cmma_flag < 2)
		वापस;
	/* Mark pages used in kernel page tables */
	mark_kernel_pgd();

	/* Set all kernel pages not used क्रम page tables to stable/no-dat */
	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &start, &end, शून्य) अणु
		page = pfn_to_page(start);
		क्रम (ix = start; ix < end; ix++, page++) अणु
			अगर (__test_and_clear_bit(PG_arch_1, &page->flags))
				जारी;	/* skip page table pages */
			अगर (!list_empty(&page->lru))
				जारी;	/* skip मुक्त pages */
			set_page_stable_nodat(page, 0);
		पूर्ण
	पूर्ण
पूर्ण

व्योम arch_मुक्त_page(काष्ठा page *page, पूर्णांक order)
अणु
	अगर (!cmma_flag)
		वापस;
	set_page_unused(page, order);
पूर्ण

व्योम arch_alloc_page(काष्ठा page *page, पूर्णांक order)
अणु
	अगर (!cmma_flag)
		वापस;
	अगर (cmma_flag < 2)
		set_page_stable_dat(page, order);
	अन्यथा
		set_page_stable_nodat(page, order);
पूर्ण

व्योम arch_set_page_dat(काष्ठा page *page, पूर्णांक order)
अणु
	अगर (!cmma_flag)
		वापस;
	set_page_stable_dat(page, order);
पूर्ण

व्योम arch_set_page_nodat(काष्ठा page *page, पूर्णांक order)
अणु
	अगर (cmma_flag < 2)
		वापस;
	set_page_stable_nodat(page, order);
पूर्ण

पूर्णांक arch_test_page_nodat(काष्ठा page *page)
अणु
	अचिन्हित अक्षर state;

	अगर (cmma_flag < 2)
		वापस 0;
	state = get_page_state(page);
	वापस !!(state & 0x20);
पूर्ण

व्योम arch_set_page_states(पूर्णांक make_stable)
अणु
	अचिन्हित दीर्घ flags, order, t;
	काष्ठा list_head *l;
	काष्ठा page *page;
	काष्ठा zone *zone;

	अगर (!cmma_flag)
		वापस;
	अगर (make_stable)
		drain_local_pages(शून्य);
	क्रम_each_populated_zone(zone) अणु
		spin_lock_irqsave(&zone->lock, flags);
		क्रम_each_migratetype_order(order, t) अणु
			list_क्रम_each(l, &zone->मुक्त_area[order].मुक्त_list[t]) अणु
				page = list_entry(l, काष्ठा page, lru);
				अगर (make_stable)
					set_page_stable_dat(page, order);
				अन्यथा
					set_page_unused(page, order);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&zone->lock, flags);
	पूर्ण
पूर्ण
