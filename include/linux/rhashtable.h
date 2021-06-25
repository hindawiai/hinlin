<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Resizable, Scalable, Concurrent Hash Table
 *
 * Copyright (c) 2015-2016 Herbert Xu <herbert@gonकरोr.apana.org.au>
 * Copyright (c) 2014-2015 Thomas Graf <tgraf@suug.ch>
 * Copyright (c) 2008-2014 Patrick McHardy <kaber@trash.net>
 *
 * Code partially derived from nft_hash
 * Rewritten with rehash code from br_multicast plus single list
 * poपूर्णांकer as suggested by Josh Triplett
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित _LINUX_RHASHTABLE_H
#घोषणा _LINUX_RHASHTABLE_H

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/jhash.h>
#समावेश <linux/list_nulls.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/rculist.h>
#समावेश <linux/bit_spinlock.h>

#समावेश <linux/rhashtable-types.h>
/*
 * Objects in an rhashtable have an embedded काष्ठा rhash_head
 * which is linked पूर्णांकo as hash chain from the hash table - or one
 * of two or more hash tables when the rhashtable is being resized.
 * The end of the chain is marked with a special nulls marks which has
 * the least signअगरicant bit set but otherwise stores the address of
 * the hash bucket.  This allows us to be sure we've found the end
 * of the right list.
 * The value stored in the hash bucket has BIT(0) used as a lock bit.
 * This bit must be atomically set beक्रमe any changes are made to
 * the chain.  To aव्योम dereferencing this poपूर्णांकer without clearing
 * the bit first, we use an opaque 'struct rhash_lock_head *' क्रम the
 * poपूर्णांकer stored in the bucket.  This काष्ठा needs to be defined so
 * that rcu_dereference() works on it, but it has no content so a
 * cast is needed क्रम it to be useful.  This ensures it isn't
 * used by mistake with clearing the lock bit first.
 */
काष्ठा rhash_lock_head अणुपूर्ण;

/* Maximum chain length beक्रमe rehash
 *
 * The maximum (not average) chain length grows with the size of the hash
 * table, at a rate of (log N)/(log log N).
 *
 * The value of 16 is selected so that even अगर the hash table grew to
 * 2^32 you would not expect the maximum chain length to exceed it
 * unless we are under attack (or extremely unlucky).
 *
 * As this limit is only to detect attacks, we करोn't need to set it to a
 * lower value as you'd need the chain length to vastly exceed 16 to have
 * any real effect on the प्रणाली.
 */
#घोषणा RHT_ELASTICITY	16u

/**
 * काष्ठा bucket_table - Table of hash buckets
 * @size: Number of hash buckets
 * @nest: Number of bits of first-level nested table.
 * @rehash: Current bucket being rehashed
 * @hash_rnd: Ranकरोm seed to fold पूर्णांकo hash
 * @walkers: List of active walkers
 * @rcu: RCU काष्ठाure क्रम मुक्तing the table
 * @future_tbl: Table under स्थिरruction during rehashing
 * @ntbl: Nested table used when out of memory.
 * @buckets: size * hash buckets
 */
काष्ठा bucket_table अणु
	अचिन्हित पूर्णांक		size;
	अचिन्हित पूर्णांक		nest;
	u32			hash_rnd;
	काष्ठा list_head	walkers;
	काष्ठा rcu_head		rcu;

	काष्ठा bucket_table __rcu *future_tbl;

	काष्ठा lockdep_map	dep_map;

	काष्ठा rhash_lock_head __rcu *buckets[] ____cacheline_aligned_in_smp;
पूर्ण;

/*
 * शून्यS_MARKER() expects a hash value with the low
 * bits mostly likely to be signअगरicant, and it discards
 * the msb.
 * We give it an address, in which the bottom bit is
 * always 0, and the msb might be signअगरicant.
 * So we shअगरt the address करोwn one bit to align with
 * expectations and aव्योम losing a signअगरicant bit.
 *
 * We never store the शून्यS_MARKER in the hash table
 * itself as we need the lsb क्रम locking.
 * Instead we store a शून्य
 */
#घोषणा	RHT_शून्यS_MARKER(ptr)	\
	((व्योम *)शून्यS_MARKER(((अचिन्हित दीर्घ) (ptr)) >> 1))
#घोषणा INIT_RHT_शून्यS_HEAD(ptr)	\
	((ptr) = शून्य)

अटल अंतरभूत bool rht_is_a_nulls(स्थिर काष्ठा rhash_head *ptr)
अणु
	वापस ((अचिन्हित दीर्घ) ptr & 1);
पूर्ण

अटल अंतरभूत व्योम *rht_obj(स्थिर काष्ठा rhashtable *ht,
			    स्थिर काष्ठा rhash_head *he)
अणु
	वापस (अक्षर *)he - ht->p.head_offset;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rht_bucket_index(स्थिर काष्ठा bucket_table *tbl,
					    अचिन्हित पूर्णांक hash)
अणु
	वापस hash & (tbl->size - 1);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rht_key_get_hash(काष्ठा rhashtable *ht,
	स्थिर व्योम *key, स्थिर काष्ठा rhashtable_params params,
	अचिन्हित पूर्णांक hash_rnd)
अणु
	अचिन्हित पूर्णांक hash;

	/* params must be equal to ht->p अगर it isn't स्थिरant. */
	अगर (!__builtin_स्थिरant_p(params.key_len))
		hash = ht->p.hashfn(key, ht->key_len, hash_rnd);
	अन्यथा अगर (params.key_len) अणु
		अचिन्हित पूर्णांक key_len = params.key_len;

		अगर (params.hashfn)
			hash = params.hashfn(key, key_len, hash_rnd);
		अन्यथा अगर (key_len & (माप(u32) - 1))
			hash = jhash(key, key_len, hash_rnd);
		अन्यथा
			hash = jhash2(key, key_len / माप(u32), hash_rnd);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक key_len = ht->p.key_len;

		अगर (params.hashfn)
			hash = params.hashfn(key, key_len, hash_rnd);
		अन्यथा
			hash = jhash(key, key_len, hash_rnd);
	पूर्ण

	वापस hash;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rht_key_hashfn(
	काष्ठा rhashtable *ht, स्थिर काष्ठा bucket_table *tbl,
	स्थिर व्योम *key, स्थिर काष्ठा rhashtable_params params)
अणु
	अचिन्हित पूर्णांक hash = rht_key_get_hash(ht, key, params, tbl->hash_rnd);

	वापस rht_bucket_index(tbl, hash);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rht_head_hashfn(
	काष्ठा rhashtable *ht, स्थिर काष्ठा bucket_table *tbl,
	स्थिर काष्ठा rhash_head *he, स्थिर काष्ठा rhashtable_params params)
अणु
	स्थिर अक्षर *ptr = rht_obj(ht, he);

	वापस likely(params.obj_hashfn) ?
	       rht_bucket_index(tbl, params.obj_hashfn(ptr, params.key_len ?:
							    ht->p.key_len,
						       tbl->hash_rnd)) :
	       rht_key_hashfn(ht, tbl, ptr + params.key_offset, params);
पूर्ण

/**
 * rht_grow_above_75 - वापसs true अगर nelems > 0.75 * table-size
 * @ht:		hash table
 * @tbl:	current table
 */
अटल अंतरभूत bool rht_grow_above_75(स्थिर काष्ठा rhashtable *ht,
				     स्थिर काष्ठा bucket_table *tbl)
अणु
	/* Expand table when exceeding 75% load */
	वापस atomic_पढ़ो(&ht->nelems) > (tbl->size / 4 * 3) &&
	       (!ht->p.max_size || tbl->size < ht->p.max_size);
पूर्ण

/**
 * rht_shrink_below_30 - वापसs true अगर nelems < 0.3 * table-size
 * @ht:		hash table
 * @tbl:	current table
 */
अटल अंतरभूत bool rht_shrink_below_30(स्थिर काष्ठा rhashtable *ht,
				       स्थिर काष्ठा bucket_table *tbl)
अणु
	/* Shrink table beneath 30% load */
	वापस atomic_पढ़ो(&ht->nelems) < (tbl->size * 3 / 10) &&
	       tbl->size > ht->p.min_size;
पूर्ण

/**
 * rht_grow_above_100 - वापसs true अगर nelems > table-size
 * @ht:		hash table
 * @tbl:	current table
 */
अटल अंतरभूत bool rht_grow_above_100(स्थिर काष्ठा rhashtable *ht,
				      स्थिर काष्ठा bucket_table *tbl)
अणु
	वापस atomic_पढ़ो(&ht->nelems) > tbl->size &&
		(!ht->p.max_size || tbl->size < ht->p.max_size);
पूर्ण

/**
 * rht_grow_above_max - वापसs true अगर table is above maximum
 * @ht:		hash table
 * @tbl:	current table
 */
अटल अंतरभूत bool rht_grow_above_max(स्थिर काष्ठा rhashtable *ht,
				      स्थिर काष्ठा bucket_table *tbl)
अणु
	वापस atomic_पढ़ो(&ht->nelems) >= ht->max_elems;
पूर्ण

#अगर_घोषित CONFIG_PROVE_LOCKING
पूर्णांक lockdep_rht_mutex_is_held(काष्ठा rhashtable *ht);
पूर्णांक lockdep_rht_bucket_is_held(स्थिर काष्ठा bucket_table *tbl, u32 hash);
#अन्यथा
अटल अंतरभूत पूर्णांक lockdep_rht_mutex_is_held(काष्ठा rhashtable *ht)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक lockdep_rht_bucket_is_held(स्थिर काष्ठा bucket_table *tbl,
					     u32 hash)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROVE_LOCKING */

व्योम *rhashtable_insert_slow(काष्ठा rhashtable *ht, स्थिर व्योम *key,
			     काष्ठा rhash_head *obj);

व्योम rhashtable_walk_enter(काष्ठा rhashtable *ht,
			   काष्ठा rhashtable_iter *iter);
व्योम rhashtable_walk_निकास(काष्ठा rhashtable_iter *iter);
पूर्णांक rhashtable_walk_start_check(काष्ठा rhashtable_iter *iter) __acquires(RCU);

अटल अंतरभूत व्योम rhashtable_walk_start(काष्ठा rhashtable_iter *iter)
अणु
	(व्योम)rhashtable_walk_start_check(iter);
पूर्ण

व्योम *rhashtable_walk_next(काष्ठा rhashtable_iter *iter);
व्योम *rhashtable_walk_peek(काष्ठा rhashtable_iter *iter);
व्योम rhashtable_walk_stop(काष्ठा rhashtable_iter *iter) __releases(RCU);

व्योम rhashtable_मुक्त_and_destroy(काष्ठा rhashtable *ht,
				 व्योम (*मुक्त_fn)(व्योम *ptr, व्योम *arg),
				 व्योम *arg);
व्योम rhashtable_destroy(काष्ठा rhashtable *ht);

काष्ठा rhash_lock_head __rcu **rht_bucket_nested(
	स्थिर काष्ठा bucket_table *tbl, अचिन्हित पूर्णांक hash);
काष्ठा rhash_lock_head __rcu **__rht_bucket_nested(
	स्थिर काष्ठा bucket_table *tbl, अचिन्हित पूर्णांक hash);
काष्ठा rhash_lock_head __rcu **rht_bucket_nested_insert(
	काष्ठा rhashtable *ht, काष्ठा bucket_table *tbl, अचिन्हित पूर्णांक hash);

#घोषणा rht_dereference(p, ht) \
	rcu_dereference_रक्षित(p, lockdep_rht_mutex_is_held(ht))

#घोषणा rht_dereference_rcu(p, ht) \
	rcu_dereference_check(p, lockdep_rht_mutex_is_held(ht))

#घोषणा rht_dereference_bucket(p, tbl, hash) \
	rcu_dereference_रक्षित(p, lockdep_rht_bucket_is_held(tbl, hash))

#घोषणा rht_dereference_bucket_rcu(p, tbl, hash) \
	rcu_dereference_check(p, lockdep_rht_bucket_is_held(tbl, hash))

#घोषणा rht_entry(tpos, pos, member) \
	(अणु tpos = container_of(pos, typeof(*tpos), member); 1; पूर्ण)

अटल अंतरभूत काष्ठा rhash_lock_head __rcu *स्थिर *rht_bucket(
	स्थिर काष्ठा bucket_table *tbl, अचिन्हित पूर्णांक hash)
अणु
	वापस unlikely(tbl->nest) ? rht_bucket_nested(tbl, hash) :
				     &tbl->buckets[hash];
पूर्ण

अटल अंतरभूत काष्ठा rhash_lock_head __rcu **rht_bucket_var(
	काष्ठा bucket_table *tbl, अचिन्हित पूर्णांक hash)
अणु
	वापस unlikely(tbl->nest) ? __rht_bucket_nested(tbl, hash) :
				     &tbl->buckets[hash];
पूर्ण

अटल अंतरभूत काष्ठा rhash_lock_head __rcu **rht_bucket_insert(
	काष्ठा rhashtable *ht, काष्ठा bucket_table *tbl, अचिन्हित पूर्णांक hash)
अणु
	वापस unlikely(tbl->nest) ? rht_bucket_nested_insert(ht, tbl, hash) :
				     &tbl->buckets[hash];
पूर्ण

/*
 * We lock a bucket by setting BIT(0) in the poपूर्णांकer - this is always
 * zero in real poपूर्णांकers.  The शून्यS mark is never stored in the bucket,
 * rather we store शून्य अगर the bucket is empty.
 * bit_spin_locks करो not handle contention well, but the whole poपूर्णांक
 * of the hashtable design is to achieve minimum per-bucket contention.
 * A nested hash table might not have a bucket poपूर्णांकer.  In that हाल
 * we cannot get a lock.  For हटाओ and replace the bucket cannot be
 * पूर्णांकeresting and करोesn't need locking.
 * For insert we allocate the bucket अगर this is the last bucket_table,
 * and then take the lock.
 * Someबार we unlock a bucket by writing a new poपूर्णांकer there.  In that
 * हाल we करोn't need to unlock, but we करो need to reset state such as
 * local_bh. For that we have rht_assign_unlock().  As rcu_assign_poपूर्णांकer()
 * provides the same release semantics that bit_spin_unlock() provides,
 * this is safe.
 * When we ग_लिखो to a bucket without unlocking, we use rht_assign_locked().
 */

अटल अंतरभूत व्योम rht_lock(काष्ठा bucket_table *tbl,
			    काष्ठा rhash_lock_head __rcu **bkt)
अणु
	local_bh_disable();
	bit_spin_lock(0, (अचिन्हित दीर्घ *)bkt);
	lock_map_acquire(&tbl->dep_map);
पूर्ण

अटल अंतरभूत व्योम rht_lock_nested(काष्ठा bucket_table *tbl,
				   काष्ठा rhash_lock_head __rcu **bucket,
				   अचिन्हित पूर्णांक subclass)
अणु
	local_bh_disable();
	bit_spin_lock(0, (अचिन्हित दीर्घ *)bucket);
	lock_acquire_exclusive(&tbl->dep_map, subclass, 0, शून्य, _THIS_IP_);
पूर्ण

अटल अंतरभूत व्योम rht_unlock(काष्ठा bucket_table *tbl,
			      काष्ठा rhash_lock_head __rcu **bkt)
अणु
	lock_map_release(&tbl->dep_map);
	bit_spin_unlock(0, (अचिन्हित दीर्घ *)bkt);
	local_bh_enable();
पूर्ण

अटल अंतरभूत काष्ठा rhash_head *__rht_ptr(
	काष्ठा rhash_lock_head *p, काष्ठा rhash_lock_head __rcu *स्थिर *bkt)
अणु
	वापस (काष्ठा rhash_head *)
		((अचिन्हित दीर्घ)p & ~BIT(0) ?:
		 (अचिन्हित दीर्घ)RHT_शून्यS_MARKER(bkt));
पूर्ण

/*
 * Where 'bkt' is a bucket and might be locked:
 *   rht_ptr_rcu() dereferences that poपूर्णांकer and clears the lock bit.
 *   rht_ptr() dereferences in a context where the bucket is locked.
 *   rht_ptr_exclusive() dereferences in a context where exclusive
 *            access is guaranteed, such as when destroying the table.
 */
अटल अंतरभूत काष्ठा rhash_head *rht_ptr_rcu(
	काष्ठा rhash_lock_head __rcu *स्थिर *bkt)
अणु
	वापस __rht_ptr(rcu_dereference(*bkt), bkt);
पूर्ण

अटल अंतरभूत काष्ठा rhash_head *rht_ptr(
	काष्ठा rhash_lock_head __rcu *स्थिर *bkt,
	काष्ठा bucket_table *tbl,
	अचिन्हित पूर्णांक hash)
अणु
	वापस __rht_ptr(rht_dereference_bucket(*bkt, tbl, hash), bkt);
पूर्ण

अटल अंतरभूत काष्ठा rhash_head *rht_ptr_exclusive(
	काष्ठा rhash_lock_head __rcu *स्थिर *bkt)
अणु
	वापस __rht_ptr(rcu_dereference_रक्षित(*bkt, 1), bkt);
पूर्ण

अटल अंतरभूत व्योम rht_assign_locked(काष्ठा rhash_lock_head __rcu **bkt,
				     काष्ठा rhash_head *obj)
अणु
	अगर (rht_is_a_nulls(obj))
		obj = शून्य;
	rcu_assign_poपूर्णांकer(*bkt, (व्योम *)((अचिन्हित दीर्घ)obj | BIT(0)));
पूर्ण

अटल अंतरभूत व्योम rht_assign_unlock(काष्ठा bucket_table *tbl,
				     काष्ठा rhash_lock_head __rcu **bkt,
				     काष्ठा rhash_head *obj)
अणु
	अगर (rht_is_a_nulls(obj))
		obj = शून्य;
	lock_map_release(&tbl->dep_map);
	rcu_assign_poपूर्णांकer(*bkt, (व्योम *)obj);
	preempt_enable();
	__release(bitlock);
	local_bh_enable();
पूर्ण

/**
 * rht_क्रम_each_from - iterate over hash chain from given head
 * @pos:	the &काष्ठा rhash_head to use as a loop cursor.
 * @head:	the &काष्ठा rhash_head to start from
 * @tbl:	the &काष्ठा bucket_table
 * @hash:	the hash value / bucket index
 */
#घोषणा rht_क्रम_each_from(pos, head, tbl, hash) \
	क्रम (pos = head;			\
	     !rht_is_a_nulls(pos);		\
	     pos = rht_dereference_bucket((pos)->next, tbl, hash))

/**
 * rht_क्रम_each - iterate over hash chain
 * @pos:	the &काष्ठा rhash_head to use as a loop cursor.
 * @tbl:	the &काष्ठा bucket_table
 * @hash:	the hash value / bucket index
 */
#घोषणा rht_क्रम_each(pos, tbl, hash) \
	rht_क्रम_each_from(pos, rht_ptr(rht_bucket(tbl, hash), tbl, hash),  \
			  tbl, hash)

/**
 * rht_क्रम_each_entry_from - iterate over hash chain from given head
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा rhash_head to use as a loop cursor.
 * @head:	the &काष्ठा rhash_head to start from
 * @tbl:	the &काष्ठा bucket_table
 * @hash:	the hash value / bucket index
 * @member:	name of the &काष्ठा rhash_head within the hashable काष्ठा.
 */
#घोषणा rht_क्रम_each_entry_from(tpos, pos, head, tbl, hash, member)	\
	क्रम (pos = head;						\
	     (!rht_is_a_nulls(pos)) && rht_entry(tpos, pos, member);	\
	     pos = rht_dereference_bucket((pos)->next, tbl, hash))

/**
 * rht_क्रम_each_entry - iterate over hash chain of given type
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा rhash_head to use as a loop cursor.
 * @tbl:	the &काष्ठा bucket_table
 * @hash:	the hash value / bucket index
 * @member:	name of the &काष्ठा rhash_head within the hashable काष्ठा.
 */
#घोषणा rht_क्रम_each_entry(tpos, pos, tbl, hash, member)		\
	rht_क्रम_each_entry_from(tpos, pos,				\
				rht_ptr(rht_bucket(tbl, hash), tbl, hash), \
				tbl, hash, member)

/**
 * rht_क्रम_each_entry_safe - safely iterate over hash chain of given type
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा rhash_head to use as a loop cursor.
 * @next:	the &काष्ठा rhash_head to use as next in loop cursor.
 * @tbl:	the &काष्ठा bucket_table
 * @hash:	the hash value / bucket index
 * @member:	name of the &काष्ठा rhash_head within the hashable काष्ठा.
 *
 * This hash chain list-traversal primitive allows क्रम the looped code to
 * हटाओ the loop cursor from the list.
 */
#घोषणा rht_क्रम_each_entry_safe(tpos, pos, next, tbl, hash, member)	      \
	क्रम (pos = rht_ptr(rht_bucket(tbl, hash), tbl, hash),		      \
	     next = !rht_is_a_nulls(pos) ?				      \
		       rht_dereference_bucket(pos->next, tbl, hash) : शून्य;   \
	     (!rht_is_a_nulls(pos)) && rht_entry(tpos, pos, member);	      \
	     pos = next,						      \
	     next = !rht_is_a_nulls(pos) ?				      \
		       rht_dereference_bucket(pos->next, tbl, hash) : शून्य)

/**
 * rht_क्रम_each_rcu_from - iterate over rcu hash chain from given head
 * @pos:	the &काष्ठा rhash_head to use as a loop cursor.
 * @head:	the &काष्ठा rhash_head to start from
 * @tbl:	the &काष्ठा bucket_table
 * @hash:	the hash value / bucket index
 *
 * This hash chain list-traversal primitive may safely run concurrently with
 * the _rcu mutation primitives such as rhashtable_insert() as दीर्घ as the
 * traversal is guarded by rcu_पढ़ो_lock().
 */
#घोषणा rht_क्रम_each_rcu_from(pos, head, tbl, hash)			\
	क्रम ((अणुbarrier(); पूर्ण),						\
	     pos = head;						\
	     !rht_is_a_nulls(pos);					\
	     pos = rcu_dereference_raw(pos->next))

/**
 * rht_क्रम_each_rcu - iterate over rcu hash chain
 * @pos:	the &काष्ठा rhash_head to use as a loop cursor.
 * @tbl:	the &काष्ठा bucket_table
 * @hash:	the hash value / bucket index
 *
 * This hash chain list-traversal primitive may safely run concurrently with
 * the _rcu mutation primitives such as rhashtable_insert() as दीर्घ as the
 * traversal is guarded by rcu_पढ़ो_lock().
 */
#घोषणा rht_क्रम_each_rcu(pos, tbl, hash)			\
	क्रम ((अणुbarrier(); पूर्ण),					\
	     pos = rht_ptr_rcu(rht_bucket(tbl, hash));		\
	     !rht_is_a_nulls(pos);				\
	     pos = rcu_dereference_raw(pos->next))

/**
 * rht_क्रम_each_entry_rcu_from - iterated over rcu hash chain from given head
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा rhash_head to use as a loop cursor.
 * @head:	the &काष्ठा rhash_head to start from
 * @tbl:	the &काष्ठा bucket_table
 * @hash:	the hash value / bucket index
 * @member:	name of the &काष्ठा rhash_head within the hashable काष्ठा.
 *
 * This hash chain list-traversal primitive may safely run concurrently with
 * the _rcu mutation primitives such as rhashtable_insert() as दीर्घ as the
 * traversal is guarded by rcu_पढ़ो_lock().
 */
#घोषणा rht_क्रम_each_entry_rcu_from(tpos, pos, head, tbl, hash, member) \
	क्रम ((अणुbarrier(); पूर्ण),						    \
	     pos = head;						    \
	     (!rht_is_a_nulls(pos)) && rht_entry(tpos, pos, member);	    \
	     pos = rht_dereference_bucket_rcu(pos->next, tbl, hash))

/**
 * rht_क्रम_each_entry_rcu - iterate over rcu hash chain of given type
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा rhash_head to use as a loop cursor.
 * @tbl:	the &काष्ठा bucket_table
 * @hash:	the hash value / bucket index
 * @member:	name of the &काष्ठा rhash_head within the hashable काष्ठा.
 *
 * This hash chain list-traversal primitive may safely run concurrently with
 * the _rcu mutation primitives such as rhashtable_insert() as दीर्घ as the
 * traversal is guarded by rcu_पढ़ो_lock().
 */
#घोषणा rht_क्रम_each_entry_rcu(tpos, pos, tbl, hash, member)		   \
	rht_क्रम_each_entry_rcu_from(tpos, pos,				   \
				    rht_ptr_rcu(rht_bucket(tbl, hash)),	   \
				    tbl, hash, member)

/**
 * rhl_क्रम_each_rcu - iterate over rcu hash table list
 * @pos:	the &काष्ठा rlist_head to use as a loop cursor.
 * @list:	the head of the list
 *
 * This hash chain list-traversal primitive should be used on the
 * list वापसed by rhltable_lookup.
 */
#घोषणा rhl_क्रम_each_rcu(pos, list)					\
	क्रम (pos = list; pos; pos = rcu_dereference_raw(pos->next))

/**
 * rhl_क्रम_each_entry_rcu - iterate over rcu hash table list of given type
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &काष्ठा rlist_head to use as a loop cursor.
 * @list:	the head of the list
 * @member:	name of the &काष्ठा rlist_head within the hashable काष्ठा.
 *
 * This hash chain list-traversal primitive should be used on the
 * list वापसed by rhltable_lookup.
 */
#घोषणा rhl_क्रम_each_entry_rcu(tpos, pos, list, member)			\
	क्रम (pos = list; pos && rht_entry(tpos, pos, member);		\
	     pos = rcu_dereference_raw(pos->next))

अटल अंतरभूत पूर्णांक rhashtable_compare(काष्ठा rhashtable_compare_arg *arg,
				     स्थिर व्योम *obj)
अणु
	काष्ठा rhashtable *ht = arg->ht;
	स्थिर अक्षर *ptr = obj;

	वापस स_भेद(ptr + ht->p.key_offset, arg->key, ht->p.key_len);
पूर्ण

/* Internal function, करो not use. */
अटल अंतरभूत काष्ठा rhash_head *__rhashtable_lookup(
	काष्ठा rhashtable *ht, स्थिर व्योम *key,
	स्थिर काष्ठा rhashtable_params params)
अणु
	काष्ठा rhashtable_compare_arg arg = अणु
		.ht = ht,
		.key = key,
	पूर्ण;
	काष्ठा rhash_lock_head __rcu *स्थिर *bkt;
	काष्ठा bucket_table *tbl;
	काष्ठा rhash_head *he;
	अचिन्हित पूर्णांक hash;

	tbl = rht_dereference_rcu(ht->tbl, ht);
restart:
	hash = rht_key_hashfn(ht, tbl, key, params);
	bkt = rht_bucket(tbl, hash);
	करो अणु
		rht_क्रम_each_rcu_from(he, rht_ptr_rcu(bkt), tbl, hash) अणु
			अगर (params.obj_cmpfn ?
			    params.obj_cmpfn(&arg, rht_obj(ht, he)) :
			    rhashtable_compare(&arg, rht_obj(ht, he)))
				जारी;
			वापस he;
		पूर्ण
		/* An object might have been moved to a dअगरferent hash chain,
		 * जबतक we walk aदीर्घ it - better check and retry.
		 */
	पूर्ण जबतक (he != RHT_शून्यS_MARKER(bkt));

	/* Ensure we see any new tables. */
	smp_rmb();

	tbl = rht_dereference_rcu(tbl->future_tbl, ht);
	अगर (unlikely(tbl))
		जाओ restart;

	वापस शून्य;
पूर्ण

/**
 * rhashtable_lookup - search hash table
 * @ht:		hash table
 * @key:	the poपूर्णांकer to the key
 * @params:	hash table parameters
 *
 * Computes the hash value क्रम the key and traverses the bucket chain looking
 * क्रम a entry with an identical key. The first matching entry is वापसed.
 *
 * This must only be called under the RCU पढ़ो lock.
 *
 * Returns the first entry on which the compare function वापसed true.
 */
अटल अंतरभूत व्योम *rhashtable_lookup(
	काष्ठा rhashtable *ht, स्थिर व्योम *key,
	स्थिर काष्ठा rhashtable_params params)
अणु
	काष्ठा rhash_head *he = __rhashtable_lookup(ht, key, params);

	वापस he ? rht_obj(ht, he) : शून्य;
पूर्ण

/**
 * rhashtable_lookup_fast - search hash table, without RCU पढ़ो lock
 * @ht:		hash table
 * @key:	the poपूर्णांकer to the key
 * @params:	hash table parameters
 *
 * Computes the hash value क्रम the key and traverses the bucket chain looking
 * क्रम a entry with an identical key. The first matching entry is वापसed.
 *
 * Only use this function when you have other mechanisms guaranteeing
 * that the object won't go away after the RCU पढ़ो lock is released.
 *
 * Returns the first entry on which the compare function वापसed true.
 */
अटल अंतरभूत व्योम *rhashtable_lookup_fast(
	काष्ठा rhashtable *ht, स्थिर व्योम *key,
	स्थिर काष्ठा rhashtable_params params)
अणु
	व्योम *obj;

	rcu_पढ़ो_lock();
	obj = rhashtable_lookup(ht, key, params);
	rcu_पढ़ो_unlock();

	वापस obj;
पूर्ण

/**
 * rhltable_lookup - search hash list table
 * @hlt:	hash table
 * @key:	the poपूर्णांकer to the key
 * @params:	hash table parameters
 *
 * Computes the hash value क्रम the key and traverses the bucket chain looking
 * क्रम a entry with an identical key.  All matching entries are वापसed
 * in a list.
 *
 * This must only be called under the RCU पढ़ो lock.
 *
 * Returns the list of entries that match the given key.
 */
अटल अंतरभूत काष्ठा rhlist_head *rhltable_lookup(
	काष्ठा rhltable *hlt, स्थिर व्योम *key,
	स्थिर काष्ठा rhashtable_params params)
अणु
	काष्ठा rhash_head *he = __rhashtable_lookup(&hlt->ht, key, params);

	वापस he ? container_of(he, काष्ठा rhlist_head, rhead) : शून्य;
पूर्ण

/* Internal function, please use rhashtable_insert_fast() instead. This
 * function वापसs the existing element alपढ़ोy in hashes in there is a clash,
 * otherwise it वापसs an error via ERR_PTR().
 */
अटल अंतरभूत व्योम *__rhashtable_insert_fast(
	काष्ठा rhashtable *ht, स्थिर व्योम *key, काष्ठा rhash_head *obj,
	स्थिर काष्ठा rhashtable_params params, bool rhlist)
अणु
	काष्ठा rhashtable_compare_arg arg = अणु
		.ht = ht,
		.key = key,
	पूर्ण;
	काष्ठा rhash_lock_head __rcu **bkt;
	काष्ठा rhash_head __rcu **pprev;
	काष्ठा bucket_table *tbl;
	काष्ठा rhash_head *head;
	अचिन्हित पूर्णांक hash;
	पूर्णांक elasticity;
	व्योम *data;

	rcu_पढ़ो_lock();

	tbl = rht_dereference_rcu(ht->tbl, ht);
	hash = rht_head_hashfn(ht, tbl, obj, params);
	elasticity = RHT_ELASTICITY;
	bkt = rht_bucket_insert(ht, tbl, hash);
	data = ERR_PTR(-ENOMEM);
	अगर (!bkt)
		जाओ out;
	pprev = शून्य;
	rht_lock(tbl, bkt);

	अगर (unlikely(rcu_access_poपूर्णांकer(tbl->future_tbl))) अणु
slow_path:
		rht_unlock(tbl, bkt);
		rcu_पढ़ो_unlock();
		वापस rhashtable_insert_slow(ht, key, obj);
	पूर्ण

	rht_क्रम_each_from(head, rht_ptr(bkt, tbl, hash), tbl, hash) अणु
		काष्ठा rhlist_head *plist;
		काष्ठा rhlist_head *list;

		elasticity--;
		अगर (!key ||
		    (params.obj_cmpfn ?
		     params.obj_cmpfn(&arg, rht_obj(ht, head)) :
		     rhashtable_compare(&arg, rht_obj(ht, head)))) अणु
			pprev = &head->next;
			जारी;
		पूर्ण

		data = rht_obj(ht, head);

		अगर (!rhlist)
			जाओ out_unlock;


		list = container_of(obj, काष्ठा rhlist_head, rhead);
		plist = container_of(head, काष्ठा rhlist_head, rhead);

		RCU_INIT_POINTER(list->next, plist);
		head = rht_dereference_bucket(head->next, tbl, hash);
		RCU_INIT_POINTER(list->rhead.next, head);
		अगर (pprev) अणु
			rcu_assign_poपूर्णांकer(*pprev, obj);
			rht_unlock(tbl, bkt);
		पूर्ण अन्यथा
			rht_assign_unlock(tbl, bkt, obj);
		data = शून्य;
		जाओ out;
	पूर्ण

	अगर (elasticity <= 0)
		जाओ slow_path;

	data = ERR_PTR(-E2BIG);
	अगर (unlikely(rht_grow_above_max(ht, tbl)))
		जाओ out_unlock;

	अगर (unlikely(rht_grow_above_100(ht, tbl)))
		जाओ slow_path;

	/* Inserting at head of list makes unlocking मुक्त. */
	head = rht_ptr(bkt, tbl, hash);

	RCU_INIT_POINTER(obj->next, head);
	अगर (rhlist) अणु
		काष्ठा rhlist_head *list;

		list = container_of(obj, काष्ठा rhlist_head, rhead);
		RCU_INIT_POINTER(list->next, शून्य);
	पूर्ण

	atomic_inc(&ht->nelems);
	rht_assign_unlock(tbl, bkt, obj);

	अगर (rht_grow_above_75(ht, tbl))
		schedule_work(&ht->run_work);

	data = शून्य;
out:
	rcu_पढ़ो_unlock();

	वापस data;

out_unlock:
	rht_unlock(tbl, bkt);
	जाओ out;
पूर्ण

/**
 * rhashtable_insert_fast - insert object पूर्णांकo hash table
 * @ht:		hash table
 * @obj:	poपूर्णांकer to hash head inside object
 * @params:	hash table parameters
 *
 * Will take the per bucket bitlock to protect against mutual mutations
 * on the same bucket. Multiple insertions may occur in parallel unless
 * they map to the same bucket.
 *
 * It is safe to call this function from atomic context.
 *
 * Will trigger an स्वतःmatic deferred table resizing अगर residency in the
 * table grows beyond 70%.
 */
अटल अंतरभूत पूर्णांक rhashtable_insert_fast(
	काष्ठा rhashtable *ht, काष्ठा rhash_head *obj,
	स्थिर काष्ठा rhashtable_params params)
अणु
	व्योम *ret;

	ret = __rhashtable_insert_fast(ht, शून्य, obj, params, false);
	अगर (IS_ERR(ret))
		वापस PTR_ERR(ret);

	वापस ret == शून्य ? 0 : -EEXIST;
पूर्ण

/**
 * rhltable_insert_key - insert object पूर्णांकo hash list table
 * @hlt:	hash list table
 * @key:	the poपूर्णांकer to the key
 * @list:	poपूर्णांकer to hash list head inside object
 * @params:	hash table parameters
 *
 * Will take the per bucket bitlock to protect against mutual mutations
 * on the same bucket. Multiple insertions may occur in parallel unless
 * they map to the same bucket.
 *
 * It is safe to call this function from atomic context.
 *
 * Will trigger an स्वतःmatic deferred table resizing अगर residency in the
 * table grows beyond 70%.
 */
अटल अंतरभूत पूर्णांक rhltable_insert_key(
	काष्ठा rhltable *hlt, स्थिर व्योम *key, काष्ठा rhlist_head *list,
	स्थिर काष्ठा rhashtable_params params)
अणु
	वापस PTR_ERR(__rhashtable_insert_fast(&hlt->ht, key, &list->rhead,
						params, true));
पूर्ण

/**
 * rhltable_insert - insert object पूर्णांकo hash list table
 * @hlt:	hash list table
 * @list:	poपूर्णांकer to hash list head inside object
 * @params:	hash table parameters
 *
 * Will take the per bucket bitlock to protect against mutual mutations
 * on the same bucket. Multiple insertions may occur in parallel unless
 * they map to the same bucket.
 *
 * It is safe to call this function from atomic context.
 *
 * Will trigger an स्वतःmatic deferred table resizing अगर residency in the
 * table grows beyond 70%.
 */
अटल अंतरभूत पूर्णांक rhltable_insert(
	काष्ठा rhltable *hlt, काष्ठा rhlist_head *list,
	स्थिर काष्ठा rhashtable_params params)
अणु
	स्थिर अक्षर *key = rht_obj(&hlt->ht, &list->rhead);

	key += params.key_offset;

	वापस rhltable_insert_key(hlt, key, list, params);
पूर्ण

/**
 * rhashtable_lookup_insert_fast - lookup and insert object पूर्णांकo hash table
 * @ht:		hash table
 * @obj:	poपूर्णांकer to hash head inside object
 * @params:	hash table parameters
 *
 * This lookup function may only be used क्रम fixed key hash table (key_len
 * parameter set). It will BUG() अगर used inappropriately.
 *
 * It is safe to call this function from atomic context.
 *
 * Will trigger an स्वतःmatic deferred table resizing अगर residency in the
 * table grows beyond 70%.
 */
अटल अंतरभूत पूर्णांक rhashtable_lookup_insert_fast(
	काष्ठा rhashtable *ht, काष्ठा rhash_head *obj,
	स्थिर काष्ठा rhashtable_params params)
अणु
	स्थिर अक्षर *key = rht_obj(ht, obj);
	व्योम *ret;

	BUG_ON(ht->p.obj_hashfn);

	ret = __rhashtable_insert_fast(ht, key + ht->p.key_offset, obj, params,
				       false);
	अगर (IS_ERR(ret))
		वापस PTR_ERR(ret);

	वापस ret == शून्य ? 0 : -EEXIST;
पूर्ण

/**
 * rhashtable_lookup_get_insert_fast - lookup and insert object पूर्णांकo hash table
 * @ht:		hash table
 * @obj:	poपूर्णांकer to hash head inside object
 * @params:	hash table parameters
 *
 * Just like rhashtable_lookup_insert_fast(), but this function वापसs the
 * object अगर it exists, शून्य अगर it did not and the insertion was successful,
 * and an ERR_PTR otherwise.
 */
अटल अंतरभूत व्योम *rhashtable_lookup_get_insert_fast(
	काष्ठा rhashtable *ht, काष्ठा rhash_head *obj,
	स्थिर काष्ठा rhashtable_params params)
अणु
	स्थिर अक्षर *key = rht_obj(ht, obj);

	BUG_ON(ht->p.obj_hashfn);

	वापस __rhashtable_insert_fast(ht, key + ht->p.key_offset, obj, params,
					false);
पूर्ण

/**
 * rhashtable_lookup_insert_key - search and insert object to hash table
 *				  with explicit key
 * @ht:		hash table
 * @key:	key
 * @obj:	poपूर्णांकer to hash head inside object
 * @params:	hash table parameters
 *
 * Lookups may occur in parallel with hashtable mutations and resizing.
 *
 * Will trigger an स्वतःmatic deferred table resizing अगर residency in the
 * table grows beyond 70%.
 *
 * Returns zero on success.
 */
अटल अंतरभूत पूर्णांक rhashtable_lookup_insert_key(
	काष्ठा rhashtable *ht, स्थिर व्योम *key, काष्ठा rhash_head *obj,
	स्थिर काष्ठा rhashtable_params params)
अणु
	व्योम *ret;

	BUG_ON(!ht->p.obj_hashfn || !key);

	ret = __rhashtable_insert_fast(ht, key, obj, params, false);
	अगर (IS_ERR(ret))
		वापस PTR_ERR(ret);

	वापस ret == शून्य ? 0 : -EEXIST;
पूर्ण

/**
 * rhashtable_lookup_get_insert_key - lookup and insert object पूर्णांकo hash table
 * @ht:		hash table
 * @key:	key
 * @obj:	poपूर्णांकer to hash head inside object
 * @params:	hash table parameters
 *
 * Just like rhashtable_lookup_insert_key(), but this function वापसs the
 * object अगर it exists, शून्य अगर it करोes not and the insertion was successful,
 * and an ERR_PTR otherwise.
 */
अटल अंतरभूत व्योम *rhashtable_lookup_get_insert_key(
	काष्ठा rhashtable *ht, स्थिर व्योम *key, काष्ठा rhash_head *obj,
	स्थिर काष्ठा rhashtable_params params)
अणु
	BUG_ON(!ht->p.obj_hashfn || !key);

	वापस __rhashtable_insert_fast(ht, key, obj, params, false);
पूर्ण

/* Internal function, please use rhashtable_हटाओ_fast() instead */
अटल अंतरभूत पूर्णांक __rhashtable_हटाओ_fast_one(
	काष्ठा rhashtable *ht, काष्ठा bucket_table *tbl,
	काष्ठा rhash_head *obj, स्थिर काष्ठा rhashtable_params params,
	bool rhlist)
अणु
	काष्ठा rhash_lock_head __rcu **bkt;
	काष्ठा rhash_head __rcu **pprev;
	काष्ठा rhash_head *he;
	अचिन्हित पूर्णांक hash;
	पूर्णांक err = -ENOENT;

	hash = rht_head_hashfn(ht, tbl, obj, params);
	bkt = rht_bucket_var(tbl, hash);
	अगर (!bkt)
		वापस -ENOENT;
	pprev = शून्य;
	rht_lock(tbl, bkt);

	rht_क्रम_each_from(he, rht_ptr(bkt, tbl, hash), tbl, hash) अणु
		काष्ठा rhlist_head *list;

		list = container_of(he, काष्ठा rhlist_head, rhead);

		अगर (he != obj) अणु
			काष्ठा rhlist_head __rcu **lpprev;

			pprev = &he->next;

			अगर (!rhlist)
				जारी;

			करो अणु
				lpprev = &list->next;
				list = rht_dereference_bucket(list->next,
							      tbl, hash);
			पूर्ण जबतक (list && obj != &list->rhead);

			अगर (!list)
				जारी;

			list = rht_dereference_bucket(list->next, tbl, hash);
			RCU_INIT_POINTER(*lpprev, list);
			err = 0;
			अवरोध;
		पूर्ण

		obj = rht_dereference_bucket(obj->next, tbl, hash);
		err = 1;

		अगर (rhlist) अणु
			list = rht_dereference_bucket(list->next, tbl, hash);
			अगर (list) अणु
				RCU_INIT_POINTER(list->rhead.next, obj);
				obj = &list->rhead;
				err = 0;
			पूर्ण
		पूर्ण

		अगर (pprev) अणु
			rcu_assign_poपूर्णांकer(*pprev, obj);
			rht_unlock(tbl, bkt);
		पूर्ण अन्यथा अणु
			rht_assign_unlock(tbl, bkt, obj);
		पूर्ण
		जाओ unlocked;
	पूर्ण

	rht_unlock(tbl, bkt);
unlocked:
	अगर (err > 0) अणु
		atomic_dec(&ht->nelems);
		अगर (unlikely(ht->p.स्वतःmatic_shrinking &&
			     rht_shrink_below_30(ht, tbl)))
			schedule_work(&ht->run_work);
		err = 0;
	पूर्ण

	वापस err;
पूर्ण

/* Internal function, please use rhashtable_हटाओ_fast() instead */
अटल अंतरभूत पूर्णांक __rhashtable_हटाओ_fast(
	काष्ठा rhashtable *ht, काष्ठा rhash_head *obj,
	स्थिर काष्ठा rhashtable_params params, bool rhlist)
अणु
	काष्ठा bucket_table *tbl;
	पूर्णांक err;

	rcu_पढ़ो_lock();

	tbl = rht_dereference_rcu(ht->tbl, ht);

	/* Because we have alपढ़ोy taken (and released) the bucket
	 * lock in old_tbl, अगर we find that future_tbl is not yet
	 * visible then that guarantees the entry to still be in
	 * the old tbl अगर it exists.
	 */
	जबतक ((err = __rhashtable_हटाओ_fast_one(ht, tbl, obj, params,
						   rhlist)) &&
	       (tbl = rht_dereference_rcu(tbl->future_tbl, ht)))
		;

	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

/**
 * rhashtable_हटाओ_fast - हटाओ object from hash table
 * @ht:		hash table
 * @obj:	poपूर्णांकer to hash head inside object
 * @params:	hash table parameters
 *
 * Since the hash chain is single linked, the removal operation needs to
 * walk the bucket chain upon removal. The removal operation is thus
 * considerable slow अगर the hash table is not correctly sized.
 *
 * Will स्वतःmatically shrink the table अगर permitted when residency drops
 * below 30%.
 *
 * Returns zero on success, -ENOENT अगर the entry could not be found.
 */
अटल अंतरभूत पूर्णांक rhashtable_हटाओ_fast(
	काष्ठा rhashtable *ht, काष्ठा rhash_head *obj,
	स्थिर काष्ठा rhashtable_params params)
अणु
	वापस __rhashtable_हटाओ_fast(ht, obj, params, false);
पूर्ण

/**
 * rhltable_हटाओ - हटाओ object from hash list table
 * @hlt:	hash list table
 * @list:	poपूर्णांकer to hash list head inside object
 * @params:	hash table parameters
 *
 * Since the hash chain is single linked, the removal operation needs to
 * walk the bucket chain upon removal. The removal operation is thus
 * considerable slow अगर the hash table is not correctly sized.
 *
 * Will स्वतःmatically shrink the table अगर permitted when residency drops
 * below 30%
 *
 * Returns zero on success, -ENOENT अगर the entry could not be found.
 */
अटल अंतरभूत पूर्णांक rhltable_हटाओ(
	काष्ठा rhltable *hlt, काष्ठा rhlist_head *list,
	स्थिर काष्ठा rhashtable_params params)
अणु
	वापस __rhashtable_हटाओ_fast(&hlt->ht, &list->rhead, params, true);
पूर्ण

/* Internal function, please use rhashtable_replace_fast() instead */
अटल अंतरभूत पूर्णांक __rhashtable_replace_fast(
	काष्ठा rhashtable *ht, काष्ठा bucket_table *tbl,
	काष्ठा rhash_head *obj_old, काष्ठा rhash_head *obj_new,
	स्थिर काष्ठा rhashtable_params params)
अणु
	काष्ठा rhash_lock_head __rcu **bkt;
	काष्ठा rhash_head __rcu **pprev;
	काष्ठा rhash_head *he;
	अचिन्हित पूर्णांक hash;
	पूर्णांक err = -ENOENT;

	/* Minimally, the old and new objects must have same hash
	 * (which should mean identअगरiers are the same).
	 */
	hash = rht_head_hashfn(ht, tbl, obj_old, params);
	अगर (hash != rht_head_hashfn(ht, tbl, obj_new, params))
		वापस -EINVAL;

	bkt = rht_bucket_var(tbl, hash);
	अगर (!bkt)
		वापस -ENOENT;

	pprev = शून्य;
	rht_lock(tbl, bkt);

	rht_क्रम_each_from(he, rht_ptr(bkt, tbl, hash), tbl, hash) अणु
		अगर (he != obj_old) अणु
			pprev = &he->next;
			जारी;
		पूर्ण

		rcu_assign_poपूर्णांकer(obj_new->next, obj_old->next);
		अगर (pprev) अणु
			rcu_assign_poपूर्णांकer(*pprev, obj_new);
			rht_unlock(tbl, bkt);
		पूर्ण अन्यथा अणु
			rht_assign_unlock(tbl, bkt, obj_new);
		पूर्ण
		err = 0;
		जाओ unlocked;
	पूर्ण

	rht_unlock(tbl, bkt);

unlocked:
	वापस err;
पूर्ण

/**
 * rhashtable_replace_fast - replace an object in hash table
 * @ht:		hash table
 * @obj_old:	poपूर्णांकer to hash head inside object being replaced
 * @obj_new:	poपूर्णांकer to hash head inside object which is new
 * @params:	hash table parameters
 *
 * Replacing an object करोesn't affect the number of elements in the hash table
 * or bucket, so we करोn't need to worry about shrinking or expanding the
 * table here.
 *
 * Returns zero on success, -ENOENT अगर the entry could not be found,
 * -EINVAL अगर hash is not the same क्रम the old and new objects.
 */
अटल अंतरभूत पूर्णांक rhashtable_replace_fast(
	काष्ठा rhashtable *ht, काष्ठा rhash_head *obj_old,
	काष्ठा rhash_head *obj_new,
	स्थिर काष्ठा rhashtable_params params)
अणु
	काष्ठा bucket_table *tbl;
	पूर्णांक err;

	rcu_पढ़ो_lock();

	tbl = rht_dereference_rcu(ht->tbl, ht);

	/* Because we have alपढ़ोy taken (and released) the bucket
	 * lock in old_tbl, अगर we find that future_tbl is not yet
	 * visible then that guarantees the entry to still be in
	 * the old tbl अगर it exists.
	 */
	जबतक ((err = __rhashtable_replace_fast(ht, tbl, obj_old,
						obj_new, params)) &&
	       (tbl = rht_dereference_rcu(tbl->future_tbl, ht)))
		;

	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

/**
 * rhltable_walk_enter - Initialise an iterator
 * @hlt:	Table to walk over
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
अटल अंतरभूत व्योम rhltable_walk_enter(काष्ठा rhltable *hlt,
				       काष्ठा rhashtable_iter *iter)
अणु
	वापस rhashtable_walk_enter(&hlt->ht, iter);
पूर्ण

/**
 * rhltable_मुक्त_and_destroy - मुक्त elements and destroy hash list table
 * @hlt:	the hash list table to destroy
 * @मुक्त_fn:	callback to release resources of element
 * @arg:	poपूर्णांकer passed to मुक्त_fn
 *
 * See करोcumentation क्रम rhashtable_मुक्त_and_destroy.
 */
अटल अंतरभूत व्योम rhltable_मुक्त_and_destroy(काष्ठा rhltable *hlt,
					     व्योम (*मुक्त_fn)(व्योम *ptr,
							     व्योम *arg),
					     व्योम *arg)
अणु
	वापस rhashtable_मुक्त_and_destroy(&hlt->ht, मुक्त_fn, arg);
पूर्ण

अटल अंतरभूत व्योम rhltable_destroy(काष्ठा rhltable *hlt)
अणु
	वापस rhltable_मुक्त_and_destroy(hlt, शून्य, शून्य);
पूर्ण

#पूर्ण_अगर /* _LINUX_RHASHTABLE_H */
