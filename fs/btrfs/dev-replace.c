<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STRATO AG 2012.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/bपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/math64.h>
#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "extent_map.h"
#समावेश "disk-io.h"
#समावेश "transaction.h"
#समावेश "print-tree.h"
#समावेश "volumes.h"
#समावेश "async-thread.h"
#समावेश "check-integrity.h"
#समावेश "rcu-string.h"
#समावेश "dev-replace.h"
#समावेश "sysfs.h"
#समावेश "zoned.h"
#समावेश "block-group.h"

/*
 * Device replace overview
 *
 * [Objective]
 * To copy all extents (both new and on-disk) from source device to target
 * device, जबतक still keeping the fileप्रणाली पढ़ो-ग_लिखो.
 *
 * [Method]
 * There are two मुख्य methods involved:
 *
 * - Write duplication
 *
 *   All new ग_लिखोs will be written to both target and source devices, so even
 *   अगर replace माला_लो canceled, sources device still contans up-to-date data.
 *
 *   Location:		handle_ops_on_dev_replace() from __btrfs_map_block()
 *   Start:		btrfs_dev_replace_start()
 *   End:		btrfs_dev_replace_finishing()
 *   Content:		Latest data/metadata
 *
 * - Copy existing extents
 *
 *   This happens by re-using scrub facility, as scrub also iterates through
 *   existing extents from commit root.
 *
 *   Location:		scrub_ग_लिखो_block_to_dev_replace() from
 *   			scrub_block_complete()
 *   Content:		Data/meta from commit root.
 *
 * Due to the content dअगरference, we need to aव्योम nocow ग_लिखो when dev-replace
 * is happening.  This is करोne by marking the block group पढ़ो-only and रुकोing
 * क्रम NOCOW ग_लिखोs.
 *
 * After replace is करोne, the finishing part is करोne by swapping the target and
 * source devices.
 *
 *   Location:		btrfs_dev_replace_update_device_in_mapping_tree() from
 *   			btrfs_dev_replace_finishing()
 */

अटल पूर्णांक btrfs_dev_replace_finishing(काष्ठा btrfs_fs_info *fs_info,
				       पूर्णांक scrub_ret);
अटल पूर्णांक btrfs_dev_replace_kthपढ़ो(व्योम *data);

पूर्णांक btrfs_init_dev_replace(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_key key;
	काष्ठा btrfs_root *dev_root = fs_info->dev_root;
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
	काष्ठा extent_buffer *eb;
	पूर्णांक slot;
	पूर्णांक ret = 0;
	काष्ठा btrfs_path *path = शून्य;
	पूर्णांक item_size;
	काष्ठा btrfs_dev_replace_item *ptr;
	u64 src_devid;

	अगर (!dev_root)
		वापस 0;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	key.objectid = 0;
	key.type = BTRFS_DEV_REPLACE_KEY;
	key.offset = 0;
	ret = btrfs_search_slot(शून्य, dev_root, &key, path, 0, 0);
	अगर (ret) अणु
no_valid_dev_replace_entry_found:
		/*
		 * We करोn't have a replace item or it's corrupted.  If there is
		 * a replace target, fail the mount.
		 */
		अगर (btrfs_find_device(fs_info->fs_devices,
				      BTRFS_DEV_REPLACE_DEVID, शून्य, शून्य)) अणु
			btrfs_err(fs_info,
			"found replace target device without a valid replace item");
			ret = -EUCLEAN;
			जाओ out;
		पूर्ण
		ret = 0;
		dev_replace->replace_state =
			BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED;
		dev_replace->cont_पढ़ोing_from_srcdev_mode =
		    BTRFS_DEV_REPLACE_ITEM_CONT_READING_FROM_SRCDEV_MODE_ALWAYS;
		dev_replace->समय_started = 0;
		dev_replace->समय_stopped = 0;
		atomic64_set(&dev_replace->num_ग_लिखो_errors, 0);
		atomic64_set(&dev_replace->num_uncorrectable_पढ़ो_errors, 0);
		dev_replace->cursor_left = 0;
		dev_replace->committed_cursor_left = 0;
		dev_replace->cursor_left_last_ग_लिखो_of_item = 0;
		dev_replace->cursor_right = 0;
		dev_replace->srcdev = शून्य;
		dev_replace->tgtdev = शून्य;
		dev_replace->is_valid = 0;
		dev_replace->item_needs_ग_लिखोback = 0;
		जाओ out;
	पूर्ण
	slot = path->slots[0];
	eb = path->nodes[0];
	item_size = btrfs_item_size_nr(eb, slot);
	ptr = btrfs_item_ptr(eb, slot, काष्ठा btrfs_dev_replace_item);

	अगर (item_size != माप(काष्ठा btrfs_dev_replace_item)) अणु
		btrfs_warn(fs_info,
			"dev_replace entry found has unexpected size, ignore entry");
		जाओ no_valid_dev_replace_entry_found;
	पूर्ण

	src_devid = btrfs_dev_replace_src_devid(eb, ptr);
	dev_replace->cont_पढ़ोing_from_srcdev_mode =
		btrfs_dev_replace_cont_पढ़ोing_from_srcdev_mode(eb, ptr);
	dev_replace->replace_state = btrfs_dev_replace_replace_state(eb, ptr);
	dev_replace->समय_started = btrfs_dev_replace_समय_started(eb, ptr);
	dev_replace->समय_stopped =
		btrfs_dev_replace_समय_stopped(eb, ptr);
	atomic64_set(&dev_replace->num_ग_लिखो_errors,
		     btrfs_dev_replace_num_ग_लिखो_errors(eb, ptr));
	atomic64_set(&dev_replace->num_uncorrectable_पढ़ो_errors,
		     btrfs_dev_replace_num_uncorrectable_पढ़ो_errors(eb, ptr));
	dev_replace->cursor_left = btrfs_dev_replace_cursor_left(eb, ptr);
	dev_replace->committed_cursor_left = dev_replace->cursor_left;
	dev_replace->cursor_left_last_ग_लिखो_of_item = dev_replace->cursor_left;
	dev_replace->cursor_right = btrfs_dev_replace_cursor_right(eb, ptr);
	dev_replace->is_valid = 1;

	dev_replace->item_needs_ग_लिखोback = 0;
	चयन (dev_replace->replace_state) अणु
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED:
		/*
		 * We करोn't have an active replace item but अगर there is a
		 * replace target, fail the mount.
		 */
		अगर (btrfs_find_device(fs_info->fs_devices,
				      BTRFS_DEV_REPLACE_DEVID, शून्य, शून्य)) अणु
			btrfs_err(fs_info,
			"replace devid present without an active replace item");
			ret = -EUCLEAN;
		पूर्ण अन्यथा अणु
			dev_replace->srcdev = शून्य;
			dev_replace->tgtdev = शून्य;
		पूर्ण
		अवरोध;
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED:
		dev_replace->srcdev = btrfs_find_device(fs_info->fs_devices,
						src_devid, शून्य, शून्य);
		dev_replace->tgtdev = btrfs_find_device(fs_info->fs_devices,
							BTRFS_DEV_REPLACE_DEVID,
							शून्य, शून्य);
		/*
		 * allow 'btrfs dev replace_cancel' अगर src/tgt device is
		 * missing
		 */
		अगर (!dev_replace->srcdev &&
		    !btrfs_test_opt(fs_info, DEGRADED)) अणु
			ret = -EIO;
			btrfs_warn(fs_info,
			   "cannot mount because device replace operation is ongoing and");
			btrfs_warn(fs_info,
			   "srcdev (devid %llu) is missing, need to run 'btrfs dev scan'?",
			   src_devid);
		पूर्ण
		अगर (!dev_replace->tgtdev &&
		    !btrfs_test_opt(fs_info, DEGRADED)) अणु
			ret = -EIO;
			btrfs_warn(fs_info,
			   "cannot mount because device replace operation is ongoing and");
			btrfs_warn(fs_info,
			   "tgtdev (devid %llu) is missing, need to run 'btrfs dev scan'?",
				BTRFS_DEV_REPLACE_DEVID);
		पूर्ण
		अगर (dev_replace->tgtdev) अणु
			अगर (dev_replace->srcdev) अणु
				dev_replace->tgtdev->total_bytes =
					dev_replace->srcdev->total_bytes;
				dev_replace->tgtdev->disk_total_bytes =
					dev_replace->srcdev->disk_total_bytes;
				dev_replace->tgtdev->commit_total_bytes =
					dev_replace->srcdev->commit_total_bytes;
				dev_replace->tgtdev->bytes_used =
					dev_replace->srcdev->bytes_used;
				dev_replace->tgtdev->commit_bytes_used =
					dev_replace->srcdev->commit_bytes_used;
			पूर्ण
			set_bit(BTRFS_DEV_STATE_REPLACE_TGT,
				&dev_replace->tgtdev->dev_state);

			WARN_ON(fs_info->fs_devices->rw_devices == 0);
			dev_replace->tgtdev->io_width = fs_info->sectorsize;
			dev_replace->tgtdev->io_align = fs_info->sectorsize;
			dev_replace->tgtdev->sector_size = fs_info->sectorsize;
			dev_replace->tgtdev->fs_info = fs_info;
			set_bit(BTRFS_DEV_STATE_IN_FS_METADATA,
				&dev_replace->tgtdev->dev_state);
		पूर्ण
		अवरोध;
	पूर्ण

out:
	btrfs_मुक्त_path(path);
	वापस ret;
पूर्ण

/*
 * Initialize a new device क्रम device replace target from a given source dev
 * and path.
 *
 * Return 0 and new device in @device_out, otherwise वापस < 0
 */
अटल पूर्णांक btrfs_init_dev_replace_tgtdev(काष्ठा btrfs_fs_info *fs_info,
				  स्थिर अक्षर *device_path,
				  काष्ठा btrfs_device *srcdev,
				  काष्ठा btrfs_device **device_out)
अणु
	काष्ठा btrfs_device *device;
	काष्ठा block_device *bdev;
	काष्ठा rcu_string *name;
	u64 devid = BTRFS_DEV_REPLACE_DEVID;
	पूर्णांक ret = 0;

	*device_out = शून्य;
	अगर (srcdev->fs_devices->seeding) अणु
		btrfs_err(fs_info, "the filesystem is a seed filesystem!");
		वापस -EINVAL;
	पूर्ण

	bdev = blkdev_get_by_path(device_path, FMODE_WRITE | FMODE_EXCL,
				  fs_info->bdev_holder);
	अगर (IS_ERR(bdev)) अणु
		btrfs_err(fs_info, "target device %s is invalid!", device_path);
		वापस PTR_ERR(bdev);
	पूर्ण

	अगर (!btrfs_check_device_zone_type(fs_info, bdev)) अणु
		btrfs_err(fs_info,
		"dev-replace: zoned type of target device mismatch with filesystem");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	sync_blockdev(bdev);

	list_क्रम_each_entry(device, &fs_info->fs_devices->devices, dev_list) अणु
		अगर (device->bdev == bdev) अणु
			btrfs_err(fs_info,
				  "target device is in the filesystem!");
			ret = -EEXIST;
			जाओ error;
		पूर्ण
	पूर्ण


	अगर (i_size_पढ़ो(bdev->bd_inode) <
	    btrfs_device_get_total_bytes(srcdev)) अणु
		btrfs_err(fs_info,
			  "target device is smaller than source device!");
		ret = -EINVAL;
		जाओ error;
	पूर्ण


	device = btrfs_alloc_device(शून्य, &devid, शून्य);
	अगर (IS_ERR(device)) अणु
		ret = PTR_ERR(device);
		जाओ error;
	पूर्ण

	name = rcu_string_strdup(device_path, GFP_KERNEL);
	अगर (!name) अणु
		btrfs_मुक्त_device(device);
		ret = -ENOMEM;
		जाओ error;
	पूर्ण
	rcu_assign_poपूर्णांकer(device->name, name);

	set_bit(BTRFS_DEV_STATE_WRITEABLE, &device->dev_state);
	device->generation = 0;
	device->io_width = fs_info->sectorsize;
	device->io_align = fs_info->sectorsize;
	device->sector_size = fs_info->sectorsize;
	device->total_bytes = btrfs_device_get_total_bytes(srcdev);
	device->disk_total_bytes = btrfs_device_get_disk_total_bytes(srcdev);
	device->bytes_used = btrfs_device_get_bytes_used(srcdev);
	device->commit_total_bytes = srcdev->commit_total_bytes;
	device->commit_bytes_used = device->bytes_used;
	device->fs_info = fs_info;
	device->bdev = bdev;
	set_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &device->dev_state);
	set_bit(BTRFS_DEV_STATE_REPLACE_TGT, &device->dev_state);
	device->mode = FMODE_EXCL;
	device->dev_stats_valid = 1;
	set_blocksize(device->bdev, BTRFS_BDEV_BLOCKSIZE);
	device->fs_devices = fs_info->fs_devices;

	ret = btrfs_get_dev_zone_info(device);
	अगर (ret)
		जाओ error;

	mutex_lock(&fs_info->fs_devices->device_list_mutex);
	list_add(&device->dev_list, &fs_info->fs_devices->devices);
	fs_info->fs_devices->num_devices++;
	fs_info->fs_devices->खोलो_devices++;
	mutex_unlock(&fs_info->fs_devices->device_list_mutex);

	*device_out = device;
	वापस 0;

error:
	blkdev_put(bdev, FMODE_EXCL);
	वापस ret;
पूर्ण

/*
 * called from commit_transaction. Writes changed device replace state to
 * disk.
 */
पूर्णांक btrfs_run_dev_replace(काष्ठा btrfs_trans_handle *trans)
अणु
	काष्ठा btrfs_fs_info *fs_info = trans->fs_info;
	पूर्णांक ret;
	काष्ठा btrfs_root *dev_root = fs_info->dev_root;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_dev_replace_item *ptr;
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;

	करोwn_पढ़ो(&dev_replace->rwsem);
	अगर (!dev_replace->is_valid ||
	    !dev_replace->item_needs_ग_लिखोback) अणु
		up_पढ़ो(&dev_replace->rwsem);
		वापस 0;
	पूर्ण
	up_पढ़ो(&dev_replace->rwsem);

	key.objectid = 0;
	key.type = BTRFS_DEV_REPLACE_KEY;
	key.offset = 0;

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	ret = btrfs_search_slot(trans, dev_root, &key, path, -1, 1);
	अगर (ret < 0) अणु
		btrfs_warn(fs_info,
			   "error %d while searching for dev_replace item!",
			   ret);
		जाओ out;
	पूर्ण

	अगर (ret == 0 &&
	    btrfs_item_size_nr(path->nodes[0], path->slots[0]) < माप(*ptr)) अणु
		/*
		 * need to delete old one and insert a new one.
		 * Since no attempt is made to recover any old state, अगर the
		 * dev_replace state is 'running', the data on the target
		 * drive is lost.
		 * It would be possible to recover the state: just make sure
		 * that the beginning of the item is never changed and always
		 * contains all the essential inक्रमmation. Then पढ़ो this
		 * minimal set of inक्रमmation and use it as a base क्रम the
		 * new state.
		 */
		ret = btrfs_del_item(trans, dev_root, path);
		अगर (ret != 0) अणु
			btrfs_warn(fs_info,
				   "delete too small dev_replace item failed %d!",
				   ret);
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
			btrfs_warn(fs_info,
				   "insert dev_replace item failed %d!", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	eb = path->nodes[0];
	ptr = btrfs_item_ptr(eb, path->slots[0],
			     काष्ठा btrfs_dev_replace_item);

	करोwn_ग_लिखो(&dev_replace->rwsem);
	अगर (dev_replace->srcdev)
		btrfs_set_dev_replace_src_devid(eb, ptr,
			dev_replace->srcdev->devid);
	अन्यथा
		btrfs_set_dev_replace_src_devid(eb, ptr, (u64)-1);
	btrfs_set_dev_replace_cont_पढ़ोing_from_srcdev_mode(eb, ptr,
		dev_replace->cont_पढ़ोing_from_srcdev_mode);
	btrfs_set_dev_replace_replace_state(eb, ptr,
		dev_replace->replace_state);
	btrfs_set_dev_replace_समय_started(eb, ptr, dev_replace->समय_started);
	btrfs_set_dev_replace_समय_stopped(eb, ptr, dev_replace->समय_stopped);
	btrfs_set_dev_replace_num_ग_लिखो_errors(eb, ptr,
		atomic64_पढ़ो(&dev_replace->num_ग_लिखो_errors));
	btrfs_set_dev_replace_num_uncorrectable_पढ़ो_errors(eb, ptr,
		atomic64_पढ़ो(&dev_replace->num_uncorrectable_पढ़ो_errors));
	dev_replace->cursor_left_last_ग_लिखो_of_item =
		dev_replace->cursor_left;
	btrfs_set_dev_replace_cursor_left(eb, ptr,
		dev_replace->cursor_left_last_ग_लिखो_of_item);
	btrfs_set_dev_replace_cursor_right(eb, ptr,
		dev_replace->cursor_right);
	dev_replace->item_needs_ग_लिखोback = 0;
	up_ग_लिखो(&dev_replace->rwsem);

	btrfs_mark_buffer_dirty(eb);

out:
	btrfs_मुक्त_path(path);

	वापस ret;
पूर्ण

अटल अक्षर* btrfs_dev_name(काष्ठा btrfs_device *device)
अणु
	अगर (!device || test_bit(BTRFS_DEV_STATE_MISSING, &device->dev_state))
		वापस "<missing disk>";
	अन्यथा
		वापस rcu_str_deref(device->name);
पूर्ण

अटल पूर्णांक mark_block_group_to_copy(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा btrfs_device *src_dev)
अणु
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_root *root = fs_info->dev_root;
	काष्ठा btrfs_dev_extent *dev_extent = शून्य;
	काष्ठा btrfs_block_group *cache;
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret = 0;
	u64 chunk_offset;

	/* Do not use "to_copy" on non zoned fileप्रणाली क्रम now */
	अगर (!btrfs_is_zoned(fs_info))
		वापस 0;

	mutex_lock(&fs_info->chunk_mutex);

	/* Ensure we करोn't have pending new block group */
	spin_lock(&fs_info->trans_lock);
	जबतक (fs_info->running_transaction &&
	       !list_empty(&fs_info->running_transaction->dev_update_list)) अणु
		spin_unlock(&fs_info->trans_lock);
		mutex_unlock(&fs_info->chunk_mutex);
		trans = btrfs_attach_transaction(root);
		अगर (IS_ERR(trans)) अणु
			ret = PTR_ERR(trans);
			mutex_lock(&fs_info->chunk_mutex);
			अगर (ret == -ENOENT) अणु
				spin_lock(&fs_info->trans_lock);
				जारी;
			पूर्ण अन्यथा अणु
				जाओ unlock;
			पूर्ण
		पूर्ण

		ret = btrfs_commit_transaction(trans);
		mutex_lock(&fs_info->chunk_mutex);
		अगर (ret)
			जाओ unlock;

		spin_lock(&fs_info->trans_lock);
	पूर्ण
	spin_unlock(&fs_info->trans_lock);

	path = btrfs_alloc_path();
	अगर (!path) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	path->पढ़ोa = READA_FORWARD;
	path->search_commit_root = 1;
	path->skip_locking = 1;

	key.objectid = src_dev->devid;
	key.type = BTRFS_DEV_EXTENT_KEY;
	key.offset = 0;

	ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
	अगर (ret < 0)
		जाओ मुक्त_path;
	अगर (ret > 0) अणु
		अगर (path->slots[0] >=
		    btrfs_header_nritems(path->nodes[0])) अणु
			ret = btrfs_next_leaf(root, path);
			अगर (ret < 0)
				जाओ मुक्त_path;
			अगर (ret > 0) अणु
				ret = 0;
				जाओ मुक्त_path;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण
	पूर्ण

	जबतक (1) अणु
		काष्ठा extent_buffer *leaf = path->nodes[0];
		पूर्णांक slot = path->slots[0];

		btrfs_item_key_to_cpu(leaf, &found_key, slot);

		अगर (found_key.objectid != src_dev->devid)
			अवरोध;

		अगर (found_key.type != BTRFS_DEV_EXTENT_KEY)
			अवरोध;

		अगर (found_key.offset < key.offset)
			अवरोध;

		dev_extent = btrfs_item_ptr(leaf, slot, काष्ठा btrfs_dev_extent);

		chunk_offset = btrfs_dev_extent_chunk_offset(leaf, dev_extent);

		cache = btrfs_lookup_block_group(fs_info, chunk_offset);
		अगर (!cache)
			जाओ skip;

		spin_lock(&cache->lock);
		cache->to_copy = 1;
		spin_unlock(&cache->lock);

		btrfs_put_block_group(cache);

skip:
		ret = btrfs_next_item(root, path);
		अगर (ret != 0) अणु
			अगर (ret > 0)
				ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

मुक्त_path:
	btrfs_मुक्त_path(path);
unlock:
	mutex_unlock(&fs_info->chunk_mutex);

	वापस ret;
पूर्ण

bool btrfs_finish_block_group_to_copy(काष्ठा btrfs_device *srcdev,
				      काष्ठा btrfs_block_group *cache,
				      u64 physical)
अणु
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	u64 chunk_offset = cache->start;
	पूर्णांक num_extents, cur_extent;
	पूर्णांक i;

	/* Do not use "to_copy" on non zoned fileप्रणाली क्रम now */
	अगर (!btrfs_is_zoned(fs_info))
		वापस true;

	spin_lock(&cache->lock);
	अगर (cache->हटाओd) अणु
		spin_unlock(&cache->lock);
		वापस true;
	पूर्ण
	spin_unlock(&cache->lock);

	em = btrfs_get_chunk_map(fs_info, chunk_offset, 1);
	ASSERT(!IS_ERR(em));
	map = em->map_lookup;

	num_extents = cur_extent = 0;
	क्रम (i = 0; i < map->num_stripes; i++) अणु
		/* We have more device extent to copy */
		अगर (srcdev != map->stripes[i].dev)
			जारी;

		num_extents++;
		अगर (physical == map->stripes[i].physical)
			cur_extent = i;
	पूर्ण

	मुक्त_extent_map(em);

	अगर (num_extents > 1 && cur_extent < num_extents - 1) अणु
		/*
		 * Has more stripes on this device. Keep this block group
		 * पढ़ोonly until we finish all the stripes.
		 */
		वापस false;
	पूर्ण

	/* Last stripe on this device */
	spin_lock(&cache->lock);
	cache->to_copy = 0;
	spin_unlock(&cache->lock);

	वापस true;
पूर्ण

अटल पूर्णांक btrfs_dev_replace_start(काष्ठा btrfs_fs_info *fs_info,
		स्थिर अक्षर *tgtdev_name, u64 srcdevid, स्थिर अक्षर *srcdev_name,
		पूर्णांक पढ़ो_src)
अणु
	काष्ठा btrfs_root *root = fs_info->dev_root;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
	पूर्णांक ret;
	काष्ठा btrfs_device *tgt_device = शून्य;
	काष्ठा btrfs_device *src_device = शून्य;

	src_device = btrfs_find_device_by_devspec(fs_info, srcdevid,
						  srcdev_name);
	अगर (IS_ERR(src_device))
		वापस PTR_ERR(src_device);

	अगर (btrfs_pinned_by_swapfile(fs_info, src_device)) अणु
		btrfs_warn_in_rcu(fs_info,
	  "cannot replace device %s (devid %llu) due to active swapfile",
			btrfs_dev_name(src_device), src_device->devid);
		वापस -ETXTBSY;
	पूर्ण

	/*
	 * Here we commit the transaction to make sure commit_total_bytes
	 * of all the devices are updated.
	 */
	trans = btrfs_attach_transaction(root);
	अगर (!IS_ERR(trans)) अणु
		ret = btrfs_commit_transaction(trans);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (PTR_ERR(trans) != -ENOENT) अणु
		वापस PTR_ERR(trans);
	पूर्ण

	ret = btrfs_init_dev_replace_tgtdev(fs_info, tgtdev_name,
					    src_device, &tgt_device);
	अगर (ret)
		वापस ret;

	ret = mark_block_group_to_copy(fs_info, src_device);
	अगर (ret)
		वापस ret;

	करोwn_ग_लिखो(&dev_replace->rwsem);
	चयन (dev_replace->replace_state) अणु
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED:
		अवरोध;
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED:
		ASSERT(0);
		ret = BTRFS_IOCTL_DEV_REPLACE_RESULT_ALREADY_STARTED;
		up_ग_लिखो(&dev_replace->rwsem);
		जाओ leave;
	पूर्ण

	dev_replace->cont_पढ़ोing_from_srcdev_mode = पढ़ो_src;
	dev_replace->srcdev = src_device;
	dev_replace->tgtdev = tgt_device;

	btrfs_info_in_rcu(fs_info,
		      "dev_replace from %s (devid %llu) to %s started",
		      btrfs_dev_name(src_device),
		      src_device->devid,
		      rcu_str_deref(tgt_device->name));

	/*
	 * from now on, the ग_लिखोs to the srcdev are all duplicated to
	 * go to the tgtdev as well (refer to btrfs_map_block()).
	 */
	dev_replace->replace_state = BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED;
	dev_replace->समय_started = kसमय_get_real_seconds();
	dev_replace->cursor_left = 0;
	dev_replace->committed_cursor_left = 0;
	dev_replace->cursor_left_last_ग_लिखो_of_item = 0;
	dev_replace->cursor_right = 0;
	dev_replace->is_valid = 1;
	dev_replace->item_needs_ग_लिखोback = 1;
	atomic64_set(&dev_replace->num_ग_लिखो_errors, 0);
	atomic64_set(&dev_replace->num_uncorrectable_पढ़ो_errors, 0);
	up_ग_लिखो(&dev_replace->rwsem);

	ret = btrfs_sysfs_add_device(tgt_device);
	अगर (ret)
		btrfs_err(fs_info, "kobj add dev failed %d", ret);

	btrfs_रुको_ordered_roots(fs_info, U64_MAX, 0, (u64)-1);

	/* Commit dev_replace state and reserve 1 item क्रम it. */
	trans = btrfs_start_transaction(root, 1);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		करोwn_ग_लिखो(&dev_replace->rwsem);
		dev_replace->replace_state =
			BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED;
		dev_replace->srcdev = शून्य;
		dev_replace->tgtdev = शून्य;
		up_ग_लिखो(&dev_replace->rwsem);
		जाओ leave;
	पूर्ण

	ret = btrfs_commit_transaction(trans);
	WARN_ON(ret);

	/* the disk copy procedure reuses the scrub code */
	ret = btrfs_scrub_dev(fs_info, src_device->devid, 0,
			      btrfs_device_get_total_bytes(src_device),
			      &dev_replace->scrub_progress, 0, 1);

	ret = btrfs_dev_replace_finishing(fs_info, ret);
	अगर (ret == -EINPROGRESS)
		ret = BTRFS_IOCTL_DEV_REPLACE_RESULT_SCRUB_INPROGRESS;

	वापस ret;

leave:
	btrfs_destroy_dev_replace_tgtdev(tgt_device);
	वापस ret;
पूर्ण

पूर्णांक btrfs_dev_replace_by_ioctl(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा btrfs_ioctl_dev_replace_args *args)
अणु
	पूर्णांक ret;

	चयन (args->start.cont_पढ़ोing_from_srcdev_mode) अणु
	हाल BTRFS_IOCTL_DEV_REPLACE_CONT_READING_FROM_SRCDEV_MODE_ALWAYS:
	हाल BTRFS_IOCTL_DEV_REPLACE_CONT_READING_FROM_SRCDEV_MODE_AVOID:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((args->start.srcdevid == 0 && args->start.srcdev_name[0] == '\0') ||
	    args->start.tgtdev_name[0] == '\0')
		वापस -EINVAL;

	ret = btrfs_dev_replace_start(fs_info, args->start.tgtdev_name,
					args->start.srcdevid,
					args->start.srcdev_name,
					args->start.cont_पढ़ोing_from_srcdev_mode);
	args->result = ret;
	/* करोn't warn अगर EINPROGRESS, someone अन्यथा might be running scrub */
	अगर (ret == BTRFS_IOCTL_DEV_REPLACE_RESULT_SCRUB_INPROGRESS ||
	    ret == BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR)
		वापस 0;

	वापस ret;
पूर्ण

/*
 * blocked until all in-flight bios operations are finished.
 */
अटल व्योम btrfs_rm_dev_replace_blocked(काष्ठा btrfs_fs_info *fs_info)
अणु
	set_bit(BTRFS_FS_STATE_DEV_REPLACING, &fs_info->fs_state);
	रुको_event(fs_info->dev_replace.replace_रुको, !percpu_counter_sum(
		   &fs_info->dev_replace.bio_counter));
पूर्ण

/*
 * we have हटाओd target device, it is safe to allow new bios request.
 */
अटल व्योम btrfs_rm_dev_replace_unblocked(काष्ठा btrfs_fs_info *fs_info)
अणु
	clear_bit(BTRFS_FS_STATE_DEV_REPLACING, &fs_info->fs_state);
	wake_up(&fs_info->dev_replace.replace_रुको);
पूर्ण

/*
 * When finishing the device replace, beक्रमe swapping the source device with the
 * target device we must update the chunk allocation state in the target device,
 * as it is empty because replace works by directly copying the chunks and not
 * through the normal chunk allocation path.
 */
अटल पूर्णांक btrfs_set_target_alloc_state(काष्ठा btrfs_device *srcdev,
					काष्ठा btrfs_device *tgtdev)
अणु
	काष्ठा extent_state *cached_state = शून्य;
	u64 start = 0;
	u64 found_start;
	u64 found_end;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&srcdev->fs_info->chunk_mutex);

	जबतक (!find_first_extent_bit(&srcdev->alloc_state, start,
				      &found_start, &found_end,
				      CHUNK_ALLOCATED, &cached_state)) अणु
		ret = set_extent_bits(&tgtdev->alloc_state, found_start,
				      found_end, CHUNK_ALLOCATED);
		अगर (ret)
			अवरोध;
		start = found_end + 1;
	पूर्ण

	मुक्त_extent_state(cached_state);
	वापस ret;
पूर्ण

अटल व्योम btrfs_dev_replace_update_device_in_mapping_tree(
						काष्ठा btrfs_fs_info *fs_info,
						काष्ठा btrfs_device *srcdev,
						काष्ठा btrfs_device *tgtdev)
अणु
	काष्ठा extent_map_tree *em_tree = &fs_info->mapping_tree;
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map;
	u64 start = 0;
	पूर्णांक i;

	ग_लिखो_lock(&em_tree->lock);
	करो अणु
		em = lookup_extent_mapping(em_tree, start, (u64)-1);
		अगर (!em)
			अवरोध;
		map = em->map_lookup;
		क्रम (i = 0; i < map->num_stripes; i++)
			अगर (srcdev == map->stripes[i].dev)
				map->stripes[i].dev = tgtdev;
		start = em->start + em->len;
		मुक्त_extent_map(em);
	पूर्ण जबतक (start);
	ग_लिखो_unlock(&em_tree->lock);
पूर्ण

अटल पूर्णांक btrfs_dev_replace_finishing(काष्ठा btrfs_fs_info *fs_info,
				       पूर्णांक scrub_ret)
अणु
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
	काष्ठा btrfs_device *tgt_device;
	काष्ठा btrfs_device *src_device;
	काष्ठा btrfs_root *root = fs_info->tree_root;
	u8 uuid_पंचांगp[BTRFS_UUID_SIZE];
	काष्ठा btrfs_trans_handle *trans;
	पूर्णांक ret = 0;

	/* करोn't allow cancel or unmount to disturb the finishing procedure */
	mutex_lock(&dev_replace->lock_finishing_cancel_unmount);

	करोwn_पढ़ो(&dev_replace->rwsem);
	/* was the operation canceled, or is it finished? */
	अगर (dev_replace->replace_state !=
	    BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED) अणु
		up_पढ़ो(&dev_replace->rwsem);
		mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);
		वापस 0;
	पूर्ण

	tgt_device = dev_replace->tgtdev;
	src_device = dev_replace->srcdev;
	up_पढ़ो(&dev_replace->rwsem);

	/*
	 * flush all outstanding I/O and inode extent mappings beक्रमe the
	 * copy operation is declared as being finished
	 */
	ret = btrfs_start_delalloc_roots(fs_info, दीर्घ_उच्च, false);
	अगर (ret) अणु
		mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);
		वापस ret;
	पूर्ण
	btrfs_रुको_ordered_roots(fs_info, U64_MAX, 0, (u64)-1);

	अगर (!scrub_ret)
		btrfs_पढ़ोa_हटाओ_dev(src_device);

	/*
	 * We have to use this loop approach because at this poपूर्णांक src_device
	 * has to be available क्रम transaction commit to complete, yet new
	 * chunks shouldn't be allocated on the device.
	 */
	जबतक (1) अणु
		trans = btrfs_start_transaction(root, 0);
		अगर (IS_ERR(trans)) अणु
			btrfs_पढ़ोa_unकरो_हटाओ_dev(src_device);
			mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);
			वापस PTR_ERR(trans);
		पूर्ण
		ret = btrfs_commit_transaction(trans);
		WARN_ON(ret);

		/* Prevent ग_लिखो_all_supers() during the finishing procedure */
		mutex_lock(&fs_info->fs_devices->device_list_mutex);
		/* Prevent new chunks being allocated on the source device */
		mutex_lock(&fs_info->chunk_mutex);

		अगर (!list_empty(&src_device->post_commit_list)) अणु
			mutex_unlock(&fs_info->fs_devices->device_list_mutex);
			mutex_unlock(&fs_info->chunk_mutex);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	करोwn_ग_लिखो(&dev_replace->rwsem);
	dev_replace->replace_state =
		scrub_ret ? BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED
			  : BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED;
	dev_replace->tgtdev = शून्य;
	dev_replace->srcdev = शून्य;
	dev_replace->समय_stopped = kसमय_get_real_seconds();
	dev_replace->item_needs_ग_लिखोback = 1;

	/*
	 * Update allocation state in the new device and replace the old device
	 * with the new one in the mapping tree.
	 */
	अगर (!scrub_ret) अणु
		scrub_ret = btrfs_set_target_alloc_state(src_device, tgt_device);
		अगर (scrub_ret)
			जाओ error;
		btrfs_dev_replace_update_device_in_mapping_tree(fs_info,
								src_device,
								tgt_device);
	पूर्ण अन्यथा अणु
		अगर (scrub_ret != -ECANCELED)
			btrfs_err_in_rcu(fs_info,
				 "btrfs_scrub_dev(%s, %llu, %s) failed %d",
				 btrfs_dev_name(src_device),
				 src_device->devid,
				 rcu_str_deref(tgt_device->name), scrub_ret);
error:
		up_ग_लिखो(&dev_replace->rwsem);
		mutex_unlock(&fs_info->chunk_mutex);
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		btrfs_पढ़ोa_unकरो_हटाओ_dev(src_device);
		btrfs_rm_dev_replace_blocked(fs_info);
		अगर (tgt_device)
			btrfs_destroy_dev_replace_tgtdev(tgt_device);
		btrfs_rm_dev_replace_unblocked(fs_info);
		mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);

		वापस scrub_ret;
	पूर्ण

	btrfs_info_in_rcu(fs_info,
			  "dev_replace from %s (devid %llu) to %s finished",
			  btrfs_dev_name(src_device),
			  src_device->devid,
			  rcu_str_deref(tgt_device->name));
	clear_bit(BTRFS_DEV_STATE_REPLACE_TGT, &tgt_device->dev_state);
	tgt_device->devid = src_device->devid;
	src_device->devid = BTRFS_DEV_REPLACE_DEVID;
	स_नकल(uuid_पंचांगp, tgt_device->uuid, माप(uuid_पंचांगp));
	स_नकल(tgt_device->uuid, src_device->uuid, माप(tgt_device->uuid));
	स_नकल(src_device->uuid, uuid_पंचांगp, माप(src_device->uuid));
	btrfs_device_set_total_bytes(tgt_device, src_device->total_bytes);
	btrfs_device_set_disk_total_bytes(tgt_device,
					  src_device->disk_total_bytes);
	btrfs_device_set_bytes_used(tgt_device, src_device->bytes_used);
	tgt_device->commit_bytes_used = src_device->bytes_used;

	btrfs_assign_next_active_device(src_device, tgt_device);

	list_add(&tgt_device->dev_alloc_list, &fs_info->fs_devices->alloc_list);
	fs_info->fs_devices->rw_devices++;

	up_ग_लिखो(&dev_replace->rwsem);
	btrfs_rm_dev_replace_blocked(fs_info);

	btrfs_rm_dev_replace_हटाओ_srcdev(src_device);

	btrfs_rm_dev_replace_unblocked(fs_info);

	/*
	 * Increment dev_stats_ccnt so that btrfs_run_dev_stats() will
	 * update on-disk dev stats value during commit transaction
	 */
	atomic_inc(&tgt_device->dev_stats_ccnt);

	/*
	 * this is again a consistent state where no dev_replace procedure
	 * is running, the target device is part of the fileप्रणाली, the
	 * source device is not part of the fileप्रणाली anymore and its 1st
	 * superblock is scratched out so that it is no दीर्घer marked to
	 * beदीर्घ to this fileप्रणाली.
	 */
	mutex_unlock(&fs_info->chunk_mutex);
	mutex_unlock(&fs_info->fs_devices->device_list_mutex);

	/* replace the sysfs entry */
	btrfs_sysfs_हटाओ_device(src_device);
	btrfs_sysfs_update_devid(tgt_device);
	अगर (test_bit(BTRFS_DEV_STATE_WRITEABLE, &src_device->dev_state))
		btrfs_scratch_superblocks(fs_info, src_device->bdev,
					  src_device->name->str);

	/* ग_लिखो back the superblocks */
	trans = btrfs_start_transaction(root, 0);
	अगर (!IS_ERR(trans))
		btrfs_commit_transaction(trans);

	mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);

	btrfs_rm_dev_replace_मुक्त_srcdev(src_device);

	वापस 0;
पूर्ण

/*
 * Read progress of device replace status according to the state and last
 * stored position. The value क्रमmat is the same as क्रम
 * btrfs_dev_replace::progress_1000
 */
अटल u64 btrfs_dev_replace_progress(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
	u64 ret = 0;

	चयन (dev_replace->replace_state) अणु
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED:
		ret = 0;
		अवरोध;
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED:
		ret = 1000;
		अवरोध;
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED:
		ret = भाग64_u64(dev_replace->cursor_left,
				भाग_u64(btrfs_device_get_total_bytes(
						dev_replace->srcdev), 1000));
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

व्योम btrfs_dev_replace_status(काष्ठा btrfs_fs_info *fs_info,
			      काष्ठा btrfs_ioctl_dev_replace_args *args)
अणु
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;

	करोwn_पढ़ो(&dev_replace->rwsem);
	/* even अगर !dev_replace_is_valid, the values are good enough क्रम
	 * the replace_status ioctl */
	args->result = BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR;
	args->status.replace_state = dev_replace->replace_state;
	args->status.समय_started = dev_replace->समय_started;
	args->status.समय_stopped = dev_replace->समय_stopped;
	args->status.num_ग_लिखो_errors =
		atomic64_पढ़ो(&dev_replace->num_ग_लिखो_errors);
	args->status.num_uncorrectable_पढ़ो_errors =
		atomic64_पढ़ो(&dev_replace->num_uncorrectable_पढ़ो_errors);
	args->status.progress_1000 = btrfs_dev_replace_progress(fs_info);
	up_पढ़ो(&dev_replace->rwsem);
पूर्ण

पूर्णांक btrfs_dev_replace_cancel(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
	काष्ठा btrfs_device *tgt_device = शून्य;
	काष्ठा btrfs_device *src_device = शून्य;
	काष्ठा btrfs_trans_handle *trans;
	काष्ठा btrfs_root *root = fs_info->tree_root;
	पूर्णांक result;
	पूर्णांक ret;

	अगर (sb_rकरोnly(fs_info->sb))
		वापस -EROFS;

	mutex_lock(&dev_replace->lock_finishing_cancel_unmount);
	करोwn_ग_लिखो(&dev_replace->rwsem);
	चयन (dev_replace->replace_state) अणु
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED:
		result = BTRFS_IOCTL_DEV_REPLACE_RESULT_NOT_STARTED;
		up_ग_लिखो(&dev_replace->rwsem);
		अवरोध;
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED:
		tgt_device = dev_replace->tgtdev;
		src_device = dev_replace->srcdev;
		up_ग_लिखो(&dev_replace->rwsem);
		ret = btrfs_scrub_cancel(fs_info);
		अगर (ret < 0) अणु
			result = BTRFS_IOCTL_DEV_REPLACE_RESULT_NOT_STARTED;
		पूर्ण अन्यथा अणु
			result = BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR;
			/*
			 * btrfs_dev_replace_finishing() will handle the
			 * cleanup part
			 */
			btrfs_info_in_rcu(fs_info,
				"dev_replace from %s (devid %llu) to %s canceled",
				btrfs_dev_name(src_device), src_device->devid,
				btrfs_dev_name(tgt_device));
		पूर्ण
		अवरोध;
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED:
		/*
		 * Scrub करोing the replace isn't running so we need to करो the
		 * cleanup step of btrfs_dev_replace_finishing() here
		 */
		result = BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR;
		tgt_device = dev_replace->tgtdev;
		src_device = dev_replace->srcdev;
		dev_replace->tgtdev = शून्य;
		dev_replace->srcdev = शून्य;
		dev_replace->replace_state =
				BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED;
		dev_replace->समय_stopped = kसमय_get_real_seconds();
		dev_replace->item_needs_ग_लिखोback = 1;

		up_ग_लिखो(&dev_replace->rwsem);

		/* Scrub क्रम replace must not be running in suspended state */
		ret = btrfs_scrub_cancel(fs_info);
		ASSERT(ret != -ENOTCONN);

		trans = btrfs_start_transaction(root, 0);
		अगर (IS_ERR(trans)) अणु
			mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);
			वापस PTR_ERR(trans);
		पूर्ण
		ret = btrfs_commit_transaction(trans);
		WARN_ON(ret);

		btrfs_info_in_rcu(fs_info,
		"suspended dev_replace from %s (devid %llu) to %s canceled",
			btrfs_dev_name(src_device), src_device->devid,
			btrfs_dev_name(tgt_device));

		अगर (tgt_device)
			btrfs_destroy_dev_replace_tgtdev(tgt_device);
		अवरोध;
	शेष:
		up_ग_लिखो(&dev_replace->rwsem);
		result = -EINVAL;
	पूर्ण

	mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);
	वापस result;
पूर्ण

व्योम btrfs_dev_replace_suspend_क्रम_unmount(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;

	mutex_lock(&dev_replace->lock_finishing_cancel_unmount);
	करोwn_ग_लिखो(&dev_replace->rwsem);

	चयन (dev_replace->replace_state) अणु
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED:
		अवरोध;
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED:
		dev_replace->replace_state =
			BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED;
		dev_replace->समय_stopped = kसमय_get_real_seconds();
		dev_replace->item_needs_ग_लिखोback = 1;
		btrfs_info(fs_info, "suspending dev_replace for unmount");
		अवरोध;
	पूर्ण

	up_ग_लिखो(&dev_replace->rwsem);
	mutex_unlock(&dev_replace->lock_finishing_cancel_unmount);
पूर्ण

/* resume dev_replace procedure that was पूर्णांकerrupted by unmount */
पूर्णांक btrfs_resume_dev_replace_async(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;

	करोwn_ग_लिखो(&dev_replace->rwsem);

	चयन (dev_replace->replace_state) अणु
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED:
		up_ग_लिखो(&dev_replace->rwsem);
		वापस 0;
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED:
		अवरोध;
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED:
		dev_replace->replace_state =
			BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED;
		अवरोध;
	पूर्ण
	अगर (!dev_replace->tgtdev || !dev_replace->tgtdev->bdev) अणु
		btrfs_info(fs_info,
			   "cannot continue dev_replace, tgtdev is missing");
		btrfs_info(fs_info,
			   "you may cancel the operation after 'mount -o degraded'");
		dev_replace->replace_state =
					BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED;
		up_ग_लिखो(&dev_replace->rwsem);
		वापस 0;
	पूर्ण
	up_ग_लिखो(&dev_replace->rwsem);

	/*
	 * This could collide with a छोड़ोd balance, but the exclusive op logic
	 * should never allow both to start and छोड़ो. We करोn't want to allow
	 * dev-replace to start anyway.
	 */
	अगर (!btrfs_exclop_start(fs_info, BTRFS_EXCLOP_DEV_REPLACE)) अणु
		करोwn_ग_लिखो(&dev_replace->rwsem);
		dev_replace->replace_state =
					BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED;
		up_ग_लिखो(&dev_replace->rwsem);
		btrfs_info(fs_info,
		"cannot resume dev-replace, other exclusive operation running");
		वापस 0;
	पूर्ण

	task = kthपढ़ो_run(btrfs_dev_replace_kthपढ़ो, fs_info, "btrfs-devrepl");
	वापस PTR_ERR_OR_ZERO(task);
पूर्ण

अटल पूर्णांक btrfs_dev_replace_kthपढ़ो(व्योम *data)
अणु
	काष्ठा btrfs_fs_info *fs_info = data;
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
	u64 progress;
	पूर्णांक ret;

	progress = btrfs_dev_replace_progress(fs_info);
	progress = भाग_u64(progress, 10);
	btrfs_info_in_rcu(fs_info,
		"continuing dev_replace from %s (devid %llu) to target %s @%u%%",
		btrfs_dev_name(dev_replace->srcdev),
		dev_replace->srcdev->devid,
		btrfs_dev_name(dev_replace->tgtdev),
		(अचिन्हित पूर्णांक)progress);

	ret = btrfs_scrub_dev(fs_info, dev_replace->srcdev->devid,
			      dev_replace->committed_cursor_left,
			      btrfs_device_get_total_bytes(dev_replace->srcdev),
			      &dev_replace->scrub_progress, 0, 1);
	ret = btrfs_dev_replace_finishing(fs_info, ret);
	WARN_ON(ret && ret != -ECANCELED);

	btrfs_exclop_finish(fs_info);
	वापस 0;
पूर्ण

पूर्णांक __pure btrfs_dev_replace_is_ongoing(काष्ठा btrfs_dev_replace *dev_replace)
अणु
	अगर (!dev_replace->is_valid)
		वापस 0;

	चयन (dev_replace->replace_state) अणु
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED:
		वापस 0;
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED:
	हाल BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED:
		/*
		 * वापस true even अगर tgtdev is missing (this is
		 * something that can happen अगर the dev_replace
		 * procedure is suspended by an umount and then
		 * the tgtdev is missing (or "btrfs dev scan") was
		 * not called and the fileप्रणाली is remounted
		 * in degraded state. This करोes not stop the
		 * dev_replace procedure. It needs to be canceled
		 * manually अगर the cancellation is wanted.
		 */
		अवरोध;
	पूर्ण
	वापस 1;
पूर्ण

व्योम btrfs_bio_counter_inc_noblocked(काष्ठा btrfs_fs_info *fs_info)
अणु
	percpu_counter_inc(&fs_info->dev_replace.bio_counter);
पूर्ण

व्योम btrfs_bio_counter_sub(काष्ठा btrfs_fs_info *fs_info, s64 amount)
अणु
	percpu_counter_sub(&fs_info->dev_replace.bio_counter, amount);
	cond_wake_up_nomb(&fs_info->dev_replace.replace_रुको);
पूर्ण

व्योम btrfs_bio_counter_inc_blocked(काष्ठा btrfs_fs_info *fs_info)
अणु
	जबतक (1) अणु
		percpu_counter_inc(&fs_info->dev_replace.bio_counter);
		अगर (likely(!test_bit(BTRFS_FS_STATE_DEV_REPLACING,
				     &fs_info->fs_state)))
			अवरोध;

		btrfs_bio_counter_dec(fs_info);
		रुको_event(fs_info->dev_replace.replace_रुको,
			   !test_bit(BTRFS_FS_STATE_DEV_REPLACING,
				     &fs_info->fs_state));
	पूर्ण
पूर्ण
