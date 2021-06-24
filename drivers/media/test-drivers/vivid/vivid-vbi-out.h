<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-vbi-out.h - vbi output support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_VBI_OUT_H_
#घोषणा _VIVID_VBI_OUT_H_

व्योम vivid_sliced_vbi_out_process(काष्ठा vivid_dev *dev, काष्ठा vivid_buffer *buf);
पूर्णांक vidioc_g_fmt_vbi_out(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_s_fmt_vbi_out(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_g_fmt_sliced_vbi_out(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt);
पूर्णांक vidioc_try_fmt_sliced_vbi_out(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt);
पूर्णांक vidioc_s_fmt_sliced_vbi_out(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *fmt);

बाह्य स्थिर काष्ठा vb2_ops vivid_vbi_out_qops;

#पूर्ण_अगर
