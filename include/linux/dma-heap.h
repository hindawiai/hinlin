<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * DMABUF Heaps Allocation Infraकाष्ठाure
 *
 * Copyright (C) 2011 Google, Inc.
 * Copyright (C) 2019 Linaro Ltd.
 */

#अगर_अघोषित _DMA_HEAPS_H
#घोषणा _DMA_HEAPS_H

#समावेश <linux/cdev.h>
#समावेश <linux/types.h>

काष्ठा dma_heap;

/**
 * काष्ठा dma_heap_ops - ops to operate on a given heap
 * @allocate:		allocate dmabuf and वापस काष्ठा dma_buf ptr
 *
 * allocate वापसs dmabuf on success, ERR_PTR(-त्रुटि_सं) on error.
 */
काष्ठा dma_heap_ops अणु
	काष्ठा dma_buf *(*allocate)(काष्ठा dma_heap *heap,
				    अचिन्हित दीर्घ len,
				    अचिन्हित दीर्घ fd_flags,
				    अचिन्हित दीर्घ heap_flags);
पूर्ण;

/**
 * काष्ठा dma_heap_export_info - inक्रमmation needed to export a new dmabuf heap
 * @name:	used क्रम debugging/device-node name
 * @ops:	ops काष्ठा क्रम this heap
 * @priv:	heap exporter निजी data
 *
 * Inक्रमmation needed to export a new dmabuf heap.
 */
काष्ठा dma_heap_export_info अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा dma_heap_ops *ops;
	व्योम *priv;
पूर्ण;

/**
 * dma_heap_get_drvdata() - get per-heap driver data
 * @heap: DMA-Heap to retrieve निजी data क्रम
 *
 * Returns:
 * The per-heap data क्रम the heap.
 */
व्योम *dma_heap_get_drvdata(काष्ठा dma_heap *heap);

/**
 * dma_heap_get_name() - get heap name
 * @heap: DMA-Heap to retrieve निजी data क्रम
 *
 * Returns:
 * The अक्षर* क्रम the heap name.
 */
स्थिर अक्षर *dma_heap_get_name(काष्ठा dma_heap *heap);

/**
 * dma_heap_add - adds a heap to dmabuf heaps
 * @exp_info:		inक्रमmation needed to रेजिस्टर this heap
 */
काष्ठा dma_heap *dma_heap_add(स्थिर काष्ठा dma_heap_export_info *exp_info);

#पूर्ण_अगर /* _DMA_HEAPS_H */
