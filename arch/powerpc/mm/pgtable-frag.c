<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 *  Handling Page Tables through page fragments
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>
#समावेश <linux/percpu.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/hugetlb.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/tlb.h>

व्योम pte_frag_destroy(व्योम *pte_frag)
अणु
	पूर्णांक count;
	काष्ठा page *page;

	page = virt_to_page(pte_frag);
	/* drop all the pending references */
	count = ((अचिन्हित दीर्घ)pte_frag & ~PAGE_MASK) >> PTE_FRAG_SIZE_SHIFT;
	/* We allow PTE_FRAG_NR fragments from a PTE page */
	अगर (atomic_sub_and_test(PTE_FRAG_NR - count, &page->pt_frag_refcount)) अणु
		pgtable_pte_page_dtor(page);
		__मुक्त_page(page);
	पूर्ण
पूर्ण

अटल pte_t *get_pte_from_cache(काष्ठा mm_काष्ठा *mm)
अणु
	व्योम *pte_frag, *ret;

	अगर (PTE_FRAG_NR == 1)
		वापस शून्य;

	spin_lock(&mm->page_table_lock);
	ret = pte_frag_get(&mm->context);
	अगर (ret) अणु
		pte_frag = ret + PTE_FRAG_SIZE;
		/*
		 * If we have taken up all the fragments mark PTE page शून्य
		 */
		अगर (((अचिन्हित दीर्घ)pte_frag & ~PAGE_MASK) == 0)
			pte_frag = शून्य;
		pte_frag_set(&mm->context, pte_frag);
	पूर्ण
	spin_unlock(&mm->page_table_lock);
	वापस (pte_t *)ret;
पूर्ण

अटल pte_t *__alloc_क्रम_ptecache(काष्ठा mm_काष्ठा *mm, पूर्णांक kernel)
अणु
	व्योम *ret = शून्य;
	काष्ठा page *page;

	अगर (!kernel) अणु
		page = alloc_page(PGALLOC_GFP | __GFP_ACCOUNT);
		अगर (!page)
			वापस शून्य;
		अगर (!pgtable_pte_page_ctor(page)) अणु
			__मुक्त_page(page);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		page = alloc_page(PGALLOC_GFP);
		अगर (!page)
			वापस शून्य;
	पूर्ण

	atomic_set(&page->pt_frag_refcount, 1);

	ret = page_address(page);
	/*
	 * अगर we support only one fragment just वापस the
	 * allocated page.
	 */
	अगर (PTE_FRAG_NR == 1)
		वापस ret;
	spin_lock(&mm->page_table_lock);
	/*
	 * If we find pgtable_page set, we वापस
	 * the allocated page with single fragement
	 * count.
	 */
	अगर (likely(!pte_frag_get(&mm->context))) अणु
		atomic_set(&page->pt_frag_refcount, PTE_FRAG_NR);
		pte_frag_set(&mm->context, ret + PTE_FRAG_SIZE);
	पूर्ण
	spin_unlock(&mm->page_table_lock);

	वापस (pte_t *)ret;
पूर्ण

pte_t *pte_fragment_alloc(काष्ठा mm_काष्ठा *mm, पूर्णांक kernel)
अणु
	pte_t *pte;

	pte = get_pte_from_cache(mm);
	अगर (pte)
		वापस pte;

	वापस __alloc_क्रम_ptecache(mm, kernel);
पूर्ण

व्योम pte_fragment_मुक्त(अचिन्हित दीर्घ *table, पूर्णांक kernel)
अणु
	काष्ठा page *page = virt_to_page(table);

	अगर (PageReserved(page))
		वापस मुक्त_reserved_page(page);

	BUG_ON(atomic_पढ़ो(&page->pt_frag_refcount) <= 0);
	अगर (atomic_dec_and_test(&page->pt_frag_refcount)) अणु
		अगर (!kernel)
			pgtable_pte_page_dtor(page);
		__मुक्त_page(page);
	पूर्ण
पूर्ण
