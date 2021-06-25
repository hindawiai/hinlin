<शैली गुरु>
// SPDX-License-Identअगरier: MIT

/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_sw_fence_work.h"

अटल व्योम fence_complete(काष्ठा dma_fence_work *f)
अणु
	अगर (f->ops->release)
		f->ops->release(f);
	dma_fence_संकेत(&f->dma);
पूर्ण

अटल व्योम fence_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dma_fence_work *f = container_of(work, typeof(*f), work);
	पूर्णांक err;

	err = f->ops->work(f);
	अगर (err)
		dma_fence_set_error(&f->dma, err);

	fence_complete(f);
	dma_fence_put(&f->dma);
पूर्ण

अटल पूर्णांक __i915_sw_fence_call
fence_notअगरy(काष्ठा i915_sw_fence *fence, क्रमागत i915_sw_fence_notअगरy state)
अणु
	काष्ठा dma_fence_work *f = container_of(fence, typeof(*f), chain);

	चयन (state) अणु
	हाल FENCE_COMPLETE:
		अगर (fence->error)
			dma_fence_set_error(&f->dma, fence->error);

		अगर (!f->dma.error) अणु
			dma_fence_get(&f->dma);
			अगर (test_bit(DMA_FENCE_WORK_IMM, &f->dma.flags))
				fence_work(&f->work);
			अन्यथा
				queue_work(प्रणाली_unbound_wq, &f->work);
		पूर्ण अन्यथा अणु
			fence_complete(f);
		पूर्ण
		अवरोध;

	हाल FENCE_FREE:
		dma_fence_put(&f->dma);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर अक्षर *get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "dma-fence";
पूर्ण

अटल स्थिर अक्षर *get_समयline_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence_work *f = container_of(fence, typeof(*f), dma);

	वापस f->ops->name ?: "work";
पूर्ण

अटल व्योम fence_release(काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence_work *f = container_of(fence, typeof(*f), dma);

	i915_sw_fence_fini(&f->chain);

	BUILD_BUG_ON(दुरत्व(typeof(*f), dma));
	dma_fence_मुक्त(&f->dma);
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops fence_ops = अणु
	.get_driver_name = get_driver_name,
	.get_समयline_name = get_समयline_name,
	.release = fence_release,
पूर्ण;

व्योम dma_fence_work_init(काष्ठा dma_fence_work *f,
			 स्थिर काष्ठा dma_fence_work_ops *ops)
अणु
	f->ops = ops;
	spin_lock_init(&f->lock);
	dma_fence_init(&f->dma, &fence_ops, &f->lock, 0, 0);
	i915_sw_fence_init(&f->chain, fence_notअगरy);
	INIT_WORK(&f->work, fence_work);
पूर्ण

पूर्णांक dma_fence_work_chain(काष्ठा dma_fence_work *f, काष्ठा dma_fence *संकेत)
अणु
	अगर (!संकेत)
		वापस 0;

	वापस __i915_sw_fence_aरुको_dma_fence(&f->chain, संकेत, &f->cb);
पूर्ण
