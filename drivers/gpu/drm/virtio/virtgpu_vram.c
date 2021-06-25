<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "virtgpu_drv.h"

अटल व्योम virtio_gpu_vram_मुक्त(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा virtio_gpu_object *bo = gem_to_virtio_gpu_obj(obj);
	काष्ठा virtio_gpu_device *vgdev = obj->dev->dev_निजी;
	काष्ठा virtio_gpu_object_vram *vram = to_virtio_gpu_vram(bo);
	bool unmap;

	अगर (bo->created) अणु
		spin_lock(&vgdev->host_visible_lock);
		unmap = drm_mm_node_allocated(&vram->vram_node);
		spin_unlock(&vgdev->host_visible_lock);

		अगर (unmap)
			virtio_gpu_cmd_unmap(vgdev, bo);

		virtio_gpu_cmd_unref_resource(vgdev, bo);
		virtio_gpu_notअगरy(vgdev);
		वापस;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा virtio_gpu_vram_vm_ops = अणु
	.खोलो = drm_gem_vm_खोलो,
	.बंद = drm_gem_vm_बंद,
पूर्ण;

अटल पूर्णांक virtio_gpu_vram_mmap(काष्ठा drm_gem_object *obj,
				काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;
	काष्ठा virtio_gpu_device *vgdev = obj->dev->dev_निजी;
	काष्ठा virtio_gpu_object *bo = gem_to_virtio_gpu_obj(obj);
	काष्ठा virtio_gpu_object_vram *vram = to_virtio_gpu_vram(bo);
	अचिन्हित दीर्घ vm_size = vma->vm_end - vma->vm_start;

	अगर (!(bo->blob_flags & VIRTGPU_BLOB_FLAG_USE_MAPPABLE))
		वापस -EINVAL;

	रुको_event(vgdev->resp_wq, vram->map_state != STATE_INITIALIZING);
	अगर (vram->map_state != STATE_OK)
		वापस -EINVAL;

	vma->vm_pgoff -= drm_vma_node_start(&obj->vma_node);
	vma->vm_flags |= VM_MIXEDMAP | VM_DONTEXPAND;
	vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
	vma->vm_page_prot = pgprot_decrypted(vma->vm_page_prot);
	vma->vm_ops = &virtio_gpu_vram_vm_ops;

	अगर (vram->map_info == VIRTIO_GPU_MAP_CACHE_WC)
		vma->vm_page_prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);
	अन्यथा अगर (vram->map_info == VIRTIO_GPU_MAP_CACHE_UNCACHED)
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	/* Partial mappings of GEM buffers करोn't happen much in practice. */
	अगर (vm_size != vram->vram_node.size)
		वापस -EINVAL;

	ret = io_remap_pfn_range(vma, vma->vm_start,
				 vram->vram_node.start >> PAGE_SHIFT,
				 vm_size, vma->vm_page_prot);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_gem_object_funcs virtio_gpu_vram_funcs = अणु
	.खोलो = virtio_gpu_gem_object_खोलो,
	.बंद = virtio_gpu_gem_object_बंद,
	.मुक्त = virtio_gpu_vram_मुक्त,
	.mmap = virtio_gpu_vram_mmap,
	.export = virtgpu_gem_prime_export,
पूर्ण;

bool virtio_gpu_is_vram(काष्ठा virtio_gpu_object *bo)
अणु
	वापस bo->base.base.funcs == &virtio_gpu_vram_funcs;
पूर्ण

अटल पूर्णांक virtio_gpu_vram_map(काष्ठा virtio_gpu_object *bo)
अणु
	पूर्णांक ret;
	uपूर्णांक64_t offset;
	काष्ठा virtio_gpu_object_array *objs;
	काष्ठा virtio_gpu_device *vgdev = bo->base.base.dev->dev_निजी;
	काष्ठा virtio_gpu_object_vram *vram = to_virtio_gpu_vram(bo);

	अगर (!vgdev->has_host_visible)
		वापस -EINVAL;

	spin_lock(&vgdev->host_visible_lock);
	ret = drm_mm_insert_node(&vgdev->host_visible_mm, &vram->vram_node,
				 bo->base.base.size);
	spin_unlock(&vgdev->host_visible_lock);

	अगर (ret)
		वापस ret;

	objs = virtio_gpu_array_alloc(1);
	अगर (!objs) अणु
		ret = -ENOMEM;
		जाओ err_हटाओ_node;
	पूर्ण

	virtio_gpu_array_add_obj(objs, &bo->base.base);
	/*TODO: Add an error checking helper function in drm_mm.h */
	offset = vram->vram_node.start - vgdev->host_visible_region.addr;

	ret = virtio_gpu_cmd_map(vgdev, objs, offset);
	अगर (ret) अणु
		virtio_gpu_array_put_मुक्त(objs);
		जाओ err_हटाओ_node;
	पूर्ण

	वापस 0;

err_हटाओ_node:
	spin_lock(&vgdev->host_visible_lock);
	drm_mm_हटाओ_node(&vram->vram_node);
	spin_unlock(&vgdev->host_visible_lock);
	वापस ret;
पूर्ण

पूर्णांक virtio_gpu_vram_create(काष्ठा virtio_gpu_device *vgdev,
			   काष्ठा virtio_gpu_object_params *params,
			   काष्ठा virtio_gpu_object **bo_ptr)
अणु
	काष्ठा drm_gem_object *obj;
	काष्ठा virtio_gpu_object_vram *vram;
	पूर्णांक ret;

	vram = kzalloc(माप(*vram), GFP_KERNEL);
	अगर (!vram)
		वापस -ENOMEM;

	obj = &vram->base.base.base;
	obj->funcs = &virtio_gpu_vram_funcs;

	params->size = PAGE_ALIGN(params->size);
	drm_gem_निजी_object_init(vgdev->ddev, obj, params->size);

	/* Create fake offset */
	ret = drm_gem_create_mmap_offset(obj);
	अगर (ret) अणु
		kमुक्त(vram);
		वापस ret;
	पूर्ण

	ret = virtio_gpu_resource_id_get(vgdev, &vram->base.hw_res_handle);
	अगर (ret) अणु
		kमुक्त(vram);
		वापस ret;
	पूर्ण

	virtio_gpu_cmd_resource_create_blob(vgdev, &vram->base, params, शून्य,
					    0);
	अगर (params->blob_flags & VIRTGPU_BLOB_FLAG_USE_MAPPABLE) अणु
		ret = virtio_gpu_vram_map(&vram->base);
		अगर (ret) अणु
			virtio_gpu_vram_मुक्त(obj);
			वापस ret;
		पूर्ण
	पूर्ण

	*bo_ptr = &vram->base;
	वापस 0;
पूर्ण
