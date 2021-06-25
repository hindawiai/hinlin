<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015-2016, Linaro Limited
 */
#समावेश <linux/device.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/idr.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/tee_drv.h>
#समावेश <linux/uपन.स>
#समावेश "tee_private.h"

अटल व्योम release_रेजिस्टरed_pages(काष्ठा tee_shm *shm)
अणु
	अगर (shm->pages) अणु
		अगर (shm->flags & TEE_SHM_USER_MAPPED) अणु
			unpin_user_pages(shm->pages, shm->num_pages);
		पूर्ण अन्यथा अणु
			माप_प्रकार n;

			क्रम (n = 0; n < shm->num_pages; n++)
				put_page(shm->pages[n]);
		पूर्ण

		kमुक्त(shm->pages);
	पूर्ण
पूर्ण

अटल व्योम tee_shm_release(काष्ठा tee_shm *shm)
अणु
	काष्ठा tee_device *teedev = shm->ctx->teedev;

	अगर (shm->flags & TEE_SHM_DMA_BUF) अणु
		mutex_lock(&teedev->mutex);
		idr_हटाओ(&teedev->idr, shm->id);
		mutex_unlock(&teedev->mutex);
	पूर्ण

	अगर (shm->flags & TEE_SHM_POOL) अणु
		काष्ठा tee_shm_pool_mgr *poolm;

		अगर (shm->flags & TEE_SHM_DMA_BUF)
			poolm = teedev->pool->dma_buf_mgr;
		अन्यथा
			poolm = teedev->pool->निजी_mgr;

		poolm->ops->मुक्त(poolm, shm);
	पूर्ण अन्यथा अगर (shm->flags & TEE_SHM_REGISTER) अणु
		पूर्णांक rc = teedev->desc->ops->shm_unरेजिस्टर(shm->ctx, shm);

		अगर (rc)
			dev_err(teedev->dev.parent,
				"unregister shm %p failed: %d", shm, rc);

		release_रेजिस्टरed_pages(shm);
	पूर्ण

	teedev_ctx_put(shm->ctx);

	kमुक्त(shm);

	tee_device_put(teedev);
पूर्ण

अटल काष्ठा sg_table *tee_shm_op_map_dma_buf(काष्ठा dma_buf_attachment
			*attach, क्रमागत dma_data_direction dir)
अणु
	वापस शून्य;
पूर्ण

अटल व्योम tee_shm_op_unmap_dma_buf(काष्ठा dma_buf_attachment *attach,
				     काष्ठा sg_table *table,
				     क्रमागत dma_data_direction dir)
अणु
पूर्ण

अटल व्योम tee_shm_op_release(काष्ठा dma_buf *dmabuf)
अणु
	काष्ठा tee_shm *shm = dmabuf->priv;

	tee_shm_release(shm);
पूर्ण

अटल पूर्णांक tee_shm_op_mmap(काष्ठा dma_buf *dmabuf, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा tee_shm *shm = dmabuf->priv;
	माप_प्रकार size = vma->vm_end - vma->vm_start;

	/* Refuse sharing shared memory provided by application */
	अगर (shm->flags & TEE_SHM_USER_MAPPED)
		वापस -EINVAL;

	वापस remap_pfn_range(vma, vma->vm_start, shm->paddr >> PAGE_SHIFT,
			       size, vma->vm_page_prot);
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops tee_shm_dma_buf_ops = अणु
	.map_dma_buf = tee_shm_op_map_dma_buf,
	.unmap_dma_buf = tee_shm_op_unmap_dma_buf,
	.release = tee_shm_op_release,
	.mmap = tee_shm_op_mmap,
पूर्ण;

काष्ठा tee_shm *tee_shm_alloc(काष्ठा tee_context *ctx, माप_प्रकार size, u32 flags)
अणु
	काष्ठा tee_device *teedev = ctx->teedev;
	काष्ठा tee_shm_pool_mgr *poolm = शून्य;
	काष्ठा tee_shm *shm;
	व्योम *ret;
	पूर्णांक rc;

	अगर (!(flags & TEE_SHM_MAPPED)) अणु
		dev_err(teedev->dev.parent,
			"only mapped allocations supported\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर ((flags & ~(TEE_SHM_MAPPED | TEE_SHM_DMA_BUF))) अणु
		dev_err(teedev->dev.parent, "invalid shm flags 0x%x", flags);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!tee_device_get(teedev))
		वापस ERR_PTR(-EINVAL);

	अगर (!teedev->pool) अणु
		/* teedev has been detached from driver */
		ret = ERR_PTR(-EINVAL);
		जाओ err_dev_put;
	पूर्ण

	shm = kzalloc(माप(*shm), GFP_KERNEL);
	अगर (!shm) अणु
		ret = ERR_PTR(-ENOMEM);
		जाओ err_dev_put;
	पूर्ण

	shm->flags = flags | TEE_SHM_POOL;
	shm->ctx = ctx;
	अगर (flags & TEE_SHM_DMA_BUF)
		poolm = teedev->pool->dma_buf_mgr;
	अन्यथा
		poolm = teedev->pool->निजी_mgr;

	rc = poolm->ops->alloc(poolm, shm, size);
	अगर (rc) अणु
		ret = ERR_PTR(rc);
		जाओ err_kमुक्त;
	पूर्ण


	अगर (flags & TEE_SHM_DMA_BUF) अणु
		DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

		mutex_lock(&teedev->mutex);
		shm->id = idr_alloc(&teedev->idr, shm, 1, 0, GFP_KERNEL);
		mutex_unlock(&teedev->mutex);
		अगर (shm->id < 0) अणु
			ret = ERR_PTR(shm->id);
			जाओ err_pool_मुक्त;
		पूर्ण

		exp_info.ops = &tee_shm_dma_buf_ops;
		exp_info.size = shm->size;
		exp_info.flags = O_RDWR;
		exp_info.priv = shm;

		shm->dmabuf = dma_buf_export(&exp_info);
		अगर (IS_ERR(shm->dmabuf)) अणु
			ret = ERR_CAST(shm->dmabuf);
			जाओ err_rem;
		पूर्ण
	पूर्ण

	teedev_ctx_get(ctx);

	वापस shm;
err_rem:
	अगर (flags & TEE_SHM_DMA_BUF) अणु
		mutex_lock(&teedev->mutex);
		idr_हटाओ(&teedev->idr, shm->id);
		mutex_unlock(&teedev->mutex);
	पूर्ण
err_pool_मुक्त:
	poolm->ops->मुक्त(poolm, shm);
err_kमुक्त:
	kमुक्त(shm);
err_dev_put:
	tee_device_put(teedev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_alloc);

काष्ठा tee_shm *tee_shm_रेजिस्टर(काष्ठा tee_context *ctx, अचिन्हित दीर्घ addr,
				 माप_प्रकार length, u32 flags)
अणु
	काष्ठा tee_device *teedev = ctx->teedev;
	स्थिर u32 req_user_flags = TEE_SHM_DMA_BUF | TEE_SHM_USER_MAPPED;
	स्थिर u32 req_kernel_flags = TEE_SHM_DMA_BUF | TEE_SHM_KERNEL_MAPPED;
	काष्ठा tee_shm *shm;
	व्योम *ret;
	पूर्णांक rc;
	पूर्णांक num_pages;
	अचिन्हित दीर्घ start;

	अगर (flags != req_user_flags && flags != req_kernel_flags)
		वापस ERR_PTR(-ENOTSUPP);

	अगर (!tee_device_get(teedev))
		वापस ERR_PTR(-EINVAL);

	अगर (!teedev->desc->ops->shm_रेजिस्टर ||
	    !teedev->desc->ops->shm_unरेजिस्टर) अणु
		tee_device_put(teedev);
		वापस ERR_PTR(-ENOTSUPP);
	पूर्ण

	teedev_ctx_get(ctx);

	shm = kzalloc(माप(*shm), GFP_KERNEL);
	अगर (!shm) अणु
		ret = ERR_PTR(-ENOMEM);
		जाओ err;
	पूर्ण

	shm->flags = flags | TEE_SHM_REGISTER;
	shm->ctx = ctx;
	shm->id = -1;
	addr = untagged_addr(addr);
	start = roundकरोwn(addr, PAGE_SIZE);
	shm->offset = addr - start;
	shm->size = length;
	num_pages = (roundup(addr + length, PAGE_SIZE) - start) / PAGE_SIZE;
	shm->pages = kसुस्मृति(num_pages, माप(*shm->pages), GFP_KERNEL);
	अगर (!shm->pages) अणु
		ret = ERR_PTR(-ENOMEM);
		जाओ err;
	पूर्ण

	अगर (flags & TEE_SHM_USER_MAPPED) अणु
		rc = pin_user_pages_fast(start, num_pages, FOLL_WRITE,
					 shm->pages);
	पूर्ण अन्यथा अणु
		काष्ठा kvec *kiov;
		पूर्णांक i;

		kiov = kसुस्मृति(num_pages, माप(*kiov), GFP_KERNEL);
		अगर (!kiov) अणु
			ret = ERR_PTR(-ENOMEM);
			जाओ err;
		पूर्ण

		क्रम (i = 0; i < num_pages; i++) अणु
			kiov[i].iov_base = (व्योम *)(start + i * PAGE_SIZE);
			kiov[i].iov_len = PAGE_SIZE;
		पूर्ण

		rc = get_kernel_pages(kiov, num_pages, 0, shm->pages);
		kमुक्त(kiov);
	पूर्ण
	अगर (rc > 0)
		shm->num_pages = rc;
	अगर (rc != num_pages) अणु
		अगर (rc >= 0)
			rc = -ENOMEM;
		ret = ERR_PTR(rc);
		जाओ err;
	पूर्ण

	mutex_lock(&teedev->mutex);
	shm->id = idr_alloc(&teedev->idr, shm, 1, 0, GFP_KERNEL);
	mutex_unlock(&teedev->mutex);

	अगर (shm->id < 0) अणु
		ret = ERR_PTR(shm->id);
		जाओ err;
	पूर्ण

	rc = teedev->desc->ops->shm_रेजिस्टर(ctx, shm, shm->pages,
					     shm->num_pages, start);
	अगर (rc) अणु
		ret = ERR_PTR(rc);
		जाओ err;
	पूर्ण

	अगर (flags & TEE_SHM_DMA_BUF) अणु
		DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

		exp_info.ops = &tee_shm_dma_buf_ops;
		exp_info.size = shm->size;
		exp_info.flags = O_RDWR;
		exp_info.priv = shm;

		shm->dmabuf = dma_buf_export(&exp_info);
		अगर (IS_ERR(shm->dmabuf)) अणु
			ret = ERR_CAST(shm->dmabuf);
			teedev->desc->ops->shm_unरेजिस्टर(ctx, shm);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस shm;
err:
	अगर (shm) अणु
		अगर (shm->id >= 0) अणु
			mutex_lock(&teedev->mutex);
			idr_हटाओ(&teedev->idr, shm->id);
			mutex_unlock(&teedev->mutex);
		पूर्ण
		release_रेजिस्टरed_pages(shm);
	पूर्ण
	kमुक्त(shm);
	teedev_ctx_put(ctx);
	tee_device_put(teedev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_रेजिस्टर);

/**
 * tee_shm_get_fd() - Increase reference count and वापस file descriptor
 * @shm:	Shared memory handle
 * @वापसs user space file descriptor to shared memory
 */
पूर्णांक tee_shm_get_fd(काष्ठा tee_shm *shm)
अणु
	पूर्णांक fd;

	अगर (!(shm->flags & TEE_SHM_DMA_BUF))
		वापस -EINVAL;

	get_dma_buf(shm->dmabuf);
	fd = dma_buf_fd(shm->dmabuf, O_CLOEXEC);
	अगर (fd < 0)
		dma_buf_put(shm->dmabuf);
	वापस fd;
पूर्ण

/**
 * tee_shm_मुक्त() - Free shared memory
 * @shm:	Handle to shared memory to मुक्त
 */
व्योम tee_shm_मुक्त(काष्ठा tee_shm *shm)
अणु
	/*
	 * dma_buf_put() decreases the dmabuf reference counter and will
	 * call tee_shm_release() when the last reference is gone.
	 *
	 * In the हाल of driver निजी memory we call tee_shm_release
	 * directly instead as it करोesn't have a reference counter.
	 */
	अगर (shm->flags & TEE_SHM_DMA_BUF)
		dma_buf_put(shm->dmabuf);
	अन्यथा
		tee_shm_release(shm);
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_मुक्त);

/**
 * tee_shm_va2pa() - Get physical address of a भव address
 * @shm:	Shared memory handle
 * @va:		Virtual address to tranlsate
 * @pa:		Returned physical address
 * @वापसs 0 on success and < 0 on failure
 */
पूर्णांक tee_shm_va2pa(काष्ठा tee_shm *shm, व्योम *va, phys_addr_t *pa)
अणु
	अगर (!(shm->flags & TEE_SHM_MAPPED))
		वापस -EINVAL;
	/* Check that we're in the range of the shm */
	अगर ((अक्षर *)va < (अक्षर *)shm->kaddr)
		वापस -EINVAL;
	अगर ((अक्षर *)va >= ((अक्षर *)shm->kaddr + shm->size))
		वापस -EINVAL;

	वापस tee_shm_get_pa(
			shm, (अचिन्हित दीर्घ)va - (अचिन्हित दीर्घ)shm->kaddr, pa);
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_va2pa);

/**
 * tee_shm_pa2va() - Get भव address of a physical address
 * @shm:	Shared memory handle
 * @pa:		Physical address to tranlsate
 * @va:		Returned भव address
 * @वापसs 0 on success and < 0 on failure
 */
पूर्णांक tee_shm_pa2va(काष्ठा tee_shm *shm, phys_addr_t pa, व्योम **va)
अणु
	अगर (!(shm->flags & TEE_SHM_MAPPED))
		वापस -EINVAL;
	/* Check that we're in the range of the shm */
	अगर (pa < shm->paddr)
		वापस -EINVAL;
	अगर (pa >= (shm->paddr + shm->size))
		वापस -EINVAL;

	अगर (va) अणु
		व्योम *v = tee_shm_get_va(shm, pa - shm->paddr);

		अगर (IS_ERR(v))
			वापस PTR_ERR(v);
		*va = v;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_pa2va);

/**
 * tee_shm_get_va() - Get भव address of a shared memory plus an offset
 * @shm:	Shared memory handle
 * @offs:	Offset from start of this shared memory
 * @वापसs भव address of the shared memory + offs अगर offs is within
 *	the bounds of this shared memory, अन्यथा an ERR_PTR
 */
व्योम *tee_shm_get_va(काष्ठा tee_shm *shm, माप_प्रकार offs)
अणु
	अगर (!(shm->flags & TEE_SHM_MAPPED))
		वापस ERR_PTR(-EINVAL);
	अगर (offs >= shm->size)
		वापस ERR_PTR(-EINVAL);
	वापस (अक्षर *)shm->kaddr + offs;
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_get_va);

/**
 * tee_shm_get_pa() - Get physical address of a shared memory plus an offset
 * @shm:	Shared memory handle
 * @offs:	Offset from start of this shared memory
 * @pa:		Physical address to वापस
 * @वापसs 0 अगर offs is within the bounds of this shared memory, अन्यथा an
 *	error code.
 */
पूर्णांक tee_shm_get_pa(काष्ठा tee_shm *shm, माप_प्रकार offs, phys_addr_t *pa)
अणु
	अगर (offs >= shm->size)
		वापस -EINVAL;
	अगर (pa)
		*pa = shm->paddr + offs;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_get_pa);

/**
 * tee_shm_get_from_id() - Find shared memory object and increase reference
 * count
 * @ctx:	Context owning the shared memory
 * @id:		Id of shared memory object
 * @वापसs a poपूर्णांकer to 'struct tee_shm' on success or an ERR_PTR on failure
 */
काष्ठा tee_shm *tee_shm_get_from_id(काष्ठा tee_context *ctx, पूर्णांक id)
अणु
	काष्ठा tee_device *teedev;
	काष्ठा tee_shm *shm;

	अगर (!ctx)
		वापस ERR_PTR(-EINVAL);

	teedev = ctx->teedev;
	mutex_lock(&teedev->mutex);
	shm = idr_find(&teedev->idr, id);
	अगर (!shm || shm->ctx != ctx)
		shm = ERR_PTR(-EINVAL);
	अन्यथा अगर (shm->flags & TEE_SHM_DMA_BUF)
		get_dma_buf(shm->dmabuf);
	mutex_unlock(&teedev->mutex);
	वापस shm;
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_get_from_id);

/**
 * tee_shm_put() - Decrease reference count on a shared memory handle
 * @shm:	Shared memory handle
 */
व्योम tee_shm_put(काष्ठा tee_shm *shm)
अणु
	अगर (shm->flags & TEE_SHM_DMA_BUF)
		dma_buf_put(shm->dmabuf);
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_put);
