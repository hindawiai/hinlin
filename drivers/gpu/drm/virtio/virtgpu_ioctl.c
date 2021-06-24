<शैली गुरु>
/*
 * Copyright (C) 2015 Red Hat, Inc.
 * All Rights Reserved.
 *
 * Authors:
 *    Dave Airlie
 *    Alon Levy
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

#समावेश <linux/file.h>
#समावेश <linux/sync_file.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_file.h>
#समावेश <drm/virtgpu_drm.h>

#समावेश "virtgpu_drv.h"

#घोषणा VIRTGPU_BLOB_FLAG_USE_MASK (VIRTGPU_BLOB_FLAG_USE_MAPPABLE | \
				    VIRTGPU_BLOB_FLAG_USE_SHAREABLE | \
				    VIRTGPU_BLOB_FLAG_USE_CROSS_DEVICE)

व्योम virtio_gpu_create_context(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_fpriv *vfpriv = file->driver_priv;
	अक्षर dbgname[TASK_COMM_LEN];

	mutex_lock(&vfpriv->context_lock);
	अगर (vfpriv->context_created)
		जाओ out_unlock;

	get_task_comm(dbgname, current);
	virtio_gpu_cmd_context_create(vgdev, vfpriv->ctx_id,
				      म_माप(dbgname), dbgname);
	vfpriv->context_created = true;

out_unlock:
	mutex_unlock(&vfpriv->context_lock);
पूर्ण

अटल पूर्णांक virtio_gpu_map_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file)
अणु
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा drm_virtgpu_map *virtio_gpu_map = data;

	वापस virtio_gpu_mode_dumb_mmap(file, vgdev->ddev,
					 virtio_gpu_map->handle,
					 &virtio_gpu_map->offset);
पूर्ण

/*
 * Usage of execbuffer:
 * Relocations need to take पूर्णांकo account the full VIRTIO_GPUDrawable size.
 * However, the command as passed from user space must *not* contain the initial
 * VIRTIO_GPUReleaseInfo काष्ठा (first XXX bytes)
 */
अटल पूर्णांक virtio_gpu_execbuffer_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file)
अणु
	काष्ठा drm_virtgpu_execbuffer *exbuf = data;
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_fpriv *vfpriv = file->driver_priv;
	काष्ठा virtio_gpu_fence *out_fence;
	पूर्णांक ret;
	uपूर्णांक32_t *bo_handles = शून्य;
	व्योम __user *user_bo_handles = शून्य;
	काष्ठा virtio_gpu_object_array *buflist = शून्य;
	काष्ठा sync_file *sync_file;
	पूर्णांक in_fence_fd = exbuf->fence_fd;
	पूर्णांक out_fence_fd = -1;
	व्योम *buf;

	अगर (vgdev->has_virgl_3d == false)
		वापस -ENOSYS;

	अगर ((exbuf->flags & ~VIRTGPU_EXECBUF_FLAGS))
		वापस -EINVAL;

	exbuf->fence_fd = -1;

	virtio_gpu_create_context(dev, file);
	अगर (exbuf->flags & VIRTGPU_EXECBUF_FENCE_FD_IN) अणु
		काष्ठा dma_fence *in_fence;

		in_fence = sync_file_get_fence(in_fence_fd);

		अगर (!in_fence)
			वापस -EINVAL;

		/*
		 * Wait अगर the fence is from a क्रमeign context, or अगर the fence
		 * array contains any fence from a क्रमeign context.
		 */
		ret = 0;
		अगर (!dma_fence_match_context(in_fence, vgdev->fence_drv.context))
			ret = dma_fence_रुको(in_fence, true);

		dma_fence_put(in_fence);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (exbuf->flags & VIRTGPU_EXECBUF_FENCE_FD_OUT) अणु
		out_fence_fd = get_unused_fd_flags(O_CLOEXEC);
		अगर (out_fence_fd < 0)
			वापस out_fence_fd;
	पूर्ण

	अगर (exbuf->num_bo_handles) अणु
		bo_handles = kvदो_स्मृति_array(exbuf->num_bo_handles,
					    माप(uपूर्णांक32_t), GFP_KERNEL);
		अगर (!bo_handles) अणु
			ret = -ENOMEM;
			जाओ out_unused_fd;
		पूर्ण

		user_bo_handles = u64_to_user_ptr(exbuf->bo_handles);
		अगर (copy_from_user(bo_handles, user_bo_handles,
				   exbuf->num_bo_handles * माप(uपूर्णांक32_t))) अणु
			ret = -EFAULT;
			जाओ out_unused_fd;
		पूर्ण

		buflist = virtio_gpu_array_from_handles(file, bo_handles,
							exbuf->num_bo_handles);
		अगर (!buflist) अणु
			ret = -ENOENT;
			जाओ out_unused_fd;
		पूर्ण
		kvमुक्त(bo_handles);
		bo_handles = शून्य;
	पूर्ण

	buf = vmemdup_user(u64_to_user_ptr(exbuf->command), exbuf->size);
	अगर (IS_ERR(buf)) अणु
		ret = PTR_ERR(buf);
		जाओ out_unused_fd;
	पूर्ण

	अगर (buflist) अणु
		ret = virtio_gpu_array_lock_resv(buflist);
		अगर (ret)
			जाओ out_memdup;
	पूर्ण

	out_fence = virtio_gpu_fence_alloc(vgdev);
	अगर(!out_fence) अणु
		ret = -ENOMEM;
		जाओ out_unresv;
	पूर्ण

	अगर (out_fence_fd >= 0) अणु
		sync_file = sync_file_create(&out_fence->f);
		अगर (!sync_file) अणु
			dma_fence_put(&out_fence->f);
			ret = -ENOMEM;
			जाओ out_unresv;
		पूर्ण

		exbuf->fence_fd = out_fence_fd;
		fd_install(out_fence_fd, sync_file->file);
	पूर्ण

	virtio_gpu_cmd_submit(vgdev, buf, exbuf->size,
			      vfpriv->ctx_id, buflist, out_fence);
	dma_fence_put(&out_fence->f);
	virtio_gpu_notअगरy(vgdev);
	वापस 0;

out_unresv:
	अगर (buflist)
		virtio_gpu_array_unlock_resv(buflist);
out_memdup:
	kvमुक्त(buf);
out_unused_fd:
	kvमुक्त(bo_handles);
	अगर (buflist)
		virtio_gpu_array_put_मुक्त(buflist);

	अगर (out_fence_fd >= 0)
		put_unused_fd(out_fence_fd);

	वापस ret;
पूर्ण

अटल पूर्णांक virtio_gpu_getparam_ioctl(काष्ठा drm_device *dev, व्योम *data,
				     काष्ठा drm_file *file)
अणु
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा drm_virtgpu_getparam *param = data;
	पूर्णांक value;

	चयन (param->param) अणु
	हाल VIRTGPU_PARAM_3D_FEATURES:
		value = vgdev->has_virgl_3d ? 1 : 0;
		अवरोध;
	हाल VIRTGPU_PARAM_CAPSET_QUERY_FIX:
		value = 1;
		अवरोध;
	हाल VIRTGPU_PARAM_RESOURCE_BLOB:
		value = vgdev->has_resource_blob ? 1 : 0;
		अवरोध;
	हाल VIRTGPU_PARAM_HOST_VISIBLE:
		value = vgdev->has_host_visible ? 1 : 0;
		अवरोध;
	हाल VIRTGPU_PARAM_CROSS_DEVICE:
		value = vgdev->has_resource_assign_uuid ? 1 : 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (copy_to_user(u64_to_user_ptr(param->value), &value, माप(पूर्णांक)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक virtio_gpu_resource_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
					    काष्ठा drm_file *file)
अणु
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा drm_virtgpu_resource_create *rc = data;
	काष्ठा virtio_gpu_fence *fence;
	पूर्णांक ret;
	काष्ठा virtio_gpu_object *qobj;
	काष्ठा drm_gem_object *obj;
	uपूर्णांक32_t handle = 0;
	काष्ठा virtio_gpu_object_params params = अणु 0 पूर्ण;

	अगर (vgdev->has_virgl_3d) अणु
		virtio_gpu_create_context(dev, file);
		params.virgl = true;
		params.target = rc->target;
		params.bind = rc->bind;
		params.depth = rc->depth;
		params.array_size = rc->array_size;
		params.last_level = rc->last_level;
		params.nr_samples = rc->nr_samples;
		params.flags = rc->flags;
	पूर्ण अन्यथा अणु
		अगर (rc->depth > 1)
			वापस -EINVAL;
		अगर (rc->nr_samples > 1)
			वापस -EINVAL;
		अगर (rc->last_level > 1)
			वापस -EINVAL;
		अगर (rc->target != 2)
			वापस -EINVAL;
		अगर (rc->array_size > 1)
			वापस -EINVAL;
	पूर्ण

	params.क्रमmat = rc->क्रमmat;
	params.width = rc->width;
	params.height = rc->height;
	params.size = rc->size;
	/* allocate a single page size object */
	अगर (params.size == 0)
		params.size = PAGE_SIZE;

	fence = virtio_gpu_fence_alloc(vgdev);
	अगर (!fence)
		वापस -ENOMEM;
	ret = virtio_gpu_object_create(vgdev, &params, &qobj, fence);
	dma_fence_put(&fence->f);
	अगर (ret < 0)
		वापस ret;
	obj = &qobj->base.base;

	ret = drm_gem_handle_create(file, obj, &handle);
	अगर (ret) अणु
		drm_gem_object_release(obj);
		वापस ret;
	पूर्ण
	drm_gem_object_put(obj);

	rc->res_handle = qobj->hw_res_handle; /* similiar to a VM address */
	rc->bo_handle = handle;
	वापस 0;
पूर्ण

अटल पूर्णांक virtio_gpu_resource_info_ioctl(काष्ठा drm_device *dev, व्योम *data,
					  काष्ठा drm_file *file)
अणु
	काष्ठा drm_virtgpu_resource_info *ri = data;
	काष्ठा drm_gem_object *gobj = शून्य;
	काष्ठा virtio_gpu_object *qobj = शून्य;

	gobj = drm_gem_object_lookup(file, ri->bo_handle);
	अगर (gobj == शून्य)
		वापस -ENOENT;

	qobj = gem_to_virtio_gpu_obj(gobj);

	ri->size = qobj->base.base.size;
	ri->res_handle = qobj->hw_res_handle;
	अगर (qobj->host3d_blob || qobj->guest_blob)
		ri->blob_mem = qobj->blob_mem;

	drm_gem_object_put(gobj);
	वापस 0;
पूर्ण

अटल पूर्णांक virtio_gpu_transfer_from_host_ioctl(काष्ठा drm_device *dev,
					       व्योम *data,
					       काष्ठा drm_file *file)
अणु
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_fpriv *vfpriv = file->driver_priv;
	काष्ठा drm_virtgpu_3d_transfer_from_host *args = data;
	काष्ठा virtio_gpu_object *bo;
	काष्ठा virtio_gpu_object_array *objs;
	काष्ठा virtio_gpu_fence *fence;
	पूर्णांक ret;
	u32 offset = args->offset;

	अगर (vgdev->has_virgl_3d == false)
		वापस -ENOSYS;

	virtio_gpu_create_context(dev, file);
	objs = virtio_gpu_array_from_handles(file, &args->bo_handle, 1);
	अगर (objs == शून्य)
		वापस -ENOENT;

	bo = gem_to_virtio_gpu_obj(objs->objs[0]);
	अगर (bo->guest_blob && !bo->host3d_blob) अणु
		ret = -EINVAL;
		जाओ err_put_मुक्त;
	पूर्ण

	अगर (!bo->host3d_blob && (args->stride || args->layer_stride)) अणु
		ret = -EINVAL;
		जाओ err_put_मुक्त;
	पूर्ण

	ret = virtio_gpu_array_lock_resv(objs);
	अगर (ret != 0)
		जाओ err_put_मुक्त;

	fence = virtio_gpu_fence_alloc(vgdev);
	अगर (!fence) अणु
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	virtio_gpu_cmd_transfer_from_host_3d
		(vgdev, vfpriv->ctx_id, offset, args->level, args->stride,
		 args->layer_stride, &args->box, objs, fence);
	dma_fence_put(&fence->f);
	virtio_gpu_notअगरy(vgdev);
	वापस 0;

err_unlock:
	virtio_gpu_array_unlock_resv(objs);
err_put_मुक्त:
	virtio_gpu_array_put_मुक्त(objs);
	वापस ret;
पूर्ण

अटल पूर्णांक virtio_gpu_transfer_to_host_ioctl(काष्ठा drm_device *dev, व्योम *data,
					     काष्ठा drm_file *file)
अणु
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_fpriv *vfpriv = file->driver_priv;
	काष्ठा drm_virtgpu_3d_transfer_to_host *args = data;
	काष्ठा virtio_gpu_object *bo;
	काष्ठा virtio_gpu_object_array *objs;
	काष्ठा virtio_gpu_fence *fence;
	पूर्णांक ret;
	u32 offset = args->offset;

	objs = virtio_gpu_array_from_handles(file, &args->bo_handle, 1);
	अगर (objs == शून्य)
		वापस -ENOENT;

	bo = gem_to_virtio_gpu_obj(objs->objs[0]);
	अगर (bo->guest_blob && !bo->host3d_blob) अणु
		ret = -EINVAL;
		जाओ err_put_मुक्त;
	पूर्ण

	अगर (!vgdev->has_virgl_3d) अणु
		virtio_gpu_cmd_transfer_to_host_2d
			(vgdev, offset,
			 args->box.w, args->box.h, args->box.x, args->box.y,
			 objs, शून्य);
	पूर्ण अन्यथा अणु
		virtio_gpu_create_context(dev, file);

		अगर (!bo->host3d_blob && (args->stride || args->layer_stride)) अणु
			ret = -EINVAL;
			जाओ err_put_मुक्त;
		पूर्ण

		ret = virtio_gpu_array_lock_resv(objs);
		अगर (ret != 0)
			जाओ err_put_मुक्त;

		ret = -ENOMEM;
		fence = virtio_gpu_fence_alloc(vgdev);
		अगर (!fence)
			जाओ err_unlock;

		virtio_gpu_cmd_transfer_to_host_3d
			(vgdev,
			 vfpriv ? vfpriv->ctx_id : 0, offset, args->level,
			 args->stride, args->layer_stride, &args->box, objs,
			 fence);
		dma_fence_put(&fence->f);
	पूर्ण
	virtio_gpu_notअगरy(vgdev);
	वापस 0;

err_unlock:
	virtio_gpu_array_unlock_resv(objs);
err_put_मुक्त:
	virtio_gpu_array_put_मुक्त(objs);
	वापस ret;
पूर्ण

अटल पूर्णांक virtio_gpu_रुको_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file)
अणु
	काष्ठा drm_virtgpu_3d_रुको *args = data;
	काष्ठा drm_gem_object *obj;
	दीर्घ समयout = 15 * HZ;
	पूर्णांक ret;

	obj = drm_gem_object_lookup(file, args->handle);
	अगर (obj == शून्य)
		वापस -ENOENT;

	अगर (args->flags & VIRTGPU_WAIT_NOWAIT) अणु
		ret = dma_resv_test_संकेतed_rcu(obj->resv, true);
	पूर्ण अन्यथा अणु
		ret = dma_resv_रुको_समयout_rcu(obj->resv, true, true,
						समयout);
	पूर्ण
	अगर (ret == 0)
		ret = -EBUSY;
	अन्यथा अगर (ret > 0)
		ret = 0;

	drm_gem_object_put(obj);
	वापस ret;
पूर्ण

अटल पूर्णांक virtio_gpu_get_caps_ioctl(काष्ठा drm_device *dev,
				व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा drm_virtgpu_get_caps *args = data;
	अचिन्हित size, host_caps_size;
	पूर्णांक i;
	पूर्णांक found_valid = -1;
	पूर्णांक ret;
	काष्ठा virtio_gpu_drv_cap_cache *cache_ent;
	व्योम *ptr;

	अगर (vgdev->num_capsets == 0)
		वापस -ENOSYS;

	/* करोn't allow userspace to pass 0 */
	अगर (args->size == 0)
		वापस -EINVAL;

	spin_lock(&vgdev->display_info_lock);
	क्रम (i = 0; i < vgdev->num_capsets; i++) अणु
		अगर (vgdev->capsets[i].id == args->cap_set_id) अणु
			अगर (vgdev->capsets[i].max_version >= args->cap_set_ver) अणु
				found_valid = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (found_valid == -1) अणु
		spin_unlock(&vgdev->display_info_lock);
		वापस -EINVAL;
	पूर्ण

	host_caps_size = vgdev->capsets[found_valid].max_size;
	/* only copy to user the minimum of the host caps size or the guest caps size */
	size = min(args->size, host_caps_size);

	list_क्रम_each_entry(cache_ent, &vgdev->cap_cache, head) अणु
		अगर (cache_ent->id == args->cap_set_id &&
		    cache_ent->version == args->cap_set_ver) अणु
			spin_unlock(&vgdev->display_info_lock);
			जाओ copy_निकास;
		पूर्ण
	पूर्ण
	spin_unlock(&vgdev->display_info_lock);

	/* not in cache - need to talk to hw */
	virtio_gpu_cmd_get_capset(vgdev, found_valid, args->cap_set_ver,
				  &cache_ent);
	virtio_gpu_notअगरy(vgdev);

copy_निकास:
	ret = रुको_event_समयout(vgdev->resp_wq,
				 atomic_पढ़ो(&cache_ent->is_valid), 5 * HZ);
	अगर (!ret)
		वापस -EBUSY;

	/* is_valid check must proceed beक्रमe copy of the cache entry. */
	smp_rmb();

	ptr = cache_ent->caps_cache;

	अगर (copy_to_user(u64_to_user_ptr(args->addr), ptr, size))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_blob(काष्ठा virtio_gpu_device *vgdev,
		       काष्ठा virtio_gpu_fpriv *vfpriv,
		       काष्ठा virtio_gpu_object_params *params,
		       काष्ठा drm_virtgpu_resource_create_blob *rc_blob,
		       bool *guest_blob, bool *host3d_blob)
अणु
	अगर (!vgdev->has_resource_blob)
		वापस -EINVAL;

	अगर ((rc_blob->blob_flags & ~VIRTGPU_BLOB_FLAG_USE_MASK) ||
	    !rc_blob->blob_flags)
		वापस -EINVAL;

	अगर (rc_blob->blob_flags & VIRTGPU_BLOB_FLAG_USE_CROSS_DEVICE) अणु
		अगर (!vgdev->has_resource_assign_uuid)
			वापस -EINVAL;
	पूर्ण

	चयन (rc_blob->blob_mem) अणु
	हाल VIRTGPU_BLOB_MEM_GUEST:
		*guest_blob = true;
		अवरोध;
	हाल VIRTGPU_BLOB_MEM_HOST3D_GUEST:
		*guest_blob = true;
		fallthrough;
	हाल VIRTGPU_BLOB_MEM_HOST3D:
		*host3d_blob = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (*host3d_blob) अणु
		अगर (!vgdev->has_virgl_3d)
			वापस -EINVAL;

		/* Must be dword aligned. */
		अगर (rc_blob->cmd_size % 4 != 0)
			वापस -EINVAL;

		params->ctx_id = vfpriv->ctx_id;
		params->blob_id = rc_blob->blob_id;
	पूर्ण अन्यथा अणु
		अगर (rc_blob->blob_id != 0)
			वापस -EINVAL;

		अगर (rc_blob->cmd_size != 0)
			वापस -EINVAL;
	पूर्ण

	params->blob_mem = rc_blob->blob_mem;
	params->size = rc_blob->size;
	params->blob = true;
	params->blob_flags = rc_blob->blob_flags;
	वापस 0;
पूर्ण

अटल पूर्णांक virtio_gpu_resource_create_blob_ioctl(काष्ठा drm_device *dev,
						 व्योम *data,
						 काष्ठा drm_file *file)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t handle = 0;
	bool guest_blob = false;
	bool host3d_blob = false;
	काष्ठा drm_gem_object *obj;
	काष्ठा virtio_gpu_object *bo;
	काष्ठा virtio_gpu_object_params params = अणु 0 पूर्ण;
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_fpriv *vfpriv = file->driver_priv;
	काष्ठा drm_virtgpu_resource_create_blob *rc_blob = data;

	अगर (verअगरy_blob(vgdev, vfpriv, &params, rc_blob,
			&guest_blob, &host3d_blob))
		वापस -EINVAL;

	अगर (vgdev->has_virgl_3d)
		virtio_gpu_create_context(dev, file);

	अगर (rc_blob->cmd_size) अणु
		व्योम *buf;

		buf = memdup_user(u64_to_user_ptr(rc_blob->cmd),
				  rc_blob->cmd_size);

		अगर (IS_ERR(buf))
			वापस PTR_ERR(buf);

		virtio_gpu_cmd_submit(vgdev, buf, rc_blob->cmd_size,
				      vfpriv->ctx_id, शून्य, शून्य);
	पूर्ण

	अगर (guest_blob)
		ret = virtio_gpu_object_create(vgdev, &params, &bo, शून्य);
	अन्यथा अगर (!guest_blob && host3d_blob)
		ret = virtio_gpu_vram_create(vgdev, &params, &bo);
	अन्यथा
		वापस -EINVAL;

	अगर (ret < 0)
		वापस ret;

	bo->guest_blob = guest_blob;
	bo->host3d_blob = host3d_blob;
	bo->blob_mem = rc_blob->blob_mem;
	bo->blob_flags = rc_blob->blob_flags;

	obj = &bo->base.base;
	अगर (params.blob_flags & VIRTGPU_BLOB_FLAG_USE_CROSS_DEVICE) अणु
		ret = virtio_gpu_resource_assign_uuid(vgdev, bo);
		अगर (ret) अणु
			drm_gem_object_release(obj);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = drm_gem_handle_create(file, obj, &handle);
	अगर (ret) अणु
		drm_gem_object_release(obj);
		वापस ret;
	पूर्ण
	drm_gem_object_put(obj);

	rc_blob->res_handle = bo->hw_res_handle;
	rc_blob->bo_handle = handle;

	वापस 0;
पूर्ण

काष्ठा drm_ioctl_desc virtio_gpu_ioctls[DRM_VIRTIO_NUM_IOCTLS] = अणु
	DRM_IOCTL_DEF_DRV(VIRTGPU_MAP, virtio_gpu_map_ioctl,
			  DRM_RENDER_ALLOW),

	DRM_IOCTL_DEF_DRV(VIRTGPU_EXECBUFFER, virtio_gpu_execbuffer_ioctl,
			  DRM_RENDER_ALLOW),

	DRM_IOCTL_DEF_DRV(VIRTGPU_GETPARAM, virtio_gpu_getparam_ioctl,
			  DRM_RENDER_ALLOW),

	DRM_IOCTL_DEF_DRV(VIRTGPU_RESOURCE_CREATE,
			  virtio_gpu_resource_create_ioctl,
			  DRM_RENDER_ALLOW),

	DRM_IOCTL_DEF_DRV(VIRTGPU_RESOURCE_INFO, virtio_gpu_resource_info_ioctl,
			  DRM_RENDER_ALLOW),

	/* make transfer async to the मुख्य ring? - no sure, can we
	 * thपढ़ो these in the underlying GL
	 */
	DRM_IOCTL_DEF_DRV(VIRTGPU_TRANSFER_FROM_HOST,
			  virtio_gpu_transfer_from_host_ioctl,
			  DRM_RENDER_ALLOW),
	DRM_IOCTL_DEF_DRV(VIRTGPU_TRANSFER_TO_HOST,
			  virtio_gpu_transfer_to_host_ioctl,
			  DRM_RENDER_ALLOW),

	DRM_IOCTL_DEF_DRV(VIRTGPU_WAIT, virtio_gpu_रुको_ioctl,
			  DRM_RENDER_ALLOW),

	DRM_IOCTL_DEF_DRV(VIRTGPU_GET_CAPS, virtio_gpu_get_caps_ioctl,
			  DRM_RENDER_ALLOW),

	DRM_IOCTL_DEF_DRV(VIRTGPU_RESOURCE_CREATE_BLOB,
			  virtio_gpu_resource_create_blob_ioctl,
			  DRM_RENDER_ALLOW),
पूर्ण;
