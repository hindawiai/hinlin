<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */

/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित I915_SW_FENCE_WORK_H
#घोषणा I915_SW_FENCE_WORK_H

#समावेश <linux/dma-fence.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

#समावेश "i915_sw_fence.h"

काष्ठा dma_fence_work;

काष्ठा dma_fence_work_ops अणु
	स्थिर अक्षर *name;
	पूर्णांक (*work)(काष्ठा dma_fence_work *f);
	व्योम (*release)(काष्ठा dma_fence_work *f);
पूर्ण;

काष्ठा dma_fence_work अणु
	काष्ठा dma_fence dma;
	spinlock_t lock;

	काष्ठा i915_sw_fence chain;
	काष्ठा i915_sw_dma_fence_cb cb;

	काष्ठा work_काष्ठा work;
	स्थिर काष्ठा dma_fence_work_ops *ops;
पूर्ण;

क्रमागत अणु
	DMA_FENCE_WORK_IMM = DMA_FENCE_FLAG_USER_BITS,
पूर्ण;

व्योम dma_fence_work_init(काष्ठा dma_fence_work *f,
			 स्थिर काष्ठा dma_fence_work_ops *ops);
पूर्णांक dma_fence_work_chain(काष्ठा dma_fence_work *f, काष्ठा dma_fence *संकेत);

अटल अंतरभूत व्योम dma_fence_work_commit(काष्ठा dma_fence_work *f)
अणु
	i915_sw_fence_commit(&f->chain);
पूर्ण

/**
 * dma_fence_work_commit_imm: Commit the fence, and अगर possible execute locally.
 * @f: the fenced worker
 *
 * Instead of always scheduling a worker to execute the callback (see
 * dma_fence_work_commit()), we try to execute the callback immediately in
 * the local context. It is required that the fence be committed beक्रमe it
 * is published, and that no other thपढ़ोs try to tamper with the number
 * of asynchronous रुकोs on the fence (or अन्यथा the callback will be
 * executed in the wrong context, i.e. not the callers).
 */
अटल अंतरभूत व्योम dma_fence_work_commit_imm(काष्ठा dma_fence_work *f)
अणु
	अगर (atomic_पढ़ो(&f->chain.pending) <= 1)
		__set_bit(DMA_FENCE_WORK_IMM, &f->dma.flags);

	dma_fence_work_commit(f);
पूर्ण

#पूर्ण_अगर /* I915_SW_FENCE_WORK_H */
