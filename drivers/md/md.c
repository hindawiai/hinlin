<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   md.c : Multiple Devices driver क्रम Linux
     Copyright (C) 1998, 1999, 2000 Ingo Molnar

     completely rewritten, based on the MD driver code from Marc Zyngier

   Changes:

   - RAID-1/RAID-5 extensions by Miguel de Icaza, Gadi Oxman, Ingo Molnar
   - RAID-6 extensions by H. Peter Anvin <hpa@zytor.com>
   - boot support क्रम linear and striped mode by Harald Hoyer <HarryH@Royal.Net>
   - kerneld support by Boris Tobotras <boris@xtalk.msk.su>
   - kmod support by: Cyrus Durgin
   - RAID0 bugfixes: Mark Anthony Lisher <markal@iname.com>
   - Devfs support by Riअक्षरd Gooch <rgooch@atnf.csiro.au>

   - lots of fixes and improvements to the RAID1/RAID5 and generic
     RAID code (such as request based resynchronization):

     Neil Brown <neilb@cse.unsw.edu.au>.

   - persistent biपंचांगap code
     Copyright (C) 2003-2004, Paul Clements, SteelEye Technology, Inc.


   Errors, Warnings, etc.
   Please use:
     pr_crit() क्रम error conditions that risk data loss
     pr_err() क्रम error conditions that are unexpected, like an IO error
         or पूर्णांकernal inconsistency
     pr_warn() क्रम error conditions that could have been predicated, like
         adding a device to an array when it has incompatible metadata
     pr_info() क्रम every पूर्णांकeresting, very rare events, like an array starting
         or stopping, or resync starting or stopping
     pr_debug() क्रम everything अन्यथा.

*/

#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/badblocks.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/hdreg.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/module.h>
#समावेश <linux/reboot.h>
#समावेश <linux/file.h>
#समावेश <linux/compat.h>
#समावेश <linux/delay.h>
#समावेश <linux/raid/md_p.h>
#समावेश <linux/raid/md_u.h>
#समावेश <linux/raid/detect.h>
#समावेश <linux/slab.h>
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/part_स्थिति.स>

#समावेश <trace/events/block.h>
#समावेश "md.h"
#समावेश "md-bitmap.h"
#समावेश "md-cluster.h"

/* pers_list is a list of रेजिस्टरed personalities रक्षित
 * by pers_lock.
 * pers_lock करोes extra service to protect accesses to
 * mddev->thपढ़ो when the mutex cannot be held.
 */
अटल LIST_HEAD(pers_list);
अटल DEFINE_SPINLOCK(pers_lock);

अटल काष्ठा kobj_type md_ktype;

काष्ठा md_cluster_operations *md_cluster_ops;
EXPORT_SYMBOL(md_cluster_ops);
अटल काष्ठा module *md_cluster_mod;

अटल DECLARE_WAIT_QUEUE_HEAD(resync_रुको);
अटल काष्ठा workqueue_काष्ठा *md_wq;
अटल काष्ठा workqueue_काष्ठा *md_misc_wq;
अटल काष्ठा workqueue_काष्ठा *md_rdev_misc_wq;

अटल पूर्णांक हटाओ_and_add_spares(काष्ठा mddev *mddev,
				 काष्ठा md_rdev *this);
अटल व्योम mddev_detach(काष्ठा mddev *mddev);

/*
 * Default number of पढ़ो corrections we'll attempt on an rdev
 * beक्रमe ejecting it from the array. We भागide the पढ़ो error
 * count by 2 क्रम every hour elapsed between पढ़ो errors.
 */
#घोषणा MD_DEFAULT_MAX_CORRECTED_READ_ERRORS 20
/* Default safemode delay: 200 msec */
#घोषणा DEFAULT_SAFEMODE_DELAY ((200 * HZ)/1000 +1)
/*
 * Current RAID-1,4,5 parallel reस्थिरruction 'guaranteed speed limit'
 * is 1000 KB/sec, so the extra प्रणाली load करोes not show up that much.
 * Increase it अगर you want to have more _guaranteed_ speed. Note that
 * the RAID driver will use the maximum available bandwidth अगर the IO
 * subप्रणाली is idle. There is also an 'absolute maximum' reस्थिरruction
 * speed limit - in हाल reस्थिरruction slows करोwn your प्रणाली despite
 * idle IO detection.
 *
 * you can change it via /proc/sys/dev/raid/speed_limit_min and _max.
 * or /sys/block/mdX/md/sync_speed_अणुmin,maxपूर्ण
 */

अटल पूर्णांक sysctl_speed_limit_min = 1000;
अटल पूर्णांक sysctl_speed_limit_max = 200000;
अटल अंतरभूत पूर्णांक speed_min(काष्ठा mddev *mddev)
अणु
	वापस mddev->sync_speed_min ?
		mddev->sync_speed_min : sysctl_speed_limit_min;
पूर्ण

अटल अंतरभूत पूर्णांक speed_max(काष्ठा mddev *mddev)
अणु
	वापस mddev->sync_speed_max ?
		mddev->sync_speed_max : sysctl_speed_limit_max;
पूर्ण

अटल व्योम rdev_uninit_serial(काष्ठा md_rdev *rdev)
अणु
	अगर (!test_and_clear_bit(CollisionCheck, &rdev->flags))
		वापस;

	kvमुक्त(rdev->serial);
	rdev->serial = शून्य;
पूर्ण

अटल व्योम rdevs_uninit_serial(काष्ठा mddev *mddev)
अणु
	काष्ठा md_rdev *rdev;

	rdev_क्रम_each(rdev, mddev)
		rdev_uninit_serial(rdev);
पूर्ण

अटल पूर्णांक rdev_init_serial(काष्ठा md_rdev *rdev)
अणु
	/* serial_nums equals with BARRIER_BUCKETS_NR */
	पूर्णांक i, serial_nums = 1 << ((PAGE_SHIFT - ilog2(माप(atomic_t))));
	काष्ठा serial_in_rdev *serial = शून्य;

	अगर (test_bit(CollisionCheck, &rdev->flags))
		वापस 0;

	serial = kvदो_स्मृति(माप(काष्ठा serial_in_rdev) * serial_nums,
			  GFP_KERNEL);
	अगर (!serial)
		वापस -ENOMEM;

	क्रम (i = 0; i < serial_nums; i++) अणु
		काष्ठा serial_in_rdev *serial_पंचांगp = &serial[i];

		spin_lock_init(&serial_पंचांगp->serial_lock);
		serial_पंचांगp->serial_rb = RB_ROOT_CACHED;
		init_रुकोqueue_head(&serial_पंचांगp->serial_io_रुको);
	पूर्ण

	rdev->serial = serial;
	set_bit(CollisionCheck, &rdev->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक rdevs_init_serial(काष्ठा mddev *mddev)
अणु
	काष्ठा md_rdev *rdev;
	पूर्णांक ret = 0;

	rdev_क्रम_each(rdev, mddev) अणु
		ret = rdev_init_serial(rdev);
		अगर (ret)
			अवरोध;
	पूर्ण

	/* Free all resources अगर pool is not existed */
	अगर (ret && !mddev->serial_info_pool)
		rdevs_uninit_serial(mddev);

	वापस ret;
पूर्ण

/*
 * rdev needs to enable serial stuffs अगर it meets the conditions:
 * 1. it is multi-queue device flaged with ग_लिखोmostly.
 * 2. the ग_लिखो-behind mode is enabled.
 */
अटल पूर्णांक rdev_need_serial(काष्ठा md_rdev *rdev)
अणु
	वापस (rdev && rdev->mddev->biपंचांगap_info.max_ग_लिखो_behind > 0 &&
		rdev->bdev->bd_disk->queue->nr_hw_queues != 1 &&
		test_bit(WriteMostly, &rdev->flags));
पूर्ण

/*
 * Init resource क्रम rdev(s), then create serial_info_pool अगर:
 * 1. rdev is the first device which वापस true from rdev_enable_serial.
 * 2. rdev is शून्य, means we want to enable serialization क्रम all rdevs.
 */
व्योम mddev_create_serial_pool(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev,
			      bool is_suspend)
अणु
	पूर्णांक ret = 0;

	अगर (rdev && !rdev_need_serial(rdev) &&
	    !test_bit(CollisionCheck, &rdev->flags))
		वापस;

	अगर (!is_suspend)
		mddev_suspend(mddev);

	अगर (!rdev)
		ret = rdevs_init_serial(mddev);
	अन्यथा
		ret = rdev_init_serial(rdev);
	अगर (ret)
		जाओ पात;

	अगर (mddev->serial_info_pool == शून्य) अणु
		/*
		 * alपढ़ोy in meदो_स्मृति noio context by
		 * mddev_suspend()
		 */
		mddev->serial_info_pool =
			mempool_create_kदो_स्मृति_pool(NR_SERIAL_INFOS,
						माप(काष्ठा serial_info));
		अगर (!mddev->serial_info_pool) अणु
			rdevs_uninit_serial(mddev);
			pr_err("can't alloc memory pool for serialization\n");
		पूर्ण
	पूर्ण

पात:
	अगर (!is_suspend)
		mddev_resume(mddev);
पूर्ण

/*
 * Free resource from rdev(s), and destroy serial_info_pool under conditions:
 * 1. rdev is the last device flaged with CollisionCheck.
 * 2. when biपंचांगap is destroyed जबतक policy is not enabled.
 * 3. क्रम disable policy, the pool is destroyed only when no rdev needs it.
 */
व्योम mddev_destroy_serial_pool(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev,
			       bool is_suspend)
अणु
	अगर (rdev && !test_bit(CollisionCheck, &rdev->flags))
		वापस;

	अगर (mddev->serial_info_pool) अणु
		काष्ठा md_rdev *temp;
		पूर्णांक num = 0; /* used to track अगर other rdevs need the pool */

		अगर (!is_suspend)
			mddev_suspend(mddev);
		rdev_क्रम_each(temp, mddev) अणु
			अगर (!rdev) अणु
				अगर (!mddev->serialize_policy ||
				    !rdev_need_serial(temp))
					rdev_uninit_serial(temp);
				अन्यथा
					num++;
			पूर्ण अन्यथा अगर (temp != rdev &&
				   test_bit(CollisionCheck, &temp->flags))
				num++;
		पूर्ण

		अगर (rdev)
			rdev_uninit_serial(rdev);

		अगर (num)
			pr_info("The mempool could be used by other devices\n");
		अन्यथा अणु
			mempool_destroy(mddev->serial_info_pool);
			mddev->serial_info_pool = शून्य;
		पूर्ण
		अगर (!is_suspend)
			mddev_resume(mddev);
	पूर्ण
पूर्ण

अटल काष्ठा ctl_table_header *raid_table_header;

अटल काष्ठा ctl_table raid_table[] = अणु
	अणु
		.procname	= "speed_limit_min",
		.data		= &sysctl_speed_limit_min,
		.maxlen		= माप(पूर्णांक),
		.mode		= S_IRUGO|S_IWUSR,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "speed_limit_max",
		.data		= &sysctl_speed_limit_max,
		.maxlen		= माप(पूर्णांक),
		.mode		= S_IRUGO|S_IWUSR,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table raid_dir_table[] = अणु
	अणु
		.procname	= "raid",
		.maxlen		= 0,
		.mode		= S_IRUGO|S_IXUGO,
		.child		= raid_table,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table raid_root_table[] = अणु
	अणु
		.procname	= "dev",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= raid_dir_table,
	पूर्ण,
	अणु  पूर्ण
पूर्ण;

अटल पूर्णांक start_पढ़ोonly;

/*
 * The original mechanism क्रम creating an md device is to create
 * a device node in /dev and to खोलो it.  This causes races with device-बंद.
 * The preferred method is to ग_लिखो to the "new_array" module parameter.
 * This can aव्योम races.
 * Setting create_on_खोलो to false disables the original mechanism
 * so all the races disappear.
 */
अटल bool create_on_खोलो = true;

/*
 * We have a प्रणाली wide 'event count' that is incremented
 * on any 'interesting' event, and पढ़ोers of /proc/mdstat
 * can use 'poll' or 'select' to find out when the event
 * count increases.
 *
 * Events are:
 *  start array, stop array, error, add device, हटाओ device,
 *  start build, activate spare
 */
अटल DECLARE_WAIT_QUEUE_HEAD(md_event_रुकोers);
अटल atomic_t md_event_count;
व्योम md_new_event(काष्ठा mddev *mddev)
अणु
	atomic_inc(&md_event_count);
	wake_up(&md_event_रुकोers);
पूर्ण
EXPORT_SYMBOL_GPL(md_new_event);

/*
 * Enables to iterate over all existing md arrays
 * all_mddevs_lock protects this list.
 */
अटल LIST_HEAD(all_mddevs);
अटल DEFINE_SPINLOCK(all_mddevs_lock);

/*
 * iterates through all used mddevs in the प्रणाली.
 * We take care to grab the all_mddevs_lock whenever navigating
 * the list, and to always hold a refcount when unlocked.
 * Any code which अवरोधs out of this loop जबतक own
 * a reference to the current mddev and must mddev_put it.
 */
#घोषणा क्रम_each_mddev(_mddev,_पंचांगp)					\
									\
	क्रम ((अणु spin_lock(&all_mddevs_lock);				\
		_पंचांगp = all_mddevs.next;					\
		_mddev = शून्य;पूर्ण);					\
	     (अणु अगर (_पंचांगp != &all_mddevs)				\
			mddev_get(list_entry(_पंचांगp, काष्ठा mddev, all_mddevs));\
		spin_unlock(&all_mddevs_lock);				\
		अगर (_mddev) mddev_put(_mddev);				\
		_mddev = list_entry(_पंचांगp, काष्ठा mddev, all_mddevs);	\
		_पंचांगp != &all_mddevs;पूर्ण);					\
	     (अणु spin_lock(&all_mddevs_lock);				\
		_पंचांगp = _पंचांगp->next;पूर्ण)					\
		)

/* Rather than calling directly पूर्णांकo the personality make_request function,
 * IO requests come here first so that we can check अगर the device is
 * being suspended pending a reconfiguration.
 * We hold a refcount over the call to ->make_request.  By the समय that
 * call has finished, the bio has been linked पूर्णांकo some पूर्णांकernal काष्ठाure
 * and so is visible to ->quiesce(), so we करोn't need the refcount any more.
 */
अटल bool is_suspended(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	अगर (mddev->suspended)
		वापस true;
	अगर (bio_data_dir(bio) != WRITE)
		वापस false;
	अगर (mddev->suspend_lo >= mddev->suspend_hi)
		वापस false;
	अगर (bio->bi_iter.bi_sector >= mddev->suspend_hi)
		वापस false;
	अगर (bio_end_sector(bio) < mddev->suspend_lo)
		वापस false;
	वापस true;
पूर्ण

व्योम md_handle_request(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
check_suspended:
	rcu_पढ़ो_lock();
	अगर (is_suspended(mddev, bio)) अणु
		DEFINE_WAIT(__रुको);
		क्रम (;;) अणु
			prepare_to_रुको(&mddev->sb_रुको, &__रुको,
					TASK_UNINTERRUPTIBLE);
			अगर (!is_suspended(mddev, bio))
				अवरोध;
			rcu_पढ़ो_unlock();
			schedule();
			rcu_पढ़ो_lock();
		पूर्ण
		finish_रुको(&mddev->sb_रुको, &__रुको);
	पूर्ण
	atomic_inc(&mddev->active_io);
	rcu_पढ़ो_unlock();

	अगर (!mddev->pers->make_request(mddev, bio)) अणु
		atomic_dec(&mddev->active_io);
		wake_up(&mddev->sb_रुको);
		जाओ check_suspended;
	पूर्ण

	अगर (atomic_dec_and_test(&mddev->active_io) && mddev->suspended)
		wake_up(&mddev->sb_रुको);
पूर्ण
EXPORT_SYMBOL(md_handle_request);

काष्ठा md_io अणु
	काष्ठा mddev *mddev;
	bio_end_io_t *orig_bi_end_io;
	व्योम *orig_bi_निजी;
	काष्ठा block_device *orig_bi_bdev;
	अचिन्हित दीर्घ start_समय;
पूर्ण;

अटल व्योम md_end_io(काष्ठा bio *bio)
अणु
	काष्ठा md_io *md_io = bio->bi_निजी;
	काष्ठा mddev *mddev = md_io->mddev;

	bio_end_io_acct_remapped(bio, md_io->start_समय, md_io->orig_bi_bdev);

	bio->bi_end_io = md_io->orig_bi_end_io;
	bio->bi_निजी = md_io->orig_bi_निजी;

	mempool_मुक्त(md_io, &mddev->md_io_pool);

	अगर (bio->bi_end_io)
		bio->bi_end_io(bio);
पूर्ण

अटल blk_qc_t md_submit_bio(काष्ठा bio *bio)
अणु
	स्थिर पूर्णांक rw = bio_data_dir(bio);
	काष्ठा mddev *mddev = bio->bi_bdev->bd_disk->निजी_data;

	अगर (mddev == शून्य || mddev->pers == शून्य) अणु
		bio_io_error(bio);
		वापस BLK_QC_T_NONE;
	पूर्ण

	अगर (unlikely(test_bit(MD_BROKEN, &mddev->flags)) && (rw == WRITE)) अणु
		bio_io_error(bio);
		वापस BLK_QC_T_NONE;
	पूर्ण

	blk_queue_split(&bio);

	अगर (mddev->ro == 1 && unlikely(rw == WRITE)) अणु
		अगर (bio_sectors(bio) != 0)
			bio->bi_status = BLK_STS_IOERR;
		bio_endio(bio);
		वापस BLK_QC_T_NONE;
	पूर्ण

	अगर (bio->bi_end_io != md_end_io) अणु
		काष्ठा md_io *md_io;

		md_io = mempool_alloc(&mddev->md_io_pool, GFP_NOIO);
		md_io->mddev = mddev;
		md_io->orig_bi_end_io = bio->bi_end_io;
		md_io->orig_bi_निजी = bio->bi_निजी;
		md_io->orig_bi_bdev = bio->bi_bdev;

		bio->bi_end_io = md_end_io;
		bio->bi_निजी = md_io;

		md_io->start_समय = bio_start_io_acct(bio);
	पूर्ण

	/* bio could be mergeable after passing to underlayer */
	bio->bi_opf &= ~REQ_NOMERGE;

	md_handle_request(mddev, bio);

	वापस BLK_QC_T_NONE;
पूर्ण

/* mddev_suspend makes sure no new requests are submitted
 * to the device, and that any requests that have been submitted
 * are completely handled.
 * Once mddev_detach() is called and completes, the module will be
 * completely unused.
 */
व्योम mddev_suspend(काष्ठा mddev *mddev)
अणु
	WARN_ON_ONCE(mddev->thपढ़ो && current == mddev->thपढ़ो->tsk);
	lockdep_निश्चित_held(&mddev->reconfig_mutex);
	अगर (mddev->suspended++)
		वापस;
	synchronize_rcu();
	wake_up(&mddev->sb_रुको);
	set_bit(MD_ALLOW_SB_UPDATE, &mddev->flags);
	smp_mb__after_atomic();
	रुको_event(mddev->sb_रुको, atomic_पढ़ो(&mddev->active_io) == 0);
	mddev->pers->quiesce(mddev, 1);
	clear_bit_unlock(MD_ALLOW_SB_UPDATE, &mddev->flags);
	रुको_event(mddev->sb_रुको, !test_bit(MD_UPDATING_SB, &mddev->flags));

	del_समयr_sync(&mddev->safemode_समयr);
	/* restrict memory reclaim I/O during raid array is suspend */
	mddev->noio_flag = meदो_स्मृति_noio_save();
पूर्ण
EXPORT_SYMBOL_GPL(mddev_suspend);

व्योम mddev_resume(काष्ठा mddev *mddev)
अणु
	/* entred the meदो_स्मृति scope from mddev_suspend() */
	meदो_स्मृति_noio_restore(mddev->noio_flag);
	lockdep_निश्चित_held(&mddev->reconfig_mutex);
	अगर (--mddev->suspended)
		वापस;
	wake_up(&mddev->sb_रुको);
	mddev->pers->quiesce(mddev, 0);

	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	md_wakeup_thपढ़ो(mddev->thपढ़ो);
	md_wakeup_thपढ़ो(mddev->sync_thपढ़ो); /* possibly kick off a reshape */
पूर्ण
EXPORT_SYMBOL_GPL(mddev_resume);

/*
 * Generic flush handling क्रम md
 */

अटल व्योम md_end_flush(काष्ठा bio *bio)
अणु
	काष्ठा md_rdev *rdev = bio->bi_निजी;
	काष्ठा mddev *mddev = rdev->mddev;

	rdev_dec_pending(rdev, mddev);

	अगर (atomic_dec_and_test(&mddev->flush_pending)) अणु
		/* The pre-request flush has finished */
		queue_work(md_wq, &mddev->flush_work);
	पूर्ण
	bio_put(bio);
पूर्ण

अटल व्योम md_submit_flush_data(काष्ठा work_काष्ठा *ws);

अटल व्योम submit_flushes(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा mddev *mddev = container_of(ws, काष्ठा mddev, flush_work);
	काष्ठा md_rdev *rdev;

	mddev->start_flush = kसमय_get_bootसमय();
	INIT_WORK(&mddev->flush_work, md_submit_flush_data);
	atomic_set(&mddev->flush_pending, 1);
	rcu_पढ़ो_lock();
	rdev_क्रम_each_rcu(rdev, mddev)
		अगर (rdev->raid_disk >= 0 &&
		    !test_bit(Faulty, &rdev->flags)) अणु
			/* Take two references, one is dropped
			 * when request finishes, one after
			 * we reclaim rcu_पढ़ो_lock
			 */
			काष्ठा bio *bi;
			atomic_inc(&rdev->nr_pending);
			atomic_inc(&rdev->nr_pending);
			rcu_पढ़ो_unlock();
			bi = bio_alloc_bioset(GFP_NOIO, 0, &mddev->bio_set);
			bi->bi_end_io = md_end_flush;
			bi->bi_निजी = rdev;
			bio_set_dev(bi, rdev->bdev);
			bi->bi_opf = REQ_OP_WRITE | REQ_PREFLUSH;
			atomic_inc(&mddev->flush_pending);
			submit_bio(bi);
			rcu_पढ़ो_lock();
			rdev_dec_pending(rdev, mddev);
		पूर्ण
	rcu_पढ़ो_unlock();
	अगर (atomic_dec_and_test(&mddev->flush_pending))
		queue_work(md_wq, &mddev->flush_work);
पूर्ण

अटल व्योम md_submit_flush_data(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा mddev *mddev = container_of(ws, काष्ठा mddev, flush_work);
	काष्ठा bio *bio = mddev->flush_bio;

	/*
	 * must reset flush_bio beक्रमe calling पूर्णांकo md_handle_request to aव्योम a
	 * deadlock, because other bios passed md_handle_request suspend check
	 * could रुको क्रम this and below md_handle_request could रुको क्रम those
	 * bios because of suspend check
	 */
	spin_lock_irq(&mddev->lock);
	mddev->prev_flush_start = mddev->start_flush;
	mddev->flush_bio = शून्य;
	spin_unlock_irq(&mddev->lock);
	wake_up(&mddev->sb_रुको);

	अगर (bio->bi_iter.bi_size == 0) अणु
		/* an empty barrier - all करोne */
		bio_endio(bio);
	पूर्ण अन्यथा अणु
		bio->bi_opf &= ~REQ_PREFLUSH;
		md_handle_request(mddev, bio);
	पूर्ण
पूर्ण

/*
 * Manages consolidation of flushes and submitting any flushes needed क्रम
 * a bio with REQ_PREFLUSH.  Returns true अगर the bio is finished or is
 * being finished in another context.  Returns false अगर the flushing is
 * complete but still needs the I/O portion of the bio to be processed.
 */
bool md_flush_request(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	kसमय_प्रकार req_start = kसमय_get_bootसमय();
	spin_lock_irq(&mddev->lock);
	/* flush requests रुको until ongoing flush completes,
	 * hence coalescing all the pending requests.
	 */
	रुको_event_lock_irq(mddev->sb_रुको,
			    !mddev->flush_bio ||
			    kसमय_beक्रमe(req_start, mddev->prev_flush_start),
			    mddev->lock);
	/* new request after previous flush is completed */
	अगर (kसमय_after(req_start, mddev->prev_flush_start)) अणु
		WARN_ON(mddev->flush_bio);
		mddev->flush_bio = bio;
		bio = शून्य;
	पूर्ण
	spin_unlock_irq(&mddev->lock);

	अगर (!bio) अणु
		INIT_WORK(&mddev->flush_work, submit_flushes);
		queue_work(md_wq, &mddev->flush_work);
	पूर्ण अन्यथा अणु
		/* flush was perक्रमmed क्रम some other bio जबतक we रुकोed. */
		अगर (bio->bi_iter.bi_size == 0)
			/* an empty barrier - all करोne */
			bio_endio(bio);
		अन्यथा अणु
			bio->bi_opf &= ~REQ_PREFLUSH;
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL(md_flush_request);

अटल अंतरभूत काष्ठा mddev *mddev_get(काष्ठा mddev *mddev)
अणु
	atomic_inc(&mddev->active);
	वापस mddev;
पूर्ण

अटल व्योम mddev_delayed_delete(काष्ठा work_काष्ठा *ws);

अटल व्योम mddev_put(काष्ठा mddev *mddev)
अणु
	अगर (!atomic_dec_and_lock(&mddev->active, &all_mddevs_lock))
		वापस;
	अगर (!mddev->raid_disks && list_empty(&mddev->disks) &&
	    mddev->स_समय == 0 && !mddev->hold_active) अणु
		/* Array is not configured at all, and not held active,
		 * so destroy it */
		list_del_init(&mddev->all_mddevs);

		/*
		 * Call queue_work inside the spinlock so that
		 * flush_workqueue() after mddev_find will succeed in रुकोing
		 * क्रम the work to be करोne.
		 */
		INIT_WORK(&mddev->del_work, mddev_delayed_delete);
		queue_work(md_misc_wq, &mddev->del_work);
	पूर्ण
	spin_unlock(&all_mddevs_lock);
पूर्ण

अटल व्योम md_safemode_समयout(काष्ठा समयr_list *t);

व्योम mddev_init(काष्ठा mddev *mddev)
अणु
	kobject_init(&mddev->kobj, &md_ktype);
	mutex_init(&mddev->खोलो_mutex);
	mutex_init(&mddev->reconfig_mutex);
	mutex_init(&mddev->biपंचांगap_info.mutex);
	INIT_LIST_HEAD(&mddev->disks);
	INIT_LIST_HEAD(&mddev->all_mddevs);
	समयr_setup(&mddev->safemode_समयr, md_safemode_समयout, 0);
	atomic_set(&mddev->active, 1);
	atomic_set(&mddev->खोलोers, 0);
	atomic_set(&mddev->active_io, 0);
	spin_lock_init(&mddev->lock);
	atomic_set(&mddev->flush_pending, 0);
	init_रुकोqueue_head(&mddev->sb_रुको);
	init_रुकोqueue_head(&mddev->recovery_रुको);
	mddev->reshape_position = MaxSector;
	mddev->reshape_backwards = 0;
	mddev->last_sync_action = "none";
	mddev->resync_min = 0;
	mddev->resync_max = MaxSector;
	mddev->level = LEVEL_NONE;
पूर्ण
EXPORT_SYMBOL_GPL(mddev_init);

अटल काष्ठा mddev *mddev_find_locked(dev_t unit)
अणु
	काष्ठा mddev *mddev;

	list_क्रम_each_entry(mddev, &all_mddevs, all_mddevs)
		अगर (mddev->unit == unit)
			वापस mddev;

	वापस शून्य;
पूर्ण

/* find an unused unit number */
अटल dev_t mddev_alloc_unit(व्योम)
अणु
	अटल पूर्णांक next_minor = 512;
	पूर्णांक start = next_minor;
	bool is_मुक्त = 0;
	dev_t dev = 0;

	जबतक (!is_मुक्त) अणु
		dev = MKDEV(MD_MAJOR, next_minor);
		next_minor++;
		अगर (next_minor > MINORMASK)
			next_minor = 0;
		अगर (next_minor == start)
			वापस 0;		/* Oh dear, all in use. */
		is_मुक्त = !mddev_find_locked(dev);
	पूर्ण

	वापस dev;
पूर्ण

अटल काष्ठा mddev *mddev_find(dev_t unit)
अणु
	काष्ठा mddev *mddev;

	अगर (MAJOR(unit) != MD_MAJOR)
		unit &= ~((1 << MdpMinorShअगरt) - 1);

	spin_lock(&all_mddevs_lock);
	mddev = mddev_find_locked(unit);
	अगर (mddev)
		mddev_get(mddev);
	spin_unlock(&all_mddevs_lock);

	वापस mddev;
पूर्ण

अटल काष्ठा mddev *mddev_alloc(dev_t unit)
अणु
	काष्ठा mddev *new;
	पूर्णांक error;

	अगर (unit && MAJOR(unit) != MD_MAJOR)
		unit &= ~((1 << MdpMinorShअगरt) - 1);

	new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (!new)
		वापस ERR_PTR(-ENOMEM);
	mddev_init(new);

	spin_lock(&all_mddevs_lock);
	अगर (unit) अणु
		error = -EEXIST;
		अगर (mddev_find_locked(unit))
			जाओ out_मुक्त_new;
		new->unit = unit;
		अगर (MAJOR(unit) == MD_MAJOR)
			new->md_minor = MINOR(unit);
		अन्यथा
			new->md_minor = MINOR(unit) >> MdpMinorShअगरt;
		new->hold_active = UNTIL_IOCTL;
	पूर्ण अन्यथा अणु
		error = -ENODEV;
		new->unit = mddev_alloc_unit();
		अगर (!new->unit)
			जाओ out_मुक्त_new;
		new->md_minor = MINOR(new->unit);
		new->hold_active = UNTIL_STOP;
	पूर्ण

	list_add(&new->all_mddevs, &all_mddevs);
	spin_unlock(&all_mddevs_lock);
	वापस new;
out_मुक्त_new:
	spin_unlock(&all_mddevs_lock);
	kमुक्त(new);
	वापस ERR_PTR(error);
पूर्ण

अटल काष्ठा attribute_group md_redundancy_group;

व्योम mddev_unlock(काष्ठा mddev *mddev)
अणु
	अगर (mddev->to_हटाओ) अणु
		/* These cannot be हटाओd under reconfig_mutex as
		 * an access to the files will try to take reconfig_mutex
		 * जबतक holding the file unremovable, which leads to
		 * a deadlock.
		 * So hold set sysfs_active जबतक the हटाओ in happeing,
		 * and anything अन्यथा which might set ->to_हटाओ or my
		 * otherwise change the sysfs namespace will fail with
		 * -EBUSY अगर sysfs_active is still set.
		 * We set sysfs_active under reconfig_mutex and अन्यथाwhere
		 * test it under the same mutex to ensure its correct value
		 * is seen.
		 */
		काष्ठा attribute_group *to_हटाओ = mddev->to_हटाओ;
		mddev->to_हटाओ = शून्य;
		mddev->sysfs_active = 1;
		mutex_unlock(&mddev->reconfig_mutex);

		अगर (mddev->kobj.sd) अणु
			अगर (to_हटाओ != &md_redundancy_group)
				sysfs_हटाओ_group(&mddev->kobj, to_हटाओ);
			अगर (mddev->pers == शून्य ||
			    mddev->pers->sync_request == शून्य) अणु
				sysfs_हटाओ_group(&mddev->kobj, &md_redundancy_group);
				अगर (mddev->sysfs_action)
					sysfs_put(mddev->sysfs_action);
				अगर (mddev->sysfs_completed)
					sysfs_put(mddev->sysfs_completed);
				अगर (mddev->sysfs_degraded)
					sysfs_put(mddev->sysfs_degraded);
				mddev->sysfs_action = शून्य;
				mddev->sysfs_completed = शून्य;
				mddev->sysfs_degraded = शून्य;
			पूर्ण
		पूर्ण
		mddev->sysfs_active = 0;
	पूर्ण अन्यथा
		mutex_unlock(&mddev->reconfig_mutex);

	/* As we've dropped the mutex we need a spinlock to
	 * make sure the thपढ़ो करोesn't disappear
	 */
	spin_lock(&pers_lock);
	md_wakeup_thपढ़ो(mddev->thपढ़ो);
	wake_up(&mddev->sb_रुको);
	spin_unlock(&pers_lock);
पूर्ण
EXPORT_SYMBOL_GPL(mddev_unlock);

काष्ठा md_rdev *md_find_rdev_nr_rcu(काष्ठा mddev *mddev, पूर्णांक nr)
अणु
	काष्ठा md_rdev *rdev;

	rdev_क्रम_each_rcu(rdev, mddev)
		अगर (rdev->desc_nr == nr)
			वापस rdev;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(md_find_rdev_nr_rcu);

अटल काष्ठा md_rdev *find_rdev(काष्ठा mddev *mddev, dev_t dev)
अणु
	काष्ठा md_rdev *rdev;

	rdev_क्रम_each(rdev, mddev)
		अगर (rdev->bdev->bd_dev == dev)
			वापस rdev;

	वापस शून्य;
पूर्ण

काष्ठा md_rdev *md_find_rdev_rcu(काष्ठा mddev *mddev, dev_t dev)
अणु
	काष्ठा md_rdev *rdev;

	rdev_क्रम_each_rcu(rdev, mddev)
		अगर (rdev->bdev->bd_dev == dev)
			वापस rdev;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(md_find_rdev_rcu);

अटल काष्ठा md_personality *find_pers(पूर्णांक level, अक्षर *clevel)
अणु
	काष्ठा md_personality *pers;
	list_क्रम_each_entry(pers, &pers_list, list) अणु
		अगर (level != LEVEL_NONE && pers->level == level)
			वापस pers;
		अगर (म_भेद(pers->name, clevel)==0)
			वापस pers;
	पूर्ण
	वापस शून्य;
पूर्ण

/* वापस the offset of the super block in 512byte sectors */
अटल अंतरभूत sector_t calc_dev_sboffset(काष्ठा md_rdev *rdev)
अणु
	sector_t num_sectors = i_size_पढ़ो(rdev->bdev->bd_inode) / 512;
	वापस MD_NEW_SIZE_SECTORS(num_sectors);
पूर्ण

अटल पूर्णांक alloc_disk_sb(काष्ठा md_rdev *rdev)
अणु
	rdev->sb_page = alloc_page(GFP_KERNEL);
	अगर (!rdev->sb_page)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम md_rdev_clear(काष्ठा md_rdev *rdev)
अणु
	अगर (rdev->sb_page) अणु
		put_page(rdev->sb_page);
		rdev->sb_loaded = 0;
		rdev->sb_page = शून्य;
		rdev->sb_start = 0;
		rdev->sectors = 0;
	पूर्ण
	अगर (rdev->bb_page) अणु
		put_page(rdev->bb_page);
		rdev->bb_page = शून्य;
	पूर्ण
	badblocks_निकास(&rdev->badblocks);
पूर्ण
EXPORT_SYMBOL_GPL(md_rdev_clear);

अटल व्योम super_written(काष्ठा bio *bio)
अणु
	काष्ठा md_rdev *rdev = bio->bi_निजी;
	काष्ठा mddev *mddev = rdev->mddev;

	अगर (bio->bi_status) अणु
		pr_err("md: %s gets error=%d\n", __func__,
		       blk_status_to_त्रुटि_सं(bio->bi_status));
		md_error(mddev, rdev);
		अगर (!test_bit(Faulty, &rdev->flags)
		    && (bio->bi_opf & MD_FAILFAST)) अणु
			set_bit(MD_SB_NEED_REWRITE, &mddev->sb_flags);
			set_bit(LastDev, &rdev->flags);
		पूर्ण
	पूर्ण अन्यथा
		clear_bit(LastDev, &rdev->flags);

	अगर (atomic_dec_and_test(&mddev->pending_ग_लिखोs))
		wake_up(&mddev->sb_रुको);
	rdev_dec_pending(rdev, mddev);
	bio_put(bio);
पूर्ण

व्योम md_super_ग_लिखो(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev,
		   sector_t sector, पूर्णांक size, काष्ठा page *page)
अणु
	/* ग_लिखो first size bytes of page to sector of rdev
	 * Increment mddev->pending_ग_लिखोs beक्रमe वापसing
	 * and decrement it on completion, waking up sb_रुको
	 * अगर zero is reached.
	 * If an error occurred, call md_error
	 */
	काष्ठा bio *bio;
	पूर्णांक ff = 0;

	अगर (!page)
		वापस;

	अगर (test_bit(Faulty, &rdev->flags))
		वापस;

	bio = bio_alloc_bioset(GFP_NOIO, 1, &mddev->sync_set);

	atomic_inc(&rdev->nr_pending);

	bio_set_dev(bio, rdev->meta_bdev ? rdev->meta_bdev : rdev->bdev);
	bio->bi_iter.bi_sector = sector;
	bio_add_page(bio, page, size, 0);
	bio->bi_निजी = rdev;
	bio->bi_end_io = super_written;

	अगर (test_bit(MD_FAILFAST_SUPPORTED, &mddev->flags) &&
	    test_bit(FailFast, &rdev->flags) &&
	    !test_bit(LastDev, &rdev->flags))
		ff = MD_FAILFAST;
	bio->bi_opf = REQ_OP_WRITE | REQ_SYNC | REQ_PREFLUSH | REQ_FUA | ff;

	atomic_inc(&mddev->pending_ग_लिखोs);
	submit_bio(bio);
पूर्ण

पूर्णांक md_super_रुको(काष्ठा mddev *mddev)
अणु
	/* रुको क्रम all superblock ग_लिखोs that were scheduled to complete */
	रुको_event(mddev->sb_रुको, atomic_पढ़ो(&mddev->pending_ग_लिखोs)==0);
	अगर (test_and_clear_bit(MD_SB_NEED_REWRITE, &mddev->sb_flags))
		वापस -EAGAIN;
	वापस 0;
पूर्ण

पूर्णांक sync_page_io(काष्ठा md_rdev *rdev, sector_t sector, पूर्णांक size,
		 काष्ठा page *page, पूर्णांक op, पूर्णांक op_flags, bool metadata_op)
अणु
	काष्ठा bio bio;
	काष्ठा bio_vec bvec;

	bio_init(&bio, &bvec, 1);

	अगर (metadata_op && rdev->meta_bdev)
		bio_set_dev(&bio, rdev->meta_bdev);
	अन्यथा
		bio_set_dev(&bio, rdev->bdev);
	bio.bi_opf = op | op_flags;
	अगर (metadata_op)
		bio.bi_iter.bi_sector = sector + rdev->sb_start;
	अन्यथा अगर (rdev->mddev->reshape_position != MaxSector &&
		 (rdev->mddev->reshape_backwards ==
		  (sector >= rdev->mddev->reshape_position)))
		bio.bi_iter.bi_sector = sector + rdev->new_data_offset;
	अन्यथा
		bio.bi_iter.bi_sector = sector + rdev->data_offset;
	bio_add_page(&bio, page, size, 0);

	submit_bio_रुको(&bio);

	वापस !bio.bi_status;
पूर्ण
EXPORT_SYMBOL_GPL(sync_page_io);

अटल पूर्णांक पढ़ो_disk_sb(काष्ठा md_rdev *rdev, पूर्णांक size)
अणु
	अक्षर b[BDEVNAME_SIZE];

	अगर (rdev->sb_loaded)
		वापस 0;

	अगर (!sync_page_io(rdev, 0, size, rdev->sb_page, REQ_OP_READ, 0, true))
		जाओ fail;
	rdev->sb_loaded = 1;
	वापस 0;

fail:
	pr_err("md: disabled device %s, could not read superblock.\n",
	       bdevname(rdev->bdev,b));
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक md_uuid_equal(mdp_super_t *sb1, mdp_super_t *sb2)
अणु
	वापस	sb1->set_uuid0 == sb2->set_uuid0 &&
		sb1->set_uuid1 == sb2->set_uuid1 &&
		sb1->set_uuid2 == sb2->set_uuid2 &&
		sb1->set_uuid3 == sb2->set_uuid3;
पूर्ण

अटल पूर्णांक md_sb_equal(mdp_super_t *sb1, mdp_super_t *sb2)
अणु
	पूर्णांक ret;
	mdp_super_t *पंचांगp1, *पंचांगp2;

	पंचांगp1 = kदो_स्मृति(माप(*पंचांगp1),GFP_KERNEL);
	पंचांगp2 = kदो_स्मृति(माप(*पंचांगp2),GFP_KERNEL);

	अगर (!पंचांगp1 || !पंचांगp2) अणु
		ret = 0;
		जाओ पात;
	पूर्ण

	*पंचांगp1 = *sb1;
	*पंचांगp2 = *sb2;

	/*
	 * nr_disks is not स्थिरant
	 */
	पंचांगp1->nr_disks = 0;
	पंचांगp2->nr_disks = 0;

	ret = (स_भेद(पंचांगp1, पंचांगp2, MD_SB_GENERIC_CONSTANT_WORDS * 4) == 0);
पात:
	kमुक्त(पंचांगp1);
	kमुक्त(पंचांगp2);
	वापस ret;
पूर्ण

अटल u32 md_csum_fold(u32 csum)
अणु
	csum = (csum & 0xffff) + (csum >> 16);
	वापस (csum & 0xffff) + (csum >> 16);
पूर्ण

अटल अचिन्हित पूर्णांक calc_sb_csum(mdp_super_t *sb)
अणु
	u64 newcsum = 0;
	u32 *sb32 = (u32*)sb;
	पूर्णांक i;
	अचिन्हित पूर्णांक disk_csum, csum;

	disk_csum = sb->sb_csum;
	sb->sb_csum = 0;

	क्रम (i = 0; i < MD_SB_BYTES/4 ; i++)
		newcsum += sb32[i];
	csum = (newcsum & 0xffffffff) + (newcsum>>32);

#अगर_घोषित CONFIG_ALPHA
	/* This used to use csum_partial, which was wrong क्रम several
	 * reasons including that dअगरferent results are वापसed on
	 * dअगरferent architectures.  It isn't critical that we get exactly
	 * the same वापस value as beक्रमe (we always csum_fold beक्रमe
	 * testing, and that हटाओs any dअगरferences).  However as we
	 * know that csum_partial always वापसed a 16bit value on
	 * alphas, करो a fold to maximise conक्रमmity to previous behaviour.
	 */
	sb->sb_csum = md_csum_fold(disk_csum);
#अन्यथा
	sb->sb_csum = disk_csum;
#पूर्ण_अगर
	वापस csum;
पूर्ण

/*
 * Handle superblock details.
 * We want to be able to handle multiple superblock क्रमmats
 * so we have a common पूर्णांकerface to them all, and an array of
 * dअगरferent handlers.
 * We rely on user-space to ग_लिखो the initial superblock, and support
 * पढ़ोing and updating of superblocks.
 * Interface methods are:
 *   पूर्णांक load_super(काष्ठा md_rdev *dev, काष्ठा md_rdev *refdev, पूर्णांक minor_version)
 *      loads and validates a superblock on dev.
 *      अगर refdev != शून्य, compare superblocks on both devices
 *    Return:
 *      0 - dev has a superblock that is compatible with refdev
 *      1 - dev has a superblock that is compatible and newer than refdev
 *          so dev should be used as the refdev in future
 *     -EINVAL superblock incompatible or invalid
 *     -othererror e.g. -EIO
 *
 *   पूर्णांक validate_super(काष्ठा mddev *mddev, काष्ठा md_rdev *dev)
 *      Verअगरy that dev is acceptable पूर्णांकo mddev.
 *       The first समय, mddev->raid_disks will be 0, and data from
 *       dev should be merged in.  Subsequent calls check that dev
 *       is new enough.  Return 0 or -EINVAL
 *
 *   व्योम sync_super(काष्ठा mddev *mddev, काष्ठा md_rdev *dev)
 *     Update the superblock क्रम rdev with data in mddev
 *     This करोes not ग_लिखो to disc.
 *
 */

काष्ठा super_type  अणु
	अक्षर		    *name;
	काष्ठा module	    *owner;
	पूर्णांक		    (*load_super)(काष्ठा md_rdev *rdev,
					  काष्ठा md_rdev *refdev,
					  पूर्णांक minor_version);
	पूर्णांक		    (*validate_super)(काष्ठा mddev *mddev,
					      काष्ठा md_rdev *rdev);
	व्योम		    (*sync_super)(काष्ठा mddev *mddev,
					  काष्ठा md_rdev *rdev);
	अचिन्हित दीर्घ दीर्घ  (*rdev_size_change)(काष्ठा md_rdev *rdev,
						sector_t num_sectors);
	पूर्णांक		    (*allow_new_offset)(काष्ठा md_rdev *rdev,
						अचिन्हित दीर्घ दीर्घ new_offset);
पूर्ण;

/*
 * Check that the given mddev has no biपंचांगap.
 *
 * This function is called from the run method of all personalities that करो not
 * support biपंचांगaps. It prपूर्णांकs an error message and वापसs non-zero अगर mddev
 * has a biपंचांगap. Otherwise, it वापसs 0.
 *
 */
पूर्णांक md_check_no_biपंचांगap(काष्ठा mddev *mddev)
अणु
	अगर (!mddev->biपंचांगap_info.file && !mddev->biपंचांगap_info.offset)
		वापस 0;
	pr_warn("%s: bitmaps are not supported for %s\n",
		mdname(mddev), mddev->pers->name);
	वापस 1;
पूर्ण
EXPORT_SYMBOL(md_check_no_biपंचांगap);

/*
 * load_super क्रम 0.90.0
 */
अटल पूर्णांक super_90_load(काष्ठा md_rdev *rdev, काष्ठा md_rdev *refdev, पूर्णांक minor_version)
अणु
	अक्षर b[BDEVNAME_SIZE], b2[BDEVNAME_SIZE];
	mdp_super_t *sb;
	पूर्णांक ret;
	bool spare_disk = true;

	/*
	 * Calculate the position of the superblock (512byte sectors),
	 * it's at the end of the disk.
	 *
	 * It also happens to be a multiple of 4Kb.
	 */
	rdev->sb_start = calc_dev_sboffset(rdev);

	ret = पढ़ो_disk_sb(rdev, MD_SB_BYTES);
	अगर (ret)
		वापस ret;

	ret = -EINVAL;

	bdevname(rdev->bdev, b);
	sb = page_address(rdev->sb_page);

	अगर (sb->md_magic != MD_SB_MAGIC) अणु
		pr_warn("md: invalid raid superblock magic on %s\n", b);
		जाओ पात;
	पूर्ण

	अगर (sb->major_version != 0 ||
	    sb->minor_version < 90 ||
	    sb->minor_version > 91) अणु
		pr_warn("Bad version number %d.%d on %s\n",
			sb->major_version, sb->minor_version, b);
		जाओ पात;
	पूर्ण

	अगर (sb->raid_disks <= 0)
		जाओ पात;

	अगर (md_csum_fold(calc_sb_csum(sb)) != md_csum_fold(sb->sb_csum)) अणु
		pr_warn("md: invalid superblock checksum on %s\n", b);
		जाओ पात;
	पूर्ण

	rdev->preferred_minor = sb->md_minor;
	rdev->data_offset = 0;
	rdev->new_data_offset = 0;
	rdev->sb_size = MD_SB_BYTES;
	rdev->badblocks.shअगरt = -1;

	अगर (sb->level == LEVEL_MULTIPATH)
		rdev->desc_nr = -1;
	अन्यथा
		rdev->desc_nr = sb->this_disk.number;

	/* not spare disk, or LEVEL_MULTIPATH */
	अगर (sb->level == LEVEL_MULTIPATH ||
		(rdev->desc_nr >= 0 &&
		 rdev->desc_nr < MD_SB_DISKS &&
		 sb->disks[rdev->desc_nr].state &
		 ((1<<MD_DISK_SYNC) | (1 << MD_DISK_ACTIVE))))
		spare_disk = false;

	अगर (!refdev) अणु
		अगर (!spare_disk)
			ret = 1;
		अन्यथा
			ret = 0;
	पूर्ण अन्यथा अणु
		__u64 ev1, ev2;
		mdp_super_t *refsb = page_address(refdev->sb_page);
		अगर (!md_uuid_equal(refsb, sb)) अणु
			pr_warn("md: %s has different UUID to %s\n",
				b, bdevname(refdev->bdev,b2));
			जाओ पात;
		पूर्ण
		अगर (!md_sb_equal(refsb, sb)) अणु
			pr_warn("md: %s has same UUID but different superblock to %s\n",
				b, bdevname(refdev->bdev, b2));
			जाओ पात;
		पूर्ण
		ev1 = md_event(sb);
		ev2 = md_event(refsb);

		अगर (!spare_disk && ev1 > ev2)
			ret = 1;
		अन्यथा
			ret = 0;
	पूर्ण
	rdev->sectors = rdev->sb_start;
	/* Limit to 4TB as metadata cannot record more than that.
	 * (not needed क्रम Linear and RAID0 as metadata करोesn't
	 * record this size)
	 */
	अगर ((u64)rdev->sectors >= (2ULL << 32) && sb->level >= 1)
		rdev->sectors = (sector_t)(2ULL << 32) - 2;

	अगर (rdev->sectors < ((sector_t)sb->size) * 2 && sb->level >= 1)
		/* "this cannot possibly happen" ... */
		ret = -EINVAL;

 पात:
	वापस ret;
पूर्ण

/*
 * validate_super क्रम 0.90.0
 */
अटल पूर्णांक super_90_validate(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	mdp_disk_t *desc;
	mdp_super_t *sb = page_address(rdev->sb_page);
	__u64 ev1 = md_event(sb);

	rdev->raid_disk = -1;
	clear_bit(Faulty, &rdev->flags);
	clear_bit(In_sync, &rdev->flags);
	clear_bit(Biपंचांगap_sync, &rdev->flags);
	clear_bit(WriteMostly, &rdev->flags);

	अगर (mddev->raid_disks == 0) अणु
		mddev->major_version = 0;
		mddev->minor_version = sb->minor_version;
		mddev->patch_version = sb->patch_version;
		mddev->बाह्यal = 0;
		mddev->chunk_sectors = sb->chunk_size >> 9;
		mddev->स_समय = sb->स_समय;
		mddev->uसमय = sb->uसमय;
		mddev->level = sb->level;
		mddev->clevel[0] = 0;
		mddev->layout = sb->layout;
		mddev->raid_disks = sb->raid_disks;
		mddev->dev_sectors = ((sector_t)sb->size) * 2;
		mddev->events = ev1;
		mddev->biपंचांगap_info.offset = 0;
		mddev->biपंचांगap_info.space = 0;
		/* biपंचांगap can use 60 K after the 4K superblocks */
		mddev->biपंचांगap_info.शेष_offset = MD_SB_BYTES >> 9;
		mddev->biपंचांगap_info.शेष_space = 64*2 - (MD_SB_BYTES >> 9);
		mddev->reshape_backwards = 0;

		अगर (mddev->minor_version >= 91) अणु
			mddev->reshape_position = sb->reshape_position;
			mddev->delta_disks = sb->delta_disks;
			mddev->new_level = sb->new_level;
			mddev->new_layout = sb->new_layout;
			mddev->new_chunk_sectors = sb->new_chunk >> 9;
			अगर (mddev->delta_disks < 0)
				mddev->reshape_backwards = 1;
		पूर्ण अन्यथा अणु
			mddev->reshape_position = MaxSector;
			mddev->delta_disks = 0;
			mddev->new_level = mddev->level;
			mddev->new_layout = mddev->layout;
			mddev->new_chunk_sectors = mddev->chunk_sectors;
		पूर्ण
		अगर (mddev->level == 0)
			mddev->layout = -1;

		अगर (sb->state & (1<<MD_SB_CLEAN))
			mddev->recovery_cp = MaxSector;
		अन्यथा अणु
			अगर (sb->events_hi == sb->cp_events_hi &&
				sb->events_lo == sb->cp_events_lo) अणु
				mddev->recovery_cp = sb->recovery_cp;
			पूर्ण अन्यथा
				mddev->recovery_cp = 0;
		पूर्ण

		स_नकल(mddev->uuid+0, &sb->set_uuid0, 4);
		स_नकल(mddev->uuid+4, &sb->set_uuid1, 4);
		स_नकल(mddev->uuid+8, &sb->set_uuid2, 4);
		स_नकल(mddev->uuid+12,&sb->set_uuid3, 4);

		mddev->max_disks = MD_SB_DISKS;

		अगर (sb->state & (1<<MD_SB_BITMAP_PRESENT) &&
		    mddev->biपंचांगap_info.file == शून्य) अणु
			mddev->biपंचांगap_info.offset =
				mddev->biपंचांगap_info.शेष_offset;
			mddev->biपंचांगap_info.space =
				mddev->biपंचांगap_info.शेष_space;
		पूर्ण

	पूर्ण अन्यथा अगर (mddev->pers == शून्य) अणु
		/* Insist on good event counter जबतक assembling, except
		 * क्रम spares (which करोn't need an event count) */
		++ev1;
		अगर (sb->disks[rdev->desc_nr].state & (
			    (1<<MD_DISK_SYNC) | (1 << MD_DISK_ACTIVE)))
			अगर (ev1 < mddev->events)
				वापस -EINVAL;
	पूर्ण अन्यथा अगर (mddev->biपंचांगap) अणु
		/* अगर adding to array with a biपंचांगap, then we can accept an
		 * older device ... but not too old.
		 */
		अगर (ev1 < mddev->biपंचांगap->events_cleared)
			वापस 0;
		अगर (ev1 < mddev->events)
			set_bit(Biपंचांगap_sync, &rdev->flags);
	पूर्ण अन्यथा अणु
		अगर (ev1 < mddev->events)
			/* just a hot-add of a new device, leave raid_disk at -1 */
			वापस 0;
	पूर्ण

	अगर (mddev->level != LEVEL_MULTIPATH) अणु
		desc = sb->disks + rdev->desc_nr;

		अगर (desc->state & (1<<MD_DISK_FAULTY))
			set_bit(Faulty, &rdev->flags);
		अन्यथा अगर (desc->state & (1<<MD_DISK_SYNC) /* &&
			    desc->raid_disk < mddev->raid_disks */) अणु
			set_bit(In_sync, &rdev->flags);
			rdev->raid_disk = desc->raid_disk;
			rdev->saved_raid_disk = desc->raid_disk;
		पूर्ण अन्यथा अगर (desc->state & (1<<MD_DISK_ACTIVE)) अणु
			/* active but not in sync implies recovery up to
			 * reshape position.  We करोn't know exactly where
			 * that is, so set to zero क्रम now */
			अगर (mddev->minor_version >= 91) अणु
				rdev->recovery_offset = 0;
				rdev->raid_disk = desc->raid_disk;
			पूर्ण
		पूर्ण
		अगर (desc->state & (1<<MD_DISK_WRITEMOSTLY))
			set_bit(WriteMostly, &rdev->flags);
		अगर (desc->state & (1<<MD_DISK_FAILFAST))
			set_bit(FailFast, &rdev->flags);
	पूर्ण अन्यथा /* MULTIPATH are always insync */
		set_bit(In_sync, &rdev->flags);
	वापस 0;
पूर्ण

/*
 * sync_super क्रम 0.90.0
 */
अटल व्योम super_90_sync(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	mdp_super_t *sb;
	काष्ठा md_rdev *rdev2;
	पूर्णांक next_spare = mddev->raid_disks;

	/* make rdev->sb match mddev data..
	 *
	 * 1/ zero out disks
	 * 2/ Add info क्रम each disk, keeping track of highest desc_nr (next_spare);
	 * 3/ any empty disks < next_spare become हटाओd
	 *
	 * disks[0] माला_लो initialised to REMOVED because
	 * we cannot be sure from other fields अगर it has
	 * been initialised or not.
	 */
	पूर्णांक i;
	पूर्णांक active=0, working=0,failed=0,spare=0,nr_disks=0;

	rdev->sb_size = MD_SB_BYTES;

	sb = page_address(rdev->sb_page);

	स_रखो(sb, 0, माप(*sb));

	sb->md_magic = MD_SB_MAGIC;
	sb->major_version = mddev->major_version;
	sb->patch_version = mddev->patch_version;
	sb->gvalid_words  = 0; /* ignored */
	स_नकल(&sb->set_uuid0, mddev->uuid+0, 4);
	स_नकल(&sb->set_uuid1, mddev->uuid+4, 4);
	स_नकल(&sb->set_uuid2, mddev->uuid+8, 4);
	स_नकल(&sb->set_uuid3, mddev->uuid+12,4);

	sb->स_समय = clamp_t(समय64_t, mddev->स_समय, 0, U32_MAX);
	sb->level = mddev->level;
	sb->size = mddev->dev_sectors / 2;
	sb->raid_disks = mddev->raid_disks;
	sb->md_minor = mddev->md_minor;
	sb->not_persistent = 0;
	sb->uसमय = clamp_t(समय64_t, mddev->uसमय, 0, U32_MAX);
	sb->state = 0;
	sb->events_hi = (mddev->events>>32);
	sb->events_lo = (u32)mddev->events;

	अगर (mddev->reshape_position == MaxSector)
		sb->minor_version = 90;
	अन्यथा अणु
		sb->minor_version = 91;
		sb->reshape_position = mddev->reshape_position;
		sb->new_level = mddev->new_level;
		sb->delta_disks = mddev->delta_disks;
		sb->new_layout = mddev->new_layout;
		sb->new_chunk = mddev->new_chunk_sectors << 9;
	पूर्ण
	mddev->minor_version = sb->minor_version;
	अगर (mddev->in_sync)
	अणु
		sb->recovery_cp = mddev->recovery_cp;
		sb->cp_events_hi = (mddev->events>>32);
		sb->cp_events_lo = (u32)mddev->events;
		अगर (mddev->recovery_cp == MaxSector)
			sb->state = (1<< MD_SB_CLEAN);
	पूर्ण अन्यथा
		sb->recovery_cp = 0;

	sb->layout = mddev->layout;
	sb->chunk_size = mddev->chunk_sectors << 9;

	अगर (mddev->biपंचांगap && mddev->biपंचांगap_info.file == शून्य)
		sb->state |= (1<<MD_SB_BITMAP_PRESENT);

	sb->disks[0].state = (1<<MD_DISK_REMOVED);
	rdev_क्रम_each(rdev2, mddev) अणु
		mdp_disk_t *d;
		पूर्णांक desc_nr;
		पूर्णांक is_active = test_bit(In_sync, &rdev2->flags);

		अगर (rdev2->raid_disk >= 0 &&
		    sb->minor_version >= 91)
			/* we have nowhere to store the recovery_offset,
			 * but अगर it is not below the reshape_position,
			 * we can piggy-back on that.
			 */
			is_active = 1;
		अगर (rdev2->raid_disk < 0 ||
		    test_bit(Faulty, &rdev2->flags))
			is_active = 0;
		अगर (is_active)
			desc_nr = rdev2->raid_disk;
		अन्यथा
			desc_nr = next_spare++;
		rdev2->desc_nr = desc_nr;
		d = &sb->disks[rdev2->desc_nr];
		nr_disks++;
		d->number = rdev2->desc_nr;
		d->major = MAJOR(rdev2->bdev->bd_dev);
		d->minor = MINOR(rdev2->bdev->bd_dev);
		अगर (is_active)
			d->raid_disk = rdev2->raid_disk;
		अन्यथा
			d->raid_disk = rdev2->desc_nr; /* compatibility */
		अगर (test_bit(Faulty, &rdev2->flags))
			d->state = (1<<MD_DISK_FAULTY);
		अन्यथा अगर (is_active) अणु
			d->state = (1<<MD_DISK_ACTIVE);
			अगर (test_bit(In_sync, &rdev2->flags))
				d->state |= (1<<MD_DISK_SYNC);
			active++;
			working++;
		पूर्ण अन्यथा अणु
			d->state = 0;
			spare++;
			working++;
		पूर्ण
		अगर (test_bit(WriteMostly, &rdev2->flags))
			d->state |= (1<<MD_DISK_WRITEMOSTLY);
		अगर (test_bit(FailFast, &rdev2->flags))
			d->state |= (1<<MD_DISK_FAILFAST);
	पूर्ण
	/* now set the "removed" and "faulty" bits on any missing devices */
	क्रम (i=0 ; i < mddev->raid_disks ; i++) अणु
		mdp_disk_t *d = &sb->disks[i];
		अगर (d->state == 0 && d->number == 0) अणु
			d->number = i;
			d->raid_disk = i;
			d->state = (1<<MD_DISK_REMOVED);
			d->state |= (1<<MD_DISK_FAULTY);
			failed++;
		पूर्ण
	पूर्ण
	sb->nr_disks = nr_disks;
	sb->active_disks = active;
	sb->working_disks = working;
	sb->failed_disks = failed;
	sb->spare_disks = spare;

	sb->this_disk = sb->disks[rdev->desc_nr];
	sb->sb_csum = calc_sb_csum(sb);
पूर्ण

/*
 * rdev_size_change क्रम 0.90.0
 */
अटल अचिन्हित दीर्घ दीर्घ
super_90_rdev_size_change(काष्ठा md_rdev *rdev, sector_t num_sectors)
अणु
	अगर (num_sectors && num_sectors < rdev->mddev->dev_sectors)
		वापस 0; /* component must fit device */
	अगर (rdev->mddev->biपंचांगap_info.offset)
		वापस 0; /* can't move biपंचांगap */
	rdev->sb_start = calc_dev_sboffset(rdev);
	अगर (!num_sectors || num_sectors > rdev->sb_start)
		num_sectors = rdev->sb_start;
	/* Limit to 4TB as metadata cannot record more than that.
	 * 4TB == 2^32 KB, or 2*2^32 sectors.
	 */
	अगर ((u64)num_sectors >= (2ULL << 32) && rdev->mddev->level >= 1)
		num_sectors = (sector_t)(2ULL << 32) - 2;
	करो अणु
		md_super_ग_लिखो(rdev->mddev, rdev, rdev->sb_start, rdev->sb_size,
		       rdev->sb_page);
	पूर्ण जबतक (md_super_रुको(rdev->mddev) < 0);
	वापस num_sectors;
पूर्ण

अटल पूर्णांक
super_90_allow_new_offset(काष्ठा md_rdev *rdev, अचिन्हित दीर्घ दीर्घ new_offset)
अणु
	/* non-zero offset changes not possible with v0.90 */
	वापस new_offset == 0;
पूर्ण

/*
 * version 1 superblock
 */

अटल __le32 calc_sb_1_csum(काष्ठा mdp_superblock_1 *sb)
अणु
	__le32 disk_csum;
	u32 csum;
	अचिन्हित दीर्घ दीर्घ newcsum;
	पूर्णांक size = 256 + le32_to_cpu(sb->max_dev)*2;
	__le32 *isuper = (__le32*)sb;

	disk_csum = sb->sb_csum;
	sb->sb_csum = 0;
	newcsum = 0;
	क्रम (; size >= 4; size -= 4)
		newcsum += le32_to_cpu(*isuper++);

	अगर (size == 2)
		newcsum += le16_to_cpu(*(__le16*) isuper);

	csum = (newcsum & 0xffffffff) + (newcsum >> 32);
	sb->sb_csum = disk_csum;
	वापस cpu_to_le32(csum);
पूर्ण

अटल पूर्णांक super_1_load(काष्ठा md_rdev *rdev, काष्ठा md_rdev *refdev, पूर्णांक minor_version)
अणु
	काष्ठा mdp_superblock_1 *sb;
	पूर्णांक ret;
	sector_t sb_start;
	sector_t sectors;
	अक्षर b[BDEVNAME_SIZE], b2[BDEVNAME_SIZE];
	पूर्णांक bmask;
	bool spare_disk = true;

	/*
	 * Calculate the position of the superblock in 512byte sectors.
	 * It is always aligned to a 4K boundary and
	 * depeding on minor_version, it can be:
	 * 0: At least 8K, but less than 12K, from end of device
	 * 1: At start of device
	 * 2: 4K from start of device.
	 */
	चयन(minor_version) अणु
	हाल 0:
		sb_start = i_size_पढ़ो(rdev->bdev->bd_inode) >> 9;
		sb_start -= 8*2;
		sb_start &= ~(sector_t)(4*2-1);
		अवरोध;
	हाल 1:
		sb_start = 0;
		अवरोध;
	हाल 2:
		sb_start = 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	rdev->sb_start = sb_start;

	/* superblock is rarely larger than 1K, but it can be larger,
	 * and it is safe to पढ़ो 4k, so we करो that
	 */
	ret = पढ़ो_disk_sb(rdev, 4096);
	अगर (ret) वापस ret;

	sb = page_address(rdev->sb_page);

	अगर (sb->magic != cpu_to_le32(MD_SB_MAGIC) ||
	    sb->major_version != cpu_to_le32(1) ||
	    le32_to_cpu(sb->max_dev) > (4096-256)/2 ||
	    le64_to_cpu(sb->super_offset) != rdev->sb_start ||
	    (le32_to_cpu(sb->feature_map) & ~MD_FEATURE_ALL) != 0)
		वापस -EINVAL;

	अगर (calc_sb_1_csum(sb) != sb->sb_csum) अणु
		pr_warn("md: invalid superblock checksum on %s\n",
			bdevname(rdev->bdev,b));
		वापस -EINVAL;
	पूर्ण
	अगर (le64_to_cpu(sb->data_size) < 10) अणु
		pr_warn("md: data_size too small on %s\n",
			bdevname(rdev->bdev,b));
		वापस -EINVAL;
	पूर्ण
	अगर (sb->pad0 ||
	    sb->pad3[0] ||
	    स_भेद(sb->pad3, sb->pad3+1, माप(sb->pad3) - माप(sb->pad3[1])))
		/* Some padding is non-zero, might be a new feature */
		वापस -EINVAL;

	rdev->preferred_minor = 0xffff;
	rdev->data_offset = le64_to_cpu(sb->data_offset);
	rdev->new_data_offset = rdev->data_offset;
	अगर ((le32_to_cpu(sb->feature_map) & MD_FEATURE_RESHAPE_ACTIVE) &&
	    (le32_to_cpu(sb->feature_map) & MD_FEATURE_NEW_OFFSET))
		rdev->new_data_offset += (s32)le32_to_cpu(sb->new_offset);
	atomic_set(&rdev->corrected_errors, le32_to_cpu(sb->cnt_corrected_पढ़ो));

	rdev->sb_size = le32_to_cpu(sb->max_dev) * 2 + 256;
	bmask = queue_logical_block_size(rdev->bdev->bd_disk->queue)-1;
	अगर (rdev->sb_size & bmask)
		rdev->sb_size = (rdev->sb_size | bmask) + 1;

	अगर (minor_version
	    && rdev->data_offset < sb_start + (rdev->sb_size/512))
		वापस -EINVAL;
	अगर (minor_version
	    && rdev->new_data_offset < sb_start + (rdev->sb_size/512))
		वापस -EINVAL;

	अगर (sb->level == cpu_to_le32(LEVEL_MULTIPATH))
		rdev->desc_nr = -1;
	अन्यथा
		rdev->desc_nr = le32_to_cpu(sb->dev_number);

	अगर (!rdev->bb_page) अणु
		rdev->bb_page = alloc_page(GFP_KERNEL);
		अगर (!rdev->bb_page)
			वापस -ENOMEM;
	पूर्ण
	अगर ((le32_to_cpu(sb->feature_map) & MD_FEATURE_BAD_BLOCKS) &&
	    rdev->badblocks.count == 0) अणु
		/* need to load the bad block list.
		 * Currently we limit it to one page.
		 */
		s32 offset;
		sector_t bb_sector;
		__le64 *bbp;
		पूर्णांक i;
		पूर्णांक sectors = le16_to_cpu(sb->bblog_size);
		अगर (sectors > (PAGE_SIZE / 512))
			वापस -EINVAL;
		offset = le32_to_cpu(sb->bblog_offset);
		अगर (offset == 0)
			वापस -EINVAL;
		bb_sector = (दीर्घ दीर्घ)offset;
		अगर (!sync_page_io(rdev, bb_sector, sectors << 9,
				  rdev->bb_page, REQ_OP_READ, 0, true))
			वापस -EIO;
		bbp = (__le64 *)page_address(rdev->bb_page);
		rdev->badblocks.shअगरt = sb->bblog_shअगरt;
		क्रम (i = 0 ; i < (sectors << (9-3)) ; i++, bbp++) अणु
			u64 bb = le64_to_cpu(*bbp);
			पूर्णांक count = bb & (0x3ff);
			u64 sector = bb >> 10;
			sector <<= sb->bblog_shअगरt;
			count <<= sb->bblog_shअगरt;
			अगर (bb + 1 == 0)
				अवरोध;
			अगर (badblocks_set(&rdev->badblocks, sector, count, 1))
				वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (sb->bblog_offset != 0)
		rdev->badblocks.shअगरt = 0;

	अगर ((le32_to_cpu(sb->feature_map) &
	    (MD_FEATURE_PPL | MD_FEATURE_MULTIPLE_PPLS))) अणु
		rdev->ppl.offset = (__s16)le16_to_cpu(sb->ppl.offset);
		rdev->ppl.size = le16_to_cpu(sb->ppl.size);
		rdev->ppl.sector = rdev->sb_start + rdev->ppl.offset;
	पूर्ण

	अगर ((le32_to_cpu(sb->feature_map) & MD_FEATURE_RAID0_LAYOUT) &&
	    sb->level != 0)
		वापस -EINVAL;

	/* not spare disk, or LEVEL_MULTIPATH */
	अगर (sb->level == cpu_to_le32(LEVEL_MULTIPATH) ||
		(rdev->desc_nr >= 0 &&
		rdev->desc_nr < le32_to_cpu(sb->max_dev) &&
		(le16_to_cpu(sb->dev_roles[rdev->desc_nr]) < MD_DISK_ROLE_MAX ||
		 le16_to_cpu(sb->dev_roles[rdev->desc_nr]) == MD_DISK_ROLE_JOURNAL)))
		spare_disk = false;

	अगर (!refdev) अणु
		अगर (!spare_disk)
			ret = 1;
		अन्यथा
			ret = 0;
	पूर्ण अन्यथा अणु
		__u64 ev1, ev2;
		काष्ठा mdp_superblock_1 *refsb = page_address(refdev->sb_page);

		अगर (स_भेद(sb->set_uuid, refsb->set_uuid, 16) != 0 ||
		    sb->level != refsb->level ||
		    sb->layout != refsb->layout ||
		    sb->chunksize != refsb->chunksize) अणु
			pr_warn("md: %s has strangely different superblock to %s\n",
				bdevname(rdev->bdev,b),
				bdevname(refdev->bdev,b2));
			वापस -EINVAL;
		पूर्ण
		ev1 = le64_to_cpu(sb->events);
		ev2 = le64_to_cpu(refsb->events);

		अगर (!spare_disk && ev1 > ev2)
			ret = 1;
		अन्यथा
			ret = 0;
	पूर्ण
	अगर (minor_version) अणु
		sectors = (i_size_पढ़ो(rdev->bdev->bd_inode) >> 9);
		sectors -= rdev->data_offset;
	पूर्ण अन्यथा
		sectors = rdev->sb_start;
	अगर (sectors < le64_to_cpu(sb->data_size))
		वापस -EINVAL;
	rdev->sectors = le64_to_cpu(sb->data_size);
	वापस ret;
पूर्ण

अटल पूर्णांक super_1_validate(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा mdp_superblock_1 *sb = page_address(rdev->sb_page);
	__u64 ev1 = le64_to_cpu(sb->events);

	rdev->raid_disk = -1;
	clear_bit(Faulty, &rdev->flags);
	clear_bit(In_sync, &rdev->flags);
	clear_bit(Biपंचांगap_sync, &rdev->flags);
	clear_bit(WriteMostly, &rdev->flags);

	अगर (mddev->raid_disks == 0) अणु
		mddev->major_version = 1;
		mddev->patch_version = 0;
		mddev->बाह्यal = 0;
		mddev->chunk_sectors = le32_to_cpu(sb->chunksize);
		mddev->स_समय = le64_to_cpu(sb->स_समय);
		mddev->uसमय = le64_to_cpu(sb->uसमय);
		mddev->level = le32_to_cpu(sb->level);
		mddev->clevel[0] = 0;
		mddev->layout = le32_to_cpu(sb->layout);
		mddev->raid_disks = le32_to_cpu(sb->raid_disks);
		mddev->dev_sectors = le64_to_cpu(sb->size);
		mddev->events = ev1;
		mddev->biपंचांगap_info.offset = 0;
		mddev->biपंचांगap_info.space = 0;
		/* Default location क्रम biपंचांगap is 1K after superblock
		 * using 3K - total of 4K
		 */
		mddev->biपंचांगap_info.शेष_offset = 1024 >> 9;
		mddev->biपंचांगap_info.शेष_space = (4096-1024) >> 9;
		mddev->reshape_backwards = 0;

		mddev->recovery_cp = le64_to_cpu(sb->resync_offset);
		स_नकल(mddev->uuid, sb->set_uuid, 16);

		mddev->max_disks =  (4096-256)/2;

		अगर ((le32_to_cpu(sb->feature_map) & MD_FEATURE_BITMAP_OFFSET) &&
		    mddev->biपंचांगap_info.file == शून्य) अणु
			mddev->biपंचांगap_info.offset =
				(__s32)le32_to_cpu(sb->biपंचांगap_offset);
			/* Metadata करोesn't record how much space is available.
			 * For 1.0, we assume we can use up to the superblock
			 * अगर beक्रमe, अन्यथा to 4K beyond superblock.
			 * For others, assume no change is possible.
			 */
			अगर (mddev->minor_version > 0)
				mddev->biपंचांगap_info.space = 0;
			अन्यथा अगर (mddev->biपंचांगap_info.offset > 0)
				mddev->biपंचांगap_info.space =
					8 - mddev->biपंचांगap_info.offset;
			अन्यथा
				mddev->biपंचांगap_info.space =
					-mddev->biपंचांगap_info.offset;
		पूर्ण

		अगर ((le32_to_cpu(sb->feature_map) & MD_FEATURE_RESHAPE_ACTIVE)) अणु
			mddev->reshape_position = le64_to_cpu(sb->reshape_position);
			mddev->delta_disks = le32_to_cpu(sb->delta_disks);
			mddev->new_level = le32_to_cpu(sb->new_level);
			mddev->new_layout = le32_to_cpu(sb->new_layout);
			mddev->new_chunk_sectors = le32_to_cpu(sb->new_chunk);
			अगर (mddev->delta_disks < 0 ||
			    (mddev->delta_disks == 0 &&
			     (le32_to_cpu(sb->feature_map)
			      & MD_FEATURE_RESHAPE_BACKWARDS)))
				mddev->reshape_backwards = 1;
		पूर्ण अन्यथा अणु
			mddev->reshape_position = MaxSector;
			mddev->delta_disks = 0;
			mddev->new_level = mddev->level;
			mddev->new_layout = mddev->layout;
			mddev->new_chunk_sectors = mddev->chunk_sectors;
		पूर्ण

		अगर (mddev->level == 0 &&
		    !(le32_to_cpu(sb->feature_map) & MD_FEATURE_RAID0_LAYOUT))
			mddev->layout = -1;

		अगर (le32_to_cpu(sb->feature_map) & MD_FEATURE_JOURNAL)
			set_bit(MD_HAS_JOURNAL, &mddev->flags);

		अगर (le32_to_cpu(sb->feature_map) &
		    (MD_FEATURE_PPL | MD_FEATURE_MULTIPLE_PPLS)) अणु
			अगर (le32_to_cpu(sb->feature_map) &
			    (MD_FEATURE_BITMAP_OFFSET | MD_FEATURE_JOURNAL))
				वापस -EINVAL;
			अगर ((le32_to_cpu(sb->feature_map) & MD_FEATURE_PPL) &&
			    (le32_to_cpu(sb->feature_map) &
					    MD_FEATURE_MULTIPLE_PPLS))
				वापस -EINVAL;
			set_bit(MD_HAS_PPL, &mddev->flags);
		पूर्ण
	पूर्ण अन्यथा अगर (mddev->pers == शून्य) अणु
		/* Insist of good event counter जबतक assembling, except क्रम
		 * spares (which करोn't need an event count) */
		++ev1;
		अगर (rdev->desc_nr >= 0 &&
		    rdev->desc_nr < le32_to_cpu(sb->max_dev) &&
		    (le16_to_cpu(sb->dev_roles[rdev->desc_nr]) < MD_DISK_ROLE_MAX ||
		     le16_to_cpu(sb->dev_roles[rdev->desc_nr]) == MD_DISK_ROLE_JOURNAL))
			अगर (ev1 < mddev->events)
				वापस -EINVAL;
	पूर्ण अन्यथा अगर (mddev->biपंचांगap) अणु
		/* If adding to array with a biपंचांगap, then we can accept an
		 * older device, but not too old.
		 */
		अगर (ev1 < mddev->biपंचांगap->events_cleared)
			वापस 0;
		अगर (ev1 < mddev->events)
			set_bit(Biपंचांगap_sync, &rdev->flags);
	पूर्ण अन्यथा अणु
		अगर (ev1 < mddev->events)
			/* just a hot-add of a new device, leave raid_disk at -1 */
			वापस 0;
	पूर्ण
	अगर (mddev->level != LEVEL_MULTIPATH) अणु
		पूर्णांक role;
		अगर (rdev->desc_nr < 0 ||
		    rdev->desc_nr >= le32_to_cpu(sb->max_dev)) अणु
			role = MD_DISK_ROLE_SPARE;
			rdev->desc_nr = -1;
		पूर्ण अन्यथा
			role = le16_to_cpu(sb->dev_roles[rdev->desc_nr]);
		चयन(role) अणु
		हाल MD_DISK_ROLE_SPARE: /* spare */
			अवरोध;
		हाल MD_DISK_ROLE_FAULTY: /* faulty */
			set_bit(Faulty, &rdev->flags);
			अवरोध;
		हाल MD_DISK_ROLE_JOURNAL: /* journal device */
			अगर (!(le32_to_cpu(sb->feature_map) & MD_FEATURE_JOURNAL)) अणु
				/* journal device without journal feature */
				pr_warn("md: journal device provided without journal feature, ignoring the device\n");
				वापस -EINVAL;
			पूर्ण
			set_bit(Journal, &rdev->flags);
			rdev->journal_tail = le64_to_cpu(sb->journal_tail);
			rdev->raid_disk = 0;
			अवरोध;
		शेष:
			rdev->saved_raid_disk = role;
			अगर ((le32_to_cpu(sb->feature_map) &
			     MD_FEATURE_RECOVERY_OFFSET)) अणु
				rdev->recovery_offset = le64_to_cpu(sb->recovery_offset);
				अगर (!(le32_to_cpu(sb->feature_map) &
				      MD_FEATURE_RECOVERY_BITMAP))
					rdev->saved_raid_disk = -1;
			पूर्ण अन्यथा अणु
				/*
				 * If the array is FROZEN, then the device can't
				 * be in_sync with rest of array.
				 */
				अगर (!test_bit(MD_RECOVERY_FROZEN,
					      &mddev->recovery))
					set_bit(In_sync, &rdev->flags);
			पूर्ण
			rdev->raid_disk = role;
			अवरोध;
		पूर्ण
		अगर (sb->devflags & WriteMostly1)
			set_bit(WriteMostly, &rdev->flags);
		अगर (sb->devflags & FailFast1)
			set_bit(FailFast, &rdev->flags);
		अगर (le32_to_cpu(sb->feature_map) & MD_FEATURE_REPLACEMENT)
			set_bit(Replacement, &rdev->flags);
	पूर्ण अन्यथा /* MULTIPATH are always insync */
		set_bit(In_sync, &rdev->flags);

	वापस 0;
पूर्ण

अटल व्योम super_1_sync(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा mdp_superblock_1 *sb;
	काष्ठा md_rdev *rdev2;
	पूर्णांक max_dev, i;
	/* make rdev->sb match mddev and rdev data. */

	sb = page_address(rdev->sb_page);

	sb->feature_map = 0;
	sb->pad0 = 0;
	sb->recovery_offset = cpu_to_le64(0);
	स_रखो(sb->pad3, 0, माप(sb->pad3));

	sb->uसमय = cpu_to_le64((__u64)mddev->uसमय);
	sb->events = cpu_to_le64(mddev->events);
	अगर (mddev->in_sync)
		sb->resync_offset = cpu_to_le64(mddev->recovery_cp);
	अन्यथा अगर (test_bit(MD_JOURNAL_CLEAN, &mddev->flags))
		sb->resync_offset = cpu_to_le64(MaxSector);
	अन्यथा
		sb->resync_offset = cpu_to_le64(0);

	sb->cnt_corrected_पढ़ो = cpu_to_le32(atomic_पढ़ो(&rdev->corrected_errors));

	sb->raid_disks = cpu_to_le32(mddev->raid_disks);
	sb->size = cpu_to_le64(mddev->dev_sectors);
	sb->chunksize = cpu_to_le32(mddev->chunk_sectors);
	sb->level = cpu_to_le32(mddev->level);
	sb->layout = cpu_to_le32(mddev->layout);
	अगर (test_bit(FailFast, &rdev->flags))
		sb->devflags |= FailFast1;
	अन्यथा
		sb->devflags &= ~FailFast1;

	अगर (test_bit(WriteMostly, &rdev->flags))
		sb->devflags |= WriteMostly1;
	अन्यथा
		sb->devflags &= ~WriteMostly1;
	sb->data_offset = cpu_to_le64(rdev->data_offset);
	sb->data_size = cpu_to_le64(rdev->sectors);

	अगर (mddev->biपंचांगap && mddev->biपंचांगap_info.file == शून्य) अणु
		sb->biपंचांगap_offset = cpu_to_le32((__u32)mddev->biपंचांगap_info.offset);
		sb->feature_map = cpu_to_le32(MD_FEATURE_BITMAP_OFFSET);
	पूर्ण

	अगर (rdev->raid_disk >= 0 && !test_bit(Journal, &rdev->flags) &&
	    !test_bit(In_sync, &rdev->flags)) अणु
		sb->feature_map |=
			cpu_to_le32(MD_FEATURE_RECOVERY_OFFSET);
		sb->recovery_offset =
			cpu_to_le64(rdev->recovery_offset);
		अगर (rdev->saved_raid_disk >= 0 && mddev->biपंचांगap)
			sb->feature_map |=
				cpu_to_le32(MD_FEATURE_RECOVERY_BITMAP);
	पूर्ण
	/* Note: recovery_offset and journal_tail share space  */
	अगर (test_bit(Journal, &rdev->flags))
		sb->journal_tail = cpu_to_le64(rdev->journal_tail);
	अगर (test_bit(Replacement, &rdev->flags))
		sb->feature_map |=
			cpu_to_le32(MD_FEATURE_REPLACEMENT);

	अगर (mddev->reshape_position != MaxSector) अणु
		sb->feature_map |= cpu_to_le32(MD_FEATURE_RESHAPE_ACTIVE);
		sb->reshape_position = cpu_to_le64(mddev->reshape_position);
		sb->new_layout = cpu_to_le32(mddev->new_layout);
		sb->delta_disks = cpu_to_le32(mddev->delta_disks);
		sb->new_level = cpu_to_le32(mddev->new_level);
		sb->new_chunk = cpu_to_le32(mddev->new_chunk_sectors);
		अगर (mddev->delta_disks == 0 &&
		    mddev->reshape_backwards)
			sb->feature_map
				|= cpu_to_le32(MD_FEATURE_RESHAPE_BACKWARDS);
		अगर (rdev->new_data_offset != rdev->data_offset) अणु
			sb->feature_map
				|= cpu_to_le32(MD_FEATURE_NEW_OFFSET);
			sb->new_offset = cpu_to_le32((__u32)(rdev->new_data_offset
							     - rdev->data_offset));
		पूर्ण
	पूर्ण

	अगर (mddev_is_clustered(mddev))
		sb->feature_map |= cpu_to_le32(MD_FEATURE_CLUSTERED);

	अगर (rdev->badblocks.count == 0)
		/* Nothing to करो क्रम bad blocks*/ ;
	अन्यथा अगर (sb->bblog_offset == 0)
		/* Cannot record bad blocks on this device */
		md_error(mddev, rdev);
	अन्यथा अणु
		काष्ठा badblocks *bb = &rdev->badblocks;
		__le64 *bbp = (__le64 *)page_address(rdev->bb_page);
		u64 *p = bb->page;
		sb->feature_map |= cpu_to_le32(MD_FEATURE_BAD_BLOCKS);
		अगर (bb->changed) अणु
			अचिन्हित seq;

retry:
			seq = पढ़ो_seqbegin(&bb->lock);

			स_रखो(bbp, 0xff, PAGE_SIZE);

			क्रम (i = 0 ; i < bb->count ; i++) अणु
				u64 पूर्णांकernal_bb = p[i];
				u64 store_bb = ((BB_OFFSET(पूर्णांकernal_bb) << 10)
						| BB_LEN(पूर्णांकernal_bb));
				bbp[i] = cpu_to_le64(store_bb);
			पूर्ण
			bb->changed = 0;
			अगर (पढ़ो_seqretry(&bb->lock, seq))
				जाओ retry;

			bb->sector = (rdev->sb_start +
				      (पूर्णांक)le32_to_cpu(sb->bblog_offset));
			bb->size = le16_to_cpu(sb->bblog_size);
		पूर्ण
	पूर्ण

	max_dev = 0;
	rdev_क्रम_each(rdev2, mddev)
		अगर (rdev2->desc_nr+1 > max_dev)
			max_dev = rdev2->desc_nr+1;

	अगर (max_dev > le32_to_cpu(sb->max_dev)) अणु
		पूर्णांक bmask;
		sb->max_dev = cpu_to_le32(max_dev);
		rdev->sb_size = max_dev * 2 + 256;
		bmask = queue_logical_block_size(rdev->bdev->bd_disk->queue)-1;
		अगर (rdev->sb_size & bmask)
			rdev->sb_size = (rdev->sb_size | bmask) + 1;
	पूर्ण अन्यथा
		max_dev = le32_to_cpu(sb->max_dev);

	क्रम (i=0; i<max_dev;i++)
		sb->dev_roles[i] = cpu_to_le16(MD_DISK_ROLE_SPARE);

	अगर (test_bit(MD_HAS_JOURNAL, &mddev->flags))
		sb->feature_map |= cpu_to_le32(MD_FEATURE_JOURNAL);

	अगर (test_bit(MD_HAS_PPL, &mddev->flags)) अणु
		अगर (test_bit(MD_HAS_MULTIPLE_PPLS, &mddev->flags))
			sb->feature_map |=
			    cpu_to_le32(MD_FEATURE_MULTIPLE_PPLS);
		अन्यथा
			sb->feature_map |= cpu_to_le32(MD_FEATURE_PPL);
		sb->ppl.offset = cpu_to_le16(rdev->ppl.offset);
		sb->ppl.size = cpu_to_le16(rdev->ppl.size);
	पूर्ण

	rdev_क्रम_each(rdev2, mddev) अणु
		i = rdev2->desc_nr;
		अगर (test_bit(Faulty, &rdev2->flags))
			sb->dev_roles[i] = cpu_to_le16(MD_DISK_ROLE_FAULTY);
		अन्यथा अगर (test_bit(In_sync, &rdev2->flags))
			sb->dev_roles[i] = cpu_to_le16(rdev2->raid_disk);
		अन्यथा अगर (test_bit(Journal, &rdev2->flags))
			sb->dev_roles[i] = cpu_to_le16(MD_DISK_ROLE_JOURNAL);
		अन्यथा अगर (rdev2->raid_disk >= 0)
			sb->dev_roles[i] = cpu_to_le16(rdev2->raid_disk);
		अन्यथा
			sb->dev_roles[i] = cpu_to_le16(MD_DISK_ROLE_SPARE);
	पूर्ण

	sb->sb_csum = calc_sb_1_csum(sb);
पूर्ण

अटल sector_t super_1_choose_bm_space(sector_t dev_size)
अणु
	sector_t bm_space;

	/* अगर the device is bigger than 8Gig, save 64k क्रम biपंचांगap
	 * usage, अगर bigger than 200Gig, save 128k
	 */
	अगर (dev_size < 64*2)
		bm_space = 0;
	अन्यथा अगर (dev_size - 64*2 >= 200*1024*1024*2)
		bm_space = 128*2;
	अन्यथा अगर (dev_size - 4*2 > 8*1024*1024*2)
		bm_space = 64*2;
	अन्यथा
		bm_space = 4*2;
	वापस bm_space;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ
super_1_rdev_size_change(काष्ठा md_rdev *rdev, sector_t num_sectors)
अणु
	काष्ठा mdp_superblock_1 *sb;
	sector_t max_sectors;
	अगर (num_sectors && num_sectors < rdev->mddev->dev_sectors)
		वापस 0; /* component must fit device */
	अगर (rdev->data_offset != rdev->new_data_offset)
		वापस 0; /* too confusing */
	अगर (rdev->sb_start < rdev->data_offset) अणु
		/* minor versions 1 and 2; superblock beक्रमe data */
		max_sectors = i_size_पढ़ो(rdev->bdev->bd_inode) >> 9;
		max_sectors -= rdev->data_offset;
		अगर (!num_sectors || num_sectors > max_sectors)
			num_sectors = max_sectors;
	पूर्ण अन्यथा अगर (rdev->mddev->biपंचांगap_info.offset) अणु
		/* minor version 0 with biपंचांगap we can't move */
		वापस 0;
	पूर्ण अन्यथा अणु
		/* minor version 0; superblock after data */
		sector_t sb_start, bm_space;
		sector_t dev_size = i_size_पढ़ो(rdev->bdev->bd_inode) >> 9;

		/* 8K is क्रम superblock */
		sb_start = dev_size - 8*2;
		sb_start &= ~(sector_t)(4*2 - 1);

		bm_space = super_1_choose_bm_space(dev_size);

		/* Space that can be used to store date needs to decrease
		 * superblock biपंचांगap space and bad block space(4K)
		 */
		max_sectors = sb_start - bm_space - 4*2;

		अगर (!num_sectors || num_sectors > max_sectors)
			num_sectors = max_sectors;
	पूर्ण
	sb = page_address(rdev->sb_page);
	sb->data_size = cpu_to_le64(num_sectors);
	sb->super_offset = cpu_to_le64(rdev->sb_start);
	sb->sb_csum = calc_sb_1_csum(sb);
	करो अणु
		md_super_ग_लिखो(rdev->mddev, rdev, rdev->sb_start, rdev->sb_size,
			       rdev->sb_page);
	पूर्ण जबतक (md_super_रुको(rdev->mddev) < 0);
	वापस num_sectors;

पूर्ण

अटल पूर्णांक
super_1_allow_new_offset(काष्ठा md_rdev *rdev,
			 अचिन्हित दीर्घ दीर्घ new_offset)
अणु
	/* All necessary checks on new >= old have been करोne */
	काष्ठा biपंचांगap *biपंचांगap;
	अगर (new_offset >= rdev->data_offset)
		वापस 1;

	/* with 1.0 metadata, there is no metadata to tपढ़ो on
	 * so we can always move back */
	अगर (rdev->mddev->minor_version == 0)
		वापस 1;

	/* otherwise we must be sure not to step on
	 * any metadata, so stay:
	 * 36K beyond start of superblock
	 * beyond end of badblocks
	 * beyond ग_लिखो-पूर्णांकent biपंचांगap
	 */
	अगर (rdev->sb_start + (32+4)*2 > new_offset)
		वापस 0;
	biपंचांगap = rdev->mddev->biपंचांगap;
	अगर (biपंचांगap && !rdev->mddev->biपंचांगap_info.file &&
	    rdev->sb_start + rdev->mddev->biपंचांगap_info.offset +
	    biपंचांगap->storage.file_pages * (PAGE_SIZE>>9) > new_offset)
		वापस 0;
	अगर (rdev->badblocks.sector + rdev->badblocks.size > new_offset)
		वापस 0;

	वापस 1;
पूर्ण

अटल काष्ठा super_type super_types[] = अणु
	[0] = अणु
		.name	= "0.90.0",
		.owner	= THIS_MODULE,
		.load_super	    = super_90_load,
		.validate_super	    = super_90_validate,
		.sync_super	    = super_90_sync,
		.rdev_size_change   = super_90_rdev_size_change,
		.allow_new_offset   = super_90_allow_new_offset,
	पूर्ण,
	[1] = अणु
		.name	= "md-1",
		.owner	= THIS_MODULE,
		.load_super	    = super_1_load,
		.validate_super	    = super_1_validate,
		.sync_super	    = super_1_sync,
		.rdev_size_change   = super_1_rdev_size_change,
		.allow_new_offset   = super_1_allow_new_offset,
	पूर्ण,
पूर्ण;

अटल व्योम sync_super(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	अगर (mddev->sync_super) अणु
		mddev->sync_super(mddev, rdev);
		वापस;
	पूर्ण

	BUG_ON(mddev->major_version >= ARRAY_SIZE(super_types));

	super_types[mddev->major_version].sync_super(mddev, rdev);
पूर्ण

अटल पूर्णांक match_mddev_units(काष्ठा mddev *mddev1, काष्ठा mddev *mddev2)
अणु
	काष्ठा md_rdev *rdev, *rdev2;

	rcu_पढ़ो_lock();
	rdev_क्रम_each_rcu(rdev, mddev1) अणु
		अगर (test_bit(Faulty, &rdev->flags) ||
		    test_bit(Journal, &rdev->flags) ||
		    rdev->raid_disk == -1)
			जारी;
		rdev_क्रम_each_rcu(rdev2, mddev2) अणु
			अगर (test_bit(Faulty, &rdev2->flags) ||
			    test_bit(Journal, &rdev2->flags) ||
			    rdev2->raid_disk == -1)
				जारी;
			अगर (rdev->bdev->bd_disk == rdev2->bdev->bd_disk) अणु
				rcu_पढ़ो_unlock();
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल LIST_HEAD(pending_raid_disks);

/*
 * Try to रेजिस्टर data पूर्णांकegrity profile क्रम an mddev
 *
 * This is called when an array is started and after a disk has been kicked
 * from the array. It only succeeds अगर all working and active component devices
 * are पूर्णांकegrity capable with matching profiles.
 */
पूर्णांक md_पूर्णांकegrity_रेजिस्टर(काष्ठा mddev *mddev)
अणु
	काष्ठा md_rdev *rdev, *reference = शून्य;

	अगर (list_empty(&mddev->disks))
		वापस 0; /* nothing to करो */
	अगर (!mddev->gendisk || blk_get_पूर्णांकegrity(mddev->gendisk))
		वापस 0; /* shouldn't रेजिस्टर, or alपढ़ोy is */
	rdev_क्रम_each(rdev, mddev) अणु
		/* skip spares and non-functional disks */
		अगर (test_bit(Faulty, &rdev->flags))
			जारी;
		अगर (rdev->raid_disk < 0)
			जारी;
		अगर (!reference) अणु
			/* Use the first rdev as the reference */
			reference = rdev;
			जारी;
		पूर्ण
		/* करोes this rdev's profile match the reference profile? */
		अगर (blk_पूर्णांकegrity_compare(reference->bdev->bd_disk,
				rdev->bdev->bd_disk) < 0)
			वापस -EINVAL;
	पूर्ण
	अगर (!reference || !bdev_get_पूर्णांकegrity(reference->bdev))
		वापस 0;
	/*
	 * All component devices are पूर्णांकegrity capable and have matching
	 * profiles, रेजिस्टर the common profile क्रम the md device.
	 */
	blk_पूर्णांकegrity_रेजिस्टर(mddev->gendisk,
			       bdev_get_पूर्णांकegrity(reference->bdev));

	pr_debug("md: data integrity enabled on %s\n", mdname(mddev));
	अगर (bioset_पूर्णांकegrity_create(&mddev->bio_set, BIO_POOL_SIZE)) अणु
		pr_err("md: failed to create integrity pool for %s\n",
		       mdname(mddev));
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(md_पूर्णांकegrity_रेजिस्टर);

/*
 * Attempt to add an rdev, but only अगर it is consistent with the current
 * पूर्णांकegrity profile
 */
पूर्णांक md_पूर्णांकegrity_add_rdev(काष्ठा md_rdev *rdev, काष्ठा mddev *mddev)
अणु
	काष्ठा blk_पूर्णांकegrity *bi_mddev;
	अक्षर name[BDEVNAME_SIZE];

	अगर (!mddev->gendisk)
		वापस 0;

	bi_mddev = blk_get_पूर्णांकegrity(mddev->gendisk);

	अगर (!bi_mddev) /* nothing to करो */
		वापस 0;

	अगर (blk_पूर्णांकegrity_compare(mddev->gendisk, rdev->bdev->bd_disk) != 0) अणु
		pr_err("%s: incompatible integrity profile for %s\n",
		       mdname(mddev), bdevname(rdev->bdev, name));
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(md_पूर्णांकegrity_add_rdev);

अटल bool rdev_पढ़ो_only(काष्ठा md_rdev *rdev)
अणु
	वापस bdev_पढ़ो_only(rdev->bdev) ||
		(rdev->meta_bdev && bdev_पढ़ो_only(rdev->meta_bdev));
पूर्ण

अटल पूर्णांक bind_rdev_to_array(काष्ठा md_rdev *rdev, काष्ठा mddev *mddev)
अणु
	अक्षर b[BDEVNAME_SIZE];
	पूर्णांक err;

	/* prevent duplicates */
	अगर (find_rdev(mddev, rdev->bdev->bd_dev))
		वापस -EEXIST;

	अगर (rdev_पढ़ो_only(rdev) && mddev->pers)
		वापस -EROFS;

	/* make sure rdev->sectors exceeds mddev->dev_sectors */
	अगर (!test_bit(Journal, &rdev->flags) &&
	    rdev->sectors &&
	    (mddev->dev_sectors == 0 || rdev->sectors < mddev->dev_sectors)) अणु
		अगर (mddev->pers) अणु
			/* Cannot change size, so fail
			 * If mddev->level <= 0, then we करोn't care
			 * about aligning sizes (e.g. linear)
			 */
			अगर (mddev->level > 0)
				वापस -ENOSPC;
		पूर्ण अन्यथा
			mddev->dev_sectors = rdev->sectors;
	पूर्ण

	/* Verअगरy rdev->desc_nr is unique.
	 * If it is -1, assign a मुक्त number, अन्यथा
	 * check number is not in use
	 */
	rcu_पढ़ो_lock();
	अगर (rdev->desc_nr < 0) अणु
		पूर्णांक choice = 0;
		अगर (mddev->pers)
			choice = mddev->raid_disks;
		जबतक (md_find_rdev_nr_rcu(mddev, choice))
			choice++;
		rdev->desc_nr = choice;
	पूर्ण अन्यथा अणु
		अगर (md_find_rdev_nr_rcu(mddev, rdev->desc_nr)) अणु
			rcu_पढ़ो_unlock();
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (!test_bit(Journal, &rdev->flags) &&
	    mddev->max_disks && rdev->desc_nr >= mddev->max_disks) अणु
		pr_warn("md: %s: array is limited to %d devices\n",
			mdname(mddev), mddev->max_disks);
		वापस -EBUSY;
	पूर्ण
	bdevname(rdev->bdev,b);
	strreplace(b, '/', '!');

	rdev->mddev = mddev;
	pr_debug("md: bind<%s>\n", b);

	अगर (mddev->raid_disks)
		mddev_create_serial_pool(mddev, rdev, false);

	अगर ((err = kobject_add(&rdev->kobj, &mddev->kobj, "dev-%s", b)))
		जाओ fail;

	/* failure here is OK */
	err = sysfs_create_link(&rdev->kobj, bdev_kobj(rdev->bdev), "block");
	rdev->sysfs_state = sysfs_get_dirent_safe(rdev->kobj.sd, "state");
	rdev->sysfs_unack_badblocks =
		sysfs_get_dirent_safe(rdev->kobj.sd, "unacknowledged_bad_blocks");
	rdev->sysfs_badblocks =
		sysfs_get_dirent_safe(rdev->kobj.sd, "bad_blocks");

	list_add_rcu(&rdev->same_set, &mddev->disks);
	bd_link_disk_holder(rdev->bdev, mddev->gendisk);

	/* May as well allow recovery to be retried once */
	mddev->recovery_disabled++;

	वापस 0;

 fail:
	pr_warn("md: failed to register dev-%s for %s\n",
		b, mdname(mddev));
	वापस err;
पूर्ण

अटल व्योम rdev_delayed_delete(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा md_rdev *rdev = container_of(ws, काष्ठा md_rdev, del_work);
	kobject_del(&rdev->kobj);
	kobject_put(&rdev->kobj);
पूर्ण

अटल व्योम unbind_rdev_from_array(काष्ठा md_rdev *rdev)
अणु
	अक्षर b[BDEVNAME_SIZE];

	bd_unlink_disk_holder(rdev->bdev, rdev->mddev->gendisk);
	list_del_rcu(&rdev->same_set);
	pr_debug("md: unbind<%s>\n", bdevname(rdev->bdev,b));
	mddev_destroy_serial_pool(rdev->mddev, rdev, false);
	rdev->mddev = शून्य;
	sysfs_हटाओ_link(&rdev->kobj, "block");
	sysfs_put(rdev->sysfs_state);
	sysfs_put(rdev->sysfs_unack_badblocks);
	sysfs_put(rdev->sysfs_badblocks);
	rdev->sysfs_state = शून्य;
	rdev->sysfs_unack_badblocks = शून्य;
	rdev->sysfs_badblocks = शून्य;
	rdev->badblocks.count = 0;
	/* We need to delay this, otherwise we can deadlock when
	 * writing to 'remove' to "dev/state".  We also need
	 * to delay it due to rcu usage.
	 */
	synchronize_rcu();
	INIT_WORK(&rdev->del_work, rdev_delayed_delete);
	kobject_get(&rdev->kobj);
	queue_work(md_rdev_misc_wq, &rdev->del_work);
पूर्ण

/*
 * prevent the device from being mounted, repartitioned or
 * otherwise reused by a RAID array (or any other kernel
 * subप्रणाली), by bd_claiming the device.
 */
अटल पूर्णांक lock_rdev(काष्ठा md_rdev *rdev, dev_t dev, पूर्णांक shared)
अणु
	पूर्णांक err = 0;
	काष्ठा block_device *bdev;

	bdev = blkdev_get_by_dev(dev, FMODE_READ|FMODE_WRITE|FMODE_EXCL,
				 shared ? (काष्ठा md_rdev *)lock_rdev : rdev);
	अगर (IS_ERR(bdev)) अणु
		pr_warn("md: could not open device unknown-block(%u,%u).\n",
			MAJOR(dev), MINOR(dev));
		वापस PTR_ERR(bdev);
	पूर्ण
	rdev->bdev = bdev;
	वापस err;
पूर्ण

अटल व्योम unlock_rdev(काष्ठा md_rdev *rdev)
अणु
	काष्ठा block_device *bdev = rdev->bdev;
	rdev->bdev = शून्य;
	blkdev_put(bdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);
पूर्ण

व्योम md_स्वतःdetect_dev(dev_t dev);

अटल व्योम export_rdev(काष्ठा md_rdev *rdev)
अणु
	अक्षर b[BDEVNAME_SIZE];

	pr_debug("md: export_rdev(%s)\n", bdevname(rdev->bdev,b));
	md_rdev_clear(rdev);
#अगर_अघोषित MODULE
	अगर (test_bit(AutoDetected, &rdev->flags))
		md_स्वतःdetect_dev(rdev->bdev->bd_dev);
#पूर्ण_अगर
	unlock_rdev(rdev);
	kobject_put(&rdev->kobj);
पूर्ण

व्योम md_kick_rdev_from_array(काष्ठा md_rdev *rdev)
अणु
	unbind_rdev_from_array(rdev);
	export_rdev(rdev);
पूर्ण
EXPORT_SYMBOL_GPL(md_kick_rdev_from_array);

अटल व्योम export_array(काष्ठा mddev *mddev)
अणु
	काष्ठा md_rdev *rdev;

	जबतक (!list_empty(&mddev->disks)) अणु
		rdev = list_first_entry(&mddev->disks, काष्ठा md_rdev,
					same_set);
		md_kick_rdev_from_array(rdev);
	पूर्ण
	mddev->raid_disks = 0;
	mddev->major_version = 0;
पूर्ण

अटल bool set_in_sync(काष्ठा mddev *mddev)
अणु
	lockdep_निश्चित_held(&mddev->lock);
	अगर (!mddev->in_sync) अणु
		mddev->sync_checkers++;
		spin_unlock(&mddev->lock);
		percpu_ref_चयन_to_atomic_sync(&mddev->ग_लिखोs_pending);
		spin_lock(&mddev->lock);
		अगर (!mddev->in_sync &&
		    percpu_ref_is_zero(&mddev->ग_लिखोs_pending)) अणु
			mddev->in_sync = 1;
			/*
			 * Ensure ->in_sync is visible beक्रमe we clear
			 * ->sync_checkers.
			 */
			smp_mb();
			set_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags);
			sysfs_notअगरy_dirent_safe(mddev->sysfs_state);
		पूर्ण
		अगर (--mddev->sync_checkers == 0)
			percpu_ref_चयन_to_percpu(&mddev->ग_लिखोs_pending);
	पूर्ण
	अगर (mddev->safemode == 1)
		mddev->safemode = 0;
	वापस mddev->in_sync;
पूर्ण

अटल व्योम sync_sbs(काष्ठा mddev *mddev, पूर्णांक nospares)
अणु
	/* Update each superblock (in-memory image), but
	 * अगर we are allowed to, skip spares which alपढ़ोy
	 * have the right event counter, or have one earlier
	 * (which would mean they aren't being marked as dirty
	 * with the rest of the array)
	 */
	काष्ठा md_rdev *rdev;
	rdev_क्रम_each(rdev, mddev) अणु
		अगर (rdev->sb_events == mddev->events ||
		    (nospares &&
		     rdev->raid_disk < 0 &&
		     rdev->sb_events+1 == mddev->events)) अणु
			/* Don't update this superblock */
			rdev->sb_loaded = 2;
		पूर्ण अन्यथा अणु
			sync_super(mddev, rdev);
			rdev->sb_loaded = 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool करोes_sb_need_changing(काष्ठा mddev *mddev)
अणु
	काष्ठा md_rdev *rdev;
	काष्ठा mdp_superblock_1 *sb;
	पूर्णांक role;

	/* Find a good rdev */
	rdev_क्रम_each(rdev, mddev)
		अगर ((rdev->raid_disk >= 0) && !test_bit(Faulty, &rdev->flags))
			अवरोध;

	/* No good device found. */
	अगर (!rdev)
		वापस false;

	sb = page_address(rdev->sb_page);
	/* Check अगर a device has become faulty or a spare become active */
	rdev_क्रम_each(rdev, mddev) अणु
		role = le16_to_cpu(sb->dev_roles[rdev->desc_nr]);
		/* Device activated? */
		अगर (role == 0xffff && rdev->raid_disk >=0 &&
		    !test_bit(Faulty, &rdev->flags))
			वापस true;
		/* Device turned faulty? */
		अगर (test_bit(Faulty, &rdev->flags) && (role < 0xfffd))
			वापस true;
	पूर्ण

	/* Check अगर any mddev parameters have changed */
	अगर ((mddev->dev_sectors != le64_to_cpu(sb->size)) ||
	    (mddev->reshape_position != le64_to_cpu(sb->reshape_position)) ||
	    (mddev->layout != le32_to_cpu(sb->layout)) ||
	    (mddev->raid_disks != le32_to_cpu(sb->raid_disks)) ||
	    (mddev->chunk_sectors != le32_to_cpu(sb->chunksize)))
		वापस true;

	वापस false;
पूर्ण

व्योम md_update_sb(काष्ठा mddev *mddev, पूर्णांक क्रमce_change)
अणु
	काष्ठा md_rdev *rdev;
	पूर्णांक sync_req;
	पूर्णांक nospares = 0;
	पूर्णांक any_badblocks_changed = 0;
	पूर्णांक ret = -1;

	अगर (mddev->ro) अणु
		अगर (क्रमce_change)
			set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
		वापस;
	पूर्ण

repeat:
	अगर (mddev_is_clustered(mddev)) अणु
		अगर (test_and_clear_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags))
			क्रमce_change = 1;
		अगर (test_and_clear_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags))
			nospares = 1;
		ret = md_cluster_ops->metadata_update_start(mddev);
		/* Has someone अन्यथा has updated the sb */
		अगर (!करोes_sb_need_changing(mddev)) अणु
			अगर (ret == 0)
				md_cluster_ops->metadata_update_cancel(mddev);
			bit_clear_unless(&mddev->sb_flags, BIT(MD_SB_CHANGE_PENDING),
							 BIT(MD_SB_CHANGE_DEVS) |
							 BIT(MD_SB_CHANGE_CLEAN));
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * First make sure inभागidual recovery_offsets are correct
	 * curr_resync_completed can only be used during recovery.
	 * During reshape/resync it might use array-addresses rather
	 * that device addresses.
	 */
	rdev_क्रम_each(rdev, mddev) अणु
		अगर (rdev->raid_disk >= 0 &&
		    mddev->delta_disks >= 0 &&
		    test_bit(MD_RECOVERY_RUNNING, &mddev->recovery) &&
		    test_bit(MD_RECOVERY_RECOVER, &mddev->recovery) &&
		    !test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
		    !test_bit(Journal, &rdev->flags) &&
		    !test_bit(In_sync, &rdev->flags) &&
		    mddev->curr_resync_completed > rdev->recovery_offset)
				rdev->recovery_offset = mddev->curr_resync_completed;

	पूर्ण
	अगर (!mddev->persistent) अणु
		clear_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags);
		clear_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
		अगर (!mddev->बाह्यal) अणु
			clear_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags);
			rdev_क्रम_each(rdev, mddev) अणु
				अगर (rdev->badblocks.changed) अणु
					rdev->badblocks.changed = 0;
					ack_all_badblocks(&rdev->badblocks);
					md_error(mddev, rdev);
				पूर्ण
				clear_bit(Blocked, &rdev->flags);
				clear_bit(BlockedBadBlocks, &rdev->flags);
				wake_up(&rdev->blocked_रुको);
			पूर्ण
		पूर्ण
		wake_up(&mddev->sb_रुको);
		वापस;
	पूर्ण

	spin_lock(&mddev->lock);

	mddev->uसमय = kसमय_get_real_seconds();

	अगर (test_and_clear_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags))
		क्रमce_change = 1;
	अगर (test_and_clear_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags))
		/* just a clean<-> dirty transition, possibly leave spares alone,
		 * though अगर events isn't the right even/odd, we will have to करो
		 * spares after all
		 */
		nospares = 1;
	अगर (क्रमce_change)
		nospares = 0;
	अगर (mddev->degraded)
		/* If the array is degraded, then skipping spares is both
		 * dangerous and fairly poपूर्णांकless.
		 * Dangerous because a device that was हटाओd from the array
		 * might have a event_count that still looks up-to-date,
		 * so it can be re-added without a resync.
		 * Poपूर्णांकless because अगर there are any spares to skip,
		 * then a recovery will happen and soon that array won't
		 * be degraded any more and the spare can go back to sleep then.
		 */
		nospares = 0;

	sync_req = mddev->in_sync;

	/* If this is just a dirty<->clean transition, and the array is clean
	 * and 'events' is odd, we can roll back to the previous clean state */
	अगर (nospares
	    && (mddev->in_sync && mddev->recovery_cp == MaxSector)
	    && mddev->can_decrease_events
	    && mddev->events != 1) अणु
		mddev->events--;
		mddev->can_decrease_events = 0;
	पूर्ण अन्यथा अणु
		/* otherwise we have to go क्रमward and ... */
		mddev->events ++;
		mddev->can_decrease_events = nospares;
	पूर्ण

	/*
	 * This 64-bit counter should never wrap.
	 * Either we are in around ~1 trillion A.C., assuming
	 * 1 reboot per second, or we have a bug...
	 */
	WARN_ON(mddev->events == 0);

	rdev_क्रम_each(rdev, mddev) अणु
		अगर (rdev->badblocks.changed)
			any_badblocks_changed++;
		अगर (test_bit(Faulty, &rdev->flags))
			set_bit(FaultRecorded, &rdev->flags);
	पूर्ण

	sync_sbs(mddev, nospares);
	spin_unlock(&mddev->lock);

	pr_debug("md: updating %s RAID superblock on device (in sync %d)\n",
		 mdname(mddev), mddev->in_sync);

	अगर (mddev->queue)
		blk_add_trace_msg(mddev->queue, "md md_update_sb");
reग_लिखो:
	md_biपंचांगap_update_sb(mddev->biपंचांगap);
	rdev_क्रम_each(rdev, mddev) अणु
		अक्षर b[BDEVNAME_SIZE];

		अगर (rdev->sb_loaded != 1)
			जारी; /* no noise on spare devices */

		अगर (!test_bit(Faulty, &rdev->flags)) अणु
			md_super_ग_लिखो(mddev,rdev,
				       rdev->sb_start, rdev->sb_size,
				       rdev->sb_page);
			pr_debug("md: (write) %s's sb offset: %llu\n",
				 bdevname(rdev->bdev, b),
				 (अचिन्हित दीर्घ दीर्घ)rdev->sb_start);
			rdev->sb_events = mddev->events;
			अगर (rdev->badblocks.size) अणु
				md_super_ग_लिखो(mddev, rdev,
					       rdev->badblocks.sector,
					       rdev->badblocks.size << 9,
					       rdev->bb_page);
				rdev->badblocks.size = 0;
			पूर्ण

		पूर्ण अन्यथा
			pr_debug("md: %s (skipping faulty)\n",
				 bdevname(rdev->bdev, b));

		अगर (mddev->level == LEVEL_MULTIPATH)
			/* only need to ग_लिखो one superblock... */
			अवरोध;
	पूर्ण
	अगर (md_super_रुको(mddev) < 0)
		जाओ reग_लिखो;
	/* अगर there was a failure, MD_SB_CHANGE_DEVS was set, and we re-ग_लिखो super */

	अगर (mddev_is_clustered(mddev) && ret == 0)
		md_cluster_ops->metadata_update_finish(mddev);

	अगर (mddev->in_sync != sync_req ||
	    !bit_clear_unless(&mddev->sb_flags, BIT(MD_SB_CHANGE_PENDING),
			       BIT(MD_SB_CHANGE_DEVS) | BIT(MD_SB_CHANGE_CLEAN)))
		/* have to ग_लिखो it out again */
		जाओ repeat;
	wake_up(&mddev->sb_रुको);
	अगर (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		sysfs_notअगरy_dirent_safe(mddev->sysfs_completed);

	rdev_क्रम_each(rdev, mddev) अणु
		अगर (test_and_clear_bit(FaultRecorded, &rdev->flags))
			clear_bit(Blocked, &rdev->flags);

		अगर (any_badblocks_changed)
			ack_all_badblocks(&rdev->badblocks);
		clear_bit(BlockedBadBlocks, &rdev->flags);
		wake_up(&rdev->blocked_रुको);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(md_update_sb);

अटल पूर्णांक add_bound_rdev(काष्ठा md_rdev *rdev)
अणु
	काष्ठा mddev *mddev = rdev->mddev;
	पूर्णांक err = 0;
	bool add_journal = test_bit(Journal, &rdev->flags);

	अगर (!mddev->pers->hot_हटाओ_disk || add_journal) अणु
		/* If there is hot_add_disk but no hot_हटाओ_disk
		 * then added disks क्रम geometry changes,
		 * and should be added immediately.
		 */
		super_types[mddev->major_version].
			validate_super(mddev, rdev);
		अगर (add_journal)
			mddev_suspend(mddev);
		err = mddev->pers->hot_add_disk(mddev, rdev);
		अगर (add_journal)
			mddev_resume(mddev);
		अगर (err) अणु
			md_kick_rdev_from_array(rdev);
			वापस err;
		पूर्ण
	पूर्ण
	sysfs_notअगरy_dirent_safe(rdev->sysfs_state);

	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
	अगर (mddev->degraded)
		set_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	md_new_event(mddev);
	md_wakeup_thपढ़ो(mddev->thपढ़ो);
	वापस 0;
पूर्ण

/* words written to sysfs files may, or may not, be \न terminated.
 * We want to accept with हाल. For this we use cmd_match.
 */
अटल पूर्णांक cmd_match(स्थिर अक्षर *cmd, स्थिर अक्षर *str)
अणु
	/* See अगर cmd, written पूर्णांकo a sysfs file, matches
	 * str.  They must either be the same, or cmd can
	 * have a trailing newline
	 */
	जबतक (*cmd && *str && *cmd == *str) अणु
		cmd++;
		str++;
	पूर्ण
	अगर (*cmd == '\n')
		cmd++;
	अगर (*str || *cmd)
		वापस 0;
	वापस 1;
पूर्ण

काष्ठा rdev_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा md_rdev *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा md_rdev *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

अटल sमाप_प्रकार
state_show(काष्ठा md_rdev *rdev, अक्षर *page)
अणु
	अक्षर *sep = ",";
	माप_प्रकार len = 0;
	अचिन्हित दीर्घ flags = READ_ONCE(rdev->flags);

	अगर (test_bit(Faulty, &flags) ||
	    (!test_bit(ExternalBbl, &flags) &&
	    rdev->badblocks.unacked_exist))
		len += प्र_लिखो(page+len, "faulty%s", sep);
	अगर (test_bit(In_sync, &flags))
		len += प्र_लिखो(page+len, "in_sync%s", sep);
	अगर (test_bit(Journal, &flags))
		len += प्र_लिखो(page+len, "journal%s", sep);
	अगर (test_bit(WriteMostly, &flags))
		len += प्र_लिखो(page+len, "write_mostly%s", sep);
	अगर (test_bit(Blocked, &flags) ||
	    (rdev->badblocks.unacked_exist
	     && !test_bit(Faulty, &flags)))
		len += प्र_लिखो(page+len, "blocked%s", sep);
	अगर (!test_bit(Faulty, &flags) &&
	    !test_bit(Journal, &flags) &&
	    !test_bit(In_sync, &flags))
		len += प्र_लिखो(page+len, "spare%s", sep);
	अगर (test_bit(WriteErrorSeen, &flags))
		len += प्र_लिखो(page+len, "write_error%s", sep);
	अगर (test_bit(WantReplacement, &flags))
		len += प्र_लिखो(page+len, "want_replacement%s", sep);
	अगर (test_bit(Replacement, &flags))
		len += प्र_लिखो(page+len, "replacement%s", sep);
	अगर (test_bit(ExternalBbl, &flags))
		len += प्र_लिखो(page+len, "external_bbl%s", sep);
	अगर (test_bit(FailFast, &flags))
		len += प्र_लिखो(page+len, "failfast%s", sep);

	अगर (len)
		len -= म_माप(sep);

	वापस len+प्र_लिखो(page+len, "\n");
पूर्ण

अटल sमाप_प्रकार
state_store(काष्ठा md_rdev *rdev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	/* can ग_लिखो
	 *  faulty  - simulates an error
	 *  हटाओ  - disconnects the device
	 *  ग_लिखोmostly - sets ग_लिखो_mostly
	 *  -ग_लिखोmostly - clears ग_लिखो_mostly
	 *  blocked - sets the Blocked flags
	 *  -blocked - clears the Blocked and possibly simulates an error
	 *  insync - sets Insync providing device isn't active
	 *  -insync - clear Insync क्रम a device with a slot asचिन्हित,
	 *            so that it माला_लो rebuilt based on biपंचांगap
	 *  ग_लिखो_error - sets WriteErrorSeen
	 *  -ग_लिखो_error - clears WriteErrorSeen
	 *  अणु,-पूर्णfailfast - set/clear FailFast
	 */
	पूर्णांक err = -EINVAL;
	अगर (cmd_match(buf, "faulty") && rdev->mddev->pers) अणु
		md_error(rdev->mddev, rdev);
		अगर (test_bit(Faulty, &rdev->flags))
			err = 0;
		अन्यथा
			err = -EBUSY;
	पूर्ण अन्यथा अगर (cmd_match(buf, "remove")) अणु
		अगर (rdev->mddev->pers) अणु
			clear_bit(Blocked, &rdev->flags);
			हटाओ_and_add_spares(rdev->mddev, rdev);
		पूर्ण
		अगर (rdev->raid_disk >= 0)
			err = -EBUSY;
		अन्यथा अणु
			काष्ठा mddev *mddev = rdev->mddev;
			err = 0;
			अगर (mddev_is_clustered(mddev))
				err = md_cluster_ops->हटाओ_disk(mddev, rdev);

			अगर (err == 0) अणु
				md_kick_rdev_from_array(rdev);
				अगर (mddev->pers) अणु
					set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
					md_wakeup_thपढ़ो(mddev->thपढ़ो);
				पूर्ण
				md_new_event(mddev);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (cmd_match(buf, "writemostly")) अणु
		set_bit(WriteMostly, &rdev->flags);
		mddev_create_serial_pool(rdev->mddev, rdev, false);
		err = 0;
	पूर्ण अन्यथा अगर (cmd_match(buf, "-writemostly")) अणु
		mddev_destroy_serial_pool(rdev->mddev, rdev, false);
		clear_bit(WriteMostly, &rdev->flags);
		err = 0;
	पूर्ण अन्यथा अगर (cmd_match(buf, "blocked")) अणु
		set_bit(Blocked, &rdev->flags);
		err = 0;
	पूर्ण अन्यथा अगर (cmd_match(buf, "-blocked")) अणु
		अगर (!test_bit(Faulty, &rdev->flags) &&
		    !test_bit(ExternalBbl, &rdev->flags) &&
		    rdev->badblocks.unacked_exist) अणु
			/* metadata handler करोesn't understand badblocks,
			 * so we need to fail the device
			 */
			md_error(rdev->mddev, rdev);
		पूर्ण
		clear_bit(Blocked, &rdev->flags);
		clear_bit(BlockedBadBlocks, &rdev->flags);
		wake_up(&rdev->blocked_रुको);
		set_bit(MD_RECOVERY_NEEDED, &rdev->mddev->recovery);
		md_wakeup_thपढ़ो(rdev->mddev->thपढ़ो);

		err = 0;
	पूर्ण अन्यथा अगर (cmd_match(buf, "insync") && rdev->raid_disk == -1) अणु
		set_bit(In_sync, &rdev->flags);
		err = 0;
	पूर्ण अन्यथा अगर (cmd_match(buf, "failfast")) अणु
		set_bit(FailFast, &rdev->flags);
		err = 0;
	पूर्ण अन्यथा अगर (cmd_match(buf, "-failfast")) अणु
		clear_bit(FailFast, &rdev->flags);
		err = 0;
	पूर्ण अन्यथा अगर (cmd_match(buf, "-insync") && rdev->raid_disk >= 0 &&
		   !test_bit(Journal, &rdev->flags)) अणु
		अगर (rdev->mddev->pers == शून्य) अणु
			clear_bit(In_sync, &rdev->flags);
			rdev->saved_raid_disk = rdev->raid_disk;
			rdev->raid_disk = -1;
			err = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd_match(buf, "write_error")) अणु
		set_bit(WriteErrorSeen, &rdev->flags);
		err = 0;
	पूर्ण अन्यथा अगर (cmd_match(buf, "-write_error")) अणु
		clear_bit(WriteErrorSeen, &rdev->flags);
		err = 0;
	पूर्ण अन्यथा अगर (cmd_match(buf, "want_replacement")) अणु
		/* Any non-spare device that is not a replacement can
		 * become want_replacement at any समय, but we then need to
		 * check अगर recovery is needed.
		 */
		अगर (rdev->raid_disk >= 0 &&
		    !test_bit(Journal, &rdev->flags) &&
		    !test_bit(Replacement, &rdev->flags))
			set_bit(WantReplacement, &rdev->flags);
		set_bit(MD_RECOVERY_NEEDED, &rdev->mddev->recovery);
		md_wakeup_thपढ़ो(rdev->mddev->thपढ़ो);
		err = 0;
	पूर्ण अन्यथा अगर (cmd_match(buf, "-want_replacement")) अणु
		/* Clearing 'want_replacement' is always allowed.
		 * Once replacements starts it is too late though.
		 */
		err = 0;
		clear_bit(WantReplacement, &rdev->flags);
	पूर्ण अन्यथा अगर (cmd_match(buf, "replacement")) अणु
		/* Can only set a device as a replacement when array has not
		 * yet been started.  Once running, replacement is स्वतःmatic
		 * from spares, or by assigning 'slot'.
		 */
		अगर (rdev->mddev->pers)
			err = -EBUSY;
		अन्यथा अणु
			set_bit(Replacement, &rdev->flags);
			err = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd_match(buf, "-replacement")) अणु
		/* Similarly, can only clear Replacement beक्रमe start */
		अगर (rdev->mddev->pers)
			err = -EBUSY;
		अन्यथा अणु
			clear_bit(Replacement, &rdev->flags);
			err = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (cmd_match(buf, "re-add")) अणु
		अगर (!rdev->mddev->pers)
			err = -EINVAL;
		अन्यथा अगर (test_bit(Faulty, &rdev->flags) && (rdev->raid_disk == -1) &&
				rdev->saved_raid_disk >= 0) अणु
			/* clear_bit is perक्रमmed _after_ all the devices
			 * have their local Faulty bit cleared. If any ग_लिखोs
			 * happen in the meanसमय in the local node, they
			 * will land in the local biपंचांगap, which will be synced
			 * by this node eventually
			 */
			अगर (!mddev_is_clustered(rdev->mddev) ||
			    (err = md_cluster_ops->gather_biपंचांगaps(rdev)) == 0) अणु
				clear_bit(Faulty, &rdev->flags);
				err = add_bound_rdev(rdev);
			पूर्ण
		पूर्ण अन्यथा
			err = -EBUSY;
	पूर्ण अन्यथा अगर (cmd_match(buf, "external_bbl") && (rdev->mddev->बाह्यal)) अणु
		set_bit(ExternalBbl, &rdev->flags);
		rdev->badblocks.shअगरt = 0;
		err = 0;
	पूर्ण अन्यथा अगर (cmd_match(buf, "-external_bbl") && (rdev->mddev->बाह्यal)) अणु
		clear_bit(ExternalBbl, &rdev->flags);
		err = 0;
	पूर्ण
	अगर (!err)
		sysfs_notअगरy_dirent_safe(rdev->sysfs_state);
	वापस err ? err : len;
पूर्ण
अटल काष्ठा rdev_sysfs_entry rdev_state =
__ATTR_PREALLOC(state, S_IRUGO|S_IWUSR, state_show, state_store);

अटल sमाप_प्रकार
errors_show(काष्ठा md_rdev *rdev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", atomic_पढ़ो(&rdev->corrected_errors));
पूर्ण

अटल sमाप_प्रकार
errors_store(काष्ठा md_rdev *rdev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक n;
	पूर्णांक rv;

	rv = kstrtouपूर्णांक(buf, 10, &n);
	अगर (rv < 0)
		वापस rv;
	atomic_set(&rdev->corrected_errors, n);
	वापस len;
पूर्ण
अटल काष्ठा rdev_sysfs_entry rdev_errors =
__ATTR(errors, S_IRUGO|S_IWUSR, errors_show, errors_store);

अटल sमाप_प्रकार
slot_show(काष्ठा md_rdev *rdev, अक्षर *page)
अणु
	अगर (test_bit(Journal, &rdev->flags))
		वापस प्र_लिखो(page, "journal\n");
	अन्यथा अगर (rdev->raid_disk < 0)
		वापस प्र_लिखो(page, "none\n");
	अन्यथा
		वापस प्र_लिखो(page, "%d\n", rdev->raid_disk);
पूर्ण

अटल sमाप_प्रकार
slot_store(काष्ठा md_rdev *rdev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक slot;
	पूर्णांक err;

	अगर (test_bit(Journal, &rdev->flags))
		वापस -EBUSY;
	अगर (म_भेदन(buf, "none", 4)==0)
		slot = -1;
	अन्यथा अणु
		err = kstrtouपूर्णांक(buf, 10, (अचिन्हित पूर्णांक *)&slot);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (rdev->mddev->pers && slot == -1) अणु
		/* Setting 'slot' on an active array requires also
		 * updating the 'rd%d' link, and communicating
		 * with the personality with ->hot_*_disk.
		 * For now we only support removing
		 * failed/spare devices.  This normally happens स्वतःmatically,
		 * but not when the metadata is बाह्यally managed.
		 */
		अगर (rdev->raid_disk == -1)
			वापस -EEXIST;
		/* personality करोes all needed checks */
		अगर (rdev->mddev->pers->hot_हटाओ_disk == शून्य)
			वापस -EINVAL;
		clear_bit(Blocked, &rdev->flags);
		हटाओ_and_add_spares(rdev->mddev, rdev);
		अगर (rdev->raid_disk >= 0)
			वापस -EBUSY;
		set_bit(MD_RECOVERY_NEEDED, &rdev->mddev->recovery);
		md_wakeup_thपढ़ो(rdev->mddev->thपढ़ो);
	पूर्ण अन्यथा अगर (rdev->mddev->pers) अणु
		/* Activating a spare .. or possibly reactivating
		 * अगर we ever get biपंचांगaps working here.
		 */
		पूर्णांक err;

		अगर (rdev->raid_disk != -1)
			वापस -EBUSY;

		अगर (test_bit(MD_RECOVERY_RUNNING, &rdev->mddev->recovery))
			वापस -EBUSY;

		अगर (rdev->mddev->pers->hot_add_disk == शून्य)
			वापस -EINVAL;

		अगर (slot >= rdev->mddev->raid_disks &&
		    slot >= rdev->mddev->raid_disks + rdev->mddev->delta_disks)
			वापस -ENOSPC;

		rdev->raid_disk = slot;
		अगर (test_bit(In_sync, &rdev->flags))
			rdev->saved_raid_disk = slot;
		अन्यथा
			rdev->saved_raid_disk = -1;
		clear_bit(In_sync, &rdev->flags);
		clear_bit(Biपंचांगap_sync, &rdev->flags);
		err = rdev->mddev->pers->hot_add_disk(rdev->mddev, rdev);
		अगर (err) अणु
			rdev->raid_disk = -1;
			वापस err;
		पूर्ण अन्यथा
			sysfs_notअगरy_dirent_safe(rdev->sysfs_state);
		/* failure here is OK */;
		sysfs_link_rdev(rdev->mddev, rdev);
		/* करोn't wakeup anyone, leave that to userspace. */
	पूर्ण अन्यथा अणु
		अगर (slot >= rdev->mddev->raid_disks &&
		    slot >= rdev->mddev->raid_disks + rdev->mddev->delta_disks)
			वापस -ENOSPC;
		rdev->raid_disk = slot;
		/* assume it is working */
		clear_bit(Faulty, &rdev->flags);
		clear_bit(WriteMostly, &rdev->flags);
		set_bit(In_sync, &rdev->flags);
		sysfs_notअगरy_dirent_safe(rdev->sysfs_state);
	पूर्ण
	वापस len;
पूर्ण

अटल काष्ठा rdev_sysfs_entry rdev_slot =
__ATTR(slot, S_IRUGO|S_IWUSR, slot_show, slot_store);

अटल sमाप_प्रकार
offset_show(काष्ठा md_rdev *rdev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n", (अचिन्हित दीर्घ दीर्घ)rdev->data_offset);
पूर्ण

अटल sमाप_प्रकार
offset_store(काष्ठा md_rdev *rdev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ दीर्घ offset;
	अगर (kम_से_अदीर्घl(buf, 10, &offset) < 0)
		वापस -EINVAL;
	अगर (rdev->mddev->pers && rdev->raid_disk >= 0)
		वापस -EBUSY;
	अगर (rdev->sectors && rdev->mddev->बाह्यal)
		/* Must set offset beक्रमe size, so overlap checks
		 * can be sane */
		वापस -EBUSY;
	rdev->data_offset = offset;
	rdev->new_data_offset = offset;
	वापस len;
पूर्ण

अटल काष्ठा rdev_sysfs_entry rdev_offset =
__ATTR(offset, S_IRUGO|S_IWUSR, offset_show, offset_store);

अटल sमाप_प्रकार new_offset_show(काष्ठा md_rdev *rdev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n",
		       (अचिन्हित दीर्घ दीर्घ)rdev->new_data_offset);
पूर्ण

अटल sमाप_प्रकार new_offset_store(काष्ठा md_rdev *rdev,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ दीर्घ new_offset;
	काष्ठा mddev *mddev = rdev->mddev;

	अगर (kम_से_अदीर्घl(buf, 10, &new_offset) < 0)
		वापस -EINVAL;

	अगर (mddev->sync_thपढ़ो ||
	    test_bit(MD_RECOVERY_RUNNING,&mddev->recovery))
		वापस -EBUSY;
	अगर (new_offset == rdev->data_offset)
		/* reset is always permitted */
		;
	अन्यथा अगर (new_offset > rdev->data_offset) अणु
		/* must not push array size beyond rdev_sectors */
		अगर (new_offset - rdev->data_offset
		    + mddev->dev_sectors > rdev->sectors)
				वापस -E2BIG;
	पूर्ण
	/* Metadata worries about other space details. */

	/* decreasing the offset is inconsistent with a backwards
	 * reshape.
	 */
	अगर (new_offset < rdev->data_offset &&
	    mddev->reshape_backwards)
		वापस -EINVAL;
	/* Increasing offset is inconsistent with क्रमwards
	 * reshape.  reshape_direction should be set to
	 * 'backwards' first.
	 */
	अगर (new_offset > rdev->data_offset &&
	    !mddev->reshape_backwards)
		वापस -EINVAL;

	अगर (mddev->pers && mddev->persistent &&
	    !super_types[mddev->major_version]
	    .allow_new_offset(rdev, new_offset))
		वापस -E2BIG;
	rdev->new_data_offset = new_offset;
	अगर (new_offset > rdev->data_offset)
		mddev->reshape_backwards = 1;
	अन्यथा अगर (new_offset < rdev->data_offset)
		mddev->reshape_backwards = 0;

	वापस len;
पूर्ण
अटल काष्ठा rdev_sysfs_entry rdev_new_offset =
__ATTR(new_offset, S_IRUGO|S_IWUSR, new_offset_show, new_offset_store);

अटल sमाप_प्रकार
rdev_size_show(काष्ठा md_rdev *rdev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n", (अचिन्हित दीर्घ दीर्घ)rdev->sectors / 2);
पूर्ण

अटल पूर्णांक overlaps(sector_t s1, sector_t l1, sector_t s2, sector_t l2)
अणु
	/* check अगर two start/length pairs overlap */
	अगर (s1+l1 <= s2)
		वापस 0;
	अगर (s2+l2 <= s1)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक strict_blocks_to_sectors(स्थिर अक्षर *buf, sector_t *sectors)
अणु
	अचिन्हित दीर्घ दीर्घ blocks;
	sector_t new;

	अगर (kम_से_अदीर्घl(buf, 10, &blocks) < 0)
		वापस -EINVAL;

	अगर (blocks & 1ULL << (8 * माप(blocks) - 1))
		वापस -EINVAL; /* sector conversion overflow */

	new = blocks * 2;
	अगर (new != blocks * 2)
		वापस -EINVAL; /* अचिन्हित दीर्घ दीर्घ to sector_t overflow */

	*sectors = new;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
rdev_size_store(काष्ठा md_rdev *rdev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा mddev *my_mddev = rdev->mddev;
	sector_t oldsectors = rdev->sectors;
	sector_t sectors;

	अगर (test_bit(Journal, &rdev->flags))
		वापस -EBUSY;
	अगर (strict_blocks_to_sectors(buf, &sectors) < 0)
		वापस -EINVAL;
	अगर (rdev->data_offset != rdev->new_data_offset)
		वापस -EINVAL; /* too confusing */
	अगर (my_mddev->pers && rdev->raid_disk >= 0) अणु
		अगर (my_mddev->persistent) अणु
			sectors = super_types[my_mddev->major_version].
				rdev_size_change(rdev, sectors);
			अगर (!sectors)
				वापस -EBUSY;
		पूर्ण अन्यथा अगर (!sectors)
			sectors = (i_size_पढ़ो(rdev->bdev->bd_inode) >> 9) -
				rdev->data_offset;
		अगर (!my_mddev->pers->resize)
			/* Cannot change size क्रम RAID0 or Linear etc */
			वापस -EINVAL;
	पूर्ण
	अगर (sectors < my_mddev->dev_sectors)
		वापस -EINVAL; /* component must fit device */

	rdev->sectors = sectors;
	अगर (sectors > oldsectors && my_mddev->बाह्यal) अणु
		/* Need to check that all other rdevs with the same
		 * ->bdev करो not overlap.  'rcu' is sufficient to walk
		 * the rdev lists safely.
		 * This check करोes not provide a hard guarantee, it
		 * just helps aव्योम dangerous mistakes.
		 */
		काष्ठा mddev *mddev;
		पूर्णांक overlap = 0;
		काष्ठा list_head *पंचांगp;

		rcu_पढ़ो_lock();
		क्रम_each_mddev(mddev, पंचांगp) अणु
			काष्ठा md_rdev *rdev2;

			rdev_क्रम_each(rdev2, mddev)
				अगर (rdev->bdev == rdev2->bdev &&
				    rdev != rdev2 &&
				    overlaps(rdev->data_offset, rdev->sectors,
					     rdev2->data_offset,
					     rdev2->sectors)) अणु
					overlap = 1;
					अवरोध;
				पूर्ण
			अगर (overlap) अणु
				mddev_put(mddev);
				अवरोध;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
		अगर (overlap) अणु
			/* Someone अन्यथा could have slipped in a size
			 * change here, but करोing so is just silly.
			 * We put oldsectors back because we *know* it is
			 * safe, and trust userspace not to race with
			 * itself
			 */
			rdev->sectors = oldsectors;
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	वापस len;
पूर्ण

अटल काष्ठा rdev_sysfs_entry rdev_size =
__ATTR(size, S_IRUGO|S_IWUSR, rdev_size_show, rdev_size_store);

अटल sमाप_प्रकार recovery_start_show(काष्ठा md_rdev *rdev, अक्षर *page)
अणु
	अचिन्हित दीर्घ दीर्घ recovery_start = rdev->recovery_offset;

	अगर (test_bit(In_sync, &rdev->flags) ||
	    recovery_start == MaxSector)
		वापस प्र_लिखो(page, "none\n");

	वापस प्र_लिखो(page, "%llu\n", recovery_start);
पूर्ण

अटल sमाप_प्रकार recovery_start_store(काष्ठा md_rdev *rdev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ दीर्घ recovery_start;

	अगर (cmd_match(buf, "none"))
		recovery_start = MaxSector;
	अन्यथा अगर (kम_से_अदीर्घl(buf, 10, &recovery_start))
		वापस -EINVAL;

	अगर (rdev->mddev->pers &&
	    rdev->raid_disk >= 0)
		वापस -EBUSY;

	rdev->recovery_offset = recovery_start;
	अगर (recovery_start == MaxSector)
		set_bit(In_sync, &rdev->flags);
	अन्यथा
		clear_bit(In_sync, &rdev->flags);
	वापस len;
पूर्ण

अटल काष्ठा rdev_sysfs_entry rdev_recovery_start =
__ATTR(recovery_start, S_IRUGO|S_IWUSR, recovery_start_show, recovery_start_store);

/* sysfs access to bad-blocks list.
 * We present two files.
 * 'bad-blocks' lists sector numbers and lengths of ranges that
 *    are recorded as bad.  The list is truncated to fit within
 *    the one-page limit of sysfs.
 *    Writing "sector length" to this file adds an acknowledged
 *    bad block list.
 * 'unacknowledged-bad-blocks' lists bad blocks that have not yet
 *    been acknowledged.  Writing to this file adds bad blocks
 *    without acknowledging them.  This is largely क्रम testing.
 */
अटल sमाप_प्रकार bb_show(काष्ठा md_rdev *rdev, अक्षर *page)
अणु
	वापस badblocks_show(&rdev->badblocks, page, 0);
पूर्ण
अटल sमाप_प्रकार bb_store(काष्ठा md_rdev *rdev, स्थिर अक्षर *page, माप_प्रकार len)
अणु
	पूर्णांक rv = badblocks_store(&rdev->badblocks, page, len, 0);
	/* Maybe that ack was all we needed */
	अगर (test_and_clear_bit(BlockedBadBlocks, &rdev->flags))
		wake_up(&rdev->blocked_रुको);
	वापस rv;
पूर्ण
अटल काष्ठा rdev_sysfs_entry rdev_bad_blocks =
__ATTR(bad_blocks, S_IRUGO|S_IWUSR, bb_show, bb_store);

अटल sमाप_प्रकार ubb_show(काष्ठा md_rdev *rdev, अक्षर *page)
अणु
	वापस badblocks_show(&rdev->badblocks, page, 1);
पूर्ण
अटल sमाप_प्रकार ubb_store(काष्ठा md_rdev *rdev, स्थिर अक्षर *page, माप_प्रकार len)
अणु
	वापस badblocks_store(&rdev->badblocks, page, len, 1);
पूर्ण
अटल काष्ठा rdev_sysfs_entry rdev_unack_bad_blocks =
__ATTR(unacknowledged_bad_blocks, S_IRUGO|S_IWUSR, ubb_show, ubb_store);

अटल sमाप_प्रकार
ppl_sector_show(काष्ठा md_rdev *rdev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n", (अचिन्हित दीर्घ दीर्घ)rdev->ppl.sector);
पूर्ण

अटल sमाप_प्रकार
ppl_sector_store(काष्ठा md_rdev *rdev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ दीर्घ sector;

	अगर (kम_से_अदीर्घl(buf, 10, &sector) < 0)
		वापस -EINVAL;
	अगर (sector != (sector_t)sector)
		वापस -EINVAL;

	अगर (rdev->mddev->pers && test_bit(MD_HAS_PPL, &rdev->mddev->flags) &&
	    rdev->raid_disk >= 0)
		वापस -EBUSY;

	अगर (rdev->mddev->persistent) अणु
		अगर (rdev->mddev->major_version == 0)
			वापस -EINVAL;
		अगर ((sector > rdev->sb_start &&
		     sector - rdev->sb_start > S16_MAX) ||
		    (sector < rdev->sb_start &&
		     rdev->sb_start - sector > -S16_MIN))
			वापस -EINVAL;
		rdev->ppl.offset = sector - rdev->sb_start;
	पूर्ण अन्यथा अगर (!rdev->mddev->बाह्यal) अणु
		वापस -EBUSY;
	पूर्ण
	rdev->ppl.sector = sector;
	वापस len;
पूर्ण

अटल काष्ठा rdev_sysfs_entry rdev_ppl_sector =
__ATTR(ppl_sector, S_IRUGO|S_IWUSR, ppl_sector_show, ppl_sector_store);

अटल sमाप_प्रकार
ppl_size_show(काष्ठा md_rdev *rdev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", rdev->ppl.size);
पूर्ण

अटल sमाप_प्रकार
ppl_size_store(काष्ठा md_rdev *rdev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक size;

	अगर (kstrtouपूर्णांक(buf, 10, &size) < 0)
		वापस -EINVAL;

	अगर (rdev->mddev->pers && test_bit(MD_HAS_PPL, &rdev->mddev->flags) &&
	    rdev->raid_disk >= 0)
		वापस -EBUSY;

	अगर (rdev->mddev->persistent) अणु
		अगर (rdev->mddev->major_version == 0)
			वापस -EINVAL;
		अगर (size > U16_MAX)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (!rdev->mddev->बाह्यal) अणु
		वापस -EBUSY;
	पूर्ण
	rdev->ppl.size = size;
	वापस len;
पूर्ण

अटल काष्ठा rdev_sysfs_entry rdev_ppl_size =
__ATTR(ppl_size, S_IRUGO|S_IWUSR, ppl_size_show, ppl_size_store);

अटल काष्ठा attribute *rdev_शेष_attrs[] = अणु
	&rdev_state.attr,
	&rdev_errors.attr,
	&rdev_slot.attr,
	&rdev_offset.attr,
	&rdev_new_offset.attr,
	&rdev_size.attr,
	&rdev_recovery_start.attr,
	&rdev_bad_blocks.attr,
	&rdev_unack_bad_blocks.attr,
	&rdev_ppl_sector.attr,
	&rdev_ppl_size.attr,
	शून्य,
पूर्ण;
अटल sमाप_प्रकार
rdev_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr, अक्षर *page)
अणु
	काष्ठा rdev_sysfs_entry *entry = container_of(attr, काष्ठा rdev_sysfs_entry, attr);
	काष्ठा md_rdev *rdev = container_of(kobj, काष्ठा md_rdev, kobj);

	अगर (!entry->show)
		वापस -EIO;
	अगर (!rdev->mddev)
		वापस -ENODEV;
	वापस entry->show(rdev, page);
पूर्ण

अटल sमाप_प्रकार
rdev_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
	      स्थिर अक्षर *page, माप_प्रकार length)
अणु
	काष्ठा rdev_sysfs_entry *entry = container_of(attr, काष्ठा rdev_sysfs_entry, attr);
	काष्ठा md_rdev *rdev = container_of(kobj, काष्ठा md_rdev, kobj);
	sमाप_प्रकार rv;
	काष्ठा mddev *mddev = rdev->mddev;

	अगर (!entry->store)
		वापस -EIO;
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	rv = mddev ? mddev_lock(mddev) : -ENODEV;
	अगर (!rv) अणु
		अगर (rdev->mddev == शून्य)
			rv = -ENODEV;
		अन्यथा
			rv = entry->store(rdev, page, length);
		mddev_unlock(mddev);
	पूर्ण
	वापस rv;
पूर्ण

अटल व्योम rdev_मुक्त(काष्ठा kobject *ko)
अणु
	काष्ठा md_rdev *rdev = container_of(ko, काष्ठा md_rdev, kobj);
	kमुक्त(rdev);
पूर्ण
अटल स्थिर काष्ठा sysfs_ops rdev_sysfs_ops = अणु
	.show		= rdev_attr_show,
	.store		= rdev_attr_store,
पूर्ण;
अटल काष्ठा kobj_type rdev_ktype = अणु
	.release	= rdev_मुक्त,
	.sysfs_ops	= &rdev_sysfs_ops,
	.शेष_attrs	= rdev_शेष_attrs,
पूर्ण;

पूर्णांक md_rdev_init(काष्ठा md_rdev *rdev)
अणु
	rdev->desc_nr = -1;
	rdev->saved_raid_disk = -1;
	rdev->raid_disk = -1;
	rdev->flags = 0;
	rdev->data_offset = 0;
	rdev->new_data_offset = 0;
	rdev->sb_events = 0;
	rdev->last_पढ़ो_error = 0;
	rdev->sb_loaded = 0;
	rdev->bb_page = शून्य;
	atomic_set(&rdev->nr_pending, 0);
	atomic_set(&rdev->पढ़ो_errors, 0);
	atomic_set(&rdev->corrected_errors, 0);

	INIT_LIST_HEAD(&rdev->same_set);
	init_रुकोqueue_head(&rdev->blocked_रुको);

	/* Add space to store bad block list.
	 * This reserves the space even on arrays where it cannot
	 * be used - I wonder अगर that matters
	 */
	वापस badblocks_init(&rdev->badblocks, 0);
पूर्ण
EXPORT_SYMBOL_GPL(md_rdev_init);
/*
 * Import a device. If 'super_format' >= 0, then sanity check the superblock
 *
 * mark the device faulty अगर:
 *
 *   - the device is nonexistent (zero size)
 *   - the device has no valid superblock
 *
 * a faulty rdev _never_ has rdev->sb set.
 */
अटल काष्ठा md_rdev *md_import_device(dev_t newdev, पूर्णांक super_क्रमmat, पूर्णांक super_minor)
अणु
	अक्षर b[BDEVNAME_SIZE];
	पूर्णांक err;
	काष्ठा md_rdev *rdev;
	sector_t size;

	rdev = kzalloc(माप(*rdev), GFP_KERNEL);
	अगर (!rdev)
		वापस ERR_PTR(-ENOMEM);

	err = md_rdev_init(rdev);
	अगर (err)
		जाओ पात_मुक्त;
	err = alloc_disk_sb(rdev);
	अगर (err)
		जाओ पात_मुक्त;

	err = lock_rdev(rdev, newdev, super_क्रमmat == -2);
	अगर (err)
		जाओ पात_मुक्त;

	kobject_init(&rdev->kobj, &rdev_ktype);

	size = i_size_पढ़ो(rdev->bdev->bd_inode) >> BLOCK_SIZE_BITS;
	अगर (!size) अणु
		pr_warn("md: %s has zero or unknown size, marking faulty!\n",
			bdevname(rdev->bdev,b));
		err = -EINVAL;
		जाओ पात_मुक्त;
	पूर्ण

	अगर (super_क्रमmat >= 0) अणु
		err = super_types[super_क्रमmat].
			load_super(rdev, शून्य, super_minor);
		अगर (err == -EINVAL) अणु
			pr_warn("md: %s does not have a valid v%d.%d superblock, not importing!\n",
				bdevname(rdev->bdev,b),
				super_क्रमmat, super_minor);
			जाओ पात_मुक्त;
		पूर्ण
		अगर (err < 0) अणु
			pr_warn("md: could not read %s's sb, not importing!\n",
				bdevname(rdev->bdev,b));
			जाओ पात_मुक्त;
		पूर्ण
	पूर्ण

	वापस rdev;

पात_मुक्त:
	अगर (rdev->bdev)
		unlock_rdev(rdev);
	md_rdev_clear(rdev);
	kमुक्त(rdev);
	वापस ERR_PTR(err);
पूर्ण

/*
 * Check a full RAID array क्रम plausibility
 */

अटल पूर्णांक analyze_sbs(काष्ठा mddev *mddev)
अणु
	पूर्णांक i;
	काष्ठा md_rdev *rdev, *freshest, *पंचांगp;
	अक्षर b[BDEVNAME_SIZE];

	freshest = शून्य;
	rdev_क्रम_each_safe(rdev, पंचांगp, mddev)
		चयन (super_types[mddev->major_version].
			load_super(rdev, freshest, mddev->minor_version)) अणु
		हाल 1:
			freshest = rdev;
			अवरोध;
		हाल 0:
			अवरोध;
		शेष:
			pr_warn("md: fatal superblock inconsistency in %s -- removing from array\n",
				bdevname(rdev->bdev,b));
			md_kick_rdev_from_array(rdev);
		पूर्ण

	/* Cannot find a valid fresh disk */
	अगर (!freshest) अणु
		pr_warn("md: cannot find a valid disk\n");
		वापस -EINVAL;
	पूर्ण

	super_types[mddev->major_version].
		validate_super(mddev, freshest);

	i = 0;
	rdev_क्रम_each_safe(rdev, पंचांगp, mddev) अणु
		अगर (mddev->max_disks &&
		    (rdev->desc_nr >= mddev->max_disks ||
		     i > mddev->max_disks)) अणु
			pr_warn("md: %s: %s: only %d devices permitted\n",
				mdname(mddev), bdevname(rdev->bdev, b),
				mddev->max_disks);
			md_kick_rdev_from_array(rdev);
			जारी;
		पूर्ण
		अगर (rdev != freshest) अणु
			अगर (super_types[mddev->major_version].
			    validate_super(mddev, rdev)) अणु
				pr_warn("md: kicking non-fresh %s from array!\n",
					bdevname(rdev->bdev,b));
				md_kick_rdev_from_array(rdev);
				जारी;
			पूर्ण
		पूर्ण
		अगर (mddev->level == LEVEL_MULTIPATH) अणु
			rdev->desc_nr = i++;
			rdev->raid_disk = rdev->desc_nr;
			set_bit(In_sync, &rdev->flags);
		पूर्ण अन्यथा अगर (rdev->raid_disk >=
			    (mddev->raid_disks - min(0, mddev->delta_disks)) &&
			   !test_bit(Journal, &rdev->flags)) अणु
			rdev->raid_disk = -1;
			clear_bit(In_sync, &rdev->flags);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Read a fixed-poपूर्णांक number.
 * Numbers in sysfs attributes should be in "standard" units where
 * possible, so समय should be in seconds.
 * However we पूर्णांकernally use a a much smaller unit such as
 * milliseconds or jअगरfies.
 * This function takes a decimal number with a possible fractional
 * component, and produces an पूर्णांकeger which is the result of
 * multiplying that number by 10^'scale'.
 * all without any भग्नing-poपूर्णांक arithmetic.
 */
पूर्णांक strict_म_से_अदीर्घ_scaled(स्थिर अक्षर *cp, अचिन्हित दीर्घ *res, पूर्णांक scale)
अणु
	अचिन्हित दीर्घ result = 0;
	दीर्घ decimals = -1;
	जबतक (है_अंक(*cp) || (*cp == '.' && decimals < 0)) अणु
		अगर (*cp == '.')
			decimals = 0;
		अन्यथा अगर (decimals < scale) अणु
			अचिन्हित पूर्णांक value;
			value = *cp - '0';
			result = result * 10 + value;
			अगर (decimals >= 0)
				decimals++;
		पूर्ण
		cp++;
	पूर्ण
	अगर (*cp == '\n')
		cp++;
	अगर (*cp)
		वापस -EINVAL;
	अगर (decimals < 0)
		decimals = 0;
	*res = result * पूर्णांक_घात(10, scale - decimals);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
safe_delay_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	पूर्णांक msec = (mddev->safemode_delay*1000)/HZ;
	वापस प्र_लिखो(page, "%d.%03d\n", msec/1000, msec%1000);
पूर्ण
अटल sमाप_प्रकार
safe_delay_store(काष्ठा mddev *mddev, स्थिर अक्षर *cbuf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ msec;

	अगर (mddev_is_clustered(mddev)) अणु
		pr_warn("md: Safemode is disabled for clustered mode\n");
		वापस -EINVAL;
	पूर्ण

	अगर (strict_म_से_अदीर्घ_scaled(cbuf, &msec, 3) < 0)
		वापस -EINVAL;
	अगर (msec == 0)
		mddev->safemode_delay = 0;
	अन्यथा अणु
		अचिन्हित दीर्घ old_delay = mddev->safemode_delay;
		अचिन्हित दीर्घ new_delay = (msec*HZ)/1000;

		अगर (new_delay == 0)
			new_delay = 1;
		mddev->safemode_delay = new_delay;
		अगर (new_delay < old_delay || old_delay == 0)
			mod_समयr(&mddev->safemode_समयr, jअगरfies+1);
	पूर्ण
	वापस len;
पूर्ण
अटल काष्ठा md_sysfs_entry md_safe_delay =
__ATTR(safe_mode_delay, S_IRUGO|S_IWUSR,safe_delay_show, safe_delay_store);

अटल sमाप_प्रकार
level_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	काष्ठा md_personality *p;
	पूर्णांक ret;
	spin_lock(&mddev->lock);
	p = mddev->pers;
	अगर (p)
		ret = प्र_लिखो(page, "%s\n", p->name);
	अन्यथा अगर (mddev->clevel[0])
		ret = प्र_लिखो(page, "%s\n", mddev->clevel);
	अन्यथा अगर (mddev->level != LEVEL_NONE)
		ret = प्र_लिखो(page, "%d\n", mddev->level);
	अन्यथा
		ret = 0;
	spin_unlock(&mddev->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
level_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अक्षर clevel[16];
	sमाप_प्रकार rv;
	माप_प्रकार slen = len;
	काष्ठा md_personality *pers, *oldpers;
	दीर्घ level;
	व्योम *priv, *oldpriv;
	काष्ठा md_rdev *rdev;

	अगर (slen == 0 || slen >= माप(clevel))
		वापस -EINVAL;

	rv = mddev_lock(mddev);
	अगर (rv)
		वापस rv;

	अगर (mddev->pers == शून्य) अणु
		म_नकलन(mddev->clevel, buf, slen);
		अगर (mddev->clevel[slen-1] == '\n')
			slen--;
		mddev->clevel[slen] = 0;
		mddev->level = LEVEL_NONE;
		rv = len;
		जाओ out_unlock;
	पूर्ण
	rv = -EROFS;
	अगर (mddev->ro)
		जाओ out_unlock;

	/* request to change the personality.  Need to ensure:
	 *  - array is not engaged in resync/recovery/reshape
	 *  - old personality can be suspended
	 *  - new personality will access other array.
	 */

	rv = -EBUSY;
	अगर (mddev->sync_thपढ़ो ||
	    test_bit(MD_RECOVERY_RUNNING, &mddev->recovery) ||
	    mddev->reshape_position != MaxSector ||
	    mddev->sysfs_active)
		जाओ out_unlock;

	rv = -EINVAL;
	अगर (!mddev->pers->quiesce) अणु
		pr_warn("md: %s: %s does not support online personality change\n",
			mdname(mddev), mddev->pers->name);
		जाओ out_unlock;
	पूर्ण

	/* Now find the new personality */
	म_नकलन(clevel, buf, slen);
	अगर (clevel[slen-1] == '\n')
		slen--;
	clevel[slen] = 0;
	अगर (kम_से_दीर्घ(clevel, 10, &level))
		level = LEVEL_NONE;

	अगर (request_module("md-%s", clevel) != 0)
		request_module("md-level-%s", clevel);
	spin_lock(&pers_lock);
	pers = find_pers(level, clevel);
	अगर (!pers || !try_module_get(pers->owner)) अणु
		spin_unlock(&pers_lock);
		pr_warn("md: personality %s not loaded\n", clevel);
		rv = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	spin_unlock(&pers_lock);

	अगर (pers == mddev->pers) अणु
		/* Nothing to करो! */
		module_put(pers->owner);
		rv = len;
		जाओ out_unlock;
	पूर्ण
	अगर (!pers->takeover) अणु
		module_put(pers->owner);
		pr_warn("md: %s: %s does not support personality takeover\n",
			mdname(mddev), clevel);
		rv = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	rdev_क्रम_each(rdev, mddev)
		rdev->new_raid_disk = rdev->raid_disk;

	/* ->takeover must set new_* and/or delta_disks
	 * अगर it succeeds, and may set them when it fails.
	 */
	priv = pers->takeover(mddev);
	अगर (IS_ERR(priv)) अणु
		mddev->new_level = mddev->level;
		mddev->new_layout = mddev->layout;
		mddev->new_chunk_sectors = mddev->chunk_sectors;
		mddev->raid_disks -= mddev->delta_disks;
		mddev->delta_disks = 0;
		mddev->reshape_backwards = 0;
		module_put(pers->owner);
		pr_warn("md: %s: %s would not accept array\n",
			mdname(mddev), clevel);
		rv = PTR_ERR(priv);
		जाओ out_unlock;
	पूर्ण

	/* Looks like we have a winner */
	mddev_suspend(mddev);
	mddev_detach(mddev);

	spin_lock(&mddev->lock);
	oldpers = mddev->pers;
	oldpriv = mddev->निजी;
	mddev->pers = pers;
	mddev->निजी = priv;
	strlcpy(mddev->clevel, pers->name, माप(mddev->clevel));
	mddev->level = mddev->new_level;
	mddev->layout = mddev->new_layout;
	mddev->chunk_sectors = mddev->new_chunk_sectors;
	mddev->delta_disks = 0;
	mddev->reshape_backwards = 0;
	mddev->degraded = 0;
	spin_unlock(&mddev->lock);

	अगर (oldpers->sync_request == शून्य &&
	    mddev->बाह्यal) अणु
		/* We are converting from a no-redundancy array
		 * to a redundancy array and metadata is managed
		 * बाह्यally so we need to be sure that ग_लिखोs
		 * won't block due to a need to transition
		 *      clean->dirty
		 * until बाह्यal management is started.
		 */
		mddev->in_sync = 0;
		mddev->safemode_delay = 0;
		mddev->safemode = 0;
	पूर्ण

	oldpers->मुक्त(mddev, oldpriv);

	अगर (oldpers->sync_request == शून्य &&
	    pers->sync_request != शून्य) अणु
		/* need to add the md_redundancy_group */
		अगर (sysfs_create_group(&mddev->kobj, &md_redundancy_group))
			pr_warn("md: cannot register extra attributes for %s\n",
				mdname(mddev));
		mddev->sysfs_action = sysfs_get_dirent(mddev->kobj.sd, "sync_action");
		mddev->sysfs_completed = sysfs_get_dirent_safe(mddev->kobj.sd, "sync_completed");
		mddev->sysfs_degraded = sysfs_get_dirent_safe(mddev->kobj.sd, "degraded");
	पूर्ण
	अगर (oldpers->sync_request != शून्य &&
	    pers->sync_request == शून्य) अणु
		/* need to हटाओ the md_redundancy_group */
		अगर (mddev->to_हटाओ == शून्य)
			mddev->to_हटाओ = &md_redundancy_group;
	पूर्ण

	module_put(oldpers->owner);

	rdev_क्रम_each(rdev, mddev) अणु
		अगर (rdev->raid_disk < 0)
			जारी;
		अगर (rdev->new_raid_disk >= mddev->raid_disks)
			rdev->new_raid_disk = -1;
		अगर (rdev->new_raid_disk == rdev->raid_disk)
			जारी;
		sysfs_unlink_rdev(mddev, rdev);
	पूर्ण
	rdev_क्रम_each(rdev, mddev) अणु
		अगर (rdev->raid_disk < 0)
			जारी;
		अगर (rdev->new_raid_disk == rdev->raid_disk)
			जारी;
		rdev->raid_disk = rdev->new_raid_disk;
		अगर (rdev->raid_disk < 0)
			clear_bit(In_sync, &rdev->flags);
		अन्यथा अणु
			अगर (sysfs_link_rdev(mddev, rdev))
				pr_warn("md: cannot register rd%d for %s after level change\n",
					rdev->raid_disk, mdname(mddev));
		पूर्ण
	पूर्ण

	अगर (pers->sync_request == शून्य) अणु
		/* this is now an array without redundancy, so
		 * it must always be in_sync
		 */
		mddev->in_sync = 1;
		del_समयr_sync(&mddev->safemode_समयr);
	पूर्ण
	blk_set_stacking_limits(&mddev->queue->limits);
	pers->run(mddev);
	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
	mddev_resume(mddev);
	अगर (!mddev->thपढ़ो)
		md_update_sb(mddev, 1);
	sysfs_notअगरy_dirent_safe(mddev->sysfs_level);
	md_new_event(mddev);
	rv = len;
out_unlock:
	mddev_unlock(mddev);
	वापस rv;
पूर्ण

अटल काष्ठा md_sysfs_entry md_level =
__ATTR(level, S_IRUGO|S_IWUSR, level_show, level_store);

अटल sमाप_प्रकार
layout_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	/* just a number, not meaningful क्रम all levels */
	अगर (mddev->reshape_position != MaxSector &&
	    mddev->layout != mddev->new_layout)
		वापस प्र_लिखो(page, "%d (%d)\n",
			       mddev->new_layout, mddev->layout);
	वापस प्र_लिखो(page, "%d\n", mddev->layout);
पूर्ण

अटल sमाप_प्रकार
layout_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक n;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &n);
	अगर (err < 0)
		वापस err;
	err = mddev_lock(mddev);
	अगर (err)
		वापस err;

	अगर (mddev->pers) अणु
		अगर (mddev->pers->check_reshape == शून्य)
			err = -EBUSY;
		अन्यथा अगर (mddev->ro)
			err = -EROFS;
		अन्यथा अणु
			mddev->new_layout = n;
			err = mddev->pers->check_reshape(mddev);
			अगर (err)
				mddev->new_layout = mddev->layout;
		पूर्ण
	पूर्ण अन्यथा अणु
		mddev->new_layout = n;
		अगर (mddev->reshape_position == MaxSector)
			mddev->layout = n;
	पूर्ण
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण
अटल काष्ठा md_sysfs_entry md_layout =
__ATTR(layout, S_IRUGO|S_IWUSR, layout_show, layout_store);

अटल sमाप_प्रकार
raid_disks_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	अगर (mddev->raid_disks == 0)
		वापस 0;
	अगर (mddev->reshape_position != MaxSector &&
	    mddev->delta_disks != 0)
		वापस प्र_लिखो(page, "%d (%d)\n", mddev->raid_disks,
			       mddev->raid_disks - mddev->delta_disks);
	वापस प्र_लिखो(page, "%d\n", mddev->raid_disks);
पूर्ण

अटल पूर्णांक update_raid_disks(काष्ठा mddev *mddev, पूर्णांक raid_disks);

अटल sमाप_प्रकार
raid_disks_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक n;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &n);
	अगर (err < 0)
		वापस err;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	अगर (mddev->pers)
		err = update_raid_disks(mddev, n);
	अन्यथा अगर (mddev->reshape_position != MaxSector) अणु
		काष्ठा md_rdev *rdev;
		पूर्णांक olddisks = mddev->raid_disks - mddev->delta_disks;

		err = -EINVAL;
		rdev_क्रम_each(rdev, mddev) अणु
			अगर (olddisks < n &&
			    rdev->data_offset < rdev->new_data_offset)
				जाओ out_unlock;
			अगर (olddisks > n &&
			    rdev->data_offset > rdev->new_data_offset)
				जाओ out_unlock;
		पूर्ण
		err = 0;
		mddev->delta_disks = n - olddisks;
		mddev->raid_disks = n;
		mddev->reshape_backwards = (mddev->delta_disks < 0);
	पूर्ण अन्यथा
		mddev->raid_disks = n;
out_unlock:
	mddev_unlock(mddev);
	वापस err ? err : len;
पूर्ण
अटल काष्ठा md_sysfs_entry md_raid_disks =
__ATTR(raid_disks, S_IRUGO|S_IWUSR, raid_disks_show, raid_disks_store);

अटल sमाप_प्रकार
uuid_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%pU\n", mddev->uuid);
पूर्ण
अटल काष्ठा md_sysfs_entry md_uuid =
__ATTR(uuid, S_IRUGO, uuid_show, शून्य);

अटल sमाप_प्रकार
chunk_size_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	अगर (mddev->reshape_position != MaxSector &&
	    mddev->chunk_sectors != mddev->new_chunk_sectors)
		वापस प्र_लिखो(page, "%d (%d)\n",
			       mddev->new_chunk_sectors << 9,
			       mddev->chunk_sectors << 9);
	वापस प्र_लिखो(page, "%d\n", mddev->chunk_sectors << 9);
पूर्ण

अटल sमाप_प्रकार
chunk_size_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ n;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &n);
	अगर (err < 0)
		वापस err;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	अगर (mddev->pers) अणु
		अगर (mddev->pers->check_reshape == शून्य)
			err = -EBUSY;
		अन्यथा अगर (mddev->ro)
			err = -EROFS;
		अन्यथा अणु
			mddev->new_chunk_sectors = n >> 9;
			err = mddev->pers->check_reshape(mddev);
			अगर (err)
				mddev->new_chunk_sectors = mddev->chunk_sectors;
		पूर्ण
	पूर्ण अन्यथा अणु
		mddev->new_chunk_sectors = n >> 9;
		अगर (mddev->reshape_position == MaxSector)
			mddev->chunk_sectors = n >> 9;
	पूर्ण
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण
अटल काष्ठा md_sysfs_entry md_chunk_size =
__ATTR(chunk_size, S_IRUGO|S_IWUSR, chunk_size_show, chunk_size_store);

अटल sमाप_प्रकार
resync_start_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	अगर (mddev->recovery_cp == MaxSector)
		वापस प्र_लिखो(page, "none\n");
	वापस प्र_लिखो(page, "%llu\n", (अचिन्हित दीर्घ दीर्घ)mddev->recovery_cp);
पूर्ण

अटल sमाप_प्रकार
resync_start_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ दीर्घ n;
	पूर्णांक err;

	अगर (cmd_match(buf, "none"))
		n = MaxSector;
	अन्यथा अणु
		err = kम_से_अदीर्घl(buf, 10, &n);
		अगर (err < 0)
			वापस err;
		अगर (n != (sector_t)n)
			वापस -EINVAL;
	पूर्ण

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	अगर (mddev->pers && !test_bit(MD_RECOVERY_FROZEN, &mddev->recovery))
		err = -EBUSY;

	अगर (!err) अणु
		mddev->recovery_cp = n;
		अगर (mddev->pers)
			set_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags);
	पूर्ण
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण
अटल काष्ठा md_sysfs_entry md_resync_start =
__ATTR_PREALLOC(resync_start, S_IRUGO|S_IWUSR,
		resync_start_show, resync_start_store);

/*
 * The array state can be:
 *
 * clear
 *     No devices, no size, no level
 *     Equivalent to STOP_ARRAY ioctl
 * inactive
 *     May have some settings, but array is not active
 *        all IO results in error
 *     When written, करोesn't tear करोwn array, but just stops it
 * suspended (not supported yet)
 *     All IO requests will block. The array can be reconfigured.
 *     Writing this, अगर accepted, will block until array is quiescent
 * पढ़ोonly
 *     no resync can happen.  no superblocks get written.
 *     ग_लिखो requests fail
 * पढ़ो-स्वतः
 *     like पढ़ोonly, but behaves like 'clean' on a ग_लिखो request.
 *
 * clean - no pending ग_लिखोs, but otherwise active.
 *     When written to inactive array, starts without resync
 *     If a ग_लिखो request arrives then
 *       अगर metadata is known, mark 'dirty' and switch to 'active'.
 *       अगर not known, block and चयन to ग_लिखो-pending
 *     If written to an active array that has pending ग_लिखोs, then fails.
 * active
 *     fully active: IO and resync can be happening.
 *     When written to inactive array, starts with resync
 *
 * ग_लिखो-pending
 *     clean, but ग_लिखोs are blocked रुकोing क्रम 'active' to be written.
 *
 * active-idle
 *     like active, but no ग_लिखोs have been seen क्रम a जबतक (100msec).
 *
 * broken
 *     RAID0/LINEAR-only: same as clean, but array is missing a member.
 *     It's useful because RAID0/LINEAR mounted-arrays aren't stopped
 *     when a member is gone, so this state will at least alert the
 *     user that something is wrong.
 */
क्रमागत array_state अणु clear, inactive, suspended, पढ़ोonly, पढ़ो_स्वतः, clean, active,
		   ग_लिखो_pending, active_idle, broken, bad_wordपूर्ण;
अटल अक्षर *array_states[] = अणु
	"clear", "inactive", "suspended", "readonly", "read-auto", "clean", "active",
	"write-pending", "active-idle", "broken", शून्य पूर्ण;

अटल पूर्णांक match_word(स्थिर अक्षर *word, अक्षर **list)
अणु
	पूर्णांक n;
	क्रम (n=0; list[n]; n++)
		अगर (cmd_match(word, list[n]))
			अवरोध;
	वापस n;
पूर्ण

अटल sमाप_प्रकार
array_state_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	क्रमागत array_state st = inactive;

	अगर (mddev->pers && !test_bit(MD_NOT_READY, &mddev->flags)) अणु
		चयन(mddev->ro) अणु
		हाल 1:
			st = पढ़ोonly;
			अवरोध;
		हाल 2:
			st = पढ़ो_स्वतः;
			अवरोध;
		हाल 0:
			spin_lock(&mddev->lock);
			अगर (test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags))
				st = ग_लिखो_pending;
			अन्यथा अगर (mddev->in_sync)
				st = clean;
			अन्यथा अगर (mddev->safemode)
				st = active_idle;
			अन्यथा
				st = active;
			spin_unlock(&mddev->lock);
		पूर्ण

		अगर (test_bit(MD_BROKEN, &mddev->flags) && st == clean)
			st = broken;
	पूर्ण अन्यथा अणु
		अगर (list_empty(&mddev->disks) &&
		    mddev->raid_disks == 0 &&
		    mddev->dev_sectors == 0)
			st = clear;
		अन्यथा
			st = inactive;
	पूर्ण
	वापस प्र_लिखो(page, "%s\n", array_states[st]);
पूर्ण

अटल पूर्णांक करो_md_stop(काष्ठा mddev *mddev, पूर्णांक ro, काष्ठा block_device *bdev);
अटल पूर्णांक md_set_पढ़ोonly(काष्ठा mddev *mddev, काष्ठा block_device *bdev);
अटल पूर्णांक restart_array(काष्ठा mddev *mddev);

अटल sमाप_प्रकार
array_state_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक err = 0;
	क्रमागत array_state st = match_word(buf, array_states);

	अगर (mddev->pers && (st == active || st == clean) && mddev->ro != 1) अणु
		/* करोn't take reconfig_mutex when toggling between
		 * clean and active
		 */
		spin_lock(&mddev->lock);
		अगर (st == active) अणु
			restart_array(mddev);
			clear_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags);
			md_wakeup_thपढ़ो(mddev->thपढ़ो);
			wake_up(&mddev->sb_रुको);
		पूर्ण अन्यथा /* st == clean */ अणु
			restart_array(mddev);
			अगर (!set_in_sync(mddev))
				err = -EBUSY;
		पूर्ण
		अगर (!err)
			sysfs_notअगरy_dirent_safe(mddev->sysfs_state);
		spin_unlock(&mddev->lock);
		वापस err ?: len;
	पूर्ण
	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	err = -EINVAL;
	चयन(st) अणु
	हाल bad_word:
		अवरोध;
	हाल clear:
		/* stopping an active array */
		err = करो_md_stop(mddev, 0, शून्य);
		अवरोध;
	हाल inactive:
		/* stopping an active array */
		अगर (mddev->pers)
			err = करो_md_stop(mddev, 2, शून्य);
		अन्यथा
			err = 0; /* alपढ़ोy inactive */
		अवरोध;
	हाल suspended:
		अवरोध; /* not supported yet */
	हाल पढ़ोonly:
		अगर (mddev->pers)
			err = md_set_पढ़ोonly(mddev, शून्य);
		अन्यथा अणु
			mddev->ro = 1;
			set_disk_ro(mddev->gendisk, 1);
			err = करो_md_run(mddev);
		पूर्ण
		अवरोध;
	हाल पढ़ो_स्वतः:
		अगर (mddev->pers) अणु
			अगर (mddev->ro == 0)
				err = md_set_पढ़ोonly(mddev, शून्य);
			अन्यथा अगर (mddev->ro == 1)
				err = restart_array(mddev);
			अगर (err == 0) अणु
				mddev->ro = 2;
				set_disk_ro(mddev->gendisk, 0);
			पूर्ण
		पूर्ण अन्यथा अणु
			mddev->ro = 2;
			err = करो_md_run(mddev);
		पूर्ण
		अवरोध;
	हाल clean:
		अगर (mddev->pers) अणु
			err = restart_array(mddev);
			अगर (err)
				अवरोध;
			spin_lock(&mddev->lock);
			अगर (!set_in_sync(mddev))
				err = -EBUSY;
			spin_unlock(&mddev->lock);
		पूर्ण अन्यथा
			err = -EINVAL;
		अवरोध;
	हाल active:
		अगर (mddev->pers) अणु
			err = restart_array(mddev);
			अगर (err)
				अवरोध;
			clear_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags);
			wake_up(&mddev->sb_रुको);
			err = 0;
		पूर्ण अन्यथा अणु
			mddev->ro = 0;
			set_disk_ro(mddev->gendisk, 0);
			err = करो_md_run(mddev);
		पूर्ण
		अवरोध;
	हाल ग_लिखो_pending:
	हाल active_idle:
	हाल broken:
		/* these cannot be set */
		अवरोध;
	पूर्ण

	अगर (!err) अणु
		अगर (mddev->hold_active == UNTIL_IOCTL)
			mddev->hold_active = 0;
		sysfs_notअगरy_dirent_safe(mddev->sysfs_state);
	पूर्ण
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण
अटल काष्ठा md_sysfs_entry md_array_state =
__ATTR_PREALLOC(array_state, S_IRUGO|S_IWUSR, array_state_show, array_state_store);

अटल sमाप_प्रकार
max_corrected_पढ़ो_errors_show(काष्ठा mddev *mddev, अक्षर *page) अणु
	वापस प्र_लिखो(page, "%d\n",
		       atomic_पढ़ो(&mddev->max_corr_पढ़ो_errors));
पूर्ण

अटल sमाप_प्रकार
max_corrected_पढ़ो_errors_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक n;
	पूर्णांक rv;

	rv = kstrtouपूर्णांक(buf, 10, &n);
	अगर (rv < 0)
		वापस rv;
	atomic_set(&mddev->max_corr_पढ़ो_errors, n);
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry max_corr_पढ़ो_errors =
__ATTR(max_पढ़ो_errors, S_IRUGO|S_IWUSR, max_corrected_पढ़ो_errors_show,
	max_corrected_पढ़ो_errors_store);

अटल sमाप_प्रकार
null_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस -EINVAL;
पूर्ण

/* need to ensure rdev_delayed_delete() has completed */
अटल व्योम flush_rdev_wq(काष्ठा mddev *mddev)
अणु
	काष्ठा md_rdev *rdev;

	rcu_पढ़ो_lock();
	rdev_क्रम_each_rcu(rdev, mddev)
		अगर (work_pending(&rdev->del_work)) अणु
			flush_workqueue(md_rdev_misc_wq);
			अवरोध;
		पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल sमाप_प्रकार
new_dev_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	/* buf must be %d:%d\न? giving major and minor numbers */
	/* The new device is added to the array.
	 * If the array has a persistent superblock, we पढ़ो the
	 * superblock to initialise info and check validity.
	 * Otherwise, only checking करोne is that in bind_rdev_to_array,
	 * which मुख्यly checks size.
	 */
	अक्षर *e;
	पूर्णांक major = simple_म_से_अदीर्घ(buf, &e, 10);
	पूर्णांक minor;
	dev_t dev;
	काष्ठा md_rdev *rdev;
	पूर्णांक err;

	अगर (!*buf || *e != ':' || !e[1] || e[1] == '\n')
		वापस -EINVAL;
	minor = simple_म_से_अदीर्घ(e+1, &e, 10);
	अगर (*e && *e != '\n')
		वापस -EINVAL;
	dev = MKDEV(major, minor);
	अगर (major != MAJOR(dev) ||
	    minor != MINOR(dev))
		वापस -EOVERFLOW;

	flush_rdev_wq(mddev);
	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	अगर (mddev->persistent) अणु
		rdev = md_import_device(dev, mddev->major_version,
					mddev->minor_version);
		अगर (!IS_ERR(rdev) && !list_empty(&mddev->disks)) अणु
			काष्ठा md_rdev *rdev0
				= list_entry(mddev->disks.next,
					     काष्ठा md_rdev, same_set);
			err = super_types[mddev->major_version]
				.load_super(rdev, rdev0, mddev->minor_version);
			अगर (err < 0)
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (mddev->बाह्यal)
		rdev = md_import_device(dev, -2, -1);
	अन्यथा
		rdev = md_import_device(dev, -1, -1);

	अगर (IS_ERR(rdev)) अणु
		mddev_unlock(mddev);
		वापस PTR_ERR(rdev);
	पूर्ण
	err = bind_rdev_to_array(rdev, mddev);
 out:
	अगर (err)
		export_rdev(rdev);
	mddev_unlock(mddev);
	अगर (!err)
		md_new_event(mddev);
	वापस err ? err : len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_new_device =
__ATTR(new_dev, S_IWUSR, null_show, new_dev_store);

अटल sमाप_प्रकार
biपंचांगap_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अक्षर *end;
	अचिन्हित दीर्घ chunk, end_chunk;
	पूर्णांक err;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	अगर (!mddev->biपंचांगap)
		जाओ out;
	/* buf should be <chunk> <chunk> ... or <chunk>-<chunk> ... (range) */
	जबतक (*buf) अणु
		chunk = end_chunk = simple_म_से_अदीर्घ(buf, &end, 0);
		अगर (buf == end) अवरोध;
		अगर (*end == '-') अणु /* range */
			buf = end + 1;
			end_chunk = simple_म_से_अदीर्घ(buf, &end, 0);
			अगर (buf == end) अवरोध;
		पूर्ण
		अगर (*end && !है_खाली(*end)) अवरोध;
		md_biपंचांगap_dirty_bits(mddev->biपंचांगap, chunk, end_chunk);
		buf = skip_spaces(end);
	पूर्ण
	md_biपंचांगap_unplug(mddev->biपंचांगap); /* flush the bits to disk */
out:
	mddev_unlock(mddev);
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_biपंचांगap =
__ATTR(biपंचांगap_set_bits, S_IWUSR, null_show, biपंचांगap_store);

अटल sमाप_प्रकार
size_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n",
		(अचिन्हित दीर्घ दीर्घ)mddev->dev_sectors / 2);
पूर्ण

अटल पूर्णांक update_size(काष्ठा mddev *mddev, sector_t num_sectors);

अटल sमाप_प्रकार
size_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	/* If array is inactive, we can reduce the component size, but
	 * not increase it (except from 0).
	 * If array is active, we can try an on-line resize
	 */
	sector_t sectors;
	पूर्णांक err = strict_blocks_to_sectors(buf, &sectors);

	अगर (err < 0)
		वापस err;
	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	अगर (mddev->pers) अणु
		err = update_size(mddev, sectors);
		अगर (err == 0)
			md_update_sb(mddev, 1);
	पूर्ण अन्यथा अणु
		अगर (mddev->dev_sectors == 0 ||
		    mddev->dev_sectors > sectors)
			mddev->dev_sectors = sectors;
		अन्यथा
			err = -ENOSPC;
	पूर्ण
	mddev_unlock(mddev);
	वापस err ? err : len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_size =
__ATTR(component_size, S_IRUGO|S_IWUSR, size_show, size_store);

/* Metadata version.
 * This is one of
 *   'none' क्रम arrays with no metadata (good luck...)
 *   'external' क्रम arrays with बाह्यally managed metadata,
 * or N.M क्रम पूर्णांकernally known क्रमmats
 */
अटल sमाप_प्रकार
metadata_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	अगर (mddev->persistent)
		वापस प्र_लिखो(page, "%d.%d\n",
			       mddev->major_version, mddev->minor_version);
	अन्यथा अगर (mddev->बाह्यal)
		वापस प्र_लिखो(page, "external:%s\n", mddev->metadata_type);
	अन्यथा
		वापस प्र_लिखो(page, "none\n");
पूर्ण

अटल sमाप_प्रकार
metadata_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक major, minor;
	अक्षर *e;
	पूर्णांक err;
	/* Changing the details of 'external' metadata is
	 * always permitted.  Otherwise there must be
	 * no devices attached to the array.
	 */

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	err = -EBUSY;
	अगर (mddev->बाह्यal && म_भेदन(buf, "external:", 9) == 0)
		;
	अन्यथा अगर (!list_empty(&mddev->disks))
		जाओ out_unlock;

	err = 0;
	अगर (cmd_match(buf, "none")) अणु
		mddev->persistent = 0;
		mddev->बाह्यal = 0;
		mddev->major_version = 0;
		mddev->minor_version = 90;
		जाओ out_unlock;
	पूर्ण
	अगर (म_भेदन(buf, "external:", 9) == 0) अणु
		माप_प्रकार namelen = len-9;
		अगर (namelen >= माप(mddev->metadata_type))
			namelen = माप(mddev->metadata_type)-1;
		म_नकलन(mddev->metadata_type, buf+9, namelen);
		mddev->metadata_type[namelen] = 0;
		अगर (namelen && mddev->metadata_type[namelen-1] == '\n')
			mddev->metadata_type[--namelen] = 0;
		mddev->persistent = 0;
		mddev->बाह्यal = 1;
		mddev->major_version = 0;
		mddev->minor_version = 90;
		जाओ out_unlock;
	पूर्ण
	major = simple_म_से_अदीर्घ(buf, &e, 10);
	err = -EINVAL;
	अगर (e==buf || *e != '.')
		जाओ out_unlock;
	buf = e+1;
	minor = simple_म_से_अदीर्घ(buf, &e, 10);
	अगर (e==buf || (*e && *e != '\n') )
		जाओ out_unlock;
	err = -ENOENT;
	अगर (major >= ARRAY_SIZE(super_types) || super_types[major].name == शून्य)
		जाओ out_unlock;
	mddev->major_version = major;
	mddev->minor_version = minor;
	mddev->persistent = 1;
	mddev->बाह्यal = 0;
	err = 0;
out_unlock:
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_metadata =
__ATTR_PREALLOC(metadata_version, S_IRUGO|S_IWUSR, metadata_show, metadata_store);

अटल sमाप_प्रकार
action_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	अक्षर *type = "idle";
	अचिन्हित दीर्घ recovery = mddev->recovery;
	अगर (test_bit(MD_RECOVERY_FROZEN, &recovery))
		type = "frozen";
	अन्यथा अगर (test_bit(MD_RECOVERY_RUNNING, &recovery) ||
	    (!mddev->ro && test_bit(MD_RECOVERY_NEEDED, &recovery))) अणु
		अगर (test_bit(MD_RECOVERY_RESHAPE, &recovery))
			type = "reshape";
		अन्यथा अगर (test_bit(MD_RECOVERY_SYNC, &recovery)) अणु
			अगर (!test_bit(MD_RECOVERY_REQUESTED, &recovery))
				type = "resync";
			अन्यथा अगर (test_bit(MD_RECOVERY_CHECK, &recovery))
				type = "check";
			अन्यथा
				type = "repair";
		पूर्ण अन्यथा अगर (test_bit(MD_RECOVERY_RECOVER, &recovery))
			type = "recover";
		अन्यथा अगर (mddev->reshape_position != MaxSector)
			type = "reshape";
	पूर्ण
	वापस प्र_लिखो(page, "%s\n", type);
पूर्ण

अटल sमाप_प्रकार
action_store(काष्ठा mddev *mddev, स्थिर अक्षर *page, माप_प्रकार len)
अणु
	अगर (!mddev->pers || !mddev->pers->sync_request)
		वापस -EINVAL;


	अगर (cmd_match(page, "idle") || cmd_match(page, "frozen")) अणु
		अगर (cmd_match(page, "frozen"))
			set_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		अन्यथा
			clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		अगर (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery) &&
		    mddev_lock(mddev) == 0) अणु
			अगर (work_pending(&mddev->del_work))
				flush_workqueue(md_misc_wq);
			अगर (mddev->sync_thपढ़ो) अणु
				set_bit(MD_RECOVERY_INTR, &mddev->recovery);
				md_reap_sync_thपढ़ो(mddev);
			पूर्ण
			mddev_unlock(mddev);
		पूर्ण
	पूर्ण अन्यथा अगर (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		वापस -EBUSY;
	अन्यथा अगर (cmd_match(page, "resync"))
		clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
	अन्यथा अगर (cmd_match(page, "recover")) अणु
		clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		set_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
	पूर्ण अन्यथा अगर (cmd_match(page, "reshape")) अणु
		पूर्णांक err;
		अगर (mddev->pers->start_reshape == शून्य)
			वापस -EINVAL;
		err = mddev_lock(mddev);
		अगर (!err) अणु
			अगर (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
				err =  -EBUSY;
			अन्यथा अणु
				clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
				err = mddev->pers->start_reshape(mddev);
			पूर्ण
			mddev_unlock(mddev);
		पूर्ण
		अगर (err)
			वापस err;
		sysfs_notअगरy_dirent_safe(mddev->sysfs_degraded);
	पूर्ण अन्यथा अणु
		अगर (cmd_match(page, "check"))
			set_bit(MD_RECOVERY_CHECK, &mddev->recovery);
		अन्यथा अगर (!cmd_match(page, "repair"))
			वापस -EINVAL;
		clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		set_bit(MD_RECOVERY_REQUESTED, &mddev->recovery);
		set_bit(MD_RECOVERY_SYNC, &mddev->recovery);
	पूर्ण
	अगर (mddev->ro == 2) अणु
		/* A ग_लिखो to sync_action is enough to justअगरy
		 * canceling पढ़ो-स्वतः mode
		 */
		mddev->ro = 0;
		md_wakeup_thपढ़ो(mddev->sync_thपढ़ो);
	पूर्ण
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	md_wakeup_thपढ़ो(mddev->thपढ़ो);
	sysfs_notअगरy_dirent_safe(mddev->sysfs_action);
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_scan_mode =
__ATTR_PREALLOC(sync_action, S_IRUGO|S_IWUSR, action_show, action_store);

अटल sमाप_प्रकार
last_sync_action_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", mddev->last_sync_action);
पूर्ण

अटल काष्ठा md_sysfs_entry md_last_scan_mode = __ATTR_RO(last_sync_action);

अटल sमाप_प्रकार
mismatch_cnt_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n",
		       (अचिन्हित दीर्घ दीर्घ)
		       atomic64_पढ़ो(&mddev->resync_mismatches));
पूर्ण

अटल काष्ठा md_sysfs_entry md_mismatches = __ATTR_RO(mismatch_cnt);

अटल sमाप_प्रकार
sync_min_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d (%s)\n", speed_min(mddev),
		       mddev->sync_speed_min ? "local": "system");
पूर्ण

अटल sमाप_प्रकार
sync_min_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक min;
	पूर्णांक rv;

	अगर (म_भेदन(buf, "system", 6)==0) अणु
		min = 0;
	पूर्ण अन्यथा अणु
		rv = kstrtouपूर्णांक(buf, 10, &min);
		अगर (rv < 0)
			वापस rv;
		अगर (min == 0)
			वापस -EINVAL;
	पूर्ण
	mddev->sync_speed_min = min;
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_sync_min =
__ATTR(sync_speed_min, S_IRUGO|S_IWUSR, sync_min_show, sync_min_store);

अटल sमाप_प्रकार
sync_max_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d (%s)\n", speed_max(mddev),
		       mddev->sync_speed_max ? "local": "system");
पूर्ण

अटल sमाप_प्रकार
sync_max_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक max;
	पूर्णांक rv;

	अगर (म_भेदन(buf, "system", 6)==0) अणु
		max = 0;
	पूर्ण अन्यथा अणु
		rv = kstrtouपूर्णांक(buf, 10, &max);
		अगर (rv < 0)
			वापस rv;
		अगर (max == 0)
			वापस -EINVAL;
	पूर्ण
	mddev->sync_speed_max = max;
	वापस len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_sync_max =
__ATTR(sync_speed_max, S_IRUGO|S_IWUSR, sync_max_show, sync_max_store);

अटल sमाप_प्रकार
degraded_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", mddev->degraded);
पूर्ण
अटल काष्ठा md_sysfs_entry md_degraded = __ATTR_RO(degraded);

अटल sमाप_प्रकार
sync_क्रमce_parallel_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", mddev->parallel_resync);
पूर्ण

अटल sमाप_प्रकार
sync_क्रमce_parallel_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	दीर्घ n;

	अगर (kम_से_दीर्घ(buf, 10, &n))
		वापस -EINVAL;

	अगर (n != 0 && n != 1)
		वापस -EINVAL;

	mddev->parallel_resync = n;

	अगर (mddev->sync_thपढ़ो)
		wake_up(&resync_रुको);

	वापस len;
पूर्ण

/* क्रमce parallel resync, even with shared block devices */
अटल काष्ठा md_sysfs_entry md_sync_क्रमce_parallel =
__ATTR(sync_क्रमce_parallel, S_IRUGO|S_IWUSR,
       sync_क्रमce_parallel_show, sync_क्रमce_parallel_store);

अटल sमाप_प्रकार
sync_speed_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	अचिन्हित दीर्घ resync, dt, db;
	अगर (mddev->curr_resync == 0)
		वापस प्र_लिखो(page, "none\n");
	resync = mddev->curr_mark_cnt - atomic_पढ़ो(&mddev->recovery_active);
	dt = (jअगरfies - mddev->resync_mark) / HZ;
	अगर (!dt) dt++;
	db = resync - mddev->resync_mark_cnt;
	वापस प्र_लिखो(page, "%lu\n", db/dt/2); /* K/sec */
पूर्ण

अटल काष्ठा md_sysfs_entry md_sync_speed = __ATTR_RO(sync_speed);

अटल sमाप_प्रकार
sync_completed_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	अचिन्हित दीर्घ दीर्घ max_sectors, resync;

	अगर (!test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		वापस प्र_लिखो(page, "none\n");

	अगर (mddev->curr_resync == 1 ||
	    mddev->curr_resync == 2)
		वापस प्र_लिखो(page, "delayed\n");

	अगर (test_bit(MD_RECOVERY_SYNC, &mddev->recovery) ||
	    test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery))
		max_sectors = mddev->resync_max_sectors;
	अन्यथा
		max_sectors = mddev->dev_sectors;

	resync = mddev->curr_resync_completed;
	वापस प्र_लिखो(page, "%llu / %llu\n", resync, max_sectors);
पूर्ण

अटल काष्ठा md_sysfs_entry md_sync_completed =
	__ATTR_PREALLOC(sync_completed, S_IRUGO, sync_completed_show, शून्य);

अटल sमाप_प्रकार
min_sync_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n",
		       (अचिन्हित दीर्घ दीर्घ)mddev->resync_min);
पूर्ण
अटल sमाप_प्रकार
min_sync_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ दीर्घ min;
	पूर्णांक err;

	अगर (kम_से_अदीर्घl(buf, 10, &min))
		वापस -EINVAL;

	spin_lock(&mddev->lock);
	err = -EINVAL;
	अगर (min > mddev->resync_max)
		जाओ out_unlock;

	err = -EBUSY;
	अगर (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		जाओ out_unlock;

	/* Round करोwn to multiple of 4K क्रम safety */
	mddev->resync_min = round_करोwn(min, 8);
	err = 0;

out_unlock:
	spin_unlock(&mddev->lock);
	वापस err ?: len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_min_sync =
__ATTR(sync_min, S_IRUGO|S_IWUSR, min_sync_show, min_sync_store);

अटल sमाप_प्रकार
max_sync_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	अगर (mddev->resync_max == MaxSector)
		वापस प्र_लिखो(page, "max\n");
	अन्यथा
		वापस प्र_लिखो(page, "%llu\n",
			       (अचिन्हित दीर्घ दीर्घ)mddev->resync_max);
पूर्ण
अटल sमाप_प्रकार
max_sync_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक err;
	spin_lock(&mddev->lock);
	अगर (म_भेदन(buf, "max", 3) == 0)
		mddev->resync_max = MaxSector;
	अन्यथा अणु
		अचिन्हित दीर्घ दीर्घ max;
		पूर्णांक chunk;

		err = -EINVAL;
		अगर (kम_से_अदीर्घl(buf, 10, &max))
			जाओ out_unlock;
		अगर (max < mddev->resync_min)
			जाओ out_unlock;

		err = -EBUSY;
		अगर (max < mddev->resync_max &&
		    mddev->ro == 0 &&
		    test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
			जाओ out_unlock;

		/* Must be a multiple of chunk_size */
		chunk = mddev->chunk_sectors;
		अगर (chunk) अणु
			sector_t temp = max;

			err = -EINVAL;
			अगर (sector_भाग(temp, chunk))
				जाओ out_unlock;
		पूर्ण
		mddev->resync_max = max;
	पूर्ण
	wake_up(&mddev->recovery_रुको);
	err = 0;
out_unlock:
	spin_unlock(&mddev->lock);
	वापस err ?: len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_max_sync =
__ATTR(sync_max, S_IRUGO|S_IWUSR, max_sync_show, max_sync_store);

अटल sमाप_प्रकार
suspend_lo_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n", (अचिन्हित दीर्घ दीर्घ)mddev->suspend_lo);
पूर्ण

अटल sमाप_प्रकार
suspend_lo_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ दीर्घ new;
	पूर्णांक err;

	err = kम_से_अदीर्घl(buf, 10, &new);
	अगर (err < 0)
		वापस err;
	अगर (new != (sector_t)new)
		वापस -EINVAL;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	err = -EINVAL;
	अगर (mddev->pers == शून्य ||
	    mddev->pers->quiesce == शून्य)
		जाओ unlock;
	mddev_suspend(mddev);
	mddev->suspend_lo = new;
	mddev_resume(mddev);

	err = 0;
unlock:
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण
अटल काष्ठा md_sysfs_entry md_suspend_lo =
__ATTR(suspend_lo, S_IRUGO|S_IWUSR, suspend_lo_show, suspend_lo_store);

अटल sमाप_प्रकार
suspend_hi_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n", (अचिन्हित दीर्घ दीर्घ)mddev->suspend_hi);
पूर्ण

अटल sमाप_प्रकार
suspend_hi_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ दीर्घ new;
	पूर्णांक err;

	err = kम_से_अदीर्घl(buf, 10, &new);
	अगर (err < 0)
		वापस err;
	अगर (new != (sector_t)new)
		वापस -EINVAL;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	err = -EINVAL;
	अगर (mddev->pers == शून्य)
		जाओ unlock;

	mddev_suspend(mddev);
	mddev->suspend_hi = new;
	mddev_resume(mddev);

	err = 0;
unlock:
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण
अटल काष्ठा md_sysfs_entry md_suspend_hi =
__ATTR(suspend_hi, S_IRUGO|S_IWUSR, suspend_hi_show, suspend_hi_store);

अटल sमाप_प्रकार
reshape_position_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	अगर (mddev->reshape_position != MaxSector)
		वापस प्र_लिखो(page, "%llu\n",
			       (अचिन्हित दीर्घ दीर्घ)mddev->reshape_position);
	म_नकल(page, "none\n");
	वापस 5;
पूर्ण

अटल sमाप_प्रकार
reshape_position_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा md_rdev *rdev;
	अचिन्हित दीर्घ दीर्घ new;
	पूर्णांक err;

	err = kम_से_अदीर्घl(buf, 10, &new);
	अगर (err < 0)
		वापस err;
	अगर (new != (sector_t)new)
		वापस -EINVAL;
	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	err = -EBUSY;
	अगर (mddev->pers)
		जाओ unlock;
	mddev->reshape_position = new;
	mddev->delta_disks = 0;
	mddev->reshape_backwards = 0;
	mddev->new_level = mddev->level;
	mddev->new_layout = mddev->layout;
	mddev->new_chunk_sectors = mddev->chunk_sectors;
	rdev_क्रम_each(rdev, mddev)
		rdev->new_data_offset = rdev->data_offset;
	err = 0;
unlock:
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_reshape_position =
__ATTR(reshape_position, S_IRUGO|S_IWUSR, reshape_position_show,
       reshape_position_store);

अटल sमाप_प्रकार
reshape_direction_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n",
		       mddev->reshape_backwards ? "backwards" : "forwards");
पूर्ण

अटल sमाप_प्रकार
reshape_direction_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक backwards = 0;
	पूर्णांक err;

	अगर (cmd_match(buf, "forwards"))
		backwards = 0;
	अन्यथा अगर (cmd_match(buf, "backwards"))
		backwards = 1;
	अन्यथा
		वापस -EINVAL;
	अगर (mddev->reshape_backwards == backwards)
		वापस len;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	/* check अगर we are allowed to change */
	अगर (mddev->delta_disks)
		err = -EBUSY;
	अन्यथा अगर (mddev->persistent &&
	    mddev->major_version == 0)
		err =  -EINVAL;
	अन्यथा
		mddev->reshape_backwards = backwards;
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_reshape_direction =
__ATTR(reshape_direction, S_IRUGO|S_IWUSR, reshape_direction_show,
       reshape_direction_store);

अटल sमाप_प्रकार
array_size_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	अगर (mddev->बाह्यal_size)
		वापस प्र_लिखो(page, "%llu\n",
			       (अचिन्हित दीर्घ दीर्घ)mddev->array_sectors/2);
	अन्यथा
		वापस प्र_लिखो(page, "default\n");
पूर्ण

अटल sमाप_प्रकार
array_size_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	sector_t sectors;
	पूर्णांक err;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;

	/* cluster raid करोesn't support change array_sectors */
	अगर (mddev_is_clustered(mddev)) अणु
		mddev_unlock(mddev);
		वापस -EINVAL;
	पूर्ण

	अगर (म_भेदन(buf, "default", 7) == 0) अणु
		अगर (mddev->pers)
			sectors = mddev->pers->size(mddev, 0, 0);
		अन्यथा
			sectors = mddev->array_sectors;

		mddev->बाह्यal_size = 0;
	पूर्ण अन्यथा अणु
		अगर (strict_blocks_to_sectors(buf, &sectors) < 0)
			err = -EINVAL;
		अन्यथा अगर (mddev->pers && mddev->pers->size(mddev, 0, 0) < sectors)
			err = -E2BIG;
		अन्यथा
			mddev->बाह्यal_size = 1;
	पूर्ण

	अगर (!err) अणु
		mddev->array_sectors = sectors;
		अगर (mddev->pers)
			set_capacity_and_notअगरy(mddev->gendisk,
						mddev->array_sectors);
	पूर्ण
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_array_size =
__ATTR(array_size, S_IRUGO|S_IWUSR, array_size_show,
       array_size_store);

अटल sमाप_प्रकार
consistency_policy_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	पूर्णांक ret;

	अगर (test_bit(MD_HAS_JOURNAL, &mddev->flags)) अणु
		ret = प्र_लिखो(page, "journal\n");
	पूर्ण अन्यथा अगर (test_bit(MD_HAS_PPL, &mddev->flags)) अणु
		ret = प्र_लिखो(page, "ppl\n");
	पूर्ण अन्यथा अगर (mddev->biपंचांगap) अणु
		ret = प्र_लिखो(page, "bitmap\n");
	पूर्ण अन्यथा अगर (mddev->pers) अणु
		अगर (mddev->pers->sync_request)
			ret = प्र_लिखो(page, "resync\n");
		अन्यथा
			ret = प्र_लिखो(page, "none\n");
	पूर्ण अन्यथा अणु
		ret = प्र_लिखो(page, "unknown\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
consistency_policy_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक err = 0;

	अगर (mddev->pers) अणु
		अगर (mddev->pers->change_consistency_policy)
			err = mddev->pers->change_consistency_policy(mddev, buf);
		अन्यथा
			err = -EBUSY;
	पूर्ण अन्यथा अगर (mddev->बाह्यal && म_भेदन(buf, "ppl", 3) == 0) अणु
		set_bit(MD_HAS_PPL, &mddev->flags);
	पूर्ण अन्यथा अणु
		err = -EINVAL;
	पूर्ण

	वापस err ? err : len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_consistency_policy =
__ATTR(consistency_policy, S_IRUGO | S_IWUSR, consistency_policy_show,
       consistency_policy_store);

अटल sमाप_प्रकार fail_last_dev_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", mddev->fail_last_dev);
पूर्ण

/*
 * Setting fail_last_dev to true to allow last device to be क्रमcibly हटाओd
 * from RAID1/RAID10.
 */
अटल sमाप_प्रकार
fail_last_dev_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;
	bool value;

	ret = kstrtobool(buf, &value);
	अगर (ret)
		वापस ret;

	अगर (value != mddev->fail_last_dev)
		mddev->fail_last_dev = value;

	वापस len;
पूर्ण
अटल काष्ठा md_sysfs_entry md_fail_last_dev =
__ATTR(fail_last_dev, S_IRUGO | S_IWUSR, fail_last_dev_show,
       fail_last_dev_store);

अटल sमाप_प्रकार serialize_policy_show(काष्ठा mddev *mddev, अक्षर *page)
अणु
	अगर (mddev->pers == शून्य || (mddev->pers->level != 1))
		वापस प्र_लिखो(page, "n/a\n");
	अन्यथा
		वापस प्र_लिखो(page, "%d\n", mddev->serialize_policy);
पूर्ण

/*
 * Setting serialize_policy to true to enक्रमce ग_लिखो IO is not reordered
 * क्रम raid1.
 */
अटल sमाप_प्रकार
serialize_policy_store(काष्ठा mddev *mddev, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक err;
	bool value;

	err = kstrtobool(buf, &value);
	अगर (err)
		वापस err;

	अगर (value == mddev->serialize_policy)
		वापस len;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;
	अगर (mddev->pers == शून्य || (mddev->pers->level != 1)) अणु
		pr_err("md: serialize_policy is only effective for raid1\n");
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	mddev_suspend(mddev);
	अगर (value)
		mddev_create_serial_pool(mddev, शून्य, true);
	अन्यथा
		mddev_destroy_serial_pool(mddev, शून्य, true);
	mddev->serialize_policy = value;
	mddev_resume(mddev);
unlock:
	mddev_unlock(mddev);
	वापस err ?: len;
पूर्ण

अटल काष्ठा md_sysfs_entry md_serialize_policy =
__ATTR(serialize_policy, S_IRUGO | S_IWUSR, serialize_policy_show,
       serialize_policy_store);


अटल काष्ठा attribute *md_शेष_attrs[] = अणु
	&md_level.attr,
	&md_layout.attr,
	&md_raid_disks.attr,
	&md_uuid.attr,
	&md_chunk_size.attr,
	&md_size.attr,
	&md_resync_start.attr,
	&md_metadata.attr,
	&md_new_device.attr,
	&md_safe_delay.attr,
	&md_array_state.attr,
	&md_reshape_position.attr,
	&md_reshape_direction.attr,
	&md_array_size.attr,
	&max_corr_पढ़ो_errors.attr,
	&md_consistency_policy.attr,
	&md_fail_last_dev.attr,
	&md_serialize_policy.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *md_redundancy_attrs[] = अणु
	&md_scan_mode.attr,
	&md_last_scan_mode.attr,
	&md_mismatches.attr,
	&md_sync_min.attr,
	&md_sync_max.attr,
	&md_sync_speed.attr,
	&md_sync_क्रमce_parallel.attr,
	&md_sync_completed.attr,
	&md_min_sync.attr,
	&md_max_sync.attr,
	&md_suspend_lo.attr,
	&md_suspend_hi.attr,
	&md_biपंचांगap.attr,
	&md_degraded.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group md_redundancy_group = अणु
	.name = शून्य,
	.attrs = md_redundancy_attrs,
पूर्ण;

अटल sमाप_प्रकार
md_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr, अक्षर *page)
अणु
	काष्ठा md_sysfs_entry *entry = container_of(attr, काष्ठा md_sysfs_entry, attr);
	काष्ठा mddev *mddev = container_of(kobj, काष्ठा mddev, kobj);
	sमाप_प्रकार rv;

	अगर (!entry->show)
		वापस -EIO;
	spin_lock(&all_mddevs_lock);
	अगर (list_empty(&mddev->all_mddevs)) अणु
		spin_unlock(&all_mddevs_lock);
		वापस -EBUSY;
	पूर्ण
	mddev_get(mddev);
	spin_unlock(&all_mddevs_lock);

	rv = entry->show(mddev, page);
	mddev_put(mddev);
	वापस rv;
पूर्ण

अटल sमाप_प्रकार
md_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
	      स्थिर अक्षर *page, माप_प्रकार length)
अणु
	काष्ठा md_sysfs_entry *entry = container_of(attr, काष्ठा md_sysfs_entry, attr);
	काष्ठा mddev *mddev = container_of(kobj, काष्ठा mddev, kobj);
	sमाप_प्रकार rv;

	अगर (!entry->store)
		वापस -EIO;
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;
	spin_lock(&all_mddevs_lock);
	अगर (list_empty(&mddev->all_mddevs)) अणु
		spin_unlock(&all_mddevs_lock);
		वापस -EBUSY;
	पूर्ण
	mddev_get(mddev);
	spin_unlock(&all_mddevs_lock);
	rv = entry->store(mddev, page, length);
	mddev_put(mddev);
	वापस rv;
पूर्ण

अटल व्योम md_मुक्त(काष्ठा kobject *ko)
अणु
	काष्ठा mddev *mddev = container_of(ko, काष्ठा mddev, kobj);

	अगर (mddev->sysfs_state)
		sysfs_put(mddev->sysfs_state);
	अगर (mddev->sysfs_level)
		sysfs_put(mddev->sysfs_level);

	अगर (mddev->gendisk)
		del_gendisk(mddev->gendisk);
	अगर (mddev->queue)
		blk_cleanup_queue(mddev->queue);
	अगर (mddev->gendisk)
		put_disk(mddev->gendisk);
	percpu_ref_निकास(&mddev->ग_लिखोs_pending);

	bioset_निकास(&mddev->bio_set);
	bioset_निकास(&mddev->sync_set);
	mempool_निकास(&mddev->md_io_pool);
	kमुक्त(mddev);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops md_sysfs_ops = अणु
	.show	= md_attr_show,
	.store	= md_attr_store,
पूर्ण;
अटल काष्ठा kobj_type md_ktype = अणु
	.release	= md_मुक्त,
	.sysfs_ops	= &md_sysfs_ops,
	.शेष_attrs	= md_शेष_attrs,
पूर्ण;

पूर्णांक mdp_major = 0;

अटल व्योम mddev_delayed_delete(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा mddev *mddev = container_of(ws, काष्ठा mddev, del_work);

	sysfs_हटाओ_group(&mddev->kobj, &md_biपंचांगap_group);
	kobject_del(&mddev->kobj);
	kobject_put(&mddev->kobj);
पूर्ण

अटल व्योम no_op(काष्ठा percpu_ref *r) अणुपूर्ण

पूर्णांक mddev_init_ग_लिखोs_pending(काष्ठा mddev *mddev)
अणु
	अगर (mddev->ग_लिखोs_pending.percpu_count_ptr)
		वापस 0;
	अगर (percpu_ref_init(&mddev->ग_लिखोs_pending, no_op,
			    PERCPU_REF_ALLOW_REINIT, GFP_KERNEL) < 0)
		वापस -ENOMEM;
	/* We want to start with the refcount at zero */
	percpu_ref_put(&mddev->ग_लिखोs_pending);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mddev_init_ग_लिखोs_pending);

अटल पूर्णांक md_alloc(dev_t dev, अक्षर *name)
अणु
	/*
	 * If dev is zero, name is the name of a device to allocate with
	 * an arbitrary minor number.  It will be "md_???"
	 * If dev is non-zero it must be a device number with a MAJOR of
	 * MD_MAJOR or mdp_major.  In this हाल, अगर "name" is शून्य, then
	 * the device is being created by खोलोing a node in /dev.
	 * If "name" is not शून्य, the device is being created by
	 * writing to /sys/module/md_mod/parameters/new_array.
	 */
	अटल DEFINE_MUTEX(disks_mutex);
	काष्ठा mddev *mddev;
	काष्ठा gendisk *disk;
	पूर्णांक partitioned;
	पूर्णांक shअगरt;
	पूर्णांक unit;
	पूर्णांक error ;

	/*
	 * Wait क्रम any previous instance of this device to be completely
	 * हटाओd (mddev_delayed_delete).
	 */
	flush_workqueue(md_misc_wq);

	mutex_lock(&disks_mutex);
	mddev = mddev_alloc(dev);
	अगर (IS_ERR(mddev)) अणु
		mutex_unlock(&disks_mutex);
		वापस PTR_ERR(mddev);
	पूर्ण

	partitioned = (MAJOR(mddev->unit) != MD_MAJOR);
	shअगरt = partitioned ? MdpMinorShअगरt : 0;
	unit = MINOR(mddev->unit) >> shअगरt;

	अगर (name && !dev) अणु
		/* Need to ensure that 'name' is not a duplicate.
		 */
		काष्ठा mddev *mddev2;
		spin_lock(&all_mddevs_lock);

		list_क्रम_each_entry(mddev2, &all_mddevs, all_mddevs)
			अगर (mddev2->gendisk &&
			    म_भेद(mddev2->gendisk->disk_name, name) == 0) अणु
				spin_unlock(&all_mddevs_lock);
				error = -EEXIST;
				जाओ पात;
			पूर्ण
		spin_unlock(&all_mddevs_lock);
	पूर्ण
	अगर (name && dev)
		/*
		 * Creating /dev/mdNNN via "newarray", so adjust hold_active.
		 */
		mddev->hold_active = UNTIL_STOP;

	error = mempool_init_kदो_स्मृति_pool(&mddev->md_io_pool, BIO_POOL_SIZE,
					  माप(काष्ठा md_io));
	अगर (error)
		जाओ पात;

	error = -ENOMEM;
	mddev->queue = blk_alloc_queue(NUMA_NO_NODE);
	अगर (!mddev->queue)
		जाओ पात;

	blk_set_stacking_limits(&mddev->queue->limits);

	disk = alloc_disk(1 << shअगरt);
	अगर (!disk) अणु
		blk_cleanup_queue(mddev->queue);
		mddev->queue = शून्य;
		जाओ पात;
	पूर्ण
	disk->major = MAJOR(mddev->unit);
	disk->first_minor = unit << shअगरt;
	अगर (name)
		म_नकल(disk->disk_name, name);
	अन्यथा अगर (partitioned)
		प्र_लिखो(disk->disk_name, "md_d%d", unit);
	अन्यथा
		प्र_लिखो(disk->disk_name, "md%d", unit);
	disk->fops = &md_fops;
	disk->निजी_data = mddev;
	disk->queue = mddev->queue;
	blk_queue_ग_लिखो_cache(mddev->queue, true, true);
	/* Allow extended partitions.  This makes the
	 * 'mdp' device redundant, but we can't really
	 * हटाओ it now.
	 */
	disk->flags |= GENHD_FL_EXT_DEVT;
	disk->events |= DISK_EVENT_MEDIA_CHANGE;
	mddev->gendisk = disk;
	/* As soon as we call add_disk(), another thपढ़ो could get
	 * through to md_खोलो, so make sure it करोesn't get too far
	 */
	mutex_lock(&mddev->खोलो_mutex);
	add_disk(disk);

	error = kobject_add(&mddev->kobj, &disk_to_dev(disk)->kobj, "%s", "md");
	अगर (error) अणु
		/* This isn't possible, but as kobject_init_and_add is marked
		 * __must_check, we must करो something with the result
		 */
		pr_debug("md: cannot register %s/md - name in use\n",
			 disk->disk_name);
		error = 0;
	पूर्ण
	अगर (mddev->kobj.sd &&
	    sysfs_create_group(&mddev->kobj, &md_biपंचांगap_group))
		pr_debug("pointless warning\n");
	mutex_unlock(&mddev->खोलो_mutex);
 पात:
	mutex_unlock(&disks_mutex);
	अगर (!error && mddev->kobj.sd) अणु
		kobject_uevent(&mddev->kobj, KOBJ_ADD);
		mddev->sysfs_state = sysfs_get_dirent_safe(mddev->kobj.sd, "array_state");
		mddev->sysfs_level = sysfs_get_dirent_safe(mddev->kobj.sd, "level");
	पूर्ण
	mddev_put(mddev);
	वापस error;
पूर्ण

अटल व्योम md_probe(dev_t dev)
अणु
	अगर (MAJOR(dev) == MD_MAJOR && MINOR(dev) >= 512)
		वापस;
	अगर (create_on_खोलो)
		md_alloc(dev, शून्य);
पूर्ण

अटल पूर्णांक add_named_array(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	/*
	 * val must be "md_*" or "mdNNN".
	 * For "md_*" we allocate an array with a large मुक्त minor number, and
	 * set the name to val.  val must not alपढ़ोy be an active name.
	 * For "mdNNN" we allocate an array with the minor number NNN
	 * which must not alपढ़ोy be in use.
	 */
	पूर्णांक len = म_माप(val);
	अक्षर buf[DISK_NAME_LEN];
	अचिन्हित दीर्घ devnum;

	जबतक (len && val[len-1] == '\n')
		len--;
	अगर (len >= DISK_NAME_LEN)
		वापस -E2BIG;
	strlcpy(buf, val, len+1);
	अगर (म_भेदन(buf, "md_", 3) == 0)
		वापस md_alloc(0, buf);
	अगर (म_भेदन(buf, "md", 2) == 0 &&
	    है_अंक(buf[2]) &&
	    kम_से_अदीर्घ(buf+2, 10, &devnum) == 0 &&
	    devnum <= MINORMASK)
		वापस md_alloc(MKDEV(MD_MAJOR, devnum), शून्य);

	वापस -EINVAL;
पूर्ण

अटल व्योम md_safemode_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा mddev *mddev = from_समयr(mddev, t, safemode_समयr);

	mddev->safemode = 1;
	अगर (mddev->बाह्यal)
		sysfs_notअगरy_dirent_safe(mddev->sysfs_state);

	md_wakeup_thपढ़ो(mddev->thपढ़ो);
पूर्ण

अटल पूर्णांक start_dirty_degraded;

पूर्णांक md_run(काष्ठा mddev *mddev)
अणु
	पूर्णांक err;
	काष्ठा md_rdev *rdev;
	काष्ठा md_personality *pers;

	अगर (list_empty(&mddev->disks))
		/* cannot run an array with no devices.. */
		वापस -EINVAL;

	अगर (mddev->pers)
		वापस -EBUSY;
	/* Cannot run until previous stop completes properly */
	अगर (mddev->sysfs_active)
		वापस -EBUSY;

	/*
	 * Analyze all RAID superblock(s)
	 */
	अगर (!mddev->raid_disks) अणु
		अगर (!mddev->persistent)
			वापस -EINVAL;
		err = analyze_sbs(mddev);
		अगर (err)
			वापस -EINVAL;
	पूर्ण

	अगर (mddev->level != LEVEL_NONE)
		request_module("md-level-%d", mddev->level);
	अन्यथा अगर (mddev->clevel[0])
		request_module("md-%s", mddev->clevel);

	/*
	 * Drop all container device buffers, from now on
	 * the only valid बाह्यal पूर्णांकerface is through the md
	 * device.
	 */
	mddev->has_superblocks = false;
	rdev_क्रम_each(rdev, mddev) अणु
		अगर (test_bit(Faulty, &rdev->flags))
			जारी;
		sync_blockdev(rdev->bdev);
		invalidate_bdev(rdev->bdev);
		अगर (mddev->ro != 1 && rdev_पढ़ो_only(rdev)) अणु
			mddev->ro = 1;
			अगर (mddev->gendisk)
				set_disk_ro(mddev->gendisk, 1);
		पूर्ण

		अगर (rdev->sb_page)
			mddev->has_superblocks = true;

		/* perक्रमm some consistency tests on the device.
		 * We करोn't want the data to overlap the metadata,
		 * Internal Biपंचांगap issues have been handled अन्यथाwhere.
		 */
		अगर (rdev->meta_bdev) अणु
			/* Nothing to check */;
		पूर्ण अन्यथा अगर (rdev->data_offset < rdev->sb_start) अणु
			अगर (mddev->dev_sectors &&
			    rdev->data_offset + mddev->dev_sectors
			    > rdev->sb_start) अणु
				pr_warn("md: %s: data overlaps metadata\n",
					mdname(mddev));
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (rdev->sb_start + rdev->sb_size/512
			    > rdev->data_offset) अणु
				pr_warn("md: %s: metadata overlaps data\n",
					mdname(mddev));
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		sysfs_notअगरy_dirent_safe(rdev->sysfs_state);
	पूर्ण

	अगर (!bioset_initialized(&mddev->bio_set)) अणु
		err = bioset_init(&mddev->bio_set, BIO_POOL_SIZE, 0, BIOSET_NEED_BVECS);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!bioset_initialized(&mddev->sync_set)) अणु
		err = bioset_init(&mddev->sync_set, BIO_POOL_SIZE, 0, BIOSET_NEED_BVECS);
		अगर (err)
			वापस err;
	पूर्ण

	spin_lock(&pers_lock);
	pers = find_pers(mddev->level, mddev->clevel);
	अगर (!pers || !try_module_get(pers->owner)) अणु
		spin_unlock(&pers_lock);
		अगर (mddev->level != LEVEL_NONE)
			pr_warn("md: personality for level %d is not loaded!\n",
				mddev->level);
		अन्यथा
			pr_warn("md: personality for level %s is not loaded!\n",
				mddev->clevel);
		err = -EINVAL;
		जाओ पात;
	पूर्ण
	spin_unlock(&pers_lock);
	अगर (mddev->level != pers->level) अणु
		mddev->level = pers->level;
		mddev->new_level = pers->level;
	पूर्ण
	strlcpy(mddev->clevel, pers->name, माप(mddev->clevel));

	अगर (mddev->reshape_position != MaxSector &&
	    pers->start_reshape == शून्य) अणु
		/* This personality cannot handle reshaping... */
		module_put(pers->owner);
		err = -EINVAL;
		जाओ पात;
	पूर्ण

	अगर (pers->sync_request) अणु
		/* Warn अगर this is a potentially silly
		 * configuration.
		 */
		अक्षर b[BDEVNAME_SIZE], b2[BDEVNAME_SIZE];
		काष्ठा md_rdev *rdev2;
		पूर्णांक warned = 0;

		rdev_क्रम_each(rdev, mddev)
			rdev_क्रम_each(rdev2, mddev) अणु
				अगर (rdev < rdev2 &&
				    rdev->bdev->bd_disk ==
				    rdev2->bdev->bd_disk) अणु
					pr_warn("%s: WARNING: %s appears to be on the same physical disk as %s.\n",
						mdname(mddev),
						bdevname(rdev->bdev,b),
						bdevname(rdev2->bdev,b2));
					warned = 1;
				पूर्ण
			पूर्ण

		अगर (warned)
			pr_warn("True protection against single-disk failure might be compromised.\n");
	पूर्ण

	mddev->recovery = 0;
	/* may be over-ridden by personality */
	mddev->resync_max_sectors = mddev->dev_sectors;

	mddev->ok_start_degraded = start_dirty_degraded;

	अगर (start_पढ़ोonly && mddev->ro == 0)
		mddev->ro = 2; /* पढ़ो-only, but चयन on first ग_लिखो */

	err = pers->run(mddev);
	अगर (err)
		pr_warn("md: pers->run() failed ...\n");
	अन्यथा अगर (pers->size(mddev, 0, 0) < mddev->array_sectors) अणु
		WARN_ONCE(!mddev->बाह्यal_size,
			  "%s: default size too small, but 'external_size' not in effect?\n",
			  __func__);
		pr_warn("md: invalid array_size %llu > default size %llu\n",
			(अचिन्हित दीर्घ दीर्घ)mddev->array_sectors / 2,
			(अचिन्हित दीर्घ दीर्घ)pers->size(mddev, 0, 0) / 2);
		err = -EINVAL;
	पूर्ण
	अगर (err == 0 && pers->sync_request &&
	    (mddev->biपंचांगap_info.file || mddev->biपंचांगap_info.offset)) अणु
		काष्ठा biपंचांगap *biपंचांगap;

		biपंचांगap = md_biपंचांगap_create(mddev, -1);
		अगर (IS_ERR(biपंचांगap)) अणु
			err = PTR_ERR(biपंचांगap);
			pr_warn("%s: failed to create bitmap (%d)\n",
				mdname(mddev), err);
		पूर्ण अन्यथा
			mddev->biपंचांगap = biपंचांगap;

	पूर्ण
	अगर (err)
		जाओ biपंचांगap_पात;

	अगर (mddev->biपंचांगap_info.max_ग_लिखो_behind > 0) अणु
		bool create_pool = false;

		rdev_क्रम_each(rdev, mddev) अणु
			अगर (test_bit(WriteMostly, &rdev->flags) &&
			    rdev_init_serial(rdev))
				create_pool = true;
		पूर्ण
		अगर (create_pool && mddev->serial_info_pool == शून्य) अणु
			mddev->serial_info_pool =
				mempool_create_kदो_स्मृति_pool(NR_SERIAL_INFOS,
						    माप(काष्ठा serial_info));
			अगर (!mddev->serial_info_pool) अणु
				err = -ENOMEM;
				जाओ biपंचांगap_पात;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (mddev->queue) अणु
		bool nonrot = true;

		rdev_क्रम_each(rdev, mddev) अणु
			अगर (rdev->raid_disk >= 0 &&
			    !blk_queue_nonrot(bdev_get_queue(rdev->bdev))) अणु
				nonrot = false;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (mddev->degraded)
			nonrot = false;
		अगर (nonrot)
			blk_queue_flag_set(QUEUE_FLAG_NONROT, mddev->queue);
		अन्यथा
			blk_queue_flag_clear(QUEUE_FLAG_NONROT, mddev->queue);
	पूर्ण
	अगर (pers->sync_request) अणु
		अगर (mddev->kobj.sd &&
		    sysfs_create_group(&mddev->kobj, &md_redundancy_group))
			pr_warn("md: cannot register extra attributes for %s\n",
				mdname(mddev));
		mddev->sysfs_action = sysfs_get_dirent_safe(mddev->kobj.sd, "sync_action");
		mddev->sysfs_completed = sysfs_get_dirent_safe(mddev->kobj.sd, "sync_completed");
		mddev->sysfs_degraded = sysfs_get_dirent_safe(mddev->kobj.sd, "degraded");
	पूर्ण अन्यथा अगर (mddev->ro == 2) /* स्वतः-पढ़ोonly not meaningful */
		mddev->ro = 0;

	atomic_set(&mddev->max_corr_पढ़ो_errors,
		   MD_DEFAULT_MAX_CORRECTED_READ_ERRORS);
	mddev->safemode = 0;
	अगर (mddev_is_clustered(mddev))
		mddev->safemode_delay = 0;
	अन्यथा
		mddev->safemode_delay = DEFAULT_SAFEMODE_DELAY;
	mddev->in_sync = 1;
	smp_wmb();
	spin_lock(&mddev->lock);
	mddev->pers = pers;
	spin_unlock(&mddev->lock);
	rdev_क्रम_each(rdev, mddev)
		अगर (rdev->raid_disk >= 0)
			sysfs_link_rdev(mddev, rdev); /* failure here is OK */

	अगर (mddev->degraded && !mddev->ro)
		/* This ensures that recovering status is reported immediately
		 * via sysfs - until a lack of spares is confirmed.
		 */
		set_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);

	अगर (mddev->sb_flags)
		md_update_sb(mddev, 0);

	md_new_event(mddev);
	वापस 0;

biपंचांगap_पात:
	mddev_detach(mddev);
	अगर (mddev->निजी)
		pers->मुक्त(mddev, mddev->निजी);
	mddev->निजी = शून्य;
	module_put(pers->owner);
	md_biपंचांगap_destroy(mddev);
पात:
	bioset_निकास(&mddev->bio_set);
	bioset_निकास(&mddev->sync_set);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(md_run);

पूर्णांक करो_md_run(काष्ठा mddev *mddev)
अणु
	पूर्णांक err;

	set_bit(MD_NOT_READY, &mddev->flags);
	err = md_run(mddev);
	अगर (err)
		जाओ out;
	err = md_biपंचांगap_load(mddev);
	अगर (err) अणु
		md_biपंचांगap_destroy(mddev);
		जाओ out;
	पूर्ण

	अगर (mddev_is_clustered(mddev))
		md_allow_ग_लिखो(mddev);

	/* run start up tasks that require md_thपढ़ो */
	md_start(mddev);

	md_wakeup_thपढ़ो(mddev->thपढ़ो);
	md_wakeup_thपढ़ो(mddev->sync_thपढ़ो); /* possibly kick off a reshape */

	set_capacity_and_notअगरy(mddev->gendisk, mddev->array_sectors);
	clear_bit(MD_NOT_READY, &mddev->flags);
	mddev->changed = 1;
	kobject_uevent(&disk_to_dev(mddev->gendisk)->kobj, KOBJ_CHANGE);
	sysfs_notअगरy_dirent_safe(mddev->sysfs_state);
	sysfs_notअगरy_dirent_safe(mddev->sysfs_action);
	sysfs_notअगरy_dirent_safe(mddev->sysfs_degraded);
out:
	clear_bit(MD_NOT_READY, &mddev->flags);
	वापस err;
पूर्ण

पूर्णांक md_start(काष्ठा mddev *mddev)
अणु
	पूर्णांक ret = 0;

	अगर (mddev->pers->start) अणु
		set_bit(MD_RECOVERY_WAIT, &mddev->recovery);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		ret = mddev->pers->start(mddev);
		clear_bit(MD_RECOVERY_WAIT, &mddev->recovery);
		md_wakeup_thपढ़ो(mddev->sync_thपढ़ो);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(md_start);

अटल पूर्णांक restart_array(काष्ठा mddev *mddev)
अणु
	काष्ठा gendisk *disk = mddev->gendisk;
	काष्ठा md_rdev *rdev;
	bool has_journal = false;
	bool has_पढ़ोonly = false;

	/* Complain अगर it has no devices */
	अगर (list_empty(&mddev->disks))
		वापस -ENXIO;
	अगर (!mddev->pers)
		वापस -EINVAL;
	अगर (!mddev->ro)
		वापस -EBUSY;

	rcu_पढ़ो_lock();
	rdev_क्रम_each_rcu(rdev, mddev) अणु
		अगर (test_bit(Journal, &rdev->flags) &&
		    !test_bit(Faulty, &rdev->flags))
			has_journal = true;
		अगर (rdev_पढ़ो_only(rdev))
			has_पढ़ोonly = true;
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (test_bit(MD_HAS_JOURNAL, &mddev->flags) && !has_journal)
		/* Don't restart rw with journal missing/faulty */
			वापस -EINVAL;
	अगर (has_पढ़ोonly)
		वापस -EROFS;

	mddev->safemode = 0;
	mddev->ro = 0;
	set_disk_ro(disk, 0);
	pr_debug("md: %s switched to read-write mode.\n", mdname(mddev));
	/* Kick recovery or resync अगर necessary */
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	md_wakeup_thपढ़ो(mddev->thपढ़ो);
	md_wakeup_thपढ़ो(mddev->sync_thपढ़ो);
	sysfs_notअगरy_dirent_safe(mddev->sysfs_state);
	वापस 0;
पूर्ण

अटल व्योम md_clean(काष्ठा mddev *mddev)
अणु
	mddev->array_sectors = 0;
	mddev->बाह्यal_size = 0;
	mddev->dev_sectors = 0;
	mddev->raid_disks = 0;
	mddev->recovery_cp = 0;
	mddev->resync_min = 0;
	mddev->resync_max = MaxSector;
	mddev->reshape_position = MaxSector;
	mddev->बाह्यal = 0;
	mddev->persistent = 0;
	mddev->level = LEVEL_NONE;
	mddev->clevel[0] = 0;
	mddev->flags = 0;
	mddev->sb_flags = 0;
	mddev->ro = 0;
	mddev->metadata_type[0] = 0;
	mddev->chunk_sectors = 0;
	mddev->स_समय = mddev->uसमय = 0;
	mddev->layout = 0;
	mddev->max_disks = 0;
	mddev->events = 0;
	mddev->can_decrease_events = 0;
	mddev->delta_disks = 0;
	mddev->reshape_backwards = 0;
	mddev->new_level = LEVEL_NONE;
	mddev->new_layout = 0;
	mddev->new_chunk_sectors = 0;
	mddev->curr_resync = 0;
	atomic64_set(&mddev->resync_mismatches, 0);
	mddev->suspend_lo = mddev->suspend_hi = 0;
	mddev->sync_speed_min = mddev->sync_speed_max = 0;
	mddev->recovery = 0;
	mddev->in_sync = 0;
	mddev->changed = 0;
	mddev->degraded = 0;
	mddev->safemode = 0;
	mddev->निजी = शून्य;
	mddev->cluster_info = शून्य;
	mddev->biपंचांगap_info.offset = 0;
	mddev->biपंचांगap_info.शेष_offset = 0;
	mddev->biपंचांगap_info.शेष_space = 0;
	mddev->biपंचांगap_info.chunksize = 0;
	mddev->biपंचांगap_info.daemon_sleep = 0;
	mddev->biपंचांगap_info.max_ग_लिखो_behind = 0;
	mddev->biपंचांगap_info.nodes = 0;
पूर्ण

अटल व्योम __md_stop_ग_लिखोs(काष्ठा mddev *mddev)
अणु
	set_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
	अगर (work_pending(&mddev->del_work))
		flush_workqueue(md_misc_wq);
	अगर (mddev->sync_thपढ़ो) अणु
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
		md_reap_sync_thपढ़ो(mddev);
	पूर्ण

	del_समयr_sync(&mddev->safemode_समयr);

	अगर (mddev->pers && mddev->pers->quiesce) अणु
		mddev->pers->quiesce(mddev, 1);
		mddev->pers->quiesce(mddev, 0);
	पूर्ण
	md_biपंचांगap_flush(mddev);

	अगर (mddev->ro == 0 &&
	    ((!mddev->in_sync && !mddev_is_clustered(mddev)) ||
	     mddev->sb_flags)) अणु
		/* mark array as shutकरोwn cleanly */
		अगर (!mddev_is_clustered(mddev))
			mddev->in_sync = 1;
		md_update_sb(mddev, 1);
	पूर्ण
	/* disable policy to guarantee rdevs मुक्त resources क्रम serialization */
	mddev->serialize_policy = 0;
	mddev_destroy_serial_pool(mddev, शून्य, true);
पूर्ण

व्योम md_stop_ग_लिखोs(काष्ठा mddev *mddev)
अणु
	mddev_lock_noपूर्णांकr(mddev);
	__md_stop_ग_लिखोs(mddev);
	mddev_unlock(mddev);
पूर्ण
EXPORT_SYMBOL_GPL(md_stop_ग_लिखोs);

अटल व्योम mddev_detach(काष्ठा mddev *mddev)
अणु
	md_biपंचांगap_रुको_behind_ग_लिखोs(mddev);
	अगर (mddev->pers && mddev->pers->quiesce && !mddev->suspended) अणु
		mddev->pers->quiesce(mddev, 1);
		mddev->pers->quiesce(mddev, 0);
	पूर्ण
	md_unरेजिस्टर_thपढ़ो(&mddev->thपढ़ो);
	अगर (mddev->queue)
		blk_sync_queue(mddev->queue); /* the unplug fn references 'conf'*/
पूर्ण

अटल व्योम __md_stop(काष्ठा mddev *mddev)
अणु
	काष्ठा md_personality *pers = mddev->pers;
	md_biपंचांगap_destroy(mddev);
	mddev_detach(mddev);
	/* Ensure ->event_work is करोne */
	अगर (mddev->event_work.func)
		flush_workqueue(md_misc_wq);
	spin_lock(&mddev->lock);
	mddev->pers = शून्य;
	spin_unlock(&mddev->lock);
	pers->मुक्त(mddev, mddev->निजी);
	mddev->निजी = शून्य;
	अगर (pers->sync_request && mddev->to_हटाओ == शून्य)
		mddev->to_हटाओ = &md_redundancy_group;
	module_put(pers->owner);
	clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
पूर्ण

व्योम md_stop(काष्ठा mddev *mddev)
अणु
	/* stop the array and मुक्त an attached data काष्ठाures.
	 * This is called from dm-raid
	 */
	__md_stop(mddev);
	bioset_निकास(&mddev->bio_set);
	bioset_निकास(&mddev->sync_set);
पूर्ण

EXPORT_SYMBOL_GPL(md_stop);

अटल पूर्णांक md_set_पढ़ोonly(काष्ठा mddev *mddev, काष्ठा block_device *bdev)
अणु
	पूर्णांक err = 0;
	पूर्णांक did_मुक्तze = 0;

	अगर (!test_bit(MD_RECOVERY_FROZEN, &mddev->recovery)) अणु
		did_मुक्तze = 1;
		set_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
	पूर्ण
	अगर (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
	अगर (mddev->sync_thपढ़ो)
		/* Thपढ़ो might be blocked रुकोing क्रम metadata update
		 * which will now never happen */
		wake_up_process(mddev->sync_thपढ़ो->tsk);

	अगर (mddev->बाह्यal && test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags))
		वापस -EBUSY;
	mddev_unlock(mddev);
	रुको_event(resync_रुको, !test_bit(MD_RECOVERY_RUNNING,
					  &mddev->recovery));
	रुको_event(mddev->sb_रुको,
		   !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags));
	mddev_lock_noपूर्णांकr(mddev);

	mutex_lock(&mddev->खोलो_mutex);
	अगर ((mddev->pers && atomic_पढ़ो(&mddev->खोलोers) > !!bdev) ||
	    mddev->sync_thपढ़ो ||
	    test_bit(MD_RECOVERY_RUNNING, &mddev->recovery)) अणु
		pr_warn("md: %s still in use.\n",mdname(mddev));
		अगर (did_मुक्तze) अणु
			clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
			set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
			md_wakeup_thपढ़ो(mddev->thपढ़ो);
		पूर्ण
		err = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (mddev->pers) अणु
		__md_stop_ग_लिखोs(mddev);

		err  = -ENXIO;
		अगर (mddev->ro==1)
			जाओ out;
		mddev->ro = 1;
		set_disk_ro(mddev->gendisk, 1);
		clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		sysfs_notअगरy_dirent_safe(mddev->sysfs_state);
		err = 0;
	पूर्ण
out:
	mutex_unlock(&mddev->खोलो_mutex);
	वापस err;
पूर्ण

/* mode:
 *   0 - completely stop and dis-assemble array
 *   2 - stop but करो not disassemble array
 */
अटल पूर्णांक करो_md_stop(काष्ठा mddev *mddev, पूर्णांक mode,
		      काष्ठा block_device *bdev)
अणु
	काष्ठा gendisk *disk = mddev->gendisk;
	काष्ठा md_rdev *rdev;
	पूर्णांक did_मुक्तze = 0;

	अगर (!test_bit(MD_RECOVERY_FROZEN, &mddev->recovery)) अणु
		did_मुक्तze = 1;
		set_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
	पूर्ण
	अगर (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
	अगर (mddev->sync_thपढ़ो)
		/* Thपढ़ो might be blocked रुकोing क्रम metadata update
		 * which will now never happen */
		wake_up_process(mddev->sync_thपढ़ो->tsk);

	mddev_unlock(mddev);
	रुको_event(resync_रुको, (mddev->sync_thपढ़ो == शून्य &&
				 !test_bit(MD_RECOVERY_RUNNING,
					   &mddev->recovery)));
	mddev_lock_noपूर्णांकr(mddev);

	mutex_lock(&mddev->खोलो_mutex);
	अगर ((mddev->pers && atomic_पढ़ो(&mddev->खोलोers) > !!bdev) ||
	    mddev->sysfs_active ||
	    mddev->sync_thपढ़ो ||
	    test_bit(MD_RECOVERY_RUNNING, &mddev->recovery)) अणु
		pr_warn("md: %s still in use.\n",mdname(mddev));
		mutex_unlock(&mddev->खोलो_mutex);
		अगर (did_मुक्तze) अणु
			clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
			set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
			md_wakeup_thपढ़ो(mddev->thपढ़ो);
		पूर्ण
		वापस -EBUSY;
	पूर्ण
	अगर (mddev->pers) अणु
		अगर (mddev->ro)
			set_disk_ro(disk, 0);

		__md_stop_ग_लिखोs(mddev);
		__md_stop(mddev);

		/* tell userspace to handle 'inactive' */
		sysfs_notअगरy_dirent_safe(mddev->sysfs_state);

		rdev_क्रम_each(rdev, mddev)
			अगर (rdev->raid_disk >= 0)
				sysfs_unlink_rdev(mddev, rdev);

		set_capacity_and_notअगरy(disk, 0);
		mutex_unlock(&mddev->खोलो_mutex);
		mddev->changed = 1;

		अगर (mddev->ro)
			mddev->ro = 0;
	पूर्ण अन्यथा
		mutex_unlock(&mddev->खोलो_mutex);
	/*
	 * Free resources अगर final stop
	 */
	अगर (mode == 0) अणु
		pr_info("md: %s stopped.\n", mdname(mddev));

		अगर (mddev->biपंचांगap_info.file) अणु
			काष्ठा file *f = mddev->biपंचांगap_info.file;
			spin_lock(&mddev->lock);
			mddev->biपंचांगap_info.file = शून्य;
			spin_unlock(&mddev->lock);
			fput(f);
		पूर्ण
		mddev->biपंचांगap_info.offset = 0;

		export_array(mddev);

		md_clean(mddev);
		अगर (mddev->hold_active == UNTIL_STOP)
			mddev->hold_active = 0;
	पूर्ण
	md_new_event(mddev);
	sysfs_notअगरy_dirent_safe(mddev->sysfs_state);
	वापस 0;
पूर्ण

#अगर_अघोषित MODULE
अटल व्योम स्वतःrun_array(काष्ठा mddev *mddev)
अणु
	काष्ठा md_rdev *rdev;
	पूर्णांक err;

	अगर (list_empty(&mddev->disks))
		वापस;

	pr_info("md: running: ");

	rdev_क्रम_each(rdev, mddev) अणु
		अक्षर b[BDEVNAME_SIZE];
		pr_cont("<%s>", bdevname(rdev->bdev,b));
	पूर्ण
	pr_cont("\n");

	err = करो_md_run(mddev);
	अगर (err) अणु
		pr_warn("md: do_md_run() returned %d\n", err);
		करो_md_stop(mddev, 0, शून्य);
	पूर्ण
पूर्ण

/*
 * lets try to run arrays based on all disks that have arrived
 * until now. (those are in pending_raid_disks)
 *
 * the method: pick the first pending disk, collect all disks with
 * the same UUID, हटाओ all from the pending list and put them पूर्णांकo
 * the 'same_array' list. Then order this list based on superblock
 * update समय (freshest comes first), kick out 'old' disks and
 * compare superblocks. If everything's fine then run it.
 *
 * If "unit" is allocated, then bump its reference count
 */
अटल व्योम स्वतःrun_devices(पूर्णांक part)
अणु
	काष्ठा md_rdev *rdev0, *rdev, *पंचांगp;
	काष्ठा mddev *mddev;
	अक्षर b[BDEVNAME_SIZE];

	pr_info("md: autorun ...\n");
	जबतक (!list_empty(&pending_raid_disks)) अणु
		पूर्णांक unit;
		dev_t dev;
		LIST_HEAD(candidates);
		rdev0 = list_entry(pending_raid_disks.next,
					 काष्ठा md_rdev, same_set);

		pr_debug("md: considering %s ...\n", bdevname(rdev0->bdev,b));
		INIT_LIST_HEAD(&candidates);
		rdev_क्रम_each_list(rdev, पंचांगp, &pending_raid_disks)
			अगर (super_90_load(rdev, rdev0, 0) >= 0) अणु
				pr_debug("md:  adding %s ...\n",
					 bdevname(rdev->bdev,b));
				list_move(&rdev->same_set, &candidates);
			पूर्ण
		/*
		 * now we have a set of devices, with all of them having
		 * mostly sane superblocks. It's समय to allocate the
		 * mddev.
		 */
		अगर (part) अणु
			dev = MKDEV(mdp_major,
				    rdev0->preferred_minor << MdpMinorShअगरt);
			unit = MINOR(dev) >> MdpMinorShअगरt;
		पूर्ण अन्यथा अणु
			dev = MKDEV(MD_MAJOR, rdev0->preferred_minor);
			unit = MINOR(dev);
		पूर्ण
		अगर (rdev0->preferred_minor != unit) अणु
			pr_warn("md: unit number in %s is bad: %d\n",
				bdevname(rdev0->bdev, b), rdev0->preferred_minor);
			अवरोध;
		पूर्ण

		md_probe(dev);
		mddev = mddev_find(dev);
		अगर (!mddev)
			अवरोध;

		अगर (mddev_lock(mddev))
			pr_warn("md: %s locked, cannot run\n", mdname(mddev));
		अन्यथा अगर (mddev->raid_disks || mddev->major_version
			 || !list_empty(&mddev->disks)) अणु
			pr_warn("md: %s already running, cannot run %s\n",
				mdname(mddev), bdevname(rdev0->bdev,b));
			mddev_unlock(mddev);
		पूर्ण अन्यथा अणु
			pr_debug("md: created %s\n", mdname(mddev));
			mddev->persistent = 1;
			rdev_क्रम_each_list(rdev, पंचांगp, &candidates) अणु
				list_del_init(&rdev->same_set);
				अगर (bind_rdev_to_array(rdev, mddev))
					export_rdev(rdev);
			पूर्ण
			स्वतःrun_array(mddev);
			mddev_unlock(mddev);
		पूर्ण
		/* on success, candidates will be empty, on error
		 * it won't...
		 */
		rdev_क्रम_each_list(rdev, पंचांगp, &candidates) अणु
			list_del_init(&rdev->same_set);
			export_rdev(rdev);
		पूर्ण
		mddev_put(mddev);
	पूर्ण
	pr_info("md: ... autorun DONE.\n");
पूर्ण
#पूर्ण_अगर /* !MODULE */

अटल पूर्णांक get_version(व्योम __user *arg)
अणु
	mdu_version_t ver;

	ver.major = MD_MAJOR_VERSION;
	ver.minor = MD_MINOR_VERSION;
	ver.patchlevel = MD_PATCHLEVEL_VERSION;

	अगर (copy_to_user(arg, &ver, माप(ver)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_array_info(काष्ठा mddev *mddev, व्योम __user *arg)
अणु
	mdu_array_info_t info;
	पूर्णांक nr,working,insync,failed,spare;
	काष्ठा md_rdev *rdev;

	nr = working = insync = failed = spare = 0;
	rcu_पढ़ो_lock();
	rdev_क्रम_each_rcu(rdev, mddev) अणु
		nr++;
		अगर (test_bit(Faulty, &rdev->flags))
			failed++;
		अन्यथा अणु
			working++;
			अगर (test_bit(In_sync, &rdev->flags))
				insync++;
			अन्यथा अगर (test_bit(Journal, &rdev->flags))
				/* TODO: add journal count to md_u.h */
				;
			अन्यथा
				spare++;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	info.major_version = mddev->major_version;
	info.minor_version = mddev->minor_version;
	info.patch_version = MD_PATCHLEVEL_VERSION;
	info.स_समय         = clamp_t(समय64_t, mddev->स_समय, 0, U32_MAX);
	info.level         = mddev->level;
	info.size          = mddev->dev_sectors / 2;
	अगर (info.size != mddev->dev_sectors / 2) /* overflow */
		info.size = -1;
	info.nr_disks      = nr;
	info.raid_disks    = mddev->raid_disks;
	info.md_minor      = mddev->md_minor;
	info.not_persistent= !mddev->persistent;

	info.uसमय         = clamp_t(समय64_t, mddev->uसमय, 0, U32_MAX);
	info.state         = 0;
	अगर (mddev->in_sync)
		info.state = (1<<MD_SB_CLEAN);
	अगर (mddev->biपंचांगap && mddev->biपंचांगap_info.offset)
		info.state |= (1<<MD_SB_BITMAP_PRESENT);
	अगर (mddev_is_clustered(mddev))
		info.state |= (1<<MD_SB_CLUSTERED);
	info.active_disks  = insync;
	info.working_disks = working;
	info.failed_disks  = failed;
	info.spare_disks   = spare;

	info.layout        = mddev->layout;
	info.chunk_size    = mddev->chunk_sectors << 9;

	अगर (copy_to_user(arg, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_biपंचांगap_file(काष्ठा mddev *mddev, व्योम __user * arg)
अणु
	mdu_biपंचांगap_file_t *file = शून्य; /* too big क्रम stack allocation */
	अक्षर *ptr;
	पूर्णांक err;

	file = kzalloc(माप(*file), GFP_NOIO);
	अगर (!file)
		वापस -ENOMEM;

	err = 0;
	spin_lock(&mddev->lock);
	/* biपंचांगap enabled */
	अगर (mddev->biपंचांगap_info.file) अणु
		ptr = file_path(mddev->biपंचांगap_info.file, file->pathname,
				माप(file->pathname));
		अगर (IS_ERR(ptr))
			err = PTR_ERR(ptr);
		अन्यथा
			स_हटाओ(file->pathname, ptr,
				माप(file->pathname)-(ptr-file->pathname));
	पूर्ण
	spin_unlock(&mddev->lock);

	अगर (err == 0 &&
	    copy_to_user(arg, file, माप(*file)))
		err = -EFAULT;

	kमुक्त(file);
	वापस err;
पूर्ण

अटल पूर्णांक get_disk_info(काष्ठा mddev *mddev, व्योम __user * arg)
अणु
	mdu_disk_info_t info;
	काष्ठा md_rdev *rdev;

	अगर (copy_from_user(&info, arg, माप(info)))
		वापस -EFAULT;

	rcu_पढ़ो_lock();
	rdev = md_find_rdev_nr_rcu(mddev, info.number);
	अगर (rdev) अणु
		info.major = MAJOR(rdev->bdev->bd_dev);
		info.minor = MINOR(rdev->bdev->bd_dev);
		info.raid_disk = rdev->raid_disk;
		info.state = 0;
		अगर (test_bit(Faulty, &rdev->flags))
			info.state |= (1<<MD_DISK_FAULTY);
		अन्यथा अगर (test_bit(In_sync, &rdev->flags)) अणु
			info.state |= (1<<MD_DISK_ACTIVE);
			info.state |= (1<<MD_DISK_SYNC);
		पूर्ण
		अगर (test_bit(Journal, &rdev->flags))
			info.state |= (1<<MD_DISK_JOURNAL);
		अगर (test_bit(WriteMostly, &rdev->flags))
			info.state |= (1<<MD_DISK_WRITEMOSTLY);
		अगर (test_bit(FailFast, &rdev->flags))
			info.state |= (1<<MD_DISK_FAILFAST);
	पूर्ण अन्यथा अणु
		info.major = info.minor = 0;
		info.raid_disk = -1;
		info.state = (1<<MD_DISK_REMOVED);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (copy_to_user(arg, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक md_add_new_disk(काष्ठा mddev *mddev, काष्ठा mdu_disk_info_s *info)
अणु
	अक्षर b[BDEVNAME_SIZE], b2[BDEVNAME_SIZE];
	काष्ठा md_rdev *rdev;
	dev_t dev = MKDEV(info->major,info->minor);

	अगर (mddev_is_clustered(mddev) &&
		!(info->state & ((1 << MD_DISK_CLUSTER_ADD) | (1 << MD_DISK_CANDIDATE)))) अणु
		pr_warn("%s: Cannot add to clustered mddev.\n",
			mdname(mddev));
		वापस -EINVAL;
	पूर्ण

	अगर (info->major != MAJOR(dev) || info->minor != MINOR(dev))
		वापस -EOVERFLOW;

	अगर (!mddev->raid_disks) अणु
		पूर्णांक err;
		/* expecting a device which has a superblock */
		rdev = md_import_device(dev, mddev->major_version, mddev->minor_version);
		अगर (IS_ERR(rdev)) अणु
			pr_warn("md: md_import_device returned %ld\n",
				PTR_ERR(rdev));
			वापस PTR_ERR(rdev);
		पूर्ण
		अगर (!list_empty(&mddev->disks)) अणु
			काष्ठा md_rdev *rdev0
				= list_entry(mddev->disks.next,
					     काष्ठा md_rdev, same_set);
			err = super_types[mddev->major_version]
				.load_super(rdev, rdev0, mddev->minor_version);
			अगर (err < 0) अणु
				pr_warn("md: %s has different UUID to %s\n",
					bdevname(rdev->bdev,b),
					bdevname(rdev0->bdev,b2));
				export_rdev(rdev);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		err = bind_rdev_to_array(rdev, mddev);
		अगर (err)
			export_rdev(rdev);
		वापस err;
	पूर्ण

	/*
	 * md_add_new_disk can be used once the array is assembled
	 * to add "hot spares".  They must alपढ़ोy have a superblock
	 * written
	 */
	अगर (mddev->pers) अणु
		पूर्णांक err;
		अगर (!mddev->pers->hot_add_disk) अणु
			pr_warn("%s: personality does not support diskops!\n",
				mdname(mddev));
			वापस -EINVAL;
		पूर्ण
		अगर (mddev->persistent)
			rdev = md_import_device(dev, mddev->major_version,
						mddev->minor_version);
		अन्यथा
			rdev = md_import_device(dev, -1, -1);
		अगर (IS_ERR(rdev)) अणु
			pr_warn("md: md_import_device returned %ld\n",
				PTR_ERR(rdev));
			वापस PTR_ERR(rdev);
		पूर्ण
		/* set saved_raid_disk अगर appropriate */
		अगर (!mddev->persistent) अणु
			अगर (info->state & (1<<MD_DISK_SYNC)  &&
			    info->raid_disk < mddev->raid_disks) अणु
				rdev->raid_disk = info->raid_disk;
				set_bit(In_sync, &rdev->flags);
				clear_bit(Biपंचांगap_sync, &rdev->flags);
			पूर्ण अन्यथा
				rdev->raid_disk = -1;
			rdev->saved_raid_disk = rdev->raid_disk;
		पूर्ण अन्यथा
			super_types[mddev->major_version].
				validate_super(mddev, rdev);
		अगर ((info->state & (1<<MD_DISK_SYNC)) &&
		     rdev->raid_disk != info->raid_disk) अणु
			/* This was a hot-add request, but events करोesn't
			 * match, so reject it.
			 */
			export_rdev(rdev);
			वापस -EINVAL;
		पूर्ण

		clear_bit(In_sync, &rdev->flags); /* just to be sure */
		अगर (info->state & (1<<MD_DISK_WRITEMOSTLY))
			set_bit(WriteMostly, &rdev->flags);
		अन्यथा
			clear_bit(WriteMostly, &rdev->flags);
		अगर (info->state & (1<<MD_DISK_FAILFAST))
			set_bit(FailFast, &rdev->flags);
		अन्यथा
			clear_bit(FailFast, &rdev->flags);

		अगर (info->state & (1<<MD_DISK_JOURNAL)) अणु
			काष्ठा md_rdev *rdev2;
			bool has_journal = false;

			/* make sure no existing journal disk */
			rdev_क्रम_each(rdev2, mddev) अणु
				अगर (test_bit(Journal, &rdev2->flags)) अणु
					has_journal = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (has_journal || mddev->biपंचांगap) अणु
				export_rdev(rdev);
				वापस -EBUSY;
			पूर्ण
			set_bit(Journal, &rdev->flags);
		पूर्ण
		/*
		 * check whether the device shows up in other nodes
		 */
		अगर (mddev_is_clustered(mddev)) अणु
			अगर (info->state & (1 << MD_DISK_CANDIDATE))
				set_bit(Candidate, &rdev->flags);
			अन्यथा अगर (info->state & (1 << MD_DISK_CLUSTER_ADD)) अणु
				/* --add initiated by this node */
				err = md_cluster_ops->add_new_disk(mddev, rdev);
				अगर (err) अणु
					export_rdev(rdev);
					वापस err;
				पूर्ण
			पूर्ण
		पूर्ण

		rdev->raid_disk = -1;
		err = bind_rdev_to_array(rdev, mddev);

		अगर (err)
			export_rdev(rdev);

		अगर (mddev_is_clustered(mddev)) अणु
			अगर (info->state & (1 << MD_DISK_CANDIDATE)) अणु
				अगर (!err) अणु
					err = md_cluster_ops->new_disk_ack(mddev,
						err == 0);
					अगर (err)
						md_kick_rdev_from_array(rdev);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (err)
					md_cluster_ops->add_new_disk_cancel(mddev);
				अन्यथा
					err = add_bound_rdev(rdev);
			पूर्ण

		पूर्ण अन्यथा अगर (!err)
			err = add_bound_rdev(rdev);

		वापस err;
	पूर्ण

	/* otherwise, md_add_new_disk is only allowed
	 * क्रम major_version==0 superblocks
	 */
	अगर (mddev->major_version != 0) अणु
		pr_warn("%s: ADD_NEW_DISK not supported\n", mdname(mddev));
		वापस -EINVAL;
	पूर्ण

	अगर (!(info->state & (1<<MD_DISK_FAULTY))) अणु
		पूर्णांक err;
		rdev = md_import_device(dev, -1, 0);
		अगर (IS_ERR(rdev)) अणु
			pr_warn("md: error, md_import_device() returned %ld\n",
				PTR_ERR(rdev));
			वापस PTR_ERR(rdev);
		पूर्ण
		rdev->desc_nr = info->number;
		अगर (info->raid_disk < mddev->raid_disks)
			rdev->raid_disk = info->raid_disk;
		अन्यथा
			rdev->raid_disk = -1;

		अगर (rdev->raid_disk < mddev->raid_disks)
			अगर (info->state & (1<<MD_DISK_SYNC))
				set_bit(In_sync, &rdev->flags);

		अगर (info->state & (1<<MD_DISK_WRITEMOSTLY))
			set_bit(WriteMostly, &rdev->flags);
		अगर (info->state & (1<<MD_DISK_FAILFAST))
			set_bit(FailFast, &rdev->flags);

		अगर (!mddev->persistent) अणु
			pr_debug("md: nonpersistent superblock ...\n");
			rdev->sb_start = i_size_पढ़ो(rdev->bdev->bd_inode) / 512;
		पूर्ण अन्यथा
			rdev->sb_start = calc_dev_sboffset(rdev);
		rdev->sectors = rdev->sb_start;

		err = bind_rdev_to_array(rdev, mddev);
		अगर (err) अणु
			export_rdev(rdev);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hot_हटाओ_disk(काष्ठा mddev *mddev, dev_t dev)
अणु
	अक्षर b[BDEVNAME_SIZE];
	काष्ठा md_rdev *rdev;

	अगर (!mddev->pers)
		वापस -ENODEV;

	rdev = find_rdev(mddev, dev);
	अगर (!rdev)
		वापस -ENXIO;

	अगर (rdev->raid_disk < 0)
		जाओ kick_rdev;

	clear_bit(Blocked, &rdev->flags);
	हटाओ_and_add_spares(mddev, rdev);

	अगर (rdev->raid_disk >= 0)
		जाओ busy;

kick_rdev:
	अगर (mddev_is_clustered(mddev)) अणु
		अगर (md_cluster_ops->हटाओ_disk(mddev, rdev))
			जाओ busy;
	पूर्ण

	md_kick_rdev_from_array(rdev);
	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
	अगर (mddev->thपढ़ो)
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
	अन्यथा
		md_update_sb(mddev, 1);
	md_new_event(mddev);

	वापस 0;
busy:
	pr_debug("md: cannot remove active disk %s from %s ...\n",
		 bdevname(rdev->bdev,b), mdname(mddev));
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक hot_add_disk(काष्ठा mddev *mddev, dev_t dev)
अणु
	अक्षर b[BDEVNAME_SIZE];
	पूर्णांक err;
	काष्ठा md_rdev *rdev;

	अगर (!mddev->pers)
		वापस -ENODEV;

	अगर (mddev->major_version != 0) अणु
		pr_warn("%s: HOT_ADD may only be used with version-0 superblocks.\n",
			mdname(mddev));
		वापस -EINVAL;
	पूर्ण
	अगर (!mddev->pers->hot_add_disk) अणु
		pr_warn("%s: personality does not support diskops!\n",
			mdname(mddev));
		वापस -EINVAL;
	पूर्ण

	rdev = md_import_device(dev, -1, 0);
	अगर (IS_ERR(rdev)) अणु
		pr_warn("md: error, md_import_device() returned %ld\n",
			PTR_ERR(rdev));
		वापस -EINVAL;
	पूर्ण

	अगर (mddev->persistent)
		rdev->sb_start = calc_dev_sboffset(rdev);
	अन्यथा
		rdev->sb_start = i_size_पढ़ो(rdev->bdev->bd_inode) / 512;

	rdev->sectors = rdev->sb_start;

	अगर (test_bit(Faulty, &rdev->flags)) अणु
		pr_warn("md: can not hot-add faulty %s disk to %s!\n",
			bdevname(rdev->bdev,b), mdname(mddev));
		err = -EINVAL;
		जाओ पात_export;
	पूर्ण

	clear_bit(In_sync, &rdev->flags);
	rdev->desc_nr = -1;
	rdev->saved_raid_disk = -1;
	err = bind_rdev_to_array(rdev, mddev);
	अगर (err)
		जाओ पात_export;

	/*
	 * The rest should better be atomic, we can have disk failures
	 * noticed in पूर्णांकerrupt contexts ...
	 */

	rdev->raid_disk = -1;

	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
	अगर (!mddev->thपढ़ो)
		md_update_sb(mddev, 1);
	/*
	 * Kick recovery, maybe this spare has to be added to the
	 * array immediately.
	 */
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	md_wakeup_thपढ़ो(mddev->thपढ़ो);
	md_new_event(mddev);
	वापस 0;

पात_export:
	export_rdev(rdev);
	वापस err;
पूर्ण

अटल पूर्णांक set_biपंचांगap_file(काष्ठा mddev *mddev, पूर्णांक fd)
अणु
	पूर्णांक err = 0;

	अगर (mddev->pers) अणु
		अगर (!mddev->pers->quiesce || !mddev->thपढ़ो)
			वापस -EBUSY;
		अगर (mddev->recovery || mddev->sync_thपढ़ो)
			वापस -EBUSY;
		/* we should be able to change the biपंचांगap.. */
	पूर्ण

	अगर (fd >= 0) अणु
		काष्ठा inode *inode;
		काष्ठा file *f;

		अगर (mddev->biपंचांगap || mddev->biपंचांगap_info.file)
			वापस -EEXIST; /* cannot add when biपंचांगap is present */
		f = fget(fd);

		अगर (f == शून्य) अणु
			pr_warn("%s: error: failed to get bitmap file\n",
				mdname(mddev));
			वापस -EBADF;
		पूर्ण

		inode = f->f_mapping->host;
		अगर (!S_ISREG(inode->i_mode)) अणु
			pr_warn("%s: error: bitmap file must be a regular file\n",
				mdname(mddev));
			err = -EBADF;
		पूर्ण अन्यथा अगर (!(f->f_mode & FMODE_WRITE)) अणु
			pr_warn("%s: error: bitmap file must open for write\n",
				mdname(mddev));
			err = -EBADF;
		पूर्ण अन्यथा अगर (atomic_पढ़ो(&inode->i_ग_लिखोcount) != 1) अणु
			pr_warn("%s: error: bitmap file is already in use\n",
				mdname(mddev));
			err = -EBUSY;
		पूर्ण
		अगर (err) अणु
			fput(f);
			वापस err;
		पूर्ण
		mddev->biपंचांगap_info.file = f;
		mddev->biपंचांगap_info.offset = 0; /* file overrides offset */
	पूर्ण अन्यथा अगर (mddev->biपंचांगap == शून्य)
		वापस -ENOENT; /* cannot हटाओ what isn't there */
	err = 0;
	अगर (mddev->pers) अणु
		अगर (fd >= 0) अणु
			काष्ठा biपंचांगap *biपंचांगap;

			biपंचांगap = md_biपंचांगap_create(mddev, -1);
			mddev_suspend(mddev);
			अगर (!IS_ERR(biपंचांगap)) अणु
				mddev->biपंचांगap = biपंचांगap;
				err = md_biपंचांगap_load(mddev);
			पूर्ण अन्यथा
				err = PTR_ERR(biपंचांगap);
			अगर (err) अणु
				md_biपंचांगap_destroy(mddev);
				fd = -1;
			पूर्ण
			mddev_resume(mddev);
		पूर्ण अन्यथा अगर (fd < 0) अणु
			mddev_suspend(mddev);
			md_biपंचांगap_destroy(mddev);
			mddev_resume(mddev);
		पूर्ण
	पूर्ण
	अगर (fd < 0) अणु
		काष्ठा file *f = mddev->biपंचांगap_info.file;
		अगर (f) अणु
			spin_lock(&mddev->lock);
			mddev->biपंचांगap_info.file = शून्य;
			spin_unlock(&mddev->lock);
			fput(f);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/*
 * md_set_array_info is used two dअगरferent ways
 * The original usage is when creating a new array.
 * In this usage, raid_disks is > 0 and it together with
 *  level, size, not_persistent,layout,chunksize determine the
 *  shape of the array.
 *  This will always create an array with a type-0.90.0 superblock.
 * The newer usage is when assembling an array.
 *  In this हाल raid_disks will be 0, and the major_version field is
 *  use to determine which style super-blocks are to be found on the devices.
 *  The minor and patch _version numbers are also kept inहाल the
 *  super_block handler wishes to पूर्णांकerpret them.
 */
पूर्णांक md_set_array_info(काष्ठा mddev *mddev, काष्ठा mdu_array_info_s *info)
अणु
	अगर (info->raid_disks == 0) अणु
		/* just setting version number क्रम superblock loading */
		अगर (info->major_version < 0 ||
		    info->major_version >= ARRAY_SIZE(super_types) ||
		    super_types[info->major_version].name == शून्य) अणु
			/* maybe try to स्वतः-load a module? */
			pr_warn("md: superblock version %d not known\n",
				info->major_version);
			वापस -EINVAL;
		पूर्ण
		mddev->major_version = info->major_version;
		mddev->minor_version = info->minor_version;
		mddev->patch_version = info->patch_version;
		mddev->persistent = !info->not_persistent;
		/* ensure mddev_put करोesn't delete this now that there
		 * is some minimal configuration.
		 */
		mddev->स_समय         = kसमय_get_real_seconds();
		वापस 0;
	पूर्ण
	mddev->major_version = MD_MAJOR_VERSION;
	mddev->minor_version = MD_MINOR_VERSION;
	mddev->patch_version = MD_PATCHLEVEL_VERSION;
	mddev->स_समय         = kसमय_get_real_seconds();

	mddev->level         = info->level;
	mddev->clevel[0]     = 0;
	mddev->dev_sectors   = 2 * (sector_t)info->size;
	mddev->raid_disks    = info->raid_disks;
	/* करोn't set md_minor, it is determined by which /dev/md* was
	 * खोलोned
	 */
	अगर (info->state & (1<<MD_SB_CLEAN))
		mddev->recovery_cp = MaxSector;
	अन्यथा
		mddev->recovery_cp = 0;
	mddev->persistent    = ! info->not_persistent;
	mddev->बाह्यal	     = 0;

	mddev->layout        = info->layout;
	अगर (mddev->level == 0)
		/* Cannot trust RAID0 layout info here */
		mddev->layout = -1;
	mddev->chunk_sectors = info->chunk_size >> 9;

	अगर (mddev->persistent) अणु
		mddev->max_disks = MD_SB_DISKS;
		mddev->flags = 0;
		mddev->sb_flags = 0;
	पूर्ण
	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);

	mddev->biपंचांगap_info.शेष_offset = MD_SB_BYTES >> 9;
	mddev->biपंचांगap_info.शेष_space = 64*2 - (MD_SB_BYTES >> 9);
	mddev->biपंचांगap_info.offset = 0;

	mddev->reshape_position = MaxSector;

	/*
	 * Generate a 128 bit UUID
	 */
	get_अक्रमom_bytes(mddev->uuid, 16);

	mddev->new_level = mddev->level;
	mddev->new_chunk_sectors = mddev->chunk_sectors;
	mddev->new_layout = mddev->layout;
	mddev->delta_disks = 0;
	mddev->reshape_backwards = 0;

	वापस 0;
पूर्ण

व्योम md_set_array_sectors(काष्ठा mddev *mddev, sector_t array_sectors)
अणु
	lockdep_निश्चित_held(&mddev->reconfig_mutex);

	अगर (mddev->बाह्यal_size)
		वापस;

	mddev->array_sectors = array_sectors;
पूर्ण
EXPORT_SYMBOL(md_set_array_sectors);

अटल पूर्णांक update_size(काष्ठा mddev *mddev, sector_t num_sectors)
अणु
	काष्ठा md_rdev *rdev;
	पूर्णांक rv;
	पूर्णांक fit = (num_sectors == 0);
	sector_t old_dev_sectors = mddev->dev_sectors;

	अगर (mddev->pers->resize == शून्य)
		वापस -EINVAL;
	/* The "num_sectors" is the number of sectors of each device that
	 * is used.  This can only make sense क्रम arrays with redundancy.
	 * linear and raid0 always use whatever space is available. We can only
	 * consider changing this number अगर no resync or reस्थिरruction is
	 * happening, and अगर the new size is acceptable. It must fit beक्रमe the
	 * sb_start or, अगर that is <data_offset, it must fit beक्रमe the size
	 * of each device.  If num_sectors is zero, we find the largest size
	 * that fits.
	 */
	अगर (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery) ||
	    mddev->sync_thपढ़ो)
		वापस -EBUSY;
	अगर (mddev->ro)
		वापस -EROFS;

	rdev_क्रम_each(rdev, mddev) अणु
		sector_t avail = rdev->sectors;

		अगर (fit && (num_sectors == 0 || num_sectors > avail))
			num_sectors = avail;
		अगर (avail < num_sectors)
			वापस -ENOSPC;
	पूर्ण
	rv = mddev->pers->resize(mddev, num_sectors);
	अगर (!rv) अणु
		अगर (mddev_is_clustered(mddev))
			md_cluster_ops->update_size(mddev, old_dev_sectors);
		अन्यथा अगर (mddev->queue) अणु
			set_capacity_and_notअगरy(mddev->gendisk,
						mddev->array_sectors);
		पूर्ण
	पूर्ण
	वापस rv;
पूर्ण

अटल पूर्णांक update_raid_disks(काष्ठा mddev *mddev, पूर्णांक raid_disks)
अणु
	पूर्णांक rv;
	काष्ठा md_rdev *rdev;
	/* change the number of raid disks */
	अगर (mddev->pers->check_reshape == शून्य)
		वापस -EINVAL;
	अगर (mddev->ro)
		वापस -EROFS;
	अगर (raid_disks <= 0 ||
	    (mddev->max_disks && raid_disks >= mddev->max_disks))
		वापस -EINVAL;
	अगर (mddev->sync_thपढ़ो ||
	    test_bit(MD_RECOVERY_RUNNING, &mddev->recovery) ||
	    test_bit(MD_RESYNCING_REMOTE, &mddev->recovery) ||
	    mddev->reshape_position != MaxSector)
		वापस -EBUSY;

	rdev_क्रम_each(rdev, mddev) अणु
		अगर (mddev->raid_disks < raid_disks &&
		    rdev->data_offset < rdev->new_data_offset)
			वापस -EINVAL;
		अगर (mddev->raid_disks > raid_disks &&
		    rdev->data_offset > rdev->new_data_offset)
			वापस -EINVAL;
	पूर्ण

	mddev->delta_disks = raid_disks - mddev->raid_disks;
	अगर (mddev->delta_disks < 0)
		mddev->reshape_backwards = 1;
	अन्यथा अगर (mddev->delta_disks > 0)
		mddev->reshape_backwards = 0;

	rv = mddev->pers->check_reshape(mddev);
	अगर (rv < 0) अणु
		mddev->delta_disks = 0;
		mddev->reshape_backwards = 0;
	पूर्ण
	वापस rv;
पूर्ण

/*
 * update_array_info is used to change the configuration of an
 * on-line array.
 * The version, स_समय,level,size,raid_disks,not_persistent, layout,chunk_size
 * fields in the info are checked against the array.
 * Any dअगरferences that cannot be handled will cause an error.
 * Normally, only one change can be managed at a समय.
 */
अटल पूर्णांक update_array_info(काष्ठा mddev *mddev, mdu_array_info_t *info)
अणु
	पूर्णांक rv = 0;
	पूर्णांक cnt = 0;
	पूर्णांक state = 0;

	/* calculate expected state,ignoring low bits */
	अगर (mddev->biपंचांगap && mddev->biपंचांगap_info.offset)
		state |= (1 << MD_SB_BITMAP_PRESENT);

	अगर (mddev->major_version != info->major_version ||
	    mddev->minor_version != info->minor_version ||
/*	    mddev->patch_version != info->patch_version || */
	    mddev->स_समय         != info->स_समय         ||
	    mddev->level         != info->level         ||
/*	    mddev->layout        != info->layout        || */
	    mddev->persistent	 != !info->not_persistent ||
	    mddev->chunk_sectors != info->chunk_size >> 9 ||
	    /* ignore bottom 8 bits of state, and allow SB_BITMAP_PRESENT to change */
	    ((state^info->state) & 0xfffffe00)
		)
		वापस -EINVAL;
	/* Check there is only one change */
	अगर (info->size >= 0 && mddev->dev_sectors / 2 != info->size)
		cnt++;
	अगर (mddev->raid_disks != info->raid_disks)
		cnt++;
	अगर (mddev->layout != info->layout)
		cnt++;
	अगर ((state ^ info->state) & (1<<MD_SB_BITMAP_PRESENT))
		cnt++;
	अगर (cnt == 0)
		वापस 0;
	अगर (cnt > 1)
		वापस -EINVAL;

	अगर (mddev->layout != info->layout) अणु
		/* Change layout
		 * we करोn't need to करो anything at the md level, the
		 * personality will take care of it all.
		 */
		अगर (mddev->pers->check_reshape == शून्य)
			वापस -EINVAL;
		अन्यथा अणु
			mddev->new_layout = info->layout;
			rv = mddev->pers->check_reshape(mddev);
			अगर (rv)
				mddev->new_layout = mddev->layout;
			वापस rv;
		पूर्ण
	पूर्ण
	अगर (info->size >= 0 && mddev->dev_sectors / 2 != info->size)
		rv = update_size(mddev, (sector_t)info->size * 2);

	अगर (mddev->raid_disks    != info->raid_disks)
		rv = update_raid_disks(mddev, info->raid_disks);

	अगर ((state ^ info->state) & (1<<MD_SB_BITMAP_PRESENT)) अणु
		अगर (mddev->pers->quiesce == शून्य || mddev->thपढ़ो == शून्य) अणु
			rv = -EINVAL;
			जाओ err;
		पूर्ण
		अगर (mddev->recovery || mddev->sync_thपढ़ो) अणु
			rv = -EBUSY;
			जाओ err;
		पूर्ण
		अगर (info->state & (1<<MD_SB_BITMAP_PRESENT)) अणु
			काष्ठा biपंचांगap *biपंचांगap;
			/* add the biपंचांगap */
			अगर (mddev->biपंचांगap) अणु
				rv = -EEXIST;
				जाओ err;
			पूर्ण
			अगर (mddev->biपंचांगap_info.शेष_offset == 0) अणु
				rv = -EINVAL;
				जाओ err;
			पूर्ण
			mddev->biपंचांगap_info.offset =
				mddev->biपंचांगap_info.शेष_offset;
			mddev->biपंचांगap_info.space =
				mddev->biपंचांगap_info.शेष_space;
			biपंचांगap = md_biपंचांगap_create(mddev, -1);
			mddev_suspend(mddev);
			अगर (!IS_ERR(biपंचांगap)) अणु
				mddev->biपंचांगap = biपंचांगap;
				rv = md_biपंचांगap_load(mddev);
			पूर्ण अन्यथा
				rv = PTR_ERR(biपंचांगap);
			अगर (rv)
				md_biपंचांगap_destroy(mddev);
			mddev_resume(mddev);
		पूर्ण अन्यथा अणु
			/* हटाओ the biपंचांगap */
			अगर (!mddev->biपंचांगap) अणु
				rv = -ENOENT;
				जाओ err;
			पूर्ण
			अगर (mddev->biपंचांगap->storage.file) अणु
				rv = -EINVAL;
				जाओ err;
			पूर्ण
			अगर (mddev->biपंचांगap_info.nodes) अणु
				/* hold PW on all the biपंचांगap lock */
				अगर (md_cluster_ops->lock_all_biपंचांगaps(mddev) <= 0) अणु
					pr_warn("md: can't change bitmap to none since the array is in use by more than one node\n");
					rv = -EPERM;
					md_cluster_ops->unlock_all_biपंचांगaps(mddev);
					जाओ err;
				पूर्ण

				mddev->biपंचांगap_info.nodes = 0;
				md_cluster_ops->leave(mddev);
				module_put(md_cluster_mod);
				mddev->safemode_delay = DEFAULT_SAFEMODE_DELAY;
			पूर्ण
			mddev_suspend(mddev);
			md_biपंचांगap_destroy(mddev);
			mddev_resume(mddev);
			mddev->biपंचांगap_info.offset = 0;
		पूर्ण
	पूर्ण
	md_update_sb(mddev, 1);
	वापस rv;
err:
	वापस rv;
पूर्ण

अटल पूर्णांक set_disk_faulty(काष्ठा mddev *mddev, dev_t dev)
अणु
	काष्ठा md_rdev *rdev;
	पूर्णांक err = 0;

	अगर (mddev->pers == शून्य)
		वापस -ENODEV;

	rcu_पढ़ो_lock();
	rdev = md_find_rdev_rcu(mddev, dev);
	अगर (!rdev)
		err =  -ENODEV;
	अन्यथा अणु
		md_error(mddev, rdev);
		अगर (!test_bit(Faulty, &rdev->flags))
			err = -EBUSY;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

/*
 * We have a problem here : there is no easy way to give a CHS
 * भव geometry. We currently pretend that we have a 2 heads
 * 4 sectors (with a BIG number of cylinders...). This drives
 * करोsfs just mad... ;-)
 */
अटल पूर्णांक md_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा mddev *mddev = bdev->bd_disk->निजी_data;

	geo->heads = 2;
	geo->sectors = 4;
	geo->cylinders = mddev->array_sectors / 8;
	वापस 0;
पूर्ण

अटल अंतरभूत bool md_ioctl_valid(अचिन्हित पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल ADD_NEW_DISK:
	हाल GET_ARRAY_INFO:
	हाल GET_BITMAP_खाता:
	हाल GET_DISK_INFO:
	हाल HOT_ADD_DISK:
	हाल HOT_REMOVE_DISK:
	हाल RAID_VERSION:
	हाल RESTART_ARRAY_RW:
	हाल RUN_ARRAY:
	हाल SET_ARRAY_INFO:
	हाल SET_BITMAP_खाता:
	हाल SET_DISK_FAULTY:
	हाल STOP_ARRAY:
	हाल STOP_ARRAY_RO:
	हाल CLUSTERED_DISK_NACK:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक md_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err = 0;
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा mddev *mddev = शून्य;
	bool did_set_md_closing = false;

	अगर (!md_ioctl_valid(cmd))
		वापस -ENOTTY;

	चयन (cmd) अणु
	हाल RAID_VERSION:
	हाल GET_ARRAY_INFO:
	हाल GET_DISK_INFO:
		अवरोध;
	शेष:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EACCES;
	पूर्ण

	/*
	 * Commands dealing with the RAID driver but not any
	 * particular array:
	 */
	चयन (cmd) अणु
	हाल RAID_VERSION:
		err = get_version(argp);
		जाओ out;
	शेष:;
	पूर्ण

	/*
	 * Commands creating/starting a new array:
	 */

	mddev = bdev->bd_disk->निजी_data;

	अगर (!mddev) अणु
		BUG();
		जाओ out;
	पूर्ण

	/* Some actions करो not requires the mutex */
	चयन (cmd) अणु
	हाल GET_ARRAY_INFO:
		अगर (!mddev->raid_disks && !mddev->बाह्यal)
			err = -ENODEV;
		अन्यथा
			err = get_array_info(mddev, argp);
		जाओ out;

	हाल GET_DISK_INFO:
		अगर (!mddev->raid_disks && !mddev->बाह्यal)
			err = -ENODEV;
		अन्यथा
			err = get_disk_info(mddev, argp);
		जाओ out;

	हाल SET_DISK_FAULTY:
		err = set_disk_faulty(mddev, new_decode_dev(arg));
		जाओ out;

	हाल GET_BITMAP_खाता:
		err = get_biपंचांगap_file(mddev, argp);
		जाओ out;

	पूर्ण

	अगर (cmd == ADD_NEW_DISK || cmd == HOT_ADD_DISK)
		flush_rdev_wq(mddev);

	अगर (cmd == HOT_REMOVE_DISK)
		/* need to ensure recovery thपढ़ो has run */
		रुको_event_पूर्णांकerruptible_समयout(mddev->sb_रुको,
						 !test_bit(MD_RECOVERY_NEEDED,
							   &mddev->recovery),
						 msecs_to_jअगरfies(5000));
	अगर (cmd == STOP_ARRAY || cmd == STOP_ARRAY_RO) अणु
		/* Need to flush page cache, and ensure no-one अन्यथा खोलोs
		 * and ग_लिखोs
		 */
		mutex_lock(&mddev->खोलो_mutex);
		अगर (mddev->pers && atomic_पढ़ो(&mddev->खोलोers) > 1) अणु
			mutex_unlock(&mddev->खोलो_mutex);
			err = -EBUSY;
			जाओ out;
		पूर्ण
		अगर (test_and_set_bit(MD_CLOSING, &mddev->flags)) अणु
			mutex_unlock(&mddev->खोलो_mutex);
			err = -EBUSY;
			जाओ out;
		पूर्ण
		did_set_md_closing = true;
		mutex_unlock(&mddev->खोलो_mutex);
		sync_blockdev(bdev);
	पूर्ण
	err = mddev_lock(mddev);
	अगर (err) अणु
		pr_debug("md: ioctl lock interrupted, reason %d, cmd %d\n",
			 err, cmd);
		जाओ out;
	पूर्ण

	अगर (cmd == SET_ARRAY_INFO) अणु
		mdu_array_info_t info;
		अगर (!arg)
			स_रखो(&info, 0, माप(info));
		अन्यथा अगर (copy_from_user(&info, argp, माप(info))) अणु
			err = -EFAULT;
			जाओ unlock;
		पूर्ण
		अगर (mddev->pers) अणु
			err = update_array_info(mddev, &info);
			अगर (err) अणु
				pr_warn("md: couldn't update array info. %d\n", err);
				जाओ unlock;
			पूर्ण
			जाओ unlock;
		पूर्ण
		अगर (!list_empty(&mddev->disks)) अणु
			pr_warn("md: array %s already has disks!\n", mdname(mddev));
			err = -EBUSY;
			जाओ unlock;
		पूर्ण
		अगर (mddev->raid_disks) अणु
			pr_warn("md: array %s already initialised!\n", mdname(mddev));
			err = -EBUSY;
			जाओ unlock;
		पूर्ण
		err = md_set_array_info(mddev, &info);
		अगर (err) अणु
			pr_warn("md: couldn't set array info. %d\n", err);
			जाओ unlock;
		पूर्ण
		जाओ unlock;
	पूर्ण

	/*
	 * Commands querying/configuring an existing array:
	 */
	/* अगर we are not initialised yet, only ADD_NEW_DISK, STOP_ARRAY,
	 * RUN_ARRAY, and GET_ and SET_BITMAP_खाता are allowed */
	अगर ((!mddev->raid_disks && !mddev->बाह्यal)
	    && cmd != ADD_NEW_DISK && cmd != STOP_ARRAY
	    && cmd != RUN_ARRAY && cmd != SET_BITMAP_खाता
	    && cmd != GET_BITMAP_खाता) अणु
		err = -ENODEV;
		जाओ unlock;
	पूर्ण

	/*
	 * Commands even a पढ़ो-only array can execute:
	 */
	चयन (cmd) अणु
	हाल RESTART_ARRAY_RW:
		err = restart_array(mddev);
		जाओ unlock;

	हाल STOP_ARRAY:
		err = करो_md_stop(mddev, 0, bdev);
		जाओ unlock;

	हाल STOP_ARRAY_RO:
		err = md_set_पढ़ोonly(mddev, bdev);
		जाओ unlock;

	हाल HOT_REMOVE_DISK:
		err = hot_हटाओ_disk(mddev, new_decode_dev(arg));
		जाओ unlock;

	हाल ADD_NEW_DISK:
		/* We can support ADD_NEW_DISK on पढ़ो-only arrays
		 * only अगर we are re-adding a preexisting device.
		 * So require mddev->pers and MD_DISK_SYNC.
		 */
		अगर (mddev->pers) अणु
			mdu_disk_info_t info;
			अगर (copy_from_user(&info, argp, माप(info)))
				err = -EFAULT;
			अन्यथा अगर (!(info.state & (1<<MD_DISK_SYNC)))
				/* Need to clear पढ़ो-only क्रम this */
				अवरोध;
			अन्यथा
				err = md_add_new_disk(mddev, &info);
			जाओ unlock;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 * The reमुख्यing ioctls are changing the state of the
	 * superblock, so we करो not allow them on पढ़ो-only arrays.
	 */
	अगर (mddev->ro && mddev->pers) अणु
		अगर (mddev->ro == 2) अणु
			mddev->ro = 0;
			sysfs_notअगरy_dirent_safe(mddev->sysfs_state);
			set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
			/* mddev_unlock will wake thपढ़ो */
			/* If a device failed जबतक we were पढ़ो-only, we
			 * need to make sure the metadata is updated now.
			 */
			अगर (test_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags)) अणु
				mddev_unlock(mddev);
				रुको_event(mddev->sb_रुको,
					   !test_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags) &&
					   !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags));
				mddev_lock_noपूर्णांकr(mddev);
			पूर्ण
		पूर्ण अन्यथा अणु
			err = -EROFS;
			जाओ unlock;
		पूर्ण
	पूर्ण

	चयन (cmd) अणु
	हाल ADD_NEW_DISK:
	अणु
		mdu_disk_info_t info;
		अगर (copy_from_user(&info, argp, माप(info)))
			err = -EFAULT;
		अन्यथा
			err = md_add_new_disk(mddev, &info);
		जाओ unlock;
	पूर्ण

	हाल CLUSTERED_DISK_NACK:
		अगर (mddev_is_clustered(mddev))
			md_cluster_ops->new_disk_ack(mddev, false);
		अन्यथा
			err = -EINVAL;
		जाओ unlock;

	हाल HOT_ADD_DISK:
		err = hot_add_disk(mddev, new_decode_dev(arg));
		जाओ unlock;

	हाल RUN_ARRAY:
		err = करो_md_run(mddev);
		जाओ unlock;

	हाल SET_BITMAP_खाता:
		err = set_biपंचांगap_file(mddev, (पूर्णांक)arg);
		जाओ unlock;

	शेष:
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

unlock:
	अगर (mddev->hold_active == UNTIL_IOCTL &&
	    err != -EINVAL)
		mddev->hold_active = 0;
	mddev_unlock(mddev);
out:
	अगर(did_set_md_closing)
		clear_bit(MD_CLOSING, &mddev->flags);
	वापस err;
पूर्ण
#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक md_compat_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल HOT_REMOVE_DISK:
	हाल HOT_ADD_DISK:
	हाल SET_DISK_FAULTY:
	हाल SET_BITMAP_खाता:
		/* These take in पूर्णांकeger arg, करो not convert */
		अवरोध;
	शेष:
		arg = (अचिन्हित दीर्घ)compat_ptr(arg);
		अवरोध;
	पूर्ण

	वापस md_ioctl(bdev, mode, cmd, arg);
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

अटल पूर्णांक md_set_पढ़ो_only(काष्ठा block_device *bdev, bool ro)
अणु
	काष्ठा mddev *mddev = bdev->bd_disk->निजी_data;
	पूर्णांक err;

	err = mddev_lock(mddev);
	अगर (err)
		वापस err;

	अगर (!mddev->raid_disks && !mddev->बाह्यal) अणु
		err = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	/*
	 * Transitioning to पढ़ो-स्वतः need only happen क्रम arrays that call
	 * md_ग_लिखो_start and which are not पढ़ोy क्रम ग_लिखोs yet.
	 */
	अगर (!ro && mddev->ro == 1 && mddev->pers) अणु
		err = restart_array(mddev);
		अगर (err)
			जाओ out_unlock;
		mddev->ro = 2;
	पूर्ण

out_unlock:
	mddev_unlock(mddev);
	वापस err;
पूर्ण

अटल पूर्णांक md_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	/*
	 * Succeed अगर we can lock the mddev, which confirms that
	 * it isn't being stopped right now.
	 */
	काष्ठा mddev *mddev = mddev_find(bdev->bd_dev);
	पूर्णांक err;

	अगर (!mddev)
		वापस -ENODEV;

	अगर (mddev->gendisk != bdev->bd_disk) अणु
		/* we are racing with mddev_put which is discarding this
		 * bd_disk.
		 */
		mddev_put(mddev);
		/* Wait until bdev->bd_disk is definitely gone */
		अगर (work_pending(&mddev->del_work))
			flush_workqueue(md_misc_wq);
		वापस -EBUSY;
	पूर्ण
	BUG_ON(mddev != bdev->bd_disk->निजी_data);

	अगर ((err = mutex_lock_पूर्णांकerruptible(&mddev->खोलो_mutex)))
		जाओ out;

	अगर (test_bit(MD_CLOSING, &mddev->flags)) अणु
		mutex_unlock(&mddev->खोलो_mutex);
		err = -ENODEV;
		जाओ out;
	पूर्ण

	err = 0;
	atomic_inc(&mddev->खोलोers);
	mutex_unlock(&mddev->खोलो_mutex);

	bdev_check_media_change(bdev);
 out:
	अगर (err)
		mddev_put(mddev);
	वापस err;
पूर्ण

अटल व्योम md_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा mddev *mddev = disk->निजी_data;

	BUG_ON(!mddev);
	atomic_dec(&mddev->खोलोers);
	mddev_put(mddev);
पूर्ण

अटल अचिन्हित पूर्णांक md_check_events(काष्ठा gendisk *disk, अचिन्हित पूर्णांक clearing)
अणु
	काष्ठा mddev *mddev = disk->निजी_data;
	अचिन्हित पूर्णांक ret = 0;

	अगर (mddev->changed)
		ret = DISK_EVENT_MEDIA_CHANGE;
	mddev->changed = 0;
	वापस ret;
पूर्ण

स्थिर काष्ठा block_device_operations md_fops =
अणु
	.owner		= THIS_MODULE,
	.submit_bio	= md_submit_bio,
	.खोलो		= md_खोलो,
	.release	= md_release,
	.ioctl		= md_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= md_compat_ioctl,
#पूर्ण_अगर
	.getgeo		= md_getgeo,
	.check_events	= md_check_events,
	.set_पढ़ो_only	= md_set_पढ़ो_only,
पूर्ण;

अटल पूर्णांक md_thपढ़ो(व्योम *arg)
अणु
	काष्ठा md_thपढ़ो *thपढ़ो = arg;

	/*
	 * md_thपढ़ो is a 'system-thread', it's priority should be very
	 * high. We aव्योम resource deadlocks inभागidually in each
	 * raid personality. (RAID5 करोes pपुनः_स्मृतिation) We also use RR and
	 * the very same RT priority as kswapd, thus we will never get
	 * पूर्णांकo a priority inversion deadlock.
	 *
	 * we definitely have to have equal or higher priority than
	 * bdflush, otherwise bdflush will deadlock अगर there are too
	 * many dirty RAID5 blocks.
	 */

	allow_संकेत(SIGKILL);
	जबतक (!kthपढ़ो_should_stop()) अणु

		/* We need to रुको INTERRUPTIBLE so that
		 * we करोn't add to the load-average.
		 * That means we need to be sure no संकेतs are
		 * pending
		 */
		अगर (संकेत_pending(current))
			flush_संकेतs(current);

		रुको_event_पूर्णांकerruptible_समयout
			(thपढ़ो->wqueue,
			 test_bit(THREAD_WAKEUP, &thपढ़ो->flags)
			 || kthपढ़ो_should_stop() || kthपढ़ो_should_park(),
			 thपढ़ो->समयout);

		clear_bit(THREAD_WAKEUP, &thपढ़ो->flags);
		अगर (kthपढ़ो_should_park())
			kthपढ़ो_parkme();
		अगर (!kthपढ़ो_should_stop())
			thपढ़ो->run(thपढ़ो);
	पूर्ण

	वापस 0;
पूर्ण

व्योम md_wakeup_thपढ़ो(काष्ठा md_thपढ़ो *thपढ़ो)
अणु
	अगर (thपढ़ो) अणु
		pr_debug("md: waking up MD thread %s.\n", thपढ़ो->tsk->comm);
		set_bit(THREAD_WAKEUP, &thपढ़ो->flags);
		wake_up(&thपढ़ो->wqueue);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(md_wakeup_thपढ़ो);

काष्ठा md_thपढ़ो *md_रेजिस्टर_thपढ़ो(व्योम (*run) (काष्ठा md_thपढ़ो *),
		काष्ठा mddev *mddev, स्थिर अक्षर *name)
अणु
	काष्ठा md_thपढ़ो *thपढ़ो;

	thपढ़ो = kzalloc(माप(काष्ठा md_thपढ़ो), GFP_KERNEL);
	अगर (!thपढ़ो)
		वापस शून्य;

	init_रुकोqueue_head(&thपढ़ो->wqueue);

	thपढ़ो->run = run;
	thपढ़ो->mddev = mddev;
	thपढ़ो->समयout = MAX_SCHEDULE_TIMEOUT;
	thपढ़ो->tsk = kthपढ़ो_run(md_thपढ़ो, thपढ़ो,
				  "%s_%s",
				  mdname(thपढ़ो->mddev),
				  name);
	अगर (IS_ERR(thपढ़ो->tsk)) अणु
		kमुक्त(thपढ़ो);
		वापस शून्य;
	पूर्ण
	वापस thपढ़ो;
पूर्ण
EXPORT_SYMBOL(md_रेजिस्टर_thपढ़ो);

व्योम md_unरेजिस्टर_thपढ़ो(काष्ठा md_thपढ़ो **thपढ़ोp)
अणु
	काष्ठा md_thपढ़ो *thपढ़ो = *thपढ़ोp;
	अगर (!thपढ़ो)
		वापस;
	pr_debug("interrupting MD-thread pid %d\n", task_pid_nr(thपढ़ो->tsk));
	/* Locking ensures that mddev_unlock करोes not wake_up a
	 * non-existent thपढ़ो
	 */
	spin_lock(&pers_lock);
	*thपढ़ोp = शून्य;
	spin_unlock(&pers_lock);

	kthपढ़ो_stop(thपढ़ो->tsk);
	kमुक्त(thपढ़ो);
पूर्ण
EXPORT_SYMBOL(md_unरेजिस्टर_thपढ़ो);

व्योम md_error(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	अगर (!rdev || test_bit(Faulty, &rdev->flags))
		वापस;

	अगर (!mddev->pers || !mddev->pers->error_handler)
		वापस;
	mddev->pers->error_handler(mddev,rdev);
	अगर (mddev->degraded)
		set_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
	sysfs_notअगरy_dirent_safe(rdev->sysfs_state);
	set_bit(MD_RECOVERY_INTR, &mddev->recovery);
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	md_wakeup_thपढ़ो(mddev->thपढ़ो);
	अगर (mddev->event_work.func)
		queue_work(md_misc_wq, &mddev->event_work);
	md_new_event(mddev);
पूर्ण
EXPORT_SYMBOL(md_error);

/* seq_file implementation /proc/mdstat */

अटल व्योम status_unused(काष्ठा seq_file *seq)
अणु
	पूर्णांक i = 0;
	काष्ठा md_rdev *rdev;

	seq_म_लिखो(seq, "unused devices: ");

	list_क्रम_each_entry(rdev, &pending_raid_disks, same_set) अणु
		अक्षर b[BDEVNAME_SIZE];
		i++;
		seq_म_लिखो(seq, "%s ",
			      bdevname(rdev->bdev,b));
	पूर्ण
	अगर (!i)
		seq_म_लिखो(seq, "<none>");

	seq_म_लिखो(seq, "\n");
पूर्ण

अटल पूर्णांक status_resync(काष्ठा seq_file *seq, काष्ठा mddev *mddev)
अणु
	sector_t max_sectors, resync, res;
	अचिन्हित दीर्घ dt, db = 0;
	sector_t rt, curr_mark_cnt, resync_mark_cnt;
	पूर्णांक scale, recovery_active;
	अचिन्हित पूर्णांक per_milli;

	अगर (test_bit(MD_RECOVERY_SYNC, &mddev->recovery) ||
	    test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery))
		max_sectors = mddev->resync_max_sectors;
	अन्यथा
		max_sectors = mddev->dev_sectors;

	resync = mddev->curr_resync;
	अगर (resync <= 3) अणु
		अगर (test_bit(MD_RECOVERY_DONE, &mddev->recovery))
			/* Still cleaning up */
			resync = max_sectors;
	पूर्ण अन्यथा अगर (resync > max_sectors)
		resync = max_sectors;
	अन्यथा
		resync -= atomic_पढ़ो(&mddev->recovery_active);

	अगर (resync == 0) अणु
		अगर (test_bit(MD_RESYNCING_REMOTE, &mddev->recovery)) अणु
			काष्ठा md_rdev *rdev;

			rdev_क्रम_each(rdev, mddev)
				अगर (rdev->raid_disk >= 0 &&
				    !test_bit(Faulty, &rdev->flags) &&
				    rdev->recovery_offset != MaxSector &&
				    rdev->recovery_offset) अणु
					seq_म_लिखो(seq, "\trecover=REMOTE");
					वापस 1;
				पूर्ण
			अगर (mddev->reshape_position != MaxSector)
				seq_म_लिखो(seq, "\treshape=REMOTE");
			अन्यथा
				seq_म_लिखो(seq, "\tresync=REMOTE");
			वापस 1;
		पूर्ण
		अगर (mddev->recovery_cp < MaxSector) अणु
			seq_म_लिखो(seq, "\tresync=PENDING");
			वापस 1;
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (resync < 3) अणु
		seq_म_लिखो(seq, "\tresync=DELAYED");
		वापस 1;
	पूर्ण

	WARN_ON(max_sectors == 0);
	/* Pick 'scale' such that (resync>>scale)*1000 will fit
	 * in a sector_t, and (max_sectors>>scale) will fit in a
	 * u32, as those are the requirements क्रम sector_भाग.
	 * Thus 'scale' must be at least 10
	 */
	scale = 10;
	अगर (माप(sector_t) > माप(अचिन्हित दीर्घ)) अणु
		जबतक ( max_sectors/2 > (1ULL<<(scale+32)))
			scale++;
	पूर्ण
	res = (resync>>scale)*1000;
	sector_भाग(res, (u32)((max_sectors>>scale)+1));

	per_milli = res;
	अणु
		पूर्णांक i, x = per_milli/50, y = 20-x;
		seq_म_लिखो(seq, "[");
		क्रम (i = 0; i < x; i++)
			seq_म_लिखो(seq, "=");
		seq_म_लिखो(seq, ">");
		क्रम (i = 0; i < y; i++)
			seq_म_लिखो(seq, ".");
		seq_म_लिखो(seq, "] ");
	पूर्ण
	seq_म_लिखो(seq, " %s =%3u.%u%% (%llu/%llu)",
		   (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery)?
		    "reshape" :
		    (test_bit(MD_RECOVERY_CHECK, &mddev->recovery)?
		     "check" :
		     (test_bit(MD_RECOVERY_SYNC, &mddev->recovery) ?
		      "resync" : "recovery"))),
		   per_milli/10, per_milli % 10,
		   (अचिन्हित दीर्घ दीर्घ) resync/2,
		   (अचिन्हित दीर्घ दीर्घ) max_sectors/2);

	/*
	 * dt: समय from mark until now
	 * db: blocks written from mark until now
	 * rt: reमुख्यing समय
	 *
	 * rt is a sector_t, which is always 64bit now. We are keeping
	 * the original algorithm, but it is not really necessary.
	 *
	 * Original algorithm:
	 *   So we भागide beक्रमe multiply in हाल it is 32bit and बंद
	 *   to the limit.
	 *   We scale the भागisor (db) by 32 to aव्योम losing precision
	 *   near the end of resync when the number of reमुख्यing sectors
	 *   is बंद to 'db'.
	 *   We then भागide rt by 32 after multiplying by db to compensate.
	 *   The '+1' aव्योमs भागision by zero अगर db is very small.
	 */
	dt = ((jअगरfies - mddev->resync_mark) / HZ);
	अगर (!dt) dt++;

	curr_mark_cnt = mddev->curr_mark_cnt;
	recovery_active = atomic_पढ़ो(&mddev->recovery_active);
	resync_mark_cnt = mddev->resync_mark_cnt;

	अगर (curr_mark_cnt >= (recovery_active + resync_mark_cnt))
		db = curr_mark_cnt - (recovery_active + resync_mark_cnt);

	rt = max_sectors - resync;    /* number of reमुख्यing sectors */
	rt = भाग64_u64(rt, db/32+1);
	rt *= dt;
	rt >>= 5;

	seq_म_लिखो(seq, " finish=%lu.%lumin", (अचिन्हित दीर्घ)rt / 60,
		   ((अचिन्हित दीर्घ)rt % 60)/6);

	seq_म_लिखो(seq, " speed=%ldK/sec", db/2/dt);
	वापस 1;
पूर्ण

अटल व्योम *md_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा list_head *पंचांगp;
	loff_t l = *pos;
	काष्ठा mddev *mddev;

	अगर (l == 0x10000) अणु
		++*pos;
		वापस (व्योम *)2;
	पूर्ण
	अगर (l > 0x10000)
		वापस शून्य;
	अगर (!l--)
		/* header */
		वापस (व्योम*)1;

	spin_lock(&all_mddevs_lock);
	list_क्रम_each(पंचांगp,&all_mddevs)
		अगर (!l--) अणु
			mddev = list_entry(पंचांगp, काष्ठा mddev, all_mddevs);
			mddev_get(mddev);
			spin_unlock(&all_mddevs_lock);
			वापस mddev;
		पूर्ण
	spin_unlock(&all_mddevs_lock);
	अगर (!l--)
		वापस (व्योम*)2;/* tail */
	वापस शून्य;
पूर्ण

अटल व्योम *md_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा list_head *पंचांगp;
	काष्ठा mddev *next_mddev, *mddev = v;

	++*pos;
	अगर (v == (व्योम*)2)
		वापस शून्य;

	spin_lock(&all_mddevs_lock);
	अगर (v == (व्योम*)1)
		पंचांगp = all_mddevs.next;
	अन्यथा
		पंचांगp = mddev->all_mddevs.next;
	अगर (पंचांगp != &all_mddevs)
		next_mddev = mddev_get(list_entry(पंचांगp,काष्ठा mddev,all_mddevs));
	अन्यथा अणु
		next_mddev = (व्योम*)2;
		*pos = 0x10000;
	पूर्ण
	spin_unlock(&all_mddevs_lock);

	अगर (v != (व्योम*)1)
		mddev_put(mddev);
	वापस next_mddev;

पूर्ण

अटल व्योम md_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा mddev *mddev = v;

	अगर (mddev && v != (व्योम*)1 && v != (व्योम*)2)
		mddev_put(mddev);
पूर्ण

अटल पूर्णांक md_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा mddev *mddev = v;
	sector_t sectors;
	काष्ठा md_rdev *rdev;

	अगर (v == (व्योम*)1) अणु
		काष्ठा md_personality *pers;
		seq_म_लिखो(seq, "Personalities : ");
		spin_lock(&pers_lock);
		list_क्रम_each_entry(pers, &pers_list, list)
			seq_म_लिखो(seq, "[%s] ", pers->name);

		spin_unlock(&pers_lock);
		seq_म_लिखो(seq, "\n");
		seq->poll_event = atomic_पढ़ो(&md_event_count);
		वापस 0;
	पूर्ण
	अगर (v == (व्योम*)2) अणु
		status_unused(seq);
		वापस 0;
	पूर्ण

	spin_lock(&mddev->lock);
	अगर (mddev->pers || mddev->raid_disks || !list_empty(&mddev->disks)) अणु
		seq_म_लिखो(seq, "%s : %sactive", mdname(mddev),
						mddev->pers ? "" : "in");
		अगर (mddev->pers) अणु
			अगर (mddev->ro==1)
				seq_म_लिखो(seq, " (read-only)");
			अगर (mddev->ro==2)
				seq_म_लिखो(seq, " (auto-read-only)");
			seq_म_लिखो(seq, " %s", mddev->pers->name);
		पूर्ण

		sectors = 0;
		rcu_पढ़ो_lock();
		rdev_क्रम_each_rcu(rdev, mddev) अणु
			अक्षर b[BDEVNAME_SIZE];
			seq_म_लिखो(seq, " %s[%d]",
				bdevname(rdev->bdev,b), rdev->desc_nr);
			अगर (test_bit(WriteMostly, &rdev->flags))
				seq_म_लिखो(seq, "(W)");
			अगर (test_bit(Journal, &rdev->flags))
				seq_म_लिखो(seq, "(J)");
			अगर (test_bit(Faulty, &rdev->flags)) अणु
				seq_म_लिखो(seq, "(F)");
				जारी;
			पूर्ण
			अगर (rdev->raid_disk < 0)
				seq_म_लिखो(seq, "(S)"); /* spare */
			अगर (test_bit(Replacement, &rdev->flags))
				seq_म_लिखो(seq, "(R)");
			sectors += rdev->sectors;
		पूर्ण
		rcu_पढ़ो_unlock();

		अगर (!list_empty(&mddev->disks)) अणु
			अगर (mddev->pers)
				seq_म_लिखो(seq, "\n      %llu blocks",
					   (अचिन्हित दीर्घ दीर्घ)
					   mddev->array_sectors / 2);
			अन्यथा
				seq_म_लिखो(seq, "\n      %llu blocks",
					   (अचिन्हित दीर्घ दीर्घ)sectors / 2);
		पूर्ण
		अगर (mddev->persistent) अणु
			अगर (mddev->major_version != 0 ||
			    mddev->minor_version != 90) अणु
				seq_म_लिखो(seq," super %d.%d",
					   mddev->major_version,
					   mddev->minor_version);
			पूर्ण
		पूर्ण अन्यथा अगर (mddev->बाह्यal)
			seq_म_लिखो(seq, " super external:%s",
				   mddev->metadata_type);
		अन्यथा
			seq_म_लिखो(seq, " super non-persistent");

		अगर (mddev->pers) अणु
			mddev->pers->status(seq, mddev);
			seq_म_लिखो(seq, "\n      ");
			अगर (mddev->pers->sync_request) अणु
				अगर (status_resync(seq, mddev))
					seq_म_लिखो(seq, "\n      ");
			पूर्ण
		पूर्ण अन्यथा
			seq_म_लिखो(seq, "\n       ");

		md_biपंचांगap_status(seq, mddev->biपंचांगap);

		seq_म_लिखो(seq, "\n");
	पूर्ण
	spin_unlock(&mddev->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations md_seq_ops = अणु
	.start  = md_seq_start,
	.next   = md_seq_next,
	.stop   = md_seq_stop,
	.show   = md_seq_show,
पूर्ण;

अटल पूर्णांक md_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq;
	पूर्णांक error;

	error = seq_खोलो(file, &md_seq_ops);
	अगर (error)
		वापस error;

	seq = file->निजी_data;
	seq->poll_event = atomic_पढ़ो(&md_event_count);
	वापस error;
पूर्ण

अटल पूर्णांक md_unloading;
अटल __poll_t mdstat_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा seq_file *seq = filp->निजी_data;
	__poll_t mask;

	अगर (md_unloading)
		वापस EPOLLIN|EPOLLRDNORM|EPOLLERR|EPOLLPRI;
	poll_रुको(filp, &md_event_रुकोers, रुको);

	/* always allow पढ़ो */
	mask = EPOLLIN | EPOLLRDNORM;

	अगर (seq->poll_event != atomic_पढ़ो(&md_event_count))
		mask |= EPOLLERR | EPOLLPRI;
	वापस mask;
पूर्ण

अटल स्थिर काष्ठा proc_ops mdstat_proc_ops = अणु
	.proc_खोलो	= md_seq_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release,
	.proc_poll	= mdstat_poll,
पूर्ण;

पूर्णांक रेजिस्टर_md_personality(काष्ठा md_personality *p)
अणु
	pr_debug("md: %s personality registered for level %d\n",
		 p->name, p->level);
	spin_lock(&pers_lock);
	list_add_tail(&p->list, &pers_list);
	spin_unlock(&pers_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_md_personality);

पूर्णांक unरेजिस्टर_md_personality(काष्ठा md_personality *p)
अणु
	pr_debug("md: %s personality unregistered\n", p->name);
	spin_lock(&pers_lock);
	list_del_init(&p->list);
	spin_unlock(&pers_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_md_personality);

पूर्णांक रेजिस्टर_md_cluster_operations(काष्ठा md_cluster_operations *ops,
				   काष्ठा module *module)
अणु
	पूर्णांक ret = 0;
	spin_lock(&pers_lock);
	अगर (md_cluster_ops != शून्य)
		ret = -EALREADY;
	अन्यथा अणु
		md_cluster_ops = ops;
		md_cluster_mod = module;
	पूर्ण
	spin_unlock(&pers_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_md_cluster_operations);

पूर्णांक unरेजिस्टर_md_cluster_operations(व्योम)
अणु
	spin_lock(&pers_lock);
	md_cluster_ops = शून्य;
	spin_unlock(&pers_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_md_cluster_operations);

पूर्णांक md_setup_cluster(काष्ठा mddev *mddev, पूर्णांक nodes)
अणु
	पूर्णांक ret;
	अगर (!md_cluster_ops)
		request_module("md-cluster");
	spin_lock(&pers_lock);
	/* ensure module won't be unloaded */
	अगर (!md_cluster_ops || !try_module_get(md_cluster_mod)) अणु
		pr_warn("can't find md-cluster module or get it's reference.\n");
		spin_unlock(&pers_lock);
		वापस -ENOENT;
	पूर्ण
	spin_unlock(&pers_lock);

	ret = md_cluster_ops->join(mddev, nodes);
	अगर (!ret)
		mddev->safemode_delay = 0;
	वापस ret;
पूर्ण

व्योम md_cluster_stop(काष्ठा mddev *mddev)
अणु
	अगर (!md_cluster_ops)
		वापस;
	md_cluster_ops->leave(mddev);
	module_put(md_cluster_mod);
पूर्ण

अटल पूर्णांक is_mddev_idle(काष्ठा mddev *mddev, पूर्णांक init)
अणु
	काष्ठा md_rdev *rdev;
	पूर्णांक idle;
	पूर्णांक curr_events;

	idle = 1;
	rcu_पढ़ो_lock();
	rdev_क्रम_each_rcu(rdev, mddev) अणु
		काष्ठा gendisk *disk = rdev->bdev->bd_disk;
		curr_events = (पूर्णांक)part_stat_पढ़ो_accum(disk->part0, sectors) -
			      atomic_पढ़ो(&disk->sync_io);
		/* sync IO will cause sync_io to increase beक्रमe the disk_stats
		 * as sync_io is counted when a request starts, and
		 * disk_stats is counted when it completes.
		 * So resync activity will cause curr_events to be smaller than
		 * when there was no such activity.
		 * non-sync IO will cause disk_stat to increase without
		 * increasing sync_io so curr_events will (eventually)
		 * be larger than it was beक्रमe.  Once it becomes
		 * substantially larger, the test below will cause
		 * the array to appear non-idle, and resync will slow
		 * करोwn.
		 * If there is a lot of outstanding resync activity when
		 * we set last_event to curr_events, then all that activity
		 * completing might cause the array to appear non-idle
		 * and resync will be slowed करोwn even though there might
		 * not have been non-resync activity.  This will only
		 * happen once though.  'last_events' will soon reflect
		 * the state where there is little or no outstanding
		 * resync requests, and further resync activity will
		 * always make curr_events less than last_events.
		 *
		 */
		अगर (init || curr_events - rdev->last_events > 64) अणु
			rdev->last_events = curr_events;
			idle = 0;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस idle;
पूर्ण

व्योम md_करोne_sync(काष्ठा mddev *mddev, पूर्णांक blocks, पूर्णांक ok)
अणु
	/* another "blocks" (512byte) blocks have been synced */
	atomic_sub(blocks, &mddev->recovery_active);
	wake_up(&mddev->recovery_रुको);
	अगर (!ok) अणु
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
		set_bit(MD_RECOVERY_ERROR, &mddev->recovery);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		// stop recovery, संकेत करो_sync ....
	पूर्ण
पूर्ण
EXPORT_SYMBOL(md_करोne_sync);

/* md_ग_लिखो_start(mddev, bi)
 * If we need to update some array metadata (e.g. 'active' flag
 * in superblock) beक्रमe writing, schedule a superblock update
 * and रुको क्रम it to complete.
 * A वापस value of 'false' means that the write wasn't recorded
 * and cannot proceed as the array is being suspend.
 */
bool md_ग_लिखो_start(काष्ठा mddev *mddev, काष्ठा bio *bi)
अणु
	पूर्णांक did_change = 0;

	अगर (bio_data_dir(bi) != WRITE)
		वापस true;

	BUG_ON(mddev->ro == 1);
	अगर (mddev->ro == 2) अणु
		/* need to चयन to पढ़ो/ग_लिखो */
		mddev->ro = 0;
		set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		md_wakeup_thपढ़ो(mddev->sync_thपढ़ो);
		did_change = 1;
	पूर्ण
	rcu_पढ़ो_lock();
	percpu_ref_get(&mddev->ग_लिखोs_pending);
	smp_mb(); /* Match smp_mb in set_in_sync() */
	अगर (mddev->safemode == 1)
		mddev->safemode = 0;
	/* sync_checkers is always 0 when ग_लिखोs_pending is in per-cpu mode */
	अगर (mddev->in_sync || mddev->sync_checkers) अणु
		spin_lock(&mddev->lock);
		अगर (mddev->in_sync) अणु
			mddev->in_sync = 0;
			set_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags);
			set_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags);
			md_wakeup_thपढ़ो(mddev->thपढ़ो);
			did_change = 1;
		पूर्ण
		spin_unlock(&mddev->lock);
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (did_change)
		sysfs_notअगरy_dirent_safe(mddev->sysfs_state);
	अगर (!mddev->has_superblocks)
		वापस true;
	रुको_event(mddev->sb_रुको,
		   !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags) ||
		   mddev->suspended);
	अगर (test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags)) अणु
		percpu_ref_put(&mddev->ग_लिखोs_pending);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL(md_ग_लिखो_start);

/* md_ग_लिखो_inc can only be called when md_ग_लिखो_start() has
 * alपढ़ोy been called at least once of the current request.
 * It increments the counter and is useful when a single request
 * is split पूर्णांकo several parts.  Each part causes an increment and
 * so needs a matching md_ग_लिखो_end().
 * Unlike md_ग_लिखो_start(), it is safe to call md_ग_लिखो_inc() inside
 * a spinlocked region.
 */
व्योम md_ग_लिखो_inc(काष्ठा mddev *mddev, काष्ठा bio *bi)
अणु
	अगर (bio_data_dir(bi) != WRITE)
		वापस;
	WARN_ON_ONCE(mddev->in_sync || mddev->ro);
	percpu_ref_get(&mddev->ग_लिखोs_pending);
पूर्ण
EXPORT_SYMBOL(md_ग_लिखो_inc);

व्योम md_ग_लिखो_end(काष्ठा mddev *mddev)
अणु
	percpu_ref_put(&mddev->ग_लिखोs_pending);

	अगर (mddev->safemode == 2)
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
	अन्यथा अगर (mddev->safemode_delay)
		/* The roundup() ensures this only perक्रमms locking once
		 * every ->safemode_delay jअगरfies
		 */
		mod_समयr(&mddev->safemode_समयr,
			  roundup(jअगरfies, mddev->safemode_delay) +
			  mddev->safemode_delay);
पूर्ण

EXPORT_SYMBOL(md_ग_लिखो_end);

/* This is used by raid0 and raid10 */
व्योम md_submit_discard_bio(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev,
			काष्ठा bio *bio, sector_t start, sector_t size)
अणु
	काष्ठा bio *discard_bio = शून्य;

	अगर (__blkdev_issue_discard(rdev->bdev, start, size, GFP_NOIO, 0,
			&discard_bio) || !discard_bio)
		वापस;

	bio_chain(discard_bio, bio);
	bio_clone_blkg_association(discard_bio, bio);
	अगर (mddev->gendisk)
		trace_block_bio_remap(discard_bio,
				disk_devt(mddev->gendisk),
				bio->bi_iter.bi_sector);
	submit_bio_noacct(discard_bio);
पूर्ण
EXPORT_SYMBOL_GPL(md_submit_discard_bio);

/* md_allow_ग_लिखो(mddev)
 * Calling this ensures that the array is marked 'active' so that ग_लिखोs
 * may proceed without blocking.  It is important to call this beक्रमe
 * attempting a GFP_KERNEL allocation जबतक holding the mddev lock.
 * Must be called with mddev_lock held.
 */
व्योम md_allow_ग_लिखो(काष्ठा mddev *mddev)
अणु
	अगर (!mddev->pers)
		वापस;
	अगर (mddev->ro)
		वापस;
	अगर (!mddev->pers->sync_request)
		वापस;

	spin_lock(&mddev->lock);
	अगर (mddev->in_sync) अणु
		mddev->in_sync = 0;
		set_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags);
		set_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags);
		अगर (mddev->safemode_delay &&
		    mddev->safemode == 0)
			mddev->safemode = 1;
		spin_unlock(&mddev->lock);
		md_update_sb(mddev, 0);
		sysfs_notअगरy_dirent_safe(mddev->sysfs_state);
		/* रुको क्रम the dirty state to be recorded in the metadata */
		रुको_event(mddev->sb_रुको,
			   !test_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags));
	पूर्ण अन्यथा
		spin_unlock(&mddev->lock);
पूर्ण
EXPORT_SYMBOL_GPL(md_allow_ग_लिखो);

#घोषणा SYNC_MARKS	10
#घोषणा	SYNC_MARK_STEP	(3*HZ)
#घोषणा UPDATE_FREQUENCY (5*60*HZ)
व्योम md_करो_sync(काष्ठा md_thपढ़ो *thपढ़ो)
अणु
	काष्ठा mddev *mddev = thपढ़ो->mddev;
	काष्ठा mddev *mddev2;
	अचिन्हित पूर्णांक currspeed = 0, winकरोw;
	sector_t max_sectors,j, io_sectors, recovery_करोne;
	अचिन्हित दीर्घ mark[SYNC_MARKS];
	अचिन्हित दीर्घ update_समय;
	sector_t mark_cnt[SYNC_MARKS];
	पूर्णांक last_mark,m;
	काष्ठा list_head *पंचांगp;
	sector_t last_check;
	पूर्णांक skipped = 0;
	काष्ठा md_rdev *rdev;
	अक्षर *desc, *action = शून्य;
	काष्ठा blk_plug plug;
	पूर्णांक ret;

	/* just inहाल thपढ़ो restarts... */
	अगर (test_bit(MD_RECOVERY_DONE, &mddev->recovery) ||
	    test_bit(MD_RECOVERY_WAIT, &mddev->recovery))
		वापस;
	अगर (mddev->ro) अणु/* never try to sync a पढ़ो-only array */
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
		वापस;
	पूर्ण

	अगर (mddev_is_clustered(mddev)) अणु
		ret = md_cluster_ops->resync_start(mddev);
		अगर (ret)
			जाओ skip;

		set_bit(MD_CLUSTER_RESYNC_LOCKED, &mddev->flags);
		अगर (!(test_bit(MD_RECOVERY_SYNC, &mddev->recovery) ||
			test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) ||
			test_bit(MD_RECOVERY_RECOVER, &mddev->recovery))
		     && ((अचिन्हित दीर्घ दीर्घ)mddev->curr_resync_completed
			 < (अचिन्हित दीर्घ दीर्घ)mddev->resync_max_sectors))
			जाओ skip;
	पूर्ण

	अगर (test_bit(MD_RECOVERY_SYNC, &mddev->recovery)) अणु
		अगर (test_bit(MD_RECOVERY_CHECK, &mddev->recovery)) अणु
			desc = "data-check";
			action = "check";
		पूर्ण अन्यथा अगर (test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery)) अणु
			desc = "requested-resync";
			action = "repair";
		पूर्ण अन्यथा
			desc = "resync";
	पूर्ण अन्यथा अगर (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery))
		desc = "reshape";
	अन्यथा
		desc = "recovery";

	mddev->last_sync_action = action ?: desc;

	/* we overload curr_resync somewhat here.
	 * 0 == not engaged in resync at all
	 * 2 == checking that there is no conflict with another sync
	 * 1 == like 2, but have yielded to allow conflicting resync to
	 *		commence
	 * other == active in resync - this many blocks
	 *
	 * Beक्रमe starting a resync we must have set curr_resync to
	 * 2, and then checked that every "conflicting" array has curr_resync
	 * less than ours.  When we find one that is the same or higher
	 * we रुको on resync_रुको.  To aव्योम deadlock, we reduce curr_resync
	 * to 1 अगर we choose to yield (based arbitrarily on address of mddev काष्ठाure).
	 * This will mean we have to start checking from the beginning again.
	 *
	 */

	करो अणु
		पूर्णांक mddev2_minor = -1;
		mddev->curr_resync = 2;

	try_again:
		अगर (test_bit(MD_RECOVERY_INTR, &mddev->recovery))
			जाओ skip;
		क्रम_each_mddev(mddev2, पंचांगp) अणु
			अगर (mddev2 == mddev)
				जारी;
			अगर (!mddev->parallel_resync
			&&  mddev2->curr_resync
			&&  match_mddev_units(mddev, mddev2)) अणु
				DEFINE_WAIT(wq);
				अगर (mddev < mddev2 && mddev->curr_resync == 2) अणु
					/* arbitrarily yield */
					mddev->curr_resync = 1;
					wake_up(&resync_रुको);
				पूर्ण
				अगर (mddev > mddev2 && mddev->curr_resync == 1)
					/* no need to रुको here, we can रुको the next
					 * समय 'round when curr_resync == 2
					 */
					जारी;
				/* We need to रुको 'interruptible' so as not to
				 * contribute to the load average, and not to
				 * be caught by 'softlockup'
				 */
				prepare_to_रुको(&resync_रुको, &wq, TASK_INTERRUPTIBLE);
				अगर (!test_bit(MD_RECOVERY_INTR, &mddev->recovery) &&
				    mddev2->curr_resync >= mddev->curr_resync) अणु
					अगर (mddev2_minor != mddev2->md_minor) अणु
						mddev2_minor = mddev2->md_minor;
						pr_info("md: delaying %s of %s until %s has finished (they share one or more physical units)\n",
							desc, mdname(mddev),
							mdname(mddev2));
					पूर्ण
					mddev_put(mddev2);
					अगर (संकेत_pending(current))
						flush_संकेतs(current);
					schedule();
					finish_रुको(&resync_रुको, &wq);
					जाओ try_again;
				पूर्ण
				finish_रुको(&resync_रुको, &wq);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (mddev->curr_resync < 2);

	j = 0;
	अगर (test_bit(MD_RECOVERY_SYNC, &mddev->recovery)) अणु
		/* resync follows the size requested by the personality,
		 * which शेषs to physical size, but can be भव size
		 */
		max_sectors = mddev->resync_max_sectors;
		atomic64_set(&mddev->resync_mismatches, 0);
		/* we करोn't use the checkpoint if there's a biपंचांगap */
		अगर (test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery))
			j = mddev->resync_min;
		अन्यथा अगर (!mddev->biपंचांगap)
			j = mddev->recovery_cp;

	पूर्ण अन्यथा अगर (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery)) अणु
		max_sectors = mddev->resync_max_sectors;
		/*
		 * If the original node पातs reshaping then we जारी the
		 * reshaping, so set j again to aव्योम restart reshape from the
		 * first beginning
		 */
		अगर (mddev_is_clustered(mddev) &&
		    mddev->reshape_position != MaxSector)
			j = mddev->reshape_position;
	पूर्ण अन्यथा अणु
		/* recovery follows the physical size of devices */
		max_sectors = mddev->dev_sectors;
		j = MaxSector;
		rcu_पढ़ो_lock();
		rdev_क्रम_each_rcu(rdev, mddev)
			अगर (rdev->raid_disk >= 0 &&
			    !test_bit(Journal, &rdev->flags) &&
			    !test_bit(Faulty, &rdev->flags) &&
			    !test_bit(In_sync, &rdev->flags) &&
			    rdev->recovery_offset < j)
				j = rdev->recovery_offset;
		rcu_पढ़ो_unlock();

		/* If there is a biपंचांगap, we need to make sure all
		 * ग_लिखोs that started beक्रमe we added a spare
		 * complete beक्रमe we start करोing a recovery.
		 * Otherwise the ग_लिखो might complete and (via
		 * biपंचांगap_endग_लिखो) set a bit in the biपंचांगap after the
		 * recovery has checked that bit and skipped that
		 * region.
		 */
		अगर (mddev->biपंचांगap) अणु
			mddev->pers->quiesce(mddev, 1);
			mddev->pers->quiesce(mddev, 0);
		पूर्ण
	पूर्ण

	pr_info("md: %s of RAID array %s\n", desc, mdname(mddev));
	pr_debug("md: minimum _guaranteed_  speed: %d KB/sec/disk.\n", speed_min(mddev));
	pr_debug("md: using maximum available idle IO bandwidth (but not more than %d KB/sec) for %s.\n",
		 speed_max(mddev), desc);

	is_mddev_idle(mddev, 1); /* this initializes IO event counters */

	io_sectors = 0;
	क्रम (m = 0; m < SYNC_MARKS; m++) अणु
		mark[m] = jअगरfies;
		mark_cnt[m] = io_sectors;
	पूर्ण
	last_mark = 0;
	mddev->resync_mark = mark[last_mark];
	mddev->resync_mark_cnt = mark_cnt[last_mark];

	/*
	 * Tune reस्थिरruction:
	 */
	winकरोw = 32 * (PAGE_SIZE / 512);
	pr_debug("md: using %dk window, over a total of %lluk.\n",
		 winकरोw/2, (अचिन्हित दीर्घ दीर्घ)max_sectors/2);

	atomic_set(&mddev->recovery_active, 0);
	last_check = 0;

	अगर (j>2) अणु
		pr_debug("md: resuming %s of %s from checkpoint.\n",
			 desc, mdname(mddev));
		mddev->curr_resync = j;
	पूर्ण अन्यथा
		mddev->curr_resync = 3; /* no दीर्घer delayed */
	mddev->curr_resync_completed = j;
	sysfs_notअगरy_dirent_safe(mddev->sysfs_completed);
	md_new_event(mddev);
	update_समय = jअगरfies;

	blk_start_plug(&plug);
	जबतक (j < max_sectors) अणु
		sector_t sectors;

		skipped = 0;

		अगर (!test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
		    ((mddev->curr_resync > mddev->curr_resync_completed &&
		      (mddev->curr_resync - mddev->curr_resync_completed)
		      > (max_sectors >> 4)) ||
		     समय_after_eq(jअगरfies, update_समय + UPDATE_FREQUENCY) ||
		     (j - mddev->curr_resync_completed)*2
		     >= mddev->resync_max - mddev->curr_resync_completed ||
		     mddev->curr_resync_completed > mddev->resync_max
			    )) अणु
			/* समय to update curr_resync_completed */
			रुको_event(mddev->recovery_रुको,
				   atomic_पढ़ो(&mddev->recovery_active) == 0);
			mddev->curr_resync_completed = j;
			अगर (test_bit(MD_RECOVERY_SYNC, &mddev->recovery) &&
			    j > mddev->recovery_cp)
				mddev->recovery_cp = j;
			update_समय = jअगरfies;
			set_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags);
			sysfs_notअगरy_dirent_safe(mddev->sysfs_completed);
		पूर्ण

		जबतक (j >= mddev->resync_max &&
		       !test_bit(MD_RECOVERY_INTR, &mddev->recovery)) अणु
			/* As this condition is controlled by user-space,
			 * we can block indefinitely, so use '_interruptible'
			 * to aव्योम triggering warnings.
			 */
			flush_संकेतs(current); /* just in हाल */
			रुको_event_पूर्णांकerruptible(mddev->recovery_रुको,
						 mddev->resync_max > j
						 || test_bit(MD_RECOVERY_INTR,
							     &mddev->recovery));
		पूर्ण

		अगर (test_bit(MD_RECOVERY_INTR, &mddev->recovery))
			अवरोध;

		sectors = mddev->pers->sync_request(mddev, j, &skipped);
		अगर (sectors == 0) अणु
			set_bit(MD_RECOVERY_INTR, &mddev->recovery);
			अवरोध;
		पूर्ण

		अगर (!skipped) अणु /* actual IO requested */
			io_sectors += sectors;
			atomic_add(sectors, &mddev->recovery_active);
		पूर्ण

		अगर (test_bit(MD_RECOVERY_INTR, &mddev->recovery))
			अवरोध;

		j += sectors;
		अगर (j > max_sectors)
			/* when skipping, extra large numbers can be वापसed. */
			j = max_sectors;
		अगर (j > 2)
			mddev->curr_resync = j;
		mddev->curr_mark_cnt = io_sectors;
		अगर (last_check == 0)
			/* this is the earliest that rebuild will be
			 * visible in /proc/mdstat
			 */
			md_new_event(mddev);

		अगर (last_check + winकरोw > io_sectors || j == max_sectors)
			जारी;

		last_check = io_sectors;
	repeat:
		अगर (समय_after_eq(jअगरfies, mark[last_mark] + SYNC_MARK_STEP )) अणु
			/* step marks */
			पूर्णांक next = (last_mark+1) % SYNC_MARKS;

			mddev->resync_mark = mark[next];
			mddev->resync_mark_cnt = mark_cnt[next];
			mark[next] = jअगरfies;
			mark_cnt[next] = io_sectors - atomic_पढ़ो(&mddev->recovery_active);
			last_mark = next;
		पूर्ण

		अगर (test_bit(MD_RECOVERY_INTR, &mddev->recovery))
			अवरोध;

		/*
		 * this loop निकासs only अगर either when we are slower than
		 * the 'hard' speed limit, or the प्रणाली was IO-idle क्रम
		 * a jअगरfy.
		 * the प्रणाली might be non-idle CPU-wise, but we only care
		 * about not overloading the IO subप्रणाली. (things like an
		 * e2fsck being करोne on the RAID array should execute fast)
		 */
		cond_resched();

		recovery_करोne = io_sectors - atomic_पढ़ो(&mddev->recovery_active);
		currspeed = ((अचिन्हित दीर्घ)(recovery_करोne - mddev->resync_mark_cnt))/2
			/((jअगरfies-mddev->resync_mark)/HZ +1) +1;

		अगर (currspeed > speed_min(mddev)) अणु
			अगर (currspeed > speed_max(mddev)) अणु
				msleep(500);
				जाओ repeat;
			पूर्ण
			अगर (!is_mddev_idle(mddev, 0)) अणु
				/*
				 * Give other IO more of a chance.
				 * The faster the devices, the less we रुको.
				 */
				रुको_event(mddev->recovery_रुको,
					   !atomic_पढ़ो(&mddev->recovery_active));
			पूर्ण
		पूर्ण
	पूर्ण
	pr_info("md: %s: %s %s.\n",mdname(mddev), desc,
		test_bit(MD_RECOVERY_INTR, &mddev->recovery)
		? "interrupted" : "done");
	/*
	 * this also संकेतs 'finished resyncing' to md_stop
	 */
	blk_finish_plug(&plug);
	रुको_event(mddev->recovery_रुको, !atomic_पढ़ो(&mddev->recovery_active));

	अगर (!test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
	    !test_bit(MD_RECOVERY_INTR, &mddev->recovery) &&
	    mddev->curr_resync > 3) अणु
		mddev->curr_resync_completed = mddev->curr_resync;
		sysfs_notअगरy_dirent_safe(mddev->sysfs_completed);
	पूर्ण
	mddev->pers->sync_request(mddev, max_sectors, &skipped);

	अगर (!test_bit(MD_RECOVERY_CHECK, &mddev->recovery) &&
	    mddev->curr_resync > 3) अणु
		अगर (test_bit(MD_RECOVERY_SYNC, &mddev->recovery)) अणु
			अगर (test_bit(MD_RECOVERY_INTR, &mddev->recovery)) अणु
				अगर (mddev->curr_resync >= mddev->recovery_cp) अणु
					pr_debug("md: checkpointing %s of %s.\n",
						 desc, mdname(mddev));
					अगर (test_bit(MD_RECOVERY_ERROR,
						&mddev->recovery))
						mddev->recovery_cp =
							mddev->curr_resync_completed;
					अन्यथा
						mddev->recovery_cp =
							mddev->curr_resync;
				पूर्ण
			पूर्ण अन्यथा
				mddev->recovery_cp = MaxSector;
		पूर्ण अन्यथा अणु
			अगर (!test_bit(MD_RECOVERY_INTR, &mddev->recovery))
				mddev->curr_resync = MaxSector;
			अगर (!test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
			    test_bit(MD_RECOVERY_RECOVER, &mddev->recovery)) अणु
				rcu_पढ़ो_lock();
				rdev_क्रम_each_rcu(rdev, mddev)
					अगर (rdev->raid_disk >= 0 &&
					    mddev->delta_disks >= 0 &&
					    !test_bit(Journal, &rdev->flags) &&
					    !test_bit(Faulty, &rdev->flags) &&
					    !test_bit(In_sync, &rdev->flags) &&
					    rdev->recovery_offset < mddev->curr_resync)
						rdev->recovery_offset = mddev->curr_resync;
				rcu_पढ़ो_unlock();
			पूर्ण
		पूर्ण
	पूर्ण
 skip:
	/* set CHANGE_PENDING here since maybe another update is needed,
	 * so other nodes are inक्रमmed. It should be harmless क्रम normal
	 * raid */
	set_mask_bits(&mddev->sb_flags, 0,
		      BIT(MD_SB_CHANGE_PENDING) | BIT(MD_SB_CHANGE_DEVS));

	अगर (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
			!test_bit(MD_RECOVERY_INTR, &mddev->recovery) &&
			mddev->delta_disks > 0 &&
			mddev->pers->finish_reshape &&
			mddev->pers->size &&
			mddev->queue) अणु
		mddev_lock_noपूर्णांकr(mddev);
		md_set_array_sectors(mddev, mddev->pers->size(mddev, 0, 0));
		mddev_unlock(mddev);
		अगर (!mddev_is_clustered(mddev))
			set_capacity_and_notअगरy(mddev->gendisk,
						mddev->array_sectors);
	पूर्ण

	spin_lock(&mddev->lock);
	अगर (!test_bit(MD_RECOVERY_INTR, &mddev->recovery)) अणु
		/* We completed so min/max setting can be क्रमgotten अगर used. */
		अगर (test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery))
			mddev->resync_min = 0;
		mddev->resync_max = MaxSector;
	पूर्ण अन्यथा अगर (test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery))
		mddev->resync_min = mddev->curr_resync_completed;
	set_bit(MD_RECOVERY_DONE, &mddev->recovery);
	mddev->curr_resync = 0;
	spin_unlock(&mddev->lock);

	wake_up(&resync_रुको);
	md_wakeup_thपढ़ो(mddev->thपढ़ो);
	वापस;
पूर्ण
EXPORT_SYMBOL_GPL(md_करो_sync);

अटल पूर्णांक हटाओ_and_add_spares(काष्ठा mddev *mddev,
				 काष्ठा md_rdev *this)
अणु
	काष्ठा md_rdev *rdev;
	पूर्णांक spares = 0;
	पूर्णांक हटाओd = 0;
	bool हटाओ_some = false;

	अगर (this && test_bit(MD_RECOVERY_RUNNING, &mddev->recovery))
		/* Mustn't हटाओ devices when resync thपढ़ो is running */
		वापस 0;

	rdev_क्रम_each(rdev, mddev) अणु
		अगर ((this == शून्य || rdev == this) &&
		    rdev->raid_disk >= 0 &&
		    !test_bit(Blocked, &rdev->flags) &&
		    test_bit(Faulty, &rdev->flags) &&
		    atomic_पढ़ो(&rdev->nr_pending)==0) अणु
			/* Faulty non-Blocked devices with nr_pending == 0
			 * never get nr_pending incremented,
			 * never get Faulty cleared, and never get Blocked set.
			 * So we can synchronize_rcu now rather than once per device
			 */
			हटाओ_some = true;
			set_bit(RemoveSynchronized, &rdev->flags);
		पूर्ण
	पूर्ण

	अगर (हटाओ_some)
		synchronize_rcu();
	rdev_क्रम_each(rdev, mddev) अणु
		अगर ((this == शून्य || rdev == this) &&
		    rdev->raid_disk >= 0 &&
		    !test_bit(Blocked, &rdev->flags) &&
		    ((test_bit(RemoveSynchronized, &rdev->flags) ||
		     (!test_bit(In_sync, &rdev->flags) &&
		      !test_bit(Journal, &rdev->flags))) &&
		    atomic_पढ़ो(&rdev->nr_pending)==0)) अणु
			अगर (mddev->pers->hot_हटाओ_disk(
				    mddev, rdev) == 0) अणु
				sysfs_unlink_rdev(mddev, rdev);
				rdev->saved_raid_disk = rdev->raid_disk;
				rdev->raid_disk = -1;
				हटाओd++;
			पूर्ण
		पूर्ण
		अगर (हटाओ_some && test_bit(RemoveSynchronized, &rdev->flags))
			clear_bit(RemoveSynchronized, &rdev->flags);
	पूर्ण

	अगर (हटाओd && mddev->kobj.sd)
		sysfs_notअगरy_dirent_safe(mddev->sysfs_degraded);

	अगर (this && हटाओd)
		जाओ no_add;

	rdev_क्रम_each(rdev, mddev) अणु
		अगर (this && this != rdev)
			जारी;
		अगर (test_bit(Candidate, &rdev->flags))
			जारी;
		अगर (rdev->raid_disk >= 0 &&
		    !test_bit(In_sync, &rdev->flags) &&
		    !test_bit(Journal, &rdev->flags) &&
		    !test_bit(Faulty, &rdev->flags))
			spares++;
		अगर (rdev->raid_disk >= 0)
			जारी;
		अगर (test_bit(Faulty, &rdev->flags))
			जारी;
		अगर (!test_bit(Journal, &rdev->flags)) अणु
			अगर (mddev->ro &&
			    ! (rdev->saved_raid_disk >= 0 &&
			       !test_bit(Biपंचांगap_sync, &rdev->flags)))
				जारी;

			rdev->recovery_offset = 0;
		पूर्ण
		अगर (mddev->pers->hot_add_disk(mddev, rdev) == 0) अणु
			/* failure here is OK */
			sysfs_link_rdev(mddev, rdev);
			अगर (!test_bit(Journal, &rdev->flags))
				spares++;
			md_new_event(mddev);
			set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
		पूर्ण
	पूर्ण
no_add:
	अगर (हटाओd)
		set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
	वापस spares;
पूर्ण

अटल व्योम md_start_sync(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा mddev *mddev = container_of(ws, काष्ठा mddev, del_work);

	mddev->sync_thपढ़ो = md_रेजिस्टर_thपढ़ो(md_करो_sync,
						mddev,
						"resync");
	अगर (!mddev->sync_thपढ़ो) अणु
		pr_warn("%s: could not start resync thread...\n",
			mdname(mddev));
		/* leave the spares where they are, it shouldn't hurt */
		clear_bit(MD_RECOVERY_SYNC, &mddev->recovery);
		clear_bit(MD_RECOVERY_RESHAPE, &mddev->recovery);
		clear_bit(MD_RECOVERY_REQUESTED, &mddev->recovery);
		clear_bit(MD_RECOVERY_CHECK, &mddev->recovery);
		clear_bit(MD_RECOVERY_RUNNING, &mddev->recovery);
		wake_up(&resync_रुको);
		अगर (test_and_clear_bit(MD_RECOVERY_RECOVER,
				       &mddev->recovery))
			अगर (mddev->sysfs_action)
				sysfs_notअगरy_dirent_safe(mddev->sysfs_action);
	पूर्ण अन्यथा
		md_wakeup_thपढ़ो(mddev->sync_thपढ़ो);
	sysfs_notअगरy_dirent_safe(mddev->sysfs_action);
	md_new_event(mddev);
पूर्ण

/*
 * This routine is regularly called by all per-raid-array thपढ़ोs to
 * deal with generic issues like resync and super-block update.
 * Raid personalities that करोn't have a thपढ़ो (linear/raid0) करो not
 * need this as they never करो any recovery or update the superblock.
 *
 * It करोes not करो any resync itself, but rather "forks" off other thपढ़ोs
 * to करो that as needed.
 * When it is determined that resync is needed, we set MD_RECOVERY_RUNNING in
 * "->recovery" and create a thपढ़ो at ->sync_thपढ़ो.
 * When the thपढ़ो finishes it sets MD_RECOVERY_DONE
 * and wakeups up this thपढ़ो which will reap the thपढ़ो and finish up.
 * This thपढ़ो also हटाओs any faulty devices (with nr_pending == 0).
 *
 * The overall approach is:
 *  1/ अगर the superblock needs updating, update it.
 *  2/ If a recovery thपढ़ो is running, करोn't करो anything अन्यथा.
 *  3/ If recovery has finished, clean up, possibly marking spares active.
 *  4/ If there are any faulty devices, हटाओ them.
 *  5/ If array is degraded, try to add spares devices
 *  6/ If array has spares or is not in-sync, start a resync thपढ़ो.
 */
व्योम md_check_recovery(काष्ठा mddev *mddev)
अणु
	अगर (test_bit(MD_ALLOW_SB_UPDATE, &mddev->flags) && mddev->sb_flags) अणु
		/* Write superblock - thपढ़ो that called mddev_suspend()
		 * holds reconfig_mutex क्रम us.
		 */
		set_bit(MD_UPDATING_SB, &mddev->flags);
		smp_mb__after_atomic();
		अगर (test_bit(MD_ALLOW_SB_UPDATE, &mddev->flags))
			md_update_sb(mddev, 0);
		clear_bit_unlock(MD_UPDATING_SB, &mddev->flags);
		wake_up(&mddev->sb_रुको);
	पूर्ण

	अगर (mddev->suspended)
		वापस;

	अगर (mddev->biपंचांगap)
		md_biपंचांगap_daemon_work(mddev);

	अगर (संकेत_pending(current)) अणु
		अगर (mddev->pers->sync_request && !mddev->बाह्यal) अणु
			pr_debug("md: %s in immediate safe mode\n",
				 mdname(mddev));
			mddev->safemode = 2;
		पूर्ण
		flush_संकेतs(current);
	पूर्ण

	अगर (mddev->ro && !test_bit(MD_RECOVERY_NEEDED, &mddev->recovery))
		वापस;
	अगर ( ! (
		(mddev->sb_flags & ~ (1<<MD_SB_CHANGE_PENDING)) ||
		test_bit(MD_RECOVERY_NEEDED, &mddev->recovery) ||
		test_bit(MD_RECOVERY_DONE, &mddev->recovery) ||
		(mddev->बाह्यal == 0 && mddev->safemode == 1) ||
		(mddev->safemode == 2
		 && !mddev->in_sync && mddev->recovery_cp == MaxSector)
		))
		वापस;

	अगर (mddev_trylock(mddev)) अणु
		पूर्णांक spares = 0;
		bool try_set_sync = mddev->safemode != 0;

		अगर (!mddev->बाह्यal && mddev->safemode == 1)
			mddev->safemode = 0;

		अगर (mddev->ro) अणु
			काष्ठा md_rdev *rdev;
			अगर (!mddev->बाह्यal && mddev->in_sync)
				/* 'Blocked' flag not needed as failed devices
				 * will be recorded अगर array चयनed to पढ़ो/ग_लिखो.
				 * Leaving it set will prevent the device
				 * from being हटाओd.
				 */
				rdev_क्रम_each(rdev, mddev)
					clear_bit(Blocked, &rdev->flags);
			/* On a पढ़ो-only array we can:
			 * - हटाओ failed devices
			 * - add alपढ़ोy-in_sync devices अगर the array itself
			 *   is in-sync.
			 * As we only add devices that are alपढ़ोy in-sync,
			 * we can activate the spares immediately.
			 */
			हटाओ_and_add_spares(mddev, शून्य);
			/* There is no thपढ़ो, but we need to call
			 * ->spare_active and clear saved_raid_disk
			 */
			set_bit(MD_RECOVERY_INTR, &mddev->recovery);
			md_reap_sync_thपढ़ो(mddev);
			clear_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
			clear_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
			clear_bit(MD_SB_CHANGE_PENDING, &mddev->sb_flags);
			जाओ unlock;
		पूर्ण

		अगर (mddev_is_clustered(mddev)) अणु
			काष्ठा md_rdev *rdev, *पंचांगp;
			/* kick the device अगर another node issued a
			 * हटाओ disk.
			 */
			rdev_क्रम_each_safe(rdev, पंचांगp, mddev) अणु
				अगर (test_and_clear_bit(ClusterRemove, &rdev->flags) &&
						rdev->raid_disk < 0)
					md_kick_rdev_from_array(rdev);
			पूर्ण
		पूर्ण

		अगर (try_set_sync && !mddev->बाह्यal && !mddev->in_sync) अणु
			spin_lock(&mddev->lock);
			set_in_sync(mddev);
			spin_unlock(&mddev->lock);
		पूर्ण

		अगर (mddev->sb_flags)
			md_update_sb(mddev, 0);

		अगर (test_bit(MD_RECOVERY_RUNNING, &mddev->recovery) &&
		    !test_bit(MD_RECOVERY_DONE, &mddev->recovery)) अणु
			/* resync/recovery still happening */
			clear_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
			जाओ unlock;
		पूर्ण
		अगर (mddev->sync_thपढ़ो) अणु
			md_reap_sync_thपढ़ो(mddev);
			जाओ unlock;
		पूर्ण
		/* Set RUNNING beक्रमe clearing NEEDED to aव्योम
		 * any transients in the value of "sync_action".
		 */
		mddev->curr_resync_completed = 0;
		spin_lock(&mddev->lock);
		set_bit(MD_RECOVERY_RUNNING, &mddev->recovery);
		spin_unlock(&mddev->lock);
		/* Clear some bits that करोn't mean anything, but
		 * might be left set
		 */
		clear_bit(MD_RECOVERY_INTR, &mddev->recovery);
		clear_bit(MD_RECOVERY_DONE, &mddev->recovery);

		अगर (!test_and_clear_bit(MD_RECOVERY_NEEDED, &mddev->recovery) ||
		    test_bit(MD_RECOVERY_FROZEN, &mddev->recovery))
			जाओ not_running;
		/* no recovery is running.
		 * हटाओ any failed drives, then
		 * add spares अगर possible.
		 * Spares are also हटाओd and re-added, to allow
		 * the personality to fail the re-add.
		 */

		अगर (mddev->reshape_position != MaxSector) अणु
			अगर (mddev->pers->check_reshape == शून्य ||
			    mddev->pers->check_reshape(mddev) != 0)
				/* Cannot proceed */
				जाओ not_running;
			set_bit(MD_RECOVERY_RESHAPE, &mddev->recovery);
			clear_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
		पूर्ण अन्यथा अगर ((spares = हटाओ_and_add_spares(mddev, शून्य))) अणु
			clear_bit(MD_RECOVERY_SYNC, &mddev->recovery);
			clear_bit(MD_RECOVERY_CHECK, &mddev->recovery);
			clear_bit(MD_RECOVERY_REQUESTED, &mddev->recovery);
			set_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
		पूर्ण अन्यथा अगर (mddev->recovery_cp < MaxSector) अणु
			set_bit(MD_RECOVERY_SYNC, &mddev->recovery);
			clear_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
		पूर्ण अन्यथा अगर (!test_bit(MD_RECOVERY_SYNC, &mddev->recovery))
			/* nothing to be करोne ... */
			जाओ not_running;

		अगर (mddev->pers->sync_request) अणु
			अगर (spares) अणु
				/* We are adding a device or devices to an array
				 * which has the biपंचांगap stored on all devices.
				 * So make sure all biपंचांगap pages get written
				 */
				md_biपंचांगap_ग_लिखो_all(mddev->biपंचांगap);
			पूर्ण
			INIT_WORK(&mddev->del_work, md_start_sync);
			queue_work(md_misc_wq, &mddev->del_work);
			जाओ unlock;
		पूर्ण
	not_running:
		अगर (!mddev->sync_thपढ़ो) अणु
			clear_bit(MD_RECOVERY_RUNNING, &mddev->recovery);
			wake_up(&resync_रुको);
			अगर (test_and_clear_bit(MD_RECOVERY_RECOVER,
					       &mddev->recovery))
				अगर (mddev->sysfs_action)
					sysfs_notअगरy_dirent_safe(mddev->sysfs_action);
		पूर्ण
	unlock:
		wake_up(&mddev->sb_रुको);
		mddev_unlock(mddev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(md_check_recovery);

व्योम md_reap_sync_thपढ़ो(काष्ठा mddev *mddev)
अणु
	काष्ठा md_rdev *rdev;
	sector_t old_dev_sectors = mddev->dev_sectors;
	bool is_reshaped = false;

	/* resync has finished, collect result */
	md_unरेजिस्टर_thपढ़ो(&mddev->sync_thपढ़ो);
	अगर (!test_bit(MD_RECOVERY_INTR, &mddev->recovery) &&
	    !test_bit(MD_RECOVERY_REQUESTED, &mddev->recovery) &&
	    mddev->degraded != mddev->raid_disks) अणु
		/* success...*/
		/* activate any spares */
		अगर (mddev->pers->spare_active(mddev)) अणु
			sysfs_notअगरy_dirent_safe(mddev->sysfs_degraded);
			set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
		पूर्ण
	पूर्ण
	अगर (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
	    mddev->pers->finish_reshape) अणु
		mddev->pers->finish_reshape(mddev);
		अगर (mddev_is_clustered(mddev))
			is_reshaped = true;
	पूर्ण

	/* If array is no-दीर्घer degraded, then any saved_raid_disk
	 * inक्रमmation must be scrapped.
	 */
	अगर (!mddev->degraded)
		rdev_क्रम_each(rdev, mddev)
			rdev->saved_raid_disk = -1;

	md_update_sb(mddev, 1);
	/* MD_SB_CHANGE_PENDING should be cleared by md_update_sb, so we can
	 * call resync_finish here अगर MD_CLUSTER_RESYNC_LOCKED is set by
	 * clustered raid */
	अगर (test_and_clear_bit(MD_CLUSTER_RESYNC_LOCKED, &mddev->flags))
		md_cluster_ops->resync_finish(mddev);
	clear_bit(MD_RECOVERY_RUNNING, &mddev->recovery);
	clear_bit(MD_RECOVERY_DONE, &mddev->recovery);
	clear_bit(MD_RECOVERY_SYNC, &mddev->recovery);
	clear_bit(MD_RECOVERY_RESHAPE, &mddev->recovery);
	clear_bit(MD_RECOVERY_REQUESTED, &mddev->recovery);
	clear_bit(MD_RECOVERY_CHECK, &mddev->recovery);
	/*
	 * We call md_cluster_ops->update_size here because sync_size could
	 * be changed by md_update_sb, and MD_RECOVERY_RESHAPE is cleared,
	 * so it is समय to update size across cluster.
	 */
	अगर (mddev_is_clustered(mddev) && is_reshaped
				      && !test_bit(MD_CLOSING, &mddev->flags))
		md_cluster_ops->update_size(mddev, old_dev_sectors);
	wake_up(&resync_रुको);
	/* flag recovery needed just to द्विगुन check */
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	sysfs_notअगरy_dirent_safe(mddev->sysfs_action);
	md_new_event(mddev);
	अगर (mddev->event_work.func)
		queue_work(md_misc_wq, &mddev->event_work);
पूर्ण
EXPORT_SYMBOL(md_reap_sync_thपढ़ो);

व्योम md_रुको_क्रम_blocked_rdev(काष्ठा md_rdev *rdev, काष्ठा mddev *mddev)
अणु
	sysfs_notअगरy_dirent_safe(rdev->sysfs_state);
	रुको_event_समयout(rdev->blocked_रुको,
			   !test_bit(Blocked, &rdev->flags) &&
			   !test_bit(BlockedBadBlocks, &rdev->flags),
			   msecs_to_jअगरfies(5000));
	rdev_dec_pending(rdev, mddev);
पूर्ण
EXPORT_SYMBOL(md_रुको_क्रम_blocked_rdev);

व्योम md_finish_reshape(काष्ठा mddev *mddev)
अणु
	/* called be personality module when reshape completes. */
	काष्ठा md_rdev *rdev;

	rdev_क्रम_each(rdev, mddev) अणु
		अगर (rdev->data_offset > rdev->new_data_offset)
			rdev->sectors += rdev->data_offset - rdev->new_data_offset;
		अन्यथा
			rdev->sectors -= rdev->new_data_offset - rdev->data_offset;
		rdev->data_offset = rdev->new_data_offset;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(md_finish_reshape);

/* Bad block management */

/* Returns 1 on success, 0 on failure */
पूर्णांक rdev_set_badblocks(काष्ठा md_rdev *rdev, sector_t s, पूर्णांक sectors,
		       पूर्णांक is_new)
अणु
	काष्ठा mddev *mddev = rdev->mddev;
	पूर्णांक rv;
	अगर (is_new)
		s += rdev->new_data_offset;
	अन्यथा
		s += rdev->data_offset;
	rv = badblocks_set(&rdev->badblocks, s, sectors, 0);
	अगर (rv == 0) अणु
		/* Make sure they get written out promptly */
		अगर (test_bit(ExternalBbl, &rdev->flags))
			sysfs_notअगरy_dirent_safe(rdev->sysfs_unack_badblocks);
		sysfs_notअगरy_dirent_safe(rdev->sysfs_state);
		set_mask_bits(&mddev->sb_flags, 0,
			      BIT(MD_SB_CHANGE_CLEAN) | BIT(MD_SB_CHANGE_PENDING));
		md_wakeup_thपढ़ो(rdev->mddev->thपढ़ो);
		वापस 1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rdev_set_badblocks);

पूर्णांक rdev_clear_badblocks(काष्ठा md_rdev *rdev, sector_t s, पूर्णांक sectors,
			 पूर्णांक is_new)
अणु
	पूर्णांक rv;
	अगर (is_new)
		s += rdev->new_data_offset;
	अन्यथा
		s += rdev->data_offset;
	rv = badblocks_clear(&rdev->badblocks, s, sectors);
	अगर ((rv == 0) && test_bit(ExternalBbl, &rdev->flags))
		sysfs_notअगरy_dirent_safe(rdev->sysfs_badblocks);
	वापस rv;
पूर्ण
EXPORT_SYMBOL_GPL(rdev_clear_badblocks);

अटल पूर्णांक md_notअगरy_reboot(काष्ठा notअगरier_block *this,
			    अचिन्हित दीर्घ code, व्योम *x)
अणु
	काष्ठा list_head *पंचांगp;
	काष्ठा mddev *mddev;
	पूर्णांक need_delay = 0;

	क्रम_each_mddev(mddev, पंचांगp) अणु
		अगर (mddev_trylock(mddev)) अणु
			अगर (mddev->pers)
				__md_stop_ग_लिखोs(mddev);
			अगर (mddev->persistent)
				mddev->safemode = 2;
			mddev_unlock(mddev);
		पूर्ण
		need_delay = 1;
	पूर्ण
	/*
	 * certain more exotic SCSI devices are known to be
	 * अस्थिर wrt too early प्रणाली reboots. While the
	 * right place to handle this issue is the given
	 * driver, we करो want to have a safe RAID driver ...
	 */
	अगर (need_delay)
		mdelay(1000*1);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block md_notअगरier = अणु
	.notअगरier_call	= md_notअगरy_reboot,
	.next		= शून्य,
	.priority	= पूर्णांक_उच्च, /* beक्रमe any real devices */
पूर्ण;

अटल व्योम md_geninit(व्योम)
अणु
	pr_debug("md: sizeof(mdp_super_t) = %d\n", (पूर्णांक)माप(mdp_super_t));

	proc_create("mdstat", S_IRUGO, शून्य, &mdstat_proc_ops);
पूर्ण

अटल पूर्णांक __init md_init(व्योम)
अणु
	पूर्णांक ret = -ENOMEM;

	md_wq = alloc_workqueue("md", WQ_MEM_RECLAIM, 0);
	अगर (!md_wq)
		जाओ err_wq;

	md_misc_wq = alloc_workqueue("md_misc", 0, 0);
	अगर (!md_misc_wq)
		जाओ err_misc_wq;

	md_rdev_misc_wq = alloc_workqueue("md_rdev_misc", 0, 0);
	अगर (!md_rdev_misc_wq)
		जाओ err_rdev_misc_wq;

	ret = __रेजिस्टर_blkdev(MD_MAJOR, "md", md_probe);
	अगर (ret < 0)
		जाओ err_md;

	ret = __रेजिस्टर_blkdev(0, "mdp", md_probe);
	अगर (ret < 0)
		जाओ err_mdp;
	mdp_major = ret;

	रेजिस्टर_reboot_notअगरier(&md_notअगरier);
	raid_table_header = रेजिस्टर_sysctl_table(raid_root_table);

	md_geninit();
	वापस 0;

err_mdp:
	unरेजिस्टर_blkdev(MD_MAJOR, "md");
err_md:
	destroy_workqueue(md_rdev_misc_wq);
err_rdev_misc_wq:
	destroy_workqueue(md_misc_wq);
err_misc_wq:
	destroy_workqueue(md_wq);
err_wq:
	वापस ret;
पूर्ण

अटल व्योम check_sb_changes(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा mdp_superblock_1 *sb = page_address(rdev->sb_page);
	काष्ठा md_rdev *rdev2, *पंचांगp;
	पूर्णांक role, ret;
	अक्षर b[BDEVNAME_SIZE];

	/*
	 * If size is changed in another node then we need to
	 * करो resize as well.
	 */
	अगर (mddev->dev_sectors != le64_to_cpu(sb->size)) अणु
		ret = mddev->pers->resize(mddev, le64_to_cpu(sb->size));
		अगर (ret)
			pr_info("md-cluster: resize failed\n");
		अन्यथा
			md_biपंचांगap_update_sb(mddev->biपंचांगap);
	पूर्ण

	/* Check क्रम change of roles in the active devices */
	rdev_क्रम_each_safe(rdev2, पंचांगp, mddev) अणु
		अगर (test_bit(Faulty, &rdev2->flags))
			जारी;

		/* Check अगर the roles changed */
		role = le16_to_cpu(sb->dev_roles[rdev2->desc_nr]);

		अगर (test_bit(Candidate, &rdev2->flags)) अणु
			अगर (role == 0xfffe) अणु
				pr_info("md: Removing Candidate device %s because add failed\n", bdevname(rdev2->bdev,b));
				md_kick_rdev_from_array(rdev2);
				जारी;
			पूर्ण
			अन्यथा
				clear_bit(Candidate, &rdev2->flags);
		पूर्ण

		अगर (role != rdev2->raid_disk) अणु
			/*
			 * got activated except reshape is happening.
			 */
			अगर (rdev2->raid_disk == -1 && role != 0xffff &&
			    !(le32_to_cpu(sb->feature_map) &
			      MD_FEATURE_RESHAPE_ACTIVE)) अणु
				rdev2->saved_raid_disk = role;
				ret = हटाओ_and_add_spares(mddev, rdev2);
				pr_info("Activated spare: %s\n",
					bdevname(rdev2->bdev,b));
				/* wakeup mddev->thपढ़ो here, so array could
				 * perक्रमm resync with the new activated disk */
				set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
				md_wakeup_thपढ़ो(mddev->thपढ़ो);
			पूर्ण
			/* device faulty
			 * We just want to करो the minimum to mark the disk
			 * as faulty. The recovery is perक्रमmed by the
			 * one who initiated the error.
			 */
			अगर ((role == 0xfffe) || (role == 0xfffd)) अणु
				md_error(mddev, rdev2);
				clear_bit(Blocked, &rdev2->flags);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (mddev->raid_disks != le32_to_cpu(sb->raid_disks)) अणु
		ret = update_raid_disks(mddev, le32_to_cpu(sb->raid_disks));
		अगर (ret)
			pr_warn("md: updating array disks failed. %d\n", ret);
	पूर्ण

	/*
	 * Since mddev->delta_disks has alपढ़ोy updated in update_raid_disks,
	 * so it is समय to check reshape.
	 */
	अगर (test_bit(MD_RESYNCING_REMOTE, &mddev->recovery) &&
	    (le32_to_cpu(sb->feature_map) & MD_FEATURE_RESHAPE_ACTIVE)) अणु
		/*
		 * reshape is happening in the remote node, we need to
		 * update reshape_position and call start_reshape.
		 */
		mddev->reshape_position = le64_to_cpu(sb->reshape_position);
		अगर (mddev->pers->update_reshape_pos)
			mddev->pers->update_reshape_pos(mddev);
		अगर (mddev->pers->start_reshape)
			mddev->pers->start_reshape(mddev);
	पूर्ण अन्यथा अगर (test_bit(MD_RESYNCING_REMOTE, &mddev->recovery) &&
		   mddev->reshape_position != MaxSector &&
		   !(le32_to_cpu(sb->feature_map) & MD_FEATURE_RESHAPE_ACTIVE)) अणु
		/* reshape is just करोne in another node. */
		mddev->reshape_position = MaxSector;
		अगर (mddev->pers->update_reshape_pos)
			mddev->pers->update_reshape_pos(mddev);
	पूर्ण

	/* Finally set the event to be up to date */
	mddev->events = le64_to_cpu(sb->events);
पूर्ण

अटल पूर्णांक पढ़ो_rdev(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	पूर्णांक err;
	काष्ठा page *swapout = rdev->sb_page;
	काष्ठा mdp_superblock_1 *sb;

	/* Store the sb page of the rdev in the swapout temporary
	 * variable in हाल we err in the future
	 */
	rdev->sb_page = शून्य;
	err = alloc_disk_sb(rdev);
	अगर (err == 0) अणु
		ClearPageUptodate(rdev->sb_page);
		rdev->sb_loaded = 0;
		err = super_types[mddev->major_version].
			load_super(rdev, शून्य, mddev->minor_version);
	पूर्ण
	अगर (err < 0) अणु
		pr_warn("%s: %d Could not reload rdev(%d) err: %d. Restoring old values\n",
				__func__, __LINE__, rdev->desc_nr, err);
		अगर (rdev->sb_page)
			put_page(rdev->sb_page);
		rdev->sb_page = swapout;
		rdev->sb_loaded = 1;
		वापस err;
	पूर्ण

	sb = page_address(rdev->sb_page);
	/* Read the offset unconditionally, even अगर MD_FEATURE_RECOVERY_OFFSET
	 * is not set
	 */

	अगर ((le32_to_cpu(sb->feature_map) & MD_FEATURE_RECOVERY_OFFSET))
		rdev->recovery_offset = le64_to_cpu(sb->recovery_offset);

	/* The other node finished recovery, call spare_active to set
	 * device In_sync and mddev->degraded
	 */
	अगर (rdev->recovery_offset == MaxSector &&
	    !test_bit(In_sync, &rdev->flags) &&
	    mddev->pers->spare_active(mddev))
		sysfs_notअगरy_dirent_safe(mddev->sysfs_degraded);

	put_page(swapout);
	वापस 0;
पूर्ण

व्योम md_reload_sb(काष्ठा mddev *mddev, पूर्णांक nr)
अणु
	काष्ठा md_rdev *rdev;
	पूर्णांक err;

	/* Find the rdev */
	rdev_क्रम_each_rcu(rdev, mddev) अणु
		अगर (rdev->desc_nr == nr)
			अवरोध;
	पूर्ण

	अगर (!rdev || rdev->desc_nr != nr) अणु
		pr_warn("%s: %d Could not find rdev with nr %d\n", __func__, __LINE__, nr);
		वापस;
	पूर्ण

	err = पढ़ो_rdev(mddev, rdev);
	अगर (err < 0)
		वापस;

	check_sb_changes(mddev, rdev);

	/* Read all rdev's to update recovery_offset */
	rdev_क्रम_each_rcu(rdev, mddev) अणु
		अगर (!test_bit(Faulty, &rdev->flags))
			पढ़ो_rdev(mddev, rdev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(md_reload_sb);

#अगर_अघोषित MODULE

/*
 * Searches all रेजिस्टरed partitions क्रम स्वतःrun RAID arrays
 * at boot समय.
 */

अटल DEFINE_MUTEX(detected_devices_mutex);
अटल LIST_HEAD(all_detected_devices);
काष्ठा detected_devices_node अणु
	काष्ठा list_head list;
	dev_t dev;
पूर्ण;

व्योम md_स्वतःdetect_dev(dev_t dev)
अणु
	काष्ठा detected_devices_node *node_detected_dev;

	node_detected_dev = kzalloc(माप(*node_detected_dev), GFP_KERNEL);
	अगर (node_detected_dev) अणु
		node_detected_dev->dev = dev;
		mutex_lock(&detected_devices_mutex);
		list_add_tail(&node_detected_dev->list, &all_detected_devices);
		mutex_unlock(&detected_devices_mutex);
	पूर्ण
पूर्ण

व्योम md_स्वतःstart_arrays(पूर्णांक part)
अणु
	काष्ठा md_rdev *rdev;
	काष्ठा detected_devices_node *node_detected_dev;
	dev_t dev;
	पूर्णांक i_scanned, i_passed;

	i_scanned = 0;
	i_passed = 0;

	pr_info("md: Autodetecting RAID arrays.\n");

	mutex_lock(&detected_devices_mutex);
	जबतक (!list_empty(&all_detected_devices) && i_scanned < पूर्णांक_उच्च) अणु
		i_scanned++;
		node_detected_dev = list_entry(all_detected_devices.next,
					काष्ठा detected_devices_node, list);
		list_del(&node_detected_dev->list);
		dev = node_detected_dev->dev;
		kमुक्त(node_detected_dev);
		mutex_unlock(&detected_devices_mutex);
		rdev = md_import_device(dev,0, 90);
		mutex_lock(&detected_devices_mutex);
		अगर (IS_ERR(rdev))
			जारी;

		अगर (test_bit(Faulty, &rdev->flags))
			जारी;

		set_bit(AutoDetected, &rdev->flags);
		list_add(&rdev->same_set, &pending_raid_disks);
		i_passed++;
	पूर्ण
	mutex_unlock(&detected_devices_mutex);

	pr_debug("md: Scanned %d and added %d devices.\n", i_scanned, i_passed);

	स्वतःrun_devices(part);
पूर्ण

#पूर्ण_अगर /* !MODULE */

अटल __निकास व्योम md_निकास(व्योम)
अणु
	काष्ठा mddev *mddev;
	काष्ठा list_head *पंचांगp;
	पूर्णांक delay = 1;

	unरेजिस्टर_blkdev(MD_MAJOR,"md");
	unरेजिस्टर_blkdev(mdp_major, "mdp");
	unरेजिस्टर_reboot_notअगरier(&md_notअगरier);
	unरेजिस्टर_sysctl_table(raid_table_header);

	/* We cannot unload the modules जबतक some process is
	 * रुकोing क्रम us in select() or poll() - wake them up
	 */
	md_unloading = 1;
	जबतक (रुकोqueue_active(&md_event_रुकोers)) अणु
		/* not safe to leave yet */
		wake_up(&md_event_रुकोers);
		msleep(delay);
		delay += delay;
	पूर्ण
	हटाओ_proc_entry("mdstat", शून्य);

	क्रम_each_mddev(mddev, पंचांगp) अणु
		export_array(mddev);
		mddev->स_समय = 0;
		mddev->hold_active = 0;
		/*
		 * क्रम_each_mddev() will call mddev_put() at the end of each
		 * iteration.  As the mddev is now fully clear, this will
		 * schedule the mddev क्रम deकाष्ठाion by a workqueue, and the
		 * destroy_workqueue() below will रुको क्रम that to complete.
		 */
	पूर्ण
	destroy_workqueue(md_rdev_misc_wq);
	destroy_workqueue(md_misc_wq);
	destroy_workqueue(md_wq);
पूर्ण

subsys_initcall(md_init);
module_निकास(md_निकास)

अटल पूर्णांक get_ro(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "%d\n", start_पढ़ोonly);
पूर्ण
अटल पूर्णांक set_ro(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस kstrtouपूर्णांक(val, 10, (अचिन्हित पूर्णांक *)&start_पढ़ोonly);
पूर्ण

module_param_call(start_ro, set_ro, get_ro, शून्य, S_IRUSR|S_IWUSR);
module_param(start_dirty_degraded, पूर्णांक, S_IRUGO|S_IWUSR);
module_param_call(new_array, add_named_array, शून्य, शून्य, S_IWUSR);
module_param(create_on_खोलो, bool, S_IRUSR|S_IWUSR);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MD RAID framework");
MODULE_ALIAS("md");
MODULE_ALIAS_BLOCKDEV_MAJOR(MD_MAJOR);
