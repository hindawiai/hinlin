<शैली गुरु>
/*
 * videobuf2-dma-sg.h - DMA scatter/gather memory allocator क्रम videobuf2
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित _MEDIA_VIDEOBUF2_DMA_SG_H
#घोषणा _MEDIA_VIDEOBUF2_DMA_SG_H

#समावेश <media/videobuf2-v4l2.h>

अटल अंतरभूत काष्ठा sg_table *vb2_dma_sg_plane_desc(
		काष्ठा vb2_buffer *vb, अचिन्हित पूर्णांक plane_no)
अणु
	वापस (काष्ठा sg_table *)vb2_plane_cookie(vb, plane_no);
पूर्ण

बाह्य स्थिर काष्ठा vb2_mem_ops vb2_dma_sg_memops;

#पूर्ण_अगर
