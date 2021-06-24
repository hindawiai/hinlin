<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  cx18 init/start/stop/निकास stream functions
 *
 *  Derived from ivtv-streams.h
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

u32 cx18_find_handle(काष्ठा cx18 *cx);
काष्ठा cx18_stream *cx18_handle_to_stream(काष्ठा cx18 *cx, u32 handle);
पूर्णांक cx18_streams_setup(काष्ठा cx18 *cx);
पूर्णांक cx18_streams_रेजिस्टर(काष्ठा cx18 *cx);
व्योम cx18_streams_cleanup(काष्ठा cx18 *cx, पूर्णांक unरेजिस्टर);

#घोषणा CX18_ENC_STREAM_TYPE_IDX_FW_MDL_MIN (3)
व्योम cx18_stream_rotate_idx_mdls(काष्ठा cx18 *cx);

अटल अंतरभूत bool cx18_stream_enabled(काष्ठा cx18_stream *s)
अणु
	वापस s->video_dev.v4l2_dev ||
	       (s->dvb && s->dvb->enabled) ||
	       (s->type == CX18_ENC_STREAM_TYPE_IDX &&
		s->cx->stream_buffers[CX18_ENC_STREAM_TYPE_IDX] != 0);
पूर्ण

/* Related to submission of mdls to firmware */
अटल अंतरभूत व्योम cx18_stream_load_fw_queue(काष्ठा cx18_stream *s)
अणु
	schedule_work(&s->out_work_order);
पूर्ण

अटल अंतरभूत व्योम cx18_stream_put_mdl_fw(काष्ठा cx18_stream *s,
					  काष्ठा cx18_mdl *mdl)
अणु
	/* Put mdl on q_मुक्त; the out work handler will move mdl(s) to q_busy */
	cx18_enqueue(s, mdl, &s->q_मुक्त);
	cx18_stream_load_fw_queue(s);
पूर्ण

व्योम cx18_out_work_handler(काष्ठा work_काष्ठा *work);

/* Capture related */
पूर्णांक cx18_start_v4l2_encode_stream(काष्ठा cx18_stream *s);
पूर्णांक cx18_stop_v4l2_encode_stream(काष्ठा cx18_stream *s, पूर्णांक gop_end);

व्योम cx18_stop_all_captures(काष्ठा cx18 *cx);
