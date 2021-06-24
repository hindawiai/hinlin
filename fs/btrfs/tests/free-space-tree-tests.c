<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Facebook.  All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश "btrfs-tests.h"
#समावेश "../ctree.h"
#समावेश "../disk-io.h"
#समावेश "../free-space-tree.h"
#समावेश "../transaction.h"
#समावेश "../block-group.h"

काष्ठा मुक्त_space_extent अणु
	u64 start;
	u64 length;
पूर्ण;

अटल पूर्णांक __check_मुक्त_space_extents(काष्ठा btrfs_trans_handle *trans,
				      काष्ठा btrfs_fs_info *fs_info,
				      काष्ठा btrfs_block_group *cache,
				      काष्ठा btrfs_path *path,
				      स्थिर काष्ठा मुक्त_space_extent * स्थिर extents,
				      अचिन्हित पूर्णांक num_extents)
अणु
	काष्ठा btrfs_मुक्त_space_info *info;
	काष्ठा btrfs_key key;
	पूर्णांक prev_bit = 0, bit;
	u64 extent_start = 0, offset, end;
	u32 flags, extent_count;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	info = search_मुक्त_space_info(trans, cache, path, 0);
	अगर (IS_ERR(info)) अणु
		test_err("could not find free space info");
		ret = PTR_ERR(info);
		जाओ out;
	पूर्ण
	flags = btrfs_मुक्त_space_flags(path->nodes[0], info);
	extent_count = btrfs_मुक्त_space_extent_count(path->nodes[0], info);

	अगर (extent_count != num_extents) अणु
		test_err("extent count is wrong");
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (flags & BTRFS_FREE_SPACE_USING_BITMAPS) अणु
		अगर (path->slots[0] != 0)
			जाओ invalid;
		end = cache->start + cache->length;
		i = 0;
		जबतक (++path->slots[0] < btrfs_header_nritems(path->nodes[0])) अणु
			btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
			अगर (key.type != BTRFS_FREE_SPACE_BITMAP_KEY)
				जाओ invalid;
			offset = key.objectid;
			जबतक (offset < key.objectid + key.offset) अणु
				bit = मुक्त_space_test_bit(cache, path, offset);
				अगर (prev_bit == 0 && bit == 1) अणु
					extent_start = offset;
				पूर्ण अन्यथा अगर (prev_bit == 1 && bit == 0) अणु
					अगर (i >= num_extents ||
					    extent_start != extents[i].start ||
					    offset - extent_start != extents[i].length)
						जाओ invalid;
					i++;
				पूर्ण
				prev_bit = bit;
				offset += fs_info->sectorsize;
			पूर्ण
		पूर्ण
		अगर (prev_bit == 1) अणु
			अगर (i >= num_extents ||
			    extent_start != extents[i].start ||
			    end - extent_start != extents[i].length)
				जाओ invalid;
			i++;
		पूर्ण
		अगर (i != num_extents)
			जाओ invalid;
	पूर्ण अन्यथा अणु
		अगर (btrfs_header_nritems(path->nodes[0]) != num_extents + 1 ||
		    path->slots[0] != 0)
			जाओ invalid;
		क्रम (i = 0; i < num_extents; i++) अणु
			path->slots[0]++;
			btrfs_item_key_to_cpu(path->nodes[0], &key, path->slots[0]);
			अगर (key.type != BTRFS_FREE_SPACE_EXTENT_KEY ||
			    key.objectid != extents[i].start ||
			    key.offset != extents[i].length)
				जाओ invalid;
		पूर्ण
	पूर्ण

	ret = 0;
out:
	btrfs_release_path(path);
	वापस ret;
invalid:
	test_err("free space tree is invalid");
	ret = -EINVAL;
	जाओ out;
पूर्ण

अटल पूर्णांक check_मुक्त_space_extents(काष्ठा btrfs_trans_handle *trans,
				    काष्ठा btrfs_fs_info *fs_info,
				    काष्ठा btrfs_block_group *cache,
				    काष्ठा btrfs_path *path,
				    स्थिर काष्ठा मुक्त_space_extent * स्थिर extents,
				    अचिन्हित पूर्णांक num_extents)
अणु
	काष्ठा btrfs_मुक्त_space_info *info;
	u32 flags;
	पूर्णांक ret;

	info = search_मुक्त_space_info(trans, cache, path, 0);
	अगर (IS_ERR(info)) अणु
		test_err("could not find free space info");
		btrfs_release_path(path);
		वापस PTR_ERR(info);
	पूर्ण
	flags = btrfs_मुक्त_space_flags(path->nodes[0], info);
	btrfs_release_path(path);

	ret = __check_मुक्त_space_extents(trans, fs_info, cache, path, extents,
					 num_extents);
	अगर (ret)
		वापस ret;

	/* Flip it to the other क्रमmat and check that क्रम good measure. */
	अगर (flags & BTRFS_FREE_SPACE_USING_BITMAPS) अणु
		ret = convert_मुक्त_space_to_extents(trans, cache, path);
		अगर (ret) अणु
			test_err("could not convert to extents");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = convert_मुक्त_space_to_biपंचांगaps(trans, cache, path);
		अगर (ret) अणु
			test_err("could not convert to bitmaps");
			वापस ret;
		पूर्ण
	पूर्ण
	वापस __check_मुक्त_space_extents(trans, fs_info, cache, path, extents,
					  num_extents);
पूर्ण

अटल पूर्णांक test_empty_block_group(काष्ठा btrfs_trans_handle *trans,
				  काष्ठा btrfs_fs_info *fs_info,
				  काष्ठा btrfs_block_group *cache,
				  काष्ठा btrfs_path *path,
				  u32 alignment)
अणु
	स्थिर काष्ठा मुक्त_space_extent extents[] = अणु
		अणुcache->start, cache->lengthपूर्ण,
	पूर्ण;

	वापस check_मुक्त_space_extents(trans, fs_info, cache, path,
					extents, ARRAY_SIZE(extents));
पूर्ण

अटल पूर्णांक test_हटाओ_all(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_block_group *cache,
			   काष्ठा btrfs_path *path,
			   u32 alignment)
अणु
	स्थिर काष्ठा मुक्त_space_extent extents[] = अणुपूर्ण;
	पूर्णांक ret;

	ret = __हटाओ_from_मुक्त_space_tree(trans, cache, path,
					    cache->start,
					    cache->length);
	अगर (ret) अणु
		test_err("could not remove free space");
		वापस ret;
	पूर्ण

	वापस check_मुक्त_space_extents(trans, fs_info, cache, path,
					extents, ARRAY_SIZE(extents));
पूर्ण

अटल पूर्णांक test_हटाओ_beginning(काष्ठा btrfs_trans_handle *trans,
				 काष्ठा btrfs_fs_info *fs_info,
				 काष्ठा btrfs_block_group *cache,
				 काष्ठा btrfs_path *path,
				 u32 alignment)
अणु
	स्थिर काष्ठा मुक्त_space_extent extents[] = अणु
		अणुcache->start + alignment, cache->length - alignmentपूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = __हटाओ_from_मुक्त_space_tree(trans, cache, path,
					    cache->start, alignment);
	अगर (ret) अणु
		test_err("could not remove free space");
		वापस ret;
	पूर्ण

	वापस check_मुक्त_space_extents(trans, fs_info, cache, path,
					extents, ARRAY_SIZE(extents));

पूर्ण

अटल पूर्णांक test_हटाओ_end(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_block_group *cache,
			   काष्ठा btrfs_path *path,
			   u32 alignment)
अणु
	स्थिर काष्ठा मुक्त_space_extent extents[] = अणु
		अणुcache->start, cache->length - alignmentपूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = __हटाओ_from_मुक्त_space_tree(trans, cache, path,
				    cache->start + cache->length - alignment,
				    alignment);
	अगर (ret) अणु
		test_err("could not remove free space");
		वापस ret;
	पूर्ण

	वापस check_मुक्त_space_extents(trans, fs_info, cache, path,
					extents, ARRAY_SIZE(extents));
पूर्ण

अटल पूर्णांक test_हटाओ_middle(काष्ठा btrfs_trans_handle *trans,
			      काष्ठा btrfs_fs_info *fs_info,
			      काष्ठा btrfs_block_group *cache,
			      काष्ठा btrfs_path *path,
			      u32 alignment)
अणु
	स्थिर काष्ठा मुक्त_space_extent extents[] = अणु
		अणुcache->start, alignmentपूर्ण,
		अणुcache->start + 2 * alignment, cache->length - 2 * alignmentपूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = __हटाओ_from_मुक्त_space_tree(trans, cache, path,
					    cache->start + alignment,
					    alignment);
	अगर (ret) अणु
		test_err("could not remove free space");
		वापस ret;
	पूर्ण

	वापस check_मुक्त_space_extents(trans, fs_info, cache, path,
					extents, ARRAY_SIZE(extents));
पूर्ण

अटल पूर्णांक test_merge_left(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_block_group *cache,
			   काष्ठा btrfs_path *path,
			   u32 alignment)
अणु
	स्थिर काष्ठा मुक्त_space_extent extents[] = अणु
		अणुcache->start, 2 * alignmentपूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = __हटाओ_from_मुक्त_space_tree(trans, cache, path,
					    cache->start, cache->length);
	अगर (ret) अणु
		test_err("could not remove free space");
		वापस ret;
	पूर्ण

	ret = __add_to_मुक्त_space_tree(trans, cache, path, cache->start,
				       alignment);
	अगर (ret) अणु
		test_err("could not add free space");
		वापस ret;
	पूर्ण

	ret = __add_to_मुक्त_space_tree(trans, cache, path,
				       cache->start + alignment,
				       alignment);
	अगर (ret) अणु
		test_err("could not add free space");
		वापस ret;
	पूर्ण

	वापस check_मुक्त_space_extents(trans, fs_info, cache, path,
					extents, ARRAY_SIZE(extents));
पूर्ण

अटल पूर्णांक test_merge_right(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_block_group *cache,
			   काष्ठा btrfs_path *path,
			   u32 alignment)
अणु
	स्थिर काष्ठा मुक्त_space_extent extents[] = अणु
		अणुcache->start + alignment, 2 * alignmentपूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = __हटाओ_from_मुक्त_space_tree(trans, cache, path,
					    cache->start, cache->length);
	अगर (ret) अणु
		test_err("could not remove free space");
		वापस ret;
	पूर्ण

	ret = __add_to_मुक्त_space_tree(trans, cache, path,
				       cache->start + 2 * alignment,
				       alignment);
	अगर (ret) अणु
		test_err("could not add free space");
		वापस ret;
	पूर्ण

	ret = __add_to_मुक्त_space_tree(trans, cache, path,
				       cache->start + alignment,
				       alignment);
	अगर (ret) अणु
		test_err("could not add free space");
		वापस ret;
	पूर्ण

	वापस check_मुक्त_space_extents(trans, fs_info, cache, path,
					extents, ARRAY_SIZE(extents));
पूर्ण

अटल पूर्णांक test_merge_both(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_block_group *cache,
			   काष्ठा btrfs_path *path,
			   u32 alignment)
अणु
	स्थिर काष्ठा मुक्त_space_extent extents[] = अणु
		अणुcache->start, 3 * alignmentपूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = __हटाओ_from_मुक्त_space_tree(trans, cache, path,
					    cache->start, cache->length);
	अगर (ret) अणु
		test_err("could not remove free space");
		वापस ret;
	पूर्ण

	ret = __add_to_मुक्त_space_tree(trans, cache, path, cache->start,
				       alignment);
	अगर (ret) अणु
		test_err("could not add free space");
		वापस ret;
	पूर्ण

	ret = __add_to_मुक्त_space_tree(trans, cache, path,
				       cache->start + 2 * alignment, alignment);
	अगर (ret) अणु
		test_err("could not add free space");
		वापस ret;
	पूर्ण

	ret = __add_to_मुक्त_space_tree(trans, cache, path,
				       cache->start + alignment, alignment);
	अगर (ret) अणु
		test_err("could not add free space");
		वापस ret;
	पूर्ण

	वापस check_मुक्त_space_extents(trans, fs_info, cache, path,
					extents, ARRAY_SIZE(extents));
पूर्ण

अटल पूर्णांक test_merge_none(काष्ठा btrfs_trans_handle *trans,
			   काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा btrfs_block_group *cache,
			   काष्ठा btrfs_path *path,
			   u32 alignment)
अणु
	स्थिर काष्ठा मुक्त_space_extent extents[] = अणु
		अणुcache->start, alignmentपूर्ण,
		अणुcache->start + 2 * alignment, alignmentपूर्ण,
		अणुcache->start + 4 * alignment, alignmentपूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = __हटाओ_from_मुक्त_space_tree(trans, cache, path,
					    cache->start, cache->length);
	अगर (ret) अणु
		test_err("could not remove free space");
		वापस ret;
	पूर्ण

	ret = __add_to_मुक्त_space_tree(trans, cache, path, cache->start,
				       alignment);
	अगर (ret) अणु
		test_err("could not add free space");
		वापस ret;
	पूर्ण

	ret = __add_to_मुक्त_space_tree(trans, cache, path,
				       cache->start + 4 * alignment, alignment);
	अगर (ret) अणु
		test_err("could not add free space");
		वापस ret;
	पूर्ण

	ret = __add_to_मुक्त_space_tree(trans, cache, path,
				       cache->start + 2 * alignment, alignment);
	अगर (ret) अणु
		test_err("could not add free space");
		वापस ret;
	पूर्ण

	वापस check_मुक्त_space_extents(trans, fs_info, cache, path,
					extents, ARRAY_SIZE(extents));
पूर्ण

प्रकार पूर्णांक (*test_func_t)(काष्ठा btrfs_trans_handle *,
			   काष्ठा btrfs_fs_info *,
			   काष्ठा btrfs_block_group *,
			   काष्ठा btrfs_path *,
			   u32 alignment);

अटल पूर्णांक run_test(test_func_t test_func, पूर्णांक biपंचांगaps, u32 sectorsize,
		    u32 nodesize, u32 alignment)
अणु
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_root *root = शून्य;
	काष्ठा btrfs_block_group *cache = शून्य;
	काष्ठा btrfs_trans_handle trans;
	काष्ठा btrfs_path *path = शून्य;
	पूर्णांक ret;

	fs_info = btrfs_alloc_dummy_fs_info(nodesize, sectorsize);
	अगर (!fs_info) अणु
		test_std_err(TEST_ALLOC_FS_INFO);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	root = btrfs_alloc_dummy_root(fs_info);
	अगर (IS_ERR(root)) अणु
		test_std_err(TEST_ALLOC_ROOT);
		ret = PTR_ERR(root);
		जाओ out;
	पूर्ण

	btrfs_set_super_compat_ro_flags(root->fs_info->super_copy,
					BTRFS_FEATURE_COMPAT_RO_FREE_SPACE_TREE);
	root->fs_info->मुक्त_space_root = root;
	root->fs_info->tree_root = root;

	root->node = alloc_test_extent_buffer(root->fs_info, nodesize);
	अगर (IS_ERR(root->node)) अणु
		test_std_err(TEST_ALLOC_EXTENT_BUFFER);
		ret = PTR_ERR(root->node);
		जाओ out;
	पूर्ण
	btrfs_set_header_level(root->node, 0);
	btrfs_set_header_nritems(root->node, 0);
	root->alloc_bytenr += 2 * nodesize;

	cache = btrfs_alloc_dummy_block_group(fs_info, 8 * alignment);
	अगर (!cache) अणु
		test_std_err(TEST_ALLOC_BLOCK_GROUP);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	cache->biपंचांगap_low_thresh = 0;
	cache->biपंचांगap_high_thresh = (u32)-1;
	cache->needs_मुक्त_space = 1;
	cache->fs_info = root->fs_info;

	btrfs_init_dummy_trans(&trans, root->fs_info);

	path = btrfs_alloc_path();
	अगर (!path) अणु
		test_std_err(TEST_ALLOC_ROOT);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = add_block_group_मुक्त_space(&trans, cache);
	अगर (ret) अणु
		test_err("could not add block group free space");
		जाओ out;
	पूर्ण

	अगर (biपंचांगaps) अणु
		ret = convert_मुक्त_space_to_biपंचांगaps(&trans, cache, path);
		अगर (ret) अणु
			test_err("could not convert block group to bitmaps");
			जाओ out;
		पूर्ण
	पूर्ण

	ret = test_func(&trans, root->fs_info, cache, path, alignment);
	अगर (ret)
		जाओ out;

	ret = हटाओ_block_group_मुक्त_space(&trans, cache);
	अगर (ret) अणु
		test_err("could not remove block group free space");
		जाओ out;
	पूर्ण

	अगर (btrfs_header_nritems(root->node) != 0) अणु
		test_err("free space tree has leftover items");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = 0;
out:
	btrfs_मुक्त_path(path);
	btrfs_मुक्त_dummy_block_group(cache);
	btrfs_मुक्त_dummy_root(root);
	btrfs_मुक्त_dummy_fs_info(fs_info);
	वापस ret;
पूर्ण

अटल पूर्णांक run_test_both_क्रमmats(test_func_t test_func, u32 sectorsize,
				 u32 nodesize, u32 alignment)
अणु
	पूर्णांक test_ret = 0;
	पूर्णांक ret;

	ret = run_test(test_func, 0, sectorsize, nodesize, alignment);
	अगर (ret) अणु
		test_err(
	"%ps failed with extents, sectorsize=%u, nodesize=%u, alignment=%u",
			 test_func, sectorsize, nodesize, alignment);
		test_ret = ret;
	पूर्ण

	ret = run_test(test_func, 1, sectorsize, nodesize, alignment);
	अगर (ret) अणु
		test_err(
	"%ps failed with bitmaps, sectorsize=%u, nodesize=%u, alignment=%u",
			 test_func, sectorsize, nodesize, alignment);
		test_ret = ret;
	पूर्ण

	वापस test_ret;
पूर्ण

पूर्णांक btrfs_test_मुक्त_space_tree(u32 sectorsize, u32 nodesize)
अणु
	test_func_t tests[] = अणु
		test_empty_block_group,
		test_हटाओ_all,
		test_हटाओ_beginning,
		test_हटाओ_end,
		test_हटाओ_middle,
		test_merge_left,
		test_merge_right,
		test_merge_both,
		test_merge_none,
	पूर्ण;
	u32 biपंचांगap_alignment;
	पूर्णांक test_ret = 0;
	पूर्णांक i;

	/*
	 * Align some operations to a page to flush out bugs in the extent
	 * buffer biपंचांगap handling of highmem.
	 */
	biपंचांगap_alignment = BTRFS_FREE_SPACE_BITMAP_BITS * PAGE_SIZE;

	test_msg("running free space tree tests");
	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		पूर्णांक ret;

		ret = run_test_both_क्रमmats(tests[i], sectorsize, nodesize,
					    sectorsize);
		अगर (ret)
			test_ret = ret;

		ret = run_test_both_क्रमmats(tests[i], sectorsize, nodesize,
					    biपंचांगap_alignment);
		अगर (ret)
			test_ret = ret;
	पूर्ण

	वापस test_ret;
पूर्ण
