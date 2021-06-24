<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_32_HUGETLB_8XX_H
#घोषणा _ASM_POWERPC_NOHASH_32_HUGETLB_8XX_H

#घोषणा PAGE_SHIFT_8M		23

अटल अंतरभूत pte_t *hugepd_page(hugepd_t hpd)
अणु
	BUG_ON(!hugepd_ok(hpd));

	वापस (pte_t *)__va(hpd_val(hpd) & ~HUGEPD_SHIFT_MASK);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hugepd_shअगरt(hugepd_t hpd)
अणु
	वापस PAGE_SHIFT_8M;
पूर्ण

अटल अंतरभूत pte_t *hugepte_offset(hugepd_t hpd, अचिन्हित दीर्घ addr,
				    अचिन्हित पूर्णांक pdshअगरt)
अणु
	अचिन्हित दीर्घ idx = (addr & (SZ_4M - 1)) >> PAGE_SHIFT;

	वापस hugepd_page(hpd) + idx;
पूर्ण

अटल अंतरभूत व्योम flush_hugetlb_page(काष्ठा vm_area_काष्ठा *vma,
				      अचिन्हित दीर्घ vmaddr)
अणु
	flush_tlb_page(vma, vmaddr);
पूर्ण

अटल अंतरभूत व्योम hugepd_populate(hugepd_t *hpdp, pte_t *new, अचिन्हित पूर्णांक pshअगरt)
अणु
	*hpdp = __hugepd(__pa(new) | _PMD_USER | _PMD_PRESENT | _PMD_PAGE_8M);
पूर्ण

अटल अंतरभूत व्योम hugepd_populate_kernel(hugepd_t *hpdp, pte_t *new, अचिन्हित पूर्णांक pshअगरt)
अणु
	*hpdp = __hugepd(__pa(new) | _PMD_PRESENT | _PMD_PAGE_8M);
पूर्ण

अटल अंतरभूत पूर्णांक check_and_get_huge_psize(पूर्णांक shअगरt)
अणु
	वापस shअगरt_to_mmu_psize(shअगरt);
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_SET_HUGE_PTE_AT
व्योम set_huge_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep, pte_t pte);

#घोषणा __HAVE_ARCH_HUGE_PTE_CLEAR
अटल अंतरभूत व्योम huge_pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				  pte_t *ptep, अचिन्हित दीर्घ sz)
अणु
	pte_update(mm, addr, ptep, ~0UL, 0, 1);
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम huge_ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	अचिन्हित दीर्घ clr = ~pte_val(pte_wrprotect(__pte(~0)));
	अचिन्हित दीर्घ set = pte_val(pte_wrprotect(__pte(0)));

	pte_update(mm, addr, ptep, clr, set, 1);
पूर्ण

#अगर_घोषित CONFIG_PPC_4K_PAGES
अटल अंतरभूत pte_t arch_make_huge_pte(pte_t entry, काष्ठा vm_area_काष्ठा *vma,
				       काष्ठा page *page, पूर्णांक writable)
अणु
	माप_प्रकार size = huge_page_size(hstate_vma(vma));

	अगर (size == SZ_16K)
		वापस __pte(pte_val(entry) & ~_PAGE_HUGE);
	अन्यथा
		वापस entry;
पूर्ण
#घोषणा arch_make_huge_pte arch_make_huge_pte
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_POWERPC_NOHASH_32_HUGETLB_8XX_H */
