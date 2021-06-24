<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2001 Momchil Velikov
 * Portions Copyright (C) 2001 Christoph Hellwig
 * Copyright (C) 2006 Nick Piggin
 * Copyright (C) 2012 Konstantin Khlebnikov
 */
#अगर_अघोषित _LINUX_RADIX_TREE_H
#घोषणा _LINUX_RADIX_TREE_H

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/percpu.h>
#समावेश <linux/preempt.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/xarray.h>
#समावेश <linux/local_lock.h>

/* Keep unconverted code working */
#घोषणा radix_tree_root		xarray
#घोषणा radix_tree_node		xa_node

काष्ठा radix_tree_preload अणु
	local_lock_t lock;
	अचिन्हित nr;
	/* nodes->parent poपूर्णांकs to next pपुनः_स्मृतिated node */
	काष्ठा radix_tree_node *nodes;
पूर्ण;
DECLARE_PER_CPU(काष्ठा radix_tree_preload, radix_tree_preloads);

/*
 * The bottom two bits of the slot determine how the reमुख्यing bits in the
 * slot are पूर्णांकerpreted:
 *
 * 00 - data poपूर्णांकer
 * 10 - पूर्णांकernal entry
 * x1 - value entry
 *
 * The पूर्णांकernal entry may be a poपूर्णांकer to the next level in the tree, a
 * sibling entry, or an indicator that the entry in this slot has been moved
 * to another location in the tree and the lookup should be restarted.  While
 * शून्य fits the 'data pointer' pattern, it means that there is no entry in
 * the tree क्रम this index (no matter what level of the tree it is found at).
 * This means that storing a शून्य entry in the tree is the same as deleting
 * the entry from the tree.
 */
#घोषणा RADIX_TREE_ENTRY_MASK		3UL
#घोषणा RADIX_TREE_INTERNAL_NODE	2UL

अटल अंतरभूत bool radix_tree_is_पूर्णांकernal_node(व्योम *ptr)
अणु
	वापस ((अचिन्हित दीर्घ)ptr & RADIX_TREE_ENTRY_MASK) ==
				RADIX_TREE_INTERNAL_NODE;
पूर्ण

/*** radix-tree API starts here ***/

#घोषणा RADIX_TREE_MAP_SHIFT	XA_CHUNK_SHIFT
#घोषणा RADIX_TREE_MAP_SIZE	(1UL << RADIX_TREE_MAP_SHIFT)
#घोषणा RADIX_TREE_MAP_MASK	(RADIX_TREE_MAP_SIZE-1)

#घोषणा RADIX_TREE_MAX_TAGS	XA_MAX_MARKS
#घोषणा RADIX_TREE_TAG_LONGS	XA_MARK_LONGS

#घोषणा RADIX_TREE_INDEX_BITS  (8 /* अक्षर_बिट */ * माप(अचिन्हित दीर्घ))
#घोषणा RADIX_TREE_MAX_PATH (DIV_ROUND_UP(RADIX_TREE_INDEX_BITS, \
					  RADIX_TREE_MAP_SHIFT))

/* The IDR tag is stored in the low bits of xa_flags */
#घोषणा ROOT_IS_IDR	((__क्रमce gfp_t)4)
/* The top bits of xa_flags are used to store the root tags */
#घोषणा ROOT_TAG_SHIFT	(__GFP_BITS_SHIFT)

#घोषणा RADIX_TREE_INIT(name, mask)	XARRAY_INIT(name, mask)

#घोषणा RADIX_TREE(name, mask) \
	काष्ठा radix_tree_root name = RADIX_TREE_INIT(name, mask)

#घोषणा INIT_RADIX_TREE(root, mask) xa_init_flags(root, mask)

अटल अंतरभूत bool radix_tree_empty(स्थिर काष्ठा radix_tree_root *root)
अणु
	वापस root->xa_head == शून्य;
पूर्ण

/**
 * काष्ठा radix_tree_iter - radix tree iterator state
 *
 * @index:	index of current slot
 * @next_index:	one beyond the last index क्रम this chunk
 * @tags:	bit-mask क्रम tag-iterating
 * @node:	node that contains current slot
 *
 * This radix tree iterator works in terms of "chunks" of slots.  A chunk is a
 * subपूर्णांकerval of slots contained within one radix tree leaf node.  It is
 * described by a poपूर्णांकer to its first slot and a काष्ठा radix_tree_iter
 * which holds the chunk's position in the tree and its size.  For tagged
 * iteration radix_tree_iter also holds the slots' bit-mask क्रम one chosen
 * radix tree tag.
 */
काष्ठा radix_tree_iter अणु
	अचिन्हित दीर्घ	index;
	अचिन्हित दीर्घ	next_index;
	अचिन्हित दीर्घ	tags;
	काष्ठा radix_tree_node *node;
पूर्ण;

/**
 * Radix-tree synchronization
 *
 * The radix-tree API requires that users provide all synchronisation (with
 * specअगरic exceptions, noted below).
 *
 * Synchronization of access to the data items being stored in the tree, and
 * management of their lअगरeबार must be completely managed by API users.
 *
 * For API usage, in general,
 * - any function _modअगरying_ the tree or tags (inserting or deleting
 *   items, setting or clearing tags) must exclude other modअगरications, and
 *   exclude any functions पढ़ोing the tree.
 * - any function _पढ़ोing_ the tree or tags (looking up items or tags,
 *   gang lookups) must exclude modअगरications to the tree, but may occur
 *   concurrently with other पढ़ोers.
 *
 * The notable exceptions to this rule are the following functions:
 * __radix_tree_lookup
 * radix_tree_lookup
 * radix_tree_lookup_slot
 * radix_tree_tag_get
 * radix_tree_gang_lookup
 * radix_tree_gang_lookup_tag
 * radix_tree_gang_lookup_tag_slot
 * radix_tree_tagged
 *
 * The first 7 functions are able to be called locklessly, using RCU. The
 * caller must ensure calls to these functions are made within rcu_पढ़ो_lock()
 * regions. Other पढ़ोers (lock-मुक्त or otherwise) and modअगरications may be
 * running concurrently.
 *
 * It is still required that the caller manage the synchronization and lअगरeबार
 * of the items. So अगर RCU lock-मुक्त lookups are used, typically this would mean
 * that the items have their own locks, or are amenable to lock-मुक्त access; and
 * that the items are मुक्तd by RCU (or only मुक्तd after having been deleted from
 * the radix tree *and* a synchronize_rcu() grace period).
 *
 * (Note, rcu_assign_poपूर्णांकer and rcu_dereference are not needed to control
 * access to data items when inserting पूर्णांकo or looking up from the radix tree)
 *
 * Note that the value वापसed by radix_tree_tag_get() may not be relied upon
 * अगर only the RCU पढ़ो lock is held.  Functions to set/clear tags and to
 * delete nodes running concurrently with it may affect its result such that
 * two consecutive पढ़ोs in the same locked section may वापस dअगरferent
 * values.  If reliability is required, modअगरication functions must also be
 * excluded from concurrency.
 *
 * radix_tree_tagged is able to be called without locking or RCU.
 */

/**
 * radix_tree_deref_slot - dereference a slot
 * @slot: slot poपूर्णांकer, वापसed by radix_tree_lookup_slot
 *
 * For use with radix_tree_lookup_slot().  Caller must hold tree at least पढ़ो
 * locked across slot lookup and dereference. Not required अगर ग_लिखो lock is
 * held (ie. items cannot be concurrently inserted).
 *
 * radix_tree_deref_retry must be used to confirm validity of the poपूर्णांकer अगर
 * only the पढ़ो lock is held.
 *
 * Return: entry stored in that slot.
 */
अटल अंतरभूत व्योम *radix_tree_deref_slot(व्योम __rcu **slot)
अणु
	वापस rcu_dereference(*slot);
पूर्ण

/**
 * radix_tree_deref_slot_रक्षित - dereference a slot with tree lock held
 * @slot: slot poपूर्णांकer, वापसed by radix_tree_lookup_slot
 *
 * Similar to radix_tree_deref_slot.  The caller करोes not hold the RCU पढ़ो
 * lock but it must hold the tree lock to prevent parallel updates.
 *
 * Return: entry stored in that slot.
 */
अटल अंतरभूत व्योम *radix_tree_deref_slot_रक्षित(व्योम __rcu **slot,
							spinlock_t *treelock)
अणु
	वापस rcu_dereference_रक्षित(*slot, lockdep_is_held(treelock));
पूर्ण

/**
 * radix_tree_deref_retry	- check radix_tree_deref_slot
 * @arg:	poपूर्णांकer वापसed by radix_tree_deref_slot
 * Returns:	0 अगर retry is not required, otherwise retry is required
 *
 * radix_tree_deref_retry must be used with radix_tree_deref_slot.
 */
अटल अंतरभूत पूर्णांक radix_tree_deref_retry(व्योम *arg)
अणु
	वापस unlikely(radix_tree_is_पूर्णांकernal_node(arg));
पूर्ण

/**
 * radix_tree_exception	- radix_tree_deref_slot वापसed either exception?
 * @arg:	value वापसed by radix_tree_deref_slot
 * Returns:	0 अगर well-aligned poपूर्णांकer, non-0 अगर either kind of exception.
 */
अटल अंतरभूत पूर्णांक radix_tree_exception(व्योम *arg)
अणु
	वापस unlikely((अचिन्हित दीर्घ)arg & RADIX_TREE_ENTRY_MASK);
पूर्ण

पूर्णांक radix_tree_insert(काष्ठा radix_tree_root *, अचिन्हित दीर्घ index,
			व्योम *);
व्योम *__radix_tree_lookup(स्थिर काष्ठा radix_tree_root *, अचिन्हित दीर्घ index,
			  काष्ठा radix_tree_node **nodep, व्योम __rcu ***slotp);
व्योम *radix_tree_lookup(स्थिर काष्ठा radix_tree_root *, अचिन्हित दीर्घ);
व्योम __rcu **radix_tree_lookup_slot(स्थिर काष्ठा radix_tree_root *,
					अचिन्हित दीर्घ index);
व्योम __radix_tree_replace(काष्ठा radix_tree_root *, काष्ठा radix_tree_node *,
			  व्योम __rcu **slot, व्योम *entry);
व्योम radix_tree_iter_replace(काष्ठा radix_tree_root *,
		स्थिर काष्ठा radix_tree_iter *, व्योम __rcu **slot, व्योम *entry);
व्योम radix_tree_replace_slot(काष्ठा radix_tree_root *,
			     व्योम __rcu **slot, व्योम *entry);
व्योम radix_tree_iter_delete(काष्ठा radix_tree_root *,
			काष्ठा radix_tree_iter *iter, व्योम __rcu **slot);
व्योम *radix_tree_delete_item(काष्ठा radix_tree_root *, अचिन्हित दीर्घ, व्योम *);
व्योम *radix_tree_delete(काष्ठा radix_tree_root *, अचिन्हित दीर्घ);
अचिन्हित पूर्णांक radix_tree_gang_lookup(स्थिर काष्ठा radix_tree_root *,
			व्योम **results, अचिन्हित दीर्घ first_index,
			अचिन्हित पूर्णांक max_items);
पूर्णांक radix_tree_preload(gfp_t gfp_mask);
पूर्णांक radix_tree_maybe_preload(gfp_t gfp_mask);
व्योम radix_tree_init(व्योम);
व्योम *radix_tree_tag_set(काष्ठा radix_tree_root *,
			अचिन्हित दीर्घ index, अचिन्हित पूर्णांक tag);
व्योम *radix_tree_tag_clear(काष्ठा radix_tree_root *,
			अचिन्हित दीर्घ index, अचिन्हित पूर्णांक tag);
पूर्णांक radix_tree_tag_get(स्थिर काष्ठा radix_tree_root *,
			अचिन्हित दीर्घ index, अचिन्हित पूर्णांक tag);
व्योम radix_tree_iter_tag_clear(काष्ठा radix_tree_root *,
		स्थिर काष्ठा radix_tree_iter *iter, अचिन्हित पूर्णांक tag);
अचिन्हित पूर्णांक radix_tree_gang_lookup_tag(स्थिर काष्ठा radix_tree_root *,
		व्योम **results, अचिन्हित दीर्घ first_index,
		अचिन्हित पूर्णांक max_items, अचिन्हित पूर्णांक tag);
अचिन्हित पूर्णांक radix_tree_gang_lookup_tag_slot(स्थिर काष्ठा radix_tree_root *,
		व्योम __rcu ***results, अचिन्हित दीर्घ first_index,
		अचिन्हित पूर्णांक max_items, अचिन्हित पूर्णांक tag);
पूर्णांक radix_tree_tagged(स्थिर काष्ठा radix_tree_root *, अचिन्हित पूर्णांक tag);

अटल अंतरभूत व्योम radix_tree_preload_end(व्योम)
अणु
	local_unlock(&radix_tree_preloads.lock);
पूर्ण

व्योम __rcu **idr_get_मुक्त(काष्ठा radix_tree_root *root,
			      काष्ठा radix_tree_iter *iter, gfp_t gfp,
			      अचिन्हित दीर्घ max);

क्रमागत अणु
	RADIX_TREE_ITER_TAG_MASK = 0x0f,	/* tag index in lower nybble */
	RADIX_TREE_ITER_TAGGED   = 0x10,	/* lookup tagged slots */
	RADIX_TREE_ITER_CONTIG   = 0x20,	/* stop at first hole */
पूर्ण;

/**
 * radix_tree_iter_init - initialize radix tree iterator
 *
 * @iter:	poपूर्णांकer to iterator state
 * @start:	iteration starting index
 * Returns:	शून्य
 */
अटल __always_अंतरभूत व्योम __rcu **
radix_tree_iter_init(काष्ठा radix_tree_iter *iter, अचिन्हित दीर्घ start)
अणु
	/*
	 * Leave iter->tags uninitialized. radix_tree_next_chunk() will fill it
	 * in the हाल of a successful tagged chunk lookup.  If the lookup was
	 * unsuccessful or non-tagged then nobody cares about ->tags.
	 *
	 * Set index to zero to bypass next_index overflow protection.
	 * See the comment in radix_tree_next_chunk() क्रम details.
	 */
	iter->index = 0;
	iter->next_index = start;
	वापस शून्य;
पूर्ण

/**
 * radix_tree_next_chunk - find next chunk of slots क्रम iteration
 *
 * @root:	radix tree root
 * @iter:	iterator state
 * @flags:	RADIX_TREE_ITER_* flags and tag index
 * Returns:	poपूर्णांकer to chunk first slot, or शून्य अगर there no more left
 *
 * This function looks up the next chunk in the radix tree starting from
 * @iter->next_index.  It वापसs a poपूर्णांकer to the chunk's first slot.
 * Also it fills @iter with data about chunk: position in the tree (index),
 * its end (next_index), and स्थिरructs a bit mask क्रम tagged iterating (tags).
 */
व्योम __rcu **radix_tree_next_chunk(स्थिर काष्ठा radix_tree_root *,
			     काष्ठा radix_tree_iter *iter, अचिन्हित flags);

/**
 * radix_tree_iter_lookup - look up an index in the radix tree
 * @root: radix tree root
 * @iter: iterator state
 * @index: key to look up
 *
 * If @index is present in the radix tree, this function वापसs the slot
 * containing it and updates @iter to describe the entry.  If @index is not
 * present, it वापसs शून्य.
 */
अटल अंतरभूत व्योम __rcu **
radix_tree_iter_lookup(स्थिर काष्ठा radix_tree_root *root,
			काष्ठा radix_tree_iter *iter, अचिन्हित दीर्घ index)
अणु
	radix_tree_iter_init(iter, index);
	वापस radix_tree_next_chunk(root, iter, RADIX_TREE_ITER_CONTIG);
पूर्ण

/**
 * radix_tree_iter_retry - retry this chunk of the iteration
 * @iter:	iterator state
 *
 * If we iterate over a tree रक्षित only by the RCU lock, a race
 * against deletion or creation may result in seeing a slot क्रम which
 * radix_tree_deref_retry() वापसs true.  If so, call this function
 * and जारी the iteration.
 */
अटल अंतरभूत __must_check
व्योम __rcu **radix_tree_iter_retry(काष्ठा radix_tree_iter *iter)
अणु
	iter->next_index = iter->index;
	iter->tags = 0;
	वापस शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
__radix_tree_iter_add(काष्ठा radix_tree_iter *iter, अचिन्हित दीर्घ slots)
अणु
	वापस iter->index + slots;
पूर्ण

/**
 * radix_tree_iter_resume - resume iterating when the chunk may be invalid
 * @slot: poपूर्णांकer to current slot
 * @iter: iterator state
 * Returns: New slot poपूर्णांकer
 *
 * If the iterator needs to release then reacquire a lock, the chunk may
 * have been invalidated by an insertion or deletion.  Call this function
 * beक्रमe releasing the lock to जारी the iteration from the next index.
 */
व्योम __rcu **__must_check radix_tree_iter_resume(व्योम __rcu **slot,
					काष्ठा radix_tree_iter *iter);

/**
 * radix_tree_chunk_size - get current chunk size
 *
 * @iter:	poपूर्णांकer to radix tree iterator
 * Returns:	current chunk size
 */
अटल __always_अंतरभूत दीर्घ
radix_tree_chunk_size(काष्ठा radix_tree_iter *iter)
अणु
	वापस iter->next_index - iter->index;
पूर्ण

/**
 * radix_tree_next_slot - find next slot in chunk
 *
 * @slot:	poपूर्णांकer to current slot
 * @iter:	poपूर्णांकer to iterator state
 * @flags:	RADIX_TREE_ITER_*, should be स्थिरant
 * Returns:	poपूर्णांकer to next slot, or शून्य अगर there no more left
 *
 * This function updates @iter->index in the हाल of a successful lookup.
 * For tagged lookup it also eats @iter->tags.
 *
 * There are several हालs where 'slot' can be passed in as शून्य to this
 * function.  These हालs result from the use of radix_tree_iter_resume() or
 * radix_tree_iter_retry().  In these हालs we करोn't end up dereferencing
 * 'slot' because either:
 * a) we are करोing tagged iteration and iter->tags has been set to 0, or
 * b) we are करोing non-tagged iteration, and iter->index and iter->next_index
 *    have been set up so that radix_tree_chunk_size() वापसs 1 or 0.
 */
अटल __always_अंतरभूत व्योम __rcu **radix_tree_next_slot(व्योम __rcu **slot,
				काष्ठा radix_tree_iter *iter, अचिन्हित flags)
अणु
	अगर (flags & RADIX_TREE_ITER_TAGGED) अणु
		iter->tags >>= 1;
		अगर (unlikely(!iter->tags))
			वापस शून्य;
		अगर (likely(iter->tags & 1ul)) अणु
			iter->index = __radix_tree_iter_add(iter, 1);
			slot++;
			जाओ found;
		पूर्ण
		अगर (!(flags & RADIX_TREE_ITER_CONTIG)) अणु
			अचिन्हित offset = __ffs(iter->tags);

			iter->tags >>= offset++;
			iter->index = __radix_tree_iter_add(iter, offset);
			slot += offset;
			जाओ found;
		पूर्ण
	पूर्ण अन्यथा अणु
		दीर्घ count = radix_tree_chunk_size(iter);

		जबतक (--count > 0) अणु
			slot++;
			iter->index = __radix_tree_iter_add(iter, 1);

			अगर (likely(*slot))
				जाओ found;
			अगर (flags & RADIX_TREE_ITER_CONTIG) अणु
				/* क्रमbid चयनing to the next chunk */
				iter->next_index = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस शून्य;

 found:
	वापस slot;
पूर्ण

/**
 * radix_tree_क्रम_each_slot - iterate over non-empty slots
 *
 * @slot:	the व्योम** variable क्रम poपूर्णांकer to slot
 * @root:	the काष्ठा radix_tree_root poपूर्णांकer
 * @iter:	the काष्ठा radix_tree_iter poपूर्णांकer
 * @start:	iteration starting index
 *
 * @slot poपूर्णांकs to radix tree slot, @iter->index contains its index.
 */
#घोषणा radix_tree_क्रम_each_slot(slot, root, iter, start)		\
	क्रम (slot = radix_tree_iter_init(iter, start) ;			\
	     slot || (slot = radix_tree_next_chunk(root, iter, 0)) ;	\
	     slot = radix_tree_next_slot(slot, iter, 0))

/**
 * radix_tree_क्रम_each_tagged - iterate over tagged slots
 *
 * @slot:	the व्योम** variable क्रम poपूर्णांकer to slot
 * @root:	the काष्ठा radix_tree_root poपूर्णांकer
 * @iter:	the काष्ठा radix_tree_iter poपूर्णांकer
 * @start:	iteration starting index
 * @tag:	tag index
 *
 * @slot poपूर्णांकs to radix tree slot, @iter->index contains its index.
 */
#घोषणा radix_tree_क्रम_each_tagged(slot, root, iter, start, tag)	\
	क्रम (slot = radix_tree_iter_init(iter, start) ;			\
	     slot || (slot = radix_tree_next_chunk(root, iter,		\
			      RADIX_TREE_ITER_TAGGED | tag)) ;		\
	     slot = radix_tree_next_slot(slot, iter,			\
				RADIX_TREE_ITER_TAGGED | tag))

#पूर्ण_अगर /* _LINUX_RADIX_TREE_H */
