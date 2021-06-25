<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    buffer queues.
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#अगर_अघोषित IVTV_QUEUE_H
#घोषणा IVTV_QUEUE_H

#घोषणा IVTV_DMA_UNMAPPED	((u32) -1)
#घोषणा SLICED_VBI_PIO 0

/* ivtv_buffer utility functions */

अटल अंतरभूत पूर्णांक ivtv_might_use_pio(काष्ठा ivtv_stream *s)
अणु
	वापस s->dma == PCI_DMA_NONE || (SLICED_VBI_PIO && s->type == IVTV_ENC_STREAM_TYPE_VBI);
पूर्ण

अटल अंतरभूत पूर्णांक ivtv_use_pio(काष्ठा ivtv_stream *s)
अणु
	काष्ठा ivtv *itv = s->itv;

	वापस s->dma == PCI_DMA_NONE ||
	    (SLICED_VBI_PIO && s->type == IVTV_ENC_STREAM_TYPE_VBI && itv->vbi.sliced_in->service_set);
पूर्ण

अटल अंतरभूत पूर्णांक ivtv_might_use_dma(काष्ठा ivtv_stream *s)
अणु
	वापस s->dma != PCI_DMA_NONE;
पूर्ण

अटल अंतरभूत पूर्णांक ivtv_use_dma(काष्ठा ivtv_stream *s)
अणु
	वापस !ivtv_use_pio(s);
पूर्ण

अटल अंतरभूत व्योम ivtv_buf_sync_क्रम_cpu(काष्ठा ivtv_stream *s, काष्ठा ivtv_buffer *buf)
अणु
	अगर (ivtv_use_dma(s))
		pci_dma_sync_single_क्रम_cpu(s->itv->pdev, buf->dma_handle,
				s->buf_size + 256, s->dma);
पूर्ण

अटल अंतरभूत व्योम ivtv_buf_sync_क्रम_device(काष्ठा ivtv_stream *s, काष्ठा ivtv_buffer *buf)
अणु
	अगर (ivtv_use_dma(s))
		pci_dma_sync_single_क्रम_device(s->itv->pdev, buf->dma_handle,
				s->buf_size + 256, s->dma);
पूर्ण

पूर्णांक ivtv_buf_copy_from_user(काष्ठा ivtv_stream *s, काष्ठा ivtv_buffer *buf, स्थिर अक्षर __user *src, पूर्णांक copybytes);
व्योम ivtv_buf_swap(काष्ठा ivtv_buffer *buf);

/* ivtv_queue utility functions */
व्योम ivtv_queue_init(काष्ठा ivtv_queue *q);
व्योम ivtv_enqueue(काष्ठा ivtv_stream *s, काष्ठा ivtv_buffer *buf, काष्ठा ivtv_queue *q);
काष्ठा ivtv_buffer *ivtv_dequeue(काष्ठा ivtv_stream *s, काष्ठा ivtv_queue *q);
पूर्णांक ivtv_queue_move(काष्ठा ivtv_stream *s, काष्ठा ivtv_queue *from, काष्ठा ivtv_queue *steal,
		    काष्ठा ivtv_queue *to, पूर्णांक needed_bytes);
व्योम ivtv_flush_queues(काष्ठा ivtv_stream *s);

/* ivtv_stream utility functions */
पूर्णांक ivtv_stream_alloc(काष्ठा ivtv_stream *s);
व्योम ivtv_stream_मुक्त(काष्ठा ivtv_stream *s);

अटल अंतरभूत व्योम ivtv_stream_sync_क्रम_cpu(काष्ठा ivtv_stream *s)
अणु
	अगर (ivtv_use_dma(s))
		pci_dma_sync_single_क्रम_cpu(s->itv->pdev, s->sg_handle,
			माप(काष्ठा ivtv_sg_element), PCI_DMA_TODEVICE);
पूर्ण

अटल अंतरभूत व्योम ivtv_stream_sync_क्रम_device(काष्ठा ivtv_stream *s)
अणु
	अगर (ivtv_use_dma(s))
		pci_dma_sync_single_क्रम_device(s->itv->pdev, s->sg_handle,
			माप(काष्ठा ivtv_sg_element), PCI_DMA_TODEVICE);
पूर्ण

#पूर्ण_अगर
