<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors:
 *    Christian Kथघnig <christian.koenig@amd.com>
 */

#समावेश "amdgpu.h"
#समावेश "amdgpu_trace.h"
#समावेश "amdgpu_amdkfd.h"

काष्ठा amdgpu_sync_entry अणु
	काष्ठा hlist_node	node;
	काष्ठा dma_fence	*fence;
पूर्ण;

अटल काष्ठा kmem_cache *amdgpu_sync_slab;

/**
 * amdgpu_sync_create - zero init sync object
 *
 * @sync: sync object to initialize
 *
 * Just clear the sync object क्रम now.
 */
व्योम amdgpu_sync_create(काष्ठा amdgpu_sync *sync)
अणु
	hash_init(sync->fences);
	sync->last_vm_update = शून्य;
पूर्ण

/**
 * amdgpu_sync_same_dev - test अगर fence beदीर्घ to us
 *
 * @adev: amdgpu device to use क्रम the test
 * @f: fence to test
 *
 * Test अगर the fence was issued by us.
 */
अटल bool amdgpu_sync_same_dev(काष्ठा amdgpu_device *adev,
				 काष्ठा dma_fence *f)
अणु
	काष्ठा drm_sched_fence *s_fence = to_drm_sched_fence(f);

	अगर (s_fence) अणु
		काष्ठा amdgpu_ring *ring;

		ring = container_of(s_fence->sched, काष्ठा amdgpu_ring, sched);
		वापस ring->adev == adev;
	पूर्ण

	वापस false;
पूर्ण

/**
 * amdgpu_sync_get_owner - extract the owner of a fence
 *
 * @f: fence get the owner from
 *
 * Extract who originally created the fence.
 */
अटल व्योम *amdgpu_sync_get_owner(काष्ठा dma_fence *f)
अणु
	काष्ठा drm_sched_fence *s_fence;
	काष्ठा amdgpu_amdkfd_fence *kfd_fence;

	अगर (!f)
		वापस AMDGPU_FENCE_OWNER_UNDEFINED;

	s_fence = to_drm_sched_fence(f);
	अगर (s_fence)
		वापस s_fence->owner;

	kfd_fence = to_amdgpu_amdkfd_fence(f);
	अगर (kfd_fence)
		वापस AMDGPU_FENCE_OWNER_KFD;

	वापस AMDGPU_FENCE_OWNER_UNDEFINED;
पूर्ण

/**
 * amdgpu_sync_keep_later - Keep the later fence
 *
 * @keep: existing fence to test
 * @fence: new fence
 *
 * Either keep the existing fence or the new one, depending which one is later.
 */
अटल व्योम amdgpu_sync_keep_later(काष्ठा dma_fence **keep,
				   काष्ठा dma_fence *fence)
अणु
	अगर (*keep && dma_fence_is_later(*keep, fence))
		वापस;

	dma_fence_put(*keep);
	*keep = dma_fence_get(fence);
पूर्ण

/**
 * amdgpu_sync_add_later - add the fence to the hash
 *
 * @sync: sync object to add the fence to
 * @f: fence to add
 *
 * Tries to add the fence to an existing hash entry. Returns true when an entry
 * was found, false otherwise.
 */
अटल bool amdgpu_sync_add_later(काष्ठा amdgpu_sync *sync, काष्ठा dma_fence *f)
अणु
	काष्ठा amdgpu_sync_entry *e;

	hash_क्रम_each_possible(sync->fences, e, node, f->context) अणु
		अगर (unlikely(e->fence->context != f->context))
			जारी;

		amdgpu_sync_keep_later(&e->fence, f);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * amdgpu_sync_fence - remember to sync to this fence
 *
 * @sync: sync object to add fence to
 * @f: fence to sync to
 *
 * Add the fence to the sync object.
 */
पूर्णांक amdgpu_sync_fence(काष्ठा amdgpu_sync *sync, काष्ठा dma_fence *f)
अणु
	काष्ठा amdgpu_sync_entry *e;

	अगर (!f)
		वापस 0;

	अगर (amdgpu_sync_add_later(sync, f))
		वापस 0;

	e = kmem_cache_alloc(amdgpu_sync_slab, GFP_KERNEL);
	अगर (!e)
		वापस -ENOMEM;

	hash_add(sync->fences, &e->node, f->context);
	e->fence = dma_fence_get(f);
	वापस 0;
पूर्ण

/**
 * amdgpu_sync_vm_fence - remember to sync to this VM fence
 *
 * @sync: sync object to add fence to
 * @fence: the VM fence to add
 *
 * Add the fence to the sync object and remember it as VM update.
 */
पूर्णांक amdgpu_sync_vm_fence(काष्ठा amdgpu_sync *sync, काष्ठा dma_fence *fence)
अणु
	अगर (!fence)
		वापस 0;

	amdgpu_sync_keep_later(&sync->last_vm_update, fence);
	वापस amdgpu_sync_fence(sync, fence);
पूर्ण

/**
 * amdgpu_sync_resv - sync to a reservation object
 *
 * @adev: amdgpu device
 * @sync: sync object to add fences from reservation object to
 * @resv: reservation object with embedded fence
 * @mode: how owner affects which fences we sync to
 * @owner: owner of the planned job submission
 *
 * Sync to the fence
 */
पूर्णांक amdgpu_sync_resv(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_sync *sync,
		     काष्ठा dma_resv *resv, क्रमागत amdgpu_sync_mode mode,
		     व्योम *owner)
अणु
	काष्ठा dma_resv_list *flist;
	काष्ठा dma_fence *f;
	अचिन्हित i;
	पूर्णांक r = 0;

	अगर (resv == शून्य)
		वापस -EINVAL;

	/* always sync to the exclusive fence */
	f = dma_resv_get_excl(resv);
	r = amdgpu_sync_fence(sync, f);

	flist = dma_resv_get_list(resv);
	अगर (!flist || r)
		वापस r;

	क्रम (i = 0; i < flist->shared_count; ++i) अणु
		व्योम *fence_owner;

		f = rcu_dereference_रक्षित(flist->shared[i],
					      dma_resv_held(resv));

		fence_owner = amdgpu_sync_get_owner(f);

		/* Always sync to moves, no matter what */
		अगर (fence_owner == AMDGPU_FENCE_OWNER_UNDEFINED) अणु
			r = amdgpu_sync_fence(sync, f);
			अगर (r)
				अवरोध;
		पूर्ण

		/* We only want to trigger KFD eviction fences on
		 * evict or move jobs. Skip KFD fences otherwise.
		 */
		अगर (fence_owner == AMDGPU_FENCE_OWNER_KFD &&
		    owner != AMDGPU_FENCE_OWNER_UNDEFINED)
			जारी;

		/* Never sync to VM updates either. */
		अगर (fence_owner == AMDGPU_FENCE_OWNER_VM &&
		    owner != AMDGPU_FENCE_OWNER_UNDEFINED)
			जारी;

		/* Ignore fences depending on the sync mode */
		चयन (mode) अणु
		हाल AMDGPU_SYNC_ALWAYS:
			अवरोध;

		हाल AMDGPU_SYNC_NE_OWNER:
			अगर (amdgpu_sync_same_dev(adev, f) &&
			    fence_owner == owner)
				जारी;
			अवरोध;

		हाल AMDGPU_SYNC_EQ_OWNER:
			अगर (amdgpu_sync_same_dev(adev, f) &&
			    fence_owner != owner)
				जारी;
			अवरोध;

		हाल AMDGPU_SYNC_EXPLICIT:
			जारी;
		पूर्ण

		WARN(debug_evictions && fence_owner == AMDGPU_FENCE_OWNER_KFD,
		     "Adding eviction fence to sync obj");
		r = amdgpu_sync_fence(sync, f);
		अगर (r)
			अवरोध;
	पूर्ण
	वापस r;
पूर्ण

/**
 * amdgpu_sync_peek_fence - get the next fence not संकेतed yet
 *
 * @sync: the sync object
 * @ring: optional ring to use क्रम test
 *
 * Returns the next fence not संकेतed yet without removing it from the sync
 * object.
 */
काष्ठा dma_fence *amdgpu_sync_peek_fence(काष्ठा amdgpu_sync *sync,
					 काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_sync_entry *e;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	hash_क्रम_each_safe(sync->fences, i, पंचांगp, e, node) अणु
		काष्ठा dma_fence *f = e->fence;
		काष्ठा drm_sched_fence *s_fence = to_drm_sched_fence(f);

		अगर (dma_fence_is_संकेतed(f)) अणु
			hash_del(&e->node);
			dma_fence_put(f);
			kmem_cache_मुक्त(amdgpu_sync_slab, e);
			जारी;
		पूर्ण
		अगर (ring && s_fence) अणु
			/* For fences from the same ring it is sufficient
			 * when they are scheduled.
			 */
			अगर (s_fence->sched == &ring->sched) अणु
				अगर (dma_fence_is_संकेतed(&s_fence->scheduled))
					जारी;

				वापस &s_fence->scheduled;
			पूर्ण
		पूर्ण

		वापस f;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * amdgpu_sync_get_fence - get the next fence from the sync object
 *
 * @sync: sync object to use
 *
 * Get and हटाओs the next fence from the sync object not संकेतed yet.
 */
काष्ठा dma_fence *amdgpu_sync_get_fence(काष्ठा amdgpu_sync *sync)
अणु
	काष्ठा amdgpu_sync_entry *e;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा dma_fence *f;
	पूर्णांक i;
	hash_क्रम_each_safe(sync->fences, i, पंचांगp, e, node) अणु

		f = e->fence;

		hash_del(&e->node);
		kmem_cache_मुक्त(amdgpu_sync_slab, e);

		अगर (!dma_fence_is_संकेतed(f))
			वापस f;

		dma_fence_put(f);
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * amdgpu_sync_clone - clone a sync object
 *
 * @source: sync object to clone
 * @clone: poपूर्णांकer to destination sync object
 *
 * Adds references to all unसंकेतed fences in @source to @clone. Also
 * हटाओs संकेतed fences from @source जबतक at it.
 */
पूर्णांक amdgpu_sync_clone(काष्ठा amdgpu_sync *source, काष्ठा amdgpu_sync *clone)
अणु
	काष्ठा amdgpu_sync_entry *e;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा dma_fence *f;
	पूर्णांक i, r;

	hash_क्रम_each_safe(source->fences, i, पंचांगp, e, node) अणु
		f = e->fence;
		अगर (!dma_fence_is_संकेतed(f)) अणु
			r = amdgpu_sync_fence(clone, f);
			अगर (r)
				वापस r;
		पूर्ण अन्यथा अणु
			hash_del(&e->node);
			dma_fence_put(f);
			kmem_cache_मुक्त(amdgpu_sync_slab, e);
		पूर्ण
	पूर्ण

	dma_fence_put(clone->last_vm_update);
	clone->last_vm_update = dma_fence_get(source->last_vm_update);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_sync_रुको(काष्ठा amdgpu_sync *sync, bool पूर्णांकr)
अणु
	काष्ठा amdgpu_sync_entry *e;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i, r;

	hash_क्रम_each_safe(sync->fences, i, पंचांगp, e, node) अणु
		r = dma_fence_रुको(e->fence, पूर्णांकr);
		अगर (r)
			वापस r;

		hash_del(&e->node);
		dma_fence_put(e->fence);
		kmem_cache_मुक्त(amdgpu_sync_slab, e);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_sync_मुक्त - मुक्त the sync object
 *
 * @sync: sync object to use
 *
 * Free the sync object.
 */
व्योम amdgpu_sync_मुक्त(काष्ठा amdgpu_sync *sync)
अणु
	काष्ठा amdgpu_sync_entry *e;
	काष्ठा hlist_node *पंचांगp;
	अचिन्हित i;

	hash_क्रम_each_safe(sync->fences, i, पंचांगp, e, node) अणु
		hash_del(&e->node);
		dma_fence_put(e->fence);
		kmem_cache_मुक्त(amdgpu_sync_slab, e);
	पूर्ण

	dma_fence_put(sync->last_vm_update);
पूर्ण

/**
 * amdgpu_sync_init - init sync object subप्रणाली
 *
 * Allocate the slab allocator.
 */
पूर्णांक amdgpu_sync_init(व्योम)
अणु
	amdgpu_sync_slab = kmem_cache_create(
		"amdgpu_sync", माप(काष्ठा amdgpu_sync_entry), 0,
		SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!amdgpu_sync_slab)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * amdgpu_sync_fini - fini sync object subप्रणाली
 *
 * Free the slab allocator.
 */
व्योम amdgpu_sync_fini(व्योम)
अणु
	kmem_cache_destroy(amdgpu_sync_slab);
पूर्ण
