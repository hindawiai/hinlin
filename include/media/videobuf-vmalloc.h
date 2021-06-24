<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * helper functions क्रम vदो_स्मृति capture buffers
 *
 * The functions expect the hardware being able to scatter gather
 * (i.e. the buffers are not linear in physical memory, but fragmented
 * पूर्णांकo PAGE_SIZE chunks).  They also assume the driver करोes not need
 * to touch the video data.
 *
 * (c) 2007 Mauro Carvalho Chehab, <mchehab@kernel.org>
 */
#अगर_अघोषित _VIDEOBUF_VMALLOC_H
#घोषणा _VIDEOBUF_VMALLOC_H

#समावेश <media/videobuf-core.h>

/* --------------------------------------------------------------------- */

काष्ठा videobuf_vदो_स्मृति_memory अणु
	u32                 magic;

	व्योम                *vaddr;

	/* remap_vदो_स्मृति_range seems to need to run
	 * after mmap() on some हालs */
	काष्ठा vm_area_काष्ठा *vma;
पूर्ण;

व्योम videobuf_queue_vदो_स्मृति_init(काष्ठा videobuf_queue *q,
			 स्थिर काष्ठा videobuf_queue_ops *ops,
			 काष्ठा device *dev,
			 spinlock_t *irqlock,
			 क्रमागत v4l2_buf_type type,
			 क्रमागत v4l2_field field,
			 अचिन्हित पूर्णांक msize,
			 व्योम *priv,
			 काष्ठा mutex *ext_lock);

व्योम *videobuf_to_vदो_स्मृति(काष्ठा videobuf_buffer *buf);

व्योम videobuf_vदो_स्मृति_मुक्त(काष्ठा videobuf_buffer *buf);

#पूर्ण_अगर
