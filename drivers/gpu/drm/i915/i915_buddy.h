<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_BUDDY_H__
#घोषणा __I915_BUDDY_H__

#समावेश <linux/bitops.h>
#समावेश <linux/list.h>

काष्ठा i915_buddy_block अणु
#घोषणा I915_BUDDY_HEADER_OFFSET GENMASK_ULL(63, 12)
#घोषणा I915_BUDDY_HEADER_STATE  GENMASK_ULL(11, 10)
#घोषणा   I915_BUDDY_ALLOCATED	   (1 << 10)
#घोषणा   I915_BUDDY_FREE	   (2 << 10)
#घोषणा   I915_BUDDY_SPLIT	   (3 << 10)
/* Free to be used, अगर needed in the future */
#घोषणा I915_BUDDY_HEADER_UNUSED GENMASK_ULL(9, 6)
#घोषणा I915_BUDDY_HEADER_ORDER  GENMASK_ULL(5, 0)
	u64 header;

	काष्ठा i915_buddy_block *left;
	काष्ठा i915_buddy_block *right;
	काष्ठा i915_buddy_block *parent;

	व्योम *निजी; /* owned by creator */

	/*
	 * While the block is allocated by the user through i915_buddy_alloc*,
	 * the user has ownership of the link, क्रम example to मुख्यtain within
	 * a list, अगर so desired. As soon as the block is मुक्तd with
	 * i915_buddy_मुक्त* ownership is given back to the mm.
	 */
	काष्ठा list_head link;
	काष्ठा list_head पंचांगp_link;
पूर्ण;

/* Order-zero must be at least PAGE_SIZE */
#घोषणा I915_BUDDY_MAX_ORDER (63 - PAGE_SHIFT)

/*
 * Binary Buddy System.
 *
 * Locking should be handled by the user, a simple mutex around
 * i915_buddy_alloc* and i915_buddy_मुक्त* should suffice.
 */
काष्ठा i915_buddy_mm अणु
	/* Maपूर्णांकain a मुक्त list क्रम each order. */
	काष्ठा list_head *मुक्त_list;

	/*
	 * Maपूर्णांकain explicit binary tree(s) to track the allocation of the
	 * address space. This gives us a simple way of finding a buddy block
	 * and perक्रमming the potentially recursive merge step when मुक्तing a
	 * block.  Nodes are either allocated or मुक्त, in which हाल they will
	 * also exist on the respective मुक्त list.
	 */
	काष्ठा i915_buddy_block **roots;

	/*
	 * Anything from here is खुला, and reमुख्यs अटल क्रम the lअगरeसमय of
	 * the mm. Everything above is considered करो-not-touch.
	 */
	अचिन्हित पूर्णांक n_roots;
	अचिन्हित पूर्णांक max_order;

	/* Must be at least PAGE_SIZE */
	u64 chunk_size;
	u64 size;
पूर्ण;

अटल अंतरभूत u64
i915_buddy_block_offset(काष्ठा i915_buddy_block *block)
अणु
	वापस block->header & I915_BUDDY_HEADER_OFFSET;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
i915_buddy_block_order(काष्ठा i915_buddy_block *block)
अणु
	वापस block->header & I915_BUDDY_HEADER_ORDER;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
i915_buddy_block_state(काष्ठा i915_buddy_block *block)
अणु
	वापस block->header & I915_BUDDY_HEADER_STATE;
पूर्ण

अटल अंतरभूत bool
i915_buddy_block_is_allocated(काष्ठा i915_buddy_block *block)
अणु
	वापस i915_buddy_block_state(block) == I915_BUDDY_ALLOCATED;
पूर्ण

अटल अंतरभूत bool
i915_buddy_block_is_मुक्त(काष्ठा i915_buddy_block *block)
अणु
	वापस i915_buddy_block_state(block) == I915_BUDDY_FREE;
पूर्ण

अटल अंतरभूत bool
i915_buddy_block_is_split(काष्ठा i915_buddy_block *block)
अणु
	वापस i915_buddy_block_state(block) == I915_BUDDY_SPLIT;
पूर्ण

अटल अंतरभूत u64
i915_buddy_block_size(काष्ठा i915_buddy_mm *mm,
		      काष्ठा i915_buddy_block *block)
अणु
	वापस mm->chunk_size << i915_buddy_block_order(block);
पूर्ण

पूर्णांक i915_buddy_init(काष्ठा i915_buddy_mm *mm, u64 size, u64 chunk_size);

व्योम i915_buddy_fini(काष्ठा i915_buddy_mm *mm);

काष्ठा i915_buddy_block *
i915_buddy_alloc(काष्ठा i915_buddy_mm *mm, अचिन्हित पूर्णांक order);

पूर्णांक i915_buddy_alloc_range(काष्ठा i915_buddy_mm *mm,
			   काष्ठा list_head *blocks,
			   u64 start, u64 size);

व्योम i915_buddy_मुक्त(काष्ठा i915_buddy_mm *mm, काष्ठा i915_buddy_block *block);

व्योम i915_buddy_मुक्त_list(काष्ठा i915_buddy_mm *mm, काष्ठा list_head *objects);

#पूर्ण_अगर
