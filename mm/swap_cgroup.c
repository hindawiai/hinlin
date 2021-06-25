<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/swap_cgroup.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>

#समावेश <linux/swapops.h> /* depends on mm.h include */

अटल DEFINE_MUTEX(swap_cgroup_mutex);
काष्ठा swap_cgroup_ctrl अणु
	काष्ठा page **map;
	अचिन्हित दीर्घ length;
	spinlock_t	lock;
पूर्ण;

अटल काष्ठा swap_cgroup_ctrl swap_cgroup_ctrl[MAX_SWAPखाताS];

काष्ठा swap_cgroup अणु
	अचिन्हित लघु		id;
पूर्ण;
#घोषणा SC_PER_PAGE	(PAGE_SIZE/माप(काष्ठा swap_cgroup))

/*
 * SwapCgroup implements "lookup" and "exchange" operations.
 * In typical usage, this swap_cgroup is accessed via memcg's अक्षरge/unअक्षरge
 * against SwapCache. At swap_मुक्त(), this is accessed directly from swap.
 *
 * This means,
 *  - we have no race in "exchange" when we're accessed via SwapCache because
 *    SwapCache(and its swp_entry) is under lock.
 *  - When called via swap_मुक्त(), there is no user of this entry and no race.
 * Then, we करोn't need lock around "exchange".
 *
 * TODO: we can push these buffers out to HIGHMEM.
 */

/*
 * allocate buffer क्रम swap_cgroup.
 */
अटल पूर्णांक swap_cgroup_prepare(पूर्णांक type)
अणु
	काष्ठा page *page;
	काष्ठा swap_cgroup_ctrl *ctrl;
	अचिन्हित दीर्घ idx, max;

	ctrl = &swap_cgroup_ctrl[type];

	क्रम (idx = 0; idx < ctrl->length; idx++) अणु
		page = alloc_page(GFP_KERNEL | __GFP_ZERO);
		अगर (!page)
			जाओ not_enough_page;
		ctrl->map[idx] = page;

		अगर (!(idx % SWAP_CLUSTER_MAX))
			cond_resched();
	पूर्ण
	वापस 0;
not_enough_page:
	max = idx;
	क्रम (idx = 0; idx < max; idx++)
		__मुक्त_page(ctrl->map[idx]);

	वापस -ENOMEM;
पूर्ण

अटल काष्ठा swap_cgroup *__lookup_swap_cgroup(काष्ठा swap_cgroup_ctrl *ctrl,
						pgoff_t offset)
अणु
	काष्ठा page *mappage;
	काष्ठा swap_cgroup *sc;

	mappage = ctrl->map[offset / SC_PER_PAGE];
	sc = page_address(mappage);
	वापस sc + offset % SC_PER_PAGE;
पूर्ण

अटल काष्ठा swap_cgroup *lookup_swap_cgroup(swp_entry_t ent,
					काष्ठा swap_cgroup_ctrl **ctrlp)
अणु
	pgoff_t offset = swp_offset(ent);
	काष्ठा swap_cgroup_ctrl *ctrl;

	ctrl = &swap_cgroup_ctrl[swp_type(ent)];
	अगर (ctrlp)
		*ctrlp = ctrl;
	वापस __lookup_swap_cgroup(ctrl, offset);
पूर्ण

/**
 * swap_cgroup_cmpxchg - cmpxchg mem_cgroup's id क्रम this swp_entry.
 * @ent: swap entry to be cmpxchged
 * @old: old id
 * @new: new id
 *
 * Returns old id at success, 0 at failure.
 * (There is no mem_cgroup using 0 as its id)
 */
अचिन्हित लघु swap_cgroup_cmpxchg(swp_entry_t ent,
					अचिन्हित लघु old, अचिन्हित लघु new)
अणु
	काष्ठा swap_cgroup_ctrl *ctrl;
	काष्ठा swap_cgroup *sc;
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु retval;

	sc = lookup_swap_cgroup(ent, &ctrl);

	spin_lock_irqsave(&ctrl->lock, flags);
	retval = sc->id;
	अगर (retval == old)
		sc->id = new;
	अन्यथा
		retval = 0;
	spin_unlock_irqrestore(&ctrl->lock, flags);
	वापस retval;
पूर्ण

/**
 * swap_cgroup_record - record mem_cgroup क्रम a set of swap entries
 * @ent: the first swap entry to be recorded पूर्णांकo
 * @id: mem_cgroup to be recorded
 * @nr_ents: number of swap entries to be recorded
 *
 * Returns old value at success, 0 at failure.
 * (Of course, old value can be 0.)
 */
अचिन्हित लघु swap_cgroup_record(swp_entry_t ent, अचिन्हित लघु id,
				  अचिन्हित पूर्णांक nr_ents)
अणु
	काष्ठा swap_cgroup_ctrl *ctrl;
	काष्ठा swap_cgroup *sc;
	अचिन्हित लघु old;
	अचिन्हित दीर्घ flags;
	pgoff_t offset = swp_offset(ent);
	pgoff_t end = offset + nr_ents;

	sc = lookup_swap_cgroup(ent, &ctrl);

	spin_lock_irqsave(&ctrl->lock, flags);
	old = sc->id;
	क्रम (;;) अणु
		VM_BUG_ON(sc->id != old);
		sc->id = id;
		offset++;
		अगर (offset == end)
			अवरोध;
		अगर (offset % SC_PER_PAGE)
			sc++;
		अन्यथा
			sc = __lookup_swap_cgroup(ctrl, offset);
	पूर्ण
	spin_unlock_irqrestore(&ctrl->lock, flags);

	वापस old;
पूर्ण

/**
 * lookup_swap_cgroup_id - lookup mem_cgroup id tied to swap entry
 * @ent: swap entry to be looked up.
 *
 * Returns ID of mem_cgroup at success. 0 at failure. (0 is invalid ID)
 */
अचिन्हित लघु lookup_swap_cgroup_id(swp_entry_t ent)
अणु
	वापस lookup_swap_cgroup(ent, शून्य)->id;
पूर्ण

पूर्णांक swap_cgroup_swapon(पूर्णांक type, अचिन्हित दीर्घ max_pages)
अणु
	व्योम *array;
	अचिन्हित दीर्घ array_size;
	अचिन्हित दीर्घ length;
	काष्ठा swap_cgroup_ctrl *ctrl;

	length = DIV_ROUND_UP(max_pages, SC_PER_PAGE);
	array_size = length * माप(व्योम *);

	array = vzalloc(array_size);
	अगर (!array)
		जाओ nomem;

	ctrl = &swap_cgroup_ctrl[type];
	mutex_lock(&swap_cgroup_mutex);
	ctrl->length = length;
	ctrl->map = array;
	spin_lock_init(&ctrl->lock);
	अगर (swap_cgroup_prepare(type)) अणु
		/* memory लघुage */
		ctrl->map = शून्य;
		ctrl->length = 0;
		mutex_unlock(&swap_cgroup_mutex);
		vमुक्त(array);
		जाओ nomem;
	पूर्ण
	mutex_unlock(&swap_cgroup_mutex);

	वापस 0;
nomem:
	pr_info("couldn't allocate enough memory for swap_cgroup\n");
	pr_info("swap_cgroup can be disabled by swapaccount=0 boot option\n");
	वापस -ENOMEM;
पूर्ण

व्योम swap_cgroup_swapoff(पूर्णांक type)
अणु
	काष्ठा page **map;
	अचिन्हित दीर्घ i, length;
	काष्ठा swap_cgroup_ctrl *ctrl;

	mutex_lock(&swap_cgroup_mutex);
	ctrl = &swap_cgroup_ctrl[type];
	map = ctrl->map;
	length = ctrl->length;
	ctrl->map = शून्य;
	ctrl->length = 0;
	mutex_unlock(&swap_cgroup_mutex);

	अगर (map) अणु
		क्रम (i = 0; i < length; i++) अणु
			काष्ठा page *page = map[i];
			अगर (page)
				__मुक्त_page(page);
			अगर (!(i % SWAP_CLUSTER_MAX))
				cond_resched();
		पूर्ण
		vमुक्त(map);
	पूर्ण
पूर्ण
