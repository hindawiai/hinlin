<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * helper functions क्रम SG DMA video4linux capture buffers
 *
 * The functions expect the hardware being able to scatter gather
 * (i.e. the buffers are not linear in physical memory, but fragmented
 * पूर्णांकo PAGE_SIZE chunks).  They also assume the driver करोes not need
 * to touch the video data.
 *
 * (c) 2007 Mauro Carvalho Chehab, <mchehab@kernel.org>
 *
 * Highly based on video-buf written originally by:
 * (c) 2001,02 Gerd Knorr <kraxel@bytesex.org>
 * (c) 2006 Mauro Carvalho Chehab, <mchehab@kernel.org>
 * (c) 2006 Ted Walther and John Sokol
 */
#अगर_अघोषित _VIDEOBUF_DMA_SG_H
#घोषणा _VIDEOBUF_DMA_SG_H

#समावेश <media/videobuf-core.h>

/* --------------------------------------------------------------------- */

/*
 * A small set of helper functions to manage buffers (both userland
 * and kernel) क्रम DMA.
 *
 * videobuf_dma_init_*()
 *	creates a buffer.  The userland version takes a userspace
 *	poपूर्णांकer + length.  The kernel version just wants the size and
 *	करोes memory allocation too using vदो_स्मृति_32().
 *
 * videobuf_dma_*()
 *	see Documentation/core-api/dma-api-howto.rst, these functions to
 *	basically the same.  The map function करोes also build a
 *	scatterlist क्रम the buffer (and unmap मुक्तs it ...)
 *
 * videobuf_dma_मुक्त()
 *	no comment ...
 *
 */

काष्ठा videobuf_dmabuf अणु
	u32                 magic;

	/* क्रम userland buffer */
	पूर्णांक                 offset;
	माप_प्रकार		    size;
	काष्ठा page         **pages;

	/* क्रम kernel buffers */
	व्योम                *vaddr;
	काष्ठा page         **vaddr_pages;
	dma_addr_t          *dma_addr;
	काष्ठा device       *dev;

	/* क्रम overlay buffers (pci-pci dma) */
	dma_addr_t          bus_addr;

	/* common */
	काष्ठा scatterlist  *sglist;
	पूर्णांक                 sglen;
	अचिन्हित दीर्घ       nr_pages;
	पूर्णांक                 direction;
पूर्ण;

काष्ठा videobuf_dma_sg_memory अणु
	u32                 magic;

	/* क्रम mmap'ed buffers */
	काष्ठा videobuf_dmabuf  dma;
पूर्ण;

/*
 * Scatter-gather DMA buffer API.
 *
 * These functions provide a simple way to create a page list and a
 * scatter-gather list from a kernel, userspace of physical address and map the
 * memory क्रम DMA operation.
 *
 * Despite the name, this is totally unrelated to videobuf, except that
 * videobuf-dma-sg uses the same API पूर्णांकernally.
 */
पूर्णांक videobuf_dma_मुक्त(काष्ठा videobuf_dmabuf *dma);

पूर्णांक videobuf_dma_unmap(काष्ठा device *dev, काष्ठा videobuf_dmabuf *dma);
काष्ठा videobuf_dmabuf *videobuf_to_dma(काष्ठा videobuf_buffer *buf);

व्योम *videobuf_sg_alloc(माप_प्रकार size);

व्योम videobuf_queue_sg_init(काष्ठा videobuf_queue *q,
			 स्थिर काष्ठा videobuf_queue_ops *ops,
			 काष्ठा device *dev,
			 spinlock_t *irqlock,
			 क्रमागत v4l2_buf_type type,
			 क्रमागत v4l2_field field,
			 अचिन्हित पूर्णांक msize,
			 व्योम *priv,
			 काष्ठा mutex *ext_lock);

#पूर्ण_अगर /* _VIDEOBUF_DMA_SG_H */

