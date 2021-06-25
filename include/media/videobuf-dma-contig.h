<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * helper functions क्रम physically contiguous capture buffers
 *
 * The functions support hardware lacking scatter gather support
 * (i.e. the buffers must be linear in physical memory)
 *
 * Copyright (c) 2008 Magnus Damm
 */
#अगर_अघोषित _VIDEOBUF_DMA_CONTIG_H
#घोषणा _VIDEOBUF_DMA_CONTIG_H

#समावेश <linux/dma-mapping.h>
#समावेश <media/videobuf-core.h>

व्योम videobuf_queue_dma_contig_init(काष्ठा videobuf_queue *q,
				    स्थिर काष्ठा videobuf_queue_ops *ops,
				    काष्ठा device *dev,
				    spinlock_t *irqlock,
				    क्रमागत v4l2_buf_type type,
				    क्रमागत v4l2_field field,
				    अचिन्हित पूर्णांक msize,
				    व्योम *priv,
				    काष्ठा mutex *ext_lock);

dma_addr_t videobuf_to_dma_contig(काष्ठा videobuf_buffer *buf);
व्योम videobuf_dma_contig_मुक्त(काष्ठा videobuf_queue *q,
			      काष्ठा videobuf_buffer *buf);

#पूर्ण_अगर /* _VIDEOBUF_DMA_CONTIG_H */
