<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-sdr-cap.h - software defined radio support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_SDR_CAP_H_
#घोषणा _VIVID_SDR_CAP_H_

पूर्णांक vivid_sdr_क्रमागत_freq_bands(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_frequency_band *band);
पूर्णांक vivid_sdr_g_frequency(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_frequency *vf);
पूर्णांक vivid_sdr_s_frequency(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_frequency *vf);
पूर्णांक vivid_sdr_g_tuner(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_tuner *vt);
पूर्णांक vivid_sdr_s_tuner(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_tuner *vt);
पूर्णांक vidioc_क्रमागत_fmt_sdr_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *f);
पूर्णांक vidioc_g_fmt_sdr_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_s_fmt_sdr_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_try_fmt_sdr_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f);
व्योम vivid_sdr_cap_process(काष्ठा vivid_dev *dev, काष्ठा vivid_buffer *buf);

बाह्य स्थिर काष्ठा vb2_ops vivid_sdr_cap_qops;

#पूर्ण_अगर
