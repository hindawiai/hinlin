<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_DISCARD_H
#घोषणा BTRFS_DISCARD_H

#समावेश <linux/sizes.h>

काष्ठा btrfs_fs_info;
काष्ठा btrfs_discard_ctl;
काष्ठा btrfs_block_group;

/* Discard size limits */
#घोषणा BTRFS_ASYNC_DISCARD_DEFAULT_MAX_SIZE		(SZ_64M)
#घोषणा BTRFS_ASYNC_DISCARD_MAX_FILTER			(SZ_1M)
#घोषणा BTRFS_ASYNC_DISCARD_MIN_FILTER			(SZ_32K)

/* List operations */
व्योम btrfs_discard_check_filter(काष्ठा btrfs_block_group *block_group, u64 bytes);

/* Work operations */
व्योम btrfs_discard_cancel_work(काष्ठा btrfs_discard_ctl *discard_ctl,
			       काष्ठा btrfs_block_group *block_group);
व्योम btrfs_discard_queue_work(काष्ठा btrfs_discard_ctl *discard_ctl,
			      काष्ठा btrfs_block_group *block_group);
व्योम btrfs_discard_schedule_work(काष्ठा btrfs_discard_ctl *discard_ctl,
				 bool override);
bool btrfs_run_discard_work(काष्ठा btrfs_discard_ctl *discard_ctl);

/* Update operations */
व्योम btrfs_discard_calc_delay(काष्ठा btrfs_discard_ctl *discard_ctl);
व्योम btrfs_discard_update_discardable(काष्ठा btrfs_block_group *block_group);

/* Setup/cleanup operations */
व्योम btrfs_discard_punt_unused_bgs_list(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_discard_resume(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_discard_stop(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_discard_init(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_discard_cleanup(काष्ठा btrfs_fs_info *fs_info);

#पूर्ण_अगर
