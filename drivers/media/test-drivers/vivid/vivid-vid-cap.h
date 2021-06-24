<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-vid-cap.h - video capture support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_VID_CAP_H_
#घोषणा _VIVID_VID_CAP_H_

व्योम vivid_update_quality(काष्ठा vivid_dev *dev);
व्योम vivid_update_क्रमmat_cap(काष्ठा vivid_dev *dev, bool keep_controls);
क्रमागत tpg_video_aspect vivid_get_video_aspect(स्थिर काष्ठा vivid_dev *dev);

बाह्य स्थिर v4l2_std_id vivid_standard[];
बाह्य स्थिर अक्षर * स्थिर vivid_ctrl_standard_strings[];

बाह्य स्थिर काष्ठा vb2_ops vivid_vid_cap_qops;

पूर्णांक vivid_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vivid_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vivid_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_g_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_try_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_s_fmt_vid_cap_mplane(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vivid_vid_cap_g_selection(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_selection *sel);
पूर्णांक vivid_vid_cap_s_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *s);
पूर्णांक vivid_vid_cap_g_pixelaspect(काष्ठा file *file, व्योम *priv, पूर्णांक type, काष्ठा v4l2_fract *f);
पूर्णांक vidioc_क्रमागत_fmt_vid_overlay(काष्ठा file *file, व्योम  *priv, काष्ठा v4l2_fmtdesc *f);
पूर्णांक vidioc_g_fmt_vid_overlay(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_try_fmt_vid_overlay(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_s_fmt_vid_overlay(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vivid_vid_cap_overlay(काष्ठा file *file, व्योम *fh, अचिन्हित i);
पूर्णांक vivid_vid_cap_g_fbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_framebuffer *a);
पूर्णांक vivid_vid_cap_s_fbuf(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_framebuffer *a);
पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_input *inp);
पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित *i);
पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित i);
पूर्णांक vidioc_क्रमागतaudio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *vin);
पूर्णांक vidioc_g_audio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *vin);
पूर्णांक vidioc_s_audio(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_audio *vin);
पूर्णांक vivid_video_g_frequency(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_frequency *vf);
पूर्णांक vivid_video_s_frequency(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_frequency *vf);
पूर्णांक vivid_video_s_tuner(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_tuner *vt);
पूर्णांक vivid_video_g_tuner(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_tuner *vt);
पूर्णांक vidioc_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *id);
पूर्णांक vivid_vid_cap_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id);
पूर्णांक vivid_vid_cap_s_dv_timings(काष्ठा file *file, व्योम *_fh, काष्ठा v4l2_dv_timings *timings);
पूर्णांक vidioc_query_dv_timings(काष्ठा file *file, व्योम *_fh, काष्ठा v4l2_dv_timings *timings);
पूर्णांक vidioc_s_edid(काष्ठा file *file, व्योम *_fh, काष्ठा v4l2_edid *edid);
पूर्णांक vidioc_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_frmsizeक्रमागत *fsize);
पूर्णांक vidioc_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_frmivalक्रमागत *fival);
पूर्णांक vivid_vid_cap_g_parm(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_streamparm *parm);
पूर्णांक vivid_vid_cap_s_parm(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_streamparm *parm);

#पूर्ण_अगर
