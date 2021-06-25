<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Manage cache of swap slots to be used क्रम and वापसed from
 * swap.
 *
 * Copyright(c) 2016 Intel Corporation.
 *
 * Author: Tim Chen <tim.c.chen@linux.पूर्णांकel.com>
 *
 * We allocate the swap slots from the global pool and put
 * it पूर्णांकo local per cpu caches.  This has the advantage
 * of no needing to acquire the swap_info lock every समय
 * we need a new slot.
 *
 * There is also opportunity to simply वापस the slot
 * to local caches without needing to acquire swap_info
 * lock.  We करो not reuse the वापसed slots directly but
 * move them back to the global pool in a batch.  This
 * allows the slots to coalesce and reduce fragmentation.
 *
 * The swap entry allocated is marked with SWAP_HAS_CACHE
 * flag in map_count that prevents it from being allocated
 * again from the global pool.
 *
 * The swap slots cache is रक्षित by a mutex instead of
 * a spin lock as when we search क्रम slots with scan_swap_map,
 * we can possibly sleep.
 */

#समावेश <linux/swap_slots.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mm.h>

अटल DEFINE_PER_CPU(काष्ठा swap_slots_cache, swp_slots);
अटल bool	swap_slot_cache_active;
bool	swap_slot_cache_enabled;
अटल bool	swap_slot_cache_initialized;
अटल DEFINE_MUTEX(swap_slots_cache_mutex);
/* Serialize swap slots cache enable/disable operations */
अटल DEFINE_MUTEX(swap_slots_cache_enable_mutex);

अटल व्योम __drain_swap_slots_cache(अचिन्हित पूर्णांक type);
अटल व्योम deactivate_swap_slots_cache(व्योम);
अटल व्योम reactivate_swap_slots_cache(व्योम);

#घोषणा use_swap_slot_cache (swap_slot_cache_active && swap_slot_cache_enabled)
#घोषणा SLOTS_CACHE 0x1
#घोषणा SLOTS_CACHE_RET 0x2

अटल व्योम deactivate_swap_slots_cache(व्योम)
अणु
	mutex_lock(&swap_slots_cache_mutex);
	swap_slot_cache_active = false;
	__drain_swap_slots_cache(SLOTS_CACHE|SLOTS_CACHE_RET);
	mutex_unlock(&swap_slots_cache_mutex);
पूर्ण

अटल व्योम reactivate_swap_slots_cache(व्योम)
अणु
	mutex_lock(&swap_slots_cache_mutex);
	swap_slot_cache_active = true;
	mutex_unlock(&swap_slots_cache_mutex);
पूर्ण

/* Must not be called with cpu hot plug lock */
व्योम disable_swap_slots_cache_lock(व्योम)
अणु
	mutex_lock(&swap_slots_cache_enable_mutex);
	swap_slot_cache_enabled = false;
	अगर (swap_slot_cache_initialized) अणु
		/* serialize with cpu hotplug operations */
		get_online_cpus();
		__drain_swap_slots_cache(SLOTS_CACHE|SLOTS_CACHE_RET);
		put_online_cpus();
	पूर्ण
पूर्ण

अटल व्योम __reenable_swap_slots_cache(व्योम)
अणु
	swap_slot_cache_enabled = has_usable_swap();
पूर्ण

व्योम reenable_swap_slots_cache_unlock(व्योम)
अणु
	__reenable_swap_slots_cache();
	mutex_unlock(&swap_slots_cache_enable_mutex);
पूर्ण

अटल bool check_cache_active(व्योम)
अणु
	दीर्घ pages;

	अगर (!swap_slot_cache_enabled)
		वापस false;

	pages = get_nr_swap_pages();
	अगर (!swap_slot_cache_active) अणु
		अगर (pages > num_online_cpus() *
		    THRESHOLD_ACTIVATE_SWAP_SLOTS_CACHE)
			reactivate_swap_slots_cache();
		जाओ out;
	पूर्ण

	/* अगर global pool of slot caches too low, deactivate cache */
	अगर (pages < num_online_cpus() * THRESHOLD_DEACTIVATE_SWAP_SLOTS_CACHE)
		deactivate_swap_slots_cache();
out:
	वापस swap_slot_cache_active;
पूर्ण

अटल पूर्णांक alloc_swap_slot_cache(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा swap_slots_cache *cache;
	swp_entry_t *slots, *slots_ret;

	/*
	 * Do allocation outside swap_slots_cache_mutex
	 * as kvzalloc could trigger reclaim and get_swap_page,
	 * which can lock swap_slots_cache_mutex.
	 */
	slots = kvसुस्मृति(SWAP_SLOTS_CACHE_SIZE, माप(swp_entry_t),
			 GFP_KERNEL);
	अगर (!slots)
		वापस -ENOMEM;

	slots_ret = kvसुस्मृति(SWAP_SLOTS_CACHE_SIZE, माप(swp_entry_t),
			     GFP_KERNEL);
	अगर (!slots_ret) अणु
		kvमुक्त(slots);
		वापस -ENOMEM;
	पूर्ण

	mutex_lock(&swap_slots_cache_mutex);
	cache = &per_cpu(swp_slots, cpu);
	अगर (cache->slots || cache->slots_ret) अणु
		/* cache alपढ़ोy allocated */
		mutex_unlock(&swap_slots_cache_mutex);

		kvमुक्त(slots);
		kvमुक्त(slots_ret);

		वापस 0;
	पूर्ण

	अगर (!cache->lock_initialized) अणु
		mutex_init(&cache->alloc_lock);
		spin_lock_init(&cache->मुक्त_lock);
		cache->lock_initialized = true;
	पूर्ण
	cache->nr = 0;
	cache->cur = 0;
	cache->n_ret = 0;
	/*
	 * We initialized alloc_lock and मुक्त_lock earlier.  We use
	 * !cache->slots or !cache->slots_ret to know अगर it is safe to acquire
	 * the corresponding lock and use the cache.  Memory barrier below
	 * ensures the assumption.
	 */
	mb();
	cache->slots = slots;
	cache->slots_ret = slots_ret;
	mutex_unlock(&swap_slots_cache_mutex);
	वापस 0;
पूर्ण

अटल व्योम drain_slots_cache_cpu(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक type,
				  bool मुक्त_slots)
अणु
	काष्ठा swap_slots_cache *cache;
	swp_entry_t *slots = शून्य;

	cache = &per_cpu(swp_slots, cpu);
	अगर ((type & SLOTS_CACHE) && cache->slots) अणु
		mutex_lock(&cache->alloc_lock);
		swapcache_मुक्त_entries(cache->slots + cache->cur, cache->nr);
		cache->cur = 0;
		cache->nr = 0;
		अगर (मुक्त_slots && cache->slots) अणु
			kvमुक्त(cache->slots);
			cache->slots = शून्य;
		पूर्ण
		mutex_unlock(&cache->alloc_lock);
	पूर्ण
	अगर ((type & SLOTS_CACHE_RET) && cache->slots_ret) अणु
		spin_lock_irq(&cache->मुक्त_lock);
		swapcache_मुक्त_entries(cache->slots_ret, cache->n_ret);
		cache->n_ret = 0;
		अगर (मुक्त_slots && cache->slots_ret) अणु
			slots = cache->slots_ret;
			cache->slots_ret = शून्य;
		पूर्ण
		spin_unlock_irq(&cache->मुक्त_lock);
		kvमुक्त(slots);
	पूर्ण
पूर्ण

अटल व्योम __drain_swap_slots_cache(अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक cpu;

	/*
	 * This function is called during
	 *	1) swapoff, when we have to make sure no
	 *	   left over slots are in cache when we हटाओ
	 *	   a swap device;
	 *      2) disabling of swap slot cache, when we run low
	 *	   on swap slots when allocating memory and need
	 *	   to वापस swap slots to global pool.
	 *
	 * We cannot acquire cpu hot plug lock here as
	 * this function can be invoked in the cpu
	 * hot plug path:
	 * cpu_up -> lock cpu_hotplug -> cpu hotplug state callback
	 *   -> memory allocation -> direct reclaim -> get_swap_page
	 *   -> drain_swap_slots_cache
	 *
	 * Hence the loop over current online cpu below could miss cpu that
	 * is being brought online but not yet marked as online.
	 * That is okay as we करो not schedule and run anything on a
	 * cpu beक्रमe it has been marked online. Hence, we will not
	 * fill any swap slots in slots cache of such cpu.
	 * There are no slots on such cpu that need to be drained.
	 */
	क्रम_each_online_cpu(cpu)
		drain_slots_cache_cpu(cpu, type, false);
पूर्ण

अटल पूर्णांक मुक्त_slot_cache(अचिन्हित पूर्णांक cpu)
अणु
	mutex_lock(&swap_slots_cache_mutex);
	drain_slots_cache_cpu(cpu, SLOTS_CACHE | SLOTS_CACHE_RET, true);
	mutex_unlock(&swap_slots_cache_mutex);
	वापस 0;
पूर्ण

व्योम enable_swap_slots_cache(व्योम)
अणु
	mutex_lock(&swap_slots_cache_enable_mutex);
	अगर (!swap_slot_cache_initialized) अणु
		पूर्णांक ret;

		ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "swap_slots_cache",
					alloc_swap_slot_cache, मुक्त_slot_cache);
		अगर (WARN_ONCE(ret < 0, "Cache allocation failed (%s), operating "
				       "without swap slots cache.\n", __func__))
			जाओ out_unlock;

		swap_slot_cache_initialized = true;
	पूर्ण

	__reenable_swap_slots_cache();
out_unlock:
	mutex_unlock(&swap_slots_cache_enable_mutex);
पूर्ण

/* called with swap slot cache's alloc lock held */
अटल पूर्णांक refill_swap_slots_cache(काष्ठा swap_slots_cache *cache)
अणु
	अगर (!use_swap_slot_cache || cache->nr)
		वापस 0;

	cache->cur = 0;
	अगर (swap_slot_cache_active)
		cache->nr = get_swap_pages(SWAP_SLOTS_CACHE_SIZE,
					   cache->slots, 1);

	वापस cache->nr;
पूर्ण

पूर्णांक मुक्त_swap_slot(swp_entry_t entry)
अणु
	काष्ठा swap_slots_cache *cache;

	cache = raw_cpu_ptr(&swp_slots);
	अगर (likely(use_swap_slot_cache && cache->slots_ret)) अणु
		spin_lock_irq(&cache->मुक्त_lock);
		/* Swap slots cache may be deactivated beक्रमe acquiring lock */
		अगर (!use_swap_slot_cache || !cache->slots_ret) अणु
			spin_unlock_irq(&cache->मुक्त_lock);
			जाओ direct_मुक्त;
		पूर्ण
		अगर (cache->n_ret >= SWAP_SLOTS_CACHE_SIZE) अणु
			/*
			 * Return slots to global pool.
			 * The current swap_map value is SWAP_HAS_CACHE.
			 * Set it to 0 to indicate it is available क्रम
			 * allocation in global pool
			 */
			swapcache_मुक्त_entries(cache->slots_ret, cache->n_ret);
			cache->n_ret = 0;
		पूर्ण
		cache->slots_ret[cache->n_ret++] = entry;
		spin_unlock_irq(&cache->मुक्त_lock);
	पूर्ण अन्यथा अणु
direct_मुक्त:
		swapcache_मुक्त_entries(&entry, 1);
	पूर्ण

	वापस 0;
पूर्ण

swp_entry_t get_swap_page(काष्ठा page *page)
अणु
	swp_entry_t entry;
	काष्ठा swap_slots_cache *cache;

	entry.val = 0;

	अगर (PageTransHuge(page)) अणु
		अगर (IS_ENABLED(CONFIG_THP_SWAP))
			get_swap_pages(1, &entry, HPAGE_PMD_NR);
		जाओ out;
	पूर्ण

	/*
	 * Preemption is allowed here, because we may sleep
	 * in refill_swap_slots_cache().  But it is safe, because
	 * accesses to the per-CPU data काष्ठाure are रक्षित by the
	 * mutex cache->alloc_lock.
	 *
	 * The alloc path here करोes not touch cache->slots_ret
	 * so cache->मुक्त_lock is not taken.
	 */
	cache = raw_cpu_ptr(&swp_slots);

	अगर (likely(check_cache_active() && cache->slots)) अणु
		mutex_lock(&cache->alloc_lock);
		अगर (cache->slots) अणु
repeat:
			अगर (cache->nr) अणु
				entry = cache->slots[cache->cur];
				cache->slots[cache->cur++].val = 0;
				cache->nr--;
			पूर्ण अन्यथा अगर (refill_swap_slots_cache(cache)) अणु
				जाओ repeat;
			पूर्ण
		पूर्ण
		mutex_unlock(&cache->alloc_lock);
		अगर (entry.val)
			जाओ out;
	पूर्ण

	get_swap_pages(1, &entry, 1);
out:
	अगर (mem_cgroup_try_अक्षरge_swap(page, entry)) अणु
		put_swap_page(page, entry);
		entry.val = 0;
	पूर्ण
	वापस entry;
पूर्ण
