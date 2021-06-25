<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 Fusion IO.  All rights reserved.
 */

#समावेश <linux/slab.h>
#समावेश "btrfs-tests.h"
#समावेश "../ctree.h"
#समावेश "../disk-io.h"
#समावेश "../free-space-cache.h"
#समावेश "../block-group.h"

#घोषणा BITS_PER_BITMAP		(PAGE_SIZE * 8UL)

/*
 * This test just करोes basic sanity checking, making sure we can add an extent
 * entry and हटाओ space from either end and the middle, and make sure we can
 * हटाओ space that covers adjacent extent entries.
 */
अटल पूर्णांक test_extents(काष्ठा btrfs_block_group *cache)
अणु
	पूर्णांक ret = 0;

	test_msg("running extent only tests");

	/* First just make sure we can हटाओ an entire entry */
	ret = btrfs_add_मुक्त_space(cache, 0, SZ_4M);
	अगर (ret) अणु
		test_err("error adding initial extents %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, 0, SZ_4M);
	अगर (ret) अणु
		test_err("error removing extent %d", ret);
		वापस ret;
	पूर्ण

	अगर (test_check_exists(cache, 0, SZ_4M)) अणु
		test_err("full remove left some lingering space");
		वापस -1;
	पूर्ण

	/* Ok edge and middle हालs now */
	ret = btrfs_add_मुक्त_space(cache, 0, SZ_4M);
	अगर (ret) अणु
		test_err("error adding half extent %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, 3 * SZ_1M, SZ_1M);
	अगर (ret) अणु
		test_err("error removing tail end %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, 0, SZ_1M);
	अगर (ret) अणु
		test_err("error removing front end %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, SZ_2M, 4096);
	अगर (ret) अणु
		test_err("error removing middle piece %d", ret);
		वापस ret;
	पूर्ण

	अगर (test_check_exists(cache, 0, SZ_1M)) अणु
		test_err("still have space at the front");
		वापस -1;
	पूर्ण

	अगर (test_check_exists(cache, SZ_2M, 4096)) अणु
		test_err("still have space in the middle");
		वापस -1;
	पूर्ण

	अगर (test_check_exists(cache, 3 * SZ_1M, SZ_1M)) अणु
		test_err("still have space at the end");
		वापस -1;
	पूर्ण

	/* Cleanup */
	__btrfs_हटाओ_मुक्त_space_cache(cache->मुक्त_space_ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक test_biपंचांगaps(काष्ठा btrfs_block_group *cache, u32 sectorsize)
अणु
	u64 next_biपंचांगap_offset;
	पूर्णांक ret;

	test_msg("running bitmap only tests");

	ret = test_add_मुक्त_space_entry(cache, 0, SZ_4M, 1);
	अगर (ret) अणु
		test_err("couldn't create a bitmap entry %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, 0, SZ_4M);
	अगर (ret) अणु
		test_err("error removing bitmap full range %d", ret);
		वापस ret;
	पूर्ण

	अगर (test_check_exists(cache, 0, SZ_4M)) अणु
		test_err("left some space in bitmap");
		वापस -1;
	पूर्ण

	ret = test_add_मुक्त_space_entry(cache, 0, SZ_4M, 1);
	अगर (ret) अणु
		test_err("couldn't add to our bitmap entry %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, SZ_1M, SZ_2M);
	अगर (ret) अणु
		test_err("couldn't remove middle chunk %d", ret);
		वापस ret;
	पूर्ण

	/*
	 * The first biपंचांगap we have starts at offset 0 so the next one is just
	 * at the end of the first biपंचांगap.
	 */
	next_biपंचांगap_offset = (u64)(BITS_PER_BITMAP * sectorsize);

	/* Test a bit straddling two biपंचांगaps */
	ret = test_add_मुक्त_space_entry(cache, next_biपंचांगap_offset - SZ_2M,
					SZ_4M, 1);
	अगर (ret) अणु
		test_err("couldn't add space that straddles two bitmaps %d",
				ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, next_biपंचांगap_offset - SZ_1M, SZ_2M);
	अगर (ret) अणु
		test_err("couldn't remove overlapping space %d", ret);
		वापस ret;
	पूर्ण

	अगर (test_check_exists(cache, next_biपंचांगap_offset - SZ_1M, SZ_2M)) अणु
		test_err("left some space when removing overlapping");
		वापस -1;
	पूर्ण

	__btrfs_हटाओ_मुक्त_space_cache(cache->मुक्त_space_ctl);

	वापस 0;
पूर्ण

/* This is the high grade jackassery */
अटल पूर्णांक test_biपंचांगaps_and_extents(काष्ठा btrfs_block_group *cache,
				    u32 sectorsize)
अणु
	u64 biपंचांगap_offset = (u64)(BITS_PER_BITMAP * sectorsize);
	पूर्णांक ret;

	test_msg("running bitmap and extent tests");

	/*
	 * First let's करो something simple, an extent at the same offset as the
	 * biपंचांगap, but the मुक्त space completely in the extent and then
	 * completely in the biपंचांगap.
	 */
	ret = test_add_मुक्त_space_entry(cache, SZ_4M, SZ_1M, 1);
	अगर (ret) अणु
		test_err("couldn't create bitmap entry %d", ret);
		वापस ret;
	पूर्ण

	ret = test_add_मुक्त_space_entry(cache, 0, SZ_1M, 0);
	अगर (ret) अणु
		test_err("couldn't add extent entry %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, 0, SZ_1M);
	अगर (ret) अणु
		test_err("couldn't remove extent entry %d", ret);
		वापस ret;
	पूर्ण

	अगर (test_check_exists(cache, 0, SZ_1M)) अणु
		test_err("left remnants after our remove");
		वापस -1;
	पूर्ण

	/* Now to add back the extent entry and हटाओ from the biपंचांगap */
	ret = test_add_मुक्त_space_entry(cache, 0, SZ_1M, 0);
	अगर (ret) अणु
		test_err("couldn't re-add extent entry %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, SZ_4M, SZ_1M);
	अगर (ret) अणु
		test_err("couldn't remove from bitmap %d", ret);
		वापस ret;
	पूर्ण

	अगर (test_check_exists(cache, SZ_4M, SZ_1M)) अणु
		test_err("left remnants in the bitmap");
		वापस -1;
	पूर्ण

	/*
	 * Ok so a little more evil, extent entry and biपंचांगap at the same offset,
	 * removing an overlapping chunk.
	 */
	ret = test_add_मुक्त_space_entry(cache, SZ_1M, SZ_4M, 1);
	अगर (ret) अणु
		test_err("couldn't add to a bitmap %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, SZ_512K, 3 * SZ_1M);
	अगर (ret) अणु
		test_err("couldn't remove overlapping space %d", ret);
		वापस ret;
	पूर्ण

	अगर (test_check_exists(cache, SZ_512K, 3 * SZ_1M)) अणु
		test_err("left over pieces after removing overlapping");
		वापस -1;
	पूर्ण

	__btrfs_हटाओ_मुक्त_space_cache(cache->मुक्त_space_ctl);

	/* Now with the extent entry offset पूर्णांकo the biपंचांगap */
	ret = test_add_मुक्त_space_entry(cache, SZ_4M, SZ_4M, 1);
	अगर (ret) अणु
		test_err("couldn't add space to the bitmap %d", ret);
		वापस ret;
	पूर्ण

	ret = test_add_मुक्त_space_entry(cache, SZ_2M, SZ_2M, 0);
	अगर (ret) अणु
		test_err("couldn't add extent to the cache %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, 3 * SZ_1M, SZ_4M);
	अगर (ret) अणु
		test_err("problem removing overlapping space %d", ret);
		वापस ret;
	पूर्ण

	अगर (test_check_exists(cache, 3 * SZ_1M, SZ_4M)) अणु
		test_err("left something behind when removing space");
		वापस -1;
	पूर्ण

	/*
	 * This has blown up in the past, the extent entry starts beक्रमe the
	 * biपंचांगap entry, but we're trying to हटाओ an offset that falls
	 * completely within the biपंचांगap range and is in both the extent entry
	 * and the biपंचांगap entry, looks like this
	 *
	 *   [ extent ]
	 *      [ biपंचांगap ]
	 *        [ del ]
	 */
	__btrfs_हटाओ_मुक्त_space_cache(cache->मुक्त_space_ctl);
	ret = test_add_मुक्त_space_entry(cache, biपंचांगap_offset + SZ_4M, SZ_4M, 1);
	अगर (ret) अणु
		test_err("couldn't add bitmap %d", ret);
		वापस ret;
	पूर्ण

	ret = test_add_मुक्त_space_entry(cache, biपंचांगap_offset - SZ_1M,
					5 * SZ_1M, 0);
	अगर (ret) अणु
		test_err("couldn't add extent entry %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, biपंचांगap_offset + SZ_1M, 5 * SZ_1M);
	अगर (ret) अणु
		test_err("failed to free our space %d", ret);
		वापस ret;
	पूर्ण

	अगर (test_check_exists(cache, biपंचांगap_offset + SZ_1M, 5 * SZ_1M)) अणु
		test_err("left stuff over");
		वापस -1;
	पूर्ण

	__btrfs_हटाओ_मुक्त_space_cache(cache->मुक्त_space_ctl);

	/*
	 * This blew up beक्रमe, we have part of the मुक्त space in a biपंचांगap and
	 * then the entirety of the rest of the space in an extent.  This used
	 * to वापस -EAGAIN back from btrfs_हटाओ_extent, make sure this
	 * करोesn't happen.
	 */
	ret = test_add_मुक्त_space_entry(cache, SZ_1M, SZ_2M, 1);
	अगर (ret) अणु
		test_err("couldn't add bitmap entry %d", ret);
		वापस ret;
	पूर्ण

	ret = test_add_मुक्त_space_entry(cache, 3 * SZ_1M, SZ_1M, 0);
	अगर (ret) अणु
		test_err("couldn't add extent entry %d", ret);
		वापस ret;
	पूर्ण

	ret = btrfs_हटाओ_मुक्त_space(cache, SZ_1M, 3 * SZ_1M);
	अगर (ret) अणु
		test_err("error removing bitmap and extent overlapping %d", ret);
		वापस ret;
	पूर्ण

	__btrfs_हटाओ_मुक्त_space_cache(cache->मुक्त_space_ctl);
	वापस 0;
पूर्ण

/* Used by test_steal_space_from_biपंचांगap_to_extent(). */
अटल bool test_use_biपंचांगap(काष्ठा btrfs_मुक्त_space_ctl *ctl,
			    काष्ठा btrfs_मुक्त_space *info)
अणु
	वापस ctl->मुक्त_extents > 0;
पूर्ण

/* Used by test_steal_space_from_biपंचांगap_to_extent(). */
अटल पूर्णांक
check_num_extents_and_biपंचांगaps(स्थिर काष्ठा btrfs_block_group *cache,
			      स्थिर पूर्णांक num_extents,
			      स्थिर पूर्णांक num_biपंचांगaps)
अणु
	अगर (cache->मुक्त_space_ctl->मुक्त_extents != num_extents) अणु
		test_err(
		"incorrect # of extent entries in the cache: %d, expected %d",
			 cache->मुक्त_space_ctl->मुक्त_extents, num_extents);
		वापस -EINVAL;
	पूर्ण
	अगर (cache->मुक्त_space_ctl->total_biपंचांगaps != num_biपंचांगaps) अणु
		test_err(
		"incorrect # of extent entries in the cache: %d, expected %d",
			 cache->मुक्त_space_ctl->total_biपंचांगaps, num_biपंचांगaps);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Used by test_steal_space_from_biपंचांगap_to_extent(). */
अटल पूर्णांक check_cache_empty(काष्ठा btrfs_block_group *cache)
अणु
	u64 offset;
	u64 max_extent_size;

	/*
	 * Now lets confirm that there's असलolutely no मुक्त space left to
	 * allocate.
	 */
	अगर (cache->मुक्त_space_ctl->मुक्त_space != 0) अणु
		test_err("cache free space is not 0");
		वापस -EINVAL;
	पूर्ण

	/* And any allocation request, no matter how small, should fail now. */
	offset = btrfs_find_space_क्रम_alloc(cache, 0, 4096, 0,
					    &max_extent_size);
	अगर (offset != 0) अणु
		test_err("space allocation did not fail, returned offset: %llu",
			 offset);
		वापस -EINVAL;
	पूर्ण

	/* And no extent nor biपंचांगap entries in the cache anymore. */
	वापस check_num_extents_and_biपंचांगaps(cache, 0, 0);
पूर्ण

/*
 * Beक्रमe we were able to steal मुक्त space from a biपंचांगap entry to an extent
 * entry, we could end up with 2 entries representing a contiguous मुक्त space.
 * One would be an extent entry and the other a biपंचांगap entry. Since in order
 * to allocate space to a caller we use only 1 entry, we couldn't वापस that
 * whole range to the caller अगर it was requested. This क्रमced the caller to
 * either assume ENOSPC or perक्रमm several smaller space allocations, which
 * wasn't optimal as they could be spपढ़ो all over the block group जबतक under
 * concurrency (extra overhead and fragmentation).
 *
 * This stealing approach is beneficial, since we always prefer to allocate
 * from extent entries, both क्रम clustered and non-clustered allocation
 * requests.
 */
अटल पूर्णांक
test_steal_space_from_biपंचांगap_to_extent(काष्ठा btrfs_block_group *cache,
				       u32 sectorsize)
अणु
	पूर्णांक ret;
	u64 offset;
	u64 max_extent_size;
	स्थिर काष्ठा btrfs_मुक्त_space_op test_मुक्त_space_ops = अणु
		.use_biपंचांगap = test_use_biपंचांगap,
	पूर्ण;
	स्थिर काष्ठा btrfs_मुक्त_space_op *orig_मुक्त_space_ops;

	test_msg("running space stealing from bitmap to extent tests");

	/*
	 * For this test, we want to ensure we end up with an extent entry
	 * immediately adjacent to a biपंचांगap entry, where the biपंचांगap starts
	 * at an offset where the extent entry ends. We keep adding and
	 * removing मुक्त space to reach पूर्णांकo this state, but to get there
	 * we need to reach a poपूर्णांक where marking new मुक्त space करोesn't
	 * result in adding new extent entries or merging the new space
	 * with existing extent entries - the space ends up being marked
	 * in an existing biपंचांगap that covers the new मुक्त space range.
	 *
	 * To get there, we need to reach the threshold defined set at
	 * cache->मुक्त_space_ctl->extents_thresh, which currently is
	 * 256 extents on a x86_64 प्रणाली at least, and a few other
	 * conditions (check मुक्त_space_cache.c). Instead of making the
	 * test much दीर्घer and complicated, use a "use_bitmap" operation
	 * that क्रमces use of biपंचांगaps as soon as we have at least 1
	 * extent entry.
	 */
	orig_मुक्त_space_ops = cache->मुक्त_space_ctl->op;
	cache->मुक्त_space_ctl->op = &test_मुक्त_space_ops;

	/*
	 * Extent entry covering मुक्त space range [128Mb - 256Kb, 128Mb - 128Kb[
	 */
	ret = test_add_मुक्त_space_entry(cache, SZ_128M - SZ_256K, SZ_128K, 0);
	अगर (ret) अणु
		test_err("couldn't add extent entry %d", ret);
		वापस ret;
	पूर्ण

	/* Biपंचांगap entry covering मुक्त space range [128Mb + 512Kb, 256Mb[ */
	ret = test_add_मुक्त_space_entry(cache, SZ_128M + SZ_512K,
					SZ_128M - SZ_512K, 1);
	अगर (ret) अणु
		test_err("couldn't add bitmap entry %d", ret);
		वापस ret;
	पूर्ण

	ret = check_num_extents_and_biपंचांगaps(cache, 2, 1);
	अगर (ret)
		वापस ret;

	/*
	 * Now make only the first 256Kb of the biपंचांगap marked as मुक्त, so that
	 * we end up with only the following ranges marked as मुक्त space:
	 *
	 * [128Mb - 256Kb, 128Mb - 128Kb[
	 * [128Mb + 512Kb, 128Mb + 768Kb[
	 */
	ret = btrfs_हटाओ_मुक्त_space(cache,
				      SZ_128M + 768 * SZ_1K,
				      SZ_128M - 768 * SZ_1K);
	अगर (ret) अणु
		test_err("failed to free part of bitmap space %d", ret);
		वापस ret;
	पूर्ण

	/* Confirm that only those 2 ranges are marked as मुक्त. */
	अगर (!test_check_exists(cache, SZ_128M - SZ_256K, SZ_128K)) अणु
		test_err("free space range missing");
		वापस -ENOENT;
	पूर्ण
	अगर (!test_check_exists(cache, SZ_128M + SZ_512K, SZ_256K)) अणु
		test_err("free space range missing");
		वापस -ENOENT;
	पूर्ण

	/*
	 * Confirm that the biपंचांगap range [128Mb + 768Kb, 256Mb[ isn't marked
	 * as मुक्त anymore.
	 */
	अगर (test_check_exists(cache, SZ_128M + 768 * SZ_1K,
			      SZ_128M - 768 * SZ_1K)) अणु
		test_err("bitmap region not removed from space cache");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Confirm that the region [128Mb + 256Kb, 128Mb + 512Kb[, which is
	 * covered by the biपंचांगap, isn't marked as मुक्त.
	 */
	अगर (test_check_exists(cache, SZ_128M + SZ_256K, SZ_256K)) अणु
		test_err("invalid bitmap region marked as free");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Confirm that the region [128Mb, 128Mb + 256Kb[, which is covered
	 * by the biपंचांगap too, isn't marked as मुक्त either.
	 */
	अगर (test_check_exists(cache, SZ_128M, SZ_256K)) अणु
		test_err("invalid bitmap region marked as free");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Now lets mark the region [128Mb, 128Mb + 512Kb[ as मुक्त too. But,
	 * lets make sure the मुक्त space cache marks it as मुक्त in the biपंचांगap,
	 * and करोesn't insert a new extent entry to represent this region.
	 */
	ret = btrfs_add_मुक्त_space(cache, SZ_128M, SZ_512K);
	अगर (ret) अणु
		test_err("error adding free space: %d", ret);
		वापस ret;
	पूर्ण
	/* Confirm the region is marked as मुक्त. */
	अगर (!test_check_exists(cache, SZ_128M, SZ_512K)) अणु
		test_err("bitmap region not marked as free");
		वापस -ENOENT;
	पूर्ण

	/*
	 * Confirm that no new extent entries or biपंचांगap entries were added to
	 * the cache after adding that मुक्त space region.
	 */
	ret = check_num_extents_and_biपंचांगaps(cache, 2, 1);
	अगर (ret)
		वापस ret;

	/*
	 * Now lets add a small मुक्त space region to the right of the previous
	 * one, which is not contiguous with it and is part of the biपंचांगap too.
	 * The goal is to test that the biपंचांगap entry space stealing करोesn't
	 * steal this space region.
	 */
	ret = btrfs_add_मुक्त_space(cache, SZ_128M + SZ_16M, sectorsize);
	अगर (ret) अणु
		test_err("error adding free space: %d", ret);
		वापस ret;
	पूर्ण

	/*
	 * Confirm that no new extent entries or biपंचांगap entries were added to
	 * the cache after adding that मुक्त space region.
	 */
	ret = check_num_extents_and_biपंचांगaps(cache, 2, 1);
	अगर (ret)
		वापस ret;

	/*
	 * Now mark the region [128Mb - 128Kb, 128Mb[ as मुक्त too. This will
	 * expand the range covered by the existing extent entry that represents
	 * the मुक्त space [128Mb - 256Kb, 128Mb - 128Kb[.
	 */
	ret = btrfs_add_मुक्त_space(cache, SZ_128M - SZ_128K, SZ_128K);
	अगर (ret) अणु
		test_err("error adding free space: %d", ret);
		वापस ret;
	पूर्ण
	/* Confirm the region is marked as मुक्त. */
	अगर (!test_check_exists(cache, SZ_128M - SZ_128K, SZ_128K)) अणु
		test_err("extent region not marked as free");
		वापस -ENOENT;
	पूर्ण

	/*
	 * Confirm that our extent entry didn't stole all मुक्त space from the
	 * biपंचांगap, because of the small 4Kb मुक्त space region.
	 */
	ret = check_num_extents_and_biपंचांगaps(cache, 2, 1);
	अगर (ret)
		वापस ret;

	/*
	 * So now we have the range [128Mb - 256Kb, 128Mb + 768Kb[ as मुक्त
	 * space. Without stealing biपंचांगap मुक्त space पूर्णांकo extent entry space,
	 * we would have all this मुक्त space represented by 2 entries in the
	 * cache:
	 *
	 * extent entry covering range: [128Mb - 256Kb, 128Mb[
	 * biपंचांगap entry covering range: [128Mb, 128Mb + 768Kb[
	 *
	 * Attempting to allocate the whole मुक्त space (1Mb) would fail, because
	 * we can't allocate from multiple entries.
	 * With the biपंचांगap मुक्त space stealing, we get a single extent entry
	 * that represents the 1Mb मुक्त space, and thereक्रमe we're able to
	 * allocate the whole मुक्त space at once.
	 */
	अगर (!test_check_exists(cache, SZ_128M - SZ_256K, SZ_1M)) अणु
		test_err("expected region not marked as free");
		वापस -ENOENT;
	पूर्ण

	अगर (cache->मुक्त_space_ctl->मुक्त_space != (SZ_1M + sectorsize)) अणु
		test_err("cache free space is not 1Mb + %u", sectorsize);
		वापस -EINVAL;
	पूर्ण

	offset = btrfs_find_space_क्रम_alloc(cache,
					    0, SZ_1M, 0,
					    &max_extent_size);
	अगर (offset != (SZ_128M - SZ_256K)) अणु
		test_err(
	"failed to allocate 1Mb from space cache, returned offset is: %llu",
			 offset);
		वापस -EINVAL;
	पूर्ण

	/*
	 * All that reमुख्यs is a sectorsize मुक्त space region in a biपंचांगap.
	 * Confirm.
	 */
	ret = check_num_extents_and_biपंचांगaps(cache, 1, 1);
	अगर (ret)
		वापस ret;

	अगर (cache->मुक्त_space_ctl->मुक्त_space != sectorsize) अणु
		test_err("cache free space is not %u", sectorsize);
		वापस -EINVAL;
	पूर्ण

	offset = btrfs_find_space_क्रम_alloc(cache,
					    0, sectorsize, 0,
					    &max_extent_size);
	अगर (offset != (SZ_128M + SZ_16M)) अणु
		test_err("failed to allocate %u, returned offset : %llu",
			 sectorsize, offset);
		वापस -EINVAL;
	पूर्ण

	ret = check_cache_empty(cache);
	अगर (ret)
		वापस ret;

	__btrfs_हटाओ_मुक्त_space_cache(cache->मुक्त_space_ctl);

	/*
	 * Now test a similar scenario, but where our extent entry is located
	 * to the right of the biपंचांगap entry, so that we can check that stealing
	 * space from a biपंचांगap to the front of an extent entry works.
	 */

	/*
	 * Extent entry covering मुक्त space range [128Mb + 128Kb, 128Mb + 256Kb[
	 */
	ret = test_add_मुक्त_space_entry(cache, SZ_128M + SZ_128K, SZ_128K, 0);
	अगर (ret) अणु
		test_err("couldn't add extent entry %d", ret);
		वापस ret;
	पूर्ण

	/* Biपंचांगap entry covering मुक्त space range [0, 128Mb - 512Kb[ */
	ret = test_add_मुक्त_space_entry(cache, 0, SZ_128M - SZ_512K, 1);
	अगर (ret) अणु
		test_err("couldn't add bitmap entry %d", ret);
		वापस ret;
	पूर्ण

	ret = check_num_extents_and_biपंचांगaps(cache, 2, 1);
	अगर (ret)
		वापस ret;

	/*
	 * Now make only the last 256Kb of the biपंचांगap marked as मुक्त, so that
	 * we end up with only the following ranges marked as मुक्त space:
	 *
	 * [128Mb + 128b, 128Mb + 256Kb[
	 * [128Mb - 768Kb, 128Mb - 512Kb[
	 */
	ret = btrfs_हटाओ_मुक्त_space(cache, 0, SZ_128M - 768 * SZ_1K);
	अगर (ret) अणु
		test_err("failed to free part of bitmap space %d", ret);
		वापस ret;
	पूर्ण

	/* Confirm that only those 2 ranges are marked as मुक्त. */
	अगर (!test_check_exists(cache, SZ_128M + SZ_128K, SZ_128K)) अणु
		test_err("free space range missing");
		वापस -ENOENT;
	पूर्ण
	अगर (!test_check_exists(cache, SZ_128M - 768 * SZ_1K, SZ_256K)) अणु
		test_err("free space range missing");
		वापस -ENOENT;
	पूर्ण

	/*
	 * Confirm that the biपंचांगap range [0, 128Mb - 768Kb[ isn't marked
	 * as मुक्त anymore.
	 */
	अगर (test_check_exists(cache, 0, SZ_128M - 768 * SZ_1K)) अणु
		test_err("bitmap region not removed from space cache");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Confirm that the region [128Mb - 512Kb, 128Mb[, which is
	 * covered by the biपंचांगap, isn't marked as मुक्त.
	 */
	अगर (test_check_exists(cache, SZ_128M - SZ_512K, SZ_512K)) अणु
		test_err("invalid bitmap region marked as free");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Now lets mark the region [128Mb - 512Kb, 128Mb[ as मुक्त too. But,
	 * lets make sure the मुक्त space cache marks it as मुक्त in the biपंचांगap,
	 * and करोesn't insert a new extent entry to represent this region.
	 */
	ret = btrfs_add_मुक्त_space(cache, SZ_128M - SZ_512K, SZ_512K);
	अगर (ret) अणु
		test_err("error adding free space: %d", ret);
		वापस ret;
	पूर्ण
	/* Confirm the region is marked as मुक्त. */
	अगर (!test_check_exists(cache, SZ_128M - SZ_512K, SZ_512K)) अणु
		test_err("bitmap region not marked as free");
		वापस -ENOENT;
	पूर्ण

	/*
	 * Confirm that no new extent entries or biपंचांगap entries were added to
	 * the cache after adding that मुक्त space region.
	 */
	ret = check_num_extents_and_biपंचांगaps(cache, 2, 1);
	अगर (ret)
		वापस ret;

	/*
	 * Now lets add a small मुक्त space region to the left of the previous
	 * one, which is not contiguous with it and is part of the biपंचांगap too.
	 * The goal is to test that the biपंचांगap entry space stealing करोesn't
	 * steal this space region.
	 */
	ret = btrfs_add_मुक्त_space(cache, SZ_32M, 2 * sectorsize);
	अगर (ret) अणु
		test_err("error adding free space: %d", ret);
		वापस ret;
	पूर्ण

	/*
	 * Now mark the region [128Mb, 128Mb + 128Kb[ as मुक्त too. This will
	 * expand the range covered by the existing extent entry that represents
	 * the मुक्त space [128Mb + 128Kb, 128Mb + 256Kb[.
	 */
	ret = btrfs_add_मुक्त_space(cache, SZ_128M, SZ_128K);
	अगर (ret) अणु
		test_err("error adding free space: %d", ret);
		वापस ret;
	पूर्ण
	/* Confirm the region is marked as मुक्त. */
	अगर (!test_check_exists(cache, SZ_128M, SZ_128K)) अणु
		test_err("extent region not marked as free");
		वापस -ENOENT;
	पूर्ण

	/*
	 * Confirm that our extent entry didn't stole all मुक्त space from the
	 * biपंचांगap, because of the small 2 * sectorsize मुक्त space region.
	 */
	ret = check_num_extents_and_biपंचांगaps(cache, 2, 1);
	अगर (ret)
		वापस ret;

	/*
	 * So now we have the range [128Mb - 768Kb, 128Mb + 256Kb[ as मुक्त
	 * space. Without stealing biपंचांगap मुक्त space पूर्णांकo extent entry space,
	 * we would have all this मुक्त space represented by 2 entries in the
	 * cache:
	 *
	 * extent entry covering range: [128Mb, 128Mb + 256Kb[
	 * biपंचांगap entry covering range: [128Mb - 768Kb, 128Mb[
	 *
	 * Attempting to allocate the whole मुक्त space (1Mb) would fail, because
	 * we can't allocate from multiple entries.
	 * With the biपंचांगap मुक्त space stealing, we get a single extent entry
	 * that represents the 1Mb मुक्त space, and thereक्रमe we're able to
	 * allocate the whole मुक्त space at once.
	 */
	अगर (!test_check_exists(cache, SZ_128M - 768 * SZ_1K, SZ_1M)) अणु
		test_err("expected region not marked as free");
		वापस -ENOENT;
	पूर्ण

	अगर (cache->मुक्त_space_ctl->मुक्त_space != (SZ_1M + 2 * sectorsize)) अणु
		test_err("cache free space is not 1Mb + %u", 2 * sectorsize);
		वापस -EINVAL;
	पूर्ण

	offset = btrfs_find_space_क्रम_alloc(cache, 0, SZ_1M, 0,
					    &max_extent_size);
	अगर (offset != (SZ_128M - 768 * SZ_1K)) अणु
		test_err(
	"failed to allocate 1Mb from space cache, returned offset is: %llu",
			 offset);
		वापस -EINVAL;
	पूर्ण

	/*
	 * All that reमुख्यs is 2 * sectorsize मुक्त space region
	 * in a biपंचांगap. Confirm.
	 */
	ret = check_num_extents_and_biपंचांगaps(cache, 1, 1);
	अगर (ret)
		वापस ret;

	अगर (cache->मुक्त_space_ctl->मुक्त_space != 2 * sectorsize) अणु
		test_err("cache free space is not %u", 2 * sectorsize);
		वापस -EINVAL;
	पूर्ण

	offset = btrfs_find_space_क्रम_alloc(cache,
					    0, 2 * sectorsize, 0,
					    &max_extent_size);
	अगर (offset != SZ_32M) अणु
		test_err("failed to allocate %u, offset: %llu",
			 2 * sectorsize, offset);
		वापस -EINVAL;
	पूर्ण

	ret = check_cache_empty(cache);
	अगर (ret)
		वापस ret;

	cache->मुक्त_space_ctl->op = orig_मुक्त_space_ops;
	__btrfs_हटाओ_मुक्त_space_cache(cache->मुक्त_space_ctl);

	वापस 0;
पूर्ण

पूर्णांक btrfs_test_मुक्त_space_cache(u32 sectorsize, u32 nodesize)
अणु
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_block_group *cache;
	काष्ठा btrfs_root *root = शून्य;
	पूर्णांक ret = -ENOMEM;

	test_msg("running btrfs free space cache tests");
	fs_info = btrfs_alloc_dummy_fs_info(nodesize, sectorsize);
	अगर (!fs_info) अणु
		test_std_err(TEST_ALLOC_FS_INFO);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * For ppc64 (with 64k page size), bytes per biपंचांगap might be
	 * larger than 1G.  To make biपंचांगap test available in ppc64,
	 * alloc dummy block group whose size cross biपंचांगaps.
	 */
	cache = btrfs_alloc_dummy_block_group(fs_info,
				      BITS_PER_BITMAP * sectorsize + PAGE_SIZE);
	अगर (!cache) अणु
		test_std_err(TEST_ALLOC_BLOCK_GROUP);
		btrfs_मुक्त_dummy_fs_info(fs_info);
		वापस 0;
	पूर्ण

	root = btrfs_alloc_dummy_root(fs_info);
	अगर (IS_ERR(root)) अणु
		test_std_err(TEST_ALLOC_ROOT);
		ret = PTR_ERR(root);
		जाओ out;
	पूर्ण

	root->fs_info->extent_root = root;

	ret = test_extents(cache);
	अगर (ret)
		जाओ out;
	ret = test_biपंचांगaps(cache, sectorsize);
	अगर (ret)
		जाओ out;
	ret = test_biपंचांगaps_and_extents(cache, sectorsize);
	अगर (ret)
		जाओ out;

	ret = test_steal_space_from_biपंचांगap_to_extent(cache, sectorsize);
out:
	btrfs_मुक्त_dummy_block_group(cache);
	btrfs_मुक्त_dummy_root(root);
	btrfs_मुक्त_dummy_fs_info(fs_info);
	वापस ret;
पूर्ण
