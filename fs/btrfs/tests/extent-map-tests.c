<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Oracle.  All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश "btrfs-tests.h"
#समावेश "../ctree.h"
#समावेश "../volumes.h"
#समावेश "../disk-io.h"
#समावेश "../block-group.h"

अटल व्योम मुक्त_extent_map_tree(काष्ठा extent_map_tree *em_tree)
अणु
	काष्ठा extent_map *em;
	काष्ठा rb_node *node;

	जबतक (!RB_EMPTY_ROOT(&em_tree->map.rb_root)) अणु
		node = rb_first_cached(&em_tree->map);
		em = rb_entry(node, काष्ठा extent_map, rb_node);
		हटाओ_extent_mapping(em_tree, em);

#अगर_घोषित CONFIG_BTRFS_DEBUG
		अगर (refcount_पढ़ो(&em->refs) != 1) अणु
			test_err(
"em leak: em (start 0x%llx len 0x%llx block_start 0x%llx block_len 0x%llx) refs %d",
				 em->start, em->len, em->block_start,
				 em->block_len, refcount_पढ़ो(&em->refs));

			refcount_set(&em->refs, 1);
		पूर्ण
#पूर्ण_अगर
		मुक्त_extent_map(em);
	पूर्ण
पूर्ण

/*
 * Test scenario:
 *
 * Suppose that no extent map has been loaded पूर्णांकo memory yet, there is a file
 * extent [0, 16K), followed by another file extent [16K, 20K), two dio पढ़ोs
 * are entering btrfs_get_extent() concurrently, t1 is पढ़ोing [8K, 16K), t2 is
 * पढ़ोing [0, 8K)
 *
 *     t1                            t2
 *  btrfs_get_extent()              btrfs_get_extent()
 *    -> lookup_extent_mapping()      ->lookup_extent_mapping()
 *    -> add_extent_mapping(0, 16K)
 *    -> वापस em
 *                                    ->add_extent_mapping(0, 16K)
 *                                    -> #handle -EEXIST
 */
अटल पूर्णांक test_हाल_1(काष्ठा btrfs_fs_info *fs_info,
		काष्ठा extent_map_tree *em_tree)
अणु
	काष्ठा extent_map *em;
	u64 start = 0;
	u64 len = SZ_8K;
	पूर्णांक ret;

	em = alloc_extent_map();
	अगर (!em) अणु
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		वापस -ENOMEM;
	पूर्ण

	/* Add [0, 16K) */
	em->start = 0;
	em->len = SZ_16K;
	em->block_start = 0;
	em->block_len = SZ_16K;
	ग_लिखो_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em, 0);
	ग_लिखो_unlock(&em_tree->lock);
	अगर (ret < 0) अणु
		test_err("cannot add extent range [0, 16K)");
		जाओ out;
	पूर्ण
	मुक्त_extent_map(em);

	/* Add [16K, 20K) following [0, 16K)  */
	em = alloc_extent_map();
	अगर (!em) अणु
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	em->start = SZ_16K;
	em->len = SZ_4K;
	em->block_start = SZ_32K; /* aव्योम merging */
	em->block_len = SZ_4K;
	ग_लिखो_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em, 0);
	ग_लिखो_unlock(&em_tree->lock);
	अगर (ret < 0) अणु
		test_err("cannot add extent range [16K, 20K)");
		जाओ out;
	पूर्ण
	मुक्त_extent_map(em);

	em = alloc_extent_map();
	अगर (!em) अणु
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Add [0, 8K), should वापस [0, 16K) instead. */
	em->start = start;
	em->len = len;
	em->block_start = start;
	em->block_len = len;
	ग_लिखो_lock(&em_tree->lock);
	ret = btrfs_add_extent_mapping(fs_info, em_tree, &em, em->start, em->len);
	ग_लिखो_unlock(&em_tree->lock);
	अगर (ret) अणु
		test_err("case1 [%llu %llu]: ret %d", start, start + len, ret);
		जाओ out;
	पूर्ण
	अगर (em &&
	    (em->start != 0 || extent_map_end(em) != SZ_16K ||
	     em->block_start != 0 || em->block_len != SZ_16K)) अणु
		test_err(
"case1 [%llu %llu]: ret %d return a wrong em (start %llu len %llu block_start %llu block_len %llu",
			 start, start + len, ret, em->start, em->len,
			 em->block_start, em->block_len);
		ret = -EINVAL;
	पूर्ण
	मुक्त_extent_map(em);
out:
	मुक्त_extent_map_tree(em_tree);

	वापस ret;
पूर्ण

/*
 * Test scenario:
 *
 * Reading the अंतरभूत ending up with EEXIST, ie. पढ़ो an अंतरभूत
 * extent and discard page cache and पढ़ो it again.
 */
अटल पूर्णांक test_हाल_2(काष्ठा btrfs_fs_info *fs_info,
		काष्ठा extent_map_tree *em_tree)
अणु
	काष्ठा extent_map *em;
	पूर्णांक ret;

	em = alloc_extent_map();
	अगर (!em) अणु
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		वापस -ENOMEM;
	पूर्ण

	/* Add [0, 1K) */
	em->start = 0;
	em->len = SZ_1K;
	em->block_start = EXTENT_MAP_INLINE;
	em->block_len = (u64)-1;
	ग_लिखो_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em, 0);
	ग_लिखो_unlock(&em_tree->lock);
	अगर (ret < 0) अणु
		test_err("cannot add extent range [0, 1K)");
		जाओ out;
	पूर्ण
	मुक्त_extent_map(em);

	/* Add [4K, 8K) following [0, 1K)  */
	em = alloc_extent_map();
	अगर (!em) अणु
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	em->start = SZ_4K;
	em->len = SZ_4K;
	em->block_start = SZ_4K;
	em->block_len = SZ_4K;
	ग_लिखो_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em, 0);
	ग_लिखो_unlock(&em_tree->lock);
	अगर (ret < 0) अणु
		test_err("cannot add extent range [4K, 8K)");
		जाओ out;
	पूर्ण
	मुक्त_extent_map(em);

	em = alloc_extent_map();
	अगर (!em) अणु
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Add [0, 1K) */
	em->start = 0;
	em->len = SZ_1K;
	em->block_start = EXTENT_MAP_INLINE;
	em->block_len = (u64)-1;
	ग_लिखो_lock(&em_tree->lock);
	ret = btrfs_add_extent_mapping(fs_info, em_tree, &em, em->start, em->len);
	ग_लिखो_unlock(&em_tree->lock);
	अगर (ret) अणु
		test_err("case2 [0 1K]: ret %d", ret);
		जाओ out;
	पूर्ण
	अगर (em &&
	    (em->start != 0 || extent_map_end(em) != SZ_1K ||
	     em->block_start != EXTENT_MAP_INLINE || em->block_len != (u64)-1)) अणु
		test_err(
"case2 [0 1K]: ret %d return a wrong em (start %llu len %llu block_start %llu block_len %llu",
			 ret, em->start, em->len, em->block_start,
			 em->block_len);
		ret = -EINVAL;
	पूर्ण
	मुक्त_extent_map(em);
out:
	मुक्त_extent_map_tree(em_tree);

	वापस ret;
पूर्ण

अटल पूर्णांक __test_हाल_3(काष्ठा btrfs_fs_info *fs_info,
		काष्ठा extent_map_tree *em_tree, u64 start)
अणु
	काष्ठा extent_map *em;
	u64 len = SZ_4K;
	पूर्णांक ret;

	em = alloc_extent_map();
	अगर (!em) अणु
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		वापस -ENOMEM;
	पूर्ण

	/* Add [4K, 8K) */
	em->start = SZ_4K;
	em->len = SZ_4K;
	em->block_start = SZ_4K;
	em->block_len = SZ_4K;
	ग_लिखो_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em, 0);
	ग_लिखो_unlock(&em_tree->lock);
	अगर (ret < 0) अणु
		test_err("cannot add extent range [4K, 8K)");
		जाओ out;
	पूर्ण
	मुक्त_extent_map(em);

	em = alloc_extent_map();
	अगर (!em) अणु
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Add [0, 16K) */
	em->start = 0;
	em->len = SZ_16K;
	em->block_start = 0;
	em->block_len = SZ_16K;
	ग_लिखो_lock(&em_tree->lock);
	ret = btrfs_add_extent_mapping(fs_info, em_tree, &em, start, len);
	ग_लिखो_unlock(&em_tree->lock);
	अगर (ret) अणु
		test_err("case3 [0x%llx 0x%llx): ret %d",
			 start, start + len, ret);
		जाओ out;
	पूर्ण
	/*
	 * Since bytes within em are contiguous, em->block_start is identical to
	 * em->start.
	 */
	अगर (em &&
	    (start < em->start || start + len > extent_map_end(em) ||
	     em->start != em->block_start || em->len != em->block_len)) अणु
		test_err(
"case3 [0x%llx 0x%llx): ret %d em (start 0x%llx len 0x%llx block_start 0x%llx block_len 0x%llx)",
			 start, start + len, ret, em->start, em->len,
			 em->block_start, em->block_len);
		ret = -EINVAL;
	पूर्ण
	मुक्त_extent_map(em);
out:
	मुक्त_extent_map_tree(em_tree);

	वापस ret;
पूर्ण

/*
 * Test scenario:
 *
 * Suppose that no extent map has been loaded पूर्णांकo memory yet.
 * There is a file extent [0, 16K), two jobs are running concurrently
 * against it, t1 is buffered writing to [4K, 8K) and t2 is करोing dio
 * पढ़ो from [0, 4K) or [8K, 12K) or [12K, 16K).
 *
 * t1 goes ahead of t2 and adds em [4K, 8K) पूर्णांकo tree.
 *
 *         t1                       t2
 *  cow_file_range()	     btrfs_get_extent()
 *                            -> lookup_extent_mapping()
 *   -> add_extent_mapping()
 *                            -> add_extent_mapping()
 */
अटल पूर्णांक test_हाल_3(काष्ठा btrfs_fs_info *fs_info,
		काष्ठा extent_map_tree *em_tree)
अणु
	पूर्णांक ret;

	ret = __test_हाल_3(fs_info, em_tree, 0);
	अगर (ret)
		वापस ret;
	ret = __test_हाल_3(fs_info, em_tree, SZ_8K);
	अगर (ret)
		वापस ret;
	ret = __test_हाल_3(fs_info, em_tree, (12 * SZ_1K));

	वापस ret;
पूर्ण

अटल पूर्णांक __test_हाल_4(काष्ठा btrfs_fs_info *fs_info,
		काष्ठा extent_map_tree *em_tree, u64 start)
अणु
	काष्ठा extent_map *em;
	u64 len = SZ_4K;
	पूर्णांक ret;

	em = alloc_extent_map();
	अगर (!em) अणु
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		वापस -ENOMEM;
	पूर्ण

	/* Add [0K, 8K) */
	em->start = 0;
	em->len = SZ_8K;
	em->block_start = 0;
	em->block_len = SZ_8K;
	ग_लिखो_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em, 0);
	ग_लिखो_unlock(&em_tree->lock);
	अगर (ret < 0) अणु
		test_err("cannot add extent range [0, 8K)");
		जाओ out;
	पूर्ण
	मुक्त_extent_map(em);

	em = alloc_extent_map();
	अगर (!em) अणु
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Add [8K, 32K) */
	em->start = SZ_8K;
	em->len = 24 * SZ_1K;
	em->block_start = SZ_16K; /* aव्योम merging */
	em->block_len = 24 * SZ_1K;
	ग_लिखो_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em, 0);
	ग_लिखो_unlock(&em_tree->lock);
	अगर (ret < 0) अणु
		test_err("cannot add extent range [8K, 32K)");
		जाओ out;
	पूर्ण
	मुक्त_extent_map(em);

	em = alloc_extent_map();
	अगर (!em) अणु
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	/* Add [0K, 32K) */
	em->start = 0;
	em->len = SZ_32K;
	em->block_start = 0;
	em->block_len = SZ_32K;
	ग_लिखो_lock(&em_tree->lock);
	ret = btrfs_add_extent_mapping(fs_info, em_tree, &em, start, len);
	ग_लिखो_unlock(&em_tree->lock);
	अगर (ret) अणु
		test_err("case4 [0x%llx 0x%llx): ret %d",
			 start, len, ret);
		जाओ out;
	पूर्ण
	अगर (em && (start < em->start || start + len > extent_map_end(em))) अणु
		test_err(
"case4 [0x%llx 0x%llx): ret %d, added wrong em (start 0x%llx len 0x%llx block_start 0x%llx block_len 0x%llx)",
			 start, len, ret, em->start, em->len, em->block_start,
			 em->block_len);
		ret = -EINVAL;
	पूर्ण
	मुक्त_extent_map(em);
out:
	मुक्त_extent_map_tree(em_tree);

	वापस ret;
पूर्ण

/*
 * Test scenario:
 *
 * Suppose that no extent map has been loaded पूर्णांकo memory yet.
 * There is a file extent [0, 32K), two jobs are running concurrently
 * against it, t1 is करोing dio ग_लिखो to [8K, 32K) and t2 is करोing dio
 * पढ़ो from [0, 4K) or [4K, 8K).
 *
 * t1 goes ahead of t2 and splits em [0, 32K) to em [0K, 8K) and [8K 32K).
 *
 *         t1                                t2
 *  btrfs_get_blocks_direct()	       btrfs_get_blocks_direct()
 *   -> btrfs_get_extent()              -> btrfs_get_extent()
 *       -> lookup_extent_mapping()
 *       -> add_extent_mapping()            -> lookup_extent_mapping()
 *          # load [0, 32K)
 *   -> btrfs_new_extent_direct()
 *       -> btrfs_drop_extent_cache()
 *          # split [0, 32K)
 *       -> add_extent_mapping()
 *          # add [8K, 32K)
 *                                          -> add_extent_mapping()
 *                                             # handle -EEXIST when adding
 *                                             # [0, 32K)
 */
अटल पूर्णांक test_हाल_4(काष्ठा btrfs_fs_info *fs_info,
		काष्ठा extent_map_tree *em_tree)
अणु
	पूर्णांक ret;

	ret = __test_हाल_4(fs_info, em_tree, 0);
	अगर (ret)
		वापस ret;
	ret = __test_हाल_4(fs_info, em_tree, SZ_4K);

	वापस ret;
पूर्ण

काष्ठा rmap_test_vector अणु
	u64 raid_type;
	u64 physical_start;
	u64 data_stripe_size;
	u64 num_data_stripes;
	u64 num_stripes;
	/* Assume we won't have more than 5 physical stripes */
	u64 data_stripe_phys_start[5];
	bool expected_mapped_addr;
	/* Physical to logical addresses */
	u64 mapped_logical[5];
पूर्ण;

अटल पूर्णांक test_rmap_block(काष्ठा btrfs_fs_info *fs_info,
			   काष्ठा rmap_test_vector *test)
अणु
	काष्ठा extent_map *em;
	काष्ठा map_lookup *map = शून्य;
	u64 *logical = शून्य;
	पूर्णांक i, out_ndaddrs, out_stripe_len;
	पूर्णांक ret;

	em = alloc_extent_map();
	अगर (!em) अणु
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		वापस -ENOMEM;
	पूर्ण

	map = kदो_स्मृति(map_lookup_size(test->num_stripes), GFP_KERNEL);
	अगर (!map) अणु
		kमुक्त(em);
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		वापस -ENOMEM;
	पूर्ण

	set_bit(EXTENT_FLAG_FS_MAPPING, &em->flags);
	/* Start at 4GiB logical address */
	em->start = SZ_4G;
	em->len = test->data_stripe_size * test->num_data_stripes;
	em->block_len = em->len;
	em->orig_block_len = test->data_stripe_size;
	em->map_lookup = map;

	map->num_stripes = test->num_stripes;
	map->stripe_len = BTRFS_STRIPE_LEN;
	map->type = test->raid_type;

	क्रम (i = 0; i < map->num_stripes; i++) अणु
		काष्ठा btrfs_device *dev = btrfs_alloc_dummy_device(fs_info);

		अगर (IS_ERR(dev)) अणु
			test_err("cannot allocate device");
			ret = PTR_ERR(dev);
			जाओ out;
		पूर्ण
		map->stripes[i].dev = dev;
		map->stripes[i].physical = test->data_stripe_phys_start[i];
	पूर्ण

	ग_लिखो_lock(&fs_info->mapping_tree.lock);
	ret = add_extent_mapping(&fs_info->mapping_tree, em, 0);
	ग_लिखो_unlock(&fs_info->mapping_tree.lock);
	अगर (ret) अणु
		test_err("error adding block group mapping to mapping tree");
		जाओ out_मुक्त;
	पूर्ण

	ret = btrfs_rmap_block(fs_info, em->start, शून्य, btrfs_sb_offset(1),
			       &logical, &out_ndaddrs, &out_stripe_len);
	अगर (ret || (out_ndaddrs == 0 && test->expected_mapped_addr)) अणु
		test_err("didn't rmap anything but expected %d",
			 test->expected_mapped_addr);
		जाओ out;
	पूर्ण

	अगर (out_stripe_len != BTRFS_STRIPE_LEN) अणु
		test_err("calculated stripe length doesn't match");
		जाओ out;
	पूर्ण

	अगर (out_ndaddrs != test->expected_mapped_addr) अणु
		क्रम (i = 0; i < out_ndaddrs; i++)
			test_msg("mapped %llu", logical[i]);
		test_err("unexpected number of mapped addresses: %d", out_ndaddrs);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < out_ndaddrs; i++) अणु
		अगर (logical[i] != test->mapped_logical[i]) अणु
			test_err("unexpected logical address mapped");
			जाओ out;
		पूर्ण
	पूर्ण

	ret = 0;
out:
	ग_लिखो_lock(&fs_info->mapping_tree.lock);
	हटाओ_extent_mapping(&fs_info->mapping_tree, em);
	ग_लिखो_unlock(&fs_info->mapping_tree.lock);
	/* For us */
	मुक्त_extent_map(em);
out_मुक्त:
	/* For the tree */
	मुक्त_extent_map(em);
	kमुक्त(logical);
	वापस ret;
पूर्ण

पूर्णांक btrfs_test_extent_map(व्योम)
अणु
	काष्ठा btrfs_fs_info *fs_info = शून्य;
	काष्ठा extent_map_tree *em_tree;
	पूर्णांक ret = 0, i;
	काष्ठा rmap_test_vector rmap_tests[] = अणु
		अणु
			/*
			 * Test a chunk with 2 data stripes one of which
			 * पूर्णांकeresects the physical address of the super block
			 * is correctly recognised.
			 */
			.raid_type = BTRFS_BLOCK_GROUP_RAID1,
			.physical_start = SZ_64M - SZ_4M,
			.data_stripe_size = SZ_256M,
			.num_data_stripes = 2,
			.num_stripes = 2,
			.data_stripe_phys_start =
				अणुSZ_64M - SZ_4M, SZ_64M - SZ_4M + SZ_256Mपूर्ण,
			.expected_mapped_addr = true,
			.mapped_logical= अणुSZ_4G + SZ_4Mपूर्ण
		पूर्ण,
		अणु
			/*
			 * Test that out-of-range physical addresses are
			 * ignored
			 */

			 /* SINGLE chunk type */
			.raid_type = 0,
			.physical_start = SZ_4G,
			.data_stripe_size = SZ_256M,
			.num_data_stripes = 1,
			.num_stripes = 1,
			.data_stripe_phys_start = अणुSZ_256Mपूर्ण,
			.expected_mapped_addr = false,
			.mapped_logical = अणु0पूर्ण
		पूर्ण
	पूर्ण;

	test_msg("running extent_map tests");

	/*
	 * Note: the fs_info is not set up completely, we only need
	 * fs_info::fsid क्रम the tracepoपूर्णांक.
	 */
	fs_info = btrfs_alloc_dummy_fs_info(PAGE_SIZE, PAGE_SIZE);
	अगर (!fs_info) अणु
		test_std_err(TEST_ALLOC_FS_INFO);
		वापस -ENOMEM;
	पूर्ण

	em_tree = kzalloc(माप(*em_tree), GFP_KERNEL);
	अगर (!em_tree) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	extent_map_tree_init(em_tree);

	ret = test_हाल_1(fs_info, em_tree);
	अगर (ret)
		जाओ out;
	ret = test_हाल_2(fs_info, em_tree);
	अगर (ret)
		जाओ out;
	ret = test_हाल_3(fs_info, em_tree);
	अगर (ret)
		जाओ out;
	ret = test_हाल_4(fs_info, em_tree);

	test_msg("running rmap tests");
	क्रम (i = 0; i < ARRAY_SIZE(rmap_tests); i++) अणु
		ret = test_rmap_block(fs_info, &rmap_tests[i]);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	kमुक्त(em_tree);
	btrfs_मुक्त_dummy_fs_info(fs_info);

	वापस ret;
पूर्ण
