<शैली गुरु>
/*
 * Copyright 2017 Red Hat
 * Parts ported from amdgpu (fence रुको code).
 * Copyright 2016 Advanced Micro Devices, Inc.
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

/**
 * DOC: Overview
 *
 * DRM synchronisation objects (syncobj, see काष्ठा &drm_syncobj) provide a
 * container क्रम a synchronization primitive which can be used by userspace
 * to explicitly synchronize GPU commands, can be shared between userspace
 * processes, and can be shared between dअगरferent DRM drivers.
 * Their primary use-हाल is to implement Vulkan fences and semaphores.
 * The syncobj userspace API provides ioctls क्रम several operations:
 *
 *  - Creation and deकाष्ठाion of syncobjs
 *  - Import and export of syncobjs to/from a syncobj file descriptor
 *  - Import and export a syncobj's underlying fence to/from a sync file
 *  - Reset a syncobj (set its fence to शून्य)
 *  - Signal a syncobj (set a trivially संकेतed fence)
 *  - Wait क्रम a syncobj's fence to appear and be संकेतed
 *
 * The syncobj userspace API also provides operations to manipulate a syncobj
 * in terms of a समयline of काष्ठा &dma_fence_chain rather than a single
 * काष्ठा &dma_fence, through the following operations:
 *
 *   - Signal a given poपूर्णांक on the समयline
 *   - Wait क्रम a given poपूर्णांक to appear and/or be संकेतed
 *   - Import and export from/to a given poपूर्णांक of a समयline
 *
 * At it's core, a syncobj is simply a wrapper around a poपूर्णांकer to a काष्ठा
 * &dma_fence which may be शून्य.
 * When a syncobj is first created, its poपूर्णांकer is either शून्य or a poपूर्णांकer
 * to an alपढ़ोy संकेतed fence depending on whether the
 * &DRM_SYNCOBJ_CREATE_SIGNALED flag is passed to
 * &DRM_IOCTL_SYNCOBJ_CREATE.
 *
 * If the syncobj is considered as a binary (its state is either संकेतed or
 * unसंकेतed) primitive, when GPU work is enqueued in a DRM driver to संकेत
 * the syncobj, the syncobj's fence is replaced with a fence which will be
 * संकेतed by the completion of that work.
 * If the syncobj is considered as a समयline primitive, when GPU work is
 * enqueued in a DRM driver to संकेत the a given poपूर्णांक of the syncobj, a new
 * काष्ठा &dma_fence_chain poपूर्णांकing to the DRM driver's fence and also
 * poपूर्णांकing to the previous fence that was in the syncobj. The new काष्ठा
 * &dma_fence_chain fence replace the syncobj's fence and will be संकेतed by
 * completion of the DRM driver's work and also any work associated with the
 * fence previously in the syncobj.
 *
 * When GPU work which रुकोs on a syncobj is enqueued in a DRM driver, at the
 * समय the work is enqueued, it रुकोs on the syncobj's fence beक्रमe
 * submitting the work to hardware. That fence is either :
 *
 *    - The syncobj's current fence अगर the syncobj is considered as a binary
 *      primitive.
 *    - The काष्ठा &dma_fence associated with a given poपूर्णांक अगर the syncobj is
 *      considered as a समयline primitive.
 *
 * If the syncobj's fence is NULL or not present in the syncobj's समयline,
 * the enqueue operation is expected to fail.
 *
 * With binary syncobj, all manipulation of the syncobjs's fence happens in
 * terms of the current fence at the समय the ioctl is called by userspace
 * regardless of whether that operation is an immediate host-side operation
 * (संकेत or reset) or or an operation which is enqueued in some driver
 * queue. &DRM_IOCTL_SYNCOBJ_RESET and &DRM_IOCTL_SYNCOBJ_SIGNAL can be used
 * to manipulate a syncobj from the host by resetting its poपूर्णांकer to शून्य or
 * setting its poपूर्णांकer to a fence which is alपढ़ोy संकेतed.
 *
 * With a समयline syncobj, all manipulation of the synobj's fence happens in
 * terms of a u64 value referring to poपूर्णांक in the समयline. See
 * dma_fence_chain_find_seqno() to see how a given poपूर्णांक is found in the
 * समयline.
 *
 * Note that applications should be careful to always use समयline set of
 * ioctl() when dealing with syncobj considered as समयline. Using a binary
 * set of ioctl() with a syncobj considered as समयline could result incorrect
 * synchronization. The use of binary syncobj is supported through the
 * समयline set of ioctl() by using a poपूर्णांक value of 0, this will reproduce
 * the behavior of the binary set of ioctl() (क्रम example replace the
 * syncobj's fence when संकेतing).
 *
 *
 * Host-side रुको on syncobjs
 * --------------------------
 *
 * &DRM_IOCTL_SYNCOBJ_WAIT takes an array of syncobj handles and करोes a
 * host-side रुको on all of the syncobj fences simultaneously.
 * If &DRM_SYNCOBJ_WAIT_FLAGS_WAIT_ALL is set, the रुको ioctl will रुको on
 * all of the syncobj fences to be संकेतed beक्रमe it वापसs.
 * Otherwise, it वापसs once at least one syncobj fence has been संकेतed
 * and the index of a संकेतed fence is written back to the client.
 *
 * Unlike the enqueued GPU work dependencies which fail अगर they see a शून्य
 * fence in a syncobj, अगर &DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT is set,
 * the host-side रुको will first रुको क्रम the syncobj to receive a non-शून्य
 * fence and then रुको on that fence.
 * If &DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT is not set and any one of the
 * syncobjs in the array has a शून्य fence, -EINVAL will be वापसed.
 * Assuming the syncobj starts off with a शून्य fence, this allows a client
 * to करो a host रुको in one thपढ़ो (or process) which रुकोs on GPU work
 * submitted in another thपढ़ो (or process) without having to manually
 * synchronize between the two.
 * This requirement is inherited from the Vulkan fence API.
 *
 * Similarly, &DRM_IOCTL_SYNCOBJ_TIMELINE_WAIT takes an array of syncobj
 * handles as well as an array of u64 poपूर्णांकs and करोes a host-side रुको on all
 * of syncobj fences at the given poपूर्णांकs simultaneously.
 *
 * &DRM_IOCTL_SYNCOBJ_TIMELINE_WAIT also adds the ability to रुको क्रम a given
 * fence to materialize on the समयline without रुकोing क्रम the fence to be
 * संकेतed by using the &DRM_SYNCOBJ_WAIT_FLAGS_WAIT_AVAILABLE flag. This
 * requirement is inherited from the रुको-beक्रमe-संकेत behavior required by
 * the Vulkan समयline semaphore API.
 *
 *
 * Import/export of syncobjs
 * -------------------------
 *
 * &DRM_IOCTL_SYNCOBJ_FD_TO_HANDLE and &DRM_IOCTL_SYNCOBJ_HANDLE_TO_FD
 * provide two mechanisms क्रम import/export of syncobjs.
 *
 * The first lets the client import or export an entire syncobj to a file
 * descriptor.
 * These fd's are opaque and have no other use हाल, except passing the
 * syncobj between processes.
 * All exported file descriptors and any syncobj handles created as a
 * result of importing those file descriptors own a reference to the
 * same underlying काष्ठा &drm_syncobj and the syncobj can be used
 * persistently across all the processes with which it is shared.
 * The syncobj is मुक्तd only once the last reference is dropped.
 * Unlike dma-buf, importing a syncobj creates a new handle (with its own
 * reference) क्रम every import instead of de-duplicating.
 * The primary use-हाल of this persistent import/export is क्रम shared
 * Vulkan fences and semaphores.
 *
 * The second import/export mechanism, which is indicated by
 * &DRM_SYNCOBJ_FD_TO_HANDLE_FLAGS_IMPORT_SYNC_खाता or
 * &DRM_SYNCOBJ_HANDLE_TO_FD_FLAGS_EXPORT_SYNC_खाता lets the client
 * import/export the syncobj's current fence from/to a &sync_file.
 * When a syncobj is exported to a sync file, that sync file wraps the
 * sycnobj's fence at the समय of export and any later संकेत or reset
 * operations on the syncobj will not affect the exported sync file.
 * When a sync file is imported पूर्णांकo a syncobj, the syncobj's fence is set
 * to the fence wrapped by that sync file.
 * Because sync files are immutable, resetting or संकेतing the syncobj
 * will not affect any sync files whose fences have been imported पूर्णांकo the
 * syncobj.
 *
 *
 * Import/export of समयline poपूर्णांकs in समयline syncobjs
 * -----------------------------------------------------
 *
 * &DRM_IOCTL_SYNCOBJ_TRANSFER provides a mechanism to transfer a काष्ठा
 * &dma_fence_chain of a syncobj at a given u64 poपूर्णांक to another u64 poपूर्णांक
 * पूर्णांकo another syncobj.
 *
 * Note that अगर you want to transfer a काष्ठा &dma_fence_chain from a given
 * poपूर्णांक on a समयline syncobj from/पूर्णांकo a binary syncobj, you can use the
 * poपूर्णांक 0 to mean take/replace the fence in the syncobj.
 */

#समावेश <linux/anon_inodes.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sync_file.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_syncobj.h>
#समावेश <drm/drm_utils.h>

#समावेश "drm_internal.h"

काष्ठा syncobj_रुको_entry अणु
	काष्ठा list_head node;
	काष्ठा task_काष्ठा *task;
	काष्ठा dma_fence *fence;
	काष्ठा dma_fence_cb fence_cb;
	u64    poपूर्णांक;
पूर्ण;

अटल व्योम syncobj_रुको_syncobj_func(काष्ठा drm_syncobj *syncobj,
				      काष्ठा syncobj_रुको_entry *रुको);

/**
 * drm_syncobj_find - lookup and reference a sync object.
 * @file_निजी: drm file निजी poपूर्णांकer
 * @handle: sync object handle to lookup.
 *
 * Returns a reference to the syncobj poपूर्णांकed to by handle or शून्य. The
 * reference must be released by calling drm_syncobj_put().
 */
काष्ठा drm_syncobj *drm_syncobj_find(काष्ठा drm_file *file_निजी,
				     u32 handle)
अणु
	काष्ठा drm_syncobj *syncobj;

	spin_lock(&file_निजी->syncobj_table_lock);

	/* Check अगर we currently have a reference on the object */
	syncobj = idr_find(&file_निजी->syncobj_idr, handle);
	अगर (syncobj)
		drm_syncobj_get(syncobj);

	spin_unlock(&file_निजी->syncobj_table_lock);

	वापस syncobj;
पूर्ण
EXPORT_SYMBOL(drm_syncobj_find);

अटल व्योम drm_syncobj_fence_add_रुको(काष्ठा drm_syncobj *syncobj,
				       काष्ठा syncobj_रुको_entry *रुको)
अणु
	काष्ठा dma_fence *fence;

	अगर (रुको->fence)
		वापस;

	spin_lock(&syncobj->lock);
	/* We've alपढ़ोy tried once to get a fence and failed.  Now that we
	 * have the lock, try one more समय just to be sure we करोn't add a
	 * callback when a fence has alपढ़ोy been set.
	 */
	fence = dma_fence_get(rcu_dereference_रक्षित(syncobj->fence, 1));
	अगर (!fence || dma_fence_chain_find_seqno(&fence, रुको->poपूर्णांक)) अणु
		dma_fence_put(fence);
		list_add_tail(&रुको->node, &syncobj->cb_list);
	पूर्ण अन्यथा अगर (!fence) अणु
		रुको->fence = dma_fence_get_stub();
	पूर्ण अन्यथा अणु
		रुको->fence = fence;
	पूर्ण
	spin_unlock(&syncobj->lock);
पूर्ण

अटल व्योम drm_syncobj_हटाओ_रुको(काष्ठा drm_syncobj *syncobj,
				    काष्ठा syncobj_रुको_entry *रुको)
अणु
	अगर (!रुको->node.next)
		वापस;

	spin_lock(&syncobj->lock);
	list_del_init(&रुको->node);
	spin_unlock(&syncobj->lock);
पूर्ण

/**
 * drm_syncobj_add_poपूर्णांक - add new समयline poपूर्णांक to the syncobj
 * @syncobj: sync object to add समयline poपूर्णांक करो
 * @chain: chain node to use to add the poपूर्णांक
 * @fence: fence to encapsulate in the chain node
 * @poपूर्णांक: sequence number to use क्रम the poपूर्णांक
 *
 * Add the chain node as new समयline poपूर्णांक to the syncobj.
 */
व्योम drm_syncobj_add_poपूर्णांक(काष्ठा drm_syncobj *syncobj,
			   काष्ठा dma_fence_chain *chain,
			   काष्ठा dma_fence *fence,
			   uपूर्णांक64_t poपूर्णांक)
अणु
	काष्ठा syncobj_रुको_entry *cur, *पंचांगp;
	काष्ठा dma_fence *prev;

	dma_fence_get(fence);

	spin_lock(&syncobj->lock);

	prev = drm_syncobj_fence_get(syncobj);
	/* You are adding an unorder poपूर्णांक to समयline, which could cause payload वापसed from query_ioctl is 0! */
	अगर (prev && prev->seqno >= poपूर्णांक)
		DRM_DEBUG("You are adding an unorder point to timeline!\n");
	dma_fence_chain_init(chain, prev, fence, poपूर्णांक);
	rcu_assign_poपूर्णांकer(syncobj->fence, &chain->base);

	list_क्रम_each_entry_safe(cur, पंचांगp, &syncobj->cb_list, node)
		syncobj_रुको_syncobj_func(syncobj, cur);
	spin_unlock(&syncobj->lock);

	/* Walk the chain once to trigger garbage collection */
	dma_fence_chain_क्रम_each(fence, prev);
	dma_fence_put(prev);
पूर्ण
EXPORT_SYMBOL(drm_syncobj_add_poपूर्णांक);

/**
 * drm_syncobj_replace_fence - replace fence in a sync object.
 * @syncobj: Sync object to replace fence in
 * @fence: fence to install in sync file.
 *
 * This replaces the fence on a sync object.
 */
व्योम drm_syncobj_replace_fence(काष्ठा drm_syncobj *syncobj,
			       काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence *old_fence;
	काष्ठा syncobj_रुको_entry *cur, *पंचांगp;

	अगर (fence)
		dma_fence_get(fence);

	spin_lock(&syncobj->lock);

	old_fence = rcu_dereference_रक्षित(syncobj->fence,
					      lockdep_is_held(&syncobj->lock));
	rcu_assign_poपूर्णांकer(syncobj->fence, fence);

	अगर (fence != old_fence) अणु
		list_क्रम_each_entry_safe(cur, पंचांगp, &syncobj->cb_list, node)
			syncobj_रुको_syncobj_func(syncobj, cur);
	पूर्ण

	spin_unlock(&syncobj->lock);

	dma_fence_put(old_fence);
पूर्ण
EXPORT_SYMBOL(drm_syncobj_replace_fence);

/**
 * drm_syncobj_assign_null_handle - assign a stub fence to the sync object
 * @syncobj: sync object to assign the fence on
 *
 * Assign a alपढ़ोy संकेतed stub fence to the sync object.
 */
अटल पूर्णांक drm_syncobj_assign_null_handle(काष्ठा drm_syncobj *syncobj)
अणु
	काष्ठा dma_fence *fence = dma_fence_allocate_निजी_stub();

	अगर (IS_ERR(fence))
		वापस PTR_ERR(fence);

	drm_syncobj_replace_fence(syncobj, fence);
	dma_fence_put(fence);
	वापस 0;
पूर्ण

/* 5s शेष क्रम रुको submission */
#घोषणा DRM_SYNCOBJ_WAIT_FOR_SUBMIT_TIMEOUT 5000000000ULL
/**
 * drm_syncobj_find_fence - lookup and reference the fence in a sync object
 * @file_निजी: drm file निजी poपूर्णांकer
 * @handle: sync object handle to lookup.
 * @poपूर्णांक: समयline poपूर्णांक
 * @flags: DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT or not
 * @fence: out parameter क्रम the fence
 *
 * This is just a convenience function that combines drm_syncobj_find() and
 * drm_syncobj_fence_get().
 *
 * Returns 0 on success or a negative error value on failure. On success @fence
 * contains a reference to the fence, which must be released by calling
 * dma_fence_put().
 */
पूर्णांक drm_syncobj_find_fence(काष्ठा drm_file *file_निजी,
			   u32 handle, u64 poपूर्णांक, u64 flags,
			   काष्ठा dma_fence **fence)
अणु
	काष्ठा drm_syncobj *syncobj = drm_syncobj_find(file_निजी, handle);
	काष्ठा syncobj_रुको_entry रुको;
	u64 समयout = nsecs_to_jअगरfies64(DRM_SYNCOBJ_WAIT_FOR_SUBMIT_TIMEOUT);
	पूर्णांक ret;

	अगर (!syncobj)
		वापस -ENOENT;

	/* Waiting क्रम userspace with locks help is illegal cause that can
	 * trivial deadlock with page faults क्रम example. Make lockdep complain
	 * about it early on.
	 */
	अगर (flags & DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT) अणु
		might_sleep();
		lockdep_निश्चित_none_held_once();
	पूर्ण

	*fence = drm_syncobj_fence_get(syncobj);

	अगर (*fence) अणु
		ret = dma_fence_chain_find_seqno(fence, poपूर्णांक);
		अगर (!ret)
			जाओ out;
		dma_fence_put(*fence);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	अगर (!(flags & DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT))
		जाओ out;

	स_रखो(&रुको, 0, माप(रुको));
	रुको.task = current;
	रुको.poपूर्णांक = poपूर्णांक;
	drm_syncobj_fence_add_रुको(syncobj, &रुको);

	करो अणु
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (रुको.fence) अणु
			ret = 0;
			अवरोध;
		पूर्ण
                अगर (समयout == 0) अणु
                        ret = -ETIME;
                        अवरोध;
                पूर्ण

		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण

                समयout = schedule_समयout(समयout);
	पूर्ण जबतक (1);

	__set_current_state(TASK_RUNNING);
	*fence = रुको.fence;

	अगर (रुको.node.next)
		drm_syncobj_हटाओ_रुको(syncobj, &रुको);

out:
	drm_syncobj_put(syncobj);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_syncobj_find_fence);

/**
 * drm_syncobj_मुक्त - मुक्त a sync object.
 * @kref: kref to मुक्त.
 *
 * Only to be called from kref_put in drm_syncobj_put.
 */
व्योम drm_syncobj_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा drm_syncobj *syncobj = container_of(kref,
						   काष्ठा drm_syncobj,
						   refcount);
	drm_syncobj_replace_fence(syncobj, शून्य);
	kमुक्त(syncobj);
पूर्ण
EXPORT_SYMBOL(drm_syncobj_मुक्त);

/**
 * drm_syncobj_create - create a new syncobj
 * @out_syncobj: वापसed syncobj
 * @flags: DRM_SYNCOBJ_* flags
 * @fence: अगर non-शून्य, the syncobj will represent this fence
 *
 * This is the first function to create a sync object. After creating, drivers
 * probably want to make it available to userspace, either through
 * drm_syncobj_get_handle() or drm_syncobj_get_fd().
 *
 * Returns 0 on success or a negative error value on failure.
 */
पूर्णांक drm_syncobj_create(काष्ठा drm_syncobj **out_syncobj, uपूर्णांक32_t flags,
		       काष्ठा dma_fence *fence)
अणु
	पूर्णांक ret;
	काष्ठा drm_syncobj *syncobj;

	syncobj = kzalloc(माप(काष्ठा drm_syncobj), GFP_KERNEL);
	अगर (!syncobj)
		वापस -ENOMEM;

	kref_init(&syncobj->refcount);
	INIT_LIST_HEAD(&syncobj->cb_list);
	spin_lock_init(&syncobj->lock);

	अगर (flags & DRM_SYNCOBJ_CREATE_SIGNALED) अणु
		ret = drm_syncobj_assign_null_handle(syncobj);
		अगर (ret < 0) अणु
			drm_syncobj_put(syncobj);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (fence)
		drm_syncobj_replace_fence(syncobj, fence);

	*out_syncobj = syncobj;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_syncobj_create);

/**
 * drm_syncobj_get_handle - get a handle from a syncobj
 * @file_निजी: drm file निजी poपूर्णांकer
 * @syncobj: Sync object to export
 * @handle: out parameter with the new handle
 *
 * Exports a sync object created with drm_syncobj_create() as a handle on
 * @file_निजी to userspace.
 *
 * Returns 0 on success or a negative error value on failure.
 */
पूर्णांक drm_syncobj_get_handle(काष्ठा drm_file *file_निजी,
			   काष्ठा drm_syncobj *syncobj, u32 *handle)
अणु
	पूर्णांक ret;

	/* take a reference to put in the idr */
	drm_syncobj_get(syncobj);

	idr_preload(GFP_KERNEL);
	spin_lock(&file_निजी->syncobj_table_lock);
	ret = idr_alloc(&file_निजी->syncobj_idr, syncobj, 1, 0, GFP_NOWAIT);
	spin_unlock(&file_निजी->syncobj_table_lock);

	idr_preload_end();

	अगर (ret < 0) अणु
		drm_syncobj_put(syncobj);
		वापस ret;
	पूर्ण

	*handle = ret;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_syncobj_get_handle);

अटल पूर्णांक drm_syncobj_create_as_handle(काष्ठा drm_file *file_निजी,
					u32 *handle, uपूर्णांक32_t flags)
अणु
	पूर्णांक ret;
	काष्ठा drm_syncobj *syncobj;

	ret = drm_syncobj_create(&syncobj, flags, शून्य);
	अगर (ret)
		वापस ret;

	ret = drm_syncobj_get_handle(file_निजी, syncobj, handle);
	drm_syncobj_put(syncobj);
	वापस ret;
पूर्ण

अटल पूर्णांक drm_syncobj_destroy(काष्ठा drm_file *file_निजी,
			       u32 handle)
अणु
	काष्ठा drm_syncobj *syncobj;

	spin_lock(&file_निजी->syncobj_table_lock);
	syncobj = idr_हटाओ(&file_निजी->syncobj_idr, handle);
	spin_unlock(&file_निजी->syncobj_table_lock);

	अगर (!syncobj)
		वापस -EINVAL;

	drm_syncobj_put(syncobj);
	वापस 0;
पूर्ण

अटल पूर्णांक drm_syncobj_file_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_syncobj *syncobj = file->निजी_data;

	drm_syncobj_put(syncobj);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations drm_syncobj_file_fops = अणु
	.release = drm_syncobj_file_release,
पूर्ण;

/**
 * drm_syncobj_get_fd - get a file descriptor from a syncobj
 * @syncobj: Sync object to export
 * @p_fd: out parameter with the new file descriptor
 *
 * Exports a sync object created with drm_syncobj_create() as a file descriptor.
 *
 * Returns 0 on success or a negative error value on failure.
 */
पूर्णांक drm_syncobj_get_fd(काष्ठा drm_syncobj *syncobj, पूर्णांक *p_fd)
अणु
	काष्ठा file *file;
	पूर्णांक fd;

	fd = get_unused_fd_flags(O_CLOEXEC);
	अगर (fd < 0)
		वापस fd;

	file = anon_inode_getfile("syncobj_file",
				  &drm_syncobj_file_fops,
				  syncobj, 0);
	अगर (IS_ERR(file)) अणु
		put_unused_fd(fd);
		वापस PTR_ERR(file);
	पूर्ण

	drm_syncobj_get(syncobj);
	fd_install(fd, file);

	*p_fd = fd;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_syncobj_get_fd);

अटल पूर्णांक drm_syncobj_handle_to_fd(काष्ठा drm_file *file_निजी,
				    u32 handle, पूर्णांक *p_fd)
अणु
	काष्ठा drm_syncobj *syncobj = drm_syncobj_find(file_निजी, handle);
	पूर्णांक ret;

	अगर (!syncobj)
		वापस -EINVAL;

	ret = drm_syncobj_get_fd(syncobj, p_fd);
	drm_syncobj_put(syncobj);
	वापस ret;
पूर्ण

अटल पूर्णांक drm_syncobj_fd_to_handle(काष्ठा drm_file *file_निजी,
				    पूर्णांक fd, u32 *handle)
अणु
	काष्ठा drm_syncobj *syncobj;
	काष्ठा fd f = fdget(fd);
	पूर्णांक ret;

	अगर (!f.file)
		वापस -EINVAL;

	अगर (f.file->f_op != &drm_syncobj_file_fops) अणु
		fdput(f);
		वापस -EINVAL;
	पूर्ण

	/* take a reference to put in the idr */
	syncobj = f.file->निजी_data;
	drm_syncobj_get(syncobj);

	idr_preload(GFP_KERNEL);
	spin_lock(&file_निजी->syncobj_table_lock);
	ret = idr_alloc(&file_निजी->syncobj_idr, syncobj, 1, 0, GFP_NOWAIT);
	spin_unlock(&file_निजी->syncobj_table_lock);
	idr_preload_end();

	अगर (ret > 0) अणु
		*handle = ret;
		ret = 0;
	पूर्ण अन्यथा
		drm_syncobj_put(syncobj);

	fdput(f);
	वापस ret;
पूर्ण

अटल पूर्णांक drm_syncobj_import_sync_file_fence(काष्ठा drm_file *file_निजी,
					      पूर्णांक fd, पूर्णांक handle)
अणु
	काष्ठा dma_fence *fence = sync_file_get_fence(fd);
	काष्ठा drm_syncobj *syncobj;

	अगर (!fence)
		वापस -EINVAL;

	syncobj = drm_syncobj_find(file_निजी, handle);
	अगर (!syncobj) अणु
		dma_fence_put(fence);
		वापस -ENOENT;
	पूर्ण

	drm_syncobj_replace_fence(syncobj, fence);
	dma_fence_put(fence);
	drm_syncobj_put(syncobj);
	वापस 0;
पूर्ण

अटल पूर्णांक drm_syncobj_export_sync_file(काष्ठा drm_file *file_निजी,
					पूर्णांक handle, पूर्णांक *p_fd)
अणु
	पूर्णांक ret;
	काष्ठा dma_fence *fence;
	काष्ठा sync_file *sync_file;
	पूर्णांक fd = get_unused_fd_flags(O_CLOEXEC);

	अगर (fd < 0)
		वापस fd;

	ret = drm_syncobj_find_fence(file_निजी, handle, 0, 0, &fence);
	अगर (ret)
		जाओ err_put_fd;

	sync_file = sync_file_create(fence);

	dma_fence_put(fence);

	अगर (!sync_file) अणु
		ret = -EINVAL;
		जाओ err_put_fd;
	पूर्ण

	fd_install(fd, sync_file->file);

	*p_fd = fd;
	वापस 0;
err_put_fd:
	put_unused_fd(fd);
	वापस ret;
पूर्ण
/**
 * drm_syncobj_खोलो - initalizes syncobj file-निजी काष्ठाures at devnode खोलो समय
 * @file_निजी: drm file-निजी काष्ठाure to set up
 *
 * Called at device खोलो समय, sets up the काष्ठाure क्रम handling refcounting
 * of sync objects.
 */
व्योम
drm_syncobj_खोलो(काष्ठा drm_file *file_निजी)
अणु
	idr_init_base(&file_निजी->syncobj_idr, 1);
	spin_lock_init(&file_निजी->syncobj_table_lock);
पूर्ण

अटल पूर्णांक
drm_syncobj_release_handle(पूर्णांक id, व्योम *ptr, व्योम *data)
अणु
	काष्ठा drm_syncobj *syncobj = ptr;

	drm_syncobj_put(syncobj);
	वापस 0;
पूर्ण

/**
 * drm_syncobj_release - release file-निजी sync object resources
 * @file_निजी: drm file-निजी काष्ठाure to clean up
 *
 * Called at बंद समय when the filp is going away.
 *
 * Releases any reमुख्यing references on objects by this filp.
 */
व्योम
drm_syncobj_release(काष्ठा drm_file *file_निजी)
अणु
	idr_क्रम_each(&file_निजी->syncobj_idr,
		     &drm_syncobj_release_handle, file_निजी);
	idr_destroy(&file_निजी->syncobj_idr);
पूर्ण

पूर्णांक
drm_syncobj_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_निजी)
अणु
	काष्ठा drm_syncobj_create *args = data;

	अगर (!drm_core_check_feature(dev, DRIVER_SYNCOBJ))
		वापस -EOPNOTSUPP;

	/* no valid flags yet */
	अगर (args->flags & ~DRM_SYNCOBJ_CREATE_SIGNALED)
		वापस -EINVAL;

	वापस drm_syncobj_create_as_handle(file_निजी,
					    &args->handle, args->flags);
पूर्ण

पूर्णांक
drm_syncobj_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_निजी)
अणु
	काष्ठा drm_syncobj_destroy *args = data;

	अगर (!drm_core_check_feature(dev, DRIVER_SYNCOBJ))
		वापस -EOPNOTSUPP;

	/* make sure padding is empty */
	अगर (args->pad)
		वापस -EINVAL;
	वापस drm_syncobj_destroy(file_निजी, args->handle);
पूर्ण

पूर्णांक
drm_syncobj_handle_to_fd_ioctl(काष्ठा drm_device *dev, व्योम *data,
				   काष्ठा drm_file *file_निजी)
अणु
	काष्ठा drm_syncobj_handle *args = data;

	अगर (!drm_core_check_feature(dev, DRIVER_SYNCOBJ))
		वापस -EOPNOTSUPP;

	अगर (args->pad)
		वापस -EINVAL;

	अगर (args->flags != 0 &&
	    args->flags != DRM_SYNCOBJ_HANDLE_TO_FD_FLAGS_EXPORT_SYNC_खाता)
		वापस -EINVAL;

	अगर (args->flags & DRM_SYNCOBJ_HANDLE_TO_FD_FLAGS_EXPORT_SYNC_खाता)
		वापस drm_syncobj_export_sync_file(file_निजी, args->handle,
						    &args->fd);

	वापस drm_syncobj_handle_to_fd(file_निजी, args->handle,
					&args->fd);
पूर्ण

पूर्णांक
drm_syncobj_fd_to_handle_ioctl(काष्ठा drm_device *dev, व्योम *data,
				   काष्ठा drm_file *file_निजी)
अणु
	काष्ठा drm_syncobj_handle *args = data;

	अगर (!drm_core_check_feature(dev, DRIVER_SYNCOBJ))
		वापस -EOPNOTSUPP;

	अगर (args->pad)
		वापस -EINVAL;

	अगर (args->flags != 0 &&
	    args->flags != DRM_SYNCOBJ_FD_TO_HANDLE_FLAGS_IMPORT_SYNC_खाता)
		वापस -EINVAL;

	अगर (args->flags & DRM_SYNCOBJ_FD_TO_HANDLE_FLAGS_IMPORT_SYNC_खाता)
		वापस drm_syncobj_import_sync_file_fence(file_निजी,
							  args->fd,
							  args->handle);

	वापस drm_syncobj_fd_to_handle(file_निजी, args->fd,
					&args->handle);
पूर्ण

अटल पूर्णांक drm_syncobj_transfer_to_समयline(काष्ठा drm_file *file_निजी,
					    काष्ठा drm_syncobj_transfer *args)
अणु
	काष्ठा drm_syncobj *समयline_syncobj = शून्य;
	काष्ठा dma_fence *fence;
	काष्ठा dma_fence_chain *chain;
	पूर्णांक ret;

	समयline_syncobj = drm_syncobj_find(file_निजी, args->dst_handle);
	अगर (!समयline_syncobj) अणु
		वापस -ENOENT;
	पूर्ण
	ret = drm_syncobj_find_fence(file_निजी, args->src_handle,
				     args->src_poपूर्णांक, args->flags,
				     &fence);
	अगर (ret)
		जाओ err;
	chain = kzalloc(माप(काष्ठा dma_fence_chain), GFP_KERNEL);
	अगर (!chain) अणु
		ret = -ENOMEM;
		जाओ err1;
	पूर्ण
	drm_syncobj_add_poपूर्णांक(समयline_syncobj, chain, fence, args->dst_poपूर्णांक);
err1:
	dma_fence_put(fence);
err:
	drm_syncobj_put(समयline_syncobj);

	वापस ret;
पूर्ण

अटल पूर्णांक
drm_syncobj_transfer_to_binary(काष्ठा drm_file *file_निजी,
			       काष्ठा drm_syncobj_transfer *args)
अणु
	काष्ठा drm_syncobj *binary_syncobj = शून्य;
	काष्ठा dma_fence *fence;
	पूर्णांक ret;

	binary_syncobj = drm_syncobj_find(file_निजी, args->dst_handle);
	अगर (!binary_syncobj)
		वापस -ENOENT;
	ret = drm_syncobj_find_fence(file_निजी, args->src_handle,
				     args->src_poपूर्णांक, args->flags, &fence);
	अगर (ret)
		जाओ err;
	drm_syncobj_replace_fence(binary_syncobj, fence);
	dma_fence_put(fence);
err:
	drm_syncobj_put(binary_syncobj);

	वापस ret;
पूर्ण
पूर्णांक
drm_syncobj_transfer_ioctl(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_निजी)
अणु
	काष्ठा drm_syncobj_transfer *args = data;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_SYNCOBJ_TIMELINE))
		वापस -EOPNOTSUPP;

	अगर (args->pad)
		वापस -EINVAL;

	अगर (args->dst_poपूर्णांक)
		ret = drm_syncobj_transfer_to_समयline(file_निजी, args);
	अन्यथा
		ret = drm_syncobj_transfer_to_binary(file_निजी, args);

	वापस ret;
पूर्ण

अटल व्योम syncobj_रुको_fence_func(काष्ठा dma_fence *fence,
				    काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा syncobj_रुको_entry *रुको =
		container_of(cb, काष्ठा syncobj_रुको_entry, fence_cb);

	wake_up_process(रुको->task);
पूर्ण

अटल व्योम syncobj_रुको_syncobj_func(काष्ठा drm_syncobj *syncobj,
				      काष्ठा syncobj_रुको_entry *रुको)
अणु
	काष्ठा dma_fence *fence;

	/* This happens inside the syncobj lock */
	fence = rcu_dereference_रक्षित(syncobj->fence,
					  lockdep_is_held(&syncobj->lock));
	dma_fence_get(fence);
	अगर (!fence || dma_fence_chain_find_seqno(&fence, रुको->poपूर्णांक)) अणु
		dma_fence_put(fence);
		वापस;
	पूर्ण अन्यथा अगर (!fence) अणु
		रुको->fence = dma_fence_get_stub();
	पूर्ण अन्यथा अणु
		रुको->fence = fence;
	पूर्ण

	wake_up_process(रुको->task);
	list_del_init(&रुको->node);
पूर्ण

अटल चिन्हित दीर्घ drm_syncobj_array_रुको_समयout(काष्ठा drm_syncobj **syncobjs,
						  व्योम __user *user_poपूर्णांकs,
						  uपूर्णांक32_t count,
						  uपूर्णांक32_t flags,
						  चिन्हित दीर्घ समयout,
						  uपूर्णांक32_t *idx)
अणु
	काष्ठा syncobj_रुको_entry *entries;
	काष्ठा dma_fence *fence;
	uपूर्णांक64_t *poपूर्णांकs;
	uपूर्णांक32_t संकेतed_count, i;

	अगर (flags & DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT)
		lockdep_निश्चित_none_held_once();

	poपूर्णांकs = kदो_स्मृति_array(count, माप(*poपूर्णांकs), GFP_KERNEL);
	अगर (poपूर्णांकs == शून्य)
		वापस -ENOMEM;

	अगर (!user_poपूर्णांकs) अणु
		स_रखो(poपूर्णांकs, 0, count * माप(uपूर्णांक64_t));

	पूर्ण अन्यथा अगर (copy_from_user(poपूर्णांकs, user_poपूर्णांकs,
				  माप(uपूर्णांक64_t) * count)) अणु
		समयout = -EFAULT;
		जाओ err_मुक्त_poपूर्णांकs;
	पूर्ण

	entries = kसुस्मृति(count, माप(*entries), GFP_KERNEL);
	अगर (!entries) अणु
		समयout = -ENOMEM;
		जाओ err_मुक्त_poपूर्णांकs;
	पूर्ण
	/* Walk the list of sync objects and initialize entries.  We करो
	 * this up-front so that we can properly वापस -EINVAL अगर there is
	 * a syncobj with a missing fence and then never have the chance of
	 * वापसing -EINVAL again.
	 */
	संकेतed_count = 0;
	क्रम (i = 0; i < count; ++i) अणु
		काष्ठा dma_fence *fence;

		entries[i].task = current;
		entries[i].poपूर्णांक = poपूर्णांकs[i];
		fence = drm_syncobj_fence_get(syncobjs[i]);
		अगर (!fence || dma_fence_chain_find_seqno(&fence, poपूर्णांकs[i])) अणु
			dma_fence_put(fence);
			अगर (flags & DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT) अणु
				जारी;
			पूर्ण अन्यथा अणु
				समयout = -EINVAL;
				जाओ cleanup_entries;
			पूर्ण
		पूर्ण

		अगर (fence)
			entries[i].fence = fence;
		अन्यथा
			entries[i].fence = dma_fence_get_stub();

		अगर ((flags & DRM_SYNCOBJ_WAIT_FLAGS_WAIT_AVAILABLE) ||
		    dma_fence_is_संकेतed(entries[i].fence)) अणु
			अगर (संकेतed_count == 0 && idx)
				*idx = i;
			संकेतed_count++;
		पूर्ण
	पूर्ण

	अगर (संकेतed_count == count ||
	    (संकेतed_count > 0 &&
	     !(flags & DRM_SYNCOBJ_WAIT_FLAGS_WAIT_ALL)))
		जाओ cleanup_entries;

	/* There's a very annoying laxness in the dma_fence API here, in
	 * that backends are not required to स्वतःmatically report when a
	 * fence is संकेतed prior to fence->ops->enable_संकेतing() being
	 * called.  So here अगर we fail to match संकेतed_count, we need to
	 * fallthough and try a 0 समयout रुको!
	 */

	अगर (flags & DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT) अणु
		क्रम (i = 0; i < count; ++i)
			drm_syncobj_fence_add_रुको(syncobjs[i], &entries[i]);
	पूर्ण

	करो अणु
		set_current_state(TASK_INTERRUPTIBLE);

		संकेतed_count = 0;
		क्रम (i = 0; i < count; ++i) अणु
			fence = entries[i].fence;
			अगर (!fence)
				जारी;

			अगर ((flags & DRM_SYNCOBJ_WAIT_FLAGS_WAIT_AVAILABLE) ||
			    dma_fence_is_संकेतed(fence) ||
			    (!entries[i].fence_cb.func &&
			     dma_fence_add_callback(fence,
						    &entries[i].fence_cb,
						    syncobj_रुको_fence_func))) अणु
				/* The fence has been संकेतed */
				अगर (flags & DRM_SYNCOBJ_WAIT_FLAGS_WAIT_ALL) अणु
					संकेतed_count++;
				पूर्ण अन्यथा अणु
					अगर (idx)
						*idx = i;
					जाओ करोne_रुकोing;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (संकेतed_count == count)
			जाओ करोne_रुकोing;

		अगर (समयout == 0) अणु
			समयout = -ETIME;
			जाओ करोne_रुकोing;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			समयout = -ERESTARTSYS;
			जाओ करोne_रुकोing;
		पूर्ण

		समयout = schedule_समयout(समयout);
	पूर्ण जबतक (1);

करोne_रुकोing:
	__set_current_state(TASK_RUNNING);

cleanup_entries:
	क्रम (i = 0; i < count; ++i) अणु
		drm_syncobj_हटाओ_रुको(syncobjs[i], &entries[i]);
		अगर (entries[i].fence_cb.func)
			dma_fence_हटाओ_callback(entries[i].fence,
						  &entries[i].fence_cb);
		dma_fence_put(entries[i].fence);
	पूर्ण
	kमुक्त(entries);

err_मुक्त_poपूर्णांकs:
	kमुक्त(poपूर्णांकs);

	वापस समयout;
पूर्ण

/**
 * drm_समयout_असल_to_jअगरfies - calculate jअगरfies समयout from असलolute value
 *
 * @समयout_nsec: समयout nsec component in ns, 0 क्रम poll
 *
 * Calculate the समयout in jअगरfies from an असलolute समय in sec/nsec.
 */
चिन्हित दीर्घ drm_समयout_असल_to_jअगरfies(पूर्णांक64_t समयout_nsec)
अणु
	kसमय_प्रकार असल_समयout, now;
	u64 समयout_ns, समयout_jअगरfies64;

	/* make 0 समयout means poll - असलolute 0 करोesn't seem valid */
	अगर (समयout_nsec == 0)
		वापस 0;

	असल_समयout = ns_to_kसमय(समयout_nsec);
	now = kसमय_get();

	अगर (!kसमय_after(असल_समयout, now))
		वापस 0;

	समयout_ns = kसमय_प्रकारo_ns(kसमय_sub(असल_समयout, now));

	समयout_jअगरfies64 = nsecs_to_jअगरfies64(समयout_ns);
	/*  clamp समयout to aव्योम infinite समयout */
	अगर (समयout_jअगरfies64 >= MAX_SCHEDULE_TIMEOUT - 1)
		वापस MAX_SCHEDULE_TIMEOUT - 1;

	वापस समयout_jअगरfies64 + 1;
पूर्ण
EXPORT_SYMBOL(drm_समयout_असल_to_jअगरfies);

अटल पूर्णांक drm_syncobj_array_रुको(काष्ठा drm_device *dev,
				  काष्ठा drm_file *file_निजी,
				  काष्ठा drm_syncobj_रुको *रुको,
				  काष्ठा drm_syncobj_समयline_रुको *समयline_रुको,
				  काष्ठा drm_syncobj **syncobjs, bool समयline)
अणु
	चिन्हित दीर्घ समयout = 0;
	uपूर्णांक32_t first = ~0;

	अगर (!समयline) अणु
		समयout = drm_समयout_असल_to_jअगरfies(रुको->समयout_nsec);
		समयout = drm_syncobj_array_रुको_समयout(syncobjs,
							 शून्य,
							 रुको->count_handles,
							 रुको->flags,
							 समयout, &first);
		अगर (समयout < 0)
			वापस समयout;
		रुको->first_संकेतed = first;
	पूर्ण अन्यथा अणु
		समयout = drm_समयout_असल_to_jअगरfies(समयline_रुको->समयout_nsec);
		समयout = drm_syncobj_array_रुको_समयout(syncobjs,
							 u64_to_user_ptr(समयline_रुको->poपूर्णांकs),
							 समयline_रुको->count_handles,
							 समयline_रुको->flags,
							 समयout, &first);
		अगर (समयout < 0)
			वापस समयout;
		समयline_रुको->first_संकेतed = first;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक drm_syncobj_array_find(काष्ठा drm_file *file_निजी,
				  व्योम __user *user_handles,
				  uपूर्णांक32_t count_handles,
				  काष्ठा drm_syncobj ***syncobjs_out)
अणु
	uपूर्णांक32_t i, *handles;
	काष्ठा drm_syncobj **syncobjs;
	पूर्णांक ret;

	handles = kदो_स्मृति_array(count_handles, माप(*handles), GFP_KERNEL);
	अगर (handles == शून्य)
		वापस -ENOMEM;

	अगर (copy_from_user(handles, user_handles,
			   माप(uपूर्णांक32_t) * count_handles)) अणु
		ret = -EFAULT;
		जाओ err_मुक्त_handles;
	पूर्ण

	syncobjs = kदो_स्मृति_array(count_handles, माप(*syncobjs), GFP_KERNEL);
	अगर (syncobjs == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_handles;
	पूर्ण

	क्रम (i = 0; i < count_handles; i++) अणु
		syncobjs[i] = drm_syncobj_find(file_निजी, handles[i]);
		अगर (!syncobjs[i]) अणु
			ret = -ENOENT;
			जाओ err_put_syncobjs;
		पूर्ण
	पूर्ण

	kमुक्त(handles);
	*syncobjs_out = syncobjs;
	वापस 0;

err_put_syncobjs:
	जबतक (i-- > 0)
		drm_syncobj_put(syncobjs[i]);
	kमुक्त(syncobjs);
err_मुक्त_handles:
	kमुक्त(handles);

	वापस ret;
पूर्ण

अटल व्योम drm_syncobj_array_मुक्त(काष्ठा drm_syncobj **syncobjs,
				   uपूर्णांक32_t count)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; i < count; i++)
		drm_syncobj_put(syncobjs[i]);
	kमुक्त(syncobjs);
पूर्ण

पूर्णांक
drm_syncobj_रुको_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_निजी)
अणु
	काष्ठा drm_syncobj_रुको *args = data;
	काष्ठा drm_syncobj **syncobjs;
	पूर्णांक ret = 0;

	अगर (!drm_core_check_feature(dev, DRIVER_SYNCOBJ))
		वापस -EOPNOTSUPP;

	अगर (args->flags & ~(DRM_SYNCOBJ_WAIT_FLAGS_WAIT_ALL |
			    DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT))
		वापस -EINVAL;

	अगर (args->count_handles == 0)
		वापस -EINVAL;

	ret = drm_syncobj_array_find(file_निजी,
				     u64_to_user_ptr(args->handles),
				     args->count_handles,
				     &syncobjs);
	अगर (ret < 0)
		वापस ret;

	ret = drm_syncobj_array_रुको(dev, file_निजी,
				     args, शून्य, syncobjs, false);

	drm_syncobj_array_मुक्त(syncobjs, args->count_handles);

	वापस ret;
पूर्ण

पूर्णांक
drm_syncobj_समयline_रुको_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_निजी)
अणु
	काष्ठा drm_syncobj_समयline_रुको *args = data;
	काष्ठा drm_syncobj **syncobjs;
	पूर्णांक ret = 0;

	अगर (!drm_core_check_feature(dev, DRIVER_SYNCOBJ_TIMELINE))
		वापस -EOPNOTSUPP;

	अगर (args->flags & ~(DRM_SYNCOBJ_WAIT_FLAGS_WAIT_ALL |
			    DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT |
			    DRM_SYNCOBJ_WAIT_FLAGS_WAIT_AVAILABLE))
		वापस -EINVAL;

	अगर (args->count_handles == 0)
		वापस -EINVAL;

	ret = drm_syncobj_array_find(file_निजी,
				     u64_to_user_ptr(args->handles),
				     args->count_handles,
				     &syncobjs);
	अगर (ret < 0)
		वापस ret;

	ret = drm_syncobj_array_रुको(dev, file_निजी,
				     शून्य, args, syncobjs, true);

	drm_syncobj_array_मुक्त(syncobjs, args->count_handles);

	वापस ret;
पूर्ण


पूर्णांक
drm_syncobj_reset_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_निजी)
अणु
	काष्ठा drm_syncobj_array *args = data;
	काष्ठा drm_syncobj **syncobjs;
	uपूर्णांक32_t i;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_SYNCOBJ))
		वापस -EOPNOTSUPP;

	अगर (args->pad != 0)
		वापस -EINVAL;

	अगर (args->count_handles == 0)
		वापस -EINVAL;

	ret = drm_syncobj_array_find(file_निजी,
				     u64_to_user_ptr(args->handles),
				     args->count_handles,
				     &syncobjs);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < args->count_handles; i++)
		drm_syncobj_replace_fence(syncobjs[i], शून्य);

	drm_syncobj_array_मुक्त(syncobjs, args->count_handles);

	वापस 0;
पूर्ण

पूर्णांक
drm_syncobj_संकेत_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_निजी)
अणु
	काष्ठा drm_syncobj_array *args = data;
	काष्ठा drm_syncobj **syncobjs;
	uपूर्णांक32_t i;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_SYNCOBJ))
		वापस -EOPNOTSUPP;

	अगर (args->pad != 0)
		वापस -EINVAL;

	अगर (args->count_handles == 0)
		वापस -EINVAL;

	ret = drm_syncobj_array_find(file_निजी,
				     u64_to_user_ptr(args->handles),
				     args->count_handles,
				     &syncobjs);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < args->count_handles; i++) अणु
		ret = drm_syncobj_assign_null_handle(syncobjs[i]);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	drm_syncobj_array_मुक्त(syncobjs, args->count_handles);

	वापस ret;
पूर्ण

पूर्णांक
drm_syncobj_समयline_संकेत_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file_निजी)
अणु
	काष्ठा drm_syncobj_समयline_array *args = data;
	काष्ठा drm_syncobj **syncobjs;
	काष्ठा dma_fence_chain **chains;
	uपूर्णांक64_t *poपूर्णांकs;
	uपूर्णांक32_t i, j;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_SYNCOBJ_TIMELINE))
		वापस -EOPNOTSUPP;

	अगर (args->flags != 0)
		वापस -EINVAL;

	अगर (args->count_handles == 0)
		वापस -EINVAL;

	ret = drm_syncobj_array_find(file_निजी,
				     u64_to_user_ptr(args->handles),
				     args->count_handles,
				     &syncobjs);
	अगर (ret < 0)
		वापस ret;

	poपूर्णांकs = kदो_स्मृति_array(args->count_handles, माप(*poपूर्णांकs),
			       GFP_KERNEL);
	अगर (!poपूर्णांकs) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर (!u64_to_user_ptr(args->poपूर्णांकs)) अणु
		स_रखो(poपूर्णांकs, 0, args->count_handles * माप(uपूर्णांक64_t));
	पूर्ण अन्यथा अगर (copy_from_user(poपूर्णांकs, u64_to_user_ptr(args->poपूर्णांकs),
				  माप(uपूर्णांक64_t) * args->count_handles)) अणु
		ret = -EFAULT;
		जाओ err_poपूर्णांकs;
	पूर्ण

	chains = kदो_स्मृति_array(args->count_handles, माप(व्योम *), GFP_KERNEL);
	अगर (!chains) अणु
		ret = -ENOMEM;
		जाओ err_poपूर्णांकs;
	पूर्ण
	क्रम (i = 0; i < args->count_handles; i++) अणु
		chains[i] = kzalloc(माप(काष्ठा dma_fence_chain), GFP_KERNEL);
		अगर (!chains[i]) अणु
			क्रम (j = 0; j < i; j++)
				kमुक्त(chains[j]);
			ret = -ENOMEM;
			जाओ err_chains;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < args->count_handles; i++) अणु
		काष्ठा dma_fence *fence = dma_fence_get_stub();

		drm_syncobj_add_poपूर्णांक(syncobjs[i], chains[i],
				      fence, poपूर्णांकs[i]);
		dma_fence_put(fence);
	पूर्ण
err_chains:
	kमुक्त(chains);
err_poपूर्णांकs:
	kमुक्त(poपूर्णांकs);
out:
	drm_syncobj_array_मुक्त(syncobjs, args->count_handles);

	वापस ret;
पूर्ण

पूर्णांक drm_syncobj_query_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_निजी)
अणु
	काष्ठा drm_syncobj_समयline_array *args = data;
	काष्ठा drm_syncobj **syncobjs;
	uपूर्णांक64_t __user *poपूर्णांकs = u64_to_user_ptr(args->poपूर्णांकs);
	uपूर्णांक32_t i;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_SYNCOBJ_TIMELINE))
		वापस -EOPNOTSUPP;

	अगर (args->flags & ~DRM_SYNCOBJ_QUERY_FLAGS_LAST_SUBMITTED)
		वापस -EINVAL;

	अगर (args->count_handles == 0)
		वापस -EINVAL;

	ret = drm_syncobj_array_find(file_निजी,
				     u64_to_user_ptr(args->handles),
				     args->count_handles,
				     &syncobjs);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < args->count_handles; i++) अणु
		काष्ठा dma_fence_chain *chain;
		काष्ठा dma_fence *fence;
		uपूर्णांक64_t poपूर्णांक;

		fence = drm_syncobj_fence_get(syncobjs[i]);
		chain = to_dma_fence_chain(fence);
		अगर (chain) अणु
			काष्ठा dma_fence *iter, *last_संकेतed =
				dma_fence_get(fence);

			अगर (args->flags &
			    DRM_SYNCOBJ_QUERY_FLAGS_LAST_SUBMITTED) अणु
				poपूर्णांक = fence->seqno;
			पूर्ण अन्यथा अणु
				dma_fence_chain_क्रम_each(iter, fence) अणु
					अगर (iter->context != fence->context) अणु
						dma_fence_put(iter);
						/* It is most likely that समयline has
						* unorder poपूर्णांकs. */
						अवरोध;
					पूर्ण
					dma_fence_put(last_संकेतed);
					last_संकेतed = dma_fence_get(iter);
				पूर्ण
				poपूर्णांक = dma_fence_is_संकेतed(last_संकेतed) ?
					last_संकेतed->seqno :
					to_dma_fence_chain(last_संकेतed)->prev_seqno;
			पूर्ण
			dma_fence_put(last_संकेतed);
		पूर्ण अन्यथा अणु
			poपूर्णांक = 0;
		पूर्ण
		dma_fence_put(fence);
		ret = copy_to_user(&poपूर्णांकs[i], &poपूर्णांक, माप(uपूर्णांक64_t));
		ret = ret ? -EFAULT : 0;
		अगर (ret)
			अवरोध;
	पूर्ण
	drm_syncobj_array_मुक्त(syncobjs, args->count_handles);

	वापस ret;
पूर्ण
