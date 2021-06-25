<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  IBM System z Huge TLB Page Support क्रम Kernel.
 *
 *    Copyright IBM Corp. 2008
 *    Author(s): Gerald Schaefer <gerald.schaefer@de.ibm.com>
 */

#अगर_अघोषित _ASM_S390_HUGETLB_H
#घोषणा _ASM_S390_HUGETLB_H

#समावेश <linux/pgtable.h>
#समावेश <यंत्र/page.h>

#घोषणा hugetlb_मुक्त_pgd_range			मुक्त_pgd_range
#घोषणा hugepages_supported()			(MACHINE_HAS_EDAT1)

व्योम set_huge_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, pte_t pte);
pte_t huge_ptep_get(pte_t *ptep);
pte_t huge_ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
			      अचिन्हित दीर्घ addr, pte_t *ptep);

/*
 * If the arch करोesn't supply something अन्यथा, assume that hugepage
 * size aligned regions are ok without further preparation.
 */
अटल अंतरभूत पूर्णांक prepare_hugepage_range(काष्ठा file *file,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	अगर (len & ~HPAGE_MASK)
		वापस -EINVAL;
	अगर (addr & ~HPAGE_MASK)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम arch_clear_hugepage_flags(काष्ठा page *page)
अणु
	clear_bit(PG_arch_1, &page->flags);
पूर्ण
#घोषणा arch_clear_hugepage_flags arch_clear_hugepage_flags

अटल अंतरभूत व्योम huge_pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				  pte_t *ptep, अचिन्हित दीर्घ sz)
अणु
	अगर ((pte_val(*ptep) & _REGION_ENTRY_TYPE_MASK) == _REGION_ENTRY_TYPE_R3)
		pte_val(*ptep) = _REGION3_ENTRY_EMPTY;
	अन्यथा
		pte_val(*ptep) = _SEGMENT_ENTRY_EMPTY;
पूर्ण

अटल अंतरभूत व्योम huge_ptep_clear_flush(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	huge_ptep_get_and_clear(vma->vm_mm, address, ptep);
पूर्ण

अटल अंतरभूत पूर्णांक huge_ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					     अचिन्हित दीर्घ addr, pte_t *ptep,
					     pte_t pte, पूर्णांक dirty)
अणु
	पूर्णांक changed = !pte_same(huge_ptep_get(ptep), pte);
	अगर (changed) अणु
		huge_ptep_get_and_clear(vma->vm_mm, addr, ptep);
		set_huge_pte_at(vma->vm_mm, addr, ptep, pte);
	पूर्ण
	वापस changed;
पूर्ण

अटल अंतरभूत व्योम huge_ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t pte = huge_ptep_get_and_clear(mm, addr, ptep);
	set_huge_pte_at(mm, addr, ptep, pte_wrprotect(pte));
पूर्ण

अटल अंतरभूत pte_t mk_huge_pte(काष्ठा page *page, pgprot_t pgprot)
अणु
	वापस mk_pte(page, pgprot);
पूर्ण

अटल अंतरभूत पूर्णांक huge_pte_none(pte_t pte)
अणु
	वापस pte_none(pte);
पूर्ण

अटल अंतरभूत पूर्णांक huge_pte_ग_लिखो(pte_t pte)
अणु
	वापस pte_ग_लिखो(pte);
पूर्ण

अटल अंतरभूत पूर्णांक huge_pte_dirty(pte_t pte)
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

अटल अंतरभूत pte_t huge_pte_wrprotect(pte_t pte)
अणु
	वापस pte_wrprotect(pte);
पूर्ण

अटल अंतरभूत pte_t huge_pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	वापस pte_modअगरy(pte, newprot);
पूर्ण

अटल अंतरभूत bool gigantic_page_runसमय_supported(व्योम)
अणु
	वापस true;
पूर्ण

#पूर्ण_अगर /* _ASM_S390_HUGETLB_H */
