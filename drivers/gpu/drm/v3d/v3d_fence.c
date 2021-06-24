<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2017-2018 Broadcom */

#समावेश "v3d_drv.h"

काष्ठा dma_fence *v3d_fence_create(काष्ठा v3d_dev *v3d, क्रमागत v3d_queue queue)
अणु
	काष्ठा v3d_fence *fence;

	fence = kzalloc(माप(*fence), GFP_KERNEL);
	अगर (!fence)
		वापस ERR_PTR(-ENOMEM);

	fence->dev = &v3d->drm;
	fence->queue = queue;
	fence->seqno = ++v3d->queue[queue].emit_seqno;
	dma_fence_init(&fence->base, &v3d_fence_ops, &v3d->job_lock,
		       v3d->queue[queue].fence_context, fence->seqno);

	वापस &fence->base;
पूर्ण

अटल स्थिर अक्षर *v3d_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "v3d";
पूर्ण

अटल स्थिर अक्षर *v3d_fence_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा v3d_fence *f = to_v3d_fence(fence);

	चयन (f->queue) अणु
	हाल V3D_BIN:
		वापस "v3d-bin";
	हाल V3D_RENDER:
		वापस "v3d-render";
	हाल V3D_TFU:
		वापस "v3d-tfu";
	हाल V3D_CSD:
		वापस "v3d-csd";
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

स्थिर काष्ठा dma_fence_ops v3d_fence_ops = अणु
	.get_driver_name = v3d_fence_get_driver_name,
	.get_समयline_name = v3d_fence_get_समयline_name,
पूर्ण;
