<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mm/page-ग_लिखोback.c
 *
 * Copyright (C) 2002, Linus Torvalds.
 * Copyright (C) 2007 Red Hat, Inc., Peter Zijlstra
 *
 * Contains functions related to writing back dirty pages at the
 * address_space level.
 *
 * 10Apr2002	Andrew Morton
 *		Initial version
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/init.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/mpage.h>
#समावेश <linux/rmap.h>
#समावेश <linux/percpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/cpu.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/buffer_head.h> /* __set_page_dirty_buffers */
#समावेश <linux/pagevec.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sched/rt.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <trace/events/ग_लिखोback.h>

#समावेश "internal.h"

/*
 * Sleep at most 200ms at a समय in balance_dirty_pages().
 */
#घोषणा MAX_PAUSE		max(HZ/5, 1)

/*
 * Try to keep balance_dirty_pages() call पूर्णांकervals higher than this many pages
 * by raising छोड़ो समय to max_छोड़ो when falls below it.
 */
#घोषणा सूचीTY_POLL_THRESH	(128 >> (PAGE_SHIFT - 10))

/*
 * Estimate ग_लिखो bandwidth at 200ms पूर्णांकervals.
 */
#घोषणा BANDWIDTH_INTERVAL	max(HZ/5, 1)

#घोषणा RATELIMIT_CALC_SHIFT	10

/*
 * After a CPU has dirtied this many pages, balance_dirty_pages_ratelimited
 * will look to see अगर it needs to क्रमce ग_लिखोback or throttling.
 */
अटल दीर्घ ratelimit_pages = 32;

/* The following parameters are exported via /proc/sys/vm */

/*
 * Start background ग_लिखोback (via ग_लिखोback thपढ़ोs) at this percentage
 */
पूर्णांक dirty_background_ratio = 10;

/*
 * dirty_background_bytes starts at 0 (disabled) so that it is a function of
 * dirty_background_ratio * the amount of dirtyable memory
 */
अचिन्हित दीर्घ dirty_background_bytes;

/*
 * मुक्त highmem will not be subtracted from the total मुक्त memory
 * क्रम calculating मुक्त ratios अगर vm_highmem_is_dirtyable is true
 */
पूर्णांक vm_highmem_is_dirtyable;

/*
 * The generator of dirty data starts ग_लिखोback at this percentage
 */
पूर्णांक vm_dirty_ratio = 20;

/*
 * vm_dirty_bytes starts at 0 (disabled) so that it is a function of
 * vm_dirty_ratio * the amount of dirtyable memory
 */
अचिन्हित दीर्घ vm_dirty_bytes;

/*
 * The पूर्णांकerval between `kupdate'-style ग_लिखोbacks
 */
अचिन्हित पूर्णांक dirty_ग_लिखोback_पूर्णांकerval = 5 * 100; /* centiseconds */

EXPORT_SYMBOL_GPL(dirty_ग_लिखोback_पूर्णांकerval);

/*
 * The दीर्घest समय क्रम which data is allowed to reमुख्य dirty
 */
अचिन्हित पूर्णांक dirty_expire_पूर्णांकerval = 30 * 100; /* centiseconds */

/*
 * Flag that makes the machine dump ग_लिखोs/पढ़ोs and block dirtyings.
 */
पूर्णांक block_dump;

/*
 * Flag that माला_दो the machine in "laptop mode". Doubles as a समयout in jअगरfies:
 * a full sync is triggered after this समय elapses without any disk activity.
 */
पूर्णांक laptop_mode;

EXPORT_SYMBOL(laptop_mode);

/* End of sysctl-exported parameters */

काष्ठा wb_करोमुख्य global_wb_करोमुख्य;

/* consolidated parameters क्रम balance_dirty_pages() and its subroutines */
काष्ठा dirty_throttle_control अणु
#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	काष्ठा wb_करोमुख्य	*करोm;
	काष्ठा dirty_throttle_control *gdtc;	/* only set in memcg dtc's */
#पूर्ण_अगर
	काष्ठा bdi_ग_लिखोback	*wb;
	काष्ठा fprop_local_percpu *wb_completions;

	अचिन्हित दीर्घ		avail;		/* dirtyable */
	अचिन्हित दीर्घ		dirty;		/* file_dirty + ग_लिखो + nfs */
	अचिन्हित दीर्घ		thresh;		/* dirty threshold */
	अचिन्हित दीर्घ		bg_thresh;	/* dirty background threshold */

	अचिन्हित दीर्घ		wb_dirty;	/* per-wb counterparts */
	अचिन्हित दीर्घ		wb_thresh;
	अचिन्हित दीर्घ		wb_bg_thresh;

	अचिन्हित दीर्घ		pos_ratio;
पूर्ण;

/*
 * Length of period क्रम aging ग_लिखोout fractions of bdis. This is an
 * arbitrarily chosen number. The दीर्घer the period, the slower fractions will
 * reflect changes in current ग_लिखोout rate.
 */
#घोषणा VM_COMPLETIONS_PERIOD_LEN (3*HZ)

#अगर_घोषित CONFIG_CGROUP_WRITEBACK

#घोषणा GDTC_INIT(__wb)		.wb = (__wb),				\
				.करोm = &global_wb_करोमुख्य,		\
				.wb_completions = &(__wb)->completions

#घोषणा GDTC_INIT_NO_WB		.करोm = &global_wb_करोमुख्य

#घोषणा MDTC_INIT(__wb, __gdtc)	.wb = (__wb),				\
				.करोm = mem_cgroup_wb_करोमुख्य(__wb),	\
				.wb_completions = &(__wb)->memcg_completions, \
				.gdtc = __gdtc

अटल bool mdtc_valid(काष्ठा dirty_throttle_control *dtc)
अणु
	वापस dtc->करोm;
पूर्ण

अटल काष्ठा wb_करोमुख्य *dtc_करोm(काष्ठा dirty_throttle_control *dtc)
अणु
	वापस dtc->करोm;
पूर्ण

अटल काष्ठा dirty_throttle_control *mdtc_gdtc(काष्ठा dirty_throttle_control *mdtc)
अणु
	वापस mdtc->gdtc;
पूर्ण

अटल काष्ठा fprop_local_percpu *wb_memcg_completions(काष्ठा bdi_ग_लिखोback *wb)
अणु
	वापस &wb->memcg_completions;
पूर्ण

अटल व्योम wb_min_max_ratio(काष्ठा bdi_ग_लिखोback *wb,
			     अचिन्हित दीर्घ *minp, अचिन्हित दीर्घ *maxp)
अणु
	अचिन्हित दीर्घ this_bw = wb->avg_ग_लिखो_bandwidth;
	अचिन्हित दीर्घ tot_bw = atomic_दीर्घ_पढ़ो(&wb->bdi->tot_ग_लिखो_bandwidth);
	अचिन्हित दीर्घ दीर्घ min = wb->bdi->min_ratio;
	अचिन्हित दीर्घ दीर्घ max = wb->bdi->max_ratio;

	/*
	 * @wb may alपढ़ोy be clean by the समय control reaches here and
	 * the total may not include its bw.
	 */
	अगर (this_bw < tot_bw) अणु
		अगर (min) अणु
			min *= this_bw;
			min = भाग64_ul(min, tot_bw);
		पूर्ण
		अगर (max < 100) अणु
			max *= this_bw;
			max = भाग64_ul(max, tot_bw);
		पूर्ण
	पूर्ण

	*minp = min;
	*maxp = max;
पूर्ण

#अन्यथा	/* CONFIG_CGROUP_WRITEBACK */

#घोषणा GDTC_INIT(__wb)		.wb = (__wb),                           \
				.wb_completions = &(__wb)->completions
#घोषणा GDTC_INIT_NO_WB
#घोषणा MDTC_INIT(__wb, __gdtc)

अटल bool mdtc_valid(काष्ठा dirty_throttle_control *dtc)
अणु
	वापस false;
पूर्ण

अटल काष्ठा wb_करोमुख्य *dtc_करोm(काष्ठा dirty_throttle_control *dtc)
अणु
	वापस &global_wb_करोमुख्य;
पूर्ण

अटल काष्ठा dirty_throttle_control *mdtc_gdtc(काष्ठा dirty_throttle_control *mdtc)
अणु
	वापस शून्य;
पूर्ण

अटल काष्ठा fprop_local_percpu *wb_memcg_completions(काष्ठा bdi_ग_लिखोback *wb)
अणु
	वापस शून्य;
पूर्ण

अटल व्योम wb_min_max_ratio(काष्ठा bdi_ग_लिखोback *wb,
			     अचिन्हित दीर्घ *minp, अचिन्हित दीर्घ *maxp)
अणु
	*minp = wb->bdi->min_ratio;
	*maxp = wb->bdi->max_ratio;
पूर्ण

#पूर्ण_अगर	/* CONFIG_CGROUP_WRITEBACK */

/*
 * In a memory zone, there is a certain amount of pages we consider
 * available क्रम the page cache, which is essentially the number of
 * मुक्त and reclaimable pages, minus some zone reserves to protect
 * lowmem and the ability to uphold the zone's watermarks without
 * requiring ग_लिखोback.
 *
 * This number of dirtyable pages is the base value of which the
 * user-configurable dirty ratio is the effective number of pages that
 * are allowed to be actually dirtied.  Per inभागidual zone, or
 * globally by using the sum of dirtyable pages over all zones.
 *
 * Because the user is allowed to specअगरy the dirty limit globally as
 * असलolute number of bytes, calculating the per-zone dirty limit can
 * require translating the configured limit पूर्णांकo a percentage of
 * global dirtyable memory first.
 */

/**
 * node_dirtyable_memory - number of dirtyable pages in a node
 * @pgdat: the node
 *
 * Return: the node's number of pages potentially available क्रम dirty
 * page cache.  This is the base value क्रम the per-node dirty limits.
 */
अटल अचिन्हित दीर्घ node_dirtyable_memory(काष्ठा pglist_data *pgdat)
अणु
	अचिन्हित दीर्घ nr_pages = 0;
	पूर्णांक z;

	क्रम (z = 0; z < MAX_NR_ZONES; z++) अणु
		काष्ठा zone *zone = pgdat->node_zones + z;

		अगर (!populated_zone(zone))
			जारी;

		nr_pages += zone_page_state(zone, NR_FREE_PAGES);
	पूर्ण

	/*
	 * Pages reserved क्रम the kernel should not be considered
	 * dirtyable, to prevent a situation where reclaim has to
	 * clean pages in order to balance the zones.
	 */
	nr_pages -= min(nr_pages, pgdat->totalreserve_pages);

	nr_pages += node_page_state(pgdat, NR_INACTIVE_खाता);
	nr_pages += node_page_state(pgdat, NR_ACTIVE_खाता);

	वापस nr_pages;
पूर्ण

अटल अचिन्हित दीर्घ highmem_dirtyable_memory(अचिन्हित दीर्घ total)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	पूर्णांक node;
	अचिन्हित दीर्घ x = 0;
	पूर्णांक i;

	क्रम_each_node_state(node, N_HIGH_MEMORY) अणु
		क्रम (i = ZONE_NORMAL + 1; i < MAX_NR_ZONES; i++) अणु
			काष्ठा zone *z;
			अचिन्हित दीर्घ nr_pages;

			अगर (!is_highmem_idx(i))
				जारी;

			z = &NODE_DATA(node)->node_zones[i];
			अगर (!populated_zone(z))
				जारी;

			nr_pages = zone_page_state(z, NR_FREE_PAGES);
			/* watch क्रम underflows */
			nr_pages -= min(nr_pages, high_wmark_pages(z));
			nr_pages += zone_page_state(z, NR_ZONE_INACTIVE_खाता);
			nr_pages += zone_page_state(z, NR_ZONE_ACTIVE_खाता);
			x += nr_pages;
		पूर्ण
	पूर्ण

	/*
	 * Unreclaimable memory (kernel memory or anonymous memory
	 * without swap) can bring करोwn the dirtyable pages below
	 * the zone's dirty balance reserve and the above calculation
	 * will underflow.  However we still want to add in nodes
	 * which are below threshold (negative values) to get a more
	 * accurate calculation but make sure that the total never
	 * underflows.
	 */
	अगर ((दीर्घ)x < 0)
		x = 0;

	/*
	 * Make sure that the number of highmem pages is never larger
	 * than the number of the total dirtyable memory. This can only
	 * occur in very strange VM situations but we want to make sure
	 * that this करोes not occur.
	 */
	वापस min(x, total);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 * global_dirtyable_memory - number of globally dirtyable pages
 *
 * Return: the global number of pages potentially available क्रम dirty
 * page cache.  This is the base value क्रम the global dirty limits.
 */
अटल अचिन्हित दीर्घ global_dirtyable_memory(व्योम)
अणु
	अचिन्हित दीर्घ x;

	x = global_zone_page_state(NR_FREE_PAGES);
	/*
	 * Pages reserved क्रम the kernel should not be considered
	 * dirtyable, to prevent a situation where reclaim has to
	 * clean pages in order to balance the zones.
	 */
	x -= min(x, totalreserve_pages);

	x += global_node_page_state(NR_INACTIVE_खाता);
	x += global_node_page_state(NR_ACTIVE_खाता);

	अगर (!vm_highmem_is_dirtyable)
		x -= highmem_dirtyable_memory(x);

	वापस x + 1;	/* Ensure that we never वापस 0 */
पूर्ण

/**
 * करोमुख्य_dirty_limits - calculate thresh and bg_thresh क्रम a wb_करोमुख्य
 * @dtc: dirty_throttle_control of पूर्णांकerest
 *
 * Calculate @dtc->thresh and ->bg_thresh considering
 * vm_dirty_अणुbytes|ratioपूर्ण and dirty_background_अणुbytes|ratioपूर्ण.  The caller
 * must ensure that @dtc->avail is set beक्रमe calling this function.  The
 * dirty limits will be lअगरted by 1/4 क्रम real-समय tasks.
 */
अटल व्योम करोमुख्य_dirty_limits(काष्ठा dirty_throttle_control *dtc)
अणु
	स्थिर अचिन्हित दीर्घ available_memory = dtc->avail;
	काष्ठा dirty_throttle_control *gdtc = mdtc_gdtc(dtc);
	अचिन्हित दीर्घ bytes = vm_dirty_bytes;
	अचिन्हित दीर्घ bg_bytes = dirty_background_bytes;
	/* convert ratios to per-PAGE_SIZE क्रम higher precision */
	अचिन्हित दीर्घ ratio = (vm_dirty_ratio * PAGE_SIZE) / 100;
	अचिन्हित दीर्घ bg_ratio = (dirty_background_ratio * PAGE_SIZE) / 100;
	अचिन्हित दीर्घ thresh;
	अचिन्हित दीर्घ bg_thresh;
	काष्ठा task_काष्ठा *tsk;

	/* gdtc is !शून्य अगरf @dtc is क्रम memcg करोमुख्य */
	अगर (gdtc) अणु
		अचिन्हित दीर्घ global_avail = gdtc->avail;

		/*
		 * The byte settings can't be applied directly to memcg
		 * करोमुख्यs.  Convert them to ratios by scaling against
		 * globally available memory.  As the ratios are in
		 * per-PAGE_SIZE, they can be obtained by भागiding bytes by
		 * number of pages.
		 */
		अगर (bytes)
			ratio = min(DIV_ROUND_UP(bytes, global_avail),
				    PAGE_SIZE);
		अगर (bg_bytes)
			bg_ratio = min(DIV_ROUND_UP(bg_bytes, global_avail),
				       PAGE_SIZE);
		bytes = bg_bytes = 0;
	पूर्ण

	अगर (bytes)
		thresh = DIV_ROUND_UP(bytes, PAGE_SIZE);
	अन्यथा
		thresh = (ratio * available_memory) / PAGE_SIZE;

	अगर (bg_bytes)
		bg_thresh = DIV_ROUND_UP(bg_bytes, PAGE_SIZE);
	अन्यथा
		bg_thresh = (bg_ratio * available_memory) / PAGE_SIZE;

	अगर (bg_thresh >= thresh)
		bg_thresh = thresh / 2;
	tsk = current;
	अगर (rt_task(tsk)) अणु
		bg_thresh += bg_thresh / 4 + global_wb_करोमुख्य.dirty_limit / 32;
		thresh += thresh / 4 + global_wb_करोमुख्य.dirty_limit / 32;
	पूर्ण
	dtc->thresh = thresh;
	dtc->bg_thresh = bg_thresh;

	/* we should eventually report the करोमुख्य in the TP */
	अगर (!gdtc)
		trace_global_dirty_state(bg_thresh, thresh);
पूर्ण

/**
 * global_dirty_limits - background-ग_लिखोback and dirty-throttling thresholds
 * @pbackground: out parameter क्रम bg_thresh
 * @pdirty: out parameter क्रम thresh
 *
 * Calculate bg_thresh and thresh क्रम global_wb_करोमुख्य.  See
 * करोमुख्य_dirty_limits() क्रम details.
 */
व्योम global_dirty_limits(अचिन्हित दीर्घ *pbackground, अचिन्हित दीर्घ *pdirty)
अणु
	काष्ठा dirty_throttle_control gdtc = अणु GDTC_INIT_NO_WB पूर्ण;

	gdtc.avail = global_dirtyable_memory();
	करोमुख्य_dirty_limits(&gdtc);

	*pbackground = gdtc.bg_thresh;
	*pdirty = gdtc.thresh;
पूर्ण

/**
 * node_dirty_limit - maximum number of dirty pages allowed in a node
 * @pgdat: the node
 *
 * Return: the maximum number of dirty pages allowed in a node, based
 * on the node's dirtyable memory.
 */
अटल अचिन्हित दीर्घ node_dirty_limit(काष्ठा pglist_data *pgdat)
अणु
	अचिन्हित दीर्घ node_memory = node_dirtyable_memory(pgdat);
	काष्ठा task_काष्ठा *tsk = current;
	अचिन्हित दीर्घ dirty;

	अगर (vm_dirty_bytes)
		dirty = DIV_ROUND_UP(vm_dirty_bytes, PAGE_SIZE) *
			node_memory / global_dirtyable_memory();
	अन्यथा
		dirty = vm_dirty_ratio * node_memory / 100;

	अगर (rt_task(tsk))
		dirty += dirty / 4;

	वापस dirty;
पूर्ण

/**
 * node_dirty_ok - tells whether a node is within its dirty limits
 * @pgdat: the node to check
 *
 * Return: %true when the dirty pages in @pgdat are within the node's
 * dirty limit, %false अगर the limit is exceeded.
 */
bool node_dirty_ok(काष्ठा pglist_data *pgdat)
अणु
	अचिन्हित दीर्घ limit = node_dirty_limit(pgdat);
	अचिन्हित दीर्घ nr_pages = 0;

	nr_pages += node_page_state(pgdat, NR_खाता_सूचीTY);
	nr_pages += node_page_state(pgdat, NR_WRITEBACK);

	वापस nr_pages <= limit;
पूर्ण

पूर्णांक dirty_background_ratio_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;

	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret == 0 && ग_लिखो)
		dirty_background_bytes = 0;
	वापस ret;
पूर्ण

पूर्णांक dirty_background_bytes_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;

	ret = proc_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret == 0 && ग_लिखो)
		dirty_background_ratio = 0;
	वापस ret;
पूर्ण

पूर्णांक dirty_ratio_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक old_ratio = vm_dirty_ratio;
	पूर्णांक ret;

	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret == 0 && ग_लिखो && vm_dirty_ratio != old_ratio) अणु
		ग_लिखोback_set_ratelimit();
		vm_dirty_bytes = 0;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक dirty_bytes_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अचिन्हित दीर्घ old_bytes = vm_dirty_bytes;
	पूर्णांक ret;

	ret = proc_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret == 0 && ग_लिखो && vm_dirty_bytes != old_bytes) अणु
		ग_लिखोback_set_ratelimit();
		vm_dirty_ratio = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ wp_next_समय(अचिन्हित दीर्घ cur_समय)
अणु
	cur_समय += VM_COMPLETIONS_PERIOD_LEN;
	/* 0 has a special meaning... */
	अगर (!cur_समय)
		वापस 1;
	वापस cur_समय;
पूर्ण

अटल व्योम wb_करोमुख्य_ग_लिखोout_inc(काष्ठा wb_करोमुख्य *करोm,
				   काष्ठा fprop_local_percpu *completions,
				   अचिन्हित पूर्णांक max_prop_frac)
अणु
	__fprop_inc_percpu_max(&करोm->completions, completions,
			       max_prop_frac);
	/* First event after period चयनing was turned off? */
	अगर (unlikely(!करोm->period_समय)) अणु
		/*
		 * We can race with other __bdi_ग_लिखोout_inc calls here but
		 * it करोes not cause any harm since the resulting समय when
		 * समयr will fire and what is in ग_लिखोout_period_समय will be
		 * roughly the same.
		 */
		करोm->period_समय = wp_next_समय(jअगरfies);
		mod_समयr(&करोm->period_समयr, करोm->period_समय);
	पूर्ण
पूर्ण

/*
 * Increment @wb's ग_लिखोout completion count and the global ग_लिखोout
 * completion count. Called from test_clear_page_ग_लिखोback().
 */
अटल अंतरभूत व्योम __wb_ग_लिखोout_inc(काष्ठा bdi_ग_लिखोback *wb)
अणु
	काष्ठा wb_करोमुख्य *cgकरोm;

	inc_wb_stat(wb, WB_WRITTEN);
	wb_करोमुख्य_ग_लिखोout_inc(&global_wb_करोमुख्य, &wb->completions,
			       wb->bdi->max_prop_frac);

	cgकरोm = mem_cgroup_wb_करोमुख्य(wb);
	अगर (cgकरोm)
		wb_करोमुख्य_ग_लिखोout_inc(cgकरोm, wb_memcg_completions(wb),
				       wb->bdi->max_prop_frac);
पूर्ण

व्योम wb_ग_लिखोout_inc(काष्ठा bdi_ग_लिखोback *wb)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__wb_ग_लिखोout_inc(wb);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(wb_ग_लिखोout_inc);

/*
 * On idle प्रणाली, we can be called दीर्घ after we scheduled because we use
 * deferred समयrs so count with missed periods.
 */
अटल व्योम ग_लिखोout_period(काष्ठा समयr_list *t)
अणु
	काष्ठा wb_करोमुख्य *करोm = from_समयr(करोm, t, period_समयr);
	पूर्णांक miss_periods = (jअगरfies - करोm->period_समय) /
						 VM_COMPLETIONS_PERIOD_LEN;

	अगर (fprop_new_period(&करोm->completions, miss_periods + 1)) अणु
		करोm->period_समय = wp_next_समय(करोm->period_समय +
				miss_periods * VM_COMPLETIONS_PERIOD_LEN);
		mod_समयr(&करोm->period_समयr, करोm->period_समय);
	पूर्ण अन्यथा अणु
		/*
		 * Aging has zeroed all fractions. Stop wasting CPU on period
		 * updates.
		 */
		करोm->period_समय = 0;
	पूर्ण
पूर्ण

पूर्णांक wb_करोमुख्य_init(काष्ठा wb_करोमुख्य *करोm, gfp_t gfp)
अणु
	स_रखो(करोm, 0, माप(*करोm));

	spin_lock_init(&करोm->lock);

	समयr_setup(&करोm->period_समयr, ग_लिखोout_period, TIMER_DEFERRABLE);

	करोm->dirty_limit_tstamp = jअगरfies;

	वापस fprop_global_init(&करोm->completions, gfp);
पूर्ण

#अगर_घोषित CONFIG_CGROUP_WRITEBACK
व्योम wb_करोमुख्य_निकास(काष्ठा wb_करोमुख्य *करोm)
अणु
	del_समयr_sync(&करोm->period_समयr);
	fprop_global_destroy(&करोm->completions);
पूर्ण
#पूर्ण_अगर

/*
 * bdi_min_ratio keeps the sum of the minimum dirty shares of all
 * रेजिस्टरed backing devices, which, क्रम obvious reasons, can not
 * exceed 100%.
 */
अटल अचिन्हित पूर्णांक bdi_min_ratio;

पूर्णांक bdi_set_min_ratio(काष्ठा backing_dev_info *bdi, अचिन्हित पूर्णांक min_ratio)
अणु
	पूर्णांक ret = 0;

	spin_lock_bh(&bdi_lock);
	अगर (min_ratio > bdi->max_ratio) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		min_ratio -= bdi->min_ratio;
		अगर (bdi_min_ratio + min_ratio < 100) अणु
			bdi_min_ratio += min_ratio;
			bdi->min_ratio += min_ratio;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&bdi_lock);

	वापस ret;
पूर्ण

पूर्णांक bdi_set_max_ratio(काष्ठा backing_dev_info *bdi, अचिन्हित max_ratio)
अणु
	पूर्णांक ret = 0;

	अगर (max_ratio > 100)
		वापस -EINVAL;

	spin_lock_bh(&bdi_lock);
	अगर (bdi->min_ratio > max_ratio) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		bdi->max_ratio = max_ratio;
		bdi->max_prop_frac = (FPROP_FRAC_BASE * max_ratio) / 100;
	पूर्ण
	spin_unlock_bh(&bdi_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(bdi_set_max_ratio);

अटल अचिन्हित दीर्घ dirty_मुक्तrun_उच्चमानing(अचिन्हित दीर्घ thresh,
					   अचिन्हित दीर्घ bg_thresh)
अणु
	वापस (thresh + bg_thresh) / 2;
पूर्ण

अटल अचिन्हित दीर्घ hard_dirty_limit(काष्ठा wb_करोमुख्य *करोm,
				      अचिन्हित दीर्घ thresh)
अणु
	वापस max(thresh, करोm->dirty_limit);
पूर्ण

/*
 * Memory which can be further allocated to a memcg करोमुख्य is capped by
 * प्रणाली-wide clean memory excluding the amount being used in the करोमुख्य.
 */
अटल व्योम mdtc_calc_avail(काष्ठा dirty_throttle_control *mdtc,
			    अचिन्हित दीर्घ filepages, अचिन्हित दीर्घ headroom)
अणु
	काष्ठा dirty_throttle_control *gdtc = mdtc_gdtc(mdtc);
	अचिन्हित दीर्घ clean = filepages - min(filepages, mdtc->dirty);
	अचिन्हित दीर्घ global_clean = gdtc->avail - min(gdtc->avail, gdtc->dirty);
	अचिन्हित दीर्घ other_clean = global_clean - min(global_clean, clean);

	mdtc->avail = filepages + min(headroom, other_clean);
पूर्ण

/**
 * __wb_calc_thresh - @wb's share of dirty throttling threshold
 * @dtc: dirty_throttle_context of पूर्णांकerest
 *
 * Note that balance_dirty_pages() will only seriously take it as a hard limit
 * when sleeping max_छोड़ो per page is not enough to keep the dirty pages under
 * control. For example, when the device is completely stalled due to some error
 * conditions, or when there are 1000 dd tasks writing to a slow 10MB/s USB key.
 * In the other normal situations, it acts more gently by throttling the tasks
 * more (rather than completely block them) when the wb dirty pages go high.
 *
 * It allocates high/low dirty limits to fast/slow devices, in order to prevent
 * - starving fast devices
 * - piling up dirty pages (that will take दीर्घ समय to sync) on slow devices
 *
 * The wb's share of dirty limit will be adapting to its throughput and
 * bounded by the bdi->min_ratio and/or bdi->max_ratio parameters, अगर set.
 *
 * Return: @wb's dirty limit in pages. The term "dirty" in the context of
 * dirty balancing includes all PG_dirty and PG_ग_लिखोback pages.
 */
अटल अचिन्हित दीर्घ __wb_calc_thresh(काष्ठा dirty_throttle_control *dtc)
अणु
	काष्ठा wb_करोमुख्य *करोm = dtc_करोm(dtc);
	अचिन्हित दीर्घ thresh = dtc->thresh;
	u64 wb_thresh;
	अचिन्हित दीर्घ numerator, denominator;
	अचिन्हित दीर्घ wb_min_ratio, wb_max_ratio;

	/*
	 * Calculate this BDI's share of the thresh ratio.
	 */
	fprop_fraction_percpu(&करोm->completions, dtc->wb_completions,
			      &numerator, &denominator);

	wb_thresh = (thresh * (100 - bdi_min_ratio)) / 100;
	wb_thresh *= numerator;
	wb_thresh = भाग64_ul(wb_thresh, denominator);

	wb_min_max_ratio(dtc->wb, &wb_min_ratio, &wb_max_ratio);

	wb_thresh += (thresh * wb_min_ratio) / 100;
	अगर (wb_thresh > (thresh * wb_max_ratio) / 100)
		wb_thresh = thresh * wb_max_ratio / 100;

	वापस wb_thresh;
पूर्ण

अचिन्हित दीर्घ wb_calc_thresh(काष्ठा bdi_ग_लिखोback *wb, अचिन्हित दीर्घ thresh)
अणु
	काष्ठा dirty_throttle_control gdtc = अणु GDTC_INIT(wb),
					       .thresh = thresh पूर्ण;
	वापस __wb_calc_thresh(&gdtc);
पूर्ण

/*
 *                           setpoपूर्णांक - dirty 3
 *        f(dirty) := 1.0 + (----------------)
 *                           limit - setpoपूर्णांक
 *
 * it's a 3rd order polynomial that subjects to
 *
 * (1) f(मुक्तrun)  = 2.0 => rampup dirty_ratelimit reasonably fast
 * (2) f(setpoपूर्णांक) = 1.0 => the balance poपूर्णांक
 * (3) f(limit)    = 0   => the hard limit
 * (4) df/dx      <= 0	 => negative feedback control
 * (5) the बंदr to setpoपूर्णांक, the smaller |df/dx| (and the reverse)
 *     => fast response on large errors; small oscillation near setpoपूर्णांक
 */
अटल दीर्घ दीर्घ pos_ratio_polynom(अचिन्हित दीर्घ setpoपूर्णांक,
					  अचिन्हित दीर्घ dirty,
					  अचिन्हित दीर्घ limit)
अणु
	दीर्घ दीर्घ pos_ratio;
	दीर्घ x;

	x = भाग64_s64(((s64)setpoपूर्णांक - (s64)dirty) << RATELIMIT_CALC_SHIFT,
		      (limit - setpoपूर्णांक) | 1);
	pos_ratio = x;
	pos_ratio = pos_ratio * x >> RATELIMIT_CALC_SHIFT;
	pos_ratio = pos_ratio * x >> RATELIMIT_CALC_SHIFT;
	pos_ratio += 1 << RATELIMIT_CALC_SHIFT;

	वापस clamp(pos_ratio, 0LL, 2LL << RATELIMIT_CALC_SHIFT);
पूर्ण

/*
 * Dirty position control.
 *
 * (o) global/bdi setpoपूर्णांकs
 *
 * We want the dirty pages be balanced around the global/wb setpoपूर्णांकs.
 * When the number of dirty pages is higher/lower than the setpoपूर्णांक, the
 * dirty position control ratio (and hence task dirty ratelimit) will be
 * decreased/increased to bring the dirty pages back to the setpoपूर्णांक.
 *
 *     pos_ratio = 1 << RATELIMIT_CALC_SHIFT
 *
 *     अगर (dirty < setpoपूर्णांक) scale up   pos_ratio
 *     अगर (dirty > setpoपूर्णांक) scale करोwn pos_ratio
 *
 *     अगर (wb_dirty < wb_setpoपूर्णांक) scale up   pos_ratio
 *     अगर (wb_dirty > wb_setpoपूर्णांक) scale करोwn pos_ratio
 *
 *     task_ratelimit = dirty_ratelimit * pos_ratio >> RATELIMIT_CALC_SHIFT
 *
 * (o) global control line
 *
 *     ^ pos_ratio
 *     |
 *     |            |<===== global dirty control scope ======>|
 * 2.0 .............*
 *     |            .*
 *     |            . *
 *     |            .   *
 *     |            .     *
 *     |            .        *
 *     |            .            *
 * 1.0 ................................*
 *     |            .                  .     *
 *     |            .                  .          *
 *     |            .                  .              *
 *     |            .                  .                 *
 *     |            .                  .                    *
 *   0 +------------.------------------.----------------------*------------->
 *           मुक्तrun^          setpoपूर्णांक^                 limit^   dirty pages
 *
 * (o) wb control line
 *
 *     ^ pos_ratio
 *     |
 *     |            *
 *     |              *
 *     |                *
 *     |                  *
 *     |                    * |<=========== span ============>|
 * 1.0 .......................*
 *     |                      . *
 *     |                      .   *
 *     |                      .     *
 *     |                      .       *
 *     |                      .         *
 *     |                      .           *
 *     |                      .             *
 *     |                      .               *
 *     |                      .                 *
 *     |                      .                   *
 *     |                      .                     *
 * 1/4 ...............................................* * * * * * * * * * * *
 *     |                      .                         .
 *     |                      .                           .
 *     |                      .                             .
 *   0 +----------------------.-------------------------------.------------->
 *                wb_setpoपूर्णांक^                    x_पूर्णांकercept^
 *
 * The wb control line won't drop below pos_ratio=1/4, so that wb_dirty can
 * be smoothly throttled करोwn to normal अगर it starts high in situations like
 * - start writing to a slow SD card and a fast disk at the same समय. The SD
 *   card's wb_dirty may rush to many बार higher than wb_setpoपूर्णांक.
 * - the wb dirty thresh drops quickly due to change of JBOD workload
 */
अटल व्योम wb_position_ratio(काष्ठा dirty_throttle_control *dtc)
अणु
	काष्ठा bdi_ग_लिखोback *wb = dtc->wb;
	अचिन्हित दीर्घ ग_लिखो_bw = wb->avg_ग_लिखो_bandwidth;
	अचिन्हित दीर्घ मुक्तrun = dirty_मुक्तrun_उच्चमानing(dtc->thresh, dtc->bg_thresh);
	अचिन्हित दीर्घ limit = hard_dirty_limit(dtc_करोm(dtc), dtc->thresh);
	अचिन्हित दीर्घ wb_thresh = dtc->wb_thresh;
	अचिन्हित दीर्घ x_पूर्णांकercept;
	अचिन्हित दीर्घ setpoपूर्णांक;		/* dirty pages' target balance poपूर्णांक */
	अचिन्हित दीर्घ wb_setpoपूर्णांक;
	अचिन्हित दीर्घ span;
	दीर्घ दीर्घ pos_ratio;		/* क्रम scaling up/करोwn the rate limit */
	दीर्घ x;

	dtc->pos_ratio = 0;

	अगर (unlikely(dtc->dirty >= limit))
		वापस;

	/*
	 * global setpoपूर्णांक
	 *
	 * See comment क्रम pos_ratio_polynom().
	 */
	setpoपूर्णांक = (मुक्तrun + limit) / 2;
	pos_ratio = pos_ratio_polynom(setpoपूर्णांक, dtc->dirty, limit);

	/*
	 * The strictlimit feature is a tool preventing mistrusted fileप्रणालीs
	 * from growing a large number of dirty pages beक्रमe throttling. For
	 * such fileप्रणालीs balance_dirty_pages always checks wb counters
	 * against wb limits. Even अगर global "nr_dirty" is under "freerun".
	 * This is especially important क्रम fuse which sets bdi->max_ratio to
	 * 1% by शेष. Without strictlimit feature, fuse ग_लिखोback may
	 * consume arbitrary amount of RAM because it is accounted in
	 * NR_WRITEBACK_TEMP which is not involved in calculating "nr_dirty".
	 *
	 * Here, in wb_position_ratio(), we calculate pos_ratio based on
	 * two values: wb_dirty and wb_thresh. Let's consider an example:
	 * total amount of RAM is 16GB, bdi->max_ratio is equal to 1%, global
	 * limits are set by शेष to 10% and 20% (background and throttle).
	 * Then wb_thresh is 1% of 20% of 16GB. This amounts to ~8K pages.
	 * wb_calc_thresh(wb, bg_thresh) is about ~4K pages. wb_setpoपूर्णांक is
	 * about ~6K pages (as the average of background and throttle wb
	 * limits). The 3rd order polynomial will provide positive feedback अगर
	 * wb_dirty is under wb_setpoपूर्णांक and vice versa.
	 *
	 * Note, that we cannot use global counters in these calculations
	 * because we want to throttle process writing to a strictlimit wb
	 * much earlier than global "freerun" is reached (~23MB vs. ~2.3GB
	 * in the example above).
	 */
	अगर (unlikely(wb->bdi->capabilities & BDI_CAP_STRICTLIMIT)) अणु
		दीर्घ दीर्घ wb_pos_ratio;

		अगर (dtc->wb_dirty < 8) अणु
			dtc->pos_ratio = min_t(दीर्घ दीर्घ, pos_ratio * 2,
					   2 << RATELIMIT_CALC_SHIFT);
			वापस;
		पूर्ण

		अगर (dtc->wb_dirty >= wb_thresh)
			वापस;

		wb_setpoपूर्णांक = dirty_मुक्तrun_उच्चमानing(wb_thresh,
						    dtc->wb_bg_thresh);

		अगर (wb_setpoपूर्णांक == 0 || wb_setpoपूर्णांक == wb_thresh)
			वापस;

		wb_pos_ratio = pos_ratio_polynom(wb_setpoपूर्णांक, dtc->wb_dirty,
						 wb_thresh);

		/*
		 * Typically, क्रम strictlimit हाल, wb_setpoपूर्णांक << setpoपूर्णांक
		 * and pos_ratio >> wb_pos_ratio. In the other words global
		 * state ("dirty") is not limiting factor and we have to
		 * make decision based on wb counters. But there is an
		 * important हाल when global pos_ratio should get precedence:
		 * global limits are exceeded (e.g. due to activities on other
		 * wb's) जबतक given strictlimit wb is below limit.
		 *
		 * "pos_ratio * wb_pos_ratio" would work क्रम the हाल above,
		 * but it would look too non-natural क्रम the हाल of all
		 * activity in the प्रणाली coming from a single strictlimit wb
		 * with bdi->max_ratio == 100%.
		 *
		 * Note that min() below somewhat changes the dynamics of the
		 * control प्रणाली. Normally, pos_ratio value can be well over 3
		 * (when globally we are at मुक्तrun and wb is well below wb
		 * setpoपूर्णांक). Now the maximum pos_ratio in the same situation
		 * is 2. We might want to tweak this अगर we observe the control
		 * प्रणाली is too slow to adapt.
		 */
		dtc->pos_ratio = min(pos_ratio, wb_pos_ratio);
		वापस;
	पूर्ण

	/*
	 * We have computed basic pos_ratio above based on global situation. If
	 * the wb is over/under its share of dirty pages, we want to scale
	 * pos_ratio further करोwn/up. That is करोne by the following mechanism.
	 */

	/*
	 * wb setpoपूर्णांक
	 *
	 *        f(wb_dirty) := 1.0 + k * (wb_dirty - wb_setpoपूर्णांक)
	 *
	 *                        x_पूर्णांकercept - wb_dirty
	 *                     := --------------------------
	 *                        x_पूर्णांकercept - wb_setpoपूर्णांक
	 *
	 * The मुख्य wb control line is a linear function that subjects to
	 *
	 * (1) f(wb_setpoपूर्णांक) = 1.0
	 * (2) k = - 1 / (8 * ग_लिखो_bw)  (in single wb हाल)
	 *     or equally: x_पूर्णांकercept = wb_setpoपूर्णांक + 8 * ग_लिखो_bw
	 *
	 * For single wb हाल, the dirty pages are observed to fluctuate
	 * regularly within range
	 *        [wb_setpoपूर्णांक - ग_लिखो_bw/2, wb_setpoपूर्णांक + ग_लिखो_bw/2]
	 * क्रम various fileप्रणालीs, where (2) can yield in a reasonable 12.5%
	 * fluctuation range क्रम pos_ratio.
	 *
	 * For JBOD हाल, wb_thresh (not wb_dirty!) could fluctuate up to its
	 * own size, so move the slope over accordingly and choose a slope that
	 * yields 100% pos_ratio fluctuation on suddenly द्विगुनd wb_thresh.
	 */
	अगर (unlikely(wb_thresh > dtc->thresh))
		wb_thresh = dtc->thresh;
	/*
	 * It's very possible that wb_thresh is बंद to 0 not because the
	 * device is slow, but that it has reमुख्यed inactive क्रम दीर्घ समय.
	 * Honour such devices a reasonable good (hopefully IO efficient)
	 * threshold, so that the occasional ग_लिखोs won't be blocked and active
	 * ग_लिखोs can rampup the threshold quickly.
	 */
	wb_thresh = max(wb_thresh, (limit - dtc->dirty) / 8);
	/*
	 * scale global setpoपूर्णांक to wb's:
	 *	wb_setpoपूर्णांक = setpoपूर्णांक * wb_thresh / thresh
	 */
	x = भाग_u64((u64)wb_thresh << 16, dtc->thresh | 1);
	wb_setpoपूर्णांक = setpoपूर्णांक * (u64)x >> 16;
	/*
	 * Use span=(8*ग_लिखो_bw) in single wb हाल as indicated by
	 * (thresh - wb_thresh ~= 0) and transit to wb_thresh in JBOD हाल.
	 *
	 *        wb_thresh                    thresh - wb_thresh
	 * span = --------- * (8 * ग_लिखो_bw) + ------------------ * wb_thresh
	 *         thresh                           thresh
	 */
	span = (dtc->thresh - wb_thresh + 8 * ग_लिखो_bw) * (u64)x >> 16;
	x_पूर्णांकercept = wb_setpoपूर्णांक + span;

	अगर (dtc->wb_dirty < x_पूर्णांकercept - span / 4) अणु
		pos_ratio = भाग64_u64(pos_ratio * (x_पूर्णांकercept - dtc->wb_dirty),
				      (x_पूर्णांकercept - wb_setpoपूर्णांक) | 1);
	पूर्ण अन्यथा
		pos_ratio /= 4;

	/*
	 * wb reserve area, safeguard against dirty pool underrun and disk idle
	 * It may push the desired control poपूर्णांक of global dirty pages higher
	 * than setpoपूर्णांक.
	 */
	x_पूर्णांकercept = wb_thresh / 2;
	अगर (dtc->wb_dirty < x_पूर्णांकercept) अणु
		अगर (dtc->wb_dirty > x_पूर्णांकercept / 8)
			pos_ratio = भाग_u64(pos_ratio * x_पूर्णांकercept,
					    dtc->wb_dirty);
		अन्यथा
			pos_ratio *= 8;
	पूर्ण

	dtc->pos_ratio = pos_ratio;
पूर्ण

अटल व्योम wb_update_ग_लिखो_bandwidth(काष्ठा bdi_ग_लिखोback *wb,
				      अचिन्हित दीर्घ elapsed,
				      अचिन्हित दीर्घ written)
अणु
	स्थिर अचिन्हित दीर्घ period = roundup_घात_of_two(3 * HZ);
	अचिन्हित दीर्घ avg = wb->avg_ग_लिखो_bandwidth;
	अचिन्हित दीर्घ old = wb->ग_लिखो_bandwidth;
	u64 bw;

	/*
	 * bw = written * HZ / elapsed
	 *
	 *                   bw * elapsed + ग_लिखो_bandwidth * (period - elapsed)
	 * ग_लिखो_bandwidth = ---------------------------------------------------
	 *                                          period
	 *
	 * @written may have decreased due to account_page_redirty().
	 * Aव्योम underflowing @bw calculation.
	 */
	bw = written - min(written, wb->written_stamp);
	bw *= HZ;
	अगर (unlikely(elapsed > period)) अणु
		bw = भाग64_ul(bw, elapsed);
		avg = bw;
		जाओ out;
	पूर्ण
	bw += (u64)wb->ग_लिखो_bandwidth * (period - elapsed);
	bw >>= ilog2(period);

	/*
	 * one more level of smoothing, क्रम filtering out sudden spikes
	 */
	अगर (avg > old && old >= (अचिन्हित दीर्घ)bw)
		avg -= (avg - old) >> 3;

	अगर (avg < old && old <= (अचिन्हित दीर्घ)bw)
		avg += (old - avg) >> 3;

out:
	/* keep avg > 0 to guarantee that tot > 0 अगर there are dirty wbs */
	avg = max(avg, 1LU);
	अगर (wb_has_dirty_io(wb)) अणु
		दीर्घ delta = avg - wb->avg_ग_लिखो_bandwidth;
		WARN_ON_ONCE(atomic_दीर्घ_add_वापस(delta,
					&wb->bdi->tot_ग_लिखो_bandwidth) <= 0);
	पूर्ण
	wb->ग_लिखो_bandwidth = bw;
	wb->avg_ग_लिखो_bandwidth = avg;
पूर्ण

अटल व्योम update_dirty_limit(काष्ठा dirty_throttle_control *dtc)
अणु
	काष्ठा wb_करोमुख्य *करोm = dtc_करोm(dtc);
	अचिन्हित दीर्घ thresh = dtc->thresh;
	अचिन्हित दीर्घ limit = करोm->dirty_limit;

	/*
	 * Follow up in one step.
	 */
	अगर (limit < thresh) अणु
		limit = thresh;
		जाओ update;
	पूर्ण

	/*
	 * Follow करोwn slowly. Use the higher one as the target, because thresh
	 * may drop below dirty. This is exactly the reason to पूर्णांकroduce
	 * करोm->dirty_limit which is guaranteed to lie above the dirty pages.
	 */
	thresh = max(thresh, dtc->dirty);
	अगर (limit > thresh) अणु
		limit -= (limit - thresh) >> 5;
		जाओ update;
	पूर्ण
	वापस;
update:
	करोm->dirty_limit = limit;
पूर्ण

अटल व्योम करोमुख्य_update_bandwidth(काष्ठा dirty_throttle_control *dtc,
				    अचिन्हित दीर्घ now)
अणु
	काष्ठा wb_करोमुख्य *करोm = dtc_करोm(dtc);

	/*
	 * check locklessly first to optimize away locking क्रम the most समय
	 */
	अगर (समय_beक्रमe(now, करोm->dirty_limit_tstamp + BANDWIDTH_INTERVAL))
		वापस;

	spin_lock(&करोm->lock);
	अगर (समय_after_eq(now, करोm->dirty_limit_tstamp + BANDWIDTH_INTERVAL)) अणु
		update_dirty_limit(dtc);
		करोm->dirty_limit_tstamp = now;
	पूर्ण
	spin_unlock(&करोm->lock);
पूर्ण

/*
 * Maपूर्णांकain wb->dirty_ratelimit, the base dirty throttle rate.
 *
 * Normal wb tasks will be curbed at or below it in दीर्घ term.
 * Obviously it should be around (ग_लिखो_bw / N) when there are N dd tasks.
 */
अटल व्योम wb_update_dirty_ratelimit(काष्ठा dirty_throttle_control *dtc,
				      अचिन्हित दीर्घ dirtied,
				      अचिन्हित दीर्घ elapsed)
अणु
	काष्ठा bdi_ग_लिखोback *wb = dtc->wb;
	अचिन्हित दीर्घ dirty = dtc->dirty;
	अचिन्हित दीर्घ मुक्तrun = dirty_मुक्तrun_उच्चमानing(dtc->thresh, dtc->bg_thresh);
	अचिन्हित दीर्घ limit = hard_dirty_limit(dtc_करोm(dtc), dtc->thresh);
	अचिन्हित दीर्घ setpoपूर्णांक = (मुक्तrun + limit) / 2;
	अचिन्हित दीर्घ ग_लिखो_bw = wb->avg_ग_लिखो_bandwidth;
	अचिन्हित दीर्घ dirty_ratelimit = wb->dirty_ratelimit;
	अचिन्हित दीर्घ dirty_rate;
	अचिन्हित दीर्घ task_ratelimit;
	अचिन्हित दीर्घ balanced_dirty_ratelimit;
	अचिन्हित दीर्घ step;
	अचिन्हित दीर्घ x;
	अचिन्हित दीर्घ shअगरt;

	/*
	 * The dirty rate will match the ग_लिखोout rate in दीर्घ term, except
	 * when dirty pages are truncated by userspace or re-dirtied by FS.
	 */
	dirty_rate = (dirtied - wb->dirtied_stamp) * HZ / elapsed;

	/*
	 * task_ratelimit reflects each dd's dirty rate क्रम the past 200ms.
	 */
	task_ratelimit = (u64)dirty_ratelimit *
					dtc->pos_ratio >> RATELIMIT_CALC_SHIFT;
	task_ratelimit++; /* it helps rampup dirty_ratelimit from tiny values */

	/*
	 * A linear estimation of the "balanced" throttle rate. The theory is,
	 * अगर there are N dd tasks, each throttled at task_ratelimit, the wb's
	 * dirty_rate will be measured to be (N * task_ratelimit). So the below
	 * क्रमmula will yield the balanced rate limit (ग_लिखो_bw / N).
	 *
	 * Note that the expanded क्रमm is not a pure rate feedback:
	 *	rate_(i+1) = rate_(i) * (ग_लिखो_bw / dirty_rate)		     (1)
	 * but also takes pos_ratio पूर्णांकo account:
	 *	rate_(i+1) = rate_(i) * (ग_लिखो_bw / dirty_rate) * pos_ratio  (2)
	 *
	 * (1) is not realistic because pos_ratio also takes part in balancing
	 * the dirty rate.  Consider the state
	 *	pos_ratio = 0.5						     (3)
	 *	rate = 2 * (ग_लिखो_bw / N)				     (4)
	 * If (1) is used, it will stuck in that state! Because each dd will
	 * be throttled at
	 *	task_ratelimit = pos_ratio * rate = (ग_लिखो_bw / N)	     (5)
	 * yielding
	 *	dirty_rate = N * task_ratelimit = ग_लिखो_bw		     (6)
	 * put (6) पूर्णांकo (1) we get
	 *	rate_(i+1) = rate_(i)					     (7)
	 *
	 * So we end up using (2) to always keep
	 *	rate_(i+1) ~= (ग_लिखो_bw / N)				     (8)
	 * regardless of the value of pos_ratio. As दीर्घ as (8) is satisfied,
	 * pos_ratio is able to drive itself to 1.0, which is not only where
	 * the dirty count meet the setpoपूर्णांक, but also where the slope of
	 * pos_ratio is most flat and hence task_ratelimit is least fluctuated.
	 */
	balanced_dirty_ratelimit = भाग_u64((u64)task_ratelimit * ग_लिखो_bw,
					   dirty_rate | 1);
	/*
	 * balanced_dirty_ratelimit ~= (ग_लिखो_bw / N) <= ग_लिखो_bw
	 */
	अगर (unlikely(balanced_dirty_ratelimit > ग_लिखो_bw))
		balanced_dirty_ratelimit = ग_लिखो_bw;

	/*
	 * We could safely करो this and वापस immediately:
	 *
	 *	wb->dirty_ratelimit = balanced_dirty_ratelimit;
	 *
	 * However to get a more stable dirty_ratelimit, the below elaborated
	 * code makes use of task_ratelimit to filter out singular poपूर्णांकs and
	 * limit the step size.
	 *
	 * The below code essentially only uses the relative value of
	 *
	 *	task_ratelimit - dirty_ratelimit
	 *	= (pos_ratio - 1) * dirty_ratelimit
	 *
	 * which reflects the direction and size of dirty position error.
	 */

	/*
	 * dirty_ratelimit will follow balanced_dirty_ratelimit अगरf
	 * task_ratelimit is on the same side of dirty_ratelimit, too.
	 * For example, when
	 * - dirty_ratelimit > balanced_dirty_ratelimit
	 * - dirty_ratelimit > task_ratelimit (dirty pages are above setpoपूर्णांक)
	 * lowering dirty_ratelimit will help meet both the position and rate
	 * control tarमाला_लो. Otherwise, करोn't update dirty_ratelimit अगर it will
	 * only help meet the rate target. After all, what the users ultimately
	 * feel and care are stable dirty rate and small position error.
	 *
	 * |task_ratelimit - dirty_ratelimit| is used to limit the step size
	 * and filter out the singular poपूर्णांकs of balanced_dirty_ratelimit. Which
	 * keeps jumping around अक्रमomly and can even leap far away at बार
	 * due to the small 200ms estimation period of dirty_rate (we want to
	 * keep that period small to reduce समय lags).
	 */
	step = 0;

	/*
	 * For strictlimit हाल, calculations above were based on wb counters
	 * and limits (starting from pos_ratio = wb_position_ratio() and up to
	 * balanced_dirty_ratelimit = task_ratelimit * ग_लिखो_bw / dirty_rate).
	 * Hence, to calculate "step" properly, we have to use wb_dirty as
	 * "dirty" and wb_setpoपूर्णांक as "setpoint".
	 *
	 * We rampup dirty_ratelimit क्रमcibly अगर wb_dirty is low because
	 * it's possible that wb_thresh is बंद to zero due to inactivity
	 * of backing device.
	 */
	अगर (unlikely(wb->bdi->capabilities & BDI_CAP_STRICTLIMIT)) अणु
		dirty = dtc->wb_dirty;
		अगर (dtc->wb_dirty < 8)
			setpoपूर्णांक = dtc->wb_dirty + 1;
		अन्यथा
			setpoपूर्णांक = (dtc->wb_thresh + dtc->wb_bg_thresh) / 2;
	पूर्ण

	अगर (dirty < setpoपूर्णांक) अणु
		x = min3(wb->balanced_dirty_ratelimit,
			 balanced_dirty_ratelimit, task_ratelimit);
		अगर (dirty_ratelimit < x)
			step = x - dirty_ratelimit;
	पूर्ण अन्यथा अणु
		x = max3(wb->balanced_dirty_ratelimit,
			 balanced_dirty_ratelimit, task_ratelimit);
		अगर (dirty_ratelimit > x)
			step = dirty_ratelimit - x;
	पूर्ण

	/*
	 * Don't pursue 100% rate matching. It's impossible since the balanced
	 * rate itself is स्थिरantly fluctuating. So decrease the track speed
	 * when it माला_लो बंद to the target. Helps eliminate poपूर्णांकless tremors.
	 */
	shअगरt = dirty_ratelimit / (2 * step + 1);
	अगर (shअगरt < BITS_PER_LONG)
		step = DIV_ROUND_UP(step >> shअगरt, 8);
	अन्यथा
		step = 0;

	अगर (dirty_ratelimit < balanced_dirty_ratelimit)
		dirty_ratelimit += step;
	अन्यथा
		dirty_ratelimit -= step;

	wb->dirty_ratelimit = max(dirty_ratelimit, 1UL);
	wb->balanced_dirty_ratelimit = balanced_dirty_ratelimit;

	trace_bdi_dirty_ratelimit(wb, dirty_rate, task_ratelimit);
पूर्ण

अटल व्योम __wb_update_bandwidth(काष्ठा dirty_throttle_control *gdtc,
				  काष्ठा dirty_throttle_control *mdtc,
				  अचिन्हित दीर्घ start_समय,
				  bool update_ratelimit)
अणु
	काष्ठा bdi_ग_लिखोback *wb = gdtc->wb;
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ elapsed = now - wb->bw_समय_stamp;
	अचिन्हित दीर्घ dirtied;
	अचिन्हित दीर्घ written;

	lockdep_निश्चित_held(&wb->list_lock);

	/*
	 * rate-limit, only update once every 200ms.
	 */
	अगर (elapsed < BANDWIDTH_INTERVAL)
		वापस;

	dirtied = percpu_counter_पढ़ो(&wb->stat[WB_सूचीTIED]);
	written = percpu_counter_पढ़ो(&wb->stat[WB_WRITTEN]);

	/*
	 * Skip quiet periods when disk bandwidth is under-utilized.
	 * (at least 1s idle समय between two flusher runs)
	 */
	अगर (elapsed > HZ && समय_beक्रमe(wb->bw_समय_stamp, start_समय))
		जाओ snapshot;

	अगर (update_ratelimit) अणु
		करोमुख्य_update_bandwidth(gdtc, now);
		wb_update_dirty_ratelimit(gdtc, dirtied, elapsed);

		/*
		 * @mdtc is always शून्य अगर !CGROUP_WRITEBACK but the
		 * compiler has no way to figure that out.  Help it.
		 */
		अगर (IS_ENABLED(CONFIG_CGROUP_WRITEBACK) && mdtc) अणु
			करोमुख्य_update_bandwidth(mdtc, now);
			wb_update_dirty_ratelimit(mdtc, dirtied, elapsed);
		पूर्ण
	पूर्ण
	wb_update_ग_लिखो_bandwidth(wb, elapsed, written);

snapshot:
	wb->dirtied_stamp = dirtied;
	wb->written_stamp = written;
	wb->bw_समय_stamp = now;
पूर्ण

व्योम wb_update_bandwidth(काष्ठा bdi_ग_लिखोback *wb, अचिन्हित दीर्घ start_समय)
अणु
	काष्ठा dirty_throttle_control gdtc = अणु GDTC_INIT(wb) पूर्ण;

	__wb_update_bandwidth(&gdtc, शून्य, start_समय, false);
पूर्ण

/*
 * After a task dirtied this many pages, balance_dirty_pages_ratelimited()
 * will look to see अगर it needs to start dirty throttling.
 *
 * If dirty_poll_पूर्णांकerval is too low, big NUMA machines will call the expensive
 * global_zone_page_state() too often. So scale it near-वर्ग_मूल to the safety margin
 * (the number of pages we may dirty without exceeding the dirty limits).
 */
अटल अचिन्हित दीर्घ dirty_poll_पूर्णांकerval(अचिन्हित दीर्घ dirty,
					 अचिन्हित दीर्घ thresh)
अणु
	अगर (thresh > dirty)
		वापस 1UL << (ilog2(thresh - dirty) >> 1);

	वापस 1;
पूर्ण

अटल अचिन्हित दीर्घ wb_max_छोड़ो(काष्ठा bdi_ग_लिखोback *wb,
				  अचिन्हित दीर्घ wb_dirty)
अणु
	अचिन्हित दीर्घ bw = wb->avg_ग_लिखो_bandwidth;
	अचिन्हित दीर्घ t;

	/*
	 * Limit छोड़ो समय क्रम small memory प्रणालीs. If sleeping क्रम too दीर्घ
	 * समय, a small pool of dirty/ग_लिखोback pages may go empty and disk go
	 * idle.
	 *
	 * 8 serves as the safety ratio.
	 */
	t = wb_dirty / (1 + bw / roundup_घात_of_two(1 + HZ / 8));
	t++;

	वापस min_t(अचिन्हित दीर्घ, t, MAX_PAUSE);
पूर्ण

अटल दीर्घ wb_min_छोड़ो(काष्ठा bdi_ग_लिखोback *wb,
			 दीर्घ max_छोड़ो,
			 अचिन्हित दीर्घ task_ratelimit,
			 अचिन्हित दीर्घ dirty_ratelimit,
			 पूर्णांक *nr_dirtied_छोड़ो)
अणु
	दीर्घ hi = ilog2(wb->avg_ग_लिखो_bandwidth);
	दीर्घ lo = ilog2(wb->dirty_ratelimit);
	दीर्घ t;		/* target छोड़ो */
	दीर्घ छोड़ो;	/* estimated next छोड़ो */
	पूर्णांक pages;	/* target nr_dirtied_छोड़ो */

	/* target क्रम 10ms छोड़ो on 1-dd हाल */
	t = max(1, HZ / 100);

	/*
	 * Scale up छोड़ो समय क्रम concurrent dirtiers in order to reduce CPU
	 * overheads.
	 *
	 * (N * 10ms) on 2^N concurrent tasks.
	 */
	अगर (hi > lo)
		t += (hi - lo) * (10 * HZ) / 1024;

	/*
	 * This is a bit convoluted. We try to base the next nr_dirtied_छोड़ो
	 * on the much more stable dirty_ratelimit. However the next छोड़ो समय
	 * will be computed based on task_ratelimit and the two rate limits may
	 * depart considerably at some समय. Especially अगर task_ratelimit goes
	 * below dirty_ratelimit/2 and the target छोड़ो is max_छोड़ो, the next
	 * छोड़ो समय will be max_छोड़ो*2 _trimmed करोwn_ to max_छोड़ो.  As a
	 * result task_ratelimit won't be executed faithfully, which could
	 * eventually bring करोwn dirty_ratelimit.
	 *
	 * We apply two rules to fix it up:
	 * 1) try to estimate the next छोड़ो समय and अगर necessary, use a lower
	 *    nr_dirtied_छोड़ो so as not to exceed max_छोड़ो. When this happens,
	 *    nr_dirtied_छोड़ो will be "dancing" with task_ratelimit.
	 * 2) limit the target छोड़ो समय to max_छोड़ो/2, so that the normal
	 *    small fluctuations of task_ratelimit won't trigger rule (1) and
	 *    nr_dirtied_छोड़ो will reमुख्य as stable as dirty_ratelimit.
	 */
	t = min(t, 1 + max_छोड़ो / 2);
	pages = dirty_ratelimit * t / roundup_घात_of_two(HZ);

	/*
	 * Tiny nr_dirtied_छोड़ो is found to hurt I/O perक्रमmance in the test
	 * हाल fio-mmap-अक्रमग_लिखो-64k, which करोes 16*अणुsync पढ़ो, async ग_लिखोपूर्ण.
	 * When the 16 consecutive पढ़ोs are often पूर्णांकerrupted by some dirty
	 * throttling छोड़ो during the async ग_लिखोs, cfq will go पूर्णांकo idles
	 * (deadline is fine). So push nr_dirtied_छोड़ो as high as possible
	 * until reaches सूचीTY_POLL_THRESH=32 pages.
	 */
	अगर (pages < सूचीTY_POLL_THRESH) अणु
		t = max_छोड़ो;
		pages = dirty_ratelimit * t / roundup_घात_of_two(HZ);
		अगर (pages > सूचीTY_POLL_THRESH) अणु
			pages = सूचीTY_POLL_THRESH;
			t = HZ * सूचीTY_POLL_THRESH / dirty_ratelimit;
		पूर्ण
	पूर्ण

	छोड़ो = HZ * pages / (task_ratelimit + 1);
	अगर (छोड़ो > max_छोड़ो) अणु
		t = max_छोड़ो;
		pages = task_ratelimit * t / roundup_घात_of_two(HZ);
	पूर्ण

	*nr_dirtied_छोड़ो = pages;
	/*
	 * The minimal छोड़ो समय will normally be half the target छोड़ो समय.
	 */
	वापस pages >= सूचीTY_POLL_THRESH ? 1 + t / 2 : t;
पूर्ण

अटल अंतरभूत व्योम wb_dirty_limits(काष्ठा dirty_throttle_control *dtc)
अणु
	काष्ठा bdi_ग_लिखोback *wb = dtc->wb;
	अचिन्हित दीर्घ wb_reclaimable;

	/*
	 * wb_thresh is not treated as some limiting factor as
	 * dirty_thresh, due to reasons
	 * - in JBOD setup, wb_thresh can fluctuate a lot
	 * - in a प्रणाली with HDD and USB key, the USB key may somehow
	 *   go पूर्णांकo state (wb_dirty >> wb_thresh) either because
	 *   wb_dirty starts high, or because wb_thresh drops low.
	 *   In this हाल we करोn't want to hard throttle the USB key
	 *   dirtiers क्रम 100 seconds until wb_dirty drops under
	 *   wb_thresh. Instead the auxiliary wb control line in
	 *   wb_position_ratio() will let the dirtier task progress
	 *   at some rate <= (ग_लिखो_bw / 2) क्रम bringing करोwn wb_dirty.
	 */
	dtc->wb_thresh = __wb_calc_thresh(dtc);
	dtc->wb_bg_thresh = dtc->thresh ?
		भाग_u64((u64)dtc->wb_thresh * dtc->bg_thresh, dtc->thresh) : 0;

	/*
	 * In order to aव्योम the stacked BDI deadlock we need
	 * to ensure we accurately count the 'dirty' pages when
	 * the threshold is low.
	 *
	 * Otherwise it would be possible to get thresh+n pages
	 * reported dirty, even though there are thresh-m pages
	 * actually dirty; with m+n sitting in the percpu
	 * deltas.
	 */
	अगर (dtc->wb_thresh < 2 * wb_stat_error()) अणु
		wb_reclaimable = wb_stat_sum(wb, WB_RECLAIMABLE);
		dtc->wb_dirty = wb_reclaimable + wb_stat_sum(wb, WB_WRITEBACK);
	पूर्ण अन्यथा अणु
		wb_reclaimable = wb_stat(wb, WB_RECLAIMABLE);
		dtc->wb_dirty = wb_reclaimable + wb_stat(wb, WB_WRITEBACK);
	पूर्ण
पूर्ण

/*
 * balance_dirty_pages() must be called by processes which are generating dirty
 * data.  It looks at the number of dirty pages in the machine and will क्रमce
 * the caller to रुको once crossing the (background_thresh + dirty_thresh) / 2.
 * If we're over `background_thresh' then the ग_लिखोback thपढ़ोs are woken to
 * perक्रमm some ग_लिखोout.
 */
अटल व्योम balance_dirty_pages(काष्ठा bdi_ग_लिखोback *wb,
				अचिन्हित दीर्घ pages_dirtied)
अणु
	काष्ठा dirty_throttle_control gdtc_stor = अणु GDTC_INIT(wb) पूर्ण;
	काष्ठा dirty_throttle_control mdtc_stor = अणु MDTC_INIT(wb, &gdtc_stor) पूर्ण;
	काष्ठा dirty_throttle_control * स्थिर gdtc = &gdtc_stor;
	काष्ठा dirty_throttle_control * स्थिर mdtc = mdtc_valid(&mdtc_stor) ?
						     &mdtc_stor : शून्य;
	काष्ठा dirty_throttle_control *sdtc;
	अचिन्हित दीर्घ nr_reclaimable;	/* = file_dirty */
	दीर्घ period;
	दीर्घ छोड़ो;
	दीर्घ max_छोड़ो;
	दीर्घ min_छोड़ो;
	पूर्णांक nr_dirtied_छोड़ो;
	bool dirty_exceeded = false;
	अचिन्हित दीर्घ task_ratelimit;
	अचिन्हित दीर्घ dirty_ratelimit;
	काष्ठा backing_dev_info *bdi = wb->bdi;
	bool strictlimit = bdi->capabilities & BDI_CAP_STRICTLIMIT;
	अचिन्हित दीर्घ start_समय = jअगरfies;

	क्रम (;;) अणु
		अचिन्हित दीर्घ now = jअगरfies;
		अचिन्हित दीर्घ dirty, thresh, bg_thresh;
		अचिन्हित दीर्घ m_dirty = 0;	/* stop bogus uninit warnings */
		अचिन्हित दीर्घ m_thresh = 0;
		अचिन्हित दीर्घ m_bg_thresh = 0;

		nr_reclaimable = global_node_page_state(NR_खाता_सूचीTY);
		gdtc->avail = global_dirtyable_memory();
		gdtc->dirty = nr_reclaimable + global_node_page_state(NR_WRITEBACK);

		करोमुख्य_dirty_limits(gdtc);

		अगर (unlikely(strictlimit)) अणु
			wb_dirty_limits(gdtc);

			dirty = gdtc->wb_dirty;
			thresh = gdtc->wb_thresh;
			bg_thresh = gdtc->wb_bg_thresh;
		पूर्ण अन्यथा अणु
			dirty = gdtc->dirty;
			thresh = gdtc->thresh;
			bg_thresh = gdtc->bg_thresh;
		पूर्ण

		अगर (mdtc) अणु
			अचिन्हित दीर्घ filepages, headroom, ग_लिखोback;

			/*
			 * If @wb beदीर्घs to !root memcg, repeat the same
			 * basic calculations क्रम the memcg करोमुख्य.
			 */
			mem_cgroup_wb_stats(wb, &filepages, &headroom,
					    &mdtc->dirty, &ग_लिखोback);
			mdtc->dirty += ग_लिखोback;
			mdtc_calc_avail(mdtc, filepages, headroom);

			करोमुख्य_dirty_limits(mdtc);

			अगर (unlikely(strictlimit)) अणु
				wb_dirty_limits(mdtc);
				m_dirty = mdtc->wb_dirty;
				m_thresh = mdtc->wb_thresh;
				m_bg_thresh = mdtc->wb_bg_thresh;
			पूर्ण अन्यथा अणु
				m_dirty = mdtc->dirty;
				m_thresh = mdtc->thresh;
				m_bg_thresh = mdtc->bg_thresh;
			पूर्ण
		पूर्ण

		/*
		 * Throttle it only when the background ग_लिखोback cannot
		 * catch-up. This aव्योमs (excessively) small ग_लिखोouts
		 * when the wb limits are ramping up in हाल of !strictlimit.
		 *
		 * In strictlimit हाल make decision based on the wb counters
		 * and limits. Small ग_लिखोouts when the wb limits are ramping
		 * up are the price we consciously pay क्रम strictlimit-ing.
		 *
		 * If memcg करोमुख्य is in effect, @dirty should be under
		 * both global and memcg मुक्तrun उच्चमानings.
		 */
		अगर (dirty <= dirty_मुक्तrun_उच्चमानing(thresh, bg_thresh) &&
		    (!mdtc ||
		     m_dirty <= dirty_मुक्तrun_उच्चमानing(m_thresh, m_bg_thresh))) अणु
			अचिन्हित दीर्घ पूर्णांकv;
			अचिन्हित दीर्घ m_पूर्णांकv;

मुक्त_running:
			पूर्णांकv = dirty_poll_पूर्णांकerval(dirty, thresh);
			m_पूर्णांकv = अच_दीर्घ_उच्च;

			current->dirty_छोड़ोd_when = now;
			current->nr_dirtied = 0;
			अगर (mdtc)
				m_पूर्णांकv = dirty_poll_पूर्णांकerval(m_dirty, m_thresh);
			current->nr_dirtied_छोड़ो = min(पूर्णांकv, m_पूर्णांकv);
			अवरोध;
		पूर्ण

		अगर (unlikely(!ग_लिखोback_in_progress(wb)))
			wb_start_background_ग_लिखोback(wb);

		mem_cgroup_flush_क्रमeign(wb);

		/*
		 * Calculate global करोमुख्य's pos_ratio and select the
		 * global dtc by शेष.
		 */
		अगर (!strictlimit) अणु
			wb_dirty_limits(gdtc);

			अगर ((current->flags & PF_LOCAL_THROTTLE) &&
			    gdtc->wb_dirty <
			    dirty_मुक्तrun_उच्चमानing(gdtc->wb_thresh,
						  gdtc->wb_bg_thresh))
				/*
				 * LOCAL_THROTTLE tasks must not be throttled
				 * when below the per-wb मुक्तrun उच्चमानing.
				 */
				जाओ मुक्त_running;
		पूर्ण

		dirty_exceeded = (gdtc->wb_dirty > gdtc->wb_thresh) &&
			((gdtc->dirty > gdtc->thresh) || strictlimit);

		wb_position_ratio(gdtc);
		sdtc = gdtc;

		अगर (mdtc) अणु
			/*
			 * If memcg करोमुख्य is in effect, calculate its
			 * pos_ratio.  @wb should satisfy स्थिरraपूर्णांकs from
			 * both global and memcg करोमुख्यs.  Choose the one
			 * w/ lower pos_ratio.
			 */
			अगर (!strictlimit) अणु
				wb_dirty_limits(mdtc);

				अगर ((current->flags & PF_LOCAL_THROTTLE) &&
				    mdtc->wb_dirty <
				    dirty_मुक्तrun_उच्चमानing(mdtc->wb_thresh,
							  mdtc->wb_bg_thresh))
					/*
					 * LOCAL_THROTTLE tasks must not be
					 * throttled when below the per-wb
					 * मुक्तrun उच्चमानing.
					 */
					जाओ मुक्त_running;
			पूर्ण
			dirty_exceeded |= (mdtc->wb_dirty > mdtc->wb_thresh) &&
				((mdtc->dirty > mdtc->thresh) || strictlimit);

			wb_position_ratio(mdtc);
			अगर (mdtc->pos_ratio < gdtc->pos_ratio)
				sdtc = mdtc;
		पूर्ण

		अगर (dirty_exceeded && !wb->dirty_exceeded)
			wb->dirty_exceeded = 1;

		अगर (समय_is_beक्रमe_jअगरfies(wb->bw_समय_stamp +
					   BANDWIDTH_INTERVAL)) अणु
			spin_lock(&wb->list_lock);
			__wb_update_bandwidth(gdtc, mdtc, start_समय, true);
			spin_unlock(&wb->list_lock);
		पूर्ण

		/* throttle according to the chosen dtc */
		dirty_ratelimit = wb->dirty_ratelimit;
		task_ratelimit = ((u64)dirty_ratelimit * sdtc->pos_ratio) >>
							RATELIMIT_CALC_SHIFT;
		max_छोड़ो = wb_max_छोड़ो(wb, sdtc->wb_dirty);
		min_छोड़ो = wb_min_छोड़ो(wb, max_छोड़ो,
					 task_ratelimit, dirty_ratelimit,
					 &nr_dirtied_छोड़ो);

		अगर (unlikely(task_ratelimit == 0)) अणु
			period = max_छोड़ो;
			छोड़ो = max_छोड़ो;
			जाओ छोड़ो;
		पूर्ण
		period = HZ * pages_dirtied / task_ratelimit;
		छोड़ो = period;
		अगर (current->dirty_छोड़ोd_when)
			छोड़ो -= now - current->dirty_छोड़ोd_when;
		/*
		 * For less than 1s think समय (ext3/4 may block the dirtier
		 * क्रम up to 800ms from समय to समय on 1-HDD; so करोes xfs,
		 * however at much less frequency), try to compensate it in
		 * future periods by updating the भव समय; otherwise just
		 * करो a reset, as it may be a light dirtier.
		 */
		अगर (छोड़ो < min_छोड़ो) अणु
			trace_balance_dirty_pages(wb,
						  sdtc->thresh,
						  sdtc->bg_thresh,
						  sdtc->dirty,
						  sdtc->wb_thresh,
						  sdtc->wb_dirty,
						  dirty_ratelimit,
						  task_ratelimit,
						  pages_dirtied,
						  period,
						  min(छोड़ो, 0L),
						  start_समय);
			अगर (छोड़ो < -HZ) अणु
				current->dirty_छोड़ोd_when = now;
				current->nr_dirtied = 0;
			पूर्ण अन्यथा अगर (period) अणु
				current->dirty_छोड़ोd_when += period;
				current->nr_dirtied = 0;
			पूर्ण अन्यथा अगर (current->nr_dirtied_छोड़ो <= pages_dirtied)
				current->nr_dirtied_छोड़ो += pages_dirtied;
			अवरोध;
		पूर्ण
		अगर (unlikely(छोड़ो > max_छोड़ो)) अणु
			/* क्रम occasional dropped task_ratelimit */
			now += min(छोड़ो - max_छोड़ो, max_छोड़ो);
			छोड़ो = max_छोड़ो;
		पूर्ण

छोड़ो:
		trace_balance_dirty_pages(wb,
					  sdtc->thresh,
					  sdtc->bg_thresh,
					  sdtc->dirty,
					  sdtc->wb_thresh,
					  sdtc->wb_dirty,
					  dirty_ratelimit,
					  task_ratelimit,
					  pages_dirtied,
					  period,
					  छोड़ो,
					  start_समय);
		__set_current_state(TASK_KILLABLE);
		wb->dirty_sleep = now;
		io_schedule_समयout(छोड़ो);

		current->dirty_छोड़ोd_when = now + छोड़ो;
		current->nr_dirtied = 0;
		current->nr_dirtied_छोड़ो = nr_dirtied_छोड़ो;

		/*
		 * This is typically equal to (dirty < thresh) and can also
		 * keep "1000+ dd on a slow USB stick" under control.
		 */
		अगर (task_ratelimit)
			अवरोध;

		/*
		 * In the हाल of an unresponsive NFS server and the NFS dirty
		 * pages exceeds dirty_thresh, give the other good wb's a pipe
		 * to go through, so that tasks on them still reमुख्य responsive.
		 *
		 * In theory 1 page is enough to keep the consumer-producer
		 * pipe going: the flusher cleans 1 page => the task dirties 1
		 * more page. However wb_dirty has accounting errors.  So use
		 * the larger and more IO मित्रly wb_stat_error.
		 */
		अगर (sdtc->wb_dirty <= wb_stat_error())
			अवरोध;

		अगर (fatal_संकेत_pending(current))
			अवरोध;
	पूर्ण

	अगर (!dirty_exceeded && wb->dirty_exceeded)
		wb->dirty_exceeded = 0;

	अगर (ग_लिखोback_in_progress(wb))
		वापस;

	/*
	 * In laptop mode, we रुको until hitting the higher threshold beक्रमe
	 * starting background ग_लिखोout, and then ग_लिखो out all the way करोwn
	 * to the lower threshold.  So slow ग_लिखोrs cause minimal disk activity.
	 *
	 * In normal mode, we start background ग_लिखोout at the lower
	 * background_thresh, to keep the amount of dirty memory low.
	 */
	अगर (laptop_mode)
		वापस;

	अगर (nr_reclaimable > gdtc->bg_thresh)
		wb_start_background_ग_लिखोback(wb);
पूर्ण

अटल DEFINE_PER_CPU(पूर्णांक, bdp_ratelimits);

/*
 * Normal tasks are throttled by
 *	loop अणु
 *		dirty tsk->nr_dirtied_छोड़ो pages;
 *		take a snap in balance_dirty_pages();
 *	पूर्ण
 * However there is a worst हाल. If every task निकास immediately when dirtied
 * (tsk->nr_dirtied_छोड़ो - 1) pages, balance_dirty_pages() will never be
 * called to throttle the page dirties. The solution is to save the not yet
 * throttled page dirties in dirty_throttle_leaks on task निकास and अक्षरge them
 * अक्रमomly पूर्णांकo the running tasks. This works well क्रम the above worst हाल,
 * as the new task will pick up and accumulate the old task's leaked dirty
 * count and eventually get throttled.
 */
DEFINE_PER_CPU(पूर्णांक, dirty_throttle_leaks) = 0;

/**
 * balance_dirty_pages_ratelimited - balance dirty memory state
 * @mapping: address_space which was dirtied
 *
 * Processes which are dirtying memory should call in here once क्रम each page
 * which was newly dirtied.  The function will periodically check the प्रणाली's
 * dirty state and will initiate ग_लिखोback अगर needed.
 *
 * On really big machines, get_ग_लिखोback_state is expensive, so try to aव्योम
 * calling it too often (ratelimiting).  But once we're over the dirty memory
 * limit we decrease the ratelimiting by a lot, to prevent inभागidual processes
 * from overshooting the limit by (ratelimit_pages) each.
 */
व्योम balance_dirty_pages_ratelimited(काष्ठा address_space *mapping)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा backing_dev_info *bdi = inode_to_bdi(inode);
	काष्ठा bdi_ग_लिखोback *wb = शून्य;
	पूर्णांक ratelimit;
	पूर्णांक *p;

	अगर (!(bdi->capabilities & BDI_CAP_WRITEBACK))
		वापस;

	अगर (inode_cgwb_enabled(inode))
		wb = wb_get_create_current(bdi, GFP_KERNEL);
	अगर (!wb)
		wb = &bdi->wb;

	ratelimit = current->nr_dirtied_छोड़ो;
	अगर (wb->dirty_exceeded)
		ratelimit = min(ratelimit, 32 >> (PAGE_SHIFT - 10));

	preempt_disable();
	/*
	 * This prevents one CPU to accumulate too many dirtied pages without
	 * calling पूर्णांकo balance_dirty_pages(), which can happen when there are
	 * 1000+ tasks, all of them start dirtying pages at exactly the same
	 * समय, hence all honoured too large initial task->nr_dirtied_छोड़ो.
	 */
	p =  this_cpu_ptr(&bdp_ratelimits);
	अगर (unlikely(current->nr_dirtied >= ratelimit))
		*p = 0;
	अन्यथा अगर (unlikely(*p >= ratelimit_pages)) अणु
		*p = 0;
		ratelimit = 0;
	पूर्ण
	/*
	 * Pick up the dirtied pages by the निकासed tasks. This aव्योमs lots of
	 * लघु-lived tasks (eg. gcc invocations in a kernel build) escaping
	 * the dirty throttling and livelock other दीर्घ-run dirtiers.
	 */
	p = this_cpu_ptr(&dirty_throttle_leaks);
	अगर (*p > 0 && current->nr_dirtied < ratelimit) अणु
		अचिन्हित दीर्घ nr_pages_dirtied;
		nr_pages_dirtied = min(*p, ratelimit - current->nr_dirtied);
		*p -= nr_pages_dirtied;
		current->nr_dirtied += nr_pages_dirtied;
	पूर्ण
	preempt_enable();

	अगर (unlikely(current->nr_dirtied >= ratelimit))
		balance_dirty_pages(wb, current->nr_dirtied);

	wb_put(wb);
पूर्ण
EXPORT_SYMBOL(balance_dirty_pages_ratelimited);

/**
 * wb_over_bg_thresh - करोes @wb need to be written back?
 * @wb: bdi_ग_लिखोback of पूर्णांकerest
 *
 * Determines whether background ग_लिखोback should keep writing @wb or it's
 * clean enough.
 *
 * Return: %true अगर ग_लिखोback should जारी.
 */
bool wb_over_bg_thresh(काष्ठा bdi_ग_लिखोback *wb)
अणु
	काष्ठा dirty_throttle_control gdtc_stor = अणु GDTC_INIT(wb) पूर्ण;
	काष्ठा dirty_throttle_control mdtc_stor = अणु MDTC_INIT(wb, &gdtc_stor) पूर्ण;
	काष्ठा dirty_throttle_control * स्थिर gdtc = &gdtc_stor;
	काष्ठा dirty_throttle_control * स्थिर mdtc = mdtc_valid(&mdtc_stor) ?
						     &mdtc_stor : शून्य;

	/*
	 * Similar to balance_dirty_pages() but ignores pages being written
	 * as we're trying to decide whether to put more under ग_लिखोback.
	 */
	gdtc->avail = global_dirtyable_memory();
	gdtc->dirty = global_node_page_state(NR_खाता_सूचीTY);
	करोमुख्य_dirty_limits(gdtc);

	अगर (gdtc->dirty > gdtc->bg_thresh)
		वापस true;

	अगर (wb_stat(wb, WB_RECLAIMABLE) >
	    wb_calc_thresh(gdtc->wb, gdtc->bg_thresh))
		वापस true;

	अगर (mdtc) अणु
		अचिन्हित दीर्घ filepages, headroom, ग_लिखोback;

		mem_cgroup_wb_stats(wb, &filepages, &headroom, &mdtc->dirty,
				    &ग_लिखोback);
		mdtc_calc_avail(mdtc, filepages, headroom);
		करोमुख्य_dirty_limits(mdtc);	/* ditto, ignore ग_लिखोback */

		अगर (mdtc->dirty > mdtc->bg_thresh)
			वापस true;

		अगर (wb_stat(wb, WB_RECLAIMABLE) >
		    wb_calc_thresh(mdtc->wb, mdtc->bg_thresh))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * sysctl handler क्रम /proc/sys/vm/dirty_ग_लिखोback_centisecs
 */
पूर्णांक dirty_ग_लिखोback_centisecs_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *length, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक old_पूर्णांकerval = dirty_ग_लिखोback_पूर्णांकerval;
	पूर्णांक ret;

	ret = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, length, ppos);

	/*
	 * Writing 0 to dirty_ग_लिखोback_पूर्णांकerval will disable periodic ग_लिखोback
	 * and a dअगरferent non-zero value will wakeup the ग_लिखोback thपढ़ोs.
	 * wb_wakeup_delayed() would be more appropriate, but it's a pain to
	 * iterate over all bdis and wbs.
	 * The reason we करो this is to make the change take effect immediately.
	 */
	अगर (!ret && ग_लिखो && dirty_ग_लिखोback_पूर्णांकerval &&
		dirty_ग_लिखोback_पूर्णांकerval != old_पूर्णांकerval)
		wakeup_flusher_thपढ़ोs(WB_REASON_PERIODIC);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_BLOCK
व्योम laptop_mode_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा backing_dev_info *backing_dev_info =
		from_समयr(backing_dev_info, t, laptop_mode_wb_समयr);

	wakeup_flusher_thपढ़ोs_bdi(backing_dev_info, WB_REASON_LAPTOP_TIMER);
पूर्ण

/*
 * We've spun up the disk and we're in laptop mode: schedule ग_लिखोback
 * of all dirty data a few seconds from now.  If the flush is alपढ़ोy scheduled
 * then push it back - the user is still using the disk.
 */
व्योम laptop_io_completion(काष्ठा backing_dev_info *info)
अणु
	mod_समयr(&info->laptop_mode_wb_समयr, jअगरfies + laptop_mode);
पूर्ण

/*
 * We're in laptop mode and we've just synced. The sync's ग_लिखोs will have
 * caused another ग_लिखोback to be scheduled by laptop_io_completion.
 * Nothing needs to be written back anymore, so we unschedule the ग_लिखोback.
 */
व्योम laptop_sync_completion(व्योम)
अणु
	काष्ठा backing_dev_info *bdi;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(bdi, &bdi_list, bdi_list)
		del_समयr(&bdi->laptop_mode_wb_समयr);

	rcu_पढ़ो_unlock();
पूर्ण
#पूर्ण_अगर

/*
 * If ratelimit_pages is too high then we can get पूर्णांकo dirty-data overload
 * अगर a large number of processes all perक्रमm ग_लिखोs at the same समय.
 * If it is too low then SMP machines will call the (expensive)
 * get_ग_लिखोback_state too often.
 *
 * Here we set ratelimit_pages to a level which ensures that when all CPUs are
 * dirtying in parallel, we cannot go more than 3% (1/32) over the dirty memory
 * thresholds.
 */

व्योम ग_लिखोback_set_ratelimit(व्योम)
अणु
	काष्ठा wb_करोमुख्य *करोm = &global_wb_करोमुख्य;
	अचिन्हित दीर्घ background_thresh;
	अचिन्हित दीर्घ dirty_thresh;

	global_dirty_limits(&background_thresh, &dirty_thresh);
	करोm->dirty_limit = dirty_thresh;
	ratelimit_pages = dirty_thresh / (num_online_cpus() * 32);
	अगर (ratelimit_pages < 16)
		ratelimit_pages = 16;
पूर्ण

अटल पूर्णांक page_ग_लिखोback_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	ग_लिखोback_set_ratelimit();
	वापस 0;
पूर्ण

/*
 * Called early on to tune the page ग_लिखोback dirty limits.
 *
 * We used to scale dirty pages according to how total memory
 * related to pages that could be allocated क्रम buffers.
 *
 * However, that was when we used "dirty_ratio" to scale with
 * all memory, and we करोn't करो that any more. "dirty_ratio"
 * is now applied to total non-HIGHPAGE memory, and as such we can't
 * get पूर्णांकo the old insane situation any more where we had
 * large amounts of dirty pages compared to a small amount of
 * non-HIGHMEM memory.
 *
 * But we might still want to scale the dirty_ratio by how
 * much memory the box has..
 */
व्योम __init page_ग_लिखोback_init(व्योम)
अणु
	BUG_ON(wb_करोमुख्य_init(&global_wb_करोमुख्य, GFP_KERNEL));

	cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "mm/writeback:online",
			  page_ग_लिखोback_cpu_online, शून्य);
	cpuhp_setup_state(CPUHP_MM_WRITEBACK_DEAD, "mm/writeback:dead", शून्य,
			  page_ग_लिखोback_cpu_online);
पूर्ण

/**
 * tag_pages_क्रम_ग_लिखोback - tag pages to be written by ग_लिखो_cache_pages
 * @mapping: address space काष्ठाure to ग_लिखो
 * @start: starting page index
 * @end: ending page index (inclusive)
 *
 * This function scans the page range from @start to @end (inclusive) and tags
 * all pages that have सूचीTY tag set with a special TOWRITE tag. The idea is
 * that ग_लिखो_cache_pages (or whoever calls this function) will then use
 * TOWRITE tag to identअगरy pages eligible क्रम ग_लिखोback.  This mechanism is
 * used to aव्योम livelocking of ग_लिखोback by a process steadily creating new
 * dirty pages in the file (thus it is important क्रम this function to be quick
 * so that it can tag pages faster than a dirtying process can create them).
 */
व्योम tag_pages_क्रम_ग_लिखोback(काष्ठा address_space *mapping,
			     pgoff_t start, pgoff_t end)
अणु
	XA_STATE(xas, &mapping->i_pages, start);
	अचिन्हित पूर्णांक tagged = 0;
	व्योम *page;

	xas_lock_irq(&xas);
	xas_क्रम_each_marked(&xas, page, end, PAGECACHE_TAG_सूचीTY) अणु
		xas_set_mark(&xas, PAGECACHE_TAG_TOWRITE);
		अगर (++tagged % XA_CHECK_SCHED)
			जारी;

		xas_छोड़ो(&xas);
		xas_unlock_irq(&xas);
		cond_resched();
		xas_lock_irq(&xas);
	पूर्ण
	xas_unlock_irq(&xas);
पूर्ण
EXPORT_SYMBOL(tag_pages_क्रम_ग_लिखोback);

/**
 * ग_लिखो_cache_pages - walk the list of dirty pages of the given address space and ग_लिखो all of them.
 * @mapping: address space काष्ठाure to ग_लिखो
 * @wbc: subtract the number of written pages from *@wbc->nr_to_ग_लिखो
 * @ग_लिखोpage: function called क्रम each page
 * @data: data passed to ग_लिखोpage function
 *
 * If a page is alपढ़ोy under I/O, ग_लिखो_cache_pages() skips it, even
 * अगर it's dirty.  This is desirable behaviour क्रम memory-cleaning ग_लिखोback,
 * but it is INCORRECT क्रम data-पूर्णांकegrity प्रणाली calls such as fsync().  fsync()
 * and msync() need to guarantee that all the data which was dirty at the समय
 * the call was made get new I/O started against them.  If wbc->sync_mode is
 * WB_SYNC_ALL then we were called क्रम data पूर्णांकegrity and we must रुको क्रम
 * existing IO to complete.
 *
 * To aव्योम livelocks (when other process dirties new pages), we first tag
 * pages which should be written back with TOWRITE tag and only then start
 * writing them. For data-पूर्णांकegrity sync we have to be careful so that we करो
 * not miss some pages (e.g., because some other process has cleared TOWRITE
 * tag we set). The rule we follow is that TOWRITE tag can be cleared only
 * by the process clearing the सूचीTY tag (and submitting the page क्रम IO).
 *
 * To aव्योम deadlocks between range_cyclic ग_लिखोback and callers that hold
 * pages in PageWriteback to aggregate IO until ग_लिखो_cache_pages() वापसs,
 * we करो not loop back to the start of the file. Doing so causes a page
 * lock/page ग_लिखोback access order inversion - we should only ever lock
 * multiple pages in ascending page->index order, and looping back to the start
 * of the file violates that rule and causes deadlocks.
 *
 * Return: %0 on success, negative error code otherwise
 */
पूर्णांक ग_लिखो_cache_pages(काष्ठा address_space *mapping,
		      काष्ठा ग_लिखोback_control *wbc, ग_लिखोpage_t ग_लिखोpage,
		      व्योम *data)
अणु
	पूर्णांक ret = 0;
	पूर्णांक करोne = 0;
	पूर्णांक error;
	काष्ठा pagevec pvec;
	पूर्णांक nr_pages;
	pgoff_t index;
	pgoff_t end;		/* Inclusive */
	pgoff_t करोne_index;
	पूर्णांक range_whole = 0;
	xa_mark_t tag;

	pagevec_init(&pvec);
	अगर (wbc->range_cyclic) अणु
		index = mapping->ग_लिखोback_index; /* prev offset */
		end = -1;
	पूर्ण अन्यथा अणु
		index = wbc->range_start >> PAGE_SHIFT;
		end = wbc->range_end >> PAGE_SHIFT;
		अगर (wbc->range_start == 0 && wbc->range_end == Lदीर्घ_उच्च)
			range_whole = 1;
	पूर्ण
	अगर (wbc->sync_mode == WB_SYNC_ALL || wbc->tagged_ग_लिखोpages) अणु
		tag_pages_क्रम_ग_लिखोback(mapping, index, end);
		tag = PAGECACHE_TAG_TOWRITE;
	पूर्ण अन्यथा अणु
		tag = PAGECACHE_TAG_सूचीTY;
	पूर्ण
	करोne_index = index;
	जबतक (!करोne && (index <= end)) अणु
		पूर्णांक i;

		nr_pages = pagevec_lookup_range_tag(&pvec, mapping, &index, end,
				tag);
		अगर (nr_pages == 0)
			अवरोध;

		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];

			करोne_index = page->index;

			lock_page(page);

			/*
			 * Page truncated or invalidated. We can मुक्तly skip it
			 * then, even क्रम data पूर्णांकegrity operations: the page
			 * has disappeared concurrently, so there could be no
			 * real expectation of this data पूर्णांकegrity operation
			 * even अगर there is now a new, dirty page at the same
			 * pagecache address.
			 */
			अगर (unlikely(page->mapping != mapping)) अणु
जारी_unlock:
				unlock_page(page);
				जारी;
			पूर्ण

			अगर (!PageDirty(page)) अणु
				/* someone wrote it क्रम us */
				जाओ जारी_unlock;
			पूर्ण

			अगर (PageWriteback(page)) अणु
				अगर (wbc->sync_mode != WB_SYNC_NONE)
					रुको_on_page_ग_लिखोback(page);
				अन्यथा
					जाओ जारी_unlock;
			पूर्ण

			BUG_ON(PageWriteback(page));
			अगर (!clear_page_dirty_क्रम_io(page))
				जाओ जारी_unlock;

			trace_wbc_ग_लिखोpage(wbc, inode_to_bdi(mapping->host));
			error = (*ग_लिखोpage)(page, wbc, data);
			अगर (unlikely(error)) अणु
				/*
				 * Handle errors according to the type of
				 * ग_लिखोback. There's no need to जारी क्रम
				 * background ग_लिखोback. Just push करोne_index
				 * past this page so media errors won't choke
				 * ग_लिखोout क्रम the entire file. For पूर्णांकegrity
				 * ग_लिखोback, we must process the entire dirty
				 * set regardless of errors because the fs may
				 * still have state to clear क्रम each page. In
				 * that हाल we जारी processing and वापस
				 * the first error.
				 */
				अगर (error == AOP_WRITEPAGE_ACTIVATE) अणु
					unlock_page(page);
					error = 0;
				पूर्ण अन्यथा अगर (wbc->sync_mode != WB_SYNC_ALL) अणु
					ret = error;
					करोne_index = page->index + 1;
					करोne = 1;
					अवरोध;
				पूर्ण
				अगर (!ret)
					ret = error;
			पूर्ण

			/*
			 * We stop writing back only अगर we are not करोing
			 * पूर्णांकegrity sync. In हाल of पूर्णांकegrity sync we have to
			 * keep going until we have written all the pages
			 * we tagged क्रम ग_लिखोback prior to entering this loop.
			 */
			अगर (--wbc->nr_to_ग_लिखो <= 0 &&
			    wbc->sync_mode == WB_SYNC_NONE) अणु
				करोne = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण

	/*
	 * If we hit the last page and there is more work to be करोne: wrap
	 * back the index back to the start of the file क्रम the next
	 * समय we are called.
	 */
	अगर (wbc->range_cyclic && !करोne)
		करोne_index = 0;
	अगर (wbc->range_cyclic || (range_whole && wbc->nr_to_ग_लिखो > 0))
		mapping->ग_लिखोback_index = करोne_index;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ग_लिखो_cache_pages);

/*
 * Function used by generic_ग_लिखोpages to call the real ग_लिखोpage
 * function and set the mapping flags on error
 */
अटल पूर्णांक __ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc,
		       व्योम *data)
अणु
	काष्ठा address_space *mapping = data;
	पूर्णांक ret = mapping->a_ops->ग_लिखोpage(page, wbc);
	mapping_set_error(mapping, ret);
	वापस ret;
पूर्ण

/**
 * generic_ग_लिखोpages - walk the list of dirty pages of the given address space and ग_लिखोpage() all of them.
 * @mapping: address space काष्ठाure to ग_लिखो
 * @wbc: subtract the number of written pages from *@wbc->nr_to_ग_लिखो
 *
 * This is a library function, which implements the ग_लिखोpages()
 * address_space_operation.
 *
 * Return: %0 on success, negative error code otherwise
 */
पूर्णांक generic_ग_लिखोpages(काष्ठा address_space *mapping,
		       काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा blk_plug plug;
	पूर्णांक ret;

	/* deal with अक्षरdevs and other special file */
	अगर (!mapping->a_ops->ग_लिखोpage)
		वापस 0;

	blk_start_plug(&plug);
	ret = ग_लिखो_cache_pages(mapping, wbc, __ग_लिखोpage, mapping);
	blk_finish_plug(&plug);
	वापस ret;
पूर्ण

EXPORT_SYMBOL(generic_ग_लिखोpages);

पूर्णांक करो_ग_लिखोpages(काष्ठा address_space *mapping, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret;

	अगर (wbc->nr_to_ग_लिखो <= 0)
		वापस 0;
	जबतक (1) अणु
		अगर (mapping->a_ops->ग_लिखोpages)
			ret = mapping->a_ops->ग_लिखोpages(mapping, wbc);
		अन्यथा
			ret = generic_ग_लिखोpages(mapping, wbc);
		अगर ((ret != -ENOMEM) || (wbc->sync_mode != WB_SYNC_ALL))
			अवरोध;
		cond_resched();
		congestion_रुको(BLK_RW_ASYNC, HZ/50);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * ग_लिखो_one_page - ग_लिखो out a single page and रुको on I/O
 * @page: the page to ग_लिखो
 *
 * The page must be locked by the caller and will be unlocked upon वापस.
 *
 * Note that the mapping's AS_EIO/AS_ENOSPC flags will be cleared when this
 * function वापसs.
 *
 * Return: %0 on success, negative error code otherwise
 */
पूर्णांक ग_लिखो_one_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page->mapping;
	पूर्णांक ret = 0;
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = WB_SYNC_ALL,
		.nr_to_ग_लिखो = 1,
	पूर्ण;

	BUG_ON(!PageLocked(page));

	रुको_on_page_ग_लिखोback(page);

	अगर (clear_page_dirty_क्रम_io(page)) अणु
		get_page(page);
		ret = mapping->a_ops->ग_लिखोpage(page, &wbc);
		अगर (ret == 0)
			रुको_on_page_ग_लिखोback(page);
		put_page(page);
	पूर्ण अन्यथा अणु
		unlock_page(page);
	पूर्ण

	अगर (!ret)
		ret = filemap_check_errors(mapping);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ग_लिखो_one_page);

/*
 * For address_spaces which करो not use buffers nor ग_लिखो back.
 */
पूर्णांक __set_page_dirty_no_ग_लिखोback(काष्ठा page *page)
अणु
	अगर (!PageDirty(page))
		वापस !TestSetPageDirty(page);
	वापस 0;
पूर्ण

/*
 * Helper function क्रम set_page_dirty family.
 *
 * Caller must hold lock_page_memcg().
 *
 * NOTE: This relies on being atomic wrt पूर्णांकerrupts.
 */
व्योम account_page_dirtied(काष्ठा page *page, काष्ठा address_space *mapping)
अणु
	काष्ठा inode *inode = mapping->host;

	trace_ग_लिखोback_dirty_page(page, mapping);

	अगर (mapping_can_ग_लिखोback(mapping)) अणु
		काष्ठा bdi_ग_लिखोback *wb;

		inode_attach_wb(inode, page);
		wb = inode_to_wb(inode);

		__inc_lruvec_page_state(page, NR_खाता_सूचीTY);
		__inc_zone_page_state(page, NR_ZONE_WRITE_PENDING);
		__inc_node_page_state(page, NR_सूचीTIED);
		inc_wb_stat(wb, WB_RECLAIMABLE);
		inc_wb_stat(wb, WB_सूचीTIED);
		task_io_account_ग_लिखो(PAGE_SIZE);
		current->nr_dirtied++;
		this_cpu_inc(bdp_ratelimits);

		mem_cgroup_track_क्रमeign_dirty(page, wb);
	पूर्ण
पूर्ण

/*
 * Helper function क्रम deaccounting dirty page without ग_लिखोback.
 *
 * Caller must hold lock_page_memcg().
 */
व्योम account_page_cleaned(काष्ठा page *page, काष्ठा address_space *mapping,
			  काष्ठा bdi_ग_लिखोback *wb)
अणु
	अगर (mapping_can_ग_लिखोback(mapping)) अणु
		dec_lruvec_page_state(page, NR_खाता_सूचीTY);
		dec_zone_page_state(page, NR_ZONE_WRITE_PENDING);
		dec_wb_stat(wb, WB_RECLAIMABLE);
		task_io_account_cancelled_ग_लिखो(PAGE_SIZE);
	पूर्ण
पूर्ण

/*
 * For address_spaces which करो not use buffers.  Just tag the page as dirty in
 * the xarray.
 *
 * This is also used when a single buffer is being dirtied: we want to set the
 * page dirty in that हाल, but not all the buffers.  This is a "bottom-up"
 * dirtying, whereas __set_page_dirty_buffers() is a "top-down" dirtying.
 *
 * The caller must ensure this करोesn't race with truncation.  Most will simply
 * hold the page lock, but e.g. zap_pte_range() calls with the page mapped and
 * the pte lock held, which also locks out truncation.
 */
पूर्णांक __set_page_dirty_nobuffers(काष्ठा page *page)
अणु
	lock_page_memcg(page);
	अगर (!TestSetPageDirty(page)) अणु
		काष्ठा address_space *mapping = page_mapping(page);
		अचिन्हित दीर्घ flags;

		अगर (!mapping) अणु
			unlock_page_memcg(page);
			वापस 1;
		पूर्ण

		xa_lock_irqsave(&mapping->i_pages, flags);
		BUG_ON(page_mapping(page) != mapping);
		WARN_ON_ONCE(!PagePrivate(page) && !PageUptodate(page));
		account_page_dirtied(page, mapping);
		__xa_set_mark(&mapping->i_pages, page_index(page),
				   PAGECACHE_TAG_सूचीTY);
		xa_unlock_irqrestore(&mapping->i_pages, flags);
		unlock_page_memcg(page);

		अगर (mapping->host) अणु
			/* !PageAnon && !swapper_space */
			__mark_inode_dirty(mapping->host, I_सूचीTY_PAGES);
		पूर्ण
		वापस 1;
	पूर्ण
	unlock_page_memcg(page);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__set_page_dirty_nobuffers);

/*
 * Call this whenever redirtying a page, to de-account the dirty counters
 * (NR_सूचीTIED, WB_सूचीTIED, tsk->nr_dirtied), so that they match the written
 * counters (NR_WRITTEN, WB_WRITTEN) in दीर्घ term. The mismatches will lead to
 * प्रणालीatic errors in balanced_dirty_ratelimit and the dirty pages position
 * control.
 */
व्योम account_page_redirty(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page->mapping;

	अगर (mapping && mapping_can_ग_लिखोback(mapping)) अणु
		काष्ठा inode *inode = mapping->host;
		काष्ठा bdi_ग_लिखोback *wb;
		काष्ठा wb_lock_cookie cookie = अणुपूर्ण;

		wb = unlocked_inode_to_wb_begin(inode, &cookie);
		current->nr_dirtied--;
		dec_node_page_state(page, NR_सूचीTIED);
		dec_wb_stat(wb, WB_सूचीTIED);
		unlocked_inode_to_wb_end(inode, &cookie);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(account_page_redirty);

/*
 * When a ग_लिखोpage implementation decides that it करोesn't want to ग_लिखो this
 * page क्रम some reason, it should redirty the locked page via
 * redirty_page_क्रम_ग_लिखोpage() and it should then unlock the page and वापस 0
 */
पूर्णांक redirty_page_क्रम_ग_लिखोpage(काष्ठा ग_लिखोback_control *wbc, काष्ठा page *page)
अणु
	पूर्णांक ret;

	wbc->pages_skipped++;
	ret = __set_page_dirty_nobuffers(page);
	account_page_redirty(page);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(redirty_page_क्रम_ग_लिखोpage);

/*
 * Dirty a page.
 *
 * For pages with a mapping this should be करोne under the page lock
 * क्रम the benefit of asynchronous memory errors who prefer a consistent
 * dirty state. This rule can be broken in some special हालs,
 * but should be better not to.
 *
 * If the mapping करोesn't provide a set_page_dirty a_op, then
 * just fall through and assume that it wants buffer_heads.
 */
पूर्णांक set_page_dirty(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_mapping(page);

	page = compound_head(page);
	अगर (likely(mapping)) अणु
		पूर्णांक (*spd)(काष्ठा page *) = mapping->a_ops->set_page_dirty;
		/*
		 * पढ़ोahead/lru_deactivate_page could reमुख्य
		 * PG_पढ़ोahead/PG_reclaim due to race with end_page_ग_लिखोback
		 * About पढ़ोahead, अगर the page is written, the flags would be
		 * reset. So no problem.
		 * About lru_deactivate_page, अगर the page is redirty, the flag
		 * will be reset. So no problem. but अगर the page is used by पढ़ोahead
		 * it will confuse पढ़ोahead and make it restart the size rampup
		 * process. But it's a trivial problem.
		 */
		अगर (PageReclaim(page))
			ClearPageReclaim(page);
#अगर_घोषित CONFIG_BLOCK
		अगर (!spd)
			spd = __set_page_dirty_buffers;
#पूर्ण_अगर
		वापस (*spd)(page);
	पूर्ण
	अगर (!PageDirty(page)) अणु
		अगर (!TestSetPageDirty(page))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(set_page_dirty);

/*
 * set_page_dirty() is racy अगर the caller has no reference against
 * page->mapping->host, and अगर the page is unlocked.  This is because another
 * CPU could truncate the page off the mapping and then मुक्त the mapping.
 *
 * Usually, the page _is_ locked, or the caller is a user-space process which
 * holds a reference on the inode by having an खोलो file.
 *
 * In other हालs, the page should be locked beक्रमe running set_page_dirty().
 */
पूर्णांक set_page_dirty_lock(काष्ठा page *page)
अणु
	पूर्णांक ret;

	lock_page(page);
	ret = set_page_dirty(page);
	unlock_page(page);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(set_page_dirty_lock);

/*
 * This cancels just the dirty bit on the kernel page itself, it करोes NOT
 * actually हटाओ dirty bits on any mmap's that may be around. It also
 * leaves the page tagged dirty, so any sync activity will still find it on
 * the dirty lists, and in particular, clear_page_dirty_क्रम_io() will still
 * look at the dirty bits in the VM.
 *
 * Doing this should *normally* only ever be करोne when a page is truncated,
 * and is not actually mapped anywhere at all. However, fs/buffer.c करोes
 * this when it notices that somebody has cleaned out all the buffers on a
 * page without actually करोing it through the VM. Can you say "ext3 is
 * horribly ugly"? Thought you could.
 */
व्योम __cancel_dirty_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_mapping(page);

	अगर (mapping_can_ग_लिखोback(mapping)) अणु
		काष्ठा inode *inode = mapping->host;
		काष्ठा bdi_ग_लिखोback *wb;
		काष्ठा wb_lock_cookie cookie = अणुपूर्ण;

		lock_page_memcg(page);
		wb = unlocked_inode_to_wb_begin(inode, &cookie);

		अगर (TestClearPageDirty(page))
			account_page_cleaned(page, mapping, wb);

		unlocked_inode_to_wb_end(inode, &cookie);
		unlock_page_memcg(page);
	पूर्ण अन्यथा अणु
		ClearPageDirty(page);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__cancel_dirty_page);

/*
 * Clear a page's dirty flag, जबतक caring क्रम dirty memory accounting.
 * Returns true अगर the page was previously dirty.
 *
 * This is क्रम preparing to put the page under ग_लिखोout.  We leave the page
 * tagged as dirty in the xarray so that a concurrent ग_लिखो-क्रम-sync
 * can discover it via a PAGECACHE_TAG_सूचीTY walk.  The ->ग_लिखोpage
 * implementation will run either set_page_ग_लिखोback() or set_page_dirty(),
 * at which stage we bring the page's dirty flag and xarray dirty tag
 * back पूर्णांकo sync.
 *
 * This incoherency between the page's dirty flag and xarray tag is
 * unक्रमtunate, but it only exists जबतक the page is locked.
 */
पूर्णांक clear_page_dirty_क्रम_io(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_mapping(page);
	पूर्णांक ret = 0;

	VM_BUG_ON_PAGE(!PageLocked(page), page);

	अगर (mapping && mapping_can_ग_लिखोback(mapping)) अणु
		काष्ठा inode *inode = mapping->host;
		काष्ठा bdi_ग_लिखोback *wb;
		काष्ठा wb_lock_cookie cookie = अणुपूर्ण;

		/*
		 * Yes, Virginia, this is indeed insane.
		 *
		 * We use this sequence to make sure that
		 *  (a) we account क्रम dirty stats properly
		 *  (b) we tell the low-level fileप्रणाली to
		 *      mark the whole page dirty अगर it was
		 *      dirty in a pagetable. Only to then
		 *  (c) clean the page again and वापस 1 to
		 *      cause the ग_लिखोback.
		 *
		 * This way we aव्योम all nasty races with the
		 * dirty bit in multiple places and clearing
		 * them concurrently from dअगरferent thपढ़ोs.
		 *
		 * Note! Normally the "set_page_dirty(page)"
		 * has no effect on the actual dirty bit - since
		 * that will alपढ़ोy usually be set. But we
		 * need the side effects, and it can help us
		 * aव्योम races.
		 *
		 * We basically use the page "master dirty bit"
		 * as a serialization poपूर्णांक क्रम all the dअगरferent
		 * thपढ़ोs करोing their things.
		 */
		अगर (page_mkclean(page))
			set_page_dirty(page);
		/*
		 * We carefully synchronise fault handlers against
		 * installing a dirty pte and marking the page dirty
		 * at this poपूर्णांक.  We करो this by having them hold the
		 * page lock जबतक dirtying the page, and pages are
		 * always locked coming in here, so we get the desired
		 * exclusion.
		 */
		wb = unlocked_inode_to_wb_begin(inode, &cookie);
		अगर (TestClearPageDirty(page)) अणु
			dec_lruvec_page_state(page, NR_खाता_सूचीTY);
			dec_zone_page_state(page, NR_ZONE_WRITE_PENDING);
			dec_wb_stat(wb, WB_RECLAIMABLE);
			ret = 1;
		पूर्ण
		unlocked_inode_to_wb_end(inode, &cookie);
		वापस ret;
	पूर्ण
	वापस TestClearPageDirty(page);
पूर्ण
EXPORT_SYMBOL(clear_page_dirty_क्रम_io);

पूर्णांक test_clear_page_ग_लिखोback(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_mapping(page);
	पूर्णांक ret;

	lock_page_memcg(page);
	अगर (mapping && mapping_use_ग_लिखोback_tags(mapping)) अणु
		काष्ठा inode *inode = mapping->host;
		काष्ठा backing_dev_info *bdi = inode_to_bdi(inode);
		अचिन्हित दीर्घ flags;

		xa_lock_irqsave(&mapping->i_pages, flags);
		ret = TestClearPageWriteback(page);
		अगर (ret) अणु
			__xa_clear_mark(&mapping->i_pages, page_index(page),
						PAGECACHE_TAG_WRITEBACK);
			अगर (bdi->capabilities & BDI_CAP_WRITEBACK_ACCT) अणु
				काष्ठा bdi_ग_लिखोback *wb = inode_to_wb(inode);

				dec_wb_stat(wb, WB_WRITEBACK);
				__wb_ग_लिखोout_inc(wb);
			पूर्ण
		पूर्ण

		अगर (mapping->host && !mapping_tagged(mapping,
						     PAGECACHE_TAG_WRITEBACK))
			sb_clear_inode_ग_लिखोback(mapping->host);

		xa_unlock_irqrestore(&mapping->i_pages, flags);
	पूर्ण अन्यथा अणु
		ret = TestClearPageWriteback(page);
	पूर्ण
	अगर (ret) अणु
		dec_lruvec_page_state(page, NR_WRITEBACK);
		dec_zone_page_state(page, NR_ZONE_WRITE_PENDING);
		inc_node_page_state(page, NR_WRITTEN);
	पूर्ण
	unlock_page_memcg(page);
	वापस ret;
पूर्ण

पूर्णांक __test_set_page_ग_लिखोback(काष्ठा page *page, bool keep_ग_लिखो)
अणु
	काष्ठा address_space *mapping = page_mapping(page);
	पूर्णांक ret, access_ret;

	lock_page_memcg(page);
	अगर (mapping && mapping_use_ग_लिखोback_tags(mapping)) अणु
		XA_STATE(xas, &mapping->i_pages, page_index(page));
		काष्ठा inode *inode = mapping->host;
		काष्ठा backing_dev_info *bdi = inode_to_bdi(inode);
		अचिन्हित दीर्घ flags;

		xas_lock_irqsave(&xas, flags);
		xas_load(&xas);
		ret = TestSetPageWriteback(page);
		अगर (!ret) अणु
			bool on_wblist;

			on_wblist = mapping_tagged(mapping,
						   PAGECACHE_TAG_WRITEBACK);

			xas_set_mark(&xas, PAGECACHE_TAG_WRITEBACK);
			अगर (bdi->capabilities & BDI_CAP_WRITEBACK_ACCT)
				inc_wb_stat(inode_to_wb(inode), WB_WRITEBACK);

			/*
			 * We can come through here when swapping anonymous
			 * pages, so we करोn't necessarily have an inode to track
			 * क्रम sync.
			 */
			अगर (mapping->host && !on_wblist)
				sb_mark_inode_ग_लिखोback(mapping->host);
		पूर्ण
		अगर (!PageDirty(page))
			xas_clear_mark(&xas, PAGECACHE_TAG_सूचीTY);
		अगर (!keep_ग_लिखो)
			xas_clear_mark(&xas, PAGECACHE_TAG_TOWRITE);
		xas_unlock_irqrestore(&xas, flags);
	पूर्ण अन्यथा अणु
		ret = TestSetPageWriteback(page);
	पूर्ण
	अगर (!ret) अणु
		inc_lruvec_page_state(page, NR_WRITEBACK);
		inc_zone_page_state(page, NR_ZONE_WRITE_PENDING);
	पूर्ण
	unlock_page_memcg(page);
	access_ret = arch_make_page_accessible(page);
	/*
	 * If ग_लिखोback has been triggered on a page that cannot be made
	 * accessible, it is too late to recover here.
	 */
	VM_BUG_ON_PAGE(access_ret != 0, page);

	वापस ret;

पूर्ण
EXPORT_SYMBOL(__test_set_page_ग_लिखोback);

/*
 * Wait क्रम a page to complete ग_लिखोback
 */
व्योम रुको_on_page_ग_लिखोback(काष्ठा page *page)
अणु
	जबतक (PageWriteback(page)) अणु
		trace_रुको_on_page_ग_लिखोback(page, page_mapping(page));
		रुको_on_page_bit(page, PG_ग_लिखोback);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(रुको_on_page_ग_लिखोback);

/*
 * Wait क्रम a page to complete ग_लिखोback.  Returns -EINTR अगर we get a
 * fatal संकेत जबतक रुकोing.
 */
पूर्णांक रुको_on_page_ग_लिखोback_समाप्तable(काष्ठा page *page)
अणु
	जबतक (PageWriteback(page)) अणु
		trace_रुको_on_page_ग_लिखोback(page, page_mapping(page));
		अगर (रुको_on_page_bit_समाप्तable(page, PG_ग_लिखोback))
			वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(रुको_on_page_ग_लिखोback_समाप्तable);

/**
 * रुको_क्रम_stable_page() - रुको क्रम ग_लिखोback to finish, अगर necessary.
 * @page:	The page to रुको on.
 *
 * This function determines अगर the given page is related to a backing device
 * that requires page contents to be held stable during ग_लिखोback.  If so, then
 * it will रुको क्रम any pending ग_लिखोback to complete.
 */
व्योम रुको_क्रम_stable_page(काष्ठा page *page)
अणु
	page = thp_head(page);
	अगर (page->mapping->host->i_sb->s_अगरlags & SB_I_STABLE_WRITES)
		रुको_on_page_ग_लिखोback(page);
पूर्ण
EXPORT_SYMBOL_GPL(रुको_क्रम_stable_page);
