<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    yuv support

    Copyright (C) 2007  Ian Armstrong <ian@iarmst.demon.co.uk>

 */

#अगर_अघोषित IVTV_YUV_H
#घोषणा IVTV_YUV_H

#घोषणा IVTV_YUV_BUFFER_UV_OFFSET 0x65400	/* Offset to UV Buffer */

/* Offset to filter table in firmware */
#घोषणा IVTV_YUV_HORIZONTAL_FILTER_OFFSET 0x025d8
#घोषणा IVTV_YUV_VERTICAL_FILTER_OFFSET 0x03358

#घोषणा IVTV_YUV_UPDATE_HORIZONTAL  0x01
#घोषणा IVTV_YUV_UPDATE_VERTICAL    0x02
#घोषणा IVTV_YUV_UPDATE_INVALID     0x04

बाह्य स्थिर u32 yuv_offset[IVTV_YUV_BUFFERS];

पूर्णांक ivtv_yuv_filter_check(काष्ठा ivtv *itv);
व्योम ivtv_yuv_setup_stream_frame(काष्ठा ivtv *itv);
पूर्णांक ivtv_yuv_udma_stream_frame(काष्ठा ivtv *itv, व्योम __user *src);
व्योम ivtv_yuv_frame_complete(काष्ठा ivtv *itv);
पूर्णांक ivtv_yuv_prep_frame(काष्ठा ivtv *itv, काष्ठा ivtv_dma_frame *args);
व्योम ivtv_yuv_बंद(काष्ठा ivtv *itv);
व्योम ivtv_yuv_work_handler(काष्ठा ivtv *itv);

#पूर्ण_अगर
