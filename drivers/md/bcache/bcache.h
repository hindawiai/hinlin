<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BCACHE_H
#घोषणा _BCACHE_H

/*
 * SOME HIGH LEVEL CODE DOCUMENTATION:
 *
 * Bcache mostly works with cache sets, cache devices, and backing devices.
 *
 * Support क्रम multiple cache devices hasn't quite been finished off yet, but
 * it's about 95% plumbed through. A cache set and its cache devices is sort of
 * like a md raid array and its component devices. Most of the code करोesn't care
 * about inभागidual cache devices, the मुख्य असलtraction is the cache set.
 *
 * Multiple cache devices is पूर्णांकended to give us the ability to mirror dirty
 * cached data and metadata, without mirroring clean cached data.
 *
 * Backing devices are dअगरferent, in that they have a lअगरeसमय independent of a
 * cache set. When you रेजिस्टर a newly क्रमmatted backing device it'll come up
 * in passthrough mode, and then you can attach and detach a backing device from
 * a cache set at runसमय - जबतक it's mounted and in use. Detaching implicitly
 * invalidates any cached data क्रम that backing device.
 *
 * A cache set can have multiple (many) backing devices attached to it.
 *
 * There's also flash only volumes - this is the reason क्रम the distinction
 * between काष्ठा cached_dev and काष्ठा bcache_device. A flash only volume
 * works much like a bcache device that has a backing device, except the
 * "cached" data is always dirty. The end result is that we get thin
 * provisioning with very little additional code.
 *
 * Flash only volumes work but they're not production पढ़ोy because the moving
 * garbage collector needs more work. More on that later.
 *
 * BUCKETS/ALLOCATION:
 *
 * Bcache is primarily deचिन्हित क्रम caching, which means that in normal
 * operation all of our available space will be allocated. Thus, we need an
 * efficient way of deleting things from the cache so we can ग_लिखो new things to
 * it.
 *
 * To करो this, we first भागide the cache device up पूर्णांकo buckets. A bucket is the
 * unit of allocation; they're typically around 1 mb - anywhere from 128k to 2M+
 * works efficiently.
 *
 * Each bucket has a 16 bit priority, and an 8 bit generation associated with
 * it. The gens and priorities क्रम all the buckets are stored contiguously and
 * packed on disk (in a linked list of buckets - aside from the superblock, all
 * of bcache's metadata is stored in buckets).
 *
 * The priority is used to implement an LRU. We reset a bucket's priority when
 * we allocate it or on cache it, and every so often we decrement the priority
 * of each bucket. It could be used to implement something more sophisticated,
 * अगर anyone ever माला_लो around to it.
 *
 * The generation is used क्रम invalidating buckets. Each poपूर्णांकer also has an 8
 * bit generation embedded in it; क्रम a poपूर्णांकer to be considered valid, its gen
 * must match the gen of the bucket it poपूर्णांकs पूर्णांकo.  Thus, to reuse a bucket all
 * we have to करो is increment its gen (and ग_लिखो its new gen to disk; we batch
 * this up).
 *
 * Bcache is entirely COW - we never ग_लिखो twice to a bucket, even buckets that
 * contain metadata (including btree nodes).
 *
 * THE BTREE:
 *
 * Bcache is in large part design around the btree.
 *
 * At a high level, the btree is just an index of key -> ptr tuples.
 *
 * Keys represent extents, and thus have a size field. Keys also have a variable
 * number of poपूर्णांकers attached to them (potentially zero, which is handy क्रम
 * invalidating the cache).
 *
 * The key itself is an inode:offset pair. The inode number corresponds to a
 * backing device or a flash only volume. The offset is the ending offset of the
 * extent within the inode - not the starting offset; this makes lookups
 * slightly more convenient.
 *
 * Poपूर्णांकers contain the cache device id, the offset on that device, and an 8 bit
 * generation number. More on the gen later.
 *
 * Index lookups are not fully असलtracted - cache lookups in particular are
 * still somewhat mixed in with the btree code, but things are headed in that
 * direction.
 *
 * Updates are fairly well असलtracted, though. There are two dअगरferent ways of
 * updating the btree; insert and replace.
 *
 * BTREE_INSERT will just take a list of keys and insert them पूर्णांकo the btree -
 * overwriting (possibly only partially) any extents they overlap with. This is
 * used to update the index after a ग_लिखो.
 *
 * BTREE_REPLACE is really cmpxchg(); it inserts a key पूर्णांकo the btree अगरf it is
 * overwriting a key that matches another given key. This is used क्रम inserting
 * data पूर्णांकo the cache after a cache miss, and क्रम background ग_लिखोback, and क्रम
 * the moving garbage collector.
 *
 * There is no "delete" operation; deleting things from the index is
 * accomplished by either by invalidating poपूर्णांकers (by incrementing a bucket's
 * gen) or by inserting a key with 0 poपूर्णांकers - which will overग_लिखो anything
 * previously present at that location in the index.
 *
 * This means that there are always stale/invalid keys in the btree. They're
 * filtered out by the code that iterates through a btree node, and हटाओd when
 * a btree node is rewritten.
 *
 * BTREE NODES:
 *
 * Our unit of allocation is a bucket, and we we can't arbitrarily allocate and
 * मुक्त smaller than a bucket - so, that's how big our btree nodes are.
 *
 * (If buckets are really big we'll only use part of the bucket क्रम a btree node
 * - no less than 1/4th - but a bucket still contains no more than a single
 * btree node. I'd actually like to change this, but क्रम now we rely on the
 * bucket's gen क्रम deleting btree nodes when we reग_लिखो/split a node.)
 *
 * Anyways, btree nodes are big - big enough to be inefficient with a textbook
 * btree implementation.
 *
 * The way this is solved is that btree nodes are पूर्णांकernally log काष्ठाured; we
 * can append new keys to an existing btree node without rewriting it. This
 * means each set of keys we ग_लिखो is sorted, but the node is not.
 *
 * We मुख्यtain this log काष्ठाure in memory - keeping 1Mb of keys sorted would
 * be expensive, and we have to distinguish between the keys we have written and
 * the keys we haven't. So to करो a lookup in a btree node, we have to search
 * each sorted set. But we करो merge written sets together lazily, so the cost of
 * these extra searches is quite low (normally most of the keys in a btree node
 * will be in one big set, and then there'll be one or two sets that are much
 * smaller).
 *
 * This log काष्ठाure makes bcache's btree more of a hybrid between a
 * conventional btree and a compacting data काष्ठाure, with some of the
 * advantages of both.
 *
 * GARBAGE COLLECTION:
 *
 * We can't just invalidate any bucket - it might contain dirty data or
 * metadata. If it once contained dirty data, other ग_लिखोs might overग_लिखो it
 * later, leaving no valid poपूर्णांकers पूर्णांकo that bucket in the index.
 *
 * Thus, the primary purpose of garbage collection is to find buckets to reuse.
 * It also counts how much valid data it each bucket currently contains, so that
 * allocation can reuse buckets sooner when they've been mostly overwritten.
 *
 * It also करोes some things that are really पूर्णांकernal to the btree
 * implementation. If a btree node contains poपूर्णांकers that are stale by more than
 * some threshold, it reग_लिखोs the btree node to aव्योम the bucket's generation
 * wrapping around. It also merges adjacent btree nodes अगर they're empty enough.
 *
 * THE JOURNAL:
 *
 * Bcache's journal is not necessary क्रम consistency; we always strictly
 * order metadata ग_लिखोs so that the btree and everything अन्यथा is consistent on
 * disk in the event of an unclean shutकरोwn, and in fact bcache had ग_लिखोback
 * caching (with recovery from unclean shutकरोwn) beक्रमe journalling was
 * implemented.
 *
 * Rather, the journal is purely a perक्रमmance optimization; we can't complete a
 * ग_लिखो until we've updated the index on disk, otherwise the cache would be
 * inconsistent in the event of an unclean shutकरोwn. This means that without the
 * journal, on अक्रमom ग_लिखो workloads we स्थिरantly have to update all the leaf
 * nodes in the btree, and those ग_लिखोs will be mostly empty (appending at most
 * a few keys each) - highly inefficient in terms of amount of metadata ग_लिखोs,
 * and it माला_दो more strain on the various btree resorting/compacting code.
 *
 * The journal is just a log of keys we've inserted; on startup we just reinsert
 * all the keys in the खोलो journal entries. That means that when we're updating
 * a node in the btree, we can रुको until a 4k block of keys fills up beक्रमe
 * writing them out.
 *
 * For simplicity, we only journal updates to leaf nodes; updates to parent
 * nodes are rare enough (since our leaf nodes are huge) that it wasn't worth
 * the complनिकासy to deal with journalling them (in particular, journal replay)
 * - updates to non leaf nodes just happen synchronously (see btree_split()).
 */

#घोषणा pr_fmt(fmt) "bcache: %s() " fmt, __func__

#समावेश <linux/bcache.h>
#समावेश <linux/bपन.स>
#समावेश <linux/kobject.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/refcount.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "bset.h"
#समावेश "util.h"
#समावेश "closure.h"

काष्ठा bucket अणु
	atomic_t	pin;
	uपूर्णांक16_t	prio;
	uपूर्णांक8_t		gen;
	uपूर्णांक8_t		last_gc; /* Most out of date gen in the btree */
	uपूर्णांक16_t	gc_mark; /* Bitfield used by GC. See below क्रम field */
पूर्ण;

/*
 * I'd use bitfields for these, but I don't trust the compiler not to screw me
 * as multiple thपढ़ोs touch काष्ठा bucket without locking
 */

BITMASK(GC_MARK,	 काष्ठा bucket, gc_mark, 0, 2);
#घोषणा GC_MARK_RECLAIMABLE	1
#घोषणा GC_MARK_सूचीTY		2
#घोषणा GC_MARK_METADATA	3
#घोषणा GC_SECTORS_USED_SIZE	13
#घोषणा MAX_GC_SECTORS_USED	(~(~0ULL << GC_SECTORS_USED_SIZE))
BITMASK(GC_SECTORS_USED, काष्ठा bucket, gc_mark, 2, GC_SECTORS_USED_SIZE);
BITMASK(GC_MOVE, काष्ठा bucket, gc_mark, 15, 1);

#समावेश "journal.h"
#समावेश "stats.h"
काष्ठा search;
काष्ठा btree;
काष्ठा keybuf;

काष्ठा keybuf_key अणु
	काष्ठा rb_node		node;
	BKEY_PADDED(key);
	व्योम			*निजी;
पूर्ण;

काष्ठा keybuf अणु
	काष्ठा bkey		last_scanned;
	spinlock_t		lock;

	/*
	 * Beginning and end of range in rb tree - so that we can skip taking
	 * lock and checking the rb tree when we need to check क्रम overlapping
	 * keys.
	 */
	काष्ठा bkey		start;
	काष्ठा bkey		end;

	काष्ठा rb_root		keys;

#घोषणा KEYBUF_NR		500
	DECLARE_ARRAY_ALLOCATOR(काष्ठा keybuf_key, मुक्तlist, KEYBUF_NR);
पूर्ण;

काष्ठा bcache_device अणु
	काष्ठा closure		cl;

	काष्ठा kobject		kobj;

	काष्ठा cache_set	*c;
	अचिन्हित पूर्णांक		id;
#घोषणा BCACHEDEVNAME_SIZE	12
	अक्षर			name[BCACHEDEVNAME_SIZE];

	काष्ठा gendisk		*disk;

	अचिन्हित दीर्घ		flags;
#घोषणा BCACHE_DEV_CLOSING		0
#घोषणा BCACHE_DEV_DETACHING		1
#घोषणा BCACHE_DEV_UNLINK_DONE		2
#घोषणा BCACHE_DEV_WB_RUNNING		3
#घोषणा BCACHE_DEV_RATE_DW_RUNNING	4
	पूर्णांक			nr_stripes;
	अचिन्हित पूर्णांक		stripe_size;
	atomic_t		*stripe_sectors_dirty;
	अचिन्हित दीर्घ		*full_dirty_stripes;

	काष्ठा bio_set		bio_split;

	अचिन्हित पूर्णांक		data_csum:1;

	पूर्णांक (*cache_miss)(काष्ठा btree *b, काष्ठा search *s,
			  काष्ठा bio *bio, अचिन्हित पूर्णांक sectors);
	पूर्णांक (*ioctl)(काष्ठा bcache_device *d, भ_शेषe_t mode,
		     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्ण;

काष्ठा io अणु
	/* Used to track sequential IO so it can be skipped */
	काष्ठा hlist_node	hash;
	काष्ठा list_head	lru;

	अचिन्हित दीर्घ		jअगरfies;
	अचिन्हित पूर्णांक		sequential;
	sector_t		last;
पूर्ण;

क्रमागत stop_on_failure अणु
	BCH_CACHED_DEV_STOP_AUTO = 0,
	BCH_CACHED_DEV_STOP_ALWAYS,
	BCH_CACHED_DEV_STOP_MODE_MAX,
पूर्ण;

काष्ठा cached_dev अणु
	काष्ठा list_head	list;
	काष्ठा bcache_device	disk;
	काष्ठा block_device	*bdev;

	काष्ठा cache_sb		sb;
	काष्ठा cache_sb_disk	*sb_disk;
	काष्ठा bio		sb_bio;
	काष्ठा bio_vec		sb_bv[1];
	काष्ठा closure		sb_ग_लिखो;
	काष्ठा semaphore	sb_ग_लिखो_mutex;

	/* Refcount on the cache set. Always nonzero when we're caching. */
	refcount_t		count;
	काष्ठा work_काष्ठा	detach;

	/*
	 * Device might not be running अगर it's dirty and the cache set hasn't
	 * showed up yet.
	 */
	atomic_t		running;

	/*
	 * Writes take a shared lock from start to finish; scanning क्रम dirty
	 * data to refill the rb tree requires an exclusive lock.
	 */
	काष्ठा rw_semaphore	ग_लिखोback_lock;

	/*
	 * Nonzero, and ग_लिखोback has a refcount (d->count), अगरf there is dirty
	 * data in the cache. Protected by ग_लिखोback_lock; must have an
	 * shared lock to set and exclusive lock to clear.
	 */
	atomic_t		has_dirty;

#घोषणा BCH_CACHE_READA_ALL		0
#घोषणा BCH_CACHE_READA_META_ONLY	1
	अचिन्हित पूर्णांक		cache_पढ़ोahead_policy;
	काष्ठा bch_ratelimit	ग_लिखोback_rate;
	काष्ठा delayed_work	ग_लिखोback_rate_update;

	/* Limit number of ग_लिखोback bios in flight */
	काष्ठा semaphore	in_flight;
	काष्ठा task_काष्ठा	*ग_लिखोback_thपढ़ो;
	काष्ठा workqueue_काष्ठा	*ग_लिखोback_ग_लिखो_wq;

	काष्ठा keybuf		ग_लिखोback_keys;

	काष्ठा task_काष्ठा	*status_update_thपढ़ो;
	/*
	 * Order the ग_लिखो-half of ग_लिखोback operations strongly in dispatch
	 * order.  (Maपूर्णांकain LBA order; करोn't allow पढ़ोs completing out of
	 * order to re-order the ग_लिखोs...)
	 */
	काष्ठा closure_रुकोlist ग_लिखोback_ordering_रुको;
	atomic_t		ग_लिखोback_sequence_next;

	/* For tracking sequential IO */
#घोषणा RECENT_IO_BITS	7
#घोषणा RECENT_IO	(1 << RECENT_IO_BITS)
	काष्ठा io		io[RECENT_IO];
	काष्ठा hlist_head	io_hash[RECENT_IO + 1];
	काष्ठा list_head	io_lru;
	spinlock_t		io_lock;

	काष्ठा cache_accounting	accounting;

	/* The rest of this all shows up in sysfs */
	अचिन्हित पूर्णांक		sequential_cutoff;

	अचिन्हित पूर्णांक		io_disable:1;
	अचिन्हित पूर्णांक		verअगरy:1;
	अचिन्हित पूर्णांक		bypass_torture_test:1;

	अचिन्हित पूर्णांक		partial_stripes_expensive:1;
	अचिन्हित पूर्णांक		ग_लिखोback_metadata:1;
	अचिन्हित पूर्णांक		ग_लिखोback_running:1;
	अचिन्हित पूर्णांक		ग_लिखोback_consider_fragment:1;
	अचिन्हित अक्षर		ग_लिखोback_percent;
	अचिन्हित पूर्णांक		ग_लिखोback_delay;

	uपूर्णांक64_t		ग_लिखोback_rate_target;
	पूर्णांक64_t			ग_लिखोback_rate_proportional;
	पूर्णांक64_t			ग_लिखोback_rate_पूर्णांकegral;
	पूर्णांक64_t			ग_लिखोback_rate_पूर्णांकegral_scaled;
	पूर्णांक32_t			ग_लिखोback_rate_change;

	अचिन्हित पूर्णांक		ग_लिखोback_rate_update_seconds;
	अचिन्हित पूर्णांक		ग_लिखोback_rate_i_term_inverse;
	अचिन्हित पूर्णांक		ग_लिखोback_rate_p_term_inverse;
	अचिन्हित पूर्णांक		ग_लिखोback_rate_fp_term_low;
	अचिन्हित पूर्णांक		ग_लिखोback_rate_fp_term_mid;
	अचिन्हित पूर्णांक		ग_लिखोback_rate_fp_term_high;
	अचिन्हित पूर्णांक		ग_लिखोback_rate_minimum;

	क्रमागत stop_on_failure	stop_when_cache_set_failed;
#घोषणा DEFAULT_CACHED_DEV_ERROR_LIMIT	64
	atomic_t		io_errors;
	अचिन्हित पूर्णांक		error_limit;
	अचिन्हित पूर्णांक		offline_seconds;

	अक्षर			backing_dev_name[BDEVNAME_SIZE];
पूर्ण;

क्रमागत alloc_reserve अणु
	RESERVE_BTREE,
	RESERVE_PRIO,
	RESERVE_MOVINGGC,
	RESERVE_NONE,
	RESERVE_NR,
पूर्ण;

काष्ठा cache अणु
	काष्ठा cache_set	*set;
	काष्ठा cache_sb		sb;
	काष्ठा cache_sb_disk	*sb_disk;
	काष्ठा bio		sb_bio;
	काष्ठा bio_vec		sb_bv[1];

	काष्ठा kobject		kobj;
	काष्ठा block_device	*bdev;

	काष्ठा task_काष्ठा	*alloc_thपढ़ो;

	काष्ठा closure		prio;
	काष्ठा prio_set		*disk_buckets;

	/*
	 * When allocating new buckets, prio_ग_लिखो() माला_लो first dibs - since we
	 * may not be allocate at all without writing priorities and gens.
	 * prio_last_buckets[] contains the last buckets we wrote priorities to
	 * (so gc can mark them as metadata), prio_buckets[] contains the
	 * buckets allocated क्रम the next prio ग_लिखो.
	 */
	uपूर्णांक64_t		*prio_buckets;
	uपूर्णांक64_t		*prio_last_buckets;

	/*
	 * मुक्त: Buckets that are पढ़ोy to be used
	 *
	 * मुक्त_inc: Incoming buckets - these are buckets that currently have
	 * cached data in them, and we can't reuse them until after we ग_लिखो
	 * their new gen to disk. After prio_ग_लिखो() finishes writing the new
	 * gens/prios, they'll be moved to the मुक्त list (and possibly discarded
	 * in the process)
	 */
	DECLARE_FIFO(दीर्घ, मुक्त)[RESERVE_NR];
	DECLARE_FIFO(दीर्घ, मुक्त_inc);

	माप_प्रकार			fअगरo_last_bucket;

	/* Allocation stuff: */
	काष्ठा bucket		*buckets;

	DECLARE_HEAP(काष्ठा bucket *, heap);

	/*
	 * If nonzero, we know we aren't going to find any buckets to invalidate
	 * until a gc finishes - otherwise we could poपूर्णांकlessly burn a ton of
	 * cpu
	 */
	अचिन्हित पूर्णांक		invalidate_needs_gc;

	bool			discard; /* Get rid of? */

	काष्ठा journal_device	journal;

	/* The rest of this all shows up in sysfs */
#घोषणा IO_ERROR_SHIFT		20
	atomic_t		io_errors;
	atomic_t		io_count;

	atomic_दीर्घ_t		meta_sectors_written;
	atomic_दीर्घ_t		btree_sectors_written;
	atomic_दीर्घ_t		sectors_written;

	अक्षर			cache_dev_name[BDEVNAME_SIZE];
पूर्ण;

काष्ठा gc_stat अणु
	माप_प्रकार			nodes;
	माप_प्रकार			nodes_pre;
	माप_प्रकार			key_bytes;

	माप_प्रकार			nkeys;
	uपूर्णांक64_t		data;	/* sectors */
	अचिन्हित पूर्णांक		in_use; /* percent */
पूर्ण;

/*
 * Flag bits, क्रम how the cache set is shutting करोwn, and what phase it's at:
 *
 * CACHE_SET_UNREGISTERING means we're not just shutting down, we're detaching
 * all the backing devices first (their cached data माला_लो invalidated, and they
 * won't स्वतःmatically reattach).
 *
 * CACHE_SET_STOPPING always माला_लो set first when we're closing करोwn a cache set;
 * we'll जारी to run normally क्रम aजबतक with CACHE_SET_STOPPING set (i.e.
 * flushing dirty data).
 *
 * CACHE_SET_RUNNING means all cache devices have been रेजिस्टरed and journal
 * replay is complete.
 *
 * CACHE_SET_IO_DISABLE is set when bcache is stopping the whold cache set, all
 * बाह्यal and पूर्णांकernal I/O should be denied when this flag is set.
 *
 */
#घोषणा CACHE_SET_UNREGISTERING		0
#घोषणा	CACHE_SET_STOPPING		1
#घोषणा	CACHE_SET_RUNNING		2
#घोषणा CACHE_SET_IO_DISABLE		3

काष्ठा cache_set अणु
	काष्ठा closure		cl;

	काष्ठा list_head	list;
	काष्ठा kobject		kobj;
	काष्ठा kobject		पूर्णांकernal;
	काष्ठा dentry		*debug;
	काष्ठा cache_accounting accounting;

	अचिन्हित दीर्घ		flags;
	atomic_t		idle_counter;
	atomic_t		at_max_ग_लिखोback_rate;

	काष्ठा cache		*cache;

	काष्ठा bcache_device	**devices;
	अचिन्हित पूर्णांक		devices_max_used;
	atomic_t		attached_dev_nr;
	काष्ठा list_head	cached_devs;
	uपूर्णांक64_t		cached_dev_sectors;
	atomic_दीर्घ_t		flash_dev_dirty_sectors;
	काष्ठा closure		caching;

	काष्ठा closure		sb_ग_लिखो;
	काष्ठा semaphore	sb_ग_लिखो_mutex;

	mempool_t		search;
	mempool_t		bio_meta;
	काष्ठा bio_set		bio_split;

	/* For the btree cache */
	काष्ठा shrinker		shrink;

	/* For the btree cache and anything allocation related */
	काष्ठा mutex		bucket_lock;

	/* log2(bucket_size), in sectors */
	अचिन्हित लघु		bucket_bits;

	/* log2(block_size), in sectors */
	अचिन्हित लघु		block_bits;

	/*
	 * Default number of pages क्रम a new btree node - may be less than a
	 * full bucket
	 */
	अचिन्हित पूर्णांक		btree_pages;

	/*
	 * Lists of काष्ठा btrees; lru is the list क्रम काष्ठाs that have memory
	 * allocated क्रम actual btree node, मुक्तd is क्रम काष्ठाs that करो not.
	 *
	 * We never मुक्त a काष्ठा btree, except on shutकरोwn - we just put it on
	 * the btree_cache_मुक्तd list and reuse it later. This simplअगरies the
	 * code, and it करोesn't cost us much memory as the memory usage is
	 * करोminated by buffers that hold the actual btree node data and those
	 * can be मुक्तd - and the number of काष्ठा btrees allocated is
	 * effectively bounded.
	 *
	 * btree_cache_मुक्तable effectively is a small cache - we use it because
	 * high order page allocations can be rather expensive, and it's quite
	 * common to delete and allocate btree nodes in quick succession. It
	 * should never grow past ~2-3 nodes in practice.
	 */
	काष्ठा list_head	btree_cache;
	काष्ठा list_head	btree_cache_मुक्तable;
	काष्ठा list_head	btree_cache_मुक्तd;

	/* Number of elements in btree_cache + btree_cache_मुक्तable lists */
	अचिन्हित पूर्णांक		btree_cache_used;

	/*
	 * If we need to allocate memory क्रम a new btree node and that
	 * allocation fails, we can cannibalize another node in the btree cache
	 * to satisfy the allocation - lock to guarantee only one thपढ़ो करोes
	 * this at a समय:
	 */
	रुको_queue_head_t	btree_cache_रुको;
	काष्ठा task_काष्ठा	*btree_cache_alloc_lock;
	spinlock_t		btree_cannibalize_lock;

	/*
	 * When we मुक्त a btree node, we increment the gen of the bucket the
	 * node is in - but we can't reग_लिखो the prios and gens until we
	 * finished whatever it is we were करोing, otherwise after a crash the
	 * btree node would be मुक्तd but क्रम say a split, we might not have the
	 * poपूर्णांकers to the new nodes inserted पूर्णांकo the btree yet.
	 *
	 * This is a refcount that blocks prio_ग_लिखो() until the new keys are
	 * written.
	 */
	atomic_t		prio_blocked;
	रुको_queue_head_t	bucket_रुको;

	/*
	 * For any bio we करोn't skip we subtract the number of sectors from
	 * rescale; when it hits 0 we rescale all the bucket priorities.
	 */
	atomic_t		rescale;
	/*
	 * used क्रम GC, identअगरy अगर any front side I/Os is inflight
	 */
	atomic_t		search_inflight;
	/*
	 * When we invalidate buckets, we use both the priority and the amount
	 * of good data to determine which buckets to reuse first - to weight
	 * those together consistently we keep track of the smallest nonzero
	 * priority of any bucket.
	 */
	uपूर्णांक16_t		min_prio;

	/*
	 * max(gen - last_gc) क्रम all buckets. When it माला_लो too big we have to
	 * gc to keep gens from wrapping around.
	 */
	uपूर्णांक8_t			need_gc;
	काष्ठा gc_stat		gc_stats;
	माप_प्रकार			nbuckets;
	माप_प्रकार			avail_nbuckets;

	काष्ठा task_काष्ठा	*gc_thपढ़ो;
	/* Where in the btree gc currently is */
	काष्ठा bkey		gc_करोne;

	/*
	 * For स्वतःmatical garbage collection after ग_लिखोback completed, this
	 * varialbe is used as bit fields,
	 * - 0000 0001b (BCH_ENABLE_AUTO_GC): enable gc after ग_लिखोback
	 * - 0000 0010b (BCH_DO_AUTO_GC):     करो gc after ग_लिखोback
	 * This is an optimization क्रम following ग_लिखो request after ग_लिखोback
	 * finished, but पढ़ो hit rate dropped due to clean data on cache is
	 * discarded. Unless user explicitly sets it via sysfs, it won't be
	 * enabled.
	 */
#घोषणा BCH_ENABLE_AUTO_GC	1
#घोषणा BCH_DO_AUTO_GC		2
	uपूर्णांक8_t			gc_after_ग_लिखोback;

	/*
	 * The allocation code needs gc_mark in काष्ठा bucket to be correct, but
	 * it's not जबतक a gc is in progress. Protected by bucket_lock.
	 */
	पूर्णांक			gc_mark_valid;

	/* Counts how many sectors bio_insert has added to the cache */
	atomic_t		sectors_to_gc;
	रुको_queue_head_t	gc_रुको;

	काष्ठा keybuf		moving_gc_keys;
	/* Number of moving GC bios in flight */
	काष्ठा semaphore	moving_in_flight;

	काष्ठा workqueue_काष्ठा	*moving_gc_wq;

	काष्ठा btree		*root;

#अगर_घोषित CONFIG_BCACHE_DEBUG
	काष्ठा btree		*verअगरy_data;
	काष्ठा bset		*verअगरy_ondisk;
	काष्ठा mutex		verअगरy_lock;
#पूर्ण_अगर

	uपूर्णांक8_t			set_uuid[16];
	अचिन्हित पूर्णांक		nr_uuids;
	काष्ठा uuid_entry	*uuids;
	BKEY_PADDED(uuid_bucket);
	काष्ठा closure		uuid_ग_लिखो;
	काष्ठा semaphore	uuid_ग_लिखो_mutex;

	/*
	 * A btree node on disk could have too many bsets क्रम an iterator to fit
	 * on the stack - have to dynamically allocate them.
	 * bch_cache_set_alloc() will make sure the pool can allocate iterators
	 * equipped with enough room that can host
	 *     (sb.bucket_size / sb.block_size)
	 * btree_iter_sets, which is more than अटल MAX_BSETS.
	 */
	mempool_t		fill_iter;

	काष्ठा bset_sort_state	sort;

	/* List of buckets we're currently writing data to */
	काष्ठा list_head	data_buckets;
	spinlock_t		data_bucket_lock;

	काष्ठा journal		journal;

#घोषणा CONGESTED_MAX		1024
	अचिन्हित पूर्णांक		congested_last_us;
	atomic_t		congested;

	/* The rest of this all shows up in sysfs */
	अचिन्हित पूर्णांक		congested_पढ़ो_threshold_us;
	अचिन्हित पूर्णांक		congested_ग_लिखो_threshold_us;

	काष्ठा समय_stats	btree_gc_समय;
	काष्ठा समय_stats	btree_split_समय;
	काष्ठा समय_stats	btree_पढ़ो_समय;

	atomic_दीर्घ_t		cache_पढ़ो_races;
	atomic_दीर्घ_t		ग_लिखोback_keys_करोne;
	atomic_दीर्घ_t		ग_लिखोback_keys_failed;

	atomic_दीर्घ_t		reclaim;
	atomic_दीर्घ_t		reclaimed_journal_buckets;
	atomic_दीर्घ_t		flush_ग_लिखो;

	क्रमागत			अणु
		ON_ERROR_UNREGISTER,
		ON_ERROR_PANIC,
	पूर्ण			on_error;
#घोषणा DEFAULT_IO_ERROR_LIMIT 8
	अचिन्हित पूर्णांक		error_limit;
	अचिन्हित पूर्णांक		error_decay;

	अचिन्हित लघु		journal_delay_ms;
	bool			expensive_debug_checks;
	अचिन्हित पूर्णांक		verअगरy:1;
	अचिन्हित पूर्णांक		key_merging_disabled:1;
	अचिन्हित पूर्णांक		gc_always_reग_लिखो:1;
	अचिन्हित पूर्णांक		shrinker_disabled:1;
	अचिन्हित पूर्णांक		copy_gc_enabled:1;
	अचिन्हित पूर्णांक		idle_max_ग_लिखोback_rate_enabled:1;

#घोषणा BUCKET_HASH_BITS	12
	काष्ठा hlist_head	bucket_hash[1 << BUCKET_HASH_BITS];
पूर्ण;

काष्ठा bbio अणु
	अचिन्हित पूर्णांक		submit_समय_us;
	जोड़ अणु
		काष्ठा bkey	key;
		uपूर्णांक64_t	_pad[3];
		/*
		 * We only need pad = 3 here because we only ever carry around a
		 * single poपूर्णांकer - i.e. the poपूर्णांकer we're करोing io to/from.
		 */
	पूर्ण;
	काष्ठा bio		bio;
पूर्ण;

#घोषणा BTREE_PRIO		अच_लघु_उच्च
#घोषणा INITIAL_PRIO		32768U

#घोषणा btree_bytes(c)		((c)->btree_pages * PAGE_SIZE)
#घोषणा btree_blocks(b)							\
	((अचिन्हित पूर्णांक) (KEY_SIZE(&b->key) >> (b)->c->block_bits))

#घोषणा btree_शेष_blocks(c)						\
	((अचिन्हित पूर्णांक) ((PAGE_SECTORS * (c)->btree_pages) >> (c)->block_bits))

#घोषणा bucket_bytes(ca)	((ca)->sb.bucket_size << 9)
#घोषणा block_bytes(ca)		((ca)->sb.block_size << 9)

अटल अंतरभूत अचिन्हित पूर्णांक meta_bucket_pages(काष्ठा cache_sb *sb)
अणु
	अचिन्हित पूर्णांक n, max_pages;

	max_pages = min_t(अचिन्हित पूर्णांक,
			  __roundकरोwn_घात_of_two(अच_लघु_उच्च) / PAGE_SECTORS,
			  MAX_ORDER_NR_PAGES);

	n = sb->bucket_size / PAGE_SECTORS;
	अगर (n > max_pages)
		n = max_pages;

	वापस n;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक meta_bucket_bytes(काष्ठा cache_sb *sb)
अणु
	वापस meta_bucket_pages(sb) << PAGE_SHIFT;
पूर्ण

#घोषणा prios_per_bucket(ca)						\
	((meta_bucket_bytes(&(ca)->sb) - माप(काष्ठा prio_set)) /	\
	 माप(काष्ठा bucket_disk))

#घोषणा prio_buckets(ca)						\
	DIV_ROUND_UP((माप_प्रकार) (ca)->sb.nbuckets, prios_per_bucket(ca))

अटल अंतरभूत माप_प्रकार sector_to_bucket(काष्ठा cache_set *c, sector_t s)
अणु
	वापस s >> c->bucket_bits;
पूर्ण

अटल अंतरभूत sector_t bucket_to_sector(काष्ठा cache_set *c, माप_प्रकार b)
अणु
	वापस ((sector_t) b) << c->bucket_bits;
पूर्ण

अटल अंतरभूत sector_t bucket_reमुख्यder(काष्ठा cache_set *c, sector_t s)
अणु
	वापस s & (c->cache->sb.bucket_size - 1);
पूर्ण

अटल अंतरभूत माप_प्रकार PTR_BUCKET_NR(काष्ठा cache_set *c,
				   स्थिर काष्ठा bkey *k,
				   अचिन्हित पूर्णांक ptr)
अणु
	वापस sector_to_bucket(c, PTR_OFFSET(k, ptr));
पूर्ण

अटल अंतरभूत काष्ठा bucket *PTR_BUCKET(काष्ठा cache_set *c,
					स्थिर काष्ठा bkey *k,
					अचिन्हित पूर्णांक ptr)
अणु
	वापस c->cache->buckets + PTR_BUCKET_NR(c, k, ptr);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t gen_after(uपूर्णांक8_t a, uपूर्णांक8_t b)
अणु
	uपूर्णांक8_t r = a - b;

	वापस r > 128U ? 0 : r;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t ptr_stale(काष्ठा cache_set *c, स्थिर काष्ठा bkey *k,
				अचिन्हित पूर्णांक i)
अणु
	वापस gen_after(PTR_BUCKET(c, k, i)->gen, PTR_GEN(k, i));
पूर्ण

अटल अंतरभूत bool ptr_available(काष्ठा cache_set *c, स्थिर काष्ठा bkey *k,
				 अचिन्हित पूर्णांक i)
अणु
	वापस (PTR_DEV(k, i) < MAX_CACHES_PER_SET) && c->cache;
पूर्ण

/* Btree key macros */

/*
 * This is used क्रम various on disk data काष्ठाures - cache_sb, prio_set, bset,
 * jset: The checksum is _always_ the first 8 bytes of these काष्ठाs
 */
#घोषणा csum_set(i)							\
	bch_crc64(((व्योम *) (i)) + माप(uपूर्णांक64_t),			\
		  ((व्योम *) bset_bkey_last(i)) -			\
		  (((व्योम *) (i)) + माप(uपूर्णांक64_t)))

/* Error handling macros */

#घोषणा btree_bug(b, ...)						\
करो अणु									\
	अगर (bch_cache_set_error((b)->c, __VA_ARGS__))			\
		dump_stack();						\
पूर्ण जबतक (0)

#घोषणा cache_bug(c, ...)						\
करो अणु									\
	अगर (bch_cache_set_error(c, __VA_ARGS__))			\
		dump_stack();						\
पूर्ण जबतक (0)

#घोषणा btree_bug_on(cond, b, ...)					\
करो अणु									\
	अगर (cond)							\
		btree_bug(b, __VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा cache_bug_on(cond, c, ...)					\
करो अणु									\
	अगर (cond)							\
		cache_bug(c, __VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा cache_set_err_on(cond, c, ...)					\
करो अणु									\
	अगर (cond)							\
		bch_cache_set_error(c, __VA_ARGS__);			\
पूर्ण जबतक (0)

/* Looping macros */

#घोषणा क्रम_each_bucket(b, ca)						\
	क्रम (b = (ca)->buckets + (ca)->sb.first_bucket;			\
	     b < (ca)->buckets + (ca)->sb.nbuckets; b++)

अटल अंतरभूत व्योम cached_dev_put(काष्ठा cached_dev *dc)
अणु
	अगर (refcount_dec_and_test(&dc->count))
		schedule_work(&dc->detach);
पूर्ण

अटल अंतरभूत bool cached_dev_get(काष्ठा cached_dev *dc)
अणु
	अगर (!refcount_inc_not_zero(&dc->count))
		वापस false;

	/* Paired with the mb in cached_dev_attach */
	smp_mb__after_atomic();
	वापस true;
पूर्ण

/*
 * bucket_gc_gen() वापसs the dअगरference between the bucket's current gen and
 * the oldest gen of any poपूर्णांकer पूर्णांकo that bucket in the btree (last_gc).
 */

अटल अंतरभूत uपूर्णांक8_t bucket_gc_gen(काष्ठा bucket *b)
अणु
	वापस b->gen - b->last_gc;
पूर्ण

#घोषणा BUCKET_GC_GEN_MAX	96U

#घोषणा kobj_attribute_ग_लिखो(n, fn)					\
	अटल काष्ठा kobj_attribute ksysfs_##n = __ATTR(n, 0200, शून्य, fn)

#घोषणा kobj_attribute_rw(n, show, store)				\
	अटल काष्ठा kobj_attribute ksysfs_##n =			\
		__ATTR(n, 0600, show, store)

अटल अंतरभूत व्योम wake_up_allocators(काष्ठा cache_set *c)
अणु
	काष्ठा cache *ca = c->cache;

	wake_up_process(ca->alloc_thपढ़ो);
पूर्ण

अटल अंतरभूत व्योम closure_bio_submit(काष्ठा cache_set *c,
				      काष्ठा bio *bio,
				      काष्ठा closure *cl)
अणु
	closure_get(cl);
	अगर (unlikely(test_bit(CACHE_SET_IO_DISABLE, &c->flags))) अणु
		bio->bi_status = BLK_STS_IOERR;
		bio_endio(bio);
		वापस;
	पूर्ण
	submit_bio_noacct(bio);
पूर्ण

/*
 * Prevent the kthपढ़ो निकासs directly, and make sure when kthपढ़ो_stop()
 * is called to stop a kthपढ़ो, it is still alive. If a kthपढ़ो might be
 * stopped by CACHE_SET_IO_DISABLE bit set, रुको_क्रम_kthपढ़ो_stop() is
 * necessary beक्रमe the kthपढ़ो वापसs.
 */
अटल अंतरभूत व्योम रुको_क्रम_kthपढ़ो_stop(व्योम)
अणु
	जबतक (!kthपढ़ो_should_stop()) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	पूर्ण
पूर्ण

/* Forward declarations */

व्योम bch_count_backing_io_errors(काष्ठा cached_dev *dc, काष्ठा bio *bio);
व्योम bch_count_io_errors(काष्ठा cache *ca, blk_status_t error,
			 पूर्णांक is_पढ़ो, स्थिर अक्षर *m);
व्योम bch_bbio_count_io_errors(काष्ठा cache_set *c, काष्ठा bio *bio,
			      blk_status_t error, स्थिर अक्षर *m);
व्योम bch_bbio_endio(काष्ठा cache_set *c, काष्ठा bio *bio,
		    blk_status_t error, स्थिर अक्षर *m);
व्योम bch_bbio_मुक्त(काष्ठा bio *bio, काष्ठा cache_set *c);
काष्ठा bio *bch_bbio_alloc(काष्ठा cache_set *c);

व्योम __bch_submit_bbio(काष्ठा bio *bio, काष्ठा cache_set *c);
व्योम bch_submit_bbio(काष्ठा bio *bio, काष्ठा cache_set *c,
		     काष्ठा bkey *k, अचिन्हित पूर्णांक ptr);

uपूर्णांक8_t bch_inc_gen(काष्ठा cache *ca, काष्ठा bucket *b);
व्योम bch_rescale_priorities(काष्ठा cache_set *c, पूर्णांक sectors);

bool bch_can_invalidate_bucket(काष्ठा cache *ca, काष्ठा bucket *b);
व्योम __bch_invalidate_one_bucket(काष्ठा cache *ca, काष्ठा bucket *b);

व्योम __bch_bucket_मुक्त(काष्ठा cache *ca, काष्ठा bucket *b);
व्योम bch_bucket_मुक्त(काष्ठा cache_set *c, काष्ठा bkey *k);

दीर्घ bch_bucket_alloc(काष्ठा cache *ca, अचिन्हित पूर्णांक reserve, bool रुको);
पूर्णांक __bch_bucket_alloc_set(काष्ठा cache_set *c, अचिन्हित पूर्णांक reserve,
			   काष्ठा bkey *k, bool रुको);
पूर्णांक bch_bucket_alloc_set(काष्ठा cache_set *c, अचिन्हित पूर्णांक reserve,
			 काष्ठा bkey *k, bool रुको);
bool bch_alloc_sectors(काष्ठा cache_set *c, काष्ठा bkey *k,
		       अचिन्हित पूर्णांक sectors, अचिन्हित पूर्णांक ग_लिखो_poपूर्णांक,
		       अचिन्हित पूर्णांक ग_लिखो_prio, bool रुको);
bool bch_cached_dev_error(काष्ठा cached_dev *dc);

__म_लिखो(2, 3)
bool bch_cache_set_error(काष्ठा cache_set *c, स्थिर अक्षर *fmt, ...);

पूर्णांक bch_prio_ग_लिखो(काष्ठा cache *ca, bool रुको);
व्योम bch_ग_लिखो_bdev_super(काष्ठा cached_dev *dc, काष्ठा closure *parent);

बाह्य काष्ठा workqueue_काष्ठा *bcache_wq;
बाह्य काष्ठा workqueue_काष्ठा *bch_journal_wq;
बाह्य काष्ठा workqueue_काष्ठा *bch_flush_wq;
बाह्य काष्ठा mutex bch_रेजिस्टर_lock;
बाह्य काष्ठा list_head bch_cache_sets;

बाह्य काष्ठा kobj_type bch_cached_dev_ktype;
बाह्य काष्ठा kobj_type bch_flash_dev_ktype;
बाह्य काष्ठा kobj_type bch_cache_set_ktype;
बाह्य काष्ठा kobj_type bch_cache_set_पूर्णांकernal_ktype;
बाह्य काष्ठा kobj_type bch_cache_ktype;

व्योम bch_cached_dev_release(काष्ठा kobject *kobj);
व्योम bch_flash_dev_release(काष्ठा kobject *kobj);
व्योम bch_cache_set_release(काष्ठा kobject *kobj);
व्योम bch_cache_release(काष्ठा kobject *kobj);

पूर्णांक bch_uuid_ग_लिखो(काष्ठा cache_set *c);
व्योम bcache_ग_लिखो_super(काष्ठा cache_set *c);

पूर्णांक bch_flash_dev_create(काष्ठा cache_set *c, uपूर्णांक64_t size);

पूर्णांक bch_cached_dev_attach(काष्ठा cached_dev *dc, काष्ठा cache_set *c,
			  uपूर्णांक8_t *set_uuid);
व्योम bch_cached_dev_detach(काष्ठा cached_dev *dc);
पूर्णांक bch_cached_dev_run(काष्ठा cached_dev *dc);
व्योम bcache_device_stop(काष्ठा bcache_device *d);

व्योम bch_cache_set_unरेजिस्टर(काष्ठा cache_set *c);
व्योम bch_cache_set_stop(काष्ठा cache_set *c);

काष्ठा cache_set *bch_cache_set_alloc(काष्ठा cache_sb *sb);
व्योम bch_btree_cache_मुक्त(काष्ठा cache_set *c);
पूर्णांक bch_btree_cache_alloc(काष्ठा cache_set *c);
व्योम bch_moving_init_cache_set(काष्ठा cache_set *c);
पूर्णांक bch_खोलो_buckets_alloc(काष्ठा cache_set *c);
व्योम bch_खोलो_buckets_मुक्त(काष्ठा cache_set *c);

पूर्णांक bch_cache_allocator_start(काष्ठा cache *ca);

व्योम bch_debug_निकास(व्योम);
व्योम bch_debug_init(व्योम);
व्योम bch_request_निकास(व्योम);
पूर्णांक bch_request_init(व्योम);
व्योम bch_btree_निकास(व्योम);
पूर्णांक bch_btree_init(व्योम);

#पूर्ण_अगर /* _BCACHE_H */
