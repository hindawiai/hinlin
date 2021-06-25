<शैली गुरु>
/*
 * Copyright (C) 2015 Red Hat, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <drm/drm_file.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "virtgpu_drv.h"

अटल पूर्णांक virtio_gpu_gem_create(काष्ठा drm_file *file,
				 काष्ठा drm_device *dev,
				 काष्ठा virtio_gpu_object_params *params,
				 काष्ठा drm_gem_object **obj_p,
				 uपूर्णांक32_t *handle_p)
अणु
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_object *obj;
	पूर्णांक ret;
	u32 handle;

	ret = virtio_gpu_object_create(vgdev, params, &obj, शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = drm_gem_handle_create(file, &obj->base.base, &handle);
	अगर (ret) अणु
		drm_gem_object_release(&obj->base.base);
		वापस ret;
	पूर्ण

	*obj_p = &obj->base.base;

	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put(&obj->base.base);

	*handle_p = handle;
	वापस 0;
पूर्ण

पूर्णांक virtio_gpu_mode_dumb_create(काष्ठा drm_file *file_priv,
				काष्ठा drm_device *dev,
				काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा drm_gem_object *gobj;
	काष्ठा virtio_gpu_object_params params = अणु 0 पूर्ण;
	पूर्णांक ret;
	uपूर्णांक32_t pitch;

	अगर (args->bpp != 32)
		वापस -EINVAL;

	pitch = args->width * 4;
	args->size = pitch * args->height;
	args->size = ALIGN(args->size, PAGE_SIZE);

	params.क्रमmat = virtio_gpu_translate_क्रमmat(DRM_FORMAT_HOST_XRGB8888);
	params.width = args->width;
	params.height = args->height;
	params.size = args->size;
	params.dumb = true;
	ret = virtio_gpu_gem_create(file_priv, dev, &params, &gobj,
				    &args->handle);
	अगर (ret)
		जाओ fail;

	args->pitch = pitch;
	वापस ret;

fail:
	वापस ret;
पूर्ण

पूर्णांक virtio_gpu_mode_dumb_mmap(काष्ठा drm_file *file_priv,
			      काष्ठा drm_device *dev,
			      uपूर्णांक32_t handle, uपूर्णांक64_t *offset_p)
अणु
	काष्ठा drm_gem_object *gobj;

	BUG_ON(!offset_p);
	gobj = drm_gem_object_lookup(file_priv, handle);
	अगर (gobj == शून्य)
		वापस -ENOENT;
	*offset_p = drm_vma_node_offset_addr(&gobj->vma_node);
	drm_gem_object_put(gobj);
	वापस 0;
पूर्ण

पूर्णांक virtio_gpu_gem_object_खोलो(काष्ठा drm_gem_object *obj,
			       काष्ठा drm_file *file)
अणु
	काष्ठा virtio_gpu_device *vgdev = obj->dev->dev_निजी;
	काष्ठा virtio_gpu_fpriv *vfpriv = file->driver_priv;
	काष्ठा virtio_gpu_object_array *objs;

	अगर (!vgdev->has_virgl_3d)
		जाओ out_notअगरy;

	/* the context might still be missing when the first ioctl is
	 * DRM_IOCTL_MODE_CREATE_DUMB or DRM_IOCTL_PRIME_FD_TO_HANDLE
	 */
	virtio_gpu_create_context(obj->dev, file);

	objs = virtio_gpu_array_alloc(1);
	अगर (!objs)
		वापस -ENOMEM;
	virtio_gpu_array_add_obj(objs, obj);

	virtio_gpu_cmd_context_attach_resource(vgdev, vfpriv->ctx_id,
					       objs);
out_notअगरy:
	virtio_gpu_notअगरy(vgdev);
	वापस 0;
पूर्ण

व्योम virtio_gpu_gem_object_बंद(काष्ठा drm_gem_object *obj,
				 काष्ठा drm_file *file)
अणु
	काष्ठा virtio_gpu_device *vgdev = obj->dev->dev_निजी;
	काष्ठा virtio_gpu_fpriv *vfpriv = file->driver_priv;
	काष्ठा virtio_gpu_object_array *objs;

	अगर (!vgdev->has_virgl_3d)
		वापस;

	objs = virtio_gpu_array_alloc(1);
	अगर (!objs)
		वापस;
	virtio_gpu_array_add_obj(objs, obj);

	virtio_gpu_cmd_context_detach_resource(vgdev, vfpriv->ctx_id,
					       objs);
	virtio_gpu_notअगरy(vgdev);
पूर्ण

काष्ठा virtio_gpu_object_array *virtio_gpu_array_alloc(u32 nents)
अणु
	काष्ठा virtio_gpu_object_array *objs;

	objs = kदो_स्मृति(काष्ठा_size(objs, objs, nents), GFP_KERNEL);
	अगर (!objs)
		वापस शून्य;

	objs->nents = 0;
	objs->total = nents;
	वापस objs;
पूर्ण

अटल व्योम virtio_gpu_array_मुक्त(काष्ठा virtio_gpu_object_array *objs)
अणु
	kमुक्त(objs);
पूर्ण

काष्ठा virtio_gpu_object_array*
virtio_gpu_array_from_handles(काष्ठा drm_file *drm_file, u32 *handles, u32 nents)
अणु
	काष्ठा virtio_gpu_object_array *objs;
	u32 i;

	objs = virtio_gpu_array_alloc(nents);
	अगर (!objs)
		वापस शून्य;

	क्रम (i = 0; i < nents; i++) अणु
		objs->objs[i] = drm_gem_object_lookup(drm_file, handles[i]);
		अगर (!objs->objs[i]) अणु
			objs->nents = i;
			virtio_gpu_array_put_मुक्त(objs);
			वापस शून्य;
		पूर्ण
	पूर्ण
	objs->nents = i;
	वापस objs;
पूर्ण

व्योम virtio_gpu_array_add_obj(काष्ठा virtio_gpu_object_array *objs,
			      काष्ठा drm_gem_object *obj)
अणु
	अगर (WARN_ON_ONCE(objs->nents == objs->total))
		वापस;

	drm_gem_object_get(obj);
	objs->objs[objs->nents] = obj;
	objs->nents++;
पूर्ण

पूर्णांक virtio_gpu_array_lock_resv(काष्ठा virtio_gpu_object_array *objs)
अणु
	पूर्णांक ret;

	अगर (objs->nents == 1) अणु
		ret = dma_resv_lock_पूर्णांकerruptible(objs->objs[0]->resv, शून्य);
	पूर्ण अन्यथा अणु
		ret = drm_gem_lock_reservations(objs->objs, objs->nents,
						&objs->ticket);
	पूर्ण
	वापस ret;
पूर्ण

व्योम virtio_gpu_array_unlock_resv(काष्ठा virtio_gpu_object_array *objs)
अणु
	अगर (objs->nents == 1) अणु
		dma_resv_unlock(objs->objs[0]->resv);
	पूर्ण अन्यथा अणु
		drm_gem_unlock_reservations(objs->objs, objs->nents,
					    &objs->ticket);
	पूर्ण
पूर्ण

व्योम virtio_gpu_array_add_fence(काष्ठा virtio_gpu_object_array *objs,
				काष्ठा dma_fence *fence)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < objs->nents; i++)
		dma_resv_add_excl_fence(objs->objs[i]->resv, fence);
पूर्ण

व्योम virtio_gpu_array_put_मुक्त(काष्ठा virtio_gpu_object_array *objs)
अणु
	u32 i;

	क्रम (i = 0; i < objs->nents; i++)
		drm_gem_object_put(objs->objs[i]);
	virtio_gpu_array_मुक्त(objs);
पूर्ण

व्योम virtio_gpu_array_put_मुक्त_delayed(काष्ठा virtio_gpu_device *vgdev,
				       काष्ठा virtio_gpu_object_array *objs)
अणु
	spin_lock(&vgdev->obj_मुक्त_lock);
	list_add_tail(&objs->next, &vgdev->obj_मुक्त_list);
	spin_unlock(&vgdev->obj_मुक्त_lock);
	schedule_work(&vgdev->obj_मुक्त_work);
पूर्ण

व्योम virtio_gpu_array_put_मुक्त_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_gpu_device *vgdev =
		container_of(work, काष्ठा virtio_gpu_device, obj_मुक्त_work);
	काष्ठा virtio_gpu_object_array *objs;

	spin_lock(&vgdev->obj_मुक्त_lock);
	जबतक (!list_empty(&vgdev->obj_मुक्त_list)) अणु
		objs = list_first_entry(&vgdev->obj_मुक्त_list,
					काष्ठा virtio_gpu_object_array, next);
		list_del(&objs->next);
		spin_unlock(&vgdev->obj_मुक्त_lock);
		virtio_gpu_array_put_मुक्त(objs);
		spin_lock(&vgdev->obj_मुक्त_lock);
	पूर्ण
	spin_unlock(&vgdev->obj_मुक्त_lock);
पूर्ण
