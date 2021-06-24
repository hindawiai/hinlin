<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Resizable, Scalable, Concurrent Hash Table
 *
 * Simple काष्ठाures that might be needed in include
 * files.
 */

#अगर_अघोषित _LINUX_RHASHTABLE_TYPES_H
#घोषणा _LINUX_RHASHTABLE_TYPES_H

#समावेश <linux/atomic.h>
#समावेश <linux/compiler.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>

काष्ठा rhash_head अणु
	काष्ठा rhash_head __rcu		*next;
पूर्ण;

काष्ठा rhlist_head अणु
	काष्ठा rhash_head		rhead;
	काष्ठा rhlist_head __rcu	*next;
पूर्ण;

काष्ठा bucket_table;

/**
 * काष्ठा rhashtable_compare_arg - Key क्रम the function rhashtable_compare
 * @ht: Hash table
 * @key: Key to compare against
 */
काष्ठा rhashtable_compare_arg अणु
	काष्ठा rhashtable *ht;
	स्थिर व्योम *key;
पूर्ण;

प्रकार u32 (*rht_hashfn_t)(स्थिर व्योम *data, u32 len, u32 seed);
प्रकार u32 (*rht_obj_hashfn_t)(स्थिर व्योम *data, u32 len, u32 seed);
प्रकार पूर्णांक (*rht_obj_cmpfn_t)(काष्ठा rhashtable_compare_arg *arg,
			       स्थिर व्योम *obj);

/**
 * काष्ठा rhashtable_params - Hash table स्थिरruction parameters
 * @nelem_hपूर्णांक: Hपूर्णांक on number of elements, should be 75% of desired size
 * @key_len: Length of key
 * @key_offset: Offset of key in काष्ठा to be hashed
 * @head_offset: Offset of rhash_head in काष्ठा to be hashed
 * @max_size: Maximum size जबतक expanding
 * @min_size: Minimum size जबतक shrinking
 * @स्वतःmatic_shrinking: Enable स्वतःmatic shrinking of tables
 * @hashfn: Hash function (शेष: jhash2 अगर !(key_len % 4), or jhash)
 * @obj_hashfn: Function to hash object
 * @obj_cmpfn: Function to compare key with object
 */
काष्ठा rhashtable_params अणु
	u16			nelem_hपूर्णांक;
	u16			key_len;
	u16			key_offset;
	u16			head_offset;
	अचिन्हित पूर्णांक		max_size;
	u16			min_size;
	bool			स्वतःmatic_shrinking;
	rht_hashfn_t		hashfn;
	rht_obj_hashfn_t	obj_hashfn;
	rht_obj_cmpfn_t		obj_cmpfn;
पूर्ण;

/**
 * काष्ठा rhashtable - Hash table handle
 * @tbl: Bucket table
 * @key_len: Key length क्रम hashfn
 * @max_elems: Maximum number of elements in table
 * @p: Configuration parameters
 * @rhlist: True अगर this is an rhltable
 * @run_work: Deferred worker to expand/shrink asynchronously
 * @mutex: Mutex to protect current/future table swapping
 * @lock: Spin lock to protect walker list
 * @nelems: Number of elements in table
 */
काष्ठा rhashtable अणु
	काष्ठा bucket_table __rcu	*tbl;
	अचिन्हित पूर्णांक			key_len;
	अचिन्हित पूर्णांक			max_elems;
	काष्ठा rhashtable_params	p;
	bool				rhlist;
	काष्ठा work_काष्ठा		run_work;
	काष्ठा mutex                    mutex;
	spinlock_t			lock;
	atomic_t			nelems;
पूर्ण;

/**
 * काष्ठा rhltable - Hash table with duplicate objects in a list
 * @ht: Underlying rhtable
 */
काष्ठा rhltable अणु
	काष्ठा rhashtable ht;
पूर्ण;

/**
 * काष्ठा rhashtable_walker - Hash table walker
 * @list: List entry on list of walkers
 * @tbl: The table that we were walking over
 */
काष्ठा rhashtable_walker अणु
	काष्ठा list_head list;
	काष्ठा bucket_table *tbl;
पूर्ण;

/**
 * काष्ठा rhashtable_iter - Hash table iterator
 * @ht: Table to iterate through
 * @p: Current poपूर्णांकer
 * @list: Current hash list poपूर्णांकer
 * @walker: Associated rhashtable walker
 * @slot: Current slot
 * @skip: Number of entries to skip in slot
 */
काष्ठा rhashtable_iter अणु
	काष्ठा rhashtable *ht;
	काष्ठा rhash_head *p;
	काष्ठा rhlist_head *list;
	काष्ठा rhashtable_walker walker;
	अचिन्हित पूर्णांक slot;
	अचिन्हित पूर्णांक skip;
	bool end_of_table;
पूर्ण;

पूर्णांक rhashtable_init(काष्ठा rhashtable *ht,
		    स्थिर काष्ठा rhashtable_params *params);
पूर्णांक rhltable_init(काष्ठा rhltable *hlt,
		  स्थिर काष्ठा rhashtable_params *params);

#पूर्ण_अगर /* _LINUX_RHASHTABLE_TYPES_H */
