<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_DELALLOC_SPACE_H
#घोषणा BTRFS_DELALLOC_SPACE_H

काष्ठा extent_changeset;

पूर्णांक btrfs_alloc_data_chunk_ondemand(काष्ठा btrfs_inode *inode, u64 bytes);
पूर्णांक btrfs_check_data_मुक्त_space(काष्ठा btrfs_inode *inode,
			काष्ठा extent_changeset **reserved, u64 start, u64 len);
व्योम btrfs_मुक्त_reserved_data_space(काष्ठा btrfs_inode *inode,
			काष्ठा extent_changeset *reserved, u64 start, u64 len);
व्योम btrfs_delalloc_release_space(काष्ठा btrfs_inode *inode,
				  काष्ठा extent_changeset *reserved,
				  u64 start, u64 len, bool qgroup_मुक्त);
व्योम btrfs_मुक्त_reserved_data_space_noquota(काष्ठा btrfs_fs_info *fs_info,
					    u64 len);
व्योम btrfs_delalloc_release_metadata(काष्ठा btrfs_inode *inode, u64 num_bytes,
				     bool qgroup_मुक्त);
पूर्णांक btrfs_delalloc_reserve_space(काष्ठा btrfs_inode *inode,
			काष्ठा extent_changeset **reserved, u64 start, u64 len);

#पूर्ण_अगर /* BTRFS_DELALLOC_SPACE_H */
