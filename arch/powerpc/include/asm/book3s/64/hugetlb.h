<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_HUGETLB_H
#घोषणा _ASM_POWERPC_BOOK3S_64_HUGETLB_H
/*
 * For radix we want generic code to handle hugetlb. But then अगर we want
 * both hash and radix to be enabled together we need to workaround the
 * limitations.
 */
व्योम radix__flush_hugetlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr);
व्योम radix__local_flush_hugetlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr);
बाह्य अचिन्हित दीर्घ
radix__hugetlb_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
				अचिन्हित दीर्घ flags);

बाह्य व्योम radix__huge_ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma,
						अचिन्हित दीर्घ addr, pte_t *ptep,
						pte_t old_pte, pte_t pte);

अटल अंतरभूत पूर्णांक hstate_get_psize(काष्ठा hstate *hstate)
अणु
	अचिन्हित दीर्घ shअगरt;

	shअगरt = huge_page_shअगरt(hstate);
	अगर (shअगरt == mmu_psize_defs[MMU_PAGE_2M].shअगरt)
		वापस MMU_PAGE_2M;
	अन्यथा अगर (shअगरt == mmu_psize_defs[MMU_PAGE_1G].shअगरt)
		वापस MMU_PAGE_1G;
	अन्यथा अगर (shअगरt == mmu_psize_defs[MMU_PAGE_16M].shअगरt)
		वापस MMU_PAGE_16M;
	अन्यथा अगर (shअगरt == mmu_psize_defs[MMU_PAGE_16G].shअगरt)
		वापस MMU_PAGE_16G;
	अन्यथा अणु
		WARN(1, "Wrong huge page shift\n");
		वापस mmu_भव_psize;
	पूर्ण
पूर्ण

#घोषणा __HAVE_ARCH_GIGANTIC_PAGE_RUNTIME_SUPPORTED
अटल अंतरभूत bool gigantic_page_runसमय_supported(व्योम)
अणु
	/*
	 * We used gigantic page reservation with hypervisor assist in some हाल.
	 * We cannot use runसमय allocation of gigantic pages in those platक्रमms
	 * This is hash translation mode LPARs.
	 */
	अगर (firmware_has_feature(FW_FEATURE_LPAR) && !radix_enabled())
		वापस false;

	वापस true;
पूर्ण

/* hugepd entry valid bit */
#घोषणा HUGEPD_VAL_BITS		(0x8000000000000000UL)

#घोषणा huge_ptep_modअगरy_prot_start huge_ptep_modअगरy_prot_start
बाह्य pte_t huge_ptep_modअगरy_prot_start(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ addr, pte_t *ptep);

#घोषणा huge_ptep_modअगरy_prot_commit huge_ptep_modअगरy_prot_commit
बाह्य व्योम huge_ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ addr, pte_t *ptep,
					 pte_t old_pte, pte_t new_pte);
/*
 * This should work क्रम other subarchs too. But right now we use the
 * new क्रमmat only क्रम 64bit book3s
 */
अटल अंतरभूत pte_t *hugepd_page(hugepd_t hpd)
अणु
	BUG_ON(!hugepd_ok(hpd));
	/*
	 * We have only four bits to encode, MMU page size
	 */
	BUILD_BUG_ON((MMU_PAGE_COUNT - 1) > 0xf);
	वापस __va(hpd_val(hpd) & HUGEPD_ADDR_MASK);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hugepd_mmu_psize(hugepd_t hpd)
अणु
	वापस (hpd_val(hpd) & HUGEPD_SHIFT_MASK) >> 2;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hugepd_shअगरt(hugepd_t hpd)
अणु
	वापस mmu_pमाप_प्रकारo_shअगरt(hugepd_mmu_psize(hpd));
पूर्ण
अटल अंतरभूत व्योम flush_hugetlb_page(काष्ठा vm_area_काष्ठा *vma,
				      अचिन्हित दीर्घ vmaddr)
अणु
	अगर (radix_enabled())
		वापस radix__flush_hugetlb_page(vma, vmaddr);
पूर्ण

अटल अंतरभूत pte_t *hugepte_offset(hugepd_t hpd, अचिन्हित दीर्घ addr,
				    अचिन्हित पूर्णांक pdshअगरt)
अणु
	अचिन्हित दीर्घ idx = (addr & ((1UL << pdshअगरt) - 1)) >> hugepd_shअगरt(hpd);

	वापस hugepd_page(hpd) + idx;
पूर्ण

अटल अंतरभूत व्योम hugepd_populate(hugepd_t *hpdp, pte_t *new, अचिन्हित पूर्णांक pshअगरt)
अणु
	*hpdp = __hugepd(__pa(new) | HUGEPD_VAL_BITS | (shअगरt_to_mmu_psize(pshअगरt) << 2));
पूर्ण

व्योम flush_hugetlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr);

अटल अंतरभूत पूर्णांक check_and_get_huge_psize(पूर्णांक shअगरt)
अणु
	पूर्णांक mmu_psize;

	अगर (shअगरt > SLICE_HIGH_SHIFT)
		वापस -EINVAL;

	mmu_psize = shअगरt_to_mmu_psize(shअगरt);

	/*
	 * We need to make sure that क्रम dअगरferent page sizes reported by
	 * firmware we only add hugetlb support क्रम page sizes that can be
	 * supported by linux page table layout.
	 * For now we have
	 * Radix: 2M and 1G
	 * Hash: 16M and 16G
	 */
	अगर (radix_enabled()) अणु
		अगर (mmu_psize != MMU_PAGE_2M && mmu_psize != MMU_PAGE_1G)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (mmu_psize != MMU_PAGE_16M && mmu_psize != MMU_PAGE_16G)
			वापस -EINVAL;
	पूर्ण
	वापस mmu_psize;
पूर्ण

#पूर्ण_अगर
