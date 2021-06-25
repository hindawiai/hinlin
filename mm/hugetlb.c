<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic hugetlb support.
 * (C) Nadia Yvette Chambers, April 2004
 */
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/compiler.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/mutex.h>
#समावेश <linux/memblock.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/rmap.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/jhash.h>
#समावेश <linux/numa.h>
#समावेश <linux/llist.h>
#समावेश <linux/cma.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlb.h>

#समावेश <linux/पन.स>
#समावेश <linux/hugetlb.h>
#समावेश <linux/hugetlb_cgroup.h>
#समावेश <linux/node.h>
#समावेश <linux/page_owner.h>
#समावेश "internal.h"

पूर्णांक hugetlb_max_hstate __पढ़ो_mostly;
अचिन्हित पूर्णांक शेष_hstate_idx;
काष्ठा hstate hstates[HUGE_MAX_HSTATE];

#अगर_घोषित CONFIG_CMA
अटल काष्ठा cma *hugetlb_cma[MAX_NUMNODES];
#पूर्ण_अगर
अटल अचिन्हित दीर्घ hugetlb_cma_size __initdata;

/*
 * Minimum page order among possible hugepage sizes, set to a proper value
 * at boot समय.
 */
अटल अचिन्हित पूर्णांक minimum_order __पढ़ो_mostly = अच_पूर्णांक_उच्च;

__initdata LIST_HEAD(huge_boot_pages);

/* क्रम command line parsing */
अटल काष्ठा hstate * __initdata parsed_hstate;
अटल अचिन्हित दीर्घ __initdata शेष_hstate_max_huge_pages;
अटल bool __initdata parsed_valid_hugepagesz = true;
अटल bool __initdata parsed_शेष_hugepagesz;

/*
 * Protects updates to hugepage_मुक्तlists, hugepage_activelist, nr_huge_pages,
 * मुक्त_huge_pages, and surplus_huge_pages.
 */
DEFINE_SPINLOCK(hugetlb_lock);

/*
 * Serializes faults on the same logical page.  This is used to
 * prevent spurious OOMs when the hugepage pool is fully utilized.
 */
अटल पूर्णांक num_fault_mutexes;
काष्ठा mutex *hugetlb_fault_mutex_table ____cacheline_aligned_in_smp;

/* Forward declaration */
अटल पूर्णांक hugetlb_acct_memory(काष्ठा hstate *h, दीर्घ delta);

अटल अंतरभूत bool subpool_is_मुक्त(काष्ठा hugepage_subpool *spool)
अणु
	अगर (spool->count)
		वापस false;
	अगर (spool->max_hpages != -1)
		वापस spool->used_hpages == 0;
	अगर (spool->min_hpages != -1)
		वापस spool->rsv_hpages == spool->min_hpages;

	वापस true;
पूर्ण

अटल अंतरभूत व्योम unlock_or_release_subpool(काष्ठा hugepage_subpool *spool,
						अचिन्हित दीर्घ irq_flags)
अणु
	spin_unlock_irqrestore(&spool->lock, irq_flags);

	/* If no pages are used, and no other handles to the subpool
	 * reमुख्य, give up any reservations based on minimum size and
	 * मुक्त the subpool */
	अगर (subpool_is_मुक्त(spool)) अणु
		अगर (spool->min_hpages != -1)
			hugetlb_acct_memory(spool->hstate,
						-spool->min_hpages);
		kमुक्त(spool);
	पूर्ण
पूर्ण

काष्ठा hugepage_subpool *hugepage_new_subpool(काष्ठा hstate *h, दीर्घ max_hpages,
						दीर्घ min_hpages)
अणु
	काष्ठा hugepage_subpool *spool;

	spool = kzalloc(माप(*spool), GFP_KERNEL);
	अगर (!spool)
		वापस शून्य;

	spin_lock_init(&spool->lock);
	spool->count = 1;
	spool->max_hpages = max_hpages;
	spool->hstate = h;
	spool->min_hpages = min_hpages;

	अगर (min_hpages != -1 && hugetlb_acct_memory(h, min_hpages)) अणु
		kमुक्त(spool);
		वापस शून्य;
	पूर्ण
	spool->rsv_hpages = min_hpages;

	वापस spool;
पूर्ण

व्योम hugepage_put_subpool(काष्ठा hugepage_subpool *spool)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spool->lock, flags);
	BUG_ON(!spool->count);
	spool->count--;
	unlock_or_release_subpool(spool, flags);
पूर्ण

/*
 * Subpool accounting क्रम allocating and reserving pages.
 * Return -ENOMEM अगर there are not enough resources to satisfy the
 * request.  Otherwise, वापस the number of pages by which the
 * global pools must be adjusted (upward).  The वापसed value may
 * only be dअगरferent than the passed value (delta) in the हाल where
 * a subpool minimum size must be मुख्यtained.
 */
अटल दीर्घ hugepage_subpool_get_pages(काष्ठा hugepage_subpool *spool,
				      दीर्घ delta)
अणु
	दीर्घ ret = delta;

	अगर (!spool)
		वापस ret;

	spin_lock_irq(&spool->lock);

	अगर (spool->max_hpages != -1) अणु		/* maximum size accounting */
		अगर ((spool->used_hpages + delta) <= spool->max_hpages)
			spool->used_hpages += delta;
		अन्यथा अणु
			ret = -ENOMEM;
			जाओ unlock_ret;
		पूर्ण
	पूर्ण

	/* minimum size accounting */
	अगर (spool->min_hpages != -1 && spool->rsv_hpages) अणु
		अगर (delta > spool->rsv_hpages) अणु
			/*
			 * Asking क्रम more reserves than those alपढ़ोy taken on
			 * behalf of subpool.  Return dअगरference.
			 */
			ret = delta - spool->rsv_hpages;
			spool->rsv_hpages = 0;
		पूर्ण अन्यथा अणु
			ret = 0;	/* reserves alपढ़ोy accounted क्रम */
			spool->rsv_hpages -= delta;
		पूर्ण
	पूर्ण

unlock_ret:
	spin_unlock_irq(&spool->lock);
	वापस ret;
पूर्ण

/*
 * Subpool accounting क्रम मुक्तing and unreserving pages.
 * Return the number of global page reservations that must be dropped.
 * The वापस value may only be dअगरferent than the passed value (delta)
 * in the हाल where a subpool minimum size must be मुख्यtained.
 */
अटल दीर्घ hugepage_subpool_put_pages(काष्ठा hugepage_subpool *spool,
				       दीर्घ delta)
अणु
	दीर्घ ret = delta;
	अचिन्हित दीर्घ flags;

	अगर (!spool)
		वापस delta;

	spin_lock_irqsave(&spool->lock, flags);

	अगर (spool->max_hpages != -1)		/* maximum size accounting */
		spool->used_hpages -= delta;

	 /* minimum size accounting */
	अगर (spool->min_hpages != -1 && spool->used_hpages < spool->min_hpages) अणु
		अगर (spool->rsv_hpages + delta <= spool->min_hpages)
			ret = 0;
		अन्यथा
			ret = spool->rsv_hpages + delta - spool->min_hpages;

		spool->rsv_hpages += delta;
		अगर (spool->rsv_hpages > spool->min_hpages)
			spool->rsv_hpages = spool->min_hpages;
	पूर्ण

	/*
	 * If hugetlbfs_put_super couldn't मुक्त spool due to an outstanding
	 * quota reference, मुक्त it now.
	 */
	unlock_or_release_subpool(spool, flags);

	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा hugepage_subpool *subpool_inode(काष्ठा inode *inode)
अणु
	वापस HUGETLBFS_SB(inode->i_sb)->spool;
पूर्ण

अटल अंतरभूत काष्ठा hugepage_subpool *subpool_vma(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस subpool_inode(file_inode(vma->vm_file));
पूर्ण

/* Helper that हटाओs a काष्ठा file_region from the resv_map cache and वापसs
 * it क्रम use.
 */
अटल काष्ठा file_region *
get_file_region_entry_from_cache(काष्ठा resv_map *resv, दीर्घ from, दीर्घ to)
अणु
	काष्ठा file_region *nrg = शून्य;

	VM_BUG_ON(resv->region_cache_count <= 0);

	resv->region_cache_count--;
	nrg = list_first_entry(&resv->region_cache, काष्ठा file_region, link);
	list_del(&nrg->link);

	nrg->from = from;
	nrg->to = to;

	वापस nrg;
पूर्ण

अटल व्योम copy_hugetlb_cgroup_unअक्षरge_info(काष्ठा file_region *nrg,
					      काष्ठा file_region *rg)
अणु
#अगर_घोषित CONFIG_CGROUP_HUGETLB
	nrg->reservation_counter = rg->reservation_counter;
	nrg->css = rg->css;
	अगर (rg->css)
		css_get(rg->css);
#पूर्ण_अगर
पूर्ण

/* Helper that records hugetlb_cgroup unअक्षरge info. */
अटल व्योम record_hugetlb_cgroup_unअक्षरge_info(काष्ठा hugetlb_cgroup *h_cg,
						काष्ठा hstate *h,
						काष्ठा resv_map *resv,
						काष्ठा file_region *nrg)
अणु
#अगर_घोषित CONFIG_CGROUP_HUGETLB
	अगर (h_cg) अणु
		nrg->reservation_counter =
			&h_cg->rsvd_hugepage[hstate_index(h)];
		nrg->css = &h_cg->css;
		/*
		 * The caller will hold exactly one h_cg->css reference क्रम the
		 * whole contiguous reservation region. But this area might be
		 * scattered when there are alपढ़ोy some file_regions reside in
		 * it. As a result, many file_regions may share only one css
		 * reference. In order to ensure that one file_region must hold
		 * exactly one h_cg->css reference, we should करो css_get क्रम
		 * each file_region and leave the reference held by caller
		 * untouched.
		 */
		css_get(&h_cg->css);
		अगर (!resv->pages_per_hpage)
			resv->pages_per_hpage = pages_per_huge_page(h);
		/* pages_per_hpage should be the same क्रम all entries in
		 * a resv_map.
		 */
		VM_BUG_ON(resv->pages_per_hpage != pages_per_huge_page(h));
	पूर्ण अन्यथा अणु
		nrg->reservation_counter = शून्य;
		nrg->css = शून्य;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम put_unअक्षरge_info(काष्ठा file_region *rg)
अणु
#अगर_घोषित CONFIG_CGROUP_HUGETLB
	अगर (rg->css)
		css_put(rg->css);
#पूर्ण_अगर
पूर्ण

अटल bool has_same_unअक्षरge_info(काष्ठा file_region *rg,
				   काष्ठा file_region *org)
अणु
#अगर_घोषित CONFIG_CGROUP_HUGETLB
	वापस rg && org &&
	       rg->reservation_counter == org->reservation_counter &&
	       rg->css == org->css;

#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

अटल व्योम coalesce_file_region(काष्ठा resv_map *resv, काष्ठा file_region *rg)
अणु
	काष्ठा file_region *nrg = शून्य, *prg = शून्य;

	prg = list_prev_entry(rg, link);
	अगर (&prg->link != &resv->regions && prg->to == rg->from &&
	    has_same_unअक्षरge_info(prg, rg)) अणु
		prg->to = rg->to;

		list_del(&rg->link);
		put_unअक्षरge_info(rg);
		kमुक्त(rg);

		rg = prg;
	पूर्ण

	nrg = list_next_entry(rg, link);
	अगर (&nrg->link != &resv->regions && nrg->from == rg->to &&
	    has_same_unअक्षरge_info(nrg, rg)) अणु
		nrg->from = rg->from;

		list_del(&rg->link);
		put_unअक्षरge_info(rg);
		kमुक्त(rg);
	पूर्ण
पूर्ण

अटल अंतरभूत दीर्घ
hugetlb_resv_map_add(काष्ठा resv_map *map, काष्ठा file_region *rg, दीर्घ from,
		     दीर्घ to, काष्ठा hstate *h, काष्ठा hugetlb_cgroup *cg,
		     दीर्घ *regions_needed)
अणु
	काष्ठा file_region *nrg;

	अगर (!regions_needed) अणु
		nrg = get_file_region_entry_from_cache(map, from, to);
		record_hugetlb_cgroup_unअक्षरge_info(cg, h, map, nrg);
		list_add(&nrg->link, rg->link.prev);
		coalesce_file_region(map, nrg);
	पूर्ण अन्यथा
		*regions_needed += 1;

	वापस to - from;
पूर्ण

/*
 * Must be called with resv->lock held.
 *
 * Calling this with regions_needed != शून्य will count the number of pages
 * to be added but will not modअगरy the linked list. And regions_needed will
 * indicate the number of file_regions needed in the cache to carry out to add
 * the regions क्रम this range.
 */
अटल दीर्घ add_reservation_in_range(काष्ठा resv_map *resv, दीर्घ f, दीर्घ t,
				     काष्ठा hugetlb_cgroup *h_cg,
				     काष्ठा hstate *h, दीर्घ *regions_needed)
अणु
	दीर्घ add = 0;
	काष्ठा list_head *head = &resv->regions;
	दीर्घ last_accounted_offset = f;
	काष्ठा file_region *rg = शून्य, *trg = शून्य;

	अगर (regions_needed)
		*regions_needed = 0;

	/* In this loop, we essentially handle an entry क्रम the range
	 * [last_accounted_offset, rg->from), at every iteration, with some
	 * bounds checking.
	 */
	list_क्रम_each_entry_safe(rg, trg, head, link) अणु
		/* Skip irrelevant regions that start beक्रमe our range. */
		अगर (rg->from < f) अणु
			/* If this region ends after the last accounted offset,
			 * then we need to update last_accounted_offset.
			 */
			अगर (rg->to > last_accounted_offset)
				last_accounted_offset = rg->to;
			जारी;
		पूर्ण

		/* When we find a region that starts beyond our range, we've
		 * finished.
		 */
		अगर (rg->from >= t)
			अवरोध;

		/* Add an entry क्रम last_accounted_offset -> rg->from, and
		 * update last_accounted_offset.
		 */
		अगर (rg->from > last_accounted_offset)
			add += hugetlb_resv_map_add(resv, rg,
						    last_accounted_offset,
						    rg->from, h, h_cg,
						    regions_needed);

		last_accounted_offset = rg->to;
	पूर्ण

	/* Handle the हाल where our range extends beyond
	 * last_accounted_offset.
	 */
	अगर (last_accounted_offset < t)
		add += hugetlb_resv_map_add(resv, rg, last_accounted_offset,
					    t, h, h_cg, regions_needed);

	VM_BUG_ON(add < 0);
	वापस add;
पूर्ण

/* Must be called with resv->lock acquired. Will drop lock to allocate entries.
 */
अटल पूर्णांक allocate_file_region_entries(काष्ठा resv_map *resv,
					पूर्णांक regions_needed)
	__must_hold(&resv->lock)
अणु
	काष्ठा list_head allocated_regions;
	पूर्णांक to_allocate = 0, i = 0;
	काष्ठा file_region *trg = शून्य, *rg = शून्य;

	VM_BUG_ON(regions_needed < 0);

	INIT_LIST_HEAD(&allocated_regions);

	/*
	 * Check क्रम sufficient descriptors in the cache to accommodate
	 * the number of in progress add operations plus regions_needed.
	 *
	 * This is a जबतक loop because when we drop the lock, some other call
	 * to region_add or region_del may have consumed some region_entries,
	 * so we keep looping here until we finally have enough entries क्रम
	 * (adds_in_progress + regions_needed).
	 */
	जबतक (resv->region_cache_count <
	       (resv->adds_in_progress + regions_needed)) अणु
		to_allocate = resv->adds_in_progress + regions_needed -
			      resv->region_cache_count;

		/* At this poपूर्णांक, we should have enough entries in the cache
		 * क्रम all the existing adds_in_progress. We should only be
		 * needing to allocate क्रम regions_needed.
		 */
		VM_BUG_ON(resv->region_cache_count < resv->adds_in_progress);

		spin_unlock(&resv->lock);
		क्रम (i = 0; i < to_allocate; i++) अणु
			trg = kदो_स्मृति(माप(*trg), GFP_KERNEL);
			अगर (!trg)
				जाओ out_of_memory;
			list_add(&trg->link, &allocated_regions);
		पूर्ण

		spin_lock(&resv->lock);

		list_splice(&allocated_regions, &resv->region_cache);
		resv->region_cache_count += to_allocate;
	पूर्ण

	वापस 0;

out_of_memory:
	list_क्रम_each_entry_safe(rg, trg, &allocated_regions, link) अणु
		list_del(&rg->link);
		kमुक्त(rg);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

/*
 * Add the huge page range represented by [f, t) to the reserve
 * map.  Regions will be taken from the cache to fill in this range.
 * Sufficient regions should exist in the cache due to the previous
 * call to region_chg with the same range, but in some हालs the cache will not
 * have sufficient entries due to races with other code करोing region_add or
 * region_del.  The extra needed entries will be allocated.
 *
 * regions_needed is the out value provided by a previous call to region_chg.
 *
 * Return the number of new huge pages added to the map.  This number is greater
 * than or equal to zero.  If file_region entries needed to be allocated क्रम
 * this operation and we were not able to allocate, it वापसs -ENOMEM.
 * region_add of regions of length 1 never allocate file_regions and cannot
 * fail; region_chg will always allocate at least 1 entry and a region_add क्रम
 * 1 page will only require at most 1 entry.
 */
अटल दीर्घ region_add(काष्ठा resv_map *resv, दीर्घ f, दीर्घ t,
		       दीर्घ in_regions_needed, काष्ठा hstate *h,
		       काष्ठा hugetlb_cgroup *h_cg)
अणु
	दीर्घ add = 0, actual_regions_needed = 0;

	spin_lock(&resv->lock);
retry:

	/* Count how many regions are actually needed to execute this add. */
	add_reservation_in_range(resv, f, t, शून्य, शून्य,
				 &actual_regions_needed);

	/*
	 * Check क्रम sufficient descriptors in the cache to accommodate
	 * this add operation. Note that actual_regions_needed may be greater
	 * than in_regions_needed, as the resv_map may have been modअगरied since
	 * the region_chg call. In this हाल, we need to make sure that we
	 * allocate extra entries, such that we have enough क्रम all the
	 * existing adds_in_progress, plus the excess needed क्रम this
	 * operation.
	 */
	अगर (actual_regions_needed > in_regions_needed &&
	    resv->region_cache_count <
		    resv->adds_in_progress +
			    (actual_regions_needed - in_regions_needed)) अणु
		/* region_add operation of range 1 should never need to
		 * allocate file_region entries.
		 */
		VM_BUG_ON(t - f <= 1);

		अगर (allocate_file_region_entries(
			    resv, actual_regions_needed - in_regions_needed)) अणु
			वापस -ENOMEM;
		पूर्ण

		जाओ retry;
	पूर्ण

	add = add_reservation_in_range(resv, f, t, h_cg, h, शून्य);

	resv->adds_in_progress -= in_regions_needed;

	spin_unlock(&resv->lock);
	वापस add;
पूर्ण

/*
 * Examine the existing reserve map and determine how many
 * huge pages in the specअगरied range [f, t) are NOT currently
 * represented.  This routine is called beक्रमe a subsequent
 * call to region_add that will actually modअगरy the reserve
 * map to add the specअगरied range [f, t).  region_chg करोes
 * not change the number of huge pages represented by the
 * map.  A number of new file_region काष्ठाures is added to the cache as a
 * placeholder, क्रम the subsequent region_add call to use. At least 1
 * file_region काष्ठाure is added.
 *
 * out_regions_needed is the number of regions added to the
 * resv->adds_in_progress.  This value needs to be provided to a follow up call
 * to region_add or region_पात क्रम proper accounting.
 *
 * Returns the number of huge pages that need to be added to the existing
 * reservation map क्रम the range [f, t).  This number is greater or equal to
 * zero.  -ENOMEM is वापसed अगर a new file_region काष्ठाure or cache entry
 * is needed and can not be allocated.
 */
अटल दीर्घ region_chg(काष्ठा resv_map *resv, दीर्घ f, दीर्घ t,
		       दीर्घ *out_regions_needed)
अणु
	दीर्घ chg = 0;

	spin_lock(&resv->lock);

	/* Count how many hugepages in this range are NOT represented. */
	chg = add_reservation_in_range(resv, f, t, शून्य, शून्य,
				       out_regions_needed);

	अगर (*out_regions_needed == 0)
		*out_regions_needed = 1;

	अगर (allocate_file_region_entries(resv, *out_regions_needed))
		वापस -ENOMEM;

	resv->adds_in_progress += *out_regions_needed;

	spin_unlock(&resv->lock);
	वापस chg;
पूर्ण

/*
 * Abort the in progress add operation.  The adds_in_progress field
 * of the resv_map keeps track of the operations in progress between
 * calls to region_chg and region_add.  Operations are someबार
 * पातed after the call to region_chg.  In such हालs, region_पात
 * is called to decrement the adds_in_progress counter. regions_needed
 * is the value वापसed by the region_chg call, it is used to decrement
 * the adds_in_progress counter.
 *
 * NOTE: The range arguments [f, t) are not needed or used in this
 * routine.  They are kept to make पढ़ोing the calling code easier as
 * arguments will match the associated region_chg call.
 */
अटल व्योम region_पात(काष्ठा resv_map *resv, दीर्घ f, दीर्घ t,
			 दीर्घ regions_needed)
अणु
	spin_lock(&resv->lock);
	VM_BUG_ON(!resv->region_cache_count);
	resv->adds_in_progress -= regions_needed;
	spin_unlock(&resv->lock);
पूर्ण

/*
 * Delete the specअगरied range [f, t) from the reserve map.  If the
 * t parameter is दीर्घ_उच्च, this indicates that ALL regions after f
 * should be deleted.  Locate the regions which पूर्णांकersect [f, t)
 * and either trim, delete or split the existing regions.
 *
 * Returns the number of huge pages deleted from the reserve map.
 * In the normal हाल, the वापस value is zero or more.  In the
 * हाल where a region must be split, a new region descriptor must
 * be allocated.  If the allocation fails, -ENOMEM will be वापसed.
 * NOTE: If the parameter t == दीर्घ_उच्च, then we will never split
 * a region and possibly वापस -ENOMEM.  Callers specअगरying
 * t == दीर्घ_उच्च करो not need to check क्रम -ENOMEM error.
 */
अटल दीर्घ region_del(काष्ठा resv_map *resv, दीर्घ f, दीर्घ t)
अणु
	काष्ठा list_head *head = &resv->regions;
	काष्ठा file_region *rg, *trg;
	काष्ठा file_region *nrg = शून्य;
	दीर्घ del = 0;

retry:
	spin_lock(&resv->lock);
	list_क्रम_each_entry_safe(rg, trg, head, link) अणु
		/*
		 * Skip regions beक्रमe the range to be deleted.  file_region
		 * ranges are normally of the क्रमm [from, to).  However, there
		 * may be a "placeholder" entry in the map which is of the क्रमm
		 * (from, to) with from == to.  Check क्रम placeholder entries
		 * at the beginning of the range to be deleted.
		 */
		अगर (rg->to <= f && (rg->to != rg->from || rg->to != f))
			जारी;

		अगर (rg->from >= t)
			अवरोध;

		अगर (f > rg->from && t < rg->to) अणु /* Must split region */
			/*
			 * Check क्रम an entry in the cache beक्रमe dropping
			 * lock and attempting allocation.
			 */
			अगर (!nrg &&
			    resv->region_cache_count > resv->adds_in_progress) अणु
				nrg = list_first_entry(&resv->region_cache,
							काष्ठा file_region,
							link);
				list_del(&nrg->link);
				resv->region_cache_count--;
			पूर्ण

			अगर (!nrg) अणु
				spin_unlock(&resv->lock);
				nrg = kदो_स्मृति(माप(*nrg), GFP_KERNEL);
				अगर (!nrg)
					वापस -ENOMEM;
				जाओ retry;
			पूर्ण

			del += t - f;
			hugetlb_cgroup_unअक्षरge_file_region(
				resv, rg, t - f, false);

			/* New entry क्रम end of split region */
			nrg->from = t;
			nrg->to = rg->to;

			copy_hugetlb_cgroup_unअक्षरge_info(nrg, rg);

			INIT_LIST_HEAD(&nrg->link);

			/* Original entry is trimmed */
			rg->to = f;

			list_add(&nrg->link, &rg->link);
			nrg = शून्य;
			अवरोध;
		पूर्ण

		अगर (f <= rg->from && t >= rg->to) अणु /* Remove entire region */
			del += rg->to - rg->from;
			hugetlb_cgroup_unअक्षरge_file_region(resv, rg,
							    rg->to - rg->from, true);
			list_del(&rg->link);
			kमुक्त(rg);
			जारी;
		पूर्ण

		अगर (f <= rg->from) अणु	/* Trim beginning of region */
			hugetlb_cgroup_unअक्षरge_file_region(resv, rg,
							    t - rg->from, false);

			del += t - rg->from;
			rg->from = t;
		पूर्ण अन्यथा अणु		/* Trim end of region */
			hugetlb_cgroup_unअक्षरge_file_region(resv, rg,
							    rg->to - f, false);

			del += rg->to - f;
			rg->to = f;
		पूर्ण
	पूर्ण

	spin_unlock(&resv->lock);
	kमुक्त(nrg);
	वापस del;
पूर्ण

/*
 * A rare out of memory error was encountered which prevented removal of
 * the reserve map region क्रम a page.  The huge page itself was मुक्त'ed
 * and हटाओd from the page cache.  This routine will adjust the subpool
 * usage count, and the global reserve count अगर needed.  By incrementing
 * these counts, the reserve map entry which could not be deleted will
 * appear as a "reserved" entry instead of simply dangling with incorrect
 * counts.
 */
व्योम hugetlb_fix_reserve_counts(काष्ठा inode *inode)
अणु
	काष्ठा hugepage_subpool *spool = subpool_inode(inode);
	दीर्घ rsv_adjust;
	bool reserved = false;

	rsv_adjust = hugepage_subpool_get_pages(spool, 1);
	अगर (rsv_adjust > 0) अणु
		काष्ठा hstate *h = hstate_inode(inode);

		अगर (!hugetlb_acct_memory(h, 1))
			reserved = true;
	पूर्ण अन्यथा अगर (!rsv_adjust) अणु
		reserved = true;
	पूर्ण

	अगर (!reserved)
		pr_warn("hugetlb: Huge Page Reserved count may go negative.\n");
पूर्ण

/*
 * Count and वापस the number of huge pages in the reserve map
 * that पूर्णांकersect with the range [f, t).
 */
अटल दीर्घ region_count(काष्ठा resv_map *resv, दीर्घ f, दीर्घ t)
अणु
	काष्ठा list_head *head = &resv->regions;
	काष्ठा file_region *rg;
	दीर्घ chg = 0;

	spin_lock(&resv->lock);
	/* Locate each segment we overlap with, and count that overlap. */
	list_क्रम_each_entry(rg, head, link) अणु
		दीर्घ seg_from;
		दीर्घ seg_to;

		अगर (rg->to <= f)
			जारी;
		अगर (rg->from >= t)
			अवरोध;

		seg_from = max(rg->from, f);
		seg_to = min(rg->to, t);

		chg += seg_to - seg_from;
	पूर्ण
	spin_unlock(&resv->lock);

	वापस chg;
पूर्ण

/*
 * Convert the address within this vma to the page offset within
 * the mapping, in pagecache page units; huge pages here.
 */
अटल pgoff_t vma_hugecache_offset(काष्ठा hstate *h,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	वापस ((address - vma->vm_start) >> huge_page_shअगरt(h)) +
			(vma->vm_pgoff >> huge_page_order(h));
पूर्ण

pgoff_t linear_hugepage_index(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ address)
अणु
	वापस vma_hugecache_offset(hstate_vma(vma), vma, address);
पूर्ण
EXPORT_SYMBOL_GPL(linear_hugepage_index);

/*
 * Return the size of the pages allocated when backing a VMA. In the majority
 * हालs this will be same size as used by the page table entries.
 */
अचिन्हित दीर्घ vma_kernel_pagesize(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->vm_ops && vma->vm_ops->pagesize)
		वापस vma->vm_ops->pagesize(vma);
	वापस PAGE_SIZE;
पूर्ण
EXPORT_SYMBOL_GPL(vma_kernel_pagesize);

/*
 * Return the page size being used by the MMU to back a VMA. In the majority
 * of हालs, the page size used by the kernel matches the MMU size. On
 * architectures where it dअगरfers, an architecture-specअगरic 'strong'
 * version of this symbol is required.
 */
__weak अचिन्हित दीर्घ vma_mmu_pagesize(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma_kernel_pagesize(vma);
पूर्ण

/*
 * Flags क्रम MAP_PRIVATE reservations.  These are stored in the bottom
 * bits of the reservation map poपूर्णांकer, which are always clear due to
 * alignment.
 */
#घोषणा HPAGE_RESV_OWNER    (1UL << 0)
#घोषणा HPAGE_RESV_UNMAPPED (1UL << 1)
#घोषणा HPAGE_RESV_MASK (HPAGE_RESV_OWNER | HPAGE_RESV_UNMAPPED)

/*
 * These helpers are used to track how many pages are reserved क्रम
 * faults in a MAP_PRIVATE mapping. Only the process that called mmap()
 * is guaranteed to have their future faults succeed.
 *
 * With the exception of reset_vma_resv_huge_pages() which is called at विभाजन(),
 * the reserve counters are updated with the hugetlb_lock held. It is safe
 * to reset the VMA at विभाजन() समय as it is not in use yet and there is no
 * chance of the global counters getting corrupted as a result of the values.
 *
 * The निजी mapping reservation is represented in a subtly dअगरferent
 * manner to a shared mapping.  A shared mapping has a region map associated
 * with the underlying file, this region map represents the backing file
 * pages which have ever had a reservation asचिन्हित which this persists even
 * after the page is instantiated.  A निजी mapping has a region map
 * associated with the original mmap which is attached to all VMAs which
 * reference it, this region map represents those offsets which have consumed
 * reservation ie. where pages have been instantiated.
 */
अटल अचिन्हित दीर्घ get_vma_निजी_data(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस (अचिन्हित दीर्घ)vma->vm_निजी_data;
पूर्ण

अटल व्योम set_vma_निजी_data(काष्ठा vm_area_काष्ठा *vma,
							अचिन्हित दीर्घ value)
अणु
	vma->vm_निजी_data = (व्योम *)value;
पूर्ण

अटल व्योम
resv_map_set_hugetlb_cgroup_unअक्षरge_info(काष्ठा resv_map *resv_map,
					  काष्ठा hugetlb_cgroup *h_cg,
					  काष्ठा hstate *h)
अणु
#अगर_घोषित CONFIG_CGROUP_HUGETLB
	अगर (!h_cg || !h) अणु
		resv_map->reservation_counter = शून्य;
		resv_map->pages_per_hpage = 0;
		resv_map->css = शून्य;
	पूर्ण अन्यथा अणु
		resv_map->reservation_counter =
			&h_cg->rsvd_hugepage[hstate_index(h)];
		resv_map->pages_per_hpage = pages_per_huge_page(h);
		resv_map->css = &h_cg->css;
	पूर्ण
#पूर्ण_अगर
पूर्ण

काष्ठा resv_map *resv_map_alloc(व्योम)
अणु
	काष्ठा resv_map *resv_map = kदो_स्मृति(माप(*resv_map), GFP_KERNEL);
	काष्ठा file_region *rg = kदो_स्मृति(माप(*rg), GFP_KERNEL);

	अगर (!resv_map || !rg) अणु
		kमुक्त(resv_map);
		kमुक्त(rg);
		वापस शून्य;
	पूर्ण

	kref_init(&resv_map->refs);
	spin_lock_init(&resv_map->lock);
	INIT_LIST_HEAD(&resv_map->regions);

	resv_map->adds_in_progress = 0;
	/*
	 * Initialize these to 0. On shared mappings, 0's here indicate these
	 * fields करोn't करो cgroup accounting. On निजी mappings, these will be
	 * re-initialized to the proper values, to indicate that hugetlb cgroup
	 * reservations are to be un-अक्षरged from here.
	 */
	resv_map_set_hugetlb_cgroup_unअक्षरge_info(resv_map, शून्य, शून्य);

	INIT_LIST_HEAD(&resv_map->region_cache);
	list_add(&rg->link, &resv_map->region_cache);
	resv_map->region_cache_count = 1;

	वापस resv_map;
पूर्ण

व्योम resv_map_release(काष्ठा kref *ref)
अणु
	काष्ठा resv_map *resv_map = container_of(ref, काष्ठा resv_map, refs);
	काष्ठा list_head *head = &resv_map->region_cache;
	काष्ठा file_region *rg, *trg;

	/* Clear out any active regions beक्रमe we release the map. */
	region_del(resv_map, 0, दीर्घ_उच्च);

	/* ... and any entries left in the cache */
	list_क्रम_each_entry_safe(rg, trg, head, link) अणु
		list_del(&rg->link);
		kमुक्त(rg);
	पूर्ण

	VM_BUG_ON(resv_map->adds_in_progress);

	kमुक्त(resv_map);
पूर्ण

अटल अंतरभूत काष्ठा resv_map *inode_resv_map(काष्ठा inode *inode)
अणु
	/*
	 * At inode evict समय, i_mapping may not poपूर्णांक to the original
	 * address space within the inode.  This original address space
	 * contains the poपूर्णांकer to the resv_map.  So, always use the
	 * address space embedded within the inode.
	 * The VERY common हाल is inode->mapping == &inode->i_data but,
	 * this may not be true क्रम device special inodes.
	 */
	वापस (काष्ठा resv_map *)(&inode->i_data)->निजी_data;
पूर्ण

अटल काष्ठा resv_map *vma_resv_map(काष्ठा vm_area_काष्ठा *vma)
अणु
	VM_BUG_ON_VMA(!is_vm_hugetlb_page(vma), vma);
	अगर (vma->vm_flags & VM_MAYSHARE) अणु
		काष्ठा address_space *mapping = vma->vm_file->f_mapping;
		काष्ठा inode *inode = mapping->host;

		वापस inode_resv_map(inode);

	पूर्ण अन्यथा अणु
		वापस (काष्ठा resv_map *)(get_vma_निजी_data(vma) &
							~HPAGE_RESV_MASK);
	पूर्ण
पूर्ण

अटल व्योम set_vma_resv_map(काष्ठा vm_area_काष्ठा *vma, काष्ठा resv_map *map)
अणु
	VM_BUG_ON_VMA(!is_vm_hugetlb_page(vma), vma);
	VM_BUG_ON_VMA(vma->vm_flags & VM_MAYSHARE, vma);

	set_vma_निजी_data(vma, (get_vma_निजी_data(vma) &
				HPAGE_RESV_MASK) | (अचिन्हित दीर्घ)map);
पूर्ण

अटल व्योम set_vma_resv_flags(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ flags)
अणु
	VM_BUG_ON_VMA(!is_vm_hugetlb_page(vma), vma);
	VM_BUG_ON_VMA(vma->vm_flags & VM_MAYSHARE, vma);

	set_vma_निजी_data(vma, get_vma_निजी_data(vma) | flags);
पूर्ण

अटल पूर्णांक is_vma_resv_set(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ flag)
अणु
	VM_BUG_ON_VMA(!is_vm_hugetlb_page(vma), vma);

	वापस (get_vma_निजी_data(vma) & flag) != 0;
पूर्ण

/* Reset counters to 0 and clear all HPAGE_RESV_* flags */
व्योम reset_vma_resv_huge_pages(काष्ठा vm_area_काष्ठा *vma)
अणु
	VM_BUG_ON_VMA(!is_vm_hugetlb_page(vma), vma);
	अगर (!(vma->vm_flags & VM_MAYSHARE))
		vma->vm_निजी_data = (व्योम *)0;
पूर्ण

/* Returns true अगर the VMA has associated reserve pages */
अटल bool vma_has_reserves(काष्ठा vm_area_काष्ठा *vma, दीर्घ chg)
अणु
	अगर (vma->vm_flags & VM_NORESERVE) अणु
		/*
		 * This address is alपढ़ोy reserved by other process(chg == 0),
		 * so, we should decrement reserved count. Without decrementing,
		 * reserve count reमुख्यs after releasing inode, because this
		 * allocated page will go पूर्णांकo page cache and is regarded as
		 * coming from reserved pool in releasing step.  Currently, we
		 * करोn't have any other solution to deal with this situation
		 * properly, so add work-around here.
		 */
		अगर (vma->vm_flags & VM_MAYSHARE && chg == 0)
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण

	/* Shared mappings always use reserves */
	अगर (vma->vm_flags & VM_MAYSHARE) अणु
		/*
		 * We know VM_NORESERVE is not set.  Thereक्रमe, there SHOULD
		 * be a region map क्रम all pages.  The only situation where
		 * there is no region map is अगर a hole was punched via
		 * fallocate.  In this हाल, there really are no reserves to
		 * use.  This situation is indicated अगर chg != 0.
		 */
		अगर (chg)
			वापस false;
		अन्यथा
			वापस true;
	पूर्ण

	/*
	 * Only the process that called mmap() has reserves क्रम
	 * निजी mappings.
	 */
	अगर (is_vma_resv_set(vma, HPAGE_RESV_OWNER)) अणु
		/*
		 * Like the shared हाल above, a hole punch or truncate
		 * could have been perक्रमmed on the निजी mapping.
		 * Examine the value of chg to determine अगर reserves
		 * actually exist or were previously consumed.
		 * Very Subtle - The value of chg comes from a previous
		 * call to vma_needs_reserves().  The reserve map क्रम
		 * निजी mappings has dअगरferent (opposite) semantics
		 * than that of shared mappings.  vma_needs_reserves()
		 * has alपढ़ोy taken this dअगरference in semantics पूर्णांकo
		 * account.  Thereक्रमe, the meaning of chg is the same
		 * as in the shared हाल above.  Code could easily be
		 * combined, but keeping it separate draws attention to
		 * subtle dअगरferences.
		 */
		अगर (chg)
			वापस false;
		अन्यथा
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम enqueue_huge_page(काष्ठा hstate *h, काष्ठा page *page)
अणु
	पूर्णांक nid = page_to_nid(page);

	lockdep_निश्चित_held(&hugetlb_lock);
	list_move(&page->lru, &h->hugepage_मुक्तlists[nid]);
	h->मुक्त_huge_pages++;
	h->मुक्त_huge_pages_node[nid]++;
	SetHPageFreed(page);
पूर्ण

अटल काष्ठा page *dequeue_huge_page_node_exact(काष्ठा hstate *h, पूर्णांक nid)
अणु
	काष्ठा page *page;
	bool pin = !!(current->flags & PF_MEMALLOC_PIN);

	lockdep_निश्चित_held(&hugetlb_lock);
	list_क्रम_each_entry(page, &h->hugepage_मुक्तlists[nid], lru) अणु
		अगर (pin && !is_pinnable_page(page))
			जारी;

		अगर (PageHWPoison(page))
			जारी;

		list_move(&page->lru, &h->hugepage_activelist);
		set_page_refcounted(page);
		ClearHPageFreed(page);
		h->मुक्त_huge_pages--;
		h->मुक्त_huge_pages_node[nid]--;
		वापस page;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा page *dequeue_huge_page_nodemask(काष्ठा hstate *h, gfp_t gfp_mask, पूर्णांक nid,
		nodemask_t *nmask)
अणु
	अचिन्हित पूर्णांक cpuset_mems_cookie;
	काष्ठा zonelist *zonelist;
	काष्ठा zone *zone;
	काष्ठा zoneref *z;
	पूर्णांक node = NUMA_NO_NODE;

	zonelist = node_zonelist(nid, gfp_mask);

retry_cpuset:
	cpuset_mems_cookie = पढ़ो_mems_allowed_begin();
	क्रम_each_zone_zonelist_nodemask(zone, z, zonelist, gfp_zone(gfp_mask), nmask) अणु
		काष्ठा page *page;

		अगर (!cpuset_zone_allowed(zone, gfp_mask))
			जारी;
		/*
		 * no need to ask again on the same node. Pool is node rather than
		 * zone aware
		 */
		अगर (zone_to_nid(zone) == node)
			जारी;
		node = zone_to_nid(zone);

		page = dequeue_huge_page_node_exact(h, node);
		अगर (page)
			वापस page;
	पूर्ण
	अगर (unlikely(पढ़ो_mems_allowed_retry(cpuset_mems_cookie)))
		जाओ retry_cpuset;

	वापस शून्य;
पूर्ण

अटल काष्ठा page *dequeue_huge_page_vma(काष्ठा hstate *h,
				काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ address, पूर्णांक aव्योम_reserve,
				दीर्घ chg)
अणु
	काष्ठा page *page;
	काष्ठा mempolicy *mpol;
	gfp_t gfp_mask;
	nodemask_t *nodemask;
	पूर्णांक nid;

	/*
	 * A child process with MAP_PRIVATE mappings created by their parent
	 * have no page reserves. This check ensures that reservations are
	 * not "stolen". The child may still get SIGKILLed
	 */
	अगर (!vma_has_reserves(vma, chg) &&
			h->मुक्त_huge_pages - h->resv_huge_pages == 0)
		जाओ err;

	/* If reserves cannot be used, ensure enough pages are in the pool */
	अगर (aव्योम_reserve && h->मुक्त_huge_pages - h->resv_huge_pages == 0)
		जाओ err;

	gfp_mask = htlb_alloc_mask(h);
	nid = huge_node(vma, address, gfp_mask, &mpol, &nodemask);
	page = dequeue_huge_page_nodemask(h, gfp_mask, nid, nodemask);
	अगर (page && !aव्योम_reserve && vma_has_reserves(vma, chg)) अणु
		SetHPageRestoreReserve(page);
		h->resv_huge_pages--;
	पूर्ण

	mpol_cond_put(mpol);
	वापस page;

err:
	वापस शून्य;
पूर्ण

/*
 * common helper functions क्रम hstate_next_node_to_अणुalloc|मुक्तपूर्ण.
 * We may have allocated or मुक्तd a huge page based on a dअगरferent
 * nodes_allowed previously, so h->next_node_to_अणुalloc|मुक्तपूर्ण might
 * be outside of *nodes_allowed.  Ensure that we use an allowed
 * node क्रम alloc or मुक्त.
 */
अटल पूर्णांक next_node_allowed(पूर्णांक nid, nodemask_t *nodes_allowed)
अणु
	nid = next_node_in(nid, *nodes_allowed);
	VM_BUG_ON(nid >= MAX_NUMNODES);

	वापस nid;
पूर्ण

अटल पूर्णांक get_valid_node_allowed(पूर्णांक nid, nodemask_t *nodes_allowed)
अणु
	अगर (!node_isset(nid, *nodes_allowed))
		nid = next_node_allowed(nid, nodes_allowed);
	वापस nid;
पूर्ण

/*
 * वापसs the previously saved node ["this node"] from which to
 * allocate a persistent huge page क्रम the pool and advance the
 * next node from which to allocate, handling wrap at end of node
 * mask.
 */
अटल पूर्णांक hstate_next_node_to_alloc(काष्ठा hstate *h,
					nodemask_t *nodes_allowed)
अणु
	पूर्णांक nid;

	VM_BUG_ON(!nodes_allowed);

	nid = get_valid_node_allowed(h->next_nid_to_alloc, nodes_allowed);
	h->next_nid_to_alloc = next_node_allowed(nid, nodes_allowed);

	वापस nid;
पूर्ण

/*
 * helper क्रम हटाओ_pool_huge_page() - वापस the previously saved
 * node ["this node"] from which to मुक्त a huge page.  Advance the
 * next node id whether or not we find a मुक्त huge page to मुक्त so
 * that the next attempt to मुक्त addresses the next node.
 */
अटल पूर्णांक hstate_next_node_to_मुक्त(काष्ठा hstate *h, nodemask_t *nodes_allowed)
अणु
	पूर्णांक nid;

	VM_BUG_ON(!nodes_allowed);

	nid = get_valid_node_allowed(h->next_nid_to_मुक्त, nodes_allowed);
	h->next_nid_to_मुक्त = next_node_allowed(nid, nodes_allowed);

	वापस nid;
पूर्ण

#घोषणा क्रम_each_node_mask_to_alloc(hs, nr_nodes, node, mask)		\
	क्रम (nr_nodes = nodes_weight(*mask);				\
		nr_nodes > 0 &&						\
		((node = hstate_next_node_to_alloc(hs, mask)) || 1);	\
		nr_nodes--)

#घोषणा क्रम_each_node_mask_to_मुक्त(hs, nr_nodes, node, mask)		\
	क्रम (nr_nodes = nodes_weight(*mask);				\
		nr_nodes > 0 &&						\
		((node = hstate_next_node_to_मुक्त(hs, mask)) || 1);	\
		nr_nodes--)

#अगर_घोषित CONFIG_ARCH_HAS_GIGANTIC_PAGE
अटल व्योम destroy_compound_gigantic_page(काष्ठा page *page,
					अचिन्हित पूर्णांक order)
अणु
	पूर्णांक i;
	पूर्णांक nr_pages = 1 << order;
	काष्ठा page *p = page + 1;

	atomic_set(compound_mapcount_ptr(page), 0);
	atomic_set(compound_pincount_ptr(page), 0);

	क्रम (i = 1; i < nr_pages; i++, p = mem_map_next(p, page, i)) अणु
		clear_compound_head(p);
		set_page_refcounted(p);
	पूर्ण

	set_compound_order(page, 0);
	page[1].compound_nr = 0;
	__ClearPageHead(page);
पूर्ण

अटल व्योम मुक्त_gigantic_page(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	/*
	 * If the page isn't allocated using the cma allocator,
	 * cma_release() वापसs false.
	 */
#अगर_घोषित CONFIG_CMA
	अगर (cma_release(hugetlb_cma[page_to_nid(page)], page, 1 << order))
		वापस;
#पूर्ण_अगर

	मुक्त_contig_range(page_to_pfn(page), 1 << order);
पूर्ण

#अगर_घोषित CONFIG_CONTIG_ALLOC
अटल काष्ठा page *alloc_gigantic_page(काष्ठा hstate *h, gfp_t gfp_mask,
		पूर्णांक nid, nodemask_t *nodemask)
अणु
	अचिन्हित दीर्घ nr_pages = pages_per_huge_page(h);
	अगर (nid == NUMA_NO_NODE)
		nid = numa_mem_id();

#अगर_घोषित CONFIG_CMA
	अणु
		काष्ठा page *page;
		पूर्णांक node;

		अगर (hugetlb_cma[nid]) अणु
			page = cma_alloc(hugetlb_cma[nid], nr_pages,
					huge_page_order(h), true);
			अगर (page)
				वापस page;
		पूर्ण

		अगर (!(gfp_mask & __GFP_THISNODE)) अणु
			क्रम_each_node_mask(node, *nodemask) अणु
				अगर (node == nid || !hugetlb_cma[node])
					जारी;

				page = cma_alloc(hugetlb_cma[node], nr_pages,
						huge_page_order(h), true);
				अगर (page)
					वापस page;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस alloc_contig_pages(nr_pages, gfp_mask, nid, nodemask);
पूर्ण

अटल व्योम prep_new_huge_page(काष्ठा hstate *h, काष्ठा page *page, पूर्णांक nid);
अटल व्योम prep_compound_gigantic_page(काष्ठा page *page, अचिन्हित पूर्णांक order);
#अन्यथा /* !CONFIG_CONTIG_ALLOC */
अटल काष्ठा page *alloc_gigantic_page(काष्ठा hstate *h, gfp_t gfp_mask,
					पूर्णांक nid, nodemask_t *nodemask)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_CONTIG_ALLOC */

#अन्यथा /* !CONFIG_ARCH_HAS_GIGANTIC_PAGE */
अटल काष्ठा page *alloc_gigantic_page(काष्ठा hstate *h, gfp_t gfp_mask,
					पूर्णांक nid, nodemask_t *nodemask)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम मुक्त_gigantic_page(काष्ठा page *page, अचिन्हित पूर्णांक order) अणु पूर्ण
अटल अंतरभूत व्योम destroy_compound_gigantic_page(काष्ठा page *page,
						अचिन्हित पूर्णांक order) अणु पूर्ण
#पूर्ण_अगर

/*
 * Remove hugetlb page from lists, and update dtor so that page appears
 * as just a compound page.  A reference is held on the page.
 *
 * Must be called with hugetlb lock held.
 */
अटल व्योम हटाओ_hugetlb_page(काष्ठा hstate *h, काष्ठा page *page,
							bool adjust_surplus)
अणु
	पूर्णांक nid = page_to_nid(page);

	VM_BUG_ON_PAGE(hugetlb_cgroup_from_page(page), page);
	VM_BUG_ON_PAGE(hugetlb_cgroup_from_page_rsvd(page), page);

	lockdep_निश्चित_held(&hugetlb_lock);
	अगर (hstate_is_gigantic(h) && !gigantic_page_runसमय_supported())
		वापस;

	list_del(&page->lru);

	अगर (HPageFreed(page)) अणु
		h->मुक्त_huge_pages--;
		h->मुक्त_huge_pages_node[nid]--;
	पूर्ण
	अगर (adjust_surplus) अणु
		h->surplus_huge_pages--;
		h->surplus_huge_pages_node[nid]--;
	पूर्ण

	set_page_refcounted(page);
	set_compound_page_dtor(page, शून्य_COMPOUND_DTOR);

	h->nr_huge_pages--;
	h->nr_huge_pages_node[nid]--;
पूर्ण

अटल व्योम update_and_मुक्त_page(काष्ठा hstate *h, काष्ठा page *page)
अणु
	पूर्णांक i;
	काष्ठा page *subpage = page;

	अगर (hstate_is_gigantic(h) && !gigantic_page_runसमय_supported())
		वापस;

	क्रम (i = 0; i < pages_per_huge_page(h);
	     i++, subpage = mem_map_next(subpage, page, i)) अणु
		subpage->flags &= ~(1 << PG_locked | 1 << PG_error |
				1 << PG_referenced | 1 << PG_dirty |
				1 << PG_active | 1 << PG_निजी |
				1 << PG_ग_लिखोback);
	पूर्ण
	अगर (hstate_is_gigantic(h)) अणु
		destroy_compound_gigantic_page(page, huge_page_order(h));
		मुक्त_gigantic_page(page, huge_page_order(h));
	पूर्ण अन्यथा अणु
		__मुक्त_pages(page, huge_page_order(h));
	पूर्ण
पूर्ण

अटल व्योम update_and_मुक्त_pages_bulk(काष्ठा hstate *h, काष्ठा list_head *list)
अणु
	काष्ठा page *page, *t_page;

	list_क्रम_each_entry_safe(page, t_page, list, lru) अणु
		update_and_मुक्त_page(h, page);
		cond_resched();
	पूर्ण
पूर्ण

काष्ठा hstate *माप_प्रकारo_hstate(अचिन्हित दीर्घ size)
अणु
	काष्ठा hstate *h;

	क्रम_each_hstate(h) अणु
		अगर (huge_page_size(h) == size)
			वापस h;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम मुक्त_huge_page(काष्ठा page *page)
अणु
	/*
	 * Can't pass hstate in here because it is called from the
	 * compound page deकाष्ठाor.
	 */
	काष्ठा hstate *h = page_hstate(page);
	पूर्णांक nid = page_to_nid(page);
	काष्ठा hugepage_subpool *spool = hugetlb_page_subpool(page);
	bool restore_reserve;
	अचिन्हित दीर्घ flags;

	VM_BUG_ON_PAGE(page_count(page), page);
	VM_BUG_ON_PAGE(page_mapcount(page), page);

	hugetlb_set_page_subpool(page, शून्य);
	page->mapping = शून्य;
	restore_reserve = HPageRestoreReserve(page);
	ClearHPageRestoreReserve(page);

	/*
	 * If HPageRestoreReserve was set on page, page allocation consumed a
	 * reservation.  If the page was associated with a subpool, there
	 * would have been a page reserved in the subpool beक्रमe allocation
	 * via hugepage_subpool_get_pages().  Since we are 'restoring' the
	 * reservation, करो not call hugepage_subpool_put_pages() as this will
	 * हटाओ the reserved page from the subpool.
	 */
	अगर (!restore_reserve) अणु
		/*
		 * A वापस code of zero implies that the subpool will be
		 * under its minimum size अगर the reservation is not restored
		 * after page is मुक्त.  Thereक्रमe, क्रमce restore_reserve
		 * operation.
		 */
		अगर (hugepage_subpool_put_pages(spool, 1) == 0)
			restore_reserve = true;
	पूर्ण

	spin_lock_irqsave(&hugetlb_lock, flags);
	ClearHPageMigratable(page);
	hugetlb_cgroup_unअक्षरge_page(hstate_index(h),
				     pages_per_huge_page(h), page);
	hugetlb_cgroup_unअक्षरge_page_rsvd(hstate_index(h),
					  pages_per_huge_page(h), page);
	अगर (restore_reserve)
		h->resv_huge_pages++;

	अगर (HPageTemporary(page)) अणु
		हटाओ_hugetlb_page(h, page, false);
		spin_unlock_irqrestore(&hugetlb_lock, flags);
		update_and_मुक्त_page(h, page);
	पूर्ण अन्यथा अगर (h->surplus_huge_pages_node[nid]) अणु
		/* हटाओ the page from active list */
		हटाओ_hugetlb_page(h, page, true);
		spin_unlock_irqrestore(&hugetlb_lock, flags);
		update_and_मुक्त_page(h, page);
	पूर्ण अन्यथा अणु
		arch_clear_hugepage_flags(page);
		enqueue_huge_page(h, page);
		spin_unlock_irqrestore(&hugetlb_lock, flags);
	पूर्ण
पूर्ण

/*
 * Must be called with the hugetlb lock held
 */
अटल व्योम __prep_account_new_huge_page(काष्ठा hstate *h, पूर्णांक nid)
अणु
	lockdep_निश्चित_held(&hugetlb_lock);
	h->nr_huge_pages++;
	h->nr_huge_pages_node[nid]++;
पूर्ण

अटल व्योम __prep_new_huge_page(काष्ठा page *page)
अणु
	INIT_LIST_HEAD(&page->lru);
	set_compound_page_dtor(page, HUGETLB_PAGE_DTOR);
	hugetlb_set_page_subpool(page, शून्य);
	set_hugetlb_cgroup(page, शून्य);
	set_hugetlb_cgroup_rsvd(page, शून्य);
पूर्ण

अटल व्योम prep_new_huge_page(काष्ठा hstate *h, काष्ठा page *page, पूर्णांक nid)
अणु
	__prep_new_huge_page(page);
	spin_lock_irq(&hugetlb_lock);
	__prep_account_new_huge_page(h, nid);
	spin_unlock_irq(&hugetlb_lock);
पूर्ण

अटल व्योम prep_compound_gigantic_page(काष्ठा page *page, अचिन्हित पूर्णांक order)
अणु
	पूर्णांक i;
	पूर्णांक nr_pages = 1 << order;
	काष्ठा page *p = page + 1;

	/* we rely on prep_new_huge_page to set the deकाष्ठाor */
	set_compound_order(page, order);
	__ClearPageReserved(page);
	__SetPageHead(page);
	क्रम (i = 1; i < nr_pages; i++, p = mem_map_next(p, page, i)) अणु
		/*
		 * For gigantic hugepages allocated through booपंचांगem at
		 * boot, it's safer to be consistent with the not-gigantic
		 * hugepages and clear the PG_reserved bit from all tail pages
		 * too.  Otherwise drivers using get_user_pages() to access tail
		 * pages may get the reference counting wrong अगर they see
		 * PG_reserved set on a tail page (despite the head page not
		 * having PG_reserved set).  Enक्रमcing this consistency between
		 * head and tail pages allows drivers to optimize away a check
		 * on the head page when they need know अगर put_page() is needed
		 * after get_user_pages().
		 */
		__ClearPageReserved(p);
		set_page_count(p, 0);
		set_compound_head(p, page);
	पूर्ण
	atomic_set(compound_mapcount_ptr(page), -1);
	atomic_set(compound_pincount_ptr(page), 0);
पूर्ण

/*
 * PageHuge() only वापसs true क्रम hugetlbfs pages, but not क्रम normal or
 * transparent huge pages.  See the PageTransHuge() करोcumentation क्रम more
 * details.
 */
पूर्णांक PageHuge(काष्ठा page *page)
अणु
	अगर (!PageCompound(page))
		वापस 0;

	page = compound_head(page);
	वापस page[1].compound_dtor == HUGETLB_PAGE_DTOR;
पूर्ण
EXPORT_SYMBOL_GPL(PageHuge);

/*
 * PageHeadHuge() only वापसs true क्रम hugetlbfs head page, but not क्रम
 * normal or transparent huge pages.
 */
पूर्णांक PageHeadHuge(काष्ठा page *page_head)
अणु
	अगर (!PageHead(page_head))
		वापस 0;

	वापस page_head[1].compound_dtor == HUGETLB_PAGE_DTOR;
पूर्ण

/*
 * Find and lock address space (mapping) in ग_लिखो mode.
 *
 * Upon entry, the page is locked which means that page_mapping() is
 * stable.  Due to locking order, we can only trylock_ग_लिखो.  If we can
 * not get the lock, simply वापस शून्य to caller.
 */
काष्ठा address_space *hugetlb_page_mapping_lock_ग_लिखो(काष्ठा page *hpage)
अणु
	काष्ठा address_space *mapping = page_mapping(hpage);

	अगर (!mapping)
		वापस mapping;

	अगर (i_mmap_trylock_ग_लिखो(mapping))
		वापस mapping;

	वापस शून्य;
पूर्ण

pgoff_t __basepage_index(काष्ठा page *page)
अणु
	काष्ठा page *page_head = compound_head(page);
	pgoff_t index = page_index(page_head);
	अचिन्हित दीर्घ compound_idx;

	अगर (!PageHuge(page_head))
		वापस page_index(page);

	अगर (compound_order(page_head) >= MAX_ORDER)
		compound_idx = page_to_pfn(page) - page_to_pfn(page_head);
	अन्यथा
		compound_idx = page - page_head;

	वापस (index << compound_order(page_head)) + compound_idx;
पूर्ण

अटल काष्ठा page *alloc_buddy_huge_page(काष्ठा hstate *h,
		gfp_t gfp_mask, पूर्णांक nid, nodemask_t *nmask,
		nodemask_t *node_alloc_noretry)
अणु
	पूर्णांक order = huge_page_order(h);
	काष्ठा page *page;
	bool alloc_try_hard = true;

	/*
	 * By शेष we always try hard to allocate the page with
	 * __GFP_RETRY_MAYFAIL flag.  However, अगर we are allocating pages in
	 * a loop (to adjust global huge page counts) and previous allocation
	 * failed, करो not जारी to try hard on the same node.  Use the
	 * node_alloc_noretry biपंचांगap to manage this state inक्रमmation.
	 */
	अगर (node_alloc_noretry && node_isset(nid, *node_alloc_noretry))
		alloc_try_hard = false;
	gfp_mask |= __GFP_COMP|__GFP_NOWARN;
	अगर (alloc_try_hard)
		gfp_mask |= __GFP_RETRY_MAYFAIL;
	अगर (nid == NUMA_NO_NODE)
		nid = numa_mem_id();
	page = __alloc_pages(gfp_mask, order, nid, nmask);
	अगर (page)
		__count_vm_event(HTLB_BUDDY_PGALLOC);
	अन्यथा
		__count_vm_event(HTLB_BUDDY_PGALLOC_FAIL);

	/*
	 * If we did not specअगरy __GFP_RETRY_MAYFAIL, but still got a page this
	 * indicates an overall state change.  Clear bit so that we resume
	 * normal 'try hard' allocations.
	 */
	अगर (node_alloc_noretry && page && !alloc_try_hard)
		node_clear(nid, *node_alloc_noretry);

	/*
	 * If we tried hard to get a page but failed, set bit so that
	 * subsequent attempts will not try as hard until there is an
	 * overall state change.
	 */
	अगर (node_alloc_noretry && !page && alloc_try_hard)
		node_set(nid, *node_alloc_noretry);

	वापस page;
पूर्ण

/*
 * Common helper to allocate a fresh hugetlb page. All specअगरic allocators
 * should use this function to get new hugetlb pages
 */
अटल काष्ठा page *alloc_fresh_huge_page(काष्ठा hstate *h,
		gfp_t gfp_mask, पूर्णांक nid, nodemask_t *nmask,
		nodemask_t *node_alloc_noretry)
अणु
	काष्ठा page *page;

	अगर (hstate_is_gigantic(h))
		page = alloc_gigantic_page(h, gfp_mask, nid, nmask);
	अन्यथा
		page = alloc_buddy_huge_page(h, gfp_mask,
				nid, nmask, node_alloc_noretry);
	अगर (!page)
		वापस शून्य;

	अगर (hstate_is_gigantic(h))
		prep_compound_gigantic_page(page, huge_page_order(h));
	prep_new_huge_page(h, page, page_to_nid(page));

	वापस page;
पूर्ण

/*
 * Allocates a fresh page to the hugetlb allocator pool in the node पूर्णांकerleaved
 * manner.
 */
अटल पूर्णांक alloc_pool_huge_page(काष्ठा hstate *h, nodemask_t *nodes_allowed,
				nodemask_t *node_alloc_noretry)
अणु
	काष्ठा page *page;
	पूर्णांक nr_nodes, node;
	gfp_t gfp_mask = htlb_alloc_mask(h) | __GFP_THISNODE;

	क्रम_each_node_mask_to_alloc(h, nr_nodes, node, nodes_allowed) अणु
		page = alloc_fresh_huge_page(h, gfp_mask, node, nodes_allowed,
						node_alloc_noretry);
		अगर (page)
			अवरोध;
	पूर्ण

	अगर (!page)
		वापस 0;

	put_page(page); /* मुक्त it पूर्णांकo the hugepage allocator */

	वापस 1;
पूर्ण

/*
 * Remove huge page from pool from next node to मुक्त.  Attempt to keep
 * persistent huge pages more or less balanced over allowed nodes.
 * This routine only 'removes' the hugetlb page.  The caller must make
 * an additional call to मुक्त the page to low level allocators.
 * Called with hugetlb_lock locked.
 */
अटल काष्ठा page *हटाओ_pool_huge_page(काष्ठा hstate *h,
						nodemask_t *nodes_allowed,
						 bool acct_surplus)
अणु
	पूर्णांक nr_nodes, node;
	काष्ठा page *page = शून्य;

	lockdep_निश्चित_held(&hugetlb_lock);
	क्रम_each_node_mask_to_मुक्त(h, nr_nodes, node, nodes_allowed) अणु
		/*
		 * If we're वापसing unused surplus pages, only examine
		 * nodes with surplus pages.
		 */
		अगर ((!acct_surplus || h->surplus_huge_pages_node[node]) &&
		    !list_empty(&h->hugepage_मुक्तlists[node])) अणु
			page = list_entry(h->hugepage_मुक्तlists[node].next,
					  काष्ठा page, lru);
			हटाओ_hugetlb_page(h, page, acct_surplus);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस page;
पूर्ण

/*
 * Dissolve a given मुक्त hugepage पूर्णांकo मुक्त buddy pages. This function करोes
 * nothing क्रम in-use hugepages and non-hugepages.
 * This function वापसs values like below:
 *
 *  -EBUSY: failed to dissolved मुक्त hugepages or the hugepage is in-use
 *          (allocated or reserved.)
 *       0: successfully dissolved मुक्त hugepages or the page is not a
 *          hugepage (considered as alपढ़ोy dissolved)
 */
पूर्णांक dissolve_मुक्त_huge_page(काष्ठा page *page)
अणु
	पूर्णांक rc = -EBUSY;

retry:
	/* Not to disrupt normal path by vainly holding hugetlb_lock */
	अगर (!PageHuge(page))
		वापस 0;

	spin_lock_irq(&hugetlb_lock);
	अगर (!PageHuge(page)) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	अगर (!page_count(page)) अणु
		काष्ठा page *head = compound_head(page);
		काष्ठा hstate *h = page_hstate(head);
		अगर (h->मुक्त_huge_pages - h->resv_huge_pages == 0)
			जाओ out;

		/*
		 * We should make sure that the page is alपढ़ोy on the मुक्त list
		 * when it is dissolved.
		 */
		अगर (unlikely(!HPageFreed(head))) अणु
			spin_unlock_irq(&hugetlb_lock);
			cond_resched();

			/*
			 * Theoretically, we should वापस -EBUSY when we
			 * encounter this race. In fact, we have a chance
			 * to successfully dissolve the page अगर we करो a
			 * retry. Because the race winकरोw is quite small.
			 * If we seize this opportunity, it is an optimization
			 * क्रम increasing the success rate of dissolving page.
			 */
			जाओ retry;
		पूर्ण

		/*
		 * Move PageHWPoison flag from head page to the raw error page,
		 * which makes any subpages rather than the error page reusable.
		 */
		अगर (PageHWPoison(head) && page != head) अणु
			SetPageHWPoison(page);
			ClearPageHWPoison(head);
		पूर्ण
		हटाओ_hugetlb_page(h, head, false);
		h->max_huge_pages--;
		spin_unlock_irq(&hugetlb_lock);
		update_and_मुक्त_page(h, head);
		वापस 0;
	पूर्ण
out:
	spin_unlock_irq(&hugetlb_lock);
	वापस rc;
पूर्ण

/*
 * Dissolve मुक्त hugepages in a given pfn range. Used by memory hotplug to
 * make specअगरied memory blocks removable from the प्रणाली.
 * Note that this will dissolve a मुक्त gigantic hugepage completely, अगर any
 * part of it lies within the given range.
 * Also note that अगर dissolve_मुक्त_huge_page() वापसs with an error, all
 * मुक्त hugepages that were dissolved beक्रमe that error are lost.
 */
पूर्णांक dissolve_मुक्त_huge_pages(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn)
अणु
	अचिन्हित दीर्घ pfn;
	काष्ठा page *page;
	पूर्णांक rc = 0;

	अगर (!hugepages_supported())
		वापस rc;

	क्रम (pfn = start_pfn; pfn < end_pfn; pfn += 1 << minimum_order) अणु
		page = pfn_to_page(pfn);
		rc = dissolve_मुक्त_huge_page(page);
		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Allocates a fresh surplus page from the page allocator.
 */
अटल काष्ठा page *alloc_surplus_huge_page(काष्ठा hstate *h, gfp_t gfp_mask,
		पूर्णांक nid, nodemask_t *nmask)
अणु
	काष्ठा page *page = शून्य;

	अगर (hstate_is_gigantic(h))
		वापस शून्य;

	spin_lock_irq(&hugetlb_lock);
	अगर (h->surplus_huge_pages >= h->nr_overcommit_huge_pages)
		जाओ out_unlock;
	spin_unlock_irq(&hugetlb_lock);

	page = alloc_fresh_huge_page(h, gfp_mask, nid, nmask, शून्य);
	अगर (!page)
		वापस शून्य;

	spin_lock_irq(&hugetlb_lock);
	/*
	 * We could have raced with the pool size change.
	 * Double check that and simply deallocate the new page
	 * अगर we would end up overcommiting the surpluses. Abuse
	 * temporary page to workaround the nasty मुक्त_huge_page
	 * codeflow
	 */
	अगर (h->surplus_huge_pages >= h->nr_overcommit_huge_pages) अणु
		SetHPageTemporary(page);
		spin_unlock_irq(&hugetlb_lock);
		put_page(page);
		वापस शून्य;
	पूर्ण अन्यथा अणु
		h->surplus_huge_pages++;
		h->surplus_huge_pages_node[page_to_nid(page)]++;
	पूर्ण

out_unlock:
	spin_unlock_irq(&hugetlb_lock);

	वापस page;
पूर्ण

अटल काष्ठा page *alloc_migrate_huge_page(काष्ठा hstate *h, gfp_t gfp_mask,
				     पूर्णांक nid, nodemask_t *nmask)
अणु
	काष्ठा page *page;

	अगर (hstate_is_gigantic(h))
		वापस शून्य;

	page = alloc_fresh_huge_page(h, gfp_mask, nid, nmask, शून्य);
	अगर (!page)
		वापस शून्य;

	/*
	 * We करो not account these pages as surplus because they are only
	 * temporary and will be released properly on the last reference
	 */
	SetHPageTemporary(page);

	वापस page;
पूर्ण

/*
 * Use the VMA's mpolicy to allocate a huge page from the buddy.
 */
अटल
काष्ठा page *alloc_buddy_huge_page_with_mpol(काष्ठा hstate *h,
		काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	काष्ठा page *page;
	काष्ठा mempolicy *mpol;
	gfp_t gfp_mask = htlb_alloc_mask(h);
	पूर्णांक nid;
	nodemask_t *nodemask;

	nid = huge_node(vma, addr, gfp_mask, &mpol, &nodemask);
	page = alloc_surplus_huge_page(h, gfp_mask, nid, nodemask);
	mpol_cond_put(mpol);

	वापस page;
पूर्ण

/* page migration callback function */
काष्ठा page *alloc_huge_page_nodemask(काष्ठा hstate *h, पूर्णांक preferred_nid,
		nodemask_t *nmask, gfp_t gfp_mask)
अणु
	spin_lock_irq(&hugetlb_lock);
	अगर (h->मुक्त_huge_pages - h->resv_huge_pages > 0) अणु
		काष्ठा page *page;

		page = dequeue_huge_page_nodemask(h, gfp_mask, preferred_nid, nmask);
		अगर (page) अणु
			spin_unlock_irq(&hugetlb_lock);
			वापस page;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&hugetlb_lock);

	वापस alloc_migrate_huge_page(h, gfp_mask, preferred_nid, nmask);
पूर्ण

/* mempolicy aware migration callback */
काष्ठा page *alloc_huge_page_vma(काष्ठा hstate *h, काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address)
अणु
	काष्ठा mempolicy *mpol;
	nodemask_t *nodemask;
	काष्ठा page *page;
	gfp_t gfp_mask;
	पूर्णांक node;

	gfp_mask = htlb_alloc_mask(h);
	node = huge_node(vma, address, gfp_mask, &mpol, &nodemask);
	page = alloc_huge_page_nodemask(h, node, nodemask, gfp_mask);
	mpol_cond_put(mpol);

	वापस page;
पूर्ण

/*
 * Increase the hugetlb pool such that it can accommodate a reservation
 * of size 'delta'.
 */
अटल पूर्णांक gather_surplus_pages(काष्ठा hstate *h, दीर्घ delta)
	__must_hold(&hugetlb_lock)
अणु
	काष्ठा list_head surplus_list;
	काष्ठा page *page, *पंचांगp;
	पूर्णांक ret;
	दीर्घ i;
	दीर्घ needed, allocated;
	bool alloc_ok = true;

	lockdep_निश्चित_held(&hugetlb_lock);
	needed = (h->resv_huge_pages + delta) - h->मुक्त_huge_pages;
	अगर (needed <= 0) अणु
		h->resv_huge_pages += delta;
		वापस 0;
	पूर्ण

	allocated = 0;
	INIT_LIST_HEAD(&surplus_list);

	ret = -ENOMEM;
retry:
	spin_unlock_irq(&hugetlb_lock);
	क्रम (i = 0; i < needed; i++) अणु
		page = alloc_surplus_huge_page(h, htlb_alloc_mask(h),
				NUMA_NO_NODE, शून्य);
		अगर (!page) अणु
			alloc_ok = false;
			अवरोध;
		पूर्ण
		list_add(&page->lru, &surplus_list);
		cond_resched();
	पूर्ण
	allocated += i;

	/*
	 * After retaking hugetlb_lock, we need to recalculate 'needed'
	 * because either resv_huge_pages or मुक्त_huge_pages may have changed.
	 */
	spin_lock_irq(&hugetlb_lock);
	needed = (h->resv_huge_pages + delta) -
			(h->मुक्त_huge_pages + allocated);
	अगर (needed > 0) अणु
		अगर (alloc_ok)
			जाओ retry;
		/*
		 * We were not able to allocate enough pages to
		 * satisfy the entire reservation so we मुक्त what
		 * we've allocated so far.
		 */
		जाओ मुक्त;
	पूर्ण
	/*
	 * The surplus_list now contains _at_least_ the number of extra pages
	 * needed to accommodate the reservation.  Add the appropriate number
	 * of pages to the hugetlb pool and मुक्त the extras back to the buddy
	 * allocator.  Commit the entire reservation here to prevent another
	 * process from stealing the pages as they are added to the pool but
	 * beक्रमe they are reserved.
	 */
	needed += allocated;
	h->resv_huge_pages += delta;
	ret = 0;

	/* Free the needed pages to the hugetlb pool */
	list_क्रम_each_entry_safe(page, पंचांगp, &surplus_list, lru) अणु
		पूर्णांक zeroed;

		अगर ((--needed) < 0)
			अवरोध;
		/*
		 * This page is now managed by the hugetlb allocator and has
		 * no users -- drop the buddy allocator's reference.
		 */
		zeroed = put_page_testzero(page);
		VM_BUG_ON_PAGE(!zeroed, page);
		enqueue_huge_page(h, page);
	पूर्ण
मुक्त:
	spin_unlock_irq(&hugetlb_lock);

	/* Free unnecessary surplus pages to the buddy allocator */
	list_क्रम_each_entry_safe(page, पंचांगp, &surplus_list, lru)
		put_page(page);
	spin_lock_irq(&hugetlb_lock);

	वापस ret;
पूर्ण

/*
 * This routine has two मुख्य purposes:
 * 1) Decrement the reservation count (resv_huge_pages) by the value passed
 *    in unused_resv_pages.  This corresponds to the prior adjusपंचांगents made
 *    to the associated reservation map.
 * 2) Free any unused surplus pages that may have been allocated to satisfy
 *    the reservation.  As many as unused_resv_pages may be मुक्तd.
 */
अटल व्योम वापस_unused_surplus_pages(काष्ठा hstate *h,
					अचिन्हित दीर्घ unused_resv_pages)
अणु
	अचिन्हित दीर्घ nr_pages;
	काष्ठा page *page;
	LIST_HEAD(page_list);

	lockdep_निश्चित_held(&hugetlb_lock);
	/* Uncommit the reservation */
	h->resv_huge_pages -= unused_resv_pages;

	/* Cannot वापस gigantic pages currently */
	अगर (hstate_is_gigantic(h))
		जाओ out;

	/*
	 * Part (or even all) of the reservation could have been backed
	 * by pre-allocated pages. Only मुक्त surplus pages.
	 */
	nr_pages = min(unused_resv_pages, h->surplus_huge_pages);

	/*
	 * We want to release as many surplus pages as possible, spपढ़ो
	 * evenly across all nodes with memory. Iterate across these nodes
	 * until we can no दीर्घer मुक्त unreserved surplus pages. This occurs
	 * when the nodes with surplus pages have no मुक्त pages.
	 * हटाओ_pool_huge_page() will balance the मुक्तd pages across the
	 * on-line nodes with memory and will handle the hstate accounting.
	 */
	जबतक (nr_pages--) अणु
		page = हटाओ_pool_huge_page(h, &node_states[N_MEMORY], 1);
		अगर (!page)
			जाओ out;

		list_add(&page->lru, &page_list);
	पूर्ण

out:
	spin_unlock_irq(&hugetlb_lock);
	update_and_मुक्त_pages_bulk(h, &page_list);
	spin_lock_irq(&hugetlb_lock);
पूर्ण


/*
 * vma_needs_reservation, vma_commit_reservation and vma_end_reservation
 * are used by the huge page allocation routines to manage reservations.
 *
 * vma_needs_reservation is called to determine अगर the huge page at addr
 * within the vma has an associated reservation.  If a reservation is
 * needed, the value 1 is वापसed.  The caller is then responsible क्रम
 * managing the global reservation and subpool usage counts.  After
 * the huge page has been allocated, vma_commit_reservation is called
 * to add the page to the reservation map.  If the page allocation fails,
 * the reservation must be ended instead of committed.  vma_end_reservation
 * is called in such हालs.
 *
 * In the normal हाल, vma_commit_reservation वापसs the same value
 * as the preceding vma_needs_reservation call.  The only समय this
 * is not the हाल is अगर a reserve map was changed between calls.  It
 * is the responsibility of the caller to notice the dअगरference and
 * take appropriate action.
 *
 * vma_add_reservation is used in error paths where a reservation must
 * be restored when a newly allocated huge page must be मुक्तd.  It is
 * to be called after calling vma_needs_reservation to determine अगर a
 * reservation exists.
 *
 * vma_del_reservation is used in error paths where an entry in the reserve
 * map was created during huge page allocation and must be हटाओd.  It is to
 * be called after calling vma_needs_reservation to determine अगर a reservation
 * exists.
 */
क्रमागत vma_resv_mode अणु
	VMA_NEEDS_RESV,
	VMA_COMMIT_RESV,
	VMA_END_RESV,
	VMA_ADD_RESV,
	VMA_DEL_RESV,
पूर्ण;
अटल दीर्घ __vma_reservation_common(काष्ठा hstate *h,
				काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
				क्रमागत vma_resv_mode mode)
अणु
	काष्ठा resv_map *resv;
	pgoff_t idx;
	दीर्घ ret;
	दीर्घ dummy_out_regions_needed;

	resv = vma_resv_map(vma);
	अगर (!resv)
		वापस 1;

	idx = vma_hugecache_offset(h, vma, addr);
	चयन (mode) अणु
	हाल VMA_NEEDS_RESV:
		ret = region_chg(resv, idx, idx + 1, &dummy_out_regions_needed);
		/* We assume that vma_reservation_* routines always operate on
		 * 1 page, and that adding to resv map a 1 page entry can only
		 * ever require 1 region.
		 */
		VM_BUG_ON(dummy_out_regions_needed != 1);
		अवरोध;
	हाल VMA_COMMIT_RESV:
		ret = region_add(resv, idx, idx + 1, 1, शून्य, शून्य);
		/* region_add calls of range 1 should never fail. */
		VM_BUG_ON(ret < 0);
		अवरोध;
	हाल VMA_END_RESV:
		region_पात(resv, idx, idx + 1, 1);
		ret = 0;
		अवरोध;
	हाल VMA_ADD_RESV:
		अगर (vma->vm_flags & VM_MAYSHARE) अणु
			ret = region_add(resv, idx, idx + 1, 1, शून्य, शून्य);
			/* region_add calls of range 1 should never fail. */
			VM_BUG_ON(ret < 0);
		पूर्ण अन्यथा अणु
			region_पात(resv, idx, idx + 1, 1);
			ret = region_del(resv, idx, idx + 1);
		पूर्ण
		अवरोध;
	हाल VMA_DEL_RESV:
		अगर (vma->vm_flags & VM_MAYSHARE) अणु
			region_पात(resv, idx, idx + 1, 1);
			ret = region_del(resv, idx, idx + 1);
		पूर्ण अन्यथा अणु
			ret = region_add(resv, idx, idx + 1, 1, शून्य, शून्य);
			/* region_add calls of range 1 should never fail. */
			VM_BUG_ON(ret < 0);
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (vma->vm_flags & VM_MAYSHARE || mode == VMA_DEL_RESV)
		वापस ret;
	/*
	 * We know निजी mapping must have HPAGE_RESV_OWNER set.
	 *
	 * In most हालs, reserves always exist क्रम निजी mappings.
	 * However, a file associated with mapping could have been
	 * hole punched or truncated after reserves were consumed.
	 * As subsequent fault on such a range will not use reserves.
	 * Subtle - The reserve map क्रम निजी mappings has the
	 * opposite meaning than that of shared mappings.  If NO
	 * entry is in the reserve map, it means a reservation exists.
	 * If an entry exists in the reserve map, it means the
	 * reservation has alपढ़ोy been consumed.  As a result, the
	 * वापस value of this routine is the opposite of the
	 * value वापसed from reserve map manipulation routines above.
	 */
	अगर (ret > 0)
		वापस 0;
	अगर (ret == 0)
		वापस 1;
	वापस ret;
पूर्ण

अटल दीर्घ vma_needs_reservation(काष्ठा hstate *h,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	वापस __vma_reservation_common(h, vma, addr, VMA_NEEDS_RESV);
पूर्ण

अटल दीर्घ vma_commit_reservation(काष्ठा hstate *h,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	वापस __vma_reservation_common(h, vma, addr, VMA_COMMIT_RESV);
पूर्ण

अटल व्योम vma_end_reservation(काष्ठा hstate *h,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	(व्योम)__vma_reservation_common(h, vma, addr, VMA_END_RESV);
पूर्ण

अटल दीर्घ vma_add_reservation(काष्ठा hstate *h,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	वापस __vma_reservation_common(h, vma, addr, VMA_ADD_RESV);
पूर्ण

अटल दीर्घ vma_del_reservation(काष्ठा hstate *h,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	वापस __vma_reservation_common(h, vma, addr, VMA_DEL_RESV);
पूर्ण

/*
 * This routine is called to restore reservation inक्रमmation on error paths.
 * It should ONLY be called क्रम pages allocated via alloc_huge_page(), and
 * the hugetlb mutex should reमुख्य held when calling this routine.
 *
 * It handles two specअगरic हालs:
 * 1) A reservation was in place and the page consumed the reservation.
 *    HPageRestoreReserve is set in the page.
 * 2) No reservation was in place क्रम the page, so HPageRestoreReserve is
 *    not set.  However, alloc_huge_page always updates the reserve map.
 *
 * In हाल 1, मुक्त_huge_page later in the error path will increment the
 * global reserve count.  But, मुक्त_huge_page करोes not have enough context
 * to adjust the reservation map.  This हाल deals primarily with निजी
 * mappings.  Adjust the reserve map here to be consistent with global
 * reserve count adjusपंचांगents to be made by मुक्त_huge_page.  Make sure the
 * reserve map indicates there is a reservation present.
 *
 * In हाल 2, simply unकरो reserve map modअगरications करोne by alloc_huge_page.
 */
व्योम restore_reserve_on_error(काष्ठा hstate *h, काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ address, काष्ठा page *page)
अणु
	दीर्घ rc = vma_needs_reservation(h, vma, address);

	अगर (HPageRestoreReserve(page)) अणु
		अगर (unlikely(rc < 0))
			/*
			 * Rare out of memory condition in reserve map
			 * manipulation.  Clear HPageRestoreReserve so that
			 * global reserve count will not be incremented
			 * by मुक्त_huge_page.  This will make it appear
			 * as though the reservation क्रम this page was
			 * consumed.  This may prevent the task from
			 * faulting in the page at a later समय.  This
			 * is better than inconsistent global huge page
			 * accounting of reserve counts.
			 */
			ClearHPageRestoreReserve(page);
		अन्यथा अगर (rc)
			(व्योम)vma_add_reservation(h, vma, address);
		अन्यथा
			vma_end_reservation(h, vma, address);
	पूर्ण अन्यथा अणु
		अगर (!rc) अणु
			/*
			 * This indicates there is an entry in the reserve map
			 * added by alloc_huge_page.  We know it was added
			 * beक्रमe the alloc_huge_page call, otherwise
			 * HPageRestoreReserve would be set on the page.
			 * Remove the entry so that a subsequent allocation
			 * करोes not consume a reservation.
			 */
			rc = vma_del_reservation(h, vma, address);
			अगर (rc < 0)
				/*
				 * VERY rare out of memory condition.  Since
				 * we can not delete the entry, set
				 * HPageRestoreReserve so that the reserve
				 * count will be incremented when the page
				 * is मुक्तd.  This reserve will be consumed
				 * on a subsequent allocation.
				 */
				SetHPageRestoreReserve(page);
		पूर्ण अन्यथा अगर (rc < 0) अणु
			/*
			 * Rare out of memory condition from
			 * vma_needs_reservation call.  Memory allocation is
			 * only attempted अगर a new entry is needed.  Thereक्रमe,
			 * this implies there is not an entry in the
			 * reserve map.
			 *
			 * For shared mappings, no entry in the map indicates
			 * no reservation.  We are करोne.
			 */
			अगर (!(vma->vm_flags & VM_MAYSHARE))
				/*
				 * For निजी mappings, no entry indicates
				 * a reservation is present.  Since we can
				 * not add an entry, set SetHPageRestoreReserve
				 * on the page so reserve count will be
				 * incremented when मुक्तd.  This reserve will
				 * be consumed on a subsequent allocation.
				 */
				SetHPageRestoreReserve(page);
		पूर्ण अन्यथा
			/*
			 * No reservation present, करो nothing
			 */
			 vma_end_reservation(h, vma, address);
	पूर्ण
पूर्ण

/*
 * alloc_and_dissolve_huge_page - Allocate a new page and dissolve the old one
 * @h: काष्ठा hstate old page beदीर्घs to
 * @old_page: Old page to dissolve
 * @list: List to isolate the page in हाल we need to
 * Returns 0 on success, otherwise negated error.
 */
अटल पूर्णांक alloc_and_dissolve_huge_page(काष्ठा hstate *h, काष्ठा page *old_page,
					काष्ठा list_head *list)
अणु
	gfp_t gfp_mask = htlb_alloc_mask(h) | __GFP_THISNODE;
	पूर्णांक nid = page_to_nid(old_page);
	काष्ठा page *new_page;
	पूर्णांक ret = 0;

	/*
	 * Beक्रमe dissolving the page, we need to allocate a new one क्रम the
	 * pool to reमुख्य stable. Using alloc_buddy_huge_page() allows us to
	 * not having to deal with prep_new_huge_page() and aव्योमs dealing of any
	 * counters. This simplअगरies and let us करो the whole thing under the
	 * lock.
	 */
	new_page = alloc_buddy_huge_page(h, gfp_mask, nid, शून्य, शून्य);
	अगर (!new_page)
		वापस -ENOMEM;

retry:
	spin_lock_irq(&hugetlb_lock);
	अगर (!PageHuge(old_page)) अणु
		/*
		 * Freed from under us. Drop new_page too.
		 */
		जाओ मुक्त_new;
	पूर्ण अन्यथा अगर (page_count(old_page)) अणु
		/*
		 * Someone has grabbed the page, try to isolate it here.
		 * Fail with -EBUSY अगर not possible.
		 */
		spin_unlock_irq(&hugetlb_lock);
		अगर (!isolate_huge_page(old_page, list))
			ret = -EBUSY;
		spin_lock_irq(&hugetlb_lock);
		जाओ मुक्त_new;
	पूर्ण अन्यथा अगर (!HPageFreed(old_page)) अणु
		/*
		 * Page's refcount is 0 but it has not been enqueued in the
		 * मुक्तlist yet. Race winकरोw is small, so we can succeed here अगर
		 * we retry.
		 */
		spin_unlock_irq(&hugetlb_lock);
		cond_resched();
		जाओ retry;
	पूर्ण अन्यथा अणु
		/*
		 * Ok, old_page is still a genuine मुक्त hugepage. Remove it from
		 * the मुक्तlist and decrease the counters. These will be
		 * incremented again when calling __prep_account_new_huge_page()
		 * and enqueue_huge_page() क्रम new_page. The counters will reमुख्य
		 * stable since this happens under the lock.
		 */
		हटाओ_hugetlb_page(h, old_page, false);

		/*
		 * new_page needs to be initialized with the standard hugetlb
		 * state. This is normally करोne by prep_new_huge_page() but
		 * that takes hugetlb_lock which is alपढ़ोy held so we need to
		 * खोलो code it here.
		 * Reference count trick is needed because allocator gives us
		 * referenced page but the pool requires pages with 0 refcount.
		 */
		__prep_new_huge_page(new_page);
		__prep_account_new_huge_page(h, nid);
		page_ref_dec(new_page);
		enqueue_huge_page(h, new_page);

		/*
		 * Pages have been replaced, we can safely मुक्त the old one.
		 */
		spin_unlock_irq(&hugetlb_lock);
		update_and_मुक्त_page(h, old_page);
	पूर्ण

	वापस ret;

मुक्त_new:
	spin_unlock_irq(&hugetlb_lock);
	__मुक्त_pages(new_page, huge_page_order(h));

	वापस ret;
पूर्ण

पूर्णांक isolate_or_dissolve_huge_page(काष्ठा page *page, काष्ठा list_head *list)
अणु
	काष्ठा hstate *h;
	काष्ठा page *head;
	पूर्णांक ret = -EBUSY;

	/*
	 * The page might have been dissolved from under our feet, so make sure
	 * to carefully check the state under the lock.
	 * Return success when racing as अगर we dissolved the page ourselves.
	 */
	spin_lock_irq(&hugetlb_lock);
	अगर (PageHuge(page)) अणु
		head = compound_head(page);
		h = page_hstate(head);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&hugetlb_lock);
		वापस 0;
	पूर्ण
	spin_unlock_irq(&hugetlb_lock);

	/*
	 * Fence off gigantic pages as there is a cyclic dependency between
	 * alloc_contig_range and them. Return -ENOMEM as this has the effect
	 * of bailing out right away without further retrying.
	 */
	अगर (hstate_is_gigantic(h))
		वापस -ENOMEM;

	अगर (page_count(head) && isolate_huge_page(head, list))
		ret = 0;
	अन्यथा अगर (!page_count(head))
		ret = alloc_and_dissolve_huge_page(h, head, list);

	वापस ret;
पूर्ण

काष्ठा page *alloc_huge_page(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ addr, पूर्णांक aव्योम_reserve)
अणु
	काष्ठा hugepage_subpool *spool = subpool_vma(vma);
	काष्ठा hstate *h = hstate_vma(vma);
	काष्ठा page *page;
	दीर्घ map_chg, map_commit;
	दीर्घ gbl_chg;
	पूर्णांक ret, idx;
	काष्ठा hugetlb_cgroup *h_cg;
	bool deferred_reserve;

	idx = hstate_index(h);
	/*
	 * Examine the region/reserve map to determine अगर the process
	 * has a reservation क्रम the page to be allocated.  A वापस
	 * code of zero indicates a reservation exists (no change).
	 */
	map_chg = gbl_chg = vma_needs_reservation(h, vma, addr);
	अगर (map_chg < 0)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * Processes that did not create the mapping will have no
	 * reserves as indicated by the region/reserve map. Check
	 * that the allocation will not exceed the subpool limit.
	 * Allocations क्रम MAP_NORESERVE mappings also need to be
	 * checked against any subpool limit.
	 */
	अगर (map_chg || aव्योम_reserve) अणु
		gbl_chg = hugepage_subpool_get_pages(spool, 1);
		अगर (gbl_chg < 0) अणु
			vma_end_reservation(h, vma, addr);
			वापस ERR_PTR(-ENOSPC);
		पूर्ण

		/*
		 * Even though there was no reservation in the region/reserve
		 * map, there could be reservations associated with the
		 * subpool that can be used.  This would be indicated अगर the
		 * वापस value of hugepage_subpool_get_pages() is zero.
		 * However, अगर aव्योम_reserve is specअगरied we still aव्योम even
		 * the subpool reservations.
		 */
		अगर (aव्योम_reserve)
			gbl_chg = 1;
	पूर्ण

	/* If this allocation is not consuming a reservation, अक्षरge it now.
	 */
	deferred_reserve = map_chg || aव्योम_reserve;
	अगर (deferred_reserve) अणु
		ret = hugetlb_cgroup_अक्षरge_cgroup_rsvd(
			idx, pages_per_huge_page(h), &h_cg);
		अगर (ret)
			जाओ out_subpool_put;
	पूर्ण

	ret = hugetlb_cgroup_अक्षरge_cgroup(idx, pages_per_huge_page(h), &h_cg);
	अगर (ret)
		जाओ out_unअक्षरge_cgroup_reservation;

	spin_lock_irq(&hugetlb_lock);
	/*
	 * glb_chg is passed to indicate whether or not a page must be taken
	 * from the global मुक्त pool (global change).  gbl_chg == 0 indicates
	 * a reservation exists क्रम the allocation.
	 */
	page = dequeue_huge_page_vma(h, vma, addr, aव्योम_reserve, gbl_chg);
	अगर (!page) अणु
		spin_unlock_irq(&hugetlb_lock);
		page = alloc_buddy_huge_page_with_mpol(h, vma, addr);
		अगर (!page)
			जाओ out_unअक्षरge_cgroup;
		अगर (!aव्योम_reserve && vma_has_reserves(vma, gbl_chg)) अणु
			SetHPageRestoreReserve(page);
			h->resv_huge_pages--;
		पूर्ण
		spin_lock_irq(&hugetlb_lock);
		list_add(&page->lru, &h->hugepage_activelist);
		/* Fall through */
	पूर्ण
	hugetlb_cgroup_commit_अक्षरge(idx, pages_per_huge_page(h), h_cg, page);
	/* If allocation is not consuming a reservation, also store the
	 * hugetlb_cgroup poपूर्णांकer on the page.
	 */
	अगर (deferred_reserve) अणु
		hugetlb_cgroup_commit_अक्षरge_rsvd(idx, pages_per_huge_page(h),
						  h_cg, page);
	पूर्ण

	spin_unlock_irq(&hugetlb_lock);

	hugetlb_set_page_subpool(page, spool);

	map_commit = vma_commit_reservation(h, vma, addr);
	अगर (unlikely(map_chg > map_commit)) अणु
		/*
		 * The page was added to the reservation map between
		 * vma_needs_reservation and vma_commit_reservation.
		 * This indicates a race with hugetlb_reserve_pages.
		 * Adjust क्रम the subpool count incremented above AND
		 * in hugetlb_reserve_pages क्रम the same page.  Also,
		 * the reservation count added in hugetlb_reserve_pages
		 * no दीर्घer applies.
		 */
		दीर्घ rsv_adjust;

		rsv_adjust = hugepage_subpool_put_pages(spool, 1);
		hugetlb_acct_memory(h, -rsv_adjust);
		अगर (deferred_reserve)
			hugetlb_cgroup_unअक्षरge_page_rsvd(hstate_index(h),
					pages_per_huge_page(h), page);
	पूर्ण
	वापस page;

out_unअक्षरge_cgroup:
	hugetlb_cgroup_unअक्षरge_cgroup(idx, pages_per_huge_page(h), h_cg);
out_unअक्षरge_cgroup_reservation:
	अगर (deferred_reserve)
		hugetlb_cgroup_unअक्षरge_cgroup_rsvd(idx, pages_per_huge_page(h),
						    h_cg);
out_subpool_put:
	अगर (map_chg || aव्योम_reserve)
		hugepage_subpool_put_pages(spool, 1);
	vma_end_reservation(h, vma, addr);
	वापस ERR_PTR(-ENOSPC);
पूर्ण

पूर्णांक alloc_booपंचांगem_huge_page(काष्ठा hstate *h)
	__attribute__ ((weak, alias("__alloc_bootmem_huge_page")));
पूर्णांक __alloc_booपंचांगem_huge_page(काष्ठा hstate *h)
अणु
	काष्ठा huge_booपंचांगem_page *m;
	पूर्णांक nr_nodes, node;

	क्रम_each_node_mask_to_alloc(h, nr_nodes, node, &node_states[N_MEMORY]) अणु
		व्योम *addr;

		addr = memblock_alloc_try_nid_raw(
				huge_page_size(h), huge_page_size(h),
				0, MEMBLOCK_ALLOC_ACCESSIBLE, node);
		अगर (addr) अणु
			/*
			 * Use the beginning of the huge page to store the
			 * huge_booपंचांगem_page काष्ठा (until gather_booपंचांगem
			 * माला_दो them पूर्णांकo the mem_map).
			 */
			m = addr;
			जाओ found;
		पूर्ण
	पूर्ण
	वापस 0;

found:
	BUG_ON(!IS_ALIGNED(virt_to_phys(m), huge_page_size(h)));
	/* Put them पूर्णांकo a निजी list first because mem_map is not up yet */
	INIT_LIST_HEAD(&m->list);
	list_add(&m->list, &huge_boot_pages);
	m->hstate = h;
	वापस 1;
पूर्ण

अटल व्योम __init prep_compound_huge_page(काष्ठा page *page,
		अचिन्हित पूर्णांक order)
अणु
	अगर (unlikely(order > (MAX_ORDER - 1)))
		prep_compound_gigantic_page(page, order);
	अन्यथा
		prep_compound_page(page, order);
पूर्ण

/* Put booपंचांगem huge pages पूर्णांकo the standard lists after mem_map is up */
अटल व्योम __init gather_booपंचांगem_pपुनः_स्मृति(व्योम)
अणु
	काष्ठा huge_booपंचांगem_page *m;

	list_क्रम_each_entry(m, &huge_boot_pages, list) अणु
		काष्ठा page *page = virt_to_page(m);
		काष्ठा hstate *h = m->hstate;

		WARN_ON(page_count(page) != 1);
		prep_compound_huge_page(page, huge_page_order(h));
		WARN_ON(PageReserved(page));
		prep_new_huge_page(h, page, page_to_nid(page));
		put_page(page); /* मुक्त it पूर्णांकo the hugepage allocator */

		/*
		 * If we had gigantic hugepages allocated at boot समय, we need
		 * to restore the 'stolen' pages to totalram_pages in order to
		 * fix confusing memory reports from मुक्त(1) and another
		 * side-effects, like CommitLimit going negative.
		 */
		अगर (hstate_is_gigantic(h))
			adjust_managed_page_count(page, pages_per_huge_page(h));
		cond_resched();
	पूर्ण
पूर्ण

अटल व्योम __init hugetlb_hstate_alloc_pages(काष्ठा hstate *h)
अणु
	अचिन्हित दीर्घ i;
	nodemask_t *node_alloc_noretry;

	अगर (!hstate_is_gigantic(h)) अणु
		/*
		 * Bit mask controlling how hard we retry per-node allocations.
		 * Ignore errors as lower level routines can deal with
		 * node_alloc_noretry == शून्य.  If this kदो_स्मृति fails at boot
		 * समय, we are likely in bigger trouble.
		 */
		node_alloc_noretry = kदो_स्मृति(माप(*node_alloc_noretry),
						GFP_KERNEL);
	पूर्ण अन्यथा अणु
		/* allocations करोne at boot समय */
		node_alloc_noretry = शून्य;
	पूर्ण

	/* bit mask controlling how hard we retry per-node allocations */
	अगर (node_alloc_noretry)
		nodes_clear(*node_alloc_noretry);

	क्रम (i = 0; i < h->max_huge_pages; ++i) अणु
		अगर (hstate_is_gigantic(h)) अणु
			अगर (hugetlb_cma_size) अणु
				pr_warn_once("HugeTLB: hugetlb_cma is enabled, skip boot time allocation\n");
				जाओ मुक्त;
			पूर्ण
			अगर (!alloc_booपंचांगem_huge_page(h))
				अवरोध;
		पूर्ण अन्यथा अगर (!alloc_pool_huge_page(h,
					 &node_states[N_MEMORY],
					 node_alloc_noretry))
			अवरोध;
		cond_resched();
	पूर्ण
	अगर (i < h->max_huge_pages) अणु
		अक्षर buf[32];

		string_get_size(huge_page_size(h), 1, STRING_UNITS_2, buf, 32);
		pr_warn("HugeTLB: allocating %lu of page size %s failed.  Only allocated %lu hugepages.\n",
			h->max_huge_pages, buf, i);
		h->max_huge_pages = i;
	पूर्ण
मुक्त:
	kमुक्त(node_alloc_noretry);
पूर्ण

अटल व्योम __init hugetlb_init_hstates(व्योम)
अणु
	काष्ठा hstate *h;

	क्रम_each_hstate(h) अणु
		अगर (minimum_order > huge_page_order(h))
			minimum_order = huge_page_order(h);

		/* oversize hugepages were init'ed in early boot */
		अगर (!hstate_is_gigantic(h))
			hugetlb_hstate_alloc_pages(h);
	पूर्ण
	VM_BUG_ON(minimum_order == अच_पूर्णांक_उच्च);
पूर्ण

अटल व्योम __init report_hugepages(व्योम)
अणु
	काष्ठा hstate *h;

	क्रम_each_hstate(h) अणु
		अक्षर buf[32];

		string_get_size(huge_page_size(h), 1, STRING_UNITS_2, buf, 32);
		pr_info("HugeTLB registered %s page size, pre-allocated %ld pages\n",
			buf, h->मुक्त_huge_pages);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
अटल व्योम try_to_मुक्त_low(काष्ठा hstate *h, अचिन्हित दीर्घ count,
						nodemask_t *nodes_allowed)
अणु
	पूर्णांक i;
	LIST_HEAD(page_list);

	lockdep_निश्चित_held(&hugetlb_lock);
	अगर (hstate_is_gigantic(h))
		वापस;

	/*
	 * Collect pages to be मुक्तd on a list, and मुक्त after dropping lock
	 */
	क्रम_each_node_mask(i, *nodes_allowed) अणु
		काष्ठा page *page, *next;
		काष्ठा list_head *मुक्तl = &h->hugepage_मुक्तlists[i];
		list_क्रम_each_entry_safe(page, next, मुक्तl, lru) अणु
			अगर (count >= h->nr_huge_pages)
				जाओ out;
			अगर (PageHighMem(page))
				जारी;
			हटाओ_hugetlb_page(h, page, false);
			list_add(&page->lru, &page_list);
		पूर्ण
	पूर्ण

out:
	spin_unlock_irq(&hugetlb_lock);
	update_and_मुक्त_pages_bulk(h, &page_list);
	spin_lock_irq(&hugetlb_lock);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम try_to_मुक्त_low(काष्ठा hstate *h, अचिन्हित दीर्घ count,
						nodemask_t *nodes_allowed)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Increment or decrement surplus_huge_pages.  Keep node-specअगरic counters
 * balanced by operating on them in a round-robin fashion.
 * Returns 1 अगर an adjusपंचांगent was made.
 */
अटल पूर्णांक adjust_pool_surplus(काष्ठा hstate *h, nodemask_t *nodes_allowed,
				पूर्णांक delta)
अणु
	पूर्णांक nr_nodes, node;

	lockdep_निश्चित_held(&hugetlb_lock);
	VM_BUG_ON(delta != -1 && delta != 1);

	अगर (delta < 0) अणु
		क्रम_each_node_mask_to_alloc(h, nr_nodes, node, nodes_allowed) अणु
			अगर (h->surplus_huge_pages_node[node])
				जाओ found;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_node_mask_to_मुक्त(h, nr_nodes, node, nodes_allowed) अणु
			अगर (h->surplus_huge_pages_node[node] <
					h->nr_huge_pages_node[node])
				जाओ found;
		पूर्ण
	पूर्ण
	वापस 0;

found:
	h->surplus_huge_pages += delta;
	h->surplus_huge_pages_node[node] += delta;
	वापस 1;
पूर्ण

#घोषणा persistent_huge_pages(h) (h->nr_huge_pages - h->surplus_huge_pages)
अटल पूर्णांक set_max_huge_pages(काष्ठा hstate *h, अचिन्हित दीर्घ count, पूर्णांक nid,
			      nodemask_t *nodes_allowed)
अणु
	अचिन्हित दीर्घ min_count, ret;
	काष्ठा page *page;
	LIST_HEAD(page_list);
	NODEMASK_ALLOC(nodemask_t, node_alloc_noretry, GFP_KERNEL);

	/*
	 * Bit mask controlling how hard we retry per-node allocations.
	 * If we can not allocate the bit mask, करो not attempt to allocate
	 * the requested huge pages.
	 */
	अगर (node_alloc_noretry)
		nodes_clear(*node_alloc_noretry);
	अन्यथा
		वापस -ENOMEM;

	/*
	 * resize_lock mutex prevents concurrent adjusपंचांगents to number of
	 * pages in hstate via the proc/sysfs पूर्णांकerfaces.
	 */
	mutex_lock(&h->resize_lock);
	spin_lock_irq(&hugetlb_lock);

	/*
	 * Check क्रम a node specअगरic request.
	 * Changing node specअगरic huge page count may require a corresponding
	 * change to the global count.  In any हाल, the passed node mask
	 * (nodes_allowed) will restrict alloc/मुक्त to the specअगरied node.
	 */
	अगर (nid != NUMA_NO_NODE) अणु
		अचिन्हित दीर्घ old_count = count;

		count += h->nr_huge_pages - h->nr_huge_pages_node[nid];
		/*
		 * User may have specअगरied a large count value which caused the
		 * above calculation to overflow.  In this हाल, they wanted
		 * to allocate as many huge pages as possible.  Set count to
		 * largest possible value to align with their पूर्णांकention.
		 */
		अगर (count < old_count)
			count = अच_दीर्घ_उच्च;
	पूर्ण

	/*
	 * Gigantic pages runसमय allocation depend on the capability क्रम large
	 * page range allocation.
	 * If the प्रणाली करोes not provide this feature, वापस an error when
	 * the user tries to allocate gigantic pages but let the user मुक्त the
	 * bootसमय allocated gigantic pages.
	 */
	अगर (hstate_is_gigantic(h) && !IS_ENABLED(CONFIG_CONTIG_ALLOC)) अणु
		अगर (count > persistent_huge_pages(h)) अणु
			spin_unlock_irq(&hugetlb_lock);
			mutex_unlock(&h->resize_lock);
			NODEMASK_FREE(node_alloc_noretry);
			वापस -EINVAL;
		पूर्ण
		/* Fall through to decrease pool */
	पूर्ण

	/*
	 * Increase the pool size
	 * First take pages out of surplus state.  Then make up the
	 * reमुख्यing dअगरference by allocating fresh huge pages.
	 *
	 * We might race with alloc_surplus_huge_page() here and be unable
	 * to convert a surplus huge page to a normal huge page. That is
	 * not critical, though, it just means the overall size of the
	 * pool might be one hugepage larger than it needs to be, but
	 * within all the स्थिरraपूर्णांकs specअगरied by the sysctls.
	 */
	जबतक (h->surplus_huge_pages && count > persistent_huge_pages(h)) अणु
		अगर (!adjust_pool_surplus(h, nodes_allowed, -1))
			अवरोध;
	पूर्ण

	जबतक (count > persistent_huge_pages(h)) अणु
		/*
		 * If this allocation races such that we no दीर्घer need the
		 * page, मुक्त_huge_page will handle it by मुक्तing the page
		 * and reducing the surplus.
		 */
		spin_unlock_irq(&hugetlb_lock);

		/* yield cpu to aव्योम soft lockup */
		cond_resched();

		ret = alloc_pool_huge_page(h, nodes_allowed,
						node_alloc_noretry);
		spin_lock_irq(&hugetlb_lock);
		अगर (!ret)
			जाओ out;

		/* Bail क्रम संकेतs. Probably ctrl-c from user */
		अगर (संकेत_pending(current))
			जाओ out;
	पूर्ण

	/*
	 * Decrease the pool size
	 * First वापस मुक्त pages to the buddy allocator (being careful
	 * to keep enough around to satisfy reservations).  Then place
	 * pages पूर्णांकo surplus state as needed so the pool will shrink
	 * to the desired size as pages become मुक्त.
	 *
	 * By placing pages पूर्णांकo the surplus state independent of the
	 * overcommit value, we are allowing the surplus pool size to
	 * exceed overcommit. There are few sane options here. Since
	 * alloc_surplus_huge_page() is checking the global counter,
	 * though, we'll note that we're not allowed to exceed surplus
	 * and won't grow the pool anywhere अन्यथा. Not until one of the
	 * sysctls are changed, or the surplus pages go out of use.
	 */
	min_count = h->resv_huge_pages + h->nr_huge_pages - h->मुक्त_huge_pages;
	min_count = max(count, min_count);
	try_to_मुक्त_low(h, min_count, nodes_allowed);

	/*
	 * Collect pages to be हटाओd on list without dropping lock
	 */
	जबतक (min_count < persistent_huge_pages(h)) अणु
		page = हटाओ_pool_huge_page(h, nodes_allowed, 0);
		अगर (!page)
			अवरोध;

		list_add(&page->lru, &page_list);
	पूर्ण
	/* मुक्त the pages after dropping lock */
	spin_unlock_irq(&hugetlb_lock);
	update_and_मुक्त_pages_bulk(h, &page_list);
	spin_lock_irq(&hugetlb_lock);

	जबतक (count < persistent_huge_pages(h)) अणु
		अगर (!adjust_pool_surplus(h, nodes_allowed, 1))
			अवरोध;
	पूर्ण
out:
	h->max_huge_pages = persistent_huge_pages(h);
	spin_unlock_irq(&hugetlb_lock);
	mutex_unlock(&h->resize_lock);

	NODEMASK_FREE(node_alloc_noretry);

	वापस 0;
पूर्ण

#घोषणा HSTATE_ATTR_RO(_name) \
	अटल काष्ठा kobj_attribute _name##_attr = __ATTR_RO(_name)

#घोषणा HSTATE_ATTR(_name) \
	अटल काष्ठा kobj_attribute _name##_attr = \
		__ATTR(_name, 0644, _name##_show, _name##_store)

अटल काष्ठा kobject *hugepages_kobj;
अटल काष्ठा kobject *hstate_kobjs[HUGE_MAX_HSTATE];

अटल काष्ठा hstate *kobj_to_node_hstate(काष्ठा kobject *kobj, पूर्णांक *nidp);

अटल काष्ठा hstate *kobj_to_hstate(काष्ठा kobject *kobj, पूर्णांक *nidp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HUGE_MAX_HSTATE; i++)
		अगर (hstate_kobjs[i] == kobj) अणु
			अगर (nidp)
				*nidp = NUMA_NO_NODE;
			वापस &hstates[i];
		पूर्ण

	वापस kobj_to_node_hstate(kobj, nidp);
पूर्ण

अटल sमाप_प्रकार nr_hugepages_show_common(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hstate *h;
	अचिन्हित दीर्घ nr_huge_pages;
	पूर्णांक nid;

	h = kobj_to_hstate(kobj, &nid);
	अगर (nid == NUMA_NO_NODE)
		nr_huge_pages = h->nr_huge_pages;
	अन्यथा
		nr_huge_pages = h->nr_huge_pages_node[nid];

	वापस sysfs_emit(buf, "%lu\n", nr_huge_pages);
पूर्ण

अटल sमाप_प्रकार __nr_hugepages_store_common(bool obey_mempolicy,
					   काष्ठा hstate *h, पूर्णांक nid,
					   अचिन्हित दीर्घ count, माप_प्रकार len)
अणु
	पूर्णांक err;
	nodemask_t nodes_allowed, *n_mask;

	अगर (hstate_is_gigantic(h) && !gigantic_page_runसमय_supported())
		वापस -EINVAL;

	अगर (nid == NUMA_NO_NODE) अणु
		/*
		 * global hstate attribute
		 */
		अगर (!(obey_mempolicy &&
				init_nodemask_of_mempolicy(&nodes_allowed)))
			n_mask = &node_states[N_MEMORY];
		अन्यथा
			n_mask = &nodes_allowed;
	पूर्ण अन्यथा अणु
		/*
		 * Node specअगरic request.  count adjusपंचांगent happens in
		 * set_max_huge_pages() after acquiring hugetlb_lock.
		 */
		init_nodemask_of_node(&nodes_allowed, nid);
		n_mask = &nodes_allowed;
	पूर्ण

	err = set_max_huge_pages(h, count, nid, n_mask);

	वापस err ? err : len;
पूर्ण

अटल sमाप_प्रकार nr_hugepages_store_common(bool obey_mempolicy,
					 काष्ठा kobject *kobj, स्थिर अक्षर *buf,
					 माप_प्रकार len)
अणु
	काष्ठा hstate *h;
	अचिन्हित दीर्घ count;
	पूर्णांक nid;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &count);
	अगर (err)
		वापस err;

	h = kobj_to_hstate(kobj, &nid);
	वापस __nr_hugepages_store_common(obey_mempolicy, h, nid, count, len);
पूर्ण

अटल sमाप_प्रकार nr_hugepages_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस nr_hugepages_show_common(kobj, attr, buf);
पूर्ण

अटल sमाप_प्रकार nr_hugepages_store(काष्ठा kobject *kobj,
	       काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस nr_hugepages_store_common(false, kobj, buf, len);
पूर्ण
HSTATE_ATTR(nr_hugepages);

#अगर_घोषित CONFIG_NUMA

/*
 * hstate attribute क्रम optionally mempolicy-based स्थिरraपूर्णांक on persistent
 * huge page alloc/मुक्त.
 */
अटल sमाप_प्रकार nr_hugepages_mempolicy_show(काष्ठा kobject *kobj,
					   काष्ठा kobj_attribute *attr,
					   अक्षर *buf)
अणु
	वापस nr_hugepages_show_common(kobj, attr, buf);
पूर्ण

अटल sमाप_प्रकार nr_hugepages_mempolicy_store(काष्ठा kobject *kobj,
	       काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	वापस nr_hugepages_store_common(true, kobj, buf, len);
पूर्ण
HSTATE_ATTR(nr_hugepages_mempolicy);
#पूर्ण_अगर


अटल sमाप_प्रकार nr_overcommit_hugepages_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hstate *h = kobj_to_hstate(kobj, शून्य);
	वापस sysfs_emit(buf, "%lu\n", h->nr_overcommit_huge_pages);
पूर्ण

अटल sमाप_प्रकार nr_overcommit_hugepages_store(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ input;
	काष्ठा hstate *h = kobj_to_hstate(kobj, शून्य);

	अगर (hstate_is_gigantic(h))
		वापस -EINVAL;

	err = kम_से_अदीर्घ(buf, 10, &input);
	अगर (err)
		वापस err;

	spin_lock_irq(&hugetlb_lock);
	h->nr_overcommit_huge_pages = input;
	spin_unlock_irq(&hugetlb_lock);

	वापस count;
पूर्ण
HSTATE_ATTR(nr_overcommit_hugepages);

अटल sमाप_प्रकार मुक्त_hugepages_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hstate *h;
	अचिन्हित दीर्घ मुक्त_huge_pages;
	पूर्णांक nid;

	h = kobj_to_hstate(kobj, &nid);
	अगर (nid == NUMA_NO_NODE)
		मुक्त_huge_pages = h->मुक्त_huge_pages;
	अन्यथा
		मुक्त_huge_pages = h->मुक्त_huge_pages_node[nid];

	वापस sysfs_emit(buf, "%lu\n", मुक्त_huge_pages);
पूर्ण
HSTATE_ATTR_RO(मुक्त_hugepages);

अटल sमाप_प्रकार resv_hugepages_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hstate *h = kobj_to_hstate(kobj, शून्य);
	वापस sysfs_emit(buf, "%lu\n", h->resv_huge_pages);
पूर्ण
HSTATE_ATTR_RO(resv_hugepages);

अटल sमाप_प्रकार surplus_hugepages_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hstate *h;
	अचिन्हित दीर्घ surplus_huge_pages;
	पूर्णांक nid;

	h = kobj_to_hstate(kobj, &nid);
	अगर (nid == NUMA_NO_NODE)
		surplus_huge_pages = h->surplus_huge_pages;
	अन्यथा
		surplus_huge_pages = h->surplus_huge_pages_node[nid];

	वापस sysfs_emit(buf, "%lu\n", surplus_huge_pages);
पूर्ण
HSTATE_ATTR_RO(surplus_hugepages);

अटल काष्ठा attribute *hstate_attrs[] = अणु
	&nr_hugepages_attr.attr,
	&nr_overcommit_hugepages_attr.attr,
	&मुक्त_hugepages_attr.attr,
	&resv_hugepages_attr.attr,
	&surplus_hugepages_attr.attr,
#अगर_घोषित CONFIG_NUMA
	&nr_hugepages_mempolicy_attr.attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hstate_attr_group = अणु
	.attrs = hstate_attrs,
पूर्ण;

अटल पूर्णांक hugetlb_sysfs_add_hstate(काष्ठा hstate *h, काष्ठा kobject *parent,
				    काष्ठा kobject **hstate_kobjs,
				    स्थिर काष्ठा attribute_group *hstate_attr_group)
अणु
	पूर्णांक retval;
	पूर्णांक hi = hstate_index(h);

	hstate_kobjs[hi] = kobject_create_and_add(h->name, parent);
	अगर (!hstate_kobjs[hi])
		वापस -ENOMEM;

	retval = sysfs_create_group(hstate_kobjs[hi], hstate_attr_group);
	अगर (retval) अणु
		kobject_put(hstate_kobjs[hi]);
		hstate_kobjs[hi] = शून्य;
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम __init hugetlb_sysfs_init(व्योम)
अणु
	काष्ठा hstate *h;
	पूर्णांक err;

	hugepages_kobj = kobject_create_and_add("hugepages", mm_kobj);
	अगर (!hugepages_kobj)
		वापस;

	क्रम_each_hstate(h) अणु
		err = hugetlb_sysfs_add_hstate(h, hugepages_kobj,
					 hstate_kobjs, &hstate_attr_group);
		अगर (err)
			pr_err("HugeTLB: Unable to add hstate %s", h->name);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_NUMA

/*
 * node_hstate/s - associate per node hstate attributes, via their kobjects,
 * with node devices in node_devices[] using a parallel array.  The array
 * index of a node device or _hstate == node id.
 * This is here to aव्योम any अटल dependency of the node device driver, in
 * the base kernel, on the hugetlb module.
 */
काष्ठा node_hstate अणु
	काष्ठा kobject		*hugepages_kobj;
	काष्ठा kobject		*hstate_kobjs[HUGE_MAX_HSTATE];
पूर्ण;
अटल काष्ठा node_hstate node_hstates[MAX_NUMNODES];

/*
 * A subset of global hstate attributes क्रम node devices
 */
अटल काष्ठा attribute *per_node_hstate_attrs[] = अणु
	&nr_hugepages_attr.attr,
	&मुक्त_hugepages_attr.attr,
	&surplus_hugepages_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group per_node_hstate_attr_group = अणु
	.attrs = per_node_hstate_attrs,
पूर्ण;

/*
 * kobj_to_node_hstate - lookup global hstate क्रम node device hstate attr kobj.
 * Returns node id via non-शून्य nidp.
 */
अटल काष्ठा hstate *kobj_to_node_hstate(काष्ठा kobject *kobj, पूर्णांक *nidp)
अणु
	पूर्णांक nid;

	क्रम (nid = 0; nid < nr_node_ids; nid++) अणु
		काष्ठा node_hstate *nhs = &node_hstates[nid];
		पूर्णांक i;
		क्रम (i = 0; i < HUGE_MAX_HSTATE; i++)
			अगर (nhs->hstate_kobjs[i] == kobj) अणु
				अगर (nidp)
					*nidp = nid;
				वापस &hstates[i];
			पूर्ण
	पूर्ण

	BUG();
	वापस शून्य;
पूर्ण

/*
 * Unरेजिस्टर hstate attributes from a single node device.
 * No-op अगर no hstate attributes attached.
 */
अटल व्योम hugetlb_unरेजिस्टर_node(काष्ठा node *node)
अणु
	काष्ठा hstate *h;
	काष्ठा node_hstate *nhs = &node_hstates[node->dev.id];

	अगर (!nhs->hugepages_kobj)
		वापस;		/* no hstate attributes */

	क्रम_each_hstate(h) अणु
		पूर्णांक idx = hstate_index(h);
		अगर (nhs->hstate_kobjs[idx]) अणु
			kobject_put(nhs->hstate_kobjs[idx]);
			nhs->hstate_kobjs[idx] = शून्य;
		पूर्ण
	पूर्ण

	kobject_put(nhs->hugepages_kobj);
	nhs->hugepages_kobj = शून्य;
पूर्ण


/*
 * Register hstate attributes क्रम a single node device.
 * No-op अगर attributes alपढ़ोy रेजिस्टरed.
 */
अटल व्योम hugetlb_रेजिस्टर_node(काष्ठा node *node)
अणु
	काष्ठा hstate *h;
	काष्ठा node_hstate *nhs = &node_hstates[node->dev.id];
	पूर्णांक err;

	अगर (nhs->hugepages_kobj)
		वापस;		/* alपढ़ोy allocated */

	nhs->hugepages_kobj = kobject_create_and_add("hugepages",
							&node->dev.kobj);
	अगर (!nhs->hugepages_kobj)
		वापस;

	क्रम_each_hstate(h) अणु
		err = hugetlb_sysfs_add_hstate(h, nhs->hugepages_kobj,
						nhs->hstate_kobjs,
						&per_node_hstate_attr_group);
		अगर (err) अणु
			pr_err("HugeTLB: Unable to add hstate %s for node %d\n",
				h->name, node->dev.id);
			hugetlb_unरेजिस्टर_node(node);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * hugetlb init समय:  रेजिस्टर hstate attributes क्रम all रेजिस्टरed node
 * devices of nodes that have memory.  All on-line nodes should have
 * रेजिस्टरed their associated device by this समय.
 */
अटल व्योम __init hugetlb_रेजिस्टर_all_nodes(व्योम)
अणु
	पूर्णांक nid;

	क्रम_each_node_state(nid, N_MEMORY) अणु
		काष्ठा node *node = node_devices[nid];
		अगर (node->dev.id == nid)
			hugetlb_रेजिस्टर_node(node);
	पूर्ण

	/*
	 * Let the node device driver know we're here so it can
	 * [un]रेजिस्टर hstate attributes on node hotplug.
	 */
	रेजिस्टर_hugetlbfs_with_node(hugetlb_रेजिस्टर_node,
				     hugetlb_unरेजिस्टर_node);
पूर्ण
#अन्यथा	/* !CONFIG_NUMA */

अटल काष्ठा hstate *kobj_to_node_hstate(काष्ठा kobject *kobj, पूर्णांक *nidp)
अणु
	BUG();
	अगर (nidp)
		*nidp = -1;
	वापस शून्य;
पूर्ण

अटल व्योम hugetlb_रेजिस्टर_all_nodes(व्योम) अणु पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __init hugetlb_init(व्योम)
अणु
	पूर्णांक i;

	BUILD_BUG_ON(माप_field(काष्ठा page, निजी) * BITS_PER_BYTE <
			__NR_HPAGEFLAGS);

	अगर (!hugepages_supported()) अणु
		अगर (hugetlb_max_hstate || शेष_hstate_max_huge_pages)
			pr_warn("HugeTLB: huge pages not supported, ignoring associated command-line parameters\n");
		वापस 0;
	पूर्ण

	/*
	 * Make sure HPAGE_SIZE (HUGETLB_PAGE_ORDER) hstate exists.  Some
	 * architectures depend on setup being करोne here.
	 */
	hugetlb_add_hstate(HUGETLB_PAGE_ORDER);
	अगर (!parsed_शेष_hugepagesz) अणु
		/*
		 * If we did not parse a शेष huge page size, set
		 * शेष_hstate_idx to HPAGE_SIZE hstate. And, अगर the
		 * number of huge pages क्रम this शेष size was implicitly
		 * specअगरied, set that here as well.
		 * Note that the implicit setting will overग_लिखो an explicit
		 * setting.  A warning will be prपूर्णांकed in this हाल.
		 */
		शेष_hstate_idx = hstate_index(माप_प्रकारo_hstate(HPAGE_SIZE));
		अगर (शेष_hstate_max_huge_pages) अणु
			अगर (शेष_hstate.max_huge_pages) अणु
				अक्षर buf[32];

				string_get_size(huge_page_size(&शेष_hstate),
					1, STRING_UNITS_2, buf, 32);
				pr_warn("HugeTLB: Ignoring hugepages=%lu associated with %s page size\n",
					शेष_hstate.max_huge_pages, buf);
				pr_warn("HugeTLB: Using hugepages=%lu for number of default huge pages\n",
					शेष_hstate_max_huge_pages);
			पूर्ण
			शेष_hstate.max_huge_pages =
				शेष_hstate_max_huge_pages;
		पूर्ण
	पूर्ण

	hugetlb_cma_check();
	hugetlb_init_hstates();
	gather_booपंचांगem_pपुनः_स्मृति();
	report_hugepages();

	hugetlb_sysfs_init();
	hugetlb_रेजिस्टर_all_nodes();
	hugetlb_cgroup_file_init();

#अगर_घोषित CONFIG_SMP
	num_fault_mutexes = roundup_घात_of_two(8 * num_possible_cpus());
#अन्यथा
	num_fault_mutexes = 1;
#पूर्ण_अगर
	hugetlb_fault_mutex_table =
		kदो_स्मृति_array(num_fault_mutexes, माप(काष्ठा mutex),
			      GFP_KERNEL);
	BUG_ON(!hugetlb_fault_mutex_table);

	क्रम (i = 0; i < num_fault_mutexes; i++)
		mutex_init(&hugetlb_fault_mutex_table[i]);
	वापस 0;
पूर्ण
subsys_initcall(hugetlb_init);

/* Overwritten by architectures with more huge page sizes */
bool __init __attribute((weak)) arch_hugetlb_valid_size(अचिन्हित दीर्घ size)
अणु
	वापस size == HPAGE_SIZE;
पूर्ण

व्योम __init hugetlb_add_hstate(अचिन्हित पूर्णांक order)
अणु
	काष्ठा hstate *h;
	अचिन्हित दीर्घ i;

	अगर (माप_प्रकारo_hstate(PAGE_SIZE << order)) अणु
		वापस;
	पूर्ण
	BUG_ON(hugetlb_max_hstate >= HUGE_MAX_HSTATE);
	BUG_ON(order == 0);
	h = &hstates[hugetlb_max_hstate++];
	mutex_init(&h->resize_lock);
	h->order = order;
	h->mask = ~(huge_page_size(h) - 1);
	क्रम (i = 0; i < MAX_NUMNODES; ++i)
		INIT_LIST_HEAD(&h->hugepage_मुक्तlists[i]);
	INIT_LIST_HEAD(&h->hugepage_activelist);
	h->next_nid_to_alloc = first_memory_node;
	h->next_nid_to_मुक्त = first_memory_node;
	snम_लिखो(h->name, HSTATE_NAME_LEN, "hugepages-%lukB",
					huge_page_size(h)/1024);

	parsed_hstate = h;
पूर्ण

/*
 * hugepages command line processing
 * hugepages normally follows a valid hugepagsz or शेष_hugepagsz
 * specअगरication.  If not, ignore the hugepages value.  hugepages can also
 * be the first huge page command line  option in which हाल it implicitly
 * specअगरies the number of huge pages क्रम the शेष size.
 */
अटल पूर्णांक __init hugepages_setup(अक्षर *s)
अणु
	अचिन्हित दीर्घ *mhp;
	अटल अचिन्हित दीर्घ *last_mhp;

	अगर (!parsed_valid_hugepagesz) अणु
		pr_warn("HugeTLB: hugepages=%s does not follow a valid hugepagesz, ignoring\n", s);
		parsed_valid_hugepagesz = true;
		वापस 0;
	पूर्ण

	/*
	 * !hugetlb_max_hstate means we haven't parsed a hugepagesz= parameter
	 * yet, so this hugepages= parameter goes to the "default hstate".
	 * Otherwise, it goes with the previously parsed hugepagesz or
	 * शेष_hugepagesz.
	 */
	अन्यथा अगर (!hugetlb_max_hstate)
		mhp = &शेष_hstate_max_huge_pages;
	अन्यथा
		mhp = &parsed_hstate->max_huge_pages;

	अगर (mhp == last_mhp) अणु
		pr_warn("HugeTLB: hugepages= specified twice without interleaving hugepagesz=, ignoring hugepages=%s\n", s);
		वापस 0;
	पूर्ण

	अगर (माला_पूछो(s, "%lu", mhp) <= 0)
		*mhp = 0;

	/*
	 * Global state is always initialized later in hugetlb_init.
	 * But we need to allocate gigantic hstates here early to still
	 * use the booपंचांगem allocator.
	 */
	अगर (hugetlb_max_hstate && hstate_is_gigantic(parsed_hstate))
		hugetlb_hstate_alloc_pages(parsed_hstate);

	last_mhp = mhp;

	वापस 1;
पूर्ण
__setup("hugepages=", hugepages_setup);

/*
 * hugepagesz command line processing
 * A specअगरic huge page size can only be specअगरied once with hugepagesz.
 * hugepagesz is followed by hugepages on the command line.  The global
 * variable 'parsed_valid_hugepagesz' is used to determine अगर prior
 * hugepagesz argument was valid.
 */
अटल पूर्णांक __init hugepagesz_setup(अक्षर *s)
अणु
	अचिन्हित दीर्घ size;
	काष्ठा hstate *h;

	parsed_valid_hugepagesz = false;
	size = (अचिन्हित दीर्घ)memparse(s, शून्य);

	अगर (!arch_hugetlb_valid_size(size)) अणु
		pr_err("HugeTLB: unsupported hugepagesz=%s\n", s);
		वापस 0;
	पूर्ण

	h = माप_प्रकारo_hstate(size);
	अगर (h) अणु
		/*
		 * hstate क्रम this size alपढ़ोy exists.  This is normally
		 * an error, but is allowed अगर the existing hstate is the
		 * शेष hstate.  More specअगरically, it is only allowed अगर
		 * the number of huge pages क्रम the शेष hstate was not
		 * previously specअगरied.
		 */
		अगर (!parsed_शेष_hugepagesz ||  h != &शेष_hstate ||
		    शेष_hstate.max_huge_pages) अणु
			pr_warn("HugeTLB: hugepagesz=%s specified twice, ignoring\n", s);
			वापस 0;
		पूर्ण

		/*
		 * No need to call hugetlb_add_hstate() as hstate alपढ़ोy
		 * exists.  But, करो set parsed_hstate so that a following
		 * hugepages= parameter will be applied to this hstate.
		 */
		parsed_hstate = h;
		parsed_valid_hugepagesz = true;
		वापस 1;
	पूर्ण

	hugetlb_add_hstate(ilog2(size) - PAGE_SHIFT);
	parsed_valid_hugepagesz = true;
	वापस 1;
पूर्ण
__setup("hugepagesz=", hugepagesz_setup);

/*
 * शेष_hugepagesz command line input
 * Only one instance of शेष_hugepagesz allowed on command line.
 */
अटल पूर्णांक __init शेष_hugepagesz_setup(अक्षर *s)
अणु
	अचिन्हित दीर्घ size;

	parsed_valid_hugepagesz = false;
	अगर (parsed_शेष_hugepagesz) अणु
		pr_err("HugeTLB: default_hugepagesz previously specified, ignoring %s\n", s);
		वापस 0;
	पूर्ण

	size = (अचिन्हित दीर्घ)memparse(s, शून्य);

	अगर (!arch_hugetlb_valid_size(size)) अणु
		pr_err("HugeTLB: unsupported default_hugepagesz=%s\n", s);
		वापस 0;
	पूर्ण

	hugetlb_add_hstate(ilog2(size) - PAGE_SHIFT);
	parsed_valid_hugepagesz = true;
	parsed_शेष_hugepagesz = true;
	शेष_hstate_idx = hstate_index(माप_प्रकारo_hstate(size));

	/*
	 * The number of शेष huge pages (क्रम this size) could have been
	 * specअगरied as the first hugetlb parameter: hugepages=X.  If so,
	 * then शेष_hstate_max_huge_pages is set.  If the शेष huge
	 * page size is gigantic (>= MAX_ORDER), then the pages must be
	 * allocated here from booपंचांगem allocator.
	 */
	अगर (शेष_hstate_max_huge_pages) अणु
		शेष_hstate.max_huge_pages = शेष_hstate_max_huge_pages;
		अगर (hstate_is_gigantic(&शेष_hstate))
			hugetlb_hstate_alloc_pages(&शेष_hstate);
		शेष_hstate_max_huge_pages = 0;
	पूर्ण

	वापस 1;
पूर्ण
__setup("default_hugepagesz=", शेष_hugepagesz_setup);

अटल अचिन्हित पूर्णांक allowed_mems_nr(काष्ठा hstate *h)
अणु
	पूर्णांक node;
	अचिन्हित पूर्णांक nr = 0;
	nodemask_t *mpol_allowed;
	अचिन्हित पूर्णांक *array = h->मुक्त_huge_pages_node;
	gfp_t gfp_mask = htlb_alloc_mask(h);

	mpol_allowed = policy_nodemask_current(gfp_mask);

	क्रम_each_node_mask(node, cpuset_current_mems_allowed) अणु
		अगर (!mpol_allowed || node_isset(node, *mpol_allowed))
			nr += array[node];
	पूर्ण

	वापस nr;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
अटल पूर्णांक proc_hugetlb_करोuदीर्घvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
					  व्योम *buffer, माप_प्रकार *length,
					  loff_t *ppos, अचिन्हित दीर्घ *out)
अणु
	काष्ठा ctl_table dup_table;

	/*
	 * In order to aव्योम races with __करो_proc_करोuदीर्घvec_minmax(), we
	 * can duplicate the @table and alter the duplicate of it.
	 */
	dup_table = *table;
	dup_table.data = out;

	वापस proc_करोuदीर्घvec_minmax(&dup_table, ग_लिखो, buffer, length, ppos);
पूर्ण

अटल पूर्णांक hugetlb_sysctl_handler_common(bool obey_mempolicy,
			 काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			 व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	काष्ठा hstate *h = &शेष_hstate;
	अचिन्हित दीर्घ पंचांगp = h->max_huge_pages;
	पूर्णांक ret;

	अगर (!hugepages_supported())
		वापस -EOPNOTSUPP;

	ret = proc_hugetlb_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, length, ppos,
					     &पंचांगp);
	अगर (ret)
		जाओ out;

	अगर (ग_लिखो)
		ret = __nr_hugepages_store_common(obey_mempolicy, h,
						  NUMA_NO_NODE, पंचांगp, *length);
out:
	वापस ret;
पूर्ण

पूर्णांक hugetlb_sysctl_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			  व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु

	वापस hugetlb_sysctl_handler_common(false, table, ग_लिखो,
							buffer, length, ppos);
पूर्ण

#अगर_घोषित CONFIG_NUMA
पूर्णांक hugetlb_mempolicy_sysctl_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			  व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	वापस hugetlb_sysctl_handler_common(true, table, ग_लिखो,
							buffer, length, ppos);
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA */

पूर्णांक hugetlb_overcommit_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	काष्ठा hstate *h = &शेष_hstate;
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;

	अगर (!hugepages_supported())
		वापस -EOPNOTSUPP;

	पंचांगp = h->nr_overcommit_huge_pages;

	अगर (ग_लिखो && hstate_is_gigantic(h))
		वापस -EINVAL;

	ret = proc_hugetlb_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, length, ppos,
					     &पंचांगp);
	अगर (ret)
		जाओ out;

	अगर (ग_लिखो) अणु
		spin_lock_irq(&hugetlb_lock);
		h->nr_overcommit_huge_pages = पंचांगp;
		spin_unlock_irq(&hugetlb_lock);
	पूर्ण
out:
	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_SYSCTL */

व्योम hugetlb_report_meminfo(काष्ठा seq_file *m)
अणु
	काष्ठा hstate *h;
	अचिन्हित दीर्घ total = 0;

	अगर (!hugepages_supported())
		वापस;

	क्रम_each_hstate(h) अणु
		अचिन्हित दीर्घ count = h->nr_huge_pages;

		total += huge_page_size(h) * count;

		अगर (h == &शेष_hstate)
			seq_म_लिखो(m,
				   "HugePages_Total:   %5lu\n"
				   "HugePages_Free:    %5lu\n"
				   "HugePages_Rsvd:    %5lu\n"
				   "HugePages_Surp:    %5lu\n"
				   "Hugepagesize:   %8lu kB\n",
				   count,
				   h->मुक्त_huge_pages,
				   h->resv_huge_pages,
				   h->surplus_huge_pages,
				   huge_page_size(h) / SZ_1K);
	पूर्ण

	seq_म_लिखो(m, "Hugetlb:        %8lu kB\n", total / SZ_1K);
पूर्ण

पूर्णांक hugetlb_report_node_meminfo(अक्षर *buf, पूर्णांक len, पूर्णांक nid)
अणु
	काष्ठा hstate *h = &शेष_hstate;

	अगर (!hugepages_supported())
		वापस 0;

	वापस sysfs_emit_at(buf, len,
			     "Node %d HugePages_Total: %5u\n"
			     "Node %d HugePages_Free:  %5u\n"
			     "Node %d HugePages_Surp:  %5u\n",
			     nid, h->nr_huge_pages_node[nid],
			     nid, h->मुक्त_huge_pages_node[nid],
			     nid, h->surplus_huge_pages_node[nid]);
पूर्ण

व्योम hugetlb_show_meminfo(व्योम)
अणु
	काष्ठा hstate *h;
	पूर्णांक nid;

	अगर (!hugepages_supported())
		वापस;

	क्रम_each_node_state(nid, N_MEMORY)
		क्रम_each_hstate(h)
			pr_info("Node %d hugepages_total=%u hugepages_free=%u hugepages_surp=%u hugepages_size=%lukB\n",
				nid,
				h->nr_huge_pages_node[nid],
				h->मुक्त_huge_pages_node[nid],
				h->surplus_huge_pages_node[nid],
				huge_page_size(h) / SZ_1K);
पूर्ण

व्योम hugetlb_report_usage(काष्ठा seq_file *m, काष्ठा mm_काष्ठा *mm)
अणु
	seq_म_लिखो(m, "HugetlbPages:\t%8lu kB\n",
		   atomic_दीर्घ_पढ़ो(&mm->hugetlb_usage) << (PAGE_SHIFT - 10));
पूर्ण

/* Return the number pages of memory we physically have, in PAGE_SIZE units. */
अचिन्हित दीर्घ hugetlb_total_pages(व्योम)
अणु
	काष्ठा hstate *h;
	अचिन्हित दीर्घ nr_total_pages = 0;

	क्रम_each_hstate(h)
		nr_total_pages += h->nr_huge_pages * pages_per_huge_page(h);
	वापस nr_total_pages;
पूर्ण

अटल पूर्णांक hugetlb_acct_memory(काष्ठा hstate *h, दीर्घ delta)
अणु
	पूर्णांक ret = -ENOMEM;

	अगर (!delta)
		वापस 0;

	spin_lock_irq(&hugetlb_lock);
	/*
	 * When cpuset is configured, it अवरोधs the strict hugetlb page
	 * reservation as the accounting is करोne on a global variable. Such
	 * reservation is completely rubbish in the presence of cpuset because
	 * the reservation is not checked against page availability क्रम the
	 * current cpuset. Application can still potentially OOM'ed by kernel
	 * with lack of मुक्त htlb page in cpuset that the task is in.
	 * Attempt to enक्रमce strict accounting with cpuset is almost
	 * impossible (or too ugly) because cpuset is too fluid that
	 * task or memory node can be dynamically moved between cpusets.
	 *
	 * The change of semantics क्रम shared hugetlb mapping with cpuset is
	 * undesirable. However, in order to preserve some of the semantics,
	 * we fall back to check against current मुक्त page availability as
	 * a best attempt and hopefully to minimize the impact of changing
	 * semantics that cpuset has.
	 *
	 * Apart from cpuset, we also have memory policy mechanism that
	 * also determines from which node the kernel will allocate memory
	 * in a NUMA प्रणाली. So similar to cpuset, we also should consider
	 * the memory policy of the current task. Similar to the description
	 * above.
	 */
	अगर (delta > 0) अणु
		अगर (gather_surplus_pages(h, delta) < 0)
			जाओ out;

		अगर (delta > allowed_mems_nr(h)) अणु
			वापस_unused_surplus_pages(h, delta);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = 0;
	अगर (delta < 0)
		वापस_unused_surplus_pages(h, (अचिन्हित दीर्घ) -delta);

out:
	spin_unlock_irq(&hugetlb_lock);
	वापस ret;
पूर्ण

अटल व्योम hugetlb_vm_op_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा resv_map *resv = vma_resv_map(vma);

	/*
	 * This new VMA should share its siblings reservation map अगर present.
	 * The VMA will only ever have a valid reservation map poपूर्णांकer where
	 * it is being copied क्रम another still existing VMA.  As that VMA
	 * has a reference to the reservation map it cannot disappear until
	 * after this खोलो call completes.  It is thereक्रमe safe to take a
	 * new reference here without additional locking.
	 */
	अगर (resv && is_vma_resv_set(vma, HPAGE_RESV_OWNER))
		kref_get(&resv->refs);
पूर्ण

अटल व्योम hugetlb_vm_op_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा hstate *h = hstate_vma(vma);
	काष्ठा resv_map *resv = vma_resv_map(vma);
	काष्ठा hugepage_subpool *spool = subpool_vma(vma);
	अचिन्हित दीर्घ reserve, start, end;
	दीर्घ gbl_reserve;

	अगर (!resv || !is_vma_resv_set(vma, HPAGE_RESV_OWNER))
		वापस;

	start = vma_hugecache_offset(h, vma, vma->vm_start);
	end = vma_hugecache_offset(h, vma, vma->vm_end);

	reserve = (end - start) - region_count(resv, start, end);
	hugetlb_cgroup_unअक्षरge_counter(resv, start, end);
	अगर (reserve) अणु
		/*
		 * Decrement reserve counts.  The global reserve count may be
		 * adjusted अगर the subpool has a minimum size.
		 */
		gbl_reserve = hugepage_subpool_put_pages(spool, reserve);
		hugetlb_acct_memory(h, -gbl_reserve);
	पूर्ण

	kref_put(&resv->refs, resv_map_release);
पूर्ण

अटल पूर्णांक hugetlb_vm_op_split(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	अगर (addr & ~(huge_page_mask(hstate_vma(vma))))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ hugetlb_vm_op_pagesize(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस huge_page_size(hstate_vma(vma));
पूर्ण

/*
 * We cannot handle pagefaults against hugetlb pages at all.  They cause
 * handle_mm_fault() to try to instantiate regular-sized pages in the
 * hugepage VMA.  करो_page_fault() is supposed to trap this, so BUG is we get
 * this far.
 */
अटल vm_fault_t hugetlb_vm_op_fault(काष्ठा vm_fault *vmf)
अणु
	BUG();
	वापस 0;
पूर्ण

/*
 * When a new function is पूर्णांकroduced to vm_operations_काष्ठा and added
 * to hugetlb_vm_ops, please consider adding the function to shm_vm_ops.
 * This is because under System V memory model, mappings created via
 * shmget/shmat with "huge page" specअगरied are backed by hugetlbfs files,
 * their original vm_ops are overwritten with shm_vm_ops.
 */
स्थिर काष्ठा vm_operations_काष्ठा hugetlb_vm_ops = अणु
	.fault = hugetlb_vm_op_fault,
	.खोलो = hugetlb_vm_op_खोलो,
	.बंद = hugetlb_vm_op_बंद,
	.may_split = hugetlb_vm_op_split,
	.pagesize = hugetlb_vm_op_pagesize,
पूर्ण;

अटल pte_t make_huge_pte(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
				पूर्णांक writable)
अणु
	pte_t entry;

	अगर (writable) अणु
		entry = huge_pte_mkग_लिखो(huge_pte_सूची_गढ़ोty(mk_huge_pte(page,
					 vma->vm_page_prot)));
	पूर्ण अन्यथा अणु
		entry = huge_pte_wrprotect(mk_huge_pte(page,
					   vma->vm_page_prot));
	पूर्ण
	entry = pte_mkyoung(entry);
	entry = pte_mkhuge(entry);
	entry = arch_make_huge_pte(entry, vma, page, writable);

	वापस entry;
पूर्ण

अटल व्योम set_huge_ptep_writable(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	pte_t entry;

	entry = huge_pte_mkग_लिखो(huge_pte_सूची_गढ़ोty(huge_ptep_get(ptep)));
	अगर (huge_ptep_set_access_flags(vma, address, ptep, entry, 1))
		update_mmu_cache(vma, address, ptep);
पूर्ण

bool is_hugetlb_entry_migration(pte_t pte)
अणु
	swp_entry_t swp;

	अगर (huge_pte_none(pte) || pte_present(pte))
		वापस false;
	swp = pte_to_swp_entry(pte);
	अगर (is_migration_entry(swp))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool is_hugetlb_entry_hwpoisoned(pte_t pte)
अणु
	swp_entry_t swp;

	अगर (huge_pte_none(pte) || pte_present(pte))
		वापस false;
	swp = pte_to_swp_entry(pte);
	अगर (is_hwpoison_entry(swp))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम
hugetlb_install_page(काष्ठा vm_area_काष्ठा *vma, pte_t *ptep, अचिन्हित दीर्घ addr,
		     काष्ठा page *new_page)
अणु
	__SetPageUptodate(new_page);
	set_huge_pte_at(vma->vm_mm, addr, ptep, make_huge_pte(vma, new_page, 1));
	hugepage_add_new_anon_rmap(new_page, vma, addr);
	hugetlb_count_add(pages_per_huge_page(hstate_vma(vma)), vma->vm_mm);
	ClearHPageRestoreReserve(new_page);
	SetHPageMigratable(new_page);
पूर्ण

पूर्णांक copy_hugetlb_page_range(काष्ठा mm_काष्ठा *dst, काष्ठा mm_काष्ठा *src,
			    काष्ठा vm_area_काष्ठा *vma)
अणु
	pte_t *src_pte, *dst_pte, entry, dst_entry;
	काष्ठा page *ptepage;
	अचिन्हित दीर्घ addr;
	bool cow = is_cow_mapping(vma->vm_flags);
	काष्ठा hstate *h = hstate_vma(vma);
	अचिन्हित दीर्घ sz = huge_page_size(h);
	अचिन्हित दीर्घ npages = pages_per_huge_page(h);
	काष्ठा address_space *mapping = vma->vm_file->f_mapping;
	काष्ठा mmu_notअगरier_range range;
	पूर्णांक ret = 0;

	अगर (cow) अणु
		mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, src,
					vma->vm_start,
					vma->vm_end);
		mmu_notअगरier_invalidate_range_start(&range);
	पूर्ण अन्यथा अणु
		/*
		 * For shared mappings i_mmap_rwsem must be held to call
		 * huge_pte_alloc, otherwise the वापसed ptep could go
		 * away अगर part of a shared pmd and another thपढ़ो calls
		 * huge_pmd_unshare.
		 */
		i_mmap_lock_पढ़ो(mapping);
	पूर्ण

	क्रम (addr = vma->vm_start; addr < vma->vm_end; addr += sz) अणु
		spinlock_t *src_ptl, *dst_ptl;
		src_pte = huge_pte_offset(src, addr, sz);
		अगर (!src_pte)
			जारी;
		dst_pte = huge_pte_alloc(dst, vma, addr, sz);
		अगर (!dst_pte) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		/*
		 * If the pagetables are shared करोn't copy or take references.
		 * dst_pte == src_pte is the common हाल of src/dest sharing.
		 *
		 * However, src could have 'unshared' and dst shares with
		 * another vma.  If dst_pte !none, this implies sharing.
		 * Check here beक्रमe taking page table lock, and once again
		 * after taking the lock below.
		 */
		dst_entry = huge_ptep_get(dst_pte);
		अगर ((dst_pte == src_pte) || !huge_pte_none(dst_entry))
			जारी;

		dst_ptl = huge_pte_lock(h, dst, dst_pte);
		src_ptl = huge_pte_lockptr(h, src, src_pte);
		spin_lock_nested(src_ptl, SINGLE_DEPTH_NESTING);
		entry = huge_ptep_get(src_pte);
		dst_entry = huge_ptep_get(dst_pte);
again:
		अगर (huge_pte_none(entry) || !huge_pte_none(dst_entry)) अणु
			/*
			 * Skip अगर src entry none.  Also, skip in the
			 * unlikely हाल dst entry !none as this implies
			 * sharing with another vma.
			 */
			;
		पूर्ण अन्यथा अगर (unlikely(is_hugetlb_entry_migration(entry) ||
				    is_hugetlb_entry_hwpoisoned(entry))) अणु
			swp_entry_t swp_entry = pte_to_swp_entry(entry);

			अगर (is_ग_लिखो_migration_entry(swp_entry) && cow) अणु
				/*
				 * COW mappings require pages in both
				 * parent and child to be set to पढ़ो.
				 */
				make_migration_entry_पढ़ो(&swp_entry);
				entry = swp_entry_to_pte(swp_entry);
				set_huge_swap_pte_at(src, addr, src_pte,
						     entry, sz);
			पूर्ण
			set_huge_swap_pte_at(dst, addr, dst_pte, entry, sz);
		पूर्ण अन्यथा अणु
			entry = huge_ptep_get(src_pte);
			ptepage = pte_page(entry);
			get_page(ptepage);

			/*
			 * This is a rare हाल where we see pinned hugetlb
			 * pages जबतक they're prone to COW.  We need to करो the
			 * COW earlier during विभाजन.
			 *
			 * When pre-allocating the page or copying data, we
			 * need to be without the pgtable locks since we could
			 * sleep during the process.
			 */
			अगर (unlikely(page_needs_cow_क्रम_dma(vma, ptepage))) अणु
				pte_t src_pte_old = entry;
				काष्ठा page *new;

				spin_unlock(src_ptl);
				spin_unlock(dst_ptl);
				/* Do not use reserve as it's निजी owned */
				new = alloc_huge_page(vma, addr, 1);
				अगर (IS_ERR(new)) अणु
					put_page(ptepage);
					ret = PTR_ERR(new);
					अवरोध;
				पूर्ण
				copy_user_huge_page(new, ptepage, addr, vma,
						    npages);
				put_page(ptepage);

				/* Install the new huge page अगर src pte stable */
				dst_ptl = huge_pte_lock(h, dst, dst_pte);
				src_ptl = huge_pte_lockptr(h, src, src_pte);
				spin_lock_nested(src_ptl, SINGLE_DEPTH_NESTING);
				entry = huge_ptep_get(src_pte);
				अगर (!pte_same(src_pte_old, entry)) अणु
					restore_reserve_on_error(h, vma, addr,
								new);
					put_page(new);
					/* dst_entry won't change as in child */
					जाओ again;
				पूर्ण
				hugetlb_install_page(vma, dst_pte, addr, new);
				spin_unlock(src_ptl);
				spin_unlock(dst_ptl);
				जारी;
			पूर्ण

			अगर (cow) अणु
				/*
				 * No need to notअगरy as we are करोwngrading page
				 * table protection not changing it to poपूर्णांक
				 * to a new page.
				 *
				 * See Documentation/vm/mmu_notअगरier.rst
				 */
				huge_ptep_set_wrprotect(src, addr, src_pte);
				entry = huge_pte_wrprotect(entry);
			पूर्ण

			page_dup_rmap(ptepage, true);
			set_huge_pte_at(dst, addr, dst_pte, entry);
			hugetlb_count_add(npages, dst);
		पूर्ण
		spin_unlock(src_ptl);
		spin_unlock(dst_ptl);
	पूर्ण

	अगर (cow)
		mmu_notअगरier_invalidate_range_end(&range);
	अन्यथा
		i_mmap_unlock_पढ़ो(mapping);

	वापस ret;
पूर्ण

व्योम __unmap_hugepage_range(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma,
			    अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			    काष्ठा page *ref_page)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ address;
	pte_t *ptep;
	pte_t pte;
	spinlock_t *ptl;
	काष्ठा page *page;
	काष्ठा hstate *h = hstate_vma(vma);
	अचिन्हित दीर्घ sz = huge_page_size(h);
	काष्ठा mmu_notअगरier_range range;

	WARN_ON(!is_vm_hugetlb_page(vma));
	BUG_ON(start & ~huge_page_mask(h));
	BUG_ON(end & ~huge_page_mask(h));

	/*
	 * This is a hugetlb vma, all the pte entries should poपूर्णांक
	 * to huge page.
	 */
	tlb_change_page_size(tlb, sz);
	tlb_start_vma(tlb, vma);

	/*
	 * If sharing possible, alert mmu notअगरiers of worst हाल.
	 */
	mmu_notअगरier_range_init(&range, MMU_NOTIFY_UNMAP, 0, vma, mm, start,
				end);
	adjust_range_अगर_pmd_sharing_possible(vma, &range.start, &range.end);
	mmu_notअगरier_invalidate_range_start(&range);
	address = start;
	क्रम (; address < end; address += sz) अणु
		ptep = huge_pte_offset(mm, address, sz);
		अगर (!ptep)
			जारी;

		ptl = huge_pte_lock(h, mm, ptep);
		अगर (huge_pmd_unshare(mm, vma, &address, ptep)) अणु
			spin_unlock(ptl);
			/*
			 * We just unmapped a page of PMDs by clearing a PUD.
			 * The caller's TLB flush range should cover this area.
			 */
			जारी;
		पूर्ण

		pte = huge_ptep_get(ptep);
		अगर (huge_pte_none(pte)) अणु
			spin_unlock(ptl);
			जारी;
		पूर्ण

		/*
		 * Migrating hugepage or HWPoisoned hugepage is alपढ़ोy
		 * unmapped and its refcount is dropped, so just clear pte here.
		 */
		अगर (unlikely(!pte_present(pte))) अणु
			huge_pte_clear(mm, address, ptep, sz);
			spin_unlock(ptl);
			जारी;
		पूर्ण

		page = pte_page(pte);
		/*
		 * If a reference page is supplied, it is because a specअगरic
		 * page is being unmapped, not a range. Ensure the page we
		 * are about to unmap is the actual page of पूर्णांकerest.
		 */
		अगर (ref_page) अणु
			अगर (page != ref_page) अणु
				spin_unlock(ptl);
				जारी;
			पूर्ण
			/*
			 * Mark the VMA as having unmapped its page so that
			 * future faults in this VMA will fail rather than
			 * looking like data was lost
			 */
			set_vma_resv_flags(vma, HPAGE_RESV_UNMAPPED);
		पूर्ण

		pte = huge_ptep_get_and_clear(mm, address, ptep);
		tlb_हटाओ_huge_tlb_entry(h, tlb, ptep, address);
		अगर (huge_pte_dirty(pte))
			set_page_dirty(page);

		hugetlb_count_sub(pages_per_huge_page(h), mm);
		page_हटाओ_rmap(page, true);

		spin_unlock(ptl);
		tlb_हटाओ_page_size(tlb, page, huge_page_size(h));
		/*
		 * Bail out after unmapping reference page अगर supplied
		 */
		अगर (ref_page)
			अवरोध;
	पूर्ण
	mmu_notअगरier_invalidate_range_end(&range);
	tlb_end_vma(tlb, vma);
पूर्ण

व्योम __unmap_hugepage_range_final(काष्ठा mmu_gather *tlb,
			  काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			  अचिन्हित दीर्घ end, काष्ठा page *ref_page)
अणु
	__unmap_hugepage_range(tlb, vma, start, end, ref_page);

	/*
	 * Clear this flag so that x86's huge_pmd_share page_table_shareable
	 * test will fail on a vma being torn करोwn, and not grab a page table
	 * on its way out.  We're lucky that the flag has such an appropriate
	 * name, and can in fact be safely cleared here. We could clear it
	 * beक्रमe the __unmap_hugepage_range above, but all that's necessary
	 * is to clear it beक्रमe releasing the i_mmap_rwsem. This works
	 * because in the context this is called, the VMA is about to be
	 * destroyed and the i_mmap_rwsem is held.
	 */
	vma->vm_flags &= ~VM_MAYSHARE;
पूर्ण

व्योम unmap_hugepage_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			  अचिन्हित दीर्घ end, काष्ठा page *ref_page)
अणु
	काष्ठा mmu_gather tlb;

	tlb_gather_mmu(&tlb, vma->vm_mm);
	__unmap_hugepage_range(&tlb, vma, start, end, ref_page);
	tlb_finish_mmu(&tlb);
पूर्ण

/*
 * This is called when the original mapper is failing to COW a MAP_PRIVATE
 * mapping it owns the reserve page क्रम. The पूर्णांकention is to unmap the page
 * from other VMAs and let the children be SIGKILLed अगर they are faulting the
 * same region.
 */
अटल व्योम unmap_ref_निजी(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			      काष्ठा page *page, अचिन्हित दीर्घ address)
अणु
	काष्ठा hstate *h = hstate_vma(vma);
	काष्ठा vm_area_काष्ठा *iter_vma;
	काष्ठा address_space *mapping;
	pgoff_t pgoff;

	/*
	 * vm_pgoff is in PAGE_SIZE units, hence the dअगरferent calculation
	 * from page cache lookup which is in HPAGE_SIZE units.
	 */
	address = address & huge_page_mask(h);
	pgoff = ((address - vma->vm_start) >> PAGE_SHIFT) +
			vma->vm_pgoff;
	mapping = vma->vm_file->f_mapping;

	/*
	 * Take the mapping lock क्रम the duration of the table walk. As
	 * this mapping should be shared between all the VMAs,
	 * __unmap_hugepage_range() is called as the lock is alपढ़ोy held
	 */
	i_mmap_lock_ग_लिखो(mapping);
	vma_पूर्णांकerval_tree_क्रमeach(iter_vma, &mapping->i_mmap, pgoff, pgoff) अणु
		/* Do not unmap the current VMA */
		अगर (iter_vma == vma)
			जारी;

		/*
		 * Shared VMAs have their own reserves and करो not affect
		 * MAP_PRIVATE accounting but it is possible that a shared
		 * VMA is using the same page so check and skip such VMAs.
		 */
		अगर (iter_vma->vm_flags & VM_MAYSHARE)
			जारी;

		/*
		 * Unmap the page from other VMAs without their own reserves.
		 * They get marked to be SIGKILLed अगर they fault in these
		 * areas. This is because a future no-page fault on this VMA
		 * could insert a zeroed page instead of the data existing
		 * from the समय of विभाजन. This would look like data corruption
		 */
		अगर (!is_vma_resv_set(iter_vma, HPAGE_RESV_OWNER))
			unmap_hugepage_range(iter_vma, address,
					     address + huge_page_size(h), page);
	पूर्ण
	i_mmap_unlock_ग_लिखो(mapping);
पूर्ण

/*
 * Hugetlb_cow() should be called with page lock of the original hugepage held.
 * Called with hugetlb_instantiation_mutex held and pte_page locked so we
 * cannot race with other handlers or page migration.
 * Keep the pte_same checks anyway to make transition from the mutex easier.
 */
अटल vm_fault_t hugetlb_cow(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		       अचिन्हित दीर्घ address, pte_t *ptep,
		       काष्ठा page *pagecache_page, spinlock_t *ptl)
अणु
	pte_t pte;
	काष्ठा hstate *h = hstate_vma(vma);
	काष्ठा page *old_page, *new_page;
	पूर्णांक outside_reserve = 0;
	vm_fault_t ret = 0;
	अचिन्हित दीर्घ haddr = address & huge_page_mask(h);
	काष्ठा mmu_notअगरier_range range;

	pte = huge_ptep_get(ptep);
	old_page = pte_page(pte);

retry_aव्योमcopy:
	/* If no-one अन्यथा is actually using this page, aव्योम the copy
	 * and just make the page writable */
	अगर (page_mapcount(old_page) == 1 && PageAnon(old_page)) अणु
		page_move_anon_rmap(old_page, vma);
		set_huge_ptep_writable(vma, haddr, ptep);
		वापस 0;
	पूर्ण

	/*
	 * If the process that created a MAP_PRIVATE mapping is about to
	 * perक्रमm a COW due to a shared page count, attempt to satisfy
	 * the allocation without using the existing reserves. The pagecache
	 * page is used to determine अगर the reserve at this address was
	 * consumed or not. If reserves were used, a partial faulted mapping
	 * at the समय of विभाजन() could consume its reserves on COW instead
	 * of the full address range.
	 */
	अगर (is_vma_resv_set(vma, HPAGE_RESV_OWNER) &&
			old_page != pagecache_page)
		outside_reserve = 1;

	get_page(old_page);

	/*
	 * Drop page table lock as buddy allocator may be called. It will
	 * be acquired again beक्रमe वापसing to the caller, as expected.
	 */
	spin_unlock(ptl);
	new_page = alloc_huge_page(vma, haddr, outside_reserve);

	अगर (IS_ERR(new_page)) अणु
		/*
		 * If a process owning a MAP_PRIVATE mapping fails to COW,
		 * it is due to references held by a child and an insufficient
		 * huge page pool. To guarantee the original mappers
		 * reliability, unmap the page from child processes. The child
		 * may get SIGKILLed अगर it later faults.
		 */
		अगर (outside_reserve) अणु
			काष्ठा address_space *mapping = vma->vm_file->f_mapping;
			pgoff_t idx;
			u32 hash;

			put_page(old_page);
			BUG_ON(huge_pte_none(pte));
			/*
			 * Drop hugetlb_fault_mutex and i_mmap_rwsem beक्रमe
			 * unmapping.  unmapping needs to hold i_mmap_rwsem
			 * in ग_लिखो mode.  Dropping i_mmap_rwsem in पढ़ो mode
			 * here is OK as COW mappings करो not पूर्णांकeract with
			 * PMD sharing.
			 *
			 * Reacquire both after unmap operation.
			 */
			idx = vma_hugecache_offset(h, vma, haddr);
			hash = hugetlb_fault_mutex_hash(mapping, idx);
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			i_mmap_unlock_पढ़ो(mapping);

			unmap_ref_निजी(mm, vma, old_page, haddr);

			i_mmap_lock_पढ़ो(mapping);
			mutex_lock(&hugetlb_fault_mutex_table[hash]);
			spin_lock(ptl);
			ptep = huge_pte_offset(mm, haddr, huge_page_size(h));
			अगर (likely(ptep &&
				   pte_same(huge_ptep_get(ptep), pte)))
				जाओ retry_aव्योमcopy;
			/*
			 * race occurs जबतक re-acquiring page table
			 * lock, and our job is करोne.
			 */
			वापस 0;
		पूर्ण

		ret = vmf_error(PTR_ERR(new_page));
		जाओ out_release_old;
	पूर्ण

	/*
	 * When the original hugepage is shared one, it करोes not have
	 * anon_vma prepared.
	 */
	अगर (unlikely(anon_vma_prepare(vma))) अणु
		ret = VM_FAULT_OOM;
		जाओ out_release_all;
	पूर्ण

	copy_user_huge_page(new_page, old_page, address, vma,
			    pages_per_huge_page(h));
	__SetPageUptodate(new_page);

	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, mm, haddr,
				haddr + huge_page_size(h));
	mmu_notअगरier_invalidate_range_start(&range);

	/*
	 * Retake the page table lock to check क्रम racing updates
	 * beक्रमe the page tables are altered
	 */
	spin_lock(ptl);
	ptep = huge_pte_offset(mm, haddr, huge_page_size(h));
	अगर (likely(ptep && pte_same(huge_ptep_get(ptep), pte))) अणु
		ClearHPageRestoreReserve(new_page);

		/* Break COW */
		huge_ptep_clear_flush(vma, haddr, ptep);
		mmu_notअगरier_invalidate_range(mm, range.start, range.end);
		set_huge_pte_at(mm, haddr, ptep,
				make_huge_pte(vma, new_page, 1));
		page_हटाओ_rmap(old_page, true);
		hugepage_add_new_anon_rmap(new_page, vma, haddr);
		SetHPageMigratable(new_page);
		/* Make the old page be मुक्तd below */
		new_page = old_page;
	पूर्ण
	spin_unlock(ptl);
	mmu_notअगरier_invalidate_range_end(&range);
out_release_all:
	restore_reserve_on_error(h, vma, haddr, new_page);
	put_page(new_page);
out_release_old:
	put_page(old_page);

	spin_lock(ptl); /* Caller expects lock to be held */
	वापस ret;
पूर्ण

/* Return the pagecache page at a given address within a VMA */
अटल काष्ठा page *hugetlbfs_pagecache_page(काष्ठा hstate *h,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	काष्ठा address_space *mapping;
	pgoff_t idx;

	mapping = vma->vm_file->f_mapping;
	idx = vma_hugecache_offset(h, vma, address);

	वापस find_lock_page(mapping, idx);
पूर्ण

/*
 * Return whether there is a pagecache page to back given address within VMA.
 * Caller follow_hugetlb_page() holds page_table_lock so we cannot lock_page.
 */
अटल bool hugetlbfs_pagecache_present(काष्ठा hstate *h,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	काष्ठा address_space *mapping;
	pgoff_t idx;
	काष्ठा page *page;

	mapping = vma->vm_file->f_mapping;
	idx = vma_hugecache_offset(h, vma, address);

	page = find_get_page(mapping, idx);
	अगर (page)
		put_page(page);
	वापस page != शून्य;
पूर्ण

पूर्णांक huge_add_to_page_cache(काष्ठा page *page, काष्ठा address_space *mapping,
			   pgoff_t idx)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा hstate *h = hstate_inode(inode);
	पूर्णांक err = add_to_page_cache(page, mapping, idx, GFP_KERNEL);

	अगर (err)
		वापस err;
	ClearHPageRestoreReserve(page);

	/*
	 * set page dirty so that it will not be हटाओd from cache/file
	 * by non-hugetlbfs specअगरic code paths.
	 */
	set_page_dirty(page);

	spin_lock(&inode->i_lock);
	inode->i_blocks += blocks_per_huge_page(h);
	spin_unlock(&inode->i_lock);
	वापस 0;
पूर्ण

अटल अंतरभूत vm_fault_t hugetlb_handle_userfault(काष्ठा vm_area_काष्ठा *vma,
						  काष्ठा address_space *mapping,
						  pgoff_t idx,
						  अचिन्हित पूर्णांक flags,
						  अचिन्हित दीर्घ haddr,
						  अचिन्हित दीर्घ reason)
अणु
	vm_fault_t ret;
	u32 hash;
	काष्ठा vm_fault vmf = अणु
		.vma = vma,
		.address = haddr,
		.flags = flags,

		/*
		 * Hard to debug अगर it ends up being
		 * used by a callee that assumes
		 * something about the other
		 * uninitialized fields... same as in
		 * memory.c
		 */
	पूर्ण;

	/*
	 * hugetlb_fault_mutex and i_mmap_rwsem must be
	 * dropped beक्रमe handling userfault.  Reacquire
	 * after handling fault to make calling code simpler.
	 */
	hash = hugetlb_fault_mutex_hash(mapping, idx);
	mutex_unlock(&hugetlb_fault_mutex_table[hash]);
	i_mmap_unlock_पढ़ो(mapping);
	ret = handle_userfault(&vmf, reason);
	i_mmap_lock_पढ़ो(mapping);
	mutex_lock(&hugetlb_fault_mutex_table[hash]);

	वापस ret;
पूर्ण

अटल vm_fault_t hugetlb_no_page(काष्ठा mm_काष्ठा *mm,
			काष्ठा vm_area_काष्ठा *vma,
			काष्ठा address_space *mapping, pgoff_t idx,
			अचिन्हित दीर्घ address, pte_t *ptep, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा hstate *h = hstate_vma(vma);
	vm_fault_t ret = VM_FAULT_SIGBUS;
	पूर्णांक anon_rmap = 0;
	अचिन्हित दीर्घ size;
	काष्ठा page *page;
	pte_t new_pte;
	spinlock_t *ptl;
	अचिन्हित दीर्घ haddr = address & huge_page_mask(h);
	bool new_page = false;

	/*
	 * Currently, we are क्रमced to समाप्त the process in the event the
	 * original mapper has unmapped pages from the child due to a failed
	 * COW. Warn that such a situation has occurred as it may not be obvious
	 */
	अगर (is_vma_resv_set(vma, HPAGE_RESV_UNMAPPED)) अणु
		pr_warn_ratelimited("PID %d killed due to inadequate hugepage pool\n",
			   current->pid);
		वापस ret;
	पूर्ण

	/*
	 * We can not race with truncation due to holding i_mmap_rwsem.
	 * i_size is modअगरied when holding i_mmap_rwsem, so check here
	 * once क्रम faults beyond end of file.
	 */
	size = i_size_पढ़ो(mapping->host) >> huge_page_shअगरt(h);
	अगर (idx >= size)
		जाओ out;

retry:
	page = find_lock_page(mapping, idx);
	अगर (!page) अणु
		/* Check क्रम page in userfault range */
		अगर (userfaultfd_missing(vma)) अणु
			ret = hugetlb_handle_userfault(vma, mapping, idx,
						       flags, haddr,
						       VM_UFFD_MISSING);
			जाओ out;
		पूर्ण

		page = alloc_huge_page(vma, haddr, 0);
		अगर (IS_ERR(page)) अणु
			/*
			 * Returning error will result in faulting task being
			 * sent SIGBUS.  The hugetlb fault mutex prevents two
			 * tasks from racing to fault in the same page which
			 * could result in false unable to allocate errors.
			 * Page migration करोes not take the fault mutex, but
			 * करोes a clear then ग_लिखो of pte's under page table
			 * lock.  Page fault code could race with migration,
			 * notice the clear pte and try to allocate a page
			 * here.  Beक्रमe वापसing error, get ptl and make
			 * sure there really is no pte entry.
			 */
			ptl = huge_pte_lock(h, mm, ptep);
			ret = 0;
			अगर (huge_pte_none(huge_ptep_get(ptep)))
				ret = vmf_error(PTR_ERR(page));
			spin_unlock(ptl);
			जाओ out;
		पूर्ण
		clear_huge_page(page, address, pages_per_huge_page(h));
		__SetPageUptodate(page);
		new_page = true;

		अगर (vma->vm_flags & VM_MAYSHARE) अणु
			पूर्णांक err = huge_add_to_page_cache(page, mapping, idx);
			अगर (err) अणु
				put_page(page);
				अगर (err == -EEXIST)
					जाओ retry;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			lock_page(page);
			अगर (unlikely(anon_vma_prepare(vma))) अणु
				ret = VM_FAULT_OOM;
				जाओ backout_unlocked;
			पूर्ण
			anon_rmap = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If memory error occurs between mmap() and fault, some process
		 * करोn't have hwpoisoned swap entry क्रम errored भव address.
		 * So we need to block hugepage fault by PG_hwpoison bit check.
		 */
		अगर (unlikely(PageHWPoison(page))) अणु
			ret = VM_FAULT_HWPOISON_LARGE |
				VM_FAULT_SET_HINDEX(hstate_index(h));
			जाओ backout_unlocked;
		पूर्ण

		/* Check क्रम page in userfault range. */
		अगर (userfaultfd_minor(vma)) अणु
			unlock_page(page);
			put_page(page);
			ret = hugetlb_handle_userfault(vma, mapping, idx,
						       flags, haddr,
						       VM_UFFD_MINOR);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * If we are going to COW a निजी mapping later, we examine the
	 * pending reservations क्रम this page now. This will ensure that
	 * any allocations necessary to record that reservation occur outside
	 * the spinlock.
	 */
	अगर ((flags & FAULT_FLAG_WRITE) && !(vma->vm_flags & VM_SHARED)) अणु
		अगर (vma_needs_reservation(h, vma, haddr) < 0) अणु
			ret = VM_FAULT_OOM;
			जाओ backout_unlocked;
		पूर्ण
		/* Just decrements count, करोes not deallocate */
		vma_end_reservation(h, vma, haddr);
	पूर्ण

	ptl = huge_pte_lock(h, mm, ptep);
	ret = 0;
	अगर (!huge_pte_none(huge_ptep_get(ptep)))
		जाओ backout;

	अगर (anon_rmap) अणु
		ClearHPageRestoreReserve(page);
		hugepage_add_new_anon_rmap(page, vma, haddr);
	पूर्ण अन्यथा
		page_dup_rmap(page, true);
	new_pte = make_huge_pte(vma, page, ((vma->vm_flags & VM_WRITE)
				&& (vma->vm_flags & VM_SHARED)));
	set_huge_pte_at(mm, haddr, ptep, new_pte);

	hugetlb_count_add(pages_per_huge_page(h), mm);
	अगर ((flags & FAULT_FLAG_WRITE) && !(vma->vm_flags & VM_SHARED)) अणु
		/* Optimization, करो the COW without a second fault */
		ret = hugetlb_cow(mm, vma, address, ptep, page, ptl);
	पूर्ण

	spin_unlock(ptl);

	/*
	 * Only set HPageMigratable in newly allocated pages.  Existing pages
	 * found in the pagecache may not have HPageMigratableset अगर they have
	 * been isolated क्रम migration.
	 */
	अगर (new_page)
		SetHPageMigratable(page);

	unlock_page(page);
out:
	वापस ret;

backout:
	spin_unlock(ptl);
backout_unlocked:
	unlock_page(page);
	restore_reserve_on_error(h, vma, haddr, page);
	put_page(page);
	जाओ out;
पूर्ण

#अगर_घोषित CONFIG_SMP
u32 hugetlb_fault_mutex_hash(काष्ठा address_space *mapping, pgoff_t idx)
अणु
	अचिन्हित दीर्घ key[2];
	u32 hash;

	key[0] = (अचिन्हित दीर्घ) mapping;
	key[1] = idx;

	hash = jhash2((u32 *)&key, माप(key)/(माप(u32)), 0);

	वापस hash & (num_fault_mutexes - 1);
पूर्ण
#अन्यथा
/*
 * For uniprocessor प्रणालीs we always use a single mutex, so just
 * वापस 0 and aव्योम the hashing overhead.
 */
u32 hugetlb_fault_mutex_hash(काष्ठा address_space *mapping, pgoff_t idx)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

vm_fault_t hugetlb_fault(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ address, अचिन्हित पूर्णांक flags)
अणु
	pte_t *ptep, entry;
	spinlock_t *ptl;
	vm_fault_t ret;
	u32 hash;
	pgoff_t idx;
	काष्ठा page *page = शून्य;
	काष्ठा page *pagecache_page = शून्य;
	काष्ठा hstate *h = hstate_vma(vma);
	काष्ठा address_space *mapping;
	पूर्णांक need_रुको_lock = 0;
	अचिन्हित दीर्घ haddr = address & huge_page_mask(h);

	ptep = huge_pte_offset(mm, haddr, huge_page_size(h));
	अगर (ptep) अणु
		/*
		 * Since we hold no locks, ptep could be stale.  That is
		 * OK as we are only making decisions based on content and
		 * not actually modअगरying content here.
		 */
		entry = huge_ptep_get(ptep);
		अगर (unlikely(is_hugetlb_entry_migration(entry))) अणु
			migration_entry_रुको_huge(vma, mm, ptep);
			वापस 0;
		पूर्ण अन्यथा अगर (unlikely(is_hugetlb_entry_hwpoisoned(entry)))
			वापस VM_FAULT_HWPOISON_LARGE |
				VM_FAULT_SET_HINDEX(hstate_index(h));
	पूर्ण

	/*
	 * Acquire i_mmap_rwsem beक्रमe calling huge_pte_alloc and hold
	 * until finished with ptep.  This serves two purposes:
	 * 1) It prevents huge_pmd_unshare from being called अन्यथाwhere
	 *    and making the ptep no दीर्घer valid.
	 * 2) It synchronizes us with i_size modअगरications during truncation.
	 *
	 * ptep could have alपढ़ोy be asचिन्हित via huge_pte_offset.  That
	 * is OK, as huge_pte_alloc will वापस the same value unless
	 * something has changed.
	 */
	mapping = vma->vm_file->f_mapping;
	i_mmap_lock_पढ़ो(mapping);
	ptep = huge_pte_alloc(mm, vma, haddr, huge_page_size(h));
	अगर (!ptep) अणु
		i_mmap_unlock_पढ़ो(mapping);
		वापस VM_FAULT_OOM;
	पूर्ण

	/*
	 * Serialize hugepage allocation and instantiation, so that we करोn't
	 * get spurious allocation failures अगर two CPUs race to instantiate
	 * the same page in the page cache.
	 */
	idx = vma_hugecache_offset(h, vma, haddr);
	hash = hugetlb_fault_mutex_hash(mapping, idx);
	mutex_lock(&hugetlb_fault_mutex_table[hash]);

	entry = huge_ptep_get(ptep);
	अगर (huge_pte_none(entry)) अणु
		ret = hugetlb_no_page(mm, vma, mapping, idx, address, ptep, flags);
		जाओ out_mutex;
	पूर्ण

	ret = 0;

	/*
	 * entry could be a migration/hwpoison entry at this poपूर्णांक, so this
	 * check prevents the kernel from going below assuming that we have
	 * an active hugepage in pagecache. This जाओ expects the 2nd page
	 * fault, and is_hugetlb_entry_(migration|hwpoisoned) check will
	 * properly handle it.
	 */
	अगर (!pte_present(entry))
		जाओ out_mutex;

	/*
	 * If we are going to COW the mapping later, we examine the pending
	 * reservations क्रम this page now. This will ensure that any
	 * allocations necessary to record that reservation occur outside the
	 * spinlock. For निजी mappings, we also lookup the pagecache
	 * page now as it is used to determine अगर a reservation has been
	 * consumed.
	 */
	अगर ((flags & FAULT_FLAG_WRITE) && !huge_pte_ग_लिखो(entry)) अणु
		अगर (vma_needs_reservation(h, vma, haddr) < 0) अणु
			ret = VM_FAULT_OOM;
			जाओ out_mutex;
		पूर्ण
		/* Just decrements count, करोes not deallocate */
		vma_end_reservation(h, vma, haddr);

		अगर (!(vma->vm_flags & VM_MAYSHARE))
			pagecache_page = hugetlbfs_pagecache_page(h,
								vma, haddr);
	पूर्ण

	ptl = huge_pte_lock(h, mm, ptep);

	/* Check क्रम a racing update beक्रमe calling hugetlb_cow */
	अगर (unlikely(!pte_same(entry, huge_ptep_get(ptep))))
		जाओ out_ptl;

	/*
	 * hugetlb_cow() requires page locks of pte_page(entry) and
	 * pagecache_page, so here we need take the क्रमmer one
	 * when page != pagecache_page or !pagecache_page.
	 */
	page = pte_page(entry);
	अगर (page != pagecache_page)
		अगर (!trylock_page(page)) अणु
			need_रुको_lock = 1;
			जाओ out_ptl;
		पूर्ण

	get_page(page);

	अगर (flags & FAULT_FLAG_WRITE) अणु
		अगर (!huge_pte_ग_लिखो(entry)) अणु
			ret = hugetlb_cow(mm, vma, address, ptep,
					  pagecache_page, ptl);
			जाओ out_put_page;
		पूर्ण
		entry = huge_pte_सूची_गढ़ोty(entry);
	पूर्ण
	entry = pte_mkyoung(entry);
	अगर (huge_ptep_set_access_flags(vma, haddr, ptep, entry,
						flags & FAULT_FLAG_WRITE))
		update_mmu_cache(vma, haddr, ptep);
out_put_page:
	अगर (page != pagecache_page)
		unlock_page(page);
	put_page(page);
out_ptl:
	spin_unlock(ptl);

	अगर (pagecache_page) अणु
		unlock_page(pagecache_page);
		put_page(pagecache_page);
	पूर्ण
out_mutex:
	mutex_unlock(&hugetlb_fault_mutex_table[hash]);
	i_mmap_unlock_पढ़ो(mapping);
	/*
	 * Generally it's safe to hold refcount during रुकोing page lock. But
	 * here we just रुको to defer the next page fault to aव्योम busy loop and
	 * the page is not used after unlocked beक्रमe वापसing from the current
	 * page fault. So we are safe from accessing मुक्तd page, even अगर we रुको
	 * here without taking refcount.
	 */
	अगर (need_रुको_lock)
		रुको_on_page_locked(page);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_USERFAULTFD
/*
 * Used by userfaultfd UFFDIO_COPY.  Based on mcopy_atomic_pte with
 * modअगरications क्रम huge pages.
 */
पूर्णांक hugetlb_mcopy_atomic_pte(काष्ठा mm_काष्ठा *dst_mm,
			    pte_t *dst_pte,
			    काष्ठा vm_area_काष्ठा *dst_vma,
			    अचिन्हित दीर्घ dst_addr,
			    अचिन्हित दीर्घ src_addr,
			    क्रमागत mcopy_atomic_mode mode,
			    काष्ठा page **pagep)
अणु
	bool is_जारी = (mode == MCOPY_ATOMIC_CONTINUE);
	काष्ठा address_space *mapping;
	pgoff_t idx;
	अचिन्हित दीर्घ size;
	पूर्णांक vm_shared = dst_vma->vm_flags & VM_SHARED;
	काष्ठा hstate *h = hstate_vma(dst_vma);
	pte_t _dst_pte;
	spinlock_t *ptl;
	पूर्णांक ret;
	काष्ठा page *page;
	पूर्णांक writable;

	mapping = dst_vma->vm_file->f_mapping;
	idx = vma_hugecache_offset(h, dst_vma, dst_addr);

	अगर (is_जारी) अणु
		ret = -EFAULT;
		page = find_lock_page(mapping, idx);
		अगर (!page)
			जाओ out;
	पूर्ण अन्यथा अगर (!*pagep) अणु
		/* If a page alपढ़ोy exists, then it's UFFDIO_COPY क्रम
		 * a non-missing हाल. Return -EEXIST.
		 */
		अगर (vm_shared &&
		    hugetlbfs_pagecache_present(h, dst_vma, dst_addr)) अणु
			ret = -EEXIST;
			जाओ out;
		पूर्ण

		page = alloc_huge_page(dst_vma, dst_addr, 0);
		अगर (IS_ERR(page)) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		ret = copy_huge_page_from_user(page,
						(स्थिर व्योम __user *) src_addr,
						pages_per_huge_page(h), false);

		/* fallback to copy_from_user outside mmap_lock */
		अगर (unlikely(ret)) अणु
			ret = -ENOENT;
			*pagep = page;
			/* करोn't मुक्त the page */
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		page = *pagep;
		*pagep = शून्य;
	पूर्ण

	/*
	 * The memory barrier inside __SetPageUptodate makes sure that
	 * preceding stores to the page contents become visible beक्रमe
	 * the set_pte_at() ग_लिखो.
	 */
	__SetPageUptodate(page);

	/* Add shared, newly allocated pages to the page cache. */
	अगर (vm_shared && !is_जारी) अणु
		size = i_size_पढ़ो(mapping->host) >> huge_page_shअगरt(h);
		ret = -EFAULT;
		अगर (idx >= size)
			जाओ out_release_nounlock;

		/*
		 * Serialization between हटाओ_inode_hugepages() and
		 * huge_add_to_page_cache() below happens through the
		 * hugetlb_fault_mutex_table that here must be hold by
		 * the caller.
		 */
		ret = huge_add_to_page_cache(page, mapping, idx);
		अगर (ret)
			जाओ out_release_nounlock;
	पूर्ण

	ptl = huge_pte_lockptr(h, dst_mm, dst_pte);
	spin_lock(ptl);

	/*
	 * Recheck the i_size after holding PT lock to make sure not
	 * to leave any page mapped (as page_mapped()) beyond the end
	 * of the i_size (हटाओ_inode_hugepages() is strict about
	 * enक्रमcing that). If we bail out here, we'll also leave a
	 * page in the radix tree in the vm_shared हाल beyond the end
	 * of the i_size, but हटाओ_inode_hugepages() will take care
	 * of it as soon as we drop the hugetlb_fault_mutex_table.
	 */
	size = i_size_पढ़ो(mapping->host) >> huge_page_shअगरt(h);
	ret = -EFAULT;
	अगर (idx >= size)
		जाओ out_release_unlock;

	ret = -EEXIST;
	अगर (!huge_pte_none(huge_ptep_get(dst_pte)))
		जाओ out_release_unlock;

	अगर (vm_shared) अणु
		page_dup_rmap(page, true);
	पूर्ण अन्यथा अणु
		ClearHPageRestoreReserve(page);
		hugepage_add_new_anon_rmap(page, dst_vma, dst_addr);
	पूर्ण

	/* For CONTINUE on a non-shared VMA, करोn't set VM_WRITE क्रम CoW. */
	अगर (is_जारी && !vm_shared)
		writable = 0;
	अन्यथा
		writable = dst_vma->vm_flags & VM_WRITE;

	_dst_pte = make_huge_pte(dst_vma, page, writable);
	अगर (writable)
		_dst_pte = huge_pte_सूची_गढ़ोty(_dst_pte);
	_dst_pte = pte_mkyoung(_dst_pte);

	set_huge_pte_at(dst_mm, dst_addr, dst_pte, _dst_pte);

	(व्योम)huge_ptep_set_access_flags(dst_vma, dst_addr, dst_pte, _dst_pte,
					dst_vma->vm_flags & VM_WRITE);
	hugetlb_count_add(pages_per_huge_page(h), dst_mm);

	/* No need to invalidate - it was non-present beक्रमe */
	update_mmu_cache(dst_vma, dst_addr, dst_pte);

	spin_unlock(ptl);
	अगर (!is_जारी)
		SetHPageMigratable(page);
	अगर (vm_shared || is_जारी)
		unlock_page(page);
	ret = 0;
out:
	वापस ret;
out_release_unlock:
	spin_unlock(ptl);
	अगर (vm_shared || is_जारी)
		unlock_page(page);
out_release_nounlock:
	restore_reserve_on_error(h, dst_vma, dst_addr, page);
	put_page(page);
	जाओ out;
पूर्ण
#पूर्ण_अगर /* CONFIG_USERFAULTFD */

अटल व्योम record_subpages_vmas(काष्ठा page *page, काष्ठा vm_area_काष्ठा *vma,
				 पूर्णांक refs, काष्ठा page **pages,
				 काष्ठा vm_area_काष्ठा **vmas)
अणु
	पूर्णांक nr;

	क्रम (nr = 0; nr < refs; nr++) अणु
		अगर (likely(pages))
			pages[nr] = mem_map_offset(page, nr);
		अगर (vmas)
			vmas[nr] = vma;
	पूर्ण
पूर्ण

दीर्घ follow_hugetlb_page(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			 काष्ठा page **pages, काष्ठा vm_area_काष्ठा **vmas,
			 अचिन्हित दीर्घ *position, अचिन्हित दीर्घ *nr_pages,
			 दीर्घ i, अचिन्हित पूर्णांक flags, पूर्णांक *locked)
अणु
	अचिन्हित दीर्घ pfn_offset;
	अचिन्हित दीर्घ vaddr = *position;
	अचिन्हित दीर्घ reमुख्यder = *nr_pages;
	काष्ठा hstate *h = hstate_vma(vma);
	पूर्णांक err = -EFAULT, refs;

	जबतक (vaddr < vma->vm_end && reमुख्यder) अणु
		pte_t *pte;
		spinlock_t *ptl = शून्य;
		पूर्णांक असलent;
		काष्ठा page *page;

		/*
		 * If we have a pending SIGKILL, करोn't keep faulting pages and
		 * potentially allocating memory.
		 */
		अगर (fatal_संकेत_pending(current)) अणु
			reमुख्यder = 0;
			अवरोध;
		पूर्ण

		/*
		 * Some archs (sparc64, sh*) have multiple pte_ts to
		 * each hugepage.  We have to make sure we get the
		 * first, क्रम the page indexing below to work.
		 *
		 * Note that page table lock is not held when pte is null.
		 */
		pte = huge_pte_offset(mm, vaddr & huge_page_mask(h),
				      huge_page_size(h));
		अगर (pte)
			ptl = huge_pte_lock(h, mm, pte);
		असलent = !pte || huge_pte_none(huge_ptep_get(pte));

		/*
		 * When coredumping, it suits get_dump_page अगर we just वापस
		 * an error where there's an empty slot with no huge pagecache
		 * to back it.  This way, we aव्योम allocating a hugepage, and
		 * the sparse dumpfile aव्योमs allocating disk blocks, but its
		 * huge holes still show up with zeroes where they need to be.
		 */
		अगर (असलent && (flags & FOLL_DUMP) &&
		    !hugetlbfs_pagecache_present(h, vma, vaddr)) अणु
			अगर (pte)
				spin_unlock(ptl);
			reमुख्यder = 0;
			अवरोध;
		पूर्ण

		/*
		 * We need call hugetlb_fault क्रम both hugepages under migration
		 * (in which हाल hugetlb_fault रुकोs क्रम the migration,) and
		 * hwpoisoned hugepages (in which हाल we need to prevent the
		 * caller from accessing to them.) In order to करो this, we use
		 * here is_swap_pte instead of is_hugetlb_entry_migration and
		 * is_hugetlb_entry_hwpoisoned. This is because it simply covers
		 * both हालs, and because we can't follow correct pages
		 * directly from any kind of swap entries.
		 */
		अगर (असलent || is_swap_pte(huge_ptep_get(pte)) ||
		    ((flags & FOLL_WRITE) &&
		      !huge_pte_ग_लिखो(huge_ptep_get(pte)))) अणु
			vm_fault_t ret;
			अचिन्हित पूर्णांक fault_flags = 0;

			अगर (pte)
				spin_unlock(ptl);
			अगर (flags & FOLL_WRITE)
				fault_flags |= FAULT_FLAG_WRITE;
			अगर (locked)
				fault_flags |= FAULT_FLAG_ALLOW_RETRY |
					FAULT_FLAG_KILLABLE;
			अगर (flags & FOLL_NOWAIT)
				fault_flags |= FAULT_FLAG_ALLOW_RETRY |
					FAULT_FLAG_RETRY_NOWAIT;
			अगर (flags & FOLL_TRIED) अणु
				/*
				 * Note: FAULT_FLAG_ALLOW_RETRY and
				 * FAULT_FLAG_TRIED can co-exist
				 */
				fault_flags |= FAULT_FLAG_TRIED;
			पूर्ण
			ret = hugetlb_fault(mm, vma, vaddr, fault_flags);
			अगर (ret & VM_FAULT_ERROR) अणु
				err = vm_fault_to_त्रुटि_सं(ret, flags);
				reमुख्यder = 0;
				अवरोध;
			पूर्ण
			अगर (ret & VM_FAULT_RETRY) अणु
				अगर (locked &&
				    !(fault_flags & FAULT_FLAG_RETRY_NOWAIT))
					*locked = 0;
				*nr_pages = 0;
				/*
				 * VM_FAULT_RETRY must not वापस an
				 * error, it will वापस zero
				 * instead.
				 *
				 * No need to update "position" as the
				 * caller will not check it after
				 * *nr_pages is set to 0.
				 */
				वापस i;
			पूर्ण
			जारी;
		पूर्ण

		pfn_offset = (vaddr & ~huge_page_mask(h)) >> PAGE_SHIFT;
		page = pte_page(huge_ptep_get(pte));

		/*
		 * If subpage inक्रमmation not requested, update counters
		 * and skip the same_page loop below.
		 */
		अगर (!pages && !vmas && !pfn_offset &&
		    (vaddr + huge_page_size(h) < vma->vm_end) &&
		    (reमुख्यder >= pages_per_huge_page(h))) अणु
			vaddr += huge_page_size(h);
			reमुख्यder -= pages_per_huge_page(h);
			i += pages_per_huge_page(h);
			spin_unlock(ptl);
			जारी;
		पूर्ण

		refs = min3(pages_per_huge_page(h) - pfn_offset,
			    (vma->vm_end - vaddr) >> PAGE_SHIFT, reमुख्यder);

		अगर (pages || vmas)
			record_subpages_vmas(mem_map_offset(page, pfn_offset),
					     vma, refs,
					     likely(pages) ? pages + i : शून्य,
					     vmas ? vmas + i : शून्य);

		अगर (pages) अणु
			/*
			 * try_grab_compound_head() should always succeed here,
			 * because: a) we hold the ptl lock, and b) we've just
			 * checked that the huge page is present in the page
			 * tables. If the huge page is present, then the tail
			 * pages must also be present. The ptl prevents the
			 * head page and tail pages from being rearranged in
			 * any way. So this page must be available at this
			 * poपूर्णांक, unless the page refcount overflowed:
			 */
			अगर (WARN_ON_ONCE(!try_grab_compound_head(pages[i],
								 refs,
								 flags))) अणु
				spin_unlock(ptl);
				reमुख्यder = 0;
				err = -ENOMEM;
				अवरोध;
			पूर्ण
		पूर्ण

		vaddr += (refs << PAGE_SHIFT);
		reमुख्यder -= refs;
		i += refs;

		spin_unlock(ptl);
	पूर्ण
	*nr_pages = reमुख्यder;
	/*
	 * setting position is actually required only अगर reमुख्यder is
	 * not zero but it's faster not to add a "if (remainder)"
	 * branch.
	 */
	*position = vaddr;

	वापस i ? i : err;
पूर्ण

अचिन्हित दीर्घ hugetlb_change_protection(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, अचिन्हित दीर्घ end, pgprot_t newprot)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ start = address;
	pte_t *ptep;
	pte_t pte;
	काष्ठा hstate *h = hstate_vma(vma);
	अचिन्हित दीर्घ pages = 0;
	bool shared_pmd = false;
	काष्ठा mmu_notअगरier_range range;

	/*
	 * In the हाल of shared PMDs, the area to flush could be beyond
	 * start/end.  Set range.start/range.end to cover the maximum possible
	 * range अगर PMD sharing is possible.
	 */
	mmu_notअगरier_range_init(&range, MMU_NOTIFY_PROTECTION_VMA,
				0, vma, mm, start, end);
	adjust_range_अगर_pmd_sharing_possible(vma, &range.start, &range.end);

	BUG_ON(address >= end);
	flush_cache_range(vma, range.start, range.end);

	mmu_notअगरier_invalidate_range_start(&range);
	i_mmap_lock_ग_लिखो(vma->vm_file->f_mapping);
	क्रम (; address < end; address += huge_page_size(h)) अणु
		spinlock_t *ptl;
		ptep = huge_pte_offset(mm, address, huge_page_size(h));
		अगर (!ptep)
			जारी;
		ptl = huge_pte_lock(h, mm, ptep);
		अगर (huge_pmd_unshare(mm, vma, &address, ptep)) अणु
			pages++;
			spin_unlock(ptl);
			shared_pmd = true;
			जारी;
		पूर्ण
		pte = huge_ptep_get(ptep);
		अगर (unlikely(is_hugetlb_entry_hwpoisoned(pte))) अणु
			spin_unlock(ptl);
			जारी;
		पूर्ण
		अगर (unlikely(is_hugetlb_entry_migration(pte))) अणु
			swp_entry_t entry = pte_to_swp_entry(pte);

			अगर (is_ग_लिखो_migration_entry(entry)) अणु
				pte_t newpte;

				make_migration_entry_पढ़ो(&entry);
				newpte = swp_entry_to_pte(entry);
				set_huge_swap_pte_at(mm, address, ptep,
						     newpte, huge_page_size(h));
				pages++;
			पूर्ण
			spin_unlock(ptl);
			जारी;
		पूर्ण
		अगर (!huge_pte_none(pte)) अणु
			pte_t old_pte;

			old_pte = huge_ptep_modअगरy_prot_start(vma, address, ptep);
			pte = pte_mkhuge(huge_pte_modअगरy(old_pte, newprot));
			pte = arch_make_huge_pte(pte, vma, शून्य, 0);
			huge_ptep_modअगरy_prot_commit(vma, address, ptep, old_pte, pte);
			pages++;
		पूर्ण
		spin_unlock(ptl);
	पूर्ण
	/*
	 * Must flush TLB beक्रमe releasing i_mmap_rwsem: x86's huge_pmd_unshare
	 * may have cleared our pud entry and करोne put_page on the page table:
	 * once we release i_mmap_rwsem, another task can करो the final put_page
	 * and that page table be reused and filled with junk.  If we actually
	 * did unshare a page of pmds, flush the range corresponding to the pud.
	 */
	अगर (shared_pmd)
		flush_hugetlb_tlb_range(vma, range.start, range.end);
	अन्यथा
		flush_hugetlb_tlb_range(vma, start, end);
	/*
	 * No need to call mmu_notअगरier_invalidate_range() we are करोwngrading
	 * page table protection not changing it to poपूर्णांक to a new page.
	 *
	 * See Documentation/vm/mmu_notअगरier.rst
	 */
	i_mmap_unlock_ग_लिखो(vma->vm_file->f_mapping);
	mmu_notअगरier_invalidate_range_end(&range);

	वापस pages << h->order;
पूर्ण

/* Return true अगर reservation was successful, false otherwise.  */
bool hugetlb_reserve_pages(काष्ठा inode *inode,
					दीर्घ from, दीर्घ to,
					काष्ठा vm_area_काष्ठा *vma,
					vm_flags_t vm_flags)
अणु
	दीर्घ chg, add = -1;
	काष्ठा hstate *h = hstate_inode(inode);
	काष्ठा hugepage_subpool *spool = subpool_inode(inode);
	काष्ठा resv_map *resv_map;
	काष्ठा hugetlb_cgroup *h_cg = शून्य;
	दीर्घ gbl_reserve, regions_needed = 0;

	/* This should never happen */
	अगर (from > to) अणु
		VM_WARN(1, "%s called with a negative range\n", __func__);
		वापस false;
	पूर्ण

	/*
	 * Only apply hugepage reservation अगर asked. At fault समय, an
	 * attempt will be made क्रम VM_NORESERVE to allocate a page
	 * without using reserves
	 */
	अगर (vm_flags & VM_NORESERVE)
		वापस true;

	/*
	 * Shared mappings base their reservation on the number of pages that
	 * are alपढ़ोy allocated on behalf of the file. Private mappings need
	 * to reserve the full area even अगर पढ़ो-only as mprotect() may be
	 * called to make the mapping पढ़ो-ग_लिखो. Assume !vma is a shm mapping
	 */
	अगर (!vma || vma->vm_flags & VM_MAYSHARE) अणु
		/*
		 * resv_map can not be शून्य as hugetlb_reserve_pages is only
		 * called क्रम inodes क्रम which resv_maps were created (see
		 * hugetlbfs_get_inode).
		 */
		resv_map = inode_resv_map(inode);

		chg = region_chg(resv_map, from, to, &regions_needed);

	पूर्ण अन्यथा अणु
		/* Private mapping. */
		resv_map = resv_map_alloc();
		अगर (!resv_map)
			वापस false;

		chg = to - from;

		set_vma_resv_map(vma, resv_map);
		set_vma_resv_flags(vma, HPAGE_RESV_OWNER);
	पूर्ण

	अगर (chg < 0)
		जाओ out_err;

	अगर (hugetlb_cgroup_अक्षरge_cgroup_rsvd(hstate_index(h),
				chg * pages_per_huge_page(h), &h_cg) < 0)
		जाओ out_err;

	अगर (vma && !(vma->vm_flags & VM_MAYSHARE) && h_cg) अणु
		/* For निजी mappings, the hugetlb_cgroup unअक्षरge info hangs
		 * of the resv_map.
		 */
		resv_map_set_hugetlb_cgroup_unअक्षरge_info(resv_map, h_cg, h);
	पूर्ण

	/*
	 * There must be enough pages in the subpool क्रम the mapping. If
	 * the subpool has a minimum size, there may be some global
	 * reservations alपढ़ोy in place (gbl_reserve).
	 */
	gbl_reserve = hugepage_subpool_get_pages(spool, chg);
	अगर (gbl_reserve < 0)
		जाओ out_unअक्षरge_cgroup;

	/*
	 * Check enough hugepages are available क्रम the reservation.
	 * Hand the pages back to the subpool अगर there are not
	 */
	अगर (hugetlb_acct_memory(h, gbl_reserve) < 0)
		जाओ out_put_pages;

	/*
	 * Account क्रम the reservations made. Shared mappings record regions
	 * that have reservations as they are shared by multiple VMAs.
	 * When the last VMA disappears, the region map says how much
	 * the reservation was and the page cache tells how much of
	 * the reservation was consumed. Private mappings are per-VMA and
	 * only the consumed reservations are tracked. When the VMA
	 * disappears, the original reservation is the VMA size and the
	 * consumed reservations are stored in the map. Hence, nothing
	 * अन्यथा has to be करोne क्रम निजी mappings here
	 */
	अगर (!vma || vma->vm_flags & VM_MAYSHARE) अणु
		add = region_add(resv_map, from, to, regions_needed, h, h_cg);

		अगर (unlikely(add < 0)) अणु
			hugetlb_acct_memory(h, -gbl_reserve);
			जाओ out_put_pages;
		पूर्ण अन्यथा अगर (unlikely(chg > add)) अणु
			/*
			 * pages in this range were added to the reserve
			 * map between region_chg and region_add.  This
			 * indicates a race with alloc_huge_page.  Adjust
			 * the subpool and reserve counts modअगरied above
			 * based on the dअगरference.
			 */
			दीर्घ rsv_adjust;

			/*
			 * hugetlb_cgroup_unअक्षरge_cgroup_rsvd() will put the
			 * reference to h_cg->css. See comment below क्रम detail.
			 */
			hugetlb_cgroup_unअक्षरge_cgroup_rsvd(
				hstate_index(h),
				(chg - add) * pages_per_huge_page(h), h_cg);

			rsv_adjust = hugepage_subpool_put_pages(spool,
								chg - add);
			hugetlb_acct_memory(h, -rsv_adjust);
		पूर्ण अन्यथा अगर (h_cg) अणु
			/*
			 * The file_regions will hold their own reference to
			 * h_cg->css. So we should release the reference held
			 * via hugetlb_cgroup_अक्षरge_cgroup_rsvd() when we are
			 * करोne.
			 */
			hugetlb_cgroup_put_rsvd_cgroup(h_cg);
		पूर्ण
	पूर्ण
	वापस true;

out_put_pages:
	/* put back original number of pages, chg */
	(व्योम)hugepage_subpool_put_pages(spool, chg);
out_unअक्षरge_cgroup:
	hugetlb_cgroup_unअक्षरge_cgroup_rsvd(hstate_index(h),
					    chg * pages_per_huge_page(h), h_cg);
out_err:
	अगर (!vma || vma->vm_flags & VM_MAYSHARE)
		/* Only call region_पात अगर the region_chg succeeded but the
		 * region_add failed or didn't run.
		 */
		अगर (chg >= 0 && add < 0)
			region_पात(resv_map, from, to, regions_needed);
	अगर (vma && is_vma_resv_set(vma, HPAGE_RESV_OWNER))
		kref_put(&resv_map->refs, resv_map_release);
	वापस false;
पूर्ण

दीर्घ hugetlb_unreserve_pages(काष्ठा inode *inode, दीर्घ start, दीर्घ end,
								दीर्घ मुक्तd)
अणु
	काष्ठा hstate *h = hstate_inode(inode);
	काष्ठा resv_map *resv_map = inode_resv_map(inode);
	दीर्घ chg = 0;
	काष्ठा hugepage_subpool *spool = subpool_inode(inode);
	दीर्घ gbl_reserve;

	/*
	 * Since this routine can be called in the evict inode path क्रम all
	 * hugetlbfs inodes, resv_map could be शून्य.
	 */
	अगर (resv_map) अणु
		chg = region_del(resv_map, start, end);
		/*
		 * region_del() can fail in the rare हाल where a region
		 * must be split and another region descriptor can not be
		 * allocated.  If end == दीर्घ_उच्च, it will not fail.
		 */
		अगर (chg < 0)
			वापस chg;
	पूर्ण

	spin_lock(&inode->i_lock);
	inode->i_blocks -= (blocks_per_huge_page(h) * मुक्तd);
	spin_unlock(&inode->i_lock);

	/*
	 * If the subpool has a minimum size, the number of global
	 * reservations to be released may be adjusted.
	 *
	 * Note that !resv_map implies मुक्तd == 0. So (chg - मुक्तd)
	 * won't go negative.
	 */
	gbl_reserve = hugepage_subpool_put_pages(spool, (chg - मुक्तd));
	hugetlb_acct_memory(h, -gbl_reserve);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ARCH_WANT_HUGE_PMD_SHARE
अटल अचिन्हित दीर्घ page_table_shareable(काष्ठा vm_area_काष्ठा *svma,
				काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ addr, pgoff_t idx)
अणु
	अचिन्हित दीर्घ saddr = ((idx - svma->vm_pgoff) << PAGE_SHIFT) +
				svma->vm_start;
	अचिन्हित दीर्घ sbase = saddr & PUD_MASK;
	अचिन्हित दीर्घ s_end = sbase + PUD_SIZE;

	/* Allow segments to share अगर only one is marked locked */
	अचिन्हित दीर्घ vm_flags = vma->vm_flags & VM_LOCKED_CLEAR_MASK;
	अचिन्हित दीर्घ svm_flags = svma->vm_flags & VM_LOCKED_CLEAR_MASK;

	/*
	 * match the भव addresses, permission and the alignment of the
	 * page table page.
	 */
	अगर (pmd_index(addr) != pmd_index(saddr) ||
	    vm_flags != svm_flags ||
	    !range_in_vma(svma, sbase, s_end))
		वापस 0;

	वापस saddr;
पूर्ण

अटल bool vma_shareable(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ base = addr & PUD_MASK;
	अचिन्हित दीर्घ end = base + PUD_SIZE;

	/*
	 * check on proper vm_flags and page table alignment
	 */
	अगर (vma->vm_flags & VM_MAYSHARE && range_in_vma(vma, base, end))
		वापस true;
	वापस false;
पूर्ण

bool want_pmd_share(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
#अगर_घोषित CONFIG_USERFAULTFD
	अगर (uffd_disable_huge_pmd_share(vma))
		वापस false;
#पूर्ण_अगर
	वापस vma_shareable(vma, addr);
पूर्ण

/*
 * Determine अगर start,end range within vma could be mapped by shared pmd.
 * If yes, adjust start and end to cover range associated with possible
 * shared pmd mappings.
 */
व्योम adjust_range_अगर_pmd_sharing_possible(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ *start, अचिन्हित दीर्घ *end)
अणु
	अचिन्हित दीर्घ v_start = ALIGN(vma->vm_start, PUD_SIZE),
		v_end = ALIGN_DOWN(vma->vm_end, PUD_SIZE);

	/*
	 * vma needs to span at least one aligned PUD size, and the range
	 * must be at least partially within in.
	 */
	अगर (!(vma->vm_flags & VM_MAYSHARE) || !(v_end > v_start) ||
		(*end <= v_start) || (*start >= v_end))
		वापस;

	/* Extend the range to be PUD aligned क्रम a worst हाल scenario */
	अगर (*start > v_start)
		*start = ALIGN_DOWN(*start, PUD_SIZE);

	अगर (*end < v_end)
		*end = ALIGN(*end, PUD_SIZE);
पूर्ण

/*
 * Search क्रम a shareable pmd page क्रम hugetlb. In any हाल calls pmd_alloc()
 * and वापसs the corresponding pte. While this is not necessary क्रम the
 * !shared pmd हाल because we can allocate the pmd later as well, it makes the
 * code much cleaner.
 *
 * This routine must be called with i_mmap_rwsem held in at least पढ़ो mode अगर
 * sharing is possible.  For hugetlbfs, this prevents removal of any page
 * table entries associated with the address space.  This is important as we
 * are setting up sharing based on existing page table entries (mappings).
 *
 * NOTE: This routine is only called from huge_pte_alloc.  Some callers of
 * huge_pte_alloc know that sharing is not possible and करो not take
 * i_mmap_rwsem as a perक्रमmance optimization.  This is handled by the
 * अगर !vma_shareable check at the beginning of the routine. i_mmap_rwsem is
 * only required क्रम subsequent processing.
 */
pte_t *huge_pmd_share(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ addr, pud_t *pud)
अणु
	काष्ठा address_space *mapping = vma->vm_file->f_mapping;
	pgoff_t idx = ((addr - vma->vm_start) >> PAGE_SHIFT) +
			vma->vm_pgoff;
	काष्ठा vm_area_काष्ठा *svma;
	अचिन्हित दीर्घ saddr;
	pte_t *spte = शून्य;
	pte_t *pte;
	spinlock_t *ptl;

	i_mmap_निश्चित_locked(mapping);
	vma_पूर्णांकerval_tree_क्रमeach(svma, &mapping->i_mmap, idx, idx) अणु
		अगर (svma == vma)
			जारी;

		saddr = page_table_shareable(svma, vma, addr, idx);
		अगर (saddr) अणु
			spte = huge_pte_offset(svma->vm_mm, saddr,
					       vma_mmu_pagesize(svma));
			अगर (spte) अणु
				get_page(virt_to_page(spte));
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!spte)
		जाओ out;

	ptl = huge_pte_lock(hstate_vma(vma), mm, spte);
	अगर (pud_none(*pud)) अणु
		pud_populate(mm, pud,
				(pmd_t *)((अचिन्हित दीर्घ)spte & PAGE_MASK));
		mm_inc_nr_pmds(mm);
	पूर्ण अन्यथा अणु
		put_page(virt_to_page(spte));
	पूर्ण
	spin_unlock(ptl);
out:
	pte = (pte_t *)pmd_alloc(mm, pud, addr);
	वापस pte;
पूर्ण

/*
 * unmap huge page backed by shared pte.
 *
 * Hugetlb pte page is ref counted at the समय of mapping.  If pte is shared
 * indicated by page_count > 1, unmap is achieved by clearing pud and
 * decrementing the ref count. If count == 1, the pte page is not shared.
 *
 * Called with page table lock held and i_mmap_rwsem held in ग_लिखो mode.
 *
 * वापसs: 1 successfully unmapped a shared pte page
 *	    0 the underlying pte page is not shared, or it is the last user
 */
पूर्णांक huge_pmd_unshare(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ *addr, pte_t *ptep)
अणु
	pgd_t *pgd = pgd_offset(mm, *addr);
	p4d_t *p4d = p4d_offset(pgd, *addr);
	pud_t *pud = pud_offset(p4d, *addr);

	i_mmap_निश्चित_ग_लिखो_locked(vma->vm_file->f_mapping);
	BUG_ON(page_count(virt_to_page(ptep)) == 0);
	अगर (page_count(virt_to_page(ptep)) == 1)
		वापस 0;

	pud_clear(pud);
	put_page(virt_to_page(ptep));
	mm_dec_nr_pmds(mm);
	*addr = ALIGN(*addr, HPAGE_SIZE * PTRS_PER_PTE) - HPAGE_SIZE;
	वापस 1;
पूर्ण

#अन्यथा /* !CONFIG_ARCH_WANT_HUGE_PMD_SHARE */
pte_t *huge_pmd_share(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ addr, pud_t *pud)
अणु
	वापस शून्य;
पूर्ण

पूर्णांक huge_pmd_unshare(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ *addr, pte_t *ptep)
अणु
	वापस 0;
पूर्ण

व्योम adjust_range_अगर_pmd_sharing_possible(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ *start, अचिन्हित दीर्घ *end)
अणु
पूर्ण

bool want_pmd_share(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_WANT_HUGE_PMD_SHARE */

#अगर_घोषित CONFIG_ARCH_WANT_GENERAL_HUGETLB
pte_t *huge_pte_alloc(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pte_t *pte = शून्य;

	pgd = pgd_offset(mm, addr);
	p4d = p4d_alloc(mm, pgd, addr);
	अगर (!p4d)
		वापस शून्य;
	pud = pud_alloc(mm, p4d, addr);
	अगर (pud) अणु
		अगर (sz == PUD_SIZE) अणु
			pte = (pte_t *)pud;
		पूर्ण अन्यथा अणु
			BUG_ON(sz != PMD_SIZE);
			अगर (want_pmd_share(vma, addr) && pud_none(*pud))
				pte = huge_pmd_share(mm, vma, addr, pud);
			अन्यथा
				pte = (pte_t *)pmd_alloc(mm, pud, addr);
		पूर्ण
	पूर्ण
	BUG_ON(pte && pte_present(*pte) && !pte_huge(*pte));

	वापस pte;
पूर्ण

/*
 * huge_pte_offset() - Walk the page table to resolve the hugepage
 * entry at address @addr
 *
 * Return: Poपूर्णांकer to page table entry (PUD or PMD) क्रम
 * address @addr, or शून्य अगर a !p*d_present() entry is encountered and the
 * size @sz करोesn't match the hugepage size at this level of the page
 * table.
 */
pte_t *huge_pte_offset(काष्ठा mm_काष्ठा *mm,
		       अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset(mm, addr);
	अगर (!pgd_present(*pgd))
		वापस शून्य;
	p4d = p4d_offset(pgd, addr);
	अगर (!p4d_present(*p4d))
		वापस शून्य;

	pud = pud_offset(p4d, addr);
	अगर (sz == PUD_SIZE)
		/* must be pud huge, non-present or none */
		वापस (pte_t *)pud;
	अगर (!pud_present(*pud))
		वापस शून्य;
	/* must have a valid entry and size to go further */

	pmd = pmd_offset(pud, addr);
	/* must be pmd huge, non-present or none */
	वापस (pte_t *)pmd;
पूर्ण

#पूर्ण_अगर /* CONFIG_ARCH_WANT_GENERAL_HUGETLB */

/*
 * These functions are overwritable अगर your architecture needs its own
 * behavior.
 */
काष्ठा page * __weak
follow_huge_addr(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
			      पूर्णांक ग_लिखो)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

काष्ठा page * __weak
follow_huge_pd(काष्ठा vm_area_काष्ठा *vma,
	       अचिन्हित दीर्घ address, hugepd_t hpd, पूर्णांक flags, पूर्णांक pdshअगरt)
अणु
	WARN(1, "hugepd follow called with no support for hugepage directory format\n");
	वापस शून्य;
पूर्ण

काष्ठा page * __weak
follow_huge_pmd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
		pmd_t *pmd, पूर्णांक flags)
अणु
	काष्ठा page *page = शून्य;
	spinlock_t *ptl;
	pte_t pte;

	/* FOLL_GET and FOLL_PIN are mutually exclusive. */
	अगर (WARN_ON_ONCE((flags & (FOLL_PIN | FOLL_GET)) ==
			 (FOLL_PIN | FOLL_GET)))
		वापस शून्य;

retry:
	ptl = pmd_lockptr(mm, pmd);
	spin_lock(ptl);
	/*
	 * make sure that the address range covered by this pmd is not
	 * unmapped from other thपढ़ोs.
	 */
	अगर (!pmd_huge(*pmd))
		जाओ out;
	pte = huge_ptep_get((pte_t *)pmd);
	अगर (pte_present(pte)) अणु
		page = pmd_page(*pmd) + ((address & ~PMD_MASK) >> PAGE_SHIFT);
		/*
		 * try_grab_page() should always succeed here, because: a) we
		 * hold the pmd (ptl) lock, and b) we've just checked that the
		 * huge pmd (head) page is present in the page tables. The ptl
		 * prevents the head page and tail pages from being rearranged
		 * in any way. So this page must be available at this poपूर्णांक,
		 * unless the page refcount overflowed:
		 */
		अगर (WARN_ON_ONCE(!try_grab_page(page, flags))) अणु
			page = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (is_hugetlb_entry_migration(pte)) अणु
			spin_unlock(ptl);
			__migration_entry_रुको(mm, (pte_t *)pmd, ptl);
			जाओ retry;
		पूर्ण
		/*
		 * hwpoisoned entry is treated as no_page_table in
		 * follow_page_mask().
		 */
	पूर्ण
out:
	spin_unlock(ptl);
	वापस page;
पूर्ण

काष्ठा page * __weak
follow_huge_pud(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
		pud_t *pud, पूर्णांक flags)
अणु
	अगर (flags & (FOLL_GET | FOLL_PIN))
		वापस शून्य;

	वापस pte_page(*(pte_t *)pud) + ((address & ~PUD_MASK) >> PAGE_SHIFT);
पूर्ण

काष्ठा page * __weak
follow_huge_pgd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address, pgd_t *pgd, पूर्णांक flags)
अणु
	अगर (flags & (FOLL_GET | FOLL_PIN))
		वापस शून्य;

	वापस pte_page(*(pte_t *)pgd) + ((address & ~PGसूची_MASK) >> PAGE_SHIFT);
पूर्ण

bool isolate_huge_page(काष्ठा page *page, काष्ठा list_head *list)
अणु
	bool ret = true;

	spin_lock_irq(&hugetlb_lock);
	अगर (!PageHeadHuge(page) ||
	    !HPageMigratable(page) ||
	    !get_page_unless_zero(page)) अणु
		ret = false;
		जाओ unlock;
	पूर्ण
	ClearHPageMigratable(page);
	list_move_tail(&page->lru, list);
unlock:
	spin_unlock_irq(&hugetlb_lock);
	वापस ret;
पूर्ण

पूर्णांक get_hwpoison_huge_page(काष्ठा page *page, bool *hugetlb)
अणु
	पूर्णांक ret = 0;

	*hugetlb = false;
	spin_lock_irq(&hugetlb_lock);
	अगर (PageHeadHuge(page)) अणु
		*hugetlb = true;
		अगर (HPageFreed(page) || HPageMigratable(page))
			ret = get_page_unless_zero(page);
	पूर्ण
	spin_unlock_irq(&hugetlb_lock);
	वापस ret;
पूर्ण

व्योम putback_active_hugepage(काष्ठा page *page)
अणु
	spin_lock_irq(&hugetlb_lock);
	SetHPageMigratable(page);
	list_move_tail(&page->lru, &(page_hstate(page))->hugepage_activelist);
	spin_unlock_irq(&hugetlb_lock);
	put_page(page);
पूर्ण

व्योम move_hugetlb_state(काष्ठा page *oldpage, काष्ठा page *newpage, पूर्णांक reason)
अणु
	काष्ठा hstate *h = page_hstate(oldpage);

	hugetlb_cgroup_migrate(oldpage, newpage);
	set_page_owner_migrate_reason(newpage, reason);

	/*
	 * transfer temporary state of the new huge page. This is
	 * reverse to other transitions because the newpage is going to
	 * be final जबतक the old one will be मुक्तd so it takes over
	 * the temporary status.
	 *
	 * Also note that we have to transfer the per-node surplus state
	 * here as well otherwise the global surplus count will not match
	 * the per-node's.
	 */
	अगर (HPageTemporary(newpage)) अणु
		पूर्णांक old_nid = page_to_nid(oldpage);
		पूर्णांक new_nid = page_to_nid(newpage);

		SetHPageTemporary(oldpage);
		ClearHPageTemporary(newpage);

		/*
		 * There is no need to transfer the per-node surplus state
		 * when we करो not cross the node.
		 */
		अगर (new_nid == old_nid)
			वापस;
		spin_lock_irq(&hugetlb_lock);
		अगर (h->surplus_huge_pages_node[old_nid]) अणु
			h->surplus_huge_pages_node[old_nid]--;
			h->surplus_huge_pages_node[new_nid]++;
		पूर्ण
		spin_unlock_irq(&hugetlb_lock);
	पूर्ण
पूर्ण

/*
 * This function will unconditionally हटाओ all the shared pmd pgtable entries
 * within the specअगरic vma क्रम a hugetlbfs memory range.
 */
व्योम hugetlb_unshare_all_pmds(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा hstate *h = hstate_vma(vma);
	अचिन्हित दीर्घ sz = huge_page_size(h);
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा mmu_notअगरier_range range;
	अचिन्हित दीर्घ address, start, end;
	spinlock_t *ptl;
	pte_t *ptep;

	अगर (!(vma->vm_flags & VM_MAYSHARE))
		वापस;

	start = ALIGN(vma->vm_start, PUD_SIZE);
	end = ALIGN_DOWN(vma->vm_end, PUD_SIZE);

	अगर (start >= end)
		वापस;

	/*
	 * No need to call adjust_range_अगर_pmd_sharing_possible(), because
	 * we have alपढ़ोy करोne the PUD_SIZE alignment.
	 */
	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, mm,
				start, end);
	mmu_notअगरier_invalidate_range_start(&range);
	i_mmap_lock_ग_लिखो(vma->vm_file->f_mapping);
	क्रम (address = start; address < end; address += PUD_SIZE) अणु
		अचिन्हित दीर्घ पंचांगp = address;

		ptep = huge_pte_offset(mm, address, sz);
		अगर (!ptep)
			जारी;
		ptl = huge_pte_lock(h, mm, ptep);
		/* We करोn't want 'address' to be changed */
		huge_pmd_unshare(mm, vma, &पंचांगp, ptep);
		spin_unlock(ptl);
	पूर्ण
	flush_hugetlb_tlb_range(vma, start, end);
	i_mmap_unlock_ग_लिखो(vma->vm_file->f_mapping);
	/*
	 * No need to call mmu_notअगरier_invalidate_range(), see
	 * Documentation/vm/mmu_notअगरier.rst.
	 */
	mmu_notअगरier_invalidate_range_end(&range);
पूर्ण

#अगर_घोषित CONFIG_CMA
अटल bool cma_reserve_called __initdata;

अटल पूर्णांक __init cmdline_parse_hugetlb_cma(अक्षर *p)
अणु
	hugetlb_cma_size = memparse(p, &p);
	वापस 0;
पूर्ण

early_param("hugetlb_cma", cmdline_parse_hugetlb_cma);

व्योम __init hugetlb_cma_reserve(पूर्णांक order)
अणु
	अचिन्हित दीर्घ size, reserved, per_node;
	पूर्णांक nid;

	cma_reserve_called = true;

	अगर (!hugetlb_cma_size)
		वापस;

	अगर (hugetlb_cma_size < (PAGE_SIZE << order)) अणु
		pr_warn("hugetlb_cma: cma area should be at least %lu MiB\n",
			(PAGE_SIZE << order) / SZ_1M);
		वापस;
	पूर्ण

	/*
	 * If 3 GB area is requested on a machine with 4 numa nodes,
	 * let's allocate 1 GB on first three nodes and ignore the last one.
	 */
	per_node = DIV_ROUND_UP(hugetlb_cma_size, nr_online_nodes);
	pr_info("hugetlb_cma: reserve %lu MiB, up to %lu MiB per node\n",
		hugetlb_cma_size / SZ_1M, per_node / SZ_1M);

	reserved = 0;
	क्रम_each_node_state(nid, N_ONLINE) अणु
		पूर्णांक res;
		अक्षर name[CMA_MAX_NAME];

		size = min(per_node, hugetlb_cma_size - reserved);
		size = round_up(size, PAGE_SIZE << order);

		snम_लिखो(name, माप(name), "hugetlb%d", nid);
		res = cma_declare_contiguous_nid(0, size, 0, PAGE_SIZE << order,
						 0, false, name,
						 &hugetlb_cma[nid], nid);
		अगर (res) अणु
			pr_warn("hugetlb_cma: reservation failed: err %d, node %d",
				res, nid);
			जारी;
		पूर्ण

		reserved += size;
		pr_info("hugetlb_cma: reserved %lu MiB on node %d\n",
			size / SZ_1M, nid);

		अगर (reserved >= hugetlb_cma_size)
			अवरोध;
	पूर्ण
पूर्ण

व्योम __init hugetlb_cma_check(व्योम)
अणु
	अगर (!hugetlb_cma_size || cma_reserve_called)
		वापस;

	pr_warn("hugetlb_cma: the option isn't supported by current arch\n");
पूर्ण

#पूर्ण_अगर /* CONFIG_CMA */
