<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PAGEWALK_H
#घोषणा _LINUX_PAGEWALK_H

#समावेश <linux/mm.h>

काष्ठा mm_walk;

/**
 * काष्ठा mm_walk_ops - callbacks क्रम walk_page_range
 * @pgd_entry:		अगर set, called क्रम each non-empty PGD (top-level) entry
 * @p4d_entry:		अगर set, called क्रम each non-empty P4D entry
 * @pud_entry:		अगर set, called क्रम each non-empty PUD entry
 * @pmd_entry:		अगर set, called क्रम each non-empty PMD entry
 *			this handler is required to be able to handle
 *			pmd_trans_huge() pmds.  They may simply choose to
 *			split_huge_page() instead of handling it explicitly.
 * @pte_entry:		अगर set, called क्रम each non-empty PTE (lowest-level)
 *			entry
 * @pte_hole:		अगर set, called क्रम each hole at all levels,
 *			depth is -1 अगर not known, 0:PGD, 1:P4D, 2:PUD, 3:PMD
 *			4:PTE. Any folded depths (where PTRS_PER_P?D is equal
 *			to 1) are skipped.
 * @hugetlb_entry:	अगर set, called क्रम each hugetlb entry
 * @test_walk:		caller specअगरic callback function to determine whether
 *			we walk over the current vma or not. Returning 0 means
 *			"do page table walk over the current vma", वापसing
 *			a negative value means "पात current page table walk
 *			right now" and returning 1 means "skip the current vma"
 * @pre_vma:            अगर set, called beक्रमe starting walk on a non-null vma.
 * @post_vma:           अगर set, called after a walk on a non-null vma, provided
 *                      that @pre_vma and the vma walk succeeded.
 *
 * p?d_entry callbacks are called even अगर those levels are folded on a
 * particular architecture/configuration.
 */
काष्ठा mm_walk_ops अणु
	पूर्णांक (*pgd_entry)(pgd_t *pgd, अचिन्हित दीर्घ addr,
			 अचिन्हित दीर्घ next, काष्ठा mm_walk *walk);
	पूर्णांक (*p4d_entry)(p4d_t *p4d, अचिन्हित दीर्घ addr,
			 अचिन्हित दीर्घ next, काष्ठा mm_walk *walk);
	पूर्णांक (*pud_entry)(pud_t *pud, अचिन्हित दीर्घ addr,
			 अचिन्हित दीर्घ next, काष्ठा mm_walk *walk);
	पूर्णांक (*pmd_entry)(pmd_t *pmd, अचिन्हित दीर्घ addr,
			 अचिन्हित दीर्घ next, काष्ठा mm_walk *walk);
	पूर्णांक (*pte_entry)(pte_t *pte, अचिन्हित दीर्घ addr,
			 अचिन्हित दीर्घ next, काष्ठा mm_walk *walk);
	पूर्णांक (*pte_hole)(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ next,
			पूर्णांक depth, काष्ठा mm_walk *walk);
	पूर्णांक (*hugetlb_entry)(pte_t *pte, अचिन्हित दीर्घ hmask,
			     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ next,
			     काष्ठा mm_walk *walk);
	पूर्णांक (*test_walk)(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ next,
			काष्ठा mm_walk *walk);
	पूर्णांक (*pre_vma)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		       काष्ठा mm_walk *walk);
	व्योम (*post_vma)(काष्ठा mm_walk *walk);
पूर्ण;

/*
 * Action क्रम pud_entry / pmd_entry callbacks.
 * ACTION_SUBTREE is the शेष
 */
क्रमागत page_walk_action अणु
	/* Descend to next level, splitting huge pages अगर needed and possible */
	ACTION_SUBTREE = 0,
	/* Continue to next entry at this level (ignoring any subtree) */
	ACTION_CONTINUE = 1,
	/* Call again क्रम this entry */
	ACTION_AGAIN = 2
पूर्ण;

/**
 * काष्ठा mm_walk - walk_page_range data
 * @ops:	operation to call during the walk
 * @mm:		mm_काष्ठा representing the target process of page table walk
 * @pgd:	poपूर्णांकer to PGD; only valid with no_vma (otherwise set to शून्य)
 * @vma:	vma currently walked (शून्य अगर walking outside vmas)
 * @action:	next action to perक्रमm (see क्रमागत page_walk_action)
 * @no_vma:	walk ignoring vmas (vma will always be शून्य)
 * @निजी:	निजी data क्रम callbacks' usage
 *
 * (see the comment on walk_page_range() क्रम more details)
 */
काष्ठा mm_walk अणु
	स्थिर काष्ठा mm_walk_ops *ops;
	काष्ठा mm_काष्ठा *mm;
	pgd_t *pgd;
	काष्ठा vm_area_काष्ठा *vma;
	क्रमागत page_walk_action action;
	bool no_vma;
	व्योम *निजी;
पूर्ण;

पूर्णांक walk_page_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ end, स्थिर काष्ठा mm_walk_ops *ops,
		व्योम *निजी);
पूर्णांक walk_page_range_novma(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
			  अचिन्हित दीर्घ end, स्थिर काष्ठा mm_walk_ops *ops,
			  pgd_t *pgd,
			  व्योम *निजी);
पूर्णांक walk_page_vma(काष्ठा vm_area_काष्ठा *vma, स्थिर काष्ठा mm_walk_ops *ops,
		व्योम *निजी);
पूर्णांक walk_page_mapping(काष्ठा address_space *mapping, pgoff_t first_index,
		      pgoff_t nr, स्थिर काष्ठा mm_walk_ops *ops,
		      व्योम *निजी);

#पूर्ण_अगर /* _LINUX_PAGEWALK_H */
