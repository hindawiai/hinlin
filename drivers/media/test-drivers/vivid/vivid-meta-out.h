<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-meta-out.h - meta output support functions.
 */
#अगर_अघोषित _VIVID_META_OUT_H_
#घोषणा _VIVID_META_OUT_H_

काष्ठा vivid_meta_out_buf अणु
	u16	brightness;
	u16	contrast;
	u16	saturation;
	s16	hue;
पूर्ण;

व्योम vivid_meta_out_process(काष्ठा vivid_dev *dev, काष्ठा vivid_buffer *buf);
पूर्णांक vidioc_क्रमागत_fmt_meta_out(काष्ठा file *file, व्योम  *priv,
			     काष्ठा v4l2_fmtdesc *f);
पूर्णांक vidioc_g_fmt_meta_out(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_s_fmt_meta_out(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_क्रमmat *f);

बाह्य स्थिर काष्ठा vb2_ops vivid_meta_out_qops;

#पूर्ण_अगर
