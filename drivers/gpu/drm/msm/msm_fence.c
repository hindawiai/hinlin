<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013-2016 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/dma-fence.h>

#समावेश "msm_drv.h"
#समावेश "msm_fence.h"


काष्ठा msm_fence_context *
msm_fence_context_alloc(काष्ठा drm_device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा msm_fence_context *fctx;

	fctx = kzalloc(माप(*fctx), GFP_KERNEL);
	अगर (!fctx)
		वापस ERR_PTR(-ENOMEM);

	fctx->dev = dev;
	म_नकलन(fctx->name, name, माप(fctx->name));
	fctx->context = dma_fence_context_alloc(1);
	init_रुकोqueue_head(&fctx->event);
	spin_lock_init(&fctx->spinlock);

	वापस fctx;
पूर्ण

व्योम msm_fence_context_मुक्त(काष्ठा msm_fence_context *fctx)
अणु
	kमुक्त(fctx);
पूर्ण

अटल अंतरभूत bool fence_completed(काष्ठा msm_fence_context *fctx, uपूर्णांक32_t fence)
अणु
	वापस (पूर्णांक32_t)(fctx->completed_fence - fence) >= 0;
पूर्ण

/* legacy path क्रम WAIT_FENCE ioctl: */
पूर्णांक msm_रुको_fence(काष्ठा msm_fence_context *fctx, uपूर्णांक32_t fence,
		kसमय_प्रकार *समयout, bool पूर्णांकerruptible)
अणु
	पूर्णांक ret;

	अगर (fence > fctx->last_fence) अणु
		DRM_ERROR_RATELIMITED("%s: waiting on invalid fence: %u (of %u)\n",
				fctx->name, fence, fctx->last_fence);
		वापस -EINVAL;
	पूर्ण

	अगर (!समयout) अणु
		/* no-रुको: */
		ret = fence_completed(fctx, fence) ? 0 : -EBUSY;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ reमुख्यing_jअगरfies = समयout_to_jअगरfies(समयout);

		अगर (पूर्णांकerruptible)
			ret = रुको_event_पूर्णांकerruptible_समयout(fctx->event,
				fence_completed(fctx, fence),
				reमुख्यing_jअगरfies);
		अन्यथा
			ret = रुको_event_समयout(fctx->event,
				fence_completed(fctx, fence),
				reमुख्यing_jअगरfies);

		अगर (ret == 0) अणु
			DBG("timeout waiting for fence: %u (completed: %u)",
					fence, fctx->completed_fence);
			ret = -ETIMEDOUT;
		पूर्ण अन्यथा अगर (ret != -ERESTARTSYS) अणु
			ret = 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* called from workqueue */
व्योम msm_update_fence(काष्ठा msm_fence_context *fctx, uपूर्णांक32_t fence)
अणु
	spin_lock(&fctx->spinlock);
	fctx->completed_fence = max(fence, fctx->completed_fence);
	spin_unlock(&fctx->spinlock);

	wake_up_all(&fctx->event);
पूर्ण

काष्ठा msm_fence अणु
	काष्ठा dma_fence base;
	काष्ठा msm_fence_context *fctx;
पूर्ण;

अटल अंतरभूत काष्ठा msm_fence *to_msm_fence(काष्ठा dma_fence *fence)
अणु
	वापस container_of(fence, काष्ठा msm_fence, base);
पूर्ण

अटल स्थिर अक्षर *msm_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "msm";
पूर्ण

अटल स्थिर अक्षर *msm_fence_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा msm_fence *f = to_msm_fence(fence);
	वापस f->fctx->name;
पूर्ण

अटल bool msm_fence_संकेतed(काष्ठा dma_fence *fence)
अणु
	काष्ठा msm_fence *f = to_msm_fence(fence);
	वापस fence_completed(f->fctx, f->base.seqno);
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops msm_fence_ops = अणु
	.get_driver_name = msm_fence_get_driver_name,
	.get_समयline_name = msm_fence_get_समयline_name,
	.संकेतed = msm_fence_संकेतed,
पूर्ण;

काष्ठा dma_fence *
msm_fence_alloc(काष्ठा msm_fence_context *fctx)
अणु
	काष्ठा msm_fence *f;

	f = kzalloc(माप(*f), GFP_KERNEL);
	अगर (!f)
		वापस ERR_PTR(-ENOMEM);

	f->fctx = fctx;

	dma_fence_init(&f->base, &msm_fence_ops, &fctx->spinlock,
		       fctx->context, ++fctx->last_fence);

	वापस &f->base;
पूर्ण
