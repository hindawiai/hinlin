<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#अगर_अघोषित __KVM_X86_MMU_TDP_ITER_H
#घोषणा __KVM_X86_MMU_TDP_ITER_H

#समावेश <linux/kvm_host.h>

#समावेश "mmu.h"

प्रकार u64 __rcu *tdp_ptep_t;

/*
 * A TDP iterator perक्रमms a pre-order walk over a TDP paging काष्ठाure.
 */
काष्ठा tdp_iter अणु
	/*
	 * The iterator will traverse the paging काष्ठाure towards the mapping
	 * क्रम this GFN.
	 */
	gfn_t next_last_level_gfn;
	/*
	 * The next_last_level_gfn at the समय when the thपढ़ो last
	 * yielded. Only yielding when the next_last_level_gfn !=
	 * yielded_gfn helps ensure क्रमward progress.
	 */
	gfn_t yielded_gfn;
	/* Poपूर्णांकers to the page tables traversed to reach the current SPTE */
	tdp_ptep_t pt_path[PT64_ROOT_MAX_LEVEL];
	/* A poपूर्णांकer to the current SPTE */
	tdp_ptep_t sptep;
	/* The lowest GFN mapped by the current SPTE */
	gfn_t gfn;
	/* The level of the root page given to the iterator */
	पूर्णांक root_level;
	/* The lowest level the iterator should traverse to */
	पूर्णांक min_level;
	/* The iterator's current level within the paging काष्ठाure */
	पूर्णांक level;
	/* The address space ID, i.e. SMM vs. regular. */
	पूर्णांक as_id;
	/* A snapshot of the value at sptep */
	u64 old_spte;
	/*
	 * Whether the iterator has a valid state. This will be false अगर the
	 * iterator walks off the end of the paging काष्ठाure.
	 */
	bool valid;
पूर्ण;

/*
 * Iterates over every SPTE mapping the GFN range [start, end) in a
 * preorder traversal.
 */
#घोषणा क्रम_each_tdp_pte_min_level(iter, root, root_level, min_level, start, end) \
	क्रम (tdp_iter_start(&iter, root, root_level, min_level, start); \
	     iter.valid && iter.gfn < end;		     \
	     tdp_iter_next(&iter))

#घोषणा क्रम_each_tdp_pte(iter, root, root_level, start, end) \
	क्रम_each_tdp_pte_min_level(iter, root, root_level, PG_LEVEL_4K, start, end)

tdp_ptep_t spte_to_child_pt(u64 pte, पूर्णांक level);

व्योम tdp_iter_start(काष्ठा tdp_iter *iter, u64 *root_pt, पूर्णांक root_level,
		    पूर्णांक min_level, gfn_t next_last_level_gfn);
व्योम tdp_iter_next(काष्ठा tdp_iter *iter);
व्योम tdp_iter_restart(काष्ठा tdp_iter *iter);

#पूर्ण_अगर /* __KVM_X86_MMU_TDP_ITER_H */
