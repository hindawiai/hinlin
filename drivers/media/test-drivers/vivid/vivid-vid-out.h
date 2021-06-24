<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-vid-out.h - video output support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _VIVID_VID_OUT_H_
#घोषणा _VIVID_VID_OUT_H_

बाह्य स्थिर काष्ठा vb2_ops vivid_vid_out_qops;

व्योम vivid_update_क्रमmat_out(काष्ठा vivid_dev *dev);

पूर्णांक vivid_g_fmt_vid_out(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vivid_try_fmt_vid_out(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vivid_s_fmt_vid_out(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_g_fmt_vid_out_mplane(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_try_fmt_vid_out_mplane(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_s_fmt_vid_out_mplane(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_g_fmt_vid_out(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_try_fmt_vid_out(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_s_fmt_vid_out(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vivid_vid_out_g_selection(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_selection *sel);
पूर्णांक vivid_vid_out_s_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *s);
पूर्णांक vivid_vid_out_g_pixelaspect(काष्ठा file *file, व्योम *priv, पूर्णांक type, काष्ठा v4l2_fract *f);
पूर्णांक vidioc_क्रमागत_fmt_vid_out_overlay(काष्ठा file *file, व्योम  *priv, काष्ठा v4l2_fmtdesc *f);
पूर्णांक vidioc_g_fmt_vid_out_overlay(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_try_fmt_vid_out_overlay(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vidioc_s_fmt_vid_out_overlay(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vivid_vid_out_overlay(काष्ठा file *file, व्योम *fh, अचिन्हित i);
पूर्णांक vivid_vid_out_g_fbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_framebuffer *a);
पूर्णांक vivid_vid_out_s_fbuf(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_framebuffer *a);
पूर्णांक vidioc_क्रमागत_output(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_output *out);
पूर्णांक vidioc_g_output(काष्ठा file *file, व्योम *priv, अचिन्हित *i);
पूर्णांक vidioc_s_output(काष्ठा file *file, व्योम *priv, अचिन्हित i);
पूर्णांक vidioc_क्रमागतauकरोut(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audioout *vout);
पूर्णांक vidioc_g_auकरोut(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audioout *vout);
पूर्णांक vidioc_s_auकरोut(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_audioout *vout);
पूर्णांक vivid_vid_out_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id);
पूर्णांक vivid_vid_out_s_dv_timings(काष्ठा file *file, व्योम *_fh, काष्ठा v4l2_dv_timings *timings);
पूर्णांक vivid_vid_out_g_parm(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_streamparm *parm);

#पूर्ण_अगर
