<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#अगर_अघोषित __MOCK_DMABUF_H__
#घोषणा __MOCK_DMABUF_H__

#समावेश <linux/dma-buf.h>

काष्ठा mock_dmabuf अणु
	पूर्णांक npages;
	काष्ठा page *pages[];
पूर्ण;

अटल अंतरभूत काष्ठा mock_dmabuf *to_mock(काष्ठा dma_buf *buf)
अणु
	वापस buf->priv;
पूर्ण

#पूर्ण_अगर /* !__MOCK_DMABUF_H__ */
