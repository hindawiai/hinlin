<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/pagewalk.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

/**
 * काष्ठा wp_walk - Private काष्ठा क्रम pagetable walk callbacks
 * @range: Range क्रम mmu notअगरiers
 * @tlbflush_start: Address of first modअगरied pte
 * @tlbflush_end: Address of last modअगरied pte + 1
 * @total: Total number of modअगरied ptes
 */
काष्ठा wp_walk अणु
	काष्ठा mmu_notअगरier_range range;
	अचिन्हित दीर्घ tlbflush_start;
	अचिन्हित दीर्घ tlbflush_end;
	अचिन्हित दीर्घ total;
पूर्ण;

/**
 * wp_pte - Write-protect a pte
 * @pte: Poपूर्णांकer to the pte
 * @addr: The start of protecting भव address
 * @end: The end of protecting भव address
 * @walk: pagetable walk callback argument
 *
 * The function ग_लिखो-protects a pte and records the range in
 * भव address space of touched ptes क्रम efficient range TLB flushes.
 */
अटल पूर्णांक wp_pte(pte_t *pte, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		  काष्ठा mm_walk *walk)
अणु
	काष्ठा wp_walk *wpwalk = walk->निजी;
	pte_t ptent = *pte;

	अगर (pte_ग_लिखो(ptent)) अणु
		pte_t old_pte = ptep_modअगरy_prot_start(walk->vma, addr, pte);

		ptent = pte_wrprotect(old_pte);
		ptep_modअगरy_prot_commit(walk->vma, addr, pte, old_pte, ptent);
		wpwalk->total++;
		wpwalk->tlbflush_start = min(wpwalk->tlbflush_start, addr);
		wpwalk->tlbflush_end = max(wpwalk->tlbflush_end,
					   addr + PAGE_SIZE);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * काष्ठा clean_walk - Private काष्ठा क्रम the clean_record_pte function.
 * @base: काष्ठा wp_walk we derive from
 * @biपंचांगap_pgoff: Address_space Page offset of the first bit in @biपंचांगap
 * @biपंचांगap: Biपंचांगap with one bit क्रम each page offset in the address_space range
 * covered.
 * @start: Address_space page offset of first modअगरied pte relative
 * to @biपंचांगap_pgoff
 * @end: Address_space page offset of last modअगरied pte relative
 * to @biपंचांगap_pgoff
 */
काष्ठा clean_walk अणु
	काष्ठा wp_walk base;
	pgoff_t biपंचांगap_pgoff;
	अचिन्हित दीर्घ *biपंचांगap;
	pgoff_t start;
	pgoff_t end;
पूर्ण;

#घोषणा to_clean_walk(_wpwalk) container_of(_wpwalk, काष्ठा clean_walk, base)

/**
 * clean_record_pte - Clean a pte and record its address space offset in a
 * biपंचांगap
 * @pte: Poपूर्णांकer to the pte
 * @addr: The start of भव address to be clean
 * @end: The end of भव address to be clean
 * @walk: pagetable walk callback argument
 *
 * The function cleans a pte and records the range in
 * भव address space of touched ptes क्रम efficient TLB flushes.
 * It also records dirty ptes in a biपंचांगap representing page offsets
 * in the address_space, as well as the first and last of the bits
 * touched.
 */
अटल पूर्णांक clean_record_pte(pte_t *pte, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
अणु
	काष्ठा wp_walk *wpwalk = walk->निजी;
	काष्ठा clean_walk *cwalk = to_clean_walk(wpwalk);
	pte_t ptent = *pte;

	अगर (pte_dirty(ptent)) अणु
		pgoff_t pgoff = ((addr - walk->vma->vm_start) >> PAGE_SHIFT) +
			walk->vma->vm_pgoff - cwalk->biपंचांगap_pgoff;
		pte_t old_pte = ptep_modअगरy_prot_start(walk->vma, addr, pte);

		ptent = pte_mkclean(old_pte);
		ptep_modअगरy_prot_commit(walk->vma, addr, pte, old_pte, ptent);

		wpwalk->total++;
		wpwalk->tlbflush_start = min(wpwalk->tlbflush_start, addr);
		wpwalk->tlbflush_end = max(wpwalk->tlbflush_end,
					   addr + PAGE_SIZE);

		__set_bit(pgoff, cwalk->biपंचांगap);
		cwalk->start = min(cwalk->start, pgoff);
		cwalk->end = max(cwalk->end, pgoff + 1);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * wp_clean_pmd_entry - The pagewalk pmd callback.
 *
 * Dirty-tracking should take place on the PTE level, so
 * WARN() अगर encountering a dirty huge pmd.
 * Furthermore, never split huge pmds, since that currently
 * causes dirty info loss. The pagefault handler should करो
 * that अगर needed.
 */
अटल पूर्णांक wp_clean_pmd_entry(pmd_t *pmd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			      काष्ठा mm_walk *walk)
अणु
	pmd_t pmdval = pmd_पढ़ो_atomic(pmd);

	अगर (!pmd_trans_unstable(&pmdval))
		वापस 0;

	अगर (pmd_none(pmdval)) अणु
		walk->action = ACTION_AGAIN;
		वापस 0;
	पूर्ण

	/* Huge pmd, present or migrated */
	walk->action = ACTION_CONTINUE;
	अगर (pmd_trans_huge(pmdval) || pmd_devmap(pmdval))
		WARN_ON(pmd_ग_लिखो(pmdval) || pmd_dirty(pmdval));

	वापस 0;
पूर्ण

/*
 * wp_clean_pud_entry - The pagewalk pud callback.
 *
 * Dirty-tracking should take place on the PTE level, so
 * WARN() अगर encountering a dirty huge puds.
 * Furthermore, never split huge puds, since that currently
 * causes dirty info loss. The pagefault handler should करो
 * that अगर needed.
 */
अटल पूर्णांक wp_clean_pud_entry(pud_t *pud, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			      काष्ठा mm_walk *walk)
अणु
	pud_t pudval = READ_ONCE(*pud);

	अगर (!pud_trans_unstable(&pudval))
		वापस 0;

	अगर (pud_none(pudval)) अणु
		walk->action = ACTION_AGAIN;
		वापस 0;
	पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
	/* Huge pud */
	walk->action = ACTION_CONTINUE;
	अगर (pud_trans_huge(pudval) || pud_devmap(pudval))
		WARN_ON(pud_ग_लिखो(pudval) || pud_dirty(pudval));
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 * wp_clean_pre_vma - The pagewalk pre_vma callback.
 *
 * The pre_vma callback perक्रमms the cache flush, stages the tlb flush
 * and calls the necessary mmu notअगरiers.
 */
अटल पूर्णांक wp_clean_pre_vma(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			    काष्ठा mm_walk *walk)
अणु
	काष्ठा wp_walk *wpwalk = walk->निजी;

	wpwalk->tlbflush_start = end;
	wpwalk->tlbflush_end = start;

	mmu_notअगरier_range_init(&wpwalk->range, MMU_NOTIFY_PROTECTION_PAGE, 0,
				walk->vma, walk->mm, start, end);
	mmu_notअगरier_invalidate_range_start(&wpwalk->range);
	flush_cache_range(walk->vma, start, end);

	/*
	 * We're not using tlb_gather_mmu() since typically
	 * only a small subrange of PTEs are affected, whereas
	 * tlb_gather_mmu() records the full range.
	 */
	inc_tlb_flush_pending(walk->mm);

	वापस 0;
पूर्ण

/*
 * wp_clean_post_vma - The pagewalk post_vma callback.
 *
 * The post_vma callback perक्रमms the tlb flush and calls necessary mmu
 * notअगरiers.
 */
अटल व्योम wp_clean_post_vma(काष्ठा mm_walk *walk)
अणु
	काष्ठा wp_walk *wpwalk = walk->निजी;

	अगर (mm_tlb_flush_nested(walk->mm))
		flush_tlb_range(walk->vma, wpwalk->range.start,
				wpwalk->range.end);
	अन्यथा अगर (wpwalk->tlbflush_end > wpwalk->tlbflush_start)
		flush_tlb_range(walk->vma, wpwalk->tlbflush_start,
				wpwalk->tlbflush_end);

	mmu_notअगरier_invalidate_range_end(&wpwalk->range);
	dec_tlb_flush_pending(walk->mm);
पूर्ण

/*
 * wp_clean_test_walk - The pagewalk test_walk callback.
 *
 * Won't perक्रमm dirty-tracking on COW, पढ़ो-only or HUGETLB vmas.
 */
अटल पूर्णांक wp_clean_test_walk(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			      काष्ठा mm_walk *walk)
अणु
	अचिन्हित दीर्घ vm_flags = READ_ONCE(walk->vma->vm_flags);

	/* Skip non-applicable VMAs */
	अगर ((vm_flags & (VM_SHARED | VM_MAYWRITE | VM_HUGETLB)) !=
	    (VM_SHARED | VM_MAYWRITE))
		वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops clean_walk_ops = अणु
	.pte_entry = clean_record_pte,
	.pmd_entry = wp_clean_pmd_entry,
	.pud_entry = wp_clean_pud_entry,
	.test_walk = wp_clean_test_walk,
	.pre_vma = wp_clean_pre_vma,
	.post_vma = wp_clean_post_vma
पूर्ण;

अटल स्थिर काष्ठा mm_walk_ops wp_walk_ops = अणु
	.pte_entry = wp_pte,
	.pmd_entry = wp_clean_pmd_entry,
	.pud_entry = wp_clean_pud_entry,
	.test_walk = wp_clean_test_walk,
	.pre_vma = wp_clean_pre_vma,
	.post_vma = wp_clean_post_vma
पूर्ण;

/**
 * wp_shared_mapping_range - Write-protect all ptes in an address space range
 * @mapping: The address_space we want to ग_लिखो protect
 * @first_index: The first page offset in the range
 * @nr: Number of incremental page offsets to cover
 *
 * Note: This function currently skips transhuge page-table entries, since
 * it's पूर्णांकended क्रम dirty-tracking on the PTE level. It will warn on
 * encountering transhuge ग_लिखो-enabled entries, though, and can easily be
 * extended to handle them as well.
 *
 * Return: The number of ptes actually ग_लिखो-रक्षित. Note that
 * alपढ़ोy ग_लिखो-रक्षित ptes are not counted.
 */
अचिन्हित दीर्घ wp_shared_mapping_range(काष्ठा address_space *mapping,
				      pgoff_t first_index, pgoff_t nr)
अणु
	काष्ठा wp_walk wpwalk = अणु .total = 0 पूर्ण;

	i_mmap_lock_पढ़ो(mapping);
	WARN_ON(walk_page_mapping(mapping, first_index, nr, &wp_walk_ops,
				  &wpwalk));
	i_mmap_unlock_पढ़ो(mapping);

	वापस wpwalk.total;
पूर्ण
EXPORT_SYMBOL_GPL(wp_shared_mapping_range);

/**
 * clean_record_shared_mapping_range - Clean and record all ptes in an
 * address space range
 * @mapping: The address_space we want to clean
 * @first_index: The first page offset in the range
 * @nr: Number of incremental page offsets to cover
 * @biपंचांगap_pgoff: The page offset of the first bit in @biपंचांगap
 * @biपंचांगap: Poपूर्णांकer to a biपंचांगap of at least @nr bits. The biपंचांगap needs to
 * cover the whole range @first_index..@first_index + @nr.
 * @start: Poपूर्णांकer to number of the first set bit in @biपंचांगap.
 * is modअगरied as new bits are set by the function.
 * @end: Poपूर्णांकer to the number of the last set bit in @biपंचांगap.
 * none set. The value is modअगरied as new bits are set by the function.
 *
 * Note: When this function वापसs there is no guarantee that a CPU has
 * not alपढ़ोy dirtied new ptes. However it will not clean any ptes not
 * reported in the biपंचांगap. The guarantees are as follows:
 * a) All ptes dirty when the function starts executing will end up recorded
 *    in the biपंचांगap.
 * b) All ptes dirtied after that will either reमुख्य dirty, be recorded in the
 *    biपंचांगap or both.
 *
 * If a caller needs to make sure all dirty ptes are picked up and none
 * additional are added, it first needs to ग_लिखो-protect the address-space
 * range and make sure new ग_लिखोrs are blocked in page_mkग_लिखो() or
 * pfn_mkग_लिखो(). And then after a TLB flush following the ग_लिखो-protection
 * pick up all dirty bits.
 *
 * Note: This function currently skips transhuge page-table entries, since
 * it's पूर्णांकended क्रम dirty-tracking on the PTE level. It will warn on
 * encountering transhuge dirty entries, though, and can easily be extended
 * to handle them as well.
 *
 * Return: The number of dirty ptes actually cleaned.
 */
अचिन्हित दीर्घ clean_record_shared_mapping_range(काष्ठा address_space *mapping,
						pgoff_t first_index, pgoff_t nr,
						pgoff_t biपंचांगap_pgoff,
						अचिन्हित दीर्घ *biपंचांगap,
						pgoff_t *start,
						pgoff_t *end)
अणु
	bool none_set = (*start >= *end);
	काष्ठा clean_walk cwalk = अणु
		.base = अणु .total = 0 पूर्ण,
		.biपंचांगap_pgoff = biपंचांगap_pgoff,
		.biपंचांगap = biपंचांगap,
		.start = none_set ? nr : *start,
		.end = none_set ? 0 : *end,
	पूर्ण;

	i_mmap_lock_पढ़ो(mapping);
	WARN_ON(walk_page_mapping(mapping, first_index, nr, &clean_walk_ops,
				  &cwalk.base));
	i_mmap_unlock_पढ़ो(mapping);

	*start = cwalk.start;
	*end = cwalk.end;

	वापस cwalk.base.total;
पूर्ण
EXPORT_SYMBOL_GPL(clean_record_shared_mapping_range);
