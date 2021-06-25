<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015 Facebook.  All rights reserved.
 */

#अगर_अघोषित BTRFS_FREE_SPACE_TREE_H
#घोषणा BTRFS_FREE_SPACE_TREE_H

काष्ठा btrfs_caching_control;

/*
 * The शेष size क्रम new मुक्त space biपंचांगap items. The last biपंचांगap in a block
 * group may be truncated, and none of the मुक्त space tree code assumes that
 * existing biपंचांगaps are this size.
 */
#घोषणा BTRFS_FREE_SPACE_BITMAP_SIZE 256
#घोषणा BTRFS_FREE_SPACE_BITMAP_BITS (BTRFS_FREE_SPACE_BITMAP_SIZE * BITS_PER_BYTE)

व्योम set_मुक्त_space_tree_thresholds(काष्ठा btrfs_block_group *block_group);
पूर्णांक btrfs_create_मुक्त_space_tree(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_clear_मुक्त_space_tree(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक load_मुक्त_space_tree(काष्ठा btrfs_caching_control *caching_ctl);
पूर्णांक add_block_group_मुक्त_space(काष्ठा btrfs_trans_handle *trans,
			       काष्ठा btrfs_block_group *block_group);
पूर्णांक हटाओ_block_group_मुक्त_space(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_block_group *block_group);
पूर्णांक add_to_मुक्त_space_tree(काष्ठा btrfs_trans_handle *trans,
			   u64 start, u64 size);
पूर्णांक हटाओ_from_मुक्त_space_tree(काष्ठा btrfs_trans_handle *trans,
				u64 start, u64 size);

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
काष्ठा btrfs_मुक्त_space_info *
search_मुक्त_space_info(काष्ठा btrfs_trans_handle *trans,
		       काष्ठा btrfs_block_group *block_group,
		       काष्ठा btrfs_path *path, पूर्णांक cow);
पूर्णांक __add_to_मुक्त_space_tree(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_block_group *block_group,
			     काष्ठा btrfs_path *path, u64 start, u64 size);
पूर्णांक __हटाओ_from_मुक्त_space_tree(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_block_group *block_group,
				  काष्ठा btrfs_path *path, u64 start, u64 size);
पूर्णांक convert_मुक्त_space_to_biपंचांगaps(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_block_group *block_group,
				  काष्ठा btrfs_path *path);
पूर्णांक convert_मुक्त_space_to_extents(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_block_group *block_group,
				  काष्ठा btrfs_path *path);
पूर्णांक मुक्त_space_test_bit(काष्ठा btrfs_block_group *block_group,
			काष्ठा btrfs_path *path, u64 offset);
#पूर्ण_अगर

#पूर्ण_अगर
