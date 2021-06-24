<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 Fusion IO.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/magic.h>
#समावेश "btrfs-tests.h"
#समावेश "../ctree.h"
#समावेश "../free-space-cache.h"
#समावेश "../free-space-tree.h"
#समावेश "../transaction.h"
#समावेश "../volumes.h"
#समावेश "../disk-io.h"
#समावेश "../qgroup.h"
#समावेश "../block-group.h"

अटल काष्ठा vfsmount *test_mnt = शून्य;

स्थिर अक्षर *test_error[] = अणु
	[TEST_ALLOC_FS_INFO]	     = "cannot allocate fs_info",
	[TEST_ALLOC_ROOT]	     = "cannot allocate root",
	[TEST_ALLOC_EXTENT_BUFFER]   = "cannot extent buffer",
	[TEST_ALLOC_PATH]	     = "cannot allocate path",
	[TEST_ALLOC_INODE]	     = "cannot allocate inode",
	[TEST_ALLOC_BLOCK_GROUP]     = "cannot allocate block group",
	[TEST_ALLOC_EXTENT_MAP]      = "cannot allocate extent map",
पूर्ण;

अटल स्थिर काष्ठा super_operations btrfs_test_super_ops = अणु
	.alloc_inode	= btrfs_alloc_inode,
	.destroy_inode	= btrfs_test_destroy_inode,
पूर्ण;


अटल पूर्णांक btrfs_test_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा pseuकरो_fs_context *ctx = init_pseuकरो(fc, BTRFS_TEST_MAGIC);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->ops = &btrfs_test_super_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type test_type = अणु
	.name		= "btrfs_test_fs",
	.init_fs_context = btrfs_test_init_fs_context,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;

काष्ठा inode *btrfs_new_test_inode(व्योम)
अणु
	काष्ठा inode *inode;

	inode = new_inode(test_mnt->mnt_sb);
	अगर (!inode)
		वापस शून्य;

	inode->i_mode = S_IFREG;
	BTRFS_I(inode)->location.type = BTRFS_INODE_ITEM_KEY;
	BTRFS_I(inode)->location.objectid = BTRFS_FIRST_FREE_OBJECTID;
	BTRFS_I(inode)->location.offset = 0;
	inode_init_owner(&init_user_ns, inode, शून्य, S_IFREG);

	वापस inode;
पूर्ण

अटल पूर्णांक btrfs_init_test_fs(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_fileप्रणाली(&test_type);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "btrfs: cannot register test file system\n");
		वापस ret;
	पूर्ण

	test_mnt = kern_mount(&test_type);
	अगर (IS_ERR(test_mnt)) अणु
		prपूर्णांकk(KERN_ERR "btrfs: cannot mount test file system\n");
		unरेजिस्टर_fileप्रणाली(&test_type);
		वापस PTR_ERR(test_mnt);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम btrfs_destroy_test_fs(व्योम)
अणु
	kern_unmount(test_mnt);
	unरेजिस्टर_fileप्रणाली(&test_type);
पूर्ण

काष्ठा btrfs_device *btrfs_alloc_dummy_device(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा btrfs_device *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	extent_io_tree_init(शून्य, &dev->alloc_state, 0, शून्य);
	INIT_LIST_HEAD(&dev->dev_list);
	list_add(&dev->dev_list, &fs_info->fs_devices->devices);

	वापस dev;
पूर्ण

अटल व्योम btrfs_मुक्त_dummy_device(काष्ठा btrfs_device *dev)
अणु
	extent_io_tree_release(&dev->alloc_state);
	kमुक्त(dev);
पूर्ण

काष्ठा btrfs_fs_info *btrfs_alloc_dummy_fs_info(u32 nodesize, u32 sectorsize)
अणु
	काष्ठा btrfs_fs_info *fs_info = kzalloc(माप(काष्ठा btrfs_fs_info),
						GFP_KERNEL);

	अगर (!fs_info)
		वापस fs_info;
	fs_info->fs_devices = kzalloc(माप(काष्ठा btrfs_fs_devices),
				      GFP_KERNEL);
	अगर (!fs_info->fs_devices) अणु
		kमुक्त(fs_info);
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&fs_info->fs_devices->devices);

	fs_info->super_copy = kzalloc(माप(काष्ठा btrfs_super_block),
				      GFP_KERNEL);
	अगर (!fs_info->super_copy) अणु
		kमुक्त(fs_info->fs_devices);
		kमुक्त(fs_info);
		वापस शून्य;
	पूर्ण

	btrfs_init_fs_info(fs_info);

	fs_info->nodesize = nodesize;
	fs_info->sectorsize = sectorsize;
	fs_info->sectorsize_bits = ilog2(sectorsize);
	set_bit(BTRFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state);

	test_mnt->mnt_sb->s_fs_info = fs_info;

	वापस fs_info;
पूर्ण

व्योम btrfs_मुक्त_dummy_fs_info(काष्ठा btrfs_fs_info *fs_info)
अणु
	काष्ठा radix_tree_iter iter;
	व्योम **slot;
	काष्ठा btrfs_device *dev, *पंचांगp;

	अगर (!fs_info)
		वापस;

	अगर (WARN_ON(!test_bit(BTRFS_FS_STATE_DUMMY_FS_INFO,
			      &fs_info->fs_state)))
		वापस;

	test_mnt->mnt_sb->s_fs_info = शून्य;

	spin_lock(&fs_info->buffer_lock);
	radix_tree_क्रम_each_slot(slot, &fs_info->buffer_radix, &iter, 0) अणु
		काष्ठा extent_buffer *eb;

		eb = radix_tree_deref_slot_रक्षित(slot, &fs_info->buffer_lock);
		अगर (!eb)
			जारी;
		/* Shouldn't happen but that kind of thinking creates CVE's */
		अगर (radix_tree_exception(eb)) अणु
			अगर (radix_tree_deref_retry(eb))
				slot = radix_tree_iter_retry(&iter);
			जारी;
		पूर्ण
		slot = radix_tree_iter_resume(slot, &iter);
		spin_unlock(&fs_info->buffer_lock);
		मुक्त_extent_buffer_stale(eb);
		spin_lock(&fs_info->buffer_lock);
	पूर्ण
	spin_unlock(&fs_info->buffer_lock);

	btrfs_mapping_tree_मुक्त(&fs_info->mapping_tree);
	list_क्रम_each_entry_safe(dev, पंचांगp, &fs_info->fs_devices->devices,
				 dev_list) अणु
		btrfs_मुक्त_dummy_device(dev);
	पूर्ण
	btrfs_मुक्त_qgroup_config(fs_info);
	btrfs_मुक्त_fs_roots(fs_info);
	kमुक्त(fs_info->super_copy);
	btrfs_check_leaked_roots(fs_info);
	btrfs_extent_buffer_leak_debug_check(fs_info);
	kमुक्त(fs_info->fs_devices);
	kमुक्त(fs_info);
पूर्ण

व्योम btrfs_मुक्त_dummy_root(काष्ठा btrfs_root *root)
अणु
	अगर (!root)
		वापस;
	/* Will be मुक्तd by btrfs_मुक्त_fs_roots */
	अगर (WARN_ON(test_bit(BTRFS_ROOT_IN_RADIX, &root->state)))
		वापस;
	btrfs_put_root(root);
पूर्ण

काष्ठा btrfs_block_group *
btrfs_alloc_dummy_block_group(काष्ठा btrfs_fs_info *fs_info,
			      अचिन्हित दीर्घ length)
अणु
	काष्ठा btrfs_block_group *cache;

	cache = kzalloc(माप(*cache), GFP_KERNEL);
	अगर (!cache)
		वापस शून्य;
	cache->मुक्त_space_ctl = kzalloc(माप(*cache->मुक्त_space_ctl),
					GFP_KERNEL);
	अगर (!cache->मुक्त_space_ctl) अणु
		kमुक्त(cache);
		वापस शून्य;
	पूर्ण

	cache->start = 0;
	cache->length = length;
	cache->full_stripe_len = fs_info->sectorsize;
	cache->fs_info = fs_info;

	INIT_LIST_HEAD(&cache->list);
	INIT_LIST_HEAD(&cache->cluster_list);
	INIT_LIST_HEAD(&cache->bg_list);
	btrfs_init_मुक्त_space_ctl(cache, cache->मुक्त_space_ctl);
	mutex_init(&cache->मुक्त_space_lock);

	वापस cache;
पूर्ण

व्योम btrfs_मुक्त_dummy_block_group(काष्ठा btrfs_block_group *cache)
अणु
	अगर (!cache)
		वापस;
	__btrfs_हटाओ_मुक्त_space_cache(cache->मुक्त_space_ctl);
	kमुक्त(cache->मुक्त_space_ctl);
	kमुक्त(cache);
पूर्ण

व्योम btrfs_init_dummy_trans(काष्ठा btrfs_trans_handle *trans,
			    काष्ठा btrfs_fs_info *fs_info)
अणु
	स_रखो(trans, 0, माप(*trans));
	trans->transid = 1;
	trans->type = __TRANS_DUMMY;
	trans->fs_info = fs_info;
पूर्ण

पूर्णांक btrfs_run_sanity_tests(व्योम)
अणु
	पूर्णांक ret, i;
	u32 sectorsize, nodesize;
	u32 test_sectorsize[] = अणु
		PAGE_SIZE,
	पूर्ण;
	ret = btrfs_init_test_fs();
	अगर (ret)
		वापस ret;
	क्रम (i = 0; i < ARRAY_SIZE(test_sectorsize); i++) अणु
		sectorsize = test_sectorsize[i];
		क्रम (nodesize = sectorsize;
		     nodesize <= BTRFS_MAX_METADATA_BLOCKSIZE;
		     nodesize <<= 1) अणु
			pr_info("BTRFS: selftest: sectorsize: %u  nodesize: %u\n",
				sectorsize, nodesize);
			ret = btrfs_test_मुक्त_space_cache(sectorsize, nodesize);
			अगर (ret)
				जाओ out;
			ret = btrfs_test_extent_buffer_operations(sectorsize,
				nodesize);
			अगर (ret)
				जाओ out;
			ret = btrfs_test_extent_io(sectorsize, nodesize);
			अगर (ret)
				जाओ out;
			ret = btrfs_test_inodes(sectorsize, nodesize);
			अगर (ret)
				जाओ out;
			ret = btrfs_test_qgroups(sectorsize, nodesize);
			अगर (ret)
				जाओ out;
			ret = btrfs_test_मुक्त_space_tree(sectorsize, nodesize);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण
	ret = btrfs_test_extent_map();

out:
	btrfs_destroy_test_fs();
	वापस ret;
पूर्ण
