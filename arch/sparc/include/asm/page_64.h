<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_PAGE_H
#घोषणा _SPARC64_PAGE_H

#समावेश <linux/स्थिर.h>

#घोषणा PAGE_SHIFT   13

#घोषणा PAGE_SIZE    (_AC(1,UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK    (~(PAGE_SIZE-1))

/* Flushing क्रम D-cache alias handling is only needed अगर
 * the page size is smaller than 16K.
 */
#अगर PAGE_SHIFT < 14
#घोषणा DCACHE_ALIASING_POSSIBLE
#पूर्ण_अगर

#घोषणा HPAGE_SHIFT		23
#घोषणा REAL_HPAGE_SHIFT	22
#घोषणा HPAGE_16GB_SHIFT	34
#घोषणा HPAGE_2GB_SHIFT		31
#घोषणा HPAGE_256MB_SHIFT	28
#घोषणा HPAGE_64K_SHIFT		16
#घोषणा REAL_HPAGE_SIZE		(_AC(1,UL) << REAL_HPAGE_SHIFT)

#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
#घोषणा HPAGE_SIZE		(_AC(1,UL) << HPAGE_SHIFT)
#घोषणा HPAGE_MASK		(~(HPAGE_SIZE - 1UL))
#घोषणा HUGETLB_PAGE_ORDER	(HPAGE_SHIFT - PAGE_SHIFT)
#घोषणा HAVE_ARCH_HUGETLB_UNMAPPED_AREA
#घोषणा REAL_HPAGE_PER_HPAGE	(_AC(1,UL) << (HPAGE_SHIFT - REAL_HPAGE_SHIFT))
#घोषणा HUGE_MAX_HSTATE		5
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
काष्ठा pt_regs;
व्योम hugetlb_setup(काष्ठा pt_regs *regs);
#पूर्ण_अगर

#घोषणा WANT_PAGE_VIRTUAL

व्योम _clear_page(व्योम *page);
#घोषणा clear_page(X)	_clear_page((व्योम *)(X))
काष्ठा page;
व्योम clear_user_page(व्योम *addr, अचिन्हित दीर्घ vaddr, काष्ठा page *page);
#घोषणा copy_page(X,Y)	स_नकल((व्योम *)(X), (व्योम *)(Y), PAGE_SIZE)
व्योम copy_user_page(व्योम *to, व्योम *from, अचिन्हित दीर्घ vaddr, काष्ठा page *topage);
#घोषणा __HAVE_ARCH_COPY_USER_HIGHPAGE
काष्ठा vm_area_काष्ठा;
व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
			अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma);
#घोषणा __HAVE_ARCH_COPY_HIGHPAGE
व्योम copy_highpage(काष्ठा page *to, काष्ठा page *from);

/* Unlike sparc32, sparc64's parameter passing API is more
 * sane in that काष्ठाures which as small enough are passed
 * in रेजिस्टरs instead of on the stack.  Thus, setting
 * STRICT_MM_TYPECHECKS करोes not generate worse code so
 * let's enable it to get the type checking.
 */

#घोषणा STRICT_MM_TYPECHECKS

#अगर_घोषित STRICT_MM_TYPECHECKS
/* These are used to make use of C type-checking.. */
प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ iopte; पूर्ण iopte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pmd; पूर्ण pmd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pud; पूर्ण pud_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;

#घोषणा pte_val(x)	((x).pte)
#घोषणा iopte_val(x)	((x).iopte)
#घोषणा pmd_val(x)      ((x).pmd)
#घोषणा pud_val(x)      ((x).pud)
#घोषणा pgd_val(x)	((x).pgd)
#घोषणा pgprot_val(x)	((x).pgprot)

#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण )
#घोषणा __iopte(x)	((iopte_t) अणु (x) पूर्ण )
#घोषणा __pmd(x)        ((pmd_t) अणु (x) पूर्ण )
#घोषणा __pud(x)        ((pud_t) अणु (x) पूर्ण )
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण )
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण )

#अन्यथा
/* .. जबतक these make it easier on the compiler */
प्रकार अचिन्हित दीर्घ pte_t;
प्रकार अचिन्हित दीर्घ iopte_t;
प्रकार अचिन्हित दीर्घ pmd_t;
प्रकार अचिन्हित दीर्घ pud_t;
प्रकार अचिन्हित दीर्घ pgd_t;
प्रकार अचिन्हित दीर्घ pgprot_t;

#घोषणा pte_val(x)	(x)
#घोषणा iopte_val(x)	(x)
#घोषणा pmd_val(x)      (x)
#घोषणा pud_val(x)      (x)
#घोषणा pgd_val(x)	(x)
#घोषणा pgprot_val(x)	(x)

#घोषणा __pte(x)	(x)
#घोषणा __iopte(x)	(x)
#घोषणा __pmd(x)        (x)
#घोषणा __pud(x)        (x)
#घोषणा __pgd(x)	(x)
#घोषणा __pgprot(x)	(x)

#पूर्ण_अगर /* (STRICT_MM_TYPECHECKS) */

प्रकार pte_t *pgtable_t;

बाह्य अचिन्हित दीर्घ sparc64_va_hole_top;
बाह्य अचिन्हित दीर्घ sparc64_va_hole_bottom;

/* The next two defines specअगरy the actual exclusion region we
 * enक्रमce, wherein we use a 4GB red zone on each side of the VA hole.
 */
#घोषणा VA_EXCLUDE_START (sparc64_va_hole_bottom - (1UL << 32UL))
#घोषणा VA_EXCLUDE_END   (sparc64_va_hole_top + (1UL << 32UL))

#घोषणा TASK_UNMAPPED_BASE	(test_thपढ़ो_flag(TIF_32BIT) ? \
				 _AC(0x0000000070000000,UL) : \
				 VA_EXCLUDE_END)

#समावेश <यंत्र-generic/memory_model.h>

बाह्य अचिन्हित दीर्घ PAGE_OFFSET;

#पूर्ण_अगर /* !(__ASSEMBLY__) */

/* The maximum number of physical memory address bits we support.  The
 * largest value we can support is whatever "KPGD_SHIFT + KPTE_BITS"
 * evaluates to.
 */
#घोषणा MAX_PHYS_ADDRESS_BITS	53

#घोषणा ILOG2_4MB		22
#घोषणा ILOG2_256MB		28

#अगर_अघोषित __ASSEMBLY__

#घोषणा __pa(x)			((अचिन्हित दीर्घ)(x) - PAGE_OFFSET)
#घोषणा __va(x)			((व्योम *)((अचिन्हित दीर्घ) (x) + PAGE_OFFSET))

#घोषणा pfn_to_kaddr(pfn)	__va((pfn) << PAGE_SHIFT)

#घोषणा virt_to_page(kaddr)	pfn_to_page(__pa(kaddr)>>PAGE_SHIFT)

#घोषणा virt_addr_valid(kaddr)	pfn_valid(__pa(kaddr) >> PAGE_SHIFT)

#घोषणा virt_to_phys __pa
#घोषणा phys_to_virt __va

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* _SPARC64_PAGE_H */
