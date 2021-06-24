<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 Fusion IO.  All rights reserved.
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/sizes.h>
#समावेश "btrfs-tests.h"
#समावेश "../ctree.h"
#समावेश "../extent_io.h"
#समावेश "../btrfs_inode.h"

#घोषणा PROCESS_UNLOCK		(1 << 0)
#घोषणा PROCESS_RELEASE		(1 << 1)
#घोषणा PROCESS_TEST_LOCKED	(1 << 2)

अटल noअंतरभूत पूर्णांक process_page_range(काष्ठा inode *inode, u64 start, u64 end,
				       अचिन्हित दीर्घ flags)
अणु
	पूर्णांक ret;
	काष्ठा page *pages[16];
	अचिन्हित दीर्घ index = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ end_index = end >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_pages = end_index - index + 1;
	पूर्णांक i;
	पूर्णांक count = 0;
	पूर्णांक loops = 0;

	जबतक (nr_pages > 0) अणु
		ret = find_get_pages_contig(inode->i_mapping, index,
				     min_t(अचिन्हित दीर्घ, nr_pages,
				     ARRAY_SIZE(pages)), pages);
		क्रम (i = 0; i < ret; i++) अणु
			अगर (flags & PROCESS_TEST_LOCKED &&
			    !PageLocked(pages[i]))
				count++;
			अगर (flags & PROCESS_UNLOCK && PageLocked(pages[i]))
				unlock_page(pages[i]);
			put_page(pages[i]);
			अगर (flags & PROCESS_RELEASE)
				put_page(pages[i]);
		पूर्ण
		nr_pages -= ret;
		index += ret;
		cond_resched();
		loops++;
		अगर (loops > 100000) अणु
			prपूर्णांकk(KERN_ERR
		"stuck in a loop, start %llu, end %llu, nr_pages %lu, ret %d\n",
				start, end, nr_pages, ret);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक test_find_delalloc(u32 sectorsize)
अणु
	काष्ठा inode *inode;
	काष्ठा extent_io_tree *पंचांगp;
	काष्ठा page *page;
	काष्ठा page *locked_page = शून्य;
	अचिन्हित दीर्घ index = 0;
	/* In this test we need at least 2 file extents at its maximum size */
	u64 max_bytes = BTRFS_MAX_EXTENT_SIZE;
	u64 total_dirty = 2 * max_bytes;
	u64 start, end, test_start;
	bool found;
	पूर्णांक ret = -EINVAL;

	test_msg("running find delalloc tests");

	inode = btrfs_new_test_inode();
	अगर (!inode) अणु
		test_std_err(TEST_ALLOC_INODE);
		वापस -ENOMEM;
	पूर्ण
	पंचांगp = &BTRFS_I(inode)->io_tree;

	/*
	 * Passing शून्य as we करोn't have fs_info but tracepoपूर्णांकs are not used
	 * at this poपूर्णांक
	 */
	extent_io_tree_init(शून्य, पंचांगp, IO_TREE_SELFTEST, शून्य);

	/*
	 * First go through and create and mark all of our pages dirty, we pin
	 * everything to make sure our pages करोn't get evicted and screw up our
	 * test.
	 */
	क्रम (index = 0; index < (total_dirty >> PAGE_SHIFT); index++) अणु
		page = find_or_create_page(inode->i_mapping, index, GFP_KERNEL);
		अगर (!page) अणु
			test_err("failed to allocate test page");
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		SetPageDirty(page);
		अगर (index) अणु
			unlock_page(page);
		पूर्ण अन्यथा अणु
			get_page(page);
			locked_page = page;
		पूर्ण
	पूर्ण

	/* Test this scenario
	 * |--- delalloc ---|
	 * |---  search  ---|
	 */
	set_extent_delalloc(पंचांगp, 0, sectorsize - 1, 0, शून्य);
	start = 0;
	end = 0;
	found = find_lock_delalloc_range(inode, locked_page, &start,
					 &end);
	अगर (!found) अणु
		test_err("should have found at least one delalloc");
		जाओ out_bits;
	पूर्ण
	अगर (start != 0 || end != (sectorsize - 1)) अणु
		test_err("expected start 0 end %u, got start %llu end %llu",
			sectorsize - 1, start, end);
		जाओ out_bits;
	पूर्ण
	unlock_extent(पंचांगp, start, end);
	unlock_page(locked_page);
	put_page(locked_page);

	/*
	 * Test this scenario
	 *
	 * |--- delalloc ---|
	 *           |--- search ---|
	 */
	test_start = SZ_64M;
	locked_page = find_lock_page(inode->i_mapping,
				     test_start >> PAGE_SHIFT);
	अगर (!locked_page) अणु
		test_err("couldn't find the locked page");
		जाओ out_bits;
	पूर्ण
	set_extent_delalloc(पंचांगp, sectorsize, max_bytes - 1, 0, शून्य);
	start = test_start;
	end = 0;
	found = find_lock_delalloc_range(inode, locked_page, &start,
					 &end);
	अगर (!found) अणु
		test_err("couldn't find delalloc in our range");
		जाओ out_bits;
	पूर्ण
	अगर (start != test_start || end != max_bytes - 1) अणु
		test_err("expected start %llu end %llu, got start %llu, end %llu",
				test_start, max_bytes - 1, start, end);
		जाओ out_bits;
	पूर्ण
	अगर (process_page_range(inode, start, end,
			       PROCESS_TEST_LOCKED | PROCESS_UNLOCK)) अणु
		test_err("there were unlocked pages in the range");
		जाओ out_bits;
	पूर्ण
	unlock_extent(पंचांगp, start, end);
	/* locked_page was unlocked above */
	put_page(locked_page);

	/*
	 * Test this scenario
	 * |--- delalloc ---|
	 *                    |--- search ---|
	 */
	test_start = max_bytes + sectorsize;
	locked_page = find_lock_page(inode->i_mapping, test_start >>
				     PAGE_SHIFT);
	अगर (!locked_page) अणु
		test_err("couldn't find the locked page");
		जाओ out_bits;
	पूर्ण
	start = test_start;
	end = 0;
	found = find_lock_delalloc_range(inode, locked_page, &start,
					 &end);
	अगर (found) अणु
		test_err("found range when we shouldn't have");
		जाओ out_bits;
	पूर्ण
	अगर (end != (u64)-1) अणु
		test_err("did not return the proper end offset");
		जाओ out_bits;
	पूर्ण

	/*
	 * Test this scenario
	 * [------- delalloc -------|
	 * [max_bytes]|-- search--|
	 *
	 * We are re-using our test_start from above since it works out well.
	 */
	set_extent_delalloc(पंचांगp, max_bytes, total_dirty - 1, 0, शून्य);
	start = test_start;
	end = 0;
	found = find_lock_delalloc_range(inode, locked_page, &start,
					 &end);
	अगर (!found) अणु
		test_err("didn't find our range");
		जाओ out_bits;
	पूर्ण
	अगर (start != test_start || end != total_dirty - 1) अणु
		test_err("expected start %llu end %llu, got start %llu end %llu",
			 test_start, total_dirty - 1, start, end);
		जाओ out_bits;
	पूर्ण
	अगर (process_page_range(inode, start, end,
			       PROCESS_TEST_LOCKED | PROCESS_UNLOCK)) अणु
		test_err("pages in range were not all locked");
		जाओ out_bits;
	पूर्ण
	unlock_extent(पंचांगp, start, end);

	/*
	 * Now to test where we run पूर्णांकo a page that is no दीर्घer dirty in the
	 * range we want to find.
	 */
	page = find_get_page(inode->i_mapping,
			     (max_bytes + SZ_1M) >> PAGE_SHIFT);
	अगर (!page) अणु
		test_err("couldn't find our page");
		जाओ out_bits;
	पूर्ण
	ClearPageDirty(page);
	put_page(page);

	/* We unlocked it in the previous test */
	lock_page(locked_page);
	start = test_start;
	end = 0;
	/*
	 * Currently अगर we fail to find dirty pages in the delalloc range we
	 * will adjust max_bytes करोwn to PAGE_SIZE and then re-search.  If
	 * this changes at any poपूर्णांक in the future we will need to fix this
	 * tests expected behavior.
	 */
	found = find_lock_delalloc_range(inode, locked_page, &start,
					 &end);
	अगर (!found) अणु
		test_err("didn't find our range");
		जाओ out_bits;
	पूर्ण
	अगर (start != test_start && end != test_start + PAGE_SIZE - 1) अणु
		test_err("expected start %llu end %llu, got start %llu end %llu",
			 test_start, test_start + PAGE_SIZE - 1, start, end);
		जाओ out_bits;
	पूर्ण
	अगर (process_page_range(inode, start, end, PROCESS_TEST_LOCKED |
			       PROCESS_UNLOCK)) अणु
		test_err("pages in range were not all locked");
		जाओ out_bits;
	पूर्ण
	ret = 0;
out_bits:
	clear_extent_bits(पंचांगp, 0, total_dirty - 1, (अचिन्हित)-1);
out:
	अगर (locked_page)
		put_page(locked_page);
	process_page_range(inode, 0, total_dirty - 1,
			   PROCESS_UNLOCK | PROCESS_RELEASE);
	iput(inode);
	वापस ret;
पूर्ण

अटल पूर्णांक check_eb_biपंचांगap(अचिन्हित दीर्घ *biपंचांगap, काष्ठा extent_buffer *eb,
			   अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < len * BITS_PER_BYTE; i++) अणु
		पूर्णांक bit, bit1;

		bit = !!test_bit(i, biपंचांगap);
		bit1 = !!extent_buffer_test_bit(eb, 0, i);
		अगर (bit1 != bit) अणु
			test_err("bits do not match");
			वापस -EINVAL;
		पूर्ण

		bit1 = !!extent_buffer_test_bit(eb, i / BITS_PER_BYTE,
						i % BITS_PER_BYTE);
		अगर (bit1 != bit) अणु
			test_err("offset bits do not match");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __test_eb_biपंचांगaps(अचिन्हित दीर्घ *biपंचांगap, काष्ठा extent_buffer *eb,
			     अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ i, j;
	u32 x;
	पूर्णांक ret;

	स_रखो(biपंचांगap, 0, len);
	memzero_extent_buffer(eb, 0, len);
	अगर (स_भेद_extent_buffer(eb, biपंचांगap, 0, len) != 0) अणु
		test_err("bitmap was not zeroed");
		वापस -EINVAL;
	पूर्ण

	biपंचांगap_set(biपंचांगap, 0, len * BITS_PER_BYTE);
	extent_buffer_biपंचांगap_set(eb, 0, 0, len * BITS_PER_BYTE);
	ret = check_eb_biपंचांगap(biपंचांगap, eb, len);
	अगर (ret) अणु
		test_err("setting all bits failed");
		वापस ret;
	पूर्ण

	biपंचांगap_clear(biपंचांगap, 0, len * BITS_PER_BYTE);
	extent_buffer_biपंचांगap_clear(eb, 0, 0, len * BITS_PER_BYTE);
	ret = check_eb_biपंचांगap(biपंचांगap, eb, len);
	अगर (ret) अणु
		test_err("clearing all bits failed");
		वापस ret;
	पूर्ण

	/* Straddling pages test */
	अगर (len > PAGE_SIZE) अणु
		biपंचांगap_set(biपंचांगap,
			(PAGE_SIZE - माप(दीर्घ) / 2) * BITS_PER_BYTE,
			माप(दीर्घ) * BITS_PER_BYTE);
		extent_buffer_biपंचांगap_set(eb, PAGE_SIZE - माप(दीर्घ) / 2, 0,
					माप(दीर्घ) * BITS_PER_BYTE);
		ret = check_eb_biपंचांगap(biपंचांगap, eb, len);
		अगर (ret) अणु
			test_err("setting straddling pages failed");
			वापस ret;
		पूर्ण

		biपंचांगap_set(biपंचांगap, 0, len * BITS_PER_BYTE);
		biपंचांगap_clear(biपंचांगap,
			(PAGE_SIZE - माप(दीर्घ) / 2) * BITS_PER_BYTE,
			माप(दीर्घ) * BITS_PER_BYTE);
		extent_buffer_biपंचांगap_set(eb, 0, 0, len * BITS_PER_BYTE);
		extent_buffer_biपंचांगap_clear(eb, PAGE_SIZE - माप(दीर्घ) / 2, 0,
					माप(दीर्घ) * BITS_PER_BYTE);
		ret = check_eb_biपंचांगap(biपंचांगap, eb, len);
		अगर (ret) अणु
			test_err("clearing straddling pages failed");
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Generate a wonky pseuकरो-अक्रमom bit pattern क्रम the sake of not using
	 * something repetitive that could miss some hypothetical off-by-n bug.
	 */
	x = 0;
	biपंचांगap_clear(biपंचांगap, 0, len * BITS_PER_BYTE);
	extent_buffer_biपंचांगap_clear(eb, 0, 0, len * BITS_PER_BYTE);
	क्रम (i = 0; i < len * BITS_PER_BYTE / 32; i++) अणु
		x = (0x19660dULL * (u64)x + 0x3c6ef35fULL) & 0xffffffffU;
		क्रम (j = 0; j < 32; j++) अणु
			अगर (x & (1U << j)) अणु
				biपंचांगap_set(biपंचांगap, i * 32 + j, 1);
				extent_buffer_biपंचांगap_set(eb, 0, i * 32 + j, 1);
			पूर्ण
		पूर्ण
	पूर्ण

	ret = check_eb_biपंचांगap(biपंचांगap, eb, len);
	अगर (ret) अणु
		test_err("random bit pattern failed");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक test_eb_biपंचांगaps(u32 sectorsize, u32 nodesize)
अणु
	काष्ठा btrfs_fs_info *fs_info;
	अचिन्हित दीर्घ *biपंचांगap = शून्य;
	काष्ठा extent_buffer *eb = शून्य;
	पूर्णांक ret;

	test_msg("running extent buffer bitmap tests");

	fs_info = btrfs_alloc_dummy_fs_info(nodesize, sectorsize);
	अगर (!fs_info) अणु
		test_std_err(TEST_ALLOC_FS_INFO);
		वापस -ENOMEM;
	पूर्ण

	biपंचांगap = kदो_स्मृति(nodesize, GFP_KERNEL);
	अगर (!biपंचांगap) अणु
		test_err("couldn't allocate test bitmap");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	eb = __alloc_dummy_extent_buffer(fs_info, 0, nodesize);
	अगर (!eb) अणु
		test_std_err(TEST_ALLOC_ROOT);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = __test_eb_biपंचांगaps(biपंचांगap, eb, nodesize);
	अगर (ret)
		जाओ out;

	मुक्त_extent_buffer(eb);

	/*
	 * Test again क्रम हाल where the tree block is sectorsize aligned but
	 * not nodesize aligned.
	 */
	eb = __alloc_dummy_extent_buffer(fs_info, sectorsize, nodesize);
	अगर (!eb) अणु
		test_std_err(TEST_ALLOC_ROOT);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = __test_eb_biपंचांगaps(biपंचांगap, eb, nodesize);
out:
	मुक्त_extent_buffer(eb);
	kमुक्त(biपंचांगap);
	btrfs_मुक्त_dummy_fs_info(fs_info);
	वापस ret;
पूर्ण

अटल पूर्णांक test_find_first_clear_extent_bit(व्योम)
अणु
	काष्ठा extent_io_tree tree;
	u64 start, end;
	पूर्णांक ret = -EINVAL;

	test_msg("running find_first_clear_extent_bit test");

	extent_io_tree_init(शून्य, &tree, IO_TREE_SELFTEST, शून्य);

	/* Test correct handling of empty tree */
	find_first_clear_extent_bit(&tree, 0, &start, &end, CHUNK_TRIMMED);
	अगर (start != 0 || end != -1) अणु
		test_err(
	"error getting a range from completely empty tree: start %llu end %llu",
			 start, end);
		जाओ out;
	पूर्ण
	/*
	 * Set 1M-4M alloc/discard and 32M-64M thus leaving a hole between
	 * 4M-32M
	 */
	set_extent_bits(&tree, SZ_1M, SZ_4M - 1,
			CHUNK_TRIMMED | CHUNK_ALLOCATED);

	find_first_clear_extent_bit(&tree, SZ_512K, &start, &end,
				    CHUNK_TRIMMED | CHUNK_ALLOCATED);

	अगर (start != 0 || end != SZ_1M - 1) अणु
		test_err("error finding beginning range: start %llu end %llu",
			 start, end);
		जाओ out;
	पूर्ण

	/* Now add 32M-64M so that we have a hole between 4M-32M */
	set_extent_bits(&tree, SZ_32M, SZ_64M - 1,
			CHUNK_TRIMMED | CHUNK_ALLOCATED);

	/*
	 * Request first hole starting at 12M, we should get 4M-32M
	 */
	find_first_clear_extent_bit(&tree, 12 * SZ_1M, &start, &end,
				    CHUNK_TRIMMED | CHUNK_ALLOCATED);

	अगर (start != SZ_4M || end != SZ_32M - 1) अणु
		test_err("error finding trimmed range: start %llu end %llu",
			 start, end);
		जाओ out;
	पूर्ण

	/*
	 * Search in the middle of allocated range, should get the next one
	 * available, which happens to be unallocated -> 4M-32M
	 */
	find_first_clear_extent_bit(&tree, SZ_2M, &start, &end,
				    CHUNK_TRIMMED | CHUNK_ALLOCATED);

	अगर (start != SZ_4M || end != SZ_32M - 1) अणु
		test_err("error finding next unalloc range: start %llu end %llu",
			 start, end);
		जाओ out;
	पूर्ण

	/*
	 * Set 64M-72M with CHUNK_ALLOC flag, then search क्रम CHUNK_TRIMMED flag
	 * being unset in this range, we should get the entry in range 64M-72M
	 */
	set_extent_bits(&tree, SZ_64M, SZ_64M + SZ_8M - 1, CHUNK_ALLOCATED);
	find_first_clear_extent_bit(&tree, SZ_64M + SZ_1M, &start, &end,
				    CHUNK_TRIMMED);

	अगर (start != SZ_64M || end != SZ_64M + SZ_8M - 1) अणु
		test_err("error finding exact range: start %llu end %llu",
			 start, end);
		जाओ out;
	पूर्ण

	find_first_clear_extent_bit(&tree, SZ_64M - SZ_8M, &start, &end,
				    CHUNK_TRIMMED);

	/*
	 * Search in the middle of set range whose immediate neighbour करोesn't
	 * have the bits set so it must be वापसed
	 */
	अगर (start != SZ_64M || end != SZ_64M + SZ_8M - 1) अणु
		test_err("error finding next alloc range: start %llu end %llu",
			 start, end);
		जाओ out;
	पूर्ण

	/*
	 * Search beyond any known range, shall वापस after last known range
	 * and end should be -1
	 */
	find_first_clear_extent_bit(&tree, -1, &start, &end, CHUNK_TRIMMED);
	अगर (start != SZ_64M + SZ_8M || end != -1) अणु
		test_err(
		"error handling beyond end of range search: start %llu end %llu",
			start, end);
		जाओ out;
	पूर्ण

	ret = 0;
out:
	clear_extent_bits(&tree, 0, (u64)-1, CHUNK_TRIMMED | CHUNK_ALLOCATED);

	वापस ret;
पूर्ण

पूर्णांक btrfs_test_extent_io(u32 sectorsize, u32 nodesize)
अणु
	पूर्णांक ret;

	test_msg("running extent I/O tests");

	ret = test_find_delalloc(sectorsize);
	अगर (ret)
		जाओ out;

	ret = test_find_first_clear_extent_bit();
	अगर (ret)
		जाओ out;

	ret = test_eb_biपंचांगaps(sectorsize, nodesize);
out:
	वापस ret;
पूर्ण
