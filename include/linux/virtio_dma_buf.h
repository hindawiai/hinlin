<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * dma-bufs क्रम virtio exported objects
 *
 * Copyright (C) 2020 Google, Inc.
 */

#अगर_अघोषित _LINUX_VIRTIO_DMA_BUF_H
#घोषणा _LINUX_VIRTIO_DMA_BUF_H

#समावेश <linux/dma-buf.h>
#समावेश <linux/uuid.h>
#समावेश <linux/virtपन.स>

/**
 * काष्ठा virtio_dma_buf_ops - operations possible on exported object dma-buf
 * @ops: the base dma_buf_ops. ops.attach MUST be virtio_dma_buf_attach.
 * @device_attach: [optional] callback invoked by virtio_dma_buf_attach during
 *		   all attach operations.
 * @get_uid: [required] callback to get the uuid of the exported object.
 */
काष्ठा virtio_dma_buf_ops अणु
	काष्ठा dma_buf_ops ops;
	पूर्णांक (*device_attach)(काष्ठा dma_buf *dma_buf,
			     काष्ठा dma_buf_attachment *attach);
	पूर्णांक (*get_uuid)(काष्ठा dma_buf *dma_buf, uuid_t *uuid);
पूर्ण;

पूर्णांक virtio_dma_buf_attach(काष्ठा dma_buf *dma_buf,
			  काष्ठा dma_buf_attachment *attach);

काष्ठा dma_buf *virtio_dma_buf_export
	(स्थिर काष्ठा dma_buf_export_info *exp_info);
bool is_virtio_dma_buf(काष्ठा dma_buf *dma_buf);
पूर्णांक virtio_dma_buf_get_uuid(काष्ठा dma_buf *dma_buf, uuid_t *uuid);

#पूर्ण_अगर /* _LINUX_VIRTIO_DMA_BUF_H */
