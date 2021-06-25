<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright (c) 2006-2009 VMware, Inc., Palo Alto, CA., USA
 * Copyright (c) 2012 David Airlie <airlied@linux.ie>
 * Copyright (c) 2013 David Herrmann <dh.herrmann@gmail.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#समावेश <drm/drm_mm.h>
#समावेश <drm/drm_vma_manager.h>

/**
 * DOC: vma offset manager
 *
 * The vma-manager is responsible to map arbitrary driver-dependent memory
 * regions पूर्णांकo the linear user address-space. It provides offsets to the
 * caller which can then be used on the address_space of the drm-device. It
 * takes care to not overlap regions, size them appropriately and to not
 * confuse mm-core by inconsistent fake vm_pgoff fields.
 * Drivers shouldn't use this क्रम object placement in VMEM. This manager should
 * only be used to manage mappings पूर्णांकo linear user-space VMs.
 *
 * We use drm_mm as backend to manage object allocations. But it is highly
 * optimized क्रम alloc/मुक्त calls, not lookups. Hence, we use an rb-tree to
 * speed up offset lookups.
 *
 * You must not use multiple offset managers on a single address_space.
 * Otherwise, mm-core will be unable to tear करोwn memory mappings as the VM will
 * no दीर्घer be linear.
 *
 * This offset manager works on page-based addresses. That is, every argument
 * and वापस code (with the exception of drm_vma_node_offset_addr()) is given
 * in number of pages, not number of bytes. That means, object sizes and offsets
 * must always be page-aligned (as usual).
 * If you want to get a valid byte-based user-space address क्रम a given offset,
 * please see drm_vma_node_offset_addr().
 *
 * Additionally to offset management, the vma offset manager also handles access
 * management. For every खोलो-file context that is allowed to access a given
 * node, you must call drm_vma_node_allow(). Otherwise, an mmap() call on this
 * खोलो-file with the offset of the node will fail with -EACCES. To revoke
 * access again, use drm_vma_node_revoke(). However, the caller is responsible
 * क्रम destroying alपढ़ोy existing mappings, अगर required.
 */

/**
 * drm_vma_offset_manager_init - Initialize new offset-manager
 * @mgr: Manager object
 * @page_offset: Offset of available memory area (page-based)
 * @size: Size of available address space range (page-based)
 *
 * Initialize a new offset-manager. The offset and area size available क्रम the
 * manager are given as @page_offset and @size. Both are पूर्णांकerpreted as
 * page-numbers, not bytes.
 *
 * Adding/removing nodes from the manager is locked पूर्णांकernally and रक्षित
 * against concurrent access. However, node allocation and deकाष्ठाion is left
 * क्रम the caller. While calling पूर्णांकo the vma-manager, a given node must
 * always be guaranteed to be referenced.
 */
व्योम drm_vma_offset_manager_init(काष्ठा drm_vma_offset_manager *mgr,
				 अचिन्हित दीर्घ page_offset, अचिन्हित दीर्घ size)
अणु
	rwlock_init(&mgr->vm_lock);
	drm_mm_init(&mgr->vm_addr_space_mm, page_offset, size);
पूर्ण
EXPORT_SYMBOL(drm_vma_offset_manager_init);

/**
 * drm_vma_offset_manager_destroy() - Destroy offset manager
 * @mgr: Manager object
 *
 * Destroy an object manager which was previously created via
 * drm_vma_offset_manager_init(). The caller must हटाओ all allocated nodes
 * beक्रमe destroying the manager. Otherwise, drm_mm will refuse to मुक्त the
 * requested resources.
 *
 * The manager must not be accessed after this function is called.
 */
व्योम drm_vma_offset_manager_destroy(काष्ठा drm_vma_offset_manager *mgr)
अणु
	drm_mm_takeकरोwn(&mgr->vm_addr_space_mm);
पूर्ण
EXPORT_SYMBOL(drm_vma_offset_manager_destroy);

/**
 * drm_vma_offset_lookup_locked() - Find node in offset space
 * @mgr: Manager object
 * @start: Start address क्रम object (page-based)
 * @pages: Size of object (page-based)
 *
 * Find a node given a start address and object size. This वापसs the _best_
 * match क्रम the given node. That is, @start may poपूर्णांक somewhere पूर्णांकo a valid
 * region and the given node will be वापसed, as दीर्घ as the node spans the
 * whole requested area (given the size in number of pages as @pages).
 *
 * Note that beक्रमe lookup the vma offset manager lookup lock must be acquired
 * with drm_vma_offset_lock_lookup(). See there क्रम an example. This can then be
 * used to implement weakly referenced lookups using kref_get_unless_zero().
 *
 * Example:
 *
 * ::
 *
 *     drm_vma_offset_lock_lookup(mgr);
 *     node = drm_vma_offset_lookup_locked(mgr);
 *     अगर (node)
 *         kref_get_unless_zero(container_of(node, sth, entr));
 *     drm_vma_offset_unlock_lookup(mgr);
 *
 * RETURNS:
 * Returns शून्य अगर no suitable node can be found. Otherwise, the best match
 * is वापसed. It's the caller's responsibility to make sure the node doesn't
 * get destroyed beक्रमe the caller can access it.
 */
काष्ठा drm_vma_offset_node *drm_vma_offset_lookup_locked(काष्ठा drm_vma_offset_manager *mgr,
							 अचिन्हित दीर्घ start,
							 अचिन्हित दीर्घ pages)
अणु
	काष्ठा drm_mm_node *node, *best;
	काष्ठा rb_node *iter;
	अचिन्हित दीर्घ offset;

	iter = mgr->vm_addr_space_mm.पूर्णांकerval_tree.rb_root.rb_node;
	best = शून्य;

	जबतक (likely(iter)) अणु
		node = rb_entry(iter, काष्ठा drm_mm_node, rb);
		offset = node->start;
		अगर (start >= offset) अणु
			iter = iter->rb_right;
			best = node;
			अगर (start == offset)
				अवरोध;
		पूर्ण अन्यथा अणु
			iter = iter->rb_left;
		पूर्ण
	पूर्ण

	/* verअगरy that the node spans the requested area */
	अगर (best) अणु
		offset = best->start + best->size;
		अगर (offset < start + pages)
			best = शून्य;
	पूर्ण

	अगर (!best)
		वापस शून्य;

	वापस container_of(best, काष्ठा drm_vma_offset_node, vm_node);
पूर्ण
EXPORT_SYMBOL(drm_vma_offset_lookup_locked);

/**
 * drm_vma_offset_add() - Add offset node to manager
 * @mgr: Manager object
 * @node: Node to be added
 * @pages: Allocation size visible to user-space (in number of pages)
 *
 * Add a node to the offset-manager. If the node was alपढ़ोy added, this करोes
 * nothing and वापस 0. @pages is the size of the object given in number of
 * pages.
 * After this call succeeds, you can access the offset of the node until it
 * is हटाओd again.
 *
 * If this call fails, it is safe to retry the operation or call
 * drm_vma_offset_हटाओ(), anyway. However, no cleanup is required in that
 * हाल.
 *
 * @pages is not required to be the same size as the underlying memory object
 * that you want to map. It only limits the size that user-space can map पूर्णांकo
 * their address space.
 *
 * RETURNS:
 * 0 on success, negative error code on failure.
 */
पूर्णांक drm_vma_offset_add(काष्ठा drm_vma_offset_manager *mgr,
		       काष्ठा drm_vma_offset_node *node, अचिन्हित दीर्घ pages)
अणु
	पूर्णांक ret = 0;

	ग_लिखो_lock(&mgr->vm_lock);

	अगर (!drm_mm_node_allocated(&node->vm_node))
		ret = drm_mm_insert_node(&mgr->vm_addr_space_mm,
					 &node->vm_node, pages);

	ग_लिखो_unlock(&mgr->vm_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_vma_offset_add);

/**
 * drm_vma_offset_हटाओ() - Remove offset node from manager
 * @mgr: Manager object
 * @node: Node to be हटाओd
 *
 * Remove a node from the offset manager. If the node wasn't added beक्रमe, this
 * करोes nothing. After this call वापसs, the offset and size will be 0 until a
 * new offset is allocated via drm_vma_offset_add() again. Helper functions like
 * drm_vma_node_start() and drm_vma_node_offset_addr() will वापस 0 अगर no
 * offset is allocated.
 */
व्योम drm_vma_offset_हटाओ(काष्ठा drm_vma_offset_manager *mgr,
			   काष्ठा drm_vma_offset_node *node)
अणु
	ग_लिखो_lock(&mgr->vm_lock);

	अगर (drm_mm_node_allocated(&node->vm_node)) अणु
		drm_mm_हटाओ_node(&node->vm_node);
		स_रखो(&node->vm_node, 0, माप(node->vm_node));
	पूर्ण

	ग_लिखो_unlock(&mgr->vm_lock);
पूर्ण
EXPORT_SYMBOL(drm_vma_offset_हटाओ);

/**
 * drm_vma_node_allow - Add खोलो-file to list of allowed users
 * @node: Node to modअगरy
 * @tag: Tag of file to हटाओ
 *
 * Add @tag to the list of allowed खोलो-files क्रम this node. If @tag is
 * alपढ़ोy on this list, the ref-count is incremented.
 *
 * The list of allowed-users is preserved across drm_vma_offset_add() and
 * drm_vma_offset_हटाओ() calls. You may even call it अगर the node is currently
 * not added to any offset-manager.
 *
 * You must हटाओ all खोलो-files the same number of बार as you added them
 * beक्रमe destroying the node. Otherwise, you will leak memory.
 *
 * This is locked against concurrent access पूर्णांकernally.
 *
 * RETURNS:
 * 0 on success, negative error code on पूर्णांकernal failure (out-of-mem)
 */
पूर्णांक drm_vma_node_allow(काष्ठा drm_vma_offset_node *node, काष्ठा drm_file *tag)
अणु
	काष्ठा rb_node **iter;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा drm_vma_offset_file *new, *entry;
	पूर्णांक ret = 0;

	/* Pपुनः_स्मृतिate entry to aव्योम atomic allocations below. It is quite
	 * unlikely that an खोलो-file is added twice to a single node so we
	 * करोn't optimize क्रम this हाल. OOM is checked below only अगर the entry
	 * is actually used. */
	new = kदो_स्मृति(माप(*entry), GFP_KERNEL);

	ग_लिखो_lock(&node->vm_lock);

	iter = &node->vm_files.rb_node;

	जबतक (likely(*iter)) अणु
		parent = *iter;
		entry = rb_entry(*iter, काष्ठा drm_vma_offset_file, vm_rb);

		अगर (tag == entry->vm_tag) अणु
			entry->vm_count++;
			जाओ unlock;
		पूर्ण अन्यथा अगर (tag > entry->vm_tag) अणु
			iter = &(*iter)->rb_right;
		पूर्ण अन्यथा अणु
			iter = &(*iter)->rb_left;
		पूर्ण
	पूर्ण

	अगर (!new) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	new->vm_tag = tag;
	new->vm_count = 1;
	rb_link_node(&new->vm_rb, parent, iter);
	rb_insert_color(&new->vm_rb, &node->vm_files);
	new = शून्य;

unlock:
	ग_लिखो_unlock(&node->vm_lock);
	kमुक्त(new);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_vma_node_allow);

/**
 * drm_vma_node_revoke - Remove खोलो-file from list of allowed users
 * @node: Node to modअगरy
 * @tag: Tag of file to हटाओ
 *
 * Decrement the ref-count of @tag in the list of allowed खोलो-files on @node.
 * If the ref-count drops to zero, हटाओ @tag from the list. You must call
 * this once क्रम every drm_vma_node_allow() on @tag.
 *
 * This is locked against concurrent access पूर्णांकernally.
 *
 * If @tag is not on the list, nothing is करोne.
 */
व्योम drm_vma_node_revoke(काष्ठा drm_vma_offset_node *node,
			 काष्ठा drm_file *tag)
अणु
	काष्ठा drm_vma_offset_file *entry;
	काष्ठा rb_node *iter;

	ग_लिखो_lock(&node->vm_lock);

	iter = node->vm_files.rb_node;
	जबतक (likely(iter)) अणु
		entry = rb_entry(iter, काष्ठा drm_vma_offset_file, vm_rb);
		अगर (tag == entry->vm_tag) अणु
			अगर (!--entry->vm_count) अणु
				rb_erase(&entry->vm_rb, &node->vm_files);
				kमुक्त(entry);
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (tag > entry->vm_tag) अणु
			iter = iter->rb_right;
		पूर्ण अन्यथा अणु
			iter = iter->rb_left;
		पूर्ण
	पूर्ण

	ग_लिखो_unlock(&node->vm_lock);
पूर्ण
EXPORT_SYMBOL(drm_vma_node_revoke);

/**
 * drm_vma_node_is_allowed - Check whether an खोलो-file is granted access
 * @node: Node to check
 * @tag: Tag of file to हटाओ
 *
 * Search the list in @node whether @tag is currently on the list of allowed
 * खोलो-files (see drm_vma_node_allow()).
 *
 * This is locked against concurrent access पूर्णांकernally.
 *
 * RETURNS:
 * true अगरf @filp is on the list
 */
bool drm_vma_node_is_allowed(काष्ठा drm_vma_offset_node *node,
			     काष्ठा drm_file *tag)
अणु
	काष्ठा drm_vma_offset_file *entry;
	काष्ठा rb_node *iter;

	पढ़ो_lock(&node->vm_lock);

	iter = node->vm_files.rb_node;
	जबतक (likely(iter)) अणु
		entry = rb_entry(iter, काष्ठा drm_vma_offset_file, vm_rb);
		अगर (tag == entry->vm_tag)
			अवरोध;
		अन्यथा अगर (tag > entry->vm_tag)
			iter = iter->rb_right;
		अन्यथा
			iter = iter->rb_left;
	पूर्ण

	पढ़ो_unlock(&node->vm_lock);

	वापस iter;
पूर्ण
EXPORT_SYMBOL(drm_vma_node_is_allowed);
