<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-meta-cap.h - meta capture support functions.
 */
#अगर_अघोषित _VIVID_META_CAP_H_
#घोषणा _VIVID_META_CAP_H_

#घोषणा VIVID_META_CLOCK_UNIT	10 /* 100 MHz */

काष्ठा vivid_uvc_meta_buf अणु
	__u64 ns;
	__u16 sof;
	__u8 length;
	__u8 flags;
	__u8 buf[10]; /* PTS(4)+STC(4)+SOF(2) */
पूर्ण __packed;

व्योम vivid_meta_cap_fillbuff(काष्ठा vivid_dev *dev,
			     काष्ठा vivid_buffer *buf, u64 soe);

पूर्णांक vidioc_क्रमागत_fmt_meta_cap(काष्ठा file *file, व्योम  *priv,
			     काष्ठा v4l2_fmtdesc *f);

पूर्णांक vidioc_g_fmt_meta_cap(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_क्रमmat *f);

बाह्य स्थिर काष्ठा vb2_ops vivid_meta_cap_qops;

#पूर्ण_अगर
