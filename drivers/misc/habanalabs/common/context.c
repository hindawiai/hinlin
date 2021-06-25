<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "habanalabs.h"

#समावेश <linux/slab.h>

अटल व्योम hl_ctx_fini(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	u64 idle_mask[HL_BUSY_ENGINES_MASK_EXT_SIZE] = अणु0पूर्ण;
	पूर्णांक i;

	/* Release all allocated pending cb's, those cb's were never
	 * scheduled so it is safe to release them here
	 */
	hl_pending_cb_list_flush(ctx);

	/* Release all allocated HW block mapped list entries and destroy
	 * the mutex.
	 */
	hl_hw_block_mem_fini(ctx);

	/*
	 * If we arrived here, there are no jobs रुकोing क्रम this context
	 * on its queues so we can safely हटाओ it.
	 * This is because क्रम each CS, we increment the ref count and क्रम
	 * every CS that was finished we decrement it and we won't arrive
	 * to this function unless the ref count is 0
	 */

	क्रम (i = 0 ; i < hdev->asic_prop.max_pending_cs ; i++)
		hl_fence_put(ctx->cs_pending[i]);

	kमुक्त(ctx->cs_pending);

	अगर (ctx->asid != HL_KERNEL_ASID_ID) अणु
		dev_dbg(hdev->dev, "closing user context %d\n", ctx->asid);

		/* The engines are stopped as there is no executing CS, but the
		 * Coresight might be still working by accessing addresses
		 * related to the stopped engines. Hence stop it explicitly.
		 * Stop only अगर this is the compute context, as there can be
		 * only one compute context
		 */
		अगर ((hdev->in_debug) && (hdev->compute_ctx == ctx))
			hl_device_set_debug_mode(hdev, false);

		hdev->asic_funcs->ctx_fini(ctx);
		hl_cb_va_pool_fini(ctx);
		hl_vm_ctx_fini(ctx);
		hl_asid_मुक्त(hdev, ctx->asid);

		/* Scrub both SRAM and DRAM */
		hdev->asic_funcs->scrub_device_mem(hdev, 0, 0);

		अगर ((!hdev->pldm) && (hdev->pdev) &&
				(!hdev->asic_funcs->is_device_idle(hdev,
					idle_mask,
					HL_BUSY_ENGINES_MASK_EXT_SIZE, शून्य)))
			dev_notice(hdev->dev,
					"device not idle after user context is closed (0x%llx, 0x%llx)\n",
						idle_mask[0], idle_mask[1]);
	पूर्ण अन्यथा अणु
		dev_dbg(hdev->dev, "closing kernel context\n");
		hdev->asic_funcs->ctx_fini(ctx);
		hl_vm_ctx_fini(ctx);
		hl_mmu_ctx_fini(ctx);
	पूर्ण
पूर्ण

व्योम hl_ctx_करो_release(काष्ठा kref *ref)
अणु
	काष्ठा hl_ctx *ctx;

	ctx = container_of(ref, काष्ठा hl_ctx, refcount);

	hl_ctx_fini(ctx);

	अगर (ctx->hpriv)
		hl_hpriv_put(ctx->hpriv);

	kमुक्त(ctx);
पूर्ण

पूर्णांक hl_ctx_create(काष्ठा hl_device *hdev, काष्ठा hl_fpriv *hpriv)
अणु
	काष्ठा hl_ctx_mgr *mgr = &hpriv->ctx_mgr;
	काष्ठा hl_ctx *ctx;
	पूर्णांक rc;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		rc = -ENOMEM;
		जाओ out_err;
	पूर्ण

	mutex_lock(&mgr->ctx_lock);
	rc = idr_alloc(&mgr->ctx_handles, ctx, 1, 0, GFP_KERNEL);
	mutex_unlock(&mgr->ctx_lock);

	अगर (rc < 0) अणु
		dev_err(hdev->dev, "Failed to allocate IDR for a new CTX\n");
		जाओ मुक्त_ctx;
	पूर्ण

	ctx->handle = rc;

	rc = hl_ctx_init(hdev, ctx, false);
	अगर (rc)
		जाओ हटाओ_from_idr;

	hl_hpriv_get(hpriv);
	ctx->hpriv = hpriv;

	/* TODO: हटाओ क्रम multiple contexts per process */
	hpriv->ctx = ctx;

	/* TODO: हटाओ the following line क्रम multiple process support */
	hdev->compute_ctx = ctx;

	वापस 0;

हटाओ_from_idr:
	mutex_lock(&mgr->ctx_lock);
	idr_हटाओ(&mgr->ctx_handles, ctx->handle);
	mutex_unlock(&mgr->ctx_lock);
मुक्त_ctx:
	kमुक्त(ctx);
out_err:
	वापस rc;
पूर्ण

व्योम hl_ctx_मुक्त(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx)
अणु
	अगर (kref_put(&ctx->refcount, hl_ctx_करो_release) == 1)
		वापस;

	dev_warn(hdev->dev,
		"user process released device but its command submissions are still executing\n");
पूर्ण

पूर्णांक hl_ctx_init(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx, bool is_kernel_ctx)
अणु
	पूर्णांक rc = 0;

	ctx->hdev = hdev;

	kref_init(&ctx->refcount);

	ctx->cs_sequence = 1;
	INIT_LIST_HEAD(&ctx->pending_cb_list);
	spin_lock_init(&ctx->pending_cb_lock);
	spin_lock_init(&ctx->cs_lock);
	atomic_set(&ctx->thपढ़ो_ctx_चयन_token, 1);
	atomic_set(&ctx->thपढ़ो_pending_cb_token, 1);
	ctx->thपढ़ो_ctx_चयन_रुको_token = 0;
	ctx->cs_pending = kसुस्मृति(hdev->asic_prop.max_pending_cs,
				माप(काष्ठा hl_fence *),
				GFP_KERNEL);
	अगर (!ctx->cs_pending)
		वापस -ENOMEM;

	hl_hw_block_mem_init(ctx);

	अगर (is_kernel_ctx) अणु
		ctx->asid = HL_KERNEL_ASID_ID; /* Kernel driver माला_लो ASID 0 */
		rc = hl_vm_ctx_init(ctx);
		अगर (rc) अणु
			dev_err(hdev->dev, "Failed to init mem ctx module\n");
			rc = -ENOMEM;
			जाओ err_hw_block_mem_fini;
		पूर्ण

		rc = hdev->asic_funcs->ctx_init(ctx);
		अगर (rc) अणु
			dev_err(hdev->dev, "ctx_init failed\n");
			जाओ err_vm_ctx_fini;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctx->asid = hl_asid_alloc(hdev);
		अगर (!ctx->asid) अणु
			dev_err(hdev->dev, "No free ASID, failed to create context\n");
			rc = -ENOMEM;
			जाओ err_hw_block_mem_fini;
		पूर्ण

		rc = hl_vm_ctx_init(ctx);
		अगर (rc) अणु
			dev_err(hdev->dev, "Failed to init mem ctx module\n");
			rc = -ENOMEM;
			जाओ err_asid_मुक्त;
		पूर्ण

		rc = hl_cb_va_pool_init(ctx);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"Failed to init VA pool for mapped CB\n");
			जाओ err_vm_ctx_fini;
		पूर्ण

		rc = hdev->asic_funcs->ctx_init(ctx);
		अगर (rc) अणु
			dev_err(hdev->dev, "ctx_init failed\n");
			जाओ err_cb_va_pool_fini;
		पूर्ण

		dev_dbg(hdev->dev, "create user context %d\n", ctx->asid);
	पूर्ण

	वापस 0;

err_cb_va_pool_fini:
	hl_cb_va_pool_fini(ctx);
err_vm_ctx_fini:
	hl_vm_ctx_fini(ctx);
err_asid_मुक्त:
	अगर (ctx->asid != HL_KERNEL_ASID_ID)
		hl_asid_मुक्त(hdev, ctx->asid);
err_hw_block_mem_fini:
	hl_hw_block_mem_fini(ctx);
	kमुक्त(ctx->cs_pending);

	वापस rc;
पूर्ण

व्योम hl_ctx_get(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx)
अणु
	kref_get(&ctx->refcount);
पूर्ण

पूर्णांक hl_ctx_put(काष्ठा hl_ctx *ctx)
अणु
	वापस kref_put(&ctx->refcount, hl_ctx_करो_release);
पूर्ण

काष्ठा hl_fence *hl_ctx_get_fence(काष्ठा hl_ctx *ctx, u64 seq)
अणु
	काष्ठा asic_fixed_properties *asic_prop = &ctx->hdev->asic_prop;
	काष्ठा hl_fence *fence;

	spin_lock(&ctx->cs_lock);

	अगर (seq >= ctx->cs_sequence) अणु
		spin_unlock(&ctx->cs_lock);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (seq + asic_prop->max_pending_cs < ctx->cs_sequence) अणु
		spin_unlock(&ctx->cs_lock);
		वापस शून्य;
	पूर्ण

	fence = ctx->cs_pending[seq & (asic_prop->max_pending_cs - 1)];
	hl_fence_get(fence);

	spin_unlock(&ctx->cs_lock);

	वापस fence;
पूर्ण

/*
 * hl_ctx_mgr_init - initialize the context manager
 *
 * @mgr: poपूर्णांकer to context manager काष्ठाure
 *
 * This manager is an object inside the hpriv object of the user process.
 * The function is called when a user process खोलोs the FD.
 */
व्योम hl_ctx_mgr_init(काष्ठा hl_ctx_mgr *mgr)
अणु
	mutex_init(&mgr->ctx_lock);
	idr_init(&mgr->ctx_handles);
पूर्ण

/*
 * hl_ctx_mgr_fini - finalize the context manager
 *
 * @hdev: poपूर्णांकer to device काष्ठाure
 * @mgr: poपूर्णांकer to context manager काष्ठाure
 *
 * This function goes over all the contexts in the manager and मुक्तs them.
 * It is called when a process बंदs the FD.
 */
व्योम hl_ctx_mgr_fini(काष्ठा hl_device *hdev, काष्ठा hl_ctx_mgr *mgr)
अणु
	काष्ठा hl_ctx *ctx;
	काष्ठा idr *idp;
	u32 id;

	idp = &mgr->ctx_handles;

	idr_क्रम_each_entry(idp, ctx, id)
		hl_ctx_मुक्त(hdev, ctx);

	idr_destroy(&mgr->ctx_handles);
	mutex_destroy(&mgr->ctx_lock);
पूर्ण
