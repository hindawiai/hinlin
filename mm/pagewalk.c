<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/pagewalk.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sched.h>
#समावेश <linux/hugetlb.h>

/*
 * We want to know the real level where a entry is located ignoring any
 * folding of levels which may be happening. For example अगर p4d is folded then
 * a missing entry found at level 1 (p4d) is actually at level 0 (pgd).
 */
अटल पूर्णांक real_depth(पूर्णांक depth)
अणु
	अगर (depth == 3 && PTRS_PER_PMD == 1)
		depth = 2;
	अगर (depth == 2 && PTRS_PER_PUD == 1)
		depth = 1;
	अगर (depth == 1 && PTRS_PER_P4D == 1)
		depth = 0;
	वापस depth;
पूर्ण

अटल पूर्णांक walk_pte_range_inner(pte_t *pte, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
अणु
	स्थिर काष्ठा mm_walk_ops *ops = walk->ops;
	पूर्णांक err = 0;

	क्रम (;;) अणु
		err = ops->pte_entry(pte, addr, addr + PAGE_SIZE, walk);
		अगर (err)
		       अवरोध;
		अगर (addr >= end - PAGE_SIZE)
			अवरोध;
		addr += PAGE_SIZE;
		pte++;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक walk_pte_range(pmd_t *pmd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			  काष्ठा mm_walk *walk)
अणु
	pte_t *pte;
	पूर्णांक err = 0;
	spinlock_t *ptl;

	अगर (walk->no_vma) अणु
		pte = pte_offset_map(pmd, addr);
		err = walk_pte_range_inner(pte, addr, end, walk);
		pte_unmap(pte);
	पूर्ण अन्यथा अणु
		pte = pte_offset_map_lock(walk->mm, pmd, addr, &ptl);
		err = walk_pte_range_inner(pte, addr, end, walk);
		pte_unmap_unlock(pte, ptl);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक walk_pmd_range(pud_t *pud, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			  काष्ठा mm_walk *walk)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;
	स्थिर काष्ठा mm_walk_ops *ops = walk->ops;
	पूर्णांक err = 0;
	पूर्णांक depth = real_depth(3);

	pmd = pmd_offset(pud, addr);
	करो अणु
again:
		next = pmd_addr_end(addr, end);
		अगर (pmd_none(*pmd) || (!walk->vma && !walk->no_vma)) अणु
			अगर (ops->pte_hole)
				err = ops->pte_hole(addr, next, depth, walk);
			अगर (err)
				अवरोध;
			जारी;
		पूर्ण

		walk->action = ACTION_SUBTREE;

		/*
		 * This implies that each ->pmd_entry() handler
		 * needs to know about pmd_trans_huge() pmds
		 */
		अगर (ops->pmd_entry)
			err = ops->pmd_entry(pmd, addr, next, walk);
		अगर (err)
			अवरोध;

		अगर (walk->action == ACTION_AGAIN)
			जाओ again;

		/*
		 * Check this here so we only अवरोध करोwn trans_huge
		 * pages when we _need_ to
		 */
		अगर ((!walk->vma && (pmd_leaf(*pmd) || !pmd_present(*pmd))) ||
		    walk->action == ACTION_CONTINUE ||
		    !(ops->pte_entry))
			जारी;

		अगर (walk->vma) अणु
			split_huge_pmd(walk->vma, pmd, addr);
			अगर (pmd_trans_unstable(pmd))
				जाओ again;
		पूर्ण

		err = walk_pte_range(pmd, addr, next, walk);
		अगर (err)
			अवरोध;
	पूर्ण जबतक (pmd++, addr = next, addr != end);

	वापस err;
पूर्ण

अटल पूर्णांक walk_pud_range(p4d_t *p4d, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			  काष्ठा mm_walk *walk)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;
	स्थिर काष्ठा mm_walk_ops *ops = walk->ops;
	पूर्णांक err = 0;
	पूर्णांक depth = real_depth(2);

	pud = pud_offset(p4d, addr);
	करो अणु
 again:
		next = pud_addr_end(addr, end);
		अगर (pud_none(*pud) || (!walk->vma && !walk->no_vma)) अणु
			अगर (ops->pte_hole)
				err = ops->pte_hole(addr, next, depth, walk);
			अगर (err)
				अवरोध;
			जारी;
		पूर्ण

		walk->action = ACTION_SUBTREE;

		अगर (ops->pud_entry)
			err = ops->pud_entry(pud, addr, next, walk);
		अगर (err)
			अवरोध;

		अगर (walk->action == ACTION_AGAIN)
			जाओ again;

		अगर ((!walk->vma && (pud_leaf(*pud) || !pud_present(*pud))) ||
		    walk->action == ACTION_CONTINUE ||
		    !(ops->pmd_entry || ops->pte_entry))
			जारी;

		अगर (walk->vma)
			split_huge_pud(walk->vma, pud, addr);
		अगर (pud_none(*pud))
			जाओ again;

		err = walk_pmd_range(pud, addr, next, walk);
		अगर (err)
			अवरोध;
	पूर्ण जबतक (pud++, addr = next, addr != end);

	वापस err;
पूर्ण

अटल पूर्णांक walk_p4d_range(pgd_t *pgd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			  काष्ठा mm_walk *walk)
अणु
	p4d_t *p4d;
	अचिन्हित दीर्घ next;
	स्थिर काष्ठा mm_walk_ops *ops = walk->ops;
	पूर्णांक err = 0;
	पूर्णांक depth = real_depth(1);

	p4d = p4d_offset(pgd, addr);
	करो अणु
		next = p4d_addr_end(addr, end);
		अगर (p4d_none_or_clear_bad(p4d)) अणु
			अगर (ops->pte_hole)
				err = ops->pte_hole(addr, next, depth, walk);
			अगर (err)
				अवरोध;
			जारी;
		पूर्ण
		अगर (ops->p4d_entry) अणु
			err = ops->p4d_entry(p4d, addr, next, walk);
			अगर (err)
				अवरोध;
		पूर्ण
		अगर (ops->pud_entry || ops->pmd_entry || ops->pte_entry)
			err = walk_pud_range(p4d, addr, next, walk);
		अगर (err)
			अवरोध;
	पूर्ण जबतक (p4d++, addr = next, addr != end);

	वापस err;
पूर्ण

अटल पूर्णांक walk_pgd_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			  काष्ठा mm_walk *walk)
अणु
	pgd_t *pgd;
	अचिन्हित दीर्घ next;
	स्थिर काष्ठा mm_walk_ops *ops = walk->ops;
	पूर्णांक err = 0;

	अगर (walk->pgd)
		pgd = walk->pgd + pgd_index(addr);
	अन्यथा
		pgd = pgd_offset(walk->mm, addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		अगर (pgd_none_or_clear_bad(pgd)) अणु
			अगर (ops->pte_hole)
				err = ops->pte_hole(addr, next, 0, walk);
			अगर (err)
				अवरोध;
			जारी;
		पूर्ण
		अगर (ops->pgd_entry) अणु
			err = ops->pgd_entry(pgd, addr, next, walk);
			अगर (err)
				अवरोध;
		पूर्ण
		अगर (ops->p4d_entry || ops->pud_entry || ops->pmd_entry ||
		    ops->pte_entry)
			err = walk_p4d_range(pgd, addr, next, walk);
		अगर (err)
			अवरोध;
	पूर्ण जबतक (pgd++, addr = next, addr != end);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
अटल अचिन्हित दीर्घ hugetlb_entry_end(काष्ठा hstate *h, अचिन्हित दीर्घ addr,
				       अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ boundary = (addr & huge_page_mask(h)) + huge_page_size(h);
	वापस boundary < end ? boundary : end;
पूर्ण

अटल पूर्णांक walk_hugetlb_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			      काष्ठा mm_walk *walk)
अणु
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	काष्ठा hstate *h = hstate_vma(vma);
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ hmask = huge_page_mask(h);
	अचिन्हित दीर्घ sz = huge_page_size(h);
	pte_t *pte;
	स्थिर काष्ठा mm_walk_ops *ops = walk->ops;
	पूर्णांक err = 0;

	करो अणु
		next = hugetlb_entry_end(h, addr, end);
		pte = huge_pte_offset(walk->mm, addr & hmask, sz);

		अगर (pte)
			err = ops->hugetlb_entry(pte, hmask, addr, next, walk);
		अन्यथा अगर (ops->pte_hole)
			err = ops->pte_hole(addr, next, -1, walk);

		अगर (err)
			अवरोध;
	पूर्ण जबतक (addr = next, addr != end);

	वापस err;
पूर्ण

#अन्यथा /* CONFIG_HUGETLB_PAGE */
अटल पूर्णांक walk_hugetlb_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			      काष्ठा mm_walk *walk)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

/*
 * Decide whether we really walk over the current vma on [@start, @end)
 * or skip it via the वापसed value. Return 0 अगर we करो walk over the
 * current vma, and वापस 1 अगर we skip the vma. Negative values means
 * error, where we पात the current walk.
 */
अटल पूर्णांक walk_page_test(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			काष्ठा mm_walk *walk)
अणु
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	स्थिर काष्ठा mm_walk_ops *ops = walk->ops;

	अगर (ops->test_walk)
		वापस ops->test_walk(start, end, walk);

	/*
	 * vma(VM_PFNMAP) करोesn't have any valid काष्ठा pages behind VM_PFNMAP
	 * range, so we करोn't walk over it as we करो क्रम normal vmas. However,
	 * Some callers are पूर्णांकerested in handling hole range and they करोn't
	 * want to just ignore any single address range. Such users certainly
	 * define their ->pte_hole() callbacks, so let's delegate them to handle
	 * vma(VM_PFNMAP).
	 */
	अगर (vma->vm_flags & VM_PFNMAP) अणु
		पूर्णांक err = 1;
		अगर (ops->pte_hole)
			err = ops->pte_hole(start, end, -1, walk);
		वापस err ? err : 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __walk_page_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			काष्ठा mm_walk *walk)
अणु
	पूर्णांक err = 0;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	स्थिर काष्ठा mm_walk_ops *ops = walk->ops;

	अगर (vma && ops->pre_vma) अणु
		err = ops->pre_vma(start, end, walk);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (vma && is_vm_hugetlb_page(vma)) अणु
		अगर (ops->hugetlb_entry)
			err = walk_hugetlb_range(start, end, walk);
	पूर्ण अन्यथा
		err = walk_pgd_range(start, end, walk);

	अगर (vma && ops->post_vma)
		ops->post_vma(walk);

	वापस err;
पूर्ण

/**
 * walk_page_range - walk page table with caller specअगरic callbacks
 * @mm:		mm_काष्ठा representing the target process of page table walk
 * @start:	start address of the भव address range
 * @end:	end address of the भव address range
 * @ops:	operation to call during the walk
 * @निजी:	निजी data क्रम callbacks' usage
 *
 * Recursively walk the page table tree of the process represented by @mm
 * within the भव address range [@start, @end). During walking, we can करो
 * some caller-specअगरic works क्रम each entry, by setting up pmd_entry(),
 * pte_entry(), and/or hugetlb_entry(). If you करोn't set up क्रम some of these
 * callbacks, the associated entries/pages are just ignored.
 * The वापस values of these callbacks are commonly defined like below:
 *
 *  - 0  : succeeded to handle the current entry, and अगर you करोn't reach the
 *         end address yet, जारी to walk.
 *  - >0 : succeeded to handle the current entry, and वापस to the caller
 *         with caller specअगरic value.
 *  - <0 : failed to handle the current entry, and वापस to the caller
 *         with error code.
 *
 * Beक्रमe starting to walk page table, some callers want to check whether
 * they really want to walk over the current vma, typically by checking
 * its vm_flags. walk_page_test() and @ops->test_walk() are used क्रम this
 * purpose.
 *
 * If operations need to be staged beक्रमe and committed after a vma is walked,
 * there are two callbacks, pre_vma() and post_vma(). Note that post_vma(),
 * since it is पूर्णांकended to handle commit-type operations, can't वापस any
 * errors.
 *
 * काष्ठा mm_walk keeps current values of some common data like vma and pmd,
 * which are useful क्रम the access from callbacks. If you want to pass some
 * caller-specअगरic data to callbacks, @निजी should be helpful.
 *
 * Locking:
 *   Callers of walk_page_range() and walk_page_vma() should hold @mm->mmap_lock,
 *   because these function traverse vma list and/or access to vma's data.
 */
पूर्णांक walk_page_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ end, स्थिर काष्ठा mm_walk_ops *ops,
		व्योम *निजी)
अणु
	पूर्णांक err = 0;
	अचिन्हित दीर्घ next;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_walk walk = अणु
		.ops		= ops,
		.mm		= mm,
		.निजी	= निजी,
	पूर्ण;

	अगर (start >= end)
		वापस -EINVAL;

	अगर (!walk.mm)
		वापस -EINVAL;

	mmap_निश्चित_locked(walk.mm);

	vma = find_vma(walk.mm, start);
	करो अणु
		अगर (!vma) अणु /* after the last vma */
			walk.vma = शून्य;
			next = end;
		पूर्ण अन्यथा अगर (start < vma->vm_start) अणु /* outside vma */
			walk.vma = शून्य;
			next = min(end, vma->vm_start);
		पूर्ण अन्यथा अणु /* inside vma */
			walk.vma = vma;
			next = min(end, vma->vm_end);
			vma = vma->vm_next;

			err = walk_page_test(start, next, &walk);
			अगर (err > 0) अणु
				/*
				 * positive वापस values are purely क्रम
				 * controlling the pagewalk, so should never
				 * be passed to the callers.
				 */
				err = 0;
				जारी;
			पूर्ण
			अगर (err < 0)
				अवरोध;
		पूर्ण
		अगर (walk.vma || walk.ops->pte_hole)
			err = __walk_page_range(start, next, &walk);
		अगर (err)
			अवरोध;
	पूर्ण जबतक (start = next, start < end);
	वापस err;
पूर्ण

/*
 * Similar to walk_page_range() but can walk any page tables even अगर they are
 * not backed by VMAs. Because 'unusual' entries may be walked this function
 * will also not lock the PTEs क्रम the pte_entry() callback. This is useful क्रम
 * walking the kernel pages tables or page tables क्रम firmware.
 */
पूर्णांक walk_page_range_novma(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
			  अचिन्हित दीर्घ end, स्थिर काष्ठा mm_walk_ops *ops,
			  pgd_t *pgd,
			  व्योम *निजी)
अणु
	काष्ठा mm_walk walk = अणु
		.ops		= ops,
		.mm		= mm,
		.pgd		= pgd,
		.निजी	= निजी,
		.no_vma		= true
	पूर्ण;

	अगर (start >= end || !walk.mm)
		वापस -EINVAL;

	mmap_निश्चित_locked(walk.mm);

	वापस __walk_page_range(start, end, &walk);
पूर्ण

पूर्णांक walk_page_vma(काष्ठा vm_area_काष्ठा *vma, स्थिर काष्ठा mm_walk_ops *ops,
		व्योम *निजी)
अणु
	काष्ठा mm_walk walk = अणु
		.ops		= ops,
		.mm		= vma->vm_mm,
		.vma		= vma,
		.निजी	= निजी,
	पूर्ण;
	पूर्णांक err;

	अगर (!walk.mm)
		वापस -EINVAL;

	mmap_निश्चित_locked(walk.mm);

	err = walk_page_test(vma->vm_start, vma->vm_end, &walk);
	अगर (err > 0)
		वापस 0;
	अगर (err < 0)
		वापस err;
	वापस __walk_page_range(vma->vm_start, vma->vm_end, &walk);
पूर्ण

/**
 * walk_page_mapping - walk all memory areas mapped पूर्णांकo a काष्ठा address_space.
 * @mapping: Poपूर्णांकer to the काष्ठा address_space
 * @first_index: First page offset in the address_space
 * @nr: Number of incremental page offsets to cover
 * @ops:	operation to call during the walk
 * @निजी:	निजी data क्रम callbacks' usage
 *
 * This function walks all memory areas mapped पूर्णांकo a काष्ठा address_space.
 * The walk is limited to only the given page-size index range, but अगर
 * the index boundaries cross a huge page-table entry, that entry will be
 * included.
 *
 * Also see walk_page_range() क्रम additional inक्रमmation.
 *
 * Locking:
 *   This function can't require that the काष्ठा mm_काष्ठा::mmap_lock is held,
 *   since @mapping may be mapped by multiple processes. Instead
 *   @mapping->i_mmap_rwsem must be held. This might have implications in the
 *   callbacks, and it's up tho the caller to ensure that the
 *   काष्ठा mm_काष्ठा::mmap_lock is not needed.
 *
 *   Also this means that a caller can't rely on the काष्ठा
 *   vm_area_काष्ठा::vm_flags to be स्थिरant across a call,
 *   except क्रम immutable flags. Callers requiring this shouldn't use
 *   this function.
 *
 * Return: 0 on success, negative error code on failure, positive number on
 * caller defined premature termination.
 */
पूर्णांक walk_page_mapping(काष्ठा address_space *mapping, pgoff_t first_index,
		      pgoff_t nr, स्थिर काष्ठा mm_walk_ops *ops,
		      व्योम *निजी)
अणु
	काष्ठा mm_walk walk = अणु
		.ops		= ops,
		.निजी	= निजी,
	पूर्ण;
	काष्ठा vm_area_काष्ठा *vma;
	pgoff_t vba, vea, cba, cea;
	अचिन्हित दीर्घ start_addr, end_addr;
	पूर्णांक err = 0;

	lockdep_निश्चित_held(&mapping->i_mmap_rwsem);
	vma_पूर्णांकerval_tree_क्रमeach(vma, &mapping->i_mmap, first_index,
				  first_index + nr - 1) अणु
		/* Clip to the vma */
		vba = vma->vm_pgoff;
		vea = vba + vma_pages(vma);
		cba = first_index;
		cba = max(cba, vba);
		cea = first_index + nr;
		cea = min(cea, vea);

		start_addr = ((cba - vba) << PAGE_SHIFT) + vma->vm_start;
		end_addr = ((cea - vba) << PAGE_SHIFT) + vma->vm_start;
		अगर (start_addr >= end_addr)
			जारी;

		walk.vma = vma;
		walk.mm = vma->vm_mm;

		err = walk_page_test(vma->vm_start, vma->vm_end, &walk);
		अगर (err > 0) अणु
			err = 0;
			अवरोध;
		पूर्ण अन्यथा अगर (err < 0)
			अवरोध;

		err = __walk_page_range(start_addr, end_addr, &walk);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण
