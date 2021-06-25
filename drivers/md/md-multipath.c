<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * multipath.c : Multiple Devices driver क्रम Linux
 *
 * Copyright (C) 1999, 2000, 2001 Ingo Molnar, Red Hat
 *
 * Copyright (C) 1996, 1997, 1998 Ingo Molnar, Miguel de Icaza, Gadi Oxman
 *
 * MULTIPATH management functions.
 *
 * derived from raid1.c.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <linux/raid/md_u.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश "md.h"
#समावेश "md-multipath.h"

#घोषणा MAX_WORK_PER_DISK 128

#घोषणा	NR_RESERVED_BUFS	32

अटल पूर्णांक multipath_map (काष्ठा mpconf *conf)
अणु
	पूर्णांक i, disks = conf->raid_disks;

	/*
	 * Later we करो पढ़ो balancing on the पढ़ो side
	 * now we use the first available disk.
	 */

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < disks; i++) अणु
		काष्ठा md_rdev *rdev = rcu_dereference(conf->multipaths[i].rdev);
		अगर (rdev && test_bit(In_sync, &rdev->flags) &&
		    !test_bit(Faulty, &rdev->flags)) अणु
			atomic_inc(&rdev->nr_pending);
			rcu_पढ़ो_unlock();
			वापस i;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	pr_crit_ratelimited("multipath_map(): no more operational IO paths?\n");
	वापस (-1);
पूर्ण

अटल व्योम multipath_reschedule_retry (काष्ठा multipath_bh *mp_bh)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mddev *mddev = mp_bh->mddev;
	काष्ठा mpconf *conf = mddev->निजी;

	spin_lock_irqsave(&conf->device_lock, flags);
	list_add(&mp_bh->retry_list, &conf->retry_list);
	spin_unlock_irqrestore(&conf->device_lock, flags);
	md_wakeup_thपढ़ो(mddev->thपढ़ो);
पूर्ण

/*
 * multipath_end_bh_io() is called when we have finished servicing a multipathed
 * operation and are पढ़ोy to वापस a success/failure code to the buffer
 * cache layer.
 */
अटल व्योम multipath_end_bh_io(काष्ठा multipath_bh *mp_bh, blk_status_t status)
अणु
	काष्ठा bio *bio = mp_bh->master_bio;
	काष्ठा mpconf *conf = mp_bh->mddev->निजी;

	bio->bi_status = status;
	bio_endio(bio);
	mempool_मुक्त(mp_bh, &conf->pool);
पूर्ण

अटल व्योम multipath_end_request(काष्ठा bio *bio)
अणु
	काष्ठा multipath_bh *mp_bh = bio->bi_निजी;
	काष्ठा mpconf *conf = mp_bh->mddev->निजी;
	काष्ठा md_rdev *rdev = conf->multipaths[mp_bh->path].rdev;

	अगर (!bio->bi_status)
		multipath_end_bh_io(mp_bh, 0);
	अन्यथा अगर (!(bio->bi_opf & REQ_RAHEAD)) अणु
		/*
		 * oops, IO error:
		 */
		अक्षर b[BDEVNAME_SIZE];
		md_error (mp_bh->mddev, rdev);
		pr_info("multipath: %s: rescheduling sector %llu\n",
			bdevname(rdev->bdev,b),
			(अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector);
		multipath_reschedule_retry(mp_bh);
	पूर्ण अन्यथा
		multipath_end_bh_io(mp_bh, bio->bi_status);
	rdev_dec_pending(rdev, conf->mddev);
पूर्ण

अटल bool multipath_make_request(काष्ठा mddev *mddev, काष्ठा bio * bio)
अणु
	काष्ठा mpconf *conf = mddev->निजी;
	काष्ठा multipath_bh * mp_bh;
	काष्ठा multipath_info *multipath;

	अगर (unlikely(bio->bi_opf & REQ_PREFLUSH)
	    && md_flush_request(mddev, bio))
		वापस true;

	mp_bh = mempool_alloc(&conf->pool, GFP_NOIO);

	mp_bh->master_bio = bio;
	mp_bh->mddev = mddev;

	mp_bh->path = multipath_map(conf);
	अगर (mp_bh->path < 0) अणु
		bio_io_error(bio);
		mempool_मुक्त(mp_bh, &conf->pool);
		वापस true;
	पूर्ण
	multipath = conf->multipaths + mp_bh->path;

	bio_init(&mp_bh->bio, शून्य, 0);
	__bio_clone_fast(&mp_bh->bio, bio);

	mp_bh->bio.bi_iter.bi_sector += multipath->rdev->data_offset;
	bio_set_dev(&mp_bh->bio, multipath->rdev->bdev);
	mp_bh->bio.bi_opf |= REQ_FAILFAST_TRANSPORT;
	mp_bh->bio.bi_end_io = multipath_end_request;
	mp_bh->bio.bi_निजी = mp_bh;
	mddev_check_ग_लिखोsame(mddev, &mp_bh->bio);
	mddev_check_ग_लिखो_zeroes(mddev, &mp_bh->bio);
	submit_bio_noacct(&mp_bh->bio);
	वापस true;
पूर्ण

अटल व्योम multipath_status(काष्ठा seq_file *seq, काष्ठा mddev *mddev)
अणु
	काष्ठा mpconf *conf = mddev->निजी;
	पूर्णांक i;

	seq_म_लिखो (seq, " [%d/%d] [", conf->raid_disks,
		    conf->raid_disks - mddev->degraded);
	rcu_पढ़ो_lock();
	क्रम (i = 0; i < conf->raid_disks; i++) अणु
		काष्ठा md_rdev *rdev = rcu_dereference(conf->multipaths[i].rdev);
		seq_म_लिखो (seq, "%s", rdev && test_bit(In_sync, &rdev->flags) ? "U" : "_");
	पूर्ण
	rcu_पढ़ो_unlock();
	seq_अ_दो(seq, ']');
पूर्ण

/*
 * Careful, this can execute in IRQ contexts as well!
 */
अटल व्योम multipath_error (काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा mpconf *conf = mddev->निजी;
	अक्षर b[BDEVNAME_SIZE];

	अगर (conf->raid_disks - mddev->degraded <= 1) अणु
		/*
		 * Uh oh, we can करो nothing अगर this is our last path, but
		 * first check अगर this is a queued request क्रम a device
		 * which has just failed.
		 */
		pr_warn("multipath: only one IO path left and IO error.\n");
		/* leave it active... it's all we have */
		वापस;
	पूर्ण
	/*
	 * Mark disk as unusable
	 */
	अगर (test_and_clear_bit(In_sync, &rdev->flags)) अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&conf->device_lock, flags);
		mddev->degraded++;
		spin_unlock_irqrestore(&conf->device_lock, flags);
	पूर्ण
	set_bit(Faulty, &rdev->flags);
	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
	pr_err("multipath: IO failure on %s, disabling IO path.\n"
	       "multipath: Operation continuing on %d IO paths.\n",
	       bdevname(rdev->bdev, b),
	       conf->raid_disks - mddev->degraded);
पूर्ण

अटल व्योम prपूर्णांक_multipath_conf (काष्ठा mpconf *conf)
अणु
	पूर्णांक i;
	काष्ठा multipath_info *पंचांगp;

	pr_debug("MULTIPATH conf printout:\n");
	अगर (!conf) अणु
		pr_debug("(conf==NULL)\n");
		वापस;
	पूर्ण
	pr_debug(" --- wd:%d rd:%d\n", conf->raid_disks - conf->mddev->degraded,
		 conf->raid_disks);

	क्रम (i = 0; i < conf->raid_disks; i++) अणु
		अक्षर b[BDEVNAME_SIZE];
		पंचांगp = conf->multipaths + i;
		अगर (पंचांगp->rdev)
			pr_debug(" disk%d, o:%d, dev:%s\n",
				 i,!test_bit(Faulty, &पंचांगp->rdev->flags),
				 bdevname(पंचांगp->rdev->bdev,b));
	पूर्ण
पूर्ण

अटल पूर्णांक multipath_add_disk(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा mpconf *conf = mddev->निजी;
	पूर्णांक err = -EEXIST;
	पूर्णांक path;
	काष्ठा multipath_info *p;
	पूर्णांक first = 0;
	पूर्णांक last = mddev->raid_disks - 1;

	अगर (rdev->raid_disk >= 0)
		first = last = rdev->raid_disk;

	prपूर्णांक_multipath_conf(conf);

	क्रम (path = first; path <= last; path++)
		अगर ((p=conf->multipaths+path)->rdev == शून्य) अणु
			disk_stack_limits(mddev->gendisk, rdev->bdev,
					  rdev->data_offset << 9);

			err = md_पूर्णांकegrity_add_rdev(rdev, mddev);
			अगर (err)
				अवरोध;
			spin_lock_irq(&conf->device_lock);
			mddev->degraded--;
			rdev->raid_disk = path;
			set_bit(In_sync, &rdev->flags);
			spin_unlock_irq(&conf->device_lock);
			rcu_assign_poपूर्णांकer(p->rdev, rdev);
			err = 0;
			अवरोध;
		पूर्ण

	prपूर्णांक_multipath_conf(conf);

	वापस err;
पूर्ण

अटल पूर्णांक multipath_हटाओ_disk(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा mpconf *conf = mddev->निजी;
	पूर्णांक err = 0;
	पूर्णांक number = rdev->raid_disk;
	काष्ठा multipath_info *p = conf->multipaths + number;

	prपूर्णांक_multipath_conf(conf);

	अगर (rdev == p->rdev) अणु
		अगर (test_bit(In_sync, &rdev->flags) ||
		    atomic_पढ़ो(&rdev->nr_pending)) अणु
			pr_warn("hot-remove-disk, slot %d is identified but is still operational!\n", number);
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
		err = md_पूर्णांकegrity_रेजिस्टर(mddev);
	पूर्ण
पात:

	prपूर्णांक_multipath_conf(conf);
	वापस err;
पूर्ण

/*
 * This is a kernel thपढ़ो which:
 *
 *	1.	Retries failed पढ़ो operations on working multipaths.
 *	2.	Updates the raid superblock when problems encounter.
 *	3.	Perक्रमms ग_लिखोs following पढ़ोs क्रम array syncronising.
 */

अटल व्योम multipathd(काष्ठा md_thपढ़ो *thपढ़ो)
अणु
	काष्ठा mddev *mddev = thपढ़ो->mddev;
	काष्ठा multipath_bh *mp_bh;
	काष्ठा bio *bio;
	अचिन्हित दीर्घ flags;
	काष्ठा mpconf *conf = mddev->निजी;
	काष्ठा list_head *head = &conf->retry_list;

	md_check_recovery(mddev);
	क्रम (;;) अणु
		अक्षर b[BDEVNAME_SIZE];
		spin_lock_irqsave(&conf->device_lock, flags);
		अगर (list_empty(head))
			अवरोध;
		mp_bh = list_entry(head->prev, काष्ठा multipath_bh, retry_list);
		list_del(head->prev);
		spin_unlock_irqrestore(&conf->device_lock, flags);

		bio = &mp_bh->bio;
		bio->bi_iter.bi_sector = mp_bh->master_bio->bi_iter.bi_sector;

		अगर ((mp_bh->path = multipath_map (conf))<0) अणु
			pr_err("multipath: %s: unrecoverable IO read error for block %llu\n",
			       bio_devname(bio, b),
			       (अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector);
			multipath_end_bh_io(mp_bh, BLK_STS_IOERR);
		पूर्ण अन्यथा अणु
			pr_err("multipath: %s: redirecting sector %llu to another IO path\n",
			       bio_devname(bio, b),
			       (अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector);
			*bio = *(mp_bh->master_bio);
			bio->bi_iter.bi_sector +=
				conf->multipaths[mp_bh->path].rdev->data_offset;
			bio_set_dev(bio, conf->multipaths[mp_bh->path].rdev->bdev);
			bio->bi_opf |= REQ_FAILFAST_TRANSPORT;
			bio->bi_end_io = multipath_end_request;
			bio->bi_निजी = mp_bh;
			submit_bio_noacct(bio);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&conf->device_lock, flags);
पूर्ण

अटल sector_t multipath_size(काष्ठा mddev *mddev, sector_t sectors, पूर्णांक raid_disks)
अणु
	WARN_ONCE(sectors || raid_disks,
		  "%s does not support generic reshape\n", __func__);

	वापस mddev->dev_sectors;
पूर्ण

अटल पूर्णांक multipath_run (काष्ठा mddev *mddev)
अणु
	काष्ठा mpconf *conf;
	पूर्णांक disk_idx;
	काष्ठा multipath_info *disk;
	काष्ठा md_rdev *rdev;
	पूर्णांक working_disks;
	पूर्णांक ret;

	अगर (md_check_no_biपंचांगap(mddev))
		वापस -EINVAL;

	अगर (mddev->level != LEVEL_MULTIPATH) अणु
		pr_warn("multipath: %s: raid level not set to multipath IO (%d)\n",
			mdname(mddev), mddev->level);
		जाओ out;
	पूर्ण
	/*
	 * copy the alपढ़ोy verअगरied devices पूर्णांकo our निजी MULTIPATH
	 * bookkeeping area. [whatever we allocate in multipath_run(),
	 * should be मुक्तd in multipath_मुक्त()]
	 */

	conf = kzalloc(माप(काष्ठा mpconf), GFP_KERNEL);
	mddev->निजी = conf;
	अगर (!conf)
		जाओ out;

	conf->multipaths = kसुस्मृति(mddev->raid_disks,
				   माप(काष्ठा multipath_info),
				   GFP_KERNEL);
	अगर (!conf->multipaths)
		जाओ out_मुक्त_conf;

	working_disks = 0;
	rdev_क्रम_each(rdev, mddev) अणु
		disk_idx = rdev->raid_disk;
		अगर (disk_idx < 0 ||
		    disk_idx >= mddev->raid_disks)
			जारी;

		disk = conf->multipaths + disk_idx;
		disk->rdev = rdev;
		disk_stack_limits(mddev->gendisk, rdev->bdev,
				  rdev->data_offset << 9);

		अगर (!test_bit(Faulty, &rdev->flags))
			working_disks++;
	पूर्ण

	conf->raid_disks = mddev->raid_disks;
	conf->mddev = mddev;
	spin_lock_init(&conf->device_lock);
	INIT_LIST_HEAD(&conf->retry_list);

	अगर (!working_disks) अणु
		pr_warn("multipath: no operational IO paths for %s\n",
			mdname(mddev));
		जाओ out_मुक्त_conf;
	पूर्ण
	mddev->degraded = conf->raid_disks - working_disks;

	ret = mempool_init_kदो_स्मृति_pool(&conf->pool, NR_RESERVED_BUFS,
					माप(काष्ठा multipath_bh));
	अगर (ret)
		जाओ out_मुक्त_conf;

	mddev->thपढ़ो = md_रेजिस्टर_thपढ़ो(multipathd, mddev,
					   "multipath");
	अगर (!mddev->thपढ़ो)
		जाओ out_मुक्त_conf;

	pr_info("multipath: array %s active with %d out of %d IO paths\n",
		mdname(mddev), conf->raid_disks - mddev->degraded,
		mddev->raid_disks);
	/*
	 * Ok, everything is just fine now
	 */
	md_set_array_sectors(mddev, multipath_size(mddev, 0, 0));

	अगर (md_पूर्णांकegrity_रेजिस्टर(mddev))
		जाओ out_मुक्त_conf;

	वापस 0;

out_मुक्त_conf:
	mempool_निकास(&conf->pool);
	kमुक्त(conf->multipaths);
	kमुक्त(conf);
	mddev->निजी = शून्य;
out:
	वापस -EIO;
पूर्ण

अटल व्योम multipath_मुक्त(काष्ठा mddev *mddev, व्योम *priv)
अणु
	काष्ठा mpconf *conf = priv;

	mempool_निकास(&conf->pool);
	kमुक्त(conf->multipaths);
	kमुक्त(conf);
पूर्ण

अटल काष्ठा md_personality multipath_personality =
अणु
	.name		= "multipath",
	.level		= LEVEL_MULTIPATH,
	.owner		= THIS_MODULE,
	.make_request	= multipath_make_request,
	.run		= multipath_run,
	.मुक्त		= multipath_मुक्त,
	.status		= multipath_status,
	.error_handler	= multipath_error,
	.hot_add_disk	= multipath_add_disk,
	.hot_हटाओ_disk= multipath_हटाओ_disk,
	.size		= multipath_size,
पूर्ण;

अटल पूर्णांक __init multipath_init (व्योम)
अणु
	वापस रेजिस्टर_md_personality (&multipath_personality);
पूर्ण

अटल व्योम __निकास multipath_निकास (व्योम)
अणु
	unरेजिस्टर_md_personality (&multipath_personality);
पूर्ण

module_init(multipath_init);
module_निकास(multipath_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("simple multi-path personality for MD");
MODULE_ALIAS("md-personality-7"); /* MULTIPATH */
MODULE_ALIAS("md-multipath");
MODULE_ALIAS("md-level--4");
