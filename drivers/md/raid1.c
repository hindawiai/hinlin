<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * raid1.c : Multiple Devices driver क्रम Linux
 *
 * Copyright (C) 1999, 2000, 2001 Ingo Molnar, Red Hat
 *
 * Copyright (C) 1996, 1997, 1998 Ingo Molnar, Miguel de Icaza, Gadi Oxman
 *
 * RAID-1 management functions.
 *
 * Better पढ़ो-balancing code written by Mika Kuoppala <miku@iki.fi>, 2000
 *
 * Fixes to reस्थिरruction by Jakob थstergaard" <jakob@ostenfeld.dk>
 * Various fixes by Neil Brown <neilb@cse.unsw.edu.au>
 *
 * Changes by Peter T. Breuer <ptb@it.uc3m.es> 31/1/2003 to support
 * biपंचांगapped पूर्णांकelligence in resync:
 *
 *      - biपंचांगap marked during normal i/o
 *      - biपंचांगap used to skip nondirty blocks during sync
 *
 * Additions to biपंचांगap code, (C) 2003-2004 Paul Clements, SteelEye Technology:
 * - persistent biपंचांगap code
 */

#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/पूर्णांकerval_tree_generic.h>

#समावेश <trace/events/block.h>

#समावेश "md.h"
#समावेश "raid1.h"
#समावेश "md-bitmap.h"

#घोषणा UNSUPPORTED_MDDEV_FLAGS		\
	((1L << MD_HAS_JOURNAL) |	\
	 (1L << MD_JOURNAL_CLEAN) |	\
	 (1L << MD_HAS_PPL) |		\
	 (1L << MD_HAS_MULTIPLE_PPLS))

अटल व्योम allow_barrier(काष्ठा r1conf *conf, sector_t sector_nr);
अटल व्योम lower_barrier(काष्ठा r1conf *conf, sector_t sector_nr);

#घोषणा raid1_log(md, fmt, args...)				\
	करो अणु अगर ((md)->queue) blk_add_trace_msg((md)->queue, "raid1 " fmt, ##args); पूर्ण जबतक (0)

#समावेश "raid1-10.c"

#घोषणा START(node) ((node)->start)
#घोषणा LAST(node) ((node)->last)
INTERVAL_TREE_DEFINE(काष्ठा serial_info, node, sector_t, _subtree_last,
		     START, LAST, अटल अंतरभूत, raid1_rb);

अटल पूर्णांक check_and_add_serial(काष्ठा md_rdev *rdev, काष्ठा r1bio *r1_bio,
				काष्ठा serial_info *si, पूर्णांक idx)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	sector_t lo = r1_bio->sector;
	sector_t hi = lo + r1_bio->sectors;
	काष्ठा serial_in_rdev *serial = &rdev->serial[idx];

	spin_lock_irqsave(&serial->serial_lock, flags);
	/* collision happened */
	अगर (raid1_rb_iter_first(&serial->serial_rb, lo, hi))
		ret = -EBUSY;
	अन्यथा अणु
		si->start = lo;
		si->last = hi;
		raid1_rb_insert(si, &serial->serial_rb);
	पूर्ण
	spin_unlock_irqrestore(&serial->serial_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम रुको_क्रम_serialization(काष्ठा md_rdev *rdev, काष्ठा r1bio *r1_bio)
अणु
	काष्ठा mddev *mddev = rdev->mddev;
	काष्ठा serial_info *si;
	पूर्णांक idx = sector_to_idx(r1_bio->sector);
	काष्ठा serial_in_rdev *serial = &rdev->serial[idx];

	अगर (WARN_ON(!mddev->serial_info_pool))
		वापस;
	si = mempool_alloc(mddev->serial_info_pool, GFP_NOIO);
	रुको_event(serial->serial_io_रुको,
		   check_and_add_serial(rdev, r1_bio, si, idx) == 0);
पूर्ण

अटल व्योम हटाओ_serial(काष्ठा md_rdev *rdev, sector_t lo, sector_t hi)
अणु
	काष्ठा serial_info *si;
	अचिन्हित दीर्घ flags;
	पूर्णांक found = 0;
	काष्ठा mddev *mddev = rdev->mddev;
	पूर्णांक idx = sector_to_idx(lo);
	काष्ठा serial_in_rdev *serial = &rdev->serial[idx];

	spin_lock_irqsave(&serial->serial_lock, flags);
	क्रम (si = raid1_rb_iter_first(&serial->serial_rb, lo, hi);
	     si; si = raid1_rb_iter_next(si, lo, hi)) अणु
		अगर (si->start == lo && si->last == hi) अणु
			raid1_rb_हटाओ(si, &serial->serial_rb);
			mempool_मुक्त(si, mddev->serial_info_pool);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
		WARN(1, "The write IO is not recorded for serialization\n");
	spin_unlock_irqrestore(&serial->serial_lock, flags);
	wake_up(&serial->serial_io_रुको);
पूर्ण

/*
 * क्रम resync bio, r1bio poपूर्णांकer can be retrieved from the per-bio
 * 'struct resync_pages'.
 */
अटल अंतरभूत काष्ठा r1bio *get_resync_r1bio(काष्ठा bio *bio)
अणु
	वापस get_resync_pages(bio)->raid_bio;
पूर्ण

अटल व्योम * r1bio_pool_alloc(gfp_t gfp_flags, व्योम *data)
अणु
	काष्ठा pool_info *pi = data;
	पूर्णांक size = दुरत्व(काष्ठा r1bio, bios[pi->raid_disks]);

	/* allocate a r1bio with room क्रम raid_disks entries in the bios array */
	वापस kzalloc(size, gfp_flags);
पूर्ण

#घोषणा RESYNC_DEPTH 32
#घोषणा RESYNC_SECTORS (RESYNC_BLOCK_SIZE >> 9)
#घोषणा RESYNC_WINDOW (RESYNC_BLOCK_SIZE * RESYNC_DEPTH)
#घोषणा RESYNC_WINDOW_SECTORS (RESYNC_WINDOW >> 9)
#घोषणा CLUSTER_RESYNC_WINDOW (16 * RESYNC_WINDOW)
#घोषणा CLUSTER_RESYNC_WINDOW_SECTORS (CLUSTER_RESYNC_WINDOW >> 9)

अटल व्योम * r1buf_pool_alloc(gfp_t gfp_flags, व्योम *data)
अणु
	काष्ठा pool_info *pi = data;
	काष्ठा r1bio *r1_bio;
	काष्ठा bio *bio;
	पूर्णांक need_pages;
	पूर्णांक j;
	काष्ठा resync_pages *rps;

	r1_bio = r1bio_pool_alloc(gfp_flags, pi);
	अगर (!r1_bio)
		वापस शून्य;

	rps = kदो_स्मृति_array(pi->raid_disks, माप(काष्ठा resync_pages),
			    gfp_flags);
	अगर (!rps)
		जाओ out_मुक्त_r1bio;

	/*
	 * Allocate bios : 1 क्रम पढ़ोing, n-1 क्रम writing
	 */
	क्रम (j = pi->raid_disks ; j-- ; ) अणु
		bio = bio_kदो_स्मृति(gfp_flags, RESYNC_PAGES);
		अगर (!bio)
			जाओ out_मुक्त_bio;
		r1_bio->bios[j] = bio;
	पूर्ण
	/*
	 * Allocate RESYNC_PAGES data pages and attach them to
	 * the first bio.
	 * If this is a user-requested check/repair, allocate
	 * RESYNC_PAGES क्रम each bio.
	 */
	अगर (test_bit(MD_RECOVERY_REQUESTED, &pi->mddev->recovery))
		need_pages = pi->raid_disks;
	अन्यथा
		need_pages = 1;
	क्रम (j = 0; j < pi->raid_disks; j++) अणु
		काष्ठा resync_pages *rp = &rps[j];

		bio = r1_bio->bios[j];

		अगर (j < need_pages) अणु
			अगर (resync_alloc_pages(rp, gfp_flags))
				जाओ out_मुक्त_pages;
		पूर्ण अन्यथा अणु
			स_नकल(rp, &rps[0], माप(*rp));
			resync_get_all_pages(rp);
		पूर्ण

		rp->raid_bio = r1_bio;
		bio->bi_निजी = rp;
	पूर्ण

	r1_bio->master_bio = शून्य;

	वापस r1_bio;

out_मुक्त_pages:
	जबतक (--j >= 0)
		resync_मुक्त_pages(&rps[j]);

out_मुक्त_bio:
	जबतक (++j < pi->raid_disks)
		bio_put(r1_bio->bios[j]);
	kमुक्त(rps);

out_मुक्त_r1bio:
	rbio_pool_मुक्त(r1_bio, data);
	वापस शून्य;
पूर्ण

अटल व्योम r1buf_pool_मुक्त(व्योम *__r1_bio, व्योम *data)
अणु
	काष्ठा pool_info *pi = data;
	पूर्णांक i;
	काष्ठा r1bio *r1bio = __r1_bio;
	काष्ठा resync_pages *rp = शून्य;

	क्रम (i = pi->raid_disks; i--; ) अणु
		rp = get_resync_pages(r1bio->bios[i]);
		resync_मुक्त_pages(rp);
		bio_put(r1bio->bios[i]);
	पूर्ण

	/* resync pages array stored in the 1st bio's .bi_निजी */
	kमुक्त(rp);

	rbio_pool_मुक्त(r1bio, data);
पूर्ण

अटल व्योम put_all_bios(काष्ठा r1conf *conf, काष्ठा r1bio *r1_bio)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < conf->raid_disks * 2; i++) अणु
		काष्ठा bio **bio = r1_bio->bios + i;
		अगर (!BIO_SPECIAL(*bio))
			bio_put(*bio);
		*bio = शून्य;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_r1bio(काष्ठा r1bio *r1_bio)
अणु
	काष्ठा r1conf *conf = r1_bio->mddev->निजी;

	put_all_bios(conf, r1_bio);
	mempool_मुक्त(r1_bio, &conf->r1bio_pool);
पूर्ण

अटल व्योम put_buf(काष्ठा r1bio *r1_bio)
अणु
	काष्ठा r1conf *conf = r1_bio->mddev->निजी;
	sector_t sect = r1_bio->sector;
	पूर्णांक i;

	क्रम (i = 0; i < conf->raid_disks * 2; i++) अणु
		काष्ठा bio *bio = r1_bio->bios[i];
		अगर (bio->bi_end_io)
			rdev_dec_pending(conf->mirrors[i].rdev, r1_bio->mddev);
	पूर्ण

	mempool_मुक्त(r1_bio, &conf->r1buf_pool);

	lower_barrier(conf, sect);
पूर्ण

अटल व्योम reschedule_retry(काष्ठा r1bio *r1_bio)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mddev *mddev = r1_bio->mddev;
	काष्ठा r1conf *conf = mddev->निजी;
	पूर्णांक idx;

	idx = sector_to_idx(r1_bio->sector);
	spin_lock_irqsave(&conf->device_lock, flags);
	list_add(&r1_bio->retry_list, &conf->retry_list);
	atomic_inc(&conf->nr_queued[idx]);
	spin_unlock_irqrestore(&conf->device_lock, flags);

	wake_up(&conf->रुको_barrier);
	md_wakeup_thपढ़ो(mddev->thपढ़ो);
पूर्ण

/*
 * raid_end_bio_io() is called when we have finished servicing a mirrored
 * operation and are पढ़ोy to वापस a success/failure code to the buffer
 * cache layer.
 */
अटल व्योम call_bio_endio(काष्ठा r1bio *r1_bio)
अणु
	काष्ठा bio *bio = r1_bio->master_bio;

	अगर (!test_bit(R1BIO_Uptodate, &r1_bio->state))
		bio->bi_status = BLK_STS_IOERR;

	bio_endio(bio);
पूर्ण

अटल व्योम raid_end_bio_io(काष्ठा r1bio *r1_bio)
अणु
	काष्ठा bio *bio = r1_bio->master_bio;
	काष्ठा r1conf *conf = r1_bio->mddev->निजी;

	/* अगर nobody has करोne the final endio yet, करो it now */
	अगर (!test_and_set_bit(R1BIO_Returned, &r1_bio->state)) अणु
		pr_debug("raid1: sync end %s on sectors %llu-%llu\n",
			 (bio_data_dir(bio) == WRITE) ? "write" : "read",
			 (अचिन्हित दीर्घ दीर्घ) bio->bi_iter.bi_sector,
			 (अचिन्हित दीर्घ दीर्घ) bio_end_sector(bio) - 1);

		call_bio_endio(r1_bio);
	पूर्ण
	/*
	 * Wake up any possible resync thपढ़ो that रुकोs क्रम the device
	 * to go idle.  All I/Os, even ग_लिखो-behind ग_लिखोs, are करोne.
	 */
	allow_barrier(conf, r1_bio->sector);

	मुक्त_r1bio(r1_bio);
पूर्ण

/*
 * Update disk head position estimator based on IRQ completion info.
 */
अटल अंतरभूत व्योम update_head_pos(पूर्णांक disk, काष्ठा r1bio *r1_bio)
अणु
	काष्ठा r1conf *conf = r1_bio->mddev->निजी;

	conf->mirrors[disk].head_position =
		r1_bio->sector + (r1_bio->sectors);
पूर्ण

/*
 * Find the disk number which triggered given bio
 */
अटल पूर्णांक find_bio_disk(काष्ठा r1bio *r1_bio, काष्ठा bio *bio)
अणु
	पूर्णांक mirror;
	काष्ठा r1conf *conf = r1_bio->mddev->निजी;
	पूर्णांक raid_disks = conf->raid_disks;

	क्रम (mirror = 0; mirror < raid_disks * 2; mirror++)
		अगर (r1_bio->bios[mirror] == bio)
			अवरोध;

	BUG_ON(mirror == raid_disks * 2);
	update_head_pos(mirror, r1_bio);

	वापस mirror;
पूर्ण

अटल व्योम raid1_end_पढ़ो_request(काष्ठा bio *bio)
अणु
	पूर्णांक uptodate = !bio->bi_status;
	काष्ठा r1bio *r1_bio = bio->bi_निजी;
	काष्ठा r1conf *conf = r1_bio->mddev->निजी;
	काष्ठा md_rdev *rdev = conf->mirrors[r1_bio->पढ़ो_disk].rdev;

	/*
	 * this branch is our 'one mirror IO has finished' event handler:
	 */
	update_head_pos(r1_bio->पढ़ो_disk, r1_bio);

	अगर (uptodate)
		set_bit(R1BIO_Uptodate, &r1_bio->state);
	अन्यथा अगर (test_bit(FailFast, &rdev->flags) &&
		 test_bit(R1BIO_FailFast, &r1_bio->state))
		/* This was a fail-fast पढ़ो so we definitely
		 * want to retry */
		;
	अन्यथा अणु
		/* If all other devices have failed, we want to वापस
		 * the error upwards rather than fail the last device.
		 * Here we redefine "uptodate" to mean "Don't want to retry"
		 */
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&conf->device_lock, flags);
		अगर (r1_bio->mddev->degraded == conf->raid_disks ||
		    (r1_bio->mddev->degraded == conf->raid_disks-1 &&
		     test_bit(In_sync, &rdev->flags)))
			uptodate = 1;
		spin_unlock_irqrestore(&conf->device_lock, flags);
	पूर्ण

	अगर (uptodate) अणु
		raid_end_bio_io(r1_bio);
		rdev_dec_pending(rdev, conf->mddev);
	पूर्ण अन्यथा अणु
		/*
		 * oops, पढ़ो error:
		 */
		अक्षर b[BDEVNAME_SIZE];
		pr_err_ratelimited("md/raid1:%s: %s: rescheduling sector %llu\n",
				   mdname(conf->mddev),
				   bdevname(rdev->bdev, b),
				   (अचिन्हित दीर्घ दीर्घ)r1_bio->sector);
		set_bit(R1BIO_ReadError, &r1_bio->state);
		reschedule_retry(r1_bio);
		/* करोn't drop the reference on पढ़ो_disk yet */
	पूर्ण
पूर्ण

अटल व्योम बंद_ग_लिखो(काष्ठा r1bio *r1_bio)
अणु
	/* it really is the end of this request */
	अगर (test_bit(R1BIO_BehindIO, &r1_bio->state)) अणु
		bio_मुक्त_pages(r1_bio->behind_master_bio);
		bio_put(r1_bio->behind_master_bio);
		r1_bio->behind_master_bio = शून्य;
	पूर्ण
	/* clear the biपंचांगap अगर all ग_लिखोs complete successfully */
	md_biपंचांगap_endग_लिखो(r1_bio->mddev->biपंचांगap, r1_bio->sector,
			   r1_bio->sectors,
			   !test_bit(R1BIO_Degraded, &r1_bio->state),
			   test_bit(R1BIO_BehindIO, &r1_bio->state));
	md_ग_लिखो_end(r1_bio->mddev);
पूर्ण

अटल व्योम r1_bio_ग_लिखो_करोne(काष्ठा r1bio *r1_bio)
अणु
	अगर (!atomic_dec_and_test(&r1_bio->reमुख्यing))
		वापस;

	अगर (test_bit(R1BIO_WriteError, &r1_bio->state))
		reschedule_retry(r1_bio);
	अन्यथा अणु
		बंद_ग_लिखो(r1_bio);
		अगर (test_bit(R1BIO_MadeGood, &r1_bio->state))
			reschedule_retry(r1_bio);
		अन्यथा
			raid_end_bio_io(r1_bio);
	पूर्ण
पूर्ण

अटल व्योम raid1_end_ग_लिखो_request(काष्ठा bio *bio)
अणु
	काष्ठा r1bio *r1_bio = bio->bi_निजी;
	पूर्णांक behind = test_bit(R1BIO_BehindIO, &r1_bio->state);
	काष्ठा r1conf *conf = r1_bio->mddev->निजी;
	काष्ठा bio *to_put = शून्य;
	पूर्णांक mirror = find_bio_disk(r1_bio, bio);
	काष्ठा md_rdev *rdev = conf->mirrors[mirror].rdev;
	bool discard_error;
	sector_t lo = r1_bio->sector;
	sector_t hi = r1_bio->sector + r1_bio->sectors;

	discard_error = bio->bi_status && bio_op(bio) == REQ_OP_DISCARD;

	/*
	 * 'one mirror IO has finished' event handler:
	 */
	अगर (bio->bi_status && !discard_error) अणु
		set_bit(WriteErrorSeen,	&rdev->flags);
		अगर (!test_and_set_bit(WantReplacement, &rdev->flags))
			set_bit(MD_RECOVERY_NEEDED, &
				conf->mddev->recovery);

		अगर (test_bit(FailFast, &rdev->flags) &&
		    (bio->bi_opf & MD_FAILFAST) &&
		    /* We never try FailFast to WriteMostly devices */
		    !test_bit(WriteMostly, &rdev->flags)) अणु
			md_error(r1_bio->mddev, rdev);
		पूर्ण

		/*
		 * When the device is faulty, it is not necessary to
		 * handle ग_लिखो error.
		 * For failfast, this is the only reमुख्यing device,
		 * We need to retry the ग_लिखो without FailFast.
		 */
		अगर (!test_bit(Faulty, &rdev->flags))
			set_bit(R1BIO_WriteError, &r1_bio->state);
		अन्यथा अणु
			/* Fail the request */
			set_bit(R1BIO_Degraded, &r1_bio->state);
			/* Finished with this branch */
			r1_bio->bios[mirror] = शून्य;
			to_put = bio;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Set R1BIO_Uptodate in our master bio, so that we
		 * will वापस a good error code क्रम to the higher
		 * levels even अगर IO on some other mirrored buffer
		 * fails.
		 *
		 * The 'master' represents the composite IO operation
		 * to user-side. So अगर something रुकोs क्रम IO, then it
		 * will रुको क्रम the 'master' bio.
		 */
		sector_t first_bad;
		पूर्णांक bad_sectors;

		r1_bio->bios[mirror] = शून्य;
		to_put = bio;
		/*
		 * Do not set R1BIO_Uptodate अगर the current device is
		 * rebuilding or Faulty. This is because we cannot use
		 * such device क्रम properly पढ़ोing the data back (we could
		 * potentially use it, अगर the current ग_लिखो would have felt
		 * beक्रमe rdev->recovery_offset, but क्रम simplicity we करोn't
		 * check this here.
		 */
		अगर (test_bit(In_sync, &rdev->flags) &&
		    !test_bit(Faulty, &rdev->flags))
			set_bit(R1BIO_Uptodate, &r1_bio->state);

		/* Maybe we can clear some bad blocks. */
		अगर (is_badblock(rdev, r1_bio->sector, r1_bio->sectors,
				&first_bad, &bad_sectors) && !discard_error) अणु
			r1_bio->bios[mirror] = IO_MADE_GOOD;
			set_bit(R1BIO_MadeGood, &r1_bio->state);
		पूर्ण
	पूर्ण

	अगर (behind) अणु
		अगर (test_bit(CollisionCheck, &rdev->flags))
			हटाओ_serial(rdev, lo, hi);
		अगर (test_bit(WriteMostly, &rdev->flags))
			atomic_dec(&r1_bio->behind_reमुख्यing);

		/*
		 * In behind mode, we ACK the master bio once the I/O
		 * has safely reached all non-ग_लिखोmostly
		 * disks. Setting the Returned bit ensures that this
		 * माला_लो करोne only once -- we करोn't ever want to वापस
		 * -EIO here, instead we'll रुको
		 */
		अगर (atomic_पढ़ो(&r1_bio->behind_reमुख्यing) >= (atomic_पढ़ो(&r1_bio->reमुख्यing)-1) &&
		    test_bit(R1BIO_Uptodate, &r1_bio->state)) अणु
			/* Maybe we can वापस now */
			अगर (!test_and_set_bit(R1BIO_Returned, &r1_bio->state)) अणु
				काष्ठा bio *mbio = r1_bio->master_bio;
				pr_debug("raid1: behind end write sectors"
					 " %llu-%llu\n",
					 (अचिन्हित दीर्घ दीर्घ) mbio->bi_iter.bi_sector,
					 (अचिन्हित दीर्घ दीर्घ) bio_end_sector(mbio) - 1);
				call_bio_endio(r1_bio);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (rdev->mddev->serialize_policy)
		हटाओ_serial(rdev, lo, hi);
	अगर (r1_bio->bios[mirror] == शून्य)
		rdev_dec_pending(rdev, conf->mddev);

	/*
	 * Let's see अगर all mirrored ग_लिखो operations have finished
	 * alपढ़ोy.
	 */
	r1_bio_ग_लिखो_करोne(r1_bio);

	अगर (to_put)
		bio_put(to_put);
पूर्ण

अटल sector_t align_to_barrier_unit_end(sector_t start_sector,
					  sector_t sectors)
अणु
	sector_t len;

	WARN_ON(sectors == 0);
	/*
	 * len is the number of sectors from start_sector to end of the
	 * barrier unit which start_sector beदीर्घs to.
	 */
	len = round_up(start_sector + 1, BARRIER_UNIT_SECTOR_SIZE) -
	      start_sector;

	अगर (len > sectors)
		len = sectors;

	वापस len;
पूर्ण

/*
 * This routine वापसs the disk from which the requested पढ़ो should
 * be करोne. There is a per-array 'next expected sequential IO' sector
 * number - अगर this matches on the next IO then we use the last disk.
 * There is also a per-disk 'last know head position' sector that is
 * मुख्यtained from IRQ contexts, both the normal and the resync IO
 * completion handlers update this position correctly. If there is no
 * perfect sequential match then we pick the disk whose head is बंदst.
 *
 * If there are 2 mirrors in the same 2 devices, perक्रमmance degrades
 * because position is mirror, not device based.
 *
 * The rdev क्रम the device selected will have nr_pending incremented.
 */
अटल पूर्णांक पढ़ो_balance(काष्ठा r1conf *conf, काष्ठा r1bio *r1_bio, पूर्णांक *max_sectors)
अणु
	स्थिर sector_t this_sector = r1_bio->sector;
	पूर्णांक sectors;
	पूर्णांक best_good_sectors;
	पूर्णांक best_disk, best_dist_disk, best_pending_disk;
	पूर्णांक has_nonrot_disk;
	पूर्णांक disk;
	sector_t best_dist;
	अचिन्हित पूर्णांक min_pending;
	काष्ठा md_rdev *rdev;
	पूर्णांक choose_first;
	पूर्णांक choose_next_idle;

	rcu_पढ़ो_lock();
	/*
	 * Check अगर we can balance. We can balance on the whole
	 * device अगर no resync is going on, or below the resync winकरोw.
	 * We take the first पढ़ोable disk when above the resync winकरोw.
	 */
 retry:
	sectors = r1_bio->sectors;
	best_disk = -1;
	best_dist_disk = -1;
	best_dist = MaxSector;
	best_pending_disk = -1;
	min_pending = अच_पूर्णांक_उच्च;
	best_good_sectors = 0;
	has_nonrot_disk = 0;
	choose_next_idle = 0;
	clear_bit(R1BIO_FailFast, &r1_bio->state);

	अगर ((conf->mddev->recovery_cp < this_sector + sectors) ||
	    (mddev_is_clustered(conf->mddev) &&
	    md_cluster_ops->area_resyncing(conf->mddev, READ, this_sector,
		    this_sector + sectors)))
		choose_first = 1;
	अन्यथा
		choose_first = 0;

	क्रम (disk = 0 ; disk < conf->raid_disks * 2 ; disk++) अणु
		sector_t dist;
		sector_t first_bad;
		पूर्णांक bad_sectors;
		अचिन्हित पूर्णांक pending;
		bool nonrot;

		rdev = rcu_dereference(conf->mirrors[disk].rdev);
		अगर (r1_bio->bios[disk] == IO_BLOCKED
		    || rdev == शून्य
		    || test_bit(Faulty, &rdev->flags))
			जारी;
		अगर (!test_bit(In_sync, &rdev->flags) &&
		    rdev->recovery_offset < this_sector + sectors)
			जारी;
		अगर (test_bit(WriteMostly, &rdev->flags)) अणु
			/* Don't balance among ग_लिखो-mostly, just
			 * use the first as a last resort */
			अगर (best_dist_disk < 0) अणु
				अगर (is_badblock(rdev, this_sector, sectors,
						&first_bad, &bad_sectors)) अणु
					अगर (first_bad <= this_sector)
						/* Cannot use this */
						जारी;
					best_good_sectors = first_bad - this_sector;
				पूर्ण अन्यथा
					best_good_sectors = sectors;
				best_dist_disk = disk;
				best_pending_disk = disk;
			पूर्ण
			जारी;
		पूर्ण
		/* This is a reasonable device to use.  It might
		 * even be best.
		 */
		अगर (is_badblock(rdev, this_sector, sectors,
				&first_bad, &bad_sectors)) अणु
			अगर (best_dist < MaxSector)
				/* alपढ़ोy have a better device */
				जारी;
			अगर (first_bad <= this_sector) अणु
				/* cannot पढ़ो here. If this is the 'primary'
				 * device, then we must not पढ़ो beyond
				 * bad_sectors from another device..
				 */
				bad_sectors -= (this_sector - first_bad);
				अगर (choose_first && sectors > bad_sectors)
					sectors = bad_sectors;
				अगर (best_good_sectors > sectors)
					best_good_sectors = sectors;

			पूर्ण अन्यथा अणु
				sector_t good_sectors = first_bad - this_sector;
				अगर (good_sectors > best_good_sectors) अणु
					best_good_sectors = good_sectors;
					best_disk = disk;
				पूर्ण
				अगर (choose_first)
					अवरोध;
			पूर्ण
			जारी;
		पूर्ण अन्यथा अणु
			अगर ((sectors > best_good_sectors) && (best_disk >= 0))
				best_disk = -1;
			best_good_sectors = sectors;
		पूर्ण

		अगर (best_disk >= 0)
			/* At least two disks to choose from so failfast is OK */
			set_bit(R1BIO_FailFast, &r1_bio->state);

		nonrot = blk_queue_nonrot(bdev_get_queue(rdev->bdev));
		has_nonrot_disk |= nonrot;
		pending = atomic_पढ़ो(&rdev->nr_pending);
		dist = असल(this_sector - conf->mirrors[disk].head_position);
		अगर (choose_first) अणु
			best_disk = disk;
			अवरोध;
		पूर्ण
		/* Don't change to another disk क्रम sequential पढ़ोs */
		अगर (conf->mirrors[disk].next_seq_sect == this_sector
		    || dist == 0) अणु
			पूर्णांक opt_iosize = bdev_io_opt(rdev->bdev) >> 9;
			काष्ठा raid1_info *mirror = &conf->mirrors[disk];

			best_disk = disk;
			/*
			 * If buffered sequential IO size exceeds optimal
			 * iosize, check अगर there is idle disk. If yes, choose
			 * the idle disk. पढ़ो_balance could alपढ़ोy choose an
			 * idle disk beक्रमe noticing it's a sequential IO in
			 * this disk. This करोesn't matter because this disk
			 * will idle, next समय it will be utilized after the
			 * first disk has IO size exceeds optimal iosize. In
			 * this way, iosize of the first disk will be optimal
			 * iosize at least. iosize of the second disk might be
			 * small, but not a big deal since when the second disk
			 * starts IO, the first disk is likely still busy.
			 */
			अगर (nonrot && opt_iosize > 0 &&
			    mirror->seq_start != MaxSector &&
			    mirror->next_seq_sect > opt_iosize &&
			    mirror->next_seq_sect - opt_iosize >=
			    mirror->seq_start) अणु
				choose_next_idle = 1;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (choose_next_idle)
			जारी;

		अगर (min_pending > pending) अणु
			min_pending = pending;
			best_pending_disk = disk;
		पूर्ण

		अगर (dist < best_dist) अणु
			best_dist = dist;
			best_dist_disk = disk;
		पूर्ण
	पूर्ण

	/*
	 * If all disks are rotational, choose the बंदst disk. If any disk is
	 * non-rotational, choose the disk with less pending request even the
	 * disk is rotational, which might/might not be optimal क्रम raids with
	 * mixed ratation/non-rotational disks depending on workload.
	 */
	अगर (best_disk == -1) अणु
		अगर (has_nonrot_disk || min_pending == 0)
			best_disk = best_pending_disk;
		अन्यथा
			best_disk = best_dist_disk;
	पूर्ण

	अगर (best_disk >= 0) अणु
		rdev = rcu_dereference(conf->mirrors[best_disk].rdev);
		अगर (!rdev)
			जाओ retry;
		atomic_inc(&rdev->nr_pending);
		sectors = best_good_sectors;

		अगर (conf->mirrors[best_disk].next_seq_sect != this_sector)
			conf->mirrors[best_disk].seq_start = this_sector;

		conf->mirrors[best_disk].next_seq_sect = this_sector + sectors;
	पूर्ण
	rcu_पढ़ो_unlock();
	*max_sectors = sectors;

	वापस best_disk;
पूर्ण

अटल व्योम flush_bio_list(काष्ठा r1conf *conf, काष्ठा bio *bio)
अणु
	/* flush any pending biपंचांगap ग_लिखोs to disk beक्रमe proceeding w/ I/O */
	md_biपंचांगap_unplug(conf->mddev->biपंचांगap);
	wake_up(&conf->रुको_barrier);

	जबतक (bio) अणु /* submit pending ग_लिखोs */
		काष्ठा bio *next = bio->bi_next;
		काष्ठा md_rdev *rdev = (व्योम *)bio->bi_bdev;
		bio->bi_next = शून्य;
		bio_set_dev(bio, rdev->bdev);
		अगर (test_bit(Faulty, &rdev->flags)) अणु
			bio_io_error(bio);
		पूर्ण अन्यथा अगर (unlikely((bio_op(bio) == REQ_OP_DISCARD) &&
				    !blk_queue_discard(bio->bi_bdev->bd_disk->queue)))
			/* Just ignore it */
			bio_endio(bio);
		अन्यथा
			submit_bio_noacct(bio);
		bio = next;
		cond_resched();
	पूर्ण
पूर्ण

अटल व्योम flush_pending_ग_लिखोs(काष्ठा r1conf *conf)
अणु
	/* Any ग_लिखोs that have been queued but are aरुकोing
	 * biपंचांगap updates get flushed here.
	 */
	spin_lock_irq(&conf->device_lock);

	अगर (conf->pending_bio_list.head) अणु
		काष्ठा blk_plug plug;
		काष्ठा bio *bio;

		bio = bio_list_get(&conf->pending_bio_list);
		conf->pending_count = 0;
		spin_unlock_irq(&conf->device_lock);

		/*
		 * As this is called in a रुको_event() loop (see मुक्तze_array),
		 * current->state might be TASK_UNINTERRUPTIBLE which will
		 * cause a warning when we prepare to रुको again.  As it is
		 * rare that this path is taken, it is perfectly safe to क्रमce
		 * us to go around the रुको_event() loop again, so the warning
		 * is a false-positive.  Silence the warning by resetting
		 * thपढ़ो state
		 */
		__set_current_state(TASK_RUNNING);
		blk_start_plug(&plug);
		flush_bio_list(conf, bio);
		blk_finish_plug(&plug);
	पूर्ण अन्यथा
		spin_unlock_irq(&conf->device_lock);
पूर्ण

/* Barriers....
 * Someबार we need to suspend IO जबतक we करो something अन्यथा,
 * either some resync/recovery, or reconfigure the array.
 * To करो this we उठाओ a 'barrier'.
 * The 'barrier' is a counter that can be उठाओd multiple बार
 * to count how many activities are happening which preclude
 * normal IO.
 * We can only उठाओ the barrier अगर there is no pending IO.
 * i.e. अगर nr_pending == 0.
 * We choose only to उठाओ the barrier अगर no-one is रुकोing क्रम the
 * barrier to go करोwn.  This means that as soon as an IO request
 * is पढ़ोy, no other operations which require a barrier will start
 * until the IO request has had a chance.
 *
 * So: regular IO calls 'wait_barrier'.  When that वापसs there
 *    is no backgroup IO happening,  It must arrange to call
 *    allow_barrier when it has finished its IO.
 * backgroup IO calls must call उठाओ_barrier.  Once that वापसs
 *    there is no normal IO happeing.  It must arrange to call
 *    lower_barrier when the particular background IO completes.
 *
 * If resync/recovery is पूर्णांकerrupted, वापसs -EINTR;
 * Otherwise, वापसs 0.
 */
अटल पूर्णांक उठाओ_barrier(काष्ठा r1conf *conf, sector_t sector_nr)
अणु
	पूर्णांक idx = sector_to_idx(sector_nr);

	spin_lock_irq(&conf->resync_lock);

	/* Wait until no block IO is रुकोing */
	रुको_event_lock_irq(conf->रुको_barrier,
			    !atomic_पढ़ो(&conf->nr_रुकोing[idx]),
			    conf->resync_lock);

	/* block any new IO from starting */
	atomic_inc(&conf->barrier[idx]);
	/*
	 * In उठाओ_barrier() we firstly increase conf->barrier[idx] then
	 * check conf->nr_pending[idx]. In _रुको_barrier() we firstly
	 * increase conf->nr_pending[idx] then check conf->barrier[idx].
	 * A memory barrier here to make sure conf->nr_pending[idx] won't
	 * be fetched beक्रमe conf->barrier[idx] is increased. Otherwise
	 * there will be a race between उठाओ_barrier() and _रुको_barrier().
	 */
	smp_mb__after_atomic();

	/* For these conditions we must रुको:
	 * A: जबतक the array is in frozen state
	 * B: जबतक conf->nr_pending[idx] is not 0, meaning regular I/O
	 *    existing in corresponding I/O barrier bucket.
	 * C: जबतक conf->barrier[idx] >= RESYNC_DEPTH, meaning reaches
	 *    max resync count which allowed on current I/O barrier bucket.
	 */
	रुको_event_lock_irq(conf->रुको_barrier,
			    (!conf->array_frozen &&
			     !atomic_पढ़ो(&conf->nr_pending[idx]) &&
			     atomic_पढ़ो(&conf->barrier[idx]) < RESYNC_DEPTH) ||
				test_bit(MD_RECOVERY_INTR, &conf->mddev->recovery),
			    conf->resync_lock);

	अगर (test_bit(MD_RECOVERY_INTR, &conf->mddev->recovery)) अणु
		atomic_dec(&conf->barrier[idx]);
		spin_unlock_irq(&conf->resync_lock);
		wake_up(&conf->रुको_barrier);
		वापस -EINTR;
	पूर्ण

	atomic_inc(&conf->nr_sync_pending);
	spin_unlock_irq(&conf->resync_lock);

	वापस 0;
पूर्ण

अटल व्योम lower_barrier(काष्ठा r1conf *conf, sector_t sector_nr)
अणु
	पूर्णांक idx = sector_to_idx(sector_nr);

	BUG_ON(atomic_पढ़ो(&conf->barrier[idx]) <= 0);

	atomic_dec(&conf->barrier[idx]);
	atomic_dec(&conf->nr_sync_pending);
	wake_up(&conf->रुको_barrier);
पूर्ण

अटल व्योम _रुको_barrier(काष्ठा r1conf *conf, पूर्णांक idx)
अणु
	/*
	 * We need to increase conf->nr_pending[idx] very early here,
	 * then उठाओ_barrier() can be blocked when it रुकोs क्रम
	 * conf->nr_pending[idx] to be 0. Then we can aव्योम holding
	 * conf->resync_lock when there is no barrier उठाओd in same
	 * barrier unit bucket. Also अगर the array is frozen, I/O
	 * should be blocked until array is unfrozen.
	 */
	atomic_inc(&conf->nr_pending[idx]);
	/*
	 * In _रुको_barrier() we firstly increase conf->nr_pending[idx], then
	 * check conf->barrier[idx]. In उठाओ_barrier() we firstly increase
	 * conf->barrier[idx], then check conf->nr_pending[idx]. A memory
	 * barrier is necessary here to make sure conf->barrier[idx] won't be
	 * fetched beक्रमe conf->nr_pending[idx] is increased. Otherwise there
	 * will be a race between _रुको_barrier() and उठाओ_barrier().
	 */
	smp_mb__after_atomic();

	/*
	 * Don't worry about checking two atomic_t variables at same समय
	 * here. If during we check conf->barrier[idx], the array is
	 * frozen (conf->array_frozen is 1), and chonf->barrier[idx] is
	 * 0, it is safe to वापस and make the I/O जारी. Because the
	 * array is frozen, all I/O वापसed here will eventually complete
	 * or be queued, no race will happen. See code comment in
	 * frozen_array().
	 */
	अगर (!READ_ONCE(conf->array_frozen) &&
	    !atomic_पढ़ो(&conf->barrier[idx]))
		वापस;

	/*
	 * After holding conf->resync_lock, conf->nr_pending[idx]
	 * should be decreased beक्रमe रुकोing क्रम barrier to drop.
	 * Otherwise, we may encounter a race condition because
	 * उठाओ_barrer() might be रुकोing क्रम conf->nr_pending[idx]
	 * to be 0 at same समय.
	 */
	spin_lock_irq(&conf->resync_lock);
	atomic_inc(&conf->nr_रुकोing[idx]);
	atomic_dec(&conf->nr_pending[idx]);
	/*
	 * In हाल मुक्तze_array() is रुकोing क्रम
	 * get_unqueued_pending() == extra
	 */
	wake_up(&conf->रुको_barrier);
	/* Wait क्रम the barrier in same barrier unit bucket to drop. */
	रुको_event_lock_irq(conf->रुको_barrier,
			    !conf->array_frozen &&
			     !atomic_पढ़ो(&conf->barrier[idx]),
			    conf->resync_lock);
	atomic_inc(&conf->nr_pending[idx]);
	atomic_dec(&conf->nr_रुकोing[idx]);
	spin_unlock_irq(&conf->resync_lock);
पूर्ण

अटल व्योम रुको_पढ़ो_barrier(काष्ठा r1conf *conf, sector_t sector_nr)
अणु
	पूर्णांक idx = sector_to_idx(sector_nr);

	/*
	 * Very similar to _रुको_barrier(). The dअगरference is, क्रम पढ़ो
	 * I/O we करोn't need रुको क्रम sync I/O, but अगर the whole array
	 * is frozen, the पढ़ो I/O still has to रुको until the array is
	 * unfrozen. Since there is no ordering requirement with
	 * conf->barrier[idx] here, memory barrier is unnecessary as well.
	 */
	atomic_inc(&conf->nr_pending[idx]);

	अगर (!READ_ONCE(conf->array_frozen))
		वापस;

	spin_lock_irq(&conf->resync_lock);
	atomic_inc(&conf->nr_रुकोing[idx]);
	atomic_dec(&conf->nr_pending[idx]);
	/*
	 * In हाल मुक्तze_array() is रुकोing क्रम
	 * get_unqueued_pending() == extra
	 */
	wake_up(&conf->रुको_barrier);
	/* Wait क्रम array to be unfrozen */
	रुको_event_lock_irq(conf->रुको_barrier,
			    !conf->array_frozen,
			    conf->resync_lock);
	atomic_inc(&conf->nr_pending[idx]);
	atomic_dec(&conf->nr_रुकोing[idx]);
	spin_unlock_irq(&conf->resync_lock);
पूर्ण

अटल व्योम रुको_barrier(काष्ठा r1conf *conf, sector_t sector_nr)
अणु
	पूर्णांक idx = sector_to_idx(sector_nr);

	_रुको_barrier(conf, idx);
पूर्ण

अटल व्योम _allow_barrier(काष्ठा r1conf *conf, पूर्णांक idx)
अणु
	atomic_dec(&conf->nr_pending[idx]);
	wake_up(&conf->रुको_barrier);
पूर्ण

अटल व्योम allow_barrier(काष्ठा r1conf *conf, sector_t sector_nr)
अणु
	पूर्णांक idx = sector_to_idx(sector_nr);

	_allow_barrier(conf, idx);
पूर्ण

/* conf->resync_lock should be held */
अटल पूर्णांक get_unqueued_pending(काष्ठा r1conf *conf)
अणु
	पूर्णांक idx, ret;

	ret = atomic_पढ़ो(&conf->nr_sync_pending);
	क्रम (idx = 0; idx < BARRIER_BUCKETS_NR; idx++)
		ret += atomic_पढ़ो(&conf->nr_pending[idx]) -
			atomic_पढ़ो(&conf->nr_queued[idx]);

	वापस ret;
पूर्ण

अटल व्योम मुक्तze_array(काष्ठा r1conf *conf, पूर्णांक extra)
अणु
	/* Stop sync I/O and normal I/O and रुको क्रम everything to
	 * go quiet.
	 * This is called in two situations:
	 * 1) management command handlers (reshape, हटाओ disk, quiesce).
	 * 2) one normal I/O request failed.

	 * After array_frozen is set to 1, new sync IO will be blocked at
	 * उठाओ_barrier(), and new normal I/O will blocked at _रुको_barrier()
	 * or रुको_पढ़ो_barrier(). The flying I/Os will either complete or be
	 * queued. When everything goes quite, there are only queued I/Os left.

	 * Every flying I/O contributes to a conf->nr_pending[idx], idx is the
	 * barrier bucket index which this I/O request hits. When all sync and
	 * normal I/O are queued, sum of all conf->nr_pending[] will match sum
	 * of all conf->nr_queued[]. But normal I/O failure is an exception,
	 * in handle_पढ़ो_error(), we may call मुक्तze_array() beक्रमe trying to
	 * fix the पढ़ो error. In this हाल, the error पढ़ो I/O is not queued,
	 * so get_unqueued_pending() == 1.
	 *
	 * Thereक्रमe beक्रमe this function वापसs, we need to रुको until
	 * get_unqueued_pendings(conf) माला_लो equal to extra. For
	 * normal I/O context, extra is 1, in rested situations extra is 0.
	 */
	spin_lock_irq(&conf->resync_lock);
	conf->array_frozen = 1;
	raid1_log(conf->mddev, "wait freeze");
	रुको_event_lock_irq_cmd(
		conf->रुको_barrier,
		get_unqueued_pending(conf) == extra,
		conf->resync_lock,
		flush_pending_ग_लिखोs(conf));
	spin_unlock_irq(&conf->resync_lock);
पूर्ण
अटल व्योम unमुक्तze_array(काष्ठा r1conf *conf)
अणु
	/* reverse the effect of the मुक्तze */
	spin_lock_irq(&conf->resync_lock);
	conf->array_frozen = 0;
	spin_unlock_irq(&conf->resync_lock);
	wake_up(&conf->रुको_barrier);
पूर्ण

अटल व्योम alloc_behind_master_bio(काष्ठा r1bio *r1_bio,
					   काष्ठा bio *bio)
अणु
	पूर्णांक size = bio->bi_iter.bi_size;
	अचिन्हित vcnt = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	पूर्णांक i = 0;
	काष्ठा bio *behind_bio = शून्य;

	behind_bio = bio_alloc_bioset(GFP_NOIO, vcnt, &r1_bio->mddev->bio_set);
	अगर (!behind_bio)
		वापस;

	/* discard op, we करोn't support ग_लिखोzero/ग_लिखोsame yet */
	अगर (!bio_has_data(bio)) अणु
		behind_bio->bi_iter.bi_size = size;
		जाओ skip_copy;
	पूर्ण

	behind_bio->bi_ग_लिखो_hपूर्णांक = bio->bi_ग_लिखो_hपूर्णांक;

	जबतक (i < vcnt && size) अणु
		काष्ठा page *page;
		पूर्णांक len = min_t(पूर्णांक, PAGE_SIZE, size);

		page = alloc_page(GFP_NOIO);
		अगर (unlikely(!page))
			जाओ मुक्त_pages;

		bio_add_page(behind_bio, page, len, 0);

		size -= len;
		i++;
	पूर्ण

	bio_copy_data(behind_bio, bio);
skip_copy:
	r1_bio->behind_master_bio = behind_bio;
	set_bit(R1BIO_BehindIO, &r1_bio->state);

	वापस;

मुक्त_pages:
	pr_debug("%dB behind alloc failed, doing sync I/O\n",
		 bio->bi_iter.bi_size);
	bio_मुक्त_pages(behind_bio);
	bio_put(behind_bio);
पूर्ण

काष्ठा raid1_plug_cb अणु
	काष्ठा blk_plug_cb	cb;
	काष्ठा bio_list		pending;
	पूर्णांक			pending_cnt;
पूर्ण;

अटल व्योम raid1_unplug(काष्ठा blk_plug_cb *cb, bool from_schedule)
अणु
	काष्ठा raid1_plug_cb *plug = container_of(cb, काष्ठा raid1_plug_cb,
						  cb);
	काष्ठा mddev *mddev = plug->cb.data;
	काष्ठा r1conf *conf = mddev->निजी;
	काष्ठा bio *bio;

	अगर (from_schedule || current->bio_list) अणु
		spin_lock_irq(&conf->device_lock);
		bio_list_merge(&conf->pending_bio_list, &plug->pending);
		conf->pending_count += plug->pending_cnt;
		spin_unlock_irq(&conf->device_lock);
		wake_up(&conf->रुको_barrier);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		kमुक्त(plug);
		वापस;
	पूर्ण

	/* we aren't scheduling, so we can करो the ग_लिखो-out directly. */
	bio = bio_list_get(&plug->pending);
	flush_bio_list(conf, bio);
	kमुक्त(plug);
पूर्ण

अटल व्योम init_r1bio(काष्ठा r1bio *r1_bio, काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	r1_bio->master_bio = bio;
	r1_bio->sectors = bio_sectors(bio);
	r1_bio->state = 0;
	r1_bio->mddev = mddev;
	r1_bio->sector = bio->bi_iter.bi_sector;
पूर्ण

अटल अंतरभूत काष्ठा r1bio *
alloc_r1bio(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	काष्ठा r1conf *conf = mddev->निजी;
	काष्ठा r1bio *r1_bio;

	r1_bio = mempool_alloc(&conf->r1bio_pool, GFP_NOIO);
	/* Ensure no bio records IO_BLOCKED */
	स_रखो(r1_bio->bios, 0, conf->raid_disks * माप(r1_bio->bios[0]));
	init_r1bio(r1_bio, mddev, bio);
	वापस r1_bio;
पूर्ण

अटल व्योम raid1_पढ़ो_request(काष्ठा mddev *mddev, काष्ठा bio *bio,
			       पूर्णांक max_पढ़ो_sectors, काष्ठा r1bio *r1_bio)
अणु
	काष्ठा r1conf *conf = mddev->निजी;
	काष्ठा raid1_info *mirror;
	काष्ठा bio *पढ़ो_bio;
	काष्ठा biपंचांगap *biपंचांगap = mddev->biपंचांगap;
	स्थिर पूर्णांक op = bio_op(bio);
	स्थिर अचिन्हित दीर्घ करो_sync = (bio->bi_opf & REQ_SYNC);
	पूर्णांक max_sectors;
	पूर्णांक rdisk;
	bool prपूर्णांक_msg = !!r1_bio;
	अक्षर b[BDEVNAME_SIZE];

	/*
	 * If r1_bio is set, we are blocking the raid1d thपढ़ो
	 * so there is a tiny risk of deadlock.  So ask क्रम
	 * emergency memory अगर needed.
	 */
	gfp_t gfp = r1_bio ? (GFP_NOIO | __GFP_HIGH) : GFP_NOIO;

	अगर (prपूर्णांक_msg) अणु
		/* Need to get the block device name carefully */
		काष्ठा md_rdev *rdev;
		rcu_पढ़ो_lock();
		rdev = rcu_dereference(conf->mirrors[r1_bio->पढ़ो_disk].rdev);
		अगर (rdev)
			bdevname(rdev->bdev, b);
		अन्यथा
			म_नकल(b, "???");
		rcu_पढ़ो_unlock();
	पूर्ण

	/*
	 * Still need barrier क्रम READ in हाल that whole
	 * array is frozen.
	 */
	रुको_पढ़ो_barrier(conf, bio->bi_iter.bi_sector);

	अगर (!r1_bio)
		r1_bio = alloc_r1bio(mddev, bio);
	अन्यथा
		init_r1bio(r1_bio, mddev, bio);
	r1_bio->sectors = max_पढ़ो_sectors;

	/*
	 * make_request() can पात the operation when पढ़ो-ahead is being
	 * used and no empty request is available.
	 */
	rdisk = पढ़ो_balance(conf, r1_bio, &max_sectors);

	अगर (rdisk < 0) अणु
		/* couldn't find anywhere to पढ़ो from */
		अगर (prपूर्णांक_msg) अणु
			pr_crit_ratelimited("md/raid1:%s: %s: unrecoverable I/O read error for block %llu\n",
					    mdname(mddev),
					    b,
					    (अचिन्हित दीर्घ दीर्घ)r1_bio->sector);
		पूर्ण
		raid_end_bio_io(r1_bio);
		वापस;
	पूर्ण
	mirror = conf->mirrors + rdisk;

	अगर (prपूर्णांक_msg)
		pr_info_ratelimited("md/raid1:%s: redirecting sector %llu to other mirror: %s\n",
				    mdname(mddev),
				    (अचिन्हित दीर्घ दीर्घ)r1_bio->sector,
				    bdevname(mirror->rdev->bdev, b));

	अगर (test_bit(WriteMostly, &mirror->rdev->flags) &&
	    biपंचांगap) अणु
		/*
		 * Reading from a ग_लिखो-mostly device must take care not to
		 * over-take any ग_लिखोs that are 'behind'
		 */
		raid1_log(mddev, "wait behind writes");
		रुको_event(biपंचांगap->behind_रुको,
			   atomic_पढ़ो(&biपंचांगap->behind_ग_लिखोs) == 0);
	पूर्ण

	अगर (max_sectors < bio_sectors(bio)) अणु
		काष्ठा bio *split = bio_split(bio, max_sectors,
					      gfp, &conf->bio_split);
		bio_chain(split, bio);
		submit_bio_noacct(bio);
		bio = split;
		r1_bio->master_bio = bio;
		r1_bio->sectors = max_sectors;
	पूर्ण

	r1_bio->पढ़ो_disk = rdisk;

	पढ़ो_bio = bio_clone_fast(bio, gfp, &mddev->bio_set);

	r1_bio->bios[rdisk] = पढ़ो_bio;

	पढ़ो_bio->bi_iter.bi_sector = r1_bio->sector +
		mirror->rdev->data_offset;
	bio_set_dev(पढ़ो_bio, mirror->rdev->bdev);
	पढ़ो_bio->bi_end_io = raid1_end_पढ़ो_request;
	bio_set_op_attrs(पढ़ो_bio, op, करो_sync);
	अगर (test_bit(FailFast, &mirror->rdev->flags) &&
	    test_bit(R1BIO_FailFast, &r1_bio->state))
	        पढ़ो_bio->bi_opf |= MD_FAILFAST;
	पढ़ो_bio->bi_निजी = r1_bio;

	अगर (mddev->gendisk)
	        trace_block_bio_remap(पढ़ो_bio, disk_devt(mddev->gendisk),
				      r1_bio->sector);

	submit_bio_noacct(पढ़ो_bio);
पूर्ण

अटल व्योम raid1_ग_लिखो_request(काष्ठा mddev *mddev, काष्ठा bio *bio,
				पूर्णांक max_ग_लिखो_sectors)
अणु
	काष्ठा r1conf *conf = mddev->निजी;
	काष्ठा r1bio *r1_bio;
	पूर्णांक i, disks;
	काष्ठा biपंचांगap *biपंचांगap = mddev->biपंचांगap;
	अचिन्हित दीर्घ flags;
	काष्ठा md_rdev *blocked_rdev;
	काष्ठा blk_plug_cb *cb;
	काष्ठा raid1_plug_cb *plug = शून्य;
	पूर्णांक first_clone;
	पूर्णांक max_sectors;

	अगर (mddev_is_clustered(mddev) &&
	     md_cluster_ops->area_resyncing(mddev, WRITE,
		     bio->bi_iter.bi_sector, bio_end_sector(bio))) अणु

		DEFINE_WAIT(w);
		क्रम (;;) अणु
			prepare_to_रुको(&conf->रुको_barrier,
					&w, TASK_IDLE);
			अगर (!md_cluster_ops->area_resyncing(mddev, WRITE,
							bio->bi_iter.bi_sector,
							bio_end_sector(bio)))
				अवरोध;
			schedule();
		पूर्ण
		finish_रुको(&conf->रुको_barrier, &w);
	पूर्ण

	/*
	 * Register the new request and रुको अगर the reस्थिरruction
	 * thपढ़ो has put up a bar क्रम new requests.
	 * Continue immediately अगर no resync is active currently.
	 */
	रुको_barrier(conf, bio->bi_iter.bi_sector);

	r1_bio = alloc_r1bio(mddev, bio);
	r1_bio->sectors = max_ग_लिखो_sectors;

	अगर (conf->pending_count >= max_queued_requests) अणु
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		raid1_log(mddev, "wait queued");
		रुको_event(conf->रुको_barrier,
			   conf->pending_count < max_queued_requests);
	पूर्ण
	/* first select target devices under rcu_lock and
	 * inc refcount on their rdev.  Record them by setting
	 * bios[x] to bio
	 * If there are known/acknowledged bad blocks on any device on
	 * which we have seen a ग_लिखो error, we want to aव्योम writing those
	 * blocks.
	 * This potentially requires several ग_लिखोs to ग_लिखो around
	 * the bad blocks.  Each set of ग_लिखोs माला_लो it's own r1bio
	 * with a set of bios attached.
	 */

	disks = conf->raid_disks * 2;
 retry_ग_लिखो:
	blocked_rdev = शून्य;
	rcu_पढ़ो_lock();
	max_sectors = r1_bio->sectors;
	क्रम (i = 0;  i < disks; i++) अणु
		काष्ठा md_rdev *rdev = rcu_dereference(conf->mirrors[i].rdev);
		अगर (rdev && unlikely(test_bit(Blocked, &rdev->flags))) अणु
			atomic_inc(&rdev->nr_pending);
			blocked_rdev = rdev;
			अवरोध;
		पूर्ण
		r1_bio->bios[i] = शून्य;
		अगर (!rdev || test_bit(Faulty, &rdev->flags)) अणु
			अगर (i < conf->raid_disks)
				set_bit(R1BIO_Degraded, &r1_bio->state);
			जारी;
		पूर्ण

		atomic_inc(&rdev->nr_pending);
		अगर (test_bit(WriteErrorSeen, &rdev->flags)) अणु
			sector_t first_bad;
			पूर्णांक bad_sectors;
			पूर्णांक is_bad;

			is_bad = is_badblock(rdev, r1_bio->sector, max_sectors,
					     &first_bad, &bad_sectors);
			अगर (is_bad < 0) अणु
				/* mustn't ग_लिखो here until the bad block is
				 * acknowledged*/
				set_bit(BlockedBadBlocks, &rdev->flags);
				blocked_rdev = rdev;
				अवरोध;
			पूर्ण
			अगर (is_bad && first_bad <= r1_bio->sector) अणु
				/* Cannot ग_लिखो here at all */
				bad_sectors -= (r1_bio->sector - first_bad);
				अगर (bad_sectors < max_sectors)
					/* mustn't ग_लिखो more than bad_sectors
					 * to other devices yet
					 */
					max_sectors = bad_sectors;
				rdev_dec_pending(rdev, mddev);
				/* We करोn't set R1BIO_Degraded as that
				 * only applies अगर the disk is
				 * missing, so it might be re-added,
				 * and we want to know to recover this
				 * chunk.
				 * In this हाल the device is here,
				 * and the fact that this chunk is not
				 * in-sync is recorded in the bad
				 * block log
				 */
				जारी;
			पूर्ण
			अगर (is_bad) अणु
				पूर्णांक good_sectors = first_bad - r1_bio->sector;
				अगर (good_sectors < max_sectors)
					max_sectors = good_sectors;
			पूर्ण
		पूर्ण
		r1_bio->bios[i] = bio;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (unlikely(blocked_rdev)) अणु
		/* Wait क्रम this device to become unblocked */
		पूर्णांक j;

		क्रम (j = 0; j < i; j++)
			अगर (r1_bio->bios[j])
				rdev_dec_pending(conf->mirrors[j].rdev, mddev);
		r1_bio->state = 0;
		allow_barrier(conf, bio->bi_iter.bi_sector);
		raid1_log(mddev, "wait rdev %d blocked", blocked_rdev->raid_disk);
		md_रुको_क्रम_blocked_rdev(blocked_rdev, mddev);
		रुको_barrier(conf, bio->bi_iter.bi_sector);
		जाओ retry_ग_लिखो;
	पूर्ण

	अगर (max_sectors < bio_sectors(bio)) अणु
		काष्ठा bio *split = bio_split(bio, max_sectors,
					      GFP_NOIO, &conf->bio_split);
		bio_chain(split, bio);
		submit_bio_noacct(bio);
		bio = split;
		r1_bio->master_bio = bio;
		r1_bio->sectors = max_sectors;
	पूर्ण

	atomic_set(&r1_bio->reमुख्यing, 1);
	atomic_set(&r1_bio->behind_reमुख्यing, 0);

	first_clone = 1;

	क्रम (i = 0; i < disks; i++) अणु
		काष्ठा bio *mbio = शून्य;
		काष्ठा md_rdev *rdev = conf->mirrors[i].rdev;
		अगर (!r1_bio->bios[i])
			जारी;

		अगर (first_clone) अणु
			/* करो behind I/O ?
			 * Not अगर there are too many, or cannot
			 * allocate memory, or a पढ़ोer on WriteMostly
			 * is रुकोing क्रम behind ग_लिखोs to flush */
			अगर (biपंचांगap &&
			    (atomic_पढ़ो(&biपंचांगap->behind_ग_लिखोs)
			     < mddev->biपंचांगap_info.max_ग_लिखो_behind) &&
			    !रुकोqueue_active(&biपंचांगap->behind_रुको)) अणु
				alloc_behind_master_bio(r1_bio, bio);
			पूर्ण

			md_biपंचांगap_startग_लिखो(biपंचांगap, r1_bio->sector, r1_bio->sectors,
					     test_bit(R1BIO_BehindIO, &r1_bio->state));
			first_clone = 0;
		पूर्ण

		अगर (r1_bio->behind_master_bio)
			mbio = bio_clone_fast(r1_bio->behind_master_bio,
					      GFP_NOIO, &mddev->bio_set);
		अन्यथा
			mbio = bio_clone_fast(bio, GFP_NOIO, &mddev->bio_set);

		अगर (r1_bio->behind_master_bio) अणु
			अगर (test_bit(CollisionCheck, &rdev->flags))
				रुको_क्रम_serialization(rdev, r1_bio);
			अगर (test_bit(WriteMostly, &rdev->flags))
				atomic_inc(&r1_bio->behind_reमुख्यing);
		पूर्ण अन्यथा अगर (mddev->serialize_policy)
			रुको_क्रम_serialization(rdev, r1_bio);

		r1_bio->bios[i] = mbio;

		mbio->bi_iter.bi_sector	= (r1_bio->sector +
				   conf->mirrors[i].rdev->data_offset);
		bio_set_dev(mbio, conf->mirrors[i].rdev->bdev);
		mbio->bi_end_io	= raid1_end_ग_लिखो_request;
		mbio->bi_opf = bio_op(bio) | (bio->bi_opf & (REQ_SYNC | REQ_FUA));
		अगर (test_bit(FailFast, &conf->mirrors[i].rdev->flags) &&
		    !test_bit(WriteMostly, &conf->mirrors[i].rdev->flags) &&
		    conf->raid_disks - mddev->degraded > 1)
			mbio->bi_opf |= MD_FAILFAST;
		mbio->bi_निजी = r1_bio;

		atomic_inc(&r1_bio->reमुख्यing);

		अगर (mddev->gendisk)
			trace_block_bio_remap(mbio, disk_devt(mddev->gendisk),
					      r1_bio->sector);
		/* flush_pending_ग_लिखोs() needs access to the rdev so...*/
		mbio->bi_bdev = (व्योम *)conf->mirrors[i].rdev;

		cb = blk_check_plugged(raid1_unplug, mddev, माप(*plug));
		अगर (cb)
			plug = container_of(cb, काष्ठा raid1_plug_cb, cb);
		अन्यथा
			plug = शून्य;
		अगर (plug) अणु
			bio_list_add(&plug->pending, mbio);
			plug->pending_cnt++;
		पूर्ण अन्यथा अणु
			spin_lock_irqsave(&conf->device_lock, flags);
			bio_list_add(&conf->pending_bio_list, mbio);
			conf->pending_count++;
			spin_unlock_irqrestore(&conf->device_lock, flags);
			md_wakeup_thपढ़ो(mddev->thपढ़ो);
		पूर्ण
	पूर्ण

	r1_bio_ग_लिखो_करोne(r1_bio);

	/* In हाल raid1d snuck in to मुक्तze_array */
	wake_up(&conf->रुको_barrier);
पूर्ण

अटल bool raid1_make_request(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	sector_t sectors;

	अगर (unlikely(bio->bi_opf & REQ_PREFLUSH)
	    && md_flush_request(mddev, bio))
		वापस true;

	/*
	 * There is a limit to the maximum size, but
	 * the पढ़ो/ग_लिखो handler might find a lower limit
	 * due to bad blocks.  To aव्योम multiple splits,
	 * we pass the maximum number of sectors करोwn
	 * and let the lower level perक्रमm the split.
	 */
	sectors = align_to_barrier_unit_end(
		bio->bi_iter.bi_sector, bio_sectors(bio));

	अगर (bio_data_dir(bio) == READ)
		raid1_पढ़ो_request(mddev, bio, sectors, शून्य);
	अन्यथा अणु
		अगर (!md_ग_लिखो_start(mddev,bio))
			वापस false;
		raid1_ग_लिखो_request(mddev, bio, sectors);
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम raid1_status(काष्ठा seq_file *seq, काष्ठा mddev *mddev)
अणु
	काष्ठा r1conf *conf = mddev->निजी;
	पूर्णांक i;

	seq_म_लिखो(seq, " [%d/%d] [", conf->raid_disks,
		   conf->raid_disks - mddev->degraded);
	rcu_पढ़ो_lock();
	क्रम (i = 0; i < conf->raid_disks; i++) अणु
		काष्ठा md_rdev *rdev = rcu_dereference(conf->mirrors[i].rdev);
		seq_म_लिखो(seq, "%s",
			   rdev && test_bit(In_sync, &rdev->flags) ? "U" : "_");
	पूर्ण
	rcu_पढ़ो_unlock();
	seq_म_लिखो(seq, "]");
पूर्ण

अटल व्योम raid1_error(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	अक्षर b[BDEVNAME_SIZE];
	काष्ठा r1conf *conf = mddev->निजी;
	अचिन्हित दीर्घ flags;

	/*
	 * If it is not operational, then we have alपढ़ोy marked it as dead
	 * अन्यथा अगर it is the last working disks with "fail_last_dev == false",
	 * ignore the error, let the next level up know.
	 * अन्यथा mark the drive as failed
	 */
	spin_lock_irqsave(&conf->device_lock, flags);
	अगर (test_bit(In_sync, &rdev->flags) && !mddev->fail_last_dev
	    && (conf->raid_disks - mddev->degraded) == 1) अणु
		/*
		 * Don't fail the drive, act as though we were just a
		 * normal single drive.
		 * However करोn't try a recovery from this drive as
		 * it is very likely to fail.
		 */
		conf->recovery_disabled = mddev->recovery_disabled;
		spin_unlock_irqrestore(&conf->device_lock, flags);
		वापस;
	पूर्ण
	set_bit(Blocked, &rdev->flags);
	अगर (test_and_clear_bit(In_sync, &rdev->flags))
		mddev->degraded++;
	set_bit(Faulty, &rdev->flags);
	spin_unlock_irqrestore(&conf->device_lock, flags);
	/*
	 * अगर recovery is running, make sure it पातs.
	 */
	set_bit(MD_RECOVERY_INTR, &mddev->recovery);
	set_mask_bits(&mddev->sb_flags, 0,
		      BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_PENDING));
	pr_crit("md/raid1:%s: Disk failure on %s, disabling device.\n"
		"md/raid1:%s: Operation continuing on %d devices.\n",
		mdname(mddev), bdevname(rdev->bdev, b),
		mdname(mddev), conf->raid_disks - mddev->degraded);
पूर्ण

अटल व्योम prपूर्णांक_conf(काष्ठा r1conf *conf)
अणु
	पूर्णांक i;

	pr_debug("RAID1 conf printout:\n");
	अगर (!conf) अणु
		pr_debug("(!conf)\n");
		वापस;
	पूर्ण
	pr_debug(" --- wd:%d rd:%d\n", conf->raid_disks - conf->mddev->degraded,
		 conf->raid_disks);

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < conf->raid_disks; i++) अणु
		अक्षर b[BDEVNAME_SIZE];
		काष्ठा md_rdev *rdev = rcu_dereference(conf->mirrors[i].rdev);
		अगर (rdev)
			pr_debug(" disk %d, wo:%d, o:%d, dev:%s\n",
				 i, !test_bit(In_sync, &rdev->flags),
				 !test_bit(Faulty, &rdev->flags),
				 bdevname(rdev->bdev,b));
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम बंद_sync(काष्ठा r1conf *conf)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < BARRIER_BUCKETS_NR; idx++) अणु
		_रुको_barrier(conf, idx);
		_allow_barrier(conf, idx);
	पूर्ण

	mempool_निकास(&conf->r1buf_pool);
पूर्ण

अटल पूर्णांक raid1_spare_active(काष्ठा mddev *mddev)
अणु
	पूर्णांक i;
	काष्ठा r1conf *conf = mddev->निजी;
	पूर्णांक count = 0;
	अचिन्हित दीर्घ flags;

	/*
	 * Find all failed disks within the RAID1 configuration
	 * and mark them पढ़ोable.
	 * Called under mddev lock, so rcu protection not needed.
	 * device_lock used to aव्योम races with raid1_end_पढ़ो_request
	 * which expects 'In_sync' flags and ->degraded to be consistent.
	 */
	spin_lock_irqsave(&conf->device_lock, flags);
	क्रम (i = 0; i < conf->raid_disks; i++) अणु
		काष्ठा md_rdev *rdev = conf->mirrors[i].rdev;
		काष्ठा md_rdev *repl = conf->mirrors[conf->raid_disks + i].rdev;
		अगर (repl
		    && !test_bit(Candidate, &repl->flags)
		    && repl->recovery_offset == MaxSector
		    && !test_bit(Faulty, &repl->flags)
		    && !test_and_set_bit(In_sync, &repl->flags)) अणु
			/* replacement has just become active */
			अगर (!rdev ||
			    !test_and_clear_bit(In_sync, &rdev->flags))
				count++;
			अगर (rdev) अणु
				/* Replaced device not technically
				 * faulty, but we need to be sure
				 * it माला_लो हटाओd and never re-added
				 */
				set_bit(Faulty, &rdev->flags);
				sysfs_notअगरy_dirent_safe(
					rdev->sysfs_state);
			पूर्ण
		पूर्ण
		अगर (rdev
		    && rdev->recovery_offset == MaxSector
		    && !test_bit(Faulty, &rdev->flags)
		    && !test_and_set_bit(In_sync, &rdev->flags)) अणु
			count++;
			sysfs_notअगरy_dirent_safe(rdev->sysfs_state);
		पूर्ण
	पूर्ण
	mddev->degraded -= count;
	spin_unlock_irqrestore(&conf->device_lock, flags);

	prपूर्णांक_conf(conf);
	वापस count;
पूर्ण

अटल पूर्णांक raid1_add_disk(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा r1conf *conf = mddev->निजी;
	पूर्णांक err = -EEXIST;
	पूर्णांक mirror = 0;
	काष्ठा raid1_info *p;
	पूर्णांक first = 0;
	पूर्णांक last = conf->raid_disks - 1;

	अगर (mddev->recovery_disabled == conf->recovery_disabled)
		वापस -EBUSY;

	अगर (md_पूर्णांकegrity_add_rdev(rdev, mddev))
		वापस -ENXIO;

	अगर (rdev->raid_disk >= 0)
		first = last = rdev->raid_disk;

	/*
	 * find the disk ... but prefer rdev->saved_raid_disk
	 * अगर possible.
	 */
	अगर (rdev->saved_raid_disk >= 0 &&
	    rdev->saved_raid_disk >= first &&
	    rdev->saved_raid_disk < conf->raid_disks &&
	    conf->mirrors[rdev->saved_raid_disk].rdev == शून्य)
		first = last = rdev->saved_raid_disk;

	क्रम (mirror = first; mirror <= last; mirror++) अणु
		p = conf->mirrors + mirror;
		अगर (!p->rdev) अणु
			अगर (mddev->gendisk)
				disk_stack_limits(mddev->gendisk, rdev->bdev,
						  rdev->data_offset << 9);

			p->head_position = 0;
			rdev->raid_disk = mirror;
			err = 0;
			/* As all devices are equivalent, we करोn't need a full recovery
			 * अगर this was recently any drive of the array
			 */
			अगर (rdev->saved_raid_disk < 0)
				conf->fullsync = 1;
			rcu_assign_poपूर्णांकer(p->rdev, rdev);
			अवरोध;
		पूर्ण
		अगर (test_bit(WantReplacement, &p->rdev->flags) &&
		    p[conf->raid_disks].rdev == शून्य) अणु
			/* Add this device as a replacement */
			clear_bit(In_sync, &rdev->flags);
			set_bit(Replacement, &rdev->flags);
			rdev->raid_disk = mirror;
			err = 0;
			conf->fullsync = 1;
			rcu_assign_poपूर्णांकer(p[conf->raid_disks].rdev, rdev);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (mddev->queue && blk_queue_discard(bdev_get_queue(rdev->bdev)))
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, mddev->queue);
	prपूर्णांक_conf(conf);
	वापस err;
पूर्ण

अटल पूर्णांक raid1_हटाओ_disk(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा r1conf *conf = mddev->निजी;
	पूर्णांक err = 0;
	पूर्णांक number = rdev->raid_disk;
	काष्ठा raid1_info *p = conf->mirrors + number;

	अगर (rdev != p->rdev)
		p = conf->mirrors + conf->raid_disks + number;

	prपूर्णांक_conf(conf);
	अगर (rdev == p->rdev) अणु
		अगर (test_bit(In_sync, &rdev->flags) ||
		    atomic_पढ़ो(&rdev->nr_pending)) अणु
			err = -EBUSY;
			जाओ पात;
		पूर्ण
		/* Only हटाओ non-faulty devices अगर recovery
		 * is not possible.
		 */
		अगर (!test_bit(Faulty, &rdev->flags) &&
		    mddev->recovery_disabled != conf->recovery_disabled &&
		    mddev->degraded < conf->raid_disks) अणु
			err = -EBUSY;
			जाओ पात;
		पूर्ण
		p->rdev = शून्य;
		अगर (!test_bit(RemoveSynchronized, &rdev->flags)) अणु
			synchronize_rcu();
			अगर (atomic_पढ़ो(&rdev->nr_pending)) अणु
				/* lost the race, try later */
				err = -EBUSY;
				p->rdev = rdev;
				जाओ पात;
			पूर्ण
		पूर्ण
		अगर (conf->mirrors[conf->raid_disks + number].rdev) अणु
			/* We just हटाओd a device that is being replaced.
			 * Move करोwn the replacement.  We drain all IO beक्रमe
			 * करोing this to aव्योम confusion.
			 */
			काष्ठा md_rdev *repl =
				conf->mirrors[conf->raid_disks + number].rdev;
			मुक्तze_array(conf, 0);
			अगर (atomic_पढ़ो(&repl->nr_pending)) अणु
				/* It means that some queued IO of retry_list
				 * hold repl. Thus, we cannot set replacement
				 * as शून्य, aव्योमing rdev शून्य poपूर्णांकer
				 * dereference in sync_request_ग_लिखो and
				 * handle_ग_लिखो_finished.
				 */
				err = -EBUSY;
				unमुक्तze_array(conf);
				जाओ पात;
			पूर्ण
			clear_bit(Replacement, &repl->flags);
			p->rdev = repl;
			conf->mirrors[conf->raid_disks + number].rdev = शून्य;
			unमुक्तze_array(conf);
		पूर्ण

		clear_bit(WantReplacement, &rdev->flags);
		err = md_पूर्णांकegrity_रेजिस्टर(mddev);
	पूर्ण
पात:

	prपूर्णांक_conf(conf);
	वापस err;
पूर्ण

अटल व्योम end_sync_पढ़ो(काष्ठा bio *bio)
अणु
	काष्ठा r1bio *r1_bio = get_resync_r1bio(bio);

	update_head_pos(r1_bio->पढ़ो_disk, r1_bio);

	/*
	 * we have पढ़ो a block, now it needs to be re-written,
	 * or re-पढ़ो अगर the पढ़ो failed.
	 * We करोn't करो much here, just schedule handling by raid1d
	 */
	अगर (!bio->bi_status)
		set_bit(R1BIO_Uptodate, &r1_bio->state);

	अगर (atomic_dec_and_test(&r1_bio->reमुख्यing))
		reschedule_retry(r1_bio);
पूर्ण

अटल व्योम पात_sync_ग_लिखो(काष्ठा mddev *mddev, काष्ठा r1bio *r1_bio)
अणु
	sector_t sync_blocks = 0;
	sector_t s = r1_bio->sector;
	दीर्घ sectors_to_go = r1_bio->sectors;

	/* make sure these bits करोn't get cleared. */
	करो अणु
		md_biपंचांगap_end_sync(mddev->biपंचांगap, s, &sync_blocks, 1);
		s += sync_blocks;
		sectors_to_go -= sync_blocks;
	पूर्ण जबतक (sectors_to_go > 0);
पूर्ण

अटल व्योम put_sync_ग_लिखो_buf(काष्ठा r1bio *r1_bio, पूर्णांक uptodate)
अणु
	अगर (atomic_dec_and_test(&r1_bio->reमुख्यing)) अणु
		काष्ठा mddev *mddev = r1_bio->mddev;
		पूर्णांक s = r1_bio->sectors;

		अगर (test_bit(R1BIO_MadeGood, &r1_bio->state) ||
		    test_bit(R1BIO_WriteError, &r1_bio->state))
			reschedule_retry(r1_bio);
		अन्यथा अणु
			put_buf(r1_bio);
			md_करोne_sync(mddev, s, uptodate);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम end_sync_ग_लिखो(काष्ठा bio *bio)
अणु
	पूर्णांक uptodate = !bio->bi_status;
	काष्ठा r1bio *r1_bio = get_resync_r1bio(bio);
	काष्ठा mddev *mddev = r1_bio->mddev;
	काष्ठा r1conf *conf = mddev->निजी;
	sector_t first_bad;
	पूर्णांक bad_sectors;
	काष्ठा md_rdev *rdev = conf->mirrors[find_bio_disk(r1_bio, bio)].rdev;

	अगर (!uptodate) अणु
		पात_sync_ग_लिखो(mddev, r1_bio);
		set_bit(WriteErrorSeen, &rdev->flags);
		अगर (!test_and_set_bit(WantReplacement, &rdev->flags))
			set_bit(MD_RECOVERY_NEEDED, &
				mddev->recovery);
		set_bit(R1BIO_WriteError, &r1_bio->state);
	पूर्ण अन्यथा अगर (is_badblock(rdev, r1_bio->sector, r1_bio->sectors,
			       &first_bad, &bad_sectors) &&
		   !is_badblock(conf->mirrors[r1_bio->पढ़ो_disk].rdev,
				r1_bio->sector,
				r1_bio->sectors,
				&first_bad, &bad_sectors)
		)
		set_bit(R1BIO_MadeGood, &r1_bio->state);

	put_sync_ग_लिखो_buf(r1_bio, uptodate);
पूर्ण

अटल पूर्णांक r1_sync_page_io(काष्ठा md_rdev *rdev, sector_t sector,
			    पूर्णांक sectors, काष्ठा page *page, पूर्णांक rw)
अणु
	अगर (sync_page_io(rdev, sector, sectors << 9, page, rw, 0, false))
		/* success */
		वापस 1;
	अगर (rw == WRITE) अणु
		set_bit(WriteErrorSeen, &rdev->flags);
		अगर (!test_and_set_bit(WantReplacement,
				      &rdev->flags))
			set_bit(MD_RECOVERY_NEEDED, &
				rdev->mddev->recovery);
	पूर्ण
	/* need to record an error - either क्रम the block or the device */
	अगर (!rdev_set_badblocks(rdev, sector, sectors, 0))
		md_error(rdev->mddev, rdev);
	वापस 0;
पूर्ण

अटल पूर्णांक fix_sync_पढ़ो_error(काष्ठा r1bio *r1_bio)
अणु
	/* Try some synchronous पढ़ोs of other devices to get
	 * good data, much like with normal पढ़ो errors.  Only
	 * पढ़ो पूर्णांकo the pages we alपढ़ोy have so we करोn't
	 * need to re-issue the पढ़ो request.
	 * We करोn't need to मुक्तze the array, because being in an
	 * active sync request, there is no normal IO, and
	 * no overlapping syncs.
	 * We करोn't need to check is_badblock() again as we
	 * made sure that anything with a bad block in range
	 * will have bi_end_io clear.
	 */
	काष्ठा mddev *mddev = r1_bio->mddev;
	काष्ठा r1conf *conf = mddev->निजी;
	काष्ठा bio *bio = r1_bio->bios[r1_bio->पढ़ो_disk];
	काष्ठा page **pages = get_resync_pages(bio)->pages;
	sector_t sect = r1_bio->sector;
	पूर्णांक sectors = r1_bio->sectors;
	पूर्णांक idx = 0;
	काष्ठा md_rdev *rdev;

	rdev = conf->mirrors[r1_bio->पढ़ो_disk].rdev;
	अगर (test_bit(FailFast, &rdev->flags)) अणु
		/* Don't try recovering from here - just fail it
		 * ... unless it is the last working device of course */
		md_error(mddev, rdev);
		अगर (test_bit(Faulty, &rdev->flags))
			/* Don't try to पढ़ो from here, but make sure
			 * put_buf करोes it's thing
			 */
			bio->bi_end_io = end_sync_ग_लिखो;
	पूर्ण

	जबतक(sectors) अणु
		पूर्णांक s = sectors;
		पूर्णांक d = r1_bio->पढ़ो_disk;
		पूर्णांक success = 0;
		पूर्णांक start;

		अगर (s > (PAGE_SIZE>>9))
			s = PAGE_SIZE >> 9;
		करो अणु
			अगर (r1_bio->bios[d]->bi_end_io == end_sync_पढ़ो) अणु
				/* No rcu protection needed here devices
				 * can only be हटाओd when no resync is
				 * active, and resync is currently active
				 */
				rdev = conf->mirrors[d].rdev;
				अगर (sync_page_io(rdev, sect, s<<9,
						 pages[idx],
						 REQ_OP_READ, 0, false)) अणु
					success = 1;
					अवरोध;
				पूर्ण
			पूर्ण
			d++;
			अगर (d == conf->raid_disks * 2)
				d = 0;
		पूर्ण जबतक (!success && d != r1_bio->पढ़ो_disk);

		अगर (!success) अणु
			अक्षर b[BDEVNAME_SIZE];
			पूर्णांक पात = 0;
			/* Cannot पढ़ो from anywhere, this block is lost.
			 * Record a bad block on each device.  If that करोesn't
			 * work just disable and पूर्णांकerrupt the recovery.
			 * Don't fail devices as that won't really help.
			 */
			pr_crit_ratelimited("md/raid1:%s: %s: unrecoverable I/O read error for block %llu\n",
					    mdname(mddev), bio_devname(bio, b),
					    (अचिन्हित दीर्घ दीर्घ)r1_bio->sector);
			क्रम (d = 0; d < conf->raid_disks * 2; d++) अणु
				rdev = conf->mirrors[d].rdev;
				अगर (!rdev || test_bit(Faulty, &rdev->flags))
					जारी;
				अगर (!rdev_set_badblocks(rdev, sect, s, 0))
					पात = 1;
			पूर्ण
			अगर (पात) अणु
				conf->recovery_disabled =
					mddev->recovery_disabled;
				set_bit(MD_RECOVERY_INTR, &mddev->recovery);
				md_करोne_sync(mddev, r1_bio->sectors, 0);
				put_buf(r1_bio);
				वापस 0;
			पूर्ण
			/* Try next page */
			sectors -= s;
			sect += s;
			idx++;
			जारी;
		पूर्ण

		start = d;
		/* ग_लिखो it back and re-पढ़ो */
		जबतक (d != r1_bio->पढ़ो_disk) अणु
			अगर (d == 0)
				d = conf->raid_disks * 2;
			d--;
			अगर (r1_bio->bios[d]->bi_end_io != end_sync_पढ़ो)
				जारी;
			rdev = conf->mirrors[d].rdev;
			अगर (r1_sync_page_io(rdev, sect, s,
					    pages[idx],
					    WRITE) == 0) अणु
				r1_bio->bios[d]->bi_end_io = शून्य;
				rdev_dec_pending(rdev, mddev);
			पूर्ण
		पूर्ण
		d = start;
		जबतक (d != r1_bio->पढ़ो_disk) अणु
			अगर (d == 0)
				d = conf->raid_disks * 2;
			d--;
			अगर (r1_bio->bios[d]->bi_end_io != end_sync_पढ़ो)
				जारी;
			rdev = conf->mirrors[d].rdev;
			अगर (r1_sync_page_io(rdev, sect, s,
					    pages[idx],
					    READ) != 0)
				atomic_add(s, &rdev->corrected_errors);
		पूर्ण
		sectors -= s;
		sect += s;
		idx ++;
	पूर्ण
	set_bit(R1BIO_Uptodate, &r1_bio->state);
	bio->bi_status = 0;
	वापस 1;
पूर्ण

अटल व्योम process_checks(काष्ठा r1bio *r1_bio)
अणु
	/* We have पढ़ो all पढ़ोable devices.  If we haven't
	 * got the block, then there is no hope left.
	 * If we have, then we want to करो a comparison
	 * and skip the ग_लिखो अगर everything is the same.
	 * If any blocks failed to पढ़ो, then we need to
	 * attempt an over-ग_लिखो
	 */
	काष्ठा mddev *mddev = r1_bio->mddev;
	काष्ठा r1conf *conf = mddev->निजी;
	पूर्णांक primary;
	पूर्णांक i;
	पूर्णांक vcnt;

	/* Fix variable parts of all bios */
	vcnt = (r1_bio->sectors + PAGE_SIZE / 512 - 1) >> (PAGE_SHIFT - 9);
	क्रम (i = 0; i < conf->raid_disks * 2; i++) अणु
		blk_status_t status;
		काष्ठा bio *b = r1_bio->bios[i];
		काष्ठा resync_pages *rp = get_resync_pages(b);
		अगर (b->bi_end_io != end_sync_पढ़ो)
			जारी;
		/* fixup the bio क्रम reuse, but preserve त्रुटि_सं */
		status = b->bi_status;
		bio_reset(b);
		b->bi_status = status;
		b->bi_iter.bi_sector = r1_bio->sector +
			conf->mirrors[i].rdev->data_offset;
		bio_set_dev(b, conf->mirrors[i].rdev->bdev);
		b->bi_end_io = end_sync_पढ़ो;
		rp->raid_bio = r1_bio;
		b->bi_निजी = rp;

		/* initialize bvec table again */
		md_bio_reset_resync_pages(b, rp, r1_bio->sectors << 9);
	पूर्ण
	क्रम (primary = 0; primary < conf->raid_disks * 2; primary++)
		अगर (r1_bio->bios[primary]->bi_end_io == end_sync_पढ़ो &&
		    !r1_bio->bios[primary]->bi_status) अणु
			r1_bio->bios[primary]->bi_end_io = शून्य;
			rdev_dec_pending(conf->mirrors[primary].rdev, mddev);
			अवरोध;
		पूर्ण
	r1_bio->पढ़ो_disk = primary;
	क्रम (i = 0; i < conf->raid_disks * 2; i++) अणु
		पूर्णांक j = 0;
		काष्ठा bio *pbio = r1_bio->bios[primary];
		काष्ठा bio *sbio = r1_bio->bios[i];
		blk_status_t status = sbio->bi_status;
		काष्ठा page **ppages = get_resync_pages(pbio)->pages;
		काष्ठा page **spages = get_resync_pages(sbio)->pages;
		काष्ठा bio_vec *bi;
		पूर्णांक page_len[RESYNC_PAGES] = अणु 0 पूर्ण;
		काष्ठा bvec_iter_all iter_all;

		अगर (sbio->bi_end_io != end_sync_पढ़ो)
			जारी;
		/* Now we can 'fixup' the error value */
		sbio->bi_status = 0;

		bio_क्रम_each_segment_all(bi, sbio, iter_all)
			page_len[j++] = bi->bv_len;

		अगर (!status) अणु
			क्रम (j = vcnt; j-- ; ) अणु
				अगर (स_भेद(page_address(ppages[j]),
					   page_address(spages[j]),
					   page_len[j]))
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			j = 0;
		अगर (j >= 0)
			atomic64_add(r1_bio->sectors, &mddev->resync_mismatches);
		अगर (j < 0 || (test_bit(MD_RECOVERY_CHECK, &mddev->recovery)
			      && !status)) अणु
			/* No need to ग_लिखो to this device. */
			sbio->bi_end_io = शून्य;
			rdev_dec_pending(conf->mirrors[i].rdev, mddev);
			जारी;
		पूर्ण

		bio_copy_data(sbio, pbio);
	पूर्ण
पूर्ण

अटल व्योम sync_request_ग_लिखो(काष्ठा mddev *mddev, काष्ठा r1bio *r1_bio)
अणु
	काष्ठा r1conf *conf = mddev->निजी;
	पूर्णांक i;
	पूर्णांक disks = conf->raid_disks * 2;
	काष्ठा bio *wbio;

	अगर (!test_bit(R1BIO_Uptodate, &r1_bio->state))
		/* ouch - failed to पढ़ो all of that. */
		अगर (!fix_sync_पढ़ो_error(r1_bio))
			वापस;

	अगर (test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery))
		process_checks(r1_bio);

	/*
	 * schedule ग_लिखोs
	 */
	atomic_set(&r1_bio->reमुख्यing, 1);
	क्रम (i = 0; i < disks ; i++) अणु
		wbio = r1_bio->bios[i];
		अगर (wbio->bi_end_io == शून्य ||
		    (wbio->bi_end_io == end_sync_पढ़ो &&
		     (i == r1_bio->पढ़ो_disk ||
		      !test_bit(MD_RECOVERY_SYNC, &mddev->recovery))))
			जारी;
		अगर (test_bit(Faulty, &conf->mirrors[i].rdev->flags)) अणु
			पात_sync_ग_लिखो(mddev, r1_bio);
			जारी;
		पूर्ण

		bio_set_op_attrs(wbio, REQ_OP_WRITE, 0);
		अगर (test_bit(FailFast, &conf->mirrors[i].rdev->flags))
			wbio->bi_opf |= MD_FAILFAST;

		wbio->bi_end_io = end_sync_ग_लिखो;
		atomic_inc(&r1_bio->reमुख्यing);
		md_sync_acct(conf->mirrors[i].rdev->bdev, bio_sectors(wbio));

		submit_bio_noacct(wbio);
	पूर्ण

	put_sync_ग_लिखो_buf(r1_bio, 1);
पूर्ण

/*
 * This is a kernel thपढ़ो which:
 *
 *	1.	Retries failed पढ़ो operations on working mirrors.
 *	2.	Updates the raid superblock when problems encounter.
 *	3.	Perक्रमms ग_लिखोs following पढ़ोs क्रम array synchronising.
 */

अटल व्योम fix_पढ़ो_error(काष्ठा r1conf *conf, पूर्णांक पढ़ो_disk,
			   sector_t sect, पूर्णांक sectors)
अणु
	काष्ठा mddev *mddev = conf->mddev;
	जबतक(sectors) अणु
		पूर्णांक s = sectors;
		पूर्णांक d = पढ़ो_disk;
		पूर्णांक success = 0;
		पूर्णांक start;
		काष्ठा md_rdev *rdev;

		अगर (s > (PAGE_SIZE>>9))
			s = PAGE_SIZE >> 9;

		करो अणु
			sector_t first_bad;
			पूर्णांक bad_sectors;

			rcu_पढ़ो_lock();
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			अगर (rdev &&
			    (test_bit(In_sync, &rdev->flags) ||
			     (!test_bit(Faulty, &rdev->flags) &&
			      rdev->recovery_offset >= sect + s)) &&
			    is_badblock(rdev, sect, s,
					&first_bad, &bad_sectors) == 0) अणु
				atomic_inc(&rdev->nr_pending);
				rcu_पढ़ो_unlock();
				अगर (sync_page_io(rdev, sect, s<<9,
					 conf->पंचांगppage, REQ_OP_READ, 0, false))
					success = 1;
				rdev_dec_pending(rdev, mddev);
				अगर (success)
					अवरोध;
			पूर्ण अन्यथा
				rcu_पढ़ो_unlock();
			d++;
			अगर (d == conf->raid_disks * 2)
				d = 0;
		पूर्ण जबतक (!success && d != पढ़ो_disk);

		अगर (!success) अणु
			/* Cannot पढ़ो from anywhere - mark it bad */
			काष्ठा md_rdev *rdev = conf->mirrors[पढ़ो_disk].rdev;
			अगर (!rdev_set_badblocks(rdev, sect, s, 0))
				md_error(mddev, rdev);
			अवरोध;
		पूर्ण
		/* ग_लिखो it back and re-पढ़ो */
		start = d;
		जबतक (d != पढ़ो_disk) अणु
			अगर (d==0)
				d = conf->raid_disks * 2;
			d--;
			rcu_पढ़ो_lock();
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			अगर (rdev &&
			    !test_bit(Faulty, &rdev->flags)) अणु
				atomic_inc(&rdev->nr_pending);
				rcu_पढ़ो_unlock();
				r1_sync_page_io(rdev, sect, s,
						conf->पंचांगppage, WRITE);
				rdev_dec_pending(rdev, mddev);
			पूर्ण अन्यथा
				rcu_पढ़ो_unlock();
		पूर्ण
		d = start;
		जबतक (d != पढ़ो_disk) अणु
			अक्षर b[BDEVNAME_SIZE];
			अगर (d==0)
				d = conf->raid_disks * 2;
			d--;
			rcu_पढ़ो_lock();
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			अगर (rdev &&
			    !test_bit(Faulty, &rdev->flags)) अणु
				atomic_inc(&rdev->nr_pending);
				rcu_पढ़ो_unlock();
				अगर (r1_sync_page_io(rdev, sect, s,
						    conf->पंचांगppage, READ)) अणु
					atomic_add(s, &rdev->corrected_errors);
					pr_info("md/raid1:%s: read error corrected (%d sectors at %llu on %s)\n",
						mdname(mddev), s,
						(अचिन्हित दीर्घ दीर्घ)(sect +
								     rdev->data_offset),
						bdevname(rdev->bdev, b));
				पूर्ण
				rdev_dec_pending(rdev, mddev);
			पूर्ण अन्यथा
				rcu_पढ़ो_unlock();
		पूर्ण
		sectors -= s;
		sect += s;
	पूर्ण
पूर्ण

अटल पूर्णांक narrow_ग_लिखो_error(काष्ठा r1bio *r1_bio, पूर्णांक i)
अणु
	काष्ठा mddev *mddev = r1_bio->mddev;
	काष्ठा r1conf *conf = mddev->निजी;
	काष्ठा md_rdev *rdev = conf->mirrors[i].rdev;

	/* bio has the data to be written to device 'i' where
	 * we just recently had a ग_लिखो error.
	 * We repeatedly clone the bio and trim करोwn to one block,
	 * then try the ग_लिखो.  Where the ग_लिखो fails we record
	 * a bad block.
	 * It is conceivable that the bio करोesn't exactly align with
	 * blocks.  We must handle this somehow.
	 *
	 * We currently own a reference on the rdev.
	 */

	पूर्णांक block_sectors;
	sector_t sector;
	पूर्णांक sectors;
	पूर्णांक sect_to_ग_लिखो = r1_bio->sectors;
	पूर्णांक ok = 1;

	अगर (rdev->badblocks.shअगरt < 0)
		वापस 0;

	block_sectors = roundup(1 << rdev->badblocks.shअगरt,
				bdev_logical_block_size(rdev->bdev) >> 9);
	sector = r1_bio->sector;
	sectors = ((sector + block_sectors)
		   & ~(sector_t)(block_sectors - 1))
		- sector;

	जबतक (sect_to_ग_लिखो) अणु
		काष्ठा bio *wbio;
		अगर (sectors > sect_to_ग_लिखो)
			sectors = sect_to_ग_लिखो;
		/* Write at 'sector' for 'sectors'*/

		अगर (test_bit(R1BIO_BehindIO, &r1_bio->state)) अणु
			wbio = bio_clone_fast(r1_bio->behind_master_bio,
					      GFP_NOIO,
					      &mddev->bio_set);
		पूर्ण अन्यथा अणु
			wbio = bio_clone_fast(r1_bio->master_bio, GFP_NOIO,
					      &mddev->bio_set);
		पूर्ण

		bio_set_op_attrs(wbio, REQ_OP_WRITE, 0);
		wbio->bi_iter.bi_sector = r1_bio->sector;
		wbio->bi_iter.bi_size = r1_bio->sectors << 9;

		bio_trim(wbio, sector - r1_bio->sector, sectors);
		wbio->bi_iter.bi_sector += rdev->data_offset;
		bio_set_dev(wbio, rdev->bdev);

		अगर (submit_bio_रुको(wbio) < 0)
			/* failure! */
			ok = rdev_set_badblocks(rdev, sector,
						sectors, 0)
				&& ok;

		bio_put(wbio);
		sect_to_ग_लिखो -= sectors;
		sector += sectors;
		sectors = block_sectors;
	पूर्ण
	वापस ok;
पूर्ण

अटल व्योम handle_sync_ग_लिखो_finished(काष्ठा r1conf *conf, काष्ठा r1bio *r1_bio)
अणु
	पूर्णांक m;
	पूर्णांक s = r1_bio->sectors;
	क्रम (m = 0; m < conf->raid_disks * 2 ; m++) अणु
		काष्ठा md_rdev *rdev = conf->mirrors[m].rdev;
		काष्ठा bio *bio = r1_bio->bios[m];
		अगर (bio->bi_end_io == शून्य)
			जारी;
		अगर (!bio->bi_status &&
		    test_bit(R1BIO_MadeGood, &r1_bio->state)) अणु
			rdev_clear_badblocks(rdev, r1_bio->sector, s, 0);
		पूर्ण
		अगर (bio->bi_status &&
		    test_bit(R1BIO_WriteError, &r1_bio->state)) अणु
			अगर (!rdev_set_badblocks(rdev, r1_bio->sector, s, 0))
				md_error(conf->mddev, rdev);
		पूर्ण
	पूर्ण
	put_buf(r1_bio);
	md_करोne_sync(conf->mddev, s, 1);
पूर्ण

अटल व्योम handle_ग_लिखो_finished(काष्ठा r1conf *conf, काष्ठा r1bio *r1_bio)
अणु
	पूर्णांक m, idx;
	bool fail = false;

	क्रम (m = 0; m < conf->raid_disks * 2 ; m++)
		अगर (r1_bio->bios[m] == IO_MADE_GOOD) अणु
			काष्ठा md_rdev *rdev = conf->mirrors[m].rdev;
			rdev_clear_badblocks(rdev,
					     r1_bio->sector,
					     r1_bio->sectors, 0);
			rdev_dec_pending(rdev, conf->mddev);
		पूर्ण अन्यथा अगर (r1_bio->bios[m] != शून्य) अणु
			/* This drive got a ग_लिखो error.  We need to
			 * narrow करोwn and record precise ग_लिखो
			 * errors.
			 */
			fail = true;
			अगर (!narrow_ग_लिखो_error(r1_bio, m)) अणु
				md_error(conf->mddev,
					 conf->mirrors[m].rdev);
				/* an I/O failed, we can't clear the biपंचांगap */
				set_bit(R1BIO_Degraded, &r1_bio->state);
			पूर्ण
			rdev_dec_pending(conf->mirrors[m].rdev,
					 conf->mddev);
		पूर्ण
	अगर (fail) अणु
		spin_lock_irq(&conf->device_lock);
		list_add(&r1_bio->retry_list, &conf->bio_end_io_list);
		idx = sector_to_idx(r1_bio->sector);
		atomic_inc(&conf->nr_queued[idx]);
		spin_unlock_irq(&conf->device_lock);
		/*
		 * In हाल मुक्तze_array() is रुकोing क्रम condition
		 * get_unqueued_pending() == extra to be true.
		 */
		wake_up(&conf->रुको_barrier);
		md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
	पूर्ण अन्यथा अणु
		अगर (test_bit(R1BIO_WriteError, &r1_bio->state))
			बंद_ग_लिखो(r1_bio);
		raid_end_bio_io(r1_bio);
	पूर्ण
पूर्ण

अटल व्योम handle_पढ़ो_error(काष्ठा r1conf *conf, काष्ठा r1bio *r1_bio)
अणु
	काष्ठा mddev *mddev = conf->mddev;
	काष्ठा bio *bio;
	काष्ठा md_rdev *rdev;

	clear_bit(R1BIO_ReadError, &r1_bio->state);
	/* we got a पढ़ो error. Maybe the drive is bad.  Maybe just
	 * the block and we can fix it.
	 * We मुक्तze all other IO, and try पढ़ोing the block from
	 * other devices.  When we find one, we re-ग_लिखो
	 * and check it that fixes the पढ़ो error.
	 * This is all करोne synchronously जबतक the array is
	 * frozen
	 */

	bio = r1_bio->bios[r1_bio->पढ़ो_disk];
	bio_put(bio);
	r1_bio->bios[r1_bio->पढ़ो_disk] = शून्य;

	rdev = conf->mirrors[r1_bio->पढ़ो_disk].rdev;
	अगर (mddev->ro == 0
	    && !test_bit(FailFast, &rdev->flags)) अणु
		मुक्तze_array(conf, 1);
		fix_पढ़ो_error(conf, r1_bio->पढ़ो_disk,
			       r1_bio->sector, r1_bio->sectors);
		unमुक्तze_array(conf);
	पूर्ण अन्यथा अगर (mddev->ro == 0 && test_bit(FailFast, &rdev->flags)) अणु
		md_error(mddev, rdev);
	पूर्ण अन्यथा अणु
		r1_bio->bios[r1_bio->पढ़ो_disk] = IO_BLOCKED;
	पूर्ण

	rdev_dec_pending(rdev, conf->mddev);
	allow_barrier(conf, r1_bio->sector);
	bio = r1_bio->master_bio;

	/* Reuse the old r1_bio so that the IO_BLOCKED settings are preserved */
	r1_bio->state = 0;
	raid1_पढ़ो_request(mddev, bio, r1_bio->sectors, r1_bio);
पूर्ण

अटल व्योम raid1d(काष्ठा md_thपढ़ो *thपढ़ो)
अणु
	काष्ठा mddev *mddev = thपढ़ो->mddev;
	काष्ठा r1bio *r1_bio;
	अचिन्हित दीर्घ flags;
	काष्ठा r1conf *conf = mddev->निजी;
	काष्ठा list_head *head = &conf->retry_list;
	काष्ठा blk_plug plug;
	पूर्णांक idx;

	md_check_recovery(mddev);

	अगर (!list_empty_careful(&conf->bio_end_io_list) &&
	    !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags)) अणु
		LIST_HEAD(पंचांगp);
		spin_lock_irqsave(&conf->device_lock, flags);
		अगर (!test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags))
			list_splice_init(&conf->bio_end_io_list, &पंचांगp);
		spin_unlock_irqrestore(&conf->device_lock, flags);
		जबतक (!list_empty(&पंचांगp)) अणु
			r1_bio = list_first_entry(&पंचांगp, काष्ठा r1bio,
						  retry_list);
			list_del(&r1_bio->retry_list);
			idx = sector_to_idx(r1_bio->sector);
			atomic_dec(&conf->nr_queued[idx]);
			अगर (mddev->degraded)
				set_bit(R1BIO_Degraded, &r1_bio->state);
			अगर (test_bit(R1BIO_WriteError, &r1_bio->state))
				बंद_ग_लिखो(r1_bio);
			raid_end_bio_io(r1_bio);
		पूर्ण
	पूर्ण

	blk_start_plug(&plug);
	क्रम (;;) अणु

		flush_pending_ग_लिखोs(conf);

		spin_lock_irqsave(&conf->device_lock, flags);
		अगर (list_empty(head)) अणु
			spin_unlock_irqrestore(&conf->device_lock, flags);
			अवरोध;
		पूर्ण
		r1_bio = list_entry(head->prev, काष्ठा r1bio, retry_list);
		list_del(head->prev);
		idx = sector_to_idx(r1_bio->sector);
		atomic_dec(&conf->nr_queued[idx]);
		spin_unlock_irqrestore(&conf->device_lock, flags);

		mddev = r1_bio->mddev;
		conf = mddev->निजी;
		अगर (test_bit(R1BIO_IsSync, &r1_bio->state)) अणु
			अगर (test_bit(R1BIO_MadeGood, &r1_bio->state) ||
			    test_bit(R1BIO_WriteError, &r1_bio->state))
				handle_sync_ग_लिखो_finished(conf, r1_bio);
			अन्यथा
				sync_request_ग_लिखो(mddev, r1_bio);
		पूर्ण अन्यथा अगर (test_bit(R1BIO_MadeGood, &r1_bio->state) ||
			   test_bit(R1BIO_WriteError, &r1_bio->state))
			handle_ग_लिखो_finished(conf, r1_bio);
		अन्यथा अगर (test_bit(R1BIO_ReadError, &r1_bio->state))
			handle_पढ़ो_error(conf, r1_bio);
		अन्यथा
			WARN_ON_ONCE(1);

		cond_resched();
		अगर (mddev->sb_flags & ~(1<<MD_SB_CHANGE_PENDING))
			md_check_recovery(mddev);
	पूर्ण
	blk_finish_plug(&plug);
पूर्ण

अटल पूर्णांक init_resync(काष्ठा r1conf *conf)
अणु
	पूर्णांक buffs;

	buffs = RESYNC_WINDOW / RESYNC_BLOCK_SIZE;
	BUG_ON(mempool_initialized(&conf->r1buf_pool));

	वापस mempool_init(&conf->r1buf_pool, buffs, r1buf_pool_alloc,
			    r1buf_pool_मुक्त, conf->poolinfo);
पूर्ण

अटल काष्ठा r1bio *raid1_alloc_init_r1buf(काष्ठा r1conf *conf)
अणु
	काष्ठा r1bio *r1bio = mempool_alloc(&conf->r1buf_pool, GFP_NOIO);
	काष्ठा resync_pages *rps;
	काष्ठा bio *bio;
	पूर्णांक i;

	क्रम (i = conf->poolinfo->raid_disks; i--; ) अणु
		bio = r1bio->bios[i];
		rps = bio->bi_निजी;
		bio_reset(bio);
		bio->bi_निजी = rps;
	पूर्ण
	r1bio->master_bio = शून्य;
	वापस r1bio;
पूर्ण

/*
 * perक्रमm a "sync" on one "block"
 *
 * We need to make sure that no normal I/O request - particularly ग_लिखो
 * requests - conflict with active sync requests.
 *
 * This is achieved by tracking pending requests and a 'barrier' concept
 * that can be installed to exclude normal IO requests.
 */

अटल sector_t raid1_sync_request(काष्ठा mddev *mddev, sector_t sector_nr,
				   पूर्णांक *skipped)
अणु
	काष्ठा r1conf *conf = mddev->निजी;
	काष्ठा r1bio *r1_bio;
	काष्ठा bio *bio;
	sector_t max_sector, nr_sectors;
	पूर्णांक disk = -1;
	पूर्णांक i;
	पूर्णांक wonly = -1;
	पूर्णांक ग_लिखो_tarमाला_लो = 0, पढ़ो_tarमाला_लो = 0;
	sector_t sync_blocks;
	पूर्णांक still_degraded = 0;
	पूर्णांक good_sectors = RESYNC_SECTORS;
	पूर्णांक min_bad = 0; /* number of sectors that are bad in all devices */
	पूर्णांक idx = sector_to_idx(sector_nr);
	पूर्णांक page_idx = 0;

	अगर (!mempool_initialized(&conf->r1buf_pool))
		अगर (init_resync(conf))
			वापस 0;

	max_sector = mddev->dev_sectors;
	अगर (sector_nr >= max_sector) अणु
		/* If we पातed, we need to पात the
		 * sync on the 'current' biपंचांगap chunk (there will
		 * only be one in raid1 resync.
		 * We can find the current addess in mddev->curr_resync
		 */
		अगर (mddev->curr_resync < max_sector) /* पातed */
			md_biपंचांगap_end_sync(mddev->biपंचांगap, mddev->curr_resync,
					   &sync_blocks, 1);
		अन्यथा /* completed sync */
			conf->fullsync = 0;

		md_biपंचांगap_बंद_sync(mddev->biपंचांगap);
		बंद_sync(conf);

		अगर (mddev_is_clustered(mddev)) अणु
			conf->cluster_sync_low = 0;
			conf->cluster_sync_high = 0;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (mddev->biपंचांगap == शून्य &&
	    mddev->recovery_cp == MaxSector &&
	    !test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery) &&
	    conf->fullsync == 0) अणु
		*skipped = 1;
		वापस max_sector - sector_nr;
	पूर्ण
	/* beक्रमe building a request, check अगर we can skip these blocks..
	 * This call the biपंचांगap_start_sync करोesn't actually record anything
	 */
	अगर (!md_biपंचांगap_start_sync(mddev->biपंचांगap, sector_nr, &sync_blocks, 1) &&
	    !conf->fullsync && !test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery)) अणु
		/* We can skip this block, and probably several more */
		*skipped = 1;
		वापस sync_blocks;
	पूर्ण

	/*
	 * If there is non-resync activity रुकोing क्रम a turn, then let it
	 * though beक्रमe starting on this new sync request.
	 */
	अगर (atomic_पढ़ो(&conf->nr_रुकोing[idx]))
		schedule_समयout_unपूर्णांकerruptible(1);

	/* we are incrementing sector_nr below. To be safe, we check against
	 * sector_nr + two बार RESYNC_SECTORS
	 */

	md_biपंचांगap_cond_end_sync(mddev->biपंचांगap, sector_nr,
		mddev_is_clustered(mddev) && (sector_nr + 2 * RESYNC_SECTORS > conf->cluster_sync_high));


	अगर (उठाओ_barrier(conf, sector_nr))
		वापस 0;

	r1_bio = raid1_alloc_init_r1buf(conf);

	rcu_पढ़ो_lock();
	/*
	 * If we get a correctably पढ़ो error during resync or recovery,
	 * we might want to पढ़ो from a dअगरferent device.  So we
	 * flag all drives that could conceivably be पढ़ो from क्रम READ,
	 * and any others (which will be non-In_sync devices) क्रम WRITE.
	 * If a पढ़ो fails, we try पढ़ोing from something अन्यथा क्रम which READ
	 * is OK.
	 */

	r1_bio->mddev = mddev;
	r1_bio->sector = sector_nr;
	r1_bio->state = 0;
	set_bit(R1BIO_IsSync, &r1_bio->state);
	/* make sure good_sectors won't go across barrier unit boundary */
	good_sectors = align_to_barrier_unit_end(sector_nr, good_sectors);

	क्रम (i = 0; i < conf->raid_disks * 2; i++) अणु
		काष्ठा md_rdev *rdev;
		bio = r1_bio->bios[i];

		rdev = rcu_dereference(conf->mirrors[i].rdev);
		अगर (rdev == शून्य ||
		    test_bit(Faulty, &rdev->flags)) अणु
			अगर (i < conf->raid_disks)
				still_degraded = 1;
		पूर्ण अन्यथा अगर (!test_bit(In_sync, &rdev->flags)) अणु
			bio_set_op_attrs(bio, REQ_OP_WRITE, 0);
			bio->bi_end_io = end_sync_ग_लिखो;
			ग_लिखो_tarमाला_लो ++;
		पूर्ण अन्यथा अणु
			/* may need to पढ़ो from here */
			sector_t first_bad = MaxSector;
			पूर्णांक bad_sectors;

			अगर (is_badblock(rdev, sector_nr, good_sectors,
					&first_bad, &bad_sectors)) अणु
				अगर (first_bad > sector_nr)
					good_sectors = first_bad - sector_nr;
				अन्यथा अणु
					bad_sectors -= (sector_nr - first_bad);
					अगर (min_bad == 0 ||
					    min_bad > bad_sectors)
						min_bad = bad_sectors;
				पूर्ण
			पूर्ण
			अगर (sector_nr < first_bad) अणु
				अगर (test_bit(WriteMostly, &rdev->flags)) अणु
					अगर (wonly < 0)
						wonly = i;
				पूर्ण अन्यथा अणु
					अगर (disk < 0)
						disk = i;
				पूर्ण
				bio_set_op_attrs(bio, REQ_OP_READ, 0);
				bio->bi_end_io = end_sync_पढ़ो;
				पढ़ो_tarमाला_लो++;
			पूर्ण अन्यथा अगर (!test_bit(WriteErrorSeen, &rdev->flags) &&
				test_bit(MD_RECOVERY_SYNC, &mddev->recovery) &&
				!test_bit(MD_RECOVERY_CHECK, &mddev->recovery)) अणु
				/*
				 * The device is suitable क्रम पढ़ोing (InSync),
				 * but has bad block(s) here. Let's try to correct them,
				 * अगर we are करोing resync or repair. Otherwise, leave
				 * this device alone क्रम this sync request.
				 */
				bio_set_op_attrs(bio, REQ_OP_WRITE, 0);
				bio->bi_end_io = end_sync_ग_लिखो;
				ग_लिखो_tarमाला_लो++;
			पूर्ण
		पूर्ण
		अगर (rdev && bio->bi_end_io) अणु
			atomic_inc(&rdev->nr_pending);
			bio->bi_iter.bi_sector = sector_nr + rdev->data_offset;
			bio_set_dev(bio, rdev->bdev);
			अगर (test_bit(FailFast, &rdev->flags))
				bio->bi_opf |= MD_FAILFAST;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (disk < 0)
		disk = wonly;
	r1_bio->पढ़ो_disk = disk;

	अगर (पढ़ो_tarमाला_लो == 0 && min_bad > 0) अणु
		/* These sectors are bad on all InSync devices, so we
		 * need to mark them bad on all ग_लिखो tarमाला_लो
		 */
		पूर्णांक ok = 1;
		क्रम (i = 0 ; i < conf->raid_disks * 2 ; i++)
			अगर (r1_bio->bios[i]->bi_end_io == end_sync_ग_लिखो) अणु
				काष्ठा md_rdev *rdev = conf->mirrors[i].rdev;
				ok = rdev_set_badblocks(rdev, sector_nr,
							min_bad, 0
					) && ok;
			पूर्ण
		set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
		*skipped = 1;
		put_buf(r1_bio);

		अगर (!ok) अणु
			/* Cannot record the badblocks, so need to
			 * पात the resync.
			 * If there are multiple पढ़ो tarमाला_लो, could just
			 * fail the really bad ones ???
			 */
			conf->recovery_disabled = mddev->recovery_disabled;
			set_bit(MD_RECOVERY_INTR, &mddev->recovery);
			वापस 0;
		पूर्ण अन्यथा
			वापस min_bad;

	पूर्ण
	अगर (min_bad > 0 && min_bad < good_sectors) अणु
		/* only resync enough to reach the next bad->good
		 * transition */
		good_sectors = min_bad;
	पूर्ण

	अगर (test_bit(MD_RECOVERY_SYNC, &mddev->recovery) && पढ़ो_tarमाला_लो > 0)
		/* extra पढ़ो tarमाला_लो are also ग_लिखो tarमाला_लो */
		ग_लिखो_tarमाला_लो += पढ़ो_tarमाला_लो-1;

	अगर (ग_लिखो_tarमाला_लो == 0 || पढ़ो_tarमाला_लो == 0) अणु
		/* There is nowhere to ग_लिखो, so all non-sync
		 * drives must be failed - so we are finished
		 */
		sector_t rv;
		अगर (min_bad > 0)
			max_sector = sector_nr + min_bad;
		rv = max_sector - sector_nr;
		*skipped = 1;
		put_buf(r1_bio);
		वापस rv;
	पूर्ण

	अगर (max_sector > mddev->resync_max)
		max_sector = mddev->resync_max; /* Don't करो IO beyond here */
	अगर (max_sector > sector_nr + good_sectors)
		max_sector = sector_nr + good_sectors;
	nr_sectors = 0;
	sync_blocks = 0;
	करो अणु
		काष्ठा page *page;
		पूर्णांक len = PAGE_SIZE;
		अगर (sector_nr + (len>>9) > max_sector)
			len = (max_sector - sector_nr) << 9;
		अगर (len == 0)
			अवरोध;
		अगर (sync_blocks == 0) अणु
			अगर (!md_biपंचांगap_start_sync(mddev->biपंचांगap, sector_nr,
						  &sync_blocks, still_degraded) &&
			    !conf->fullsync &&
			    !test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery))
				अवरोध;
			अगर ((len >> 9) > sync_blocks)
				len = sync_blocks<<9;
		पूर्ण

		क्रम (i = 0 ; i < conf->raid_disks * 2; i++) अणु
			काष्ठा resync_pages *rp;

			bio = r1_bio->bios[i];
			rp = get_resync_pages(bio);
			अगर (bio->bi_end_io) अणु
				page = resync_fetch_page(rp, page_idx);

				/*
				 * won't fail because the vec table is big
				 * enough to hold all these pages
				 */
				bio_add_page(bio, page, len, 0);
			पूर्ण
		पूर्ण
		nr_sectors += len>>9;
		sector_nr += len>>9;
		sync_blocks -= (len>>9);
	पूर्ण जबतक (++page_idx < RESYNC_PAGES);

	r1_bio->sectors = nr_sectors;

	अगर (mddev_is_clustered(mddev) &&
			conf->cluster_sync_high < sector_nr + nr_sectors) अणु
		conf->cluster_sync_low = mddev->curr_resync_completed;
		conf->cluster_sync_high = conf->cluster_sync_low + CLUSTER_RESYNC_WINDOW_SECTORS;
		/* Send resync message */
		md_cluster_ops->resync_info_update(mddev,
				conf->cluster_sync_low,
				conf->cluster_sync_high);
	पूर्ण

	/* For a user-requested sync, we पढ़ो all पढ़ोable devices and करो a
	 * compare
	 */
	अगर (test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery)) अणु
		atomic_set(&r1_bio->reमुख्यing, पढ़ो_tarमाला_लो);
		क्रम (i = 0; i < conf->raid_disks * 2 && पढ़ो_tarमाला_लो; i++) अणु
			bio = r1_bio->bios[i];
			अगर (bio->bi_end_io == end_sync_पढ़ो) अणु
				पढ़ो_tarमाला_लो--;
				md_sync_acct_bio(bio, nr_sectors);
				अगर (पढ़ो_tarमाला_लो == 1)
					bio->bi_opf &= ~MD_FAILFAST;
				submit_bio_noacct(bio);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		atomic_set(&r1_bio->reमुख्यing, 1);
		bio = r1_bio->bios[r1_bio->पढ़ो_disk];
		md_sync_acct_bio(bio, nr_sectors);
		अगर (पढ़ो_tarमाला_लो == 1)
			bio->bi_opf &= ~MD_FAILFAST;
		submit_bio_noacct(bio);
	पूर्ण
	वापस nr_sectors;
पूर्ण

अटल sector_t raid1_size(काष्ठा mddev *mddev, sector_t sectors, पूर्णांक raid_disks)
अणु
	अगर (sectors)
		वापस sectors;

	वापस mddev->dev_sectors;
पूर्ण

अटल काष्ठा r1conf *setup_conf(काष्ठा mddev *mddev)
अणु
	काष्ठा r1conf *conf;
	पूर्णांक i;
	काष्ठा raid1_info *disk;
	काष्ठा md_rdev *rdev;
	पूर्णांक err = -ENOMEM;

	conf = kzalloc(माप(काष्ठा r1conf), GFP_KERNEL);
	अगर (!conf)
		जाओ पात;

	conf->nr_pending = kसुस्मृति(BARRIER_BUCKETS_NR,
				   माप(atomic_t), GFP_KERNEL);
	अगर (!conf->nr_pending)
		जाओ पात;

	conf->nr_रुकोing = kसुस्मृति(BARRIER_BUCKETS_NR,
				   माप(atomic_t), GFP_KERNEL);
	अगर (!conf->nr_रुकोing)
		जाओ पात;

	conf->nr_queued = kसुस्मृति(BARRIER_BUCKETS_NR,
				  माप(atomic_t), GFP_KERNEL);
	अगर (!conf->nr_queued)
		जाओ पात;

	conf->barrier = kसुस्मृति(BARRIER_BUCKETS_NR,
				माप(atomic_t), GFP_KERNEL);
	अगर (!conf->barrier)
		जाओ पात;

	conf->mirrors = kzalloc(array3_size(माप(काष्ठा raid1_info),
					    mddev->raid_disks, 2),
				GFP_KERNEL);
	अगर (!conf->mirrors)
		जाओ पात;

	conf->पंचांगppage = alloc_page(GFP_KERNEL);
	अगर (!conf->पंचांगppage)
		जाओ पात;

	conf->poolinfo = kzalloc(माप(*conf->poolinfo), GFP_KERNEL);
	अगर (!conf->poolinfo)
		जाओ पात;
	conf->poolinfo->raid_disks = mddev->raid_disks * 2;
	err = mempool_init(&conf->r1bio_pool, NR_RAID_BIOS, r1bio_pool_alloc,
			   rbio_pool_मुक्त, conf->poolinfo);
	अगर (err)
		जाओ पात;

	err = bioset_init(&conf->bio_split, BIO_POOL_SIZE, 0, 0);
	अगर (err)
		जाओ पात;

	conf->poolinfo->mddev = mddev;

	err = -EINVAL;
	spin_lock_init(&conf->device_lock);
	rdev_क्रम_each(rdev, mddev) अणु
		पूर्णांक disk_idx = rdev->raid_disk;
		अगर (disk_idx >= mddev->raid_disks
		    || disk_idx < 0)
			जारी;
		अगर (test_bit(Replacement, &rdev->flags))
			disk = conf->mirrors + mddev->raid_disks + disk_idx;
		अन्यथा
			disk = conf->mirrors + disk_idx;

		अगर (disk->rdev)
			जाओ पात;
		disk->rdev = rdev;
		disk->head_position = 0;
		disk->seq_start = MaxSector;
	पूर्ण
	conf->raid_disks = mddev->raid_disks;
	conf->mddev = mddev;
	INIT_LIST_HEAD(&conf->retry_list);
	INIT_LIST_HEAD(&conf->bio_end_io_list);

	spin_lock_init(&conf->resync_lock);
	init_रुकोqueue_head(&conf->रुको_barrier);

	bio_list_init(&conf->pending_bio_list);
	conf->pending_count = 0;
	conf->recovery_disabled = mddev->recovery_disabled - 1;

	err = -EIO;
	क्रम (i = 0; i < conf->raid_disks * 2; i++) अणु

		disk = conf->mirrors + i;

		अगर (i < conf->raid_disks &&
		    disk[conf->raid_disks].rdev) अणु
			/* This slot has a replacement. */
			अगर (!disk->rdev) अणु
				/* No original, just make the replacement
				 * a recovering spare
				 */
				disk->rdev =
					disk[conf->raid_disks].rdev;
				disk[conf->raid_disks].rdev = शून्य;
			पूर्ण अन्यथा अगर (!test_bit(In_sync, &disk->rdev->flags))
				/* Original is not in_sync - bad */
				जाओ पात;
		पूर्ण

		अगर (!disk->rdev ||
		    !test_bit(In_sync, &disk->rdev->flags)) अणु
			disk->head_position = 0;
			अगर (disk->rdev &&
			    (disk->rdev->saved_raid_disk < 0))
				conf->fullsync = 1;
		पूर्ण
	पूर्ण

	err = -ENOMEM;
	conf->thपढ़ो = md_रेजिस्टर_thपढ़ो(raid1d, mddev, "raid1");
	अगर (!conf->thपढ़ो)
		जाओ पात;

	वापस conf;

 पात:
	अगर (conf) अणु
		mempool_निकास(&conf->r1bio_pool);
		kमुक्त(conf->mirrors);
		safe_put_page(conf->पंचांगppage);
		kमुक्त(conf->poolinfo);
		kमुक्त(conf->nr_pending);
		kमुक्त(conf->nr_रुकोing);
		kमुक्त(conf->nr_queued);
		kमुक्त(conf->barrier);
		bioset_निकास(&conf->bio_split);
		kमुक्त(conf);
	पूर्ण
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम raid1_मुक्त(काष्ठा mddev *mddev, व्योम *priv);
अटल पूर्णांक raid1_run(काष्ठा mddev *mddev)
अणु
	काष्ठा r1conf *conf;
	पूर्णांक i;
	काष्ठा md_rdev *rdev;
	पूर्णांक ret;
	bool discard_supported = false;

	अगर (mddev->level != 1) अणु
		pr_warn("md/raid1:%s: raid level not set to mirroring (%d)\n",
			mdname(mddev), mddev->level);
		वापस -EIO;
	पूर्ण
	अगर (mddev->reshape_position != MaxSector) अणु
		pr_warn("md/raid1:%s: reshape_position set but not supported\n",
			mdname(mddev));
		वापस -EIO;
	पूर्ण
	अगर (mddev_init_ग_लिखोs_pending(mddev) < 0)
		वापस -ENOMEM;
	/*
	 * copy the alपढ़ोy verअगरied devices पूर्णांकo our निजी RAID1
	 * bookkeeping area. [whatever we allocate in run(),
	 * should be मुक्तd in raid1_मुक्त()]
	 */
	अगर (mddev->निजी == शून्य)
		conf = setup_conf(mddev);
	अन्यथा
		conf = mddev->निजी;

	अगर (IS_ERR(conf))
		वापस PTR_ERR(conf);

	अगर (mddev->queue) अणु
		blk_queue_max_ग_लिखो_same_sectors(mddev->queue, 0);
		blk_queue_max_ग_लिखो_zeroes_sectors(mddev->queue, 0);
	पूर्ण

	rdev_क्रम_each(rdev, mddev) अणु
		अगर (!mddev->gendisk)
			जारी;
		disk_stack_limits(mddev->gendisk, rdev->bdev,
				  rdev->data_offset << 9);
		अगर (blk_queue_discard(bdev_get_queue(rdev->bdev)))
			discard_supported = true;
	पूर्ण

	mddev->degraded = 0;
	क्रम (i = 0; i < conf->raid_disks; i++)
		अगर (conf->mirrors[i].rdev == शून्य ||
		    !test_bit(In_sync, &conf->mirrors[i].rdev->flags) ||
		    test_bit(Faulty, &conf->mirrors[i].rdev->flags))
			mddev->degraded++;
	/*
	 * RAID1 needs at least one disk in active
	 */
	अगर (conf->raid_disks - mddev->degraded < 1) अणु
		ret = -EINVAL;
		जाओ पात;
	पूर्ण

	अगर (conf->raid_disks - mddev->degraded == 1)
		mddev->recovery_cp = MaxSector;

	अगर (mddev->recovery_cp != MaxSector)
		pr_info("md/raid1:%s: not clean -- starting background reconstruction\n",
			mdname(mddev));
	pr_info("md/raid1:%s: active with %d out of %d mirrors\n",
		mdname(mddev), mddev->raid_disks - mddev->degraded,
		mddev->raid_disks);

	/*
	 * Ok, everything is just fine now
	 */
	mddev->thपढ़ो = conf->thपढ़ो;
	conf->thपढ़ो = शून्य;
	mddev->निजी = conf;
	set_bit(MD_FAILFAST_SUPPORTED, &mddev->flags);

	md_set_array_sectors(mddev, raid1_size(mddev, 0, 0));

	अगर (mddev->queue) अणु
		अगर (discard_supported)
			blk_queue_flag_set(QUEUE_FLAG_DISCARD,
						mddev->queue);
		अन्यथा
			blk_queue_flag_clear(QUEUE_FLAG_DISCARD,
						  mddev->queue);
	पूर्ण

	ret = md_पूर्णांकegrity_रेजिस्टर(mddev);
	अगर (ret) अणु
		md_unरेजिस्टर_thपढ़ो(&mddev->thपढ़ो);
		जाओ पात;
	पूर्ण
	वापस 0;

पात:
	raid1_मुक्त(mddev, conf);
	वापस ret;
पूर्ण

अटल व्योम raid1_मुक्त(काष्ठा mddev *mddev, व्योम *priv)
अणु
	काष्ठा r1conf *conf = priv;

	mempool_निकास(&conf->r1bio_pool);
	kमुक्त(conf->mirrors);
	safe_put_page(conf->पंचांगppage);
	kमुक्त(conf->poolinfo);
	kमुक्त(conf->nr_pending);
	kमुक्त(conf->nr_रुकोing);
	kमुक्त(conf->nr_queued);
	kमुक्त(conf->barrier);
	bioset_निकास(&conf->bio_split);
	kमुक्त(conf);
पूर्ण

अटल पूर्णांक raid1_resize(काष्ठा mddev *mddev, sector_t sectors)
अणु
	/* no resync is happening, and there is enough space
	 * on all devices, so we can resize.
	 * We need to make sure resync covers any new space.
	 * If the array is shrinking we should possibly रुको until
	 * any io in the हटाओd space completes, but it hardly seems
	 * worth it.
	 */
	sector_t newsize = raid1_size(mddev, sectors, 0);
	अगर (mddev->बाह्यal_size &&
	    mddev->array_sectors > newsize)
		वापस -EINVAL;
	अगर (mddev->biपंचांगap) अणु
		पूर्णांक ret = md_biपंचांगap_resize(mddev->biपंचांगap, newsize, 0, 0);
		अगर (ret)
			वापस ret;
	पूर्ण
	md_set_array_sectors(mddev, newsize);
	अगर (sectors > mddev->dev_sectors &&
	    mddev->recovery_cp > mddev->dev_sectors) अणु
		mddev->recovery_cp = mddev->dev_sectors;
		set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	पूर्ण
	mddev->dev_sectors = sectors;
	mddev->resync_max_sectors = sectors;
	वापस 0;
पूर्ण

अटल पूर्णांक raid1_reshape(काष्ठा mddev *mddev)
अणु
	/* We need to:
	 * 1/ resize the r1bio_pool
	 * 2/ resize conf->mirrors
	 *
	 * We allocate a new r1bio_pool अगर we can.
	 * Then उठाओ a device barrier and रुको until all IO stops.
	 * Then resize conf->mirrors and swap in the new r1bio pool.
	 *
	 * At the same समय, we "pack" the devices so that all the missing
	 * devices have the higher raid_disk numbers.
	 */
	mempool_t newpool, oldpool;
	काष्ठा pool_info *newpoolinfo;
	काष्ठा raid1_info *newmirrors;
	काष्ठा r1conf *conf = mddev->निजी;
	पूर्णांक cnt, raid_disks;
	अचिन्हित दीर्घ flags;
	पूर्णांक d, d2;
	पूर्णांक ret;

	स_रखो(&newpool, 0, माप(newpool));
	स_रखो(&oldpool, 0, माप(oldpool));

	/* Cannot change chunk_size, layout, or level */
	अगर (mddev->chunk_sectors != mddev->new_chunk_sectors ||
	    mddev->layout != mddev->new_layout ||
	    mddev->level != mddev->new_level) अणु
		mddev->new_chunk_sectors = mddev->chunk_sectors;
		mddev->new_layout = mddev->layout;
		mddev->new_level = mddev->level;
		वापस -EINVAL;
	पूर्ण

	अगर (!mddev_is_clustered(mddev))
		md_allow_ग_लिखो(mddev);

	raid_disks = mddev->raid_disks + mddev->delta_disks;

	अगर (raid_disks < conf->raid_disks) अणु
		cnt=0;
		क्रम (d= 0; d < conf->raid_disks; d++)
			अगर (conf->mirrors[d].rdev)
				cnt++;
		अगर (cnt > raid_disks)
			वापस -EBUSY;
	पूर्ण

	newpoolinfo = kदो_स्मृति(माप(*newpoolinfo), GFP_KERNEL);
	अगर (!newpoolinfo)
		वापस -ENOMEM;
	newpoolinfo->mddev = mddev;
	newpoolinfo->raid_disks = raid_disks * 2;

	ret = mempool_init(&newpool, NR_RAID_BIOS, r1bio_pool_alloc,
			   rbio_pool_मुक्त, newpoolinfo);
	अगर (ret) अणु
		kमुक्त(newpoolinfo);
		वापस ret;
	पूर्ण
	newmirrors = kzalloc(array3_size(माप(काष्ठा raid1_info),
					 raid_disks, 2),
			     GFP_KERNEL);
	अगर (!newmirrors) अणु
		kमुक्त(newpoolinfo);
		mempool_निकास(&newpool);
		वापस -ENOMEM;
	पूर्ण

	मुक्तze_array(conf, 0);

	/* ok, everything is stopped */
	oldpool = conf->r1bio_pool;
	conf->r1bio_pool = newpool;

	क्रम (d = d2 = 0; d < conf->raid_disks; d++) अणु
		काष्ठा md_rdev *rdev = conf->mirrors[d].rdev;
		अगर (rdev && rdev->raid_disk != d2) अणु
			sysfs_unlink_rdev(mddev, rdev);
			rdev->raid_disk = d2;
			sysfs_unlink_rdev(mddev, rdev);
			अगर (sysfs_link_rdev(mddev, rdev))
				pr_warn("md/raid1:%s: cannot register rd%d\n",
					mdname(mddev), rdev->raid_disk);
		पूर्ण
		अगर (rdev)
			newmirrors[d2++].rdev = rdev;
	पूर्ण
	kमुक्त(conf->mirrors);
	conf->mirrors = newmirrors;
	kमुक्त(conf->poolinfo);
	conf->poolinfo = newpoolinfo;

	spin_lock_irqsave(&conf->device_lock, flags);
	mddev->degraded += (raid_disks - conf->raid_disks);
	spin_unlock_irqrestore(&conf->device_lock, flags);
	conf->raid_disks = mddev->raid_disks = raid_disks;
	mddev->delta_disks = 0;

	unमुक्तze_array(conf);

	set_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	md_wakeup_thपढ़ो(mddev->thपढ़ो);

	mempool_निकास(&oldpool);
	वापस 0;
पूर्ण

अटल व्योम raid1_quiesce(काष्ठा mddev *mddev, पूर्णांक quiesce)
अणु
	काष्ठा r1conf *conf = mddev->निजी;

	अगर (quiesce)
		मुक्तze_array(conf, 0);
	अन्यथा
		unमुक्तze_array(conf);
पूर्ण

अटल व्योम *raid1_takeover(काष्ठा mddev *mddev)
अणु
	/* raid1 can take over:
	 *  raid5 with 2 devices, any layout or chunk size
	 */
	अगर (mddev->level == 5 && mddev->raid_disks == 2) अणु
		काष्ठा r1conf *conf;
		mddev->new_level = 1;
		mddev->new_layout = 0;
		mddev->new_chunk_sectors = 0;
		conf = setup_conf(mddev);
		अगर (!IS_ERR(conf)) अणु
			/* Array must appear to be quiesced */
			conf->array_frozen = 1;
			mddev_clear_unsupported_flags(mddev,
				UNSUPPORTED_MDDEV_FLAGS);
		पूर्ण
		वापस conf;
	पूर्ण
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा md_personality raid1_personality =
अणु
	.name		= "raid1",
	.level		= 1,
	.owner		= THIS_MODULE,
	.make_request	= raid1_make_request,
	.run		= raid1_run,
	.मुक्त		= raid1_मुक्त,
	.status		= raid1_status,
	.error_handler	= raid1_error,
	.hot_add_disk	= raid1_add_disk,
	.hot_हटाओ_disk= raid1_हटाओ_disk,
	.spare_active	= raid1_spare_active,
	.sync_request	= raid1_sync_request,
	.resize		= raid1_resize,
	.size		= raid1_size,
	.check_reshape	= raid1_reshape,
	.quiesce	= raid1_quiesce,
	.takeover	= raid1_takeover,
पूर्ण;

अटल पूर्णांक __init raid_init(व्योम)
अणु
	वापस रेजिस्टर_md_personality(&raid1_personality);
पूर्ण

अटल व्योम raid_निकास(व्योम)
अणु
	unरेजिस्टर_md_personality(&raid1_personality);
पूर्ण

module_init(raid_init);
module_निकास(raid_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("RAID1 (mirroring) personality for MD");
MODULE_ALIAS("md-personality-3"); /* RAID1 */
MODULE_ALIAS("md-raid1");
MODULE_ALIAS("md-level-1");

module_param(max_queued_requests, पूर्णांक, S_IRUGO|S_IWUSR);
