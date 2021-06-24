<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook  */
#समावेश <linux/rculist.h>
#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bpf.h>
#समावेश <linux/btf_ids.h>
#समावेश <linux/bpf_local_storage.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/sock_diag.h>
#समावेश <uapi/linux/btf.h>

#घोषणा BPF_LOCAL_STORAGE_CREATE_FLAG_MASK (BPF_F_NO_PREALLOC | BPF_F_CLONE)

अटल काष्ठा bpf_local_storage_map_bucket *
select_bucket(काष्ठा bpf_local_storage_map *smap,
	      काष्ठा bpf_local_storage_elem *selem)
अणु
	वापस &smap->buckets[hash_ptr(selem, smap->bucket_log)];
पूर्ण

अटल पूर्णांक mem_अक्षरge(काष्ठा bpf_local_storage_map *smap, व्योम *owner, u32 size)
अणु
	काष्ठा bpf_map *map = &smap->map;

	अगर (!map->ops->map_local_storage_अक्षरge)
		वापस 0;

	वापस map->ops->map_local_storage_अक्षरge(smap, owner, size);
पूर्ण

अटल व्योम mem_unअक्षरge(काष्ठा bpf_local_storage_map *smap, व्योम *owner,
			 u32 size)
अणु
	काष्ठा bpf_map *map = &smap->map;

	अगर (map->ops->map_local_storage_unअक्षरge)
		map->ops->map_local_storage_unअक्षरge(smap, owner, size);
पूर्ण

अटल काष्ठा bpf_local_storage __rcu **
owner_storage(काष्ठा bpf_local_storage_map *smap, व्योम *owner)
अणु
	काष्ठा bpf_map *map = &smap->map;

	वापस map->ops->map_owner_storage_ptr(owner);
पूर्ण

अटल bool selem_linked_to_storage(स्थिर काष्ठा bpf_local_storage_elem *selem)
अणु
	वापस !hlist_unhashed(&selem->snode);
पूर्ण

अटल bool selem_linked_to_map(स्थिर काष्ठा bpf_local_storage_elem *selem)
अणु
	वापस !hlist_unhashed(&selem->map_node);
पूर्ण

काष्ठा bpf_local_storage_elem *
bpf_selem_alloc(काष्ठा bpf_local_storage_map *smap, व्योम *owner,
		व्योम *value, bool अक्षरge_mem)
अणु
	काष्ठा bpf_local_storage_elem *selem;

	अगर (अक्षरge_mem && mem_अक्षरge(smap, owner, smap->elem_size))
		वापस शून्य;

	selem = bpf_map_kzalloc(&smap->map, smap->elem_size,
				GFP_ATOMIC | __GFP_NOWARN);
	अगर (selem) अणु
		अगर (value)
			स_नकल(SDATA(selem)->data, value, smap->map.value_size);
		वापस selem;
	पूर्ण

	अगर (अक्षरge_mem)
		mem_unअक्षरge(smap, owner, smap->elem_size);

	वापस शून्य;
पूर्ण

/* local_storage->lock must be held and selem->local_storage == local_storage.
 * The caller must ensure selem->smap is still valid to be
 * dereferenced क्रम its smap->elem_size and smap->cache_idx.
 */
bool bpf_selem_unlink_storage_nolock(काष्ठा bpf_local_storage *local_storage,
				     काष्ठा bpf_local_storage_elem *selem,
				     bool unअक्षरge_mem)
अणु
	काष्ठा bpf_local_storage_map *smap;
	bool मुक्त_local_storage;
	व्योम *owner;

	smap = rcu_dereference(SDATA(selem)->smap);
	owner = local_storage->owner;

	/* All unअक्षरging on the owner must be करोne first.
	 * The owner may be मुक्तd once the last selem is unlinked
	 * from local_storage.
	 */
	अगर (unअक्षरge_mem)
		mem_unअक्षरge(smap, owner, smap->elem_size);

	मुक्त_local_storage = hlist_is_singular_node(&selem->snode,
						    &local_storage->list);
	अगर (मुक्त_local_storage) अणु
		mem_unअक्षरge(smap, owner, माप(काष्ठा bpf_local_storage));
		local_storage->owner = शून्य;

		/* After this RCU_INIT, owner may be मुक्तd and cannot be used */
		RCU_INIT_POINTER(*owner_storage(smap, owner), शून्य);

		/* local_storage is not मुक्तd now.  local_storage->lock is
		 * still held and raw_spin_unlock_bh(&local_storage->lock)
		 * will be करोne by the caller.
		 *
		 * Although the unlock will be करोne under
		 * rcu_पढ़ो_lock(),  it is more पूर्णांकutivie to
		 * पढ़ो अगर kमुक्त_rcu(local_storage, rcu) is करोne
		 * after the raw_spin_unlock_bh(&local_storage->lock).
		 *
		 * Hence, a "bool free_local_storage" is वापसed
		 * to the caller which then calls the kमुक्त_rcu()
		 * after unlock.
		 */
	पूर्ण
	hlist_del_init_rcu(&selem->snode);
	अगर (rcu_access_poपूर्णांकer(local_storage->cache[smap->cache_idx]) ==
	    SDATA(selem))
		RCU_INIT_POINTER(local_storage->cache[smap->cache_idx], शून्य);

	kमुक्त_rcu(selem, rcu);

	वापस मुक्त_local_storage;
पूर्ण

अटल व्योम __bpf_selem_unlink_storage(काष्ठा bpf_local_storage_elem *selem)
अणु
	काष्ठा bpf_local_storage *local_storage;
	bool मुक्त_local_storage = false;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!selem_linked_to_storage(selem)))
		/* selem has alपढ़ोy been unlinked from sk */
		वापस;

	local_storage = rcu_dereference(selem->local_storage);
	raw_spin_lock_irqsave(&local_storage->lock, flags);
	अगर (likely(selem_linked_to_storage(selem)))
		मुक्त_local_storage = bpf_selem_unlink_storage_nolock(
			local_storage, selem, true);
	raw_spin_unlock_irqrestore(&local_storage->lock, flags);

	अगर (मुक्त_local_storage)
		kमुक्त_rcu(local_storage, rcu);
पूर्ण

व्योम bpf_selem_link_storage_nolock(काष्ठा bpf_local_storage *local_storage,
				   काष्ठा bpf_local_storage_elem *selem)
अणु
	RCU_INIT_POINTER(selem->local_storage, local_storage);
	hlist_add_head_rcu(&selem->snode, &local_storage->list);
पूर्ण

व्योम bpf_selem_unlink_map(काष्ठा bpf_local_storage_elem *selem)
अणु
	काष्ठा bpf_local_storage_map *smap;
	काष्ठा bpf_local_storage_map_bucket *b;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!selem_linked_to_map(selem)))
		/* selem has alपढ़ोy be unlinked from smap */
		वापस;

	smap = rcu_dereference(SDATA(selem)->smap);
	b = select_bucket(smap, selem);
	raw_spin_lock_irqsave(&b->lock, flags);
	अगर (likely(selem_linked_to_map(selem)))
		hlist_del_init_rcu(&selem->map_node);
	raw_spin_unlock_irqrestore(&b->lock, flags);
पूर्ण

व्योम bpf_selem_link_map(काष्ठा bpf_local_storage_map *smap,
			काष्ठा bpf_local_storage_elem *selem)
अणु
	काष्ठा bpf_local_storage_map_bucket *b = select_bucket(smap, selem);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&b->lock, flags);
	RCU_INIT_POINTER(SDATA(selem)->smap, smap);
	hlist_add_head_rcu(&selem->map_node, &b->list);
	raw_spin_unlock_irqrestore(&b->lock, flags);
पूर्ण

व्योम bpf_selem_unlink(काष्ठा bpf_local_storage_elem *selem)
अणु
	/* Always unlink from map beक्रमe unlinking from local_storage
	 * because selem will be मुक्तd after successfully unlinked from
	 * the local_storage.
	 */
	bpf_selem_unlink_map(selem);
	__bpf_selem_unlink_storage(selem);
पूर्ण

काष्ठा bpf_local_storage_data *
bpf_local_storage_lookup(काष्ठा bpf_local_storage *local_storage,
			 काष्ठा bpf_local_storage_map *smap,
			 bool cacheit_lockit)
अणु
	काष्ठा bpf_local_storage_data *sdata;
	काष्ठा bpf_local_storage_elem *selem;

	/* Fast path (cache hit) */
	sdata = rcu_dereference(local_storage->cache[smap->cache_idx]);
	अगर (sdata && rcu_access_poपूर्णांकer(sdata->smap) == smap)
		वापस sdata;

	/* Slow path (cache miss) */
	hlist_क्रम_each_entry_rcu(selem, &local_storage->list, snode)
		अगर (rcu_access_poपूर्णांकer(SDATA(selem)->smap) == smap)
			अवरोध;

	अगर (!selem)
		वापस शून्य;

	sdata = SDATA(selem);
	अगर (cacheit_lockit) अणु
		अचिन्हित दीर्घ flags;

		/* spinlock is needed to aव्योम racing with the
		 * parallel delete.  Otherwise, publishing an alपढ़ोy
		 * deleted sdata to the cache will become a use-after-मुक्त
		 * problem in the next bpf_local_storage_lookup().
		 */
		raw_spin_lock_irqsave(&local_storage->lock, flags);
		अगर (selem_linked_to_storage(selem))
			rcu_assign_poपूर्णांकer(local_storage->cache[smap->cache_idx],
					   sdata);
		raw_spin_unlock_irqrestore(&local_storage->lock, flags);
	पूर्ण

	वापस sdata;
पूर्ण

अटल पूर्णांक check_flags(स्थिर काष्ठा bpf_local_storage_data *old_sdata,
		       u64 map_flags)
अणु
	अगर (old_sdata && (map_flags & ~BPF_F_LOCK) == BPF_NOEXIST)
		/* elem alपढ़ोy exists */
		वापस -EEXIST;

	अगर (!old_sdata && (map_flags & ~BPF_F_LOCK) == BPF_EXIST)
		/* elem करोesn't exist, cannot update it */
		वापस -ENOENT;

	वापस 0;
पूर्ण

पूर्णांक bpf_local_storage_alloc(व्योम *owner,
			    काष्ठा bpf_local_storage_map *smap,
			    काष्ठा bpf_local_storage_elem *first_selem)
अणु
	काष्ठा bpf_local_storage *prev_storage, *storage;
	काष्ठा bpf_local_storage **owner_storage_ptr;
	पूर्णांक err;

	err = mem_अक्षरge(smap, owner, माप(*storage));
	अगर (err)
		वापस err;

	storage = bpf_map_kzalloc(&smap->map, माप(*storage),
				  GFP_ATOMIC | __GFP_NOWARN);
	अगर (!storage) अणु
		err = -ENOMEM;
		जाओ unअक्षरge;
	पूर्ण

	INIT_HLIST_HEAD(&storage->list);
	raw_spin_lock_init(&storage->lock);
	storage->owner = owner;

	bpf_selem_link_storage_nolock(storage, first_selem);
	bpf_selem_link_map(smap, first_selem);

	owner_storage_ptr =
		(काष्ठा bpf_local_storage **)owner_storage(smap, owner);
	/* Publish storage to the owner.
	 * Instead of using any lock of the kernel object (i.e. owner),
	 * cmpxchg will work with any kernel object regardless what
	 * the running context is, bh, irq...etc.
	 *
	 * From now on, the owner->storage poपूर्णांकer (e.g. sk->sk_bpf_storage)
	 * is रक्षित by the storage->lock.  Hence, when मुक्तing
	 * the owner->storage, the storage->lock must be held beक्रमe
	 * setting owner->storage ptr to शून्य.
	 */
	prev_storage = cmpxchg(owner_storage_ptr, शून्य, storage);
	अगर (unlikely(prev_storage)) अणु
		bpf_selem_unlink_map(first_selem);
		err = -EAGAIN;
		जाओ unअक्षरge;

		/* Note that even first_selem was linked to smap's
		 * bucket->list, first_selem can be मुक्तd immediately
		 * (instead of kमुक्त_rcu) because
		 * bpf_local_storage_map_मुक्त() करोes a
		 * synchronize_rcu() beक्रमe walking the bucket->list.
		 * Hence, no one is accessing selem from the
		 * bucket->list under rcu_पढ़ो_lock().
		 */
	पूर्ण

	वापस 0;

unअक्षरge:
	kमुक्त(storage);
	mem_unअक्षरge(smap, owner, माप(*storage));
	वापस err;
पूर्ण

/* sk cannot be going away because it is linking new elem
 * to sk->sk_bpf_storage. (i.e. sk->sk_refcnt cannot be 0).
 * Otherwise, it will become a leak (and other memory issues
 * during map deकाष्ठाion).
 */
काष्ठा bpf_local_storage_data *
bpf_local_storage_update(व्योम *owner, काष्ठा bpf_local_storage_map *smap,
			 व्योम *value, u64 map_flags)
अणु
	काष्ठा bpf_local_storage_data *old_sdata = शून्य;
	काष्ठा bpf_local_storage_elem *selem;
	काष्ठा bpf_local_storage *local_storage;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	/* BPF_EXIST and BPF_NOEXIST cannot be both set */
	अगर (unlikely((map_flags & ~BPF_F_LOCK) > BPF_EXIST) ||
	    /* BPF_F_LOCK can only be used in a value with spin_lock */
	    unlikely((map_flags & BPF_F_LOCK) &&
		     !map_value_has_spin_lock(&smap->map)))
		वापस ERR_PTR(-EINVAL);

	local_storage = rcu_dereference(*owner_storage(smap, owner));
	अगर (!local_storage || hlist_empty(&local_storage->list)) अणु
		/* Very first elem क्रम the owner */
		err = check_flags(शून्य, map_flags);
		अगर (err)
			वापस ERR_PTR(err);

		selem = bpf_selem_alloc(smap, owner, value, true);
		अगर (!selem)
			वापस ERR_PTR(-ENOMEM);

		err = bpf_local_storage_alloc(owner, smap, selem);
		अगर (err) अणु
			kमुक्त(selem);
			mem_unअक्षरge(smap, owner, smap->elem_size);
			वापस ERR_PTR(err);
		पूर्ण

		वापस SDATA(selem);
	पूर्ण

	अगर ((map_flags & BPF_F_LOCK) && !(map_flags & BPF_NOEXIST)) अणु
		/* Hoping to find an old_sdata to करो अंतरभूत update
		 * such that it can aव्योम taking the local_storage->lock
		 * and changing the lists.
		 */
		old_sdata =
			bpf_local_storage_lookup(local_storage, smap, false);
		err = check_flags(old_sdata, map_flags);
		अगर (err)
			वापस ERR_PTR(err);
		अगर (old_sdata && selem_linked_to_storage(SELEM(old_sdata))) अणु
			copy_map_value_locked(&smap->map, old_sdata->data,
					      value, false);
			वापस old_sdata;
		पूर्ण
	पूर्ण

	raw_spin_lock_irqsave(&local_storage->lock, flags);

	/* Recheck local_storage->list under local_storage->lock */
	अगर (unlikely(hlist_empty(&local_storage->list))) अणु
		/* A parallel del is happening and local_storage is going
		 * away.  It has just been checked beक्रमe, so very
		 * unlikely.  Return instead of retry to keep things
		 * simple.
		 */
		err = -EAGAIN;
		जाओ unlock_err;
	पूर्ण

	old_sdata = bpf_local_storage_lookup(local_storage, smap, false);
	err = check_flags(old_sdata, map_flags);
	अगर (err)
		जाओ unlock_err;

	अगर (old_sdata && (map_flags & BPF_F_LOCK)) अणु
		copy_map_value_locked(&smap->map, old_sdata->data, value,
				      false);
		selem = SELEM(old_sdata);
		जाओ unlock;
	पूर्ण

	/* local_storage->lock is held.  Hence, we are sure
	 * we can unlink and unअक्षरge the old_sdata successfully
	 * later.  Hence, instead of अक्षरging the new selem now
	 * and then unअक्षरge the old selem later (which may cause
	 * a potential but unnecessary अक्षरge failure),  aव्योम taking
	 * a अक्षरge at all here (the "!old_sdata" check) and the
	 * old_sdata will not be unअक्षरged later during
	 * bpf_selem_unlink_storage_nolock().
	 */
	selem = bpf_selem_alloc(smap, owner, value, !old_sdata);
	अगर (!selem) अणु
		err = -ENOMEM;
		जाओ unlock_err;
	पूर्ण

	/* First, link the new selem to the map */
	bpf_selem_link_map(smap, selem);

	/* Second, link (and publish) the new selem to local_storage */
	bpf_selem_link_storage_nolock(local_storage, selem);

	/* Third, हटाओ old selem, SELEM(old_sdata) */
	अगर (old_sdata) अणु
		bpf_selem_unlink_map(SELEM(old_sdata));
		bpf_selem_unlink_storage_nolock(local_storage, SELEM(old_sdata),
						false);
	पूर्ण

unlock:
	raw_spin_unlock_irqrestore(&local_storage->lock, flags);
	वापस SDATA(selem);

unlock_err:
	raw_spin_unlock_irqrestore(&local_storage->lock, flags);
	वापस ERR_PTR(err);
पूर्ण

u16 bpf_local_storage_cache_idx_get(काष्ठा bpf_local_storage_cache *cache)
अणु
	u64 min_usage = U64_MAX;
	u16 i, res = 0;

	spin_lock(&cache->idx_lock);

	क्रम (i = 0; i < BPF_LOCAL_STORAGE_CACHE_SIZE; i++) अणु
		अगर (cache->idx_usage_counts[i] < min_usage) अणु
			min_usage = cache->idx_usage_counts[i];
			res = i;

			/* Found a मुक्त cache_idx */
			अगर (!min_usage)
				अवरोध;
		पूर्ण
	पूर्ण
	cache->idx_usage_counts[res]++;

	spin_unlock(&cache->idx_lock);

	वापस res;
पूर्ण

व्योम bpf_local_storage_cache_idx_मुक्त(काष्ठा bpf_local_storage_cache *cache,
				      u16 idx)
अणु
	spin_lock(&cache->idx_lock);
	cache->idx_usage_counts[idx]--;
	spin_unlock(&cache->idx_lock);
पूर्ण

व्योम bpf_local_storage_map_मुक्त(काष्ठा bpf_local_storage_map *smap,
				पूर्णांक __percpu *busy_counter)
अणु
	काष्ठा bpf_local_storage_elem *selem;
	काष्ठा bpf_local_storage_map_bucket *b;
	अचिन्हित पूर्णांक i;

	/* Note that this map might be concurrently cloned from
	 * bpf_sk_storage_clone. Wait क्रम any existing bpf_sk_storage_clone
	 * RCU पढ़ो section to finish beक्रमe proceeding. New RCU
	 * पढ़ो sections should be prevented via bpf_map_inc_not_zero.
	 */
	synchronize_rcu();

	/* bpf prog and the userspace can no दीर्घer access this map
	 * now.  No new selem (of this map) can be added
	 * to the owner->storage or to the map bucket's list.
	 *
	 * The elem of this map can be cleaned up here
	 * or when the storage is मुक्तd e.g.
	 * by bpf_sk_storage_मुक्त() during __sk_deकाष्ठा().
	 */
	क्रम (i = 0; i < (1U << smap->bucket_log); i++) अणु
		b = &smap->buckets[i];

		rcu_पढ़ो_lock();
		/* No one is adding to b->list now */
		जबतक ((selem = hlist_entry_safe(
				rcu_dereference_raw(hlist_first_rcu(&b->list)),
				काष्ठा bpf_local_storage_elem, map_node))) अणु
			अगर (busy_counter) अणु
				migrate_disable();
				__this_cpu_inc(*busy_counter);
			पूर्ण
			bpf_selem_unlink(selem);
			अगर (busy_counter) अणु
				__this_cpu_dec(*busy_counter);
				migrate_enable();
			पूर्ण
			cond_resched_rcu();
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	/* While मुक्तing the storage we may still need to access the map.
	 *
	 * e.g. when bpf_sk_storage_मुक्त() has unlinked selem from the map
	 * which then made the above जबतक((selem = ...)) loop
	 * निकास immediately.
	 *
	 * However, जबतक मुक्तing the storage one still needs to access the
	 * smap->elem_size to करो the unअक्षरging in
	 * bpf_selem_unlink_storage_nolock().
	 *
	 * Hence, रुको another rcu grace period क्रम the storage to be मुक्तd.
	 */
	synchronize_rcu();

	kvमुक्त(smap->buckets);
	kमुक्त(smap);
पूर्ण

पूर्णांक bpf_local_storage_map_alloc_check(जोड़ bpf_attr *attr)
अणु
	अगर (attr->map_flags & ~BPF_LOCAL_STORAGE_CREATE_FLAG_MASK ||
	    !(attr->map_flags & BPF_F_NO_PREALLOC) ||
	    attr->max_entries ||
	    attr->key_size != माप(पूर्णांक) || !attr->value_size ||
	    /* Enक्रमce BTF क्रम userspace sk dumping */
	    !attr->btf_key_type_id || !attr->btf_value_type_id)
		वापस -EINVAL;

	अगर (!bpf_capable())
		वापस -EPERM;

	अगर (attr->value_size > BPF_LOCAL_STORAGE_MAX_VALUE_SIZE)
		वापस -E2BIG;

	वापस 0;
पूर्ण

काष्ठा bpf_local_storage_map *bpf_local_storage_map_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_local_storage_map *smap;
	अचिन्हित पूर्णांक i;
	u32 nbuckets;

	smap = kzalloc(माप(*smap), GFP_USER | __GFP_NOWARN | __GFP_ACCOUNT);
	अगर (!smap)
		वापस ERR_PTR(-ENOMEM);
	bpf_map_init_from_attr(&smap->map, attr);

	nbuckets = roundup_घात_of_two(num_possible_cpus());
	/* Use at least 2 buckets, select_bucket() is undefined behavior with 1 bucket */
	nbuckets = max_t(u32, 2, nbuckets);
	smap->bucket_log = ilog2(nbuckets);

	smap->buckets = kvसुस्मृति(माप(*smap->buckets), nbuckets,
				 GFP_USER | __GFP_NOWARN | __GFP_ACCOUNT);
	अगर (!smap->buckets) अणु
		kमुक्त(smap);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम (i = 0; i < nbuckets; i++) अणु
		INIT_HLIST_HEAD(&smap->buckets[i].list);
		raw_spin_lock_init(&smap->buckets[i].lock);
	पूर्ण

	smap->elem_size =
		माप(काष्ठा bpf_local_storage_elem) + attr->value_size;

	वापस smap;
पूर्ण

पूर्णांक bpf_local_storage_map_check_btf(स्थिर काष्ठा bpf_map *map,
				    स्थिर काष्ठा btf *btf,
				    स्थिर काष्ठा btf_type *key_type,
				    स्थिर काष्ठा btf_type *value_type)
अणु
	u32 पूर्णांक_data;

	अगर (BTF_INFO_KIND(key_type->info) != BTF_KIND_INT)
		वापस -EINVAL;

	पूर्णांक_data = *(u32 *)(key_type + 1);
	अगर (BTF_INT_BITS(पूर्णांक_data) != 32 || BTF_INT_OFFSET(पूर्णांक_data))
		वापस -EINVAL;

	वापस 0;
पूर्ण
