<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * fence-chain: chain fences together in a समयline
 *
 * Copyright (C) 2018 Advanced Micro Devices, Inc.
 * Authors:
 *	Christian Kथघnig <christian.koenig@amd.com>
 */

#अगर_अघोषित __LINUX_DMA_FENCE_CHAIN_H
#घोषणा __LINUX_DMA_FENCE_CHAIN_H

#समावेश <linux/dma-fence.h>
#समावेश <linux/irq_work.h>

/**
 * काष्ठा dma_fence_chain - fence to represent an node of a fence chain
 * @base: fence base class
 * @lock: spinlock क्रम fence handling
 * @prev: previous fence of the chain
 * @prev_seqno: original previous seqno beक्रमe garbage collection
 * @fence: encapsulated fence
 * @cb: callback काष्ठाure क्रम संकेतing
 * @work: irq work item क्रम संकेतing
 */
काष्ठा dma_fence_chain अणु
	काष्ठा dma_fence base;
	spinlock_t lock;
	काष्ठा dma_fence __rcu *prev;
	u64 prev_seqno;
	काष्ठा dma_fence *fence;
	काष्ठा dma_fence_cb cb;
	काष्ठा irq_work work;
पूर्ण;

बाह्य स्थिर काष्ठा dma_fence_ops dma_fence_chain_ops;

/**
 * to_dma_fence_chain - cast a fence to a dma_fence_chain
 * @fence: fence to cast to a dma_fence_array
 *
 * Returns शून्य अगर the fence is not a dma_fence_chain,
 * or the dma_fence_chain otherwise.
 */
अटल अंतरभूत काष्ठा dma_fence_chain *
to_dma_fence_chain(काष्ठा dma_fence *fence)
अणु
	अगर (!fence || fence->ops != &dma_fence_chain_ops)
		वापस शून्य;

	वापस container_of(fence, काष्ठा dma_fence_chain, base);
पूर्ण

/**
 * dma_fence_chain_क्रम_each - iterate over all fences in chain
 * @iter: current fence
 * @head: starting poपूर्णांक
 *
 * Iterate over all fences in the chain. We keep a reference to the current
 * fence जबतक inside the loop which must be dropped when अवरोधing out.
 */
#घोषणा dma_fence_chain_क्रम_each(iter, head)	\
	क्रम (iter = dma_fence_get(head); iter; \
	     iter = dma_fence_chain_walk(iter))

काष्ठा dma_fence *dma_fence_chain_walk(काष्ठा dma_fence *fence);
पूर्णांक dma_fence_chain_find_seqno(काष्ठा dma_fence **pfence, uपूर्णांक64_t seqno);
व्योम dma_fence_chain_init(काष्ठा dma_fence_chain *chain,
			  काष्ठा dma_fence *prev,
			  काष्ठा dma_fence *fence,
			  uपूर्णांक64_t seqno);

#पूर्ण_अगर /* __LINUX_DMA_FENCE_CHAIN_H */
