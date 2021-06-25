<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    file operation functions
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#अगर_अघोषित IVTV_खाताOPS_H
#घोषणा IVTV_खाताOPS_H

/* Testing/Debugging */
पूर्णांक ivtv_v4l2_खोलो(काष्ठा file *filp);
sमाप_प्रकार ivtv_v4l2_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
		      loff_t * pos);
sमाप_प्रकार ivtv_v4l2_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf, माप_प्रकार count,
		       loff_t * pos);
पूर्णांक ivtv_v4l2_बंद(काष्ठा file *filp);
__poll_t ivtv_v4l2_enc_poll(काष्ठा file *filp, poll_table * रुको);
__poll_t ivtv_v4l2_dec_poll(काष्ठा file *filp, poll_table * रुको);
पूर्णांक ivtv_start_capture(काष्ठा ivtv_खोलो_id *id);
व्योम ivtv_stop_capture(काष्ठा ivtv_खोलो_id *id, पूर्णांक gop_end);
पूर्णांक ivtv_start_decoding(काष्ठा ivtv_खोलो_id *id, पूर्णांक speed);
व्योम ivtv_mute(काष्ठा ivtv *itv);
व्योम ivtv_unmute(काष्ठा ivtv *itv);

/* Utilities */
/* Shared with ivtv-alsa module */
पूर्णांक ivtv_claim_stream(काष्ठा ivtv_खोलो_id *id, पूर्णांक type);
व्योम ivtv_release_stream(काष्ठा ivtv_stream *s);

#पूर्ण_अगर
