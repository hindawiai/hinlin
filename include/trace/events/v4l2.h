<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM v4l2

#अगर !defined(_TRACE_V4L2_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_V4L2_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <media/videobuf2-v4l2.h>

/* Enums require being exported to userspace, क्रम user tool parsing */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	TRACE_DEFINE_ENUM(a);
#घोषणा EMe(a, b)	TRACE_DEFINE_ENUM(a);

#घोषणा show_type(type)							\
	__prपूर्णांक_symbolic(type, SHOW_TYPE)

#घोषणा SHOW_TYPE							\
	EM( V4L2_BUF_TYPE_VIDEO_CAPTURE,	"VIDEO_CAPTURE" )	\
	EM( V4L2_BUF_TYPE_VIDEO_OUTPUT,		"VIDEO_OUTPUT" )	\
	EM( V4L2_BUF_TYPE_VIDEO_OVERLAY,	"VIDEO_OVERLAY" )	\
	EM( V4L2_BUF_TYPE_VBI_CAPTURE,		"VBI_CAPTURE" )		\
	EM( V4L2_BUF_TYPE_VBI_OUTPUT,		"VBI_OUTPUT" )		\
	EM( V4L2_BUF_TYPE_SLICED_VBI_CAPTURE,   "SLICED_VBI_CAPTURE" )	\
	EM( V4L2_BUF_TYPE_SLICED_VBI_OUTPUT,    "SLICED_VBI_OUTPUT" )	\
	EM( V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY, "VIDEO_OUTPUT_OVERLAY" ) \
	EM( V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE, "VIDEO_CAPTURE_MPLANE" ) \
	EM( V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE,  "VIDEO_OUTPUT_MPLANE" )	\
	EM( V4L2_BUF_TYPE_SDR_CAPTURE,          "SDR_CAPTURE" )		\
	EM( V4L2_BUF_TYPE_SDR_OUTPUT,           "SDR_OUTPUT" )		\
	EM( V4L2_BUF_TYPE_META_CAPTURE,		"META_CAPTURE" )	\
	EMe(V4L2_BUF_TYPE_PRIVATE,		"PRIVATE" )

SHOW_TYPE

#घोषणा show_field(field)						\
	__prपूर्णांक_symbolic(field, SHOW_FIELD)

#घोषणा SHOW_FIELD							\
	EM( V4L2_FIELD_ANY,		"ANY" )				\
	EM( V4L2_FIELD_NONE,		"NONE" )			\
	EM( V4L2_FIELD_TOP,		"TOP" )				\
	EM( V4L2_FIELD_BOTTOM,		"BOTTOM" )			\
	EM( V4L2_FIELD_INTERLACED,	"INTERLACED" )			\
	EM( V4L2_FIELD_SEQ_TB,		"SEQ_TB" )			\
	EM( V4L2_FIELD_SEQ_BT,		"SEQ_BT" )			\
	EM( V4L2_FIELD_ALTERNATE,	"ALTERNATE" )			\
	EM( V4L2_FIELD_INTERLACED_TB,	"INTERLACED_TB" )		\
	EMe( V4L2_FIELD_INTERLACED_BT,	"INTERLACED_BT" )

SHOW_FIELD

/*
 * Now redefine the EM() and EMe() macros to map the क्रमागतs to the strings
 * that will be prपूर्णांकed in the output.
 */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a, b)	अणुa, bपूर्ण,
#घोषणा EMe(a, b)	अणुa, bपूर्ण

/* V4L2_TC_TYPE_* are macros, not defines, they करो not need processing */

#घोषणा show_समयcode_type(type)					\
	__prपूर्णांक_symbolic(type,						\
		अणु V4L2_TC_TYPE_24FPS,		"24FPS" पूर्ण,		\
		अणु V4L2_TC_TYPE_25FPS,		"25FPS" पूर्ण,		\
		अणु V4L2_TC_TYPE_30FPS,		"30FPS" पूर्ण,		\
		अणु V4L2_TC_TYPE_50FPS,		"50FPS" पूर्ण,		\
		अणु V4L2_TC_TYPE_60FPS,		"60FPS" पूर्ण)

#घोषणा show_flags(flags)						      \
	__prपूर्णांक_flags(flags, "|",					      \
		अणु V4L2_BUF_FLAG_MAPPED,		     "MAPPED" पूर्ण,	      \
		अणु V4L2_BUF_FLAG_QUEUED,		     "QUEUED" पूर्ण,	      \
		अणु V4L2_BUF_FLAG_DONE,		     "DONE" पूर्ण,		      \
		अणु V4L2_BUF_FLAG_KEYFRAME,	     "KEYFRAME" पूर्ण,	      \
		अणु V4L2_BUF_FLAG_PFRAME,		     "PFRAME" पूर्ण,	      \
		अणु V4L2_BUF_FLAG_BFRAME,		     "BFRAME" पूर्ण,	      \
		अणु V4L2_BUF_FLAG_ERROR,		     "ERROR" पूर्ण,		      \
		अणु V4L2_BUF_FLAG_TIMECODE,	     "TIMECODE" पूर्ण,	      \
		अणु V4L2_BUF_FLAG_PREPARED,	     "PREPARED" पूर्ण,	      \
		अणु V4L2_BUF_FLAG_NO_CACHE_INVALIDATE, "NO_CACHE_INVALIDATE" पूर्ण, \
		अणु V4L2_BUF_FLAG_NO_CACHE_CLEAN,	     "NO_CACHE_CLEAN" पूर्ण,      \
		अणु V4L2_BUF_FLAG_TIMESTAMP_MASK,	     "TIMESTAMP_MASK" पूर्ण,      \
		अणु V4L2_BUF_FLAG_TIMESTAMP_UNKNOWN,   "TIMESTAMP_UNKNOWN" पूर्ण,   \
		अणु V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC, "TIMESTAMP_MONOTONIC" पूर्ण, \
		अणु V4L2_BUF_FLAG_TIMESTAMP_COPY,	     "TIMESTAMP_COPY" पूर्ण,      \
		अणु V4L2_BUF_FLAG_LAST,                "LAST" पूर्ण)

#घोषणा show_समयcode_flags(flags)					  \
	__prपूर्णांक_flags(flags, "|",					  \
		अणु V4L2_TC_FLAG_DROPFRAME,       "DROPFRAME" पूर्ण,		  \
		अणु V4L2_TC_FLAG_COLORFRAME,      "COLORFRAME" पूर्ण,		  \
		अणु V4L2_TC_USERBITS_USERDEFINED,	"USERBITS_USERDEFINED" पूर्ण, \
		अणु V4L2_TC_USERBITS_8BITCHARS,	"USERBITS_8BITCHARS" पूर्ण)

DECLARE_EVENT_CLASS(v4l2_event_class,
	TP_PROTO(पूर्णांक minor, काष्ठा v4l2_buffer *buf),

	TP_ARGS(minor, buf),

	TP_STRUCT__entry(
		__field(पूर्णांक, minor)
		__field(u32, index)
		__field(u32, type)
		__field(u32, bytesused)
		__field(u32, flags)
		__field(u32, field)
		__field(s64, बारtamp)
		__field(u32, समयcode_type)
		__field(u32, समयcode_flags)
		__field(u8, समयcode_frames)
		__field(u8, समयcode_seconds)
		__field(u8, समयcode_minutes)
		__field(u8, समयcode_hours)
		__field(u8, समयcode_userbits0)
		__field(u8, समयcode_userbits1)
		__field(u8, समयcode_userbits2)
		__field(u8, समयcode_userbits3)
		__field(u32, sequence)
	),

	TP_fast_assign(
		__entry->minor = minor;
		__entry->index = buf->index;
		__entry->type = buf->type;
		__entry->bytesused = buf->bytesused;
		__entry->flags = buf->flags;
		__entry->field = buf->field;
		__entry->बारtamp = v4l2_buffer_get_बारtamp(buf);
		__entry->समयcode_type = buf->समयcode.type;
		__entry->समयcode_flags = buf->समयcode.flags;
		__entry->समयcode_frames = buf->समयcode.frames;
		__entry->समयcode_seconds = buf->समयcode.seconds;
		__entry->समयcode_minutes = buf->समयcode.minutes;
		__entry->समयcode_hours = buf->समयcode.hours;
		__entry->समयcode_userbits0 = buf->समयcode.userbits[0];
		__entry->समयcode_userbits1 = buf->समयcode.userbits[1];
		__entry->समयcode_userbits2 = buf->समयcode.userbits[2];
		__entry->समयcode_userbits3 = buf->समयcode.userbits[3];
		__entry->sequence = buf->sequence;
	),

	TP_prपूर्णांकk("minor = %d, index = %u, type = %s, bytesused = %u, "
		  "flags = %s, field = %s, timestamp = %llu, "
		  "timecode = { type = %s, flags = %s, frames = %u, "
		  "seconds = %u, minutes = %u, hours = %u, "
		  "userbits = { %u %u %u %u } }, sequence = %u", __entry->minor,
		  __entry->index, show_type(__entry->type),
		  __entry->bytesused,
		  show_flags(__entry->flags),
		  show_field(__entry->field),
		  __entry->बारtamp,
		  show_समयcode_type(__entry->समयcode_type),
		  show_समयcode_flags(__entry->समयcode_flags),
		  __entry->समयcode_frames,
		  __entry->समयcode_seconds,
		  __entry->समयcode_minutes,
		  __entry->समयcode_hours,
		  __entry->समयcode_userbits0,
		  __entry->समयcode_userbits1,
		  __entry->समयcode_userbits2,
		  __entry->समयcode_userbits3,
		  __entry->sequence
	)
)

DEFINE_EVENT(v4l2_event_class, v4l2_dqbuf,
	TP_PROTO(पूर्णांक minor, काष्ठा v4l2_buffer *buf),
	TP_ARGS(minor, buf)
);

DEFINE_EVENT(v4l2_event_class, v4l2_qbuf,
	TP_PROTO(पूर्णांक minor, काष्ठा v4l2_buffer *buf),
	TP_ARGS(minor, buf)
);

DECLARE_EVENT_CLASS(vb2_v4l2_event_class,
	TP_PROTO(काष्ठा vb2_queue *q, काष्ठा vb2_buffer *vb),
	TP_ARGS(q, vb),

	TP_STRUCT__entry(
		__field(पूर्णांक, minor)
		__field(u32, flags)
		__field(u32, field)
		__field(u64, बारtamp)
		__field(u32, समयcode_type)
		__field(u32, समयcode_flags)
		__field(u8, समयcode_frames)
		__field(u8, समयcode_seconds)
		__field(u8, समयcode_minutes)
		__field(u8, समयcode_hours)
		__field(u8, समयcode_userbits0)
		__field(u8, समयcode_userbits1)
		__field(u8, समयcode_userbits2)
		__field(u8, समयcode_userbits3)
		__field(u32, sequence)
	),

	TP_fast_assign(
		काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
		काष्ठा v4l2_fh *owner = q->owner;

		__entry->minor = owner ? owner->vdev->minor : -1;
		__entry->flags = vbuf->flags;
		__entry->field = vbuf->field;
		__entry->बारtamp = vb->बारtamp;
		__entry->समयcode_type = vbuf->समयcode.type;
		__entry->समयcode_flags = vbuf->समयcode.flags;
		__entry->समयcode_frames = vbuf->समयcode.frames;
		__entry->समयcode_seconds = vbuf->समयcode.seconds;
		__entry->समयcode_minutes = vbuf->समयcode.minutes;
		__entry->समयcode_hours = vbuf->समयcode.hours;
		__entry->समयcode_userbits0 = vbuf->समयcode.userbits[0];
		__entry->समयcode_userbits1 = vbuf->समयcode.userbits[1];
		__entry->समयcode_userbits2 = vbuf->समयcode.userbits[2];
		__entry->समयcode_userbits3 = vbuf->समयcode.userbits[3];
		__entry->sequence = vbuf->sequence;
	),

	TP_prपूर्णांकk("minor=%d flags = %s, field = %s, "
		  "timestamp = %llu, timecode = { type = %s, flags = %s, "
		  "frames = %u, seconds = %u, minutes = %u, hours = %u, "
		  "userbits = { %u %u %u %u } }, sequence = %u", __entry->minor,
		  show_flags(__entry->flags),
		  show_field(__entry->field),
		  __entry->बारtamp,
		  show_समयcode_type(__entry->समयcode_type),
		  show_समयcode_flags(__entry->समयcode_flags),
		  __entry->समयcode_frames,
		  __entry->समयcode_seconds,
		  __entry->समयcode_minutes,
		  __entry->समयcode_hours,
		  __entry->समयcode_userbits0,
		  __entry->समयcode_userbits1,
		  __entry->समयcode_userbits2,
		  __entry->समयcode_userbits3,
		  __entry->sequence
	)
)

DEFINE_EVENT(vb2_v4l2_event_class, vb2_v4l2_buf_करोne,
	TP_PROTO(काष्ठा vb2_queue *q, काष्ठा vb2_buffer *vb),
	TP_ARGS(q, vb)
);

DEFINE_EVENT(vb2_v4l2_event_class, vb2_v4l2_buf_queue,
	TP_PROTO(काष्ठा vb2_queue *q, काष्ठा vb2_buffer *vb),
	TP_ARGS(q, vb)
);

DEFINE_EVENT(vb2_v4l2_event_class, vb2_v4l2_dqbuf,
	TP_PROTO(काष्ठा vb2_queue *q, काष्ठा vb2_buffer *vb),
	TP_ARGS(q, vb)
);

DEFINE_EVENT(vb2_v4l2_event_class, vb2_v4l2_qbuf,
	TP_PROTO(काष्ठा vb2_queue *q, काष्ठा vb2_buffer *vb),
	TP_ARGS(q, vb)
);

#पूर्ण_अगर /* अगर !defined(_TRACE_V4L2_H) || defined(TRACE_HEADER_MULTI_READ) */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
