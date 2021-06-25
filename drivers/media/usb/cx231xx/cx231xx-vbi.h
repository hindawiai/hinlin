<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
   cx231xx_vbi.h - driver क्रम Conexant Cx23100/101/102 USB video capture devices

   Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>
		Based on cx88 driver

 */

#अगर_अघोषित _CX231XX_VBI_H
#घोषणा _CX231XX_VBI_H

बाह्य काष्ठा vb2_ops cx231xx_vbi_qops;

#घोषणा   NTSC_VBI_START_LINE 10	/* line 10 - 21 */
#घोषणा   NTSC_VBI_END_LINE   21
#घोषणा   NTSC_VBI_LINES	  (NTSC_VBI_END_LINE-NTSC_VBI_START_LINE+1)

#घोषणा   PAL_VBI_START_LINE  6
#घोषणा   PAL_VBI_END_LINE    23
#घोषणा   PAL_VBI_LINES       (PAL_VBI_END_LINE-PAL_VBI_START_LINE+1)

#घोषणा   VBI_STRIDE            1440
#घोषणा   VBI_SAMPLES_PER_LINE  1440

#घोषणा   CX231XX_NUM_VBI_PACKETS       4
#घोषणा   CX231XX_NUM_VBI_BUFS          5

/* stream functions */
पूर्णांक cx231xx_init_vbi_isoc(काष्ठा cx231xx *dev, पूर्णांक max_packets,
			  पूर्णांक num_bufs, पूर्णांक max_pkt_size,
			  पूर्णांक (*bulk_copy) (काष्ठा cx231xx *dev,
					    काष्ठा urb *urb));

व्योम cx231xx_uninit_vbi_isoc(काष्ठा cx231xx *dev);

/* vbi data copy functions */
u32 cx231xx_get_vbi_line(काष्ठा cx231xx *dev, काष्ठा cx231xx_dmaqueue *dma_q,
			 u8 sav_eav, u8 *p_buffer, u32 buffer_size);

u32 cx231xx_copy_vbi_line(काष्ठा cx231xx *dev, काष्ठा cx231xx_dmaqueue *dma_q,
			  u8 *p_line, u32 length, पूर्णांक field_number);

व्योम cx231xx_reset_vbi_buffer(काष्ठा cx231xx *dev,
			      काष्ठा cx231xx_dmaqueue *dma_q);

पूर्णांक cx231xx_करो_vbi_copy(काष्ठा cx231xx *dev, काष्ठा cx231xx_dmaqueue *dma_q,
			u8 *p_buffer, u32 bytes_to_copy);

u8 cx231xx_is_vbi_buffer_करोne(काष्ठा cx231xx *dev,
			      काष्ठा cx231xx_dmaqueue *dma_q);

#पूर्ण_अगर
