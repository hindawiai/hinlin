<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * seqno-fence, using a dma-buf to synchronize fencing
 *
 * Copyright (C) 2012 Texas Instruments
 * Copyright (C) 2012-2014 Canonical Ltd
 * Authors:
 *   Rob Clark <robdclark@gmail.com>
 *   Maarten Lankhorst <maarten.lankhorst@canonical.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/seqno-fence.h>

अटल स्थिर अक्षर *seqno_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा seqno_fence *seqno_fence = to_seqno_fence(fence);

	वापस seqno_fence->ops->get_driver_name(fence);
पूर्ण

अटल स्थिर अक्षर *seqno_fence_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा seqno_fence *seqno_fence = to_seqno_fence(fence);

	वापस seqno_fence->ops->get_समयline_name(fence);
पूर्ण

अटल bool seqno_enable_संकेतing(काष्ठा dma_fence *fence)
अणु
	काष्ठा seqno_fence *seqno_fence = to_seqno_fence(fence);

	वापस seqno_fence->ops->enable_संकेतing(fence);
पूर्ण

अटल bool seqno_संकेतed(काष्ठा dma_fence *fence)
अणु
	काष्ठा seqno_fence *seqno_fence = to_seqno_fence(fence);

	वापस seqno_fence->ops->संकेतed && seqno_fence->ops->संकेतed(fence);
पूर्ण

अटल व्योम seqno_release(काष्ठा dma_fence *fence)
अणु
	काष्ठा seqno_fence *f = to_seqno_fence(fence);

	dma_buf_put(f->sync_buf);
	अगर (f->ops->release)
		f->ops->release(fence);
	अन्यथा
		dma_fence_मुक्त(&f->base);
पूर्ण

अटल चिन्हित दीर्घ seqno_रुको(काष्ठा dma_fence *fence, bool पूर्णांकr,
			      चिन्हित दीर्घ समयout)
अणु
	काष्ठा seqno_fence *f = to_seqno_fence(fence);

	वापस f->ops->रुको(fence, पूर्णांकr, समयout);
पूर्ण

स्थिर काष्ठा dma_fence_ops seqno_fence_ops = अणु
	.get_driver_name = seqno_fence_get_driver_name,
	.get_समयline_name = seqno_fence_get_समयline_name,
	.enable_संकेतing = seqno_enable_संकेतing,
	.संकेतed = seqno_संकेतed,
	.रुको = seqno_रुको,
	.release = seqno_release,
पूर्ण;
EXPORT_SYMBOL(seqno_fence_ops);
