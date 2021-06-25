<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PGALLOC_TRACK_H
#घोषणा _LINUX_PGALLOC_TRACK_H

#अगर defined(CONFIG_MMU)
अटल अंतरभूत p4d_t *p4d_alloc_track(काष्ठा mm_काष्ठा *mm, pgd_t *pgd,
				     अचिन्हित दीर्घ address,
				     pgtbl_mod_mask *mod_mask)
अणु
	अगर (unlikely(pgd_none(*pgd))) अणु
		अगर (__p4d_alloc(mm, pgd, address))
			वापस शून्य;
		*mod_mask |= PGTBL_PGD_MODIFIED;
	पूर्ण

	वापस p4d_offset(pgd, address);
पूर्ण

अटल अंतरभूत pud_t *pud_alloc_track(काष्ठा mm_काष्ठा *mm, p4d_t *p4d,
				     अचिन्हित दीर्घ address,
				     pgtbl_mod_mask *mod_mask)
अणु
	अगर (unlikely(p4d_none(*p4d))) अणु
		अगर (__pud_alloc(mm, p4d, address))
			वापस शून्य;
		*mod_mask |= PGTBL_P4D_MODIFIED;
	पूर्ण

	वापस pud_offset(p4d, address);
पूर्ण

अटल अंतरभूत pmd_t *pmd_alloc_track(काष्ठा mm_काष्ठा *mm, pud_t *pud,
				     अचिन्हित दीर्घ address,
				     pgtbl_mod_mask *mod_mask)
अणु
	अगर (unlikely(pud_none(*pud))) अणु
		अगर (__pmd_alloc(mm, pud, address))
			वापस शून्य;
		*mod_mask |= PGTBL_PUD_MODIFIED;
	पूर्ण

	वापस pmd_offset(pud, address);
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */

#घोषणा pte_alloc_kernel_track(pmd, address, mask)			\
	((unlikely(pmd_none(*(pmd))) &&					\
	  (__pte_alloc_kernel(pmd) || (अणु*(mask)|=PGTBL_PMD_MODIFIED;0;पूर्ण)))?\
		शून्य: pte_offset_kernel(pmd, address))

#पूर्ण_अगर /* _LINUX_PGALLOC_TRACK_H */
