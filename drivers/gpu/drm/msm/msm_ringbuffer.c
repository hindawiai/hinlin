<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश "msm_ringbuffer.h"
#समावेश "msm_gpu.h"

काष्ठा msm_ringbuffer *msm_ringbuffer_new(काष्ठा msm_gpu *gpu, पूर्णांक id,
		व्योम *memptrs, uपूर्णांक64_t memptrs_iova)
अणु
	काष्ठा msm_ringbuffer *ring;
	अक्षर name[32];
	पूर्णांक ret;

	/* We assume everwhere that MSM_GPU_RINGBUFFER_SZ is a घातer of 2 */
	BUILD_BUG_ON(!is_घातer_of_2(MSM_GPU_RINGBUFFER_SZ));

	ring = kzalloc(माप(*ring), GFP_KERNEL);
	अगर (!ring) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	ring->gpu = gpu;
	ring->id = id;

	ring->start = msm_gem_kernel_new(gpu->dev, MSM_GPU_RINGBUFFER_SZ,
		check_apriv(gpu, MSM_BO_WC | MSM_BO_GPU_READONLY),
		gpu->aspace, &ring->bo, &ring->iova);

	अगर (IS_ERR(ring->start)) अणु
		ret = PTR_ERR(ring->start);
		ring->start = 0;
		जाओ fail;
	पूर्ण

	msm_gem_object_set_name(ring->bo, "ring%d", id);

	ring->end   = ring->start + (MSM_GPU_RINGBUFFER_SZ >> 2);
	ring->next  = ring->start;
	ring->cur   = ring->start;

	ring->memptrs = memptrs;
	ring->memptrs_iova = memptrs_iova;

	INIT_LIST_HEAD(&ring->submits);
	spin_lock_init(&ring->submit_lock);
	spin_lock_init(&ring->preempt_lock);

	snम_लिखो(name, माप(name), "gpu-ring-%d", ring->id);

	ring->fctx = msm_fence_context_alloc(gpu->dev, name);

	वापस ring;

fail:
	msm_ringbuffer_destroy(ring);
	वापस ERR_PTR(ret);
पूर्ण

व्योम msm_ringbuffer_destroy(काष्ठा msm_ringbuffer *ring)
अणु
	अगर (IS_ERR_OR_शून्य(ring))
		वापस;

	msm_fence_context_मुक्त(ring->fctx);

	msm_gem_kernel_put(ring->bo, ring->gpu->aspace, false);

	kमुक्त(ring);
पूर्ण
