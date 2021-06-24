<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_ZONED_H
#घोषणा BTRFS_ZONED_H

#समावेश <linux/types.h>
#समावेश <linux/blkdev.h>
#समावेश "volumes.h"
#समावेश "disk-io.h"
#समावेश "block-group.h"

/*
 * Block groups with more than this value (percents) of unusable space will be
 * scheduled क्रम background reclaim.
 */
#घोषणा BTRFS_DEFAULT_RECLAIM_THRESH		75

काष्ठा btrfs_zoned_device_info अणु
	/*
	 * Number of zones, zone size and types of zones अगर bdev is a
	 * zoned block device.
	 */
	u64 zone_size;
	u8  zone_size_shअगरt;
	u64 max_zone_append_size;
	u32 nr_zones;
	अचिन्हित दीर्घ *seq_zones;
	अचिन्हित दीर्घ *empty_zones;
	काष्ठा blk_zone sb_zones[2 * BTRFS_SUPER_MIRROR_MAX];
पूर्ण;

#अगर_घोषित CONFIG_BLK_DEV_ZONED
पूर्णांक btrfs_get_dev_zone(काष्ठा btrfs_device *device, u64 pos,
		       काष्ठा blk_zone *zone);
पूर्णांक btrfs_get_dev_zone_info_all_devices(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_get_dev_zone_info(काष्ठा btrfs_device *device);
व्योम btrfs_destroy_dev_zone_info(काष्ठा btrfs_device *device);
पूर्णांक btrfs_check_zoned_mode(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_check_mountopts_zoned(काष्ठा btrfs_fs_info *info);
पूर्णांक btrfs_sb_log_location_bdev(काष्ठा block_device *bdev, पूर्णांक mirror, पूर्णांक rw,
			       u64 *bytenr_ret);
पूर्णांक btrfs_sb_log_location(काष्ठा btrfs_device *device, पूर्णांक mirror, पूर्णांक rw,
			  u64 *bytenr_ret);
व्योम btrfs_advance_sb_log(काष्ठा btrfs_device *device, पूर्णांक mirror);
पूर्णांक btrfs_reset_sb_log_zones(काष्ठा block_device *bdev, पूर्णांक mirror);
u64 btrfs_find_allocatable_zones(काष्ठा btrfs_device *device, u64 hole_start,
				 u64 hole_end, u64 num_bytes);
पूर्णांक btrfs_reset_device_zone(काष्ठा btrfs_device *device, u64 physical,
			    u64 length, u64 *bytes);
पूर्णांक btrfs_ensure_empty_zones(काष्ठा btrfs_device *device, u64 start, u64 size);
पूर्णांक btrfs_load_block_group_zone_info(काष्ठा btrfs_block_group *cache, bool new);
व्योम btrfs_calc_zone_unusable(काष्ठा btrfs_block_group *cache);
व्योम btrfs_redirty_list_add(काष्ठा btrfs_transaction *trans,
			    काष्ठा extent_buffer *eb);
व्योम btrfs_मुक्त_redirty_list(काष्ठा btrfs_transaction *trans);
bool btrfs_use_zone_append(काष्ठा btrfs_inode *inode, u64 start);
व्योम btrfs_record_physical_zoned(काष्ठा inode *inode, u64 file_offset,
				 काष्ठा bio *bio);
व्योम btrfs_reग_लिखो_logical_zoned(काष्ठा btrfs_ordered_extent *ordered);
bool btrfs_check_meta_ग_लिखो_poपूर्णांकer(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा extent_buffer *eb,
				    काष्ठा btrfs_block_group **cache_ret);
व्योम btrfs_revert_meta_ग_लिखो_poपूर्णांकer(काष्ठा btrfs_block_group *cache,
				     काष्ठा extent_buffer *eb);
पूर्णांक btrfs_zoned_issue_zeroout(काष्ठा btrfs_device *device, u64 physical, u64 length);
पूर्णांक btrfs_sync_zone_ग_लिखो_poपूर्णांकer(काष्ठा btrfs_device *tgt_dev, u64 logical,
				  u64 physical_start, u64 physical_pos);
#अन्यथा /* CONFIG_BLK_DEV_ZONED */
अटल अंतरभूत पूर्णांक btrfs_get_dev_zone(काष्ठा btrfs_device *device, u64 pos,
				     काष्ठा blk_zone *zone)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_get_dev_zone_info_all_devices(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_get_dev_zone_info(काष्ठा btrfs_device *device)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम btrfs_destroy_dev_zone_info(काष्ठा btrfs_device *device) अणु पूर्ण

अटल अंतरभूत पूर्णांक btrfs_check_zoned_mode(स्थिर काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (!btrfs_is_zoned(fs_info))
		वापस 0;

	btrfs_err(fs_info, "zoned block devices support is not enabled");
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_check_mountopts_zoned(काष्ठा btrfs_fs_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_sb_log_location_bdev(काष्ठा block_device *bdev,
					     पूर्णांक mirror, पूर्णांक rw, u64 *bytenr_ret)
अणु
	*bytenr_ret = btrfs_sb_offset(mirror);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_sb_log_location(काष्ठा btrfs_device *device, पूर्णांक mirror,
					पूर्णांक rw, u64 *bytenr_ret)
अणु
	*bytenr_ret = btrfs_sb_offset(mirror);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम btrfs_advance_sb_log(काष्ठा btrfs_device *device, पूर्णांक mirror)
अणु पूर्ण

अटल अंतरभूत पूर्णांक btrfs_reset_sb_log_zones(काष्ठा block_device *bdev, पूर्णांक mirror)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u64 btrfs_find_allocatable_zones(काष्ठा btrfs_device *device,
					       u64 hole_start, u64 hole_end,
					       u64 num_bytes)
अणु
	वापस hole_start;
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_reset_device_zone(काष्ठा btrfs_device *device,
					  u64 physical, u64 length, u64 *bytes)
अणु
	*bytes = 0;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_ensure_empty_zones(काष्ठा btrfs_device *device,
					   u64 start, u64 size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_load_block_group_zone_info(
		काष्ठा btrfs_block_group *cache, bool new)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम btrfs_calc_zone_unusable(काष्ठा btrfs_block_group *cache) अणु पूर्ण

अटल अंतरभूत व्योम btrfs_redirty_list_add(काष्ठा btrfs_transaction *trans,
					  काष्ठा extent_buffer *eb) अणु पूर्ण
अटल अंतरभूत व्योम btrfs_मुक्त_redirty_list(काष्ठा btrfs_transaction *trans) अणु पूर्ण

अटल अंतरभूत bool btrfs_use_zone_append(काष्ठा btrfs_inode *inode, u64 start)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम btrfs_record_physical_zoned(काष्ठा inode *inode,
					       u64 file_offset, काष्ठा bio *bio)
अणु
पूर्ण

अटल अंतरभूत व्योम btrfs_reग_लिखो_logical_zoned(
				काष्ठा btrfs_ordered_extent *ordered) अणु पूर्ण

अटल अंतरभूत bool btrfs_check_meta_ग_लिखो_poपूर्णांकer(काष्ठा btrfs_fs_info *fs_info,
			       काष्ठा extent_buffer *eb,
			       काष्ठा btrfs_block_group **cache_ret)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम btrfs_revert_meta_ग_लिखो_poपूर्णांकer(
						काष्ठा btrfs_block_group *cache,
						काष्ठा extent_buffer *eb)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_zoned_issue_zeroout(काष्ठा btrfs_device *device,
					    u64 physical, u64 length)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_sync_zone_ग_लिखो_poपूर्णांकer(काष्ठा btrfs_device *tgt_dev,
						u64 logical, u64 physical_start,
						u64 physical_pos)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत bool btrfs_dev_is_sequential(काष्ठा btrfs_device *device, u64 pos)
अणु
	काष्ठा btrfs_zoned_device_info *zone_info = device->zone_info;

	अगर (!zone_info)
		वापस false;

	वापस test_bit(pos >> zone_info->zone_size_shअगरt, zone_info->seq_zones);
पूर्ण

अटल अंतरभूत bool btrfs_dev_is_empty_zone(काष्ठा btrfs_device *device, u64 pos)
अणु
	काष्ठा btrfs_zoned_device_info *zone_info = device->zone_info;

	अगर (!zone_info)
		वापस true;

	वापस test_bit(pos >> zone_info->zone_size_shअगरt, zone_info->empty_zones);
पूर्ण

अटल अंतरभूत व्योम btrfs_dev_set_empty_zone_bit(काष्ठा btrfs_device *device,
						u64 pos, bool set)
अणु
	काष्ठा btrfs_zoned_device_info *zone_info = device->zone_info;
	अचिन्हित पूर्णांक zno;

	अगर (!zone_info)
		वापस;

	zno = pos >> zone_info->zone_size_shअगरt;
	अगर (set)
		set_bit(zno, zone_info->empty_zones);
	अन्यथा
		clear_bit(zno, zone_info->empty_zones);
पूर्ण

अटल अंतरभूत व्योम btrfs_dev_set_zone_empty(काष्ठा btrfs_device *device, u64 pos)
अणु
	btrfs_dev_set_empty_zone_bit(device, pos, true);
पूर्ण

अटल अंतरभूत व्योम btrfs_dev_clear_zone_empty(काष्ठा btrfs_device *device, u64 pos)
अणु
	btrfs_dev_set_empty_zone_bit(device, pos, false);
पूर्ण

अटल अंतरभूत bool btrfs_check_device_zone_type(स्थिर काष्ठा btrfs_fs_info *fs_info,
						काष्ठा block_device *bdev)
अणु
	अगर (btrfs_is_zoned(fs_info)) अणु
		/*
		 * We can allow a regular device on a zoned fileप्रणाली, because
		 * we will emulate the zoned capabilities.
		 */
		अगर (!bdev_is_zoned(bdev))
			वापस true;

		वापस fs_info->zone_size ==
			(bdev_zone_sectors(bdev) << SECTOR_SHIFT);
	पूर्ण

	/* Do not allow Host Manged zoned device */
	वापस bdev_zoned_model(bdev) != BLK_ZONED_HM;
पूर्ण

अटल अंतरभूत bool btrfs_check_super_location(काष्ठा btrfs_device *device, u64 pos)
अणु
	/*
	 * On a non-zoned device, any address is OK. On a zoned device,
	 * non-SEQUENTIAL WRITE REQUIRED zones are capable.
	 */
	वापस device->zone_info == शून्य || !btrfs_dev_is_sequential(device, pos);
पूर्ण

अटल अंतरभूत bool btrfs_can_zone_reset(काष्ठा btrfs_device *device,
					u64 physical, u64 length)
अणु
	u64 zone_size;

	अगर (!btrfs_dev_is_sequential(device, physical))
		वापस false;

	zone_size = device->zone_info->zone_size;
	अगर (!IS_ALIGNED(physical, zone_size) || !IS_ALIGNED(length, zone_size))
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत व्योम btrfs_zoned_meta_io_lock(काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (!btrfs_is_zoned(fs_info))
		वापस;
	mutex_lock(&fs_info->zoned_meta_io_lock);
पूर्ण

अटल अंतरभूत व्योम btrfs_zoned_meta_io_unlock(काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (!btrfs_is_zoned(fs_info))
		वापस;
	mutex_unlock(&fs_info->zoned_meta_io_lock);
पूर्ण

अटल अंतरभूत व्योम btrfs_clear_treelog_bg(काष्ठा btrfs_block_group *bg)
अणु
	काष्ठा btrfs_fs_info *fs_info = bg->fs_info;

	अगर (!btrfs_is_zoned(fs_info))
		वापस;

	spin_lock(&fs_info->treelog_bg_lock);
	अगर (fs_info->treelog_bg == bg->start)
		fs_info->treelog_bg = 0;
	spin_unlock(&fs_info->treelog_bg_lock);
पूर्ण

#पूर्ण_अगर
