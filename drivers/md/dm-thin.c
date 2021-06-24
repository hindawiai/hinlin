<शैली गुरु>
/*
 * Copyright (C) 2011-2012 Red Hat UK.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-thin-metadata.h"
#समावेश "dm-bio-prison-v1.h"
#समावेश "dm.h"

#समावेश <linux/device-mapper.h>
#समावेश <linux/dm-पन.स>
#समावेश <linux/dm-kcopyd.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/log2.h>
#समावेश <linux/list.h>
#समावेश <linux/rculist.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sort.h>
#समावेश <linux/rbtree.h>

#घोषणा	DM_MSG_PREFIX	"thin"

/*
 * Tunable स्थिरants
 */
#घोषणा ENDIO_HOOK_POOL_SIZE 1024
#घोषणा MAPPING_POOL_SIZE 1024
#घोषणा COMMIT_PERIOD HZ
#घोषणा NO_SPACE_TIMEOUT_SECS 60

अटल अचिन्हित no_space_समयout_secs = NO_SPACE_TIMEOUT_SECS;

DECLARE_DM_KCOPYD_THROTTLE_WITH_MODULE_PARM(snapshot_copy_throttle,
		"A percentage of time allocated for copy on write");

/*
 * The block size of the device holding pool data must be
 * between 64KB and 1GB.
 */
#घोषणा DATA_DEV_BLOCK_SIZE_MIN_SECTORS (64 * 1024 >> SECTOR_SHIFT)
#घोषणा DATA_DEV_BLOCK_SIZE_MAX_SECTORS (1024 * 1024 * 1024 >> SECTOR_SHIFT)

/*
 * Device id is restricted to 24 bits.
 */
#घोषणा MAX_DEV_ID ((1 << 24) - 1)

/*
 * How करो we handle अवरोधing sharing of data blocks?
 * =================================================
 *
 * We use a standard copy-on-ग_लिखो btree to store the mappings क्रम the
 * devices (note I'm talking about copy-on-ग_लिखो of the metadata here, not
 * the data).  When you take an पूर्णांकernal snapshot you clone the root node
 * of the origin btree.  After this there is no concept of an origin or a
 * snapshot.  They are just two device trees that happen to poपूर्णांक to the
 * same data blocks.
 *
 * When we get a ग_लिखो in we decide अगर it's to a shared data block using
 * some बारtamp magic.  If it is, we have to अवरोध sharing.
 *
 * Let's say we ग_लिखो to a shared block in what was the origin.  The
 * steps are:
 *
 * i) plug io further to this physical block. (see bio_prison code).
 *
 * ii) quiesce any पढ़ो io to that shared data block.  Obviously
 * including all devices that share this block.  (see dm_deferred_set code)
 *
 * iii) copy the data block to a newly allocate block.  This step can be
 * missed out अगर the io covers the block. (schedule_copy).
 *
 * iv) insert the new mapping पूर्णांकo the origin's btree
 * (process_prepared_mapping).  This act of inserting अवरोधs some
 * sharing of btree nodes between the two devices.  Breaking sharing only
 * effects the btree of that specअगरic device.  Btrees क्रम the other
 * devices that share the block never change.  The btree क्रम the origin
 * device as it was after the last commit is untouched, ie. we're using
 * persistent data काष्ठाures in the functional programming sense.
 *
 * v) unplug io to this physical block, including the io that triggered
 * the अवरोधing of sharing.
 *
 * Steps (ii) and (iii) occur in parallel.
 *
 * The metadata _करोesn't_ need to be committed beक्रमe the io जारीs.  We
 * get away with this because the io is always written to a _new_ block.
 * If there's a crash, then:
 *
 * - The origin mapping will poपूर्णांक to the old origin block (the shared
 * one).  This will contain the data as it was beक्रमe the io that triggered
 * the अवरोधing of sharing came in.
 *
 * - The snap mapping still poपूर्णांकs to the old block.  As it would after
 * the commit.
 *
 * The करोwnside of this scheme is the बारtamp magic isn't perfect, and
 * will जारी to think that data block in the snapshot device is shared
 * even after the ग_लिखो to the origin has broken sharing.  I suspect data
 * blocks will typically be shared by many dअगरferent devices, so we're
 * अवरोधing sharing n + 1 बार, rather than n, where n is the number of
 * devices that reference this data block.  At the moment I think the
 * benefits far, far outweigh the disadvantages.
 */

/*----------------------------------------------------------------*/

/*
 * Key building.
 */
क्रमागत lock_space अणु
	VIRTUAL,
	PHYSICAL
पूर्ण;

अटल व्योम build_key(काष्ठा dm_thin_device *td, क्रमागत lock_space ls,
		      dm_block_t b, dm_block_t e, काष्ठा dm_cell_key *key)
अणु
	key->भव = (ls == VIRTUAL);
	key->dev = dm_thin_dev_id(td);
	key->block_begin = b;
	key->block_end = e;
पूर्ण

अटल व्योम build_data_key(काष्ठा dm_thin_device *td, dm_block_t b,
			   काष्ठा dm_cell_key *key)
अणु
	build_key(td, PHYSICAL, b, b + 1llu, key);
पूर्ण

अटल व्योम build_भव_key(काष्ठा dm_thin_device *td, dm_block_t b,
			      काष्ठा dm_cell_key *key)
अणु
	build_key(td, VIRTUAL, b, b + 1llu, key);
पूर्ण

/*----------------------------------------------------------------*/

#घोषणा THROTTLE_THRESHOLD (1 * HZ)

काष्ठा throttle अणु
	काष्ठा rw_semaphore lock;
	अचिन्हित दीर्घ threshold;
	bool throttle_applied;
पूर्ण;

अटल व्योम throttle_init(काष्ठा throttle *t)
अणु
	init_rwsem(&t->lock);
	t->throttle_applied = false;
पूर्ण

अटल व्योम throttle_work_start(काष्ठा throttle *t)
अणु
	t->threshold = jअगरfies + THROTTLE_THRESHOLD;
पूर्ण

अटल व्योम throttle_work_update(काष्ठा throttle *t)
अणु
	अगर (!t->throttle_applied && jअगरfies > t->threshold) अणु
		करोwn_ग_लिखो(&t->lock);
		t->throttle_applied = true;
	पूर्ण
पूर्ण

अटल व्योम throttle_work_complete(काष्ठा throttle *t)
अणु
	अगर (t->throttle_applied) अणु
		t->throttle_applied = false;
		up_ग_लिखो(&t->lock);
	पूर्ण
पूर्ण

अटल व्योम throttle_lock(काष्ठा throttle *t)
अणु
	करोwn_पढ़ो(&t->lock);
पूर्ण

अटल व्योम throttle_unlock(काष्ठा throttle *t)
अणु
	up_पढ़ो(&t->lock);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * A pool device ties together a metadata device and a data device.  It
 * also provides the पूर्णांकerface क्रम creating and destroying पूर्णांकernal
 * devices.
 */
काष्ठा dm_thin_new_mapping;

/*
 * The pool runs in various modes.  Ordered in degraded order क्रम comparisons.
 */
क्रमागत pool_mode अणु
	PM_WRITE,		/* metadata may be changed */
	PM_OUT_OF_DATA_SPACE,	/* metadata may be changed, though data may not be allocated */

	/*
	 * Like READ_ONLY, except may चयन back to WRITE on metadata resize. Reported as READ_ONLY.
	 */
	PM_OUT_OF_METADATA_SPACE,
	PM_READ_ONLY,		/* metadata may not be changed */

	PM_FAIL,		/* all I/O fails */
पूर्ण;

काष्ठा pool_features अणु
	क्रमागत pool_mode mode;

	bool zero_new_blocks:1;
	bool discard_enabled:1;
	bool discard_passकरोwn:1;
	bool error_अगर_no_space:1;
पूर्ण;

काष्ठा thin_c;
प्रकार व्योम (*process_bio_fn)(काष्ठा thin_c *tc, काष्ठा bio *bio);
प्रकार व्योम (*process_cell_fn)(काष्ठा thin_c *tc, काष्ठा dm_bio_prison_cell *cell);
प्रकार व्योम (*process_mapping_fn)(काष्ठा dm_thin_new_mapping *m);

#घोषणा CELL_SORT_ARRAY_SIZE 8192

काष्ठा pool अणु
	काष्ठा list_head list;
	काष्ठा dm_target *ti;	/* Only set अगर a pool target is bound */

	काष्ठा mapped_device *pool_md;
	काष्ठा block_device *data_dev;
	काष्ठा block_device *md_dev;
	काष्ठा dm_pool_metadata *pmd;

	dm_block_t low_water_blocks;
	uपूर्णांक32_t sectors_per_block;
	पूर्णांक sectors_per_block_shअगरt;

	काष्ठा pool_features pf;
	bool low_water_triggered:1;	/* A dm event has been sent */
	bool suspended:1;
	bool out_of_data_space:1;

	काष्ठा dm_bio_prison *prison;
	काष्ठा dm_kcopyd_client *copier;

	काष्ठा work_काष्ठा worker;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा throttle throttle;
	काष्ठा delayed_work waker;
	काष्ठा delayed_work no_space_समयout;

	अचिन्हित दीर्घ last_commit_jअगरfies;
	अचिन्हित ref_count;

	spinlock_t lock;
	काष्ठा bio_list deferred_flush_bios;
	काष्ठा bio_list deferred_flush_completions;
	काष्ठा list_head prepared_mappings;
	काष्ठा list_head prepared_discards;
	काष्ठा list_head prepared_discards_pt2;
	काष्ठा list_head active_thins;

	काष्ठा dm_deferred_set *shared_पढ़ो_ds;
	काष्ठा dm_deferred_set *all_io_ds;

	काष्ठा dm_thin_new_mapping *next_mapping;

	process_bio_fn process_bio;
	process_bio_fn process_discard;

	process_cell_fn process_cell;
	process_cell_fn process_discard_cell;

	process_mapping_fn process_prepared_mapping;
	process_mapping_fn process_prepared_discard;
	process_mapping_fn process_prepared_discard_pt2;

	काष्ठा dm_bio_prison_cell **cell_sort_array;

	mempool_t mapping_pool;

	काष्ठा bio flush_bio;
पूर्ण;

अटल व्योम metadata_operation_failed(काष्ठा pool *pool, स्थिर अक्षर *op, पूर्णांक r);

अटल क्रमागत pool_mode get_pool_mode(काष्ठा pool *pool)
अणु
	वापस pool->pf.mode;
पूर्ण

अटल व्योम notअगरy_of_pool_mode_change(काष्ठा pool *pool)
अणु
	स्थिर अक्षर *descs[] = अणु
		"write",
		"out-of-data-space",
		"read-only",
		"read-only",
		"fail"
	पूर्ण;
	स्थिर अक्षर *extra_desc = शून्य;
	क्रमागत pool_mode mode = get_pool_mode(pool);

	अगर (mode == PM_OUT_OF_DATA_SPACE) अणु
		अगर (!pool->pf.error_अगर_no_space)
			extra_desc = " (queue IO)";
		अन्यथा
			extra_desc = " (error IO)";
	पूर्ण

	dm_table_event(pool->ti->table);
	DMINFO("%s: switching pool to %s%s mode",
	       dm_device_name(pool->pool_md),
	       descs[(पूर्णांक)mode], extra_desc ? : "");
पूर्ण

/*
 * Target context क्रम a pool.
 */
काष्ठा pool_c अणु
	काष्ठा dm_target *ti;
	काष्ठा pool *pool;
	काष्ठा dm_dev *data_dev;
	काष्ठा dm_dev *metadata_dev;

	dm_block_t low_water_blocks;
	काष्ठा pool_features requested_pf; /* Features requested during table load */
	काष्ठा pool_features adjusted_pf;  /* Features used after adjusting क्रम स्थिरituent devices */
पूर्ण;

/*
 * Target context क्रम a thin.
 */
काष्ठा thin_c अणु
	काष्ठा list_head list;
	काष्ठा dm_dev *pool_dev;
	काष्ठा dm_dev *origin_dev;
	sector_t origin_size;
	dm_thin_id dev_id;

	काष्ठा pool *pool;
	काष्ठा dm_thin_device *td;
	काष्ठा mapped_device *thin_md;

	bool requeue_mode:1;
	spinlock_t lock;
	काष्ठा list_head deferred_cells;
	काष्ठा bio_list deferred_bio_list;
	काष्ठा bio_list retry_on_resume_list;
	काष्ठा rb_root sort_bio_list; /* sorted list of deferred bios */

	/*
	 * Ensures the thin is not destroyed until the worker has finished
	 * iterating the active_thins list.
	 */
	refcount_t refcount;
	काष्ठा completion can_destroy;
पूर्ण;

/*----------------------------------------------------------------*/

अटल bool block_size_is_घातer_of_two(काष्ठा pool *pool)
अणु
	वापस pool->sectors_per_block_shअगरt >= 0;
पूर्ण

अटल sector_t block_to_sectors(काष्ठा pool *pool, dm_block_t b)
अणु
	वापस block_size_is_घातer_of_two(pool) ?
		(b << pool->sectors_per_block_shअगरt) :
		(b * pool->sectors_per_block);
पूर्ण

/*----------------------------------------------------------------*/

काष्ठा discard_op अणु
	काष्ठा thin_c *tc;
	काष्ठा blk_plug plug;
	काष्ठा bio *parent_bio;
	काष्ठा bio *bio;
पूर्ण;

अटल व्योम begin_discard(काष्ठा discard_op *op, काष्ठा thin_c *tc, काष्ठा bio *parent)
अणु
	BUG_ON(!parent);

	op->tc = tc;
	blk_start_plug(&op->plug);
	op->parent_bio = parent;
	op->bio = शून्य;
पूर्ण

अटल पूर्णांक issue_discard(काष्ठा discard_op *op, dm_block_t data_b, dm_block_t data_e)
अणु
	काष्ठा thin_c *tc = op->tc;
	sector_t s = block_to_sectors(tc->pool, data_b);
	sector_t len = block_to_sectors(tc->pool, data_e - data_b);

	वापस __blkdev_issue_discard(tc->pool_dev->bdev, s, len,
				      GFP_NOWAIT, 0, &op->bio);
पूर्ण

अटल व्योम end_discard(काष्ठा discard_op *op, पूर्णांक r)
अणु
	अगर (op->bio) अणु
		/*
		 * Even अगर one of the calls to issue_discard failed, we
		 * need to रुको क्रम the chain to complete.
		 */
		bio_chain(op->bio, op->parent_bio);
		bio_set_op_attrs(op->bio, REQ_OP_DISCARD, 0);
		submit_bio(op->bio);
	पूर्ण

	blk_finish_plug(&op->plug);

	/*
	 * Even अगर r is set, there could be sub discards in flight that we
	 * need to रुको क्रम.
	 */
	अगर (r && !op->parent_bio->bi_status)
		op->parent_bio->bi_status = त्रुटि_सं_to_blk_status(r);
	bio_endio(op->parent_bio);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * wake_worker() is used when new work is queued and when pool_resume is
 * पढ़ोy to जारी deferred IO processing.
 */
अटल व्योम wake_worker(काष्ठा pool *pool)
अणु
	queue_work(pool->wq, &pool->worker);
पूर्ण

/*----------------------------------------------------------------*/

अटल पूर्णांक bio_detain(काष्ठा pool *pool, काष्ठा dm_cell_key *key, काष्ठा bio *bio,
		      काष्ठा dm_bio_prison_cell **cell_result)
अणु
	पूर्णांक r;
	काष्ठा dm_bio_prison_cell *cell_pपुनः_स्मृति;

	/*
	 * Allocate a cell from the prison's mempool.
	 * This might block but it can't fail.
	 */
	cell_pपुनः_स्मृति = dm_bio_prison_alloc_cell(pool->prison, GFP_NOIO);

	r = dm_bio_detain(pool->prison, key, bio, cell_pपुनः_स्मृति, cell_result);
	अगर (r)
		/*
		 * We reused an old cell; we can get rid of
		 * the new one.
		 */
		dm_bio_prison_मुक्त_cell(pool->prison, cell_pपुनः_स्मृति);

	वापस r;
पूर्ण

अटल व्योम cell_release(काष्ठा pool *pool,
			 काष्ठा dm_bio_prison_cell *cell,
			 काष्ठा bio_list *bios)
अणु
	dm_cell_release(pool->prison, cell, bios);
	dm_bio_prison_मुक्त_cell(pool->prison, cell);
पूर्ण

अटल व्योम cell_visit_release(काष्ठा pool *pool,
			       व्योम (*fn)(व्योम *, काष्ठा dm_bio_prison_cell *),
			       व्योम *context,
			       काष्ठा dm_bio_prison_cell *cell)
अणु
	dm_cell_visit_release(pool->prison, fn, context, cell);
	dm_bio_prison_मुक्त_cell(pool->prison, cell);
पूर्ण

अटल व्योम cell_release_no_holder(काष्ठा pool *pool,
				   काष्ठा dm_bio_prison_cell *cell,
				   काष्ठा bio_list *bios)
अणु
	dm_cell_release_no_holder(pool->prison, cell, bios);
	dm_bio_prison_मुक्त_cell(pool->prison, cell);
पूर्ण

अटल व्योम cell_error_with_code(काष्ठा pool *pool,
		काष्ठा dm_bio_prison_cell *cell, blk_status_t error_code)
अणु
	dm_cell_error(pool->prison, cell, error_code);
	dm_bio_prison_मुक्त_cell(pool->prison, cell);
पूर्ण

अटल blk_status_t get_pool_io_error_code(काष्ठा pool *pool)
अणु
	वापस pool->out_of_data_space ? BLK_STS_NOSPC : BLK_STS_IOERR;
पूर्ण

अटल व्योम cell_error(काष्ठा pool *pool, काष्ठा dm_bio_prison_cell *cell)
अणु
	cell_error_with_code(pool, cell, get_pool_io_error_code(pool));
पूर्ण

अटल व्योम cell_success(काष्ठा pool *pool, काष्ठा dm_bio_prison_cell *cell)
अणु
	cell_error_with_code(pool, cell, 0);
पूर्ण

अटल व्योम cell_requeue(काष्ठा pool *pool, काष्ठा dm_bio_prison_cell *cell)
अणु
	cell_error_with_code(pool, cell, BLK_STS_DM_REQUEUE);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * A global list of pools that uses a काष्ठा mapped_device as a key.
 */
अटल काष्ठा dm_thin_pool_table अणु
	काष्ठा mutex mutex;
	काष्ठा list_head pools;
पूर्ण dm_thin_pool_table;

अटल व्योम pool_table_init(व्योम)
अणु
	mutex_init(&dm_thin_pool_table.mutex);
	INIT_LIST_HEAD(&dm_thin_pool_table.pools);
पूर्ण

अटल व्योम pool_table_निकास(व्योम)
अणु
	mutex_destroy(&dm_thin_pool_table.mutex);
पूर्ण

अटल व्योम __pool_table_insert(काष्ठा pool *pool)
अणु
	BUG_ON(!mutex_is_locked(&dm_thin_pool_table.mutex));
	list_add(&pool->list, &dm_thin_pool_table.pools);
पूर्ण

अटल व्योम __pool_table_हटाओ(काष्ठा pool *pool)
अणु
	BUG_ON(!mutex_is_locked(&dm_thin_pool_table.mutex));
	list_del(&pool->list);
पूर्ण

अटल काष्ठा pool *__pool_table_lookup(काष्ठा mapped_device *md)
अणु
	काष्ठा pool *pool = शून्य, *पंचांगp;

	BUG_ON(!mutex_is_locked(&dm_thin_pool_table.mutex));

	list_क्रम_each_entry(पंचांगp, &dm_thin_pool_table.pools, list) अणु
		अगर (पंचांगp->pool_md == md) अणु
			pool = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस pool;
पूर्ण

अटल काष्ठा pool *__pool_table_lookup_metadata_dev(काष्ठा block_device *md_dev)
अणु
	काष्ठा pool *pool = शून्य, *पंचांगp;

	BUG_ON(!mutex_is_locked(&dm_thin_pool_table.mutex));

	list_क्रम_each_entry(पंचांगp, &dm_thin_pool_table.pools, list) अणु
		अगर (पंचांगp->md_dev == md_dev) अणु
			pool = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस pool;
पूर्ण

/*----------------------------------------------------------------*/

काष्ठा dm_thin_endio_hook अणु
	काष्ठा thin_c *tc;
	काष्ठा dm_deferred_entry *shared_पढ़ो_entry;
	काष्ठा dm_deferred_entry *all_io_entry;
	काष्ठा dm_thin_new_mapping *overग_लिखो_mapping;
	काष्ठा rb_node rb_node;
	काष्ठा dm_bio_prison_cell *cell;
पूर्ण;

अटल व्योम __merge_bio_list(काष्ठा bio_list *bios, काष्ठा bio_list *master)
अणु
	bio_list_merge(bios, master);
	bio_list_init(master);
पूर्ण

अटल व्योम error_bio_list(काष्ठा bio_list *bios, blk_status_t error)
अणु
	काष्ठा bio *bio;

	जबतक ((bio = bio_list_pop(bios))) अणु
		bio->bi_status = error;
		bio_endio(bio);
	पूर्ण
पूर्ण

अटल व्योम error_thin_bio_list(काष्ठा thin_c *tc, काष्ठा bio_list *master,
		blk_status_t error)
अणु
	काष्ठा bio_list bios;

	bio_list_init(&bios);

	spin_lock_irq(&tc->lock);
	__merge_bio_list(&bios, master);
	spin_unlock_irq(&tc->lock);

	error_bio_list(&bios, error);
पूर्ण

अटल व्योम requeue_deferred_cells(काष्ठा thin_c *tc)
अणु
	काष्ठा pool *pool = tc->pool;
	काष्ठा list_head cells;
	काष्ठा dm_bio_prison_cell *cell, *पंचांगp;

	INIT_LIST_HEAD(&cells);

	spin_lock_irq(&tc->lock);
	list_splice_init(&tc->deferred_cells, &cells);
	spin_unlock_irq(&tc->lock);

	list_क्रम_each_entry_safe(cell, पंचांगp, &cells, user_list)
		cell_requeue(pool, cell);
पूर्ण

अटल व्योम requeue_io(काष्ठा thin_c *tc)
अणु
	काष्ठा bio_list bios;

	bio_list_init(&bios);

	spin_lock_irq(&tc->lock);
	__merge_bio_list(&bios, &tc->deferred_bio_list);
	__merge_bio_list(&bios, &tc->retry_on_resume_list);
	spin_unlock_irq(&tc->lock);

	error_bio_list(&bios, BLK_STS_DM_REQUEUE);
	requeue_deferred_cells(tc);
पूर्ण

अटल व्योम error_retry_list_with_code(काष्ठा pool *pool, blk_status_t error)
अणु
	काष्ठा thin_c *tc;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(tc, &pool->active_thins, list)
		error_thin_bio_list(tc, &tc->retry_on_resume_list, error);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम error_retry_list(काष्ठा pool *pool)
अणु
	error_retry_list_with_code(pool, get_pool_io_error_code(pool));
पूर्ण

/*
 * This section of code contains the logic क्रम processing a thin device's IO.
 * Much of the code depends on pool object resources (lists, workqueues, etc)
 * but most is exclusively called from the thin target rather than the thin-pool
 * target.
 */

अटल dm_block_t get_bio_block(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	काष्ठा pool *pool = tc->pool;
	sector_t block_nr = bio->bi_iter.bi_sector;

	अगर (block_size_is_घातer_of_two(pool))
		block_nr >>= pool->sectors_per_block_shअगरt;
	अन्यथा
		(व्योम) sector_भाग(block_nr, pool->sectors_per_block);

	वापस block_nr;
पूर्ण

/*
 * Returns the _complete_ blocks that this bio covers.
 */
अटल व्योम get_bio_block_range(काष्ठा thin_c *tc, काष्ठा bio *bio,
				dm_block_t *begin, dm_block_t *end)
अणु
	काष्ठा pool *pool = tc->pool;
	sector_t b = bio->bi_iter.bi_sector;
	sector_t e = b + (bio->bi_iter.bi_size >> SECTOR_SHIFT);

	b += pool->sectors_per_block - 1ull; /* so we round up */

	अगर (block_size_is_घातer_of_two(pool)) अणु
		b >>= pool->sectors_per_block_shअगरt;
		e >>= pool->sectors_per_block_shअगरt;
	पूर्ण अन्यथा अणु
		(व्योम) sector_भाग(b, pool->sectors_per_block);
		(व्योम) sector_भाग(e, pool->sectors_per_block);
	पूर्ण

	अगर (e < b)
		/* Can happen अगर the bio is within a single block. */
		e = b;

	*begin = b;
	*end = e;
पूर्ण

अटल व्योम remap(काष्ठा thin_c *tc, काष्ठा bio *bio, dm_block_t block)
अणु
	काष्ठा pool *pool = tc->pool;
	sector_t bi_sector = bio->bi_iter.bi_sector;

	bio_set_dev(bio, tc->pool_dev->bdev);
	अगर (block_size_is_घातer_of_two(pool))
		bio->bi_iter.bi_sector =
			(block << pool->sectors_per_block_shअगरt) |
			(bi_sector & (pool->sectors_per_block - 1));
	अन्यथा
		bio->bi_iter.bi_sector = (block * pool->sectors_per_block) +
				 sector_भाग(bi_sector, pool->sectors_per_block);
पूर्ण

अटल व्योम remap_to_origin(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	bio_set_dev(bio, tc->origin_dev->bdev);
पूर्ण

अटल पूर्णांक bio_triggers_commit(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	वापस op_is_flush(bio->bi_opf) &&
		dm_thin_changed_this_transaction(tc->td);
पूर्ण

अटल व्योम inc_all_io_entry(काष्ठा pool *pool, काष्ठा bio *bio)
अणु
	काष्ठा dm_thin_endio_hook *h;

	अगर (bio_op(bio) == REQ_OP_DISCARD)
		वापस;

	h = dm_per_bio_data(bio, माप(काष्ठा dm_thin_endio_hook));
	h->all_io_entry = dm_deferred_entry_inc(pool->all_io_ds);
पूर्ण

अटल व्योम issue(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	काष्ठा pool *pool = tc->pool;

	अगर (!bio_triggers_commit(tc, bio)) अणु
		submit_bio_noacct(bio);
		वापस;
	पूर्ण

	/*
	 * Complete bio with an error अगर earlier I/O caused changes to
	 * the metadata that can't be committed e.g, due to I/O errors
	 * on the metadata device.
	 */
	अगर (dm_thin_पातed_changes(tc->td)) अणु
		bio_io_error(bio);
		वापस;
	पूर्ण

	/*
	 * Batch together any bios that trigger commits and then issue a
	 * single commit क्रम them in process_deferred_bios().
	 */
	spin_lock_irq(&pool->lock);
	bio_list_add(&pool->deferred_flush_bios, bio);
	spin_unlock_irq(&pool->lock);
पूर्ण

अटल व्योम remap_to_origin_and_issue(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	remap_to_origin(tc, bio);
	issue(tc, bio);
पूर्ण

अटल व्योम remap_and_issue(काष्ठा thin_c *tc, काष्ठा bio *bio,
			    dm_block_t block)
अणु
	remap(tc, bio, block);
	issue(tc, bio);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Bio endio functions.
 */
काष्ठा dm_thin_new_mapping अणु
	काष्ठा list_head list;

	bool pass_discard:1;
	bool maybe_shared:1;

	/*
	 * Track quiescing, copying and zeroing preparation actions.  When this
	 * counter hits zero the block is prepared and can be inserted पूर्णांकo the
	 * btree.
	 */
	atomic_t prepare_actions;

	blk_status_t status;
	काष्ठा thin_c *tc;
	dm_block_t virt_begin, virt_end;
	dm_block_t data_block;
	काष्ठा dm_bio_prison_cell *cell;

	/*
	 * If the bio covers the whole area of a block then we can aव्योम
	 * zeroing or copying.  Instead this bio is hooked.  The bio will
	 * still be in the cell, so care has to be taken to aव्योम issuing
	 * the bio twice.
	 */
	काष्ठा bio *bio;
	bio_end_io_t *saved_bi_end_io;
पूर्ण;

अटल व्योम __complete_mapping_preparation(काष्ठा dm_thin_new_mapping *m)
अणु
	काष्ठा pool *pool = m->tc->pool;

	अगर (atomic_dec_and_test(&m->prepare_actions)) अणु
		list_add_tail(&m->list, &pool->prepared_mappings);
		wake_worker(pool);
	पूर्ण
पूर्ण

अटल व्योम complete_mapping_preparation(काष्ठा dm_thin_new_mapping *m)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pool *pool = m->tc->pool;

	spin_lock_irqsave(&pool->lock, flags);
	__complete_mapping_preparation(m);
	spin_unlock_irqrestore(&pool->lock, flags);
पूर्ण

अटल व्योम copy_complete(पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err, व्योम *context)
अणु
	काष्ठा dm_thin_new_mapping *m = context;

	m->status = पढ़ो_err || ग_लिखो_err ? BLK_STS_IOERR : 0;
	complete_mapping_preparation(m);
पूर्ण

अटल व्योम overग_लिखो_endio(काष्ठा bio *bio)
अणु
	काष्ठा dm_thin_endio_hook *h = dm_per_bio_data(bio, माप(काष्ठा dm_thin_endio_hook));
	काष्ठा dm_thin_new_mapping *m = h->overग_लिखो_mapping;

	bio->bi_end_io = m->saved_bi_end_io;

	m->status = bio->bi_status;
	complete_mapping_preparation(m);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Workqueue.
 */

/*
 * Prepared mapping jobs.
 */

/*
 * This sends the bios in the cell, except the original holder, back
 * to the deferred_bios list.
 */
अटल व्योम cell_defer_no_holder(काष्ठा thin_c *tc, काष्ठा dm_bio_prison_cell *cell)
अणु
	काष्ठा pool *pool = tc->pool;
	अचिन्हित दीर्घ flags;
	पूर्णांक has_work;

	spin_lock_irqsave(&tc->lock, flags);
	cell_release_no_holder(pool, cell, &tc->deferred_bio_list);
	has_work = !bio_list_empty(&tc->deferred_bio_list);
	spin_unlock_irqrestore(&tc->lock, flags);

	अगर (has_work)
		wake_worker(pool);
पूर्ण

अटल व्योम thin_defer_bio(काष्ठा thin_c *tc, काष्ठा bio *bio);

काष्ठा remap_info अणु
	काष्ठा thin_c *tc;
	काष्ठा bio_list defer_bios;
	काष्ठा bio_list issue_bios;
पूर्ण;

अटल व्योम __inc_remap_and_issue_cell(व्योम *context,
				       काष्ठा dm_bio_prison_cell *cell)
अणु
	काष्ठा remap_info *info = context;
	काष्ठा bio *bio;

	जबतक ((bio = bio_list_pop(&cell->bios))) अणु
		अगर (op_is_flush(bio->bi_opf) || bio_op(bio) == REQ_OP_DISCARD)
			bio_list_add(&info->defer_bios, bio);
		अन्यथा अणु
			inc_all_io_entry(info->tc->pool, bio);

			/*
			 * We can't issue the bios with the bio prison lock
			 * held, so we add them to a list to issue on
			 * वापस from this function.
			 */
			bio_list_add(&info->issue_bios, bio);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम inc_remap_and_issue_cell(काष्ठा thin_c *tc,
				     काष्ठा dm_bio_prison_cell *cell,
				     dm_block_t block)
अणु
	काष्ठा bio *bio;
	काष्ठा remap_info info;

	info.tc = tc;
	bio_list_init(&info.defer_bios);
	bio_list_init(&info.issue_bios);

	/*
	 * We have to be careful to inc any bios we're about to issue
	 * beक्रमe the cell is released, and aव्योम a race with new bios
	 * being added to the cell.
	 */
	cell_visit_release(tc->pool, __inc_remap_and_issue_cell,
			   &info, cell);

	जबतक ((bio = bio_list_pop(&info.defer_bios)))
		thin_defer_bio(tc, bio);

	जबतक ((bio = bio_list_pop(&info.issue_bios)))
		remap_and_issue(info.tc, bio, block);
पूर्ण

अटल व्योम process_prepared_mapping_fail(काष्ठा dm_thin_new_mapping *m)
अणु
	cell_error(m->tc->pool, m->cell);
	list_del(&m->list);
	mempool_मुक्त(m, &m->tc->pool->mapping_pool);
पूर्ण

अटल व्योम complete_overग_लिखो_bio(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	काष्ठा pool *pool = tc->pool;

	/*
	 * If the bio has the REQ_FUA flag set we must commit the metadata
	 * beक्रमe संकेतing its completion.
	 */
	अगर (!bio_triggers_commit(tc, bio)) अणु
		bio_endio(bio);
		वापस;
	पूर्ण

	/*
	 * Complete bio with an error अगर earlier I/O caused changes to the
	 * metadata that can't be committed, e.g, due to I/O errors on the
	 * metadata device.
	 */
	अगर (dm_thin_पातed_changes(tc->td)) अणु
		bio_io_error(bio);
		वापस;
	पूर्ण

	/*
	 * Batch together any bios that trigger commits and then issue a
	 * single commit क्रम them in process_deferred_bios().
	 */
	spin_lock_irq(&pool->lock);
	bio_list_add(&pool->deferred_flush_completions, bio);
	spin_unlock_irq(&pool->lock);
पूर्ण

अटल व्योम process_prepared_mapping(काष्ठा dm_thin_new_mapping *m)
अणु
	काष्ठा thin_c *tc = m->tc;
	काष्ठा pool *pool = tc->pool;
	काष्ठा bio *bio = m->bio;
	पूर्णांक r;

	अगर (m->status) अणु
		cell_error(pool, m->cell);
		जाओ out;
	पूर्ण

	/*
	 * Commit the prepared block पूर्णांकo the mapping btree.
	 * Any I/O क्रम this block arriving after this poपूर्णांक will get
	 * remapped to it directly.
	 */
	r = dm_thin_insert_block(tc->td, m->virt_begin, m->data_block);
	अगर (r) अणु
		metadata_operation_failed(pool, "dm_thin_insert_block", r);
		cell_error(pool, m->cell);
		जाओ out;
	पूर्ण

	/*
	 * Release any bios held जबतक the block was being provisioned.
	 * If we are processing a ग_लिखो bio that completely covers the block,
	 * we alपढ़ोy processed it so can ignore it now when processing
	 * the bios in the cell.
	 */
	अगर (bio) अणु
		inc_remap_and_issue_cell(tc, m->cell, m->data_block);
		complete_overग_लिखो_bio(tc, bio);
	पूर्ण अन्यथा अणु
		inc_all_io_entry(tc->pool, m->cell->holder);
		remap_and_issue(tc, m->cell->holder, m->data_block);
		inc_remap_and_issue_cell(tc, m->cell, m->data_block);
	पूर्ण

out:
	list_del(&m->list);
	mempool_मुक्त(m, &pool->mapping_pool);
पूर्ण

/*----------------------------------------------------------------*/

अटल व्योम मुक्त_discard_mapping(काष्ठा dm_thin_new_mapping *m)
अणु
	काष्ठा thin_c *tc = m->tc;
	अगर (m->cell)
		cell_defer_no_holder(tc, m->cell);
	mempool_मुक्त(m, &tc->pool->mapping_pool);
पूर्ण

अटल व्योम process_prepared_discard_fail(काष्ठा dm_thin_new_mapping *m)
अणु
	bio_io_error(m->bio);
	मुक्त_discard_mapping(m);
पूर्ण

अटल व्योम process_prepared_discard_success(काष्ठा dm_thin_new_mapping *m)
अणु
	bio_endio(m->bio);
	मुक्त_discard_mapping(m);
पूर्ण

अटल व्योम process_prepared_discard_no_passकरोwn(काष्ठा dm_thin_new_mapping *m)
अणु
	पूर्णांक r;
	काष्ठा thin_c *tc = m->tc;

	r = dm_thin_हटाओ_range(tc->td, m->cell->key.block_begin, m->cell->key.block_end);
	अगर (r) अणु
		metadata_operation_failed(tc->pool, "dm_thin_remove_range", r);
		bio_io_error(m->bio);
	पूर्ण अन्यथा
		bio_endio(m->bio);

	cell_defer_no_holder(tc, m->cell);
	mempool_मुक्त(m, &tc->pool->mapping_pool);
पूर्ण

/*----------------------------------------------------------------*/

अटल व्योम passकरोwn_द्विगुन_checking_shared_status(काष्ठा dm_thin_new_mapping *m,
						   काष्ठा bio *discard_parent)
अणु
	/*
	 * We've alपढ़ोy unmapped this range of blocks, but beक्रमe we
	 * passकरोwn we have to check that these blocks are now unused.
	 */
	पूर्णांक r = 0;
	bool shared = true;
	काष्ठा thin_c *tc = m->tc;
	काष्ठा pool *pool = tc->pool;
	dm_block_t b = m->data_block, e, end = m->data_block + m->virt_end - m->virt_begin;
	काष्ठा discard_op op;

	begin_discard(&op, tc, discard_parent);
	जबतक (b != end) अणु
		/* find start of unmapped run */
		क्रम (; b < end; b++) अणु
			r = dm_pool_block_is_shared(pool->pmd, b, &shared);
			अगर (r)
				जाओ out;

			अगर (!shared)
				अवरोध;
		पूर्ण

		अगर (b == end)
			अवरोध;

		/* find end of run */
		क्रम (e = b + 1; e != end; e++) अणु
			r = dm_pool_block_is_shared(pool->pmd, e, &shared);
			अगर (r)
				जाओ out;

			अगर (shared)
				अवरोध;
		पूर्ण

		r = issue_discard(&op, b, e);
		अगर (r)
			जाओ out;

		b = e;
	पूर्ण
out:
	end_discard(&op, r);
पूर्ण

अटल व्योम queue_passकरोwn_pt2(काष्ठा dm_thin_new_mapping *m)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pool *pool = m->tc->pool;

	spin_lock_irqsave(&pool->lock, flags);
	list_add_tail(&m->list, &pool->prepared_discards_pt2);
	spin_unlock_irqrestore(&pool->lock, flags);
	wake_worker(pool);
पूर्ण

अटल व्योम passकरोwn_endio(काष्ठा bio *bio)
अणु
	/*
	 * It करोesn't matter अगर the passकरोwn discard failed, we still want
	 * to unmap (we ignore err).
	 */
	queue_passकरोwn_pt2(bio->bi_निजी);
	bio_put(bio);
पूर्ण

अटल व्योम process_prepared_discard_passकरोwn_pt1(काष्ठा dm_thin_new_mapping *m)
अणु
	पूर्णांक r;
	काष्ठा thin_c *tc = m->tc;
	काष्ठा pool *pool = tc->pool;
	काष्ठा bio *discard_parent;
	dm_block_t data_end = m->data_block + (m->virt_end - m->virt_begin);

	/*
	 * Only this thपढ़ो allocates blocks, so we can be sure that the
	 * newly unmapped blocks will not be allocated beक्रमe the end of
	 * the function.
	 */
	r = dm_thin_हटाओ_range(tc->td, m->virt_begin, m->virt_end);
	अगर (r) अणु
		metadata_operation_failed(pool, "dm_thin_remove_range", r);
		bio_io_error(m->bio);
		cell_defer_no_holder(tc, m->cell);
		mempool_मुक्त(m, &pool->mapping_pool);
		वापस;
	पूर्ण

	/*
	 * Increment the unmapped blocks.  This prevents a race between the
	 * passकरोwn io and पुनः_स्मृतिation of मुक्तd blocks.
	 */
	r = dm_pool_inc_data_range(pool->pmd, m->data_block, data_end);
	अगर (r) अणु
		metadata_operation_failed(pool, "dm_pool_inc_data_range", r);
		bio_io_error(m->bio);
		cell_defer_no_holder(tc, m->cell);
		mempool_मुक्त(m, &pool->mapping_pool);
		वापस;
	पूर्ण

	discard_parent = bio_alloc(GFP_NOIO, 1);
	अगर (!discard_parent) अणु
		DMWARN("%s: unable to allocate top level discard bio for passdown. Skipping passdown.",
		       dm_device_name(tc->pool->pool_md));
		queue_passकरोwn_pt2(m);

	पूर्ण अन्यथा अणु
		discard_parent->bi_end_io = passकरोwn_endio;
		discard_parent->bi_निजी = m;

		अगर (m->maybe_shared)
			passकरोwn_द्विगुन_checking_shared_status(m, discard_parent);
		अन्यथा अणु
			काष्ठा discard_op op;

			begin_discard(&op, tc, discard_parent);
			r = issue_discard(&op, m->data_block, data_end);
			end_discard(&op, r);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम process_prepared_discard_passकरोwn_pt2(काष्ठा dm_thin_new_mapping *m)
अणु
	पूर्णांक r;
	काष्ठा thin_c *tc = m->tc;
	काष्ठा pool *pool = tc->pool;

	/*
	 * The passकरोwn has completed, so now we can decrement all those
	 * unmapped blocks.
	 */
	r = dm_pool_dec_data_range(pool->pmd, m->data_block,
				   m->data_block + (m->virt_end - m->virt_begin));
	अगर (r) अणु
		metadata_operation_failed(pool, "dm_pool_dec_data_range", r);
		bio_io_error(m->bio);
	पूर्ण अन्यथा
		bio_endio(m->bio);

	cell_defer_no_holder(tc, m->cell);
	mempool_मुक्त(m, &pool->mapping_pool);
पूर्ण

अटल व्योम process_prepared(काष्ठा pool *pool, काष्ठा list_head *head,
			     process_mapping_fn *fn)
अणु
	काष्ठा list_head maps;
	काष्ठा dm_thin_new_mapping *m, *पंचांगp;

	INIT_LIST_HEAD(&maps);
	spin_lock_irq(&pool->lock);
	list_splice_init(head, &maps);
	spin_unlock_irq(&pool->lock);

	list_क्रम_each_entry_safe(m, पंचांगp, &maps, list)
		(*fn)(m);
पूर्ण

/*
 * Deferred bio jobs.
 */
अटल पूर्णांक io_overlaps_block(काष्ठा pool *pool, काष्ठा bio *bio)
अणु
	वापस bio->bi_iter.bi_size ==
		(pool->sectors_per_block << SECTOR_SHIFT);
पूर्ण

अटल पूर्णांक io_overग_लिखोs_block(काष्ठा pool *pool, काष्ठा bio *bio)
अणु
	वापस (bio_data_dir(bio) == WRITE) &&
		io_overlaps_block(pool, bio);
पूर्ण

अटल व्योम save_and_set_endio(काष्ठा bio *bio, bio_end_io_t **save,
			       bio_end_io_t *fn)
अणु
	*save = bio->bi_end_io;
	bio->bi_end_io = fn;
पूर्ण

अटल पूर्णांक ensure_next_mapping(काष्ठा pool *pool)
अणु
	अगर (pool->next_mapping)
		वापस 0;

	pool->next_mapping = mempool_alloc(&pool->mapping_pool, GFP_ATOMIC);

	वापस pool->next_mapping ? 0 : -ENOMEM;
पूर्ण

अटल काष्ठा dm_thin_new_mapping *get_next_mapping(काष्ठा pool *pool)
अणु
	काष्ठा dm_thin_new_mapping *m = pool->next_mapping;

	BUG_ON(!pool->next_mapping);

	स_रखो(m, 0, माप(काष्ठा dm_thin_new_mapping));
	INIT_LIST_HEAD(&m->list);
	m->bio = शून्य;

	pool->next_mapping = शून्य;

	वापस m;
पूर्ण

अटल व्योम ll_zero(काष्ठा thin_c *tc, काष्ठा dm_thin_new_mapping *m,
		    sector_t begin, sector_t end)
अणु
	काष्ठा dm_io_region to;

	to.bdev = tc->pool_dev->bdev;
	to.sector = begin;
	to.count = end - begin;

	dm_kcopyd_zero(tc->pool->copier, 1, &to, 0, copy_complete, m);
पूर्ण

अटल व्योम remap_and_issue_overग_लिखो(काष्ठा thin_c *tc, काष्ठा bio *bio,
				      dm_block_t data_begin,
				      काष्ठा dm_thin_new_mapping *m)
अणु
	काष्ठा pool *pool = tc->pool;
	काष्ठा dm_thin_endio_hook *h = dm_per_bio_data(bio, माप(काष्ठा dm_thin_endio_hook));

	h->overग_लिखो_mapping = m;
	m->bio = bio;
	save_and_set_endio(bio, &m->saved_bi_end_io, overग_लिखो_endio);
	inc_all_io_entry(pool, bio);
	remap_and_issue(tc, bio, data_begin);
पूर्ण

/*
 * A partial copy also needs to zero the uncopied region.
 */
अटल व्योम schedule_copy(काष्ठा thin_c *tc, dm_block_t virt_block,
			  काष्ठा dm_dev *origin, dm_block_t data_origin,
			  dm_block_t data_dest,
			  काष्ठा dm_bio_prison_cell *cell, काष्ठा bio *bio,
			  sector_t len)
अणु
	काष्ठा pool *pool = tc->pool;
	काष्ठा dm_thin_new_mapping *m = get_next_mapping(pool);

	m->tc = tc;
	m->virt_begin = virt_block;
	m->virt_end = virt_block + 1u;
	m->data_block = data_dest;
	m->cell = cell;

	/*
	 * quiesce action + copy action + an extra reference held क्रम the
	 * duration of this function (we may need to inc later क्रम a
	 * partial zero).
	 */
	atomic_set(&m->prepare_actions, 3);

	अगर (!dm_deferred_set_add_work(pool->shared_पढ़ो_ds, &m->list))
		complete_mapping_preparation(m); /* alपढ़ोy quiesced */

	/*
	 * IO to pool_dev remaps to the pool target's data_dev.
	 *
	 * If the whole block of data is being overwritten, we can issue the
	 * bio immediately. Otherwise we use kcopyd to clone the data first.
	 */
	अगर (io_overग_लिखोs_block(pool, bio))
		remap_and_issue_overग_लिखो(tc, bio, data_dest, m);
	अन्यथा अणु
		काष्ठा dm_io_region from, to;

		from.bdev = origin->bdev;
		from.sector = data_origin * pool->sectors_per_block;
		from.count = len;

		to.bdev = tc->pool_dev->bdev;
		to.sector = data_dest * pool->sectors_per_block;
		to.count = len;

		dm_kcopyd_copy(pool->copier, &from, 1, &to,
			       0, copy_complete, m);

		/*
		 * Do we need to zero a tail region?
		 */
		अगर (len < pool->sectors_per_block && pool->pf.zero_new_blocks) अणु
			atomic_inc(&m->prepare_actions);
			ll_zero(tc, m,
				data_dest * pool->sectors_per_block + len,
				(data_dest + 1) * pool->sectors_per_block);
		पूर्ण
	पूर्ण

	complete_mapping_preparation(m); /* drop our ref */
पूर्ण

अटल व्योम schedule_पूर्णांकernal_copy(काष्ठा thin_c *tc, dm_block_t virt_block,
				   dm_block_t data_origin, dm_block_t data_dest,
				   काष्ठा dm_bio_prison_cell *cell, काष्ठा bio *bio)
अणु
	schedule_copy(tc, virt_block, tc->pool_dev,
		      data_origin, data_dest, cell, bio,
		      tc->pool->sectors_per_block);
पूर्ण

अटल व्योम schedule_zero(काष्ठा thin_c *tc, dm_block_t virt_block,
			  dm_block_t data_block, काष्ठा dm_bio_prison_cell *cell,
			  काष्ठा bio *bio)
अणु
	काष्ठा pool *pool = tc->pool;
	काष्ठा dm_thin_new_mapping *m = get_next_mapping(pool);

	atomic_set(&m->prepare_actions, 1); /* no need to quiesce */
	m->tc = tc;
	m->virt_begin = virt_block;
	m->virt_end = virt_block + 1u;
	m->data_block = data_block;
	m->cell = cell;

	/*
	 * If the whole block of data is being overwritten or we are not
	 * zeroing pre-existing data, we can issue the bio immediately.
	 * Otherwise we use kcopyd to zero the data first.
	 */
	अगर (pool->pf.zero_new_blocks) अणु
		अगर (io_overग_लिखोs_block(pool, bio))
			remap_and_issue_overग_लिखो(tc, bio, data_block, m);
		अन्यथा
			ll_zero(tc, m, data_block * pool->sectors_per_block,
				(data_block + 1) * pool->sectors_per_block);
	पूर्ण अन्यथा
		process_prepared_mapping(m);
पूर्ण

अटल व्योम schedule_बाह्यal_copy(काष्ठा thin_c *tc, dm_block_t virt_block,
				   dm_block_t data_dest,
				   काष्ठा dm_bio_prison_cell *cell, काष्ठा bio *bio)
अणु
	काष्ठा pool *pool = tc->pool;
	sector_t virt_block_begin = virt_block * pool->sectors_per_block;
	sector_t virt_block_end = (virt_block + 1) * pool->sectors_per_block;

	अगर (virt_block_end <= tc->origin_size)
		schedule_copy(tc, virt_block, tc->origin_dev,
			      virt_block, data_dest, cell, bio,
			      pool->sectors_per_block);

	अन्यथा अगर (virt_block_begin < tc->origin_size)
		schedule_copy(tc, virt_block, tc->origin_dev,
			      virt_block, data_dest, cell, bio,
			      tc->origin_size - virt_block_begin);

	अन्यथा
		schedule_zero(tc, virt_block, data_dest, cell, bio);
पूर्ण

अटल व्योम set_pool_mode(काष्ठा pool *pool, क्रमागत pool_mode new_mode);

अटल व्योम requeue_bios(काष्ठा pool *pool);

अटल bool is_पढ़ो_only_pool_mode(क्रमागत pool_mode mode)
अणु
	वापस (mode == PM_OUT_OF_METADATA_SPACE || mode == PM_READ_ONLY);
पूर्ण

अटल bool is_पढ़ो_only(काष्ठा pool *pool)
अणु
	वापस is_पढ़ो_only_pool_mode(get_pool_mode(pool));
पूर्ण

अटल व्योम check_क्रम_metadata_space(काष्ठा pool *pool)
अणु
	पूर्णांक r;
	स्थिर अक्षर *ooms_reason = शून्य;
	dm_block_t nr_मुक्त;

	r = dm_pool_get_मुक्त_metadata_block_count(pool->pmd, &nr_मुक्त);
	अगर (r)
		ooms_reason = "Could not get free metadata blocks";
	अन्यथा अगर (!nr_मुक्त)
		ooms_reason = "No free metadata blocks";

	अगर (ooms_reason && !is_पढ़ो_only(pool)) अणु
		DMERR("%s", ooms_reason);
		set_pool_mode(pool, PM_OUT_OF_METADATA_SPACE);
	पूर्ण
पूर्ण

अटल व्योम check_क्रम_data_space(काष्ठा pool *pool)
अणु
	पूर्णांक r;
	dm_block_t nr_मुक्त;

	अगर (get_pool_mode(pool) != PM_OUT_OF_DATA_SPACE)
		वापस;

	r = dm_pool_get_मुक्त_block_count(pool->pmd, &nr_मुक्त);
	अगर (r)
		वापस;

	अगर (nr_मुक्त) अणु
		set_pool_mode(pool, PM_WRITE);
		requeue_bios(pool);
	पूर्ण
पूर्ण

/*
 * A non-zero वापस indicates पढ़ो_only or fail_io mode.
 * Many callers करोn't care about the वापस value.
 */
अटल पूर्णांक commit(काष्ठा pool *pool)
अणु
	पूर्णांक r;

	अगर (get_pool_mode(pool) >= PM_OUT_OF_METADATA_SPACE)
		वापस -EINVAL;

	r = dm_pool_commit_metadata(pool->pmd);
	अगर (r)
		metadata_operation_failed(pool, "dm_pool_commit_metadata", r);
	अन्यथा अणु
		check_क्रम_metadata_space(pool);
		check_क्रम_data_space(pool);
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम check_low_water_mark(काष्ठा pool *pool, dm_block_t मुक्त_blocks)
अणु
	अगर (मुक्त_blocks <= pool->low_water_blocks && !pool->low_water_triggered) अणु
		DMWARN("%s: reached low water mark for data device: sending event.",
		       dm_device_name(pool->pool_md));
		spin_lock_irq(&pool->lock);
		pool->low_water_triggered = true;
		spin_unlock_irq(&pool->lock);
		dm_table_event(pool->ti->table);
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_data_block(काष्ठा thin_c *tc, dm_block_t *result)
अणु
	पूर्णांक r;
	dm_block_t मुक्त_blocks;
	काष्ठा pool *pool = tc->pool;

	अगर (WARN_ON(get_pool_mode(pool) != PM_WRITE))
		वापस -EINVAL;

	r = dm_pool_get_मुक्त_block_count(pool->pmd, &मुक्त_blocks);
	अगर (r) अणु
		metadata_operation_failed(pool, "dm_pool_get_free_block_count", r);
		वापस r;
	पूर्ण

	check_low_water_mark(pool, मुक्त_blocks);

	अगर (!मुक्त_blocks) अणु
		/*
		 * Try to commit to see अगर that will मुक्त up some
		 * more space.
		 */
		r = commit(pool);
		अगर (r)
			वापस r;

		r = dm_pool_get_मुक्त_block_count(pool->pmd, &मुक्त_blocks);
		अगर (r) अणु
			metadata_operation_failed(pool, "dm_pool_get_free_block_count", r);
			वापस r;
		पूर्ण

		अगर (!मुक्त_blocks) अणु
			set_pool_mode(pool, PM_OUT_OF_DATA_SPACE);
			वापस -ENOSPC;
		पूर्ण
	पूर्ण

	r = dm_pool_alloc_data_block(pool->pmd, result);
	अगर (r) अणु
		अगर (r == -ENOSPC)
			set_pool_mode(pool, PM_OUT_OF_DATA_SPACE);
		अन्यथा
			metadata_operation_failed(pool, "dm_pool_alloc_data_block", r);
		वापस r;
	पूर्ण

	r = dm_pool_get_मुक्त_metadata_block_count(pool->pmd, &मुक्त_blocks);
	अगर (r) अणु
		metadata_operation_failed(pool, "dm_pool_get_free_metadata_block_count", r);
		वापस r;
	पूर्ण

	अगर (!मुक्त_blocks) अणु
		/* Let's commit beक्रमe we use up the metadata reserve. */
		r = commit(pool);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If we have run out of space, queue bios until the device is
 * resumed, presumably after having been reloaded with more space.
 */
अटल व्योम retry_on_resume(काष्ठा bio *bio)
अणु
	काष्ठा dm_thin_endio_hook *h = dm_per_bio_data(bio, माप(काष्ठा dm_thin_endio_hook));
	काष्ठा thin_c *tc = h->tc;

	spin_lock_irq(&tc->lock);
	bio_list_add(&tc->retry_on_resume_list, bio);
	spin_unlock_irq(&tc->lock);
पूर्ण

अटल blk_status_t should_error_unserviceable_bio(काष्ठा pool *pool)
अणु
	क्रमागत pool_mode m = get_pool_mode(pool);

	चयन (m) अणु
	हाल PM_WRITE:
		/* Shouldn't get here */
		DMERR_LIMIT("bio unserviceable, yet pool is in PM_WRITE mode");
		वापस BLK_STS_IOERR;

	हाल PM_OUT_OF_DATA_SPACE:
		वापस pool->pf.error_अगर_no_space ? BLK_STS_NOSPC : 0;

	हाल PM_OUT_OF_METADATA_SPACE:
	हाल PM_READ_ONLY:
	हाल PM_FAIL:
		वापस BLK_STS_IOERR;
	शेष:
		/* Shouldn't get here */
		DMERR_LIMIT("bio unserviceable, yet pool has an unknown mode");
		वापस BLK_STS_IOERR;
	पूर्ण
पूर्ण

अटल व्योम handle_unserviceable_bio(काष्ठा pool *pool, काष्ठा bio *bio)
अणु
	blk_status_t error = should_error_unserviceable_bio(pool);

	अगर (error) अणु
		bio->bi_status = error;
		bio_endio(bio);
	पूर्ण अन्यथा
		retry_on_resume(bio);
पूर्ण

अटल व्योम retry_bios_on_resume(काष्ठा pool *pool, काष्ठा dm_bio_prison_cell *cell)
अणु
	काष्ठा bio *bio;
	काष्ठा bio_list bios;
	blk_status_t error;

	error = should_error_unserviceable_bio(pool);
	अगर (error) अणु
		cell_error_with_code(pool, cell, error);
		वापस;
	पूर्ण

	bio_list_init(&bios);
	cell_release(pool, cell, &bios);

	जबतक ((bio = bio_list_pop(&bios)))
		retry_on_resume(bio);
पूर्ण

अटल व्योम process_discard_cell_no_passकरोwn(काष्ठा thin_c *tc,
					     काष्ठा dm_bio_prison_cell *virt_cell)
अणु
	काष्ठा pool *pool = tc->pool;
	काष्ठा dm_thin_new_mapping *m = get_next_mapping(pool);

	/*
	 * We करोn't need to lock the data blocks, since there's no
	 * passकरोwn.  We only lock data blocks क्रम allocation and अवरोधing sharing.
	 */
	m->tc = tc;
	m->virt_begin = virt_cell->key.block_begin;
	m->virt_end = virt_cell->key.block_end;
	m->cell = virt_cell;
	m->bio = virt_cell->holder;

	अगर (!dm_deferred_set_add_work(pool->all_io_ds, &m->list))
		pool->process_prepared_discard(m);
पूर्ण

अटल व्योम अवरोध_up_discard_bio(काष्ठा thin_c *tc, dm_block_t begin, dm_block_t end,
				 काष्ठा bio *bio)
अणु
	काष्ठा pool *pool = tc->pool;

	पूर्णांक r;
	bool maybe_shared;
	काष्ठा dm_cell_key data_key;
	काष्ठा dm_bio_prison_cell *data_cell;
	काष्ठा dm_thin_new_mapping *m;
	dm_block_t virt_begin, virt_end, data_begin;

	जबतक (begin != end) अणु
		r = ensure_next_mapping(pool);
		अगर (r)
			/* we did our best */
			वापस;

		r = dm_thin_find_mapped_range(tc->td, begin, end, &virt_begin, &virt_end,
					      &data_begin, &maybe_shared);
		अगर (r)
			/*
			 * Silently fail, letting any mappings we've
			 * created complete.
			 */
			अवरोध;

		build_key(tc->td, PHYSICAL, data_begin, data_begin + (virt_end - virt_begin), &data_key);
		अगर (bio_detain(tc->pool, &data_key, शून्य, &data_cell)) अणु
			/* contention, we'll give up with this range */
			begin = virt_end;
			जारी;
		पूर्ण

		/*
		 * IO may still be going to the destination block.  We must
		 * quiesce beक्रमe we can करो the removal.
		 */
		m = get_next_mapping(pool);
		m->tc = tc;
		m->maybe_shared = maybe_shared;
		m->virt_begin = virt_begin;
		m->virt_end = virt_end;
		m->data_block = data_begin;
		m->cell = data_cell;
		m->bio = bio;

		/*
		 * The parent bio must not complete beक्रमe sub discard bios are
		 * chained to it (see end_discard's bio_chain)!
		 *
		 * This per-mapping bi_reमुख्यing increment is paired with
		 * the implicit decrement that occurs via bio_endio() in
		 * end_discard().
		 */
		bio_inc_reमुख्यing(bio);
		अगर (!dm_deferred_set_add_work(pool->all_io_ds, &m->list))
			pool->process_prepared_discard(m);

		begin = virt_end;
	पूर्ण
पूर्ण

अटल व्योम process_discard_cell_passकरोwn(काष्ठा thin_c *tc, काष्ठा dm_bio_prison_cell *virt_cell)
अणु
	काष्ठा bio *bio = virt_cell->holder;
	काष्ठा dm_thin_endio_hook *h = dm_per_bio_data(bio, माप(काष्ठा dm_thin_endio_hook));

	/*
	 * The virt_cell will only get मुक्तd once the origin bio completes.
	 * This means it will reमुख्य locked जबतक all the inभागidual
	 * passकरोwn bios are in flight.
	 */
	h->cell = virt_cell;
	अवरोध_up_discard_bio(tc, virt_cell->key.block_begin, virt_cell->key.block_end, bio);

	/*
	 * We complete the bio now, knowing that the bi_reमुख्यing field
	 * will prevent completion until the sub range discards have
	 * completed.
	 */
	bio_endio(bio);
पूर्ण

अटल व्योम process_discard_bio(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	dm_block_t begin, end;
	काष्ठा dm_cell_key virt_key;
	काष्ठा dm_bio_prison_cell *virt_cell;

	get_bio_block_range(tc, bio, &begin, &end);
	अगर (begin == end) अणु
		/*
		 * The discard covers less than a block.
		 */
		bio_endio(bio);
		वापस;
	पूर्ण

	build_key(tc->td, VIRTUAL, begin, end, &virt_key);
	अगर (bio_detain(tc->pool, &virt_key, bio, &virt_cell))
		/*
		 * Potential starvation issue: We're relying on the
		 * fs/application being well behaved, and not trying to
		 * send IO to a region at the same समय as discarding it.
		 * If they करो this persistently then it's possible this
		 * cell will never be granted.
		 */
		वापस;

	tc->pool->process_discard_cell(tc, virt_cell);
पूर्ण

अटल व्योम अवरोध_sharing(काष्ठा thin_c *tc, काष्ठा bio *bio, dm_block_t block,
			  काष्ठा dm_cell_key *key,
			  काष्ठा dm_thin_lookup_result *lookup_result,
			  काष्ठा dm_bio_prison_cell *cell)
अणु
	पूर्णांक r;
	dm_block_t data_block;
	काष्ठा pool *pool = tc->pool;

	r = alloc_data_block(tc, &data_block);
	चयन (r) अणु
	हाल 0:
		schedule_पूर्णांकernal_copy(tc, block, lookup_result->block,
				       data_block, cell, bio);
		अवरोध;

	हाल -ENOSPC:
		retry_bios_on_resume(pool, cell);
		अवरोध;

	शेष:
		DMERR_LIMIT("%s: alloc_data_block() failed: error = %d",
			    __func__, r);
		cell_error(pool, cell);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __remap_and_issue_shared_cell(व्योम *context,
					  काष्ठा dm_bio_prison_cell *cell)
अणु
	काष्ठा remap_info *info = context;
	काष्ठा bio *bio;

	जबतक ((bio = bio_list_pop(&cell->bios))) अणु
		अगर (bio_data_dir(bio) == WRITE || op_is_flush(bio->bi_opf) ||
		    bio_op(bio) == REQ_OP_DISCARD)
			bio_list_add(&info->defer_bios, bio);
		अन्यथा अणु
			काष्ठा dm_thin_endio_hook *h = dm_per_bio_data(bio, माप(काष्ठा dm_thin_endio_hook));

			h->shared_पढ़ो_entry = dm_deferred_entry_inc(info->tc->pool->shared_पढ़ो_ds);
			inc_all_io_entry(info->tc->pool, bio);
			bio_list_add(&info->issue_bios, bio);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम remap_and_issue_shared_cell(काष्ठा thin_c *tc,
					काष्ठा dm_bio_prison_cell *cell,
					dm_block_t block)
अणु
	काष्ठा bio *bio;
	काष्ठा remap_info info;

	info.tc = tc;
	bio_list_init(&info.defer_bios);
	bio_list_init(&info.issue_bios);

	cell_visit_release(tc->pool, __remap_and_issue_shared_cell,
			   &info, cell);

	जबतक ((bio = bio_list_pop(&info.defer_bios)))
		thin_defer_bio(tc, bio);

	जबतक ((bio = bio_list_pop(&info.issue_bios)))
		remap_and_issue(tc, bio, block);
पूर्ण

अटल व्योम process_shared_bio(काष्ठा thin_c *tc, काष्ठा bio *bio,
			       dm_block_t block,
			       काष्ठा dm_thin_lookup_result *lookup_result,
			       काष्ठा dm_bio_prison_cell *virt_cell)
अणु
	काष्ठा dm_bio_prison_cell *data_cell;
	काष्ठा pool *pool = tc->pool;
	काष्ठा dm_cell_key key;

	/*
	 * If cell is alपढ़ोy occupied, then sharing is alपढ़ोy in the process
	 * of being broken so we have nothing further to करो here.
	 */
	build_data_key(tc->td, lookup_result->block, &key);
	अगर (bio_detain(pool, &key, bio, &data_cell)) अणु
		cell_defer_no_holder(tc, virt_cell);
		वापस;
	पूर्ण

	अगर (bio_data_dir(bio) == WRITE && bio->bi_iter.bi_size) अणु
		अवरोध_sharing(tc, bio, block, &key, lookup_result, data_cell);
		cell_defer_no_holder(tc, virt_cell);
	पूर्ण अन्यथा अणु
		काष्ठा dm_thin_endio_hook *h = dm_per_bio_data(bio, माप(काष्ठा dm_thin_endio_hook));

		h->shared_पढ़ो_entry = dm_deferred_entry_inc(pool->shared_पढ़ो_ds);
		inc_all_io_entry(pool, bio);
		remap_and_issue(tc, bio, lookup_result->block);

		remap_and_issue_shared_cell(tc, data_cell, lookup_result->block);
		remap_and_issue_shared_cell(tc, virt_cell, lookup_result->block);
	पूर्ण
पूर्ण

अटल व्योम provision_block(काष्ठा thin_c *tc, काष्ठा bio *bio, dm_block_t block,
			    काष्ठा dm_bio_prison_cell *cell)
अणु
	पूर्णांक r;
	dm_block_t data_block;
	काष्ठा pool *pool = tc->pool;

	/*
	 * Remap empty bios (flushes) immediately, without provisioning.
	 */
	अगर (!bio->bi_iter.bi_size) अणु
		inc_all_io_entry(pool, bio);
		cell_defer_no_holder(tc, cell);

		remap_and_issue(tc, bio, 0);
		वापस;
	पूर्ण

	/*
	 * Fill पढ़ो bios with zeroes and complete them immediately.
	 */
	अगर (bio_data_dir(bio) == READ) अणु
		zero_fill_bio(bio);
		cell_defer_no_holder(tc, cell);
		bio_endio(bio);
		वापस;
	पूर्ण

	r = alloc_data_block(tc, &data_block);
	चयन (r) अणु
	हाल 0:
		अगर (tc->origin_dev)
			schedule_बाह्यal_copy(tc, block, data_block, cell, bio);
		अन्यथा
			schedule_zero(tc, block, data_block, cell, bio);
		अवरोध;

	हाल -ENOSPC:
		retry_bios_on_resume(pool, cell);
		अवरोध;

	शेष:
		DMERR_LIMIT("%s: alloc_data_block() failed: error = %d",
			    __func__, r);
		cell_error(pool, cell);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम process_cell(काष्ठा thin_c *tc, काष्ठा dm_bio_prison_cell *cell)
अणु
	पूर्णांक r;
	काष्ठा pool *pool = tc->pool;
	काष्ठा bio *bio = cell->holder;
	dm_block_t block = get_bio_block(tc, bio);
	काष्ठा dm_thin_lookup_result lookup_result;

	अगर (tc->requeue_mode) अणु
		cell_requeue(pool, cell);
		वापस;
	पूर्ण

	r = dm_thin_find_block(tc->td, block, 1, &lookup_result);
	चयन (r) अणु
	हाल 0:
		अगर (lookup_result.shared)
			process_shared_bio(tc, bio, block, &lookup_result, cell);
		अन्यथा अणु
			inc_all_io_entry(pool, bio);
			remap_and_issue(tc, bio, lookup_result.block);
			inc_remap_and_issue_cell(tc, cell, lookup_result.block);
		पूर्ण
		अवरोध;

	हाल -ENODATA:
		अगर (bio_data_dir(bio) == READ && tc->origin_dev) अणु
			inc_all_io_entry(pool, bio);
			cell_defer_no_holder(tc, cell);

			अगर (bio_end_sector(bio) <= tc->origin_size)
				remap_to_origin_and_issue(tc, bio);

			अन्यथा अगर (bio->bi_iter.bi_sector < tc->origin_size) अणु
				zero_fill_bio(bio);
				bio->bi_iter.bi_size = (tc->origin_size - bio->bi_iter.bi_sector) << SECTOR_SHIFT;
				remap_to_origin_and_issue(tc, bio);

			पूर्ण अन्यथा अणु
				zero_fill_bio(bio);
				bio_endio(bio);
			पूर्ण
		पूर्ण अन्यथा
			provision_block(tc, bio, block, cell);
		अवरोध;

	शेष:
		DMERR_LIMIT("%s: dm_thin_find_block() failed: error = %d",
			    __func__, r);
		cell_defer_no_holder(tc, cell);
		bio_io_error(bio);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम process_bio(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	काष्ठा pool *pool = tc->pool;
	dm_block_t block = get_bio_block(tc, bio);
	काष्ठा dm_bio_prison_cell *cell;
	काष्ठा dm_cell_key key;

	/*
	 * If cell is alपढ़ोy occupied, then the block is alपढ़ोy
	 * being provisioned so we have nothing further to करो here.
	 */
	build_भव_key(tc->td, block, &key);
	अगर (bio_detain(pool, &key, bio, &cell))
		वापस;

	process_cell(tc, cell);
पूर्ण

अटल व्योम __process_bio_पढ़ो_only(काष्ठा thin_c *tc, काष्ठा bio *bio,
				    काष्ठा dm_bio_prison_cell *cell)
अणु
	पूर्णांक r;
	पूर्णांक rw = bio_data_dir(bio);
	dm_block_t block = get_bio_block(tc, bio);
	काष्ठा dm_thin_lookup_result lookup_result;

	r = dm_thin_find_block(tc->td, block, 1, &lookup_result);
	चयन (r) अणु
	हाल 0:
		अगर (lookup_result.shared && (rw == WRITE) && bio->bi_iter.bi_size) अणु
			handle_unserviceable_bio(tc->pool, bio);
			अगर (cell)
				cell_defer_no_holder(tc, cell);
		पूर्ण अन्यथा अणु
			inc_all_io_entry(tc->pool, bio);
			remap_and_issue(tc, bio, lookup_result.block);
			अगर (cell)
				inc_remap_and_issue_cell(tc, cell, lookup_result.block);
		पूर्ण
		अवरोध;

	हाल -ENODATA:
		अगर (cell)
			cell_defer_no_holder(tc, cell);
		अगर (rw != READ) अणु
			handle_unserviceable_bio(tc->pool, bio);
			अवरोध;
		पूर्ण

		अगर (tc->origin_dev) अणु
			inc_all_io_entry(tc->pool, bio);
			remap_to_origin_and_issue(tc, bio);
			अवरोध;
		पूर्ण

		zero_fill_bio(bio);
		bio_endio(bio);
		अवरोध;

	शेष:
		DMERR_LIMIT("%s: dm_thin_find_block() failed: error = %d",
			    __func__, r);
		अगर (cell)
			cell_defer_no_holder(tc, cell);
		bio_io_error(bio);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम process_bio_पढ़ो_only(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	__process_bio_पढ़ो_only(tc, bio, शून्य);
पूर्ण

अटल व्योम process_cell_पढ़ो_only(काष्ठा thin_c *tc, काष्ठा dm_bio_prison_cell *cell)
अणु
	__process_bio_पढ़ो_only(tc, cell->holder, cell);
पूर्ण

अटल व्योम process_bio_success(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	bio_endio(bio);
पूर्ण

अटल व्योम process_bio_fail(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	bio_io_error(bio);
पूर्ण

अटल व्योम process_cell_success(काष्ठा thin_c *tc, काष्ठा dm_bio_prison_cell *cell)
अणु
	cell_success(tc->pool, cell);
पूर्ण

अटल व्योम process_cell_fail(काष्ठा thin_c *tc, काष्ठा dm_bio_prison_cell *cell)
अणु
	cell_error(tc->pool, cell);
पूर्ण

/*
 * FIXME: should we also commit due to size of transaction, measured in
 * metadata blocks?
 */
अटल पूर्णांक need_commit_due_to_समय(काष्ठा pool *pool)
अणु
	वापस !समय_in_range(jअगरfies, pool->last_commit_jअगरfies,
			      pool->last_commit_jअगरfies + COMMIT_PERIOD);
पूर्ण

#घोषणा thin_pbd(node) rb_entry((node), काष्ठा dm_thin_endio_hook, rb_node)
#घोषणा thin_bio(pbd) dm_bio_from_per_bio_data((pbd), माप(काष्ठा dm_thin_endio_hook))

अटल व्योम __thin_bio_rb_add(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	काष्ठा rb_node **rbp, *parent;
	काष्ठा dm_thin_endio_hook *pbd;
	sector_t bi_sector = bio->bi_iter.bi_sector;

	rbp = &tc->sort_bio_list.rb_node;
	parent = शून्य;
	जबतक (*rbp) अणु
		parent = *rbp;
		pbd = thin_pbd(parent);

		अगर (bi_sector < thin_bio(pbd)->bi_iter.bi_sector)
			rbp = &(*rbp)->rb_left;
		अन्यथा
			rbp = &(*rbp)->rb_right;
	पूर्ण

	pbd = dm_per_bio_data(bio, माप(काष्ठा dm_thin_endio_hook));
	rb_link_node(&pbd->rb_node, parent, rbp);
	rb_insert_color(&pbd->rb_node, &tc->sort_bio_list);
पूर्ण

अटल व्योम __extract_sorted_bios(काष्ठा thin_c *tc)
अणु
	काष्ठा rb_node *node;
	काष्ठा dm_thin_endio_hook *pbd;
	काष्ठा bio *bio;

	क्रम (node = rb_first(&tc->sort_bio_list); node; node = rb_next(node)) अणु
		pbd = thin_pbd(node);
		bio = thin_bio(pbd);

		bio_list_add(&tc->deferred_bio_list, bio);
		rb_erase(&pbd->rb_node, &tc->sort_bio_list);
	पूर्ण

	WARN_ON(!RB_EMPTY_ROOT(&tc->sort_bio_list));
पूर्ण

अटल व्योम __sort_thin_deferred_bios(काष्ठा thin_c *tc)
अणु
	काष्ठा bio *bio;
	काष्ठा bio_list bios;

	bio_list_init(&bios);
	bio_list_merge(&bios, &tc->deferred_bio_list);
	bio_list_init(&tc->deferred_bio_list);

	/* Sort deferred_bio_list using rb-tree */
	जबतक ((bio = bio_list_pop(&bios)))
		__thin_bio_rb_add(tc, bio);

	/*
	 * Transfer the sorted bios in sort_bio_list back to
	 * deferred_bio_list to allow lockless submission of
	 * all bios.
	 */
	__extract_sorted_bios(tc);
पूर्ण

अटल व्योम process_thin_deferred_bios(काष्ठा thin_c *tc)
अणु
	काष्ठा pool *pool = tc->pool;
	काष्ठा bio *bio;
	काष्ठा bio_list bios;
	काष्ठा blk_plug plug;
	अचिन्हित count = 0;

	अगर (tc->requeue_mode) अणु
		error_thin_bio_list(tc, &tc->deferred_bio_list,
				BLK_STS_DM_REQUEUE);
		वापस;
	पूर्ण

	bio_list_init(&bios);

	spin_lock_irq(&tc->lock);

	अगर (bio_list_empty(&tc->deferred_bio_list)) अणु
		spin_unlock_irq(&tc->lock);
		वापस;
	पूर्ण

	__sort_thin_deferred_bios(tc);

	bio_list_merge(&bios, &tc->deferred_bio_list);
	bio_list_init(&tc->deferred_bio_list);

	spin_unlock_irq(&tc->lock);

	blk_start_plug(&plug);
	जबतक ((bio = bio_list_pop(&bios))) अणु
		/*
		 * If we've got no मुक्त new_mapping काष्ठाs, and processing
		 * this bio might require one, we छोड़ो until there are some
		 * prepared mappings to process.
		 */
		अगर (ensure_next_mapping(pool)) अणु
			spin_lock_irq(&tc->lock);
			bio_list_add(&tc->deferred_bio_list, bio);
			bio_list_merge(&tc->deferred_bio_list, &bios);
			spin_unlock_irq(&tc->lock);
			अवरोध;
		पूर्ण

		अगर (bio_op(bio) == REQ_OP_DISCARD)
			pool->process_discard(tc, bio);
		अन्यथा
			pool->process_bio(tc, bio);

		अगर ((count++ & 127) == 0) अणु
			throttle_work_update(&pool->throttle);
			dm_pool_issue_prefetches(pool->pmd);
		पूर्ण
	पूर्ण
	blk_finish_plug(&plug);
पूर्ण

अटल पूर्णांक cmp_cells(स्थिर व्योम *lhs, स्थिर व्योम *rhs)
अणु
	काष्ठा dm_bio_prison_cell *lhs_cell = *((काष्ठा dm_bio_prison_cell **) lhs);
	काष्ठा dm_bio_prison_cell *rhs_cell = *((काष्ठा dm_bio_prison_cell **) rhs);

	BUG_ON(!lhs_cell->holder);
	BUG_ON(!rhs_cell->holder);

	अगर (lhs_cell->holder->bi_iter.bi_sector < rhs_cell->holder->bi_iter.bi_sector)
		वापस -1;

	अगर (lhs_cell->holder->bi_iter.bi_sector > rhs_cell->holder->bi_iter.bi_sector)
		वापस 1;

	वापस 0;
पूर्ण

अटल अचिन्हित sort_cells(काष्ठा pool *pool, काष्ठा list_head *cells)
अणु
	अचिन्हित count = 0;
	काष्ठा dm_bio_prison_cell *cell, *पंचांगp;

	list_क्रम_each_entry_safe(cell, पंचांगp, cells, user_list) अणु
		अगर (count >= CELL_SORT_ARRAY_SIZE)
			अवरोध;

		pool->cell_sort_array[count++] = cell;
		list_del(&cell->user_list);
	पूर्ण

	sort(pool->cell_sort_array, count, माप(cell), cmp_cells, शून्य);

	वापस count;
पूर्ण

अटल व्योम process_thin_deferred_cells(काष्ठा thin_c *tc)
अणु
	काष्ठा pool *pool = tc->pool;
	काष्ठा list_head cells;
	काष्ठा dm_bio_prison_cell *cell;
	अचिन्हित i, j, count;

	INIT_LIST_HEAD(&cells);

	spin_lock_irq(&tc->lock);
	list_splice_init(&tc->deferred_cells, &cells);
	spin_unlock_irq(&tc->lock);

	अगर (list_empty(&cells))
		वापस;

	करो अणु
		count = sort_cells(tc->pool, &cells);

		क्रम (i = 0; i < count; i++) अणु
			cell = pool->cell_sort_array[i];
			BUG_ON(!cell->holder);

			/*
			 * If we've got no मुक्त new_mapping काष्ठाs, and processing
			 * this bio might require one, we छोड़ो until there are some
			 * prepared mappings to process.
			 */
			अगर (ensure_next_mapping(pool)) अणु
				क्रम (j = i; j < count; j++)
					list_add(&pool->cell_sort_array[j]->user_list, &cells);

				spin_lock_irq(&tc->lock);
				list_splice(&cells, &tc->deferred_cells);
				spin_unlock_irq(&tc->lock);
				वापस;
			पूर्ण

			अगर (bio_op(cell->holder) == REQ_OP_DISCARD)
				pool->process_discard_cell(tc, cell);
			अन्यथा
				pool->process_cell(tc, cell);
		पूर्ण
	पूर्ण जबतक (!list_empty(&cells));
पूर्ण

अटल व्योम thin_get(काष्ठा thin_c *tc);
अटल व्योम thin_put(काष्ठा thin_c *tc);

/*
 * We can't hold rcu_पढ़ो_lock() around code that can block.  So we
 * find a thin with the rcu lock held; bump a refcount; then drop
 * the lock.
 */
अटल काष्ठा thin_c *get_first_thin(काष्ठा pool *pool)
अणु
	काष्ठा thin_c *tc = शून्य;

	rcu_पढ़ो_lock();
	अगर (!list_empty(&pool->active_thins)) अणु
		tc = list_entry_rcu(pool->active_thins.next, काष्ठा thin_c, list);
		thin_get(tc);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस tc;
पूर्ण

अटल काष्ठा thin_c *get_next_thin(काष्ठा pool *pool, काष्ठा thin_c *tc)
अणु
	काष्ठा thin_c *old_tc = tc;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_जारी_rcu(tc, &pool->active_thins, list) अणु
		thin_get(tc);
		thin_put(old_tc);
		rcu_पढ़ो_unlock();
		वापस tc;
	पूर्ण
	thin_put(old_tc);
	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

अटल व्योम process_deferred_bios(काष्ठा pool *pool)
अणु
	काष्ठा bio *bio;
	काष्ठा bio_list bios, bio_completions;
	काष्ठा thin_c *tc;

	tc = get_first_thin(pool);
	जबतक (tc) अणु
		process_thin_deferred_cells(tc);
		process_thin_deferred_bios(tc);
		tc = get_next_thin(pool, tc);
	पूर्ण

	/*
	 * If there are any deferred flush bios, we must commit the metadata
	 * beक्रमe issuing them or संकेतing their completion.
	 */
	bio_list_init(&bios);
	bio_list_init(&bio_completions);

	spin_lock_irq(&pool->lock);
	bio_list_merge(&bios, &pool->deferred_flush_bios);
	bio_list_init(&pool->deferred_flush_bios);

	bio_list_merge(&bio_completions, &pool->deferred_flush_completions);
	bio_list_init(&pool->deferred_flush_completions);
	spin_unlock_irq(&pool->lock);

	अगर (bio_list_empty(&bios) && bio_list_empty(&bio_completions) &&
	    !(dm_pool_changed_this_transaction(pool->pmd) && need_commit_due_to_समय(pool)))
		वापस;

	अगर (commit(pool)) अणु
		bio_list_merge(&bios, &bio_completions);

		जबतक ((bio = bio_list_pop(&bios)))
			bio_io_error(bio);
		वापस;
	पूर्ण
	pool->last_commit_jअगरfies = jअगरfies;

	जबतक ((bio = bio_list_pop(&bio_completions)))
		bio_endio(bio);

	जबतक ((bio = bio_list_pop(&bios))) अणु
		/*
		 * The data device was flushed as part of metadata commit,
		 * so complete redundant flushes immediately.
		 */
		अगर (bio->bi_opf & REQ_PREFLUSH)
			bio_endio(bio);
		अन्यथा
			submit_bio_noacct(bio);
	पूर्ण
पूर्ण

अटल व्योम करो_worker(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा pool *pool = container_of(ws, काष्ठा pool, worker);

	throttle_work_start(&pool->throttle);
	dm_pool_issue_prefetches(pool->pmd);
	throttle_work_update(&pool->throttle);
	process_prepared(pool, &pool->prepared_mappings, &pool->process_prepared_mapping);
	throttle_work_update(&pool->throttle);
	process_prepared(pool, &pool->prepared_discards, &pool->process_prepared_discard);
	throttle_work_update(&pool->throttle);
	process_prepared(pool, &pool->prepared_discards_pt2, &pool->process_prepared_discard_pt2);
	throttle_work_update(&pool->throttle);
	process_deferred_bios(pool);
	throttle_work_complete(&pool->throttle);
पूर्ण

/*
 * We want to commit periodically so that not too much
 * unwritten data builds up.
 */
अटल व्योम करो_waker(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा pool *pool = container_of(to_delayed_work(ws), काष्ठा pool, waker);
	wake_worker(pool);
	queue_delayed_work(pool->wq, &pool->waker, COMMIT_PERIOD);
पूर्ण

/*
 * We're holding onto IO to allow userland समय to react.  After the
 * समयout either the pool will have been resized (and thus back in
 * PM_WRITE mode), or we degrade to PM_OUT_OF_DATA_SPACE w/ error_अगर_no_space.
 */
अटल व्योम करो_no_space_समयout(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा pool *pool = container_of(to_delayed_work(ws), काष्ठा pool,
					 no_space_समयout);

	अगर (get_pool_mode(pool) == PM_OUT_OF_DATA_SPACE && !pool->pf.error_अगर_no_space) अणु
		pool->pf.error_अगर_no_space = true;
		notअगरy_of_pool_mode_change(pool);
		error_retry_list_with_code(pool, BLK_STS_NOSPC);
	पूर्ण
पूर्ण

/*----------------------------------------------------------------*/

काष्ठा pool_work अणु
	काष्ठा work_काष्ठा worker;
	काष्ठा completion complete;
पूर्ण;

अटल काष्ठा pool_work *to_pool_work(काष्ठा work_काष्ठा *ws)
अणु
	वापस container_of(ws, काष्ठा pool_work, worker);
पूर्ण

अटल व्योम pool_work_complete(काष्ठा pool_work *pw)
अणु
	complete(&pw->complete);
पूर्ण

अटल व्योम pool_work_रुको(काष्ठा pool_work *pw, काष्ठा pool *pool,
			   व्योम (*fn)(काष्ठा work_काष्ठा *))
अणु
	INIT_WORK_ONSTACK(&pw->worker, fn);
	init_completion(&pw->complete);
	queue_work(pool->wq, &pw->worker);
	रुको_क्रम_completion(&pw->complete);
पूर्ण

/*----------------------------------------------------------------*/

काष्ठा noflush_work अणु
	काष्ठा pool_work pw;
	काष्ठा thin_c *tc;
पूर्ण;

अटल काष्ठा noflush_work *to_noflush(काष्ठा work_काष्ठा *ws)
अणु
	वापस container_of(to_pool_work(ws), काष्ठा noflush_work, pw);
पूर्ण

अटल व्योम करो_noflush_start(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा noflush_work *w = to_noflush(ws);
	w->tc->requeue_mode = true;
	requeue_io(w->tc);
	pool_work_complete(&w->pw);
पूर्ण

अटल व्योम करो_noflush_stop(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा noflush_work *w = to_noflush(ws);
	w->tc->requeue_mode = false;
	pool_work_complete(&w->pw);
पूर्ण

अटल व्योम noflush_work(काष्ठा thin_c *tc, व्योम (*fn)(काष्ठा work_काष्ठा *))
अणु
	काष्ठा noflush_work w;

	w.tc = tc;
	pool_work_रुको(&w.pw, tc->pool, fn);
पूर्ण

/*----------------------------------------------------------------*/

अटल bool passकरोwn_enabled(काष्ठा pool_c *pt)
अणु
	वापस pt->adjusted_pf.discard_passकरोwn;
पूर्ण

अटल व्योम set_discard_callbacks(काष्ठा pool *pool)
अणु
	काष्ठा pool_c *pt = pool->ti->निजी;

	अगर (passकरोwn_enabled(pt)) अणु
		pool->process_discard_cell = process_discard_cell_passकरोwn;
		pool->process_prepared_discard = process_prepared_discard_passकरोwn_pt1;
		pool->process_prepared_discard_pt2 = process_prepared_discard_passकरोwn_pt2;
	पूर्ण अन्यथा अणु
		pool->process_discard_cell = process_discard_cell_no_passकरोwn;
		pool->process_prepared_discard = process_prepared_discard_no_passकरोwn;
	पूर्ण
पूर्ण

अटल व्योम set_pool_mode(काष्ठा pool *pool, क्रमागत pool_mode new_mode)
अणु
	काष्ठा pool_c *pt = pool->ti->निजी;
	bool needs_check = dm_pool_metadata_needs_check(pool->pmd);
	क्रमागत pool_mode old_mode = get_pool_mode(pool);
	अचिन्हित दीर्घ no_space_समयout = READ_ONCE(no_space_समयout_secs) * HZ;

	/*
	 * Never allow the pool to transition to PM_WRITE mode अगर user
	 * पूर्णांकervention is required to verअगरy metadata and data consistency.
	 */
	अगर (new_mode == PM_WRITE && needs_check) अणु
		DMERR("%s: unable to switch pool to write mode until repaired.",
		      dm_device_name(pool->pool_md));
		अगर (old_mode != new_mode)
			new_mode = old_mode;
		अन्यथा
			new_mode = PM_READ_ONLY;
	पूर्ण
	/*
	 * If we were in PM_FAIL mode, rollback of metadata failed.  We're
	 * not going to recover without a thin_repair.	So we never let the
	 * pool move out of the old mode.
	 */
	अगर (old_mode == PM_FAIL)
		new_mode = old_mode;

	चयन (new_mode) अणु
	हाल PM_FAIL:
		dm_pool_metadata_पढ़ो_only(pool->pmd);
		pool->process_bio = process_bio_fail;
		pool->process_discard = process_bio_fail;
		pool->process_cell = process_cell_fail;
		pool->process_discard_cell = process_cell_fail;
		pool->process_prepared_mapping = process_prepared_mapping_fail;
		pool->process_prepared_discard = process_prepared_discard_fail;

		error_retry_list(pool);
		अवरोध;

	हाल PM_OUT_OF_METADATA_SPACE:
	हाल PM_READ_ONLY:
		dm_pool_metadata_पढ़ो_only(pool->pmd);
		pool->process_bio = process_bio_पढ़ो_only;
		pool->process_discard = process_bio_success;
		pool->process_cell = process_cell_पढ़ो_only;
		pool->process_discard_cell = process_cell_success;
		pool->process_prepared_mapping = process_prepared_mapping_fail;
		pool->process_prepared_discard = process_prepared_discard_success;

		error_retry_list(pool);
		अवरोध;

	हाल PM_OUT_OF_DATA_SPACE:
		/*
		 * Ideally we'd never hit this state; the low water mark
		 * would trigger userland to extend the pool beक्रमe we
		 * completely run out of data space.  However, many small
		 * IOs to unprovisioned space can consume data space at an
		 * alarming rate.  Adjust your low water mark अगर you're
		 * frequently seeing this mode.
		 */
		pool->out_of_data_space = true;
		pool->process_bio = process_bio_पढ़ो_only;
		pool->process_discard = process_discard_bio;
		pool->process_cell = process_cell_पढ़ो_only;
		pool->process_prepared_mapping = process_prepared_mapping;
		set_discard_callbacks(pool);

		अगर (!pool->pf.error_अगर_no_space && no_space_समयout)
			queue_delayed_work(pool->wq, &pool->no_space_समयout, no_space_समयout);
		अवरोध;

	हाल PM_WRITE:
		अगर (old_mode == PM_OUT_OF_DATA_SPACE)
			cancel_delayed_work_sync(&pool->no_space_समयout);
		pool->out_of_data_space = false;
		pool->pf.error_अगर_no_space = pt->requested_pf.error_अगर_no_space;
		dm_pool_metadata_पढ़ो_ग_लिखो(pool->pmd);
		pool->process_bio = process_bio;
		pool->process_discard = process_discard_bio;
		pool->process_cell = process_cell;
		pool->process_prepared_mapping = process_prepared_mapping;
		set_discard_callbacks(pool);
		अवरोध;
	पूर्ण

	pool->pf.mode = new_mode;
	/*
	 * The pool mode may have changed, sync it so bind_control_target()
	 * करोesn't cause an unexpected mode transition on resume.
	 */
	pt->adjusted_pf.mode = new_mode;

	अगर (old_mode != new_mode)
		notअगरy_of_pool_mode_change(pool);
पूर्ण

अटल व्योम पात_transaction(काष्ठा pool *pool)
अणु
	स्थिर अक्षर *dev_name = dm_device_name(pool->pool_md);

	DMERR_LIMIT("%s: aborting current metadata transaction", dev_name);
	अगर (dm_pool_पात_metadata(pool->pmd)) अणु
		DMERR("%s: failed to abort metadata transaction", dev_name);
		set_pool_mode(pool, PM_FAIL);
	पूर्ण

	अगर (dm_pool_metadata_set_needs_check(pool->pmd)) अणु
		DMERR("%s: failed to set 'needs_check' flag in metadata", dev_name);
		set_pool_mode(pool, PM_FAIL);
	पूर्ण
पूर्ण

अटल व्योम metadata_operation_failed(काष्ठा pool *pool, स्थिर अक्षर *op, पूर्णांक r)
अणु
	DMERR_LIMIT("%s: metadata operation '%s' failed: error = %d",
		    dm_device_name(pool->pool_md), op, r);

	पात_transaction(pool);
	set_pool_mode(pool, PM_READ_ONLY);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Mapping functions.
 */

/*
 * Called only जबतक mapping a thin bio to hand it over to the workqueue.
 */
अटल व्योम thin_defer_bio(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	काष्ठा pool *pool = tc->pool;

	spin_lock_irq(&tc->lock);
	bio_list_add(&tc->deferred_bio_list, bio);
	spin_unlock_irq(&tc->lock);

	wake_worker(pool);
पूर्ण

अटल व्योम thin_defer_bio_with_throttle(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	काष्ठा pool *pool = tc->pool;

	throttle_lock(&pool->throttle);
	thin_defer_bio(tc, bio);
	throttle_unlock(&pool->throttle);
पूर्ण

अटल व्योम thin_defer_cell(काष्ठा thin_c *tc, काष्ठा dm_bio_prison_cell *cell)
अणु
	काष्ठा pool *pool = tc->pool;

	throttle_lock(&pool->throttle);
	spin_lock_irq(&tc->lock);
	list_add_tail(&cell->user_list, &tc->deferred_cells);
	spin_unlock_irq(&tc->lock);
	throttle_unlock(&pool->throttle);

	wake_worker(pool);
पूर्ण

अटल व्योम thin_hook_bio(काष्ठा thin_c *tc, काष्ठा bio *bio)
अणु
	काष्ठा dm_thin_endio_hook *h = dm_per_bio_data(bio, माप(काष्ठा dm_thin_endio_hook));

	h->tc = tc;
	h->shared_पढ़ो_entry = शून्य;
	h->all_io_entry = शून्य;
	h->overग_लिखो_mapping = शून्य;
	h->cell = शून्य;
पूर्ण

/*
 * Non-blocking function called from the thin target's map function.
 */
अटल पूर्णांक thin_bio_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	पूर्णांक r;
	काष्ठा thin_c *tc = ti->निजी;
	dm_block_t block = get_bio_block(tc, bio);
	काष्ठा dm_thin_device *td = tc->td;
	काष्ठा dm_thin_lookup_result result;
	काष्ठा dm_bio_prison_cell *virt_cell, *data_cell;
	काष्ठा dm_cell_key key;

	thin_hook_bio(tc, bio);

	अगर (tc->requeue_mode) अणु
		bio->bi_status = BLK_STS_DM_REQUEUE;
		bio_endio(bio);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	अगर (get_pool_mode(tc->pool) == PM_FAIL) अणु
		bio_io_error(bio);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	अगर (op_is_flush(bio->bi_opf) || bio_op(bio) == REQ_OP_DISCARD) अणु
		thin_defer_bio_with_throttle(tc, bio);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	/*
	 * We must hold the भव cell beक्रमe करोing the lookup, otherwise
	 * there's a race with discard.
	 */
	build_भव_key(tc->td, block, &key);
	अगर (bio_detain(tc->pool, &key, bio, &virt_cell))
		वापस DM_MAPIO_SUBMITTED;

	r = dm_thin_find_block(td, block, 0, &result);

	/*
	 * Note that we defer पढ़ोahead too.
	 */
	चयन (r) अणु
	हाल 0:
		अगर (unlikely(result.shared)) अणु
			/*
			 * We have a race condition here between the
			 * result.shared value वापसed by the lookup and
			 * snapshot creation, which may cause new
			 * sharing.
			 *
			 * To aव्योम this always quiesce the origin beक्रमe
			 * taking the snap.  You want to करो this anyway to
			 * ensure a consistent application view
			 * (i.e. lockfs).
			 *
			 * More distant ancestors are irrelevant. The
			 * shared flag will be set in their हाल.
			 */
			thin_defer_cell(tc, virt_cell);
			वापस DM_MAPIO_SUBMITTED;
		पूर्ण

		build_data_key(tc->td, result.block, &key);
		अगर (bio_detain(tc->pool, &key, bio, &data_cell)) अणु
			cell_defer_no_holder(tc, virt_cell);
			वापस DM_MAPIO_SUBMITTED;
		पूर्ण

		inc_all_io_entry(tc->pool, bio);
		cell_defer_no_holder(tc, data_cell);
		cell_defer_no_holder(tc, virt_cell);

		remap(tc, bio, result.block);
		वापस DM_MAPIO_REMAPPED;

	हाल -ENODATA:
	हाल -EWOULDBLOCK:
		thin_defer_cell(tc, virt_cell);
		वापस DM_MAPIO_SUBMITTED;

	शेष:
		/*
		 * Must always call bio_io_error on failure.
		 * dm_thin_find_block can fail with -EINVAL अगर the
		 * pool is चयनed to fail-io mode.
		 */
		bio_io_error(bio);
		cell_defer_no_holder(tc, virt_cell);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण
पूर्ण

अटल व्योम requeue_bios(काष्ठा pool *pool)
अणु
	काष्ठा thin_c *tc;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(tc, &pool->active_thins, list) अणु
		spin_lock_irq(&tc->lock);
		bio_list_merge(&tc->deferred_bio_list, &tc->retry_on_resume_list);
		bio_list_init(&tc->retry_on_resume_list);
		spin_unlock_irq(&tc->lock);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/*----------------------------------------------------------------
 * Binding of control tarमाला_लो to a pool object
 *--------------------------------------------------------------*/
अटल bool data_dev_supports_discard(काष्ठा pool_c *pt)
अणु
	काष्ठा request_queue *q = bdev_get_queue(pt->data_dev->bdev);

	वापस blk_queue_discard(q);
पूर्ण

अटल bool is_factor(sector_t block_size, uपूर्णांक32_t n)
अणु
	वापस !sector_भाग(block_size, n);
पूर्ण

/*
 * If discard_passकरोwn was enabled verअगरy that the data device
 * supports discards.  Disable discard_passकरोwn अगर not.
 */
अटल व्योम disable_passकरोwn_अगर_not_supported(काष्ठा pool_c *pt)
अणु
	काष्ठा pool *pool = pt->pool;
	काष्ठा block_device *data_bdev = pt->data_dev->bdev;
	काष्ठा queue_limits *data_limits = &bdev_get_queue(data_bdev)->limits;
	स्थिर अक्षर *reason = शून्य;
	अक्षर buf[BDEVNAME_SIZE];

	अगर (!pt->adjusted_pf.discard_passकरोwn)
		वापस;

	अगर (!data_dev_supports_discard(pt))
		reason = "discard unsupported";

	अन्यथा अगर (data_limits->max_discard_sectors < pool->sectors_per_block)
		reason = "max discard sectors smaller than a block";

	अगर (reason) अणु
		DMWARN("Data device (%s) %s: Disabling discard passdown.", bdevname(data_bdev, buf), reason);
		pt->adjusted_pf.discard_passकरोwn = false;
	पूर्ण
पूर्ण

अटल पूर्णांक bind_control_target(काष्ठा pool *pool, काष्ठा dm_target *ti)
अणु
	काष्ठा pool_c *pt = ti->निजी;

	/*
	 * We want to make sure that a pool in PM_FAIL mode is never upgraded.
	 */
	क्रमागत pool_mode old_mode = get_pool_mode(pool);
	क्रमागत pool_mode new_mode = pt->adjusted_pf.mode;

	/*
	 * Don't change the pool's mode until set_pool_mode() below.
	 * Otherwise the pool's process_* function poपूर्णांकers may
	 * not match the desired pool mode.
	 */
	pt->adjusted_pf.mode = old_mode;

	pool->ti = ti;
	pool->pf = pt->adjusted_pf;
	pool->low_water_blocks = pt->low_water_blocks;

	set_pool_mode(pool, new_mode);

	वापस 0;
पूर्ण

अटल व्योम unbind_control_target(काष्ठा pool *pool, काष्ठा dm_target *ti)
अणु
	अगर (pool->ti == ti)
		pool->ti = शून्य;
पूर्ण

/*----------------------------------------------------------------
 * Pool creation
 *--------------------------------------------------------------*/
/* Initialize pool features. */
अटल व्योम pool_features_init(काष्ठा pool_features *pf)
अणु
	pf->mode = PM_WRITE;
	pf->zero_new_blocks = true;
	pf->discard_enabled = true;
	pf->discard_passकरोwn = true;
	pf->error_अगर_no_space = false;
पूर्ण

अटल व्योम __pool_destroy(काष्ठा pool *pool)
अणु
	__pool_table_हटाओ(pool);

	vमुक्त(pool->cell_sort_array);
	अगर (dm_pool_metadata_बंद(pool->pmd) < 0)
		DMWARN("%s: dm_pool_metadata_close() failed.", __func__);

	dm_bio_prison_destroy(pool->prison);
	dm_kcopyd_client_destroy(pool->copier);

	अगर (pool->wq)
		destroy_workqueue(pool->wq);

	अगर (pool->next_mapping)
		mempool_मुक्त(pool->next_mapping, &pool->mapping_pool);
	mempool_निकास(&pool->mapping_pool);
	bio_uninit(&pool->flush_bio);
	dm_deferred_set_destroy(pool->shared_पढ़ो_ds);
	dm_deferred_set_destroy(pool->all_io_ds);
	kमुक्त(pool);
पूर्ण

अटल काष्ठा kmem_cache *_new_mapping_cache;

अटल काष्ठा pool *pool_create(काष्ठा mapped_device *pool_md,
				काष्ठा block_device *metadata_dev,
				काष्ठा block_device *data_dev,
				अचिन्हित दीर्घ block_size,
				पूर्णांक पढ़ो_only, अक्षर **error)
अणु
	पूर्णांक r;
	व्योम *err_p;
	काष्ठा pool *pool;
	काष्ठा dm_pool_metadata *pmd;
	bool क्रमmat_device = पढ़ो_only ? false : true;

	pmd = dm_pool_metadata_खोलो(metadata_dev, block_size, क्रमmat_device);
	अगर (IS_ERR(pmd)) अणु
		*error = "Error creating metadata object";
		वापस (काष्ठा pool *)pmd;
	पूर्ण

	pool = kzalloc(माप(*pool), GFP_KERNEL);
	अगर (!pool) अणु
		*error = "Error allocating memory for pool";
		err_p = ERR_PTR(-ENOMEM);
		जाओ bad_pool;
	पूर्ण

	pool->pmd = pmd;
	pool->sectors_per_block = block_size;
	अगर (block_size & (block_size - 1))
		pool->sectors_per_block_shअगरt = -1;
	अन्यथा
		pool->sectors_per_block_shअगरt = __ffs(block_size);
	pool->low_water_blocks = 0;
	pool_features_init(&pool->pf);
	pool->prison = dm_bio_prison_create();
	अगर (!pool->prison) अणु
		*error = "Error creating pool's bio prison";
		err_p = ERR_PTR(-ENOMEM);
		जाओ bad_prison;
	पूर्ण

	pool->copier = dm_kcopyd_client_create(&dm_kcopyd_throttle);
	अगर (IS_ERR(pool->copier)) अणु
		r = PTR_ERR(pool->copier);
		*error = "Error creating pool's kcopyd client";
		err_p = ERR_PTR(r);
		जाओ bad_kcopyd_client;
	पूर्ण

	/*
	 * Create singlethपढ़ोed workqueue that will service all devices
	 * that use this metadata.
	 */
	pool->wq = alloc_ordered_workqueue("dm-" DM_MSG_PREFIX, WQ_MEM_RECLAIM);
	अगर (!pool->wq) अणु
		*error = "Error creating pool's workqueue";
		err_p = ERR_PTR(-ENOMEM);
		जाओ bad_wq;
	पूर्ण

	throttle_init(&pool->throttle);
	INIT_WORK(&pool->worker, करो_worker);
	INIT_DELAYED_WORK(&pool->waker, करो_waker);
	INIT_DELAYED_WORK(&pool->no_space_समयout, करो_no_space_समयout);
	spin_lock_init(&pool->lock);
	bio_list_init(&pool->deferred_flush_bios);
	bio_list_init(&pool->deferred_flush_completions);
	INIT_LIST_HEAD(&pool->prepared_mappings);
	INIT_LIST_HEAD(&pool->prepared_discards);
	INIT_LIST_HEAD(&pool->prepared_discards_pt2);
	INIT_LIST_HEAD(&pool->active_thins);
	pool->low_water_triggered = false;
	pool->suspended = true;
	pool->out_of_data_space = false;
	bio_init(&pool->flush_bio, शून्य, 0);

	pool->shared_पढ़ो_ds = dm_deferred_set_create();
	अगर (!pool->shared_पढ़ो_ds) अणु
		*error = "Error creating pool's shared read deferred set";
		err_p = ERR_PTR(-ENOMEM);
		जाओ bad_shared_पढ़ो_ds;
	पूर्ण

	pool->all_io_ds = dm_deferred_set_create();
	अगर (!pool->all_io_ds) अणु
		*error = "Error creating pool's all io deferred set";
		err_p = ERR_PTR(-ENOMEM);
		जाओ bad_all_io_ds;
	पूर्ण

	pool->next_mapping = शून्य;
	r = mempool_init_slab_pool(&pool->mapping_pool, MAPPING_POOL_SIZE,
				   _new_mapping_cache);
	अगर (r) अणु
		*error = "Error creating pool's mapping mempool";
		err_p = ERR_PTR(r);
		जाओ bad_mapping_pool;
	पूर्ण

	pool->cell_sort_array =
		vदो_स्मृति(array_size(CELL_SORT_ARRAY_SIZE,
				   माप(*pool->cell_sort_array)));
	अगर (!pool->cell_sort_array) अणु
		*error = "Error allocating cell sort array";
		err_p = ERR_PTR(-ENOMEM);
		जाओ bad_sort_array;
	पूर्ण

	pool->ref_count = 1;
	pool->last_commit_jअगरfies = jअगरfies;
	pool->pool_md = pool_md;
	pool->md_dev = metadata_dev;
	pool->data_dev = data_dev;
	__pool_table_insert(pool);

	वापस pool;

bad_sort_array:
	mempool_निकास(&pool->mapping_pool);
bad_mapping_pool:
	dm_deferred_set_destroy(pool->all_io_ds);
bad_all_io_ds:
	dm_deferred_set_destroy(pool->shared_पढ़ो_ds);
bad_shared_पढ़ो_ds:
	destroy_workqueue(pool->wq);
bad_wq:
	dm_kcopyd_client_destroy(pool->copier);
bad_kcopyd_client:
	dm_bio_prison_destroy(pool->prison);
bad_prison:
	kमुक्त(pool);
bad_pool:
	अगर (dm_pool_metadata_बंद(pmd))
		DMWARN("%s: dm_pool_metadata_close() failed.", __func__);

	वापस err_p;
पूर्ण

अटल व्योम __pool_inc(काष्ठा pool *pool)
अणु
	BUG_ON(!mutex_is_locked(&dm_thin_pool_table.mutex));
	pool->ref_count++;
पूर्ण

अटल व्योम __pool_dec(काष्ठा pool *pool)
अणु
	BUG_ON(!mutex_is_locked(&dm_thin_pool_table.mutex));
	BUG_ON(!pool->ref_count);
	अगर (!--pool->ref_count)
		__pool_destroy(pool);
पूर्ण

अटल काष्ठा pool *__pool_find(काष्ठा mapped_device *pool_md,
				काष्ठा block_device *metadata_dev,
				काष्ठा block_device *data_dev,
				अचिन्हित दीर्घ block_size, पूर्णांक पढ़ो_only,
				अक्षर **error, पूर्णांक *created)
अणु
	काष्ठा pool *pool = __pool_table_lookup_metadata_dev(metadata_dev);

	अगर (pool) अणु
		अगर (pool->pool_md != pool_md) अणु
			*error = "metadata device already in use by a pool";
			वापस ERR_PTR(-EBUSY);
		पूर्ण
		अगर (pool->data_dev != data_dev) अणु
			*error = "data device already in use by a pool";
			वापस ERR_PTR(-EBUSY);
		पूर्ण
		__pool_inc(pool);

	पूर्ण अन्यथा अणु
		pool = __pool_table_lookup(pool_md);
		अगर (pool) अणु
			अगर (pool->md_dev != metadata_dev || pool->data_dev != data_dev) अणु
				*error = "different pool cannot replace a pool";
				वापस ERR_PTR(-EINVAL);
			पूर्ण
			__pool_inc(pool);

		पूर्ण अन्यथा अणु
			pool = pool_create(pool_md, metadata_dev, data_dev, block_size, पढ़ो_only, error);
			*created = 1;
		पूर्ण
	पूर्ण

	वापस pool;
पूर्ण

/*----------------------------------------------------------------
 * Pool target methods
 *--------------------------------------------------------------*/
अटल व्योम pool_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा pool_c *pt = ti->निजी;

	mutex_lock(&dm_thin_pool_table.mutex);

	unbind_control_target(pt->pool, ti);
	__pool_dec(pt->pool);
	dm_put_device(ti, pt->metadata_dev);
	dm_put_device(ti, pt->data_dev);
	kमुक्त(pt);

	mutex_unlock(&dm_thin_pool_table.mutex);
पूर्ण

अटल पूर्णांक parse_pool_features(काष्ठा dm_arg_set *as, काष्ठा pool_features *pf,
			       काष्ठा dm_target *ti)
अणु
	पूर्णांक r;
	अचिन्हित argc;
	स्थिर अक्षर *arg_name;

	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, 4, "Invalid number of pool feature arguments"पूर्ण,
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

		अगर (!strहालcmp(arg_name, "skip_block_zeroing"))
			pf->zero_new_blocks = false;

		अन्यथा अगर (!strहालcmp(arg_name, "ignore_discard"))
			pf->discard_enabled = false;

		अन्यथा अगर (!strहालcmp(arg_name, "no_discard_passdown"))
			pf->discard_passकरोwn = false;

		अन्यथा अगर (!strहालcmp(arg_name, "read_only"))
			pf->mode = PM_READ_ONLY;

		अन्यथा अगर (!strहालcmp(arg_name, "error_if_no_space"))
			pf->error_अगर_no_space = true;

		अन्यथा अणु
			ti->error = "Unrecognised pool feature requested";
			r = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम metadata_low_callback(व्योम *context)
अणु
	काष्ठा pool *pool = context;

	DMWARN("%s: reached low water mark for metadata device: sending event.",
	       dm_device_name(pool->pool_md));

	dm_table_event(pool->ti->table);
पूर्ण

/*
 * We need to flush the data device **beक्रमe** committing the metadata.
 *
 * This ensures that the data blocks of any newly inserted mappings are
 * properly written to non-अस्थिर storage and won't be lost in हाल of a
 * crash.
 *
 * Failure to करो so can result in data corruption in the हाल of पूर्णांकernal or
 * बाह्यal snapshots and in the हाल of newly provisioned blocks, when block
 * zeroing is enabled.
 */
अटल पूर्णांक metadata_pre_commit_callback(व्योम *context)
अणु
	काष्ठा pool *pool = context;
	काष्ठा bio *flush_bio = &pool->flush_bio;

	bio_reset(flush_bio);
	bio_set_dev(flush_bio, pool->data_dev);
	flush_bio->bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;

	वापस submit_bio_रुको(flush_bio);
पूर्ण

अटल sector_t get_dev_size(काष्ठा block_device *bdev)
अणु
	वापस i_size_पढ़ो(bdev->bd_inode) >> SECTOR_SHIFT;
पूर्ण

अटल व्योम warn_अगर_metadata_device_too_big(काष्ठा block_device *bdev)
अणु
	sector_t metadata_dev_size = get_dev_size(bdev);
	अक्षर buffer[BDEVNAME_SIZE];

	अगर (metadata_dev_size > THIN_METADATA_MAX_SECTORS_WARNING)
		DMWARN("Metadata device %s is larger than %u sectors: excess space will not be used.",
		       bdevname(bdev, buffer), THIN_METADATA_MAX_SECTORS);
पूर्ण

अटल sector_t get_metadata_dev_size(काष्ठा block_device *bdev)
अणु
	sector_t metadata_dev_size = get_dev_size(bdev);

	अगर (metadata_dev_size > THIN_METADATA_MAX_SECTORS)
		metadata_dev_size = THIN_METADATA_MAX_SECTORS;

	वापस metadata_dev_size;
पूर्ण

अटल dm_block_t get_metadata_dev_size_in_blocks(काष्ठा block_device *bdev)
अणु
	sector_t metadata_dev_size = get_metadata_dev_size(bdev);

	sector_भाग(metadata_dev_size, THIN_METADATA_BLOCK_SIZE);

	वापस metadata_dev_size;
पूर्ण

/*
 * When a metadata threshold is crossed a dm event is triggered, and
 * userland should respond by growing the metadata device.  We could let
 * userland set the threshold, like we करो with the data threshold, but I'm
 * not sure they know enough to करो this well.
 */
अटल dm_block_t calc_metadata_threshold(काष्ठा pool_c *pt)
अणु
	/*
	 * 4M is ample क्रम all ops with the possible exception of thin
	 * device deletion which is harmless अगर it fails (just retry the
	 * delete after you've grown the device).
	 */
	dm_block_t quarter = get_metadata_dev_size_in_blocks(pt->metadata_dev->bdev) / 4;
	वापस min((dm_block_t)1024ULL /* 4M */, quarter);
पूर्ण

/*
 * thin-pool <metadata dev> <data dev>
 *	     <data block size (sectors)>
 *	     <low water mark (blocks)>
 *	     [<#feature args> [<arg>]*]
 *
 * Optional feature arguments are:
 *	     skip_block_zeroing: skips the zeroing of newly-provisioned blocks.
 *	     ignore_discard: disable discard
 *	     no_discard_passकरोwn: करोn't pass discards करोwn to the data device
 *	     पढ़ो_only: Don't allow any changes to be made to the pool metadata.
 *	     error_अगर_no_space: error IOs, instead of queueing, अगर no space.
 */
अटल पूर्णांक pool_ctr(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv)
अणु
	पूर्णांक r, pool_created = 0;
	काष्ठा pool_c *pt;
	काष्ठा pool *pool;
	काष्ठा pool_features pf;
	काष्ठा dm_arg_set as;
	काष्ठा dm_dev *data_dev;
	अचिन्हित दीर्घ block_size;
	dm_block_t low_water_blocks;
	काष्ठा dm_dev *metadata_dev;
	भ_शेषe_t metadata_mode;

	/*
	 * FIXME Remove validation from scope of lock.
	 */
	mutex_lock(&dm_thin_pool_table.mutex);

	अगर (argc < 4) अणु
		ti->error = "Invalid argument count";
		r = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	as.argc = argc;
	as.argv = argv;

	/* make sure metadata and data are dअगरferent devices */
	अगर (!म_भेद(argv[0], argv[1])) अणु
		ti->error = "Error setting metadata or data device";
		r = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/*
	 * Set शेष pool features.
	 */
	pool_features_init(&pf);

	dm_consume_args(&as, 4);
	r = parse_pool_features(&as, &pf, ti);
	अगर (r)
		जाओ out_unlock;

	metadata_mode = FMODE_READ | ((pf.mode == PM_READ_ONLY) ? 0 : FMODE_WRITE);
	r = dm_get_device(ti, argv[0], metadata_mode, &metadata_dev);
	अगर (r) अणु
		ti->error = "Error opening metadata block device";
		जाओ out_unlock;
	पूर्ण
	warn_अगर_metadata_device_too_big(metadata_dev->bdev);

	r = dm_get_device(ti, argv[1], FMODE_READ | FMODE_WRITE, &data_dev);
	अगर (r) अणु
		ti->error = "Error getting data device";
		जाओ out_metadata;
	पूर्ण

	अगर (kम_से_अदीर्घ(argv[2], 10, &block_size) || !block_size ||
	    block_size < DATA_DEV_BLOCK_SIZE_MIN_SECTORS ||
	    block_size > DATA_DEV_BLOCK_SIZE_MAX_SECTORS ||
	    block_size & (DATA_DEV_BLOCK_SIZE_MIN_SECTORS - 1)) अणु
		ti->error = "Invalid block size";
		r = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (kम_से_अदीर्घl(argv[3], 10, (अचिन्हित दीर्घ दीर्घ *)&low_water_blocks)) अणु
		ti->error = "Invalid low water mark";
		r = -EINVAL;
		जाओ out;
	पूर्ण

	pt = kzalloc(माप(*pt), GFP_KERNEL);
	अगर (!pt) अणु
		r = -ENOMEM;
		जाओ out;
	पूर्ण

	pool = __pool_find(dm_table_get_md(ti->table), metadata_dev->bdev, data_dev->bdev,
			   block_size, pf.mode == PM_READ_ONLY, &ti->error, &pool_created);
	अगर (IS_ERR(pool)) अणु
		r = PTR_ERR(pool);
		जाओ out_मुक्त_pt;
	पूर्ण

	/*
	 * 'pool_created' reflects whether this is the first table load.
	 * Top level discard support is not allowed to be changed after
	 * initial load.  This would require a pool reload to trigger thin
	 * device changes.
	 */
	अगर (!pool_created && pf.discard_enabled != pool->pf.discard_enabled) अणु
		ti->error = "Discard support cannot be disabled once enabled";
		r = -EINVAL;
		जाओ out_flags_changed;
	पूर्ण

	pt->pool = pool;
	pt->ti = ti;
	pt->metadata_dev = metadata_dev;
	pt->data_dev = data_dev;
	pt->low_water_blocks = low_water_blocks;
	pt->adjusted_pf = pt->requested_pf = pf;
	ti->num_flush_bios = 1;

	/*
	 * Only need to enable discards अगर the pool should pass
	 * them करोwn to the data device.  The thin device's discard
	 * processing will cause mappings to be हटाओd from the btree.
	 */
	अगर (pf.discard_enabled && pf.discard_passकरोwn) अणु
		ti->num_discard_bios = 1;

		/*
		 * Setting 'discards_supported' circumvents the normal
		 * stacking of discard limits (this keeps the pool and
		 * thin devices' discard limits consistent).
		 */
		ti->discards_supported = true;
	पूर्ण
	ti->निजी = pt;

	r = dm_pool_रेजिस्टर_metadata_threshold(pt->pool->pmd,
						calc_metadata_threshold(pt),
						metadata_low_callback,
						pool);
	अगर (r)
		जाओ out_flags_changed;

	dm_pool_रेजिस्टर_pre_commit_callback(pool->pmd,
					     metadata_pre_commit_callback, pool);

	mutex_unlock(&dm_thin_pool_table.mutex);

	वापस 0;

out_flags_changed:
	__pool_dec(pool);
out_मुक्त_pt:
	kमुक्त(pt);
out:
	dm_put_device(ti, data_dev);
out_metadata:
	dm_put_device(ti, metadata_dev);
out_unlock:
	mutex_unlock(&dm_thin_pool_table.mutex);

	वापस r;
पूर्ण

अटल पूर्णांक pool_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	पूर्णांक r;
	काष्ठा pool_c *pt = ti->निजी;
	काष्ठा pool *pool = pt->pool;

	/*
	 * As this is a singleton target, ti->begin is always zero.
	 */
	spin_lock_irq(&pool->lock);
	bio_set_dev(bio, pt->data_dev->bdev);
	r = DM_MAPIO_REMAPPED;
	spin_unlock_irq(&pool->lock);

	वापस r;
पूर्ण

अटल पूर्णांक maybe_resize_data_dev(काष्ठा dm_target *ti, bool *need_commit)
अणु
	पूर्णांक r;
	काष्ठा pool_c *pt = ti->निजी;
	काष्ठा pool *pool = pt->pool;
	sector_t data_size = ti->len;
	dm_block_t sb_data_size;

	*need_commit = false;

	(व्योम) sector_भाग(data_size, pool->sectors_per_block);

	r = dm_pool_get_data_dev_size(pool->pmd, &sb_data_size);
	अगर (r) अणु
		DMERR("%s: failed to retrieve data device size",
		      dm_device_name(pool->pool_md));
		वापस r;
	पूर्ण

	अगर (data_size < sb_data_size) अणु
		DMERR("%s: pool target (%llu blocks) too small: expected %llu",
		      dm_device_name(pool->pool_md),
		      (अचिन्हित दीर्घ दीर्घ)data_size, sb_data_size);
		वापस -EINVAL;

	पूर्ण अन्यथा अगर (data_size > sb_data_size) अणु
		अगर (dm_pool_metadata_needs_check(pool->pmd)) अणु
			DMERR("%s: unable to grow the data device until repaired.",
			      dm_device_name(pool->pool_md));
			वापस 0;
		पूर्ण

		अगर (sb_data_size)
			DMINFO("%s: growing the data device from %llu to %llu blocks",
			       dm_device_name(pool->pool_md),
			       sb_data_size, (अचिन्हित दीर्घ दीर्घ)data_size);
		r = dm_pool_resize_data_dev(pool->pmd, data_size);
		अगर (r) अणु
			metadata_operation_failed(pool, "dm_pool_resize_data_dev", r);
			वापस r;
		पूर्ण

		*need_commit = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक maybe_resize_metadata_dev(काष्ठा dm_target *ti, bool *need_commit)
अणु
	पूर्णांक r;
	काष्ठा pool_c *pt = ti->निजी;
	काष्ठा pool *pool = pt->pool;
	dm_block_t metadata_dev_size, sb_metadata_dev_size;

	*need_commit = false;

	metadata_dev_size = get_metadata_dev_size_in_blocks(pool->md_dev);

	r = dm_pool_get_metadata_dev_size(pool->pmd, &sb_metadata_dev_size);
	अगर (r) अणु
		DMERR("%s: failed to retrieve metadata device size",
		      dm_device_name(pool->pool_md));
		वापस r;
	पूर्ण

	अगर (metadata_dev_size < sb_metadata_dev_size) अणु
		DMERR("%s: metadata device (%llu blocks) too small: expected %llu",
		      dm_device_name(pool->pool_md),
		      metadata_dev_size, sb_metadata_dev_size);
		वापस -EINVAL;

	पूर्ण अन्यथा अगर (metadata_dev_size > sb_metadata_dev_size) अणु
		अगर (dm_pool_metadata_needs_check(pool->pmd)) अणु
			DMERR("%s: unable to grow the metadata device until repaired.",
			      dm_device_name(pool->pool_md));
			वापस 0;
		पूर्ण

		warn_अगर_metadata_device_too_big(pool->md_dev);
		DMINFO("%s: growing the metadata device from %llu to %llu blocks",
		       dm_device_name(pool->pool_md),
		       sb_metadata_dev_size, metadata_dev_size);

		अगर (get_pool_mode(pool) == PM_OUT_OF_METADATA_SPACE)
			set_pool_mode(pool, PM_WRITE);

		r = dm_pool_resize_metadata_dev(pool->pmd, metadata_dev_size);
		अगर (r) अणु
			metadata_operation_failed(pool, "dm_pool_resize_metadata_dev", r);
			वापस r;
		पूर्ण

		*need_commit = true;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Retrieves the number of blocks of the data device from
 * the superblock and compares it to the actual device size,
 * thus resizing the data device in हाल it has grown.
 *
 * This both copes with खोलोing pपुनः_स्मृतिated data devices in the ctr
 * being followed by a resume
 * -and-
 * calling the resume method inभागidually after userspace has
 * grown the data device in reaction to a table event.
 */
अटल पूर्णांक pool_preresume(काष्ठा dm_target *ti)
अणु
	पूर्णांक r;
	bool need_commit1, need_commit2;
	काष्ठा pool_c *pt = ti->निजी;
	काष्ठा pool *pool = pt->pool;

	/*
	 * Take control of the pool object.
	 */
	r = bind_control_target(pool, ti);
	अगर (r)
		वापस r;

	r = maybe_resize_data_dev(ti, &need_commit1);
	अगर (r)
		वापस r;

	r = maybe_resize_metadata_dev(ti, &need_commit2);
	अगर (r)
		वापस r;

	अगर (need_commit1 || need_commit2)
		(व्योम) commit(pool);

	वापस 0;
पूर्ण

अटल व्योम pool_suspend_active_thins(काष्ठा pool *pool)
अणु
	काष्ठा thin_c *tc;

	/* Suspend all active thin devices */
	tc = get_first_thin(pool);
	जबतक (tc) अणु
		dm_पूर्णांकernal_suspend_noflush(tc->thin_md);
		tc = get_next_thin(pool, tc);
	पूर्ण
पूर्ण

अटल व्योम pool_resume_active_thins(काष्ठा pool *pool)
अणु
	काष्ठा thin_c *tc;

	/* Resume all active thin devices */
	tc = get_first_thin(pool);
	जबतक (tc) अणु
		dm_पूर्णांकernal_resume(tc->thin_md);
		tc = get_next_thin(pool, tc);
	पूर्ण
पूर्ण

अटल व्योम pool_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा pool_c *pt = ti->निजी;
	काष्ठा pool *pool = pt->pool;

	/*
	 * Must requeue active_thins' bios and then resume
	 * active_thins _beक्रमe_ clearing 'suspend' flag.
	 */
	requeue_bios(pool);
	pool_resume_active_thins(pool);

	spin_lock_irq(&pool->lock);
	pool->low_water_triggered = false;
	pool->suspended = false;
	spin_unlock_irq(&pool->lock);

	करो_waker(&pool->waker.work);
पूर्ण

अटल व्योम pool_presuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा pool_c *pt = ti->निजी;
	काष्ठा pool *pool = pt->pool;

	spin_lock_irq(&pool->lock);
	pool->suspended = true;
	spin_unlock_irq(&pool->lock);

	pool_suspend_active_thins(pool);
पूर्ण

अटल व्योम pool_presuspend_unकरो(काष्ठा dm_target *ti)
अणु
	काष्ठा pool_c *pt = ti->निजी;
	काष्ठा pool *pool = pt->pool;

	pool_resume_active_thins(pool);

	spin_lock_irq(&pool->lock);
	pool->suspended = false;
	spin_unlock_irq(&pool->lock);
पूर्ण

अटल व्योम pool_postsuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा pool_c *pt = ti->निजी;
	काष्ठा pool *pool = pt->pool;

	cancel_delayed_work_sync(&pool->waker);
	cancel_delayed_work_sync(&pool->no_space_समयout);
	flush_workqueue(pool->wq);
	(व्योम) commit(pool);
पूर्ण

अटल पूर्णांक check_arg_count(अचिन्हित argc, अचिन्हित args_required)
अणु
	अगर (argc != args_required) अणु
		DMWARN("Message received with %u arguments instead of %u.",
		       argc, args_required);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_dev_id(अक्षर *arg, dm_thin_id *dev_id, पूर्णांक warning)
अणु
	अगर (!kम_से_अदीर्घl(arg, 10, (अचिन्हित दीर्घ दीर्घ *)dev_id) &&
	    *dev_id <= MAX_DEV_ID)
		वापस 0;

	अगर (warning)
		DMWARN("Message received with invalid device id: %s", arg);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक process_create_thin_mesg(अचिन्हित argc, अक्षर **argv, काष्ठा pool *pool)
अणु
	dm_thin_id dev_id;
	पूर्णांक r;

	r = check_arg_count(argc, 2);
	अगर (r)
		वापस r;

	r = पढ़ो_dev_id(argv[1], &dev_id, 1);
	अगर (r)
		वापस r;

	r = dm_pool_create_thin(pool->pmd, dev_id);
	अगर (r) अणु
		DMWARN("Creation of new thinly-provisioned device with id %s failed.",
		       argv[1]);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_create_snap_mesg(अचिन्हित argc, अक्षर **argv, काष्ठा pool *pool)
अणु
	dm_thin_id dev_id;
	dm_thin_id origin_dev_id;
	पूर्णांक r;

	r = check_arg_count(argc, 3);
	अगर (r)
		वापस r;

	r = पढ़ो_dev_id(argv[1], &dev_id, 1);
	अगर (r)
		वापस r;

	r = पढ़ो_dev_id(argv[2], &origin_dev_id, 1);
	अगर (r)
		वापस r;

	r = dm_pool_create_snap(pool->pmd, dev_id, origin_dev_id);
	अगर (r) अणु
		DMWARN("Creation of new snapshot %s of device %s failed.",
		       argv[1], argv[2]);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_delete_mesg(अचिन्हित argc, अक्षर **argv, काष्ठा pool *pool)
अणु
	dm_thin_id dev_id;
	पूर्णांक r;

	r = check_arg_count(argc, 2);
	अगर (r)
		वापस r;

	r = पढ़ो_dev_id(argv[1], &dev_id, 1);
	अगर (r)
		वापस r;

	r = dm_pool_delete_thin_device(pool->pmd, dev_id);
	अगर (r)
		DMWARN("Deletion of thin device %s failed.", argv[1]);

	वापस r;
पूर्ण

अटल पूर्णांक process_set_transaction_id_mesg(अचिन्हित argc, अक्षर **argv, काष्ठा pool *pool)
अणु
	dm_thin_id old_id, new_id;
	पूर्णांक r;

	r = check_arg_count(argc, 3);
	अगर (r)
		वापस r;

	अगर (kम_से_अदीर्घl(argv[1], 10, (अचिन्हित दीर्घ दीर्घ *)&old_id)) अणु
		DMWARN("set_transaction_id message: Unrecognised id %s.", argv[1]);
		वापस -EINVAL;
	पूर्ण

	अगर (kम_से_अदीर्घl(argv[2], 10, (अचिन्हित दीर्घ दीर्घ *)&new_id)) अणु
		DMWARN("set_transaction_id message: Unrecognised new id %s.", argv[2]);
		वापस -EINVAL;
	पूर्ण

	r = dm_pool_set_metadata_transaction_id(pool->pmd, old_id, new_id);
	अगर (r) अणु
		DMWARN("Failed to change transaction id from %s to %s.",
		       argv[1], argv[2]);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_reserve_metadata_snap_mesg(अचिन्हित argc, अक्षर **argv, काष्ठा pool *pool)
अणु
	पूर्णांक r;

	r = check_arg_count(argc, 1);
	अगर (r)
		वापस r;

	(व्योम) commit(pool);

	r = dm_pool_reserve_metadata_snap(pool->pmd);
	अगर (r)
		DMWARN("reserve_metadata_snap message failed.");

	वापस r;
पूर्ण

अटल पूर्णांक process_release_metadata_snap_mesg(अचिन्हित argc, अक्षर **argv, काष्ठा pool *pool)
अणु
	पूर्णांक r;

	r = check_arg_count(argc, 1);
	अगर (r)
		वापस r;

	r = dm_pool_release_metadata_snap(pool->pmd);
	अगर (r)
		DMWARN("release_metadata_snap message failed.");

	वापस r;
पूर्ण

/*
 * Messages supported:
 *   create_thin	<dev_id>
 *   create_snap	<dev_id> <origin_id>
 *   delete		<dev_id>
 *   set_transaction_id <current_trans_id> <new_trans_id>
 *   reserve_metadata_snap
 *   release_metadata_snap
 */
अटल पूर्णांक pool_message(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv,
			अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r = -EINVAL;
	काष्ठा pool_c *pt = ti->निजी;
	काष्ठा pool *pool = pt->pool;

	अगर (get_pool_mode(pool) >= PM_OUT_OF_METADATA_SPACE) अणु
		DMERR("%s: unable to service pool target messages in READ_ONLY or FAIL mode",
		      dm_device_name(pool->pool_md));
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!strहालcmp(argv[0], "create_thin"))
		r = process_create_thin_mesg(argc, argv, pool);

	अन्यथा अगर (!strहालcmp(argv[0], "create_snap"))
		r = process_create_snap_mesg(argc, argv, pool);

	अन्यथा अगर (!strहालcmp(argv[0], "delete"))
		r = process_delete_mesg(argc, argv, pool);

	अन्यथा अगर (!strहालcmp(argv[0], "set_transaction_id"))
		r = process_set_transaction_id_mesg(argc, argv, pool);

	अन्यथा अगर (!strहालcmp(argv[0], "reserve_metadata_snap"))
		r = process_reserve_metadata_snap_mesg(argc, argv, pool);

	अन्यथा अगर (!strहालcmp(argv[0], "release_metadata_snap"))
		r = process_release_metadata_snap_mesg(argc, argv, pool);

	अन्यथा
		DMWARN("Unrecognised thin pool target message received: %s", argv[0]);

	अगर (!r)
		(व्योम) commit(pool);

	वापस r;
पूर्ण

अटल व्योम emit_flags(काष्ठा pool_features *pf, अक्षर *result,
		       अचिन्हित sz, अचिन्हित maxlen)
अणु
	अचिन्हित count = !pf->zero_new_blocks + !pf->discard_enabled +
		!pf->discard_passकरोwn + (pf->mode == PM_READ_ONLY) +
		pf->error_अगर_no_space;
	DMEMIT("%u ", count);

	अगर (!pf->zero_new_blocks)
		DMEMIT("skip_block_zeroing ");

	अगर (!pf->discard_enabled)
		DMEMIT("ignore_discard ");

	अगर (!pf->discard_passकरोwn)
		DMEMIT("no_discard_passdown ");

	अगर (pf->mode == PM_READ_ONLY)
		DMEMIT("read_only ");

	अगर (pf->error_अगर_no_space)
		DMEMIT("error_if_no_space ");
पूर्ण

/*
 * Status line is:
 *    <transaction id> <used metadata sectors>/<total metadata sectors>
 *    <used data sectors>/<total data sectors> <held metadata root>
 *    <pool mode> <discard config> <no space config> <needs_check>
 */
अटल व्योम pool_status(काष्ठा dm_target *ti, status_type_t type,
			अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r;
	अचिन्हित sz = 0;
	uपूर्णांक64_t transaction_id;
	dm_block_t nr_मुक्त_blocks_data;
	dm_block_t nr_मुक्त_blocks_metadata;
	dm_block_t nr_blocks_data;
	dm_block_t nr_blocks_metadata;
	dm_block_t held_root;
	क्रमागत pool_mode mode;
	अक्षर buf[BDEVNAME_SIZE];
	अक्षर buf2[BDEVNAME_SIZE];
	काष्ठा pool_c *pt = ti->निजी;
	काष्ठा pool *pool = pt->pool;

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		अगर (get_pool_mode(pool) == PM_FAIL) अणु
			DMEMIT("Fail");
			अवरोध;
		पूर्ण

		/* Commit to ensure statistics aren't out-of-date */
		अगर (!(status_flags & DM_STATUS_NOFLUSH_FLAG) && !dm_suspended(ti))
			(व्योम) commit(pool);

		r = dm_pool_get_metadata_transaction_id(pool->pmd, &transaction_id);
		अगर (r) अणु
			DMERR("%s: dm_pool_get_metadata_transaction_id returned %d",
			      dm_device_name(pool->pool_md), r);
			जाओ err;
		पूर्ण

		r = dm_pool_get_मुक्त_metadata_block_count(pool->pmd, &nr_मुक्त_blocks_metadata);
		अगर (r) अणु
			DMERR("%s: dm_pool_get_free_metadata_block_count returned %d",
			      dm_device_name(pool->pool_md), r);
			जाओ err;
		पूर्ण

		r = dm_pool_get_metadata_dev_size(pool->pmd, &nr_blocks_metadata);
		अगर (r) अणु
			DMERR("%s: dm_pool_get_metadata_dev_size returned %d",
			      dm_device_name(pool->pool_md), r);
			जाओ err;
		पूर्ण

		r = dm_pool_get_मुक्त_block_count(pool->pmd, &nr_मुक्त_blocks_data);
		अगर (r) अणु
			DMERR("%s: dm_pool_get_free_block_count returned %d",
			      dm_device_name(pool->pool_md), r);
			जाओ err;
		पूर्ण

		r = dm_pool_get_data_dev_size(pool->pmd, &nr_blocks_data);
		अगर (r) अणु
			DMERR("%s: dm_pool_get_data_dev_size returned %d",
			      dm_device_name(pool->pool_md), r);
			जाओ err;
		पूर्ण

		r = dm_pool_get_metadata_snap(pool->pmd, &held_root);
		अगर (r) अणु
			DMERR("%s: dm_pool_get_metadata_snap returned %d",
			      dm_device_name(pool->pool_md), r);
			जाओ err;
		पूर्ण

		DMEMIT("%llu %llu/%llu %llu/%llu ",
		       (अचिन्हित दीर्घ दीर्घ)transaction_id,
		       (अचिन्हित दीर्घ दीर्घ)(nr_blocks_metadata - nr_मुक्त_blocks_metadata),
		       (अचिन्हित दीर्घ दीर्घ)nr_blocks_metadata,
		       (अचिन्हित दीर्घ दीर्घ)(nr_blocks_data - nr_मुक्त_blocks_data),
		       (अचिन्हित दीर्घ दीर्घ)nr_blocks_data);

		अगर (held_root)
			DMEMIT("%llu ", held_root);
		अन्यथा
			DMEMIT("- ");

		mode = get_pool_mode(pool);
		अगर (mode == PM_OUT_OF_DATA_SPACE)
			DMEMIT("out_of_data_space ");
		अन्यथा अगर (is_पढ़ो_only_pool_mode(mode))
			DMEMIT("ro ");
		अन्यथा
			DMEMIT("rw ");

		अगर (!pool->pf.discard_enabled)
			DMEMIT("ignore_discard ");
		अन्यथा अगर (pool->pf.discard_passकरोwn)
			DMEMIT("discard_passdown ");
		अन्यथा
			DMEMIT("no_discard_passdown ");

		अगर (pool->pf.error_अगर_no_space)
			DMEMIT("error_if_no_space ");
		अन्यथा
			DMEMIT("queue_if_no_space ");

		अगर (dm_pool_metadata_needs_check(pool->pmd))
			DMEMIT("needs_check ");
		अन्यथा
			DMEMIT("- ");

		DMEMIT("%llu ", (अचिन्हित दीर्घ दीर्घ)calc_metadata_threshold(pt));

		अवरोध;

	हाल STATUSTYPE_TABLE:
		DMEMIT("%s %s %lu %llu ",
		       क्रमmat_dev_t(buf, pt->metadata_dev->bdev->bd_dev),
		       क्रमmat_dev_t(buf2, pt->data_dev->bdev->bd_dev),
		       (अचिन्हित दीर्घ)pool->sectors_per_block,
		       (अचिन्हित दीर्घ दीर्घ)pt->low_water_blocks);
		emit_flags(&pt->requested_pf, result, sz, maxlen);
		अवरोध;
	पूर्ण
	वापस;

err:
	DMEMIT("Error");
पूर्ण

अटल पूर्णांक pool_iterate_devices(काष्ठा dm_target *ti,
				iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा pool_c *pt = ti->निजी;

	वापस fn(ti, pt->data_dev, 0, ti->len, data);
पूर्ण

अटल व्योम pool_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा pool_c *pt = ti->निजी;
	काष्ठा pool *pool = pt->pool;
	sector_t io_opt_sectors = limits->io_opt >> SECTOR_SHIFT;

	/*
	 * If max_sectors is smaller than pool->sectors_per_block adjust it
	 * to the highest possible घातer-of-2 factor of pool->sectors_per_block.
	 * This is especially beneficial when the pool's data device is a RAID
	 * device that has a full stripe width that matches pool->sectors_per_block
	 * -- because even though partial RAID stripe-sized IOs will be issued to a
	 *    single RAID stripe; when aggregated they will end on a full RAID stripe
	 *    boundary.. which aव्योमs additional partial RAID stripe ग_लिखोs cascading
	 */
	अगर (limits->max_sectors < pool->sectors_per_block) अणु
		जबतक (!is_factor(pool->sectors_per_block, limits->max_sectors)) अणु
			अगर ((limits->max_sectors & (limits->max_sectors - 1)) == 0)
				limits->max_sectors--;
			limits->max_sectors = roundकरोwn_घात_of_two(limits->max_sectors);
		पूर्ण
	पूर्ण

	/*
	 * If the प्रणाली-determined stacked limits are compatible with the
	 * pool's blocksize (io_opt is a factor) करो not override them.
	 */
	अगर (io_opt_sectors < pool->sectors_per_block ||
	    !is_factor(io_opt_sectors, pool->sectors_per_block)) अणु
		अगर (is_factor(pool->sectors_per_block, limits->max_sectors))
			blk_limits_io_min(limits, limits->max_sectors << SECTOR_SHIFT);
		अन्यथा
			blk_limits_io_min(limits, pool->sectors_per_block << SECTOR_SHIFT);
		blk_limits_io_opt(limits, pool->sectors_per_block << SECTOR_SHIFT);
	पूर्ण

	/*
	 * pt->adjusted_pf is a staging area क्रम the actual features to use.
	 * They get transferred to the live pool in bind_control_target()
	 * called from pool_preresume().
	 */
	अगर (!pt->adjusted_pf.discard_enabled) अणु
		/*
		 * Must explicitly disallow stacking discard limits otherwise the
		 * block layer will stack them अगर pool's data device has support.
		 * QUEUE_FLAG_DISCARD wouldn't be set but there is no way क्रम the
		 * user to see that, so make sure to set all discard limits to 0.
		 */
		limits->discard_granularity = 0;
		वापस;
	पूर्ण

	disable_passकरोwn_अगर_not_supported(pt);

	/*
	 * The pool uses the same discard limits as the underlying data
	 * device.  DM core has alपढ़ोy set this up.
	 */
पूर्ण

अटल काष्ठा target_type pool_target = अणु
	.name = "thin-pool",
	.features = DM_TARGET_SINGLETON | DM_TARGET_ALWAYS_WRITEABLE |
		    DM_TARGET_IMMUTABLE,
	.version = अणु1, 22, 0पूर्ण,
	.module = THIS_MODULE,
	.ctr = pool_ctr,
	.dtr = pool_dtr,
	.map = pool_map,
	.presuspend = pool_presuspend,
	.presuspend_unकरो = pool_presuspend_unकरो,
	.postsuspend = pool_postsuspend,
	.preresume = pool_preresume,
	.resume = pool_resume,
	.message = pool_message,
	.status = pool_status,
	.iterate_devices = pool_iterate_devices,
	.io_hपूर्णांकs = pool_io_hपूर्णांकs,
पूर्ण;

/*----------------------------------------------------------------
 * Thin target methods
 *--------------------------------------------------------------*/
अटल व्योम thin_get(काष्ठा thin_c *tc)
अणु
	refcount_inc(&tc->refcount);
पूर्ण

अटल व्योम thin_put(काष्ठा thin_c *tc)
अणु
	अगर (refcount_dec_and_test(&tc->refcount))
		complete(&tc->can_destroy);
पूर्ण

अटल व्योम thin_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा thin_c *tc = ti->निजी;

	spin_lock_irq(&tc->pool->lock);
	list_del_rcu(&tc->list);
	spin_unlock_irq(&tc->pool->lock);
	synchronize_rcu();

	thin_put(tc);
	रुको_क्रम_completion(&tc->can_destroy);

	mutex_lock(&dm_thin_pool_table.mutex);

	__pool_dec(tc->pool);
	dm_pool_बंद_thin_device(tc->td);
	dm_put_device(ti, tc->pool_dev);
	अगर (tc->origin_dev)
		dm_put_device(ti, tc->origin_dev);
	kमुक्त(tc);

	mutex_unlock(&dm_thin_pool_table.mutex);
पूर्ण

/*
 * Thin target parameters:
 *
 * <pool_dev> <dev_id> [origin_dev]
 *
 * pool_dev: the path to the pool (eg, /dev/mapper/my_pool)
 * dev_id: the पूर्णांकernal device identअगरier
 * origin_dev: a device बाह्यal to the pool that should act as the origin
 *
 * If the pool device has discards disabled, they get disabled क्रम the thin
 * device as well.
 */
अटल पूर्णांक thin_ctr(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv)
अणु
	पूर्णांक r;
	काष्ठा thin_c *tc;
	काष्ठा dm_dev *pool_dev, *origin_dev;
	काष्ठा mapped_device *pool_md;

	mutex_lock(&dm_thin_pool_table.mutex);

	अगर (argc != 2 && argc != 3) अणु
		ti->error = "Invalid argument count";
		r = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	tc = ti->निजी = kzalloc(माप(*tc), GFP_KERNEL);
	अगर (!tc) अणु
		ti->error = "Out of memory";
		r = -ENOMEM;
		जाओ out_unlock;
	पूर्ण
	tc->thin_md = dm_table_get_md(ti->table);
	spin_lock_init(&tc->lock);
	INIT_LIST_HEAD(&tc->deferred_cells);
	bio_list_init(&tc->deferred_bio_list);
	bio_list_init(&tc->retry_on_resume_list);
	tc->sort_bio_list = RB_ROOT;

	अगर (argc == 3) अणु
		अगर (!म_भेद(argv[0], argv[2])) अणु
			ti->error = "Error setting origin device";
			r = -EINVAL;
			जाओ bad_origin_dev;
		पूर्ण

		r = dm_get_device(ti, argv[2], FMODE_READ, &origin_dev);
		अगर (r) अणु
			ti->error = "Error opening origin device";
			जाओ bad_origin_dev;
		पूर्ण
		tc->origin_dev = origin_dev;
	पूर्ण

	r = dm_get_device(ti, argv[0], dm_table_get_mode(ti->table), &pool_dev);
	अगर (r) अणु
		ti->error = "Error opening pool device";
		जाओ bad_pool_dev;
	पूर्ण
	tc->pool_dev = pool_dev;

	अगर (पढ़ो_dev_id(argv[1], (अचिन्हित दीर्घ दीर्घ *)&tc->dev_id, 0)) अणु
		ti->error = "Invalid device id";
		r = -EINVAL;
		जाओ bad_common;
	पूर्ण

	pool_md = dm_get_md(tc->pool_dev->bdev->bd_dev);
	अगर (!pool_md) अणु
		ti->error = "Couldn't get pool mapped device";
		r = -EINVAL;
		जाओ bad_common;
	पूर्ण

	tc->pool = __pool_table_lookup(pool_md);
	अगर (!tc->pool) अणु
		ti->error = "Couldn't find pool object";
		r = -EINVAL;
		जाओ bad_pool_lookup;
	पूर्ण
	__pool_inc(tc->pool);

	अगर (get_pool_mode(tc->pool) == PM_FAIL) अणु
		ti->error = "Couldn't open thin device, Pool is in fail mode";
		r = -EINVAL;
		जाओ bad_pool;
	पूर्ण

	r = dm_pool_खोलो_thin_device(tc->pool->pmd, tc->dev_id, &tc->td);
	अगर (r) अणु
		ti->error = "Couldn't open thin internal device";
		जाओ bad_pool;
	पूर्ण

	r = dm_set_target_max_io_len(ti, tc->pool->sectors_per_block);
	अगर (r)
		जाओ bad;

	ti->num_flush_bios = 1;
	ti->flush_supported = true;
	ti->per_io_data_size = माप(काष्ठा dm_thin_endio_hook);

	/* In हाल the pool supports discards, pass them on. */
	अगर (tc->pool->pf.discard_enabled) अणु
		ti->discards_supported = true;
		ti->num_discard_bios = 1;
	पूर्ण

	mutex_unlock(&dm_thin_pool_table.mutex);

	spin_lock_irq(&tc->pool->lock);
	अगर (tc->pool->suspended) अणु
		spin_unlock_irq(&tc->pool->lock);
		mutex_lock(&dm_thin_pool_table.mutex); /* reacquire क्रम __pool_dec */
		ti->error = "Unable to activate thin device while pool is suspended";
		r = -EINVAL;
		जाओ bad;
	पूर्ण
	refcount_set(&tc->refcount, 1);
	init_completion(&tc->can_destroy);
	list_add_tail_rcu(&tc->list, &tc->pool->active_thins);
	spin_unlock_irq(&tc->pool->lock);
	/*
	 * This synchronize_rcu() call is needed here otherwise we risk a
	 * wake_worker() call finding no bios to process (because the newly
	 * added tc isn't yet visible).  So this reduces latency since we
	 * aren't then dependent on the periodic commit to wake_worker().
	 */
	synchronize_rcu();

	dm_put(pool_md);

	वापस 0;

bad:
	dm_pool_बंद_thin_device(tc->td);
bad_pool:
	__pool_dec(tc->pool);
bad_pool_lookup:
	dm_put(pool_md);
bad_common:
	dm_put_device(ti, tc->pool_dev);
bad_pool_dev:
	अगर (tc->origin_dev)
		dm_put_device(ti, tc->origin_dev);
bad_origin_dev:
	kमुक्त(tc);
out_unlock:
	mutex_unlock(&dm_thin_pool_table.mutex);

	वापस r;
पूर्ण

अटल पूर्णांक thin_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	bio->bi_iter.bi_sector = dm_target_offset(ti, bio->bi_iter.bi_sector);

	वापस thin_bio_map(ti, bio);
पूर्ण

अटल पूर्णांक thin_endio(काष्ठा dm_target *ti, काष्ठा bio *bio,
		blk_status_t *err)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dm_thin_endio_hook *h = dm_per_bio_data(bio, माप(काष्ठा dm_thin_endio_hook));
	काष्ठा list_head work;
	काष्ठा dm_thin_new_mapping *m, *पंचांगp;
	काष्ठा pool *pool = h->tc->pool;

	अगर (h->shared_पढ़ो_entry) अणु
		INIT_LIST_HEAD(&work);
		dm_deferred_entry_dec(h->shared_पढ़ो_entry, &work);

		spin_lock_irqsave(&pool->lock, flags);
		list_क्रम_each_entry_safe(m, पंचांगp, &work, list) अणु
			list_del(&m->list);
			__complete_mapping_preparation(m);
		पूर्ण
		spin_unlock_irqrestore(&pool->lock, flags);
	पूर्ण

	अगर (h->all_io_entry) अणु
		INIT_LIST_HEAD(&work);
		dm_deferred_entry_dec(h->all_io_entry, &work);
		अगर (!list_empty(&work)) अणु
			spin_lock_irqsave(&pool->lock, flags);
			list_क्रम_each_entry_safe(m, पंचांगp, &work, list)
				list_add_tail(&m->list, &pool->prepared_discards);
			spin_unlock_irqrestore(&pool->lock, flags);
			wake_worker(pool);
		पूर्ण
	पूर्ण

	अगर (h->cell)
		cell_defer_no_holder(h->tc, h->cell);

	वापस DM_ENDIO_DONE;
पूर्ण

अटल व्योम thin_presuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा thin_c *tc = ti->निजी;

	अगर (dm_noflush_suspending(ti))
		noflush_work(tc, करो_noflush_start);
पूर्ण

अटल व्योम thin_postsuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा thin_c *tc = ti->निजी;

	/*
	 * The dm_noflush_suspending flag has been cleared by now, so
	 * unक्रमtunately we must always run this.
	 */
	noflush_work(tc, करो_noflush_stop);
पूर्ण

अटल पूर्णांक thin_preresume(काष्ठा dm_target *ti)
अणु
	काष्ठा thin_c *tc = ti->निजी;

	अगर (tc->origin_dev)
		tc->origin_size = get_dev_size(tc->origin_dev->bdev);

	वापस 0;
पूर्ण

/*
 * <nr mapped sectors> <highest mapped sector>
 */
अटल व्योम thin_status(काष्ठा dm_target *ti, status_type_t type,
			अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r;
	sमाप_प्रकार sz = 0;
	dm_block_t mapped, highest;
	अक्षर buf[BDEVNAME_SIZE];
	काष्ठा thin_c *tc = ti->निजी;

	अगर (get_pool_mode(tc->pool) == PM_FAIL) अणु
		DMEMIT("Fail");
		वापस;
	पूर्ण

	अगर (!tc->td)
		DMEMIT("-");
	अन्यथा अणु
		चयन (type) अणु
		हाल STATUSTYPE_INFO:
			r = dm_thin_get_mapped_count(tc->td, &mapped);
			अगर (r) अणु
				DMERR("dm_thin_get_mapped_count returned %d", r);
				जाओ err;
			पूर्ण

			r = dm_thin_get_highest_mapped_block(tc->td, &highest);
			अगर (r < 0) अणु
				DMERR("dm_thin_get_highest_mapped_block returned %d", r);
				जाओ err;
			पूर्ण

			DMEMIT("%llu ", mapped * tc->pool->sectors_per_block);
			अगर (r)
				DMEMIT("%llu", ((highest + 1) *
						tc->pool->sectors_per_block) - 1);
			अन्यथा
				DMEMIT("-");
			अवरोध;

		हाल STATUSTYPE_TABLE:
			DMEMIT("%s %lu",
			       क्रमmat_dev_t(buf, tc->pool_dev->bdev->bd_dev),
			       (अचिन्हित दीर्घ) tc->dev_id);
			अगर (tc->origin_dev)
				DMEMIT(" %s", क्रमmat_dev_t(buf, tc->origin_dev->bdev->bd_dev));
			अवरोध;
		पूर्ण
	पूर्ण

	वापस;

err:
	DMEMIT("Error");
पूर्ण

अटल पूर्णांक thin_iterate_devices(काष्ठा dm_target *ti,
				iterate_devices_callout_fn fn, व्योम *data)
अणु
	sector_t blocks;
	काष्ठा thin_c *tc = ti->निजी;
	काष्ठा pool *pool = tc->pool;

	/*
	 * We can't call dm_pool_get_data_dev_size() since that blocks.  So
	 * we follow a more convoluted path through to the pool's target.
	 */
	अगर (!pool->ti)
		वापस 0;	/* nothing is bound */

	blocks = pool->ti->len;
	(व्योम) sector_भाग(blocks, pool->sectors_per_block);
	अगर (blocks)
		वापस fn(ti, tc->pool_dev, 0, pool->sectors_per_block * blocks, data);

	वापस 0;
पूर्ण

अटल व्योम thin_io_hपूर्णांकs(काष्ठा dm_target *ti, काष्ठा queue_limits *limits)
अणु
	काष्ठा thin_c *tc = ti->निजी;
	काष्ठा pool *pool = tc->pool;

	अगर (!pool->pf.discard_enabled)
		वापस;

	limits->discard_granularity = pool->sectors_per_block << SECTOR_SHIFT;
	limits->max_discard_sectors = 2048 * 1024 * 16; /* 16G */
पूर्ण

अटल काष्ठा target_type thin_target = अणु
	.name = "thin",
	.version = अणु1, 22, 0पूर्ण,
	.module	= THIS_MODULE,
	.ctr = thin_ctr,
	.dtr = thin_dtr,
	.map = thin_map,
	.end_io = thin_endio,
	.preresume = thin_preresume,
	.presuspend = thin_presuspend,
	.postsuspend = thin_postsuspend,
	.status = thin_status,
	.iterate_devices = thin_iterate_devices,
	.io_hपूर्णांकs = thin_io_hपूर्णांकs,
पूर्ण;

/*----------------------------------------------------------------*/

अटल पूर्णांक __init dm_thin_init(व्योम)
अणु
	पूर्णांक r = -ENOMEM;

	pool_table_init();

	_new_mapping_cache = KMEM_CACHE(dm_thin_new_mapping, 0);
	अगर (!_new_mapping_cache)
		वापस r;

	r = dm_रेजिस्टर_target(&thin_target);
	अगर (r)
		जाओ bad_new_mapping_cache;

	r = dm_रेजिस्टर_target(&pool_target);
	अगर (r)
		जाओ bad_thin_target;

	वापस 0;

bad_thin_target:
	dm_unरेजिस्टर_target(&thin_target);
bad_new_mapping_cache:
	kmem_cache_destroy(_new_mapping_cache);

	वापस r;
पूर्ण

अटल व्योम dm_thin_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&thin_target);
	dm_unरेजिस्टर_target(&pool_target);

	kmem_cache_destroy(_new_mapping_cache);

	pool_table_निकास();
पूर्ण

module_init(dm_thin_init);
module_निकास(dm_thin_निकास);

module_param_named(no_space_समयout, no_space_समयout_secs, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(no_space_समयout, "Out of data space queue IO timeout in seconds");

MODULE_DESCRIPTION(DM_NAME " thin provisioning target");
MODULE_AUTHOR("Joe Thornber <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
