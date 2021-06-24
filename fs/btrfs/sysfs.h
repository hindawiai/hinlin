<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_SYSFS_H
#घोषणा BTRFS_SYSFS_H

#समावेश <linux/kobject.h>

क्रमागत btrfs_feature_set अणु
	FEAT_COMPAT,
	FEAT_COMPAT_RO,
	FEAT_INCOMPAT,
	FEAT_MAX
पूर्ण;

अक्षर *btrfs_prपूर्णांकable_features(क्रमागत btrfs_feature_set set, u64 flags);
स्थिर अक्षर *btrfs_feature_set_name(क्रमागत btrfs_feature_set set);
पूर्णांक btrfs_sysfs_add_device(काष्ठा btrfs_device *device);
व्योम btrfs_sysfs_हटाओ_device(काष्ठा btrfs_device *device);
पूर्णांक btrfs_sysfs_add_fsid(काष्ठा btrfs_fs_devices *fs_devs);
व्योम btrfs_sysfs_हटाओ_fsid(काष्ठा btrfs_fs_devices *fs_devs);
व्योम btrfs_sysfs_update_sprout_fsid(काष्ठा btrfs_fs_devices *fs_devices);
व्योम btrfs_sysfs_feature_update(काष्ठा btrfs_fs_info *fs_info,
		u64 bit, क्रमागत btrfs_feature_set set);
व्योम btrfs_kobject_uevent(काष्ठा block_device *bdev, क्रमागत kobject_action action);

पूर्णांक __init btrfs_init_sysfs(व्योम);
व्योम __cold btrfs_निकास_sysfs(व्योम);
पूर्णांक btrfs_sysfs_add_mounted(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_sysfs_हटाओ_mounted(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_sysfs_add_block_group_type(काष्ठा btrfs_block_group *cache);
पूर्णांक btrfs_sysfs_add_space_info_type(काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा btrfs_space_info *space_info);
व्योम btrfs_sysfs_हटाओ_space_info(काष्ठा btrfs_space_info *space_info);
व्योम btrfs_sysfs_update_devid(काष्ठा btrfs_device *device);

पूर्णांक btrfs_sysfs_add_one_qgroup(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_qgroup *qgroup);
व्योम btrfs_sysfs_del_qgroups(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_sysfs_add_qgroups(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_sysfs_del_one_qgroup(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा btrfs_qgroup *qgroup);

#पूर्ण_अगर
