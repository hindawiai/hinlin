<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * XArray implementation
 * Copyright (c) 2017-2018 Microsoft Corporation
 * Copyright (c) 2018-2020 Oracle
 * Author: Matthew Wilcox <willy@infradead.org>
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/export.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/xarray.h>

/*
 * Coding conventions in this file:
 *
 * @xa is used to refer to the entire xarray.
 * @xas is the 'xarray operation state'.  It may be either a poपूर्णांकer to
 * an xa_state, or an xa_state stored on the stack.  This is an unक्रमtunate
 * ambiguity.
 * @index is the index of the entry being operated on
 * @mark is an xa_mark_t; a small number indicating one of the mark bits.
 * @node refers to an xa_node; usually the primary one being operated on by
 * this function.
 * @offset is the index पूर्णांकo the slots array inside an xa_node.
 * @parent refers to the @xa_node बंदr to the head than @node.
 * @entry refers to something stored in a slot in the xarray
 */

अटल अंतरभूत अचिन्हित पूर्णांक xa_lock_type(स्थिर काष्ठा xarray *xa)
अणु
	वापस (__क्रमce अचिन्हित पूर्णांक)xa->xa_flags & 3;
पूर्ण

अटल अंतरभूत व्योम xas_lock_type(काष्ठा xa_state *xas, अचिन्हित पूर्णांक lock_type)
अणु
	अगर (lock_type == XA_LOCK_IRQ)
		xas_lock_irq(xas);
	अन्यथा अगर (lock_type == XA_LOCK_BH)
		xas_lock_bh(xas);
	अन्यथा
		xas_lock(xas);
पूर्ण

अटल अंतरभूत व्योम xas_unlock_type(काष्ठा xa_state *xas, अचिन्हित पूर्णांक lock_type)
अणु
	अगर (lock_type == XA_LOCK_IRQ)
		xas_unlock_irq(xas);
	अन्यथा अगर (lock_type == XA_LOCK_BH)
		xas_unlock_bh(xas);
	अन्यथा
		xas_unlock(xas);
पूर्ण

अटल अंतरभूत bool xa_track_मुक्त(स्थिर काष्ठा xarray *xa)
अणु
	वापस xa->xa_flags & XA_FLAGS_TRACK_FREE;
पूर्ण

अटल अंतरभूत bool xa_zero_busy(स्थिर काष्ठा xarray *xa)
अणु
	वापस xa->xa_flags & XA_FLAGS_ZERO_BUSY;
पूर्ण

अटल अंतरभूत व्योम xa_mark_set(काष्ठा xarray *xa, xa_mark_t mark)
अणु
	अगर (!(xa->xa_flags & XA_FLAGS_MARK(mark)))
		xa->xa_flags |= XA_FLAGS_MARK(mark);
पूर्ण

अटल अंतरभूत व्योम xa_mark_clear(काष्ठा xarray *xa, xa_mark_t mark)
अणु
	अगर (xa->xa_flags & XA_FLAGS_MARK(mark))
		xa->xa_flags &= ~(XA_FLAGS_MARK(mark));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *node_marks(काष्ठा xa_node *node, xa_mark_t mark)
अणु
	वापस node->marks[(__क्रमce अचिन्हित)mark];
पूर्ण

अटल अंतरभूत bool node_get_mark(काष्ठा xa_node *node,
		अचिन्हित पूर्णांक offset, xa_mark_t mark)
अणु
	वापस test_bit(offset, node_marks(node, mark));
पूर्ण

/* वापसs true अगर the bit was set */
अटल अंतरभूत bool node_set_mark(काष्ठा xa_node *node, अचिन्हित पूर्णांक offset,
				xa_mark_t mark)
अणु
	वापस __test_and_set_bit(offset, node_marks(node, mark));
पूर्ण

/* वापसs true अगर the bit was set */
अटल अंतरभूत bool node_clear_mark(काष्ठा xa_node *node, अचिन्हित पूर्णांक offset,
				xa_mark_t mark)
अणु
	वापस __test_and_clear_bit(offset, node_marks(node, mark));
पूर्ण

अटल अंतरभूत bool node_any_mark(काष्ठा xa_node *node, xa_mark_t mark)
अणु
	वापस !biपंचांगap_empty(node_marks(node, mark), XA_CHUNK_SIZE);
पूर्ण

अटल अंतरभूत व्योम node_mark_all(काष्ठा xa_node *node, xa_mark_t mark)
अणु
	biपंचांगap_fill(node_marks(node, mark), XA_CHUNK_SIZE);
पूर्ण

#घोषणा mark_inc(mark) करो अणु \
	mark = (__क्रमce xa_mark_t)((__क्रमce अचिन्हित)(mark) + 1); \
पूर्ण जबतक (0)

/*
 * xas_squash_marks() - Merge all marks to the first entry
 * @xas: Array operation state.
 *
 * Set a mark on the first entry अगर any entry has it set.  Clear marks on
 * all sibling entries.
 */
अटल व्योम xas_squash_marks(स्थिर काष्ठा xa_state *xas)
अणु
	अचिन्हित पूर्णांक mark = 0;
	अचिन्हित पूर्णांक limit = xas->xa_offset + xas->xa_sibs + 1;

	अगर (!xas->xa_sibs)
		वापस;

	करो अणु
		अचिन्हित दीर्घ *marks = xas->xa_node->marks[mark];
		अगर (find_next_bit(marks, limit, xas->xa_offset + 1) == limit)
			जारी;
		__set_bit(xas->xa_offset, marks);
		biपंचांगap_clear(marks, xas->xa_offset + 1, xas->xa_sibs);
	पूर्ण जबतक (mark++ != (__क्रमce अचिन्हित)XA_MARK_MAX);
पूर्ण

/* extracts the offset within this node from the index */
अटल अचिन्हित पूर्णांक get_offset(अचिन्हित दीर्घ index, काष्ठा xa_node *node)
अणु
	वापस (index >> node->shअगरt) & XA_CHUNK_MASK;
पूर्ण

अटल व्योम xas_set_offset(काष्ठा xa_state *xas)
अणु
	xas->xa_offset = get_offset(xas->xa_index, xas->xa_node);
पूर्ण

/* move the index either क्रमwards (find) or backwards (sibling slot) */
अटल व्योम xas_move_index(काष्ठा xa_state *xas, अचिन्हित दीर्घ offset)
अणु
	अचिन्हित पूर्णांक shअगरt = xas->xa_node->shअगरt;
	xas->xa_index &= ~XA_CHUNK_MASK << shअगरt;
	xas->xa_index += offset << shअगरt;
पूर्ण

अटल व्योम xas_advance(काष्ठा xa_state *xas)
अणु
	xas->xa_offset++;
	xas_move_index(xas, xas->xa_offset);
पूर्ण

अटल व्योम *set_bounds(काष्ठा xa_state *xas)
अणु
	xas->xa_node = XAS_BOUNDS;
	वापस शून्य;
पूर्ण

/*
 * Starts a walk.  If the @xas is alपढ़ोy valid, we assume that it's on
 * the right path and just वापस where we've got to.  If we're in an
 * error state, वापस शून्य.  If the index is outside the current scope
 * of the xarray, वापस शून्य without changing @xas->xa_node.  Otherwise
 * set @xas->xa_node to शून्य and वापस the current head of the array.
 */
अटल व्योम *xas_start(काष्ठा xa_state *xas)
अणु
	व्योम *entry;

	अगर (xas_valid(xas))
		वापस xas_reload(xas);
	अगर (xas_error(xas))
		वापस शून्य;

	entry = xa_head(xas->xa);
	अगर (!xa_is_node(entry)) अणु
		अगर (xas->xa_index)
			वापस set_bounds(xas);
	पूर्ण अन्यथा अणु
		अगर ((xas->xa_index >> xa_to_node(entry)->shअगरt) > XA_CHUNK_MASK)
			वापस set_bounds(xas);
	पूर्ण

	xas->xa_node = शून्य;
	वापस entry;
पूर्ण

अटल व्योम *xas_descend(काष्ठा xa_state *xas, काष्ठा xa_node *node)
अणु
	अचिन्हित पूर्णांक offset = get_offset(xas->xa_index, node);
	व्योम *entry = xa_entry(xas->xa, node, offset);

	xas->xa_node = node;
	अगर (xa_is_sibling(entry)) अणु
		offset = xa_to_sibling(entry);
		entry = xa_entry(xas->xa, node, offset);
	पूर्ण

	xas->xa_offset = offset;
	वापस entry;
पूर्ण

/**
 * xas_load() - Load an entry from the XArray (advanced).
 * @xas: XArray operation state.
 *
 * Usually walks the @xas to the appropriate state to load the entry
 * stored at xa_index.  However, it will करो nothing and वापस %शून्य अगर
 * @xas is in an error state.  xas_load() will never expand the tree.
 *
 * If the xa_state is set up to operate on a multi-index entry, xas_load()
 * may वापस %शून्य or an पूर्णांकernal entry, even अगर there are entries
 * present within the range specअगरied by @xas.
 *
 * Context: Any context.  The caller should hold the xa_lock or the RCU lock.
 * Return: Usually an entry in the XArray, but see description क्रम exceptions.
 */
व्योम *xas_load(काष्ठा xa_state *xas)
अणु
	व्योम *entry = xas_start(xas);

	जबतक (xa_is_node(entry)) अणु
		काष्ठा xa_node *node = xa_to_node(entry);

		अगर (xas->xa_shअगरt > node->shअगरt)
			अवरोध;
		entry = xas_descend(xas, node);
		अगर (node->shअगरt == 0)
			अवरोध;
	पूर्ण
	वापस entry;
पूर्ण
EXPORT_SYMBOL_GPL(xas_load);

/* Move the radix tree node cache here */
बाह्य काष्ठा kmem_cache *radix_tree_node_cachep;
बाह्य व्योम radix_tree_node_rcu_मुक्त(काष्ठा rcu_head *head);

#घोषणा XA_RCU_FREE	((काष्ठा xarray *)1)

अटल व्योम xa_node_मुक्त(काष्ठा xa_node *node)
अणु
	XA_NODE_BUG_ON(node, !list_empty(&node->निजी_list));
	node->array = XA_RCU_FREE;
	call_rcu(&node->rcu_head, radix_tree_node_rcu_मुक्त);
पूर्ण

/*
 * xas_destroy() - Free any resources allocated during the XArray operation.
 * @xas: XArray operation state.
 *
 * This function is now पूर्णांकernal-only.
 */
अटल व्योम xas_destroy(काष्ठा xa_state *xas)
अणु
	काष्ठा xa_node *next, *node = xas->xa_alloc;

	जबतक (node) अणु
		XA_NODE_BUG_ON(node, !list_empty(&node->निजी_list));
		next = rcu_dereference_raw(node->parent);
		radix_tree_node_rcu_मुक्त(&node->rcu_head);
		xas->xa_alloc = node = next;
	पूर्ण
पूर्ण

/**
 * xas_nomem() - Allocate memory अगर needed.
 * @xas: XArray operation state.
 * @gfp: Memory allocation flags.
 *
 * If we need to add new nodes to the XArray, we try to allocate memory
 * with GFP_NOWAIT जबतक holding the lock, which will usually succeed.
 * If it fails, @xas is flagged as needing memory to जारी.  The caller
 * should drop the lock and call xas_nomem().  If xas_nomem() succeeds,
 * the caller should retry the operation.
 *
 * Forward progress is guaranteed as one node is allocated here and
 * stored in the xa_state where it will be found by xas_alloc().  More
 * nodes will likely be found in the slab allocator, but we करो not tie
 * them up here.
 *
 * Return: true अगर memory was needed, and was successfully allocated.
 */
bool xas_nomem(काष्ठा xa_state *xas, gfp_t gfp)
अणु
	अगर (xas->xa_node != XA_ERROR(-ENOMEM)) अणु
		xas_destroy(xas);
		वापस false;
	पूर्ण
	अगर (xas->xa->xa_flags & XA_FLAGS_ACCOUNT)
		gfp |= __GFP_ACCOUNT;
	xas->xa_alloc = kmem_cache_alloc(radix_tree_node_cachep, gfp);
	अगर (!xas->xa_alloc)
		वापस false;
	xas->xa_alloc->parent = शून्य;
	XA_NODE_BUG_ON(xas->xa_alloc, !list_empty(&xas->xa_alloc->निजी_list));
	xas->xa_node = XAS_RESTART;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(xas_nomem);

/*
 * __xas_nomem() - Drop locks and allocate memory अगर needed.
 * @xas: XArray operation state.
 * @gfp: Memory allocation flags.
 *
 * Internal variant of xas_nomem().
 *
 * Return: true अगर memory was needed, and was successfully allocated.
 */
अटल bool __xas_nomem(काष्ठा xa_state *xas, gfp_t gfp)
	__must_hold(xas->xa->xa_lock)
अणु
	अचिन्हित पूर्णांक lock_type = xa_lock_type(xas->xa);

	अगर (xas->xa_node != XA_ERROR(-ENOMEM)) अणु
		xas_destroy(xas);
		वापस false;
	पूर्ण
	अगर (xas->xa->xa_flags & XA_FLAGS_ACCOUNT)
		gfp |= __GFP_ACCOUNT;
	अगर (gfpflags_allow_blocking(gfp)) अणु
		xas_unlock_type(xas, lock_type);
		xas->xa_alloc = kmem_cache_alloc(radix_tree_node_cachep, gfp);
		xas_lock_type(xas, lock_type);
	पूर्ण अन्यथा अणु
		xas->xa_alloc = kmem_cache_alloc(radix_tree_node_cachep, gfp);
	पूर्ण
	अगर (!xas->xa_alloc)
		वापस false;
	xas->xa_alloc->parent = शून्य;
	XA_NODE_BUG_ON(xas->xa_alloc, !list_empty(&xas->xa_alloc->निजी_list));
	xas->xa_node = XAS_RESTART;
	वापस true;
पूर्ण

अटल व्योम xas_update(काष्ठा xa_state *xas, काष्ठा xa_node *node)
अणु
	अगर (xas->xa_update)
		xas->xa_update(node);
	अन्यथा
		XA_NODE_BUG_ON(node, !list_empty(&node->निजी_list));
पूर्ण

अटल व्योम *xas_alloc(काष्ठा xa_state *xas, अचिन्हित पूर्णांक shअगरt)
अणु
	काष्ठा xa_node *parent = xas->xa_node;
	काष्ठा xa_node *node = xas->xa_alloc;

	अगर (xas_invalid(xas))
		वापस शून्य;

	अगर (node) अणु
		xas->xa_alloc = शून्य;
	पूर्ण अन्यथा अणु
		gfp_t gfp = GFP_NOWAIT | __GFP_NOWARN;

		अगर (xas->xa->xa_flags & XA_FLAGS_ACCOUNT)
			gfp |= __GFP_ACCOUNT;

		node = kmem_cache_alloc(radix_tree_node_cachep, gfp);
		अगर (!node) अणु
			xas_set_err(xas, -ENOMEM);
			वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (parent) अणु
		node->offset = xas->xa_offset;
		parent->count++;
		XA_NODE_BUG_ON(node, parent->count > XA_CHUNK_SIZE);
		xas_update(xas, parent);
	पूर्ण
	XA_NODE_BUG_ON(node, shअगरt > BITS_PER_LONG);
	XA_NODE_BUG_ON(node, !list_empty(&node->निजी_list));
	node->shअगरt = shअगरt;
	node->count = 0;
	node->nr_values = 0;
	RCU_INIT_POINTER(node->parent, xas->xa_node);
	node->array = xas->xa;

	वापस node;
पूर्ण

#अगर_घोषित CONFIG_XARRAY_MULTI
/* Returns the number of indices covered by a given xa_state */
अटल अचिन्हित दीर्घ xas_size(स्थिर काष्ठा xa_state *xas)
अणु
	वापस (xas->xa_sibs + 1UL) << xas->xa_shअगरt;
पूर्ण
#पूर्ण_अगर

/*
 * Use this to calculate the maximum index that will need to be created
 * in order to add the entry described by @xas.  Because we cannot store a
 * multi-index entry at index 0, the calculation is a little more complex
 * than you might expect.
 */
अटल अचिन्हित दीर्घ xas_max(काष्ठा xa_state *xas)
अणु
	अचिन्हित दीर्घ max = xas->xa_index;

#अगर_घोषित CONFIG_XARRAY_MULTI
	अगर (xas->xa_shअगरt || xas->xa_sibs) अणु
		अचिन्हित दीर्घ mask = xas_size(xas) - 1;
		max |= mask;
		अगर (mask == max)
			max++;
	पूर्ण
#पूर्ण_अगर

	वापस max;
पूर्ण

/* The maximum index that can be contained in the array without expanding it */
अटल अचिन्हित दीर्घ max_index(व्योम *entry)
अणु
	अगर (!xa_is_node(entry))
		वापस 0;
	वापस (XA_CHUNK_SIZE << xa_to_node(entry)->shअगरt) - 1;
पूर्ण

अटल व्योम xas_shrink(काष्ठा xa_state *xas)
अणु
	काष्ठा xarray *xa = xas->xa;
	काष्ठा xa_node *node = xas->xa_node;

	क्रम (;;) अणु
		व्योम *entry;

		XA_NODE_BUG_ON(node, node->count > XA_CHUNK_SIZE);
		अगर (node->count != 1)
			अवरोध;
		entry = xa_entry_locked(xa, node, 0);
		अगर (!entry)
			अवरोध;
		अगर (!xa_is_node(entry) && node->shअगरt)
			अवरोध;
		अगर (xa_is_zero(entry) && xa_zero_busy(xa))
			entry = शून्य;
		xas->xa_node = XAS_BOUNDS;

		RCU_INIT_POINTER(xa->xa_head, entry);
		अगर (xa_track_मुक्त(xa) && !node_get_mark(node, 0, XA_FREE_MARK))
			xa_mark_clear(xa, XA_FREE_MARK);

		node->count = 0;
		node->nr_values = 0;
		अगर (!xa_is_node(entry))
			RCU_INIT_POINTER(node->slots[0], XA_RETRY_ENTRY);
		xas_update(xas, node);
		xa_node_मुक्त(node);
		अगर (!xa_is_node(entry))
			अवरोध;
		node = xa_to_node(entry);
		node->parent = शून्य;
	पूर्ण
पूर्ण

/*
 * xas_delete_node() - Attempt to delete an xa_node
 * @xas: Array operation state.
 *
 * Attempts to delete the @xas->xa_node.  This will fail अगर xa->node has
 * a non-zero reference count.
 */
अटल व्योम xas_delete_node(काष्ठा xa_state *xas)
अणु
	काष्ठा xa_node *node = xas->xa_node;

	क्रम (;;) अणु
		काष्ठा xa_node *parent;

		XA_NODE_BUG_ON(node, node->count > XA_CHUNK_SIZE);
		अगर (node->count)
			अवरोध;

		parent = xa_parent_locked(xas->xa, node);
		xas->xa_node = parent;
		xas->xa_offset = node->offset;
		xa_node_मुक्त(node);

		अगर (!parent) अणु
			xas->xa->xa_head = शून्य;
			xas->xa_node = XAS_BOUNDS;
			वापस;
		पूर्ण

		parent->slots[xas->xa_offset] = शून्य;
		parent->count--;
		XA_NODE_BUG_ON(parent, parent->count > XA_CHUNK_SIZE);
		node = parent;
		xas_update(xas, node);
	पूर्ण

	अगर (!node->parent)
		xas_shrink(xas);
पूर्ण

/**
 * xas_मुक्त_nodes() - Free this node and all nodes that it references
 * @xas: Array operation state.
 * @top: Node to मुक्त
 *
 * This node has been हटाओd from the tree.  We must now मुक्त it and all
 * of its subnodes.  There may be RCU walkers with references पूर्णांकo the tree,
 * so we must replace all entries with retry markers.
 */
अटल व्योम xas_मुक्त_nodes(काष्ठा xa_state *xas, काष्ठा xa_node *top)
अणु
	अचिन्हित पूर्णांक offset = 0;
	काष्ठा xa_node *node = top;

	क्रम (;;) अणु
		व्योम *entry = xa_entry_locked(xas->xa, node, offset);

		अगर (node->shअगरt && xa_is_node(entry)) अणु
			node = xa_to_node(entry);
			offset = 0;
			जारी;
		पूर्ण
		अगर (entry)
			RCU_INIT_POINTER(node->slots[offset], XA_RETRY_ENTRY);
		offset++;
		जबतक (offset == XA_CHUNK_SIZE) अणु
			काष्ठा xa_node *parent;

			parent = xa_parent_locked(xas->xa, node);
			offset = node->offset + 1;
			node->count = 0;
			node->nr_values = 0;
			xas_update(xas, node);
			xa_node_मुक्त(node);
			अगर (node == top)
				वापस;
			node = parent;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * xas_expand adds nodes to the head of the tree until it has reached
 * sufficient height to be able to contain @xas->xa_index
 */
अटल पूर्णांक xas_expand(काष्ठा xa_state *xas, व्योम *head)
अणु
	काष्ठा xarray *xa = xas->xa;
	काष्ठा xa_node *node = शून्य;
	अचिन्हित पूर्णांक shअगरt = 0;
	अचिन्हित दीर्घ max = xas_max(xas);

	अगर (!head) अणु
		अगर (max == 0)
			वापस 0;
		जबतक ((max >> shअगरt) >= XA_CHUNK_SIZE)
			shअगरt += XA_CHUNK_SHIFT;
		वापस shअगरt + XA_CHUNK_SHIFT;
	पूर्ण अन्यथा अगर (xa_is_node(head)) अणु
		node = xa_to_node(head);
		shअगरt = node->shअगरt + XA_CHUNK_SHIFT;
	पूर्ण
	xas->xa_node = शून्य;

	जबतक (max > max_index(head)) अणु
		xa_mark_t mark = 0;

		XA_NODE_BUG_ON(node, shअगरt > BITS_PER_LONG);
		node = xas_alloc(xas, shअगरt);
		अगर (!node)
			वापस -ENOMEM;

		node->count = 1;
		अगर (xa_is_value(head))
			node->nr_values = 1;
		RCU_INIT_POINTER(node->slots[0], head);

		/* Propagate the aggregated mark info to the new child */
		क्रम (;;) अणु
			अगर (xa_track_मुक्त(xa) && mark == XA_FREE_MARK) अणु
				node_mark_all(node, XA_FREE_MARK);
				अगर (!xa_marked(xa, XA_FREE_MARK)) अणु
					node_clear_mark(node, 0, XA_FREE_MARK);
					xa_mark_set(xa, XA_FREE_MARK);
				पूर्ण
			पूर्ण अन्यथा अगर (xa_marked(xa, mark)) अणु
				node_set_mark(node, 0, mark);
			पूर्ण
			अगर (mark == XA_MARK_MAX)
				अवरोध;
			mark_inc(mark);
		पूर्ण

		/*
		 * Now that the new node is fully initialised, we can add
		 * it to the tree
		 */
		अगर (xa_is_node(head)) अणु
			xa_to_node(head)->offset = 0;
			rcu_assign_poपूर्णांकer(xa_to_node(head)->parent, node);
		पूर्ण
		head = xa_mk_node(node);
		rcu_assign_poपूर्णांकer(xa->xa_head, head);
		xas_update(xas, node);

		shअगरt += XA_CHUNK_SHIFT;
	पूर्ण

	xas->xa_node = node;
	वापस shअगरt;
पूर्ण

/*
 * xas_create() - Create a slot to store an entry in.
 * @xas: XArray operation state.
 * @allow_root: %true अगर we can store the entry in the root directly
 *
 * Most users will not need to call this function directly, as it is called
 * by xas_store().  It is useful क्रम करोing conditional store operations
 * (see the xa_cmpxchg() implementation क्रम an example).
 *
 * Return: If the slot alपढ़ोy existed, वापसs the contents of this slot.
 * If the slot was newly created, वापसs %शून्य.  If it failed to create the
 * slot, वापसs %शून्य and indicates the error in @xas.
 */
अटल व्योम *xas_create(काष्ठा xa_state *xas, bool allow_root)
अणु
	काष्ठा xarray *xa = xas->xa;
	व्योम *entry;
	व्योम __rcu **slot;
	काष्ठा xa_node *node = xas->xa_node;
	पूर्णांक shअगरt;
	अचिन्हित पूर्णांक order = xas->xa_shअगरt;

	अगर (xas_top(node)) अणु
		entry = xa_head_locked(xa);
		xas->xa_node = शून्य;
		अगर (!entry && xa_zero_busy(xa))
			entry = XA_ZERO_ENTRY;
		shअगरt = xas_expand(xas, entry);
		अगर (shअगरt < 0)
			वापस शून्य;
		अगर (!shअगरt && !allow_root)
			shअगरt = XA_CHUNK_SHIFT;
		entry = xa_head_locked(xa);
		slot = &xa->xa_head;
	पूर्ण अन्यथा अगर (xas_error(xas)) अणु
		वापस शून्य;
	पूर्ण अन्यथा अगर (node) अणु
		अचिन्हित पूर्णांक offset = xas->xa_offset;

		shअगरt = node->shअगरt;
		entry = xa_entry_locked(xa, node, offset);
		slot = &node->slots[offset];
	पूर्ण अन्यथा अणु
		shअगरt = 0;
		entry = xa_head_locked(xa);
		slot = &xa->xa_head;
	पूर्ण

	जबतक (shअगरt > order) अणु
		shअगरt -= XA_CHUNK_SHIFT;
		अगर (!entry) अणु
			node = xas_alloc(xas, shअगरt);
			अगर (!node)
				अवरोध;
			अगर (xa_track_मुक्त(xa))
				node_mark_all(node, XA_FREE_MARK);
			rcu_assign_poपूर्णांकer(*slot, xa_mk_node(node));
		पूर्ण अन्यथा अगर (xa_is_node(entry)) अणु
			node = xa_to_node(entry);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
		entry = xas_descend(xas, node);
		slot = &node->slots[xas->xa_offset];
	पूर्ण

	वापस entry;
पूर्ण

/**
 * xas_create_range() - Ensure that stores to this range will succeed
 * @xas: XArray operation state.
 *
 * Creates all of the slots in the range covered by @xas.  Sets @xas to
 * create single-index entries and positions it at the beginning of the
 * range.  This is क्रम the benefit of users which have not yet been
 * converted to use multi-index entries.
 */
व्योम xas_create_range(काष्ठा xa_state *xas)
अणु
	अचिन्हित दीर्घ index = xas->xa_index;
	अचिन्हित अक्षर shअगरt = xas->xa_shअगरt;
	अचिन्हित अक्षर sibs = xas->xa_sibs;

	xas->xa_index |= ((sibs + 1UL) << shअगरt) - 1;
	अगर (xas_is_node(xas) && xas->xa_node->shअगरt == xas->xa_shअगरt)
		xas->xa_offset |= sibs;
	xas->xa_shअगरt = 0;
	xas->xa_sibs = 0;

	क्रम (;;) अणु
		xas_create(xas, true);
		अगर (xas_error(xas))
			जाओ restore;
		अगर (xas->xa_index <= (index | XA_CHUNK_MASK))
			जाओ success;
		xas->xa_index -= XA_CHUNK_SIZE;

		क्रम (;;) अणु
			काष्ठा xa_node *node = xas->xa_node;
			xas->xa_node = xa_parent_locked(xas->xa, node);
			xas->xa_offset = node->offset - 1;
			अगर (node->offset != 0)
				अवरोध;
		पूर्ण
	पूर्ण

restore:
	xas->xa_shअगरt = shअगरt;
	xas->xa_sibs = sibs;
	xas->xa_index = index;
	वापस;
success:
	xas->xa_index = index;
	अगर (xas->xa_node)
		xas_set_offset(xas);
पूर्ण
EXPORT_SYMBOL_GPL(xas_create_range);

अटल व्योम update_node(काष्ठा xa_state *xas, काष्ठा xa_node *node,
		पूर्णांक count, पूर्णांक values)
अणु
	अगर (!node || (!count && !values))
		वापस;

	node->count += count;
	node->nr_values += values;
	XA_NODE_BUG_ON(node, node->count > XA_CHUNK_SIZE);
	XA_NODE_BUG_ON(node, node->nr_values > XA_CHUNK_SIZE);
	xas_update(xas, node);
	अगर (count < 0)
		xas_delete_node(xas);
पूर्ण

/**
 * xas_store() - Store this entry in the XArray.
 * @xas: XArray operation state.
 * @entry: New entry.
 *
 * If @xas is operating on a multi-index entry, the entry वापसed by this
 * function is essentially meaningless (it may be an पूर्णांकernal entry or it
 * may be %शून्य, even अगर there are non-शून्य entries at some of the indices
 * covered by the range).  This is not a problem क्रम any current users,
 * and can be changed अगर needed.
 *
 * Return: The old entry at this index.
 */
व्योम *xas_store(काष्ठा xa_state *xas, व्योम *entry)
अणु
	काष्ठा xa_node *node;
	व्योम __rcu **slot = &xas->xa->xa_head;
	अचिन्हित पूर्णांक offset, max;
	पूर्णांक count = 0;
	पूर्णांक values = 0;
	व्योम *first, *next;
	bool value = xa_is_value(entry);

	अगर (entry) अणु
		bool allow_root = !xa_is_node(entry) && !xa_is_zero(entry);
		first = xas_create(xas, allow_root);
	पूर्ण अन्यथा अणु
		first = xas_load(xas);
	पूर्ण

	अगर (xas_invalid(xas))
		वापस first;
	node = xas->xa_node;
	अगर (node && (xas->xa_shअगरt < node->shअगरt))
		xas->xa_sibs = 0;
	अगर ((first == entry) && !xas->xa_sibs)
		वापस first;

	next = first;
	offset = xas->xa_offset;
	max = xas->xa_offset + xas->xa_sibs;
	अगर (node) अणु
		slot = &node->slots[offset];
		अगर (xas->xa_sibs)
			xas_squash_marks(xas);
	पूर्ण
	अगर (!entry)
		xas_init_marks(xas);

	क्रम (;;) अणु
		/*
		 * Must clear the marks beक्रमe setting the entry to शून्य,
		 * otherwise xas_क्रम_each_marked may find a शून्य entry and
		 * stop early.  rcu_assign_poपूर्णांकer contains a release barrier
		 * so the mark clearing will appear to happen beक्रमe the
		 * entry is set to शून्य.
		 */
		rcu_assign_poपूर्णांकer(*slot, entry);
		अगर (xa_is_node(next) && (!node || node->shअगरt))
			xas_मुक्त_nodes(xas, xa_to_node(next));
		अगर (!node)
			अवरोध;
		count += !next - !entry;
		values += !xa_is_value(first) - !value;
		अगर (entry) अणु
			अगर (offset == max)
				अवरोध;
			अगर (!xa_is_sibling(entry))
				entry = xa_mk_sibling(xas->xa_offset);
		पूर्ण अन्यथा अणु
			अगर (offset == XA_CHUNK_MASK)
				अवरोध;
		पूर्ण
		next = xa_entry_locked(xas->xa, node, ++offset);
		अगर (!xa_is_sibling(next)) अणु
			अगर (!entry && (offset > max))
				अवरोध;
			first = next;
		पूर्ण
		slot++;
	पूर्ण

	update_node(xas, node, count, values);
	वापस first;
पूर्ण
EXPORT_SYMBOL_GPL(xas_store);

/**
 * xas_get_mark() - Returns the state of this mark.
 * @xas: XArray operation state.
 * @mark: Mark number.
 *
 * Return: true अगर the mark is set, false अगर the mark is clear or @xas
 * is in an error state.
 */
bool xas_get_mark(स्थिर काष्ठा xa_state *xas, xa_mark_t mark)
अणु
	अगर (xas_invalid(xas))
		वापस false;
	अगर (!xas->xa_node)
		वापस xa_marked(xas->xa, mark);
	वापस node_get_mark(xas->xa_node, xas->xa_offset, mark);
पूर्ण
EXPORT_SYMBOL_GPL(xas_get_mark);

/**
 * xas_set_mark() - Sets the mark on this entry and its parents.
 * @xas: XArray operation state.
 * @mark: Mark number.
 *
 * Sets the specअगरied mark on this entry, and walks up the tree setting it
 * on all the ancestor entries.  Does nothing अगर @xas has not been walked to
 * an entry, or is in an error state.
 */
व्योम xas_set_mark(स्थिर काष्ठा xa_state *xas, xa_mark_t mark)
अणु
	काष्ठा xa_node *node = xas->xa_node;
	अचिन्हित पूर्णांक offset = xas->xa_offset;

	अगर (xas_invalid(xas))
		वापस;

	जबतक (node) अणु
		अगर (node_set_mark(node, offset, mark))
			वापस;
		offset = node->offset;
		node = xa_parent_locked(xas->xa, node);
	पूर्ण

	अगर (!xa_marked(xas->xa, mark))
		xa_mark_set(xas->xa, mark);
पूर्ण
EXPORT_SYMBOL_GPL(xas_set_mark);

/**
 * xas_clear_mark() - Clears the mark on this entry and its parents.
 * @xas: XArray operation state.
 * @mark: Mark number.
 *
 * Clears the specअगरied mark on this entry, and walks back to the head
 * attempting to clear it on all the ancestor entries.  Does nothing अगर
 * @xas has not been walked to an entry, or is in an error state.
 */
व्योम xas_clear_mark(स्थिर काष्ठा xa_state *xas, xa_mark_t mark)
अणु
	काष्ठा xa_node *node = xas->xa_node;
	अचिन्हित पूर्णांक offset = xas->xa_offset;

	अगर (xas_invalid(xas))
		वापस;

	जबतक (node) अणु
		अगर (!node_clear_mark(node, offset, mark))
			वापस;
		अगर (node_any_mark(node, mark))
			वापस;

		offset = node->offset;
		node = xa_parent_locked(xas->xa, node);
	पूर्ण

	अगर (xa_marked(xas->xa, mark))
		xa_mark_clear(xas->xa, mark);
पूर्ण
EXPORT_SYMBOL_GPL(xas_clear_mark);

/**
 * xas_init_marks() - Initialise all marks क्रम the entry
 * @xas: Array operations state.
 *
 * Initialise all marks क्रम the entry specअगरied by @xas.  If we're tracking
 * मुक्त entries with a mark, we need to set it on all entries.  All other
 * marks are cleared.
 *
 * This implementation is not as efficient as it could be; we may walk
 * up the tree multiple बार.
 */
व्योम xas_init_marks(स्थिर काष्ठा xa_state *xas)
अणु
	xa_mark_t mark = 0;

	क्रम (;;) अणु
		अगर (xa_track_मुक्त(xas->xa) && mark == XA_FREE_MARK)
			xas_set_mark(xas, mark);
		अन्यथा
			xas_clear_mark(xas, mark);
		अगर (mark == XA_MARK_MAX)
			अवरोध;
		mark_inc(mark);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(xas_init_marks);

#अगर_घोषित CONFIG_XARRAY_MULTI
अटल अचिन्हित पूर्णांक node_get_marks(काष्ठा xa_node *node, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक marks = 0;
	xa_mark_t mark = XA_MARK_0;

	क्रम (;;) अणु
		अगर (node_get_mark(node, offset, mark))
			marks |= 1 << (__क्रमce अचिन्हित पूर्णांक)mark;
		अगर (mark == XA_MARK_MAX)
			अवरोध;
		mark_inc(mark);
	पूर्ण

	वापस marks;
पूर्ण

अटल व्योम node_set_marks(काष्ठा xa_node *node, अचिन्हित पूर्णांक offset,
			काष्ठा xa_node *child, अचिन्हित पूर्णांक marks)
अणु
	xa_mark_t mark = XA_MARK_0;

	क्रम (;;) अणु
		अगर (marks & (1 << (__क्रमce अचिन्हित पूर्णांक)mark)) अणु
			node_set_mark(node, offset, mark);
			अगर (child)
				node_mark_all(child, mark);
		पूर्ण
		अगर (mark == XA_MARK_MAX)
			अवरोध;
		mark_inc(mark);
	पूर्ण
पूर्ण

/**
 * xas_split_alloc() - Allocate memory क्रम splitting an entry.
 * @xas: XArray operation state.
 * @entry: New entry which will be stored in the array.
 * @order: Current entry order.
 * @gfp: Memory allocation flags.
 *
 * This function should be called beक्रमe calling xas_split().
 * If necessary, it will allocate new nodes (and fill them with @entry)
 * to prepare क्रम the upcoming split of an entry of @order size पूर्णांकo
 * entries of the order stored in the @xas.
 *
 * Context: May sleep अगर @gfp flags permit.
 */
व्योम xas_split_alloc(काष्ठा xa_state *xas, व्योम *entry, अचिन्हित पूर्णांक order,
		gfp_t gfp)
अणु
	अचिन्हित पूर्णांक sibs = (1 << (order % XA_CHUNK_SHIFT)) - 1;
	अचिन्हित पूर्णांक mask = xas->xa_sibs;

	/* XXX: no support क्रम splitting really large entries yet */
	अगर (WARN_ON(xas->xa_shअगरt + 2 * XA_CHUNK_SHIFT < order))
		जाओ nomem;
	अगर (xas->xa_shअगरt + XA_CHUNK_SHIFT > order)
		वापस;

	करो अणु
		अचिन्हित पूर्णांक i;
		व्योम *sibling = शून्य;
		काष्ठा xa_node *node;

		node = kmem_cache_alloc(radix_tree_node_cachep, gfp);
		अगर (!node)
			जाओ nomem;
		node->array = xas->xa;
		क्रम (i = 0; i < XA_CHUNK_SIZE; i++) अणु
			अगर ((i & mask) == 0) अणु
				RCU_INIT_POINTER(node->slots[i], entry);
				sibling = xa_mk_sibling(i);
			पूर्ण अन्यथा अणु
				RCU_INIT_POINTER(node->slots[i], sibling);
			पूर्ण
		पूर्ण
		RCU_INIT_POINTER(node->parent, xas->xa_alloc);
		xas->xa_alloc = node;
	पूर्ण जबतक (sibs-- > 0);

	वापस;
nomem:
	xas_destroy(xas);
	xas_set_err(xas, -ENOMEM);
पूर्ण
EXPORT_SYMBOL_GPL(xas_split_alloc);

/**
 * xas_split() - Split a multi-index entry पूर्णांकo smaller entries.
 * @xas: XArray operation state.
 * @entry: New entry to store in the array.
 * @order: Current entry order.
 *
 * The size of the new entries is set in @xas.  The value in @entry is
 * copied to all the replacement entries.
 *
 * Context: Any context.  The caller should hold the xa_lock.
 */
व्योम xas_split(काष्ठा xa_state *xas, व्योम *entry, अचिन्हित पूर्णांक order)
अणु
	अचिन्हित पूर्णांक sibs = (1 << (order % XA_CHUNK_SHIFT)) - 1;
	अचिन्हित पूर्णांक offset, marks;
	काष्ठा xa_node *node;
	व्योम *curr = xas_load(xas);
	पूर्णांक values = 0;

	node = xas->xa_node;
	अगर (xas_top(node))
		वापस;

	marks = node_get_marks(node, xas->xa_offset);

	offset = xas->xa_offset + sibs;
	करो अणु
		अगर (xas->xa_shअगरt < node->shअगरt) अणु
			काष्ठा xa_node *child = xas->xa_alloc;

			xas->xa_alloc = rcu_dereference_raw(child->parent);
			child->shअगरt = node->shअगरt - XA_CHUNK_SHIFT;
			child->offset = offset;
			child->count = XA_CHUNK_SIZE;
			child->nr_values = xa_is_value(entry) ?
					XA_CHUNK_SIZE : 0;
			RCU_INIT_POINTER(child->parent, node);
			node_set_marks(node, offset, child, marks);
			rcu_assign_poपूर्णांकer(node->slots[offset],
					xa_mk_node(child));
			अगर (xa_is_value(curr))
				values--;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक canon = offset - xas->xa_sibs;

			node_set_marks(node, canon, शून्य, marks);
			rcu_assign_poपूर्णांकer(node->slots[canon], entry);
			जबतक (offset > canon)
				rcu_assign_poपूर्णांकer(node->slots[offset--],
						xa_mk_sibling(canon));
			values += (xa_is_value(entry) - xa_is_value(curr)) *
					(xas->xa_sibs + 1);
		पूर्ण
	पूर्ण जबतक (offset-- > xas->xa_offset);

	node->nr_values += values;
पूर्ण
EXPORT_SYMBOL_GPL(xas_split);
#पूर्ण_अगर

/**
 * xas_छोड़ो() - Pause a walk to drop a lock.
 * @xas: XArray operation state.
 *
 * Some users need to छोड़ो a walk and drop the lock they're holding in
 * order to yield to a higher priority thपढ़ो or carry out an operation
 * on an entry.  Those users should call this function beक्रमe they drop
 * the lock.  It resets the @xas to be suitable क्रम the next iteration
 * of the loop after the user has reacquired the lock.  If most entries
 * found during a walk require you to call xas_छोड़ो(), the xa_क्रम_each()
 * iterator may be more appropriate.
 *
 * Note that xas_छोड़ो() only works क्रम क्रमward iteration.  If a user needs
 * to छोड़ो a reverse iteration, we will need a xas_छोड़ो_rev().
 */
व्योम xas_छोड़ो(काष्ठा xa_state *xas)
अणु
	काष्ठा xa_node *node = xas->xa_node;

	अगर (xas_invalid(xas))
		वापस;

	xas->xa_node = XAS_RESTART;
	अगर (node) अणु
		अचिन्हित दीर्घ offset = xas->xa_offset;
		जबतक (++offset < XA_CHUNK_SIZE) अणु
			अगर (!xa_is_sibling(xa_entry(xas->xa, node, offset)))
				अवरोध;
		पूर्ण
		xas->xa_index += (offset - xas->xa_offset) << node->shअगरt;
		अगर (xas->xa_index == 0)
			xas->xa_node = XAS_BOUNDS;
	पूर्ण अन्यथा अणु
		xas->xa_index++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(xas_छोड़ो);

/*
 * __xas_prev() - Find the previous entry in the XArray.
 * @xas: XArray operation state.
 *
 * Helper function क्रम xas_prev() which handles all the complex हालs
 * out of line.
 */
व्योम *__xas_prev(काष्ठा xa_state *xas)
अणु
	व्योम *entry;

	अगर (!xas_frozen(xas->xa_node))
		xas->xa_index--;
	अगर (!xas->xa_node)
		वापस set_bounds(xas);
	अगर (xas_not_node(xas->xa_node))
		वापस xas_load(xas);

	अगर (xas->xa_offset != get_offset(xas->xa_index, xas->xa_node))
		xas->xa_offset--;

	जबतक (xas->xa_offset == 255) अणु
		xas->xa_offset = xas->xa_node->offset - 1;
		xas->xa_node = xa_parent(xas->xa, xas->xa_node);
		अगर (!xas->xa_node)
			वापस set_bounds(xas);
	पूर्ण

	क्रम (;;) अणु
		entry = xa_entry(xas->xa, xas->xa_node, xas->xa_offset);
		अगर (!xa_is_node(entry))
			वापस entry;

		xas->xa_node = xa_to_node(entry);
		xas_set_offset(xas);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__xas_prev);

/*
 * __xas_next() - Find the next entry in the XArray.
 * @xas: XArray operation state.
 *
 * Helper function क्रम xas_next() which handles all the complex हालs
 * out of line.
 */
व्योम *__xas_next(काष्ठा xa_state *xas)
अणु
	व्योम *entry;

	अगर (!xas_frozen(xas->xa_node))
		xas->xa_index++;
	अगर (!xas->xa_node)
		वापस set_bounds(xas);
	अगर (xas_not_node(xas->xa_node))
		वापस xas_load(xas);

	अगर (xas->xa_offset != get_offset(xas->xa_index, xas->xa_node))
		xas->xa_offset++;

	जबतक (xas->xa_offset == XA_CHUNK_SIZE) अणु
		xas->xa_offset = xas->xa_node->offset + 1;
		xas->xa_node = xa_parent(xas->xa, xas->xa_node);
		अगर (!xas->xa_node)
			वापस set_bounds(xas);
	पूर्ण

	क्रम (;;) अणु
		entry = xa_entry(xas->xa, xas->xa_node, xas->xa_offset);
		अगर (!xa_is_node(entry))
			वापस entry;

		xas->xa_node = xa_to_node(entry);
		xas_set_offset(xas);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__xas_next);

/**
 * xas_find() - Find the next present entry in the XArray.
 * @xas: XArray operation state.
 * @max: Highest index to वापस.
 *
 * If the @xas has not yet been walked to an entry, वापस the entry
 * which has an index >= xas.xa_index.  If it has been walked, the entry
 * currently being poपूर्णांकed at has been processed, and so we move to the
 * next entry.
 *
 * If no entry is found and the array is smaller than @max, the iterator
 * is set to the smallest index not yet in the array.  This allows @xas
 * to be immediately passed to xas_store().
 *
 * Return: The entry, अगर found, otherwise %शून्य.
 */
व्योम *xas_find(काष्ठा xa_state *xas, अचिन्हित दीर्घ max)
अणु
	व्योम *entry;

	अगर (xas_error(xas) || xas->xa_node == XAS_BOUNDS)
		वापस शून्य;
	अगर (xas->xa_index > max)
		वापस set_bounds(xas);

	अगर (!xas->xa_node) अणु
		xas->xa_index = 1;
		वापस set_bounds(xas);
	पूर्ण अन्यथा अगर (xas->xa_node == XAS_RESTART) अणु
		entry = xas_load(xas);
		अगर (entry || xas_not_node(xas->xa_node))
			वापस entry;
	पूर्ण अन्यथा अगर (!xas->xa_node->shअगरt &&
		    xas->xa_offset != (xas->xa_index & XA_CHUNK_MASK)) अणु
		xas->xa_offset = ((xas->xa_index - 1) & XA_CHUNK_MASK) + 1;
	पूर्ण

	xas_advance(xas);

	जबतक (xas->xa_node && (xas->xa_index <= max)) अणु
		अगर (unlikely(xas->xa_offset == XA_CHUNK_SIZE)) अणु
			xas->xa_offset = xas->xa_node->offset + 1;
			xas->xa_node = xa_parent(xas->xa, xas->xa_node);
			जारी;
		पूर्ण

		entry = xa_entry(xas->xa, xas->xa_node, xas->xa_offset);
		अगर (xa_is_node(entry)) अणु
			xas->xa_node = xa_to_node(entry);
			xas->xa_offset = 0;
			जारी;
		पूर्ण
		अगर (entry && !xa_is_sibling(entry))
			वापस entry;

		xas_advance(xas);
	पूर्ण

	अगर (!xas->xa_node)
		xas->xa_node = XAS_BOUNDS;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(xas_find);

/**
 * xas_find_marked() - Find the next marked entry in the XArray.
 * @xas: XArray operation state.
 * @max: Highest index to वापस.
 * @mark: Mark number to search क्रम.
 *
 * If the @xas has not yet been walked to an entry, वापस the marked entry
 * which has an index >= xas.xa_index.  If it has been walked, the entry
 * currently being poपूर्णांकed at has been processed, and so we वापस the
 * first marked entry with an index > xas.xa_index.
 *
 * If no marked entry is found and the array is smaller than @max, @xas is
 * set to the bounds state and xas->xa_index is set to the smallest index
 * not yet in the array.  This allows @xas to be immediately passed to
 * xas_store().
 *
 * If no entry is found beक्रमe @max is reached, @xas is set to the restart
 * state.
 *
 * Return: The entry, अगर found, otherwise %शून्य.
 */
व्योम *xas_find_marked(काष्ठा xa_state *xas, अचिन्हित दीर्घ max, xa_mark_t mark)
अणु
	bool advance = true;
	अचिन्हित पूर्णांक offset;
	व्योम *entry;

	अगर (xas_error(xas))
		वापस शून्य;
	अगर (xas->xa_index > max)
		जाओ max;

	अगर (!xas->xa_node) अणु
		xas->xa_index = 1;
		जाओ out;
	पूर्ण अन्यथा अगर (xas_top(xas->xa_node)) अणु
		advance = false;
		entry = xa_head(xas->xa);
		xas->xa_node = शून्य;
		अगर (xas->xa_index > max_index(entry))
			जाओ out;
		अगर (!xa_is_node(entry)) अणु
			अगर (xa_marked(xas->xa, mark))
				वापस entry;
			xas->xa_index = 1;
			जाओ out;
		पूर्ण
		xas->xa_node = xa_to_node(entry);
		xas->xa_offset = xas->xa_index >> xas->xa_node->shअगरt;
	पूर्ण

	जबतक (xas->xa_index <= max) अणु
		अगर (unlikely(xas->xa_offset == XA_CHUNK_SIZE)) अणु
			xas->xa_offset = xas->xa_node->offset + 1;
			xas->xa_node = xa_parent(xas->xa, xas->xa_node);
			अगर (!xas->xa_node)
				अवरोध;
			advance = false;
			जारी;
		पूर्ण

		अगर (!advance) अणु
			entry = xa_entry(xas->xa, xas->xa_node, xas->xa_offset);
			अगर (xa_is_sibling(entry)) अणु
				xas->xa_offset = xa_to_sibling(entry);
				xas_move_index(xas, xas->xa_offset);
			पूर्ण
		पूर्ण

		offset = xas_find_chunk(xas, advance, mark);
		अगर (offset > xas->xa_offset) अणु
			advance = false;
			xas_move_index(xas, offset);
			/* Mind the wrap */
			अगर ((xas->xa_index - 1) >= max)
				जाओ max;
			xas->xa_offset = offset;
			अगर (offset == XA_CHUNK_SIZE)
				जारी;
		पूर्ण

		entry = xa_entry(xas->xa, xas->xa_node, xas->xa_offset);
		अगर (!entry && !(xa_track_मुक्त(xas->xa) && mark == XA_FREE_MARK))
			जारी;
		अगर (!xa_is_node(entry))
			वापस entry;
		xas->xa_node = xa_to_node(entry);
		xas_set_offset(xas);
	पूर्ण

out:
	अगर (xas->xa_index > max)
		जाओ max;
	वापस set_bounds(xas);
max:
	xas->xa_node = XAS_RESTART;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(xas_find_marked);

/**
 * xas_find_conflict() - Find the next present entry in a range.
 * @xas: XArray operation state.
 *
 * The @xas describes both a range and a position within that range.
 *
 * Context: Any context.  Expects xa_lock to be held.
 * Return: The next entry in the range covered by @xas or %शून्य.
 */
व्योम *xas_find_conflict(काष्ठा xa_state *xas)
अणु
	व्योम *curr;

	अगर (xas_error(xas))
		वापस शून्य;

	अगर (!xas->xa_node)
		वापस शून्य;

	अगर (xas_top(xas->xa_node)) अणु
		curr = xas_start(xas);
		अगर (!curr)
			वापस शून्य;
		जबतक (xa_is_node(curr)) अणु
			काष्ठा xa_node *node = xa_to_node(curr);
			curr = xas_descend(xas, node);
		पूर्ण
		अगर (curr)
			वापस curr;
	पूर्ण

	अगर (xas->xa_node->shअगरt > xas->xa_shअगरt)
		वापस शून्य;

	क्रम (;;) अणु
		अगर (xas->xa_node->shअगरt == xas->xa_shअगरt) अणु
			अगर ((xas->xa_offset & xas->xa_sibs) == xas->xa_sibs)
				अवरोध;
		पूर्ण अन्यथा अगर (xas->xa_offset == XA_CHUNK_MASK) अणु
			xas->xa_offset = xas->xa_node->offset;
			xas->xa_node = xa_parent_locked(xas->xa, xas->xa_node);
			अगर (!xas->xa_node)
				अवरोध;
			जारी;
		पूर्ण
		curr = xa_entry_locked(xas->xa, xas->xa_node, ++xas->xa_offset);
		अगर (xa_is_sibling(curr))
			जारी;
		जबतक (xa_is_node(curr)) अणु
			xas->xa_node = xa_to_node(curr);
			xas->xa_offset = 0;
			curr = xa_entry_locked(xas->xa, xas->xa_node, 0);
		पूर्ण
		अगर (curr)
			वापस curr;
	पूर्ण
	xas->xa_offset -= xas->xa_sibs;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(xas_find_conflict);

/**
 * xa_load() - Load an entry from an XArray.
 * @xa: XArray.
 * @index: index पूर्णांकo array.
 *
 * Context: Any context.  Takes and releases the RCU lock.
 * Return: The entry at @index in @xa.
 */
व्योम *xa_load(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	XA_STATE(xas, xa, index);
	व्योम *entry;

	rcu_पढ़ो_lock();
	करो अणु
		entry = xas_load(&xas);
		अगर (xa_is_zero(entry))
			entry = शून्य;
	पूर्ण जबतक (xas_retry(&xas, entry));
	rcu_पढ़ो_unlock();

	वापस entry;
पूर्ण
EXPORT_SYMBOL(xa_load);

अटल व्योम *xas_result(काष्ठा xa_state *xas, व्योम *curr)
अणु
	अगर (xa_is_zero(curr))
		वापस शून्य;
	अगर (xas_error(xas))
		curr = xas->xa_node;
	वापस curr;
पूर्ण

/**
 * __xa_erase() - Erase this entry from the XArray जबतक locked.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 *
 * After this function वापसs, loading from @index will वापस %शून्य.
 * If the index is part of a multi-index entry, all indices will be erased
 * and none of the entries will be part of a multi-index entry.
 *
 * Context: Any context.  Expects xa_lock to be held on entry.
 * Return: The entry which used to be at this index.
 */
व्योम *__xa_erase(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	XA_STATE(xas, xa, index);
	वापस xas_result(&xas, xas_store(&xas, शून्य));
पूर्ण
EXPORT_SYMBOL(__xa_erase);

/**
 * xa_erase() - Erase this entry from the XArray.
 * @xa: XArray.
 * @index: Index of entry.
 *
 * After this function वापसs, loading from @index will वापस %शून्य.
 * If the index is part of a multi-index entry, all indices will be erased
 * and none of the entries will be part of a multi-index entry.
 *
 * Context: Any context.  Takes and releases the xa_lock.
 * Return: The entry which used to be at this index.
 */
व्योम *xa_erase(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	व्योम *entry;

	xa_lock(xa);
	entry = __xa_erase(xa, index);
	xa_unlock(xa);

	वापस entry;
पूर्ण
EXPORT_SYMBOL(xa_erase);

/**
 * __xa_store() - Store this entry in the XArray.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @entry: New entry.
 * @gfp: Memory allocation flags.
 *
 * You must alपढ़ोy be holding the xa_lock when calling this function.
 * It will drop the lock अगर needed to allocate memory, and then reacquire
 * it afterwards.
 *
 * Context: Any context.  Expects xa_lock to be held on entry.  May
 * release and reacquire xa_lock अगर @gfp flags permit.
 * Return: The old entry at this index or xa_err() अगर an error happened.
 */
व्योम *__xa_store(काष्ठा xarray *xa, अचिन्हित दीर्घ index, व्योम *entry, gfp_t gfp)
अणु
	XA_STATE(xas, xa, index);
	व्योम *curr;

	अगर (WARN_ON_ONCE(xa_is_advanced(entry)))
		वापस XA_ERROR(-EINVAL);
	अगर (xa_track_मुक्त(xa) && !entry)
		entry = XA_ZERO_ENTRY;

	करो अणु
		curr = xas_store(&xas, entry);
		अगर (xa_track_मुक्त(xa))
			xas_clear_mark(&xas, XA_FREE_MARK);
	पूर्ण जबतक (__xas_nomem(&xas, gfp));

	वापस xas_result(&xas, curr);
पूर्ण
EXPORT_SYMBOL(__xa_store);

/**
 * xa_store() - Store this entry in the XArray.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @entry: New entry.
 * @gfp: Memory allocation flags.
 *
 * After this function वापसs, loads from this index will वापस @entry.
 * Storing पूर्णांकo an existing multi-index entry updates the entry of every index.
 * The marks associated with @index are unaffected unless @entry is %शून्य.
 *
 * Context: Any context.  Takes and releases the xa_lock.
 * May sleep अगर the @gfp flags permit.
 * Return: The old entry at this index on success, xa_err(-EINVAL) अगर @entry
 * cannot be stored in an XArray, or xa_err(-ENOMEM) अगर memory allocation
 * failed.
 */
व्योम *xa_store(काष्ठा xarray *xa, अचिन्हित दीर्घ index, व्योम *entry, gfp_t gfp)
अणु
	व्योम *curr;

	xa_lock(xa);
	curr = __xa_store(xa, index, entry, gfp);
	xa_unlock(xa);

	वापस curr;
पूर्ण
EXPORT_SYMBOL(xa_store);

/**
 * __xa_cmpxchg() - Store this entry in the XArray.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @old: Old value to test against.
 * @entry: New entry.
 * @gfp: Memory allocation flags.
 *
 * You must alपढ़ोy be holding the xa_lock when calling this function.
 * It will drop the lock अगर needed to allocate memory, and then reacquire
 * it afterwards.
 *
 * Context: Any context.  Expects xa_lock to be held on entry.  May
 * release and reacquire xa_lock अगर @gfp flags permit.
 * Return: The old entry at this index or xa_err() अगर an error happened.
 */
व्योम *__xa_cmpxchg(काष्ठा xarray *xa, अचिन्हित दीर्घ index,
			व्योम *old, व्योम *entry, gfp_t gfp)
अणु
	XA_STATE(xas, xa, index);
	व्योम *curr;

	अगर (WARN_ON_ONCE(xa_is_advanced(entry)))
		वापस XA_ERROR(-EINVAL);

	करो अणु
		curr = xas_load(&xas);
		अगर (curr == old) अणु
			xas_store(&xas, entry);
			अगर (xa_track_मुक्त(xa) && entry && !curr)
				xas_clear_mark(&xas, XA_FREE_MARK);
		पूर्ण
	पूर्ण जबतक (__xas_nomem(&xas, gfp));

	वापस xas_result(&xas, curr);
पूर्ण
EXPORT_SYMBOL(__xa_cmpxchg);

/**
 * __xa_insert() - Store this entry in the XArray अगर no entry is present.
 * @xa: XArray.
 * @index: Index पूर्णांकo array.
 * @entry: New entry.
 * @gfp: Memory allocation flags.
 *
 * Inserting a शून्य entry will store a reserved entry (like xa_reserve())
 * अगर no entry is present.  Inserting will fail अगर a reserved entry is
 * present, even though loading from this index will वापस शून्य.
 *
 * Context: Any context.  Expects xa_lock to be held on entry.  May
 * release and reacquire xa_lock अगर @gfp flags permit.
 * Return: 0 अगर the store succeeded.  -EBUSY अगर another entry was present.
 * -ENOMEM अगर memory could not be allocated.
 */
पूर्णांक __xa_insert(काष्ठा xarray *xa, अचिन्हित दीर्घ index, व्योम *entry, gfp_t gfp)
अणु
	XA_STATE(xas, xa, index);
	व्योम *curr;

	अगर (WARN_ON_ONCE(xa_is_advanced(entry)))
		वापस -EINVAL;
	अगर (!entry)
		entry = XA_ZERO_ENTRY;

	करो अणु
		curr = xas_load(&xas);
		अगर (!curr) अणु
			xas_store(&xas, entry);
			अगर (xa_track_मुक्त(xa))
				xas_clear_mark(&xas, XA_FREE_MARK);
		पूर्ण अन्यथा अणु
			xas_set_err(&xas, -EBUSY);
		पूर्ण
	पूर्ण जबतक (__xas_nomem(&xas, gfp));

	वापस xas_error(&xas);
पूर्ण
EXPORT_SYMBOL(__xa_insert);

#अगर_घोषित CONFIG_XARRAY_MULTI
अटल व्योम xas_set_range(काष्ठा xa_state *xas, अचिन्हित दीर्घ first,
		अचिन्हित दीर्घ last)
अणु
	अचिन्हित पूर्णांक shअगरt = 0;
	अचिन्हित दीर्घ sibs = last - first;
	अचिन्हित पूर्णांक offset = XA_CHUNK_MASK;

	xas_set(xas, first);

	जबतक ((first & XA_CHUNK_MASK) == 0) अणु
		अगर (sibs < XA_CHUNK_MASK)
			अवरोध;
		अगर ((sibs == XA_CHUNK_MASK) && (offset < XA_CHUNK_MASK))
			अवरोध;
		shअगरt += XA_CHUNK_SHIFT;
		अगर (offset == XA_CHUNK_MASK)
			offset = sibs & XA_CHUNK_MASK;
		sibs >>= XA_CHUNK_SHIFT;
		first >>= XA_CHUNK_SHIFT;
	पूर्ण

	offset = first & XA_CHUNK_MASK;
	अगर (offset + sibs > XA_CHUNK_MASK)
		sibs = XA_CHUNK_MASK - offset;
	अगर ((((first + sibs + 1) << shअगरt) - 1) > last)
		sibs -= 1;

	xas->xa_shअगरt = shअगरt;
	xas->xa_sibs = sibs;
पूर्ण

/**
 * xa_store_range() - Store this entry at a range of indices in the XArray.
 * @xa: XArray.
 * @first: First index to affect.
 * @last: Last index to affect.
 * @entry: New entry.
 * @gfp: Memory allocation flags.
 *
 * After this function वापसs, loads from any index between @first and @last,
 * inclusive will वापस @entry.
 * Storing पूर्णांकo an existing multi-index entry updates the entry of every index.
 * The marks associated with @index are unaffected unless @entry is %शून्य.
 *
 * Context: Process context.  Takes and releases the xa_lock.  May sleep
 * अगर the @gfp flags permit.
 * Return: %शून्य on success, xa_err(-EINVAL) अगर @entry cannot be stored in
 * an XArray, or xa_err(-ENOMEM) अगर memory allocation failed.
 */
व्योम *xa_store_range(काष्ठा xarray *xa, अचिन्हित दीर्घ first,
		अचिन्हित दीर्घ last, व्योम *entry, gfp_t gfp)
अणु
	XA_STATE(xas, xa, 0);

	अगर (WARN_ON_ONCE(xa_is_पूर्णांकernal(entry)))
		वापस XA_ERROR(-EINVAL);
	अगर (last < first)
		वापस XA_ERROR(-EINVAL);

	करो अणु
		xas_lock(&xas);
		अगर (entry) अणु
			अचिन्हित पूर्णांक order = BITS_PER_LONG;
			अगर (last + 1)
				order = __ffs(last + 1);
			xas_set_order(&xas, last, order);
			xas_create(&xas, true);
			अगर (xas_error(&xas))
				जाओ unlock;
		पूर्ण
		करो अणु
			xas_set_range(&xas, first, last);
			xas_store(&xas, entry);
			अगर (xas_error(&xas))
				जाओ unlock;
			first += xas_size(&xas);
		पूर्ण जबतक (first <= last);
unlock:
		xas_unlock(&xas);
	पूर्ण जबतक (xas_nomem(&xas, gfp));

	वापस xas_result(&xas, शून्य);
पूर्ण
EXPORT_SYMBOL(xa_store_range);

/**
 * xa_get_order() - Get the order of an entry.
 * @xa: XArray.
 * @index: Index of the entry.
 *
 * Return: A number between 0 and 63 indicating the order of the entry.
 */
पूर्णांक xa_get_order(काष्ठा xarray *xa, अचिन्हित दीर्घ index)
अणु
	XA_STATE(xas, xa, index);
	व्योम *entry;
	पूर्णांक order = 0;

	rcu_पढ़ो_lock();
	entry = xas_load(&xas);

	अगर (!entry)
		जाओ unlock;

	अगर (!xas.xa_node)
		जाओ unlock;

	क्रम (;;) अणु
		अचिन्हित पूर्णांक slot = xas.xa_offset + (1 << order);

		अगर (slot >= XA_CHUNK_SIZE)
			अवरोध;
		अगर (!xa_is_sibling(xas.xa_node->slots[slot]))
			अवरोध;
		order++;
	पूर्ण

	order += xas.xa_node->shअगरt;
unlock:
	rcu_पढ़ो_unlock();

	वापस order;
पूर्ण
EXPORT_SYMBOL(xa_get_order);
#पूर्ण_अगर /* CONFIG_XARRAY_MULTI */

/**
 * __xa_alloc() - Find somewhere to store this entry in the XArray.
 * @xa: XArray.
 * @id: Poपूर्णांकer to ID.
 * @limit: Range क्रम allocated ID.
 * @entry: New entry.
 * @gfp: Memory allocation flags.
 *
 * Finds an empty entry in @xa between @limit.min and @limit.max,
 * stores the index पूर्णांकo the @id poपूर्णांकer, then stores the entry at
 * that index.  A concurrent lookup will not see an uninitialised @id.
 *
 * Context: Any context.  Expects xa_lock to be held on entry.  May
 * release and reacquire xa_lock अगर @gfp flags permit.
 * Return: 0 on success, -ENOMEM अगर memory could not be allocated or
 * -EBUSY अगर there are no मुक्त entries in @limit.
 */
पूर्णांक __xa_alloc(काष्ठा xarray *xa, u32 *id, व्योम *entry,
		काष्ठा xa_limit limit, gfp_t gfp)
अणु
	XA_STATE(xas, xa, 0);

	अगर (WARN_ON_ONCE(xa_is_advanced(entry)))
		वापस -EINVAL;
	अगर (WARN_ON_ONCE(!xa_track_मुक्त(xa)))
		वापस -EINVAL;

	अगर (!entry)
		entry = XA_ZERO_ENTRY;

	करो अणु
		xas.xa_index = limit.min;
		xas_find_marked(&xas, limit.max, XA_FREE_MARK);
		अगर (xas.xa_node == XAS_RESTART)
			xas_set_err(&xas, -EBUSY);
		अन्यथा
			*id = xas.xa_index;
		xas_store(&xas, entry);
		xas_clear_mark(&xas, XA_FREE_MARK);
	पूर्ण जबतक (__xas_nomem(&xas, gfp));

	वापस xas_error(&xas);
पूर्ण
EXPORT_SYMBOL(__xa_alloc);

/**
 * __xa_alloc_cyclic() - Find somewhere to store this entry in the XArray.
 * @xa: XArray.
 * @id: Poपूर्णांकer to ID.
 * @entry: New entry.
 * @limit: Range of allocated ID.
 * @next: Poपूर्णांकer to next ID to allocate.
 * @gfp: Memory allocation flags.
 *
 * Finds an empty entry in @xa between @limit.min and @limit.max,
 * stores the index पूर्णांकo the @id poपूर्णांकer, then stores the entry at
 * that index.  A concurrent lookup will not see an uninitialised @id.
 * The search क्रम an empty entry will start at @next and will wrap
 * around अगर necessary.
 *
 * Context: Any context.  Expects xa_lock to be held on entry.  May
 * release and reacquire xa_lock अगर @gfp flags permit.
 * Return: 0 अगर the allocation succeeded without wrapping.  1 अगर the
 * allocation succeeded after wrapping, -ENOMEM अगर memory could not be
 * allocated or -EBUSY अगर there are no मुक्त entries in @limit.
 */
पूर्णांक __xa_alloc_cyclic(काष्ठा xarray *xa, u32 *id, व्योम *entry,
		काष्ठा xa_limit limit, u32 *next, gfp_t gfp)
अणु
	u32 min = limit.min;
	पूर्णांक ret;

	limit.min = max(min, *next);
	ret = __xa_alloc(xa, id, entry, limit, gfp);
	अगर ((xa->xa_flags & XA_FLAGS_ALLOC_WRAPPED) && ret == 0) अणु
		xa->xa_flags &= ~XA_FLAGS_ALLOC_WRAPPED;
		ret = 1;
	पूर्ण

	अगर (ret < 0 && limit.min > min) अणु
		limit.min = min;
		ret = __xa_alloc(xa, id, entry, limit, gfp);
		अगर (ret == 0)
			ret = 1;
	पूर्ण

	अगर (ret >= 0) अणु
		*next = *id + 1;
		अगर (*next == 0)
			xa->xa_flags |= XA_FLAGS_ALLOC_WRAPPED;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__xa_alloc_cyclic);

/**
 * __xa_set_mark() - Set this mark on this entry जबतक locked.
 * @xa: XArray.
 * @index: Index of entry.
 * @mark: Mark number.
 *
 * Attempting to set a mark on a %शून्य entry करोes not succeed.
 *
 * Context: Any context.  Expects xa_lock to be held on entry.
 */
व्योम __xa_set_mark(काष्ठा xarray *xa, अचिन्हित दीर्घ index, xa_mark_t mark)
अणु
	XA_STATE(xas, xa, index);
	व्योम *entry = xas_load(&xas);

	अगर (entry)
		xas_set_mark(&xas, mark);
पूर्ण
EXPORT_SYMBOL(__xa_set_mark);

/**
 * __xa_clear_mark() - Clear this mark on this entry जबतक locked.
 * @xa: XArray.
 * @index: Index of entry.
 * @mark: Mark number.
 *
 * Context: Any context.  Expects xa_lock to be held on entry.
 */
व्योम __xa_clear_mark(काष्ठा xarray *xa, अचिन्हित दीर्घ index, xa_mark_t mark)
अणु
	XA_STATE(xas, xa, index);
	व्योम *entry = xas_load(&xas);

	अगर (entry)
		xas_clear_mark(&xas, mark);
पूर्ण
EXPORT_SYMBOL(__xa_clear_mark);

/**
 * xa_get_mark() - Inquire whether this mark is set on this entry.
 * @xa: XArray.
 * @index: Index of entry.
 * @mark: Mark number.
 *
 * This function uses the RCU पढ़ो lock, so the result may be out of date
 * by the समय it वापसs.  If you need the result to be stable, use a lock.
 *
 * Context: Any context.  Takes and releases the RCU lock.
 * Return: True अगर the entry at @index has this mark set, false अगर it करोesn't.
 */
bool xa_get_mark(काष्ठा xarray *xa, अचिन्हित दीर्घ index, xa_mark_t mark)
अणु
	XA_STATE(xas, xa, index);
	व्योम *entry;

	rcu_पढ़ो_lock();
	entry = xas_start(&xas);
	जबतक (xas_get_mark(&xas, mark)) अणु
		अगर (!xa_is_node(entry))
			जाओ found;
		entry = xas_descend(&xas, xa_to_node(entry));
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस false;
 found:
	rcu_पढ़ो_unlock();
	वापस true;
पूर्ण
EXPORT_SYMBOL(xa_get_mark);

/**
 * xa_set_mark() - Set this mark on this entry.
 * @xa: XArray.
 * @index: Index of entry.
 * @mark: Mark number.
 *
 * Attempting to set a mark on a %शून्य entry करोes not succeed.
 *
 * Context: Process context.  Takes and releases the xa_lock.
 */
व्योम xa_set_mark(काष्ठा xarray *xa, अचिन्हित दीर्घ index, xa_mark_t mark)
अणु
	xa_lock(xa);
	__xa_set_mark(xa, index, mark);
	xa_unlock(xa);
पूर्ण
EXPORT_SYMBOL(xa_set_mark);

/**
 * xa_clear_mark() - Clear this mark on this entry.
 * @xa: XArray.
 * @index: Index of entry.
 * @mark: Mark number.
 *
 * Clearing a mark always succeeds.
 *
 * Context: Process context.  Takes and releases the xa_lock.
 */
व्योम xa_clear_mark(काष्ठा xarray *xa, अचिन्हित दीर्घ index, xa_mark_t mark)
अणु
	xa_lock(xa);
	__xa_clear_mark(xa, index, mark);
	xa_unlock(xa);
पूर्ण
EXPORT_SYMBOL(xa_clear_mark);

/**
 * xa_find() - Search the XArray क्रम an entry.
 * @xa: XArray.
 * @indexp: Poपूर्णांकer to an index.
 * @max: Maximum index to search to.
 * @filter: Selection criterion.
 *
 * Finds the entry in @xa which matches the @filter, and has the lowest
 * index that is at least @indexp and no more than @max.
 * If an entry is found, @indexp is updated to be the index of the entry.
 * This function is रक्षित by the RCU पढ़ो lock, so it may not find
 * entries which are being simultaneously added.  It will not वापस an
 * %XA_RETRY_ENTRY; अगर you need to see retry entries, use xas_find().
 *
 * Context: Any context.  Takes and releases the RCU lock.
 * Return: The entry, अगर found, otherwise %शून्य.
 */
व्योम *xa_find(काष्ठा xarray *xa, अचिन्हित दीर्घ *indexp,
			अचिन्हित दीर्घ max, xa_mark_t filter)
अणु
	XA_STATE(xas, xa, *indexp);
	व्योम *entry;

	rcu_पढ़ो_lock();
	करो अणु
		अगर ((__क्रमce अचिन्हित पूर्णांक)filter < XA_MAX_MARKS)
			entry = xas_find_marked(&xas, max, filter);
		अन्यथा
			entry = xas_find(&xas, max);
	पूर्ण जबतक (xas_retry(&xas, entry));
	rcu_पढ़ो_unlock();

	अगर (entry)
		*indexp = xas.xa_index;
	वापस entry;
पूर्ण
EXPORT_SYMBOL(xa_find);

अटल bool xas_sibling(काष्ठा xa_state *xas)
अणु
	काष्ठा xa_node *node = xas->xa_node;
	अचिन्हित दीर्घ mask;

	अगर (!IS_ENABLED(CONFIG_XARRAY_MULTI) || !node)
		वापस false;
	mask = (XA_CHUNK_SIZE << node->shअगरt) - 1;
	वापस (xas->xa_index & mask) >
		((अचिन्हित दीर्घ)xas->xa_offset << node->shअगरt);
पूर्ण

/**
 * xa_find_after() - Search the XArray क्रम a present entry.
 * @xa: XArray.
 * @indexp: Poपूर्णांकer to an index.
 * @max: Maximum index to search to.
 * @filter: Selection criterion.
 *
 * Finds the entry in @xa which matches the @filter and has the lowest
 * index that is above @indexp and no more than @max.
 * If an entry is found, @indexp is updated to be the index of the entry.
 * This function is रक्षित by the RCU पढ़ो lock, so it may miss entries
 * which are being simultaneously added.  It will not वापस an
 * %XA_RETRY_ENTRY; अगर you need to see retry entries, use xas_find().
 *
 * Context: Any context.  Takes and releases the RCU lock.
 * Return: The poपूर्णांकer, अगर found, otherwise %शून्य.
 */
व्योम *xa_find_after(काष्ठा xarray *xa, अचिन्हित दीर्घ *indexp,
			अचिन्हित दीर्घ max, xa_mark_t filter)
अणु
	XA_STATE(xas, xa, *indexp + 1);
	व्योम *entry;

	अगर (xas.xa_index == 0)
		वापस शून्य;

	rcu_पढ़ो_lock();
	क्रम (;;) अणु
		अगर ((__क्रमce अचिन्हित पूर्णांक)filter < XA_MAX_MARKS)
			entry = xas_find_marked(&xas, max, filter);
		अन्यथा
			entry = xas_find(&xas, max);

		अगर (xas_invalid(&xas))
			अवरोध;
		अगर (xas_sibling(&xas))
			जारी;
		अगर (!xas_retry(&xas, entry))
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (entry)
		*indexp = xas.xa_index;
	वापस entry;
पूर्ण
EXPORT_SYMBOL(xa_find_after);

अटल अचिन्हित पूर्णांक xas_extract_present(काष्ठा xa_state *xas, व्योम **dst,
			अचिन्हित दीर्घ max, अचिन्हित पूर्णांक n)
अणु
	व्योम *entry;
	अचिन्हित पूर्णांक i = 0;

	rcu_पढ़ो_lock();
	xas_क्रम_each(xas, entry, max) अणु
		अगर (xas_retry(xas, entry))
			जारी;
		dst[i++] = entry;
		अगर (i == n)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस i;
पूर्ण

अटल अचिन्हित पूर्णांक xas_extract_marked(काष्ठा xa_state *xas, व्योम **dst,
			अचिन्हित दीर्घ max, अचिन्हित पूर्णांक n, xa_mark_t mark)
अणु
	व्योम *entry;
	अचिन्हित पूर्णांक i = 0;

	rcu_पढ़ो_lock();
	xas_क्रम_each_marked(xas, entry, max, mark) अणु
		अगर (xas_retry(xas, entry))
			जारी;
		dst[i++] = entry;
		अगर (i == n)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस i;
पूर्ण

/**
 * xa_extract() - Copy selected entries from the XArray पूर्णांकo a normal array.
 * @xa: The source XArray to copy from.
 * @dst: The buffer to copy entries पूर्णांकo.
 * @start: The first index in the XArray eligible to be selected.
 * @max: The last index in the XArray eligible to be selected.
 * @n: The maximum number of entries to copy.
 * @filter: Selection criterion.
 *
 * Copies up to @n entries that match @filter from the XArray.  The
 * copied entries will have indices between @start and @max, inclusive.
 *
 * The @filter may be an XArray mark value, in which हाल entries which are
 * marked with that mark will be copied.  It may also be %XA_PRESENT, in
 * which हाल all entries which are not %शून्य will be copied.
 *
 * The entries वापसed may not represent a snapshot of the XArray at a
 * moment in समय.  For example, अगर another thपढ़ो stores to index 5, then
 * index 10, calling xa_extract() may वापस the old contents of index 5
 * and the new contents of index 10.  Indices not modअगरied जबतक this
 * function is running will not be skipped.
 *
 * If you need stronger guarantees, holding the xa_lock across calls to this
 * function will prevent concurrent modअगरication.
 *
 * Context: Any context.  Takes and releases the RCU lock.
 * Return: The number of entries copied.
 */
अचिन्हित पूर्णांक xa_extract(काष्ठा xarray *xa, व्योम **dst, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ max, अचिन्हित पूर्णांक n, xa_mark_t filter)
अणु
	XA_STATE(xas, xa, start);

	अगर (!n)
		वापस 0;

	अगर ((__क्रमce अचिन्हित पूर्णांक)filter < XA_MAX_MARKS)
		वापस xas_extract_marked(&xas, dst, max, n, filter);
	वापस xas_extract_present(&xas, dst, max, n);
पूर्ण
EXPORT_SYMBOL(xa_extract);

/**
 * xa_delete_node() - Private पूर्णांकerface क्रम workingset code.
 * @node: Node to be हटाओd from the tree.
 * @update: Function to call to update ancestor nodes.
 *
 * Context: xa_lock must be held on entry and will not be released.
 */
व्योम xa_delete_node(काष्ठा xa_node *node, xa_update_node_t update)
अणु
	काष्ठा xa_state xas = अणु
		.xa = node->array,
		.xa_index = (अचिन्हित दीर्घ)node->offset <<
				(node->shअगरt + XA_CHUNK_SHIFT),
		.xa_shअगरt = node->shअगरt + XA_CHUNK_SHIFT,
		.xa_offset = node->offset,
		.xa_node = xa_parent_locked(node->array, node),
		.xa_update = update,
	पूर्ण;

	xas_store(&xas, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(xa_delete_node);	/* For the benefit of the test suite */

/**
 * xa_destroy() - Free all पूर्णांकernal data काष्ठाures.
 * @xa: XArray.
 *
 * After calling this function, the XArray is empty and has मुक्तd all memory
 * allocated क्रम its पूर्णांकernal data काष्ठाures.  You are responsible क्रम
 * मुक्तing the objects referenced by the XArray.
 *
 * Context: Any context.  Takes and releases the xa_lock, पूर्णांकerrupt-safe.
 */
व्योम xa_destroy(काष्ठा xarray *xa)
अणु
	XA_STATE(xas, xa, 0);
	अचिन्हित दीर्घ flags;
	व्योम *entry;

	xas.xa_node = शून्य;
	xas_lock_irqsave(&xas, flags);
	entry = xa_head_locked(xa);
	RCU_INIT_POINTER(xa->xa_head, शून्य);
	xas_init_marks(&xas);
	अगर (xa_zero_busy(xa))
		xa_mark_clear(xa, XA_FREE_MARK);
	/* lockdep checks we're still holding the lock in xas_मुक्त_nodes() */
	अगर (xa_is_node(entry))
		xas_मुक्त_nodes(&xas, xa_to_node(entry));
	xas_unlock_irqrestore(&xas, flags);
पूर्ण
EXPORT_SYMBOL(xa_destroy);

#अगर_घोषित XA_DEBUG
व्योम xa_dump_node(स्थिर काष्ठा xa_node *node)
अणु
	अचिन्हित i, j;

	अगर (!node)
		वापस;
	अगर ((अचिन्हित दीर्घ)node & 3) अणु
		pr_cont("node %px\n", node);
		वापस;
	पूर्ण

	pr_cont("node %px %s %d parent %px shift %d count %d values %d "
		"array %px list %px %px marks",
		node, node->parent ? "offset" : "max", node->offset,
		node->parent, node->shअगरt, node->count, node->nr_values,
		node->array, node->निजी_list.prev, node->निजी_list.next);
	क्रम (i = 0; i < XA_MAX_MARKS; i++)
		क्रम (j = 0; j < XA_MARK_LONGS; j++)
			pr_cont(" %lx", node->marks[i][j]);
	pr_cont("\n");
पूर्ण

व्योम xa_dump_index(अचिन्हित दीर्घ index, अचिन्हित पूर्णांक shअगरt)
अणु
	अगर (!shअगरt)
		pr_info("%lu: ", index);
	अन्यथा अगर (shअगरt >= BITS_PER_LONG)
		pr_info("0-%lu: ", ~0UL);
	अन्यथा
		pr_info("%lu-%lu: ", index, index | ((1UL << shअगरt) - 1));
पूर्ण

व्योम xa_dump_entry(स्थिर व्योम *entry, अचिन्हित दीर्घ index, अचिन्हित दीर्घ shअगरt)
अणु
	अगर (!entry)
		वापस;

	xa_dump_index(index, shअगरt);

	अगर (xa_is_node(entry)) अणु
		अगर (shअगरt == 0) अणु
			pr_cont("%px\n", entry);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ i;
			काष्ठा xa_node *node = xa_to_node(entry);
			xa_dump_node(node);
			क्रम (i = 0; i < XA_CHUNK_SIZE; i++)
				xa_dump_entry(node->slots[i],
				      index + (i << node->shअगरt), node->shअगरt);
		पूर्ण
	पूर्ण अन्यथा अगर (xa_is_value(entry))
		pr_cont("value %ld (0x%lx) [%px]\n", xa_to_value(entry),
						xa_to_value(entry), entry);
	अन्यथा अगर (!xa_is_पूर्णांकernal(entry))
		pr_cont("%px\n", entry);
	अन्यथा अगर (xa_is_retry(entry))
		pr_cont("retry (%ld)\n", xa_to_पूर्णांकernal(entry));
	अन्यथा अगर (xa_is_sibling(entry))
		pr_cont("sibling (slot %ld)\n", xa_to_sibling(entry));
	अन्यथा अगर (xa_is_zero(entry))
		pr_cont("zero (%ld)\n", xa_to_पूर्णांकernal(entry));
	अन्यथा
		pr_cont("UNKNOWN ENTRY (%px)\n", entry);
पूर्ण

व्योम xa_dump(स्थिर काष्ठा xarray *xa)
अणु
	व्योम *entry = xa->xa_head;
	अचिन्हित पूर्णांक shअगरt = 0;

	pr_info("xarray: %px head %px flags %x marks %d %d %d\n", xa, entry,
			xa->xa_flags, xa_marked(xa, XA_MARK_0),
			xa_marked(xa, XA_MARK_1), xa_marked(xa, XA_MARK_2));
	अगर (xa_is_node(entry))
		shअगरt = xa_to_node(entry)->shअगरt + XA_CHUNK_SHIFT;
	xa_dump_entry(entry, 0, shअगरt);
पूर्ण
#पूर्ण_अगर
