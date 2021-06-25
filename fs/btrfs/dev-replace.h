<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STRATO AG 2012.  All rights reserved.
 */

#अगर_अघोषित BTRFS_DEV_REPLACE_H
#घोषणा BTRFS_DEV_REPLACE_H

काष्ठा btrfs_ioctl_dev_replace_args;

पूर्णांक btrfs_init_dev_replace(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_run_dev_replace(काष्ठा btrfs_trans_handle *trans);
पूर्णांक btrfs_dev_replace_by_ioctl(काष्ठा btrfs_fs_info *fs_info,
			    काष्ठा btrfs_ioctl_dev_replace_args *args);
व्योम btrfs_dev_replace_status(काष्ठा btrfs_fs_info *fs_info,
			      काष्ठा btrfs_ioctl_dev_replace_args *args);
पूर्णांक btrfs_dev_replace_cancel(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_dev_replace_suspend_क्रम_unmount(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_resume_dev_replace_async(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक __pure btrfs_dev_replace_is_ongoing(काष्ठा btrfs_dev_replace *dev_replace);
bool btrfs_finish_block_group_to_copy(काष्ठा btrfs_device *srcdev,
				      काष्ठा btrfs_block_group *cache,
				      u64 physical);

#पूर्ण_अगर
