<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PGTABLE_H
#घोषणा _ASM_X86_PGTABLE_H

#समावेश <linux/mem_encrypt.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgtable_types.h>

/*
 * Macro to mark a page protection value as UC-
 */
#घोषणा pgprot_noncached(prot)						\
	((boot_cpu_data.x86 > 3)					\
	 ? (__pgprot(pgprot_val(prot) |					\
		     cachemode2protval(_PAGE_CACHE_MODE_UC_MINUS)))	\
	 : (prot))

/*
 * Macros to add or हटाओ encryption attribute
 */
#घोषणा pgprot_encrypted(prot)	__pgprot(__sme_set(pgprot_val(prot)))
#घोषणा pgprot_decrypted(prot)	__pgprot(__sme_clr(pgprot_val(prot)))

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/fpu/xstate.h>
#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र-generic/pgtable_uffd.h>

बाह्य pgd_t early_top_pgt[PTRS_PER_PGD];
bool __init __early_make_pgtable(अचिन्हित दीर्घ address, pmdval_t pmd);

व्योम ptdump_walk_pgd_level(काष्ठा seq_file *m, काष्ठा mm_काष्ठा *mm);
व्योम ptdump_walk_pgd_level_debugfs(काष्ठा seq_file *m, काष्ठा mm_काष्ठा *mm,
				   bool user);
व्योम ptdump_walk_pgd_level_checkwx(व्योम);
व्योम ptdump_walk_user_pgd_level_checkwx(व्योम);

#अगर_घोषित CONFIG_DEBUG_WX
#घोषणा debug_checkwx()		ptdump_walk_pgd_level_checkwx()
#घोषणा debug_checkwx_user()	ptdump_walk_user_pgd_level_checkwx()
#अन्यथा
#घोषणा debug_checkwx()		करो अणु पूर्ण जबतक (0)
#घोषणा debug_checkwx_user()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
बाह्य अचिन्हित दीर्घ empty_zero_page[PAGE_SIZE / माप(अचिन्हित दीर्घ)]
	__visible;
#घोषणा ZERO_PAGE(vaddr) ((व्योम)(vaddr),virt_to_page(empty_zero_page))

बाह्य spinlock_t pgd_lock;
बाह्य काष्ठा list_head pgd_list;

बाह्य काष्ठा mm_काष्ठा *pgd_page_get_mm(काष्ठा page *page);

बाह्य pmdval_t early_pmd_flags;

#अगर_घोषित CONFIG_PARAVIRT_XXL
#समावेश <यंत्र/paravirt.h>
#अन्यथा  /* !CONFIG_PARAVIRT_XXL */
#घोषणा set_pte(ptep, pte)		native_set_pte(ptep, pte)

#घोषणा set_pte_atomic(ptep, pte)					\
	native_set_pte_atomic(ptep, pte)

#घोषणा set_pmd(pmdp, pmd)		native_set_pmd(pmdp, pmd)

#अगर_अघोषित __PAGETABLE_P4D_FOLDED
#घोषणा set_pgd(pgdp, pgd)		native_set_pgd(pgdp, pgd)
#घोषणा pgd_clear(pgd)			(pgtable_l5_enabled() ? native_pgd_clear(pgd) : 0)
#पूर्ण_अगर

#अगर_अघोषित set_p4d
# define set_p4d(p4dp, p4d)		native_set_p4d(p4dp, p4d)
#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PUD_FOLDED
#घोषणा p4d_clear(p4d)			native_p4d_clear(p4d)
#पूर्ण_अगर

#अगर_अघोषित set_pud
# define set_pud(pudp, pud)		native_set_pud(pudp, pud)
#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PUD_FOLDED
#घोषणा pud_clear(pud)			native_pud_clear(pud)
#पूर्ण_अगर

#घोषणा pte_clear(mm, addr, ptep)	native_pte_clear(mm, addr, ptep)
#घोषणा pmd_clear(pmd)			native_pmd_clear(pmd)

#घोषणा pgd_val(x)	native_pgd_val(x)
#घोषणा __pgd(x)	native_make_pgd(x)

#अगर_अघोषित __PAGETABLE_P4D_FOLDED
#घोषणा p4d_val(x)	native_p4d_val(x)
#घोषणा __p4d(x)	native_make_p4d(x)
#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PUD_FOLDED
#घोषणा pud_val(x)	native_pud_val(x)
#घोषणा __pud(x)	native_make_pud(x)
#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
#घोषणा pmd_val(x)	native_pmd_val(x)
#घोषणा __pmd(x)	native_make_pmd(x)
#पूर्ण_अगर

#घोषणा pte_val(x)	native_pte_val(x)
#घोषणा __pte(x)	native_make_pte(x)

#घोषणा arch_end_context_चयन(prev)	करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर	/* CONFIG_PARAVIRT_XXL */

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)
अणु
	वापस pte_flags(pte) & _PAGE_सूचीTY;
पूर्ण


अटल अंतरभूत u32 पढ़ो_pkru(व्योम)
अणु
	अगर (boot_cpu_has(X86_FEATURE_OSPKE))
		वापस rdpkru();
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_pkru(u32 pkru)
अणु
	काष्ठा pkru_state *pk;

	अगर (!boot_cpu_has(X86_FEATURE_OSPKE))
		वापस;

	pk = get_xsave_addr(&current->thपढ़ो.fpu.state.xsave, XFEATURE_PKRU);

	/*
	 * The PKRU value in xstate needs to be in sync with the value that is
	 * written to the CPU. The FPU restore on वापस to userland would
	 * otherwise load the previous value again.
	 */
	fpregs_lock();
	अगर (pk)
		pk->pkru = pkru;
	__ग_लिखो_pkru(pkru);
	fpregs_unlock();
पूर्ण

अटल अंतरभूत पूर्णांक pte_young(pte_t pte)
अणु
	वापस pte_flags(pte) & _PAGE_ACCESSED;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_dirty(pmd_t pmd)
अणु
	वापस pmd_flags(pmd) & _PAGE_सूचीTY;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_young(pmd_t pmd)
अणु
	वापस pmd_flags(pmd) & _PAGE_ACCESSED;
पूर्ण

अटल अंतरभूत पूर्णांक pud_dirty(pud_t pud)
अणु
	वापस pud_flags(pud) & _PAGE_सूचीTY;
पूर्ण

अटल अंतरभूत पूर्णांक pud_young(pud_t pud)
अणु
	वापस pud_flags(pud) & _PAGE_ACCESSED;
पूर्ण

अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)
अणु
	वापस pte_flags(pte) & _PAGE_RW;
पूर्ण

अटल अंतरभूत पूर्णांक pte_huge(pte_t pte)
अणु
	वापस pte_flags(pte) & _PAGE_PSE;
पूर्ण

अटल अंतरभूत पूर्णांक pte_global(pte_t pte)
अणु
	वापस pte_flags(pte) & _PAGE_GLOBAL;
पूर्ण

अटल अंतरभूत पूर्णांक pte_exec(pte_t pte)
अणु
	वापस !(pte_flags(pte) & _PAGE_NX);
पूर्ण

अटल अंतरभूत पूर्णांक pte_special(pte_t pte)
अणु
	वापस pte_flags(pte) & _PAGE_SPECIAL;
पूर्ण

/* Entries that were set to PROT_NONE are inverted */

अटल अंतरभूत u64 protnone_mask(u64 val);

अटल अंतरभूत अचिन्हित दीर्घ pte_pfn(pte_t pte)
अणु
	phys_addr_t pfn = pte_val(pte);
	pfn ^= protnone_mask(pfn);
	वापस (pfn & PTE_PFN_MASK) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pmd_pfn(pmd_t pmd)
अणु
	phys_addr_t pfn = pmd_val(pmd);
	pfn ^= protnone_mask(pfn);
	वापस (pfn & pmd_pfn_mask(pmd)) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pud_pfn(pud_t pud)
अणु
	phys_addr_t pfn = pud_val(pud);
	pfn ^= protnone_mask(pfn);
	वापस (pfn & pud_pfn_mask(pud)) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ p4d_pfn(p4d_t p4d)
अणु
	वापस (p4d_val(p4d) & p4d_pfn_mask(p4d)) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pgd_pfn(pgd_t pgd)
अणु
	वापस (pgd_val(pgd) & PTE_PFN_MASK) >> PAGE_SHIFT;
पूर्ण

#घोषणा p4d_leaf	p4d_large
अटल अंतरभूत पूर्णांक p4d_large(p4d_t p4d)
अणु
	/* No 512 GiB pages yet */
	वापस 0;
पूर्ण

#घोषणा pte_page(pte)	pfn_to_page(pte_pfn(pte))

#घोषणा pmd_leaf	pmd_large
अटल अंतरभूत पूर्णांक pmd_large(pmd_t pte)
अणु
	वापस pmd_flags(pte) & _PAGE_PSE;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
/* NOTE: when predicate huge page, consider also pmd_devmap, or use pmd_large */
अटल अंतरभूत पूर्णांक pmd_trans_huge(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) & (_PAGE_PSE|_PAGE_DEVMAP)) == _PAGE_PSE;
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
अटल अंतरभूत पूर्णांक pud_trans_huge(pud_t pud)
अणु
	वापस (pud_val(pud) & (_PAGE_PSE|_PAGE_DEVMAP)) == _PAGE_PSE;
पूर्ण
#पूर्ण_अगर

#घोषणा has_transparent_hugepage has_transparent_hugepage
अटल अंतरभूत पूर्णांक has_transparent_hugepage(व्योम)
अणु
	वापस boot_cpu_has(X86_FEATURE_PSE);
पूर्ण

#अगर_घोषित CONFIG_ARCH_HAS_PTE_DEVMAP
अटल अंतरभूत पूर्णांक pmd_devmap(pmd_t pmd)
अणु
	वापस !!(pmd_val(pmd) & _PAGE_DEVMAP);
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
अटल अंतरभूत पूर्णांक pud_devmap(pud_t pud)
अणु
	वापस !!(pud_val(pud) & _PAGE_DEVMAP);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक pud_devmap(pud_t pud)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक pgd_devmap(pgd_t pgd)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

अटल अंतरभूत pte_t pte_set_flags(pte_t pte, pteval_t set)
अणु
	pteval_t v = native_pte_val(pte);

	वापस native_make_pte(v | set);
पूर्ण

अटल अंतरभूत pte_t pte_clear_flags(pte_t pte, pteval_t clear)
अणु
	pteval_t v = native_pte_val(pte);

	वापस native_make_pte(v & ~clear);
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_USERFAULTFD_WP
अटल अंतरभूत पूर्णांक pte_uffd_wp(pte_t pte)
अणु
	वापस pte_flags(pte) & _PAGE_UFFD_WP;
पूर्ण

अटल अंतरभूत pte_t pte_mkuffd_wp(pte_t pte)
अणु
	वापस pte_set_flags(pte, _PAGE_UFFD_WP);
पूर्ण

अटल अंतरभूत pte_t pte_clear_uffd_wp(pte_t pte)
अणु
	वापस pte_clear_flags(pte, _PAGE_UFFD_WP);
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_USERFAULTFD_WP */

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	वापस pte_clear_flags(pte, _PAGE_सूचीTY);
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	वापस pte_clear_flags(pte, _PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	वापस pte_clear_flags(pte, _PAGE_RW);
पूर्ण

अटल अंतरभूत pte_t pte_mkexec(pte_t pte)
अणु
	वापस pte_clear_flags(pte, _PAGE_NX);
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	वापस pte_set_flags(pte, _PAGE_सूचीTY | _PAGE_SOFT_सूचीTY);
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	वापस pte_set_flags(pte, _PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	वापस pte_set_flags(pte, _PAGE_RW);
पूर्ण

अटल अंतरभूत pte_t pte_mkhuge(pte_t pte)
अणु
	वापस pte_set_flags(pte, _PAGE_PSE);
पूर्ण

अटल अंतरभूत pte_t pte_clrhuge(pte_t pte)
अणु
	वापस pte_clear_flags(pte, _PAGE_PSE);
पूर्ण

अटल अंतरभूत pte_t pte_mkglobal(pte_t pte)
अणु
	वापस pte_set_flags(pte, _PAGE_GLOBAL);
पूर्ण

अटल अंतरभूत pte_t pte_clrglobal(pte_t pte)
अणु
	वापस pte_clear_flags(pte, _PAGE_GLOBAL);
पूर्ण

अटल अंतरभूत pte_t pte_mkspecial(pte_t pte)
अणु
	वापस pte_set_flags(pte, _PAGE_SPECIAL);
पूर्ण

अटल अंतरभूत pte_t pte_mkdevmap(pte_t pte)
अणु
	वापस pte_set_flags(pte, _PAGE_SPECIAL|_PAGE_DEVMAP);
पूर्ण

अटल अंतरभूत pmd_t pmd_set_flags(pmd_t pmd, pmdval_t set)
अणु
	pmdval_t v = native_pmd_val(pmd);

	वापस native_make_pmd(v | set);
पूर्ण

अटल अंतरभूत pmd_t pmd_clear_flags(pmd_t pmd, pmdval_t clear)
अणु
	pmdval_t v = native_pmd_val(pmd);

	वापस native_make_pmd(v & ~clear);
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_USERFAULTFD_WP
अटल अंतरभूत पूर्णांक pmd_uffd_wp(pmd_t pmd)
अणु
	वापस pmd_flags(pmd) & _PAGE_UFFD_WP;
पूर्ण

अटल अंतरभूत pmd_t pmd_mkuffd_wp(pmd_t pmd)
अणु
	वापस pmd_set_flags(pmd, _PAGE_UFFD_WP);
पूर्ण

अटल अंतरभूत pmd_t pmd_clear_uffd_wp(pmd_t pmd)
अणु
	वापस pmd_clear_flags(pmd, _PAGE_UFFD_WP);
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_USERFAULTFD_WP */

अटल अंतरभूत pmd_t pmd_mkold(pmd_t pmd)
अणु
	वापस pmd_clear_flags(pmd, _PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत pmd_t pmd_mkclean(pmd_t pmd)
अणु
	वापस pmd_clear_flags(pmd, _PAGE_सूचीTY);
पूर्ण

अटल अंतरभूत pmd_t pmd_wrprotect(pmd_t pmd)
अणु
	वापस pmd_clear_flags(pmd, _PAGE_RW);
पूर्ण

अटल अंतरभूत pmd_t pmd_सूची_गढ़ोty(pmd_t pmd)
अणु
	वापस pmd_set_flags(pmd, _PAGE_सूचीTY | _PAGE_SOFT_सूचीTY);
पूर्ण

अटल अंतरभूत pmd_t pmd_mkdevmap(pmd_t pmd)
अणु
	वापस pmd_set_flags(pmd, _PAGE_DEVMAP);
पूर्ण

अटल अंतरभूत pmd_t pmd_mkhuge(pmd_t pmd)
अणु
	वापस pmd_set_flags(pmd, _PAGE_PSE);
पूर्ण

अटल अंतरभूत pmd_t pmd_mkyoung(pmd_t pmd)
अणु
	वापस pmd_set_flags(pmd, _PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत pmd_t pmd_mkग_लिखो(pmd_t pmd)
अणु
	वापस pmd_set_flags(pmd, _PAGE_RW);
पूर्ण

अटल अंतरभूत pud_t pud_set_flags(pud_t pud, pudval_t set)
अणु
	pudval_t v = native_pud_val(pud);

	वापस native_make_pud(v | set);
पूर्ण

अटल अंतरभूत pud_t pud_clear_flags(pud_t pud, pudval_t clear)
अणु
	pudval_t v = native_pud_val(pud);

	वापस native_make_pud(v & ~clear);
पूर्ण

अटल अंतरभूत pud_t pud_mkold(pud_t pud)
अणु
	वापस pud_clear_flags(pud, _PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत pud_t pud_mkclean(pud_t pud)
अणु
	वापस pud_clear_flags(pud, _PAGE_सूचीTY);
पूर्ण

अटल अंतरभूत pud_t pud_wrprotect(pud_t pud)
अणु
	वापस pud_clear_flags(pud, _PAGE_RW);
पूर्ण

अटल अंतरभूत pud_t pud_सूची_गढ़ोty(pud_t pud)
अणु
	वापस pud_set_flags(pud, _PAGE_सूचीTY | _PAGE_SOFT_सूचीTY);
पूर्ण

अटल अंतरभूत pud_t pud_mkdevmap(pud_t pud)
अणु
	वापस pud_set_flags(pud, _PAGE_DEVMAP);
पूर्ण

अटल अंतरभूत pud_t pud_mkhuge(pud_t pud)
अणु
	वापस pud_set_flags(pud, _PAGE_PSE);
पूर्ण

अटल अंतरभूत pud_t pud_mkyoung(pud_t pud)
अणु
	वापस pud_set_flags(pud, _PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत pud_t pud_mkग_लिखो(pud_t pud)
अणु
	वापस pud_set_flags(pud, _PAGE_RW);
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_SOFT_सूचीTY
अटल अंतरभूत पूर्णांक pte_soft_dirty(pte_t pte)
अणु
	वापस pte_flags(pte) & _PAGE_SOFT_सूचीTY;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_soft_dirty(pmd_t pmd)
अणु
	वापस pmd_flags(pmd) & _PAGE_SOFT_सूचीTY;
पूर्ण

अटल अंतरभूत पूर्णांक pud_soft_dirty(pud_t pud)
अणु
	वापस pud_flags(pud) & _PAGE_SOFT_सूचीTY;
पूर्ण

अटल अंतरभूत pte_t pte_mksoft_dirty(pte_t pte)
अणु
	वापस pte_set_flags(pte, _PAGE_SOFT_सूचीTY);
पूर्ण

अटल अंतरभूत pmd_t pmd_mksoft_dirty(pmd_t pmd)
अणु
	वापस pmd_set_flags(pmd, _PAGE_SOFT_सूचीTY);
पूर्ण

अटल अंतरभूत pud_t pud_mksoft_dirty(pud_t pud)
अणु
	वापस pud_set_flags(pud, _PAGE_SOFT_सूचीTY);
पूर्ण

अटल अंतरभूत pte_t pte_clear_soft_dirty(pte_t pte)
अणु
	वापस pte_clear_flags(pte, _PAGE_SOFT_सूचीTY);
पूर्ण

अटल अंतरभूत pmd_t pmd_clear_soft_dirty(pmd_t pmd)
अणु
	वापस pmd_clear_flags(pmd, _PAGE_SOFT_सूचीTY);
पूर्ण

अटल अंतरभूत pud_t pud_clear_soft_dirty(pud_t pud)
अणु
	वापस pud_clear_flags(pud, _PAGE_SOFT_सूचीTY);
पूर्ण

#पूर्ण_अगर /* CONFIG_HAVE_ARCH_SOFT_सूचीTY */

/*
 * Mask out unsupported bits in a present pgprot.  Non-present pgprots
 * can use those bits क्रम other purposes, so leave them be.
 */
अटल अंतरभूत pgprotval_t massage_pgprot(pgprot_t pgprot)
अणु
	pgprotval_t protval = pgprot_val(pgprot);

	अगर (protval & _PAGE_PRESENT)
		protval &= __supported_pte_mask;

	वापस protval;
पूर्ण

अटल अंतरभूत pgprotval_t check_pgprot(pgprot_t pgprot)
अणु
	pgprotval_t massaged_val = massage_pgprot(pgprot);

	/* mmdebug.h can not be included here because of dependencies */
#अगर_घोषित CONFIG_DEBUG_VM
	WARN_ONCE(pgprot_val(pgprot) != massaged_val,
		  "attempted to set unsupported pgprot: %016llx "
		  "bits: %016llx supported: %016llx\n",
		  (u64)pgprot_val(pgprot),
		  (u64)pgprot_val(pgprot) ^ massaged_val,
		  (u64)__supported_pte_mask);
#पूर्ण_अगर

	वापस massaged_val;
पूर्ण

अटल अंतरभूत pte_t pfn_pte(अचिन्हित दीर्घ page_nr, pgprot_t pgprot)
अणु
	phys_addr_t pfn = (phys_addr_t)page_nr << PAGE_SHIFT;
	pfn ^= protnone_mask(pgprot_val(pgprot));
	pfn &= PTE_PFN_MASK;
	वापस __pte(pfn | check_pgprot(pgprot));
पूर्ण

अटल अंतरभूत pmd_t pfn_pmd(अचिन्हित दीर्घ page_nr, pgprot_t pgprot)
अणु
	phys_addr_t pfn = (phys_addr_t)page_nr << PAGE_SHIFT;
	pfn ^= protnone_mask(pgprot_val(pgprot));
	pfn &= PHYSICAL_PMD_PAGE_MASK;
	वापस __pmd(pfn | check_pgprot(pgprot));
पूर्ण

अटल अंतरभूत pud_t pfn_pud(अचिन्हित दीर्घ page_nr, pgprot_t pgprot)
अणु
	phys_addr_t pfn = (phys_addr_t)page_nr << PAGE_SHIFT;
	pfn ^= protnone_mask(pgprot_val(pgprot));
	pfn &= PHYSICAL_PUD_PAGE_MASK;
	वापस __pud(pfn | check_pgprot(pgprot));
पूर्ण

अटल अंतरभूत pmd_t pmd_mkinvalid(pmd_t pmd)
अणु
	वापस pfn_pmd(pmd_pfn(pmd),
		      __pgprot(pmd_flags(pmd) & ~(_PAGE_PRESENT|_PAGE_PROTNONE)));
पूर्ण

अटल अंतरभूत u64 flip_protnone_guard(u64 oldval, u64 val, u64 mask);

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	pteval_t val = pte_val(pte), oldval = val;

	/*
	 * Chop off the NX bit (अगर present), and add the NX portion of
	 * the newprot (अगर present):
	 */
	val &= _PAGE_CHG_MASK;
	val |= check_pgprot(newprot) & ~_PAGE_CHG_MASK;
	val = flip_protnone_guard(oldval, val, PTE_PFN_MASK);
	वापस __pte(val);
पूर्ण

अटल अंतरभूत pmd_t pmd_modअगरy(pmd_t pmd, pgprot_t newprot)
अणु
	pmdval_t val = pmd_val(pmd), oldval = val;

	val &= _HPAGE_CHG_MASK;
	val |= check_pgprot(newprot) & ~_HPAGE_CHG_MASK;
	val = flip_protnone_guard(oldval, val, PHYSICAL_PMD_PAGE_MASK);
	वापस __pmd(val);
पूर्ण

/*
 * mprotect needs to preserve PAT and encryption bits when updating
 * vm_page_prot
 */
#घोषणा pgprot_modअगरy pgprot_modअगरy
अटल अंतरभूत pgprot_t pgprot_modअगरy(pgprot_t oldprot, pgprot_t newprot)
अणु
	pgprotval_t preservebits = pgprot_val(oldprot) & _PAGE_CHG_MASK;
	pgprotval_t addbits = pgprot_val(newprot) & ~_PAGE_CHG_MASK;
	वापस __pgprot(preservebits | addbits);
पूर्ण

#घोषणा pte_pgprot(x) __pgprot(pte_flags(x))
#घोषणा pmd_pgprot(x) __pgprot(pmd_flags(x))
#घोषणा pud_pgprot(x) __pgprot(pud_flags(x))
#घोषणा p4d_pgprot(x) __pgprot(p4d_flags(x))

#घोषणा canon_pgprot(p) __pgprot(massage_pgprot(p))

अटल अंतरभूत pgprot_t arch_filter_pgprot(pgprot_t prot)
अणु
	वापस canon_pgprot(prot);
पूर्ण

अटल अंतरभूत पूर्णांक is_new_memtype_allowed(u64 paddr, अचिन्हित दीर्घ size,
					 क्रमागत page_cache_mode pcm,
					 क्रमागत page_cache_mode new_pcm)
अणु
	/*
	 * PAT type is always WB क्रम untracked ranges, so no need to check.
	 */
	अगर (x86_platक्रमm.is_untracked_pat_range(paddr, paddr + size))
		वापस 1;

	/*
	 * Certain new memtypes are not allowed with certain
	 * requested memtype:
	 * - request is uncached, वापस cannot be ग_लिखो-back
	 * - request is ग_लिखो-combine, वापस cannot be ग_लिखो-back
	 * - request is ग_लिखो-through, वापस cannot be ग_लिखो-back
	 * - request is ग_लिखो-through, वापस cannot be ग_लिखो-combine
	 */
	अगर ((pcm == _PAGE_CACHE_MODE_UC_MINUS &&
	     new_pcm == _PAGE_CACHE_MODE_WB) ||
	    (pcm == _PAGE_CACHE_MODE_WC &&
	     new_pcm == _PAGE_CACHE_MODE_WB) ||
	    (pcm == _PAGE_CACHE_MODE_WT &&
	     new_pcm == _PAGE_CACHE_MODE_WB) ||
	    (pcm == _PAGE_CACHE_MODE_WT &&
	     new_pcm == _PAGE_CACHE_MODE_WC)) अणु
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

pmd_t *populate_extra_pmd(अचिन्हित दीर्घ vaddr);
pte_t *populate_extra_pte(अचिन्हित दीर्घ vaddr);

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
pgd_t __pti_set_user_pgtbl(pgd_t *pgdp, pgd_t pgd);

/*
 * Take a PGD location (pgdp) and a pgd value that needs to be set there.
 * Populates the user and वापसs the resulting PGD that must be set in
 * the kernel copy of the page tables.
 */
अटल अंतरभूत pgd_t pti_set_user_pgtbl(pgd_t *pgdp, pgd_t pgd)
अणु
	अगर (!अटल_cpu_has(X86_FEATURE_PTI))
		वापस pgd;
	वापस __pti_set_user_pgtbl(pgdp, pgd);
पूर्ण
#अन्यथा   /* CONFIG_PAGE_TABLE_ISOLATION */
अटल अंतरभूत pgd_t pti_set_user_pgtbl(pgd_t *pgdp, pgd_t pgd)
अणु
	वापस pgd;
पूर्ण
#पूर्ण_अगर  /* CONFIG_PAGE_TABLE_ISOLATION */

#पूर्ण_अगर	/* __ASSEMBLY__ */


#अगर_घोषित CONFIG_X86_32
# include <यंत्र/pgtable_32.h>
#अन्यथा
# include <यंत्र/pgtable_64.h>
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/mm_types.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/log2.h>
#समावेश <यंत्र/fixmap.h>

अटल अंतरभूत पूर्णांक pte_none(pte_t pte)
अणु
	वापस !(pte.pte & ~(_PAGE_KNL_ERRATUM_MASK));
पूर्ण

#घोषणा __HAVE_ARCH_PTE_SAME
अटल अंतरभूत पूर्णांक pte_same(pte_t a, pte_t b)
अणु
	वापस a.pte == b.pte;
पूर्ण

अटल अंतरभूत पूर्णांक pte_present(pte_t a)
अणु
	वापस pte_flags(a) & (_PAGE_PRESENT | _PAGE_PROTNONE);
पूर्ण

#अगर_घोषित CONFIG_ARCH_HAS_PTE_DEVMAP
अटल अंतरभूत पूर्णांक pte_devmap(pte_t a)
अणु
	वापस (pte_flags(a) & _PAGE_DEVMAP) == _PAGE_DEVMAP;
पूर्ण
#पूर्ण_अगर

#घोषणा pte_accessible pte_accessible
अटल अंतरभूत bool pte_accessible(काष्ठा mm_काष्ठा *mm, pte_t a)
अणु
	अगर (pte_flags(a) & _PAGE_PRESENT)
		वापस true;

	अगर ((pte_flags(a) & _PAGE_PROTNONE) &&
			mm_tlb_flush_pending(mm))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_present(pmd_t pmd)
अणु
	/*
	 * Checking क्रम _PAGE_PSE is needed too because
	 * split_huge_page will temporarily clear the present bit (but
	 * the _PAGE_PSE flag will reमुख्य set at all बार जबतक the
	 * _PAGE_PRESENT bit is clear).
	 */
	वापस pmd_flags(pmd) & (_PAGE_PRESENT | _PAGE_PROTNONE | _PAGE_PSE);
पूर्ण

#अगर_घोषित CONFIG_NUMA_BALANCING
/*
 * These work without NUMA balancing but the kernel करोes not care. See the
 * comment in include/linux/pgtable.h
 */
अटल अंतरभूत पूर्णांक pte_protnone(pte_t pte)
अणु
	वापस (pte_flags(pte) & (_PAGE_PROTNONE | _PAGE_PRESENT))
		== _PAGE_PROTNONE;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_protnone(pmd_t pmd)
अणु
	वापस (pmd_flags(pmd) & (_PAGE_PROTNONE | _PAGE_PRESENT))
		== _PAGE_PROTNONE;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

अटल अंतरभूत पूर्णांक pmd_none(pmd_t pmd)
अणु
	/* Only check low word on 32-bit platक्रमms, since it might be
	   out of sync with upper half. */
	अचिन्हित दीर्घ val = native_pmd_val(pmd);
	वापस (val & ~_PAGE_KNL_ERRATUM_MASK) == 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस (अचिन्हित दीर्घ)__va(pmd_val(pmd) & pmd_pfn_mask(pmd));
पूर्ण

/*
 * Currently stuck as a macro due to indirect क्रमward reference to
 * linux/mmzone.h's __section_mem_map_addr() definition:
 */
#घोषणा pmd_page(pmd)	pfn_to_page(pmd_pfn(pmd))

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 *
 * (Currently stuck as a macro because of indirect क्रमward reference
 * to linux/mm.h:page_to_nid())
 */
#घोषणा mk_pte(page, pgprot)   pfn_pte(page_to_pfn(page), (pgprot))

अटल अंतरभूत पूर्णांक pmd_bad(pmd_t pmd)
अणु
	वापस (pmd_flags(pmd) & ~_PAGE_USER) != _KERNPG_TABLE;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pages_to_mb(अचिन्हित दीर्घ npg)
अणु
	वापस npg >> (20 - PAGE_SHIFT);
पूर्ण

#अगर CONFIG_PGTABLE_LEVELS > 2
अटल अंतरभूत पूर्णांक pud_none(pud_t pud)
अणु
	वापस (native_pud_val(pud) & ~(_PAGE_KNL_ERRATUM_MASK)) == 0;
पूर्ण

अटल अंतरभूत पूर्णांक pud_present(pud_t pud)
अणु
	वापस pud_flags(pud) & _PAGE_PRESENT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pud_page_vaddr(pud_t pud)
अणु
	वापस (अचिन्हित दीर्घ)__va(pud_val(pud) & pud_pfn_mask(pud));
पूर्ण

/*
 * Currently stuck as a macro due to indirect क्रमward reference to
 * linux/mmzone.h's __section_mem_map_addr() definition:
 */
#घोषणा pud_page(pud)	pfn_to_page(pud_pfn(pud))

#घोषणा pud_leaf	pud_large
अटल अंतरभूत पूर्णांक pud_large(pud_t pud)
अणु
	वापस (pud_val(pud) & (_PAGE_PSE | _PAGE_PRESENT)) ==
		(_PAGE_PSE | _PAGE_PRESENT);
पूर्ण

अटल अंतरभूत पूर्णांक pud_bad(pud_t pud)
अणु
	वापस (pud_flags(pud) & ~(_KERNPG_TABLE | _PAGE_USER)) != 0;
पूर्ण
#अन्यथा
#घोषणा pud_leaf	pud_large
अटल अंतरभूत पूर्णांक pud_large(pud_t pud)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_PGTABLE_LEVELS > 2 */

#अगर CONFIG_PGTABLE_LEVELS > 3
अटल अंतरभूत पूर्णांक p4d_none(p4d_t p4d)
अणु
	वापस (native_p4d_val(p4d) & ~(_PAGE_KNL_ERRATUM_MASK)) == 0;
पूर्ण

अटल अंतरभूत पूर्णांक p4d_present(p4d_t p4d)
अणु
	वापस p4d_flags(p4d) & _PAGE_PRESENT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ p4d_page_vaddr(p4d_t p4d)
अणु
	वापस (अचिन्हित दीर्घ)__va(p4d_val(p4d) & p4d_pfn_mask(p4d));
पूर्ण

/*
 * Currently stuck as a macro due to indirect क्रमward reference to
 * linux/mmzone.h's __section_mem_map_addr() definition:
 */
#घोषणा p4d_page(p4d)	pfn_to_page(p4d_pfn(p4d))

अटल अंतरभूत पूर्णांक p4d_bad(p4d_t p4d)
अणु
	अचिन्हित दीर्घ ignore_flags = _KERNPG_TABLE | _PAGE_USER;

	अगर (IS_ENABLED(CONFIG_PAGE_TABLE_ISOLATION))
		ignore_flags |= _PAGE_NX;

	वापस (p4d_flags(p4d) & ~ignore_flags) != 0;
पूर्ण
#पूर्ण_अगर  /* CONFIG_PGTABLE_LEVELS > 3 */

अटल अंतरभूत अचिन्हित दीर्घ p4d_index(अचिन्हित दीर्घ address)
अणु
	वापस (address >> P4D_SHIFT) & (PTRS_PER_P4D - 1);
पूर्ण

#अगर CONFIG_PGTABLE_LEVELS > 4
अटल अंतरभूत पूर्णांक pgd_present(pgd_t pgd)
अणु
	अगर (!pgtable_l5_enabled())
		वापस 1;
	वापस pgd_flags(pgd) & _PAGE_PRESENT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pgd_page_vaddr(pgd_t pgd)
अणु
	वापस (अचिन्हित दीर्घ)__va((अचिन्हित दीर्घ)pgd_val(pgd) & PTE_PFN_MASK);
पूर्ण

/*
 * Currently stuck as a macro due to indirect क्रमward reference to
 * linux/mmzone.h's __section_mem_map_addr() definition:
 */
#घोषणा pgd_page(pgd)	pfn_to_page(pgd_pfn(pgd))

/* to find an entry in a page-table-directory. */
अटल अंतरभूत p4d_t *p4d_offset(pgd_t *pgd, अचिन्हित दीर्घ address)
अणु
	अगर (!pgtable_l5_enabled())
		वापस (p4d_t *)pgd;
	वापस (p4d_t *)pgd_page_vaddr(*pgd) + p4d_index(address);
पूर्ण

अटल अंतरभूत पूर्णांक pgd_bad(pgd_t pgd)
अणु
	अचिन्हित दीर्घ ignore_flags = _PAGE_USER;

	अगर (!pgtable_l5_enabled())
		वापस 0;

	अगर (IS_ENABLED(CONFIG_PAGE_TABLE_ISOLATION))
		ignore_flags |= _PAGE_NX;

	वापस (pgd_flags(pgd) & ~ignore_flags) != _KERNPG_TABLE;
पूर्ण

अटल अंतरभूत पूर्णांक pgd_none(pgd_t pgd)
अणु
	अगर (!pgtable_l5_enabled())
		वापस 0;
	/*
	 * There is no need to करो a workaround क्रम the KNL stray
	 * A/D bit erratum here.  PGDs only poपूर्णांक to page tables
	 * except on 32-bit non-PAE which is not supported on
	 * KNL.
	 */
	वापस !native_pgd_val(pgd);
पूर्ण
#पूर्ण_अगर	/* CONFIG_PGTABLE_LEVELS > 4 */

#पूर्ण_अगर	/* __ASSEMBLY__ */

#घोषणा KERNEL_PGD_BOUNDARY	pgd_index(PAGE_OFFSET)
#घोषणा KERNEL_PGD_PTRS		(PTRS_PER_PGD - KERNEL_PGD_BOUNDARY)

#अगर_अघोषित __ASSEMBLY__

बाह्य पूर्णांक direct_gbpages;
व्योम init_mem_mapping(व्योम);
व्योम early_alloc_pgt_buf(व्योम);
बाह्य व्योम memblock_find_dma_reserve(व्योम);
व्योम __init poking_init(व्योम);
अचिन्हित दीर्घ init_memory_mapping(अचिन्हित दीर्घ start,
				  अचिन्हित दीर्घ end, pgprot_t prot);

#अगर_घोषित CONFIG_X86_64
बाह्य pgd_t trampoline_pgd_entry;
#पूर्ण_अगर

/* local pte updates need not use xchg क्रम locking */
अटल अंतरभूत pte_t native_local_ptep_get_and_clear(pte_t *ptep)
अणु
	pte_t res = *ptep;

	/* Pure native function needs no input क्रम mm, addr */
	native_pte_clear(शून्य, 0, ptep);
	वापस res;
पूर्ण

अटल अंतरभूत pmd_t native_local_pmdp_get_and_clear(pmd_t *pmdp)
अणु
	pmd_t res = *pmdp;

	native_pmd_clear(pmdp);
	वापस res;
पूर्ण

अटल अंतरभूत pud_t native_local_pudp_get_and_clear(pud_t *pudp)
अणु
	pud_t res = *pudp;

	native_pud_clear(pudp);
	वापस res;
पूर्ण

अटल अंतरभूत व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *ptep, pte_t pte)
अणु
	set_pte(ptep, pte);
पूर्ण

अटल अंतरभूत व्योम set_pmd_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pmd_t *pmdp, pmd_t pmd)
अणु
	set_pmd(pmdp, pmd);
पूर्ण

अटल अंतरभूत व्योम set_pud_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pud_t *pudp, pud_t pud)
अणु
	native_set_pud(pudp, pud);
पूर्ण

/*
 * We only update the dirty/accessed state अगर we set
 * the dirty bit by hand in the kernel, since the hardware
 * will करो the accessed bit क्रम us, and we करोn't want to
 * race with other CPU's that might be updating the dirty
 * bit at the same समय.
 */
काष्ठा vm_area_काष्ठा;

#घोषणा  __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
बाह्य पूर्णांक ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ address, pte_t *ptep,
				 pte_t entry, पूर्णांक dirty);

#घोषणा __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
बाह्य पूर्णांक ptep_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ addr, pte_t *ptep);

#घोषणा __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
बाह्य पूर्णांक ptep_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ address, pte_t *ptep);

#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t ptep_get_and_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				       pte_t *ptep)
अणु
	pte_t pte = native_ptep_get_and_clear(ptep);
	वापस pte;
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR_FULL
अटल अंतरभूत pte_t ptep_get_and_clear_full(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ addr, pte_t *ptep,
					    पूर्णांक full)
अणु
	pte_t pte;
	अगर (full) अणु
		/*
		 * Full address deकाष्ठाion in progress; paravirt करोes not
		 * care about updates and native needs no locking
		 */
		pte = native_local_ptep_get_and_clear(ptep);
	पूर्ण अन्यथा अणु
		pte = ptep_get_and_clear(mm, addr, ptep);
	पूर्ण
	वापस pte;
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	clear_bit(_PAGE_BIT_RW, (अचिन्हित दीर्घ *)&ptep->pte);
पूर्ण

#घोषणा flush_tlb_fix_spurious_fault(vma, address) करो अणु पूर्ण जबतक (0)

#घोषणा mk_pmd(page, pgprot)   pfn_pmd(page_to_pfn(page), (pgprot))

#घोषणा  __HAVE_ARCH_PMDP_SET_ACCESS_FLAGS
बाह्य पूर्णांक pmdp_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ address, pmd_t *pmdp,
				 pmd_t entry, पूर्णांक dirty);
बाह्य पूर्णांक pudp_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ address, pud_t *pudp,
				 pud_t entry, पूर्णांक dirty);

#घोषणा __HAVE_ARCH_PMDP_TEST_AND_CLEAR_YOUNG
बाह्य पूर्णांक pmdp_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ addr, pmd_t *pmdp);
बाह्य पूर्णांक pudp_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ addr, pud_t *pudp);

#घोषणा __HAVE_ARCH_PMDP_CLEAR_YOUNG_FLUSH
बाह्य पूर्णांक pmdp_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ address, pmd_t *pmdp);


#घोषणा pmd_ग_लिखो pmd_ग_लिखो
अटल अंतरभूत पूर्णांक pmd_ग_लिखो(pmd_t pmd)
अणु
	वापस pmd_flags(pmd) & _PAGE_RW;
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR
अटल अंतरभूत pmd_t pmdp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				       pmd_t *pmdp)
अणु
	वापस native_pmdp_get_and_clear(pmdp);
पूर्ण

#घोषणा __HAVE_ARCH_PUDP_HUGE_GET_AND_CLEAR
अटल अंतरभूत pud_t pudp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm,
					अचिन्हित दीर्घ addr, pud_t *pudp)
अणु
	वापस native_pudp_get_and_clear(pudp);
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_SET_WRPROTECT
अटल अंतरभूत व्योम pmdp_set_wrprotect(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	clear_bit(_PAGE_BIT_RW, (अचिन्हित दीर्घ *)pmdp);
पूर्ण

#घोषणा pud_ग_लिखो pud_ग_लिखो
अटल अंतरभूत पूर्णांक pud_ग_लिखो(pud_t pud)
अणु
	वापस pud_flags(pud) & _PAGE_RW;
पूर्ण

#अगर_अघोषित pmdp_establish
#घोषणा pmdp_establish pmdp_establish
अटल अंतरभूत pmd_t pmdp_establish(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, pmd_t *pmdp, pmd_t pmd)
अणु
	अगर (IS_ENABLED(CONFIG_SMP)) अणु
		वापस xchg(pmdp, pmd);
	पूर्ण अन्यथा अणु
		pmd_t old = *pmdp;
		WRITE_ONCE(*pmdp, pmd);
		वापस old;
	पूर्ण
पूर्ण
#पूर्ण_अगर
/*
 * Page table pages are page-aligned.  The lower half of the top
 * level is used क्रम userspace and the top half क्रम the kernel.
 *
 * Returns true क्रम parts of the PGD that map userspace and
 * false क्रम the parts that map the kernel.
 */
अटल अंतरभूत bool pgdp_maps_userspace(व्योम *__ptr)
अणु
	अचिन्हित दीर्घ ptr = (अचिन्हित दीर्घ)__ptr;

	वापस (((ptr & ~PAGE_MASK) / माप(pgd_t)) < PGD_KERNEL_START);
पूर्ण

#घोषणा pgd_leaf	pgd_large
अटल अंतरभूत पूर्णांक pgd_large(pgd_t pgd) अणु वापस 0; पूर्ण

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
/*
 * All top-level PAGE_TABLE_ISOLATION page tables are order-1 pages
 * (8k-aligned and 8k in size).  The kernel one is at the beginning 4k and
 * the user one is in the last 4k.  To चयन between them, you
 * just need to flip the 12th bit in their addresses.
 */
#घोषणा PTI_PGTABLE_SWITCH_BIT	PAGE_SHIFT

/*
 * This generates better code than the अंतरभूत assembly in
 * __set_bit().
 */
अटल अंतरभूत व्योम *ptr_set_bit(व्योम *ptr, पूर्णांक bit)
अणु
	अचिन्हित दीर्घ __ptr = (अचिन्हित दीर्घ)ptr;

	__ptr |= BIT(bit);
	वापस (व्योम *)__ptr;
पूर्ण
अटल अंतरभूत व्योम *ptr_clear_bit(व्योम *ptr, पूर्णांक bit)
अणु
	अचिन्हित दीर्घ __ptr = (अचिन्हित दीर्घ)ptr;

	__ptr &= ~BIT(bit);
	वापस (व्योम *)__ptr;
पूर्ण

अटल अंतरभूत pgd_t *kernel_to_user_pgdp(pgd_t *pgdp)
अणु
	वापस ptr_set_bit(pgdp, PTI_PGTABLE_SWITCH_BIT);
पूर्ण

अटल अंतरभूत pgd_t *user_to_kernel_pgdp(pgd_t *pgdp)
अणु
	वापस ptr_clear_bit(pgdp, PTI_PGTABLE_SWITCH_BIT);
पूर्ण

अटल अंतरभूत p4d_t *kernel_to_user_p4dp(p4d_t *p4dp)
अणु
	वापस ptr_set_bit(p4dp, PTI_PGTABLE_SWITCH_BIT);
पूर्ण

अटल अंतरभूत p4d_t *user_to_kernel_p4dp(p4d_t *p4dp)
अणु
	वापस ptr_clear_bit(p4dp, PTI_PGTABLE_SWITCH_BIT);
पूर्ण
#पूर्ण_अगर /* CONFIG_PAGE_TABLE_ISOLATION */

/*
 * clone_pgd_range(pgd_t *dst, pgd_t *src, पूर्णांक count);
 *
 *  dst - poपूर्णांकer to pgd range anywhere on a pgd page
 *  src - ""
 *  count - the number of pgds to copy.
 *
 * dst and src can be on the same page, but the range must not overlap,
 * and must not cross a page boundary.
 */
अटल अंतरभूत व्योम clone_pgd_range(pgd_t *dst, pgd_t *src, पूर्णांक count)
अणु
	स_नकल(dst, src, count * माप(pgd_t));
#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
	अगर (!अटल_cpu_has(X86_FEATURE_PTI))
		वापस;
	/* Clone the user space pgd as well */
	स_नकल(kernel_to_user_pgdp(dst), kernel_to_user_pgdp(src),
	       count * माप(pgd_t));
#पूर्ण_अगर
पूर्ण

#घोषणा PTE_SHIFT ilog2(PTRS_PER_PTE)
अटल अंतरभूत पूर्णांक page_level_shअगरt(क्रमागत pg_level level)
अणु
	वापस (PAGE_SHIFT - PTE_SHIFT) + level * PTE_SHIFT;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ page_level_size(क्रमागत pg_level level)
अणु
	वापस 1UL << page_level_shअगरt(level);
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ page_level_mask(क्रमागत pg_level level)
अणु
	वापस ~(page_level_size(level) - 1);
पूर्ण

/*
 * The x86 करोesn't have any बाह्यal MMU info: the kernel page
 * tables contain all the necessary inक्रमmation.
 */
अटल अंतरभूत व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
पूर्ण
अटल अंतरभूत व्योम update_mmu_cache_pmd(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pmd_t *pmd)
अणु
पूर्ण
अटल अंतरभूत व्योम update_mmu_cache_pud(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pud_t *pud)
अणु
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_SOFT_सूचीTY
अटल अंतरभूत pte_t pte_swp_mksoft_dirty(pte_t pte)
अणु
	वापस pte_set_flags(pte, _PAGE_SWP_SOFT_सूचीTY);
पूर्ण

अटल अंतरभूत पूर्णांक pte_swp_soft_dirty(pte_t pte)
अणु
	वापस pte_flags(pte) & _PAGE_SWP_SOFT_सूचीTY;
पूर्ण

अटल अंतरभूत pte_t pte_swp_clear_soft_dirty(pte_t pte)
अणु
	वापस pte_clear_flags(pte, _PAGE_SWP_SOFT_सूचीTY);
पूर्ण

#अगर_घोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
अटल अंतरभूत pmd_t pmd_swp_mksoft_dirty(pmd_t pmd)
अणु
	वापस pmd_set_flags(pmd, _PAGE_SWP_SOFT_सूचीTY);
पूर्ण

अटल अंतरभूत पूर्णांक pmd_swp_soft_dirty(pmd_t pmd)
अणु
	वापस pmd_flags(pmd) & _PAGE_SWP_SOFT_सूचीTY;
पूर्ण

अटल अंतरभूत pmd_t pmd_swp_clear_soft_dirty(pmd_t pmd)
अणु
	वापस pmd_clear_flags(pmd, _PAGE_SWP_SOFT_सूचीTY);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_ARCH_USERFAULTFD_WP
अटल अंतरभूत pte_t pte_swp_mkuffd_wp(pte_t pte)
अणु
	वापस pte_set_flags(pte, _PAGE_SWP_UFFD_WP);
पूर्ण

अटल अंतरभूत पूर्णांक pte_swp_uffd_wp(pte_t pte)
अणु
	वापस pte_flags(pte) & _PAGE_SWP_UFFD_WP;
पूर्ण

अटल अंतरभूत pte_t pte_swp_clear_uffd_wp(pte_t pte)
अणु
	वापस pte_clear_flags(pte, _PAGE_SWP_UFFD_WP);
पूर्ण

अटल अंतरभूत pmd_t pmd_swp_mkuffd_wp(pmd_t pmd)
अणु
	वापस pmd_set_flags(pmd, _PAGE_SWP_UFFD_WP);
पूर्ण

अटल अंतरभूत पूर्णांक pmd_swp_uffd_wp(pmd_t pmd)
अणु
	वापस pmd_flags(pmd) & _PAGE_SWP_UFFD_WP;
पूर्ण

अटल अंतरभूत pmd_t pmd_swp_clear_uffd_wp(pmd_t pmd)
अणु
	वापस pmd_clear_flags(pmd, _PAGE_SWP_UFFD_WP);
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_USERFAULTFD_WP */

#घोषणा PKRU_AD_BIT 0x1
#घोषणा PKRU_WD_BIT 0x2
#घोषणा PKRU_BITS_PER_PKEY 2

#अगर_घोषित CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS
बाह्य u32 init_pkru_value;
#अन्यथा
#घोषणा init_pkru_value	0
#पूर्ण_अगर

अटल अंतरभूत bool __pkru_allows_पढ़ो(u32 pkru, u16 pkey)
अणु
	पूर्णांक pkru_pkey_bits = pkey * PKRU_BITS_PER_PKEY;
	वापस !(pkru & (PKRU_AD_BIT << pkru_pkey_bits));
पूर्ण

अटल अंतरभूत bool __pkru_allows_ग_लिखो(u32 pkru, u16 pkey)
अणु
	पूर्णांक pkru_pkey_bits = pkey * PKRU_BITS_PER_PKEY;
	/*
	 * Access-disable disables ग_लिखोs too so we need to check
	 * both bits here.
	 */
	वापस !(pkru & ((PKRU_AD_BIT|PKRU_WD_BIT) << pkru_pkey_bits));
पूर्ण

अटल अंतरभूत u16 pte_flags_pkey(अचिन्हित दीर्घ pte_flags)
अणु
#अगर_घोषित CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS
	/* अगरdef to aव्योम करोing 59-bit shअगरt on 32-bit values */
	वापस (pte_flags & _PAGE_PKEY_MASK) >> _PAGE_BIT_PKEY_BIT0;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool __pkru_allows_pkey(u16 pkey, bool ग_लिखो)
अणु
	u32 pkru = पढ़ो_pkru();

	अगर (!__pkru_allows_पढ़ो(pkru, pkey))
		वापस false;
	अगर (ग_लिखो && !__pkru_allows_ग_लिखो(pkru, pkey))
		वापस false;

	वापस true;
पूर्ण

/*
 * 'pteval' can come from a PTE, PMD or PUD.  We only check
 * _PAGE_PRESENT, _PAGE_USER, and _PAGE_RW in here which are the
 * same value on all 3 types.
 */
अटल अंतरभूत bool __pte_access_permitted(अचिन्हित दीर्घ pteval, bool ग_लिखो)
अणु
	अचिन्हित दीर्घ need_pte_bits = _PAGE_PRESENT|_PAGE_USER;

	अगर (ग_लिखो)
		need_pte_bits |= _PAGE_RW;

	अगर ((pteval & need_pte_bits) != need_pte_bits)
		वापस 0;

	वापस __pkru_allows_pkey(pte_flags_pkey(pteval), ग_लिखो);
पूर्ण

#घोषणा pte_access_permitted pte_access_permitted
अटल अंतरभूत bool pte_access_permitted(pte_t pte, bool ग_लिखो)
अणु
	वापस __pte_access_permitted(pte_val(pte), ग_लिखो);
पूर्ण

#घोषणा pmd_access_permitted pmd_access_permitted
अटल अंतरभूत bool pmd_access_permitted(pmd_t pmd, bool ग_लिखो)
अणु
	वापस __pte_access_permitted(pmd_val(pmd), ग_लिखो);
पूर्ण

#घोषणा pud_access_permitted pud_access_permitted
अटल अंतरभूत bool pud_access_permitted(pud_t pud, bool ग_लिखो)
अणु
	वापस __pte_access_permitted(pud_val(pud), ग_लिखो);
पूर्ण

#घोषणा __HAVE_ARCH_PFN_MODIFY_ALLOWED 1
बाह्य bool pfn_modअगरy_allowed(अचिन्हित दीर्घ pfn, pgprot_t prot);

अटल अंतरभूत bool arch_has_pfn_modअगरy_check(व्योम)
अणु
	वापस boot_cpu_has_bug(X86_BUG_L1TF);
पूर्ण

#घोषणा arch_faults_on_old_pte arch_faults_on_old_pte
अटल अंतरभूत bool arch_faults_on_old_pte(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_PGTABLE_H */
