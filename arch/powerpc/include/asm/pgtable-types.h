<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_PGTABLE_TYPES_H
#घोषणा _ASM_POWERPC_PGTABLE_TYPES_H

/* PTE level */
#अगर defined(CONFIG_PPC_8xx) && defined(CONFIG_PPC_16K_PAGES)
प्रकार काष्ठा अणु pte_basic_t pte, pte1, pte2, pte3; पूर्ण pte_t;
#अन्यथा
प्रकार काष्ठा अणु pte_basic_t pte; पूर्ण pte_t;
#पूर्ण_अगर
#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण)
अटल अंतरभूत pte_basic_t pte_val(pte_t x)
अणु
	वापस x.pte;
पूर्ण

/* PMD level */
#अगर_घोषित CONFIG_PPC64
प्रकार काष्ठा अणु अचिन्हित दीर्घ pmd; पूर्ण pmd_t;
#घोषणा __pmd(x)	((pmd_t) अणु (x) पूर्ण)
अटल अंतरभूत अचिन्हित दीर्घ pmd_val(pmd_t x)
अणु
	वापस x.pmd;
पूर्ण

/* 64 bit always use 4 level table. */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pud; पूर्ण pud_t;
#घोषणा __pud(x)	((pud_t) अणु (x) पूर्ण)
अटल अंतरभूत अचिन्हित दीर्घ pud_val(pud_t x)
अणु
	वापस x.pud;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

/* PGD level */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण)
अटल अंतरभूत अचिन्हित दीर्घ pgd_val(pgd_t x)
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

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#समावेश <यंत्र/cmpxchg.h>

अटल अंतरभूत bool pte_xchg(pte_t *ptep, pte_t old, pte_t new)
अणु
	अचिन्हित दीर्घ *p = (अचिन्हित दीर्घ *)ptep;

	/* See comment in चयन_mm_irqs_off() */
	वापस pte_val(old) == __cmpxchg_u64(p, pte_val(old), pte_val(new));
पूर्ण
#पूर्ण_अगर

प्रकार काष्ठा अणु अचिन्हित दीर्घ pd; पूर्ण hugepd_t;
#घोषणा __hugepd(x) ((hugepd_t) अणु (x) पूर्ण)
अटल अंतरभूत अचिन्हित दीर्घ hpd_val(hugepd_t x)
अणु
	वापस x.pd;
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_PGTABLE_TYPES_H */
