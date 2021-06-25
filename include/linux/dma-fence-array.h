<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * fence-array: aggregates fence to be रुकोed together
 *
 * Copyright (C) 2016 Collabora Ltd
 * Copyright (C) 2016 Advanced Micro Devices, Inc.
 * Authors:
 *	Gustavo Paकरोvan <gustavo@paकरोvan.org>
 *	Christian Kथघnig <christian.koenig@amd.com>
 */

#अगर_अघोषित __LINUX_DMA_FENCE_ARRAY_H
#घोषणा __LINUX_DMA_FENCE_ARRAY_H

#समावेश <linux/dma-fence.h>
#समावेश <linux/irq_work.h>

/**
 * काष्ठा dma_fence_array_cb - callback helper क्रम fence array
 * @cb: fence callback काष्ठाure क्रम संकेतing
 * @array: reference to the parent fence array object
 */
काष्ठा dma_fence_array_cb अणु
	काष्ठा dma_fence_cb cb;
	काष्ठा dma_fence_array *array;
पूर्ण;

/**
 * काष्ठा dma_fence_array - fence to represent an array of fences
 * @base: fence base class
 * @lock: spinlock क्रम fence handling
 * @num_fences: number of fences in the array
 * @num_pending: fences in the array still pending
 * @fences: array of the fences
 * @work: पूर्णांकernal irq_work function
 */
काष्ठा dma_fence_array अणु
	काष्ठा dma_fence base;

	spinlock_t lock;
	अचिन्हित num_fences;
	atomic_t num_pending;
	काष्ठा dma_fence **fences;

	काष्ठा irq_work work;
पूर्ण;

बाह्य स्थिर काष्ठा dma_fence_ops dma_fence_array_ops;

/**
 * dma_fence_is_array - check अगर a fence is from the array subsclass
 * @fence: fence to test
 *
 * Return true अगर it is a dma_fence_array and false otherwise.
 */
अटल अंतरभूत bool dma_fence_is_array(काष्ठा dma_fence *fence)
अणु
	वापस fence->ops == &dma_fence_array_ops;
पूर्ण

/**
 * to_dma_fence_array - cast a fence to a dma_fence_array
 * @fence: fence to cast to a dma_fence_array
 *
 * Returns शून्य अगर the fence is not a dma_fence_array,
 * or the dma_fence_array otherwise.
 */
अटल अंतरभूत काष्ठा dma_fence_array *
to_dma_fence_array(काष्ठा dma_fence *fence)
अणु
	अगर (fence->ops != &dma_fence_array_ops)
		वापस शून्य;

	वापस container_of(fence, काष्ठा dma_fence_array, base);
पूर्ण

काष्ठा dma_fence_array *dma_fence_array_create(पूर्णांक num_fences,
					       काष्ठा dma_fence **fences,
					       u64 context, अचिन्हित seqno,
					       bool संकेत_on_any);

bool dma_fence_match_context(काष्ठा dma_fence *fence, u64 context);

#पूर्ण_अगर /* __LINUX_DMA_FENCE_ARRAY_H */
