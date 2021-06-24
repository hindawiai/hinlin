<शैली गुरु>
/*
 * Copyright तऊ 2017 Red Hat
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *
 */
#अगर_अघोषित __DRM_SYNCOBJ_H__
#घोषणा __DRM_SYNCOBJ_H__

#समावेश <linux/dma-fence.h>
#समावेश <linux/dma-fence-chain.h>

काष्ठा drm_file;

/**
 * काष्ठा drm_syncobj - sync object.
 *
 * This काष्ठाure defines a generic sync object which wraps a &dma_fence.
 */
काष्ठा drm_syncobj अणु
	/**
	 * @refcount: Reference count of this object.
	 */
	काष्ठा kref refcount;
	/**
	 * @fence:
	 * शून्य or a poपूर्णांकer to the fence bound to this object.
	 *
	 * This field should not be used directly. Use drm_syncobj_fence_get()
	 * and drm_syncobj_replace_fence() instead.
	 */
	काष्ठा dma_fence __rcu *fence;
	/**
	 * @cb_list: List of callbacks to call when the &fence माला_लो replaced.
	 */
	काष्ठा list_head cb_list;
	/**
	 * @lock: Protects &cb_list and ग_लिखो-locks &fence.
	 */
	spinlock_t lock;
	/**
	 * @file: A file backing क्रम this syncobj.
	 */
	काष्ठा file *file;
पूर्ण;

व्योम drm_syncobj_मुक्त(काष्ठा kref *kref);

/**
 * drm_syncobj_get - acquire a syncobj reference
 * @obj: sync object
 *
 * This acquires an additional reference to @obj. It is illegal to call this
 * without alपढ़ोy holding a reference. No locks required.
 */
अटल अंतरभूत व्योम
drm_syncobj_get(काष्ठा drm_syncobj *obj)
अणु
	kref_get(&obj->refcount);
पूर्ण

/**
 * drm_syncobj_put - release a reference to a sync object.
 * @obj: sync object.
 */
अटल अंतरभूत व्योम
drm_syncobj_put(काष्ठा drm_syncobj *obj)
अणु
	kref_put(&obj->refcount, drm_syncobj_मुक्त);
पूर्ण

/**
 * drm_syncobj_fence_get - get a reference to a fence in a sync object
 * @syncobj: sync object.
 *
 * This acquires additional reference to &drm_syncobj.fence contained in @obj,
 * अगर not शून्य. It is illegal to call this without alपढ़ोy holding a reference.
 * No locks required.
 *
 * Returns:
 * Either the fence of @obj or शून्य अगर there's none.
 */
अटल अंतरभूत काष्ठा dma_fence *
drm_syncobj_fence_get(काष्ठा drm_syncobj *syncobj)
अणु
	काष्ठा dma_fence *fence;

	rcu_पढ़ो_lock();
	fence = dma_fence_get_rcu_safe(&syncobj->fence);
	rcu_पढ़ो_unlock();

	वापस fence;
पूर्ण

काष्ठा drm_syncobj *drm_syncobj_find(काष्ठा drm_file *file_निजी,
				     u32 handle);
व्योम drm_syncobj_add_poपूर्णांक(काष्ठा drm_syncobj *syncobj,
			   काष्ठा dma_fence_chain *chain,
			   काष्ठा dma_fence *fence,
			   uपूर्णांक64_t poपूर्णांक);
व्योम drm_syncobj_replace_fence(काष्ठा drm_syncobj *syncobj,
			       काष्ठा dma_fence *fence);
पूर्णांक drm_syncobj_find_fence(काष्ठा drm_file *file_निजी,
			   u32 handle, u64 poपूर्णांक, u64 flags,
			   काष्ठा dma_fence **fence);
व्योम drm_syncobj_मुक्त(काष्ठा kref *kref);
पूर्णांक drm_syncobj_create(काष्ठा drm_syncobj **out_syncobj, uपूर्णांक32_t flags,
		       काष्ठा dma_fence *fence);
पूर्णांक drm_syncobj_get_handle(काष्ठा drm_file *file_निजी,
			   काष्ठा drm_syncobj *syncobj, u32 *handle);
पूर्णांक drm_syncobj_get_fd(काष्ठा drm_syncobj *syncobj, पूर्णांक *p_fd);

#पूर्ण_अगर
