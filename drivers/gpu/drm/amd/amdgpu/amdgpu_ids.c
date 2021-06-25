<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
 *
 */
#समावेश "amdgpu_ids.h"

#समावेश <linux/idr.h>
#समावेश <linux/dma-fence-array.h>


#समावेश "amdgpu.h"
#समावेश "amdgpu_trace.h"

/*
 * PASID manager
 *
 * PASIDs are global address space identअगरiers that can be shared
 * between the GPU, an IOMMU and the driver. VMs on dअगरferent devices
 * may use the same PASID अगर they share the same address
 * space. Thereक्रमe PASIDs are allocated using a global IDA. VMs are
 * looked up from the PASID per amdgpu_device.
 */
अटल DEFINE_IDA(amdgpu_pasid_ida);

/* Helper to मुक्त pasid from a fence callback */
काष्ठा amdgpu_pasid_cb अणु
	काष्ठा dma_fence_cb cb;
	u32 pasid;
पूर्ण;

/**
 * amdgpu_pasid_alloc - Allocate a PASID
 * @bits: Maximum width of the PASID in bits, must be at least 1
 *
 * Allocates a PASID of the given width जबतक keeping smaller PASIDs
 * available अगर possible.
 *
 * Returns a positive पूर्णांकeger on success. Returns %-EINVAL अगर bits==0.
 * Returns %-ENOSPC अगर no PASID was available. Returns %-ENOMEM on
 * memory allocation failure.
 */
पूर्णांक amdgpu_pasid_alloc(अचिन्हित पूर्णांक bits)
अणु
	पूर्णांक pasid = -EINVAL;

	क्रम (bits = min(bits, 31U); bits > 0; bits--) अणु
		pasid = ida_simple_get(&amdgpu_pasid_ida,
				       1U << (bits - 1), 1U << bits,
				       GFP_KERNEL);
		अगर (pasid != -ENOSPC)
			अवरोध;
	पूर्ण

	अगर (pasid >= 0)
		trace_amdgpu_pasid_allocated(pasid);

	वापस pasid;
पूर्ण

/**
 * amdgpu_pasid_मुक्त - Free a PASID
 * @pasid: PASID to मुक्त
 */
व्योम amdgpu_pasid_मुक्त(u32 pasid)
अणु
	trace_amdgpu_pasid_मुक्तd(pasid);
	ida_simple_हटाओ(&amdgpu_pasid_ida, pasid);
पूर्ण

अटल व्योम amdgpu_pasid_मुक्त_cb(काष्ठा dma_fence *fence,
				 काष्ठा dma_fence_cb *_cb)
अणु
	काष्ठा amdgpu_pasid_cb *cb =
		container_of(_cb, काष्ठा amdgpu_pasid_cb, cb);

	amdgpu_pasid_मुक्त(cb->pasid);
	dma_fence_put(fence);
	kमुक्त(cb);
पूर्ण

/**
 * amdgpu_pasid_मुक्त_delayed - मुक्त pasid when fences संकेत
 *
 * @resv: reservation object with the fences to रुको क्रम
 * @pasid: pasid to मुक्त
 *
 * Free the pasid only after all the fences in resv are संकेतed.
 */
व्योम amdgpu_pasid_मुक्त_delayed(काष्ठा dma_resv *resv,
			       u32 pasid)
अणु
	काष्ठा dma_fence *fence, **fences;
	काष्ठा amdgpu_pasid_cb *cb;
	अचिन्हित count;
	पूर्णांक r;

	r = dma_resv_get_fences_rcu(resv, शून्य, &count, &fences);
	अगर (r)
		जाओ fallback;

	अगर (count == 0) अणु
		amdgpu_pasid_मुक्त(pasid);
		वापस;
	पूर्ण

	अगर (count == 1) अणु
		fence = fences[0];
		kमुक्त(fences);
	पूर्ण अन्यथा अणु
		uपूर्णांक64_t context = dma_fence_context_alloc(1);
		काष्ठा dma_fence_array *array;

		array = dma_fence_array_create(count, fences, context,
					       1, false);
		अगर (!array) अणु
			kमुक्त(fences);
			जाओ fallback;
		पूर्ण
		fence = &array->base;
	पूर्ण

	cb = kदो_स्मृति(माप(*cb), GFP_KERNEL);
	अगर (!cb) अणु
		/* Last resort when we are OOM */
		dma_fence_रुको(fence, false);
		dma_fence_put(fence);
		amdgpu_pasid_मुक्त(pasid);
	पूर्ण अन्यथा अणु
		cb->pasid = pasid;
		अगर (dma_fence_add_callback(fence, &cb->cb,
					   amdgpu_pasid_मुक्त_cb))
			amdgpu_pasid_मुक्त_cb(fence, &cb->cb);
	पूर्ण

	वापस;

fallback:
	/* Not enough memory क्रम the delayed delete, as last resort
	 * block क्रम all the fences to complete.
	 */
	dma_resv_रुको_समयout_rcu(resv, true, false,
					    MAX_SCHEDULE_TIMEOUT);
	amdgpu_pasid_मुक्त(pasid);
पूर्ण

/*
 * VMID manager
 *
 * VMIDs are a per VMHUB identअगरier क्रम page tables handling.
 */

/**
 * amdgpu_vmid_had_gpu_reset - check अगर reset occured since last use
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @id: VMID काष्ठाure
 *
 * Check अगर GPU reset occured since last use of the VMID.
 */
bool amdgpu_vmid_had_gpu_reset(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_vmid *id)
अणु
	वापस id->current_gpu_reset_count !=
		atomic_पढ़ो(&adev->gpu_reset_counter);
पूर्ण

/**
 * amdgpu_vm_grab_idle - grab idle VMID
 *
 * @vm: vm to allocate id क्रम
 * @ring: ring we want to submit job to
 * @sync: sync object where we add dependencies
 * @idle: resulting idle VMID
 *
 * Try to find an idle VMID, अगर none is idle add a fence to रुको to the sync
 * object. Returns -ENOMEM when we are out of memory.
 */
अटल पूर्णांक amdgpu_vmid_grab_idle(काष्ठा amdgpu_vm *vm,
				 काष्ठा amdgpu_ring *ring,
				 काष्ठा amdgpu_sync *sync,
				 काष्ठा amdgpu_vmid **idle)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अचिन्हित vmhub = ring->funcs->vmhub;
	काष्ठा amdgpu_vmid_mgr *id_mgr = &adev->vm_manager.id_mgr[vmhub];
	काष्ठा dma_fence **fences;
	अचिन्हित i;
	पूर्णांक r;

	अगर (ring->vmid_रुको && !dma_fence_is_संकेतed(ring->vmid_रुको))
		वापस amdgpu_sync_fence(sync, ring->vmid_रुको);

	fences = kदो_स्मृति_array(id_mgr->num_ids, माप(व्योम *), GFP_KERNEL);
	अगर (!fences)
		वापस -ENOMEM;

	/* Check अगर we have an idle VMID */
	i = 0;
	list_क्रम_each_entry((*idle), &id_mgr->ids_lru, list) अणु
		/* Don't use per engine and per process VMID at the same समय */
		काष्ठा amdgpu_ring *r = adev->vm_manager.concurrent_flush ?
			शून्य : ring;

		fences[i] = amdgpu_sync_peek_fence(&(*idle)->active, r);
		अगर (!fences[i])
			अवरोध;
		++i;
	पूर्ण

	/* If we can't find a idle VMID to use, रुको till one becomes available */
	अगर (&(*idle)->list == &id_mgr->ids_lru) अणु
		u64 fence_context = adev->vm_manager.fence_context + ring->idx;
		अचिन्हित seqno = ++adev->vm_manager.seqno[ring->idx];
		काष्ठा dma_fence_array *array;
		अचिन्हित j;

		*idle = शून्य;
		क्रम (j = 0; j < i; ++j)
			dma_fence_get(fences[j]);

		array = dma_fence_array_create(i, fences, fence_context,
					       seqno, true);
		अगर (!array) अणु
			क्रम (j = 0; j < i; ++j)
				dma_fence_put(fences[j]);
			kमुक्त(fences);
			वापस -ENOMEM;
		पूर्ण

		r = amdgpu_sync_fence(sync, &array->base);
		dma_fence_put(ring->vmid_रुको);
		ring->vmid_रुको = &array->base;
		वापस r;
	पूर्ण
	kमुक्त(fences);

	वापस 0;
पूर्ण

/**
 * amdgpu_vm_grab_reserved - try to assign reserved VMID
 *
 * @vm: vm to allocate id क्रम
 * @ring: ring we want to submit job to
 * @sync: sync object where we add dependencies
 * @fence: fence protecting ID from reuse
 * @job: job who wants to use the VMID
 * @id: resulting VMID
 *
 * Try to assign a reserved VMID.
 */
अटल पूर्णांक amdgpu_vmid_grab_reserved(काष्ठा amdgpu_vm *vm,
				     काष्ठा amdgpu_ring *ring,
				     काष्ठा amdgpu_sync *sync,
				     काष्ठा dma_fence *fence,
				     काष्ठा amdgpu_job *job,
				     काष्ठा amdgpu_vmid **id)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अचिन्हित vmhub = ring->funcs->vmhub;
	uपूर्णांक64_t fence_context = adev->fence_context + ring->idx;
	काष्ठा dma_fence *updates = sync->last_vm_update;
	bool needs_flush = vm->use_cpu_क्रम_update;
	पूर्णांक r = 0;

	*id = vm->reserved_vmid[vmhub];
	अगर (updates && (*id)->flushed_updates &&
	    updates->context == (*id)->flushed_updates->context &&
	    !dma_fence_is_later(updates, (*id)->flushed_updates))
		updates = शून्य;

	अगर ((*id)->owner != vm->immediate.fence_context ||
	    job->vm_pd_addr != (*id)->pd_gpu_addr ||
	    updates || !(*id)->last_flush ||
	    ((*id)->last_flush->context != fence_context &&
	     !dma_fence_is_संकेतed((*id)->last_flush))) अणु
		काष्ठा dma_fence *पंचांगp;

		/* Don't use per engine and per process VMID at the same समय */
		अगर (adev->vm_manager.concurrent_flush)
			ring = शून्य;

		/* to prevent one context starved by another context */
		(*id)->pd_gpu_addr = 0;
		पंचांगp = amdgpu_sync_peek_fence(&(*id)->active, ring);
		अगर (पंचांगp) अणु
			*id = शून्य;
			r = amdgpu_sync_fence(sync, पंचांगp);
			वापस r;
		पूर्ण
		needs_flush = true;
	पूर्ण

	/* Good we can use this VMID. Remember this submission as
	* user of the VMID.
	*/
	r = amdgpu_sync_fence(&(*id)->active, fence);
	अगर (r)
		वापस r;

	अगर (updates) अणु
		dma_fence_put((*id)->flushed_updates);
		(*id)->flushed_updates = dma_fence_get(updates);
	पूर्ण
	job->vm_needs_flush = needs_flush;
	वापस 0;
पूर्ण

/**
 * amdgpu_vm_grab_used - try to reuse a VMID
 *
 * @vm: vm to allocate id क्रम
 * @ring: ring we want to submit job to
 * @sync: sync object where we add dependencies
 * @fence: fence protecting ID from reuse
 * @job: job who wants to use the VMID
 * @id: resulting VMID
 *
 * Try to reuse a VMID क्रम this submission.
 */
अटल पूर्णांक amdgpu_vmid_grab_used(काष्ठा amdgpu_vm *vm,
				 काष्ठा amdgpu_ring *ring,
				 काष्ठा amdgpu_sync *sync,
				 काष्ठा dma_fence *fence,
				 काष्ठा amdgpu_job *job,
				 काष्ठा amdgpu_vmid **id)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अचिन्हित vmhub = ring->funcs->vmhub;
	काष्ठा amdgpu_vmid_mgr *id_mgr = &adev->vm_manager.id_mgr[vmhub];
	uपूर्णांक64_t fence_context = adev->fence_context + ring->idx;
	काष्ठा dma_fence *updates = sync->last_vm_update;
	पूर्णांक r;

	job->vm_needs_flush = vm->use_cpu_क्रम_update;

	/* Check अगर we can use a VMID alपढ़ोy asचिन्हित to this VM */
	list_क्रम_each_entry_reverse((*id), &id_mgr->ids_lru, list) अणु
		bool needs_flush = vm->use_cpu_क्रम_update;
		काष्ठा dma_fence *flushed;

		/* Check all the prerequisites to using this VMID */
		अगर ((*id)->owner != vm->immediate.fence_context)
			जारी;

		अगर ((*id)->pd_gpu_addr != job->vm_pd_addr)
			जारी;

		अगर (!(*id)->last_flush ||
		    ((*id)->last_flush->context != fence_context &&
		     !dma_fence_is_संकेतed((*id)->last_flush)))
			needs_flush = true;

		flushed  = (*id)->flushed_updates;
		अगर (updates && (!flushed || dma_fence_is_later(updates, flushed)))
			needs_flush = true;

		अगर (needs_flush && !adev->vm_manager.concurrent_flush)
			जारी;

		/* Good, we can use this VMID. Remember this submission as
		 * user of the VMID.
		 */
		r = amdgpu_sync_fence(&(*id)->active, fence);
		अगर (r)
			वापस r;

		अगर (updates && (!flushed || dma_fence_is_later(updates, flushed))) अणु
			dma_fence_put((*id)->flushed_updates);
			(*id)->flushed_updates = dma_fence_get(updates);
		पूर्ण

		job->vm_needs_flush |= needs_flush;
		वापस 0;
	पूर्ण

	*id = शून्य;
	वापस 0;
पूर्ण

/**
 * amdgpu_vm_grab_id - allocate the next मुक्त VMID
 *
 * @vm: vm to allocate id क्रम
 * @ring: ring we want to submit job to
 * @sync: sync object where we add dependencies
 * @fence: fence protecting ID from reuse
 * @job: job who wants to use the VMID
 *
 * Allocate an id क्रम the vm, adding fences to the sync obj as necessary.
 */
पूर्णांक amdgpu_vmid_grab(काष्ठा amdgpu_vm *vm, काष्ठा amdgpu_ring *ring,
		     काष्ठा amdgpu_sync *sync, काष्ठा dma_fence *fence,
		     काष्ठा amdgpu_job *job)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अचिन्हित vmhub = ring->funcs->vmhub;
	काष्ठा amdgpu_vmid_mgr *id_mgr = &adev->vm_manager.id_mgr[vmhub];
	काष्ठा amdgpu_vmid *idle = शून्य;
	काष्ठा amdgpu_vmid *id = शून्य;
	पूर्णांक r = 0;

	mutex_lock(&id_mgr->lock);
	r = amdgpu_vmid_grab_idle(vm, ring, sync, &idle);
	अगर (r || !idle)
		जाओ error;

	अगर (vm->reserved_vmid[vmhub]) अणु
		r = amdgpu_vmid_grab_reserved(vm, ring, sync, fence, job, &id);
		अगर (r || !id)
			जाओ error;
	पूर्ण अन्यथा अणु
		r = amdgpu_vmid_grab_used(vm, ring, sync, fence, job, &id);
		अगर (r)
			जाओ error;

		अगर (!id) अणु
			काष्ठा dma_fence *updates = sync->last_vm_update;

			/* Still no ID to use? Then use the idle one found earlier */
			id = idle;

			/* Remember this submission as user of the VMID */
			r = amdgpu_sync_fence(&id->active, fence);
			अगर (r)
				जाओ error;

			dma_fence_put(id->flushed_updates);
			id->flushed_updates = dma_fence_get(updates);
			job->vm_needs_flush = true;
		पूर्ण

		list_move_tail(&id->list, &id_mgr->ids_lru);
	पूर्ण

	id->pd_gpu_addr = job->vm_pd_addr;
	id->owner = vm->immediate.fence_context;

	अगर (job->vm_needs_flush) अणु
		dma_fence_put(id->last_flush);
		id->last_flush = शून्य;
	पूर्ण
	job->vmid = id - id_mgr->ids;
	job->pasid = vm->pasid;
	trace_amdgpu_vm_grab_id(vm, ring, job);

error:
	mutex_unlock(&id_mgr->lock);
	वापस r;
पूर्ण

पूर्णांक amdgpu_vmid_alloc_reserved(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_vm *vm,
			       अचिन्हित vmhub)
अणु
	काष्ठा amdgpu_vmid_mgr *id_mgr;
	काष्ठा amdgpu_vmid *idle;
	पूर्णांक r = 0;

	id_mgr = &adev->vm_manager.id_mgr[vmhub];
	mutex_lock(&id_mgr->lock);
	अगर (vm->reserved_vmid[vmhub])
		जाओ unlock;
	अगर (atomic_inc_वापस(&id_mgr->reserved_vmid_num) >
	    AMDGPU_VM_MAX_RESERVED_VMID) अणु
		DRM_ERROR("Over limitation of reserved vmid\n");
		atomic_dec(&id_mgr->reserved_vmid_num);
		r = -EINVAL;
		जाओ unlock;
	पूर्ण
	/* Select the first entry VMID */
	idle = list_first_entry(&id_mgr->ids_lru, काष्ठा amdgpu_vmid, list);
	list_del_init(&idle->list);
	vm->reserved_vmid[vmhub] = idle;
	mutex_unlock(&id_mgr->lock);

	वापस 0;
unlock:
	mutex_unlock(&id_mgr->lock);
	वापस r;
पूर्ण

व्योम amdgpu_vmid_मुक्त_reserved(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_vm *vm,
			       अचिन्हित vmhub)
अणु
	काष्ठा amdgpu_vmid_mgr *id_mgr = &adev->vm_manager.id_mgr[vmhub];

	mutex_lock(&id_mgr->lock);
	अगर (vm->reserved_vmid[vmhub]) अणु
		list_add(&vm->reserved_vmid[vmhub]->list,
			&id_mgr->ids_lru);
		vm->reserved_vmid[vmhub] = शून्य;
		atomic_dec(&id_mgr->reserved_vmid_num);
	पूर्ण
	mutex_unlock(&id_mgr->lock);
पूर्ण

/**
 * amdgpu_vmid_reset - reset VMID to zero
 *
 * @adev: amdgpu device काष्ठाure
 * @vmhub: vmhub type
 * @vmid: vmid number to use
 *
 * Reset saved GDW, GWS and OA to क्रमce चयन on next flush.
 */
व्योम amdgpu_vmid_reset(काष्ठा amdgpu_device *adev, अचिन्हित vmhub,
		       अचिन्हित vmid)
अणु
	काष्ठा amdgpu_vmid_mgr *id_mgr = &adev->vm_manager.id_mgr[vmhub];
	काष्ठा amdgpu_vmid *id = &id_mgr->ids[vmid];

	mutex_lock(&id_mgr->lock);
	id->owner = 0;
	id->gds_base = 0;
	id->gds_size = 0;
	id->gws_base = 0;
	id->gws_size = 0;
	id->oa_base = 0;
	id->oa_size = 0;
	mutex_unlock(&id_mgr->lock);
पूर्ण

/**
 * amdgpu_vmid_reset_all - reset VMID to zero
 *
 * @adev: amdgpu device काष्ठाure
 *
 * Reset VMID to क्रमce flush on next use
 */
व्योम amdgpu_vmid_reset_all(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i, j;

	क्रम (i = 0; i < AMDGPU_MAX_VMHUBS; ++i) अणु
		काष्ठा amdgpu_vmid_mgr *id_mgr =
			&adev->vm_manager.id_mgr[i];

		क्रम (j = 1; j < id_mgr->num_ids; ++j)
			amdgpu_vmid_reset(adev, i, j);
	पूर्ण
पूर्ण

/**
 * amdgpu_vmid_mgr_init - init the VMID manager
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Initialize the VM manager काष्ठाures
 */
व्योम amdgpu_vmid_mgr_init(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i, j;

	क्रम (i = 0; i < AMDGPU_MAX_VMHUBS; ++i) अणु
		काष्ठा amdgpu_vmid_mgr *id_mgr =
			&adev->vm_manager.id_mgr[i];

		mutex_init(&id_mgr->lock);
		INIT_LIST_HEAD(&id_mgr->ids_lru);
		atomic_set(&id_mgr->reserved_vmid_num, 0);

		/* manage only VMIDs not used by KFD */
		id_mgr->num_ids = adev->vm_manager.first_kfd_vmid;

		/* skip over VMID 0, since it is the प्रणाली VM */
		क्रम (j = 1; j < id_mgr->num_ids; ++j) अणु
			amdgpu_vmid_reset(adev, i, j);
			amdgpu_sync_create(&id_mgr->ids[j].active);
			list_add_tail(&id_mgr->ids[j].list, &id_mgr->ids_lru);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * amdgpu_vmid_mgr_fini - cleanup VM manager
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Cleanup the VM manager and मुक्त resources.
 */
व्योम amdgpu_vmid_mgr_fini(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i, j;

	क्रम (i = 0; i < AMDGPU_MAX_VMHUBS; ++i) अणु
		काष्ठा amdgpu_vmid_mgr *id_mgr =
			&adev->vm_manager.id_mgr[i];

		mutex_destroy(&id_mgr->lock);
		क्रम (j = 0; j < AMDGPU_NUM_VMID; ++j) अणु
			काष्ठा amdgpu_vmid *id = &id_mgr->ids[j];

			amdgpu_sync_मुक्त(&id->active);
			dma_fence_put(id->flushed_updates);
			dma_fence_put(id->last_flush);
			dma_fence_put(id->pasid_mapping);
		पूर्ण
	पूर्ण
पूर्ण
