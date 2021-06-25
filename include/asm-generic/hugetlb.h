<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_HUGETLB_H
#घोषणा _ASM_GENERIC_HUGETLB_H

अटल अंतरभूत pte_t mk_huge_pte(काष्ठा page *page, pgprot_t pgprot)
अणु
	वापस mk_pte(page, pgprot);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ huge_pte_ग_लिखो(pte_t pte)
अणु
	वापस pte_ग_लिखो(pte);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ huge_pte_dirty(pte_t pte)
अणु
	वापस pte_dirty(pte);
पूर्ण

अटल अंतरभूत pte_t huge_pte_mkग_लिखो(pte_t pte)
अणु
	वापस pte_mkग_लिखो(pte);
पूर्ण

अटल अंतरभूत pte_t huge_pte_सूची_गढ़ोty(pte_t pte)
अणु
	वापस pte_सूची_गढ़ोty(pte);
पूर्ण

अटल अंतरभूत pte_t huge_pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	वापस pte_modअगरy(pte, newprot);
पूर्ण

#अगर_अघोषित __HAVE_ARCH_HUGE_PTE_CLEAR
अटल अंतरभूत व्योम huge_pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		    pte_t *ptep, अचिन्हित दीर्घ sz)
अणु
	pte_clear(mm, addr, ptep);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_HUGETLB_FREE_PGD_RANGE
अटल अंतरभूत व्योम hugetlb_मुक्त_pgd_range(काष्ठा mmu_gather *tlb,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	मुक्त_pgd_range(tlb, addr, end, न्यूनमान, उच्चमानing);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_HUGE_SET_HUGE_PTE_AT
अटल अंतरभूत व्योम set_huge_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		pte_t *ptep, pte_t pte)
अणु
	set_pte_at(mm, addr, ptep, pte);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_HUGE_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t huge_ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	वापस ptep_get_and_clear(mm, addr, ptep);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_HUGE_PTEP_CLEAR_FLUSH
अटल अंतरभूत व्योम huge_ptep_clear_flush(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	ptep_clear_flush(vma, addr, ptep);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_HUGE_PTE_NONE
अटल अंतरभूत पूर्णांक huge_pte_none(pte_t pte)
अणु
	वापस pte_none(pte);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_HUGE_PTE_WRPROTECT
अटल अंतरभूत pte_t huge_pte_wrprotect(pte_t pte)
अणु
	वापस pte_wrprotect(pte);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_PREPARE_HUGEPAGE_RANGE
अटल अंतरभूत पूर्णांक prepare_hugepage_range(काष्ठा file *file,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	काष्ठा hstate *h = hstate_file(file);

	अगर (len & ~huge_page_mask(h))
		वापस -EINVAL;
	अगर (addr & ~huge_page_mask(h))
		वापस -EINVAL;

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_HUGE_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम huge_ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	ptep_set_wrprotect(mm, addr, ptep);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_HUGE_PTEP_SET_ACCESS_FLAGS
अटल अंतरभूत पूर्णांक huge_ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pte_t *ptep,
		pte_t pte, पूर्णांक dirty)
अणु
	वापस ptep_set_access_flags(vma, addr, ptep, pte, dirty);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_HUGE_PTEP_GET
अटल अंतरभूत pte_t huge_ptep_get(pte_t *ptep)
अणु
	वापस ptep_get(ptep);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_GIGANTIC_PAGE_RUNTIME_SUPPORTED
अटल अंतरभूत bool gigantic_page_runसमय_supported(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARCH_HAS_GIGANTIC_PAGE);
पूर्ण
#पूर्ण_अगर /* __HAVE_ARCH_GIGANTIC_PAGE_RUNTIME_SUPPORTED */

#पूर्ण_अगर /* _ASM_GENERIC_HUGETLB_H */
