<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_HIGHMEM_INTERNAL_H
#घोषणा _LINUX_HIGHMEM_INTERNAL_H

/*
 * Outside of CONFIG_HIGHMEM to support X86 32bit iomap_atomic() cruft.
 */
#अगर_घोषित CONFIG_KMAP_LOCAL
व्योम *__kmap_local_pfn_prot(अचिन्हित दीर्घ pfn, pgprot_t prot);
व्योम *__kmap_local_page_prot(काष्ठा page *page, pgprot_t prot);
व्योम kunmap_local_indexed(व्योम *vaddr);
व्योम kmap_local_विभाजन(काष्ठा task_काष्ठा *tsk);
व्योम __kmap_local_sched_out(व्योम);
व्योम __kmap_local_sched_in(व्योम);
अटल अंतरभूत व्योम kmap_निश्चित_nomap(व्योम)
अणु
	DEBUG_LOCKS_WARN_ON(current->kmap_ctrl.idx);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम kmap_local_विभाजन(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत व्योम kmap_निश्चित_nomap(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HIGHMEM
#समावेश <यंत्र/highस्मृति.स>

#अगर_अघोषित ARCH_HAS_KMAP_FLUSH_TLB
अटल अंतरभूत व्योम kmap_flush_tlb(अचिन्हित दीर्घ addr) अणु पूर्ण
#पूर्ण_अगर

#अगर_अघोषित kmap_prot
#घोषणा kmap_prot PAGE_KERNEL
#पूर्ण_अगर

व्योम *kmap_high(काष्ठा page *page);
व्योम kunmap_high(काष्ठा page *page);
व्योम __kmap_flush_unused(व्योम);
काष्ठा page *__kmap_to_page(व्योम *addr);

अटल अंतरभूत व्योम *kmap(काष्ठा page *page)
अणु
	व्योम *addr;

	might_sleep();
	अगर (!PageHighMem(page))
		addr = page_address(page);
	अन्यथा
		addr = kmap_high(page);
	kmap_flush_tlb((अचिन्हित दीर्घ)addr);
	वापस addr;
पूर्ण

अटल अंतरभूत व्योम kunmap(काष्ठा page *page)
अणु
	might_sleep();
	अगर (!PageHighMem(page))
		वापस;
	kunmap_high(page);
पूर्ण

अटल अंतरभूत काष्ठा page *kmap_to_page(व्योम *addr)
अणु
	वापस __kmap_to_page(addr);
पूर्ण

अटल अंतरभूत व्योम kmap_flush_unused(व्योम)
अणु
	__kmap_flush_unused();
पूर्ण

अटल अंतरभूत व्योम *kmap_local_page(काष्ठा page *page)
अणु
	वापस __kmap_local_page_prot(page, kmap_prot);
पूर्ण

अटल अंतरभूत व्योम *kmap_local_page_prot(काष्ठा page *page, pgprot_t prot)
अणु
	वापस __kmap_local_page_prot(page, prot);
पूर्ण

अटल अंतरभूत व्योम *kmap_local_pfn(अचिन्हित दीर्घ pfn)
अणु
	वापस __kmap_local_pfn_prot(pfn, kmap_prot);
पूर्ण

अटल अंतरभूत व्योम __kunmap_local(व्योम *vaddr)
अणु
	kunmap_local_indexed(vaddr);
पूर्ण

अटल अंतरभूत व्योम *kmap_atomic_prot(काष्ठा page *page, pgprot_t prot)
अणु
	preempt_disable();
	pagefault_disable();
	वापस __kmap_local_page_prot(page, prot);
पूर्ण

अटल अंतरभूत व्योम *kmap_atomic(काष्ठा page *page)
अणु
	वापस kmap_atomic_prot(page, kmap_prot);
पूर्ण

अटल अंतरभूत व्योम *kmap_atomic_pfn(अचिन्हित दीर्घ pfn)
अणु
	preempt_disable();
	pagefault_disable();
	वापस __kmap_local_pfn_prot(pfn, kmap_prot);
पूर्ण

अटल अंतरभूत व्योम __kunmap_atomic(व्योम *addr)
अणु
	kunmap_local_indexed(addr);
	pagefault_enable();
	preempt_enable();
पूर्ण

अचिन्हित पूर्णांक __nr_मुक्त_highpages(व्योम);
बाह्य atomic_दीर्घ_t _totalhigh_pages;

अटल अंतरभूत अचिन्हित पूर्णांक nr_मुक्त_highpages(व्योम)
अणु
	वापस __nr_मुक्त_highpages();
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ totalhigh_pages(व्योम)
अणु
	वापस (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&_totalhigh_pages);
पूर्ण

अटल अंतरभूत व्योम totalhigh_pages_add(दीर्घ count)
अणु
	atomic_दीर्घ_add(count, &_totalhigh_pages);
पूर्ण

#अन्यथा /* CONFIG_HIGHMEM */

अटल अंतरभूत काष्ठा page *kmap_to_page(व्योम *addr)
अणु
	वापस virt_to_page(addr);
पूर्ण

अटल अंतरभूत व्योम *kmap(काष्ठा page *page)
अणु
	might_sleep();
	वापस page_address(page);
पूर्ण

अटल अंतरभूत व्योम kunmap_high(काष्ठा page *page) अणु पूर्ण
अटल अंतरभूत व्योम kmap_flush_unused(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम kunmap(काष्ठा page *page)
अणु
#अगर_घोषित ARCH_HAS_FLUSH_ON_KUNMAP
	kunmap_flush_on_unmap(page_address(page));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम *kmap_local_page(काष्ठा page *page)
अणु
	वापस page_address(page);
पूर्ण

अटल अंतरभूत व्योम *kmap_local_page_prot(काष्ठा page *page, pgprot_t prot)
अणु
	वापस kmap_local_page(page);
पूर्ण

अटल अंतरभूत व्योम *kmap_local_pfn(अचिन्हित दीर्घ pfn)
अणु
	वापस kmap_local_page(pfn_to_page(pfn));
पूर्ण

अटल अंतरभूत व्योम __kunmap_local(व्योम *addr)
अणु
#अगर_घोषित ARCH_HAS_FLUSH_ON_KUNMAP
	kunmap_flush_on_unmap(addr);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम *kmap_atomic(काष्ठा page *page)
अणु
	preempt_disable();
	pagefault_disable();
	वापस page_address(page);
पूर्ण

अटल अंतरभूत व्योम *kmap_atomic_prot(काष्ठा page *page, pgprot_t prot)
अणु
	वापस kmap_atomic(page);
पूर्ण

अटल अंतरभूत व्योम *kmap_atomic_pfn(अचिन्हित दीर्घ pfn)
अणु
	वापस kmap_atomic(pfn_to_page(pfn));
पूर्ण

अटल अंतरभूत व्योम __kunmap_atomic(व्योम *addr)
अणु
#अगर_घोषित ARCH_HAS_FLUSH_ON_KUNMAP
	kunmap_flush_on_unmap(addr);
#पूर्ण_अगर
	pagefault_enable();
	preempt_enable();
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक nr_मुक्त_highpages(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ totalhigh_pages(व्योम) अणु वापस 0UL; पूर्ण

#पूर्ण_अगर /* CONFIG_HIGHMEM */

/*
 * Prevent people trying to call kunmap_atomic() as अगर it were kunmap()
 * kunmap_atomic() should get the वापस value of kmap_atomic, not the page.
 */
#घोषणा kunmap_atomic(__addr)					\
करो अणु								\
	BUILD_BUG_ON(__same_type((__addr), काष्ठा page *));	\
	__kunmap_atomic(__addr);				\
पूर्ण जबतक (0)

#घोषणा kunmap_local(__addr)					\
करो अणु								\
	BUILD_BUG_ON(__same_type((__addr), काष्ठा page *));	\
	__kunmap_local(__addr);					\
पूर्ण जबतक (0)

#पूर्ण_अगर
