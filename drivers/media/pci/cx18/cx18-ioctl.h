<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  cx18 ioctl प्रणाली call
 *
 *  Derived from ivtv-ioctl.h
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

u16 cx18_service2vbi(पूर्णांक type);
व्योम cx18_expand_service_set(काष्ठा v4l2_sliced_vbi_क्रमmat *fmt, पूर्णांक is_pal);
u16 cx18_get_service_set(काष्ठा v4l2_sliced_vbi_क्रमmat *fmt);
व्योम cx18_set_funcs(काष्ठा video_device *vdev);
पूर्णांक cx18_s_std(काष्ठा file *file, व्योम *fh, v4l2_std_id std);
पूर्णांक cx18_s_frequency(काष्ठा file *file, व्योम *fh, स्थिर काष्ठा v4l2_frequency *vf);
पूर्णांक cx18_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक inp);
