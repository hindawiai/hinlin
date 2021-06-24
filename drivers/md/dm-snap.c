<शैली गुरु>
/*
 * Copyright (C) 2001-2002 Sistina Software (UK) Limited.
 *
 * This file is released under the GPL.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/device-mapper.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/list.h>
#समावेश <linux/list_bl.h>
#समावेश <linux/mempool.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/log2.h>
#समावेश <linux/dm-kcopyd.h>

#समावेश "dm.h"

#समावेश "dm-exception-store.h"

#घोषणा DM_MSG_PREFIX "snapshots"

अटल स्थिर अक्षर dm_snapshot_merge_target_name[] = "snapshot-merge";

#घोषणा dm_target_is_snapshot_merge(ti) \
	((ti)->type->name == dm_snapshot_merge_target_name)

/*
 * The size of the mempool used to track chunks in use.
 */
#घोषणा MIN_IOS 256

#घोषणा DM_TRACKED_CHUNK_HASH_SIZE	16
#घोषणा DM_TRACKED_CHUNK_HASH(x)	((अचिन्हित दीर्घ)(x) & \
					 (DM_TRACKED_CHUNK_HASH_SIZE - 1))

काष्ठा dm_exception_table अणु
	uपूर्णांक32_t hash_mask;
	अचिन्हित hash_shअगरt;
	काष्ठा hlist_bl_head *table;
पूर्ण;

काष्ठा dm_snapshot अणु
	काष्ठा rw_semaphore lock;

	काष्ठा dm_dev *origin;
	काष्ठा dm_dev *cow;

	काष्ठा dm_target *ti;

	/* List of snapshots per Origin */
	काष्ठा list_head list;

	/*
	 * You can't use a snapshot अगर this is 0 (e.g. अगर full).
	 * A snapshot-merge target never clears this.
	 */
	पूर्णांक valid;

	/*
	 * The snapshot overflowed because of a ग_लिखो to the snapshot device.
	 * We करोn't have to invalidate the snapshot in this हाल, but we need
	 * to prevent further ग_लिखोs.
	 */
	पूर्णांक snapshot_overflowed;

	/* Origin ग_लिखोs करोn't trigger exceptions until this is set */
	पूर्णांक active;

	atomic_t pending_exceptions_count;

	spinlock_t pe_allocation_lock;

	/* Protected by "pe_allocation_lock" */
	sector_t exception_start_sequence;

	/* Protected by kcopyd single-thपढ़ोed callback */
	sector_t exception_complete_sequence;

	/*
	 * A list of pending exceptions that completed out of order.
	 * Protected by kcopyd single-thपढ़ोed callback.
	 */
	काष्ठा rb_root out_of_order_tree;

	mempool_t pending_pool;

	काष्ठा dm_exception_table pending;
	काष्ठा dm_exception_table complete;

	/*
	 * pe_lock protects all pending_exception operations and access
	 * as well as the snapshot_bios list.
	 */
	spinlock_t pe_lock;

	/* Chunks with outstanding पढ़ोs */
	spinlock_t tracked_chunk_lock;
	काष्ठा hlist_head tracked_chunk_hash[DM_TRACKED_CHUNK_HASH_SIZE];

	/* The on disk metadata handler */
	काष्ठा dm_exception_store *store;

	अचिन्हित in_progress;
	काष्ठा रुको_queue_head in_progress_रुको;

	काष्ठा dm_kcopyd_client *kcopyd_client;

	/* Wait क्रम events based on state_bits */
	अचिन्हित दीर्घ state_bits;

	/* Range of chunks currently being merged. */
	chunk_t first_merging_chunk;
	पूर्णांक num_merging_chunks;

	/*
	 * The merge operation failed अगर this flag is set.
	 * Failure modes are handled as follows:
	 * - I/O error पढ़ोing the header
	 *   	=> करोn't load the target; पात.
	 * - Header करोes not have "valid" flag set
	 *   	=> use the origin; क्रमget about the snapshot.
	 * - I/O error when पढ़ोing exceptions
	 *   	=> करोn't load the target; पात.
	 *         (We can't use the पूर्णांकermediate origin state.)
	 * - I/O error जबतक merging
	 *	=> stop merging; set merge_failed; process I/O normally.
	 */
	bool merge_failed:1;

	bool discard_zeroes_cow:1;
	bool discard_passकरोwn_origin:1;

	/*
	 * Incoming bios that overlap with chunks being merged must रुको
	 * क्रम them to be committed.
	 */
	काष्ठा bio_list bios_queued_during_merge;

	/*
	 * Flush data after merge.
	 */
	काष्ठा bio flush_bio;
पूर्ण;

/*
 * state_bits:
 *   RUNNING_MERGE  - Merge operation is in progress.
 *   SHUTDOWN_MERGE - Set to संकेत that merge needs to be stopped;
 *                    cleared afterwards.
 */
#घोषणा RUNNING_MERGE          0
#घोषणा SHUTDOWN_MERGE         1

/*
 * Maximum number of chunks being copied on ग_लिखो.
 *
 * The value was decided experimentally as a trade-off between memory
 * consumption, stalling the kernel's workqueues and मुख्यtaining a high enough
 * throughput.
 */
#घोषणा DEFAULT_COW_THRESHOLD 2048

अटल अचिन्हित cow_threshold = DEFAULT_COW_THRESHOLD;
module_param_named(snapshot_cow_threshold, cow_threshold, uपूर्णांक, 0644);
MODULE_PARM_DESC(snapshot_cow_threshold, "Maximum number of chunks being copied on write");

DECLARE_DM_KCOPYD_THROTTLE_WITH_MODULE_PARM(snapshot_copy_throttle,
		"A percentage of time allocated for copy on write");

काष्ठा dm_dev *dm_snap_origin(काष्ठा dm_snapshot *s)
अणु
	वापस s->origin;
पूर्ण
EXPORT_SYMBOL(dm_snap_origin);

काष्ठा dm_dev *dm_snap_cow(काष्ठा dm_snapshot *s)
अणु
	वापस s->cow;
पूर्ण
EXPORT_SYMBOL(dm_snap_cow);

अटल sector_t chunk_to_sector(काष्ठा dm_exception_store *store,
				chunk_t chunk)
अणु
	वापस chunk << store->chunk_shअगरt;
पूर्ण

अटल पूर्णांक bdev_equal(काष्ठा block_device *lhs, काष्ठा block_device *rhs)
अणु
	/*
	 * There is only ever one instance of a particular block
	 * device so we can compare poपूर्णांकers safely.
	 */
	वापस lhs == rhs;
पूर्ण

काष्ठा dm_snap_pending_exception अणु
	काष्ठा dm_exception e;

	/*
	 * Origin buffers रुकोing क्रम this to complete are held
	 * in a bio list
	 */
	काष्ठा bio_list origin_bios;
	काष्ठा bio_list snapshot_bios;

	/* Poपूर्णांकer back to snapshot context */
	काष्ठा dm_snapshot *snap;

	/*
	 * 1 indicates the exception has alपढ़ोy been sent to
	 * kcopyd.
	 */
	पूर्णांक started;

	/* There was copying error. */
	पूर्णांक copy_error;

	/* A sequence number, it is used क्रम in-order completion. */
	sector_t exception_sequence;

	काष्ठा rb_node out_of_order_node;

	/*
	 * For writing a complete chunk, bypassing the copy.
	 */
	काष्ठा bio *full_bio;
	bio_end_io_t *full_bio_end_io;
पूर्ण;

/*
 * Hash table mapping origin volumes to lists of snapshots and
 * a lock to protect it
 */
अटल काष्ठा kmem_cache *exception_cache;
अटल काष्ठा kmem_cache *pending_cache;

काष्ठा dm_snap_tracked_chunk अणु
	काष्ठा hlist_node node;
	chunk_t chunk;
पूर्ण;

अटल व्योम init_tracked_chunk(काष्ठा bio *bio)
अणु
	काष्ठा dm_snap_tracked_chunk *c = dm_per_bio_data(bio, माप(काष्ठा dm_snap_tracked_chunk));
	INIT_HLIST_NODE(&c->node);
पूर्ण

अटल bool is_bio_tracked(काष्ठा bio *bio)
अणु
	काष्ठा dm_snap_tracked_chunk *c = dm_per_bio_data(bio, माप(काष्ठा dm_snap_tracked_chunk));
	वापस !hlist_unhashed(&c->node);
पूर्ण

अटल व्योम track_chunk(काष्ठा dm_snapshot *s, काष्ठा bio *bio, chunk_t chunk)
अणु
	काष्ठा dm_snap_tracked_chunk *c = dm_per_bio_data(bio, माप(काष्ठा dm_snap_tracked_chunk));

	c->chunk = chunk;

	spin_lock_irq(&s->tracked_chunk_lock);
	hlist_add_head(&c->node,
		       &s->tracked_chunk_hash[DM_TRACKED_CHUNK_HASH(chunk)]);
	spin_unlock_irq(&s->tracked_chunk_lock);
पूर्ण

अटल व्योम stop_tracking_chunk(काष्ठा dm_snapshot *s, काष्ठा bio *bio)
अणु
	काष्ठा dm_snap_tracked_chunk *c = dm_per_bio_data(bio, माप(काष्ठा dm_snap_tracked_chunk));
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->tracked_chunk_lock, flags);
	hlist_del(&c->node);
	spin_unlock_irqrestore(&s->tracked_chunk_lock, flags);
पूर्ण

अटल पूर्णांक __chunk_is_tracked(काष्ठा dm_snapshot *s, chunk_t chunk)
अणु
	काष्ठा dm_snap_tracked_chunk *c;
	पूर्णांक found = 0;

	spin_lock_irq(&s->tracked_chunk_lock);

	hlist_क्रम_each_entry(c,
	    &s->tracked_chunk_hash[DM_TRACKED_CHUNK_HASH(chunk)], node) अणु
		अगर (c->chunk == chunk) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irq(&s->tracked_chunk_lock);

	वापस found;
पूर्ण

/*
 * This conflicting I/O is extremely improbable in the caller,
 * so msleep(1) is sufficient and there is no need क्रम a रुको queue.
 */
अटल व्योम __check_क्रम_conflicting_io(काष्ठा dm_snapshot *s, chunk_t chunk)
अणु
	जबतक (__chunk_is_tracked(s, chunk))
		msleep(1);
पूर्ण

/*
 * One of these per रेजिस्टरed origin, held in the snapshot_origins hash
 */
काष्ठा origin अणु
	/* The origin device */
	काष्ठा block_device *bdev;

	काष्ठा list_head hash_list;

	/* List of snapshots क्रम this origin */
	काष्ठा list_head snapshots;
पूर्ण;

/*
 * This काष्ठाure is allocated क्रम each origin target
 */
काष्ठा dm_origin अणु
	काष्ठा dm_dev *dev;
	काष्ठा dm_target *ti;
	अचिन्हित split_boundary;
	काष्ठा list_head hash_list;
पूर्ण;

/*
 * Size of the hash table क्रम origin volumes. If we make this
 * the size of the minors list then it should be nearly perfect
 */
#घोषणा ORIGIN_HASH_SIZE 256
#घोषणा ORIGIN_MASK      0xFF
अटल काष्ठा list_head *_origins;
अटल काष्ठा list_head *_dm_origins;
अटल काष्ठा rw_semaphore _origins_lock;

अटल DECLARE_WAIT_QUEUE_HEAD(_pending_exceptions_करोne);
अटल DEFINE_SPINLOCK(_pending_exceptions_करोne_spinlock);
अटल uपूर्णांक64_t _pending_exceptions_करोne_count;

अटल पूर्णांक init_origin_hash(व्योम)
अणु
	पूर्णांक i;

	_origins = kदो_स्मृति_array(ORIGIN_HASH_SIZE, माप(काष्ठा list_head),
				 GFP_KERNEL);
	अगर (!_origins) अणु
		DMERR("unable to allocate memory for _origins");
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < ORIGIN_HASH_SIZE; i++)
		INIT_LIST_HEAD(_origins + i);

	_dm_origins = kदो_स्मृति_array(ORIGIN_HASH_SIZE,
				    माप(काष्ठा list_head),
				    GFP_KERNEL);
	अगर (!_dm_origins) अणु
		DMERR("unable to allocate memory for _dm_origins");
		kमुक्त(_origins);
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < ORIGIN_HASH_SIZE; i++)
		INIT_LIST_HEAD(_dm_origins + i);

	init_rwsem(&_origins_lock);

	वापस 0;
पूर्ण

अटल व्योम निकास_origin_hash(व्योम)
अणु
	kमुक्त(_origins);
	kमुक्त(_dm_origins);
पूर्ण

अटल अचिन्हित origin_hash(काष्ठा block_device *bdev)
अणु
	वापस bdev->bd_dev & ORIGIN_MASK;
पूर्ण

अटल काष्ठा origin *__lookup_origin(काष्ठा block_device *origin)
अणु
	काष्ठा list_head *ol;
	काष्ठा origin *o;

	ol = &_origins[origin_hash(origin)];
	list_क्रम_each_entry (o, ol, hash_list)
		अगर (bdev_equal(o->bdev, origin))
			वापस o;

	वापस शून्य;
पूर्ण

अटल व्योम __insert_origin(काष्ठा origin *o)
अणु
	काष्ठा list_head *sl = &_origins[origin_hash(o->bdev)];
	list_add_tail(&o->hash_list, sl);
पूर्ण

अटल काष्ठा dm_origin *__lookup_dm_origin(काष्ठा block_device *origin)
अणु
	काष्ठा list_head *ol;
	काष्ठा dm_origin *o;

	ol = &_dm_origins[origin_hash(origin)];
	list_क्रम_each_entry (o, ol, hash_list)
		अगर (bdev_equal(o->dev->bdev, origin))
			वापस o;

	वापस शून्य;
पूर्ण

अटल व्योम __insert_dm_origin(काष्ठा dm_origin *o)
अणु
	काष्ठा list_head *sl = &_dm_origins[origin_hash(o->dev->bdev)];
	list_add_tail(&o->hash_list, sl);
पूर्ण

अटल व्योम __हटाओ_dm_origin(काष्ठा dm_origin *o)
अणु
	list_del(&o->hash_list);
पूर्ण

/*
 * _origins_lock must be held when calling this function.
 * Returns number of snapshots रेजिस्टरed using the supplied cow device, plus:
 * snap_src - a snapshot suitable क्रम use as a source of exception hanकरोver
 * snap_dest - a snapshot capable of receiving exception hanकरोver.
 * snap_merge - an existing snapshot-merge target linked to the same origin.
 *   There can be at most one snapshot-merge target. The parameter is optional.
 *
 * Possible वापस values and states of snap_src and snap_dest.
 *   0: शून्य, शून्य  - first new snapshot
 *   1: snap_src, शून्य - normal snapshot
 *   2: snap_src, snap_dest  - रुकोing क्रम hanकरोver
 *   2: snap_src, शून्य - handed over, रुकोing क्रम old to be deleted
 *   1: शून्य, snap_dest - source got destroyed without hanकरोver
 */
अटल पूर्णांक __find_snapshots_sharing_cow(काष्ठा dm_snapshot *snap,
					काष्ठा dm_snapshot **snap_src,
					काष्ठा dm_snapshot **snap_dest,
					काष्ठा dm_snapshot **snap_merge)
अणु
	काष्ठा dm_snapshot *s;
	काष्ठा origin *o;
	पूर्णांक count = 0;
	पूर्णांक active;

	o = __lookup_origin(snap->origin->bdev);
	अगर (!o)
		जाओ out;

	list_क्रम_each_entry(s, &o->snapshots, list) अणु
		अगर (dm_target_is_snapshot_merge(s->ti) && snap_merge)
			*snap_merge = s;
		अगर (!bdev_equal(s->cow->bdev, snap->cow->bdev))
			जारी;

		करोwn_पढ़ो(&s->lock);
		active = s->active;
		up_पढ़ो(&s->lock);

		अगर (active) अणु
			अगर (snap_src)
				*snap_src = s;
		पूर्ण अन्यथा अगर (snap_dest)
			*snap_dest = s;

		count++;
	पूर्ण

out:
	वापस count;
पूर्ण

/*
 * On success, वापसs 1 अगर this snapshot is a hanकरोver destination,
 * otherwise वापसs 0.
 */
अटल पूर्णांक __validate_exception_hanकरोver(काष्ठा dm_snapshot *snap)
अणु
	काष्ठा dm_snapshot *snap_src = शून्य, *snap_dest = शून्य;
	काष्ठा dm_snapshot *snap_merge = शून्य;

	/* Does snapshot need exceptions handed over to it? */
	अगर ((__find_snapshots_sharing_cow(snap, &snap_src, &snap_dest,
					  &snap_merge) == 2) ||
	    snap_dest) अणु
		snap->ti->error = "Snapshot cow pairing for exception "
				  "table handover failed";
		वापस -EINVAL;
	पूर्ण

	/*
	 * If no snap_src was found, snap cannot become a hanकरोver
	 * destination.
	 */
	अगर (!snap_src)
		वापस 0;

	/*
	 * Non-snapshot-merge hanकरोver?
	 */
	अगर (!dm_target_is_snapshot_merge(snap->ti))
		वापस 1;

	/*
	 * Do not allow more than one merging snapshot.
	 */
	अगर (snap_merge) अणु
		snap->ti->error = "A snapshot is already merging.";
		वापस -EINVAL;
	पूर्ण

	अगर (!snap_src->store->type->prepare_merge ||
	    !snap_src->store->type->commit_merge) अणु
		snap->ti->error = "Snapshot exception store does not "
				  "support snapshot-merge.";
		वापस -EINVAL;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम __insert_snapshot(काष्ठा origin *o, काष्ठा dm_snapshot *s)
अणु
	काष्ठा dm_snapshot *l;

	/* Sort the list according to chunk size, largest-first smallest-last */
	list_क्रम_each_entry(l, &o->snapshots, list)
		अगर (l->store->chunk_size < s->store->chunk_size)
			अवरोध;
	list_add_tail(&s->list, &l->list);
पूर्ण

/*
 * Make a note of the snapshot and its origin so we can look it
 * up when the origin has a ग_लिखो on it.
 *
 * Also validate snapshot exception store hanकरोvers.
 * On success, वापसs 1 अगर this registration is a hanकरोver destination,
 * otherwise वापसs 0.
 */
अटल पूर्णांक रेजिस्टर_snapshot(काष्ठा dm_snapshot *snap)
अणु
	काष्ठा origin *o, *new_o = शून्य;
	काष्ठा block_device *bdev = snap->origin->bdev;
	पूर्णांक r = 0;

	new_o = kदो_स्मृति(माप(*new_o), GFP_KERNEL);
	अगर (!new_o)
		वापस -ENOMEM;

	करोwn_ग_लिखो(&_origins_lock);

	r = __validate_exception_hanकरोver(snap);
	अगर (r < 0) अणु
		kमुक्त(new_o);
		जाओ out;
	पूर्ण

	o = __lookup_origin(bdev);
	अगर (o)
		kमुक्त(new_o);
	अन्यथा अणु
		/* New origin */
		o = new_o;

		/* Initialise the काष्ठा */
		INIT_LIST_HEAD(&o->snapshots);
		o->bdev = bdev;

		__insert_origin(o);
	पूर्ण

	__insert_snapshot(o, snap);

out:
	up_ग_लिखो(&_origins_lock);

	वापस r;
पूर्ण

/*
 * Move snapshot to correct place in list according to chunk size.
 */
अटल व्योम reरेजिस्टर_snapshot(काष्ठा dm_snapshot *s)
अणु
	काष्ठा block_device *bdev = s->origin->bdev;

	करोwn_ग_लिखो(&_origins_lock);

	list_del(&s->list);
	__insert_snapshot(__lookup_origin(bdev), s);

	up_ग_लिखो(&_origins_lock);
पूर्ण

अटल व्योम unरेजिस्टर_snapshot(काष्ठा dm_snapshot *s)
अणु
	काष्ठा origin *o;

	करोwn_ग_लिखो(&_origins_lock);
	o = __lookup_origin(s->origin->bdev);

	list_del(&s->list);
	अगर (o && list_empty(&o->snapshots)) अणु
		list_del(&o->hash_list);
		kमुक्त(o);
	पूर्ण

	up_ग_लिखो(&_origins_lock);
पूर्ण

/*
 * Implementation of the exception hash tables.
 * The lowest hash_shअगरt bits of the chunk number are ignored, allowing
 * some consecutive chunks to be grouped together.
 */
अटल uपूर्णांक32_t exception_hash(काष्ठा dm_exception_table *et, chunk_t chunk);

/* Lock to protect access to the completed and pending exception hash tables. */
काष्ठा dm_exception_table_lock अणु
	काष्ठा hlist_bl_head *complete_slot;
	काष्ठा hlist_bl_head *pending_slot;
पूर्ण;

अटल व्योम dm_exception_table_lock_init(काष्ठा dm_snapshot *s, chunk_t chunk,
					 काष्ठा dm_exception_table_lock *lock)
अणु
	काष्ठा dm_exception_table *complete = &s->complete;
	काष्ठा dm_exception_table *pending = &s->pending;

	lock->complete_slot = &complete->table[exception_hash(complete, chunk)];
	lock->pending_slot = &pending->table[exception_hash(pending, chunk)];
पूर्ण

अटल व्योम dm_exception_table_lock(काष्ठा dm_exception_table_lock *lock)
अणु
	hlist_bl_lock(lock->complete_slot);
	hlist_bl_lock(lock->pending_slot);
पूर्ण

अटल व्योम dm_exception_table_unlock(काष्ठा dm_exception_table_lock *lock)
अणु
	hlist_bl_unlock(lock->pending_slot);
	hlist_bl_unlock(lock->complete_slot);
पूर्ण

अटल पूर्णांक dm_exception_table_init(काष्ठा dm_exception_table *et,
				   uपूर्णांक32_t size, अचिन्हित hash_shअगरt)
अणु
	अचिन्हित पूर्णांक i;

	et->hash_shअगरt = hash_shअगरt;
	et->hash_mask = size - 1;
	et->table = kvदो_स्मृति_array(size, माप(काष्ठा hlist_bl_head),
				   GFP_KERNEL);
	अगर (!et->table)
		वापस -ENOMEM;

	क्रम (i = 0; i < size; i++)
		INIT_HLIST_BL_HEAD(et->table + i);

	वापस 0;
पूर्ण

अटल व्योम dm_exception_table_निकास(काष्ठा dm_exception_table *et,
				    काष्ठा kmem_cache *mem)
अणु
	काष्ठा hlist_bl_head *slot;
	काष्ठा dm_exception *ex;
	काष्ठा hlist_bl_node *pos, *n;
	पूर्णांक i, size;

	size = et->hash_mask + 1;
	क्रम (i = 0; i < size; i++) अणु
		slot = et->table + i;

		hlist_bl_क्रम_each_entry_safe(ex, pos, n, slot, hash_list)
			kmem_cache_मुक्त(mem, ex);
	पूर्ण

	kvमुक्त(et->table);
पूर्ण

अटल uपूर्णांक32_t exception_hash(काष्ठा dm_exception_table *et, chunk_t chunk)
अणु
	वापस (chunk >> et->hash_shअगरt) & et->hash_mask;
पूर्ण

अटल व्योम dm_हटाओ_exception(काष्ठा dm_exception *e)
अणु
	hlist_bl_del(&e->hash_list);
पूर्ण

/*
 * Return the exception data क्रम a sector, or शून्य अगर not
 * remapped.
 */
अटल काष्ठा dm_exception *dm_lookup_exception(काष्ठा dm_exception_table *et,
						chunk_t chunk)
अणु
	काष्ठा hlist_bl_head *slot;
	काष्ठा hlist_bl_node *pos;
	काष्ठा dm_exception *e;

	slot = &et->table[exception_hash(et, chunk)];
	hlist_bl_क्रम_each_entry(e, pos, slot, hash_list)
		अगर (chunk >= e->old_chunk &&
		    chunk <= e->old_chunk + dm_consecutive_chunk_count(e))
			वापस e;

	वापस शून्य;
पूर्ण

अटल काष्ठा dm_exception *alloc_completed_exception(gfp_t gfp)
अणु
	काष्ठा dm_exception *e;

	e = kmem_cache_alloc(exception_cache, gfp);
	अगर (!e && gfp == GFP_NOIO)
		e = kmem_cache_alloc(exception_cache, GFP_ATOMIC);

	वापस e;
पूर्ण

अटल व्योम मुक्त_completed_exception(काष्ठा dm_exception *e)
अणु
	kmem_cache_मुक्त(exception_cache, e);
पूर्ण

अटल काष्ठा dm_snap_pending_exception *alloc_pending_exception(काष्ठा dm_snapshot *s)
अणु
	काष्ठा dm_snap_pending_exception *pe = mempool_alloc(&s->pending_pool,
							     GFP_NOIO);

	atomic_inc(&s->pending_exceptions_count);
	pe->snap = s;

	वापस pe;
पूर्ण

अटल व्योम मुक्त_pending_exception(काष्ठा dm_snap_pending_exception *pe)
अणु
	काष्ठा dm_snapshot *s = pe->snap;

	mempool_मुक्त(pe, &s->pending_pool);
	smp_mb__beक्रमe_atomic();
	atomic_dec(&s->pending_exceptions_count);
पूर्ण

अटल व्योम dm_insert_exception(काष्ठा dm_exception_table *eh,
				काष्ठा dm_exception *new_e)
अणु
	काष्ठा hlist_bl_head *l;
	काष्ठा hlist_bl_node *pos;
	काष्ठा dm_exception *e = शून्य;

	l = &eh->table[exception_hash(eh, new_e->old_chunk)];

	/* Add immediately अगर this table करोesn't support consecutive chunks */
	अगर (!eh->hash_shअगरt)
		जाओ out;

	/* List is ordered by old_chunk */
	hlist_bl_क्रम_each_entry(e, pos, l, hash_list) अणु
		/* Insert after an existing chunk? */
		अगर (new_e->old_chunk == (e->old_chunk +
					 dm_consecutive_chunk_count(e) + 1) &&
		    new_e->new_chunk == (dm_chunk_number(e->new_chunk) +
					 dm_consecutive_chunk_count(e) + 1)) अणु
			dm_consecutive_chunk_count_inc(e);
			मुक्त_completed_exception(new_e);
			वापस;
		पूर्ण

		/* Insert beक्रमe an existing chunk? */
		अगर (new_e->old_chunk == (e->old_chunk - 1) &&
		    new_e->new_chunk == (dm_chunk_number(e->new_chunk) - 1)) अणु
			dm_consecutive_chunk_count_inc(e);
			e->old_chunk--;
			e->new_chunk--;
			मुक्त_completed_exception(new_e);
			वापस;
		पूर्ण

		अगर (new_e->old_chunk < e->old_chunk)
			अवरोध;
	पूर्ण

out:
	अगर (!e) अणु
		/*
		 * Either the table करोesn't support consecutive chunks or slot
		 * l is empty.
		 */
		hlist_bl_add_head(&new_e->hash_list, l);
	पूर्ण अन्यथा अगर (new_e->old_chunk < e->old_chunk) अणु
		/* Add beक्रमe an existing exception */
		hlist_bl_add_beक्रमe(&new_e->hash_list, &e->hash_list);
	पूर्ण अन्यथा अणु
		/* Add to l's tail: e is the last exception in this slot */
		hlist_bl_add_behind(&new_e->hash_list, &e->hash_list);
	पूर्ण
पूर्ण

/*
 * Callback used by the exception stores to load exceptions when
 * initialising.
 */
अटल पूर्णांक dm_add_exception(व्योम *context, chunk_t old, chunk_t new)
अणु
	काष्ठा dm_exception_table_lock lock;
	काष्ठा dm_snapshot *s = context;
	काष्ठा dm_exception *e;

	e = alloc_completed_exception(GFP_KERNEL);
	अगर (!e)
		वापस -ENOMEM;

	e->old_chunk = old;

	/* Consecutive_count is implicitly initialised to zero */
	e->new_chunk = new;

	/*
	 * Although there is no need to lock access to the exception tables
	 * here, अगर we करोn't then hlist_bl_add_head(), called by
	 * dm_insert_exception(), will complain about accessing the
	 * corresponding list without locking it first.
	 */
	dm_exception_table_lock_init(s, old, &lock);

	dm_exception_table_lock(&lock);
	dm_insert_exception(&s->complete, e);
	dm_exception_table_unlock(&lock);

	वापस 0;
पूर्ण

/*
 * Return a minimum chunk size of all snapshots that have the specअगरied origin.
 * Return zero अगर the origin has no snapshots.
 */
अटल uपूर्णांक32_t __minimum_chunk_size(काष्ठा origin *o)
अणु
	काष्ठा dm_snapshot *snap;
	अचिन्हित chunk_size = roundकरोwn_घात_of_two(अच_पूर्णांक_उच्च);

	अगर (o)
		list_क्रम_each_entry(snap, &o->snapshots, list)
			chunk_size = min_not_zero(chunk_size,
						  snap->store->chunk_size);

	वापस (uपूर्णांक32_t) chunk_size;
पूर्ण

/*
 * Hard coded magic.
 */
अटल पूर्णांक calc_max_buckets(व्योम)
अणु
	/* use a fixed size of 2MB */
	अचिन्हित दीर्घ mem = 2 * 1024 * 1024;
	mem /= माप(काष्ठा hlist_bl_head);

	वापस mem;
पूर्ण

/*
 * Allocate room क्रम a suitable hash table.
 */
अटल पूर्णांक init_hash_tables(काष्ठा dm_snapshot *s)
अणु
	sector_t hash_size, cow_dev_size, max_buckets;

	/*
	 * Calculate based on the size of the original volume or
	 * the COW volume...
	 */
	cow_dev_size = get_dev_size(s->cow->bdev);
	max_buckets = calc_max_buckets();

	hash_size = cow_dev_size >> s->store->chunk_shअगरt;
	hash_size = min(hash_size, max_buckets);

	अगर (hash_size < 64)
		hash_size = 64;
	hash_size = roundकरोwn_घात_of_two(hash_size);
	अगर (dm_exception_table_init(&s->complete, hash_size,
				    DM_CHUNK_CONSECUTIVE_BITS))
		वापस -ENOMEM;

	/*
	 * Allocate hash table क्रम in-flight exceptions
	 * Make this smaller than the real hash table
	 */
	hash_size >>= 3;
	अगर (hash_size < 64)
		hash_size = 64;

	अगर (dm_exception_table_init(&s->pending, hash_size, 0)) अणु
		dm_exception_table_निकास(&s->complete, exception_cache);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम merge_shutकरोwn(काष्ठा dm_snapshot *s)
अणु
	clear_bit_unlock(RUNNING_MERGE, &s->state_bits);
	smp_mb__after_atomic();
	wake_up_bit(&s->state_bits, RUNNING_MERGE);
पूर्ण

अटल काष्ठा bio *__release_queued_bios_after_merge(काष्ठा dm_snapshot *s)
अणु
	s->first_merging_chunk = 0;
	s->num_merging_chunks = 0;

	वापस bio_list_get(&s->bios_queued_during_merge);
पूर्ण

/*
 * Remove one chunk from the index of completed exceptions.
 */
अटल पूर्णांक __हटाओ_single_exception_chunk(काष्ठा dm_snapshot *s,
					   chunk_t old_chunk)
अणु
	काष्ठा dm_exception *e;

	e = dm_lookup_exception(&s->complete, old_chunk);
	अगर (!e) अणु
		DMERR("Corruption detected: exception for block %llu is "
		      "on disk but not in memory",
		      (अचिन्हित दीर्घ दीर्घ)old_chunk);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If this is the only chunk using this exception, हटाओ exception.
	 */
	अगर (!dm_consecutive_chunk_count(e)) अणु
		dm_हटाओ_exception(e);
		मुक्त_completed_exception(e);
		वापस 0;
	पूर्ण

	/*
	 * The chunk may be either at the beginning or the end of a
	 * group of consecutive chunks - never in the middle.  We are
	 * removing chunks in the opposite order to that in which they
	 * were added, so this should always be true.
	 * Decrement the consecutive chunk counter and adjust the
	 * starting poपूर्णांक अगर necessary.
	 */
	अगर (old_chunk == e->old_chunk) अणु
		e->old_chunk++;
		e->new_chunk++;
	पूर्ण अन्यथा अगर (old_chunk != e->old_chunk +
		   dm_consecutive_chunk_count(e)) अणु
		DMERR("Attempt to merge block %llu from the "
		      "middle of a chunk range [%llu - %llu]",
		      (अचिन्हित दीर्घ दीर्घ)old_chunk,
		      (अचिन्हित दीर्घ दीर्घ)e->old_chunk,
		      (अचिन्हित दीर्घ दीर्घ)
		      e->old_chunk + dm_consecutive_chunk_count(e));
		वापस -EINVAL;
	पूर्ण

	dm_consecutive_chunk_count_dec(e);

	वापस 0;
पूर्ण

अटल व्योम flush_bios(काष्ठा bio *bio);

अटल पूर्णांक हटाओ_single_exception_chunk(काष्ठा dm_snapshot *s)
अणु
	काष्ठा bio *b = शून्य;
	पूर्णांक r;
	chunk_t old_chunk = s->first_merging_chunk + s->num_merging_chunks - 1;

	करोwn_ग_लिखो(&s->lock);

	/*
	 * Process chunks (and associated exceptions) in reverse order
	 * so that dm_consecutive_chunk_count_dec() accounting works.
	 */
	करो अणु
		r = __हटाओ_single_exception_chunk(s, old_chunk);
		अगर (r)
			जाओ out;
	पूर्ण जबतक (old_chunk-- > s->first_merging_chunk);

	b = __release_queued_bios_after_merge(s);

out:
	up_ग_लिखो(&s->lock);
	अगर (b)
		flush_bios(b);

	वापस r;
पूर्ण

अटल पूर्णांक origin_ग_लिखो_extent(काष्ठा dm_snapshot *merging_snap,
			       sector_t sector, अचिन्हित chunk_size);

अटल व्योम merge_callback(पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err,
			   व्योम *context);

अटल uपूर्णांक64_t पढ़ो_pending_exceptions_करोne_count(व्योम)
अणु
	uपूर्णांक64_t pending_exceptions_करोne;

	spin_lock(&_pending_exceptions_करोne_spinlock);
	pending_exceptions_करोne = _pending_exceptions_करोne_count;
	spin_unlock(&_pending_exceptions_करोne_spinlock);

	वापस pending_exceptions_करोne;
पूर्ण

अटल व्योम increment_pending_exceptions_करोne_count(व्योम)
अणु
	spin_lock(&_pending_exceptions_करोne_spinlock);
	_pending_exceptions_करोne_count++;
	spin_unlock(&_pending_exceptions_करोne_spinlock);

	wake_up_all(&_pending_exceptions_करोne);
पूर्ण

अटल व्योम snapshot_merge_next_chunks(काष्ठा dm_snapshot *s)
अणु
	पूर्णांक i, linear_chunks;
	chunk_t old_chunk, new_chunk;
	काष्ठा dm_io_region src, dest;
	sector_t io_size;
	uपूर्णांक64_t previous_count;

	BUG_ON(!test_bit(RUNNING_MERGE, &s->state_bits));
	अगर (unlikely(test_bit(SHUTDOWN_MERGE, &s->state_bits)))
		जाओ shut;

	/*
	 * valid flag never changes during merge, so no lock required.
	 */
	अगर (!s->valid) अणु
		DMERR("Snapshot is invalid: can't merge");
		जाओ shut;
	पूर्ण

	linear_chunks = s->store->type->prepare_merge(s->store, &old_chunk,
						      &new_chunk);
	अगर (linear_chunks <= 0) अणु
		अगर (linear_chunks < 0) अणु
			DMERR("Read error in exception store: "
			      "shutting down merge");
			करोwn_ग_लिखो(&s->lock);
			s->merge_failed = true;
			up_ग_लिखो(&s->lock);
		पूर्ण
		जाओ shut;
	पूर्ण

	/* Adjust old_chunk and new_chunk to reflect start of linear region */
	old_chunk = old_chunk + 1 - linear_chunks;
	new_chunk = new_chunk + 1 - linear_chunks;

	/*
	 * Use one (potentially large) I/O to copy all 'linear_chunks'
	 * from the exception store to the origin
	 */
	io_size = linear_chunks * s->store->chunk_size;

	dest.bdev = s->origin->bdev;
	dest.sector = chunk_to_sector(s->store, old_chunk);
	dest.count = min(io_size, get_dev_size(dest.bdev) - dest.sector);

	src.bdev = s->cow->bdev;
	src.sector = chunk_to_sector(s->store, new_chunk);
	src.count = dest.count;

	/*
	 * Reallocate any exceptions needed in other snapshots then
	 * रुको क्रम the pending exceptions to complete.
	 * Each समय any pending exception (globally on the प्रणाली)
	 * completes we are woken and repeat the process to find out
	 * अगर we can proceed.  While this may not seem a particularly
	 * efficient algorithm, it is not expected to have any
	 * signअगरicant impact on perक्रमmance.
	 */
	previous_count = पढ़ो_pending_exceptions_करोne_count();
	जबतक (origin_ग_लिखो_extent(s, dest.sector, io_size)) अणु
		रुको_event(_pending_exceptions_करोne,
			   (पढ़ो_pending_exceptions_करोne_count() !=
			    previous_count));
		/* Retry after the रुको, until all exceptions are करोne. */
		previous_count = पढ़ो_pending_exceptions_करोne_count();
	पूर्ण

	करोwn_ग_लिखो(&s->lock);
	s->first_merging_chunk = old_chunk;
	s->num_merging_chunks = linear_chunks;
	up_ग_लिखो(&s->lock);

	/* Wait until ग_लिखोs to all 'linear_chunks' drain */
	क्रम (i = 0; i < linear_chunks; i++)
		__check_क्रम_conflicting_io(s, old_chunk + i);

	dm_kcopyd_copy(s->kcopyd_client, &src, 1, &dest, 0, merge_callback, s);
	वापस;

shut:
	merge_shutकरोwn(s);
पूर्ण

अटल व्योम error_bios(काष्ठा bio *bio);

अटल पूर्णांक flush_data(काष्ठा dm_snapshot *s)
अणु
	काष्ठा bio *flush_bio = &s->flush_bio;

	bio_reset(flush_bio);
	bio_set_dev(flush_bio, s->origin->bdev);
	flush_bio->bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;

	वापस submit_bio_रुको(flush_bio);
पूर्ण

अटल व्योम merge_callback(पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err, व्योम *context)
अणु
	काष्ठा dm_snapshot *s = context;
	काष्ठा bio *b = शून्य;

	अगर (पढ़ो_err || ग_लिखो_err) अणु
		अगर (पढ़ो_err)
			DMERR("Read error: shutting down merge.");
		अन्यथा
			DMERR("Write error: shutting down merge.");
		जाओ shut;
	पूर्ण

	अगर (flush_data(s) < 0) अणु
		DMERR("Flush after merge failed: shutting down merge");
		जाओ shut;
	पूर्ण

	अगर (s->store->type->commit_merge(s->store,
					 s->num_merging_chunks) < 0) अणु
		DMERR("Write error in exception store: shutting down merge");
		जाओ shut;
	पूर्ण

	अगर (हटाओ_single_exception_chunk(s) < 0)
		जाओ shut;

	snapshot_merge_next_chunks(s);

	वापस;

shut:
	करोwn_ग_लिखो(&s->lock);
	s->merge_failed = true;
	b = __release_queued_bios_after_merge(s);
	up_ग_लिखो(&s->lock);
	error_bios(b);

	merge_shutकरोwn(s);
पूर्ण

अटल व्योम start_merge(काष्ठा dm_snapshot *s)
अणु
	अगर (!test_and_set_bit(RUNNING_MERGE, &s->state_bits))
		snapshot_merge_next_chunks(s);
पूर्ण

/*
 * Stop the merging process and रुको until it finishes.
 */
अटल व्योम stop_merge(काष्ठा dm_snapshot *s)
अणु
	set_bit(SHUTDOWN_MERGE, &s->state_bits);
	रुको_on_bit(&s->state_bits, RUNNING_MERGE, TASK_UNINTERRUPTIBLE);
	clear_bit(SHUTDOWN_MERGE, &s->state_bits);
पूर्ण

अटल पूर्णांक parse_snapshot_features(काष्ठा dm_arg_set *as, काष्ठा dm_snapshot *s,
				   काष्ठा dm_target *ti)
अणु
	पूर्णांक r;
	अचिन्हित argc;
	स्थिर अक्षर *arg_name;

	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, 2, "Invalid number of feature arguments"पूर्ण,
	पूर्ण;

	/*
	 * No feature arguments supplied.
	 */
	अगर (!as->argc)
		वापस 0;

	r = dm_पढ़ो_arg_group(_args, as, &argc, &ti->error);
	अगर (r)
		वापस -EINVAL;

	जबतक (argc && !r) अणु
		arg_name = dm_shअगरt_arg(as);
		argc--;

		अगर (!strहालcmp(arg_name, "discard_zeroes_cow"))
			s->discard_zeroes_cow = true;

		अन्यथा अगर (!strहालcmp(arg_name, "discard_passdown_origin"))
			s->discard_passकरोwn_origin = true;

		अन्यथा अणु
			ti->error = "Unrecognised feature requested";
			r = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!s->discard_zeroes_cow && s->discard_passकरोwn_origin) अणु
		/*
		 * TODO: really these are disjoपूर्णांक.. but ti->num_discard_bios
		 * and dm_bio_get_target_bio_nr() require rigid स्थिरraपूर्णांकs.
		 */
		ti->error = "discard_passdown_origin feature depends on discard_zeroes_cow";
		r = -EINVAL;
	पूर्ण

	वापस r;
पूर्ण

/*
 * Conकाष्ठा a snapshot mapping:
 * <origin_dev> <COW-dev> <p|po|n> <chunk-size> [<# feature args> [<arg>]*]
 */
अटल पूर्णांक snapshot_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा dm_snapshot *s;
	काष्ठा dm_arg_set as;
	पूर्णांक i;
	पूर्णांक r = -EINVAL;
	अक्षर *origin_path, *cow_path;
	dev_t origin_dev, cow_dev;
	अचिन्हित args_used, num_flush_bios = 1;
	भ_शेषe_t origin_mode = FMODE_READ;

	अगर (argc < 4) अणु
		ti->error = "requires 4 or more arguments";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	अगर (dm_target_is_snapshot_merge(ti)) अणु
		num_flush_bios = 2;
		origin_mode = FMODE_WRITE;
	पूर्ण

	s = kzalloc(माप(*s), GFP_KERNEL);
	अगर (!s) अणु
		ti->error = "Cannot allocate private snapshot structure";
		r = -ENOMEM;
		जाओ bad;
	पूर्ण

	as.argc = argc;
	as.argv = argv;
	dm_consume_args(&as, 4);
	r = parse_snapshot_features(&as, s, ti);
	अगर (r)
		जाओ bad_features;

	origin_path = argv[0];
	argv++;
	argc--;

	r = dm_get_device(ti, origin_path, origin_mode, &s->origin);
	अगर (r) अणु
		ti->error = "Cannot get origin device";
		जाओ bad_origin;
	पूर्ण
	origin_dev = s->origin->bdev->bd_dev;

	cow_path = argv[0];
	argv++;
	argc--;

	cow_dev = dm_get_dev_t(cow_path);
	अगर (cow_dev && cow_dev == origin_dev) अणु
		ti->error = "COW device cannot be the same as origin device";
		r = -EINVAL;
		जाओ bad_cow;
	पूर्ण

	r = dm_get_device(ti, cow_path, dm_table_get_mode(ti->table), &s->cow);
	अगर (r) अणु
		ti->error = "Cannot get COW device";
		जाओ bad_cow;
	पूर्ण

	r = dm_exception_store_create(ti, argc, argv, s, &args_used, &s->store);
	अगर (r) अणु
		ti->error = "Couldn't create exception store";
		r = -EINVAL;
		जाओ bad_store;
	पूर्ण

	argv += args_used;
	argc -= args_used;

	s->ti = ti;
	s->valid = 1;
	s->snapshot_overflowed = 0;
	s->active = 0;
	atomic_set(&s->pending_exceptions_count, 0);
	spin_lock_init(&s->pe_allocation_lock);
	s->exception_start_sequence = 0;
	s->exception_complete_sequence = 0;
	s->out_of_order_tree = RB_ROOT;
	init_rwsem(&s->lock);
	INIT_LIST_HEAD(&s->list);
	spin_lock_init(&s->pe_lock);
	s->state_bits = 0;
	s->merge_failed = false;
	s->first_merging_chunk = 0;
	s->num_merging_chunks = 0;
	bio_list_init(&s->bios_queued_during_merge);
	bio_init(&s->flush_bio, शून्य, 0);

	/* Allocate hash table क्रम COW data */
	अगर (init_hash_tables(s)) अणु
		ti->error = "Unable to allocate hash table space";
		r = -ENOMEM;
		जाओ bad_hash_tables;
	पूर्ण

	init_रुकोqueue_head(&s->in_progress_रुको);

	s->kcopyd_client = dm_kcopyd_client_create(&dm_kcopyd_throttle);
	अगर (IS_ERR(s->kcopyd_client)) अणु
		r = PTR_ERR(s->kcopyd_client);
		ti->error = "Could not create kcopyd client";
		जाओ bad_kcopyd;
	पूर्ण

	r = mempool_init_slab_pool(&s->pending_pool, MIN_IOS, pending_cache);
	अगर (r) अणु
		ti->error = "Could not allocate mempool for pending exceptions";
		जाओ bad_pending_pool;
	पूर्ण

	क्रम (i = 0; i < DM_TRACKED_CHUNK_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&s->tracked_chunk_hash[i]);

	spin_lock_init(&s->tracked_chunk_lock);

	ti->निजी = s;
	ti->num_flush_bios = num_flush_bios;
	अगर (s->discard_zeroes_cow)
		ti->num_discard_bios = (s->discard_passकरोwn_origin ? 2 : 1);
	ti->per_io_data_size = माप(काष्ठा dm_snap_tracked_chunk);

	/* Add snapshot to the list of snapshots क्रम this origin */
	/* Exceptions aren't triggered till snapshot_resume() is called */
	r = रेजिस्टर_snapshot(s);
	अगर (r == -ENOMEM) अणु
		ti->error = "Snapshot origin struct allocation failed";
		जाओ bad_load_and_रेजिस्टर;
	पूर्ण अन्यथा अगर (r < 0) अणु
		/* invalid hanकरोver, रेजिस्टर_snapshot has set ti->error */
		जाओ bad_load_and_रेजिस्टर;
	पूर्ण

	/*
	 * Metadata must only be loaded पूर्णांकo one table at once, so skip this
	 * अगर metadata will be handed over during resume.
	 * Chunk size will be set during the hanकरोver - set it to zero to
	 * ensure it's ignored.
	 */
	अगर (r > 0) अणु
		s->store->chunk_size = 0;
		वापस 0;
	पूर्ण

	r = s->store->type->पढ़ो_metadata(s->store, dm_add_exception,
					  (व्योम *)s);
	अगर (r < 0) अणु
		ti->error = "Failed to read snapshot metadata";
		जाओ bad_पढ़ो_metadata;
	पूर्ण अन्यथा अगर (r > 0) अणु
		s->valid = 0;
		DMWARN("Snapshot is marked invalid.");
	पूर्ण

	अगर (!s->store->chunk_size) अणु
		ti->error = "Chunk size not set";
		r = -EINVAL;
		जाओ bad_पढ़ो_metadata;
	पूर्ण

	r = dm_set_target_max_io_len(ti, s->store->chunk_size);
	अगर (r)
		जाओ bad_पढ़ो_metadata;

	वापस 0;

bad_पढ़ो_metadata:
	unरेजिस्टर_snapshot(s);
bad_load_and_रेजिस्टर:
	mempool_निकास(&s->pending_pool);
bad_pending_pool:
	dm_kcopyd_client_destroy(s->kcopyd_client);
bad_kcopyd:
	dm_exception_table_निकास(&s->pending, pending_cache);
	dm_exception_table_निकास(&s->complete, exception_cache);
bad_hash_tables:
	dm_exception_store_destroy(s->store);
bad_store:
	dm_put_device(ti, s->cow);
bad_cow:
	dm_put_device(ti, s->origin);
bad_origin:
bad_features:
	kमुक्त(s);
bad:
	वापस r;
पूर्ण

अटल व्योम __मुक्त_exceptions(काष्ठा dm_snapshot *s)
अणु
	dm_kcopyd_client_destroy(s->kcopyd_client);
	s->kcopyd_client = शून्य;

	dm_exception_table_निकास(&s->pending, pending_cache);
	dm_exception_table_निकास(&s->complete, exception_cache);
पूर्ण

अटल व्योम __hanकरोver_exceptions(काष्ठा dm_snapshot *snap_src,
				  काष्ठा dm_snapshot *snap_dest)
अणु
	जोड़ अणु
		काष्ठा dm_exception_table table_swap;
		काष्ठा dm_exception_store *store_swap;
	पूर्ण u;

	/*
	 * Swap all snapshot context inक्रमmation between the two instances.
	 */
	u.table_swap = snap_dest->complete;
	snap_dest->complete = snap_src->complete;
	snap_src->complete = u.table_swap;

	u.store_swap = snap_dest->store;
	snap_dest->store = snap_src->store;
	snap_dest->store->userspace_supports_overflow = u.store_swap->userspace_supports_overflow;
	snap_src->store = u.store_swap;

	snap_dest->store->snap = snap_dest;
	snap_src->store->snap = snap_src;

	snap_dest->ti->max_io_len = snap_dest->store->chunk_size;
	snap_dest->valid = snap_src->valid;
	snap_dest->snapshot_overflowed = snap_src->snapshot_overflowed;

	/*
	 * Set source invalid to ensure it receives no further I/O.
	 */
	snap_src->valid = 0;
पूर्ण

अटल व्योम snapshot_dtr(काष्ठा dm_target *ti)
अणु
#अगर_घोषित CONFIG_DM_DEBUG
	पूर्णांक i;
#पूर्ण_अगर
	काष्ठा dm_snapshot *s = ti->निजी;
	काष्ठा dm_snapshot *snap_src = शून्य, *snap_dest = शून्य;

	करोwn_पढ़ो(&_origins_lock);
	/* Check whether exception hanकरोver must be cancelled */
	(व्योम) __find_snapshots_sharing_cow(s, &snap_src, &snap_dest, शून्य);
	अगर (snap_src && snap_dest && (s == snap_src)) अणु
		करोwn_ग_लिखो(&snap_dest->lock);
		snap_dest->valid = 0;
		up_ग_लिखो(&snap_dest->lock);
		DMERR("Cancelling snapshot handover.");
	पूर्ण
	up_पढ़ो(&_origins_lock);

	अगर (dm_target_is_snapshot_merge(ti))
		stop_merge(s);

	/* Prevent further origin ग_लिखोs from using this snapshot. */
	/* After this वापसs there can be no new kcopyd jobs. */
	unरेजिस्टर_snapshot(s);

	जबतक (atomic_पढ़ो(&s->pending_exceptions_count))
		msleep(1);
	/*
	 * Ensure inकाष्ठाions in mempool_निकास aren't reordered
	 * beक्रमe atomic_पढ़ो.
	 */
	smp_mb();

#अगर_घोषित CONFIG_DM_DEBUG
	क्रम (i = 0; i < DM_TRACKED_CHUNK_HASH_SIZE; i++)
		BUG_ON(!hlist_empty(&s->tracked_chunk_hash[i]));
#पूर्ण_अगर

	__मुक्त_exceptions(s);

	mempool_निकास(&s->pending_pool);

	dm_exception_store_destroy(s->store);

	bio_uninit(&s->flush_bio);

	dm_put_device(ti, s->cow);

	dm_put_device(ti, s->origin);

	WARN_ON(s->in_progress);

	kमुक्त(s);
पूर्ण

अटल व्योम account_start_copy(काष्ठा dm_snapshot *s)
अणु
	spin_lock(&s->in_progress_रुको.lock);
	s->in_progress++;
	spin_unlock(&s->in_progress_रुको.lock);
पूर्ण

अटल व्योम account_end_copy(काष्ठा dm_snapshot *s)
अणु
	spin_lock(&s->in_progress_रुको.lock);
	BUG_ON(!s->in_progress);
	s->in_progress--;
	अगर (likely(s->in_progress <= cow_threshold) &&
	    unlikely(रुकोqueue_active(&s->in_progress_रुको)))
		wake_up_locked(&s->in_progress_रुको);
	spin_unlock(&s->in_progress_रुको.lock);
पूर्ण

अटल bool रुको_क्रम_in_progress(काष्ठा dm_snapshot *s, bool unlock_origins)
अणु
	अगर (unlikely(s->in_progress > cow_threshold)) अणु
		spin_lock(&s->in_progress_रुको.lock);
		अगर (likely(s->in_progress > cow_threshold)) अणु
			/*
			 * NOTE: this throttle करोesn't account क्रम whether
			 * the caller is servicing an IO that will trigger a COW
			 * so excess throttling may result क्रम chunks not required
			 * to be COW'd.  But अगर cow_threshold was reached, extra
			 * throttling is unlikely to negatively impact perक्रमmance.
			 */
			DECLARE_WAITQUEUE(रुको, current);
			__add_रुको_queue(&s->in_progress_रुको, &रुको);
			__set_current_state(TASK_UNINTERRUPTIBLE);
			spin_unlock(&s->in_progress_रुको.lock);
			अगर (unlock_origins)
				up_पढ़ो(&_origins_lock);
			io_schedule();
			हटाओ_रुको_queue(&s->in_progress_रुको, &रुको);
			वापस false;
		पूर्ण
		spin_unlock(&s->in_progress_रुको.lock);
	पूर्ण
	वापस true;
पूर्ण

/*
 * Flush a list of buffers.
 */
अटल व्योम flush_bios(काष्ठा bio *bio)
अणु
	काष्ठा bio *n;

	जबतक (bio) अणु
		n = bio->bi_next;
		bio->bi_next = शून्य;
		submit_bio_noacct(bio);
		bio = n;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_origin(काष्ठा dm_dev *origin, काष्ठा bio *bio, bool limit);

/*
 * Flush a list of buffers.
 */
अटल व्योम retry_origin_bios(काष्ठा dm_snapshot *s, काष्ठा bio *bio)
अणु
	काष्ठा bio *n;
	पूर्णांक r;

	जबतक (bio) अणु
		n = bio->bi_next;
		bio->bi_next = शून्य;
		r = करो_origin(s->origin, bio, false);
		अगर (r == DM_MAPIO_REMAPPED)
			submit_bio_noacct(bio);
		bio = n;
	पूर्ण
पूर्ण

/*
 * Error a list of buffers.
 */
अटल व्योम error_bios(काष्ठा bio *bio)
अणु
	काष्ठा bio *n;

	जबतक (bio) अणु
		n = bio->bi_next;
		bio->bi_next = शून्य;
		bio_io_error(bio);
		bio = n;
	पूर्ण
पूर्ण

अटल व्योम __invalidate_snapshot(काष्ठा dm_snapshot *s, पूर्णांक err)
अणु
	अगर (!s->valid)
		वापस;

	अगर (err == -EIO)
		DMERR("Invalidating snapshot: Error reading/writing.");
	अन्यथा अगर (err == -ENOMEM)
		DMERR("Invalidating snapshot: Unable to allocate exception.");

	अगर (s->store->type->drop_snapshot)
		s->store->type->drop_snapshot(s->store);

	s->valid = 0;

	dm_table_event(s->ti->table);
पूर्ण

अटल व्योम invalidate_snapshot(काष्ठा dm_snapshot *s, पूर्णांक err)
अणु
	करोwn_ग_लिखो(&s->lock);
	__invalidate_snapshot(s, err);
	up_ग_लिखो(&s->lock);
पूर्ण

अटल व्योम pending_complete(व्योम *context, पूर्णांक success)
अणु
	काष्ठा dm_snap_pending_exception *pe = context;
	काष्ठा dm_exception *e;
	काष्ठा dm_snapshot *s = pe->snap;
	काष्ठा bio *origin_bios = शून्य;
	काष्ठा bio *snapshot_bios = शून्य;
	काष्ठा bio *full_bio = शून्य;
	काष्ठा dm_exception_table_lock lock;
	पूर्णांक error = 0;

	dm_exception_table_lock_init(s, pe->e.old_chunk, &lock);

	अगर (!success) अणु
		/* Read/ग_लिखो error - snapshot is unusable */
		invalidate_snapshot(s, -EIO);
		error = 1;

		dm_exception_table_lock(&lock);
		जाओ out;
	पूर्ण

	e = alloc_completed_exception(GFP_NOIO);
	अगर (!e) अणु
		invalidate_snapshot(s, -ENOMEM);
		error = 1;

		dm_exception_table_lock(&lock);
		जाओ out;
	पूर्ण
	*e = pe->e;

	करोwn_पढ़ो(&s->lock);
	dm_exception_table_lock(&lock);
	अगर (!s->valid) अणु
		up_पढ़ो(&s->lock);
		मुक्त_completed_exception(e);
		error = 1;

		जाओ out;
	पूर्ण

	/*
	 * Add a proper exception. After inserting the completed exception all
	 * subsequent snapshot पढ़ोs to this chunk will be redirected to the
	 * COW device.  This ensures that we करो not starve. Moreover, as दीर्घ
	 * as the pending exception exists, neither origin ग_लिखोs nor snapshot
	 * merging can overग_लिखो the chunk in origin.
	 */
	dm_insert_exception(&s->complete, e);
	up_पढ़ो(&s->lock);

	/* Wait क्रम conflicting पढ़ोs to drain */
	अगर (__chunk_is_tracked(s, pe->e.old_chunk)) अणु
		dm_exception_table_unlock(&lock);
		__check_क्रम_conflicting_io(s, pe->e.old_chunk);
		dm_exception_table_lock(&lock);
	पूर्ण

out:
	/* Remove the in-flight exception from the list */
	dm_हटाओ_exception(&pe->e);

	dm_exception_table_unlock(&lock);

	snapshot_bios = bio_list_get(&pe->snapshot_bios);
	origin_bios = bio_list_get(&pe->origin_bios);
	full_bio = pe->full_bio;
	अगर (full_bio)
		full_bio->bi_end_io = pe->full_bio_end_io;
	increment_pending_exceptions_करोne_count();

	/* Submit any pending ग_लिखो bios */
	अगर (error) अणु
		अगर (full_bio)
			bio_io_error(full_bio);
		error_bios(snapshot_bios);
	पूर्ण अन्यथा अणु
		अगर (full_bio)
			bio_endio(full_bio);
		flush_bios(snapshot_bios);
	पूर्ण

	retry_origin_bios(s, origin_bios);

	मुक्त_pending_exception(pe);
पूर्ण

अटल व्योम complete_exception(काष्ठा dm_snap_pending_exception *pe)
अणु
	काष्ठा dm_snapshot *s = pe->snap;

	/* Update the metadata अगर we are persistent */
	s->store->type->commit_exception(s->store, &pe->e, !pe->copy_error,
					 pending_complete, pe);
पूर्ण

/*
 * Called when the copy I/O has finished.  kcopyd actually runs
 * this code so करोn't block.
 */
अटल व्योम copy_callback(पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err, व्योम *context)
अणु
	काष्ठा dm_snap_pending_exception *pe = context;
	काष्ठा dm_snapshot *s = pe->snap;

	pe->copy_error = पढ़ो_err || ग_लिखो_err;

	अगर (pe->exception_sequence == s->exception_complete_sequence) अणु
		काष्ठा rb_node *next;

		s->exception_complete_sequence++;
		complete_exception(pe);

		next = rb_first(&s->out_of_order_tree);
		जबतक (next) अणु
			pe = rb_entry(next, काष्ठा dm_snap_pending_exception,
					out_of_order_node);
			अगर (pe->exception_sequence != s->exception_complete_sequence)
				अवरोध;
			next = rb_next(next);
			s->exception_complete_sequence++;
			rb_erase(&pe->out_of_order_node, &s->out_of_order_tree);
			complete_exception(pe);
			cond_resched();
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा rb_node *parent = शून्य;
		काष्ठा rb_node **p = &s->out_of_order_tree.rb_node;
		काष्ठा dm_snap_pending_exception *pe2;

		जबतक (*p) अणु
			pe2 = rb_entry(*p, काष्ठा dm_snap_pending_exception, out_of_order_node);
			parent = *p;

			BUG_ON(pe->exception_sequence == pe2->exception_sequence);
			अगर (pe->exception_sequence < pe2->exception_sequence)
				p = &((*p)->rb_left);
			अन्यथा
				p = &((*p)->rb_right);
		पूर्ण

		rb_link_node(&pe->out_of_order_node, parent, p);
		rb_insert_color(&pe->out_of_order_node, &s->out_of_order_tree);
	पूर्ण
	account_end_copy(s);
पूर्ण

/*
 * Dispatches the copy operation to kcopyd.
 */
अटल व्योम start_copy(काष्ठा dm_snap_pending_exception *pe)
अणु
	काष्ठा dm_snapshot *s = pe->snap;
	काष्ठा dm_io_region src, dest;
	काष्ठा block_device *bdev = s->origin->bdev;
	sector_t dev_size;

	dev_size = get_dev_size(bdev);

	src.bdev = bdev;
	src.sector = chunk_to_sector(s->store, pe->e.old_chunk);
	src.count = min((sector_t)s->store->chunk_size, dev_size - src.sector);

	dest.bdev = s->cow->bdev;
	dest.sector = chunk_to_sector(s->store, pe->e.new_chunk);
	dest.count = src.count;

	/* Hand over to kcopyd */
	account_start_copy(s);
	dm_kcopyd_copy(s->kcopyd_client, &src, 1, &dest, 0, copy_callback, pe);
पूर्ण

अटल व्योम full_bio_end_io(काष्ठा bio *bio)
अणु
	व्योम *callback_data = bio->bi_निजी;

	dm_kcopyd_करो_callback(callback_data, 0, bio->bi_status ? 1 : 0);
पूर्ण

अटल व्योम start_full_bio(काष्ठा dm_snap_pending_exception *pe,
			   काष्ठा bio *bio)
अणु
	काष्ठा dm_snapshot *s = pe->snap;
	व्योम *callback_data;

	pe->full_bio = bio;
	pe->full_bio_end_io = bio->bi_end_io;

	account_start_copy(s);
	callback_data = dm_kcopyd_prepare_callback(s->kcopyd_client,
						   copy_callback, pe);

	bio->bi_end_io = full_bio_end_io;
	bio->bi_निजी = callback_data;

	submit_bio_noacct(bio);
पूर्ण

अटल काष्ठा dm_snap_pending_exception *
__lookup_pending_exception(काष्ठा dm_snapshot *s, chunk_t chunk)
अणु
	काष्ठा dm_exception *e = dm_lookup_exception(&s->pending, chunk);

	अगर (!e)
		वापस शून्य;

	वापस container_of(e, काष्ठा dm_snap_pending_exception, e);
पूर्ण

/*
 * Inserts a pending exception पूर्णांकo the pending table.
 *
 * NOTE: a ग_लिखो lock must be held on the chunk's pending exception table slot
 * beक्रमe calling this.
 */
अटल काष्ठा dm_snap_pending_exception *
__insert_pending_exception(काष्ठा dm_snapshot *s,
			   काष्ठा dm_snap_pending_exception *pe, chunk_t chunk)
अणु
	pe->e.old_chunk = chunk;
	bio_list_init(&pe->origin_bios);
	bio_list_init(&pe->snapshot_bios);
	pe->started = 0;
	pe->full_bio = शून्य;

	spin_lock(&s->pe_allocation_lock);
	अगर (s->store->type->prepare_exception(s->store, &pe->e)) अणु
		spin_unlock(&s->pe_allocation_lock);
		मुक्त_pending_exception(pe);
		वापस शून्य;
	पूर्ण

	pe->exception_sequence = s->exception_start_sequence++;
	spin_unlock(&s->pe_allocation_lock);

	dm_insert_exception(&s->pending, &pe->e);

	वापस pe;
पूर्ण

/*
 * Looks to see अगर this snapshot alपढ़ोy has a pending exception
 * क्रम this chunk, otherwise it allocates a new one and inserts
 * it पूर्णांकo the pending table.
 *
 * NOTE: a ग_लिखो lock must be held on the chunk's pending exception table slot
 * beक्रमe calling this.
 */
अटल काष्ठा dm_snap_pending_exception *
__find_pending_exception(काष्ठा dm_snapshot *s,
			 काष्ठा dm_snap_pending_exception *pe, chunk_t chunk)
अणु
	काष्ठा dm_snap_pending_exception *pe2;

	pe2 = __lookup_pending_exception(s, chunk);
	अगर (pe2) अणु
		मुक्त_pending_exception(pe);
		वापस pe2;
	पूर्ण

	वापस __insert_pending_exception(s, pe, chunk);
पूर्ण

अटल व्योम remap_exception(काष्ठा dm_snapshot *s, काष्ठा dm_exception *e,
			    काष्ठा bio *bio, chunk_t chunk)
अणु
	bio_set_dev(bio, s->cow->bdev);
	bio->bi_iter.bi_sector =
		chunk_to_sector(s->store, dm_chunk_number(e->new_chunk) +
				(chunk - e->old_chunk)) +
		(bio->bi_iter.bi_sector & s->store->chunk_mask);
पूर्ण

अटल व्योम zero_callback(पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err, व्योम *context)
अणु
	काष्ठा bio *bio = context;
	काष्ठा dm_snapshot *s = bio->bi_निजी;

	account_end_copy(s);
	bio->bi_status = ग_लिखो_err ? BLK_STS_IOERR : 0;
	bio_endio(bio);
पूर्ण

अटल व्योम zero_exception(काष्ठा dm_snapshot *s, काष्ठा dm_exception *e,
			   काष्ठा bio *bio, chunk_t chunk)
अणु
	काष्ठा dm_io_region dest;

	dest.bdev = s->cow->bdev;
	dest.sector = bio->bi_iter.bi_sector;
	dest.count = s->store->chunk_size;

	account_start_copy(s);
	WARN_ON_ONCE(bio->bi_निजी);
	bio->bi_निजी = s;
	dm_kcopyd_zero(s->kcopyd_client, 1, &dest, 0, zero_callback, bio);
पूर्ण

अटल bool io_overlaps_chunk(काष्ठा dm_snapshot *s, काष्ठा bio *bio)
अणु
	वापस bio->bi_iter.bi_size ==
		(s->store->chunk_size << SECTOR_SHIFT);
पूर्ण

अटल पूर्णांक snapshot_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा dm_exception *e;
	काष्ठा dm_snapshot *s = ti->निजी;
	पूर्णांक r = DM_MAPIO_REMAPPED;
	chunk_t chunk;
	काष्ठा dm_snap_pending_exception *pe = शून्य;
	काष्ठा dm_exception_table_lock lock;

	init_tracked_chunk(bio);

	अगर (bio->bi_opf & REQ_PREFLUSH) अणु
		bio_set_dev(bio, s->cow->bdev);
		वापस DM_MAPIO_REMAPPED;
	पूर्ण

	chunk = sector_to_chunk(s->store, bio->bi_iter.bi_sector);
	dm_exception_table_lock_init(s, chunk, &lock);

	/* Full snapshots are not usable */
	/* To get here the table must be live so s->active is always set. */
	अगर (!s->valid)
		वापस DM_MAPIO_KILL;

	अगर (bio_data_dir(bio) == WRITE) अणु
		जबतक (unlikely(!रुको_क्रम_in_progress(s, false)))
			; /* रुको_क्रम_in_progress() has slept */
	पूर्ण

	करोwn_पढ़ो(&s->lock);
	dm_exception_table_lock(&lock);

	अगर (!s->valid || (unlikely(s->snapshot_overflowed) &&
	    bio_data_dir(bio) == WRITE)) अणु
		r = DM_MAPIO_KILL;
		जाओ out_unlock;
	पूर्ण

	अगर (unlikely(bio_op(bio) == REQ_OP_DISCARD)) अणु
		अगर (s->discard_passकरोwn_origin && dm_bio_get_target_bio_nr(bio)) अणु
			/*
			 * passकरोwn discard to origin (without triggering
			 * snapshot exceptions via करो_origin; करोing so would
			 * defeat the goal of मुक्तing space in origin that is
			 * implied by the "discard_passdown_origin" feature)
			 */
			bio_set_dev(bio, s->origin->bdev);
			track_chunk(s, bio, chunk);
			जाओ out_unlock;
		पूर्ण
		/* discard to snapshot (target_bio_nr == 0) zeroes exceptions */
	पूर्ण

	/* If the block is alपढ़ोy remapped - use that, अन्यथा remap it */
	e = dm_lookup_exception(&s->complete, chunk);
	अगर (e) अणु
		remap_exception(s, e, bio, chunk);
		अगर (unlikely(bio_op(bio) == REQ_OP_DISCARD) &&
		    io_overlaps_chunk(s, bio)) अणु
			dm_exception_table_unlock(&lock);
			up_पढ़ो(&s->lock);
			zero_exception(s, e, bio, chunk);
			r = DM_MAPIO_SUBMITTED; /* discard is not issued */
			जाओ out;
		पूर्ण
		जाओ out_unlock;
	पूर्ण

	अगर (unlikely(bio_op(bio) == REQ_OP_DISCARD)) अणु
		/*
		 * If no exception exists, complete discard immediately
		 * otherwise it'll trigger copy-out.
		 */
		bio_endio(bio);
		r = DM_MAPIO_SUBMITTED;
		जाओ out_unlock;
	पूर्ण

	/*
	 * Write to snapshot - higher level takes care of RW/RO
	 * flags so we should only get this अगर we are
	 * ग_लिखोable.
	 */
	अगर (bio_data_dir(bio) == WRITE) अणु
		pe = __lookup_pending_exception(s, chunk);
		अगर (!pe) अणु
			dm_exception_table_unlock(&lock);
			pe = alloc_pending_exception(s);
			dm_exception_table_lock(&lock);

			e = dm_lookup_exception(&s->complete, chunk);
			अगर (e) अणु
				मुक्त_pending_exception(pe);
				remap_exception(s, e, bio, chunk);
				जाओ out_unlock;
			पूर्ण

			pe = __find_pending_exception(s, pe, chunk);
			अगर (!pe) अणु
				dm_exception_table_unlock(&lock);
				up_पढ़ो(&s->lock);

				करोwn_ग_लिखो(&s->lock);

				अगर (s->store->userspace_supports_overflow) अणु
					अगर (s->valid && !s->snapshot_overflowed) अणु
						s->snapshot_overflowed = 1;
						DMERR("Snapshot overflowed: Unable to allocate exception.");
					पूर्ण
				पूर्ण अन्यथा
					__invalidate_snapshot(s, -ENOMEM);
				up_ग_लिखो(&s->lock);

				r = DM_MAPIO_KILL;
				जाओ out;
			पूर्ण
		पूर्ण

		remap_exception(s, &pe->e, bio, chunk);

		r = DM_MAPIO_SUBMITTED;

		अगर (!pe->started && io_overlaps_chunk(s, bio)) अणु
			pe->started = 1;

			dm_exception_table_unlock(&lock);
			up_पढ़ो(&s->lock);

			start_full_bio(pe, bio);
			जाओ out;
		पूर्ण

		bio_list_add(&pe->snapshot_bios, bio);

		अगर (!pe->started) अणु
			/* this is रक्षित by the exception table lock */
			pe->started = 1;

			dm_exception_table_unlock(&lock);
			up_पढ़ो(&s->lock);

			start_copy(pe);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		bio_set_dev(bio, s->origin->bdev);
		track_chunk(s, bio, chunk);
	पूर्ण

out_unlock:
	dm_exception_table_unlock(&lock);
	up_पढ़ो(&s->lock);
out:
	वापस r;
पूर्ण

/*
 * A snapshot-merge target behaves like a combination of a snapshot
 * target and a snapshot-origin target.  It only generates new
 * exceptions in other snapshots and not in the one that is being
 * merged.
 *
 * For each chunk, अगर there is an existing exception, it is used to
 * redirect I/O to the cow device.  Otherwise I/O is sent to the origin,
 * which in turn might generate exceptions in other snapshots.
 * If merging is currently taking place on the chunk in question, the
 * I/O is deferred by adding it to s->bios_queued_during_merge.
 */
अटल पूर्णांक snapshot_merge_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा dm_exception *e;
	काष्ठा dm_snapshot *s = ti->निजी;
	पूर्णांक r = DM_MAPIO_REMAPPED;
	chunk_t chunk;

	init_tracked_chunk(bio);

	अगर (bio->bi_opf & REQ_PREFLUSH) अणु
		अगर (!dm_bio_get_target_bio_nr(bio))
			bio_set_dev(bio, s->origin->bdev);
		अन्यथा
			bio_set_dev(bio, s->cow->bdev);
		वापस DM_MAPIO_REMAPPED;
	पूर्ण

	अगर (unlikely(bio_op(bio) == REQ_OP_DISCARD)) अणु
		/* Once merging, discards no दीर्घer effect change */
		bio_endio(bio);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	chunk = sector_to_chunk(s->store, bio->bi_iter.bi_sector);

	करोwn_ग_लिखो(&s->lock);

	/* Full merging snapshots are redirected to the origin */
	अगर (!s->valid)
		जाओ redirect_to_origin;

	/* If the block is alपढ़ोy remapped - use that */
	e = dm_lookup_exception(&s->complete, chunk);
	अगर (e) अणु
		/* Queue ग_लिखोs overlapping with chunks being merged */
		अगर (bio_data_dir(bio) == WRITE &&
		    chunk >= s->first_merging_chunk &&
		    chunk < (s->first_merging_chunk +
			     s->num_merging_chunks)) अणु
			bio_set_dev(bio, s->origin->bdev);
			bio_list_add(&s->bios_queued_during_merge, bio);
			r = DM_MAPIO_SUBMITTED;
			जाओ out_unlock;
		पूर्ण

		remap_exception(s, e, bio, chunk);

		अगर (bio_data_dir(bio) == WRITE)
			track_chunk(s, bio, chunk);
		जाओ out_unlock;
	पूर्ण

redirect_to_origin:
	bio_set_dev(bio, s->origin->bdev);

	अगर (bio_data_dir(bio) == WRITE) अणु
		up_ग_लिखो(&s->lock);
		वापस करो_origin(s->origin, bio, false);
	पूर्ण

out_unlock:
	up_ग_लिखो(&s->lock);

	वापस r;
पूर्ण

अटल पूर्णांक snapshot_end_io(काष्ठा dm_target *ti, काष्ठा bio *bio,
		blk_status_t *error)
अणु
	काष्ठा dm_snapshot *s = ti->निजी;

	अगर (is_bio_tracked(bio))
		stop_tracking_chunk(s, bio);

	वापस DM_ENDIO_DONE;
पूर्ण

अटल व्योम snapshot_merge_presuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_snapshot *s = ti->निजी;

	stop_merge(s);
पूर्ण

अटल पूर्णांक snapshot_preresume(काष्ठा dm_target *ti)
अणु
	पूर्णांक r = 0;
	काष्ठा dm_snapshot *s = ti->निजी;
	काष्ठा dm_snapshot *snap_src = शून्य, *snap_dest = शून्य;

	करोwn_पढ़ो(&_origins_lock);
	(व्योम) __find_snapshots_sharing_cow(s, &snap_src, &snap_dest, शून्य);
	अगर (snap_src && snap_dest) अणु
		करोwn_पढ़ो(&snap_src->lock);
		अगर (s == snap_src) अणु
			DMERR("Unable to resume snapshot source until "
			      "handover completes.");
			r = -EINVAL;
		पूर्ण अन्यथा अगर (!dm_suspended(snap_src->ti)) अणु
			DMERR("Unable to perform snapshot handover until "
			      "source is suspended.");
			r = -EINVAL;
		पूर्ण
		up_पढ़ो(&snap_src->lock);
	पूर्ण
	up_पढ़ो(&_origins_lock);

	वापस r;
पूर्ण

अटल व्योम snapshot_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_snapshot *s = ti->निजी;
	काष्ठा dm_snapshot *snap_src = शून्य, *snap_dest = शून्य, *snap_merging = शून्य;
	काष्ठा dm_origin *o;
	काष्ठा mapped_device *origin_md = शून्य;
	bool must_restart_merging = false;

	करोwn_पढ़ो(&_origins_lock);

	o = __lookup_dm_origin(s->origin->bdev);
	अगर (o)
		origin_md = dm_table_get_md(o->ti->table);
	अगर (!origin_md) अणु
		(व्योम) __find_snapshots_sharing_cow(s, शून्य, शून्य, &snap_merging);
		अगर (snap_merging)
			origin_md = dm_table_get_md(snap_merging->ti->table);
	पूर्ण
	अगर (origin_md == dm_table_get_md(ti->table))
		origin_md = शून्य;
	अगर (origin_md) अणु
		अगर (dm_hold(origin_md))
			origin_md = शून्य;
	पूर्ण

	up_पढ़ो(&_origins_lock);

	अगर (origin_md) अणु
		dm_पूर्णांकernal_suspend_fast(origin_md);
		अगर (snap_merging && test_bit(RUNNING_MERGE, &snap_merging->state_bits)) अणु
			must_restart_merging = true;
			stop_merge(snap_merging);
		पूर्ण
	पूर्ण

	करोwn_पढ़ो(&_origins_lock);

	(व्योम) __find_snapshots_sharing_cow(s, &snap_src, &snap_dest, शून्य);
	अगर (snap_src && snap_dest) अणु
		करोwn_ग_लिखो(&snap_src->lock);
		करोwn_ग_लिखो_nested(&snap_dest->lock, SINGLE_DEPTH_NESTING);
		__hanकरोver_exceptions(snap_src, snap_dest);
		up_ग_लिखो(&snap_dest->lock);
		up_ग_लिखो(&snap_src->lock);
	पूर्ण

	up_पढ़ो(&_origins_lock);

	अगर (origin_md) अणु
		अगर (must_restart_merging)
			start_merge(snap_merging);
		dm_पूर्णांकernal_resume_fast(origin_md);
		dm_put(origin_md);
	पूर्ण

	/* Now we have correct chunk size, reरेजिस्टर */
	reरेजिस्टर_snapshot(s);

	करोwn_ग_लिखो(&s->lock);
	s->active = 1;
	up_ग_लिखो(&s->lock);
पूर्ण

अटल uपूर्णांक32_t get_origin_minimum_chunksize(काष्ठा block_device *bdev)
अणु
	uपूर्णांक32_t min_chunksize;

	करोwn_पढ़ो(&_origins_lock);
	min_chunksize = __minimum_chunk_size(__lookup_origin(bdev));
	up_पढ़ो(&_origins_lock);

	वापस min_chunksize;
पूर्ण

अटल व्योम snapshot_merge_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_snapshot *s = ti->निजी;

	/*
	 * Hanकरोver exceptions from existing snapshot.
	 */
	snapshot_resume(ti);

	/*
	 * snapshot-merge acts as an origin, so set ti->max_io_len
	 */
	ti->max_io_len = get_origin_minimum_chunksize(s->origin->bdev);

	start_merge(s);
पूर्ण

अटल व्योम snapshot_status(काष्ठा dm_target *ti, status_type_t type,
			    अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	अचिन्हित sz = 0;
	काष्ठा dm_snapshot *snap = ti->निजी;
	अचिन्हित num_features;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:

		करोwn_ग_लिखो(&snap->lock);

		अगर (!snap->valid)
			DMEMIT("Invalid");
		अन्यथा अगर (snap->merge_failed)
			DMEMIT("Merge failed");
		अन्यथा अगर (snap->snapshot_overflowed)
			DMEMIT("Overflow");
		अन्यथा अणु
			अगर (snap->store->type->usage) अणु
				sector_t total_sectors, sectors_allocated,
					 metadata_sectors;
				snap->store->type->usage(snap->store,
							 &total_sectors,
							 &sectors_allocated,
							 &metadata_sectors);
				DMEMIT("%llu/%llu %llu",
				       (अचिन्हित दीर्घ दीर्घ)sectors_allocated,
				       (अचिन्हित दीर्घ दीर्घ)total_sectors,
				       (अचिन्हित दीर्घ दीर्घ)metadata_sectors);
			पूर्ण
			अन्यथा
				DMEMIT("Unknown");
		पूर्ण

		up_ग_लिखो(&snap->lock);

		अवरोध;

	हाल STATUSTYPE_TABLE:
		/*
		 * kdevname वापसs a अटल poपूर्णांकer so we need
		 * to make निजी copies अगर the output is to
		 * make sense.
		 */
		DMEMIT("%s %s", snap->origin->name, snap->cow->name);
		sz += snap->store->type->status(snap->store, type, result + sz,
						maxlen - sz);
		num_features = snap->discard_zeroes_cow + snap->discard_passकरोwn_origin;
		अगर (num_features) अणु
			DMEMIT(" %u", num_features);
			अगर (snap->discard_zeroes_cow)
				DMEMIT(" discard_zeroes_cow");
			अगर (snap->discard_passकरोwn_origin)
				DMEMIT(" discard_passdown_origin");
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक snapshot_iterate_devices(काष्ठा dm_target *ti,
				    iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा dm_snapshot *snap = ti->निजी;
	पूर्णांक r;

	r = fn(ti, snap->origin, 0, ti->len, data);

	अगर (!r)
		r = fn(ti, snap->cow, 0, get_dev_size(snap->cow->bdev), data);

	वापस r;
पूर्ण

अटल व्योम snapshot_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा dm_snapshot *snap = ti->निजी;

	अगर (snap->discard_zeroes_cow) अणु
		काष्ठा dm_snapshot *snap_src = शून्य, *snap_dest = शून्य;

		करोwn_पढ़ो(&_origins_lock);

		(व्योम) __find_snapshots_sharing_cow(snap, &snap_src, &snap_dest, शून्य);
		अगर (snap_src && snap_dest)
			snap = snap_src;

		/* All discards are split on chunk_size boundary */
		limits->discard_granularity = snap->store->chunk_size;
		limits->max_discard_sectors = snap->store->chunk_size;

		up_पढ़ो(&_origins_lock);
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------
 * Origin methods
 *---------------------------------------------------------------*/

/*
 * If no exceptions need creating, DM_MAPIO_REMAPPED is वापसed and any
 * supplied bio was ignored.  The caller may submit it immediately.
 * (No remapping actually occurs as the origin is always a direct linear
 * map.)
 *
 * If further exceptions are required, DM_MAPIO_SUBMITTED is वापसed
 * and any supplied bio is added to a list to be submitted once all
 * the necessary exceptions exist.
 */
अटल पूर्णांक __origin_ग_लिखो(काष्ठा list_head *snapshots, sector_t sector,
			  काष्ठा bio *bio)
अणु
	पूर्णांक r = DM_MAPIO_REMAPPED;
	काष्ठा dm_snapshot *snap;
	काष्ठा dm_exception *e;
	काष्ठा dm_snap_pending_exception *pe, *pe2;
	काष्ठा dm_snap_pending_exception *pe_to_start_now = शून्य;
	काष्ठा dm_snap_pending_exception *pe_to_start_last = शून्य;
	काष्ठा dm_exception_table_lock lock;
	chunk_t chunk;

	/* Do all the snapshots on this origin */
	list_क्रम_each_entry (snap, snapshots, list) अणु
		/*
		 * Don't make new exceptions in a merging snapshot
		 * because it has effectively been deleted
		 */
		अगर (dm_target_is_snapshot_merge(snap->ti))
			जारी;

		/* Nothing to करो अगर writing beyond end of snapshot */
		अगर (sector >= dm_table_get_size(snap->ti->table))
			जारी;

		/*
		 * Remember, dअगरferent snapshots can have
		 * dअगरferent chunk sizes.
		 */
		chunk = sector_to_chunk(snap->store, sector);
		dm_exception_table_lock_init(snap, chunk, &lock);

		करोwn_पढ़ो(&snap->lock);
		dm_exception_table_lock(&lock);

		/* Only deal with valid and active snapshots */
		अगर (!snap->valid || !snap->active)
			जाओ next_snapshot;

		pe = __lookup_pending_exception(snap, chunk);
		अगर (!pe) अणु
			/*
			 * Check exception table to see अगर block is alपढ़ोy
			 * remapped in this snapshot and trigger an exception
			 * अगर not.
			 */
			e = dm_lookup_exception(&snap->complete, chunk);
			अगर (e)
				जाओ next_snapshot;

			dm_exception_table_unlock(&lock);
			pe = alloc_pending_exception(snap);
			dm_exception_table_lock(&lock);

			pe2 = __lookup_pending_exception(snap, chunk);

			अगर (!pe2) अणु
				e = dm_lookup_exception(&snap->complete, chunk);
				अगर (e) अणु
					मुक्त_pending_exception(pe);
					जाओ next_snapshot;
				पूर्ण

				pe = __insert_pending_exception(snap, pe, chunk);
				अगर (!pe) अणु
					dm_exception_table_unlock(&lock);
					up_पढ़ो(&snap->lock);

					invalidate_snapshot(snap, -ENOMEM);
					जारी;
				पूर्ण
			पूर्ण अन्यथा अणु
				मुक्त_pending_exception(pe);
				pe = pe2;
			पूर्ण
		पूर्ण

		r = DM_MAPIO_SUBMITTED;

		/*
		 * If an origin bio was supplied, queue it to रुको क्रम the
		 * completion of this exception, and start this one last,
		 * at the end of the function.
		 */
		अगर (bio) अणु
			bio_list_add(&pe->origin_bios, bio);
			bio = शून्य;

			अगर (!pe->started) अणु
				pe->started = 1;
				pe_to_start_last = pe;
			पूर्ण
		पूर्ण

		अगर (!pe->started) अणु
			pe->started = 1;
			pe_to_start_now = pe;
		पूर्ण

next_snapshot:
		dm_exception_table_unlock(&lock);
		up_पढ़ो(&snap->lock);

		अगर (pe_to_start_now) अणु
			start_copy(pe_to_start_now);
			pe_to_start_now = शून्य;
		पूर्ण
	पूर्ण

	/*
	 * Submit the exception against which the bio is queued last,
	 * to give the other exceptions a head start.
	 */
	अगर (pe_to_start_last)
		start_copy(pe_to_start_last);

	वापस r;
पूर्ण

/*
 * Called on a ग_लिखो from the origin driver.
 */
अटल पूर्णांक करो_origin(काष्ठा dm_dev *origin, काष्ठा bio *bio, bool limit)
अणु
	काष्ठा origin *o;
	पूर्णांक r = DM_MAPIO_REMAPPED;

again:
	करोwn_पढ़ो(&_origins_lock);
	o = __lookup_origin(origin->bdev);
	अगर (o) अणु
		अगर (limit) अणु
			काष्ठा dm_snapshot *s;
			list_क्रम_each_entry(s, &o->snapshots, list)
				अगर (unlikely(!रुको_क्रम_in_progress(s, true)))
					जाओ again;
		पूर्ण

		r = __origin_ग_लिखो(&o->snapshots, bio->bi_iter.bi_sector, bio);
	पूर्ण
	up_पढ़ो(&_origins_lock);

	वापस r;
पूर्ण

/*
 * Trigger exceptions in all non-merging snapshots.
 *
 * The chunk size of the merging snapshot may be larger than the chunk
 * size of some other snapshot so we may need to पुनः_स्मृतिate multiple
 * chunks in other snapshots.
 *
 * We scan all the overlapping exceptions in the other snapshots.
 * Returns 1 अगर anything was पुनः_स्मृतिated and must be रुकोed क्रम,
 * otherwise वापसs 0.
 *
 * size must be a multiple of merging_snap's chunk_size.
 */
अटल पूर्णांक origin_ग_लिखो_extent(काष्ठा dm_snapshot *merging_snap,
			       sector_t sector, अचिन्हित size)
अणु
	पूर्णांक must_रुको = 0;
	sector_t n;
	काष्ठा origin *o;

	/*
	 * The origin's __minimum_chunk_size() got stored in max_io_len
	 * by snapshot_merge_resume().
	 */
	करोwn_पढ़ो(&_origins_lock);
	o = __lookup_origin(merging_snap->origin->bdev);
	क्रम (n = 0; n < size; n += merging_snap->ti->max_io_len)
		अगर (__origin_ग_लिखो(&o->snapshots, sector + n, शून्य) ==
		    DM_MAPIO_SUBMITTED)
			must_रुको = 1;
	up_पढ़ो(&_origins_lock);

	वापस must_रुको;
पूर्ण

/*
 * Origin: maps a linear range of a device, with hooks क्रम snapshotting.
 */

/*
 * Conकाष्ठा an origin mapping: <dev_path>
 * The context क्रम an origin is merely a 'struct dm_dev *'
 * poपूर्णांकing to the real device.
 */
अटल पूर्णांक origin_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक r;
	काष्ठा dm_origin *o;

	अगर (argc != 1) अणु
		ti->error = "origin: incorrect number of arguments";
		वापस -EINVAL;
	पूर्ण

	o = kदो_स्मृति(माप(काष्ठा dm_origin), GFP_KERNEL);
	अगर (!o) अणु
		ti->error = "Cannot allocate private origin structure";
		r = -ENOMEM;
		जाओ bad_alloc;
	पूर्ण

	r = dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &o->dev);
	अगर (r) अणु
		ti->error = "Cannot get target device";
		जाओ bad_खोलो;
	पूर्ण

	o->ti = ti;
	ti->निजी = o;
	ti->num_flush_bios = 1;

	वापस 0;

bad_खोलो:
	kमुक्त(o);
bad_alloc:
	वापस r;
पूर्ण

अटल व्योम origin_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_origin *o = ti->निजी;

	dm_put_device(ti, o->dev);
	kमुक्त(o);
पूर्ण

अटल पूर्णांक origin_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा dm_origin *o = ti->निजी;
	अचिन्हित available_sectors;

	bio_set_dev(bio, o->dev->bdev);

	अगर (unlikely(bio->bi_opf & REQ_PREFLUSH))
		वापस DM_MAPIO_REMAPPED;

	अगर (bio_data_dir(bio) != WRITE)
		वापस DM_MAPIO_REMAPPED;

	available_sectors = o->split_boundary -
		((अचिन्हित)bio->bi_iter.bi_sector & (o->split_boundary - 1));

	अगर (bio_sectors(bio) > available_sectors)
		dm_accept_partial_bio(bio, available_sectors);

	/* Only tell snapshots अगर this is a ग_लिखो */
	वापस करो_origin(o->dev, bio, true);
पूर्ण

/*
 * Set the target "max_io_len" field to the minimum of all the snapshots'
 * chunk sizes.
 */
अटल व्योम origin_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_origin *o = ti->निजी;

	o->split_boundary = get_origin_minimum_chunksize(o->dev->bdev);

	करोwn_ग_लिखो(&_origins_lock);
	__insert_dm_origin(o);
	up_ग_लिखो(&_origins_lock);
पूर्ण

अटल व्योम origin_postsuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा dm_origin *o = ti->निजी;

	करोwn_ग_लिखो(&_origins_lock);
	__हटाओ_dm_origin(o);
	up_ग_लिखो(&_origins_lock);
पूर्ण

अटल व्योम origin_status(काष्ठा dm_target *ti, status_type_t type,
			  अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	काष्ठा dm_origin *o = ti->निजी;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		result[0] = '\0';
		अवरोध;

	हाल STATUSTYPE_TABLE:
		snम_लिखो(result, maxlen, "%s", o->dev->name);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक origin_iterate_devices(काष्ठा dm_target *ti,
				  iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा dm_origin *o = ti->निजी;

	वापस fn(ti, o->dev, 0, ti->len, data);
पूर्ण

अटल काष्ठा target_type origin_target = अणु
	.name    = "snapshot-origin",
	.version = अणु1, 9, 0पूर्ण,
	.module  = THIS_MODULE,
	.ctr     = origin_ctr,
	.dtr     = origin_dtr,
	.map     = origin_map,
	.resume  = origin_resume,
	.postsuspend = origin_postsuspend,
	.status  = origin_status,
	.iterate_devices = origin_iterate_devices,
पूर्ण;

अटल काष्ठा target_type snapshot_target = अणु
	.name    = "snapshot",
	.version = अणु1, 16, 0पूर्ण,
	.module  = THIS_MODULE,
	.ctr     = snapshot_ctr,
	.dtr     = snapshot_dtr,
	.map     = snapshot_map,
	.end_io  = snapshot_end_io,
	.preresume  = snapshot_preresume,
	.resume  = snapshot_resume,
	.status  = snapshot_status,
	.iterate_devices = snapshot_iterate_devices,
	.io_hपूर्णांकs = snapshot_io_hपूर्णांकs,
पूर्ण;

अटल काष्ठा target_type merge_target = अणु
	.name    = dm_snapshot_merge_target_name,
	.version = अणु1, 5, 0पूर्ण,
	.module  = THIS_MODULE,
	.ctr     = snapshot_ctr,
	.dtr     = snapshot_dtr,
	.map     = snapshot_merge_map,
	.end_io  = snapshot_end_io,
	.presuspend = snapshot_merge_presuspend,
	.preresume  = snapshot_preresume,
	.resume  = snapshot_merge_resume,
	.status  = snapshot_status,
	.iterate_devices = snapshot_iterate_devices,
	.io_hपूर्णांकs = snapshot_io_hपूर्णांकs,
पूर्ण;

अटल पूर्णांक __init dm_snapshot_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_exception_store_init();
	अगर (r) अणु
		DMERR("Failed to initialize exception stores");
		वापस r;
	पूर्ण

	r = init_origin_hash();
	अगर (r) अणु
		DMERR("init_origin_hash failed.");
		जाओ bad_origin_hash;
	पूर्ण

	exception_cache = KMEM_CACHE(dm_exception, 0);
	अगर (!exception_cache) अणु
		DMERR("Couldn't create exception cache.");
		r = -ENOMEM;
		जाओ bad_exception_cache;
	पूर्ण

	pending_cache = KMEM_CACHE(dm_snap_pending_exception, 0);
	अगर (!pending_cache) अणु
		DMERR("Couldn't create pending cache.");
		r = -ENOMEM;
		जाओ bad_pending_cache;
	पूर्ण

	r = dm_रेजिस्टर_target(&snapshot_target);
	अगर (r < 0) अणु
		DMERR("snapshot target register failed %d", r);
		जाओ bad_रेजिस्टर_snapshot_target;
	पूर्ण

	r = dm_रेजिस्टर_target(&origin_target);
	अगर (r < 0) अणु
		DMERR("Origin target register failed %d", r);
		जाओ bad_रेजिस्टर_origin_target;
	पूर्ण

	r = dm_रेजिस्टर_target(&merge_target);
	अगर (r < 0) अणु
		DMERR("Merge target register failed %d", r);
		जाओ bad_रेजिस्टर_merge_target;
	पूर्ण

	वापस 0;

bad_रेजिस्टर_merge_target:
	dm_unरेजिस्टर_target(&origin_target);
bad_रेजिस्टर_origin_target:
	dm_unरेजिस्टर_target(&snapshot_target);
bad_रेजिस्टर_snapshot_target:
	kmem_cache_destroy(pending_cache);
bad_pending_cache:
	kmem_cache_destroy(exception_cache);
bad_exception_cache:
	निकास_origin_hash();
bad_origin_hash:
	dm_exception_store_निकास();

	वापस r;
पूर्ण

अटल व्योम __निकास dm_snapshot_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&snapshot_target);
	dm_unरेजिस्टर_target(&origin_target);
	dm_unरेजिस्टर_target(&merge_target);

	निकास_origin_hash();
	kmem_cache_destroy(pending_cache);
	kmem_cache_destroy(exception_cache);

	dm_exception_store_निकास();
पूर्ण

/* Module hooks */
module_init(dm_snapshot_init);
module_निकास(dm_snapshot_निकास);

MODULE_DESCRIPTION(DM_NAME " snapshot target");
MODULE_AUTHOR("Joe Thornber");
MODULE_LICENSE("GPL");
MODULE_ALIAS("dm-snapshot-origin");
MODULE_ALIAS("dm-snapshot-merge");
