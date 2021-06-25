<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   linear.c : Multiple Devices driver क्रम Linux
	      Copyright (C) 1994-96 Marc ZYNGIER
	      <zyngier@ufr-info-p7.ibp.fr> or
	      <maz@gloups.fdn.fr>

   Linear mode management functions.

*/

#समावेश <linux/blkdev.h>
#समावेश <linux/raid/md_u.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <trace/events/block.h>
#समावेश "md.h"
#समावेश "md-linear.h"

/*
 * find which device holds a particular offset
 */
अटल अंतरभूत काष्ठा dev_info *which_dev(काष्ठा mddev *mddev, sector_t sector)
अणु
	पूर्णांक lo, mid, hi;
	काष्ठा linear_conf *conf;

	lo = 0;
	hi = mddev->raid_disks - 1;
	conf = mddev->निजी;

	/*
	 * Binary Search
	 */

	जबतक (hi > lo) अणु

		mid = (hi + lo) / 2;
		अगर (sector < conf->disks[mid].end_sector)
			hi = mid;
		अन्यथा
			lo = mid + 1;
	पूर्ण

	वापस conf->disks + lo;
पूर्ण

अटल sector_t linear_size(काष्ठा mddev *mddev, sector_t sectors, पूर्णांक raid_disks)
अणु
	काष्ठा linear_conf *conf;
	sector_t array_sectors;

	conf = mddev->निजी;
	WARN_ONCE(sectors || raid_disks,
		  "%s does not support generic reshape\n", __func__);
	array_sectors = conf->array_sectors;

	वापस array_sectors;
पूर्ण

अटल काष्ठा linear_conf *linear_conf(काष्ठा mddev *mddev, पूर्णांक raid_disks)
अणु
	काष्ठा linear_conf *conf;
	काष्ठा md_rdev *rdev;
	पूर्णांक i, cnt;
	bool discard_supported = false;

	conf = kzalloc(काष्ठा_size(conf, disks, raid_disks), GFP_KERNEL);
	अगर (!conf)
		वापस शून्य;

	cnt = 0;
	conf->array_sectors = 0;

	rdev_क्रम_each(rdev, mddev) अणु
		पूर्णांक j = rdev->raid_disk;
		काष्ठा dev_info *disk = conf->disks + j;
		sector_t sectors;

		अगर (j < 0 || j >= raid_disks || disk->rdev) अणु
			pr_warn("md/linear:%s: disk numbering problem. Aborting!\n",
				mdname(mddev));
			जाओ out;
		पूर्ण

		disk->rdev = rdev;
		अगर (mddev->chunk_sectors) अणु
			sectors = rdev->sectors;
			sector_भाग(sectors, mddev->chunk_sectors);
			rdev->sectors = sectors * mddev->chunk_sectors;
		पूर्ण

		disk_stack_limits(mddev->gendisk, rdev->bdev,
				  rdev->data_offset << 9);

		conf->array_sectors += rdev->sectors;
		cnt++;

		अगर (blk_queue_discard(bdev_get_queue(rdev->bdev)))
			discard_supported = true;
	पूर्ण
	अगर (cnt != raid_disks) अणु
		pr_warn("md/linear:%s: not enough drives present. Aborting!\n",
			mdname(mddev));
		जाओ out;
	पूर्ण

	अगर (!discard_supported)
		blk_queue_flag_clear(QUEUE_FLAG_DISCARD, mddev->queue);
	अन्यथा
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, mddev->queue);

	/*
	 * Here we calculate the device offsets.
	 */
	conf->disks[0].end_sector = conf->disks[0].rdev->sectors;

	क्रम (i = 1; i < raid_disks; i++)
		conf->disks[i].end_sector =
			conf->disks[i-1].end_sector +
			conf->disks[i].rdev->sectors;

	/*
	 * conf->raid_disks is copy of mddev->raid_disks. The reason to
	 * keep a copy of mddev->raid_disks in काष्ठा linear_conf is,
	 * mddev->raid_disks may not be consistent with poपूर्णांकers number of
	 * conf->disks[] when it is updated in linear_add() and used to
	 * iterate old conf->disks[] earray in linear_congested().
	 * Here conf->raid_disks is always consitent with number of
	 * poपूर्णांकers in conf->disks[] array, and mddev->निजी is updated
	 * with rcu_assign_poपूर्णांकer() in linear_addr(), such race can be
	 * aव्योमed.
	 */
	conf->raid_disks = raid_disks;

	वापस conf;

out:
	kमुक्त(conf);
	वापस शून्य;
पूर्ण

अटल पूर्णांक linear_run (काष्ठा mddev *mddev)
अणु
	काष्ठा linear_conf *conf;
	पूर्णांक ret;

	अगर (md_check_no_biपंचांगap(mddev))
		वापस -EINVAL;
	conf = linear_conf(mddev, mddev->raid_disks);

	अगर (!conf)
		वापस 1;
	mddev->निजी = conf;
	md_set_array_sectors(mddev, linear_size(mddev, 0, 0));

	ret =  md_पूर्णांकegrity_रेजिस्टर(mddev);
	अगर (ret) अणु
		kमुक्त(conf);
		mddev->निजी = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक linear_add(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	/* Adding a drive to a linear array allows the array to grow.
	 * It is permitted अगर the new drive has a matching superblock
	 * alपढ़ोy on it, with raid_disk equal to raid_disks.
	 * It is achieved by creating a new linear_निजी_data काष्ठाure
	 * and swapping it in in-place of the current one.
	 * The current one is never मुक्तd until the array is stopped.
	 * This aव्योमs races.
	 */
	काष्ठा linear_conf *newconf, *oldconf;

	अगर (rdev->saved_raid_disk != mddev->raid_disks)
		वापस -EINVAL;

	rdev->raid_disk = rdev->saved_raid_disk;
	rdev->saved_raid_disk = -1;

	newconf = linear_conf(mddev,mddev->raid_disks+1);

	अगर (!newconf)
		वापस -ENOMEM;

	/* newconf->raid_disks alपढ़ोy keeps a copy of * the increased
	 * value of mddev->raid_disks, WARN_ONCE() is just used to make
	 * sure of this. It is possible that oldconf is still referenced
	 * in linear_congested(), thereक्रमe kमुक्त_rcu() is used to मुक्त
	 * oldconf until no one uses it anymore.
	 */
	mddev_suspend(mddev);
	oldconf = rcu_dereference_रक्षित(mddev->निजी,
			lockdep_is_held(&mddev->reconfig_mutex));
	mddev->raid_disks++;
	WARN_ONCE(mddev->raid_disks != newconf->raid_disks,
		"copied raid_disks doesn't match mddev->raid_disks");
	rcu_assign_poपूर्णांकer(mddev->निजी, newconf);
	md_set_array_sectors(mddev, linear_size(mddev, 0, 0));
	set_capacity_and_notअगरy(mddev->gendisk, mddev->array_sectors);
	mddev_resume(mddev);
	kमुक्त_rcu(oldconf, rcu);
	वापस 0;
पूर्ण

अटल व्योम linear_मुक्त(काष्ठा mddev *mddev, व्योम *priv)
अणु
	काष्ठा linear_conf *conf = priv;

	kमुक्त(conf);
पूर्ण

अटल bool linear_make_request(काष्ठा mddev *mddev, काष्ठा bio *bio)
अणु
	अक्षर b[BDEVNAME_SIZE];
	काष्ठा dev_info *पंचांगp_dev;
	sector_t start_sector, end_sector, data_offset;
	sector_t bio_sector = bio->bi_iter.bi_sector;

	अगर (unlikely(bio->bi_opf & REQ_PREFLUSH)
	    && md_flush_request(mddev, bio))
		वापस true;

	पंचांगp_dev = which_dev(mddev, bio_sector);
	start_sector = पंचांगp_dev->end_sector - पंचांगp_dev->rdev->sectors;
	end_sector = पंचांगp_dev->end_sector;
	data_offset = पंचांगp_dev->rdev->data_offset;

	अगर (unlikely(bio_sector >= end_sector ||
		     bio_sector < start_sector))
		जाओ out_of_bounds;

	अगर (unlikely(is_mddev_broken(पंचांगp_dev->rdev, "linear"))) अणु
		bio_io_error(bio);
		वापस true;
	पूर्ण

	अगर (unlikely(bio_end_sector(bio) > end_sector)) अणु
		/* This bio crosses a device boundary, so we have to split it */
		काष्ठा bio *split = bio_split(bio, end_sector - bio_sector,
					      GFP_NOIO, &mddev->bio_set);
		bio_chain(split, bio);
		submit_bio_noacct(bio);
		bio = split;
	पूर्ण

	bio_set_dev(bio, पंचांगp_dev->rdev->bdev);
	bio->bi_iter.bi_sector = bio->bi_iter.bi_sector -
		start_sector + data_offset;

	अगर (unlikely((bio_op(bio) == REQ_OP_DISCARD) &&
		     !blk_queue_discard(bio->bi_bdev->bd_disk->queue))) अणु
		/* Just ignore it */
		bio_endio(bio);
	पूर्ण अन्यथा अणु
		अगर (mddev->gendisk)
			trace_block_bio_remap(bio, disk_devt(mddev->gendisk),
					      bio_sector);
		mddev_check_ग_लिखोsame(mddev, bio);
		mddev_check_ग_लिखो_zeroes(mddev, bio);
		submit_bio_noacct(bio);
	पूर्ण
	वापस true;

out_of_bounds:
	pr_err("md/linear:%s: make_request: Sector %llu out of bounds on dev %s: %llu sectors, offset %llu\n",
	       mdname(mddev),
	       (अचिन्हित दीर्घ दीर्घ)bio->bi_iter.bi_sector,
	       bdevname(पंचांगp_dev->rdev->bdev, b),
	       (अचिन्हित दीर्घ दीर्घ)पंचांगp_dev->rdev->sectors,
	       (अचिन्हित दीर्घ दीर्घ)start_sector);
	bio_io_error(bio);
	वापस true;
पूर्ण

अटल व्योम linear_status (काष्ठा seq_file *seq, काष्ठा mddev *mddev)
अणु
	seq_म_लिखो(seq, " %dk rounding", mddev->chunk_sectors / 2);
पूर्ण

अटल व्योम linear_quiesce(काष्ठा mddev *mddev, पूर्णांक state)
अणु
पूर्ण

अटल काष्ठा md_personality linear_personality =
अणु
	.name		= "linear",
	.level		= LEVEL_LINEAR,
	.owner		= THIS_MODULE,
	.make_request	= linear_make_request,
	.run		= linear_run,
	.मुक्त		= linear_मुक्त,
	.status		= linear_status,
	.hot_add_disk	= linear_add,
	.size		= linear_size,
	.quiesce	= linear_quiesce,
पूर्ण;

अटल पूर्णांक __init linear_init (व्योम)
अणु
	वापस रेजिस्टर_md_personality (&linear_personality);
पूर्ण

अटल व्योम linear_निकास (व्योम)
अणु
	unरेजिस्टर_md_personality (&linear_personality);
पूर्ण

module_init(linear_init);
module_निकास(linear_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linear device concatenation personality for MD");
MODULE_ALIAS("md-personality-1"); /* LINEAR - deprecated*/
MODULE_ALIAS("md-linear");
MODULE_ALIAS("md-level--1");
