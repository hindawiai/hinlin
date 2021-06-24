<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2014 Facebook.  All rights reserved.
 */

#अगर_अघोषित BTRFS_REF_VERIFY_H
#घोषणा BTRFS_REF_VERIFY_H

#अगर_घोषित CONFIG_BTRFS_FS_REF_VERIFY
पूर्णांक btrfs_build_ref_tree(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_मुक्त_ref_cache(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_ref_tree_mod(काष्ठा btrfs_fs_info *fs_info,
		       काष्ठा btrfs_ref *generic_ref);
व्योम btrfs_मुक्त_ref_tree_range(काष्ठा btrfs_fs_info *fs_info, u64 start,
			       u64 len);

अटल अंतरभूत व्योम btrfs_init_ref_verअगरy(काष्ठा btrfs_fs_info *fs_info)
अणु
	spin_lock_init(&fs_info->ref_verअगरy_lock);
	fs_info->block_tree = RB_ROOT;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक btrfs_build_ref_tree(काष्ठा btrfs_fs_info *fs_info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम btrfs_मुक्त_ref_cache(काष्ठा btrfs_fs_info *fs_info)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक btrfs_ref_tree_mod(काष्ठा btrfs_fs_info *fs_info,
		       काष्ठा btrfs_ref *generic_ref)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम btrfs_मुक्त_ref_tree_range(काष्ठा btrfs_fs_info *fs_info,
					     u64 start, u64 len)
अणु
पूर्ण

अटल अंतरभूत व्योम btrfs_init_ref_verअगरy(काष्ठा btrfs_fs_info *fs_info)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_BTRFS_FS_REF_VERIFY */

#पूर्ण_अगर
