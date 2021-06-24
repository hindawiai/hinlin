<शैली गुरु>
/*
 * videobuf2-dma-contig.h - DMA contig memory allocator क्रम videobuf2
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित _MEDIA_VIDEOBUF2_DMA_CONTIG_H
#घोषणा _MEDIA_VIDEOBUF2_DMA_CONTIG_H

#समावेश <media/videobuf2-v4l2.h>
#समावेश <linux/dma-mapping.h>

अटल अंतरभूत dma_addr_t
vb2_dma_contig_plane_dma_addr(काष्ठा vb2_buffer *vb, अचिन्हित पूर्णांक plane_no)
अणु
	dma_addr_t *addr = vb2_plane_cookie(vb, plane_no);

	वापस *addr;
पूर्ण

पूर्णांक vb2_dma_contig_set_max_seg_size(काष्ठा device *dev, अचिन्हित पूर्णांक size);
अटल अंतरभूत व्योम vb2_dma_contig_clear_max_seg_size(काष्ठा device *dev) अणु पूर्ण

बाह्य स्थिर काष्ठा vb2_mem_ops vb2_dma_contig_memops;

#पूर्ण_अगर
