<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/prime_numbers.h>

#समावेश "../i915_selftest.h"
#समावेश "i915_random.h"

अटल व्योम __igt_dump_block(काष्ठा i915_buddy_mm *mm,
			     काष्ठा i915_buddy_block *block,
			     bool buddy)
अणु
	pr_err("block info: header=%llx, state=%u, order=%d, offset=%llx size=%llx root=%s buddy=%s\n",
	       block->header,
	       i915_buddy_block_state(block),
	       i915_buddy_block_order(block),
	       i915_buddy_block_offset(block),
	       i915_buddy_block_size(mm, block),
	       yesno(!block->parent),
	       yesno(buddy));
पूर्ण

अटल व्योम igt_dump_block(काष्ठा i915_buddy_mm *mm,
			   काष्ठा i915_buddy_block *block)
अणु
	काष्ठा i915_buddy_block *buddy;

	__igt_dump_block(mm, block, false);

	buddy = get_buddy(block);
	अगर (buddy)
		__igt_dump_block(mm, buddy, true);
पूर्ण

अटल पूर्णांक igt_check_block(काष्ठा i915_buddy_mm *mm,
			   काष्ठा i915_buddy_block *block)
अणु
	काष्ठा i915_buddy_block *buddy;
	अचिन्हित पूर्णांक block_state;
	u64 block_size;
	u64 offset;
	पूर्णांक err = 0;

	block_state = i915_buddy_block_state(block);

	अगर (block_state != I915_BUDDY_ALLOCATED &&
	    block_state != I915_BUDDY_FREE &&
	    block_state != I915_BUDDY_SPLIT) अणु
		pr_err("block state mismatch\n");
		err = -EINVAL;
	पूर्ण

	block_size = i915_buddy_block_size(mm, block);
	offset = i915_buddy_block_offset(block);

	अगर (block_size < mm->chunk_size) अणु
		pr_err("block size smaller than min size\n");
		err = -EINVAL;
	पूर्ण

	अगर (!is_घातer_of_2(block_size)) अणु
		pr_err("block size not power of two\n");
		err = -EINVAL;
	पूर्ण

	अगर (!IS_ALIGNED(block_size, mm->chunk_size)) अणु
		pr_err("block size not aligned to min size\n");
		err = -EINVAL;
	पूर्ण

	अगर (!IS_ALIGNED(offset, mm->chunk_size)) अणु
		pr_err("block offset not aligned to min size\n");
		err = -EINVAL;
	पूर्ण

	अगर (!IS_ALIGNED(offset, block_size)) अणु
		pr_err("block offset not aligned to block size\n");
		err = -EINVAL;
	पूर्ण

	buddy = get_buddy(block);

	अगर (!buddy && block->parent) अणु
		pr_err("buddy has gone fishing\n");
		err = -EINVAL;
	पूर्ण

	अगर (buddy) अणु
		अगर (i915_buddy_block_offset(buddy) != (offset ^ block_size)) अणु
			pr_err("buddy has wrong offset\n");
			err = -EINVAL;
		पूर्ण

		अगर (i915_buddy_block_size(mm, buddy) != block_size) अणु
			pr_err("buddy size mismatch\n");
			err = -EINVAL;
		पूर्ण

		अगर (i915_buddy_block_state(buddy) == block_state &&
		    block_state == I915_BUDDY_FREE) अणु
			pr_err("block and its buddy are free\n");
			err = -EINVAL;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक igt_check_blocks(काष्ठा i915_buddy_mm *mm,
			    काष्ठा list_head *blocks,
			    u64 expected_size,
			    bool is_contiguous)
अणु
	काष्ठा i915_buddy_block *block;
	काष्ठा i915_buddy_block *prev;
	u64 total;
	पूर्णांक err = 0;

	block = शून्य;
	prev = शून्य;
	total = 0;

	list_क्रम_each_entry(block, blocks, link) अणु
		err = igt_check_block(mm, block);

		अगर (!i915_buddy_block_is_allocated(block)) अणु
			pr_err("block not allocated\n"),
			err = -EINVAL;
		पूर्ण

		अगर (is_contiguous && prev) अणु
			u64 prev_block_size;
			u64 prev_offset;
			u64 offset;

			prev_offset = i915_buddy_block_offset(prev);
			prev_block_size = i915_buddy_block_size(mm, prev);
			offset = i915_buddy_block_offset(block);

			अगर (offset != (prev_offset + prev_block_size)) अणु
				pr_err("block offset mismatch\n");
				err = -EINVAL;
			पूर्ण
		पूर्ण

		अगर (err)
			अवरोध;

		total += i915_buddy_block_size(mm, block);
		prev = block;
	पूर्ण

	अगर (!err) अणु
		अगर (total != expected_size) अणु
			pr_err("size mismatch, expected=%llx, found=%llx\n",
			       expected_size, total);
			err = -EINVAL;
		पूर्ण
		वापस err;
	पूर्ण

	अगर (prev) अणु
		pr_err("prev block, dump:\n");
		igt_dump_block(mm, prev);
	पूर्ण

	अगर (block) अणु
		pr_err("bad block, dump:\n");
		igt_dump_block(mm, block);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक igt_check_mm(काष्ठा i915_buddy_mm *mm)
अणु
	काष्ठा i915_buddy_block *root;
	काष्ठा i915_buddy_block *prev;
	अचिन्हित पूर्णांक i;
	u64 total;
	पूर्णांक err = 0;

	अगर (!mm->n_roots) अणु
		pr_err("n_roots is zero\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mm->n_roots != hweight64(mm->size)) अणु
		pr_err("n_roots mismatch, n_roots=%u, expected=%lu\n",
		       mm->n_roots, hweight64(mm->size));
		वापस -EINVAL;
	पूर्ण

	root = शून्य;
	prev = शून्य;
	total = 0;

	क्रम (i = 0; i < mm->n_roots; ++i) अणु
		काष्ठा i915_buddy_block *block;
		अचिन्हित पूर्णांक order;

		root = mm->roots[i];
		अगर (!root) अणु
			pr_err("root(%u) is NULL\n", i);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		err = igt_check_block(mm, root);

		अगर (!i915_buddy_block_is_मुक्त(root)) अणु
			pr_err("root not free\n");
			err = -EINVAL;
		पूर्ण

		order = i915_buddy_block_order(root);

		अगर (!i) अणु
			अगर (order != mm->max_order) अणु
				pr_err("max order root missing\n");
				err = -EINVAL;
			पूर्ण
		पूर्ण

		अगर (prev) अणु
			u64 prev_block_size;
			u64 prev_offset;
			u64 offset;

			prev_offset = i915_buddy_block_offset(prev);
			prev_block_size = i915_buddy_block_size(mm, prev);
			offset = i915_buddy_block_offset(root);

			अगर (offset != (prev_offset + prev_block_size)) अणु
				pr_err("root offset mismatch\n");
				err = -EINVAL;
			पूर्ण
		पूर्ण

		block = list_first_entry_or_null(&mm->मुक्त_list[order],
						 काष्ठा i915_buddy_block,
						 link);
		अगर (block != root) अणु
			pr_err("root mismatch at order=%u\n", order);
			err = -EINVAL;
		पूर्ण

		अगर (err)
			अवरोध;

		prev = root;
		total += i915_buddy_block_size(mm, root);
	पूर्ण

	अगर (!err) अणु
		अगर (total != mm->size) अणु
			pr_err("expected mm size=%llx, found=%llx\n", mm->size,
			       total);
			err = -EINVAL;
		पूर्ण
		वापस err;
	पूर्ण

	अगर (prev) अणु
		pr_err("prev root(%u), dump:\n", i - 1);
		igt_dump_block(mm, prev);
	पूर्ण

	अगर (root) अणु
		pr_err("bad root(%u), dump:\n", i);
		igt_dump_block(mm, root);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम igt_mm_config(u64 *size, u64 *chunk_size)
अणु
	I915_RND_STATE(prng);
	u32 s, ms;

	/* Nothing fancy, just try to get an पूर्णांकeresting bit pattern */

	pअक्रमom_seed_state(&prng, i915_selftest.अक्रमom_seed);

	/* Let size be a अक्रमom number of pages up to 8 GB (2M pages) */
	s = 1 + i915_pअक्रमom_u32_max_state((BIT(33 - 12)) - 1, &prng);
	/* Let the chunk size be a अक्रमom घातer of 2 less than size */
	ms = BIT(i915_pअक्रमom_u32_max_state(ilog2(s), &prng));
	/* Round size करोwn to the chunk size */
	s &= -ms;

	/* Convert from pages to bytes */
	*chunk_size = (u64)ms << 12;
	*size = (u64)s << 12;
पूर्ण

अटल पूर्णांक igt_buddy_alloc_smoke(व्योम *arg)
अणु
	काष्ठा i915_buddy_mm mm;
	IGT_TIMEOUT(end_समय);
	I915_RND_STATE(prng);
	u64 chunk_size;
	u64 mm_size;
	पूर्णांक *order;
	पूर्णांक err, i;

	igt_mm_config(&mm_size, &chunk_size);

	pr_info("buddy_init with size=%llx, chunk_size=%llx\n", mm_size, chunk_size);

	err = i915_buddy_init(&mm, mm_size, chunk_size);
	अगर (err) अणु
		pr_err("buddy_init failed(%d)\n", err);
		वापस err;
	पूर्ण

	order = i915_अक्रमom_order(mm.max_order + 1, &prng);
	अगर (!order)
		जाओ out_fini;

	क्रम (i = 0; i <= mm.max_order; ++i) अणु
		काष्ठा i915_buddy_block *block;
		पूर्णांक max_order = order[i];
		bool समयout = false;
		LIST_HEAD(blocks);
		पूर्णांक order;
		u64 total;

		err = igt_check_mm(&mm);
		अगर (err) अणु
			pr_err("pre-mm check failed, abort\n");
			अवरोध;
		पूर्ण

		pr_info("filling from max_order=%u\n", max_order);

		order = max_order;
		total = 0;

		करो अणु
retry:
			block = i915_buddy_alloc(&mm, order);
			अगर (IS_ERR(block)) अणु
				err = PTR_ERR(block);
				अगर (err == -ENOMEM) अणु
					pr_info("buddy_alloc hit -ENOMEM with order=%d\n",
						order);
				पूर्ण अन्यथा अणु
					अगर (order--) अणु
						err = 0;
						जाओ retry;
					पूर्ण

					pr_err("buddy_alloc with order=%d failed(%d)\n",
					       order, err);
				पूर्ण

				अवरोध;
			पूर्ण

			list_add_tail(&block->link, &blocks);

			अगर (i915_buddy_block_order(block) != order) अणु
				pr_err("buddy_alloc order mismatch\n");
				err = -EINVAL;
				अवरोध;
			पूर्ण

			total += i915_buddy_block_size(&mm, block);

			अगर (__igt_समयout(end_समय, शून्य)) अणु
				समयout = true;
				अवरोध;
			पूर्ण
		पूर्ण जबतक (total < mm.size);

		अगर (!err)
			err = igt_check_blocks(&mm, &blocks, total, false);

		i915_buddy_मुक्त_list(&mm, &blocks);

		अगर (!err) अणु
			err = igt_check_mm(&mm);
			अगर (err)
				pr_err("post-mm check failed\n");
		पूर्ण

		अगर (err || समयout)
			अवरोध;

		cond_resched();
	पूर्ण

	अगर (err == -ENOMEM)
		err = 0;

	kमुक्त(order);
out_fini:
	i915_buddy_fini(&mm);

	वापस err;
पूर्ण

अटल पूर्णांक igt_buddy_alloc_pessimistic(व्योम *arg)
अणु
	स्थिर अचिन्हित पूर्णांक max_order = 16;
	काष्ठा i915_buddy_block *block, *bn;
	काष्ठा i915_buddy_mm mm;
	अचिन्हित पूर्णांक order;
	LIST_HEAD(blocks);
	पूर्णांक err;

	/*
	 * Create a pot-sized mm, then allocate one of each possible
	 * order within. This should leave the mm with exactly one
	 * page left.
	 */

	err = i915_buddy_init(&mm, PAGE_SIZE << max_order, PAGE_SIZE);
	अगर (err) अणु
		pr_err("buddy_init failed(%d)\n", err);
		वापस err;
	पूर्ण
	GEM_BUG_ON(mm.max_order != max_order);

	क्रम (order = 0; order < max_order; order++) अणु
		block = i915_buddy_alloc(&mm, order);
		अगर (IS_ERR(block)) अणु
			pr_info("buddy_alloc hit -ENOMEM with order=%d\n",
				order);
			err = PTR_ERR(block);
			जाओ err;
		पूर्ण

		list_add_tail(&block->link, &blocks);
	पूर्ण

	/* And now the last reमुख्यing block available */
	block = i915_buddy_alloc(&mm, 0);
	अगर (IS_ERR(block)) अणु
		pr_info("buddy_alloc hit -ENOMEM on final alloc\n");
		err = PTR_ERR(block);
		जाओ err;
	पूर्ण
	list_add_tail(&block->link, &blocks);

	/* Should be completely full! */
	क्रम (order = max_order; order--; ) अणु
		block = i915_buddy_alloc(&mm, order);
		अगर (!IS_ERR(block)) अणु
			pr_info("buddy_alloc unexpectedly succeeded at order %d, it should be full!",
				order);
			list_add_tail(&block->link, &blocks);
			err = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	block = list_last_entry(&blocks, typeof(*block), link);
	list_del(&block->link);
	i915_buddy_मुक्त(&mm, block);

	/* As we मुक्त in increasing size, we make available larger blocks */
	order = 1;
	list_क्रम_each_entry_safe(block, bn, &blocks, link) अणु
		list_del(&block->link);
		i915_buddy_मुक्त(&mm, block);

		block = i915_buddy_alloc(&mm, order);
		अगर (IS_ERR(block)) अणु
			pr_info("buddy_alloc (realloc) hit -ENOMEM with order=%d\n",
				order);
			err = PTR_ERR(block);
			जाओ err;
		पूर्ण
		i915_buddy_मुक्त(&mm, block);
		order++;
	पूर्ण

	/* To confirm, now the whole mm should be available */
	block = i915_buddy_alloc(&mm, max_order);
	अगर (IS_ERR(block)) अणु
		pr_info("buddy_alloc (realloc) hit -ENOMEM with order=%d\n",
			max_order);
		err = PTR_ERR(block);
		जाओ err;
	पूर्ण
	i915_buddy_मुक्त(&mm, block);

err:
	i915_buddy_मुक्त_list(&mm, &blocks);
	i915_buddy_fini(&mm);
	वापस err;
पूर्ण

अटल पूर्णांक igt_buddy_alloc_optimistic(व्योम *arg)
अणु
	स्थिर पूर्णांक max_order = 16;
	काष्ठा i915_buddy_block *block;
	काष्ठा i915_buddy_mm mm;
	LIST_HEAD(blocks);
	पूर्णांक order;
	पूर्णांक err;

	/*
	 * Create a mm with one block of each order available, and
	 * try to allocate them all.
	 */

	err = i915_buddy_init(&mm,
			      PAGE_SIZE * ((1 << (max_order + 1)) - 1),
			      PAGE_SIZE);
	अगर (err) अणु
		pr_err("buddy_init failed(%d)\n", err);
		वापस err;
	पूर्ण
	GEM_BUG_ON(mm.max_order != max_order);

	क्रम (order = 0; order <= max_order; order++) अणु
		block = i915_buddy_alloc(&mm, order);
		अगर (IS_ERR(block)) अणु
			pr_info("buddy_alloc hit -ENOMEM with order=%d\n",
				order);
			err = PTR_ERR(block);
			जाओ err;
		पूर्ण

		list_add_tail(&block->link, &blocks);
	पूर्ण

	/* Should be completely full! */
	block = i915_buddy_alloc(&mm, 0);
	अगर (!IS_ERR(block)) अणु
		pr_info("buddy_alloc unexpectedly succeeded, it should be full!");
		list_add_tail(&block->link, &blocks);
		err = -EINVAL;
		जाओ err;
	पूर्ण

err:
	i915_buddy_मुक्त_list(&mm, &blocks);
	i915_buddy_fini(&mm);
	वापस err;
पूर्ण

अटल पूर्णांक igt_buddy_alloc_pathological(व्योम *arg)
अणु
	स्थिर पूर्णांक max_order = 16;
	काष्ठा i915_buddy_block *block;
	काष्ठा i915_buddy_mm mm;
	LIST_HEAD(blocks);
	LIST_HEAD(holes);
	पूर्णांक order, top;
	पूर्णांक err;

	/*
	 * Create a pot-sized mm, then allocate one of each possible
	 * order within. This should leave the mm with exactly one
	 * page left. Free the largest block, then whittle करोwn again.
	 * Eventually we will have a fully 50% fragmented mm.
	 */

	err = i915_buddy_init(&mm, PAGE_SIZE << max_order, PAGE_SIZE);
	अगर (err) अणु
		pr_err("buddy_init failed(%d)\n", err);
		वापस err;
	पूर्ण
	GEM_BUG_ON(mm.max_order != max_order);

	क्रम (top = max_order; top; top--) अणु
		/* Make room by मुक्तing the largest allocated block */
		block = list_first_entry_or_null(&blocks, typeof(*block), link);
		अगर (block) अणु
			list_del(&block->link);
			i915_buddy_मुक्त(&mm, block);
		पूर्ण

		क्रम (order = top; order--; ) अणु
			block = i915_buddy_alloc(&mm, order);
			अगर (IS_ERR(block)) अणु
				pr_info("buddy_alloc hit -ENOMEM with order=%d, top=%d\n",
					order, top);
				err = PTR_ERR(block);
				जाओ err;
			पूर्ण
			list_add_tail(&block->link, &blocks);
		पूर्ण

		/* There should be one final page क्रम this sub-allocation */
		block = i915_buddy_alloc(&mm, 0);
		अगर (IS_ERR(block)) अणु
			pr_info("buddy_alloc hit -ENOMEM for hole\n");
			err = PTR_ERR(block);
			जाओ err;
		पूर्ण
		list_add_tail(&block->link, &holes);

		block = i915_buddy_alloc(&mm, top);
		अगर (!IS_ERR(block)) अणु
			pr_info("buddy_alloc unexpectedly succeeded at top-order %d/%d, it should be full!",
				top, max_order);
			list_add_tail(&block->link, &blocks);
			err = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	i915_buddy_मुक्त_list(&mm, &holes);

	/* Nothing larger than blocks of chunk_size now available */
	क्रम (order = 1; order <= max_order; order++) अणु
		block = i915_buddy_alloc(&mm, order);
		अगर (!IS_ERR(block)) अणु
			pr_info("buddy_alloc unexpectedly succeeded at order %d, it should be full!",
				order);
			list_add_tail(&block->link, &blocks);
			err = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

err:
	list_splice_tail(&holes, &blocks);
	i915_buddy_मुक्त_list(&mm, &blocks);
	i915_buddy_fini(&mm);
	वापस err;
पूर्ण

अटल पूर्णांक igt_buddy_alloc_range(व्योम *arg)
अणु
	काष्ठा i915_buddy_mm mm;
	अचिन्हित दीर्घ page_num;
	LIST_HEAD(blocks);
	u64 chunk_size;
	u64 offset;
	u64 size;
	u64 rem;
	पूर्णांक err;

	igt_mm_config(&size, &chunk_size);

	pr_info("buddy_init with size=%llx, chunk_size=%llx\n", size, chunk_size);

	err = i915_buddy_init(&mm, size, chunk_size);
	अगर (err) अणु
		pr_err("buddy_init failed(%d)\n", err);
		वापस err;
	पूर्ण

	err = igt_check_mm(&mm);
	अगर (err) अणु
		pr_err("pre-mm check failed, abort, abort, abort!\n");
		जाओ err_fini;
	पूर्ण

	rem = mm.size;
	offset = 0;

	क्रम_each_prime_number_from(page_num, 1, अच_दीर्घ_उच्च - 1) अणु
		काष्ठा i915_buddy_block *block;
		LIST_HEAD(पंचांगp);

		size = min(page_num * mm.chunk_size, rem);

		err = i915_buddy_alloc_range(&mm, &पंचांगp, offset, size);
		अगर (err) अणु
			अगर (err == -ENOMEM) अणु
				pr_info("alloc_range hit -ENOMEM with size=%llx\n",
					size);
			पूर्ण अन्यथा अणु
				pr_err("alloc_range with offset=%llx, size=%llx failed(%d)\n",
				       offset, size, err);
			पूर्ण

			अवरोध;
		पूर्ण

		block = list_first_entry_or_null(&पंचांगp,
						 काष्ठा i915_buddy_block,
						 link);
		अगर (!block) अणु
			pr_err("alloc_range has no blocks\n");
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (i915_buddy_block_offset(block) != offset) अणु
			pr_err("alloc_range start offset mismatch, found=%llx, expected=%llx\n",
			       i915_buddy_block_offset(block), offset);
			err = -EINVAL;
		पूर्ण

		अगर (!err)
			err = igt_check_blocks(&mm, &पंचांगp, size, true);

		list_splice_tail(&पंचांगp, &blocks);

		अगर (err)
			अवरोध;

		offset += size;

		rem -= size;
		अगर (!rem)
			अवरोध;

		cond_resched();
	पूर्ण

	अगर (err == -ENOMEM)
		err = 0;

	i915_buddy_मुक्त_list(&mm, &blocks);

	अगर (!err) अणु
		err = igt_check_mm(&mm);
		अगर (err)
			pr_err("post-mm check failed\n");
	पूर्ण

err_fini:
	i915_buddy_fini(&mm);

	वापस err;
पूर्ण

अटल पूर्णांक igt_buddy_alloc_limit(व्योम *arg)
अणु
	काष्ठा i915_buddy_block *block;
	काष्ठा i915_buddy_mm mm;
	स्थिर u64 size = U64_MAX;
	पूर्णांक err;

	err = i915_buddy_init(&mm, size, PAGE_SIZE);
	अगर (err)
		वापस err;

	अगर (mm.max_order != I915_BUDDY_MAX_ORDER) अणु
		pr_err("mm.max_order(%d) != %d\n",
		       mm.max_order, I915_BUDDY_MAX_ORDER);
		err = -EINVAL;
		जाओ out_fini;
	पूर्ण

	block = i915_buddy_alloc(&mm, mm.max_order);
	अगर (IS_ERR(block)) अणु
		err = PTR_ERR(block);
		जाओ out_fini;
	पूर्ण

	अगर (i915_buddy_block_order(block) != mm.max_order) अणु
		pr_err("block order(%d) != %d\n",
		       i915_buddy_block_order(block), mm.max_order);
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	अगर (i915_buddy_block_size(&mm, block) !=
	    BIT_ULL(mm.max_order) * PAGE_SIZE) अणु
		pr_err("block size(%llu) != %llu\n",
		       i915_buddy_block_size(&mm, block),
		       BIT_ULL(mm.max_order) * PAGE_SIZE);
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	i915_buddy_मुक्त(&mm, block);
out_fini:
	i915_buddy_fini(&mm);
	वापस err;
पूर्ण

पूर्णांक i915_buddy_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_buddy_alloc_pessimistic),
		SUBTEST(igt_buddy_alloc_optimistic),
		SUBTEST(igt_buddy_alloc_pathological),
		SUBTEST(igt_buddy_alloc_smoke),
		SUBTEST(igt_buddy_alloc_range),
		SUBTEST(igt_buddy_alloc_limit),
	पूर्ण;

	वापस i915_subtests(tests, शून्य);
पूर्ण
