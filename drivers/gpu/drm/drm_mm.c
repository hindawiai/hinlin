<शैली गुरु>
/**************************************************************************
 *
 * Copyright 2006 Tungsten Graphics, Inc., Bismarck, ND., USA.
 * Copyright 2016 Intel Corporation
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 **************************************************************************/

/*
 * Generic simple memory manager implementation. Intended to be used as a base
 * class implementation क्रम more advanced memory managers.
 *
 * Note that the algorithm used is quite simple and there might be substantial
 * perक्रमmance gains अगर a smarter मुक्त list is implemented. Currently it is
 * just an unordered stack of मुक्त regions. This could easily be improved अगर
 * an RB-tree is used instead. At least अगर we expect heavy fragmentation.
 *
 * Aligned allocations can also see improvement.
 *
 * Authors:
 * Thomas Hellstrथघm <thomas-at-tungstengraphics-करोt-com>
 */

#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerval_tree_generic.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/stacktrace.h>

#समावेश <drm/drm_mm.h>

/**
 * DOC: Overview
 *
 * drm_mm provides a simple range allocator. The drivers are मुक्त to use the
 * resource allocator from the linux core अगर it suits them, the upside of drm_mm
 * is that it's in the DRM core. Which means that it's easier to extend क्रम
 * some of the crazier special purpose needs of gpus.
 *
 * The मुख्य data काष्ठा is &drm_mm, allocations are tracked in &drm_mm_node.
 * Drivers are मुक्त to embed either of them पूर्णांकo their own suitable
 * dataकाष्ठाures. drm_mm itself will not करो any memory allocations of its own,
 * so अगर drivers choose not to embed nodes they need to still allocate them
 * themselves.
 *
 * The range allocator also supports reservation of pपुनः_स्मृतिated blocks. This is
 * useful क्रम taking over initial mode setting configurations from the firmware,
 * where an object needs to be created which exactly matches the firmware's
 * scanout target. As दीर्घ as the range is still मुक्त it can be inserted anyसमय
 * after the allocator is initialized, which helps with aव्योमing looped
 * dependencies in the driver load sequence.
 *
 * drm_mm मुख्यtains a stack of most recently मुक्तd holes, which of all
 * simplistic dataकाष्ठाures seems to be a fairly decent approach to clustering
 * allocations and aव्योमing too much fragmentation. This means मुक्त space
 * searches are O(num_holes). Given that all the fancy features drm_mm supports
 * something better would be fairly complex and since gfx thrashing is a fairly
 * steep clअगरf not a real concern. Removing a node again is O(1).
 *
 * drm_mm supports a few features: Alignment and range restrictions can be
 * supplied. Furthermore every &drm_mm_node has a color value (which is just an
 * opaque अचिन्हित दीर्घ) which in conjunction with a driver callback can be used
 * to implement sophisticated placement restrictions. The i915 DRM driver uses
 * this to implement guard pages between incompatible caching करोमुख्यs in the
 * graphics TT.
 *
 * Two behaviors are supported क्रम searching and allocating: bottom-up and
 * top-करोwn. The शेष is bottom-up. Top-करोwn allocation can be used अगर the
 * memory area has dअगरferent restrictions, or just to reduce fragmentation.
 *
 * Finally iteration helpers to walk all nodes and all holes are provided as are
 * some basic allocator dumpers क्रम debugging.
 *
 * Note that this range allocator is not thपढ़ो-safe, drivers need to protect
 * modअगरications with their own locking. The idea behind this is that क्रम a full
 * memory manager additional data needs to be रक्षित anyway, hence पूर्णांकernal
 * locking would be fully redundant.
 */

#अगर_घोषित CONFIG_DRM_DEBUG_MM
#समावेश <linux/stackdepot.h>

#घोषणा STACKDEPTH 32
#घोषणा BUFSZ 4096

अटल noअंतरभूत व्योम save_stack(काष्ठा drm_mm_node *node)
अणु
	अचिन्हित दीर्घ entries[STACKDEPTH];
	अचिन्हित पूर्णांक n;

	n = stack_trace_save(entries, ARRAY_SIZE(entries), 1);

	/* May be called under spinlock, so aव्योम sleeping */
	node->stack = stack_depot_save(entries, n, GFP_NOWAIT);
पूर्ण

अटल व्योम show_leaks(काष्ठा drm_mm *mm)
अणु
	काष्ठा drm_mm_node *node;
	अचिन्हित दीर्घ *entries;
	अचिन्हित पूर्णांक nr_entries;
	अक्षर *buf;

	buf = kदो_स्मृति(BUFSZ, GFP_KERNEL);
	अगर (!buf)
		वापस;

	list_क्रम_each_entry(node, drm_mm_nodes(mm), node_list) अणु
		अगर (!node->stack) अणु
			DRM_ERROR("node [%08llx + %08llx]: unknown owner\n",
				  node->start, node->size);
			जारी;
		पूर्ण

		nr_entries = stack_depot_fetch(node->stack, &entries);
		stack_trace_snprपूर्णांक(buf, BUFSZ, entries, nr_entries, 0);
		DRM_ERROR("node [%08llx + %08llx]: inserted at\n%s",
			  node->start, node->size, buf);
	पूर्ण

	kमुक्त(buf);
पूर्ण

#अघोषित STACKDEPTH
#अघोषित BUFSZ
#अन्यथा
अटल व्योम save_stack(काष्ठा drm_mm_node *node) अणु पूर्ण
अटल व्योम show_leaks(काष्ठा drm_mm *mm) अणु पूर्ण
#पूर्ण_अगर

#घोषणा START(node) ((node)->start)
#घोषणा LAST(node)  ((node)->start + (node)->size - 1)

INTERVAL_TREE_DEFINE(काष्ठा drm_mm_node, rb,
		     u64, __subtree_last,
		     START, LAST, अटल अंतरभूत, drm_mm_पूर्णांकerval_tree)

काष्ठा drm_mm_node *
__drm_mm_पूर्णांकerval_first(स्थिर काष्ठा drm_mm *mm, u64 start, u64 last)
अणु
	वापस drm_mm_पूर्णांकerval_tree_iter_first((काष्ठा rb_root_cached *)&mm->पूर्णांकerval_tree,
					       start, last) ?: (काष्ठा drm_mm_node *)&mm->head_node;
पूर्ण
EXPORT_SYMBOL(__drm_mm_पूर्णांकerval_first);

अटल व्योम drm_mm_पूर्णांकerval_tree_add_node(काष्ठा drm_mm_node *hole_node,
					  काष्ठा drm_mm_node *node)
अणु
	काष्ठा drm_mm *mm = hole_node->mm;
	काष्ठा rb_node **link, *rb;
	काष्ठा drm_mm_node *parent;
	bool lefपंचांगost;

	node->__subtree_last = LAST(node);

	अगर (drm_mm_node_allocated(hole_node)) अणु
		rb = &hole_node->rb;
		जबतक (rb) अणु
			parent = rb_entry(rb, काष्ठा drm_mm_node, rb);
			अगर (parent->__subtree_last >= node->__subtree_last)
				अवरोध;

			parent->__subtree_last = node->__subtree_last;
			rb = rb_parent(rb);
		पूर्ण

		rb = &hole_node->rb;
		link = &hole_node->rb.rb_right;
		lefपंचांगost = false;
	पूर्ण अन्यथा अणु
		rb = शून्य;
		link = &mm->पूर्णांकerval_tree.rb_root.rb_node;
		lefपंचांगost = true;
	पूर्ण

	जबतक (*link) अणु
		rb = *link;
		parent = rb_entry(rb, काष्ठा drm_mm_node, rb);
		अगर (parent->__subtree_last < node->__subtree_last)
			parent->__subtree_last = node->__subtree_last;
		अगर (node->start < parent->start) अणु
			link = &parent->rb.rb_left;
		पूर्ण अन्यथा अणु
			link = &parent->rb.rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	rb_link_node(&node->rb, rb, link);
	rb_insert_augmented_cached(&node->rb, &mm->पूर्णांकerval_tree, lefपंचांगost,
				   &drm_mm_पूर्णांकerval_tree_augment);
पूर्ण

#घोषणा HOLE_SIZE(NODE) ((NODE)->hole_size)
#घोषणा HOLE_ADDR(NODE) (__drm_mm_hole_node_start(NODE))

अटल u64 rb_to_hole_size(काष्ठा rb_node *rb)
अणु
	वापस rb_entry(rb, काष्ठा drm_mm_node, rb_hole_size)->hole_size;
पूर्ण

अटल व्योम insert_hole_size(काष्ठा rb_root_cached *root,
			     काष्ठा drm_mm_node *node)
अणु
	काष्ठा rb_node **link = &root->rb_root.rb_node, *rb = शून्य;
	u64 x = node->hole_size;
	bool first = true;

	जबतक (*link) अणु
		rb = *link;
		अगर (x > rb_to_hole_size(rb)) अणु
			link = &rb->rb_left;
		पूर्ण अन्यथा अणु
			link = &rb->rb_right;
			first = false;
		पूर्ण
	पूर्ण

	rb_link_node(&node->rb_hole_size, rb, link);
	rb_insert_color_cached(&node->rb_hole_size, root, first);
पूर्ण

RB_DECLARE_CALLBACKS_MAX(अटल, augment_callbacks,
			 काष्ठा drm_mm_node, rb_hole_addr,
			 u64, subtree_max_hole, HOLE_SIZE)

अटल व्योम insert_hole_addr(काष्ठा rb_root *root, काष्ठा drm_mm_node *node)
अणु
	काष्ठा rb_node **link = &root->rb_node, *rb_parent = शून्य;
	u64 start = HOLE_ADDR(node), subtree_max_hole = node->subtree_max_hole;
	काष्ठा drm_mm_node *parent;

	जबतक (*link) अणु
		rb_parent = *link;
		parent = rb_entry(rb_parent, काष्ठा drm_mm_node, rb_hole_addr);
		अगर (parent->subtree_max_hole < subtree_max_hole)
			parent->subtree_max_hole = subtree_max_hole;
		अगर (start < HOLE_ADDR(parent))
			link = &parent->rb_hole_addr.rb_left;
		अन्यथा
			link = &parent->rb_hole_addr.rb_right;
	पूर्ण

	rb_link_node(&node->rb_hole_addr, rb_parent, link);
	rb_insert_augmented(&node->rb_hole_addr, root, &augment_callbacks);
पूर्ण

अटल व्योम add_hole(काष्ठा drm_mm_node *node)
अणु
	काष्ठा drm_mm *mm = node->mm;

	node->hole_size =
		__drm_mm_hole_node_end(node) - __drm_mm_hole_node_start(node);
	node->subtree_max_hole = node->hole_size;
	DRM_MM_BUG_ON(!drm_mm_hole_follows(node));

	insert_hole_size(&mm->holes_size, node);
	insert_hole_addr(&mm->holes_addr, node);

	list_add(&node->hole_stack, &mm->hole_stack);
पूर्ण

अटल व्योम rm_hole(काष्ठा drm_mm_node *node)
अणु
	DRM_MM_BUG_ON(!drm_mm_hole_follows(node));

	list_del(&node->hole_stack);
	rb_erase_cached(&node->rb_hole_size, &node->mm->holes_size);
	rb_erase_augmented(&node->rb_hole_addr, &node->mm->holes_addr,
			   &augment_callbacks);
	node->hole_size = 0;
	node->subtree_max_hole = 0;

	DRM_MM_BUG_ON(drm_mm_hole_follows(node));
पूर्ण

अटल अंतरभूत काष्ठा drm_mm_node *rb_hole_माप_प्रकारo_node(काष्ठा rb_node *rb)
अणु
	वापस rb_entry_safe(rb, काष्ठा drm_mm_node, rb_hole_size);
पूर्ण

अटल अंतरभूत काष्ठा drm_mm_node *rb_hole_addr_to_node(काष्ठा rb_node *rb)
अणु
	वापस rb_entry_safe(rb, काष्ठा drm_mm_node, rb_hole_addr);
पूर्ण

अटल काष्ठा drm_mm_node *best_hole(काष्ठा drm_mm *mm, u64 size)
अणु
	काष्ठा rb_node *rb = mm->holes_size.rb_root.rb_node;
	काष्ठा drm_mm_node *best = शून्य;

	करो अणु
		काष्ठा drm_mm_node *node =
			rb_entry(rb, काष्ठा drm_mm_node, rb_hole_size);

		अगर (size <= node->hole_size) अणु
			best = node;
			rb = rb->rb_right;
		पूर्ण अन्यथा अणु
			rb = rb->rb_left;
		पूर्ण
	पूर्ण जबतक (rb);

	वापस best;
पूर्ण

अटल bool usable_hole_addr(काष्ठा rb_node *rb, u64 size)
अणु
	वापस rb && rb_hole_addr_to_node(rb)->subtree_max_hole >= size;
पूर्ण

अटल काष्ठा drm_mm_node *find_hole_addr(काष्ठा drm_mm *mm, u64 addr, u64 size)
अणु
	काष्ठा rb_node *rb = mm->holes_addr.rb_node;
	काष्ठा drm_mm_node *node = शून्य;

	जबतक (rb) अणु
		u64 hole_start;

		अगर (!usable_hole_addr(rb, size))
			अवरोध;

		node = rb_hole_addr_to_node(rb);
		hole_start = __drm_mm_hole_node_start(node);

		अगर (addr < hole_start)
			rb = node->rb_hole_addr.rb_left;
		अन्यथा अगर (addr > hole_start + node->hole_size)
			rb = node->rb_hole_addr.rb_right;
		अन्यथा
			अवरोध;
	पूर्ण

	वापस node;
पूर्ण

अटल काष्ठा drm_mm_node *
first_hole(काष्ठा drm_mm *mm,
	   u64 start, u64 end, u64 size,
	   क्रमागत drm_mm_insert_mode mode)
अणु
	चयन (mode) अणु
	शेष:
	हाल DRM_MM_INSERT_BEST:
		वापस best_hole(mm, size);

	हाल DRM_MM_INSERT_LOW:
		वापस find_hole_addr(mm, start, size);

	हाल DRM_MM_INSERT_HIGH:
		वापस find_hole_addr(mm, end, size);

	हाल DRM_MM_INSERT_EVICT:
		वापस list_first_entry_or_null(&mm->hole_stack,
						काष्ठा drm_mm_node,
						hole_stack);
	पूर्ण
पूर्ण

/**
 * DECLARE_NEXT_HOLE_ADDR - macro to declare next hole functions
 * @name: name of function to declare
 * @first: first rb member to traverse (either rb_left or rb_right).
 * @last: last rb member to traverse (either rb_right or rb_left).
 *
 * This macro declares a function to वापस the next hole of the addr rb tree.
 * While traversing the tree we take the searched size पूर्णांकo account and only
 * visit branches with potential big enough holes.
 */

#घोषणा DECLARE_NEXT_HOLE_ADDR(name, first, last)			\
अटल काष्ठा drm_mm_node *name(काष्ठा drm_mm_node *entry, u64 size)	\
अणु									\
	काष्ठा rb_node *parent, *node = &entry->rb_hole_addr;		\
									\
	अगर (!entry || RB_EMPTY_NODE(node))				\
		वापस शून्य;						\
									\
	अगर (usable_hole_addr(node->first, size)) अणु			\
		node = node->first;					\
		जबतक (usable_hole_addr(node->last, size))		\
			node = node->last;				\
		वापस rb_hole_addr_to_node(node);			\
	पूर्ण								\
									\
	जबतक ((parent = rb_parent(node)) && node == parent->first)	\
		node = parent;						\
									\
	वापस rb_hole_addr_to_node(parent);				\
पूर्ण

DECLARE_NEXT_HOLE_ADDR(next_hole_high_addr, rb_left, rb_right)
DECLARE_NEXT_HOLE_ADDR(next_hole_low_addr, rb_right, rb_left)

अटल काष्ठा drm_mm_node *
next_hole(काष्ठा drm_mm *mm,
	  काष्ठा drm_mm_node *node,
	  u64 size,
	  क्रमागत drm_mm_insert_mode mode)
अणु
	चयन (mode) अणु
	शेष:
	हाल DRM_MM_INSERT_BEST:
		वापस rb_hole_माप_प्रकारo_node(rb_prev(&node->rb_hole_size));

	हाल DRM_MM_INSERT_LOW:
		वापस next_hole_low_addr(node, size);

	हाल DRM_MM_INSERT_HIGH:
		वापस next_hole_high_addr(node, size);

	हाल DRM_MM_INSERT_EVICT:
		node = list_next_entry(node, hole_stack);
		वापस &node->hole_stack == &mm->hole_stack ? शून्य : node;
	पूर्ण
पूर्ण

/**
 * drm_mm_reserve_node - insert an pre-initialized node
 * @mm: drm_mm allocator to insert @node पूर्णांकo
 * @node: drm_mm_node to insert
 *
 * This functions inserts an alपढ़ोy set-up &drm_mm_node पूर्णांकo the allocator,
 * meaning that start, size and color must be set by the caller. All other
 * fields must be cleared to 0. This is useful to initialize the allocator with
 * pपुनः_स्मृतिated objects which must be set-up beक्रमe the range allocator can be
 * set-up, e.g. when taking over a firmware framebuffer.
 *
 * Returns:
 * 0 on success, -ENOSPC अगर there's no hole where @node is.
 */
पूर्णांक drm_mm_reserve_node(काष्ठा drm_mm *mm, काष्ठा drm_mm_node *node)
अणु
	काष्ठा drm_mm_node *hole;
	u64 hole_start, hole_end;
	u64 adj_start, adj_end;
	u64 end;

	end = node->start + node->size;
	अगर (unlikely(end <= node->start))
		वापस -ENOSPC;

	/* Find the relevant hole to add our node to */
	hole = find_hole_addr(mm, node->start, 0);
	अगर (!hole)
		वापस -ENOSPC;

	adj_start = hole_start = __drm_mm_hole_node_start(hole);
	adj_end = hole_end = hole_start + hole->hole_size;

	अगर (mm->color_adjust)
		mm->color_adjust(hole, node->color, &adj_start, &adj_end);

	अगर (adj_start > node->start || adj_end < end)
		वापस -ENOSPC;

	node->mm = mm;

	__set_bit(DRM_MM_NODE_ALLOCATED_BIT, &node->flags);
	list_add(&node->node_list, &hole->node_list);
	drm_mm_पूर्णांकerval_tree_add_node(hole, node);
	node->hole_size = 0;

	rm_hole(hole);
	अगर (node->start > hole_start)
		add_hole(hole);
	अगर (end < hole_end)
		add_hole(node);

	save_stack(node);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_mm_reserve_node);

अटल u64 rb_to_hole_size_or_zero(काष्ठा rb_node *rb)
अणु
	वापस rb ? rb_to_hole_size(rb) : 0;
पूर्ण

/**
 * drm_mm_insert_node_in_range - ranged search क्रम space and insert @node
 * @mm: drm_mm to allocate from
 * @node: pपुनः_स्मृतिate node to insert
 * @size: size of the allocation
 * @alignment: alignment of the allocation
 * @color: opaque tag value to use क्रम this node
 * @range_start: start of the allowed range क्रम this node
 * @range_end: end of the allowed range क्रम this node
 * @mode: fine-tune the allocation search and placement
 *
 * The pपुनः_स्मृतिated @node must be cleared to 0.
 *
 * Returns:
 * 0 on success, -ENOSPC अगर there's no suitable hole.
 */
पूर्णांक drm_mm_insert_node_in_range(काष्ठा drm_mm * स्थिर mm,
				काष्ठा drm_mm_node * स्थिर node,
				u64 size, u64 alignment,
				अचिन्हित दीर्घ color,
				u64 range_start, u64 range_end,
				क्रमागत drm_mm_insert_mode mode)
अणु
	काष्ठा drm_mm_node *hole;
	u64 reमुख्यder_mask;
	bool once;

	DRM_MM_BUG_ON(range_start > range_end);

	अगर (unlikely(size == 0 || range_end - range_start < size))
		वापस -ENOSPC;

	अगर (rb_to_hole_size_or_zero(rb_first_cached(&mm->holes_size)) < size)
		वापस -ENOSPC;

	अगर (alignment <= 1)
		alignment = 0;

	once = mode & DRM_MM_INSERT_ONCE;
	mode &= ~DRM_MM_INSERT_ONCE;

	reमुख्यder_mask = is_घातer_of_2(alignment) ? alignment - 1 : 0;
	क्रम (hole = first_hole(mm, range_start, range_end, size, mode);
	     hole;
	     hole = once ? शून्य : next_hole(mm, hole, size, mode)) अणु
		u64 hole_start = __drm_mm_hole_node_start(hole);
		u64 hole_end = hole_start + hole->hole_size;
		u64 adj_start, adj_end;
		u64 col_start, col_end;

		अगर (mode == DRM_MM_INSERT_LOW && hole_start >= range_end)
			अवरोध;

		अगर (mode == DRM_MM_INSERT_HIGH && hole_end <= range_start)
			अवरोध;

		col_start = hole_start;
		col_end = hole_end;
		अगर (mm->color_adjust)
			mm->color_adjust(hole, color, &col_start, &col_end);

		adj_start = max(col_start, range_start);
		adj_end = min(col_end, range_end);

		अगर (adj_end <= adj_start || adj_end - adj_start < size)
			जारी;

		अगर (mode == DRM_MM_INSERT_HIGH)
			adj_start = adj_end - size;

		अगर (alignment) अणु
			u64 rem;

			अगर (likely(reमुख्यder_mask))
				rem = adj_start & reमुख्यder_mask;
			अन्यथा
				भाग64_u64_rem(adj_start, alignment, &rem);
			अगर (rem) अणु
				adj_start -= rem;
				अगर (mode != DRM_MM_INSERT_HIGH)
					adj_start += alignment;

				अगर (adj_start < max(col_start, range_start) ||
				    min(col_end, range_end) - adj_start < size)
					जारी;

				अगर (adj_end <= adj_start ||
				    adj_end - adj_start < size)
					जारी;
			पूर्ण
		पूर्ण

		node->mm = mm;
		node->size = size;
		node->start = adj_start;
		node->color = color;
		node->hole_size = 0;

		__set_bit(DRM_MM_NODE_ALLOCATED_BIT, &node->flags);
		list_add(&node->node_list, &hole->node_list);
		drm_mm_पूर्णांकerval_tree_add_node(hole, node);

		rm_hole(hole);
		अगर (adj_start > hole_start)
			add_hole(hole);
		अगर (adj_start + size < hole_end)
			add_hole(node);

		save_stack(node);
		वापस 0;
	पूर्ण

	वापस -ENOSPC;
पूर्ण
EXPORT_SYMBOL(drm_mm_insert_node_in_range);

अटल अंतरभूत bool drm_mm_node_scanned_block(स्थिर काष्ठा drm_mm_node *node)
अणु
	वापस test_bit(DRM_MM_NODE_SCANNED_BIT, &node->flags);
पूर्ण

/**
 * drm_mm_हटाओ_node - Remove a memory node from the allocator.
 * @node: drm_mm_node to हटाओ
 *
 * This just हटाओs a node from its drm_mm allocator. The node करोes not need to
 * be cleared again beक्रमe it can be re-inserted पूर्णांकo this or any other drm_mm
 * allocator. It is a bug to call this function on a unallocated node.
 */
व्योम drm_mm_हटाओ_node(काष्ठा drm_mm_node *node)
अणु
	काष्ठा drm_mm *mm = node->mm;
	काष्ठा drm_mm_node *prev_node;

	DRM_MM_BUG_ON(!drm_mm_node_allocated(node));
	DRM_MM_BUG_ON(drm_mm_node_scanned_block(node));

	prev_node = list_prev_entry(node, node_list);

	अगर (drm_mm_hole_follows(node))
		rm_hole(node);

	drm_mm_पूर्णांकerval_tree_हटाओ(node, &mm->पूर्णांकerval_tree);
	list_del(&node->node_list);

	अगर (drm_mm_hole_follows(prev_node))
		rm_hole(prev_node);
	add_hole(prev_node);

	clear_bit_unlock(DRM_MM_NODE_ALLOCATED_BIT, &node->flags);
पूर्ण
EXPORT_SYMBOL(drm_mm_हटाओ_node);

/**
 * drm_mm_replace_node - move an allocation from @old to @new
 * @old: drm_mm_node to हटाओ from the allocator
 * @new: drm_mm_node which should inherit @old's allocation
 *
 * This is useful क्रम when drivers embed the drm_mm_node काष्ठाure and hence
 * can't move allocations by reassigning pointers. It's a combination of हटाओ
 * and insert with the guarantee that the allocation start will match.
 */
व्योम drm_mm_replace_node(काष्ठा drm_mm_node *old, काष्ठा drm_mm_node *new)
अणु
	काष्ठा drm_mm *mm = old->mm;

	DRM_MM_BUG_ON(!drm_mm_node_allocated(old));

	*new = *old;

	__set_bit(DRM_MM_NODE_ALLOCATED_BIT, &new->flags);
	list_replace(&old->node_list, &new->node_list);
	rb_replace_node_cached(&old->rb, &new->rb, &mm->पूर्णांकerval_tree);

	अगर (drm_mm_hole_follows(old)) अणु
		list_replace(&old->hole_stack, &new->hole_stack);
		rb_replace_node_cached(&old->rb_hole_size,
				       &new->rb_hole_size,
				       &mm->holes_size);
		rb_replace_node(&old->rb_hole_addr,
				&new->rb_hole_addr,
				&mm->holes_addr);
	पूर्ण

	clear_bit_unlock(DRM_MM_NODE_ALLOCATED_BIT, &old->flags);
पूर्ण
EXPORT_SYMBOL(drm_mm_replace_node);

/**
 * DOC: lru scan roster
 *
 * Very often GPUs need to have continuous allocations क्रम a given object. When
 * evicting objects to make space क्रम a new one it is thereक्रमe not most
 * efficient when we simply start to select all objects from the tail of an LRU
 * until there's a suitable hole: Especially क्रम big objects or nodes that
 * otherwise have special allocation स्थिरraपूर्णांकs there's a good chance we evict
 * lots of (smaller) objects unnecessarily.
 *
 * The DRM range allocator supports this use-हाल through the scanning
 * पूर्णांकerfaces. First a scan operation needs to be initialized with
 * drm_mm_scan_init() or drm_mm_scan_init_with_range(). The driver adds
 * objects to the roster, probably by walking an LRU list, but this can be
 * मुक्तly implemented. Eviction candiates are added using
 * drm_mm_scan_add_block() until a suitable hole is found or there are no
 * further evictable objects. Eviction roster metadata is tracked in &काष्ठा
 * drm_mm_scan.
 *
 * The driver must walk through all objects again in exactly the reverse
 * order to restore the allocator state. Note that जबतक the allocator is used
 * in the scan mode no other operation is allowed.
 *
 * Finally the driver evicts all objects selected (drm_mm_scan_हटाओ_block()
 * reported true) in the scan, and any overlapping nodes after color adjusपंचांगent
 * (drm_mm_scan_color_evict()). Adding and removing an object is O(1), and
 * since मुक्तing a node is also O(1) the overall complनिकासy is
 * O(scanned_objects). So like the मुक्त stack which needs to be walked beक्रमe a
 * scan operation even begins this is linear in the number of objects. It
 * करोesn't seem to hurt too badly.
 */

/**
 * drm_mm_scan_init_with_range - initialize range-restricted lru scanning
 * @scan: scan state
 * @mm: drm_mm to scan
 * @size: size of the allocation
 * @alignment: alignment of the allocation
 * @color: opaque tag value to use क्रम the allocation
 * @start: start of the allowed range क्रम the allocation
 * @end: end of the allowed range क्रम the allocation
 * @mode: fine-tune the allocation search and placement
 *
 * This simply sets up the scanning routines with the parameters क्रम the desired
 * hole.
 *
 * Warning:
 * As दीर्घ as the scan list is non-empty, no other operations than
 * adding/removing nodes to/from the scan list are allowed.
 */
व्योम drm_mm_scan_init_with_range(काष्ठा drm_mm_scan *scan,
				 काष्ठा drm_mm *mm,
				 u64 size,
				 u64 alignment,
				 अचिन्हित दीर्घ color,
				 u64 start,
				 u64 end,
				 क्रमागत drm_mm_insert_mode mode)
अणु
	DRM_MM_BUG_ON(start >= end);
	DRM_MM_BUG_ON(!size || size > end - start);
	DRM_MM_BUG_ON(mm->scan_active);

	scan->mm = mm;

	अगर (alignment <= 1)
		alignment = 0;

	scan->color = color;
	scan->alignment = alignment;
	scan->reमुख्यder_mask = is_घातer_of_2(alignment) ? alignment - 1 : 0;
	scan->size = size;
	scan->mode = mode;

	DRM_MM_BUG_ON(end <= start);
	scan->range_start = start;
	scan->range_end = end;

	scan->hit_start = U64_MAX;
	scan->hit_end = 0;
पूर्ण
EXPORT_SYMBOL(drm_mm_scan_init_with_range);

/**
 * drm_mm_scan_add_block - add a node to the scan list
 * @scan: the active drm_mm scanner
 * @node: drm_mm_node to add
 *
 * Add a node to the scan list that might be मुक्तd to make space क्रम the desired
 * hole.
 *
 * Returns:
 * True अगर a hole has been found, false otherwise.
 */
bool drm_mm_scan_add_block(काष्ठा drm_mm_scan *scan,
			   काष्ठा drm_mm_node *node)
अणु
	काष्ठा drm_mm *mm = scan->mm;
	काष्ठा drm_mm_node *hole;
	u64 hole_start, hole_end;
	u64 col_start, col_end;
	u64 adj_start, adj_end;

	DRM_MM_BUG_ON(node->mm != mm);
	DRM_MM_BUG_ON(!drm_mm_node_allocated(node));
	DRM_MM_BUG_ON(drm_mm_node_scanned_block(node));
	__set_bit(DRM_MM_NODE_SCANNED_BIT, &node->flags);
	mm->scan_active++;

	/* Remove this block from the node_list so that we enlarge the hole
	 * (distance between the end of our previous node and the start of
	 * or next), without poisoning the link so that we can restore it
	 * later in drm_mm_scan_हटाओ_block().
	 */
	hole = list_prev_entry(node, node_list);
	DRM_MM_BUG_ON(list_next_entry(hole, node_list) != node);
	__list_del_entry(&node->node_list);

	hole_start = __drm_mm_hole_node_start(hole);
	hole_end = __drm_mm_hole_node_end(hole);

	col_start = hole_start;
	col_end = hole_end;
	अगर (mm->color_adjust)
		mm->color_adjust(hole, scan->color, &col_start, &col_end);

	adj_start = max(col_start, scan->range_start);
	adj_end = min(col_end, scan->range_end);
	अगर (adj_end <= adj_start || adj_end - adj_start < scan->size)
		वापस false;

	अगर (scan->mode == DRM_MM_INSERT_HIGH)
		adj_start = adj_end - scan->size;

	अगर (scan->alignment) अणु
		u64 rem;

		अगर (likely(scan->reमुख्यder_mask))
			rem = adj_start & scan->reमुख्यder_mask;
		अन्यथा
			भाग64_u64_rem(adj_start, scan->alignment, &rem);
		अगर (rem) अणु
			adj_start -= rem;
			अगर (scan->mode != DRM_MM_INSERT_HIGH)
				adj_start += scan->alignment;
			अगर (adj_start < max(col_start, scan->range_start) ||
			    min(col_end, scan->range_end) - adj_start < scan->size)
				वापस false;

			अगर (adj_end <= adj_start ||
			    adj_end - adj_start < scan->size)
				वापस false;
		पूर्ण
	पूर्ण

	scan->hit_start = adj_start;
	scan->hit_end = adj_start + scan->size;

	DRM_MM_BUG_ON(scan->hit_start >= scan->hit_end);
	DRM_MM_BUG_ON(scan->hit_start < hole_start);
	DRM_MM_BUG_ON(scan->hit_end > hole_end);

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_mm_scan_add_block);

/**
 * drm_mm_scan_हटाओ_block - हटाओ a node from the scan list
 * @scan: the active drm_mm scanner
 * @node: drm_mm_node to हटाओ
 *
 * Nodes **must** be हटाओd in exactly the reverse order from the scan list as
 * they have been added (e.g. using list_add() as they are added and then
 * list_क्रम_each() over that eviction list to हटाओ), otherwise the पूर्णांकernal
 * state of the memory manager will be corrupted.
 *
 * When the scan list is empty, the selected memory nodes can be मुक्तd. An
 * immediately following drm_mm_insert_node_in_range_generic() or one of the
 * simpler versions of that function with !DRM_MM_SEARCH_BEST will then वापस
 * the just मुक्तd block (because it's at the top of the मुक्त_stack list).
 *
 * Returns:
 * True अगर this block should be evicted, false otherwise. Will always
 * वापस false when no hole has been found.
 */
bool drm_mm_scan_हटाओ_block(काष्ठा drm_mm_scan *scan,
			      काष्ठा drm_mm_node *node)
अणु
	काष्ठा drm_mm_node *prev_node;

	DRM_MM_BUG_ON(node->mm != scan->mm);
	DRM_MM_BUG_ON(!drm_mm_node_scanned_block(node));
	__clear_bit(DRM_MM_NODE_SCANNED_BIT, &node->flags);

	DRM_MM_BUG_ON(!node->mm->scan_active);
	node->mm->scan_active--;

	/* During drm_mm_scan_add_block() we decoupled this node leaving
	 * its poपूर्णांकers पूर्णांकact. Now that the caller is walking back aदीर्घ
	 * the eviction list we can restore this block पूर्णांकo its rightful
	 * place on the full node_list. To confirm that the caller is walking
	 * backwards correctly we check that prev_node->next == node->next,
	 * i.e. both believe the same node should be on the other side of the
	 * hole.
	 */
	prev_node = list_prev_entry(node, node_list);
	DRM_MM_BUG_ON(list_next_entry(prev_node, node_list) !=
		      list_next_entry(node, node_list));
	list_add(&node->node_list, &prev_node->node_list);

	वापस (node->start + node->size > scan->hit_start &&
		node->start < scan->hit_end);
पूर्ण
EXPORT_SYMBOL(drm_mm_scan_हटाओ_block);

/**
 * drm_mm_scan_color_evict - evict overlapping nodes on either side of hole
 * @scan: drm_mm scan with target hole
 *
 * After completing an eviction scan and removing the selected nodes, we may
 * need to हटाओ a few more nodes from either side of the target hole अगर
 * mm.color_adjust is being used.
 *
 * Returns:
 * A node to evict, or शून्य अगर there are no overlapping nodes.
 */
काष्ठा drm_mm_node *drm_mm_scan_color_evict(काष्ठा drm_mm_scan *scan)
अणु
	काष्ठा drm_mm *mm = scan->mm;
	काष्ठा drm_mm_node *hole;
	u64 hole_start, hole_end;

	DRM_MM_BUG_ON(list_empty(&mm->hole_stack));

	अगर (!mm->color_adjust)
		वापस शून्य;

	/*
	 * The hole found during scanning should ideally be the first element
	 * in the hole_stack list, but due to side-effects in the driver it
	 * may not be.
	 */
	list_क्रम_each_entry(hole, &mm->hole_stack, hole_stack) अणु
		hole_start = __drm_mm_hole_node_start(hole);
		hole_end = hole_start + hole->hole_size;

		अगर (hole_start <= scan->hit_start &&
		    hole_end >= scan->hit_end)
			अवरोध;
	पूर्ण

	/* We should only be called after we found the hole previously */
	DRM_MM_BUG_ON(&hole->hole_stack == &mm->hole_stack);
	अगर (unlikely(&hole->hole_stack == &mm->hole_stack))
		वापस शून्य;

	DRM_MM_BUG_ON(hole_start > scan->hit_start);
	DRM_MM_BUG_ON(hole_end < scan->hit_end);

	mm->color_adjust(hole, scan->color, &hole_start, &hole_end);
	अगर (hole_start > scan->hit_start)
		वापस hole;
	अगर (hole_end < scan->hit_end)
		वापस list_next_entry(hole, node_list);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_mm_scan_color_evict);

/**
 * drm_mm_init - initialize a drm-mm allocator
 * @mm: the drm_mm काष्ठाure to initialize
 * @start: start of the range managed by @mm
 * @size: end of the range managed by @mm
 *
 * Note that @mm must be cleared to 0 beक्रमe calling this function.
 */
व्योम drm_mm_init(काष्ठा drm_mm *mm, u64 start, u64 size)
अणु
	DRM_MM_BUG_ON(start + size <= start);

	mm->color_adjust = शून्य;

	INIT_LIST_HEAD(&mm->hole_stack);
	mm->पूर्णांकerval_tree = RB_ROOT_CACHED;
	mm->holes_size = RB_ROOT_CACHED;
	mm->holes_addr = RB_ROOT;

	/* Clever trick to aव्योम a special हाल in the मुक्त hole tracking. */
	INIT_LIST_HEAD(&mm->head_node.node_list);
	mm->head_node.flags = 0;
	mm->head_node.mm = mm;
	mm->head_node.start = start + size;
	mm->head_node.size = -size;
	add_hole(&mm->head_node);

	mm->scan_active = 0;
पूर्ण
EXPORT_SYMBOL(drm_mm_init);

/**
 * drm_mm_takeकरोwn - clean up a drm_mm allocator
 * @mm: drm_mm allocator to clean up
 *
 * Note that it is a bug to call this function on an allocator which is not
 * clean.
 */
व्योम drm_mm_takeकरोwn(काष्ठा drm_mm *mm)
अणु
	अगर (WARN(!drm_mm_clean(mm),
		 "Memory manager not clean during takedown.\n"))
		show_leaks(mm);
पूर्ण
EXPORT_SYMBOL(drm_mm_takeकरोwn);

अटल u64 drm_mm_dump_hole(काष्ठा drm_prपूर्णांकer *p, स्थिर काष्ठा drm_mm_node *entry)
अणु
	u64 start, size;

	size = entry->hole_size;
	अगर (size) अणु
		start = drm_mm_hole_node_start(entry);
		drm_म_लिखो(p, "%#018llx-%#018llx: %llu: free\n",
			   start, start + size, size);
	पूर्ण

	वापस size;
पूर्ण
/**
 * drm_mm_prपूर्णांक - prपूर्णांक allocator state
 * @mm: drm_mm allocator to prपूर्णांक
 * @p: DRM prपूर्णांकer to use
 */
व्योम drm_mm_prपूर्णांक(स्थिर काष्ठा drm_mm *mm, काष्ठा drm_prपूर्णांकer *p)
अणु
	स्थिर काष्ठा drm_mm_node *entry;
	u64 total_used = 0, total_मुक्त = 0, total = 0;

	total_मुक्त += drm_mm_dump_hole(p, &mm->head_node);

	drm_mm_क्रम_each_node(entry, mm) अणु
		drm_म_लिखो(p, "%#018llx-%#018llx: %llu: used\n", entry->start,
			   entry->start + entry->size, entry->size);
		total_used += entry->size;
		total_मुक्त += drm_mm_dump_hole(p, entry);
	पूर्ण
	total = total_मुक्त + total_used;

	drm_म_लिखो(p, "total: %llu, used %llu free %llu\n", total,
		   total_used, total_मुक्त);
पूर्ण
EXPORT_SYMBOL(drm_mm_prपूर्णांक);
