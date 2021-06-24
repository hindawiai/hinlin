<शैली गुरु>
/*
 * Copyright (C) 2001, 2002 Sistina Software (UK) Limited.
 * Copyright (C) 2004-2008 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-core.h"
#समावेश "dm-rq.h"
#समावेश "dm-uevent.h"

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/blkpg.h>
#समावेश <linux/bपन.स>
#समावेश <linux/mempool.h>
#समावेश <linux/dax.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/uपन.स>
#समावेश <linux/hdreg.h>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>
#समावेश <linux/pr.h>
#समावेश <linux/refcount.h>
#समावेश <linux/part_स्थिति.स>
#समावेश <linux/blk-crypto.h>
#समावेश <linux/keyslot-manager.h>

#घोषणा DM_MSG_PREFIX "core"

/*
 * Cookies are numeric values sent with CHANGE and REMOVE
 * uevents जबतक resuming, removing or renaming the device.
 */
#घोषणा DM_COOKIE_ENV_VAR_NAME "DM_COOKIE"
#घोषणा DM_COOKIE_LENGTH 24

अटल स्थिर अक्षर *_name = DM_NAME;

अटल अचिन्हित पूर्णांक major = 0;
अटल अचिन्हित पूर्णांक _major = 0;

अटल DEFINE_IDR(_minor_idr);

अटल DEFINE_SPINLOCK(_minor_lock);

अटल व्योम करो_deferred_हटाओ(काष्ठा work_काष्ठा *w);

अटल DECLARE_WORK(deferred_हटाओ_work, करो_deferred_हटाओ);

अटल काष्ठा workqueue_काष्ठा *deferred_हटाओ_workqueue;

atomic_t dm_global_event_nr = ATOMIC_INIT(0);
DECLARE_WAIT_QUEUE_HEAD(dm_global_eventq);

व्योम dm_issue_global_event(व्योम)
अणु
	atomic_inc(&dm_global_event_nr);
	wake_up(&dm_global_eventq);
पूर्ण

/*
 * One of these is allocated (on-stack) per original bio.
 */
काष्ठा clone_info अणु
	काष्ठा dm_table *map;
	काष्ठा bio *bio;
	काष्ठा dm_io *io;
	sector_t sector;
	अचिन्हित sector_count;
पूर्ण;

/*
 * One of these is allocated per clone bio.
 */
#घोषणा DM_TIO_MAGIC 7282014
काष्ठा dm_target_io अणु
	अचिन्हित magic;
	काष्ठा dm_io *io;
	काष्ठा dm_target *ti;
	अचिन्हित target_bio_nr;
	अचिन्हित *len_ptr;
	bool inside_dm_io;
	काष्ठा bio clone;
पूर्ण;

/*
 * One of these is allocated per original bio.
 * It contains the first clone used क्रम that original.
 */
#घोषणा DM_IO_MAGIC 5191977
काष्ठा dm_io अणु
	अचिन्हित magic;
	काष्ठा mapped_device *md;
	blk_status_t status;
	atomic_t io_count;
	काष्ठा bio *orig_bio;
	अचिन्हित दीर्घ start_समय;
	spinlock_t endio_lock;
	काष्ठा dm_stats_aux stats_aux;
	/* last member of dm_target_io is 'struct bio' */
	काष्ठा dm_target_io tio;
पूर्ण;

#घोषणा DM_TARGET_IO_BIO_OFFSET (दुरत्व(काष्ठा dm_target_io, clone))
#घोषणा DM_IO_BIO_OFFSET \
	(दुरत्व(काष्ठा dm_target_io, clone) + दुरत्व(काष्ठा dm_io, tio))

व्योम *dm_per_bio_data(काष्ठा bio *bio, माप_प्रकार data_size)
अणु
	काष्ठा dm_target_io *tio = container_of(bio, काष्ठा dm_target_io, clone);
	अगर (!tio->inside_dm_io)
		वापस (अक्षर *)bio - DM_TARGET_IO_BIO_OFFSET - data_size;
	वापस (अक्षर *)bio - DM_IO_BIO_OFFSET - data_size;
पूर्ण
EXPORT_SYMBOL_GPL(dm_per_bio_data);

काष्ठा bio *dm_bio_from_per_bio_data(व्योम *data, माप_प्रकार data_size)
अणु
	काष्ठा dm_io *io = (काष्ठा dm_io *)((अक्षर *)data + data_size);
	अगर (io->magic == DM_IO_MAGIC)
		वापस (काष्ठा bio *)((अक्षर *)io + DM_IO_BIO_OFFSET);
	BUG_ON(io->magic != DM_TIO_MAGIC);
	वापस (काष्ठा bio *)((अक्षर *)io + DM_TARGET_IO_BIO_OFFSET);
पूर्ण
EXPORT_SYMBOL_GPL(dm_bio_from_per_bio_data);

अचिन्हित dm_bio_get_target_bio_nr(स्थिर काष्ठा bio *bio)
अणु
	वापस container_of(bio, काष्ठा dm_target_io, clone)->target_bio_nr;
पूर्ण
EXPORT_SYMBOL_GPL(dm_bio_get_target_bio_nr);

#घोषणा MINOR_ALLOCED ((व्योम *)-1)

/*
 * Bits क्रम the md->flags field.
 */
#घोषणा DMF_BLOCK_IO_FOR_SUSPEND 0
#घोषणा DMF_SUSPENDED 1
#घोषणा DMF_FROZEN 2
#घोषणा DMF_FREEING 3
#घोषणा DMF_DELETING 4
#घोषणा DMF_NOFLUSH_SUSPENDING 5
#घोषणा DMF_DEFERRED_REMOVE 6
#घोषणा DMF_SUSPENDED_INTERNALLY 7
#घोषणा DMF_POST_SUSPENDING 8

#घोषणा DM_NUMA_NODE NUMA_NO_NODE
अटल पूर्णांक dm_numa_node = DM_NUMA_NODE;

#घोषणा DEFAULT_SWAP_BIOS	(8 * 1048576 / PAGE_SIZE)
अटल पूर्णांक swap_bios = DEFAULT_SWAP_BIOS;
अटल पूर्णांक get_swap_bios(व्योम)
अणु
	पूर्णांक latch = READ_ONCE(swap_bios);
	अगर (unlikely(latch <= 0))
		latch = DEFAULT_SWAP_BIOS;
	वापस latch;
पूर्ण

/*
 * For mempools pre-allocation at the table loading समय.
 */
काष्ठा dm_md_mempools अणु
	काष्ठा bio_set bs;
	काष्ठा bio_set io_bs;
पूर्ण;

काष्ठा table_device अणु
	काष्ठा list_head list;
	refcount_t count;
	काष्ठा dm_dev dm_dev;
पूर्ण;

/*
 * Bio-based DM's mempools' reserved IOs set by the user.
 */
#घोषणा RESERVED_BIO_BASED_IOS		16
अटल अचिन्हित reserved_bio_based_ios = RESERVED_BIO_BASED_IOS;

अटल पूर्णांक __dm_get_module_param_पूर्णांक(पूर्णांक *module_param, पूर्णांक min, पूर्णांक max)
अणु
	पूर्णांक param = READ_ONCE(*module_param);
	पूर्णांक modअगरied_param = 0;
	bool modअगरied = true;

	अगर (param < min)
		modअगरied_param = min;
	अन्यथा अगर (param > max)
		modअगरied_param = max;
	अन्यथा
		modअगरied = false;

	अगर (modअगरied) अणु
		(व्योम)cmpxchg(module_param, param, modअगरied_param);
		param = modअगरied_param;
	पूर्ण

	वापस param;
पूर्ण

अचिन्हित __dm_get_module_param(अचिन्हित *module_param,
			       अचिन्हित def, अचिन्हित max)
अणु
	अचिन्हित param = READ_ONCE(*module_param);
	अचिन्हित modअगरied_param = 0;

	अगर (!param)
		modअगरied_param = def;
	अन्यथा अगर (param > max)
		modअगरied_param = max;

	अगर (modअगरied_param) अणु
		(व्योम)cmpxchg(module_param, param, modअगरied_param);
		param = modअगरied_param;
	पूर्ण

	वापस param;
पूर्ण

अचिन्हित dm_get_reserved_bio_based_ios(व्योम)
अणु
	वापस __dm_get_module_param(&reserved_bio_based_ios,
				     RESERVED_BIO_BASED_IOS, DM_RESERVED_MAX_IOS);
पूर्ण
EXPORT_SYMBOL_GPL(dm_get_reserved_bio_based_ios);

अटल अचिन्हित dm_get_numa_node(व्योम)
अणु
	वापस __dm_get_module_param_पूर्णांक(&dm_numa_node,
					 DM_NUMA_NODE, num_online_nodes() - 1);
पूर्ण

अटल पूर्णांक __init local_init(व्योम)
अणु
	पूर्णांक r;

	r = dm_uevent_init();
	अगर (r)
		वापस r;

	deferred_हटाओ_workqueue = alloc_workqueue("kdmremove", WQ_UNBOUND, 1);
	अगर (!deferred_हटाओ_workqueue) अणु
		r = -ENOMEM;
		जाओ out_uevent_निकास;
	पूर्ण

	_major = major;
	r = रेजिस्टर_blkdev(_major, _name);
	अगर (r < 0)
		जाओ out_मुक्त_workqueue;

	अगर (!_major)
		_major = r;

	वापस 0;

out_मुक्त_workqueue:
	destroy_workqueue(deferred_हटाओ_workqueue);
out_uevent_निकास:
	dm_uevent_निकास();

	वापस r;
पूर्ण

अटल व्योम local_निकास(व्योम)
अणु
	flush_scheduled_work();
	destroy_workqueue(deferred_हटाओ_workqueue);

	unरेजिस्टर_blkdev(_major, _name);
	dm_uevent_निकास();

	_major = 0;

	DMINFO("cleaned up");
पूर्ण

अटल पूर्णांक (*_inits[])(व्योम) __initdata = अणु
	local_init,
	dm_target_init,
	dm_linear_init,
	dm_stripe_init,
	dm_io_init,
	dm_kcopyd_init,
	dm_पूर्णांकerface_init,
	dm_statistics_init,
पूर्ण;

अटल व्योम (*_निकासs[])(व्योम) = अणु
	local_निकास,
	dm_target_निकास,
	dm_linear_निकास,
	dm_stripe_निकास,
	dm_io_निकास,
	dm_kcopyd_निकास,
	dm_पूर्णांकerface_निकास,
	dm_statistics_निकास,
पूर्ण;

अटल पूर्णांक __init dm_init(व्योम)
अणु
	स्थिर पूर्णांक count = ARRAY_SIZE(_inits);

	पूर्णांक r, i;

	क्रम (i = 0; i < count; i++) अणु
		r = _inits[i]();
		अगर (r)
			जाओ bad;
	पूर्ण

	वापस 0;

      bad:
	जबतक (i--)
		_निकासs[i]();

	वापस r;
पूर्ण

अटल व्योम __निकास dm_निकास(व्योम)
अणु
	पूर्णांक i = ARRAY_SIZE(_निकासs);

	जबतक (i--)
		_निकासs[i]();

	/*
	 * Should be empty by this poपूर्णांक.
	 */
	idr_destroy(&_minor_idr);
पूर्ण

/*
 * Block device functions
 */
पूर्णांक dm_deleting_md(काष्ठा mapped_device *md)
अणु
	वापस test_bit(DMF_DELETING, &md->flags);
पूर्ण

अटल पूर्णांक dm_blk_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा mapped_device *md;

	spin_lock(&_minor_lock);

	md = bdev->bd_disk->निजी_data;
	अगर (!md)
		जाओ out;

	अगर (test_bit(DMF_FREEING, &md->flags) ||
	    dm_deleting_md(md)) अणु
		md = शून्य;
		जाओ out;
	पूर्ण

	dm_get(md);
	atomic_inc(&md->खोलो_count);
out:
	spin_unlock(&_minor_lock);

	वापस md ? 0 : -ENXIO;
पूर्ण

अटल व्योम dm_blk_बंद(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा mapped_device *md;

	spin_lock(&_minor_lock);

	md = disk->निजी_data;
	अगर (WARN_ON(!md))
		जाओ out;

	अगर (atomic_dec_and_test(&md->खोलो_count) &&
	    (test_bit(DMF_DEFERRED_REMOVE, &md->flags)))
		queue_work(deferred_हटाओ_workqueue, &deferred_हटाओ_work);

	dm_put(md);
out:
	spin_unlock(&_minor_lock);
पूर्ण

पूर्णांक dm_खोलो_count(काष्ठा mapped_device *md)
अणु
	वापस atomic_पढ़ो(&md->खोलो_count);
पूर्ण

/*
 * Guarantees nothing is using the device beक्रमe it's deleted.
 */
पूर्णांक dm_lock_क्रम_deletion(काष्ठा mapped_device *md, bool mark_deferred, bool only_deferred)
अणु
	पूर्णांक r = 0;

	spin_lock(&_minor_lock);

	अगर (dm_खोलो_count(md)) अणु
		r = -EBUSY;
		अगर (mark_deferred)
			set_bit(DMF_DEFERRED_REMOVE, &md->flags);
	पूर्ण अन्यथा अगर (only_deferred && !test_bit(DMF_DEFERRED_REMOVE, &md->flags))
		r = -EEXIST;
	अन्यथा
		set_bit(DMF_DELETING, &md->flags);

	spin_unlock(&_minor_lock);

	वापस r;
पूर्ण

पूर्णांक dm_cancel_deferred_हटाओ(काष्ठा mapped_device *md)
अणु
	पूर्णांक r = 0;

	spin_lock(&_minor_lock);

	अगर (test_bit(DMF_DELETING, &md->flags))
		r = -EBUSY;
	अन्यथा
		clear_bit(DMF_DEFERRED_REMOVE, &md->flags);

	spin_unlock(&_minor_lock);

	वापस r;
पूर्ण

अटल व्योम करो_deferred_हटाओ(काष्ठा work_काष्ठा *w)
अणु
	dm_deferred_हटाओ();
पूर्ण

अटल पूर्णांक dm_blk_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा mapped_device *md = bdev->bd_disk->निजी_data;

	वापस dm_get_geometry(md, geo);
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_ZONED
पूर्णांक dm_report_zones_cb(काष्ठा blk_zone *zone, अचिन्हित पूर्णांक idx, व्योम *data)
अणु
	काष्ठा dm_report_zones_args *args = data;
	sector_t sector_dअगरf = args->tgt->begin - args->start;

	/*
	 * Ignore zones beyond the target range.
	 */
	अगर (zone->start >= args->start + args->tgt->len)
		वापस 0;

	/*
	 * Remap the start sector and ग_लिखो poपूर्णांकer position of the zone
	 * to match its position in the target range.
	 */
	zone->start += sector_dअगरf;
	अगर (zone->type != BLK_ZONE_TYPE_CONVENTIONAL) अणु
		अगर (zone->cond == BLK_ZONE_COND_FULL)
			zone->wp = zone->start + zone->len;
		अन्यथा अगर (zone->cond == BLK_ZONE_COND_EMPTY)
			zone->wp = zone->start;
		अन्यथा
			zone->wp += sector_dअगरf;
	पूर्ण

	args->next_sector = zone->start + zone->len;
	वापस args->orig_cb(zone, args->zone_idx++, args->orig_data);
पूर्ण
EXPORT_SYMBOL_GPL(dm_report_zones_cb);

अटल पूर्णांक dm_blk_report_zones(काष्ठा gendisk *disk, sector_t sector,
		अचिन्हित पूर्णांक nr_zones, report_zones_cb cb, व्योम *data)
अणु
	काष्ठा mapped_device *md = disk->निजी_data;
	काष्ठा dm_table *map;
	पूर्णांक srcu_idx, ret;
	काष्ठा dm_report_zones_args args = अणु
		.next_sector = sector,
		.orig_data = data,
		.orig_cb = cb,
	पूर्ण;

	अगर (dm_suspended_md(md))
		वापस -EAGAIN;

	map = dm_get_live_table(md, &srcu_idx);
	अगर (!map) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	करो अणु
		काष्ठा dm_target *tgt;

		tgt = dm_table_find_target(map, args.next_sector);
		अगर (WARN_ON_ONCE(!tgt->type->report_zones)) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण

		args.tgt = tgt;
		ret = tgt->type->report_zones(tgt, &args,
					      nr_zones - args.zone_idx);
		अगर (ret < 0)
			जाओ out;
	पूर्ण जबतक (args.zone_idx < nr_zones &&
		 args.next_sector < get_capacity(disk));

	ret = args.zone_idx;
out:
	dm_put_live_table(md, srcu_idx);
	वापस ret;
पूर्ण
#अन्यथा
#घोषणा dm_blk_report_zones		शून्य
#पूर्ण_अगर /* CONFIG_BLK_DEV_ZONED */

अटल पूर्णांक dm_prepare_ioctl(काष्ठा mapped_device *md, पूर्णांक *srcu_idx,
			    काष्ठा block_device **bdev)
अणु
	काष्ठा dm_target *tgt;
	काष्ठा dm_table *map;
	पूर्णांक r;

retry:
	r = -ENOTTY;
	map = dm_get_live_table(md, srcu_idx);
	अगर (!map || !dm_table_get_size(map))
		वापस r;

	/* We only support devices that have a single target */
	अगर (dm_table_get_num_tarमाला_लो(map) != 1)
		वापस r;

	tgt = dm_table_get_target(map, 0);
	अगर (!tgt->type->prepare_ioctl)
		वापस r;

	अगर (dm_suspended_md(md))
		वापस -EAGAIN;

	r = tgt->type->prepare_ioctl(tgt, bdev);
	अगर (r == -ENOTCONN && !fatal_संकेत_pending(current)) अणु
		dm_put_live_table(md, *srcu_idx);
		msleep(10);
		जाओ retry;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम dm_unprepare_ioctl(काष्ठा mapped_device *md, पूर्णांक srcu_idx)
अणु
	dm_put_live_table(md, srcu_idx);
पूर्ण

अटल पूर्णांक dm_blk_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mapped_device *md = bdev->bd_disk->निजी_data;
	पूर्णांक r, srcu_idx;

	r = dm_prepare_ioctl(md, &srcu_idx, &bdev);
	अगर (r < 0)
		जाओ out;

	अगर (r > 0) अणु
		/*
		 * Target determined this ioctl is being issued against a
		 * subset of the parent bdev; require extra privileges.
		 */
		अगर (!capable(CAP_SYS_RAWIO)) अणु
			DMDEBUG_LIMIT(
	"%s: sending ioctl %x to DM device without required privilege.",
				current->comm, cmd);
			r = -ENOIOCTLCMD;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!bdev->bd_disk->fops->ioctl)
		r = -ENOTTY;
	अन्यथा
		r = bdev->bd_disk->fops->ioctl(bdev, mode, cmd, arg);
out:
	dm_unprepare_ioctl(md, srcu_idx);
	वापस r;
पूर्ण

u64 dm_start_समय_ns_from_clone(काष्ठा bio *bio)
अणु
	काष्ठा dm_target_io *tio = container_of(bio, काष्ठा dm_target_io, clone);
	काष्ठा dm_io *io = tio->io;

	वापस jअगरfies_to_nsecs(io->start_समय);
पूर्ण
EXPORT_SYMBOL_GPL(dm_start_समय_ns_from_clone);

अटल व्योम start_io_acct(काष्ठा dm_io *io)
अणु
	काष्ठा mapped_device *md = io->md;
	काष्ठा bio *bio = io->orig_bio;

	io->start_समय = bio_start_io_acct(bio);
	अगर (unlikely(dm_stats_used(&md->stats)))
		dm_stats_account_io(&md->stats, bio_data_dir(bio),
				    bio->bi_iter.bi_sector, bio_sectors(bio),
				    false, 0, &io->stats_aux);
पूर्ण

अटल व्योम end_io_acct(काष्ठा dm_io *io)
अणु
	काष्ठा mapped_device *md = io->md;
	काष्ठा bio *bio = io->orig_bio;
	अचिन्हित दीर्घ duration = jअगरfies - io->start_समय;

	bio_end_io_acct(bio, io->start_समय);

	अगर (unlikely(dm_stats_used(&md->stats)))
		dm_stats_account_io(&md->stats, bio_data_dir(bio),
				    bio->bi_iter.bi_sector, bio_sectors(bio),
				    true, duration, &io->stats_aux);

	/* nudge anyone रुकोing on suspend queue */
	अगर (unlikely(wq_has_sleeper(&md->रुको)))
		wake_up(&md->रुको);
पूर्ण

अटल काष्ठा dm_io *alloc_io(काष्ठा mapped_device *md, काष्ठा bio *bio)
अणु
	काष्ठा dm_io *io;
	काष्ठा dm_target_io *tio;
	काष्ठा bio *clone;

	clone = bio_alloc_bioset(GFP_NOIO, 0, &md->io_bs);
	अगर (!clone)
		वापस शून्य;

	tio = container_of(clone, काष्ठा dm_target_io, clone);
	tio->inside_dm_io = true;
	tio->io = शून्य;

	io = container_of(tio, काष्ठा dm_io, tio);
	io->magic = DM_IO_MAGIC;
	io->status = 0;
	atomic_set(&io->io_count, 1);
	io->orig_bio = bio;
	io->md = md;
	spin_lock_init(&io->endio_lock);

	start_io_acct(io);

	वापस io;
पूर्ण

अटल व्योम मुक्त_io(काष्ठा mapped_device *md, काष्ठा dm_io *io)
अणु
	bio_put(&io->tio.clone);
पूर्ण

अटल काष्ठा dm_target_io *alloc_tio(काष्ठा clone_info *ci, काष्ठा dm_target *ti,
				      अचिन्हित target_bio_nr, gfp_t gfp_mask)
अणु
	काष्ठा dm_target_io *tio;

	अगर (!ci->io->tio.io) अणु
		/* the dm_target_io embedded in ci->io is available */
		tio = &ci->io->tio;
	पूर्ण अन्यथा अणु
		काष्ठा bio *clone = bio_alloc_bioset(gfp_mask, 0, &ci->io->md->bs);
		अगर (!clone)
			वापस शून्य;

		tio = container_of(clone, काष्ठा dm_target_io, clone);
		tio->inside_dm_io = false;
	पूर्ण

	tio->magic = DM_TIO_MAGIC;
	tio->io = ci->io;
	tio->ti = ti;
	tio->target_bio_nr = target_bio_nr;

	वापस tio;
पूर्ण

अटल व्योम मुक्त_tio(काष्ठा dm_target_io *tio)
अणु
	अगर (tio->inside_dm_io)
		वापस;
	bio_put(&tio->clone);
पूर्ण

/*
 * Add the bio to the list of deferred io.
 */
अटल व्योम queue_io(काष्ठा mapped_device *md, काष्ठा bio *bio)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&md->deferred_lock, flags);
	bio_list_add(&md->deferred, bio);
	spin_unlock_irqrestore(&md->deferred_lock, flags);
	queue_work(md->wq, &md->work);
पूर्ण

/*
 * Everyone (including functions in this file), should use this
 * function to access the md->map field, and make sure they call
 * dm_put_live_table() when finished.
 */
काष्ठा dm_table *dm_get_live_table(काष्ठा mapped_device *md, पूर्णांक *srcu_idx) __acquires(md->io_barrier)
अणु
	*srcu_idx = srcu_पढ़ो_lock(&md->io_barrier);

	वापस srcu_dereference(md->map, &md->io_barrier);
पूर्ण

व्योम dm_put_live_table(काष्ठा mapped_device *md, पूर्णांक srcu_idx) __releases(md->io_barrier)
अणु
	srcu_पढ़ो_unlock(&md->io_barrier, srcu_idx);
पूर्ण

व्योम dm_sync_table(काष्ठा mapped_device *md)
अणु
	synchronize_srcu(&md->io_barrier);
	synchronize_rcu_expedited();
पूर्ण

/*
 * A fast alternative to dm_get_live_table/dm_put_live_table.
 * The caller must not block between these two functions.
 */
अटल काष्ठा dm_table *dm_get_live_table_fast(काष्ठा mapped_device *md) __acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	वापस rcu_dereference(md->map);
पूर्ण

अटल व्योम dm_put_live_table_fast(काष्ठा mapped_device *md) __releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल अक्षर *_dm_claim_ptr = "I belong to device-mapper";

/*
 * Open a table device so we can use it as a map destination.
 */
अटल पूर्णांक खोलो_table_device(काष्ठा table_device *td, dev_t dev,
			     काष्ठा mapped_device *md)
अणु
	काष्ठा block_device *bdev;

	पूर्णांक r;

	BUG_ON(td->dm_dev.bdev);

	bdev = blkdev_get_by_dev(dev, td->dm_dev.mode | FMODE_EXCL, _dm_claim_ptr);
	अगर (IS_ERR(bdev))
		वापस PTR_ERR(bdev);

	r = bd_link_disk_holder(bdev, dm_disk(md));
	अगर (r) अणु
		blkdev_put(bdev, td->dm_dev.mode | FMODE_EXCL);
		वापस r;
	पूर्ण

	td->dm_dev.bdev = bdev;
	td->dm_dev.dax_dev = dax_get_by_host(bdev->bd_disk->disk_name);
	वापस 0;
पूर्ण

/*
 * Close a table device that we've been using.
 */
अटल व्योम बंद_table_device(काष्ठा table_device *td, काष्ठा mapped_device *md)
अणु
	अगर (!td->dm_dev.bdev)
		वापस;

	bd_unlink_disk_holder(td->dm_dev.bdev, dm_disk(md));
	blkdev_put(td->dm_dev.bdev, td->dm_dev.mode | FMODE_EXCL);
	put_dax(td->dm_dev.dax_dev);
	td->dm_dev.bdev = शून्य;
	td->dm_dev.dax_dev = शून्य;
पूर्ण

अटल काष्ठा table_device *find_table_device(काष्ठा list_head *l, dev_t dev,
					      भ_शेषe_t mode)
अणु
	काष्ठा table_device *td;

	list_क्रम_each_entry(td, l, list)
		अगर (td->dm_dev.bdev->bd_dev == dev && td->dm_dev.mode == mode)
			वापस td;

	वापस शून्य;
पूर्ण

पूर्णांक dm_get_table_device(काष्ठा mapped_device *md, dev_t dev, भ_शेषe_t mode,
			काष्ठा dm_dev **result)
अणु
	पूर्णांक r;
	काष्ठा table_device *td;

	mutex_lock(&md->table_devices_lock);
	td = find_table_device(&md->table_devices, dev, mode);
	अगर (!td) अणु
		td = kदो_स्मृति_node(माप(*td), GFP_KERNEL, md->numa_node_id);
		अगर (!td) अणु
			mutex_unlock(&md->table_devices_lock);
			वापस -ENOMEM;
		पूर्ण

		td->dm_dev.mode = mode;
		td->dm_dev.bdev = शून्य;

		अगर ((r = खोलो_table_device(td, dev, md))) अणु
			mutex_unlock(&md->table_devices_lock);
			kमुक्त(td);
			वापस r;
		पूर्ण

		क्रमmat_dev_t(td->dm_dev.name, dev);

		refcount_set(&td->count, 1);
		list_add(&td->list, &md->table_devices);
	पूर्ण अन्यथा अणु
		refcount_inc(&td->count);
	पूर्ण
	mutex_unlock(&md->table_devices_lock);

	*result = &td->dm_dev;
	वापस 0;
पूर्ण

व्योम dm_put_table_device(काष्ठा mapped_device *md, काष्ठा dm_dev *d)
अणु
	काष्ठा table_device *td = container_of(d, काष्ठा table_device, dm_dev);

	mutex_lock(&md->table_devices_lock);
	अगर (refcount_dec_and_test(&td->count)) अणु
		बंद_table_device(td, md);
		list_del(&td->list);
		kमुक्त(td);
	पूर्ण
	mutex_unlock(&md->table_devices_lock);
पूर्ण

अटल व्योम मुक्त_table_devices(काष्ठा list_head *devices)
अणु
	काष्ठा list_head *पंचांगp, *next;

	list_क्रम_each_safe(पंचांगp, next, devices) अणु
		काष्ठा table_device *td = list_entry(पंचांगp, काष्ठा table_device, list);

		DMWARN("dm_destroy: %s still exists with %d references",
		       td->dm_dev.name, refcount_पढ़ो(&td->count));
		kमुक्त(td);
	पूर्ण
पूर्ण

/*
 * Get the geometry associated with a dm device
 */
पूर्णांक dm_get_geometry(काष्ठा mapped_device *md, काष्ठा hd_geometry *geo)
अणु
	*geo = md->geometry;

	वापस 0;
पूर्ण

/*
 * Set the geometry of a device.
 */
पूर्णांक dm_set_geometry(काष्ठा mapped_device *md, काष्ठा hd_geometry *geo)
अणु
	sector_t sz = (sector_t)geo->cylinders * geo->heads * geo->sectors;

	अगर (geo->start > sz) अणु
		DMWARN("Start sector is beyond the geometry limits.");
		वापस -EINVAL;
	पूर्ण

	md->geometry = *geo;

	वापस 0;
पूर्ण

अटल पूर्णांक __noflush_suspending(काष्ठा mapped_device *md)
अणु
	वापस test_bit(DMF_NOFLUSH_SUSPENDING, &md->flags);
पूर्ण

/*
 * Decrements the number of outstanding ios that a bio has been
 * cloned पूर्णांकo, completing the original io अगर necc.
 */
अटल व्योम dec_pending(काष्ठा dm_io *io, blk_status_t error)
अणु
	अचिन्हित दीर्घ flags;
	blk_status_t io_error;
	काष्ठा bio *bio;
	काष्ठा mapped_device *md = io->md;

	/* Push-back supersedes any I/O errors */
	अगर (unlikely(error)) अणु
		spin_lock_irqsave(&io->endio_lock, flags);
		अगर (!(io->status == BLK_STS_DM_REQUEUE && __noflush_suspending(md)))
			io->status = error;
		spin_unlock_irqrestore(&io->endio_lock, flags);
	पूर्ण

	अगर (atomic_dec_and_test(&io->io_count)) अणु
		अगर (io->status == BLK_STS_DM_REQUEUE) अणु
			/*
			 * Target requested pushing back the I/O.
			 */
			spin_lock_irqsave(&md->deferred_lock, flags);
			अगर (__noflush_suspending(md))
				/* NOTE early वापस due to BLK_STS_DM_REQUEUE below */
				bio_list_add_head(&md->deferred, io->orig_bio);
			अन्यथा
				/* noflush suspend was पूर्णांकerrupted. */
				io->status = BLK_STS_IOERR;
			spin_unlock_irqrestore(&md->deferred_lock, flags);
		पूर्ण

		io_error = io->status;
		bio = io->orig_bio;
		end_io_acct(io);
		मुक्त_io(md, io);

		अगर (io_error == BLK_STS_DM_REQUEUE)
			वापस;

		अगर ((bio->bi_opf & REQ_PREFLUSH) && bio->bi_iter.bi_size) अणु
			/*
			 * Preflush करोne क्रम flush with data, reissue
			 * without REQ_PREFLUSH.
			 */
			bio->bi_opf &= ~REQ_PREFLUSH;
			queue_io(md, bio);
		पूर्ण अन्यथा अणु
			/* करोne with normal IO or empty flush */
			अगर (io_error)
				bio->bi_status = io_error;
			bio_endio(bio);
		पूर्ण
	पूर्ण
पूर्ण

व्योम disable_discard(काष्ठा mapped_device *md)
अणु
	काष्ठा queue_limits *limits = dm_get_queue_limits(md);

	/* device करोesn't really support DISCARD, disable it */
	limits->max_discard_sectors = 0;
	blk_queue_flag_clear(QUEUE_FLAG_DISCARD, md->queue);
पूर्ण

व्योम disable_ग_लिखो_same(काष्ठा mapped_device *md)
अणु
	काष्ठा queue_limits *limits = dm_get_queue_limits(md);

	/* device करोesn't really support WRITE SAME, disable it */
	limits->max_ग_लिखो_same_sectors = 0;
पूर्ण

व्योम disable_ग_लिखो_zeroes(काष्ठा mapped_device *md)
अणु
	काष्ठा queue_limits *limits = dm_get_queue_limits(md);

	/* device करोesn't really support WRITE ZEROES, disable it */
	limits->max_ग_लिखो_zeroes_sectors = 0;
पूर्ण

अटल bool swap_bios_limit(काष्ठा dm_target *ti, काष्ठा bio *bio)
अणु
	वापस unlikely((bio->bi_opf & REQ_SWAP) != 0) && unlikely(ti->limit_swap_bios);
पूर्ण

अटल व्योम clone_endio(काष्ठा bio *bio)
अणु
	blk_status_t error = bio->bi_status;
	काष्ठा dm_target_io *tio = container_of(bio, काष्ठा dm_target_io, clone);
	काष्ठा dm_io *io = tio->io;
	काष्ठा mapped_device *md = tio->io->md;
	dm_endio_fn endio = tio->ti->type->end_io;
	काष्ठा bio *orig_bio = io->orig_bio;
	काष्ठा request_queue *q = bio->bi_bdev->bd_disk->queue;

	अगर (unlikely(error == BLK_STS_TARGET)) अणु
		अगर (bio_op(bio) == REQ_OP_DISCARD &&
		    !q->limits.max_discard_sectors)
			disable_discard(md);
		अन्यथा अगर (bio_op(bio) == REQ_OP_WRITE_SAME &&
			 !q->limits.max_ग_लिखो_same_sectors)
			disable_ग_लिखो_same(md);
		अन्यथा अगर (bio_op(bio) == REQ_OP_WRITE_ZEROES &&
			 !q->limits.max_ग_लिखो_zeroes_sectors)
			disable_ग_लिखो_zeroes(md);
	पूर्ण

	/*
	 * For zone-append bios get offset in zone of the written
	 * sector and add that to the original bio sector pos.
	 */
	अगर (bio_op(orig_bio) == REQ_OP_ZONE_APPEND) अणु
		sector_t written_sector = bio->bi_iter.bi_sector;
		काष्ठा request_queue *q = orig_bio->bi_bdev->bd_disk->queue;
		u64 mask = (u64)blk_queue_zone_sectors(q) - 1;

		orig_bio->bi_iter.bi_sector += written_sector & mask;
	पूर्ण

	अगर (endio) अणु
		पूर्णांक r = endio(tio->ti, bio, &error);
		चयन (r) अणु
		हाल DM_ENDIO_REQUEUE:
			error = BLK_STS_DM_REQUEUE;
			fallthrough;
		हाल DM_ENDIO_DONE:
			अवरोध;
		हाल DM_ENDIO_INCOMPLETE:
			/* The target will handle the io */
			वापस;
		शेष:
			DMWARN("unimplemented target endio return value: %d", r);
			BUG();
		पूर्ण
	पूर्ण

	अगर (unlikely(swap_bios_limit(tio->ti, bio))) अणु
		काष्ठा mapped_device *md = io->md;
		up(&md->swap_bios_semaphore);
	पूर्ण

	मुक्त_tio(tio);
	dec_pending(io, error);
पूर्ण

/*
 * Return maximum size of I/O possible at the supplied sector up to the current
 * target boundary.
 */
अटल अंतरभूत sector_t max_io_len_target_boundary(काष्ठा dm_target *ti,
						  sector_t target_offset)
अणु
	वापस ti->len - target_offset;
पूर्ण

अटल sector_t max_io_len(काष्ठा dm_target *ti, sector_t sector)
अणु
	sector_t target_offset = dm_target_offset(ti, sector);
	sector_t len = max_io_len_target_boundary(ti, target_offset);
	sector_t max_len;

	/*
	 * Does the target need to split IO even further?
	 * - varied (per target) IO splitting is a tenet of DM; this
	 *   explains why stacked chunk_sectors based splitting via
	 *   blk_max_size_offset() isn't possible here. So pass in
	 *   ti->max_io_len to override stacked chunk_sectors.
	 */
	अगर (ti->max_io_len) अणु
		max_len = blk_max_size_offset(ti->table->md->queue,
					      target_offset, ti->max_io_len);
		अगर (len > max_len)
			len = max_len;
	पूर्ण

	वापस len;
पूर्ण

पूर्णांक dm_set_target_max_io_len(काष्ठा dm_target *ti, sector_t len)
अणु
	अगर (len > अच_पूर्णांक_उच्च) अणु
		DMERR("Specified maximum size of target IO (%llu) exceeds limit (%u)",
		      (अचिन्हित दीर्घ दीर्घ)len, अच_पूर्णांक_उच्च);
		ti->error = "Maximum size of target IO is too large";
		वापस -EINVAL;
	पूर्ण

	ti->max_io_len = (uपूर्णांक32_t) len;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dm_set_target_max_io_len);

अटल काष्ठा dm_target *dm_dax_get_live_target(काष्ठा mapped_device *md,
						sector_t sector, पूर्णांक *srcu_idx)
	__acquires(md->io_barrier)
अणु
	काष्ठा dm_table *map;
	काष्ठा dm_target *ti;

	map = dm_get_live_table(md, srcu_idx);
	अगर (!map)
		वापस शून्य;

	ti = dm_table_find_target(map, sector);
	अगर (!ti)
		वापस शून्य;

	वापस ti;
पूर्ण

अटल दीर्घ dm_dax_direct_access(काष्ठा dax_device *dax_dev, pgoff_t pgoff,
				 दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn)
अणु
	काष्ठा mapped_device *md = dax_get_निजी(dax_dev);
	sector_t sector = pgoff * PAGE_SECTORS;
	काष्ठा dm_target *ti;
	दीर्घ len, ret = -EIO;
	पूर्णांक srcu_idx;

	ti = dm_dax_get_live_target(md, sector, &srcu_idx);

	अगर (!ti)
		जाओ out;
	अगर (!ti->type->direct_access)
		जाओ out;
	len = max_io_len(ti, sector) / PAGE_SECTORS;
	अगर (len < 1)
		जाओ out;
	nr_pages = min(len, nr_pages);
	ret = ti->type->direct_access(ti, pgoff, nr_pages, kaddr, pfn);

 out:
	dm_put_live_table(md, srcu_idx);

	वापस ret;
पूर्ण

अटल bool dm_dax_supported(काष्ठा dax_device *dax_dev, काष्ठा block_device *bdev,
		पूर्णांक blocksize, sector_t start, sector_t len)
अणु
	काष्ठा mapped_device *md = dax_get_निजी(dax_dev);
	काष्ठा dm_table *map;
	bool ret = false;
	पूर्णांक srcu_idx;

	map = dm_get_live_table(md, &srcu_idx);
	अगर (!map)
		जाओ out;

	ret = dm_table_supports_dax(map, device_not_dax_capable, &blocksize);

out:
	dm_put_live_table(md, srcu_idx);

	वापस ret;
पूर्ण

अटल माप_प्रकार dm_dax_copy_from_iter(काष्ठा dax_device *dax_dev, pgoff_t pgoff,
				    व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	काष्ठा mapped_device *md = dax_get_निजी(dax_dev);
	sector_t sector = pgoff * PAGE_SECTORS;
	काष्ठा dm_target *ti;
	दीर्घ ret = 0;
	पूर्णांक srcu_idx;

	ti = dm_dax_get_live_target(md, sector, &srcu_idx);

	अगर (!ti)
		जाओ out;
	अगर (!ti->type->dax_copy_from_iter) अणु
		ret = copy_from_iter(addr, bytes, i);
		जाओ out;
	पूर्ण
	ret = ti->type->dax_copy_from_iter(ti, pgoff, addr, bytes, i);
 out:
	dm_put_live_table(md, srcu_idx);

	वापस ret;
पूर्ण

अटल माप_प्रकार dm_dax_copy_to_iter(काष्ठा dax_device *dax_dev, pgoff_t pgoff,
		व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	काष्ठा mapped_device *md = dax_get_निजी(dax_dev);
	sector_t sector = pgoff * PAGE_SECTORS;
	काष्ठा dm_target *ti;
	दीर्घ ret = 0;
	पूर्णांक srcu_idx;

	ti = dm_dax_get_live_target(md, sector, &srcu_idx);

	अगर (!ti)
		जाओ out;
	अगर (!ti->type->dax_copy_to_iter) अणु
		ret = copy_to_iter(addr, bytes, i);
		जाओ out;
	पूर्ण
	ret = ti->type->dax_copy_to_iter(ti, pgoff, addr, bytes, i);
 out:
	dm_put_live_table(md, srcu_idx);

	वापस ret;
पूर्ण

अटल पूर्णांक dm_dax_zero_page_range(काष्ठा dax_device *dax_dev, pgoff_t pgoff,
				  माप_प्रकार nr_pages)
अणु
	काष्ठा mapped_device *md = dax_get_निजी(dax_dev);
	sector_t sector = pgoff * PAGE_SECTORS;
	काष्ठा dm_target *ti;
	पूर्णांक ret = -EIO;
	पूर्णांक srcu_idx;

	ti = dm_dax_get_live_target(md, sector, &srcu_idx);

	अगर (!ti)
		जाओ out;
	अगर (WARN_ON(!ti->type->dax_zero_page_range)) अणु
		/*
		 * ->zero_page_range() is mandatory dax operation. If we are
		 *  here, something is wrong.
		 */
		जाओ out;
	पूर्ण
	ret = ti->type->dax_zero_page_range(ti, pgoff, nr_pages);
 out:
	dm_put_live_table(md, srcu_idx);

	वापस ret;
पूर्ण

/*
 * A target may call dm_accept_partial_bio only from the map routine.  It is
 * allowed क्रम all bio types except REQ_PREFLUSH, REQ_OP_ZONE_RESET,
 * REQ_OP_ZONE_OPEN, REQ_OP_ZONE_CLOSE and REQ_OP_ZONE_FINISH.
 *
 * dm_accept_partial_bio inक्रमms the dm that the target only wants to process
 * additional n_sectors sectors of the bio and the rest of the data should be
 * sent in a next bio.
 *
 * A diagram that explains the arithmetics:
 * +--------------------+---------------+-------+
 * |         1          |       2       |   3   |
 * +--------------------+---------------+-------+
 *
 * <-------------- *tio->len_ptr --------------->
 *                      <------- bi_size ------->
 *                      <-- n_sectors -->
 *
 * Region 1 was alपढ़ोy iterated over with bio_advance or similar function.
 *	(it may be empty अगर the target करोesn't use bio_advance)
 * Region 2 is the reमुख्यing bio size that the target wants to process.
 *	(it may be empty अगर region 1 is non-empty, although there is no reason
 *	 to make it empty)
 * The target requires that region 3 is to be sent in the next bio.
 *
 * If the target wants to receive multiple copies of the bio (via num_*bios, etc),
 * the partially processed part (the sum of regions 1+2) must be the same क्रम all
 * copies of the bio.
 */
व्योम dm_accept_partial_bio(काष्ठा bio *bio, अचिन्हित n_sectors)
अणु
	काष्ठा dm_target_io *tio = container_of(bio, काष्ठा dm_target_io, clone);
	अचिन्हित bi_size = bio->bi_iter.bi_size >> SECTOR_SHIFT;
	BUG_ON(bio->bi_opf & REQ_PREFLUSH);
	BUG_ON(bi_size > *tio->len_ptr);
	BUG_ON(n_sectors > bi_size);
	*tio->len_ptr -= bi_size - n_sectors;
	bio->bi_iter.bi_size = n_sectors << SECTOR_SHIFT;
पूर्ण
EXPORT_SYMBOL_GPL(dm_accept_partial_bio);

अटल noअंतरभूत व्योम __set_swap_bios_limit(काष्ठा mapped_device *md, पूर्णांक latch)
अणु
	mutex_lock(&md->swap_bios_lock);
	जबतक (latch < md->swap_bios) अणु
		cond_resched();
		करोwn(&md->swap_bios_semaphore);
		md->swap_bios--;
	पूर्ण
	जबतक (latch > md->swap_bios) अणु
		cond_resched();
		up(&md->swap_bios_semaphore);
		md->swap_bios++;
	पूर्ण
	mutex_unlock(&md->swap_bios_lock);
पूर्ण

अटल blk_qc_t __map_bio(काष्ठा dm_target_io *tio)
अणु
	पूर्णांक r;
	sector_t sector;
	काष्ठा bio *clone = &tio->clone;
	काष्ठा dm_io *io = tio->io;
	काष्ठा dm_target *ti = tio->ti;
	blk_qc_t ret = BLK_QC_T_NONE;

	clone->bi_end_io = clone_endio;

	/*
	 * Map the clone.  If r == 0 we करोn't need to करो
	 * anything, the target has assumed ownership of
	 * this io.
	 */
	atomic_inc(&io->io_count);
	sector = clone->bi_iter.bi_sector;

	अगर (unlikely(swap_bios_limit(ti, clone))) अणु
		काष्ठा mapped_device *md = io->md;
		पूर्णांक latch = get_swap_bios();
		अगर (unlikely(latch != md->swap_bios))
			__set_swap_bios_limit(md, latch);
		करोwn(&md->swap_bios_semaphore);
	पूर्ण

	r = ti->type->map(ti, clone);
	चयन (r) अणु
	हाल DM_MAPIO_SUBMITTED:
		अवरोध;
	हाल DM_MAPIO_REMAPPED:
		/* the bio has been remapped so dispatch it */
		trace_block_bio_remap(clone, bio_dev(io->orig_bio), sector);
		ret = submit_bio_noacct(clone);
		अवरोध;
	हाल DM_MAPIO_KILL:
		अगर (unlikely(swap_bios_limit(ti, clone))) अणु
			काष्ठा mapped_device *md = io->md;
			up(&md->swap_bios_semaphore);
		पूर्ण
		मुक्त_tio(tio);
		dec_pending(io, BLK_STS_IOERR);
		अवरोध;
	हाल DM_MAPIO_REQUEUE:
		अगर (unlikely(swap_bios_limit(ti, clone))) अणु
			काष्ठा mapped_device *md = io->md;
			up(&md->swap_bios_semaphore);
		पूर्ण
		मुक्त_tio(tio);
		dec_pending(io, BLK_STS_DM_REQUEUE);
		अवरोध;
	शेष:
		DMWARN("unimplemented target map return value: %d", r);
		BUG();
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम bio_setup_sector(काष्ठा bio *bio, sector_t sector, अचिन्हित len)
अणु
	bio->bi_iter.bi_sector = sector;
	bio->bi_iter.bi_size = to_bytes(len);
पूर्ण

/*
 * Creates a bio that consists of range of complete bvecs.
 */
अटल पूर्णांक clone_bio(काष्ठा dm_target_io *tio, काष्ठा bio *bio,
		     sector_t sector, अचिन्हित len)
अणु
	काष्ठा bio *clone = &tio->clone;
	पूर्णांक r;

	__bio_clone_fast(clone, bio);

	r = bio_crypt_clone(clone, bio, GFP_NOIO);
	अगर (r < 0)
		वापस r;

	अगर (bio_पूर्णांकegrity(bio)) अणु
		अगर (unlikely(!dm_target_has_पूर्णांकegrity(tio->ti->type) &&
			     !dm_target_passes_पूर्णांकegrity(tio->ti->type))) अणु
			DMWARN("%s: the target %s doesn't support integrity data.",
				dm_device_name(tio->io->md),
				tio->ti->type->name);
			वापस -EIO;
		पूर्ण

		r = bio_पूर्णांकegrity_clone(clone, bio, GFP_NOIO);
		अगर (r < 0)
			वापस r;
	पूर्ण

	bio_advance(clone, to_bytes(sector - clone->bi_iter.bi_sector));
	clone->bi_iter.bi_size = to_bytes(len);

	अगर (bio_पूर्णांकegrity(bio))
		bio_पूर्णांकegrity_trim(clone);

	वापस 0;
पूर्ण

अटल व्योम alloc_multiple_bios(काष्ठा bio_list *blist, काष्ठा clone_info *ci,
				काष्ठा dm_target *ti, अचिन्हित num_bios)
अणु
	काष्ठा dm_target_io *tio;
	पूर्णांक try;

	अगर (!num_bios)
		वापस;

	अगर (num_bios == 1) अणु
		tio = alloc_tio(ci, ti, 0, GFP_NOIO);
		bio_list_add(blist, &tio->clone);
		वापस;
	पूर्ण

	क्रम (try = 0; try < 2; try++) अणु
		पूर्णांक bio_nr;
		काष्ठा bio *bio;

		अगर (try)
			mutex_lock(&ci->io->md->table_devices_lock);
		क्रम (bio_nr = 0; bio_nr < num_bios; bio_nr++) अणु
			tio = alloc_tio(ci, ti, bio_nr, try ? GFP_NOIO : GFP_NOWAIT);
			अगर (!tio)
				अवरोध;

			bio_list_add(blist, &tio->clone);
		पूर्ण
		अगर (try)
			mutex_unlock(&ci->io->md->table_devices_lock);
		अगर (bio_nr == num_bios)
			वापस;

		जबतक ((bio = bio_list_pop(blist))) अणु
			tio = container_of(bio, काष्ठा dm_target_io, clone);
			मुक्त_tio(tio);
		पूर्ण
	पूर्ण
पूर्ण

अटल blk_qc_t __clone_and_map_simple_bio(काष्ठा clone_info *ci,
					   काष्ठा dm_target_io *tio, अचिन्हित *len)
अणु
	काष्ठा bio *clone = &tio->clone;

	tio->len_ptr = len;

	__bio_clone_fast(clone, ci->bio);
	अगर (len)
		bio_setup_sector(clone, ci->sector, *len);

	वापस __map_bio(tio);
पूर्ण

अटल व्योम __send_duplicate_bios(काष्ठा clone_info *ci, काष्ठा dm_target *ti,
				  अचिन्हित num_bios, अचिन्हित *len)
अणु
	काष्ठा bio_list blist = BIO_EMPTY_LIST;
	काष्ठा bio *bio;
	काष्ठा dm_target_io *tio;

	alloc_multiple_bios(&blist, ci, ti, num_bios);

	जबतक ((bio = bio_list_pop(&blist))) अणु
		tio = container_of(bio, काष्ठा dm_target_io, clone);
		(व्योम) __clone_and_map_simple_bio(ci, tio, len);
	पूर्ण
पूर्ण

अटल पूर्णांक __send_empty_flush(काष्ठा clone_info *ci)
अणु
	अचिन्हित target_nr = 0;
	काष्ठा dm_target *ti;
	काष्ठा bio flush_bio;

	/*
	 * Use an on-stack bio क्रम this, it's safe since we don't
	 * need to reference it after submit. It's just used as
	 * the basis क्रम the clone(s).
	 */
	bio_init(&flush_bio, शून्य, 0);
	flush_bio.bi_opf = REQ_OP_WRITE | REQ_PREFLUSH | REQ_SYNC;
	bio_set_dev(&flush_bio, ci->io->md->disk->part0);

	ci->bio = &flush_bio;
	ci->sector_count = 0;

	BUG_ON(bio_has_data(ci->bio));
	जबतक ((ti = dm_table_get_target(ci->map, target_nr++)))
		__send_duplicate_bios(ci, ti, ti->num_flush_bios, शून्य);

	bio_uninit(ci->bio);
	वापस 0;
पूर्ण

अटल पूर्णांक __clone_and_map_data_bio(काष्ठा clone_info *ci, काष्ठा dm_target *ti,
				    sector_t sector, अचिन्हित *len)
अणु
	काष्ठा bio *bio = ci->bio;
	काष्ठा dm_target_io *tio;
	पूर्णांक r;

	tio = alloc_tio(ci, ti, 0, GFP_NOIO);
	tio->len_ptr = len;
	r = clone_bio(tio, bio, sector, *len);
	अगर (r < 0) अणु
		मुक्त_tio(tio);
		वापस r;
	पूर्ण
	(व्योम) __map_bio(tio);

	वापस 0;
पूर्ण

अटल पूर्णांक __send_changing_extent_only(काष्ठा clone_info *ci, काष्ठा dm_target *ti,
				       अचिन्हित num_bios)
अणु
	अचिन्हित len;

	/*
	 * Even though the device advertised support क्रम this type of
	 * request, that करोes not mean every target supports it, and
	 * reconfiguration might also have changed that since the
	 * check was perक्रमmed.
	 */
	अगर (!num_bios)
		वापस -EOPNOTSUPP;

	len = min_t(sector_t, ci->sector_count,
		    max_io_len_target_boundary(ti, dm_target_offset(ti, ci->sector)));

	__send_duplicate_bios(ci, ti, num_bios, &len);

	ci->sector += len;
	ci->sector_count -= len;

	वापस 0;
पूर्ण

अटल bool is_abnormal_io(काष्ठा bio *bio)
अणु
	bool r = false;

	चयन (bio_op(bio)) अणु
	हाल REQ_OP_DISCARD:
	हाल REQ_OP_SECURE_ERASE:
	हाल REQ_OP_WRITE_SAME:
	हाल REQ_OP_WRITE_ZEROES:
		r = true;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल bool __process_abnormal_io(काष्ठा clone_info *ci, काष्ठा dm_target *ti,
				  पूर्णांक *result)
अणु
	काष्ठा bio *bio = ci->bio;
	अचिन्हित num_bios = 0;

	चयन (bio_op(bio)) अणु
	हाल REQ_OP_DISCARD:
		num_bios = ti->num_discard_bios;
		अवरोध;
	हाल REQ_OP_SECURE_ERASE:
		num_bios = ti->num_secure_erase_bios;
		अवरोध;
	हाल REQ_OP_WRITE_SAME:
		num_bios = ti->num_ग_लिखो_same_bios;
		अवरोध;
	हाल REQ_OP_WRITE_ZEROES:
		num_bios = ti->num_ग_लिखो_zeroes_bios;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	*result = __send_changing_extent_only(ci, ti, num_bios);
	वापस true;
पूर्ण

/*
 * Select the correct strategy क्रम processing a non-flush bio.
 */
अटल पूर्णांक __split_and_process_non_flush(काष्ठा clone_info *ci)
अणु
	काष्ठा dm_target *ti;
	अचिन्हित len;
	पूर्णांक r;

	ti = dm_table_find_target(ci->map, ci->sector);
	अगर (!ti)
		वापस -EIO;

	अगर (__process_abnormal_io(ci, ti, &r))
		वापस r;

	len = min_t(sector_t, max_io_len(ti, ci->sector), ci->sector_count);

	r = __clone_and_map_data_bio(ci, ti, ci->sector, &len);
	अगर (r < 0)
		वापस r;

	ci->sector += len;
	ci->sector_count -= len;

	वापस 0;
पूर्ण

अटल व्योम init_clone_info(काष्ठा clone_info *ci, काष्ठा mapped_device *md,
			    काष्ठा dm_table *map, काष्ठा bio *bio)
अणु
	ci->map = map;
	ci->io = alloc_io(md, bio);
	ci->sector = bio->bi_iter.bi_sector;
पूर्ण

#घोषणा __dm_part_stat_sub(part, field, subnd)	\
	(part_stat_get(part, field) -= (subnd))

/*
 * Entry poपूर्णांक to split a bio पूर्णांकo clones and submit them to the tarमाला_लो.
 */
अटल blk_qc_t __split_and_process_bio(काष्ठा mapped_device *md,
					काष्ठा dm_table *map, काष्ठा bio *bio)
अणु
	काष्ठा clone_info ci;
	blk_qc_t ret = BLK_QC_T_NONE;
	पूर्णांक error = 0;

	init_clone_info(&ci, md, map, bio);

	अगर (bio->bi_opf & REQ_PREFLUSH) अणु
		error = __send_empty_flush(&ci);
		/* dec_pending submits any data associated with flush */
	पूर्ण अन्यथा अगर (op_is_zone_mgmt(bio_op(bio))) अणु
		ci.bio = bio;
		ci.sector_count = 0;
		error = __split_and_process_non_flush(&ci);
	पूर्ण अन्यथा अणु
		ci.bio = bio;
		ci.sector_count = bio_sectors(bio);
		error = __split_and_process_non_flush(&ci);
		अगर (ci.sector_count && !error) अणु
			/*
			 * Reमुख्यder must be passed to submit_bio_noacct()
			 * so that it माला_लो handled *after* bios alपढ़ोy submitted
			 * have been completely processed.
			 * We take a clone of the original to store in
			 * ci.io->orig_bio to be used by end_io_acct() and
			 * क्रम dec_pending to use क्रम completion handling.
			 */
			काष्ठा bio *b = bio_split(bio, bio_sectors(bio) - ci.sector_count,
						  GFP_NOIO, &md->queue->bio_split);
			ci.io->orig_bio = b;

			/*
			 * Adjust IO stats क्रम each split, otherwise upon queue
			 * reentry there will be redundant IO accounting.
			 * NOTE: this is a stop-gap fix, a proper fix involves
			 * signअगरicant refactoring of DM core's bio splitting
			 * (by eliminating DM's splitting and just using bio_split)
			 */
			part_stat_lock();
			__dm_part_stat_sub(dm_disk(md)->part0,
					   sectors[op_stat_group(bio_op(bio))], ci.sector_count);
			part_stat_unlock();

			bio_chain(b, bio);
			trace_block_split(b, bio->bi_iter.bi_sector);
			ret = submit_bio_noacct(bio);
		पूर्ण
	पूर्ण

	/* drop the extra reference count */
	dec_pending(ci.io, त्रुटि_सं_to_blk_status(error));
	वापस ret;
पूर्ण

अटल blk_qc_t dm_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा mapped_device *md = bio->bi_bdev->bd_disk->निजी_data;
	blk_qc_t ret = BLK_QC_T_NONE;
	पूर्णांक srcu_idx;
	काष्ठा dm_table *map;

	map = dm_get_live_table(md, &srcu_idx);
	अगर (unlikely(!map)) अणु
		DMERR_LIMIT("%s: mapping table unavailable, erroring io",
			    dm_device_name(md));
		bio_io_error(bio);
		जाओ out;
	पूर्ण

	/* If suspended, queue this IO क्रम later */
	अगर (unlikely(test_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags))) अणु
		अगर (bio->bi_opf & REQ_NOWAIT)
			bio_wouldblock_error(bio);
		अन्यथा अगर (bio->bi_opf & REQ_RAHEAD)
			bio_io_error(bio);
		अन्यथा
			queue_io(md, bio);
		जाओ out;
	पूर्ण

	/*
	 * Use blk_queue_split() क्रम abnormal IO (e.g. discard, ग_लिखोsame, etc)
	 * otherwise associated queue_limits won't be imposed.
	 */
	अगर (is_abnormal_io(bio))
		blk_queue_split(&bio);

	ret = __split_and_process_bio(md, map, bio);
out:
	dm_put_live_table(md, srcu_idx);
	वापस ret;
पूर्ण

/*-----------------------------------------------------------------
 * An IDR is used to keep track of allocated minor numbers.
 *---------------------------------------------------------------*/
अटल व्योम मुक्त_minor(पूर्णांक minor)
अणु
	spin_lock(&_minor_lock);
	idr_हटाओ(&_minor_idr, minor);
	spin_unlock(&_minor_lock);
पूर्ण

/*
 * See अगर the device with a specअगरic minor # is मुक्त.
 */
अटल पूर्णांक specअगरic_minor(पूर्णांक minor)
अणु
	पूर्णांक r;

	अगर (minor >= (1 << MINORBITS))
		वापस -EINVAL;

	idr_preload(GFP_KERNEL);
	spin_lock(&_minor_lock);

	r = idr_alloc(&_minor_idr, MINOR_ALLOCED, minor, minor + 1, GFP_NOWAIT);

	spin_unlock(&_minor_lock);
	idr_preload_end();
	अगर (r < 0)
		वापस r == -ENOSPC ? -EBUSY : r;
	वापस 0;
पूर्ण

अटल पूर्णांक next_मुक्त_minor(पूर्णांक *minor)
अणु
	पूर्णांक r;

	idr_preload(GFP_KERNEL);
	spin_lock(&_minor_lock);

	r = idr_alloc(&_minor_idr, MINOR_ALLOCED, 0, 1 << MINORBITS, GFP_NOWAIT);

	spin_unlock(&_minor_lock);
	idr_preload_end();
	अगर (r < 0)
		वापस r;
	*minor = r;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा block_device_operations dm_blk_करोps;
अटल स्थिर काष्ठा block_device_operations dm_rq_blk_करोps;
अटल स्थिर काष्ठा dax_operations dm_dax_ops;

अटल व्योम dm_wq_work(काष्ठा work_काष्ठा *work);

#अगर_घोषित CONFIG_BLK_INLINE_ENCRYPTION
अटल व्योम dm_queue_destroy_keyslot_manager(काष्ठा request_queue *q)
अणु
	dm_destroy_keyslot_manager(q->ksm);
पूर्ण

#अन्यथा /* CONFIG_BLK_INLINE_ENCRYPTION */

अटल अंतरभूत व्योम dm_queue_destroy_keyslot_manager(काष्ठा request_queue *q)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_BLK_INLINE_ENCRYPTION */

अटल व्योम cleanup_mapped_device(काष्ठा mapped_device *md)
अणु
	अगर (md->wq)
		destroy_workqueue(md->wq);
	bioset_निकास(&md->bs);
	bioset_निकास(&md->io_bs);

	अगर (md->dax_dev) अणु
		समाप्त_dax(md->dax_dev);
		put_dax(md->dax_dev);
		md->dax_dev = शून्य;
	पूर्ण

	अगर (md->disk) अणु
		spin_lock(&_minor_lock);
		md->disk->निजी_data = शून्य;
		spin_unlock(&_minor_lock);
		del_gendisk(md->disk);
		put_disk(md->disk);
	पूर्ण

	अगर (md->queue) अणु
		dm_queue_destroy_keyslot_manager(md->queue);
		blk_cleanup_queue(md->queue);
	पूर्ण

	cleanup_srcu_काष्ठा(&md->io_barrier);

	mutex_destroy(&md->suspend_lock);
	mutex_destroy(&md->type_lock);
	mutex_destroy(&md->table_devices_lock);
	mutex_destroy(&md->swap_bios_lock);

	dm_mq_cleanup_mapped_device(md);
पूर्ण

/*
 * Allocate and initialise a blank device with a given minor.
 */
अटल काष्ठा mapped_device *alloc_dev(पूर्णांक minor)
अणु
	पूर्णांक r, numa_node_id = dm_get_numa_node();
	काष्ठा mapped_device *md;
	व्योम *old_md;

	md = kvzalloc_node(माप(*md), GFP_KERNEL, numa_node_id);
	अगर (!md) अणु
		DMWARN("unable to allocate device, out of memory.");
		वापस शून्य;
	पूर्ण

	अगर (!try_module_get(THIS_MODULE))
		जाओ bad_module_get;

	/* get a minor number क्रम the dev */
	अगर (minor == DM_ANY_MINOR)
		r = next_मुक्त_minor(&minor);
	अन्यथा
		r = specअगरic_minor(minor);
	अगर (r < 0)
		जाओ bad_minor;

	r = init_srcu_काष्ठा(&md->io_barrier);
	अगर (r < 0)
		जाओ bad_io_barrier;

	md->numa_node_id = numa_node_id;
	md->init_tio_pdu = false;
	md->type = DM_TYPE_NONE;
	mutex_init(&md->suspend_lock);
	mutex_init(&md->type_lock);
	mutex_init(&md->table_devices_lock);
	spin_lock_init(&md->deferred_lock);
	atomic_set(&md->holders, 1);
	atomic_set(&md->खोलो_count, 0);
	atomic_set(&md->event_nr, 0);
	atomic_set(&md->uevent_seq, 0);
	INIT_LIST_HEAD(&md->uevent_list);
	INIT_LIST_HEAD(&md->table_devices);
	spin_lock_init(&md->uevent_lock);

	/*
	 * शेष to bio-based until DM table is loaded and md->type
	 * established. If request-based table is loaded: blk-mq will
	 * override accordingly.
	 */
	md->queue = blk_alloc_queue(numa_node_id);
	अगर (!md->queue)
		जाओ bad;

	md->disk = alloc_disk_node(1, md->numa_node_id);
	अगर (!md->disk)
		जाओ bad;

	init_रुकोqueue_head(&md->रुको);
	INIT_WORK(&md->work, dm_wq_work);
	init_रुकोqueue_head(&md->eventq);
	init_completion(&md->kobj_holder.completion);

	md->swap_bios = get_swap_bios();
	sema_init(&md->swap_bios_semaphore, md->swap_bios);
	mutex_init(&md->swap_bios_lock);

	md->disk->major = _major;
	md->disk->first_minor = minor;
	md->disk->fops = &dm_blk_करोps;
	md->disk->queue = md->queue;
	md->disk->निजी_data = md;
	प्र_लिखो(md->disk->disk_name, "dm-%d", minor);

	अगर (IS_ENABLED(CONFIG_DAX_DRIVER)) अणु
		md->dax_dev = alloc_dax(md, md->disk->disk_name,
					&dm_dax_ops, 0);
		अगर (IS_ERR(md->dax_dev))
			जाओ bad;
	पूर्ण

	add_disk_no_queue_reg(md->disk);
	क्रमmat_dev_t(md->name, MKDEV(_major, minor));

	md->wq = alloc_workqueue("kdmflush", WQ_MEM_RECLAIM, 0);
	अगर (!md->wq)
		जाओ bad;

	dm_stats_init(&md->stats);

	/* Populate the mapping, nobody knows we exist yet */
	spin_lock(&_minor_lock);
	old_md = idr_replace(&_minor_idr, md, minor);
	spin_unlock(&_minor_lock);

	BUG_ON(old_md != MINOR_ALLOCED);

	वापस md;

bad:
	cleanup_mapped_device(md);
bad_io_barrier:
	मुक्त_minor(minor);
bad_minor:
	module_put(THIS_MODULE);
bad_module_get:
	kvमुक्त(md);
	वापस शून्य;
पूर्ण

अटल व्योम unlock_fs(काष्ठा mapped_device *md);

अटल व्योम मुक्त_dev(काष्ठा mapped_device *md)
अणु
	पूर्णांक minor = MINOR(disk_devt(md->disk));

	unlock_fs(md);

	cleanup_mapped_device(md);

	मुक्त_table_devices(&md->table_devices);
	dm_stats_cleanup(&md->stats);
	मुक्त_minor(minor);

	module_put(THIS_MODULE);
	kvमुक्त(md);
पूर्ण

अटल पूर्णांक __bind_mempools(काष्ठा mapped_device *md, काष्ठा dm_table *t)
अणु
	काष्ठा dm_md_mempools *p = dm_table_get_md_mempools(t);
	पूर्णांक ret = 0;

	अगर (dm_table_bio_based(t)) अणु
		/*
		 * The md may alपढ़ोy have mempools that need changing.
		 * If so, reload bioset because front_pad may have changed
		 * because a dअगरferent table was loaded.
		 */
		bioset_निकास(&md->bs);
		bioset_निकास(&md->io_bs);

	पूर्ण अन्यथा अगर (bioset_initialized(&md->bs)) अणु
		/*
		 * There's no need to reload with request-based dm
		 * because the size of front_pad करोesn't change.
		 * Note क्रम future: If you are to reload bioset,
		 * prep-ed requests in the queue may refer
		 * to bio from the old bioset, so you must walk
		 * through the queue to unprep.
		 */
		जाओ out;
	पूर्ण

	BUG_ON(!p ||
	       bioset_initialized(&md->bs) ||
	       bioset_initialized(&md->io_bs));

	ret = bioset_init_from_src(&md->bs, &p->bs);
	अगर (ret)
		जाओ out;
	ret = bioset_init_from_src(&md->io_bs, &p->io_bs);
	अगर (ret)
		bioset_निकास(&md->bs);
out:
	/* mempool bind completed, no दीर्घer need any mempools in the table */
	dm_table_मुक्त_md_mempools(t);
	वापस ret;
पूर्ण

/*
 * Bind a table to the device.
 */
अटल व्योम event_callback(व्योम *context)
अणु
	अचिन्हित दीर्घ flags;
	LIST_HEAD(uevents);
	काष्ठा mapped_device *md = (काष्ठा mapped_device *) context;

	spin_lock_irqsave(&md->uevent_lock, flags);
	list_splice_init(&md->uevent_list, &uevents);
	spin_unlock_irqrestore(&md->uevent_lock, flags);

	dm_send_uevents(&uevents, &disk_to_dev(md->disk)->kobj);

	atomic_inc(&md->event_nr);
	wake_up(&md->eventq);
	dm_issue_global_event();
पूर्ण

/*
 * Returns old map, which caller must destroy.
 */
अटल काष्ठा dm_table *__bind(काष्ठा mapped_device *md, काष्ठा dm_table *t,
			       काष्ठा queue_limits *limits)
अणु
	काष्ठा dm_table *old_map;
	काष्ठा request_queue *q = md->queue;
	bool request_based = dm_table_request_based(t);
	sector_t size;
	पूर्णांक ret;

	lockdep_निश्चित_held(&md->suspend_lock);

	size = dm_table_get_size(t);

	/*
	 * Wipe any geometry अगर the size of the table changed.
	 */
	अगर (size != dm_get_size(md))
		स_रखो(&md->geometry, 0, माप(md->geometry));

	अगर (!get_capacity(md->disk))
		set_capacity(md->disk, size);
	अन्यथा
		set_capacity_and_notअगरy(md->disk, size);

	dm_table_event_callback(t, event_callback, md);

	/*
	 * The queue hasn't been stopped yet, if the old table type wasn't
	 * क्रम request-based during suspension.  So stop it to prevent
	 * I/O mapping beक्रमe resume.
	 * This must be करोne beक्रमe setting the queue restrictions,
	 * because request-based dm may be run just after the setting.
	 */
	अगर (request_based)
		dm_stop_queue(q);

	अगर (request_based) अणु
		/*
		 * Leverage the fact that request-based DM tarमाला_लो are
		 * immutable singletons - used to optimize dm_mq_queue_rq.
		 */
		md->immutable_target = dm_table_get_immutable_target(t);
	पूर्ण

	ret = __bind_mempools(md, t);
	अगर (ret) अणु
		old_map = ERR_PTR(ret);
		जाओ out;
	पूर्ण

	old_map = rcu_dereference_रक्षित(md->map, lockdep_is_held(&md->suspend_lock));
	rcu_assign_poपूर्णांकer(md->map, (व्योम *)t);
	md->immutable_target_type = dm_table_get_immutable_target_type(t);

	dm_table_set_restrictions(t, q, limits);
	अगर (old_map)
		dm_sync_table(md);

out:
	वापस old_map;
पूर्ण

/*
 * Returns unbound table क्रम the caller to मुक्त.
 */
अटल काष्ठा dm_table *__unbind(काष्ठा mapped_device *md)
अणु
	काष्ठा dm_table *map = rcu_dereference_रक्षित(md->map, 1);

	अगर (!map)
		वापस शून्य;

	dm_table_event_callback(map, शून्य, शून्य);
	RCU_INIT_POINTER(md->map, शून्य);
	dm_sync_table(md);

	वापस map;
पूर्ण

/*
 * Conकाष्ठाor क्रम a new device.
 */
पूर्णांक dm_create(पूर्णांक minor, काष्ठा mapped_device **result)
अणु
	पूर्णांक r;
	काष्ठा mapped_device *md;

	md = alloc_dev(minor);
	अगर (!md)
		वापस -ENXIO;

	r = dm_sysfs_init(md);
	अगर (r) अणु
		मुक्त_dev(md);
		वापस r;
	पूर्ण

	*result = md;
	वापस 0;
पूर्ण

/*
 * Functions to manage md->type.
 * All are required to hold md->type_lock.
 */
व्योम dm_lock_md_type(काष्ठा mapped_device *md)
अणु
	mutex_lock(&md->type_lock);
पूर्ण

व्योम dm_unlock_md_type(काष्ठा mapped_device *md)
अणु
	mutex_unlock(&md->type_lock);
पूर्ण

व्योम dm_set_md_type(काष्ठा mapped_device *md, क्रमागत dm_queue_mode type)
अणु
	BUG_ON(!mutex_is_locked(&md->type_lock));
	md->type = type;
पूर्ण

क्रमागत dm_queue_mode dm_get_md_type(काष्ठा mapped_device *md)
अणु
	वापस md->type;
पूर्ण

काष्ठा target_type *dm_get_immutable_target_type(काष्ठा mapped_device *md)
अणु
	वापस md->immutable_target_type;
पूर्ण

/*
 * The queue_limits are only valid as दीर्घ as you have a reference
 * count on 'md'.
 */
काष्ठा queue_limits *dm_get_queue_limits(काष्ठा mapped_device *md)
अणु
	BUG_ON(!atomic_पढ़ो(&md->holders));
	वापस &md->queue->limits;
पूर्ण
EXPORT_SYMBOL_GPL(dm_get_queue_limits);

/*
 * Setup the DM device's queue based on md's type
 */
पूर्णांक dm_setup_md_queue(काष्ठा mapped_device *md, काष्ठा dm_table *t)
अणु
	पूर्णांक r;
	काष्ठा queue_limits limits;
	क्रमागत dm_queue_mode type = dm_get_md_type(md);

	चयन (type) अणु
	हाल DM_TYPE_REQUEST_BASED:
		md->disk->fops = &dm_rq_blk_करोps;
		r = dm_mq_init_request_queue(md, t);
		अगर (r) अणु
			DMERR("Cannot initialize queue for request-based dm mapped device");
			वापस r;
		पूर्ण
		अवरोध;
	हाल DM_TYPE_BIO_BASED:
	हाल DM_TYPE_DAX_BIO_BASED:
		अवरोध;
	हाल DM_TYPE_NONE:
		WARN_ON_ONCE(true);
		अवरोध;
	पूर्ण

	r = dm_calculate_queue_limits(t, &limits);
	अगर (r) अणु
		DMERR("Cannot calculate initial queue limits");
		वापस r;
	पूर्ण
	dm_table_set_restrictions(t, md->queue, &limits);
	blk_रेजिस्टर_queue(md->disk);

	वापस 0;
पूर्ण

काष्ठा mapped_device *dm_get_md(dev_t dev)
अणु
	काष्ठा mapped_device *md;
	अचिन्हित minor = MINOR(dev);

	अगर (MAJOR(dev) != _major || minor >= (1 << MINORBITS))
		वापस शून्य;

	spin_lock(&_minor_lock);

	md = idr_find(&_minor_idr, minor);
	अगर (!md || md == MINOR_ALLOCED || (MINOR(disk_devt(dm_disk(md))) != minor) ||
	    test_bit(DMF_FREEING, &md->flags) || dm_deleting_md(md)) अणु
		md = शून्य;
		जाओ out;
	पूर्ण
	dm_get(md);
out:
	spin_unlock(&_minor_lock);

	वापस md;
पूर्ण
EXPORT_SYMBOL_GPL(dm_get_md);

व्योम *dm_get_mdptr(काष्ठा mapped_device *md)
अणु
	वापस md->पूर्णांकerface_ptr;
पूर्ण

व्योम dm_set_mdptr(काष्ठा mapped_device *md, व्योम *ptr)
अणु
	md->पूर्णांकerface_ptr = ptr;
पूर्ण

व्योम dm_get(काष्ठा mapped_device *md)
अणु
	atomic_inc(&md->holders);
	BUG_ON(test_bit(DMF_FREEING, &md->flags));
पूर्ण

पूर्णांक dm_hold(काष्ठा mapped_device *md)
अणु
	spin_lock(&_minor_lock);
	अगर (test_bit(DMF_FREEING, &md->flags)) अणु
		spin_unlock(&_minor_lock);
		वापस -EBUSY;
	पूर्ण
	dm_get(md);
	spin_unlock(&_minor_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dm_hold);

स्थिर अक्षर *dm_device_name(काष्ठा mapped_device *md)
अणु
	वापस md->name;
पूर्ण
EXPORT_SYMBOL_GPL(dm_device_name);

अटल व्योम __dm_destroy(काष्ठा mapped_device *md, bool रुको)
अणु
	काष्ठा dm_table *map;
	पूर्णांक srcu_idx;

	might_sleep();

	spin_lock(&_minor_lock);
	idr_replace(&_minor_idr, MINOR_ALLOCED, MINOR(disk_devt(dm_disk(md))));
	set_bit(DMF_FREEING, &md->flags);
	spin_unlock(&_minor_lock);

	blk_set_queue_dying(md->queue);

	/*
	 * Take suspend_lock so that presuspend and postsuspend methods
	 * करो not race with पूर्णांकernal suspend.
	 */
	mutex_lock(&md->suspend_lock);
	map = dm_get_live_table(md, &srcu_idx);
	अगर (!dm_suspended_md(md)) अणु
		dm_table_presuspend_tarमाला_लो(map);
		set_bit(DMF_SUSPENDED, &md->flags);
		set_bit(DMF_POST_SUSPENDING, &md->flags);
		dm_table_postsuspend_tarमाला_लो(map);
	पूर्ण
	/* dm_put_live_table must be beक्रमe msleep, otherwise deadlock is possible */
	dm_put_live_table(md, srcu_idx);
	mutex_unlock(&md->suspend_lock);

	/*
	 * Rare, but there may be I/O requests still going to complete,
	 * क्रम example.  Wait क्रम all references to disappear.
	 * No one should increment the reference count of the mapped_device,
	 * after the mapped_device state becomes DMF_FREEING.
	 */
	अगर (रुको)
		जबतक (atomic_पढ़ो(&md->holders))
			msleep(1);
	अन्यथा अगर (atomic_पढ़ो(&md->holders))
		DMWARN("%s: Forcibly removing mapped_device still in use! (%d users)",
		       dm_device_name(md), atomic_पढ़ो(&md->holders));

	dm_sysfs_निकास(md);
	dm_table_destroy(__unbind(md));
	मुक्त_dev(md);
पूर्ण

व्योम dm_destroy(काष्ठा mapped_device *md)
अणु
	__dm_destroy(md, true);
पूर्ण

व्योम dm_destroy_immediate(काष्ठा mapped_device *md)
अणु
	__dm_destroy(md, false);
पूर्ण

व्योम dm_put(काष्ठा mapped_device *md)
अणु
	atomic_dec(&md->holders);
पूर्ण
EXPORT_SYMBOL_GPL(dm_put);

अटल bool md_in_flight_bios(काष्ठा mapped_device *md)
अणु
	पूर्णांक cpu;
	काष्ठा block_device *part = dm_disk(md)->part0;
	दीर्घ sum = 0;

	क्रम_each_possible_cpu(cpu) अणु
		sum += part_stat_local_पढ़ो_cpu(part, in_flight[0], cpu);
		sum += part_stat_local_पढ़ो_cpu(part, in_flight[1], cpu);
	पूर्ण

	वापस sum != 0;
पूर्ण

अटल पूर्णांक dm_रुको_क्रम_bios_completion(काष्ठा mapped_device *md, दीर्घ task_state)
अणु
	पूर्णांक r = 0;
	DEFINE_WAIT(रुको);

	जबतक (true) अणु
		prepare_to_रुको(&md->रुको, &रुको, task_state);

		अगर (!md_in_flight_bios(md))
			अवरोध;

		अगर (संकेत_pending_state(task_state, current)) अणु
			r = -EINTR;
			अवरोध;
		पूर्ण

		io_schedule();
	पूर्ण
	finish_रुको(&md->रुको, &रुको);

	वापस r;
पूर्ण

अटल पूर्णांक dm_रुको_क्रम_completion(काष्ठा mapped_device *md, दीर्घ task_state)
अणु
	पूर्णांक r = 0;

	अगर (!queue_is_mq(md->queue))
		वापस dm_रुको_क्रम_bios_completion(md, task_state);

	जबतक (true) अणु
		अगर (!blk_mq_queue_inflight(md->queue))
			अवरोध;

		अगर (संकेत_pending_state(task_state, current)) अणु
			r = -EINTR;
			अवरोध;
		पूर्ण

		msleep(5);
	पूर्ण

	वापस r;
पूर्ण

/*
 * Process the deferred bios
 */
अटल व्योम dm_wq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mapped_device *md = container_of(work, काष्ठा mapped_device, work);
	काष्ठा bio *bio;

	जबतक (!test_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags)) अणु
		spin_lock_irq(&md->deferred_lock);
		bio = bio_list_pop(&md->deferred);
		spin_unlock_irq(&md->deferred_lock);

		अगर (!bio)
			अवरोध;

		submit_bio_noacct(bio);
	पूर्ण
पूर्ण

अटल व्योम dm_queue_flush(काष्ठा mapped_device *md)
अणु
	clear_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags);
	smp_mb__after_atomic();
	queue_work(md->wq, &md->work);
पूर्ण

/*
 * Swap in a new table, वापसing the old one क्रम the caller to destroy.
 */
काष्ठा dm_table *dm_swap_table(काष्ठा mapped_device *md, काष्ठा dm_table *table)
अणु
	काष्ठा dm_table *live_map = शून्य, *map = ERR_PTR(-EINVAL);
	काष्ठा queue_limits limits;
	पूर्णांक r;

	mutex_lock(&md->suspend_lock);

	/* device must be suspended */
	अगर (!dm_suspended_md(md))
		जाओ out;

	/*
	 * If the new table has no data devices, retain the existing limits.
	 * This helps multipath with queue_अगर_no_path अगर all paths disappear,
	 * then new I/O is queued based on these limits, and then some paths
	 * reappear.
	 */
	अगर (dm_table_has_no_data_devices(table)) अणु
		live_map = dm_get_live_table_fast(md);
		अगर (live_map)
			limits = md->queue->limits;
		dm_put_live_table_fast(md);
	पूर्ण

	अगर (!live_map) अणु
		r = dm_calculate_queue_limits(table, &limits);
		अगर (r) अणु
			map = ERR_PTR(r);
			जाओ out;
		पूर्ण
	पूर्ण

	map = __bind(md, table, &limits);
	dm_issue_global_event();

out:
	mutex_unlock(&md->suspend_lock);
	वापस map;
पूर्ण

/*
 * Functions to lock and unlock any fileप्रणाली running on the
 * device.
 */
अटल पूर्णांक lock_fs(काष्ठा mapped_device *md)
अणु
	पूर्णांक r;

	WARN_ON(test_bit(DMF_FROZEN, &md->flags));

	r = मुक्तze_bdev(md->disk->part0);
	अगर (!r)
		set_bit(DMF_FROZEN, &md->flags);
	वापस r;
पूर्ण

अटल व्योम unlock_fs(काष्ठा mapped_device *md)
अणु
	अगर (!test_bit(DMF_FROZEN, &md->flags))
		वापस;
	thaw_bdev(md->disk->part0);
	clear_bit(DMF_FROZEN, &md->flags);
पूर्ण

/*
 * @suspend_flags: DM_SUSPEND_LOCKFS_FLAG and/or DM_SUSPEND_NOFLUSH_FLAG
 * @task_state: e.g. TASK_INTERRUPTIBLE or TASK_UNINTERRUPTIBLE
 * @dmf_suspended_flag: DMF_SUSPENDED or DMF_SUSPENDED_INTERNALLY
 *
 * If __dm_suspend वापसs 0, the device is completely quiescent
 * now. There is no request-processing activity. All new requests
 * are being added to md->deferred list.
 */
अटल पूर्णांक __dm_suspend(काष्ठा mapped_device *md, काष्ठा dm_table *map,
			अचिन्हित suspend_flags, दीर्घ task_state,
			पूर्णांक dmf_suspended_flag)
अणु
	bool करो_lockfs = suspend_flags & DM_SUSPEND_LOCKFS_FLAG;
	bool noflush = suspend_flags & DM_SUSPEND_NOFLUSH_FLAG;
	पूर्णांक r;

	lockdep_निश्चित_held(&md->suspend_lock);

	/*
	 * DMF_NOFLUSH_SUSPENDING must be set beक्रमe presuspend.
	 * This flag is cleared beक्रमe dm_suspend वापसs.
	 */
	अगर (noflush)
		set_bit(DMF_NOFLUSH_SUSPENDING, &md->flags);
	अन्यथा
		DMDEBUG("%s: suspending with flush", dm_device_name(md));

	/*
	 * This माला_लो reverted अगर there's an error later and the tarमाला_लो
	 * provide the .presuspend_unकरो hook.
	 */
	dm_table_presuspend_tarमाला_लो(map);

	/*
	 * Flush I/O to the device.
	 * Any I/O submitted after lock_fs() may not be flushed.
	 * noflush takes precedence over करो_lockfs.
	 * (lock_fs() flushes I/Os and रुकोs क्रम them to complete.)
	 */
	अगर (!noflush && करो_lockfs) अणु
		r = lock_fs(md);
		अगर (r) अणु
			dm_table_presuspend_unकरो_tarमाला_लो(map);
			वापस r;
		पूर्ण
	पूर्ण

	/*
	 * Here we must make sure that no processes are submitting requests
	 * to target drivers i.e. no one may be executing
	 * __split_and_process_bio from dm_submit_bio.
	 *
	 * To get all processes out of __split_and_process_bio in dm_submit_bio,
	 * we take the ग_लिखो lock. To prevent any process from reentering
	 * __split_and_process_bio from dm_submit_bio and quiesce the thपढ़ो
	 * (dm_wq_work), we set DMF_BLOCK_IO_FOR_SUSPEND and call
	 * flush_workqueue(md->wq).
	 */
	set_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags);
	अगर (map)
		synchronize_srcu(&md->io_barrier);

	/*
	 * Stop md->queue beक्रमe flushing md->wq in हाल request-based
	 * dm defers requests to md->wq from md->queue.
	 */
	अगर (dm_request_based(md))
		dm_stop_queue(md->queue);

	flush_workqueue(md->wq);

	/*
	 * At this poपूर्णांक no more requests are entering target request routines.
	 * We call dm_रुको_क्रम_completion to रुको क्रम all existing requests
	 * to finish.
	 */
	r = dm_रुको_क्रम_completion(md, task_state);
	अगर (!r)
		set_bit(dmf_suspended_flag, &md->flags);

	अगर (noflush)
		clear_bit(DMF_NOFLUSH_SUSPENDING, &md->flags);
	अगर (map)
		synchronize_srcu(&md->io_barrier);

	/* were we पूर्णांकerrupted ? */
	अगर (r < 0) अणु
		dm_queue_flush(md);

		अगर (dm_request_based(md))
			dm_start_queue(md->queue);

		unlock_fs(md);
		dm_table_presuspend_unकरो_tarमाला_लो(map);
		/* pushback list is alपढ़ोy flushed, so skip flush */
	पूर्ण

	वापस r;
पूर्ण

/*
 * We need to be able to change a mapping table under a mounted
 * fileप्रणाली.  For example we might want to move some data in
 * the background.  Beक्रमe the table can be swapped with
 * dm_bind_table, dm_suspend must be called to flush any in
 * flight bios and ensure that any further io माला_लो deferred.
 */
/*
 * Suspend mechanism in request-based dm.
 *
 * 1. Flush all I/Os by lock_fs() अगर needed.
 * 2. Stop dispatching any I/O by stopping the request_queue.
 * 3. Wait क्रम all in-flight I/Os to be completed or requeued.
 *
 * To पात suspend, start the request_queue.
 */
पूर्णांक dm_suspend(काष्ठा mapped_device *md, अचिन्हित suspend_flags)
अणु
	काष्ठा dm_table *map = शून्य;
	पूर्णांक r = 0;

retry:
	mutex_lock_nested(&md->suspend_lock, SINGLE_DEPTH_NESTING);

	अगर (dm_suspended_md(md)) अणु
		r = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (dm_suspended_पूर्णांकernally_md(md)) अणु
		/* alपढ़ोy पूर्णांकernally suspended, रुको क्रम पूर्णांकernal resume */
		mutex_unlock(&md->suspend_lock);
		r = रुको_on_bit(&md->flags, DMF_SUSPENDED_INTERNALLY, TASK_INTERRUPTIBLE);
		अगर (r)
			वापस r;
		जाओ retry;
	पूर्ण

	map = rcu_dereference_रक्षित(md->map, lockdep_is_held(&md->suspend_lock));

	r = __dm_suspend(md, map, suspend_flags, TASK_INTERRUPTIBLE, DMF_SUSPENDED);
	अगर (r)
		जाओ out_unlock;

	set_bit(DMF_POST_SUSPENDING, &md->flags);
	dm_table_postsuspend_tarमाला_लो(map);
	clear_bit(DMF_POST_SUSPENDING, &md->flags);

out_unlock:
	mutex_unlock(&md->suspend_lock);
	वापस r;
पूर्ण

अटल पूर्णांक __dm_resume(काष्ठा mapped_device *md, काष्ठा dm_table *map)
अणु
	अगर (map) अणु
		पूर्णांक r = dm_table_resume_tarमाला_लो(map);
		अगर (r)
			वापस r;
	पूर्ण

	dm_queue_flush(md);

	/*
	 * Flushing deferred I/Os must be करोne after tarमाला_लो are resumed
	 * so that mapping of tarमाला_लो can work correctly.
	 * Request-based dm is queueing the deferred I/Os in its request_queue.
	 */
	अगर (dm_request_based(md))
		dm_start_queue(md->queue);

	unlock_fs(md);

	वापस 0;
पूर्ण

पूर्णांक dm_resume(काष्ठा mapped_device *md)
अणु
	पूर्णांक r;
	काष्ठा dm_table *map = शून्य;

retry:
	r = -EINVAL;
	mutex_lock_nested(&md->suspend_lock, SINGLE_DEPTH_NESTING);

	अगर (!dm_suspended_md(md))
		जाओ out;

	अगर (dm_suspended_पूर्णांकernally_md(md)) अणु
		/* alपढ़ोy पूर्णांकernally suspended, रुको क्रम पूर्णांकernal resume */
		mutex_unlock(&md->suspend_lock);
		r = रुको_on_bit(&md->flags, DMF_SUSPENDED_INTERNALLY, TASK_INTERRUPTIBLE);
		अगर (r)
			वापस r;
		जाओ retry;
	पूर्ण

	map = rcu_dereference_रक्षित(md->map, lockdep_is_held(&md->suspend_lock));
	अगर (!map || !dm_table_get_size(map))
		जाओ out;

	r = __dm_resume(md, map);
	अगर (r)
		जाओ out;

	clear_bit(DMF_SUSPENDED, &md->flags);
out:
	mutex_unlock(&md->suspend_lock);

	वापस r;
पूर्ण

/*
 * Internal suspend/resume works like userspace-driven suspend. It रुकोs
 * until all bios finish and prevents issuing new bios to the target drivers.
 * It may be used only from the kernel.
 */

अटल व्योम __dm_पूर्णांकernal_suspend(काष्ठा mapped_device *md, अचिन्हित suspend_flags)
अणु
	काष्ठा dm_table *map = शून्य;

	lockdep_निश्चित_held(&md->suspend_lock);

	अगर (md->पूर्णांकernal_suspend_count++)
		वापस; /* nested पूर्णांकernal suspend */

	अगर (dm_suspended_md(md)) अणु
		set_bit(DMF_SUSPENDED_INTERNALLY, &md->flags);
		वापस; /* nest suspend */
	पूर्ण

	map = rcu_dereference_रक्षित(md->map, lockdep_is_held(&md->suspend_lock));

	/*
	 * Using TASK_UNINTERRUPTIBLE because only NOFLUSH पूर्णांकernal suspend is
	 * supported.  Properly supporting a TASK_INTERRUPTIBLE पूर्णांकernal suspend
	 * would require changing .presuspend to वापस an error -- aव्योम this
	 * until there is a need क्रम more elaborate variants of पूर्णांकernal suspend.
	 */
	(व्योम) __dm_suspend(md, map, suspend_flags, TASK_UNINTERRUPTIBLE,
			    DMF_SUSPENDED_INTERNALLY);

	set_bit(DMF_POST_SUSPENDING, &md->flags);
	dm_table_postsuspend_tarमाला_लो(map);
	clear_bit(DMF_POST_SUSPENDING, &md->flags);
पूर्ण

अटल व्योम __dm_पूर्णांकernal_resume(काष्ठा mapped_device *md)
अणु
	BUG_ON(!md->पूर्णांकernal_suspend_count);

	अगर (--md->पूर्णांकernal_suspend_count)
		वापस; /* resume from nested पूर्णांकernal suspend */

	अगर (dm_suspended_md(md))
		जाओ करोne; /* resume from nested suspend */

	/*
	 * NOTE: existing callers करोn't need to call dm_table_resume_tarमाला_लो
	 * (which may fail -- so best to aव्योम it क्रम now by passing शून्य map)
	 */
	(व्योम) __dm_resume(md, शून्य);

करोne:
	clear_bit(DMF_SUSPENDED_INTERNALLY, &md->flags);
	smp_mb__after_atomic();
	wake_up_bit(&md->flags, DMF_SUSPENDED_INTERNALLY);
पूर्ण

व्योम dm_पूर्णांकernal_suspend_noflush(काष्ठा mapped_device *md)
अणु
	mutex_lock(&md->suspend_lock);
	__dm_पूर्णांकernal_suspend(md, DM_SUSPEND_NOFLUSH_FLAG);
	mutex_unlock(&md->suspend_lock);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पूर्णांकernal_suspend_noflush);

व्योम dm_पूर्णांकernal_resume(काष्ठा mapped_device *md)
अणु
	mutex_lock(&md->suspend_lock);
	__dm_पूर्णांकernal_resume(md);
	mutex_unlock(&md->suspend_lock);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पूर्णांकernal_resume);

/*
 * Fast variants of पूर्णांकernal suspend/resume hold md->suspend_lock,
 * which prevents पूर्णांकeraction with userspace-driven suspend.
 */

व्योम dm_पूर्णांकernal_suspend_fast(काष्ठा mapped_device *md)
अणु
	mutex_lock(&md->suspend_lock);
	अगर (dm_suspended_md(md) || dm_suspended_पूर्णांकernally_md(md))
		वापस;

	set_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags);
	synchronize_srcu(&md->io_barrier);
	flush_workqueue(md->wq);
	dm_रुको_क्रम_completion(md, TASK_UNINTERRUPTIBLE);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पूर्णांकernal_suspend_fast);

व्योम dm_पूर्णांकernal_resume_fast(काष्ठा mapped_device *md)
अणु
	अगर (dm_suspended_md(md) || dm_suspended_पूर्णांकernally_md(md))
		जाओ करोne;

	dm_queue_flush(md);

करोne:
	mutex_unlock(&md->suspend_lock);
पूर्ण
EXPORT_SYMBOL_GPL(dm_पूर्णांकernal_resume_fast);

/*-----------------------------------------------------------------
 * Event notअगरication.
 *---------------------------------------------------------------*/
पूर्णांक dm_kobject_uevent(काष्ठा mapped_device *md, क्रमागत kobject_action action,
		       अचिन्हित cookie)
अणु
	पूर्णांक r;
	अचिन्हित noio_flag;
	अक्षर udev_cookie[DM_COOKIE_LENGTH];
	अक्षर *envp[] = अणु udev_cookie, शून्य पूर्ण;

	noio_flag = meदो_स्मृति_noio_save();

	अगर (!cookie)
		r = kobject_uevent(&disk_to_dev(md->disk)->kobj, action);
	अन्यथा अणु
		snम_लिखो(udev_cookie, DM_COOKIE_LENGTH, "%s=%u",
			 DM_COOKIE_ENV_VAR_NAME, cookie);
		r = kobject_uevent_env(&disk_to_dev(md->disk)->kobj,
				       action, envp);
	पूर्ण

	meदो_स्मृति_noio_restore(noio_flag);

	वापस r;
पूर्ण

uपूर्णांक32_t dm_next_uevent_seq(काष्ठा mapped_device *md)
अणु
	वापस atomic_add_वापस(1, &md->uevent_seq);
पूर्ण

uपूर्णांक32_t dm_get_event_nr(काष्ठा mapped_device *md)
अणु
	वापस atomic_पढ़ो(&md->event_nr);
पूर्ण

पूर्णांक dm_रुको_event(काष्ठा mapped_device *md, पूर्णांक event_nr)
अणु
	वापस रुको_event_पूर्णांकerruptible(md->eventq,
			(event_nr != atomic_पढ़ो(&md->event_nr)));
पूर्ण

व्योम dm_uevent_add(काष्ठा mapped_device *md, काष्ठा list_head *elist)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&md->uevent_lock, flags);
	list_add(elist, &md->uevent_list);
	spin_unlock_irqrestore(&md->uevent_lock, flags);
पूर्ण

/*
 * The gendisk is only valid as दीर्घ as you have a reference
 * count on 'md'.
 */
काष्ठा gendisk *dm_disk(काष्ठा mapped_device *md)
अणु
	वापस md->disk;
पूर्ण
EXPORT_SYMBOL_GPL(dm_disk);

काष्ठा kobject *dm_kobject(काष्ठा mapped_device *md)
अणु
	वापस &md->kobj_holder.kobj;
पूर्ण

काष्ठा mapped_device *dm_get_from_kobject(काष्ठा kobject *kobj)
अणु
	काष्ठा mapped_device *md;

	md = container_of(kobj, काष्ठा mapped_device, kobj_holder.kobj);

	spin_lock(&_minor_lock);
	अगर (test_bit(DMF_FREEING, &md->flags) || dm_deleting_md(md)) अणु
		md = शून्य;
		जाओ out;
	पूर्ण
	dm_get(md);
out:
	spin_unlock(&_minor_lock);

	वापस md;
पूर्ण

पूर्णांक dm_suspended_md(काष्ठा mapped_device *md)
अणु
	वापस test_bit(DMF_SUSPENDED, &md->flags);
पूर्ण

अटल पूर्णांक dm_post_suspending_md(काष्ठा mapped_device *md)
अणु
	वापस test_bit(DMF_POST_SUSPENDING, &md->flags);
पूर्ण

पूर्णांक dm_suspended_पूर्णांकernally_md(काष्ठा mapped_device *md)
अणु
	वापस test_bit(DMF_SUSPENDED_INTERNALLY, &md->flags);
पूर्ण

पूर्णांक dm_test_deferred_हटाओ_flag(काष्ठा mapped_device *md)
अणु
	वापस test_bit(DMF_DEFERRED_REMOVE, &md->flags);
पूर्ण

पूर्णांक dm_suspended(काष्ठा dm_target *ti)
अणु
	वापस dm_suspended_md(ti->table->md);
पूर्ण
EXPORT_SYMBOL_GPL(dm_suspended);

पूर्णांक dm_post_suspending(काष्ठा dm_target *ti)
अणु
	वापस dm_post_suspending_md(ti->table->md);
पूर्ण
EXPORT_SYMBOL_GPL(dm_post_suspending);

पूर्णांक dm_noflush_suspending(काष्ठा dm_target *ti)
अणु
	वापस __noflush_suspending(ti->table->md);
पूर्ण
EXPORT_SYMBOL_GPL(dm_noflush_suspending);

काष्ठा dm_md_mempools *dm_alloc_md_mempools(काष्ठा mapped_device *md, क्रमागत dm_queue_mode type,
					    अचिन्हित पूर्णांकegrity, अचिन्हित per_io_data_size,
					    अचिन्हित min_pool_size)
अणु
	काष्ठा dm_md_mempools *pools = kzalloc_node(माप(*pools), GFP_KERNEL, md->numa_node_id);
	अचिन्हित पूर्णांक pool_size = 0;
	अचिन्हित पूर्णांक front_pad, io_front_pad;
	पूर्णांक ret;

	अगर (!pools)
		वापस शून्य;

	चयन (type) अणु
	हाल DM_TYPE_BIO_BASED:
	हाल DM_TYPE_DAX_BIO_BASED:
		pool_size = max(dm_get_reserved_bio_based_ios(), min_pool_size);
		front_pad = roundup(per_io_data_size, __alignof__(काष्ठा dm_target_io)) + DM_TARGET_IO_BIO_OFFSET;
		io_front_pad = roundup(per_io_data_size,  __alignof__(काष्ठा dm_io)) + DM_IO_BIO_OFFSET;
		ret = bioset_init(&pools->io_bs, pool_size, io_front_pad, 0);
		अगर (ret)
			जाओ out;
		अगर (पूर्णांकegrity && bioset_पूर्णांकegrity_create(&pools->io_bs, pool_size))
			जाओ out;
		अवरोध;
	हाल DM_TYPE_REQUEST_BASED:
		pool_size = max(dm_get_reserved_rq_based_ios(), min_pool_size);
		front_pad = दुरत्व(काष्ठा dm_rq_clone_bio_info, clone);
		/* per_io_data_size is used क्रम blk-mq pdu at queue allocation */
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	ret = bioset_init(&pools->bs, pool_size, front_pad, 0);
	अगर (ret)
		जाओ out;

	अगर (पूर्णांकegrity && bioset_पूर्णांकegrity_create(&pools->bs, pool_size))
		जाओ out;

	वापस pools;

out:
	dm_मुक्त_md_mempools(pools);

	वापस शून्य;
पूर्ण

व्योम dm_मुक्त_md_mempools(काष्ठा dm_md_mempools *pools)
अणु
	अगर (!pools)
		वापस;

	bioset_निकास(&pools->bs);
	bioset_निकास(&pools->io_bs);

	kमुक्त(pools);
पूर्ण

काष्ठा dm_pr अणु
	u64	old_key;
	u64	new_key;
	u32	flags;
	bool	fail_early;
पूर्ण;

अटल पूर्णांक dm_call_pr(काष्ठा block_device *bdev, iterate_devices_callout_fn fn,
		      व्योम *data)
अणु
	काष्ठा mapped_device *md = bdev->bd_disk->निजी_data;
	काष्ठा dm_table *table;
	काष्ठा dm_target *ti;
	पूर्णांक ret = -ENOTTY, srcu_idx;

	table = dm_get_live_table(md, &srcu_idx);
	अगर (!table || !dm_table_get_size(table))
		जाओ out;

	/* We only support devices that have a single target */
	अगर (dm_table_get_num_tarमाला_लो(table) != 1)
		जाओ out;
	ti = dm_table_get_target(table, 0);

	ret = -EINVAL;
	अगर (!ti->type->iterate_devices)
		जाओ out;

	ret = ti->type->iterate_devices(ti, fn, data);
out:
	dm_put_live_table(md, srcu_idx);
	वापस ret;
पूर्ण

/*
 * For रेजिस्टर / unरेजिस्टर we need to manually call out to every path.
 */
अटल पूर्णांक __dm_pr_रेजिस्टर(काष्ठा dm_target *ti, काष्ठा dm_dev *dev,
			    sector_t start, sector_t len, व्योम *data)
अणु
	काष्ठा dm_pr *pr = data;
	स्थिर काष्ठा pr_ops *ops = dev->bdev->bd_disk->fops->pr_ops;

	अगर (!ops || !ops->pr_रेजिस्टर)
		वापस -EOPNOTSUPP;
	वापस ops->pr_रेजिस्टर(dev->bdev, pr->old_key, pr->new_key, pr->flags);
पूर्ण

अटल पूर्णांक dm_pr_रेजिस्टर(काष्ठा block_device *bdev, u64 old_key, u64 new_key,
			  u32 flags)
अणु
	काष्ठा dm_pr pr = अणु
		.old_key	= old_key,
		.new_key	= new_key,
		.flags		= flags,
		.fail_early	= true,
	पूर्ण;
	पूर्णांक ret;

	ret = dm_call_pr(bdev, __dm_pr_रेजिस्टर, &pr);
	अगर (ret && new_key) अणु
		/* unरेजिस्टर all paths अगर we failed to रेजिस्टर any path */
		pr.old_key = new_key;
		pr.new_key = 0;
		pr.flags = 0;
		pr.fail_early = false;
		dm_call_pr(bdev, __dm_pr_रेजिस्टर, &pr);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dm_pr_reserve(काष्ठा block_device *bdev, u64 key, क्रमागत pr_type type,
			 u32 flags)
अणु
	काष्ठा mapped_device *md = bdev->bd_disk->निजी_data;
	स्थिर काष्ठा pr_ops *ops;
	पूर्णांक r, srcu_idx;

	r = dm_prepare_ioctl(md, &srcu_idx, &bdev);
	अगर (r < 0)
		जाओ out;

	ops = bdev->bd_disk->fops->pr_ops;
	अगर (ops && ops->pr_reserve)
		r = ops->pr_reserve(bdev, key, type, flags);
	अन्यथा
		r = -EOPNOTSUPP;
out:
	dm_unprepare_ioctl(md, srcu_idx);
	वापस r;
पूर्ण

अटल पूर्णांक dm_pr_release(काष्ठा block_device *bdev, u64 key, क्रमागत pr_type type)
अणु
	काष्ठा mapped_device *md = bdev->bd_disk->निजी_data;
	स्थिर काष्ठा pr_ops *ops;
	पूर्णांक r, srcu_idx;

	r = dm_prepare_ioctl(md, &srcu_idx, &bdev);
	अगर (r < 0)
		जाओ out;

	ops = bdev->bd_disk->fops->pr_ops;
	अगर (ops && ops->pr_release)
		r = ops->pr_release(bdev, key, type);
	अन्यथा
		r = -EOPNOTSUPP;
out:
	dm_unprepare_ioctl(md, srcu_idx);
	वापस r;
पूर्ण

अटल पूर्णांक dm_pr_preempt(काष्ठा block_device *bdev, u64 old_key, u64 new_key,
			 क्रमागत pr_type type, bool पात)
अणु
	काष्ठा mapped_device *md = bdev->bd_disk->निजी_data;
	स्थिर काष्ठा pr_ops *ops;
	पूर्णांक r, srcu_idx;

	r = dm_prepare_ioctl(md, &srcu_idx, &bdev);
	अगर (r < 0)
		जाओ out;

	ops = bdev->bd_disk->fops->pr_ops;
	अगर (ops && ops->pr_preempt)
		r = ops->pr_preempt(bdev, old_key, new_key, type, पात);
	अन्यथा
		r = -EOPNOTSUPP;
out:
	dm_unprepare_ioctl(md, srcu_idx);
	वापस r;
पूर्ण

अटल पूर्णांक dm_pr_clear(काष्ठा block_device *bdev, u64 key)
अणु
	काष्ठा mapped_device *md = bdev->bd_disk->निजी_data;
	स्थिर काष्ठा pr_ops *ops;
	पूर्णांक r, srcu_idx;

	r = dm_prepare_ioctl(md, &srcu_idx, &bdev);
	अगर (r < 0)
		जाओ out;

	ops = bdev->bd_disk->fops->pr_ops;
	अगर (ops && ops->pr_clear)
		r = ops->pr_clear(bdev, key);
	अन्यथा
		r = -EOPNOTSUPP;
out:
	dm_unprepare_ioctl(md, srcu_idx);
	वापस r;
पूर्ण

अटल स्थिर काष्ठा pr_ops dm_pr_ops = अणु
	.pr_रेजिस्टर	= dm_pr_रेजिस्टर,
	.pr_reserve	= dm_pr_reserve,
	.pr_release	= dm_pr_release,
	.pr_preempt	= dm_pr_preempt,
	.pr_clear	= dm_pr_clear,
पूर्ण;

अटल स्थिर काष्ठा block_device_operations dm_blk_करोps = अणु
	.submit_bio = dm_submit_bio,
	.खोलो = dm_blk_खोलो,
	.release = dm_blk_बंद,
	.ioctl = dm_blk_ioctl,
	.getgeo = dm_blk_getgeo,
	.report_zones = dm_blk_report_zones,
	.pr_ops = &dm_pr_ops,
	.owner = THIS_MODULE
पूर्ण;

अटल स्थिर काष्ठा block_device_operations dm_rq_blk_करोps = अणु
	.खोलो = dm_blk_खोलो,
	.release = dm_blk_बंद,
	.ioctl = dm_blk_ioctl,
	.getgeo = dm_blk_getgeo,
	.pr_ops = &dm_pr_ops,
	.owner = THIS_MODULE
पूर्ण;

अटल स्थिर काष्ठा dax_operations dm_dax_ops = अणु
	.direct_access = dm_dax_direct_access,
	.dax_supported = dm_dax_supported,
	.copy_from_iter = dm_dax_copy_from_iter,
	.copy_to_iter = dm_dax_copy_to_iter,
	.zero_page_range = dm_dax_zero_page_range,
पूर्ण;

/*
 * module hooks
 */
module_init(dm_init);
module_निकास(dm_निकास);

module_param(major, uपूर्णांक, 0);
MODULE_PARM_DESC(major, "The major number of the device mapper");

module_param(reserved_bio_based_ios, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(reserved_bio_based_ios, "Reserved IOs in bio-based mempools");

module_param(dm_numa_node, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dm_numa_node, "NUMA node for DM device memory allocations");

module_param(swap_bios, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(swap_bios, "Maximum allowed inflight swap IOs");

MODULE_DESCRIPTION(DM_NAME " driver");
MODULE_AUTHOR("Joe Thornber <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
