<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    init/start/stop/निकास stream functions
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#अगर_अघोषित IVTV_STREAMS_H
#घोषणा IVTV_STREAMS_H

पूर्णांक ivtv_streams_setup(काष्ठा ivtv *itv);
पूर्णांक ivtv_streams_रेजिस्टर(काष्ठा ivtv *itv);
व्योम ivtv_streams_cleanup(काष्ठा ivtv *itv);

/* Capture related */
पूर्णांक ivtv_start_v4l2_encode_stream(काष्ठा ivtv_stream *s);
पूर्णांक ivtv_stop_v4l2_encode_stream(काष्ठा ivtv_stream *s, पूर्णांक gop_end);
पूर्णांक ivtv_start_v4l2_decode_stream(काष्ठा ivtv_stream *s, पूर्णांक gop_offset);
पूर्णांक ivtv_stop_v4l2_decode_stream(काष्ठा ivtv_stream *s, पूर्णांक flags, u64 pts);

व्योम ivtv_stop_all_captures(काष्ठा ivtv *itv);
पूर्णांक ivtv_passthrough_mode(काष्ठा ivtv *itv, पूर्णांक enable);

#पूर्ण_अगर
