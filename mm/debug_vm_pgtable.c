<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This kernel test validates architecture page table helpers and
 * accessors and helps in verअगरying their जारीd compliance with
 * expected generic MM semantics.
 *
 * Copyright (C) 2019 ARM Ltd.
 *
 * Author: Anshuman Khandual <anshuman.khandual@arm.com>
 */
#घोषणा pr_fmt(fmt) "debug_vm_pgtable: [%-25s]: " fmt, __func__

#समावेश <linux/gfp.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/hugetlb.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kconfig.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/module.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/start_kernel.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlbflush.h>

/*
 * Please refer Documentation/vm/arch_pgtable_helpers.rst क्रम the semantics
 * expectations that are being validated here. All future changes in here
 * or the करोcumentation need to be in sync.
 */

#घोषणा VMFLAGS	(VM_READ|VM_WRITE|VM_EXEC)

/*
 * On s390 platक्रमm, the lower 4 bits are used to identअगरy given page table
 * entry type. But these bits might affect the ability to clear entries with
 * pxx_clear() because of how dynamic page table folding works on s390. So
 * जबतक loading up the entries करो not change the lower 4 bits. It करोes not
 * have affect any other platक्रमm. Also aव्योम the 62nd bit on ppc64 that is
 * used to mark a pte entry.
 */
#घोषणा S390_SKIP_MASK		GENMASK(3, 0)
#अगर __BITS_PER_LONG == 64
#घोषणा PPC64_SKIP_MASK		GENMASK(62, 62)
#अन्यथा
#घोषणा PPC64_SKIP_MASK		0x0
#पूर्ण_अगर
#घोषणा ARCH_SKIP_MASK (S390_SKIP_MASK | PPC64_SKIP_MASK)
#घोषणा RANDOM_ORVALUE (GENMASK(BITS_PER_LONG - 1, 0) & ~ARCH_SKIP_MASK)
#घोषणा RANDOM_NZVALUE	GENMASK(7, 0)

अटल व्योम __init pte_basic_tests(अचिन्हित दीर्घ pfn, पूर्णांक idx)
अणु
	pgprot_t prot = protection_map[idx];
	pte_t pte = pfn_pte(pfn, prot);
	अचिन्हित दीर्घ val = idx, *ptr = &val;

	pr_debug("Validating PTE basic (%pGv)\n", ptr);

	/*
	 * This test needs to be executed after the given page table entry
	 * is created with pfn_pte() to make sure that protection_map[idx]
	 * करोes not have the dirty bit enabled from the beginning. This is
	 * important क्रम platक्रमms like arm64 where (!PTE_RDONLY) indicate
	 * dirty bit being set.
	 */
	WARN_ON(pte_dirty(pte_wrprotect(pte)));

	WARN_ON(!pte_same(pte, pte));
	WARN_ON(!pte_young(pte_mkyoung(pte_mkold(pte))));
	WARN_ON(!pte_dirty(pte_सूची_गढ़ोty(pte_mkclean(pte))));
	WARN_ON(!pte_ग_लिखो(pte_mkग_लिखो(pte_wrprotect(pte))));
	WARN_ON(pte_young(pte_mkold(pte_mkyoung(pte))));
	WARN_ON(pte_dirty(pte_mkclean(pte_सूची_गढ़ोty(pte))));
	WARN_ON(pte_ग_लिखो(pte_wrprotect(pte_mkग_लिखो(pte))));
	WARN_ON(pte_dirty(pte_wrprotect(pte_mkclean(pte))));
	WARN_ON(!pte_dirty(pte_wrprotect(pte_सूची_गढ़ोty(pte))));
पूर्ण

अटल व्योम __init pte_advanced_tests(काष्ठा mm_काष्ठा *mm,
				      काष्ठा vm_area_काष्ठा *vma, pte_t *ptep,
				      अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ vaddr,
				      pgprot_t prot)
अणु
	pte_t pte = pfn_pte(pfn, prot);

	/*
	 * Architectures optimize set_pte_at by aव्योमing TLB flush.
	 * This requires set_pte_at to be not used to update an
	 * existing pte entry. Clear pte beक्रमe we करो set_pte_at
	 */

	pr_debug("Validating PTE advanced\n");
	pte = pfn_pte(pfn, prot);
	set_pte_at(mm, vaddr, ptep, pte);
	ptep_set_wrprotect(mm, vaddr, ptep);
	pte = ptep_get(ptep);
	WARN_ON(pte_ग_लिखो(pte));
	ptep_get_and_clear(mm, vaddr, ptep);
	pte = ptep_get(ptep);
	WARN_ON(!pte_none(pte));

	pte = pfn_pte(pfn, prot);
	pte = pte_wrprotect(pte);
	pte = pte_mkclean(pte);
	set_pte_at(mm, vaddr, ptep, pte);
	pte = pte_mkग_लिखो(pte);
	pte = pte_सूची_गढ़ोty(pte);
	ptep_set_access_flags(vma, vaddr, ptep, pte, 1);
	pte = ptep_get(ptep);
	WARN_ON(!(pte_ग_लिखो(pte) && pte_dirty(pte)));
	ptep_get_and_clear_full(mm, vaddr, ptep, 1);
	pte = ptep_get(ptep);
	WARN_ON(!pte_none(pte));

	pte = pfn_pte(pfn, prot);
	pte = pte_mkyoung(pte);
	set_pte_at(mm, vaddr, ptep, pte);
	ptep_test_and_clear_young(vma, vaddr, ptep);
	pte = ptep_get(ptep);
	WARN_ON(pte_young(pte));
पूर्ण

अटल व्योम __init pte_savedग_लिखो_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pte_t pte = pfn_pte(pfn, prot);

	अगर (!IS_ENABLED(CONFIG_NUMA_BALANCING))
		वापस;

	pr_debug("Validating PTE saved write\n");
	WARN_ON(!pte_savedग_लिखो(pte_mk_savedग_लिखो(pte_clear_savedग_लिखो(pte))));
	WARN_ON(pte_savedग_लिखो(pte_clear_savedग_लिखो(pte_mk_savedग_लिखो(pte))));
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल व्योम __init pmd_basic_tests(अचिन्हित दीर्घ pfn, पूर्णांक idx)
अणु
	pgprot_t prot = protection_map[idx];
	pmd_t pmd = pfn_pmd(pfn, prot);
	अचिन्हित दीर्घ val = idx, *ptr = &val;

	अगर (!has_transparent_hugepage())
		वापस;

	pr_debug("Validating PMD basic (%pGv)\n", ptr);

	/*
	 * This test needs to be executed after the given page table entry
	 * is created with pfn_pmd() to make sure that protection_map[idx]
	 * करोes not have the dirty bit enabled from the beginning. This is
	 * important क्रम platक्रमms like arm64 where (!PTE_RDONLY) indicate
	 * dirty bit being set.
	 */
	WARN_ON(pmd_dirty(pmd_wrprotect(pmd)));


	WARN_ON(!pmd_same(pmd, pmd));
	WARN_ON(!pmd_young(pmd_mkyoung(pmd_mkold(pmd))));
	WARN_ON(!pmd_dirty(pmd_सूची_गढ़ोty(pmd_mkclean(pmd))));
	WARN_ON(!pmd_ग_लिखो(pmd_mkग_लिखो(pmd_wrprotect(pmd))));
	WARN_ON(pmd_young(pmd_mkold(pmd_mkyoung(pmd))));
	WARN_ON(pmd_dirty(pmd_mkclean(pmd_सूची_गढ़ोty(pmd))));
	WARN_ON(pmd_ग_लिखो(pmd_wrprotect(pmd_mkग_लिखो(pmd))));
	WARN_ON(pmd_dirty(pmd_wrprotect(pmd_mkclean(pmd))));
	WARN_ON(!pmd_dirty(pmd_wrprotect(pmd_सूची_गढ़ोty(pmd))));
	/*
	 * A huge page करोes not poपूर्णांक to next level page table
	 * entry. Hence this must qualअगरy as pmd_bad().
	 */
	WARN_ON(!pmd_bad(pmd_mkhuge(pmd)));
पूर्ण

अटल व्योम __init pmd_advanced_tests(काष्ठा mm_काष्ठा *mm,
				      काष्ठा vm_area_काष्ठा *vma, pmd_t *pmdp,
				      अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ vaddr,
				      pgprot_t prot, pgtable_t pgtable)
अणु
	pmd_t pmd = pfn_pmd(pfn, prot);

	अगर (!has_transparent_hugepage())
		वापस;

	pr_debug("Validating PMD advanced\n");
	/* Align the address wrt HPAGE_PMD_SIZE */
	vaddr &= HPAGE_PMD_MASK;

	pgtable_trans_huge_deposit(mm, pmdp, pgtable);

	pmd = pfn_pmd(pfn, prot);
	set_pmd_at(mm, vaddr, pmdp, pmd);
	pmdp_set_wrprotect(mm, vaddr, pmdp);
	pmd = READ_ONCE(*pmdp);
	WARN_ON(pmd_ग_लिखो(pmd));
	pmdp_huge_get_and_clear(mm, vaddr, pmdp);
	pmd = READ_ONCE(*pmdp);
	WARN_ON(!pmd_none(pmd));

	pmd = pfn_pmd(pfn, prot);
	pmd = pmd_wrprotect(pmd);
	pmd = pmd_mkclean(pmd);
	set_pmd_at(mm, vaddr, pmdp, pmd);
	pmd = pmd_mkग_लिखो(pmd);
	pmd = pmd_सूची_गढ़ोty(pmd);
	pmdp_set_access_flags(vma, vaddr, pmdp, pmd, 1);
	pmd = READ_ONCE(*pmdp);
	WARN_ON(!(pmd_ग_लिखो(pmd) && pmd_dirty(pmd)));
	pmdp_huge_get_and_clear_full(vma, vaddr, pmdp, 1);
	pmd = READ_ONCE(*pmdp);
	WARN_ON(!pmd_none(pmd));

	pmd = pmd_mkhuge(pfn_pmd(pfn, prot));
	pmd = pmd_mkyoung(pmd);
	set_pmd_at(mm, vaddr, pmdp, pmd);
	pmdp_test_and_clear_young(vma, vaddr, pmdp);
	pmd = READ_ONCE(*pmdp);
	WARN_ON(pmd_young(pmd));

	/*  Clear the pte entries  */
	pmdp_huge_get_and_clear(mm, vaddr, pmdp);
	pgtable = pgtable_trans_huge_withdraw(mm, pmdp);
पूर्ण

अटल व्योम __init pmd_leaf_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pmd_t pmd = pfn_pmd(pfn, prot);

	pr_debug("Validating PMD leaf\n");
	/*
	 * PMD based THP is a leaf entry.
	 */
	pmd = pmd_mkhuge(pmd);
	WARN_ON(!pmd_leaf(pmd));
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMAP
अटल व्योम __init pmd_huge_tests(pmd_t *pmdp, अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pmd_t pmd;

	अगर (!arch_vmap_pmd_supported(prot))
		वापस;

	pr_debug("Validating PMD huge\n");
	/*
	 * X86 defined pmd_set_huge() verअगरies that the given
	 * PMD is not a populated non-leaf entry.
	 */
	WRITE_ONCE(*pmdp, __pmd(0));
	WARN_ON(!pmd_set_huge(pmdp, __pfn_to_phys(pfn), prot));
	WARN_ON(!pmd_clear_huge(pmdp));
	pmd = READ_ONCE(*pmdp);
	WARN_ON(!pmd_none(pmd));
पूर्ण
#अन्यथा /* CONFIG_HAVE_ARCH_HUGE_VMAP */
अटल व्योम __init pmd_huge_tests(pmd_t *pmdp, अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_HUGE_VMAP */

अटल व्योम __init pmd_savedग_लिखो_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pmd_t pmd = pfn_pmd(pfn, prot);

	अगर (!IS_ENABLED(CONFIG_NUMA_BALANCING))
		वापस;

	pr_debug("Validating PMD saved write\n");
	WARN_ON(!pmd_savedग_लिखो(pmd_mk_savedग_लिखो(pmd_clear_savedग_लिखो(pmd))));
	WARN_ON(pmd_savedग_लिखो(pmd_clear_savedग_लिखो(pmd_mk_savedग_लिखो(pmd))));
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
अटल व्योम __init pud_basic_tests(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn, पूर्णांक idx)
अणु
	pgprot_t prot = protection_map[idx];
	pud_t pud = pfn_pud(pfn, prot);
	अचिन्हित दीर्घ val = idx, *ptr = &val;

	अगर (!has_transparent_hugepage())
		वापस;

	pr_debug("Validating PUD basic (%pGv)\n", ptr);

	/*
	 * This test needs to be executed after the given page table entry
	 * is created with pfn_pud() to make sure that protection_map[idx]
	 * करोes not have the dirty bit enabled from the beginning. This is
	 * important क्रम platक्रमms like arm64 where (!PTE_RDONLY) indicate
	 * dirty bit being set.
	 */
	WARN_ON(pud_dirty(pud_wrprotect(pud)));

	WARN_ON(!pud_same(pud, pud));
	WARN_ON(!pud_young(pud_mkyoung(pud_mkold(pud))));
	WARN_ON(!pud_dirty(pud_सूची_गढ़ोty(pud_mkclean(pud))));
	WARN_ON(pud_dirty(pud_mkclean(pud_सूची_गढ़ोty(pud))));
	WARN_ON(!pud_ग_लिखो(pud_mkग_लिखो(pud_wrprotect(pud))));
	WARN_ON(pud_ग_लिखो(pud_wrprotect(pud_mkग_लिखो(pud))));
	WARN_ON(pud_young(pud_mkold(pud_mkyoung(pud))));
	WARN_ON(pud_dirty(pud_wrprotect(pud_mkclean(pud))));
	WARN_ON(!pud_dirty(pud_wrprotect(pud_सूची_गढ़ोty(pud))));

	अगर (mm_pmd_folded(mm))
		वापस;

	/*
	 * A huge page करोes not poपूर्णांक to next level page table
	 * entry. Hence this must qualअगरy as pud_bad().
	 */
	WARN_ON(!pud_bad(pud_mkhuge(pud)));
पूर्ण

अटल व्योम __init pud_advanced_tests(काष्ठा mm_काष्ठा *mm,
				      काष्ठा vm_area_काष्ठा *vma, pud_t *pudp,
				      अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ vaddr,
				      pgprot_t prot)
अणु
	pud_t pud = pfn_pud(pfn, prot);

	अगर (!has_transparent_hugepage())
		वापस;

	pr_debug("Validating PUD advanced\n");
	/* Align the address wrt HPAGE_PUD_SIZE */
	vaddr &= HPAGE_PUD_MASK;

	set_pud_at(mm, vaddr, pudp, pud);
	pudp_set_wrprotect(mm, vaddr, pudp);
	pud = READ_ONCE(*pudp);
	WARN_ON(pud_ग_लिखो(pud));

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	pudp_huge_get_and_clear(mm, vaddr, pudp);
	pud = READ_ONCE(*pudp);
	WARN_ON(!pud_none(pud));
#पूर्ण_अगर /* __PAGETABLE_PMD_FOLDED */
	pud = pfn_pud(pfn, prot);
	pud = pud_wrprotect(pud);
	pud = pud_mkclean(pud);
	set_pud_at(mm, vaddr, pudp, pud);
	pud = pud_mkग_लिखो(pud);
	pud = pud_सूची_गढ़ोty(pud);
	pudp_set_access_flags(vma, vaddr, pudp, pud, 1);
	pud = READ_ONCE(*pudp);
	WARN_ON(!(pud_ग_लिखो(pud) && pud_dirty(pud)));

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	pudp_huge_get_and_clear_full(mm, vaddr, pudp, 1);
	pud = READ_ONCE(*pudp);
	WARN_ON(!pud_none(pud));
#पूर्ण_अगर /* __PAGETABLE_PMD_FOLDED */

	pud = pfn_pud(pfn, prot);
	pud = pud_mkyoung(pud);
	set_pud_at(mm, vaddr, pudp, pud);
	pudp_test_and_clear_young(vma, vaddr, pudp);
	pud = READ_ONCE(*pudp);
	WARN_ON(pud_young(pud));

	pudp_huge_get_and_clear(mm, vaddr, pudp);
पूर्ण

अटल व्योम __init pud_leaf_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pud_t pud = pfn_pud(pfn, prot);

	pr_debug("Validating PUD leaf\n");
	/*
	 * PUD based THP is a leaf entry.
	 */
	pud = pud_mkhuge(pud);
	WARN_ON(!pud_leaf(pud));
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMAP
अटल व्योम __init pud_huge_tests(pud_t *pudp, अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pud_t pud;

	अगर (!arch_vmap_pud_supported(prot))
		वापस;

	pr_debug("Validating PUD huge\n");
	/*
	 * X86 defined pud_set_huge() verअगरies that the given
	 * PUD is not a populated non-leaf entry.
	 */
	WRITE_ONCE(*pudp, __pud(0));
	WARN_ON(!pud_set_huge(pudp, __pfn_to_phys(pfn), prot));
	WARN_ON(!pud_clear_huge(pudp));
	pud = READ_ONCE(*pudp);
	WARN_ON(!pud_none(pud));
पूर्ण
#अन्यथा /* !CONFIG_HAVE_ARCH_HUGE_VMAP */
अटल व्योम __init pud_huge_tests(pud_t *pudp, अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_HAVE_ARCH_HUGE_VMAP */

#अन्यथा  /* !CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD */
अटल व्योम __init pud_basic_tests(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn, पूर्णांक idx) अणु पूर्ण
अटल व्योम __init pud_advanced_tests(काष्ठा mm_काष्ठा *mm,
				      काष्ठा vm_area_काष्ठा *vma, pud_t *pudp,
				      अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ vaddr,
				      pgprot_t prot)
अणु
पूर्ण
अटल व्योम __init pud_leaf_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
अटल व्योम __init pud_huge_tests(pud_t *pudp, अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD */
#अन्यथा  /* !CONFIG_TRANSPARENT_HUGEPAGE */
अटल व्योम __init pmd_basic_tests(अचिन्हित दीर्घ pfn, पूर्णांक idx) अणु पूर्ण
अटल व्योम __init pud_basic_tests(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn, पूर्णांक idx) अणु पूर्ण
अटल व्योम __init pmd_advanced_tests(काष्ठा mm_काष्ठा *mm,
				      काष्ठा vm_area_काष्ठा *vma, pmd_t *pmdp,
				      अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ vaddr,
				      pgprot_t prot, pgtable_t pgtable)
अणु
पूर्ण
अटल व्योम __init pud_advanced_tests(काष्ठा mm_काष्ठा *mm,
				      काष्ठा vm_area_काष्ठा *vma, pud_t *pudp,
				      अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ vaddr,
				      pgprot_t prot)
अणु
पूर्ण
अटल व्योम __init pmd_leaf_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
अटल व्योम __init pud_leaf_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
अटल व्योम __init pmd_huge_tests(pmd_t *pmdp, अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
पूर्ण
अटल व्योम __init pud_huge_tests(pud_t *pudp, अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
पूर्ण
अटल व्योम __init pmd_savedग_लिखो_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

अटल व्योम __init p4d_basic_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	p4d_t p4d;

	pr_debug("Validating P4D basic\n");
	स_रखो(&p4d, RANDOM_NZVALUE, माप(p4d_t));
	WARN_ON(!p4d_same(p4d, p4d));
पूर्ण

अटल व्योम __init pgd_basic_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pgd_t pgd;

	pr_debug("Validating PGD basic\n");
	स_रखो(&pgd, RANDOM_NZVALUE, माप(pgd_t));
	WARN_ON(!pgd_same(pgd, pgd));
पूर्ण

#अगर_अघोषित __PAGETABLE_PUD_FOLDED
अटल व्योम __init pud_clear_tests(काष्ठा mm_काष्ठा *mm, pud_t *pudp)
अणु
	pud_t pud = READ_ONCE(*pudp);

	अगर (mm_pmd_folded(mm))
		वापस;

	pr_debug("Validating PUD clear\n");
	pud = __pud(pud_val(pud) | RANDOM_ORVALUE);
	WRITE_ONCE(*pudp, pud);
	pud_clear(pudp);
	pud = READ_ONCE(*pudp);
	WARN_ON(!pud_none(pud));
पूर्ण

अटल व्योम __init pud_populate_tests(काष्ठा mm_काष्ठा *mm, pud_t *pudp,
				      pmd_t *pmdp)
अणु
	pud_t pud;

	अगर (mm_pmd_folded(mm))
		वापस;

	pr_debug("Validating PUD populate\n");
	/*
	 * This entry poपूर्णांकs to next level page table page.
	 * Hence this must not qualअगरy as pud_bad().
	 */
	pud_populate(mm, pudp, pmdp);
	pud = READ_ONCE(*pudp);
	WARN_ON(pud_bad(pud));
पूर्ण
#अन्यथा  /* !__PAGETABLE_PUD_FOLDED */
अटल व्योम __init pud_clear_tests(काष्ठा mm_काष्ठा *mm, pud_t *pudp) अणु पूर्ण
अटल व्योम __init pud_populate_tests(काष्ठा mm_काष्ठा *mm, pud_t *pudp,
				      pmd_t *pmdp)
अणु
पूर्ण
#पूर्ण_अगर /* PAGETABLE_PUD_FOLDED */

#अगर_अघोषित __PAGETABLE_P4D_FOLDED
अटल व्योम __init p4d_clear_tests(काष्ठा mm_काष्ठा *mm, p4d_t *p4dp)
अणु
	p4d_t p4d = READ_ONCE(*p4dp);

	अगर (mm_pud_folded(mm))
		वापस;

	pr_debug("Validating P4D clear\n");
	p4d = __p4d(p4d_val(p4d) | RANDOM_ORVALUE);
	WRITE_ONCE(*p4dp, p4d);
	p4d_clear(p4dp);
	p4d = READ_ONCE(*p4dp);
	WARN_ON(!p4d_none(p4d));
पूर्ण

अटल व्योम __init p4d_populate_tests(काष्ठा mm_काष्ठा *mm, p4d_t *p4dp,
				      pud_t *pudp)
अणु
	p4d_t p4d;

	अगर (mm_pud_folded(mm))
		वापस;

	pr_debug("Validating P4D populate\n");
	/*
	 * This entry poपूर्णांकs to next level page table page.
	 * Hence this must not qualअगरy as p4d_bad().
	 */
	pud_clear(pudp);
	p4d_clear(p4dp);
	p4d_populate(mm, p4dp, pudp);
	p4d = READ_ONCE(*p4dp);
	WARN_ON(p4d_bad(p4d));
पूर्ण

अटल व्योम __init pgd_clear_tests(काष्ठा mm_काष्ठा *mm, pgd_t *pgdp)
अणु
	pgd_t pgd = READ_ONCE(*pgdp);

	अगर (mm_p4d_folded(mm))
		वापस;

	pr_debug("Validating PGD clear\n");
	pgd = __pgd(pgd_val(pgd) | RANDOM_ORVALUE);
	WRITE_ONCE(*pgdp, pgd);
	pgd_clear(pgdp);
	pgd = READ_ONCE(*pgdp);
	WARN_ON(!pgd_none(pgd));
पूर्ण

अटल व्योम __init pgd_populate_tests(काष्ठा mm_काष्ठा *mm, pgd_t *pgdp,
				      p4d_t *p4dp)
अणु
	pgd_t pgd;

	अगर (mm_p4d_folded(mm))
		वापस;

	pr_debug("Validating PGD populate\n");
	/*
	 * This entry poपूर्णांकs to next level page table page.
	 * Hence this must not qualअगरy as pgd_bad().
	 */
	p4d_clear(p4dp);
	pgd_clear(pgdp);
	pgd_populate(mm, pgdp, p4dp);
	pgd = READ_ONCE(*pgdp);
	WARN_ON(pgd_bad(pgd));
पूर्ण
#अन्यथा  /* !__PAGETABLE_P4D_FOLDED */
अटल व्योम __init p4d_clear_tests(काष्ठा mm_काष्ठा *mm, p4d_t *p4dp) अणु पूर्ण
अटल व्योम __init pgd_clear_tests(काष्ठा mm_काष्ठा *mm, pgd_t *pgdp) अणु पूर्ण
अटल व्योम __init p4d_populate_tests(काष्ठा mm_काष्ठा *mm, p4d_t *p4dp,
				      pud_t *pudp)
अणु
पूर्ण
अटल व्योम __init pgd_populate_tests(काष्ठा mm_काष्ठा *mm, pgd_t *pgdp,
				      p4d_t *p4dp)
अणु
पूर्ण
#पूर्ण_अगर /* PAGETABLE_P4D_FOLDED */

अटल व्योम __init pte_clear_tests(काष्ठा mm_काष्ठा *mm, pte_t *ptep,
				   अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ vaddr,
				   pgprot_t prot)
अणु
	pte_t pte = pfn_pte(pfn, prot);

	pr_debug("Validating PTE clear\n");
#अगर_अघोषित CONFIG_RISCV
	pte = __pte(pte_val(pte) | RANDOM_ORVALUE);
#पूर्ण_अगर
	set_pte_at(mm, vaddr, ptep, pte);
	barrier();
	pte_clear(mm, vaddr, ptep);
	pte = ptep_get(ptep);
	WARN_ON(!pte_none(pte));
पूर्ण

अटल व्योम __init pmd_clear_tests(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp)
अणु
	pmd_t pmd = READ_ONCE(*pmdp);

	pr_debug("Validating PMD clear\n");
	pmd = __pmd(pmd_val(pmd) | RANDOM_ORVALUE);
	WRITE_ONCE(*pmdp, pmd);
	pmd_clear(pmdp);
	pmd = READ_ONCE(*pmdp);
	WARN_ON(!pmd_none(pmd));
पूर्ण

अटल व्योम __init pmd_populate_tests(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				      pgtable_t pgtable)
अणु
	pmd_t pmd;

	pr_debug("Validating PMD populate\n");
	/*
	 * This entry poपूर्णांकs to next level page table page.
	 * Hence this must not qualअगरy as pmd_bad().
	 */
	pmd_populate(mm, pmdp, pgtable);
	pmd = READ_ONCE(*pmdp);
	WARN_ON(pmd_bad(pmd));
पूर्ण

अटल व्योम __init pte_special_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pte_t pte = pfn_pte(pfn, prot);

	अगर (!IS_ENABLED(CONFIG_ARCH_HAS_PTE_SPECIAL))
		वापस;

	pr_debug("Validating PTE special\n");
	WARN_ON(!pte_special(pte_mkspecial(pte)));
पूर्ण

अटल व्योम __init pte_protnone_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pte_t pte = pfn_pte(pfn, prot);

	अगर (!IS_ENABLED(CONFIG_NUMA_BALANCING))
		वापस;

	pr_debug("Validating PTE protnone\n");
	WARN_ON(!pte_protnone(pte));
	WARN_ON(!pte_present(pte));
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल व्योम __init pmd_protnone_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pmd_t pmd = pmd_mkhuge(pfn_pmd(pfn, prot));

	अगर (!IS_ENABLED(CONFIG_NUMA_BALANCING))
		वापस;

	pr_debug("Validating PMD protnone\n");
	WARN_ON(!pmd_protnone(pmd));
	WARN_ON(!pmd_present(pmd));
पूर्ण
#अन्यथा  /* !CONFIG_TRANSPARENT_HUGEPAGE */
अटल व्योम __init pmd_protnone_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

#अगर_घोषित CONFIG_ARCH_HAS_PTE_DEVMAP
अटल व्योम __init pte_devmap_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pte_t pte = pfn_pte(pfn, prot);

	pr_debug("Validating PTE devmap\n");
	WARN_ON(!pte_devmap(pte_mkdevmap(pte)));
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल व्योम __init pmd_devmap_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pmd_t pmd = pfn_pmd(pfn, prot);

	pr_debug("Validating PMD devmap\n");
	WARN_ON(!pmd_devmap(pmd_mkdevmap(pmd)));
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
अटल व्योम __init pud_devmap_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pud_t pud = pfn_pud(pfn, prot);

	pr_debug("Validating PUD devmap\n");
	WARN_ON(!pud_devmap(pud_mkdevmap(pud)));
पूर्ण
#अन्यथा  /* !CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD */
अटल व्योम __init pud_devmap_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD */
#अन्यथा  /* CONFIG_TRANSPARENT_HUGEPAGE */
अटल व्योम __init pmd_devmap_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
अटल व्योम __init pud_devmap_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */
#अन्यथा
अटल व्योम __init pte_devmap_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
अटल व्योम __init pmd_devmap_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
अटल व्योम __init pud_devmap_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_PTE_DEVMAP */

अटल व्योम __init pte_soft_dirty_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pte_t pte = pfn_pte(pfn, prot);

	अगर (!IS_ENABLED(CONFIG_MEM_SOFT_सूचीTY))
		वापस;

	pr_debug("Validating PTE soft dirty\n");
	WARN_ON(!pte_soft_dirty(pte_mksoft_dirty(pte)));
	WARN_ON(pte_soft_dirty(pte_clear_soft_dirty(pte)));
पूर्ण

अटल व्योम __init pte_swap_soft_dirty_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pte_t pte = pfn_pte(pfn, prot);

	अगर (!IS_ENABLED(CONFIG_MEM_SOFT_सूचीTY))
		वापस;

	pr_debug("Validating PTE swap soft dirty\n");
	WARN_ON(!pte_swp_soft_dirty(pte_swp_mksoft_dirty(pte)));
	WARN_ON(pte_swp_soft_dirty(pte_swp_clear_soft_dirty(pte)));
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल व्योम __init pmd_soft_dirty_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pmd_t pmd = pfn_pmd(pfn, prot);

	अगर (!IS_ENABLED(CONFIG_MEM_SOFT_सूचीTY))
		वापस;

	pr_debug("Validating PMD soft dirty\n");
	WARN_ON(!pmd_soft_dirty(pmd_mksoft_dirty(pmd)));
	WARN_ON(pmd_soft_dirty(pmd_clear_soft_dirty(pmd)));
पूर्ण

अटल व्योम __init pmd_swap_soft_dirty_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pmd_t pmd = pfn_pmd(pfn, prot);

	अगर (!IS_ENABLED(CONFIG_MEM_SOFT_सूचीTY) ||
		!IS_ENABLED(CONFIG_ARCH_ENABLE_THP_MIGRATION))
		वापस;

	pr_debug("Validating PMD swap soft dirty\n");
	WARN_ON(!pmd_swp_soft_dirty(pmd_swp_mksoft_dirty(pmd)));
	WARN_ON(pmd_swp_soft_dirty(pmd_swp_clear_soft_dirty(pmd)));
पूर्ण
#अन्यथा  /* !CONFIG_ARCH_HAS_PTE_DEVMAP */
अटल व्योम __init pmd_soft_dirty_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
अटल व्योम __init pmd_swap_soft_dirty_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_PTE_DEVMAP */

अटल व्योम __init pte_swap_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	swp_entry_t swp;
	pte_t pte;

	pr_debug("Validating PTE swap\n");
	pte = pfn_pte(pfn, prot);
	swp = __pte_to_swp_entry(pte);
	pte = __swp_entry_to_pte(swp);
	WARN_ON(pfn != pte_pfn(pte));
पूर्ण

#अगर_घोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
अटल व्योम __init pmd_swap_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	swp_entry_t swp;
	pmd_t pmd;

	pr_debug("Validating PMD swap\n");
	pmd = pfn_pmd(pfn, prot);
	swp = __pmd_to_swp_entry(pmd);
	pmd = __swp_entry_to_pmd(swp);
	WARN_ON(pfn != pmd_pfn(pmd));
पूर्ण
#अन्यथा  /* !CONFIG_ARCH_ENABLE_THP_MIGRATION */
अटल व्योम __init pmd_swap_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_ENABLE_THP_MIGRATION */

अटल व्योम __init swap_migration_tests(व्योम)
अणु
	काष्ठा page *page;
	swp_entry_t swp;

	अगर (!IS_ENABLED(CONFIG_MIGRATION))
		वापस;

	pr_debug("Validating swap migration\n");
	/*
	 * swap_migration_tests() requires a dedicated page as it needs to
	 * be locked beक्रमe creating a migration entry from it. Locking the
	 * page that actually maps kernel text ('start_kernel') can be real
	 * problematic. Lets allocate a dedicated page explicitly क्रम this
	 * purpose that will be मुक्तd subsequently.
	 */
	page = alloc_page(GFP_KERNEL);
	अगर (!page) अणु
		pr_err("page allocation failed\n");
		वापस;
	पूर्ण

	/*
	 * make_migration_entry() expects given page to be
	 * locked, otherwise it stumbles upon a BUG_ON().
	 */
	__SetPageLocked(page);
	swp = make_migration_entry(page, 1);
	WARN_ON(!is_migration_entry(swp));
	WARN_ON(!is_ग_लिखो_migration_entry(swp));

	make_migration_entry_पढ़ो(&swp);
	WARN_ON(!is_migration_entry(swp));
	WARN_ON(is_ग_लिखो_migration_entry(swp));

	swp = make_migration_entry(page, 0);
	WARN_ON(!is_migration_entry(swp));
	WARN_ON(is_ग_लिखो_migration_entry(swp));
	__ClearPageLocked(page);
	__मुक्त_page(page);
पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
अटल व्योम __init hugetlb_basic_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	काष्ठा page *page;
	pte_t pte;

	pr_debug("Validating HugeTLB basic\n");
	/*
	 * Accessing the page associated with the pfn is safe here,
	 * as it was previously derived from a real kernel symbol.
	 */
	page = pfn_to_page(pfn);
	pte = mk_huge_pte(page, prot);

	WARN_ON(!huge_pte_dirty(huge_pte_सूची_गढ़ोty(pte)));
	WARN_ON(!huge_pte_ग_लिखो(huge_pte_mkग_लिखो(huge_pte_wrprotect(pte))));
	WARN_ON(huge_pte_ग_लिखो(huge_pte_wrprotect(huge_pte_mkग_लिखो(pte))));

#अगर_घोषित CONFIG_ARCH_WANT_GENERAL_HUGETLB
	pte = pfn_pte(pfn, prot);

	WARN_ON(!pte_huge(pte_mkhuge(pte)));
#पूर्ण_अगर /* CONFIG_ARCH_WANT_GENERAL_HUGETLB */
पूर्ण
#अन्यथा  /* !CONFIG_HUGETLB_PAGE */
अटल व्योम __init hugetlb_basic_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल व्योम __init pmd_thp_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pmd_t pmd;

	अगर (!has_transparent_hugepage())
		वापस;

	pr_debug("Validating PMD based THP\n");
	/*
	 * pmd_trans_huge() and pmd_present() must वापस positive after
	 * MMU invalidation with pmd_mkinvalid(). This behavior is an
	 * optimization क्रम transparent huge page. pmd_trans_huge() must
	 * be true अगर pmd_page() वापसs a valid THP to aव्योम taking the
	 * pmd_lock when others walk over non transhuge pmds (i.e. there
	 * are no THP allocated). Especially when splitting a THP and
	 * removing the present bit from the pmd, pmd_trans_huge() still
	 * needs to वापस true. pmd_present() should be true whenever
	 * pmd_trans_huge() वापसs true.
	 */
	pmd = pfn_pmd(pfn, prot);
	WARN_ON(!pmd_trans_huge(pmd_mkhuge(pmd)));

#अगर_अघोषित __HAVE_ARCH_PMDP_INVALIDATE
	WARN_ON(!pmd_trans_huge(pmd_mkinvalid(pmd_mkhuge(pmd))));
	WARN_ON(!pmd_present(pmd_mkinvalid(pmd_mkhuge(pmd))));
#पूर्ण_अगर /* __HAVE_ARCH_PMDP_INVALIDATE */
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
अटल व्योम __init pud_thp_tests(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	pud_t pud;

	अगर (!has_transparent_hugepage())
		वापस;

	pr_debug("Validating PUD based THP\n");
	pud = pfn_pud(pfn, prot);
	WARN_ON(!pud_trans_huge(pud_mkhuge(pud)));

	/*
	 * pud_mkinvalid() has been dropped क्रम now. Enable back
	 * these tests when it comes back with a modअगरied pud_present().
	 *
	 * WARN_ON(!pud_trans_huge(pud_mkinvalid(pud_mkhuge(pud))));
	 * WARN_ON(!pud_present(pud_mkinvalid(pud_mkhuge(pud))));
	 */
पूर्ण
#अन्यथा  /* !CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD */
अटल व्योम __init pud_thp_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD */
#अन्यथा  /* !CONFIG_TRANSPARENT_HUGEPAGE */
अटल व्योम __init pmd_thp_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
अटल व्योम __init pud_thp_tests(अचिन्हित दीर्घ pfn, pgprot_t prot) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

अटल अचिन्हित दीर्घ __init get_अक्रमom_vaddr(व्योम)
अणु
	अचिन्हित दीर्घ अक्रमom_vaddr, अक्रमom_pages, total_user_pages;

	total_user_pages = (TASK_SIZE - FIRST_USER_ADDRESS) / PAGE_SIZE;

	अक्रमom_pages = get_अक्रमom_दीर्घ() % total_user_pages;
	अक्रमom_vaddr = FIRST_USER_ADDRESS + अक्रमom_pages * PAGE_SIZE;

	वापस अक्रमom_vaddr;
पूर्ण

अटल पूर्णांक __init debug_vm_pgtable(व्योम)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm;
	pgd_t *pgdp;
	p4d_t *p4dp, *saved_p4dp;
	pud_t *pudp, *saved_pudp;
	pmd_t *pmdp, *saved_pmdp, pmd;
	pte_t *ptep;
	pgtable_t saved_ptep;
	pgprot_t prot, protnone;
	phys_addr_t paddr;
	अचिन्हित दीर्घ vaddr, pte_aligned, pmd_aligned;
	अचिन्हित दीर्घ pud_aligned, p4d_aligned, pgd_aligned;
	spinlock_t *ptl = शून्य;
	पूर्णांक idx;

	pr_info("Validating architecture page table helpers\n");
	prot = vm_get_page_prot(VMFLAGS);
	vaddr = get_अक्रमom_vaddr();
	mm = mm_alloc();
	अगर (!mm) अणु
		pr_err("mm_struct allocation failed\n");
		वापस 1;
	पूर्ण

	/*
	 * __P000 (or even __S000) will help create page table entries with
	 * PROT_NONE permission as required क्रम pxx_protnone_tests().
	 */
	protnone = __P000;

	vma = vm_area_alloc(mm);
	अगर (!vma) अणु
		pr_err("vma allocation failed\n");
		वापस 1;
	पूर्ण

	/*
	 * PFN क्रम mapping at PTE level is determined from a standard kernel
	 * text symbol. But pfns क्रम higher page table levels are derived by
	 * masking lower bits of this real pfn. These derived pfns might not
	 * exist on the platक्रमm but that करोes not really matter as pfn_pxx()
	 * helpers will still create appropriate entries क्रम the test. This
	 * helps aव्योम large memory block allocations to be used क्रम mapping
	 * at higher page table levels.
	 */
	paddr = __pa_symbol(&start_kernel);

	pte_aligned = (paddr & PAGE_MASK) >> PAGE_SHIFT;
	pmd_aligned = (paddr & PMD_MASK) >> PAGE_SHIFT;
	pud_aligned = (paddr & PUD_MASK) >> PAGE_SHIFT;
	p4d_aligned = (paddr & P4D_MASK) >> PAGE_SHIFT;
	pgd_aligned = (paddr & PGसूची_MASK) >> PAGE_SHIFT;
	WARN_ON(!pfn_valid(pte_aligned));

	pgdp = pgd_offset(mm, vaddr);
	p4dp = p4d_alloc(mm, pgdp, vaddr);
	pudp = pud_alloc(mm, p4dp, vaddr);
	pmdp = pmd_alloc(mm, pudp, vaddr);
	/*
	 * Allocate pgtable_t
	 */
	अगर (pte_alloc(mm, pmdp)) अणु
		pr_err("pgtable allocation failed\n");
		वापस 1;
	पूर्ण

	/*
	 * Save all the page table page addresses as the page table
	 * entries will be used क्रम testing with अक्रमom or garbage
	 * values. These saved addresses will be used क्रम मुक्तing
	 * page table pages.
	 */
	pmd = READ_ONCE(*pmdp);
	saved_p4dp = p4d_offset(pgdp, 0UL);
	saved_pudp = pud_offset(p4dp, 0UL);
	saved_pmdp = pmd_offset(pudp, 0UL);
	saved_ptep = pmd_pgtable(pmd);

	/*
	 * Iterate over the protection_map[] to make sure that all
	 * the basic page table transक्रमmation validations just hold
	 * true irrespective of the starting protection value क्रम a
	 * given page table entry.
	 */
	क्रम (idx = 0; idx < ARRAY_SIZE(protection_map); idx++) अणु
		pte_basic_tests(pte_aligned, idx);
		pmd_basic_tests(pmd_aligned, idx);
		pud_basic_tests(mm, pud_aligned, idx);
	पूर्ण

	/*
	 * Both P4D and PGD level tests are very basic which करो not
	 * involve creating page table entries from the protection
	 * value and the given pfn. Hence just keep them out from
	 * the above iteration क्रम now to save some test execution
	 * समय.
	 */
	p4d_basic_tests(p4d_aligned, prot);
	pgd_basic_tests(pgd_aligned, prot);

	pmd_leaf_tests(pmd_aligned, prot);
	pud_leaf_tests(pud_aligned, prot);

	pte_savedग_लिखो_tests(pte_aligned, protnone);
	pmd_savedग_लिखो_tests(pmd_aligned, protnone);

	pte_special_tests(pte_aligned, prot);
	pte_protnone_tests(pte_aligned, protnone);
	pmd_protnone_tests(pmd_aligned, protnone);

	pte_devmap_tests(pte_aligned, prot);
	pmd_devmap_tests(pmd_aligned, prot);
	pud_devmap_tests(pud_aligned, prot);

	pte_soft_dirty_tests(pte_aligned, prot);
	pmd_soft_dirty_tests(pmd_aligned, prot);
	pte_swap_soft_dirty_tests(pte_aligned, prot);
	pmd_swap_soft_dirty_tests(pmd_aligned, prot);

	pte_swap_tests(pte_aligned, prot);
	pmd_swap_tests(pmd_aligned, prot);

	swap_migration_tests();

	pmd_thp_tests(pmd_aligned, prot);
	pud_thp_tests(pud_aligned, prot);

	hugetlb_basic_tests(pte_aligned, prot);

	/*
	 * Page table modअगरying tests. They need to hold
	 * proper page table lock.
	 */

	ptep = pte_offset_map_lock(mm, pmdp, vaddr, &ptl);
	pte_clear_tests(mm, ptep, pte_aligned, vaddr, prot);
	pte_advanced_tests(mm, vma, ptep, pte_aligned, vaddr, prot);
	pte_unmap_unlock(ptep, ptl);

	ptl = pmd_lock(mm, pmdp);
	pmd_clear_tests(mm, pmdp);
	pmd_advanced_tests(mm, vma, pmdp, pmd_aligned, vaddr, prot, saved_ptep);
	pmd_huge_tests(pmdp, pmd_aligned, prot);
	pmd_populate_tests(mm, pmdp, saved_ptep);
	spin_unlock(ptl);

	ptl = pud_lock(mm, pudp);
	pud_clear_tests(mm, pudp);
	pud_advanced_tests(mm, vma, pudp, pud_aligned, vaddr, prot);
	pud_huge_tests(pudp, pud_aligned, prot);
	pud_populate_tests(mm, pudp, saved_pmdp);
	spin_unlock(ptl);

	spin_lock(&mm->page_table_lock);
	p4d_clear_tests(mm, p4dp);
	pgd_clear_tests(mm, pgdp);
	p4d_populate_tests(mm, p4dp, saved_pudp);
	pgd_populate_tests(mm, pgdp, saved_p4dp);
	spin_unlock(&mm->page_table_lock);

	p4d_मुक्त(mm, saved_p4dp);
	pud_मुक्त(mm, saved_pudp);
	pmd_मुक्त(mm, saved_pmdp);
	pte_मुक्त(mm, saved_ptep);

	vm_area_मुक्त(vma);
	mm_dec_nr_puds(mm);
	mm_dec_nr_pmds(mm);
	mm_dec_nr_ptes(mm);
	mmdrop(mm);
	वापस 0;
पूर्ण
late_initcall(debug_vm_pgtable);
