<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    ioctl प्रणाली call
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#अगर_अघोषित IVTV_IOCTL_H
#घोषणा IVTV_IOCTL_H

u16 ivtv_service2vbi(पूर्णांक type);
व्योम ivtv_expand_service_set(काष्ठा v4l2_sliced_vbi_क्रमmat *fmt, पूर्णांक is_pal);
u16 ivtv_get_service_set(काष्ठा v4l2_sliced_vbi_क्रमmat *fmt);
व्योम ivtv_set_osd_alpha(काष्ठा ivtv *itv);
पूर्णांक ivtv_set_speed(काष्ठा ivtv *itv, पूर्णांक speed);
व्योम ivtv_set_funcs(काष्ठा video_device *vdev);
व्योम ivtv_s_std_enc(काष्ठा ivtv *itv, v4l2_std_id std);
व्योम ivtv_s_std_dec(काष्ठा ivtv *itv, v4l2_std_id std);
पूर्णांक ivtv_s_frequency(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_frequency *vf);
पूर्णांक ivtv_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक inp);

#पूर्ण_अगर
