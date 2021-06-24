<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/mm.h>
#समावेश <linux/sync_file.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/dma-mapping.h>

#समावेश <drm/drm_file.h>
#समावेश <drm/drm_syncobj.h>
#समावेश <drm/drm_utils.h>

#समावेश <drm/lima_drm.h>

#समावेश "lima_drv.h"
#समावेश "lima_gem.h"
#समावेश "lima_vm.h"

पूर्णांक lima_heap_alloc(काष्ठा lima_bo *bo, काष्ठा lima_vm *vm)
अणु
	काष्ठा page **pages;
	काष्ठा address_space *mapping = bo->base.base.filp->f_mapping;
	काष्ठा device *dev = bo->base.base.dev->dev;
	माप_प्रकार old_size = bo->heap_size;
	माप_प्रकार new_size = bo->heap_size ? bo->heap_size * 2 :
		(lima_heap_init_nr_pages << PAGE_SHIFT);
	काष्ठा sg_table sgt;
	पूर्णांक i, ret;

	अगर (bo->heap_size >= bo->base.base.size)
		वापस -ENOSPC;

	new_size = min(new_size, bo->base.base.size);

	mutex_lock(&bo->base.pages_lock);

	अगर (bo->base.pages) अणु
		pages = bo->base.pages;
	पूर्ण अन्यथा अणु
		pages = kvदो_स्मृति_array(bo->base.base.size >> PAGE_SHIFT,
				       माप(*pages), GFP_KERNEL | __GFP_ZERO);
		अगर (!pages) अणु
			mutex_unlock(&bo->base.pages_lock);
			वापस -ENOMEM;
		पूर्ण

		bo->base.pages = pages;
		bo->base.pages_use_count = 1;

		mapping_set_unevictable(mapping);
	पूर्ण

	क्रम (i = old_size >> PAGE_SHIFT; i < new_size >> PAGE_SHIFT; i++) अणु
		काष्ठा page *page = shmem_पढ़ो_mapping_page(mapping, i);

		अगर (IS_ERR(page)) अणु
			mutex_unlock(&bo->base.pages_lock);
			वापस PTR_ERR(page);
		पूर्ण
		pages[i] = page;
	पूर्ण

	mutex_unlock(&bo->base.pages_lock);

	ret = sg_alloc_table_from_pages(&sgt, pages, i, 0,
					new_size, GFP_KERNEL);
	अगर (ret)
		वापस ret;

	अगर (bo->base.sgt) अणु
		dma_unmap_sgtable(dev, bo->base.sgt, DMA_BIसूचीECTIONAL, 0);
		sg_मुक्त_table(bo->base.sgt);
	पूर्ण अन्यथा अणु
		bo->base.sgt = kदो_स्मृति(माप(*bo->base.sgt), GFP_KERNEL);
		अगर (!bo->base.sgt) अणु
			sg_मुक्त_table(&sgt);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	ret = dma_map_sgtable(dev, &sgt, DMA_BIसूचीECTIONAL, 0);
	अगर (ret) अणु
		sg_मुक्त_table(&sgt);
		kमुक्त(bo->base.sgt);
		bo->base.sgt = शून्य;
		वापस ret;
	पूर्ण

	*bo->base.sgt = sgt;

	अगर (vm) अणु
		ret = lima_vm_map_bo(vm, bo, old_size >> PAGE_SHIFT);
		अगर (ret)
			वापस ret;
	पूर्ण

	bo->heap_size = new_size;
	वापस 0;
पूर्ण

पूर्णांक lima_gem_create_handle(काष्ठा drm_device *dev, काष्ठा drm_file *file,
			   u32 size, u32 flags, u32 *handle)
अणु
	पूर्णांक err;
	gfp_t mask;
	काष्ठा drm_gem_shmem_object *shmem;
	काष्ठा drm_gem_object *obj;
	काष्ठा lima_bo *bo;
	bool is_heap = flags & LIMA_BO_FLAG_HEAP;

	shmem = drm_gem_shmem_create(dev, size);
	अगर (IS_ERR(shmem))
		वापस PTR_ERR(shmem);

	obj = &shmem->base;

	/* Mali Utgard GPU can only support 32bit address space */
	mask = mapping_gfp_mask(obj->filp->f_mapping);
	mask &= ~__GFP_HIGHMEM;
	mask |= __GFP_DMA32;
	mapping_set_gfp_mask(obj->filp->f_mapping, mask);

	अगर (is_heap) अणु
		bo = to_lima_bo(obj);
		err = lima_heap_alloc(bo, शून्य);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		काष्ठा sg_table *sgt = drm_gem_shmem_get_pages_sgt(obj);

		अगर (IS_ERR(sgt)) अणु
			err = PTR_ERR(sgt);
			जाओ out;
		पूर्ण
	पूर्ण

	err = drm_gem_handle_create(file, obj, handle);

out:
	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put(obj);

	वापस err;
पूर्ण

अटल व्योम lima_gem_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा lima_bo *bo = to_lima_bo(obj);

	अगर (!list_empty(&bo->va))
		dev_err(obj->dev->dev, "lima gem free bo still has va\n");

	drm_gem_shmem_मुक्त_object(obj);
पूर्ण

अटल पूर्णांक lima_gem_object_खोलो(काष्ठा drm_gem_object *obj, काष्ठा drm_file *file)
अणु
	काष्ठा lima_bo *bo = to_lima_bo(obj);
	काष्ठा lima_drm_priv *priv = to_lima_drm_priv(file);
	काष्ठा lima_vm *vm = priv->vm;

	वापस lima_vm_bo_add(vm, bo, true);
पूर्ण

अटल व्योम lima_gem_object_बंद(काष्ठा drm_gem_object *obj, काष्ठा drm_file *file)
अणु
	काष्ठा lima_bo *bo = to_lima_bo(obj);
	काष्ठा lima_drm_priv *priv = to_lima_drm_priv(file);
	काष्ठा lima_vm *vm = priv->vm;

	lima_vm_bo_del(vm, bo);
पूर्ण

अटल पूर्णांक lima_gem_pin(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा lima_bo *bo = to_lima_bo(obj);

	अगर (bo->heap_size)
		वापस -EINVAL;

	वापस drm_gem_shmem_pin(obj);
पूर्ण

अटल पूर्णांक lima_gem_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	काष्ठा lima_bo *bo = to_lima_bo(obj);

	अगर (bo->heap_size)
		वापस -EINVAL;

	वापस drm_gem_shmem_vmap(obj, map);
पूर्ण

अटल पूर्णांक lima_gem_mmap(काष्ठा drm_gem_object *obj, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा lima_bo *bo = to_lima_bo(obj);

	अगर (bo->heap_size)
		वापस -EINVAL;

	वापस drm_gem_shmem_mmap(obj, vma);
पूर्ण

अटल स्थिर काष्ठा drm_gem_object_funcs lima_gem_funcs = अणु
	.मुक्त = lima_gem_मुक्त_object,
	.खोलो = lima_gem_object_खोलो,
	.बंद = lima_gem_object_बंद,
	.prपूर्णांक_info = drm_gem_shmem_prपूर्णांक_info,
	.pin = lima_gem_pin,
	.unpin = drm_gem_shmem_unpin,
	.get_sg_table = drm_gem_shmem_get_sg_table,
	.vmap = lima_gem_vmap,
	.vunmap = drm_gem_shmem_vunmap,
	.mmap = lima_gem_mmap,
पूर्ण;

काष्ठा drm_gem_object *lima_gem_create_object(काष्ठा drm_device *dev, माप_प्रकार size)
अणु
	काष्ठा lima_bo *bo;

	bo = kzalloc(माप(*bo), GFP_KERNEL);
	अगर (!bo)
		वापस शून्य;

	mutex_init(&bo->lock);
	INIT_LIST_HEAD(&bo->va);
	bo->base.map_wc = true;
	bo->base.base.funcs = &lima_gem_funcs;

	वापस &bo->base.base;
पूर्ण

पूर्णांक lima_gem_get_info(काष्ठा drm_file *file, u32 handle, u32 *va, u64 *offset)
अणु
	काष्ठा drm_gem_object *obj;
	काष्ठा lima_bo *bo;
	काष्ठा lima_drm_priv *priv = to_lima_drm_priv(file);
	काष्ठा lima_vm *vm = priv->vm;

	obj = drm_gem_object_lookup(file, handle);
	अगर (!obj)
		वापस -ENOENT;

	bo = to_lima_bo(obj);

	*va = lima_vm_get_va(vm, bo);

	*offset = drm_vma_node_offset_addr(&obj->vma_node);

	drm_gem_object_put(obj);
	वापस 0;
पूर्ण

अटल पूर्णांक lima_gem_sync_bo(काष्ठा lima_sched_task *task, काष्ठा lima_bo *bo,
			    bool ग_लिखो, bool explicit)
अणु
	पूर्णांक err = 0;

	अगर (!ग_लिखो) अणु
		err = dma_resv_reserve_shared(lima_bo_resv(bo), 1);
		अगर (err)
			वापस err;
	पूर्ण

	/* explicit sync use user passed dep fence */
	अगर (explicit)
		वापस 0;

	वापस drm_gem_fence_array_add_implicit(&task->deps, &bo->base.base, ग_लिखो);
पूर्ण

अटल पूर्णांक lima_gem_add_deps(काष्ठा drm_file *file, काष्ठा lima_submit *submit)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < ARRAY_SIZE(submit->in_sync); i++) अणु
		काष्ठा dma_fence *fence = शून्य;

		अगर (!submit->in_sync[i])
			जारी;

		err = drm_syncobj_find_fence(file, submit->in_sync[i],
					     0, 0, &fence);
		अगर (err)
			वापस err;

		err = drm_gem_fence_array_add(&submit->task->deps, fence);
		अगर (err) अणु
			dma_fence_put(fence);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक lima_gem_submit(काष्ठा drm_file *file, काष्ठा lima_submit *submit)
अणु
	पूर्णांक i, err = 0;
	काष्ठा ww_acquire_ctx ctx;
	काष्ठा lima_drm_priv *priv = to_lima_drm_priv(file);
	काष्ठा lima_vm *vm = priv->vm;
	काष्ठा drm_syncobj *out_sync = शून्य;
	काष्ठा dma_fence *fence;
	काष्ठा lima_bo **bos = submit->lbos;

	अगर (submit->out_sync) अणु
		out_sync = drm_syncobj_find(file, submit->out_sync);
		अगर (!out_sync)
			वापस -ENOENT;
	पूर्ण

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा drm_gem_object *obj;
		काष्ठा lima_bo *bo;

		obj = drm_gem_object_lookup(file, submit->bos[i].handle);
		अगर (!obj) अणु
			err = -ENOENT;
			जाओ err_out0;
		पूर्ण

		bo = to_lima_bo(obj);

		/* increase refcnt of gpu va map to prevent unmapped when executing,
		 * will be decreased when task करोne
		 */
		err = lima_vm_bo_add(vm, bo, false);
		अगर (err) अणु
			drm_gem_object_put(obj);
			जाओ err_out0;
		पूर्ण

		bos[i] = bo;
	पूर्ण

	err = drm_gem_lock_reservations((काष्ठा drm_gem_object **)bos,
					submit->nr_bos, &ctx);
	अगर (err)
		जाओ err_out0;

	err = lima_sched_task_init(
		submit->task, submit->ctx->context + submit->pipe,
		bos, submit->nr_bos, vm);
	अगर (err)
		जाओ err_out1;

	err = lima_gem_add_deps(file, submit);
	अगर (err)
		जाओ err_out2;

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		err = lima_gem_sync_bo(
			submit->task, bos[i],
			submit->bos[i].flags & LIMA_SUBMIT_BO_WRITE,
			submit->flags & LIMA_SUBMIT_FLAG_EXPLICIT_FENCE);
		अगर (err)
			जाओ err_out2;
	पूर्ण

	fence = lima_sched_context_queue_task(
		submit->ctx->context + submit->pipe, submit->task);

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		अगर (submit->bos[i].flags & LIMA_SUBMIT_BO_WRITE)
			dma_resv_add_excl_fence(lima_bo_resv(bos[i]), fence);
		अन्यथा
			dma_resv_add_shared_fence(lima_bo_resv(bos[i]), fence);
	पूर्ण

	drm_gem_unlock_reservations((काष्ठा drm_gem_object **)bos,
				    submit->nr_bos, &ctx);

	क्रम (i = 0; i < submit->nr_bos; i++)
		drm_gem_object_put(&bos[i]->base.base);

	अगर (out_sync) अणु
		drm_syncobj_replace_fence(out_sync, fence);
		drm_syncobj_put(out_sync);
	पूर्ण

	dma_fence_put(fence);

	वापस 0;

err_out2:
	lima_sched_task_fini(submit->task);
err_out1:
	drm_gem_unlock_reservations((काष्ठा drm_gem_object **)bos,
				    submit->nr_bos, &ctx);
err_out0:
	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		अगर (!bos[i])
			अवरोध;
		lima_vm_bo_del(vm, bos[i]);
		drm_gem_object_put(&bos[i]->base.base);
	पूर्ण
	अगर (out_sync)
		drm_syncobj_put(out_sync);
	वापस err;
पूर्ण

पूर्णांक lima_gem_रुको(काष्ठा drm_file *file, u32 handle, u32 op, s64 समयout_ns)
अणु
	bool ग_लिखो = op & LIMA_GEM_WAIT_WRITE;
	दीर्घ ret, समयout;

	अगर (!op)
		वापस 0;

	समयout = drm_समयout_असल_to_jअगरfies(समयout_ns);

	ret = drm_gem_dma_resv_रुको(file, handle, ग_लिखो, समयout);
	अगर (ret == -ETIME)
		ret = समयout ? -ETIMEDOUT : -EBUSY;

	वापस ret;
पूर्ण
