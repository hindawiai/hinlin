<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 * Copyright (c) 2016 Facebook
 */
#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/jhash.h>
#समावेश <linux/filter.h>
#समावेश <linux/rculist_nulls.h>
#समावेश <linux/अक्रमom.h>
#समावेश <uapi/linux/btf.h>
#समावेश <linux/rcupdate_trace.h>
#समावेश "percpu_freelist.h"
#समावेश "bpf_lru_list.h"
#समावेश "map_in_map.h"

#घोषणा HTAB_CREATE_FLAG_MASK						\
	(BPF_F_NO_PREALLOC | BPF_F_NO_COMMON_LRU | BPF_F_NUMA_NODE |	\
	 BPF_F_ACCESS_MASK | BPF_F_ZERO_SEED)

#घोषणा BATCH_OPS(_name)			\
	.map_lookup_batch =			\
	_name##_map_lookup_batch,		\
	.map_lookup_and_delete_batch =		\
	_name##_map_lookup_and_delete_batch,	\
	.map_update_batch =			\
	generic_map_update_batch,		\
	.map_delete_batch =			\
	generic_map_delete_batch

/*
 * The bucket lock has two protection scopes:
 *
 * 1) Serializing concurrent operations from BPF programs on dअगरferent
 *    CPUs
 *
 * 2) Serializing concurrent operations from BPF programs and sys_bpf()
 *
 * BPF programs can execute in any context including perf, kprobes and
 * tracing. As there are almost no limits where perf, kprobes and tracing
 * can be invoked from the lock operations need to be रक्षित against
 * deadlocks. Deadlocks can be caused by recursion and by an invocation in
 * the lock held section when functions which acquire this lock are invoked
 * from sys_bpf(). BPF recursion is prevented by incrementing the per CPU
 * variable bpf_prog_active, which prevents BPF programs attached to perf
 * events, kprobes and tracing to be invoked beक्रमe the prior invocation
 * from one of these contexts completed. sys_bpf() uses the same mechanism
 * by pinning the task to the current CPU and incrementing the recursion
 * protection accross the map operation.
 *
 * This has subtle implications on PREEMPT_RT. PREEMPT_RT क्रमbids certain
 * operations like memory allocations (even with GFP_ATOMIC) from atomic
 * contexts. This is required because even with GFP_ATOMIC the memory
 * allocator calls पूर्णांकo code pathes which acquire locks with दीर्घ held lock
 * sections. To ensure the deterministic behaviour these locks are regular
 * spinlocks, which are converted to 'sleepable' spinlocks on RT. The only
 * true atomic contexts on an RT kernel are the low level hardware
 * handling, scheduling, low level पूर्णांकerrupt handling, NMIs etc. None of
 * these contexts should ever करो memory allocations.
 *
 * As regular device पूर्णांकerrupt handlers and soft पूर्णांकerrupts are क्रमced पूर्णांकo
 * thपढ़ो context, the existing code which करोes
 *   spin_lock*(); alloc(GPF_ATOMIC); spin_unlock*();
 * just works.
 *
 * In theory the BPF locks could be converted to regular spinlocks as well,
 * but the bucket locks and percpu_मुक्तlist locks can be taken from
 * arbitrary contexts (perf, kprobes, tracepoपूर्णांकs) which are required to be
 * atomic contexts even on RT. These mechanisms require pपुनः_स्मृतिated maps,
 * so there is no need to invoke memory allocations within the lock held
 * sections.
 *
 * BPF maps which need dynamic allocation are only used from (क्रमced)
 * thपढ़ो context on RT and can thereक्रमe use regular spinlocks which in
 * turn allows to invoke memory allocations from the lock held section.
 *
 * On a non RT kernel this distinction is neither possible nor required.
 * spinlock maps to raw_spinlock and the extra code is optimized out by the
 * compiler.
 */
काष्ठा bucket अणु
	काष्ठा hlist_nulls_head head;
	जोड़ अणु
		raw_spinlock_t raw_lock;
		spinlock_t     lock;
	पूर्ण;
पूर्ण;

#घोषणा HASHTAB_MAP_LOCK_COUNT 8
#घोषणा HASHTAB_MAP_LOCK_MASK (HASHTAB_MAP_LOCK_COUNT - 1)

काष्ठा bpf_htab अणु
	काष्ठा bpf_map map;
	काष्ठा bucket *buckets;
	व्योम *elems;
	जोड़ अणु
		काष्ठा pcpu_मुक्तlist मुक्तlist;
		काष्ठा bpf_lru lru;
	पूर्ण;
	काष्ठा htab_elem *__percpu *extra_elems;
	atomic_t count;	/* number of elements in this hashtable */
	u32 n_buckets;	/* number of hash buckets */
	u32 elem_size;	/* size of each element in bytes */
	u32 hashrnd;
	काष्ठा lock_class_key lockdep_key;
	पूर्णांक __percpu *map_locked[HASHTAB_MAP_LOCK_COUNT];
पूर्ण;

/* each htab element is काष्ठा htab_elem + key + value */
काष्ठा htab_elem अणु
	जोड़ अणु
		काष्ठा hlist_nulls_node hash_node;
		काष्ठा अणु
			व्योम *padding;
			जोड़ अणु
				काष्ठा bpf_htab *htab;
				काष्ठा pcpu_मुक्तlist_node fnode;
				काष्ठा htab_elem *batch_flink;
			पूर्ण;
		पूर्ण;
	पूर्ण;
	जोड़ अणु
		काष्ठा rcu_head rcu;
		काष्ठा bpf_lru_node lru_node;
	पूर्ण;
	u32 hash;
	अक्षर key[] __aligned(8);
पूर्ण;

अटल अंतरभूत bool htab_is_pपुनः_स्मृति(स्थिर काष्ठा bpf_htab *htab)
अणु
	वापस !(htab->map.map_flags & BPF_F_NO_PREALLOC);
पूर्ण

अटल अंतरभूत bool htab_use_raw_lock(स्थिर काष्ठा bpf_htab *htab)
अणु
	वापस (!IS_ENABLED(CONFIG_PREEMPT_RT) || htab_is_pपुनः_स्मृति(htab));
पूर्ण

अटल व्योम htab_init_buckets(काष्ठा bpf_htab *htab)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < htab->n_buckets; i++) अणु
		INIT_HLIST_शून्यS_HEAD(&htab->buckets[i].head, i);
		अगर (htab_use_raw_lock(htab)) अणु
			raw_spin_lock_init(&htab->buckets[i].raw_lock);
			lockdep_set_class(&htab->buckets[i].raw_lock,
					  &htab->lockdep_key);
		पूर्ण अन्यथा अणु
			spin_lock_init(&htab->buckets[i].lock);
			lockdep_set_class(&htab->buckets[i].lock,
					  &htab->lockdep_key);
		पूर्ण
		cond_resched();
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक htab_lock_bucket(स्थिर काष्ठा bpf_htab *htab,
				   काष्ठा bucket *b, u32 hash,
				   अचिन्हित दीर्घ *pflags)
अणु
	अचिन्हित दीर्घ flags;

	hash = hash & HASHTAB_MAP_LOCK_MASK;

	migrate_disable();
	अगर (unlikely(__this_cpu_inc_वापस(*(htab->map_locked[hash])) != 1)) अणु
		__this_cpu_dec(*(htab->map_locked[hash]));
		migrate_enable();
		वापस -EBUSY;
	पूर्ण

	अगर (htab_use_raw_lock(htab))
		raw_spin_lock_irqsave(&b->raw_lock, flags);
	अन्यथा
		spin_lock_irqsave(&b->lock, flags);
	*pflags = flags;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम htab_unlock_bucket(स्थिर काष्ठा bpf_htab *htab,
				      काष्ठा bucket *b, u32 hash,
				      अचिन्हित दीर्घ flags)
अणु
	hash = hash & HASHTAB_MAP_LOCK_MASK;
	अगर (htab_use_raw_lock(htab))
		raw_spin_unlock_irqrestore(&b->raw_lock, flags);
	अन्यथा
		spin_unlock_irqrestore(&b->lock, flags);
	__this_cpu_dec(*(htab->map_locked[hash]));
	migrate_enable();
पूर्ण

अटल bool htab_lru_map_delete_node(व्योम *arg, काष्ठा bpf_lru_node *node);

अटल bool htab_is_lru(स्थिर काष्ठा bpf_htab *htab)
अणु
	वापस htab->map.map_type == BPF_MAP_TYPE_LRU_HASH ||
		htab->map.map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH;
पूर्ण

अटल bool htab_is_percpu(स्थिर काष्ठा bpf_htab *htab)
अणु
	वापस htab->map.map_type == BPF_MAP_TYPE_PERCPU_HASH ||
		htab->map.map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH;
पूर्ण

अटल अंतरभूत व्योम htab_elem_set_ptr(काष्ठा htab_elem *l, u32 key_size,
				     व्योम __percpu *pptr)
अणु
	*(व्योम __percpu **)(l->key + key_size) = pptr;
पूर्ण

अटल अंतरभूत व्योम __percpu *htab_elem_get_ptr(काष्ठा htab_elem *l, u32 key_size)
अणु
	वापस *(व्योम __percpu **)(l->key + key_size);
पूर्ण

अटल व्योम *fd_htab_map_get_ptr(स्थिर काष्ठा bpf_map *map, काष्ठा htab_elem *l)
अणु
	वापस *(व्योम **)(l->key + roundup(map->key_size, 8));
पूर्ण

अटल काष्ठा htab_elem *get_htab_elem(काष्ठा bpf_htab *htab, पूर्णांक i)
अणु
	वापस (काष्ठा htab_elem *) (htab->elems + i * (u64)htab->elem_size);
पूर्ण

अटल व्योम htab_मुक्त_elems(काष्ठा bpf_htab *htab)
अणु
	पूर्णांक i;

	अगर (!htab_is_percpu(htab))
		जाओ मुक्त_elems;

	क्रम (i = 0; i < htab->map.max_entries; i++) अणु
		व्योम __percpu *pptr;

		pptr = htab_elem_get_ptr(get_htab_elem(htab, i),
					 htab->map.key_size);
		मुक्त_percpu(pptr);
		cond_resched();
	पूर्ण
मुक्त_elems:
	bpf_map_area_मुक्त(htab->elems);
पूर्ण

/* The LRU list has a lock (lru_lock). Each htab bucket has a lock
 * (bucket_lock). If both locks need to be acquired together, the lock
 * order is always lru_lock -> bucket_lock and this only happens in
 * bpf_lru_list.c logic. For example, certain code path of
 * bpf_lru_pop_मुक्त(), which is called by function pपुनः_स्मृति_lru_pop(),
 * will acquire lru_lock first followed by acquiring bucket_lock.
 *
 * In hashtab.c, to aव्योम deadlock, lock acquisition of
 * bucket_lock followed by lru_lock is not allowed. In such हालs,
 * bucket_lock needs to be released first beक्रमe acquiring lru_lock.
 */
अटल काष्ठा htab_elem *pपुनः_स्मृति_lru_pop(काष्ठा bpf_htab *htab, व्योम *key,
					  u32 hash)
अणु
	काष्ठा bpf_lru_node *node = bpf_lru_pop_मुक्त(&htab->lru, hash);
	काष्ठा htab_elem *l;

	अगर (node) अणु
		l = container_of(node, काष्ठा htab_elem, lru_node);
		स_नकल(l->key, key, htab->map.key_size);
		वापस l;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक pपुनः_स्मृति_init(काष्ठा bpf_htab *htab)
अणु
	u32 num_entries = htab->map.max_entries;
	पूर्णांक err = -ENOMEM, i;

	अगर (!htab_is_percpu(htab) && !htab_is_lru(htab))
		num_entries += num_possible_cpus();

	htab->elems = bpf_map_area_alloc((u64)htab->elem_size * num_entries,
					 htab->map.numa_node);
	अगर (!htab->elems)
		वापस -ENOMEM;

	अगर (!htab_is_percpu(htab))
		जाओ skip_percpu_elems;

	क्रम (i = 0; i < num_entries; i++) अणु
		u32 size = round_up(htab->map.value_size, 8);
		व्योम __percpu *pptr;

		pptr = bpf_map_alloc_percpu(&htab->map, size, 8,
					    GFP_USER | __GFP_NOWARN);
		अगर (!pptr)
			जाओ मुक्त_elems;
		htab_elem_set_ptr(get_htab_elem(htab, i), htab->map.key_size,
				  pptr);
		cond_resched();
	पूर्ण

skip_percpu_elems:
	अगर (htab_is_lru(htab))
		err = bpf_lru_init(&htab->lru,
				   htab->map.map_flags & BPF_F_NO_COMMON_LRU,
				   दुरत्व(काष्ठा htab_elem, hash) -
				   दुरत्व(काष्ठा htab_elem, lru_node),
				   htab_lru_map_delete_node,
				   htab);
	अन्यथा
		err = pcpu_मुक्तlist_init(&htab->मुक्तlist);

	अगर (err)
		जाओ मुक्त_elems;

	अगर (htab_is_lru(htab))
		bpf_lru_populate(&htab->lru, htab->elems,
				 दुरत्व(काष्ठा htab_elem, lru_node),
				 htab->elem_size, num_entries);
	अन्यथा
		pcpu_मुक्तlist_populate(&htab->मुक्तlist,
				       htab->elems + दुरत्व(काष्ठा htab_elem, fnode),
				       htab->elem_size, num_entries);

	वापस 0;

मुक्त_elems:
	htab_मुक्त_elems(htab);
	वापस err;
पूर्ण

अटल व्योम pपुनः_स्मृति_destroy(काष्ठा bpf_htab *htab)
अणु
	htab_मुक्त_elems(htab);

	अगर (htab_is_lru(htab))
		bpf_lru_destroy(&htab->lru);
	अन्यथा
		pcpu_मुक्तlist_destroy(&htab->मुक्तlist);
पूर्ण

अटल पूर्णांक alloc_extra_elems(काष्ठा bpf_htab *htab)
अणु
	काष्ठा htab_elem *__percpu *pptr, *l_new;
	काष्ठा pcpu_मुक्तlist_node *l;
	पूर्णांक cpu;

	pptr = bpf_map_alloc_percpu(&htab->map, माप(काष्ठा htab_elem *), 8,
				    GFP_USER | __GFP_NOWARN);
	अगर (!pptr)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(cpu) अणु
		l = pcpu_मुक्तlist_pop(&htab->मुक्तlist);
		/* pop will succeed, since pपुनः_स्मृति_init()
		 * pपुनः_स्मृतिated extra num_possible_cpus elements
		 */
		l_new = container_of(l, काष्ठा htab_elem, fnode);
		*per_cpu_ptr(pptr, cpu) = l_new;
	पूर्ण
	htab->extra_elems = pptr;
	वापस 0;
पूर्ण

/* Called from syscall */
अटल पूर्णांक htab_map_alloc_check(जोड़ bpf_attr *attr)
अणु
	bool percpu = (attr->map_type == BPF_MAP_TYPE_PERCPU_HASH ||
		       attr->map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH);
	bool lru = (attr->map_type == BPF_MAP_TYPE_LRU_HASH ||
		    attr->map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH);
	/* percpu_lru means each cpu has its own LRU list.
	 * it is dअगरferent from BPF_MAP_TYPE_PERCPU_HASH where
	 * the map's value itself is percpu.  percpu_lru has
	 * nothing to करो with the map's value.
	 */
	bool percpu_lru = (attr->map_flags & BPF_F_NO_COMMON_LRU);
	bool pपुनः_स्मृति = !(attr->map_flags & BPF_F_NO_PREALLOC);
	bool zero_seed = (attr->map_flags & BPF_F_ZERO_SEED);
	पूर्णांक numa_node = bpf_map_attr_numa_node(attr);

	BUILD_BUG_ON(दुरत्व(काष्ठा htab_elem, htab) !=
		     दुरत्व(काष्ठा htab_elem, hash_node.pprev));
	BUILD_BUG_ON(दुरत्व(काष्ठा htab_elem, fnode.next) !=
		     दुरत्व(काष्ठा htab_elem, hash_node.pprev));

	अगर (lru && !bpf_capable())
		/* LRU implementation is much complicated than other
		 * maps.  Hence, limit to CAP_BPF.
		 */
		वापस -EPERM;

	अगर (zero_seed && !capable(CAP_SYS_ADMIN))
		/* Guard against local DoS, and discourage production use. */
		वापस -EPERM;

	अगर (attr->map_flags & ~HTAB_CREATE_FLAG_MASK ||
	    !bpf_map_flags_access_ok(attr->map_flags))
		वापस -EINVAL;

	अगर (!lru && percpu_lru)
		वापस -EINVAL;

	अगर (lru && !pपुनः_स्मृति)
		वापस -ENOTSUPP;

	अगर (numa_node != NUMA_NO_NODE && (percpu || percpu_lru))
		वापस -EINVAL;

	/* check sanity of attributes.
	 * value_size == 0 may be allowed in the future to use map as a set
	 */
	अगर (attr->max_entries == 0 || attr->key_size == 0 ||
	    attr->value_size == 0)
		वापस -EINVAL;

	अगर ((u64)attr->key_size + attr->value_size >= KMALLOC_MAX_SIZE -
	   माप(काष्ठा htab_elem))
		/* अगर key_size + value_size is bigger, the user space won't be
		 * able to access the elements via bpf syscall. This check
		 * also makes sure that the elem_size करोesn't overflow and it's
		 * kदो_स्मृति-able later in htab_map_update_elem()
		 */
		वापस -E2BIG;

	वापस 0;
पूर्ण

अटल काष्ठा bpf_map *htab_map_alloc(जोड़ bpf_attr *attr)
अणु
	bool percpu = (attr->map_type == BPF_MAP_TYPE_PERCPU_HASH ||
		       attr->map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH);
	bool lru = (attr->map_type == BPF_MAP_TYPE_LRU_HASH ||
		    attr->map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH);
	/* percpu_lru means each cpu has its own LRU list.
	 * it is dअगरferent from BPF_MAP_TYPE_PERCPU_HASH where
	 * the map's value itself is percpu.  percpu_lru has
	 * nothing to करो with the map's value.
	 */
	bool percpu_lru = (attr->map_flags & BPF_F_NO_COMMON_LRU);
	bool pपुनः_स्मृति = !(attr->map_flags & BPF_F_NO_PREALLOC);
	काष्ठा bpf_htab *htab;
	पूर्णांक err, i;

	htab = kzalloc(माप(*htab), GFP_USER | __GFP_ACCOUNT);
	अगर (!htab)
		वापस ERR_PTR(-ENOMEM);

	lockdep_रेजिस्टर_key(&htab->lockdep_key);

	bpf_map_init_from_attr(&htab->map, attr);

	अगर (percpu_lru) अणु
		/* ensure each CPU's lru list has >=1 elements.
		 * since we are at it, make each lru list has the same
		 * number of elements.
		 */
		htab->map.max_entries = roundup(attr->max_entries,
						num_possible_cpus());
		अगर (htab->map.max_entries < attr->max_entries)
			htab->map.max_entries = roundकरोwn(attr->max_entries,
							  num_possible_cpus());
	पूर्ण

	/* hash table size must be घातer of 2 */
	htab->n_buckets = roundup_घात_of_two(htab->map.max_entries);

	htab->elem_size = माप(काष्ठा htab_elem) +
			  round_up(htab->map.key_size, 8);
	अगर (percpu)
		htab->elem_size += माप(व्योम *);
	अन्यथा
		htab->elem_size += round_up(htab->map.value_size, 8);

	err = -E2BIG;
	/* prevent zero size kदो_स्मृति and check क्रम u32 overflow */
	अगर (htab->n_buckets == 0 ||
	    htab->n_buckets > U32_MAX / माप(काष्ठा bucket))
		जाओ मुक्त_htab;

	err = -ENOMEM;
	htab->buckets = bpf_map_area_alloc(htab->n_buckets *
					   माप(काष्ठा bucket),
					   htab->map.numa_node);
	अगर (!htab->buckets)
		जाओ मुक्त_htab;

	क्रम (i = 0; i < HASHTAB_MAP_LOCK_COUNT; i++) अणु
		htab->map_locked[i] = bpf_map_alloc_percpu(&htab->map,
							   माप(पूर्णांक),
							   माप(पूर्णांक),
							   GFP_USER);
		अगर (!htab->map_locked[i])
			जाओ मुक्त_map_locked;
	पूर्ण

	अगर (htab->map.map_flags & BPF_F_ZERO_SEED)
		htab->hashrnd = 0;
	अन्यथा
		htab->hashrnd = get_अक्रमom_पूर्णांक();

	htab_init_buckets(htab);

	अगर (pपुनः_स्मृति) अणु
		err = pपुनः_स्मृति_init(htab);
		अगर (err)
			जाओ मुक्त_map_locked;

		अगर (!percpu && !lru) अणु
			/* lru itself can हटाओ the least used element, so
			 * there is no need क्रम an extra elem during map_update.
			 */
			err = alloc_extra_elems(htab);
			अगर (err)
				जाओ मुक्त_pपुनः_स्मृति;
		पूर्ण
	पूर्ण

	वापस &htab->map;

मुक्त_pपुनः_स्मृति:
	pपुनः_स्मृति_destroy(htab);
मुक्त_map_locked:
	क्रम (i = 0; i < HASHTAB_MAP_LOCK_COUNT; i++)
		मुक्त_percpu(htab->map_locked[i]);
	bpf_map_area_मुक्त(htab->buckets);
मुक्त_htab:
	lockdep_unरेजिस्टर_key(&htab->lockdep_key);
	kमुक्त(htab);
	वापस ERR_PTR(err);
पूर्ण

अटल अंतरभूत u32 htab_map_hash(स्थिर व्योम *key, u32 key_len, u32 hashrnd)
अणु
	वापस jhash(key, key_len, hashrnd);
पूर्ण

अटल अंतरभूत काष्ठा bucket *__select_bucket(काष्ठा bpf_htab *htab, u32 hash)
अणु
	वापस &htab->buckets[hash & (htab->n_buckets - 1)];
पूर्ण

अटल अंतरभूत काष्ठा hlist_nulls_head *select_bucket(काष्ठा bpf_htab *htab, u32 hash)
अणु
	वापस &__select_bucket(htab, hash)->head;
पूर्ण

/* this lookup function can only be called with bucket lock taken */
अटल काष्ठा htab_elem *lookup_elem_raw(काष्ठा hlist_nulls_head *head, u32 hash,
					 व्योम *key, u32 key_size)
अणु
	काष्ठा hlist_nulls_node *n;
	काष्ठा htab_elem *l;

	hlist_nulls_क्रम_each_entry_rcu(l, n, head, hash_node)
		अगर (l->hash == hash && !स_भेद(&l->key, key, key_size))
			वापस l;

	वापस शून्य;
पूर्ण

/* can be called without bucket lock. it will repeat the loop in
 * the unlikely event when elements moved from one bucket पूर्णांकo another
 * जबतक link list is being walked
 */
अटल काष्ठा htab_elem *lookup_nulls_elem_raw(काष्ठा hlist_nulls_head *head,
					       u32 hash, व्योम *key,
					       u32 key_size, u32 n_buckets)
अणु
	काष्ठा hlist_nulls_node *n;
	काष्ठा htab_elem *l;

again:
	hlist_nulls_क्रम_each_entry_rcu(l, n, head, hash_node)
		अगर (l->hash == hash && !स_भेद(&l->key, key, key_size))
			वापस l;

	अगर (unlikely(get_nulls_value(n) != (hash & (n_buckets - 1))))
		जाओ again;

	वापस शून्य;
पूर्ण

/* Called from syscall or from eBPF program directly, so
 * arguments have to match bpf_map_lookup_elem() exactly.
 * The वापस value is adjusted by BPF inकाष्ठाions
 * in htab_map_gen_lookup().
 */
अटल व्योम *__htab_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	काष्ठा hlist_nulls_head *head;
	काष्ठा htab_elem *l;
	u32 hash, key_size;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held() && !rcu_पढ़ो_lock_trace_held());

	key_size = map->key_size;

	hash = htab_map_hash(key, key_size, htab->hashrnd);

	head = select_bucket(htab, hash);

	l = lookup_nulls_elem_raw(head, hash, key, key_size, htab->n_buckets);

	वापस l;
पूर्ण

अटल व्योम *htab_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा htab_elem *l = __htab_map_lookup_elem(map, key);

	अगर (l)
		वापस l->key + round_up(map->key_size, 8);

	वापस शून्य;
पूर्ण

/* अंतरभूत bpf_map_lookup_elem() call.
 * Instead of:
 * bpf_prog
 *   bpf_map_lookup_elem
 *     map->ops->map_lookup_elem
 *       htab_map_lookup_elem
 *         __htab_map_lookup_elem
 * करो:
 * bpf_prog
 *   __htab_map_lookup_elem
 */
अटल पूर्णांक htab_map_gen_lookup(काष्ठा bpf_map *map, काष्ठा bpf_insn *insn_buf)
अणु
	काष्ठा bpf_insn *insn = insn_buf;
	स्थिर पूर्णांक ret = BPF_REG_0;

	BUILD_BUG_ON(!__same_type(&__htab_map_lookup_elem,
		     (व्योम *(*)(काष्ठा bpf_map *map, व्योम *key))शून्य));
	*insn++ = BPF_EMIT_CALL(BPF_CAST_CALL(__htab_map_lookup_elem));
	*insn++ = BPF_JMP_IMM(BPF_JEQ, ret, 0, 1);
	*insn++ = BPF_ALU64_IMM(BPF_ADD, ret,
				दुरत्व(काष्ठा htab_elem, key) +
				round_up(map->key_size, 8));
	वापस insn - insn_buf;
पूर्ण

अटल __always_अंतरभूत व्योम *__htab_lru_map_lookup_elem(काष्ठा bpf_map *map,
							व्योम *key, स्थिर bool mark)
अणु
	काष्ठा htab_elem *l = __htab_map_lookup_elem(map, key);

	अगर (l) अणु
		अगर (mark)
			bpf_lru_node_set_ref(&l->lru_node);
		वापस l->key + round_up(map->key_size, 8);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *htab_lru_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	वापस __htab_lru_map_lookup_elem(map, key, true);
पूर्ण

अटल व्योम *htab_lru_map_lookup_elem_sys(काष्ठा bpf_map *map, व्योम *key)
अणु
	वापस __htab_lru_map_lookup_elem(map, key, false);
पूर्ण

अटल पूर्णांक htab_lru_map_gen_lookup(काष्ठा bpf_map *map,
				   काष्ठा bpf_insn *insn_buf)
अणु
	काष्ठा bpf_insn *insn = insn_buf;
	स्थिर पूर्णांक ret = BPF_REG_0;
	स्थिर पूर्णांक ref_reg = BPF_REG_1;

	BUILD_BUG_ON(!__same_type(&__htab_map_lookup_elem,
		     (व्योम *(*)(काष्ठा bpf_map *map, व्योम *key))शून्य));
	*insn++ = BPF_EMIT_CALL(BPF_CAST_CALL(__htab_map_lookup_elem));
	*insn++ = BPF_JMP_IMM(BPF_JEQ, ret, 0, 4);
	*insn++ = BPF_LDX_MEM(BPF_B, ref_reg, ret,
			      दुरत्व(काष्ठा htab_elem, lru_node) +
			      दुरत्व(काष्ठा bpf_lru_node, ref));
	*insn++ = BPF_JMP_IMM(BPF_JNE, ref_reg, 0, 1);
	*insn++ = BPF_ST_MEM(BPF_B, ret,
			     दुरत्व(काष्ठा htab_elem, lru_node) +
			     दुरत्व(काष्ठा bpf_lru_node, ref),
			     1);
	*insn++ = BPF_ALU64_IMM(BPF_ADD, ret,
				दुरत्व(काष्ठा htab_elem, key) +
				round_up(map->key_size, 8));
	वापस insn - insn_buf;
पूर्ण

/* It is called from the bpf_lru_list when the LRU needs to delete
 * older elements from the htab.
 */
अटल bool htab_lru_map_delete_node(व्योम *arg, काष्ठा bpf_lru_node *node)
अणु
	काष्ठा bpf_htab *htab = (काष्ठा bpf_htab *)arg;
	काष्ठा htab_elem *l = शून्य, *tgt_l;
	काष्ठा hlist_nulls_head *head;
	काष्ठा hlist_nulls_node *n;
	अचिन्हित दीर्घ flags;
	काष्ठा bucket *b;
	पूर्णांक ret;

	tgt_l = container_of(node, काष्ठा htab_elem, lru_node);
	b = __select_bucket(htab, tgt_l->hash);
	head = &b->head;

	ret = htab_lock_bucket(htab, b, tgt_l->hash, &flags);
	अगर (ret)
		वापस false;

	hlist_nulls_क्रम_each_entry_rcu(l, n, head, hash_node)
		अगर (l == tgt_l) अणु
			hlist_nulls_del_rcu(&l->hash_node);
			अवरोध;
		पूर्ण

	htab_unlock_bucket(htab, b, tgt_l->hash, flags);

	वापस l == tgt_l;
पूर्ण

/* Called from syscall */
अटल पूर्णांक htab_map_get_next_key(काष्ठा bpf_map *map, व्योम *key, व्योम *next_key)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	काष्ठा hlist_nulls_head *head;
	काष्ठा htab_elem *l, *next_l;
	u32 hash, key_size;
	पूर्णांक i = 0;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());

	key_size = map->key_size;

	अगर (!key)
		जाओ find_first_elem;

	hash = htab_map_hash(key, key_size, htab->hashrnd);

	head = select_bucket(htab, hash);

	/* lookup the key */
	l = lookup_nulls_elem_raw(head, hash, key, key_size, htab->n_buckets);

	अगर (!l)
		जाओ find_first_elem;

	/* key was found, get next key in the same bucket */
	next_l = hlist_nulls_entry_safe(rcu_dereference_raw(hlist_nulls_next_rcu(&l->hash_node)),
				  काष्ठा htab_elem, hash_node);

	अगर (next_l) अणु
		/* अगर next elem in this hash list is non-zero, just वापस it */
		स_नकल(next_key, next_l->key, key_size);
		वापस 0;
	पूर्ण

	/* no more elements in this hash list, go to the next bucket */
	i = hash & (htab->n_buckets - 1);
	i++;

find_first_elem:
	/* iterate over buckets */
	क्रम (; i < htab->n_buckets; i++) अणु
		head = select_bucket(htab, i);

		/* pick first element in the bucket */
		next_l = hlist_nulls_entry_safe(rcu_dereference_raw(hlist_nulls_first_rcu(head)),
					  काष्ठा htab_elem, hash_node);
		अगर (next_l) अणु
			/* अगर it's not empty, just वापस it */
			स_नकल(next_key, next_l->key, key_size);
			वापस 0;
		पूर्ण
	पूर्ण

	/* iterated over all buckets and all elements */
	वापस -ENOENT;
पूर्ण

अटल व्योम htab_elem_मुक्त(काष्ठा bpf_htab *htab, काष्ठा htab_elem *l)
अणु
	अगर (htab->map.map_type == BPF_MAP_TYPE_PERCPU_HASH)
		मुक्त_percpu(htab_elem_get_ptr(l, htab->map.key_size));
	kमुक्त(l);
पूर्ण

अटल व्योम htab_elem_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा htab_elem *l = container_of(head, काष्ठा htab_elem, rcu);
	काष्ठा bpf_htab *htab = l->htab;

	htab_elem_मुक्त(htab, l);
पूर्ण

अटल व्योम htab_put_fd_value(काष्ठा bpf_htab *htab, काष्ठा htab_elem *l)
अणु
	काष्ठा bpf_map *map = &htab->map;
	व्योम *ptr;

	अगर (map->ops->map_fd_put_ptr) अणु
		ptr = fd_htab_map_get_ptr(map, l);
		map->ops->map_fd_put_ptr(ptr);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_htab_elem(काष्ठा bpf_htab *htab, काष्ठा htab_elem *l)
अणु
	htab_put_fd_value(htab, l);

	अगर (htab_is_pपुनः_स्मृति(htab)) अणु
		__pcpu_मुक्तlist_push(&htab->मुक्तlist, &l->fnode);
	पूर्ण अन्यथा अणु
		atomic_dec(&htab->count);
		l->htab = htab;
		call_rcu(&l->rcu, htab_elem_मुक्त_rcu);
	पूर्ण
पूर्ण

अटल व्योम pcpu_copy_value(काष्ठा bpf_htab *htab, व्योम __percpu *pptr,
			    व्योम *value, bool onallcpus)
अणु
	अगर (!onallcpus) अणु
		/* copy true value_size bytes */
		स_नकल(this_cpu_ptr(pptr), value, htab->map.value_size);
	पूर्ण अन्यथा अणु
		u32 size = round_up(htab->map.value_size, 8);
		पूर्णांक off = 0, cpu;

		क्रम_each_possible_cpu(cpu) अणु
			bpf_दीर्घ_स_नकल(per_cpu_ptr(pptr, cpu),
					value + off, size);
			off += size;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pcpu_init_value(काष्ठा bpf_htab *htab, व्योम __percpu *pptr,
			    व्योम *value, bool onallcpus)
अणु
	/* When using pपुनः_स्मृति and not setting the initial value on all cpus,
	 * zero-fill element values क्रम other cpus (just as what happens when
	 * not using pपुनः_स्मृति). Otherwise, bpf program has no way to ensure
	 * known initial values क्रम cpus other than current one
	 * (onallcpus=false always when coming from bpf prog).
	 */
	अगर (htab_is_pपुनः_स्मृति(htab) && !onallcpus) अणु
		u32 size = round_up(htab->map.value_size, 8);
		पूर्णांक current_cpu = raw_smp_processor_id();
		पूर्णांक cpu;

		क्रम_each_possible_cpu(cpu) अणु
			अगर (cpu == current_cpu)
				bpf_दीर्घ_स_नकल(per_cpu_ptr(pptr, cpu), value,
						size);
			अन्यथा
				स_रखो(per_cpu_ptr(pptr, cpu), 0, size);
		पूर्ण
	पूर्ण अन्यथा अणु
		pcpu_copy_value(htab, pptr, value, onallcpus);
	पूर्ण
पूर्ण

अटल bool fd_htab_map_needs_adjust(स्थिर काष्ठा bpf_htab *htab)
अणु
	वापस htab->map.map_type == BPF_MAP_TYPE_HASH_OF_MAPS &&
	       BITS_PER_LONG == 64;
पूर्ण

अटल काष्ठा htab_elem *alloc_htab_elem(काष्ठा bpf_htab *htab, व्योम *key,
					 व्योम *value, u32 key_size, u32 hash,
					 bool percpu, bool onallcpus,
					 काष्ठा htab_elem *old_elem)
अणु
	u32 size = htab->map.value_size;
	bool pपुनः_स्मृति = htab_is_pपुनः_स्मृति(htab);
	काष्ठा htab_elem *l_new, **pl_new;
	व्योम __percpu *pptr;

	अगर (pपुनः_स्मृति) अणु
		अगर (old_elem) अणु
			/* अगर we're updating the existing element,
			 * use per-cpu extra elems to aव्योम मुक्तlist_pop/push
			 */
			pl_new = this_cpu_ptr(htab->extra_elems);
			l_new = *pl_new;
			htab_put_fd_value(htab, old_elem);
			*pl_new = old_elem;
		पूर्ण अन्यथा अणु
			काष्ठा pcpu_मुक्तlist_node *l;

			l = __pcpu_मुक्तlist_pop(&htab->मुक्तlist);
			अगर (!l)
				वापस ERR_PTR(-E2BIG);
			l_new = container_of(l, काष्ठा htab_elem, fnode);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (atomic_inc_वापस(&htab->count) > htab->map.max_entries)
			अगर (!old_elem) अणु
				/* when map is full and update() is replacing
				 * old element, it's ok to allocate, since
				 * old element will be मुक्तd immediately.
				 * Otherwise वापस an error
				 */
				l_new = ERR_PTR(-E2BIG);
				जाओ dec_count;
			पूर्ण
		l_new = bpf_map_kदो_स्मृति_node(&htab->map, htab->elem_size,
					     GFP_ATOMIC | __GFP_NOWARN,
					     htab->map.numa_node);
		अगर (!l_new) अणु
			l_new = ERR_PTR(-ENOMEM);
			जाओ dec_count;
		पूर्ण
		check_and_init_map_lock(&htab->map,
					l_new->key + round_up(key_size, 8));
	पूर्ण

	स_नकल(l_new->key, key, key_size);
	अगर (percpu) अणु
		size = round_up(size, 8);
		अगर (pपुनः_स्मृति) अणु
			pptr = htab_elem_get_ptr(l_new, key_size);
		पूर्ण अन्यथा अणु
			/* alloc_percpu zero-fills */
			pptr = bpf_map_alloc_percpu(&htab->map, size, 8,
						    GFP_ATOMIC | __GFP_NOWARN);
			अगर (!pptr) अणु
				kमुक्त(l_new);
				l_new = ERR_PTR(-ENOMEM);
				जाओ dec_count;
			पूर्ण
		पूर्ण

		pcpu_init_value(htab, pptr, value, onallcpus);

		अगर (!pपुनः_स्मृति)
			htab_elem_set_ptr(l_new, key_size, pptr);
	पूर्ण अन्यथा अगर (fd_htab_map_needs_adjust(htab)) अणु
		size = round_up(size, 8);
		स_नकल(l_new->key + round_up(key_size, 8), value, size);
	पूर्ण अन्यथा अणु
		copy_map_value(&htab->map,
			       l_new->key + round_up(key_size, 8),
			       value);
	पूर्ण

	l_new->hash = hash;
	वापस l_new;
dec_count:
	atomic_dec(&htab->count);
	वापस l_new;
पूर्ण

अटल पूर्णांक check_flags(काष्ठा bpf_htab *htab, काष्ठा htab_elem *l_old,
		       u64 map_flags)
अणु
	अगर (l_old && (map_flags & ~BPF_F_LOCK) == BPF_NOEXIST)
		/* elem alपढ़ोy exists */
		वापस -EEXIST;

	अगर (!l_old && (map_flags & ~BPF_F_LOCK) == BPF_EXIST)
		/* elem करोesn't exist, cannot update it */
		वापस -ENOENT;

	वापस 0;
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक htab_map_update_elem(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
				u64 map_flags)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	काष्ठा htab_elem *l_new = शून्य, *l_old;
	काष्ठा hlist_nulls_head *head;
	अचिन्हित दीर्घ flags;
	काष्ठा bucket *b;
	u32 key_size, hash;
	पूर्णांक ret;

	अगर (unlikely((map_flags & ~BPF_F_LOCK) > BPF_EXIST))
		/* unknown flags */
		वापस -EINVAL;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held() && !rcu_पढ़ो_lock_trace_held());

	key_size = map->key_size;

	hash = htab_map_hash(key, key_size, htab->hashrnd);

	b = __select_bucket(htab, hash);
	head = &b->head;

	अगर (unlikely(map_flags & BPF_F_LOCK)) अणु
		अगर (unlikely(!map_value_has_spin_lock(map)))
			वापस -EINVAL;
		/* find an element without taking the bucket lock */
		l_old = lookup_nulls_elem_raw(head, hash, key, key_size,
					      htab->n_buckets);
		ret = check_flags(htab, l_old, map_flags);
		अगर (ret)
			वापस ret;
		अगर (l_old) अणु
			/* grab the element lock and update value in place */
			copy_map_value_locked(map,
					      l_old->key + round_up(key_size, 8),
					      value, false);
			वापस 0;
		पूर्ण
		/* fall through, grab the bucket lock and lookup again.
		 * 99.9% chance that the element won't be found,
		 * but second lookup under lock has to be करोne.
		 */
	पूर्ण

	ret = htab_lock_bucket(htab, b, hash, &flags);
	अगर (ret)
		वापस ret;

	l_old = lookup_elem_raw(head, hash, key, key_size);

	ret = check_flags(htab, l_old, map_flags);
	अगर (ret)
		जाओ err;

	अगर (unlikely(l_old && (map_flags & BPF_F_LOCK))) अणु
		/* first lookup without the bucket lock didn't find the element,
		 * but second lookup with the bucket lock found it.
		 * This हाल is highly unlikely, but has to be dealt with:
		 * grab the element lock in addition to the bucket lock
		 * and update element in place
		 */
		copy_map_value_locked(map,
				      l_old->key + round_up(key_size, 8),
				      value, false);
		ret = 0;
		जाओ err;
	पूर्ण

	l_new = alloc_htab_elem(htab, key, value, key_size, hash, false, false,
				l_old);
	अगर (IS_ERR(l_new)) अणु
		/* all pre-allocated elements are in use or memory exhausted */
		ret = PTR_ERR(l_new);
		जाओ err;
	पूर्ण

	/* add new element to the head of the list, so that
	 * concurrent search will find it beक्रमe old elem
	 */
	hlist_nulls_add_head_rcu(&l_new->hash_node, head);
	अगर (l_old) अणु
		hlist_nulls_del_rcu(&l_old->hash_node);
		अगर (!htab_is_pपुनः_स्मृति(htab))
			मुक्त_htab_elem(htab, l_old);
	पूर्ण
	ret = 0;
err:
	htab_unlock_bucket(htab, b, hash, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक htab_lru_map_update_elem(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
				    u64 map_flags)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	काष्ठा htab_elem *l_new, *l_old = शून्य;
	काष्ठा hlist_nulls_head *head;
	अचिन्हित दीर्घ flags;
	काष्ठा bucket *b;
	u32 key_size, hash;
	पूर्णांक ret;

	अगर (unlikely(map_flags > BPF_EXIST))
		/* unknown flags */
		वापस -EINVAL;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held() && !rcu_पढ़ो_lock_trace_held());

	key_size = map->key_size;

	hash = htab_map_hash(key, key_size, htab->hashrnd);

	b = __select_bucket(htab, hash);
	head = &b->head;

	/* For LRU, we need to alloc beक्रमe taking bucket's
	 * spinlock because getting मुक्त nodes from LRU may need
	 * to हटाओ older elements from htab and this removal
	 * operation will need a bucket lock.
	 */
	l_new = pपुनः_स्मृति_lru_pop(htab, key, hash);
	अगर (!l_new)
		वापस -ENOMEM;
	स_नकल(l_new->key + round_up(map->key_size, 8), value, map->value_size);

	ret = htab_lock_bucket(htab, b, hash, &flags);
	अगर (ret)
		वापस ret;

	l_old = lookup_elem_raw(head, hash, key, key_size);

	ret = check_flags(htab, l_old, map_flags);
	अगर (ret)
		जाओ err;

	/* add new element to the head of the list, so that
	 * concurrent search will find it beक्रमe old elem
	 */
	hlist_nulls_add_head_rcu(&l_new->hash_node, head);
	अगर (l_old) अणु
		bpf_lru_node_set_ref(&l_new->lru_node);
		hlist_nulls_del_rcu(&l_old->hash_node);
	पूर्ण
	ret = 0;

err:
	htab_unlock_bucket(htab, b, hash, flags);

	अगर (ret)
		bpf_lru_push_मुक्त(&htab->lru, &l_new->lru_node);
	अन्यथा अगर (l_old)
		bpf_lru_push_मुक्त(&htab->lru, &l_old->lru_node);

	वापस ret;
पूर्ण

अटल पूर्णांक __htab_percpu_map_update_elem(काष्ठा bpf_map *map, व्योम *key,
					 व्योम *value, u64 map_flags,
					 bool onallcpus)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	काष्ठा htab_elem *l_new = शून्य, *l_old;
	काष्ठा hlist_nulls_head *head;
	अचिन्हित दीर्घ flags;
	काष्ठा bucket *b;
	u32 key_size, hash;
	पूर्णांक ret;

	अगर (unlikely(map_flags > BPF_EXIST))
		/* unknown flags */
		वापस -EINVAL;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held() && !rcu_पढ़ो_lock_trace_held());

	key_size = map->key_size;

	hash = htab_map_hash(key, key_size, htab->hashrnd);

	b = __select_bucket(htab, hash);
	head = &b->head;

	ret = htab_lock_bucket(htab, b, hash, &flags);
	अगर (ret)
		वापस ret;

	l_old = lookup_elem_raw(head, hash, key, key_size);

	ret = check_flags(htab, l_old, map_flags);
	अगर (ret)
		जाओ err;

	अगर (l_old) अणु
		/* per-cpu hash map can update value in-place */
		pcpu_copy_value(htab, htab_elem_get_ptr(l_old, key_size),
				value, onallcpus);
	पूर्ण अन्यथा अणु
		l_new = alloc_htab_elem(htab, key, value, key_size,
					hash, true, onallcpus, शून्य);
		अगर (IS_ERR(l_new)) अणु
			ret = PTR_ERR(l_new);
			जाओ err;
		पूर्ण
		hlist_nulls_add_head_rcu(&l_new->hash_node, head);
	पूर्ण
	ret = 0;
err:
	htab_unlock_bucket(htab, b, hash, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक __htab_lru_percpu_map_update_elem(काष्ठा bpf_map *map, व्योम *key,
					     व्योम *value, u64 map_flags,
					     bool onallcpus)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	काष्ठा htab_elem *l_new = शून्य, *l_old;
	काष्ठा hlist_nulls_head *head;
	अचिन्हित दीर्घ flags;
	काष्ठा bucket *b;
	u32 key_size, hash;
	पूर्णांक ret;

	अगर (unlikely(map_flags > BPF_EXIST))
		/* unknown flags */
		वापस -EINVAL;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held() && !rcu_पढ़ो_lock_trace_held());

	key_size = map->key_size;

	hash = htab_map_hash(key, key_size, htab->hashrnd);

	b = __select_bucket(htab, hash);
	head = &b->head;

	/* For LRU, we need to alloc beक्रमe taking bucket's
	 * spinlock because LRU's elem alloc may need
	 * to हटाओ older elem from htab and this removal
	 * operation will need a bucket lock.
	 */
	अगर (map_flags != BPF_EXIST) अणु
		l_new = pपुनः_स्मृति_lru_pop(htab, key, hash);
		अगर (!l_new)
			वापस -ENOMEM;
	पूर्ण

	ret = htab_lock_bucket(htab, b, hash, &flags);
	अगर (ret)
		वापस ret;

	l_old = lookup_elem_raw(head, hash, key, key_size);

	ret = check_flags(htab, l_old, map_flags);
	अगर (ret)
		जाओ err;

	अगर (l_old) अणु
		bpf_lru_node_set_ref(&l_old->lru_node);

		/* per-cpu hash map can update value in-place */
		pcpu_copy_value(htab, htab_elem_get_ptr(l_old, key_size),
				value, onallcpus);
	पूर्ण अन्यथा अणु
		pcpu_init_value(htab, htab_elem_get_ptr(l_new, key_size),
				value, onallcpus);
		hlist_nulls_add_head_rcu(&l_new->hash_node, head);
		l_new = शून्य;
	पूर्ण
	ret = 0;
err:
	htab_unlock_bucket(htab, b, hash, flags);
	अगर (l_new)
		bpf_lru_push_मुक्त(&htab->lru, &l_new->lru_node);
	वापस ret;
पूर्ण

अटल पूर्णांक htab_percpu_map_update_elem(काष्ठा bpf_map *map, व्योम *key,
				       व्योम *value, u64 map_flags)
अणु
	वापस __htab_percpu_map_update_elem(map, key, value, map_flags, false);
पूर्ण

अटल पूर्णांक htab_lru_percpu_map_update_elem(काष्ठा bpf_map *map, व्योम *key,
					   व्योम *value, u64 map_flags)
अणु
	वापस __htab_lru_percpu_map_update_elem(map, key, value, map_flags,
						 false);
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक htab_map_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	काष्ठा hlist_nulls_head *head;
	काष्ठा bucket *b;
	काष्ठा htab_elem *l;
	अचिन्हित दीर्घ flags;
	u32 hash, key_size;
	पूर्णांक ret;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held() && !rcu_पढ़ो_lock_trace_held());

	key_size = map->key_size;

	hash = htab_map_hash(key, key_size, htab->hashrnd);
	b = __select_bucket(htab, hash);
	head = &b->head;

	ret = htab_lock_bucket(htab, b, hash, &flags);
	अगर (ret)
		वापस ret;

	l = lookup_elem_raw(head, hash, key, key_size);

	अगर (l) अणु
		hlist_nulls_del_rcu(&l->hash_node);
		मुक्त_htab_elem(htab, l);
	पूर्ण अन्यथा अणु
		ret = -ENOENT;
	पूर्ण

	htab_unlock_bucket(htab, b, hash, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक htab_lru_map_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	काष्ठा hlist_nulls_head *head;
	काष्ठा bucket *b;
	काष्ठा htab_elem *l;
	अचिन्हित दीर्घ flags;
	u32 hash, key_size;
	पूर्णांक ret;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held() && !rcu_पढ़ो_lock_trace_held());

	key_size = map->key_size;

	hash = htab_map_hash(key, key_size, htab->hashrnd);
	b = __select_bucket(htab, hash);
	head = &b->head;

	ret = htab_lock_bucket(htab, b, hash, &flags);
	अगर (ret)
		वापस ret;

	l = lookup_elem_raw(head, hash, key, key_size);

	अगर (l)
		hlist_nulls_del_rcu(&l->hash_node);
	अन्यथा
		ret = -ENOENT;

	htab_unlock_bucket(htab, b, hash, flags);
	अगर (l)
		bpf_lru_push_मुक्त(&htab->lru, &l->lru_node);
	वापस ret;
पूर्ण

अटल व्योम delete_all_elements(काष्ठा bpf_htab *htab)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < htab->n_buckets; i++) अणु
		काष्ठा hlist_nulls_head *head = select_bucket(htab, i);
		काष्ठा hlist_nulls_node *n;
		काष्ठा htab_elem *l;

		hlist_nulls_क्रम_each_entry_safe(l, n, head, hash_node) अणु
			hlist_nulls_del_rcu(&l->hash_node);
			htab_elem_मुक्त(htab, l);
		पूर्ण
	पूर्ण
पूर्ण

/* Called when map->refcnt goes to zero, either from workqueue or from syscall */
अटल व्योम htab_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	पूर्णांक i;

	/* bpf_मुक्त_used_maps() or बंद(map_fd) will trigger this map_मुक्त callback.
	 * bpf_मुक्त_used_maps() is called after bpf prog is no दीर्घer executing.
	 * There is no need to synchronize_rcu() here to protect map elements.
	 */

	/* some of मुक्त_htab_elem() callbacks क्रम elements of this map may
	 * not have executed. Wait क्रम them.
	 */
	rcu_barrier();
	अगर (!htab_is_pपुनः_स्मृति(htab))
		delete_all_elements(htab);
	अन्यथा
		pपुनः_स्मृति_destroy(htab);

	मुक्त_percpu(htab->extra_elems);
	bpf_map_area_मुक्त(htab->buckets);
	क्रम (i = 0; i < HASHTAB_MAP_LOCK_COUNT; i++)
		मुक्त_percpu(htab->map_locked[i]);
	lockdep_unरेजिस्टर_key(&htab->lockdep_key);
	kमुक्त(htab);
पूर्ण

अटल व्योम htab_map_seq_show_elem(काष्ठा bpf_map *map, व्योम *key,
				   काष्ठा seq_file *m)
अणु
	व्योम *value;

	rcu_पढ़ो_lock();

	value = htab_map_lookup_elem(map, key);
	अगर (!value) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	btf_type_seq_show(map->btf, map->btf_key_type_id, key, m);
	seq_माला_दो(m, ": ");
	btf_type_seq_show(map->btf, map->btf_value_type_id, value, m);
	seq_माला_दो(m, "\n");

	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक
__htab_map_lookup_and_delete_batch(काष्ठा bpf_map *map,
				   स्थिर जोड़ bpf_attr *attr,
				   जोड़ bpf_attr __user *uattr,
				   bool करो_delete, bool is_lru_map,
				   bool is_percpu)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	u32 bucket_cnt, total, key_size, value_size, roundup_key_size;
	व्योम *keys = शून्य, *values = शून्य, *value, *dst_key, *dst_val;
	व्योम __user *uvalues = u64_to_user_ptr(attr->batch.values);
	व्योम __user *ukeys = u64_to_user_ptr(attr->batch.keys);
	व्योम __user *ubatch = u64_to_user_ptr(attr->batch.in_batch);
	u32 batch, max_count, size, bucket_size;
	काष्ठा htab_elem *node_to_मुक्त = शून्य;
	u64 elem_map_flags, map_flags;
	काष्ठा hlist_nulls_head *head;
	काष्ठा hlist_nulls_node *n;
	अचिन्हित दीर्घ flags = 0;
	bool locked = false;
	काष्ठा htab_elem *l;
	काष्ठा bucket *b;
	पूर्णांक ret = 0;

	elem_map_flags = attr->batch.elem_flags;
	अगर ((elem_map_flags & ~BPF_F_LOCK) ||
	    ((elem_map_flags & BPF_F_LOCK) && !map_value_has_spin_lock(map)))
		वापस -EINVAL;

	map_flags = attr->batch.flags;
	अगर (map_flags)
		वापस -EINVAL;

	max_count = attr->batch.count;
	अगर (!max_count)
		वापस 0;

	अगर (put_user(0, &uattr->batch.count))
		वापस -EFAULT;

	batch = 0;
	अगर (ubatch && copy_from_user(&batch, ubatch, माप(batch)))
		वापस -EFAULT;

	अगर (batch >= htab->n_buckets)
		वापस -ENOENT;

	key_size = htab->map.key_size;
	roundup_key_size = round_up(htab->map.key_size, 8);
	value_size = htab->map.value_size;
	size = round_up(value_size, 8);
	अगर (is_percpu)
		value_size = size * num_possible_cpus();
	total = 0;
	/* जबतक experimenting with hash tables with sizes ranging from 10 to
	 * 1000, it was observed that a bucket can have upto 5 entries.
	 */
	bucket_size = 5;

alloc:
	/* We cannot करो copy_from_user or copy_to_user inside
	 * the rcu_पढ़ो_lock. Allocate enough space here.
	 */
	keys = kvदो_स्मृति(key_size * bucket_size, GFP_USER | __GFP_NOWARN);
	values = kvदो_स्मृति(value_size * bucket_size, GFP_USER | __GFP_NOWARN);
	अगर (!keys || !values) अणु
		ret = -ENOMEM;
		जाओ after_loop;
	पूर्ण

again:
	bpf_disable_instrumentation();
	rcu_पढ़ो_lock();
again_nocopy:
	dst_key = keys;
	dst_val = values;
	b = &htab->buckets[batch];
	head = &b->head;
	/* करो not grab the lock unless need it (bucket_cnt > 0). */
	अगर (locked) अणु
		ret = htab_lock_bucket(htab, b, batch, &flags);
		अगर (ret)
			जाओ next_batch;
	पूर्ण

	bucket_cnt = 0;
	hlist_nulls_क्रम_each_entry_rcu(l, n, head, hash_node)
		bucket_cnt++;

	अगर (bucket_cnt && !locked) अणु
		locked = true;
		जाओ again_nocopy;
	पूर्ण

	अगर (bucket_cnt > (max_count - total)) अणु
		अगर (total == 0)
			ret = -ENOSPC;
		/* Note that since bucket_cnt > 0 here, it is implicit
		 * that the locked was grabbed, so release it.
		 */
		htab_unlock_bucket(htab, b, batch, flags);
		rcu_पढ़ो_unlock();
		bpf_enable_instrumentation();
		जाओ after_loop;
	पूर्ण

	अगर (bucket_cnt > bucket_size) अणु
		bucket_size = bucket_cnt;
		/* Note that since bucket_cnt > 0 here, it is implicit
		 * that the locked was grabbed, so release it.
		 */
		htab_unlock_bucket(htab, b, batch, flags);
		rcu_पढ़ो_unlock();
		bpf_enable_instrumentation();
		kvमुक्त(keys);
		kvमुक्त(values);
		जाओ alloc;
	पूर्ण

	/* Next block is only safe to run अगर you have grabbed the lock */
	अगर (!locked)
		जाओ next_batch;

	hlist_nulls_क्रम_each_entry_safe(l, n, head, hash_node) अणु
		स_नकल(dst_key, l->key, key_size);

		अगर (is_percpu) अणु
			पूर्णांक off = 0, cpu;
			व्योम __percpu *pptr;

			pptr = htab_elem_get_ptr(l, map->key_size);
			क्रम_each_possible_cpu(cpu) अणु
				bpf_दीर्घ_स_नकल(dst_val + off,
						per_cpu_ptr(pptr, cpu), size);
				off += size;
			पूर्ण
		पूर्ण अन्यथा अणु
			value = l->key + roundup_key_size;
			अगर (elem_map_flags & BPF_F_LOCK)
				copy_map_value_locked(map, dst_val, value,
						      true);
			अन्यथा
				copy_map_value(map, dst_val, value);
			check_and_init_map_lock(map, dst_val);
		पूर्ण
		अगर (करो_delete) अणु
			hlist_nulls_del_rcu(&l->hash_node);

			/* bpf_lru_push_मुक्त() will acquire lru_lock, which
			 * may cause deadlock. See comments in function
			 * pपुनः_स्मृति_lru_pop(). Let us करो bpf_lru_push_मुक्त()
			 * after releasing the bucket lock.
			 */
			अगर (is_lru_map) अणु
				l->batch_flink = node_to_मुक्त;
				node_to_मुक्त = l;
			पूर्ण अन्यथा अणु
				मुक्त_htab_elem(htab, l);
			पूर्ण
		पूर्ण
		dst_key += key_size;
		dst_val += value_size;
	पूर्ण

	htab_unlock_bucket(htab, b, batch, flags);
	locked = false;

	जबतक (node_to_मुक्त) अणु
		l = node_to_मुक्त;
		node_to_मुक्त = node_to_मुक्त->batch_flink;
		bpf_lru_push_मुक्त(&htab->lru, &l->lru_node);
	पूर्ण

next_batch:
	/* If we are not copying data, we can go to next bucket and aव्योम
	 * unlocking the rcu.
	 */
	अगर (!bucket_cnt && (batch + 1 < htab->n_buckets)) अणु
		batch++;
		जाओ again_nocopy;
	पूर्ण

	rcu_पढ़ो_unlock();
	bpf_enable_instrumentation();
	अगर (bucket_cnt && (copy_to_user(ukeys + total * key_size, keys,
	    key_size * bucket_cnt) ||
	    copy_to_user(uvalues + total * value_size, values,
	    value_size * bucket_cnt))) अणु
		ret = -EFAULT;
		जाओ after_loop;
	पूर्ण

	total += bucket_cnt;
	batch++;
	अगर (batch >= htab->n_buckets) अणु
		ret = -ENOENT;
		जाओ after_loop;
	पूर्ण
	जाओ again;

after_loop:
	अगर (ret == -EFAULT)
		जाओ out;

	/* copy # of entries and next batch */
	ubatch = u64_to_user_ptr(attr->batch.out_batch);
	अगर (copy_to_user(ubatch, &batch, माप(batch)) ||
	    put_user(total, &uattr->batch.count))
		ret = -EFAULT;

out:
	kvमुक्त(keys);
	kvमुक्त(values);
	वापस ret;
पूर्ण

अटल पूर्णांक
htab_percpu_map_lookup_batch(काष्ठा bpf_map *map, स्थिर जोड़ bpf_attr *attr,
			     जोड़ bpf_attr __user *uattr)
अणु
	वापस __htab_map_lookup_and_delete_batch(map, attr, uattr, false,
						  false, true);
पूर्ण

अटल पूर्णांक
htab_percpu_map_lookup_and_delete_batch(काष्ठा bpf_map *map,
					स्थिर जोड़ bpf_attr *attr,
					जोड़ bpf_attr __user *uattr)
अणु
	वापस __htab_map_lookup_and_delete_batch(map, attr, uattr, true,
						  false, true);
पूर्ण

अटल पूर्णांक
htab_map_lookup_batch(काष्ठा bpf_map *map, स्थिर जोड़ bpf_attr *attr,
		      जोड़ bpf_attr __user *uattr)
अणु
	वापस __htab_map_lookup_and_delete_batch(map, attr, uattr, false,
						  false, false);
पूर्ण

अटल पूर्णांक
htab_map_lookup_and_delete_batch(काष्ठा bpf_map *map,
				 स्थिर जोड़ bpf_attr *attr,
				 जोड़ bpf_attr __user *uattr)
अणु
	वापस __htab_map_lookup_and_delete_batch(map, attr, uattr, true,
						  false, false);
पूर्ण

अटल पूर्णांक
htab_lru_percpu_map_lookup_batch(काष्ठा bpf_map *map,
				 स्थिर जोड़ bpf_attr *attr,
				 जोड़ bpf_attr __user *uattr)
अणु
	वापस __htab_map_lookup_and_delete_batch(map, attr, uattr, false,
						  true, true);
पूर्ण

अटल पूर्णांक
htab_lru_percpu_map_lookup_and_delete_batch(काष्ठा bpf_map *map,
					    स्थिर जोड़ bpf_attr *attr,
					    जोड़ bpf_attr __user *uattr)
अणु
	वापस __htab_map_lookup_and_delete_batch(map, attr, uattr, true,
						  true, true);
पूर्ण

अटल पूर्णांक
htab_lru_map_lookup_batch(काष्ठा bpf_map *map, स्थिर जोड़ bpf_attr *attr,
			  जोड़ bpf_attr __user *uattr)
अणु
	वापस __htab_map_lookup_and_delete_batch(map, attr, uattr, false,
						  true, false);
पूर्ण

अटल पूर्णांक
htab_lru_map_lookup_and_delete_batch(काष्ठा bpf_map *map,
				     स्थिर जोड़ bpf_attr *attr,
				     जोड़ bpf_attr __user *uattr)
अणु
	वापस __htab_map_lookup_and_delete_batch(map, attr, uattr, true,
						  true, false);
पूर्ण

काष्ठा bpf_iter_seq_hash_map_info अणु
	काष्ठा bpf_map *map;
	काष्ठा bpf_htab *htab;
	व्योम *percpu_value_buf; // non-zero means percpu hash
	u32 bucket_id;
	u32 skip_elems;
पूर्ण;

अटल काष्ठा htab_elem *
bpf_hash_map_seq_find_next(काष्ठा bpf_iter_seq_hash_map_info *info,
			   काष्ठा htab_elem *prev_elem)
अणु
	स्थिर काष्ठा bpf_htab *htab = info->htab;
	u32 skip_elems = info->skip_elems;
	u32 bucket_id = info->bucket_id;
	काष्ठा hlist_nulls_head *head;
	काष्ठा hlist_nulls_node *n;
	काष्ठा htab_elem *elem;
	काष्ठा bucket *b;
	u32 i, count;

	अगर (bucket_id >= htab->n_buckets)
		वापस शून्य;

	/* try to find next elem in the same bucket */
	अगर (prev_elem) अणु
		/* no update/deletion on this bucket, prev_elem should be still valid
		 * and we won't skip elements.
		 */
		n = rcu_dereference_raw(hlist_nulls_next_rcu(&prev_elem->hash_node));
		elem = hlist_nulls_entry_safe(n, काष्ठा htab_elem, hash_node);
		अगर (elem)
			वापस elem;

		/* not found, unlock and go to the next bucket */
		b = &htab->buckets[bucket_id++];
		rcu_पढ़ो_unlock();
		skip_elems = 0;
	पूर्ण

	क्रम (i = bucket_id; i < htab->n_buckets; i++) अणु
		b = &htab->buckets[i];
		rcu_पढ़ो_lock();

		count = 0;
		head = &b->head;
		hlist_nulls_क्रम_each_entry_rcu(elem, n, head, hash_node) अणु
			अगर (count >= skip_elems) अणु
				info->bucket_id = i;
				info->skip_elems = count;
				वापस elem;
			पूर्ण
			count++;
		पूर्ण

		rcu_पढ़ो_unlock();
		skip_elems = 0;
	पूर्ण

	info->bucket_id = i;
	info->skip_elems = 0;
	वापस शून्य;
पूर्ण

अटल व्योम *bpf_hash_map_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_hash_map_info *info = seq->निजी;
	काष्ठा htab_elem *elem;

	elem = bpf_hash_map_seq_find_next(info, शून्य);
	अगर (!elem)
		वापस शून्य;

	अगर (*pos == 0)
		++*pos;
	वापस elem;
पूर्ण

अटल व्योम *bpf_hash_map_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_hash_map_info *info = seq->निजी;

	++*pos;
	++info->skip_elems;
	वापस bpf_hash_map_seq_find_next(info, v);
पूर्ण

अटल पूर्णांक __bpf_hash_map_seq_show(काष्ठा seq_file *seq, काष्ठा htab_elem *elem)
अणु
	काष्ठा bpf_iter_seq_hash_map_info *info = seq->निजी;
	u32 roundup_key_size, roundup_value_size;
	काष्ठा bpf_iter__bpf_map_elem ctx = अणुपूर्ण;
	काष्ठा bpf_map *map = info->map;
	काष्ठा bpf_iter_meta meta;
	पूर्णांक ret = 0, off = 0, cpu;
	काष्ठा bpf_prog *prog;
	व्योम __percpu *pptr;

	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, elem == शून्य);
	अगर (prog) अणु
		ctx.meta = &meta;
		ctx.map = info->map;
		अगर (elem) अणु
			roundup_key_size = round_up(map->key_size, 8);
			ctx.key = elem->key;
			अगर (!info->percpu_value_buf) अणु
				ctx.value = elem->key + roundup_key_size;
			पूर्ण अन्यथा अणु
				roundup_value_size = round_up(map->value_size, 8);
				pptr = htab_elem_get_ptr(elem, map->key_size);
				क्रम_each_possible_cpu(cpu) अणु
					bpf_दीर्घ_स_नकल(info->percpu_value_buf + off,
							per_cpu_ptr(pptr, cpu),
							roundup_value_size);
					off += roundup_value_size;
				पूर्ण
				ctx.value = info->percpu_value_buf;
			पूर्ण
		पूर्ण
		ret = bpf_iter_run_prog(prog, &ctx);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bpf_hash_map_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस __bpf_hash_map_seq_show(seq, v);
पूर्ण

अटल व्योम bpf_hash_map_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (!v)
		(व्योम)__bpf_hash_map_seq_show(seq, शून्य);
	अन्यथा
		rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक bpf_iter_init_hash_map(व्योम *priv_data,
				  काष्ठा bpf_iter_aux_info *aux)
अणु
	काष्ठा bpf_iter_seq_hash_map_info *seq_info = priv_data;
	काष्ठा bpf_map *map = aux->map;
	व्योम *value_buf;
	u32 buf_size;

	अगर (map->map_type == BPF_MAP_TYPE_PERCPU_HASH ||
	    map->map_type == BPF_MAP_TYPE_LRU_PERCPU_HASH) अणु
		buf_size = round_up(map->value_size, 8) * num_possible_cpus();
		value_buf = kदो_स्मृति(buf_size, GFP_USER | __GFP_NOWARN);
		अगर (!value_buf)
			वापस -ENOMEM;

		seq_info->percpu_value_buf = value_buf;
	पूर्ण

	seq_info->map = map;
	seq_info->htab = container_of(map, काष्ठा bpf_htab, map);
	वापस 0;
पूर्ण

अटल व्योम bpf_iter_fini_hash_map(व्योम *priv_data)
अणु
	काष्ठा bpf_iter_seq_hash_map_info *seq_info = priv_data;

	kमुक्त(seq_info->percpu_value_buf);
पूर्ण

अटल स्थिर काष्ठा seq_operations bpf_hash_map_seq_ops = अणु
	.start	= bpf_hash_map_seq_start,
	.next	= bpf_hash_map_seq_next,
	.stop	= bpf_hash_map_seq_stop,
	.show	= bpf_hash_map_seq_show,
पूर्ण;

अटल स्थिर काष्ठा bpf_iter_seq_info iter_seq_info = अणु
	.seq_ops		= &bpf_hash_map_seq_ops,
	.init_seq_निजी	= bpf_iter_init_hash_map,
	.fini_seq_निजी	= bpf_iter_fini_hash_map,
	.seq_priv_size		= माप(काष्ठा bpf_iter_seq_hash_map_info),
पूर्ण;

अटल पूर्णांक bpf_क्रम_each_hash_elem(काष्ठा bpf_map *map, व्योम *callback_fn,
				  व्योम *callback_ctx, u64 flags)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	काष्ठा hlist_nulls_head *head;
	काष्ठा hlist_nulls_node *n;
	काष्ठा htab_elem *elem;
	u32 roundup_key_size;
	पूर्णांक i, num_elems = 0;
	व्योम __percpu *pptr;
	काष्ठा bucket *b;
	व्योम *key, *val;
	bool is_percpu;
	u64 ret = 0;

	अगर (flags != 0)
		वापस -EINVAL;

	is_percpu = htab_is_percpu(htab);

	roundup_key_size = round_up(map->key_size, 8);
	/* disable migration so percpu value prepared here will be the
	 * same as the one seen by the bpf program with bpf_map_lookup_elem().
	 */
	अगर (is_percpu)
		migrate_disable();
	क्रम (i = 0; i < htab->n_buckets; i++) अणु
		b = &htab->buckets[i];
		rcu_पढ़ो_lock();
		head = &b->head;
		hlist_nulls_क्रम_each_entry_rcu(elem, n, head, hash_node) अणु
			key = elem->key;
			अगर (is_percpu) अणु
				/* current cpu value क्रम percpu map */
				pptr = htab_elem_get_ptr(elem, map->key_size);
				val = this_cpu_ptr(pptr);
			पूर्ण अन्यथा अणु
				val = elem->key + roundup_key_size;
			पूर्ण
			num_elems++;
			ret = BPF_CAST_CALL(callback_fn)((u64)(दीर्घ)map,
					(u64)(दीर्घ)key, (u64)(दीर्घ)val,
					(u64)(दीर्घ)callback_ctx, 0);
			/* वापस value: 0 - जारी, 1 - stop and वापस */
			अगर (ret) अणु
				rcu_पढ़ो_unlock();
				जाओ out;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
out:
	अगर (is_percpu)
		migrate_enable();
	वापस num_elems;
पूर्ण

अटल पूर्णांक htab_map_btf_id;
स्थिर काष्ठा bpf_map_ops htab_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = htab_map_alloc_check,
	.map_alloc = htab_map_alloc,
	.map_मुक्त = htab_map_मुक्त,
	.map_get_next_key = htab_map_get_next_key,
	.map_lookup_elem = htab_map_lookup_elem,
	.map_update_elem = htab_map_update_elem,
	.map_delete_elem = htab_map_delete_elem,
	.map_gen_lookup = htab_map_gen_lookup,
	.map_seq_show_elem = htab_map_seq_show_elem,
	.map_set_क्रम_each_callback_args = map_set_क्रम_each_callback_args,
	.map_क्रम_each_callback = bpf_क्रम_each_hash_elem,
	BATCH_OPS(htab),
	.map_btf_name = "bpf_htab",
	.map_btf_id = &htab_map_btf_id,
	.iter_seq_info = &iter_seq_info,
पूर्ण;

अटल पूर्णांक htab_lru_map_btf_id;
स्थिर काष्ठा bpf_map_ops htab_lru_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = htab_map_alloc_check,
	.map_alloc = htab_map_alloc,
	.map_मुक्त = htab_map_मुक्त,
	.map_get_next_key = htab_map_get_next_key,
	.map_lookup_elem = htab_lru_map_lookup_elem,
	.map_lookup_elem_sys_only = htab_lru_map_lookup_elem_sys,
	.map_update_elem = htab_lru_map_update_elem,
	.map_delete_elem = htab_lru_map_delete_elem,
	.map_gen_lookup = htab_lru_map_gen_lookup,
	.map_seq_show_elem = htab_map_seq_show_elem,
	.map_set_क्रम_each_callback_args = map_set_क्रम_each_callback_args,
	.map_क्रम_each_callback = bpf_क्रम_each_hash_elem,
	BATCH_OPS(htab_lru),
	.map_btf_name = "bpf_htab",
	.map_btf_id = &htab_lru_map_btf_id,
	.iter_seq_info = &iter_seq_info,
पूर्ण;

/* Called from eBPF program */
अटल व्योम *htab_percpu_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा htab_elem *l = __htab_map_lookup_elem(map, key);

	अगर (l)
		वापस this_cpu_ptr(htab_elem_get_ptr(l, map->key_size));
	अन्यथा
		वापस शून्य;
पूर्ण

अटल व्योम *htab_lru_percpu_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा htab_elem *l = __htab_map_lookup_elem(map, key);

	अगर (l) अणु
		bpf_lru_node_set_ref(&l->lru_node);
		वापस this_cpu_ptr(htab_elem_get_ptr(l, map->key_size));
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक bpf_percpu_hash_copy(काष्ठा bpf_map *map, व्योम *key, व्योम *value)
अणु
	काष्ठा htab_elem *l;
	व्योम __percpu *pptr;
	पूर्णांक ret = -ENOENT;
	पूर्णांक cpu, off = 0;
	u32 size;

	/* per_cpu areas are zero-filled and bpf programs can only
	 * access 'value_size' of them, so copying rounded areas
	 * will not leak any kernel data
	 */
	size = round_up(map->value_size, 8);
	rcu_पढ़ो_lock();
	l = __htab_map_lookup_elem(map, key);
	अगर (!l)
		जाओ out;
	/* We करो not mark LRU map element here in order to not mess up
	 * eviction heuristics when user space करोes a map walk.
	 */
	pptr = htab_elem_get_ptr(l, map->key_size);
	क्रम_each_possible_cpu(cpu) अणु
		bpf_दीर्घ_स_नकल(value + off,
				per_cpu_ptr(pptr, cpu), size);
		off += size;
	पूर्ण
	ret = 0;
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

पूर्णांक bpf_percpu_hash_update(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
			   u64 map_flags)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	अगर (htab_is_lru(htab))
		ret = __htab_lru_percpu_map_update_elem(map, key, value,
							map_flags, true);
	अन्यथा
		ret = __htab_percpu_map_update_elem(map, key, value, map_flags,
						    true);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल व्योम htab_percpu_map_seq_show_elem(काष्ठा bpf_map *map, व्योम *key,
					  काष्ठा seq_file *m)
अणु
	काष्ठा htab_elem *l;
	व्योम __percpu *pptr;
	पूर्णांक cpu;

	rcu_पढ़ो_lock();

	l = __htab_map_lookup_elem(map, key);
	अगर (!l) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	btf_type_seq_show(map->btf, map->btf_key_type_id, key, m);
	seq_माला_दो(m, ": {\n");
	pptr = htab_elem_get_ptr(l, map->key_size);
	क्रम_each_possible_cpu(cpu) अणु
		seq_म_लिखो(m, "\tcpu%d: ", cpu);
		btf_type_seq_show(map->btf, map->btf_value_type_id,
				  per_cpu_ptr(pptr, cpu), m);
		seq_माला_दो(m, "\n");
	पूर्ण
	seq_माला_दो(m, "}\n");

	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक htab_percpu_map_btf_id;
स्थिर काष्ठा bpf_map_ops htab_percpu_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = htab_map_alloc_check,
	.map_alloc = htab_map_alloc,
	.map_मुक्त = htab_map_मुक्त,
	.map_get_next_key = htab_map_get_next_key,
	.map_lookup_elem = htab_percpu_map_lookup_elem,
	.map_update_elem = htab_percpu_map_update_elem,
	.map_delete_elem = htab_map_delete_elem,
	.map_seq_show_elem = htab_percpu_map_seq_show_elem,
	.map_set_क्रम_each_callback_args = map_set_क्रम_each_callback_args,
	.map_क्रम_each_callback = bpf_क्रम_each_hash_elem,
	BATCH_OPS(htab_percpu),
	.map_btf_name = "bpf_htab",
	.map_btf_id = &htab_percpu_map_btf_id,
	.iter_seq_info = &iter_seq_info,
पूर्ण;

अटल पूर्णांक htab_lru_percpu_map_btf_id;
स्थिर काष्ठा bpf_map_ops htab_lru_percpu_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = htab_map_alloc_check,
	.map_alloc = htab_map_alloc,
	.map_मुक्त = htab_map_मुक्त,
	.map_get_next_key = htab_map_get_next_key,
	.map_lookup_elem = htab_lru_percpu_map_lookup_elem,
	.map_update_elem = htab_lru_percpu_map_update_elem,
	.map_delete_elem = htab_lru_map_delete_elem,
	.map_seq_show_elem = htab_percpu_map_seq_show_elem,
	.map_set_क्रम_each_callback_args = map_set_क्रम_each_callback_args,
	.map_क्रम_each_callback = bpf_क्रम_each_hash_elem,
	BATCH_OPS(htab_lru_percpu),
	.map_btf_name = "bpf_htab",
	.map_btf_id = &htab_lru_percpu_map_btf_id,
	.iter_seq_info = &iter_seq_info,
पूर्ण;

अटल पूर्णांक fd_htab_map_alloc_check(जोड़ bpf_attr *attr)
अणु
	अगर (attr->value_size != माप(u32))
		वापस -EINVAL;
	वापस htab_map_alloc_check(attr);
पूर्ण

अटल व्योम fd_htab_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_htab *htab = container_of(map, काष्ठा bpf_htab, map);
	काष्ठा hlist_nulls_node *n;
	काष्ठा hlist_nulls_head *head;
	काष्ठा htab_elem *l;
	पूर्णांक i;

	क्रम (i = 0; i < htab->n_buckets; i++) अणु
		head = select_bucket(htab, i);

		hlist_nulls_क्रम_each_entry_safe(l, n, head, hash_node) अणु
			व्योम *ptr = fd_htab_map_get_ptr(map, l);

			map->ops->map_fd_put_ptr(ptr);
		पूर्ण
	पूर्ण

	htab_map_मुक्त(map);
पूर्ण

/* only called from syscall */
पूर्णांक bpf_fd_htab_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key, u32 *value)
अणु
	व्योम **ptr;
	पूर्णांक ret = 0;

	अगर (!map->ops->map_fd_sys_lookup_elem)
		वापस -ENOTSUPP;

	rcu_पढ़ो_lock();
	ptr = htab_map_lookup_elem(map, key);
	अगर (ptr)
		*value = map->ops->map_fd_sys_lookup_elem(READ_ONCE(*ptr));
	अन्यथा
		ret = -ENOENT;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/* only called from syscall */
पूर्णांक bpf_fd_htab_map_update_elem(काष्ठा bpf_map *map, काष्ठा file *map_file,
				व्योम *key, व्योम *value, u64 map_flags)
अणु
	व्योम *ptr;
	पूर्णांक ret;
	u32 ufd = *(u32 *)value;

	ptr = map->ops->map_fd_get_ptr(map, map_file, ufd);
	अगर (IS_ERR(ptr))
		वापस PTR_ERR(ptr);

	ret = htab_map_update_elem(map, key, &ptr, map_flags);
	अगर (ret)
		map->ops->map_fd_put_ptr(ptr);

	वापस ret;
पूर्ण

अटल काष्ठा bpf_map *htab_of_map_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_map *map, *inner_map_meta;

	inner_map_meta = bpf_map_meta_alloc(attr->inner_map_fd);
	अगर (IS_ERR(inner_map_meta))
		वापस inner_map_meta;

	map = htab_map_alloc(attr);
	अगर (IS_ERR(map)) अणु
		bpf_map_meta_मुक्त(inner_map_meta);
		वापस map;
	पूर्ण

	map->inner_map_meta = inner_map_meta;

	वापस map;
पूर्ण

अटल व्योम *htab_of_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_map **inner_map  = htab_map_lookup_elem(map, key);

	अगर (!inner_map)
		वापस शून्य;

	वापस READ_ONCE(*inner_map);
पूर्ण

अटल पूर्णांक htab_of_map_gen_lookup(काष्ठा bpf_map *map,
				  काष्ठा bpf_insn *insn_buf)
अणु
	काष्ठा bpf_insn *insn = insn_buf;
	स्थिर पूर्णांक ret = BPF_REG_0;

	BUILD_BUG_ON(!__same_type(&__htab_map_lookup_elem,
		     (व्योम *(*)(काष्ठा bpf_map *map, व्योम *key))शून्य));
	*insn++ = BPF_EMIT_CALL(BPF_CAST_CALL(__htab_map_lookup_elem));
	*insn++ = BPF_JMP_IMM(BPF_JEQ, ret, 0, 2);
	*insn++ = BPF_ALU64_IMM(BPF_ADD, ret,
				दुरत्व(काष्ठा htab_elem, key) +
				round_up(map->key_size, 8));
	*insn++ = BPF_LDX_MEM(BPF_DW, ret, ret, 0);

	वापस insn - insn_buf;
पूर्ण

अटल व्योम htab_of_map_मुक्त(काष्ठा bpf_map *map)
अणु
	bpf_map_meta_मुक्त(map->inner_map_meta);
	fd_htab_map_मुक्त(map);
पूर्ण

अटल पूर्णांक htab_of_maps_map_btf_id;
स्थिर काष्ठा bpf_map_ops htab_of_maps_map_ops = अणु
	.map_alloc_check = fd_htab_map_alloc_check,
	.map_alloc = htab_of_map_alloc,
	.map_मुक्त = htab_of_map_मुक्त,
	.map_get_next_key = htab_map_get_next_key,
	.map_lookup_elem = htab_of_map_lookup_elem,
	.map_delete_elem = htab_map_delete_elem,
	.map_fd_get_ptr = bpf_map_fd_get_ptr,
	.map_fd_put_ptr = bpf_map_fd_put_ptr,
	.map_fd_sys_lookup_elem = bpf_map_fd_sys_lookup_elem,
	.map_gen_lookup = htab_of_map_gen_lookup,
	.map_check_btf = map_check_no_btf,
	.map_btf_name = "bpf_htab",
	.map_btf_id = &htab_of_maps_map_btf_id,
पूर्ण;
