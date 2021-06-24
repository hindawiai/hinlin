<शैली गुरु>
#अगर_अघोषित __DRM_VMA_MANAGER_H__
#घोषणा __DRM_VMA_MANAGER_H__

/*
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

#समावेश <drm/drm_mm.h>
#समावेश <linux/mm.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

/* We make up offsets क्रम buffer objects so we can recognize them at
 * mmap समय. pgoff in mmap is an अचिन्हित दीर्घ, so we need to make sure
 * that the faked up offset will fit
 */
#अगर BITS_PER_LONG == 64
#घोषणा DRM_खाता_PAGE_OFFSET_START ((0xFFFFFFFFUL >> PAGE_SHIFT) + 1)
#घोषणा DRM_खाता_PAGE_OFFSET_SIZE ((0xFFFFFFFFUL >> PAGE_SHIFT) * 256)
#अन्यथा
#घोषणा DRM_खाता_PAGE_OFFSET_START ((0xFFFFFFFUL >> PAGE_SHIFT) + 1)
#घोषणा DRM_खाता_PAGE_OFFSET_SIZE ((0xFFFFFFFUL >> PAGE_SHIFT) * 16)
#पूर्ण_अगर

काष्ठा drm_file;

काष्ठा drm_vma_offset_file अणु
	काष्ठा rb_node vm_rb;
	काष्ठा drm_file *vm_tag;
	अचिन्हित दीर्घ vm_count;
पूर्ण;

काष्ठा drm_vma_offset_node अणु
	rwlock_t vm_lock;
	काष्ठा drm_mm_node vm_node;
	काष्ठा rb_root vm_files;
	bool पढ़ोonly:1;
पूर्ण;

काष्ठा drm_vma_offset_manager अणु
	rwlock_t vm_lock;
	काष्ठा drm_mm vm_addr_space_mm;
पूर्ण;

व्योम drm_vma_offset_manager_init(काष्ठा drm_vma_offset_manager *mgr,
				 अचिन्हित दीर्घ page_offset, अचिन्हित दीर्घ size);
व्योम drm_vma_offset_manager_destroy(काष्ठा drm_vma_offset_manager *mgr);

काष्ठा drm_vma_offset_node *drm_vma_offset_lookup_locked(काष्ठा drm_vma_offset_manager *mgr,
							   अचिन्हित दीर्घ start,
							   अचिन्हित दीर्घ pages);
पूर्णांक drm_vma_offset_add(काष्ठा drm_vma_offset_manager *mgr,
		       काष्ठा drm_vma_offset_node *node, अचिन्हित दीर्घ pages);
व्योम drm_vma_offset_हटाओ(काष्ठा drm_vma_offset_manager *mgr,
			   काष्ठा drm_vma_offset_node *node);

पूर्णांक drm_vma_node_allow(काष्ठा drm_vma_offset_node *node, काष्ठा drm_file *tag);
व्योम drm_vma_node_revoke(काष्ठा drm_vma_offset_node *node,
			 काष्ठा drm_file *tag);
bool drm_vma_node_is_allowed(काष्ठा drm_vma_offset_node *node,
			     काष्ठा drm_file *tag);

/**
 * drm_vma_offset_exact_lookup_locked() - Look up node by exact address
 * @mgr: Manager object
 * @start: Start address (page-based, not byte-based)
 * @pages: Size of object (page-based)
 *
 * Same as drm_vma_offset_lookup_locked() but करोes not allow any offset पूर्णांकo the node.
 * It only वापसs the exact object with the given start address.
 *
 * RETURNS:
 * Node at exact start address @start.
 */
अटल अंतरभूत काष्ठा drm_vma_offset_node *
drm_vma_offset_exact_lookup_locked(काष्ठा drm_vma_offset_manager *mgr,
				   अचिन्हित दीर्घ start,
				   अचिन्हित दीर्घ pages)
अणु
	काष्ठा drm_vma_offset_node *node;

	node = drm_vma_offset_lookup_locked(mgr, start, pages);
	वापस (node && node->vm_node.start == start) ? node : शून्य;
पूर्ण

/**
 * drm_vma_offset_lock_lookup() - Lock lookup क्रम extended निजी use
 * @mgr: Manager object
 *
 * Lock VMA manager क्रम extended lookups. Only locked VMA function calls
 * are allowed जबतक holding this lock. All other contexts are blocked from VMA
 * until the lock is released via drm_vma_offset_unlock_lookup().
 *
 * Use this अगर you need to take a reference to the objects वापसed by
 * drm_vma_offset_lookup_locked() beक्रमe releasing this lock again.
 *
 * This lock must not be used क्रम anything अन्यथा than extended lookups. You must
 * not call any other VMA helpers जबतक holding this lock.
 *
 * Note: You're in atomic-context जबतक holding this lock!
 */
अटल अंतरभूत व्योम drm_vma_offset_lock_lookup(काष्ठा drm_vma_offset_manager *mgr)
अणु
	पढ़ो_lock(&mgr->vm_lock);
पूर्ण

/**
 * drm_vma_offset_unlock_lookup() - Unlock lookup क्रम extended निजी use
 * @mgr: Manager object
 *
 * Release lookup-lock. See drm_vma_offset_lock_lookup() क्रम more inक्रमmation.
 */
अटल अंतरभूत व्योम drm_vma_offset_unlock_lookup(काष्ठा drm_vma_offset_manager *mgr)
अणु
	पढ़ो_unlock(&mgr->vm_lock);
पूर्ण

/**
 * drm_vma_node_reset() - Initialize or reset node object
 * @node: Node to initialize or reset
 *
 * Reset a node to its initial state. This must be called beक्रमe using it with
 * any VMA offset manager.
 *
 * This must not be called on an alपढ़ोy allocated node, or you will leak
 * memory.
 */
अटल अंतरभूत व्योम drm_vma_node_reset(काष्ठा drm_vma_offset_node *node)
अणु
	स_रखो(node, 0, माप(*node));
	node->vm_files = RB_ROOT;
	rwlock_init(&node->vm_lock);
पूर्ण

/**
 * drm_vma_node_start() - Return start address क्रम page-based addressing
 * @node: Node to inspect
 *
 * Return the start address of the given node. This can be used as offset पूर्णांकo
 * the linear VM space that is provided by the VMA offset manager. Note that
 * this can only be used क्रम page-based addressing. If you need a proper offset
 * क्रम user-space mappings, you must apply "<< PAGE_SHIFT" or use the
 * drm_vma_node_offset_addr() helper instead.
 *
 * RETURNS:
 * Start address of @node क्रम page-based addressing. 0 अगर the node करोes not
 * have an offset allocated.
 */
अटल अंतरभूत अचिन्हित दीर्घ drm_vma_node_start(स्थिर काष्ठा drm_vma_offset_node *node)
अणु
	वापस node->vm_node.start;
पूर्ण

/**
 * drm_vma_node_size() - Return size (page-based)
 * @node: Node to inspect
 *
 * Return the size as number of pages क्रम the given node. This is the same size
 * that was passed to drm_vma_offset_add(). If no offset is allocated क्रम the
 * node, this is 0.
 *
 * RETURNS:
 * Size of @node as number of pages. 0 अगर the node करोes not have an offset
 * allocated.
 */
अटल अंतरभूत अचिन्हित दीर्घ drm_vma_node_size(काष्ठा drm_vma_offset_node *node)
अणु
	वापस node->vm_node.size;
पूर्ण

/**
 * drm_vma_node_offset_addr() - Return sanitized offset क्रम user-space mmaps
 * @node: Linked offset node
 *
 * Same as drm_vma_node_start() but वापसs the address as a valid offset that
 * can be used क्रम user-space mappings during mmap().
 * This must not be called on unlinked nodes.
 *
 * RETURNS:
 * Offset of @node क्रम byte-based addressing. 0 अगर the node करोes not have an
 * object allocated.
 */
अटल अंतरभूत __u64 drm_vma_node_offset_addr(काष्ठा drm_vma_offset_node *node)
अणु
	वापस ((__u64)node->vm_node.start) << PAGE_SHIFT;
पूर्ण

/**
 * drm_vma_node_unmap() - Unmap offset node
 * @node: Offset node
 * @file_mapping: Address space to unmap @node from
 *
 * Unmap all userspace mappings क्रम a given offset node. The mappings must be
 * associated with the @file_mapping address-space. If no offset exists
 * nothing is करोne.
 *
 * This call is unlocked. The caller must guarantee that drm_vma_offset_हटाओ()
 * is not called on this node concurrently.
 */
अटल अंतरभूत व्योम drm_vma_node_unmap(काष्ठा drm_vma_offset_node *node,
				      काष्ठा address_space *file_mapping)
अणु
	अगर (drm_mm_node_allocated(&node->vm_node))
		unmap_mapping_range(file_mapping,
				    drm_vma_node_offset_addr(node),
				    drm_vma_node_size(node) << PAGE_SHIFT, 1);
पूर्ण

/**
 * drm_vma_node_verअगरy_access() - Access verअगरication helper क्रम TTM
 * @node: Offset node
 * @tag: Tag of file to check
 *
 * This checks whether @tag is granted access to @node. It is the same as
 * drm_vma_node_is_allowed() but suitable as drop-in helper क्रम TTM
 * verअगरy_access() callbacks.
 *
 * RETURNS:
 * 0 अगर access is granted, -EACCES otherwise.
 */
अटल अंतरभूत पूर्णांक drm_vma_node_verअगरy_access(काष्ठा drm_vma_offset_node *node,
					     काष्ठा drm_file *tag)
अणु
	वापस drm_vma_node_is_allowed(node, tag) ? 0 : -EACCES;
पूर्ण

#पूर्ण_अगर /* __DRM_VMA_MANAGER_H__ */
