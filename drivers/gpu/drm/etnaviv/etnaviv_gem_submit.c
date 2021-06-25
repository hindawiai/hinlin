<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Etnaviv Project
 */

#समावेश <drm/drm_file.h>
#समावेश <linux/dma-fence-array.h>
#समावेश <linux/file.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/dma-resv.h>
#समावेश <linux/sync_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "etnaviv_cmdbuf.h"
#समावेश "etnaviv_drv.h"
#समावेश "etnaviv_gpu.h"
#समावेश "etnaviv_gem.h"
#समावेश "etnaviv_perfmon.h"
#समावेश "etnaviv_sched.h"

/*
 * Cmdstream submission:
 */

#घोषणा BO_INVALID_FLAGS ~(ETNA_SUBMIT_BO_READ | ETNA_SUBMIT_BO_WRITE)
/* make sure these करोn't conflict w/ ETNAVIV_SUBMIT_BO_x */
#घोषणा BO_LOCKED   0x4000
#घोषणा BO_PINNED   0x2000

अटल काष्ठा etnaviv_gem_submit *submit_create(काष्ठा drm_device *dev,
		काष्ठा etnaviv_gpu *gpu, माप_प्रकार nr_bos, माप_प्रकार nr_pmrs)
अणु
	काष्ठा etnaviv_gem_submit *submit;
	माप_प्रकार sz = size_vकाष्ठा(nr_bos, माप(submit->bos[0]), माप(*submit));

	submit = kzalloc(sz, GFP_KERNEL);
	अगर (!submit)
		वापस शून्य;

	submit->pmrs = kसुस्मृति(nr_pmrs, माप(काष्ठा etnaviv_perfmon_request),
			       GFP_KERNEL);
	अगर (!submit->pmrs) अणु
		kमुक्त(submit);
		वापस शून्य;
	पूर्ण
	submit->nr_pmrs = nr_pmrs;

	submit->gpu = gpu;
	kref_init(&submit->refcount);

	वापस submit;
पूर्ण

अटल पूर्णांक submit_lookup_objects(काष्ठा etnaviv_gem_submit *submit,
	काष्ठा drm_file *file, काष्ठा drm_etnaviv_gem_submit_bo *submit_bos,
	अचिन्हित nr_bos)
अणु
	काष्ठा drm_etnaviv_gem_submit_bo *bo;
	अचिन्हित i;
	पूर्णांक ret = 0;

	spin_lock(&file->table_lock);

	क्रम (i = 0, bo = submit_bos; i < nr_bos; i++, bo++) अणु
		काष्ठा drm_gem_object *obj;

		अगर (bo->flags & BO_INVALID_FLAGS) अणु
			DRM_ERROR("invalid flags: %x\n", bo->flags);
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		submit->bos[i].flags = bo->flags;
		अगर (submit->flags & ETNA_SUBMIT_SOFTPIN) अणु
			अगर (bo->presumed < ETNAVIV_SOFTPIN_START_ADDRESS) अणु
				DRM_ERROR("invalid softpin address\n");
				ret = -EINVAL;
				जाओ out_unlock;
			पूर्ण
			submit->bos[i].va = bo->presumed;
		पूर्ण

		/* normally use drm_gem_object_lookup(), but क्रम bulk lookup
		 * all under single table_lock just hit object_idr directly:
		 */
		obj = idr_find(&file->object_idr, bo->handle);
		अगर (!obj) अणु
			DRM_ERROR("invalid handle %u at index %u\n",
				  bo->handle, i);
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		/*
		 * Take a refcount on the object. The file table lock
		 * prevents the object_idr's refcount on this being dropped.
		 */
		drm_gem_object_get(obj);

		submit->bos[i].obj = to_etnaviv_bo(obj);
	पूर्ण

out_unlock:
	submit->nr_bos = i;
	spin_unlock(&file->table_lock);

	वापस ret;
पूर्ण

अटल व्योम submit_unlock_object(काष्ठा etnaviv_gem_submit *submit, पूर्णांक i)
अणु
	अगर (submit->bos[i].flags & BO_LOCKED) अणु
		काष्ठा drm_gem_object *obj = &submit->bos[i].obj->base;

		dma_resv_unlock(obj->resv);
		submit->bos[i].flags &= ~BO_LOCKED;
	पूर्ण
पूर्ण

अटल पूर्णांक submit_lock_objects(काष्ठा etnaviv_gem_submit *submit,
		काष्ठा ww_acquire_ctx *ticket)
अणु
	पूर्णांक contended, slow_locked = -1, i, ret = 0;

retry:
	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा drm_gem_object *obj = &submit->bos[i].obj->base;

		अगर (slow_locked == i)
			slow_locked = -1;

		contended = i;

		अगर (!(submit->bos[i].flags & BO_LOCKED)) अणु
			ret = dma_resv_lock_पूर्णांकerruptible(obj->resv, ticket);
			अगर (ret == -EALREADY)
				DRM_ERROR("BO at index %u already on submit list\n",
					  i);
			अगर (ret)
				जाओ fail;
			submit->bos[i].flags |= BO_LOCKED;
		पूर्ण
	पूर्ण

	ww_acquire_करोne(ticket);

	वापस 0;

fail:
	क्रम (; i >= 0; i--)
		submit_unlock_object(submit, i);

	अगर (slow_locked > 0)
		submit_unlock_object(submit, slow_locked);

	अगर (ret == -EDEADLK) अणु
		काष्ठा drm_gem_object *obj;

		obj = &submit->bos[contended].obj->base;

		/* we lost out in a seqno race, lock and retry.. */
		ret = dma_resv_lock_slow_पूर्णांकerruptible(obj->resv, ticket);
		अगर (!ret) अणु
			submit->bos[contended].flags |= BO_LOCKED;
			slow_locked = contended;
			जाओ retry;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक submit_fence_sync(काष्ठा etnaviv_gem_submit *submit)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा etnaviv_gem_submit_bo *bo = &submit->bos[i];
		काष्ठा dma_resv *robj = bo->obj->base.resv;

		अगर (!(bo->flags & ETNA_SUBMIT_BO_WRITE)) अणु
			ret = dma_resv_reserve_shared(robj, 1);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (submit->flags & ETNA_SUBMIT_NO_IMPLICIT)
			जारी;

		अगर (bo->flags & ETNA_SUBMIT_BO_WRITE) अणु
			ret = dma_resv_get_fences_rcu(robj, &bo->excl,
								&bo->nr_shared,
								&bo->shared);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			bo->excl = dma_resv_get_excl_rcu(robj);
		पूर्ण

	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम submit_attach_object_fences(काष्ठा etnaviv_gem_submit *submit)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा drm_gem_object *obj = &submit->bos[i].obj->base;

		अगर (submit->bos[i].flags & ETNA_SUBMIT_BO_WRITE)
			dma_resv_add_excl_fence(obj->resv,
							  submit->out_fence);
		अन्यथा
			dma_resv_add_shared_fence(obj->resv,
							    submit->out_fence);

		submit_unlock_object(submit, i);
	पूर्ण
पूर्ण

अटल पूर्णांक submit_pin_objects(काष्ठा etnaviv_gem_submit *submit)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा etnaviv_gem_object *etnaviv_obj = submit->bos[i].obj;
		काष्ठा etnaviv_vram_mapping *mapping;

		mapping = etnaviv_gem_mapping_get(&etnaviv_obj->base,
						  submit->mmu_context,
						  submit->bos[i].va);
		अगर (IS_ERR(mapping)) अणु
			ret = PTR_ERR(mapping);
			अवरोध;
		पूर्ण

		अगर ((submit->flags & ETNA_SUBMIT_SOFTPIN) &&
		     submit->bos[i].va != mapping->iova) अणु
			etnaviv_gem_mapping_unreference(mapping);
			वापस -EINVAL;
		पूर्ण

		atomic_inc(&etnaviv_obj->gpu_active);

		submit->bos[i].flags |= BO_PINNED;
		submit->bos[i].mapping = mapping;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक submit_bo(काष्ठा etnaviv_gem_submit *submit, u32 idx,
	काष्ठा etnaviv_gem_submit_bo **bo)
अणु
	अगर (idx >= submit->nr_bos) अणु
		DRM_ERROR("invalid buffer index: %u (out of %u)\n",
				idx, submit->nr_bos);
		वापस -EINVAL;
	पूर्ण

	*bo = &submit->bos[idx];

	वापस 0;
पूर्ण

/* process the reloc's and patch up the cmdstream as needed: */
अटल पूर्णांक submit_reloc(काष्ठा etnaviv_gem_submit *submit, व्योम *stream,
		u32 size, स्थिर काष्ठा drm_etnaviv_gem_submit_reloc *relocs,
		u32 nr_relocs)
अणु
	u32 i, last_offset = 0;
	u32 *ptr = stream;
	पूर्णांक ret;

	/* Submits using softpin करोn't blend with relocs */
	अगर ((submit->flags & ETNA_SUBMIT_SOFTPIN) && nr_relocs != 0)
		वापस -EINVAL;

	क्रम (i = 0; i < nr_relocs; i++) अणु
		स्थिर काष्ठा drm_etnaviv_gem_submit_reloc *r = relocs + i;
		काष्ठा etnaviv_gem_submit_bo *bo;
		u32 off;

		अगर (unlikely(r->flags)) अणु
			DRM_ERROR("invalid reloc flags\n");
			वापस -EINVAL;
		पूर्ण

		अगर (r->submit_offset % 4) अणु
			DRM_ERROR("non-aligned reloc offset: %u\n",
				  r->submit_offset);
			वापस -EINVAL;
		पूर्ण

		/* offset in dwords: */
		off = r->submit_offset / 4;

		अगर ((off >= size ) ||
				(off < last_offset)) अणु
			DRM_ERROR("invalid offset %u at reloc %u\n", off, i);
			वापस -EINVAL;
		पूर्ण

		ret = submit_bo(submit, r->reloc_idx, &bo);
		अगर (ret)
			वापस ret;

		अगर (r->reloc_offset > bo->obj->base.size - माप(*ptr)) अणु
			DRM_ERROR("relocation %u outside object\n", i);
			वापस -EINVAL;
		पूर्ण

		ptr[off] = bo->mapping->iova + r->reloc_offset;

		last_offset = off;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक submit_perfmon_validate(काष्ठा etnaviv_gem_submit *submit,
		u32 exec_state, स्थिर काष्ठा drm_etnaviv_gem_submit_pmr *pmrs)
अणु
	u32 i;

	क्रम (i = 0; i < submit->nr_pmrs; i++) अणु
		स्थिर काष्ठा drm_etnaviv_gem_submit_pmr *r = pmrs + i;
		काष्ठा etnaviv_gem_submit_bo *bo;
		पूर्णांक ret;

		ret = submit_bo(submit, r->पढ़ो_idx, &bo);
		अगर (ret)
			वापस ret;

		/* at offset 0 a sequence number माला_लो stored used क्रम userspace sync */
		अगर (r->पढ़ो_offset == 0) अणु
			DRM_ERROR("perfmon request: offset is 0");
			वापस -EINVAL;
		पूर्ण

		अगर (r->पढ़ो_offset >= bo->obj->base.size - माप(u32)) अणु
			DRM_ERROR("perfmon request: offset %u outside object", i);
			वापस -EINVAL;
		पूर्ण

		अगर (r->flags & ~(ETNA_PM_PROCESS_PRE | ETNA_PM_PROCESS_POST)) अणु
			DRM_ERROR("perfmon request: flags are not valid");
			वापस -EINVAL;
		पूर्ण

		अगर (etnaviv_pm_req_validate(r, exec_state)) अणु
			DRM_ERROR("perfmon request: domain or signal not valid");
			वापस -EINVAL;
		पूर्ण

		submit->pmrs[i].flags = r->flags;
		submit->pmrs[i].करोमुख्य = r->करोमुख्य;
		submit->pmrs[i].संकेत = r->संकेत;
		submit->pmrs[i].sequence = r->sequence;
		submit->pmrs[i].offset = r->पढ़ो_offset;
		submit->pmrs[i].bo_vma = etnaviv_gem_vmap(&bo->obj->base);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम submit_cleanup(काष्ठा kref *kref)
अणु
	काष्ठा etnaviv_gem_submit *submit =
			container_of(kref, काष्ठा etnaviv_gem_submit, refcount);
	अचिन्हित i;

	अगर (submit->runसमय_resumed)
		pm_runसमय_put_स्वतःsuspend(submit->gpu->dev);

	अगर (submit->cmdbuf.suballoc)
		etnaviv_cmdbuf_मुक्त(&submit->cmdbuf);

	अगर (submit->mmu_context)
		etnaviv_iommu_context_put(submit->mmu_context);

	अगर (submit->prev_mmu_context)
		etnaviv_iommu_context_put(submit->prev_mmu_context);

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा etnaviv_gem_object *etnaviv_obj = submit->bos[i].obj;

		/* unpin all objects */
		अगर (submit->bos[i].flags & BO_PINNED) अणु
			etnaviv_gem_mapping_unreference(submit->bos[i].mapping);
			atomic_dec(&etnaviv_obj->gpu_active);
			submit->bos[i].mapping = शून्य;
			submit->bos[i].flags &= ~BO_PINNED;
		पूर्ण

		/* अगर the GPU submit failed, objects might still be locked */
		submit_unlock_object(submit, i);
		drm_gem_object_put(&etnaviv_obj->base);
	पूर्ण

	wake_up_all(&submit->gpu->fence_event);

	अगर (submit->in_fence)
		dma_fence_put(submit->in_fence);
	अगर (submit->out_fence) अणु
		/* first हटाओ from IDR, so fence can not be found anymore */
		mutex_lock(&submit->gpu->fence_lock);
		idr_हटाओ(&submit->gpu->fence_idr, submit->out_fence_id);
		mutex_unlock(&submit->gpu->fence_lock);
		dma_fence_put(submit->out_fence);
	पूर्ण
	kमुक्त(submit->pmrs);
	kमुक्त(submit);
पूर्ण

व्योम etnaviv_submit_put(काष्ठा etnaviv_gem_submit *submit)
अणु
	kref_put(&submit->refcount, submit_cleanup);
पूर्ण

पूर्णांक etnaviv_ioctl_gem_submit(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	काष्ठा etnaviv_file_निजी *ctx = file->driver_priv;
	काष्ठा etnaviv_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_etnaviv_gem_submit *args = data;
	काष्ठा drm_etnaviv_gem_submit_reloc *relocs;
	काष्ठा drm_etnaviv_gem_submit_pmr *pmrs;
	काष्ठा drm_etnaviv_gem_submit_bo *bos;
	काष्ठा etnaviv_gem_submit *submit;
	काष्ठा etnaviv_gpu *gpu;
	काष्ठा sync_file *sync_file = शून्य;
	काष्ठा ww_acquire_ctx ticket;
	पूर्णांक out_fence_fd = -1;
	व्योम *stream;
	पूर्णांक ret;

	अगर (args->pipe >= ETNA_MAX_PIPES)
		वापस -EINVAL;

	gpu = priv->gpu[args->pipe];
	अगर (!gpu)
		वापस -ENXIO;

	अगर (args->stream_size % 4) अणु
		DRM_ERROR("non-aligned cmdstream buffer size: %u\n",
			  args->stream_size);
		वापस -EINVAL;
	पूर्ण

	अगर (args->exec_state != ETNA_PIPE_3D &&
	    args->exec_state != ETNA_PIPE_2D &&
	    args->exec_state != ETNA_PIPE_VG) अणु
		DRM_ERROR("invalid exec_state: 0x%x\n", args->exec_state);
		वापस -EINVAL;
	पूर्ण

	अगर (args->flags & ~ETNA_SUBMIT_FLAGS) अणु
		DRM_ERROR("invalid flags: 0x%x\n", args->flags);
		वापस -EINVAL;
	पूर्ण

	अगर ((args->flags & ETNA_SUBMIT_SOFTPIN) &&
	    priv->mmu_global->version != ETNAVIV_IOMMU_V2) अणु
		DRM_ERROR("softpin requested on incompatible MMU\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Copy the command submission and bo array to kernel space in
	 * one go, and करो this outside of any locks.
	 */
	bos = kvदो_स्मृति_array(args->nr_bos, माप(*bos), GFP_KERNEL);
	relocs = kvदो_स्मृति_array(args->nr_relocs, माप(*relocs), GFP_KERNEL);
	pmrs = kvदो_स्मृति_array(args->nr_pmrs, माप(*pmrs), GFP_KERNEL);
	stream = kvदो_स्मृति_array(1, args->stream_size, GFP_KERNEL);
	अगर (!bos || !relocs || !pmrs || !stream) अणु
		ret = -ENOMEM;
		जाओ err_submit_cmds;
	पूर्ण

	ret = copy_from_user(bos, u64_to_user_ptr(args->bos),
			     args->nr_bos * माप(*bos));
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ err_submit_cmds;
	पूर्ण

	ret = copy_from_user(relocs, u64_to_user_ptr(args->relocs),
			     args->nr_relocs * माप(*relocs));
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ err_submit_cmds;
	पूर्ण

	ret = copy_from_user(pmrs, u64_to_user_ptr(args->pmrs),
			     args->nr_pmrs * माप(*pmrs));
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ err_submit_cmds;
	पूर्ण

	ret = copy_from_user(stream, u64_to_user_ptr(args->stream),
			     args->stream_size);
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ err_submit_cmds;
	पूर्ण

	अगर (args->flags & ETNA_SUBMIT_FENCE_FD_OUT) अणु
		out_fence_fd = get_unused_fd_flags(O_CLOEXEC);
		अगर (out_fence_fd < 0) अणु
			ret = out_fence_fd;
			जाओ err_submit_cmds;
		पूर्ण
	पूर्ण

	ww_acquire_init(&ticket, &reservation_ww_class);

	submit = submit_create(dev, gpu, args->nr_bos, args->nr_pmrs);
	अगर (!submit) अणु
		ret = -ENOMEM;
		जाओ err_submit_ww_acquire;
	पूर्ण

	ret = etnaviv_cmdbuf_init(priv->cmdbuf_suballoc, &submit->cmdbuf,
				  ALIGN(args->stream_size, 8) + 8);
	अगर (ret)
		जाओ err_submit_objects;

	submit->ctx = file->driver_priv;
	etnaviv_iommu_context_get(submit->ctx->mmu);
	submit->mmu_context = submit->ctx->mmu;
	submit->exec_state = args->exec_state;
	submit->flags = args->flags;

	ret = submit_lookup_objects(submit, file, bos, args->nr_bos);
	अगर (ret)
		जाओ err_submit_objects;

	अगर ((priv->mmu_global->version != ETNAVIV_IOMMU_V2) &&
	    !etnaviv_cmd_validate_one(gpu, stream, args->stream_size / 4,
				      relocs, args->nr_relocs)) अणु
		ret = -EINVAL;
		जाओ err_submit_objects;
	पूर्ण

	अगर (args->flags & ETNA_SUBMIT_FENCE_FD_IN) अणु
		submit->in_fence = sync_file_get_fence(args->fence_fd);
		अगर (!submit->in_fence) अणु
			ret = -EINVAL;
			जाओ err_submit_objects;
		पूर्ण
	पूर्ण

	ret = submit_pin_objects(submit);
	अगर (ret)
		जाओ err_submit_objects;

	ret = submit_reloc(submit, stream, args->stream_size / 4,
			   relocs, args->nr_relocs);
	अगर (ret)
		जाओ err_submit_objects;

	ret = submit_perfmon_validate(submit, args->exec_state, pmrs);
	अगर (ret)
		जाओ err_submit_objects;

	स_नकल(submit->cmdbuf.vaddr, stream, args->stream_size);

	ret = submit_lock_objects(submit, &ticket);
	अगर (ret)
		जाओ err_submit_objects;

	ret = submit_fence_sync(submit);
	अगर (ret)
		जाओ err_submit_objects;

	ret = etnaviv_sched_push_job(&ctx->sched_entity[args->pipe], submit);
	अगर (ret)
		जाओ err_submit_objects;

	submit_attach_object_fences(submit);

	अगर (args->flags & ETNA_SUBMIT_FENCE_FD_OUT) अणु
		/*
		 * This can be improved: ideally we want to allocate the sync
		 * file beक्रमe kicking off the GPU job and just attach the
		 * fence to the sync file here, eliminating the ENOMEM
		 * possibility at this stage.
		 */
		sync_file = sync_file_create(submit->out_fence);
		अगर (!sync_file) अणु
			ret = -ENOMEM;
			जाओ err_submit_objects;
		पूर्ण
		fd_install(out_fence_fd, sync_file->file);
	पूर्ण

	args->fence_fd = out_fence_fd;
	args->fence = submit->out_fence_id;

err_submit_objects:
	etnaviv_submit_put(submit);

err_submit_ww_acquire:
	ww_acquire_fini(&ticket);

err_submit_cmds:
	अगर (ret && (out_fence_fd >= 0))
		put_unused_fd(out_fence_fd);
	अगर (stream)
		kvमुक्त(stream);
	अगर (bos)
		kvमुक्त(bos);
	अगर (relocs)
		kvमुक्त(relocs);
	अगर (pmrs)
		kvमुक्त(pmrs);

	वापस ret;
पूर्ण
