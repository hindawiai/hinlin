<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-vid-common.h - common video support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_VID_COMMON_H_
#घोषणा _VIVID_VID_COMMON_H_

प्रकार पूर्णांक (*fmtfunc)(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);

/*
 * Conversion function that converts a single-planar क्रमmat to a
 * single-plane multiplanar क्रमmat.
 */
व्योम fmt_sp2mp(स्थिर काष्ठा v4l2_क्रमmat *sp_fmt, काष्ठा v4l2_क्रमmat *mp_fmt);
पूर्णांक fmt_sp2mp_func(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_क्रमmat *f, fmtfunc func);

बाह्य स्थिर काष्ठा v4l2_dv_timings_cap vivid_dv_timings_cap;

स्थिर काष्ठा vivid_fmt *vivid_get_क्रमmat(काष्ठा vivid_dev *dev, u32 pixelक्रमmat);

bool vivid_vid_can_loop(काष्ठा vivid_dev *dev);
व्योम vivid_send_source_change(काष्ठा vivid_dev *dev, अचिन्हित type);

पूर्णांक vivid_vid_adjust_sel(अचिन्हित flags, काष्ठा v4l2_rect *r);

पूर्णांक vivid_क्रमागत_fmt_vid(काष्ठा file *file, व्योम  *priv, काष्ठा v4l2_fmtdesc *f);
पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *id);
पूर्णांक vidioc_g_dv_timings(काष्ठा file *file, व्योम *_fh, काष्ठा v4l2_dv_timings *timings);
पूर्णांक vidioc_क्रमागत_dv_timings(काष्ठा file *file, व्योम *_fh, काष्ठा v4l2_क्रमागत_dv_timings *timings);
पूर्णांक vidioc_dv_timings_cap(काष्ठा file *file, व्योम *_fh, काष्ठा v4l2_dv_timings_cap *cap);
पूर्णांक vidioc_g_edid(काष्ठा file *file, व्योम *_fh, काष्ठा v4l2_edid *edid);
पूर्णांक vidioc_subscribe_event(काष्ठा v4l2_fh *fh, स्थिर काष्ठा v4l2_event_subscription *sub);

#पूर्ण_अगर
