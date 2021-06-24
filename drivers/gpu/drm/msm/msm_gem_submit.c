<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/file.h>
#समावेश <linux/sync_file.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_syncobj.h>

#समावेश "msm_drv.h"
#समावेश "msm_gpu.h"
#समावेश "msm_gem.h"
#समावेश "msm_gpu_trace.h"

/*
 * Cmdstream submission:
 */

/* make sure these करोn't conflict w/ MSM_SUBMIT_BO_x */
#घोषणा BO_VALID    0x8000   /* is current addr in cmdstream correct/valid? */
#घोषणा BO_LOCKED   0x4000
#घोषणा BO_PINNED   0x2000

अटल काष्ठा msm_gem_submit *submit_create(काष्ठा drm_device *dev,
		काष्ठा msm_gpu *gpu,
		काष्ठा msm_gpu_submitqueue *queue, uपूर्णांक32_t nr_bos,
		uपूर्णांक32_t nr_cmds)
अणु
	काष्ठा msm_gem_submit *submit;
	uपूर्णांक64_t sz = काष्ठा_size(submit, bos, nr_bos) +
				  ((u64)nr_cmds * माप(submit->cmd[0]));

	अगर (sz > SIZE_MAX)
		वापस शून्य;

	submit = kदो_स्मृति(sz, GFP_KERNEL | __GFP_NOWARN | __GFP_NORETRY);
	अगर (!submit)
		वापस शून्य;

	kref_init(&submit->ref);
	submit->dev = dev;
	submit->aspace = queue->ctx->aspace;
	submit->gpu = gpu;
	submit->fence = शून्य;
	submit->cmd = (व्योम *)&submit->bos[nr_bos];
	submit->queue = queue;
	submit->ring = gpu->rb[queue->prio];

	/* initially, until copy_from_user() and bo lookup succeeds: */
	submit->nr_bos = 0;
	submit->nr_cmds = 0;

	INIT_LIST_HEAD(&submit->node);
	INIT_LIST_HEAD(&submit->bo_list);

	वापस submit;
पूर्ण

व्योम __msm_gem_submit_destroy(काष्ठा kref *kref)
अणु
	काष्ठा msm_gem_submit *submit =
			container_of(kref, काष्ठा msm_gem_submit, ref);
	अचिन्हित i;

	dma_fence_put(submit->fence);
	put_pid(submit->pid);
	msm_submitqueue_put(submit->queue);

	क्रम (i = 0; i < submit->nr_cmds; i++)
		kमुक्त(submit->cmd[i].relocs);

	kमुक्त(submit);
पूर्ण

अटल पूर्णांक submit_lookup_objects(काष्ठा msm_gem_submit *submit,
		काष्ठा drm_msm_gem_submit *args, काष्ठा drm_file *file)
अणु
	अचिन्हित i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < args->nr_bos; i++) अणु
		काष्ठा drm_msm_gem_submit_bo submit_bo;
		व्योम __user *userptr =
			u64_to_user_ptr(args->bos + (i * माप(submit_bo)));

		/* make sure we करोn't have garbage flags, in हाल we hit
		 * error path beक्रमe flags is initialized:
		 */
		submit->bos[i].flags = 0;

		अगर (copy_from_user(&submit_bo, userptr, माप(submit_bo))) अणु
			ret = -EFAULT;
			i = 0;
			जाओ out;
		पूर्ण

/* at least one of READ and/or WRITE flags should be set: */
#घोषणा MANDATORY_FLAGS (MSM_SUBMIT_BO_READ | MSM_SUBMIT_BO_WRITE)

		अगर ((submit_bo.flags & ~MSM_SUBMIT_BO_FLAGS) ||
			!(submit_bo.flags & MANDATORY_FLAGS)) अणु
			DRM_ERROR("invalid flags: %x\n", submit_bo.flags);
			ret = -EINVAL;
			i = 0;
			जाओ out;
		पूर्ण

		submit->bos[i].handle = submit_bo.handle;
		submit->bos[i].flags = submit_bo.flags;
		/* in validate_objects() we figure out अगर this is true: */
		submit->bos[i].iova  = submit_bo.presumed;
	पूर्ण

	spin_lock(&file->table_lock);

	क्रम (i = 0; i < args->nr_bos; i++) अणु
		काष्ठा drm_gem_object *obj;
		काष्ठा msm_gem_object *msm_obj;

		/* normally use drm_gem_object_lookup(), but क्रम bulk lookup
		 * all under single table_lock just hit object_idr directly:
		 */
		obj = idr_find(&file->object_idr, submit->bos[i].handle);
		अगर (!obj) अणु
			DRM_ERROR("invalid handle %u at index %u\n", submit->bos[i].handle, i);
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		msm_obj = to_msm_bo(obj);

		अगर (!list_empty(&msm_obj->submit_entry)) अणु
			DRM_ERROR("handle %u at index %u already on submit list\n",
					submit->bos[i].handle, i);
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		drm_gem_object_get(obj);

		submit->bos[i].obj = msm_obj;

		list_add_tail(&msm_obj->submit_entry, &submit->bo_list);
	पूर्ण

out_unlock:
	spin_unlock(&file->table_lock);

out:
	submit->nr_bos = i;

	वापस ret;
पूर्ण

अटल पूर्णांक submit_lookup_cmds(काष्ठा msm_gem_submit *submit,
		काष्ठा drm_msm_gem_submit *args, काष्ठा drm_file *file)
अणु
	अचिन्हित i, sz;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < args->nr_cmds; i++) अणु
		काष्ठा drm_msm_gem_submit_cmd submit_cmd;
		व्योम __user *userptr =
			u64_to_user_ptr(args->cmds + (i * माप(submit_cmd)));

		ret = copy_from_user(&submit_cmd, userptr, माप(submit_cmd));
		अगर (ret) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		/* validate input from userspace: */
		चयन (submit_cmd.type) अणु
		हाल MSM_SUBMIT_CMD_BUF:
		हाल MSM_SUBMIT_CMD_IB_TARGET_BUF:
		हाल MSM_SUBMIT_CMD_CTX_RESTORE_BUF:
			अवरोध;
		शेष:
			DRM_ERROR("invalid type: %08x\n", submit_cmd.type);
			वापस -EINVAL;
		पूर्ण

		अगर (submit_cmd.size % 4) अणु
			DRM_ERROR("non-aligned cmdstream buffer size: %u\n",
					submit_cmd.size);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		submit->cmd[i].type = submit_cmd.type;
		submit->cmd[i].size = submit_cmd.size / 4;
		submit->cmd[i].offset = submit_cmd.submit_offset / 4;
		submit->cmd[i].idx  = submit_cmd.submit_idx;
		submit->cmd[i].nr_relocs = submit_cmd.nr_relocs;

		userptr = u64_to_user_ptr(submit_cmd.relocs);

		sz = array_size(submit_cmd.nr_relocs,
				माप(काष्ठा drm_msm_gem_submit_reloc));
		/* check क्रम overflow: */
		अगर (sz == SIZE_MAX) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		submit->cmd[i].relocs = kदो_स्मृति(sz, GFP_KERNEL);
		ret = copy_from_user(submit->cmd[i].relocs, userptr, sz);
		अगर (ret) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम submit_unlock_unpin_bo(काष्ठा msm_gem_submit *submit,
		पूर्णांक i, bool backoff)
अणु
	काष्ठा msm_gem_object *msm_obj = submit->bos[i].obj;

	अगर (submit->bos[i].flags & BO_PINNED)
		msm_gem_unpin_iova_locked(&msm_obj->base, submit->aspace);

	अगर (submit->bos[i].flags & BO_LOCKED)
		dma_resv_unlock(msm_obj->base.resv);

	अगर (backoff && !(submit->bos[i].flags & BO_VALID))
		submit->bos[i].iova = 0;

	submit->bos[i].flags &= ~(BO_LOCKED | BO_PINNED);
पूर्ण

/* This is where we make sure all the bo's are reserved and pin'd: */
अटल पूर्णांक submit_lock_objects(काष्ठा msm_gem_submit *submit)
अणु
	पूर्णांक contended, slow_locked = -1, i, ret = 0;

retry:
	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा msm_gem_object *msm_obj = submit->bos[i].obj;

		अगर (slow_locked == i)
			slow_locked = -1;

		contended = i;

		अगर (!(submit->bos[i].flags & BO_LOCKED)) अणु
			ret = dma_resv_lock_पूर्णांकerruptible(msm_obj->base.resv,
							  &submit->ticket);
			अगर (ret)
				जाओ fail;
			submit->bos[i].flags |= BO_LOCKED;
		पूर्ण
	पूर्ण

	ww_acquire_करोne(&submit->ticket);

	वापस 0;

fail:
	क्रम (; i >= 0; i--)
		submit_unlock_unpin_bo(submit, i, true);

	अगर (slow_locked > 0)
		submit_unlock_unpin_bo(submit, slow_locked, true);

	अगर (ret == -EDEADLK) अणु
		काष्ठा msm_gem_object *msm_obj = submit->bos[contended].obj;
		/* we lost out in a seqno race, lock and retry.. */
		ret = dma_resv_lock_slow_पूर्णांकerruptible(msm_obj->base.resv,
						       &submit->ticket);
		अगर (!ret) अणु
			submit->bos[contended].flags |= BO_LOCKED;
			slow_locked = contended;
			जाओ retry;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक submit_fence_sync(काष्ठा msm_gem_submit *submit, bool no_implicit)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा msm_gem_object *msm_obj = submit->bos[i].obj;
		bool ग_लिखो = submit->bos[i].flags & MSM_SUBMIT_BO_WRITE;

		अगर (!ग_लिखो) अणु
			/* NOTE: _reserve_shared() must happen beक्रमe
			 * _add_shared_fence(), which makes this a slightly
			 * strange place to call it.  OTOH this is a
			 * convenient can-fail poपूर्णांक to hook it in.
			 */
			ret = dma_resv_reserve_shared(msm_obj->base.resv,
								1);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (no_implicit)
			जारी;

		ret = msm_gem_sync_object(&msm_obj->base, submit->ring->fctx,
			ग_लिखो);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक submit_pin_objects(काष्ठा msm_gem_submit *submit)
अणु
	पूर्णांक i, ret = 0;

	submit->valid = true;

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा msm_gem_object *msm_obj = submit->bos[i].obj;
		uपूर्णांक64_t iova;

		/* अगर locking succeeded, pin bo: */
		ret = msm_gem_get_and_pin_iova_locked(&msm_obj->base,
				submit->aspace, &iova);

		अगर (ret)
			अवरोध;

		submit->bos[i].flags |= BO_PINNED;

		अगर (iova == submit->bos[i].iova) अणु
			submit->bos[i].flags |= BO_VALID;
		पूर्ण अन्यथा अणु
			submit->bos[i].iova = iova;
			/* iova changed, so address in cmdstream is not valid: */
			submit->bos[i].flags &= ~BO_VALID;
			submit->valid = false;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक submit_bo(काष्ठा msm_gem_submit *submit, uपूर्णांक32_t idx,
		काष्ठा msm_gem_object **obj, uपूर्णांक64_t *iova, bool *valid)
अणु
	अगर (idx >= submit->nr_bos) अणु
		DRM_ERROR("invalid buffer index: %u (out of %u)\n",
				idx, submit->nr_bos);
		वापस -EINVAL;
	पूर्ण

	अगर (obj)
		*obj = submit->bos[idx].obj;
	अगर (iova)
		*iova = submit->bos[idx].iova;
	अगर (valid)
		*valid = !!(submit->bos[idx].flags & BO_VALID);

	वापस 0;
पूर्ण

/* process the reloc's and patch up the cmdstream as needed: */
अटल पूर्णांक submit_reloc(काष्ठा msm_gem_submit *submit, काष्ठा msm_gem_object *obj,
		uपूर्णांक32_t offset, uपूर्णांक32_t nr_relocs, काष्ठा drm_msm_gem_submit_reloc *relocs)
अणु
	uपूर्णांक32_t i, last_offset = 0;
	uपूर्णांक32_t *ptr;
	पूर्णांक ret = 0;

	अगर (!nr_relocs)
		वापस 0;

	अगर (offset % 4) अणु
		DRM_ERROR("non-aligned cmdstream buffer: %u\n", offset);
		वापस -EINVAL;
	पूर्ण

	/* For now, just map the entire thing.  Eventually we probably
	 * to करो it page-by-page, w/ kmap() अगर not vmap()d..
	 */
	ptr = msm_gem_get_vaddr_locked(&obj->base);

	अगर (IS_ERR(ptr)) अणु
		ret = PTR_ERR(ptr);
		DBG("failed to map: %d", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < nr_relocs; i++) अणु
		काष्ठा drm_msm_gem_submit_reloc submit_reloc = relocs[i];
		uपूर्णांक32_t off;
		uपूर्णांक64_t iova;
		bool valid;

		अगर (submit_reloc.submit_offset % 4) अणु
			DRM_ERROR("non-aligned reloc offset: %u\n",
					submit_reloc.submit_offset);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		/* offset in dwords: */
		off = submit_reloc.submit_offset / 4;

		अगर ((off >= (obj->base.size / 4)) ||
				(off < last_offset)) अणु
			DRM_ERROR("invalid offset %u at reloc %u\n", off, i);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		ret = submit_bo(submit, submit_reloc.reloc_idx, शून्य, &iova, &valid);
		अगर (ret)
			जाओ out;

		अगर (valid)
			जारी;

		iova += submit_reloc.reloc_offset;

		अगर (submit_reloc.shअगरt < 0)
			iova >>= -submit_reloc.shअगरt;
		अन्यथा
			iova <<= submit_reloc.shअगरt;

		ptr[off] = iova | submit_reloc.or;

		last_offset = off;
	पूर्ण

out:
	msm_gem_put_vaddr_locked(&obj->base);

	वापस ret;
पूर्ण

अटल व्योम submit_cleanup(काष्ठा msm_gem_submit *submit)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा msm_gem_object *msm_obj = submit->bos[i].obj;
		submit_unlock_unpin_bo(submit, i, false);
		list_del_init(&msm_obj->submit_entry);
		drm_gem_object_put_locked(&msm_obj->base);
	पूर्ण
पूर्ण


काष्ठा msm_submit_post_dep अणु
	काष्ठा drm_syncobj *syncobj;
	uपूर्णांक64_t poपूर्णांक;
	काष्ठा dma_fence_chain *chain;
पूर्ण;

अटल काष्ठा drm_syncobj **msm_रुको_deps(काष्ठा drm_device *dev,
                                          काष्ठा drm_file *file,
                                          uपूर्णांक64_t in_syncobjs_addr,
                                          uपूर्णांक32_t nr_in_syncobjs,
                                          माप_प्रकार syncobj_stride,
                                          काष्ठा msm_ringbuffer *ring)
अणु
	काष्ठा drm_syncobj **syncobjs = शून्य;
	काष्ठा drm_msm_gem_submit_syncobj syncobj_desc = अणु0पूर्ण;
	पूर्णांक ret = 0;
	uपूर्णांक32_t i, j;

	syncobjs = kसुस्मृति(nr_in_syncobjs, माप(*syncobjs),
	                   GFP_KERNEL | __GFP_NOWARN | __GFP_NORETRY);
	अगर (!syncobjs)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < nr_in_syncobjs; ++i) अणु
		uपूर्णांक64_t address = in_syncobjs_addr + i * syncobj_stride;
		काष्ठा dma_fence *fence;

		अगर (copy_from_user(&syncobj_desc,
			           u64_to_user_ptr(address),
			           min(syncobj_stride, माप(syncobj_desc)))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (syncobj_desc.poपूर्णांक &&
		    !drm_core_check_feature(dev, DRIVER_SYNCOBJ_TIMELINE)) अणु
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		अगर (syncobj_desc.flags & ~MSM_SUBMIT_SYNCOBJ_FLAGS) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ret = drm_syncobj_find_fence(file, syncobj_desc.handle,
		                             syncobj_desc.poपूर्णांक, 0, &fence);
		अगर (ret)
			अवरोध;

		अगर (!dma_fence_match_context(fence, ring->fctx->context))
			ret = dma_fence_रुको(fence, true);

		dma_fence_put(fence);
		अगर (ret)
			अवरोध;

		अगर (syncobj_desc.flags & MSM_SUBMIT_SYNCOBJ_RESET) अणु
			syncobjs[i] =
				drm_syncobj_find(file, syncobj_desc.handle);
			अगर (!syncobjs[i]) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		क्रम (j = 0; j <= i; ++j) अणु
			अगर (syncobjs[j])
				drm_syncobj_put(syncobjs[j]);
		पूर्ण
		kमुक्त(syncobjs);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस syncobjs;
पूर्ण

अटल व्योम msm_reset_syncobjs(काष्ठा drm_syncobj **syncobjs,
                               uपूर्णांक32_t nr_syncobjs)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; syncobjs && i < nr_syncobjs; ++i) अणु
		अगर (syncobjs[i])
			drm_syncobj_replace_fence(syncobjs[i], शून्य);
	पूर्ण
पूर्ण

अटल काष्ठा msm_submit_post_dep *msm_parse_post_deps(काष्ठा drm_device *dev,
                                                       काष्ठा drm_file *file,
                                                       uपूर्णांक64_t syncobjs_addr,
                                                       uपूर्णांक32_t nr_syncobjs,
                                                       माप_प्रकार syncobj_stride)
अणु
	काष्ठा msm_submit_post_dep *post_deps;
	काष्ठा drm_msm_gem_submit_syncobj syncobj_desc = अणु0पूर्ण;
	पूर्णांक ret = 0;
	uपूर्णांक32_t i, j;

	post_deps = kदो_स्मृति_array(nr_syncobjs, माप(*post_deps),
	                          GFP_KERNEL | __GFP_NOWARN | __GFP_NORETRY);
	अगर (!post_deps)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < nr_syncobjs; ++i) अणु
		uपूर्णांक64_t address = syncobjs_addr + i * syncobj_stride;

		अगर (copy_from_user(&syncobj_desc,
			           u64_to_user_ptr(address),
			           min(syncobj_stride, माप(syncobj_desc)))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		post_deps[i].poपूर्णांक = syncobj_desc.poपूर्णांक;
		post_deps[i].chain = शून्य;

		अगर (syncobj_desc.flags) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (syncobj_desc.poपूर्णांक) अणु
			अगर (!drm_core_check_feature(dev,
			                            DRIVER_SYNCOBJ_TIMELINE)) अणु
				ret = -EOPNOTSUPP;
				अवरोध;
			पूर्ण

			post_deps[i].chain =
				kदो_स्मृति(माप(*post_deps[i].chain),
				        GFP_KERNEL);
			अगर (!post_deps[i].chain) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण
		पूर्ण

		post_deps[i].syncobj =
			drm_syncobj_find(file, syncobj_desc.handle);
		अगर (!post_deps[i].syncobj) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		क्रम (j = 0; j <= i; ++j) अणु
			kमुक्त(post_deps[j].chain);
			अगर (post_deps[j].syncobj)
				drm_syncobj_put(post_deps[j].syncobj);
		पूर्ण

		kमुक्त(post_deps);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस post_deps;
पूर्ण

अटल व्योम msm_process_post_deps(काष्ठा msm_submit_post_dep *post_deps,
                                  uपूर्णांक32_t count, काष्ठा dma_fence *fence)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; post_deps && i < count; ++i) अणु
		अगर (post_deps[i].chain) अणु
			drm_syncobj_add_poपूर्णांक(post_deps[i].syncobj,
			                      post_deps[i].chain,
			                      fence, post_deps[i].poपूर्णांक);
			post_deps[i].chain = शून्य;
		पूर्ण अन्यथा अणु
			drm_syncobj_replace_fence(post_deps[i].syncobj,
			                          fence);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक msm_ioctl_gem_submit(काष्ठा drm_device *dev, व्योम *data,
		काष्ठा drm_file *file)
अणु
	अटल atomic_t ident = ATOMIC_INIT(0);
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_msm_gem_submit *args = data;
	काष्ठा msm_file_निजी *ctx = file->driver_priv;
	काष्ठा msm_gem_submit *submit;
	काष्ठा msm_gpu *gpu = priv->gpu;
	काष्ठा sync_file *sync_file = शून्य;
	काष्ठा msm_gpu_submitqueue *queue;
	काष्ठा msm_ringbuffer *ring;
	काष्ठा msm_submit_post_dep *post_deps = शून्य;
	काष्ठा drm_syncobj **syncobjs_to_reset = शून्य;
	पूर्णांक out_fence_fd = -1;
	काष्ठा pid *pid = get_pid(task_pid(current));
	bool has_ww_ticket = false;
	अचिन्हित i;
	पूर्णांक ret, submitid;
	अगर (!gpu)
		वापस -ENXIO;

	अगर (args->pad)
		वापस -EINVAL;

	/* क्रम now, we just have 3d pipe.. eventually this would need to
	 * be more clever to dispatch to appropriate gpu module:
	 */
	अगर (MSM_PIPE_ID(args->flags) != MSM_PIPE_3D0)
		वापस -EINVAL;

	अगर (MSM_PIPE_FLAGS(args->flags) & ~MSM_SUBMIT_FLAGS)
		वापस -EINVAL;

	अगर (args->flags & MSM_SUBMIT_SUDO) अणु
		अगर (!IS_ENABLED(CONFIG_DRM_MSM_GPU_SUDO) ||
		    !capable(CAP_SYS_RAWIO))
			वापस -EINVAL;
	पूर्ण

	queue = msm_submitqueue_get(ctx, args->queueid);
	अगर (!queue)
		वापस -ENOENT;

	/* Get a unique identअगरier क्रम the submission क्रम logging purposes */
	submitid = atomic_inc_वापस(&ident) - 1;

	ring = gpu->rb[queue->prio];
	trace_msm_gpu_submit(pid_nr(pid), ring->id, submitid,
		args->nr_bos, args->nr_cmds);

	अगर (args->flags & MSM_SUBMIT_FENCE_FD_IN) अणु
		काष्ठा dma_fence *in_fence;

		in_fence = sync_file_get_fence(args->fence_fd);

		अगर (!in_fence)
			वापस -EINVAL;

		/*
		 * Wait अगर the fence is from a क्रमeign context, or अगर the fence
		 * array contains any fence from a क्रमeign context.
		 */
		ret = 0;
		अगर (!dma_fence_match_context(in_fence, ring->fctx->context))
			ret = dma_fence_रुको(in_fence, true);

		dma_fence_put(in_fence);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (args->flags & MSM_SUBMIT_SYNCOBJ_IN) अणु
		syncobjs_to_reset = msm_रुको_deps(dev, file,
		                                  args->in_syncobjs,
		                                  args->nr_in_syncobjs,
		                                  args->syncobj_stride, ring);
		अगर (IS_ERR(syncobjs_to_reset))
			वापस PTR_ERR(syncobjs_to_reset);
	पूर्ण

	अगर (args->flags & MSM_SUBMIT_SYNCOBJ_OUT) अणु
		post_deps = msm_parse_post_deps(dev, file,
		                                args->out_syncobjs,
		                                args->nr_out_syncobjs,
		                                args->syncobj_stride);
		अगर (IS_ERR(post_deps)) अणु
			ret = PTR_ERR(post_deps);
			जाओ out_post_unlock;
		पूर्ण
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&dev->काष्ठा_mutex);
	अगर (ret)
		जाओ out_post_unlock;

	अगर (args->flags & MSM_SUBMIT_FENCE_FD_OUT) अणु
		out_fence_fd = get_unused_fd_flags(O_CLOEXEC);
		अगर (out_fence_fd < 0) अणु
			ret = out_fence_fd;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	submit = submit_create(dev, gpu, queue, args->nr_bos,
		args->nr_cmds);
	अगर (!submit) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	submit->pid = pid;
	submit->ident = submitid;

	अगर (args->flags & MSM_SUBMIT_SUDO)
		submit->in_rb = true;

	ret = submit_lookup_objects(submit, args, file);
	अगर (ret)
		जाओ out_pre_pm;

	ret = submit_lookup_cmds(submit, args, file);
	अगर (ret)
		जाओ out_pre_pm;

	/*
	 * Thanks to dev_pm_opp opp_table_lock पूर्णांकeractions with mm->mmap_sem
	 * in the resume path, we need to to rpm get beक्रमe we lock objs.
	 * Which unक्रमtunately might involve घातering up the GPU sooner than
	 * is necessary.  But at least in the explicit fencing हाल, we will
	 * have alपढ़ोy करोne all the fence रुकोing.
	 */
	pm_runसमय_get_sync(&gpu->pdev->dev);

	/* copy_*_user जबतक holding a ww ticket upsets lockdep */
	ww_acquire_init(&submit->ticket, &reservation_ww_class);
	has_ww_ticket = true;
	ret = submit_lock_objects(submit);
	अगर (ret)
		जाओ out;

	ret = submit_fence_sync(submit, !!(args->flags & MSM_SUBMIT_NO_IMPLICIT));
	अगर (ret)
		जाओ out;

	ret = submit_pin_objects(submit);
	अगर (ret)
		जाओ out;

	क्रम (i = 0; i < args->nr_cmds; i++) अणु
		काष्ठा msm_gem_object *msm_obj;
		uपूर्णांक64_t iova;

		ret = submit_bo(submit, submit->cmd[i].idx,
				&msm_obj, &iova, शून्य);
		अगर (ret)
			जाओ out;

		अगर (!submit->cmd[i].size ||
			((submit->cmd[i].size + submit->cmd[i].offset) >
				msm_obj->base.size / 4)) अणु
			DRM_ERROR("invalid cmdstream size: %u\n", submit->cmd[i].size * 4);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		submit->cmd[i].iova = iova + (submit->cmd[i].offset * 4);

		अगर (submit->valid)
			जारी;

		ret = submit_reloc(submit, msm_obj, submit->cmd[i].offset * 4,
				submit->cmd[i].nr_relocs, submit->cmd[i].relocs);
		अगर (ret)
			जाओ out;
	पूर्ण

	submit->nr_cmds = i;

	submit->fence = msm_fence_alloc(ring->fctx);
	अगर (IS_ERR(submit->fence)) अणु
		ret = PTR_ERR(submit->fence);
		submit->fence = शून्य;
		जाओ out;
	पूर्ण

	अगर (args->flags & MSM_SUBMIT_FENCE_FD_OUT) अणु
		sync_file = sync_file_create(submit->fence);
		अगर (!sync_file) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	msm_gpu_submit(gpu, submit);

	args->fence = submit->fence->seqno;

	अगर (args->flags & MSM_SUBMIT_FENCE_FD_OUT) अणु
		fd_install(out_fence_fd, sync_file->file);
		args->fence_fd = out_fence_fd;
	पूर्ण

	msm_reset_syncobjs(syncobjs_to_reset, args->nr_in_syncobjs);
	msm_process_post_deps(post_deps, args->nr_out_syncobjs,
	                      submit->fence);


out:
	pm_runसमय_put(&gpu->pdev->dev);
out_pre_pm:
	submit_cleanup(submit);
	अगर (has_ww_ticket)
		ww_acquire_fini(&submit->ticket);
	msm_gem_submit_put(submit);
out_unlock:
	अगर (ret && (out_fence_fd >= 0))
		put_unused_fd(out_fence_fd);
	mutex_unlock(&dev->काष्ठा_mutex);

out_post_unlock:
	अगर (!IS_ERR_OR_शून्य(post_deps)) अणु
		क्रम (i = 0; i < args->nr_out_syncobjs; ++i) अणु
			kमुक्त(post_deps[i].chain);
			drm_syncobj_put(post_deps[i].syncobj);
		पूर्ण
		kमुक्त(post_deps);
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(syncobjs_to_reset)) अणु
		क्रम (i = 0; i < args->nr_in_syncobjs; ++i) अणु
			अगर (syncobjs_to_reset[i])
				drm_syncobj_put(syncobjs_to_reset[i]);
		पूर्ण
		kमुक्त(syncobjs_to_reset);
	पूर्ण

	वापस ret;
पूर्ण
