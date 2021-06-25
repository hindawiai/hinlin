<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#अगर_अघोषित BTRFS_DISK_IO_H
#घोषणा BTRFS_DISK_IO_H

#घोषणा BTRFS_SUPER_INFO_OFFSET SZ_64K
#घोषणा BTRFS_SUPER_INFO_SIZE 4096

#घोषणा BTRFS_SUPER_MIRROR_MAX	 3
#घोषणा BTRFS_SUPER_MIRROR_SHIFT 12

/*
 * Fixed blocksize क्रम all devices, applies to specअगरic ways of पढ़ोing
 * metadata like superblock. Must meet the set_blocksize requirements.
 *
 * Do not change.
 */
#घोषणा BTRFS_BDEV_BLOCKSIZE	(4096)

क्रमागत btrfs_wq_endio_type अणु
	BTRFS_WQ_ENDIO_DATA,
	BTRFS_WQ_ENDIO_METADATA,
	BTRFS_WQ_ENDIO_FREE_SPACE,
	BTRFS_WQ_ENDIO_RAID56,
पूर्ण;

अटल अंतरभूत u64 btrfs_sb_offset(पूर्णांक mirror)
अणु
	u64 start = SZ_16K;
	अगर (mirror)
		वापस start << (BTRFS_SUPER_MIRROR_SHIFT * mirror);
	वापस BTRFS_SUPER_INFO_OFFSET;
पूर्ण

काष्ठा btrfs_device;
काष्ठा btrfs_fs_devices;

व्योम btrfs_check_leaked_roots(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_init_fs_info(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_verअगरy_level_key(काष्ठा extent_buffer *eb, पूर्णांक level,
			   काष्ठा btrfs_key *first_key, u64 parent_transid);
काष्ठा extent_buffer *पढ़ो_tree_block(काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
				      u64 owner_root, u64 parent_transid,
				      पूर्णांक level, काष्ठा btrfs_key *first_key);
काष्ठा extent_buffer *btrfs_find_create_tree_block(
						काष्ठा btrfs_fs_info *fs_info,
						u64 bytenr, u64 owner_root,
						पूर्णांक level);
व्योम btrfs_clean_tree_block(काष्ठा extent_buffer *buf);
व्योम btrfs_clear_oneshot_options(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_start_pre_rw_mount(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक __cold खोलो_ctree(काष्ठा super_block *sb,
	       काष्ठा btrfs_fs_devices *fs_devices,
	       अक्षर *options);
व्योम __cold बंद_ctree(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक ग_लिखो_all_supers(काष्ठा btrfs_fs_info *fs_info, पूर्णांक max_mirrors);
काष्ठा btrfs_super_block *btrfs_पढ़ो_dev_super(काष्ठा block_device *bdev);
काष्ठा btrfs_super_block *btrfs_पढ़ो_dev_one_super(काष्ठा block_device *bdev,
						   पूर्णांक copy_num);
पूर्णांक btrfs_commit_super(काष्ठा btrfs_fs_info *fs_info);
काष्ठा btrfs_root *btrfs_पढ़ो_tree_root(काष्ठा btrfs_root *tree_root,
					काष्ठा btrfs_key *key);
पूर्णांक btrfs_insert_fs_root(काष्ठा btrfs_fs_info *fs_info,
			 काष्ठा btrfs_root *root);
व्योम btrfs_मुक्त_fs_roots(काष्ठा btrfs_fs_info *fs_info);

काष्ठा btrfs_root *btrfs_get_fs_root(काष्ठा btrfs_fs_info *fs_info,
				     u64 objectid, bool check_ref);
काष्ठा btrfs_root *btrfs_get_new_fs_root(काष्ठा btrfs_fs_info *fs_info,
					 u64 objectid, dev_t anon_dev);
काष्ठा btrfs_root *btrfs_get_fs_root_commit_root(काष्ठा btrfs_fs_info *fs_info,
						 काष्ठा btrfs_path *path,
						 u64 objectid);

व्योम btrfs_मुक्त_fs_info(काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_cleanup_fs_roots(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_btree_balance_dirty(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_btree_balance_dirty_nodelay(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_drop_and_मुक्त_fs_root(काष्ठा btrfs_fs_info *fs_info,
				 काष्ठा btrfs_root *root);
पूर्णांक btrfs_validate_metadata_buffer(काष्ठा btrfs_io_bio *io_bio,
				   काष्ठा page *page, u64 start, u64 end,
				   पूर्णांक mirror);
blk_status_t btrfs_submit_metadata_bio(काष्ठा inode *inode, काष्ठा bio *bio,
				       पूर्णांक mirror_num, अचिन्हित दीर्घ bio_flags);
#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
काष्ठा btrfs_root *btrfs_alloc_dummy_root(काष्ठा btrfs_fs_info *fs_info);
#पूर्ण_अगर

/*
 * This function is used to grab the root, and aव्योम it is मुक्तd when we
 * access it. But it करोesn't ensure that the tree is not dropped.
 *
 * If you want to ensure the whole tree is safe, you should use
 * 	fs_info->subvol_srcu
 */
अटल अंतरभूत काष्ठा btrfs_root *btrfs_grab_root(काष्ठा btrfs_root *root)
अणु
	अगर (!root)
		वापस शून्य;
	अगर (refcount_inc_not_zero(&root->refs))
		वापस root;
	वापस शून्य;
पूर्ण

व्योम btrfs_put_root(काष्ठा btrfs_root *root);
व्योम btrfs_mark_buffer_dirty(काष्ठा extent_buffer *buf);
पूर्णांक btrfs_buffer_uptodate(काष्ठा extent_buffer *buf, u64 parent_transid,
			  पूर्णांक atomic);
पूर्णांक btrfs_पढ़ो_buffer(काष्ठा extent_buffer *buf, u64 parent_transid, पूर्णांक level,
		      काष्ठा btrfs_key *first_key);
blk_status_t btrfs_bio_wq_end_io(काष्ठा btrfs_fs_info *info, काष्ठा bio *bio,
			क्रमागत btrfs_wq_endio_type metadata);
blk_status_t btrfs_wq_submit_bio(काष्ठा inode *inode, काष्ठा bio *bio,
				 पूर्णांक mirror_num, अचिन्हित दीर्घ bio_flags,
				 u64 dio_file_offset,
				 extent_submit_bio_start_t *submit_bio_start);
blk_status_t btrfs_submit_bio_करोne(व्योम *निजी_data, काष्ठा bio *bio,
			  पूर्णांक mirror_num);
पूर्णांक btrfs_alloc_log_tree_node(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_root *root);
पूर्णांक btrfs_init_log_root_tree(काष्ठा btrfs_trans_handle *trans,
			     काष्ठा btrfs_fs_info *fs_info);
पूर्णांक btrfs_add_log_tree(काष्ठा btrfs_trans_handle *trans,
		       काष्ठा btrfs_root *root);
व्योम btrfs_cleanup_dirty_bgs(काष्ठा btrfs_transaction *trans,
			     काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_cleanup_one_transaction(काष्ठा btrfs_transaction *trans,
				  काष्ठा btrfs_fs_info *fs_info);
काष्ठा btrfs_root *btrfs_create_tree(काष्ठा btrfs_trans_handle *trans,
				     u64 objectid);
पूर्णांक btree_lock_page_hook(काष्ठा page *page, व्योम *data,
				व्योम (*flush_fn)(व्योम *));
पूर्णांक btrfs_get_num_tolerated_disk_barrier_failures(u64 flags);
पूर्णांक btrfs_get_मुक्त_objectid(काष्ठा btrfs_root *root, u64 *objectid);
पूर्णांक btrfs_init_root_मुक्त_objectid(काष्ठा btrfs_root *root);
पूर्णांक __init btrfs_end_io_wq_init(व्योम);
व्योम __cold btrfs_end_io_wq_निकास(व्योम);

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
व्योम btrfs_set_buffer_lockdep_class(u64 objectid,
			            काष्ठा extent_buffer *eb, पूर्णांक level);
#अन्यथा
अटल अंतरभूत व्योम btrfs_set_buffer_lockdep_class(u64 objectid,
					काष्ठा extent_buffer *eb, पूर्णांक level)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
