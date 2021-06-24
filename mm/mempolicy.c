<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Simple NUMA memory policy क्रम the Linux kernel.
 *
 * Copyright 2003,2004 Andi Kleen, SuSE Lअसल.
 * (C) Copyright 2005 Christoph Lameter, Silicon Graphics, Inc.
 *
 * NUMA policy allows the user to give hपूर्णांकs in which node(s) memory should
 * be allocated.
 *
 * Support four policies per VMA and per process:
 *
 * The VMA policy has priority over the process policy क्रम a page fault.
 *
 * पूर्णांकerleave     Allocate memory पूर्णांकerleaved over a set of nodes,
 *                with normal fallback अगर it fails.
 *                For VMA based allocations this पूर्णांकerleaves based on the
 *                offset पूर्णांकo the backing object or offset पूर्णांकo the mapping
 *                क्रम anonymous memory. For process policy an process counter
 *                is used.
 *
 * bind           Only allocate memory on a specअगरic set of nodes,
 *                no fallback.
 *                FIXME: memory is allocated starting with the first node
 *                to the last. It would be better अगर bind would truly restrict
 *                the allocation to memory nodes instead
 *
 * preferred       Try a specअगरic node first beक्रमe normal fallback.
 *                As a special हाल NUMA_NO_NODE here means करो the allocation
 *                on the local CPU. This is normally identical to शेष,
 *                but useful to set in a VMA when you have a non शेष
 *                process policy.
 *
 * शेष        Allocate on the local node first, or when on a VMA
 *                use the process policy. This is what Linux always did
 *		  in a NUMA aware kernel and still करोes by, ahem, शेष.
 *
 * The process policy is applied क्रम most non पूर्णांकerrupt memory allocations
 * in that process' context. Interrupts ignore the policies and always
 * try to allocate on the local CPU. The VMA policy is only applied क्रम memory
 * allocations क्रम a VMA in the VM.
 *
 * Currently there are a few corner हालs in swapping where the policy
 * is not applied, but the majority should be handled. When process policy
 * is used it is not remembered over swap outs/swap ins.
 *
 * Only the highest zone in the zone hierarchy माला_लो policied. Allocations
 * requesting a lower zone just use शेष policy. This implies that
 * on प्रणालीs with highmem kernel lowmem allocation करोn't get policied.
 * Same with GFP_DMA allocations.
 *
 * For shmfs/पंचांगpfs/hugetlbfs shared memory the policy is shared between
 * all users and remembered even when nobody has memory mapped.
 */

/* Notebook:
   fix mmap पढ़ोahead to honour policy and enable policy क्रम any page cache
   object
   statistics क्रम bigpages
   global policy क्रम page cache? currently it uses process policy. Requires
   first item above.
   handle mremap क्रम shared memory (currently ignored क्रम the policy)
   grows करोwn?
   make bind policy root only? It can trigger oom much faster and the
   kernel is not always grateful with that.
*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/mempolicy.h>
#समावेश <linux/pagewalk.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/hugetlb.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/numa_balancing.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/compat.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/swap.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/migrate.h>
#समावेश <linux/ksm.h>
#समावेश <linux/rmap.h>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/swapops.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <linux/uaccess.h>

#समावेश "internal.h"

/* Internal flags */
#घोषणा MPOL_MF_DISCONTIG_OK (MPOL_MF_INTERNAL << 0)	/* Skip checks क्रम continuous vmas */
#घोषणा MPOL_MF_INVERT (MPOL_MF_INTERNAL << 1)		/* Invert check क्रम nodemask */

अटल काष्ठा kmem_cache *policy_cache;
अटल काष्ठा kmem_cache *sn_cache;

/* Highest zone. An specअगरic allocation क्रम a zone below that is not
   policied. */
क्रमागत zone_type policy_zone = 0;

/*
 * run-समय प्रणाली-wide शेष policy => local allocation
 */
अटल काष्ठा mempolicy शेष_policy = अणु
	.refcnt = ATOMIC_INIT(1), /* never मुक्त it */
	.mode = MPOL_PREFERRED,
	.flags = MPOL_F_LOCAL,
पूर्ण;

अटल काष्ठा mempolicy preferred_node_policy[MAX_NUMNODES];

/**
 * numa_map_to_online_node - Find बंदst online node
 * @node: Node id to start the search
 *
 * Lookup the next बंदst node by distance अगर @nid is not online.
 */
पूर्णांक numa_map_to_online_node(पूर्णांक node)
अणु
	पूर्णांक min_dist = पूर्णांक_उच्च, dist, n, min_node;

	अगर (node == NUMA_NO_NODE || node_online(node))
		वापस node;

	min_node = node;
	क्रम_each_online_node(n) अणु
		dist = node_distance(node, n);
		अगर (dist < min_dist) अणु
			min_dist = dist;
			min_node = n;
		पूर्ण
	पूर्ण

	वापस min_node;
पूर्ण
EXPORT_SYMBOL_GPL(numa_map_to_online_node);

काष्ठा mempolicy *get_task_policy(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा mempolicy *pol = p->mempolicy;
	पूर्णांक node;

	अगर (pol)
		वापस pol;

	node = numa_node_id();
	अगर (node != NUMA_NO_NODE) अणु
		pol = &preferred_node_policy[node];
		/* preferred_node_policy is not initialised early in boot */
		अगर (pol->mode)
			वापस pol;
	पूर्ण

	वापस &शेष_policy;
पूर्ण

अटल स्थिर काष्ठा mempolicy_operations अणु
	पूर्णांक (*create)(काष्ठा mempolicy *pol, स्थिर nodemask_t *nodes);
	व्योम (*rebind)(काष्ठा mempolicy *pol, स्थिर nodemask_t *nodes);
पूर्ण mpol_ops[MPOL_MAX];

अटल अंतरभूत पूर्णांक mpol_store_user_nodemask(स्थिर काष्ठा mempolicy *pol)
अणु
	वापस pol->flags & MPOL_MODE_FLAGS;
पूर्ण

अटल व्योम mpol_relative_nodemask(nodemask_t *ret, स्थिर nodemask_t *orig,
				   स्थिर nodemask_t *rel)
अणु
	nodemask_t पंचांगp;
	nodes_fold(पंचांगp, *orig, nodes_weight(*rel));
	nodes_onto(*ret, पंचांगp, *rel);
पूर्ण

अटल पूर्णांक mpol_new_पूर्णांकerleave(काष्ठा mempolicy *pol, स्थिर nodemask_t *nodes)
अणु
	अगर (nodes_empty(*nodes))
		वापस -EINVAL;
	pol->v.nodes = *nodes;
	वापस 0;
पूर्ण

अटल पूर्णांक mpol_new_preferred(काष्ठा mempolicy *pol, स्थिर nodemask_t *nodes)
अणु
	अगर (!nodes)
		pol->flags |= MPOL_F_LOCAL;	/* local allocation */
	अन्यथा अगर (nodes_empty(*nodes))
		वापस -EINVAL;			/*  no allowed nodes */
	अन्यथा
		pol->v.preferred_node = first_node(*nodes);
	वापस 0;
पूर्ण

अटल पूर्णांक mpol_new_bind(काष्ठा mempolicy *pol, स्थिर nodemask_t *nodes)
अणु
	अगर (nodes_empty(*nodes))
		वापस -EINVAL;
	pol->v.nodes = *nodes;
	वापस 0;
पूर्ण

/*
 * mpol_set_nodemask is called after mpol_new() to set up the nodemask, अगर
 * any, क्रम the new policy.  mpol_new() has alपढ़ोy validated the nodes
 * parameter with respect to the policy mode and flags.  But, we need to
 * handle an empty nodemask with MPOL_PREFERRED here.
 *
 * Must be called holding task's alloc_lock to protect task's mems_allowed
 * and mempolicy.  May also be called holding the mmap_lock क्रम ग_लिखो.
 */
अटल पूर्णांक mpol_set_nodemask(काष्ठा mempolicy *pol,
		     स्थिर nodemask_t *nodes, काष्ठा nodemask_scratch *nsc)
अणु
	पूर्णांक ret;

	/* अगर mode is MPOL_DEFAULT, pol is शून्य. This is right. */
	अगर (pol == शून्य)
		वापस 0;
	/* Check N_MEMORY */
	nodes_and(nsc->mask1,
		  cpuset_current_mems_allowed, node_states[N_MEMORY]);

	VM_BUG_ON(!nodes);
	अगर (pol->mode == MPOL_PREFERRED && nodes_empty(*nodes))
		nodes = शून्य;	/* explicit local allocation */
	अन्यथा अणु
		अगर (pol->flags & MPOL_F_RELATIVE_NODES)
			mpol_relative_nodemask(&nsc->mask2, nodes, &nsc->mask1);
		अन्यथा
			nodes_and(nsc->mask2, *nodes, nsc->mask1);

		अगर (mpol_store_user_nodemask(pol))
			pol->w.user_nodemask = *nodes;
		अन्यथा
			pol->w.cpuset_mems_allowed =
						cpuset_current_mems_allowed;
	पूर्ण

	अगर (nodes)
		ret = mpol_ops[pol->mode].create(pol, &nsc->mask2);
	अन्यथा
		ret = mpol_ops[pol->mode].create(pol, शून्य);
	वापस ret;
पूर्ण

/*
 * This function just creates a new policy, करोes some check and simple
 * initialization. You must invoke mpol_set_nodemask() to set nodes.
 */
अटल काष्ठा mempolicy *mpol_new(अचिन्हित लघु mode, अचिन्हित लघु flags,
				  nodemask_t *nodes)
अणु
	काष्ठा mempolicy *policy;

	pr_debug("setting mode %d flags %d nodes[0] %lx\n",
		 mode, flags, nodes ? nodes_addr(*nodes)[0] : NUMA_NO_NODE);

	अगर (mode == MPOL_DEFAULT) अणु
		अगर (nodes && !nodes_empty(*nodes))
			वापस ERR_PTR(-EINVAL);
		वापस शून्य;
	पूर्ण
	VM_BUG_ON(!nodes);

	/*
	 * MPOL_PREFERRED cannot be used with MPOL_F_STATIC_NODES or
	 * MPOL_F_RELATIVE_NODES अगर the nodemask is empty (local allocation).
	 * All other modes require a valid poपूर्णांकer to a non-empty nodemask.
	 */
	अगर (mode == MPOL_PREFERRED) अणु
		अगर (nodes_empty(*nodes)) अणु
			अगर (((flags & MPOL_F_STATIC_NODES) ||
			     (flags & MPOL_F_RELATIVE_NODES)))
				वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण अन्यथा अगर (mode == MPOL_LOCAL) अणु
		अगर (!nodes_empty(*nodes) ||
		    (flags & MPOL_F_STATIC_NODES) ||
		    (flags & MPOL_F_RELATIVE_NODES))
			वापस ERR_PTR(-EINVAL);
		mode = MPOL_PREFERRED;
	पूर्ण अन्यथा अगर (nodes_empty(*nodes))
		वापस ERR_PTR(-EINVAL);
	policy = kmem_cache_alloc(policy_cache, GFP_KERNEL);
	अगर (!policy)
		वापस ERR_PTR(-ENOMEM);
	atomic_set(&policy->refcnt, 1);
	policy->mode = mode;
	policy->flags = flags;

	वापस policy;
पूर्ण

/* Slow path of a mpol deकाष्ठाor. */
व्योम __mpol_put(काष्ठा mempolicy *p)
अणु
	अगर (!atomic_dec_and_test(&p->refcnt))
		वापस;
	kmem_cache_मुक्त(policy_cache, p);
पूर्ण

अटल व्योम mpol_rebind_शेष(काष्ठा mempolicy *pol, स्थिर nodemask_t *nodes)
अणु
पूर्ण

अटल व्योम mpol_rebind_nodemask(काष्ठा mempolicy *pol, स्थिर nodemask_t *nodes)
अणु
	nodemask_t पंचांगp;

	अगर (pol->flags & MPOL_F_STATIC_NODES)
		nodes_and(पंचांगp, pol->w.user_nodemask, *nodes);
	अन्यथा अगर (pol->flags & MPOL_F_RELATIVE_NODES)
		mpol_relative_nodemask(&पंचांगp, &pol->w.user_nodemask, nodes);
	अन्यथा अणु
		nodes_remap(पंचांगp, pol->v.nodes, pol->w.cpuset_mems_allowed,
								*nodes);
		pol->w.cpuset_mems_allowed = *nodes;
	पूर्ण

	अगर (nodes_empty(पंचांगp))
		पंचांगp = *nodes;

	pol->v.nodes = पंचांगp;
पूर्ण

अटल व्योम mpol_rebind_preferred(काष्ठा mempolicy *pol,
						स्थिर nodemask_t *nodes)
अणु
	nodemask_t पंचांगp;

	अगर (pol->flags & MPOL_F_STATIC_NODES) अणु
		पूर्णांक node = first_node(pol->w.user_nodemask);

		अगर (node_isset(node, *nodes)) अणु
			pol->v.preferred_node = node;
			pol->flags &= ~MPOL_F_LOCAL;
		पूर्ण अन्यथा
			pol->flags |= MPOL_F_LOCAL;
	पूर्ण अन्यथा अगर (pol->flags & MPOL_F_RELATIVE_NODES) अणु
		mpol_relative_nodemask(&पंचांगp, &pol->w.user_nodemask, nodes);
		pol->v.preferred_node = first_node(पंचांगp);
	पूर्ण अन्यथा अगर (!(pol->flags & MPOL_F_LOCAL)) अणु
		pol->v.preferred_node = node_remap(pol->v.preferred_node,
						   pol->w.cpuset_mems_allowed,
						   *nodes);
		pol->w.cpuset_mems_allowed = *nodes;
	पूर्ण
पूर्ण

/*
 * mpol_rebind_policy - Migrate a policy to a dअगरferent set of nodes
 *
 * Per-vma policies are रक्षित by mmap_lock. Allocations using per-task
 * policies are रक्षित by task->mems_allowed_seq to prevent a premature
 * OOM/allocation failure due to parallel nodemask modअगरication.
 */
अटल व्योम mpol_rebind_policy(काष्ठा mempolicy *pol, स्थिर nodemask_t *newmask)
अणु
	अगर (!pol)
		वापस;
	अगर (!mpol_store_user_nodemask(pol) && !(pol->flags & MPOL_F_LOCAL) &&
	    nodes_equal(pol->w.cpuset_mems_allowed, *newmask))
		वापस;

	mpol_ops[pol->mode].rebind(pol, newmask);
पूर्ण

/*
 * Wrapper क्रम mpol_rebind_policy() that just requires task
 * poपूर्णांकer, and updates task mempolicy.
 *
 * Called with task's alloc_lock held.
 */

व्योम mpol_rebind_task(काष्ठा task_काष्ठा *tsk, स्थिर nodemask_t *new)
अणु
	mpol_rebind_policy(tsk->mempolicy, new);
पूर्ण

/*
 * Rebind each vma in mm to new nodemask.
 *
 * Call holding a reference to mm.  Takes mm->mmap_lock during call.
 */

व्योम mpol_rebind_mm(काष्ठा mm_काष्ठा *mm, nodemask_t *new)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	mmap_ग_लिखो_lock(mm);
	क्रम (vma = mm->mmap; vma; vma = vma->vm_next)
		mpol_rebind_policy(vma->vm_policy, new);
	mmap_ग_लिखो_unlock(mm);
पूर्ण

अटल स्थिर काष्ठा mempolicy_operations mpol_ops[MPOL_MAX] = अणु
	[MPOL_DEFAULT] = अणु
		.rebind = mpol_rebind_शेष,
	पूर्ण,
	[MPOL_INTERLEAVE] = अणु
		.create = mpol_new_पूर्णांकerleave,
		.rebind = mpol_rebind_nodemask,
	पूर्ण,
	[MPOL_PREFERRED] = अणु
		.create = mpol_new_preferred,
		.rebind = mpol_rebind_preferred,
	पूर्ण,
	[MPOL_BIND] = अणु
		.create = mpol_new_bind,
		.rebind = mpol_rebind_nodemask,
	पूर्ण,
पूर्ण;

अटल पूर्णांक migrate_page_add(काष्ठा page *page, काष्ठा list_head *pagelist,
				अचिन्हित दीर्घ flags);

काष्ठा queue_pages अणु
	काष्ठा list_head *pagelist;
	अचिन्हित दीर्घ flags;
	nodemask_t *nmask;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	काष्ठा vm_area_काष्ठा *first;
पूर्ण;

/*
 * Check अगर the page's nid is in qp->nmask.
 *
 * If MPOL_MF_INVERT is set in qp->flags, check अगर the nid is
 * in the invert of qp->nmask.
 */
अटल अंतरभूत bool queue_pages_required(काष्ठा page *page,
					काष्ठा queue_pages *qp)
अणु
	पूर्णांक nid = page_to_nid(page);
	अचिन्हित दीर्घ flags = qp->flags;

	वापस node_isset(nid, *qp->nmask) == !(flags & MPOL_MF_INVERT);
पूर्ण

/*
 * queue_pages_pmd() has four possible वापस values:
 * 0 - pages are placed on the right node or queued successfully.
 * 1 - there is unmovable page, and MPOL_MF_MOVE* & MPOL_MF_STRICT were
 *     specअगरied.
 * 2 - THP was split.
 * -EIO - is migration entry or only MPOL_MF_STRICT was specअगरied and an
 *        existing page was alपढ़ोy on a node that करोes not follow the
 *        policy.
 */
अटल पूर्णांक queue_pages_pmd(pmd_t *pmd, spinlock_t *ptl, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
	__releases(ptl)
अणु
	पूर्णांक ret = 0;
	काष्ठा page *page;
	काष्ठा queue_pages *qp = walk->निजी;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(is_pmd_migration_entry(*pmd))) अणु
		ret = -EIO;
		जाओ unlock;
	पूर्ण
	page = pmd_page(*pmd);
	अगर (is_huge_zero_page(page)) अणु
		spin_unlock(ptl);
		__split_huge_pmd(walk->vma, pmd, addr, false, शून्य);
		ret = 2;
		जाओ out;
	पूर्ण
	अगर (!queue_pages_required(page, qp))
		जाओ unlock;

	flags = qp->flags;
	/* go to thp migration */
	अगर (flags & (MPOL_MF_MOVE | MPOL_MF_MOVE_ALL)) अणु
		अगर (!vma_migratable(walk->vma) ||
		    migrate_page_add(page, qp->pagelist, flags)) अणु
			ret = 1;
			जाओ unlock;
		पूर्ण
	पूर्ण अन्यथा
		ret = -EIO;
unlock:
	spin_unlock(ptl);
out:
	वापस ret;
पूर्ण

/*
 * Scan through pages checking अगर pages follow certain conditions,
 * and move them to the pagelist अगर they करो.
 *
 * queue_pages_pte_range() has three possible वापस values:
 * 0 - pages are placed on the right node or queued successfully.
 * 1 - there is unmovable page, and MPOL_MF_MOVE* & MPOL_MF_STRICT were
 *     specअगरied.
 * -EIO - only MPOL_MF_STRICT was specअगरied and an existing page was alपढ़ोy
 *        on a node that करोes not follow the policy.
 */
अटल पूर्णांक queue_pages_pte_range(pmd_t *pmd, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
अणु
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	काष्ठा page *page;
	काष्ठा queue_pages *qp = walk->निजी;
	अचिन्हित दीर्घ flags = qp->flags;
	पूर्णांक ret;
	bool has_unmovable = false;
	pte_t *pte, *mapped_pte;
	spinlock_t *ptl;

	ptl = pmd_trans_huge_lock(pmd, vma);
	अगर (ptl) अणु
		ret = queue_pages_pmd(pmd, ptl, addr, end, walk);
		अगर (ret != 2)
			वापस ret;
	पूर्ण
	/* THP was split, fall through to pte walk */

	अगर (pmd_trans_unstable(pmd))
		वापस 0;

	mapped_pte = pte = pte_offset_map_lock(walk->mm, pmd, addr, &ptl);
	क्रम (; addr != end; pte++, addr += PAGE_SIZE) अणु
		अगर (!pte_present(*pte))
			जारी;
		page = vm_normal_page(vma, addr, *pte);
		अगर (!page)
			जारी;
		/*
		 * vm_normal_page() filters out zero pages, but there might
		 * still be PageReserved pages to skip, perhaps in a VDSO.
		 */
		अगर (PageReserved(page))
			जारी;
		अगर (!queue_pages_required(page, qp))
			जारी;
		अगर (flags & (MPOL_MF_MOVE | MPOL_MF_MOVE_ALL)) अणु
			/* MPOL_MF_STRICT must be specअगरied अगर we get here */
			अगर (!vma_migratable(vma)) अणु
				has_unmovable = true;
				अवरोध;
			पूर्ण

			/*
			 * Do not पात immediately since there may be
			 * temporary off LRU pages in the range.  Still
			 * need migrate other LRU pages.
			 */
			अगर (migrate_page_add(page, qp->pagelist, flags))
				has_unmovable = true;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	pte_unmap_unlock(mapped_pte, ptl);
	cond_resched();

	अगर (has_unmovable)
		वापस 1;

	वापस addr != end ? -EIO : 0;
पूर्ण

अटल पूर्णांक queue_pages_hugetlb(pte_t *pte, अचिन्हित दीर्घ hmask,
			       अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			       काष्ठा mm_walk *walk)
अणु
	पूर्णांक ret = 0;
#अगर_घोषित CONFIG_HUGETLB_PAGE
	काष्ठा queue_pages *qp = walk->निजी;
	अचिन्हित दीर्घ flags = (qp->flags & MPOL_MF_VALID);
	काष्ठा page *page;
	spinlock_t *ptl;
	pte_t entry;

	ptl = huge_pte_lock(hstate_vma(walk->vma), walk->mm, pte);
	entry = huge_ptep_get(pte);
	अगर (!pte_present(entry))
		जाओ unlock;
	page = pte_page(entry);
	अगर (!queue_pages_required(page, qp))
		जाओ unlock;

	अगर (flags == MPOL_MF_STRICT) अणु
		/*
		 * STRICT alone means only detecting misplaced page and no
		 * need to further check other vma.
		 */
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	अगर (!vma_migratable(walk->vma)) अणु
		/*
		 * Must be STRICT with MOVE*, otherwise .test_walk() have
		 * stopped walking current vma.
		 * Detecting misplaced page but allow migrating pages which
		 * have been queued.
		 */
		ret = 1;
		जाओ unlock;
	पूर्ण

	/* With MPOL_MF_MOVE, we migrate only unshared hugepage. */
	अगर (flags & (MPOL_MF_MOVE_ALL) ||
	    (flags & MPOL_MF_MOVE && page_mapcount(page) == 1)) अणु
		अगर (!isolate_huge_page(page, qp->pagelist) &&
			(flags & MPOL_MF_STRICT))
			/*
			 * Failed to isolate page but allow migrating pages
			 * which have been queued.
			 */
			ret = 1;
	पूर्ण
unlock:
	spin_unlock(ptl);
#अन्यथा
	BUG();
#पूर्ण_अगर
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_NUMA_BALANCING
/*
 * This is used to mark a range of भव addresses to be inaccessible.
 * These are later cleared by a NUMA hपूर्णांकing fault. Depending on these
 * faults, pages may be migrated क्रम better NUMA placement.
 *
 * This is assuming that NUMA faults are handled using PROT_NONE. If
 * an architecture makes a dअगरferent choice, it will need further
 * changes to the core.
 */
अचिन्हित दीर्घ change_prot_numa(काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	पूर्णांक nr_updated;

	nr_updated = change_protection(vma, addr, end, PAGE_NONE, MM_CP_PROT_NUMA);
	अगर (nr_updated)
		count_vm_numa_events(NUMA_PTE_UPDATES, nr_updated);

	वापस nr_updated;
पूर्ण
#अन्यथा
अटल अचिन्हित दीर्घ change_prot_numa(काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

अटल पूर्णांक queue_pages_test_walk(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				काष्ठा mm_walk *walk)
अणु
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	काष्ठा queue_pages *qp = walk->निजी;
	अचिन्हित दीर्घ endvma = vma->vm_end;
	अचिन्हित दीर्घ flags = qp->flags;

	/* range check first */
	VM_BUG_ON_VMA(!range_in_vma(vma, start, end), vma);

	अगर (!qp->first) अणु
		qp->first = vma;
		अगर (!(flags & MPOL_MF_DISCONTIG_OK) &&
			(qp->start < vma->vm_start))
			/* hole at head side of range */
			वापस -EFAULT;
	पूर्ण
	अगर (!(flags & MPOL_MF_DISCONTIG_OK) &&
		((vma->vm_end < qp->end) &&
		(!vma->vm_next || vma->vm_end < vma->vm_next->vm_start)))
		/* hole at middle or tail of range */
		वापस -EFAULT;

	/*
	 * Need check MPOL_MF_STRICT to वापस -EIO अगर possible
	 * regardless of vma_migratable
	 */
	अगर (!vma_migratable(vma) &&
	    !(flags & MPOL_MF_STRICT))
		वापस 1;

	अगर (endvma > end)
		endvma = end;

	अगर (flags & MPOL_MF_LAZY) अणु
		/* Similar to task_numa_work, skip inaccessible VMAs */
		अगर (!is_vm_hugetlb_page(vma) && vma_is_accessible(vma) &&
			!(vma->vm_flags & VM_MIXEDMAP))
			change_prot_numa(vma, start, endvma);
		वापस 1;
	पूर्ण

	/* queue pages from current vma */
	अगर (flags & MPOL_MF_VALID)
		वापस 0;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops queue_pages_walk_ops = अणु
	.hugetlb_entry		= queue_pages_hugetlb,
	.pmd_entry		= queue_pages_pte_range,
	.test_walk		= queue_pages_test_walk,
पूर्ण;

/*
 * Walk through page tables and collect pages to be migrated.
 *
 * If pages found in a given range are on a set of nodes (determined by
 * @nodes and @flags,) it's isolated and queued to the pagelist which is
 * passed via @निजी.
 *
 * queue_pages_range() has three possible वापस values:
 * 1 - there is unmovable page, but MPOL_MF_MOVE* & MPOL_MF_STRICT were
 *     specअगरied.
 * 0 - queue pages successfully or no misplaced page.
 * त्रुटि_सं - i.e. misplaced pages with MPOL_MF_STRICT specअगरied (-EIO) or
 *         memory range specअगरied by nodemask and maxnode poपूर्णांकs outside
 *         your accessible address space (-EFAULT)
 */
अटल पूर्णांक
queue_pages_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		nodemask_t *nodes, अचिन्हित दीर्घ flags,
		काष्ठा list_head *pagelist)
अणु
	पूर्णांक err;
	काष्ठा queue_pages qp = अणु
		.pagelist = pagelist,
		.flags = flags,
		.nmask = nodes,
		.start = start,
		.end = end,
		.first = शून्य,
	पूर्ण;

	err = walk_page_range(mm, start, end, &queue_pages_walk_ops, &qp);

	अगर (!qp.first)
		/* whole range in hole */
		err = -EFAULT;

	वापस err;
पूर्ण

/*
 * Apply policy to a single VMA
 * This must be called with the mmap_lock held क्रम writing.
 */
अटल पूर्णांक vma_replace_policy(काष्ठा vm_area_काष्ठा *vma,
						काष्ठा mempolicy *pol)
अणु
	पूर्णांक err;
	काष्ठा mempolicy *old;
	काष्ठा mempolicy *new;

	pr_debug("vma %lx-%lx/%lx vm_ops %p vm_file %p set_policy %p\n",
		 vma->vm_start, vma->vm_end, vma->vm_pgoff,
		 vma->vm_ops, vma->vm_file,
		 vma->vm_ops ? vma->vm_ops->set_policy : शून्य);

	new = mpol_dup(pol);
	अगर (IS_ERR(new))
		वापस PTR_ERR(new);

	अगर (vma->vm_ops && vma->vm_ops->set_policy) अणु
		err = vma->vm_ops->set_policy(vma, new);
		अगर (err)
			जाओ err_out;
	पूर्ण

	old = vma->vm_policy;
	vma->vm_policy = new; /* रक्षित by mmap_lock */
	mpol_put(old);

	वापस 0;
 err_out:
	mpol_put(new);
	वापस err;
पूर्ण

/* Step 2: apply policy to a range and करो splits. */
अटल पूर्णांक mbind_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
		       अचिन्हित दीर्घ end, काष्ठा mempolicy *new_pol)
अणु
	काष्ठा vm_area_काष्ठा *next;
	काष्ठा vm_area_काष्ठा *prev;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक err = 0;
	pgoff_t pgoff;
	अचिन्हित दीर्घ vmstart;
	अचिन्हित दीर्घ vmend;

	vma = find_vma(mm, start);
	VM_BUG_ON(!vma);

	prev = vma->vm_prev;
	अगर (start > vma->vm_start)
		prev = vma;

	क्रम (; vma && vma->vm_start < end; prev = vma, vma = next) अणु
		next = vma->vm_next;
		vmstart = max(start, vma->vm_start);
		vmend   = min(end, vma->vm_end);

		अगर (mpol_equal(vma_policy(vma), new_pol))
			जारी;

		pgoff = vma->vm_pgoff +
			((vmstart - vma->vm_start) >> PAGE_SHIFT);
		prev = vma_merge(mm, prev, vmstart, vmend, vma->vm_flags,
				 vma->anon_vma, vma->vm_file, pgoff,
				 new_pol, vma->vm_userfaultfd_ctx);
		अगर (prev) अणु
			vma = prev;
			next = vma->vm_next;
			अगर (mpol_equal(vma_policy(vma), new_pol))
				जारी;
			/* vma_merge() joined vma && vma->next, हाल 8 */
			जाओ replace;
		पूर्ण
		अगर (vma->vm_start != vmstart) अणु
			err = split_vma(vma->vm_mm, vma, vmstart, 1);
			अगर (err)
				जाओ out;
		पूर्ण
		अगर (vma->vm_end != vmend) अणु
			err = split_vma(vma->vm_mm, vma, vmend, 0);
			अगर (err)
				जाओ out;
		पूर्ण
 replace:
		err = vma_replace_policy(vma, new_pol);
		अगर (err)
			जाओ out;
	पूर्ण

 out:
	वापस err;
पूर्ण

/* Set the process memory policy */
अटल दीर्घ करो_set_mempolicy(अचिन्हित लघु mode, अचिन्हित लघु flags,
			     nodemask_t *nodes)
अणु
	काष्ठा mempolicy *new, *old;
	NODEMASK_SCRATCH(scratch);
	पूर्णांक ret;

	अगर (!scratch)
		वापस -ENOMEM;

	new = mpol_new(mode, flags, nodes);
	अगर (IS_ERR(new)) अणु
		ret = PTR_ERR(new);
		जाओ out;
	पूर्ण

	अगर (flags & MPOL_F_NUMA_BALANCING) अणु
		अगर (new && new->mode == MPOL_BIND) अणु
			new->flags |= (MPOL_F_MOF | MPOL_F_MORON);
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			mpol_put(new);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = mpol_set_nodemask(new, nodes, scratch);
	अगर (ret) अणु
		mpol_put(new);
		जाओ out;
	पूर्ण
	task_lock(current);
	old = current->mempolicy;
	current->mempolicy = new;
	अगर (new && new->mode == MPOL_INTERLEAVE)
		current->il_prev = MAX_NUMNODES-1;
	task_unlock(current);
	mpol_put(old);
	ret = 0;
out:
	NODEMASK_SCRATCH_FREE(scratch);
	वापस ret;
पूर्ण

/*
 * Return nodemask क्रम policy क्रम get_mempolicy() query
 *
 * Called with task's alloc_lock held
 */
अटल व्योम get_policy_nodemask(काष्ठा mempolicy *p, nodemask_t *nodes)
अणु
	nodes_clear(*nodes);
	अगर (p == &शेष_policy)
		वापस;

	चयन (p->mode) अणु
	हाल MPOL_BIND:
	हाल MPOL_INTERLEAVE:
		*nodes = p->v.nodes;
		अवरोध;
	हाल MPOL_PREFERRED:
		अगर (!(p->flags & MPOL_F_LOCAL))
			node_set(p->v.preferred_node, *nodes);
		/* अन्यथा वापस empty node mask क्रम local allocation */
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक lookup_node(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	काष्ठा page *p = शून्य;
	पूर्णांक err;

	पूर्णांक locked = 1;
	err = get_user_pages_locked(addr & PAGE_MASK, 1, 0, &p, &locked);
	अगर (err > 0) अणु
		err = page_to_nid(p);
		put_page(p);
	पूर्ण
	अगर (locked)
		mmap_पढ़ो_unlock(mm);
	वापस err;
पूर्ण

/* Retrieve NUMA policy */
अटल दीर्घ करो_get_mempolicy(पूर्णांक *policy, nodemask_t *nmask,
			     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक err;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma = शून्य;
	काष्ठा mempolicy *pol = current->mempolicy, *pol_refcount = शून्य;

	अगर (flags &
		~(अचिन्हित दीर्घ)(MPOL_F_NODE|MPOL_F_ADDR|MPOL_F_MEMS_ALLOWED))
		वापस -EINVAL;

	अगर (flags & MPOL_F_MEMS_ALLOWED) अणु
		अगर (flags & (MPOL_F_NODE|MPOL_F_ADDR))
			वापस -EINVAL;
		*policy = 0;	/* just so it's initialized */
		task_lock(current);
		*nmask  = cpuset_current_mems_allowed;
		task_unlock(current);
		वापस 0;
	पूर्ण

	अगर (flags & MPOL_F_ADDR) अणु
		/*
		 * Do NOT fall back to task policy अगर the
		 * vma/shared policy at addr is शून्य.  We
		 * want to वापस MPOL_DEFAULT in this हाल.
		 */
		mmap_पढ़ो_lock(mm);
		vma = find_vma_पूर्णांकersection(mm, addr, addr+1);
		अगर (!vma) अणु
			mmap_पढ़ो_unlock(mm);
			वापस -EFAULT;
		पूर्ण
		अगर (vma->vm_ops && vma->vm_ops->get_policy)
			pol = vma->vm_ops->get_policy(vma, addr);
		अन्यथा
			pol = vma->vm_policy;
	पूर्ण अन्यथा अगर (addr)
		वापस -EINVAL;

	अगर (!pol)
		pol = &शेष_policy;	/* indicates शेष behavior */

	अगर (flags & MPOL_F_NODE) अणु
		अगर (flags & MPOL_F_ADDR) अणु
			/*
			 * Take a refcount on the mpol, lookup_node()
			 * will drop the mmap_lock, so after calling
			 * lookup_node() only "pol" reमुख्यs valid, "vma"
			 * is stale.
			 */
			pol_refcount = pol;
			vma = शून्य;
			mpol_get(pol);
			err = lookup_node(mm, addr);
			अगर (err < 0)
				जाओ out;
			*policy = err;
		पूर्ण अन्यथा अगर (pol == current->mempolicy &&
				pol->mode == MPOL_INTERLEAVE) अणु
			*policy = next_node_in(current->il_prev, pol->v.nodes);
		पूर्ण अन्यथा अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		*policy = pol == &शेष_policy ? MPOL_DEFAULT :
						pol->mode;
		/*
		 * Internal mempolicy flags must be masked off beक्रमe exposing
		 * the policy to userspace.
		 */
		*policy |= (pol->flags & MPOL_MODE_FLAGS);
	पूर्ण

	err = 0;
	अगर (nmask) अणु
		अगर (mpol_store_user_nodemask(pol)) अणु
			*nmask = pol->w.user_nodemask;
		पूर्ण अन्यथा अणु
			task_lock(current);
			get_policy_nodemask(pol, nmask);
			task_unlock(current);
		पूर्ण
	पूर्ण

 out:
	mpol_cond_put(pol);
	अगर (vma)
		mmap_पढ़ो_unlock(mm);
	अगर (pol_refcount)
		mpol_put(pol_refcount);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_MIGRATION
/*
 * page migration, thp tail pages can be passed.
 */
अटल पूर्णांक migrate_page_add(काष्ठा page *page, काष्ठा list_head *pagelist,
				अचिन्हित दीर्घ flags)
अणु
	काष्ठा page *head = compound_head(page);
	/*
	 * Aव्योम migrating a page that is shared with others.
	 */
	अगर ((flags & MPOL_MF_MOVE_ALL) || page_mapcount(head) == 1) अणु
		अगर (!isolate_lru_page(head)) अणु
			list_add_tail(&head->lru, pagelist);
			mod_node_page_state(page_pgdat(head),
				NR_ISOLATED_ANON + page_is_file_lru(head),
				thp_nr_pages(head));
		पूर्ण अन्यथा अगर (flags & MPOL_MF_STRICT) अणु
			/*
			 * Non-movable page may reach here.  And, there may be
			 * temporary off LRU pages or non-LRU movable pages.
			 * Treat them as unmovable pages since they can't be
			 * isolated, so they can't be moved at the moment.  It
			 * should वापस -EIO क्रम this हाल too.
			 */
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Migrate pages from one node to a target node.
 * Returns error or the number of pages not migrated.
 */
अटल पूर्णांक migrate_to_node(काष्ठा mm_काष्ठा *mm, पूर्णांक source, पूर्णांक dest,
			   पूर्णांक flags)
अणु
	nodemask_t nmask;
	LIST_HEAD(pagelist);
	पूर्णांक err = 0;
	काष्ठा migration_target_control mtc = अणु
		.nid = dest,
		.gfp_mask = GFP_HIGHUSER_MOVABLE | __GFP_THISNODE,
	पूर्ण;

	nodes_clear(nmask);
	node_set(source, nmask);

	/*
	 * This करोes not "check" the range but isolates all pages that
	 * need migration.  Between passing in the full user address
	 * space range and MPOL_MF_DISCONTIG_OK, this call can not fail.
	 */
	VM_BUG_ON(!(flags & (MPOL_MF_MOVE | MPOL_MF_MOVE_ALL)));
	queue_pages_range(mm, mm->mmap->vm_start, mm->task_size, &nmask,
			flags | MPOL_MF_DISCONTIG_OK, &pagelist);

	अगर (!list_empty(&pagelist)) अणु
		err = migrate_pages(&pagelist, alloc_migration_target, शून्य,
				(अचिन्हित दीर्घ)&mtc, MIGRATE_SYNC, MR_SYSCALL);
		अगर (err)
			putback_movable_pages(&pagelist);
	पूर्ण

	वापस err;
पूर्ण

/*
 * Move pages between the two nodesets so as to preserve the physical
 * layout as much as possible.
 *
 * Returns the number of page that could not be moved.
 */
पूर्णांक करो_migrate_pages(काष्ठा mm_काष्ठा *mm, स्थिर nodemask_t *from,
		     स्थिर nodemask_t *to, पूर्णांक flags)
अणु
	पूर्णांक busy = 0;
	पूर्णांक err = 0;
	nodemask_t पंचांगp;

	lru_cache_disable();

	mmap_पढ़ो_lock(mm);

	/*
	 * Find a 'source' bit set in 'tmp' whose corresponding 'dest'
	 * bit in 'to' is not also set in 'tmp'.  Clear the found 'source'
	 * bit in 'tmp', and वापस that <source, dest> pair क्रम migration.
	 * The pair of nodemasks 'to' and 'from' define the map.
	 *
	 * If no pair of bits is found that way, fallback to picking some
	 * pair of 'source' and 'dest' bits that are not the same.  If the
	 * 'source' and 'dest' bits are the same, this represents a node
	 * that will be migrating to itself, so no pages need move.
	 *
	 * If no bits are left in 'tmp', or अगर all reमुख्यing bits left
	 * in 'tmp' correspond to the same bit in 'to', वापस false
	 * (nothing left to migrate).
	 *
	 * This lets us pick a pair of nodes to migrate between, such that
	 * अगर possible the dest node is not alपढ़ोy occupied by some other
	 * source node, minimizing the risk of overloading the memory on a
	 * node that would happen अगर we migrated incoming memory to a node
	 * beक्रमe migrating outgoing memory source that same node.
	 *
	 * A single scan of पंचांगp is sufficient.  As we go, we remember the
	 * most recent <s, d> pair that moved (s != d).  If we find a pair
	 * that not only moved, but what's better, moved to an empty slot
	 * (d is not set in पंचांगp), then we अवरोध out then, with that pair.
	 * Otherwise when we finish scanning from_पंचांगp, we at least have the
	 * most recent <s, d> pair that moved.  If we get all the way through
	 * the scan of पंचांगp without finding any node that moved, much less
	 * moved to an empty node, then there is nothing left worth migrating.
	 */

	पंचांगp = *from;
	जबतक (!nodes_empty(पंचांगp)) अणु
		पूर्णांक s, d;
		पूर्णांक source = NUMA_NO_NODE;
		पूर्णांक dest = 0;

		क्रम_each_node_mask(s, पंचांगp) अणु

			/*
			 * करो_migrate_pages() tries to मुख्यtain the relative
			 * node relationship of the pages established between
			 * thपढ़ोs and memory areas.
                         *
			 * However अगर the number of source nodes is not equal to
			 * the number of destination nodes we can not preserve
			 * this node relative relationship.  In that हाल, skip
			 * copying memory from a node that is in the destination
			 * mask.
			 *
			 * Example: [2,3,4] -> [3,4,5] moves everything.
			 *          [0-7] - > [3,4,5] moves only 0,1,2,6,7.
			 */

			अगर ((nodes_weight(*from) != nodes_weight(*to)) &&
						(node_isset(s, *to)))
				जारी;

			d = node_remap(s, *from, *to);
			अगर (s == d)
				जारी;

			source = s;	/* Node moved. Memorize */
			dest = d;

			/* dest not in reमुख्यing from nodes? */
			अगर (!node_isset(dest, पंचांगp))
				अवरोध;
		पूर्ण
		अगर (source == NUMA_NO_NODE)
			अवरोध;

		node_clear(source, पंचांगp);
		err = migrate_to_node(mm, source, dest, flags);
		अगर (err > 0)
			busy += err;
		अगर (err < 0)
			अवरोध;
	पूर्ण
	mmap_पढ़ो_unlock(mm);

	lru_cache_enable();
	अगर (err < 0)
		वापस err;
	वापस busy;

पूर्ण

/*
 * Allocate a new page क्रम page migration based on vma policy.
 * Start by assuming the page is mapped by the same vma as contains @start.
 * Search क्रमward from there, अगर not.  N.B., this assumes that the
 * list of pages handed to migrate_pages()--which is how we get here--
 * is in भव address order.
 */
अटल काष्ठा page *new_page(काष्ठा page *page, अचिन्हित दीर्घ start)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ address;

	vma = find_vma(current->mm, start);
	जबतक (vma) अणु
		address = page_address_in_vma(page, vma);
		अगर (address != -EFAULT)
			अवरोध;
		vma = vma->vm_next;
	पूर्ण

	अगर (PageHuge(page)) अणु
		वापस alloc_huge_page_vma(page_hstate(compound_head(page)),
				vma, address);
	पूर्ण अन्यथा अगर (PageTransHuge(page)) अणु
		काष्ठा page *thp;

		thp = alloc_hugepage_vma(GFP_TRANSHUGE, vma, address,
					 HPAGE_PMD_ORDER);
		अगर (!thp)
			वापस शून्य;
		prep_transhuge_page(thp);
		वापस thp;
	पूर्ण
	/*
	 * अगर !vma, alloc_page_vma() will use task or प्रणाली शेष policy
	 */
	वापस alloc_page_vma(GFP_HIGHUSER_MOVABLE | __GFP_RETRY_MAYFAIL,
			vma, address);
पूर्ण
#अन्यथा

अटल पूर्णांक migrate_page_add(काष्ठा page *page, काष्ठा list_head *pagelist,
				अचिन्हित दीर्घ flags)
अणु
	वापस -EIO;
पूर्ण

पूर्णांक करो_migrate_pages(काष्ठा mm_काष्ठा *mm, स्थिर nodemask_t *from,
		     स्थिर nodemask_t *to, पूर्णांक flags)
अणु
	वापस -ENOSYS;
पूर्ण

अटल काष्ठा page *new_page(काष्ठा page *page, अचिन्हित दीर्घ start)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल दीर्घ करो_mbind(अचिन्हित दीर्घ start, अचिन्हित दीर्घ len,
		     अचिन्हित लघु mode, अचिन्हित लघु mode_flags,
		     nodemask_t *nmask, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा mempolicy *new;
	अचिन्हित दीर्घ end;
	पूर्णांक err;
	पूर्णांक ret;
	LIST_HEAD(pagelist);

	अगर (flags & ~(अचिन्हित दीर्घ)MPOL_MF_VALID)
		वापस -EINVAL;
	अगर ((flags & MPOL_MF_MOVE_ALL) && !capable(CAP_SYS_NICE))
		वापस -EPERM;

	अगर (start & ~PAGE_MASK)
		वापस -EINVAL;

	अगर (mode == MPOL_DEFAULT)
		flags &= ~MPOL_MF_STRICT;

	len = (len + PAGE_SIZE - 1) & PAGE_MASK;
	end = start + len;

	अगर (end < start)
		वापस -EINVAL;
	अगर (end == start)
		वापस 0;

	new = mpol_new(mode, mode_flags, nmask);
	अगर (IS_ERR(new))
		वापस PTR_ERR(new);

	अगर (flags & MPOL_MF_LAZY)
		new->flags |= MPOL_F_MOF;

	/*
	 * If we are using the शेष policy then operation
	 * on discontinuous address spaces is okay after all
	 */
	अगर (!new)
		flags |= MPOL_MF_DISCONTIG_OK;

	pr_debug("mbind %lx-%lx mode:%d flags:%d nodes:%lx\n",
		 start, start + len, mode, mode_flags,
		 nmask ? nodes_addr(*nmask)[0] : NUMA_NO_NODE);

	अगर (flags & (MPOL_MF_MOVE | MPOL_MF_MOVE_ALL)) अणु

		lru_cache_disable();
	पूर्ण
	अणु
		NODEMASK_SCRATCH(scratch);
		अगर (scratch) अणु
			mmap_ग_लिखो_lock(mm);
			err = mpol_set_nodemask(new, nmask, scratch);
			अगर (err)
				mmap_ग_लिखो_unlock(mm);
		पूर्ण अन्यथा
			err = -ENOMEM;
		NODEMASK_SCRATCH_FREE(scratch);
	पूर्ण
	अगर (err)
		जाओ mpol_out;

	ret = queue_pages_range(mm, start, end, nmask,
			  flags | MPOL_MF_INVERT, &pagelist);

	अगर (ret < 0) अणु
		err = ret;
		जाओ up_out;
	पूर्ण

	err = mbind_range(mm, start, end, new);

	अगर (!err) अणु
		पूर्णांक nr_failed = 0;

		अगर (!list_empty(&pagelist)) अणु
			WARN_ON_ONCE(flags & MPOL_MF_LAZY);
			nr_failed = migrate_pages(&pagelist, new_page, शून्य,
				start, MIGRATE_SYNC, MR_MEMPOLICY_MBIND);
			अगर (nr_failed)
				putback_movable_pages(&pagelist);
		पूर्ण

		अगर ((ret > 0) || (nr_failed && (flags & MPOL_MF_STRICT)))
			err = -EIO;
	पूर्ण अन्यथा अणु
up_out:
		अगर (!list_empty(&pagelist))
			putback_movable_pages(&pagelist);
	पूर्ण

	mmap_ग_लिखो_unlock(mm);
mpol_out:
	mpol_put(new);
	अगर (flags & (MPOL_MF_MOVE | MPOL_MF_MOVE_ALL))
		lru_cache_enable();
	वापस err;
पूर्ण

/*
 * User space पूर्णांकerface with variable sized biपंचांगaps क्रम nodelists.
 */

/* Copy a node mask from user space. */
अटल पूर्णांक get_nodes(nodemask_t *nodes, स्थिर अचिन्हित दीर्घ __user *nmask,
		     अचिन्हित दीर्घ maxnode)
अणु
	अचिन्हित दीर्घ k;
	अचिन्हित दीर्घ t;
	अचिन्हित दीर्घ nदीर्घs;
	अचिन्हित दीर्घ endmask;

	--maxnode;
	nodes_clear(*nodes);
	अगर (maxnode == 0 || !nmask)
		वापस 0;
	अगर (maxnode > PAGE_SIZE*BITS_PER_BYTE)
		वापस -EINVAL;

	nदीर्घs = BITS_TO_LONGS(maxnode);
	अगर ((maxnode % BITS_PER_LONG) == 0)
		endmask = ~0UL;
	अन्यथा
		endmask = (1UL << (maxnode % BITS_PER_LONG)) - 1;

	/*
	 * When the user specअगरied more nodes than supported just check
	 * अगर the non supported part is all zero.
	 *
	 * If maxnode have more दीर्घs than MAX_NUMNODES, check
	 * the bits in that area first. And then go through to
	 * check the rest bits which equal or bigger than MAX_NUMNODES.
	 * Otherwise, just check bits [MAX_NUMNODES, maxnode).
	 */
	अगर (nदीर्घs > BITS_TO_LONGS(MAX_NUMNODES)) अणु
		क्रम (k = BITS_TO_LONGS(MAX_NUMNODES); k < nदीर्घs; k++) अणु
			अगर (get_user(t, nmask + k))
				वापस -EFAULT;
			अगर (k == nदीर्घs - 1) अणु
				अगर (t & endmask)
					वापस -EINVAL;
			पूर्ण अन्यथा अगर (t)
				वापस -EINVAL;
		पूर्ण
		nदीर्घs = BITS_TO_LONGS(MAX_NUMNODES);
		endmask = ~0UL;
	पूर्ण

	अगर (maxnode > MAX_NUMNODES && MAX_NUMNODES % BITS_PER_LONG != 0) अणु
		अचिन्हित दीर्घ valid_mask = endmask;

		valid_mask &= ~((1UL << (MAX_NUMNODES % BITS_PER_LONG)) - 1);
		अगर (get_user(t, nmask + nदीर्घs - 1))
			वापस -EFAULT;
		अगर (t & valid_mask)
			वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(nodes_addr(*nodes), nmask, nदीर्घs*माप(अचिन्हित दीर्घ)))
		वापस -EFAULT;
	nodes_addr(*nodes)[nदीर्घs-1] &= endmask;
	वापस 0;
पूर्ण

/* Copy a kernel node mask to user space */
अटल पूर्णांक copy_nodes_to_user(अचिन्हित दीर्घ __user *mask, अचिन्हित दीर्घ maxnode,
			      nodemask_t *nodes)
अणु
	अचिन्हित दीर्घ copy = ALIGN(maxnode-1, 64) / 8;
	अचिन्हित पूर्णांक nbytes = BITS_TO_LONGS(nr_node_ids) * माप(दीर्घ);

	अगर (copy > nbytes) अणु
		अगर (copy > PAGE_SIZE)
			वापस -EINVAL;
		अगर (clear_user((अक्षर __user *)mask + nbytes, copy - nbytes))
			वापस -EFAULT;
		copy = nbytes;
	पूर्ण
	वापस copy_to_user(mask, nodes_addr(*nodes), copy) ? -EFAULT : 0;
पूर्ण

अटल दीर्घ kernel_mbind(अचिन्हित दीर्घ start, अचिन्हित दीर्घ len,
			 अचिन्हित दीर्घ mode, स्थिर अचिन्हित दीर्घ __user *nmask,
			 अचिन्हित दीर्घ maxnode, अचिन्हित पूर्णांक flags)
अणु
	nodemask_t nodes;
	पूर्णांक err;
	अचिन्हित लघु mode_flags;

	start = untagged_addr(start);
	mode_flags = mode & MPOL_MODE_FLAGS;
	mode &= ~MPOL_MODE_FLAGS;
	अगर (mode >= MPOL_MAX)
		वापस -EINVAL;
	अगर ((mode_flags & MPOL_F_STATIC_NODES) &&
	    (mode_flags & MPOL_F_RELATIVE_NODES))
		वापस -EINVAL;
	err = get_nodes(&nodes, nmask, maxnode);
	अगर (err)
		वापस err;
	वापस करो_mbind(start, len, mode, mode_flags, &nodes, flags);
पूर्ण

SYSCALL_DEFINE6(mbind, अचिन्हित दीर्घ, start, अचिन्हित दीर्घ, len,
		अचिन्हित दीर्घ, mode, स्थिर अचिन्हित दीर्घ __user *, nmask,
		अचिन्हित दीर्घ, maxnode, अचिन्हित पूर्णांक, flags)
अणु
	वापस kernel_mbind(start, len, mode, nmask, maxnode, flags);
पूर्ण

/* Set the process memory policy */
अटल दीर्घ kernel_set_mempolicy(पूर्णांक mode, स्थिर अचिन्हित दीर्घ __user *nmask,
				 अचिन्हित दीर्घ maxnode)
अणु
	पूर्णांक err;
	nodemask_t nodes;
	अचिन्हित लघु flags;

	flags = mode & MPOL_MODE_FLAGS;
	mode &= ~MPOL_MODE_FLAGS;
	अगर ((अचिन्हित पूर्णांक)mode >= MPOL_MAX)
		वापस -EINVAL;
	अगर ((flags & MPOL_F_STATIC_NODES) && (flags & MPOL_F_RELATIVE_NODES))
		वापस -EINVAL;
	err = get_nodes(&nodes, nmask, maxnode);
	अगर (err)
		वापस err;
	वापस करो_set_mempolicy(mode, flags, &nodes);
पूर्ण

SYSCALL_DEFINE3(set_mempolicy, पूर्णांक, mode, स्थिर अचिन्हित दीर्घ __user *, nmask,
		अचिन्हित दीर्घ, maxnode)
अणु
	वापस kernel_set_mempolicy(mode, nmask, maxnode);
पूर्ण

अटल पूर्णांक kernel_migrate_pages(pid_t pid, अचिन्हित दीर्घ maxnode,
				स्थिर अचिन्हित दीर्घ __user *old_nodes,
				स्थिर अचिन्हित दीर्घ __user *new_nodes)
अणु
	काष्ठा mm_काष्ठा *mm = शून्य;
	काष्ठा task_काष्ठा *task;
	nodemask_t task_nodes;
	पूर्णांक err;
	nodemask_t *old;
	nodemask_t *new;
	NODEMASK_SCRATCH(scratch);

	अगर (!scratch)
		वापस -ENOMEM;

	old = &scratch->mask1;
	new = &scratch->mask2;

	err = get_nodes(old, old_nodes, maxnode);
	अगर (err)
		जाओ out;

	err = get_nodes(new, new_nodes, maxnode);
	अगर (err)
		जाओ out;

	/* Find the mm_काष्ठा */
	rcu_पढ़ो_lock();
	task = pid ? find_task_by_vpid(pid) : current;
	अगर (!task) अणु
		rcu_पढ़ो_unlock();
		err = -ESRCH;
		जाओ out;
	पूर्ण
	get_task_काष्ठा(task);

	err = -EINVAL;

	/*
	 * Check अगर this process has the right to modअगरy the specअगरied process.
	 * Use the regular "ptrace_may_access()" checks.
	 */
	अगर (!ptrace_may_access(task, PTRACE_MODE_READ_REALCREDS)) अणु
		rcu_पढ़ो_unlock();
		err = -EPERM;
		जाओ out_put;
	पूर्ण
	rcu_पढ़ो_unlock();

	task_nodes = cpuset_mems_allowed(task);
	/* Is the user allowed to access the target nodes? */
	अगर (!nodes_subset(*new, task_nodes) && !capable(CAP_SYS_NICE)) अणु
		err = -EPERM;
		जाओ out_put;
	पूर्ण

	task_nodes = cpuset_mems_allowed(current);
	nodes_and(*new, *new, task_nodes);
	अगर (nodes_empty(*new))
		जाओ out_put;

	err = security_task_movememory(task);
	अगर (err)
		जाओ out_put;

	mm = get_task_mm(task);
	put_task_काष्ठा(task);

	अगर (!mm) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = करो_migrate_pages(mm, old, new,
		capable(CAP_SYS_NICE) ? MPOL_MF_MOVE_ALL : MPOL_MF_MOVE);

	mmput(mm);
out:
	NODEMASK_SCRATCH_FREE(scratch);

	वापस err;

out_put:
	put_task_काष्ठा(task);
	जाओ out;

पूर्ण

SYSCALL_DEFINE4(migrate_pages, pid_t, pid, अचिन्हित दीर्घ, maxnode,
		स्थिर अचिन्हित दीर्घ __user *, old_nodes,
		स्थिर अचिन्हित दीर्घ __user *, new_nodes)
अणु
	वापस kernel_migrate_pages(pid, maxnode, old_nodes, new_nodes);
पूर्ण


/* Retrieve NUMA policy */
अटल पूर्णांक kernel_get_mempolicy(पूर्णांक __user *policy,
				अचिन्हित दीर्घ __user *nmask,
				अचिन्हित दीर्घ maxnode,
				अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ flags)
अणु
	पूर्णांक err;
	पूर्णांक pval;
	nodemask_t nodes;

	अगर (nmask != शून्य && maxnode < nr_node_ids)
		वापस -EINVAL;

	addr = untagged_addr(addr);

	err = करो_get_mempolicy(&pval, &nodes, addr, flags);

	अगर (err)
		वापस err;

	अगर (policy && put_user(pval, policy))
		वापस -EFAULT;

	अगर (nmask)
		err = copy_nodes_to_user(nmask, maxnode, &nodes);

	वापस err;
पूर्ण

SYSCALL_DEFINE5(get_mempolicy, पूर्णांक __user *, policy,
		अचिन्हित दीर्घ __user *, nmask, अचिन्हित दीर्घ, maxnode,
		अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, flags)
अणु
	वापस kernel_get_mempolicy(policy, nmask, maxnode, addr, flags);
पूर्ण

#अगर_घोषित CONFIG_COMPAT

COMPAT_SYSCALL_DEFINE5(get_mempolicy, पूर्णांक __user *, policy,
		       compat_uदीर्घ_t __user *, nmask,
		       compat_uदीर्घ_t, maxnode,
		       compat_uदीर्घ_t, addr, compat_uदीर्घ_t, flags)
अणु
	दीर्घ err;
	अचिन्हित दीर्घ __user *nm = शून्य;
	अचिन्हित दीर्घ nr_bits, alloc_size;
	DECLARE_BITMAP(bm, MAX_NUMNODES);

	nr_bits = min_t(अचिन्हित दीर्घ, maxnode-1, nr_node_ids);
	alloc_size = ALIGN(nr_bits, BITS_PER_LONG) / 8;

	अगर (nmask)
		nm = compat_alloc_user_space(alloc_size);

	err = kernel_get_mempolicy(policy, nm, nr_bits+1, addr, flags);

	अगर (!err && nmask) अणु
		अचिन्हित दीर्घ copy_size;
		copy_size = min_t(अचिन्हित दीर्घ, माप(bm), alloc_size);
		err = copy_from_user(bm, nm, copy_size);
		/* ensure entire biपंचांगap is zeroed */
		err |= clear_user(nmask, ALIGN(maxnode-1, 8) / 8);
		err |= compat_put_biपंचांगap(nmask, bm, nr_bits);
	पूर्ण

	वापस err;
पूर्ण

COMPAT_SYSCALL_DEFINE3(set_mempolicy, पूर्णांक, mode, compat_uदीर्घ_t __user *, nmask,
		       compat_uदीर्घ_t, maxnode)
अणु
	अचिन्हित दीर्घ __user *nm = शून्य;
	अचिन्हित दीर्घ nr_bits, alloc_size;
	DECLARE_BITMAP(bm, MAX_NUMNODES);

	nr_bits = min_t(अचिन्हित दीर्घ, maxnode-1, MAX_NUMNODES);
	alloc_size = ALIGN(nr_bits, BITS_PER_LONG) / 8;

	अगर (nmask) अणु
		अगर (compat_get_biपंचांगap(bm, nmask, nr_bits))
			वापस -EFAULT;
		nm = compat_alloc_user_space(alloc_size);
		अगर (copy_to_user(nm, bm, alloc_size))
			वापस -EFAULT;
	पूर्ण

	वापस kernel_set_mempolicy(mode, nm, nr_bits+1);
पूर्ण

COMPAT_SYSCALL_DEFINE6(mbind, compat_uदीर्घ_t, start, compat_uदीर्घ_t, len,
		       compat_uदीर्घ_t, mode, compat_uदीर्घ_t __user *, nmask,
		       compat_uदीर्घ_t, maxnode, compat_uदीर्घ_t, flags)
अणु
	अचिन्हित दीर्घ __user *nm = शून्य;
	अचिन्हित दीर्घ nr_bits, alloc_size;
	nodemask_t bm;

	nr_bits = min_t(अचिन्हित दीर्घ, maxnode-1, MAX_NUMNODES);
	alloc_size = ALIGN(nr_bits, BITS_PER_LONG) / 8;

	अगर (nmask) अणु
		अगर (compat_get_biपंचांगap(nodes_addr(bm), nmask, nr_bits))
			वापस -EFAULT;
		nm = compat_alloc_user_space(alloc_size);
		अगर (copy_to_user(nm, nodes_addr(bm), alloc_size))
			वापस -EFAULT;
	पूर्ण

	वापस kernel_mbind(start, len, mode, nm, nr_bits+1, flags);
पूर्ण

COMPAT_SYSCALL_DEFINE4(migrate_pages, compat_pid_t, pid,
		       compat_uदीर्घ_t, maxnode,
		       स्थिर compat_uदीर्घ_t __user *, old_nodes,
		       स्थिर compat_uदीर्घ_t __user *, new_nodes)
अणु
	अचिन्हित दीर्घ __user *old = शून्य;
	अचिन्हित दीर्घ __user *new = शून्य;
	nodemask_t पंचांगp_mask;
	अचिन्हित दीर्घ nr_bits;
	अचिन्हित दीर्घ size;

	nr_bits = min_t(अचिन्हित दीर्घ, maxnode - 1, MAX_NUMNODES);
	size = ALIGN(nr_bits, BITS_PER_LONG) / 8;
	अगर (old_nodes) अणु
		अगर (compat_get_biपंचांगap(nodes_addr(पंचांगp_mask), old_nodes, nr_bits))
			वापस -EFAULT;
		old = compat_alloc_user_space(new_nodes ? size * 2 : size);
		अगर (new_nodes)
			new = old + size / माप(अचिन्हित दीर्घ);
		अगर (copy_to_user(old, nodes_addr(पंचांगp_mask), size))
			वापस -EFAULT;
	पूर्ण
	अगर (new_nodes) अणु
		अगर (compat_get_biपंचांगap(nodes_addr(पंचांगp_mask), new_nodes, nr_bits))
			वापस -EFAULT;
		अगर (new == शून्य)
			new = compat_alloc_user_space(size);
		अगर (copy_to_user(new, nodes_addr(पंचांगp_mask), size))
			वापस -EFAULT;
	पूर्ण
	वापस kernel_migrate_pages(pid, nr_bits + 1, old, new);
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPAT */

bool vma_migratable(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->vm_flags & (VM_IO | VM_PFNMAP))
		वापस false;

	/*
	 * DAX device mappings require predictable access latency, so aव्योम
	 * incurring periodic faults.
	 */
	अगर (vma_is_dax(vma))
		वापस false;

	अगर (is_vm_hugetlb_page(vma) &&
		!hugepage_migration_supported(hstate_vma(vma)))
		वापस false;

	/*
	 * Migration allocates pages in the highest zone. If we cannot
	 * करो so then migration (at least from node to node) is not
	 * possible.
	 */
	अगर (vma->vm_file &&
		gfp_zone(mapping_gfp_mask(vma->vm_file->f_mapping))
			< policy_zone)
		वापस false;
	वापस true;
पूर्ण

काष्ठा mempolicy *__get_vma_policy(काष्ठा vm_area_काष्ठा *vma,
						अचिन्हित दीर्घ addr)
अणु
	काष्ठा mempolicy *pol = शून्य;

	अगर (vma) अणु
		अगर (vma->vm_ops && vma->vm_ops->get_policy) अणु
			pol = vma->vm_ops->get_policy(vma, addr);
		पूर्ण अन्यथा अगर (vma->vm_policy) अणु
			pol = vma->vm_policy;

			/*
			 * shmem_alloc_page() passes MPOL_F_SHARED policy with
			 * a pseuकरो vma whose vma->vm_ops=शून्य. Take a reference
			 * count on these policies which will be dropped by
			 * mpol_cond_put() later
			 */
			अगर (mpol_needs_cond_ref(pol))
				mpol_get(pol);
		पूर्ण
	पूर्ण

	वापस pol;
पूर्ण

/*
 * get_vma_policy(@vma, @addr)
 * @vma: भव memory area whose policy is sought
 * @addr: address in @vma क्रम shared policy lookup
 *
 * Returns effective policy क्रम a VMA at specअगरied address.
 * Falls back to current->mempolicy or प्रणाली शेष policy, as necessary.
 * Shared policies [those marked as MPOL_F_SHARED] require an extra reference
 * count--added by the get_policy() vm_op, as appropriate--to protect against
 * मुक्तing by another task.  It is the caller's responsibility to मुक्त the
 * extra reference क्रम shared policies.
 */
अटल काष्ठा mempolicy *get_vma_policy(काष्ठा vm_area_काष्ठा *vma,
						अचिन्हित दीर्घ addr)
अणु
	काष्ठा mempolicy *pol = __get_vma_policy(vma, addr);

	अगर (!pol)
		pol = get_task_policy(current);

	वापस pol;
पूर्ण

bool vma_policy_mof(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mempolicy *pol;

	अगर (vma->vm_ops && vma->vm_ops->get_policy) अणु
		bool ret = false;

		pol = vma->vm_ops->get_policy(vma, vma->vm_start);
		अगर (pol && (pol->flags & MPOL_F_MOF))
			ret = true;
		mpol_cond_put(pol);

		वापस ret;
	पूर्ण

	pol = vma->vm_policy;
	अगर (!pol)
		pol = get_task_policy(current);

	वापस pol->flags & MPOL_F_MOF;
पूर्ण

अटल पूर्णांक apply_policy_zone(काष्ठा mempolicy *policy, क्रमागत zone_type zone)
अणु
	क्रमागत zone_type dynamic_policy_zone = policy_zone;

	BUG_ON(dynamic_policy_zone == ZONE_MOVABLE);

	/*
	 * अगर policy->v.nodes has movable memory only,
	 * we apply policy when gfp_zone(gfp) = ZONE_MOVABLE only.
	 *
	 * policy->v.nodes is पूर्णांकersect with node_states[N_MEMORY].
	 * so अगर the following test fails, it implies
	 * policy->v.nodes has movable memory only.
	 */
	अगर (!nodes_पूर्णांकersects(policy->v.nodes, node_states[N_HIGH_MEMORY]))
		dynamic_policy_zone = ZONE_MOVABLE;

	वापस zone >= dynamic_policy_zone;
पूर्ण

/*
 * Return a nodemask representing a mempolicy क्रम filtering nodes क्रम
 * page allocation
 */
nodemask_t *policy_nodemask(gfp_t gfp, काष्ठा mempolicy *policy)
अणु
	/* Lower zones करोn't get a nodemask applied क्रम MPOL_BIND */
	अगर (unlikely(policy->mode == MPOL_BIND) &&
			apply_policy_zone(policy, gfp_zone(gfp)) &&
			cpuset_nodemask_valid_mems_allowed(&policy->v.nodes))
		वापस &policy->v.nodes;

	वापस शून्य;
पूर्ण

/* Return the node id preferred by the given mempolicy, or the given id */
अटल पूर्णांक policy_node(gfp_t gfp, काष्ठा mempolicy *policy, पूर्णांक nd)
अणु
	अगर (policy->mode == MPOL_PREFERRED && !(policy->flags & MPOL_F_LOCAL))
		nd = policy->v.preferred_node;
	अन्यथा अणु
		/*
		 * __GFP_THISNODE shouldn't even be used with the bind policy
		 * because we might easily अवरोध the expectation to stay on the
		 * requested node and not अवरोध the policy.
		 */
		WARN_ON_ONCE(policy->mode == MPOL_BIND && (gfp & __GFP_THISNODE));
	पूर्ण

	वापस nd;
पूर्ण

/* Do dynamic पूर्णांकerleaving क्रम a process */
अटल अचिन्हित पूर्णांकerleave_nodes(काष्ठा mempolicy *policy)
अणु
	अचिन्हित next;
	काष्ठा task_काष्ठा *me = current;

	next = next_node_in(me->il_prev, policy->v.nodes);
	अगर (next < MAX_NUMNODES)
		me->il_prev = next;
	वापस next;
पूर्ण

/*
 * Depending on the memory policy provide a node from which to allocate the
 * next slab entry.
 */
अचिन्हित पूर्णांक mempolicy_slab_node(व्योम)
अणु
	काष्ठा mempolicy *policy;
	पूर्णांक node = numa_mem_id();

	अगर (in_पूर्णांकerrupt())
		वापस node;

	policy = current->mempolicy;
	अगर (!policy || policy->flags & MPOL_F_LOCAL)
		वापस node;

	चयन (policy->mode) अणु
	हाल MPOL_PREFERRED:
		/*
		 * handled MPOL_F_LOCAL above
		 */
		वापस policy->v.preferred_node;

	हाल MPOL_INTERLEAVE:
		वापस पूर्णांकerleave_nodes(policy);

	हाल MPOL_BIND: अणु
		काष्ठा zoneref *z;

		/*
		 * Follow bind policy behavior and start allocation at the
		 * first node.
		 */
		काष्ठा zonelist *zonelist;
		क्रमागत zone_type highest_zoneidx = gfp_zone(GFP_KERNEL);
		zonelist = &NODE_DATA(node)->node_zonelists[ZONELIST_FALLBACK];
		z = first_zones_zonelist(zonelist, highest_zoneidx,
							&policy->v.nodes);
		वापस z->zone ? zone_to_nid(z->zone) : node;
	पूर्ण

	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * Do अटल पूर्णांकerleaving क्रम a VMA with known offset @n.  Returns the n'th
 * node in pol->v.nodes (starting from n=0), wrapping around अगर n exceeds the
 * number of present nodes.
 */
अटल अचिन्हित offset_il_node(काष्ठा mempolicy *pol, अचिन्हित दीर्घ n)
अणु
	अचिन्हित nnodes = nodes_weight(pol->v.nodes);
	अचिन्हित target;
	पूर्णांक i;
	पूर्णांक nid;

	अगर (!nnodes)
		वापस numa_node_id();
	target = (अचिन्हित पूर्णांक)n % nnodes;
	nid = first_node(pol->v.nodes);
	क्रम (i = 0; i < target; i++)
		nid = next_node(nid, pol->v.nodes);
	वापस nid;
पूर्ण

/* Determine a node number क्रम पूर्णांकerleave */
अटल अंतरभूत अचिन्हित पूर्णांकerleave_nid(काष्ठा mempolicy *pol,
		 काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr, पूर्णांक shअगरt)
अणु
	अगर (vma) अणु
		अचिन्हित दीर्घ off;

		/*
		 * क्रम small pages, there is no dअगरference between
		 * shअगरt and PAGE_SHIFT, so the bit-shअगरt is safe.
		 * क्रम huge pages, since vm_pgoff is in units of small
		 * pages, we need to shअगरt off the always 0 bits to get
		 * a useful offset.
		 */
		BUG_ON(shअगरt < PAGE_SHIFT);
		off = vma->vm_pgoff >> (shअगरt - PAGE_SHIFT);
		off += (addr - vma->vm_start) >> shअगरt;
		वापस offset_il_node(pol, off);
	पूर्ण अन्यथा
		वापस पूर्णांकerleave_nodes(pol);
पूर्ण

#अगर_घोषित CONFIG_HUGETLBFS
/*
 * huge_node(@vma, @addr, @gfp_flags, @mpol)
 * @vma: भव memory area whose policy is sought
 * @addr: address in @vma क्रम shared policy lookup and पूर्णांकerleave policy
 * @gfp_flags: क्रम requested zone
 * @mpol: poपूर्णांकer to mempolicy poपूर्णांकer क्रम reference counted mempolicy
 * @nodemask: poपूर्णांकer to nodemask poपूर्णांकer क्रम MPOL_BIND nodemask
 *
 * Returns a nid suitable क्रम a huge page allocation and a poपूर्णांकer
 * to the काष्ठा mempolicy क्रम conditional unref after allocation.
 * If the effective policy is 'BIND, returns a pointer to the mempolicy's
 * @nodemask क्रम filtering the zonelist.
 *
 * Must be रक्षित by पढ़ो_mems_allowed_begin()
 */
पूर्णांक huge_node(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr, gfp_t gfp_flags,
				काष्ठा mempolicy **mpol, nodemask_t **nodemask)
अणु
	पूर्णांक nid;

	*mpol = get_vma_policy(vma, addr);
	*nodemask = शून्य;	/* assume !MPOL_BIND */

	अगर (unlikely((*mpol)->mode == MPOL_INTERLEAVE)) अणु
		nid = पूर्णांकerleave_nid(*mpol, vma, addr,
					huge_page_shअगरt(hstate_vma(vma)));
	पूर्ण अन्यथा अणु
		nid = policy_node(gfp_flags, *mpol, numa_node_id());
		अगर ((*mpol)->mode == MPOL_BIND)
			*nodemask = &(*mpol)->v.nodes;
	पूर्ण
	वापस nid;
पूर्ण

/*
 * init_nodemask_of_mempolicy
 *
 * If the current task's mempolicy is "default" [NULL], return 'false'
 * to indicate शेष policy.  Otherwise, extract the policy nodemask
 * क्रम 'bind' or 'interleave' policy पूर्णांकo the argument nodemask, or
 * initialize the argument nodemask to contain the single node क्रम
 * 'preferred' or 'local' policy and return 'true' to indicate presence
 * of non-शेष mempolicy.
 *
 * We करोn't bother with reference counting the mempolicy [mpol_get/put]
 * because the current task is examining it's own mempolicy and a task's
 * mempolicy is only ever changed by the task itself.
 *
 * N.B., it is the caller's responsibility to मुक्त a वापसed nodemask.
 */
bool init_nodemask_of_mempolicy(nodemask_t *mask)
अणु
	काष्ठा mempolicy *mempolicy;
	पूर्णांक nid;

	अगर (!(mask && current->mempolicy))
		वापस false;

	task_lock(current);
	mempolicy = current->mempolicy;
	चयन (mempolicy->mode) अणु
	हाल MPOL_PREFERRED:
		अगर (mempolicy->flags & MPOL_F_LOCAL)
			nid = numa_node_id();
		अन्यथा
			nid = mempolicy->v.preferred_node;
		init_nodemask_of_node(mask, nid);
		अवरोध;

	हाल MPOL_BIND:
	हाल MPOL_INTERLEAVE:
		*mask =  mempolicy->v.nodes;
		अवरोध;

	शेष:
		BUG();
	पूर्ण
	task_unlock(current);

	वापस true;
पूर्ण
#पूर्ण_अगर

/*
 * mempolicy_nodemask_पूर्णांकersects
 *
 * If tsk's mempolicy is "default" [NULL], return 'true' to indicate शेष
 * policy.  Otherwise, check क्रम पूर्णांकersection between mask and the policy
 * nodemask क्रम 'bind' or 'interleave' policy.  For 'preferred' or 'local'
 * policy, always वापस true since it may allocate अन्यथाwhere on fallback.
 *
 * Takes task_lock(tsk) to prevent मुक्तing of its mempolicy.
 */
bool mempolicy_nodemask_पूर्णांकersects(काष्ठा task_काष्ठा *tsk,
					स्थिर nodemask_t *mask)
अणु
	काष्ठा mempolicy *mempolicy;
	bool ret = true;

	अगर (!mask)
		वापस ret;
	task_lock(tsk);
	mempolicy = tsk->mempolicy;
	अगर (!mempolicy)
		जाओ out;

	चयन (mempolicy->mode) अणु
	हाल MPOL_PREFERRED:
		/*
		 * MPOL_PREFERRED and MPOL_F_LOCAL are only preferred nodes to
		 * allocate from, they may fallback to other nodes when oom.
		 * Thus, it's possible क्रम tsk to have allocated memory from
		 * nodes in mask.
		 */
		अवरोध;
	हाल MPOL_BIND:
	हाल MPOL_INTERLEAVE:
		ret = nodes_पूर्णांकersects(mempolicy->v.nodes, *mask);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
out:
	task_unlock(tsk);
	वापस ret;
पूर्ण

/* Allocate a page in पूर्णांकerleaved policy.
   Own path because it needs to करो special accounting. */
अटल काष्ठा page *alloc_page_पूर्णांकerleave(gfp_t gfp, अचिन्हित order,
					अचिन्हित nid)
अणु
	काष्ठा page *page;

	page = __alloc_pages(gfp, order, nid, शून्य);
	/* skip NUMA_INTERLEAVE_HIT counter update अगर numa stats is disabled */
	अगर (!अटल_branch_likely(&vm_numa_stat_key))
		वापस page;
	अगर (page && page_to_nid(page) == nid) अणु
		preempt_disable();
		__inc_numa_state(page_zone(page), NUMA_INTERLEAVE_HIT);
		preempt_enable();
	पूर्ण
	वापस page;
पूर्ण

/**
 * alloc_pages_vma - Allocate a page क्रम a VMA.
 * @gfp: GFP flags.
 * @order: Order of the GFP allocation.
 * @vma: Poपूर्णांकer to VMA or शून्य अगर not available.
 * @addr: Virtual address of the allocation.  Must be inside @vma.
 * @node: Which node to prefer क्रम allocation (modulo policy).
 * @hugepage: For hugepages try only the preferred node अगर possible.
 *
 * Allocate a page क्रम a specअगरic address in @vma, using the appropriate
 * NUMA policy.  When @vma is not शून्य the caller must hold the mmap_lock
 * of the mm_काष्ठा of the VMA to prevent it from going away.  Should be
 * used क्रम all allocations क्रम pages that will be mapped पूर्णांकo user space.
 *
 * Return: The page on success or शून्य अगर allocation fails.
 */
काष्ठा page *alloc_pages_vma(gfp_t gfp, पूर्णांक order, काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, पूर्णांक node, bool hugepage)
अणु
	काष्ठा mempolicy *pol;
	काष्ठा page *page;
	पूर्णांक preferred_nid;
	nodemask_t *nmask;

	pol = get_vma_policy(vma, addr);

	अगर (pol->mode == MPOL_INTERLEAVE) अणु
		अचिन्हित nid;

		nid = पूर्णांकerleave_nid(pol, vma, addr, PAGE_SHIFT + order);
		mpol_cond_put(pol);
		page = alloc_page_पूर्णांकerleave(gfp, order, nid);
		जाओ out;
	पूर्ण

	अगर (unlikely(IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE) && hugepage)) अणु
		पूर्णांक hpage_node = node;

		/*
		 * For hugepage allocation and non-पूर्णांकerleave policy which
		 * allows the current node (or other explicitly preferred
		 * node) we only try to allocate from the current/preferred
		 * node and करोn't fall back to other nodes, as the cost of
		 * remote accesses would likely offset THP benefits.
		 *
		 * If the policy is पूर्णांकerleave, or करोes not allow the current
		 * node in its nodemask, we allocate the standard way.
		 */
		अगर (pol->mode == MPOL_PREFERRED && !(pol->flags & MPOL_F_LOCAL))
			hpage_node = pol->v.preferred_node;

		nmask = policy_nodemask(gfp, pol);
		अगर (!nmask || node_isset(hpage_node, *nmask)) अणु
			mpol_cond_put(pol);
			/*
			 * First, try to allocate THP only on local node, but
			 * करोn't reclaim unnecessarily, just compact.
			 */
			page = __alloc_pages_node(hpage_node,
				gfp | __GFP_THISNODE | __GFP_NORETRY, order);

			/*
			 * If hugepage allocations are configured to always
			 * synchronous compact or the vma has been madvised
			 * to prefer hugepage backing, retry allowing remote
			 * memory with both reclaim and compact as well.
			 */
			अगर (!page && (gfp & __GFP_सूचीECT_RECLAIM))
				page = __alloc_pages_node(hpage_node,
								gfp, order);

			जाओ out;
		पूर्ण
	पूर्ण

	nmask = policy_nodemask(gfp, pol);
	preferred_nid = policy_node(gfp, pol, node);
	page = __alloc_pages(gfp, order, preferred_nid, nmask);
	mpol_cond_put(pol);
out:
	वापस page;
पूर्ण
EXPORT_SYMBOL(alloc_pages_vma);

/**
 * alloc_pages - Allocate pages.
 * @gfp: GFP flags.
 * @order: Power of two of number of pages to allocate.
 *
 * Allocate 1 << @order contiguous pages.  The physical address of the
 * first page is naturally aligned (eg an order-3 allocation will be aligned
 * to a multiple of 8 * PAGE_SIZE bytes).  The NUMA policy of the current
 * process is honoured when in process context.
 *
 * Context: Can be called from any context, providing the appropriate GFP
 * flags are used.
 * Return: The page on success or शून्य अगर allocation fails.
 */
काष्ठा page *alloc_pages(gfp_t gfp, अचिन्हित order)
अणु
	काष्ठा mempolicy *pol = &शेष_policy;
	काष्ठा page *page;

	अगर (!in_पूर्णांकerrupt() && !(gfp & __GFP_THISNODE))
		pol = get_task_policy(current);

	/*
	 * No reference counting needed क्रम current->mempolicy
	 * nor प्रणाली शेष_policy
	 */
	अगर (pol->mode == MPOL_INTERLEAVE)
		page = alloc_page_पूर्णांकerleave(gfp, order, पूर्णांकerleave_nodes(pol));
	अन्यथा
		page = __alloc_pages(gfp, order,
				policy_node(gfp, pol, numa_node_id()),
				policy_nodemask(gfp, pol));

	वापस page;
पूर्ण
EXPORT_SYMBOL(alloc_pages);

पूर्णांक vma_dup_policy(काष्ठा vm_area_काष्ठा *src, काष्ठा vm_area_काष्ठा *dst)
अणु
	काष्ठा mempolicy *pol = mpol_dup(vma_policy(src));

	अगर (IS_ERR(pol))
		वापस PTR_ERR(pol);
	dst->vm_policy = pol;
	वापस 0;
पूर्ण

/*
 * If mpol_dup() sees current->cpuset == cpuset_being_rebound, then it
 * rebinds the mempolicy its copying by calling mpol_rebind_policy()
 * with the mems_allowed वापसed by cpuset_mems_allowed().  This
 * keeps mempolicies cpuset relative after its cpuset moves.  See
 * further kernel/cpuset.c update_nodemask().
 *
 * current's mempolicy may be rebinded by the other task(the task that changes
 * cpuset's mems), so we needn't करो rebind work क्रम current task.
 */

/* Slow path of a mempolicy duplicate */
काष्ठा mempolicy *__mpol_dup(काष्ठा mempolicy *old)
अणु
	काष्ठा mempolicy *new = kmem_cache_alloc(policy_cache, GFP_KERNEL);

	अगर (!new)
		वापस ERR_PTR(-ENOMEM);

	/* task's mempolicy is रक्षित by alloc_lock */
	अगर (old == current->mempolicy) अणु
		task_lock(current);
		*new = *old;
		task_unlock(current);
	पूर्ण अन्यथा
		*new = *old;

	अगर (current_cpuset_is_being_rebound()) अणु
		nodemask_t mems = cpuset_mems_allowed(current);
		mpol_rebind_policy(new, &mems);
	पूर्ण
	atomic_set(&new->refcnt, 1);
	वापस new;
पूर्ण

/* Slow path of a mempolicy comparison */
bool __mpol_equal(काष्ठा mempolicy *a, काष्ठा mempolicy *b)
अणु
	अगर (!a || !b)
		वापस false;
	अगर (a->mode != b->mode)
		वापस false;
	अगर (a->flags != b->flags)
		वापस false;
	अगर (mpol_store_user_nodemask(a))
		अगर (!nodes_equal(a->w.user_nodemask, b->w.user_nodemask))
			वापस false;

	चयन (a->mode) अणु
	हाल MPOL_BIND:
	हाल MPOL_INTERLEAVE:
		वापस !!nodes_equal(a->v.nodes, b->v.nodes);
	हाल MPOL_PREFERRED:
		/* a's ->flags is the same as b's */
		अगर (a->flags & MPOL_F_LOCAL)
			वापस true;
		वापस a->v.preferred_node == b->v.preferred_node;
	शेष:
		BUG();
		वापस false;
	पूर्ण
पूर्ण

/*
 * Shared memory backing store policy support.
 *
 * Remember policies even when nobody has shared memory mapped.
 * The policies are kept in Red-Black tree linked from the inode.
 * They are रक्षित by the sp->lock rwlock, which should be held
 * क्रम any accesses to the tree.
 */

/*
 * lookup first element पूर्णांकersecting start-end.  Caller holds sp->lock क्रम
 * पढ़ोing or क्रम writing
 */
अटल काष्ठा sp_node *
sp_lookup(काष्ठा shared_policy *sp, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा rb_node *n = sp->root.rb_node;

	जबतक (n) अणु
		काष्ठा sp_node *p = rb_entry(n, काष्ठा sp_node, nd);

		अगर (start >= p->end)
			n = n->rb_right;
		अन्यथा अगर (end <= p->start)
			n = n->rb_left;
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (!n)
		वापस शून्य;
	क्रम (;;) अणु
		काष्ठा sp_node *w = शून्य;
		काष्ठा rb_node *prev = rb_prev(n);
		अगर (!prev)
			अवरोध;
		w = rb_entry(prev, काष्ठा sp_node, nd);
		अगर (w->end <= start)
			अवरोध;
		n = prev;
	पूर्ण
	वापस rb_entry(n, काष्ठा sp_node, nd);
पूर्ण

/*
 * Insert a new shared policy पूर्णांकo the list.  Caller holds sp->lock क्रम
 * writing.
 */
अटल व्योम sp_insert(काष्ठा shared_policy *sp, काष्ठा sp_node *new)
अणु
	काष्ठा rb_node **p = &sp->root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा sp_node *nd;

	जबतक (*p) अणु
		parent = *p;
		nd = rb_entry(parent, काष्ठा sp_node, nd);
		अगर (new->start < nd->start)
			p = &(*p)->rb_left;
		अन्यथा अगर (new->end > nd->end)
			p = &(*p)->rb_right;
		अन्यथा
			BUG();
	पूर्ण
	rb_link_node(&new->nd, parent, p);
	rb_insert_color(&new->nd, &sp->root);
	pr_debug("inserting %lx-%lx: %d\n", new->start, new->end,
		 new->policy ? new->policy->mode : 0);
पूर्ण

/* Find shared policy पूर्णांकersecting idx */
काष्ठा mempolicy *
mpol_shared_policy_lookup(काष्ठा shared_policy *sp, अचिन्हित दीर्घ idx)
अणु
	काष्ठा mempolicy *pol = शून्य;
	काष्ठा sp_node *sn;

	अगर (!sp->root.rb_node)
		वापस शून्य;
	पढ़ो_lock(&sp->lock);
	sn = sp_lookup(sp, idx, idx+1);
	अगर (sn) अणु
		mpol_get(sn->policy);
		pol = sn->policy;
	पूर्ण
	पढ़ो_unlock(&sp->lock);
	वापस pol;
पूर्ण

अटल व्योम sp_मुक्त(काष्ठा sp_node *n)
अणु
	mpol_put(n->policy);
	kmem_cache_मुक्त(sn_cache, n);
पूर्ण

/**
 * mpol_misplaced - check whether current page node is valid in policy
 *
 * @page: page to be checked
 * @vma: vm area where page mapped
 * @addr: भव address where page mapped
 *
 * Lookup current policy node id क्रम vma,addr and "compare to" page's
 * node id.  Policy determination "mimics" alloc_page_vma().
 * Called from fault path where we know the vma and faulting address.
 *
 * Return: -1 अगर the page is in a node that is valid क्रम this policy, or a
 * suitable node ID to allocate a replacement page from.
 */
पूर्णांक mpol_misplaced(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	काष्ठा mempolicy *pol;
	काष्ठा zoneref *z;
	पूर्णांक curnid = page_to_nid(page);
	अचिन्हित दीर्घ pgoff;
	पूर्णांक thiscpu = raw_smp_processor_id();
	पूर्णांक thisnid = cpu_to_node(thiscpu);
	पूर्णांक polnid = NUMA_NO_NODE;
	पूर्णांक ret = -1;

	pol = get_vma_policy(vma, addr);
	अगर (!(pol->flags & MPOL_F_MOF))
		जाओ out;

	चयन (pol->mode) अणु
	हाल MPOL_INTERLEAVE:
		pgoff = vma->vm_pgoff;
		pgoff += (addr - vma->vm_start) >> PAGE_SHIFT;
		polnid = offset_il_node(pol, pgoff);
		अवरोध;

	हाल MPOL_PREFERRED:
		अगर (pol->flags & MPOL_F_LOCAL)
			polnid = numa_node_id();
		अन्यथा
			polnid = pol->v.preferred_node;
		अवरोध;

	हाल MPOL_BIND:
		/* Optimize placement among multiple nodes via NUMA balancing */
		अगर (pol->flags & MPOL_F_MORON) अणु
			अगर (node_isset(thisnid, pol->v.nodes))
				अवरोध;
			जाओ out;
		पूर्ण

		/*
		 * allows binding to multiple nodes.
		 * use current page अगर in policy nodemask,
		 * अन्यथा select nearest allowed node, अगर any.
		 * If no allowed nodes, use current [!misplaced].
		 */
		अगर (node_isset(curnid, pol->v.nodes))
			जाओ out;
		z = first_zones_zonelist(
				node_zonelist(numa_node_id(), GFP_HIGHUSER),
				gfp_zone(GFP_HIGHUSER),
				&pol->v.nodes);
		polnid = zone_to_nid(z->zone);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	/* Migrate the page towards the node whose CPU is referencing it */
	अगर (pol->flags & MPOL_F_MORON) अणु
		polnid = thisnid;

		अगर (!should_numa_migrate_memory(current, page, curnid, thiscpu))
			जाओ out;
	पूर्ण

	अगर (curnid != polnid)
		ret = polnid;
out:
	mpol_cond_put(pol);

	वापस ret;
पूर्ण

/*
 * Drop the (possibly final) reference to task->mempolicy.  It needs to be
 * dropped after task->mempolicy is set to शून्य so that any allocation करोne as
 * part of its kmem_cache_मुक्त(), such as by KASAN, करोesn't reference a मुक्तd
 * policy.
 */
व्योम mpol_put_task_policy(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा mempolicy *pol;

	task_lock(task);
	pol = task->mempolicy;
	task->mempolicy = शून्य;
	task_unlock(task);
	mpol_put(pol);
पूर्ण

अटल व्योम sp_delete(काष्ठा shared_policy *sp, काष्ठा sp_node *n)
अणु
	pr_debug("deleting %lx-l%lx\n", n->start, n->end);
	rb_erase(&n->nd, &sp->root);
	sp_मुक्त(n);
पूर्ण

अटल व्योम sp_node_init(काष्ठा sp_node *node, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ end, काष्ठा mempolicy *pol)
अणु
	node->start = start;
	node->end = end;
	node->policy = pol;
पूर्ण

अटल काष्ठा sp_node *sp_alloc(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				काष्ठा mempolicy *pol)
अणु
	काष्ठा sp_node *n;
	काष्ठा mempolicy *newpol;

	n = kmem_cache_alloc(sn_cache, GFP_KERNEL);
	अगर (!n)
		वापस शून्य;

	newpol = mpol_dup(pol);
	अगर (IS_ERR(newpol)) अणु
		kmem_cache_मुक्त(sn_cache, n);
		वापस शून्य;
	पूर्ण
	newpol->flags |= MPOL_F_SHARED;
	sp_node_init(n, start, end, newpol);

	वापस n;
पूर्ण

/* Replace a policy range. */
अटल पूर्णांक shared_policy_replace(काष्ठा shared_policy *sp, अचिन्हित दीर्घ start,
				 अचिन्हित दीर्घ end, काष्ठा sp_node *new)
अणु
	काष्ठा sp_node *n;
	काष्ठा sp_node *n_new = शून्य;
	काष्ठा mempolicy *mpol_new = शून्य;
	पूर्णांक ret = 0;

restart:
	ग_लिखो_lock(&sp->lock);
	n = sp_lookup(sp, start, end);
	/* Take care of old policies in the same range. */
	जबतक (n && n->start < end) अणु
		काष्ठा rb_node *next = rb_next(&n->nd);
		अगर (n->start >= start) अणु
			अगर (n->end <= end)
				sp_delete(sp, n);
			अन्यथा
				n->start = end;
		पूर्ण अन्यथा अणु
			/* Old policy spanning whole new range. */
			अगर (n->end > end) अणु
				अगर (!n_new)
					जाओ alloc_new;

				*mpol_new = *n->policy;
				atomic_set(&mpol_new->refcnt, 1);
				sp_node_init(n_new, end, n->end, mpol_new);
				n->end = start;
				sp_insert(sp, n_new);
				n_new = शून्य;
				mpol_new = शून्य;
				अवरोध;
			पूर्ण अन्यथा
				n->end = start;
		पूर्ण
		अगर (!next)
			अवरोध;
		n = rb_entry(next, काष्ठा sp_node, nd);
	पूर्ण
	अगर (new)
		sp_insert(sp, new);
	ग_लिखो_unlock(&sp->lock);
	ret = 0;

err_out:
	अगर (mpol_new)
		mpol_put(mpol_new);
	अगर (n_new)
		kmem_cache_मुक्त(sn_cache, n_new);

	वापस ret;

alloc_new:
	ग_लिखो_unlock(&sp->lock);
	ret = -ENOMEM;
	n_new = kmem_cache_alloc(sn_cache, GFP_KERNEL);
	अगर (!n_new)
		जाओ err_out;
	mpol_new = kmem_cache_alloc(policy_cache, GFP_KERNEL);
	अगर (!mpol_new)
		जाओ err_out;
	जाओ restart;
पूर्ण

/**
 * mpol_shared_policy_init - initialize shared policy क्रम inode
 * @sp: poपूर्णांकer to inode shared policy
 * @mpol:  काष्ठा mempolicy to install
 *
 * Install non-शून्य @mpol in inode's shared policy rb-tree.
 * On entry, the current task has a reference on a non-शून्य @mpol.
 * This must be released on निकास.
 * This is called at get_inode() calls and we can use GFP_KERNEL.
 */
व्योम mpol_shared_policy_init(काष्ठा shared_policy *sp, काष्ठा mempolicy *mpol)
अणु
	पूर्णांक ret;

	sp->root = RB_ROOT;		/* empty tree == शेष mempolicy */
	rwlock_init(&sp->lock);

	अगर (mpol) अणु
		काष्ठा vm_area_काष्ठा pvma;
		काष्ठा mempolicy *new;
		NODEMASK_SCRATCH(scratch);

		अगर (!scratch)
			जाओ put_mpol;
		/* contextualize the पंचांगpfs mount poपूर्णांक mempolicy */
		new = mpol_new(mpol->mode, mpol->flags, &mpol->w.user_nodemask);
		अगर (IS_ERR(new))
			जाओ मुक्त_scratch; /* no valid nodemask पूर्णांकersection */

		task_lock(current);
		ret = mpol_set_nodemask(new, &mpol->w.user_nodemask, scratch);
		task_unlock(current);
		अगर (ret)
			जाओ put_new;

		/* Create pseuकरो-vma that contains just the policy */
		vma_init(&pvma, शून्य);
		pvma.vm_end = TASK_SIZE;	/* policy covers entire file */
		mpol_set_shared_policy(sp, &pvma, new); /* adds ref */

put_new:
		mpol_put(new);			/* drop initial ref */
मुक्त_scratch:
		NODEMASK_SCRATCH_FREE(scratch);
put_mpol:
		mpol_put(mpol);	/* drop our incoming ref on sb mpol */
	पूर्ण
पूर्ण

पूर्णांक mpol_set_shared_policy(काष्ठा shared_policy *info,
			काष्ठा vm_area_काष्ठा *vma, काष्ठा mempolicy *npol)
अणु
	पूर्णांक err;
	काष्ठा sp_node *new = शून्य;
	अचिन्हित दीर्घ sz = vma_pages(vma);

	pr_debug("set_shared_policy %lx sz %lu %d %d %lx\n",
		 vma->vm_pgoff,
		 sz, npol ? npol->mode : -1,
		 npol ? npol->flags : -1,
		 npol ? nodes_addr(npol->v.nodes)[0] : NUMA_NO_NODE);

	अगर (npol) अणु
		new = sp_alloc(vma->vm_pgoff, vma->vm_pgoff + sz, npol);
		अगर (!new)
			वापस -ENOMEM;
	पूर्ण
	err = shared_policy_replace(info, vma->vm_pgoff, vma->vm_pgoff+sz, new);
	अगर (err && new)
		sp_मुक्त(new);
	वापस err;
पूर्ण

/* Free a backing policy store on inode delete. */
व्योम mpol_मुक्त_shared_policy(काष्ठा shared_policy *p)
अणु
	काष्ठा sp_node *n;
	काष्ठा rb_node *next;

	अगर (!p->root.rb_node)
		वापस;
	ग_लिखो_lock(&p->lock);
	next = rb_first(&p->root);
	जबतक (next) अणु
		n = rb_entry(next, काष्ठा sp_node, nd);
		next = rb_next(&n->nd);
		sp_delete(p, n);
	पूर्ण
	ग_लिखो_unlock(&p->lock);
पूर्ण

#अगर_घोषित CONFIG_NUMA_BALANCING
अटल पूर्णांक __initdata numabalancing_override;

अटल व्योम __init check_numabalancing_enable(व्योम)
अणु
	bool numabalancing_शेष = false;

	अगर (IS_ENABLED(CONFIG_NUMA_BALANCING_DEFAULT_ENABLED))
		numabalancing_शेष = true;

	/* Parsed by setup_numabalancing. override == 1 enables, -1 disables */
	अगर (numabalancing_override)
		set_numabalancing_state(numabalancing_override == 1);

	अगर (num_online_nodes() > 1 && !numabalancing_override) अणु
		pr_info("%s automatic NUMA balancing. Configure with numa_balancing= or the kernel.numa_balancing sysctl\n",
			numabalancing_शेष ? "Enabling" : "Disabling");
		set_numabalancing_state(numabalancing_शेष);
	पूर्ण
पूर्ण

अटल पूर्णांक __init setup_numabalancing(अक्षर *str)
अणु
	पूर्णांक ret = 0;
	अगर (!str)
		जाओ out;

	अगर (!म_भेद(str, "enable")) अणु
		numabalancing_override = 1;
		ret = 1;
	पूर्ण अन्यथा अगर (!म_भेद(str, "disable")) अणु
		numabalancing_override = -1;
		ret = 1;
	पूर्ण
out:
	अगर (!ret)
		pr_warn("Unable to parse numa_balancing=\n");

	वापस ret;
पूर्ण
__setup("numa_balancing=", setup_numabalancing);
#अन्यथा
अटल अंतरभूत व्योम __init check_numabalancing_enable(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

/* assumes fs == KERNEL_DS */
व्योम __init numa_policy_init(व्योम)
अणु
	nodemask_t पूर्णांकerleave_nodes;
	अचिन्हित दीर्घ largest = 0;
	पूर्णांक nid, prefer = 0;

	policy_cache = kmem_cache_create("numa_policy",
					 माप(काष्ठा mempolicy),
					 0, SLAB_PANIC, शून्य);

	sn_cache = kmem_cache_create("shared_policy_node",
				     माप(काष्ठा sp_node),
				     0, SLAB_PANIC, शून्य);

	क्रम_each_node(nid) अणु
		preferred_node_policy[nid] = (काष्ठा mempolicy) अणु
			.refcnt = ATOMIC_INIT(1),
			.mode = MPOL_PREFERRED,
			.flags = MPOL_F_MOF | MPOL_F_MORON,
			.v = अणु .preferred_node = nid, पूर्ण,
		पूर्ण;
	पूर्ण

	/*
	 * Set पूर्णांकerleaving policy क्रम प्रणाली init. Interleaving is only
	 * enabled across suitably sized nodes (शेष is >= 16MB), or
	 * fall back to the largest node अगर they're all smaller.
	 */
	nodes_clear(पूर्णांकerleave_nodes);
	क्रम_each_node_state(nid, N_MEMORY) अणु
		अचिन्हित दीर्घ total_pages = node_present_pages(nid);

		/* Preserve the largest node */
		अगर (largest < total_pages) अणु
			largest = total_pages;
			prefer = nid;
		पूर्ण

		/* Interleave this node? */
		अगर ((total_pages << PAGE_SHIFT) >= (16 << 20))
			node_set(nid, पूर्णांकerleave_nodes);
	पूर्ण

	/* All too small, use the largest */
	अगर (unlikely(nodes_empty(पूर्णांकerleave_nodes)))
		node_set(prefer, पूर्णांकerleave_nodes);

	अगर (करो_set_mempolicy(MPOL_INTERLEAVE, 0, &पूर्णांकerleave_nodes))
		pr_err("%s: interleaving failed\n", __func__);

	check_numabalancing_enable();
पूर्ण

/* Reset policy of current process to शेष */
व्योम numa_शेष_policy(व्योम)
अणु
	करो_set_mempolicy(MPOL_DEFAULT, 0, शून्य);
पूर्ण

/*
 * Parse and क्रमmat mempolicy from/to strings
 */

/*
 * "local" is implemented पूर्णांकernally by MPOL_PREFERRED with MPOL_F_LOCAL flag.
 */
अटल स्थिर अक्षर * स्थिर policy_modes[] =
अणु
	[MPOL_DEFAULT]    = "default",
	[MPOL_PREFERRED]  = "prefer",
	[MPOL_BIND]       = "bind",
	[MPOL_INTERLEAVE] = "interleave",
	[MPOL_LOCAL]      = "local",
पूर्ण;


#अगर_घोषित CONFIG_TMPFS
/**
 * mpol_parse_str - parse string to mempolicy, क्रम पंचांगpfs mpol mount option.
 * @str:  string containing mempolicy to parse
 * @mpol:  poपूर्णांकer to काष्ठा mempolicy poपूर्णांकer, वापसed on success.
 *
 * Format of input:
 *	<mode>[=<flags>][:<nodelist>]
 *
 * On success, वापसs 0, अन्यथा 1
 */
पूर्णांक mpol_parse_str(अक्षर *str, काष्ठा mempolicy **mpol)
अणु
	काष्ठा mempolicy *new = शून्य;
	अचिन्हित लघु mode_flags;
	nodemask_t nodes;
	अक्षर *nodelist = म_अक्षर(str, ':');
	अक्षर *flags = म_अक्षर(str, '=');
	पूर्णांक err = 1, mode;

	अगर (flags)
		*flags++ = '\0';	/* terminate mode string */

	अगर (nodelist) अणु
		/* NUL-terminate mode or flags string */
		*nodelist++ = '\0';
		अगर (nodelist_parse(nodelist, nodes))
			जाओ out;
		अगर (!nodes_subset(nodes, node_states[N_MEMORY]))
			जाओ out;
	पूर्ण अन्यथा
		nodes_clear(nodes);

	mode = match_string(policy_modes, MPOL_MAX, str);
	अगर (mode < 0)
		जाओ out;

	चयन (mode) अणु
	हाल MPOL_PREFERRED:
		/*
		 * Insist on a nodelist of one node only, although later
		 * we use first_node(nodes) to grab a single node, so here
		 * nodelist (or nodes) cannot be empty.
		 */
		अगर (nodelist) अणु
			अक्षर *rest = nodelist;
			जबतक (है_अंक(*rest))
				rest++;
			अगर (*rest)
				जाओ out;
			अगर (nodes_empty(nodes))
				जाओ out;
		पूर्ण
		अवरोध;
	हाल MPOL_INTERLEAVE:
		/*
		 * Default to online nodes with memory अगर no nodelist
		 */
		अगर (!nodelist)
			nodes = node_states[N_MEMORY];
		अवरोध;
	हाल MPOL_LOCAL:
		/*
		 * Don't allow a nodelist;  mpol_new() checks flags
		 */
		अगर (nodelist)
			जाओ out;
		mode = MPOL_PREFERRED;
		अवरोध;
	हाल MPOL_DEFAULT:
		/*
		 * Insist on a empty nodelist
		 */
		अगर (!nodelist)
			err = 0;
		जाओ out;
	हाल MPOL_BIND:
		/*
		 * Insist on a nodelist
		 */
		अगर (!nodelist)
			जाओ out;
	पूर्ण

	mode_flags = 0;
	अगर (flags) अणु
		/*
		 * Currently, we only support two mutually exclusive
		 * mode flags.
		 */
		अगर (!म_भेद(flags, "static"))
			mode_flags |= MPOL_F_STATIC_NODES;
		अन्यथा अगर (!म_भेद(flags, "relative"))
			mode_flags |= MPOL_F_RELATIVE_NODES;
		अन्यथा
			जाओ out;
	पूर्ण

	new = mpol_new(mode, mode_flags, &nodes);
	अगर (IS_ERR(new))
		जाओ out;

	/*
	 * Save nodes क्रम mpol_to_str() to show the पंचांगpfs mount options
	 * क्रम /proc/mounts, /proc/pid/mounts and /proc/pid/mountinfo.
	 */
	अगर (mode != MPOL_PREFERRED)
		new->v.nodes = nodes;
	अन्यथा अगर (nodelist)
		new->v.preferred_node = first_node(nodes);
	अन्यथा
		new->flags |= MPOL_F_LOCAL;

	/*
	 * Save nodes क्रम contextualization: this will be used to "clone"
	 * the mempolicy in a specअगरic context [cpuset] at a later समय.
	 */
	new->w.user_nodemask = nodes;

	err = 0;

out:
	/* Restore string क्रम error message */
	अगर (nodelist)
		*--nodelist = ':';
	अगर (flags)
		*--flags = '=';
	अगर (!err)
		*mpol = new;
	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_TMPFS */

/**
 * mpol_to_str - क्रमmat a mempolicy काष्ठाure क्रम prपूर्णांकing
 * @buffer:  to contain क्रमmatted mempolicy string
 * @maxlen:  length of @buffer
 * @pol:  poपूर्णांकer to mempolicy to be क्रमmatted
 *
 * Convert @pol पूर्णांकo a string.  If @buffer is too लघु, truncate the string.
 * Recommend a @maxlen of at least 32 क्रम the दीर्घest mode, "interleave", the
 * दीर्घest flag, "relative", and to display at least a few node ids.
 */
व्योम mpol_to_str(अक्षर *buffer, पूर्णांक maxlen, काष्ठा mempolicy *pol)
अणु
	अक्षर *p = buffer;
	nodemask_t nodes = NODE_MASK_NONE;
	अचिन्हित लघु mode = MPOL_DEFAULT;
	अचिन्हित लघु flags = 0;

	अगर (pol && pol != &शेष_policy && !(pol->flags & MPOL_F_MORON)) अणु
		mode = pol->mode;
		flags = pol->flags;
	पूर्ण

	चयन (mode) अणु
	हाल MPOL_DEFAULT:
		अवरोध;
	हाल MPOL_PREFERRED:
		अगर (flags & MPOL_F_LOCAL)
			mode = MPOL_LOCAL;
		अन्यथा
			node_set(pol->v.preferred_node, nodes);
		अवरोध;
	हाल MPOL_BIND:
	हाल MPOL_INTERLEAVE:
		nodes = pol->v.nodes;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		snम_लिखो(p, maxlen, "unknown");
		वापस;
	पूर्ण

	p += snम_लिखो(p, maxlen, "%s", policy_modes[mode]);

	अगर (flags & MPOL_MODE_FLAGS) अणु
		p += snम_लिखो(p, buffer + maxlen - p, "=");

		/*
		 * Currently, the only defined flags are mutually exclusive
		 */
		अगर (flags & MPOL_F_STATIC_NODES)
			p += snम_लिखो(p, buffer + maxlen - p, "static");
		अन्यथा अगर (flags & MPOL_F_RELATIVE_NODES)
			p += snम_लिखो(p, buffer + maxlen - p, "relative");
	पूर्ण

	अगर (!nodes_empty(nodes))
		p += scnम_लिखो(p, buffer + maxlen - p, ":%*pbl",
			       nodemask_pr_args(&nodes));
पूर्ण
