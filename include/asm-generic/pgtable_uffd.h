<शैली गुरु>
#अगर_अघोषित _ASM_GENERIC_PGTABLE_UFFD_H
#घोषणा _ASM_GENERIC_PGTABLE_UFFD_H

#अगर_अघोषित CONFIG_HAVE_ARCH_USERFAULTFD_WP
अटल __always_अंतरभूत पूर्णांक pte_uffd_wp(pte_t pte)
अणु
	वापस 0;
पूर्ण

अटल __always_अंतरभूत पूर्णांक pmd_uffd_wp(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

अटल __always_अंतरभूत pte_t pte_mkuffd_wp(pte_t pte)
अणु
	वापस pte;
पूर्ण

अटल __always_अंतरभूत pmd_t pmd_mkuffd_wp(pmd_t pmd)
अणु
	वापस pmd;
पूर्ण

अटल __always_अंतरभूत pte_t pte_clear_uffd_wp(pte_t pte)
अणु
	वापस pte;
पूर्ण

अटल __always_अंतरभूत pmd_t pmd_clear_uffd_wp(pmd_t pmd)
अणु
	वापस pmd;
पूर्ण

अटल __always_अंतरभूत pte_t pte_swp_mkuffd_wp(pte_t pte)
अणु
	वापस pte;
पूर्ण

अटल __always_अंतरभूत पूर्णांक pte_swp_uffd_wp(pte_t pte)
अणु
	वापस 0;
पूर्ण

अटल __always_अंतरभूत pte_t pte_swp_clear_uffd_wp(pte_t pte)
अणु
	वापस pte;
पूर्ण

अटल अंतरभूत pmd_t pmd_swp_mkuffd_wp(pmd_t pmd)
अणु
	वापस pmd;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_swp_uffd_wp(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत pmd_t pmd_swp_clear_uffd_wp(pmd_t pmd)
अणु
	वापस pmd;
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_USERFAULTFD_WP */

#पूर्ण_अगर /* _ASM_GENERIC_PGTABLE_UFFD_H */
