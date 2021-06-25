<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/sched/mm.h>
#समावेश "ctree.h"
#समावेश "volumes.h"
#समावेश "zoned.h"
#समावेश "rcu-string.h"
#समावेश "disk-io.h"
#समावेश "block-group.h"
#समावेश "transaction.h"
#समावेश "dev-replace.h"
#समावेश "space-info.h"

/* Maximum number of zones to report per blkdev_report_zones() call */
#घोषणा BTRFS_REPORT_NR_ZONES   4096
/* Invalid allocation poपूर्णांकer value क्रम missing devices */
#घोषणा WP_MISSING_DEV ((u64)-1)
/* Pseuकरो ग_लिखो poपूर्णांकer value क्रम conventional zone */
#घोषणा WP_CONVENTIONAL ((u64)-2)

/*
 * Location of the first zone of superblock logging zone pairs.
 *
 * - primary superblock:    0B (zone 0)
 * - first copy:          512G (zone starting at that offset)
 * - second copy:           4T (zone starting at that offset)
 */
#घोषणा BTRFS_SB_LOG_PRIMARY_OFFSET	(0ULL)
#घोषणा BTRFS_SB_LOG_FIRST_OFFSET	(512ULL * SZ_1G)
#घोषणा BTRFS_SB_LOG_SECOND_OFFSET	(4096ULL * SZ_1G)

#घोषणा BTRFS_SB_LOG_FIRST_SHIFT	स्थिर_ilog2(BTRFS_SB_LOG_FIRST_OFFSET)
#घोषणा BTRFS_SB_LOG_SECOND_SHIFT	स्थिर_ilog2(BTRFS_SB_LOG_SECOND_OFFSET)

/* Number of superblock log zones */
#घोषणा BTRFS_NR_SB_LOG_ZONES 2

/*
 * Maximum supported zone size. Currently, SMR disks have a zone size of
 * 256MiB, and we are expecting ZNS drives to be in the 1-4GiB range. We करो not
 * expect the zone size to become larger than 8GiB in the near future.
 */
#घोषणा BTRFS_MAX_ZONE_SIZE		SZ_8G

अटल पूर्णांक copy_zone_info_cb(काष्ठा blk_zone *zone, अचिन्हित पूर्णांक idx, व्योम *data)
अणु
	काष्ठा blk_zone *zones = data;

	स_नकल(&zones[idx], zone, माप(*zone));

	वापस 0;
पूर्ण

अटल पूर्णांक sb_ग_लिखो_poपूर्णांकer(काष्ठा block_device *bdev, काष्ठा blk_zone *zones,
			    u64 *wp_ret)
अणु
	bool empty[BTRFS_NR_SB_LOG_ZONES];
	bool full[BTRFS_NR_SB_LOG_ZONES];
	sector_t sector;

	ASSERT(zones[0].type != BLK_ZONE_TYPE_CONVENTIONAL &&
	       zones[1].type != BLK_ZONE_TYPE_CONVENTIONAL);

	empty[0] = (zones[0].cond == BLK_ZONE_COND_EMPTY);
	empty[1] = (zones[1].cond == BLK_ZONE_COND_EMPTY);
	full[0] = (zones[0].cond == BLK_ZONE_COND_FULL);
	full[1] = (zones[1].cond == BLK_ZONE_COND_FULL);

	/*
	 * Possible states of log buffer zones
	 *
	 *           Empty[0]  In use[0]  Full[0]
	 * Empty[1]         *          x        0
	 * In use[1]        0          x        0
	 * Full[1]          1          1        C
	 *
	 * Log position:
	 *   *: Special हाल, no superblock is written
	 *   0: Use ग_लिखो poपूर्णांकer of zones[0]
	 *   1: Use ग_लिखो poपूर्णांकer of zones[1]
	 *   C: Compare super blcoks from zones[0] and zones[1], use the latest
	 *      one determined by generation
	 *   x: Invalid state
	 */

	अगर (empty[0] && empty[1]) अणु
		/* Special हाल to distinguish no superblock to पढ़ो */
		*wp_ret = zones[0].start << SECTOR_SHIFT;
		वापस -ENOENT;
	पूर्ण अन्यथा अगर (full[0] && full[1]) अणु
		/* Compare two super blocks */
		काष्ठा address_space *mapping = bdev->bd_inode->i_mapping;
		काष्ठा page *page[BTRFS_NR_SB_LOG_ZONES];
		काष्ठा btrfs_super_block *super[BTRFS_NR_SB_LOG_ZONES];
		पूर्णांक i;

		क्रम (i = 0; i < BTRFS_NR_SB_LOG_ZONES; i++) अणु
			u64 bytenr;

			bytenr = ((zones[i].start + zones[i].len)
				   << SECTOR_SHIFT) - BTRFS_SUPER_INFO_SIZE;

			page[i] = पढ़ो_cache_page_gfp(mapping,
					bytenr >> PAGE_SHIFT, GFP_NOFS);
			अगर (IS_ERR(page[i])) अणु
				अगर (i == 1)
					btrfs_release_disk_super(super[0]);
				वापस PTR_ERR(page[i]);
			पूर्ण
			super[i] = page_address(page[i]);
		पूर्ण

		अगर (super[0]->generation > super[1]->generation)
			sector = zones[1].start;
		अन्यथा
			sector = zones[0].start;

		क्रम (i = 0; i < BTRFS_NR_SB_LOG_ZONES; i++)
			btrfs_release_disk_super(super[i]);
	पूर्ण अन्यथा अगर (!full[0] && (empty[1] || full[1])) अणु
		sector = zones[0].wp;
	पूर्ण अन्यथा अगर (full[0]) अणु
		sector = zones[1].wp;
	पूर्ण अन्यथा अणु
		वापस -EUCLEAN;
	पूर्ण
	*wp_ret = sector << SECTOR_SHIFT;
	वापस 0;
पूर्ण

/*
 * Get the first zone number of the superblock mirror
 */
अटल अंतरभूत u32 sb_zone_number(पूर्णांक shअगरt, पूर्णांक mirror)
अणु
	u64 zone;

	ASSERT(mirror < BTRFS_SUPER_MIRROR_MAX);
	चयन (mirror) अणु
	हाल 0: zone = 0; अवरोध;
	हाल 1: zone = 1ULL << (BTRFS_SB_LOG_FIRST_SHIFT - shअगरt); अवरोध;
	हाल 2: zone = 1ULL << (BTRFS_SB_LOG_SECOND_SHIFT - shअगरt); अवरोध;
	पूर्ण

	ASSERT(zone <= U32_MAX);

	वापस (u32)zone;
पूर्ण

अटल अंतरभूत sector_t zone_start_sector(u32 zone_number,
					 काष्ठा block_device *bdev)
अणु
	वापस (sector_t)zone_number << ilog2(bdev_zone_sectors(bdev));
पूर्ण

अटल अंतरभूत u64 zone_start_physical(u32 zone_number,
				      काष्ठा btrfs_zoned_device_info *zone_info)
अणु
	वापस (u64)zone_number << zone_info->zone_size_shअगरt;
पूर्ण

/*
 * Emulate blkdev_report_zones() क्रम a non-zoned device. It slices up the block
 * device पूर्णांकo अटल sized chunks and fake a conventional zone on each of
 * them.
 */
अटल पूर्णांक emulate_report_zones(काष्ठा btrfs_device *device, u64 pos,
				काष्ठा blk_zone *zones, अचिन्हित पूर्णांक nr_zones)
अणु
	स्थिर sector_t zone_sectors = device->fs_info->zone_size >> SECTOR_SHIFT;
	sector_t bdev_size = bdev_nr_sectors(device->bdev);
	अचिन्हित पूर्णांक i;

	pos >>= SECTOR_SHIFT;
	क्रम (i = 0; i < nr_zones; i++) अणु
		zones[i].start = i * zone_sectors + pos;
		zones[i].len = zone_sectors;
		zones[i].capacity = zone_sectors;
		zones[i].wp = zones[i].start + zone_sectors;
		zones[i].type = BLK_ZONE_TYPE_CONVENTIONAL;
		zones[i].cond = BLK_ZONE_COND_NOT_WP;

		अगर (zones[i].wp >= bdev_size) अणु
			i++;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक btrfs_get_dev_zones(काष्ठा btrfs_device *device, u64 pos,
			       काष्ठा blk_zone *zones, अचिन्हित पूर्णांक *nr_zones)
अणु
	पूर्णांक ret;

	अगर (!*nr_zones)
		वापस 0;

	अगर (!bdev_is_zoned(device->bdev)) अणु
		ret = emulate_report_zones(device, pos, zones, *nr_zones);
		*nr_zones = ret;
		वापस 0;
	पूर्ण

	ret = blkdev_report_zones(device->bdev, pos >> SECTOR_SHIFT, *nr_zones,
				  copy_zone_info_cb, zones);
	अगर (ret < 0) अणु
		btrfs_err_in_rcu(device->fs_info,
				 "zoned: failed to read zone %llu on %s (devid %llu)",
				 pos, rcu_str_deref(device->name),
				 device->devid);
		वापस ret;
	पूर्ण
	*nr_zones = ret;
	अगर (!ret)
		वापस -EIO;

	वापस 0;
पूर्ण

/* The emulated zone size is determined from the size of device extent */
अटल पूर्णांक calculate_emulated_zone_size(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_root *root = fs_info->dev_root;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *leaf;
	काष्ठा btrfs_dev_extent *dext;
	पूर्णांक ret = 0;

	key.objectid = 1;
	key.type = BTRFS_DEV_EXTENT_KEY;
	key.offset = 0;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

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

	leaf = path->nodes[0];
	dext = btrfs_item_ptr(leaf, path->slots[0], काष्ठा btrfs_dev_extent);
	fs_info->zone_size = btrfs_dev_extent_length(leaf, dext);
	ret = 0;

out:
	btrfs_मुक्त_path(path);

	वापस ret;
पूर्ण

पूर्णांक btrfs_get_dev_zone_info_all_devices(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	काष्ठा btrfs_device *device;
	पूर्णांक ret = 0;

	/* fs_info->zone_size might not set yet. Use the incomapt flag here. */
	अगर (!btrfs_fs_incompat(fs_info, ZONED))
		वापस 0;

	mutex_lock(&fs_devices->device_list_mutex);
	list_क्रम_each_entry(device, &fs_devices->devices, dev_list) अणु
		/* We can skip पढ़ोing of zone info क्रम missing devices */
		अगर (!device->bdev)
			जारी;

		ret = btrfs_get_dev_zone_info(device);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&fs_devices->device_list_mutex);

	वापस ret;
पूर्ण

पूर्णांक btrfs_get_dev_zone_info(काष्ठा btrfs_device *device)
अणु
	काष्ठा btrfs_fs_info *fs_info = device->fs_info;
	काष्ठा btrfs_zoned_device_info *zone_info = शून्य;
	काष्ठा block_device *bdev = device->bdev;
	काष्ठा request_queue *queue = bdev_get_queue(bdev);
	sector_t nr_sectors;
	sector_t sector = 0;
	काष्ठा blk_zone *zones = शून्य;
	अचिन्हित पूर्णांक i, nreported = 0, nr_zones;
	sector_t zone_sectors;
	अक्षर *model, *emulated;
	पूर्णांक ret;

	/*
	 * Cannot use btrfs_is_zoned here, since fs_info::zone_size might not
	 * yet be set.
	 */
	अगर (!btrfs_fs_incompat(fs_info, ZONED))
		वापस 0;

	अगर (device->zone_info)
		वापस 0;

	zone_info = kzalloc(माप(*zone_info), GFP_KERNEL);
	अगर (!zone_info)
		वापस -ENOMEM;

	अगर (!bdev_is_zoned(bdev)) अणु
		अगर (!fs_info->zone_size) अणु
			ret = calculate_emulated_zone_size(fs_info);
			अगर (ret)
				जाओ out;
		पूर्ण

		ASSERT(fs_info->zone_size);
		zone_sectors = fs_info->zone_size >> SECTOR_SHIFT;
	पूर्ण अन्यथा अणु
		zone_sectors = bdev_zone_sectors(bdev);
	पूर्ण

	/* Check अगर it's घातer of 2 (see is_घातer_of_2) */
	ASSERT(zone_sectors != 0 && (zone_sectors & (zone_sectors - 1)) == 0);
	zone_info->zone_size = zone_sectors << SECTOR_SHIFT;

	/* We reject devices with a zone size larger than 8GB */
	अगर (zone_info->zone_size > BTRFS_MAX_ZONE_SIZE) अणु
		btrfs_err_in_rcu(fs_info,
		"zoned: %s: zone size %llu larger than supported maximum %llu",
				 rcu_str_deref(device->name),
				 zone_info->zone_size, BTRFS_MAX_ZONE_SIZE);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	nr_sectors = bdev_nr_sectors(bdev);
	zone_info->zone_size_shअगरt = ilog2(zone_info->zone_size);
	zone_info->max_zone_append_size =
		(u64)queue_max_zone_append_sectors(queue) << SECTOR_SHIFT;
	zone_info->nr_zones = nr_sectors >> ilog2(zone_sectors);
	अगर (!IS_ALIGNED(nr_sectors, zone_sectors))
		zone_info->nr_zones++;

	अगर (bdev_is_zoned(bdev) && zone_info->max_zone_append_size == 0) अणु
		btrfs_err(fs_info, "zoned: device %pg does not support zone append",
			  bdev);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	zone_info->seq_zones = biपंचांगap_zalloc(zone_info->nr_zones, GFP_KERNEL);
	अगर (!zone_info->seq_zones) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	zone_info->empty_zones = biपंचांगap_zalloc(zone_info->nr_zones, GFP_KERNEL);
	अगर (!zone_info->empty_zones) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	zones = kसुस्मृति(BTRFS_REPORT_NR_ZONES, माप(काष्ठा blk_zone), GFP_KERNEL);
	अगर (!zones) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Get zones type */
	जबतक (sector < nr_sectors) अणु
		nr_zones = BTRFS_REPORT_NR_ZONES;
		ret = btrfs_get_dev_zones(device, sector << SECTOR_SHIFT, zones,
					  &nr_zones);
		अगर (ret)
			जाओ out;

		क्रम (i = 0; i < nr_zones; i++) अणु
			अगर (zones[i].type == BLK_ZONE_TYPE_SEQWRITE_REQ)
				__set_bit(nreported, zone_info->seq_zones);
			अगर (zones[i].cond == BLK_ZONE_COND_EMPTY)
				__set_bit(nreported, zone_info->empty_zones);
			nreported++;
		पूर्ण
		sector = zones[nr_zones - 1].start + zones[nr_zones - 1].len;
	पूर्ण

	अगर (nreported != zone_info->nr_zones) अणु
		btrfs_err_in_rcu(device->fs_info,
				 "inconsistent number of zones on %s (%u/%u)",
				 rcu_str_deref(device->name), nreported,
				 zone_info->nr_zones);
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* Validate superblock log */
	nr_zones = BTRFS_NR_SB_LOG_ZONES;
	क्रम (i = 0; i < BTRFS_SUPER_MIRROR_MAX; i++) अणु
		u32 sb_zone;
		u64 sb_wp;
		पूर्णांक sb_pos = BTRFS_NR_SB_LOG_ZONES * i;

		sb_zone = sb_zone_number(zone_info->zone_size_shअगरt, i);
		अगर (sb_zone + 1 >= zone_info->nr_zones)
			जारी;

		ret = btrfs_get_dev_zones(device,
					  zone_start_physical(sb_zone, zone_info),
					  &zone_info->sb_zones[sb_pos],
					  &nr_zones);
		अगर (ret)
			जाओ out;

		अगर (nr_zones != BTRFS_NR_SB_LOG_ZONES) अणु
			btrfs_err_in_rcu(device->fs_info,
	"zoned: failed to read super block log zone info at devid %llu zone %u",
					 device->devid, sb_zone);
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण

		/*
		 * If zones[0] is conventional, always use the beggining of the
		 * zone to record superblock. No need to validate in that हाल.
		 */
		अगर (zone_info->sb_zones[BTRFS_NR_SB_LOG_ZONES * i].type ==
		    BLK_ZONE_TYPE_CONVENTIONAL)
			जारी;

		ret = sb_ग_लिखो_poपूर्णांकer(device->bdev,
				       &zone_info->sb_zones[sb_pos], &sb_wp);
		अगर (ret != -ENOENT && ret) अणु
			btrfs_err_in_rcu(device->fs_info,
			"zoned: super block log zone corrupted devid %llu zone %u",
					 device->devid, sb_zone);
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण
	पूर्ण


	kमुक्त(zones);

	device->zone_info = zone_info;

	चयन (bdev_zoned_model(bdev)) अणु
	हाल BLK_ZONED_HM:
		model = "host-managed zoned";
		emulated = "";
		अवरोध;
	हाल BLK_ZONED_HA:
		model = "host-aware zoned";
		emulated = "";
		अवरोध;
	हाल BLK_ZONED_NONE:
		model = "regular";
		emulated = "emulated ";
		अवरोध;
	शेष:
		/* Just in हाल */
		btrfs_err_in_rcu(fs_info, "zoned: unsupported model %d on %s",
				 bdev_zoned_model(bdev),
				 rcu_str_deref(device->name));
		ret = -EOPNOTSUPP;
		जाओ out_मुक्त_zone_info;
	पूर्ण

	btrfs_info_in_rcu(fs_info,
		"%s block device %s, %u %szones of %llu bytes",
		model, rcu_str_deref(device->name), zone_info->nr_zones,
		emulated, zone_info->zone_size);

	वापस 0;

out:
	kमुक्त(zones);
out_मुक्त_zone_info:
	biपंचांगap_मुक्त(zone_info->empty_zones);
	biपंचांगap_मुक्त(zone_info->seq_zones);
	kमुक्त(zone_info);
	device->zone_info = शून्य;

	वापस ret;
पूर्ण

व्योम btrfs_destroy_dev_zone_info(काष्ठा btrfs_device *device)
अणु
	काष्ठा btrfs_zoned_device_info *zone_info = device->zone_info;

	अगर (!zone_info)
		वापस;

	biपंचांगap_मुक्त(zone_info->seq_zones);
	biपंचांगap_मुक्त(zone_info->empty_zones);
	kमुक्त(zone_info);
	device->zone_info = शून्य;
पूर्ण

पूर्णांक btrfs_get_dev_zone(काष्ठा btrfs_device *device, u64 pos,
		       काष्ठा blk_zone *zone)
अणु
	अचिन्हित पूर्णांक nr_zones = 1;
	पूर्णांक ret;

	ret = btrfs_get_dev_zones(device, pos, zone, &nr_zones);
	अगर (ret != 0 || !nr_zones)
		वापस ret ? ret : -EIO;

	वापस 0;
पूर्ण

पूर्णांक btrfs_check_zoned_mode(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	काष्ठा btrfs_device *device;
	u64 zoned_devices = 0;
	u64 nr_devices = 0;
	u64 zone_size = 0;
	u64 max_zone_append_size = 0;
	स्थिर bool incompat_zoned = btrfs_fs_incompat(fs_info, ZONED);
	पूर्णांक ret = 0;

	/* Count zoned devices */
	list_क्रम_each_entry(device, &fs_devices->devices, dev_list) अणु
		क्रमागत blk_zoned_model model;

		अगर (!device->bdev)
			जारी;

		model = bdev_zoned_model(device->bdev);
		/*
		 * A Host-Managed zoned device must be used as a zoned device.
		 * A Host-Aware zoned device and a non-zoned devices can be
		 * treated as a zoned device, अगर ZONED flag is enabled in the
		 * superblock.
		 */
		अगर (model == BLK_ZONED_HM ||
		    (model == BLK_ZONED_HA && incompat_zoned) ||
		    (model == BLK_ZONED_NONE && incompat_zoned)) अणु
			काष्ठा btrfs_zoned_device_info *zone_info =
				device->zone_info;

			zone_info = device->zone_info;
			zoned_devices++;
			अगर (!zone_size) अणु
				zone_size = zone_info->zone_size;
			पूर्ण अन्यथा अगर (zone_info->zone_size != zone_size) अणु
				btrfs_err(fs_info,
		"zoned: unequal block device zone sizes: have %llu found %llu",
					  device->zone_info->zone_size,
					  zone_size);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (!max_zone_append_size ||
			    (zone_info->max_zone_append_size &&
			     zone_info->max_zone_append_size < max_zone_append_size))
				max_zone_append_size =
					zone_info->max_zone_append_size;
		पूर्ण
		nr_devices++;
	पूर्ण

	अगर (!zoned_devices && !incompat_zoned)
		जाओ out;

	अगर (!zoned_devices && incompat_zoned) अणु
		/* No zoned block device found on ZONED fileप्रणाली */
		btrfs_err(fs_info,
			  "zoned: no zoned devices found on a zoned filesystem");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (zoned_devices && !incompat_zoned) अणु
		btrfs_err(fs_info,
			  "zoned: mode not enabled but zoned device found");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (zoned_devices != nr_devices) अणु
		btrfs_err(fs_info,
			  "zoned: cannot mix zoned and regular devices");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * stripe_size is always aligned to BTRFS_STRIPE_LEN in
	 * __btrfs_alloc_chunk(). Since we want stripe_len == zone_size,
	 * check the alignment here.
	 */
	अगर (!IS_ALIGNED(zone_size, BTRFS_STRIPE_LEN)) अणु
		btrfs_err(fs_info,
			  "zoned: zone size %llu not aligned to stripe %u",
			  zone_size, BTRFS_STRIPE_LEN);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (btrfs_fs_incompat(fs_info, MIXED_GROUPS)) अणु
		btrfs_err(fs_info, "zoned: mixed block groups not supported");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	fs_info->zone_size = zone_size;
	fs_info->max_zone_append_size = max_zone_append_size;
	fs_info->fs_devices->chunk_alloc_policy = BTRFS_CHUNK_ALLOC_ZONED;

	/*
	 * Check mount options here, because we might change fs_info->zoned
	 * from fs_info->zone_size.
	 */
	ret = btrfs_check_mountopts_zoned(fs_info);
	अगर (ret)
		जाओ out;

	btrfs_info(fs_info, "zoned mode enabled with zone size %llu", zone_size);
out:
	वापस ret;
पूर्ण

पूर्णांक btrfs_check_mountopts_zoned(काष्ठा btrfs_fs_info *info)
अणु
	अगर (!btrfs_is_zoned(info))
		वापस 0;

	/*
	 * Space cache writing is not COWed. Disable that to aव्योम ग_लिखो errors
	 * in sequential zones.
	 */
	अगर (btrfs_test_opt(info, SPACE_CACHE)) अणु
		btrfs_err(info, "zoned: space cache v1 is not supported");
		वापस -EINVAL;
	पूर्ण

	अगर (btrfs_test_opt(info, NODATACOW)) अणु
		btrfs_err(info, "zoned: NODATACOW not supported");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sb_log_location(काष्ठा block_device *bdev, काष्ठा blk_zone *zones,
			   पूर्णांक rw, u64 *bytenr_ret)
अणु
	u64 wp;
	पूर्णांक ret;

	अगर (zones[0].type == BLK_ZONE_TYPE_CONVENTIONAL) अणु
		*bytenr_ret = zones[0].start << SECTOR_SHIFT;
		वापस 0;
	पूर्ण

	ret = sb_ग_लिखो_poपूर्णांकer(bdev, zones, &wp);
	अगर (ret != -ENOENT && ret < 0)
		वापस ret;

	अगर (rw == WRITE) अणु
		काष्ठा blk_zone *reset = शून्य;

		अगर (wp == zones[0].start << SECTOR_SHIFT)
			reset = &zones[0];
		अन्यथा अगर (wp == zones[1].start << SECTOR_SHIFT)
			reset = &zones[1];

		अगर (reset && reset->cond != BLK_ZONE_COND_EMPTY) अणु
			ASSERT(reset->cond == BLK_ZONE_COND_FULL);

			ret = blkdev_zone_mgmt(bdev, REQ_OP_ZONE_RESET,
					       reset->start, reset->len,
					       GFP_NOFS);
			अगर (ret)
				वापस ret;

			reset->cond = BLK_ZONE_COND_EMPTY;
			reset->wp = reset->start;
		पूर्ण
	पूर्ण अन्यथा अगर (ret != -ENOENT) अणु
		/* For READ, we want the precious one */
		अगर (wp == zones[0].start << SECTOR_SHIFT)
			wp = (zones[1].start + zones[1].len) << SECTOR_SHIFT;
		wp -= BTRFS_SUPER_INFO_SIZE;
	पूर्ण

	*bytenr_ret = wp;
	वापस 0;

पूर्ण

पूर्णांक btrfs_sb_log_location_bdev(काष्ठा block_device *bdev, पूर्णांक mirror, पूर्णांक rw,
			       u64 *bytenr_ret)
अणु
	काष्ठा blk_zone zones[BTRFS_NR_SB_LOG_ZONES];
	sector_t zone_sectors;
	u32 sb_zone;
	पूर्णांक ret;
	u8 zone_sectors_shअगरt;
	sector_t nr_sectors;
	u32 nr_zones;

	अगर (!bdev_is_zoned(bdev)) अणु
		*bytenr_ret = btrfs_sb_offset(mirror);
		वापस 0;
	पूर्ण

	ASSERT(rw == READ || rw == WRITE);

	zone_sectors = bdev_zone_sectors(bdev);
	अगर (!is_घातer_of_2(zone_sectors))
		वापस -EINVAL;
	zone_sectors_shअगरt = ilog2(zone_sectors);
	nr_sectors = bdev_nr_sectors(bdev);
	nr_zones = nr_sectors >> zone_sectors_shअगरt;

	sb_zone = sb_zone_number(zone_sectors_shअगरt + SECTOR_SHIFT, mirror);
	अगर (sb_zone + 1 >= nr_zones)
		वापस -ENOENT;

	ret = blkdev_report_zones(bdev, zone_start_sector(sb_zone, bdev),
				  BTRFS_NR_SB_LOG_ZONES, copy_zone_info_cb,
				  zones);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != BTRFS_NR_SB_LOG_ZONES)
		वापस -EIO;

	वापस sb_log_location(bdev, zones, rw, bytenr_ret);
पूर्ण

पूर्णांक btrfs_sb_log_location(काष्ठा btrfs_device *device, पूर्णांक mirror, पूर्णांक rw,
			  u64 *bytenr_ret)
अणु
	काष्ठा btrfs_zoned_device_info *zinfo = device->zone_info;
	u32 zone_num;

	/*
	 * For a zoned fileप्रणाली on a non-zoned block device, use the same
	 * super block locations as regular fileप्रणाली. Doing so, the super
	 * block can always be retrieved and the zoned flag of the volume
	 * detected from the super block inक्रमmation.
	 */
	अगर (!bdev_is_zoned(device->bdev)) अणु
		*bytenr_ret = btrfs_sb_offset(mirror);
		वापस 0;
	पूर्ण

	zone_num = sb_zone_number(zinfo->zone_size_shअगरt, mirror);
	अगर (zone_num + 1 >= zinfo->nr_zones)
		वापस -ENOENT;

	वापस sb_log_location(device->bdev,
			       &zinfo->sb_zones[BTRFS_NR_SB_LOG_ZONES * mirror],
			       rw, bytenr_ret);
पूर्ण

अटल अंतरभूत bool is_sb_log_zone(काष्ठा btrfs_zoned_device_info *zinfo,
				  पूर्णांक mirror)
अणु
	u32 zone_num;

	अगर (!zinfo)
		वापस false;

	zone_num = sb_zone_number(zinfo->zone_size_shअगरt, mirror);
	अगर (zone_num + 1 >= zinfo->nr_zones)
		वापस false;

	अगर (!test_bit(zone_num, zinfo->seq_zones))
		वापस false;

	वापस true;
पूर्ण

व्योम btrfs_advance_sb_log(काष्ठा btrfs_device *device, पूर्णांक mirror)
अणु
	काष्ठा btrfs_zoned_device_info *zinfo = device->zone_info;
	काष्ठा blk_zone *zone;

	अगर (!is_sb_log_zone(zinfo, mirror))
		वापस;

	zone = &zinfo->sb_zones[BTRFS_NR_SB_LOG_ZONES * mirror];
	अगर (zone->cond != BLK_ZONE_COND_FULL) अणु
		अगर (zone->cond == BLK_ZONE_COND_EMPTY)
			zone->cond = BLK_ZONE_COND_IMP_OPEN;

		zone->wp += (BTRFS_SUPER_INFO_SIZE >> SECTOR_SHIFT);

		अगर (zone->wp == zone->start + zone->len)
			zone->cond = BLK_ZONE_COND_FULL;

		वापस;
	पूर्ण

	zone++;
	ASSERT(zone->cond != BLK_ZONE_COND_FULL);
	अगर (zone->cond == BLK_ZONE_COND_EMPTY)
		zone->cond = BLK_ZONE_COND_IMP_OPEN;

	zone->wp += (BTRFS_SUPER_INFO_SIZE >> SECTOR_SHIFT);

	अगर (zone->wp == zone->start + zone->len)
		zone->cond = BLK_ZONE_COND_FULL;
पूर्ण

पूर्णांक btrfs_reset_sb_log_zones(काष्ठा block_device *bdev, पूर्णांक mirror)
अणु
	sector_t zone_sectors;
	sector_t nr_sectors;
	u8 zone_sectors_shअगरt;
	u32 sb_zone;
	u32 nr_zones;

	zone_sectors = bdev_zone_sectors(bdev);
	zone_sectors_shअगरt = ilog2(zone_sectors);
	nr_sectors = bdev_nr_sectors(bdev);
	nr_zones = nr_sectors >> zone_sectors_shअगरt;

	sb_zone = sb_zone_number(zone_sectors_shअगरt + SECTOR_SHIFT, mirror);
	अगर (sb_zone + 1 >= nr_zones)
		वापस -ENOENT;

	वापस blkdev_zone_mgmt(bdev, REQ_OP_ZONE_RESET,
				zone_start_sector(sb_zone, bdev),
				zone_sectors * BTRFS_NR_SB_LOG_ZONES, GFP_NOFS);
पूर्ण

/**
 * btrfs_find_allocatable_zones - find allocatable zones within a given region
 *
 * @device:	the device to allocate a region on
 * @hole_start: the position of the hole to allocate the region
 * @num_bytes:	size of wanted region
 * @hole_end:	the end of the hole
 * @वापस:	position of allocatable zones
 *
 * Allocatable region should not contain any superblock locations.
 */
u64 btrfs_find_allocatable_zones(काष्ठा btrfs_device *device, u64 hole_start,
				 u64 hole_end, u64 num_bytes)
अणु
	काष्ठा btrfs_zoned_device_info *zinfo = device->zone_info;
	स्थिर u8 shअगरt = zinfo->zone_size_shअगरt;
	u64 nzones = num_bytes >> shअगरt;
	u64 pos = hole_start;
	u64 begin, end;
	bool have_sb;
	पूर्णांक i;

	ASSERT(IS_ALIGNED(hole_start, zinfo->zone_size));
	ASSERT(IS_ALIGNED(num_bytes, zinfo->zone_size));

	जबतक (pos < hole_end) अणु
		begin = pos >> shअगरt;
		end = begin + nzones;

		अगर (end > zinfo->nr_zones)
			वापस hole_end;

		/* Check अगर zones in the region are all empty */
		अगर (btrfs_dev_is_sequential(device, pos) &&
		    find_next_zero_bit(zinfo->empty_zones, end, begin) != end) अणु
			pos += zinfo->zone_size;
			जारी;
		पूर्ण

		have_sb = false;
		क्रम (i = 0; i < BTRFS_SUPER_MIRROR_MAX; i++) अणु
			u32 sb_zone;
			u64 sb_pos;

			sb_zone = sb_zone_number(shअगरt, i);
			अगर (!(end <= sb_zone ||
			      sb_zone + BTRFS_NR_SB_LOG_ZONES <= begin)) अणु
				have_sb = true;
				pos = zone_start_physical(
					sb_zone + BTRFS_NR_SB_LOG_ZONES, zinfo);
				अवरोध;
			पूर्ण

			/* We also need to exclude regular superblock positions */
			sb_pos = btrfs_sb_offset(i);
			अगर (!(pos + num_bytes <= sb_pos ||
			      sb_pos + BTRFS_SUPER_INFO_SIZE <= pos)) अणु
				have_sb = true;
				pos = ALIGN(sb_pos + BTRFS_SUPER_INFO_SIZE,
					    zinfo->zone_size);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!have_sb)
			अवरोध;
	पूर्ण

	वापस pos;
पूर्ण

पूर्णांक btrfs_reset_device_zone(काष्ठा btrfs_device *device, u64 physical,
			    u64 length, u64 *bytes)
अणु
	पूर्णांक ret;

	*bytes = 0;
	ret = blkdev_zone_mgmt(device->bdev, REQ_OP_ZONE_RESET,
			       physical >> SECTOR_SHIFT, length >> SECTOR_SHIFT,
			       GFP_NOFS);
	अगर (ret)
		वापस ret;

	*bytes = length;
	जबतक (length) अणु
		btrfs_dev_set_zone_empty(device, physical);
		physical += device->zone_info->zone_size;
		length -= device->zone_info->zone_size;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक btrfs_ensure_empty_zones(काष्ठा btrfs_device *device, u64 start, u64 size)
अणु
	काष्ठा btrfs_zoned_device_info *zinfo = device->zone_info;
	स्थिर u8 shअगरt = zinfo->zone_size_shअगरt;
	अचिन्हित दीर्घ begin = start >> shअगरt;
	अचिन्हित दीर्घ end = (start + size) >> shअगरt;
	u64 pos;
	पूर्णांक ret;

	ASSERT(IS_ALIGNED(start, zinfo->zone_size));
	ASSERT(IS_ALIGNED(size, zinfo->zone_size));

	अगर (end > zinfo->nr_zones)
		वापस -दुस्फल;

	/* All the zones are conventional */
	अगर (find_next_bit(zinfo->seq_zones, begin, end) == end)
		वापस 0;

	/* All the zones are sequential and empty */
	अगर (find_next_zero_bit(zinfo->seq_zones, begin, end) == end &&
	    find_next_zero_bit(zinfo->empty_zones, begin, end) == end)
		वापस 0;

	क्रम (pos = start; pos < start + size; pos += zinfo->zone_size) अणु
		u64 reset_bytes;

		अगर (!btrfs_dev_is_sequential(device, pos) ||
		    btrfs_dev_is_empty_zone(device, pos))
			जारी;

		/* Free regions should be empty */
		btrfs_warn_in_rcu(
			device->fs_info,
		"zoned: resetting device %s (devid %llu) zone %llu for allocation",
			rcu_str_deref(device->name), device->devid, pos >> shअगरt);
		WARN_ON_ONCE(1);

		ret = btrfs_reset_device_zone(device, pos, zinfo->zone_size,
					      &reset_bytes);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Calculate an allocation poपूर्णांकer from the extent allocation inक्रमmation
 * क्रम a block group consist of conventional zones. It is poपूर्णांकed to the
 * end of the highest addressed extent in the block group as an allocation
 * offset.
 */
अटल पूर्णांक calculate_alloc_poपूर्णांकer(काष्ठा btrfs_block_group *cache,
				   u64 *offset_ret)
अणु
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	काष्ठा btrfs_root *root = fs_info->extent_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	पूर्णांक ret;
	u64 length;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	key.objectid = cache->start + cache->length;
	key.type = 0;
	key.offset = 0;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	/* We should not find the exact match */
	अगर (!ret)
		ret = -EUCLEAN;
	अगर (ret < 0)
		जाओ out;

	ret = btrfs_previous_extent_item(root, path, cache->start);
	अगर (ret) अणु
		अगर (ret == 1) अणु
			ret = 0;
			*offset_ret = 0;
		पूर्ण
		जाओ out;
	पूर्ण

	btrfs_item_key_to_cpu(path->nodes[0], &found_key, path->slots[0]);

	अगर (found_key.type == BTRFS_EXTENT_ITEM_KEY)
		length = found_key.offset;
	अन्यथा
		length = fs_info->nodesize;

	अगर (!(found_key.objectid >= cache->start &&
	       found_key.objectid + length <= cache->start + cache->length)) अणु
		ret = -EUCLEAN;
		जाओ out;
	पूर्ण
	*offset_ret = found_key.objectid + length - cache->start;
	ret = 0;

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

पूर्णांक btrfs_load_block_group_zone_info(काष्ठा btrfs_block_group *cache, bool new)
अणु
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	काष्ठा extent_map_tree *em_tree = &fs_info->mapping_tree;
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	काष्ठा btrfs_device *device;
	u64 logical = cache->start;
	u64 length = cache->length;
	u64 physical = 0;
	पूर्णांक ret;
	पूर्णांक i;
	अचिन्हित पूर्णांक nofs_flag;
	u64 *alloc_offsets = शून्य;
	u64 last_alloc = 0;
	u32 num_sequential = 0, num_conventional = 0;

	अगर (!btrfs_is_zoned(fs_info))
		वापस 0;

	/* Sanity check */
	अगर (!IS_ALIGNED(length, fs_info->zone_size)) अणु
		btrfs_err(fs_info,
		"zoned: block group %llu len %llu unaligned to zone size %llu",
			  logical, length, fs_info->zone_size);
		वापस -EIO;
	पूर्ण

	/* Get the chunk mapping */
	पढ़ो_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, logical, length);
	पढ़ो_unlock(&em_tree->lock);

	अगर (!em)
		वापस -EINVAL;

	map = em->map_lookup;

	alloc_offsets = kसुस्मृति(map->num_stripes, माप(*alloc_offsets), GFP_NOFS);
	अगर (!alloc_offsets) अणु
		मुक्त_extent_map(em);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < map->num_stripes; i++) अणु
		bool is_sequential;
		काष्ठा blk_zone zone;
		काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
		पूर्णांक dev_replace_is_ongoing = 0;

		device = map->stripes[i].dev;
		physical = map->stripes[i].physical;

		अगर (device->bdev == शून्य) अणु
			alloc_offsets[i] = WP_MISSING_DEV;
			जारी;
		पूर्ण

		is_sequential = btrfs_dev_is_sequential(device, physical);
		अगर (is_sequential)
			num_sequential++;
		अन्यथा
			num_conventional++;

		अगर (!is_sequential) अणु
			alloc_offsets[i] = WP_CONVENTIONAL;
			जारी;
		पूर्ण

		/*
		 * This zone will be used क्रम allocation, so mark this zone
		 * non-empty.
		 */
		btrfs_dev_clear_zone_empty(device, physical);

		करोwn_पढ़ो(&dev_replace->rwsem);
		dev_replace_is_ongoing = btrfs_dev_replace_is_ongoing(dev_replace);
		अगर (dev_replace_is_ongoing && dev_replace->tgtdev != शून्य)
			btrfs_dev_clear_zone_empty(dev_replace->tgtdev, physical);
		up_पढ़ो(&dev_replace->rwsem);

		/*
		 * The group is mapped to a sequential zone. Get the zone ग_लिखो
		 * poपूर्णांकer to determine the allocation offset within the zone.
		 */
		WARN_ON(!IS_ALIGNED(physical, fs_info->zone_size));
		nofs_flag = meदो_स्मृति_nofs_save();
		ret = btrfs_get_dev_zone(device, physical, &zone);
		meदो_स्मृति_nofs_restore(nofs_flag);
		अगर (ret == -EIO || ret == -EOPNOTSUPP) अणु
			ret = 0;
			alloc_offsets[i] = WP_MISSING_DEV;
			जारी;
		पूर्ण अन्यथा अगर (ret) अणु
			जाओ out;
		पूर्ण

		अगर (zone.type == BLK_ZONE_TYPE_CONVENTIONAL) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण

		चयन (zone.cond) अणु
		हाल BLK_ZONE_COND_OFFLINE:
		हाल BLK_ZONE_COND_READONLY:
			btrfs_err(fs_info,
		"zoned: offline/readonly zone %llu on device %s (devid %llu)",
				  physical >> device->zone_info->zone_size_shअगरt,
				  rcu_str_deref(device->name), device->devid);
			alloc_offsets[i] = WP_MISSING_DEV;
			अवरोध;
		हाल BLK_ZONE_COND_EMPTY:
			alloc_offsets[i] = 0;
			अवरोध;
		हाल BLK_ZONE_COND_FULL:
			alloc_offsets[i] = fs_info->zone_size;
			अवरोध;
		शेष:
			/* Partially used zone */
			alloc_offsets[i] =
					((zone.wp - zone.start) << SECTOR_SHIFT);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (num_sequential > 0)
		cache->seq_zone = true;

	अगर (num_conventional > 0) अणु
		/*
		 * Aव्योम calling calculate_alloc_poपूर्णांकer() क्रम new BG. It
		 * is no use क्रम new BG. It must be always 0.
		 *
		 * Also, we have a lock chain of extent buffer lock ->
		 * chunk mutex.  For new BG, this function is called from
		 * btrfs_make_block_group() which is alपढ़ोy taking the
		 * chunk mutex. Thus, we cannot call
		 * calculate_alloc_poपूर्णांकer() which takes extent buffer
		 * locks to aव्योम deadlock.
		 */
		अगर (new) अणु
			cache->alloc_offset = 0;
			जाओ out;
		पूर्ण
		ret = calculate_alloc_poपूर्णांकer(cache, &last_alloc);
		अगर (ret || map->num_stripes == num_conventional) अणु
			अगर (!ret)
				cache->alloc_offset = last_alloc;
			अन्यथा
				btrfs_err(fs_info,
			"zoned: failed to determine allocation offset of bg %llu",
					  cache->start);
			जाओ out;
		पूर्ण
	पूर्ण

	चयन (map->type & BTRFS_BLOCK_GROUP_PROखाता_MASK) अणु
	हाल 0: /* single */
		cache->alloc_offset = alloc_offsets[0];
		अवरोध;
	हाल BTRFS_BLOCK_GROUP_DUP:
	हाल BTRFS_BLOCK_GROUP_RAID1:
	हाल BTRFS_BLOCK_GROUP_RAID0:
	हाल BTRFS_BLOCK_GROUP_RAID10:
	हाल BTRFS_BLOCK_GROUP_RAID5:
	हाल BTRFS_BLOCK_GROUP_RAID6:
		/* non-single profiles are not supported yet */
	शेष:
		btrfs_err(fs_info, "zoned: profile %s not yet supported",
			  btrfs_bg_type_to_raid_name(map->type));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

out:
	/* An extent is allocated after the ग_लिखो poपूर्णांकer */
	अगर (!ret && num_conventional && last_alloc > cache->alloc_offset) अणु
		btrfs_err(fs_info,
			  "zoned: got wrong write pointer in BG %llu: %llu > %llu",
			  logical, last_alloc, cache->alloc_offset);
		ret = -EIO;
	पूर्ण

	अगर (!ret)
		cache->meta_ग_लिखो_poपूर्णांकer = cache->alloc_offset + cache->start;

	kमुक्त(alloc_offsets);
	मुक्त_extent_map(em);

	वापस ret;
पूर्ण

व्योम btrfs_calc_zone_unusable(काष्ठा btrfs_block_group *cache)
अणु
	u64 unusable, मुक्त;

	अगर (!btrfs_is_zoned(cache->fs_info))
		वापस;

	WARN_ON(cache->bytes_super != 0);
	unusable = cache->alloc_offset - cache->used;
	मुक्त = cache->length - cache->alloc_offset;

	/* We only need ->मुक्त_space in ALLOC_SEQ block groups */
	cache->last_byte_to_unpin = (u64)-1;
	cache->cached = BTRFS_CACHE_FINISHED;
	cache->मुक्त_space_ctl->मुक्त_space = मुक्त;
	cache->zone_unusable = unusable;

	/* Should not have any excluded extents. Just in हाल, though */
	btrfs_मुक्त_excluded_extents(cache);
पूर्ण

व्योम btrfs_redirty_list_add(काष्ठा btrfs_transaction *trans,
			    काष्ठा extent_buffer *eb)
अणु
	काष्ठा btrfs_fs_info *fs_info = eb->fs_info;

	अगर (!btrfs_is_zoned(fs_info) ||
	    btrfs_header_flag(eb, BTRFS_HEADER_FLAG_WRITTEN) ||
	    !list_empty(&eb->release_list))
		वापस;

	set_extent_buffer_dirty(eb);
	set_extent_bits_noरुको(&trans->dirty_pages, eb->start,
			       eb->start + eb->len - 1, EXTENT_सूचीTY);
	memzero_extent_buffer(eb, 0, eb->len);
	set_bit(EXTENT_BUFFER_NO_CHECK, &eb->bflags);

	spin_lock(&trans->releasing_ebs_lock);
	list_add_tail(&eb->release_list, &trans->releasing_ebs);
	spin_unlock(&trans->releasing_ebs_lock);
	atomic_inc(&eb->refs);
पूर्ण

व्योम btrfs_मुक्त_redirty_list(काष्ठा btrfs_transaction *trans)
अणु
	spin_lock(&trans->releasing_ebs_lock);
	जबतक (!list_empty(&trans->releasing_ebs)) अणु
		काष्ठा extent_buffer *eb;

		eb = list_first_entry(&trans->releasing_ebs,
				      काष्ठा extent_buffer, release_list);
		list_del_init(&eb->release_list);
		मुक्त_extent_buffer(eb);
	पूर्ण
	spin_unlock(&trans->releasing_ebs_lock);
पूर्ण

bool btrfs_use_zone_append(काष्ठा btrfs_inode *inode, u64 start)
अणु
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा btrfs_block_group *cache;
	bool ret = false;

	अगर (!btrfs_is_zoned(fs_info))
		वापस false;

	अगर (!fs_info->max_zone_append_size)
		वापस false;

	अगर (!is_data_inode(&inode->vfs_inode))
		वापस false;

	cache = btrfs_lookup_block_group(fs_info, start);
	ASSERT(cache);
	अगर (!cache)
		वापस false;

	ret = cache->seq_zone;
	btrfs_put_block_group(cache);

	वापस ret;
पूर्ण

व्योम btrfs_record_physical_zoned(काष्ठा inode *inode, u64 file_offset,
				 काष्ठा bio *bio)
अणु
	काष्ठा btrfs_ordered_extent *ordered;
	स्थिर u64 physical = bio->bi_iter.bi_sector << SECTOR_SHIFT;

	अगर (bio_op(bio) != REQ_OP_ZONE_APPEND)
		वापस;

	ordered = btrfs_lookup_ordered_extent(BTRFS_I(inode), file_offset);
	अगर (WARN_ON(!ordered))
		वापस;

	ordered->physical = physical;
	ordered->disk = bio->bi_bdev->bd_disk;
	ordered->partno = bio->bi_bdev->bd_partno;

	btrfs_put_ordered_extent(ordered);
पूर्ण

व्योम btrfs_reग_लिखो_logical_zoned(काष्ठा btrfs_ordered_extent *ordered)
अणु
	काष्ठा btrfs_inode *inode = BTRFS_I(ordered->inode);
	काष्ठा btrfs_fs_info *fs_info = inode->root->fs_info;
	काष्ठा extent_map_tree *em_tree;
	काष्ठा extent_map *em;
	काष्ठा btrfs_ordered_sum *sum;
	काष्ठा block_device *bdev;
	u64 orig_logical = ordered->disk_bytenr;
	u64 *logical = शून्य;
	पूर्णांक nr, stripe_len;

	/* Zoned devices should not have partitions. So, we can assume it is 0 */
	ASSERT(ordered->partno == 0);
	bdev = bdgrab(ordered->disk->part0);
	अगर (WARN_ON(!bdev))
		वापस;

	अगर (WARN_ON(btrfs_rmap_block(fs_info, orig_logical, bdev,
				     ordered->physical, &logical, &nr,
				     &stripe_len)))
		जाओ out;

	WARN_ON(nr != 1);

	अगर (orig_logical == *logical)
		जाओ out;

	ordered->disk_bytenr = *logical;

	em_tree = &inode->extent_tree;
	ग_लिखो_lock(&em_tree->lock);
	em = search_extent_mapping(em_tree, ordered->file_offset,
				   ordered->num_bytes);
	em->block_start = *logical;
	मुक्त_extent_map(em);
	ग_लिखो_unlock(&em_tree->lock);

	list_क्रम_each_entry(sum, &ordered->list, list) अणु
		अगर (*logical < orig_logical)
			sum->bytenr -= orig_logical - *logical;
		अन्यथा
			sum->bytenr += *logical - orig_logical;
	पूर्ण

out:
	kमुक्त(logical);
	bdput(bdev);
पूर्ण

bool btrfs_check_meta_ग_लिखो_poपूर्णांकer(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा extent_buffer *eb,
				    काष्ठा btrfs_block_group **cache_ret)
अणु
	काष्ठा btrfs_block_group *cache;
	bool ret = true;

	अगर (!btrfs_is_zoned(fs_info))
		वापस true;

	cache = *cache_ret;

	अगर (cache && (eb->start < cache->start ||
		      cache->start + cache->length <= eb->start)) अणु
		btrfs_put_block_group(cache);
		cache = शून्य;
		*cache_ret = शून्य;
	पूर्ण

	अगर (!cache)
		cache = btrfs_lookup_block_group(fs_info, eb->start);

	अगर (cache) अणु
		अगर (cache->meta_ग_लिखो_poपूर्णांकer != eb->start) अणु
			btrfs_put_block_group(cache);
			cache = शून्य;
			ret = false;
		पूर्ण अन्यथा अणु
			cache->meta_ग_लिखो_poपूर्णांकer = eb->start + eb->len;
		पूर्ण

		*cache_ret = cache;
	पूर्ण

	वापस ret;
पूर्ण

व्योम btrfs_revert_meta_ग_लिखो_poपूर्णांकer(काष्ठा btrfs_block_group *cache,
				     काष्ठा extent_buffer *eb)
अणु
	अगर (!btrfs_is_zoned(eb->fs_info) || !cache)
		वापस;

	ASSERT(cache->meta_ग_लिखो_poपूर्णांकer == eb->start + eb->len);
	cache->meta_ग_लिखो_poपूर्णांकer = eb->start;
पूर्ण

पूर्णांक btrfs_zoned_issue_zeroout(काष्ठा btrfs_device *device, u64 physical, u64 length)
अणु
	अगर (!btrfs_dev_is_sequential(device, physical))
		वापस -EOPNOTSUPP;

	वापस blkdev_issue_zeroout(device->bdev, physical >> SECTOR_SHIFT,
				    length >> SECTOR_SHIFT, GFP_NOFS, 0);
पूर्ण

अटल पूर्णांक पढ़ो_zone_info(काष्ठा btrfs_fs_info *fs_info, u64 logical,
			  काष्ठा blk_zone *zone)
अणु
	काष्ठा btrfs_bio *bbio = शून्य;
	u64 mapped_length = PAGE_SIZE;
	अचिन्हित पूर्णांक nofs_flag;
	पूर्णांक nmirrors;
	पूर्णांक i, ret;

	ret = btrfs_map_sblock(fs_info, BTRFS_MAP_GET_READ_MIRRORS, logical,
			       &mapped_length, &bbio);
	अगर (ret || !bbio || mapped_length < PAGE_SIZE) अणु
		btrfs_put_bbio(bbio);
		वापस -EIO;
	पूर्ण

	अगर (bbio->map_type & BTRFS_BLOCK_GROUP_RAID56_MASK)
		वापस -EINVAL;

	nofs_flag = meदो_स्मृति_nofs_save();
	nmirrors = (पूर्णांक)bbio->num_stripes;
	क्रम (i = 0; i < nmirrors; i++) अणु
		u64 physical = bbio->stripes[i].physical;
		काष्ठा btrfs_device *dev = bbio->stripes[i].dev;

		/* Missing device */
		अगर (!dev->bdev)
			जारी;

		ret = btrfs_get_dev_zone(dev, physical, zone);
		/* Failing device */
		अगर (ret == -EIO || ret == -EOPNOTSUPP)
			जारी;
		अवरोध;
	पूर्ण
	meदो_स्मृति_nofs_restore(nofs_flag);

	वापस ret;
पूर्ण

/*
 * Synchronize ग_लिखो poपूर्णांकer in a zone at @physical_start on @tgt_dev, by
 * filling zeros between @physical_pos to a ग_लिखो poपूर्णांकer of dev-replace
 * source device.
 */
पूर्णांक btrfs_sync_zone_ग_लिखो_poपूर्णांकer(काष्ठा btrfs_device *tgt_dev, u64 logical,
				    u64 physical_start, u64 physical_pos)
अणु
	काष्ठा btrfs_fs_info *fs_info = tgt_dev->fs_info;
	काष्ठा blk_zone zone;
	u64 length;
	u64 wp;
	पूर्णांक ret;

	अगर (!btrfs_dev_is_sequential(tgt_dev, physical_pos))
		वापस 0;

	ret = पढ़ो_zone_info(fs_info, logical, &zone);
	अगर (ret)
		वापस ret;

	wp = physical_start + ((zone.wp - zone.start) << SECTOR_SHIFT);

	अगर (physical_pos == wp)
		वापस 0;

	अगर (physical_pos > wp)
		वापस -EUCLEAN;

	length = wp - physical_pos;
	वापस btrfs_zoned_issue_zeroout(tgt_dev, physical_pos, length);
पूर्ण
