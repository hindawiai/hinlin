<शैली गुरु>
/**************************************************************************
 *
 * Copyright 2006-2008 Tungsten Graphics, Inc., Cedar Park, TX. USA.
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
 * Authors:
 * Thomas Hellstrom <thomas-at-tungstengraphics-करोt-com>
 */

#अगर_अघोषित _DRM_MM_H_
#घोषणा _DRM_MM_H_

/*
 * Generic range manager काष्ठाs
 */
#समावेश <linux/bug.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#अगर_घोषित CONFIG_DRM_DEBUG_MM
#समावेश <linux/stackdepot.h>
#पूर्ण_अगर
#समावेश <drm/drm_prपूर्णांक.h>

#अगर_घोषित CONFIG_DRM_DEBUG_MM
#घोषणा DRM_MM_BUG_ON(expr) BUG_ON(expr)
#अन्यथा
#घोषणा DRM_MM_BUG_ON(expr) BUILD_BUG_ON_INVALID(expr)
#पूर्ण_अगर

/**
 * क्रमागत drm_mm_insert_mode - control search and allocation behaviour
 *
 * The &काष्ठा drm_mm range manager supports finding a suitable modes using
 * a number of search trees. These trees are oranised by size, by address and
 * in most recent eviction order. This allows the user to find either the
 * smallest hole to reuse, the lowest or highest address to reuse, or simply
 * reuse the most recent eviction that fits. When allocating the &drm_mm_node
 * from within the hole, the &drm_mm_insert_mode also dictate whether to
 * allocate the lowest matching address or the highest.
 */
क्रमागत drm_mm_insert_mode अणु
	/**
	 * @DRM_MM_INSERT_BEST:
	 *
	 * Search क्रम the smallest hole (within the search range) that fits
	 * the desired node.
	 *
	 * Allocates the node from the bottom of the found hole.
	 */
	DRM_MM_INSERT_BEST = 0,

	/**
	 * @DRM_MM_INSERT_LOW:
	 *
	 * Search क्रम the lowest hole (address बंदst to 0, within the search
	 * range) that fits the desired node.
	 *
	 * Allocates the node from the bottom of the found hole.
	 */
	DRM_MM_INSERT_LOW,

	/**
	 * @DRM_MM_INSERT_HIGH:
	 *
	 * Search क्रम the highest hole (address बंदst to U64_MAX, within the
	 * search range) that fits the desired node.
	 *
	 * Allocates the node from the *top* of the found hole. The specअगरied
	 * alignment क्रम the node is applied to the base of the node
	 * (&drm_mm_node.start).
	 */
	DRM_MM_INSERT_HIGH,

	/**
	 * @DRM_MM_INSERT_EVICT:
	 *
	 * Search क्रम the most recently evicted hole (within the search range)
	 * that fits the desired node. This is appropriate क्रम use immediately
	 * after perक्रमming an eviction scan (see drm_mm_scan_init()) and
	 * removing the selected nodes to क्रमm a hole.
	 *
	 * Allocates the node from the bottom of the found hole.
	 */
	DRM_MM_INSERT_EVICT,

	/**
	 * @DRM_MM_INSERT_ONCE:
	 *
	 * Only check the first hole क्रम suitablity and report -ENOSPC
	 * immediately otherwise, rather than check every hole until a
	 * suitable one is found. Can only be used in conjunction with another
	 * search method such as DRM_MM_INSERT_HIGH or DRM_MM_INSERT_LOW.
	 */
	DRM_MM_INSERT_ONCE = BIT(31),

	/**
	 * @DRM_MM_INSERT_HIGHEST:
	 *
	 * Only check the highest hole (the hole with the largest address) and
	 * insert the node at the top of the hole or report -ENOSPC अगर
	 * unsuitable.
	 *
	 * Does not search all holes.
	 */
	DRM_MM_INSERT_HIGHEST = DRM_MM_INSERT_HIGH | DRM_MM_INSERT_ONCE,

	/**
	 * @DRM_MM_INSERT_LOWEST:
	 *
	 * Only check the lowest hole (the hole with the smallest address) and
	 * insert the node at the bottom of the hole or report -ENOSPC अगर
	 * unsuitable.
	 *
	 * Does not search all holes.
	 */
	DRM_MM_INSERT_LOWEST  = DRM_MM_INSERT_LOW | DRM_MM_INSERT_ONCE,
पूर्ण;

/**
 * काष्ठा drm_mm_node - allocated block in the DRM allocator
 *
 * This represents an allocated block in a &drm_mm allocator. Except क्रम
 * pre-reserved nodes inserted using drm_mm_reserve_node() the काष्ठाure is
 * entirely opaque and should only be accessed through the provided funcions.
 * Since allocation of these nodes is entirely handled by the driver they can be
 * embedded.
 */
काष्ठा drm_mm_node अणु
	/** @color: Opaque driver-निजी tag. */
	अचिन्हित दीर्घ color;
	/** @start: Start address of the allocated block. */
	u64 start;
	/** @size: Size of the allocated block. */
	u64 size;
	/* निजी: */
	काष्ठा drm_mm *mm;
	काष्ठा list_head node_list;
	काष्ठा list_head hole_stack;
	काष्ठा rb_node rb;
	काष्ठा rb_node rb_hole_size;
	काष्ठा rb_node rb_hole_addr;
	u64 __subtree_last;
	u64 hole_size;
	u64 subtree_max_hole;
	अचिन्हित दीर्घ flags;
#घोषणा DRM_MM_NODE_ALLOCATED_BIT	0
#घोषणा DRM_MM_NODE_SCANNED_BIT		1
#अगर_घोषित CONFIG_DRM_DEBUG_MM
	depot_stack_handle_t stack;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा drm_mm - DRM allocator
 *
 * DRM range allocator with a few special functions and features geared towards
 * managing GPU memory. Except क्रम the @color_adjust callback the काष्ठाure is
 * entirely opaque and should only be accessed through the provided functions
 * and macros. This काष्ठाure can be embedded पूर्णांकo larger driver काष्ठाures.
 */
काष्ठा drm_mm अणु
	/**
	 * @color_adjust:
	 *
	 * Optional driver callback to further apply restrictions on a hole. The
	 * node argument poपूर्णांकs at the node containing the hole from which the
	 * block would be allocated (see drm_mm_hole_follows() and मित्रs). The
	 * other arguments are the size of the block to be allocated. The driver
	 * can adjust the start and end as needed to e.g. insert guard pages.
	 */
	व्योम (*color_adjust)(स्थिर काष्ठा drm_mm_node *node,
			     अचिन्हित दीर्घ color,
			     u64 *start, u64 *end);

	/* निजी: */
	/* List of all memory nodes that immediately precede a मुक्त hole. */
	काष्ठा list_head hole_stack;
	/* head_node.node_list is the list of all memory nodes, ordered
	 * according to the (increasing) start address of the memory node. */
	काष्ठा drm_mm_node head_node;
	/* Keep an पूर्णांकerval_tree क्रम fast lookup of drm_mm_nodes by address. */
	काष्ठा rb_root_cached पूर्णांकerval_tree;
	काष्ठा rb_root_cached holes_size;
	काष्ठा rb_root holes_addr;

	अचिन्हित दीर्घ scan_active;
पूर्ण;

/**
 * काष्ठा drm_mm_scan - DRM allocator eviction roaster data
 *
 * This काष्ठाure tracks data needed क्रम the eviction roaster set up using
 * drm_mm_scan_init(), and used with drm_mm_scan_add_block() and
 * drm_mm_scan_हटाओ_block(). The काष्ठाure is entirely opaque and should only
 * be accessed through the provided functions and macros. It is meant to be
 * allocated temporarily by the driver on the stack.
 */
काष्ठा drm_mm_scan अणु
	/* निजी: */
	काष्ठा drm_mm *mm;

	u64 size;
	u64 alignment;
	u64 reमुख्यder_mask;

	u64 range_start;
	u64 range_end;

	u64 hit_start;
	u64 hit_end;

	अचिन्हित दीर्घ color;
	क्रमागत drm_mm_insert_mode mode;
पूर्ण;

/**
 * drm_mm_node_allocated - checks whether a node is allocated
 * @node: drm_mm_node to check
 *
 * Drivers are required to clear a node prior to using it with the
 * drm_mm range manager.
 *
 * Drivers should use this helper क्रम proper encapsulation of drm_mm
 * पूर्णांकernals.
 *
 * Returns:
 * True अगर the @node is allocated.
 */
अटल अंतरभूत bool drm_mm_node_allocated(स्थिर काष्ठा drm_mm_node *node)
अणु
	वापस test_bit(DRM_MM_NODE_ALLOCATED_BIT, &node->flags);
पूर्ण

/**
 * drm_mm_initialized - checks whether an allocator is initialized
 * @mm: drm_mm to check
 *
 * Drivers should clear the काष्ठा drm_mm prior to initialisation अगर they
 * want to use this function.
 *
 * Drivers should use this helper क्रम proper encapsulation of drm_mm
 * पूर्णांकernals.
 *
 * Returns:
 * True अगर the @mm is initialized.
 */
अटल अंतरभूत bool drm_mm_initialized(स्थिर काष्ठा drm_mm *mm)
अणु
	वापस READ_ONCE(mm->hole_stack.next);
पूर्ण

/**
 * drm_mm_hole_follows - checks whether a hole follows this node
 * @node: drm_mm_node to check
 *
 * Holes are embedded पूर्णांकo the drm_mm using the tail of a drm_mm_node.
 * If you wish to know whether a hole follows this particular node,
 * query this function. See also drm_mm_hole_node_start() and
 * drm_mm_hole_node_end().
 *
 * Returns:
 * True अगर a hole follows the @node.
 */
अटल अंतरभूत bool drm_mm_hole_follows(स्थिर काष्ठा drm_mm_node *node)
अणु
	वापस node->hole_size;
पूर्ण

अटल अंतरभूत u64 __drm_mm_hole_node_start(स्थिर काष्ठा drm_mm_node *hole_node)
अणु
	वापस hole_node->start + hole_node->size;
पूर्ण

/**
 * drm_mm_hole_node_start - computes the start of the hole following @node
 * @hole_node: drm_mm_node which implicitly tracks the following hole
 *
 * This is useful क्रम driver-specअगरic debug dumpers. Otherwise drivers should
 * not inspect holes themselves. Drivers must check first whether a hole indeed
 * follows by looking at drm_mm_hole_follows()
 *
 * Returns:
 * Start of the subsequent hole.
 */
अटल अंतरभूत u64 drm_mm_hole_node_start(स्थिर काष्ठा drm_mm_node *hole_node)
अणु
	DRM_MM_BUG_ON(!drm_mm_hole_follows(hole_node));
	वापस __drm_mm_hole_node_start(hole_node);
पूर्ण

अटल अंतरभूत u64 __drm_mm_hole_node_end(स्थिर काष्ठा drm_mm_node *hole_node)
अणु
	वापस list_next_entry(hole_node, node_list)->start;
पूर्ण

/**
 * drm_mm_hole_node_end - computes the end of the hole following @node
 * @hole_node: drm_mm_node which implicitly tracks the following hole
 *
 * This is useful क्रम driver-specअगरic debug dumpers. Otherwise drivers should
 * not inspect holes themselves. Drivers must check first whether a hole indeed
 * follows by looking at drm_mm_hole_follows().
 *
 * Returns:
 * End of the subsequent hole.
 */
अटल अंतरभूत u64 drm_mm_hole_node_end(स्थिर काष्ठा drm_mm_node *hole_node)
अणु
	वापस __drm_mm_hole_node_end(hole_node);
पूर्ण

/**
 * drm_mm_nodes - list of nodes under the drm_mm range manager
 * @mm: the काष्ठा drm_mm range manager
 *
 * As the drm_mm range manager hides its node_list deep with its
 * काष्ठाure, extracting it looks painful and repetitive. This is
 * not expected to be used outside of the drm_mm_क्रम_each_node()
 * macros and similar पूर्णांकernal functions.
 *
 * Returns:
 * The node list, may be empty.
 */
#घोषणा drm_mm_nodes(mm) (&(mm)->head_node.node_list)

/**
 * drm_mm_क्रम_each_node - iterator to walk over all allocated nodes
 * @entry: &काष्ठा drm_mm_node to assign to in each iteration step
 * @mm: &drm_mm allocator to walk
 *
 * This iterator walks over all nodes in the range allocator. It is implemented
 * with list_क्रम_each(), so not save against removal of elements.
 */
#घोषणा drm_mm_क्रम_each_node(entry, mm) \
	list_क्रम_each_entry(entry, drm_mm_nodes(mm), node_list)

/**
 * drm_mm_क्रम_each_node_safe - iterator to walk over all allocated nodes
 * @entry: &काष्ठा drm_mm_node to assign to in each iteration step
 * @next: &काष्ठा drm_mm_node to store the next step
 * @mm: &drm_mm allocator to walk
 *
 * This iterator walks over all nodes in the range allocator. It is implemented
 * with list_क्रम_each_safe(), so save against removal of elements.
 */
#घोषणा drm_mm_क्रम_each_node_safe(entry, next, mm) \
	list_क्रम_each_entry_safe(entry, next, drm_mm_nodes(mm), node_list)

/**
 * drm_mm_क्रम_each_hole - iterator to walk over all holes
 * @pos: &drm_mm_node used पूर्णांकernally to track progress
 * @mm: &drm_mm allocator to walk
 * @hole_start: uदीर्घ variable to assign the hole start to on each iteration
 * @hole_end: uदीर्घ variable to assign the hole end to on each iteration
 *
 * This iterator walks over all holes in the range allocator. It is implemented
 * with list_क्रम_each(), so not save against removal of elements. @entry is used
 * पूर्णांकernally and will not reflect a real drm_mm_node क्रम the very first hole.
 * Hence users of this iterator may not access it.
 *
 * Implementation Note:
 * We need to अंतरभूत list_क्रम_each_entry in order to be able to set hole_start
 * and hole_end on each iteration जबतक keeping the macro sane.
 */
#घोषणा drm_mm_क्रम_each_hole(pos, mm, hole_start, hole_end) \
	क्रम (pos = list_first_entry(&(mm)->hole_stack, \
				    typeof(*pos), hole_stack); \
	     &pos->hole_stack != &(mm)->hole_stack ? \
	     hole_start = drm_mm_hole_node_start(pos), \
	     hole_end = hole_start + pos->hole_size, \
	     1 : 0; \
	     pos = list_next_entry(pos, hole_stack))

/*
 * Basic range manager support (drm_mm.c)
 */
पूर्णांक drm_mm_reserve_node(काष्ठा drm_mm *mm, काष्ठा drm_mm_node *node);
पूर्णांक drm_mm_insert_node_in_range(काष्ठा drm_mm *mm,
				काष्ठा drm_mm_node *node,
				u64 size,
				u64 alignment,
				अचिन्हित दीर्घ color,
				u64 start,
				u64 end,
				क्रमागत drm_mm_insert_mode mode);

/**
 * drm_mm_insert_node_generic - search क्रम space and insert @node
 * @mm: drm_mm to allocate from
 * @node: pपुनः_स्मृतिate node to insert
 * @size: size of the allocation
 * @alignment: alignment of the allocation
 * @color: opaque tag value to use क्रम this node
 * @mode: fine-tune the allocation search and placement
 *
 * This is a simplअगरied version of drm_mm_insert_node_in_range() with no
 * range restrictions applied.
 *
 * The pपुनः_स्मृतिated node must be cleared to 0.
 *
 * Returns:
 * 0 on success, -ENOSPC अगर there's no suitable hole.
 */
अटल अंतरभूत पूर्णांक
drm_mm_insert_node_generic(काष्ठा drm_mm *mm, काष्ठा drm_mm_node *node,
			   u64 size, u64 alignment,
			   अचिन्हित दीर्घ color,
			   क्रमागत drm_mm_insert_mode mode)
अणु
	वापस drm_mm_insert_node_in_range(mm, node,
					   size, alignment, color,
					   0, U64_MAX, mode);
पूर्ण

/**
 * drm_mm_insert_node - search क्रम space and insert @node
 * @mm: drm_mm to allocate from
 * @node: pपुनः_स्मृतिate node to insert
 * @size: size of the allocation
 *
 * This is a simplअगरied version of drm_mm_insert_node_generic() with @color set
 * to 0.
 *
 * The pपुनः_स्मृतिated node must be cleared to 0.
 *
 * Returns:
 * 0 on success, -ENOSPC अगर there's no suitable hole.
 */
अटल अंतरभूत पूर्णांक drm_mm_insert_node(काष्ठा drm_mm *mm,
				     काष्ठा drm_mm_node *node,
				     u64 size)
अणु
	वापस drm_mm_insert_node_generic(mm, node, size, 0, 0, 0);
पूर्ण

व्योम drm_mm_हटाओ_node(काष्ठा drm_mm_node *node);
व्योम drm_mm_replace_node(काष्ठा drm_mm_node *old, काष्ठा drm_mm_node *new);
व्योम drm_mm_init(काष्ठा drm_mm *mm, u64 start, u64 size);
व्योम drm_mm_takeकरोwn(काष्ठा drm_mm *mm);

/**
 * drm_mm_clean - checks whether an allocator is clean
 * @mm: drm_mm allocator to check
 *
 * Returns:
 * True अगर the allocator is completely मुक्त, false अगर there's still a node
 * allocated in it.
 */
अटल अंतरभूत bool drm_mm_clean(स्थिर काष्ठा drm_mm *mm)
अणु
	वापस list_empty(drm_mm_nodes(mm));
पूर्ण

काष्ठा drm_mm_node *
__drm_mm_पूर्णांकerval_first(स्थिर काष्ठा drm_mm *mm, u64 start, u64 last);

/**
 * drm_mm_क्रम_each_node_in_range - iterator to walk over a range of
 * allocated nodes
 * @node__: drm_mm_node काष्ठाure to assign to in each iteration step
 * @mm__: drm_mm allocator to walk
 * @start__: starting offset, the first node will overlap this
 * @end__: ending offset, the last node will start beक्रमe this (but may overlap)
 *
 * This iterator walks over all nodes in the range allocator that lie
 * between @start and @end. It is implemented similarly to list_क्रम_each(),
 * but using the पूर्णांकernal पूर्णांकerval tree to accelerate the search क्रम the
 * starting node, and so not safe against removal of elements. It assumes
 * that @end is within (or is the upper limit of) the drm_mm allocator.
 * If [@start, @end] are beyond the range of the drm_mm, the iterator may walk
 * over the special _unallocated_ &drm_mm.head_node, and may even जारी
 * indefinitely.
 */
#घोषणा drm_mm_क्रम_each_node_in_range(node__, mm__, start__, end__)	\
	क्रम (node__ = __drm_mm_पूर्णांकerval_first((mm__), (start__), (end__)-1); \
	     node__->start < (end__);					\
	     node__ = list_next_entry(node__, node_list))

व्योम drm_mm_scan_init_with_range(काष्ठा drm_mm_scan *scan,
				 काष्ठा drm_mm *mm,
				 u64 size, u64 alignment, अचिन्हित दीर्घ color,
				 u64 start, u64 end,
				 क्रमागत drm_mm_insert_mode mode);

/**
 * drm_mm_scan_init - initialize lru scanning
 * @scan: scan state
 * @mm: drm_mm to scan
 * @size: size of the allocation
 * @alignment: alignment of the allocation
 * @color: opaque tag value to use क्रम the allocation
 * @mode: fine-tune the allocation search and placement
 *
 * This is a simplअगरied version of drm_mm_scan_init_with_range() with no range
 * restrictions applied.
 *
 * This simply sets up the scanning routines with the parameters क्रम the desired
 * hole.
 *
 * Warning:
 * As दीर्घ as the scan list is non-empty, no other operations than
 * adding/removing nodes to/from the scan list are allowed.
 */
अटल अंतरभूत व्योम drm_mm_scan_init(काष्ठा drm_mm_scan *scan,
				    काष्ठा drm_mm *mm,
				    u64 size,
				    u64 alignment,
				    अचिन्हित दीर्घ color,
				    क्रमागत drm_mm_insert_mode mode)
अणु
	drm_mm_scan_init_with_range(scan, mm,
				    size, alignment, color,
				    0, U64_MAX, mode);
पूर्ण

bool drm_mm_scan_add_block(काष्ठा drm_mm_scan *scan,
			   काष्ठा drm_mm_node *node);
bool drm_mm_scan_हटाओ_block(काष्ठा drm_mm_scan *scan,
			      काष्ठा drm_mm_node *node);
काष्ठा drm_mm_node *drm_mm_scan_color_evict(काष्ठा drm_mm_scan *scan);

व्योम drm_mm_prपूर्णांक(स्थिर काष्ठा drm_mm *mm, काष्ठा drm_prपूर्णांकer *p);

#पूर्ण_अगर
