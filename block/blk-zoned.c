<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Zoned block device handling
 *
 * Copyright (c) 2015, Hannes Reinecke
 * Copyright (c) 2015, SUSE Linux GmbH
 *
 * Copyright (c) 2016, Damien Le Moal
 * Copyright (c) 2016, Western Digital
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched/mm.h>

#समावेश "blk.h"

#घोषणा ZONE_COND_NAME(name) [BLK_ZONE_COND_##name] = #name
अटल स्थिर अक्षर *स्थिर zone_cond_name[] = अणु
	ZONE_COND_NAME(NOT_WP),
	ZONE_COND_NAME(EMPTY),
	ZONE_COND_NAME(IMP_OPEN),
	ZONE_COND_NAME(EXP_OPEN),
	ZONE_COND_NAME(CLOSED),
	ZONE_COND_NAME(READONLY),
	ZONE_COND_NAME(FULL),
	ZONE_COND_NAME(OFFLINE),
पूर्ण;
#अघोषित ZONE_COND_NAME

/**
 * blk_zone_cond_str - Return string XXX in BLK_ZONE_COND_XXX.
 * @zone_cond: BLK_ZONE_COND_XXX.
 *
 * Description: Centralize block layer function to convert BLK_ZONE_COND_XXX
 * पूर्णांकo string क्रमmat. Useful in the debugging and tracing zone conditions. For
 * invalid BLK_ZONE_COND_XXX it वापसs string "UNKNOWN".
 */
स्थिर अक्षर *blk_zone_cond_str(क्रमागत blk_zone_cond zone_cond)
अणु
	अटल स्थिर अक्षर *zone_cond_str = "UNKNOWN";

	अगर (zone_cond < ARRAY_SIZE(zone_cond_name) && zone_cond_name[zone_cond])
		zone_cond_str = zone_cond_name[zone_cond];

	वापस zone_cond_str;
पूर्ण
EXPORT_SYMBOL_GPL(blk_zone_cond_str);

/*
 * Return true अगर a request is a ग_लिखो requests that needs zone ग_लिखो locking.
 */
bool blk_req_needs_zone_ग_लिखो_lock(काष्ठा request *rq)
अणु
	अगर (!rq->q->seq_zones_wlock)
		वापस false;

	अगर (blk_rq_is_passthrough(rq))
		वापस false;

	चयन (req_op(rq)) अणु
	हाल REQ_OP_WRITE_ZEROES:
	हाल REQ_OP_WRITE_SAME:
	हाल REQ_OP_WRITE:
		वापस blk_rq_zone_is_seq(rq);
	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(blk_req_needs_zone_ग_लिखो_lock);

bool blk_req_zone_ग_लिखो_trylock(काष्ठा request *rq)
अणु
	अचिन्हित पूर्णांक zno = blk_rq_zone_no(rq);

	अगर (test_and_set_bit(zno, rq->q->seq_zones_wlock))
		वापस false;

	WARN_ON_ONCE(rq->rq_flags & RQF_ZONE_WRITE_LOCKED);
	rq->rq_flags |= RQF_ZONE_WRITE_LOCKED;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(blk_req_zone_ग_लिखो_trylock);

व्योम __blk_req_zone_ग_लिखो_lock(काष्ठा request *rq)
अणु
	अगर (WARN_ON_ONCE(test_and_set_bit(blk_rq_zone_no(rq),
					  rq->q->seq_zones_wlock)))
		वापस;

	WARN_ON_ONCE(rq->rq_flags & RQF_ZONE_WRITE_LOCKED);
	rq->rq_flags |= RQF_ZONE_WRITE_LOCKED;
पूर्ण
EXPORT_SYMBOL_GPL(__blk_req_zone_ग_लिखो_lock);

व्योम __blk_req_zone_ग_लिखो_unlock(काष्ठा request *rq)
अणु
	rq->rq_flags &= ~RQF_ZONE_WRITE_LOCKED;
	अगर (rq->q->seq_zones_wlock)
		WARN_ON_ONCE(!test_and_clear_bit(blk_rq_zone_no(rq),
						 rq->q->seq_zones_wlock));
पूर्ण
EXPORT_SYMBOL_GPL(__blk_req_zone_ग_लिखो_unlock);

/**
 * blkdev_nr_zones - Get number of zones
 * @disk:	Target gendisk
 *
 * Return the total number of zones of a zoned block device.  For a block
 * device without zone capabilities, the number of zones is always 0.
 */
अचिन्हित पूर्णांक blkdev_nr_zones(काष्ठा gendisk *disk)
अणु
	sector_t zone_sectors = blk_queue_zone_sectors(disk->queue);

	अगर (!blk_queue_is_zoned(disk->queue))
		वापस 0;
	वापस (get_capacity(disk) + zone_sectors - 1) >> ilog2(zone_sectors);
पूर्ण
EXPORT_SYMBOL_GPL(blkdev_nr_zones);

/**
 * blkdev_report_zones - Get zones inक्रमmation
 * @bdev:	Target block device
 * @sector:	Sector from which to report zones
 * @nr_zones:	Maximum number of zones to report
 * @cb:		Callback function called क्रम each reported zone
 * @data:	Private data क्रम the callback
 *
 * Description:
 *    Get zone inक्रमmation starting from the zone containing @sector क्रम at most
 *    @nr_zones, and call @cb क्रम each zone reported by the device.
 *    To report all zones in a device starting from @sector, the BLK_ALL_ZONES
 *    स्थिरant can be passed to @nr_zones.
 *    Returns the number of zones reported by the device, or a negative त्रुटि_सं
 *    value in हाल of failure.
 *
 *    Note: The caller must use meदो_स्मृति_noXX_save/restore() calls to control
 *    memory allocations करोne within this function.
 */
पूर्णांक blkdev_report_zones(काष्ठा block_device *bdev, sector_t sector,
			अचिन्हित पूर्णांक nr_zones, report_zones_cb cb, व्योम *data)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	sector_t capacity = get_capacity(disk);

	अगर (!blk_queue_is_zoned(bdev_get_queue(bdev)) ||
	    WARN_ON_ONCE(!disk->fops->report_zones))
		वापस -EOPNOTSUPP;

	अगर (!nr_zones || sector >= capacity)
		वापस 0;

	वापस disk->fops->report_zones(disk, sector, nr_zones, cb, data);
पूर्ण
EXPORT_SYMBOL_GPL(blkdev_report_zones);

अटल अंतरभूत bool blkdev_allow_reset_all_zones(काष्ठा block_device *bdev,
						sector_t sector,
						sector_t nr_sectors)
अणु
	अगर (!blk_queue_zone_resetall(bdev_get_queue(bdev)))
		वापस false;

	/*
	 * REQ_OP_ZONE_RESET_ALL can be executed only अगर the number of sectors
	 * of the applicable zone range is the entire disk.
	 */
	वापस !sector && nr_sectors == get_capacity(bdev->bd_disk);
पूर्ण

/**
 * blkdev_zone_mgmt - Execute a zone management operation on a range of zones
 * @bdev:	Target block device
 * @op:		Operation to be perक्रमmed on the zones
 * @sector:	Start sector of the first zone to operate on
 * @nr_sectors:	Number of sectors, should be at least the length of one zone and
 *		must be zone size aligned.
 * @gfp_mask:	Memory allocation flags (क्रम bio_alloc)
 *
 * Description:
 *    Perक्रमm the specअगरied operation on the range of zones specअगरied by
 *    @sector..@sector+@nr_sectors. Specअगरying the entire disk sector range
 *    is valid, but the specअगरied range should not contain conventional zones.
 *    The operation to execute on each zone can be a zone reset, खोलो, बंद
 *    or finish request.
 */
पूर्णांक blkdev_zone_mgmt(काष्ठा block_device *bdev, क्रमागत req_opf op,
		     sector_t sector, sector_t nr_sectors,
		     gfp_t gfp_mask)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	sector_t zone_sectors = blk_queue_zone_sectors(q);
	sector_t capacity = get_capacity(bdev->bd_disk);
	sector_t end_sector = sector + nr_sectors;
	काष्ठा bio *bio = शून्य;
	पूर्णांक ret;

	अगर (!blk_queue_is_zoned(q))
		वापस -EOPNOTSUPP;

	अगर (bdev_पढ़ो_only(bdev))
		वापस -EPERM;

	अगर (!op_is_zone_mgmt(op))
		वापस -EOPNOTSUPP;

	अगर (end_sector <= sector || end_sector > capacity)
		/* Out of range */
		वापस -EINVAL;

	/* Check alignment (handle eventual smaller last zone) */
	अगर (sector & (zone_sectors - 1))
		वापस -EINVAL;

	अगर ((nr_sectors & (zone_sectors - 1)) && end_sector != capacity)
		वापस -EINVAL;

	जबतक (sector < end_sector) अणु
		bio = blk_next_bio(bio, 0, gfp_mask);
		bio_set_dev(bio, bdev);

		/*
		 * Special हाल क्रम the zone reset operation that reset all
		 * zones, this is useful क्रम applications like mkfs.
		 */
		अगर (op == REQ_OP_ZONE_RESET &&
		    blkdev_allow_reset_all_zones(bdev, sector, nr_sectors)) अणु
			bio->bi_opf = REQ_OP_ZONE_RESET_ALL | REQ_SYNC;
			अवरोध;
		पूर्ण

		bio->bi_opf = op | REQ_SYNC;
		bio->bi_iter.bi_sector = sector;
		sector += zone_sectors;

		/* This may take a जबतक, so be nice to others */
		cond_resched();
	पूर्ण

	ret = submit_bio_रुको(bio);
	bio_put(bio);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blkdev_zone_mgmt);

काष्ठा zone_report_args अणु
	काष्ठा blk_zone __user *zones;
पूर्ण;

अटल पूर्णांक blkdev_copy_zone_to_user(काष्ठा blk_zone *zone, अचिन्हित पूर्णांक idx,
				    व्योम *data)
अणु
	काष्ठा zone_report_args *args = data;

	अगर (copy_to_user(&args->zones[idx], zone, माप(काष्ठा blk_zone)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * BLKREPORTZONE ioctl processing.
 * Called from blkdev_ioctl.
 */
पूर्णांक blkdev_report_zones_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा zone_report_args args;
	काष्ठा request_queue *q;
	काष्ठा blk_zone_report rep;
	पूर्णांक ret;

	अगर (!argp)
		वापस -EINVAL;

	q = bdev_get_queue(bdev);
	अगर (!q)
		वापस -ENXIO;

	अगर (!blk_queue_is_zoned(q))
		वापस -ENOTTY;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (copy_from_user(&rep, argp, माप(काष्ठा blk_zone_report)))
		वापस -EFAULT;

	अगर (!rep.nr_zones)
		वापस -EINVAL;

	args.zones = argp + माप(काष्ठा blk_zone_report);
	ret = blkdev_report_zones(bdev, rep.sector, rep.nr_zones,
				  blkdev_copy_zone_to_user, &args);
	अगर (ret < 0)
		वापस ret;

	rep.nr_zones = ret;
	rep.flags = BLK_ZONE_REP_CAPACITY;
	अगर (copy_to_user(argp, &rep, माप(काष्ठा blk_zone_report)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक blkdev_truncate_zone_range(काष्ठा block_device *bdev, भ_शेषe_t mode,
				      स्थिर काष्ठा blk_zone_range *zrange)
अणु
	loff_t start, end;

	अगर (zrange->sector + zrange->nr_sectors <= zrange->sector ||
	    zrange->sector + zrange->nr_sectors > get_capacity(bdev->bd_disk))
		/* Out of range */
		वापस -EINVAL;

	start = zrange->sector << SECTOR_SHIFT;
	end = ((zrange->sector + zrange->nr_sectors) << SECTOR_SHIFT) - 1;

	वापस truncate_bdev_range(bdev, mode, start, end);
पूर्ण

/*
 * BLKRESETZONE, BLKOPENZONE, BLKCLOSEZONE and BLKFINISHZONE ioctl processing.
 * Called from blkdev_ioctl.
 */
पूर्णांक blkdev_zone_mgmt_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा request_queue *q;
	काष्ठा blk_zone_range zrange;
	क्रमागत req_opf op;
	पूर्णांक ret;

	अगर (!argp)
		वापस -EINVAL;

	q = bdev_get_queue(bdev);
	अगर (!q)
		वापस -ENXIO;

	अगर (!blk_queue_is_zoned(q))
		वापस -ENOTTY;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	अगर (!(mode & FMODE_WRITE))
		वापस -EBADF;

	अगर (copy_from_user(&zrange, argp, माप(काष्ठा blk_zone_range)))
		वापस -EFAULT;

	चयन (cmd) अणु
	हाल BLKRESETZONE:
		op = REQ_OP_ZONE_RESET;

		/* Invalidate the page cache, including dirty pages. */
		ret = blkdev_truncate_zone_range(bdev, mode, &zrange);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल BLKOPENZONE:
		op = REQ_OP_ZONE_OPEN;
		अवरोध;
	हाल BLKCLOSEZONE:
		op = REQ_OP_ZONE_CLOSE;
		अवरोध;
	हाल BLKFINISHZONE:
		op = REQ_OP_ZONE_FINISH;
		अवरोध;
	शेष:
		वापस -ENOTTY;
	पूर्ण

	ret = blkdev_zone_mgmt(bdev, op, zrange.sector, zrange.nr_sectors,
			       GFP_KERNEL);

	/*
	 * Invalidate the page cache again क्रम zone reset: ग_लिखोs can only be
	 * direct क्रम zoned devices so concurrent ग_लिखोs would not add any page
	 * to the page cache after/during reset. The page cache may be filled
	 * again due to concurrent पढ़ोs though and dropping the pages क्रम
	 * these is fine.
	 */
	अगर (!ret && cmd == BLKRESETZONE)
		ret = blkdev_truncate_zone_range(bdev, mode, &zrange);

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *blk_alloc_zone_biपंचांगap(पूर्णांक node,
						   अचिन्हित पूर्णांक nr_zones)
अणु
	वापस kसुस्मृति_node(BITS_TO_LONGS(nr_zones), माप(अचिन्हित दीर्घ),
			    GFP_NOIO, node);
पूर्ण

व्योम blk_queue_मुक्त_zone_biपंचांगaps(काष्ठा request_queue *q)
अणु
	kमुक्त(q->conv_zones_biपंचांगap);
	q->conv_zones_biपंचांगap = शून्य;
	kमुक्त(q->seq_zones_wlock);
	q->seq_zones_wlock = शून्य;
पूर्ण

काष्ठा blk_revalidate_zone_args अणु
	काष्ठा gendisk	*disk;
	अचिन्हित दीर्घ	*conv_zones_biपंचांगap;
	अचिन्हित दीर्घ	*seq_zones_wlock;
	अचिन्हित पूर्णांक	nr_zones;
	sector_t	zone_sectors;
	sector_t	sector;
पूर्ण;

/*
 * Helper function to check the validity of zones of a zoned block device.
 */
अटल पूर्णांक blk_revalidate_zone_cb(काष्ठा blk_zone *zone, अचिन्हित पूर्णांक idx,
				  व्योम *data)
अणु
	काष्ठा blk_revalidate_zone_args *args = data;
	काष्ठा gendisk *disk = args->disk;
	काष्ठा request_queue *q = disk->queue;
	sector_t capacity = get_capacity(disk);

	/*
	 * All zones must have the same size, with the exception on an eventual
	 * smaller last zone.
	 */
	अगर (zone->start == 0) अणु
		अगर (zone->len == 0 || !is_घातer_of_2(zone->len)) अणु
			pr_warn("%s: Invalid zoned device with non power of two zone size (%llu)\n",
				disk->disk_name, zone->len);
			वापस -ENODEV;
		पूर्ण

		args->zone_sectors = zone->len;
		args->nr_zones = (capacity + zone->len - 1) >> ilog2(zone->len);
	पूर्ण अन्यथा अगर (zone->start + args->zone_sectors < capacity) अणु
		अगर (zone->len != args->zone_sectors) अणु
			pr_warn("%s: Invalid zoned device with non constant zone size\n",
				disk->disk_name);
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (zone->len > args->zone_sectors) अणु
			pr_warn("%s: Invalid zoned device with larger last zone size\n",
				disk->disk_name);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* Check क्रम holes in the zone report */
	अगर (zone->start != args->sector) अणु
		pr_warn("%s: Zone gap at sectors %llu..%llu\n",
			disk->disk_name, args->sector, zone->start);
		वापस -ENODEV;
	पूर्ण

	/* Check zone type */
	चयन (zone->type) अणु
	हाल BLK_ZONE_TYPE_CONVENTIONAL:
		अगर (!args->conv_zones_biपंचांगap) अणु
			args->conv_zones_biपंचांगap =
				blk_alloc_zone_biपंचांगap(q->node, args->nr_zones);
			अगर (!args->conv_zones_biपंचांगap)
				वापस -ENOMEM;
		पूर्ण
		set_bit(idx, args->conv_zones_biपंचांगap);
		अवरोध;
	हाल BLK_ZONE_TYPE_SEQWRITE_REQ:
	हाल BLK_ZONE_TYPE_SEQWRITE_PREF:
		अगर (!args->seq_zones_wlock) अणु
			args->seq_zones_wlock =
				blk_alloc_zone_biपंचांगap(q->node, args->nr_zones);
			अगर (!args->seq_zones_wlock)
				वापस -ENOMEM;
		पूर्ण
		अवरोध;
	शेष:
		pr_warn("%s: Invalid zone type 0x%x at sectors %llu\n",
			disk->disk_name, (पूर्णांक)zone->type, zone->start);
		वापस -ENODEV;
	पूर्ण

	args->sector += zone->len;
	वापस 0;
पूर्ण

/**
 * blk_revalidate_disk_zones - (re)allocate and initialize zone biपंचांगaps
 * @disk:	Target disk
 * @update_driver_data:	Callback to update driver data on the frozen disk
 *
 * Helper function क्रम low-level device drivers to (re) allocate and initialize
 * a disk request queue zone biपंचांगaps. This functions should normally be called
 * within the disk ->revalidate method क्रम blk-mq based drivers.  For BIO based
 * drivers only q->nr_zones needs to be updated so that the sysfs exposed value
 * is correct.
 * If the @update_driver_data callback function is not शून्य, the callback is
 * executed with the device request queue frozen after all zones have been
 * checked.
 */
पूर्णांक blk_revalidate_disk_zones(काष्ठा gendisk *disk,
			      व्योम (*update_driver_data)(काष्ठा gendisk *disk))
अणु
	काष्ठा request_queue *q = disk->queue;
	काष्ठा blk_revalidate_zone_args args = अणु
		.disk		= disk,
	पूर्ण;
	अचिन्हित पूर्णांक noio_flag;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(!blk_queue_is_zoned(q)))
		वापस -EIO;
	अगर (WARN_ON_ONCE(!queue_is_mq(q)))
		वापस -EIO;

	अगर (!get_capacity(disk))
		वापस -EIO;

	/*
	 * Ensure that all memory allocations in this context are करोne as अगर
	 * GFP_NOIO was specअगरied.
	 */
	noio_flag = meदो_स्मृति_noio_save();
	ret = disk->fops->report_zones(disk, 0, अच_पूर्णांक_उच्च,
				       blk_revalidate_zone_cb, &args);
	अगर (!ret) अणु
		pr_warn("%s: No zones reported\n", disk->disk_name);
		ret = -ENODEV;
	पूर्ण
	meदो_स्मृति_noio_restore(noio_flag);

	/*
	 * If zones where reported, make sure that the entire disk capacity
	 * has been checked.
	 */
	अगर (ret > 0 && args.sector != get_capacity(disk)) अणु
		pr_warn("%s: Missing zones from sector %llu\n",
			disk->disk_name, args.sector);
		ret = -ENODEV;
	पूर्ण

	/*
	 * Install the new biपंचांगaps and update nr_zones only once the queue is
	 * stopped and all I/Os are completed (i.e. a scheduler is not
	 * referencing the biपंचांगaps).
	 */
	blk_mq_मुक्तze_queue(q);
	अगर (ret > 0) अणु
		blk_queue_chunk_sectors(q, args.zone_sectors);
		q->nr_zones = args.nr_zones;
		swap(q->seq_zones_wlock, args.seq_zones_wlock);
		swap(q->conv_zones_biपंचांगap, args.conv_zones_biपंचांगap);
		अगर (update_driver_data)
			update_driver_data(disk);
		ret = 0;
	पूर्ण अन्यथा अणु
		pr_warn("%s: failed to revalidate zones\n", disk->disk_name);
		blk_queue_मुक्त_zone_biपंचांगaps(q);
	पूर्ण
	blk_mq_unमुक्तze_queue(q);

	kमुक्त(args.seq_zones_wlock);
	kमुक्त(args.conv_zones_biपंचांगap);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blk_revalidate_disk_zones);

व्योम blk_queue_clear_zone_settings(काष्ठा request_queue *q)
अणु
	blk_mq_मुक्तze_queue(q);

	blk_queue_मुक्त_zone_biपंचांगaps(q);
	blk_queue_flag_clear(QUEUE_FLAG_ZONE_RESETALL, q);
	q->required_elevator_features &= ~ELEVATOR_F_ZBD_SEQ_WRITE;
	q->nr_zones = 0;
	q->max_खोलो_zones = 0;
	q->max_active_zones = 0;
	q->limits.chunk_sectors = 0;
	q->limits.zone_ग_लिखो_granularity = 0;
	q->limits.max_zone_append_sectors = 0;

	blk_mq_unमुक्तze_queue(q);
पूर्ण
