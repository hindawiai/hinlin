<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_HUGETLB_BOOK3E_H
#घोषणा _ASM_POWERPC_NOHASH_HUGETLB_BOOK3E_H

अटल अंतरभूत pte_t *hugepd_page(hugepd_t hpd)
अणु
	अगर (WARN_ON(!hugepd_ok(hpd)))
		वापस शून्य;

	वापस (pte_t *)((hpd_val(hpd) & ~HUGEPD_SHIFT_MASK) | PD_HUGE);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hugepd_shअगरt(hugepd_t hpd)
अणु
	वापस hpd_val(hpd) & HUGEPD_SHIFT_MASK;
पूर्ण

अटल अंतरभूत pte_t *hugepte_offset(hugepd_t hpd, अचिन्हित दीर्घ addr,
				    अचिन्हित पूर्णांक pdshअगरt)
अणु
	/*
	 * On FSL BookE, we have multiple higher-level table entries that
	 * poपूर्णांक to the same hugepte.  Just use the first one since they're all
	 * identical.  So क्रम that हाल, idx=0.
	 */
	वापस hugepd_page(hpd);
पूर्ण

व्योम flush_hugetlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr);

अटल अंतरभूत व्योम hugepd_populate(hugepd_t *hpdp, pte_t *new, अचिन्हित पूर्णांक pshअगरt)
अणु
	/* We use the old क्रमmat क्रम PPC_FSL_BOOK3E */
	*hpdp = __hugepd(((अचिन्हित दीर्घ)new & ~PD_HUGE) | pshअगरt);
पूर्ण

अटल अंतरभूत पूर्णांक check_and_get_huge_psize(पूर्णांक shअगरt)
अणु
	अगर (shअगरt & 1)	/* Not a घातer of 4 */
		वापस -EINVAL;

	वापस shअगरt_to_mmu_psize(shअगरt);
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_NOHASH_HUGETLB_BOOK3E_H */
