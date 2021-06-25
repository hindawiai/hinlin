<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
   lru_cache.c

   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2003-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 2003-2008, Philipp Reisner <philipp.reisner@linbit.com>.
   Copyright (C) 2003-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.


 */

#अगर_अघोषित LRU_CACHE_H
#घोषणा LRU_CACHE_H

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/माला.स> /* क्रम स_रखो */
#समावेश <linux/seq_file.h>

/*
This header file (and its .c file; kernel-करोc of functions see there)
  define a helper framework to easily keep track of index:label associations,
  and changes to an "active set" of objects, as well as pending transactions,
  to persistently record those changes.

  We use an LRU policy अगर it is necessary to "cool down" a region currently in
  the active set beक्रमe we can "heat" a previously unused region.

  Because of this later property, it is called "lru_cache".
  As it actually Tracks Objects in an Active SeT, we could also call it
  toast (incidentally that is what may happen to the data on the
  backend storage uppon next resync, अगर we करोn't get it right).

What क्रम?

We replicate IO (more or less synchronously) to local and remote disk.

For crash recovery after replication node failure,
  we need to resync all regions that have been target of in-flight WRITE IO
  (in use, or "hot", regions), as we करोn't know whether or not those WRITEs
  have made it to stable storage.

  To aव्योम a "full resync", we need to persistently track these regions.

  This is known as "write intent log", and can be implemented as on-disk
  (coarse or fine grained) biपंचांगap, or other meta data.

  To aव्योम the overhead of frequent extra ग_लिखोs to this meta data area,
  usually the condition is softened to regions that _may_ have been target of
  in-flight WRITE IO, e.g. by only lazily clearing the on-disk ग_लिखो-पूर्णांकent
  biपंचांगap, trading frequency of meta data transactions against amount of
  (possibly unnecessary) resync traffic.

  If we set a hard limit on the area that may be "hot" at any given समय, we
  limit the amount of resync traffic needed क्रम crash recovery.

For recovery after replication link failure,
  we need to resync all blocks that have been changed on the other replica
  in the mean समय, or, अगर both replica have been changed independently [*],
  all blocks that have been changed on either replica in the mean समय.
  [*] usually as a result of a cluster split-brain and insufficient protection.
      but there are valid use हालs to करो this on purpose.

  Tracking those blocks can be implemented as "dirty bitmap".
  Having it fine-grained reduces the amount of resync traffic.
  It should also be persistent, to allow क्रम reboots (or crashes)
  जबतक the replication link is करोwn.

There are various possible implementations क्रम persistently storing
ग_लिखो पूर्णांकent log inक्रमmation, three of which are mentioned here.

"Chunk dirtying"
  The on-disk "dirty bitmap" may be re-used as "write-intent" biपंचांगap as well.
  To reduce the frequency of biपंचांगap updates क्रम ग_लिखो-पूर्णांकent log purposes,
  one could dirty "chunks" (of some size) at a समय of the (fine grained)
  on-disk biपंचांगap, जबतक keeping the in-memory "dirty" biपंचांगap as clean as
  possible, flushing it to disk again when a previously "hot" (and on-disk
  dirtied as full chunk) area "cools down" again (no IO in flight anymore,
  and none expected in the near future either).

"Explicit (coarse) write intent bitmap"
  An other implementation could chose a (probably coarse) explicit biपंचांगap,
  क्रम ग_लिखो-पूर्णांकent log purposes, additionally to the fine grained dirty biपंचांगap.

"Activity log"
  Yet an other implementation may keep track of the hot regions, by starting
  with an empty set, and writing करोwn a journal of region numbers that have
  become "hot", or have "cooled down" again.

  To be able to use a ring buffer क्रम this journal of changes to the active
  set, we not only record the actual changes to that set, but also record the
  not changing members of the set in a round robin fashion. To करो so, we use a
  fixed (but configurable) number of slots which we can identअगरy by index, and
  associate region numbers (labels) with these indices.
  For each transaction recording a change to the active set, we record the
  change itself (index: -old_label, +new_label), and which index is associated
  with which label (index: current_label) within a certain sliding winकरोw that
  is moved further over the available indices with each such transaction.

  Thus, क्रम crash recovery, अगर the ringbuffer is sufficiently large, we can
  accurately reस्थिरruct the active set.

  Sufficiently large depends only on maximum number of active objects, and the
  size of the sliding winकरोw recording "index: current_label" associations within
  each transaction.

  This is what we call the "activity log".

  Currently we need one activity log transaction per single label change, which
  करोes not give much benefit over the "dirty chunks of bitmap" approach, other
  than potentially less seeks.

  We plan to change the transaction क्रमmat to support multiple changes per
  transaction, which then would reduce several (disjoपूर्णांक, "random") updates to
  the biपंचांगap पूर्णांकo one transaction to the activity log ring buffer.
*/

/* this defines an element in a tracked set
 * .colision is क्रम hash table lookup.
 * When we process a new IO request, we know its sector, thus can deduce the
 * region number (label) easily.  To करो the label -> object lookup without a
 * full list walk, we use a simple hash table.
 *
 * .list is on one of three lists:
 *  in_use: currently in use (refcnt > 0, lc_number != LC_FREE)
 *     lru: unused but पढ़ोy to be reused or recycled
 *          (lc_refcnt == 0, lc_number != LC_FREE),
 *    मुक्त: unused but पढ़ोy to be recycled
 *          (lc_refcnt == 0, lc_number == LC_FREE),
 *
 * an element is said to be "in the active set",
 * अगर either on "in_use" or "lru", i.e. lc_number != LC_FREE.
 *
 * DRBD currently (May 2009) only uses 61 elements on the resync lru_cache
 * (total memory usage 2 pages), and up to 3833 elements on the act_log
 * lru_cache, totalling ~215 kB क्रम 64bit architecture, ~53 pages.
 *
 * We usually करो not actually मुक्त these objects again, but only "recycle"
 * them, as the change "index: -old_label, +LC_FREE" would need a transaction
 * as well.  Which also means that using a kmem_cache to allocate the objects
 * from wastes some resources.
 * But it aव्योमs high order page allocations in kदो_स्मृति.
 */
काष्ठा lc_element अणु
	काष्ठा hlist_node colision;
	काष्ठा list_head list;		 /* LRU list or मुक्त list */
	अचिन्हित refcnt;
	/* back "pointer" पूर्णांकo lc_cache->element[index],
	 * क्रम paranoia, and क्रम "lc_element_to_index" */
	अचिन्हित lc_index;
	/* अगर we want to track a larger set of objects,
	 * it needs to become arch independend u64 */
	अचिन्हित lc_number;
	/* special label when on मुक्त list */
#घोषणा LC_FREE (~0U)

	/* क्रम pending changes */
	अचिन्हित lc_new_number;
पूर्ण;

काष्ठा lru_cache अणु
	/* the least recently used item is kept at lru->prev */
	काष्ठा list_head lru;
	काष्ठा list_head मुक्त;
	काष्ठा list_head in_use;
	काष्ठा list_head to_be_changed;

	/* the pre-created kmem cache to allocate the objects from */
	काष्ठा kmem_cache *lc_cache;

	/* size of tracked objects, used to स_रखो(,0,) them in lc_reset */
	माप_प्रकार element_size;
	/* offset of काष्ठा lc_element member in the tracked object */
	माप_प्रकार element_off;

	/* number of elements (indices) */
	अचिन्हित पूर्णांक nr_elements;
	/* Arbitrary limit on maximum tracked objects. Practical limit is much
	 * lower due to allocation failures, probably. For typical use हालs,
	 * nr_elements should be a few thousand at most.
	 * This also limits the maximum value of lc_element.lc_index, allowing the
	 * 8 high bits of .lc_index to be overloaded with flags in the future. */
#घोषणा LC_MAX_ACTIVE	(1<<24)

	/* allow to accumulate a few (index:label) changes,
	 * but no more than max_pending_changes */
	अचिन्हित पूर्णांक max_pending_changes;
	/* number of elements currently on to_be_changed list */
	अचिन्हित पूर्णांक pending_changes;

	/* statistics */
	अचिन्हित used; /* number of elements currently on in_use list */
	अचिन्हित दीर्घ hits, misses, starving, locked, changed;

	/* see below: flag-bits क्रम lru_cache */
	अचिन्हित दीर्घ flags;


	व्योम  *lc_निजी;
	स्थिर अक्षर *name;

	/* nr_elements there */
	काष्ठा hlist_head *lc_slot;
	काष्ठा lc_element **lc_element;
पूर्ण;


/* flag-bits क्रम lru_cache */
क्रमागत अणु
	/* debugging aid, to catch concurrent access early.
	 * user needs to guarantee exclusive access by proper locking! */
	__LC_PARANOIA,

	/* annotate that the set is "dirty", possibly accumulating further
	 * changes, until a transaction is finally triggered */
	__LC_सूचीTY,

	/* Locked, no further changes allowed.
	 * Also used to serialize changing transactions. */
	__LC_LOCKED,

	/* अगर we need to change the set, but currently there is no मुक्त nor
	 * unused element available, we are "starving", and must not give out
	 * further references, to guarantee that eventually some refcnt will
	 * drop to zero and we will be able to make progress again, changing
	 * the set, writing the transaction.
	 * अगर the statistics say we are frequently starving,
	 * nr_elements is too small. */
	__LC_STARVING,
पूर्ण;
#घोषणा LC_PARANOIA (1<<__LC_PARANOIA)
#घोषणा LC_सूचीTY    (1<<__LC_सूचीTY)
#घोषणा LC_LOCKED   (1<<__LC_LOCKED)
#घोषणा LC_STARVING (1<<__LC_STARVING)

बाह्य काष्ठा lru_cache *lc_create(स्थिर अक्षर *name, काष्ठा kmem_cache *cache,
		अचिन्हित max_pending_changes,
		अचिन्हित e_count, माप_प्रकार e_size, माप_प्रकार e_off);
बाह्य व्योम lc_reset(काष्ठा lru_cache *lc);
बाह्य व्योम lc_destroy(काष्ठा lru_cache *lc);
बाह्य व्योम lc_set(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr, पूर्णांक index);
बाह्य व्योम lc_del(काष्ठा lru_cache *lc, काष्ठा lc_element *element);

बाह्य काष्ठा lc_element *lc_get_cumulative(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr);
बाह्य काष्ठा lc_element *lc_try_get(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr);
बाह्य काष्ठा lc_element *lc_find(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr);
बाह्य काष्ठा lc_element *lc_get(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr);
बाह्य अचिन्हित पूर्णांक lc_put(काष्ठा lru_cache *lc, काष्ठा lc_element *e);
बाह्य व्योम lc_committed(काष्ठा lru_cache *lc);

काष्ठा seq_file;
बाह्य व्योम lc_seq_म_लिखो_stats(काष्ठा seq_file *seq, काष्ठा lru_cache *lc);

बाह्य व्योम lc_seq_dump_details(काष्ठा seq_file *seq, काष्ठा lru_cache *lc, अक्षर *utext,
				व्योम (*detail) (काष्ठा seq_file *, काष्ठा lc_element *));

/**
 * lc_try_lock_क्रम_transaction - can be used to stop lc_get() from changing the tracked set
 * @lc: the lru cache to operate on
 *
 * Allows (expects) the set to be "dirty".  Note that the reference counts and
 * order on the active and lru lists may still change.  Used to serialize
 * changing transactions.  Returns true अगर we aquired the lock.
 */
अटल अंतरभूत पूर्णांक lc_try_lock_क्रम_transaction(काष्ठा lru_cache *lc)
अणु
	वापस !test_and_set_bit(__LC_LOCKED, &lc->flags);
पूर्ण

/**
 * lc_try_lock - variant to stop lc_get() from changing the tracked set
 * @lc: the lru cache to operate on
 *
 * Note that the reference counts and order on the active and lru lists may
 * still change.  Only works on a "clean" set.  Returns true अगर we aquired the
 * lock, which means there are no pending changes, and any further attempt to
 * change the set will not succeed until the next lc_unlock().
 */
बाह्य पूर्णांक lc_try_lock(काष्ठा lru_cache *lc);

/**
 * lc_unlock - unlock @lc, allow lc_get() to change the set again
 * @lc: the lru cache to operate on
 */
अटल अंतरभूत व्योम lc_unlock(काष्ठा lru_cache *lc)
अणु
	clear_bit(__LC_सूचीTY, &lc->flags);
	clear_bit_unlock(__LC_LOCKED, &lc->flags);
पूर्ण

बाह्य bool lc_is_used(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr);

#घोषणा lc_entry(ptr, type, member) \
	container_of(ptr, type, member)

बाह्य काष्ठा lc_element *lc_element_by_index(काष्ठा lru_cache *lc, अचिन्हित i);
बाह्य अचिन्हित पूर्णांक lc_index_of(काष्ठा lru_cache *lc, काष्ठा lc_element *e);

#पूर्ण_अगर
