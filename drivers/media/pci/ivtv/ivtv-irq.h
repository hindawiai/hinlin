<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    पूर्णांकerrupt handling
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#अगर_अघोषित IVTV_IRQ_H
#घोषणा IVTV_IRQ_H

#घोषणा IVTV_IRQ_ENC_START_CAP		BIT(31)
#घोषणा IVTV_IRQ_ENC_EOS		BIT(30)
#घोषणा IVTV_IRQ_ENC_VBI_CAP		BIT(29)
#घोषणा IVTV_IRQ_ENC_VIM_RST		BIT(28)
#घोषणा IVTV_IRQ_ENC_DMA_COMPLETE	BIT(27)
#घोषणा IVTV_IRQ_ENC_PIO_COMPLETE	BIT(25)
#घोषणा IVTV_IRQ_DEC_AUD_MODE_CHG	BIT(24)
#घोषणा IVTV_IRQ_DEC_DATA_REQ		BIT(22)
#घोषणा IVTV_IRQ_DEC_DMA_COMPLETE	BIT(20)
#घोषणा IVTV_IRQ_DEC_VBI_RE_INSERT	BIT(19)
#घोषणा IVTV_IRQ_DMA_ERR		BIT(18)
#घोषणा IVTV_IRQ_DMA_WRITE		BIT(17)
#घोषणा IVTV_IRQ_DMA_READ		BIT(16)
#घोषणा IVTV_IRQ_DEC_VSYNC		BIT(10)

/* IRQ Masks */
#घोषणा IVTV_IRQ_MASK_INIT (IVTV_IRQ_DMA_ERR|IVTV_IRQ_ENC_DMA_COMPLETE|\
		IVTV_IRQ_DMA_READ|IVTV_IRQ_ENC_PIO_COMPLETE)

#घोषणा IVTV_IRQ_MASK_CAPTURE (IVTV_IRQ_ENC_START_CAP | IVTV_IRQ_ENC_EOS)
#घोषणा IVTV_IRQ_MASK_DECODE  (IVTV_IRQ_DEC_DATA_REQ|IVTV_IRQ_DEC_AUD_MODE_CHG)

irqवापस_t ivtv_irq_handler(पूर्णांक irq, व्योम *dev_id);

व्योम ivtv_irq_work_handler(काष्ठा kthपढ़ो_work *work);
व्योम ivtv_dma_stream_dec_prepare(काष्ठा ivtv_stream *s, u32 offset, पूर्णांक lock);
व्योम ivtv_unfinished_dma(काष्ठा समयr_list *t);

#पूर्ण_अगर
