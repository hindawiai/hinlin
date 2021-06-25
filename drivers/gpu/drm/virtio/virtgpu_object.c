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

#समावेश <linux/dma-mapping.h>
#समावेश <linux/moduleparam.h>

#समावेश "virtgpu_drv.h"

अटल पूर्णांक virtio_gpu_virglrenderer_workaround = 1;
module_param_named(virglhack, virtio_gpu_virglrenderer_workaround, पूर्णांक, 0400);

पूर्णांक virtio_gpu_resource_id_get(काष्ठा virtio_gpu_device *vgdev, uपूर्णांक32_t *resid)
अणु
	अगर (virtio_gpu_virglrenderer_workaround) अणु
		/*
		 * Hack to aव्योम re-using resource IDs.
		 *
		 * virglrenderer versions up to (and including) 0.7.0
		 * can't deal with that.  virglrenderer commit
		 * "f91a9dd35715 Fix unlinking resources from hash
		 * table." (Feb 2019) fixes the bug.
		 */
		अटल atomic_t seqno = ATOMIC_INIT(0);
		पूर्णांक handle = atomic_inc_वापस(&seqno);
		*resid = handle + 1;
	पूर्ण अन्यथा अणु
		पूर्णांक handle = ida_alloc(&vgdev->resource_ida, GFP_KERNEL);
		अगर (handle < 0)
			वापस handle;
		*resid = handle + 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम virtio_gpu_resource_id_put(काष्ठा virtio_gpu_device *vgdev, uपूर्णांक32_t id)
अणु
	अगर (!virtio_gpu_virglrenderer_workaround) अणु
		ida_मुक्त(&vgdev->resource_ida, id - 1);
	पूर्ण
पूर्ण

व्योम virtio_gpu_cleanup_object(काष्ठा virtio_gpu_object *bo)
अणु
	काष्ठा virtio_gpu_device *vgdev = bo->base.base.dev->dev_निजी;

	virtio_gpu_resource_id_put(vgdev, bo->hw_res_handle);
	अगर (virtio_gpu_is_shmem(bo)) अणु
		काष्ठा virtio_gpu_object_shmem *shmem = to_virtio_gpu_shmem(bo);

		अगर (shmem->pages) अणु
			अगर (shmem->mapped) अणु
				dma_unmap_sgtable(vgdev->vdev->dev.parent,
					     shmem->pages, DMA_TO_DEVICE, 0);
				shmem->mapped = 0;
			पूर्ण

			sg_मुक्त_table(shmem->pages);
			kमुक्त(shmem->pages);
			shmem->pages = शून्य;
			drm_gem_shmem_unpin(&bo->base.base);
		पूर्ण

		drm_gem_shmem_मुक्त_object(&bo->base.base);
	पूर्ण अन्यथा अगर (virtio_gpu_is_vram(bo)) अणु
		काष्ठा virtio_gpu_object_vram *vram = to_virtio_gpu_vram(bo);

		spin_lock(&vgdev->host_visible_lock);
		अगर (drm_mm_node_allocated(&vram->vram_node))
			drm_mm_हटाओ_node(&vram->vram_node);

		spin_unlock(&vgdev->host_visible_lock);

		drm_gem_मुक्त_mmap_offset(&vram->base.base.base);
		drm_gem_object_release(&vram->base.base.base);
		kमुक्त(vram);
	पूर्ण
पूर्ण

अटल व्योम virtio_gpu_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा virtio_gpu_object *bo = gem_to_virtio_gpu_obj(obj);
	काष्ठा virtio_gpu_device *vgdev = bo->base.base.dev->dev_निजी;

	अगर (bo->created) अणु
		virtio_gpu_cmd_unref_resource(vgdev, bo);
		virtio_gpu_notअगरy(vgdev);
		/* completion handler calls virtio_gpu_cleanup_object() */
		वापस;
	पूर्ण
	virtio_gpu_cleanup_object(bo);
पूर्ण

अटल स्थिर काष्ठा drm_gem_object_funcs virtio_gpu_shmem_funcs = अणु
	.मुक्त = virtio_gpu_मुक्त_object,
	.खोलो = virtio_gpu_gem_object_खोलो,
	.बंद = virtio_gpu_gem_object_बंद,

	.prपूर्णांक_info = drm_gem_shmem_prपूर्णांक_info,
	.export = virtgpu_gem_prime_export,
	.pin = drm_gem_shmem_pin,
	.unpin = drm_gem_shmem_unpin,
	.get_sg_table = drm_gem_shmem_get_sg_table,
	.vmap = drm_gem_shmem_vmap,
	.vunmap = drm_gem_shmem_vunmap,
	.mmap = drm_gem_shmem_mmap,
पूर्ण;

bool virtio_gpu_is_shmem(काष्ठा virtio_gpu_object *bo)
अणु
	वापस bo->base.base.funcs == &virtio_gpu_shmem_funcs;
पूर्ण

काष्ठा drm_gem_object *virtio_gpu_create_object(काष्ठा drm_device *dev,
						माप_प्रकार size)
अणु
	काष्ठा virtio_gpu_object_shmem *shmem;
	काष्ठा drm_gem_shmem_object *dshmem;

	shmem = kzalloc(माप(*shmem), GFP_KERNEL);
	अगर (!shmem)
		वापस शून्य;

	dshmem = &shmem->base.base;
	dshmem->base.funcs = &virtio_gpu_shmem_funcs;
	वापस &dshmem->base;
पूर्ण

अटल पूर्णांक virtio_gpu_object_shmem_init(काष्ठा virtio_gpu_device *vgdev,
					काष्ठा virtio_gpu_object *bo,
					काष्ठा virtio_gpu_mem_entry **ents,
					अचिन्हित पूर्णांक *nents)
अणु
	bool use_dma_api = !virtio_has_dma_quirk(vgdev->vdev);
	काष्ठा virtio_gpu_object_shmem *shmem = to_virtio_gpu_shmem(bo);
	काष्ठा scatterlist *sg;
	पूर्णांक si, ret;

	ret = drm_gem_shmem_pin(&bo->base.base);
	अगर (ret < 0)
		वापस -EINVAL;

	/*
	 * virtio_gpu uses drm_gem_shmem_get_sg_table instead of
	 * drm_gem_shmem_get_pages_sgt because virtio has it's own set of
	 * dma-ops. This is discouraged क्रम other drivers, but should be fine
	 * since virtio_gpu करोesn't support dma-buf import from other devices.
	 */
	shmem->pages = drm_gem_shmem_get_sg_table(&bo->base.base);
	अगर (!shmem->pages) अणु
		drm_gem_shmem_unpin(&bo->base.base);
		वापस -EINVAL;
	पूर्ण

	अगर (use_dma_api) अणु
		ret = dma_map_sgtable(vgdev->vdev->dev.parent,
				      shmem->pages, DMA_TO_DEVICE, 0);
		अगर (ret)
			वापस ret;
		*nents = shmem->mapped = shmem->pages->nents;
	पूर्ण अन्यथा अणु
		*nents = shmem->pages->orig_nents;
	पूर्ण

	*ents = kvदो_स्मृति_array(*nents,
			       माप(काष्ठा virtio_gpu_mem_entry),
			       GFP_KERNEL);
	अगर (!(*ents)) अणु
		DRM_ERROR("failed to allocate ent list\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (use_dma_api) अणु
		क्रम_each_sgtable_dma_sg(shmem->pages, sg, si) अणु
			(*ents)[si].addr = cpu_to_le64(sg_dma_address(sg));
			(*ents)[si].length = cpu_to_le32(sg_dma_len(sg));
			(*ents)[si].padding = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_sgtable_sg(shmem->pages, sg, si) अणु
			(*ents)[si].addr = cpu_to_le64(sg_phys(sg));
			(*ents)[si].length = cpu_to_le32(sg->length);
			(*ents)[si].padding = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक virtio_gpu_object_create(काष्ठा virtio_gpu_device *vgdev,
			     काष्ठा virtio_gpu_object_params *params,
			     काष्ठा virtio_gpu_object **bo_ptr,
			     काष्ठा virtio_gpu_fence *fence)
अणु
	काष्ठा virtio_gpu_object_array *objs = शून्य;
	काष्ठा drm_gem_shmem_object *shmem_obj;
	काष्ठा virtio_gpu_object *bo;
	काष्ठा virtio_gpu_mem_entry *ents;
	अचिन्हित पूर्णांक nents;
	पूर्णांक ret;

	*bo_ptr = शून्य;

	params->size = roundup(params->size, PAGE_SIZE);
	shmem_obj = drm_gem_shmem_create(vgdev->ddev, params->size);
	अगर (IS_ERR(shmem_obj))
		वापस PTR_ERR(shmem_obj);
	bo = gem_to_virtio_gpu_obj(&shmem_obj->base);

	ret = virtio_gpu_resource_id_get(vgdev, &bo->hw_res_handle);
	अगर (ret < 0)
		जाओ err_मुक्त_gem;

	bo->dumb = params->dumb;

	अगर (fence) अणु
		ret = -ENOMEM;
		objs = virtio_gpu_array_alloc(1);
		अगर (!objs)
			जाओ err_put_id;
		virtio_gpu_array_add_obj(objs, &bo->base.base);

		ret = virtio_gpu_array_lock_resv(objs);
		अगर (ret != 0)
			जाओ err_put_objs;
	पूर्ण

	ret = virtio_gpu_object_shmem_init(vgdev, bo, &ents, &nents);
	अगर (ret != 0) अणु
		virtio_gpu_array_put_मुक्त(objs);
		virtio_gpu_मुक्त_object(&shmem_obj->base);
		वापस ret;
	पूर्ण

	अगर (params->blob) अणु
		virtio_gpu_cmd_resource_create_blob(vgdev, bo, params,
						    ents, nents);
	पूर्ण अन्यथा अगर (params->virgl) अणु
		virtio_gpu_cmd_resource_create_3d(vgdev, bo, params,
						  objs, fence);
		virtio_gpu_object_attach(vgdev, bo, ents, nents);
	पूर्ण अन्यथा अणु
		virtio_gpu_cmd_create_resource(vgdev, bo, params,
					       objs, fence);
		virtio_gpu_object_attach(vgdev, bo, ents, nents);
	पूर्ण

	*bo_ptr = bo;
	वापस 0;

err_put_objs:
	virtio_gpu_array_put_मुक्त(objs);
err_put_id:
	virtio_gpu_resource_id_put(vgdev, bo->hw_res_handle);
err_मुक्त_gem:
	drm_gem_shmem_मुक्त_object(&shmem_obj->base);
	वापस ret;
पूर्ण
