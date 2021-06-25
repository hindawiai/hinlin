<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/bपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/raid/pq.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/uuid.h>
#समावेश <linux/list_sort.h>
#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "extent_map.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "print-tree.h"
#समावेश "volumes.h"
#समावेश "raid56.h"
#समावेश "async-thread.h"
#समावेश "check-integrity.h"
#समावेश "rcu-string.h"
#समावेश "dev-replace.h"
#समावेश "sysfs.h"
#समावेश "tree-checker.h"
#समावेश "space-info.h"
#समावेश "block-group.h"
#समावेश "discard.h"
#समावेश "zoned.h"

स्थिर काष्ठा btrfs_raid_attr btrfs_raid_array[BTRFS_NR_RAID_TYPES] = अणु
	[BTRFS_RAID_RAID10] = अणु
		.sub_stripes	= 2,
		.dev_stripes	= 1,
		.devs_max	= 0,	/* 0 == as many as possible */
		.devs_min	= 4,
		.tolerated_failures = 1,
		.devs_increment	= 2,
		.ncopies	= 2,
		.nparity        = 0,
		.raid_name	= "raid10",
		.bg_flag	= BTRFS_BLOCK_GROUP_RAID10,
		.mindev_error	= BTRFS_ERROR_DEV_RAID10_MIN_NOT_MET,
	पूर्ण,
	[BTRFS_RAID_RAID1] = अणु
		.sub_stripes	= 1,
		.dev_stripes	= 1,
		.devs_max	= 2,
		.devs_min	= 2,
		.tolerated_failures = 1,
		.devs_increment	= 2,
		.ncopies	= 2,
		.nparity        = 0,
		.raid_name	= "raid1",
		.bg_flag	= BTRFS_BLOCK_GROUP_RAID1,
		.mindev_error	= BTRFS_ERROR_DEV_RAID1_MIN_NOT_MET,
	पूर्ण,
	[BTRFS_RAID_RAID1C3] = अणु
		.sub_stripes	= 1,
		.dev_stripes	= 1,
		.devs_max	= 3,
		.devs_min	= 3,
		.tolerated_failures = 2,
		.devs_increment	= 3,
		.ncopies	= 3,
		.nparity        = 0,
		.raid_name	= "raid1c3",
		.bg_flag	= BTRFS_BLOCK_GROUP_RAID1C3,
		.mindev_error	= BTRFS_ERROR_DEV_RAID1C3_MIN_NOT_MET,
	पूर्ण,
	[BTRFS_RAID_RAID1C4] = अणु
		.sub_stripes	= 1,
		.dev_stripes	= 1,
		.devs_max	= 4,
		.devs_min	= 4,
		.tolerated_failures = 3,
		.devs_increment	= 4,
		.ncopies	= 4,
		.nparity        = 0,
		.raid_name	= "raid1c4",
		.bg_flag	= BTRFS_BLOCK_GROUP_RAID1C4,
		.mindev_error	= BTRFS_ERROR_DEV_RAID1C4_MIN_NOT_MET,
	पूर्ण,
	[BTRFS_RAID_DUP] = अणु
		.sub_stripes	= 1,
		.dev_stripes	= 2,
		.devs_max	= 1,
		.devs_min	= 1,
		.tolerated_failures = 0,
		.devs_increment	= 1,
		.ncopies	= 2,
		.nparity        = 0,
		.raid_name	= "dup",
		.bg_flag	= BTRFS_BLOCK_GROUP_DUP,
		.mindev_error	= 0,
	पूर्ण,
	[BTRFS_RAID_RAID0] = अणु
		.sub_stripes	= 1,
		.dev_stripes	= 1,
		.devs_max	= 0,
		.devs_min	= 2,
		.tolerated_failures = 0,
		.devs_increment	= 1,
		.ncopies	= 1,
		.nparity        = 0,
		.raid_name	= "raid0",
		.bg_flag	= BTRFS_BLOCK_GROUP_RAID0,
		.mindev_error	= 0,
	पूर्ण,
	[BTRFS_RAID_SINGLE] = अणु
		.sub_stripes	= 1,
		.dev_stripes	= 1,
		.devs_max	= 1,
		.devs_min	= 1,
		.tolerated_failures = 0,
		.devs_increment	= 1,
		.ncopies	= 1,
		.nparity        = 0,
		.raid_name	= "single",
		.bg_flag	= 0,
		.mindev_error	= 0,
	पूर्ण,
	[BTRFS_RAID_RAID5] = अणु
		.sub_stripes	= 1,
		.dev_stripes	= 1,
		.devs_max	= 0,
		.devs_min	= 2,
		.tolerated_failures = 1,
		.devs_increment	= 1,
		.ncopies	= 1,
		.nparity        = 1,
		.raid_name	= "raid5",
		.bg_flag	= BTRFS_BLOCK_GROUP_RAID5,
		.mindev_error	= BTRFS_ERROR_DEV_RAID5_MIN_NOT_MET,
	पूर्ण,
	[BTRFS_RAID_RAID6] = अणु
		.sub_stripes	= 1,
		.dev_stripes	= 1,
		.devs_max	= 0,
		.devs_min	= 3,
		.tolerated_failures = 2,
		.devs_increment	= 1,
		.ncopies	= 1,
		.nparity        = 2,
		.raid_name	= "raid6",
		.bg_flag	= BTRFS_BLOCK_GROUP_RAID6,
		.mindev_error	= BTRFS_ERROR_DEV_RAID6_MIN_NOT_MET,
	पूर्ण,
पूर्ण;

स्थिर अक्षर *btrfs_bg_type_to_raid_name(u64 flags)
अणु
	स्थिर पूर्णांक index = btrfs_bg_flags_to_raid_index(flags);

	अगर (index >= BTRFS_NR_RAID_TYPES)
		वापस शून्य;

	वापस btrfs_raid_array[index].raid_name;
पूर्ण

/*
 * Fill @buf with textual description of @bg_flags, no more than @size_buf
 * bytes including terminating null byte.
 */
व्योम btrfs_describe_block_groups(u64 bg_flags, अक्षर *buf, u32 size_buf)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	अक्षर *bp = buf;
	u64 flags = bg_flags;
	u32 size_bp = size_buf;

	अगर (!flags) अणु
		म_नकल(bp, "NONE");
		वापस;
	पूर्ण

#घोषणा DESCRIBE_FLAG(flag, desc)						\
	करो अणु								\
		अगर (flags & (flag)) अणु					\
			ret = snम_लिखो(bp, size_bp, "%s|", (desc));	\
			अगर (ret < 0 || ret >= size_bp)			\
				जाओ out_overflow;			\
			size_bp -= ret;					\
			bp += ret;					\
			flags &= ~(flag);				\
		पूर्ण							\
	पूर्ण जबतक (0)

	DESCRIBE_FLAG(BTRFS_BLOCK_GROUP_DATA, "data");
	DESCRIBE_FLAG(BTRFS_BLOCK_GROUP_SYSTEM, "system");
	DESCRIBE_FLAG(BTRFS_BLOCK_GROUP_METADATA, "metadata");

	DESCRIBE_FLAG(BTRFS_AVAIL_ALLOC_BIT_SINGLE, "single");
	क्रम (i = 0; i < BTRFS_NR_RAID_TYPES; i++)
		DESCRIBE_FLAG(btrfs_raid_array[i].bg_flag,
			      btrfs_raid_array[i].raid_name);
#अघोषित DESCRIBE_FLAG

	अगर (flags) अणु
		ret = snम_लिखो(bp, size_bp, "0x%llx|", flags);
		size_bp -= ret;
	पूर्ण

	अगर (size_bp < size_buf)
		buf[size_buf - size_bp - 1] = '\0'; /* हटाओ last | */

	/*
	 * The text is trimmed, it's up to the caller to provide sufficiently
	 * large buffer
	 */
out_overflow:;
पूर्ण

अटल पूर्णांक init_first_rw_device(काष्ठा btrfs_trans_handle *trans);
अटल पूर्णांक btrfs_relocate_sys_chunks(काष्ठा btrfs_fs_info *fs_info);
अटल व्योम btrfs_dev_stat_prपूर्णांक_on_error(काष्ठा btrfs_device *dev);
अटल व्योम btrfs_dev_stat_prपूर्णांक_on_load(काष्ठा btrfs_device *device);
अटल पूर्णांक __btrfs_map_block(काष्ठा btrfs_fs_info *fs_info,
			     क्रमागत btrfs_map_op op,
			     u64 logical, u64 *length,
			     काष्ठा btrfs_bio **bbio_ret,
			     पूर्णांक mirror_num, पूर्णांक need_raid_map);

/*
 * Device locking
 * ==============
 *
 * There are several mutexes that protect manipulation of devices and low-level
 * काष्ठाures like chunks but not block groups, extents or files
 *
 * uuid_mutex (global lock)
 * ------------------------
 * protects the fs_uuids list that tracks all per-fs fs_devices, resulting from
 * the SCAN_DEV ioctl registration or from mount either implicitly (the first
 * device) or requested by the device= mount option
 *
 * the mutex can be very coarse and can cover दीर्घ-running operations
 *
 * protects: updates to fs_devices counters like missing devices, rw devices,
 * seeding, काष्ठाure cloning, खोलोing/closing devices at mount/umount समय
 *
 * global::fs_devs - add, हटाओ, updates to the global list
 *
 * करोes not protect: manipulation of the fs_devices::devices list in general
 * but in mount context it could be used to exclude list modअगरications by eg.
 * scan ioctl
 *
 * btrfs_device::name - नामs (ग_लिखो side), पढ़ो is RCU
 *
 * fs_devices::device_list_mutex (per-fs, with RCU)
 * ------------------------------------------------
 * protects updates to fs_devices::devices, ie. adding and deleting
 *
 * simple list traversal with पढ़ो-only actions can be करोne with RCU protection
 *
 * may be used to exclude some operations from running concurrently without any
 * modअगरications to the list (see ग_लिखो_all_supers)
 *
 * Is not required at mount and बंद बार, because our device list is
 * रक्षित by the uuid_mutex at that poपूर्णांक.
 *
 * balance_mutex
 * -------------
 * protects balance काष्ठाures (status, state) and context accessed from
 * several places (पूर्णांकernally, ioctl)
 *
 * chunk_mutex
 * -----------
 * protects chunks, adding or removing during allocation, trim or when a new
 * device is added/हटाओd. Additionally it also protects post_commit_list of
 * inभागidual devices, since they can be added to the transaction's
 * post_commit_list only with chunk_mutex held.
 *
 * cleaner_mutex
 * -------------
 * a big lock that is held by the cleaner thपढ़ो and prevents running subvolume
 * cleaning together with relocation or delayed iमाला_दो
 *
 *
 * Lock nesting
 * ============
 *
 * uuid_mutex
 *   device_list_mutex
 *     chunk_mutex
 *   balance_mutex
 *
 *
 * Exclusive operations
 * ====================
 *
 * Maपूर्णांकains the exclusivity of the following operations that apply to the
 * whole fileप्रणाली and cannot run in parallel.
 *
 * - Balance (*)
 * - Device add
 * - Device हटाओ
 * - Device replace (*)
 * - Resize
 *
 * The device operations (as above) can be in one of the following states:
 *
 * - Running state
 * - Paused state
 * - Completed state
 *
 * Only device operations marked with (*) can go पूर्णांकo the Paused state क्रम the
 * following reasons:
 *
 * - ioctl (only Balance can be Paused through ioctl)
 * - fileप्रणाली remounted as पढ़ो-only
 * - fileप्रणाली unmounted and mounted as पढ़ो-only
 * - प्रणाली घातer-cycle and fileप्रणाली mounted as पढ़ो-only
 * - fileप्रणाली or device errors leading to क्रमced पढ़ो-only
 *
 * The status of exclusive operation is set and cleared atomically.
 * During the course of Paused state, fs_info::exclusive_operation reमुख्यs set.
 * A device operation in Paused or Running state can be canceled or resumed
 * either by ioctl (Balance only) or when remounted as पढ़ो-ग_लिखो.
 * The exclusive status is cleared when the device operation is canceled or
 * completed.
 */

DEFINE_MUTEX(uuid_mutex);
अटल LIST_HEAD(fs_uuids);
काष्ठा list_head * __attribute_स्थिर__ btrfs_get_fs_uuids(व्योम)
अणु
	वापस &fs_uuids;
पूर्ण

/*
 * alloc_fs_devices - allocate काष्ठा btrfs_fs_devices
 * @fsid:		अगर not शून्य, copy the UUID to fs_devices::fsid
 * @metadata_fsid:	अगर not शून्य, copy the UUID to fs_devices::metadata_fsid
 *
 * Return a poपूर्णांकer to a new काष्ठा btrfs_fs_devices on success, or ERR_PTR().
 * The वापसed काष्ठा is not linked onto any lists and can be destroyed with
 * kमुक्त() right away.
 */
अटल काष्ठा btrfs_fs_devices *alloc_fs_devices(स्थिर u8 *fsid,
						 स्थिर u8 *metadata_fsid)
अणु
	काष्ठा btrfs_fs_devices *fs_devs;

	fs_devs = kzalloc(माप(*fs_devs), GFP_KERNEL);
	अगर (!fs_devs)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&fs_devs->device_list_mutex);

	INIT_LIST_HEAD(&fs_devs->devices);
	INIT_LIST_HEAD(&fs_devs->alloc_list);
	INIT_LIST_HEAD(&fs_devs->fs_list);
	INIT_LIST_HEAD(&fs_devs->seed_list);
	अगर (fsid)
		स_नकल(fs_devs->fsid, fsid, BTRFS_FSID_SIZE);

	अगर (metadata_fsid)
		स_नकल(fs_devs->metadata_uuid, metadata_fsid, BTRFS_FSID_SIZE);
	अन्यथा अगर (fsid)
		स_नकल(fs_devs->metadata_uuid, fsid, BTRFS_FSID_SIZE);

	वापस fs_devs;
पूर्ण

व्योम btrfs_मुक्त_device(काष्ठा btrfs_device *device)
अणु
	WARN_ON(!list_empty(&device->post_commit_list));
	rcu_string_मुक्त(device->name);
	extent_io_tree_release(&device->alloc_state);
	bio_put(device->flush_bio);
	btrfs_destroy_dev_zone_info(device);
	kमुक्त(device);
पूर्ण

अटल व्योम मुक्त_fs_devices(काष्ठा btrfs_fs_devices *fs_devices)
अणु
	काष्ठा btrfs_device *device;
	WARN_ON(fs_devices->खोलोed);
	जबतक (!list_empty(&fs_devices->devices)) अणु
		device = list_entry(fs_devices->devices.next,
				    काष्ठा btrfs_device, dev_list);
		list_del(&device->dev_list);
		btrfs_मुक्त_device(device);
	पूर्ण
	kमुक्त(fs_devices);
पूर्ण

व्योम __निकास btrfs_cleanup_fs_uuids(व्योम)
अणु
	काष्ठा btrfs_fs_devices *fs_devices;

	जबतक (!list_empty(&fs_uuids)) अणु
		fs_devices = list_entry(fs_uuids.next,
					काष्ठा btrfs_fs_devices, fs_list);
		list_del(&fs_devices->fs_list);
		मुक्त_fs_devices(fs_devices);
	पूर्ण
पूर्ण

/*
 * Returns a poपूर्णांकer to a new btrfs_device on success; ERR_PTR() on error.
 * Returned काष्ठा is not linked onto any lists and must be destroyed using
 * btrfs_मुक्त_device.
 */
अटल काष्ठा btrfs_device *__alloc_device(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_device *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * Pपुनः_स्मृतिate a bio that's always going to be used क्रम flushing device
	 * barriers and matches the device lअगरespan
	 */
	dev->flush_bio = bio_kदो_स्मृति(GFP_KERNEL, 0);
	अगर (!dev->flush_bio) अणु
		kमुक्त(dev);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	INIT_LIST_HEAD(&dev->dev_list);
	INIT_LIST_HEAD(&dev->dev_alloc_list);
	INIT_LIST_HEAD(&dev->post_commit_list);

	atomic_set(&dev->पढ़ोa_in_flight, 0);
	atomic_set(&dev->dev_stats_ccnt, 0);
	btrfs_device_data_ordered_init(dev);
	INIT_RADIX_TREE(&dev->पढ़ोa_zones, GFP_NOFS & ~__GFP_सूचीECT_RECLAIM);
	INIT_RADIX_TREE(&dev->पढ़ोa_extents, GFP_NOFS & ~__GFP_सूचीECT_RECLAIM);
	extent_io_tree_init(fs_info, &dev->alloc_state,
			    IO_TREE_DEVICE_ALLOC_STATE, शून्य);

	वापस dev;
पूर्ण

अटल noअंतरभूत काष्ठा btrfs_fs_devices *find_fsid(
		स्थिर u8 *fsid, स्थिर u8 *metadata_fsid)
अणु
	काष्ठा btrfs_fs_devices *fs_devices;

	ASSERT(fsid);

	/* Handle non-split brain हालs */
	list_क्रम_each_entry(fs_devices, &fs_uuids, fs_list) अणु
		अगर (metadata_fsid) अणु
			अगर (स_भेद(fsid, fs_devices->fsid, BTRFS_FSID_SIZE) == 0
			    && स_भेद(metadata_fsid, fs_devices->metadata_uuid,
				      BTRFS_FSID_SIZE) == 0)
				वापस fs_devices;
		पूर्ण अन्यथा अणु
			अगर (स_भेद(fsid, fs_devices->fsid, BTRFS_FSID_SIZE) == 0)
				वापस fs_devices;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा btrfs_fs_devices *find_fsid_with_metadata_uuid(
				काष्ठा btrfs_super_block *disk_super)
अणु

	काष्ठा btrfs_fs_devices *fs_devices;

	/*
	 * Handle scanned device having completed its fsid change but
	 * beदीर्घing to a fs_devices that was created by first scanning
	 * a device which didn't have its fsid/metadata_uuid changed
	 * at all and the CHANGING_FSID_V2 flag set.
	 */
	list_क्रम_each_entry(fs_devices, &fs_uuids, fs_list) अणु
		अगर (fs_devices->fsid_change &&
		    स_भेद(disk_super->metadata_uuid, fs_devices->fsid,
			   BTRFS_FSID_SIZE) == 0 &&
		    स_भेद(fs_devices->fsid, fs_devices->metadata_uuid,
			   BTRFS_FSID_SIZE) == 0) अणु
			वापस fs_devices;
		पूर्ण
	पूर्ण
	/*
	 * Handle scanned device having completed its fsid change but
	 * beदीर्घing to a fs_devices that was created by a device that
	 * has an outdated pair of fsid/metadata_uuid and
	 * CHANGING_FSID_V2 flag set.
	 */
	list_क्रम_each_entry(fs_devices, &fs_uuids, fs_list) अणु
		अगर (fs_devices->fsid_change &&
		    स_भेद(fs_devices->metadata_uuid,
			   fs_devices->fsid, BTRFS_FSID_SIZE) != 0 &&
		    स_भेद(disk_super->metadata_uuid, fs_devices->metadata_uuid,
			   BTRFS_FSID_SIZE) == 0) अणु
			वापस fs_devices;
		पूर्ण
	पूर्ण

	वापस find_fsid(disk_super->fsid, disk_super->metadata_uuid);
पूर्ण


अटल पूर्णांक
btrfs_get_bdev_and_sb(स्थिर अक्षर *device_path, भ_शेषe_t flags, व्योम *holder,
		      पूर्णांक flush, काष्ठा block_device **bdev,
		      काष्ठा btrfs_super_block **disk_super)
अणु
	पूर्णांक ret;

	*bdev = blkdev_get_by_path(device_path, flags, holder);

	अगर (IS_ERR(*bdev)) अणु
		ret = PTR_ERR(*bdev);
		जाओ error;
	पूर्ण

	अगर (flush)
		filemap_ग_लिखो_and_रुको((*bdev)->bd_inode->i_mapping);
	ret = set_blocksize(*bdev, BTRFS_BDEV_BLOCKSIZE);
	अगर (ret) अणु
		blkdev_put(*bdev, flags);
		जाओ error;
	पूर्ण
	invalidate_bdev(*bdev);
	*disk_super = btrfs_पढ़ो_dev_super(*bdev);
	अगर (IS_ERR(*disk_super)) अणु
		ret = PTR_ERR(*disk_super);
		blkdev_put(*bdev, flags);
		जाओ error;
	पूर्ण

	वापस 0;

error:
	*bdev = शून्य;
	वापस ret;
पूर्ण

अटल bool device_path_matched(स्थिर अक्षर *path, काष्ठा btrfs_device *device)
अणु
	पूर्णांक found;

	rcu_पढ़ो_lock();
	found = म_भेद(rcu_str_deref(device->name), path);
	rcu_पढ़ो_unlock();

	वापस found == 0;
पूर्ण

/*
 *  Search and हटाओ all stale (devices which are not mounted) devices.
 *  When both inमाला_दो are शून्य, it will search and release all stale devices.
 *  path:	Optional. When provided will it release all unmounted devices
 *		matching this path only.
 *  skip_dev:	Optional. Will skip this device when searching क्रम the stale
 *		devices.
 *  Return:	0 क्रम success or अगर @path is शून्य.
 * 		-EBUSY अगर @path is a mounted device.
 * 		-ENOENT अगर @path करोes not match any device in the list.
 */
अटल पूर्णांक btrfs_मुक्त_stale_devices(स्थिर अक्षर *path,
				     काष्ठा btrfs_device *skip_device)
अणु
	काष्ठा btrfs_fs_devices *fs_devices, *पंचांगp_fs_devices;
	काष्ठा btrfs_device *device, *पंचांगp_device;
	पूर्णांक ret = 0;

	अगर (path)
		ret = -ENOENT;

	list_क्रम_each_entry_safe(fs_devices, पंचांगp_fs_devices, &fs_uuids, fs_list) अणु

		mutex_lock(&fs_devices->device_list_mutex);
		list_क्रम_each_entry_safe(device, पंचांगp_device,
					 &fs_devices->devices, dev_list) अणु
			अगर (skip_device && skip_device == device)
				जारी;
			अगर (path && !device->name)
				जारी;
			अगर (path && !device_path_matched(path, device))
				जारी;
			अगर (fs_devices->खोलोed) अणु
				/* क्रम an alपढ़ोy deleted device वापस 0 */
				अगर (path && ret != 0)
					ret = -EBUSY;
				अवरोध;
			पूर्ण

			/* delete the stale device */
			fs_devices->num_devices--;
			list_del(&device->dev_list);
			btrfs_मुक्त_device(device);

			ret = 0;
		पूर्ण
		mutex_unlock(&fs_devices->device_list_mutex);

		अगर (fs_devices->num_devices == 0) अणु
			btrfs_sysfs_हटाओ_fsid(fs_devices);
			list_del(&fs_devices->fs_list);
			मुक्त_fs_devices(fs_devices);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This is only used on mount, and we are रक्षित from competing things
 * messing with our fs_devices by the uuid_mutex, thus we करो not need the
 * fs_devices->device_list_mutex here.
 */
अटल पूर्णांक btrfs_खोलो_one_device(काष्ठा btrfs_fs_devices *fs_devices,
			काष्ठा btrfs_device *device, भ_शेषe_t flags,
			व्योम *holder)
अणु
	काष्ठा request_queue *q;
	काष्ठा block_device *bdev;
	काष्ठा btrfs_super_block *disk_super;
	u64 devid;
	पूर्णांक ret;

	अगर (device->bdev)
		वापस -EINVAL;
	अगर (!device->name)
		वापस -EINVAL;

	ret = btrfs_get_bdev_and_sb(device->name->str, flags, holder, 1,
				    &bdev, &disk_super);
	अगर (ret)
		वापस ret;

	devid = btrfs_stack_device_id(&disk_super->dev_item);
	अगर (devid != device->devid)
		जाओ error_मुक्त_page;

	अगर (स_भेद(device->uuid, disk_super->dev_item.uuid, BTRFS_UUID_SIZE))
		जाओ error_मुक्त_page;

	device->generation = btrfs_super_generation(disk_super);

	अगर (btrfs_super_flags(disk_super) & BTRFS_SUPER_FLAG_SEEDING) अणु
		अगर (btrfs_super_incompat_flags(disk_super) &
		    BTRFS_FEATURE_INCOMPAT_METADATA_UUID) अणु
			pr_err(
		"BTRFS: Invalid seeding and uuid-changed device detected\n");
			जाओ error_मुक्त_page;
		पूर्ण

		clear_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state);
		fs_devices->seeding = true;
	पूर्ण अन्यथा अणु
		अगर (bdev_पढ़ो_only(bdev))
			clear_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state);
		अन्यथा
			set_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state);
	पूर्ण

	q = bdev_get_queue(bdev);
	अगर (!blk_queue_nonrot(q))
		fs_devices->rotating = true;

	device->bdev = bdev;
	clear_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &device->dev_state);
	device->mode = flags;

	fs_devices->खोलो_devices++;
	अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state) &&
	    device->devid != BTRFS_DEV_REPLACE_DEVID) अणु
		fs_devices->rw_devices++;
		list_add_tail(&device->dev_alloc_list, &fs_devices->alloc_list);
	पूर्ण
	btrfs_release_disk_super(disk_super);

	वापस 0;

error_मुक्त_page:
	btrfs_release_disk_super(disk_super);
	blkdev_put(bdev, flags);

	वापस -EINVAL;
पूर्ण

/*
 * Handle scanned device having its CHANGING_FSID_V2 flag set and the fs_devices
 * being created with a disk that has alपढ़ोy completed its fsid change. Such
 * disk can beदीर्घ to an fs which has its FSID changed or to one which करोesn't.
 * Handle both हालs here.
 */
अटल काष्ठा btrfs_fs_devices *find_fsid_inprogress(
					काष्ठा btrfs_super_block *disk_super)
अणु
	काष्ठा btrfs_fs_devices *fs_devices;

	list_क्रम_each_entry(fs_devices, &fs_uuids, fs_list) अणु
		अगर (स_भेद(fs_devices->metadata_uuid, fs_devices->fsid,
			   BTRFS_FSID_SIZE) != 0 &&
		    स_भेद(fs_devices->metadata_uuid, disk_super->fsid,
			   BTRFS_FSID_SIZE) == 0 && !fs_devices->fsid_change) अणु
			वापस fs_devices;
		पूर्ण
	पूर्ण

	वापस find_fsid(disk_super->fsid, शून्य);
पूर्ण


अटल काष्ठा btrfs_fs_devices *find_fsid_changed(
					काष्ठा btrfs_super_block *disk_super)
अणु
	काष्ठा btrfs_fs_devices *fs_devices;

	/*
	 * Handles the हाल where scanned device is part of an fs that had
	 * multiple successful changes of FSID but curently device didn't
	 * observe it. Meaning our fsid will be dअगरferent than theirs. We need
	 * to handle two subहालs :
	 *  1 - The fs still जारीs to have dअगरferent METADATA/FSID uuids.
	 *  2 - The fs is चयनed back to its original FSID (METADATA/FSID
	 *  are equal).
	 */
	list_क्रम_each_entry(fs_devices, &fs_uuids, fs_list) अणु
		/* Changed UUIDs */
		अगर (स_भेद(fs_devices->metadata_uuid, fs_devices->fsid,
			   BTRFS_FSID_SIZE) != 0 &&
		    स_भेद(fs_devices->metadata_uuid, disk_super->metadata_uuid,
			   BTRFS_FSID_SIZE) == 0 &&
		    स_भेद(fs_devices->fsid, disk_super->fsid,
			   BTRFS_FSID_SIZE) != 0)
			वापस fs_devices;

		/* Unchanged UUIDs */
		अगर (स_भेद(fs_devices->metadata_uuid, fs_devices->fsid,
			   BTRFS_FSID_SIZE) == 0 &&
		    स_भेद(fs_devices->fsid, disk_super->metadata_uuid,
			   BTRFS_FSID_SIZE) == 0)
			वापस fs_devices;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा btrfs_fs_devices *find_fsid_reverted_metadata(
				काष्ठा btrfs_super_block *disk_super)
अणु
	काष्ठा btrfs_fs_devices *fs_devices;

	/*
	 * Handle the हाल where the scanned device is part of an fs whose last
	 * metadata UUID change reverted it to the original FSID. At the same
	 * समय * fs_devices was first created by another स्थिरitutent device
	 * which didn't fully observe the operation. This results in an
	 * btrfs_fs_devices created with metadata/fsid dअगरferent AND
	 * btrfs_fs_devices::fsid_change set AND the metadata_uuid of the
	 * fs_devices equal to the FSID of the disk.
	 */
	list_क्रम_each_entry(fs_devices, &fs_uuids, fs_list) अणु
		अगर (स_भेद(fs_devices->fsid, fs_devices->metadata_uuid,
			   BTRFS_FSID_SIZE) != 0 &&
		    स_भेद(fs_devices->metadata_uuid, disk_super->fsid,
			   BTRFS_FSID_SIZE) == 0 &&
		    fs_devices->fsid_change)
			वापस fs_devices;
	पूर्ण

	वापस शून्य;
पूर्ण
/*
 * Add new device to list of रेजिस्टरed devices
 *
 * Returns:
 * device poपूर्णांकer which was just added or updated when successful
 * error poपूर्णांकer when failed
 */
अटल noअंतरभूत काष्ठा btrfs_device *device_list_add(स्थिर अक्षर *path,
			   काष्ठा btrfs_super_block *disk_super,
			   bool *new_device_added)
अणु
	काष्ठा btrfs_device *device;
	काष्ठा btrfs_fs_devices *fs_devices = शून्य;
	काष्ठा rcu_string *name;
	u64 found_transid = btrfs_super_generation(disk_super);
	u64 devid = btrfs_stack_device_id(&disk_super->dev_item);
	bool has_metadata_uuid = (btrfs_super_incompat_flags(disk_super) &
		BTRFS_FEATURE_INCOMPAT_METADATA_UUID);
	bool fsid_change_in_progress = (btrfs_super_flags(disk_super) &
					BTRFS_SUPER_FLAG_CHANGING_FSID_V2);

	अगर (fsid_change_in_progress) अणु
		अगर (!has_metadata_uuid)
			fs_devices = find_fsid_inprogress(disk_super);
		अन्यथा
			fs_devices = find_fsid_changed(disk_super);
	पूर्ण अन्यथा अगर (has_metadata_uuid) अणु
		fs_devices = find_fsid_with_metadata_uuid(disk_super);
	पूर्ण अन्यथा अणु
		fs_devices = find_fsid_reverted_metadata(disk_super);
		अगर (!fs_devices)
			fs_devices = find_fsid(disk_super->fsid, शून्य);
	पूर्ण


	अगर (!fs_devices) अणु
		अगर (has_metadata_uuid)
			fs_devices = alloc_fs_devices(disk_super->fsid,
						      disk_super->metadata_uuid);
		अन्यथा
			fs_devices = alloc_fs_devices(disk_super->fsid, शून्य);

		अगर (IS_ERR(fs_devices))
			वापस ERR_CAST(fs_devices);

		fs_devices->fsid_change = fsid_change_in_progress;

		mutex_lock(&fs_devices->device_list_mutex);
		list_add(&fs_devices->fs_list, &fs_uuids);

		device = शून्य;
	पूर्ण अन्यथा अणु
		mutex_lock(&fs_devices->device_list_mutex);
		device = btrfs_find_device(fs_devices, devid,
				disk_super->dev_item.uuid, शून्य);

		/*
		 * If this disk has been pulled पूर्णांकo an fs devices created by
		 * a device which had the CHANGING_FSID_V2 flag then replace the
		 * metadata_uuid/fsid values of the fs_devices.
		 */
		अगर (fs_devices->fsid_change &&
		    found_transid > fs_devices->latest_generation) अणु
			स_नकल(fs_devices->fsid, disk_super->fsid,
					BTRFS_FSID_SIZE);

			अगर (has_metadata_uuid)
				स_नकल(fs_devices->metadata_uuid,
				       disk_super->metadata_uuid,
				       BTRFS_FSID_SIZE);
			अन्यथा
				स_नकल(fs_devices->metadata_uuid,
				       disk_super->fsid, BTRFS_FSID_SIZE);

			fs_devices->fsid_change = false;
		पूर्ण
	पूर्ण

	अगर (!device) अणु
		अगर (fs_devices->खोलोed) अणु
			mutex_unlock(&fs_devices->device_list_mutex);
			वापस ERR_PTR(-EBUSY);
		पूर्ण

		device = btrfs_alloc_device(शून्य, &devid,
					    disk_super->dev_item.uuid);
		अगर (IS_ERR(device)) अणु
			mutex_unlock(&fs_devices->device_list_mutex);
			/* we can safely leave the fs_devices entry around */
			वापस device;
		पूर्ण

		name = rcu_string_strdup(path, GFP_NOFS);
		अगर (!name) अणु
			btrfs_मुक्त_device(device);
			mutex_unlock(&fs_devices->device_list_mutex);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		rcu_assign_poपूर्णांकer(device->name, name);

		list_add_rcu(&device->dev_list, &fs_devices->devices);
		fs_devices->num_devices++;

		device->fs_devices = fs_devices;
		*new_device_added = true;

		अगर (disk_super->label[0])
			pr_info(
	"BTRFS: device label %s devid %llu transid %llu %s scanned by %s (%d)\n",
				disk_super->label, devid, found_transid, path,
				current->comm, task_pid_nr(current));
		अन्यथा
			pr_info(
	"BTRFS: device fsid %pU devid %llu transid %llu %s scanned by %s (%d)\n",
				disk_super->fsid, devid, found_transid, path,
				current->comm, task_pid_nr(current));

	पूर्ण अन्यथा अगर (!device->name || म_भेद(device->name->str, path)) अणु
		/*
		 * When FS is alपढ़ोy mounted.
		 * 1. If you are here and अगर the device->name is शून्य that
		 *    means this device was missing at समय of FS mount.
		 * 2. If you are here and अगर the device->name is dअगरferent
		 *    from 'path' that means either
		 *      a. The same device disappeared and reappeared with
		 *         dअगरferent name. or
		 *      b. The missing-disk-which-was-replaced, has
		 *         reappeared now.
		 *
		 * We must allow 1 and 2a above. But 2b would be a spurious
		 * and unपूर्णांकentional.
		 *
		 * Further in हाल of 1 and 2a above, the disk at 'path'
		 * would have missed some transaction when it was away and
		 * in हाल of 2a the stale bdev has to be updated as well.
		 * 2b must not be allowed at all समय.
		 */

		/*
		 * For now, we करो allow update to btrfs_fs_device through the
		 * btrfs dev scan cli after FS has been mounted.  We're still
		 * tracking a problem where प्रणालीs fail mount by subvolume id
		 * when we reject replacement on a mounted FS.
		 */
		अगर (!fs_devices->खोलोed && found_transid < device->generation) अणु
			/*
			 * That is अगर the FS is _not_ mounted and अगर you
			 * are here, that means there is more than one
			 * disk with same uuid and devid.We keep the one
			 * with larger generation number or the last-in अगर
			 * generation are equal.
			 */
			mutex_unlock(&fs_devices->device_list_mutex);
			वापस ERR_PTR(-EEXIST);
		पूर्ण

		/*
		 * We are going to replace the device path क्रम a given devid,
		 * make sure it's the same device अगर the device is mounted
		 */
		अगर (device->bdev) अणु
			पूर्णांक error;
			dev_t path_dev;

			error = lookup_bdev(path, &path_dev);
			अगर (error) अणु
				mutex_unlock(&fs_devices->device_list_mutex);
				वापस ERR_PTR(error);
			पूर्ण

			अगर (device->bdev->bd_dev != path_dev) अणु
				mutex_unlock(&fs_devices->device_list_mutex);
				/*
				 * device->fs_info may not be reliable here, so
				 * pass in a शून्य instead. This aव्योमs a
				 * possible use-after-मुक्त when the fs_info and
				 * fs_info->sb are alपढ़ोy torn करोwn.
				 */
				btrfs_warn_in_rcu(शून्य,
	"duplicate device %s devid %llu generation %llu scanned by %s (%d)",
						  path, devid, found_transid,
						  current->comm,
						  task_pid_nr(current));
				वापस ERR_PTR(-EEXIST);
			पूर्ण
			btrfs_info_in_rcu(device->fs_info,
	"devid %llu device path %s changed to %s scanned by %s (%d)",
					  devid, rcu_str_deref(device->name),
					  path, current->comm,
					  task_pid_nr(current));
		पूर्ण

		name = rcu_string_strdup(path, GFP_NOFS);
		अगर (!name) अणु
			mutex_unlock(&fs_devices->device_list_mutex);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		rcu_string_मुक्त(device->name);
		rcu_assign_poपूर्णांकer(device->name, name);
		अगर (test_bit(BTRFS_DEV_STATE_MISSING, &device->dev_state)) अणु
			fs_devices->missing_devices--;
			clear_bit(BTRFS_DEV_STATE_MISSING, &device->dev_state);
		पूर्ण
	पूर्ण

	/*
	 * Unmount करोes not मुक्त the btrfs_device काष्ठा but would zero
	 * generation aदीर्घ with most of the other members. So just update
	 * it back. We need it to pick the disk with largest generation
	 * (as above).
	 */
	अगर (!fs_devices->खोलोed) अणु
		device->generation = found_transid;
		fs_devices->latest_generation = max_t(u64, found_transid,
						fs_devices->latest_generation);
	पूर्ण

	fs_devices->total_devices = btrfs_super_num_devices(disk_super);

	mutex_unlock(&fs_devices->device_list_mutex);
	वापस device;
पूर्ण

अटल काष्ठा btrfs_fs_devices *clone_fs_devices(काष्ठा btrfs_fs_devices *orig)
अणु
	काष्ठा btrfs_fs_devices *fs_devices;
	काष्ठा btrfs_device *device;
	काष्ठा btrfs_device *orig_dev;
	पूर्णांक ret = 0;

	fs_devices = alloc_fs_devices(orig->fsid, शून्य);
	अगर (IS_ERR(fs_devices))
		वापस fs_devices;

	mutex_lock(&orig->device_list_mutex);
	fs_devices->total_devices = orig->total_devices;

	list_क्रम_each_entry(orig_dev, &orig->devices, dev_list) अणु
		काष्ठा rcu_string *name;

		device = btrfs_alloc_device(शून्य, &orig_dev->devid,
					    orig_dev->uuid);
		अगर (IS_ERR(device)) अणु
			ret = PTR_ERR(device);
			जाओ error;
		पूर्ण

		/*
		 * This is ok to करो without rcu पढ़ो locked because we hold the
		 * uuid mutex so nothing we touch in here is going to disappear.
		 */
		अगर (orig_dev->name) अणु
			name = rcu_string_strdup(orig_dev->name->str,
					GFP_KERNEL);
			अगर (!name) अणु
				btrfs_मुक्त_device(device);
				ret = -ENOMEM;
				जाओ error;
			पूर्ण
			rcu_assign_poपूर्णांकer(device->name, name);
		पूर्ण

		list_add(&device->dev_list, &fs_devices->devices);
		device->fs_devices = fs_devices;
		fs_devices->num_devices++;
	पूर्ण
	mutex_unlock(&orig->device_list_mutex);
	वापस fs_devices;
error:
	mutex_unlock(&orig->device_list_mutex);
	मुक्त_fs_devices(fs_devices);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम __btrfs_मुक्त_extra_devids(काष्ठा btrfs_fs_devices *fs_devices,
				      काष्ठा btrfs_device **latest_dev)
अणु
	काष्ठा btrfs_device *device, *next;

	/* This is the initialized path, it is safe to release the devices. */
	list_क्रम_each_entry_safe(device, next, &fs_devices->devices, dev_list) अणु
		अगर (test_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &device->dev_state)) अणु
			अगर (!test_bit(BTRFS_DEV_STATE_REPLACE_TGT,
				      &device->dev_state) &&
			    !test_bit(BTRFS_DEV_STATE_MISSING,
				      &device->dev_state) &&
			    (!*latest_dev ||
			     device->generation > (*latest_dev)->generation)) अणु
				*latest_dev = device;
			पूर्ण
			जारी;
		पूर्ण

		/*
		 * We have alपढ़ोy validated the presence of BTRFS_DEV_REPLACE_DEVID,
		 * in btrfs_init_dev_replace() so just जारी.
		 */
		अगर (device->devid == BTRFS_DEV_REPLACE_DEVID)
			जारी;

		अगर (device->bdev) अणु
			blkdev_put(device->bdev, device->mode);
			device->bdev = शून्य;
			fs_devices->खोलो_devices--;
		पूर्ण
		अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state)) अणु
			list_del_init(&device->dev_alloc_list);
			clear_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state);
		पूर्ण
		list_del_init(&device->dev_list);
		fs_devices->num_devices--;
		btrfs_मुक्त_device(device);
	पूर्ण

पूर्ण

/*
 * After we have पढ़ो the प्रणाली tree and know devids beदीर्घing to this
 * fileप्रणाली, हटाओ the device which करोes not beदीर्घ there.
 */
व्योम btrfs_मुक्त_extra_devids(काष्ठा btrfs_fs_devices *fs_devices)
अणु
	काष्ठा btrfs_device *latest_dev = शून्य;
	काष्ठा btrfs_fs_devices *seed_dev;

	mutex_lock(&uuid_mutex);
	__btrfs_मुक्त_extra_devids(fs_devices, &latest_dev);

	list_क्रम_each_entry(seed_dev, &fs_devices->seed_list, seed_list)
		__btrfs_मुक्त_extra_devids(seed_dev, &latest_dev);

	fs_devices->latest_bdev = latest_dev->bdev;

	mutex_unlock(&uuid_mutex);
पूर्ण

अटल व्योम btrfs_बंद_bdev(काष्ठा btrfs_device *device)
अणु
	अगर (!device->bdev)
		वापस;

	अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state)) अणु
		sync_blockdev(device->bdev);
		invalidate_bdev(device->bdev);
	पूर्ण

	blkdev_put(device->bdev, device->mode);
पूर्ण

अटल व्योम btrfs_बंद_one_device(काष्ठा btrfs_device *device)
अणु
	काष्ठा btrfs_fs_devices *fs_devices = device->fs_devices;

	अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state) &&
	    device->devid != BTRFS_DEV_REPLACE_DEVID) अणु
		list_del_init(&device->dev_alloc_list);
		fs_devices->rw_devices--;
	पूर्ण

	अगर (test_bit(BTRFS_DEV_STATE_MISSING, &device->dev_state))
		fs_devices->missing_devices--;

	btrfs_बंद_bdev(device);
	अगर (device->bdev) अणु
		fs_devices->खोलो_devices--;
		device->bdev = शून्य;
	पूर्ण
	clear_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state);
	btrfs_destroy_dev_zone_info(device);

	device->fs_info = शून्य;
	atomic_set(&device->dev_stats_ccnt, 0);
	extent_io_tree_release(&device->alloc_state);

	/* Verअगरy the device is back in a pristine state  */
	ASSERT(!test_bit(BTRFS_DEV_STATE_FLUSH_SENT, &device->dev_state));
	ASSERT(!test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state));
	ASSERT(list_empty(&device->dev_alloc_list));
	ASSERT(list_empty(&device->post_commit_list));
	ASSERT(atomic_पढ़ो(&device->पढ़ोa_in_flight) == 0);
पूर्ण

अटल व्योम बंद_fs_devices(काष्ठा btrfs_fs_devices *fs_devices)
अणु
	काष्ठा btrfs_device *device, *पंचांगp;

	lockdep_निश्चित_held(&uuid_mutex);

	अगर (--fs_devices->खोलोed > 0)
		वापस;

	list_क्रम_each_entry_safe(device, पंचांगp, &fs_devices->devices, dev_list)
		btrfs_बंद_one_device(device);

	WARN_ON(fs_devices->खोलो_devices);
	WARN_ON(fs_devices->rw_devices);
	fs_devices->खोलोed = 0;
	fs_devices->seeding = false;
	fs_devices->fs_info = शून्य;
पूर्ण

व्योम btrfs_बंद_devices(काष्ठा btrfs_fs_devices *fs_devices)
अणु
	LIST_HEAD(list);
	काष्ठा btrfs_fs_devices *पंचांगp;

	mutex_lock(&uuid_mutex);
	बंद_fs_devices(fs_devices);
	अगर (!fs_devices->खोलोed)
		list_splice_init(&fs_devices->seed_list, &list);

	list_क्रम_each_entry_safe(fs_devices, पंचांगp, &list, seed_list) अणु
		बंद_fs_devices(fs_devices);
		list_del(&fs_devices->seed_list);
		मुक्त_fs_devices(fs_devices);
	पूर्ण
	mutex_unlock(&uuid_mutex);
पूर्ण

अटल पूर्णांक खोलो_fs_devices(काष्ठा btrfs_fs_devices *fs_devices,
				भ_शेषe_t flags, व्योम *holder)
अणु
	काष्ठा btrfs_device *device;
	काष्ठा btrfs_device *latest_dev = शून्य;
	काष्ठा btrfs_device *पंचांगp_device;

	flags |= FMODE_EXCL;

	list_क्रम_each_entry_safe(device, पंचांगp_device, &fs_devices->devices,
				 dev_list) अणु
		पूर्णांक ret;

		ret = btrfs_खोलो_one_device(fs_devices, device, flags, holder);
		अगर (ret == 0 &&
		    (!latest_dev || device->generation > latest_dev->generation)) अणु
			latest_dev = device;
		पूर्ण अन्यथा अगर (ret == -ENODATA) अणु
			fs_devices->num_devices--;
			list_del(&device->dev_list);
			btrfs_मुक्त_device(device);
		पूर्ण
	पूर्ण
	अगर (fs_devices->खोलो_devices == 0)
		वापस -EINVAL;

	fs_devices->खोलोed = 1;
	fs_devices->latest_bdev = latest_dev->bdev;
	fs_devices->total_rw_bytes = 0;
	fs_devices->chunk_alloc_policy = BTRFS_CHUNK_ALLOC_REGULAR;
	fs_devices->पढ़ो_policy = BTRFS_READ_POLICY_PID;

	वापस 0;
पूर्ण

अटल पूर्णांक devid_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
		     स्थिर काष्ठा list_head *b)
अणु
	काष्ठा btrfs_device *dev1, *dev2;

	dev1 = list_entry(a, काष्ठा btrfs_device, dev_list);
	dev2 = list_entry(b, काष्ठा btrfs_device, dev_list);

	अगर (dev1->devid < dev2->devid)
		वापस -1;
	अन्यथा अगर (dev1->devid > dev2->devid)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक btrfs_खोलो_devices(काष्ठा btrfs_fs_devices *fs_devices,
		       भ_शेषe_t flags, व्योम *holder)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&uuid_mutex);
	/*
	 * The device_list_mutex cannot be taken here in हाल खोलोing the
	 * underlying device takes further locks like bd_mutex.
	 *
	 * We also करोn't need the lock here as this is called during mount and
	 * exclusion is provided by uuid_mutex
	 */

	अगर (fs_devices->खोलोed) अणु
		fs_devices->खोलोed++;
		ret = 0;
	पूर्ण अन्यथा अणु
		list_sort(शून्य, &fs_devices->devices, devid_cmp);
		ret = खोलो_fs_devices(fs_devices, flags, holder);
	पूर्ण

	वापस ret;
पूर्ण

व्योम btrfs_release_disk_super(काष्ठा btrfs_super_block *super)
अणु
	काष्ठा page *page = virt_to_page(super);

	put_page(page);
पूर्ण

अटल काष्ठा btrfs_super_block *btrfs_पढ़ो_disk_super(काष्ठा block_device *bdev,
						       u64 bytenr, u64 bytenr_orig)
अणु
	काष्ठा btrfs_super_block *disk_super;
	काष्ठा page *page;
	व्योम *p;
	pgoff_t index;

	/* make sure our super fits in the device */
	अगर (bytenr + PAGE_SIZE >= i_size_पढ़ो(bdev->bd_inode))
		वापस ERR_PTR(-EINVAL);

	/* make sure our super fits in the page */
	अगर (माप(*disk_super) > PAGE_SIZE)
		वापस ERR_PTR(-EINVAL);

	/* make sure our super करोesn't straddle pages on disk */
	index = bytenr >> PAGE_SHIFT;
	अगर ((bytenr + माप(*disk_super) - 1) >> PAGE_SHIFT != index)
		वापस ERR_PTR(-EINVAL);

	/* pull in the page with our super */
	page = पढ़ो_cache_page_gfp(bdev->bd_inode->i_mapping, index, GFP_KERNEL);

	अगर (IS_ERR(page))
		वापस ERR_CAST(page);

	p = page_address(page);

	/* align our poपूर्णांकer to the offset of the super block */
	disk_super = p + offset_in_page(bytenr);

	अगर (btrfs_super_bytenr(disk_super) != bytenr_orig ||
	    btrfs_super_magic(disk_super) != BTRFS_MAGIC) अणु
		btrfs_release_disk_super(p);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (disk_super->label[0] && disk_super->label[BTRFS_LABEL_SIZE - 1])
		disk_super->label[BTRFS_LABEL_SIZE - 1] = 0;

	वापस disk_super;
पूर्ण

पूर्णांक btrfs_क्रमget_devices(स्थिर अक्षर *path)
अणु
	पूर्णांक ret;

	mutex_lock(&uuid_mutex);
	ret = btrfs_मुक्त_stale_devices(म_माप(path) ? path : शून्य, शून्य);
	mutex_unlock(&uuid_mutex);

	वापस ret;
पूर्ण

/*
 * Look क्रम a btrfs signature on a device. This may be called out of the mount path
 * and we are not allowed to call set_blocksize during the scan. The superblock
 * is पढ़ो via pagecache
 */
काष्ठा btrfs_device *btrfs_scan_one_device(स्थिर अक्षर *path, भ_शेषe_t flags,
					   व्योम *holder)
अणु
	काष्ठा btrfs_super_block *disk_super;
	bool new_device_added = false;
	काष्ठा btrfs_device *device = शून्य;
	काष्ठा block_device *bdev;
	u64 bytenr, bytenr_orig;
	पूर्णांक ret;

	lockdep_निश्चित_held(&uuid_mutex);

	/*
	 * we would like to check all the supers, but that would make
	 * a btrfs mount succeed after a mkfs from a dअगरferent FS.
	 * So, we need to add a special mount option to scan क्रम
	 * later supers, using BTRFS_SUPER_MIRROR_MAX instead
	 */
	flags |= FMODE_EXCL;

	bdev = blkdev_get_by_path(path, flags, holder);
	अगर (IS_ERR(bdev))
		वापस ERR_CAST(bdev);

	bytenr_orig = btrfs_sb_offset(0);
	ret = btrfs_sb_log_location_bdev(bdev, 0, READ, &bytenr);
	अगर (ret)
		वापस ERR_PTR(ret);

	disk_super = btrfs_पढ़ो_disk_super(bdev, bytenr, bytenr_orig);
	अगर (IS_ERR(disk_super)) अणु
		device = ERR_CAST(disk_super);
		जाओ error_bdev_put;
	पूर्ण

	device = device_list_add(path, disk_super, &new_device_added);
	अगर (!IS_ERR(device)) अणु
		अगर (new_device_added)
			btrfs_मुक्त_stale_devices(path, device);
	पूर्ण

	btrfs_release_disk_super(disk_super);

error_bdev_put:
	blkdev_put(bdev, flags);

	वापस device;
पूर्ण

/*
 * Try to find a chunk that पूर्णांकersects [start, start + len] range and when one
 * such is found, record the end of it in *start
 */
अटल bool contains_pending_extent(काष्ठा btrfs_device *device, u64 *start,
				    u64 len)
अणु
	u64 physical_start, physical_end;

	lockdep_निश्चित_held(&device->fs_info->chunk_mutex);

	अगर (!find_first_extent_bit(&device->alloc_state, *start,
				   &physical_start, &physical_end,
				   CHUNK_ALLOCATED, शून्य)) अणु

		अगर (in_range(physical_start, *start, len) ||
		    in_range(*start, physical_start,
			     physical_end - physical_start)) अणु
			*start = physical_end + 1;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल u64 dev_extent_search_start(काष्ठा btrfs_device *device, u64 start)
अणु
	चयन (device->fs_devices->chunk_alloc_policy) अणु
	हाल BTRFS_CHUNK_ALLOC_REGULAR:
		/*
		 * We करोn't want to overग_लिखो the superblock on the drive nor
		 * any area used by the boot loader (grub क्रम example), so we
		 * make sure to start at an offset of at least 1MB.
		 */
		वापस max_t(u64, start, SZ_1M);
	हाल BTRFS_CHUNK_ALLOC_ZONED:
		/*
		 * We करोn't care about the starting region like regular
		 * allocator, because we anyway use/reserve the first two zones
		 * क्रम superblock logging.
		 */
		वापस ALIGN(start, device->zone_info->zone_size);
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल bool dev_extent_hole_check_zoned(काष्ठा btrfs_device *device,
					u64 *hole_start, u64 *hole_size,
					u64 num_bytes)
अणु
	u64 zone_size = device->zone_info->zone_size;
	u64 pos;
	पूर्णांक ret;
	bool changed = false;

	ASSERT(IS_ALIGNED(*hole_start, zone_size));

	जबतक (*hole_size > 0) अणु
		pos = btrfs_find_allocatable_zones(device, *hole_start,
						   *hole_start + *hole_size,
						   num_bytes);
		अगर (pos != *hole_start) अणु
			*hole_size = *hole_start + *hole_size - pos;
			*hole_start = pos;
			changed = true;
			अगर (*hole_size < num_bytes)
				अवरोध;
		पूर्ण

		ret = btrfs_ensure_empty_zones(device, pos, num_bytes);

		/* Range is ensured to be empty */
		अगर (!ret)
			वापस changed;

		/* Given hole range was invalid (outside of device) */
		अगर (ret == -दुस्फल) अणु
			*hole_start += *hole_size;
			*hole_size = 0;
			वापस true;
		पूर्ण

		*hole_start += zone_size;
		*hole_size -= zone_size;
		changed = true;
	पूर्ण

	वापस changed;
पूर्ण

/**
 * dev_extent_hole_check - check अगर specअगरied hole is suitable क्रम allocation
 * @device:	the device which we have the hole
 * @hole_start: starting position of the hole
 * @hole_size:	the size of the hole
 * @num_bytes:	the size of the मुक्त space that we need
 *
 * This function may modअगरy @hole_start and @hole_size to reflect the suitable
 * position क्रम allocation. Returns 1 अगर hole position is updated, 0 otherwise.
 */
अटल bool dev_extent_hole_check(काष्ठा btrfs_device *device, u64 *hole_start,
				  u64 *hole_size, u64 num_bytes)
अणु
	bool changed = false;
	u64 hole_end = *hole_start + *hole_size;

	क्रम (;;) अणु
		/*
		 * Check beक्रमe we set max_hole_start, otherwise we could end up
		 * sending back this offset anyway.
		 */
		अगर (contains_pending_extent(device, hole_start, *hole_size)) अणु
			अगर (hole_end >= *hole_start)
				*hole_size = hole_end - *hole_start;
			अन्यथा
				*hole_size = 0;
			changed = true;
		पूर्ण

		चयन (device->fs_devices->chunk_alloc_policy) अणु
		हाल BTRFS_CHUNK_ALLOC_REGULAR:
			/* No extra check */
			अवरोध;
		हाल BTRFS_CHUNK_ALLOC_ZONED:
			अगर (dev_extent_hole_check_zoned(device, hole_start,
							hole_size, num_bytes)) अणु
				changed = true;
				/*
				 * The changed hole can contain pending extent.
				 * Loop again to check that.
				 */
				जारी;
			पूर्ण
			अवरोध;
		शेष:
			BUG();
		पूर्ण

		अवरोध;
	पूर्ण

	वापस changed;
पूर्ण

/*
 * find_मुक्त_dev_extent_start - find मुक्त space in the specअगरied device
 * @device:	  the device which we search the मुक्त space in
 * @num_bytes:	  the size of the मुक्त space that we need
 * @search_start: the position from which to begin the search
 * @start:	  store the start of the मुक्त space.
 * @len:	  the size of the मुक्त space. that we find, or the size
 *		  of the max मुक्त space अगर we करोn't find suitable मुक्त space
 *
 * this uses a pretty simple search, the expectation is that it is
 * called very infrequently and that a given device has a small number
 * of extents
 *
 * @start is used to store the start of the मुक्त space अगर we find. But अगर we
 * करोn't find suitable मुक्त space, it will be used to store the start position
 * of the max मुक्त space.
 *
 * @len is used to store the size of the मुक्त space that we find.
 * But अगर we करोn't find suitable मुक्त space, it is used to store the size of
 * the max मुक्त space.
 *
 * NOTE: This function will search *commit* root of device tree, and करोes extra
 * check to ensure dev extents are not द्विगुन allocated.
 * This makes the function safe to allocate dev extents but may not report
 * correct usable device space, as device extent मुक्तd in current transaction
 * is not reported as avaiable.
 */
अटल पूर्णांक find_मुक्त_dev_extent_start(काष्ठा btrfs_device *device,
				u64 num_bytes, u64 search_start, u64 *start,
				u64 *len)
अणु
	काष्ठा btrfs_fs_info *fs_info = device->fs_info;
	काष्ठा btrfs_root *root = fs_info->dev_root;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_dev_extent *dev_extent;
	काष्ठा btrfs_path *path;
	u64 hole_size;
	u64 max_hole_start;
	u64 max_hole_size;
	u64 extent_end;
	u64 search_end = device->total_bytes;
	पूर्णांक ret;
	पूर्णांक slot;
	काष्ठा extent_buffer *l;

	search_start = dev_extent_search_start(device, search_start);

	WARN_ON(device->zone_info &&
		!IS_ALIGNED(num_bytes, device->zone_info->zone_size));

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	max_hole_start = search_start;
	max_hole_size = 0;

again:
	अगर (search_start >= search_end ||
		test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state)) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	path->पढ़ोa = READA_FORWARD;
	path->search_commit_root = 1;
	path->skip_locking = 1;

	key.objectid = device->devid;
	key.offset = search_start;
	key.type = BTRFS_DEV_EXTENT_KEY;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret > 0) अणु
		ret = btrfs_previous_item(root, path, key.objectid, key.type);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	जबतक (1) अणु
		l = path->nodes[0];
		slot = path->slots[0];
		अगर (slot >= btrfs_header_nritems(l)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret == 0)
				जारी;
			अगर (ret < 0)
				जाओ out;

			अवरोध;
		पूर्ण
		btrfs_item_key_to_cpu(l, &key, slot);

		अगर (key.objectid < device->devid)
			जाओ next;

		अगर (key.objectid > device->devid)
			अवरोध;

		अगर (key.type != BTRFS_DEV_EXTENT_KEY)
			जाओ next;

		अगर (key.offset > search_start) अणु
			hole_size = key.offset - search_start;
			dev_extent_hole_check(device, &search_start, &hole_size,
					      num_bytes);

			अगर (hole_size > max_hole_size) अणु
				max_hole_start = search_start;
				max_hole_size = hole_size;
			पूर्ण

			/*
			 * If this मुक्त space is greater than which we need,
			 * it must be the max मुक्त space that we have found
			 * until now, so max_hole_start must poपूर्णांक to the start
			 * of this मुक्त space and the length of this मुक्त space
			 * is stored in max_hole_size. Thus, we वापस
			 * max_hole_start and max_hole_size and go back to the
			 * caller.
			 */
			अगर (hole_size >= num_bytes) अणु
				ret = 0;
				जाओ out;
			पूर्ण
		पूर्ण

		dev_extent = btrfs_item_ptr(l, slot, काष्ठा btrfs_dev_extent);
		extent_end = key.offset + btrfs_dev_extent_length(l,
								  dev_extent);
		अगर (extent_end > search_start)
			search_start = extent_end;
next:
		path->slots[0]++;
		cond_resched();
	पूर्ण

	/*
	 * At this poपूर्णांक, search_start should be the end of
	 * allocated dev extents, and when shrinking the device,
	 * search_end may be smaller than search_start.
	 */
	अगर (search_end > search_start) अणु
		hole_size = search_end - search_start;
		अगर (dev_extent_hole_check(device, &search_start, &hole_size,
					  num_bytes)) अणु
			btrfs_release_path(path);
			जाओ again;
		पूर्ण

		अगर (hole_size > max_hole_size) अणु
			max_hole_start = search_start;
			max_hole_size = hole_size;
		पूर्ण
	पूर्ण

	/* See above. */
	अगर (max_hole_size < num_bytes)
		ret = -ENOSPC;
	अन्यथा
		ret = 0;

out:
	btrfs_मुक्त_path(path);
	*start = max_hole_start;
	अगर (len)
		*len = max_hole_size;
	वापस ret;
पूर्ण

पूर्णांक find_मुक्त_dev_extent(काष्ठा btrfs_device *device, u64 num_bytes,
			 u64 *start, u64 *len)
अणु
	/* FIXME use last मुक्त of some kind */
	वापस find_मुक्त_dev_extent_start(device, num_bytes, 0, start, len);
पूर्ण

अटल पूर्णांक btrfs_मुक्त_dev_extent(काष्ठा btrfs_trans_handle *trans,
			  काष्ठा btrfs_device *device,
			  u64 start, u64 *dev_extent_len)
अणु
	काष्ठा btrfs_fs_info *fs_info = device->fs_info;
	काष्ठा btrfs_root *root = fs_info->dev_root;
	पूर्णांक ret;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा extent_buffer *leaf = शून्य;
	काष्ठा btrfs_dev_extent *extent = शून्य;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = device->devid;
	key.offset = start;
	key.type = BTRFS_DEV_EXTENT_KEY;
again:
	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret > 0) अणु
		ret = btrfs_previous_item(root, path, key.objectid,
					  BTRFS_DEV_EXTENT_KEY);
		अगर (ret)
			जाओ out;
		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);
		extent = btrfs_item_ptr(leaf, path->slots[0],
					काष्ठा btrfs_dev_extent);
		BUG_ON(found_key.offset > start || found_key.offset +
		       btrfs_dev_extent_length(leaf, extent) < start);
		key = found_key;
		btrfs_release_path(path);
		जाओ again;
	पूर्ण अन्यथा अगर (ret == 0) अणु
		leaf = path->nodes[0];
		extent = btrfs_item_ptr(leaf, path->slots[0],
					काष्ठा btrfs_dev_extent);
	पूर्ण अन्यथा अणु
		btrfs_handle_fs_error(fs_info, ret, "Slot search failed");
		जाओ out;
	पूर्ण

	*dev_extent_len = btrfs_dev_extent_length(leaf, extent);

	ret = btrfs_del_item(trans, root, path);
	अगर (ret) अणु
		btrfs_handle_fs_error(fs_info, ret,
				      "Failed to remove dev extent item");
	पूर्ण अन्यथा अणु
		set_bit(BTRFS_TRANS_HAVE_FREE_BGS, &trans->transaction->flags);
	पूर्ण
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_alloc_dev_extent(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_device *device,
				  u64 chunk_offset, u64 start, u64 num_bytes)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_fs_info *fs_info = device->fs_info;
	काष्ठा btrfs_root *root = fs_info->dev_root;
	काष्ठा btrfs_dev_extent *extent;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;

	WARN_ON(!test_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &device->dev_state));
	WARN_ON(test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state));
	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = device->devid;
	key.offset = start;
	key.type = BTRFS_DEV_EXTENT_KEY;
	ret = btrfs_insert_empty_item(trans, root, path, &key,
				      माप(*extent));
	अगर (ret)
		जाओ out;

	leaf = path->nodes[0];
	extent = btrfs_item_ptr(leaf, path->slots[0],
				काष्ठा btrfs_dev_extent);
	btrfs_set_dev_extent_chunk_tree(leaf, extent,
					BTRFS_CHUNK_TREE_OBJECTID);
	btrfs_set_dev_extent_chunk_objectid(leaf, extent,
					    BTRFS_FIRST_CHUNK_TREE_OBJECTID);
	btrfs_set_dev_extent_chunk_offset(leaf, extent, chunk_offset);

	btrfs_set_dev_extent_length(leaf, extent, num_bytes);
	btrfs_mark_buffer_dirty(leaf);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल u64 find_next_chunk(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा extent_map_tree *em_tree;
	काष्ठा extent_map *em;
	काष्ठा rb_node *n;
	u64 ret = 0;

	em_tree = &fs_info->mapping_tree;
	पढ़ो_lock(&em_tree->lock);
	n = rb_last(&em_tree->map.rb_root);
	अगर (n) अणु
		em = rb_entry(n, काष्ठा extent_map, rb_node);
		ret = em->start + em->len;
	पूर्ण
	पढ़ो_unlock(&em_tree->lock);

	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक find_next_devid(काष्ठा btrfs_fs_info *fs_info,
				    u64 *devid_ret)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_path *path;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = BTRFS_DEV_ITEMS_OBJECTID;
	key.type = BTRFS_DEV_ITEM_KEY;
	key.offset = (u64)-1;

	ret = btrfs_search_slot(शून्य, fs_info->chunk_root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ error;

	अगर (ret == 0) अणु
		/* Corruption */
		btrfs_err(fs_info, "corrupted chunk tree devid -1 matched");
		ret = -EUCLEAN;
		जाओ error;
	पूर्ण

	ret = btrfs_previous_item(fs_info->chunk_root, path,
				  BTRFS_DEV_ITEMS_OBJECTID,
				  BTRFS_DEV_ITEM_KEY);
	अगर (ret) अणु
		*devid_ret = 1;
	पूर्ण अन्यथा अणु
		btrfs_item_key_to_cpu(path->nodes[0], &found_key,
				      path->slots[0]);
		*devid_ret = found_key.offset + 1;
	पूर्ण
	ret = 0;
error:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * the device inक्रमmation is stored in the chunk root
 * the btrfs_device काष्ठा should be fully filled in
 */
अटल पूर्णांक btrfs_add_dev_item(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_device *device)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_dev_item *dev_item;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	अचिन्हित दीर्घ ptr;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = BTRFS_DEV_ITEMS_OBJECTID;
	key.type = BTRFS_DEV_ITEM_KEY;
	key.offset = device->devid;

	ret = btrfs_insert_empty_item(trans, trans->fs_info->chunk_root, path,
				      &key, माप(*dev_item));
	अगर (ret)
		जाओ out;

	leaf = path->nodes[0];
	dev_item = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_dev_item);

	btrfs_set_device_id(leaf, dev_item, device->devid);
	btrfs_set_device_generation(leaf, dev_item, 0);
	btrfs_set_device_type(leaf, dev_item, device->type);
	btrfs_set_device_io_align(leaf, dev_item, device->io_align);
	btrfs_set_device_io_width(leaf, dev_item, device->io_width);
	btrfs_set_device_sector_size(leaf, dev_item, device->sector_size);
	btrfs_set_device_total_bytes(leaf, dev_item,
				     btrfs_device_get_disk_total_bytes(device));
	btrfs_set_device_bytes_used(leaf, dev_item,
				    btrfs_device_get_bytes_used(device));
	btrfs_set_device_group(leaf, dev_item, 0);
	btrfs_set_device_seek_speed(leaf, dev_item, 0);
	btrfs_set_device_bandwidth(leaf, dev_item, 0);
	btrfs_set_device_start_offset(leaf, dev_item, 0);

	ptr = btrfs_device_uuid(dev_item);
	ग_लिखो_extent_buffer(leaf, device->uuid, ptr, BTRFS_UUID_SIZE);
	ptr = btrfs_device_fsid(dev_item);
	ग_लिखो_extent_buffer(leaf, trans->fs_info->fs_devices->metadata_uuid,
			    ptr, BTRFS_FSID_SIZE);
	btrfs_mark_buffer_dirty(leaf);

	ret = 0;
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * Function to update स_समय/mसमय क्रम a given device path.
 * Mainly used क्रम स_समय/mसमय based probe like libblkid.
 */
अटल व्योम update_dev_समय(स्थिर अक्षर *path_name)
अणु
	काष्ठा file *filp;

	filp = filp_खोलो(path_name, O_RDWR, 0);
	अगर (IS_ERR(filp))
		वापस;
	file_update_समय(filp);
	filp_बंद(filp, शून्य);
पूर्ण

अटल पूर्णांक btrfs_rm_dev_item(काष्ठा btrfs_device *device)
अणु
	काष्ठा btrfs_root *root = device->fs_info->chunk_root;
	पूर्णांक ret;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_trans_handle *trans;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	trans = btrfs_start_transaction(root, 0);
	अगर (IS_ERR(trans)) अणु
		btrfs_मुक्त_path(path);
		वापस PTR_ERR(trans);
	पूर्ण
	key.objectid = BTRFS_DEV_ITEMS_OBJECTID;
	key.type = BTRFS_DEV_ITEM_KEY;
	key.offset = device->devid;

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret) अणु
		अगर (ret > 0)
			ret = -ENOENT;
		btrfs_पात_transaction(trans, ret);
		btrfs_end_transaction(trans);
		जाओ out;
	पूर्ण

	ret = btrfs_del_item(trans, root, path);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		btrfs_end_transaction(trans);
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	अगर (!ret)
		ret = btrfs_commit_transaction(trans);
	वापस ret;
पूर्ण

/*
 * Verअगरy that @num_devices satisfies the RAID profile स्थिरraपूर्णांकs in the whole
 * fileप्रणाली. It's up to the caller to adjust that number regarding eg. device
 * replace.
 */
अटल पूर्णांक btrfs_check_raid_min_devices(काष्ठा btrfs_fs_info *fs_info,
		u64 num_devices)
अणु
	u64 all_avail;
	अचिन्हित seq;
	पूर्णांक i;

	करो अणु
		seq = पढ़ो_seqbegin(&fs_info->profiles_lock);

		all_avail = fs_info->avail_data_alloc_bits |
			    fs_info->avail_प्रणाली_alloc_bits |
			    fs_info->avail_metadata_alloc_bits;
	पूर्ण जबतक (पढ़ो_seqretry(&fs_info->profiles_lock, seq));

	क्रम (i = 0; i < BTRFS_NR_RAID_TYPES; i++) अणु
		अगर (!(all_avail & btrfs_raid_array[i].bg_flag))
			जारी;

		अगर (num_devices < btrfs_raid_array[i].devs_min) अणु
			पूर्णांक ret = btrfs_raid_array[i].mindev_error;

			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा btrfs_device * btrfs_find_next_active_device(
		काष्ठा btrfs_fs_devices *fs_devs, काष्ठा btrfs_device *device)
अणु
	काष्ठा btrfs_device *next_device;

	list_क्रम_each_entry(next_device, &fs_devs->devices, dev_list) अणु
		अगर (next_device != device &&
		    !test_bit(BTRFS_DEV_STATE_MISSING, &next_device->dev_state)
		    && next_device->bdev)
			वापस next_device;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Helper function to check अगर the given device is part of s_bdev / latest_bdev
 * and replace it with the provided or the next active device, in the context
 * where this function called, there should be always be another device (or
 * this_dev) which is active.
 */
व्योम __cold btrfs_assign_next_active_device(काष्ठा btrfs_device *device,
					    काष्ठा btrfs_device *next_device)
अणु
	काष्ठा btrfs_fs_info *fs_info = device->fs_info;

	अगर (!next_device)
		next_device = btrfs_find_next_active_device(fs_info->fs_devices,
							    device);
	ASSERT(next_device);

	अगर (fs_info->sb->s_bdev &&
			(fs_info->sb->s_bdev == device->bdev))
		fs_info->sb->s_bdev = next_device->bdev;

	अगर (fs_info->fs_devices->latest_bdev == device->bdev)
		fs_info->fs_devices->latest_bdev = next_device->bdev;
पूर्ण

/*
 * Return btrfs_fs_devices::num_devices excluding the device that's being
 * currently replaced.
 */
अटल u64 btrfs_num_devices(काष्ठा btrfs_fs_info *fs_info)
अणु
	u64 num_devices = fs_info->fs_devices->num_devices;

	करोwn_पढ़ो(&fs_info->dev_replace.rwsem);
	अगर (btrfs_dev_replace_is_ongoing(&fs_info->dev_replace)) अणु
		ASSERT(num_devices > 1);
		num_devices--;
	पूर्ण
	up_पढ़ो(&fs_info->dev_replace.rwsem);

	वापस num_devices;
पूर्ण

व्योम btrfs_scratch_superblocks(काष्ठा btrfs_fs_info *fs_info,
			       काष्ठा block_device *bdev,
			       स्थिर अक्षर *device_path)
अणु
	काष्ठा btrfs_super_block *disk_super;
	पूर्णांक copy_num;

	अगर (!bdev)
		वापस;

	क्रम (copy_num = 0; copy_num < BTRFS_SUPER_MIRROR_MAX; copy_num++) अणु
		काष्ठा page *page;
		पूर्णांक ret;

		disk_super = btrfs_पढ़ो_dev_one_super(bdev, copy_num);
		अगर (IS_ERR(disk_super))
			जारी;

		अगर (bdev_is_zoned(bdev)) अणु
			btrfs_reset_sb_log_zones(bdev, copy_num);
			जारी;
		पूर्ण

		स_रखो(&disk_super->magic, 0, माप(disk_super->magic));

		page = virt_to_page(disk_super);
		set_page_dirty(page);
		lock_page(page);
		/* ग_लिखो_on_page() unlocks the page */
		ret = ग_लिखो_one_page(page);
		अगर (ret)
			btrfs_warn(fs_info,
				"error clearing superblock number %d (%d)",
				copy_num, ret);
		btrfs_release_disk_super(disk_super);

	पूर्ण

	/* Notअगरy udev that device has changed */
	btrfs_kobject_uevent(bdev, KOBJ_CHANGE);

	/* Update स_समय/mसमय क्रम device path क्रम libblkid */
	update_dev_समय(device_path);
पूर्ण

पूर्णांक btrfs_rm_device(काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *device_path,
		    u64 devid)
अणु
	काष्ठा btrfs_device *device;
	काष्ठा btrfs_fs_devices *cur_devices;
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	u64 num_devices;
	पूर्णांक ret = 0;

	mutex_lock(&uuid_mutex);

	num_devices = btrfs_num_devices(fs_info);

	ret = btrfs_check_raid_min_devices(fs_info, num_devices - 1);
	अगर (ret)
		जाओ out;

	device = btrfs_find_device_by_devspec(fs_info, devid, device_path);

	अगर (IS_ERR(device)) अणु
		अगर (PTR_ERR(device) == -ENOENT &&
		    म_भेद(device_path, "missing") == 0)
			ret = BTRFS_ERROR_DEV_MISSING_NOT_FOUND;
		अन्यथा
			ret = PTR_ERR(device);
		जाओ out;
	पूर्ण

	अगर (btrfs_pinned_by_swapfile(fs_info, device)) अणु
		btrfs_warn_in_rcu(fs_info,
		  "cannot remove device %s (devid %llu) due to active swapfile",
				  rcu_str_deref(device->name), device->devid);
		ret = -ETXTBSY;
		जाओ out;
	पूर्ण

	अगर (test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state)) अणु
		ret = BTRFS_ERROR_DEV_TGT_REPLACE;
		जाओ out;
	पूर्ण

	अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state) &&
	    fs_info->fs_devices->rw_devices == 1) अणु
		ret = BTRFS_ERROR_DEV_ONLY_WRITABLE;
		जाओ out;
	पूर्ण

	अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state)) अणु
		mutex_lock(&fs_info->chunk_mutex);
		list_del_init(&device->dev_alloc_list);
		device->fs_devices->rw_devices--;
		mutex_unlock(&fs_info->chunk_mutex);
	पूर्ण

	mutex_unlock(&uuid_mutex);
	ret = btrfs_shrink_device(device, 0);
	अगर (!ret)
		btrfs_पढ़ोa_हटाओ_dev(device);
	mutex_lock(&uuid_mutex);
	अगर (ret)
		जाओ error_unकरो;

	/*
	 * TODO: the superblock still includes this device in its num_devices
	 * counter although ग_लिखो_all_supers() is not locked out. This
	 * could give a fileप्रणाली state which requires a degraded mount.
	 */
	ret = btrfs_rm_dev_item(device);
	अगर (ret)
		जाओ error_unकरो;

	clear_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &device->dev_state);
	btrfs_scrub_cancel_dev(device);

	/*
	 * the device list mutex makes sure that we करोn't change
	 * the device list जबतक someone अन्यथा is writing out all
	 * the device supers. Whoever is writing all supers, should
	 * lock the device list mutex beक्रमe getting the number of
	 * devices in the super block (super_copy). Conversely,
	 * whoever updates the number of devices in the super block
	 * (super_copy) should hold the device list mutex.
	 */

	/*
	 * In normal हालs the cur_devices == fs_devices. But in हाल
	 * of deleting a seed device, the cur_devices should poपूर्णांक to
	 * its own fs_devices listed under the fs_devices->seed.
	 */
	cur_devices = device->fs_devices;
	mutex_lock(&fs_devices->device_list_mutex);
	list_del_rcu(&device->dev_list);

	cur_devices->num_devices--;
	cur_devices->total_devices--;
	/* Update total_devices of the parent fs_devices अगर it's seed */
	अगर (cur_devices != fs_devices)
		fs_devices->total_devices--;

	अगर (test_bit(BTRFS_DEV_STATE_MISSING, &device->dev_state))
		cur_devices->missing_devices--;

	btrfs_assign_next_active_device(device, शून्य);

	अगर (device->bdev) अणु
		cur_devices->खोलो_devices--;
		/* हटाओ sysfs entry */
		btrfs_sysfs_हटाओ_device(device);
	पूर्ण

	num_devices = btrfs_super_num_devices(fs_info->super_copy) - 1;
	btrfs_set_super_num_devices(fs_info->super_copy, num_devices);
	mutex_unlock(&fs_devices->device_list_mutex);

	/*
	 * at this poपूर्णांक, the device is zero sized and detached from
	 * the devices list.  All that's left is to zero out the old
	 * supers and मुक्त the device.
	 */
	अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state))
		btrfs_scratch_superblocks(fs_info, device->bdev,
					  device->name->str);

	btrfs_बंद_bdev(device);
	synchronize_rcu();
	btrfs_मुक्त_device(device);

	अगर (cur_devices->खोलो_devices == 0) अणु
		list_del_init(&cur_devices->seed_list);
		बंद_fs_devices(cur_devices);
		मुक्त_fs_devices(cur_devices);
	पूर्ण

out:
	mutex_unlock(&uuid_mutex);
	वापस ret;

error_unकरो:
	btrfs_पढ़ोa_unकरो_हटाओ_dev(device);
	अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state)) अणु
		mutex_lock(&fs_info->chunk_mutex);
		list_add(&device->dev_alloc_list,
			 &fs_devices->alloc_list);
		device->fs_devices->rw_devices++;
		mutex_unlock(&fs_info->chunk_mutex);
	पूर्ण
	जाओ out;
पूर्ण

व्योम btrfs_rm_dev_replace_हटाओ_srcdev(काष्ठा btrfs_device *srcdev)
अणु
	काष्ठा btrfs_fs_devices *fs_devices;

	lockdep_निश्चित_held(&srcdev->fs_info->fs_devices->device_list_mutex);

	/*
	 * in हाल of fs with no seed, srcdev->fs_devices will poपूर्णांक
	 * to fs_devices of fs_info. However when the dev being replaced is
	 * a seed dev it will poपूर्णांक to the seed's local fs_devices. In लघु
	 * srcdev will have its correct fs_devices in both the हालs.
	 */
	fs_devices = srcdev->fs_devices;

	list_del_rcu(&srcdev->dev_list);
	list_del(&srcdev->dev_alloc_list);
	fs_devices->num_devices--;
	अगर (test_bit(BTRFS_DEV_STATE_MISSING, &srcdev->dev_state))
		fs_devices->missing_devices--;

	अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &srcdev->dev_state))
		fs_devices->rw_devices--;

	अगर (srcdev->bdev)
		fs_devices->खोलो_devices--;
पूर्ण

व्योम btrfs_rm_dev_replace_मुक्त_srcdev(काष्ठा btrfs_device *srcdev)
अणु
	काष्ठा btrfs_fs_devices *fs_devices = srcdev->fs_devices;

	mutex_lock(&uuid_mutex);

	btrfs_बंद_bdev(srcdev);
	synchronize_rcu();
	btrfs_मुक्त_device(srcdev);

	/* अगर this is no devs we rather delete the fs_devices */
	अगर (!fs_devices->num_devices) अणु
		/*
		 * On a mounted FS, num_devices can't be zero unless it's a
		 * seed. In हाल of a seed device being replaced, the replace
		 * target added to the sprout FS, so there will be no more
		 * device left under the seed FS.
		 */
		ASSERT(fs_devices->seeding);

		list_del_init(&fs_devices->seed_list);
		बंद_fs_devices(fs_devices);
		मुक्त_fs_devices(fs_devices);
	पूर्ण
	mutex_unlock(&uuid_mutex);
पूर्ण

व्योम btrfs_destroy_dev_replace_tgtdev(काष्ठा btrfs_device *tgtdev)
अणु
	काष्ठा btrfs_fs_devices *fs_devices = tgtdev->fs_info->fs_devices;

	mutex_lock(&fs_devices->device_list_mutex);

	btrfs_sysfs_हटाओ_device(tgtdev);

	अगर (tgtdev->bdev)
		fs_devices->खोलो_devices--;

	fs_devices->num_devices--;

	btrfs_assign_next_active_device(tgtdev, शून्य);

	list_del_rcu(&tgtdev->dev_list);

	mutex_unlock(&fs_devices->device_list_mutex);

	/*
	 * The update_dev_समय() with in btrfs_scratch_superblocks()
	 * may lead to a call to btrfs_show_devname() which will try
	 * to hold device_list_mutex. And here this device
	 * is alपढ़ोy out of device list, so we करोn't have to hold
	 * the device_list_mutex lock.
	 */
	btrfs_scratch_superblocks(tgtdev->fs_info, tgtdev->bdev,
				  tgtdev->name->str);

	btrfs_बंद_bdev(tgtdev);
	synchronize_rcu();
	btrfs_मुक्त_device(tgtdev);
पूर्ण

अटल काष्ठा btrfs_device *btrfs_find_device_by_path(
		काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *device_path)
अणु
	पूर्णांक ret = 0;
	काष्ठा btrfs_super_block *disk_super;
	u64 devid;
	u8 *dev_uuid;
	काष्ठा block_device *bdev;
	काष्ठा btrfs_device *device;

	ret = btrfs_get_bdev_and_sb(device_path, FMODE_READ,
				    fs_info->bdev_holder, 0, &bdev, &disk_super);
	अगर (ret)
		वापस ERR_PTR(ret);

	devid = btrfs_stack_device_id(&disk_super->dev_item);
	dev_uuid = disk_super->dev_item.uuid;
	अगर (btrfs_fs_incompat(fs_info, METADATA_UUID))
		device = btrfs_find_device(fs_info->fs_devices, devid, dev_uuid,
					   disk_super->metadata_uuid);
	अन्यथा
		device = btrfs_find_device(fs_info->fs_devices, devid, dev_uuid,
					   disk_super->fsid);

	btrfs_release_disk_super(disk_super);
	अगर (!device)
		device = ERR_PTR(-ENOENT);
	blkdev_put(bdev, FMODE_READ);
	वापस device;
पूर्ण

/*
 * Lookup a device given by device id, or the path अगर the id is 0.
 */
काष्ठा btrfs_device *btrfs_find_device_by_devspec(
		काष्ठा btrfs_fs_info *fs_info, u64 devid,
		स्थिर अक्षर *device_path)
अणु
	काष्ठा btrfs_device *device;

	अगर (devid) अणु
		device = btrfs_find_device(fs_info->fs_devices, devid, शून्य,
					   शून्य);
		अगर (!device)
			वापस ERR_PTR(-ENOENT);
		वापस device;
	पूर्ण

	अगर (!device_path || !device_path[0])
		वापस ERR_PTR(-EINVAL);

	अगर (म_भेद(device_path, "missing") == 0) अणु
		/* Find first missing device */
		list_क्रम_each_entry(device, &fs_info->fs_devices->devices,
				    dev_list) अणु
			अगर (test_bit(BTRFS_DEV_STATE_IN_FS_METADATA,
				     &device->dev_state) && !device->bdev)
				वापस device;
		पूर्ण
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	वापस btrfs_find_device_by_path(fs_info, device_path);
पूर्ण

/*
 * करोes all the dirty work required क्रम changing file प्रणाली's UUID.
 */
अटल पूर्णांक btrfs_prepare_sprout(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	काष्ठा btrfs_fs_devices *old_devices;
	काष्ठा btrfs_fs_devices *seed_devices;
	काष्ठा btrfs_super_block *disk_super = fs_info->super_copy;
	काष्ठा btrfs_device *device;
	u64 super_flags;

	lockdep_निश्चित_held(&uuid_mutex);
	अगर (!fs_devices->seeding)
		वापस -EINVAL;

	/*
	 * Private copy of the seed devices, anchored at
	 * fs_info->fs_devices->seed_list
	 */
	seed_devices = alloc_fs_devices(शून्य, शून्य);
	अगर (IS_ERR(seed_devices))
		वापस PTR_ERR(seed_devices);

	/*
	 * It's necessary to retain a copy of the original seed fs_devices in
	 * fs_uuids so that fileप्रणालीs which have been seeded can successfully
	 * reference the seed device from खोलो_seed_devices. This also supports
	 * multiple fs seed.
	 */
	old_devices = clone_fs_devices(fs_devices);
	अगर (IS_ERR(old_devices)) अणु
		kमुक्त(seed_devices);
		वापस PTR_ERR(old_devices);
	पूर्ण

	list_add(&old_devices->fs_list, &fs_uuids);

	स_नकल(seed_devices, fs_devices, माप(*seed_devices));
	seed_devices->खोलोed = 1;
	INIT_LIST_HEAD(&seed_devices->devices);
	INIT_LIST_HEAD(&seed_devices->alloc_list);
	mutex_init(&seed_devices->device_list_mutex);

	mutex_lock(&fs_devices->device_list_mutex);
	list_splice_init_rcu(&fs_devices->devices, &seed_devices->devices,
			      synchronize_rcu);
	list_क्रम_each_entry(device, &seed_devices->devices, dev_list)
		device->fs_devices = seed_devices;

	fs_devices->seeding = false;
	fs_devices->num_devices = 0;
	fs_devices->खोलो_devices = 0;
	fs_devices->missing_devices = 0;
	fs_devices->rotating = false;
	list_add(&seed_devices->seed_list, &fs_devices->seed_list);

	generate_अक्रमom_uuid(fs_devices->fsid);
	स_नकल(fs_devices->metadata_uuid, fs_devices->fsid, BTRFS_FSID_SIZE);
	स_नकल(disk_super->fsid, fs_devices->fsid, BTRFS_FSID_SIZE);
	mutex_unlock(&fs_devices->device_list_mutex);

	super_flags = btrfs_super_flags(disk_super) &
		      ~BTRFS_SUPER_FLAG_SEEDING;
	btrfs_set_super_flags(disk_super, super_flags);

	वापस 0;
पूर्ण

/*
 * Store the expected generation क्रम seed devices in device items.
 */
अटल पूर्णांक btrfs_finish_sprout(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *root = fs_info->chunk_root;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_dev_item *dev_item;
	काष्ठा btrfs_device *device;
	काष्ठा btrfs_key key;
	u8 fs_uuid[BTRFS_FSID_SIZE];
	u8 dev_uuid[BTRFS_UUID_SIZE];
	u64 devid;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = BTRFS_DEV_ITEMS_OBJECTID;
	key.offset = 0;
	key.type = BTRFS_DEV_ITEM_KEY;

	जबतक (1) अणु
		ret = btrfs_search_slot(trans, root, &key, path, 0, 1);
		अगर (ret < 0)
			जाओ error;

		leaf = path->nodes[0];
next_slot:
		अगर (path->slots[0] >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret > 0)
				अवरोध;
			अगर (ret < 0)
				जाओ error;
			leaf = path->nodes[0];
			btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
			btrfs_release_path(path);
			जारी;
		पूर्ण

		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
		अगर (key.objectid != BTRFS_DEV_ITEMS_OBJECTID ||
		    key.type != BTRFS_DEV_ITEM_KEY)
			अवरोध;

		dev_item = btrfs_item_ptr(leaf, path->slots[0],
					  काष्ठा btrfs_dev_item);
		devid = btrfs_device_id(leaf, dev_item);
		पढ़ो_extent_buffer(leaf, dev_uuid, btrfs_device_uuid(dev_item),
				   BTRFS_UUID_SIZE);
		पढ़ो_extent_buffer(leaf, fs_uuid, btrfs_device_fsid(dev_item),
				   BTRFS_FSID_SIZE);
		device = btrfs_find_device(fs_info->fs_devices, devid, dev_uuid,
					   fs_uuid);
		BUG_ON(!device); /* Logic error */

		अगर (device->fs_devices->seeding) अणु
			btrfs_set_device_generation(leaf, dev_item,
						    device->generation);
			btrfs_mark_buffer_dirty(leaf);
		पूर्ण

		path->slots[0]++;
		जाओ next_slot;
	पूर्ण
	ret = 0;
error:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_init_new_device(काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *device_path)
अणु
	काष्ठा btrfs_root *root = fs_info->dev_root;
	काष्ठा request_queue *q;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_device *device;
	काष्ठा block_device *bdev;
	काष्ठा super_block *sb = fs_info->sb;
	काष्ठा rcu_string *name;
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	u64 orig_super_total_bytes;
	u64 orig_super_num_devices;
	पूर्णांक seeding_dev = 0;
	पूर्णांक ret = 0;
	bool locked = false;

	अगर (sb_rकरोnly(sb) && !fs_devices->seeding)
		वापस -EROFS;

	bdev = blkdev_get_by_path(device_path, FMODE_WRITE | FMODE_EXCL,
				  fs_info->bdev_holder);
	अगर (IS_ERR(bdev))
		वापस PTR_ERR(bdev);

	अगर (!btrfs_check_device_zone_type(fs_info, bdev)) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (fs_devices->seeding) अणु
		seeding_dev = 1;
		करोwn_ग_लिखो(&sb->s_umount);
		mutex_lock(&uuid_mutex);
		locked = true;
	पूर्ण

	sync_blockdev(bdev);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(device, &fs_devices->devices, dev_list) अणु
		अगर (device->bdev == bdev) अणु
			ret = -EEXIST;
			rcu_पढ़ो_unlock();
			जाओ error;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	device = btrfs_alloc_device(fs_info, शून्य, शून्य);
	अगर (IS_ERR(device)) अणु
		/* we can safely leave the fs_devices entry around */
		ret = PTR_ERR(device);
		जाओ error;
	पूर्ण

	name = rcu_string_strdup(device_path, GFP_KERNEL);
	अगर (!name) अणु
		ret = -ENOMEM;
		जाओ error_मुक्त_device;
	पूर्ण
	rcu_assign_poपूर्णांकer(device->name, name);

	device->fs_info = fs_info;
	device->bdev = bdev;

	ret = btrfs_get_dev_zone_info(device);
	अगर (ret)
		जाओ error_मुक्त_device;

	trans = btrfs_start_transaction(root, 0);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ error_मुक्त_zone;
	पूर्ण

	q = bdev_get_queue(bdev);
	set_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state);
	device->generation = trans->transid;
	device->io_width = fs_info->sectorsize;
	device->io_align = fs_info->sectorsize;
	device->sector_size = fs_info->sectorsize;
	device->total_bytes = round_करोwn(i_size_पढ़ो(bdev->bd_inode),
					 fs_info->sectorsize);
	device->disk_total_bytes = device->total_bytes;
	device->commit_total_bytes = device->total_bytes;
	set_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &device->dev_state);
	clear_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state);
	device->mode = FMODE_EXCL;
	device->dev_stats_valid = 1;
	set_blocksize(device->bdev, BTRFS_BDEV_BLOCKSIZE);

	अगर (seeding_dev) अणु
		btrfs_clear_sb_rकरोnly(sb);
		ret = btrfs_prepare_sprout(fs_info);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ error_trans;
		पूर्ण
	पूर्ण

	device->fs_devices = fs_devices;

	mutex_lock(&fs_devices->device_list_mutex);
	mutex_lock(&fs_info->chunk_mutex);
	list_add_rcu(&device->dev_list, &fs_devices->devices);
	list_add(&device->dev_alloc_list, &fs_devices->alloc_list);
	fs_devices->num_devices++;
	fs_devices->खोलो_devices++;
	fs_devices->rw_devices++;
	fs_devices->total_devices++;
	fs_devices->total_rw_bytes += device->total_bytes;

	atomic64_add(device->total_bytes, &fs_info->मुक्त_chunk_space);

	अगर (!blk_queue_nonrot(q))
		fs_devices->rotating = true;

	orig_super_total_bytes = btrfs_super_total_bytes(fs_info->super_copy);
	btrfs_set_super_total_bytes(fs_info->super_copy,
		round_करोwn(orig_super_total_bytes + device->total_bytes,
			   fs_info->sectorsize));

	orig_super_num_devices = btrfs_super_num_devices(fs_info->super_copy);
	btrfs_set_super_num_devices(fs_info->super_copy,
				    orig_super_num_devices + 1);

	/*
	 * we've got more storage, clear any full flags on the space
	 * infos
	 */
	btrfs_clear_space_info_full(fs_info);

	mutex_unlock(&fs_info->chunk_mutex);

	/* Add sysfs device entry */
	btrfs_sysfs_add_device(device);

	mutex_unlock(&fs_devices->device_list_mutex);

	अगर (seeding_dev) अणु
		mutex_lock(&fs_info->chunk_mutex);
		ret = init_first_rw_device(trans);
		mutex_unlock(&fs_info->chunk_mutex);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ error_sysfs;
		पूर्ण
	पूर्ण

	ret = btrfs_add_dev_item(trans, device);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ error_sysfs;
	पूर्ण

	अगर (seeding_dev) अणु
		ret = btrfs_finish_sprout(trans);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ error_sysfs;
		पूर्ण

		/*
		 * fs_devices now represents the newly sprouted fileप्रणाली and
		 * its fsid has been changed by btrfs_prepare_sprout
		 */
		btrfs_sysfs_update_sprout_fsid(fs_devices);
	पूर्ण

	ret = btrfs_commit_transaction(trans);

	अगर (seeding_dev) अणु
		mutex_unlock(&uuid_mutex);
		up_ग_लिखो(&sb->s_umount);
		locked = false;

		अगर (ret) /* transaction commit */
			वापस ret;

		ret = btrfs_relocate_sys_chunks(fs_info);
		अगर (ret < 0)
			btrfs_handle_fs_error(fs_info, ret,
				    "Failed to relocate sys chunks after device initialization. This can be fixed using the \"btrfs balance\" command.");
		trans = btrfs_attach_transaction(root);
		अगर (IS_ERR(trans)) अणु
			अगर (PTR_ERR(trans) == -ENOENT)
				वापस 0;
			ret = PTR_ERR(trans);
			trans = शून्य;
			जाओ error_sysfs;
		पूर्ण
		ret = btrfs_commit_transaction(trans);
	पूर्ण

	/*
	 * Now that we have written a new super block to this device, check all
	 * other fs_devices list अगर device_path alienates any other scanned
	 * device.
	 * We can ignore the वापस value as it typically वापसs -EINVAL and
	 * only succeeds अगर the device was an alien.
	 */
	btrfs_क्रमget_devices(device_path);

	/* Update स_समय/mसमय क्रम blkid or udev */
	update_dev_समय(device_path);

	वापस ret;

error_sysfs:
	btrfs_sysfs_हटाओ_device(device);
	mutex_lock(&fs_info->fs_devices->device_list_mutex);
	mutex_lock(&fs_info->chunk_mutex);
	list_del_rcu(&device->dev_list);
	list_del(&device->dev_alloc_list);
	fs_info->fs_devices->num_devices--;
	fs_info->fs_devices->खोलो_devices--;
	fs_info->fs_devices->rw_devices--;
	fs_info->fs_devices->total_devices--;
	fs_info->fs_devices->total_rw_bytes -= device->total_bytes;
	atomic64_sub(device->total_bytes, &fs_info->मुक्त_chunk_space);
	btrfs_set_super_total_bytes(fs_info->super_copy,
				    orig_super_total_bytes);
	btrfs_set_super_num_devices(fs_info->super_copy,
				    orig_super_num_devices);
	mutex_unlock(&fs_info->chunk_mutex);
	mutex_unlock(&fs_info->fs_devices->device_list_mutex);
error_trans:
	अगर (seeding_dev)
		btrfs_set_sb_rकरोnly(sb);
	अगर (trans)
		btrfs_end_transaction(trans);
error_मुक्त_zone:
	btrfs_destroy_dev_zone_info(device);
error_मुक्त_device:
	btrfs_मुक्त_device(device);
error:
	blkdev_put(bdev, FMODE_EXCL);
	अगर (locked) अणु
		mutex_unlock(&uuid_mutex);
		up_ग_लिखो(&sb->s_umount);
	पूर्ण
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक btrfs_update_device(काष्ठा btrfs_trans_handle *trans,
					काष्ठा btrfs_device *device)
अणु
	पूर्णांक ret;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_root *root = device->fs_info->chunk_root;
	काष्ठा btrfs_dev_item *dev_item;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = BTRFS_DEV_ITEMS_OBJECTID;
	key.type = BTRFS_DEV_ITEM_KEY;
	key.offset = device->devid;

	ret = btrfs_search_slot(trans, root, &key, path, 0, 1);
	अगर (ret < 0)
		जाओ out;

	अगर (ret > 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	dev_item = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_dev_item);

	btrfs_set_device_id(leaf, dev_item, device->devid);
	btrfs_set_device_type(leaf, dev_item, device->type);
	btrfs_set_device_io_align(leaf, dev_item, device->io_align);
	btrfs_set_device_io_width(leaf, dev_item, device->io_width);
	btrfs_set_device_sector_size(leaf, dev_item, device->sector_size);
	btrfs_set_device_total_bytes(leaf, dev_item,
				     btrfs_device_get_disk_total_bytes(device));
	btrfs_set_device_bytes_used(leaf, dev_item,
				    btrfs_device_get_bytes_used(device));
	btrfs_mark_buffer_dirty(leaf);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_grow_device(काष्ठा btrfs_trans_handle *trans,
		      काष्ठा btrfs_device *device, u64 new_size)
अणु
	काष्ठा btrfs_fs_info *fs_info = device->fs_info;
	काष्ठा btrfs_super_block *super_copy = fs_info->super_copy;
	u64 old_total;
	u64 dअगरf;

	अगर (!test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state))
		वापस -EACCES;

	new_size = round_करोwn(new_size, fs_info->sectorsize);

	mutex_lock(&fs_info->chunk_mutex);
	old_total = btrfs_super_total_bytes(super_copy);
	dअगरf = round_करोwn(new_size - device->total_bytes, fs_info->sectorsize);

	अगर (new_size <= device->total_bytes ||
	    test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state)) अणु
		mutex_unlock(&fs_info->chunk_mutex);
		वापस -EINVAL;
	पूर्ण

	btrfs_set_super_total_bytes(super_copy,
			round_करोwn(old_total + dअगरf, fs_info->sectorsize));
	device->fs_devices->total_rw_bytes += dअगरf;

	btrfs_device_set_total_bytes(device, new_size);
	btrfs_device_set_disk_total_bytes(device, new_size);
	btrfs_clear_space_info_full(device->fs_info);
	अगर (list_empty(&device->post_commit_list))
		list_add_tail(&device->post_commit_list,
			      &trans->transaction->dev_update_list);
	mutex_unlock(&fs_info->chunk_mutex);

	वापस btrfs_update_device(trans, device);
पूर्ण

अटल पूर्णांक btrfs_मुक्त_chunk(काष्ठा btrfs_trans_handle *trans, u64 chunk_offset)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *root = fs_info->chunk_root;
	पूर्णांक ret;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = BTRFS_FIRST_CHUNK_TREE_OBJECTID;
	key.offset = chunk_offset;
	key.type = BTRFS_CHUNK_ITEM_KEY;

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret < 0)
		जाओ out;
	अन्यथा अगर (ret > 0) अणु /* Logic error or corruption */
		btrfs_handle_fs_error(fs_info, -ENOENT,
				      "Failed lookup while freeing chunk.");
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	ret = btrfs_del_item(trans, root, path);
	अगर (ret < 0)
		btrfs_handle_fs_error(fs_info, ret,
				      "Failed to delete chunk item.");
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_del_sys_chunk(काष्ठा btrfs_fs_info *fs_info, u64 chunk_offset)
अणु
	काष्ठा btrfs_super_block *super_copy = fs_info->super_copy;
	काष्ठा btrfs_disk_key *disk_key;
	काष्ठा btrfs_chunk *chunk;
	u8 *ptr;
	पूर्णांक ret = 0;
	u32 num_stripes;
	u32 array_size;
	u32 len = 0;
	u32 cur;
	काष्ठा btrfs_key key;

	mutex_lock(&fs_info->chunk_mutex);
	array_size = btrfs_super_sys_array_size(super_copy);

	ptr = super_copy->sys_chunk_array;
	cur = 0;

	जबतक (cur < array_size) अणु
		disk_key = (काष्ठा btrfs_disk_key *)ptr;
		btrfs_disk_key_to_cpu(&key, disk_key);

		len = माप(*disk_key);

		अगर (key.type == BTRFS_CHUNK_ITEM_KEY) अणु
			chunk = (काष्ठा btrfs_chunk *)(ptr + len);
			num_stripes = btrfs_stack_chunk_num_stripes(chunk);
			len += btrfs_chunk_item_size(num_stripes);
		पूर्ण अन्यथा अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (key.objectid == BTRFS_FIRST_CHUNK_TREE_OBJECTID &&
		    key.offset == chunk_offset) अणु
			स_हटाओ(ptr, ptr + len, array_size - (cur + len));
			array_size -= len;
			btrfs_set_super_sys_array_size(super_copy, array_size);
		पूर्ण अन्यथा अणु
			ptr += len;
			cur += len;
		पूर्ण
	पूर्ण
	mutex_unlock(&fs_info->chunk_mutex);
	वापस ret;
पूर्ण

/*
 * btrfs_get_chunk_map() - Find the mapping containing the given logical extent.
 * @logical: Logical block offset in bytes.
 * @length: Length of extent in bytes.
 *
 * Return: Chunk mapping or ERR_PTR.
 */
काष्ठा extent_map *btrfs_get_chunk_map(काष्ठा btrfs_fs_info *fs_info,
				       u64 logical, u64 length)
अणु
	काष्ठा extent_map_tree *em_tree;
	काष्ठा extent_map *em;

	em_tree = &fs_info->mapping_tree;
	पढ़ो_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, logical, length);
	पढ़ो_unlock(&em_tree->lock);

	अगर (!em) अणु
		btrfs_crit(fs_info, "unable to find logical %llu length %llu",
			   logical, length);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (em->start > logical || em->start + em->len < logical) अणु
		btrfs_crit(fs_info,
			   "found a bad mapping, wanted %llu-%llu, found %llu-%llu",
			   logical, length, em->start, em->start + em->len);
		मुक्त_extent_map(em);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* callers are responsible क्रम dropping em's ref. */
	वापस em;
पूर्ण

पूर्णांक btrfs_हटाओ_chunk(काष्ठा btrfs_trans_handle *trans, u64 chunk_offset)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	u64 dev_extent_len = 0;
	पूर्णांक i, ret = 0;
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices;

	em = btrfs_get_chunk_map(fs_info, chunk_offset, 1);
	अगर (IS_ERR(em)) अणु
		/*
		 * This is a logic error, but we करोn't want to just rely on the
		 * user having built with ASSERT enabled, so अगर ASSERT करोesn't
		 * करो anything we still error out.
		 */
		ASSERT(0);
		वापस PTR_ERR(em);
	पूर्ण
	map = em->map_lookup;
	mutex_lock(&fs_info->chunk_mutex);
	check_प्रणाली_chunk(trans, map->type);
	mutex_unlock(&fs_info->chunk_mutex);

	/*
	 * Take the device list mutex to prevent races with the final phase of
	 * a device replace operation that replaces the device object associated
	 * with map stripes (dev-replace.c:btrfs_dev_replace_finishing()).
	 */
	mutex_lock(&fs_devices->device_list_mutex);
	क्रम (i = 0; i < map->num_stripes; i++) अणु
		काष्ठा btrfs_device *device = map->stripes[i].dev;
		ret = btrfs_मुक्त_dev_extent(trans, device,
					    map->stripes[i].physical,
					    &dev_extent_len);
		अगर (ret) अणु
			mutex_unlock(&fs_devices->device_list_mutex);
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण

		अगर (device->bytes_used > 0) अणु
			mutex_lock(&fs_info->chunk_mutex);
			btrfs_device_set_bytes_used(device,
					device->bytes_used - dev_extent_len);
			atomic64_add(dev_extent_len, &fs_info->मुक्त_chunk_space);
			btrfs_clear_space_info_full(fs_info);
			mutex_unlock(&fs_info->chunk_mutex);
		पूर्ण

		ret = btrfs_update_device(trans, device);
		अगर (ret) अणु
			mutex_unlock(&fs_devices->device_list_mutex);
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण
	पूर्ण
	mutex_unlock(&fs_devices->device_list_mutex);

	ret = btrfs_मुक्त_chunk(trans, chunk_offset);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

	trace_btrfs_chunk_मुक्त(fs_info, map, chunk_offset, em->len);

	अगर (map->type & BTRFS_BLOCK_GROUP_SYSTEM) अणु
		ret = btrfs_del_sys_chunk(fs_info, chunk_offset);
		अगर (ret) अणु
			btrfs_पात_transaction(trans, ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = btrfs_हटाओ_block_group(trans, chunk_offset, em);
	अगर (ret) अणु
		btrfs_पात_transaction(trans, ret);
		जाओ out;
	पूर्ण

out:
	/* once क्रम us */
	मुक्त_extent_map(em);
	वापस ret;
पूर्ण

पूर्णांक btrfs_relocate_chunk(काष्ठा btrfs_fs_info *fs_info, u64 chunk_offset)
अणु
	काष्ठा btrfs_root *root = fs_info->chunk_root;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_block_group *block_group;
	u64 length;
	पूर्णांक ret;

	/*
	 * Prevent races with स्वतःmatic removal of unused block groups.
	 * After we relocate and beक्रमe we हटाओ the chunk with offset
	 * chunk_offset, स्वतःmatic removal of the block group can kick in,
	 * resulting in a failure when calling btrfs_हटाओ_chunk() below.
	 *
	 * Make sure to acquire this mutex beक्रमe करोing a tree search (dev
	 * or chunk trees) to find chunks. Otherwise the cleaner kthपढ़ो might
	 * call btrfs_हटाओ_chunk() (through btrfs_delete_unused_bgs()) after
	 * we release the path used to search the chunk/dev tree and beक्रमe
	 * the current task acquires this mutex and calls us.
	 */
	lockdep_निश्चित_held(&fs_info->reclaim_bgs_lock);

	/* step one, relocate all the extents inside this chunk */
	btrfs_scrub_छोड़ो(fs_info);
	ret = btrfs_relocate_block_group(fs_info, chunk_offset);
	btrfs_scrub_जारी(fs_info);
	अगर (ret)
		वापस ret;

	block_group = btrfs_lookup_block_group(fs_info, chunk_offset);
	अगर (!block_group)
		वापस -ENOENT;
	btrfs_discard_cancel_work(&fs_info->discard_ctl, block_group);
	length = block_group->length;
	btrfs_put_block_group(block_group);

	/*
	 * On a zoned file प्रणाली, discard the whole block group, this will
	 * trigger a REQ_OP_ZONE_RESET operation on the device zone. If
	 * resetting the zone fails, करोn't treat it as a fatal problem from the
	 * fileप्रणाली's poपूर्णांक of view.
	 */
	अगर (btrfs_is_zoned(fs_info)) अणु
		ret = btrfs_discard_extent(fs_info, chunk_offset, length, शून्य);
		अगर (ret)
			btrfs_info(fs_info,
				"failed to reset zone %llu after relocation",
				chunk_offset);
	पूर्ण

	trans = btrfs_start_trans_हटाओ_block_group(root->fs_info,
						     chunk_offset);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		btrfs_handle_fs_error(root->fs_info, ret, शून्य);
		वापस ret;
	पूर्ण

	/*
	 * step two, delete the device extents and the
	 * chunk tree entries
	 */
	ret = btrfs_हटाओ_chunk(trans, chunk_offset);
	btrfs_end_transaction(trans);
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_relocate_sys_chunks(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *chunk_root = fs_info->chunk_root;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_chunk *chunk;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	u64 chunk_type;
	bool retried = false;
	पूर्णांक failed = 0;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

again:
	key.objectid = BTRFS_FIRST_CHUNK_TREE_OBJECTID;
	key.offset = (u64)-1;
	key.type = BTRFS_CHUNK_ITEM_KEY;

	जबतक (1) अणु
		mutex_lock(&fs_info->reclaim_bgs_lock);
		ret = btrfs_search_slot(शून्य, chunk_root, &key, path, 0, 0);
		अगर (ret < 0) अणु
			mutex_unlock(&fs_info->reclaim_bgs_lock);
			जाओ error;
		पूर्ण
		BUG_ON(ret == 0); /* Corruption */

		ret = btrfs_previous_item(chunk_root, path, key.objectid,
					  key.type);
		अगर (ret)
			mutex_unlock(&fs_info->reclaim_bgs_lock);
		अगर (ret < 0)
			जाओ error;
		अगर (ret > 0)
			अवरोध;

		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0]);

		chunk = btrfs_item_ptr(leaf, path->slots[0],
				       काष्ठा btrfs_chunk);
		chunk_type = btrfs_chunk_type(leaf, chunk);
		btrfs_release_path(path);

		अगर (chunk_type & BTRFS_BLOCK_GROUP_SYSTEM) अणु
			ret = btrfs_relocate_chunk(fs_info, found_key.offset);
			अगर (ret == -ENOSPC)
				failed++;
			अन्यथा
				BUG_ON(ret);
		पूर्ण
		mutex_unlock(&fs_info->reclaim_bgs_lock);

		अगर (found_key.offset == 0)
			अवरोध;
		key.offset = found_key.offset - 1;
	पूर्ण
	ret = 0;
	अगर (failed && !retried) अणु
		failed = 0;
		retried = true;
		जाओ again;
	पूर्ण अन्यथा अगर (WARN_ON(failed && retried)) अणु
		ret = -ENOSPC;
	पूर्ण
error:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * वापस 1 : allocate a data chunk successfully,
 * वापस <0: errors during allocating a data chunk,
 * वापस 0 : no need to allocate a data chunk.
 */
अटल पूर्णांक btrfs_may_alloc_data_chunk(काष्ठा btrfs_fs_info *fs_info,
				      u64 chunk_offset)
अणु
	काष्ठा btrfs_block_group *cache;
	u64 bytes_used;
	u64 chunk_type;

	cache = btrfs_lookup_block_group(fs_info, chunk_offset);
	ASSERT(cache);
	chunk_type = cache->flags;
	btrfs_put_block_group(cache);

	अगर (!(chunk_type & BTRFS_BLOCK_GROUP_DATA))
		वापस 0;

	spin_lock(&fs_info->data_sinfo->lock);
	bytes_used = fs_info->data_sinfo->bytes_used;
	spin_unlock(&fs_info->data_sinfo->lock);

	अगर (!bytes_used) अणु
		काष्ठा btrfs_trans_handle *trans;
		पूर्णांक ret;

		trans =	btrfs_join_transaction(fs_info->tree_root);
		अगर (IS_ERR(trans))
			वापस PTR_ERR(trans);

		ret = btrfs_क्रमce_chunk_alloc(trans, BTRFS_BLOCK_GROUP_DATA);
		btrfs_end_transaction(trans);
		अगर (ret < 0)
			वापस ret;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक insert_balance_item(काष्ठा btrfs_fs_info *fs_info,
			       काष्ठा btrfs_balance_control *bctl)
अणु
	काष्ठा btrfs_root *root = fs_info->tree_root;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_balance_item *item;
	काष्ठा btrfs_disk_balance_args disk_bargs;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	पूर्णांक ret, err;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	trans = btrfs_start_transaction(root, 0);
	अगर (IS_ERR(trans)) अणु
		btrfs_मुक्त_path(path);
		वापस PTR_ERR(trans);
	पूर्ण

	key.objectid = BTRFS_BALANCE_OBJECTID;
	key.type = BTRFS_TEMPORARY_ITEM_KEY;
	key.offset = 0;

	ret = btrfs_insert_empty_item(trans, root, path, &key,
				      माप(*item));
	अगर (ret)
		जाओ out;

	leaf = path->nodes[0];
	item = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_balance_item);

	memzero_extent_buffer(leaf, (अचिन्हित दीर्घ)item, माप(*item));

	btrfs_cpu_balance_args_to_disk(&disk_bargs, &bctl->data);
	btrfs_set_balance_data(leaf, item, &disk_bargs);
	btrfs_cpu_balance_args_to_disk(&disk_bargs, &bctl->meta);
	btrfs_set_balance_meta(leaf, item, &disk_bargs);
	btrfs_cpu_balance_args_to_disk(&disk_bargs, &bctl->sys);
	btrfs_set_balance_sys(leaf, item, &disk_bargs);

	btrfs_set_balance_flags(leaf, item, bctl->flags);

	btrfs_mark_buffer_dirty(leaf);
out:
	btrfs_मुक्त_path(path);
	err = btrfs_commit_transaction(trans);
	अगर (err && !ret)
		ret = err;
	वापस ret;
पूर्ण

अटल पूर्णांक del_balance_item(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *root = fs_info->tree_root;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	पूर्णांक ret, err;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	trans = btrfs_start_transaction_fallback_global_rsv(root, 0);
	अगर (IS_ERR(trans)) अणु
		btrfs_मुक्त_path(path);
		वापस PTR_ERR(trans);
	पूर्ण

	key.objectid = BTRFS_BALANCE_OBJECTID;
	key.type = BTRFS_TEMPORARY_ITEM_KEY;
	key.offset = 0;

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	अगर (ret < 0)
		जाओ out;
	अगर (ret > 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	ret = btrfs_del_item(trans, root, path);
out:
	btrfs_मुक्त_path(path);
	err = btrfs_commit_transaction(trans);
	अगर (err && !ret)
		ret = err;
	वापस ret;
पूर्ण

/*
 * This is a heuristic used to reduce the number of chunks balanced on
 * resume after balance was पूर्णांकerrupted.
 */
अटल व्योम update_balance_args(काष्ठा btrfs_balance_control *bctl)
अणु
	/*
	 * Turn on soft mode क्रम chunk types that were being converted.
	 */
	अगर (bctl->data.flags & BTRFS_BALANCE_ARGS_CONVERT)
		bctl->data.flags |= BTRFS_BALANCE_ARGS_SOFT;
	अगर (bctl->sys.flags & BTRFS_BALANCE_ARGS_CONVERT)
		bctl->sys.flags |= BTRFS_BALANCE_ARGS_SOFT;
	अगर (bctl->meta.flags & BTRFS_BALANCE_ARGS_CONVERT)
		bctl->meta.flags |= BTRFS_BALANCE_ARGS_SOFT;

	/*
	 * Turn on usage filter अगर is not alपढ़ोy used.  The idea is
	 * that chunks that we have alपढ़ोy balanced should be
	 * reasonably full.  Don't करो it क्रम chunks that are being
	 * converted - that will keep us from relocating unconverted
	 * (albeit full) chunks.
	 */
	अगर (!(bctl->data.flags & BTRFS_BALANCE_ARGS_USAGE) &&
	    !(bctl->data.flags & BTRFS_BALANCE_ARGS_USAGE_RANGE) &&
	    !(bctl->data.flags & BTRFS_BALANCE_ARGS_CONVERT)) अणु
		bctl->data.flags |= BTRFS_BALANCE_ARGS_USAGE;
		bctl->data.usage = 90;
	पूर्ण
	अगर (!(bctl->sys.flags & BTRFS_BALANCE_ARGS_USAGE) &&
	    !(bctl->sys.flags & BTRFS_BALANCE_ARGS_USAGE_RANGE) &&
	    !(bctl->sys.flags & BTRFS_BALANCE_ARGS_CONVERT)) अणु
		bctl->sys.flags |= BTRFS_BALANCE_ARGS_USAGE;
		bctl->sys.usage = 90;
	पूर्ण
	अगर (!(bctl->meta.flags & BTRFS_BALANCE_ARGS_USAGE) &&
	    !(bctl->meta.flags & BTRFS_BALANCE_ARGS_USAGE_RANGE) &&
	    !(bctl->meta.flags & BTRFS_BALANCE_ARGS_CONVERT)) अणु
		bctl->meta.flags |= BTRFS_BALANCE_ARGS_USAGE;
		bctl->meta.usage = 90;
	पूर्ण
पूर्ण

/*
 * Clear the balance status in fs_info and delete the balance item from disk.
 */
अटल व्योम reset_balance_state(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_balance_control *bctl = fs_info->balance_ctl;
	पूर्णांक ret;

	BUG_ON(!fs_info->balance_ctl);

	spin_lock(&fs_info->balance_lock);
	fs_info->balance_ctl = शून्य;
	spin_unlock(&fs_info->balance_lock);

	kमुक्त(bctl);
	ret = del_balance_item(fs_info);
	अगर (ret)
		btrfs_handle_fs_error(fs_info, ret, शून्य);
पूर्ण

/*
 * Balance filters.  Return 1 अगर chunk should be filtered out
 * (should not be balanced).
 */
अटल पूर्णांक chunk_profiles_filter(u64 chunk_type,
				 काष्ठा btrfs_balance_args *bargs)
अणु
	chunk_type = chunk_to_extended(chunk_type) &
				BTRFS_EXTENDED_PROखाता_MASK;

	अगर (bargs->profiles & chunk_type)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक chunk_usage_range_filter(काष्ठा btrfs_fs_info *fs_info, u64 chunk_offset,
			      काष्ठा btrfs_balance_args *bargs)
अणु
	काष्ठा btrfs_block_group *cache;
	u64 chunk_used;
	u64 user_thresh_min;
	u64 user_thresh_max;
	पूर्णांक ret = 1;

	cache = btrfs_lookup_block_group(fs_info, chunk_offset);
	chunk_used = cache->used;

	अगर (bargs->usage_min == 0)
		user_thresh_min = 0;
	अन्यथा
		user_thresh_min = भाग_factor_fine(cache->length,
						  bargs->usage_min);

	अगर (bargs->usage_max == 0)
		user_thresh_max = 1;
	अन्यथा अगर (bargs->usage_max > 100)
		user_thresh_max = cache->length;
	अन्यथा
		user_thresh_max = भाग_factor_fine(cache->length,
						  bargs->usage_max);

	अगर (user_thresh_min <= chunk_used && chunk_used < user_thresh_max)
		ret = 0;

	btrfs_put_block_group(cache);
	वापस ret;
पूर्ण

अटल पूर्णांक chunk_usage_filter(काष्ठा btrfs_fs_info *fs_info,
		u64 chunk_offset, काष्ठा btrfs_balance_args *bargs)
अणु
	काष्ठा btrfs_block_group *cache;
	u64 chunk_used, user_thresh;
	पूर्णांक ret = 1;

	cache = btrfs_lookup_block_group(fs_info, chunk_offset);
	chunk_used = cache->used;

	अगर (bargs->usage_min == 0)
		user_thresh = 1;
	अन्यथा अगर (bargs->usage > 100)
		user_thresh = cache->length;
	अन्यथा
		user_thresh = भाग_factor_fine(cache->length, bargs->usage);

	अगर (chunk_used < user_thresh)
		ret = 0;

	btrfs_put_block_group(cache);
	वापस ret;
पूर्ण

अटल पूर्णांक chunk_devid_filter(काष्ठा extent_buffer *leaf,
			      काष्ठा btrfs_chunk *chunk,
			      काष्ठा btrfs_balance_args *bargs)
अणु
	काष्ठा btrfs_stripe *stripe;
	पूर्णांक num_stripes = btrfs_chunk_num_stripes(leaf, chunk);
	पूर्णांक i;

	क्रम (i = 0; i < num_stripes; i++) अणु
		stripe = btrfs_stripe_nr(chunk, i);
		अगर (btrfs_stripe_devid(leaf, stripe) == bargs->devid)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल u64 calc_data_stripes(u64 type, पूर्णांक num_stripes)
अणु
	स्थिर पूर्णांक index = btrfs_bg_flags_to_raid_index(type);
	स्थिर पूर्णांक ncopies = btrfs_raid_array[index].ncopies;
	स्थिर पूर्णांक nparity = btrfs_raid_array[index].nparity;

	अगर (nparity)
		वापस num_stripes - nparity;
	अन्यथा
		वापस num_stripes / ncopies;
पूर्ण

/* [pstart, pend) */
अटल पूर्णांक chunk_drange_filter(काष्ठा extent_buffer *leaf,
			       काष्ठा btrfs_chunk *chunk,
			       काष्ठा btrfs_balance_args *bargs)
अणु
	काष्ठा btrfs_stripe *stripe;
	पूर्णांक num_stripes = btrfs_chunk_num_stripes(leaf, chunk);
	u64 stripe_offset;
	u64 stripe_length;
	u64 type;
	पूर्णांक factor;
	पूर्णांक i;

	अगर (!(bargs->flags & BTRFS_BALANCE_ARGS_DEVID))
		वापस 0;

	type = btrfs_chunk_type(leaf, chunk);
	factor = calc_data_stripes(type, num_stripes);

	क्रम (i = 0; i < num_stripes; i++) अणु
		stripe = btrfs_stripe_nr(chunk, i);
		अगर (btrfs_stripe_devid(leaf, stripe) != bargs->devid)
			जारी;

		stripe_offset = btrfs_stripe_offset(leaf, stripe);
		stripe_length = btrfs_chunk_length(leaf, chunk);
		stripe_length = भाग_u64(stripe_length, factor);

		अगर (stripe_offset < bargs->pend &&
		    stripe_offset + stripe_length > bargs->pstart)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* [vstart, vend) */
अटल पूर्णांक chunk_vrange_filter(काष्ठा extent_buffer *leaf,
			       काष्ठा btrfs_chunk *chunk,
			       u64 chunk_offset,
			       काष्ठा btrfs_balance_args *bargs)
अणु
	अगर (chunk_offset < bargs->vend &&
	    chunk_offset + btrfs_chunk_length(leaf, chunk) > bargs->vstart)
		/* at least part of the chunk is inside this vrange */
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक chunk_stripes_range_filter(काष्ठा extent_buffer *leaf,
			       काष्ठा btrfs_chunk *chunk,
			       काष्ठा btrfs_balance_args *bargs)
अणु
	पूर्णांक num_stripes = btrfs_chunk_num_stripes(leaf, chunk);

	अगर (bargs->stripes_min <= num_stripes
			&& num_stripes <= bargs->stripes_max)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक chunk_soft_convert_filter(u64 chunk_type,
				     काष्ठा btrfs_balance_args *bargs)
अणु
	अगर (!(bargs->flags & BTRFS_BALANCE_ARGS_CONVERT))
		वापस 0;

	chunk_type = chunk_to_extended(chunk_type) &
				BTRFS_EXTENDED_PROखाता_MASK;

	अगर (bargs->target == chunk_type)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक should_balance_chunk(काष्ठा extent_buffer *leaf,
				काष्ठा btrfs_chunk *chunk, u64 chunk_offset)
अणु
	काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	काष्ठा btrfs_balance_control *bctl = fs_info->balance_ctl;
	काष्ठा btrfs_balance_args *bargs = शून्य;
	u64 chunk_type = btrfs_chunk_type(leaf, chunk);

	/* type filter */
	अगर (!((chunk_type & BTRFS_BLOCK_GROUP_TYPE_MASK) &
	      (bctl->flags & BTRFS_BALANCE_TYPE_MASK))) अणु
		वापस 0;
	पूर्ण

	अगर (chunk_type & BTRFS_BLOCK_GROUP_DATA)
		bargs = &bctl->data;
	अन्यथा अगर (chunk_type & BTRFS_BLOCK_GROUP_SYSTEM)
		bargs = &bctl->sys;
	अन्यथा अगर (chunk_type & BTRFS_BLOCK_GROUP_METADATA)
		bargs = &bctl->meta;

	/* profiles filter */
	अगर ((bargs->flags & BTRFS_BALANCE_ARGS_PROखाताS) &&
	    chunk_profiles_filter(chunk_type, bargs)) अणु
		वापस 0;
	पूर्ण

	/* usage filter */
	अगर ((bargs->flags & BTRFS_BALANCE_ARGS_USAGE) &&
	    chunk_usage_filter(fs_info, chunk_offset, bargs)) अणु
		वापस 0;
	पूर्ण अन्यथा अगर ((bargs->flags & BTRFS_BALANCE_ARGS_USAGE_RANGE) &&
	    chunk_usage_range_filter(fs_info, chunk_offset, bargs)) अणु
		वापस 0;
	पूर्ण

	/* devid filter */
	अगर ((bargs->flags & BTRFS_BALANCE_ARGS_DEVID) &&
	    chunk_devid_filter(leaf, chunk, bargs)) अणु
		वापस 0;
	पूर्ण

	/* drange filter, makes sense only with devid filter */
	अगर ((bargs->flags & BTRFS_BALANCE_ARGS_DRANGE) &&
	    chunk_drange_filter(leaf, chunk, bargs)) अणु
		वापस 0;
	पूर्ण

	/* vrange filter */
	अगर ((bargs->flags & BTRFS_BALANCE_ARGS_VRANGE) &&
	    chunk_vrange_filter(leaf, chunk, chunk_offset, bargs)) अणु
		वापस 0;
	पूर्ण

	/* stripes filter */
	अगर ((bargs->flags & BTRFS_BALANCE_ARGS_STRIPES_RANGE) &&
	    chunk_stripes_range_filter(leaf, chunk, bargs)) अणु
		वापस 0;
	पूर्ण

	/* soft profile changing mode */
	अगर ((bargs->flags & BTRFS_BALANCE_ARGS_SOFT) &&
	    chunk_soft_convert_filter(chunk_type, bargs)) अणु
		वापस 0;
	पूर्ण

	/*
	 * limited by count, must be the last filter
	 */
	अगर ((bargs->flags & BTRFS_BALANCE_ARGS_LIMIT)) अणु
		अगर (bargs->limit == 0)
			वापस 0;
		अन्यथा
			bargs->limit--;
	पूर्ण अन्यथा अगर ((bargs->flags & BTRFS_BALANCE_ARGS_LIMIT_RANGE)) अणु
		/*
		 * Same logic as the 'limit' filter; the minimum cannot be
		 * determined here because we करो not have the global inक्रमmation
		 * about the count of all chunks that satisfy the filters.
		 */
		अगर (bargs->limit_max == 0)
			वापस 0;
		अन्यथा
			bargs->limit_max--;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक __btrfs_balance(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_balance_control *bctl = fs_info->balance_ctl;
	काष्ठा btrfs_root *chunk_root = fs_info->chunk_root;
	u64 chunk_type;
	काष्ठा btrfs_chunk *chunk;
	काष्ठा btrfs_path *path = शून्य;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा extent_buffer *leaf;
	पूर्णांक slot;
	पूर्णांक ret;
	पूर्णांक enospc_errors = 0;
	bool counting = true;
	/* The single value limit and min/max limits use the same bytes in the */
	u64 limit_data = bctl->data.limit;
	u64 limit_meta = bctl->meta.limit;
	u64 limit_sys = bctl->sys.limit;
	u32 count_data = 0;
	u32 count_meta = 0;
	u32 count_sys = 0;
	पूर्णांक chunk_reserved = 0;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	/* zero out stat counters */
	spin_lock(&fs_info->balance_lock);
	स_रखो(&bctl->stat, 0, माप(bctl->stat));
	spin_unlock(&fs_info->balance_lock);
again:
	अगर (!counting) अणु
		/*
		 * The single value limit and min/max limits use the same bytes
		 * in the
		 */
		bctl->data.limit = limit_data;
		bctl->meta.limit = limit_meta;
		bctl->sys.limit = limit_sys;
	पूर्ण
	key.objectid = BTRFS_FIRST_CHUNK_TREE_OBJECTID;
	key.offset = (u64)-1;
	key.type = BTRFS_CHUNK_ITEM_KEY;

	जबतक (1) अणु
		अगर ((!counting && atomic_पढ़ो(&fs_info->balance_छोड़ो_req)) ||
		    atomic_पढ़ो(&fs_info->balance_cancel_req)) अणु
			ret = -ECANCELED;
			जाओ error;
		पूर्ण

		mutex_lock(&fs_info->reclaim_bgs_lock);
		ret = btrfs_search_slot(शून्य, chunk_root, &key, path, 0, 0);
		अगर (ret < 0) अणु
			mutex_unlock(&fs_info->reclaim_bgs_lock);
			जाओ error;
		पूर्ण

		/*
		 * this shouldn't happen, it means the last relocate
		 * failed
		 */
		अगर (ret == 0)
			BUG(); /* FIXME अवरोध ? */

		ret = btrfs_previous_item(chunk_root, path, 0,
					  BTRFS_CHUNK_ITEM_KEY);
		अगर (ret) अणु
			mutex_unlock(&fs_info->reclaim_bgs_lock);
			ret = 0;
			अवरोध;
		पूर्ण

		leaf = path->nodes[0];
		slot = path->slots[0];
		btrfs_item_key_to_cpu(leaf, &found_key, slot);

		अगर (found_key.objectid != key.objectid) अणु
			mutex_unlock(&fs_info->reclaim_bgs_lock);
			अवरोध;
		पूर्ण

		chunk = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_chunk);
		chunk_type = btrfs_chunk_type(leaf, chunk);

		अगर (!counting) अणु
			spin_lock(&fs_info->balance_lock);
			bctl->stat.considered++;
			spin_unlock(&fs_info->balance_lock);
		पूर्ण

		ret = should_balance_chunk(leaf, chunk, found_key.offset);

		btrfs_release_path(path);
		अगर (!ret) अणु
			mutex_unlock(&fs_info->reclaim_bgs_lock);
			जाओ loop;
		पूर्ण

		अगर (counting) अणु
			mutex_unlock(&fs_info->reclaim_bgs_lock);
			spin_lock(&fs_info->balance_lock);
			bctl->stat.expected++;
			spin_unlock(&fs_info->balance_lock);

			अगर (chunk_type & BTRFS_BLOCK_GROUP_DATA)
				count_data++;
			अन्यथा अगर (chunk_type & BTRFS_BLOCK_GROUP_SYSTEM)
				count_sys++;
			अन्यथा अगर (chunk_type & BTRFS_BLOCK_GROUP_METADATA)
				count_meta++;

			जाओ loop;
		पूर्ण

		/*
		 * Apply limit_min filter, no need to check अगर the LIMITS
		 * filter is used, limit_min is 0 by शेष
		 */
		अगर (((chunk_type & BTRFS_BLOCK_GROUP_DATA) &&
					count_data < bctl->data.limit_min)
				|| ((chunk_type & BTRFS_BLOCK_GROUP_METADATA) &&
					count_meta < bctl->meta.limit_min)
				|| ((chunk_type & BTRFS_BLOCK_GROUP_SYSTEM) &&
					count_sys < bctl->sys.limit_min)) अणु
			mutex_unlock(&fs_info->reclaim_bgs_lock);
			जाओ loop;
		पूर्ण

		अगर (!chunk_reserved) अणु
			/*
			 * We may be relocating the only data chunk we have,
			 * which could potentially end up with losing data's
			 * raid profile, so lets allocate an empty one in
			 * advance.
			 */
			ret = btrfs_may_alloc_data_chunk(fs_info,
							 found_key.offset);
			अगर (ret < 0) अणु
				mutex_unlock(&fs_info->reclaim_bgs_lock);
				जाओ error;
			पूर्ण अन्यथा अगर (ret == 1) अणु
				chunk_reserved = 1;
			पूर्ण
		पूर्ण

		ret = btrfs_relocate_chunk(fs_info, found_key.offset);
		mutex_unlock(&fs_info->reclaim_bgs_lock);
		अगर (ret == -ENOSPC) अणु
			enospc_errors++;
		पूर्ण अन्यथा अगर (ret == -ETXTBSY) अणु
			btrfs_info(fs_info,
	   "skipping relocation of block group %llu due to active swapfile",
				   found_key.offset);
			ret = 0;
		पूर्ण अन्यथा अगर (ret) अणु
			जाओ error;
		पूर्ण अन्यथा अणु
			spin_lock(&fs_info->balance_lock);
			bctl->stat.completed++;
			spin_unlock(&fs_info->balance_lock);
		पूर्ण
loop:
		अगर (found_key.offset == 0)
			अवरोध;
		key.offset = found_key.offset - 1;
	पूर्ण

	अगर (counting) अणु
		btrfs_release_path(path);
		counting = false;
		जाओ again;
	पूर्ण
error:
	btrfs_मुक्त_path(path);
	अगर (enospc_errors) अणु
		btrfs_info(fs_info, "%d enospc errors during balance",
			   enospc_errors);
		अगर (!ret)
			ret = -ENOSPC;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * alloc_profile_is_valid - see अगर a given profile is valid and reduced
 * @flags: profile to validate
 * @extended: अगर true @flags is treated as an extended profile
 */
अटल पूर्णांक alloc_profile_is_valid(u64 flags, पूर्णांक extended)
अणु
	u64 mask = (extended ? BTRFS_EXTENDED_PROखाता_MASK :
			       BTRFS_BLOCK_GROUP_PROखाता_MASK);

	flags &= ~BTRFS_BLOCK_GROUP_TYPE_MASK;

	/* 1) check that all other bits are zeroed */
	अगर (flags & ~mask)
		वापस 0;

	/* 2) see अगर profile is reduced */
	अगर (flags == 0)
		वापस !extended; /* "0" is valid क्रम usual profiles */

	वापस has_single_bit_set(flags);
पूर्ण

अटल अंतरभूत पूर्णांक balance_need_बंद(काष्ठा btrfs_fs_info *fs_info)
अणु
	/* cancel requested || normal निकास path */
	वापस atomic_पढ़ो(&fs_info->balance_cancel_req) ||
		(atomic_पढ़ो(&fs_info->balance_छोड़ो_req) == 0 &&
		 atomic_पढ़ो(&fs_info->balance_cancel_req) == 0);
पूर्ण

/*
 * Validate target profile against allowed profiles and वापस true अगर it's OK.
 * Otherwise prपूर्णांक the error message and वापस false.
 */
अटल अंतरभूत पूर्णांक validate_convert_profile(काष्ठा btrfs_fs_info *fs_info,
		स्थिर काष्ठा btrfs_balance_args *bargs,
		u64 allowed, स्थिर अक्षर *type)
अणु
	अगर (!(bargs->flags & BTRFS_BALANCE_ARGS_CONVERT))
		वापस true;

	/* Profile is valid and करोes not have bits outside of the allowed set */
	अगर (alloc_profile_is_valid(bargs->target, 1) &&
	    (bargs->target & ~allowed) == 0)
		वापस true;

	btrfs_err(fs_info, "balance: invalid convert %s profile %s",
			type, btrfs_bg_type_to_raid_name(bargs->target));
	वापस false;
पूर्ण

/*
 * Fill @buf with textual description of balance filter flags @bargs, up to
 * @size_buf including the terminating null. The output may be trimmed अगर it
 * करोes not fit पूर्णांकo the provided buffer.
 */
अटल व्योम describe_balance_args(काष्ठा btrfs_balance_args *bargs, अक्षर *buf,
				 u32 size_buf)
अणु
	पूर्णांक ret;
	u32 size_bp = size_buf;
	अक्षर *bp = buf;
	u64 flags = bargs->flags;
	अक्षर पंचांगp_buf[128] = अणु'\0'पूर्ण;

	अगर (!flags)
		वापस;

#घोषणा CHECK_APPEND_NOARG(a)						\
	करो अणु								\
		ret = snम_लिखो(bp, size_bp, (a));			\
		अगर (ret < 0 || ret >= size_bp)				\
			जाओ out_overflow;				\
		size_bp -= ret;						\
		bp += ret;						\
	पूर्ण जबतक (0)

#घोषणा CHECK_APPEND_1ARG(a, v1)					\
	करो अणु								\
		ret = snम_लिखो(bp, size_bp, (a), (v1));			\
		अगर (ret < 0 || ret >= size_bp)				\
			जाओ out_overflow;				\
		size_bp -= ret;						\
		bp += ret;						\
	पूर्ण जबतक (0)

#घोषणा CHECK_APPEND_2ARG(a, v1, v2)					\
	करो अणु								\
		ret = snम_लिखो(bp, size_bp, (a), (v1), (v2));		\
		अगर (ret < 0 || ret >= size_bp)				\
			जाओ out_overflow;				\
		size_bp -= ret;						\
		bp += ret;						\
	पूर्ण जबतक (0)

	अगर (flags & BTRFS_BALANCE_ARGS_CONVERT)
		CHECK_APPEND_1ARG("convert=%s,",
				  btrfs_bg_type_to_raid_name(bargs->target));

	अगर (flags & BTRFS_BALANCE_ARGS_SOFT)
		CHECK_APPEND_NOARG("soft,");

	अगर (flags & BTRFS_BALANCE_ARGS_PROखाताS) अणु
		btrfs_describe_block_groups(bargs->profiles, पंचांगp_buf,
					    माप(पंचांगp_buf));
		CHECK_APPEND_1ARG("profiles=%s,", पंचांगp_buf);
	पूर्ण

	अगर (flags & BTRFS_BALANCE_ARGS_USAGE)
		CHECK_APPEND_1ARG("usage=%llu,", bargs->usage);

	अगर (flags & BTRFS_BALANCE_ARGS_USAGE_RANGE)
		CHECK_APPEND_2ARG("usage=%u..%u,",
				  bargs->usage_min, bargs->usage_max);

	अगर (flags & BTRFS_BALANCE_ARGS_DEVID)
		CHECK_APPEND_1ARG("devid=%llu,", bargs->devid);

	अगर (flags & BTRFS_BALANCE_ARGS_DRANGE)
		CHECK_APPEND_2ARG("drange=%llu..%llu,",
				  bargs->pstart, bargs->pend);

	अगर (flags & BTRFS_BALANCE_ARGS_VRANGE)
		CHECK_APPEND_2ARG("vrange=%llu..%llu,",
				  bargs->vstart, bargs->vend);

	अगर (flags & BTRFS_BALANCE_ARGS_LIMIT)
		CHECK_APPEND_1ARG("limit=%llu,", bargs->limit);

	अगर (flags & BTRFS_BALANCE_ARGS_LIMIT_RANGE)
		CHECK_APPEND_2ARG("limit=%u..%u,",
				bargs->limit_min, bargs->limit_max);

	अगर (flags & BTRFS_BALANCE_ARGS_STRIPES_RANGE)
		CHECK_APPEND_2ARG("stripes=%u..%u,",
				  bargs->stripes_min, bargs->stripes_max);

#अघोषित CHECK_APPEND_2ARG
#अघोषित CHECK_APPEND_1ARG
#अघोषित CHECK_APPEND_NOARG

out_overflow:

	अगर (size_bp < size_buf)
		buf[size_buf - size_bp - 1] = '\0'; /* हटाओ last , */
	अन्यथा
		buf[0] = '\0';
पूर्ण

अटल व्योम describe_balance_start_or_resume(काष्ठा btrfs_fs_info *fs_info)
अणु
	u32 size_buf = 1024;
	अक्षर पंचांगp_buf[192] = अणु'\0'पूर्ण;
	अक्षर *buf;
	अक्षर *bp;
	u32 size_bp = size_buf;
	पूर्णांक ret;
	काष्ठा btrfs_balance_control *bctl = fs_info->balance_ctl;

	buf = kzalloc(size_buf, GFP_KERNEL);
	अगर (!buf)
		वापस;

	bp = buf;

#घोषणा CHECK_APPEND_1ARG(a, v1)					\
	करो अणु								\
		ret = snम_लिखो(bp, size_bp, (a), (v1));			\
		अगर (ret < 0 || ret >= size_bp)				\
			जाओ out_overflow;				\
		size_bp -= ret;						\
		bp += ret;						\
	पूर्ण जबतक (0)

	अगर (bctl->flags & BTRFS_BALANCE_FORCE)
		CHECK_APPEND_1ARG("%s", "-f ");

	अगर (bctl->flags & BTRFS_BALANCE_DATA) अणु
		describe_balance_args(&bctl->data, पंचांगp_buf, माप(पंचांगp_buf));
		CHECK_APPEND_1ARG("-d%s ", पंचांगp_buf);
	पूर्ण

	अगर (bctl->flags & BTRFS_BALANCE_METADATA) अणु
		describe_balance_args(&bctl->meta, पंचांगp_buf, माप(पंचांगp_buf));
		CHECK_APPEND_1ARG("-m%s ", पंचांगp_buf);
	पूर्ण

	अगर (bctl->flags & BTRFS_BALANCE_SYSTEM) अणु
		describe_balance_args(&bctl->sys, पंचांगp_buf, माप(पंचांगp_buf));
		CHECK_APPEND_1ARG("-s%s ", पंचांगp_buf);
	पूर्ण

#अघोषित CHECK_APPEND_1ARG

out_overflow:

	अगर (size_bp < size_buf)
		buf[size_buf - size_bp - 1] = '\0'; /* हटाओ last " " */
	btrfs_info(fs_info, "balance: %s %s",
		   (bctl->flags & BTRFS_BALANCE_RESUME) ?
		   "resume" : "start", buf);

	kमुक्त(buf);
पूर्ण

/*
 * Should be called with balance mutexe held
 */
पूर्णांक btrfs_balance(काष्ठा btrfs_fs_info *fs_info,
		  काष्ठा btrfs_balance_control *bctl,
		  काष्ठा btrfs_ioctl_balance_args *bargs)
अणु
	u64 meta_target, data_target;
	u64 allowed;
	पूर्णांक mixed = 0;
	पूर्णांक ret;
	u64 num_devices;
	अचिन्हित seq;
	bool reducing_redundancy;
	पूर्णांक i;

	अगर (btrfs_fs_closing(fs_info) ||
	    atomic_पढ़ो(&fs_info->balance_छोड़ो_req) ||
	    btrfs_should_cancel_balance(fs_info)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	allowed = btrfs_super_incompat_flags(fs_info->super_copy);
	अगर (allowed & BTRFS_FEATURE_INCOMPAT_MIXED_GROUPS)
		mixed = 1;

	/*
	 * In हाल of mixed groups both data and meta should be picked,
	 * and identical options should be given क्रम both of them.
	 */
	allowed = BTRFS_BALANCE_DATA | BTRFS_BALANCE_METADATA;
	अगर (mixed && (bctl->flags & allowed)) अणु
		अगर (!(bctl->flags & BTRFS_BALANCE_DATA) ||
		    !(bctl->flags & BTRFS_BALANCE_METADATA) ||
		    स_भेद(&bctl->data, &bctl->meta, माप(bctl->data))) अणु
			btrfs_err(fs_info,
	  "balance: mixed groups data and metadata options must be the same");
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * rw_devices will not change at the moment, device add/delete/replace
	 * are exclusive
	 */
	num_devices = fs_info->fs_devices->rw_devices;

	/*
	 * SINGLE profile on-disk has no profile bit, but in-memory we have a
	 * special bit क्रम it, to make it easier to distinguish.  Thus we need
	 * to set it manually, or balance would refuse the profile.
	 */
	allowed = BTRFS_AVAIL_ALLOC_BIT_SINGLE;
	क्रम (i = 0; i < ARRAY_SIZE(btrfs_raid_array); i++)
		अगर (num_devices >= btrfs_raid_array[i].devs_min)
			allowed |= btrfs_raid_array[i].bg_flag;

	अगर (!validate_convert_profile(fs_info, &bctl->data, allowed, "data") ||
	    !validate_convert_profile(fs_info, &bctl->meta, allowed, "metadata") ||
	    !validate_convert_profile(fs_info, &bctl->sys,  allowed, "system")) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Allow to reduce metadata or प्रणाली पूर्णांकegrity only अगर क्रमce set क्रम
	 * profiles with redundancy (copies, parity)
	 */
	allowed = 0;
	क्रम (i = 0; i < ARRAY_SIZE(btrfs_raid_array); i++) अणु
		अगर (btrfs_raid_array[i].ncopies >= 2 ||
		    btrfs_raid_array[i].tolerated_failures >= 1)
			allowed |= btrfs_raid_array[i].bg_flag;
	पूर्ण
	करो अणु
		seq = पढ़ो_seqbegin(&fs_info->profiles_lock);

		अगर (((bctl->sys.flags & BTRFS_BALANCE_ARGS_CONVERT) &&
		     (fs_info->avail_प्रणाली_alloc_bits & allowed) &&
		     !(bctl->sys.target & allowed)) ||
		    ((bctl->meta.flags & BTRFS_BALANCE_ARGS_CONVERT) &&
		     (fs_info->avail_metadata_alloc_bits & allowed) &&
		     !(bctl->meta.target & allowed)))
			reducing_redundancy = true;
		अन्यथा
			reducing_redundancy = false;

		/* अगर we're not converting, the target field is uninitialized */
		meta_target = (bctl->meta.flags & BTRFS_BALANCE_ARGS_CONVERT) ?
			bctl->meta.target : fs_info->avail_metadata_alloc_bits;
		data_target = (bctl->data.flags & BTRFS_BALANCE_ARGS_CONVERT) ?
			bctl->data.target : fs_info->avail_data_alloc_bits;
	पूर्ण जबतक (पढ़ो_seqretry(&fs_info->profiles_lock, seq));

	अगर (reducing_redundancy) अणु
		अगर (bctl->flags & BTRFS_BALANCE_FORCE) अणु
			btrfs_info(fs_info,
			   "balance: force reducing metadata redundancy");
		पूर्ण अन्यथा अणु
			btrfs_err(fs_info,
	"balance: reduces metadata redundancy, use --force if you want this");
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (btrfs_get_num_tolerated_disk_barrier_failures(meta_target) <
		btrfs_get_num_tolerated_disk_barrier_failures(data_target)) अणु
		btrfs_warn(fs_info,
	"balance: metadata profile %s has lower redundancy than data profile %s",
				btrfs_bg_type_to_raid_name(meta_target),
				btrfs_bg_type_to_raid_name(data_target));
	पूर्ण

	अगर (fs_info->send_in_progress) अणु
		btrfs_warn_rl(fs_info,
"cannot run balance while send operations are in progress (%d in progress)",
			      fs_info->send_in_progress);
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	ret = insert_balance_item(fs_info, bctl);
	अगर (ret && ret != -EEXIST)
		जाओ out;

	अगर (!(bctl->flags & BTRFS_BALANCE_RESUME)) अणु
		BUG_ON(ret == -EEXIST);
		BUG_ON(fs_info->balance_ctl);
		spin_lock(&fs_info->balance_lock);
		fs_info->balance_ctl = bctl;
		spin_unlock(&fs_info->balance_lock);
	पूर्ण अन्यथा अणु
		BUG_ON(ret != -EEXIST);
		spin_lock(&fs_info->balance_lock);
		update_balance_args(bctl);
		spin_unlock(&fs_info->balance_lock);
	पूर्ण

	ASSERT(!test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags));
	set_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags);
	describe_balance_start_or_resume(fs_info);
	mutex_unlock(&fs_info->balance_mutex);

	ret = __btrfs_balance(fs_info);

	mutex_lock(&fs_info->balance_mutex);
	अगर (ret == -ECANCELED && atomic_पढ़ो(&fs_info->balance_छोड़ो_req))
		btrfs_info(fs_info, "balance: paused");
	/*
	 * Balance can be canceled by:
	 *
	 * - Regular cancel request
	 *   Then ret == -ECANCELED and balance_cancel_req > 0
	 *
	 * - Fatal संकेत to "btrfs" process
	 *   Either the संकेत caught by रुको_reserve_ticket() and callers
	 *   got -EINTR, or caught by btrfs_should_cancel_balance() and
	 *   got -ECANCELED.
	 *   Either way, in this हाल balance_cancel_req = 0, and
	 *   ret == -EINTR or ret == -ECANCELED.
	 *
	 * So here we only check the वापस value to catch canceled balance.
	 */
	अन्यथा अगर (ret == -ECANCELED || ret == -EINTR)
		btrfs_info(fs_info, "balance: canceled");
	अन्यथा
		btrfs_info(fs_info, "balance: ended with status: %d", ret);

	clear_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags);

	अगर (bargs) अणु
		स_रखो(bargs, 0, माप(*bargs));
		btrfs_update_ioctl_balance_args(fs_info, bargs);
	पूर्ण

	अगर ((ret && ret != -ECANCELED && ret != -ENOSPC) ||
	    balance_need_बंद(fs_info)) अणु
		reset_balance_state(fs_info);
		btrfs_exclop_finish(fs_info);
	पूर्ण

	wake_up(&fs_info->balance_रुको_q);

	वापस ret;
out:
	अगर (bctl->flags & BTRFS_BALANCE_RESUME)
		reset_balance_state(fs_info);
	अन्यथा
		kमुक्त(bctl);
	btrfs_exclop_finish(fs_info);

	वापस ret;
पूर्ण

अटल पूर्णांक balance_kthपढ़ो(व्योम *data)
अणु
	काष्ठा btrfs_fs_info *fs_info = data;
	पूर्णांक ret = 0;

	mutex_lock(&fs_info->balance_mutex);
	अगर (fs_info->balance_ctl)
		ret = btrfs_balance(fs_info, fs_info->balance_ctl, शून्य);
	mutex_unlock(&fs_info->balance_mutex);

	वापस ret;
पूर्ण

पूर्णांक btrfs_resume_balance_async(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा task_काष्ठा *tsk;

	mutex_lock(&fs_info->balance_mutex);
	अगर (!fs_info->balance_ctl) अणु
		mutex_unlock(&fs_info->balance_mutex);
		वापस 0;
	पूर्ण
	mutex_unlock(&fs_info->balance_mutex);

	अगर (btrfs_test_opt(fs_info, SKIP_BALANCE)) अणु
		btrfs_info(fs_info, "balance: resume skipped");
		वापस 0;
	पूर्ण

	/*
	 * A ro->rw remount sequence should जारी with the छोड़ोd balance
	 * regardless of who छोड़ोs it, प्रणाली or the user as of now, so set
	 * the resume flag.
	 */
	spin_lock(&fs_info->balance_lock);
	fs_info->balance_ctl->flags |= BTRFS_BALANCE_RESUME;
	spin_unlock(&fs_info->balance_lock);

	tsk = kthपढ़ो_run(balance_kthपढ़ो, fs_info, "btrfs-balance");
	वापस PTR_ERR_OR_ZERO(tsk);
पूर्ण

पूर्णांक btrfs_recover_balance(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_balance_control *bctl;
	काष्ठा btrfs_balance_item *item;
	काष्ठा btrfs_disk_balance_args disk_bargs;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	पूर्णांक ret;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = BTRFS_BALANCE_OBJECTID;
	key.type = BTRFS_TEMPORARY_ITEM_KEY;
	key.offset = 0;

	ret = btrfs_search_slot(शून्य, fs_info->tree_root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;
	अगर (ret > 0) अणु /* ret = -ENOENT; */
		ret = 0;
		जाओ out;
	पूर्ण

	bctl = kzalloc(माप(*bctl), GFP_NOFS);
	अगर (!bctl) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	leaf = path->nodes[0];
	item = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_balance_item);

	bctl->flags = btrfs_balance_flags(leaf, item);
	bctl->flags |= BTRFS_BALANCE_RESUME;

	btrfs_balance_data(leaf, item, &disk_bargs);
	btrfs_disk_balance_args_to_cpu(&bctl->data, &disk_bargs);
	btrfs_balance_meta(leaf, item, &disk_bargs);
	btrfs_disk_balance_args_to_cpu(&bctl->meta, &disk_bargs);
	btrfs_balance_sys(leaf, item, &disk_bargs);
	btrfs_disk_balance_args_to_cpu(&bctl->sys, &disk_bargs);

	/*
	 * This should never happen, as the छोड़ोd balance state is recovered
	 * during mount without any chance of other exclusive ops to collide.
	 *
	 * This gives the exclusive op status to balance and keeps in छोड़ोd
	 * state until user पूर्णांकervention (cancel or umount). If the ownership
	 * cannot be asचिन्हित, show a message but करो not fail. The balance
	 * is in a छोड़ोd state and must have fs_info::balance_ctl properly
	 * set up.
	 */
	अगर (!btrfs_exclop_start(fs_info, BTRFS_EXCLOP_BALANCE))
		btrfs_warn(fs_info,
	"balance: cannot set exclusive op status, resume manually");

	btrfs_release_path(path);

	mutex_lock(&fs_info->balance_mutex);
	BUG_ON(fs_info->balance_ctl);
	spin_lock(&fs_info->balance_lock);
	fs_info->balance_ctl = bctl;
	spin_unlock(&fs_info->balance_lock);
	mutex_unlock(&fs_info->balance_mutex);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_छोड़ो_balance(काष्ठा btrfs_fs_info *fs_info)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&fs_info->balance_mutex);
	अगर (!fs_info->balance_ctl) अणु
		mutex_unlock(&fs_info->balance_mutex);
		वापस -ENOTCONN;
	पूर्ण

	अगर (test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags)) अणु
		atomic_inc(&fs_info->balance_छोड़ो_req);
		mutex_unlock(&fs_info->balance_mutex);

		रुको_event(fs_info->balance_रुको_q,
			   !test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags));

		mutex_lock(&fs_info->balance_mutex);
		/* we are good with balance_ctl ripped off from under us */
		BUG_ON(test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags));
		atomic_dec(&fs_info->balance_छोड़ो_req);
	पूर्ण अन्यथा अणु
		ret = -ENOTCONN;
	पूर्ण

	mutex_unlock(&fs_info->balance_mutex);
	वापस ret;
पूर्ण

पूर्णांक btrfs_cancel_balance(काष्ठा btrfs_fs_info *fs_info)
अणु
	mutex_lock(&fs_info->balance_mutex);
	अगर (!fs_info->balance_ctl) अणु
		mutex_unlock(&fs_info->balance_mutex);
		वापस -ENOTCONN;
	पूर्ण

	/*
	 * A छोड़ोd balance with the item stored on disk can be resumed at
	 * mount समय अगर the mount is पढ़ो-ग_लिखो. Otherwise it's still छोड़ोd
	 * and we must not allow cancelling as it deletes the item.
	 */
	अगर (sb_rकरोnly(fs_info->sb)) अणु
		mutex_unlock(&fs_info->balance_mutex);
		वापस -EROFS;
	पूर्ण

	atomic_inc(&fs_info->balance_cancel_req);
	/*
	 * अगर we are running just रुको and वापस, balance item is
	 * deleted in btrfs_balance in this हाल
	 */
	अगर (test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags)) अणु
		mutex_unlock(&fs_info->balance_mutex);
		रुको_event(fs_info->balance_रुको_q,
			   !test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags));
		mutex_lock(&fs_info->balance_mutex);
	पूर्ण अन्यथा अणु
		mutex_unlock(&fs_info->balance_mutex);
		/*
		 * Lock released to allow other रुकोers to जारी, we'll
		 * reexamine the status again.
		 */
		mutex_lock(&fs_info->balance_mutex);

		अगर (fs_info->balance_ctl) अणु
			reset_balance_state(fs_info);
			btrfs_exclop_finish(fs_info);
			btrfs_info(fs_info, "balance: canceled");
		पूर्ण
	पूर्ण

	BUG_ON(fs_info->balance_ctl ||
		test_bit(BTRFS_FS_BALANCE_RUNNING, &fs_info->flags));
	atomic_dec(&fs_info->balance_cancel_req);
	mutex_unlock(&fs_info->balance_mutex);
	वापस 0;
पूर्ण

पूर्णांक btrfs_uuid_scan_kthपढ़ो(व्योम *data)
अणु
	काष्ठा btrfs_fs_info *fs_info = data;
	काष्ठा btrfs_root *root = fs_info->tree_root;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_path *path = शून्य;
	पूर्णांक ret = 0;
	काष्ठा extent_buffer *eb;
	पूर्णांक slot;
	काष्ठा btrfs_root_item root_item;
	u32 item_size;
	काष्ठा btrfs_trans_handle *trans = शून्य;
	bool closing = false;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	key.objectid = 0;
	key.type = BTRFS_ROOT_ITEM_KEY;
	key.offset = 0;

	जबतक (1) अणु
		अगर (btrfs_fs_closing(fs_info)) अणु
			closing = true;
			अवरोध;
		पूर्ण
		ret = btrfs_search_क्रमward(root, &key, path,
				BTRFS_OLDEST_GENERATION);
		अगर (ret) अणु
			अगर (ret > 0)
				ret = 0;
			अवरोध;
		पूर्ण

		अगर (key.type != BTRFS_ROOT_ITEM_KEY ||
		    (key.objectid < BTRFS_FIRST_FREE_OBJECTID &&
		     key.objectid != BTRFS_FS_TREE_OBJECTID) ||
		    key.objectid > BTRFS_LAST_FREE_OBJECTID)
			जाओ skip;

		eb = path->nodes[0];
		slot = path->slots[0];
		item_size = btrfs_item_size_nr(eb, slot);
		अगर (item_size < माप(root_item))
			जाओ skip;

		पढ़ो_extent_buffer(eb, &root_item,
				   btrfs_item_ptr_offset(eb, slot),
				   (पूर्णांक)माप(root_item));
		अगर (btrfs_root_refs(&root_item) == 0)
			जाओ skip;

		अगर (!btrfs_is_empty_uuid(root_item.uuid) ||
		    !btrfs_is_empty_uuid(root_item.received_uuid)) अणु
			अगर (trans)
				जाओ update_tree;

			btrfs_release_path(path);
			/*
			 * 1 - subvol uuid item
			 * 1 - received_subvol uuid item
			 */
			trans = btrfs_start_transaction(fs_info->uuid_root, 2);
			अगर (IS_ERR(trans)) अणु
				ret = PTR_ERR(trans);
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण अन्यथा अणु
			जाओ skip;
		पूर्ण
update_tree:
		btrfs_release_path(path);
		अगर (!btrfs_is_empty_uuid(root_item.uuid)) अणु
			ret = btrfs_uuid_tree_add(trans, root_item.uuid,
						  BTRFS_UUID_KEY_SUBVOL,
						  key.objectid);
			अगर (ret < 0) अणु
				btrfs_warn(fs_info, "uuid_tree_add failed %d",
					ret);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!btrfs_is_empty_uuid(root_item.received_uuid)) अणु
			ret = btrfs_uuid_tree_add(trans,
						  root_item.received_uuid,
						 BTRFS_UUID_KEY_RECEIVED_SUBVOL,
						  key.objectid);
			अगर (ret < 0) अणु
				btrfs_warn(fs_info, "uuid_tree_add failed %d",
					ret);
				अवरोध;
			पूर्ण
		पूर्ण

skip:
		btrfs_release_path(path);
		अगर (trans) अणु
			ret = btrfs_end_transaction(trans);
			trans = शून्य;
			अगर (ret)
				अवरोध;
		पूर्ण

		अगर (key.offset < (u64)-1) अणु
			key.offset++;
		पूर्ण अन्यथा अगर (key.type < BTRFS_ROOT_ITEM_KEY) अणु
			key.offset = 0;
			key.type = BTRFS_ROOT_ITEM_KEY;
		पूर्ण अन्यथा अगर (key.objectid < (u64)-1) अणु
			key.offset = 0;
			key.type = BTRFS_ROOT_ITEM_KEY;
			key.objectid++;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
		cond_resched();
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	अगर (trans && !IS_ERR(trans))
		btrfs_end_transaction(trans);
	अगर (ret)
		btrfs_warn(fs_info, "btrfs_uuid_scan_kthread failed %d", ret);
	अन्यथा अगर (!closing)
		set_bit(BTRFS_FS_UPDATE_UUID_TREE_GEN, &fs_info->flags);
	up(&fs_info->uuid_tree_rescan_sem);
	वापस 0;
पूर्ण

पूर्णांक btrfs_create_uuid_tree(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *tree_root = fs_info->tree_root;
	काष्ठा btrfs_root *uuid_root;
	काष्ठा task_काष्ठा *task;
	पूर्णांक ret;

	/*
	 * 1 - root node
	 * 1 - root item
	 */
	trans = btrfs_start_transaction(tree_root, 2);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);

	uuid_root = btrfs_create_tree(trans, BTRFS_UUID_TREE_OBJECTID);
	अगर (IS_ERR(uuid_root)) अणु
		ret = PTR_ERR(uuid_root);
		btrfs_पात_transaction(trans, ret);
		btrfs_end_transaction(trans);
		वापस ret;
	पूर्ण

	fs_info->uuid_root = uuid_root;

	ret = btrfs_commit_transaction(trans);
	अगर (ret)
		वापस ret;

	करोwn(&fs_info->uuid_tree_rescan_sem);
	task = kthपढ़ो_run(btrfs_uuid_scan_kthपढ़ो, fs_info, "btrfs-uuid");
	अगर (IS_ERR(task)) अणु
		/* fs_info->update_uuid_tree_gen reमुख्यs 0 in all error हाल */
		btrfs_warn(fs_info, "failed to start uuid_scan task");
		up(&fs_info->uuid_tree_rescan_sem);
		वापस PTR_ERR(task);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * shrinking a device means finding all of the device extents past
 * the new size, and then following the back refs to the chunks.
 * The chunk relocation code actually मुक्तs the device extent
 */
पूर्णांक btrfs_shrink_device(काष्ठा btrfs_device *device, u64 new_size)
अणु
	काष्ठा btrfs_fs_info *fs_info = device->fs_info;
	काष्ठा btrfs_root *root = fs_info->dev_root;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_dev_extent *dev_extent = शून्य;
	काष्ठा btrfs_path *path;
	u64 length;
	u64 chunk_offset;
	पूर्णांक ret;
	पूर्णांक slot;
	पूर्णांक failed = 0;
	bool retried = false;
	काष्ठा extent_buffer *l;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_super_block *super_copy = fs_info->super_copy;
	u64 old_total = btrfs_super_total_bytes(super_copy);
	u64 old_size = btrfs_device_get_total_bytes(device);
	u64 dअगरf;
	u64 start;

	new_size = round_करोwn(new_size, fs_info->sectorsize);
	start = new_size;
	dअगरf = round_करोwn(old_size - new_size, fs_info->sectorsize);

	अगर (test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state))
		वापस -EINVAL;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	path->पढ़ोa = READA_BACK;

	trans = btrfs_start_transaction(root, 0);
	अगर (IS_ERR(trans)) अणु
		btrfs_मुक्त_path(path);
		वापस PTR_ERR(trans);
	पूर्ण

	mutex_lock(&fs_info->chunk_mutex);

	btrfs_device_set_total_bytes(device, new_size);
	अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state)) अणु
		device->fs_devices->total_rw_bytes -= dअगरf;
		atomic64_sub(dअगरf, &fs_info->मुक्त_chunk_space);
	पूर्ण

	/*
	 * Once the device's size has been set to the new size, ensure all
	 * in-memory chunks are synced to disk so that the loop below sees them
	 * and relocates them accordingly.
	 */
	अगर (contains_pending_extent(device, &start, dअगरf)) अणु
		mutex_unlock(&fs_info->chunk_mutex);
		ret = btrfs_commit_transaction(trans);
		अगर (ret)
			जाओ करोne;
	पूर्ण अन्यथा अणु
		mutex_unlock(&fs_info->chunk_mutex);
		btrfs_end_transaction(trans);
	पूर्ण

again:
	key.objectid = device->devid;
	key.offset = (u64)-1;
	key.type = BTRFS_DEV_EXTENT_KEY;

	करो अणु
		mutex_lock(&fs_info->reclaim_bgs_lock);
		ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
		अगर (ret < 0) अणु
			mutex_unlock(&fs_info->reclaim_bgs_lock);
			जाओ करोne;
		पूर्ण

		ret = btrfs_previous_item(root, path, 0, key.type);
		अगर (ret) अणु
			mutex_unlock(&fs_info->reclaim_bgs_lock);
			अगर (ret < 0)
				जाओ करोne;
			ret = 0;
			btrfs_release_path(path);
			अवरोध;
		पूर्ण

		l = path->nodes[0];
		slot = path->slots[0];
		btrfs_item_key_to_cpu(l, &key, path->slots[0]);

		अगर (key.objectid != device->devid) अणु
			mutex_unlock(&fs_info->reclaim_bgs_lock);
			btrfs_release_path(path);
			अवरोध;
		पूर्ण

		dev_extent = btrfs_item_ptr(l, slot, काष्ठा btrfs_dev_extent);
		length = btrfs_dev_extent_length(l, dev_extent);

		अगर (key.offset + length <= new_size) अणु
			mutex_unlock(&fs_info->reclaim_bgs_lock);
			btrfs_release_path(path);
			अवरोध;
		पूर्ण

		chunk_offset = btrfs_dev_extent_chunk_offset(l, dev_extent);
		btrfs_release_path(path);

		/*
		 * We may be relocating the only data chunk we have,
		 * which could potentially end up with losing data's
		 * raid profile, so lets allocate an empty one in
		 * advance.
		 */
		ret = btrfs_may_alloc_data_chunk(fs_info, chunk_offset);
		अगर (ret < 0) अणु
			mutex_unlock(&fs_info->reclaim_bgs_lock);
			जाओ करोne;
		पूर्ण

		ret = btrfs_relocate_chunk(fs_info, chunk_offset);
		mutex_unlock(&fs_info->reclaim_bgs_lock);
		अगर (ret == -ENOSPC) अणु
			failed++;
		पूर्ण अन्यथा अगर (ret) अणु
			अगर (ret == -ETXTBSY) अणु
				btrfs_warn(fs_info,
		   "could not shrink block group %llu due to active swapfile",
					   chunk_offset);
			पूर्ण
			जाओ करोne;
		पूर्ण
	पूर्ण जबतक (key.offset-- > 0);

	अगर (failed && !retried) अणु
		failed = 0;
		retried = true;
		जाओ again;
	पूर्ण अन्यथा अगर (failed && retried) अणु
		ret = -ENOSPC;
		जाओ करोne;
	पूर्ण

	/* Shrinking succeeded, अन्यथा we would be at "done". */
	trans = btrfs_start_transaction(root, 0);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ करोne;
	पूर्ण

	mutex_lock(&fs_info->chunk_mutex);
	/* Clear all state bits beyond the shrunk device size */
	clear_extent_bits(&device->alloc_state, new_size, (u64)-1,
			  CHUNK_STATE_MASK);

	btrfs_device_set_disk_total_bytes(device, new_size);
	अगर (list_empty(&device->post_commit_list))
		list_add_tail(&device->post_commit_list,
			      &trans->transaction->dev_update_list);

	WARN_ON(dअगरf > old_total);
	btrfs_set_super_total_bytes(super_copy,
			round_करोwn(old_total - dअगरf, fs_info->sectorsize));
	mutex_unlock(&fs_info->chunk_mutex);

	/* Now btrfs_update_device() will change the on-disk size. */
	ret = btrfs_update_device(trans, device);
	अगर (ret < 0) अणु
		btrfs_पात_transaction(trans, ret);
		btrfs_end_transaction(trans);
	पूर्ण अन्यथा अणु
		ret = btrfs_commit_transaction(trans);
	पूर्ण
करोne:
	btrfs_मुक्त_path(path);
	अगर (ret) अणु
		mutex_lock(&fs_info->chunk_mutex);
		btrfs_device_set_total_bytes(device, old_size);
		अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state))
			device->fs_devices->total_rw_bytes += dअगरf;
		atomic64_add(dअगरf, &fs_info->मुक्त_chunk_space);
		mutex_unlock(&fs_info->chunk_mutex);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक btrfs_add_प्रणाली_chunk(काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_key *key,
			   काष्ठा btrfs_chunk *chunk, पूर्णांक item_size)
अणु
	काष्ठा btrfs_super_block *super_copy = fs_info->super_copy;
	काष्ठा btrfs_disk_key disk_key;
	u32 array_size;
	u8 *ptr;

	mutex_lock(&fs_info->chunk_mutex);
	array_size = btrfs_super_sys_array_size(super_copy);
	अगर (array_size + item_size + माप(disk_key)
			> BTRFS_SYSTEM_CHUNK_ARRAY_SIZE) अणु
		mutex_unlock(&fs_info->chunk_mutex);
		वापस -EFBIG;
	पूर्ण

	ptr = super_copy->sys_chunk_array + array_size;
	btrfs_cpu_key_to_disk(&disk_key, key);
	स_नकल(ptr, &disk_key, माप(disk_key));
	ptr += माप(disk_key);
	स_नकल(ptr, chunk, item_size);
	item_size += माप(disk_key);
	btrfs_set_super_sys_array_size(super_copy, array_size + item_size);
	mutex_unlock(&fs_info->chunk_mutex);

	वापस 0;
पूर्ण

/*
 * sort the devices in descending order by max_avail, total_avail
 */
अटल पूर्णांक btrfs_cmp_device_info(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा btrfs_device_info *di_a = a;
	स्थिर काष्ठा btrfs_device_info *di_b = b;

	अगर (di_a->max_avail > di_b->max_avail)
		वापस -1;
	अगर (di_a->max_avail < di_b->max_avail)
		वापस 1;
	अगर (di_a->total_avail > di_b->total_avail)
		वापस -1;
	अगर (di_a->total_avail < di_b->total_avail)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम check_raid56_incompat_flag(काष्ठा btrfs_fs_info *info, u64 type)
अणु
	अगर (!(type & BTRFS_BLOCK_GROUP_RAID56_MASK))
		वापस;

	btrfs_set_fs_incompat(info, RAID56);
पूर्ण

अटल व्योम check_raid1c34_incompat_flag(काष्ठा btrfs_fs_info *info, u64 type)
अणु
	अगर (!(type & (BTRFS_BLOCK_GROUP_RAID1C3 | BTRFS_BLOCK_GROUP_RAID1C4)))
		वापस;

	btrfs_set_fs_incompat(info, RAID1C34);
पूर्ण

/*
 * Structure used पूर्णांकernally क्रम __btrfs_alloc_chunk() function.
 * Wraps needed parameters.
 */
काष्ठा alloc_chunk_ctl अणु
	u64 start;
	u64 type;
	/* Total number of stripes to allocate */
	पूर्णांक num_stripes;
	/* sub_stripes info क्रम map */
	पूर्णांक sub_stripes;
	/* Stripes per device */
	पूर्णांक dev_stripes;
	/* Maximum number of devices to use */
	पूर्णांक devs_max;
	/* Minimum number of devices to use */
	पूर्णांक devs_min;
	/* ndevs has to be a multiple of this */
	पूर्णांक devs_increment;
	/* Number of copies */
	पूर्णांक ncopies;
	/* Number of stripes worth of bytes to store parity inक्रमmation */
	पूर्णांक nparity;
	u64 max_stripe_size;
	u64 max_chunk_size;
	u64 dev_extent_min;
	u64 stripe_size;
	u64 chunk_size;
	पूर्णांक ndevs;
पूर्ण;

अटल व्योम init_alloc_chunk_ctl_policy_regular(
				काष्ठा btrfs_fs_devices *fs_devices,
				काष्ठा alloc_chunk_ctl *ctl)
अणु
	u64 type = ctl->type;

	अगर (type & BTRFS_BLOCK_GROUP_DATA) अणु
		ctl->max_stripe_size = SZ_1G;
		ctl->max_chunk_size = BTRFS_MAX_DATA_CHUNK_SIZE;
	पूर्ण अन्यथा अगर (type & BTRFS_BLOCK_GROUP_METADATA) अणु
		/* For larger fileप्रणालीs, use larger metadata chunks */
		अगर (fs_devices->total_rw_bytes > 50ULL * SZ_1G)
			ctl->max_stripe_size = SZ_1G;
		अन्यथा
			ctl->max_stripe_size = SZ_256M;
		ctl->max_chunk_size = ctl->max_stripe_size;
	पूर्ण अन्यथा अगर (type & BTRFS_BLOCK_GROUP_SYSTEM) अणु
		ctl->max_stripe_size = SZ_32M;
		ctl->max_chunk_size = 2 * ctl->max_stripe_size;
		ctl->devs_max = min_t(पूर्णांक, ctl->devs_max,
				      BTRFS_MAX_DEVS_SYS_CHUNK);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	/* We करोn't want a chunk larger than 10% of writable space */
	ctl->max_chunk_size = min(भाग_factor(fs_devices->total_rw_bytes, 1),
				  ctl->max_chunk_size);
	ctl->dev_extent_min = BTRFS_STRIPE_LEN * ctl->dev_stripes;
पूर्ण

अटल व्योम init_alloc_chunk_ctl_policy_zoned(
				      काष्ठा btrfs_fs_devices *fs_devices,
				      काष्ठा alloc_chunk_ctl *ctl)
अणु
	u64 zone_size = fs_devices->fs_info->zone_size;
	u64 limit;
	पूर्णांक min_num_stripes = ctl->devs_min * ctl->dev_stripes;
	पूर्णांक min_data_stripes = (min_num_stripes - ctl->nparity) / ctl->ncopies;
	u64 min_chunk_size = min_data_stripes * zone_size;
	u64 type = ctl->type;

	ctl->max_stripe_size = zone_size;
	अगर (type & BTRFS_BLOCK_GROUP_DATA) अणु
		ctl->max_chunk_size = round_करोwn(BTRFS_MAX_DATA_CHUNK_SIZE,
						 zone_size);
	पूर्ण अन्यथा अगर (type & BTRFS_BLOCK_GROUP_METADATA) अणु
		ctl->max_chunk_size = ctl->max_stripe_size;
	पूर्ण अन्यथा अगर (type & BTRFS_BLOCK_GROUP_SYSTEM) अणु
		ctl->max_chunk_size = 2 * ctl->max_stripe_size;
		ctl->devs_max = min_t(पूर्णांक, ctl->devs_max,
				      BTRFS_MAX_DEVS_SYS_CHUNK);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	/* We करोn't want a chunk larger than 10% of writable space */
	limit = max(round_करोwn(भाग_factor(fs_devices->total_rw_bytes, 1),
			       zone_size),
		    min_chunk_size);
	ctl->max_chunk_size = min(limit, ctl->max_chunk_size);
	ctl->dev_extent_min = zone_size * ctl->dev_stripes;
पूर्ण

अटल व्योम init_alloc_chunk_ctl(काष्ठा btrfs_fs_devices *fs_devices,
				 काष्ठा alloc_chunk_ctl *ctl)
अणु
	पूर्णांक index = btrfs_bg_flags_to_raid_index(ctl->type);

	ctl->sub_stripes = btrfs_raid_array[index].sub_stripes;
	ctl->dev_stripes = btrfs_raid_array[index].dev_stripes;
	ctl->devs_max = btrfs_raid_array[index].devs_max;
	अगर (!ctl->devs_max)
		ctl->devs_max = BTRFS_MAX_DEVS(fs_devices->fs_info);
	ctl->devs_min = btrfs_raid_array[index].devs_min;
	ctl->devs_increment = btrfs_raid_array[index].devs_increment;
	ctl->ncopies = btrfs_raid_array[index].ncopies;
	ctl->nparity = btrfs_raid_array[index].nparity;
	ctl->ndevs = 0;

	चयन (fs_devices->chunk_alloc_policy) अणु
	हाल BTRFS_CHUNK_ALLOC_REGULAR:
		init_alloc_chunk_ctl_policy_regular(fs_devices, ctl);
		अवरोध;
	हाल BTRFS_CHUNK_ALLOC_ZONED:
		init_alloc_chunk_ctl_policy_zoned(fs_devices, ctl);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक gather_device_info(काष्ठा btrfs_fs_devices *fs_devices,
			      काष्ठा alloc_chunk_ctl *ctl,
			      काष्ठा btrfs_device_info *devices_info)
अणु
	काष्ठा btrfs_fs_info *info = fs_devices->fs_info;
	काष्ठा btrfs_device *device;
	u64 total_avail;
	u64 dev_extent_want = ctl->max_stripe_size * ctl->dev_stripes;
	पूर्णांक ret;
	पूर्णांक ndevs = 0;
	u64 max_avail;
	u64 dev_offset;

	/*
	 * in the first pass through the devices list, we gather inक्रमmation
	 * about the available holes on each device.
	 */
	list_क्रम_each_entry(device, &fs_devices->alloc_list, dev_alloc_list) अणु
		अगर (!test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state)) अणु
			WARN(1, KERN_ERR
			       "BTRFS: read-only device in alloc_list\n");
			जारी;
		पूर्ण

		अगर (!test_bit(BTRFS_DEV_STATE_IN_FS_METADATA,
					&device->dev_state) ||
		    test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state))
			जारी;

		अगर (device->total_bytes > device->bytes_used)
			total_avail = device->total_bytes - device->bytes_used;
		अन्यथा
			total_avail = 0;

		/* If there is no space on this device, skip it. */
		अगर (total_avail < ctl->dev_extent_min)
			जारी;

		ret = find_मुक्त_dev_extent(device, dev_extent_want, &dev_offset,
					   &max_avail);
		अगर (ret && ret != -ENOSPC)
			वापस ret;

		अगर (ret == 0)
			max_avail = dev_extent_want;

		अगर (max_avail < ctl->dev_extent_min) अणु
			अगर (btrfs_test_opt(info, ENOSPC_DEBUG))
				btrfs_debug(info,
			"%s: devid %llu has no free space, have=%llu want=%llu",
					    __func__, device->devid, max_avail,
					    ctl->dev_extent_min);
			जारी;
		पूर्ण

		अगर (ndevs == fs_devices->rw_devices) अणु
			WARN(1, "%s: found more than %llu devices\n",
			     __func__, fs_devices->rw_devices);
			अवरोध;
		पूर्ण
		devices_info[ndevs].dev_offset = dev_offset;
		devices_info[ndevs].max_avail = max_avail;
		devices_info[ndevs].total_avail = total_avail;
		devices_info[ndevs].dev = device;
		++ndevs;
	पूर्ण
	ctl->ndevs = ndevs;

	/*
	 * now sort the devices by hole size / available space
	 */
	sort(devices_info, ndevs, माप(काष्ठा btrfs_device_info),
	     btrfs_cmp_device_info, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक decide_stripe_size_regular(काष्ठा alloc_chunk_ctl *ctl,
				      काष्ठा btrfs_device_info *devices_info)
अणु
	/* Number of stripes that count क्रम block group size */
	पूर्णांक data_stripes;

	/*
	 * The primary goal is to maximize the number of stripes, so use as
	 * many devices as possible, even अगर the stripes are not maximum sized.
	 *
	 * The DUP profile stores more than one stripe per device, the
	 * max_avail is the total size so we have to adjust.
	 */
	ctl->stripe_size = भाग_u64(devices_info[ctl->ndevs - 1].max_avail,
				   ctl->dev_stripes);
	ctl->num_stripes = ctl->ndevs * ctl->dev_stripes;

	/* This will have to be fixed क्रम RAID1 and RAID10 over more drives */
	data_stripes = (ctl->num_stripes - ctl->nparity) / ctl->ncopies;

	/*
	 * Use the number of data stripes to figure out how big this chunk is
	 * really going to be in terms of logical address space, and compare
	 * that answer with the max chunk size. If it's higher, we try to
	 * reduce stripe_size.
	 */
	अगर (ctl->stripe_size * data_stripes > ctl->max_chunk_size) अणु
		/*
		 * Reduce stripe_size, round it up to a 16MB boundary again and
		 * then use it, unless it ends up being even bigger than the
		 * previous value we had alपढ़ोy.
		 */
		ctl->stripe_size = min(round_up(भाग_u64(ctl->max_chunk_size,
							data_stripes), SZ_16M),
				       ctl->stripe_size);
	पूर्ण

	/* Align to BTRFS_STRIPE_LEN */
	ctl->stripe_size = round_करोwn(ctl->stripe_size, BTRFS_STRIPE_LEN);
	ctl->chunk_size = ctl->stripe_size * data_stripes;

	वापस 0;
पूर्ण

अटल पूर्णांक decide_stripe_size_zoned(काष्ठा alloc_chunk_ctl *ctl,
				    काष्ठा btrfs_device_info *devices_info)
अणु
	u64 zone_size = devices_info[0].dev->zone_info->zone_size;
	/* Number of stripes that count क्रम block group size */
	पूर्णांक data_stripes;

	/*
	 * It should hold because:
	 *    dev_extent_min == dev_extent_want == zone_size * dev_stripes
	 */
	ASSERT(devices_info[ctl->ndevs - 1].max_avail == ctl->dev_extent_min);

	ctl->stripe_size = zone_size;
	ctl->num_stripes = ctl->ndevs * ctl->dev_stripes;
	data_stripes = (ctl->num_stripes - ctl->nparity) / ctl->ncopies;

	/* stripe_size is fixed in zoned filesysmte. Reduce ndevs instead. */
	अगर (ctl->stripe_size * data_stripes > ctl->max_chunk_size) अणु
		ctl->ndevs = भाग_u64(भाग_u64(ctl->max_chunk_size * ctl->ncopies,
					     ctl->stripe_size) + ctl->nparity,
				     ctl->dev_stripes);
		ctl->num_stripes = ctl->ndevs * ctl->dev_stripes;
		data_stripes = (ctl->num_stripes - ctl->nparity) / ctl->ncopies;
		ASSERT(ctl->stripe_size * data_stripes <= ctl->max_chunk_size);
	पूर्ण

	ctl->chunk_size = ctl->stripe_size * data_stripes;

	वापस 0;
पूर्ण

अटल पूर्णांक decide_stripe_size(काष्ठा btrfs_fs_devices *fs_devices,
			      काष्ठा alloc_chunk_ctl *ctl,
			      काष्ठा btrfs_device_info *devices_info)
अणु
	काष्ठा btrfs_fs_info *info = fs_devices->fs_info;

	/*
	 * Round करोwn to number of usable stripes, devs_increment can be any
	 * number so we can't use round_करोwn() that requires घातer of 2, जबतक
	 * roundकरोwn is safe.
	 */
	ctl->ndevs = roundकरोwn(ctl->ndevs, ctl->devs_increment);

	अगर (ctl->ndevs < ctl->devs_min) अणु
		अगर (btrfs_test_opt(info, ENOSPC_DEBUG)) अणु
			btrfs_debug(info,
	"%s: not enough devices with free space: have=%d minimum required=%d",
				    __func__, ctl->ndevs, ctl->devs_min);
		पूर्ण
		वापस -ENOSPC;
	पूर्ण

	ctl->ndevs = min(ctl->ndevs, ctl->devs_max);

	चयन (fs_devices->chunk_alloc_policy) अणु
	हाल BTRFS_CHUNK_ALLOC_REGULAR:
		वापस decide_stripe_size_regular(ctl, devices_info);
	हाल BTRFS_CHUNK_ALLOC_ZONED:
		वापस decide_stripe_size_zoned(ctl, devices_info);
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक create_chunk(काष्ठा btrfs_trans_handle *trans,
			काष्ठा alloc_chunk_ctl *ctl,
			काष्ठा btrfs_device_info *devices_info)
अणु
	काष्ठा btrfs_fs_info *info = trans->fs_info;
	काष्ठा map_lookup *map = शून्य;
	काष्ठा extent_map_tree *em_tree;
	काष्ठा extent_map *em;
	u64 start = ctl->start;
	u64 type = ctl->type;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक j;

	map = kदो_स्मृति(map_lookup_size(ctl->num_stripes), GFP_NOFS);
	अगर (!map)
		वापस -ENOMEM;
	map->num_stripes = ctl->num_stripes;

	क्रम (i = 0; i < ctl->ndevs; ++i) अणु
		क्रम (j = 0; j < ctl->dev_stripes; ++j) अणु
			पूर्णांक s = i * ctl->dev_stripes + j;
			map->stripes[s].dev = devices_info[i].dev;
			map->stripes[s].physical = devices_info[i].dev_offset +
						   j * ctl->stripe_size;
		पूर्ण
	पूर्ण
	map->stripe_len = BTRFS_STRIPE_LEN;
	map->io_align = BTRFS_STRIPE_LEN;
	map->io_width = BTRFS_STRIPE_LEN;
	map->type = type;
	map->sub_stripes = ctl->sub_stripes;

	trace_btrfs_chunk_alloc(info, map, start, ctl->chunk_size);

	em = alloc_extent_map();
	अगर (!em) अणु
		kमुक्त(map);
		वापस -ENOMEM;
	पूर्ण
	set_bit(EXTENT_FLAG_FS_MAPPING, &em->flags);
	em->map_lookup = map;
	em->start = start;
	em->len = ctl->chunk_size;
	em->block_start = 0;
	em->block_len = em->len;
	em->orig_block_len = ctl->stripe_size;

	em_tree = &info->mapping_tree;
	ग_लिखो_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em, 0);
	अगर (ret) अणु
		ग_लिखो_unlock(&em_tree->lock);
		मुक्त_extent_map(em);
		वापस ret;
	पूर्ण
	ग_लिखो_unlock(&em_tree->lock);

	ret = btrfs_make_block_group(trans, 0, type, start, ctl->chunk_size);
	अगर (ret)
		जाओ error_del_extent;

	क्रम (i = 0; i < map->num_stripes; i++) अणु
		काष्ठा btrfs_device *dev = map->stripes[i].dev;

		btrfs_device_set_bytes_used(dev,
					    dev->bytes_used + ctl->stripe_size);
		अगर (list_empty(&dev->post_commit_list))
			list_add_tail(&dev->post_commit_list,
				      &trans->transaction->dev_update_list);
	पूर्ण

	atomic64_sub(ctl->stripe_size * map->num_stripes,
		     &info->मुक्त_chunk_space);

	मुक्त_extent_map(em);
	check_raid56_incompat_flag(info, type);
	check_raid1c34_incompat_flag(info, type);

	वापस 0;

error_del_extent:
	ग_लिखो_lock(&em_tree->lock);
	हटाओ_extent_mapping(em_tree, em);
	ग_लिखो_unlock(&em_tree->lock);

	/* One क्रम our allocation */
	मुक्त_extent_map(em);
	/* One क्रम the tree reference */
	मुक्त_extent_map(em);

	वापस ret;
पूर्ण

पूर्णांक btrfs_alloc_chunk(काष्ठा btrfs_trans_handle *trans, u64 type)
अणु
	काष्ठा btrfs_fs_info *info = trans->fs_info;
	काष्ठा btrfs_fs_devices *fs_devices = info->fs_devices;
	काष्ठा btrfs_device_info *devices_info = शून्य;
	काष्ठा alloc_chunk_ctl ctl;
	पूर्णांक ret;

	lockdep_निश्चित_held(&info->chunk_mutex);

	अगर (!alloc_profile_is_valid(type, 0)) अणु
		ASSERT(0);
		वापस -EINVAL;
	पूर्ण

	अगर (list_empty(&fs_devices->alloc_list)) अणु
		अगर (btrfs_test_opt(info, ENOSPC_DEBUG))
			btrfs_debug(info, "%s: no writable device", __func__);
		वापस -ENOSPC;
	पूर्ण

	अगर (!(type & BTRFS_BLOCK_GROUP_TYPE_MASK)) अणु
		btrfs_err(info, "invalid chunk type 0x%llx requested", type);
		ASSERT(0);
		वापस -EINVAL;
	पूर्ण

	ctl.start = find_next_chunk(info);
	ctl.type = type;
	init_alloc_chunk_ctl(fs_devices, &ctl);

	devices_info = kसुस्मृति(fs_devices->rw_devices, माप(*devices_info),
			       GFP_NOFS);
	अगर (!devices_info)
		वापस -ENOMEM;

	ret = gather_device_info(fs_devices, &ctl, devices_info);
	अगर (ret < 0)
		जाओ out;

	ret = decide_stripe_size(fs_devices, &ctl, devices_info);
	अगर (ret < 0)
		जाओ out;

	ret = create_chunk(trans, &ctl, devices_info);

out:
	kमुक्त(devices_info);
	वापस ret;
पूर्ण

/*
 * Chunk allocation falls पूर्णांकo two parts. The first part करोes work
 * that makes the new allocated chunk usable, but करोes not करो any operation
 * that modअगरies the chunk tree. The second part करोes the work that
 * requires modअगरying the chunk tree. This भागision is important क्रम the
 * bootstrap process of adding storage to a seed btrfs.
 */
पूर्णांक btrfs_finish_chunk_alloc(काष्ठा btrfs_trans_handle *trans,
			     u64 chunk_offset, u64 chunk_size)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *extent_root = fs_info->extent_root;
	काष्ठा btrfs_root *chunk_root = fs_info->chunk_root;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_device *device;
	काष्ठा btrfs_chunk *chunk;
	काष्ठा btrfs_stripe *stripe;
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	माप_प्रकार item_size;
	u64 dev_offset;
	u64 stripe_size;
	पूर्णांक i = 0;
	पूर्णांक ret = 0;

	em = btrfs_get_chunk_map(fs_info, chunk_offset, chunk_size);
	अगर (IS_ERR(em))
		वापस PTR_ERR(em);

	map = em->map_lookup;
	item_size = btrfs_chunk_item_size(map->num_stripes);
	stripe_size = em->orig_block_len;

	chunk = kzalloc(item_size, GFP_NOFS);
	अगर (!chunk) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Take the device list mutex to prevent races with the final phase of
	 * a device replace operation that replaces the device object associated
	 * with the map's stripes, because the device object's id can change
	 * at any समय during that final phase of the device replace operation
	 * (dev-replace.c:btrfs_dev_replace_finishing()).
	 */
	mutex_lock(&fs_info->fs_devices->device_list_mutex);
	क्रम (i = 0; i < map->num_stripes; i++) अणु
		device = map->stripes[i].dev;
		dev_offset = map->stripes[i].physical;

		ret = btrfs_update_device(trans, device);
		अगर (ret)
			अवरोध;
		ret = btrfs_alloc_dev_extent(trans, device, chunk_offset,
					     dev_offset, stripe_size);
		अगर (ret)
			अवरोध;
	पूर्ण
	अगर (ret) अणु
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		जाओ out;
	पूर्ण

	stripe = &chunk->stripe;
	क्रम (i = 0; i < map->num_stripes; i++) अणु
		device = map->stripes[i].dev;
		dev_offset = map->stripes[i].physical;

		btrfs_set_stack_stripe_devid(stripe, device->devid);
		btrfs_set_stack_stripe_offset(stripe, dev_offset);
		स_नकल(stripe->dev_uuid, device->uuid, BTRFS_UUID_SIZE);
		stripe++;
	पूर्ण
	mutex_unlock(&fs_info->fs_devices->device_list_mutex);

	btrfs_set_stack_chunk_length(chunk, chunk_size);
	btrfs_set_stack_chunk_owner(chunk, extent_root->root_key.objectid);
	btrfs_set_stack_chunk_stripe_len(chunk, map->stripe_len);
	btrfs_set_stack_chunk_type(chunk, map->type);
	btrfs_set_stack_chunk_num_stripes(chunk, map->num_stripes);
	btrfs_set_stack_chunk_io_align(chunk, map->stripe_len);
	btrfs_set_stack_chunk_io_width(chunk, map->stripe_len);
	btrfs_set_stack_chunk_sector_size(chunk, fs_info->sectorsize);
	btrfs_set_stack_chunk_sub_stripes(chunk, map->sub_stripes);

	key.objectid = BTRFS_FIRST_CHUNK_TREE_OBJECTID;
	key.type = BTRFS_CHUNK_ITEM_KEY;
	key.offset = chunk_offset;

	ret = btrfs_insert_item(trans, chunk_root, &key, chunk, item_size);
	अगर (ret == 0 && map->type & BTRFS_BLOCK_GROUP_SYSTEM) अणु
		/*
		 * TODO: Cleanup of inserted chunk root in हाल of
		 * failure.
		 */
		ret = btrfs_add_प्रणाली_chunk(fs_info, &key, chunk, item_size);
	पूर्ण

out:
	kमुक्त(chunk);
	मुक्त_extent_map(em);
	वापस ret;
पूर्ण

अटल noअंतरभूत पूर्णांक init_first_rw_device(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	u64 alloc_profile;
	पूर्णांक ret;

	alloc_profile = btrfs_metadata_alloc_profile(fs_info);
	ret = btrfs_alloc_chunk(trans, alloc_profile);
	अगर (ret)
		वापस ret;

	alloc_profile = btrfs_प्रणाली_alloc_profile(fs_info);
	ret = btrfs_alloc_chunk(trans, alloc_profile);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_chunk_max_errors(काष्ठा map_lookup *map)
अणु
	स्थिर पूर्णांक index = btrfs_bg_flags_to_raid_index(map->type);

	वापस btrfs_raid_array[index].tolerated_failures;
पूर्ण

पूर्णांक btrfs_chunk_पढ़ोonly(काष्ठा btrfs_fs_info *fs_info, u64 chunk_offset)
अणु
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	पूर्णांक पढ़ोonly = 0;
	पूर्णांक miss_ndevs = 0;
	पूर्णांक i;

	em = btrfs_get_chunk_map(fs_info, chunk_offset, 1);
	अगर (IS_ERR(em))
		वापस 1;

	map = em->map_lookup;
	क्रम (i = 0; i < map->num_stripes; i++) अणु
		अगर (test_bit(BTRFS_DEV_STATE_MISSING,
					&map->stripes[i].dev->dev_state)) अणु
			miss_ndevs++;
			जारी;
		पूर्ण
		अगर (!test_bit(BTRFS_DEV_STATE_WRITEABLE,
					&map->stripes[i].dev->dev_state)) अणु
			पढ़ोonly = 1;
			जाओ end;
		पूर्ण
	पूर्ण

	/*
	 * If the number of missing devices is larger than max errors,
	 * we can not ग_लिखो the data पूर्णांकo that chunk successfully, so
	 * set it पढ़ोonly.
	 */
	अगर (miss_ndevs > btrfs_chunk_max_errors(map))
		पढ़ोonly = 1;
end:
	मुक्त_extent_map(em);
	वापस पढ़ोonly;
पूर्ण

व्योम btrfs_mapping_tree_मुक्त(काष्ठा extent_map_tree *tree)
अणु
	काष्ठा extent_map *em;

	जबतक (1) अणु
		ग_लिखो_lock(&tree->lock);
		em = lookup_extent_mapping(tree, 0, (u64)-1);
		अगर (em)
			हटाओ_extent_mapping(tree, em);
		ग_लिखो_unlock(&tree->lock);
		अगर (!em)
			अवरोध;
		/* once क्रम us */
		मुक्त_extent_map(em);
		/* once क्रम the tree */
		मुक्त_extent_map(em);
	पूर्ण
पूर्ण

पूर्णांक btrfs_num_copies(काष्ठा btrfs_fs_info *fs_info, u64 logical, u64 len)
अणु
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	पूर्णांक ret;

	em = btrfs_get_chunk_map(fs_info, logical, len);
	अगर (IS_ERR(em))
		/*
		 * We could वापस errors क्रम these हालs, but that could get
		 * ugly and we'd probably करो the same thing which is just not करो
		 * anything अन्यथा and निकास, so वापस 1 so the callers करोn't try
		 * to use other copies.
		 */
		वापस 1;

	map = em->map_lookup;
	अगर (map->type & (BTRFS_BLOCK_GROUP_DUP | BTRFS_BLOCK_GROUP_RAID1_MASK))
		ret = map->num_stripes;
	अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_RAID10)
		ret = map->sub_stripes;
	अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_RAID5)
		ret = 2;
	अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_RAID6)
		/*
		 * There could be two corrupted data stripes, we need
		 * to loop retry in order to rebuild the correct data.
		 *
		 * Fail a stripe at a समय on every retry except the
		 * stripe under reस्थिरruction.
		 */
		ret = map->num_stripes;
	अन्यथा
		ret = 1;
	मुक्त_extent_map(em);

	करोwn_पढ़ो(&fs_info->dev_replace.rwsem);
	अगर (btrfs_dev_replace_is_ongoing(&fs_info->dev_replace) &&
	    fs_info->dev_replace.tgtdev)
		ret++;
	up_पढ़ो(&fs_info->dev_replace.rwsem);

	वापस ret;
पूर्ण

अचिन्हित दीर्घ btrfs_full_stripe_len(काष्ठा btrfs_fs_info *fs_info,
				    u64 logical)
अणु
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	अचिन्हित दीर्घ len = fs_info->sectorsize;

	em = btrfs_get_chunk_map(fs_info, logical, len);

	अगर (!WARN_ON(IS_ERR(em))) अणु
		map = em->map_lookup;
		अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK)
			len = map->stripe_len * nr_data_stripes(map);
		मुक्त_extent_map(em);
	पूर्ण
	वापस len;
पूर्ण

पूर्णांक btrfs_is_parity_mirror(काष्ठा btrfs_fs_info *fs_info, u64 logical, u64 len)
अणु
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	पूर्णांक ret = 0;

	em = btrfs_get_chunk_map(fs_info, logical, len);

	अगर(!WARN_ON(IS_ERR(em))) अणु
		map = em->map_lookup;
		अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK)
			ret = 1;
		मुक्त_extent_map(em);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक find_live_mirror(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा map_lookup *map, पूर्णांक first,
			    पूर्णांक dev_replace_is_ongoing)
अणु
	पूर्णांक i;
	पूर्णांक num_stripes;
	पूर्णांक preferred_mirror;
	पूर्णांक tolerance;
	काष्ठा btrfs_device *srcdev;

	ASSERT((map->type &
		 (BTRFS_BLOCK_GROUP_RAID1_MASK | BTRFS_BLOCK_GROUP_RAID10)));

	अगर (map->type & BTRFS_BLOCK_GROUP_RAID10)
		num_stripes = map->sub_stripes;
	अन्यथा
		num_stripes = map->num_stripes;

	चयन (fs_info->fs_devices->पढ़ो_policy) अणु
	शेष:
		/* Shouldn't happen, just warn and use pid instead of failing */
		btrfs_warn_rl(fs_info,
			      "unknown read_policy type %u, reset to pid",
			      fs_info->fs_devices->पढ़ो_policy);
		fs_info->fs_devices->पढ़ो_policy = BTRFS_READ_POLICY_PID;
		fallthrough;
	हाल BTRFS_READ_POLICY_PID:
		preferred_mirror = first + (current->pid % num_stripes);
		अवरोध;
	पूर्ण

	अगर (dev_replace_is_ongoing &&
	    fs_info->dev_replace.cont_पढ़ोing_from_srcdev_mode ==
	     BTRFS_DEV_REPLACE_ITEM_CONT_READING_FROM_SRCDEV_MODE_AVOID)
		srcdev = fs_info->dev_replace.srcdev;
	अन्यथा
		srcdev = शून्य;

	/*
	 * try to aव्योम the drive that is the source drive क्रम a
	 * dev-replace procedure, only choose it अगर no other non-missing
	 * mirror is available
	 */
	क्रम (tolerance = 0; tolerance < 2; tolerance++) अणु
		अगर (map->stripes[preferred_mirror].dev->bdev &&
		    (tolerance || map->stripes[preferred_mirror].dev != srcdev))
			वापस preferred_mirror;
		क्रम (i = first; i < first + num_stripes; i++) अणु
			अगर (map->stripes[i].dev->bdev &&
			    (tolerance || map->stripes[i].dev != srcdev))
				वापस i;
		पूर्ण
	पूर्ण

	/* we couldn't find one that doesn't fail.  Just वापस something
	 * and the io error handling code will clean up eventually
	 */
	वापस preferred_mirror;
पूर्ण

/* Bubble-sort the stripe set to put the parity/syndrome stripes last */
अटल व्योम sort_parity_stripes(काष्ठा btrfs_bio *bbio, पूर्णांक num_stripes)
अणु
	पूर्णांक i;
	पूर्णांक again = 1;

	जबतक (again) अणु
		again = 0;
		क्रम (i = 0; i < num_stripes - 1; i++) अणु
			/* Swap अगर parity is on a smaller index */
			अगर (bbio->raid_map[i] > bbio->raid_map[i + 1]) अणु
				swap(bbio->stripes[i], bbio->stripes[i + 1]);
				swap(bbio->raid_map[i], bbio->raid_map[i + 1]);
				again = 1;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा btrfs_bio *alloc_btrfs_bio(पूर्णांक total_stripes, पूर्णांक real_stripes)
अणु
	काष्ठा btrfs_bio *bbio = kzalloc(
		 /* the size of the btrfs_bio */
		माप(काष्ठा btrfs_bio) +
		/* plus the variable array क्रम the stripes */
		माप(काष्ठा btrfs_bio_stripe) * (total_stripes) +
		/* plus the variable array क्रम the tgt dev */
		माप(पूर्णांक) * (real_stripes) +
		/*
		 * plus the raid_map, which includes both the tgt dev
		 * and the stripes
		 */
		माप(u64) * (total_stripes),
		GFP_NOFS|__GFP_NOFAIL);

	atomic_set(&bbio->error, 0);
	refcount_set(&bbio->refs, 1);

	bbio->tgtdev_map = (पूर्णांक *)(bbio->stripes + total_stripes);
	bbio->raid_map = (u64 *)(bbio->tgtdev_map + real_stripes);

	वापस bbio;
पूर्ण

व्योम btrfs_get_bbio(काष्ठा btrfs_bio *bbio)
अणु
	WARN_ON(!refcount_पढ़ो(&bbio->refs));
	refcount_inc(&bbio->refs);
पूर्ण

व्योम btrfs_put_bbio(काष्ठा btrfs_bio *bbio)
अणु
	अगर (!bbio)
		वापस;
	अगर (refcount_dec_and_test(&bbio->refs))
		kमुक्त(bbio);
पूर्ण

/* can REQ_OP_DISCARD be sent with other REQ like REQ_OP_WRITE? */
/*
 * Please note that, discard won't be sent to target device of device
 * replace.
 */
अटल पूर्णांक __btrfs_map_block_क्रम_discard(काष्ठा btrfs_fs_info *fs_info,
					 u64 logical, u64 *length_ret,
					 काष्ठा btrfs_bio **bbio_ret)
अणु
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	काष्ठा btrfs_bio *bbio;
	u64 length = *length_ret;
	u64 offset;
	u64 stripe_nr;
	u64 stripe_nr_end;
	u64 stripe_end_offset;
	u64 stripe_cnt;
	u64 stripe_len;
	u64 stripe_offset;
	u64 num_stripes;
	u32 stripe_index;
	u32 factor = 0;
	u32 sub_stripes = 0;
	u64 stripes_per_dev = 0;
	u32 reमुख्यing_stripes = 0;
	u32 last_stripe = 0;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* discard always वापस a bbio */
	ASSERT(bbio_ret);

	em = btrfs_get_chunk_map(fs_info, logical, length);
	अगर (IS_ERR(em))
		वापस PTR_ERR(em);

	map = em->map_lookup;
	/* we करोn't discard raid56 yet */
	अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	offset = logical - em->start;
	length = min_t(u64, em->start + em->len - logical, length);
	*length_ret = length;

	stripe_len = map->stripe_len;
	/*
	 * stripe_nr counts the total number of stripes we have to stride
	 * to get to this block
	 */
	stripe_nr = भाग64_u64(offset, stripe_len);

	/* stripe_offset is the offset of this block in its stripe */
	stripe_offset = offset - stripe_nr * stripe_len;

	stripe_nr_end = round_up(offset + length, map->stripe_len);
	stripe_nr_end = भाग64_u64(stripe_nr_end, map->stripe_len);
	stripe_cnt = stripe_nr_end - stripe_nr;
	stripe_end_offset = stripe_nr_end * map->stripe_len -
			    (offset + length);
	/*
	 * after this, stripe_nr is the number of stripes on this
	 * device we have to walk to find the data, and stripe_index is
	 * the number of our device in the stripe array
	 */
	num_stripes = 1;
	stripe_index = 0;
	अगर (map->type & (BTRFS_BLOCK_GROUP_RAID0 |
			 BTRFS_BLOCK_GROUP_RAID10)) अणु
		अगर (map->type & BTRFS_BLOCK_GROUP_RAID0)
			sub_stripes = 1;
		अन्यथा
			sub_stripes = map->sub_stripes;

		factor = map->num_stripes / sub_stripes;
		num_stripes = min_t(u64, map->num_stripes,
				    sub_stripes * stripe_cnt);
		stripe_nr = भाग_u64_rem(stripe_nr, factor, &stripe_index);
		stripe_index *= sub_stripes;
		stripes_per_dev = भाग_u64_rem(stripe_cnt, factor,
					      &reमुख्यing_stripes);
		भाग_u64_rem(stripe_nr_end - 1, factor, &last_stripe);
		last_stripe *= sub_stripes;
	पूर्ण अन्यथा अगर (map->type & (BTRFS_BLOCK_GROUP_RAID1_MASK |
				BTRFS_BLOCK_GROUP_DUP)) अणु
		num_stripes = map->num_stripes;
	पूर्ण अन्यथा अणु
		stripe_nr = भाग_u64_rem(stripe_nr, map->num_stripes,
					&stripe_index);
	पूर्ण

	bbio = alloc_btrfs_bio(num_stripes, 0);
	अगर (!bbio) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_stripes; i++) अणु
		bbio->stripes[i].physical =
			map->stripes[stripe_index].physical +
			stripe_offset + stripe_nr * map->stripe_len;
		bbio->stripes[i].dev = map->stripes[stripe_index].dev;

		अगर (map->type & (BTRFS_BLOCK_GROUP_RAID0 |
				 BTRFS_BLOCK_GROUP_RAID10)) अणु
			bbio->stripes[i].length = stripes_per_dev *
				map->stripe_len;

			अगर (i / sub_stripes < reमुख्यing_stripes)
				bbio->stripes[i].length +=
					map->stripe_len;

			/*
			 * Special क्रम the first stripe and
			 * the last stripe:
			 *
			 * |-------|...|-------|
			 *     |----------|
			 *    off     end_off
			 */
			अगर (i < sub_stripes)
				bbio->stripes[i].length -=
					stripe_offset;

			अगर (stripe_index >= last_stripe &&
			    stripe_index <= (last_stripe +
					     sub_stripes - 1))
				bbio->stripes[i].length -=
					stripe_end_offset;

			अगर (i == sub_stripes - 1)
				stripe_offset = 0;
		पूर्ण अन्यथा अणु
			bbio->stripes[i].length = length;
		पूर्ण

		stripe_index++;
		अगर (stripe_index == map->num_stripes) अणु
			stripe_index = 0;
			stripe_nr++;
		पूर्ण
	पूर्ण

	*bbio_ret = bbio;
	bbio->map_type = map->type;
	bbio->num_stripes = num_stripes;
out:
	मुक्त_extent_map(em);
	वापस ret;
पूर्ण

/*
 * In dev-replace हाल, क्रम repair हाल (that's the only हाल where the mirror
 * is selected explicitly when calling btrfs_map_block), blocks left of the
 * left cursor can also be पढ़ो from the target drive.
 *
 * For REQ_GET_READ_MIRRORS, the target drive is added as the last one to the
 * array of stripes.
 * For READ, it also needs to be supported using the same mirror number.
 *
 * If the requested block is not left of the left cursor, EIO is वापसed. This
 * can happen because btrfs_num_copies() वापसs one more in the dev-replace
 * हाल.
 */
अटल पूर्णांक get_extra_mirror_from_replace(काष्ठा btrfs_fs_info *fs_info,
					 u64 logical, u64 length,
					 u64 srcdev_devid, पूर्णांक *mirror_num,
					 u64 *physical)
अणु
	काष्ठा btrfs_bio *bbio = शून्य;
	पूर्णांक num_stripes;
	पूर्णांक index_srcdev = 0;
	पूर्णांक found = 0;
	u64 physical_of_found = 0;
	पूर्णांक i;
	पूर्णांक ret = 0;

	ret = __btrfs_map_block(fs_info, BTRFS_MAP_GET_READ_MIRRORS,
				logical, &length, &bbio, 0, 0);
	अगर (ret) अणु
		ASSERT(bbio == शून्य);
		वापस ret;
	पूर्ण

	num_stripes = bbio->num_stripes;
	अगर (*mirror_num > num_stripes) अणु
		/*
		 * BTRFS_MAP_GET_READ_MIRRORS करोes not contain this mirror,
		 * that means that the requested area is not left of the left
		 * cursor
		 */
		btrfs_put_bbio(bbio);
		वापस -EIO;
	पूर्ण

	/*
	 * process the rest of the function using the mirror_num of the source
	 * drive. Thereक्रमe look it up first.  At the end, patch the device
	 * poपूर्णांकer to the one of the target drive.
	 */
	क्रम (i = 0; i < num_stripes; i++) अणु
		अगर (bbio->stripes[i].dev->devid != srcdev_devid)
			जारी;

		/*
		 * In हाल of DUP, in order to keep it simple, only add the
		 * mirror with the lowest physical address
		 */
		अगर (found &&
		    physical_of_found <= bbio->stripes[i].physical)
			जारी;

		index_srcdev = i;
		found = 1;
		physical_of_found = bbio->stripes[i].physical;
	पूर्ण

	btrfs_put_bbio(bbio);

	ASSERT(found);
	अगर (!found)
		वापस -EIO;

	*mirror_num = index_srcdev + 1;
	*physical = physical_of_found;
	वापस ret;
पूर्ण

अटल bool is_block_group_to_copy(काष्ठा btrfs_fs_info *fs_info, u64 logical)
अणु
	काष्ठा btrfs_block_group *cache;
	bool ret;

	/* Non zoned fileप्रणाली करोes not use "to_copy" flag */
	अगर (!btrfs_is_zoned(fs_info))
		वापस false;

	cache = btrfs_lookup_block_group(fs_info, logical);

	spin_lock(&cache->lock);
	ret = cache->to_copy;
	spin_unlock(&cache->lock);

	btrfs_put_block_group(cache);
	वापस ret;
पूर्ण

अटल व्योम handle_ops_on_dev_replace(क्रमागत btrfs_map_op op,
				      काष्ठा btrfs_bio **bbio_ret,
				      काष्ठा btrfs_dev_replace *dev_replace,
				      u64 logical,
				      पूर्णांक *num_stripes_ret, पूर्णांक *max_errors_ret)
अणु
	काष्ठा btrfs_bio *bbio = *bbio_ret;
	u64 srcdev_devid = dev_replace->srcdev->devid;
	पूर्णांक tgtdev_indexes = 0;
	पूर्णांक num_stripes = *num_stripes_ret;
	पूर्णांक max_errors = *max_errors_ret;
	पूर्णांक i;

	अगर (op == BTRFS_MAP_WRITE) अणु
		पूर्णांक index_where_to_add;

		/*
		 * A block group which have "to_copy" set will eventually
		 * copied by dev-replace process. We can aव्योम cloning IO here.
		 */
		अगर (is_block_group_to_copy(dev_replace->srcdev->fs_info, logical))
			वापस;

		/*
		 * duplicate the ग_लिखो operations जबतक the dev replace
		 * procedure is running. Since the copying of the old disk to
		 * the new disk takes place at run समय जबतक the fileप्रणाली is
		 * mounted writable, the regular ग_लिखो operations to the old
		 * disk have to be duplicated to go to the new disk as well.
		 *
		 * Note that device->missing is handled by the caller, and that
		 * the ग_लिखो to the old disk is alपढ़ोy set up in the stripes
		 * array.
		 */
		index_where_to_add = num_stripes;
		क्रम (i = 0; i < num_stripes; i++) अणु
			अगर (bbio->stripes[i].dev->devid == srcdev_devid) अणु
				/* ग_लिखो to new disk, too */
				काष्ठा btrfs_bio_stripe *new =
					bbio->stripes + index_where_to_add;
				काष्ठा btrfs_bio_stripe *old =
					bbio->stripes + i;

				new->physical = old->physical;
				new->length = old->length;
				new->dev = dev_replace->tgtdev;
				bbio->tgtdev_map[i] = index_where_to_add;
				index_where_to_add++;
				max_errors++;
				tgtdev_indexes++;
			पूर्ण
		पूर्ण
		num_stripes = index_where_to_add;
	पूर्ण अन्यथा अगर (op == BTRFS_MAP_GET_READ_MIRRORS) अणु
		पूर्णांक index_srcdev = 0;
		पूर्णांक found = 0;
		u64 physical_of_found = 0;

		/*
		 * During the dev-replace procedure, the target drive can also
		 * be used to पढ़ो data in हाल it is needed to repair a corrupt
		 * block अन्यथाwhere. This is possible अगर the requested area is
		 * left of the left cursor. In this area, the target drive is a
		 * full copy of the source drive.
		 */
		क्रम (i = 0; i < num_stripes; i++) अणु
			अगर (bbio->stripes[i].dev->devid == srcdev_devid) अणु
				/*
				 * In हाल of DUP, in order to keep it simple,
				 * only add the mirror with the lowest physical
				 * address
				 */
				अगर (found &&
				    physical_of_found <=
				     bbio->stripes[i].physical)
					जारी;
				index_srcdev = i;
				found = 1;
				physical_of_found = bbio->stripes[i].physical;
			पूर्ण
		पूर्ण
		अगर (found) अणु
			काष्ठा btrfs_bio_stripe *tgtdev_stripe =
				bbio->stripes + num_stripes;

			tgtdev_stripe->physical = physical_of_found;
			tgtdev_stripe->length =
				bbio->stripes[index_srcdev].length;
			tgtdev_stripe->dev = dev_replace->tgtdev;
			bbio->tgtdev_map[index_srcdev] = num_stripes;

			tgtdev_indexes++;
			num_stripes++;
		पूर्ण
	पूर्ण

	*num_stripes_ret = num_stripes;
	*max_errors_ret = max_errors;
	bbio->num_tgtdevs = tgtdev_indexes;
	*bbio_ret = bbio;
पूर्ण

अटल bool need_full_stripe(क्रमागत btrfs_map_op op)
अणु
	वापस (op == BTRFS_MAP_WRITE || op == BTRFS_MAP_GET_READ_MIRRORS);
पूर्ण

/*
 * Calculate the geometry of a particular (address, len) tuple. This
 * inक्रमmation is used to calculate how big a particular bio can get beक्रमe it
 * straddles a stripe.
 *
 * @fs_info: the fileप्रणाली
 * @em:      mapping containing the logical extent
 * @op:      type of operation - ग_लिखो or पढ़ो
 * @logical: address that we want to figure out the geometry of
 * @len:     the length of IO we are going to perक्रमm, starting at @logical
 * @io_geom: poपूर्णांकer used to वापस values
 *
 * Returns < 0 in हाल a chunk क्रम the given logical address cannot be found,
 * usually shouldn't happen unless @logical is corrupted, 0 otherwise.
 */
पूर्णांक btrfs_get_io_geometry(काष्ठा btrfs_fs_info *fs_info, काष्ठा extent_map *em,
			  क्रमागत btrfs_map_op op, u64 logical, u64 len,
			  काष्ठा btrfs_io_geometry *io_geom)
अणु
	काष्ठा map_lookup *map;
	u64 offset;
	u64 stripe_offset;
	u64 stripe_nr;
	u64 stripe_len;
	u64 raid56_full_stripe_start = (u64)-1;
	पूर्णांक data_stripes;

	ASSERT(op != BTRFS_MAP_DISCARD);

	map = em->map_lookup;
	/* Offset of this logical address in the chunk */
	offset = logical - em->start;
	/* Len of a stripe in a chunk */
	stripe_len = map->stripe_len;
	/* Stripe wher this block falls in */
	stripe_nr = भाग64_u64(offset, stripe_len);
	/* Offset of stripe in the chunk */
	stripe_offset = stripe_nr * stripe_len;
	अगर (offset < stripe_offset) अणु
		btrfs_crit(fs_info,
"stripe math has gone wrong, stripe_offset=%llu offset=%llu start=%llu logical=%llu stripe_len=%llu",
			stripe_offset, offset, em->start, logical, stripe_len);
		वापस -EINVAL;
	पूर्ण

	/* stripe_offset is the offset of this block in its stripe */
	stripe_offset = offset - stripe_offset;
	data_stripes = nr_data_stripes(map);

	अगर (map->type & BTRFS_BLOCK_GROUP_PROखाता_MASK) अणु
		u64 max_len = stripe_len - stripe_offset;

		/*
		 * In हाल of raid56, we need to know the stripe aligned start
		 */
		अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK) अणु
			अचिन्हित दीर्घ full_stripe_len = stripe_len * data_stripes;
			raid56_full_stripe_start = offset;

			/*
			 * Allow a ग_लिखो of a full stripe, but make sure we
			 * करोn't allow straddling of stripes
			 */
			raid56_full_stripe_start = भाग64_u64(raid56_full_stripe_start,
					full_stripe_len);
			raid56_full_stripe_start *= full_stripe_len;

			/*
			 * For ग_लिखोs to RAID[56], allow a full stripeset across
			 * all disks. For other RAID types and क्रम RAID[56]
			 * पढ़ोs, just allow a single stripe (on a single disk).
			 */
			अगर (op == BTRFS_MAP_WRITE) अणु
				max_len = stripe_len * data_stripes -
					  (offset - raid56_full_stripe_start);
			पूर्ण
		पूर्ण
		len = min_t(u64, em->len - offset, max_len);
	पूर्ण अन्यथा अणु
		len = em->len - offset;
	पूर्ण

	io_geom->len = len;
	io_geom->offset = offset;
	io_geom->stripe_len = stripe_len;
	io_geom->stripe_nr = stripe_nr;
	io_geom->stripe_offset = stripe_offset;
	io_geom->raid56_stripe_offset = raid56_full_stripe_start;

	वापस 0;
पूर्ण

अटल पूर्णांक __btrfs_map_block(काष्ठा btrfs_fs_info *fs_info,
			     क्रमागत btrfs_map_op op,
			     u64 logical, u64 *length,
			     काष्ठा btrfs_bio **bbio_ret,
			     पूर्णांक mirror_num, पूर्णांक need_raid_map)
अणु
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	u64 stripe_offset;
	u64 stripe_nr;
	u64 stripe_len;
	u32 stripe_index;
	पूर्णांक data_stripes;
	पूर्णांक i;
	पूर्णांक ret = 0;
	पूर्णांक num_stripes;
	पूर्णांक max_errors = 0;
	पूर्णांक tgtdev_indexes = 0;
	काष्ठा btrfs_bio *bbio = शून्य;
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
	पूर्णांक dev_replace_is_ongoing = 0;
	पूर्णांक num_alloc_stripes;
	पूर्णांक patch_the_first_stripe_क्रम_dev_replace = 0;
	u64 physical_to_patch_in_first_stripe = 0;
	u64 raid56_full_stripe_start = (u64)-1;
	काष्ठा btrfs_io_geometry geom;

	ASSERT(bbio_ret);
	ASSERT(op != BTRFS_MAP_DISCARD);

	em = btrfs_get_chunk_map(fs_info, logical, *length);
	ASSERT(!IS_ERR(em));

	ret = btrfs_get_io_geometry(fs_info, em, op, logical, *length, &geom);
	अगर (ret < 0)
		वापस ret;

	map = em->map_lookup;

	*length = geom.len;
	stripe_len = geom.stripe_len;
	stripe_nr = geom.stripe_nr;
	stripe_offset = geom.stripe_offset;
	raid56_full_stripe_start = geom.raid56_stripe_offset;
	data_stripes = nr_data_stripes(map);

	करोwn_पढ़ो(&dev_replace->rwsem);
	dev_replace_is_ongoing = btrfs_dev_replace_is_ongoing(dev_replace);
	/*
	 * Hold the semaphore क्रम पढ़ो during the whole operation, ग_लिखो is
	 * requested at commit समय but must रुको.
	 */
	अगर (!dev_replace_is_ongoing)
		up_पढ़ो(&dev_replace->rwsem);

	अगर (dev_replace_is_ongoing && mirror_num == map->num_stripes + 1 &&
	    !need_full_stripe(op) && dev_replace->tgtdev != शून्य) अणु
		ret = get_extra_mirror_from_replace(fs_info, logical, *length,
						    dev_replace->srcdev->devid,
						    &mirror_num,
					    &physical_to_patch_in_first_stripe);
		अगर (ret)
			जाओ out;
		अन्यथा
			patch_the_first_stripe_क्रम_dev_replace = 1;
	पूर्ण अन्यथा अगर (mirror_num > map->num_stripes) अणु
		mirror_num = 0;
	पूर्ण

	num_stripes = 1;
	stripe_index = 0;
	अगर (map->type & BTRFS_BLOCK_GROUP_RAID0) अणु
		stripe_nr = भाग_u64_rem(stripe_nr, map->num_stripes,
				&stripe_index);
		अगर (!need_full_stripe(op))
			mirror_num = 1;
	पूर्ण अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_RAID1_MASK) अणु
		अगर (need_full_stripe(op))
			num_stripes = map->num_stripes;
		अन्यथा अगर (mirror_num)
			stripe_index = mirror_num - 1;
		अन्यथा अणु
			stripe_index = find_live_mirror(fs_info, map, 0,
					    dev_replace_is_ongoing);
			mirror_num = stripe_index + 1;
		पूर्ण

	पूर्ण अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_DUP) अणु
		अगर (need_full_stripe(op)) अणु
			num_stripes = map->num_stripes;
		पूर्ण अन्यथा अगर (mirror_num) अणु
			stripe_index = mirror_num - 1;
		पूर्ण अन्यथा अणु
			mirror_num = 1;
		पूर्ण

	पूर्ण अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_RAID10) अणु
		u32 factor = map->num_stripes / map->sub_stripes;

		stripe_nr = भाग_u64_rem(stripe_nr, factor, &stripe_index);
		stripe_index *= map->sub_stripes;

		अगर (need_full_stripe(op))
			num_stripes = map->sub_stripes;
		अन्यथा अगर (mirror_num)
			stripe_index += mirror_num - 1;
		अन्यथा अणु
			पूर्णांक old_stripe_index = stripe_index;
			stripe_index = find_live_mirror(fs_info, map,
					      stripe_index,
					      dev_replace_is_ongoing);
			mirror_num = stripe_index - old_stripe_index + 1;
		पूर्ण

	पूर्ण अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK) अणु
		अगर (need_raid_map && (need_full_stripe(op) || mirror_num > 1)) अणु
			/* push stripe_nr back to the start of the full stripe */
			stripe_nr = भाग64_u64(raid56_full_stripe_start,
					stripe_len * data_stripes);

			/* RAID[56] ग_लिखो or recovery. Return all stripes */
			num_stripes = map->num_stripes;
			max_errors = nr_parity_stripes(map);

			*length = map->stripe_len;
			stripe_index = 0;
			stripe_offset = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Mirror #0 or #1 means the original data block.
			 * Mirror #2 is RAID5 parity block.
			 * Mirror #3 is RAID6 Q block.
			 */
			stripe_nr = भाग_u64_rem(stripe_nr,
					data_stripes, &stripe_index);
			अगर (mirror_num > 1)
				stripe_index = data_stripes + mirror_num - 2;

			/* We distribute the parity blocks across stripes */
			भाग_u64_rem(stripe_nr + stripe_index, map->num_stripes,
					&stripe_index);
			अगर (!need_full_stripe(op) && mirror_num <= 1)
				mirror_num = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * after this, stripe_nr is the number of stripes on this
		 * device we have to walk to find the data, and stripe_index is
		 * the number of our device in the stripe array
		 */
		stripe_nr = भाग_u64_rem(stripe_nr, map->num_stripes,
				&stripe_index);
		mirror_num = stripe_index + 1;
	पूर्ण
	अगर (stripe_index >= map->num_stripes) अणु
		btrfs_crit(fs_info,
			   "stripe index math went horribly wrong, got stripe_index=%u, num_stripes=%u",
			   stripe_index, map->num_stripes);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	num_alloc_stripes = num_stripes;
	अगर (dev_replace_is_ongoing && dev_replace->tgtdev != शून्य) अणु
		अगर (op == BTRFS_MAP_WRITE)
			num_alloc_stripes <<= 1;
		अगर (op == BTRFS_MAP_GET_READ_MIRRORS)
			num_alloc_stripes++;
		tgtdev_indexes = num_stripes;
	पूर्ण

	bbio = alloc_btrfs_bio(num_alloc_stripes, tgtdev_indexes);
	अगर (!bbio) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_stripes; i++) अणु
		bbio->stripes[i].physical = map->stripes[stripe_index].physical +
			stripe_offset + stripe_nr * map->stripe_len;
		bbio->stripes[i].dev = map->stripes[stripe_index].dev;
		stripe_index++;
	पूर्ण

	/* build raid_map */
	अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK && need_raid_map &&
	    (need_full_stripe(op) || mirror_num > 1)) अणु
		u64 पंचांगp;
		अचिन्हित rot;

		/* Work out the disk rotation on this stripe-set */
		भाग_u64_rem(stripe_nr, num_stripes, &rot);

		/* Fill in the logical address of each stripe */
		पंचांगp = stripe_nr * data_stripes;
		क्रम (i = 0; i < data_stripes; i++)
			bbio->raid_map[(i+rot) % num_stripes] =
				em->start + (पंचांगp + i) * map->stripe_len;

		bbio->raid_map[(i+rot) % map->num_stripes] = RAID5_P_STRIPE;
		अगर (map->type & BTRFS_BLOCK_GROUP_RAID6)
			bbio->raid_map[(i+rot+1) % num_stripes] =
				RAID6_Q_STRIPE;

		sort_parity_stripes(bbio, num_stripes);
	पूर्ण

	अगर (need_full_stripe(op))
		max_errors = btrfs_chunk_max_errors(map);

	अगर (dev_replace_is_ongoing && dev_replace->tgtdev != शून्य &&
	    need_full_stripe(op)) अणु
		handle_ops_on_dev_replace(op, &bbio, dev_replace, logical,
					  &num_stripes, &max_errors);
	पूर्ण

	*bbio_ret = bbio;
	bbio->map_type = map->type;
	bbio->num_stripes = num_stripes;
	bbio->max_errors = max_errors;
	bbio->mirror_num = mirror_num;

	/*
	 * this is the हाल that REQ_READ && dev_replace_is_ongoing &&
	 * mirror_num == num_stripes + 1 && dev_replace target drive is
	 * available as a mirror
	 */
	अगर (patch_the_first_stripe_क्रम_dev_replace && num_stripes > 0) अणु
		WARN_ON(num_stripes > 1);
		bbio->stripes[0].dev = dev_replace->tgtdev;
		bbio->stripes[0].physical = physical_to_patch_in_first_stripe;
		bbio->mirror_num = map->num_stripes + 1;
	पूर्ण
out:
	अगर (dev_replace_is_ongoing) अणु
		lockdep_निश्चित_held(&dev_replace->rwsem);
		/* Unlock and let रुकोing ग_लिखोrs proceed */
		up_पढ़ो(&dev_replace->rwsem);
	पूर्ण
	मुक्त_extent_map(em);
	वापस ret;
पूर्ण

पूर्णांक btrfs_map_block(काष्ठा btrfs_fs_info *fs_info, क्रमागत btrfs_map_op op,
		      u64 logical, u64 *length,
		      काष्ठा btrfs_bio **bbio_ret, पूर्णांक mirror_num)
अणु
	अगर (op == BTRFS_MAP_DISCARD)
		वापस __btrfs_map_block_क्रम_discard(fs_info, logical,
						     length, bbio_ret);

	वापस __btrfs_map_block(fs_info, op, logical, length, bbio_ret,
				 mirror_num, 0);
पूर्ण

/* For Scrub/replace */
पूर्णांक btrfs_map_sblock(काष्ठा btrfs_fs_info *fs_info, क्रमागत btrfs_map_op op,
		     u64 logical, u64 *length,
		     काष्ठा btrfs_bio **bbio_ret)
अणु
	वापस __btrfs_map_block(fs_info, op, logical, length, bbio_ret, 0, 1);
पूर्ण

अटल अंतरभूत व्योम btrfs_end_bbio(काष्ठा btrfs_bio *bbio, काष्ठा bio *bio)
अणु
	bio->bi_निजी = bbio->निजी;
	bio->bi_end_io = bbio->end_io;
	bio_endio(bio);

	btrfs_put_bbio(bbio);
पूर्ण

अटल व्योम btrfs_end_bio(काष्ठा bio *bio)
अणु
	काष्ठा btrfs_bio *bbio = bio->bi_निजी;
	पूर्णांक is_orig_bio = 0;

	अगर (bio->bi_status) अणु
		atomic_inc(&bbio->error);
		अगर (bio->bi_status == BLK_STS_IOERR ||
		    bio->bi_status == BLK_STS_TARGET) अणु
			काष्ठा btrfs_device *dev = btrfs_io_bio(bio)->device;

			ASSERT(dev->bdev);
			अगर (btrfs_op(bio) == BTRFS_MAP_WRITE)
				btrfs_dev_stat_inc_and_prपूर्णांक(dev,
						BTRFS_DEV_STAT_WRITE_ERRS);
			अन्यथा अगर (!(bio->bi_opf & REQ_RAHEAD))
				btrfs_dev_stat_inc_and_prपूर्णांक(dev,
						BTRFS_DEV_STAT_READ_ERRS);
			अगर (bio->bi_opf & REQ_PREFLUSH)
				btrfs_dev_stat_inc_and_prपूर्णांक(dev,
						BTRFS_DEV_STAT_FLUSH_ERRS);
		पूर्ण
	पूर्ण

	अगर (bio == bbio->orig_bio)
		is_orig_bio = 1;

	btrfs_bio_counter_dec(bbio->fs_info);

	अगर (atomic_dec_and_test(&bbio->stripes_pending)) अणु
		अगर (!is_orig_bio) अणु
			bio_put(bio);
			bio = bbio->orig_bio;
		पूर्ण

		btrfs_io_bio(bio)->mirror_num = bbio->mirror_num;
		/* only send an error to the higher layers अगर it is
		 * beyond the tolerance of the btrfs bio
		 */
		अगर (atomic_पढ़ो(&bbio->error) > bbio->max_errors) अणु
			bio->bi_status = BLK_STS_IOERR;
		पूर्ण अन्यथा अणु
			/*
			 * this bio is actually up to date, we didn't
			 * go over the max number of errors
			 */
			bio->bi_status = BLK_STS_OK;
		पूर्ण

		btrfs_end_bbio(bbio, bio);
	पूर्ण अन्यथा अगर (!is_orig_bio) अणु
		bio_put(bio);
	पूर्ण
पूर्ण

अटल व्योम submit_stripe_bio(काष्ठा btrfs_bio *bbio, काष्ठा bio *bio,
			      u64 physical, काष्ठा btrfs_device *dev)
अणु
	काष्ठा btrfs_fs_info *fs_info = bbio->fs_info;

	bio->bi_निजी = bbio;
	btrfs_io_bio(bio)->device = dev;
	bio->bi_end_io = btrfs_end_bio;
	bio->bi_iter.bi_sector = physical >> 9;
	/*
	 * For zone append writing, bi_sector must poपूर्णांक the beginning of the
	 * zone
	 */
	अगर (bio_op(bio) == REQ_OP_ZONE_APPEND) अणु
		अगर (btrfs_dev_is_sequential(dev, physical)) अणु
			u64 zone_start = round_करोwn(physical, fs_info->zone_size);

			bio->bi_iter.bi_sector = zone_start >> SECTOR_SHIFT;
		पूर्ण अन्यथा अणु
			bio->bi_opf &= ~REQ_OP_ZONE_APPEND;
			bio->bi_opf |= REQ_OP_WRITE;
		पूर्ण
	पूर्ण
	btrfs_debug_in_rcu(fs_info,
	"btrfs_map_bio: rw %d 0x%x, sector=%llu, dev=%lu (%s id %llu), size=%u",
		bio_op(bio), bio->bi_opf, bio->bi_iter.bi_sector,
		(अचिन्हित दीर्घ)dev->bdev->bd_dev, rcu_str_deref(dev->name),
		dev->devid, bio->bi_iter.bi_size);
	bio_set_dev(bio, dev->bdev);

	btrfs_bio_counter_inc_noblocked(fs_info);

	btrfsic_submit_bio(bio);
पूर्ण

अटल व्योम bbio_error(काष्ठा btrfs_bio *bbio, काष्ठा bio *bio, u64 logical)
अणु
	atomic_inc(&bbio->error);
	अगर (atomic_dec_and_test(&bbio->stripes_pending)) अणु
		/* Should be the original bio. */
		WARN_ON(bio != bbio->orig_bio);

		btrfs_io_bio(bio)->mirror_num = bbio->mirror_num;
		bio->bi_iter.bi_sector = logical >> 9;
		अगर (atomic_पढ़ो(&bbio->error) > bbio->max_errors)
			bio->bi_status = BLK_STS_IOERR;
		अन्यथा
			bio->bi_status = BLK_STS_OK;
		btrfs_end_bbio(bbio, bio);
	पूर्ण
पूर्ण

blk_status_t btrfs_map_bio(काष्ठा btrfs_fs_info *fs_info, काष्ठा bio *bio,
			   पूर्णांक mirror_num)
अणु
	काष्ठा btrfs_device *dev;
	काष्ठा bio *first_bio = bio;
	u64 logical = bio->bi_iter.bi_sector << 9;
	u64 length = 0;
	u64 map_length;
	पूर्णांक ret;
	पूर्णांक dev_nr;
	पूर्णांक total_devs;
	काष्ठा btrfs_bio *bbio = शून्य;

	length = bio->bi_iter.bi_size;
	map_length = length;

	btrfs_bio_counter_inc_blocked(fs_info);
	ret = __btrfs_map_block(fs_info, btrfs_op(bio), logical,
				&map_length, &bbio, mirror_num, 1);
	अगर (ret) अणु
		btrfs_bio_counter_dec(fs_info);
		वापस त्रुटि_सं_to_blk_status(ret);
	पूर्ण

	total_devs = bbio->num_stripes;
	bbio->orig_bio = first_bio;
	bbio->निजी = first_bio->bi_निजी;
	bbio->end_io = first_bio->bi_end_io;
	bbio->fs_info = fs_info;
	atomic_set(&bbio->stripes_pending, bbio->num_stripes);

	अगर ((bbio->map_type & BTRFS_BLOCK_GROUP_RAID56_MASK) &&
	    ((btrfs_op(bio) == BTRFS_MAP_WRITE) || (mirror_num > 1))) अणु
		/* In this हाल, map_length has been set to the length of
		   a single stripe; not the whole ग_लिखो */
		अगर (btrfs_op(bio) == BTRFS_MAP_WRITE) अणु
			ret = raid56_parity_ग_लिखो(fs_info, bio, bbio,
						  map_length);
		पूर्ण अन्यथा अणु
			ret = raid56_parity_recover(fs_info, bio, bbio,
						    map_length, mirror_num, 1);
		पूर्ण

		btrfs_bio_counter_dec(fs_info);
		वापस त्रुटि_सं_to_blk_status(ret);
	पूर्ण

	अगर (map_length < length) अणु
		btrfs_crit(fs_info,
			   "mapping failed logical %llu bio len %llu len %llu",
			   logical, length, map_length);
		BUG();
	पूर्ण

	क्रम (dev_nr = 0; dev_nr < total_devs; dev_nr++) अणु
		dev = bbio->stripes[dev_nr].dev;
		अगर (!dev || !dev->bdev || test_bit(BTRFS_DEV_STATE_MISSING,
						   &dev->dev_state) ||
		    (btrfs_op(first_bio) == BTRFS_MAP_WRITE &&
		    !test_bit(BTRFS_DEV_STATE_WRITEABLE, &dev->dev_state))) अणु
			bbio_error(bbio, first_bio, logical);
			जारी;
		पूर्ण

		अगर (dev_nr < total_devs - 1)
			bio = btrfs_bio_clone(first_bio);
		अन्यथा
			bio = first_bio;

		submit_stripe_bio(bbio, bio, bbio->stripes[dev_nr].physical, dev);
	पूर्ण
	btrfs_bio_counter_dec(fs_info);
	वापस BLK_STS_OK;
पूर्ण

/*
 * Find a device specअगरied by @devid or @uuid in the list of @fs_devices, or
 * वापस शून्य.
 *
 * If devid and uuid are both specअगरied, the match must be exact, otherwise
 * only devid is used.
 *
 * If @seed is true, traverse through the seed devices.
 */
काष्ठा btrfs_device *btrfs_find_device(काष्ठा btrfs_fs_devices *fs_devices,
				       u64 devid, u8 *uuid, u8 *fsid)
अणु
	काष्ठा btrfs_device *device;
	काष्ठा btrfs_fs_devices *seed_devs;

	अगर (!fsid || !स_भेद(fs_devices->metadata_uuid, fsid, BTRFS_FSID_SIZE)) अणु
		list_क्रम_each_entry(device, &fs_devices->devices, dev_list) अणु
			अगर (device->devid == devid &&
			    (!uuid || स_भेद(device->uuid, uuid,
					     BTRFS_UUID_SIZE) == 0))
				वापस device;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(seed_devs, &fs_devices->seed_list, seed_list) अणु
		अगर (!fsid ||
		    !स_भेद(seed_devs->metadata_uuid, fsid, BTRFS_FSID_SIZE)) अणु
			list_क्रम_each_entry(device, &seed_devs->devices,
					    dev_list) अणु
				अगर (device->devid == devid &&
				    (!uuid || स_भेद(device->uuid, uuid,
						     BTRFS_UUID_SIZE) == 0))
					वापस device;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा btrfs_device *add_missing_dev(काष्ठा btrfs_fs_devices *fs_devices,
					    u64 devid, u8 *dev_uuid)
अणु
	काष्ठा btrfs_device *device;
	अचिन्हित पूर्णांक nofs_flag;

	/*
	 * We call this under the chunk_mutex, so we want to use NOFS क्रम this
	 * allocation, however we करोn't want to change btrfs_alloc_device() to
	 * always करो NOFS because we use it in a lot of other GFP_KERNEL safe
	 * places.
	 */
	nofs_flag = meदो_स्मृति_nofs_save();
	device = btrfs_alloc_device(शून्य, &devid, dev_uuid);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (IS_ERR(device))
		वापस device;

	list_add(&device->dev_list, &fs_devices->devices);
	device->fs_devices = fs_devices;
	fs_devices->num_devices++;

	set_bit(BTRFS_DEV_STATE_MISSING, &device->dev_state);
	fs_devices->missing_devices++;

	वापस device;
पूर्ण

/**
 * btrfs_alloc_device - allocate काष्ठा btrfs_device
 * @fs_info:	used only क्रम generating a new devid, can be शून्य अगर
 *		devid is provided (i.e. @devid != शून्य).
 * @devid:	a poपूर्णांकer to devid क्रम this device.  If शून्य a new devid
 *		is generated.
 * @uuid:	a poपूर्णांकer to UUID क्रम this device.  If शून्य a new UUID
 *		is generated.
 *
 * Return: a poपूर्णांकer to a new &काष्ठा btrfs_device on success; ERR_PTR()
 * on error.  Returned काष्ठा is not linked onto any lists and must be
 * destroyed with btrfs_मुक्त_device.
 */
काष्ठा btrfs_device *btrfs_alloc_device(काष्ठा btrfs_fs_info *fs_info,
					स्थिर u64 *devid,
					स्थिर u8 *uuid)
अणु
	काष्ठा btrfs_device *dev;
	u64 पंचांगp;

	अगर (WARN_ON(!devid && !fs_info))
		वापस ERR_PTR(-EINVAL);

	dev = __alloc_device(fs_info);
	अगर (IS_ERR(dev))
		वापस dev;

	अगर (devid)
		पंचांगp = *devid;
	अन्यथा अणु
		पूर्णांक ret;

		ret = find_next_devid(fs_info, &पंचांगp);
		अगर (ret) अणु
			btrfs_मुक्त_device(dev);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण
	dev->devid = पंचांगp;

	अगर (uuid)
		स_नकल(dev->uuid, uuid, BTRFS_UUID_SIZE);
	अन्यथा
		generate_अक्रमom_uuid(dev->uuid);

	वापस dev;
पूर्ण

अटल व्योम btrfs_report_missing_device(काष्ठा btrfs_fs_info *fs_info,
					u64 devid, u8 *uuid, bool error)
अणु
	अगर (error)
		btrfs_err_rl(fs_info, "devid %llu uuid %pU is missing",
			      devid, uuid);
	अन्यथा
		btrfs_warn_rl(fs_info, "devid %llu uuid %pU is missing",
			      devid, uuid);
पूर्ण

अटल u64 calc_stripe_length(u64 type, u64 chunk_len, पूर्णांक num_stripes)
अणु
	पूर्णांक index = btrfs_bg_flags_to_raid_index(type);
	पूर्णांक ncopies = btrfs_raid_array[index].ncopies;
	स्थिर पूर्णांक nparity = btrfs_raid_array[index].nparity;
	पूर्णांक data_stripes;

	अगर (nparity)
		data_stripes = num_stripes - nparity;
	अन्यथा
		data_stripes = num_stripes / ncopies;

	वापस भाग_u64(chunk_len, data_stripes);
पूर्ण

#अगर BITS_PER_LONG == 32
/*
 * Due to page cache limit, metadata beyond BTRFS_32BIT_MAX_खाता_SIZE
 * can't be accessed on 32bit प्रणालीs.
 *
 * This function करो mount समय check to reject the fs अगर it alपढ़ोy has
 * metadata chunk beyond that limit.
 */
अटल पूर्णांक check_32bit_meta_chunk(काष्ठा btrfs_fs_info *fs_info,
				  u64 logical, u64 length, u64 type)
अणु
	अगर (!(type & BTRFS_BLOCK_GROUP_METADATA))
		वापस 0;

	अगर (logical + length < MAX_LFS_खाताSIZE)
		वापस 0;

	btrfs_err_32bit_limit(fs_info);
	वापस -EOVERFLOW;
पूर्ण

/*
 * This is to give early warning क्रम any metadata chunk reaching
 * BTRFS_32BIT_EARLY_WARN_THRESHOLD.
 * Although we can still access the metadata, it's not going to be possible
 * once the limit is reached.
 */
अटल व्योम warn_32bit_meta_chunk(काष्ठा btrfs_fs_info *fs_info,
				  u64 logical, u64 length, u64 type)
अणु
	अगर (!(type & BTRFS_BLOCK_GROUP_METADATA))
		वापस;

	अगर (logical + length < BTRFS_32BIT_EARLY_WARN_THRESHOLD)
		वापस;

	btrfs_warn_32bit_limit(fs_info);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक पढ़ो_one_chunk(काष्ठा btrfs_key *key, काष्ठा extent_buffer *leaf,
			  काष्ठा btrfs_chunk *chunk)
अणु
	काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	काष्ठा extent_map_tree *map_tree = &fs_info->mapping_tree;
	काष्ठा map_lookup *map;
	काष्ठा extent_map *em;
	u64 logical;
	u64 length;
	u64 devid;
	u64 type;
	u8 uuid[BTRFS_UUID_SIZE];
	पूर्णांक num_stripes;
	पूर्णांक ret;
	पूर्णांक i;

	logical = key->offset;
	length = btrfs_chunk_length(leaf, chunk);
	type = btrfs_chunk_type(leaf, chunk);
	num_stripes = btrfs_chunk_num_stripes(leaf, chunk);

#अगर BITS_PER_LONG == 32
	ret = check_32bit_meta_chunk(fs_info, logical, length, type);
	अगर (ret < 0)
		वापस ret;
	warn_32bit_meta_chunk(fs_info, logical, length, type);
#पूर्ण_अगर

	/*
	 * Only need to verअगरy chunk item अगर we're पढ़ोing from sys chunk array,
	 * as chunk item in tree block is alपढ़ोy verअगरied by tree-checker.
	 */
	अगर (leaf->start == BTRFS_SUPER_INFO_OFFSET) अणु
		ret = btrfs_check_chunk_valid(leaf, chunk, logical);
		अगर (ret)
			वापस ret;
	पूर्ण

	पढ़ो_lock(&map_tree->lock);
	em = lookup_extent_mapping(map_tree, logical, 1);
	पढ़ो_unlock(&map_tree->lock);

	/* alपढ़ोy mapped? */
	अगर (em && em->start <= logical && em->start + em->len > logical) अणु
		मुक्त_extent_map(em);
		वापस 0;
	पूर्ण अन्यथा अगर (em) अणु
		मुक्त_extent_map(em);
	पूर्ण

	em = alloc_extent_map();
	अगर (!em)
		वापस -ENOMEM;
	map = kदो_स्मृति(map_lookup_size(num_stripes), GFP_NOFS);
	अगर (!map) अणु
		मुक्त_extent_map(em);
		वापस -ENOMEM;
	पूर्ण

	set_bit(EXTENT_FLAG_FS_MAPPING, &em->flags);
	em->map_lookup = map;
	em->start = logical;
	em->len = length;
	em->orig_start = 0;
	em->block_start = 0;
	em->block_len = em->len;

	map->num_stripes = num_stripes;
	map->io_width = btrfs_chunk_io_width(leaf, chunk);
	map->io_align = btrfs_chunk_io_align(leaf, chunk);
	map->stripe_len = btrfs_chunk_stripe_len(leaf, chunk);
	map->type = type;
	map->sub_stripes = btrfs_chunk_sub_stripes(leaf, chunk);
	map->verअगरied_stripes = 0;
	em->orig_block_len = calc_stripe_length(type, em->len,
						map->num_stripes);
	क्रम (i = 0; i < num_stripes; i++) अणु
		map->stripes[i].physical =
			btrfs_stripe_offset_nr(leaf, chunk, i);
		devid = btrfs_stripe_devid_nr(leaf, chunk, i);
		पढ़ो_extent_buffer(leaf, uuid, (अचिन्हित दीर्घ)
				   btrfs_stripe_dev_uuid_nr(chunk, i),
				   BTRFS_UUID_SIZE);
		map->stripes[i].dev = btrfs_find_device(fs_info->fs_devices,
							devid, uuid, शून्य);
		अगर (!map->stripes[i].dev &&
		    !btrfs_test_opt(fs_info, DEGRADED)) अणु
			मुक्त_extent_map(em);
			btrfs_report_missing_device(fs_info, devid, uuid, true);
			वापस -ENOENT;
		पूर्ण
		अगर (!map->stripes[i].dev) अणु
			map->stripes[i].dev =
				add_missing_dev(fs_info->fs_devices, devid,
						uuid);
			अगर (IS_ERR(map->stripes[i].dev)) अणु
				मुक्त_extent_map(em);
				btrfs_err(fs_info,
					"failed to init missing dev %llu: %ld",
					devid, PTR_ERR(map->stripes[i].dev));
				वापस PTR_ERR(map->stripes[i].dev);
			पूर्ण
			btrfs_report_missing_device(fs_info, devid, uuid, false);
		पूर्ण
		set_bit(BTRFS_DEV_STATE_IN_FS_METADATA,
				&(map->stripes[i].dev->dev_state));

	पूर्ण

	ग_लिखो_lock(&map_tree->lock);
	ret = add_extent_mapping(map_tree, em, 0);
	ग_लिखो_unlock(&map_tree->lock);
	अगर (ret < 0) अणु
		btrfs_err(fs_info,
			  "failed to add chunk map, start=%llu len=%llu: %d",
			  em->start, em->len, ret);
	पूर्ण
	मुक्त_extent_map(em);

	वापस ret;
पूर्ण

अटल व्योम fill_device_from_item(काष्ठा extent_buffer *leaf,
				 काष्ठा btrfs_dev_item *dev_item,
				 काष्ठा btrfs_device *device)
अणु
	अचिन्हित दीर्घ ptr;

	device->devid = btrfs_device_id(leaf, dev_item);
	device->disk_total_bytes = btrfs_device_total_bytes(leaf, dev_item);
	device->total_bytes = device->disk_total_bytes;
	device->commit_total_bytes = device->disk_total_bytes;
	device->bytes_used = btrfs_device_bytes_used(leaf, dev_item);
	device->commit_bytes_used = device->bytes_used;
	device->type = btrfs_device_type(leaf, dev_item);
	device->io_align = btrfs_device_io_align(leaf, dev_item);
	device->io_width = btrfs_device_io_width(leaf, dev_item);
	device->sector_size = btrfs_device_sector_size(leaf, dev_item);
	WARN_ON(device->devid == BTRFS_DEV_REPLACE_DEVID);
	clear_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state);

	ptr = btrfs_device_uuid(dev_item);
	पढ़ो_extent_buffer(leaf, device->uuid, ptr, BTRFS_UUID_SIZE);
पूर्ण

अटल काष्ठा btrfs_fs_devices *खोलो_seed_devices(काष्ठा btrfs_fs_info *fs_info,
						  u8 *fsid)
अणु
	काष्ठा btrfs_fs_devices *fs_devices;
	पूर्णांक ret;

	lockdep_निश्चित_held(&uuid_mutex);
	ASSERT(fsid);

	/* This will match only क्रम multi-device seed fs */
	list_क्रम_each_entry(fs_devices, &fs_info->fs_devices->seed_list, seed_list)
		अगर (!स_भेद(fs_devices->fsid, fsid, BTRFS_FSID_SIZE))
			वापस fs_devices;


	fs_devices = find_fsid(fsid, शून्य);
	अगर (!fs_devices) अणु
		अगर (!btrfs_test_opt(fs_info, DEGRADED))
			वापस ERR_PTR(-ENOENT);

		fs_devices = alloc_fs_devices(fsid, शून्य);
		अगर (IS_ERR(fs_devices))
			वापस fs_devices;

		fs_devices->seeding = true;
		fs_devices->खोलोed = 1;
		वापस fs_devices;
	पूर्ण

	/*
	 * Upon first call क्रम a seed fs fsid, just create a निजी copy of the
	 * respective fs_devices and anchor it at fs_info->fs_devices->seed_list
	 */
	fs_devices = clone_fs_devices(fs_devices);
	अगर (IS_ERR(fs_devices))
		वापस fs_devices;

	ret = खोलो_fs_devices(fs_devices, FMODE_READ, fs_info->bdev_holder);
	अगर (ret) अणु
		मुक्त_fs_devices(fs_devices);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (!fs_devices->seeding) अणु
		बंद_fs_devices(fs_devices);
		मुक्त_fs_devices(fs_devices);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	list_add(&fs_devices->seed_list, &fs_info->fs_devices->seed_list);

	वापस fs_devices;
पूर्ण

अटल पूर्णांक पढ़ो_one_dev(काष्ठा extent_buffer *leaf,
			काष्ठा btrfs_dev_item *dev_item)
अणु
	काष्ठा btrfs_fs_info *fs_info = leaf->fs_info;
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	काष्ठा btrfs_device *device;
	u64 devid;
	पूर्णांक ret;
	u8 fs_uuid[BTRFS_FSID_SIZE];
	u8 dev_uuid[BTRFS_UUID_SIZE];

	devid = btrfs_device_id(leaf, dev_item);
	पढ़ो_extent_buffer(leaf, dev_uuid, btrfs_device_uuid(dev_item),
			   BTRFS_UUID_SIZE);
	पढ़ो_extent_buffer(leaf, fs_uuid, btrfs_device_fsid(dev_item),
			   BTRFS_FSID_SIZE);

	अगर (स_भेद(fs_uuid, fs_devices->metadata_uuid, BTRFS_FSID_SIZE)) अणु
		fs_devices = खोलो_seed_devices(fs_info, fs_uuid);
		अगर (IS_ERR(fs_devices))
			वापस PTR_ERR(fs_devices);
	पूर्ण

	device = btrfs_find_device(fs_info->fs_devices, devid, dev_uuid,
				   fs_uuid);
	अगर (!device) अणु
		अगर (!btrfs_test_opt(fs_info, DEGRADED)) अणु
			btrfs_report_missing_device(fs_info, devid,
							dev_uuid, true);
			वापस -ENOENT;
		पूर्ण

		device = add_missing_dev(fs_devices, devid, dev_uuid);
		अगर (IS_ERR(device)) अणु
			btrfs_err(fs_info,
				"failed to add missing dev %llu: %ld",
				devid, PTR_ERR(device));
			वापस PTR_ERR(device);
		पूर्ण
		btrfs_report_missing_device(fs_info, devid, dev_uuid, false);
	पूर्ण अन्यथा अणु
		अगर (!device->bdev) अणु
			अगर (!btrfs_test_opt(fs_info, DEGRADED)) अणु
				btrfs_report_missing_device(fs_info,
						devid, dev_uuid, true);
				वापस -ENOENT;
			पूर्ण
			btrfs_report_missing_device(fs_info, devid,
							dev_uuid, false);
		पूर्ण

		अगर (!device->bdev &&
		    !test_bit(BTRFS_DEV_STATE_MISSING, &device->dev_state)) अणु
			/*
			 * this happens when a device that was properly setup
			 * in the device info lists suddenly goes bad.
			 * device->bdev is शून्य, and so we have to set
			 * device->missing to one here
			 */
			device->fs_devices->missing_devices++;
			set_bit(BTRFS_DEV_STATE_MISSING, &device->dev_state);
		पूर्ण

		/* Move the device to its own fs_devices */
		अगर (device->fs_devices != fs_devices) अणु
			ASSERT(test_bit(BTRFS_DEV_STATE_MISSING,
							&device->dev_state));

			list_move(&device->dev_list, &fs_devices->devices);
			device->fs_devices->num_devices--;
			fs_devices->num_devices++;

			device->fs_devices->missing_devices--;
			fs_devices->missing_devices++;

			device->fs_devices = fs_devices;
		पूर्ण
	पूर्ण

	अगर (device->fs_devices != fs_info->fs_devices) अणु
		BUG_ON(test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state));
		अगर (device->generation !=
		    btrfs_device_generation(leaf, dev_item))
			वापस -EINVAL;
	पूर्ण

	fill_device_from_item(leaf, dev_item, device);
	अगर (device->bdev) अणु
		u64 max_total_bytes = i_size_पढ़ो(device->bdev->bd_inode);

		अगर (device->total_bytes > max_total_bytes) अणु
			btrfs_err(fs_info,
			"device total_bytes should be at most %llu but found %llu",
				  max_total_bytes, device->total_bytes);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	set_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &device->dev_state);
	अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state) &&
	   !test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state)) अणु
		device->fs_devices->total_rw_bytes += device->total_bytes;
		atomic64_add(device->total_bytes - device->bytes_used,
				&fs_info->मुक्त_chunk_space);
	पूर्ण
	ret = 0;
	वापस ret;
पूर्ण

पूर्णांक btrfs_पढ़ो_sys_array(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *root = fs_info->tree_root;
	काष्ठा btrfs_super_block *super_copy = fs_info->super_copy;
	काष्ठा extent_buffer *sb;
	काष्ठा btrfs_disk_key *disk_key;
	काष्ठा btrfs_chunk *chunk;
	u8 *array_ptr;
	अचिन्हित दीर्घ sb_array_offset;
	पूर्णांक ret = 0;
	u32 num_stripes;
	u32 array_size;
	u32 len = 0;
	u32 cur_offset;
	u64 type;
	काष्ठा btrfs_key key;

	ASSERT(BTRFS_SUPER_INFO_SIZE <= fs_info->nodesize);
	/*
	 * This will create extent buffer of nodesize, superblock size is
	 * fixed to BTRFS_SUPER_INFO_SIZE. If nodesize > sb size, this will
	 * overallocate but we can keep it as-is, only the first page is used.
	 */
	sb = btrfs_find_create_tree_block(fs_info, BTRFS_SUPER_INFO_OFFSET,
					  root->root_key.objectid, 0);
	अगर (IS_ERR(sb))
		वापस PTR_ERR(sb);
	set_extent_buffer_uptodate(sb);
	/*
	 * The sb extent buffer is artअगरicial and just used to पढ़ो the प्रणाली array.
	 * set_extent_buffer_uptodate() call करोes not properly mark all it's
	 * pages up-to-date when the page is larger: extent करोes not cover the
	 * whole page and consequently check_page_uptodate करोes not find all
	 * the page's extents up-to-date (the hole beyond sb),
	 * ग_लिखो_extent_buffer then triggers a WARN_ON.
	 *
	 * Regular लघु extents go through mark_extent_buffer_dirty/ग_लिखोback cycle,
	 * but sb spans only this function. Add an explicit SetPageUptodate call
	 * to silence the warning eg. on PowerPC 64.
	 */
	अगर (PAGE_SIZE > BTRFS_SUPER_INFO_SIZE)
		SetPageUptodate(sb->pages[0]);

	ग_लिखो_extent_buffer(sb, super_copy, 0, BTRFS_SUPER_INFO_SIZE);
	array_size = btrfs_super_sys_array_size(super_copy);

	array_ptr = super_copy->sys_chunk_array;
	sb_array_offset = दुरत्व(काष्ठा btrfs_super_block, sys_chunk_array);
	cur_offset = 0;

	जबतक (cur_offset < array_size) अणु
		disk_key = (काष्ठा btrfs_disk_key *)array_ptr;
		len = माप(*disk_key);
		अगर (cur_offset + len > array_size)
			जाओ out_लघु_पढ़ो;

		btrfs_disk_key_to_cpu(&key, disk_key);

		array_ptr += len;
		sb_array_offset += len;
		cur_offset += len;

		अगर (key.type != BTRFS_CHUNK_ITEM_KEY) अणु
			btrfs_err(fs_info,
			    "unexpected item type %u in sys_array at offset %u",
				  (u32)key.type, cur_offset);
			ret = -EIO;
			अवरोध;
		पूर्ण

		chunk = (काष्ठा btrfs_chunk *)sb_array_offset;
		/*
		 * At least one btrfs_chunk with one stripe must be present,
		 * exact stripe count check comes afterwards
		 */
		len = btrfs_chunk_item_size(1);
		अगर (cur_offset + len > array_size)
			जाओ out_लघु_पढ़ो;

		num_stripes = btrfs_chunk_num_stripes(sb, chunk);
		अगर (!num_stripes) अणु
			btrfs_err(fs_info,
			"invalid number of stripes %u in sys_array at offset %u",
				  num_stripes, cur_offset);
			ret = -EIO;
			अवरोध;
		पूर्ण

		type = btrfs_chunk_type(sb, chunk);
		अगर ((type & BTRFS_BLOCK_GROUP_SYSTEM) == 0) अणु
			btrfs_err(fs_info,
			"invalid chunk type %llu in sys_array at offset %u",
				  type, cur_offset);
			ret = -EIO;
			अवरोध;
		पूर्ण

		len = btrfs_chunk_item_size(num_stripes);
		अगर (cur_offset + len > array_size)
			जाओ out_लघु_पढ़ो;

		ret = पढ़ो_one_chunk(&key, sb, chunk);
		अगर (ret)
			अवरोध;

		array_ptr += len;
		sb_array_offset += len;
		cur_offset += len;
	पूर्ण
	clear_extent_buffer_uptodate(sb);
	मुक्त_extent_buffer_stale(sb);
	वापस ret;

out_लघु_पढ़ो:
	btrfs_err(fs_info, "sys_array too short to read %u bytes at offset %u",
			len, cur_offset);
	clear_extent_buffer_uptodate(sb);
	मुक्त_extent_buffer_stale(sb);
	वापस -EIO;
पूर्ण

/*
 * Check अगर all chunks in the fs are OK क्रम पढ़ो-ग_लिखो degraded mount
 *
 * If the @failing_dev is specअगरied, it's accounted as missing.
 *
 * Return true अगर all chunks meet the minimal RW mount requirements.
 * Return false अगर any chunk करोesn't meet the minimal RW mount requirements.
 */
bool btrfs_check_rw_degradable(काष्ठा btrfs_fs_info *fs_info,
					काष्ठा btrfs_device *failing_dev)
अणु
	काष्ठा extent_map_tree *map_tree = &fs_info->mapping_tree;
	काष्ठा extent_map *em;
	u64 next_start = 0;
	bool ret = true;

	पढ़ो_lock(&map_tree->lock);
	em = lookup_extent_mapping(map_tree, 0, (u64)-1);
	पढ़ो_unlock(&map_tree->lock);
	/* No chunk at all? Return false anyway */
	अगर (!em) अणु
		ret = false;
		जाओ out;
	पूर्ण
	जबतक (em) अणु
		काष्ठा map_lookup *map;
		पूर्णांक missing = 0;
		पूर्णांक max_tolerated;
		पूर्णांक i;

		map = em->map_lookup;
		max_tolerated =
			btrfs_get_num_tolerated_disk_barrier_failures(
					map->type);
		क्रम (i = 0; i < map->num_stripes; i++) अणु
			काष्ठा btrfs_device *dev = map->stripes[i].dev;

			अगर (!dev || !dev->bdev ||
			    test_bit(BTRFS_DEV_STATE_MISSING, &dev->dev_state) ||
			    dev->last_flush_error)
				missing++;
			अन्यथा अगर (failing_dev && failing_dev == dev)
				missing++;
		पूर्ण
		अगर (missing > max_tolerated) अणु
			अगर (!failing_dev)
				btrfs_warn(fs_info,
	"chunk %llu missing %d devices, max tolerance is %d for writable mount",
				   em->start, missing, max_tolerated);
			मुक्त_extent_map(em);
			ret = false;
			जाओ out;
		पूर्ण
		next_start = extent_map_end(em);
		मुक्त_extent_map(em);

		पढ़ो_lock(&map_tree->lock);
		em = lookup_extent_mapping(map_tree, next_start,
					   (u64)(-1) - next_start);
		पढ़ो_unlock(&map_tree->lock);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम पढ़ोahead_tree_node_children(काष्ठा extent_buffer *node)
अणु
	पूर्णांक i;
	स्थिर पूर्णांक nr_items = btrfs_header_nritems(node);

	क्रम (i = 0; i < nr_items; i++)
		btrfs_पढ़ोahead_node_child(node, i);
पूर्ण

पूर्णांक btrfs_पढ़ो_chunk_tree(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_root *root = fs_info->chunk_root;
	काष्ठा btrfs_path *path;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	पूर्णांक ret;
	पूर्णांक slot;
	u64 total_dev = 0;
	u64 last_ra_node = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	/*
	 * uuid_mutex is needed only अगर we are mounting a sprout FS
	 * otherwise we करोn't need it.
	 */
	mutex_lock(&uuid_mutex);

	/*
	 * It is possible क्रम mount and umount to race in such a way that
	 * we execute this code path, but खोलो_fs_devices failed to clear
	 * total_rw_bytes. We certainly want it cleared beक्रमe पढ़ोing the
	 * device items, so clear it here.
	 */
	fs_info->fs_devices->total_rw_bytes = 0;

	/*
	 * Read all device items, and then all the chunk items. All
	 * device items are found beक्रमe any chunk item (their object id
	 * is smaller than the lowest possible object id क्रम a chunk
	 * item - BTRFS_FIRST_CHUNK_TREE_OBJECTID).
	 */
	key.objectid = BTRFS_DEV_ITEMS_OBJECTID;
	key.offset = 0;
	key.type = 0;
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ error;
	जबतक (1) अणु
		काष्ठा extent_buffer *node;

		leaf = path->nodes[0];
		slot = path->slots[0];
		अगर (slot >= btrfs_header_nritems(leaf)) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret == 0)
				जारी;
			अगर (ret < 0)
				जाओ error;
			अवरोध;
		पूर्ण
		/*
		 * The nodes on level 1 are not locked but we करोn't need to करो
		 * that during mount समय as nothing अन्यथा can access the tree
		 */
		node = path->nodes[1];
		अगर (node) अणु
			अगर (last_ra_node != node->start) अणु
				पढ़ोahead_tree_node_children(node);
				last_ra_node = node->start;
			पूर्ण
		पूर्ण
		btrfs_item_key_to_cpu(leaf, &found_key, slot);
		अगर (found_key.type == BTRFS_DEV_ITEM_KEY) अणु
			काष्ठा btrfs_dev_item *dev_item;
			dev_item = btrfs_item_ptr(leaf, slot,
						  काष्ठा btrfs_dev_item);
			ret = पढ़ो_one_dev(leaf, dev_item);
			अगर (ret)
				जाओ error;
			total_dev++;
		पूर्ण अन्यथा अगर (found_key.type == BTRFS_CHUNK_ITEM_KEY) अणु
			काष्ठा btrfs_chunk *chunk;
			chunk = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_chunk);
			mutex_lock(&fs_info->chunk_mutex);
			ret = पढ़ो_one_chunk(&found_key, leaf, chunk);
			mutex_unlock(&fs_info->chunk_mutex);
			अगर (ret)
				जाओ error;
		पूर्ण
		path->slots[0]++;
	पूर्ण

	/*
	 * After loading chunk tree, we've got all device inक्रमmation,
	 * करो another round of validation checks.
	 */
	अगर (total_dev != fs_info->fs_devices->total_devices) अणु
		btrfs_err(fs_info,
	   "super_num_devices %llu mismatch with num_devices %llu found here",
			  btrfs_super_num_devices(fs_info->super_copy),
			  total_dev);
		ret = -EINVAL;
		जाओ error;
	पूर्ण
	अगर (btrfs_super_total_bytes(fs_info->super_copy) <
	    fs_info->fs_devices->total_rw_bytes) अणु
		btrfs_err(fs_info,
	"super_total_bytes %llu mismatch with fs_devices total_rw_bytes %llu",
			  btrfs_super_total_bytes(fs_info->super_copy),
			  fs_info->fs_devices->total_rw_bytes);
		ret = -EINVAL;
		जाओ error;
	पूर्ण
	ret = 0;
error:
	mutex_unlock(&uuid_mutex);

	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

व्योम btrfs_init_devices_late(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices, *seed_devs;
	काष्ठा btrfs_device *device;

	fs_devices->fs_info = fs_info;

	mutex_lock(&fs_devices->device_list_mutex);
	list_क्रम_each_entry(device, &fs_devices->devices, dev_list)
		device->fs_info = fs_info;

	list_क्रम_each_entry(seed_devs, &fs_devices->seed_list, seed_list) अणु
		list_क्रम_each_entry(device, &seed_devs->devices, dev_list)
			device->fs_info = fs_info;

		seed_devs->fs_info = fs_info;
	पूर्ण
	mutex_unlock(&fs_devices->device_list_mutex);
पूर्ण

अटल u64 btrfs_dev_stats_value(स्थिर काष्ठा extent_buffer *eb,
				 स्थिर काष्ठा btrfs_dev_stats_item *ptr,
				 पूर्णांक index)
अणु
	u64 val;

	पढ़ो_extent_buffer(eb, &val,
			   दुरत्व(काष्ठा btrfs_dev_stats_item, values) +
			    ((अचिन्हित दीर्घ)ptr) + (index * माप(u64)),
			   माप(val));
	वापस val;
पूर्ण

अटल व्योम btrfs_set_dev_stats_value(काष्ठा extent_buffer *eb,
				      काष्ठा btrfs_dev_stats_item *ptr,
				      पूर्णांक index, u64 val)
अणु
	ग_लिखो_extent_buffer(eb, &val,
			    दुरत्व(काष्ठा btrfs_dev_stats_item, values) +
			     ((अचिन्हित दीर्घ)ptr) + (index * माप(u64)),
			    माप(val));
पूर्ण

अटल पूर्णांक btrfs_device_init_dev_stats(काष्ठा btrfs_device *device,
				       काष्ठा btrfs_path *path)
अणु
	काष्ठा btrfs_dev_stats_item *ptr;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_key key;
	पूर्णांक item_size;
	पूर्णांक i, ret, slot;

	अगर (!device->fs_info->dev_root)
		वापस 0;

	key.objectid = BTRFS_DEV_STATS_OBJECTID;
	key.type = BTRFS_PERSISTENT_ITEM_KEY;
	key.offset = device->devid;
	ret = btrfs_search_slot(शून्य, device->fs_info->dev_root, &key, path, 0, 0);
	अगर (ret) अणु
		क्रम (i = 0; i < BTRFS_DEV_STAT_VALUES_MAX; i++)
			btrfs_dev_stat_set(device, i, 0);
		device->dev_stats_valid = 1;
		btrfs_release_path(path);
		वापस ret < 0 ? ret : 0;
	पूर्ण
	slot = path->slots[0];
	eb = path->nodes[0];
	item_size = btrfs_item_size_nr(eb, slot);

	ptr = btrfs_item_ptr(eb, slot, काष्ठा btrfs_dev_stats_item);

	क्रम (i = 0; i < BTRFS_DEV_STAT_VALUES_MAX; i++) अणु
		अगर (item_size >= (1 + i) * माप(__le64))
			btrfs_dev_stat_set(device, i,
					   btrfs_dev_stats_value(eb, ptr, i));
		अन्यथा
			btrfs_dev_stat_set(device, i, 0);
	पूर्ण

	device->dev_stats_valid = 1;
	btrfs_dev_stat_prपूर्णांक_on_load(device);
	btrfs_release_path(path);

	वापस 0;
पूर्ण

पूर्णांक btrfs_init_dev_stats(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices, *seed_devs;
	काष्ठा btrfs_device *device;
	काष्ठा btrfs_path *path = शून्य;
	पूर्णांक ret = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	mutex_lock(&fs_devices->device_list_mutex);
	list_क्रम_each_entry(device, &fs_devices->devices, dev_list) अणु
		ret = btrfs_device_init_dev_stats(device, path);
		अगर (ret)
			जाओ out;
	पूर्ण
	list_क्रम_each_entry(seed_devs, &fs_devices->seed_list, seed_list) अणु
		list_क्रम_each_entry(device, &seed_devs->devices, dev_list) अणु
			ret = btrfs_device_init_dev_stats(device, path);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&fs_devices->device_list_mutex);

	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक update_dev_stat_item(काष्ठा btrfs_trans_handle *trans,
				काष्ठा btrfs_device *device)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_root *dev_root = fs_info->dev_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_dev_stats_item *ptr;
	पूर्णांक ret;
	पूर्णांक i;

	key.objectid = BTRFS_DEV_STATS_OBJECTID;
	key.type = BTRFS_PERSISTENT_ITEM_KEY;
	key.offset = device->devid;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;
	ret = btrfs_search_slot(trans, dev_root, &key, path, -1, 1);
	अगर (ret < 0) अणु
		btrfs_warn_in_rcu(fs_info,
			"error %d while searching for dev_stats item for device %s",
			      ret, rcu_str_deref(device->name));
		जाओ out;
	पूर्ण

	अगर (ret == 0 &&
	    btrfs_item_size_nr(path->nodes[0], path->slots[0]) < माप(*ptr)) अणु
		/* need to delete old one and insert a new one */
		ret = btrfs_del_item(trans, dev_root, path);
		अगर (ret != 0) अणु
			btrfs_warn_in_rcu(fs_info,
				"delete too small dev_stats item for device %s failed %d",
				      rcu_str_deref(device->name), ret);
			जाओ out;
		पूर्ण
		ret = 1;
	पूर्ण

	अगर (ret == 1) अणु
		/* need to insert a new item */
		btrfs_release_path(path);
		ret = btrfs_insert_empty_item(trans, dev_root, path,
					      &key, माप(*ptr));
		अगर (ret < 0) अणु
			btrfs_warn_in_rcu(fs_info,
				"insert dev_stats item for device %s failed %d",
				rcu_str_deref(device->name), ret);
			जाओ out;
		पूर्ण
	पूर्ण

	eb = path->nodes[0];
	ptr = btrfs_item_ptr(eb, path->slots[0], काष्ठा btrfs_dev_stats_item);
	क्रम (i = 0; i < BTRFS_DEV_STAT_VALUES_MAX; i++)
		btrfs_set_dev_stats_value(eb, ptr, i,
					  btrfs_dev_stat_पढ़ो(device, i));
	btrfs_mark_buffer_dirty(eb);

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * called from commit_transaction. Writes all changed device stats to disk.
 */
पूर्णांक btrfs_run_dev_stats(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	काष्ठा btrfs_device *device;
	पूर्णांक stats_cnt;
	पूर्णांक ret = 0;

	mutex_lock(&fs_devices->device_list_mutex);
	list_क्रम_each_entry(device, &fs_devices->devices, dev_list) अणु
		stats_cnt = atomic_पढ़ो(&device->dev_stats_ccnt);
		अगर (!device->dev_stats_valid || stats_cnt == 0)
			जारी;


		/*
		 * There is a LOAD-LOAD control dependency between the value of
		 * dev_stats_ccnt and updating the on-disk values which requires
		 * पढ़ोing the in-memory counters. Such control dependencies
		 * require explicit पढ़ो memory barriers.
		 *
		 * This memory barriers pairs with smp_mb__beक्रमe_atomic in
		 * btrfs_dev_stat_inc/btrfs_dev_stat_set and with the full
		 * barrier implied by atomic_xchg in
		 * btrfs_dev_stats_पढ़ो_and_reset
		 */
		smp_rmb();

		ret = update_dev_stat_item(trans, device);
		अगर (!ret)
			atomic_sub(stats_cnt, &device->dev_stats_ccnt);
	पूर्ण
	mutex_unlock(&fs_devices->device_list_mutex);

	वापस ret;
पूर्ण

व्योम btrfs_dev_stat_inc_and_prपूर्णांक(काष्ठा btrfs_device *dev, पूर्णांक index)
अणु
	btrfs_dev_stat_inc(dev, index);
	btrfs_dev_stat_prपूर्णांक_on_error(dev);
पूर्ण

अटल व्योम btrfs_dev_stat_prपूर्णांक_on_error(काष्ठा btrfs_device *dev)
अणु
	अगर (!dev->dev_stats_valid)
		वापस;
	btrfs_err_rl_in_rcu(dev->fs_info,
		"bdev %s errs: wr %u, rd %u, flush %u, corrupt %u, gen %u",
			   rcu_str_deref(dev->name),
			   btrfs_dev_stat_पढ़ो(dev, BTRFS_DEV_STAT_WRITE_ERRS),
			   btrfs_dev_stat_पढ़ो(dev, BTRFS_DEV_STAT_READ_ERRS),
			   btrfs_dev_stat_पढ़ो(dev, BTRFS_DEV_STAT_FLUSH_ERRS),
			   btrfs_dev_stat_पढ़ो(dev, BTRFS_DEV_STAT_CORRUPTION_ERRS),
			   btrfs_dev_stat_पढ़ो(dev, BTRFS_DEV_STAT_GENERATION_ERRS));
पूर्ण

अटल व्योम btrfs_dev_stat_prपूर्णांक_on_load(काष्ठा btrfs_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BTRFS_DEV_STAT_VALUES_MAX; i++)
		अगर (btrfs_dev_stat_पढ़ो(dev, i) != 0)
			अवरोध;
	अगर (i == BTRFS_DEV_STAT_VALUES_MAX)
		वापस; /* all values == 0, suppress message */

	btrfs_info_in_rcu(dev->fs_info,
		"bdev %s errs: wr %u, rd %u, flush %u, corrupt %u, gen %u",
	       rcu_str_deref(dev->name),
	       btrfs_dev_stat_पढ़ो(dev, BTRFS_DEV_STAT_WRITE_ERRS),
	       btrfs_dev_stat_पढ़ो(dev, BTRFS_DEV_STAT_READ_ERRS),
	       btrfs_dev_stat_पढ़ो(dev, BTRFS_DEV_STAT_FLUSH_ERRS),
	       btrfs_dev_stat_पढ़ो(dev, BTRFS_DEV_STAT_CORRUPTION_ERRS),
	       btrfs_dev_stat_पढ़ो(dev, BTRFS_DEV_STAT_GENERATION_ERRS));
पूर्ण

पूर्णांक btrfs_get_dev_stats(काष्ठा btrfs_fs_info *fs_info,
			काष्ठा btrfs_ioctl_get_dev_stats *stats)
अणु
	काष्ठा btrfs_device *dev;
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	पूर्णांक i;

	mutex_lock(&fs_devices->device_list_mutex);
	dev = btrfs_find_device(fs_info->fs_devices, stats->devid, शून्य, शून्य);
	mutex_unlock(&fs_devices->device_list_mutex);

	अगर (!dev) अणु
		btrfs_warn(fs_info, "get dev_stats failed, device not found");
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (!dev->dev_stats_valid) अणु
		btrfs_warn(fs_info, "get dev_stats failed, not yet valid");
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (stats->flags & BTRFS_DEV_STATS_RESET) अणु
		क्रम (i = 0; i < BTRFS_DEV_STAT_VALUES_MAX; i++) अणु
			अगर (stats->nr_items > i)
				stats->values[i] =
					btrfs_dev_stat_पढ़ो_and_reset(dev, i);
			अन्यथा
				btrfs_dev_stat_set(dev, i, 0);
		पूर्ण
		btrfs_info(fs_info, "device stats zeroed by %s (%d)",
			   current->comm, task_pid_nr(current));
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < BTRFS_DEV_STAT_VALUES_MAX; i++)
			अगर (stats->nr_items > i)
				stats->values[i] = btrfs_dev_stat_पढ़ो(dev, i);
	पूर्ण
	अगर (stats->nr_items > BTRFS_DEV_STAT_VALUES_MAX)
		stats->nr_items = BTRFS_DEV_STAT_VALUES_MAX;
	वापस 0;
पूर्ण

/*
 * Update the size and bytes used क्रम each device where it changed.  This is
 * delayed since we would otherwise get errors जबतक writing out the
 * superblocks.
 *
 * Must be invoked during transaction commit.
 */
व्योम btrfs_commit_device_sizes(काष्ठा btrfs_transaction *trans)
अणु
	काष्ठा btrfs_device *curr, *next;

	ASSERT(trans->state == TRANS_STATE_COMMIT_DOING);

	अगर (list_empty(&trans->dev_update_list))
		वापस;

	/*
	 * We करोn't need the device_list_mutex here.  This list is owned by the
	 * transaction and the transaction must complete beक्रमe the device is
	 * released.
	 */
	mutex_lock(&trans->fs_info->chunk_mutex);
	list_क्रम_each_entry_safe(curr, next, &trans->dev_update_list,
				 post_commit_list) अणु
		list_del_init(&curr->post_commit_list);
		curr->commit_total_bytes = curr->disk_total_bytes;
		curr->commit_bytes_used = curr->bytes_used;
	पूर्ण
	mutex_unlock(&trans->fs_info->chunk_mutex);
पूर्ण

/*
 * Multiplicity factor क्रम simple profiles: DUP, RAID1-like and RAID10.
 */
पूर्णांक btrfs_bg_type_to_factor(u64 flags)
अणु
	स्थिर पूर्णांक index = btrfs_bg_flags_to_raid_index(flags);

	वापस btrfs_raid_array[index].ncopies;
पूर्ण



अटल पूर्णांक verअगरy_one_dev_extent(काष्ठा btrfs_fs_info *fs_info,
				 u64 chunk_offset, u64 devid,
				 u64 physical_offset, u64 physical_len)
अणु
	काष्ठा extent_map_tree *em_tree = &fs_info->mapping_tree;
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	काष्ठा btrfs_device *dev;
	u64 stripe_len;
	bool found = false;
	पूर्णांक ret = 0;
	पूर्णांक i;

	पढ़ो_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, chunk_offset, 1);
	पढ़ो_unlock(&em_tree->lock);

	अगर (!em) अणु
		btrfs_err(fs_info,
"dev extent physical offset %llu on devid %llu doesn't have corresponding chunk",
			  physical_offset, devid);
		ret = -EUCLEAN;
		जाओ out;
	पूर्ण

	map = em->map_lookup;
	stripe_len = calc_stripe_length(map->type, em->len, map->num_stripes);
	अगर (physical_len != stripe_len) अणु
		btrfs_err(fs_info,
"dev extent physical offset %llu on devid %llu length doesn't match chunk %llu, have %llu expect %llu",
			  physical_offset, devid, em->start, physical_len,
			  stripe_len);
		ret = -EUCLEAN;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < map->num_stripes; i++) अणु
		अगर (map->stripes[i].dev->devid == devid &&
		    map->stripes[i].physical == physical_offset) अणु
			found = true;
			अगर (map->verअगरied_stripes >= map->num_stripes) अणु
				btrfs_err(fs_info,
				"too many dev extents for chunk %llu found",
					  em->start);
				ret = -EUCLEAN;
				जाओ out;
			पूर्ण
			map->verअगरied_stripes++;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		btrfs_err(fs_info,
	"dev extent physical offset %llu devid %llu has no corresponding chunk",
			physical_offset, devid);
		ret = -EUCLEAN;
	पूर्ण

	/* Make sure no dev extent is beyond device bondary */
	dev = btrfs_find_device(fs_info->fs_devices, devid, शून्य, शून्य);
	अगर (!dev) अणु
		btrfs_err(fs_info, "failed to find devid %llu", devid);
		ret = -EUCLEAN;
		जाओ out;
	पूर्ण

	अगर (physical_offset + physical_len > dev->disk_total_bytes) अणु
		btrfs_err(fs_info,
"dev extent devid %llu physical offset %llu len %llu is beyond device boundary %llu",
			  devid, physical_offset, physical_len,
			  dev->disk_total_bytes);
		ret = -EUCLEAN;
		जाओ out;
	पूर्ण

	अगर (dev->zone_info) अणु
		u64 zone_size = dev->zone_info->zone_size;

		अगर (!IS_ALIGNED(physical_offset, zone_size) ||
		    !IS_ALIGNED(physical_len, zone_size)) अणु
			btrfs_err(fs_info,
"zoned: dev extent devid %llu physical offset %llu len %llu is not aligned to device zone",
				  devid, physical_offset, physical_len);
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	मुक्त_extent_map(em);
	वापस ret;
पूर्ण

अटल पूर्णांक verअगरy_chunk_dev_extent_mapping(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा extent_map_tree *em_tree = &fs_info->mapping_tree;
	काष्ठा extent_map *em;
	काष्ठा rb_node *node;
	पूर्णांक ret = 0;

	पढ़ो_lock(&em_tree->lock);
	क्रम (node = rb_first_cached(&em_tree->map); node; node = rb_next(node)) अणु
		em = rb_entry(node, काष्ठा extent_map, rb_node);
		अगर (em->map_lookup->num_stripes !=
		    em->map_lookup->verअगरied_stripes) अणु
			btrfs_err(fs_info,
			"chunk %llu has missing dev extent, have %d expect %d",
				  em->start, em->map_lookup->verअगरied_stripes,
				  em->map_lookup->num_stripes);
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	पढ़ो_unlock(&em_tree->lock);
	वापस ret;
पूर्ण

/*
 * Ensure that all dev extents are mapped to correct chunk, otherwise
 * later chunk allocation/मुक्त would cause unexpected behavior.
 *
 * NOTE: This will iterate through the whole device tree, which should be of
 * the same size level as the chunk tree.  This slightly increases mount समय.
 */
पूर्णांक btrfs_verअगरy_dev_extents(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_root *root = fs_info->dev_root;
	काष्ठा btrfs_key key;
	u64 prev_devid = 0;
	u64 prev_dev_ext_end = 0;
	पूर्णांक ret = 0;

	/*
	 * We करोn't have a dev_root because we mounted with ignorebadroots and
	 * failed to load the root, so we want to skip the verअगरication in this
	 * हाल क्रम sure.
	 *
	 * However अगर the dev root is fine, but the tree itself is corrupted
	 * we'd still fail to mount.  This verअगरication is only to make sure
	 * ग_लिखोs can happen safely, so instead just bypass this check
	 * completely in the हाल of IGNOREBADROOTS.
	 */
	अगर (btrfs_test_opt(fs_info, IGNOREBADROOTS))
		वापस 0;

	key.objectid = 1;
	key.type = BTRFS_DEV_EXTENT_KEY;
	key.offset = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	path->पढ़ोa = READA_FORWARD;
	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ out;

	अगर (path->slots[0] >= btrfs_header_nritems(path->nodes[0])) अणु
		ret = btrfs_next_item(root, path);
		अगर (ret < 0)
			जाओ out;
		/* No dev extents at all? Not good */
		अगर (ret > 0) अणु
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण
	पूर्ण
	जबतक (1) अणु
		काष्ठा extent_buffer *leaf = path->nodes[0];
		काष्ठा btrfs_dev_extent *dext;
		पूर्णांक slot = path->slots[0];
		u64 chunk_offset;
		u64 physical_offset;
		u64 physical_len;
		u64 devid;

		btrfs_item_key_to_cpu(leaf, &key, slot);
		अगर (key.type != BTRFS_DEV_EXTENT_KEY)
			अवरोध;
		devid = key.objectid;
		physical_offset = key.offset;

		dext = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_dev_extent);
		chunk_offset = btrfs_dev_extent_chunk_offset(leaf, dext);
		physical_len = btrfs_dev_extent_length(leaf, dext);

		/* Check अगर this dev extent overlaps with the previous one */
		अगर (devid == prev_devid && physical_offset < prev_dev_ext_end) अणु
			btrfs_err(fs_info,
"dev extent devid %llu physical offset %llu overlap with previous dev extent end %llu",
				  devid, physical_offset, prev_dev_ext_end);
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण

		ret = verअगरy_one_dev_extent(fs_info, chunk_offset, devid,
					    physical_offset, physical_len);
		अगर (ret < 0)
			जाओ out;
		prev_devid = devid;
		prev_dev_ext_end = physical_offset + physical_len;

		ret = btrfs_next_item(root, path);
		अगर (ret < 0)
			जाओ out;
		अगर (ret > 0) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Ensure all chunks have corresponding dev extents */
	ret = verअगरy_chunk_dev_extent_mapping(fs_info);
out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * Check whether the given block group or device is pinned by any inode being
 * used as a swapfile.
 */
bool btrfs_pinned_by_swapfile(काष्ठा btrfs_fs_info *fs_info, व्योम *ptr)
अणु
	काष्ठा btrfs_swapfile_pin *sp;
	काष्ठा rb_node *node;

	spin_lock(&fs_info->swapfile_pins_lock);
	node = fs_info->swapfile_pins.rb_node;
	जबतक (node) अणु
		sp = rb_entry(node, काष्ठा btrfs_swapfile_pin, node);
		अगर (ptr < sp->ptr)
			node = node->rb_left;
		अन्यथा अगर (ptr > sp->ptr)
			node = node->rb_right;
		अन्यथा
			अवरोध;
	पूर्ण
	spin_unlock(&fs_info->swapfile_pins_lock);
	वापस node != शून्य;
पूर्ण

अटल पूर्णांक relocating_repair_kthपढ़ो(व्योम *data)
अणु
	काष्ठा btrfs_block_group *cache = (काष्ठा btrfs_block_group *)data;
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	u64 target;
	पूर्णांक ret = 0;

	target = cache->start;
	btrfs_put_block_group(cache);

	अगर (!btrfs_exclop_start(fs_info, BTRFS_EXCLOP_BALANCE)) अणु
		btrfs_info(fs_info,
			   "zoned: skip relocating block group %llu to repair: EBUSY",
			   target);
		वापस -EBUSY;
	पूर्ण

	mutex_lock(&fs_info->reclaim_bgs_lock);

	/* Ensure block group still exists */
	cache = btrfs_lookup_block_group(fs_info, target);
	अगर (!cache)
		जाओ out;

	अगर (!cache->relocating_repair)
		जाओ out;

	ret = btrfs_may_alloc_data_chunk(fs_info, target);
	अगर (ret < 0)
		जाओ out;

	btrfs_info(fs_info,
		   "zoned: relocating block group %llu to repair IO failure",
		   target);
	ret = btrfs_relocate_chunk(fs_info, target);

out:
	अगर (cache)
		btrfs_put_block_group(cache);
	mutex_unlock(&fs_info->reclaim_bgs_lock);
	btrfs_exclop_finish(fs_info);

	वापस ret;
पूर्ण

पूर्णांक btrfs_repair_one_zone(काष्ठा btrfs_fs_info *fs_info, u64 logical)
अणु
	काष्ठा btrfs_block_group *cache;

	/* Do not attempt to repair in degraded state */
	अगर (btrfs_test_opt(fs_info, DEGRADED))
		वापस 0;

	cache = btrfs_lookup_block_group(fs_info, logical);
	अगर (!cache)
		वापस 0;

	spin_lock(&cache->lock);
	अगर (cache->relocating_repair) अणु
		spin_unlock(&cache->lock);
		btrfs_put_block_group(cache);
		वापस 0;
	पूर्ण
	cache->relocating_repair = 1;
	spin_unlock(&cache->lock);

	kthपढ़ो_run(relocating_repair_kthपढ़ो, cache,
		    "btrfs-relocating-repair");

	वापस 0;
पूर्ण
