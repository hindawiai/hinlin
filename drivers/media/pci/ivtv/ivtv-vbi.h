<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Vertical Blank Interval support functions
    Copyright (C) 2004-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#अगर_अघोषित IVTV_VBI_H
#घोषणा IVTV_VBI_H

sमाप_प्रकार
ivtv_ग_लिखो_vbi_from_user(काष्ठा ivtv *itv,
			 स्थिर काष्ठा v4l2_sliced_vbi_data __user *sliced,
			 माप_प्रकार count);
व्योम ivtv_process_vbi_data(काष्ठा ivtv *itv, काष्ठा ivtv_buffer *buf,
			   u64 pts_stamp, पूर्णांक streamtype);
पूर्णांक ivtv_used_line(काष्ठा ivtv *itv, पूर्णांक line, पूर्णांक field);
व्योम ivtv_disable_cc(काष्ठा ivtv *itv);
व्योम ivtv_set_vbi(अचिन्हित दीर्घ arg);
व्योम ivtv_vbi_work_handler(काष्ठा ivtv *itv);

#पूर्ण_अगर
