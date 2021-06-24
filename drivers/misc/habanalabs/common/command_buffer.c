<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश <uapi/misc/habanaद_असल.h>
#समावेश "habanalabs.h"

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

अटल पूर्णांक cb_map_mem(काष्ठा hl_ctx *ctx, काष्ठा hl_cb *cb)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_vm_va_block *va_block, *पंचांगp;
	dma_addr_t bus_addr;
	u64 virt_addr;
	u32 page_size = prop->pmmu.page_size;
	s32 offset;
	पूर्णांक rc;

	अगर (!hdev->supports_cb_mapping) अणु
		dev_err_ratelimited(hdev->dev,
				"Cannot map CB because no VA range is allocated for CB mapping\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!hdev->mmu_enable) अणु
		dev_err_ratelimited(hdev->dev,
				"Cannot map CB because MMU is disabled\n");
		वापस -EINVAL;
	पूर्ण

	INIT_LIST_HEAD(&cb->va_block_list);

	क्रम (bus_addr = cb->bus_address;
			bus_addr < cb->bus_address + cb->size;
			bus_addr += page_size) अणु

		virt_addr = (u64) gen_pool_alloc(ctx->cb_va_pool, page_size);
		अगर (!virt_addr) अणु
			dev_err(hdev->dev,
				"Failed to allocate device virtual address for CB\n");
			rc = -ENOMEM;
			जाओ err_va_pool_मुक्त;
		पूर्ण

		va_block = kzalloc(माप(*va_block), GFP_KERNEL);
		अगर (!va_block) अणु
			rc = -ENOMEM;
			gen_pool_मुक्त(ctx->cb_va_pool, virt_addr, page_size);
			जाओ err_va_pool_मुक्त;
		पूर्ण

		va_block->start = virt_addr;
		va_block->end = virt_addr + page_size;
		va_block->size = page_size;
		list_add_tail(&va_block->node, &cb->va_block_list);
	पूर्ण

	mutex_lock(&ctx->mmu_lock);

	bus_addr = cb->bus_address;
	offset = 0;
	list_क्रम_each_entry(va_block, &cb->va_block_list, node) अणु
		rc = hl_mmu_map_page(ctx, va_block->start, bus_addr,
				va_block->size, list_is_last(&va_block->node,
							&cb->va_block_list));
		अगर (rc) अणु
			dev_err(hdev->dev, "Failed to map VA %#llx to CB\n",
				va_block->start);
			जाओ err_va_umap;
		पूर्ण

		bus_addr += va_block->size;
		offset += va_block->size;
	पूर्ण

	hdev->asic_funcs->mmu_invalidate_cache(hdev, false, VM_TYPE_USERPTR);

	mutex_unlock(&ctx->mmu_lock);

	cb->is_mmu_mapped = true;

	वापस 0;

err_va_umap:
	list_क्रम_each_entry(va_block, &cb->va_block_list, node) अणु
		अगर (offset <= 0)
			अवरोध;
		hl_mmu_unmap_page(ctx, va_block->start, va_block->size,
				offset <= va_block->size);
		offset -= va_block->size;
	पूर्ण

	hdev->asic_funcs->mmu_invalidate_cache(hdev, true, VM_TYPE_USERPTR);

	mutex_unlock(&ctx->mmu_lock);

err_va_pool_मुक्त:
	list_क्रम_each_entry_safe(va_block, पंचांगp, &cb->va_block_list, node) अणु
		gen_pool_मुक्त(ctx->cb_va_pool, va_block->start, va_block->size);
		list_del(&va_block->node);
		kमुक्त(va_block);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम cb_unmap_mem(काष्ठा hl_ctx *ctx, काष्ठा hl_cb *cb)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा hl_vm_va_block *va_block, *पंचांगp;

	mutex_lock(&ctx->mmu_lock);

	list_क्रम_each_entry(va_block, &cb->va_block_list, node)
		अगर (hl_mmu_unmap_page(ctx, va_block->start, va_block->size,
				list_is_last(&va_block->node,
						&cb->va_block_list)))
			dev_warn_ratelimited(hdev->dev,
					"Failed to unmap CB's va 0x%llx\n",
					va_block->start);

	hdev->asic_funcs->mmu_invalidate_cache(hdev, true, VM_TYPE_USERPTR);

	mutex_unlock(&ctx->mmu_lock);

	list_क्रम_each_entry_safe(va_block, पंचांगp, &cb->va_block_list, node) अणु
		gen_pool_मुक्त(ctx->cb_va_pool, va_block->start, va_block->size);
		list_del(&va_block->node);
		kमुक्त(va_block);
	पूर्ण
पूर्ण

अटल व्योम cb_fini(काष्ठा hl_device *hdev, काष्ठा hl_cb *cb)
अणु
	अगर (cb->is_पूर्णांकernal)
		gen_pool_मुक्त(hdev->पूर्णांकernal_cb_pool,
				(uपूर्णांकptr_t)cb->kernel_address, cb->size);
	अन्यथा
		hdev->asic_funcs->asic_dma_मुक्त_coherent(hdev, cb->size,
				cb->kernel_address, cb->bus_address);

	kमुक्त(cb);
पूर्ण

अटल व्योम cb_करो_release(काष्ठा hl_device *hdev, काष्ठा hl_cb *cb)
अणु
	अगर (cb->is_pool) अणु
		spin_lock(&hdev->cb_pool_lock);
		list_add(&cb->pool_list, &hdev->cb_pool);
		spin_unlock(&hdev->cb_pool_lock);
	पूर्ण अन्यथा अणु
		cb_fini(hdev, cb);
	पूर्ण
पूर्ण

अटल व्योम cb_release(काष्ठा kref *ref)
अणु
	काष्ठा hl_device *hdev;
	काष्ठा hl_cb *cb;

	cb = container_of(ref, काष्ठा hl_cb, refcount);
	hdev = cb->hdev;

	hl_debugfs_हटाओ_cb(cb);

	अगर (cb->is_mmu_mapped)
		cb_unmap_mem(cb->ctx, cb);

	hl_ctx_put(cb->ctx);

	cb_करो_release(hdev, cb);
पूर्ण

अटल काष्ठा hl_cb *hl_cb_alloc(काष्ठा hl_device *hdev, u32 cb_size,
					पूर्णांक ctx_id, bool पूर्णांकernal_cb)
अणु
	काष्ठा hl_cb *cb = शून्य;
	u32 cb_offset;
	व्योम *p;

	/*
	 * We use of GFP_ATOMIC here because this function can be called from
	 * the latency-sensitive code path क्रम command submission. Due to H/W
	 * limitations in some of the ASICs, the kernel must copy the user CB
	 * that is designated क्रम an बाह्यal queue and actually enqueue
	 * the kernel's copy. Hence, we must never sleep in this code section
	 * and must use GFP_ATOMIC क्रम all memory allocations.
	 */
	अगर (ctx_id == HL_KERNEL_ASID_ID && !hdev->disabled)
		cb = kzalloc(माप(*cb), GFP_ATOMIC);

	अगर (!cb)
		cb = kzalloc(माप(*cb), GFP_KERNEL);

	अगर (!cb)
		वापस शून्य;

	अगर (पूर्णांकernal_cb) अणु
		p = (व्योम *) gen_pool_alloc(hdev->पूर्णांकernal_cb_pool, cb_size);
		अगर (!p) अणु
			kमुक्त(cb);
			वापस शून्य;
		पूर्ण

		cb_offset = p - hdev->पूर्णांकernal_cb_pool_virt_addr;
		cb->is_पूर्णांकernal = true;
		cb->bus_address =  hdev->पूर्णांकernal_cb_va_base + cb_offset;
	पूर्ण अन्यथा अगर (ctx_id == HL_KERNEL_ASID_ID) अणु
		p = hdev->asic_funcs->asic_dma_alloc_coherent(hdev, cb_size,
						&cb->bus_address, GFP_ATOMIC);
		अगर (!p)
			p = hdev->asic_funcs->asic_dma_alloc_coherent(hdev,
					cb_size, &cb->bus_address, GFP_KERNEL);
	पूर्ण अन्यथा अणु
		p = hdev->asic_funcs->asic_dma_alloc_coherent(hdev, cb_size,
						&cb->bus_address,
						GFP_USER | __GFP_ZERO);
	पूर्ण

	अगर (!p) अणु
		dev_err(hdev->dev,
			"failed to allocate %d of dma memory for CB\n",
			cb_size);
		kमुक्त(cb);
		वापस शून्य;
	पूर्ण

	cb->kernel_address = p;
	cb->size = cb_size;

	वापस cb;
पूर्ण

पूर्णांक hl_cb_create(काष्ठा hl_device *hdev, काष्ठा hl_cb_mgr *mgr,
			काष्ठा hl_ctx *ctx, u32 cb_size, bool पूर्णांकernal_cb,
			bool map_cb, u64 *handle)
अणु
	काष्ठा hl_cb *cb;
	bool alloc_new_cb = true;
	पूर्णांक rc, ctx_id = ctx->asid;

	/*
	 * Can't use generic function to check this because of special हाल
	 * where we create a CB as part of the reset process
	 */
	अगर ((hdev->disabled) || ((atomic_पढ़ो(&hdev->in_reset)) &&
					(ctx_id != HL_KERNEL_ASID_ID))) अणु
		dev_warn_ratelimited(hdev->dev,
			"Device is disabled or in reset. Can't create new CBs\n");
		rc = -EBUSY;
		जाओ out_err;
	पूर्ण

	अगर (cb_size > SZ_2M) अणु
		dev_err(hdev->dev, "CB size %d must be less than %d\n",
			cb_size, SZ_2M);
		rc = -EINVAL;
		जाओ out_err;
	पूर्ण

	अगर (!पूर्णांकernal_cb) अणु
		/* Minimum allocation must be PAGE SIZE */
		अगर (cb_size < PAGE_SIZE)
			cb_size = PAGE_SIZE;

		अगर (ctx_id == HL_KERNEL_ASID_ID &&
				cb_size <= hdev->asic_prop.cb_pool_cb_size) अणु

			spin_lock(&hdev->cb_pool_lock);
			अगर (!list_empty(&hdev->cb_pool)) अणु
				cb = list_first_entry(&hdev->cb_pool,
						typeof(*cb), pool_list);
				list_del(&cb->pool_list);
				spin_unlock(&hdev->cb_pool_lock);
				alloc_new_cb = false;
			पूर्ण अन्यथा अणु
				spin_unlock(&hdev->cb_pool_lock);
				dev_dbg(hdev->dev, "CB pool is empty\n");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (alloc_new_cb) अणु
		cb = hl_cb_alloc(hdev, cb_size, ctx_id, पूर्णांकernal_cb);
		अगर (!cb) अणु
			rc = -ENOMEM;
			जाओ out_err;
		पूर्ण
	पूर्ण

	cb->hdev = hdev;
	cb->ctx = ctx;
	hl_ctx_get(hdev, cb->ctx);

	अगर (map_cb) अणु
		अगर (ctx_id == HL_KERNEL_ASID_ID) अणु
			dev_err(hdev->dev,
				"CB mapping is not supported for kernel context\n");
			rc = -EINVAL;
			जाओ release_cb;
		पूर्ण

		rc = cb_map_mem(ctx, cb);
		अगर (rc)
			जाओ release_cb;
	पूर्ण

	spin_lock(&mgr->cb_lock);
	rc = idr_alloc(&mgr->cb_handles, cb, 1, 0, GFP_ATOMIC);
	अगर (rc < 0)
		rc = idr_alloc(&mgr->cb_handles, cb, 1, 0, GFP_KERNEL);
	spin_unlock(&mgr->cb_lock);

	अगर (rc < 0) अणु
		dev_err(hdev->dev, "Failed to allocate IDR for a new CB\n");
		जाओ unmap_mem;
	पूर्ण

	cb->id = (u64) rc;

	kref_init(&cb->refcount);
	spin_lock_init(&cb->lock);

	/*
	 * idr is 32-bit so we can safely OR it with a mask that is above
	 * 32 bit
	 */
	*handle = cb->id | HL_MMAP_TYPE_CB;
	*handle <<= PAGE_SHIFT;

	hl_debugfs_add_cb(cb);

	वापस 0;

unmap_mem:
	अगर (cb->is_mmu_mapped)
		cb_unmap_mem(cb->ctx, cb);
release_cb:
	hl_ctx_put(cb->ctx);
	cb_करो_release(hdev, cb);
out_err:
	*handle = 0;

	वापस rc;
पूर्ण

पूर्णांक hl_cb_destroy(काष्ठा hl_device *hdev, काष्ठा hl_cb_mgr *mgr, u64 cb_handle)
अणु
	काष्ठा hl_cb *cb;
	u32 handle;
	पूर्णांक rc = 0;

	/*
	 * handle was given to user to करो mmap, I need to shअगरt it back to
	 * how the idr module gave it to me
	 */
	cb_handle >>= PAGE_SHIFT;
	handle = (u32) cb_handle;

	spin_lock(&mgr->cb_lock);

	cb = idr_find(&mgr->cb_handles, handle);
	अगर (cb) अणु
		idr_हटाओ(&mgr->cb_handles, handle);
		spin_unlock(&mgr->cb_lock);
		kref_put(&cb->refcount, cb_release);
	पूर्ण अन्यथा अणु
		spin_unlock(&mgr->cb_lock);
		dev_err(hdev->dev,
			"CB destroy failed, no match to handle 0x%x\n", handle);
		rc = -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक hl_cb_info(काष्ठा hl_device *hdev, काष्ठा hl_cb_mgr *mgr,
			u64 cb_handle, u32 *usage_cnt)
अणु
	काष्ठा hl_cb *cb;
	u32 handle;
	पूर्णांक rc = 0;

	/* The CB handle was given to user to करो mmap, so need to shअगरt it back
	 * to the value which was allocated by the IDR module.
	 */
	cb_handle >>= PAGE_SHIFT;
	handle = (u32) cb_handle;

	spin_lock(&mgr->cb_lock);

	cb = idr_find(&mgr->cb_handles, handle);
	अगर (!cb) अणु
		dev_err(hdev->dev,
			"CB info failed, no match to handle 0x%x\n", handle);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	*usage_cnt = atomic_पढ़ो(&cb->cs_cnt);

out:
	spin_unlock(&mgr->cb_lock);
	वापस rc;
पूर्ण

पूर्णांक hl_cb_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data)
अणु
	जोड़ hl_cb_args *args = data;
	काष्ठा hl_device *hdev = hpriv->hdev;
	क्रमागत hl_device_status status;
	u64 handle = 0;
	u32 usage_cnt = 0;
	पूर्णांक rc;

	अगर (!hl_device_operational(hdev, &status)) अणु
		dev_warn_ratelimited(hdev->dev,
			"Device is %s. Can't execute CB IOCTL\n",
			hdev->status[status]);
		वापस -EBUSY;
	पूर्ण

	चयन (args->in.op) अणु
	हाल HL_CB_OP_CREATE:
		अगर (args->in.cb_size > HL_MAX_CB_SIZE) अणु
			dev_err(hdev->dev,
				"User requested CB size %d must be less than %d\n",
				args->in.cb_size, HL_MAX_CB_SIZE);
			rc = -EINVAL;
		पूर्ण अन्यथा अणु
			rc = hl_cb_create(hdev, &hpriv->cb_mgr, hpriv->ctx,
					args->in.cb_size, false,
					!!(args->in.flags & HL_CB_FLAGS_MAP),
					&handle);
		पूर्ण

		स_रखो(args, 0, माप(*args));
		args->out.cb_handle = handle;
		अवरोध;

	हाल HL_CB_OP_DESTROY:
		rc = hl_cb_destroy(hdev, &hpriv->cb_mgr,
					args->in.cb_handle);
		अवरोध;

	हाल HL_CB_OP_INFO:
		rc = hl_cb_info(hdev, &hpriv->cb_mgr, args->in.cb_handle,
				&usage_cnt);
		स_रखो(args, 0, माप(*args));
		args->out.usage_cnt = usage_cnt;
		अवरोध;

	शेष:
		rc = -ENOTTY;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम cb_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा hl_cb *cb = (काष्ठा hl_cb *) vma->vm_निजी_data;
	दीर्घ new_mmap_size;

	new_mmap_size = cb->mmap_size - (vma->vm_end - vma->vm_start);

	अगर (new_mmap_size > 0) अणु
		cb->mmap_size = new_mmap_size;
		वापस;
	पूर्ण

	spin_lock(&cb->lock);
	cb->mmap = false;
	spin_unlock(&cb->lock);

	hl_cb_put(cb);
	vma->vm_निजी_data = शून्य;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा cb_vm_ops = अणु
	.बंद = cb_vm_बंद
पूर्ण;

पूर्णांक hl_cb_mmap(काष्ठा hl_fpriv *hpriv, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_cb *cb;
	u32 handle, user_cb_size;
	पूर्णांक rc;

	/* We use the page offset to hold the idr and thus we need to clear
	 * it beक्रमe करोing the mmap itself
	 */
	handle = vma->vm_pgoff;
	vma->vm_pgoff = 0;

	/* reference was taken here */
	cb = hl_cb_get(hdev, &hpriv->cb_mgr, handle);
	अगर (!cb) अणु
		dev_err(hdev->dev,
			"CB mmap failed, no match to handle 0x%x\n", handle);
		वापस -EINVAL;
	पूर्ण

	/* Validation check */
	user_cb_size = vma->vm_end - vma->vm_start;
	अगर (user_cb_size != ALIGN(cb->size, PAGE_SIZE)) अणु
		dev_err(hdev->dev,
			"CB mmap failed, mmap size 0x%lx != 0x%x cb size\n",
			vma->vm_end - vma->vm_start, cb->size);
		rc = -EINVAL;
		जाओ put_cb;
	पूर्ण

	अगर (!access_ok((व्योम __user *) (uपूर्णांकptr_t) vma->vm_start,
							user_cb_size)) अणु
		dev_err(hdev->dev,
			"user pointer is invalid - 0x%lx\n",
			vma->vm_start);

		rc = -EINVAL;
		जाओ put_cb;
	पूर्ण

	spin_lock(&cb->lock);

	अगर (cb->mmap) अणु
		dev_err(hdev->dev,
			"CB mmap failed, CB already mmaped to user\n");
		rc = -EINVAL;
		जाओ release_lock;
	पूर्ण

	cb->mmap = true;

	spin_unlock(&cb->lock);

	vma->vm_ops = &cb_vm_ops;

	/*
	 * Note: We're transferring the cb reference to
	 * vma->vm_निजी_data here.
	 */

	vma->vm_निजी_data = cb;

	rc = hdev->asic_funcs->cb_mmap(hdev, vma, cb->kernel_address,
					cb->bus_address, cb->size);
	अगर (rc) अणु
		spin_lock(&cb->lock);
		cb->mmap = false;
		जाओ release_lock;
	पूर्ण

	cb->mmap_size = cb->size;
	vma->vm_pgoff = handle;

	वापस 0;

release_lock:
	spin_unlock(&cb->lock);
put_cb:
	hl_cb_put(cb);
	वापस rc;
पूर्ण

काष्ठा hl_cb *hl_cb_get(काष्ठा hl_device *hdev, काष्ठा hl_cb_mgr *mgr,
			u32 handle)
अणु
	काष्ठा hl_cb *cb;

	spin_lock(&mgr->cb_lock);
	cb = idr_find(&mgr->cb_handles, handle);

	अगर (!cb) अणु
		spin_unlock(&mgr->cb_lock);
		dev_warn(hdev->dev,
			"CB get failed, no match to handle 0x%x\n", handle);
		वापस शून्य;
	पूर्ण

	kref_get(&cb->refcount);

	spin_unlock(&mgr->cb_lock);

	वापस cb;

पूर्ण

व्योम hl_cb_put(काष्ठा hl_cb *cb)
अणु
	kref_put(&cb->refcount, cb_release);
पूर्ण

व्योम hl_cb_mgr_init(काष्ठा hl_cb_mgr *mgr)
अणु
	spin_lock_init(&mgr->cb_lock);
	idr_init(&mgr->cb_handles);
पूर्ण

व्योम hl_cb_mgr_fini(काष्ठा hl_device *hdev, काष्ठा hl_cb_mgr *mgr)
अणु
	काष्ठा hl_cb *cb;
	काष्ठा idr *idp;
	u32 id;

	idp = &mgr->cb_handles;

	idr_क्रम_each_entry(idp, cb, id) अणु
		अगर (kref_put(&cb->refcount, cb_release) != 1)
			dev_err(hdev->dev,
				"CB %d for CTX ID %d is still alive\n",
				id, cb->ctx->asid);
	पूर्ण

	idr_destroy(&mgr->cb_handles);
पूर्ण

काष्ठा hl_cb *hl_cb_kernel_create(काष्ठा hl_device *hdev, u32 cb_size,
					bool पूर्णांकernal_cb)
अणु
	u64 cb_handle;
	काष्ठा hl_cb *cb;
	पूर्णांक rc;

	rc = hl_cb_create(hdev, &hdev->kernel_cb_mgr, hdev->kernel_ctx, cb_size,
				पूर्णांकernal_cb, false, &cb_handle);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to allocate CB for the kernel driver %d\n", rc);
		वापस शून्य;
	पूर्ण

	cb_handle >>= PAGE_SHIFT;
	cb = hl_cb_get(hdev, &hdev->kernel_cb_mgr, (u32) cb_handle);
	/* hl_cb_get should never fail here */
	अगर (!cb) अणु
		dev_crit(hdev->dev, "Kernel CB handle invalid 0x%x\n",
				(u32) cb_handle);
		जाओ destroy_cb;
	पूर्ण

	वापस cb;

destroy_cb:
	hl_cb_destroy(hdev, &hdev->kernel_cb_mgr, cb_handle << PAGE_SHIFT);

	वापस शून्य;
पूर्ण

पूर्णांक hl_cb_pool_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा hl_cb *cb;
	पूर्णांक i;

	INIT_LIST_HEAD(&hdev->cb_pool);
	spin_lock_init(&hdev->cb_pool_lock);

	क्रम (i = 0 ; i < hdev->asic_prop.cb_pool_cb_cnt ; i++) अणु
		cb = hl_cb_alloc(hdev, hdev->asic_prop.cb_pool_cb_size,
				HL_KERNEL_ASID_ID, false);
		अगर (cb) अणु
			cb->is_pool = true;
			list_add(&cb->pool_list, &hdev->cb_pool);
		पूर्ण अन्यथा अणु
			hl_cb_pool_fini(hdev);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hl_cb_pool_fini(काष्ठा hl_device *hdev)
अणु
	काष्ठा hl_cb *cb, *पंचांगp;

	list_क्रम_each_entry_safe(cb, पंचांगp, &hdev->cb_pool, pool_list) अणु
		list_del(&cb->pool_list);
		cb_fini(hdev, cb);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hl_cb_va_pool_init(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	पूर्णांक rc;

	अगर (!hdev->supports_cb_mapping)
		वापस 0;

	ctx->cb_va_pool = gen_pool_create(__ffs(prop->pmmu.page_size), -1);
	अगर (!ctx->cb_va_pool) अणु
		dev_err(hdev->dev,
			"Failed to create VA gen pool for CB mapping\n");
		वापस -ENOMEM;
	पूर्ण

	rc = gen_pool_add(ctx->cb_va_pool, prop->cb_बहु_शुरू_addr,
			prop->cb_बहु_पूर्ण_addr - prop->cb_बहु_शुरू_addr, -1);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to add memory to VA gen pool for CB mapping\n");
		जाओ err_pool_destroy;
	पूर्ण

	वापस 0;

err_pool_destroy:
	gen_pool_destroy(ctx->cb_va_pool);

	वापस rc;
पूर्ण

व्योम hl_cb_va_pool_fini(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;

	अगर (!hdev->supports_cb_mapping)
		वापस;

	gen_pool_destroy(ctx->cb_va_pool);
पूर्ण
