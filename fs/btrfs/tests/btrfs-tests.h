<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2013 Fusion IO.  All rights reserved.
 */

#अगर_अघोषित BTRFS_TESTS_H
#घोषणा BTRFS_TESTS_H

#अगर_घोषित CONFIG_BTRFS_FS_RUN_SANITY_TESTS
पूर्णांक btrfs_run_sanity_tests(व्योम);

#घोषणा test_msg(fmt, ...) pr_info("BTRFS: selftest: " fmt "\n", ##__VA_ARGS__)
#घोषणा test_err(fmt, ...) pr_err("BTRFS: selftest: %s:%d " fmt "\n",	\
		__खाता__, __LINE__, ##__VA_ARGS__)

#घोषणा test_std_err(index)	test_err("%s", test_error[index])

क्रमागत अणु
	TEST_ALLOC_FS_INFO,
	TEST_ALLOC_ROOT,
	TEST_ALLOC_EXTENT_BUFFER,
	TEST_ALLOC_PATH,
	TEST_ALLOC_INODE,
	TEST_ALLOC_BLOCK_GROUP,
	TEST_ALLOC_EXTENT_MAP,
पूर्ण;

बाह्य स्थिर अक्षर *test_error[];

काष्ठा btrfs_root;
काष्ठा btrfs_trans_handle;

पूर्णांक btrfs_test_extent_buffer_operations(u32 sectorsize, u32 nodesize);
पूर्णांक btrfs_test_मुक्त_space_cache(u32 sectorsize, u32 nodesize);
पूर्णांक btrfs_test_extent_io(u32 sectorsize, u32 nodesize);
पूर्णांक btrfs_test_inodes(u32 sectorsize, u32 nodesize);
पूर्णांक btrfs_test_qgroups(u32 sectorsize, u32 nodesize);
पूर्णांक btrfs_test_मुक्त_space_tree(u32 sectorsize, u32 nodesize);
पूर्णांक btrfs_test_extent_map(व्योम);
काष्ठा inode *btrfs_new_test_inode(व्योम);
काष्ठा btrfs_fs_info *btrfs_alloc_dummy_fs_info(u32 nodesize, u32 sectorsize);
व्योम btrfs_मुक्त_dummy_fs_info(काष्ठा btrfs_fs_info *fs_info);
व्योम btrfs_मुक्त_dummy_root(काष्ठा btrfs_root *root);
काष्ठा btrfs_block_group *
btrfs_alloc_dummy_block_group(काष्ठा btrfs_fs_info *fs_info, अचिन्हित दीर्घ length);
व्योम btrfs_मुक्त_dummy_block_group(काष्ठा btrfs_block_group *cache);
व्योम btrfs_init_dummy_trans(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_fs_info *fs_info);
काष्ठा btrfs_device *btrfs_alloc_dummy_device(काष्ठा btrfs_fs_info *fs_info);
#अन्यथा
अटल अंतरभूत पूर्णांक btrfs_run_sanity_tests(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
