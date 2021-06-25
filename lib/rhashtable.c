<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Resizable, Scalable, Concurrent Hash Table
 *
 * Copyright (c) 2015 Herbert Xu <herbert@gonकरोr.apana.org.au>
 * Copyright (c) 2014-2015 Thomas Graf <tgraf@suug.ch>
 * Copyright (c) 2008-2014 Patrick McHardy <kaber@trash.net>
 *
 * Code partially derived from nft_hash
 * Rewritten with rehash code from br_multicast plus single list
 * poपूर्णांकer as suggested by Josh Triplett
 */

#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/log2.h>
#समावेश <linux/sched.h>
#समावेश <linux/rculist.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/jhash.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>

#घोषणा HASH_DEFAULT_SIZE	64UL
#घोषणा HASH_MIN_SIZE		4U

जोड़ nested_table अणु
	जोड़ nested_table __rcu *table;
	काष्ठा rhash_lock_head __rcu *bucket;
पूर्ण;

अटल u32 head_hashfn(काष्ठा rhashtable *ht,
		       स्थिर काष्ठा bucket_table *tbl,
		       स्थिर काष्ठा rhash_head *he)
अणु
	वापस rht_head_hashfn(ht, tbl, he, ht->p);
पूर्ण

#अगर_घोषित CONFIG_PROVE_LOCKING
#घोषणा ASSERT_RHT_MUTEX(HT) BUG_ON(!lockdep_rht_mutex_is_held(HT))

पूर्णांक lockdep_rht_mutex_is_held(काष्ठा rhashtable *ht)
अणु
	वापस (debug_locks) ? lockdep_is_held(&ht->mutex) : 1;
पूर्ण
EXPORT_SYMBOL_GPL(lockdep_rht_mutex_is_held);

पूर्णांक lockdep_rht_bucket_is_held(स्थिर काष्ठा bucket_table *tbl, u32 hash)
अणु
	अगर (!debug_locks)
		वापस 1;
	अगर (unlikely(tbl->nest))
		वापस 1;
	वापस bit_spin_is_locked(0, (अचिन्हित दीर्घ *)&tbl->buckets[hash]);
पूर्ण
EXPORT_SYMBOL_GPL(lockdep_rht_bucket_is_held);
#अन्यथा
#घोषणा ASSERT_RHT_MUTEX(HT)
#पूर्ण_अगर

अटल अंतरभूत जोड़ nested_table *nested_table_top(
	स्थिर काष्ठा bucket_table *tbl)
अणु
	/* The top-level bucket entry करोes not need RCU protection
	 * because it's set at the same समय as tbl->nest.
	 */
	वापस (व्योम *)rcu_dereference_रक्षित(tbl->buckets[0], 1);
पूर्ण

अटल व्योम nested_table_मुक्त(जोड़ nested_table *ntbl, अचिन्हित पूर्णांक size)
अणु
	स्थिर अचिन्हित पूर्णांक shअगरt = PAGE_SHIFT - ilog2(माप(व्योम *));
	स्थिर अचिन्हित पूर्णांक len = 1 << shअगरt;
	अचिन्हित पूर्णांक i;

	ntbl = rcu_dereference_रक्षित(ntbl->table, 1);
	अगर (!ntbl)
		वापस;

	अगर (size > len) अणु
		size >>= shअगरt;
		क्रम (i = 0; i < len; i++)
			nested_table_मुक्त(ntbl + i, size);
	पूर्ण

	kमुक्त(ntbl);
पूर्ण

अटल व्योम nested_bucket_table_मुक्त(स्थिर काष्ठा bucket_table *tbl)
अणु
	अचिन्हित पूर्णांक size = tbl->size >> tbl->nest;
	अचिन्हित पूर्णांक len = 1 << tbl->nest;
	जोड़ nested_table *ntbl;
	अचिन्हित पूर्णांक i;

	ntbl = nested_table_top(tbl);

	क्रम (i = 0; i < len; i++)
		nested_table_मुक्त(ntbl + i, size);

	kमुक्त(ntbl);
पूर्ण

अटल व्योम bucket_table_मुक्त(स्थिर काष्ठा bucket_table *tbl)
अणु
	अगर (tbl->nest)
		nested_bucket_table_मुक्त(tbl);

	kvमुक्त(tbl);
पूर्ण

अटल व्योम bucket_table_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	bucket_table_मुक्त(container_of(head, काष्ठा bucket_table, rcu));
पूर्ण

अटल जोड़ nested_table *nested_table_alloc(काष्ठा rhashtable *ht,
					      जोड़ nested_table __rcu **prev,
					      bool leaf)
अणु
	जोड़ nested_table *ntbl;
	पूर्णांक i;

	ntbl = rcu_dereference(*prev);
	अगर (ntbl)
		वापस ntbl;

	ntbl = kzalloc(PAGE_SIZE, GFP_ATOMIC);

	अगर (ntbl && leaf) अणु
		क्रम (i = 0; i < PAGE_SIZE / माप(ntbl[0]); i++)
			INIT_RHT_शून्यS_HEAD(ntbl[i].bucket);
	पूर्ण

	अगर (cmpxchg((जोड़ nested_table **)prev, शून्य, ntbl) == शून्य)
		वापस ntbl;
	/* Raced with another thपढ़ो. */
	kमुक्त(ntbl);
	वापस rcu_dereference(*prev);
पूर्ण

अटल काष्ठा bucket_table *nested_bucket_table_alloc(काष्ठा rhashtable *ht,
						      माप_प्रकार nbuckets,
						      gfp_t gfp)
अणु
	स्थिर अचिन्हित पूर्णांक shअगरt = PAGE_SHIFT - ilog2(माप(व्योम *));
	काष्ठा bucket_table *tbl;
	माप_प्रकार size;

	अगर (nbuckets < (1 << (shअगरt + 1)))
		वापस शून्य;

	size = माप(*tbl) + माप(tbl->buckets[0]);

	tbl = kzalloc(size, gfp);
	अगर (!tbl)
		वापस शून्य;

	अगर (!nested_table_alloc(ht, (जोड़ nested_table __rcu **)tbl->buckets,
				false)) अणु
		kमुक्त(tbl);
		वापस शून्य;
	पूर्ण

	tbl->nest = (ilog2(nbuckets) - 1) % shअगरt + 1;

	वापस tbl;
पूर्ण

अटल काष्ठा bucket_table *bucket_table_alloc(काष्ठा rhashtable *ht,
					       माप_प्रकार nbuckets,
					       gfp_t gfp)
अणु
	काष्ठा bucket_table *tbl = शून्य;
	माप_प्रकार size;
	पूर्णांक i;
	अटल काष्ठा lock_class_key __key;

	tbl = kvzalloc(काष्ठा_size(tbl, buckets, nbuckets), gfp);

	size = nbuckets;

	अगर (tbl == शून्य && (gfp & ~__GFP_NOFAIL) != GFP_KERNEL) अणु
		tbl = nested_bucket_table_alloc(ht, nbuckets, gfp);
		nbuckets = 0;
	पूर्ण

	अगर (tbl == शून्य)
		वापस शून्य;

	lockdep_init_map(&tbl->dep_map, "rhashtable_bucket", &__key, 0);

	tbl->size = size;

	rcu_head_init(&tbl->rcu);
	INIT_LIST_HEAD(&tbl->walkers);

	tbl->hash_rnd = get_अक्रमom_u32();

	क्रम (i = 0; i < nbuckets; i++)
		INIT_RHT_शून्यS_HEAD(tbl->buckets[i]);

	वापस tbl;
पूर्ण

अटल काष्ठा bucket_table *rhashtable_last_table(काष्ठा rhashtable *ht,
						  काष्ठा bucket_table *tbl)
अणु
	काष्ठा bucket_table *new_tbl;

	करो अणु
		new_tbl = tbl;
		tbl = rht_dereference_rcu(tbl->future_tbl, ht);
	पूर्ण जबतक (tbl);

	वापस new_tbl;
पूर्ण

अटल पूर्णांक rhashtable_rehash_one(काष्ठा rhashtable *ht,
				 काष्ठा rhash_lock_head __rcu **bkt,
				 अचिन्हित पूर्णांक old_hash)
अणु
	काष्ठा bucket_table *old_tbl = rht_dereference(ht->tbl, ht);
	काष्ठा bucket_table *new_tbl = rhashtable_last_table(ht, old_tbl);
	पूर्णांक err = -EAGAIN;
	काष्ठा rhash_head *head, *next, *entry;
	काष्ठा rhash_head __rcu **pprev = शून्य;
	अचिन्हित पूर्णांक new_hash;

	अगर (new_tbl->nest)
		जाओ out;

	err = -ENOENT;

	rht_क्रम_each_from(entry, rht_ptr(bkt, old_tbl, old_hash),
			  old_tbl, old_hash) अणु
		err = 0;
		next = rht_dereference_bucket(entry->next, old_tbl, old_hash);

		अगर (rht_is_a_nulls(next))
			अवरोध;

		pprev = &entry->next;
	पूर्ण

	अगर (err)
		जाओ out;

	new_hash = head_hashfn(ht, new_tbl, entry);

	rht_lock_nested(new_tbl, &new_tbl->buckets[new_hash], SINGLE_DEPTH_NESTING);

	head = rht_ptr(new_tbl->buckets + new_hash, new_tbl, new_hash);

	RCU_INIT_POINTER(entry->next, head);

	rht_assign_unlock(new_tbl, &new_tbl->buckets[new_hash], entry);

	अगर (pprev)
		rcu_assign_poपूर्णांकer(*pprev, next);
	अन्यथा
		/* Need to preserved the bit lock. */
		rht_assign_locked(bkt, next);

out:
	वापस err;
पूर्ण

अटल पूर्णांक rhashtable_rehash_chain(काष्ठा rhashtable *ht,
				    अचिन्हित पूर्णांक old_hash)
अणु
	काष्ठा bucket_table *old_tbl = rht_dereference(ht->tbl, ht);
	काष्ठा rhash_lock_head __rcu **bkt = rht_bucket_var(old_tbl, old_hash);
	पूर्णांक err;

	अगर (!bkt)
		वापस 0;
	rht_lock(old_tbl, bkt);

	जबतक (!(err = rhashtable_rehash_one(ht, bkt, old_hash)))
		;

	अगर (err == -ENOENT)
		err = 0;
	rht_unlock(old_tbl, bkt);

	वापस err;
पूर्ण

अटल पूर्णांक rhashtable_rehash_attach(काष्ठा rhashtable *ht,
				    काष्ठा bucket_table *old_tbl,
				    काष्ठा bucket_table *new_tbl)
अणु
	/* Make insertions go पूर्णांकo the new, empty table right away. Deletions
	 * and lookups will be attempted in both tables until we synchronize.
	 * As cmpxchg() provides strong barriers, we करो not need
	 * rcu_assign_poपूर्णांकer().
	 */

	अगर (cmpxchg((काष्ठा bucket_table **)&old_tbl->future_tbl, शून्य,
		    new_tbl) != शून्य)
		वापस -EEXIST;

	वापस 0;
पूर्ण

अटल पूर्णांक rhashtable_rehash_table(काष्ठा rhashtable *ht)
अणु
	काष्ठा bucket_table *old_tbl = rht_dereference(ht->tbl, ht);
	काष्ठा bucket_table *new_tbl;
	काष्ठा rhashtable_walker *walker;
	अचिन्हित पूर्णांक old_hash;
	पूर्णांक err;

	new_tbl = rht_dereference(old_tbl->future_tbl, ht);
	अगर (!new_tbl)
		वापस 0;

	क्रम (old_hash = 0; old_hash < old_tbl->size; old_hash++) अणु
		err = rhashtable_rehash_chain(ht, old_hash);
		अगर (err)
			वापस err;
		cond_resched();
	पूर्ण

	/* Publish the new table poपूर्णांकer. */
	rcu_assign_poपूर्णांकer(ht->tbl, new_tbl);

	spin_lock(&ht->lock);
	list_क्रम_each_entry(walker, &old_tbl->walkers, list)
		walker->tbl = शून्य;

	/* Wait क्रम पढ़ोers. All new पढ़ोers will see the new
	 * table, and thus no references to the old table will
	 * reमुख्य.
	 * We करो this inside the locked region so that
	 * rhashtable_walk_stop() can use rcu_head_after_call_rcu()
	 * to check अगर it should not re-link the table.
	 */
	call_rcu(&old_tbl->rcu, bucket_table_मुक्त_rcu);
	spin_unlock(&ht->lock);

	वापस rht_dereference(new_tbl->future_tbl, ht) ? -EAGAIN : 0;
पूर्ण

अटल पूर्णांक rhashtable_rehash_alloc(काष्ठा rhashtable *ht,
				   काष्ठा bucket_table *old_tbl,
				   अचिन्हित पूर्णांक size)
अणु
	काष्ठा bucket_table *new_tbl;
	पूर्णांक err;

	ASSERT_RHT_MUTEX(ht);

	new_tbl = bucket_table_alloc(ht, size, GFP_KERNEL);
	अगर (new_tbl == शून्य)
		वापस -ENOMEM;

	err = rhashtable_rehash_attach(ht, old_tbl, new_tbl);
	अगर (err)
		bucket_table_मुक्त(new_tbl);

	वापस err;
पूर्ण

/**
 * rhashtable_shrink - Shrink hash table जबतक allowing concurrent lookups
 * @ht:		the hash table to shrink
 *
 * This function shrinks the hash table to fit, i.e., the smallest
 * size would not cause it to expand right away स्वतःmatically.
 *
 * The caller must ensure that no concurrent resizing occurs by holding
 * ht->mutex.
 *
 * The caller must ensure that no concurrent table mutations take place.
 * It is however valid to have concurrent lookups अगर they are RCU रक्षित.
 *
 * It is valid to have concurrent insertions and deletions रक्षित by per
 * bucket locks or concurrent RCU रक्षित lookups and traversals.
 */
अटल पूर्णांक rhashtable_shrink(काष्ठा rhashtable *ht)
अणु
	काष्ठा bucket_table *old_tbl = rht_dereference(ht->tbl, ht);
	अचिन्हित पूर्णांक nelems = atomic_पढ़ो(&ht->nelems);
	अचिन्हित पूर्णांक size = 0;

	अगर (nelems)
		size = roundup_घात_of_two(nelems * 3 / 2);
	अगर (size < ht->p.min_size)
		size = ht->p.min_size;

	अगर (old_tbl->size <= size)
		वापस 0;

	अगर (rht_dereference(old_tbl->future_tbl, ht))
		वापस -EEXIST;

	वापस rhashtable_rehash_alloc(ht, old_tbl, size);
पूर्ण

अटल व्योम rht_deferred_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rhashtable *ht;
	काष्ठा bucket_table *tbl;
	पूर्णांक err = 0;

	ht = container_of(work, काष्ठा rhashtable, run_work);
	mutex_lock(&ht->mutex);

	tbl = rht_dereference(ht->tbl, ht);
	tbl = rhashtable_last_table(ht, tbl);

	अगर (rht_grow_above_75(ht, tbl))
		err = rhashtable_rehash_alloc(ht, tbl, tbl->size * 2);
	अन्यथा अगर (ht->p.स्वतःmatic_shrinking && rht_shrink_below_30(ht, tbl))
		err = rhashtable_shrink(ht);
	अन्यथा अगर (tbl->nest)
		err = rhashtable_rehash_alloc(ht, tbl, tbl->size);

	अगर (!err || err == -EEXIST) अणु
		पूर्णांक nerr;

		nerr = rhashtable_rehash_table(ht);
		err = err ?: nerr;
	पूर्ण

	mutex_unlock(&ht->mutex);

	अगर (err)
		schedule_work(&ht->run_work);
पूर्ण

अटल पूर्णांक rhashtable_insert_rehash(काष्ठा rhashtable *ht,
				    काष्ठा bucket_table *tbl)
अणु
	काष्ठा bucket_table *old_tbl;
	काष्ठा bucket_table *new_tbl;
	अचिन्हित पूर्णांक size;
	पूर्णांक err;

	old_tbl = rht_dereference_rcu(ht->tbl, ht);

	size = tbl->size;

	err = -EBUSY;

	अगर (rht_grow_above_75(ht, tbl))
		size *= 2;
	/* Do not schedule more than one rehash */
	अन्यथा अगर (old_tbl != tbl)
		जाओ fail;

	err = -ENOMEM;

	new_tbl = bucket_table_alloc(ht, size, GFP_ATOMIC | __GFP_NOWARN);
	अगर (new_tbl == शून्य)
		जाओ fail;

	err = rhashtable_rehash_attach(ht, tbl, new_tbl);
	अगर (err) अणु
		bucket_table_मुक्त(new_tbl);
		अगर (err == -EEXIST)
			err = 0;
	पूर्ण अन्यथा
		schedule_work(&ht->run_work);

	वापस err;

fail:
	/* Do not fail the insert अगर someone अन्यथा did a rehash. */
	अगर (likely(rcu_access_poपूर्णांकer(tbl->future_tbl)))
		वापस 0;

	/* Schedule async rehash to retry allocation in process context. */
	अगर (err == -ENOMEM)
		schedule_work(&ht->run_work);

	वापस err;
पूर्ण

अटल व्योम *rhashtable_lookup_one(काष्ठा rhashtable *ht,
				   काष्ठा rhash_lock_head __rcu **bkt,
				   काष्ठा bucket_table *tbl, अचिन्हित पूर्णांक hash,
				   स्थिर व्योम *key, काष्ठा rhash_head *obj)
अणु
	काष्ठा rhashtable_compare_arg arg = अणु
		.ht = ht,
		.key = key,
	पूर्ण;
	काष्ठा rhash_head __rcu **pprev = शून्य;
	काष्ठा rhash_head *head;
	पूर्णांक elasticity;

	elasticity = RHT_ELASTICITY;
	rht_क्रम_each_from(head, rht_ptr(bkt, tbl, hash), tbl, hash) अणु
		काष्ठा rhlist_head *list;
		काष्ठा rhlist_head *plist;

		elasticity--;
		अगर (!key ||
		    (ht->p.obj_cmpfn ?
		     ht->p.obj_cmpfn(&arg, rht_obj(ht, head)) :
		     rhashtable_compare(&arg, rht_obj(ht, head)))) अणु
			pprev = &head->next;
			जारी;
		पूर्ण

		अगर (!ht->rhlist)
			वापस rht_obj(ht, head);

		list = container_of(obj, काष्ठा rhlist_head, rhead);
		plist = container_of(head, काष्ठा rhlist_head, rhead);

		RCU_INIT_POINTER(list->next, plist);
		head = rht_dereference_bucket(head->next, tbl, hash);
		RCU_INIT_POINTER(list->rhead.next, head);
		अगर (pprev)
			rcu_assign_poपूर्णांकer(*pprev, obj);
		अन्यथा
			/* Need to preserve the bit lock */
			rht_assign_locked(bkt, obj);

		वापस शून्य;
	पूर्ण

	अगर (elasticity <= 0)
		वापस ERR_PTR(-EAGAIN);

	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल काष्ठा bucket_table *rhashtable_insert_one(
	काष्ठा rhashtable *ht, काष्ठा rhash_lock_head __rcu **bkt,
	काष्ठा bucket_table *tbl, अचिन्हित पूर्णांक hash, काष्ठा rhash_head *obj,
	व्योम *data)
अणु
	काष्ठा bucket_table *new_tbl;
	काष्ठा rhash_head *head;

	अगर (!IS_ERR_OR_शून्य(data))
		वापस ERR_PTR(-EEXIST);

	अगर (PTR_ERR(data) != -EAGAIN && PTR_ERR(data) != -ENOENT)
		वापस ERR_CAST(data);

	new_tbl = rht_dereference_rcu(tbl->future_tbl, ht);
	अगर (new_tbl)
		वापस new_tbl;

	अगर (PTR_ERR(data) != -ENOENT)
		वापस ERR_CAST(data);

	अगर (unlikely(rht_grow_above_max(ht, tbl)))
		वापस ERR_PTR(-E2BIG);

	अगर (unlikely(rht_grow_above_100(ht, tbl)))
		वापस ERR_PTR(-EAGAIN);

	head = rht_ptr(bkt, tbl, hash);

	RCU_INIT_POINTER(obj->next, head);
	अगर (ht->rhlist) अणु
		काष्ठा rhlist_head *list;

		list = container_of(obj, काष्ठा rhlist_head, rhead);
		RCU_INIT_POINTER(list->next, शून्य);
	पूर्ण

	/* bkt is always the head of the list, so it holds
	 * the lock, which we need to preserve
	 */
	rht_assign_locked(bkt, obj);

	atomic_inc(&ht->nelems);
	अगर (rht_grow_above_75(ht, tbl))
		schedule_work(&ht->run_work);

	वापस शून्य;
पूर्ण

अटल व्योम *rhashtable_try_insert(काष्ठा rhashtable *ht, स्थिर व्योम *key,
				   काष्ठा rhash_head *obj)
अणु
	काष्ठा bucket_table *new_tbl;
	काष्ठा bucket_table *tbl;
	काष्ठा rhash_lock_head __rcu **bkt;
	अचिन्हित पूर्णांक hash;
	व्योम *data;

	new_tbl = rcu_dereference(ht->tbl);

	करो अणु
		tbl = new_tbl;
		hash = rht_head_hashfn(ht, tbl, obj, ht->p);
		अगर (rcu_access_poपूर्णांकer(tbl->future_tbl))
			/* Failure is OK */
			bkt = rht_bucket_var(tbl, hash);
		अन्यथा
			bkt = rht_bucket_insert(ht, tbl, hash);
		अगर (bkt == शून्य) अणु
			new_tbl = rht_dereference_rcu(tbl->future_tbl, ht);
			data = ERR_PTR(-EAGAIN);
		पूर्ण अन्यथा अणु
			rht_lock(tbl, bkt);
			data = rhashtable_lookup_one(ht, bkt, tbl,
						     hash, key, obj);
			new_tbl = rhashtable_insert_one(ht, bkt, tbl,
							hash, obj, data);
			अगर (PTR_ERR(new_tbl) != -EEXIST)
				data = ERR_CAST(new_tbl);

			rht_unlock(tbl, bkt);
		पूर्ण
	पूर्ण जबतक (!IS_ERR_OR_शून्य(new_tbl));

	अगर (PTR_ERR(data) == -EAGAIN)
		data = ERR_PTR(rhashtable_insert_rehash(ht, tbl) ?:
			       -EAGAIN);

	वापस data;
पूर्ण

व्योम *rhashtable_insert_slow(काष्ठा rhashtable *ht, स्थिर व्योम *key,
			     काष्ठा rhash_head *obj)
अणु
	व्योम *data;

	करो अणु
		rcu_पढ़ो_lock();
		data = rhashtable_try_insert(ht, key, obj);
		rcu_पढ़ो_unlock();
	पूर्ण जबतक (PTR_ERR(data) == -EAGAIN);

	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(rhashtable_insert_slow);

/**
 * rhashtable_walk_enter - Initialise an iterator
 * @ht:		Table to walk over
 * @iter:	Hash table Iterator
 *
 * This function prepares a hash table walk.
 *
 * Note that अगर you restart a walk after rhashtable_walk_stop you
 * may see the same object twice.  Also, you may miss objects अगर
 * there are removals in between rhashtable_walk_stop and the next
 * call to rhashtable_walk_start.
 *
 * For a completely stable walk you should स्थिरruct your own data
 * काष्ठाure outside the hash table.
 *
 * This function may be called from any process context, including
 * non-preemptable context, but cannot be called from softirq or
 * hardirq context.
 *
 * You must call rhashtable_walk_निकास after this function वापसs.
 */
व्योम rhashtable_walk_enter(काष्ठा rhashtable *ht, काष्ठा rhashtable_iter *iter)
अणु
	iter->ht = ht;
	iter->p = शून्य;
	iter->slot = 0;
	iter->skip = 0;
	iter->end_of_table = 0;

	spin_lock(&ht->lock);
	iter->walker.tbl =
		rcu_dereference_रक्षित(ht->tbl, lockdep_is_held(&ht->lock));
	list_add(&iter->walker.list, &iter->walker.tbl->walkers);
	spin_unlock(&ht->lock);
पूर्ण
EXPORT_SYMBOL_GPL(rhashtable_walk_enter);

/**
 * rhashtable_walk_निकास - Free an iterator
 * @iter:	Hash table Iterator
 *
 * This function मुक्तs resources allocated by rhashtable_walk_enter.
 */
व्योम rhashtable_walk_निकास(काष्ठा rhashtable_iter *iter)
अणु
	spin_lock(&iter->ht->lock);
	अगर (iter->walker.tbl)
		list_del(&iter->walker.list);
	spin_unlock(&iter->ht->lock);
पूर्ण
EXPORT_SYMBOL_GPL(rhashtable_walk_निकास);

/**
 * rhashtable_walk_start_check - Start a hash table walk
 * @iter:	Hash table iterator
 *
 * Start a hash table walk at the current iterator position.  Note that we take
 * the RCU lock in all हालs including when we वापस an error.  So you must
 * always call rhashtable_walk_stop to clean up.
 *
 * Returns zero अगर successful.
 *
 * Returns -EAGAIN अगर resize event occured.  Note that the iterator
 * will शुरुआत back to the beginning and you may use it immediately
 * by calling rhashtable_walk_next.
 *
 * rhashtable_walk_start is defined as an अंतरभूत variant that वापसs
 * व्योम. This is preferred in हालs where the caller would ignore
 * resize events and always जारी.
 */
पूर्णांक rhashtable_walk_start_check(काष्ठा rhashtable_iter *iter)
	__acquires(RCU)
अणु
	काष्ठा rhashtable *ht = iter->ht;
	bool rhlist = ht->rhlist;

	rcu_पढ़ो_lock();

	spin_lock(&ht->lock);
	अगर (iter->walker.tbl)
		list_del(&iter->walker.list);
	spin_unlock(&ht->lock);

	अगर (iter->end_of_table)
		वापस 0;
	अगर (!iter->walker.tbl) अणु
		iter->walker.tbl = rht_dereference_rcu(ht->tbl, ht);
		iter->slot = 0;
		iter->skip = 0;
		वापस -EAGAIN;
	पूर्ण

	अगर (iter->p && !rhlist) अणु
		/*
		 * We need to validate that 'p' is still in the table, and
		 * अगर so, update 'skip'
		 */
		काष्ठा rhash_head *p;
		पूर्णांक skip = 0;
		rht_क्रम_each_rcu(p, iter->walker.tbl, iter->slot) अणु
			skip++;
			अगर (p == iter->p) अणु
				iter->skip = skip;
				जाओ found;
			पूर्ण
		पूर्ण
		iter->p = शून्य;
	पूर्ण अन्यथा अगर (iter->p && rhlist) अणु
		/* Need to validate that 'list' is still in the table, and
		 * अगर so, update 'skip' and 'p'.
		 */
		काष्ठा rhash_head *p;
		काष्ठा rhlist_head *list;
		पूर्णांक skip = 0;
		rht_क्रम_each_rcu(p, iter->walker.tbl, iter->slot) अणु
			क्रम (list = container_of(p, काष्ठा rhlist_head, rhead);
			     list;
			     list = rcu_dereference(list->next)) अणु
				skip++;
				अगर (list == iter->list) अणु
					iter->p = p;
					iter->skip = skip;
					जाओ found;
				पूर्ण
			पूर्ण
		पूर्ण
		iter->p = शून्य;
	पूर्ण
found:
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rhashtable_walk_start_check);

/**
 * __rhashtable_walk_find_next - Find the next element in a table (or the first
 * one in हाल of a new walk).
 *
 * @iter:	Hash table iterator
 *
 * Returns the found object or शून्य when the end of the table is reached.
 *
 * Returns -EAGAIN अगर resize event occurred.
 */
अटल व्योम *__rhashtable_walk_find_next(काष्ठा rhashtable_iter *iter)
अणु
	काष्ठा bucket_table *tbl = iter->walker.tbl;
	काष्ठा rhlist_head *list = iter->list;
	काष्ठा rhashtable *ht = iter->ht;
	काष्ठा rhash_head *p = iter->p;
	bool rhlist = ht->rhlist;

	अगर (!tbl)
		वापस शून्य;

	क्रम (; iter->slot < tbl->size; iter->slot++) अणु
		पूर्णांक skip = iter->skip;

		rht_क्रम_each_rcu(p, tbl, iter->slot) अणु
			अगर (rhlist) अणु
				list = container_of(p, काष्ठा rhlist_head,
						    rhead);
				करो अणु
					अगर (!skip)
						जाओ next;
					skip--;
					list = rcu_dereference(list->next);
				पूर्ण जबतक (list);

				जारी;
			पूर्ण
			अगर (!skip)
				अवरोध;
			skip--;
		पूर्ण

next:
		अगर (!rht_is_a_nulls(p)) अणु
			iter->skip++;
			iter->p = p;
			iter->list = list;
			वापस rht_obj(ht, rhlist ? &list->rhead : p);
		पूर्ण

		iter->skip = 0;
	पूर्ण

	iter->p = शून्य;

	/* Ensure we see any new tables. */
	smp_rmb();

	iter->walker.tbl = rht_dereference_rcu(tbl->future_tbl, ht);
	अगर (iter->walker.tbl) अणु
		iter->slot = 0;
		iter->skip = 0;
		वापस ERR_PTR(-EAGAIN);
	पूर्ण अन्यथा अणु
		iter->end_of_table = true;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * rhashtable_walk_next - Return the next object and advance the iterator
 * @iter:	Hash table iterator
 *
 * Note that you must call rhashtable_walk_stop when you are finished
 * with the walk.
 *
 * Returns the next object or शून्य when the end of the table is reached.
 *
 * Returns -EAGAIN अगर resize event occurred.  Note that the iterator
 * will शुरुआत back to the beginning and you may जारी to use it.
 */
व्योम *rhashtable_walk_next(काष्ठा rhashtable_iter *iter)
अणु
	काष्ठा rhlist_head *list = iter->list;
	काष्ठा rhashtable *ht = iter->ht;
	काष्ठा rhash_head *p = iter->p;
	bool rhlist = ht->rhlist;

	अगर (p) अणु
		अगर (!rhlist || !(list = rcu_dereference(list->next))) अणु
			p = rcu_dereference(p->next);
			list = container_of(p, काष्ठा rhlist_head, rhead);
		पूर्ण
		अगर (!rht_is_a_nulls(p)) अणु
			iter->skip++;
			iter->p = p;
			iter->list = list;
			वापस rht_obj(ht, rhlist ? &list->rhead : p);
		पूर्ण

		/* At the end of this slot, चयन to next one and then find
		 * next entry from that poपूर्णांक.
		 */
		iter->skip = 0;
		iter->slot++;
	पूर्ण

	वापस __rhashtable_walk_find_next(iter);
पूर्ण
EXPORT_SYMBOL_GPL(rhashtable_walk_next);

/**
 * rhashtable_walk_peek - Return the next object but करोn't advance the iterator
 * @iter:	Hash table iterator
 *
 * Returns the next object or शून्य when the end of the table is reached.
 *
 * Returns -EAGAIN अगर resize event occurred.  Note that the iterator
 * will शुरुआत back to the beginning and you may जारी to use it.
 */
व्योम *rhashtable_walk_peek(काष्ठा rhashtable_iter *iter)
अणु
	काष्ठा rhlist_head *list = iter->list;
	काष्ठा rhashtable *ht = iter->ht;
	काष्ठा rhash_head *p = iter->p;

	अगर (p)
		वापस rht_obj(ht, ht->rhlist ? &list->rhead : p);

	/* No object found in current iter, find next one in the table. */

	अगर (iter->skip) अणु
		/* A nonzero skip value poपूर्णांकs to the next entry in the table
		 * beyond that last one that was found. Decrement skip so
		 * we find the current value. __rhashtable_walk_find_next
		 * will restore the original value of skip assuming that
		 * the table hasn't changed.
		 */
		iter->skip--;
	पूर्ण

	वापस __rhashtable_walk_find_next(iter);
पूर्ण
EXPORT_SYMBOL_GPL(rhashtable_walk_peek);

/**
 * rhashtable_walk_stop - Finish a hash table walk
 * @iter:	Hash table iterator
 *
 * Finish a hash table walk.  Does not reset the iterator to the start of the
 * hash table.
 */
व्योम rhashtable_walk_stop(काष्ठा rhashtable_iter *iter)
	__releases(RCU)
अणु
	काष्ठा rhashtable *ht;
	काष्ठा bucket_table *tbl = iter->walker.tbl;

	अगर (!tbl)
		जाओ out;

	ht = iter->ht;

	spin_lock(&ht->lock);
	अगर (rcu_head_after_call_rcu(&tbl->rcu, bucket_table_मुक्त_rcu))
		/* This bucket table is being मुक्तd, करोn't re-link it. */
		iter->walker.tbl = शून्य;
	अन्यथा
		list_add(&iter->walker.list, &tbl->walkers);
	spin_unlock(&ht->lock);

out:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(rhashtable_walk_stop);

अटल माप_प्रकार rounded_hashtable_size(स्थिर काष्ठा rhashtable_params *params)
अणु
	माप_प्रकार retsize;

	अगर (params->nelem_hपूर्णांक)
		retsize = max(roundup_घात_of_two(params->nelem_hपूर्णांक * 4 / 3),
			      (अचिन्हित दीर्घ)params->min_size);
	अन्यथा
		retsize = max(HASH_DEFAULT_SIZE,
			      (अचिन्हित दीर्घ)params->min_size);

	वापस retsize;
पूर्ण

अटल u32 rhashtable_jhash2(स्थिर व्योम *key, u32 length, u32 seed)
अणु
	वापस jhash2(key, length, seed);
पूर्ण

/**
 * rhashtable_init - initialize a new hash table
 * @ht:		hash table to be initialized
 * @params:	configuration parameters
 *
 * Initializes a new hash table based on the provided configuration
 * parameters. A table can be configured either with a variable or
 * fixed length key:
 *
 * Configuration Example 1: Fixed length keys
 * काष्ठा test_obj अणु
 *	पूर्णांक			key;
 *	व्योम *			my_member;
 *	काष्ठा rhash_head	node;
 * पूर्ण;
 *
 * काष्ठा rhashtable_params params = अणु
 *	.head_offset = दुरत्व(काष्ठा test_obj, node),
 *	.key_offset = दुरत्व(काष्ठा test_obj, key),
 *	.key_len = माप(पूर्णांक),
 *	.hashfn = jhash,
 * पूर्ण;
 *
 * Configuration Example 2: Variable length keys
 * काष्ठा test_obj अणु
 *	[...]
 *	काष्ठा rhash_head	node;
 * पूर्ण;
 *
 * u32 my_hash_fn(स्थिर व्योम *data, u32 len, u32 seed)
 * अणु
 *	काष्ठा test_obj *obj = data;
 *
 *	वापस [... hash ...];
 * पूर्ण
 *
 * काष्ठा rhashtable_params params = अणु
 *	.head_offset = दुरत्व(काष्ठा test_obj, node),
 *	.hashfn = jhash,
 *	.obj_hashfn = my_hash_fn,
 * पूर्ण;
 */
पूर्णांक rhashtable_init(काष्ठा rhashtable *ht,
		    स्थिर काष्ठा rhashtable_params *params)
अणु
	काष्ठा bucket_table *tbl;
	माप_प्रकार size;

	अगर ((!params->key_len && !params->obj_hashfn) ||
	    (params->obj_hashfn && !params->obj_cmpfn))
		वापस -EINVAL;

	स_रखो(ht, 0, माप(*ht));
	mutex_init(&ht->mutex);
	spin_lock_init(&ht->lock);
	स_नकल(&ht->p, params, माप(*params));

	अगर (params->min_size)
		ht->p.min_size = roundup_घात_of_two(params->min_size);

	/* Cap total entries at 2^31 to aव्योम nelems overflow. */
	ht->max_elems = 1u << 31;

	अगर (params->max_size) अणु
		ht->p.max_size = roundकरोwn_घात_of_two(params->max_size);
		अगर (ht->p.max_size < ht->max_elems / 2)
			ht->max_elems = ht->p.max_size * 2;
	पूर्ण

	ht->p.min_size = max_t(u16, ht->p.min_size, HASH_MIN_SIZE);

	size = rounded_hashtable_size(&ht->p);

	ht->key_len = ht->p.key_len;
	अगर (!params->hashfn) अणु
		ht->p.hashfn = jhash;

		अगर (!(ht->key_len & (माप(u32) - 1))) अणु
			ht->key_len /= माप(u32);
			ht->p.hashfn = rhashtable_jhash2;
		पूर्ण
	पूर्ण

	/*
	 * This is api initialization and thus we need to guarantee the
	 * initial rhashtable allocation. Upon failure, retry with the
	 * smallest possible size with __GFP_NOFAIL semantics.
	 */
	tbl = bucket_table_alloc(ht, size, GFP_KERNEL);
	अगर (unlikely(tbl == शून्य)) अणु
		size = max_t(u16, ht->p.min_size, HASH_MIN_SIZE);
		tbl = bucket_table_alloc(ht, size, GFP_KERNEL | __GFP_NOFAIL);
	पूर्ण

	atomic_set(&ht->nelems, 0);

	RCU_INIT_POINTER(ht->tbl, tbl);

	INIT_WORK(&ht->run_work, rht_deferred_worker);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rhashtable_init);

/**
 * rhltable_init - initialize a new hash list table
 * @hlt:	hash list table to be initialized
 * @params:	configuration parameters
 *
 * Initializes a new hash list table.
 *
 * See करोcumentation क्रम rhashtable_init.
 */
पूर्णांक rhltable_init(काष्ठा rhltable *hlt, स्थिर काष्ठा rhashtable_params *params)
अणु
	पूर्णांक err;

	err = rhashtable_init(&hlt->ht, params);
	hlt->ht.rhlist = true;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rhltable_init);

अटल व्योम rhashtable_मुक्त_one(काष्ठा rhashtable *ht, काष्ठा rhash_head *obj,
				व्योम (*मुक्त_fn)(व्योम *ptr, व्योम *arg),
				व्योम *arg)
अणु
	काष्ठा rhlist_head *list;

	अगर (!ht->rhlist) अणु
		मुक्त_fn(rht_obj(ht, obj), arg);
		वापस;
	पूर्ण

	list = container_of(obj, काष्ठा rhlist_head, rhead);
	करो अणु
		obj = &list->rhead;
		list = rht_dereference(list->next, ht);
		मुक्त_fn(rht_obj(ht, obj), arg);
	पूर्ण जबतक (list);
पूर्ण

/**
 * rhashtable_मुक्त_and_destroy - मुक्त elements and destroy hash table
 * @ht:		the hash table to destroy
 * @मुक्त_fn:	callback to release resources of element
 * @arg:	poपूर्णांकer passed to मुक्त_fn
 *
 * Stops an eventual async resize. If defined, invokes मुक्त_fn क्रम each
 * element to releasal resources. Please note that RCU रक्षित
 * पढ़ोers may still be accessing the elements. Releasing of resources
 * must occur in a compatible manner. Then मुक्तs the bucket array.
 *
 * This function will eventually sleep to रुको क्रम an async resize
 * to complete. The caller is responsible that no further ग_लिखो operations
 * occurs in parallel.
 */
व्योम rhashtable_मुक्त_and_destroy(काष्ठा rhashtable *ht,
				 व्योम (*मुक्त_fn)(व्योम *ptr, व्योम *arg),
				 व्योम *arg)
अणु
	काष्ठा bucket_table *tbl, *next_tbl;
	अचिन्हित पूर्णांक i;

	cancel_work_sync(&ht->run_work);

	mutex_lock(&ht->mutex);
	tbl = rht_dereference(ht->tbl, ht);
restart:
	अगर (मुक्त_fn) अणु
		क्रम (i = 0; i < tbl->size; i++) अणु
			काष्ठा rhash_head *pos, *next;

			cond_resched();
			क्रम (pos = rht_ptr_exclusive(rht_bucket(tbl, i)),
			     next = !rht_is_a_nulls(pos) ?
					rht_dereference(pos->next, ht) : शून्य;
			     !rht_is_a_nulls(pos);
			     pos = next,
			     next = !rht_is_a_nulls(pos) ?
					rht_dereference(pos->next, ht) : शून्य)
				rhashtable_मुक्त_one(ht, pos, मुक्त_fn, arg);
		पूर्ण
	पूर्ण

	next_tbl = rht_dereference(tbl->future_tbl, ht);
	bucket_table_मुक्त(tbl);
	अगर (next_tbl) अणु
		tbl = next_tbl;
		जाओ restart;
	पूर्ण
	mutex_unlock(&ht->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(rhashtable_मुक्त_and_destroy);

व्योम rhashtable_destroy(काष्ठा rhashtable *ht)
अणु
	वापस rhashtable_मुक्त_and_destroy(ht, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(rhashtable_destroy);

काष्ठा rhash_lock_head __rcu **__rht_bucket_nested(
	स्थिर काष्ठा bucket_table *tbl, अचिन्हित पूर्णांक hash)
अणु
	स्थिर अचिन्हित पूर्णांक shअगरt = PAGE_SHIFT - ilog2(माप(व्योम *));
	अचिन्हित पूर्णांक index = hash & ((1 << tbl->nest) - 1);
	अचिन्हित पूर्णांक size = tbl->size >> tbl->nest;
	अचिन्हित पूर्णांक subhash = hash;
	जोड़ nested_table *ntbl;

	ntbl = nested_table_top(tbl);
	ntbl = rht_dereference_bucket_rcu(ntbl[index].table, tbl, hash);
	subhash >>= tbl->nest;

	जबतक (ntbl && size > (1 << shअगरt)) अणु
		index = subhash & ((1 << shअगरt) - 1);
		ntbl = rht_dereference_bucket_rcu(ntbl[index].table,
						  tbl, hash);
		size >>= shअगरt;
		subhash >>= shअगरt;
	पूर्ण

	अगर (!ntbl)
		वापस शून्य;

	वापस &ntbl[subhash].bucket;

पूर्ण
EXPORT_SYMBOL_GPL(__rht_bucket_nested);

काष्ठा rhash_lock_head __rcu **rht_bucket_nested(
	स्थिर काष्ठा bucket_table *tbl, अचिन्हित पूर्णांक hash)
अणु
	अटल काष्ठा rhash_lock_head __rcu *rhnull;

	अगर (!rhnull)
		INIT_RHT_शून्यS_HEAD(rhnull);
	वापस __rht_bucket_nested(tbl, hash) ?: &rhnull;
पूर्ण
EXPORT_SYMBOL_GPL(rht_bucket_nested);

काष्ठा rhash_lock_head __rcu **rht_bucket_nested_insert(
	काष्ठा rhashtable *ht, काष्ठा bucket_table *tbl, अचिन्हित पूर्णांक hash)
अणु
	स्थिर अचिन्हित पूर्णांक shअगरt = PAGE_SHIFT - ilog2(माप(व्योम *));
	अचिन्हित पूर्णांक index = hash & ((1 << tbl->nest) - 1);
	अचिन्हित पूर्णांक size = tbl->size >> tbl->nest;
	जोड़ nested_table *ntbl;

	ntbl = nested_table_top(tbl);
	hash >>= tbl->nest;
	ntbl = nested_table_alloc(ht, &ntbl[index].table,
				  size <= (1 << shअगरt));

	जबतक (ntbl && size > (1 << shअगरt)) अणु
		index = hash & ((1 << shअगरt) - 1);
		size >>= shअगरt;
		hash >>= shअगरt;
		ntbl = nested_table_alloc(ht, &ntbl[index].table,
					  size <= (1 << shअगरt));
	पूर्ण

	अगर (!ntbl)
		वापस शून्य;

	वापस &ntbl[hash].bucket;

पूर्ण
EXPORT_SYMBOL_GPL(rht_bucket_nested_insert);
