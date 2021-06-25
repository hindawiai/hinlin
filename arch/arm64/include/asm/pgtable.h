<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_PGTABLE_H
#घोषणा __ASM_PGTABLE_H

#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/proc-fns.h>

#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mte.h>
#समावेश <यंत्र/pgtable-hwdef.h>
#समावेश <यंत्र/pgtable-prot.h>
#समावेश <यंत्र/tlbflush.h>

/*
 * VMALLOC range.
 *
 * VMALLOC_START: beginning of the kernel vदो_स्मृति space
 * VMALLOC_END: extends to the available space below vmemmap, PCI I/O space
 *	and fixed mappings
 */
#घोषणा VMALLOC_START		(MODULES_END)
#घोषणा VMALLOC_END		(VMEMMAP_START - SZ_256M)

#घोषणा vmemmap			((काष्ठा page *)VMEMMAP_START - (memstart_addr >> PAGE_SHIFT))

#घोषणा FIRST_USER_ADDRESS	0UL

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/sched.h>

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा __HAVE_ARCH_FLUSH_PMD_TLB_RANGE

/* Set stride and tlb_level in flush_*_tlb_range */
#घोषणा flush_pmd_tlb_range(vma, addr, end)	\
	__flush_tlb_range(vma, addr, end, PMD_SIZE, false, 2)
#घोषणा flush_pud_tlb_range(vma, addr, end)	\
	__flush_tlb_range(vma, addr, end, PUD_SIZE, false, 1)
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

/*
 * Outside of a few very special situations (e.g. hibernation), we always
 * use broadcast TLB invalidation inकाष्ठाions, thereक्रमe a spurious page
 * fault on one CPU which has been handled concurrently by another CPU
 * करोes not need to perक्रमm additional invalidation.
 */
#घोषणा flush_tlb_fix_spurious_fault(vma, address) करो अणु पूर्ण जबतक (0)

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
बाह्य अचिन्हित दीर्घ empty_zero_page[PAGE_SIZE / माप(अचिन्हित दीर्घ)];
#घोषणा ZERO_PAGE(vaddr)	phys_to_page(__pa_symbol(empty_zero_page))

#घोषणा pte_ERROR(e)	\
	pr_err("%s:%d: bad pte %016llx.\n", __खाता__, __LINE__, pte_val(e))

/*
 * Macros to convert between a physical address and its placement in a
 * page table entry, taking care of 52-bit addresses.
 */
#अगर_घोषित CONFIG_ARM64_PA_BITS_52
#घोषणा __pte_to_phys(pte)	\
	((pte_val(pte) & PTE_ADDR_LOW) | ((pte_val(pte) & PTE_ADDR_HIGH) << 36))
#घोषणा __phys_to_pte_val(phys)	(((phys) | ((phys) >> 36)) & PTE_ADDR_MASK)
#अन्यथा
#घोषणा __pte_to_phys(pte)	(pte_val(pte) & PTE_ADDR_MASK)
#घोषणा __phys_to_pte_val(phys)	(phys)
#पूर्ण_अगर

#घोषणा pte_pfn(pte)		(__pte_to_phys(pte) >> PAGE_SHIFT)
#घोषणा pfn_pte(pfn,prot)	\
	__pte(__phys_to_pte_val((phys_addr_t)(pfn) << PAGE_SHIFT) | pgprot_val(prot))

#घोषणा pte_none(pte)		(!pte_val(pte))
#घोषणा pte_clear(mm,addr,ptep)	set_pte(ptep, __pte(0))
#घोषणा pte_page(pte)		(pfn_to_page(pte_pfn(pte)))

/*
 * The following only work अगर pte_present(). Undefined behaviour otherwise.
 */
#घोषणा pte_present(pte)	(!!(pte_val(pte) & (PTE_VALID | PTE_PROT_NONE)))
#घोषणा pte_young(pte)		(!!(pte_val(pte) & PTE_AF))
#घोषणा pte_special(pte)	(!!(pte_val(pte) & PTE_SPECIAL))
#घोषणा pte_ग_लिखो(pte)		(!!(pte_val(pte) & PTE_WRITE))
#घोषणा pte_user_exec(pte)	(!(pte_val(pte) & PTE_UXN))
#घोषणा pte_cont(pte)		(!!(pte_val(pte) & PTE_CONT))
#घोषणा pte_devmap(pte)		(!!(pte_val(pte) & PTE_DEVMAP))
#घोषणा pte_tagged(pte)		((pte_val(pte) & PTE_ATTRINDX_MASK) == \
				 PTE_ATTRINDX(MT_NORMAL_TAGGED))

#घोषणा pte_cont_addr_end(addr, end)						\
(अणु	अचिन्हित दीर्घ __boundary = ((addr) + CONT_PTE_SIZE) & CONT_PTE_MASK;	\
	(__boundary - 1 < (end) - 1) ? __boundary : (end);			\
पूर्ण)

#घोषणा pmd_cont_addr_end(addr, end)						\
(अणु	अचिन्हित दीर्घ __boundary = ((addr) + CONT_PMD_SIZE) & CONT_PMD_MASK;	\
	(__boundary - 1 < (end) - 1) ? __boundary : (end);			\
पूर्ण)

#घोषणा pte_hw_dirty(pte)	(pte_ग_लिखो(pte) && !(pte_val(pte) & PTE_RDONLY))
#घोषणा pte_sw_dirty(pte)	(!!(pte_val(pte) & PTE_सूचीTY))
#घोषणा pte_dirty(pte)		(pte_sw_dirty(pte) || pte_hw_dirty(pte))

#घोषणा pte_valid(pte)		(!!(pte_val(pte) & PTE_VALID))
/*
 * Execute-only user mappings करो not have the PTE_USER bit set. All valid
 * kernel mappings have the PTE_UXN bit set.
 */
#घोषणा pte_valid_not_user(pte) \
	((pte_val(pte) & (PTE_VALID | PTE_USER | PTE_UXN)) == (PTE_VALID | PTE_UXN))
/*
 * Could the pte be present in the TLB? We must check mm_tlb_flush_pending
 * so that we करोn't erroneously वापस false क्रम pages that have been
 * remapped as PROT_NONE but are yet to be flushed from the TLB.
 * Note that we can't make any assumptions based on the state of the access
 * flag, since ptep_clear_flush_young() elides a DSB when invalidating the
 * TLB.
 */
#घोषणा pte_accessible(mm, pte)	\
	(mm_tlb_flush_pending(mm) ? pte_present(pte) : pte_valid(pte))

/*
 * p??_access_permitted() is true क्रम valid user mappings (PTE_USER
 * bit set, subject to the ग_लिखो permission check). For execute-only
 * mappings, like PROT_EXEC with EPAN (both PTE_USER and PTE_UXN bits
 * not set) must वापस false. PROT_NONE mappings करो not have the
 * PTE_VALID bit set.
 */
#घोषणा pte_access_permitted(pte, ग_लिखो) \
	(((pte_val(pte) & (PTE_VALID | PTE_USER)) == (PTE_VALID | PTE_USER)) && (!(ग_लिखो) || pte_ग_लिखो(pte)))
#घोषणा pmd_access_permitted(pmd, ग_लिखो) \
	(pte_access_permitted(pmd_pte(pmd), (ग_लिखो)))
#घोषणा pud_access_permitted(pud, ग_लिखो) \
	(pte_access_permitted(pud_pte(pud), (ग_लिखो)))

अटल अंतरभूत pte_t clear_pte_bit(pte_t pte, pgprot_t prot)
अणु
	pte_val(pte) &= ~pgprot_val(prot);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t set_pte_bit(pte_t pte, pgprot_t prot)
अणु
	pte_val(pte) |= pgprot_val(prot);
	वापस pte;
पूर्ण

अटल अंतरभूत pmd_t clear_pmd_bit(pmd_t pmd, pgprot_t prot)
अणु
	pmd_val(pmd) &= ~pgprot_val(prot);
	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t set_pmd_bit(pmd_t pmd, pgprot_t prot)
अणु
	pmd_val(pmd) |= pgprot_val(prot);
	वापस pmd;
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	pte = set_pte_bit(pte, __pgprot(PTE_WRITE));
	pte = clear_pte_bit(pte, __pgprot(PTE_RDONLY));
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	pte = clear_pte_bit(pte, __pgprot(PTE_सूचीTY));
	pte = set_pte_bit(pte, __pgprot(PTE_RDONLY));

	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	pte = set_pte_bit(pte, __pgprot(PTE_सूचीTY));

	अगर (pte_ग_लिखो(pte))
		pte = clear_pte_bit(pte, __pgprot(PTE_RDONLY));

	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	/*
	 * If hardware-dirty (PTE_WRITE/DBM bit set and PTE_RDONLY
	 * clear), set the PTE_सूचीTY bit.
	 */
	अगर (pte_hw_dirty(pte))
		pte = pte_सूची_गढ़ोty(pte);

	pte = clear_pte_bit(pte, __pgprot(PTE_WRITE));
	pte = set_pte_bit(pte, __pgprot(PTE_RDONLY));
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	वापस clear_pte_bit(pte, __pgprot(PTE_AF));
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	वापस set_pte_bit(pte, __pgprot(PTE_AF));
पूर्ण

अटल अंतरभूत pte_t pte_mkspecial(pte_t pte)
अणु
	वापस set_pte_bit(pte, __pgprot(PTE_SPECIAL));
पूर्ण

अटल अंतरभूत pte_t pte_mkcont(pte_t pte)
अणु
	pte = set_pte_bit(pte, __pgprot(PTE_CONT));
	वापस set_pte_bit(pte, __pgprot(PTE_TYPE_PAGE));
पूर्ण

अटल अंतरभूत pte_t pte_mknoncont(pte_t pte)
अणु
	वापस clear_pte_bit(pte, __pgprot(PTE_CONT));
पूर्ण

अटल अंतरभूत pte_t pte_mkpresent(pte_t pte)
अणु
	वापस set_pte_bit(pte, __pgprot(PTE_VALID));
पूर्ण

अटल अंतरभूत pmd_t pmd_mkcont(pmd_t pmd)
अणु
	वापस __pmd(pmd_val(pmd) | PMD_SECT_CONT);
पूर्ण

अटल अंतरभूत pte_t pte_mkdevmap(pte_t pte)
अणु
	वापस set_pte_bit(pte, __pgprot(PTE_DEVMAP | PTE_SPECIAL));
पूर्ण

अटल अंतरभूत व्योम set_pte(pte_t *ptep, pte_t pte)
अणु
	WRITE_ONCE(*ptep, pte);

	/*
	 * Only अगर the new pte is valid and kernel, otherwise TLB मुख्यtenance
	 * or update_mmu_cache() have the necessary barriers.
	 */
	अगर (pte_valid_not_user(pte)) अणु
		dsb(ishst);
		isb();
	पूर्ण
पूर्ण

बाह्य व्योम __sync_icache_dcache(pte_t pteval);

/*
 * PTE bits configuration in the presence of hardware Dirty Bit Management
 * (PTE_WRITE == PTE_DBM):
 *
 * Dirty  Writable | PTE_RDONLY  PTE_WRITE  PTE_सूचीTY (sw)
 *   0      0      |   1           0          0
 *   0      1      |   1           1          0
 *   1      0      |   1           0          1
 *   1      1      |   0           1          x
 *
 * When hardware DBM is not present, the sofware PTE_सूचीTY bit is updated via
 * the page fault mechanism. Checking the dirty status of a pte becomes:
 *
 *   PTE_सूचीTY || (PTE_WRITE && !PTE_RDONLY)
 */

अटल अंतरभूत व्योम __check_racy_pte_update(काष्ठा mm_काष्ठा *mm, pte_t *ptep,
					   pte_t pte)
अणु
	pte_t old_pte;

	अगर (!IS_ENABLED(CONFIG_DEBUG_VM))
		वापस;

	old_pte = READ_ONCE(*ptep);

	अगर (!pte_valid(old_pte) || !pte_valid(pte))
		वापस;
	अगर (mm != current->active_mm && atomic_पढ़ो(&mm->mm_users) <= 1)
		वापस;

	/*
	 * Check क्रम potential race with hardware updates of the pte
	 * (ptep_set_access_flags safely changes valid ptes without going
	 * through an invalid entry).
	 */
	VM_WARN_ONCE(!pte_young(pte),
		     "%s: racy access flag clearing: 0x%016llx -> 0x%016llx",
		     __func__, pte_val(old_pte), pte_val(pte));
	VM_WARN_ONCE(pte_ग_लिखो(old_pte) && !pte_dirty(pte),
		     "%s: racy dirty state clearing: 0x%016llx -> 0x%016llx",
		     __func__, pte_val(old_pte), pte_val(pte));
पूर्ण

अटल अंतरभूत व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *ptep, pte_t pte)
अणु
	अगर (pte_present(pte) && pte_user_exec(pte) && !pte_special(pte))
		__sync_icache_dcache(pte);

	अगर (प्रणाली_supports_mte() &&
	    pte_present(pte) && pte_tagged(pte) && !pte_special(pte))
		mte_sync_tags(ptep, pte);

	__check_racy_pte_update(mm, ptep, pte);

	set_pte(ptep, pte);
पूर्ण

/*
 * Huge pte definitions.
 */
#घोषणा pte_mkhuge(pte)		(__pte(pte_val(pte) & ~PTE_TABLE_BIT))

/*
 * Hugetlb definitions.
 */
#घोषणा HUGE_MAX_HSTATE		4
#घोषणा HPAGE_SHIFT		PMD_SHIFT
#घोषणा HPAGE_SIZE		(_AC(1, UL) << HPAGE_SHIFT)
#घोषणा HPAGE_MASK		(~(HPAGE_SIZE - 1))
#घोषणा HUGETLB_PAGE_ORDER	(HPAGE_SHIFT - PAGE_SHIFT)

अटल अंतरभूत pte_t pgd_pte(pgd_t pgd)
अणु
	वापस __pte(pgd_val(pgd));
पूर्ण

अटल अंतरभूत pte_t p4d_pte(p4d_t p4d)
अणु
	वापस __pte(p4d_val(p4d));
पूर्ण

अटल अंतरभूत pte_t pud_pte(pud_t pud)
अणु
	वापस __pte(pud_val(pud));
पूर्ण

अटल अंतरभूत pud_t pte_pud(pte_t pte)
अणु
	वापस __pud(pte_val(pte));
पूर्ण

अटल अंतरभूत pmd_t pud_pmd(pud_t pud)
अणु
	वापस __pmd(pud_val(pud));
पूर्ण

अटल अंतरभूत pte_t pmd_pte(pmd_t pmd)
अणु
	वापस __pte(pmd_val(pmd));
पूर्ण

अटल अंतरभूत pmd_t pte_pmd(pte_t pte)
अणु
	वापस __pmd(pte_val(pte));
पूर्ण

अटल अंतरभूत pgprot_t mk_pud_sect_prot(pgprot_t prot)
अणु
	वापस __pgprot((pgprot_val(prot) & ~PUD_TABLE_BIT) | PUD_TYPE_SECT);
पूर्ण

अटल अंतरभूत pgprot_t mk_pmd_sect_prot(pgprot_t prot)
अणु
	वापस __pgprot((pgprot_val(prot) & ~PMD_TABLE_BIT) | PMD_TYPE_SECT);
पूर्ण

#अगर_घोषित CONFIG_NUMA_BALANCING
/*
 * See the comment in include/linux/pgtable.h
 */
अटल अंतरभूत पूर्णांक pte_protnone(pte_t pte)
अणु
	वापस (pte_val(pte) & (PTE_VALID | PTE_PROT_NONE)) == PTE_PROT_NONE;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_protnone(pmd_t pmd)
अणु
	वापस pte_protnone(pmd_pte(pmd));
पूर्ण
#पूर्ण_अगर

#घोषणा pmd_present_invalid(pmd)     (!!(pmd_val(pmd) & PMD_PRESENT_INVALID))

अटल अंतरभूत पूर्णांक pmd_present(pmd_t pmd)
अणु
	वापस pte_present(pmd_pte(pmd)) || pmd_present_invalid(pmd);
पूर्ण

/*
 * THP definitions.
 */

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत पूर्णांक pmd_trans_huge(pmd_t pmd)
अणु
	वापस pmd_val(pmd) && pmd_present(pmd) && !(pmd_val(pmd) & PMD_TABLE_BIT);
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

#घोषणा pmd_dirty(pmd)		pte_dirty(pmd_pte(pmd))
#घोषणा pmd_young(pmd)		pte_young(pmd_pte(pmd))
#घोषणा pmd_valid(pmd)		pte_valid(pmd_pte(pmd))
#घोषणा pmd_cont(pmd)		pte_cont(pmd_pte(pmd))
#घोषणा pmd_wrprotect(pmd)	pte_pmd(pte_wrprotect(pmd_pte(pmd)))
#घोषणा pmd_mkold(pmd)		pte_pmd(pte_mkold(pmd_pte(pmd)))
#घोषणा pmd_mkग_लिखो(pmd)	pte_pmd(pte_mkग_लिखो(pmd_pte(pmd)))
#घोषणा pmd_mkclean(pmd)	pte_pmd(pte_mkclean(pmd_pte(pmd)))
#घोषणा pmd_सूची_गढ़ोty(pmd)	pte_pmd(pte_सूची_गढ़ोty(pmd_pte(pmd)))
#घोषणा pmd_mkyoung(pmd)	pte_pmd(pte_mkyoung(pmd_pte(pmd)))

अटल अंतरभूत pmd_t pmd_mkinvalid(pmd_t pmd)
अणु
	pmd = set_pmd_bit(pmd, __pgprot(PMD_PRESENT_INVALID));
	pmd = clear_pmd_bit(pmd, __pgprot(PMD_SECT_VALID));

	वापस pmd;
पूर्ण

#घोषणा pmd_thp_or_huge(pmd)	(pmd_huge(pmd) || pmd_trans_huge(pmd))

#घोषणा pmd_ग_लिखो(pmd)		pte_ग_लिखो(pmd_pte(pmd))

#घोषणा pmd_mkhuge(pmd)		(__pmd(pmd_val(pmd) & ~PMD_TABLE_BIT))

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा pmd_devmap(pmd)		pte_devmap(pmd_pte(pmd))
#पूर्ण_अगर
अटल अंतरभूत pmd_t pmd_mkdevmap(pmd_t pmd)
अणु
	वापस pte_pmd(set_pte_bit(pmd_pte(pmd), __pgprot(PTE_DEVMAP)));
पूर्ण

#घोषणा __pmd_to_phys(pmd)	__pte_to_phys(pmd_pte(pmd))
#घोषणा __phys_to_pmd_val(phys)	__phys_to_pte_val(phys)
#घोषणा pmd_pfn(pmd)		((__pmd_to_phys(pmd) & PMD_MASK) >> PAGE_SHIFT)
#घोषणा pfn_pmd(pfn,prot)	__pmd(__phys_to_pmd_val((phys_addr_t)(pfn) << PAGE_SHIFT) | pgprot_val(prot))
#घोषणा mk_pmd(page,prot)	pfn_pmd(page_to_pfn(page),prot)

#घोषणा pud_young(pud)		pte_young(pud_pte(pud))
#घोषणा pud_mkyoung(pud)	pte_pud(pte_mkyoung(pud_pte(pud)))
#घोषणा pud_ग_लिखो(pud)		pte_ग_लिखो(pud_pte(pud))

#घोषणा pud_mkhuge(pud)		(__pud(pud_val(pud) & ~PUD_TABLE_BIT))

#घोषणा __pud_to_phys(pud)	__pte_to_phys(pud_pte(pud))
#घोषणा __phys_to_pud_val(phys)	__phys_to_pte_val(phys)
#घोषणा pud_pfn(pud)		((__pud_to_phys(pud) & PUD_MASK) >> PAGE_SHIFT)
#घोषणा pfn_pud(pfn,prot)	__pud(__phys_to_pud_val((phys_addr_t)(pfn) << PAGE_SHIFT) | pgprot_val(prot))

#घोषणा set_pmd_at(mm, addr, pmdp, pmd)	set_pte_at(mm, addr, (pte_t *)pmdp, pmd_pte(pmd))
#घोषणा set_pud_at(mm, addr, pudp, pud)	set_pte_at(mm, addr, (pte_t *)pudp, pud_pte(pud))

#घोषणा __p4d_to_phys(p4d)	__pte_to_phys(p4d_pte(p4d))
#घोषणा __phys_to_p4d_val(phys)	__phys_to_pte_val(phys)

#घोषणा __pgd_to_phys(pgd)	__pte_to_phys(pgd_pte(pgd))
#घोषणा __phys_to_pgd_val(phys)	__phys_to_pte_val(phys)

#घोषणा __pgprot_modअगरy(prot,mask,bits) \
	__pgprot((pgprot_val(prot) & ~(mask)) | (bits))

#घोषणा pgprot_nx(prot) \
	__pgprot_modअगरy(prot, PTE_MAYBE_GP, PTE_PXN)

/*
 * Mark the prot value as uncacheable and unbufferable.
 */
#घोषणा pgprot_noncached(prot) \
	__pgprot_modअगरy(prot, PTE_ATTRINDX_MASK, PTE_ATTRINDX(MT_DEVICE_nGnRnE) | PTE_PXN | PTE_UXN)
#घोषणा pgprot_ग_लिखोcombine(prot) \
	__pgprot_modअगरy(prot, PTE_ATTRINDX_MASK, PTE_ATTRINDX(MT_NORMAL_NC) | PTE_PXN | PTE_UXN)
#घोषणा pgprot_device(prot) \
	__pgprot_modअगरy(prot, PTE_ATTRINDX_MASK, PTE_ATTRINDX(MT_DEVICE_nGnRE) | PTE_PXN | PTE_UXN)
#घोषणा pgprot_tagged(prot) \
	__pgprot_modअगरy(prot, PTE_ATTRINDX_MASK, PTE_ATTRINDX(MT_NORMAL_TAGGED))
#घोषणा pgprot_mhp	pgprot_tagged
/*
 * DMA allocations क्रम non-coherent devices use what the Arm architecture calls
 * "Normal non-cacheable" memory, which permits speculation, unaligned accesses
 * and merging of ग_लिखोs.  This is dअगरferent from "Device-nGnR[nE]" memory which
 * is पूर्णांकended क्रम MMIO and thus क्रमbids speculation, preserves access size,
 * requires strict alignment and can also क्रमce ग_लिखो responses to come from the
 * endpoपूर्णांक.
 */
#घोषणा pgprot_dmacoherent(prot) \
	__pgprot_modअगरy(prot, PTE_ATTRINDX_MASK, \
			PTE_ATTRINDX(MT_NORMAL_NC) | PTE_PXN | PTE_UXN)

#घोषणा __HAVE_PHYS_MEM_ACCESS_PROT
काष्ठा file;
बाह्य pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
				     अचिन्हित दीर्घ size, pgprot_t vma_prot);

#घोषणा pmd_none(pmd)		(!pmd_val(pmd))

#घोषणा pmd_bad(pmd)		(!(pmd_val(pmd) & PMD_TABLE_BIT))

#घोषणा pmd_table(pmd)		((pmd_val(pmd) & PMD_TYPE_MASK) == \
				 PMD_TYPE_TABLE)
#घोषणा pmd_sect(pmd)		((pmd_val(pmd) & PMD_TYPE_MASK) == \
				 PMD_TYPE_SECT)
#घोषणा pmd_leaf(pmd)		pmd_sect(pmd)

#घोषणा pmd_leaf_size(pmd)	(pmd_cont(pmd) ? CONT_PMD_SIZE : PMD_SIZE)
#घोषणा pte_leaf_size(pte)	(pte_cont(pte) ? CONT_PTE_SIZE : PAGE_SIZE)

#अगर defined(CONFIG_ARM64_64K_PAGES) || CONFIG_PGTABLE_LEVELS < 3
अटल अंतरभूत bool pud_sect(pud_t pud) अणु वापस false; पूर्ण
अटल अंतरभूत bool pud_table(pud_t pud) अणु वापस true; पूर्ण
#अन्यथा
#घोषणा pud_sect(pud)		((pud_val(pud) & PUD_TYPE_MASK) == \
				 PUD_TYPE_SECT)
#घोषणा pud_table(pud)		((pud_val(pud) & PUD_TYPE_MASK) == \
				 PUD_TYPE_TABLE)
#पूर्ण_अगर

बाह्य pgd_t init_pg_dir[PTRS_PER_PGD];
बाह्य pgd_t init_pg_end[];
बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];
बाह्य pgd_t idmap_pg_dir[PTRS_PER_PGD];
बाह्य pgd_t idmap_pg_end[];
बाह्य pgd_t tramp_pg_dir[PTRS_PER_PGD];
बाह्य pgd_t reserved_pg_dir[PTRS_PER_PGD];

बाह्य व्योम set_swapper_pgd(pgd_t *pgdp, pgd_t pgd);

अटल अंतरभूत bool in_swapper_pgdir(व्योम *addr)
अणु
	वापस ((अचिन्हित दीर्घ)addr & PAGE_MASK) ==
	        ((अचिन्हित दीर्घ)swapper_pg_dir & PAGE_MASK);
पूर्ण

अटल अंतरभूत व्योम set_pmd(pmd_t *pmdp, pmd_t pmd)
अणु
#अगर_घोषित __PAGETABLE_PMD_FOLDED
	अगर (in_swapper_pgdir(pmdp)) अणु
		set_swapper_pgd((pgd_t *)pmdp, __pgd(pmd_val(pmd)));
		वापस;
	पूर्ण
#पूर्ण_अगर /* __PAGETABLE_PMD_FOLDED */

	WRITE_ONCE(*pmdp, pmd);

	अगर (pmd_valid(pmd)) अणु
		dsb(ishst);
		isb();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp)
अणु
	set_pmd(pmdp, __pmd(0));
पूर्ण

अटल अंतरभूत phys_addr_t pmd_page_paddr(pmd_t pmd)
अणु
	वापस __pmd_to_phys(pmd);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस (अचिन्हित दीर्घ)__va(pmd_page_paddr(pmd));
पूर्ण

/* Find an entry in the third-level page table. */
#घोषणा pte_offset_phys(dir,addr)	(pmd_page_paddr(READ_ONCE(*(dir))) + pte_index(addr) * माप(pte_t))

#घोषणा pte_set_fixmap(addr)		((pte_t *)set_fixmap_offset(FIX_PTE, addr))
#घोषणा pte_set_fixmap_offset(pmd, addr)	pte_set_fixmap(pte_offset_phys(pmd, addr))
#घोषणा pte_clear_fixmap()		clear_fixmap(FIX_PTE)

#घोषणा pmd_page(pmd)			phys_to_page(__pmd_to_phys(pmd))

/* use ONLY क्रम अटलally allocated translation tables */
#घोषणा pte_offset_kimg(dir,addr)	((pte_t *)__phys_to_kimg(pte_offset_phys((dir), (addr))))

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
#घोषणा mk_pte(page,prot)	pfn_pte(page_to_pfn(page),prot)

#अगर CONFIG_PGTABLE_LEVELS > 2

#घोषणा pmd_ERROR(e)	\
	pr_err("%s:%d: bad pmd %016llx.\n", __खाता__, __LINE__, pmd_val(e))

#घोषणा pud_none(pud)		(!pud_val(pud))
#घोषणा pud_bad(pud)		(!(pud_val(pud) & PUD_TABLE_BIT))
#घोषणा pud_present(pud)	pte_present(pud_pte(pud))
#घोषणा pud_leaf(pud)		pud_sect(pud)
#घोषणा pud_valid(pud)		pte_valid(pud_pte(pud))

अटल अंतरभूत व्योम set_pud(pud_t *pudp, pud_t pud)
अणु
#अगर_घोषित __PAGETABLE_PUD_FOLDED
	अगर (in_swapper_pgdir(pudp)) अणु
		set_swapper_pgd((pgd_t *)pudp, __pgd(pud_val(pud)));
		वापस;
	पूर्ण
#पूर्ण_अगर /* __PAGETABLE_PUD_FOLDED */

	WRITE_ONCE(*pudp, pud);

	अगर (pud_valid(pud)) अणु
		dsb(ishst);
		isb();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pud_clear(pud_t *pudp)
अणु
	set_pud(pudp, __pud(0));
पूर्ण

अटल अंतरभूत phys_addr_t pud_page_paddr(pud_t pud)
अणु
	वापस __pud_to_phys(pud);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pud_page_vaddr(pud_t pud)
अणु
	वापस (अचिन्हित दीर्घ)__va(pud_page_paddr(pud));
पूर्ण

/* Find an entry in the second-level page table. */
#घोषणा pmd_offset_phys(dir, addr)	(pud_page_paddr(READ_ONCE(*(dir))) + pmd_index(addr) * माप(pmd_t))

#घोषणा pmd_set_fixmap(addr)		((pmd_t *)set_fixmap_offset(FIX_PMD, addr))
#घोषणा pmd_set_fixmap_offset(pud, addr)	pmd_set_fixmap(pmd_offset_phys(pud, addr))
#घोषणा pmd_clear_fixmap()		clear_fixmap(FIX_PMD)

#घोषणा pud_page(pud)			phys_to_page(__pud_to_phys(pud))

/* use ONLY क्रम अटलally allocated translation tables */
#घोषणा pmd_offset_kimg(dir,addr)	((pmd_t *)__phys_to_kimg(pmd_offset_phys((dir), (addr))))

#अन्यथा

#घोषणा pud_page_paddr(pud)	(अणु BUILD_BUG(); 0; पूर्ण)

/* Match pmd_offset folding in <यंत्र/generic/pgtable-nopmd.h> */
#घोषणा pmd_set_fixmap(addr)		शून्य
#घोषणा pmd_set_fixmap_offset(pudp, addr)	((pmd_t *)pudp)
#घोषणा pmd_clear_fixmap()

#घोषणा pmd_offset_kimg(dir,addr)	((pmd_t *)dir)

#पूर्ण_अगर	/* CONFIG_PGTABLE_LEVELS > 2 */

#अगर CONFIG_PGTABLE_LEVELS > 3

#घोषणा pud_ERROR(e)	\
	pr_err("%s:%d: bad pud %016llx.\n", __खाता__, __LINE__, pud_val(e))

#घोषणा p4d_none(p4d)		(!p4d_val(p4d))
#घोषणा p4d_bad(p4d)		(!(p4d_val(p4d) & 2))
#घोषणा p4d_present(p4d)	(p4d_val(p4d))

अटल अंतरभूत व्योम set_p4d(p4d_t *p4dp, p4d_t p4d)
अणु
	अगर (in_swapper_pgdir(p4dp)) अणु
		set_swapper_pgd((pgd_t *)p4dp, __pgd(p4d_val(p4d)));
		वापस;
	पूर्ण

	WRITE_ONCE(*p4dp, p4d);
	dsb(ishst);
	isb();
पूर्ण

अटल अंतरभूत व्योम p4d_clear(p4d_t *p4dp)
अणु
	set_p4d(p4dp, __p4d(0));
पूर्ण

अटल अंतरभूत phys_addr_t p4d_page_paddr(p4d_t p4d)
अणु
	वापस __p4d_to_phys(p4d);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ p4d_page_vaddr(p4d_t p4d)
अणु
	वापस (अचिन्हित दीर्घ)__va(p4d_page_paddr(p4d));
पूर्ण

/* Find an entry in the frst-level page table. */
#घोषणा pud_offset_phys(dir, addr)	(p4d_page_paddr(READ_ONCE(*(dir))) + pud_index(addr) * माप(pud_t))

#घोषणा pud_set_fixmap(addr)		((pud_t *)set_fixmap_offset(FIX_PUD, addr))
#घोषणा pud_set_fixmap_offset(p4d, addr)	pud_set_fixmap(pud_offset_phys(p4d, addr))
#घोषणा pud_clear_fixmap()		clear_fixmap(FIX_PUD)

#घोषणा p4d_page(p4d)		pfn_to_page(__phys_to_pfn(__p4d_to_phys(p4d)))

/* use ONLY क्रम अटलally allocated translation tables */
#घोषणा pud_offset_kimg(dir,addr)	((pud_t *)__phys_to_kimg(pud_offset_phys((dir), (addr))))

#अन्यथा

#घोषणा p4d_page_paddr(p4d)	(अणु BUILD_BUG(); 0;पूर्ण)
#घोषणा pgd_page_paddr(pgd)	(अणु BUILD_BUG(); 0;पूर्ण)

/* Match pud_offset folding in <यंत्र/generic/pgtable-nopud.h> */
#घोषणा pud_set_fixmap(addr)		शून्य
#घोषणा pud_set_fixmap_offset(pgdp, addr)	((pud_t *)pgdp)
#घोषणा pud_clear_fixmap()

#घोषणा pud_offset_kimg(dir,addr)	((pud_t *)dir)

#पूर्ण_अगर  /* CONFIG_PGTABLE_LEVELS > 3 */

#घोषणा pgd_ERROR(e)	\
	pr_err("%s:%d: bad pgd %016llx.\n", __खाता__, __LINE__, pgd_val(e))

#घोषणा pgd_set_fixmap(addr)	((pgd_t *)set_fixmap_offset(FIX_PGD, addr))
#घोषणा pgd_clear_fixmap()	clear_fixmap(FIX_PGD)

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	/*
	 * Normal and Normal-Tagged are two dअगरferent memory types and indices
	 * in MAIR_EL1. The mask below has to include PTE_ATTRINDX_MASK.
	 */
	स्थिर pteval_t mask = PTE_USER | PTE_PXN | PTE_UXN | PTE_RDONLY |
			      PTE_PROT_NONE | PTE_VALID | PTE_WRITE | PTE_GP |
			      PTE_ATTRINDX_MASK;
	/* preserve the hardware dirty inक्रमmation */
	अगर (pte_hw_dirty(pte))
		pte = pte_सूची_गढ़ोty(pte);
	pte_val(pte) = (pte_val(pte) & ~mask) | (pgprot_val(newprot) & mask);
	वापस pte;
पूर्ण

अटल अंतरभूत pmd_t pmd_modअगरy(pmd_t pmd, pgprot_t newprot)
अणु
	वापस pte_pmd(pte_modअगरy(pmd_pte(pmd), newprot));
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
बाह्य पूर्णांक ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ address, pte_t *ptep,
				 pte_t entry, पूर्णांक dirty);

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा __HAVE_ARCH_PMDP_SET_ACCESS_FLAGS
अटल अंतरभूत पूर्णांक pmdp_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ address, pmd_t *pmdp,
					pmd_t entry, पूर्णांक dirty)
अणु
	वापस ptep_set_access_flags(vma, address, (pte_t *)pmdp, pmd_pte(entry), dirty);
पूर्ण

अटल अंतरभूत पूर्णांक pud_devmap(pud_t pud)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pgd_devmap(pgd_t pgd)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Atomic pte/pmd modअगरications.
 */
#घोषणा __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
अटल अंतरभूत पूर्णांक __ptep_test_and_clear_young(pte_t *ptep)
अणु
	pte_t old_pte, pte;

	pte = READ_ONCE(*ptep);
	करो अणु
		old_pte = pte;
		pte = pte_mkold(pte);
		pte_val(pte) = cmpxchg_relaxed(&pte_val(*ptep),
					       pte_val(old_pte), pte_val(pte));
	पूर्ण जबतक (pte_val(pte) != pte_val(old_pte));

	वापस pte_young(pte);
पूर्ण

अटल अंतरभूत पूर्णांक ptep_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
					    अचिन्हित दीर्घ address,
					    pte_t *ptep)
अणु
	वापस __ptep_test_and_clear_young(ptep);
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
अटल अंतरभूत पूर्णांक ptep_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	पूर्णांक young = ptep_test_and_clear_young(vma, address, ptep);

	अगर (young) अणु
		/*
		 * We can elide the trailing DSB here since the worst that can
		 * happen is that a CPU जारीs to use the young entry in its
		 * TLB and we mistakenly reclaim the associated page. The
		 * winकरोw क्रम such an event is bounded by the next
		 * context-चयन, which provides a DSB to complete the TLB
		 * invalidation.
		 */
		flush_tlb_page_nosync(vma, address);
	पूर्ण

	वापस young;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा __HAVE_ARCH_PMDP_TEST_AND_CLEAR_YOUNG
अटल अंतरभूत पूर्णांक pmdp_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
					    अचिन्हित दीर्घ address,
					    pmd_t *pmdp)
अणु
	वापस ptep_test_and_clear_young(vma, address, (pte_t *)pmdp);
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
				       अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	वापस __pte(xchg_relaxed(&pte_val(*ptep), 0));
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR
अटल अंतरभूत pmd_t pmdp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ address, pmd_t *pmdp)
अणु
	वापस pte_pmd(ptep_get_and_clear(mm, address, (pte_t *)pmdp));
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

/*
 * ptep_set_wrprotect - mark पढ़ो-only जबतक trasferring potential hardware
 * dirty status (PTE_DBM && !PTE_RDONLY) to the software PTE_सूचीTY bit.
 */
#घोषणा __HAVE_ARCH_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	pte_t old_pte, pte;

	pte = READ_ONCE(*ptep);
	करो अणु
		old_pte = pte;
		pte = pte_wrprotect(pte);
		pte_val(pte) = cmpxchg_relaxed(&pte_val(*ptep),
					       pte_val(old_pte), pte_val(pte));
	पूर्ण जबतक (pte_val(pte) != pte_val(old_pte));
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा __HAVE_ARCH_PMDP_SET_WRPROTECT
अटल अंतरभूत व्योम pmdp_set_wrprotect(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ address, pmd_t *pmdp)
अणु
	ptep_set_wrprotect(mm, address, (pte_t *)pmdp);
पूर्ण

#घोषणा pmdp_establish pmdp_establish
अटल अंतरभूत pmd_t pmdp_establish(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, pmd_t *pmdp, pmd_t pmd)
अणु
	वापस __pmd(xchg_relaxed(&pmd_val(*pmdp), pmd_val(pmd)));
पूर्ण
#पूर्ण_अगर

/*
 * Encode and decode a swap entry:
 *	bits 0-1:	present (must be zero)
 *	bits 2-7:	swap type
 *	bits 8-57:	swap offset
 *	bit  58:	PTE_PROT_NONE (must be zero)
 */
#घोषणा __SWP_TYPE_SHIFT	2
#घोषणा __SWP_TYPE_BITS		6
#घोषणा __SWP_OFFSET_BITS	50
#घोषणा __SWP_TYPE_MASK		((1 << __SWP_TYPE_BITS) - 1)
#घोषणा __SWP_OFFSET_SHIFT	(__SWP_TYPE_BITS + __SWP_TYPE_SHIFT)
#घोषणा __SWP_OFFSET_MASK	((1UL << __SWP_OFFSET_BITS) - 1)

#घोषणा __swp_type(x)		(((x).val >> __SWP_TYPE_SHIFT) & __SWP_TYPE_MASK)
#घोषणा __swp_offset(x)		(((x).val >> __SWP_OFFSET_SHIFT) & __SWP_OFFSET_MASK)
#घोषणा __swp_entry(type,offset) ((swp_entry_t) अणु ((type) << __SWP_TYPE_SHIFT) | ((offset) << __SWP_OFFSET_SHIFT) पूर्ण)

#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(swp)	((pte_t) अणु (swp).val पूर्ण)

#अगर_घोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
#घोषणा __pmd_to_swp_entry(pmd)		((swp_entry_t) अणु pmd_val(pmd) पूर्ण)
#घोषणा __swp_entry_to_pmd(swp)		__pmd((swp).val)
#पूर्ण_अगर /* CONFIG_ARCH_ENABLE_THP_MIGRATION */

/*
 * Ensure that there are not more swap files than can be encoded in the kernel
 * PTEs.
 */
#घोषणा MAX_SWAPखाताS_CHECK() BUILD_BUG_ON(MAX_SWAPखाताS_SHIFT > __SWP_TYPE_BITS)

बाह्य पूर्णांक kern_addr_valid(अचिन्हित दीर्घ addr);

#अगर_घोषित CONFIG_ARM64_MTE

#घोषणा __HAVE_ARCH_PREPARE_TO_SWAP
अटल अंतरभूत पूर्णांक arch_prepare_to_swap(काष्ठा page *page)
अणु
	अगर (प्रणाली_supports_mte())
		वापस mte_save_tags(page);
	वापस 0;
पूर्ण

#घोषणा __HAVE_ARCH_SWAP_INVALIDATE
अटल अंतरभूत व्योम arch_swap_invalidate_page(पूर्णांक type, pgoff_t offset)
अणु
	अगर (प्रणाली_supports_mte())
		mte_invalidate_tags(type, offset);
पूर्ण

अटल अंतरभूत व्योम arch_swap_invalidate_area(पूर्णांक type)
अणु
	अगर (प्रणाली_supports_mte())
		mte_invalidate_tags_area(type);
पूर्ण

#घोषणा __HAVE_ARCH_SWAP_RESTORE
अटल अंतरभूत व्योम arch_swap_restore(swp_entry_t entry, काष्ठा page *page)
अणु
	अगर (प्रणाली_supports_mte() && mte_restore_tags(entry, page))
		set_bit(PG_mte_tagged, &page->flags);
पूर्ण

#पूर्ण_अगर /* CONFIG_ARM64_MTE */

/*
 * On AArch64, the cache coherency is handled via the set_pte_at() function.
 */
अटल अंतरभूत व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	/*
	 * We करोn't do anything here, so there's a very small chance of
	 * us retaking a user fault which we just fixed up. The alternative
	 * is करोing a dsb(ishst), but that penalises the fastpath.
	 */
पूर्ण

#घोषणा update_mmu_cache_pmd(vma, address, pmd) करो अणु पूर्ण जबतक (0)

#अगर_घोषित CONFIG_ARM64_PA_BITS_52
#घोषणा phys_to_ttbr(addr)	(((addr) | ((addr) >> 46)) & TTBR_BADDR_MASK_52)
#अन्यथा
#घोषणा phys_to_ttbr(addr)	(addr)
#पूर्ण_अगर

/*
 * On arm64 without hardware Access Flag, copying from user will fail because
 * the pte is old and cannot be marked young. So we always end up with zeroed
 * page after विभाजन() + CoW क्रम pfn mappings. We करोn't always have a
 * hardware-managed access flag on arm64.
 */
अटल अंतरभूत bool arch_faults_on_old_pte(व्योम)
अणु
	WARN_ON(preemptible());

	वापस !cpu_has_hw_af();
पूर्ण
#घोषणा arch_faults_on_old_pte		arch_faults_on_old_pte

/*
 * Experimentally, it's cheap to set the access flag in hardware and we
 * benefit from prefaulting mappings as 'old' to start with.
 */
अटल अंतरभूत bool arch_wants_old_prefaulted_pte(व्योम)
अणु
	वापस !arch_faults_on_old_pte();
पूर्ण
#घोषणा arch_wants_old_prefaulted_pte	arch_wants_old_prefaulted_pte

अटल अंतरभूत pgprot_t arch_filter_pgprot(pgprot_t prot)
अणु
	अगर (cpus_have_स्थिर_cap(ARM64_HAS_EPAN))
		वापस prot;

	अगर (pgprot_val(prot) != pgprot_val(PAGE_EXECONLY))
		वापस prot;

	वापस PAGE_READONLY_EXEC;
पूर्ण


#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_PGTABLE_H */
