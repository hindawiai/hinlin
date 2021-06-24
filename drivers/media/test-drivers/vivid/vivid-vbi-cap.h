<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-vbi-cap.h - vbi capture support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_VBI_CAP_H_
#घोषणा _VIVID_VBI_CAP_H_

व्योम vivid_fill_समय_of_day_packet(u8 *packet);
व्योम vivid_raw_vbi_cap_process(काष्ठा vivid_dev *dev, काष्ठा vivid_buffer *buf);
व्योम vivid_sliced_vbi_cap_process(काष्ठा vivid_dev *dev, काष्ठा vivid_buffer *buf);
व्योम vivid_sliced_vbi_out_process(काष्ठा vivid_dev *dev, काष्ठा vivid_buffer *buf);
पूर्णांक vidioc_g_fmt_vbi_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_s_fmt_vbi_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_g_fmt_sliced_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt);
पूर्णांक vidioc_try_fmt_sliced_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt);
पूर्णांक vidioc_s_fmt_sliced_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt);
पूर्णांक vidioc_g_sliced_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_sliced_vbi_cap *cap);

व्योम vivid_fill_service_lines(काष्ठा v4l2_sliced_vbi_क्रमmat *vbi, u32 service_set);

बाह्य स्थिर काष्ठा vb2_ops vivid_vbi_cap_qops;

#पूर्ण_अगर
