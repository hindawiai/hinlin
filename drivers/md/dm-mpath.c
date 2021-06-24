<शैली गुरु>
/*
 * Copyright (C) 2003 Sistina Software Limited.
 * Copyright (C) 2004-2005 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश <linux/device-mapper.h>

#समावेश "dm-rq.h"
#समावेश "dm-bio-record.h"
#समावेश "dm-path-selector.h"
#समावेश "dm-uevent.h"

#समावेश <linux/blkdev.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/init.h>
#समावेश <linux/mempool.h>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_dh.h>
#समावेश <linux/atomic.h>
#समावेश <linux/blk-mq.h>

#घोषणा DM_MSG_PREFIX "multipath"
#घोषणा DM_PG_INIT_DELAY_MSECS 2000
#घोषणा DM_PG_INIT_DELAY_DEFAULT ((अचिन्हित) -1)
#घोषणा QUEUE_IF_NO_PATH_TIMEOUT_DEFAULT 0

अटल अचिन्हित दीर्घ queue_अगर_no_path_समयout_secs = QUEUE_IF_NO_PATH_TIMEOUT_DEFAULT;

/* Path properties */
काष्ठा pgpath अणु
	काष्ठा list_head list;

	काष्ठा priority_group *pg;	/* Owning PG */
	अचिन्हित fail_count;		/* Cumulative failure count */

	काष्ठा dm_path path;
	काष्ठा delayed_work activate_path;

	bool is_active:1;		/* Path status */
पूर्ण;

#घोषणा path_to_pgpath(__pgp) container_of((__pgp), काष्ठा pgpath, path)

/*
 * Paths are grouped पूर्णांकo Priority Groups and numbered from 1 upwards.
 * Each has a path selector which controls which path माला_लो used.
 */
काष्ठा priority_group अणु
	काष्ठा list_head list;

	काष्ठा multipath *m;		/* Owning multipath instance */
	काष्ठा path_selector ps;

	अचिन्हित pg_num;		/* Reference number */
	अचिन्हित nr_pgpaths;		/* Number of paths in PG */
	काष्ठा list_head pgpaths;

	bool bypassed:1;		/* Temporarily bypass this PG? */
पूर्ण;

/* Multipath context */
काष्ठा multipath अणु
	अचिन्हित दीर्घ flags;		/* Multipath state flags */

	spinlock_t lock;
	क्रमागत dm_queue_mode queue_mode;

	काष्ठा pgpath *current_pgpath;
	काष्ठा priority_group *current_pg;
	काष्ठा priority_group *next_pg;	/* Switch to this PG अगर set */

	atomic_t nr_valid_paths;	/* Total number of usable paths */
	अचिन्हित nr_priority_groups;
	काष्ठा list_head priority_groups;

	स्थिर अक्षर *hw_handler_name;
	अक्षर *hw_handler_params;
	रुको_queue_head_t pg_init_रुको;	/* Wait क्रम pg_init completion */
	अचिन्हित pg_init_retries;	/* Number of बार to retry pg_init */
	अचिन्हित pg_init_delay_msecs;	/* Number of msecs beक्रमe pg_init retry */
	atomic_t pg_init_in_progress;	/* Only one pg_init allowed at once */
	atomic_t pg_init_count;		/* Number of बार pg_init called */

	काष्ठा mutex work_mutex;
	काष्ठा work_काष्ठा trigger_event;
	काष्ठा dm_target *ti;

	काष्ठा work_काष्ठा process_queued_bios;
	काष्ठा bio_list queued_bios;

	काष्ठा समयr_list nopath_समयr;	/* Timeout क्रम queue_अगर_no_path */
पूर्ण;

/*
 * Context inक्रमmation attached to each io we process.
 */
काष्ठा dm_mpath_io अणु
	काष्ठा pgpath *pgpath;
	माप_प्रकार nr_bytes;
पूर्ण;

प्रकार पूर्णांक (*action_fn) (काष्ठा pgpath *pgpath);

अटल काष्ठा workqueue_काष्ठा *kmultipathd, *kmpath_handlerd;
अटल व्योम trigger_event(काष्ठा work_काष्ठा *work);
अटल व्योम activate_or_offline_path(काष्ठा pgpath *pgpath);
अटल व्योम activate_path_work(काष्ठा work_काष्ठा *work);
अटल व्योम process_queued_bios(काष्ठा work_काष्ठा *work);
अटल व्योम queue_अगर_no_path_समयout_work(काष्ठा समयr_list *t);

/*-----------------------------------------------
 * Multipath state flags.
 *-----------------------------------------------*/

#घोषणा MPATHF_QUEUE_IO 0			/* Must we queue all I/O? */
#घोषणा MPATHF_QUEUE_IF_NO_PATH 1		/* Queue I/O अगर last path fails? */
#घोषणा MPATHF_SAVED_QUEUE_IF_NO_PATH 2		/* Saved state during suspension */
#घोषणा MPATHF_RETAIN_ATTACHED_HW_HANDLER 3	/* If there's already a hw_handler present, don't change it. */
#घोषणा MPATHF_PG_INIT_DISABLED 4		/* pg_init is not currently allowed */
#घोषणा MPATHF_PG_INIT_REQUIRED 5		/* pg_init needs calling? */
#घोषणा MPATHF_PG_INIT_DELAY_RETRY 6		/* Delay pg_init retry? */

अटल bool mpath_द्विगुन_check_test_bit(पूर्णांक MPATHF_bit, काष्ठा multipath *m)
अणु
	bool r = test_bit(MPATHF_bit, &m->flags);

	अगर (r) अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&m->lock, flags);
		r = test_bit(MPATHF_bit, &m->flags);
		spin_unlock_irqrestore(&m->lock, flags);
	पूर्ण

	वापस r;
पूर्ण

/*-----------------------------------------------
 * Allocation routines
 *-----------------------------------------------*/

अटल काष्ठा pgpath *alloc_pgpath(व्योम)
अणु
	काष्ठा pgpath *pgpath = kzalloc(माप(*pgpath), GFP_KERNEL);

	अगर (!pgpath)
		वापस शून्य;

	pgpath->is_active = true;

	वापस pgpath;
पूर्ण

अटल व्योम मुक्त_pgpath(काष्ठा pgpath *pgpath)
अणु
	kमुक्त(pgpath);
पूर्ण

अटल काष्ठा priority_group *alloc_priority_group(व्योम)
अणु
	काष्ठा priority_group *pg;

	pg = kzalloc(माप(*pg), GFP_KERNEL);

	अगर (pg)
		INIT_LIST_HEAD(&pg->pgpaths);

	वापस pg;
पूर्ण

अटल व्योम मुक्त_pgpaths(काष्ठा list_head *pgpaths, काष्ठा dm_target *ti)
अणु
	काष्ठा pgpath *pgpath, *पंचांगp;

	list_क्रम_each_entry_safe(pgpath, पंचांगp, pgpaths, list) अणु
		list_del(&pgpath->list);
		dm_put_device(ti, pgpath->path.dev);
		मुक्त_pgpath(pgpath);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_priority_group(काष्ठा priority_group *pg,
				काष्ठा dm_target *ti)
अणु
	काष्ठा path_selector *ps = &pg->ps;

	अगर (ps->type) अणु
		ps->type->destroy(ps);
		dm_put_path_selector(ps->type);
	पूर्ण

	मुक्त_pgpaths(&pg->pgpaths, ti);
	kमुक्त(pg);
पूर्ण

अटल काष्ठा multipath *alloc_multipath(काष्ठा dm_target *ti)
अणु
	काष्ठा multipath *m;

	m = kzalloc(माप(*m), GFP_KERNEL);
	अगर (m) अणु
		INIT_LIST_HEAD(&m->priority_groups);
		spin_lock_init(&m->lock);
		atomic_set(&m->nr_valid_paths, 0);
		INIT_WORK(&m->trigger_event, trigger_event);
		mutex_init(&m->work_mutex);

		m->queue_mode = DM_TYPE_NONE;

		m->ti = ti;
		ti->निजी = m;

		समयr_setup(&m->nopath_समयr, queue_अगर_no_path_समयout_work, 0);
	पूर्ण

	वापस m;
पूर्ण

अटल पूर्णांक alloc_multipath_stage2(काष्ठा dm_target *ti, काष्ठा multipath *m)
अणु
	अगर (m->queue_mode == DM_TYPE_NONE) अणु
		m->queue_mode = DM_TYPE_REQUEST_BASED;
	पूर्ण अन्यथा अगर (m->queue_mode == DM_TYPE_BIO_BASED) अणु
		INIT_WORK(&m->process_queued_bios, process_queued_bios);
		/*
		 * bio-based करोesn't support any direct scsi_dh management;
		 * it just discovers अगर a scsi_dh is attached.
		 */
		set_bit(MPATHF_RETAIN_ATTACHED_HW_HANDLER, &m->flags);
	पूर्ण

	dm_table_set_type(ti->table, m->queue_mode);

	/*
	 * Init fields that are only used when a scsi_dh is attached
	 * - must करो this unconditionally (really करोesn't hurt non-SCSI uses)
	 */
	set_bit(MPATHF_QUEUE_IO, &m->flags);
	atomic_set(&m->pg_init_in_progress, 0);
	atomic_set(&m->pg_init_count, 0);
	m->pg_init_delay_msecs = DM_PG_INIT_DELAY_DEFAULT;
	init_रुकोqueue_head(&m->pg_init_रुको);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_multipath(काष्ठा multipath *m)
अणु
	काष्ठा priority_group *pg, *पंचांगp;

	list_क्रम_each_entry_safe(pg, पंचांगp, &m->priority_groups, list) अणु
		list_del(&pg->list);
		मुक्त_priority_group(pg, m->ti);
	पूर्ण

	kमुक्त(m->hw_handler_name);
	kमुक्त(m->hw_handler_params);
	mutex_destroy(&m->work_mutex);
	kमुक्त(m);
पूर्ण

अटल काष्ठा dm_mpath_io *get_mpio(जोड़ map_info *info)
अणु
	वापस info->ptr;
पूर्ण

अटल माप_प्रकार multipath_per_bio_data_size(व्योम)
अणु
	वापस माप(काष्ठा dm_mpath_io) + माप(काष्ठा dm_bio_details);
पूर्ण

अटल काष्ठा dm_mpath_io *get_mpio_from_bio(काष्ठा bio *bio)
अणु
	वापस dm_per_bio_data(bio, multipath_per_bio_data_size());
पूर्ण

अटल काष्ठा dm_bio_details *get_bio_details_from_mpio(काष्ठा dm_mpath_io *mpio)
अणु
	/* dm_bio_details is immediately after the dm_mpath_io in bio's per-bio-data */
	व्योम *bio_details = mpio + 1;
	वापस bio_details;
पूर्ण

अटल व्योम multipath_init_per_bio_data(काष्ठा bio *bio, काष्ठा dm_mpath_io **mpio_p)
अणु
	काष्ठा dm_mpath_io *mpio = get_mpio_from_bio(bio);
	काष्ठा dm_bio_details *bio_details = get_bio_details_from_mpio(mpio);

	mpio->nr_bytes = bio->bi_iter.bi_size;
	mpio->pgpath = शून्य;
	*mpio_p = mpio;

	dm_bio_record(bio_details, bio);
पूर्ण

/*-----------------------------------------------
 * Path selection
 *-----------------------------------------------*/

अटल पूर्णांक __pg_init_all_paths(काष्ठा multipath *m)
अणु
	काष्ठा pgpath *pgpath;
	अचिन्हित दीर्घ pg_init_delay = 0;

	lockdep_निश्चित_held(&m->lock);

	अगर (atomic_पढ़ो(&m->pg_init_in_progress) || test_bit(MPATHF_PG_INIT_DISABLED, &m->flags))
		वापस 0;

	atomic_inc(&m->pg_init_count);
	clear_bit(MPATHF_PG_INIT_REQUIRED, &m->flags);

	/* Check here to reset pg_init_required */
	अगर (!m->current_pg)
		वापस 0;

	अगर (test_bit(MPATHF_PG_INIT_DELAY_RETRY, &m->flags))
		pg_init_delay = msecs_to_jअगरfies(m->pg_init_delay_msecs != DM_PG_INIT_DELAY_DEFAULT ?
						 m->pg_init_delay_msecs : DM_PG_INIT_DELAY_MSECS);
	list_क्रम_each_entry(pgpath, &m->current_pg->pgpaths, list) अणु
		/* Skip failed paths */
		अगर (!pgpath->is_active)
			जारी;
		अगर (queue_delayed_work(kmpath_handlerd, &pgpath->activate_path,
				       pg_init_delay))
			atomic_inc(&m->pg_init_in_progress);
	पूर्ण
	वापस atomic_पढ़ो(&m->pg_init_in_progress);
पूर्ण

अटल पूर्णांक pg_init_all_paths(काष्ठा multipath *m)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&m->lock, flags);
	ret = __pg_init_all_paths(m);
	spin_unlock_irqrestore(&m->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम __चयन_pg(काष्ठा multipath *m, काष्ठा priority_group *pg)
अणु
	lockdep_निश्चित_held(&m->lock);

	m->current_pg = pg;

	/* Must we initialise the PG first, and queue I/O till it's पढ़ोy? */
	अगर (m->hw_handler_name) अणु
		set_bit(MPATHF_PG_INIT_REQUIRED, &m->flags);
		set_bit(MPATHF_QUEUE_IO, &m->flags);
	पूर्ण अन्यथा अणु
		clear_bit(MPATHF_PG_INIT_REQUIRED, &m->flags);
		clear_bit(MPATHF_QUEUE_IO, &m->flags);
	पूर्ण

	atomic_set(&m->pg_init_count, 0);
पूर्ण

अटल काष्ठा pgpath *choose_path_in_pg(काष्ठा multipath *m,
					काष्ठा priority_group *pg,
					माप_प्रकार nr_bytes)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dm_path *path;
	काष्ठा pgpath *pgpath;

	path = pg->ps.type->select_path(&pg->ps, nr_bytes);
	अगर (!path)
		वापस ERR_PTR(-ENXIO);

	pgpath = path_to_pgpath(path);

	अगर (unlikely(READ_ONCE(m->current_pg) != pg)) अणु
		/* Only update current_pgpath अगर pg changed */
		spin_lock_irqsave(&m->lock, flags);
		m->current_pgpath = pgpath;
		__चयन_pg(m, pg);
		spin_unlock_irqrestore(&m->lock, flags);
	पूर्ण

	वापस pgpath;
पूर्ण

अटल काष्ठा pgpath *choose_pgpath(काष्ठा multipath *m, माप_प्रकार nr_bytes)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा priority_group *pg;
	काष्ठा pgpath *pgpath;
	अचिन्हित bypassed = 1;

	अगर (!atomic_पढ़ो(&m->nr_valid_paths)) अणु
		spin_lock_irqsave(&m->lock, flags);
		clear_bit(MPATHF_QUEUE_IO, &m->flags);
		spin_unlock_irqrestore(&m->lock, flags);
		जाओ failed;
	पूर्ण

	/* Were we inकाष्ठाed to चयन PG? */
	अगर (READ_ONCE(m->next_pg)) अणु
		spin_lock_irqsave(&m->lock, flags);
		pg = m->next_pg;
		अगर (!pg) अणु
			spin_unlock_irqrestore(&m->lock, flags);
			जाओ check_current_pg;
		पूर्ण
		m->next_pg = शून्य;
		spin_unlock_irqrestore(&m->lock, flags);
		pgpath = choose_path_in_pg(m, pg, nr_bytes);
		अगर (!IS_ERR_OR_शून्य(pgpath))
			वापस pgpath;
	पूर्ण

	/* Don't change PG until it has no reमुख्यing paths */
check_current_pg:
	pg = READ_ONCE(m->current_pg);
	अगर (pg) अणु
		pgpath = choose_path_in_pg(m, pg, nr_bytes);
		अगर (!IS_ERR_OR_शून्य(pgpath))
			वापस pgpath;
	पूर्ण

	/*
	 * Loop through priority groups until we find a valid path.
	 * First समय we skip PGs marked 'bypassed'.
	 * Second समय we only try the ones we skipped, but set
	 * pg_init_delay_retry so we करो not hammer controllers.
	 */
	करो अणु
		list_क्रम_each_entry(pg, &m->priority_groups, list) अणु
			अगर (pg->bypassed == !!bypassed)
				जारी;
			pgpath = choose_path_in_pg(m, pg, nr_bytes);
			अगर (!IS_ERR_OR_शून्य(pgpath)) अणु
				अगर (!bypassed) अणु
					spin_lock_irqsave(&m->lock, flags);
					set_bit(MPATHF_PG_INIT_DELAY_RETRY, &m->flags);
					spin_unlock_irqrestore(&m->lock, flags);
				पूर्ण
				वापस pgpath;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (bypassed--);

failed:
	spin_lock_irqsave(&m->lock, flags);
	m->current_pgpath = शून्य;
	m->current_pg = शून्य;
	spin_unlock_irqrestore(&m->lock, flags);

	वापस शून्य;
पूर्ण

/*
 * dm_report_EIO() is a macro instead of a function to make pr_debug_ratelimited()
 * report the function name and line number of the function from which
 * it has been invoked.
 */
#घोषणा dm_report_EIO(m)						\
करो अणु									\
	DMDEBUG_LIMIT("%s: returning EIO; QIFNP = %d; SQIFNP = %d; DNFS = %d", \
		      dm_table_device_name((m)->ti->table),		\
		      test_bit(MPATHF_QUEUE_IF_NO_PATH, &(m)->flags),	\
		      test_bit(MPATHF_SAVED_QUEUE_IF_NO_PATH, &(m)->flags), \
		      dm_noflush_suspending((m)->ti));			\
पूर्ण जबतक (0)

/*
 * Check whether bios must be queued in the device-mapper core rather
 * than here in the target.
 */
अटल bool __must_push_back(काष्ठा multipath *m)
अणु
	वापस dm_noflush_suspending(m->ti);
पूर्ण

अटल bool must_push_back_rq(काष्ठा multipath *m)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&m->lock, flags);
	ret = (test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags) || __must_push_back(m));
	spin_unlock_irqrestore(&m->lock, flags);

	वापस ret;
पूर्ण

/*
 * Map cloned requests (request-based multipath)
 */
अटल पूर्णांक multipath_clone_and_map(काष्ठा dm_target *ti, काष्ठा request *rq,
				   जोड़ map_info *map_context,
				   काष्ठा request **__clone)
अणु
	काष्ठा multipath *m = ti->निजी;
	माप_प्रकार nr_bytes = blk_rq_bytes(rq);
	काष्ठा pgpath *pgpath;
	काष्ठा block_device *bdev;
	काष्ठा dm_mpath_io *mpio = get_mpio(map_context);
	काष्ठा request_queue *q;
	काष्ठा request *clone;

	/* Do we need to select a new pgpath? */
	pgpath = READ_ONCE(m->current_pgpath);
	अगर (!pgpath || !mpath_द्विगुन_check_test_bit(MPATHF_QUEUE_IO, m))
		pgpath = choose_pgpath(m, nr_bytes);

	अगर (!pgpath) अणु
		अगर (must_push_back_rq(m))
			वापस DM_MAPIO_DELAY_REQUEUE;
		dm_report_EIO(m);	/* Failed */
		वापस DM_MAPIO_KILL;
	पूर्ण अन्यथा अगर (mpath_द्विगुन_check_test_bit(MPATHF_QUEUE_IO, m) ||
		   mpath_द्विगुन_check_test_bit(MPATHF_PG_INIT_REQUIRED, m)) अणु
		pg_init_all_paths(m);
		वापस DM_MAPIO_DELAY_REQUEUE;
	पूर्ण

	mpio->pgpath = pgpath;
	mpio->nr_bytes = nr_bytes;

	bdev = pgpath->path.dev->bdev;
	q = bdev_get_queue(bdev);
	clone = blk_get_request(q, rq->cmd_flags | REQ_NOMERGE,
			BLK_MQ_REQ_NOWAIT);
	अगर (IS_ERR(clone)) अणु
		/* EBUSY, ENODEV or EWOULDBLOCK: requeue */
		अगर (blk_queue_dying(q)) अणु
			atomic_inc(&m->pg_init_in_progress);
			activate_or_offline_path(pgpath);
			वापस DM_MAPIO_DELAY_REQUEUE;
		पूर्ण

		/*
		 * blk-mq's SCHED_RESTART can cover this requeue, so we
		 * needn't deal with it by DELAY_REQUEUE. More importantly,
		 * we have to वापस DM_MAPIO_REQUEUE so that blk-mq can
		 * get the queue busy feedback (via BLK_STS_RESOURCE),
		 * otherwise I/O merging can suffer.
		 */
		वापस DM_MAPIO_REQUEUE;
	पूर्ण
	clone->bio = clone->biotail = शून्य;
	clone->rq_disk = bdev->bd_disk;
	clone->cmd_flags |= REQ_FAILFAST_TRANSPORT;
	*__clone = clone;

	अगर (pgpath->pg->ps.type->start_io)
		pgpath->pg->ps.type->start_io(&pgpath->pg->ps,
					      &pgpath->path,
					      nr_bytes);
	वापस DM_MAPIO_REMAPPED;
पूर्ण

अटल व्योम multipath_release_clone(काष्ठा request *clone,
				    जोड़ map_info *map_context)
अणु
	अगर (unlikely(map_context)) अणु
		/*
		 * non-शून्य map_context means caller is still map
		 * method; must unकरो multipath_clone_and_map()
		 */
		काष्ठा dm_mpath_io *mpio = get_mpio(map_context);
		काष्ठा pgpath *pgpath = mpio->pgpath;

		अगर (pgpath && pgpath->pg->ps.type->end_io)
			pgpath->pg->ps.type->end_io(&pgpath->pg->ps,
						    &pgpath->path,
						    mpio->nr_bytes,
						    clone->io_start_समय_ns);
	पूर्ण

	blk_put_request(clone);
पूर्ण

/*
 * Map cloned bios (bio-based multipath)
 */

अटल व्योम __multipath_queue_bio(काष्ठा multipath *m, काष्ठा bio *bio)
अणु
	/* Queue क्रम the daemon to resubmit */
	bio_list_add(&m->queued_bios, bio);
	अगर (!test_bit(MPATHF_QUEUE_IO, &m->flags))
		queue_work(kmultipathd, &m->process_queued_bios);
पूर्ण

अटल व्योम multipath_queue_bio(काष्ठा multipath *m, काष्ठा bio *bio)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&m->lock, flags);
	__multipath_queue_bio(m, bio);
	spin_unlock_irqrestore(&m->lock, flags);
पूर्ण

अटल काष्ठा pgpath *__map_bio(काष्ठा multipath *m, काष्ठा bio *bio)
अणु
	काष्ठा pgpath *pgpath;
	अचिन्हित दीर्घ flags;

	/* Do we need to select a new pgpath? */
	pgpath = READ_ONCE(m->current_pgpath);
	अगर (!pgpath || !mpath_द्विगुन_check_test_bit(MPATHF_QUEUE_IO, m))
		pgpath = choose_pgpath(m, bio->bi_iter.bi_size);

	अगर (!pgpath) अणु
		spin_lock_irqsave(&m->lock, flags);
		अगर (test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags)) अणु
			__multipath_queue_bio(m, bio);
			pgpath = ERR_PTR(-EAGAIN);
		पूर्ण
		spin_unlock_irqrestore(&m->lock, flags);

	पूर्ण अन्यथा अगर (mpath_द्विगुन_check_test_bit(MPATHF_QUEUE_IO, m) ||
		   mpath_द्विगुन_check_test_bit(MPATHF_PG_INIT_REQUIRED, m)) अणु
		multipath_queue_bio(m, bio);
		pg_init_all_paths(m);
		वापस ERR_PTR(-EAGAIN);
	पूर्ण

	वापस pgpath;
पूर्ण

अटल पूर्णांक __multipath_map_bio(काष्ठा multipath *m, काष्ठा bio *bio,
			       काष्ठा dm_mpath_io *mpio)
अणु
	काष्ठा pgpath *pgpath = __map_bio(m, bio);

	अगर (IS_ERR(pgpath))
		वापस DM_MAPIO_SUBMITTED;

	अगर (!pgpath) अणु
		अगर (__must_push_back(m))
			वापस DM_MAPIO_REQUEUE;
		dm_report_EIO(m);
		वापस DM_MAPIO_KILL;
	पूर्ण

	mpio->pgpath = pgpath;

	bio->bi_status = 0;
	bio_set_dev(bio, pgpath->path.dev->bdev);
	bio->bi_opf |= REQ_FAILFAST_TRANSPORT;

	अगर (pgpath->pg->ps.type->start_io)
		pgpath->pg->ps.type->start_io(&pgpath->pg->ps,
					      &pgpath->path,
					      mpio->nr_bytes);
	वापस DM_MAPIO_REMAPPED;
पूर्ण

अटल पूर्णांक multipath_map_bio(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	काष्ठा multipath *m = ti->निजी;
	काष्ठा dm_mpath_io *mpio = शून्य;

	multipath_init_per_bio_data(bio, &mpio);
	वापस __multipath_map_bio(m, bio, mpio);
पूर्ण

अटल व्योम process_queued_io_list(काष्ठा multipath *m)
अणु
	अगर (m->queue_mode == DM_TYPE_REQUEST_BASED)
		dm_mq_kick_requeue_list(dm_table_get_md(m->ti->table));
	अन्यथा अगर (m->queue_mode == DM_TYPE_BIO_BASED)
		queue_work(kmultipathd, &m->process_queued_bios);
पूर्ण

अटल व्योम process_queued_bios(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ flags;
	काष्ठा bio *bio;
	काष्ठा bio_list bios;
	काष्ठा blk_plug plug;
	काष्ठा multipath *m =
		container_of(work, काष्ठा multipath, process_queued_bios);

	bio_list_init(&bios);

	spin_lock_irqsave(&m->lock, flags);

	अगर (bio_list_empty(&m->queued_bios)) अणु
		spin_unlock_irqrestore(&m->lock, flags);
		वापस;
	पूर्ण

	bio_list_merge(&bios, &m->queued_bios);
	bio_list_init(&m->queued_bios);

	spin_unlock_irqrestore(&m->lock, flags);

	blk_start_plug(&plug);
	जबतक ((bio = bio_list_pop(&bios))) अणु
		काष्ठा dm_mpath_io *mpio = get_mpio_from_bio(bio);
		dm_bio_restore(get_bio_details_from_mpio(mpio), bio);
		r = __multipath_map_bio(m, bio, mpio);
		चयन (r) अणु
		हाल DM_MAPIO_KILL:
			bio->bi_status = BLK_STS_IOERR;
			bio_endio(bio);
			अवरोध;
		हाल DM_MAPIO_REQUEUE:
			bio->bi_status = BLK_STS_DM_REQUEUE;
			bio_endio(bio);
			अवरोध;
		हाल DM_MAPIO_REMAPPED:
			submit_bio_noacct(bio);
			अवरोध;
		हाल DM_MAPIO_SUBMITTED:
			अवरोध;
		शेष:
			WARN_ONCE(true, "__multipath_map_bio() returned %d\n", r);
		पूर्ण
	पूर्ण
	blk_finish_plug(&plug);
पूर्ण

/*
 * If we run out of usable paths, should we queue I/O or error it?
 */
अटल पूर्णांक queue_अगर_no_path(काष्ठा multipath *m, bool queue_अगर_no_path,
			    bool save_old_value, स्थिर अक्षर *caller)
अणु
	अचिन्हित दीर्घ flags;
	bool queue_अगर_no_path_bit, saved_queue_अगर_no_path_bit;
	स्थिर अक्षर *dm_dev_name = dm_table_device_name(m->ti->table);

	DMDEBUG("%s: %s caller=%s queue_if_no_path=%d save_old_value=%d",
		dm_dev_name, __func__, caller, queue_अगर_no_path, save_old_value);

	spin_lock_irqsave(&m->lock, flags);

	queue_अगर_no_path_bit = test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags);
	saved_queue_अगर_no_path_bit = test_bit(MPATHF_SAVED_QUEUE_IF_NO_PATH, &m->flags);

	अगर (save_old_value) अणु
		अगर (unlikely(!queue_अगर_no_path_bit && saved_queue_अगर_no_path_bit)) अणु
			DMERR("%s: QIFNP disabled but saved as enabled, saving again loses state, not saving!",
			      dm_dev_name);
		पूर्ण अन्यथा
			assign_bit(MPATHF_SAVED_QUEUE_IF_NO_PATH, &m->flags, queue_अगर_no_path_bit);
	पूर्ण अन्यथा अगर (!queue_अगर_no_path && saved_queue_अगर_no_path_bit) अणु
		/* due to "fail_if_no_path" message, need to honor it. */
		clear_bit(MPATHF_SAVED_QUEUE_IF_NO_PATH, &m->flags);
	पूर्ण
	assign_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags, queue_अगर_no_path);

	DMDEBUG("%s: after %s changes; QIFNP = %d; SQIFNP = %d; DNFS = %d",
		dm_dev_name, __func__,
		test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags),
		test_bit(MPATHF_SAVED_QUEUE_IF_NO_PATH, &m->flags),
		dm_noflush_suspending(m->ti));

	spin_unlock_irqrestore(&m->lock, flags);

	अगर (!queue_अगर_no_path) अणु
		dm_table_run_md_queue_async(m->ti->table);
		process_queued_io_list(m);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * If the queue_अगर_no_path समयout fires, turn off queue_अगर_no_path and
 * process any queued I/O.
 */
अटल व्योम queue_अगर_no_path_समयout_work(काष्ठा समयr_list *t)
अणु
	काष्ठा multipath *m = from_समयr(m, t, nopath_समयr);

	DMWARN("queue_if_no_path timeout on %s, failing queued IO",
	       dm_table_device_name(m->ti->table));
	queue_अगर_no_path(m, false, false, __func__);
पूर्ण

/*
 * Enable the queue_अगर_no_path समयout अगर necessary.
 * Called with m->lock held.
 */
अटल व्योम enable_nopath_समयout(काष्ठा multipath *m)
अणु
	अचिन्हित दीर्घ queue_अगर_no_path_समयout =
		READ_ONCE(queue_अगर_no_path_समयout_secs) * HZ;

	lockdep_निश्चित_held(&m->lock);

	अगर (queue_अगर_no_path_समयout > 0 &&
	    atomic_पढ़ो(&m->nr_valid_paths) == 0 &&
	    test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags)) अणु
		mod_समयr(&m->nopath_समयr,
			  jअगरfies + queue_अगर_no_path_समयout);
	पूर्ण
पूर्ण

अटल व्योम disable_nopath_समयout(काष्ठा multipath *m)
अणु
	del_समयr_sync(&m->nopath_समयr);
पूर्ण

/*
 * An event is triggered whenever a path is taken out of use.
 * Includes path failure and PG bypass.
 */
अटल व्योम trigger_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा multipath *m =
		container_of(work, काष्ठा multipath, trigger_event);

	dm_table_event(m->ti->table);
पूर्ण

/*-----------------------------------------------------------------
 * Conकाष्ठाor/argument parsing:
 * <#multipath feature args> [<arg>]*
 * <#hw_handler args> [hw_handler [<arg>]*]
 * <#priority groups>
 * <initial priority group>
 *     [<selector> <#selector args> [<arg>]*
 *      <#paths> <#per-path selector args>
 *         [<path> [<arg>]* ]+ ]+
 *---------------------------------------------------------------*/
अटल पूर्णांक parse_path_selector(काष्ठा dm_arg_set *as, काष्ठा priority_group *pg,
			       काष्ठा dm_target *ti)
अणु
	पूर्णांक r;
	काष्ठा path_selector_type *pst;
	अचिन्हित ps_argc;

	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, 1024, "invalid number of path selector args"पूर्ण,
	पूर्ण;

	pst = dm_get_path_selector(dm_shअगरt_arg(as));
	अगर (!pst) अणु
		ti->error = "unknown path selector type";
		वापस -EINVAL;
	पूर्ण

	r = dm_पढ़ो_arg_group(_args, as, &ps_argc, &ti->error);
	अगर (r) अणु
		dm_put_path_selector(pst);
		वापस -EINVAL;
	पूर्ण

	r = pst->create(&pg->ps, ps_argc, as->argv);
	अगर (r) अणु
		dm_put_path_selector(pst);
		ti->error = "path selector constructor failed";
		वापस r;
	पूर्ण

	pg->ps.type = pst;
	dm_consume_args(as, ps_argc);

	वापस 0;
पूर्ण

अटल पूर्णांक setup_scsi_dh(काष्ठा block_device *bdev, काष्ठा multipath *m,
			 स्थिर अक्षर **attached_handler_name, अक्षर **error)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	पूर्णांक r;

	अगर (mpath_द्विगुन_check_test_bit(MPATHF_RETAIN_ATTACHED_HW_HANDLER, m)) अणु
retain:
		अगर (*attached_handler_name) अणु
			/*
			 * Clear any hw_handler_params associated with a
			 * handler that isn't alपढ़ोy attached.
			 */
			अगर (m->hw_handler_name && म_भेद(*attached_handler_name, m->hw_handler_name)) अणु
				kमुक्त(m->hw_handler_params);
				m->hw_handler_params = शून्य;
			पूर्ण

			/*
			 * Reset hw_handler_name to match the attached handler
			 *
			 * NB. This modअगरies the table line to show the actual
			 * handler instead of the original table passed in.
			 */
			kमुक्त(m->hw_handler_name);
			m->hw_handler_name = *attached_handler_name;
			*attached_handler_name = शून्य;
		पूर्ण
	पूर्ण

	अगर (m->hw_handler_name) अणु
		r = scsi_dh_attach(q, m->hw_handler_name);
		अगर (r == -EBUSY) अणु
			अक्षर b[BDEVNAME_SIZE];

			prपूर्णांकk(KERN_INFO "dm-mpath: retaining handler on device %s\n",
			       bdevname(bdev, b));
			जाओ retain;
		पूर्ण
		अगर (r < 0) अणु
			*error = "error attaching hardware handler";
			वापस r;
		पूर्ण

		अगर (m->hw_handler_params) अणु
			r = scsi_dh_set_params(q, m->hw_handler_params);
			अगर (r < 0) अणु
				*error = "unable to set hardware handler parameters";
				वापस r;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pgpath *parse_path(काष्ठा dm_arg_set *as, काष्ठा path_selector *ps,
				 काष्ठा dm_target *ti)
अणु
	पूर्णांक r;
	काष्ठा pgpath *p;
	काष्ठा multipath *m = ti->निजी;
	काष्ठा request_queue *q;
	स्थिर अक्षर *attached_handler_name = शून्य;

	/* we need at least a path arg */
	अगर (as->argc < 1) अणु
		ti->error = "no device given";
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	p = alloc_pgpath();
	अगर (!p)
		वापस ERR_PTR(-ENOMEM);

	r = dm_get_device(ti, dm_shअगरt_arg(as), dm_table_get_mode(ti->table),
			  &p->path.dev);
	अगर (r) अणु
		ti->error = "error getting device";
		जाओ bad;
	पूर्ण

	q = bdev_get_queue(p->path.dev->bdev);
	attached_handler_name = scsi_dh_attached_handler_name(q, GFP_KERNEL);
	अगर (attached_handler_name || m->hw_handler_name) अणु
		INIT_DELAYED_WORK(&p->activate_path, activate_path_work);
		r = setup_scsi_dh(p->path.dev->bdev, m, &attached_handler_name, &ti->error);
		kमुक्त(attached_handler_name);
		अगर (r) अणु
			dm_put_device(ti, p->path.dev);
			जाओ bad;
		पूर्ण
	पूर्ण

	r = ps->type->add_path(ps, &p->path, as->argc, as->argv, &ti->error);
	अगर (r) अणु
		dm_put_device(ti, p->path.dev);
		जाओ bad;
	पूर्ण

	वापस p;
 bad:
	मुक्त_pgpath(p);
	वापस ERR_PTR(r);
पूर्ण

अटल काष्ठा priority_group *parse_priority_group(काष्ठा dm_arg_set *as,
						   काष्ठा multipath *m)
अणु
	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु1, 1024, "invalid number of paths"पूर्ण,
		अणु0, 1024, "invalid number of selector args"पूर्ण
	पूर्ण;

	पूर्णांक r;
	अचिन्हित i, nr_selector_args, nr_args;
	काष्ठा priority_group *pg;
	काष्ठा dm_target *ti = m->ti;

	अगर (as->argc < 2) अणु
		as->argc = 0;
		ti->error = "not enough priority group arguments";
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pg = alloc_priority_group();
	अगर (!pg) अणु
		ti->error = "couldn't allocate priority group";
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	pg->m = m;

	r = parse_path_selector(as, pg, ti);
	अगर (r)
		जाओ bad;

	/*
	 * पढ़ो the paths
	 */
	r = dm_पढ़ो_arg(_args, as, &pg->nr_pgpaths, &ti->error);
	अगर (r)
		जाओ bad;

	r = dm_पढ़ो_arg(_args + 1, as, &nr_selector_args, &ti->error);
	अगर (r)
		जाओ bad;

	nr_args = 1 + nr_selector_args;
	क्रम (i = 0; i < pg->nr_pgpaths; i++) अणु
		काष्ठा pgpath *pgpath;
		काष्ठा dm_arg_set path_args;

		अगर (as->argc < nr_args) अणु
			ti->error = "not enough path parameters";
			r = -EINVAL;
			जाओ bad;
		पूर्ण

		path_args.argc = nr_args;
		path_args.argv = as->argv;

		pgpath = parse_path(&path_args, &pg->ps, ti);
		अगर (IS_ERR(pgpath)) अणु
			r = PTR_ERR(pgpath);
			जाओ bad;
		पूर्ण

		pgpath->pg = pg;
		list_add_tail(&pgpath->list, &pg->pgpaths);
		dm_consume_args(as, nr_args);
	पूर्ण

	वापस pg;

 bad:
	मुक्त_priority_group(pg, ti);
	वापस ERR_PTR(r);
पूर्ण

अटल पूर्णांक parse_hw_handler(काष्ठा dm_arg_set *as, काष्ठा multipath *m)
अणु
	अचिन्हित hw_argc;
	पूर्णांक ret;
	काष्ठा dm_target *ti = m->ti;

	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, 1024, "invalid number of hardware handler args"पूर्ण,
	पूर्ण;

	अगर (dm_पढ़ो_arg_group(_args, as, &hw_argc, &ti->error))
		वापस -EINVAL;

	अगर (!hw_argc)
		वापस 0;

	अगर (m->queue_mode == DM_TYPE_BIO_BASED) अणु
		dm_consume_args(as, hw_argc);
		DMERR("bio-based multipath doesn't allow hardware handler args");
		वापस 0;
	पूर्ण

	m->hw_handler_name = kstrdup(dm_shअगरt_arg(as), GFP_KERNEL);
	अगर (!m->hw_handler_name)
		वापस -EINVAL;

	अगर (hw_argc > 1) अणु
		अक्षर *p;
		पूर्णांक i, j, len = 4;

		क्रम (i = 0; i <= hw_argc - 2; i++)
			len += म_माप(as->argv[i]) + 1;
		p = m->hw_handler_params = kzalloc(len, GFP_KERNEL);
		अगर (!p) अणु
			ti->error = "memory allocation failed";
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण
		j = प्र_लिखो(p, "%d", hw_argc - 1);
		क्रम (i = 0, p+=j+1; i <= hw_argc - 2; i++, p+=j+1)
			j = प्र_लिखो(p, "%s", as->argv[i]);
	पूर्ण
	dm_consume_args(as, hw_argc - 1);

	वापस 0;
fail:
	kमुक्त(m->hw_handler_name);
	m->hw_handler_name = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक parse_features(काष्ठा dm_arg_set *as, काष्ठा multipath *m)
अणु
	पूर्णांक r;
	अचिन्हित argc;
	काष्ठा dm_target *ti = m->ti;
	स्थिर अक्षर *arg_name;

	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, 8, "invalid number of feature args"पूर्ण,
		अणु1, 50, "pg_init_retries must be between 1 and 50"पूर्ण,
		अणु0, 60000, "pg_init_delay_msecs must be between 0 and 60000"पूर्ण,
	पूर्ण;

	r = dm_पढ़ो_arg_group(_args, as, &argc, &ti->error);
	अगर (r)
		वापस -EINVAL;

	अगर (!argc)
		वापस 0;

	करो अणु
		arg_name = dm_shअगरt_arg(as);
		argc--;

		अगर (!strहालcmp(arg_name, "queue_if_no_path")) अणु
			r = queue_अगर_no_path(m, true, false, __func__);
			जारी;
		पूर्ण

		अगर (!strहालcmp(arg_name, "retain_attached_hw_handler")) अणु
			set_bit(MPATHF_RETAIN_ATTACHED_HW_HANDLER, &m->flags);
			जारी;
		पूर्ण

		अगर (!strहालcmp(arg_name, "pg_init_retries") &&
		    (argc >= 1)) अणु
			r = dm_पढ़ो_arg(_args + 1, as, &m->pg_init_retries, &ti->error);
			argc--;
			जारी;
		पूर्ण

		अगर (!strहालcmp(arg_name, "pg_init_delay_msecs") &&
		    (argc >= 1)) अणु
			r = dm_पढ़ो_arg(_args + 2, as, &m->pg_init_delay_msecs, &ti->error);
			argc--;
			जारी;
		पूर्ण

		अगर (!strहालcmp(arg_name, "queue_mode") &&
		    (argc >= 1)) अणु
			स्थिर अक्षर *queue_mode_name = dm_shअगरt_arg(as);

			अगर (!strहालcmp(queue_mode_name, "bio"))
				m->queue_mode = DM_TYPE_BIO_BASED;
			अन्यथा अगर (!strहालcmp(queue_mode_name, "rq") ||
				 !strहालcmp(queue_mode_name, "mq"))
				m->queue_mode = DM_TYPE_REQUEST_BASED;
			अन्यथा अणु
				ti->error = "Unknown 'queue_mode' requested";
				r = -EINVAL;
			पूर्ण
			argc--;
			जारी;
		पूर्ण

		ti->error = "Unrecognised multipath feature request";
		r = -EINVAL;
	पूर्ण जबतक (argc && !r);

	वापस r;
पूर्ण

अटल पूर्णांक multipath_ctr(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv)
अणु
	/* target arguments */
	अटल स्थिर काष्ठा dm_arg _args[] = अणु
		अणु0, 1024, "invalid number of priority groups"पूर्ण,
		अणु0, 1024, "invalid initial priority group number"पूर्ण,
	पूर्ण;

	पूर्णांक r;
	काष्ठा multipath *m;
	काष्ठा dm_arg_set as;
	अचिन्हित pg_count = 0;
	अचिन्हित next_pg_num;
	अचिन्हित दीर्घ flags;

	as.argc = argc;
	as.argv = argv;

	m = alloc_multipath(ti);
	अगर (!m) अणु
		ti->error = "can't allocate multipath";
		वापस -EINVAL;
	पूर्ण

	r = parse_features(&as, m);
	अगर (r)
		जाओ bad;

	r = alloc_multipath_stage2(ti, m);
	अगर (r)
		जाओ bad;

	r = parse_hw_handler(&as, m);
	अगर (r)
		जाओ bad;

	r = dm_पढ़ो_arg(_args, &as, &m->nr_priority_groups, &ti->error);
	अगर (r)
		जाओ bad;

	r = dm_पढ़ो_arg(_args + 1, &as, &next_pg_num, &ti->error);
	अगर (r)
		जाओ bad;

	अगर ((!m->nr_priority_groups && next_pg_num) ||
	    (m->nr_priority_groups && !next_pg_num)) अणु
		ti->error = "invalid initial priority group";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	/* parse the priority groups */
	जबतक (as.argc) अणु
		काष्ठा priority_group *pg;
		अचिन्हित nr_valid_paths = atomic_पढ़ो(&m->nr_valid_paths);

		pg = parse_priority_group(&as, m);
		अगर (IS_ERR(pg)) अणु
			r = PTR_ERR(pg);
			जाओ bad;
		पूर्ण

		nr_valid_paths += pg->nr_pgpaths;
		atomic_set(&m->nr_valid_paths, nr_valid_paths);

		list_add_tail(&pg->list, &m->priority_groups);
		pg_count++;
		pg->pg_num = pg_count;
		अगर (!--next_pg_num)
			m->next_pg = pg;
	पूर्ण

	अगर (pg_count != m->nr_priority_groups) अणु
		ti->error = "priority group count mismatch";
		r = -EINVAL;
		जाओ bad;
	पूर्ण

	spin_lock_irqsave(&m->lock, flags);
	enable_nopath_समयout(m);
	spin_unlock_irqrestore(&m->lock, flags);

	ti->num_flush_bios = 1;
	ti->num_discard_bios = 1;
	ti->num_ग_लिखो_same_bios = 1;
	ti->num_ग_लिखो_zeroes_bios = 1;
	अगर (m->queue_mode == DM_TYPE_BIO_BASED)
		ti->per_io_data_size = multipath_per_bio_data_size();
	अन्यथा
		ti->per_io_data_size = माप(काष्ठा dm_mpath_io);

	वापस 0;

 bad:
	मुक्त_multipath(m);
	वापस r;
पूर्ण

अटल व्योम multipath_रुको_क्रम_pg_init_completion(काष्ठा multipath *m)
अणु
	DEFINE_WAIT(रुको);

	जबतक (1) अणु
		prepare_to_रुको(&m->pg_init_रुको, &रुको, TASK_UNINTERRUPTIBLE);

		अगर (!atomic_पढ़ो(&m->pg_init_in_progress))
			अवरोध;

		io_schedule();
	पूर्ण
	finish_रुको(&m->pg_init_रुको, &रुको);
पूर्ण

अटल व्योम flush_multipath_work(काष्ठा multipath *m)
अणु
	अगर (m->hw_handler_name) अणु
		अचिन्हित दीर्घ flags;

		अगर (!atomic_पढ़ो(&m->pg_init_in_progress))
			जाओ skip;

		spin_lock_irqsave(&m->lock, flags);
		अगर (atomic_पढ़ो(&m->pg_init_in_progress) &&
		    !test_and_set_bit(MPATHF_PG_INIT_DISABLED, &m->flags)) अणु
			spin_unlock_irqrestore(&m->lock, flags);

			flush_workqueue(kmpath_handlerd);
			multipath_रुको_क्रम_pg_init_completion(m);

			spin_lock_irqsave(&m->lock, flags);
			clear_bit(MPATHF_PG_INIT_DISABLED, &m->flags);
		पूर्ण
		spin_unlock_irqrestore(&m->lock, flags);
	पूर्ण
skip:
	अगर (m->queue_mode == DM_TYPE_BIO_BASED)
		flush_work(&m->process_queued_bios);
	flush_work(&m->trigger_event);
पूर्ण

अटल व्योम multipath_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा multipath *m = ti->निजी;

	disable_nopath_समयout(m);
	flush_multipath_work(m);
	मुक्त_multipath(m);
पूर्ण

/*
 * Take a path out of use.
 */
अटल पूर्णांक fail_path(काष्ठा pgpath *pgpath)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा multipath *m = pgpath->pg->m;

	spin_lock_irqsave(&m->lock, flags);

	अगर (!pgpath->is_active)
		जाओ out;

	DMWARN("%s: Failing path %s.",
	       dm_table_device_name(m->ti->table),
	       pgpath->path.dev->name);

	pgpath->pg->ps.type->fail_path(&pgpath->pg->ps, &pgpath->path);
	pgpath->is_active = false;
	pgpath->fail_count++;

	atomic_dec(&m->nr_valid_paths);

	अगर (pgpath == m->current_pgpath)
		m->current_pgpath = शून्य;

	dm_path_uevent(DM_UEVENT_PATH_FAILED, m->ti,
		       pgpath->path.dev->name, atomic_पढ़ो(&m->nr_valid_paths));

	schedule_work(&m->trigger_event);

	enable_nopath_समयout(m);

out:
	spin_unlock_irqrestore(&m->lock, flags);

	वापस 0;
पूर्ण

/*
 * Reinstate a previously-failed path
 */
अटल पूर्णांक reinstate_path(काष्ठा pgpath *pgpath)
अणु
	पूर्णांक r = 0, run_queue = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा multipath *m = pgpath->pg->m;
	अचिन्हित nr_valid_paths;

	spin_lock_irqsave(&m->lock, flags);

	अगर (pgpath->is_active)
		जाओ out;

	DMWARN("%s: Reinstating path %s.",
	       dm_table_device_name(m->ti->table),
	       pgpath->path.dev->name);

	r = pgpath->pg->ps.type->reinstate_path(&pgpath->pg->ps, &pgpath->path);
	अगर (r)
		जाओ out;

	pgpath->is_active = true;

	nr_valid_paths = atomic_inc_वापस(&m->nr_valid_paths);
	अगर (nr_valid_paths == 1) अणु
		m->current_pgpath = शून्य;
		run_queue = 1;
	पूर्ण अन्यथा अगर (m->hw_handler_name && (m->current_pg == pgpath->pg)) अणु
		अगर (queue_work(kmpath_handlerd, &pgpath->activate_path.work))
			atomic_inc(&m->pg_init_in_progress);
	पूर्ण

	dm_path_uevent(DM_UEVENT_PATH_REINSTATED, m->ti,
		       pgpath->path.dev->name, nr_valid_paths);

	schedule_work(&m->trigger_event);

out:
	spin_unlock_irqrestore(&m->lock, flags);
	अगर (run_queue) अणु
		dm_table_run_md_queue_async(m->ti->table);
		process_queued_io_list(m);
	पूर्ण

	अगर (pgpath->is_active)
		disable_nopath_समयout(m);

	वापस r;
पूर्ण

/*
 * Fail or reinstate all paths that match the provided काष्ठा dm_dev.
 */
अटल पूर्णांक action_dev(काष्ठा multipath *m, काष्ठा dm_dev *dev,
		      action_fn action)
अणु
	पूर्णांक r = -EINVAL;
	काष्ठा pgpath *pgpath;
	काष्ठा priority_group *pg;

	list_क्रम_each_entry(pg, &m->priority_groups, list) अणु
		list_क्रम_each_entry(pgpath, &pg->pgpaths, list) अणु
			अगर (pgpath->path.dev == dev)
				r = action(pgpath);
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

/*
 * Temporarily try to aव्योम having to use the specअगरied PG
 */
अटल व्योम bypass_pg(काष्ठा multipath *m, काष्ठा priority_group *pg,
		      bool bypassed)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&m->lock, flags);

	pg->bypassed = bypassed;
	m->current_pgpath = शून्य;
	m->current_pg = शून्य;

	spin_unlock_irqrestore(&m->lock, flags);

	schedule_work(&m->trigger_event);
पूर्ण

/*
 * Switch to using the specअगरied PG from the next I/O that माला_लो mapped
 */
अटल पूर्णांक चयन_pg_num(काष्ठा multipath *m, स्थिर अक्षर *pgstr)
अणु
	काष्ठा priority_group *pg;
	अचिन्हित pgnum;
	अचिन्हित दीर्घ flags;
	अक्षर dummy;

	अगर (!pgstr || (माला_पूछो(pgstr, "%u%c", &pgnum, &dummy) != 1) || !pgnum ||
	    !m->nr_priority_groups || (pgnum > m->nr_priority_groups)) अणु
		DMWARN("invalid PG number supplied to switch_pg_num");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&m->lock, flags);
	list_क्रम_each_entry(pg, &m->priority_groups, list) अणु
		pg->bypassed = false;
		अगर (--pgnum)
			जारी;

		m->current_pgpath = शून्य;
		m->current_pg = शून्य;
		m->next_pg = pg;
	पूर्ण
	spin_unlock_irqrestore(&m->lock, flags);

	schedule_work(&m->trigger_event);
	वापस 0;
पूर्ण

/*
 * Set/clear bypassed status of a PG.
 * PGs are numbered upwards from 1 in the order they were declared.
 */
अटल पूर्णांक bypass_pg_num(काष्ठा multipath *m, स्थिर अक्षर *pgstr, bool bypassed)
अणु
	काष्ठा priority_group *pg;
	अचिन्हित pgnum;
	अक्षर dummy;

	अगर (!pgstr || (माला_पूछो(pgstr, "%u%c", &pgnum, &dummy) != 1) || !pgnum ||
	    !m->nr_priority_groups || (pgnum > m->nr_priority_groups)) अणु
		DMWARN("invalid PG number supplied to bypass_pg");
		वापस -EINVAL;
	पूर्ण

	list_क्रम_each_entry(pg, &m->priority_groups, list) अणु
		अगर (!--pgnum)
			अवरोध;
	पूर्ण

	bypass_pg(m, pg, bypassed);
	वापस 0;
पूर्ण

/*
 * Should we retry pg_init immediately?
 */
अटल bool pg_init_limit_reached(काष्ठा multipath *m, काष्ठा pgpath *pgpath)
अणु
	अचिन्हित दीर्घ flags;
	bool limit_reached = false;

	spin_lock_irqsave(&m->lock, flags);

	अगर (atomic_पढ़ो(&m->pg_init_count) <= m->pg_init_retries &&
	    !test_bit(MPATHF_PG_INIT_DISABLED, &m->flags))
		set_bit(MPATHF_PG_INIT_REQUIRED, &m->flags);
	अन्यथा
		limit_reached = true;

	spin_unlock_irqrestore(&m->lock, flags);

	वापस limit_reached;
पूर्ण

अटल व्योम pg_init_करोne(व्योम *data, पूर्णांक errors)
अणु
	काष्ठा pgpath *pgpath = data;
	काष्ठा priority_group *pg = pgpath->pg;
	काष्ठा multipath *m = pg->m;
	अचिन्हित दीर्घ flags;
	bool delay_retry = false;

	/* device or driver problems */
	चयन (errors) अणु
	हाल SCSI_DH_OK:
		अवरोध;
	हाल SCSI_DH_NOSYS:
		अगर (!m->hw_handler_name) अणु
			errors = 0;
			अवरोध;
		पूर्ण
		DMERR("Could not failover the device: Handler scsi_dh_%s "
		      "Error %d.", m->hw_handler_name, errors);
		/*
		 * Fail path क्रम now, so we करो not ping pong
		 */
		fail_path(pgpath);
		अवरोध;
	हाल SCSI_DH_DEV_TEMP_BUSY:
		/*
		 * Probably करोing something like FW upgrade on the
		 * controller so try the other pg.
		 */
		bypass_pg(m, pg, true);
		अवरोध;
	हाल SCSI_DH_RETRY:
		/* Wait beक्रमe retrying. */
		delay_retry = true;
		fallthrough;
	हाल SCSI_DH_IMM_RETRY:
	हाल SCSI_DH_RES_TEMP_UNAVAIL:
		अगर (pg_init_limit_reached(m, pgpath))
			fail_path(pgpath);
		errors = 0;
		अवरोध;
	हाल SCSI_DH_DEV_OFFLINED:
	शेष:
		/*
		 * We probably करो not want to fail the path क्रम a device
		 * error, but this is what the old dm did. In future
		 * patches we can करो more advanced handling.
		 */
		fail_path(pgpath);
	पूर्ण

	spin_lock_irqsave(&m->lock, flags);
	अगर (errors) अणु
		अगर (pgpath == m->current_pgpath) अणु
			DMERR("Could not failover device. Error %d.", errors);
			m->current_pgpath = शून्य;
			m->current_pg = शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (!test_bit(MPATHF_PG_INIT_REQUIRED, &m->flags))
		pg->bypassed = false;

	अगर (atomic_dec_वापस(&m->pg_init_in_progress) > 0)
		/* Activations of other paths are still on going */
		जाओ out;

	अगर (test_bit(MPATHF_PG_INIT_REQUIRED, &m->flags)) अणु
		अगर (delay_retry)
			set_bit(MPATHF_PG_INIT_DELAY_RETRY, &m->flags);
		अन्यथा
			clear_bit(MPATHF_PG_INIT_DELAY_RETRY, &m->flags);

		अगर (__pg_init_all_paths(m))
			जाओ out;
	पूर्ण
	clear_bit(MPATHF_QUEUE_IO, &m->flags);

	process_queued_io_list(m);

	/*
	 * Wake up any thपढ़ो रुकोing to suspend.
	 */
	wake_up(&m->pg_init_रुको);

out:
	spin_unlock_irqrestore(&m->lock, flags);
पूर्ण

अटल व्योम activate_or_offline_path(काष्ठा pgpath *pgpath)
अणु
	काष्ठा request_queue *q = bdev_get_queue(pgpath->path.dev->bdev);

	अगर (pgpath->is_active && !blk_queue_dying(q))
		scsi_dh_activate(q, pg_init_करोne, pgpath);
	अन्यथा
		pg_init_करोne(pgpath, SCSI_DH_DEV_OFFLINED);
पूर्ण

अटल व्योम activate_path_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pgpath *pgpath =
		container_of(work, काष्ठा pgpath, activate_path.work);

	activate_or_offline_path(pgpath);
पूर्ण

अटल पूर्णांक multipath_end_io(काष्ठा dm_target *ti, काष्ठा request *clone,
			    blk_status_t error, जोड़ map_info *map_context)
अणु
	काष्ठा dm_mpath_io *mpio = get_mpio(map_context);
	काष्ठा pgpath *pgpath = mpio->pgpath;
	पूर्णांक r = DM_ENDIO_DONE;

	/*
	 * We करोn't queue any clone request inside the multipath target
	 * during end I/O handling, since those clone requests करोn't have
	 * bio clones.  If we queue them inside the multipath target,
	 * we need to make bio clones, that requires memory allocation.
	 * (See drivers/md/dm-rq.c:end_clone_bio() about why the clone requests
	 *  करोn't have bio clones.)
	 * Instead of queueing the clone request here, we queue the original
	 * request पूर्णांकo dm core, which will remake a clone request and
	 * clone bios क्रम it and resubmit it later.
	 */
	अगर (error && blk_path_error(error)) अणु
		काष्ठा multipath *m = ti->निजी;

		अगर (error == BLK_STS_RESOURCE)
			r = DM_ENDIO_DELAY_REQUEUE;
		अन्यथा
			r = DM_ENDIO_REQUEUE;

		अगर (pgpath)
			fail_path(pgpath);

		अगर (!atomic_पढ़ो(&m->nr_valid_paths) &&
		    !must_push_back_rq(m)) अणु
			अगर (error == BLK_STS_IOERR)
				dm_report_EIO(m);
			/* complete with the original error */
			r = DM_ENDIO_DONE;
		पूर्ण
	पूर्ण

	अगर (pgpath) अणु
		काष्ठा path_selector *ps = &pgpath->pg->ps;

		अगर (ps->type->end_io)
			ps->type->end_io(ps, &pgpath->path, mpio->nr_bytes,
					 clone->io_start_समय_ns);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक multipath_end_io_bio(काष्ठा dm_target *ti, काष्ठा bio *clone,
				blk_status_t *error)
अणु
	काष्ठा multipath *m = ti->निजी;
	काष्ठा dm_mpath_io *mpio = get_mpio_from_bio(clone);
	काष्ठा pgpath *pgpath = mpio->pgpath;
	अचिन्हित दीर्घ flags;
	पूर्णांक r = DM_ENDIO_DONE;

	अगर (!*error || !blk_path_error(*error))
		जाओ करोne;

	अगर (pgpath)
		fail_path(pgpath);

	अगर (!atomic_पढ़ो(&m->nr_valid_paths)) अणु
		spin_lock_irqsave(&m->lock, flags);
		अगर (!test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags)) अणु
			अगर (__must_push_back(m)) अणु
				r = DM_ENDIO_REQUEUE;
			पूर्ण अन्यथा अणु
				dm_report_EIO(m);
				*error = BLK_STS_IOERR;
			पूर्ण
			spin_unlock_irqrestore(&m->lock, flags);
			जाओ करोne;
		पूर्ण
		spin_unlock_irqrestore(&m->lock, flags);
	पूर्ण

	multipath_queue_bio(m, clone);
	r = DM_ENDIO_INCOMPLETE;
करोne:
	अगर (pgpath) अणु
		काष्ठा path_selector *ps = &pgpath->pg->ps;

		अगर (ps->type->end_io)
			ps->type->end_io(ps, &pgpath->path, mpio->nr_bytes,
					 dm_start_समय_ns_from_clone(clone));
	पूर्ण

	वापस r;
पूर्ण

/*
 * Suspend with flush can't complete until all the I/O is processed
 * so अगर the last path fails we must error any reमुख्यing I/O.
 * - Note that अगर the मुक्तze_bdev fails जबतक suspending, the
 *   queue_अगर_no_path state is lost - userspace should reset it.
 * Otherwise, during noflush suspend, queue_अगर_no_path will not change.
 */
अटल व्योम multipath_presuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा multipath *m = ti->निजी;

	/* FIXME: bio-based shouldn't need to always disable queue_अगर_no_path */
	अगर (m->queue_mode == DM_TYPE_BIO_BASED || !dm_noflush_suspending(m->ti))
		queue_अगर_no_path(m, false, true, __func__);
पूर्ण

अटल व्योम multipath_postsuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा multipath *m = ti->निजी;

	mutex_lock(&m->work_mutex);
	flush_multipath_work(m);
	mutex_unlock(&m->work_mutex);
पूर्ण

/*
 * Restore the queue_अगर_no_path setting.
 */
अटल व्योम multipath_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा multipath *m = ti->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&m->lock, flags);
	अगर (test_bit(MPATHF_SAVED_QUEUE_IF_NO_PATH, &m->flags)) अणु
		set_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags);
		clear_bit(MPATHF_SAVED_QUEUE_IF_NO_PATH, &m->flags);
	पूर्ण

	DMDEBUG("%s: %s finished; QIFNP = %d; SQIFNP = %d",
		dm_table_device_name(m->ti->table), __func__,
		test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags),
		test_bit(MPATHF_SAVED_QUEUE_IF_NO_PATH, &m->flags));

	spin_unlock_irqrestore(&m->lock, flags);
पूर्ण

/*
 * Info output has the following क्रमmat:
 * num_multipath_feature_args [multipath_feature_args]*
 * num_handler_status_args [handler_status_args]*
 * num_groups init_group_number
 *            [A|D|E num_ps_status_args [ps_status_args]*
 *             num_paths num_selector_args
 *             [path_dev A|F fail_count [selector_args]* ]+ ]+
 *
 * Table output has the following क्रमmat (identical to the स्थिरructor string):
 * num_feature_args [features_args]*
 * num_handler_args hw_handler [hw_handler_args]*
 * num_groups init_group_number
 *     [priority selector-name num_ps_args [ps_args]*
 *      num_paths num_selector_args [path_dev [selector_args]* ]+ ]+
 */
अटल व्योम multipath_status(काष्ठा dm_target *ti, status_type_t type,
			     अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक sz = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा multipath *m = ti->निजी;
	काष्ठा priority_group *pg;
	काष्ठा pgpath *p;
	अचिन्हित pg_num;
	अक्षर state;

	spin_lock_irqsave(&m->lock, flags);

	/* Features */
	अगर (type == STATUSTYPE_INFO)
		DMEMIT("2 %u %u ", test_bit(MPATHF_QUEUE_IO, &m->flags),
		       atomic_पढ़ो(&m->pg_init_count));
	अन्यथा अणु
		DMEMIT("%u ", test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags) +
			      (m->pg_init_retries > 0) * 2 +
			      (m->pg_init_delay_msecs != DM_PG_INIT_DELAY_DEFAULT) * 2 +
			      test_bit(MPATHF_RETAIN_ATTACHED_HW_HANDLER, &m->flags) +
			      (m->queue_mode != DM_TYPE_REQUEST_BASED) * 2);

		अगर (test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags))
			DMEMIT("queue_if_no_path ");
		अगर (m->pg_init_retries)
			DMEMIT("pg_init_retries %u ", m->pg_init_retries);
		अगर (m->pg_init_delay_msecs != DM_PG_INIT_DELAY_DEFAULT)
			DMEMIT("pg_init_delay_msecs %u ", m->pg_init_delay_msecs);
		अगर (test_bit(MPATHF_RETAIN_ATTACHED_HW_HANDLER, &m->flags))
			DMEMIT("retain_attached_hw_handler ");
		अगर (m->queue_mode != DM_TYPE_REQUEST_BASED) अणु
			चयन(m->queue_mode) अणु
			हाल DM_TYPE_BIO_BASED:
				DMEMIT("queue_mode bio ");
				अवरोध;
			शेष:
				WARN_ON_ONCE(true);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!m->hw_handler_name || type == STATUSTYPE_INFO)
		DMEMIT("0 ");
	अन्यथा
		DMEMIT("1 %s ", m->hw_handler_name);

	DMEMIT("%u ", m->nr_priority_groups);

	अगर (m->next_pg)
		pg_num = m->next_pg->pg_num;
	अन्यथा अगर (m->current_pg)
		pg_num = m->current_pg->pg_num;
	अन्यथा
		pg_num = (m->nr_priority_groups ? 1 : 0);

	DMEMIT("%u ", pg_num);

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		list_क्रम_each_entry(pg, &m->priority_groups, list) अणु
			अगर (pg->bypassed)
				state = 'D';	/* Disabled */
			अन्यथा अगर (pg == m->current_pg)
				state = 'A';	/* Currently Active */
			अन्यथा
				state = 'E';	/* Enabled */

			DMEMIT("%c ", state);

			अगर (pg->ps.type->status)
				sz += pg->ps.type->status(&pg->ps, शून्य, type,
							  result + sz,
							  maxlen - sz);
			अन्यथा
				DMEMIT("0 ");

			DMEMIT("%u %u ", pg->nr_pgpaths,
			       pg->ps.type->info_args);

			list_क्रम_each_entry(p, &pg->pgpaths, list) अणु
				DMEMIT("%s %s %u ", p->path.dev->name,
				       p->is_active ? "A" : "F",
				       p->fail_count);
				अगर (pg->ps.type->status)
					sz += pg->ps.type->status(&pg->ps,
					      &p->path, type, result + sz,
					      maxlen - sz);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल STATUSTYPE_TABLE:
		list_क्रम_each_entry(pg, &m->priority_groups, list) अणु
			DMEMIT("%s ", pg->ps.type->name);

			अगर (pg->ps.type->status)
				sz += pg->ps.type->status(&pg->ps, शून्य, type,
							  result + sz,
							  maxlen - sz);
			अन्यथा
				DMEMIT("0 ");

			DMEMIT("%u %u ", pg->nr_pgpaths,
			       pg->ps.type->table_args);

			list_क्रम_each_entry(p, &pg->pgpaths, list) अणु
				DMEMIT("%s ", p->path.dev->name);
				अगर (pg->ps.type->status)
					sz += pg->ps.type->status(&pg->ps,
					      &p->path, type, result + sz,
					      maxlen - sz);
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&m->lock, flags);
पूर्ण

अटल पूर्णांक multipath_message(काष्ठा dm_target *ti, अचिन्हित argc, अक्षर **argv,
			     अक्षर *result, अचिन्हित maxlen)
अणु
	पूर्णांक r = -EINVAL;
	काष्ठा dm_dev *dev;
	काष्ठा multipath *m = ti->निजी;
	action_fn action;
	अचिन्हित दीर्घ flags;

	mutex_lock(&m->work_mutex);

	अगर (dm_suspended(ti)) अणु
		r = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (argc == 1) अणु
		अगर (!strहालcmp(argv[0], "queue_if_no_path")) अणु
			r = queue_अगर_no_path(m, true, false, __func__);
			spin_lock_irqsave(&m->lock, flags);
			enable_nopath_समयout(m);
			spin_unlock_irqrestore(&m->lock, flags);
			जाओ out;
		पूर्ण अन्यथा अगर (!strहालcmp(argv[0], "fail_if_no_path")) अणु
			r = queue_अगर_no_path(m, false, false, __func__);
			disable_nopath_समयout(m);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (argc != 2) अणु
		DMWARN("Invalid multipath message arguments. Expected 2 arguments, got %d.", argc);
		जाओ out;
	पूर्ण

	अगर (!strहालcmp(argv[0], "disable_group")) अणु
		r = bypass_pg_num(m, argv[1], true);
		जाओ out;
	पूर्ण अन्यथा अगर (!strहालcmp(argv[0], "enable_group")) अणु
		r = bypass_pg_num(m, argv[1], false);
		जाओ out;
	पूर्ण अन्यथा अगर (!strहालcmp(argv[0], "switch_group")) अणु
		r = चयन_pg_num(m, argv[1]);
		जाओ out;
	पूर्ण अन्यथा अगर (!strहालcmp(argv[0], "reinstate_path"))
		action = reinstate_path;
	अन्यथा अगर (!strहालcmp(argv[0], "fail_path"))
		action = fail_path;
	अन्यथा अणु
		DMWARN("Unrecognised multipath message received: %s", argv[0]);
		जाओ out;
	पूर्ण

	r = dm_get_device(ti, argv[1], dm_table_get_mode(ti->table), &dev);
	अगर (r) अणु
		DMWARN("message: error getting device %s",
		       argv[1]);
		जाओ out;
	पूर्ण

	r = action_dev(m, dev, action);

	dm_put_device(ti, dev);

out:
	mutex_unlock(&m->work_mutex);
	वापस r;
पूर्ण

अटल पूर्णांक multipath_prepare_ioctl(काष्ठा dm_target *ti,
				   काष्ठा block_device **bdev)
अणु
	काष्ठा multipath *m = ti->निजी;
	काष्ठा pgpath *pgpath;
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	pgpath = READ_ONCE(m->current_pgpath);
	अगर (!pgpath || !mpath_द्विगुन_check_test_bit(MPATHF_QUEUE_IO, m))
		pgpath = choose_pgpath(m, 0);

	अगर (pgpath) अणु
		अगर (!mpath_द्विगुन_check_test_bit(MPATHF_QUEUE_IO, m)) अणु
			*bdev = pgpath->path.dev->bdev;
			r = 0;
		पूर्ण अन्यथा अणु
			/* pg_init has not started or completed */
			r = -ENOTCONN;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* No path is available */
		r = -EIO;
		spin_lock_irqsave(&m->lock, flags);
		अगर (test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags))
			r = -ENOTCONN;
		spin_unlock_irqrestore(&m->lock, flags);
	पूर्ण

	अगर (r == -ENOTCONN) अणु
		अगर (!READ_ONCE(m->current_pg)) अणु
			/* Path status changed, reकरो selection */
			(व्योम) choose_pgpath(m, 0);
		पूर्ण
		spin_lock_irqsave(&m->lock, flags);
		अगर (test_bit(MPATHF_PG_INIT_REQUIRED, &m->flags))
			(व्योम) __pg_init_all_paths(m);
		spin_unlock_irqrestore(&m->lock, flags);
		dm_table_run_md_queue_async(m->ti->table);
		process_queued_io_list(m);
	पूर्ण

	/*
	 * Only pass ioctls through अगर the device sizes match exactly.
	 */
	अगर (!r && ti->len != i_size_पढ़ो((*bdev)->bd_inode) >> SECTOR_SHIFT)
		वापस 1;
	वापस r;
पूर्ण

अटल पूर्णांक multipath_iterate_devices(काष्ठा dm_target *ti,
				     iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा multipath *m = ti->निजी;
	काष्ठा priority_group *pg;
	काष्ठा pgpath *p;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(pg, &m->priority_groups, list) अणु
		list_क्रम_each_entry(p, &pg->pgpaths, list) अणु
			ret = fn(ti, p->path.dev, ti->begin, ti->len, data);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक pgpath_busy(काष्ठा pgpath *pgpath)
अणु
	काष्ठा request_queue *q = bdev_get_queue(pgpath->path.dev->bdev);

	वापस blk_lld_busy(q);
पूर्ण

/*
 * We वापस "busy", only when we can map I/Os but underlying devices
 * are busy (so even अगर we map I/Os now, the I/Os will रुको on
 * the underlying queue).
 * In other words, अगर we want to समाप्त I/Os or queue them inside us
 * due to map unavailability, we करोn't वापस "busy".  Otherwise,
 * dm core won't give us the I/Os and we can't करो what we want.
 */
अटल पूर्णांक multipath_busy(काष्ठा dm_target *ti)
अणु
	bool busy = false, has_active = false;
	काष्ठा multipath *m = ti->निजी;
	काष्ठा priority_group *pg, *next_pg;
	काष्ठा pgpath *pgpath;

	/* pg_init in progress */
	अगर (atomic_पढ़ो(&m->pg_init_in_progress))
		वापस true;

	/* no paths available, क्रम blk-mq: rely on IO mapping to delay requeue */
	अगर (!atomic_पढ़ो(&m->nr_valid_paths)) अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&m->lock, flags);
		अगर (test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags)) अणु
			spin_unlock_irqrestore(&m->lock, flags);
			वापस (m->queue_mode != DM_TYPE_REQUEST_BASED);
		पूर्ण
		spin_unlock_irqrestore(&m->lock, flags);
	पूर्ण

	/* Guess which priority_group will be used at next mapping समय */
	pg = READ_ONCE(m->current_pg);
	next_pg = READ_ONCE(m->next_pg);
	अगर (unlikely(!READ_ONCE(m->current_pgpath) && next_pg))
		pg = next_pg;

	अगर (!pg) अणु
		/*
		 * We करोn't know which pg will be used at next mapping समय.
		 * We करोn't call choose_pgpath() here to aव्योम to trigger
		 * pg_init just by busy checking.
		 * So we करोn't know whether underlying devices we will be using
		 * at next mapping समय are busy or not. Just try mapping.
		 */
		वापस busy;
	पूर्ण

	/*
	 * If there is one non-busy active path at least, the path selector
	 * will be able to select it. So we consider such a pg as not busy.
	 */
	busy = true;
	list_क्रम_each_entry(pgpath, &pg->pgpaths, list) अणु
		अगर (pgpath->is_active) अणु
			has_active = true;
			अगर (!pgpath_busy(pgpath)) अणु
				busy = false;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!has_active) अणु
		/*
		 * No active path in this pg, so this pg won't be used and
		 * the current_pg will be changed at next mapping समय.
		 * We need to try mapping to determine it.
		 */
		busy = false;
	पूर्ण

	वापस busy;
पूर्ण

/*-----------------------------------------------------------------
 * Module setup
 *---------------------------------------------------------------*/
अटल काष्ठा target_type multipath_target = अणु
	.name = "multipath",
	.version = अणु1, 14, 0पूर्ण,
	.features = DM_TARGET_SINGLETON | DM_TARGET_IMMUTABLE |
		    DM_TARGET_PASSES_INTEGRITY,
	.module = THIS_MODULE,
	.ctr = multipath_ctr,
	.dtr = multipath_dtr,
	.clone_and_map_rq = multipath_clone_and_map,
	.release_clone_rq = multipath_release_clone,
	.rq_end_io = multipath_end_io,
	.map = multipath_map_bio,
	.end_io = multipath_end_io_bio,
	.presuspend = multipath_presuspend,
	.postsuspend = multipath_postsuspend,
	.resume = multipath_resume,
	.status = multipath_status,
	.message = multipath_message,
	.prepare_ioctl = multipath_prepare_ioctl,
	.iterate_devices = multipath_iterate_devices,
	.busy = multipath_busy,
पूर्ण;

अटल पूर्णांक __init dm_multipath_init(व्योम)
अणु
	पूर्णांक r;

	kmultipathd = alloc_workqueue("kmpathd", WQ_MEM_RECLAIM, 0);
	अगर (!kmultipathd) अणु
		DMERR("failed to create workqueue kmpathd");
		r = -ENOMEM;
		जाओ bad_alloc_kmultipathd;
	पूर्ण

	/*
	 * A separate workqueue is used to handle the device handlers
	 * to aव्योम overloading existing workqueue. Overloading the
	 * old workqueue would also create a bottleneck in the
	 * path of the storage hardware device activation.
	 */
	kmpath_handlerd = alloc_ordered_workqueue("kmpath_handlerd",
						  WQ_MEM_RECLAIM);
	अगर (!kmpath_handlerd) अणु
		DMERR("failed to create workqueue kmpath_handlerd");
		r = -ENOMEM;
		जाओ bad_alloc_kmpath_handlerd;
	पूर्ण

	r = dm_रेजिस्टर_target(&multipath_target);
	अगर (r < 0) अणु
		DMERR("request-based register failed %d", r);
		r = -EINVAL;
		जाओ bad_रेजिस्टर_target;
	पूर्ण

	वापस 0;

bad_रेजिस्टर_target:
	destroy_workqueue(kmpath_handlerd);
bad_alloc_kmpath_handlerd:
	destroy_workqueue(kmultipathd);
bad_alloc_kmultipathd:
	वापस r;
पूर्ण

अटल व्योम __निकास dm_multipath_निकास(व्योम)
अणु
	destroy_workqueue(kmpath_handlerd);
	destroy_workqueue(kmultipathd);

	dm_unरेजिस्टर_target(&multipath_target);
पूर्ण

module_init(dm_multipath_init);
module_निकास(dm_multipath_निकास);

module_param_named(queue_अगर_no_path_समयout_secs,
		   queue_अगर_no_path_समयout_secs, uदीर्घ, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(queue_अगर_no_path_समयout_secs, "No available paths queue IO timeout in seconds");

MODULE_DESCRIPTION(DM_NAME " multipath target");
MODULE_AUTHOR("Sistina Software <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
