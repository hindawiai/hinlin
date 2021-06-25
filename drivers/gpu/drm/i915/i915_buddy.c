<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/kmemleak.h>
#समावेश <linux/slab.h>

#समावेश "i915_buddy.h"

#समावेश "i915_gem.h"
#समावेश "i915_globals.h"
#समावेश "i915_utils.h"

अटल काष्ठा i915_global_block अणु
	काष्ठा i915_global base;
	काष्ठा kmem_cache *slab_blocks;
पूर्ण global;

अटल व्योम i915_global_buddy_shrink(व्योम)
अणु
	kmem_cache_shrink(global.slab_blocks);
पूर्ण

अटल व्योम i915_global_buddy_निकास(व्योम)
अणु
	kmem_cache_destroy(global.slab_blocks);
पूर्ण

अटल काष्ठा i915_global_block global = अणु अणु
	.shrink = i915_global_buddy_shrink,
	.निकास = i915_global_buddy_निकास,
पूर्ण पूर्ण;

पूर्णांक __init i915_global_buddy_init(व्योम)
अणु
	global.slab_blocks = KMEM_CACHE(i915_buddy_block, SLAB_HWCACHE_ALIGN);
	अगर (!global.slab_blocks)
		वापस -ENOMEM;

	i915_global_रेजिस्टर(&global.base);
	वापस 0;
पूर्ण

अटल काष्ठा i915_buddy_block *i915_block_alloc(काष्ठा i915_buddy_block *parent,
						 अचिन्हित पूर्णांक order,
						 u64 offset)
अणु
	काष्ठा i915_buddy_block *block;

	GEM_BUG_ON(order > I915_BUDDY_MAX_ORDER);

	block = kmem_cache_zalloc(global.slab_blocks, GFP_KERNEL);
	अगर (!block)
		वापस शून्य;

	block->header = offset;
	block->header |= order;
	block->parent = parent;

	GEM_BUG_ON(block->header & I915_BUDDY_HEADER_UNUSED);
	वापस block;
पूर्ण

अटल व्योम i915_block_मुक्त(काष्ठा i915_buddy_block *block)
अणु
	kmem_cache_मुक्त(global.slab_blocks, block);
पूर्ण

अटल व्योम mark_allocated(काष्ठा i915_buddy_block *block)
अणु
	block->header &= ~I915_BUDDY_HEADER_STATE;
	block->header |= I915_BUDDY_ALLOCATED;

	list_del(&block->link);
पूर्ण

अटल व्योम mark_मुक्त(काष्ठा i915_buddy_mm *mm,
		      काष्ठा i915_buddy_block *block)
अणु
	block->header &= ~I915_BUDDY_HEADER_STATE;
	block->header |= I915_BUDDY_FREE;

	list_add(&block->link,
		 &mm->मुक्त_list[i915_buddy_block_order(block)]);
पूर्ण

अटल व्योम mark_split(काष्ठा i915_buddy_block *block)
अणु
	block->header &= ~I915_BUDDY_HEADER_STATE;
	block->header |= I915_BUDDY_SPLIT;

	list_del(&block->link);
पूर्ण

पूर्णांक i915_buddy_init(काष्ठा i915_buddy_mm *mm, u64 size, u64 chunk_size)
अणु
	अचिन्हित पूर्णांक i;
	u64 offset;

	अगर (size < chunk_size)
		वापस -EINVAL;

	अगर (chunk_size < PAGE_SIZE)
		वापस -EINVAL;

	अगर (!is_घातer_of_2(chunk_size))
		वापस -EINVAL;

	size = round_करोwn(size, chunk_size);

	mm->size = size;
	mm->chunk_size = chunk_size;
	mm->max_order = ilog2(size) - ilog2(chunk_size);

	GEM_BUG_ON(mm->max_order > I915_BUDDY_MAX_ORDER);

	mm->मुक्त_list = kदो_स्मृति_array(mm->max_order + 1,
				      माप(काष्ठा list_head),
				      GFP_KERNEL);
	अगर (!mm->मुक्त_list)
		वापस -ENOMEM;

	क्रम (i = 0; i <= mm->max_order; ++i)
		INIT_LIST_HEAD(&mm->मुक्त_list[i]);

	mm->n_roots = hweight64(size);

	mm->roots = kदो_स्मृति_array(mm->n_roots,
				  माप(काष्ठा i915_buddy_block *),
				  GFP_KERNEL);
	अगर (!mm->roots)
		जाओ out_मुक्त_list;

	offset = 0;
	i = 0;

	/*
	 * Split पूर्णांकo घातer-of-two blocks, in हाल we are given a size that is
	 * not itself a घातer-of-two.
	 */
	करो अणु
		काष्ठा i915_buddy_block *root;
		अचिन्हित पूर्णांक order;
		u64 root_size;

		root_size = roundकरोwn_घात_of_two(size);
		order = ilog2(root_size) - ilog2(chunk_size);

		root = i915_block_alloc(शून्य, order, offset);
		अगर (!root)
			जाओ out_मुक्त_roots;

		mark_मुक्त(mm, root);

		GEM_BUG_ON(i > mm->max_order);
		GEM_BUG_ON(i915_buddy_block_size(mm, root) < chunk_size);

		mm->roots[i] = root;

		offset += root_size;
		size -= root_size;
		i++;
	पूर्ण जबतक (size);

	वापस 0;

out_मुक्त_roots:
	जबतक (i--)
		i915_block_मुक्त(mm->roots[i]);
	kमुक्त(mm->roots);
out_मुक्त_list:
	kमुक्त(mm->मुक्त_list);
	वापस -ENOMEM;
पूर्ण

व्योम i915_buddy_fini(काष्ठा i915_buddy_mm *mm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mm->n_roots; ++i) अणु
		GEM_WARN_ON(!i915_buddy_block_is_मुक्त(mm->roots[i]));
		i915_block_मुक्त(mm->roots[i]);
	पूर्ण

	kमुक्त(mm->roots);
	kमुक्त(mm->मुक्त_list);
पूर्ण

अटल पूर्णांक split_block(काष्ठा i915_buddy_mm *mm,
		       काष्ठा i915_buddy_block *block)
अणु
	अचिन्हित पूर्णांक block_order = i915_buddy_block_order(block) - 1;
	u64 offset = i915_buddy_block_offset(block);

	GEM_BUG_ON(!i915_buddy_block_is_मुक्त(block));
	GEM_BUG_ON(!i915_buddy_block_order(block));

	block->left = i915_block_alloc(block, block_order, offset);
	अगर (!block->left)
		वापस -ENOMEM;

	block->right = i915_block_alloc(block, block_order,
					offset + (mm->chunk_size << block_order));
	अगर (!block->right) अणु
		i915_block_मुक्त(block->left);
		वापस -ENOMEM;
	पूर्ण

	mark_मुक्त(mm, block->left);
	mark_मुक्त(mm, block->right);

	mark_split(block);

	वापस 0;
पूर्ण

अटल काष्ठा i915_buddy_block *
get_buddy(काष्ठा i915_buddy_block *block)
अणु
	काष्ठा i915_buddy_block *parent;

	parent = block->parent;
	अगर (!parent)
		वापस शून्य;

	अगर (parent->left == block)
		वापस parent->right;

	वापस parent->left;
पूर्ण

अटल व्योम __i915_buddy_मुक्त(काष्ठा i915_buddy_mm *mm,
			      काष्ठा i915_buddy_block *block)
अणु
	काष्ठा i915_buddy_block *parent;

	जबतक ((parent = block->parent)) अणु
		काष्ठा i915_buddy_block *buddy;

		buddy = get_buddy(block);

		अगर (!i915_buddy_block_is_मुक्त(buddy))
			अवरोध;

		list_del(&buddy->link);

		i915_block_मुक्त(block);
		i915_block_मुक्त(buddy);

		block = parent;
	पूर्ण

	mark_मुक्त(mm, block);
पूर्ण

व्योम i915_buddy_मुक्त(काष्ठा i915_buddy_mm *mm,
		     काष्ठा i915_buddy_block *block)
अणु
	GEM_BUG_ON(!i915_buddy_block_is_allocated(block));
	__i915_buddy_मुक्त(mm, block);
पूर्ण

व्योम i915_buddy_मुक्त_list(काष्ठा i915_buddy_mm *mm, काष्ठा list_head *objects)
अणु
	काष्ठा i915_buddy_block *block, *on;

	list_क्रम_each_entry_safe(block, on, objects, link) अणु
		i915_buddy_मुक्त(mm, block);
		cond_resched();
	पूर्ण
	INIT_LIST_HEAD(objects);
पूर्ण

/*
 * Allocate घातer-of-two block. The order value here translates to:
 *
 *   0 = 2^0 * mm->chunk_size
 *   1 = 2^1 * mm->chunk_size
 *   2 = 2^2 * mm->chunk_size
 *   ...
 */
काष्ठा i915_buddy_block *
i915_buddy_alloc(काष्ठा i915_buddy_mm *mm, अचिन्हित पूर्णांक order)
अणु
	काष्ठा i915_buddy_block *block = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = order; i <= mm->max_order; ++i) अणु
		block = list_first_entry_or_null(&mm->मुक्त_list[i],
						 काष्ठा i915_buddy_block,
						 link);
		अगर (block)
			अवरोध;
	पूर्ण

	अगर (!block)
		वापस ERR_PTR(-ENOSPC);

	GEM_BUG_ON(!i915_buddy_block_is_मुक्त(block));

	जबतक (i != order) अणु
		err = split_block(mm, block);
		अगर (unlikely(err))
			जाओ out_मुक्त;

		/* Go low */
		block = block->left;
		i--;
	पूर्ण

	mark_allocated(block);
	kmemleak_update_trace(block);
	वापस block;

out_मुक्त:
	अगर (i != order)
		__i915_buddy_मुक्त(mm, block);
	वापस ERR_PTR(err);
पूर्ण

अटल अंतरभूत bool overlaps(u64 s1, u64 e1, u64 s2, u64 e2)
अणु
	वापस s1 <= e2 && e1 >= s2;
पूर्ण

अटल अंतरभूत bool contains(u64 s1, u64 e1, u64 s2, u64 e2)
अणु
	वापस s1 <= s2 && e1 >= e2;
पूर्ण

/*
 * Allocate range. Note that it's safe to chain together multiple alloc_ranges
 * with the same blocks list.
 *
 * Intended क्रम pre-allocating portions of the address space, क्रम example to
 * reserve a block क्रम the initial framebuffer or similar, hence the expectation
 * here is that i915_buddy_alloc() is still the मुख्य vehicle क्रम
 * allocations, so अगर that's not the हाल then the drm_mm range allocator is
 * probably a much better fit, and so you should probably go use that instead.
 */
पूर्णांक i915_buddy_alloc_range(काष्ठा i915_buddy_mm *mm,
			   काष्ठा list_head *blocks,
			   u64 start, u64 size)
अणु
	काष्ठा i915_buddy_block *block;
	काष्ठा i915_buddy_block *buddy;
	LIST_HEAD(allocated);
	LIST_HEAD(dfs);
	u64 end;
	पूर्णांक err;
	पूर्णांक i;

	अगर (size < mm->chunk_size)
		वापस -EINVAL;

	अगर (!IS_ALIGNED(size | start, mm->chunk_size))
		वापस -EINVAL;

	अगर (range_overflows(start, size, mm->size))
		वापस -EINVAL;

	क्रम (i = 0; i < mm->n_roots; ++i)
		list_add_tail(&mm->roots[i]->पंचांगp_link, &dfs);

	end = start + size - 1;

	करो अणु
		u64 block_start;
		u64 block_end;

		block = list_first_entry_or_null(&dfs,
						 काष्ठा i915_buddy_block,
						 पंचांगp_link);
		अगर (!block)
			अवरोध;

		list_del(&block->पंचांगp_link);

		block_start = i915_buddy_block_offset(block);
		block_end = block_start + i915_buddy_block_size(mm, block) - 1;

		अगर (!overlaps(start, end, block_start, block_end))
			जारी;

		अगर (i915_buddy_block_is_allocated(block)) अणु
			err = -ENOSPC;
			जाओ err_मुक्त;
		पूर्ण

		अगर (contains(start, end, block_start, block_end)) अणु
			अगर (!i915_buddy_block_is_मुक्त(block)) अणु
				err = -ENOSPC;
				जाओ err_मुक्त;
			पूर्ण

			mark_allocated(block);
			list_add_tail(&block->link, &allocated);
			जारी;
		पूर्ण

		अगर (!i915_buddy_block_is_split(block)) अणु
			err = split_block(mm, block);
			अगर (unlikely(err))
				जाओ err_unकरो;
		पूर्ण

		list_add(&block->right->पंचांगp_link, &dfs);
		list_add(&block->left->पंचांगp_link, &dfs);
	पूर्ण जबतक (1);

	list_splice_tail(&allocated, blocks);
	वापस 0;

err_unकरो:
	/*
	 * We really करोn't want to leave around a bunch of split blocks, since
	 * bigger is better, so make sure we merge everything back beक्रमe we
	 * मुक्त the allocated blocks.
	 */
	buddy = get_buddy(block);
	अगर (buddy &&
	    (i915_buddy_block_is_मुक्त(block) &&
	     i915_buddy_block_is_मुक्त(buddy)))
		__i915_buddy_मुक्त(mm, block);

err_मुक्त:
	i915_buddy_मुक्त_list(mm, &allocated);
	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/i915_buddy.c"
#पूर्ण_अगर
