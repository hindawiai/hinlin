<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_PGTABLE_BE_TYPES_H
#घोषणा _ASM_POWERPC_PGTABLE_BE_TYPES_H

#समावेश <यंत्र/cmpxchg.h>

/* PTE level */
प्रकार काष्ठा अणु __be64 pte; पूर्ण pte_t;
#घोषणा __pte(x)	((pte_t) अणु cpu_to_be64(x) पूर्ण)
#घोषणा __pte_raw(x)	((pte_t) अणु (x) पूर्ण)
अटल अंतरभूत अचिन्हित दीर्घ pte_val(pte_t x)
अणु
	वापस be64_to_cpu(x.pte);
पूर्ण

अटल अंतरभूत __be64 pte_raw(pte_t x)
अणु
	वापस x.pte;
पूर्ण

/* PMD level */
#अगर_घोषित CONFIG_PPC64
प्रकार काष्ठा अणु __be64 pmd; पूर्ण pmd_t;
#घोषणा __pmd(x)	((pmd_t) अणु cpu_to_be64(x) पूर्ण)
#घोषणा __pmd_raw(x)	((pmd_t) अणु (x) पूर्ण)
अटल अंतरभूत अचिन्हित दीर्घ pmd_val(pmd_t x)
अणु
	वापस be64_to_cpu(x.pmd);
पूर्ण

अटल अंतरभूत __be64 pmd_raw(pmd_t x)
अणु
	वापस x.pmd;
पूर्ण

/* 64 bit always use 4 level table. */
प्रकार काष्ठा अणु __be64 pud; पूर्ण pud_t;
#घोषणा __pud(x)	((pud_t) अणु cpu_to_be64(x) पूर्ण)
#घोषणा __pud_raw(x)	((pud_t) अणु (x) पूर्ण)
अटल अंतरभूत अचिन्हित दीर्घ pud_val(pud_t x)
अणु
	वापस be64_to_cpu(x.pud);
पूर्ण

अटल अंतरभूत __be64 pud_raw(pud_t x)
अणु
	वापस x.pud;
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC64 */

/* PGD level */
प्रकार काष्ठा अणु __be64 pgd; पूर्ण pgd_t;
#घोषणा __pgd(x)	((pgd_t) अणु cpu_to_be64(x) पूर्ण)
#घोषणा __pgd_raw(x)	((pgd_t) अणु (x) पूर्ण)
अटल अंतरभूत अचिन्हित दीर्घ pgd_val(pgd_t x)
अणु
	वापस be64_to_cpu(x.pgd);
पूर्ण

अटल अंतरभूत __be64 pgd_raw(pgd_t x)
अणु
	वापस x.pgd;
पूर्ण

/* Page protection bits */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;
#घोषणा pgprot_val(x)	((x).pgprot)
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण)

/*
 * With hash config 64k pages additionally define a bigger "real PTE" type that
 * gathers the "second half" part of the PTE क्रम pseuकरो 64k pages
 */
#अगर_घोषित CONFIG_PPC_64K_PAGES
प्रकार काष्ठा अणु pte_t pte; अचिन्हित दीर्घ hidx; पूर्ण real_pte_t;
#अन्यथा
प्रकार काष्ठा अणु pte_t pte; पूर्ण real_pte_t;
#पूर्ण_अगर

अटल अंतरभूत bool pte_xchg(pte_t *ptep, pte_t old, pte_t new)
अणु
	अचिन्हित दीर्घ *p = (अचिन्हित दीर्घ *)ptep;
	__be64 prev;

	/* See comment in चयन_mm_irqs_off() */
	prev = (__क्रमce __be64)__cmpxchg_u64(p, (__क्रमce अचिन्हित दीर्घ)pte_raw(old),
					     (__क्रमce अचिन्हित दीर्घ)pte_raw(new));

	वापस pte_raw(old) == prev;
पूर्ण

अटल अंतरभूत bool pmd_xchg(pmd_t *pmdp, pmd_t old, pmd_t new)
अणु
	अचिन्हित दीर्घ *p = (अचिन्हित दीर्घ *)pmdp;
	__be64 prev;

	prev = (__क्रमce __be64)__cmpxchg_u64(p, (__क्रमce अचिन्हित दीर्घ)pmd_raw(old),
					     (__क्रमce अचिन्हित दीर्घ)pmd_raw(new));

	वापस pmd_raw(old) == prev;
पूर्ण

प्रकार काष्ठा अणु __be64 pdbe; पूर्ण hugepd_t;
#घोषणा __hugepd(x) ((hugepd_t) अणु cpu_to_be64(x) पूर्ण)

अटल अंतरभूत अचिन्हित दीर्घ hpd_val(hugepd_t x)
अणु
	वापस be64_to_cpu(x.pdbe);
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_PGTABLE_BE_TYPES_H */
