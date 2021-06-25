<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * raid10.c : Multiple Devices driver क्रम Linux
 *
 * Copyright (C) 2000-2004 Neil Brown
 *
 * RAID-10 support क्रम md.
 *
 * Base on code in raid1.c.  See raid1.c क्रम further copyright inक्रमmation.
 */

#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/raid/md_p.h>
#समावेश <trace/events/block.h>
#समावेश "md.h"
#समावेश "raid10.h"
#समावेश "raid0.h"
#समावेश "md-bitmap.h"

/*
 * RAID10 provides a combination of RAID0 and RAID1 functionality.
 * The layout of data is defined by
 *    chunk_size
 *    raid_disks
 *    near_copies (stored in low byte of layout)
 *    far_copies (stored in second byte of layout)
 *    far_offset (stored in bit 16 of layout )
 *    use_far_sets (stored in bit 17 of layout )
 *    use_far_sets_bugfixed (stored in bit 18 of layout )
 *
 * The data to be stored is भागided पूर्णांकo chunks using chunksize.  Each device
 * is भागided पूर्णांकo far_copies sections.   In each section, chunks are laid out
 * in a style similar to raid0, but near_copies copies of each chunk is stored
 * (each on a dअगरferent drive).  The starting device क्रम each section is offset
 * near_copies from the starting device of the previous section.  Thus there
 * are (near_copies * far_copies) of each chunk, and each is on a dअगरferent
 * drive.  near_copies and far_copies must be at least one, and their product
 * is at most raid_disks.
 *
 * If far_offset is true, then the far_copies are handled a bit dअगरferently.
 * The copies are still in dअगरferent stripes, but instead of being very far
 * apart on disk, there are adjacent stripes.
 *
 * The far and offset algorithms are handled slightly dअगरferently अगर
 * 'use_far_sets' is true.  In this case, the array's devices are grouped पूर्णांकo
 * sets that are (near_copies * far_copies) in size.  The far copied stripes
 * are still shअगरted by 'near_copies' devices, but this shअगरting stays confined
 * to the set rather than the entire array.  This is करोne to improve the number
 * of device combinations that can fail without causing the array to fail.
 * Example 'far' algorithm w/o 'use_far_sets' (each letter represents a chunk
 * on a device):
 *    A B C D    A B C D E
 *      ...         ...
 *    D A B C    E A B C D
 * Example 'far' algorithm w/ 'use_far_sets' enabled (sets illustrated w/ []'s):
 *    [A B] [C D]    [A B] [C D E]
 *    |...| |...|    |...| | ... |
 *    [B A] [D C]    [B A] [E C D]
 */

अटल व्योम allow_barrier(काष्ठा r10conf *conf);
अटल व्योम lower_barrier(काष्ठा r10conf *conf);
अटल पूर्णांक _enough(काष्ठा r10conf *conf, पूर्णांक previous, पूर्णांक ignore);
अटल पूर्णांक enough(काष्ठा r10conf *conf, पूर्णांक ignore);
अटल sector_t reshape_request(काष्ठा mddev *mddev, sector_t sector_nr,
				पूर्णांक *skipped);
अटल व्योम reshape_request_ग_लिखो(काष्ठा mddev *mddev, काष्ठा r10bio *r10_bio);
अटल व्योम end_reshape_ग_लिखो(काष्ठा bio *bio);
अटल व्योम end_reshape(काष्ठा r10conf *conf);

#घोषणा raid10_log(md, fmt, args...)				\
	करो अणु अगर ((md)->queue) blk_add_trace_msg((md)->queue, "raid10 " fmt, ##args); पूर्ण जबतक (0)

#समावेश "raid1-10.c"

/*
 * क्रम resync bio, r10bio poपूर्णांकer can be retrieved from the per-bio
 * 'struct resync_pages'.
 */
अटल अंतरभूत काष्ठा r10bio *get_resync_r10bio(काष्ठा bio *bio)
अणु
	वापस get_resync_pages(bio)->raid_bio;
पूर्ण

अटल व्योम * r10bio_pool_alloc(gfp_t gfp_flags, व्योम *data)
अणु
	काष्ठा r10conf *conf = data;
	पूर्णांक size = दुरत्व(काष्ठा r10bio, devs[conf->geo.raid_disks]);

	/* allocate a r10bio with room क्रम raid_disks entries in the
	 * bios array */
	वापस kzalloc(size, gfp_flags);
पूर्ण

#घोषणा RESYNC_SECTORS (RESYNC_BLOCK_SIZE >> 9)
/* amount of memory to reserve क्रम resync requests */
#घोषणा RESYNC_WINDOW (1024*1024)
/* maximum number of concurrent requests, memory permitting */
#घोषणा RESYNC_DEPTH (32*1024*1024/RESYNC_BLOCK_SIZE)
#घोषणा CLUSTER_RESYNC_WINDOW (32 * RESYNC_WINDOW)
#घोषणा CLUSTER_RESYNC_WINDOW_SECTORS (CLUSTER_RESYNC_WINDOW >> 9)

/*
 * When perक्रमming a resync, we need to पढ़ो and compare, so
 * we need as many pages are there are copies.
 * When perक्रमming a recovery, we need 2 bios, one क्रम पढ़ो,
 * one क्रम ग_लिखो (we recover only one drive per r10buf)
 *
 */
अटल व्योम * r10buf_pool_alloc(gfp_t gfp_flags, व्योम *data)
अणु
	काष्ठा r10conf *conf = data;
	काष्ठा r10bio *r10_bio;
	काष्ठा bio *bio;
	पूर्णांक j;
	पूर्णांक nalloc, nalloc_rp;
	काष्ठा resync_pages *rps;

	r10_bio = r10bio_pool_alloc(gfp_flags, conf);
	अगर (!r10_bio)
		वापस शून्य;

	अगर (test_bit(MD_RECOVERY_SYNC, &conf->mddev->recovery) ||
	    test_bit(MD_RECOVERY_RESHAPE, &conf->mddev->recovery))
		nalloc = conf->copies; /* resync */
	अन्यथा
		nalloc = 2; /* recovery */

	/* allocate once क्रम all bios */
	अगर (!conf->have_replacement)
		nalloc_rp = nalloc;
	अन्यथा
		nalloc_rp = nalloc * 2;
	rps = kदो_स्मृति_array(nalloc_rp, माप(काष्ठा resync_pages), gfp_flags);
	अगर (!rps)
		जाओ out_मुक्त_r10bio;

	/*
	 * Allocate bios.
	 */
	क्रम (j = nalloc ; j-- ; ) अणु
		bio = bio_kदो_स्मृति(gfp_flags, RESYNC_PAGES);
		अगर (!bio)
			जाओ out_मुक्त_bio;
		r10_bio->devs[j].bio = bio;
		अगर (!conf->have_replacement)
			जारी;
		bio = bio_kदो_स्मृति(gfp_flags, RESYNC_PAGES);
		अगर (!bio)
			जाओ out_मुक्त_bio;
		r10_bio->devs[j].repl_bio = bio;
	पूर्ण
	/*
	 * Allocate RESYNC_PAGES data pages and attach them
	 * where needed.
	 */
	क्रम (j = 0; j < nalloc; j++) अणु
		काष्ठा bio *rbio = r10_bio->devs[j].repl_bio;
		काष्ठा resync_pages *rp, *rp_repl;

		rp = &rps[j];
		अगर (rbio)
			rp_repl = &rps[nalloc + j];

		bio = r10_bio->devs[j].bio;

		अगर (!j || test_bit(MD_RECOVERY_SYNC,
				   &conf->mddev->recovery)) अणु
			अगर (resync_alloc_pages(rp, gfp_flags))
				जाओ out_मुक्त_pages;
		पूर्ण अन्यथा अणु
			स_नकल(rp, &rps[0], माप(*rp));
			resync_get_all_pages(rp);
		पूर्ण

		rp->raid_bio = r10_bio;
		bio->bi_निजी = rp;
		अगर (rbio) अणु
			स_नकल(rp_repl, rp, माप(*rp));
			rbio->bi_निजी = rp_repl;
		पूर्ण
	पूर्ण

	वापस r10_bio;

out_मुक्त_pages:
	जबतक (--j >= 0)
		resync_मुक्त_pages(&rps[j]);

	j = 0;
out_मुक्त_bio:
	क्रम ( ; j < nalloc; j++) अणु
		अगर (r10_bio->devs[j].bio)
			bio_put(r10_bio->devs[j].bio);
		अगर (r10_bio->devs[j].repl_bio)
			bio_put(r10_bio->devs[j].repl_bio);
	पूर्ण
	kमुक्त(rps);
out_मुक्त_r10bio:
	rbio_pool_मुक्त(r10_bio, conf);
	वापस शून्य;
पूर्ण

अटल व्योम r10buf_pool_मुक्त(व्योम *__r10_bio, व्योम *data)
अणु
	काष्ठा r10conf *conf = data;
	काष्ठा r10bio *r10bio = __r10_bio;
	पूर्णांक j;
	काष्ठा resync_pages *rp = शून्य;

	क्रम (j = conf->copies; j--; ) अणु
		काष्ठा bio *bio = r10bio->devs[j].bio;

		अगर (bio) अणु
			rp = get_resync_pages(bio);
			resync_मुक्त_pages(rp);
			bio_put(bio);
		पूर्ण

		bio = r10bio->devs[j].repl_bio;
		अगर (bio)
			bio_put(bio);
	पूर्ण

	/* resync pages array stored in the 1st bio's .bi_निजी */
	kमुक्त(rp);

	rbio_pool_मुक्त(r10bio, conf);
पूर्ण

अटल व्योम put_all_bios(काष्ठा r10conf *conf, काष्ठा r10bio *r10_bio)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < conf->geo.raid_disks; i++) अणु
		काष्ठा bio **bio = & r10_bio->devs[i].bio;
		अगर (!BIO_SPECIAL(*bio))
			bio_put(*bio);
		*bio = शून्य;
		bio = &r10_bio->devs[i].repl_bio;
		अगर (r10_bio->पढ़ो_slot < 0 && !BIO_SPECIAL(*bio))
			bio_put(*bio);
		*bio = शून्य;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_r10bio(काष्ठा r10bio *r10_bio)
अणु
	काष्ठा r10conf *conf = r10_bio->mddev->निजी;

	put_all_bios(conf, r10_bio);
	mempool_मुक्त(r10_bio, &conf->r10bio_pool);
पूर्ण

अटल व्योम put_buf(काष्ठा r10bio *r10_bio)
अणु
	काष्ठा r10conf *conf = r10_bio->mddev->निजी;

	mempool_मुक्त(r10_bio, &conf->r10buf_pool);

	lower_barrier(conf);
पूर्ण

अटल व्योम reschedule_retry(काष्ठा r10bio *r10_bio)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mddev *mddev = r10_bio->mddev;
	काष्ठा r10conf *conf = mddev->निजी;

	spin_lock_irqsave(&conf->device_lock, flags);
	list_add(&r10_bio->retry_list, &conf->retry_list);
	conf->nr_queued ++;
	spin_unlock_irqrestore(&conf->device_lock, flags);

	/* wake up frozen array... */
	wake_up(&conf->रुको_barrier);

	md_wakeup_thपढ़ो(mddev->thपढ़ो);
पूर्ण

/*
 * raid_end_bio_io() is called when we have finished servicing a mirrored
 * operation and are पढ़ोy to वापस a success/failure code to the buffer
 * cache layer.
 */
अटल व्योम raid_end_bio_io(काष्ठा r10bio *r10_bio)
अणु
	काष्ठा bio *bio = r10_bio->master_bio;
	काष्ठा r10conf *conf = r10_bio->mddev->निजी;

	अगर (!test_bit(R10BIO_Uptodate, &r10_bio->state))
		bio->bi_status = BLK_STS_IOERR;

	bio_endio(bio);
	/*
	 * Wake up any possible resync thपढ़ो that रुकोs क्रम the device
	 * to go idle.
	 */
	allow_barrier(conf);

	मुक्त_r10bio(r10_bio);
पूर्ण

/*
 * Update disk head position estimator based on IRQ completion info.
 */
अटल अंतरभूत व्योम update_head_pos(पूर्णांक slot, काष्ठा r10bio *r10_bio)
अणु
	काष्ठा r10conf *conf = r10_bio->mddev->निजी;

	conf->mirrors[r10_bio->devs[slot].devnum].head_position =
		r10_bio->devs[slot].addr + (r10_bio->sectors);
पूर्ण

/*
 * Find the disk number which triggered given bio
 */
अटल पूर्णांक find_bio_disk(काष्ठा r10conf *conf, काष्ठा r10bio *r10_bio,
			 काष्ठा bio *bio, पूर्णांक *slotp, पूर्णांक *replp)
अणु
	पूर्णांक slot;
	पूर्णांक repl = 0;

	क्रम (slot = 0; slot < conf->geo.raid_disks; slot++) अणु
		अगर (r10_bio->devs[slot].bio == bio)
			अवरोध;
		अगर (r10_bio->devs[slot].repl_bio == bio) अणु
			repl = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	update_head_pos(slot, r10_bio);

	अगर (slotp)
		*slotp = slot;
	अगर (replp)
		*replp = repl;
	वापस r10_bio->devs[slot].devnum;
पूर्ण

अटल व्योम raid10_end_पढ़ो_request(काष्ठा bio *bio)
अणु
	पूर्णांक uptodate = !bio->bi_status;
	काष्ठा r10bio *r10_bio = bio->bi_निजी;
	पूर्णांक slot;
	काष्ठा md_rdev *rdev;
	काष्ठा r10conf *conf = r10_bio->mddev->निजी;

	slot = r10_bio->पढ़ो_slot;
	rdev = r10_bio->devs[slot].rdev;
	/*
	 * this branch is our 'one mirror IO has finished' event handler:
	 */
	update_head_pos(slot, r10_bio);

	अगर (uptodate) अणु
		/*
		 * Set R10BIO_Uptodate in our master bio, so that
		 * we will वापस a good error code to the higher
		 * levels even अगर IO on some other mirrored buffer fails.
		 *
		 * The 'master' represents the composite IO operation to
		 * user-side. So अगर something रुकोs क्रम IO, then it will
		 * रुको क्रम the 'master' bio.
		 */
		set_bit(R10BIO_Uptodate, &r10_bio->state);
	पूर्ण अन्यथा अणु
		/* If all other devices that store this block have
		 * failed, we want to वापस the error upwards rather
		 * than fail the last device.  Here we redefine
		 * "uptodate" to mean "Don't want to retry"
		 */
		अगर (!_enough(conf, test_bit(R10BIO_Previous, &r10_bio->state),
			     rdev->raid_disk))
			uptodate = 1;
	पूर्ण
	अगर (uptodate) अणु
		raid_end_bio_io(r10_bio);
		rdev_dec_pending(rdev, conf->mddev);
	पूर्ण अन्यथा अणु
		/*
		 * oops, पढ़ो error - keep the refcount on the rdev
		 */
		अक्षर b[BDEVNAME_SIZE];
		pr_err_ratelimited("md/raid10:%s: %s: rescheduling sector %llu\n",
				   mdname(conf->mddev),
				   bdevname(rdev->bdev, b),
				   (अचिन्हित दीर्घ दीर्घ)r10_bio->sector);
		set_bit(R10BIO_ReadError, &r10_bio->state);
		reschedule_retry(r10_bio);
	पूर्ण
पूर्ण

अटल व्योम बंद_ग_लिखो(काष्ठा r10bio *r10_bio)
अणु
	/* clear the biपंचांगap अगर all ग_लिखोs complete successfully */
	md_biपंचांगap_endग_लिखो(r10_bio->mddev->biपंचांगap, r10_bio->sector,
			   r10_bio->sectors,
			   !test_bit(R10BIO_Degraded, &r10_bio->state),
			   0);
	md_ग_लिखो_end(r10_bio->mddev);
पूर्ण

अटल व्योम one_ग_लिखो_करोne(काष्ठा r10bio *r10_bio)
अणु
	अगर (atomic_dec_and_test(&r10_bio->reमुख्यing)) अणु
		अगर (test_bit(R10BIO_WriteError, &r10_bio->state))
			reschedule_retry(r10_bio);
		अन्यथा अणु
			बंद_ग_लिखो(r10_bio);
			अगर (test_bit(R10BIO_MadeGood, &r10_bio->state))
				reschedule_retry(r10_bio);
			अन्यथा
				raid_end_bio_io(r10_bio);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम raid10_end_ग_लिखो_request(काष्ठा bio *bio)
अणु
	काष्ठा r10bio *r10_bio = bio->bi_निजी;
	पूर्णांक dev;
	पूर्णांक dec_rdev = 1;
	काष्ठा r10conf *conf = r10_bio->mddev->निजी;
	पूर्णांक slot, repl;
	काष्ठा md_rdev *rdev = शून्य;
	काष्ठा bio *to_put = शून्य;
	bool discard_error;

	discard_error = bio->bi_status && bio_op(bio) == REQ_OP_DISCARD;

	dev = find_bio_disk(conf, r10_bio, bio, &slot, &repl);

	अगर (repl)
		rdev = conf->mirrors[dev].replacement;
	अगर (!rdev) अणु
		smp_rmb();
		repl = 0;
		rdev = conf->mirrors[dev].rdev;
	पूर्ण
	/*
	 * this branch is our 'one mirror IO has finished' event handler:
	 */
	अगर (bio->bi_status && !discard_error) अणु
		अगर (repl)
			/* Never record new bad blocks to replacement,
			 * just fail it.
			 */
			md_error(rdev->mddev, rdev);
		अन्यथा अणु
			set_bit(WriteErrorSeen,	&rdev->flags);
			अगर (!test_and_set_bit(WantReplacement, &rdev->flags))
				set_bit(MD_RECOVERY_NEEDED,
					&rdev->mddev->recovery);

			dec_rdev = 0;
			अगर (test_bit(FailFast, &rdev->flags) &&
			    (bio->bi_opf & MD_FAILFAST)) अणु
				md_error(rdev->mddev, rdev);
			पूर्ण

			/*
			 * When the device is faulty, it is not necessary to
			 * handle ग_लिखो error.
			 * For failfast, this is the only reमुख्यing device,
			 * We need to retry the ग_लिखो without FailFast.
			 */
			अगर (!test_bit(Faulty, &rdev->flags))
				set_bit(R10BIO_WriteError, &r10_bio->state);
			अन्यथा अणु
				r10_bio->devs[slot].bio = शून्य;
				to_put = bio;
				dec_rdev = 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Set R10BIO_Uptodate in our master bio, so that
		 * we will वापस a good error code क्रम to the higher
		 * levels even अगर IO on some other mirrored buffer fails.
		 *
		 * The 'master' represents the composite IO operation to
		 * user-side. So अगर something रुकोs क्रम IO, then it will
		 * रुको क्रम the 'master' bio.
		 */
		sector_t first_bad;
		पूर्णांक bad_sectors;

		/*
		 * Do not set R10BIO_Uptodate अगर the current device is
		 * rebuilding or Faulty. This is because we cannot use
		 * such device क्रम properly पढ़ोing the data back (we could
		 * potentially use it, अगर the current ग_लिखो would have felt
		 * beक्रमe rdev->recovery_offset, but क्रम simplicity we करोn't
		 * check this here.
		 */
		अगर (test_bit(In_sync, &rdev->flags) &&
		    !test_bit(Faulty, &rdev->flags))
			set_bit(R10BIO_Uptodate, &r10_bio->state);

		/* Maybe we can clear some bad blocks. */
		अगर (is_badblock(rdev,
				r10_bio->devs[slot].addr,
				r10_bio->sectors,
				&first_bad, &bad_sectors) && !discard_error) अणु
			bio_put(bio);
			अगर (repl)
				r10_bio->devs[slot].repl_bio = IO_MADE_GOOD;
			अन्यथा
				r10_bio->devs[slot].bio = IO_MADE_GOOD;
			dec_rdev = 0;
			set_bit(R10BIO_MadeGood, &r10_bio->state);
		पूर्ण
	पूर्ण

	/*
	 *
	 * Let's see अगर all mirrored ग_लिखो operations have finished
	 * alपढ़ोy.
	 */
	one_ग_लिखो_करोne(r10_bio);
	अगर (dec_rdev)
		rdev_dec_pending(rdev, conf->mddev);
	अगर (to_put)
		bio_put(to_put);
पूर्ण

/*
 * RAID10 layout manager
 * As well as the chunksize and raid_disks count, there are two
 * parameters: near_copies and far_copies.
 * near_copies * far_copies must be <= raid_disks.
 * Normally one of these will be 1.
 * If both are 1, we get raid0.
 * If near_copies == raid_disks, we get raid1.
 *
 * Chunks are laid out in raid0 style with near_copies copies of the
 * first chunk, followed by near_copies copies of the next chunk and
 * so on.
 * If far_copies > 1, then after 1/far_copies of the array has been asचिन्हित
 * as described above, we start again with a device offset of near_copies.
 * So we effectively have another copy of the whole array further करोwn all
 * the drives, but with blocks on dअगरferent drives.
 * With this layout, and block is never stored twice on the one device.
 *
 * raid10_find_phys finds the sector offset of a given भव sector
 * on each device that it is on.
 *
 * raid10_find_virt करोes the reverse mapping, from a device and a
 * sector offset to a भव address
 */

अटल व्योम __raid10_find_phys(काष्ठा geom *geo, काष्ठा r10bio *r10bio)
अणु
	पूर्णांक n,f;
	sector_t sector;
	sector_t chunk;
	sector_t stripe;
	पूर्णांक dev;
	पूर्णांक slot = 0;
	पूर्णांक last_far_set_start, last_far_set_size;

	last_far_set_start = (geo->raid_disks / geo->far_set_size) - 1;
	last_far_set_start *= geo->far_set_size;

	last_far_set_size = geo->far_set_size;
	last_far_set_size += (geo->raid_disks % geo->far_set_size);

	/* now calculate first sector/dev */
	chunk = r10bio->sector >> geo->chunk_shअगरt;
	sector = r10bio->sector & geo->chunk_mask;

	chunk *= geo->near_copies;
	stripe = chunk;
	dev = sector_भाग(stripe, geo->raid_disks);
	अगर (geo->far_offset)
		stripe *= geo->far_copies;

	sector += stripe << geo->chunk_shअगरt;

	/* and calculate all the others */
	क्रम (n = 0; n < geo->near_copies; n++) अणु
		पूर्णांक d = dev;
		पूर्णांक set;
		sector_t s = sector;
		r10bio->devs[slot].devnum = d;
		r10bio->devs[slot].addr = s;
		slot++;

		क्रम (f = 1; f < geo->far_copies; f++) अणु
			set = d / geo->far_set_size;
			d += geo->near_copies;

			अगर ((geo->raid_disks % geo->far_set_size) &&
			    (d > last_far_set_start)) अणु
				d -= last_far_set_start;
				d %= last_far_set_size;
				d += last_far_set_start;
			पूर्ण अन्यथा अणु
				d %= geo->far_set_size;
				d += geo->far_set_size * set;
			पूर्ण
			s += geo->stride;
			r10bio->devs[slot].devnum = d;
			r10bio->devs[slot].addr = s;
			slot++;
		पूर्ण
		dev++;
		अगर (dev >= geo->raid_disks) अणु
			dev = 0;
			sector += (geo->chunk_mask + 1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम raid10_find_phys(काष्ठा r10conf *conf, काष्ठा r10bio *r10bio)
अणु
	काष्ठा geom *geo = &conf->geo;

	अगर (conf->reshape_progress != MaxSector &&
	    ((r10bio->sector >= conf->reshape_progress) !=
	     conf->mddev->reshape_backwards)) अणु
		set_bit(R10BIO_Previous, &r10bio->state);
		geo = &conf->prev;
	पूर्ण अन्यथा
		clear_bit(R10BIO_Previous, &r10bio->state);

	__raid10_find_phys(geo, r10bio);
पूर्ण

अटल sector_t raid10_find_virt(काष्ठा r10conf *conf, sector_t sector, पूर्णांक dev)
अणु
	sector_t offset, chunk, vchunk;
	/* Never use conf->prev as this is only called during resync
	 * or recovery, so reshape isn't happening
	 */
	काष्ठा geom *geo = &conf->geo;
	पूर्णांक far_set_start = (dev / geo->far_set_size) * geo->far_set_size;
	पूर्णांक far_set_size = geo->far_set_size;
	पूर्णांक last_far_set_start;

	अगर (geo->raid_disks % geo->far_set_size) अणु
		last_far_set_start = (geo->raid_disks / geo->far_set_size) - 1;
		last_far_set_start *= geo->far_set_size;

		अगर (dev >= last_far_set_start) अणु
			far_set_size = geo->far_set_size;
			far_set_size += (geo->raid_disks % geo->far_set_size);
			far_set_start = last_far_set_start;
		पूर्ण
	पूर्ण

	offset = sector & geo->chunk_mask;
	अगर (geo->far_offset) अणु
		पूर्णांक fc;
		chunk = sector >> geo->chunk_shअगरt;
		fc = sector_भाग(chunk, geo->far_copies);
		dev -= fc * geo->near_copies;
		अगर (dev < far_set_start)
			dev += far_set_size;
	पूर्ण अन्यथा अणु
		जबतक (sector >= geo->stride) अणु
			sector -= geo->stride;
			अगर (dev < (geo->near_copies + far_set_start))
				dev += far_set_size - geo->near_copies;
			अन्यथा
				dev -= geo->near_copies;
		पूर्ण
		chunk = sector >> geo->chunk_shअगरt;
	पूर्ण
	vchunk = chunk * geo->raid_disks + dev;
	sector_भाग(vchunk, geo->near_copies);
	वापस (vchunk << geo->chunk_shअगरt) + offset;
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

/*
 * FIXME: possibly should rethink पढ़ोbalancing and करो it dअगरferently
 * depending on near_copies / far_copies geometry.
 */
अटल काष्ठा md_rdev *पढ़ो_balance(काष्ठा r10conf *conf,
				    काष्ठा r10bio *r10_bio,
				    पूर्णांक *max_sectors)
अणु
	स्थिर sector_t this_sector = r10_bio->sector;
	पूर्णांक disk, slot;
	पूर्णांक sectors = r10_bio->sectors;
	पूर्णांक best_good_sectors;
	sector_t new_distance, best_dist;
	काष्ठा md_rdev *best_dist_rdev, *best_pending_rdev, *rdev = शून्य;
	पूर्णांक करो_balance;
	पूर्णांक best_dist_slot, best_pending_slot;
	bool has_nonrot_disk = false;
	अचिन्हित पूर्णांक min_pending;
	काष्ठा geom *geo = &conf->geo;

	raid10_find_phys(conf, r10_bio);
	rcu_पढ़ो_lock();
	best_dist_slot = -1;
	min_pending = अच_पूर्णांक_उच्च;
	best_dist_rdev = शून्य;
	best_pending_rdev = शून्य;
	best_dist = MaxSector;
	best_good_sectors = 0;
	करो_balance = 1;
	clear_bit(R10BIO_FailFast, &r10_bio->state);
	/*
	 * Check अगर we can balance. We can balance on the whole
	 * device अगर no resync is going on (recovery is ok), or below
	 * the resync winकरोw. We take the first पढ़ोable disk when
	 * above the resync winकरोw.
	 */
	अगर ((conf->mddev->recovery_cp < MaxSector
	     && (this_sector + sectors >= conf->next_resync)) ||
	    (mddev_is_clustered(conf->mddev) &&
	     md_cluster_ops->area_resyncing(conf->mddev, READ, this_sector,
					    this_sector + sectors)))
		करो_balance = 0;

	क्रम (slot = 0; slot < conf->copies ; slot++) अणु
		sector_t first_bad;
		पूर्णांक bad_sectors;
		sector_t dev_sector;
		अचिन्हित पूर्णांक pending;
		bool nonrot;

		अगर (r10_bio->devs[slot].bio == IO_BLOCKED)
			जारी;
		disk = r10_bio->devs[slot].devnum;
		rdev = rcu_dereference(conf->mirrors[disk].replacement);
		अगर (rdev == शून्य || test_bit(Faulty, &rdev->flags) ||
		    r10_bio->devs[slot].addr + sectors > rdev->recovery_offset)
			rdev = rcu_dereference(conf->mirrors[disk].rdev);
		अगर (rdev == शून्य ||
		    test_bit(Faulty, &rdev->flags))
			जारी;
		अगर (!test_bit(In_sync, &rdev->flags) &&
		    r10_bio->devs[slot].addr + sectors > rdev->recovery_offset)
			जारी;

		dev_sector = r10_bio->devs[slot].addr;
		अगर (is_badblock(rdev, dev_sector, sectors,
				&first_bad, &bad_sectors)) अणु
			अगर (best_dist < MaxSector)
				/* Alपढ़ोy have a better slot */
				जारी;
			अगर (first_bad <= dev_sector) अणु
				/* Cannot पढ़ो here.  If this is the
				 * 'primary' device, then we must not पढ़ो
				 * beyond 'bad_sectors' from another device.
				 */
				bad_sectors -= (dev_sector - first_bad);
				अगर (!करो_balance && sectors > bad_sectors)
					sectors = bad_sectors;
				अगर (best_good_sectors > sectors)
					best_good_sectors = sectors;
			पूर्ण अन्यथा अणु
				sector_t good_sectors =
					first_bad - dev_sector;
				अगर (good_sectors > best_good_sectors) अणु
					best_good_sectors = good_sectors;
					best_dist_slot = slot;
					best_dist_rdev = rdev;
				पूर्ण
				अगर (!करो_balance)
					/* Must पढ़ो from here */
					अवरोध;
			पूर्ण
			जारी;
		पूर्ण अन्यथा
			best_good_sectors = sectors;

		अगर (!करो_balance)
			अवरोध;

		nonrot = blk_queue_nonrot(bdev_get_queue(rdev->bdev));
		has_nonrot_disk |= nonrot;
		pending = atomic_पढ़ो(&rdev->nr_pending);
		अगर (min_pending > pending && nonrot) अणु
			min_pending = pending;
			best_pending_slot = slot;
			best_pending_rdev = rdev;
		पूर्ण

		अगर (best_dist_slot >= 0)
			/* At least 2 disks to choose from so failfast is OK */
			set_bit(R10BIO_FailFast, &r10_bio->state);
		/* This optimisation is debatable, and completely destroys
		 * sequential पढ़ो speed क्रम 'far copies' arrays.  So only
		 * keep it क्रम 'near' arrays, and review those later.
		 */
		अगर (geo->near_copies > 1 && !pending)
			new_distance = 0;

		/* क्रम far > 1 always use the lowest address */
		अन्यथा अगर (geo->far_copies > 1)
			new_distance = r10_bio->devs[slot].addr;
		अन्यथा
			new_distance = असल(r10_bio->devs[slot].addr -
					   conf->mirrors[disk].head_position);

		अगर (new_distance < best_dist) अणु
			best_dist = new_distance;
			best_dist_slot = slot;
			best_dist_rdev = rdev;
		पूर्ण
	पूर्ण
	अगर (slot >= conf->copies) अणु
		अगर (has_nonrot_disk) अणु
			slot = best_pending_slot;
			rdev = best_pending_rdev;
		पूर्ण अन्यथा अणु
			slot = best_dist_slot;
			rdev = best_dist_rdev;
		पूर्ण
	पूर्ण

	अगर (slot >= 0) अणु
		atomic_inc(&rdev->nr_pending);
		r10_bio->पढ़ो_slot = slot;
	पूर्ण अन्यथा
		rdev = शून्य;
	rcu_पढ़ो_unlock();
	*max_sectors = best_good_sectors;

	वापस rdev;
पूर्ण

अटल व्योम flush_pending_ग_लिखोs(काष्ठा r10conf *conf)
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
		 * is a false-positive. Silence the warning by resetting
		 * thपढ़ो state
		 */
		__set_current_state(TASK_RUNNING);

		blk_start_plug(&plug);
		/* flush any pending biपंचांगap ग_लिखोs to disk
		 * beक्रमe proceeding w/ I/O */
		md_biपंचांगap_unplug(conf->mddev->biपंचांगap);
		wake_up(&conf->रुको_barrier);

		जबतक (bio) अणु /* submit pending ग_लिखोs */
			काष्ठा bio *next = bio->bi_next;
			काष्ठा md_rdev *rdev = (व्योम*)bio->bi_bdev;
			bio->bi_next = शून्य;
			bio_set_dev(bio, rdev->bdev);
			अगर (test_bit(Faulty, &rdev->flags)) अणु
				bio_io_error(bio);
			पूर्ण अन्यथा अगर (unlikely((bio_op(bio) ==  REQ_OP_DISCARD) &&
					    !blk_queue_discard(bio->bi_bdev->bd_disk->queue)))
				/* Just ignore it */
				bio_endio(bio);
			अन्यथा
				submit_bio_noacct(bio);
			bio = next;
		पूर्ण
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
 */

अटल व्योम उठाओ_barrier(काष्ठा r10conf *conf, पूर्णांक क्रमce)
अणु
	BUG_ON(क्रमce && !conf->barrier);
	spin_lock_irq(&conf->resync_lock);

	/* Wait until no block IO is रुकोing (unless 'force') */
	रुको_event_lock_irq(conf->रुको_barrier, क्रमce || !conf->nr_रुकोing,
			    conf->resync_lock);

	/* block any new IO from starting */
	conf->barrier++;

	/* Now रुको क्रम all pending IO to complete */
	रुको_event_lock_irq(conf->रुको_barrier,
			    !atomic_पढ़ो(&conf->nr_pending) && conf->barrier < RESYNC_DEPTH,
			    conf->resync_lock);

	spin_unlock_irq(&conf->resync_lock);
पूर्ण

अटल व्योम lower_barrier(काष्ठा r10conf *conf)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&conf->resync_lock, flags);
	conf->barrier--;
	spin_unlock_irqrestore(&conf->resync_lock, flags);
	wake_up(&conf->रुको_barrier);
पूर्ण

अटल व्योम रुको_barrier(काष्ठा r10conf *conf)
अणु
	spin_lock_irq(&conf->resync_lock);
	अगर (conf->barrier) अणु
		काष्ठा bio_list *bio_list = current->bio_list;
		conf->nr_रुकोing++;
		/* Wait क्रम the barrier to drop.
		 * However अगर there are alपढ़ोy pending
		 * requests (preventing the barrier from
		 * rising completely), and the
		 * pre-process bio queue isn't empty,
		 * then करोn't रुको, as we need to empty
		 * that queue to get the nr_pending
		 * count करोwn.
		 */
		raid10_log(conf->mddev, "wait barrier");
		रुको_event_lock_irq(conf->रुको_barrier,
				    !conf->barrier ||
				    (atomic_पढ़ो(&conf->nr_pending) &&
				     bio_list &&
				     (!bio_list_empty(&bio_list[0]) ||
				      !bio_list_empty(&bio_list[1]))) ||
				     /* move on अगर recovery thपढ़ो is
				      * blocked by us
				      */
				     (conf->mddev->thपढ़ो->tsk == current &&
				      test_bit(MD_RECOVERY_RUNNING,
					       &conf->mddev->recovery) &&
				      conf->nr_queued > 0),
				    conf->resync_lock);
		conf->nr_रुकोing--;
		अगर (!conf->nr_रुकोing)
			wake_up(&conf->रुको_barrier);
	पूर्ण
	atomic_inc(&conf->nr_pending);
	spin_unlock_irq(&conf->resync_lock);
पूर्ण

अटल व्योम allow_barrier(काष्ठा r10conf *conf)
अणु
	अगर ((atomic_dec_and_test(&conf->nr_pending)) ||
			(conf->array_मुक्तze_pending))
		wake_up(&conf->रुको_barrier);
पूर्ण

अटल व्योम मुक्तze_array(काष्ठा r10conf *conf, पूर्णांक extra)
अणु
	/* stop syncio and normal IO and रुको क्रम everything to
	 * go quiet.
	 * We increment barrier and nr_रुकोing, and then
	 * रुको until nr_pending match nr_queued+extra
	 * This is called in the context of one normal IO request
	 * that has failed. Thus any sync request that might be pending
	 * will be blocked by nr_pending, and we need to रुको क्रम
	 * pending IO requests to complete or be queued क्रम re-try.
	 * Thus the number queued (nr_queued) plus this request (extra)
	 * must match the number of pending IOs (nr_pending) beक्रमe
	 * we जारी.
	 */
	spin_lock_irq(&conf->resync_lock);
	conf->array_मुक्तze_pending++;
	conf->barrier++;
	conf->nr_रुकोing++;
	रुको_event_lock_irq_cmd(conf->रुको_barrier,
				atomic_पढ़ो(&conf->nr_pending) == conf->nr_queued+extra,
				conf->resync_lock,
				flush_pending_ग_लिखोs(conf));

	conf->array_मुक्तze_pending--;
	spin_unlock_irq(&conf->resync_lock);
पूर्ण

अटल व्योम unमुक्तze_array(काष्ठा r10conf *conf)
अणु
	/* reverse the effect of the मुक्तze */
	spin_lock_irq(&conf->resync_lock);
	conf->barrier--;
	conf->nr_रुकोing--;
	wake_up(&conf->रुको_barrier);
	spin_unlock_irq(&conf->resync_lock);
पूर्ण

अटल sector_t choose_data_offset(काष्ठा r10bio *r10_bio,
				   काष्ठा md_rdev *rdev)
अणु
	अगर (!test_bit(MD_RECOVERY_RESHAPE, &rdev->mddev->recovery) ||
	    test_bit(R10BIO_Previous, &r10_bio->state))
		वापस rdev->data_offset;
	अन्यथा
		वापस rdev->new_data_offset;
पूर्ण

काष्ठा raid10_plug_cb अणु
	काष्ठा blk_plug_cb	cb;
	काष्ठा bio_list		pending;
	पूर्णांक			pending_cnt;
पूर्ण;

अटल व्योम raid10_unplug(काष्ठा blk_plug_cb *cb, bool from_schedule)
अणु
	काष्ठा raid10_plug_cb *plug = container_of(cb, काष्ठा raid10_plug_cb,
						   cb);
	काष्ठा mddev *mddev = plug->cb.data;
	काष्ठा r10conf *conf = mddev->निजी;
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
	md_biपंचांगap_unplug(mddev->biपंचांगap);
	wake_up(&conf->रुको_barrier);

	जबतक (bio) अणु /* submit pending ग_लिखोs */
		काष्ठा bio *next = bio->bi_next;
		काष्ठा md_rdev *rdev = (व्योम*)bio->bi_bdev;
		bio->bi_next = शून्य;
		bio_set_dev(bio, rdev->bdev);
		अगर (test_bit(Faulty, &rdev->flags)) अणु
			bio_io_error(bio);
		पूर्ण अन्यथा अगर (unlikely((bio_op(bio) ==  REQ_OP_DISCARD) &&
				    !blk_queue_discard(bio->bi_bdev->bd_disk->queue)))
			/* Just ignore it */
			bio_endio(bio);
		अन्यथा
			submit_bio_noacct(bio);
		bio = next;
	पूर्ण
	kमुक्त(plug);
पूर्ण

/*
 * 1. Register the new request and रुको अगर the reस्थिरruction thपढ़ो has put
 * up a bar क्रम new requests. Continue immediately अगर no resync is active
 * currently.
 * 2. If IO spans the reshape position.  Need to रुको क्रम reshape to pass.
 */
अटल व्योम regular_request_रुको(काष्ठा mddev *mddev, काष्ठा r10conf *conf,
				 काष्ठा bio *bio, sector_t sectors)
अणु
	रुको_barrier(conf);
	जबतक (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
	    bio->bi_iter.bi_sector < conf->reshape_progress &&
	    bio->bi_iter.bi_sector + sectors > conf->reshape_progress) अणु
		raid10_log(conf->mddev, "wait reshape");
		allow_barrier(conf);
		रुको_event(conf->रुको_barrier,
			   conf->reshape_progress <= bio->bi_iter.bi_sector ||
			   conf->reshape_progress >= bio->bi_iter.bi_sector +
			   sectors);
		रुको_barrier(conf);
	पूर्ण
पूर्ण

अटल व्योम raid10_पढ़ो_request(काष्ठा mddev *mddev, काष्ठा bio *bio,
				काष्ठा r10bio *r10_bio)
अणु
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा bio *पढ़ो_bio;
	स्थिर पूर्णांक op = bio_op(bio);
	स्थिर अचिन्हित दीर्घ करो_sync = (bio->bi_opf & REQ_SYNC);
	पूर्णांक max_sectors;
	काष्ठा md_rdev *rdev;
	अक्षर b[BDEVNAME_SIZE];
	पूर्णांक slot = r10_bio->पढ़ो_slot;
	काष्ठा md_rdev *err_rdev = शून्य;
	gfp_t gfp = GFP_NOIO;

	अगर (slot >= 0 && r10_bio->devs[slot].rdev) अणु
		/*
		 * This is an error retry, but we cannot
		 * safely dereference the rdev in the r10_bio,
		 * we must use the one in conf.
		 * If it has alपढ़ोy been disconnected (unlikely)
		 * we lose the device name in error messages.
		 */
		पूर्णांक disk;
		/*
		 * As we are blocking raid10, it is a little safer to
		 * use __GFP_HIGH.
		 */
		gfp = GFP_NOIO | __GFP_HIGH;

		rcu_पढ़ो_lock();
		disk = r10_bio->devs[slot].devnum;
		err_rdev = rcu_dereference(conf->mirrors[disk].rdev);
		अगर (err_rdev)
			bdevname(err_rdev->bdev, b);
		अन्यथा अणु
			म_नकल(b, "???");
			/* This never माला_लो dereferenced */
			err_rdev = r10_bio->devs[slot].rdev;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	regular_request_रुको(mddev, conf, bio, r10_bio->sectors);
	rdev = पढ़ो_balance(conf, r10_bio, &max_sectors);
	अगर (!rdev) अणु
		अगर (err_rdev) अणु
			pr_crit_ratelimited("md/raid10:%s: %s: unrecoverable I/O read error for block %llu\n",
					    mdname(mddev), b,
					    (अचिन्हित दीर्घ दीर्घ)r10_bio->sector);
		पूर्ण
		raid_end_bio_io(r10_bio);
		वापस;
	पूर्ण
	अगर (err_rdev)
		pr_err_ratelimited("md/raid10:%s: %s: redirecting sector %llu to another mirror\n",
				   mdname(mddev),
				   bdevname(rdev->bdev, b),
				   (अचिन्हित दीर्घ दीर्घ)r10_bio->sector);
	अगर (max_sectors < bio_sectors(bio)) अणु
		काष्ठा bio *split = bio_split(bio, max_sectors,
					      gfp, &conf->bio_split);
		bio_chain(split, bio);
		allow_barrier(conf);
		submit_bio_noacct(bio);
		रुको_barrier(conf);
		bio = split;
		r10_bio->master_bio = bio;
		r10_bio->sectors = max_sectors;
	पूर्ण
	slot = r10_bio->पढ़ो_slot;

	पढ़ो_bio = bio_clone_fast(bio, gfp, &mddev->bio_set);

	r10_bio->devs[slot].bio = पढ़ो_bio;
	r10_bio->devs[slot].rdev = rdev;

	पढ़ो_bio->bi_iter.bi_sector = r10_bio->devs[slot].addr +
		choose_data_offset(r10_bio, rdev);
	bio_set_dev(पढ़ो_bio, rdev->bdev);
	पढ़ो_bio->bi_end_io = raid10_end_पढ़ो_request;
	bio_set_op_attrs(पढ़ो_bio, op, करो_sync);
	अगर (test_bit(FailFast, &rdev->flags) &&
	    test_bit(R10BIO_FailFast, &r10_bio->state))
	        पढ़ो_bio->bi_opf |= MD_FAILFAST;
	पढ़ो_bio->bi_निजी = r10_bio;

	अगर (mddev->gendisk)
	        trace_block_bio_remap(पढ़ो_bio, disk_devt(mddev->gendisk),
	                              r10_bio->sector);
	submit_bio_noacct(पढ़ो_bio);
	वापस;
पूर्ण

अटल व्योम raid10_ग_लिखो_one_disk(काष्ठा mddev *mddev, काष्ठा r10bio *r10_bio,
				  काष्ठा bio *bio, bool replacement,
				  पूर्णांक n_copy)
अणु
	स्थिर पूर्णांक op = bio_op(bio);
	स्थिर अचिन्हित दीर्घ करो_sync = (bio->bi_opf & REQ_SYNC);
	स्थिर अचिन्हित दीर्घ करो_fua = (bio->bi_opf & REQ_FUA);
	अचिन्हित दीर्घ flags;
	काष्ठा blk_plug_cb *cb;
	काष्ठा raid10_plug_cb *plug = शून्य;
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा md_rdev *rdev;
	पूर्णांक devnum = r10_bio->devs[n_copy].devnum;
	काष्ठा bio *mbio;

	अगर (replacement) अणु
		rdev = conf->mirrors[devnum].replacement;
		अगर (rdev == शून्य) अणु
			/* Replacement just got moved to मुख्य 'rdev' */
			smp_mb();
			rdev = conf->mirrors[devnum].rdev;
		पूर्ण
	पूर्ण अन्यथा
		rdev = conf->mirrors[devnum].rdev;

	mbio = bio_clone_fast(bio, GFP_NOIO, &mddev->bio_set);
	अगर (replacement)
		r10_bio->devs[n_copy].repl_bio = mbio;
	अन्यथा
		r10_bio->devs[n_copy].bio = mbio;

	mbio->bi_iter.bi_sector	= (r10_bio->devs[n_copy].addr +
				   choose_data_offset(r10_bio, rdev));
	bio_set_dev(mbio, rdev->bdev);
	mbio->bi_end_io	= raid10_end_ग_लिखो_request;
	bio_set_op_attrs(mbio, op, करो_sync | करो_fua);
	अगर (!replacement && test_bit(FailFast,
				     &conf->mirrors[devnum].rdev->flags)
			 && enough(conf, devnum))
		mbio->bi_opf |= MD_FAILFAST;
	mbio->bi_निजी = r10_bio;

	अगर (conf->mddev->gendisk)
		trace_block_bio_remap(mbio, disk_devt(conf->mddev->gendisk),
				      r10_bio->sector);
	/* flush_pending_ग_लिखोs() needs access to the rdev so...*/
	mbio->bi_bdev = (व्योम *)rdev;

	atomic_inc(&r10_bio->reमुख्यing);

	cb = blk_check_plugged(raid10_unplug, mddev, माप(*plug));
	अगर (cb)
		plug = container_of(cb, काष्ठा raid10_plug_cb, cb);
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

अटल व्योम रुको_blocked_dev(काष्ठा mddev *mddev, काष्ठा r10bio *r10_bio)
अणु
	पूर्णांक i;
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा md_rdev *blocked_rdev;

retry_रुको:
	blocked_rdev = शून्य;
	rcu_पढ़ो_lock();
	क्रम (i = 0; i < conf->copies; i++) अणु
		काष्ठा md_rdev *rdev = rcu_dereference(conf->mirrors[i].rdev);
		काष्ठा md_rdev *rrdev = rcu_dereference(
			conf->mirrors[i].replacement);
		अगर (rdev == rrdev)
			rrdev = शून्य;
		अगर (rdev && unlikely(test_bit(Blocked, &rdev->flags))) अणु
			atomic_inc(&rdev->nr_pending);
			blocked_rdev = rdev;
			अवरोध;
		पूर्ण
		अगर (rrdev && unlikely(test_bit(Blocked, &rrdev->flags))) अणु
			atomic_inc(&rrdev->nr_pending);
			blocked_rdev = rrdev;
			अवरोध;
		पूर्ण

		अगर (rdev && test_bit(WriteErrorSeen, &rdev->flags)) अणु
			sector_t first_bad;
			sector_t dev_sector = r10_bio->devs[i].addr;
			पूर्णांक bad_sectors;
			पूर्णांक is_bad;

			/*
			 * Discard request करोesn't care the ग_लिखो result
			 * so it करोesn't need to रुको blocked disk here.
			 */
			अगर (!r10_bio->sectors)
				जारी;

			is_bad = is_badblock(rdev, dev_sector, r10_bio->sectors,
					     &first_bad, &bad_sectors);
			अगर (is_bad < 0) अणु
				/*
				 * Mustn't ग_लिखो here until the bad block
				 * is acknowledged
				 */
				atomic_inc(&rdev->nr_pending);
				set_bit(BlockedBadBlocks, &rdev->flags);
				blocked_rdev = rdev;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (unlikely(blocked_rdev)) अणु
		/* Have to रुको क्रम this device to get unblocked, then retry */
		allow_barrier(conf);
		raid10_log(conf->mddev, "%s wait rdev %d blocked",
				__func__, blocked_rdev->raid_disk);
		md_रुको_क्रम_blocked_rdev(blocked_rdev, mddev);
		रुको_barrier(conf);
		जाओ retry_रुको;
	पूर्ण
पूर्ण

अटल व्योम raid10_ग_लिखो_request(काष्ठा mddev *mddev, काष्ठा bio *bio,
				 काष्ठा r10bio *r10_bio)
अणु
	काष्ठा r10conf *conf = mddev->निजी;
	पूर्णांक i;
	sector_t sectors;
	पूर्णांक max_sectors;

	अगर ((mddev_is_clustered(mddev) &&
	     md_cluster_ops->area_resyncing(mddev, WRITE,
					    bio->bi_iter.bi_sector,
					    bio_end_sector(bio)))) अणु
		DEFINE_WAIT(w);
		क्रम (;;) अणु
			prepare_to_रुको(&conf->रुको_barrier,
					&w, TASK_IDLE);
			अगर (!md_cluster_ops->area_resyncing(mddev, WRITE,
				 bio->bi_iter.bi_sector, bio_end_sector(bio)))
				अवरोध;
			schedule();
		पूर्ण
		finish_रुको(&conf->रुको_barrier, &w);
	पूर्ण

	sectors = r10_bio->sectors;
	regular_request_रुको(mddev, conf, bio, sectors);
	अगर (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
	    (mddev->reshape_backwards
	     ? (bio->bi_iter.bi_sector < conf->reshape_safe &&
		bio->bi_iter.bi_sector + sectors > conf->reshape_progress)
	     : (bio->bi_iter.bi_sector + sectors > conf->reshape_safe &&
		bio->bi_iter.bi_sector < conf->reshape_progress))) अणु
		/* Need to update reshape_position in metadata */
		mddev->reshape_position = conf->reshape_progress;
		set_mask_bits(&mddev->sb_flags, 0,
			      BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_PENDING));
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		raid10_log(conf->mddev, "wait reshape metadata");
		रुको_event(mddev->sb_रुको,
			   !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags));

		conf->reshape_safe = mddev->reshape_position;
	पूर्ण

	अगर (conf->pending_count >= max_queued_requests) अणु
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		raid10_log(mddev, "wait queued");
		रुको_event(conf->रुको_barrier,
			   conf->pending_count < max_queued_requests);
	पूर्ण
	/* first select target devices under rcu_lock and
	 * inc refcount on their rdev.  Record them by setting
	 * bios[x] to bio
	 * If there are known/acknowledged bad blocks on any device
	 * on which we have seen a ग_लिखो error, we want to aव्योम
	 * writing to those blocks.  This potentially requires several
	 * ग_लिखोs to ग_लिखो around the bad blocks.  Each set of ग_लिखोs
	 * माला_लो its own r10_bio with a set of bios attached.
	 */

	r10_bio->पढ़ो_slot = -1; /* make sure repl_bio माला_लो मुक्तd */
	raid10_find_phys(conf, r10_bio);

	रुको_blocked_dev(mddev, r10_bio);

	rcu_पढ़ो_lock();
	max_sectors = r10_bio->sectors;

	क्रम (i = 0;  i < conf->copies; i++) अणु
		पूर्णांक d = r10_bio->devs[i].devnum;
		काष्ठा md_rdev *rdev = rcu_dereference(conf->mirrors[d].rdev);
		काष्ठा md_rdev *rrdev = rcu_dereference(
			conf->mirrors[d].replacement);
		अगर (rdev == rrdev)
			rrdev = शून्य;
		अगर (rdev && (test_bit(Faulty, &rdev->flags)))
			rdev = शून्य;
		अगर (rrdev && (test_bit(Faulty, &rrdev->flags)))
			rrdev = शून्य;

		r10_bio->devs[i].bio = शून्य;
		r10_bio->devs[i].repl_bio = शून्य;

		अगर (!rdev && !rrdev) अणु
			set_bit(R10BIO_Degraded, &r10_bio->state);
			जारी;
		पूर्ण
		अगर (rdev && test_bit(WriteErrorSeen, &rdev->flags)) अणु
			sector_t first_bad;
			sector_t dev_sector = r10_bio->devs[i].addr;
			पूर्णांक bad_sectors;
			पूर्णांक is_bad;

			is_bad = is_badblock(rdev, dev_sector, max_sectors,
					     &first_bad, &bad_sectors);
			अगर (is_bad && first_bad <= dev_sector) अणु
				/* Cannot ग_लिखो here at all */
				bad_sectors -= (dev_sector - first_bad);
				अगर (bad_sectors < max_sectors)
					/* Mustn't ग_लिखो more than bad_sectors
					 * to other devices yet
					 */
					max_sectors = bad_sectors;
				/* We करोn't set R10BIO_Degraded as that
				 * only applies अगर the disk is missing,
				 * so it might be re-added, and we want to
				 * know to recover this chunk.
				 * In this हाल the device is here, and the
				 * fact that this chunk is not in-sync is
				 * recorded in the bad block log.
				 */
				जारी;
			पूर्ण
			अगर (is_bad) अणु
				पूर्णांक good_sectors = first_bad - dev_sector;
				अगर (good_sectors < max_sectors)
					max_sectors = good_sectors;
			पूर्ण
		पूर्ण
		अगर (rdev) अणु
			r10_bio->devs[i].bio = bio;
			atomic_inc(&rdev->nr_pending);
		पूर्ण
		अगर (rrdev) अणु
			r10_bio->devs[i].repl_bio = bio;
			atomic_inc(&rrdev->nr_pending);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (max_sectors < r10_bio->sectors)
		r10_bio->sectors = max_sectors;

	अगर (r10_bio->sectors < bio_sectors(bio)) अणु
		काष्ठा bio *split = bio_split(bio, r10_bio->sectors,
					      GFP_NOIO, &conf->bio_split);
		bio_chain(split, bio);
		allow_barrier(conf);
		submit_bio_noacct(bio);
		रुको_barrier(conf);
		bio = split;
		r10_bio->master_bio = bio;
	पूर्ण

	atomic_set(&r10_bio->reमुख्यing, 1);
	md_biपंचांगap_startग_लिखो(mddev->biपंचांगap, r10_bio->sector, r10_bio->sectors, 0);

	क्रम (i = 0; i < conf->copies; i++) अणु
		अगर (r10_bio->devs[i].bio)
			raid10_ग_लिखो_one_disk(mddev, r10_bio, bio, false, i);
		अगर (r10_bio->devs[i].repl_bio)
			raid10_ग_लिखो_one_disk(mddev, r10_bio, bio, true, i);
	पूर्ण
	one_ग_लिखो_करोne(r10_bio);
पूर्ण

अटल व्योम __make_request(काष्ठा mddev *mddev, काष्ठा bio *bio, पूर्णांक sectors)
अणु
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा r10bio *r10_bio;

	r10_bio = mempool_alloc(&conf->r10bio_pool, GFP_NOIO);

	r10_bio->master_bio = bio;
	r10_bio->sectors = sectors;

	r10_bio->mddev = mddev;
	r10_bio->sector = bio->bi_iter.bi_sector;
	r10_bio->state = 0;
	r10_bio->पढ़ो_slot = -1;
	स_रखो(r10_bio->devs, 0, माप(r10_bio->devs[0]) *
			conf->geo.raid_disks);

	अगर (bio_data_dir(bio) == READ)
		raid10_पढ़ो_request(mddev, bio, r10_bio);
	अन्यथा
		raid10_ग_लिखो_request(mddev, bio, r10_bio);
पूर्ण

अटल व्योम raid_end_discard_bio(काष्ठा r10bio *r10bio)
अणु
	काष्ठा r10conf *conf = r10bio->mddev->निजी;
	काष्ठा r10bio *first_r10bio;

	जबतक (atomic_dec_and_test(&r10bio->reमुख्यing)) अणु

		allow_barrier(conf);

		अगर (!test_bit(R10BIO_Discard, &r10bio->state)) अणु
			first_r10bio = (काष्ठा r10bio *)r10bio->master_bio;
			मुक्त_r10bio(r10bio);
			r10bio = first_r10bio;
		पूर्ण अन्यथा अणु
			md_ग_लिखो_end(r10bio->mddev);
			bio_endio(r10bio->master_bio);
			मुक्त_r10bio(r10bio);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम raid10_end_discard_request(काष्ठा bio *bio)
अणु
	काष्ठा r10bio *r10_bio = bio->bi_निजी;
	काष्ठा r10conf *conf = r10_bio->mddev->निजी;
	काष्ठा md_rdev *rdev = शून्य;
	पूर्णांक dev;
	पूर्णांक slot, repl;

	/*
	 * We करोn't care the वापस value of discard bio
	 */
	अगर (!test_bit(R10BIO_Uptodate, &r10_bio->state))
		set_bit(R10BIO_Uptodate, &r10_bio->state);

	dev = find_bio_disk(conf, r10_bio, bio, &slot, &repl);
	अगर (repl)
		rdev = conf->mirrors[dev].replacement;
	अगर (!rdev) अणु
		/*
		 * raid10_हटाओ_disk uses smp_mb to make sure rdev is set to
		 * replacement beक्रमe setting replacement to शून्य. It can पढ़ो
		 * rdev first without barrier protect even replacment is शून्य
		 */
		smp_rmb();
		rdev = conf->mirrors[dev].rdev;
	पूर्ण

	raid_end_discard_bio(r10_bio);
	rdev_dec_pending(rdev, conf->mddev);
पूर्ण

/*
 * There are some limitations to handle discard bio
 * 1st, the discard size is bigger than stripe_size*2.
 * 2st, अगर the discard bio spans reshape progress, we use the old way to
 * handle discard bio
 */
अटल पूर्णांक raid10_handle_discard(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा geom *geo = &conf->geo;
	पूर्णांक far_copies = geo->far_copies;
	bool first_copy = true;
	काष्ठा r10bio *r10_bio, *first_r10bio;
	काष्ठा bio *split;
	पूर्णांक disk;
	sector_t chunk;
	अचिन्हित पूर्णांक stripe_size;
	अचिन्हित पूर्णांक stripe_data_disks;
	sector_t split_size;
	sector_t bio_start, bio_end;
	sector_t first_stripe_index, last_stripe_index;
	sector_t start_disk_offset;
	अचिन्हित पूर्णांक start_disk_index;
	sector_t end_disk_offset;
	अचिन्हित पूर्णांक end_disk_index;
	अचिन्हित पूर्णांक reमुख्यder;

	अगर (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery))
		वापस -EAGAIN;

	रुको_barrier(conf);

	/*
	 * Check reshape again to aव्योम reshape happens after checking
	 * MD_RECOVERY_RESHAPE and beक्रमe रुको_barrier
	 */
	अगर (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery))
		जाओ out;

	अगर (geo->near_copies)
		stripe_data_disks = geo->raid_disks / geo->near_copies +
					geo->raid_disks % geo->near_copies;
	अन्यथा
		stripe_data_disks = geo->raid_disks;

	stripe_size = stripe_data_disks << geo->chunk_shअगरt;

	bio_start = bio->bi_iter.bi_sector;
	bio_end = bio_end_sector(bio);

	/*
	 * Maybe one discard bio is smaller than strip size or across one
	 * stripe and discard region is larger than one stripe size. For far
	 * offset layout, अगर the discard region is not aligned with stripe
	 * size, there is hole when we submit discard bio to member disk.
	 * For simplicity, we only handle discard bio which discard region
	 * is bigger than stripe_size * 2
	 */
	अगर (bio_sectors(bio) < stripe_size*2)
		जाओ out;

	/*
	 * Keep bio aligned with strip size.
	 */
	भाग_u64_rem(bio_start, stripe_size, &reमुख्यder);
	अगर (reमुख्यder) अणु
		split_size = stripe_size - reमुख्यder;
		split = bio_split(bio, split_size, GFP_NOIO, &conf->bio_split);
		bio_chain(split, bio);
		allow_barrier(conf);
		/* Resend the fist split part */
		submit_bio_noacct(split);
		रुको_barrier(conf);
	पूर्ण
	भाग_u64_rem(bio_end, stripe_size, &reमुख्यder);
	अगर (reमुख्यder) अणु
		split_size = bio_sectors(bio) - reमुख्यder;
		split = bio_split(bio, split_size, GFP_NOIO, &conf->bio_split);
		bio_chain(split, bio);
		allow_barrier(conf);
		/* Resend the second split part */
		submit_bio_noacct(bio);
		bio = split;
		रुको_barrier(conf);
	पूर्ण

	bio_start = bio->bi_iter.bi_sector;
	bio_end = bio_end_sector(bio);

	/*
	 * Raid10 uses chunk as the unit to store data. It's similar like raid0.
	 * One stripe contains the chunks from all member disk (one chunk from
	 * one disk at the same HBA address). For layout detail, see 'man md 4'
	 */
	chunk = bio_start >> geo->chunk_shअगरt;
	chunk *= geo->near_copies;
	first_stripe_index = chunk;
	start_disk_index = sector_भाग(first_stripe_index, geo->raid_disks);
	अगर (geo->far_offset)
		first_stripe_index *= geo->far_copies;
	start_disk_offset = (bio_start & geo->chunk_mask) +
				(first_stripe_index << geo->chunk_shअगरt);

	chunk = bio_end >> geo->chunk_shअगरt;
	chunk *= geo->near_copies;
	last_stripe_index = chunk;
	end_disk_index = sector_भाग(last_stripe_index, geo->raid_disks);
	अगर (geo->far_offset)
		last_stripe_index *= geo->far_copies;
	end_disk_offset = (bio_end & geo->chunk_mask) +
				(last_stripe_index << geo->chunk_shअगरt);

retry_discard:
	r10_bio = mempool_alloc(&conf->r10bio_pool, GFP_NOIO);
	r10_bio->mddev = mddev;
	r10_bio->state = 0;
	r10_bio->sectors = 0;
	स_रखो(r10_bio->devs, 0, माप(r10_bio->devs[0]) * geo->raid_disks);
	रुको_blocked_dev(mddev, r10_bio);

	/*
	 * For far layout it needs more than one r10bio to cover all regions.
	 * Inspired by raid10_sync_request, we can use the first r10bio->master_bio
	 * to record the discard bio. Other r10bio->master_bio record the first
	 * r10bio. The first r10bio only release after all other r10bios finish.
	 * The discard bio वापसs only first r10bio finishes
	 */
	अगर (first_copy) अणु
		r10_bio->master_bio = bio;
		set_bit(R10BIO_Discard, &r10_bio->state);
		first_copy = false;
		first_r10bio = r10_bio;
	पूर्ण अन्यथा
		r10_bio->master_bio = (काष्ठा bio *)first_r10bio;

	rcu_पढ़ो_lock();
	क्रम (disk = 0; disk < geo->raid_disks; disk++) अणु
		काष्ठा md_rdev *rdev = rcu_dereference(conf->mirrors[disk].rdev);
		काष्ठा md_rdev *rrdev = rcu_dereference(
			conf->mirrors[disk].replacement);

		r10_bio->devs[disk].bio = शून्य;
		r10_bio->devs[disk].repl_bio = शून्य;

		अगर (rdev && (test_bit(Faulty, &rdev->flags)))
			rdev = शून्य;
		अगर (rrdev && (test_bit(Faulty, &rrdev->flags)))
			rrdev = शून्य;
		अगर (!rdev && !rrdev)
			जारी;

		अगर (rdev) अणु
			r10_bio->devs[disk].bio = bio;
			atomic_inc(&rdev->nr_pending);
		पूर्ण
		अगर (rrdev) अणु
			r10_bio->devs[disk].repl_bio = bio;
			atomic_inc(&rrdev->nr_pending);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	atomic_set(&r10_bio->reमुख्यing, 1);
	क्रम (disk = 0; disk < geo->raid_disks; disk++) अणु
		sector_t dev_start, dev_end;
		काष्ठा bio *mbio, *rbio = शून्य;
		काष्ठा md_rdev *rdev = rcu_dereference(conf->mirrors[disk].rdev);
		काष्ठा md_rdev *rrdev = rcu_dereference(
			conf->mirrors[disk].replacement);

		/*
		 * Now start to calculate the start and end address क्रम each disk.
		 * The space between dev_start and dev_end is the discard region.
		 *
		 * For dev_start, it needs to consider three conditions:
		 * 1st, the disk is beक्रमe start_disk, you can imagine the disk in
		 * the next stripe. So the dev_start is the start address of next
		 * stripe.
		 * 2st, the disk is after start_disk, it means the disk is at the
		 * same stripe of first disk
		 * 3st, the first disk itself, we can use start_disk_offset directly
		 */
		अगर (disk < start_disk_index)
			dev_start = (first_stripe_index + 1) * mddev->chunk_sectors;
		अन्यथा अगर (disk > start_disk_index)
			dev_start = first_stripe_index * mddev->chunk_sectors;
		अन्यथा
			dev_start = start_disk_offset;

		अगर (disk < end_disk_index)
			dev_end = (last_stripe_index + 1) * mddev->chunk_sectors;
		अन्यथा अगर (disk > end_disk_index)
			dev_end = last_stripe_index * mddev->chunk_sectors;
		अन्यथा
			dev_end = end_disk_offset;

		/*
		 * It only handles discard bio which size is >= stripe size, so
		 * dev_end > dev_start all the समय
		 */
		अगर (r10_bio->devs[disk].bio) अणु
			mbio = bio_clone_fast(bio, GFP_NOIO, &mddev->bio_set);
			mbio->bi_end_io = raid10_end_discard_request;
			mbio->bi_निजी = r10_bio;
			r10_bio->devs[disk].bio = mbio;
			r10_bio->devs[disk].devnum = disk;
			atomic_inc(&r10_bio->reमुख्यing);
			md_submit_discard_bio(mddev, rdev, mbio,
					dev_start + choose_data_offset(r10_bio, rdev),
					dev_end - dev_start);
			bio_endio(mbio);
		पूर्ण
		अगर (r10_bio->devs[disk].repl_bio) अणु
			rbio = bio_clone_fast(bio, GFP_NOIO, &mddev->bio_set);
			rbio->bi_end_io = raid10_end_discard_request;
			rbio->bi_निजी = r10_bio;
			r10_bio->devs[disk].repl_bio = rbio;
			r10_bio->devs[disk].devnum = disk;
			atomic_inc(&r10_bio->reमुख्यing);
			md_submit_discard_bio(mddev, rrdev, rbio,
					dev_start + choose_data_offset(r10_bio, rrdev),
					dev_end - dev_start);
			bio_endio(rbio);
		पूर्ण
	पूर्ण

	अगर (!geo->far_offset && --far_copies) अणु
		first_stripe_index += geo->stride >> geo->chunk_shअगरt;
		start_disk_offset += geo->stride;
		last_stripe_index += geo->stride >> geo->chunk_shअगरt;
		end_disk_offset += geo->stride;
		atomic_inc(&first_r10bio->reमुख्यing);
		raid_end_discard_bio(r10_bio);
		रुको_barrier(conf);
		जाओ retry_discard;
	पूर्ण

	raid_end_discard_bio(r10_bio);

	वापस 0;
out:
	allow_barrier(conf);
	वापस -EAGAIN;
पूर्ण

अटल bool raid10_make_request(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	काष्ठा r10conf *conf = mddev->निजी;
	sector_t chunk_mask = (conf->geo.chunk_mask & conf->prev.chunk_mask);
	पूर्णांक chunk_sects = chunk_mask + 1;
	पूर्णांक sectors = bio_sectors(bio);

	अगर (unlikely(bio->bi_opf & REQ_PREFLUSH)
	    && md_flush_request(mddev, bio))
		वापस true;

	अगर (!md_ग_लिखो_start(mddev, bio))
		वापस false;

	अगर (unlikely(bio_op(bio) == REQ_OP_DISCARD))
		अगर (!raid10_handle_discard(mddev, bio))
			वापस true;

	/*
	 * If this request crosses a chunk boundary, we need to split
	 * it.
	 */
	अगर (unlikely((bio->bi_iter.bi_sector & chunk_mask) +
		     sectors > chunk_sects
		     && (conf->geo.near_copies < conf->geo.raid_disks
			 || conf->prev.near_copies <
			 conf->prev.raid_disks)))
		sectors = chunk_sects -
			(bio->bi_iter.bi_sector &
			 (chunk_sects - 1));
	__make_request(mddev, bio, sectors);

	/* In हाल raid10d snuck in to मुक्तze_array */
	wake_up(&conf->रुको_barrier);
	वापस true;
पूर्ण

अटल व्योम raid10_status(काष्ठा seq_file *seq, काष्ठा mddev *mddev)
अणु
	काष्ठा r10conf *conf = mddev->निजी;
	पूर्णांक i;

	अगर (conf->geo.near_copies < conf->geo.raid_disks)
		seq_म_लिखो(seq, " %dK chunks", mddev->chunk_sectors / 2);
	अगर (conf->geo.near_copies > 1)
		seq_म_लिखो(seq, " %d near-copies", conf->geo.near_copies);
	अगर (conf->geo.far_copies > 1) अणु
		अगर (conf->geo.far_offset)
			seq_म_लिखो(seq, " %d offset-copies", conf->geo.far_copies);
		अन्यथा
			seq_म_लिखो(seq, " %d far-copies", conf->geo.far_copies);
		अगर (conf->geo.far_set_size != conf->geo.raid_disks)
			seq_म_लिखो(seq, " %d devices per set", conf->geo.far_set_size);
	पूर्ण
	seq_म_लिखो(seq, " [%d/%d] [", conf->geo.raid_disks,
					conf->geo.raid_disks - mddev->degraded);
	rcu_पढ़ो_lock();
	क्रम (i = 0; i < conf->geo.raid_disks; i++) अणु
		काष्ठा md_rdev *rdev = rcu_dereference(conf->mirrors[i].rdev);
		seq_म_लिखो(seq, "%s", rdev && test_bit(In_sync, &rdev->flags) ? "U" : "_");
	पूर्ण
	rcu_पढ़ो_unlock();
	seq_म_लिखो(seq, "]");
पूर्ण

/* check अगर there are enough drives क्रम
 * every block to appear on atleast one.
 * Don't consider the device numbered 'ignore'
 * as we might be about to हटाओ it.
 */
अटल पूर्णांक _enough(काष्ठा r10conf *conf, पूर्णांक previous, पूर्णांक ignore)
अणु
	पूर्णांक first = 0;
	पूर्णांक has_enough = 0;
	पूर्णांक disks, ncopies;
	अगर (previous) अणु
		disks = conf->prev.raid_disks;
		ncopies = conf->prev.near_copies;
	पूर्ण अन्यथा अणु
		disks = conf->geo.raid_disks;
		ncopies = conf->geo.near_copies;
	पूर्ण

	rcu_पढ़ो_lock();
	करो अणु
		पूर्णांक n = conf->copies;
		पूर्णांक cnt = 0;
		पूर्णांक this = first;
		जबतक (n--) अणु
			काष्ठा md_rdev *rdev;
			अगर (this != ignore &&
			    (rdev = rcu_dereference(conf->mirrors[this].rdev)) &&
			    test_bit(In_sync, &rdev->flags))
				cnt++;
			this = (this+1) % disks;
		पूर्ण
		अगर (cnt == 0)
			जाओ out;
		first = (first + ncopies) % disks;
	पूर्ण जबतक (first != 0);
	has_enough = 1;
out:
	rcu_पढ़ो_unlock();
	वापस has_enough;
पूर्ण

अटल पूर्णांक enough(काष्ठा r10conf *conf, पूर्णांक ignore)
अणु
	/* when calling 'enough', both 'prev' and 'geo' must
	 * be stable.
	 * This is ensured अगर ->reconfig_mutex or ->device_lock
	 * is held.
	 */
	वापस _enough(conf, 0, ignore) &&
		_enough(conf, 1, ignore);
पूर्ण

अटल व्योम raid10_error(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	अक्षर b[BDEVNAME_SIZE];
	काष्ठा r10conf *conf = mddev->निजी;
	अचिन्हित दीर्घ flags;

	/*
	 * If it is not operational, then we have alपढ़ोy marked it as dead
	 * अन्यथा अगर it is the last working disks with "fail_last_dev == false",
	 * ignore the error, let the next level up know.
	 * अन्यथा mark the drive as failed
	 */
	spin_lock_irqsave(&conf->device_lock, flags);
	अगर (test_bit(In_sync, &rdev->flags) && !mddev->fail_last_dev
	    && !enough(conf, rdev->raid_disk)) अणु
		/*
		 * Don't fail the drive, just वापस an IO error.
		 */
		spin_unlock_irqrestore(&conf->device_lock, flags);
		वापस;
	पूर्ण
	अगर (test_and_clear_bit(In_sync, &rdev->flags))
		mddev->degraded++;
	/*
	 * If recovery is running, make sure it पातs.
	 */
	set_bit(MD_RECOVERY_INTR, &mddev->recovery);
	set_bit(Blocked, &rdev->flags);
	set_bit(Faulty, &rdev->flags);
	set_mask_bits(&mddev->sb_flags, 0,
		      BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_PENDING));
	spin_unlock_irqrestore(&conf->device_lock, flags);
	pr_crit("md/raid10:%s: Disk failure on %s, disabling device.\n"
		"md/raid10:%s: Operation continuing on %d devices.\n",
		mdname(mddev), bdevname(rdev->bdev, b),
		mdname(mddev), conf->geo.raid_disks - mddev->degraded);
पूर्ण

अटल व्योम prपूर्णांक_conf(काष्ठा r10conf *conf)
अणु
	पूर्णांक i;
	काष्ठा md_rdev *rdev;

	pr_debug("RAID10 conf printout:\n");
	अगर (!conf) अणु
		pr_debug("(!conf)\n");
		वापस;
	पूर्ण
	pr_debug(" --- wd:%d rd:%d\n", conf->geo.raid_disks - conf->mddev->degraded,
		 conf->geo.raid_disks);

	/* This is only called with ->reconfix_mutex held, so
	 * rcu protection of rdev is not needed */
	क्रम (i = 0; i < conf->geo.raid_disks; i++) अणु
		अक्षर b[BDEVNAME_SIZE];
		rdev = conf->mirrors[i].rdev;
		अगर (rdev)
			pr_debug(" disk %d, wo:%d, o:%d, dev:%s\n",
				 i, !test_bit(In_sync, &rdev->flags),
				 !test_bit(Faulty, &rdev->flags),
				 bdevname(rdev->bdev,b));
	पूर्ण
पूर्ण

अटल व्योम बंद_sync(काष्ठा r10conf *conf)
अणु
	रुको_barrier(conf);
	allow_barrier(conf);

	mempool_निकास(&conf->r10buf_pool);
पूर्ण

अटल पूर्णांक raid10_spare_active(काष्ठा mddev *mddev)
अणु
	पूर्णांक i;
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा raid10_info *पंचांगp;
	पूर्णांक count = 0;
	अचिन्हित दीर्घ flags;

	/*
	 * Find all non-in_sync disks within the RAID10 configuration
	 * and mark them in_sync
	 */
	क्रम (i = 0; i < conf->geo.raid_disks; i++) अणु
		पंचांगp = conf->mirrors + i;
		अगर (पंचांगp->replacement
		    && पंचांगp->replacement->recovery_offset == MaxSector
		    && !test_bit(Faulty, &पंचांगp->replacement->flags)
		    && !test_and_set_bit(In_sync, &पंचांगp->replacement->flags)) अणु
			/* Replacement has just become active */
			अगर (!पंचांगp->rdev
			    || !test_and_clear_bit(In_sync, &पंचांगp->rdev->flags))
				count++;
			अगर (पंचांगp->rdev) अणु
				/* Replaced device not technically faulty,
				 * but we need to be sure it माला_लो हटाओd
				 * and never re-added.
				 */
				set_bit(Faulty, &पंचांगp->rdev->flags);
				sysfs_notअगरy_dirent_safe(
					पंचांगp->rdev->sysfs_state);
			पूर्ण
			sysfs_notअगरy_dirent_safe(पंचांगp->replacement->sysfs_state);
		पूर्ण अन्यथा अगर (पंचांगp->rdev
			   && पंचांगp->rdev->recovery_offset == MaxSector
			   && !test_bit(Faulty, &पंचांगp->rdev->flags)
			   && !test_and_set_bit(In_sync, &पंचांगp->rdev->flags)) अणु
			count++;
			sysfs_notअगरy_dirent_safe(पंचांगp->rdev->sysfs_state);
		पूर्ण
	पूर्ण
	spin_lock_irqsave(&conf->device_lock, flags);
	mddev->degraded -= count;
	spin_unlock_irqrestore(&conf->device_lock, flags);

	prपूर्णांक_conf(conf);
	वापस count;
पूर्ण

अटल पूर्णांक raid10_add_disk(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा r10conf *conf = mddev->निजी;
	पूर्णांक err = -EEXIST;
	पूर्णांक mirror;
	पूर्णांक first = 0;
	पूर्णांक last = conf->geo.raid_disks - 1;

	अगर (mddev->recovery_cp < MaxSector)
		/* only hot-add to in-sync arrays, as recovery is
		 * very dअगरferent from resync
		 */
		वापस -EBUSY;
	अगर (rdev->saved_raid_disk < 0 && !_enough(conf, 1, -1))
		वापस -EINVAL;

	अगर (md_पूर्णांकegrity_add_rdev(rdev, mddev))
		वापस -ENXIO;

	अगर (rdev->raid_disk >= 0)
		first = last = rdev->raid_disk;

	अगर (rdev->saved_raid_disk >= first &&
	    rdev->saved_raid_disk < conf->geo.raid_disks &&
	    conf->mirrors[rdev->saved_raid_disk].rdev == शून्य)
		mirror = rdev->saved_raid_disk;
	अन्यथा
		mirror = first;
	क्रम ( ; mirror <= last ; mirror++) अणु
		काष्ठा raid10_info *p = &conf->mirrors[mirror];
		अगर (p->recovery_disabled == mddev->recovery_disabled)
			जारी;
		अगर (p->rdev) अणु
			अगर (!test_bit(WantReplacement, &p->rdev->flags) ||
			    p->replacement != शून्य)
				जारी;
			clear_bit(In_sync, &rdev->flags);
			set_bit(Replacement, &rdev->flags);
			rdev->raid_disk = mirror;
			err = 0;
			अगर (mddev->gendisk)
				disk_stack_limits(mddev->gendisk, rdev->bdev,
						  rdev->data_offset << 9);
			conf->fullsync = 1;
			rcu_assign_poपूर्णांकer(p->replacement, rdev);
			अवरोध;
		पूर्ण

		अगर (mddev->gendisk)
			disk_stack_limits(mddev->gendisk, rdev->bdev,
					  rdev->data_offset << 9);

		p->head_position = 0;
		p->recovery_disabled = mddev->recovery_disabled - 1;
		rdev->raid_disk = mirror;
		err = 0;
		अगर (rdev->saved_raid_disk != mirror)
			conf->fullsync = 1;
		rcu_assign_poपूर्णांकer(p->rdev, rdev);
		अवरोध;
	पूर्ण
	अगर (mddev->queue && blk_queue_discard(bdev_get_queue(rdev->bdev)))
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, mddev->queue);

	prपूर्णांक_conf(conf);
	वापस err;
पूर्ण

अटल पूर्णांक raid10_हटाओ_disk(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा r10conf *conf = mddev->निजी;
	पूर्णांक err = 0;
	पूर्णांक number = rdev->raid_disk;
	काष्ठा md_rdev **rdevp;
	काष्ठा raid10_info *p = conf->mirrors + number;

	prपूर्णांक_conf(conf);
	अगर (rdev == p->rdev)
		rdevp = &p->rdev;
	अन्यथा अगर (rdev == p->replacement)
		rdevp = &p->replacement;
	अन्यथा
		वापस 0;

	अगर (test_bit(In_sync, &rdev->flags) ||
	    atomic_पढ़ो(&rdev->nr_pending)) अणु
		err = -EBUSY;
		जाओ पात;
	पूर्ण
	/* Only हटाओ non-faulty devices अगर recovery
	 * is not possible.
	 */
	अगर (!test_bit(Faulty, &rdev->flags) &&
	    mddev->recovery_disabled != p->recovery_disabled &&
	    (!p->replacement || p->replacement == rdev) &&
	    number < conf->geo.raid_disks &&
	    enough(conf, -1)) अणु
		err = -EBUSY;
		जाओ पात;
	पूर्ण
	*rdevp = शून्य;
	अगर (!test_bit(RemoveSynchronized, &rdev->flags)) अणु
		synchronize_rcu();
		अगर (atomic_पढ़ो(&rdev->nr_pending)) अणु
			/* lost the race, try later */
			err = -EBUSY;
			*rdevp = rdev;
			जाओ पात;
		पूर्ण
	पूर्ण
	अगर (p->replacement) अणु
		/* We must have just cleared 'rdev' */
		p->rdev = p->replacement;
		clear_bit(Replacement, &p->replacement->flags);
		smp_mb(); /* Make sure other CPUs may see both as identical
			   * but will never see neither -- अगर they are careful.
			   */
		p->replacement = शून्य;
	पूर्ण

	clear_bit(WantReplacement, &rdev->flags);
	err = md_पूर्णांकegrity_रेजिस्टर(mddev);

पात:

	prपूर्णांक_conf(conf);
	वापस err;
पूर्ण

अटल व्योम __end_sync_पढ़ो(काष्ठा r10bio *r10_bio, काष्ठा bio *bio, पूर्णांक d)
अणु
	काष्ठा r10conf *conf = r10_bio->mddev->निजी;

	अगर (!bio->bi_status)
		set_bit(R10BIO_Uptodate, &r10_bio->state);
	अन्यथा
		/* The ग_लिखो handler will notice the lack of
		 * R10BIO_Uptodate and record any errors etc
		 */
		atomic_add(r10_bio->sectors,
			   &conf->mirrors[d].rdev->corrected_errors);

	/* क्रम reस्थिरruct, we always reschedule after a पढ़ो.
	 * क्रम resync, only after all पढ़ोs
	 */
	rdev_dec_pending(conf->mirrors[d].rdev, conf->mddev);
	अगर (test_bit(R10BIO_IsRecover, &r10_bio->state) ||
	    atomic_dec_and_test(&r10_bio->reमुख्यing)) अणु
		/* we have पढ़ो all the blocks,
		 * करो the comparison in process context in raid10d
		 */
		reschedule_retry(r10_bio);
	पूर्ण
पूर्ण

अटल व्योम end_sync_पढ़ो(काष्ठा bio *bio)
अणु
	काष्ठा r10bio *r10_bio = get_resync_r10bio(bio);
	काष्ठा r10conf *conf = r10_bio->mddev->निजी;
	पूर्णांक d = find_bio_disk(conf, r10_bio, bio, शून्य, शून्य);

	__end_sync_पढ़ो(r10_bio, bio, d);
पूर्ण

अटल व्योम end_reshape_पढ़ो(काष्ठा bio *bio)
अणु
	/* reshape पढ़ो bio isn't allocated from r10buf_pool */
	काष्ठा r10bio *r10_bio = bio->bi_निजी;

	__end_sync_पढ़ो(r10_bio, bio, r10_bio->पढ़ो_slot);
पूर्ण

अटल व्योम end_sync_request(काष्ठा r10bio *r10_bio)
अणु
	काष्ठा mddev *mddev = r10_bio->mddev;

	जबतक (atomic_dec_and_test(&r10_bio->reमुख्यing)) अणु
		अगर (r10_bio->master_bio == शून्य) अणु
			/* the primary of several recovery bios */
			sector_t s = r10_bio->sectors;
			अगर (test_bit(R10BIO_MadeGood, &r10_bio->state) ||
			    test_bit(R10BIO_WriteError, &r10_bio->state))
				reschedule_retry(r10_bio);
			अन्यथा
				put_buf(r10_bio);
			md_करोne_sync(mddev, s, 1);
			अवरोध;
		पूर्ण अन्यथा अणु
			काष्ठा r10bio *r10_bio2 = (काष्ठा r10bio *)r10_bio->master_bio;
			अगर (test_bit(R10BIO_MadeGood, &r10_bio->state) ||
			    test_bit(R10BIO_WriteError, &r10_bio->state))
				reschedule_retry(r10_bio);
			अन्यथा
				put_buf(r10_bio);
			r10_bio = r10_bio2;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम end_sync_ग_लिखो(काष्ठा bio *bio)
अणु
	काष्ठा r10bio *r10_bio = get_resync_r10bio(bio);
	काष्ठा mddev *mddev = r10_bio->mddev;
	काष्ठा r10conf *conf = mddev->निजी;
	पूर्णांक d;
	sector_t first_bad;
	पूर्णांक bad_sectors;
	पूर्णांक slot;
	पूर्णांक repl;
	काष्ठा md_rdev *rdev = शून्य;

	d = find_bio_disk(conf, r10_bio, bio, &slot, &repl);
	अगर (repl)
		rdev = conf->mirrors[d].replacement;
	अन्यथा
		rdev = conf->mirrors[d].rdev;

	अगर (bio->bi_status) अणु
		अगर (repl)
			md_error(mddev, rdev);
		अन्यथा अणु
			set_bit(WriteErrorSeen, &rdev->flags);
			अगर (!test_and_set_bit(WantReplacement, &rdev->flags))
				set_bit(MD_RECOVERY_NEEDED,
					&rdev->mddev->recovery);
			set_bit(R10BIO_WriteError, &r10_bio->state);
		पूर्ण
	पूर्ण अन्यथा अगर (is_badblock(rdev,
			     r10_bio->devs[slot].addr,
			     r10_bio->sectors,
			     &first_bad, &bad_sectors))
		set_bit(R10BIO_MadeGood, &r10_bio->state);

	rdev_dec_pending(rdev, mddev);

	end_sync_request(r10_bio);
पूर्ण

/*
 * Note: sync and recover and handled very dअगरferently क्रम raid10
 * This code is क्रम resync.
 * For resync, we पढ़ो through भव addresses and पढ़ो all blocks.
 * If there is any error, we schedule a ग_लिखो.  The lowest numbered
 * drive is authoritative.
 * However requests come क्रम physical address, so we need to map.
 * For every physical address there are raid_disks/copies भव addresses,
 * which is always are least one, but is not necessarly an पूर्णांकeger.
 * This means that a physical address can span multiple chunks, so we may
 * have to submit multiple io requests क्रम a single sync request.
 */
/*
 * We check अगर all blocks are in-sync and only ग_लिखो to blocks that
 * aren't in sync
 */
अटल व्योम sync_request_ग_लिखो(काष्ठा mddev *mddev, काष्ठा r10bio *r10_bio)
अणु
	काष्ठा r10conf *conf = mddev->निजी;
	पूर्णांक i, first;
	काष्ठा bio *tbio, *fbio;
	पूर्णांक vcnt;
	काष्ठा page **tpages, **fpages;

	atomic_set(&r10_bio->reमुख्यing, 1);

	/* find the first device with a block */
	क्रम (i=0; i<conf->copies; i++)
		अगर (!r10_bio->devs[i].bio->bi_status)
			अवरोध;

	अगर (i == conf->copies)
		जाओ करोne;

	first = i;
	fbio = r10_bio->devs[i].bio;
	fbio->bi_iter.bi_size = r10_bio->sectors << 9;
	fbio->bi_iter.bi_idx = 0;
	fpages = get_resync_pages(fbio)->pages;

	vcnt = (r10_bio->sectors + (PAGE_SIZE >> 9) - 1) >> (PAGE_SHIFT - 9);
	/* now find blocks with errors */
	क्रम (i=0 ; i < conf->copies ; i++) अणु
		पूर्णांक  j, d;
		काष्ठा md_rdev *rdev;
		काष्ठा resync_pages *rp;

		tbio = r10_bio->devs[i].bio;

		अगर (tbio->bi_end_io != end_sync_पढ़ो)
			जारी;
		अगर (i == first)
			जारी;

		tpages = get_resync_pages(tbio)->pages;
		d = r10_bio->devs[i].devnum;
		rdev = conf->mirrors[d].rdev;
		अगर (!r10_bio->devs[i].bio->bi_status) अणु
			/* We know that the bi_io_vec layout is the same क्रम
			 * both 'first' and 'i', so we just compare them.
			 * All vec entries are PAGE_SIZE;
			 */
			पूर्णांक sectors = r10_bio->sectors;
			क्रम (j = 0; j < vcnt; j++) अणु
				पूर्णांक len = PAGE_SIZE;
				अगर (sectors < (len / 512))
					len = sectors * 512;
				अगर (स_भेद(page_address(fpages[j]),
					   page_address(tpages[j]),
					   len))
					अवरोध;
				sectors -= len/512;
			पूर्ण
			अगर (j == vcnt)
				जारी;
			atomic64_add(r10_bio->sectors, &mddev->resync_mismatches);
			अगर (test_bit(MD_RECOVERY_CHECK, &mddev->recovery))
				/* Don't fix anything. */
				जारी;
		पूर्ण अन्यथा अगर (test_bit(FailFast, &rdev->flags)) अणु
			/* Just give up on this device */
			md_error(rdev->mddev, rdev);
			जारी;
		पूर्ण
		/* Ok, we need to ग_लिखो this bio, either to correct an
		 * inconsistency or to correct an unपढ़ोable block.
		 * First we need to fixup bv_offset, bv_len and
		 * bi_vecs, as the पढ़ो request might have corrupted these
		 */
		rp = get_resync_pages(tbio);
		bio_reset(tbio);

		md_bio_reset_resync_pages(tbio, rp, fbio->bi_iter.bi_size);

		rp->raid_bio = r10_bio;
		tbio->bi_निजी = rp;
		tbio->bi_iter.bi_sector = r10_bio->devs[i].addr;
		tbio->bi_end_io = end_sync_ग_लिखो;
		bio_set_op_attrs(tbio, REQ_OP_WRITE, 0);

		bio_copy_data(tbio, fbio);

		atomic_inc(&conf->mirrors[d].rdev->nr_pending);
		atomic_inc(&r10_bio->reमुख्यing);
		md_sync_acct(conf->mirrors[d].rdev->bdev, bio_sectors(tbio));

		अगर (test_bit(FailFast, &conf->mirrors[d].rdev->flags))
			tbio->bi_opf |= MD_FAILFAST;
		tbio->bi_iter.bi_sector += conf->mirrors[d].rdev->data_offset;
		bio_set_dev(tbio, conf->mirrors[d].rdev->bdev);
		submit_bio_noacct(tbio);
	पूर्ण

	/* Now ग_लिखो out to any replacement devices
	 * that are active
	 */
	क्रम (i = 0; i < conf->copies; i++) अणु
		पूर्णांक d;

		tbio = r10_bio->devs[i].repl_bio;
		अगर (!tbio || !tbio->bi_end_io)
			जारी;
		अगर (r10_bio->devs[i].bio->bi_end_io != end_sync_ग_लिखो
		    && r10_bio->devs[i].bio != fbio)
			bio_copy_data(tbio, fbio);
		d = r10_bio->devs[i].devnum;
		atomic_inc(&r10_bio->reमुख्यing);
		md_sync_acct(conf->mirrors[d].replacement->bdev,
			     bio_sectors(tbio));
		submit_bio_noacct(tbio);
	पूर्ण

करोne:
	अगर (atomic_dec_and_test(&r10_bio->reमुख्यing)) अणु
		md_करोne_sync(mddev, r10_bio->sectors, 1);
		put_buf(r10_bio);
	पूर्ण
पूर्ण

/*
 * Now क्रम the recovery code.
 * Recovery happens across physical sectors.
 * We recover all non-is_sync drives by finding the भव address of
 * each, and then choose a working drive that also has that virt address.
 * There is a separate r10_bio क्रम each non-in_sync drive.
 * Only the first two slots are in use. The first क्रम पढ़ोing,
 * The second क्रम writing.
 *
 */
अटल व्योम fix_recovery_पढ़ो_error(काष्ठा r10bio *r10_bio)
अणु
	/* We got a पढ़ो error during recovery.
	 * We repeat the पढ़ो in smaller page-sized sections.
	 * If a पढ़ो succeeds, ग_लिखो it to the new device or record
	 * a bad block अगर we cannot.
	 * If a पढ़ो fails, record a bad block on both old and
	 * new devices.
	 */
	काष्ठा mddev *mddev = r10_bio->mddev;
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा bio *bio = r10_bio->devs[0].bio;
	sector_t sect = 0;
	पूर्णांक sectors = r10_bio->sectors;
	पूर्णांक idx = 0;
	पूर्णांक dr = r10_bio->devs[0].devnum;
	पूर्णांक dw = r10_bio->devs[1].devnum;
	काष्ठा page **pages = get_resync_pages(bio)->pages;

	जबतक (sectors) अणु
		पूर्णांक s = sectors;
		काष्ठा md_rdev *rdev;
		sector_t addr;
		पूर्णांक ok;

		अगर (s > (PAGE_SIZE>>9))
			s = PAGE_SIZE >> 9;

		rdev = conf->mirrors[dr].rdev;
		addr = r10_bio->devs[0].addr + sect,
		ok = sync_page_io(rdev,
				  addr,
				  s << 9,
				  pages[idx],
				  REQ_OP_READ, 0, false);
		अगर (ok) अणु
			rdev = conf->mirrors[dw].rdev;
			addr = r10_bio->devs[1].addr + sect;
			ok = sync_page_io(rdev,
					  addr,
					  s << 9,
					  pages[idx],
					  REQ_OP_WRITE, 0, false);
			अगर (!ok) अणु
				set_bit(WriteErrorSeen, &rdev->flags);
				अगर (!test_and_set_bit(WantReplacement,
						      &rdev->flags))
					set_bit(MD_RECOVERY_NEEDED,
						&rdev->mddev->recovery);
			पूर्ण
		पूर्ण
		अगर (!ok) अणु
			/* We करोn't worry अगर we cannot set a bad block -
			 * it really is bad so there is no loss in not
			 * recording it yet
			 */
			rdev_set_badblocks(rdev, addr, s, 0);

			अगर (rdev != conf->mirrors[dw].rdev) अणु
				/* need bad block on destination too */
				काष्ठा md_rdev *rdev2 = conf->mirrors[dw].rdev;
				addr = r10_bio->devs[1].addr + sect;
				ok = rdev_set_badblocks(rdev2, addr, s, 0);
				अगर (!ok) अणु
					/* just पात the recovery */
					pr_notice("md/raid10:%s: recovery aborted due to read error\n",
						  mdname(mddev));

					conf->mirrors[dw].recovery_disabled
						= mddev->recovery_disabled;
					set_bit(MD_RECOVERY_INTR,
						&mddev->recovery);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		sectors -= s;
		sect += s;
		idx++;
	पूर्ण
पूर्ण

अटल व्योम recovery_request_ग_लिखो(काष्ठा mddev *mddev, काष्ठा r10bio *r10_bio)
अणु
	काष्ठा r10conf *conf = mddev->निजी;
	पूर्णांक d;
	काष्ठा bio *wbio, *wbio2;

	अगर (!test_bit(R10BIO_Uptodate, &r10_bio->state)) अणु
		fix_recovery_पढ़ो_error(r10_bio);
		end_sync_request(r10_bio);
		वापस;
	पूर्ण

	/*
	 * share the pages with the first bio
	 * and submit the ग_लिखो request
	 */
	d = r10_bio->devs[1].devnum;
	wbio = r10_bio->devs[1].bio;
	wbio2 = r10_bio->devs[1].repl_bio;
	/* Need to test wbio2->bi_end_io beक्रमe we call
	 * submit_bio_noacct as अगर the क्रमmer is शून्य,
	 * the latter is मुक्त to मुक्त wbio2.
	 */
	अगर (wbio2 && !wbio2->bi_end_io)
		wbio2 = शून्य;
	अगर (wbio->bi_end_io) अणु
		atomic_inc(&conf->mirrors[d].rdev->nr_pending);
		md_sync_acct(conf->mirrors[d].rdev->bdev, bio_sectors(wbio));
		submit_bio_noacct(wbio);
	पूर्ण
	अगर (wbio2) अणु
		atomic_inc(&conf->mirrors[d].replacement->nr_pending);
		md_sync_acct(conf->mirrors[d].replacement->bdev,
			     bio_sectors(wbio2));
		submit_bio_noacct(wbio2);
	पूर्ण
पूर्ण

/*
 * Used by fix_पढ़ो_error() to decay the per rdev पढ़ो_errors.
 * We halve the पढ़ो error count क्रम every hour that has elapsed
 * since the last recorded पढ़ो error.
 *
 */
अटल व्योम check_decay_पढ़ो_errors(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	दीर्घ cur_समय_mon;
	अचिन्हित दीर्घ hours_since_last;
	अचिन्हित पूर्णांक पढ़ो_errors = atomic_पढ़ो(&rdev->पढ़ो_errors);

	cur_समय_mon = kसमय_get_seconds();

	अगर (rdev->last_पढ़ो_error == 0) अणु
		/* first समय we've seen a पढ़ो error */
		rdev->last_पढ़ो_error = cur_समय_mon;
		वापस;
	पूर्ण

	hours_since_last = (दीर्घ)(cur_समय_mon -
			    rdev->last_पढ़ो_error) / 3600;

	rdev->last_पढ़ो_error = cur_समय_mon;

	/*
	 * अगर hours_since_last is > the number of bits in पढ़ो_errors
	 * just set पढ़ो errors to 0. We करो this to aव्योम
	 * overflowing the shअगरt of पढ़ो_errors by hours_since_last.
	 */
	अगर (hours_since_last >= 8 * माप(पढ़ो_errors))
		atomic_set(&rdev->पढ़ो_errors, 0);
	अन्यथा
		atomic_set(&rdev->पढ़ो_errors, पढ़ो_errors >> hours_since_last);
पूर्ण

अटल पूर्णांक r10_sync_page_io(काष्ठा md_rdev *rdev, sector_t sector,
			    पूर्णांक sectors, काष्ठा page *page, पूर्णांक rw)
अणु
	sector_t first_bad;
	पूर्णांक bad_sectors;

	अगर (is_badblock(rdev, sector, sectors, &first_bad, &bad_sectors)
	    && (rw == READ || test_bit(WriteErrorSeen, &rdev->flags)))
		वापस -1;
	अगर (sync_page_io(rdev, sector, sectors << 9, page, rw, 0, false))
		/* success */
		वापस 1;
	अगर (rw == WRITE) अणु
		set_bit(WriteErrorSeen, &rdev->flags);
		अगर (!test_and_set_bit(WantReplacement, &rdev->flags))
			set_bit(MD_RECOVERY_NEEDED,
				&rdev->mddev->recovery);
	पूर्ण
	/* need to record an error - either क्रम the block or the device */
	अगर (!rdev_set_badblocks(rdev, sector, sectors, 0))
		md_error(rdev->mddev, rdev);
	वापस 0;
पूर्ण

/*
 * This is a kernel thपढ़ो which:
 *
 *	1.	Retries failed पढ़ो operations on working mirrors.
 *	2.	Updates the raid superblock when problems encounter.
 *	3.	Perक्रमms ग_लिखोs following पढ़ोs क्रम array synchronising.
 */

अटल व्योम fix_पढ़ो_error(काष्ठा r10conf *conf, काष्ठा mddev *mddev, काष्ठा r10bio *r10_bio)
अणु
	पूर्णांक sect = 0; /* Offset from r10_bio->sector */
	पूर्णांक sectors = r10_bio->sectors;
	काष्ठा md_rdev *rdev;
	पूर्णांक max_पढ़ो_errors = atomic_पढ़ो(&mddev->max_corr_पढ़ो_errors);
	पूर्णांक d = r10_bio->devs[r10_bio->पढ़ो_slot].devnum;

	/* still own a reference to this rdev, so it cannot
	 * have been cleared recently.
	 */
	rdev = conf->mirrors[d].rdev;

	अगर (test_bit(Faulty, &rdev->flags))
		/* drive has alपढ़ोy been failed, just ignore any
		   more fix_पढ़ो_error() attempts */
		वापस;

	check_decay_पढ़ो_errors(mddev, rdev);
	atomic_inc(&rdev->पढ़ो_errors);
	अगर (atomic_पढ़ो(&rdev->पढ़ो_errors) > max_पढ़ो_errors) अणु
		अक्षर b[BDEVNAME_SIZE];
		bdevname(rdev->bdev, b);

		pr_notice("md/raid10:%s: %s: Raid device exceeded read_error threshold [cur %d:max %d]\n",
			  mdname(mddev), b,
			  atomic_पढ़ो(&rdev->पढ़ो_errors), max_पढ़ो_errors);
		pr_notice("md/raid10:%s: %s: Failing raid device\n",
			  mdname(mddev), b);
		md_error(mddev, rdev);
		r10_bio->devs[r10_bio->पढ़ो_slot].bio = IO_BLOCKED;
		वापस;
	पूर्ण

	जबतक(sectors) अणु
		पूर्णांक s = sectors;
		पूर्णांक sl = r10_bio->पढ़ो_slot;
		पूर्णांक success = 0;
		पूर्णांक start;

		अगर (s > (PAGE_SIZE>>9))
			s = PAGE_SIZE >> 9;

		rcu_पढ़ो_lock();
		करो अणु
			sector_t first_bad;
			पूर्णांक bad_sectors;

			d = r10_bio->devs[sl].devnum;
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			अगर (rdev &&
			    test_bit(In_sync, &rdev->flags) &&
			    !test_bit(Faulty, &rdev->flags) &&
			    is_badblock(rdev, r10_bio->devs[sl].addr + sect, s,
					&first_bad, &bad_sectors) == 0) अणु
				atomic_inc(&rdev->nr_pending);
				rcu_पढ़ो_unlock();
				success = sync_page_io(rdev,
						       r10_bio->devs[sl].addr +
						       sect,
						       s<<9,
						       conf->पंचांगppage,
						       REQ_OP_READ, 0, false);
				rdev_dec_pending(rdev, mddev);
				rcu_पढ़ो_lock();
				अगर (success)
					अवरोध;
			पूर्ण
			sl++;
			अगर (sl == conf->copies)
				sl = 0;
		पूर्ण जबतक (!success && sl != r10_bio->पढ़ो_slot);
		rcu_पढ़ो_unlock();

		अगर (!success) अणु
			/* Cannot पढ़ो from anywhere, just mark the block
			 * as bad on the first device to discourage future
			 * पढ़ोs.
			 */
			पूर्णांक dn = r10_bio->devs[r10_bio->पढ़ो_slot].devnum;
			rdev = conf->mirrors[dn].rdev;

			अगर (!rdev_set_badblocks(
				    rdev,
				    r10_bio->devs[r10_bio->पढ़ो_slot].addr
				    + sect,
				    s, 0)) अणु
				md_error(mddev, rdev);
				r10_bio->devs[r10_bio->पढ़ो_slot].bio
					= IO_BLOCKED;
			पूर्ण
			अवरोध;
		पूर्ण

		start = sl;
		/* ग_लिखो it back and re-पढ़ो */
		rcu_पढ़ो_lock();
		जबतक (sl != r10_bio->पढ़ो_slot) अणु
			अक्षर b[BDEVNAME_SIZE];

			अगर (sl==0)
				sl = conf->copies;
			sl--;
			d = r10_bio->devs[sl].devnum;
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			अगर (!rdev ||
			    test_bit(Faulty, &rdev->flags) ||
			    !test_bit(In_sync, &rdev->flags))
				जारी;

			atomic_inc(&rdev->nr_pending);
			rcu_पढ़ो_unlock();
			अगर (r10_sync_page_io(rdev,
					     r10_bio->devs[sl].addr +
					     sect,
					     s, conf->पंचांगppage, WRITE)
			    == 0) अणु
				/* Well, this device is dead */
				pr_notice("md/raid10:%s: read correction write failed (%d sectors at %llu on %s)\n",
					  mdname(mddev), s,
					  (अचिन्हित दीर्घ दीर्घ)(
						  sect +
						  choose_data_offset(r10_bio,
								     rdev)),
					  bdevname(rdev->bdev, b));
				pr_notice("md/raid10:%s: %s: failing drive\n",
					  mdname(mddev),
					  bdevname(rdev->bdev, b));
			पूर्ण
			rdev_dec_pending(rdev, mddev);
			rcu_पढ़ो_lock();
		पूर्ण
		sl = start;
		जबतक (sl != r10_bio->पढ़ो_slot) अणु
			अक्षर b[BDEVNAME_SIZE];

			अगर (sl==0)
				sl = conf->copies;
			sl--;
			d = r10_bio->devs[sl].devnum;
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			अगर (!rdev ||
			    test_bit(Faulty, &rdev->flags) ||
			    !test_bit(In_sync, &rdev->flags))
				जारी;

			atomic_inc(&rdev->nr_pending);
			rcu_पढ़ो_unlock();
			चयन (r10_sync_page_io(rdev,
					     r10_bio->devs[sl].addr +
					     sect,
					     s, conf->पंचांगppage,
						 READ)) अणु
			हाल 0:
				/* Well, this device is dead */
				pr_notice("md/raid10:%s: unable to read back corrected sectors (%d sectors at %llu on %s)\n",
				       mdname(mddev), s,
				       (अचिन्हित दीर्घ दीर्घ)(
					       sect +
					       choose_data_offset(r10_bio, rdev)),
				       bdevname(rdev->bdev, b));
				pr_notice("md/raid10:%s: %s: failing drive\n",
				       mdname(mddev),
				       bdevname(rdev->bdev, b));
				अवरोध;
			हाल 1:
				pr_info("md/raid10:%s: read error corrected (%d sectors at %llu on %s)\n",
				       mdname(mddev), s,
				       (अचिन्हित दीर्घ दीर्घ)(
					       sect +
					       choose_data_offset(r10_bio, rdev)),
				       bdevname(rdev->bdev, b));
				atomic_add(s, &rdev->corrected_errors);
			पूर्ण

			rdev_dec_pending(rdev, mddev);
			rcu_पढ़ो_lock();
		पूर्ण
		rcu_पढ़ो_unlock();

		sectors -= s;
		sect += s;
	पूर्ण
पूर्ण

अटल पूर्णांक narrow_ग_लिखो_error(काष्ठा r10bio *r10_bio, पूर्णांक i)
अणु
	काष्ठा bio *bio = r10_bio->master_bio;
	काष्ठा mddev *mddev = r10_bio->mddev;
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा md_rdev *rdev = conf->mirrors[r10_bio->devs[i].devnum].rdev;
	/* bio has the data to be written to slot 'i' where
	 * we just recently had a ग_लिखो error.
	 * We repeatedly clone the bio and trim करोwn to one block,
	 * then try the ग_लिखो.  Where the ग_लिखो fails we record
	 * a bad block.
	 * It is conceivable that the bio करोesn't exactly align with
	 * blocks.  We must handle this.
	 *
	 * We currently own a reference to the rdev.
	 */

	पूर्णांक block_sectors;
	sector_t sector;
	पूर्णांक sectors;
	पूर्णांक sect_to_ग_लिखो = r10_bio->sectors;
	पूर्णांक ok = 1;

	अगर (rdev->badblocks.shअगरt < 0)
		वापस 0;

	block_sectors = roundup(1 << rdev->badblocks.shअगरt,
				bdev_logical_block_size(rdev->bdev) >> 9);
	sector = r10_bio->sector;
	sectors = ((r10_bio->sector + block_sectors)
		   & ~(sector_t)(block_sectors - 1))
		- sector;

	जबतक (sect_to_ग_लिखो) अणु
		काष्ठा bio *wbio;
		sector_t wsector;
		अगर (sectors > sect_to_ग_लिखो)
			sectors = sect_to_ग_लिखो;
		/* Write at 'sector' for 'sectors' */
		wbio = bio_clone_fast(bio, GFP_NOIO, &mddev->bio_set);
		bio_trim(wbio, sector - bio->bi_iter.bi_sector, sectors);
		wsector = r10_bio->devs[i].addr + (sector - r10_bio->sector);
		wbio->bi_iter.bi_sector = wsector +
				   choose_data_offset(r10_bio, rdev);
		bio_set_dev(wbio, rdev->bdev);
		bio_set_op_attrs(wbio, REQ_OP_WRITE, 0);

		अगर (submit_bio_रुको(wbio) < 0)
			/* Failure! */
			ok = rdev_set_badblocks(rdev, wsector,
						sectors, 0)
				&& ok;

		bio_put(wbio);
		sect_to_ग_लिखो -= sectors;
		sector += sectors;
		sectors = block_sectors;
	पूर्ण
	वापस ok;
पूर्ण

अटल व्योम handle_पढ़ो_error(काष्ठा mddev *mddev, काष्ठा r10bio *r10_bio)
अणु
	पूर्णांक slot = r10_bio->पढ़ो_slot;
	काष्ठा bio *bio;
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा md_rdev *rdev = r10_bio->devs[slot].rdev;

	/* we got a पढ़ो error. Maybe the drive is bad.  Maybe just
	 * the block and we can fix it.
	 * We मुक्तze all other IO, and try पढ़ोing the block from
	 * other devices.  When we find one, we re-ग_लिखो
	 * and check it that fixes the पढ़ो error.
	 * This is all करोne synchronously जबतक the array is
	 * frozen.
	 */
	bio = r10_bio->devs[slot].bio;
	bio_put(bio);
	r10_bio->devs[slot].bio = शून्य;

	अगर (mddev->ro)
		r10_bio->devs[slot].bio = IO_BLOCKED;
	अन्यथा अगर (!test_bit(FailFast, &rdev->flags)) अणु
		मुक्तze_array(conf, 1);
		fix_पढ़ो_error(conf, mddev, r10_bio);
		unमुक्तze_array(conf);
	पूर्ण अन्यथा
		md_error(mddev, rdev);

	rdev_dec_pending(rdev, mddev);
	allow_barrier(conf);
	r10_bio->state = 0;
	raid10_पढ़ो_request(mddev, r10_bio->master_bio, r10_bio);
पूर्ण

अटल व्योम handle_ग_लिखो_completed(काष्ठा r10conf *conf, काष्ठा r10bio *r10_bio)
अणु
	/* Some sort of ग_लिखो request has finished and it
	 * succeeded in writing where we thought there was a
	 * bad block.  So क्रमget the bad block.
	 * Or possibly अगर failed and we need to record
	 * a bad block.
	 */
	पूर्णांक m;
	काष्ठा md_rdev *rdev;

	अगर (test_bit(R10BIO_IsSync, &r10_bio->state) ||
	    test_bit(R10BIO_IsRecover, &r10_bio->state)) अणु
		क्रम (m = 0; m < conf->copies; m++) अणु
			पूर्णांक dev = r10_bio->devs[m].devnum;
			rdev = conf->mirrors[dev].rdev;
			अगर (r10_bio->devs[m].bio == शून्य ||
				r10_bio->devs[m].bio->bi_end_io == शून्य)
				जारी;
			अगर (!r10_bio->devs[m].bio->bi_status) अणु
				rdev_clear_badblocks(
					rdev,
					r10_bio->devs[m].addr,
					r10_bio->sectors, 0);
			पूर्ण अन्यथा अणु
				अगर (!rdev_set_badblocks(
					    rdev,
					    r10_bio->devs[m].addr,
					    r10_bio->sectors, 0))
					md_error(conf->mddev, rdev);
			पूर्ण
			rdev = conf->mirrors[dev].replacement;
			अगर (r10_bio->devs[m].repl_bio == शून्य ||
				r10_bio->devs[m].repl_bio->bi_end_io == शून्य)
				जारी;

			अगर (!r10_bio->devs[m].repl_bio->bi_status) अणु
				rdev_clear_badblocks(
					rdev,
					r10_bio->devs[m].addr,
					r10_bio->sectors, 0);
			पूर्ण अन्यथा अणु
				अगर (!rdev_set_badblocks(
					    rdev,
					    r10_bio->devs[m].addr,
					    r10_bio->sectors, 0))
					md_error(conf->mddev, rdev);
			पूर्ण
		पूर्ण
		put_buf(r10_bio);
	पूर्ण अन्यथा अणु
		bool fail = false;
		क्रम (m = 0; m < conf->copies; m++) अणु
			पूर्णांक dev = r10_bio->devs[m].devnum;
			काष्ठा bio *bio = r10_bio->devs[m].bio;
			rdev = conf->mirrors[dev].rdev;
			अगर (bio == IO_MADE_GOOD) अणु
				rdev_clear_badblocks(
					rdev,
					r10_bio->devs[m].addr,
					r10_bio->sectors, 0);
				rdev_dec_pending(rdev, conf->mddev);
			पूर्ण अन्यथा अगर (bio != शून्य && bio->bi_status) अणु
				fail = true;
				अगर (!narrow_ग_लिखो_error(r10_bio, m)) अणु
					md_error(conf->mddev, rdev);
					set_bit(R10BIO_Degraded,
						&r10_bio->state);
				पूर्ण
				rdev_dec_pending(rdev, conf->mddev);
			पूर्ण
			bio = r10_bio->devs[m].repl_bio;
			rdev = conf->mirrors[dev].replacement;
			अगर (rdev && bio == IO_MADE_GOOD) अणु
				rdev_clear_badblocks(
					rdev,
					r10_bio->devs[m].addr,
					r10_bio->sectors, 0);
				rdev_dec_pending(rdev, conf->mddev);
			पूर्ण
		पूर्ण
		अगर (fail) अणु
			spin_lock_irq(&conf->device_lock);
			list_add(&r10_bio->retry_list, &conf->bio_end_io_list);
			conf->nr_queued++;
			spin_unlock_irq(&conf->device_lock);
			/*
			 * In हाल मुक्तze_array() is रुकोing क्रम condition
			 * nr_pending == nr_queued + extra to be true.
			 */
			wake_up(&conf->रुको_barrier);
			md_wakeup_thपढ़ो(conf->mddev->thपढ़ो);
		पूर्ण अन्यथा अणु
			अगर (test_bit(R10BIO_WriteError,
				     &r10_bio->state))
				बंद_ग_लिखो(r10_bio);
			raid_end_bio_io(r10_bio);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम raid10d(काष्ठा md_thपढ़ो *thपढ़ो)
अणु
	काष्ठा mddev *mddev = thपढ़ो->mddev;
	काष्ठा r10bio *r10_bio;
	अचिन्हित दीर्घ flags;
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा list_head *head = &conf->retry_list;
	काष्ठा blk_plug plug;

	md_check_recovery(mddev);

	अगर (!list_empty_careful(&conf->bio_end_io_list) &&
	    !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags)) अणु
		LIST_HEAD(पंचांगp);
		spin_lock_irqsave(&conf->device_lock, flags);
		अगर (!test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags)) अणु
			जबतक (!list_empty(&conf->bio_end_io_list)) अणु
				list_move(conf->bio_end_io_list.prev, &पंचांगp);
				conf->nr_queued--;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&conf->device_lock, flags);
		जबतक (!list_empty(&पंचांगp)) अणु
			r10_bio = list_first_entry(&पंचांगp, काष्ठा r10bio,
						   retry_list);
			list_del(&r10_bio->retry_list);
			अगर (mddev->degraded)
				set_bit(R10BIO_Degraded, &r10_bio->state);

			अगर (test_bit(R10BIO_WriteError,
				     &r10_bio->state))
				बंद_ग_लिखो(r10_bio);
			raid_end_bio_io(r10_bio);
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
		r10_bio = list_entry(head->prev, काष्ठा r10bio, retry_list);
		list_del(head->prev);
		conf->nr_queued--;
		spin_unlock_irqrestore(&conf->device_lock, flags);

		mddev = r10_bio->mddev;
		conf = mddev->निजी;
		अगर (test_bit(R10BIO_MadeGood, &r10_bio->state) ||
		    test_bit(R10BIO_WriteError, &r10_bio->state))
			handle_ग_लिखो_completed(conf, r10_bio);
		अन्यथा अगर (test_bit(R10BIO_IsReshape, &r10_bio->state))
			reshape_request_ग_लिखो(mddev, r10_bio);
		अन्यथा अगर (test_bit(R10BIO_IsSync, &r10_bio->state))
			sync_request_ग_लिखो(mddev, r10_bio);
		अन्यथा अगर (test_bit(R10BIO_IsRecover, &r10_bio->state))
			recovery_request_ग_लिखो(mddev, r10_bio);
		अन्यथा अगर (test_bit(R10BIO_ReadError, &r10_bio->state))
			handle_पढ़ो_error(mddev, r10_bio);
		अन्यथा
			WARN_ON_ONCE(1);

		cond_resched();
		अगर (mddev->sb_flags & ~(1<<MD_SB_CHANGE_PENDING))
			md_check_recovery(mddev);
	पूर्ण
	blk_finish_plug(&plug);
पूर्ण

अटल पूर्णांक init_resync(काष्ठा r10conf *conf)
अणु
	पूर्णांक ret, buffs, i;

	buffs = RESYNC_WINDOW / RESYNC_BLOCK_SIZE;
	BUG_ON(mempool_initialized(&conf->r10buf_pool));
	conf->have_replacement = 0;
	क्रम (i = 0; i < conf->geo.raid_disks; i++)
		अगर (conf->mirrors[i].replacement)
			conf->have_replacement = 1;
	ret = mempool_init(&conf->r10buf_pool, buffs,
			   r10buf_pool_alloc, r10buf_pool_मुक्त, conf);
	अगर (ret)
		वापस ret;
	conf->next_resync = 0;
	वापस 0;
पूर्ण

अटल काष्ठा r10bio *raid10_alloc_init_r10buf(काष्ठा r10conf *conf)
अणु
	काष्ठा r10bio *r10bio = mempool_alloc(&conf->r10buf_pool, GFP_NOIO);
	काष्ठा rsync_pages *rp;
	काष्ठा bio *bio;
	पूर्णांक nalloc;
	पूर्णांक i;

	अगर (test_bit(MD_RECOVERY_SYNC, &conf->mddev->recovery) ||
	    test_bit(MD_RECOVERY_RESHAPE, &conf->mddev->recovery))
		nalloc = conf->copies; /* resync */
	अन्यथा
		nalloc = 2; /* recovery */

	क्रम (i = 0; i < nalloc; i++) अणु
		bio = r10bio->devs[i].bio;
		rp = bio->bi_निजी;
		bio_reset(bio);
		bio->bi_निजी = rp;
		bio = r10bio->devs[i].repl_bio;
		अगर (bio) अणु
			rp = bio->bi_निजी;
			bio_reset(bio);
			bio->bi_निजी = rp;
		पूर्ण
	पूर्ण
	वापस r10bio;
पूर्ण

/*
 * Set cluster_sync_high since we need other nodes to add the
 * range [cluster_sync_low, cluster_sync_high] to suspend list.
 */
अटल व्योम raid10_set_cluster_sync_high(काष्ठा r10conf *conf)
अणु
	sector_t winकरोw_size;
	पूर्णांक extra_chunk, chunks;

	/*
	 * First, here we define "stripe" as a unit which across
	 * all member devices one समय, so we get chunks by use
	 * raid_disks / near_copies. Otherwise, अगर near_copies is
	 * बंद to raid_disks, then resync winकरोw could increases
	 * linearly with the increase of raid_disks, which means
	 * we will suspend a really large IO winकरोw जबतक it is not
	 * necessary. If raid_disks is not भागisible by near_copies,
	 * an extra chunk is needed to ensure the whole "stripe" is
	 * covered.
	 */

	chunks = conf->geo.raid_disks / conf->geo.near_copies;
	अगर (conf->geo.raid_disks % conf->geo.near_copies == 0)
		extra_chunk = 0;
	अन्यथा
		extra_chunk = 1;
	winकरोw_size = (chunks + extra_chunk) * conf->mddev->chunk_sectors;

	/*
	 * At least use a 32M winकरोw to align with raid1's resync winकरोw
	 */
	winकरोw_size = (CLUSTER_RESYNC_WINDOW_SECTORS > winकरोw_size) ?
			CLUSTER_RESYNC_WINDOW_SECTORS : winकरोw_size;

	conf->cluster_sync_high = conf->cluster_sync_low + winकरोw_size;
पूर्ण

/*
 * perक्रमm a "sync" on one "block"
 *
 * We need to make sure that no normal I/O request - particularly ग_लिखो
 * requests - conflict with active sync requests.
 *
 * This is achieved by tracking pending requests and a 'barrier' concept
 * that can be installed to exclude normal IO requests.
 *
 * Resync and recovery are handled very dअगरferently.
 * We dअगरferentiate by looking at MD_RECOVERY_SYNC in mddev->recovery.
 *
 * For resync, we iterate over भव addresses, पढ़ो all copies,
 * and update अगर there are dअगरferences.  If only one copy is live,
 * skip it.
 * For recovery, we iterate over physical addresses, पढ़ो a good
 * value क्रम each non-in_sync drive, and over-ग_लिखो.
 *
 * So, क्रम recovery we may have several outstanding complex requests क्रम a
 * given address, one क्रम each out-of-sync device.  We model this by allocating
 * a number of r10_bio काष्ठाures, one क्रम each out-of-sync device.
 * As we setup these काष्ठाures, we collect all bio's together पूर्णांकo a list
 * which we then process collectively to add pages, and then process again
 * to pass to submit_bio_noacct.
 *
 * The r10_bio काष्ठाures are linked using a borrowed master_bio poपूर्णांकer.
 * This link is counted in ->reमुख्यing.  When the r10_bio that poपूर्णांकs to शून्य
 * has its reमुख्यing count decremented to 0, the whole complex operation
 * is complete.
 *
 */

अटल sector_t raid10_sync_request(काष्ठा mddev *mddev, sector_t sector_nr,
			     पूर्णांक *skipped)
अणु
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा r10bio *r10_bio;
	काष्ठा bio *biolist = शून्य, *bio;
	sector_t max_sector, nr_sectors;
	पूर्णांक i;
	पूर्णांक max_sync;
	sector_t sync_blocks;
	sector_t sectors_skipped = 0;
	पूर्णांक chunks_skipped = 0;
	sector_t chunk_mask = conf->geo.chunk_mask;
	पूर्णांक page_idx = 0;

	अगर (!mempool_initialized(&conf->r10buf_pool))
		अगर (init_resync(conf))
			वापस 0;

	/*
	 * Allow skipping a full rebuild क्रम incremental assembly
	 * of a clean array, like RAID1 करोes.
	 */
	अगर (mddev->biपंचांगap == शून्य &&
	    mddev->recovery_cp == MaxSector &&
	    mddev->reshape_position == MaxSector &&
	    !test_bit(MD_RECOVERY_SYNC, &mddev->recovery) &&
	    !test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery) &&
	    !test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
	    conf->fullsync == 0) अणु
		*skipped = 1;
		वापस mddev->dev_sectors - sector_nr;
	पूर्ण

 skipped:
	max_sector = mddev->dev_sectors;
	अगर (test_bit(MD_RECOVERY_SYNC, &mddev->recovery) ||
	    test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery))
		max_sector = mddev->resync_max_sectors;
	अगर (sector_nr >= max_sector) अणु
		conf->cluster_sync_low = 0;
		conf->cluster_sync_high = 0;

		/* If we पातed, we need to पात the
		 * sync on the 'current' biपंचांगap chucks (there can
		 * be several when recovering multiple devices).
		 * as we may have started syncing it but not finished.
		 * We can find the current address in
		 * mddev->curr_resync, but क्रम recovery,
		 * we need to convert that to several
		 * भव addresses.
		 */
		अगर (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery)) अणु
			end_reshape(conf);
			बंद_sync(conf);
			वापस 0;
		पूर्ण

		अगर (mddev->curr_resync < max_sector) अणु /* पातed */
			अगर (test_bit(MD_RECOVERY_SYNC, &mddev->recovery))
				md_biपंचांगap_end_sync(mddev->biपंचांगap, mddev->curr_resync,
						   &sync_blocks, 1);
			अन्यथा क्रम (i = 0; i < conf->geo.raid_disks; i++) अणु
				sector_t sect =
					raid10_find_virt(conf, mddev->curr_resync, i);
				md_biपंचांगap_end_sync(mddev->biपंचांगap, sect,
						   &sync_blocks, 1);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* completed sync */
			अगर ((!mddev->biपंचांगap || conf->fullsync)
			    && conf->have_replacement
			    && test_bit(MD_RECOVERY_SYNC, &mddev->recovery)) अणु
				/* Completed a full sync so the replacements
				 * are now fully recovered.
				 */
				rcu_पढ़ो_lock();
				क्रम (i = 0; i < conf->geo.raid_disks; i++) अणु
					काष्ठा md_rdev *rdev =
						rcu_dereference(conf->mirrors[i].replacement);
					अगर (rdev)
						rdev->recovery_offset = MaxSector;
				पूर्ण
				rcu_पढ़ो_unlock();
			पूर्ण
			conf->fullsync = 0;
		पूर्ण
		md_biपंचांगap_बंद_sync(mddev->biपंचांगap);
		बंद_sync(conf);
		*skipped = 1;
		वापस sectors_skipped;
	पूर्ण

	अगर (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery))
		वापस reshape_request(mddev, sector_nr, skipped);

	अगर (chunks_skipped >= conf->geo.raid_disks) अणु
		/* अगर there has been nothing to करो on any drive,
		 * then there is nothing to करो at all..
		 */
		*skipped = 1;
		वापस (max_sector - sector_nr) + sectors_skipped;
	पूर्ण

	अगर (max_sector > mddev->resync_max)
		max_sector = mddev->resync_max; /* Don't करो IO beyond here */

	/* make sure whole request will fit in a chunk - अगर chunks
	 * are meaningful
	 */
	अगर (conf->geo.near_copies < conf->geo.raid_disks &&
	    max_sector > (sector_nr | chunk_mask))
		max_sector = (sector_nr | chunk_mask) + 1;

	/*
	 * If there is non-resync activity रुकोing क्रम a turn, then let it
	 * though beक्रमe starting on this new sync request.
	 */
	अगर (conf->nr_रुकोing)
		schedule_समयout_unपूर्णांकerruptible(1);

	/* Again, very dअगरferent code क्रम resync and recovery.
	 * Both must result in an r10bio with a list of bios that
	 * have bi_end_io, bi_sector, bi_bdev set,
	 * and bi_निजी set to the r10bio.
	 * For recovery, we may actually create several r10bios
	 * with 2 bios in each, that correspond to the bios in the मुख्य one.
	 * In this हाल, the subordinate r10bios link back through a
	 * borrowed master_bio poपूर्णांकer, and the counter in the master
	 * includes a ref from each subordinate.
	 */
	/* First, we decide what to करो and set ->bi_end_io
	 * To end_sync_पढ़ो अगर we want to पढ़ो, and
	 * end_sync_ग_लिखो अगर we will want to ग_लिखो.
	 */

	max_sync = RESYNC_PAGES << (PAGE_SHIFT-9);
	अगर (!test_bit(MD_RECOVERY_SYNC, &mddev->recovery)) अणु
		/* recovery... the complicated one */
		पूर्णांक j;
		r10_bio = शून्य;

		क्रम (i = 0 ; i < conf->geo.raid_disks; i++) अणु
			पूर्णांक still_degraded;
			काष्ठा r10bio *rb2;
			sector_t sect;
			पूर्णांक must_sync;
			पूर्णांक any_working;
			पूर्णांक need_recover = 0;
			पूर्णांक need_replace = 0;
			काष्ठा raid10_info *mirror = &conf->mirrors[i];
			काष्ठा md_rdev *mrdev, *mreplace;

			rcu_पढ़ो_lock();
			mrdev = rcu_dereference(mirror->rdev);
			mreplace = rcu_dereference(mirror->replacement);

			अगर (mrdev != शून्य &&
			    !test_bit(Faulty, &mrdev->flags) &&
			    !test_bit(In_sync, &mrdev->flags))
				need_recover = 1;
			अगर (mreplace != शून्य &&
			    !test_bit(Faulty, &mreplace->flags))
				need_replace = 1;

			अगर (!need_recover && !need_replace) अणु
				rcu_पढ़ो_unlock();
				जारी;
			पूर्ण

			still_degraded = 0;
			/* want to reस्थिरruct this device */
			rb2 = r10_bio;
			sect = raid10_find_virt(conf, sector_nr, i);
			अगर (sect >= mddev->resync_max_sectors) अणु
				/* last stripe is not complete - करोn't
				 * try to recover this sector.
				 */
				rcu_पढ़ो_unlock();
				जारी;
			पूर्ण
			अगर (mreplace && test_bit(Faulty, &mreplace->flags))
				mreplace = शून्य;
			/* Unless we are करोing a full sync, or a replacement
			 * we only need to recover the block अगर it is set in
			 * the biपंचांगap
			 */
			must_sync = md_biपंचांगap_start_sync(mddev->biपंचांगap, sect,
							 &sync_blocks, 1);
			अगर (sync_blocks < max_sync)
				max_sync = sync_blocks;
			अगर (!must_sync &&
			    mreplace == शून्य &&
			    !conf->fullsync) अणु
				/* yep, skip the sync_blocks here, but करोn't assume
				 * that there will never be anything to करो here
				 */
				chunks_skipped = -1;
				rcu_पढ़ो_unlock();
				जारी;
			पूर्ण
			atomic_inc(&mrdev->nr_pending);
			अगर (mreplace)
				atomic_inc(&mreplace->nr_pending);
			rcu_पढ़ो_unlock();

			r10_bio = raid10_alloc_init_r10buf(conf);
			r10_bio->state = 0;
			उठाओ_barrier(conf, rb2 != शून्य);
			atomic_set(&r10_bio->reमुख्यing, 0);

			r10_bio->master_bio = (काष्ठा bio*)rb2;
			अगर (rb2)
				atomic_inc(&rb2->reमुख्यing);
			r10_bio->mddev = mddev;
			set_bit(R10BIO_IsRecover, &r10_bio->state);
			r10_bio->sector = sect;

			raid10_find_phys(conf, r10_bio);

			/* Need to check अगर the array will still be
			 * degraded
			 */
			rcu_पढ़ो_lock();
			क्रम (j = 0; j < conf->geo.raid_disks; j++) अणु
				काष्ठा md_rdev *rdev = rcu_dereference(
					conf->mirrors[j].rdev);
				अगर (rdev == शून्य || test_bit(Faulty, &rdev->flags)) अणु
					still_degraded = 1;
					अवरोध;
				पूर्ण
			पूर्ण

			must_sync = md_biपंचांगap_start_sync(mddev->biपंचांगap, sect,
							 &sync_blocks, still_degraded);

			any_working = 0;
			क्रम (j=0; j<conf->copies;j++) अणु
				पूर्णांक k;
				पूर्णांक d = r10_bio->devs[j].devnum;
				sector_t from_addr, to_addr;
				काष्ठा md_rdev *rdev =
					rcu_dereference(conf->mirrors[d].rdev);
				sector_t sector, first_bad;
				पूर्णांक bad_sectors;
				अगर (!rdev ||
				    !test_bit(In_sync, &rdev->flags))
					जारी;
				/* This is where we पढ़ो from */
				any_working = 1;
				sector = r10_bio->devs[j].addr;

				अगर (is_badblock(rdev, sector, max_sync,
						&first_bad, &bad_sectors)) अणु
					अगर (first_bad > sector)
						max_sync = first_bad - sector;
					अन्यथा अणु
						bad_sectors -= (sector
								- first_bad);
						अगर (max_sync > bad_sectors)
							max_sync = bad_sectors;
						जारी;
					पूर्ण
				पूर्ण
				bio = r10_bio->devs[0].bio;
				bio->bi_next = biolist;
				biolist = bio;
				bio->bi_end_io = end_sync_पढ़ो;
				bio_set_op_attrs(bio, REQ_OP_READ, 0);
				अगर (test_bit(FailFast, &rdev->flags))
					bio->bi_opf |= MD_FAILFAST;
				from_addr = r10_bio->devs[j].addr;
				bio->bi_iter.bi_sector = from_addr +
					rdev->data_offset;
				bio_set_dev(bio, rdev->bdev);
				atomic_inc(&rdev->nr_pending);
				/* and we ग_लिखो to 'i' (अगर not in_sync) */

				क्रम (k=0; k<conf->copies; k++)
					अगर (r10_bio->devs[k].devnum == i)
						अवरोध;
				BUG_ON(k == conf->copies);
				to_addr = r10_bio->devs[k].addr;
				r10_bio->devs[0].devnum = d;
				r10_bio->devs[0].addr = from_addr;
				r10_bio->devs[1].devnum = i;
				r10_bio->devs[1].addr = to_addr;

				अगर (need_recover) अणु
					bio = r10_bio->devs[1].bio;
					bio->bi_next = biolist;
					biolist = bio;
					bio->bi_end_io = end_sync_ग_लिखो;
					bio_set_op_attrs(bio, REQ_OP_WRITE, 0);
					bio->bi_iter.bi_sector = to_addr
						+ mrdev->data_offset;
					bio_set_dev(bio, mrdev->bdev);
					atomic_inc(&r10_bio->reमुख्यing);
				पूर्ण अन्यथा
					r10_bio->devs[1].bio->bi_end_io = शून्य;

				/* and maybe ग_लिखो to replacement */
				bio = r10_bio->devs[1].repl_bio;
				अगर (bio)
					bio->bi_end_io = शून्य;
				/* Note: अगर need_replace, then bio
				 * cannot be शून्य as r10buf_pool_alloc will
				 * have allocated it.
				 */
				अगर (!need_replace)
					अवरोध;
				bio->bi_next = biolist;
				biolist = bio;
				bio->bi_end_io = end_sync_ग_लिखो;
				bio_set_op_attrs(bio, REQ_OP_WRITE, 0);
				bio->bi_iter.bi_sector = to_addr +
					mreplace->data_offset;
				bio_set_dev(bio, mreplace->bdev);
				atomic_inc(&r10_bio->reमुख्यing);
				अवरोध;
			पूर्ण
			rcu_पढ़ो_unlock();
			अगर (j == conf->copies) अणु
				/* Cannot recover, so पात the recovery or
				 * record a bad block */
				अगर (any_working) अणु
					/* problem is that there are bad blocks
					 * on other device(s)
					 */
					पूर्णांक k;
					क्रम (k = 0; k < conf->copies; k++)
						अगर (r10_bio->devs[k].devnum == i)
							अवरोध;
					अगर (!test_bit(In_sync,
						      &mrdev->flags)
					    && !rdev_set_badblocks(
						    mrdev,
						    r10_bio->devs[k].addr,
						    max_sync, 0))
						any_working = 0;
					अगर (mreplace &&
					    !rdev_set_badblocks(
						    mreplace,
						    r10_bio->devs[k].addr,
						    max_sync, 0))
						any_working = 0;
				पूर्ण
				अगर (!any_working)  अणु
					अगर (!test_and_set_bit(MD_RECOVERY_INTR,
							      &mddev->recovery))
						pr_warn("md/raid10:%s: insufficient working devices for recovery.\n",
						       mdname(mddev));
					mirror->recovery_disabled
						= mddev->recovery_disabled;
				पूर्ण
				put_buf(r10_bio);
				अगर (rb2)
					atomic_dec(&rb2->reमुख्यing);
				r10_bio = rb2;
				rdev_dec_pending(mrdev, mddev);
				अगर (mreplace)
					rdev_dec_pending(mreplace, mddev);
				अवरोध;
			पूर्ण
			rdev_dec_pending(mrdev, mddev);
			अगर (mreplace)
				rdev_dec_pending(mreplace, mddev);
			अगर (r10_bio->devs[0].bio->bi_opf & MD_FAILFAST) अणु
				/* Only want this अगर there is अन्यथाwhere to
				 * पढ़ो from. 'j' is currently the first
				 * पढ़ोable copy.
				 */
				पूर्णांक tarमाला_लो = 1;
				क्रम (; j < conf->copies; j++) अणु
					पूर्णांक d = r10_bio->devs[j].devnum;
					अगर (conf->mirrors[d].rdev &&
					    test_bit(In_sync,
						      &conf->mirrors[d].rdev->flags))
						tarमाला_लो++;
				पूर्ण
				अगर (tarमाला_लो == 1)
					r10_bio->devs[0].bio->bi_opf
						&= ~MD_FAILFAST;
			पूर्ण
		पूर्ण
		अगर (biolist == शून्य) अणु
			जबतक (r10_bio) अणु
				काष्ठा r10bio *rb2 = r10_bio;
				r10_bio = (काष्ठा r10bio*) rb2->master_bio;
				rb2->master_bio = शून्य;
				put_buf(rb2);
			पूर्ण
			जाओ giveup;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* resync. Schedule a पढ़ो क्रम every block at this virt offset */
		पूर्णांक count = 0;

		/*
		 * Since curr_resync_completed could probably not update in
		 * समय, and we will set cluster_sync_low based on it.
		 * Let's check against "sector_nr + 2 * RESYNC_SECTORS" क्रम
		 * safety reason, which ensures curr_resync_completed is
		 * updated in biपंचांगap_cond_end_sync.
		 */
		md_biपंचांगap_cond_end_sync(mddev->biपंचांगap, sector_nr,
					mddev_is_clustered(mddev) &&
					(sector_nr + 2 * RESYNC_SECTORS > conf->cluster_sync_high));

		अगर (!md_biपंचांगap_start_sync(mddev->biपंचांगap, sector_nr,
					  &sync_blocks, mddev->degraded) &&
		    !conf->fullsync && !test_bit(MD_RECOVERY_REQUESTED,
						 &mddev->recovery)) अणु
			/* We can skip this block */
			*skipped = 1;
			वापस sync_blocks + sectors_skipped;
		पूर्ण
		अगर (sync_blocks < max_sync)
			max_sync = sync_blocks;
		r10_bio = raid10_alloc_init_r10buf(conf);
		r10_bio->state = 0;

		r10_bio->mddev = mddev;
		atomic_set(&r10_bio->reमुख्यing, 0);
		उठाओ_barrier(conf, 0);
		conf->next_resync = sector_nr;

		r10_bio->master_bio = शून्य;
		r10_bio->sector = sector_nr;
		set_bit(R10BIO_IsSync, &r10_bio->state);
		raid10_find_phys(conf, r10_bio);
		r10_bio->sectors = (sector_nr | chunk_mask) - sector_nr + 1;

		क्रम (i = 0; i < conf->copies; i++) अणु
			पूर्णांक d = r10_bio->devs[i].devnum;
			sector_t first_bad, sector;
			पूर्णांक bad_sectors;
			काष्ठा md_rdev *rdev;

			अगर (r10_bio->devs[i].repl_bio)
				r10_bio->devs[i].repl_bio->bi_end_io = शून्य;

			bio = r10_bio->devs[i].bio;
			bio->bi_status = BLK_STS_IOERR;
			rcu_पढ़ो_lock();
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			अगर (rdev == शून्य || test_bit(Faulty, &rdev->flags)) अणु
				rcu_पढ़ो_unlock();
				जारी;
			पूर्ण
			sector = r10_bio->devs[i].addr;
			अगर (is_badblock(rdev, sector, max_sync,
					&first_bad, &bad_sectors)) अणु
				अगर (first_bad > sector)
					max_sync = first_bad - sector;
				अन्यथा अणु
					bad_sectors -= (sector - first_bad);
					अगर (max_sync > bad_sectors)
						max_sync = bad_sectors;
					rcu_पढ़ो_unlock();
					जारी;
				पूर्ण
			पूर्ण
			atomic_inc(&rdev->nr_pending);
			atomic_inc(&r10_bio->reमुख्यing);
			bio->bi_next = biolist;
			biolist = bio;
			bio->bi_end_io = end_sync_पढ़ो;
			bio_set_op_attrs(bio, REQ_OP_READ, 0);
			अगर (test_bit(FailFast, &rdev->flags))
				bio->bi_opf |= MD_FAILFAST;
			bio->bi_iter.bi_sector = sector + rdev->data_offset;
			bio_set_dev(bio, rdev->bdev);
			count++;

			rdev = rcu_dereference(conf->mirrors[d].replacement);
			अगर (rdev == शून्य || test_bit(Faulty, &rdev->flags)) अणु
				rcu_पढ़ो_unlock();
				जारी;
			पूर्ण
			atomic_inc(&rdev->nr_pending);

			/* Need to set up क्रम writing to the replacement */
			bio = r10_bio->devs[i].repl_bio;
			bio->bi_status = BLK_STS_IOERR;

			sector = r10_bio->devs[i].addr;
			bio->bi_next = biolist;
			biolist = bio;
			bio->bi_end_io = end_sync_ग_लिखो;
			bio_set_op_attrs(bio, REQ_OP_WRITE, 0);
			अगर (test_bit(FailFast, &rdev->flags))
				bio->bi_opf |= MD_FAILFAST;
			bio->bi_iter.bi_sector = sector + rdev->data_offset;
			bio_set_dev(bio, rdev->bdev);
			count++;
			rcu_पढ़ो_unlock();
		पूर्ण

		अगर (count < 2) अणु
			क्रम (i=0; i<conf->copies; i++) अणु
				पूर्णांक d = r10_bio->devs[i].devnum;
				अगर (r10_bio->devs[i].bio->bi_end_io)
					rdev_dec_pending(conf->mirrors[d].rdev,
							 mddev);
				अगर (r10_bio->devs[i].repl_bio &&
				    r10_bio->devs[i].repl_bio->bi_end_io)
					rdev_dec_pending(
						conf->mirrors[d].replacement,
						mddev);
			पूर्ण
			put_buf(r10_bio);
			biolist = शून्य;
			जाओ giveup;
		पूर्ण
	पूर्ण

	nr_sectors = 0;
	अगर (sector_nr + max_sync < max_sector)
		max_sector = sector_nr + max_sync;
	करो अणु
		काष्ठा page *page;
		पूर्णांक len = PAGE_SIZE;
		अगर (sector_nr + (len>>9) > max_sector)
			len = (max_sector - sector_nr) << 9;
		अगर (len == 0)
			अवरोध;
		क्रम (bio= biolist ; bio ; bio=bio->bi_next) अणु
			काष्ठा resync_pages *rp = get_resync_pages(bio);
			page = resync_fetch_page(rp, page_idx);
			/*
			 * won't fail because the vec table is big enough
			 * to hold all these pages
			 */
			bio_add_page(bio, page, len, 0);
		पूर्ण
		nr_sectors += len>>9;
		sector_nr += len>>9;
	पूर्ण जबतक (++page_idx < RESYNC_PAGES);
	r10_bio->sectors = nr_sectors;

	अगर (mddev_is_clustered(mddev) &&
	    test_bit(MD_RECOVERY_SYNC, &mddev->recovery)) अणु
		/* It is resync not recovery */
		अगर (conf->cluster_sync_high < sector_nr + nr_sectors) अणु
			conf->cluster_sync_low = mddev->curr_resync_completed;
			raid10_set_cluster_sync_high(conf);
			/* Send resync message */
			md_cluster_ops->resync_info_update(mddev,
						conf->cluster_sync_low,
						conf->cluster_sync_high);
		पूर्ण
	पूर्ण अन्यथा अगर (mddev_is_clustered(mddev)) अणु
		/* This is recovery not resync */
		sector_t sect_va1, sect_va2;
		bool broadcast_msg = false;

		क्रम (i = 0; i < conf->geo.raid_disks; i++) अणु
			/*
			 * sector_nr is a device address क्रम recovery, so we
			 * need translate it to array address beक्रमe compare
			 * with cluster_sync_high.
			 */
			sect_va1 = raid10_find_virt(conf, sector_nr, i);

			अगर (conf->cluster_sync_high < sect_va1 + nr_sectors) अणु
				broadcast_msg = true;
				/*
				 * curr_resync_completed is similar as
				 * sector_nr, so make the translation too.
				 */
				sect_va2 = raid10_find_virt(conf,
					mddev->curr_resync_completed, i);

				अगर (conf->cluster_sync_low == 0 ||
				    conf->cluster_sync_low > sect_va2)
					conf->cluster_sync_low = sect_va2;
			पूर्ण
		पूर्ण
		अगर (broadcast_msg) अणु
			raid10_set_cluster_sync_high(conf);
			md_cluster_ops->resync_info_update(mddev,
						conf->cluster_sync_low,
						conf->cluster_sync_high);
		पूर्ण
	पूर्ण

	जबतक (biolist) अणु
		bio = biolist;
		biolist = biolist->bi_next;

		bio->bi_next = शून्य;
		r10_bio = get_resync_r10bio(bio);
		r10_bio->sectors = nr_sectors;

		अगर (bio->bi_end_io == end_sync_पढ़ो) अणु
			md_sync_acct_bio(bio, nr_sectors);
			bio->bi_status = 0;
			submit_bio_noacct(bio);
		पूर्ण
	पूर्ण

	अगर (sectors_skipped)
		/* pretend they weren't skipped, it makes
		 * no important dअगरference in this हाल
		 */
		md_करोne_sync(mddev, sectors_skipped, 1);

	वापस sectors_skipped + nr_sectors;
 giveup:
	/* There is nowhere to ग_लिखो, so all non-sync
	 * drives must be failed or in resync, all drives
	 * have a bad block, so try the next chunk...
	 */
	अगर (sector_nr + max_sync < max_sector)
		max_sector = sector_nr + max_sync;

	sectors_skipped += (max_sector - sector_nr);
	chunks_skipped ++;
	sector_nr = max_sector;
	जाओ skipped;
पूर्ण

अटल sector_t
raid10_size(काष्ठा mddev *mddev, sector_t sectors, पूर्णांक raid_disks)
अणु
	sector_t size;
	काष्ठा r10conf *conf = mddev->निजी;

	अगर (!raid_disks)
		raid_disks = min(conf->geo.raid_disks,
				 conf->prev.raid_disks);
	अगर (!sectors)
		sectors = conf->dev_sectors;

	size = sectors >> conf->geo.chunk_shअगरt;
	sector_भाग(size, conf->geo.far_copies);
	size = size * raid_disks;
	sector_भाग(size, conf->geo.near_copies);

	वापस size << conf->geo.chunk_shअगरt;
पूर्ण

अटल व्योम calc_sectors(काष्ठा r10conf *conf, sector_t size)
अणु
	/* Calculate the number of sectors-per-device that will
	 * actually be used, and set conf->dev_sectors and
	 * conf->stride
	 */

	size = size >> conf->geo.chunk_shअगरt;
	sector_भाग(size, conf->geo.far_copies);
	size = size * conf->geo.raid_disks;
	sector_भाग(size, conf->geo.near_copies);
	/* 'size' is now the number of chunks in the array */
	/* calculate "used chunks per device" */
	size = size * conf->copies;

	/* We need to round up when भागiding by raid_disks to
	 * get the stride size.
	 */
	size = DIV_ROUND_UP_SECTOR_T(size, conf->geo.raid_disks);

	conf->dev_sectors = size << conf->geo.chunk_shअगरt;

	अगर (conf->geo.far_offset)
		conf->geo.stride = 1 << conf->geo.chunk_shअगरt;
	अन्यथा अणु
		sector_भाग(size, conf->geo.far_copies);
		conf->geo.stride = size << conf->geo.chunk_shअगरt;
	पूर्ण
पूर्ण

क्रमागत geo_type अणुgeo_new, geo_old, geo_startपूर्ण;
अटल पूर्णांक setup_geo(काष्ठा geom *geo, काष्ठा mddev *mddev, क्रमागत geo_type new)
अणु
	पूर्णांक nc, fc, fo;
	पूर्णांक layout, chunk, disks;
	चयन (new) अणु
	हाल geo_old:
		layout = mddev->layout;
		chunk = mddev->chunk_sectors;
		disks = mddev->raid_disks - mddev->delta_disks;
		अवरोध;
	हाल geo_new:
		layout = mddev->new_layout;
		chunk = mddev->new_chunk_sectors;
		disks = mddev->raid_disks;
		अवरोध;
	शेष: /* aव्योम 'may be unused' warnings */
	हाल geo_start: /* new when starting reshape - raid_disks not
			 * updated yet. */
		layout = mddev->new_layout;
		chunk = mddev->new_chunk_sectors;
		disks = mddev->raid_disks + mddev->delta_disks;
		अवरोध;
	पूर्ण
	अगर (layout >> 19)
		वापस -1;
	अगर (chunk < (PAGE_SIZE >> 9) ||
	    !is_घातer_of_2(chunk))
		वापस -2;
	nc = layout & 255;
	fc = (layout >> 8) & 255;
	fo = layout & (1<<16);
	geo->raid_disks = disks;
	geo->near_copies = nc;
	geo->far_copies = fc;
	geo->far_offset = fo;
	चयन (layout >> 17) अणु
	हाल 0:	/* original layout.  simple but not always optimal */
		geo->far_set_size = disks;
		अवरोध;
	हाल 1: /* "improved" layout which was buggy.  Hopefully no-one is
		 * actually using this, but leave code here just in हाल.*/
		geo->far_set_size = disks/fc;
		WARN(geo->far_set_size < fc,
		     "This RAID10 layout does not provide data safety - please backup and create new array\n");
		अवरोध;
	हाल 2: /* "improved" layout fixed to match करोcumentation */
		geo->far_set_size = fc * nc;
		अवरोध;
	शेष: /* Not a valid layout */
		वापस -1;
	पूर्ण
	geo->chunk_mask = chunk - 1;
	geo->chunk_shअगरt = ffz(~chunk);
	वापस nc*fc;
पूर्ण

अटल काष्ठा r10conf *setup_conf(काष्ठा mddev *mddev)
अणु
	काष्ठा r10conf *conf = शून्य;
	पूर्णांक err = -EINVAL;
	काष्ठा geom geo;
	पूर्णांक copies;

	copies = setup_geo(&geo, mddev, geo_new);

	अगर (copies == -2) अणु
		pr_warn("md/raid10:%s: chunk size must be at least PAGE_SIZE(%ld) and be a power of 2.\n",
			mdname(mddev), PAGE_SIZE);
		जाओ out;
	पूर्ण

	अगर (copies < 2 || copies > mddev->raid_disks) अणु
		pr_warn("md/raid10:%s: unsupported raid10 layout: 0x%8x\n",
			mdname(mddev), mddev->new_layout);
		जाओ out;
	पूर्ण

	err = -ENOMEM;
	conf = kzalloc(माप(काष्ठा r10conf), GFP_KERNEL);
	अगर (!conf)
		जाओ out;

	/* FIXME calc properly */
	conf->mirrors = kसुस्मृति(mddev->raid_disks + max(0, -mddev->delta_disks),
				माप(काष्ठा raid10_info),
				GFP_KERNEL);
	अगर (!conf->mirrors)
		जाओ out;

	conf->पंचांगppage = alloc_page(GFP_KERNEL);
	अगर (!conf->पंचांगppage)
		जाओ out;

	conf->geo = geo;
	conf->copies = copies;
	err = mempool_init(&conf->r10bio_pool, NR_RAID_BIOS, r10bio_pool_alloc,
			   rbio_pool_मुक्त, conf);
	अगर (err)
		जाओ out;

	err = bioset_init(&conf->bio_split, BIO_POOL_SIZE, 0, 0);
	अगर (err)
		जाओ out;

	calc_sectors(conf, mddev->dev_sectors);
	अगर (mddev->reshape_position == MaxSector) अणु
		conf->prev = conf->geo;
		conf->reshape_progress = MaxSector;
	पूर्ण अन्यथा अणु
		अगर (setup_geo(&conf->prev, mddev, geo_old) != conf->copies) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		conf->reshape_progress = mddev->reshape_position;
		अगर (conf->prev.far_offset)
			conf->prev.stride = 1 << conf->prev.chunk_shअगरt;
		अन्यथा
			/* far_copies must be 1 */
			conf->prev.stride = conf->dev_sectors;
	पूर्ण
	conf->reshape_safe = conf->reshape_progress;
	spin_lock_init(&conf->device_lock);
	INIT_LIST_HEAD(&conf->retry_list);
	INIT_LIST_HEAD(&conf->bio_end_io_list);

	spin_lock_init(&conf->resync_lock);
	init_रुकोqueue_head(&conf->रुको_barrier);
	atomic_set(&conf->nr_pending, 0);

	err = -ENOMEM;
	conf->thपढ़ो = md_रेजिस्टर_thपढ़ो(raid10d, mddev, "raid10");
	अगर (!conf->thपढ़ो)
		जाओ out;

	conf->mddev = mddev;
	वापस conf;

 out:
	अगर (conf) अणु
		mempool_निकास(&conf->r10bio_pool);
		kमुक्त(conf->mirrors);
		safe_put_page(conf->पंचांगppage);
		bioset_निकास(&conf->bio_split);
		kमुक्त(conf);
	पूर्ण
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम raid10_set_io_opt(काष्ठा r10conf *conf)
अणु
	पूर्णांक raid_disks = conf->geo.raid_disks;

	अगर (!(conf->geo.raid_disks % conf->geo.near_copies))
		raid_disks /= conf->geo.near_copies;
	blk_queue_io_opt(conf->mddev->queue, (conf->mddev->chunk_sectors << 9) *
			 raid_disks);
पूर्ण

अटल पूर्णांक raid10_run(काष्ठा mddev *mddev)
अणु
	काष्ठा r10conf *conf;
	पूर्णांक i, disk_idx;
	काष्ठा raid10_info *disk;
	काष्ठा md_rdev *rdev;
	sector_t size;
	sector_t min_offset_dअगरf = 0;
	पूर्णांक first = 1;
	bool discard_supported = false;

	अगर (mddev_init_ग_लिखोs_pending(mddev) < 0)
		वापस -ENOMEM;

	अगर (mddev->निजी == शून्य) अणु
		conf = setup_conf(mddev);
		अगर (IS_ERR(conf))
			वापस PTR_ERR(conf);
		mddev->निजी = conf;
	पूर्ण
	conf = mddev->निजी;
	अगर (!conf)
		जाओ out;

	अगर (mddev_is_clustered(conf->mddev)) अणु
		पूर्णांक fc, fo;

		fc = (mddev->layout >> 8) & 255;
		fo = mddev->layout & (1<<16);
		अगर (fc > 1 || fo > 0) अणु
			pr_err("only near layout is supported by clustered"
				" raid10\n");
			जाओ out_मुक्त_conf;
		पूर्ण
	पूर्ण

	mddev->thपढ़ो = conf->thपढ़ो;
	conf->thपढ़ो = शून्य;

	अगर (mddev->queue) अणु
		blk_queue_max_discard_sectors(mddev->queue,
					      अच_पूर्णांक_उच्च);
		blk_queue_max_ग_लिखो_same_sectors(mddev->queue, 0);
		blk_queue_max_ग_लिखो_zeroes_sectors(mddev->queue, 0);
		blk_queue_io_min(mddev->queue, mddev->chunk_sectors << 9);
		raid10_set_io_opt(conf);
	पूर्ण

	rdev_क्रम_each(rdev, mddev) अणु
		दीर्घ दीर्घ dअगरf;

		disk_idx = rdev->raid_disk;
		अगर (disk_idx < 0)
			जारी;
		अगर (disk_idx >= conf->geo.raid_disks &&
		    disk_idx >= conf->prev.raid_disks)
			जारी;
		disk = conf->mirrors + disk_idx;

		अगर (test_bit(Replacement, &rdev->flags)) अणु
			अगर (disk->replacement)
				जाओ out_मुक्त_conf;
			disk->replacement = rdev;
		पूर्ण अन्यथा अणु
			अगर (disk->rdev)
				जाओ out_मुक्त_conf;
			disk->rdev = rdev;
		पूर्ण
		dअगरf = (rdev->new_data_offset - rdev->data_offset);
		अगर (!mddev->reshape_backwards)
			dअगरf = -dअगरf;
		अगर (dअगरf < 0)
			dअगरf = 0;
		अगर (first || dअगरf < min_offset_dअगरf)
			min_offset_dअगरf = dअगरf;

		अगर (mddev->gendisk)
			disk_stack_limits(mddev->gendisk, rdev->bdev,
					  rdev->data_offset << 9);

		disk->head_position = 0;

		अगर (blk_queue_discard(bdev_get_queue(rdev->bdev)))
			discard_supported = true;
		first = 0;
	पूर्ण

	अगर (mddev->queue) अणु
		अगर (discard_supported)
			blk_queue_flag_set(QUEUE_FLAG_DISCARD,
						mddev->queue);
		अन्यथा
			blk_queue_flag_clear(QUEUE_FLAG_DISCARD,
						  mddev->queue);
	पूर्ण
	/* need to check that every block has at least one working mirror */
	अगर (!enough(conf, -1)) अणु
		pr_err("md/raid10:%s: not enough operational mirrors.\n",
		       mdname(mddev));
		जाओ out_मुक्त_conf;
	पूर्ण

	अगर (conf->reshape_progress != MaxSector) अणु
		/* must ensure that shape change is supported */
		अगर (conf->geo.far_copies != 1 &&
		    conf->geo.far_offset == 0)
			जाओ out_मुक्त_conf;
		अगर (conf->prev.far_copies != 1 &&
		    conf->prev.far_offset == 0)
			जाओ out_मुक्त_conf;
	पूर्ण

	mddev->degraded = 0;
	क्रम (i = 0;
	     i < conf->geo.raid_disks
		     || i < conf->prev.raid_disks;
	     i++) अणु

		disk = conf->mirrors + i;

		अगर (!disk->rdev && disk->replacement) अणु
			/* The replacement is all we have - use it */
			disk->rdev = disk->replacement;
			disk->replacement = शून्य;
			clear_bit(Replacement, &disk->rdev->flags);
		पूर्ण

		अगर (!disk->rdev ||
		    !test_bit(In_sync, &disk->rdev->flags)) अणु
			disk->head_position = 0;
			mddev->degraded++;
			अगर (disk->rdev &&
			    disk->rdev->saved_raid_disk < 0)
				conf->fullsync = 1;
		पूर्ण

		अगर (disk->replacement &&
		    !test_bit(In_sync, &disk->replacement->flags) &&
		    disk->replacement->saved_raid_disk < 0) अणु
			conf->fullsync = 1;
		पूर्ण

		disk->recovery_disabled = mddev->recovery_disabled - 1;
	पूर्ण

	अगर (mddev->recovery_cp != MaxSector)
		pr_notice("md/raid10:%s: not clean -- starting background reconstruction\n",
			  mdname(mddev));
	pr_info("md/raid10:%s: active with %d out of %d devices\n",
		mdname(mddev), conf->geo.raid_disks - mddev->degraded,
		conf->geo.raid_disks);
	/*
	 * Ok, everything is just fine now
	 */
	mddev->dev_sectors = conf->dev_sectors;
	size = raid10_size(mddev, 0, 0);
	md_set_array_sectors(mddev, size);
	mddev->resync_max_sectors = size;
	set_bit(MD_FAILFAST_SUPPORTED, &mddev->flags);

	अगर (md_पूर्णांकegrity_रेजिस्टर(mddev))
		जाओ out_मुक्त_conf;

	अगर (conf->reshape_progress != MaxSector) अणु
		अचिन्हित दीर्घ beक्रमe_length, after_length;

		beक्रमe_length = ((1 << conf->prev.chunk_shअगरt) *
				 conf->prev.far_copies);
		after_length = ((1 << conf->geo.chunk_shअगरt) *
				conf->geo.far_copies);

		अगर (max(beक्रमe_length, after_length) > min_offset_dअगरf) अणु
			/* This cannot work */
			pr_warn("md/raid10: offset difference not enough to continue reshape\n");
			जाओ out_मुक्त_conf;
		पूर्ण
		conf->offset_dअगरf = min_offset_dअगरf;

		clear_bit(MD_RECOVERY_SYNC, &mddev->recovery);
		clear_bit(MD_RECOVERY_CHECK, &mddev->recovery);
		set_bit(MD_RECOVERY_RESHAPE, &mddev->recovery);
		set_bit(MD_RECOVERY_RUNNING, &mddev->recovery);
		mddev->sync_thपढ़ो = md_रेजिस्टर_thपढ़ो(md_करो_sync, mddev,
							"reshape");
		अगर (!mddev->sync_thपढ़ो)
			जाओ out_मुक्त_conf;
	पूर्ण

	वापस 0;

out_मुक्त_conf:
	md_unरेजिस्टर_thपढ़ो(&mddev->thपढ़ो);
	mempool_निकास(&conf->r10bio_pool);
	safe_put_page(conf->पंचांगppage);
	kमुक्त(conf->mirrors);
	kमुक्त(conf);
	mddev->निजी = शून्य;
out:
	वापस -EIO;
पूर्ण

अटल व्योम raid10_मुक्त(काष्ठा mddev *mddev, व्योम *priv)
अणु
	काष्ठा r10conf *conf = priv;

	mempool_निकास(&conf->r10bio_pool);
	safe_put_page(conf->पंचांगppage);
	kमुक्त(conf->mirrors);
	kमुक्त(conf->mirrors_old);
	kमुक्त(conf->mirrors_new);
	bioset_निकास(&conf->bio_split);
	kमुक्त(conf);
पूर्ण

अटल व्योम raid10_quiesce(काष्ठा mddev *mddev, पूर्णांक quiesce)
अणु
	काष्ठा r10conf *conf = mddev->निजी;

	अगर (quiesce)
		उठाओ_barrier(conf, 0);
	अन्यथा
		lower_barrier(conf);
पूर्ण

अटल पूर्णांक raid10_resize(काष्ठा mddev *mddev, sector_t sectors)
अणु
	/* Resize of 'far' arrays is not supported.
	 * For 'near' and 'offset' arrays we can set the
	 * number of sectors used to be an appropriate multiple
	 * of the chunk size.
	 * For 'offset', this is far_copies*chunksize.
	 * For 'near' the multiplier is the LCM of
	 * near_copies and raid_disks.
	 * So अगर far_copies > 1 && !far_offset, fail.
	 * Else find LCM(raid_disks, near_copy)*far_copies and
	 * multiply by chunk_size.  Then round to this number.
	 * This is mostly करोne by raid10_size()
	 */
	काष्ठा r10conf *conf = mddev->निजी;
	sector_t oldsize, size;

	अगर (mddev->reshape_position != MaxSector)
		वापस -EBUSY;

	अगर (conf->geo.far_copies > 1 && !conf->geo.far_offset)
		वापस -EINVAL;

	oldsize = raid10_size(mddev, 0, 0);
	size = raid10_size(mddev, sectors, 0);
	अगर (mddev->बाह्यal_size &&
	    mddev->array_sectors > size)
		वापस -EINVAL;
	अगर (mddev->biपंचांगap) अणु
		पूर्णांक ret = md_biपंचांगap_resize(mddev->biपंचांगap, size, 0, 0);
		अगर (ret)
			वापस ret;
	पूर्ण
	md_set_array_sectors(mddev, size);
	अगर (sectors > mddev->dev_sectors &&
	    mddev->recovery_cp > oldsize) अणु
		mddev->recovery_cp = oldsize;
		set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	पूर्ण
	calc_sectors(conf, sectors);
	mddev->dev_sectors = conf->dev_sectors;
	mddev->resync_max_sectors = size;
	वापस 0;
पूर्ण

अटल व्योम *raid10_takeover_raid0(काष्ठा mddev *mddev, sector_t size, पूर्णांक devs)
अणु
	काष्ठा md_rdev *rdev;
	काष्ठा r10conf *conf;

	अगर (mddev->degraded > 0) अणु
		pr_warn("md/raid10:%s: Error: degraded raid0!\n",
			mdname(mddev));
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	sector_भाग(size, devs);

	/* Set new parameters */
	mddev->new_level = 10;
	/* new layout: far_copies = 1, near_copies = 2 */
	mddev->new_layout = (1<<8) + 2;
	mddev->new_chunk_sectors = mddev->chunk_sectors;
	mddev->delta_disks = mddev->raid_disks;
	mddev->raid_disks *= 2;
	/* make sure it will be not marked as dirty */
	mddev->recovery_cp = MaxSector;
	mddev->dev_sectors = size;

	conf = setup_conf(mddev);
	अगर (!IS_ERR(conf)) अणु
		rdev_क्रम_each(rdev, mddev)
			अगर (rdev->raid_disk >= 0) अणु
				rdev->new_raid_disk = rdev->raid_disk * 2;
				rdev->sectors = size;
			पूर्ण
		conf->barrier = 1;
	पूर्ण

	वापस conf;
पूर्ण

अटल व्योम *raid10_takeover(काष्ठा mddev *mddev)
अणु
	काष्ठा r0conf *raid0_conf;

	/* raid10 can take over:
	 *  raid0 - providing it has only two drives
	 */
	अगर (mddev->level == 0) अणु
		/* क्रम raid0 takeover only one zone is supported */
		raid0_conf = mddev->निजी;
		अगर (raid0_conf->nr_strip_zones > 1) अणु
			pr_warn("md/raid10:%s: cannot takeover raid 0 with more than one zone.\n",
				mdname(mddev));
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		वापस raid10_takeover_raid0(mddev,
			raid0_conf->strip_zone->zone_end,
			raid0_conf->strip_zone->nb_dev);
	पूर्ण
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक raid10_check_reshape(काष्ठा mddev *mddev)
अणु
	/* Called when there is a request to change
	 * - layout (to ->new_layout)
	 * - chunk size (to ->new_chunk_sectors)
	 * - raid_disks (by delta_disks)
	 * or when trying to restart a reshape that was ongoing.
	 *
	 * We need to validate the request and possibly allocate
	 * space अगर that might be an issue later.
	 *
	 * Currently we reject any reshape of a 'far' mode array,
	 * allow chunk size to change अगर new is generally acceptable,
	 * allow raid_disks to increase, and allow
	 * a चयन between 'near' mode and 'offset' mode.
	 */
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा geom geo;

	अगर (conf->geo.far_copies != 1 && !conf->geo.far_offset)
		वापस -EINVAL;

	अगर (setup_geo(&geo, mddev, geo_start) != conf->copies)
		/* mustn't change number of copies */
		वापस -EINVAL;
	अगर (geo.far_copies > 1 && !geo.far_offset)
		/* Cannot चयन to 'far' mode */
		वापस -EINVAL;

	अगर (mddev->array_sectors & geo.chunk_mask)
			/* not factor of array size */
			वापस -EINVAL;

	अगर (!enough(conf, -1))
		वापस -EINVAL;

	kमुक्त(conf->mirrors_new);
	conf->mirrors_new = शून्य;
	अगर (mddev->delta_disks > 0) अणु
		/* allocate new 'mirrors' list */
		conf->mirrors_new =
			kसुस्मृति(mddev->raid_disks + mddev->delta_disks,
				माप(काष्ठा raid10_info),
				GFP_KERNEL);
		अगर (!conf->mirrors_new)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Need to check अगर array has failed when deciding whether to:
 *  - start an array
 *  - हटाओ non-faulty devices
 *  - add a spare
 *  - allow a reshape
 * This determination is simple when no reshape is happening.
 * However अगर there is a reshape, we need to carefully check
 * both the beक्रमe and after sections.
 * This is because some failed devices may only affect one
 * of the two sections, and some non-in_sync devices may
 * be insync in the section most affected by failed devices.
 */
अटल पूर्णांक calc_degraded(काष्ठा r10conf *conf)
अणु
	पूर्णांक degraded, degraded2;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	degraded = 0;
	/* 'prev' section first */
	क्रम (i = 0; i < conf->prev.raid_disks; i++) अणु
		काष्ठा md_rdev *rdev = rcu_dereference(conf->mirrors[i].rdev);
		अगर (!rdev || test_bit(Faulty, &rdev->flags))
			degraded++;
		अन्यथा अगर (!test_bit(In_sync, &rdev->flags))
			/* When we can reduce the number of devices in
			 * an array, this might not contribute to
			 * 'degraded'.  It करोes now.
			 */
			degraded++;
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (conf->geo.raid_disks == conf->prev.raid_disks)
		वापस degraded;
	rcu_पढ़ो_lock();
	degraded2 = 0;
	क्रम (i = 0; i < conf->geo.raid_disks; i++) अणु
		काष्ठा md_rdev *rdev = rcu_dereference(conf->mirrors[i].rdev);
		अगर (!rdev || test_bit(Faulty, &rdev->flags))
			degraded2++;
		अन्यथा अगर (!test_bit(In_sync, &rdev->flags)) अणु
			/* If reshape is increasing the number of devices,
			 * this section has alपढ़ोy been recovered, so
			 * it करोesn't contribute to degraded.
			 * अन्यथा it करोes.
			 */
			अगर (conf->geo.raid_disks <= conf->prev.raid_disks)
				degraded2++;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (degraded2 > degraded)
		वापस degraded2;
	वापस degraded;
पूर्ण

अटल पूर्णांक raid10_start_reshape(काष्ठा mddev *mddev)
अणु
	/* A 'reshape' has been requested. This commits
	 * the various 'new' fields and sets MD_RECOVER_RESHAPE
	 * This also checks अगर there are enough spares and adds them
	 * to the array.
	 * We currently require enough spares to make the final
	 * array non-degraded.  We also require that the dअगरference
	 * between old and new data_offset - on each device - is
	 * enough that we never risk over-writing.
	 */

	अचिन्हित दीर्घ beक्रमe_length, after_length;
	sector_t min_offset_dअगरf = 0;
	पूर्णांक first = 1;
	काष्ठा geom new;
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा md_rdev *rdev;
	पूर्णांक spares = 0;
	पूर्णांक ret;

	अगर (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		वापस -EBUSY;

	अगर (setup_geo(&new, mddev, geo_start) != conf->copies)
		वापस -EINVAL;

	beक्रमe_length = ((1 << conf->prev.chunk_shअगरt) *
			 conf->prev.far_copies);
	after_length = ((1 << conf->geo.chunk_shअगरt) *
			conf->geo.far_copies);

	rdev_क्रम_each(rdev, mddev) अणु
		अगर (!test_bit(In_sync, &rdev->flags)
		    && !test_bit(Faulty, &rdev->flags))
			spares++;
		अगर (rdev->raid_disk >= 0) अणु
			दीर्घ दीर्घ dअगरf = (rdev->new_data_offset
					  - rdev->data_offset);
			अगर (!mddev->reshape_backwards)
				dअगरf = -dअगरf;
			अगर (dअगरf < 0)
				dअगरf = 0;
			अगर (first || dअगरf < min_offset_dअगरf)
				min_offset_dअगरf = dअगरf;
			first = 0;
		पूर्ण
	पूर्ण

	अगर (max(beक्रमe_length, after_length) > min_offset_dअगरf)
		वापस -EINVAL;

	अगर (spares < mddev->delta_disks)
		वापस -EINVAL;

	conf->offset_dअगरf = min_offset_dअगरf;
	spin_lock_irq(&conf->device_lock);
	अगर (conf->mirrors_new) अणु
		स_नकल(conf->mirrors_new, conf->mirrors,
		       माप(काष्ठा raid10_info)*conf->prev.raid_disks);
		smp_mb();
		kमुक्त(conf->mirrors_old);
		conf->mirrors_old = conf->mirrors;
		conf->mirrors = conf->mirrors_new;
		conf->mirrors_new = शून्य;
	पूर्ण
	setup_geo(&conf->geo, mddev, geo_start);
	smp_mb();
	अगर (mddev->reshape_backwards) अणु
		sector_t size = raid10_size(mddev, 0, 0);
		अगर (size < mddev->array_sectors) अणु
			spin_unlock_irq(&conf->device_lock);
			pr_warn("md/raid10:%s: array size must be reduce before number of disks\n",
				mdname(mddev));
			वापस -EINVAL;
		पूर्ण
		mddev->resync_max_sectors = size;
		conf->reshape_progress = size;
	पूर्ण अन्यथा
		conf->reshape_progress = 0;
	conf->reshape_safe = conf->reshape_progress;
	spin_unlock_irq(&conf->device_lock);

	अगर (mddev->delta_disks && mddev->biपंचांगap) अणु
		काष्ठा mdp_superblock_1 *sb = शून्य;
		sector_t oldsize, newsize;

		oldsize = raid10_size(mddev, 0, 0);
		newsize = raid10_size(mddev, 0, conf->geo.raid_disks);

		अगर (!mddev_is_clustered(mddev)) अणु
			ret = md_biपंचांगap_resize(mddev->biपंचांगap, newsize, 0, 0);
			अगर (ret)
				जाओ पात;
			अन्यथा
				जाओ out;
		पूर्ण

		rdev_क्रम_each(rdev, mddev) अणु
			अगर (rdev->raid_disk > -1 &&
			    !test_bit(Faulty, &rdev->flags))
				sb = page_address(rdev->sb_page);
		पूर्ण

		/*
		 * some node is alपढ़ोy perक्रमming reshape, and no need to
		 * call md_biपंचांगap_resize again since it should be called when
		 * receiving BITMAP_RESIZE msg
		 */
		अगर ((sb && (le32_to_cpu(sb->feature_map) &
			    MD_FEATURE_RESHAPE_ACTIVE)) || (oldsize == newsize))
			जाओ out;

		ret = md_biपंचांगap_resize(mddev->biपंचांगap, newsize, 0, 0);
		अगर (ret)
			जाओ पात;

		ret = md_cluster_ops->resize_biपंचांगaps(mddev, newsize, oldsize);
		अगर (ret) अणु
			md_biपंचांगap_resize(mddev->biपंचांगap, oldsize, 0, 0);
			जाओ पात;
		पूर्ण
	पूर्ण
out:
	अगर (mddev->delta_disks > 0) अणु
		rdev_क्रम_each(rdev, mddev)
			अगर (rdev->raid_disk < 0 &&
			    !test_bit(Faulty, &rdev->flags)) अणु
				अगर (raid10_add_disk(mddev, rdev) == 0) अणु
					अगर (rdev->raid_disk >=
					    conf->prev.raid_disks)
						set_bit(In_sync, &rdev->flags);
					अन्यथा
						rdev->recovery_offset = 0;

					/* Failure here is OK */
					sysfs_link_rdev(mddev, rdev);
				पूर्ण
			पूर्ण अन्यथा अगर (rdev->raid_disk >= conf->prev.raid_disks
				   && !test_bit(Faulty, &rdev->flags)) अणु
				/* This is a spare that was manually added */
				set_bit(In_sync, &rdev->flags);
			पूर्ण
	पूर्ण
	/* When a reshape changes the number of devices,
	 * ->degraded is measured against the larger of the
	 * pre and  post numbers.
	 */
	spin_lock_irq(&conf->device_lock);
	mddev->degraded = calc_degraded(conf);
	spin_unlock_irq(&conf->device_lock);
	mddev->raid_disks = conf->geo.raid_disks;
	mddev->reshape_position = conf->reshape_progress;
	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);

	clear_bit(MD_RECOVERY_SYNC, &mddev->recovery);
	clear_bit(MD_RECOVERY_CHECK, &mddev->recovery);
	clear_bit(MD_RECOVERY_DONE, &mddev->recovery);
	set_bit(MD_RECOVERY_RESHAPE, &mddev->recovery);
	set_bit(MD_RECOVERY_RUNNING, &mddev->recovery);

	mddev->sync_thपढ़ो = md_रेजिस्टर_thपढ़ो(md_करो_sync, mddev,
						"reshape");
	अगर (!mddev->sync_thपढ़ो) अणु
		ret = -EAGAIN;
		जाओ पात;
	पूर्ण
	conf->reshape_checkpoपूर्णांक = jअगरfies;
	md_wakeup_thपढ़ो(mddev->sync_thपढ़ो);
	md_new_event(mddev);
	वापस 0;

पात:
	mddev->recovery = 0;
	spin_lock_irq(&conf->device_lock);
	conf->geo = conf->prev;
	mddev->raid_disks = conf->geo.raid_disks;
	rdev_क्रम_each(rdev, mddev)
		rdev->new_data_offset = rdev->data_offset;
	smp_wmb();
	conf->reshape_progress = MaxSector;
	conf->reshape_safe = MaxSector;
	mddev->reshape_position = MaxSector;
	spin_unlock_irq(&conf->device_lock);
	वापस ret;
पूर्ण

/* Calculate the last device-address that could contain
 * any block from the chunk that includes the array-address 's'
 * and report the next address.
 * i.e. the address वापसed will be chunk-aligned and after
 * any data that is in the chunk containing 's'.
 */
अटल sector_t last_dev_address(sector_t s, काष्ठा geom *geo)
अणु
	s = (s | geo->chunk_mask) + 1;
	s >>= geo->chunk_shअगरt;
	s *= geo->near_copies;
	s = DIV_ROUND_UP_SECTOR_T(s, geo->raid_disks);
	s *= geo->far_copies;
	s <<= geo->chunk_shअगरt;
	वापस s;
पूर्ण

/* Calculate the first device-address that could contain
 * any block from the chunk that includes the array-address 's'.
 * This too will be the start of a chunk
 */
अटल sector_t first_dev_address(sector_t s, काष्ठा geom *geo)
अणु
	s >>= geo->chunk_shअगरt;
	s *= geo->near_copies;
	sector_भाग(s, geo->raid_disks);
	s *= geo->far_copies;
	s <<= geo->chunk_shअगरt;
	वापस s;
पूर्ण

अटल sector_t reshape_request(काष्ठा mddev *mddev, sector_t sector_nr,
				पूर्णांक *skipped)
अणु
	/* We simply copy at most one chunk (smallest of old and new)
	 * at a समय, possibly less अगर that exceeds RESYNC_PAGES,
	 * or we hit a bad block or something.
	 * This might mean we छोड़ो क्रम normal IO in the middle of
	 * a chunk, but that is not a problem as mddev->reshape_position
	 * can record any location.
	 *
	 * If we will want to ग_लिखो to a location that isn't
	 * yet recorded as 'safe' (i.e. in metadata on disk) then
	 * we need to flush all reshape requests and update the metadata.
	 *
	 * When reshaping क्रमwards (e.g. to more devices), we पूर्णांकerpret
	 * 'safe' as the earliest block which might not have been copied
	 * करोwn yet.  We भागide this by previous stripe size and multiply
	 * by previous stripe length to get lowest device offset that we
	 * cannot ग_लिखो to yet.
	 * We पूर्णांकerpret 'sector_nr' as an address that we want to ग_लिखो to.
	 * From this we use last_device_address() to find where we might
	 * ग_लिखो to, and first_device_address on the  'safe' position.
	 * If this 'next' write position is after the 'safe' position,
	 * we must update the metadata to increase the 'safe' position.
	 *
	 * When reshaping backwards, we round in the opposite direction
	 * and perक्रमm the reverse test:  next ग_लिखो position must not be
	 * less than current safe position.
	 *
	 * In all this the minimum dअगरference in data offsets
	 * (conf->offset_dअगरf - always positive) allows a bit of slack,
	 * so next can be after 'safe', but not by more than offset_dअगरf
	 *
	 * We need to prepare all the bios here beक्रमe we start any IO
	 * to ensure the size we choose is acceptable to all devices.
	 * The means one क्रम each copy क्रम ग_लिखो-out and an extra one क्रम
	 * पढ़ो-in.
	 * We store the पढ़ो-in bio in ->master_bio and the others in
	 * ->devs[x].bio and ->devs[x].repl_bio.
	 */
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा r10bio *r10_bio;
	sector_t next, safe, last;
	पूर्णांक max_sectors;
	पूर्णांक nr_sectors;
	पूर्णांक s;
	काष्ठा md_rdev *rdev;
	पूर्णांक need_flush = 0;
	काष्ठा bio *blist;
	काष्ठा bio *bio, *पढ़ो_bio;
	पूर्णांक sectors_करोne = 0;
	काष्ठा page **pages;

	अगर (sector_nr == 0) अणु
		/* If restarting in the middle, skip the initial sectors */
		अगर (mddev->reshape_backwards &&
		    conf->reshape_progress < raid10_size(mddev, 0, 0)) अणु
			sector_nr = (raid10_size(mddev, 0, 0)
				     - conf->reshape_progress);
		पूर्ण अन्यथा अगर (!mddev->reshape_backwards &&
			   conf->reshape_progress > 0)
			sector_nr = conf->reshape_progress;
		अगर (sector_nr) अणु
			mddev->curr_resync_completed = sector_nr;
			sysfs_notअगरy_dirent_safe(mddev->sysfs_completed);
			*skipped = 1;
			वापस sector_nr;
		पूर्ण
	पूर्ण

	/* We करोn't use sector_nr to track where we are up to
	 * as that करोesn't work well क्रम ->reshape_backwards.
	 * So just use ->reshape_progress.
	 */
	अगर (mddev->reshape_backwards) अणु
		/* 'next' is the earliest device address that we might
		 * ग_लिखो to क्रम this chunk in the new layout
		 */
		next = first_dev_address(conf->reshape_progress - 1,
					 &conf->geo);

		/* 'safe' is the last device address that we might पढ़ो from
		 * in the old layout after a restart
		 */
		safe = last_dev_address(conf->reshape_safe - 1,
					&conf->prev);

		अगर (next + conf->offset_dअगरf < safe)
			need_flush = 1;

		last = conf->reshape_progress - 1;
		sector_nr = last & ~(sector_t)(conf->geo.chunk_mask
					       & conf->prev.chunk_mask);
		अगर (sector_nr + RESYNC_SECTORS < last)
			sector_nr = last + 1 - RESYNC_SECTORS;
	पूर्ण अन्यथा अणु
		/* 'next' is after the last device address that we
		 * might ग_लिखो to क्रम this chunk in the new layout
		 */
		next = last_dev_address(conf->reshape_progress, &conf->geo);

		/* 'safe' is the earliest device address that we might
		 * पढ़ो from in the old layout after a restart
		 */
		safe = first_dev_address(conf->reshape_safe, &conf->prev);

		/* Need to update metadata अगर 'next' might be beyond 'safe'
		 * as that would possibly corrupt data
		 */
		अगर (next > safe + conf->offset_dअगरf)
			need_flush = 1;

		sector_nr = conf->reshape_progress;
		last  = sector_nr | (conf->geo.chunk_mask
				     & conf->prev.chunk_mask);

		अगर (sector_nr + RESYNC_SECTORS <= last)
			last = sector_nr + RESYNC_SECTORS - 1;
	पूर्ण

	अगर (need_flush ||
	    समय_after(jअगरfies, conf->reshape_checkpoपूर्णांक + 10*HZ)) अणु
		/* Need to update reshape_position in metadata */
		रुको_barrier(conf);
		mddev->reshape_position = conf->reshape_progress;
		अगर (mddev->reshape_backwards)
			mddev->curr_resync_completed = raid10_size(mddev, 0, 0)
				- conf->reshape_progress;
		अन्यथा
			mddev->curr_resync_completed = conf->reshape_progress;
		conf->reshape_checkpoपूर्णांक = jअगरfies;
		set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		रुको_event(mddev->sb_रुको, mddev->sb_flags == 0 ||
			   test_bit(MD_RECOVERY_INTR, &mddev->recovery));
		अगर (test_bit(MD_RECOVERY_INTR, &mddev->recovery)) अणु
			allow_barrier(conf);
			वापस sectors_करोne;
		पूर्ण
		conf->reshape_safe = mddev->reshape_position;
		allow_barrier(conf);
	पूर्ण

	उठाओ_barrier(conf, 0);
पढ़ो_more:
	/* Now schedule पढ़ोs क्रम blocks from sector_nr to last */
	r10_bio = raid10_alloc_init_r10buf(conf);
	r10_bio->state = 0;
	उठाओ_barrier(conf, 1);
	atomic_set(&r10_bio->reमुख्यing, 0);
	r10_bio->mddev = mddev;
	r10_bio->sector = sector_nr;
	set_bit(R10BIO_IsReshape, &r10_bio->state);
	r10_bio->sectors = last - sector_nr + 1;
	rdev = पढ़ो_balance(conf, r10_bio, &max_sectors);
	BUG_ON(!test_bit(R10BIO_Previous, &r10_bio->state));

	अगर (!rdev) अणु
		/* Cannot पढ़ो from here, so need to record bad blocks
		 * on all the target devices.
		 */
		// FIXME
		mempool_मुक्त(r10_bio, &conf->r10buf_pool);
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
		वापस sectors_करोne;
	पूर्ण

	पढ़ो_bio = bio_alloc_bioset(GFP_KERNEL, RESYNC_PAGES, &mddev->bio_set);

	bio_set_dev(पढ़ो_bio, rdev->bdev);
	पढ़ो_bio->bi_iter.bi_sector = (r10_bio->devs[r10_bio->पढ़ो_slot].addr
			       + rdev->data_offset);
	पढ़ो_bio->bi_निजी = r10_bio;
	पढ़ो_bio->bi_end_io = end_reshape_पढ़ो;
	bio_set_op_attrs(पढ़ो_bio, REQ_OP_READ, 0);
	r10_bio->master_bio = पढ़ो_bio;
	r10_bio->पढ़ो_slot = r10_bio->devs[r10_bio->पढ़ो_slot].devnum;

	/*
	 * Broadcast RESYNC message to other nodes, so all nodes would not
	 * ग_लिखो to the region to aव्योम conflict.
	*/
	अगर (mddev_is_clustered(mddev) && conf->cluster_sync_high <= sector_nr) अणु
		काष्ठा mdp_superblock_1 *sb = शून्य;
		पूर्णांक sb_reshape_pos = 0;

		conf->cluster_sync_low = sector_nr;
		conf->cluster_sync_high = sector_nr + CLUSTER_RESYNC_WINDOW_SECTORS;
		sb = page_address(rdev->sb_page);
		अगर (sb) अणु
			sb_reshape_pos = le64_to_cpu(sb->reshape_position);
			/*
			 * Set cluster_sync_low again अगर next address क्रम array
			 * reshape is less than cluster_sync_low. Since we can't
			 * update cluster_sync_low until it has finished reshape.
			 */
			अगर (sb_reshape_pos < conf->cluster_sync_low)
				conf->cluster_sync_low = sb_reshape_pos;
		पूर्ण

		md_cluster_ops->resync_info_update(mddev, conf->cluster_sync_low,
							  conf->cluster_sync_high);
	पूर्ण

	/* Now find the locations in the new layout */
	__raid10_find_phys(&conf->geo, r10_bio);

	blist = पढ़ो_bio;
	पढ़ो_bio->bi_next = शून्य;

	rcu_पढ़ो_lock();
	क्रम (s = 0; s < conf->copies*2; s++) अणु
		काष्ठा bio *b;
		पूर्णांक d = r10_bio->devs[s/2].devnum;
		काष्ठा md_rdev *rdev2;
		अगर (s&1) अणु
			rdev2 = rcu_dereference(conf->mirrors[d].replacement);
			b = r10_bio->devs[s/2].repl_bio;
		पूर्ण अन्यथा अणु
			rdev2 = rcu_dereference(conf->mirrors[d].rdev);
			b = r10_bio->devs[s/2].bio;
		पूर्ण
		अगर (!rdev2 || test_bit(Faulty, &rdev2->flags))
			जारी;

		bio_set_dev(b, rdev2->bdev);
		b->bi_iter.bi_sector = r10_bio->devs[s/2].addr +
			rdev2->new_data_offset;
		b->bi_end_io = end_reshape_ग_लिखो;
		bio_set_op_attrs(b, REQ_OP_WRITE, 0);
		b->bi_next = blist;
		blist = b;
	पूर्ण

	/* Now add as many pages as possible to all of these bios. */

	nr_sectors = 0;
	pages = get_resync_pages(r10_bio->devs[0].bio)->pages;
	क्रम (s = 0 ; s < max_sectors; s += PAGE_SIZE >> 9) अणु
		काष्ठा page *page = pages[s / (PAGE_SIZE >> 9)];
		पूर्णांक len = (max_sectors - s) << 9;
		अगर (len > PAGE_SIZE)
			len = PAGE_SIZE;
		क्रम (bio = blist; bio ; bio = bio->bi_next) अणु
			/*
			 * won't fail because the vec table is big enough
			 * to hold all these pages
			 */
			bio_add_page(bio, page, len, 0);
		पूर्ण
		sector_nr += len >> 9;
		nr_sectors += len >> 9;
	पूर्ण
	rcu_पढ़ो_unlock();
	r10_bio->sectors = nr_sectors;

	/* Now submit the पढ़ो */
	md_sync_acct_bio(पढ़ो_bio, r10_bio->sectors);
	atomic_inc(&r10_bio->reमुख्यing);
	पढ़ो_bio->bi_next = शून्य;
	submit_bio_noacct(पढ़ो_bio);
	sectors_करोne += nr_sectors;
	अगर (sector_nr <= last)
		जाओ पढ़ो_more;

	lower_barrier(conf);

	/* Now that we have करोne the whole section we can
	 * update reshape_progress
	 */
	अगर (mddev->reshape_backwards)
		conf->reshape_progress -= sectors_करोne;
	अन्यथा
		conf->reshape_progress += sectors_करोne;

	वापस sectors_करोne;
पूर्ण

अटल व्योम end_reshape_request(काष्ठा r10bio *r10_bio);
अटल पूर्णांक handle_reshape_पढ़ो_error(काष्ठा mddev *mddev,
				     काष्ठा r10bio *r10_bio);
अटल व्योम reshape_request_ग_लिखो(काष्ठा mddev *mddev, काष्ठा r10bio *r10_bio)
अणु
	/* Reshape पढ़ो completed.  Hopefully we have a block
	 * to ग_लिखो out.
	 * If we got a पढ़ो error then we करो sync 1-page पढ़ोs from
	 * अन्यथाwhere until we find the data - or give up.
	 */
	काष्ठा r10conf *conf = mddev->निजी;
	पूर्णांक s;

	अगर (!test_bit(R10BIO_Uptodate, &r10_bio->state))
		अगर (handle_reshape_पढ़ो_error(mddev, r10_bio) < 0) अणु
			/* Reshape has been पातed */
			md_करोne_sync(mddev, r10_bio->sectors, 0);
			वापस;
		पूर्ण

	/* We definitely have the data in the pages, schedule the
	 * ग_लिखोs.
	 */
	atomic_set(&r10_bio->reमुख्यing, 1);
	क्रम (s = 0; s < conf->copies*2; s++) अणु
		काष्ठा bio *b;
		पूर्णांक d = r10_bio->devs[s/2].devnum;
		काष्ठा md_rdev *rdev;
		rcu_पढ़ो_lock();
		अगर (s&1) अणु
			rdev = rcu_dereference(conf->mirrors[d].replacement);
			b = r10_bio->devs[s/2].repl_bio;
		पूर्ण अन्यथा अणु
			rdev = rcu_dereference(conf->mirrors[d].rdev);
			b = r10_bio->devs[s/2].bio;
		पूर्ण
		अगर (!rdev || test_bit(Faulty, &rdev->flags)) अणु
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण
		atomic_inc(&rdev->nr_pending);
		rcu_पढ़ो_unlock();
		md_sync_acct_bio(b, r10_bio->sectors);
		atomic_inc(&r10_bio->reमुख्यing);
		b->bi_next = शून्य;
		submit_bio_noacct(b);
	पूर्ण
	end_reshape_request(r10_bio);
पूर्ण

अटल व्योम end_reshape(काष्ठा r10conf *conf)
अणु
	अगर (test_bit(MD_RECOVERY_INTR, &conf->mddev->recovery))
		वापस;

	spin_lock_irq(&conf->device_lock);
	conf->prev = conf->geo;
	md_finish_reshape(conf->mddev);
	smp_wmb();
	conf->reshape_progress = MaxSector;
	conf->reshape_safe = MaxSector;
	spin_unlock_irq(&conf->device_lock);

	अगर (conf->mddev->queue)
		raid10_set_io_opt(conf);
	conf->fullsync = 0;
पूर्ण

अटल व्योम raid10_update_reshape_pos(काष्ठा mddev *mddev)
अणु
	काष्ठा r10conf *conf = mddev->निजी;
	sector_t lo, hi;

	md_cluster_ops->resync_info_get(mddev, &lo, &hi);
	अगर (((mddev->reshape_position <= hi) && (mddev->reshape_position >= lo))
	    || mddev->reshape_position == MaxSector)
		conf->reshape_progress = mddev->reshape_position;
	अन्यथा
		WARN_ON_ONCE(1);
पूर्ण

अटल पूर्णांक handle_reshape_पढ़ो_error(काष्ठा mddev *mddev,
				     काष्ठा r10bio *r10_bio)
अणु
	/* Use sync पढ़ोs to get the blocks from somewhere अन्यथा */
	पूर्णांक sectors = r10_bio->sectors;
	काष्ठा r10conf *conf = mddev->निजी;
	काष्ठा r10bio *r10b;
	पूर्णांक slot = 0;
	पूर्णांक idx = 0;
	काष्ठा page **pages;

	r10b = kदो_स्मृति(काष्ठा_size(r10b, devs, conf->copies), GFP_NOIO);
	अगर (!r10b) अणु
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
		वापस -ENOMEM;
	पूर्ण

	/* reshape IOs share pages from .devs[0].bio */
	pages = get_resync_pages(r10_bio->devs[0].bio)->pages;

	r10b->sector = r10_bio->sector;
	__raid10_find_phys(&conf->prev, r10b);

	जबतक (sectors) अणु
		पूर्णांक s = sectors;
		पूर्णांक success = 0;
		पूर्णांक first_slot = slot;

		अगर (s > (PAGE_SIZE >> 9))
			s = PAGE_SIZE >> 9;

		rcu_पढ़ो_lock();
		जबतक (!success) अणु
			पूर्णांक d = r10b->devs[slot].devnum;
			काष्ठा md_rdev *rdev = rcu_dereference(conf->mirrors[d].rdev);
			sector_t addr;
			अगर (rdev == शून्य ||
			    test_bit(Faulty, &rdev->flags) ||
			    !test_bit(In_sync, &rdev->flags))
				जाओ failed;

			addr = r10b->devs[slot].addr + idx * PAGE_SIZE;
			atomic_inc(&rdev->nr_pending);
			rcu_पढ़ो_unlock();
			success = sync_page_io(rdev,
					       addr,
					       s << 9,
					       pages[idx],
					       REQ_OP_READ, 0, false);
			rdev_dec_pending(rdev, mddev);
			rcu_पढ़ो_lock();
			अगर (success)
				अवरोध;
		failed:
			slot++;
			अगर (slot >= conf->copies)
				slot = 0;
			अगर (slot == first_slot)
				अवरोध;
		पूर्ण
		rcu_पढ़ो_unlock();
		अगर (!success) अणु
			/* couldn't पढ़ो this block, must give up */
			set_bit(MD_RECOVERY_INTR,
				&mddev->recovery);
			kमुक्त(r10b);
			वापस -EIO;
		पूर्ण
		sectors -= s;
		idx++;
	पूर्ण
	kमुक्त(r10b);
	वापस 0;
पूर्ण

अटल व्योम end_reshape_ग_लिखो(काष्ठा bio *bio)
अणु
	काष्ठा r10bio *r10_bio = get_resync_r10bio(bio);
	काष्ठा mddev *mddev = r10_bio->mddev;
	काष्ठा r10conf *conf = mddev->निजी;
	पूर्णांक d;
	पूर्णांक slot;
	पूर्णांक repl;
	काष्ठा md_rdev *rdev = शून्य;

	d = find_bio_disk(conf, r10_bio, bio, &slot, &repl);
	अगर (repl)
		rdev = conf->mirrors[d].replacement;
	अगर (!rdev) अणु
		smp_mb();
		rdev = conf->mirrors[d].rdev;
	पूर्ण

	अगर (bio->bi_status) अणु
		/* FIXME should record badblock */
		md_error(mddev, rdev);
	पूर्ण

	rdev_dec_pending(rdev, mddev);
	end_reshape_request(r10_bio);
पूर्ण

अटल व्योम end_reshape_request(काष्ठा r10bio *r10_bio)
अणु
	अगर (!atomic_dec_and_test(&r10_bio->reमुख्यing))
		वापस;
	md_करोne_sync(r10_bio->mddev, r10_bio->sectors, 1);
	bio_put(r10_bio->master_bio);
	put_buf(r10_bio);
पूर्ण

अटल व्योम raid10_finish_reshape(काष्ठा mddev *mddev)
अणु
	काष्ठा r10conf *conf = mddev->निजी;

	अगर (test_bit(MD_RECOVERY_INTR, &mddev->recovery))
		वापस;

	अगर (mddev->delta_disks > 0) अणु
		अगर (mddev->recovery_cp > mddev->resync_max_sectors) अणु
			mddev->recovery_cp = mddev->resync_max_sectors;
			set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
		पूर्ण
		mddev->resync_max_sectors = mddev->array_sectors;
	पूर्ण अन्यथा अणु
		पूर्णांक d;
		rcu_पढ़ो_lock();
		क्रम (d = conf->geo.raid_disks ;
		     d < conf->geo.raid_disks - mddev->delta_disks;
		     d++) अणु
			काष्ठा md_rdev *rdev = rcu_dereference(conf->mirrors[d].rdev);
			अगर (rdev)
				clear_bit(In_sync, &rdev->flags);
			rdev = rcu_dereference(conf->mirrors[d].replacement);
			अगर (rdev)
				clear_bit(In_sync, &rdev->flags);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
	mddev->layout = mddev->new_layout;
	mddev->chunk_sectors = 1 << conf->geo.chunk_shअगरt;
	mddev->reshape_position = MaxSector;
	mddev->delta_disks = 0;
	mddev->reshape_backwards = 0;
पूर्ण

अटल काष्ठा md_personality raid10_personality =
अणु
	.name		= "raid10",
	.level		= 10,
	.owner		= THIS_MODULE,
	.make_request	= raid10_make_request,
	.run		= raid10_run,
	.मुक्त		= raid10_मुक्त,
	.status		= raid10_status,
	.error_handler	= raid10_error,
	.hot_add_disk	= raid10_add_disk,
	.hot_हटाओ_disk= raid10_हटाओ_disk,
	.spare_active	= raid10_spare_active,
	.sync_request	= raid10_sync_request,
	.quiesce	= raid10_quiesce,
	.size		= raid10_size,
	.resize		= raid10_resize,
	.takeover	= raid10_takeover,
	.check_reshape	= raid10_check_reshape,
	.start_reshape	= raid10_start_reshape,
	.finish_reshape	= raid10_finish_reshape,
	.update_reshape_pos = raid10_update_reshape_pos,
पूर्ण;

अटल पूर्णांक __init raid_init(व्योम)
अणु
	वापस रेजिस्टर_md_personality(&raid10_personality);
पूर्ण

अटल व्योम raid_निकास(व्योम)
अणु
	unरेजिस्टर_md_personality(&raid10_personality);
पूर्ण

module_init(raid_init);
module_निकास(raid_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("RAID10 (striped mirror) personality for MD");
MODULE_ALIAS("md-personality-9"); /* RAID10 */
MODULE_ALIAS("md-raid10");
MODULE_ALIAS("md-level-10");

module_param(max_queued_requests, पूर्णांक, S_IRUGO|S_IWUSR);
