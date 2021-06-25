<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "mmu_internal.h"
#समावेश "tdp_iter.h"
#समावेश "spte.h"

/*
 * Recalculates the poपूर्णांकer to the SPTE क्रम the current GFN and level and
 * reपढ़ो the SPTE.
 */
अटल व्योम tdp_iter_refresh_sptep(काष्ठा tdp_iter *iter)
अणु
	iter->sptep = iter->pt_path[iter->level - 1] +
		SHADOW_PT_INDEX(iter->gfn << PAGE_SHIFT, iter->level);
	iter->old_spte = READ_ONCE(*rcu_dereference(iter->sptep));
पूर्ण

अटल gfn_t round_gfn_क्रम_level(gfn_t gfn, पूर्णांक level)
अणु
	वापस gfn & -KVM_PAGES_PER_HPAGE(level);
पूर्ण

/*
 * Return the TDP iterator to the root PT and allow it to जारी its
 * traversal over the paging काष्ठाure from there.
 */
व्योम tdp_iter_restart(काष्ठा tdp_iter *iter)
अणु
	iter->yielded_gfn = iter->next_last_level_gfn;
	iter->level = iter->root_level;

	iter->gfn = round_gfn_क्रम_level(iter->next_last_level_gfn, iter->level);
	tdp_iter_refresh_sptep(iter);

	iter->valid = true;
पूर्ण

/*
 * Sets a TDP iterator to walk a pre-order traversal of the paging काष्ठाure
 * rooted at root_pt, starting with the walk to translate next_last_level_gfn.
 */
व्योम tdp_iter_start(काष्ठा tdp_iter *iter, u64 *root_pt, पूर्णांक root_level,
		    पूर्णांक min_level, gfn_t next_last_level_gfn)
अणु
	WARN_ON(root_level < 1);
	WARN_ON(root_level > PT64_ROOT_MAX_LEVEL);

	iter->next_last_level_gfn = next_last_level_gfn;
	iter->root_level = root_level;
	iter->min_level = min_level;
	iter->pt_path[iter->root_level - 1] = (tdp_ptep_t)root_pt;
	iter->as_id = kvm_mmu_page_as_id(sptep_to_sp(root_pt));

	tdp_iter_restart(iter);
पूर्ण

/*
 * Given an SPTE and its level, वापसs a poपूर्णांकer containing the host भव
 * address of the child page table referenced by the SPTE. Returns null अगर
 * there is no such entry.
 */
tdp_ptep_t spte_to_child_pt(u64 spte, पूर्णांक level)
अणु
	/*
	 * There's no child entry if this entry isn't present or is a
	 * last-level entry.
	 */
	अगर (!is_shaकरोw_present_pte(spte) || is_last_spte(spte, level))
		वापस शून्य;

	वापस (tdp_ptep_t)__va(spte_to_pfn(spte) << PAGE_SHIFT);
पूर्ण

/*
 * Steps करोwn one level in the paging काष्ठाure towards the goal GFN. Returns
 * true अगर the iterator was able to step करोwn a level, false otherwise.
 */
अटल bool try_step_करोwn(काष्ठा tdp_iter *iter)
अणु
	tdp_ptep_t child_pt;

	अगर (iter->level == iter->min_level)
		वापस false;

	/*
	 * Reपढ़ो the SPTE beक्रमe stepping करोwn to aव्योम traversing पूर्णांकo page
	 * tables that are no दीर्घer linked from this entry.
	 */
	iter->old_spte = READ_ONCE(*rcu_dereference(iter->sptep));

	child_pt = spte_to_child_pt(iter->old_spte, iter->level);
	अगर (!child_pt)
		वापस false;

	iter->level--;
	iter->pt_path[iter->level - 1] = child_pt;
	iter->gfn = round_gfn_क्रम_level(iter->next_last_level_gfn, iter->level);
	tdp_iter_refresh_sptep(iter);

	वापस true;
पूर्ण

/*
 * Steps to the next entry in the current page table, at the current page table
 * level. The next entry could poपूर्णांक to a page backing guest memory or another
 * page table, or it could be non-present. Returns true अगर the iterator was
 * able to step to the next entry in the page table, false अगर the iterator was
 * alपढ़ोy at the end of the current page table.
 */
अटल bool try_step_side(काष्ठा tdp_iter *iter)
अणु
	/*
	 * Check अगर the iterator is alपढ़ोy at the end of the current page
	 * table.
	 */
	अगर (SHADOW_PT_INDEX(iter->gfn << PAGE_SHIFT, iter->level) ==
            (PT64_ENT_PER_PAGE - 1))
		वापस false;

	iter->gfn += KVM_PAGES_PER_HPAGE(iter->level);
	iter->next_last_level_gfn = iter->gfn;
	iter->sptep++;
	iter->old_spte = READ_ONCE(*rcu_dereference(iter->sptep));

	वापस true;
पूर्ण

/*
 * Tries to traverse back up a level in the paging काष्ठाure so that the walk
 * can जारी from the next entry in the parent page table. Returns true on a
 * successful step up, false अगर alपढ़ोy in the root page.
 */
अटल bool try_step_up(काष्ठा tdp_iter *iter)
अणु
	अगर (iter->level == iter->root_level)
		वापस false;

	iter->level++;
	iter->gfn = round_gfn_क्रम_level(iter->gfn, iter->level);
	tdp_iter_refresh_sptep(iter);

	वापस true;
पूर्ण

/*
 * Step to the next SPTE in a pre-order traversal of the paging काष्ठाure.
 * To get to the next SPTE, the iterator either steps करोwn towards the goal
 * GFN, अगर at a present, non-last-level SPTE, or over to a SPTE mapping a
 * highter GFN.
 *
 * The basic algorithm is as follows:
 * 1. If the current SPTE is a non-last-level SPTE, step करोwn पूर्णांकo the page
 *    table it poपूर्णांकs to.
 * 2. If the iterator cannot step करोwn, it will try to step to the next SPTE
 *    in the current page of the paging काष्ठाure.
 * 3. If the iterator cannot step to the next entry in the current page, it will
 *    try to step up to the parent paging काष्ठाure page. In this हाल, that
 *    SPTE will have alपढ़ोy been visited, and so the iterator must also step
 *    to the side again.
 */
व्योम tdp_iter_next(काष्ठा tdp_iter *iter)
अणु
	अगर (try_step_करोwn(iter))
		वापस;

	करो अणु
		अगर (try_step_side(iter))
			वापस;
	पूर्ण जबतक (try_step_up(iter));
	iter->valid = false;
पूर्ण

