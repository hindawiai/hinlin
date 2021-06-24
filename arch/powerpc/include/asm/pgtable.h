<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_PGTABLE_H
#घोषणा _ASM_POWERPC_PGTABLE_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/mmdebug.h>
#समावेश <linux/mmzone.h>
#समावेश <यंत्र/processor.h>		/* For TASK_SIZE */
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/tlbflush.h>

काष्ठा mm_काष्ठा;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#अगर_घोषित CONFIG_PPC_BOOK3S
#समावेश <यंत्र/book3s/pgtable.h>
#अन्यथा
#समावेश <यंत्र/nohash/pgtable.h>
#पूर्ण_अगर /* !CONFIG_PPC_BOOK3S */

/* Note due to the way vm flags are laid out, the bits are XWR */
#घोषणा __P000	PAGE_NONE
#घोषणा __P001	PAGE_READONLY
#घोषणा __P010	PAGE_COPY
#घोषणा __P011	PAGE_COPY
#घोषणा __P100	PAGE_READONLY_X
#घोषणा __P101	PAGE_READONLY_X
#घोषणा __P110	PAGE_COPY_X
#घोषणा __P111	PAGE_COPY_X

#घोषणा __S000	PAGE_NONE
#घोषणा __S001	PAGE_READONLY
#घोषणा __S010	PAGE_SHARED
#घोषणा __S011	PAGE_SHARED
#घोषणा __S100	PAGE_READONLY_X
#घोषणा __S101	PAGE_READONLY_X
#घोषणा __S110	PAGE_SHARED_X
#घोषणा __S111	PAGE_SHARED_X

#अगर_अघोषित __ASSEMBLY__

/* Keep these as a macros to aव्योम include dependency mess */
#घोषणा pte_page(x)		pfn_to_page(pte_pfn(x))
#घोषणा mk_pte(page, pgprot)	pfn_pte(page_to_pfn(page), (pgprot))
/*
 * Select all bits except the pfn
 */
अटल अंतरभूत pgprot_t pte_pgprot(pte_t pte)
अणु
	अचिन्हित दीर्घ pte_flags;

	pte_flags = pte_val(pte) & ~PTE_RPN_MASK;
	वापस __pgprot(pte_flags);
पूर्ण

#अगर_अघोषित pmd_page_vaddr
अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस ((अचिन्हित दीर्घ)__va(pmd_val(pmd) & ~PMD_MASKED_BITS));
पूर्ण
#घोषणा pmd_page_vaddr pmd_page_vaddr
#पूर्ण_अगर
/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
बाह्य अचिन्हित दीर्घ empty_zero_page[];
#घोषणा ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))

बाह्य pgd_t swapper_pg_dir[];

बाह्य व्योम paging_init(व्योम);

बाह्य अचिन्हित दीर्घ ioremap_bot;

/*
 * kern_addr_valid is पूर्णांकended to indicate whether an address is a valid
 * kernel address.  Most 32-bit archs define it as always true (like this)
 * but most 64-bit archs actually perक्रमm a test.  What should we करो here?
 */
#घोषणा kern_addr_valid(addr)	(1)

#अगर_अघोषित CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा pmd_large(pmd)		0
#पूर्ण_अगर

/* can we use this in kvm */
अचिन्हित दीर्घ vदो_स्मृति_to_phys(व्योम *vदो_स्मृति_addr);

व्योम pgtable_cache_add(अचिन्हित पूर्णांक shअगरt);

pte_t *early_pte_alloc_kernel(pmd_t *pmdp, अचिन्हित दीर्घ va);

#अगर defined(CONFIG_STRICT_KERNEL_RWX) || defined(CONFIG_PPC32)
व्योम mark_iniपंचांगem_nx(व्योम);
#अन्यथा
अटल अंतरभूत व्योम mark_iniपंचांगem_nx(व्योम) अणु पूर्ण
#पूर्ण_अगर

/*
 * When used, PTE_FRAG_NR is defined in subarch pgtable.h
 * so we are sure it is included when arriving here.
 */
#अगर_घोषित PTE_FRAG_NR
अटल अंतरभूत व्योम *pte_frag_get(mm_context_t *ctx)
अणु
	वापस ctx->pte_frag;
पूर्ण

अटल अंतरभूत व्योम pte_frag_set(mm_context_t *ctx, व्योम *p)
अणु
	ctx->pte_frag = p;
पूर्ण
#अन्यथा
#घोषणा PTE_FRAG_NR		1
#घोषणा PTE_FRAG_SIZE_SHIFT	PAGE_SHIFT
#घोषणा PTE_FRAG_SIZE		(1UL << PTE_FRAG_SIZE_SHIFT)

अटल अंतरभूत व्योम *pte_frag_get(mm_context_t *ctx)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम pte_frag_set(mm_context_t *ctx, व्योम *p)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित pmd_is_leaf
#घोषणा pmd_is_leaf pmd_is_leaf
अटल अंतरभूत bool pmd_is_leaf(pmd_t pmd)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित pud_is_leaf
#घोषणा pud_is_leaf pud_is_leaf
अटल अंतरभूत bool pud_is_leaf(pud_t pud)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित p4d_is_leaf
#घोषणा p4d_is_leaf p4d_is_leaf
अटल अंतरभूत bool p4d_is_leaf(p4d_t p4d)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
#घोषणा is_ioremap_addr is_ioremap_addr
अटल अंतरभूत bool is_ioremap_addr(स्थिर व्योम *x)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)x;

	वापस addr >= IOREMAP_BASE && addr < IOREMAP_END;
पूर्ण

काष्ठा seq_file;
व्योम arch_report_meminfo(काष्ठा seq_file *m);
#पूर्ण_अगर /* CONFIG_PPC64 */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_PGTABLE_H */
