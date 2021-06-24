<शैली गुरु>
/*
 *
 * Copyright IBM Corporation, 2012
 * Author Aneesh Kumar K.V <aneesh.kumar@linux.vnet.ibm.com>
 *
 * Cgroup v2
 * Copyright (C) 2019 Red Hat, Inc.
 * Author: Giuseppe Scrivano <gscrivan@redhat.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#समावेश <linux/cgroup.h>
#समावेश <linux/page_counter.h>
#समावेश <linux/slab.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/hugetlb_cgroup.h>

#घोषणा MEMखाता_PRIVATE(x, val)	(((x) << 16) | (val))
#घोषणा MEMखाता_IDX(val)	(((val) >> 16) & 0xffff)
#घोषणा MEMखाता_ATTR(val)	((val) & 0xffff)

#घोषणा hugetlb_cgroup_from_counter(counter, idx)                   \
	container_of(counter, काष्ठा hugetlb_cgroup, hugepage[idx])

अटल काष्ठा hugetlb_cgroup *root_h_cgroup __पढ़ो_mostly;

अटल अंतरभूत काष्ठा page_counter *
__hugetlb_cgroup_counter_from_cgroup(काष्ठा hugetlb_cgroup *h_cg, पूर्णांक idx,
				     bool rsvd)
अणु
	अगर (rsvd)
		वापस &h_cg->rsvd_hugepage[idx];
	वापस &h_cg->hugepage[idx];
पूर्ण

अटल अंतरभूत काष्ठा page_counter *
hugetlb_cgroup_counter_from_cgroup(काष्ठा hugetlb_cgroup *h_cg, पूर्णांक idx)
अणु
	वापस __hugetlb_cgroup_counter_from_cgroup(h_cg, idx, false);
पूर्ण

अटल अंतरभूत काष्ठा page_counter *
hugetlb_cgroup_counter_from_cgroup_rsvd(काष्ठा hugetlb_cgroup *h_cg, पूर्णांक idx)
अणु
	वापस __hugetlb_cgroup_counter_from_cgroup(h_cg, idx, true);
पूर्ण

अटल अंतरभूत
काष्ठा hugetlb_cgroup *hugetlb_cgroup_from_css(काष्ठा cgroup_subsys_state *s)
अणु
	वापस s ? container_of(s, काष्ठा hugetlb_cgroup, css) : शून्य;
पूर्ण

अटल अंतरभूत
काष्ठा hugetlb_cgroup *hugetlb_cgroup_from_task(काष्ठा task_काष्ठा *task)
अणु
	वापस hugetlb_cgroup_from_css(task_css(task, hugetlb_cgrp_id));
पूर्ण

अटल अंतरभूत bool hugetlb_cgroup_is_root(काष्ठा hugetlb_cgroup *h_cg)
अणु
	वापस (h_cg == root_h_cgroup);
पूर्ण

अटल अंतरभूत काष्ठा hugetlb_cgroup *
parent_hugetlb_cgroup(काष्ठा hugetlb_cgroup *h_cg)
अणु
	वापस hugetlb_cgroup_from_css(h_cg->css.parent);
पूर्ण

अटल अंतरभूत bool hugetlb_cgroup_have_usage(काष्ठा hugetlb_cgroup *h_cg)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < hugetlb_max_hstate; idx++) अणु
		अगर (page_counter_पढ़ो(
				hugetlb_cgroup_counter_from_cgroup(h_cg, idx)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम hugetlb_cgroup_init(काष्ठा hugetlb_cgroup *h_cgroup,
				काष्ठा hugetlb_cgroup *parent_h_cgroup)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < HUGE_MAX_HSTATE; idx++) अणु
		काष्ठा page_counter *fault_parent = शून्य;
		काष्ठा page_counter *rsvd_parent = शून्य;
		अचिन्हित दीर्घ limit;
		पूर्णांक ret;

		अगर (parent_h_cgroup) अणु
			fault_parent = hugetlb_cgroup_counter_from_cgroup(
				parent_h_cgroup, idx);
			rsvd_parent = hugetlb_cgroup_counter_from_cgroup_rsvd(
				parent_h_cgroup, idx);
		पूर्ण
		page_counter_init(hugetlb_cgroup_counter_from_cgroup(h_cgroup,
								     idx),
				  fault_parent);
		page_counter_init(
			hugetlb_cgroup_counter_from_cgroup_rsvd(h_cgroup, idx),
			rsvd_parent);

		limit = round_करोwn(PAGE_COUNTER_MAX,
				   pages_per_huge_page(&hstates[idx]));

		ret = page_counter_set_max(
			hugetlb_cgroup_counter_from_cgroup(h_cgroup, idx),
			limit);
		VM_BUG_ON(ret);
		ret = page_counter_set_max(
			hugetlb_cgroup_counter_from_cgroup_rsvd(h_cgroup, idx),
			limit);
		VM_BUG_ON(ret);
	पूर्ण
पूर्ण

अटल काष्ठा cgroup_subsys_state *
hugetlb_cgroup_css_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	काष्ठा hugetlb_cgroup *parent_h_cgroup = hugetlb_cgroup_from_css(parent_css);
	काष्ठा hugetlb_cgroup *h_cgroup;

	h_cgroup = kzalloc(माप(*h_cgroup), GFP_KERNEL);
	अगर (!h_cgroup)
		वापस ERR_PTR(-ENOMEM);

	अगर (!parent_h_cgroup)
		root_h_cgroup = h_cgroup;

	hugetlb_cgroup_init(h_cgroup, parent_h_cgroup);
	वापस &h_cgroup->css;
पूर्ण

अटल व्योम hugetlb_cgroup_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा hugetlb_cgroup *h_cgroup;

	h_cgroup = hugetlb_cgroup_from_css(css);
	kमुक्त(h_cgroup);
पूर्ण

/*
 * Should be called with hugetlb_lock held.
 * Since we are holding hugetlb_lock, pages cannot get moved from
 * active list or unअक्षरged from the cgroup, So no need to get
 * page reference and test क्रम page active here. This function
 * cannot fail.
 */
अटल व्योम hugetlb_cgroup_move_parent(पूर्णांक idx, काष्ठा hugetlb_cgroup *h_cg,
				       काष्ठा page *page)
अणु
	अचिन्हित पूर्णांक nr_pages;
	काष्ठा page_counter *counter;
	काष्ठा hugetlb_cgroup *page_hcg;
	काष्ठा hugetlb_cgroup *parent = parent_hugetlb_cgroup(h_cg);

	page_hcg = hugetlb_cgroup_from_page(page);
	/*
	 * We can have pages in active list without any cgroup
	 * ie, hugepage with less than 3 pages. We can safely
	 * ignore those pages.
	 */
	अगर (!page_hcg || page_hcg != h_cg)
		जाओ out;

	nr_pages = compound_nr(page);
	अगर (!parent) अणु
		parent = root_h_cgroup;
		/* root has no limit */
		page_counter_अक्षरge(&parent->hugepage[idx], nr_pages);
	पूर्ण
	counter = &h_cg->hugepage[idx];
	/* Take the pages off the local counter */
	page_counter_cancel(counter, nr_pages);

	set_hugetlb_cgroup(page, parent);
out:
	वापस;
पूर्ण

/*
 * Force the hugetlb cgroup to empty the hugetlb resources by moving them to
 * the parent cgroup.
 */
अटल व्योम hugetlb_cgroup_css_offline(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा hugetlb_cgroup *h_cg = hugetlb_cgroup_from_css(css);
	काष्ठा hstate *h;
	काष्ठा page *page;
	पूर्णांक idx;

	करो अणु
		idx = 0;
		क्रम_each_hstate(h) अणु
			spin_lock_irq(&hugetlb_lock);
			list_क्रम_each_entry(page, &h->hugepage_activelist, lru)
				hugetlb_cgroup_move_parent(idx, h_cg, page);

			spin_unlock_irq(&hugetlb_lock);
			idx++;
		पूर्ण
		cond_resched();
	पूर्ण जबतक (hugetlb_cgroup_have_usage(h_cg));
पूर्ण

अटल अंतरभूत व्योम hugetlb_event(काष्ठा hugetlb_cgroup *hugetlb, पूर्णांक idx,
				 क्रमागत hugetlb_memory_event event)
अणु
	atomic_दीर्घ_inc(&hugetlb->events_local[idx][event]);
	cgroup_file_notअगरy(&hugetlb->events_local_file[idx]);

	करो अणु
		atomic_दीर्घ_inc(&hugetlb->events[idx][event]);
		cgroup_file_notअगरy(&hugetlb->events_file[idx]);
	पूर्ण जबतक ((hugetlb = parent_hugetlb_cgroup(hugetlb)) &&
		 !hugetlb_cgroup_is_root(hugetlb));
पूर्ण

अटल पूर्णांक __hugetlb_cgroup_अक्षरge_cgroup(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					  काष्ठा hugetlb_cgroup **ptr,
					  bool rsvd)
अणु
	पूर्णांक ret = 0;
	काष्ठा page_counter *counter;
	काष्ठा hugetlb_cgroup *h_cg = शून्य;

	अगर (hugetlb_cgroup_disabled())
		जाओ करोne;
	/*
	 * We करोn't अक्षरge any cgroup अगर the compound page have less
	 * than 3 pages.
	 */
	अगर (huge_page_order(&hstates[idx]) < HUGETLB_CGROUP_MIN_ORDER)
		जाओ करोne;
again:
	rcu_पढ़ो_lock();
	h_cg = hugetlb_cgroup_from_task(current);
	अगर (!css_tryget(&h_cg->css)) अणु
		rcu_पढ़ो_unlock();
		जाओ again;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!page_counter_try_अक्षरge(
		    __hugetlb_cgroup_counter_from_cgroup(h_cg, idx, rsvd),
		    nr_pages, &counter)) अणु
		ret = -ENOMEM;
		hugetlb_event(h_cg, idx, HUGETLB_MAX);
		css_put(&h_cg->css);
		जाओ करोne;
	पूर्ण
	/* Reservations take a reference to the css because they करो not get
	 * reparented.
	 */
	अगर (!rsvd)
		css_put(&h_cg->css);
करोne:
	*ptr = h_cg;
	वापस ret;
पूर्ण

पूर्णांक hugetlb_cgroup_अक्षरge_cgroup(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
				 काष्ठा hugetlb_cgroup **ptr)
अणु
	वापस __hugetlb_cgroup_अक्षरge_cgroup(idx, nr_pages, ptr, false);
पूर्ण

पूर्णांक hugetlb_cgroup_अक्षरge_cgroup_rsvd(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
				      काष्ठा hugetlb_cgroup **ptr)
अणु
	वापस __hugetlb_cgroup_अक्षरge_cgroup(idx, nr_pages, ptr, true);
पूर्ण

/* Should be called with hugetlb_lock held */
अटल व्योम __hugetlb_cgroup_commit_अक्षरge(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					   काष्ठा hugetlb_cgroup *h_cg,
					   काष्ठा page *page, bool rsvd)
अणु
	अगर (hugetlb_cgroup_disabled() || !h_cg)
		वापस;

	__set_hugetlb_cgroup(page, h_cg, rsvd);
	वापस;
पूर्ण

व्योम hugetlb_cgroup_commit_अक्षरge(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
				  काष्ठा hugetlb_cgroup *h_cg,
				  काष्ठा page *page)
अणु
	__hugetlb_cgroup_commit_अक्षरge(idx, nr_pages, h_cg, page, false);
पूर्ण

व्योम hugetlb_cgroup_commit_अक्षरge_rsvd(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
				       काष्ठा hugetlb_cgroup *h_cg,
				       काष्ठा page *page)
अणु
	__hugetlb_cgroup_commit_अक्षरge(idx, nr_pages, h_cg, page, true);
पूर्ण

/*
 * Should be called with hugetlb_lock held
 */
अटल व्योम __hugetlb_cgroup_unअक्षरge_page(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					   काष्ठा page *page, bool rsvd)
अणु
	काष्ठा hugetlb_cgroup *h_cg;

	अगर (hugetlb_cgroup_disabled())
		वापस;
	lockdep_निश्चित_held(&hugetlb_lock);
	h_cg = __hugetlb_cgroup_from_page(page, rsvd);
	अगर (unlikely(!h_cg))
		वापस;
	__set_hugetlb_cgroup(page, शून्य, rsvd);

	page_counter_unअक्षरge(__hugetlb_cgroup_counter_from_cgroup(h_cg, idx,
								   rsvd),
			      nr_pages);

	अगर (rsvd)
		css_put(&h_cg->css);

	वापस;
पूर्ण

व्योम hugetlb_cgroup_unअक्षरge_page(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
				  काष्ठा page *page)
अणु
	__hugetlb_cgroup_unअक्षरge_page(idx, nr_pages, page, false);
पूर्ण

व्योम hugetlb_cgroup_unअक्षरge_page_rsvd(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
				       काष्ठा page *page)
अणु
	__hugetlb_cgroup_unअक्षरge_page(idx, nr_pages, page, true);
पूर्ण

अटल व्योम __hugetlb_cgroup_unअक्षरge_cgroup(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					     काष्ठा hugetlb_cgroup *h_cg,
					     bool rsvd)
अणु
	अगर (hugetlb_cgroup_disabled() || !h_cg)
		वापस;

	अगर (huge_page_order(&hstates[idx]) < HUGETLB_CGROUP_MIN_ORDER)
		वापस;

	page_counter_unअक्षरge(__hugetlb_cgroup_counter_from_cgroup(h_cg, idx,
								   rsvd),
			      nr_pages);

	अगर (rsvd)
		css_put(&h_cg->css);
पूर्ण

व्योम hugetlb_cgroup_unअक्षरge_cgroup(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
				    काष्ठा hugetlb_cgroup *h_cg)
अणु
	__hugetlb_cgroup_unअक्षरge_cgroup(idx, nr_pages, h_cg, false);
पूर्ण

व्योम hugetlb_cgroup_unअक्षरge_cgroup_rsvd(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					 काष्ठा hugetlb_cgroup *h_cg)
अणु
	__hugetlb_cgroup_unअक्षरge_cgroup(idx, nr_pages, h_cg, true);
पूर्ण

व्योम hugetlb_cgroup_unअक्षरge_counter(काष्ठा resv_map *resv, अचिन्हित दीर्घ start,
				     अचिन्हित दीर्घ end)
अणु
	अगर (hugetlb_cgroup_disabled() || !resv || !resv->reservation_counter ||
	    !resv->css)
		वापस;

	page_counter_unअक्षरge(resv->reservation_counter,
			      (end - start) * resv->pages_per_hpage);
	css_put(resv->css);
पूर्ण

व्योम hugetlb_cgroup_unअक्षरge_file_region(काष्ठा resv_map *resv,
					 काष्ठा file_region *rg,
					 अचिन्हित दीर्घ nr_pages,
					 bool region_del)
अणु
	अगर (hugetlb_cgroup_disabled() || !resv || !rg || !nr_pages)
		वापस;

	अगर (rg->reservation_counter && resv->pages_per_hpage && nr_pages > 0 &&
	    !resv->reservation_counter) अणु
		page_counter_unअक्षरge(rg->reservation_counter,
				      nr_pages * resv->pages_per_hpage);
		/*
		 * Only करो css_put(rg->css) when we delete the entire region
		 * because one file_region must hold exactly one css reference.
		 */
		अगर (region_del)
			css_put(rg->css);
	पूर्ण
पूर्ण

क्रमागत अणु
	RES_USAGE,
	RES_RSVD_USAGE,
	RES_LIMIT,
	RES_RSVD_LIMIT,
	RES_MAX_USAGE,
	RES_RSVD_MAX_USAGE,
	RES_FAILCNT,
	RES_RSVD_FAILCNT,
पूर्ण;

अटल u64 hugetlb_cgroup_पढ़ो_u64(काष्ठा cgroup_subsys_state *css,
				   काष्ठा cftype *cft)
अणु
	काष्ठा page_counter *counter;
	काष्ठा page_counter *rsvd_counter;
	काष्ठा hugetlb_cgroup *h_cg = hugetlb_cgroup_from_css(css);

	counter = &h_cg->hugepage[MEMखाता_IDX(cft->निजी)];
	rsvd_counter = &h_cg->rsvd_hugepage[MEMखाता_IDX(cft->निजी)];

	चयन (MEMखाता_ATTR(cft->निजी)) अणु
	हाल RES_USAGE:
		वापस (u64)page_counter_पढ़ो(counter) * PAGE_SIZE;
	हाल RES_RSVD_USAGE:
		वापस (u64)page_counter_पढ़ो(rsvd_counter) * PAGE_SIZE;
	हाल RES_LIMIT:
		वापस (u64)counter->max * PAGE_SIZE;
	हाल RES_RSVD_LIMIT:
		वापस (u64)rsvd_counter->max * PAGE_SIZE;
	हाल RES_MAX_USAGE:
		वापस (u64)counter->watermark * PAGE_SIZE;
	हाल RES_RSVD_MAX_USAGE:
		वापस (u64)rsvd_counter->watermark * PAGE_SIZE;
	हाल RES_FAILCNT:
		वापस counter->failcnt;
	हाल RES_RSVD_FAILCNT:
		वापस rsvd_counter->failcnt;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक hugetlb_cgroup_पढ़ो_u64_max(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक idx;
	u64 val;
	काष्ठा cftype *cft = seq_cft(seq);
	अचिन्हित दीर्घ limit;
	काष्ठा page_counter *counter;
	काष्ठा hugetlb_cgroup *h_cg = hugetlb_cgroup_from_css(seq_css(seq));

	idx = MEMखाता_IDX(cft->निजी);
	counter = &h_cg->hugepage[idx];

	limit = round_करोwn(PAGE_COUNTER_MAX,
			   pages_per_huge_page(&hstates[idx]));

	चयन (MEMखाता_ATTR(cft->निजी)) अणु
	हाल RES_RSVD_USAGE:
		counter = &h_cg->rsvd_hugepage[idx];
		fallthrough;
	हाल RES_USAGE:
		val = (u64)page_counter_पढ़ो(counter);
		seq_म_लिखो(seq, "%llu\n", val * PAGE_SIZE);
		अवरोध;
	हाल RES_RSVD_LIMIT:
		counter = &h_cg->rsvd_hugepage[idx];
		fallthrough;
	हाल RES_LIMIT:
		val = (u64)counter->max;
		अगर (val == limit)
			seq_माला_दो(seq, "max\n");
		अन्यथा
			seq_म_लिखो(seq, "%llu\n", val * PAGE_SIZE);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(hugetlb_limit_mutex);

अटल sमाप_प्रकार hugetlb_cgroup_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				    अक्षर *buf, माप_प्रकार nbytes, loff_t off,
				    स्थिर अक्षर *max)
अणु
	पूर्णांक ret, idx;
	अचिन्हित दीर्घ nr_pages;
	काष्ठा hugetlb_cgroup *h_cg = hugetlb_cgroup_from_css(of_css(of));
	bool rsvd = false;

	अगर (hugetlb_cgroup_is_root(h_cg)) /* Can't set limit on root */
		वापस -EINVAL;

	buf = म_मालाip(buf);
	ret = page_counter_memparse(buf, max, &nr_pages);
	अगर (ret)
		वापस ret;

	idx = MEMखाता_IDX(of_cft(of)->निजी);
	nr_pages = round_करोwn(nr_pages, pages_per_huge_page(&hstates[idx]));

	चयन (MEMखाता_ATTR(of_cft(of)->निजी)) अणु
	हाल RES_RSVD_LIMIT:
		rsvd = true;
		fallthrough;
	हाल RES_LIMIT:
		mutex_lock(&hugetlb_limit_mutex);
		ret = page_counter_set_max(
			__hugetlb_cgroup_counter_from_cgroup(h_cg, idx, rsvd),
			nr_pages);
		mutex_unlock(&hugetlb_limit_mutex);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret ?: nbytes;
पूर्ण

अटल sमाप_प्रकार hugetlb_cgroup_ग_लिखो_legacy(काष्ठा kernfs_खोलो_file *of,
					   अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	वापस hugetlb_cgroup_ग_लिखो(of, buf, nbytes, off, "-1");
पूर्ण

अटल sमाप_प्रकार hugetlb_cgroup_ग_लिखो_dfl(काष्ठा kernfs_खोलो_file *of,
					अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	वापस hugetlb_cgroup_ग_लिखो(of, buf, nbytes, off, "max");
पूर्ण

अटल sमाप_प्रकार hugetlb_cgroup_reset(काष्ठा kernfs_खोलो_file *of,
				    अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	पूर्णांक ret = 0;
	काष्ठा page_counter *counter, *rsvd_counter;
	काष्ठा hugetlb_cgroup *h_cg = hugetlb_cgroup_from_css(of_css(of));

	counter = &h_cg->hugepage[MEMखाता_IDX(of_cft(of)->निजी)];
	rsvd_counter = &h_cg->rsvd_hugepage[MEMखाता_IDX(of_cft(of)->निजी)];

	चयन (MEMखाता_ATTR(of_cft(of)->निजी)) अणु
	हाल RES_MAX_USAGE:
		page_counter_reset_watermark(counter);
		अवरोध;
	हाल RES_RSVD_MAX_USAGE:
		page_counter_reset_watermark(rsvd_counter);
		अवरोध;
	हाल RES_FAILCNT:
		counter->failcnt = 0;
		अवरोध;
	हाल RES_RSVD_FAILCNT:
		rsvd_counter->failcnt = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret ?: nbytes;
पूर्ण

अटल अक्षर *mem_fmt(अक्षर *buf, पूर्णांक size, अचिन्हित दीर्घ hsize)
अणु
	अगर (hsize >= (1UL << 30))
		snम_लिखो(buf, size, "%luGB", hsize >> 30);
	अन्यथा अगर (hsize >= (1UL << 20))
		snम_लिखो(buf, size, "%luMB", hsize >> 20);
	अन्यथा
		snम_लिखो(buf, size, "%luKB", hsize >> 10);
	वापस buf;
पूर्ण

अटल पूर्णांक __hugetlb_events_show(काष्ठा seq_file *seq, bool local)
अणु
	पूर्णांक idx;
	दीर्घ max;
	काष्ठा cftype *cft = seq_cft(seq);
	काष्ठा hugetlb_cgroup *h_cg = hugetlb_cgroup_from_css(seq_css(seq));

	idx = MEMखाता_IDX(cft->निजी);

	अगर (local)
		max = atomic_दीर्घ_पढ़ो(&h_cg->events_local[idx][HUGETLB_MAX]);
	अन्यथा
		max = atomic_दीर्घ_पढ़ो(&h_cg->events[idx][HUGETLB_MAX]);

	seq_म_लिखो(seq, "max %lu\n", max);

	वापस 0;
पूर्ण

अटल पूर्णांक hugetlb_events_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस __hugetlb_events_show(seq, false);
पूर्ण

अटल पूर्णांक hugetlb_events_local_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस __hugetlb_events_show(seq, true);
पूर्ण

अटल व्योम __init __hugetlb_cgroup_file_dfl_init(पूर्णांक idx)
अणु
	अक्षर buf[32];
	काष्ठा cftype *cft;
	काष्ठा hstate *h = &hstates[idx];

	/* क्रमmat the size */
	mem_fmt(buf, माप(buf), huge_page_size(h));

	/* Add the limit file */
	cft = &h->cgroup_files_dfl[0];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.max", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, RES_LIMIT);
	cft->seq_show = hugetlb_cgroup_पढ़ो_u64_max;
	cft->ग_लिखो = hugetlb_cgroup_ग_लिखो_dfl;
	cft->flags = CFTYPE_NOT_ON_ROOT;

	/* Add the reservation limit file */
	cft = &h->cgroup_files_dfl[1];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.rsvd.max", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, RES_RSVD_LIMIT);
	cft->seq_show = hugetlb_cgroup_पढ़ो_u64_max;
	cft->ग_लिखो = hugetlb_cgroup_ग_लिखो_dfl;
	cft->flags = CFTYPE_NOT_ON_ROOT;

	/* Add the current usage file */
	cft = &h->cgroup_files_dfl[2];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.current", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, RES_USAGE);
	cft->seq_show = hugetlb_cgroup_पढ़ो_u64_max;
	cft->flags = CFTYPE_NOT_ON_ROOT;

	/* Add the current reservation usage file */
	cft = &h->cgroup_files_dfl[3];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.rsvd.current", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, RES_RSVD_USAGE);
	cft->seq_show = hugetlb_cgroup_पढ़ो_u64_max;
	cft->flags = CFTYPE_NOT_ON_ROOT;

	/* Add the events file */
	cft = &h->cgroup_files_dfl[4];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.events", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, 0);
	cft->seq_show = hugetlb_events_show;
	cft->file_offset = दुरत्व(काष्ठा hugetlb_cgroup, events_file[idx]);
	cft->flags = CFTYPE_NOT_ON_ROOT;

	/* Add the events.local file */
	cft = &h->cgroup_files_dfl[5];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.events.local", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, 0);
	cft->seq_show = hugetlb_events_local_show;
	cft->file_offset = दुरत्व(काष्ठा hugetlb_cgroup,
				    events_local_file[idx]);
	cft->flags = CFTYPE_NOT_ON_ROOT;

	/* शून्य terminate the last cft */
	cft = &h->cgroup_files_dfl[6];
	स_रखो(cft, 0, माप(*cft));

	WARN_ON(cgroup_add_dfl_cftypes(&hugetlb_cgrp_subsys,
				       h->cgroup_files_dfl));
पूर्ण

अटल व्योम __init __hugetlb_cgroup_file_legacy_init(पूर्णांक idx)
अणु
	अक्षर buf[32];
	काष्ठा cftype *cft;
	काष्ठा hstate *h = &hstates[idx];

	/* क्रमmat the size */
	mem_fmt(buf, माप(buf), huge_page_size(h));

	/* Add the limit file */
	cft = &h->cgroup_files_legacy[0];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.limit_in_bytes", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, RES_LIMIT);
	cft->पढ़ो_u64 = hugetlb_cgroup_पढ़ो_u64;
	cft->ग_लिखो = hugetlb_cgroup_ग_लिखो_legacy;

	/* Add the reservation limit file */
	cft = &h->cgroup_files_legacy[1];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.rsvd.limit_in_bytes", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, RES_RSVD_LIMIT);
	cft->पढ़ो_u64 = hugetlb_cgroup_पढ़ो_u64;
	cft->ग_लिखो = hugetlb_cgroup_ग_लिखो_legacy;

	/* Add the usage file */
	cft = &h->cgroup_files_legacy[2];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.usage_in_bytes", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, RES_USAGE);
	cft->पढ़ो_u64 = hugetlb_cgroup_पढ़ो_u64;

	/* Add the reservation usage file */
	cft = &h->cgroup_files_legacy[3];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.rsvd.usage_in_bytes", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, RES_RSVD_USAGE);
	cft->पढ़ो_u64 = hugetlb_cgroup_पढ़ो_u64;

	/* Add the MAX usage file */
	cft = &h->cgroup_files_legacy[4];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.max_usage_in_bytes", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, RES_MAX_USAGE);
	cft->ग_लिखो = hugetlb_cgroup_reset;
	cft->पढ़ो_u64 = hugetlb_cgroup_पढ़ो_u64;

	/* Add the MAX reservation usage file */
	cft = &h->cgroup_files_legacy[5];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.rsvd.max_usage_in_bytes", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, RES_RSVD_MAX_USAGE);
	cft->ग_लिखो = hugetlb_cgroup_reset;
	cft->पढ़ो_u64 = hugetlb_cgroup_पढ़ो_u64;

	/* Add the failcntfile */
	cft = &h->cgroup_files_legacy[6];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.failcnt", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, RES_FAILCNT);
	cft->ग_लिखो = hugetlb_cgroup_reset;
	cft->पढ़ो_u64 = hugetlb_cgroup_पढ़ो_u64;

	/* Add the reservation failcntfile */
	cft = &h->cgroup_files_legacy[7];
	snम_लिखो(cft->name, MAX_CFTYPE_NAME, "%s.rsvd.failcnt", buf);
	cft->निजी = MEMखाता_PRIVATE(idx, RES_RSVD_FAILCNT);
	cft->ग_लिखो = hugetlb_cgroup_reset;
	cft->पढ़ो_u64 = hugetlb_cgroup_पढ़ो_u64;

	/* शून्य terminate the last cft */
	cft = &h->cgroup_files_legacy[8];
	स_रखो(cft, 0, माप(*cft));

	WARN_ON(cgroup_add_legacy_cftypes(&hugetlb_cgrp_subsys,
					  h->cgroup_files_legacy));
पूर्ण

अटल व्योम __init __hugetlb_cgroup_file_init(पूर्णांक idx)
अणु
	__hugetlb_cgroup_file_dfl_init(idx);
	__hugetlb_cgroup_file_legacy_init(idx);
पूर्ण

व्योम __init hugetlb_cgroup_file_init(व्योम)
अणु
	काष्ठा hstate *h;

	क्रम_each_hstate(h) अणु
		/*
		 * Add cgroup control files only अगर the huge page consists
		 * of more than two normal pages. This is because we use
		 * page[2].निजी क्रम storing cgroup details.
		 */
		अगर (huge_page_order(h) >= HUGETLB_CGROUP_MIN_ORDER)
			__hugetlb_cgroup_file_init(hstate_index(h));
	पूर्ण
पूर्ण

/*
 * hugetlb_lock will make sure a parallel cgroup सूची_हटाओ won't happen
 * when we migrate hugepages
 */
व्योम hugetlb_cgroup_migrate(काष्ठा page *oldhpage, काष्ठा page *newhpage)
अणु
	काष्ठा hugetlb_cgroup *h_cg;
	काष्ठा hugetlb_cgroup *h_cg_rsvd;
	काष्ठा hstate *h = page_hstate(oldhpage);

	अगर (hugetlb_cgroup_disabled())
		वापस;

	spin_lock_irq(&hugetlb_lock);
	h_cg = hugetlb_cgroup_from_page(oldhpage);
	h_cg_rsvd = hugetlb_cgroup_from_page_rsvd(oldhpage);
	set_hugetlb_cgroup(oldhpage, शून्य);
	set_hugetlb_cgroup_rsvd(oldhpage, शून्य);

	/* move the h_cg details to new cgroup */
	set_hugetlb_cgroup(newhpage, h_cg);
	set_hugetlb_cgroup_rsvd(newhpage, h_cg_rsvd);
	list_move(&newhpage->lru, &h->hugepage_activelist);
	spin_unlock_irq(&hugetlb_lock);
	वापस;
पूर्ण

अटल काष्ठा cftype hugetlb_files[] = अणु
	अणुपूर्ण /* terminate */
पूर्ण;

काष्ठा cgroup_subsys hugetlb_cgrp_subsys = अणु
	.css_alloc	= hugetlb_cgroup_css_alloc,
	.css_offline	= hugetlb_cgroup_css_offline,
	.css_मुक्त	= hugetlb_cgroup_css_मुक्त,
	.dfl_cftypes	= hugetlb_files,
	.legacy_cftypes	= hugetlb_files,
पूर्ण;
