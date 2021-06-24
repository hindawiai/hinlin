<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux VM pressure
 *
 * Copyright 2012 Linaro Ltd.
 *		  Anton Vorontsov <anton.vorontsov@linaro.org>
 *
 * Based on ideas from Andrew Morton, David Rientjes, KOSAKI Motohiro,
 * Leonid Moiseichuk, Mel Gorman, Minchan Kim and Pekka Enberg.
 */

#समावेश <linux/cgroup.h>
#समावेश <linux/fs.h>
#समावेश <linux/log2.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/vmस्थिति.स>
#समावेश <linux/eventfd.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/vmpressure.h>

/*
 * The winकरोw size (vmpressure_win) is the number of scanned pages beक्रमe
 * we try to analyze scanned/reclaimed ratio. So the winकरोw is used as a
 * rate-limit tunable क्रम the "low" level notअगरication, and also क्रम
 * averaging the ratio क्रम medium/critical levels. Using small winकरोw
 * sizes can cause lot of false positives, but too big winकरोw size will
 * delay the notअगरications.
 *
 * As the vmscan reclaimer logic works with chunks which are multiple of
 * SWAP_CLUSTER_MAX, it makes sense to use it क्रम the winकरोw size as well.
 *
 * TODO: Make the winकरोw size depend on machine size, as we करो क्रम vmstat
 * thresholds. Currently we set it to 512 pages (2MB क्रम 4KB pages).
 */
अटल स्थिर अचिन्हित दीर्घ vmpressure_win = SWAP_CLUSTER_MAX * 16;

/*
 * These thresholds are used when we account memory pressure through
 * scanned/reclaimed ratio. The current values were chosen empirically. In
 * essence, they are percents: the higher the value, the more number
 * unsuccessful reclaims there were.
 */
अटल स्थिर अचिन्हित पूर्णांक vmpressure_level_med = 60;
अटल स्थिर अचिन्हित पूर्णांक vmpressure_level_critical = 95;

/*
 * When there are too little pages left to scan, vmpressure() may miss the
 * critical pressure as number of pages will be less than "window size".
 * However, in that हाल the vmscan priority will उठाओ fast as the
 * reclaimer will try to scan LRUs more deeply.
 *
 * The vmscan logic considers these special priorities:
 *
 * prio == DEF_PRIORITY (12): reclaimer starts with that value
 * prio <= DEF_PRIORITY - 2 : kswapd becomes somewhat overwhelmed
 * prio == 0                : बंद to OOM, kernel scans every page in an lru
 *
 * Any value in this range is acceptable क्रम this tunable (i.e. from 12 to
 * 0). Current value क्रम the vmpressure_level_critical_prio is chosen
 * empirically, but the number, in essence, means that we consider
 * critical level when scanning depth is ~10% of the lru size (vmscan
 * scans 'lru_size >> prio' pages, so it is actually 12.5%, or one
 * eights).
 */
अटल स्थिर अचिन्हित पूर्णांक vmpressure_level_critical_prio = ilog2(100 / 10);

अटल काष्ठा vmpressure *work_to_vmpressure(काष्ठा work_काष्ठा *work)
अणु
	वापस container_of(work, काष्ठा vmpressure, work);
पूर्ण

अटल काष्ठा vmpressure *vmpressure_parent(काष्ठा vmpressure *vmpr)
अणु
	काष्ठा cgroup_subsys_state *css = vmpressure_to_css(vmpr);
	काष्ठा mem_cgroup *memcg = mem_cgroup_from_css(css);

	memcg = parent_mem_cgroup(memcg);
	अगर (!memcg)
		वापस शून्य;
	वापस memcg_to_vmpressure(memcg);
पूर्ण

क्रमागत vmpressure_levels अणु
	VMPRESSURE_LOW = 0,
	VMPRESSURE_MEDIUM,
	VMPRESSURE_CRITICAL,
	VMPRESSURE_NUM_LEVELS,
पूर्ण;

क्रमागत vmpressure_modes अणु
	VMPRESSURE_NO_PASSTHROUGH = 0,
	VMPRESSURE_HIERARCHY,
	VMPRESSURE_LOCAL,
	VMPRESSURE_NUM_MODES,
पूर्ण;

अटल स्थिर अक्षर * स्थिर vmpressure_str_levels[] = अणु
	[VMPRESSURE_LOW] = "low",
	[VMPRESSURE_MEDIUM] = "medium",
	[VMPRESSURE_CRITICAL] = "critical",
पूर्ण;

अटल स्थिर अक्षर * स्थिर vmpressure_str_modes[] = अणु
	[VMPRESSURE_NO_PASSTHROUGH] = "default",
	[VMPRESSURE_HIERARCHY] = "hierarchy",
	[VMPRESSURE_LOCAL] = "local",
पूर्ण;

अटल क्रमागत vmpressure_levels vmpressure_level(अचिन्हित दीर्घ pressure)
अणु
	अगर (pressure >= vmpressure_level_critical)
		वापस VMPRESSURE_CRITICAL;
	अन्यथा अगर (pressure >= vmpressure_level_med)
		वापस VMPRESSURE_MEDIUM;
	वापस VMPRESSURE_LOW;
पूर्ण

अटल क्रमागत vmpressure_levels vmpressure_calc_level(अचिन्हित दीर्घ scanned,
						    अचिन्हित दीर्घ reclaimed)
अणु
	अचिन्हित दीर्घ scale = scanned + reclaimed;
	अचिन्हित दीर्घ pressure = 0;

	/*
	 * reclaimed can be greater than scanned क्रम things such as reclaimed
	 * slab pages. shrink_node() just adds reclaimed pages without a
	 * related increment to scanned pages.
	 */
	अगर (reclaimed >= scanned)
		जाओ out;
	/*
	 * We calculate the ratio (in percents) of how many pages were
	 * scanned vs. reclaimed in a given समय frame (winकरोw). Note that
	 * समय is in VM reclaimer's "ticks", i.e. number of pages
	 * scanned. This makes it possible to set desired reaction समय
	 * and serves as a ratelimit.
	 */
	pressure = scale - (reclaimed * scale / scanned);
	pressure = pressure * 100 / scale;

out:
	pr_debug("%s: %3lu  (s: %lu  r: %lu)\n", __func__, pressure,
		 scanned, reclaimed);

	वापस vmpressure_level(pressure);
पूर्ण

काष्ठा vmpressure_event अणु
	काष्ठा eventfd_ctx *efd;
	क्रमागत vmpressure_levels level;
	क्रमागत vmpressure_modes mode;
	काष्ठा list_head node;
पूर्ण;

अटल bool vmpressure_event(काष्ठा vmpressure *vmpr,
			     स्थिर क्रमागत vmpressure_levels level,
			     bool ancestor, bool संकेतled)
अणु
	काष्ठा vmpressure_event *ev;
	bool ret = false;

	mutex_lock(&vmpr->events_lock);
	list_क्रम_each_entry(ev, &vmpr->events, node) अणु
		अगर (ancestor && ev->mode == VMPRESSURE_LOCAL)
			जारी;
		अगर (संकेतled && ev->mode == VMPRESSURE_NO_PASSTHROUGH)
			जारी;
		अगर (level < ev->level)
			जारी;
		eventfd_संकेत(ev->efd, 1);
		ret = true;
	पूर्ण
	mutex_unlock(&vmpr->events_lock);

	वापस ret;
पूर्ण

अटल व्योम vmpressure_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vmpressure *vmpr = work_to_vmpressure(work);
	अचिन्हित दीर्घ scanned;
	अचिन्हित दीर्घ reclaimed;
	क्रमागत vmpressure_levels level;
	bool ancestor = false;
	bool संकेतled = false;

	spin_lock(&vmpr->sr_lock);
	/*
	 * Several contexts might be calling vmpressure(), so it is
	 * possible that the work was rescheduled again beक्रमe the old
	 * work context cleared the counters. In that हाल we will run
	 * just after the old work वापसs, but then scanned might be zero
	 * here. No need क्रम any locks here since we करोn't care अगर
	 * vmpr->reclaimed is in sync.
	 */
	scanned = vmpr->tree_scanned;
	अगर (!scanned) अणु
		spin_unlock(&vmpr->sr_lock);
		वापस;
	पूर्ण

	reclaimed = vmpr->tree_reclaimed;
	vmpr->tree_scanned = 0;
	vmpr->tree_reclaimed = 0;
	spin_unlock(&vmpr->sr_lock);

	level = vmpressure_calc_level(scanned, reclaimed);

	करो अणु
		अगर (vmpressure_event(vmpr, level, ancestor, संकेतled))
			संकेतled = true;
		ancestor = true;
	पूर्ण जबतक ((vmpr = vmpressure_parent(vmpr)));
पूर्ण

/**
 * vmpressure() - Account memory pressure through scanned/reclaimed ratio
 * @gfp:	reclaimer's gfp mask
 * @memcg:	cgroup memory controller handle
 * @tree:	legacy subtree mode
 * @scanned:	number of pages scanned
 * @reclaimed:	number of pages reclaimed
 *
 * This function should be called from the vmscan reclaim path to account
 * "instantaneous" memory pressure (scanned/reclaimed ratio). The raw
 * pressure index is then further refined and averaged over समय.
 *
 * If @tree is set, vmpressure is in traditional userspace reporting
 * mode: @memcg is considered the pressure root and userspace is
 * notअगरied of the entire subtree's reclaim efficiency.
 *
 * If @tree is not set, reclaim efficiency is recorded क्रम @memcg, and
 * only in-kernel users are notअगरied.
 *
 * This function करोes not वापस any value.
 */
व्योम vmpressure(gfp_t gfp, काष्ठा mem_cgroup *memcg, bool tree,
		अचिन्हित दीर्घ scanned, अचिन्हित दीर्घ reclaimed)
अणु
	काष्ठा vmpressure *vmpr = memcg_to_vmpressure(memcg);

	/*
	 * Here we only want to account pressure that userland is able to
	 * help us with. For example, suppose that DMA zone is under
	 * pressure; अगर we notअगरy userland about that kind of pressure,
	 * then it will be mostly a waste as it will trigger unnecessary
	 * मुक्तing of memory by userland (since userland is more likely to
	 * have HIGHMEM/MOVABLE pages instead of the DMA fallback). That
	 * is why we include only movable, highmem and FS/IO pages.
	 * Indirect reclaim (kswapd) sets sc->gfp_mask to GFP_KERNEL, so
	 * we account it too.
	 */
	अगर (!(gfp & (__GFP_HIGHMEM | __GFP_MOVABLE | __GFP_IO | __GFP_FS)))
		वापस;

	/*
	 * If we got here with no pages scanned, then that is an indicator
	 * that reclaimer was unable to find any shrinkable LRUs at the
	 * current scanning depth. But it करोes not mean that we should
	 * report the critical pressure, yet. If the scanning priority
	 * (scanning depth) goes too high (deep), we will be notअगरied
	 * through vmpressure_prio(). But so far, keep calm.
	 */
	अगर (!scanned)
		वापस;

	अगर (tree) अणु
		spin_lock(&vmpr->sr_lock);
		scanned = vmpr->tree_scanned += scanned;
		vmpr->tree_reclaimed += reclaimed;
		spin_unlock(&vmpr->sr_lock);

		अगर (scanned < vmpressure_win)
			वापस;
		schedule_work(&vmpr->work);
	पूर्ण अन्यथा अणु
		क्रमागत vmpressure_levels level;

		/* For now, no users क्रम root-level efficiency */
		अगर (!memcg || mem_cgroup_is_root(memcg))
			वापस;

		spin_lock(&vmpr->sr_lock);
		scanned = vmpr->scanned += scanned;
		reclaimed = vmpr->reclaimed += reclaimed;
		अगर (scanned < vmpressure_win) अणु
			spin_unlock(&vmpr->sr_lock);
			वापस;
		पूर्ण
		vmpr->scanned = vmpr->reclaimed = 0;
		spin_unlock(&vmpr->sr_lock);

		level = vmpressure_calc_level(scanned, reclaimed);

		अगर (level > VMPRESSURE_LOW) अणु
			/*
			 * Let the socket buffer allocator know that
			 * we are having trouble reclaiming LRU pages.
			 *
			 * For hysteresis keep the pressure state
			 * निश्चितed क्रम a second in which subsequent
			 * pressure events can occur.
			 */
			memcg->socket_pressure = jअगरfies + HZ;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * vmpressure_prio() - Account memory pressure through reclaimer priority level
 * @gfp:	reclaimer's gfp mask
 * @memcg:	cgroup memory controller handle
 * @prio:	reclaimer's priority
 *
 * This function should be called from the reclaim path every समय when
 * the vmscan's reclaiming priority (scanning depth) changes.
 *
 * This function करोes not वापस any value.
 */
व्योम vmpressure_prio(gfp_t gfp, काष्ठा mem_cgroup *memcg, पूर्णांक prio)
अणु
	/*
	 * We only use prio क्रम accounting critical level. For more info
	 * see comment क्रम vmpressure_level_critical_prio variable above.
	 */
	अगर (prio > vmpressure_level_critical_prio)
		वापस;

	/*
	 * OK, the prio is below the threshold, updating vmpressure
	 * inक्रमmation beक्रमe shrinker भागes पूर्णांकo दीर्घ shrinking of दीर्घ
	 * range vmscan. Passing scanned = vmpressure_win, reclaimed = 0
	 * to the vmpressure() basically means that we संकेत 'critical'
	 * level.
	 */
	vmpressure(gfp, memcg, true, vmpressure_win, 0);
पूर्ण

#घोषणा MAX_VMPRESSURE_ARGS_LEN	(म_माप("critical") + म_माप("hierarchy") + 2)

/**
 * vmpressure_रेजिस्टर_event() - Bind vmpressure notअगरications to an eventfd
 * @memcg:	memcg that is पूर्णांकerested in vmpressure notअगरications
 * @eventfd:	eventfd context to link notअगरications with
 * @args:	event arguments (pressure level threshold, optional mode)
 *
 * This function associates eventfd context with the vmpressure
 * infraकाष्ठाure, so that the notअगरications will be delivered to the
 * @eventfd. The @args parameter is a comma-delimited string that denotes a
 * pressure level threshold (one of vmpressure_str_levels, i.e. "low", "medium",
 * or "critical") and an optional mode (one of vmpressure_str_modes, i.e.
 * "hierarchy" or "local").
 *
 * To be used as memcg event method.
 *
 * Return: 0 on success, -ENOMEM on memory failure or -EINVAL अगर @args could
 * not be parsed.
 */
पूर्णांक vmpressure_रेजिस्टर_event(काष्ठा mem_cgroup *memcg,
			      काष्ठा eventfd_ctx *eventfd, स्थिर अक्षर *args)
अणु
	काष्ठा vmpressure *vmpr = memcg_to_vmpressure(memcg);
	काष्ठा vmpressure_event *ev;
	क्रमागत vmpressure_modes mode = VMPRESSURE_NO_PASSTHROUGH;
	क्रमागत vmpressure_levels level;
	अक्षर *spec, *spec_orig;
	अक्षर *token;
	पूर्णांक ret = 0;

	spec_orig = spec = kstrndup(args, MAX_VMPRESSURE_ARGS_LEN, GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	/* Find required level */
	token = strsep(&spec, ",");
	ret = match_string(vmpressure_str_levels, VMPRESSURE_NUM_LEVELS, token);
	अगर (ret < 0)
		जाओ out;
	level = ret;

	/* Find optional mode */
	token = strsep(&spec, ",");
	अगर (token) अणु
		ret = match_string(vmpressure_str_modes, VMPRESSURE_NUM_MODES, token);
		अगर (ret < 0)
			जाओ out;
		mode = ret;
	पूर्ण

	ev = kzalloc(माप(*ev), GFP_KERNEL);
	अगर (!ev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ev->efd = eventfd;
	ev->level = level;
	ev->mode = mode;

	mutex_lock(&vmpr->events_lock);
	list_add(&ev->node, &vmpr->events);
	mutex_unlock(&vmpr->events_lock);
	ret = 0;
out:
	kमुक्त(spec_orig);
	वापस ret;
पूर्ण

/**
 * vmpressure_unरेजिस्टर_event() - Unbind eventfd from vmpressure
 * @memcg:	memcg handle
 * @eventfd:	eventfd context that was used to link vmpressure with the @cg
 *
 * This function करोes पूर्णांकernal manipulations to detach the @eventfd from
 * the vmpressure notअगरications, and then मुक्तs पूर्णांकernal resources
 * associated with the @eventfd (but the @eventfd itself is not मुक्तd).
 *
 * To be used as memcg event method.
 */
व्योम vmpressure_unरेजिस्टर_event(काष्ठा mem_cgroup *memcg,
				 काष्ठा eventfd_ctx *eventfd)
अणु
	काष्ठा vmpressure *vmpr = memcg_to_vmpressure(memcg);
	काष्ठा vmpressure_event *ev;

	mutex_lock(&vmpr->events_lock);
	list_क्रम_each_entry(ev, &vmpr->events, node) अणु
		अगर (ev->efd != eventfd)
			जारी;
		list_del(&ev->node);
		kमुक्त(ev);
		अवरोध;
	पूर्ण
	mutex_unlock(&vmpr->events_lock);
पूर्ण

/**
 * vmpressure_init() - Initialize vmpressure control काष्ठाure
 * @vmpr:	Structure to be initialized
 *
 * This function should be called on every allocated vmpressure काष्ठाure
 * beक्रमe any usage.
 */
व्योम vmpressure_init(काष्ठा vmpressure *vmpr)
अणु
	spin_lock_init(&vmpr->sr_lock);
	mutex_init(&vmpr->events_lock);
	INIT_LIST_HEAD(&vmpr->events);
	INIT_WORK(&vmpr->work, vmpressure_work_fn);
पूर्ण

/**
 * vmpressure_cleanup() - shuts करोwn vmpressure control काष्ठाure
 * @vmpr:	Structure to be cleaned up
 *
 * This function should be called beक्रमe the काष्ठाure in which it is
 * embedded is cleaned up.
 */
व्योम vmpressure_cleanup(काष्ठा vmpressure *vmpr)
अणु
	/*
	 * Make sure there is no pending work beक्रमe eventfd infraकाष्ठाure
	 * goes away.
	 */
	flush_work(&vmpr->work);
पूर्ण
