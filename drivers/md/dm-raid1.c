<शैली गुरु>
/*
 * Copyright (C) 2003 Sistina Software Limited.
 * Copyright (C) 2005-2008 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-bio-record.h"

#समावेश <linux/init.h>
#समावेश <linux/mempool.h>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/device-mapper.h>
#समावेश <linux/dm-पन.स>
#समावेश <linux/dm-dirty-log.h>
#समावेश <linux/dm-kcopyd.h>
#समावेश <linux/dm-region-hash.h>

#घोषणा DM_MSG_PREFIX "raid1"

#घोषणा MAX_RECOVERY 1	/* Maximum number of regions recovered in parallel. */

#घोषणा MAX_NR_MIRRORS	(DM_KCOPYD_MAX_REGIONS + 1)

#घोषणा DM_RAID1_HANDLE_ERRORS	0x01
#घोषणा DM_RAID1_KEEP_LOG	0x02
#घोषणा errors_handled(p)	((p)->features & DM_RAID1_HANDLE_ERRORS)
#घोषणा keep_log(p)		((p)->features & DM_RAID1_KEEP_LOG)

अटल DECLARE_WAIT_QUEUE_HEAD(_kmirrord_recovery_stopped);

/*-----------------------------------------------------------------
 * Mirror set काष्ठाures.
 *---------------------------------------------------------------*/
क्रमागत dm_raid1_error अणु
	DM_RAID1_WRITE_ERROR,
	DM_RAID1_FLUSH_ERROR,
	DM_RAID1_SYNC_ERROR,
	DM_RAID1_READ_ERROR
पूर्ण;

काष्ठा mirror अणु
	काष्ठा mirror_set *ms;
	atomic_t error_count;
	अचिन्हित दीर्घ error_type;
	काष्ठा dm_dev *dev;
	sector_t offset;
पूर्ण;

काष्ठा mirror_set अणु
	काष्ठा dm_target *ti;
	काष्ठा list_head list;

	uपूर्णांक64_t features;

	spinlock_t lock;	/* protects the lists */
	काष्ठा bio_list पढ़ोs;
	काष्ठा bio_list ग_लिखोs;
	काष्ठा bio_list failures;
	काष्ठा bio_list holds;	/* bios are रुकोing until suspend */

	काष्ठा dm_region_hash *rh;
	काष्ठा dm_kcopyd_client *kcopyd_client;
	काष्ठा dm_io_client *io_client;

	/* recovery */
	region_t nr_regions;
	पूर्णांक in_sync;
	पूर्णांक log_failure;
	पूर्णांक leg_failure;
	atomic_t suspend;

	atomic_t शेष_mirror;	/* Default mirror */

	काष्ठा workqueue_काष्ठा *kmirrord_wq;
	काष्ठा work_काष्ठा kmirrord_work;
	काष्ठा समयr_list समयr;
	अचिन्हित दीर्घ समयr_pending;

	काष्ठा work_काष्ठा trigger_event;

	अचिन्हित nr_mirrors;
	काष्ठा mirror mirror[];
पूर्ण;

DECLARE_DM_KCOPYD_THROTTLE_WITH_MODULE_PARM(raid1_resync_throttle,
		"A percentage of time allocated for raid resynchronization");

अटल व्योम wakeup_mirrord(व्योम *context)
अणु
	काष्ठा mirror_set *ms = context;

	queue_work(ms->kmirrord_wq, &ms->kmirrord_work);
पूर्ण

अटल व्योम delayed_wake_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा mirror_set *ms = from_समयr(ms, t, समयr);

	clear_bit(0, &ms->समयr_pending);
	wakeup_mirrord(ms);
पूर्ण

अटल व्योम delayed_wake(काष्ठा mirror_set *ms)
अणु
	अगर (test_and_set_bit(0, &ms->समयr_pending))
		वापस;

	ms->समयr.expires = jअगरfies + HZ / 5;
	add_समयr(&ms->समयr);
पूर्ण

अटल व्योम wakeup_all_recovery_रुकोers(व्योम *context)
अणु
	wake_up_all(&_kmirrord_recovery_stopped);
पूर्ण

अटल व्योम queue_bio(काष्ठा mirror_set *ms, काष्ठा bio *bio, पूर्णांक rw)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक should_wake = 0;
	काष्ठा bio_list *bl;

	bl = (rw == WRITE) ? &ms->ग_लिखोs : &ms->पढ़ोs;
	spin_lock_irqsave(&ms->lock, flags);
	should_wake = !(bl->head);
	bio_list_add(bl, bio);
	spin_unlock_irqrestore(&ms->lock, flags);

	अगर (should_wake)
		wakeup_mirrord(ms);
पूर्ण

अटल व्योम dispatch_bios(व्योम *context, काष्ठा bio_list *bio_list)
अणु
	काष्ठा mirror_set *ms = context;
	काष्ठा bio *bio;

	जबतक ((bio = bio_list_pop(bio_list)))
		queue_bio(ms, bio, WRITE);
पूर्ण

काष्ठा dm_raid1_bio_record अणु
	काष्ठा mirror *m;
	/* अगर details->bi_bdev == शून्य, details were not saved */
	काष्ठा dm_bio_details details;
	region_t ग_लिखो_region;
पूर्ण;

/*
 * Every mirror should look like this one.
 */
#घोषणा DEFAULT_MIRROR 0

/*
 * This is yucky.  We squirrel the mirror काष्ठा away inside
 * bi_next क्रम पढ़ो/ग_लिखो buffers.  This is safe since the bh
 * करोesn't get submitted to the lower levels of block layer.
 */
अटल काष्ठा mirror *bio_get_m(काष्ठा bio *bio)
अणु
	वापस (काष्ठा mirror *) bio->bi_next;
पूर्ण

अटल व्योम bio_set_m(काष्ठा bio *bio, काष्ठा mirror *m)
अणु
	bio->bi_next = (काष्ठा bio *) m;
पूर्ण

अटल काष्ठा mirror *get_शेष_mirror(काष्ठा mirror_set *ms)
अणु
	वापस &ms->mirror[atomic_पढ़ो(&ms->शेष_mirror)];
पूर्ण

अटल व्योम set_शेष_mirror(काष्ठा mirror *m)
अणु
	काष्ठा mirror_set *ms = m->ms;
	काष्ठा mirror *m0 = &(ms->mirror[0]);

	atomic_set(&ms->शेष_mirror, m - m0);
पूर्ण

अटल काष्ठा mirror *get_valid_mirror(काष्ठा mirror_set *ms)
अणु
	काष्ठा mirror *m;

	क्रम (m = ms->mirror; m < ms->mirror + ms->nr_mirrors; m++)
		अगर (!atomic_पढ़ो(&m->error_count))
			वापस m;

	वापस शून्य;
पूर्ण

/* fail_mirror
 * @m: mirror device to fail
 * @error_type: one of the क्रमागत's, DM_RAID1_*_ERROR
 *
 * If errors are being handled, record the type of
 * error encountered क्रम this device.  If this type
 * of error has alपढ़ोy been recorded, we can वापस;
 * otherwise, we must संकेत userspace by triggering
 * an event.  Additionally, अगर the device is the
 * primary device, we must choose a new primary, but
 * only अगर the mirror is in-sync.
 *
 * This function must not block.
 */
अटल व्योम fail_mirror(काष्ठा mirror *m, क्रमागत dm_raid1_error error_type)
अणु
	काष्ठा mirror_set *ms = m->ms;
	काष्ठा mirror *new;

	ms->leg_failure = 1;

	/*
	 * error_count is used क्रम nothing more than a
	 * simple way to tell अगर a device has encountered
	 * errors.
	 */
	atomic_inc(&m->error_count);

	अगर (test_and_set_bit(error_type, &m->error_type))
		वापस;

	अगर (!errors_handled(ms))
		वापस;

	अगर (m != get_शेष_mirror(ms))
		जाओ out;

	अगर (!ms->in_sync && !keep_log(ms)) अणु
		/*
		 * Better to issue requests to same failing device
		 * than to risk वापसing corrupt data.
		 */
		DMERR("Primary mirror (%s) failed while out-of-sync: "
		      "Reads may fail.", m->dev->name);
		जाओ out;
	पूर्ण

	new = get_valid_mirror(ms);
	अगर (new)
		set_शेष_mirror(new);
	अन्यथा
		DMWARN("All sides of mirror have failed.");

out:
	schedule_work(&ms->trigger_event);
पूर्ण

अटल पूर्णांक mirror_flush(काष्ठा dm_target *ti)
अणु
	काष्ठा mirror_set *ms = ti->निजी;
	अचिन्हित दीर्घ error_bits;

	अचिन्हित पूर्णांक i;
	काष्ठा dm_io_region io[MAX_NR_MIRRORS];
	काष्ठा mirror *m;
	काष्ठा dm_io_request io_req = अणु
		.bi_op = REQ_OP_WRITE,
		.bi_op_flags = REQ_PREFLUSH | REQ_SYNC,
		.mem.type = DM_IO_KMEM,
		.mem.ptr.addr = शून्य,
		.client = ms->io_client,
	पूर्ण;

	क्रम (i = 0, m = ms->mirror; i < ms->nr_mirrors; i++, m++) अणु
		io[i].bdev = m->dev->bdev;
		io[i].sector = 0;
		io[i].count = 0;
	पूर्ण

	error_bits = -1;
	dm_io(&io_req, ms->nr_mirrors, io, &error_bits);
	अगर (unlikely(error_bits != 0)) अणु
		क्रम (i = 0; i < ms->nr_mirrors; i++)
			अगर (test_bit(i, &error_bits))
				fail_mirror(ms->mirror + i,
					    DM_RAID1_FLUSH_ERROR);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*-----------------------------------------------------------------
 * Recovery.
 *
 * When a mirror is first activated we may find that some regions
 * are in the no-sync state.  We have to recover these by
 * recopying from the शेष mirror to all the others.
 *---------------------------------------------------------------*/
अटल व्योम recovery_complete(पूर्णांक पढ़ो_err, अचिन्हित दीर्घ ग_लिखो_err,
			      व्योम *context)
अणु
	काष्ठा dm_region *reg = context;
	काष्ठा mirror_set *ms = dm_rh_region_context(reg);
	पूर्णांक m, bit = 0;

	अगर (पढ़ो_err) अणु
		/* Read error means the failure of शेष mirror. */
		DMERR_LIMIT("Unable to read primary mirror during recovery");
		fail_mirror(get_शेष_mirror(ms), DM_RAID1_SYNC_ERROR);
	पूर्ण

	अगर (ग_लिखो_err) अणु
		DMERR_LIMIT("Write error during recovery (error = 0x%lx)",
			    ग_लिखो_err);
		/*
		 * Bits correspond to devices (excluding शेष mirror).
		 * The शेष mirror cannot change during recovery.
		 */
		क्रम (m = 0; m < ms->nr_mirrors; m++) अणु
			अगर (&ms->mirror[m] == get_शेष_mirror(ms))
				जारी;
			अगर (test_bit(bit, &ग_लिखो_err))
				fail_mirror(ms->mirror + m,
					    DM_RAID1_SYNC_ERROR);
			bit++;
		पूर्ण
	पूर्ण

	dm_rh_recovery_end(reg, !(पढ़ो_err || ग_लिखो_err));
पूर्ण

अटल व्योम recover(काष्ठा mirror_set *ms, काष्ठा dm_region *reg)
अणु
	अचिन्हित i;
	काष्ठा dm_io_region from, to[DM_KCOPYD_MAX_REGIONS], *dest;
	काष्ठा mirror *m;
	अचिन्हित दीर्घ flags = 0;
	region_t key = dm_rh_get_region_key(reg);
	sector_t region_size = dm_rh_get_region_size(ms->rh);

	/* fill in the source */
	m = get_शेष_mirror(ms);
	from.bdev = m->dev->bdev;
	from.sector = m->offset + dm_rh_region_to_sector(ms->rh, key);
	अगर (key == (ms->nr_regions - 1)) अणु
		/*
		 * The final region may be smaller than
		 * region_size.
		 */
		from.count = ms->ti->len & (region_size - 1);
		अगर (!from.count)
			from.count = region_size;
	पूर्ण अन्यथा
		from.count = region_size;

	/* fill in the destinations */
	क्रम (i = 0, dest = to; i < ms->nr_mirrors; i++) अणु
		अगर (&ms->mirror[i] == get_शेष_mirror(ms))
			जारी;

		m = ms->mirror + i;
		dest->bdev = m->dev->bdev;
		dest->sector = m->offset + dm_rh_region_to_sector(ms->rh, key);
		dest->count = from.count;
		dest++;
	पूर्ण

	/* hand to kcopyd */
	अगर (!errors_handled(ms))
		set_bit(DM_KCOPYD_IGNORE_ERROR, &flags);

	dm_kcopyd_copy(ms->kcopyd_client, &from, ms->nr_mirrors - 1, to,
		       flags, recovery_complete, reg);
पूर्ण

अटल व्योम reset_ms_flags(काष्ठा mirror_set *ms)
अणु
	अचिन्हित पूर्णांक m;

	ms->leg_failure = 0;
	क्रम (m = 0; m < ms->nr_mirrors; m++) अणु
		atomic_set(&(ms->mirror[m].error_count), 0);
		ms->mirror[m].error_type = 0;
	पूर्ण
पूर्ण

अटल व्योम करो_recovery(काष्ठा mirror_set *ms)
अणु
	काष्ठा dm_region *reg;
	काष्ठा dm_dirty_log *log = dm_rh_dirty_log(ms->rh);

	/*
	 * Start quiescing some regions.
	 */
	dm_rh_recovery_prepare(ms->rh);

	/*
	 * Copy any alपढ़ोy quiesced regions.
	 */
	जबतक ((reg = dm_rh_recovery_start(ms->rh)))
		recover(ms, reg);

	/*
	 * Update the in sync flag.
	 */
	अगर (!ms->in_sync &&
	    (log->type->get_sync_count(log) == ms->nr_regions)) अणु
		/* the sync is complete */
		dm_table_event(ms->ti->table);
		ms->in_sync = 1;
		reset_ms_flags(ms);
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------
 * Reads
 *---------------------------------------------------------------*/
अटल काष्ठा mirror *choose_mirror(काष्ठा mirror_set *ms, sector_t sector)
अणु
	काष्ठा mirror *m = get_शेष_mirror(ms);

	करो अणु
		अगर (likely(!atomic_पढ़ो(&m->error_count)))
			वापस m;

		अगर (m-- == ms->mirror)
			m += ms->nr_mirrors;
	पूर्ण जबतक (m != get_शेष_mirror(ms));

	वापस शून्य;
पूर्ण

अटल पूर्णांक शेष_ok(काष्ठा mirror *m)
अणु
	काष्ठा mirror *शेष_mirror = get_शेष_mirror(m->ms);

	वापस !atomic_पढ़ो(&शेष_mirror->error_count);
पूर्ण

अटल पूर्णांक mirror_available(काष्ठा mirror_set *ms, काष्ठा bio *bio)
अणु
	काष्ठा dm_dirty_log *log = dm_rh_dirty_log(ms->rh);
	region_t region = dm_rh_bio_to_region(ms->rh, bio);

	अगर (log->type->in_sync(log, region, 0))
		वापस choose_mirror(ms,  bio->bi_iter.bi_sector) ? 1 : 0;

	वापस 0;
पूर्ण

/*
 * remap a buffer to a particular mirror.
 */
अटल sector_t map_sector(काष्ठा mirror *m, काष्ठा bio *bio)
अणु
	अगर (unlikely(!bio->bi_iter.bi_size))
		वापस 0;
	वापस m->offset + dm_target_offset(m->ms->ti, bio->bi_iter.bi_sector);
पूर्ण

अटल व्योम map_bio(काष्ठा mirror *m, काष्ठा bio *bio)
अणु
	bio_set_dev(bio, m->dev->bdev);
	bio->bi_iter.bi_sector = map_sector(m, bio);
पूर्ण

अटल व्योम map_region(काष्ठा dm_io_region *io, काष्ठा mirror *m,
		       काष्ठा bio *bio)
अणु
	io->bdev = m->dev->bdev;
	io->sector = map_sector(m, bio);
	io->count = bio_sectors(bio);
पूर्ण

अटल व्योम hold_bio(काष्ठा mirror_set *ms, काष्ठा bio *bio)
अणु
	/*
	 * Lock is required to aव्योम race condition during suspend
	 * process.
	 */
	spin_lock_irq(&ms->lock);

	अगर (atomic_पढ़ो(&ms->suspend)) अणु
		spin_unlock_irq(&ms->lock);

		/*
		 * If device is suspended, complete the bio.
		 */
		अगर (dm_noflush_suspending(ms->ti))
			bio->bi_status = BLK_STS_DM_REQUEUE;
		अन्यथा
			bio->bi_status = BLK_STS_IOERR;

		bio_endio(bio);
		वापस;
	पूर्ण

	/*
	 * Hold bio until the suspend is complete.
	 */
	bio_list_add(&ms->holds, bio);
	spin_unlock_irq(&ms->lock);
पूर्ण

/*-----------------------------------------------------------------
 * Reads
 *---------------------------------------------------------------*/
अटल व्योम पढ़ो_callback(अचिन्हित दीर्घ error, व्योम *context)
अणु
	काष्ठा bio *bio = context;
	काष्ठा mirror *m;

	m = bio_get_m(bio);
	bio_set_m(bio, शून्य);

	अगर (likely(!error)) अणु
		bio_endio(bio);
		वापस;
	पूर्ण

	fail_mirror(m, DM_RAID1_READ_ERROR);

	अगर (likely(शेष_ok(m)) || mirror_available(m->ms, bio)) अणु
		DMWARN_LIMIT("Read failure on mirror device %s.  "
			     "Trying alternative device.",
			     m->dev->name);
		queue_bio(m->ms, bio, bio_data_dir(bio));
		वापस;
	पूर्ण

	DMERR_LIMIT("Read failure on mirror device %s.  Failing I/O.",
		    m->dev->name);
	bio_io_error(bio);
पूर्ण

/* Asynchronous पढ़ो. */
अटल व्योम पढ़ो_async_bio(काष्ठा mirror *m, काष्ठा bio *bio)
अणु
	काष्ठा dm_io_region io;
	काष्ठा dm_io_request io_req = अणु
		.bi_op = REQ_OP_READ,
		.bi_op_flags = 0,
		.mem.type = DM_IO_BIO,
		.mem.ptr.bio = bio,
		.notअगरy.fn = पढ़ो_callback,
		.notअगरy.context = bio,
		.client = m->ms->io_client,
	पूर्ण;

	map_region(&io, m, bio);
	bio_set_m(bio, m);
	BUG_ON(dm_io(&io_req, 1, &io, शून्य));
पूर्ण

अटल अंतरभूत पूर्णांक region_in_sync(काष्ठा mirror_set *ms, region_t region,
				 पूर्णांक may_block)
अणु
	पूर्णांक state = dm_rh_get_state(ms->rh, region, may_block);
	वापस state == DM_RH_CLEAN || state == DM_RH_सूचीTY;
पूर्ण

अटल व्योम करो_पढ़ोs(काष्ठा mirror_set *ms, काष्ठा bio_list *पढ़ोs)
अणु
	region_t region;
	काष्ठा bio *bio;
	काष्ठा mirror *m;

	जबतक ((bio = bio_list_pop(पढ़ोs))) अणु
		region = dm_rh_bio_to_region(ms->rh, bio);
		m = get_शेष_mirror(ms);

		/*
		 * We can only पढ़ो balance अगर the region is in sync.
		 */
		अगर (likely(region_in_sync(ms, region, 1)))
			m = choose_mirror(ms, bio->bi_iter.bi_sector);
		अन्यथा अगर (m && atomic_पढ़ो(&m->error_count))
			m = शून्य;

		अगर (likely(m))
			पढ़ो_async_bio(m, bio);
		अन्यथा
			bio_io_error(bio);
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------
 * Writes.
 *
 * We करो dअगरferent things with the ग_लिखो io depending on the
 * state of the region that it's in:
 *
 * SYNC: 	increment pending, use kcopyd to ग_लिखो to *all* mirrors
 * RECOVERING:	delay the io until recovery completes
 * NOSYNC:	increment pending, just ग_लिखो to the शेष mirror
 *---------------------------------------------------------------*/


अटल व्योम ग_लिखो_callback(अचिन्हित दीर्घ error, व्योम *context)
अणु
	अचिन्हित i;
	काष्ठा bio *bio = (काष्ठा bio *) context;
	काष्ठा mirror_set *ms;
	पूर्णांक should_wake = 0;
	अचिन्हित दीर्घ flags;

	ms = bio_get_m(bio)->ms;
	bio_set_m(bio, शून्य);

	/*
	 * NOTE: We करोn't decrement the pending count here,
	 * instead it is करोne by the tarमाला_लो endio function.
	 * This way we handle both ग_लिखोs to SYNC and NOSYNC
	 * regions with the same code.
	 */
	अगर (likely(!error)) अणु
		bio_endio(bio);
		वापस;
	पूर्ण

	/*
	 * If the bio is discard, वापस an error, but करो not
	 * degrade the array.
	 */
	अगर (bio_op(bio) == REQ_OP_DISCARD) अणु
		bio->bi_status = BLK_STS_NOTSUPP;
		bio_endio(bio);
		वापस;
	पूर्ण

	क्रम (i = 0; i < ms->nr_mirrors; i++)
		अगर (test_bit(i, &error))
			fail_mirror(ms->mirror + i, DM_RAID1_WRITE_ERROR);

	/*
	 * Need to उठाओ event.  Since raising
	 * events can block, we need to करो it in
	 * the मुख्य thपढ़ो.
	 */
	spin_lock_irqsave(&ms->lock, flags);
	अगर (!ms->failures.head)
		should_wake = 1;
	bio_list_add(&ms->failures, bio);
	spin_unlock_irqrestore(&ms->lock, flags);
	अगर (should_wake)
		wakeup_mirrord(ms);
पूर्ण

अटल व्योम करो_ग_लिखो(काष्ठा mirror_set *ms, काष्ठा bio *bio)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा dm_io_region io[MAX_NR_MIRRORS], *dest = io;
	काष्ठा mirror *m;
	काष्ठा dm_io_request io_req = अणु
		.bi_op = REQ_OP_WRITE,
		.bi_op_flags = bio->bi_opf & (REQ_FUA | REQ_PREFLUSH),
		.mem.type = DM_IO_BIO,
		.mem.ptr.bio = bio,
		.notअगरy.fn = ग_लिखो_callback,
		.notअगरy.context = bio,
		.client = ms->io_client,
	पूर्ण;

	अगर (bio_op(bio) == REQ_OP_DISCARD) अणु
		io_req.bi_op = REQ_OP_DISCARD;
		io_req.mem.type = DM_IO_KMEM;
		io_req.mem.ptr.addr = शून्य;
	पूर्ण

	क्रम (i = 0, m = ms->mirror; i < ms->nr_mirrors; i++, m++)
		map_region(dest++, m, bio);

	/*
	 * Use शेष mirror because we only need it to retrieve the reference
	 * to the mirror set in ग_लिखो_callback().
	 */
	bio_set_m(bio, get_शेष_mirror(ms));

	BUG_ON(dm_io(&io_req, ms->nr_mirrors, io, शून्य));
पूर्ण

अटल व्योम करो_ग_लिखोs(काष्ठा mirror_set *ms, काष्ठा bio_list *ग_लिखोs)
अणु
	पूर्णांक state;
	काष्ठा bio *bio;
	काष्ठा bio_list sync, nosync, recover, *this_list = शून्य;
	काष्ठा bio_list requeue;
	काष्ठा dm_dirty_log *log = dm_rh_dirty_log(ms->rh);
	region_t region;

	अगर (!ग_लिखोs->head)
		वापस;

	/*
	 * Classअगरy each ग_लिखो.
	 */
	bio_list_init(&sync);
	bio_list_init(&nosync);
	bio_list_init(&recover);
	bio_list_init(&requeue);

	जबतक ((bio = bio_list_pop(ग_लिखोs))) अणु
		अगर ((bio->bi_opf & REQ_PREFLUSH) ||
		    (bio_op(bio) == REQ_OP_DISCARD)) अणु
			bio_list_add(&sync, bio);
			जारी;
		पूर्ण

		region = dm_rh_bio_to_region(ms->rh, bio);

		अगर (log->type->is_remote_recovering &&
		    log->type->is_remote_recovering(log, region)) अणु
			bio_list_add(&requeue, bio);
			जारी;
		पूर्ण

		state = dm_rh_get_state(ms->rh, region, 1);
		चयन (state) अणु
		हाल DM_RH_CLEAN:
		हाल DM_RH_सूचीTY:
			this_list = &sync;
			अवरोध;

		हाल DM_RH_NOSYNC:
			this_list = &nosync;
			अवरोध;

		हाल DM_RH_RECOVERING:
			this_list = &recover;
			अवरोध;
		पूर्ण

		bio_list_add(this_list, bio);
	पूर्ण

	/*
	 * Add bios that are delayed due to remote recovery
	 * back on to the ग_लिखो queue
	 */
	अगर (unlikely(requeue.head)) अणु
		spin_lock_irq(&ms->lock);
		bio_list_merge(&ms->ग_लिखोs, &requeue);
		spin_unlock_irq(&ms->lock);
		delayed_wake(ms);
	पूर्ण

	/*
	 * Increment the pending counts क्रम any regions that will
	 * be written to (ग_लिखोs to recover regions are going to
	 * be delayed).
	 */
	dm_rh_inc_pending(ms->rh, &sync);
	dm_rh_inc_pending(ms->rh, &nosync);

	/*
	 * If the flush fails on a previous call and succeeds here,
	 * we must not reset the log_failure variable.  We need
	 * userspace पूर्णांकeraction to करो that.
	 */
	ms->log_failure = dm_rh_flush(ms->rh) ? 1 : ms->log_failure;

	/*
	 * Dispatch io.
	 */
	अगर (unlikely(ms->log_failure) && errors_handled(ms)) अणु
		spin_lock_irq(&ms->lock);
		bio_list_merge(&ms->failures, &sync);
		spin_unlock_irq(&ms->lock);
		wakeup_mirrord(ms);
	पूर्ण अन्यथा
		जबतक ((bio = bio_list_pop(&sync)))
			करो_ग_लिखो(ms, bio);

	जबतक ((bio = bio_list_pop(&recover)))
		dm_rh_delay(ms->rh, bio);

	जबतक ((bio = bio_list_pop(&nosync))) अणु
		अगर (unlikely(ms->leg_failure) && errors_handled(ms) && !keep_log(ms)) अणु
			spin_lock_irq(&ms->lock);
			bio_list_add(&ms->failures, bio);
			spin_unlock_irq(&ms->lock);
			wakeup_mirrord(ms);
		पूर्ण अन्यथा अणु
			map_bio(get_शेष_mirror(ms), bio);
			submit_bio_noacct(bio);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम करो_failures(काष्ठा mirror_set *ms, काष्ठा bio_list *failures)
अणु
	काष्ठा bio *bio;

	अगर (likely(!failures->head))
		वापस;

	/*
	 * If the log has failed, unattempted ग_लिखोs are being
	 * put on the holds list.  We can't issue those ग_लिखोs
	 * until a log has been marked, so we must store them.
	 *
	 * If a 'noflush' suspend is in progress, we can requeue
	 * the I/O's to the core.  This give userspace a chance
	 * to reconfigure the mirror, at which poपूर्णांक the core
	 * will reissue the ग_लिखोs.  If the 'noflush' flag is
	 * not set, we have no choice but to वापस errors.
	 *
	 * Some ग_लिखोs on the failures list may have been
	 * submitted beक्रमe the log failure and represent a
	 * failure to ग_लिखो to one of the devices.  It is ok
	 * क्रम us to treat them the same and requeue them
	 * as well.
	 */
	जबतक ((bio = bio_list_pop(failures))) अणु
		अगर (!ms->log_failure) अणु
			ms->in_sync = 0;
			dm_rh_mark_nosync(ms->rh, bio);
		पूर्ण

		/*
		 * If all the legs are dead, fail the I/O.
		 * If the device has failed and keep_log is enabled,
		 * fail the I/O.
		 *
		 * If we have been told to handle errors, and keep_log
		 * isn't enabled, hold the bio and रुको क्रम userspace to
		 * deal with the problem.
		 *
		 * Otherwise pretend that the I/O succeeded. (This would
		 * be wrong अगर the failed leg वापसed after reboot and
		 * got replicated back to the good legs.)
		 */
		अगर (unlikely(!get_valid_mirror(ms) || (keep_log(ms) && ms->log_failure)))
			bio_io_error(bio);
		अन्यथा अगर (errors_handled(ms) && !keep_log(ms))
			hold_bio(ms, bio);
		अन्यथा
			bio_endio(bio);
	पूर्ण
पूर्ण

अटल व्योम trigger_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mirror_set *ms =
		container_of(work, काष्ठा mirror_set, trigger_event);

	dm_table_event(ms->ti->table);
पूर्ण

/*-----------------------------------------------------------------
 * kmirrord
 *---------------------------------------------------------------*/
अटल व्योम करो_mirror(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mirror_set *ms = container_of(work, काष्ठा mirror_set,
					     kmirrord_work);
	काष्ठा bio_list पढ़ोs, ग_लिखोs, failures;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ms->lock, flags);
	पढ़ोs = ms->पढ़ोs;
	ग_लिखोs = ms->ग_लिखोs;
	failures = ms->failures;
	bio_list_init(&ms->पढ़ोs);
	bio_list_init(&ms->ग_लिखोs);
	bio_list_init(&ms->failures);
	spin_unlock_irqrestore(&ms->lock, flags);

	dm_rh_update_states(ms->rh, errors_handled(ms));
	करो_recovery(ms);
	करो_पढ़ोs(ms, &पढ़ोs);
	करो_ग_लिखोs(ms, &ग_लिखोs);
	करो_failures(ms, &failures);
पूर्ण

/*-----------------------------------------------------------------
 * Target functions
 *---------------------------------------------------------------*/
अटल काष्ठा mirror_set *alloc_context(अचिन्हित पूर्णांक nr_mirrors,
					uपूर्णांक32_t region_size,
					काष्ठा dm_target *ti,
					काष्ठा dm_dirty_log *dl)
अणु
	काष्ठा mirror_set *ms =
		kzalloc(काष्ठा_size(ms, mirror, nr_mirrors), GFP_KERNEL);

	अगर (!ms) अणु
		ti->error = "Cannot allocate mirror context";
		वापस शून्य;
	पूर्ण

	spin_lock_init(&ms->lock);
	bio_list_init(&ms->पढ़ोs);
	bio_list_init(&ms->ग_लिखोs);
	bio_list_init(&ms->failures);
	bio_list_init(&ms->holds);

	ms->ti = ti;
	ms->nr_mirrors = nr_mirrors;
	ms->nr_regions = dm_sector_भाग_up(ti->len, region_size);
	ms->in_sync = 0;
	ms->log_failure = 0;
	ms->leg_failure = 0;
	atomic_set(&ms->suspend, 0);
	atomic_set(&ms->शेष_mirror, DEFAULT_MIRROR);

	ms->io_client = dm_io_client_create();
	अगर (IS_ERR(ms->io_client)) अणु
		ti->error = "Error creating dm_io client";
		kमुक्त(ms);
 		वापस शून्य;
	पूर्ण

	ms->rh = dm_region_hash_create(ms, dispatch_bios, wakeup_mirrord,
				       wakeup_all_recovery_रुकोers,
				       ms->ti->begin, MAX_RECOVERY,
				       dl, region_size, ms->nr_regions);
	अगर (IS_ERR(ms->rh)) अणु
		ti->error = "Error creating dirty region hash";
		dm_io_client_destroy(ms->io_client);
		kमुक्त(ms);
		वापस शून्य;
	पूर्ण

	वापस ms;
पूर्ण

अटल व्योम मुक्त_context(काष्ठा mirror_set *ms, काष्ठा dm_target *ti,
			 अचिन्हित पूर्णांक m)
अणु
	जबतक (m--)
		dm_put_device(ti, ms->mirror[m].dev);

	dm_io_client_destroy(ms->io_client);
	dm_region_hash_destroy(ms->rh);
	kमुक्त(ms);
पूर्ण

अटल पूर्णांक get_mirror(काष्ठा mirror_set *ms, काष्ठा dm_target *ti,
		      अचिन्हित पूर्णांक mirror, अक्षर **argv)
अणु
	अचिन्हित दीर्घ दीर्घ offset;
	अक्षर dummy;
	पूर्णांक ret;

	अगर (माला_पूछो(argv[1], "%llu%c", &offset, &dummy) != 1 ||
	    offset != (sector_t)offset) अणु
		ti->error = "Invalid offset";
		वापस -EINVAL;
	पूर्ण

	ret = dm_get_device(ti, argv[0], dm_table_get_mode(ti->table),
			    &ms->mirror[mirror].dev);
	अगर (ret) अणु
		ti->error = "Device lookup failure";
		वापस ret;
	पूर्ण

	ms->mirror[mirror].ms = ms;
	atomic_set(&(ms->mirror[mirror].error_count), 0);
	ms->mirror[mirror].error_type = 0;
	ms->mirror[mirror].offset = offset;

	वापस 0;
पूर्ण

/*
 * Create dirty log: log_type #log_params <log_params>
 */
अटल काष्ठा dm_dirty_log *create_dirty_log(काष्ठा dm_target *ti,
					     अचिन्हित argc, अक्षर **argv,
					     अचिन्हित *args_used)
अणु
	अचिन्हित param_count;
	काष्ठा dm_dirty_log *dl;
	अक्षर dummy;

	अगर (argc < 2) अणु
		ti->error = "Insufficient mirror log arguments";
		वापस शून्य;
	पूर्ण

	अगर (माला_पूछो(argv[1], "%u%c", &param_count, &dummy) != 1) अणु
		ti->error = "Invalid mirror log argument count";
		वापस शून्य;
	पूर्ण

	*args_used = 2 + param_count;

	अगर (argc < *args_used) अणु
		ti->error = "Insufficient mirror log arguments";
		वापस शून्य;
	पूर्ण

	dl = dm_dirty_log_create(argv[0], ti, mirror_flush, param_count,
				 argv + 2);
	अगर (!dl) अणु
		ti->error = "Error creating mirror dirty log";
		वापस शून्य;
	पूर्ण

	वापस dl;
पूर्ण

अटल पूर्णांक parse_features(काष्ठा mirror_set *ms, अचिन्हित argc, अक्षर **argv,
			  अचिन्हित *args_used)
अणु
	अचिन्हित num_features;
	काष्ठा dm_target *ti = ms->ti;
	अक्षर dummy;
	पूर्णांक i;

	*args_used = 0;

	अगर (!argc)
		वापस 0;

	अगर (माला_पूछो(argv[0], "%u%c", &num_features, &dummy) != 1) अणु
		ti->error = "Invalid number of features";
		वापस -EINVAL;
	पूर्ण

	argc--;
	argv++;
	(*args_used)++;

	अगर (num_features > argc) अणु
		ti->error = "Not enough arguments to support feature count";
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_features; i++) अणु
		अगर (!म_भेद("handle_errors", argv[0]))
			ms->features |= DM_RAID1_HANDLE_ERRORS;
		अन्यथा अगर (!म_भेद("keep_log", argv[0]))
			ms->features |= DM_RAID1_KEEP_LOG;
		अन्यथा अणु
			ti->error = "Unrecognised feature requested";
			वापस -EINVAL;
		पूर्ण

		argc--;
		argv++;
		(*args_used)++;
	पूर्ण
	अगर (!errors_handled(ms) && keep_log(ms)) अणु
		ti->error = "keep_log feature requires the handle_errors feature";
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Conकाष्ठा a mirror mapping:
 *
 * log_type #log_params <log_params>
 * #mirrors [mirror_path offset]अणु2,पूर्ण
 * [#features <features>]
 *
 * log_type is "core" or "disk"
 * #log_params is between 1 and 3
 *
 * If present, supported features are "handle_errors" and "keep_log".
 */
अटल पूर्णांक mirror_ctr(काष्ठा dm_target *ti, अचिन्हित पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक nr_mirrors, m, args_used;
	काष्ठा mirror_set *ms;
	काष्ठा dm_dirty_log *dl;
	अक्षर dummy;

	dl = create_dirty_log(ti, argc, argv, &args_used);
	अगर (!dl)
		वापस -EINVAL;

	argv += args_used;
	argc -= args_used;

	अगर (!argc || माला_पूछो(argv[0], "%u%c", &nr_mirrors, &dummy) != 1 ||
	    nr_mirrors < 2 || nr_mirrors > MAX_NR_MIRRORS) अणु
		ti->error = "Invalid number of mirrors";
		dm_dirty_log_destroy(dl);
		वापस -EINVAL;
	पूर्ण

	argv++, argc--;

	अगर (argc < nr_mirrors * 2) अणु
		ti->error = "Too few mirror arguments";
		dm_dirty_log_destroy(dl);
		वापस -EINVAL;
	पूर्ण

	ms = alloc_context(nr_mirrors, dl->type->get_region_size(dl), ti, dl);
	अगर (!ms) अणु
		dm_dirty_log_destroy(dl);
		वापस -ENOMEM;
	पूर्ण

	/* Get the mirror parameter sets */
	क्रम (m = 0; m < nr_mirrors; m++) अणु
		r = get_mirror(ms, ti, m, argv);
		अगर (r) अणु
			मुक्त_context(ms, ti, m);
			वापस r;
		पूर्ण
		argv += 2;
		argc -= 2;
	पूर्ण

	ti->निजी = ms;

	r = dm_set_target_max_io_len(ti, dm_rh_get_region_size(ms->rh));
	अगर (r)
		जाओ err_मुक्त_context;

	ti->num_flush_bios = 1;
	ti->num_discard_bios = 1;
	ti->per_io_data_size = माप(काष्ठा dm_raid1_bio_record);

	ms->kmirrord_wq = alloc_workqueue("kmirrord", WQ_MEM_RECLAIM, 0);
	अगर (!ms->kmirrord_wq) अणु
		DMERR("couldn't start kmirrord");
		r = -ENOMEM;
		जाओ err_मुक्त_context;
	पूर्ण
	INIT_WORK(&ms->kmirrord_work, करो_mirror);
	समयr_setup(&ms->समयr, delayed_wake_fn, 0);
	ms->समयr_pending = 0;
	INIT_WORK(&ms->trigger_event, trigger_event);

	r = parse_features(ms, argc, argv, &args_used);
	अगर (r)
		जाओ err_destroy_wq;

	argv += args_used;
	argc -= args_used;

	/*
	 * Any पढ़ो-balancing addition depends on the
	 * DM_RAID1_HANDLE_ERRORS flag being present.
	 * This is because the decision to balance depends
	 * on the sync state of a region.  If the above
	 * flag is not present, we ignore errors; and
	 * the sync state may be inaccurate.
	 */

	अगर (argc) अणु
		ti->error = "Too many mirror arguments";
		r = -EINVAL;
		जाओ err_destroy_wq;
	पूर्ण

	ms->kcopyd_client = dm_kcopyd_client_create(&dm_kcopyd_throttle);
	अगर (IS_ERR(ms->kcopyd_client)) अणु
		r = PTR_ERR(ms->kcopyd_client);
		जाओ err_destroy_wq;
	पूर्ण

	wakeup_mirrord(ms);
	वापस 0;

err_destroy_wq:
	destroy_workqueue(ms->kmirrord_wq);
err_मुक्त_context:
	मुक्त_context(ms, ti, ms->nr_mirrors);
	वापस r;
पूर्ण

अटल व्योम mirror_dtr(काष्ठा dm_target *ti)
अणु
	काष्ठा mirror_set *ms = (काष्ठा mirror_set *) ti->निजी;

	del_समयr_sync(&ms->समयr);
	flush_workqueue(ms->kmirrord_wq);
	flush_work(&ms->trigger_event);
	dm_kcopyd_client_destroy(ms->kcopyd_client);
	destroy_workqueue(ms->kmirrord_wq);
	मुक्त_context(ms, ti, ms->nr_mirrors);
पूर्ण

/*
 * Mirror mapping function
 */
अटल पूर्णांक mirror_map(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	पूर्णांक r, rw = bio_data_dir(bio);
	काष्ठा mirror *m;
	काष्ठा mirror_set *ms = ti->निजी;
	काष्ठा dm_dirty_log *log = dm_rh_dirty_log(ms->rh);
	काष्ठा dm_raid1_bio_record *bio_record =
	  dm_per_bio_data(bio, माप(काष्ठा dm_raid1_bio_record));

	bio_record->details.bi_bdev = शून्य;

	अगर (rw == WRITE) अणु
		/* Save region क्रम mirror_end_io() handler */
		bio_record->ग_लिखो_region = dm_rh_bio_to_region(ms->rh, bio);
		queue_bio(ms, bio, rw);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	r = log->type->in_sync(log, dm_rh_bio_to_region(ms->rh, bio), 0);
	अगर (r < 0 && r != -EWOULDBLOCK)
		वापस DM_MAPIO_KILL;

	/*
	 * If region is not in-sync queue the bio.
	 */
	अगर (!r || (r == -EWOULDBLOCK)) अणु
		अगर (bio->bi_opf & REQ_RAHEAD)
			वापस DM_MAPIO_KILL;

		queue_bio(ms, bio, rw);
		वापस DM_MAPIO_SUBMITTED;
	पूर्ण

	/*
	 * The region is in-sync and we can perक्रमm पढ़ोs directly.
	 * Store enough inक्रमmation so we can retry अगर it fails.
	 */
	m = choose_mirror(ms, bio->bi_iter.bi_sector);
	अगर (unlikely(!m))
		वापस DM_MAPIO_KILL;

	dm_bio_record(&bio_record->details, bio);
	bio_record->m = m;

	map_bio(m, bio);

	वापस DM_MAPIO_REMAPPED;
पूर्ण

अटल पूर्णांक mirror_end_io(काष्ठा dm_target *ti, काष्ठा bio *bio,
		blk_status_t *error)
अणु
	पूर्णांक rw = bio_data_dir(bio);
	काष्ठा mirror_set *ms = (काष्ठा mirror_set *) ti->निजी;
	काष्ठा mirror *m = शून्य;
	काष्ठा dm_bio_details *bd = शून्य;
	काष्ठा dm_raid1_bio_record *bio_record =
	  dm_per_bio_data(bio, माप(काष्ठा dm_raid1_bio_record));

	/*
	 * We need to dec pending अगर this was a ग_लिखो.
	 */
	अगर (rw == WRITE) अणु
		अगर (!(bio->bi_opf & REQ_PREFLUSH) &&
		    bio_op(bio) != REQ_OP_DISCARD)
			dm_rh_dec(ms->rh, bio_record->ग_लिखो_region);
		वापस DM_ENDIO_DONE;
	पूर्ण

	अगर (*error == BLK_STS_NOTSUPP)
		जाओ out;

	अगर (bio->bi_opf & REQ_RAHEAD)
		जाओ out;

	अगर (unlikely(*error)) अणु
		अगर (!bio_record->details.bi_bdev) अणु
			/*
			 * There wasn't enough memory to record necessary
			 * inक्रमmation क्रम a retry or there was no other
			 * mirror in-sync.
			 */
			DMERR_LIMIT("Mirror read failed.");
			वापस DM_ENDIO_DONE;
		पूर्ण

		m = bio_record->m;

		DMERR("Mirror read failed from %s. Trying alternative device.",
		      m->dev->name);

		fail_mirror(m, DM_RAID1_READ_ERROR);

		/*
		 * A failed पढ़ो is requeued क्रम another attempt using an पूर्णांकact
		 * mirror.
		 */
		अगर (शेष_ok(m) || mirror_available(ms, bio)) अणु
			bd = &bio_record->details;

			dm_bio_restore(bd, bio);
			bio_record->details.bi_bdev = शून्य;
			bio->bi_status = 0;

			queue_bio(ms, bio, rw);
			वापस DM_ENDIO_INCOMPLETE;
		पूर्ण
		DMERR("All replicated volumes dead, failing I/O");
	पूर्ण

out:
	bio_record->details.bi_bdev = शून्य;

	वापस DM_ENDIO_DONE;
पूर्ण

अटल व्योम mirror_presuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा mirror_set *ms = (काष्ठा mirror_set *) ti->निजी;
	काष्ठा dm_dirty_log *log = dm_rh_dirty_log(ms->rh);

	काष्ठा bio_list holds;
	काष्ठा bio *bio;

	atomic_set(&ms->suspend, 1);

	/*
	 * Process bios in the hold list to start recovery रुकोing
	 * क्रम bios in the hold list. After the process, no bio has
	 * a chance to be added in the hold list because ms->suspend
	 * is set.
	 */
	spin_lock_irq(&ms->lock);
	holds = ms->holds;
	bio_list_init(&ms->holds);
	spin_unlock_irq(&ms->lock);

	जबतक ((bio = bio_list_pop(&holds)))
		hold_bio(ms, bio);

	/*
	 * We must finish up all the work that we've
	 * generated (i.e. recovery work).
	 */
	dm_rh_stop_recovery(ms->rh);

	रुको_event(_kmirrord_recovery_stopped,
		   !dm_rh_recovery_in_flight(ms->rh));

	अगर (log->type->presuspend && log->type->presuspend(log))
		/* FIXME: need better error handling */
		DMWARN("log presuspend failed");

	/*
	 * Now that recovery is complete/stopped and the
	 * delayed bios are queued, we need to रुको क्रम
	 * the worker thपढ़ो to complete.  This way,
	 * we know that all of our I/O has been pushed.
	 */
	flush_workqueue(ms->kmirrord_wq);
पूर्ण

अटल व्योम mirror_postsuspend(काष्ठा dm_target *ti)
अणु
	काष्ठा mirror_set *ms = ti->निजी;
	काष्ठा dm_dirty_log *log = dm_rh_dirty_log(ms->rh);

	अगर (log->type->postsuspend && log->type->postsuspend(log))
		/* FIXME: need better error handling */
		DMWARN("log postsuspend failed");
पूर्ण

अटल व्योम mirror_resume(काष्ठा dm_target *ti)
अणु
	काष्ठा mirror_set *ms = ti->निजी;
	काष्ठा dm_dirty_log *log = dm_rh_dirty_log(ms->rh);

	atomic_set(&ms->suspend, 0);
	अगर (log->type->resume && log->type->resume(log))
		/* FIXME: need better error handling */
		DMWARN("log resume failed");
	dm_rh_start_recovery(ms->rh);
पूर्ण

/*
 * device_status_अक्षर
 * @m: mirror device/leg we want the status of
 *
 * We वापस one अक्षरacter representing the most severe error
 * we have encountered.
 *    A => Alive - No failures
 *    D => Dead - A ग_लिखो failure occurred leaving mirror out-of-sync
 *    S => Sync - A sychronization failure occurred, mirror out-of-sync
 *    R => Read - A पढ़ो failure occurred, mirror data unaffected
 *
 * Returns: <अक्षर>
 */
अटल अक्षर device_status_अक्षर(काष्ठा mirror *m)
अणु
	अगर (!atomic_पढ़ो(&(m->error_count)))
		वापस 'A';

	वापस (test_bit(DM_RAID1_FLUSH_ERROR, &(m->error_type))) ? 'F' :
		(test_bit(DM_RAID1_WRITE_ERROR, &(m->error_type))) ? 'D' :
		(test_bit(DM_RAID1_SYNC_ERROR, &(m->error_type))) ? 'S' :
		(test_bit(DM_RAID1_READ_ERROR, &(m->error_type))) ? 'R' : 'U';
पूर्ण


अटल व्योम mirror_status(काष्ठा dm_target *ti, status_type_t type,
			  अचिन्हित status_flags, अक्षर *result, अचिन्हित maxlen)
अणु
	अचिन्हित पूर्णांक m, sz = 0;
	पूर्णांक num_feature_args = 0;
	काष्ठा mirror_set *ms = (काष्ठा mirror_set *) ti->निजी;
	काष्ठा dm_dirty_log *log = dm_rh_dirty_log(ms->rh);
	अक्षर buffer[MAX_NR_MIRRORS + 1];

	चयन (type) अणु
	हाल STATUSTYPE_INFO:
		DMEMIT("%d ", ms->nr_mirrors);
		क्रम (m = 0; m < ms->nr_mirrors; m++) अणु
			DMEMIT("%s ", ms->mirror[m].dev->name);
			buffer[m] = device_status_अक्षर(&(ms->mirror[m]));
		पूर्ण
		buffer[m] = '\0';

		DMEMIT("%llu/%llu 1 %s ",
		      (अचिन्हित दीर्घ दीर्घ)log->type->get_sync_count(log),
		      (अचिन्हित दीर्घ दीर्घ)ms->nr_regions, buffer);

		sz += log->type->status(log, type, result+sz, maxlen-sz);

		अवरोध;

	हाल STATUSTYPE_TABLE:
		sz = log->type->status(log, type, result, maxlen);

		DMEMIT("%d", ms->nr_mirrors);
		क्रम (m = 0; m < ms->nr_mirrors; m++)
			DMEMIT(" %s %llu", ms->mirror[m].dev->name,
			       (अचिन्हित दीर्घ दीर्घ)ms->mirror[m].offset);

		num_feature_args += !!errors_handled(ms);
		num_feature_args += !!keep_log(ms);
		अगर (num_feature_args) अणु
			DMEMIT(" %d", num_feature_args);
			अगर (errors_handled(ms))
				DMEMIT(" handle_errors");
			अगर (keep_log(ms))
				DMEMIT(" keep_log");
		पूर्ण

		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mirror_iterate_devices(काष्ठा dm_target *ti,
				  iterate_devices_callout_fn fn, व्योम *data)
अणु
	काष्ठा mirror_set *ms = ti->निजी;
	पूर्णांक ret = 0;
	अचिन्हित i;

	क्रम (i = 0; !ret && i < ms->nr_mirrors; i++)
		ret = fn(ti, ms->mirror[i].dev,
			 ms->mirror[i].offset, ti->len, data);

	वापस ret;
पूर्ण

अटल काष्ठा target_type mirror_target = अणु
	.name	 = "mirror",
	.version = अणु1, 14, 0पूर्ण,
	.module	 = THIS_MODULE,
	.ctr	 = mirror_ctr,
	.dtr	 = mirror_dtr,
	.map	 = mirror_map,
	.end_io	 = mirror_end_io,
	.presuspend = mirror_presuspend,
	.postsuspend = mirror_postsuspend,
	.resume	 = mirror_resume,
	.status	 = mirror_status,
	.iterate_devices = mirror_iterate_devices,
पूर्ण;

अटल पूर्णांक __init dm_mirror_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_रेजिस्टर_target(&mirror_target);
	अगर (r < 0) अणु
		DMERR("Failed to register mirror target");
		जाओ bad_target;
	पूर्ण

	वापस 0;

bad_target:
	वापस r;
पूर्ण

अटल व्योम __निकास dm_mirror_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&mirror_target);
पूर्ण

/* Module hooks */
module_init(dm_mirror_init);
module_निकास(dm_mirror_निकास);

MODULE_DESCRIPTION(DM_NAME " mirror target");
MODULE_AUTHOR("Joe Thornber");
MODULE_LICENSE("GPL");
